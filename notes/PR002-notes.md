# PR002-notes

+ 对各文件的要点设计进行简要说明，报告可以在其上基础上补充，更多细节可以查看代码注释。

## cact_types.h

+ 这个文件主要定义了基本类型

1. 在表达式操作类型定义中，有几个需要注意的

   + OP_BASE  标志 基本常量 (直接由终结符推出)

     要求数组长度直接由intconst推出，从exp到number的过程中不经过任何操作，且其类型应当与变量（无论是否const）相区分。

     只有当表达式类型为OP_BASE，且ret_type为int时才表示直接由intConst推出，可以用于维度检查。

   + OP_ARRAY 标志 左值子数组

     在一元/二元表达式中都有要求不能对数组类型进行操作，当左值为子数组时，应当在OperandCheck检查中报错。

   + OP_ITEM 标志 左值变量或数组元素

     当左值为变量或单个的数组元素时，允许作为表达式的操作对象。应当与OP_BASE和OP_ARRAY区分，因此设置为OP_ITEM

2. 表达式类型定义

   + op表示这个表达式的操作类型，可以用于OperandCheck针对该操作的检查
   + basety表示表达式返回类型，当该表达式作为子表达式时，就需要接受返回类型的检查。注意：合法的子表达式不能为数组，因此使用basety就足以表达其类型。
   + subexprs是指向子表达式的共享指针数组。方便OperandCheck检查。
   + int_result用于表示直接由IntConst推出的表达式的值。只有当表达式类型为OP_BASE，且ret_type为int时才有效。该值用于检查维度前几维的index是否在范围内，同时完成了数组越界检查（虽然实验手册没要求）。
   + arrdims用于表示子数组的维度信息，表示函数调用实参exp推出子数组的情形。只有当类型为OP_ARRAY时才有效，且推导过程中不会经过运算。

3. 表达式共享指针类型

   文法文件中为每个exp、number和Lval都设置了指向表达式结构体的共享指针。共享指针的优势主要是避免了结构体的连续传递（因为结构体传递会涉及值拷贝，影响性能）。与普通指针的区别是共享指针指向同一个结构体，则结构体生存周期为共享指针的并集，避免了在子表达式中创建结构体，退出时无效导致指针无效的问题。（这里主义共享指针的正确使用，在debug部分详细说明）

   其使用需要include \<memory\>

4. typeutils

   主要用到了str_to_basety和str_to_op，直接根据子节点的getText获取其信息。



## Symbol.h

1. 变量表
   + map具有key不重复性的特征，适合用作表的检查。由于不关注声明顺序，使用基于hash的unordermap可以提高查找性能
   + 考虑到不同作用域可能出现同名变量，如果只使用name作为map的key，一是不同作用域同名变量不能插入，二是极端情况下可能每个作用域都有同名变量，在重复性检查中就退化成了线性查找比对作用域，影响性能。因此将name和scope对作为key。
   + 由于map插入时会和已有的表项比较，对于非基本类型，需要重新定义这个比较的方法，重载运算符==实现。
   + find只能查找特定作用域的变量，但在使用变量有一个向根查找的过程，在SymbolTable中定义了deepfind方法用于实现。
   + 变量表项，name和scope好像都可以从key得到，后续可以考虑删去。
2. 函数表
   + 同理，使用unordered map，但用name作为key即可
   + 表项，name可以删去

3. 形参列表
   + 要求有序，不能同名，使用map实现
   + map的顺序依赖其比较，因此需要重载比较运算符，按照添加顺序排序。



## SemanticAnalysis.h

1. 根作用域和当前作用域作为类的共享变量在此声明
2. 内联函数需要自行添加，cact文件可以直接调用
3. 根据模板函数来处理公共逻辑
   + OperandCheck处理一元/二元表达式的类型检查。同时赋值语句也使用临时exp来调用这个框架检查。
   + Const/Var的Decl/Def逻辑高度重合
   + 二元表达式aExp -> bExp | aExp op bExp的逻辑高度重合



## SemanticAnalysis.cpp

+ 这里重点说明一下逻辑比较复杂的，其他函数细节报告可以参照代码和注释

1. enterConst_Var_Decl

   将指向Def的basety的指针传递给btype，由bypte完成填写。依赖了左子树比右子树先遍历完成的特点。可以避免在exitDecl时重复遍历Def再来进行类型检查等一系列在第一次自动遍历Def就可以完成的操作。

2. enterConst_Var_Def

   + 在该节点定义了维度数组，将其指针分别传递给子节点arrayDims和初始值。在文法中新定义了arrayDims，负责在exit时填写维度数组。将类型和维度数组传递给初始值，在其中完成检查，避免重复遍历。
   + 考虑到初始值在无嵌套（dim_index=1）且为最外层数组时可以为平铺列表形式。因此传递了top属性。

3. exitConst_Var_Def

   除了变量的重复性检查和表项添加，主要要注意初始值的检查。

   在初始值的检查是自底向上完成的，对于嵌套形式，可能存在声明为三维数组，初始值为二维子数组的情形。因此需要在此进行维度检查，并特别考虑左边为数组，右侧为元素列表的情形（这时候元素列表的合法性已经在初始值节点完成了）。

4. exitBinaryExp

   这里需要注意表达式的返回值类型。对于布尔表达式，类型就是bool，否则任取子表达式类型即可（如果两个子表达式类型不一致，会在OperandCheck中报错）

5. enter/exit ConstInitVal

   + basety自顶向下继承，在constExp节点完成检查
   + 维度自底向上检查，直接退出constExp的dim_index为0，推出\{\}为1,否则查看检查所有子数组的dim_index一致性，并在其上加1。
   + 最外层数组，且无嵌套，允许以平铺列表初始化
   + 对于嵌套形式定义，从最内层维度开始检查。
     + 对于初始值维度大于声明的情况，在该节点报错
     + 对于初始值维度小于声明的情况，在exitDef检查

6. enterFuncDef

   locals定义了形参列表。将其指针分别传递给了形参节点和block节点。形参节点负责填写，block提前获取了形参列表以加入作用域，避免重复遍历。

7. exitFuncFParam

   这里主要注意数组形参的隐式说明，通过括号层数和intconst数量判断。

8. exitBlock

   根据实验指导，如果块中存在return或包含return的stmt，一定在最后一句。由于这个返回类型的获取与位置有关，可以考虑使用综合属性，自底向上传递。且方便了对if-else的分支结构返回类型的检查。

   使用`(void*)(ctx->children[ctx->children.size()-2]) == (void*)(*ctx->stmt().rbegin())`时，需要特别注意，第一个ctx哪里没有*，实验指导有误。且应用该条件的时候，需要增加检查`ctx->stmt().size()!=0`，否则当block中没有stmt时，会触发内存泄漏。

9. exitStmt_if

   stmt使用控制流语句对不同情况进行了划分。

   将省略的else分支视为返回类型void,错误情形如下：

   1. 只有if，且stmt返回类型不为void

   2. if-else,且stmt返回类型不一致

10. exitStmt_while

    认为跳出后分支是void，检查类似只有if。

11. exitLVal

    这里特别注意子数组的情形，用到了直接推到intConst的表达式检查。子数组前几维检查，后续维度继承。

12. exitUnaryExp

    关注else分支，也就是函数调用的情形。列表长度检查后，对于相应的形参和实参，涉及到基本类型、是否数组、维数、每维度长度等。特别的，对于首维，形参隐式声明时为0，可以忽略检查。



+ 特别说明：sharedptr的用法

  sharedptr可以指向某个结构体，使得这个结构体的生存周期不短于共享指针，但这要求正确的使用形式。

  正确形式：

  ```cpp
  //已有指针：表达式类型
  ctx->self.reset(new cact_expr_t{op,basety,subexprs,0,arrdims});
  //临时指针：赋值语句临时使用
  cact_expr_ptr expr_ptr(new 
                       cact_expr_t{op,BTY_UNKNOWN,subexprs,0,arrdims});
  ```

  已有指针通过reset的方式，临时指针通过新建的方式，但结构体都是位于shared_ptr的管理下。

  错误形式：

  ```cpp
  cact_expt_t expr = ..
  //已有指针
  ctx->self.reset(&expr);
  //临时指针
  cact_expr_ptr expr_ptr(&expr);
  ```

  错误形式下，临时变量expr会在函数退出后被释放，导致指针变为野指针，内存泄漏。该方式也可以改写以下正确形式：

  ```cpp
  cact_expt_t *expr = new cact_expr_t;
  //已有指针
  ctx->self.reset(expr);
  //临时指针
  cact_expr_ptr expr_ptr(expr);
  ```

  将expr变为指针，传递expr而非其地址，从而由shared_ptr接管指针所指结构体生存周期。