## 字节码
- 类或接口的方法信息存储在 class 文件的 method_info 结构中
- 如果方法不是抽象的，也不是本地方法，方法的 Java 代码就会被编译器编译成字节码
    - 即使是空方法，编译器也会生成一条 return 语句，存储在 method_info 结构的 Code 属性中
- 字节码中存放编码后的 Java 虚拟机指令，每条指令都以一个单字节的操作码`opcode`开头

## 指令集
- PC 程序计数器用于存储当前正在执行指令的地址
- 到 JavaSE 8 为止，Java虚拟机规范已经定义了205条指令，操作码分别是 `0(0x00)`到`202(0xCA)` 和 `254(0xFE)`到`255(0xFF)`，这些指令构成了 Java 虚拟机的指令集
- 每条指令都以一个单字节的操作码（opcode）开头，所以Java 虚拟机最多只能支持 256 条指令
- Java 虚拟机使用变长指令，操作码后面可以跟零字节或多字节的操作数（operand）。如果把指令想象成函数的话，操作数就是它的参数
    - 为了让编码后的字节码更加紧凑，很多操作码本身就隐含了操作数，例如：将常数 0 推入操作数栈的指令是 `iconst_0`
- 指令必须知道自己在操作什么类型的数据
    
### 助记符
- 为了方便记忆，Java 虚拟机规范为每个操作码都定义了一个助记符，例如：操作码为`0x00`的这条指令，因为它什么也不做，所以其助记符是`nop(no operation)`
- Java 虚拟机规范定义的指令类型
    - 常量（constants）指令
    - 加载（loads）指令
    - 存储（stores）指令
    - 操作数栈（stack）指令
    - 数学（math）指令
    - 转换（conversions）指令
    - 比较（comparisons）指令
    - 控制（control）指令
    - 引用（references）指令
    - 扩展（extended）指令
    - 保留（reserved）指令
        - 以下三条指令，不允许出现在 class 文件中
        - `0xCA -> 202, breakpoint` 调试器使用，用于实现断点功能
        - `0xFE -> 254, impdep1` Java 虚拟机实现内部使用
        - `0xFF -> 255, impdep2` Java 虚拟机实现内部使用
- 助记符首字母与变量类型对照表
    |            助记符首字母            |  数据类型       |                   示例                    |
    | :------------------------------: | :-----------: | :--------------------------------------: |
    | a                                | reference     | aload, astore, areturn                   |
    | b                                | byte/boolean  | bipush, baload                           |
    | c                                | char          | caload, castore                          |
    | d                                | double        | dload, dstore, dadd                      |
    | f                                | float         | fload, fstore, fadd                      |
    | i                                | int           | iload, istore, iadd                      |
    | l                                | long          | load, lstore, ladd                       |
    | s                                | short         | sipush, sastore                          |

## 解释器