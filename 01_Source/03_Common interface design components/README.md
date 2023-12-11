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

## QSpinBox的使用

| 属性名称           | 描述                                                    |
| ------------------ | ------------------------------------------------------- |
| prefix             | 数字显示的前缀                                          |
| suffix             | 数字显示的后缀                                          |
| minimum            | 数字范围的最小值                                        |
| maximum            | 数字范围的最大值                                        |
| singlestep         | 单步改变值                                              |
| value              | 当前显示的值                                            |
| displayIntegerBase | QSpinBox特有属性，显示整数使用的进制，例如2就表示二进制 |
| decimals           | QDoubleSpinBox特有属性，显示数值的小数位数，            |
|                    |                                                         |

