# 常用界面设计组件

## 字符串与输入输出(Test1)

### 字符串与数值之间的转换

```C++
int QString::toInt(bool *OK = Q_NULLPTR,int base = 10) const
long QString::toLong(bool *OK = Q_NULLPTR,int base = 10) const
short QString::toShort(bool *OK = Q_NULLPTR,int base = 10) const
uint QString::toUInt(bool *OK = Q_NULLPTR,int base = 10) const
ulong QString::toULONG(bool *OK = Q_NULLPTR,int base = 10) const
```

### 保留小数

以保留两位小数为例

```C++
QString str;
float total;
str = QString::number(total,'f',2);
str = QString::asprintf("%.2f",total);
str = str.setNum(total,'f',2);
str = str.sprintf("%.2f",total);
```

## QString的常用功能