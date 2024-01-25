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

| 属性名称           | 描述                                                           |
| ------------------ | -------------------------------------------------------------- |
| prefix             | 数字显示的前缀                                                 |
| suffix             | 数字显示的后缀                                                 |
| minimum            | 数字范围的最小值                                               |
| maximum            | 数字范围的最大值                                               |
| singlestep         | 单步改变值                                                     |
| value              | 当前显示的值                                                   |
| displayIntegerBase | QSpinBox特有属性，显示整数使用的进制，例如2就表示二进制        |
| decimals           | QDoubleSpinBox特有属性，显示数值的小数位数，例如2就显示2为小数 |

## 其他数值输入和显示组件

## 时间日期与定时器

## QComboBox和QPlainTextEdit

### 右键菜单绑定

```C++
setContextMenuPolicy(Qt::CustomContextMenu);

```

## QListWidget和QToolButton

Item Views基于模型/视图(Model/View)结构，视图与模型数据关联实现数据的显示和编辑

### QToolButton

QToolButton有setMenu()函数，可以为其设置一个下拉式菜单

### QToolBox

currentIndex 当前分组编号

currentItemText 当前分组的标题

currentItemName 当前分组的对象名称

currentItemIcon 为当前分组设置一个图标，显示在文字标题的左侧

在一个ToolBox内可以放置任何界面组件，并设置为Grid布局。不要使用水平布局，因为使用水平布局时，组内的ToolButton按键都是自动向左靠齐的，而使用Grid布局时，自动居中。

### QListWidget操作

```c++
    if(chk)//可编辑
    {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
    else//不可编辑
    {
        aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
```

## QTreeWidget和QDockWidget

### QDockWidget组件属性设置

allowedAreas熟悉，设置允许停靠区域
| QDockWidget::DockWidgetFeature          | 枚举                       |
| --------------------------------------- | -------------------------- |
| QDockWidget::DockWidgetClosable         | 停靠区可关闭               |
| QDockWidget::DockWidgetMovable          | 停靠区可移动               |
| QDockWidget::DockWidgetFloatable        | 停靠区可浮动               |
| QDockWidget::DockWidgetVerticalTitleBar | 在停靠区左侧显示垂直标题栏 |
| QDockWidget::AllDockWidgetFeatures      | 使用以上所有特征           |
| QDockWidget::NoDockWidgetFeatures       | 不能停靠、移动和关闭       |

### QTreeWidget

```c++
int topLevelItemCount();//返回顶层节点个数
QTreeWidgetItem* topLevelItem(int index);//返回序号为index的顶层节点
```

### QLable和QPixmap显示图片

| QPixmap scaledToHeight(int height)   | 返回一个缩放后的图片副本，图片缩放到一个高度height           |
| ------------------------------------ | ------------------------------------------------------------ |
| QPixmap scaledToWidth(int width)     | 返回一个缩放后的图片副本，图片缩放到一个宽度width            |
| QPixmap scaled(int width,int height) | 返回一个缩放后的图片副本，图片缩放到宽度width和高度height,缺省为不保持比例 |

在QLabel上显示图片，使用QLabel的setPixmap(const QPixmap &)函数