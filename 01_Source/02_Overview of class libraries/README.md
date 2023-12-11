# 类库概述

## 宏定义

### Q_DECL_OVERRIDE

在类定义中，用于重载有关虚函数，使用Q_DECL_OVERRIDE宏后，如果重载的虚函数没有进行任何重载操作，编译器会报错。

### Q_DECL_IMPORT和Q_DECL_EXPORT

在使用或设计共享库时，用于导入或导出库的内容

### Q_DECL_FINNAL

将虚函数定义为最终级别，不能再被重载，或定义一个类不能再被继承

### Qt_NO_DEBUG_OUTPUT

在debugger窗体显示信息，如果设置该宏则不作任何输出



 

# 容器类的迭代

## foreach关键字

如果只想遍历容器类中所有的项，可以用foreach关键字

头文件**\<QtGlobal\>**