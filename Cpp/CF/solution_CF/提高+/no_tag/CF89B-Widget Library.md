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

# 题解

## 作者：Ag2WO4 (赞：0)

#### 前排提示：这是一篇 Python 题解！
中等规模模拟一道，码量不大。[一遍过](https://codeforces.com/contest/89/submission/280758489)。
#### 先放代码：
```python
a={}
from functools import*
for i in range(int(input())):
    exec('a['+str(input().split()[::-1])[1:-1]
    .replace(', ',' ').replace('(',"']=[")
    .replace(")' 'Widget'",',0,[]]')
    .replace(" 'VBox'",']=[0,0,1,[]]')
    .replace(" 'HBox'",']=[0,0,2,[]]')
    .replace(".pack']=[","'][3].append('")
    .replace(".set_border']=[","'][0]=")
    .replace(".set_spacing']=[","'][1]=")
    .replace(")'","')").replace("0')",'0')
    .replace("1')",'1').replace("2')",'2')
    .replace("3')",'3').replace("4')",'4')
    .replace("5')",'5').replace("6')",'6')
    .replace("7')",'7').replace("8')",'8')
    .replace("9')",'9'))
@lru_cache(maxsize=None)
def f(i):
    return[a[i][:2],
    [max(f(i)[0]for i in a[i][3])+2*a[i][0],
    sum(f(i)[1]for i in a[i][3])+2*a[i][0]+(len(a[i][3])-1)*a[i][1]]
    if a[i][3]else[0,0],
    [sum(f(i)[0]for i in a[i][3])+2*a[i][0]+(len(a[i][3])-1)*a[i][1],
    max(f(i)[1]for i in a[i][3])+2*a[i][0]]
    if a[i][3]else[0,0]][a[i][2]]
for i in sorted([i]+f(i)for i in a):print(*i)
```
#### 讲解：
本题使用一波流带走的写法。首先构建模型，字典里每个框都有四个属性：边框、间隔（对于单个框为横纵坐标）、类型、包含的框。使用字符串编辑和 ```exec()``` 函数的方法即可，如第一个样例将被编辑为：
```python
a['me']=[50,40,0,[]]
a['grandpa']=[0,0,1,[]]
a['father']=[0,0,2,[]]
a['grandpa'][3].append('father')
a['father'][3].append('me')
a['grandpa'][0]=10
a['grandpa'][1]=20
a['brother']=[30,60,0,[]]
a['father'][3].append('brother')
a['friend']=[20,60,0,[]]
a['uncle']=[100,20,0,[]]
a['grandpa'][3].append('uncle')
```
统计框最终大小时，依题意递归遍历包含的框，平铺边为长度和加间隔的包含数量减一倍加两倍边框，对齐边为最长长度加两倍边框。排序输出即可。因为框的大小和遍历顺序无关，使用记忆化搜索优化。

---

