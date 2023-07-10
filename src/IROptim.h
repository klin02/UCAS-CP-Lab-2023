#pragma once

#include "cact_types.h"
#include "SymbolTable.h"
#include "SemanticAnalysis.h"
// #include <string.h>
extern int OPTIM_LEVEL;

extern SemanticAnalysis semantic_analysis;
extern TypeUtils    typeutils;

#ifdef IR_gen
class BasicBlock{
    public:
        //order
        int order;
        //对应原始IRC的起止位置
        int from;
        int to;
        //基本块使用链表连接
        std::vector<BasicBlock*> pre_list;
        std::vector<BasicBlock*> next_list; 
        
        std::vector<IR_code_t>   IRC_array;

        //IR指令的位置
        std::set<int> gen;
        std::set<int> kill;
        std::set<int> def_in;
        std::set<int> def_out;
        //变量名
        std::set<std::string> def;
        std::set<std::string> use;
        std::set<std::string> live_in;
        std::set<std::string> live_out;

        //用于dag替换后后续语句可以替换
        std::unordered_map<std::string,std::string> replace_map;
        
        std::string to_replace(std::string var);

        void init_def_use();
        void get_var(std::string arg, std::vector<std::string> &vec);
        void add_def(std::string var);
        void add_use(std::string var);
        void dead_code();
        void dag();
        // void init();
        // void optim();
};
class IROptim{
    public:
        std::vector<IR_code_t>   IRC_array;
        std::vector<BasicBlock>  blk_list;

    private:
        //扫描,暂存被跳转的label及其用到的位置，因为有可能控制流优化跳过label
        std::unordered_map<std::string, std::vector<int>> label_use;
        std::unordered_map<std::string, int> label_loc;

        //记录首指令位置，及来自哪条指令，用于基本块确定前驱
        std::map<int, std::vector<int>> head_map;

        //基于旧IRC_array的更新信息，减少扫描次数
        //将删除的指令位置
        std::set<int> erase_set;
        //将插入的指令位置及内容
        std::map<int,std::vector<IR_code_t>> insert_map;

    public:
        void optim();
        void printIRC(std::ofstream &outfile){
            outfile << std::setw(10) << "IRop"   << '|' 
                    << std::setw(10) << "Basety" << '|' 
                    << std::setw(10) << "result" << '|' 
                    << std::setw(10) << "arg1"   << '|' 
                    << std::setw(10) << "arg2"   << '|' << std::endl;
            for(auto IRC = IRC_array.begin(); IRC!= IRC_array.end(); IRC++) {
                outfile << std::setw(10) << (typeutils.IRop_to_str)[IRC->IRop]      << '|' 
                        << std::setw(10) << (typeutils.basety_to_str)[IRC->basety]  << '|' 
                        << std::setw(10) << IRC->result << '|' 
                        << std::setw(10) << IRC->arg1   << '|' 
                        << std::setw(10) << IRC->arg2   << '|'<< std::endl;
            }
        }
    private:
        void get_head_label();
        void update_irc();
       
        void split();
        void merge();
        
        void controlflow();
        void dag();
        void deadcode();
        void algebrasimplify();
        void kill_label();
        //是2的幂次返回指数，否则返回-1
        int get2power(std::string arg);
};
#endif