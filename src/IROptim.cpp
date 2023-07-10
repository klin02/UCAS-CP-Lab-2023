#pragma once

#include "IROptim.h"
#ifdef IR_gen
void BasicBlock::dag(){
    //仅对计算语句，且arg均不为数组元素时，向前遍历，查看有无相同计算语句
    //考虑到一个语句的arg均被替换，需要查找arg
    //如遇到对arg赋值的，则终止，如遇到相同计算，该句改为assign。(后续无使用则会被死代码消除)
    
    int loc=0;
    for(auto &IRC: IRC_array){
        switch(IRC.IRop)
        {
            case IR_ADD: case IR_SUB: case IR_MUL: case IR_DIV: 
            case IR_SLL: case IR_SRA:
            case IR_MOD: case IR_AND: case IR_OR: 
            {
                //如果该句替换，则不需擦除，否则需要擦除替换表，定值覆盖
                bool replace_flag = true;
                bool noinfix = true;
                //对出现有中缀的，保证offset部分可以正确替换
                if(IRC.arg1.find(ITEM_INFIX)!=-1){
                    noinfix = false;
                    int loc = IRC.arg1.find(ITEM_INFIX);
                    std::string prefix = IRC.arg1.substr(0,loc);
                    std::string suffix = IRC.arg1.substr(loc+1,IRC.arg1.size()-loc-1);
                    IRC.arg1 = prefix + ITEM_INFIX + to_replace(suffix);
                }    
                if(IRC.arg2.find(ITEM_INFIX)!=-1){
                    noinfix = false;
                    int loc = IRC.arg2.find(ITEM_INFIX);
                    std::string prefix = IRC.arg2.substr(0,loc);
                    std::string suffix = IRC.arg2.substr(loc+1,IRC.arg2.size()-loc-1);
                    IRC.arg2 = prefix + ITEM_INFIX + to_replace(suffix);
                }  
                //对arg都为1的，DAG优化
                if(noinfix){
                    //首先替换arg
                    IRC.arg1 = to_replace(IRC.arg1);
                    IRC.arg2 = to_replace(IRC.arg2);
                    //扫描之前的语句
                    //记录向前扫描的过程中被定义的变量，需要保证最后替换的变量为被中间定义
                    std::set<std::string> def_set;
                    for(int j=loc-1;j>=0;j--){
                        auto pre_IRC = IRC_array[j];
                        //保证不对arg定值
                        bool break_flag = false;
                        bool def_flag = false;
                        switch (pre_IRC.IRop)
                        {
                            case IR_ADD: case IR_SUB: case IR_MUL: case IR_DIV: 
                            case IR_SLL: case IR_SRA:
                            case IR_MOD: case IR_AND: case IR_OR: 
                            case IR_NEG: case IR_NOT:
                            case IR_ASSIGN:
                                if(pre_IRC.result==IRC.arg1 || pre_IRC.result==IRC.arg2){
                                    break_flag = true;
                                }
                                else{//延后插入该条，否则没有满足条件的语句
                                    def_flag = true;
                                }
                                break;
                            default:
                                break;
                        }
                        if(break_flag)
                            break;
                        //要考虑前序语句结果不覆盖计算
                        if(pre_IRC.IRop == IRC.IRop && pre_IRC.arg1 == IRC.arg1 && pre_IRC.arg2 == IRC.arg2
                            && pre_IRC.result!= pre_IRC.arg1 && pre_IRC.result != pre_IRC.arg2){
                            if(def_set.find(pre_IRC.result)==def_set.end()){
                                IRC.IRop = IR_ASSIGN;
                                IRC.arg1 = pre_IRC.result;
                                IRC.arg2 = "";
                                replace_map[IRC.result] = pre_IRC.result; 
                                replace_flag = false;                               
                            }
                            break;
                        }
                        if(def_flag){
                            def_set.insert(pre_IRC.result);
                        }
                    }
                }
                //最后需要撤销replace map中的该名字
                if(replace_flag)
                    replace_map.erase(IRC.result);
                break;  
            }
            case IR_ASSIGN: case IR_NEG: case IR_NOT:
                replace_map.erase(IRC.result);
                break;
            default:
                break;
        }
        loc++;
    }
}
std::string BasicBlock::to_replace(std::string var){
    if(replace_map.find(var)!=replace_map.end()){
        return replace_map[var];
    }
    else{
        return var;
    }
}
void BasicBlock::init_def_use(){
    //遍历基本块内IRCarray
    // for(int i=0;i<IRC_array.size();i++)
    std::vector<std::string> vec;
    for(auto IRC: IRC_array)
    {
        switch(IRC.IRop){
            case IR_L_ALLOC:
            {
                //初始化情形
                if(IRC.arg1.length()!=0){
                    get_var(IRC.arg1,vec);
                    for(auto var:vec){
                        add_use(var);
                    }
                    add_def(IRC.result); 
                }
                break;                
            }
            case IR_CALL:
            {
                //所有全局变量都可能被改变
                for(int i=0;i<semantic_analysis.Gvar_array.size();i++){
                    add_use(GVAR_PREFIX+std::to_string(i));
                }
                //有返回值情形
                if(IRC.arg1.length()!=0){
                    add_def(IRC.arg1);
                }
                break;                
            }
            case IR_FUNC_BEGIN:
            {
                //加入所有参数（局部变量）
                for(auto fparam:((symbol_table.func_table).find(IRC.result)->second).fparam_list){
                    add_use(fparam.IR_name);
                }
                break;
            }
            case IR_PARAM: case IR_RETURN: 
            {
                get_var(IRC.result,vec);
                for(auto var:vec){
                    add_use(var);
                }
                break;
            }
            case IR_ASSIGN: case IR_NEG: case IR_NOT:
            {
                get_var(IRC.arg1,vec);
                for(auto var:vec){
                    add_use(var);
                }
                get_var(IRC.result,vec);
                if(vec.size()!=1){
                    add_use(vec[1]);
                }
                add_def(vec[0]);
                break;
            }
            case IR_ADD: case IR_SUB: case IR_MUL: case IR_DIV: 
            case IR_SLL: case IR_SRA:
            case IR_MOD: case IR_AND: case IR_OR: 
            {
                get_var(IRC.arg1,vec);
                for(auto var:vec){
                    add_use(var);
                }
                get_var(IRC.arg2,vec);
                for(auto var:vec){
                    add_use(var);
                }
                get_var(IRC.result,vec);
                if(vec.size()!=1){
                    add_use(vec[1]);
                }
                add_def(vec[0]);
                break;
            }
            case IR_BEQ: case IR_BNE: case IR_BLT: case IR_BGT: 
            case IR_BLE: case IR_BGE:
            {
                get_var(IRC.arg1,vec);
                for(auto var:vec){
                    add_use(var);
                }
                get_var(IRC.arg2,vec);
                for(auto var:vec){
                    add_use(var);
                }
                break;
            }
            default:
                break;
        }
    }
}
//注意不能传出局部变量
void BasicBlock::get_var(std::string arg, std::vector<std::string> &vec){
    vec.clear();
    bool is_var = arg.find(GVAR_PREFIX)!=-1 || arg.find(LVAR_PREFIX)!=-1 || arg.find(TEMP_PREFIX)!=-1;
    if(!is_var)
        return;
    int infix_loc = arg.find(ADDR_INFIX);
    if(infix_loc==-1){
        infix_loc = arg.find(ITEM_INFIX);
    }
    if(infix_loc == -1){
        vec.push_back(arg);
    }
    else{
        vec.push_back(arg.substr(0,infix_loc));
        vec.push_back(arg.substr(infix_loc+1,arg.length()-infix_loc-1));
    }
}
//只插入变量名，不含偏移，且不在use/def中才可插入def/use
void BasicBlock::add_def(std::string var){
    if(use.find(var)==use.end()){
        def.insert(var);
    }
}
void BasicBlock::add_use(std::string var){
    if(def.find(var)==def.end()){
        use.insert(var);
    }
}
void BasicBlock::dead_code(){
    int IRC_size = IRC_array.size();
    std::set<std::string> live = live_out;
    std::vector<std::string> vec;
    for(int i=IRC_size-1;i>=0;i--){
        auto IRC = IRC_array[i];
        switch(IRC.IRop){
            case IR_L_ALLOC:
            {
                if(IRC.arg1.length()!=0){
                    if(live.find(IRC.result)==live.end()){
                        IRC_array.erase(IRC_array.begin()+i);
                    }
                    else{
                        live.erase(IRC.result);
                        get_var(IRC.arg1,vec);
                        for(auto var:vec){
                            live.insert(var);
                        }
                    }  
                }
                break;                
            }
            case IR_CALL:
            {
                //有返回值情形
                if(IRC.arg1.length()!=0){
                    live.erase(IRC.arg1);
                }
                //所有全局变量都可能被改变
                for(int i=0;i<semantic_analysis.Gvar_array.size();i++){
                    live.insert(GVAR_PREFIX+std::to_string(i));
                }
                break;                
            }
            case IR_FUNC_BEGIN:
            {
                //加入所有参数（局部变量）
                for(auto fparam:((symbol_table.func_table).find(IRC.result)->second).fparam_list){
                    live.insert(fparam.IR_name);
                }
                break;
            }
            case IR_PARAM: case IR_RETURN: 
            {
                get_var(IRC.result,vec);
                for(auto var: vec){
                    live.insert(var);
                }
                // live.insert(IRC.result);
                break;
            }
            case IR_ASSIGN: case IR_NEG: case IR_NOT:
            {
                get_var(IRC.result,vec);
                //数组对某个元素赋值不会被删除
                if(vec.size()==1 && live.find(vec[0])==live.end()){
                    IRC_array.erase(IRC_array.begin()+i);
                }
                else{
                    if(vec.size()!=1){
                        live.insert(vec[1]);
                    }
                    else{
                        //数组名不删
                        live.erase(vec[0]);
                    }
                    get_var(IRC.arg1,vec);
                    for(auto var:vec){
                        live.insert(var);
                    }
                }
                break;
            }
            case IR_ADD: case IR_SUB: case IR_MUL: case IR_DIV: 
            case IR_SLL: case IR_SRA:
            case IR_MOD: case IR_AND: case IR_OR: 
            {
                get_var(IRC.result,vec);
                if(vec.size()==1 && live.find(vec[0])==live.end()){
                    IRC_array.erase(IRC_array.begin()+i);
                }
                else{
                    if(vec.size()!=1){
                        live.insert(vec[1]);
                    }
                    else{
                        //数组名不删
                        live.erase(vec[0]);
                    }
                    get_var(IRC.arg1,vec);
                    for(auto var:vec){
                        live.insert(var);
                    }
                    get_var(IRC.arg2,vec);
                    for(auto var:vec){
                        live.insert(var);
                    }
                }
                break;
            }
            case IR_BEQ: case IR_BNE: case IR_BLT: case IR_BGT: 
            case IR_BLE: case IR_BGE:
            {
                get_var(IRC.arg1,vec);
                for(auto var:vec){
                    live.insert(var);
                }
                get_var(IRC.arg2,vec);
                for(auto var:vec){
                    live.insert(var);
                }
                break;
            }
            default:
                break;
        }
    }
}
void IROptim::optim(){
    for(auto IRC: semantic_analysis.IRC_array){
        IRC_array.push_back(IRC);
    }
    if(OPTIM_LEVEL == 0){
        return;
    }
    controlflow();
    split();
    dag();
    deadcode();
    merge();
    algebrasimplify();

    //最后杀死所有没用的标签，方便汇编的窥孔优化
    kill_label();
}
void IROptim::kill_label(){
    get_head_label();
    for(auto pair:label_loc){
        auto label = pair.first;
        auto loc = pair.second;
        //如果没用到，就删除
        if(label_use.find(label)==label_use.end()){
            erase_set.insert(loc);
        }
    }
    update_irc();
}
void IROptim::dag(){
    for(auto &blk: blk_list){
        blk.dag();
    }
}
void IROptim::deadcode(){
    //首先确定每个blk的def，use，初始化in和out均为空
    for(auto &blk: blk_list){
        blk.init_def_use();
    }
    //迭代计算直至不变
    bool du_change = true;
    while(du_change){
        du_change = false;
        for(auto &blk: blk_list){
            //存储旧值用于比较
            std::set<std::string> old_live_in = blk.live_in;
            std::set<std::string> old_live_out = blk.live_out;
            //这里不需要将旧值清空，一方面考虑到迭代不会让set减少，一方面自身后继可以是自己
            for(auto blk_ptr: blk.next_list){
                auto next_blk = *blk_ptr;
                for(auto next_in: next_blk.live_in){
                    blk.live_out.insert(next_in);
                }
            }
            //如果这是函数最后一个基本块，全局变量后续都可能使用
            if(blk.IRC_array.back().IRop == IR_FUNC_END){
                for(int i=0;i<semantic_analysis.Gvar_array.size();i++){
                    blk.live_out.insert(GVAR_PREFIX+std::to_string(i));
                }
            }
            if(blk.live_out != old_live_out)
                du_change = true;
            for(auto out: blk.live_out){
                if(blk.def.find(out)==blk.def.end()){
                    blk.live_in.insert(out);
                }
            }
            for(auto use: blk.use){
                blk.live_in.insert(use);
            }
            if(blk.live_in != old_live_in){
                // std::cout << "in dif" <<std::endl;
                du_change = true;
            }
        }
    }

    //每个基本块消除死代码
    for(auto &blk: blk_list){
        blk.dead_code();
    }
}
void IROptim::algebrasimplify(){
    //简单的将2的幂次乘除法改为移位操作
    for(int i=0;i<IRC_array.size();i++){
        auto IRC = IRC_array[i];
        auto irop = IRC.IRop;
        auto arg1 = IRC.arg1;
        auto arg2 = IRC.arg2;
        if(irop == IR_MUL){
            int p1 = get2power(arg1);
            int p2 = get2power(arg2);
            if(p1 != -1){
                IRC_array[i].IRop = IR_SLL;
                IRC_array[i].arg1 = arg2;
                IRC_array[i].arg2 = IMM_PREFIX + std::to_string(p1);
            }
            else if(p2 != -1){
                IRC_array[i].IRop = IR_SLL;
                IRC_array[i].arg2 = IMM_PREFIX + std::to_string(p2);
            }
        }
        else if(irop == IR_DIV){
            int p2 = get2power(arg2);
            if(p2 != -1){
                IRC_array[i].IRop = IR_SRA;
                IRC_array[i].arg2 = IMM_PREFIX + std::to_string(p2);
            }
        }
    }
}
int IROptim:: get2power(std::string arg){
    bool is_imm = arg[0] == IMM_PREFIX;
    bool has_prefd = arg.find(".")!=-1 || arg.find("E")!=-1 || arg.find("e")!=-1;
    bool is_int = is_imm && !has_prefd;
    if(is_int){
        int n = std::stoi(arg.substr(1));
        if(n==1){
            return 0;
        }
        if(n<1 || n%2!=0){
            return -1;
        }
        else{
            int power = 0;
            while(n>1){
                n = n>>1;
                power ++;
            }
            return power;
        }
    }
    else{
        return -1;
    }
}
void IROptim::get_head_label(){
    //清理之前的，重新获取
    label_loc.clear();
    label_use.clear();
    head_map.clear();

    //共用变量，用时修改
    std::string label;
    int IRC_size = IRC_array.size();
    for(int i=0;i<IRC_size;i++){
        IR_code_t irc = IRC_array[i];
        switch(irc.IRop){
            case IR_CALL: 
                head_map[i+1].push_back(i);
                break;
            case IR_FUNC_END:
                head_map[i+1];
                break;
            case IR_FUNC_BEGIN:
                head_map[i];
                break;
            case IR_J:
            case IR_BEQ: case IR_BNE: case IR_BLT: case IR_BGT: 
            case IR_BLE: case IR_BGE:
            //跳转的下一条指令
                label = irc.result;
                // iter = label_use.find(label);
                if(label_use.find(label)!=label_use.end()){
                    label_use.find(label)->second.push_back(i);
                }
                else{
                    label_use[label].push_back(i);
                }
                if(irc.IRop != IR_J){
                    head_map[i+1].push_back(i);
                }
                else{
                    head_map[i+1];
                }
                break;

            case IR_LABEL: 
            //可能为目标指令
            //先暂存，后续填到头指令表
                label = irc.result;
                label_loc[label] = i;
                // if(label == "L15")
                //     std::cout << "headloc " << i << " " << IRC_array[i+1].IRop;
                break;
            default:
            //第一条指令，且排除func_begin情形
                if(i==0){
                    head_map[0];
                }
                break;
        }
    }
    //将用到的label作为首指令，并记录前驱
    int loc;
    for(auto pair: label_loc){
        label = pair.first;
        loc = pair.second;
        auto iter = label_use.find(label);
        if(iter!=label_use.end()){
            // head_map[loc] = iter->second;
            //当前一条指令不是无条件跳转时，补充前一条指令
            if(IRC_array[loc-1].IRop != IR_J){
                head_map[loc].push_back(loc-1);
            }
            for(auto use: iter->second){
                head_map[loc].push_back(use);
            }
        }
    }
    //将最后一条指令的下一个加入，便于统一和区分
    head_map[IRC_size];
}
void IROptim::update_irc(){
    std::vector<IR_code_t> IRC_stack = IRC_array;

    IRC_array.clear();
    for(int i=0;i<IRC_stack.size();i++){
        if(insert_map.find(i)!=insert_map.end()){
            for(IRC: insert_map[i])
            IRC_array.push_back(IRC);
        }
        if(erase_set.find(i)==erase_set.end()){
            IRC_array.push_back(IRC_stack[i]);
        }
    }
    // std::cout << "after size " << IRC_array.size() << std::endl;
    
    erase_set.clear();
    insert_map.clear();
}
void IROptim::controlflow(){
    //多遍扫描
    bool flow_change = true;
    int cnt = 0;
    while(flow_change){
        flow_change = false;
        get_head_label();
        
        //根据Label扫描
        for(auto pair: label_loc){
            std::string label = pair.first;
            int loc = pair.second;
            auto irop = IRC_array[loc+1].IRop;
            auto this_label = IRC_array[loc+1].result;
                    
        // std::string check_label = "L15";
        // auto check_loc = label_loc[check_label];
        // std::cout <<  "check " << label << " "<< IRC_array[check_loc+1].IRop <<std::endl;

            // std::cout << label << std::endl;
            // if(label == "L15"){
            //     // int loc = label_use[label][0];
            //     std::cout << label << std::endl;
            //     std::cout << "IRop" << irop <<" " << IR_J << std::endl;
            //     std::cout << "loc" << loc <<" " << IRC_array[loc].IRop <<" " << IR_LABEL << std::endl; 
            //     for(auto from: label_use[label]){
            //         std::cout << "use" << from << IRC_array[from].IRop  << std::endl;
            //     }
            // }
                

            if(irop == IR_J){ //下一条无条件
                //遍历跳到该label的地方
                if(label_use.find(label)!=label_use.end()){
                    flow_change = true;
                    for(auto from: label_use[label]){
                        //一定是j或者branch，更改label即可
                        //延后改写，以减少循环次数
                        // IRC_array[from].result = this_label;
                        erase_set.insert(from);
                        IR_code_t tmp_ir = IRC_array[from];
                        tmp_ir.result = this_label;
                        insert_map[from].push_back(tmp_ir);
                        // if(from == 68){
                        //     std::cout << this_label << std::endl;
                        // }
                    }
                }
                //之后没有用到该标签的地方，如果前一条是J，则删除
                if(IRC_array[loc-1].IRop == IR_J){
                    flow_change = true;
                    //删除改变布局
                    erase_set.insert({loc, loc+1});
                }
            }
            else if(irop == IR_BEQ || irop == IR_BNE || irop == IR_BGE || irop == IR_BGT || irop == IR_BLE || irop == IR_BLT){
                //语义分析保证了条件跳转的下一条一定有label
                auto next_label = IRC_array[loc+2].result;
                //统计条件跳转过来的数量，确定是否仍有使用
                int branch_cnt = 0;
                //遍历跳到该label的goto语句
                if(label_use.find(label)!=label_use.end()){
                    for(auto from: label_use[label]){
                        if(IRC_array[from].IRop == IR_J){
                            flow_change = true;
                            //改写并增加语句
                            // IRC_array[from] = IRC_array[loc+1];
                            //延后改写以免影响其他label
                            erase_set.insert(from);
                            insert_map[from].push_back(IRC_array[loc+1]);
                            //每个branch指令后面附带标签，保证后续优化的进行
                            //注意连插多条语句需要用vector存储
                            std::string attach = semantic_analysis.newLabel();
                            insert_map[from].push_back((IR_code_t){IR_LABEL,BTY_UNKNOWN,attach,"",""});
                            insert_map[from].push_back((IR_code_t){IR_J,BTY_UNKNOWN,next_label,"",""});
                        }
                        else
                            branch_cnt ++;
                    }
                }
                //之后没有用到该标签的地方，如果前一条是J，则删除
                if(IRC_array[loc-1].IRop == IR_J && branch_cnt == 0){
                    flow_change = true;
                    //删除改变布局
                    erase_set.insert({loc, loc+1});
                }
            }
        }
        
        //更新IRC_array，以方便下一次重定位
        update_irc();
        cnt++;
        // if(cnt==1)
        //     break;
    }

}
//将语义分析的中间代码分入各个基本块
void IROptim::split(){
    get_head_label();
    //根据首指令及前驱切分基本块并建立联系
    std::vector<int> head_vec;
    for(auto pair: head_map){
        head_vec.push_back(pair.first);
        // std::cout << pair.first << std::endl;
    }
    int head_size = head_map.size()-1;
    for(int i=0;i<head_size;i++){
        BasicBlock blk;
        blk.order = i;
        blk.from = head_vec[i];
        blk.to = head_vec[i+1]-1;
        for(int j=blk.from;j<=blk.to;j++){
            blk.IRC_array.push_back(IRC_array[j]);
        }
        blk_list.push_back(blk);
    }
    //根据head_map记录及每个块的from和to确定基本块的前驱和后继
    for(int i=0;i<head_size;i++){
        // std::cout << "BLK " << i << std::endl;
        auto vec = head_map[blk_list[i].from];
        for(auto pre: vec){
            for(int j=0;j<head_size;j++){
                if(blk_list[j].to == pre){
                    blk_list[i].pre_list.push_back(&(blk_list[j]));
                    blk_list[j].next_list.push_back(&(blk_list[i]));
                    // std::cout << j << std::endl;
                }
            }
        }
    }

    
}
void IROptim::merge(){
    IRC_array.clear();
    for(auto &blk: blk_list){
        for(auto IRC: blk.IRC_array){
            IRC_array.push_back(IRC);
        }
        // IRC_array.push_back((IR_code_t){IR_UNKNOWN});
    }
}
#endif