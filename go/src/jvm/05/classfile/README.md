
## class 文件
- Java 虚拟机规范所指的 class 文件，并非特指位于磁盘中的 .class 文件，而是泛指任何格式符合规范的 class 数据
- 构成 class 文件的基本数据单位是字节，可以把整个 class 文件当成一个字节流来处理
- 为了描述 class 文件格式，Java 虚拟机规范定义了u1, u2, u4 三种数据类型来表示 1,2,4 字节的无符号整数，分别对应Go语言的 uint8, uint16, uint32 类型
- 相同类型的多条数据一般按表 table 的形式存储在 class 文件中
    - 表由表头和表项 item 构成，表头是 u2 或 u4 的整数。假设表头是n，后面就紧跟着 n 个表项数据
- 魔法值
    - 概述：很多文件格式都会规定满足该格式的文件必须以某几个固定字节开头，这几个字节主要起标识作用，叫做魔法值
    - 例如：
        - PDF 文件以 4 字节的 %PDF (0x25, 0x50, 0x44, 0x46) 开头
        - ZIP 文件以 2 字节的 PK (0x50, 0x4B) 开头
    - Class 文件以 4 字节的 CAFEBABE 开头，Java 虚拟机规定，如果加载的 class 文件不符合要求的格式，Java 虚拟机实现就需要抛出 java.lang.ClassFormatError 异常
- 版本号
    - 魔法数之后，是 class 文件的次版本号和主版本号，都是 u2 类型
    - 例如：某 class 文件的主版本号是 M，次版本号是 m，那么完整的版本号就可以表示成 "M.m"形式
    - 注意：
        - 主版本号在 J2SE 1.2 之前都是 45，从 1.2 开始，每次有大的 Java 版本发布，都会加 1
        - 次版本号只在 J2SE 1.2 之前用过，从 J2SE 1.2 开始就没有再使用了，其值都是 0
        - 特定的 Java 虚拟机实现只能支持版本号在某个范围内的 class 文件，比如 Java SE8 支持的版本为 45.0 ~ 52.0 的 class 文件，如果版本号不支持则抛出 java.lang.UnsupportedClassVersionError 异常        
- 常量池
    - 版本号之后，是常量池
    - 常量池是表数据，并且常量是 Java 虚拟机规范严格定义的，共 14 钟
        - 注意项
            1. 表头给出的常量池大小比实际大 1
            2. 有效的常量池索引范围是 1 ~ n-1，0 是无效索引，表示不指向任何常量
            3. **CONSTANT_Long_info 和 CONSTANT_Double_info 各占两个位置，也就是说，如果常量池中存在这两种常量，那么实际的常量数量比 n-1 还要少，而且 1 ~ n-1 的某些数也会变成无效索引**
    - 常量池表中的所有项都具有如下通用格式
        ```
        cp_info {
            u1      tag;
            u1      info[];
        }
        ```
    - 常量数据的第一个字节是 tag，用于区分常量类型，每个 tag 字节之后，必须有两个或更多的字节，这些字节用于指定这个常量的信息
    - 常量池中的常量分为两类：字面量类（数字、字符串常量）和符号引用类（类名、接口名、字段和方法信息等）
        - 符号引用类的常量都是通过索引直接或间接的指向 CONSTANT_Utf8_info 常量
    - 常量结构
        - Java 虚拟机规范一共定义了 14 中常量类型
            ```
            const (
                CONSTANT_Class             = 7
                CONSTANT_Fieldref          = 9
                CONSTANT_Methodref         = 10
                CONSTANT_InterfaceMetodref = 11
                CONSTANT_String            = 8
                CONSTANT_Integer           = 3
                CONSTANT_Float             = 4
                CONSTANT_Long              = 5
                CONSTANT_Double            = 6
                CONSTANT_NameAndType       = 12
                CONSTANT_Utf8              = 1
                CONSTANT_MethodHandle      = 15
                CONSTANT_MethodType        = 16
                CONSTANT_InvokeDynamic     = 18
            )
            ```
        - CONSTANT_Integer_info 使用 4 个字节，存储整数常量
            - CONSTANT_Integer_info 正好可以容纳一个 Java 的 int 型常量，但实际上比 int 小的 boolean、byte、short 和 char 类型的常量，也存储在 CONSTANT_Integer_info 中
            ```
            CONSTANT_Integer_info {
                u1      tag;
                u4      bytes;
            } 
            ```
        - CONSTANT_Float_info 使用 4 个字节，存储 IEEE754 单精度浮点数常量
            ```
            CONSTANT_Float_info {
                u1      tag;
                u4      bytes;
            }
            ```
        - CONSTANT_Long_info 使用 8 个字节，存储 Java 的 long 类型整数常量
            ```
            CONSTANT_Long_info {
                u1      tag;
                u4      high_bytes;
                u4      low_bytes;
            }
            ```
        - CONSTANT_Double_info 使用 8 个字节，存储 IEEE754 双精度浮点数常量
            ```
            CONSTANT_Long_info {
                u1      tag;
                u4      high_bytes;
                u4      low_bytes;
            }
            ```
        - CONSTANT_Utf8_info 常量，用于存放 MUTF-8 编码的字符串
            - Java 序列化机制也使用了 MUTF-8 编码。java.io.DataInput 和 java.io.DataOutput 接口分别定义了readUTF() 和 writeUTF() 方法，可以读写 MUTF-8 编码的字符串
            - 注意项
                - 字符串在 class 文件中是以 MUTF-8 (Modified UTF-8) 方式进行编码的（为什么没有用标准的 UTF-8 编码方式，未找到明确的原因）
                - MUTF-8 与 UTF-8 编码大致相同，但并不兼容，区别如下：
                    1. null （代码点 U+0000）字符，会被编码成 2 字节(0xC0, 0x80)
                    2. 补充字符（Supplementary Characters，代码点大于 U+FFFF 的 Unicode 字符），是按照 UTF-16 拆分为代理对（Surrogate Pair）分别编码的
            ```
            CONSTANT_Utf8_info {
                u1      tag;
                u2      length;
                u1      bytes[length];
            }            
            ```
        - CONSTANT_String_info 常量，用于表示 java.lang.String 字面量
            - CONSTANT_String_info 常量本身并不存储字符串数据，而是存放了一个常量池索引，这个索引指向一个 CONSTANT_Utf8_info 常量
            ```
            CONSTANT_String_info {
                u1      tag;
                u2      string_index;
            }
            ```
        - CONSTANT_Class_info 常量，用于表示类或接口的符号引用
            - 接口表中的接口索引，指向的都是 CONSTANT_Class_info 常量
            - CONSTANT_Class_info 常量本身并不存储数据，而是存放了一个常量池索引，这个索引指向一个 CONSTANT_Utf8_info 常量
            ```
            CONSTANT_Class_info {
                u1      tag;
                u2      name_index;
            }
            ```
        - CONSTANT_NameAndType_info 常量，用于给出字段或方法的名称和描述符
            - 通过 CONSTANT_Class_info 和 CONSTANT_NameAndType_info，可以唯一确定一个字段或方法
            - name_index 和 descriptor_index 都是常量池索引，指向 CONSTANT_Utf8_info 常量
            - 描述符规则定义：Java 虚拟机规范定义了一种简单的语法来描述字段和方法
                1. 类型描述符
                    - 基础类型的描述符：`单个字母表示`
                        - `boolean -> Z`
                        - `byte -> B`
                        - `short -> S`
                        - `char -> C`
                        - `int -> I`
                        - `long -> J`
                        - `float -> F`
                        - `double -> D`
                    - 引用类型描述符：`L + 类的完全限定名 + ;`
                    - 数组类型描述符：`[ + 数组元素的类型描述符`
                2. 字段描述符：`字段类型的描述符` 
                3. 方法描述符：`( + 参数类型描述符列表 + ) + 返回值类型描述符`，其中 void 返回值类型由单个字母 V 表示
            ```
            CONSTANT_NameAndType_info {
                u1      tag;
                u2      name_index;
                u2      descriptor_index;          
            }
            ```
        - CONSTANT_Fieldref_info 常量，用于表示`字段符号引用`
            - CONSTANT_Methodref_info 结构中的 class_index 项，表示的是类或者接口
            ```
            CONSTANT_Fieldref_info {
                u1      tag;
                u2      class_index;
                u2      name_and_type_index;
            }
            ```
        - CONSTANT_Methodref_info 常量，用于表示`普通（非接口）方法符号引用`
            - CONSTANT_Methodref_info 结构中的 class_index 项，表示的必须是类
            - 如果一个 CONSTANT_Methodref_info 结构的方法名以 `<` 开头，那么该方法名必须是特殊的 `<init>` 实例初始化方法
            ```
            CONSTANT_Methodref_info {
                u1      tag;
                u2      class_index;
                u2      name_and_type_index;
            }
            ```
        - CONSTANT_InterfaceMethodref_info 常量，用于表示`接口方法符号引用`
            - CONSTANT_InterfaceMethodref_info 结构中的 class_index 项，表示的必须是接口
            ```
            CONSTANT_InterfaceMethodref_info {
                u1      tag;
                u2      class_index;
                u2      name_and_type_index;
            }
            ```
        - CONSTANT_MethodHandle_info 常量，用于表示方法句柄
            - reference_kind 项的值必须在 1-9 范围之内，它表示方法句柄的类型。方法句柄的类型决定句柄的字节码行为
            - reference_index 项的值必须是对常量池表的有效索引，该位置上的常量池表项，必须符合下列规则：
                - 如果 reference_kind 项的值为 1（REF_getField）、2（REF_getStatic）、3（REF_putField）、4（REF_putStatic），那么 reference_index 索引处的成员必须是 CONSTANT_Fieldref_info 结构
                    - 此结构表示某个字段，本方法句柄正是为这个字段而创建的
                - 如果 reference_kind 项的值为 5（REF_invokeVirtual）、8（REF_newInvokeSpecial），那么 reference_index 索引处的成员必须是 CONSTANT_Methodref_info 结构
                    - 此结构表示类中的某个方法或构造器，本方法句柄正是为这个方法或构造器而创建的
                - 如果 reference_kind 项的值为 6（REF_invokeStatic）、7（REF_invokeSpecial）
                    - 并且如果 class 文件的版本号小于 `52.0`，那么 reference_index 索引处的成员必须是 CONSTANT_Methodref_info 结构
                        - 此结构表示类中的某个方法，本方法句柄正是为这个方法而创建的
                    - 并且如果 class 文件的版本号大于等于 `52.0`，那么 reference_index 索引处的成员必须是 CONSTANT_Methodref_info 或 CONSTANT_InterfaceMethodref_info 结构
                        - 此结构表示类或接口中的某个方法，本方法句柄正是为这个方法而创建的
                - 如果 reference_kind 项的值为 9（REF_invokeInterface）那么 reference_index 索引处的成员必须是 CONSTANT_InterfaceMethodref_info 结构
                    - 此结构表示接口中的某个方法，本方法句柄正是为这个方法而创建的
                - 如果 reference_kind 项的值为 5（REF_invokeVirtual）、6（REF_invokeStatic）、7（REF_invokeSpecial）、9（REF_invokeInterface），那么由 CONSTANT_Methodref_info 或 CONSTANT_InterfaceMethodref_info 结构所表示的方法，名称不能为 `<init> 或 <clinit>`
                - 如果 reference_kind 项的值为 8（REF_newInvokeSpecial），那么由 CONSTANT_Methodref_info 结构所表示的方法，名称必须为 `<init>`
            ```
            CONSTANT_MethodHandle_info {
                u1      tag;
                u1      reference_kind;
                u2      reference_index;
            }
            ```
        - CONSTANT_MethodType_info 常量，用于表示方法的描述符
            ```
            CONSTANT_MethodType_info {
                u1      tag;
                u2      descriptor_index;
            }
            ```
        - CONSTANT_InvokeDynamic_info 常量，用于表示 `invokedynamic 指令`所用到的引导方法、引导方法所用到的动态调用名称、参数和返回类型，并可以给引导方法传入一系列静态参数的常量
            - bootstrap_method_attr_index 项的值，必须是对当前 class 文件中引导方法表的 bootstrap_methods 数组的有效索引
            ```
            CONSTANT_InvokeDynamic_info {
                u1      tag;
                u2      bootstrap_method_attr_index;
                u2      name_and_type_index;
            }
            ```
- 类访问标志
    - 版本号之后，是类访问标志，是 u2 类型
    - 类访问标志，是一个 16 位的 "bitmask"，用于表示某个类或者接口的访问权限及属性
    - ACC_INTERFACE 标志必须与 ACC_ABSTRACT 标志同时出现，并且不能再有其它标志
    - ACC_FINAL 标志不能与 ACC_ABSTRACT 标志同时出现
    - ACC_SUPER 标志用于确定类或接口里面的 invokespecial 指令使用哪一种执行语义
        - 针对 Java 虚拟机指令集的编译器都应当设置这个标志
        - ACC_SUPER 标志，是为了向后兼容由旧 Java 编译器所编译的代码而设计的，目前的 ACC_SUPER 标志在由 JDK 1.0.2 之前的编译器所生成的 access_flags 中是没有确定含义的
        - 在 JDK 1.0.2 之后编译出的 class 文件都带有 ACC_SUPER 标志
        - 从 Java SE 8 以后，无论 class 文件中这个标志的实际值是什么，也不管 class 文件的版本号是多少，Java 虚拟机都会默认每个 class 文件均设置了 ACC_SUPER 标志
    - ACC_SYNTHETIC 标志，表示该类或接口是由编译器生成的，而不是由源代码生成的
        - 注解类型，必须设置 ACC_SYNTHETIC 标志
        - ACC_SYNTHETIC 标志必须与 ACC_INTERFACE 标志同时出现
    - ACC_ENUM 标志，表示该类或其父类为枚举类型    
    
- 类和直接超类索引
    - 类访问标志之后是两个 u2 类型的常量池索引，分别给出类名和超类名
    - 常量池在类索引处的成员必须为 CONSTANT_Class_info 结构，该结构体表示这个 class 文件所定义的类或接口
    - 二进制名(binary names)：class 文件存储的类名叫做二进制名，类似于完全限定名，但是把点换成了斜线
    - thisClass: 因为每个类都有名字，所以 thisClass 必须是有效的常量池索引
    - superClass: 除了 java.lang.Object 之外，其他类都有超类，所以 superClass 只在 thisClass 是 Object 类时，值为 0，在其它的 class 文件中必须是有效的常量池索引
- 接口索引表
    - 类和超类之后，是接口索引表
    - 接口索引表中存放的是常量池索引，常量池在索引处的成员必须为 CONSTANT_Class_info 结构，给出该类实现的所有直接超接口
    - 在接口表中，各成员所表示的接口顺序和对应的源代码中给定的接口顺序（从左至右）一样，即接口表[0] 对应的是源代码中最左边的接口
- 字段表
    - 接口索引表之后，是字段表
    - 字段表中的每个成员都必须是一个 field_info 结构的数据项，用于表示当前类或接口中某个字段的完整描述
    - 字段表描述当前类或接口声明的所有字段，但不包括从父类或父接口中继承的字段
    - 字段表用于存储字段信息，字段和类一样，具有自己的访问标志
    - 字段访问标志之后，是一个常量池索引，用于给出字段名
    - 字段名索引之后，是一个常量池索引，用于给出字段的描述符
    - 字段描述符之后，是属性表
    - Java 虚拟机规范给出的`字段结构定义`
        ```
        field_info {
            u2                      access_flags;
            u2                      name_index;
            u2                      descriptor_index;
            u2                      attributes_count;
            attribute_info          attributes[attributes_count];
        }
        ```
- 方法表
    - 字段表之后，是方法表
    - 方法表中的每个成员都必须是一个 method_info 结构，用于表示当前类或接口中某个方法的完整描述
    - 如果某个 method_info 结构的 access_flags 项既没有设置 ACC_NATIVE 标志也没有设置 ACC_ABSTRACT 标志，那么该结构中也应该包含实现这个方法所用的 Java 虚拟机指令
    - 方法表描述当前类或接口中声明的方法，但不包括从父类或父接口中继承的字段
    - method_info 结构可以表示类和接口中定义的所有方法，包括实例初始化方法、实例方法、类方法、类或接口初始化方法
    - 方法表用于存储方法信息，方法和类一样，具有自己的访问标志
    - 方法访问标志之后，是一个常量池索引，用于给出方法名
    - 方法名索引之后，是一个常量池索引，用于给出方法的描述符
    - 方法描述符之后，是属性表
    - Java 虚拟机规范给出的`方法结构定义`
        ```
        method_info {
            u2                      access_flags;
            u2                      name_index;
            u2                      descriptor_index;
            u2                      attributes_count;
            attribute_info          attributes[attributes_count];
        }
        ```
- 属性表
    - 方法表之后，是属性表
    - 属性表中的每一项都是一个 attribute_info 结构，用于存储方法的字节码等信息
    - Java 虚拟机规范没有严格规范属性类型。属性是可以扩展的，不同的虚拟机实现可以定义自己的属性类型
        - 由于这个原因，Java 虚拟机规范没有使用 tag，而是`使用属性名来区分不同的属性`
    - Java 虚拟机明确禁止 Java 虚拟机实现，因为 class 文件中包含新属性而抛出异常或以其它形式拒绝使用 class 文件
    - 属性数据存储于属性名之后的 `u1` 数据表中，这样 Java 虚拟机实现就可以跳过自己无法识别的属性
    - 注意项
        - 属性表中存放的属性名实际上并不是编码后的字符串，而是常量池索引
    - Java 虚拟机规范给出的`属性结构定义`
        ```
        attribute_info {
            u2      attribute_name_index;
            u4      attribute_length;
            u1      info[attribute_length]
        }
        ```
    - Java 虚拟机规范预定义了 23 种属性，这 23 种预定义属性，可以按照用途分为以下三组
        - 第一组属性是实现 `Java 虚拟机`所必需的属性，共有 5 种
        - 第二组属性是 `Java 类库`所必须的属性，共有 12 种
        - 第三组属性（可选的）主要提供给工具使用，共有 6 种
            - 如果 class 文件中存在第三种属性，Java 虚拟机实现或者 Java 类库可以利用它们，比如使用 LineNumberTable 属性在异常堆栈中显示行号 
        - 预定义属性表

            |                 属性名                |  Java SE  | Class 文件  |  分组  |                   位置                    |
            | :----------------------------------  | :-------: | :--------: | :---: | :--------------------------------------: |
            | ConstantValue                        | 1.0.2     |    45.3    |   1   | field_info                               |
            | Code                                 | 1.0.2     |    45.3    |   1   | method_info                              |
            | Exceptions                           | 1.0.2     |    45.3    |   1   | method_info                              |
            | StackMapTable                        | 6         |    50.0    |   1   | Code                                     |
            | BootstrapMethods                     | 7         |    51.0    |   1   | ClassFile                                |
            | SourceFile                           | 1.0.2     |    45.3    |   3   | ClassFile                                |
            | LineNumberTable                      | 1.0.2     |    45.3    |   3   | Code                                     |
            | LocalVariableTable                   | 1.0.2     |    45.3    |   3   | Code                                     |
            | InnerClasses                         | 1.1       |    45.3    |   2   | ClassFile                                |
            | Synthetic                            | 1.1       |    45.3    |   2   | ClassFile, field_info, method_info       |
            | Deprecated                           | 1.1       |    45.3    |   3   | ClassFile, field_info, method_info       |
            | EnclosingMethod                      | 5.0       |    49.0    |   2   | ClassFile                                |
            | Signature                            | 5.0       |    49.0    |   2   | ClassFile, field_info, method_info       |
            | SourceDebugExtension                 | 5.0       |    49.0    |   3   | ClassFile                                |
            | LocalVariableTypeTable               | 5.0       |    49.0    |   3   | Code                                     |
            | RuntimeVisibleAnnotations            | 5.0       |    49.0    |   2   | ClassFile, field_info, method_info       |
            | RuntimeInvisibleAnnotations          | 5.0       |    49.0    |   2   | ClassFile, field_info, method_info       |
            | RuntimeVisibleParameterAnnotations   | 5.0       |    49.0    |   2   | method_info                              |
            | RuntimeInvisibleParameterAnnotations | 5.0       |    49.0    |   2   | method_info                              |
            | AnnotationDefault                    | 5.0       |    49.0    |   2   | method_info                              |
            | RuntimeVisibleTypeAnnotations        | 8         |    52.0    |   2   | ClassFile, field_info, method_info, Code |
            | RuntimeInvisibleTypeAnnotations      | 8         |    52.0    |   2   | ClassFile, field_info, method_info, Code |
            | MethodParameters                     | 8         |    52.0    |   2   | method_info                              |
        
        - 属性解析
            - LineNumberTable、LocalVariableTable 和 SourceFile 属性都属于调试信息，非运行时所必需属性，可以通过 javac -g:none 选项来关闭这些信息的生成
            - Deprecated 和 Synthetic 属性
                - JDK 1.1 引入，仅起标记作用，不包含任何数据
                - 可以出现在 ClassFile、field_info 和 method_info 结构中
                - Deprecated 属性用于指出类、接口、字段或方法已经不建议使用，编译器等工具可以根据 Deprecated 属性输出警告信息
                - Synthetic 属性是为了支持内部类和接口而引入的，如果一个类成员没有在源文件中出现，则必须标记带有 Synthetic 属性，或者设置 ACC_SYNTHETIC 标志。
                    - 注意：唯一的例外是某些与人工实现无关、由编译器自动产生的方法，也就是指 Java 语言默认的实例初始化方法、类初始化方法、Enum.values 和 Enum.valueOf 方法
                ```
                Deprecated_attribute {
                    u2      attribute_name_index;
                    u4      attribute_length;
                }
              
                Synthetic_attribute {
                    u2      attribute_name_index;
                    u4      attribute_length;
                }
                ```
                   
            - SourceFile 属性
                - 可选定长属性，只会出现在 ClassFile 结构中，用于指出源文件名称，属于调试信息
                - attribute_length 必须是 2，sourcefile_index 常量池索引，指向 CONSTANT_Utf8_info 常量
                ```
                SourceFile_attribute {
                    u2      attribute_name_index;
                    u4      attribute_length;
                    u2      sourcefile_index;
                }
                ```
            - ConstantValue 属性
                - 定长属性，只会出现在 field_info 结构中，用于表示常量表达式的值
                - attribute_length 必须是 2，constantvalue_index 是常量池索引，但具体指向哪种常量因字段类型而异
                ```
                ConstantValue_attribute {
                    u2      attribute_name_index;
                    u4      attribute_length;
                    u2      constant_value_length;
                }
                ```
            - Code 属性
                - 变长属性，只会出现在 method_info 结构中，用于存放字节码等方法相关信息
                ```
                Code_attribute {
                    u2                  attribute_name_index;
                    u4                  attribute_length;
                    u2                  max_stack; // 操作数栈的最大深度
                    u2                  max_locals; // 局部变量表的大小
                    u4                  code_length; // 字节码信息，表头
                    u1                  code[code_length] // 字节码信息，表项
                    u2                  exception_table_length;
                    {
                        u2              start_pc;
                        u2              end_pc;
                        u2              handle_pc;
                        u2              catch_type;
                    } exception_table[exception_table_length];
                    u2                  attributes_count;
                    attribute_info      attributes[attributes_count];                  
                }
                ```
            - LineNumberTable 属性
                - 可选变长属性，位于 Code 属性的属性表中，用于存放方法的行号信息，属于调试信息
                ```
                LineNumberTable_attribute {
                    u2      attribute_name_index;
                    u4      attribute_length;
                    u2      line_number_table_length;
                    {
                        u2      start_pc;
                        u2      line_number;
                    } line_number_table[line_number_table_length];
                }
                ```
            - LocalVariableTable 属性
                - 可选变长属性，位于 Code 属性的属性表中，用于存放方法的局部变量信息，属于调试信息
                ```
                LocalVariableTable_attribute {
                    u2      attribute_name_index;
                    u4      attribute_length;
                    u2      local_variable_table_length;
                    {
                        u2      start_pc;
                        u2      length;
                        u2      name_index;
                        u2      descriptor_index;
                        u2      index;
                    } local_variable_table[local_variable_table_length];
                }
                ```
            - Exceptions 属性
                - 变长属性，位于 method_info 结构的属性表中，用于记录方法抛出的异常信息表
                - 一个 method_info 结构的属性表中，最多只能有一个 Exceptions 属性
                ```
                Exceptions_attribute {
                    u2      attribute_name_index;
                    u4      attribute_length;
                    u2      number_of_exceptions;
                    u2      exception_index_table[number_of_exceptions];
                }
                ```

### class 文件结构
* Java 虚拟机规范使用一种类 C 的结构体语法来描述 class 文件格式，整个 class 文件被描述为一个 ClassFile 结构

```
ClassFile {
    u4                      magic;
    u2                      minor_version;
    u2                      major_version;
    u2                      constant_pool_count;
    cp_info                 constant_pool[constant_pool_count - 1];
    u2                      access_flags;
    u2                      this_class;
    u2                      super_class;
    u2                      interface_count;
    u2                      interfaces[interface_count];
    u2                      fields_count;
    field_info              fields[fields_count];
    u2                      methods_count;
    method_info             methods[methods_count];
    u2                      attributes_count;
    attribute_info          attributes[attributes_count];    
}
```
 
### class 文件结构的成员顺序
> 1. major
> 2. minor_version
> 3. major_version
> 4. constant_pool
> 5. access_flags
> 6. this_class
> 7. super_class
> 8. interfaces
> 9. fields
> 10. methods
> 11. attributes