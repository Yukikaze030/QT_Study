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

## QTableWidget的使用

### QTableWidget操作

每个单元格都是一个**QTableWidgetItem**对象，QTableWidgetItem对象存储了单元格的所有内容，包括字标题、格式设置，以及关联的数据。

创建QTableWidgetItem的构造原型为:

QTableWidgetItem::QTableWidgetItem(const QString &text,int type =Type)

第一个参数为单元格显示文字，第二个参数为节点类型

```C++
    //姓名
    item = new QTableWidgetItem(Name,MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    StudID +=rowNo;//学号=学号基数+行数
    item->setData(Qt::UserRole,QVariant(StudID));//设置studID为data
    ui->tableInfo->setItem(rowNo,MainWindow::colName,item);
```

“姓名”单元格还调用了setData设置了一个自定义数据，存储的是学生ID。

自定义数据是不显示在界面上的，但是与单元格相关联。表格并没有显示学号，学号是“姓名”单元格的关联数据(类似Map?单元格是Map，setData(Key,Value)?)



获取单元格数据

当鼠标单击单元格时，被选择的单元格为当前单元格。通过QTableWidget的currentColumn()和2currentRow()可以获得当前单元格的列编号和行编号。

当单元格发生切换时，会发射currentCellChanged()信号和currentItemChanged()信号，两个信号都可以利用,只是传递的参数不同。

#### 自动调整行高和列宽

 QTableWidget有几个函数自动调整表格的行高和列宽，分别如下。

|               函数名               |                描述                |
| :--------------------------------: | :--------------------------------: |
|     resizeColumnsToContents()      | 自动调整所有列的宽度，以适应其内容 |
| resizeColumnToContents(int column) |   自动调整列号为column的列的宽度   |
|       resizeRowsToContents()       | 自动调整所有行的高度，以适应其内容 |
|    resizeRowToContents(int row)    |    自动调整行号为row的行的高度     |

以上函数均为**QTableWidget**的父类，**QTableView**的函数

#### 间隔行底色

setAlternatingRowColors()函数可以设置表格的行是否使用交替底色显示，若为交替底色，测间隔的一行会用灰色作为底色。具体底色的设置需要用styleSheet

## 杂项备注

### 拆分器

splitter

![image-20240202093802403](.picture/拆分器.png)