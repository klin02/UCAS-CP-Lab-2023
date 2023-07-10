#pragma once 

#include "RiscvGen.h"

#ifdef ASM_gen
void RiscvGen:: asm_optim(){
    std::vector<std::string> vec;
    for(int i=ASM_array.size()-1;i>=0;i--){
        get_vec(ASM_array[i],vec);
        if(vec.size()==3){
            // std::cout << vec[0] << " " << vec[1] << " " << vec[2] << std::endl;
            //可能为lw，进一步考虑
            std::string mv;
            std::string op = vec[0];
            std::string var = vec[1];
            std::string offset = vec[2];
            std::string tar; //寻找目标
            if(op=="fld"){
                tar="fsd";
                mv = "fmv.d";
            }
            else if(op=="flw"){
                tar="fsw";
                mv = "fmv.s";
            }
            else if(op=="lw"){
                tar="sw";
                mv = "mv";
            }
            else if(op=="lb"){
                tar="sb";
                mv = "mv";
            }
            else{
                continue;
            }
            std::set<std::string> def_set;
            for(int j=i-1;j>=0;j--){
                //碰到某些语句不继续查找了
                if(blk_end(ASM_array[j]))
                    break;
                get_vec(ASM_array[j],vec);
                // std::cout << vec[0] << " " << vec[1] << " " << vec[2] << std::endl;
                // std::cout << op << " " << var << " " << offset << std::endl;
                if(vec.size()==3 && vec[0]==tar && def_set.find(vec[1])==def_set.end() && vec[2]==offset){
                    ASM_array[i] = mv+"      "+var+", "+vec[1];
                    break;
                }
                if(vec.size()!=0 && var_def(vec[0]))
                    def_set.insert(vec[1]);
            }
        }
    }
}
void RiscvGen:: get_vec(std::string sm,std::vector<std::string> &vec){
    vec.clear();
    //只考虑给定的命令,load store 以及定值指令（包括load）
    // std::string list[8] = {"fld","flw","lw","lb","fsd","fsw","sw","sb"};
    std::vector<std::string> list = 
        {
            "fld","flw","lw","lb","fsd","fsw","sw","sb",
            "li", "la", "add","addi",
            "fadd.s", "fadd.d", "addw",
            "fsub.s", "fsub.d", "subw",
            "fmul.s", "fmul.d", "mul",
            "fdiv.s", "fdiv.d", "div",
            "fneg.s", "fneg.d", "neg",
            "sll", "sra", "rem", "and", "or",
        };
    int rt_flag = true;
    int op_end = sm.find_first_of(" ");
    std::string sm_op;
    if(op_end == -1)
        return ;
    else{
        sm_op = sm.substr(0,op_end);
        sm=sm.substr(op_end,sm.size()-op_end);
        sm = sm.substr(sm.find_first_not_of(" "));
    }
    for(auto op: list){
        if(sm_op == op){
            rt_flag = false;
            vec.push_back(op);
            break;
        }
    }
    if(rt_flag)
        return ;
    // int first_blk = sm.find_first_of(" ");
    // vec.push_back(sm.substr(0,first_blk));
    // sm = sm.substr(first_blk,sm.size()-first_blk);
    // std::cout<<1;
    // sm = sm.substr(sm.find(" "));
    // std::cout<<2;
    
    // std::cout<<3;
    // sm = sm.substr(no_blk,sm.size()-no_blk);
    int comma = sm.find(",");
    if(comma==-1){
        vec.push_back(sm);
        // std::cout<<4<<std::endl;
    }
    else{
        vec.push_back(sm.substr(0,comma));
        vec.push_back(sm.substr(comma+2,sm.size()-comma-2));
        // std::cout<<4<<std::endl;
    }

}
bool RiscvGen:: blk_end(std::string sm){
    std::vector<std::string> end_list = {":","blt","ble","beq","bne","call"};
    for(auto end: end_list){
        if(sm.find(end)!=-1)
            return true;
    }
    return false;
}
bool RiscvGen:: var_def(std::string op){
    std::vector<std::string> def_list = 
        {
            "fld","flw","lw","lb",
            "li", "la", "add","addi",
            "fadd.s", "fadd.d", "addw",
            "fsub.s", "fsub.d", "subw",
            "fmul.s", "fmul.d", "mul",
            "fdiv.s", "fdiv.d", "div",
            "fneg.s", "fneg.d", "neg",
            "sll", "sra", "rem", "and", "or",
        };
    for(auto def: def_list){
        if(def == op)
            return true;
    }
    return false;
}
void RiscvGen:: stack_initval(std::string initval_str, cact_basety_t basety, int len){
    size_t base_size = (typeutils.basety_to_size)[basety];
    //将初始值字符串拆分
    std::vector<std::string> initval_array;
    //去除前缀
    initval_str = initval_str.substr(1);
    int loc; //第一个逗号位置
    for(int i=0;i<len;i++){
        loc = initval_str.find(',');
        if(i==len-1 && loc==-1){
            //允许最后一个没有，后缀
            initval_array.push_back(initval_str);
        }
        else{
            initval_array.push_back(initval_str.substr(0,loc));
            initval_str = initval_str.substr(loc+1);
        }
    }
    
    //将每个初始值转到对应位置，注意占位符
    size_t zero_size = 0 ;
    for(std::string initval: initval_array){
        if(initval[0] == ARRAY_PLACEHOLDER){
            zero_size += base_size;
        }
        else{
            if(zero_size!=0){
                Const_Stack.push_back(".zero   "+std::to_string(zero_size));
                zero_size = 0;
            }

            //此处用switch case语句会出现crosses initialization
            if(basety == BTY_BOOL){
                Const_Stack.push_back(".byte   " + initval);
            }
            else if(basety == BTY_INT){
                Const_Stack.push_back(".word   " + initval);
            }
            else if(basety == BTY_FLOAT){
                float fval = std::stof(initval);
                int decimal_fval = *(int *)&fval;
                Const_Stack.push_back(".word   " + std::to_string(decimal_fval));
            }
            else if(basety == BTY_DOUBLE){
                double dval = std::stod(initval);
                long long decimal_dval = *(long long *)&dval;
                int hi = decimal_dval >> 32;
                int lo = decimal_dval & 0x00000000ffffffff;
                Const_Stack.push_back(".word   " + std::to_string(lo));
                Const_Stack.push_back(".word   " + std::to_string(hi));
            }
            else{
                std::cout << "Stack Initval: support only bool/int/float/double" << std::endl;
                exit(Code_ERR);
            }
        }
    }
    if(zero_size!=0){
        Const_Stack.push_back(".zero   "+std::to_string(zero_size));
        zero_size = 0;
    }
}

//根据名字将值从栈上转移到寄存器，使用额外寄存器s3,s4
void RiscvGen:: var_to_reg(std::string var_name,std::string reg_name){
    //考虑@x<%1 @x>%1 @x ^x<%1 ^x>%1 ^x %x #1 #2.1f #3.2
    bool is_gvar = var_name[0] == GVAR_PREFIX;
    bool is_lvar = var_name[0] == LVAR_PREFIX;
    bool is_temp = var_name[0] == TEMP_PREFIX;
    bool is_imm = var_name[0] == IMM_PREFIX;
    int addr_infix_loc = var_name.find(ADDR_INFIX);
    int item_infix_loc = var_name.find(ITEM_INFIX);
    bool is_addr = addr_infix_loc != -1;
    bool is_item = item_infix_loc != -1;
    int order;
    //存储偏移的寄存器
    std::string offset_reg = "s3";
    if(is_addr || is_item){
        int loc = is_addr ? addr_infix_loc : item_infix_loc;
        order = std::stoi(var_name.substr(1,loc-1));
        //临时变量名字
        std::string temp_name = var_name.substr(loc+1,var_name.length()-loc-1);
        //临时变量直接存在栈上，没有偏移，不会使用额外寄存器
        var_to_reg(temp_name,offset_reg);
    }
    else{
        order = num_from_name(var_name);
    }
    //使用s3 s4，保证不与其他冲突
    cact_basety_t basety;
    bool is_array; //表示原变量是否array，以区分直接使用名字的情形
    if(is_gvar){
        std::string stack_label = "GVAR" + std::to_string(order);
        basety = semantic_analysis.Gvar_array[order].basety;
        is_array = semantic_analysis.Gvar_array[order].length != 1;
        //is_array 三种表示示例 reg_name = t0/ft0 offset_reg = s3
        //self: la t0, GVAR0
        //addr: la s4, GVAR0
        //      add t0, s4, s3
        //item: la s4, GVAR0
        //      add s4, s4, s3
        //      flw ft0, 0(s4)

        //not array 表示示例
        //la s4, GVAR0
        //flw ft0, 0(s4)

        //提取公共部分，节约代码
        if(is_array && !(is_addr || is_item)){
            ASM_array.push_back("la      "+reg_name+", "+stack_label);
        }
        else{
            ASM_array.push_back("la      s4, "+stack_label);
            if(is_array && is_addr){
                ASM_array.push_back("add     "+reg_name+", s4, s3");
            }
            else{
                if(is_array && is_item){
                    ASM_array.push_back("add     s4, s4, s3");
                }
                //全局变量没有PTR
                std::string op = basety == BTY_DOUBLE ? "fld" : 
                                 basety == BTY_FLOAT  ? "flw" : 
                                 basety == BTY_INT    ? "lw"  :
                                 basety == BTY_BOOL   ? "lb"  : "";
                ASM_array.push_back(op+"     "+reg_name+", 0(s4)");
            }
        }
    }
    else if(is_lvar){
        basety = semantic_analysis.Lvar_array[order].basety;
        bool is_ptr = basety == BTY_INT_PTR || basety == BTY_BOOL_PTR || 
                      basety == BTY_FLOAT_PTR || basety == BTY_DOUBLE_PTR;
        is_array = semantic_analysis.Lvar_array[order].length != 1;
        //表示示例 栈中偏移为20,offset_reg = s3
        //is_ptr 
        //self: ld t0, -20(s0)
        //addr: ld s4, -20(s0)
        //      addi t0, s4, s3
        //item: ld s4, -20(s0)
        //      add s4, s4, s3
        //      flw ft0, 0(s3)
        
        //is_array: (addr和item做了顺序调换来节约指令)
        //self: addi t0, s0, -20
        //addr: add s4, s0, s3
        //      addi t0, s4, -20
        //item: add s4, s0, s3
        //      flw ft0, -20(s4)
        
        //元素:
        //flw ft0, -20(s0)
        std::string stack_offset = "-"+std::to_string(semantic_analysis.Lvar_array[order].offset);
        std::string op = basety == BTY_DOUBLE || basety == BTY_DOUBLE_PTR ? "fld" : 
                         basety == BTY_FLOAT  || basety == BTY_FLOAT_PTR ? "flw" : 
                         basety == BTY_INT    || basety == BTY_INT_PTR ? "lw"  :
                         basety == BTY_BOOL   || basety == BTY_BOOL_PTR ? "lb"  : "";
        if(is_ptr){
            if(is_addr){
                ASM_array.push_back("ld      s4, "+stack_offset+"(s0)");
                ASM_array.push_back("addi    "+reg_name+", s4, s3");
            }
            else if(is_item){
                ASM_array.push_back("ld      s4, "+stack_offset+"(s0)");
                ASM_array.push_back("add     s4, s4, s3");
                ASM_array.push_back(op+"     "+reg_name+", 0(s4)");
            }
            else{
                ASM_array.push_back("ld      "+reg_name+", "+stack_offset+"(s0)");
            }
        }
        else if(is_array){
            if(is_addr){
                ASM_array.push_back("add     s4, s0, s3");
                ASM_array.push_back("addi    "+reg_name+", s4, "+stack_offset);
            }
            else if(is_item){
                ASM_array.push_back("add     s4, s0, s3");
                ASM_array.push_back(op+"     "+reg_name+", "+stack_offset+"(s4)");
            }
            else{
                ASM_array.push_back("addi    "+reg_name+", "+stack_offset);
            }
        }
        else{//元素
            ASM_array.push_back(op+"     "+reg_name+", "+stack_offset+"(s0)");
        }
    }
    else if(is_temp){
        //flw ft0, -20(s0)
        basety = semantic_analysis.Temp_array[order].basety;
        std::string stack_offset = "-" + std::to_string(semantic_analysis.Temp_array[order].offset);
        //临时变量没有PTR
        std::string op = basety == BTY_DOUBLE ? "fld" : 
                         basety == BTY_FLOAT  ? "flw" : 
                         basety == BTY_INT    ? "lw"  :
                         basety == BTY_BOOL   ? "lb"  : "";
        ASM_array.push_back(op+"     "+reg_name+", "+stack_offset+"(s0)");
    }
    else if(is_imm){
        bool has_prefd = var_name.find(".")!=-1 || var_name.find("E")!=-1 || var_name.find("e")!=-1;
        bool is_float = has_prefd && (var_name.find("f") != -1 || var_name.find("F")!=-1);
        bool is_double = has_prefd && !is_float;
        if(is_float || is_double){
            std::string stack_label = "IMM" + std::to_string(imm_cnt);
            //常量声明
            Const_Stack.push_back(".section    .rodata");
            std::string align = is_float ? "2" : "3";
            Const_Stack.push_back(".align  "+align);
            Const_Stack.push_back(stack_label+":");
            cact_basety_t basety = is_float ? BTY_FLOAT : BTY_DOUBLE;
            stack_initval(var_name,basety,1);
            //主体代码
            ASM_array.push_back("la   s4, "+stack_label+")");
            std::string op = is_float ? "flw" : "fld";
            ASM_array.push_back(op+"     "+reg_name+", 0(s4)");
        }
        else{ //int bool
            std::string valstr = var_name.substr(1);
            ASM_array.push_back("li      "+reg_name+", "+valstr);
        }
    }
    else{
        std::cout << "Var To Reg: support only gvar/lvar/temp/imm, but get " << var_name << std::endl;
        exit(Code_ERR);
    }
}

//根据名字将值从寄存器转移到栈上，使用额外寄存器s5 s6
void RiscvGen:: reg_to_var(std::string var_name,std::string reg_name){
    //var_name可以形似@x<%1 @x ^x<%1 ^x %1 原变量类型可能为array/ptr/other，偏移后变量可能为item/self，不可能为addr（不允许指针操作）
    bool is_gvar = var_name[0] == GVAR_PREFIX;
    bool is_lvar = var_name[0] == LVAR_PREFIX;
    bool is_temp = var_name[0] == TEMP_PREFIX;
    int item_infix_loc = var_name.find(ITEM_INFIX);
    bool is_item = item_infix_loc != -1;

    int order;
    std::string offset_reg = "s5";
    if(is_item){
        order = std::stoi(var_name.substr(1,item_infix_loc-1));
        std::string temp_name = var_name.substr(item_infix_loc+1,var_name.length()-item_infix_loc-1);
        var_to_reg(temp_name,offset_reg);
    }
    else{
        order = std::stoi(var_name.substr(1));
    }

    //store部分示例：使用的额外寄存器 s5 s6/fs6
    //考虑到is_array.self和other的情况相同，在lvar对ptr特别区分即可
    //is_gvar: offset_reg = s5 reg_name = fs7
    //self: la s6, GVAR0
    //      fsw fs7, 0(s6)
    //item: la s6, GVAR0
    //      add s6, s6, s5
    //      fsw fs7, 0(s6)

    //is_lvar: stack_offset=20 offset_reg=s5
    //is_array:
    //self: fsw fs7, -20(s0)
    //item: add s6, s0, s5
    //      fsw fs7, -20(s6)
    //is_ptr:
    //self: fsw fs7, -20(s0)
    //item: ld s6, -20(s0)
    //      add s6, s6, s5
    //      fsw fs7, 0(s6)

    //is_temp:
    //self: fsw fs7, -20(s0)

    cact_basety_t basety;
    if(is_gvar){
        basety = semantic_analysis.Gvar_array[order].basety;
        std::string op = basety == BTY_DOUBLE ? "fsd" :
                         basety == BTY_FLOAT  ? "fsw" :
                         basety == BTY_INT    ? "sw"  :
                         basety == BTY_BOOL   ? "sb"  : "" ;
        std::string stack_label = "GVAR"+std::to_string(order);
        ASM_array.push_back("la      s6, "+stack_label);
        if(is_item){
            ASM_array.push_back("add     s6, s6, s5");
        }
        ASM_array.push_back(op+"     "+reg_name+", 0(s6)");
    }
    else if(is_lvar){
        //存储到某个局部变量，情形可能为^2<%3 这里^2可能为指针类型
        basety = semantic_analysis.Lvar_array[order].basety;
        std::string op = basety == BTY_DOUBLE || basety == BTY_DOUBLE_PTR ? "fsd" :
                         basety == BTY_FLOAT  || basety == BTY_FLOAT_PTR  ? "fsw" :
                         basety == BTY_INT    || basety == BTY_INT_PTR    ? "sw"  :
                         basety == BTY_BOOL   || basety == BTY_BOOL_PTR   ? "sb"  : "" ;
        std::string stack_offset = "-"+std::to_string(semantic_analysis.Lvar_array[order].offset);
        bool is_ptr = basety == BTY_DOUBLE_PTR || basety == BTY_FLOAT_PTR || basety == BTY_INT_PTR || basety == BTY_BOOL_PTR ;
        //item: ld s6, -20(s0)
        //      add s6, s6, s5
        //      fsw fs7, 0(s6)
        if(is_item){
            if(is_ptr){
                ASM_array.push_back("ld      s6, "+stack_offset+"(s0)");
                ASM_array.push_back("add     s6, s6, s5");
                ASM_array.push_back(op+"     "+reg_name+", 0(s6)");
            }
            else{
                ASM_array.push_back("add     s6, s0, s5");
                ASM_array.push_back(op+"     "+reg_name+", "+stack_offset+"(s6)");
            }
        }
        else{
            ASM_array.push_back(op+"     "+reg_name+", "+stack_offset+"(s0)");
        }
    }
    else if(is_temp){
        basety = semantic_analysis.Temp_array[order].basety;
        std::string op = basety == BTY_DOUBLE ? "fsd" :
                         basety == BTY_FLOAT  ? "fsw" :
                         basety == BTY_INT    ? "sw"  :
                         basety == BTY_BOOL   ? "sb"  : "" ;
        std::string stack_offset = "-"+std::to_string(semantic_analysis.Temp_array[order].offset);
        ASM_array.push_back(op+"     "+reg_name+", "+stack_offset+"(s0)");
    }
    else{
        std::cout << "Reg to Var : support only gvar/lvar/temp, but get "<< var_name << std::endl;
        exit(Code_ERR);
    }
}

void RiscvGen:: Gen_All(std::string asm_name){
    //添加开头信息
    ASM_array.push_back(".file   \"" + asm_name + ".cact\"");
    ASM_array.push_back(".option nopic");
    ASM_array.push_back(".attribute arch, \"rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0\"");
    ASM_array.push_back(".attribute unaligned_access, 0");
    ASM_array.push_back(".attribute stack_align, 16");

    bool rescan = false; //false时，除Galloc均跳过
    int rescan_loc; //重新开始扫描的位置，当func_end将rescan由false变为true时跳回
    for(int i=0;i<ir_optim.IRC_array.size();i++){
        IR_code_t irc = ir_optim.IRC_array[i];
        if(rescan){
            switch(irc.IRop){
                case IR_G_ALLOC:
                    std::cout << "Rescan exclues G_Alloc " << i << std::endl;
                    exit(Code_ERR);
                    break;
                case IR_L_ALLOC:
                    Gen_L_Alloc(irc);
                    break;
                case IR_LABEL:
                    Gen_Label(irc);
                    break;
                case IR_FUNC_BEGIN:
                    Gen_FuncBegin(irc);
                    break;
                case IR_FUNC_END:
                    Gen_FuncEnd(irc);
                    rescan = false; //表示rescan结束
                    break;
                case IR_PARAM:
                    Gen_Param(irc);
                    break;
                case IR_CALL:
                    Gen_Call(irc);
                    break;
                case IR_RETURN:
                    Gen_Return(irc);
                    break;
                case IR_ASSIGN:
                    Gen_Assign(irc);
                    break;
                case IR_ADD: case IR_SUB: case IR_MUL: case IR_DIV: 
                case IR_SLL: case IR_SRA:
                case IR_MOD: case IR_AND: case IR_OR: 
                case IR_NEG: case IR_NOT:
                    Gen_Operation(irc);
                    break;
                case IR_BEQ: case IR_BNE: case IR_BLT: case IR_BGT: 
                case IR_BLE: case IR_BGE:
                    Gen_Branch(irc);
                    break;
                case IR_J:
                    Gen_Jump(irc);
                    break;
                default:
                    std::cout << "Unexpected IRop: "<< irc.IRop <<" in Rescan" <<std::endl;
                    exit(Code_ERR);
                    break;    
            }
        }
        else{
            switch(irc.IRop){
                case IR_G_ALLOC:
                    Gen_G_Alloc(irc);
                    break;
                case IR_L_ALLOC:
                    Cnt_Temp_Lvar(irc.result);
                    break;
                case IR_FUNC_BEGIN:
                    frame_size = 16; //重新开始统计，开始包含了ra+sp 8+8
                    Cnt_FuncParam(irc.result);
                    rescan_loc = i; //表示跳回位置
                    break;
                case IR_FUNC_END:
                    //对栈帧向上对齐到16倍数处理
                    frame_size = up_to_align(frame_size,16);
                    //从Func_Begin开始重新扫描
                    rescan = true;
                    //考虑后续执行i++，跳回到前一个位置
                    i = rescan_loc-1;
                    break;
                default:
                    break;
            }
        }
    }

    if(OPTIM_LEVEL !=0)
        asm_optim();
    //结尾将全部信息输入到文件
    std::ofstream outfile;
    outfile.open(asm_name);
    for(auto ASM: ASM_array){
        //除了标号和文件名，其他(无冒号)后移一个缩进
        if(ASM.find(':')==-1){
            outfile << '\t';
        }
        outfile << ASM <<std::endl;
    }
    //打印常量部分
    for(auto constant: Const_Stack){
        if(constant.find(':')==-1){
            outfile << '\t';
        }
        outfile << constant << std::endl;
    }
    outfile.close();
}

void RiscvGen:: Gen_Label(IR_code_t &irc){
    ASM_array.push_back(irc.result+":");
}
void RiscvGen:: Gen_FuncBegin(IR_code_t &irc){
    auto func_name = irc.result;
    //开头信息
    ASM_array.push_back("");
    ASM_array.push_back(".text");
    ASM_array.push_back(".align   1");
    ASM_array.push_back(".globl   " + func_name);
    ASM_array.push_back(".type    " + func_name + ", @function");
    ASM_array.push_back(func_name + ":");

    //开辟栈帧及相关准备
    ASM_array.push_back("addi    sp, sp, -" + std::to_string(frame_size));
    ASM_array.push_back("sd      ra, " + std::to_string(frame_size-8) + "(sp)");
    ASM_array.push_back("sd      s0, " + std::to_string(frame_size-16) + "(sp)");
    ASM_array.push_back("addi    s0, sp, " + std::to_string(frame_size));

    //将函数形参从寄存器转移到栈上，当前只考虑a0-a7,fa0-fa7
    auto iter = (symbol_table.func_table).find(func_name);
    int icnt = 0;
    int fcnt = 0;
    for(auto fparam: (iter->second).fparam_list){
        std::string IR_name = fparam.IR_name;
        int order = num_from_name(IR_name);
        cact_basety_t basety = semantic_analysis.Lvar_array[order].basety;
        std::string suffix =    (basety == BTY_FLOAT || basety == BTY_INT) ? "w" :
                                (basety == BTY_BOOL) ? "b" : 
                                "d"; //double及各种指针
        std::string op;
        std::string reg;
        if(basety == BTY_FLOAT || basety == BTY_DOUBLE){
            op = "fs"+suffix;
            reg = "fa" + std::to_string(fcnt);
            fcnt++;
        }
        else{
            op = "s"+suffix;
            reg = "a" + std::to_string(icnt);
            icnt++;
        }
        std::string offset = std::to_string(semantic_analysis.Lvar_array[order].offset);
        //e.g. sb a0, -20(s0)  fsw fa0, -24(s0)
        ASM_array.push_back(op+"      "+reg+", "+"-"+offset+"(s0)");
    }
    if(icnt>=8 || fcnt>=8){
        std::cout << "ASM: support i_arg and f_arg less then 8" << std::endl;
        exit(Code_ERR);
    }

}
void RiscvGen:: Gen_FuncEnd(IR_code_t &irc){
    //恢复ra s0 栈帧 跳回位置
    std::string func_name = irc.result;
    ASM_array.push_back("ld      ra, " + std::to_string(frame_size-8) + "(sp)");
    ASM_array.push_back("ld      s0, " + std::to_string(frame_size-16) + "(sp)");
    ASM_array.push_back("addi    sp, sp, " + std::to_string(frame_size));
    ASM_array.push_back("jr      ra");
    ASM_array.push_back(".size   " + func_name + ", .-" + func_name);
}
void RiscvGen:: Gen_Param(IR_code_t &irc){
    //将传递的参数从栈上转移到寄存器
    cact_basety_t basety = irc.basety;
    std::string reg_name; //用于传参的寄存器
    if(basety == BTY_FLOAT || basety == BTY_DOUBLE){
        reg_name = "fa" + std::to_string(fparam_order);
        fparam_order ++;
    }
    else{ //包含各类指针
        reg_name = "a" + std::to_string(iparam_order);
        iparam_order ++;
    }
    std::string var_name = irc.result;
    var_to_reg(var_name,reg_name);
}
void RiscvGen:: Gen_Call(IR_code_t &irc){
    //传参结束，清空计数
    iparam_order = 0;
    fparam_order = 0;

    std::string func_name = irc.result;
    ASM_array.push_back("call    "+func_name);
    ASM_array.push_back("nop");

    cact_basety_t basety = irc.basety;
    std::string IR_temp = irc.arg1;
    if(IR_temp.length()!=0){
        std::string reg = (basety == BTY_FLOAT || basety == BTY_DOUBLE) ? "fa0" : "a0";
        std::string op = (basety == BTY_DOUBLE) ? "fsd" :
                         (basety == BTY_FLOAT) ? "fsw" :
                         (basety == BTY_BOOL) ? "sb" : 
                         "sw";
        int order = num_from_name(IR_temp);
        std::string offset = std::to_string(semantic_analysis.Temp_array[order].offset);
        ASM_array.push_back(op+"     "+reg+", -"+offset+"(s0)");
    }
}
void RiscvGen:: Gen_Return(IR_code_t &irc){
    //针对返回值非void的才执行Return
    cact_basety_t basety = irc.basety;
    std::string reg_name = (basety == BTY_FLOAT || basety == BTY_DOUBLE) ? "fa0" : "a0";
    std::string var_name = irc.result;
    var_to_reg(var_name,reg_name);
}

void RiscvGen:: Gen_Assign(IR_code_t &irc){
    //result可以形似@x<%1 @x ^x<%1 ^x 不为数组，数组用Alloc赋值
    std::string result = irc.result;
    std::string var_name = irc.arg1;
    cact_basety_t basety = irc.basety;
    //指定中间寄存器
    std::string reg_name;
    if(basety == BTY_FLOAT || basety == BTY_DOUBLE){
        reg_name = "fs7";
    }
    else{
        reg_name = "s7";
    }
    //右侧结果由栈到寄存器
    var_to_reg(var_name,reg_name);
    //左侧赋值由寄存器到栈
    reg_to_var(result,reg_name);

}
void RiscvGen:: Gen_Operation(IR_code_t &irc){
    std::string reg0,reg1,reg2;
    std::string op;
    bool is_float = irc.basety == BTY_FLOAT;
    bool is_double = irc.basety == BTY_DOUBLE;
    bool is_unary = irc.IRop == IR_NEG || irc.IRop == IR_NOT;
    if(is_float || is_double){
        reg0 = "ft0";
        reg1 = "ft1";
        reg2 = "ft2";
    }
    else{
        reg0 = "t0";
        reg1 = "t1";
        reg2 = "t2";
    }
    //neg系列和not都是伪代码
    switch(irc.IRop){
        case IR_ADD: op = is_float ? "fadd.s" : is_double ? "fadd.d" : "addw"; break;
        case IR_SUB: op = is_float ? "fsub.s" : is_double ? "fsub.d" : "subw"; break;
        case IR_MUL: op = is_float ? "fmul.s" : is_double ? "fmul.d" : "mul" ; break;
        case IR_DIV: op = is_float ? "fdiv.s" : is_double ? "fdiv.d" : "div" ; break;
        case IR_SLL: op = "sll"; break;
        case IR_SRA: op = "sra"; break;
        case IR_MOD: op = "rem"; break;
        case IR_AND: op = "and"; break;
        case IR_OR:  op = "or" ; break;
        // case IR_NOT: op = "not"; break;
        case IR_NEG: op = is_float ? "fneg.s" : is_double ? "fneg.d" : "neg"; break;
        default: break;
    }
    var_to_reg(irc.arg1,reg1);
    if(is_unary){
        if(irc.IRop==IR_NOT){
            //NOT原伪代码是所有位取反，xori rd,rs,-1，此处只希望对最后一位取反
            ASM_array.push_back("xori    "+reg0+", "+reg1+", 1");
        }
        else{
            ASM_array.push_back(op+"     "+reg0+", "+reg1);
        }
    }
    else{
        var_to_reg(irc.arg2,reg2);
        ASM_array.push_back(op+"     "+reg0+", "+reg1+", "+reg2);
    }
    reg_to_var(irc.result,reg0);
}

void RiscvGen:: Gen_Branch(IR_code_t &irc){
    // case IR_BEQ: case IR_BNE: case IR_BLT: case IR_BGT: 
    // case IR_BLE: case IR_BGE:
    std::string label, reg1, reg2;
    std::string op;
    //翻转两个操作数以适配riscv的api，操作也需要相应更改
    bool reverse = false;
    bool is_float = irc.basety == BTY_FLOAT;
    bool is_double = irc.basety == BTY_DOUBLE;
    label = irc.result;
    if(is_float || is_double){
        reg1 = "ft3";
        reg2 = "ft4";
    }
    else{
        reg1 = "t3";
        reg2 = "t4";
    }
    var_to_reg(irc.arg1,reg1);
    var_to_reg(irc.arg2,reg2);
    //BGT和BGE交换寄存器顺序后使用BLE和BLT代替，
    //BRANCH指令没有浮点版本，需要先使用浮点比较再BNEZ
    //浮点指令没有不等比较，需要结合feq做调整
    switch(irc.IRop){
        case IR_BEQ: op = is_float ? "feq.s" : is_double ? "feq.d" : "beq" ; break;
        case IR_BNE: op = is_float ? "feq.s" : is_double ? "feq.d" : "bne" ; break;
        case IR_BLT: op = is_float ? "flt.s" : is_double ? "flt.d" : "blt" ; break;
        case IR_BLE: op = is_float ? "fle.s" : is_double ? "fle.d" : "ble" ; break;
        case IR_BGT: op = is_float ? "flt.s" : is_double ? "flt.d" : "blt" ; reverse = true; break;
        case IR_BGE: op = is_float ? "fle.s" : is_double ? "fle.d" : "ble" ; reverse = true; break;
        default: break;
    }
    if(is_float || is_double){
        //需要额外的临时寄存器t5存储比较结果
        //例如: bgt-> fle.s t5, reg2, reg1   bnez t5, label
        //特别考虑bne-> feq.s t5, reg2, reg1  beqz t5, label
        if(reverse){
            ASM_array.push_back(op+"     t5, "+reg2+", "+reg1);
        }
        else{
            ASM_array.push_back(op+"     t5, "+reg1+", "+reg2);
        }
        if(irc.IRop==IR_BNE){
            ASM_array.push_back("beqz    t5, "+label);
        }
        else{
            ASM_array.push_back("bnez    t5, "+label);
        }
    }
    else{
        //例如：bgt-> ble reg2, reg1, label
        if(reverse){
            ASM_array.push_back(op+"     "+reg2+", "+reg1+", "+label);
        }
        else{
            ASM_array.push_back(op+"     "+reg1+", "+reg2+", "+label);
        }
    }
}
void RiscvGen:: Gen_Jump(IR_code_t &irc){
    ASM_array.push_back("j       "+irc.result);
}
void RiscvGen:: Gen_G_Alloc(IR_code_t &irc){
    std::string name = irc.result;
    cact_basety_t basety = irc.basety;
    std::string initval_str = irc.arg1;
    int order = num_from_name(name);
    std::string stack_label = "GVAR"+std::to_string(order);
    bool is_const = semantic_analysis.Gvar_array[order].is_const;
    bool is_inited = initval_str.size()!=0;
    size_t base_size = (typeutils.basety_to_size)[basety];
    int len = semantic_analysis.Gvar_array[order].length;
    //分区信息
    std::string sec_str =   is_const ? ".rodata" :
                            is_inited ? ".data" :
                            ".bss";
    //汇编语言中，数组都按照8字节对齐。对bool类型单个变量，不用给出align
    std::string align_str = (len != 1) ? ".align  3" : 
                            (basety == BTY_DOUBLE)  ? ".align  3" :
                            (basety != BTY_BOOL)    ? ".align  2" :
                            "";

    Const_Stack.push_back("");
    Const_Stack.push_back(".globl  "+stack_label);
    Const_Stack.push_back(sec_str);
    if(align_str.length()!=0){ //单个bool不用align
        Const_Stack.push_back(align_str);
    }
    Const_Stack.push_back(".type   " + stack_label + ", @object");
    Const_Stack.push_back(".size   " + stack_label + ", " + std::to_string(base_size*len));
    Const_Stack.push_back(stack_label + ":");

    if(is_inited){
        stack_initval(initval_str,basety,len);
    }
    else{
        Const_Stack.push_back(".zero   "+std::to_string(base_size*len));
    }
}
//使用额外寄存器s1/fs1,s2/fs2
void RiscvGen:: Gen_L_Alloc(IR_code_t &irc){
    //为temp和localvar准备
    //temp不需要初始化，已经在Cnt安排了相应位置
    //localvar只有初始化才需要生成代码
    std::string IR_name = irc.result;
    cact_basety_t basety = irc.basety;
    std::string initval_str = irc.arg1;
    bool is_inited = initval_str.size()!=0;
    bool is_lvar = IR_name[0] == LVAR_PREFIX;
    if(!is_lvar || !is_inited){
        return;
    }
    size_t base_size = (typeutils.basety_to_size)[basety];
    int order = num_from_name(IR_name);
    int len = semantic_analysis.Lvar_array[order].length;
    int offset = semantic_analysis.Lvar_array[order].offset;

    //声明和获取的label
    std::string stack_label = "LVAR" + std::to_string(order);
    
    //常量声明
    Const_Stack.push_back("");
    Const_Stack.push_back(".section    .rodata");
    if(len>1){
        //对数组，均使用标号初始化
        Const_Stack.push_back(".align  3");
        Const_Stack.push_back(stack_label+":");
        stack_initval(initval_str,basety,len);
    }
    else{
        //对浮点的单个常量，也需要给出标号
        if(basety == BTY_FLOAT || basety == BTY_DOUBLE){
            std::string align = (basety==BTY_FLOAT) ? "3" : "2";
            Const_Stack.push_back(".align  "+align);
            Const_Stack.push_back(stack_label+":");
            stack_initval(initval_str,basety,len);
        }
    }

    //主体代码，将值从标号转移到栈上
    if(len > 1){
        //将地址存到寄存器s2
        ASM_array.push_back("la      s2, " + stack_label);
        //从标号转移多少个byte
        int total_size = base_size * len;
        int done_size = 0; //已经转移的字节数
        int left_size = 0; //剩余待转移的字节数
        int shift_size; //本次能够转移的字节数 1/2/4/8
        std::string suffix; //本次转移对应后缀 b/h/w/d
        //前缀，是否使用浮点寄存器
        std::string prefix = (basety == BTY_FLOAT || basety == BTY_DOUBLE) ? "f" : ""; 
        while(done_size < total_size){
            left_size = total_size - done_size;
            if(left_size >= 8){
                shift_size = 8;
                suffix = "d";
            }
            else if(left_size >= 4){
                shift_size = 4;
                suffix = "w";                
            }
            else if(left_size >= 2){
                shift_size = 2;
                suffix = "h";
            }
            else{
                shift_size = 1;
                suffix = "b";
            }
            ASM_array.push_back(prefix+"l"+suffix+"      "+prefix+"s1, "+std::to_string(done_size)+"(s2)");
            ASM_array.push_back(prefix+"s"+suffix+"      "+prefix+"s1, -"+std::to_string(offset-done_size)+"(s0)");
            done_size += shift_size;
        }
    }
    else{
        if(basety == BTY_BOOL || basety == BTY_INT){
            std::string store = (basety == BTY_BOOL) ? "sb" : "sw";
            int loc = initval_str.find(',');
            std::string initval = initval_str.substr(1,loc-1);
            ASM_array.push_back("li      s1, "+initval);
            ASM_array.push_back(store+"      s1, -"+std::to_string(offset)+"(s0)");
        }
        else{
            std::string suffix = (basety == BTY_FLOAT) ? "w" : "d";
            ASM_array.push_back("la      s2, " + stack_label);
            ASM_array.push_back("fl"+suffix+"     fs1, 0(s2)");
            ASM_array.push_back("fs"+suffix+"     fs1, -"+std::to_string(offset)+"(s0)");
        }
    }
}

//根据函数名，计算形参占用栈帧，并将位置写入对应局部变量
void RiscvGen:: Cnt_FuncParam(std::string func_name){
    auto iter = (symbol_table.func_table).find(func_name);
    for(auto fparam: (iter->second).fparam_list){
        std::string IR_name = fparam.IR_name;
        int order = num_from_name(IR_name);
        cact_basety_t basety = semantic_analysis.Lvar_array[order].basety;
        size_t size = (typeutils.basety_to_size)[basety];
        frame_size = up_to_align(frame_size,size);
        frame_size += size;
        semantic_analysis.Lvar_array[order].offset = frame_size;
    }
}
void RiscvGen:: Cnt_Temp_Lvar(std::string var_name){
    //区分temp和lvar
    bool is_temp = var_name[0] == TEMP_PREFIX;
    int order = num_from_name(var_name);
    cact_basety_t basety;
    int len;
    if(is_temp){
        //临时变量长度都只有1
        basety = semantic_analysis.Temp_array[order].basety;
        len = semantic_analysis.Temp_array[order].length;
    }
    else{//lvar 局部变量
        basety = semantic_analysis.Lvar_array[order].basety;
        len = semantic_analysis.Lvar_array[order].basety;
    }
    //这里设计bool使用1byte
    size_t size = (typeutils.basety_to_size)[basety];
    //对齐到size大小
    frame_size = up_to_align(frame_size,size);
    size *= len;
    frame_size += size;
    if(is_temp){
        semantic_analysis.Temp_array[order].offset = frame_size;
    }
    else{
        semantic_analysis.Lvar_array[order].offset = frame_size;
    }
}
#endif