# PR001 - notes

### 脚本说明

+ rebuild.sh

  + 功能：

    1. 可选择Listener或Visitor模式。根据脚本提示，输入'l'为Listner模式，'v'或直接换行为Visitor模式。
    2. 重新生成grammer文件夹下除.g4外其余文件
    3. 重新编译程序

  + 运行：

    ```shell
    # 第一次使用前
    chmod +x ./rebuild.sh
    
    # 后续使用
    # Listernr 模式
    ./rebuild
    ...		# 脚本提示
    l
    # Visitor 模式
    ./rebuild
    ...		# 脚本提示
    v 		# 或直接换行
    ```

+ test.sh

  + 功能：
    1. 批量测试samples
    2. 输出对每个样例执行时的打印信息(Output)及返回码（Exit code），并通过返回码和名字匹配判断是否通过
    3. 统计出错样例(Fail list)和通过率(Pass rate)

  + 运行：

    ```shell
    # 第一次使用前
    chmod +x ./test.sh
    
    # 批量测试
    ./test.sh
    ```

  + 说明：

    脚本用的是bash语法，所以不能使用`sh`命令。上述命令也可以替换为`bash test.sh`



### main.cpp说明

+ 添加AST打印及调试说明

  目前对于失败样例的调试主要根据AST树的打印实现。

  由于程序方法的输出会为每个子树添加左右括号包裹，不易查看。可以将程序根据文法的推导进行缩进处理，对于失败测试用例`27_true_mixed_sample.cact`的输出处理可见notes文件夹下`sample27_debug`

+ 分析错误返回非零值

  Visitor或Listener模式下，要求识别错误返回非零值都可以通过在`visitErrorNode`方法中执行exit(1)实现

+ `class Analysis`声明

  + 对于父类的`virtual`方法，需要进行重复声明覆盖

  + 如果希望继承自`CACTVisitor`或`CACTListener`，（demo中的写法）

    CACTBaseVisitor/CACTBaseListener是一个空的实例实现，可以直接复制它的写法，然后添加`visitErrorNode`方法

  + 如果想省略大量对于virtual方法的override声明，

    可以参照`CACTVisitor`或`CACTListener`的实现，继承自依赖中的类，并重写基本的一些方法

+ Listener模式和Visitor模式的区别

  Listener模式可以通过`walk`方法隐式遍历，`Visitor`模式则需要显式为每个非终结符visit方法调用`visitChildren`（可以参照CACTBaseVisitor实现）



### 调试说明

使用未经修改的文法文件可以通过27/28个测试点，失败的测试用例`27_true_mixed_sample.cact`的输出处理可见notes文件夹下`sample27_debug`。在main中的最后一个else中的部分推导应该由

```c
unaryExp 
  print_bool 
  ( 
  false  //wrong here
  ) 
```

修改为

```c
unaryExp
  print_bool
  (
  funcRParams
    exp 
      false
  )
```

出现上述错误是因为`BoolConst`未被识别为终结符。

这是因为，在写关键字列表时，已经为"true"和"false"指定了终结符，在写`BoolConst->TURE|FALSE`产生式时，因为右部为终结符，左部应当为非终结符。但首字母大写不符合非终结符的定义规则。

解决该错误有下述方法

+ 将`BoolConst`更名为`boolConst`，即认为是非终结符
+ 为`TRUE`和`FALSE`添加`fragment`分片说明，则`BoolConst`仍可被认为是终结符。
+ `BoolConst`直接产生`true`和`false`

综合考虑下，认为第二种方法更为合理。



上述错误的发现还启发了下面这种写法的不合理性

```g4
FloatConst
    : DoubleConst ('f' | 'F')
    ;

DoubleConst 
    : ...
```

此处`FloatConst`和`DoubleConst`都是需要被语法规则调用的终结符，因此应该使用一个中间表示来避免上述情形。

修改后该处文法应当如下：

```g4
FloatConst
    : PreFloatDouble ('f' | 'F')
    ;

DoubleConst 
    : PreFloatDouble
    ;

fragment PreFloatDouble
	: ...
```









