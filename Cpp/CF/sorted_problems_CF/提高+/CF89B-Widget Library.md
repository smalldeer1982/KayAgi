---
title: "Widget Library"
layout: "post"
diff: 提高+/省选-
pid: CF89B
tag: []
---

# Widget Library

## 题目描述

Vasya 编写了一款自己的图形用户界面库，并将其命名为 VTK（VasyaToolKit）。这个库的有趣之处在于控件可以相互嵌套。

在这个库中，一个控件就是图形界面中的一个元素。每个控件都有宽度和高度，占据屏幕上的某个矩形区域。所有控件都是 Widget 类型。为了方便，我们不去区分控件和它的类型。

控件类型 HBox 和 VBox 是 Widget 类型的子类，因此它们同样是 Widget 类型。HBox 和 VBox 是特别的控件，因为它们可以存放其他控件。这两种控件都有一个叫做 pack() 的方法，可以将其他控件直接打包进自身中。它们可以容纳多个控件，甚至可以重复容纳同一个控件——这样它们会分别显示在不同的位置。pack() 方法只保存引用到被打包控件的链接，因此，当被打包的控件发生变化时，作为其宿主的控件中显示的内容也会改变。

如果存在控件链 $ a=c_{1},c_{2},...,c_{k}=b $，且 $ k \geq 2 $，并且对于任何 $ 1 \leq i < k $，$ c_{i} $ 直接打包到 $ c_{i+1} $ 中，那么我们认为控件 $ a $ 被打包在控件 $ b $ 中。Vasya 的库明确禁止控件 $ a $ 打包到自身。任何尝试将控件互相打包到自身的行为都会立即引发错误。

此外，HBox 和 VBox 还有两个参数：border 和 spacing，分别由 set\_border() 和 set\_spacing() 方法设定。默认情况下，这两个参数的值都是 $ 0 $。

上图展示了 HBox 和 VBox 中控件的打包方式。HBox 和 VBox 会根据内部打包控件的大小自动调整自身尺寸。HBox 将控件水平排列，而 VBox 则是垂直排列。spacing 参数决定了相邻控件之间的距离，而 border 参数则决定了围绕所有打包控件的边框宽度。打包的控件按照调用 pack() 方法的顺序排列。如果 HBox 或 VBox 中没有控件被打包，其自身大小将为 $ 0 \times 0 $，与 border 和 spacing 参数无关。

控件都是通过一种脚本语言 VasyaScript 来创建和控制。在输入数据中可以找到这种语言的详细描述。

为了最终验证代码，Vasya 请你编写一个程序，用来计算在 VasyaScript 源代码中所有控件的尺寸。

## 输入格式

第一行是一个整数 $ n $，表示指令的数量（$ 1 \leq n \leq 100 $）。接下来 $ n $ 行，每行包含一条 VasyaScript 的指令。以下是可能的指令类型：

- "Widget [name]([x],[y])" —— 创建一个名称为 [name] 的 Widget 类型控件，宽度为 [x]，高度为 [y]。
- "HBox [name]" —— 创建一个名称为 [name] 的 HBox。
- "VBox [name]" —— 创建一个名称为 [name] 的 VBox。
- "[name1].pack([name2])" —— 将控件 [name2] 打包到控件 [name1] 中。控件 [name1] 必须是 HBox 或 VBox 类型。
- "[name].set\_border([x])" —— 将控件 [name] 的 border 参数设为 [x]。控件 [name] 必须是 HBox 或 VBox 类型。
- "[name].set\_spacing([x])" —— 将控件 [name] 的 spacing 参数设为 [x]。控件 [name] 必须是 HBox 或 VBox 类型。

所有指令行开头和结尾都没有空格，且指令中的单词之间恰好以一个空格分隔。数字与其他部分之间没有空格。

大小写敏感，例如，“wiDget x”是不正确的指令形式。输入数据中的大小写是正确的。

所有控件的名称仅由小写字母组成，长度为 1 到 10 个字符之间，各不相同。脚本中的所有数字均为 $ 0 $ �� $ 100 $ 之间的整数。

保证脚本中所有操作均在控件创建之后进行，且没有控件打包到自身。保证至少有一个控件被创建。

## 输出格式

对于每一个控件，按名称字典序排列，输出其名称、宽度和高度，每个值之间用空格隔开。

提示：输出时请不要在 C++ 中用 %lld 读取或输出 64 位整数。建议使用 cout 流（也可以用 %I64d 特殊符）。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
12
Widget me(50,40)
VBox grandpa
HBox father
grandpa.pack(father)
father.pack(me)
grandpa.set_border(10)
grandpa.set_spacing(20)
Widget brother(30,60)
father.pack(brother)
Widget friend(20,60)
Widget uncle(100,20)
grandpa.pack(uncle)

```

### 输出

```
brother 30 60
father 80 60
friend 20 60
grandpa 120 120
me 50 40
uncle 100 20

```

## 样例 #2

### 输入

```
15
Widget pack(10,10)
HBox dummy
HBox x
VBox y
y.pack(dummy)
y.set_border(5)
y.set_spacing(55)
dummy.set_border(10)
dummy.set_spacing(20)
x.set_border(10)
x.set_spacing(10)
x.pack(pack)
x.pack(dummy)
x.pack(pack)
x.set_border(0)

```

### 输出

```
dummy 0 0
pack 10 10
x 40 10
y 10 10

```

