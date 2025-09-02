# 题目信息

# 4-point polyline

## 题目描述

You are given a rectangular grid of lattice points from $ (0,0) $ to $ (n,m) $ inclusive. You have to choose exactly 4 different points to build a polyline possibly with self-intersections and self-touching. This polyline should be as long as possible.

A polyline defined by points $ p_{1},p_{2},p_{3},p_{4} $ consists of the line segments $ p_{1}p_{2},p_{2}p_{3},p_{3}p_{4} $ , and its length is the sum of the lengths of the individual line segments.

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1 1
0 0
1 0
0 1
```

## 样例 #2

### 输入

```
0 10
```

### 输出

```
0 1
0 10
0 0
0 9
```

# AI分析结果

### 题目内容
# 四点折线

## 题目描述
给定一个包含从\((0, 0)\)到\((n, m)\)的格点的矩形网格。你必须恰好选择4个不同的点来构建一条可能有自交和自接触的折线。这条折线应尽可能长。

由点\(p_1\)、\(p_2\)、\(p_3\)、\(p_4\)定义的折线由线段\(p_1p_2\)、\(p_2p_3\)、\(p_3p_4\)组成，其长度是各个线段长度之和。

## 样例 #1
### 输入
```
1 1
```
### 输出
```
1 1
0 0
1 0
0 1
```
## 样例 #2
### 输入
```
0 10
```
### 输出
```
0 1
0 10
0 0
0 9
```
### 算法分类
数学
### 综合分析与结论
两题解思路相似，均通过分类讨论来确定使折线最长的四个点的选取方式。难点在于找出不同情况下能使折线长度最大的点的组合，并比较不同组合下折线长度。两题解均先考虑\(n\)或\(m\)为\(0\)的特殊情况，再处理\(n\)和\(m\)均不为\(0\)的一般情况。在一般情况中，都考虑了两种取点方式并通过计算比较长度。不同在于，第一个题解在判断取点方式时直接通过坐标形式判断，第二个题解先计算出两种取点方式下折线长度再比较大小。
### 所选的题解
- **作者：luuia（3星）**
  - **关键亮点**：思路清晰，分情况讨论详细，先处理特殊情况，再对一般情况通过计算两种取点方式下折线长度进行比较。
### 重点代码及核心实现思想
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    double a1,a2;
    cin >> n >> m;
    if(n == 0)
    {
    	cout << "0 1" << endl;
    	cout << "0 " << m << endl;
    	cout << "0 0" << endl;
    	cout << "0 " << m - 1 << endl;
    	return 0;
	}
	else if(m == 0)
	{
		cout << "1 0" << endl;
    	cout << m << " 0" << endl;
    	cout << "0 0" << endl;
    	cout << m - 1 << " 0" << endl;
    	return 0;
	}
    int p = max(n,m);
    n = min(n,m);
    m = p;
	a1 = m + sqrt(n * n + m * m) + sqrt(n * n + m * m);
    a2 = sqrt((n - 1) * (n - 1) + m * m) + sqrt((n - 1) * (n - 1) + m * m) + sqrt(n * n + m * m);
	if(a1 > a2)
    {
    	cout << "0 0" << endl;
    	cout << n << " " << m << endl;
    	cout << n << " 0" << endl;
    	cout << "0 " << m << endl;
	}
	else
	{
		cout << n - 1 << " " << m << endl;
		cout << "0 0" << endl;
		cout << n << " " << m << endl;
		cout << "1 0" << endl;
	}
	return 0;
}
```
核心实现思想：先判断\(n\)或\(m\)是否为\(0\)，若是则按特定方式输出四个点。若\(n\)和\(m\)均不为\(0\)，将\(n\)设为较小值，\(m\)设为较大值，分别计算两种取点方式下折线的长度\(a1\)和\(a2\)，根据比较结果输出对应四个点。
### 最优关键思路或技巧
通过分类讨论，将问题分为边界情况（\(n = 0\)或\(m = 0\)）和一般情况（\(n \neq 0\)且\(m \neq 0\)），在一般情况下找出两种可能使折线最长的取点方式，并通过数学计算比较长度，从而确定最终取点。
### 拓展与类似题目
此类题目属于几何与数学结合的问题，类似套路是通过分类讨论不同几何情况，利用数学计算来解决问题。
### 洛谷相似题目推荐
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：简单的数学计算与条件判断。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过比较不同购买方案的花费来求解。
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：结合数学运算与条件判断解决实际问题。 

---
处理用时：46.22秒