#pragma once 

#ifdef ASM_gen

#include "RiscvGen.h"

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
                zero_size == 0;
            }
            switch(basety){
                case BTY_BOOL:
                    Const_Stack.push_back(".byte   " + initval);
                    break;
                case BTY_INT:
                    Const_Stack.push_back(".word   " + initval);
                    break;
                case BTY_FLOAT:
                    float fval = std::stof(initval);
                    int decimal_fval = *(int *)&fval;
                    Const_Stack.push_back(".word   " + std::to_string(decimal_fval));
                    break;
                case BTY_DOUBLE:
                    double dval = std::stod(initval);
                    long long decimal_dval = *(long long *)&dvalue;
                    int hi = decimal_dval >> 32;
                    int lo = decimal_dval & 0x00000000ffffffff;
                    Const_Stack.push_back(".word   " + std::to_string(lo));
                    Const_Stack.push_back(".word   " + std::to_string(hi));
                    break;
                default:
                    break;
            }
        }
    }
    if(zero_size!=0){
        Const_Stack.push_back(".zero   "+std::to_string(zero_size));
        zero_size == 0;
    }
}

//根据名字将值写到寄存器
void RiscvGen:: var_to_reg(std::string var_name,std::string reg_name){
    //考虑@x<y @x>y @x ^x<y ^x>y ^x %x #1 #2.1f #3.2
    bool is_gvar = var_name[0] == GVAR_PREFIX;
    bool is_lvar = var_name[0] == LVAR_PREFIX;
    bool is_temp = var_name[0] == TEMP_PREFIX;
    int addr_infix_loc = var_name.find(ADDR_INFIX);
    int item_infix_loc = var_name.find(ITEM_INFIX);
    bool is_addr = addr_infix_loc != -1;
    bool is_item = item_infix_loc != -1;
    int order;
    int offset;
    if(is_addr || is_item){
        int loc = is_addr ? addr_infix_loc : item_infix_loc;
        order = std::stoi(var_name.substr(1,loc-1));
        //临时变量名字
        int temp_order = std::stoi(var_name.substr(loc+2,var_name.length()-loc-2));
        offset = tempary
    }
    else{
        order = num_from_name(var_name);
        offset = 0;
    }
    //使用s3以上，保证不与其他冲突
    cact_basety_t basety;
    size_t base_size;
    bool is_array; //表示原变量是否array，以区分直接使用名字的情形
    if(is_gvar){
        std::string stack_label = "GVAR" + std::to_string(order);
        basety = Gvar_array[order].basety;
        base_size = (typeutils.basety_to_size)[basety];
        is_array = Gvar_array[order].length != 1;
        //is_array 三种表示示例 reg_name = t0/ft0 相对偏移为5*4
        //self: lui s3, %hi(GVAR0)
        //      addi t0, t3, %hi(GVAR0)
        //addr：lui s3, %hi(GVAR0+20)
        //      addi t0, s3, %hi(GVAR0+20)
        //item：lui s3, %hi(GVAR0+20)
        //      flw  ft0, %hi(GVAR0+20)(s3)
        //not array 表示示例
        //lui s3, %hi(GVAR0)
        //flw ft0, %hi(GVAR0)(s3)
        std::string byte_offset = is_array && (is_addr || is_item) ? "+" + std::to_string(base_size*offset) 
                                    : "";
        ASM_array.push_back("lui     s3, %hi("+stack_label+byte_offset+")");
        if(is_array && !is_item){
            ASM_array.push_back("addi    "+reg_name+", s3, %hi("+stack_label+byte_offset+")");
        }
        else{
            //全局变量没有PTR
            std::string op = basety == BTY_DOUBLE ? "fld" : 
                             basety == BTY_FLOAT  ? "flw" : 
                             basety == BTY_INT    ? "lw"  :
                             basety == BTY_BOOL   ? "lb"  : "";
            ASM_array.push_back(op+"     "+reg_name+", %hi("+stack_label+byte_offset+")(s3)");
        }
    }
    else if(is_lvar){
        basety = Lvar_array[order].basety;
        base_size = (typeutils.basety_to_size)[basety];
        bool is_ptr = basety == BTY_INT_PTR || basety == BTY_BOOL_PTR || 
                      basety == BTY_FLOAT_PTR || basety == BTY_DOUBLE_PTR;
        is_array = Lvar_array[order].length != 1;
        //表示示例 栈中偏移为20,相对偏移为3*4
        //is_ptr 
        //self: ld t0, -20(s0)
        //addr: ld s3, -20(s0)
        //      addi t0, s3, 12
        //item: ld s3, -20(s0)
        //      flw ft0, 12(s3)
        //is_array:
        //self: addi t0, s0, -20
        //addr: addi t0, s0, -8
        //item: flw ft0, -8(s0)
        //元素:
        //flw ft0, -20(s0)
        int byte_offset = base_size * offset;
        int stack_offset = Lvar_array[order].offset;
        std::string op = basety == BTY_DOUBLE || basety == BTY_DOUBLE_PTR ? "fld" : 
                         basety == BTY_FLOAT  || basety == BTY_FLOAT_PTR ? "flw" : 
                         basety == BTY_INT    || basety == BTY_INT_PTR ? "lw"  :
                         basety == BTY_BOOL   || basety == BTY_BOOL_PTR ? "lb"  : "";
        if(is_ptr){
            if(is_addr){
                ASM_array.push_back("ld      s3, -"+std::to_string(stack_offset)+"(s0)");
                ASM_array.push_back("addi    "+reg_name+", s3, "+std::to_string(byte_offset));
            }
            else if(is_item){
                ASM_array.push_back("ld      s3, -"+std::to_string(stack_offset)+"(s0)");
                ASM_array.push_back(op+"     "+reg_name+", "+std::to_string(byte_offset)+"(s3)");
            }
            else{
                ASM_array.push_back("ld      "+reg_name+", -"+std::to_string(stack_offset)+"(s0)");
            }
        }
        else{ //item或非array时offset为0
            if(is_array && !is_item){
                ASM_array.push_back("addi    "+reg_name+", s0, -"+std::to_string(stack_offset-byte_offset));
            }
            else{
                ASM_array.push_back(op+"     "+reg_name+", -"+std::to_string(stack_offset-byte_offset)+"(s0)");
            }
        }
    }
    else if(is_temp){
        basety = Temp_array[order].basety;
        base_size = (typeutils.basety_to_size)[basety];
        int stack_offset = Temp_array[order].offset;
        //临时变量没有PTR
        std::string op = basety == BTY_DOUBLE ? "fld" : 
                         basety == BTY_FLOAT  ? "flw" : 
                         basety == BTY_INT    ? "lw"  :
                         basety == BTY_BOOL   ? "lb"  : "";
        ASM_array.push_back(op+"     "+reg_name+", -"+std::to_string(stack_offset)+"(s0)");
    }
    else{ //立即数
        bool is_float = var_name.find("f") != -1;
        bool is_double = var_name.find(".")!=-1 && !is_float;
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
            ASM_array.push_back("lui     s3, %lo("+stack_label+")");
            std::string op = is_float ? "flw" : "fld";
            ASM_array.push_back(op+"     "+reg_name+", %hi("+stack_label+")(s3)");
        }
        else{ //int bool
            std::string valstr = var_name.substr(1)
            ASM_array.push_back("li      "+reg_name+", "+valstr);
        }
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
    for(int i=0;i<semantic_analysis.IRC_array.size();i++){
        IR_code_t IRC = semantic_analysis.IRC_array[i];
        i++; //仅当func_end调回时该句无效。
        if(rescan){
            switch(IRC.IRop){
                case IR_G_ALLOC:
                    std::cout << "Rescan exclues G_Alloc" << std::endl;
                    exit(Code_ERR);
                    break;
                case IR_L_ALLOC:
                    Gen_L_Alloc(IRC);
                    break;
                case IR_LABEL:
                    Gen_Label(IRC);
                    break;
                case IR_FUNC_BEGIN:
                    Gen_FuncBegin(IRC);
                    rescan_loc = i; //表示跳回位置
                    break;
                case IR_FUNC_END:
                    Gen_FuncEnd(IRC);
                    rescan = false; //表示rescan结束
                    break;
                case IR_PARAM:
                    Gen_Param(IRC);
                    break;
                case IR_CALL:
                    Gen_Call(IRC);
                    break;
                case IR_RETURN;
                    Gen_Return(IRC);
                    break;
                case IR_ASSIGN:
                    Gen_Assign(IRC);
                    break;
                case IR_ADD: case IR_SUB: case IR_MUL: case IR_DIV: 
                case IR_MOD: case IR_AND: case IR_OR:
                    Gen_BinaryOp(IRC);
                    break;
                case IR_NEG: case IR_NOT:
                    Gen_UnaryOp(IRC);
                    break;
                case IR_BEQ: case IR_BNE: case IR_BLT: case IR_BGT: 
                case IR_BLE: case IR_BGE:
                    Gen_Branch(IRC);
                    break;
                case IR_J;
                    Gen_Jump(IRC);
                    break;
                default:
                    std::cout << "Unexpected IRop: "<< IRC.IRop <<" in Rescan" <<std::endl;
                    exit(Code_ERR);
                    break;    
            }
        }
        else{
            switch(IRC.IRop){
                case IR_G_ALLOC:
                    Gen_G_Alloc(IRC);
                    break;
                case IR_L_ALLOC:
                    Cnt_Temp_Lvar(irc.result);
                    break;
                case IR_FUNC_BEGIN:
                    frame_size = 16; //重新开始统计，开始包含了ra+sp 8+8
                    Cnt_FuncParam(irc.result);
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
        cact_basety_t basety = Lvar_array[order].basety;
        std::string suffix =    (basety == BTY_FLOAT || basety == BTY_INT) ? "w" :
                                (basety == BTY_BOOL) || "b" : 
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
        std::string offset = std::to_string(Lvar_array[order].offset);
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
    else{
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
    ASM_array.push_back("nop")

    cact_basety_t basety = irc.basety;
    std::string IR_temp = irc.arg1;
    if(IR_temp.length()!=0){
        std::string reg = (basety == BTY_FLOAT || basety == BTY_DOUBLE) ? "fa0" : "a0";
        std::string op = (basety == BTY_DOUBLE) ? "fsd" :
                         (basety == BTY_FLOAT) ? "fsw" :
                         (basety == BTY_BOOL) ? "sb" : 
                         "sw";
        int order = num_from_name(IR_temp);
        std::string offset = std::to_string(Temp_array[order].offset);
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
    //result可以是@x<y @x ^x<y ^x 不为数组，数组用Alloc赋值
    std::string result = irc.result;
    bool is_gvar = result[0] == GVAR_PREFIX;
    bool is_lvar = result[0] == LVAR_PREFIX;
    int item_infix_loc = result.find(ITEM_INFIX);
    bool is_item = item_infix_loc != -1;

    int order;
    int offset;
    if(is_item){
        order = std::stoi(result.substr(1,item_infix_loc-1));
        offset = std::stoi(result.substr(item_infix_loc+1,result.length()-item_infix_loc-1));
    }
    else{
        order = std::stoi(result.substr(1));
        offset = 0;
    }
    std::string var_name = irc.arg1;
    cact_basety_t basety = irc.basety;
    //指定中间寄存器和存储操作
    std::string reg_name;
    std::string op;
    if(basety == BTY_FLOAT || basety == BTY_DOUBLE){
        reg_name = "fs4";
        op = (basety == BTY_FLOAT) ? "fsw" : "fsd";
    }
    else{
        reg_name = "s4";
        op = (basety == BTY_BOOL) ? "sb" : "sw";
    }
    var_to_reg(var_name,reg_name);
    //存储部分示例
    //is_gvar: byte_offset = 3*4
    //self: lui s5, %lo(GVAR0)
    //      flw fs4, %hi(GVAR0)(s5)
    //item: lui s5, %lo(GVAR0+12)
    //      flw fs4, %hi(GVAR0+12)(s5)
    //is_lvar: stack_offset=20 byte_offset=12
    //self: flw fs4, -20(s0)
    //item: flw fs4, -8(s0)
    int base_size = (typeutils.basety_to_size)[basety];
    int byte_offset = base_size * offset;
    if(is_gvar){
        std::string stack_label = "GVAR"
        std::string offset_str = is_item ? "+"+std::to_string(byte_offset) : "";
        ASM_array.push_back("lui     s5, %lo("+stack_label+")");
        ASM_array.push_back(op+"     "+reg_name+", %hi("+stack_label+offset_str+")(s5)");
    }
    else{
        ASM_array.push_back(op+"     "+reg_name+", -"+std::to_string(stack_offset-byte_offset)+"(s0)");
    }
}
void RiscvGen:: Gen_BinaryOp(IR_code_t &irc){}
void RiscvGen:: Gen_UnaryOp(IR_code_t &irc){}
void RiscvGen:: Gen_Branch(IR_code_t &irc){}
void RiscvGen:: Gen_Jump(IR_code_t &irc){
    ASM_array.push_back("j       "+irc.result);
}
void RiscvGen:: Gen_G_Alloc(IR_code_t &irc){
    std::string name = irc.result;
    cact_basety_t basety = irc.basety;
    std::string initval_str = irc.arg1;
    int order = num_from_name(name);
    std::string stack_label = "GVAR"+std::
    bool is_const = Gvar_array[order].is_const;
    bool is_inited = initval_str.size()!=0;
    size_t base_size = (typeutils.basety_to_size)[basety];
    int len = Gvar_array[order].length;
    //分区信息
    std::string sec_str =   is_const ? ".rodata" :
                            is_inited ? ".bss" :
                            ".data";
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
    Const_Stack.push_back(".size   " + stack_label + std::to_string(base_size*length))
    Const_Stack.push_back(stack_label + ":");

    if(is_inited){
        stack_initval(initval_str,basety,len);
    }
    else{
        Const_Stack.push_back(".zero   "+std::to_string(base_size*len))
    }
}
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
    int len = Lvar_array[order].length;
    int offset = Lvar_array[order].offset;

    //声明和获取的label
    std::string stack_label = "LVAR" + std::to_string(order);
    
    //常量声明
    Const_Stack.push_back("")
    Const_Stack.push_back(".section    .rodata")
    if(len>1){
        //对输出，均使用标号初始化
        Const_Stack.push_back(".align  3")
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
        ASM_array("lui     s2, %hi(" + stack_label + ")");
        ASM_array("addi    s2, s2, %lo(" + stack_label + ")");
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
            int initval = std::to_string(initval_str.substr(1,loc-1))
            ASM_array.push_back("li      s1, "+std::to_string(initval));
            ASM_array.push_back(store+"      s1, -"+std::to_string(offset)+"(s0)");
        }
        else{
            std::string suffix = (basety == BTY_FLOAT) ? "w" : "d";
            ASM_array("lui     s2, %hi(" + stack_label + ")");
            ASM_array("fl"+suffix+"     fs2, %lo("+stack_label+")(s2)");
            ASM_array("fs"+suffix+"     fs2, -"+std::to_string(offset)+"(s0)");
        }
    }
}

//根据函数名，计算形参占用栈帧，并将位置写入对应局部变量
void RiscvGen:: Cnt_FuncParam(std::string func_name){
    auto iter = (symbol_table.func_table).find(func_name);
    for(auto fparam: (iter->second).fparam_list){
        std::string IR_name = fparam.IR_name;
        int order = num_from_name(IR_name);
        cact_basety_t basety = Lvar_array[order].basety;
        size_t size = (typeutils.basety_to_size)[basety];
        frame_size = up_to_align(frame_size,size);
        frame_size += size;
        Lvar_array[order].offset = frame_size;
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
        basety = Temp_array[order].basety;
        len = Temp_array[order].length;
    }
    else{//lvar 局部变量
        basety = Lvar_array[order].basety;
        len = Lvar_array[order].basety;
    }
    //这里设计bool使用1byte
    size_t size = (typeutils.basety_to_size)[basety];
    //对齐到size大小
    frame_size = up_to_align(frame_size,size);
    size *= len;
    frame_size += size;
    if(is_temp){
        Temp_array[order].offset = frame_size;
    }
    else{
        Lvar_array[order].offset = frame_size;
    }
}
#endif