#pragma once

#include "SemanticAnalysis.h"

//添加内联函数声明
void SemanticAnalysis::addBuiltinFunc(std::string func_name, int argc, cact_basety_t basety, cact_basety_t ret_type){
    //建立形参列表，内联函数argc只能为0/1
    fparam_list_t fparam_list;
    if(argc == 1){
        std::string name = "arg0";
        //不指定初始值时，arrdims默认为空
        cact_type_t type = (cact_type_t){.is_const=false,.basety=basety};
        fparam_list.push_back((fparam_item_t){.name=name,.type=type});
    }
    symbol_table.func_table[func_name] = (func_symbol_item_t){.ret_type=ret_type,.fparam_list=fparam_list};
}

//二元操作检查，类型相同，不是VOID，不是数组
//stmt_assign赋值同样需要满足上述判断，使用临时的expr传入
void SemanticAnalysis::OperandCheck(cact_expr_ptr expr_ptr){
    cact_op_t op = expr_ptr->op;
    if(expr_ptr->subexprs.size()==1){
        //单操作数
        //不是数组
        if(expr_ptr->subexprs[0]->op == OP_ARRAY){
            std::cout << "Err: OperandCheck: Unary: subexprs cannot be array" << std::endl;
            exit(Semantic_ERR);
        }
        //根据操作检查类型
        cact_basety_t basety = expr_ptr->subexprs[0]->basety;
        if((op==OP_POS) || (op==OP_NEG)){
            if((basety!=BTY_INT) && (basety!=BTY_FLOAT) && (basety!=BTY_DOUBLE)){
                std::cout << "Err: OperandCheck: Unary: POS/NEG only support INT/FLAOT/DOUBLE" << std::endl;
                exit(Semantic_ERR);
            }
        }
        else if(op==OP_NOT){
            if(basety!=BTY_BOOL){
                std::cout << "Err: OperandCheck: Unary: NOT only support BOOL" << std::endl;
                exit(Semantic_ERR);
            }
        }
        else{
            std::cout << "CodeErr: OperandCheck: UnaryOP list: POS/NEG/NOT" << std::endl;
            exit(Code_ERR);
        }
    }
    else if(expr_ptr->subexprs.size()==2){
        //双操作数
        //不是数组
        if((expr_ptr->subexprs[0]->op == OP_ARRAY) || (expr_ptr->subexprs[1]->op == OP_ARRAY)){
            std::cout << "Err: Operand Check: Binary: subexprs cannot be array" << std::endl;
            exit(Semantic_ERR);
        }
        //类型相同
        if(expr_ptr->subexprs[0]->basety != expr_ptr->subexprs[1]->basety){
            std::cout << "Err: Operand Check: Binary: subexprs basety mismatched" << std::endl;
            exit(Semantic_ERR);
        }
        //根据操作检查类型
        cact_basety_t basety = expr_ptr->subexprs[0]->basety;
        if(op==OP_ASSIGN){
            if((basety!=BTY_BOOL) && (basety!=BTY_INT) && (basety!=BTY_FLOAT) && (basety!=BTY_DOUBLE)){
                std::cout << "Err: OperandCheck: Binary: ASSIGN only support BOOL/INT/FLOAT/DOUBLE" << std::endl;
                exit(Semantic_ERR);
            }
        }
        else if((op==OP_ADD) || (op==OP_SUB) || (op==OP_MUL) || (op==OP_DIV) || (op==OP_LEQ) || (op==OP_GEQ) || (op==OP_LT) || (op==OP_GT)){
            if((basety!=BTY_INT) && (basety!=BTY_FLOAT) && (basety!=BTY_DOUBLE)){
                std::cout << "Err: OperandCheck: Binary: ADD/SUB/MUL/DIV/LEQ/GEQ/LT/GT only support INT/FLOAT/DOUBLE" << std::endl;
                exit(Semantic_ERR);
            }
        }
        else if(op==OP_MOD){
            if(basety!=BTY_INT){
                std::cout << "Err: OperandCheck: Binary: MOD only support INT" << std::endl;
                exit(Semantic_ERR);
            }
        }
        else if((op==OP_EQ) || (op==OP_NEQ)){
            if((basety!=BTY_BOOL) && (basety!=BTY_INT) && (basety!=BTY_FLOAT) && (basety!=BTY_DOUBLE)){
                std::cout << "Err: OperandCheck: Binary: EQ/NEQ only support BOOL/INT/FLOAT/DOUBLE" << std::endl;
                exit(Semantic_ERR);
            }
        }
        else if((op==OP_AND) || (op==OP_OR)){
            if(basety!=BTY_BOOL){
                std::cout << "Err: OperandCheck: Binary: AND/OR only support BOOL" << std::endl;
                exit(Semantic_ERR);
            }
        }
        else{
            std::cout << "CodeErr: OperandCheck: BinaryOP list: ASSIGN/ADD/SUB/MUL/DIV/MOD/LEQ/GEQ/LT/GT/EQ/NEQ/AND/OR" << std::endl;
            exit(Code_ERR);
        }
    }
    else{
        std::cout << "CodeErr: OperandCheck: subexprs size is not 1/2" << std::endl;
        exit(Code_ERR);
    }
}

template <typename T1,typename T2>
void SemanticAnalysis::enterConst_Var_Decl(T1 *ctx,std::vector<T2*> def_list){
    //将后续Def的基本类型传递向btype，&def->type.basety非法
    for (auto def: def_list){
        ctx->bType()->passTo.push_back(&(def->basety));
    }
}

//有初始值的情况下，最终维度、各维度限制、基本类型分别在Def、constInitVal和constExp中完成检查
template <typename T1>
void SemanticAnalysis::enterConst_Var_Def(T1 *ctx){
    //有初始值时，basety和维度数据自顶向下继承
    if(ctx->constInitVal() != nullptr){
        ctx->constInitVal()->basety = ctx->basety;
        ctx->constInitVal()->dims_ptr = &(ctx->arraydims);
        //最顶层数组，且index为1时允许以平铺列表形式初始化
        ctx->constInitVal()->top = true;
    }
    
    //子节点arrayDims负责填写维度数组
    if(ctx->arrayDims() != nullptr){
        ctx->arrayDims()->dims_ptr = &(ctx->arraydims);
    }
}

//通过is_const区分constDef和varDef加入变量表的类型
template <typename T1>
void SemanticAnalysis::exitConst_Var_Def(T1 *ctx, bool is_const){
    std::string name = ctx->Ident()->getText();
    ctx->name = name;
    
    //检查当前作用域该变量是否声明
    auto iter = (symbol_table.var_table).find((name_scope_t){.name=name, .scope_ptr=cur_scope});
    if(iter != (symbol_table.var_table).end()){
        std::cout << "Err: Const_Var_Def: "<<name<<" Redefined" << std::endl;
        exit(Semantic_ERR);
    }
    
    //整合变量类型
    ctx->type = (cact_type_t){.is_const=is_const, .basety=ctx->basety, .arrdims=ctx->arraydims};

    #ifdef IR_gen
    bool is_global = cur_scope == symbol_table.root_scope;
    IR_op_t IRop;
    size_t len;
    std::string IR_name;
    if(is_global){
        IRop = IR_G_ALLOC;
        len = len_from_type(ctx->type);
        IR_name = newGvar(ctx->basety, is_const, len);
    }
    else{
        IRop = IR_L_ALLOC;
        len = len_from_type(ctx->type);
        IR_name = newLvar(ctx->basety, is_const, len);
    }
    //将IRname写入变量表，后续中间代码直接只用IRname
    symbol_table.var_table[(name_scope_t){name,cur_scope}] = (var_symbol_item_t){.type=ctx->type,.IR_name=IR_name};
    
    #else
    //将该变量加入变量表
    symbol_table.var_table[(name_scope_t){name,cur_scope}] = (var_symbol_item_t){.type=ctx->type};

    #endif
    //检查变量与初始值层级
    if(ctx->constInitVal()!=nullptr){
        //同时考虑非数组左右都应当为0
        if(ctx->arraydims.size() != ctx->constInitVal()->dim_index){
            //只有左边为数组，右侧为元素列表才允许不等
            if((ctx->arraydims.size() != 0) && (ctx->constInitVal()->dim_index==1)){
                ;
            }
            else{
                std::cout << "Err: Const_Var_Def: Def and Initval dims mismatched"<<std::endl;
                exit(Semantic_ERR);
            }
        }
        #ifdef IR_gen
        //arg1表示初始值串
        std::string initval = IMM_PREFIX + ctx->constInitVal()->value_list;
        addIRC( IRop,
                ctx->basety,
                IR_name,
                initval);
        #endif
    }
    else{
        #ifdef IR_gen
        addIRC( IRop,
                ctx->basety,
                IR_name);
        #endif
    }

}

//二元表达式模板，处理形似 aExp -> bExp | aExp op bExp
//使用is_boolexp 区分Mul/Add 和 Rel/Eq/LAnd/LOr 的不同返回值类型
//注意RelExp还可能推导出BoolConst，考虑该分支后再应用模板
template <typename T1,typename T2, typename T3, typename T4>
void SemanticAnalysis::exitBinaryExp(T1 *ctx, T2 *aExp, T3 *op_ptr, T4 *bExp, bool is_boolexp){
    if(aExp == nullptr){
        ctx->self = bExp->self;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[op_ptr->getText()];
        cact_basety_t basety;
        if(is_boolexp){
            basety = BTY_BOOL;
        }
        else{
            //任取一个子表达式类型，如果两个子表达式类型不一致，会在OperandCheck中报错
            basety = bExp->self->basety;
        }
        subexprs_t subexprs;
        subexprs.push_back(aExp->self);
        subexprs.push_back(bExp->self);
        //作为维度的intConst和子数组不允许操作，不需指定arrdims
        ctx->self.reset(new cact_expr_t{.op=op, .basety=basety, .subexprs=subexprs});

        //类型检查
        OperandCheck(ctx->self);
    }
}

void SemanticAnalysis::enterCompUnit(CACTParser::CompUnitContext *ctx){
    //初始化根作用域及当前作用域
    symbol_table.root_scope = new scope_t;
    symbol_table.root_scope -> parent = nullptr;
    cur_scope = symbol_table.root_scope;

    //添加内联函数
    addBuiltinFunc("print_int", 1, BTY_INT, BTY_VOID);
    addBuiltinFunc("print_float", 1, BTY_FLOAT, BTY_VOID);
    addBuiltinFunc("print_double", 1, BTY_DOUBLE, BTY_VOID);
    addBuiltinFunc("print_bool", 1, BTY_BOOL, BTY_VOID);
    
    addBuiltinFunc("get_int", 0, BTY_VOID, BTY_INT);
    addBuiltinFunc("get_float", 0, BTY_VOID, BTY_FLOAT);
    addBuiltinFunc("get_double", 0, BTY_VOID, BTY_DOUBLE);
}
void SemanticAnalysis::exitCompUnit(CACTParser::CompUnitContext *ctx){
    //检查main函数相关属性
    //是否存在
    auto iter = (symbol_table.func_table).find("main");
    if(iter == (symbol_table.func_table).end()){
        std::cout << "Err: MainCheck: Missing" << std::endl;
        exit(Semantic_ERR);
    }

    //获取表项
    auto item = iter->second;
    
    //形参数量
    if((item.fparam_list).size() != 0){
        std::cout << "Err: MainCheck: Arg isn't 0" << std::endl;
        exit(Semantic_ERR);
    }    

    //返回类型
    if(item.ret_type != BTY_INT){
        std::cout << "Err: MainCheck: Wrong ret_type" << std::endl;
    }
}

void SemanticAnalysis::enterDecl(CACTParser::DeclContext *ctx){}
void SemanticAnalysis::exitDecl(CACTParser::DeclContext *ctx){}

void SemanticAnalysis::enterConstDecl(CACTParser::ConstDeclContext *ctx){
    enterConst_Var_Decl(ctx,ctx->constDef());
}
void SemanticAnalysis::exitConstDecl(CACTParser::ConstDeclContext *ctx){}

void SemanticAnalysis::enterBType(CACTParser::BTypeContext *ctx){}
void SemanticAnalysis::exitBType(CACTParser::BTypeContext *ctx){
    ctx->basety = (typeutils.str_to_basety)[ctx->getText()];
    for(cact_basety_t* to: ctx->passTo){
        assert(to);
        *to = ctx->basety;
    }
}

void SemanticAnalysis::enterArrayDims(CACTParser::ArrayDimsContext *ctx){}
void SemanticAnalysis::exitArrayDims(CACTParser::ArrayDimsContext *ctx){
    for(auto dim: ctx->IntConst()){
        uint32_t len = std::stoi(dim->getText());
        ctx->dims_ptr->push_back(len);
    }

}

void SemanticAnalysis::enterConstDef(CACTParser::ConstDefContext *ctx){
    enterConst_Var_Def(ctx);
}
void SemanticAnalysis::exitConstDef(CACTParser::ConstDefContext *ctx){
    exitConst_Var_Def(ctx, true);
}

//对于多维数组：
//  basety自顶向下继承，在最内层节点(constExp)检查
//  维度自底向上检查，最内层index为1，直接推出constExp的为0
void SemanticAnalysis::enterConstInitVal(CACTParser::ConstInitValContext *ctx){
    //最内层元素传递给constExp
    if(ctx->constExp() != nullptr){
        ctx->constExp()->basety = ctx->basety;
    }
    
    //数组传递给子数组/元素
    //当可能的子节点数不为1时，返回类型是vector，不能直接与nullptr比较，而应当使用size
    if((ctx->constInitVal()).size()!=0){
        for (auto initval: ctx->constInitVal()){
            initval->basety = ctx->basety;
            initval->dims_ptr = ctx->dims_ptr;
            //表示内层数组
            initval->top = false;
        }
    }
}
void SemanticAnalysis::exitConstInitVal(CACTParser::ConstInitValContext *ctx){
    if(ctx->constExp() != nullptr){
        ctx->dim_index = 0;
        #ifdef IR_gen
            ctx->value_list = ctx->constExp()->valstr + ",";
        #endif
    }
    else{
        //检查是否存在维度数组
        if((*ctx->dims_ptr).size()==0){
            std::cout << "Err: constInitVal: lack of arraydims" <<std::endl;
            exit(Semantic_ERR);
        }
        //所有维度长度乘积
        int product = 1;
        for(int num: *(ctx->dims_ptr)){
            product *= num;
        }

        auto initval_list = ctx->constInitVal();
        size_t len = initval_list.size(); 
        if(len == 0){
            //考虑到数组形如int a[2]={}; 无需维度检查
            ctx->dim_index = 1;
        }
        else{
            //检查各子数组index是否一致，与第一个元素比较
            uint16_t child_index = initval_list[0]->dim_index;
            for(int i=1;i<len;i++){
                if((initval_list[i]->dim_index) != child_index){
                    std::cout << "Err: constInitVal: child_index mismatched" << std::endl;
                    exit(Semantic_ERR);
                }
            }
            //获得本层index
            ctx->dim_index = child_index + 1;
            if(ctx->top == true && ctx->dim_index == 1){
                //最外层数组，且无嵌套，允许以平铺列表初始化
                if(len > product){
                    std::cout << "Err: constInitVal: flatten: len greater than dims_product" << std::endl;
                    exit(Semantic_ERR);
                }
            }
            else{
                //嵌套形式定义
                //维度索引相对应的数组索引
                int index = (*ctx->dims_ptr).size() - ctx->dim_index;
                if(index<0){
                    std::cout << "Err: constInitVal: nested: layer greater than dims_size" << std::endl;
                    exit(Semantic_ERR);
                }
                size_t dim_len = (*ctx->dims_ptr)[index];
                if(len > dim_len){
                    std::cout << "Err: constInitVal: nested: len greater than dim_len" << std::endl;
                    exit(Semantic_ERR);
                }
            }
        }

        //占位长度hold_len取决于是否顶层
        //前部分用子数组填充，后部分占位填充
        #ifdef IR_gen
        size_t hold_len;
        if(ctx->top == true && ctx->dim_index == 1){
            hold_len = product;
        }
        else{
            int index = (*ctx->dims_ptr).size() - ctx->dim_index;
            hold_len = (*ctx->dims_ptr)[index];
        }
        
        for(auto initval:initval_list){
            ctx->value_list += initval->value_list;
        }
        //缺失一个元素需要补充的占位符个数,最底层数组为1，次层数组为底层长度
        int subproduct = 1;
        for(int i=1;i<ctx->dim_index;i++){
            int index = (*ctx->dims_ptr).size() - i;
            subproduct *= (*ctx->dims_ptr)[index];
        }
        std::string holder = ARRAY_PLACEHOLDER + std::string(",");
        for (int i=0;i<(hold_len-len)*subproduct;i++){
            ctx->value_list += holder;
        }
        #endif
    }

}

//VarDecl/ValDef和ConstDecl/ConstDef逻辑一致
void SemanticAnalysis::enterVarDecl(CACTParser::VarDeclContext *ctx){
    enterConst_Var_Decl(ctx,ctx->varDef());
}
void SemanticAnalysis::exitVarDecl(CACTParser::VarDeclContext *ctx){}

void SemanticAnalysis::enterVarDef(CACTParser::VarDefContext *ctx){
    enterConst_Var_Def(ctx);
}
void SemanticAnalysis::exitVarDef(CACTParser::VarDefContext *ctx){
    exitConst_Var_Def(ctx, false);
}

void SemanticAnalysis::enterFuncDef(CACTParser::FuncDefContext *ctx){
    //由子节点填写形参列表，指定形参顺序
    int order = 0;
    for(auto fparam: ctx->funcFParam()){
        fparam->fparam_list_ptr = &(ctx->fparam_list);
        fparam->order = order;
        order ++;
    }
    
    //对于block，由fparam提供形参列表
    ctx->block()->fparam_list_ptr = &(ctx->fparam_list);

    #ifdef IR_gen
    //这里类型还未获得，中间代码生成汇编时从符号表提取即可
    addIRC( IR_FUNC_BEGIN,
            BTY_UNKNOWN,
            ctx->Ident()->getText());
    #endif
}
void SemanticAnalysis::exitFuncDef(CACTParser::FuncDefContext *ctx){
    std::string name = ctx->Ident()->getText();
    cact_basety_t ret_type = ctx->funcType()->basety;

    //检查符号表中是否已定义
    if((symbol_table.func_table).find(name) != (symbol_table.func_table).end()){
        std::cout << "Err: FuncDef: "<<name<<" Redefined" << std::endl;
        exit(Semantic_ERR);
    }
    
    //未定义则添加
    func_symbol_item_t item = (func_symbol_item_t){.ret_type=ret_type, .fparam_list=ctx->fparam_list};
    (symbol_table.func_table)[name] = item;

    //检查声明类型与块返回类型一致性
    if(ret_type != ctx->block()->ret_type){
        std::cout << "Err: FuncDef: Func_type mismatched block ret_type" << std::endl;
        exit(Semantic_ERR);
    }

    #ifdef IR_gen
    addIRC( IR_FUNC_END,
            BTY_UNKNOWN,
            ctx->Ident()->getText());
    #endif
}

void SemanticAnalysis::enterFuncType(CACTParser::FuncTypeContext *ctx){}
void SemanticAnalysis::exitFuncType(CACTParser::FuncTypeContext *ctx){
    ctx->basety = (typeutils.str_to_basety)[ctx->getText()];
}

void SemanticAnalysis::enterFuncFParam(CACTParser::FuncFParamContext *ctx){}
void SemanticAnalysis::exitFuncFParam(CACTParser::FuncFParamContext *ctx){
    std::string name = ctx->Ident()->getText();
    cact_basety_t basety = ctx->bType()->basety;
    arrdims_t arrdims;
    
    //根据括号判断总层数
    int dim_layer = (ctx->LeftBracket()).size();
    if((ctx->LeftBracket()).size() != ctx->IntConst().size()){
        //对应最外层省略情形，后续根据是否为0判断隐式声明
        arrdims.push_back(0);
    }
    for(auto dim: ctx->IntConst()){
        uint32_t len = std::stoi(dim->getText());
        //依次为最外层到最内层元素
        arrdims.push_back(len);
    }
    
    //整合类型
    cact_type_t type = (cact_type_t){.is_const=false, .basety=basety, .arrdims=arrdims};

    //在形参列表中查找是否已定义，遍历vector
    for(int i=0;i<(*ctx->fparam_list_ptr).size();i++){
        if(name == (*ctx->fparam_list_ptr)[i].name){
            std::cout<< "Err: FuncFParam: "<<name<<" Redefined" << std::endl;
            exit(Semantic_ERR);
        }
    }

    //未定义则添加
    (*ctx->fparam_list_ptr).push_back((fparam_item_t){.name=name,.type=type});
    
}

void SemanticAnalysis::enterLab(CACTParser::LabContext *ctx){
    #ifdef IR_gen
    addIRC( IR_LABEL,
            BTY_UNKNOWN,
            ctx->in_label);
    #endif
}
void SemanticAnalysis::exitLab(CACTParser::LabContext *ctx){}

void SemanticAnalysis::enterGo(CACTParser::GoContext *ctx){
    #ifdef IR_gen
    addIRC( IR_J,
            BTY_UNKNOWN,
            ctx->out_label);
    #endif
}
void SemanticAnalysis::exitGo(CACTParser::GoContext *ctx){}

void SemanticAnalysis::enterBlock(CACTParser::BlockContext *ctx){
    //更改当前作用域
    scope_t *new_scope = new scope_t;
    new_scope->parent = cur_scope;
    cur_scope = new_scope;

    //对于函数声明作用域，将形参列表逐一添加到作用域
    if(ctx->fparam_list_ptr != nullptr){
        for(int i=0;i<(*ctx->fparam_list_ptr).size();i++){
            fparam_item_t fparam = (*ctx->fparam_list_ptr)[i];

            #ifdef IR_gen
            cact_basety_t basety;
            if(fparam.type.arrdims.size()!=0){
                switch(fparam.type.basety){
                    case BTY_INT:   basety = BTY_INT_PTR; break;
                    case BTY_BOOL:  basety = BTY_BOOL_PTR; break;
                    case BTY_FLOAT: basety = BTY_FLOAT_PTR; break;
                    case BTY_DOUBLE: basety = BTY_DOUBLE_PTR; break;
                    default: break;
                }
            }
            else{
                basety = fparam.type.basety;
            }
            std::string IR_name = newLvar(basety);//使用缺省参数 isconst=false,len=1
            (*ctx->fparam_list_ptr)[i].IR_name = IR_name;
            var_symbol_item_t item = (var_symbol_item_t){.type=fparam.type,.IR_name=IR_name};
            
            #else
            var_symbol_item_t item = (var_symbol_item_t){.type=fparam.type};
            
            #endif   
                     
            (symbol_table.var_table)[(name_scope_t){.name=fparam.name, .scope_ptr=cur_scope}] = item;
        }        
    }

    #ifdef IR_gen
    for(auto stmt:ctx->stmt()){
        stmt->break_label = ctx->break_label;
        stmt->continue_label = ctx->continue_label;
    }
    #endif
}
void SemanticAnalysis::exitBlock(CACTParser::BlockContext *ctx){
    //根据简化，若有return，一定在最后一个语句
    //根据指针判断最后一个子节点是stmt
    if(ctx->stmt().size()!=0 && (void*)(ctx->children[ctx->children.size()-2]) == (void*)(*ctx->stmt().rbegin())){
        ctx->ret_type = (*ctx->stmt().rbegin())->ret_type;
    }
    else{
        ctx->ret_type = BTY_VOID;
    }
    //退出作用域
    cur_scope = cur_scope->parent;

}

void SemanticAnalysis::enterStmt_assign(CACTParser::Stmt_assignContext *ctx){
    // #ifdef IR_gen
    // //标识左值使用场景为赋值
    // ctx->lVal()->is_store = true; 
    // #endif
}
void SemanticAnalysis::exitStmt_assign(CACTParser::Stmt_assignContext *ctx){
    //左值检查(是否存在于变量表在exitLVal中完成)
    //检查不可为常量
    if(ctx->lVal()->is_const == true){
        std::cout << "Err: Stmt_Assign: Cannot assign to const" << std::endl;
        exit(Semantic_ERR);
    }

    //类型检查，创建临时表达式以应用框架
    cact_op_t op = (typeutils.str_to_op)[ctx->ASSIGN()->getText()];
    subexprs_t subexprs;
    subexprs.push_back(ctx->lVal()->self);
    subexprs.push_back(ctx->exp()->self);
    cact_expr_ptr expr_ptr(new cact_expr_t{.op=op, .basety=BTY_UNKNOWN, .subexprs=subexprs});
    OperandCheck(expr_ptr);

    //返回类型
    ctx->ret_type = BTY_VOID; 

    #ifdef IR_gen
    addIRC( IR_ASSIGN,
            ctx->exp()->self->basety,
            ctx->lVal()->result_name,
            ctx->exp()->result_name);
    #endif
}

void SemanticAnalysis::enterStmt_exp(CACTParser::Stmt_expContext *ctx){}
void SemanticAnalysis::exitStmt_exp(CACTParser::Stmt_expContext *ctx){
    ctx->ret_type = BTY_VOID;
}

void SemanticAnalysis::enterStmt_block(CACTParser::Stmt_blockContext *ctx){
    ctx->block()->fparam_list_ptr = nullptr;
    #ifdef IR_gen
    ctx->block()->break_label = ctx->break_label;
    ctx->block()->continue_label = ctx->continue_label;
    #endif
}
void SemanticAnalysis::exitStmt_block(CACTParser::Stmt_blockContext *ctx){
    //当块最后一个节点是子块时，继承其返回类型
    ctx->ret_type = ctx->block()->ret_type;
}

void SemanticAnalysis::enterStmt_if(CACTParser::Stmt_ifContext *ctx){
    #ifdef IR_gen
    std::string end_label = newLabel();
    int branch = (ctx->stmt()).size();
    //xx_start表示某个分支块最开始的语句
    //省略了最后一个分支跳转到end_label的语句
    if(branch == 1){ //if
        std::string if_start = newLabel();
        ctx->cond()->true_label = if_start;
        ctx->cond()->false_label = end_label;
        ctx->lab()[0]->in_label = if_start;
        ctx->lab()[1]->in_label = end_label;
    }
    if(branch == 2){ //if-else
        std::string if_start = newLabel();
        std::string else_start = newLabel();
        ctx->cond()->true_label = if_start;
        ctx->cond()->false_label = else_start;
        ctx->lab()[0]->in_label = if_start;
        ctx->lab()[1]->in_label = else_start;
        ctx->lab()[2]->in_label = end_label;
        ctx->go()->out_label = end_label;
    }
    //沿子节点传递
    for(auto stmt: ctx->stmt()){
        stmt->break_label = ctx->break_label;
        stmt->continue_label = ctx->continue_label;
    }
    #endif
}
void SemanticAnalysis::exitStmt_if(CACTParser::Stmt_ifContext *ctx){
    //根据简化，如果if-else语句的stmt含有return，则在块的最后一句
    //将省略的else分支视为返回类型void
    //错误情形如下：
    //1. 只有if，且stmt返回类型不为void
    //2. if-else,且stmt返回类型不一致
    int branch = (ctx->stmt()).size();
    if(branch == 1 && ctx->stmt()[0]->ret_type != BTY_VOID){
        std::cout << "Err: Stmt_If: If-only ret_type must be VOID" <<std::endl;
        exit(Semantic_ERR);
    }
    if(branch == 2 && ctx->stmt()[0]->ret_type != ctx->stmt()[1]->ret_type){
        std::cout << "Err: Stmt_If: If-Else ret_type mismatched" << std::endl;
        exit(Semantic_ERR);
    }

    ctx->ret_type = ctx->stmt()[0]->ret_type;
}

void SemanticAnalysis::enterStmt_while(CACTParser::Stmt_whileContext *ctx){
    #ifdef IR_gen
    std::string start_label = newLabel();
    std::string end_label = newLabel();
    std::string blk_start = newLabel();
    ctx->cond()->true_label = blk_start;
    ctx->cond()->false_label = end_label;
    ctx->lab()[0]->in_label = start_label;
    ctx->lab()[1]->in_label = blk_start;
    ctx->lab()[2]->in_label = end_label;
    ctx->go()->out_label = start_label;
    //沿子节点传递
    ctx->stmt()->break_label = end_label;
    ctx->stmt()->continue_label = start_label;
    #endif
}
void SemanticAnalysis::exitStmt_while(CACTParser::Stmt_whileContext *ctx){
    //根据简化，如果while语句stmt含有return，则在块最后
    //错误情形，while的stmt返回类型不为VOID
    if(ctx->stmt()->ret_type != BTY_VOID){
        std::cout << "Err: Stmt_While: stmt ret_type must be VOID" << std::endl;
        exit(Semantic_ERR);
    }

    ctx->ret_type = ctx->stmt()->ret_type;
}

void SemanticAnalysis::enterStmt_bcr(CACTParser::Stmt_bcrContext *ctx){
}
void SemanticAnalysis::exitStmt_bcr(CACTParser::Stmt_bcrContext *ctx){
    //return exp时由exp类型决定，其余都为VOID
    if(ctx->RETURN()!=nullptr){
        if(ctx->exp() != nullptr){ //return exp
            //数组检查
            if(ctx->exp()->self->op == OP_ARRAY){
                std::cout << "Err: Stmt_bcr: stmt ret_type cannot be array" << std::endl;
                exit(Semantic_ERR);
            }
            ctx->ret_type = ctx->exp()->self->basety;
            #ifdef IR_gen
            addIRC( IR_RETURN,
                    ctx->ret_type,
                    ctx->exp()->result_name);
            #endif
        }
        else{ //return语句负责将变量存到a0，exp为空时不需要
            ctx->ret_type = BTY_VOID;
        }
    }
    else{
        ctx->ret_type = BTY_VOID;
        #ifdef IR_gen
        if(ctx->BREAK()!=nullptr){
            addIRC( IR_J,
                    BTY_UNKNOWN,
                    ctx->break_label);
        }
        else if(ctx->CONTINUE()!=nullptr){
            addIRC( IR_J,
                    BTY_UNKNOWN,
                    ctx->continue_label);
        }
        #endif
    }

}

void SemanticAnalysis::enterExp(CACTParser::ExpContext *ctx){}
void SemanticAnalysis::exitExp(CACTParser::ExpContext *ctx){
    if(ctx->BoolConst() != nullptr){
        //创建self指向的结构体
        cact_op_t op = OP_BASE;
        ctx->self.reset(new cact_expr_t{.op=op, .basety=BTY_BOOL});
        #ifdef IR_gen
        bool is_true = ctx->BoolConst()->getText() == "true";
        if(is_true){
            ctx->result_name = IMM_PREFIX + std::to_string(1);
        }
        else{
            ctx->result_name = IMM_PREFIX + std::to_string(0);
        }
        #endif
    }
    else{
        ctx->self = ctx->addExp()->self;
        #ifdef IR_gen
        ctx->result_name = ctx->addExp()->result_name;
        #endif
    }
}

void SemanticAnalysis::enterConstExp(CACTParser::ConstExpContext *ctx){}
void SemanticAnalysis::exitConstExp(CACTParser::ConstExpContext *ctx){
    //在constInitVal中，已经继承了声明基本类型
    //与值类型比较
    if(ctx->number() != nullptr){
        cact_basety_t valty = ctx->number()->self->basety;
        if(ctx->basety != valty){
            std::cout<<"Err: ConstExp: number type mismatched" << std::endl;
            exit(Semantic_ERR);
        }
        #ifdef IR_gen
        ctx->valstr = ctx->number()->getText();
        #endif
    }
    if(ctx->BoolConst() != nullptr){
        if(ctx->basety != BTY_BOOL){
            std::cout<<"Err: ConstExp: BoolConst type mismatched" << std::endl;
            exit(Semantic_ERR);
        }
        #ifdef IR_gen
        bool is_true = ctx->BoolConst()->getText() == "true";
        if(is_true){
            ctx->valstr = std::to_string(1);
        }
        else{
            ctx->valstr = std::to_string(0);
        }
        #endif
    }
}

void SemanticAnalysis::enterCond(CACTParser::CondContext *ctx){
    #ifdef IR_gen
    ctx->lOrExp()->true_label = ctx->true_label;
    ctx->lOrExp()->false_label = ctx->false_label;
    #endif
}
void SemanticAnalysis::exitCond(CACTParser::CondContext *ctx){
    auto expr_ptr = ctx->lOrExp()->self;
    if(expr_ptr->basety != BTY_BOOL || expr_ptr->op == OP_ARRAY){
        std::cout << "Err: Cond: cond must be single bool" << std::endl;
        exit(Semantic_ERR);
    }
}

void SemanticAnalysis::enterLVal(CACTParser::LValContext *ctx){}
void SemanticAnalysis::exitLVal(CACTParser::LValContext *ctx){
    std::string name = ctx->Ident()->getText();
    
    //从变量表检查和提取，使用符号表中定义的向根追溯查找
    auto iter = symbol_table.deepfind(name,cur_scope);

    //判断是否存在
    if(iter == (symbol_table.var_table).end()){
        std::cout << "Err: LVal: " << name << " Undefined" << std::endl;
        exit(Semantic_ERR);
    }

    #ifdef IR_gen
    //注意在完成上述检查后才可获取，避免段错误
    std::string IR_name = (iter->second).IR_name;
    #endif

    //维度检查和类型继承
    auto exp_list = ctx->exp();
    int layer = exp_list.size();
    cact_type_t iter_type = (iter->second).type;

    //常量属性继承：用于赋值时判断
    ctx->is_const = iter_type.is_const;

    if(layer == 0){
        //不带中括号，类型相同。将原类型转换为self指向的expr结构体
        cact_op_t op;
        //判断该变量是否数组
        if(iter_type.arrdims.size() == 0){
            op = OP_ITEM;
        }
        else{
            op = OP_ARRAY;
        }
        ctx->self.reset(new cact_expr_t{.op=op, .basety=iter_type.basety, .arrdims=iter_type.arrdims});
        
        #ifdef IR_gen
        ctx->result_name = IR_name;
        #endif
    }
    else{
        //带中括号，layer前检查维度，layer后继承维度
        size_t dim_size = (iter_type.arrdims).size();
        //检查layer范围
        if(layer > dim_size){
            std::cout << "Err: LVal: left leyer greater than var_item dims" << std::endl;
            exit(Semantic_ERR);
        }

        //维度检查
        for(int i=0;i<layer;i++){
            //类型检查：必须是int，但不要求是终结符常量，不需要越界检查
            auto expr_ptr = exp_list[i]->self;
            if(expr_ptr->basety != BTY_INT && expr_ptr->op != OP_ARRAY){
                std::cout << "Err: LVal: expr for dims must be int" << std::endl;
                exit(Semantic_ERR);
            }
        }

        #ifdef IR_gen
        //统计字节偏移量，使用临时变量
        std::string byte_offset = newTemp(BTY_INT);
        addIRC(IR_L_ALLOC,BTY_INT,byte_offset);
        //单位元素的字节偏移，语义分析不出现PTR，只有IR传参的时候可能使用
        int base_size;
        switch(iter_type.basety){
            case BTY_BOOL: 
                base_size = 1; break;
            case BTY_INT: case BTY_FLOAT:  
                base_size = 4; break;
            case BTY_DOUBLE: 
                base_size = 8; break;
            default: 
                break;
        }

        int subproduct = 1; //后续维度乘积，注意这里不能用总维度除以首维度，因为首维度允许隐式声明
        //单独把layer=1的情况提取出来，节省一条指令
        for(int j=1;j<dim_size;j++){
            subproduct *= iter_type.arrdims[j];
        }
        std::string times = IMM_PREFIX + std::to_string(subproduct * base_size);
        addIRC(IR_MUL,BTY_INT,byte_offset,exp_list[0]->result_name,times);
        
        if(layer>1){ //a[i][j]
            std::string index_offset = newTemp(BTY_INT); //当前维度的字节偏移
            addIRC(IR_L_ALLOC,BTY_INT,index_offset);
            for(int i=1;i<layer;i++){
                int subproduct = 1;
                for(int j=i+1;j<dim_size;j++){
                    subproduct *= iter_type.arrdims[j];
                }
                std::string times = IMM_PREFIX + std::to_string(subproduct*base_size);
                addIRC(IR_MUL,BTY_INT,index_offset,exp_list[i]->result_name,times);
                addIRC(IR_ADD,BTY_INT,byte_offset,byte_offset,index_offset);
            }
        }
        #endif

        //建立结构体
        cact_op_t op;
        arrdims_t arrdims;
        //判断类型
        if(layer == dim_size){
            op = OP_ITEM;
        }
        else{
            op = OP_ARRAY;
            //子数组，继承后续维度
            for(int i=layer;i<dim_size;i++){
                arrdims.push_back(iter_type.arrdims[i]);
            }
        }
        ctx->self.reset(new cact_expr_t{.op=op, .basety=iter_type.basety, .arrdims=arrdims});

        #ifdef IR_gen
        //形如abc>%2 或abc<%2
        std::string infix = (op==OP_ARRAY) ? ADDR_INFIX : ITEM_INFIX;
        ctx->result_name = IR_name + infix + byte_offset;
        #endif
    }

}

void SemanticAnalysis::enterPrimaryExp(CACTParser::PrimaryExpContext *ctx){}
void SemanticAnalysis::exitPrimaryExp(CACTParser::PrimaryExpContext *ctx){
    if(ctx->number()!=nullptr){
        ctx->self = ctx->number()->self;
        #ifdef IR_gen
        ctx->result_name = IMM_PREFIX + ctx->number()->getText();
        #endif
    }
    else if(ctx->lVal()!=nullptr){
        ctx->self = ctx->lVal()->self;
        #ifdef IR_gen
        ctx->result_name = ctx->lVal()->result_name;
        #endif
    }
    else{
        ctx->self = ctx->exp()->self;
        #ifdef IR_gen
        ctx->result_name = ctx->exp()->result_name;
        #endif
    }
}

void SemanticAnalysis::enterNumber(CACTParser::NumberContext *ctx){}
void SemanticAnalysis::exitNumber(CACTParser::NumberContext *ctx){
    cact_op_t op = OP_BASE;
    cact_basety_t basety;
    if(ctx->IntConst() != nullptr){
        basety = BTY_INT;
        //构造指向结构体的指针
        ctx->self.reset(new cact_expr_t{.op=op, .basety=basety});
    }
    else if(ctx->FloatConst() != nullptr){
        basety = BTY_FLOAT;
        ctx->self.reset(new cact_expr_t{.op=op, .basety=basety});
    }
    else if(ctx->DoubleConst() != nullptr){
        basety = BTY_DOUBLE;
        ctx->self.reset(new cact_expr_t{.op=op, .basety=basety});
    }
}

void SemanticAnalysis::enterUnaryExp(CACTParser::UnaryExpContext *ctx){}
void SemanticAnalysis::exitUnaryExp(CACTParser::UnaryExpContext *ctx){
    if(ctx->primaryExp()!=nullptr){
        ctx->self = ctx->primaryExp()->self;
        #ifdef IR_gen
        ctx->result_name = ctx->primaryExp()->result_name;
        #endif
    }
    else if(ctx->unaryExp()!=nullptr){
        //注意这里的OP_POS/OP_NEG，通过后缀与二元区分
        cact_op_t op = (typeutils.str_to_op)[ctx->unaryOp()->getText()+"U"];
        cact_basety_t basety = ctx->unaryExp()->self->basety;
        subexprs_t subexprs;
        subexprs.push_back(ctx->unaryExp()->self);

        //构造self指向的结构体
        //注：因为不能对数组操作，数组维度也不能经过任何操作，无需为arrdims赋值
        ctx->self.reset(new cact_expr_t{.op=op, .basety=basety, .subexprs=subexprs});

        //针对操作符的操作对象检查
        OperandCheck(ctx->self);

        #ifdef IR_gen
        //形如a=+b，直接当做a=b即可
        if(op==OP_POS){
            ctx->result_name = ctx->unaryExp()->result_name;
        }
        else{
            IR_op_t IRop = (typeutils.op_to_IRop)[op];
            ctx->result_name = newTemp(basety);
            addIRC( IR_L_ALLOC,
                    basety,
                    ctx->result_name);
            addIRC( IRop, 
                    basety, 
                    ctx->result_name, 
                    ctx->unaryExp()->result_name);
        }
        #endif
    }
    else{ //func call
        std::string func_name = ctx->Ident()->getText();
        //检查函数表项是否存在
        auto iter = (symbol_table.func_table).find(func_name);
        if(iter == (symbol_table.func_table).end()){
            std::cout << "Err: UnaryExp: Called Func" << func_name << " Undefined" << std::endl;
            exit(Semantic_ERR);
        }
        
        //构造self指向的结构体，类型同变量
        cact_op_t op = OP_ITEM;
        cact_basety_t basety = (iter->second).ret_type;
        ctx->self.reset(new cact_expr_t{.op=op, .basety=basety});

        //检查参数列表
        auto fparam_list = (iter->second).fparam_list;
        int fparam_len = fparam_list.size();
        if(ctx->funcRParams() == nullptr){
            //调用无参数，要求形参列表为空
            if(fparam_len != 0){
                std::cout << "Err: UnaryExp: param_len mismatched" << std::endl;
                exit(Semantic_ERR);
            }
        }
        else{ //至少含一个参数
            auto exp_list = ctx->funcRParams()->exp();
            //长度检查
            if(exp_list.size() != fparam_len){
                std::cout << "Err: UnaryExp: param_len mismatched" << std::endl;
                exit(Semantic_ERR);
            }
            
            //类型检查
            for(int i=0;i<fparam_len;i++){
                auto fparam_type = fparam_list[i].type;
                #ifdef IR_gen
                std::string expr_name = exp_list[i]->result_name;
                #endif
                auto expr_ptr = exp_list[i]->self;
                //基本类型检查
                if(expr_ptr->basety != fparam_type.basety){
                    std::cout << "Err: UnaryExp: param basety mismatched" << std::endl;
                    exit(Semantic_ERR);
                }

                size_t dim_size = fparam_type.arrdims.size();
                if(dim_size == 0){//传入元素情形
                    if(expr_ptr->op == OP_ARRAY){
                        std::cout << "Err: UnaryExp: expr cannot be array when fparam is not" << std::endl;
                        exit(Semantic_ERR);
                    }

                    #ifdef IR_gen
                    addIRC( IR_PARAM, 
                            expr_ptr->basety, 
                            expr_name);
                    #endif
                }
                else{//传入数组（指针）情形
                    //数组及维数检查
                    if((expr_ptr->op != OP_ARRAY) || (expr_ptr->arrdims.size() != dim_size)){
                        std::cout << "Err: UnaryExp: expr must be array with same dims as fparam" << std::endl;
                        exit(Semantic_ERR);
                    }
                    
                    //逐维度检查
                    for(int j=0;j<dim_size;j++){
                        if(j==0 && fparam_type.arrdims[j]==0){
                            //首维隐式声明时为0，忽略检查
                            continue;
                        }
                        if(expr_ptr->arrdims[j]!=fparam_type.arrdims[j]){
                            std::cout << "Err: UnaryExp: param dim_len mismatched" << std::endl;
                            exit(Semantic_ERR);
                        }
                    }

                    #ifdef IR_gen
                    cact_basety_t basety;
                    switch(expr_ptr->basety){
                        case BTY_INT: basety = BTY_INT_PTR; break;
                        case BTY_BOOL: basety = BTY_BOOL_PTR; break;
                        case BTY_FLOAT: basety = BTY_FLOAT_PTR; break;
                        case BTY_DOUBLE: basety = BTY_DOUBLE_PTR; break;
                        default: break; 
                    }
                    addIRC( IR_PARAM, 
                            basety, 
                            expr_name);                    
                    #endif
                }
            }
        }

        #ifdef IR_gen
        //传参结束，调用函数
        //函数类型为basety
        //arg1表示当函数类别不为void时，用临时变量存储
        if(basety==BTY_VOID){
            addIRC( IR_CALL,
                    BTY_VOID,
                    func_name);
        }
        else{
            ctx->result_name = newTemp(basety);
            addIRC( IR_L_ALLOC,
                    basety,
                    ctx->result_name);
            addIRC( IR_CALL,
                    basety,
                    func_name,
                    ctx->result_name);
        }
        #endif
    }
}

void SemanticAnalysis::enterUnaryOp(CACTParser::UnaryOpContext *ctx){}
void SemanticAnalysis::exitUnaryOp(CACTParser::UnaryOpContext *ctx){}

void SemanticAnalysis::enterFuncRParams(CACTParser::FuncRParamsContext *ctx){}
void SemanticAnalysis::exitFuncRParams(CACTParser::FuncRParamsContext *ctx){}

void SemanticAnalysis::enterMulExp(CACTParser::MulExpContext *ctx){}
void SemanticAnalysis::exitMulExp(CACTParser::MulExpContext *ctx){
    exitBinaryExp(ctx, ctx->mulExp(), ctx->mulOp(), ctx->unaryExp(), false);
    #ifdef IR_gen
    if(ctx->mulExp()==nullptr){
        ctx->result_name = ctx->unaryExp()->result_name;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[ctx->mulOp()->getText()];
        IR_op_t IRop = (typeutils.op_to_IRop)[op];
        cact_basety_t basety = ctx->unaryExp()->self->basety;
        ctx->result_name = newTemp(basety);
        addIRC( IR_L_ALLOC,
                basety,
                ctx->result_name);
        addIRC( IRop, 
                basety, 
                ctx->result_name, 
                ctx->mulExp()->result_name, 
                ctx->unaryExp()->result_name);
    }
    #endif
}

void SemanticAnalysis::enterMulOp(CACTParser::MulOpContext *ctx){}
void SemanticAnalysis::exitMulOp(CACTParser::MulOpContext *ctx){}

void SemanticAnalysis::enterAddExp(CACTParser::AddExpContext *ctx){}
void SemanticAnalysis::exitAddExp(CACTParser::AddExpContext *ctx){
    exitBinaryExp(ctx, ctx->addExp(), ctx->addOp(), ctx->mulExp(), false);
    #ifdef IR_gen
    if(ctx->addExp()==nullptr){
        ctx->result_name = ctx->mulExp()->result_name;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[ctx->addOp()->getText()];
        IR_op_t IRop = (typeutils.op_to_IRop)[op];
        cact_basety_t basety = ctx->mulExp()->self->basety;
        ctx->result_name = newTemp(basety);
        addIRC( IR_L_ALLOC,
                basety,
                ctx->result_name);
        addIRC( IRop, 
                basety, 
                ctx->result_name, 
                ctx->addExp()->result_name, 
                ctx->mulExp()->result_name);
    }
    #endif
}

void SemanticAnalysis::enterAddOp(CACTParser::AddOpContext *ctx){}
void SemanticAnalysis::exitAddOp(CACTParser::AddOpContext *ctx){}

//考虑a & true 和 a != true两种情形，前者需要label，后者需要存值
void SemanticAnalysis::enterRelExp(CACTParser::RelExpContext *ctx){
    #ifdef IR_gen
    if(ctx->relExp()!=nullptr){
        ctx->relExp()->has_label = false;
    }
    #endif
}

//考虑到if(0)等情况，这里bool可以直接看作1和0，从而合并到addExp情况中
void SemanticAnalysis::exitRelExp(CACTParser::RelExpContext *ctx){
    if(ctx->BoolConst()!=nullptr){
        //创建self所指结构体
        cact_op_t op = OP_BASE;
        ctx->self.reset(new cact_expr_t{.op=op, .basety=BTY_BOOL});
    }
    else{
        exitBinaryExp(ctx, ctx->relExp(), ctx->relOp(), ctx->addExp(), true);
    }

    #ifdef IR_gen
    if(ctx->BoolConst()!=nullptr){
        bool is_true = ctx->BoolConst()->getText() == "true";
        if(ctx->has_label){
            if(is_true){
                addIRC( IR_J,
                        BTY_UNKNOWN,
                        ctx->true_label);
            }
            else{
                addIRC( IR_J,
                        BTY_UNKNOWN,
                        ctx->false_label);
            }
        }
        else{
            if(is_true){
                ctx->result_name = IMM_PREFIX + std::to_string(1);
            }
            else{
                ctx->result_name = IMM_PREFIX + std::to_string(0);
            }
        }
    }
    else if(ctx->relExp()==nullptr){
        if(ctx->has_label){ //例如if(b) 其中b=0
            addIRC( IR_BNE,
                    ctx->addExp()->self->basety,
                    ctx->true_label,
                    ctx->addExp()->result_name,
                    IMM_PREFIX+std::to_string(0));
            addIRC( IR_J,
                    BTY_UNKNOWN,
                    ctx->false_label);
        }   
        else{
            ctx->result_name = ctx->addExp()->result_name;
        }
    }
    else{
        if(ctx->has_label){
            cact_op_t op = (typeutils.str_to_op)[ctx->relOp()->getText()];
            IR_op_t IRop = (typeutils.op_to_IRop)[op];
            
            addIRC( IRop,
                    ctx->addExp()->self->basety,
                    ctx->true_label,
                    ctx->relExp()->result_name,
                    ctx->addExp()->result_name);
            addIRC( IR_J,
                    BTY_UNKNOWN,
                    ctx->false_label);
        }
    }
    #endif
}

void SemanticAnalysis::enterRelOp(CACTParser::RelOpContext *ctx){}
void SemanticAnalysis::exitRelOp(CACTParser::RelOpContext *ctx){}

//不考虑a==b==c / a<b == c>d等复杂情形，因此eqExp和relExp都直接用标签，没有存储中间结果的情形
//即，二元推导之后默认都是一元传递，一元推导才传label
void SemanticAnalysis::enterEqExp(CACTParser::EqExpContext *ctx){
    #ifdef IR_gen
    if(ctx->eqExp()==nullptr){ //relExp
        ctx->relExp()->true_label = ctx->true_label;
        ctx->relExp()->false_label = ctx->false_label;
        //考虑到eqExp->relExp->true和eqExp->eqExp == relExp->true=a，二者relExp的has_label不同
        ctx->relExp()->has_label = ctx->has_label;
    }
    else{
        ctx->relExp()->has_label = false;
        ctx->eqExp()->has_label = false;
    }
    #endif
}
void SemanticAnalysis::exitEqExp(CACTParser::EqExpContext *ctx){
    exitBinaryExp(ctx, ctx->eqExp(), ctx->eqOp(), ctx->relExp(), true);
    #ifdef IR_gen
    if(ctx->eqExp()==nullptr){
        ctx->result_name = ctx->relExp()->result_name;
    }
    else if(ctx->has_label){
        cact_op_t op = (typeutils.str_to_op)[ctx->eqOp()->getText()];
        IR_op_t IRop = (typeutils.op_to_IRop)[op];
        addIRC( IRop,
                ctx->relExp()->self->basety,
                ctx->true_label,
                ctx->eqExp()->result_name,
                ctx->relExp()->result_name);
        addIRC( IR_J,
                BTY_UNKNOWN,
                ctx->false_label);
    }
    #endif
}

void SemanticAnalysis::enterEqOp(CACTParser::EqOpContext *ctx){}
void SemanticAnalysis::exitEqOp(CACTParser::EqOpContext *ctx){}

void SemanticAnalysis::enterLAndExp(CACTParser::LAndExpContext *ctx){
    #ifdef IR_gen
    if(ctx->lAndExp()!=nullptr){ //lAndExp AND eqExp
        //部分为true不需要特别处理，继续向下即可，不必和OR一样加额外标签
        std::string and_label = newLabel();
        ctx->lab()->in_label = and_label;
        ctx->lAndExp()->true_label = and_label;
        ctx->lAndExp()->false_label = ctx->false_label;
        ctx->eqExp()->true_label = ctx->true_label;
        ctx->eqExp()->false_label = ctx->false_label;
        ctx->eqExp()->has_label = true;
    }
    else{//eqExp
        ctx->eqExp()->true_label = ctx->true_label;
        ctx->eqExp()->false_label = ctx->false_label;
        ctx->eqExp()->has_label = true;
    }
    #endif
}
void SemanticAnalysis::exitLAndExp(CACTParser::LAndExpContext *ctx){
    exitBinaryExp(ctx, ctx->lAndExp(), ctx->AND(), ctx->eqExp(), true);
}

void SemanticAnalysis::enterLOrExp(CACTParser::LOrExpContext *ctx){
    #ifdef IR_gen
    if(ctx->lOrExp()!=nullptr){ //lOrExp OR lAandExp
        //lOrExp部分出错需要跳转到lAndExp前
        std::string or_label = newLabel();
        ctx->lab()->in_label = or_label;
        ctx->lOrExp()->true_label = ctx->true_label;
        ctx->lOrExp()->false_label = or_label;
        ctx->lAndExp()->true_label = ctx->true_label;
        ctx->lAndExp()->false_label = ctx->false_label;
    }
    else{//lAndExp 
        ctx->lAndExp()->true_label = ctx->true_label;
        ctx->lAndExp()->false_label = ctx->false_label;
    }
    #endif
}
void SemanticAnalysis::exitLOrExp(CACTParser::LOrExpContext *ctx){
    exitBinaryExp(ctx, ctx->lOrExp(), ctx->OR(), ctx->lAndExp(), true);
}



void SemanticAnalysis::enterEveryRule(antlr4::ParserRuleContext * ctx){
    int ruleIndex = ctx->getRuleIndex();
    node.push_back(ruleIndex);
    
    // std::cout << "enter " << ruleIndex << std::endl;
}
void SemanticAnalysis::exitEveryRule(antlr4::ParserRuleContext * ctx){

    int ruleIndex = ctx->getRuleIndex();
    node.pop_back();

    //打印下一次退出节点时需要弹出的，表示错误发生在exit该节点
    // std::cout << node.back() << std::endl;
}
void SemanticAnalysis::visitTerminal(antlr4::tree::TerminalNode * node){}
void SemanticAnalysis::visitErrorNode(antlr4::tree::ErrorNode * node){
    // std::cout << "Err: Syntax: "<< node->getText() << std::endl;
    // exit(Syntax_ERR);
}