---
title: "Affine Mess"
layout: "post"
diff: 难度0
pid: UVA1102
tag: []
---

# Affine Mess

## 题目描述

[![](https://img.shields.io/badge/题目-UVA1102_Affine_Mess-green)
![](https://img.shields.io/badge/难度-暂无评定（省选/NOI−）-purple)
![](https://img.shields.io/badge/题库-UVA-blue)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/UVA1102)
[![](https://img.shields.io/badge/翻译-wangbinfeng(387009)-yellow)](https://www.luogu.com.cn/user/387009)

------------

### 题目大意
在平面直角坐标系种有一个边长为 $20$ 的正方形（它的中心是原点），其中有三个点，记为 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$。

先对整个图形整体进行旋转，**如果有小数部分则四舍五入**。

然后对整个图形进行放缩和平移（顺序未知）。放缩的中心是 $O(0,0)$。放缩对于 $x$ 轴和 $y$ 轴的比例可以不同。但是，**放缩比例和平移量均必须是整数**。

现在另给出三个点 $(a_1,b_1),(a_2,b_2),(a_3,b_3)$，并不知道对应原本的哪个点，请问是否有可能是由原本的三个点经过上述变换得到的？如果是，请问多种变换等价吗？

## 输入格式

输入包括多组数据。每组数据包含 $6$ 个数对，分别是 $(x_1,y_1),(x_2,y_2),(x_3,y_3),(a_1,b_1),(a_2,b_2),(a_3,b_3)$，前三组和后三组分别保证两两不同。

结束标志为 $6$ 个 $0$。

## 输出格式

对于每组数据：
1. 如果全部等价，输出 `no solution`。
2. 如果有解但不等价，输出 `inconsistent solutions`。
3. 如果有解且等价，输出 `equivalent solutions`。


### 样例
输入样例：
```
3 0 4 0 1 4
-2 -4 -1 3 3 -4
0 1 1 1 2 1
1 2 2 2 3 2
1 0 2 0 3 0
3 3 1 1 2 2
1 0 2 0 3 0
3 2 1 1 2 2
2 3 0 6 1 2
2 3 0 6 1 2
0 0 0 0 0 0
```
输出样例：
```
Case 1: equivalent solutions
Case 2: inconsistent solutions
Case 3: no solution
Case 4: inconsistent solutions
Case 5: equivalent solutions
```

------------
> 翻译提供者：[@wangbinfeng(387009)](https://www.luogu.com.cn/user/387009)

