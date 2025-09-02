# 题目信息

# Coloring Rectangles

## 题目描述

David was given a red checkered rectangle of size $ n \times m $ . But he doesn't like it. So David cuts the original or any other rectangle piece obtained during the cutting into two new pieces along the grid lines. He can do this operation as many times as he wants.

As a result, he will get a set of rectangles. Rectangles $ 1 \times 1 $ are forbidden.

David also knows how to paint the cells blue. He wants each rectangle from the resulting set of pieces to be colored such that any pair of adjacent cells by side (from the same piece) have different colors.

What is the minimum number of cells David will have to paint?

## 说明/提示

The following pictures show how the initial rectangle can be split and cells colored blue.

In the first test case:

 ![](https://espresso.codeforces.com/d4181663ab2adbfb9f518c9f09390152197a7da9.png)In the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/031877f8fff4a791933910251c89a32c8e77053c.png)In the third test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/56c02ce81081236d5a7f494f32a723cf9e1c4a6e.png)In the fourth test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/13bf05e608fac4f3bd0b4c9984699891f97a32fe.png)

## 样例 #1

### 输入

```
4
1 3
2 2
2 5
3 5```

### 输出

```
1
2
4
5```

# AI分析结果

### 题目内容
# 给矩形上色

## 题目描述
大卫得到了一个大小为$n \times m$的红色方格矩形。但他不喜欢这个矩形，所以他会沿着网格线将原始矩形或在切割过程中得到的任意其他矩形切成两个新的矩形。他可以根据需要进行多次此操作。

最终，他会得到一组矩形。其中$1 \times 1$的矩形是不允许出现的。

大卫还知道如何将单元格涂成蓝色。他希望对最终得到的每个矩形进行涂色，使得同一矩形中任意两个相邻的单元格（边相邻）颜色不同。

大卫最少需要涂多少个单元格？

## 说明/提示
以下图片展示了初始矩形如何分割以及单元格如何涂成蓝色。

在第一个测试用例中：
![](https://espresso.codeforces.com/d4181663ab2adbfb9f518c9f09390152197a7da9.png)
在第二个测试用例中：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/031877f8fff4a791933910251c89a32c8e77053c.png)
在第三个测试用例中：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/56c02ce81081236d5a7f494f32a723cf9e1c4a6e.png)
在第四个测试用例中：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1584B/13bf05e608fac4f3bd0b4c9984699891f97a32fe.png)

## 样例 #1
### 输入
```
4
1 3
2 2
2 5
3 5
```
### 输出
```
1
2
4
5
```

### 算法分类
数学

### 综合分析与结论
所有题解的核心思路都是将大矩形尽可能多地分割为$1\times3$和$1\times2$的小矩形，因为这样能使涂色次数最少。主要难点在于如何根据$n\times m$的结果对$3$取模的余数情况，来确定最终的涂色次数。各题解都围绕这一难点展开分析，大部分题解直接给出通用公式$(n*m + 2) / 3$，部分题解通过分类讨论余数为$0$、$1$、$2$的情况来得到结果。整体思路较为清晰，差异不大，只是在表述和代码风格上略有不同。

### 所选的题解
- **作者：让风忽悠你 (3星)**
    - **关键亮点**：从单行或单列棋盘入手，推广到多行多列棋盘，思路推导自然。
    - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

int T,n,m;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		printf("%d\n",(n*m+2)/3);
	}
	return 0;
}
```
    - **核心实现思想**：直接套用公式计算并输出结果。
- **作者：_Haoomff_ (3星)**
    - **关键亮点**：简洁地分类讨论$n$和$m$与$3$的倍数关系及余数情况，得出最终公式。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t; 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(;t--;){
		int n,m;
		cin>>n>>m;
		cout<<(n*m+2)/3<<"\n";
	}
	return 0;
}
```
    - **核心实现思想**：输入数据后，直接用公式计算并输出最小涂色次数。
- **作者：luguangxing (3星)**
    - **关键亮点**：结合图片，以博弈论的思想，详细分类讨论取$1\times3$矩形后余数的三种情况并推导公式。
    - **重点代码（详细版）**：
```cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		if(n*m%3==0)
		cout<<n*m/3<<endl;
		else if(n*m%3==1)
		cout<<n*m/3+1<<endl;
		else if(n*m%3==2)
		cout<<n*m/3+1<<endl;
	}
	return 0;
}
```
    - **核心实现思想**：根据$n\times m$对$3$取模的结果，分情况输出对应的涂色次数。

### 最优关键思路或技巧
将大矩形分割为$1\times3$和$1\times2$的小矩形这一思路是解题关键，通过对总面积对$3$取模的余数情况进行分类讨论，得出通用公式$(n*m + 2) / 3$，简化计算过程。

### 拓展思路
此类题目属于几何与数学结合的类型，类似套路是先观察图形的分割方式，找到最优的基本图形（本题为$1\times3$矩形），再根据整体与基本图形的数量关系（通过取模等运算）得出结果。

### 相似知识点洛谷题目
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：通过对数字的生成规则进行分析，利用递推或记忆化搜索求解，与本题分析图形分割方式类似。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：根据等差数列求和公式及数论知识，通过枚举和计算解决问题，与本题利用数学运算求解最小涂色次数思路相似。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：运用数论知识和斐波那契数列性质求解最大公约数，与本题运用数学知识解决几何问题的方式类似。 

---
处理用时：60.30秒