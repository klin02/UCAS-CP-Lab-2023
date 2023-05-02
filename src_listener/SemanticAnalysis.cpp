#pragma once

#include "cact_types.h"
#include "SemanticAnalysis.h"

//添加内联函数声明
void SemanticAnalysis::addBuiltinFunc(std::string func_name, int argc, cact_basety_t basety, cact_basety_t ret_type){
    //建立形参列表，内联函数argc只能为0/1
    fparam_list_t fparam_list;
    if(argc == 1){
        std::string name = "arg0";
        //创建空vector
        arrdims_t arrdims;
        cact_type_t type = (cact_type_t){false, basety, arrdims};
        int order = 0;
        fparam_list[name] = (fparam_item_t){type, order};
    }
    symbol_table.func_table[func_name] = (func_symbol_item_t){func_name,ret_type,fparam_list};
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
        if((op==OP_ADD) || (op==OP_SUB)){
            if((basety!=BTY_INT) && (basety!=BTY_FLOAT) && (basety!=BTY_DOUBLE)){
                std::cout << "Err: OperandCheck: Unary: ADD/SUB only support INT/FLAOT/DOUBLE" << std::endl;
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
            std::cout << "CodeErr: OperandCheck: UnaryOP list: ADD/SUB/NOT" << std::endl;
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

void SemanticAnalysis::enterCompUnit(CACTParser::CompUnitContext *ctx){
    //初始化根作用域及当前作用域
    root_scope = new scope_t;
    root_scope -> parent = nullptr;
    cur_scope = root_scope;

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
    //将后续Def的基本类型传递向btype，&def->type.basety非法
    for (auto def: ctx->constDef()){
        ctx->bType()->passTo.push_back(&(def->basety));
    }
}
void SemanticAnalysis::exitConstDecl(CACTParser::ConstDeclContext *ctx){}

void SemanticAnalysis::enterBType(CACTParser::BTypeContext *ctx){}
void SemanticAnalysis::exitBType(CACTParser::BTypeContext *ctx){
    ctx->basety = (typeutils.str_to_val)[ctx->getText()];
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

//有初始值的情况下，维度及基本类型分别在constInitVal和constExp中完成检查
void SemanticAnalysis::enterConstDef(CACTParser::ConstDefContext *ctx){
    //有初始值时，basety和维度数据自顶向下继承
    if(ctx->constInitVal() != nullptr){
        ctx->constInitVal()->basety = ctx->basety;
        ctx->constInitVal()->dims_ptr = &(ctx->arraydims);
        ctx->constInitVal()->dim_index = 0;
        //最顶层数组，且index为1时允许以平铺列表形式初始化
        ctx->constInitVal()->top = true;
    }
    
    //子节点arrayDims负责填写维度数组
    if(ctx->arrayDims() != nullptr){
        ctx->arrayDims()->dims_ptr = &(ctx->arraydims);
    }
}
void SemanticAnalysis::exitConstDef(CACTParser::ConstDefContext *ctx){
    std::string name = ctx->Ident()->getText();
    ctx->name = name;
    //检查当前作用域该变量是否声明
    auto iter = (symbol_table.var_table).find((name_scope_t){name,cur_scope});
    if(iter != (symbol_table.var_table).end()){
        std::cout << "Err: constDef: "<<name<<" Redefined" << std::endl;
        exit(Semantic_ERR);
    }
    
    //整合变量类型
    ctx->type = (cact_type_t){true, ctx->basety, ctx->arraydims};
    
    //将该变量加入变量表
    symbol_table.var_table[(name_scope_t){name,cur_scope}] = (var_symbol_item_t){name,ctx->type,cur_scope};

    //检查变量与初始值层级
    if(ctx->constInitVal()!=nullptr){
        //同时考虑非数组左右都应当为0
        if(ctx->arraydims.size() != ctx->constInitVal()->dim_index){
            //只有左边为数组，右侧为元素列表才允许不等
            if((ctx->arraydims.size() != 0) && (ctx->constInitVal()->dim_index==1)){
                ;
            }
            else{
                std::cout << "Err: constDef: Def and Initval dims mismatched"<<std::endl;
                exit(Semantic_ERR);
            }
        }
    }
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
    }
    else{
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
                int product = 1;
                for(int num: *(ctx->dims_ptr)){
                    product *= num;
                }
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
    }
}

//VarDecl/ValDef和ConstDecl/ConstDef逻辑一致
void SemanticAnalysis::enterVarDecl(CACTParser::VarDeclContext *ctx){
    //将后续Def的基本类型传递向btype，&def->type.basety非法
    for (auto def: ctx->varDef()){
        ctx->bType()->passTo.push_back(&(def->basety));
    }
}
void SemanticAnalysis::exitVarDecl(CACTParser::VarDeclContext *ctx){}

void SemanticAnalysis::enterVarDef(CACTParser::VarDefContext *ctx){
    //有初始值时，basety和维度数据自顶向下继承
    if(ctx->constInitVal() != nullptr){
        ctx->constInitVal()->basety = ctx->basety;
        ctx->constInitVal()->dims_ptr = &(ctx->arraydims);
        ctx->constInitVal()->dim_index = 0;
        //最顶层数组，且index为1时允许以平铺列表形式初始化
        ctx->constInitVal()->top = true;
    }
    
    //子节点arrayDims负责填写维度数组
    if(ctx->arrayDims() != nullptr){
        ctx->arrayDims()->dims_ptr = &(ctx->arraydims);
    }
}
void SemanticAnalysis::exitVarDef(CACTParser::VarDefContext *ctx){
    std::string name = ctx->Ident()->getText();
    ctx->name = name;
    
    //检查当前作用域该变量是否声明
    auto iter = (symbol_table.var_table).find((name_scope_t){name,cur_scope});
    if(iter != (symbol_table.var_table).end()){
        std::cout << "Err: varDef: "<<name<<" Redefined" << std::endl;
        exit(Semantic_ERR);
    }
    
    //整合变量类型
    ctx->type = (cact_type_t){false, ctx->basety, ctx->arraydims};
    
    //将该变量加入变量表
    symbol_table.var_table[(name_scope_t){name,cur_scope}] = (var_symbol_item_t){name,ctx->type,cur_scope};

    //检查变量与初始值层级
    if(ctx->constInitVal()!=nullptr){
        //同时考虑非数组左右都应当为0
        if(ctx->arraydims.size() != ctx->constInitVal()->dim_index){
            //只有左边为数组，右侧为元素列表才允许不等
            if((ctx->arraydims.size() != 0) && (ctx->constInitVal()->dim_index==1)){
                ;
            }
            else{
                std::cout << "Err: varDef: Def and Initval dims mismatched"<<std::endl;
                exit(Semantic_ERR);
            }
        }
    }
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
    func_symbol_item_t item = (func_symbol_item_t){name,ret_type,ctx->fparam_list};
    (symbol_table.func_table)[name] = item;

    //检查声明类型与块返回类型一致性
    if(ret_type != ctx->block()->ret_type){
        std::cout << "Err: FuncDef: Func_type mismatched block ret_type" << std::endl;
        exit(Semantic_ERR);
    }
}

void SemanticAnalysis::enterFuncType(CACTParser::FuncTypeContext *ctx){}
void SemanticAnalysis::exitFuncType(CACTParser::FuncTypeContext *ctx){
    ctx->basety = (typeutils.str_to_val)[ctx->getText()];
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
    cact_type_t type = (cact_type_t){false, basety, arrdims};

    //在形参列表中查找是否已定义
    if((*ctx->fparam_list_ptr).find(name) != (*ctx->fparam_list_ptr).end()){
        std::cout<< "Err: FuncFParam: "<<name<<" Redefined" << std::endl;
        exit(Semantic_ERR);
    }

    //未定义则添加
    fparam_item_t item = (fparam_item_t){type,ctx->order};
    (*ctx->fparam_list_ptr)[name] = item;
}

void SemanticAnalysis::enterBlock(CACTParser::BlockContext *ctx){
    //更改当前作用域
    scope_t *new_scope = new scope_t;
    new_scope->parent = cur_scope;
    cur_scope->child_list.push_back(new_scope);
    cur_scope = new_scope;

    //对于函数声明作用域，将形参列表逐一添加到作用域
    if(ctx->fparam_list_ptr != nullptr){
        for(auto iter = (*ctx->fparam_list_ptr).begin(); iter != (*ctx->fparam_list_ptr).end(); iter++){
            std::string name = iter->first;
            fparam_item_t fparam = iter->second;
            var_symbol_item_t item = (var_symbol_item_t){name,fparam.type,cur_scope};
            (symbol_table.var_table)[(name_scope_t){name,cur_scope}] = item;
        }        
    }
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

void SemanticAnalysis::enterStmt_assign(CACTParser::Stmt_assignContext *ctx){}
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
    arrdims_t arrdims;
    cact_expr_ptr expr_ptr(new cact_expr_t{op,BTY_UNKNOWN,subexprs,0,arrdims});
    OperandCheck(expr_ptr);

    //返回类型
    ctx->ret_type = BTY_VOID;
}

void SemanticAnalysis::enterStmt_exp(CACTParser::Stmt_expContext *ctx){}
void SemanticAnalysis::exitStmt_exp(CACTParser::Stmt_expContext *ctx){
    ctx->ret_type = BTY_VOID;
}

void SemanticAnalysis::enterStmt_block(CACTParser::Stmt_blockContext *ctx){
    ctx->block()->fparam_list_ptr = nullptr;
}
void SemanticAnalysis::exitStmt_block(CACTParser::Stmt_blockContext *ctx){
    //当块最后一个节点是子块时，继承其返回类型
    ctx->ret_type = ctx->block()->ret_type;
}

void SemanticAnalysis::enterStmt_if(CACTParser::Stmt_ifContext *ctx){}
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

void SemanticAnalysis::enterStmt_while(CACTParser::Stmt_whileContext *ctx){}
void SemanticAnalysis::exitStmt_while(CACTParser::Stmt_whileContext *ctx){
    //根据简化，如果while语句stmt含有return，则在块最后
    //错误情形，while的stmt返回类型不为VOID
    if(ctx->stmt()->ret_type != BTY_VOID){
        std::cout << "Err: Stmt_While: stmt ret_type must be VOID" << std::endl;
        exit(Semantic_ERR);
    }

    ctx->ret_type = ctx->stmt()->ret_type;
}

void SemanticAnalysis::enterStmt_bcr(CACTParser::Stmt_bcrContext *ctx){}
void SemanticAnalysis::exitStmt_bcr(CACTParser::Stmt_bcrContext *ctx){
    //return exp时由exp类型决定，其余都为VOID
    if(ctx->exp() != nullptr){
        //数组检查
        if(ctx->exp()->self->op == OP_ARRAY){
            std::cout << "Err: Stmt_bcr: stmt ret_type cannot be array" << std::endl;
            exit(Semantic_ERR);
        }
        ctx->ret_type = ctx->exp()->self->basety;
    }
    else{
        ctx->ret_type = BTY_VOID;
    }
}

void SemanticAnalysis::enterExp(CACTParser::ExpContext *ctx){}
void SemanticAnalysis::exitExp(CACTParser::ExpContext *ctx){
    if(ctx->BoolConst() != nullptr){
        //创建self指向的结构体
        cact_op_t op = OP_BASE;
        subexprs_t subexprs;
        arrdims_t arrdims;

        ctx->self.reset(new cact_expr_t{op,BTY_BOOL,subexprs,0,arrdims});
    }
    else{
        ctx->self = ctx->addExp()->self;
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
    }
    if(ctx->BoolConst() != nullptr){
        if(ctx->basety != BTY_BOOL){
            std::cout<<"Err: ConstExp: BoolConst type mismatched" << std::endl;
            exit(Semantic_ERR);
        }
    }
}

void SemanticAnalysis::enterCond(CACTParser::CondContext *ctx){}
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
        subexprs_t subexprs;
        ctx->self.reset(new cact_expr_t{op,iter_type.basety,subexprs,0,iter_type.arrdims});
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
            //类型检查：必须是为终结符int常量
            //该值传递过程中不经历任何操作
            auto expr_ptr = exp_list[i]->self;
            if(expr_ptr->op != OP_BASE || expr_ptr->basety != BTY_INT){
                std::cout << "Err: LVal: expr for dims must be base_int" << std::endl;
                exit(Semantic_ERR);
            }

            //索引，合法范围为0~dim_len-1
            int index = expr_ptr->int_result;
            if(index >= iter_type.arrdims[i]){
                std::cout << "Err: LVal: expr index greater then dim_len" << std::endl;
                exit(Semantic_ERR);
            }
        }

        //建立结构体
        cact_op_t op;
        subexprs_t subexprs;
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
        ctx->self.reset(new cact_expr_t{op,iter_type.basety,subexprs,0,arrdims});
    }

}

void SemanticAnalysis::enterPrimaryExp(CACTParser::PrimaryExpContext *ctx){}
void SemanticAnalysis::exitPrimaryExp(CACTParser::PrimaryExpContext *ctx){
    if(ctx->number()!=nullptr){
        ctx->self = ctx->number()->self;
    }
    else if(ctx->lVal()!=nullptr){
        ctx->self = ctx->lVal()->self;
    }
    else{
        ctx->self = ctx->exp()->self;
    }
}

void SemanticAnalysis::enterNumber(CACTParser::NumberContext *ctx){}
void SemanticAnalysis::exitNumber(CACTParser::NumberContext *ctx){
    cact_op_t op = OP_BASE;
    cact_basety_t basety;
    if(ctx->IntConst() != nullptr){
        basety = BTY_INT;
    }
    if(ctx->FloatConst() != nullptr){
        basety = BTY_FLOAT;
    }
    if(ctx->DoubleConst() != nullptr){
        basety = BTY_DOUBLE;
    }
    subexprs_t subexprs;
    arrdims_t arrdims;
    
    //构造结构体
    ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});
}

void SemanticAnalysis::enterUnaryExp(CACTParser::UnaryExpContext *ctx){}
void SemanticAnalysis::exitUnaryExp(CACTParser::UnaryExpContext *ctx){
    if(ctx->primaryExp()!=nullptr){
        ctx->self = ctx->primaryExp()->self;
    }
    else if(ctx->unaryExp()!=nullptr){
        cact_op_t op = (typeutils.str_to_op)[ctx->unaryOp()->getText()];
        cact_basety_t basety = ctx->unaryExp()->self->basety;
        subexprs_t subexprs;
        subexprs.push_back(ctx->unaryExp()->self);
        //由于不允许对数组操作，arrdims使用空的即可
        arrdims_t arrdims;

        //构造self指向的结构体
        //注：因为数组维度不能经过任何操作，无需为int_result赋值
        ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});

        //针对操作符的操作对象检查
        OperandCheck(ctx->self);
    }
    else{ //func call
        std::string name = ctx->Ident()->getText();
        //检查函数表项是否存在
        auto iter = (symbol_table.func_table).find(name);
        if(iter == (symbol_table.func_table).end()){
            std::cout << "Err: UnaryExp: Called Func" << name << " Undefined" << std::endl;
            exit(Semantic_ERR);
        }
        
        //构造self指向的结构体，类型同变量
        cact_op_t op = OP_ITEM;
        cact_basety_t basety = (iter->second).ret_type;
        subexprs_t subexprs;
        arrdims_t arrdims;
        ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});

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
        else{
            auto exp_list = ctx->funcRParams()->exp();
            //长度检查
            if(exp_list.size() != fparam_len){
                std::cout << "Err: UnaryExp: param_len mismatched" << std::endl;
                exit(Semantic_ERR);
            }
            
            //类型检查
            auto iter = fparam_list.begin();
            for(int i=0;i<fparam_len;i++,iter++){
                auto fparam_type = (iter->second).type;
                auto expr_ptr = exp_list[i]->self;
                //基本类型检查
                if(expr_ptr->basety != fparam_type.basety){
                    std::cout << "Err: UnaryExp: param basety mismatched" << std::endl;
                    exit(Semantic_ERR);
                }

                size_t dim_size = fparam_type.arrdims.size();
                if(dim_size == 0){
                    if(expr_ptr->op == OP_ARRAY){
                        std::cout << "Err: UnaryExp: expr cannot be array when fparam is not" << std::endl;
                        exit(Semantic_ERR);
                    }
                }
                else{
                    //数组及维数检查
                    if((expr_ptr->op != OP_ARRAY) || (expr_ptr->arrdims.size() != dim_size)){
                        std::cout << "Err: UnaryExp: expr must be array with same dims as fparam" << std::endl;
                        exit(Semantic_ERR);
                    }
                    else{
                        //逐维度检查
                        for(int i=0;i<dim_size;i++){
                            if(i==0 && fparam_type.arrdims[i]==0){
                                //首维隐式声明时为0，忽略检查
                                continue;
                            }
                            if(expr_ptr->arrdims[i]!=fparam_type.arrdims[i]){
                                std::cout << "Err: UnaryExp: param dim_len mismatched" << std::endl;
                                exit(Semantic_ERR);
                            }
                        }
                    }
                }
            }
        }

    }
}

void SemanticAnalysis::enterUnaryOp(CACTParser::UnaryOpContext *ctx){}
void SemanticAnalysis::exitUnaryOp(CACTParser::UnaryOpContext *ctx){}

void SemanticAnalysis::enterFuncRParams(CACTParser::FuncRParamsContext *ctx){}
void SemanticAnalysis::exitFuncRParams(CACTParser::FuncRParamsContext *ctx){}

void SemanticAnalysis::enterMulExp(CACTParser::MulExpContext *ctx){}
void SemanticAnalysis::exitMulExp(CACTParser::MulExpContext *ctx){
    if(ctx->mulExp() == nullptr){
        ctx->self = ctx->unaryExp()->self;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[ctx->mulOp()->getText()];
        //如果两个子表达式类型不一致，会在OperandCheck中报错
        cact_basety_t basety = ctx->unaryExp()->self->basety;
        subexprs_t subexprs;
        subexprs.push_back(ctx->mulExp()->self);
        subexprs.push_back(ctx->unaryExp()->self);
        arrdims_t arrdims;
        ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});
        
        //类型检查
        OperandCheck(ctx->self);
    }
}

void SemanticAnalysis::enterMulOp(CACTParser::MulOpContext *ctx){}
void SemanticAnalysis::exitMulOp(CACTParser::MulOpContext *ctx){}

void SemanticAnalysis::enterAddExp(CACTParser::AddExpContext *ctx){}
void SemanticAnalysis::exitAddExp(CACTParser::AddExpContext *ctx){
    if(ctx->addExp() == nullptr){
        ctx->self = ctx->mulExp()->self;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[ctx->addOp()->getText()];
        //如果两个子表达式类型不一致，会在OperandCheck中报错
        cact_basety_t basety = ctx->mulExp()->self->basety;
        subexprs_t subexprs;
        subexprs.push_back(ctx->addExp()->self);
        subexprs.push_back(ctx->mulExp()->self);
        arrdims_t arrdims;
        ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});
        
        //类型检查
        OperandCheck(ctx->self);
    }
}

void SemanticAnalysis::enterAddOp(CACTParser::AddOpContext *ctx){}
void SemanticAnalysis::exitAddOp(CACTParser::AddOpContext *ctx){}

void SemanticAnalysis::enterRelExp(CACTParser::RelExpContext *ctx){}
void SemanticAnalysis::exitRelExp(CACTParser::RelExpContext *ctx){
    if(ctx->BoolConst()!=nullptr){
        //创建self所指结构体
        cact_op_t op = OP_BASE;
        subexprs_t subexprs;
        arrdims_t arrdims;

        ctx->self.reset(new cact_expr_t{op,BTY_BOOL,subexprs,0,arrdims});
    }
    else if(ctx->relExp() == nullptr){
        ctx->self = ctx->addExp()->self;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[ctx->relOp()->getText()];
        //如果两个子表达式类型不一致，会在OperandCheck中报错
        cact_basety_t basety = BTY_BOOL;
        subexprs_t subexprs;
        subexprs.push_back(ctx->relExp()->self);
        subexprs.push_back(ctx->addExp()->self);
        arrdims_t arrdims;

        ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});
        
        //类型检查
        OperandCheck(ctx->self);
    }
}

void SemanticAnalysis::enterRelOp(CACTParser::RelOpContext *ctx){}
void SemanticAnalysis::exitRelOp(CACTParser::RelOpContext *ctx){}

void SemanticAnalysis::enterEqExp(CACTParser::EqExpContext *ctx){}
void SemanticAnalysis::exitEqExp(CACTParser::EqExpContext *ctx){
    if(ctx->eqExp() == nullptr){
        ctx->self = ctx->relExp()->self;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[ctx->eqOp()->getText()];
        //如果两个子表达式类型不一致，会在OperandCheck中报错
        cact_basety_t basety = BTY_BOOL;
        subexprs_t subexprs;
        subexprs.push_back(ctx->eqExp()->self);
        subexprs.push_back(ctx->relExp()->self);
        arrdims_t arrdims;
        
        ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});
        
        //类型检查
        OperandCheck(ctx->self);
    }
}

void SemanticAnalysis::enterEqOp(CACTParser::EqOpContext *ctx){}
void SemanticAnalysis::exitEqOp(CACTParser::EqOpContext *ctx){}

void SemanticAnalysis::enterLAndExp(CACTParser::LAndExpContext *ctx){}
void SemanticAnalysis::exitLAndExp(CACTParser::LAndExpContext *ctx){
    if(ctx->lAndExp() == nullptr){
        ctx->self = ctx->eqExp()->self;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[ctx->AND()->getText()];
        //如果两个子表达式类型不一致，会在OperandCheck中报错
        cact_basety_t basety = BTY_BOOL;
        subexprs_t subexprs;
        subexprs.push_back(ctx->lAndExp()->self);
        subexprs.push_back(ctx->eqExp()->self);
        arrdims_t arrdims;
        
        ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});
        
        //类型检查
        OperandCheck(ctx->self);
    }
}

void SemanticAnalysis::enterLOrExp(CACTParser::LOrExpContext *ctx){}
void SemanticAnalysis::exitLOrExp(CACTParser::LOrExpContext *ctx){
    if(ctx->lOrExp() == nullptr){
        ctx->self = ctx->lAndExp()->self;
    }
    else{
        cact_op_t op = (typeutils.str_to_op)[ctx->OR()->getText()];
        //如果两个子表达式类型不一致，会在OperandCheck中报错
        cact_basety_t basety = BTY_BOOL;
        subexprs_t subexprs;
        subexprs.push_back(ctx->lOrExp()->self);
        subexprs.push_back(ctx->lAndExp()->self);
        arrdims_t arrdims;
        
        ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});
        
        //类型检查
        OperandCheck(ctx->self);
    }
}



void SemanticAnalysis::enterEveryRule(antlr4::ParserRuleContext * ctx){}
void SemanticAnalysis::exitEveryRule(antlr4::ParserRuleContext * ctx){}
void SemanticAnalysis::visitTerminal(antlr4::tree::TerminalNode * node){}
void SemanticAnalysis::visitErrorNode(antlr4::tree::ErrorNode * node){
    std::cout << "Err: Syntax: "<< node->getText() << std::endl;
    exit(Syntax_ERR);
}