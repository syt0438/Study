## 控制指令
- 控制指令共 11 条
- `goto` 指令，用于无条件跳转
- `jsr, ret` 指令，用于在 Java 6 之前实现 finally 子句，从 Java 6 开始，Oracle 的 Java 编译器已经不再使用这两条指令
- `tableswitch, lookupswitch` 指令，用于 switch 条件跳转，如果 case 值可以编码成一个索引表，则实现为 tableswitch 指令；否则则实现为 lookupswitch 指令
    - 注意：操作码之后跟 `0-3` 个字节的内存填充，以保证 defaultOffset 在字节码中的地址是 4 的倍数
    ``` java
    /** tableswitch */
    int chooseNear(int i) {
        switch (i) {
            case 0: return 0;
            case 1: return 1;
            case 2: return 2;
            default: return -1;
        }
    }
  
    /** lookupswitch */
    int chooseFar(int i) {
        switch (i) {
            case -100: return -1;
            case 0: return 0;
            case 100: return 1;
            default: return -1;
        }
    }
    ``` 
- `return, ireturn, lreturn, freturn, dreturn, areturn` 指令，用于从方法调用中返回相应类型的数值