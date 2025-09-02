# 题目信息

# Death Stars (easy)

## 题目描述

The stardate is 1977 and the science and art of detecting Death Stars is in its infancy. Princess Heidi has received information about the stars in the nearby solar system from the Rebel spies and now, to help her identify the exact location of the Death Star, she needs to know whether this information is correct.

Two rebel spies have provided her with the maps of the solar system. Each map is an $ N×N $ grid, where each cell is either occupied by a star or empty. To see whether the information is correct, Heidi needs to know whether the two maps are of the same solar system, or if possibly one of the spies is actually an Empire double agent, feeding her false information.

Unfortunately, spies may have accidentally rotated a map by 90, 180, or 270 degrees, or flipped it along the vertical or the horizontal axis, before delivering it to Heidi. If Heidi can rotate or flip the maps so that two of them become identical, then those maps are of the same solar system. Otherwise, there are traitors in the Rebel ranks! Help Heidi find out.

## 说明/提示

In the first test, you can match the first map to the second map by first flipping the first map along the vertical axis, and then by rotating it 90 degrees clockwise.

## 样例 #1

### 输入

```
4
XOOO
XXOO
OOOO
XXXX
XOOO
XOOO
XOXO
XOXX
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2
XX
OO
XO
OX
```

### 输出

```
No
```

# AI分析结果

### 题目内容重写

**题目名称：死亡之星（简单版）**

**题目描述：**

在1977年的星际历中，检测死亡之星的科学和艺术还处于初级阶段。Heidi公主从反抗军的间谍那里收到了附近太阳系中恒星的信息，现在为了帮助她确定死亡之星的确切位置，她需要知道这些信息是否正确。

两位反抗军间谍向她提供了太阳系的地图。每张地图都是一个 $N×N$ 的网格，每个单元格要么被一颗恒星占据，要么为空。为了确认信息的正确性，Heidi需要知道这两张地图是否来自同一个太阳系，或者其中一位间谍可能是帝国的双重间谍，向她提供了虚假信息。

不幸的是，间谍可能在将地图交给Heidi之前不小心将其旋转了90度、180度或270度，或者沿垂直或水平轴翻转。如果Heidi可以通过旋转或翻转地图使它们变得相同，那么这两张地图就是来自同一个太阳系。否则，反抗军队伍中就有叛徒！请帮助Heidi找出答案。

**说明/提示：**

在第一个测试中，你可以通过先将第一张地图沿垂直轴翻转，然后顺时针旋转90度，使其与第二张地图匹配。

**样例 #1**

输入：

```
4
XOOO
XXOO
OOOO
XXXX
XOOO
XOOO
XOXO
XOXX
```

输出：

```
Yes
```

**样例 #2**

输入：

```
2
XX
OO
XO
OX
```

输出：

```
No
```

### 算法分类
模拟

### 题解分析与结论

本题的核心逻辑是通过模拟旋转和翻转操作，判断两张地图是否可以通过这些操作变得相同。由于地图的大小 $N$ 最大为10，因此可以直接通过枚举所有可能的旋转和翻转操作来进行判断。

### 所选高分题解

#### 题解作者：_mi_ka_ (5星)

**关键亮点：**
- 详细列出了所有可能的旋转和翻转操作，并给出了每种操作的具体实现。
- 通过枚举所有可能的操作组合，确保不会遗漏任何情况。
- 代码结构清晰，逻辑严谨，易于理解和实现。

**核心代码：**

```cpp
#include<iostream>
#include<cstdio>
#define N 12
using namespace std;
int n,flag;
char A[N][N],B[N][N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>(A[i]+1);
	for(int i=1;i<=n;i++)
		cin>>(B[i]+1);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[i][j])//枚举每一种 
				flag=0;
	if(flag)
		puts("Yes"),exit(0);//某种情况符合直接输出 Yes，然后结束程序 
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[n-i+1][j])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[i][n-j+1])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[n-i+1][n-j+1])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[j][i])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[n-j+1][i])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[j][n-i+1])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	flag=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(A[i][j]!=B[n-j+1][n-i+1])
				flag=0;
	if(flag)
		puts("Yes"),exit(0);
	puts("No");//都不符合，输出 No  
	return 0;
}
```

**个人心得：**
- 作者通过详细的枚举和清晰的代码结构，确保所有可能的操作都被覆盖，避免了遗漏。

### 最优关键思路或技巧

1. **枚举所有可能的旋转和翻转操作**：通过枚举所有可能的操作组合，确保不会遗漏任何情况。
2. **代码结构清晰**：通过将每种操作单独实现，并在主函数中依次调用，确保代码逻辑清晰易懂。
3. **提前退出**：在找到匹配的操作后，立即输出结果并退出程序，减少不必要的计算。

### 可拓展之处

类似的问题可以通过枚举所有可能的操作组合来解决，尤其是在数据规模较小的情况下。例如，类似的题目可以涉及图像的旋转、翻转、平移等操作。

### 推荐题目

1. [P1205 方块转换](https://www.luogu.com.cn/problem/P1205)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：38.44秒