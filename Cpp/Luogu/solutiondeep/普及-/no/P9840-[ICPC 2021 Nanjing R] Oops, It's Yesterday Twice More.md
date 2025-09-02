# 题目信息

# [ICPC 2021 Nanjing R] Oops, It's Yesterday Twice More

## 题目描述

After the great success in 2018, 2019, and 2020, Nanjing University of Aeronautics and Astronautics (NUAA) will host the $\textit{International Collegiate Programming Contest}$ (ICPC) Nanjing regional for the fourth time.

Team $\textbf{\textit{Power of Two}}$ and team $\textbf{\textit{Three Hold Two}}$ won the champion for Tsinghua University in 2018 and 2019. In 2020, team $\textbf{\textit{Inverted Cross}}$ from Peking University won the champion. In 2021, there are around $700$ teams including $\textbf{the defending champion}$ participating in the contest. We are so excited to see who will win this year!

Although we can't gather in Nanjing this time due to the pandemic, we should still be grateful for the hard work done by all staff and volunteers for this contest. Thank you all for your great contribution to this contest!

In the 2018 contest, problem K, $\textbf{\textit{Kangaroo Puzzle}}$, requires the contestants to construct an operation sequence for the game:

> The puzzle is a grid with $n$ rows and $m$ columns ($1 \le n, m \le 20$) and there are some (at least $2$) kangaroos standing in the puzzle. The player's goal is to control them to get together. There are some walls in some cells and the kangaroos cannot enter the cells with walls. The other cells are empty. The kangaroos can move from an empty cell to an adjacent empty cell in four directions: up, down, left, and right.
>
> There is exactly one kangaroo in every empty cell in the beginning and the player can control the kangaroos by pressing the button U, D, L, R on the keyboard. The kangaroos will move simultaneously according to the button you press.
>
> The contestant needs to construct an operating sequence of at most $5 \times 10^4$ steps consisting of U, D, L, R only to achieve the goal.

In the 2020 contest, problem A, $\textbf{\textit{Ah, It's Yesterday Once More}}$, requires the contestants to construct an input map to hack the following code of the problem described before:

```cpp
#include <bits/stdc++.h>
using namespace std;
string s = "UDLR";
int main()
{
  srand(time(NULL));
  for (int i = 1; i <= 50000; i++) putchar(s[rand() % 4]);
  return 0;
}
```

Now in the 2021 contest, Paimon prepares another version of the problem for you. You are given a grid with $n$ rows and $n$ columns ($2 \leq n \leq 500$). All cells are empty and there is one kangaroo standing in each cell.

Similarly, you can control the kangaroos by pressing the button U, D, L, R on the keyboard. The kangaroos will move simultaneously according to the button you press. Specifically, for any kangaroo located in the cell on the $i$-th row and the $j$-th column, indicated by $(i,j)$:

- Button U: it will move to $(i-1,j)$ if $i>1$. Otherwise, it will stay in the same grid.
- Button D: it will move to $(i+1,j)$ if $i<n$. Otherwise, it will stay in the same grid.
- Button L: it will move to $(i,j-1)$ if $j>1$. Otherwise, it will stay in the same grid.
- Button R: it will move to $(i,j+1)$ if $j<n$. Otherwise, it will stay in the same grid.

You need to construct an operating sequence consisting only of characters `U`, `D`, `L`, and `R`. After applying it, you must make sure every kangaroo will gather at the specific cell $(a,b)$. The length of the operating sequence cannot exceed $3(n-1)$.

## 样例 #1

### 输入

```
3 3 3
```

### 输出

```
RRDD```

## 样例 #2

### 输入

```
4 3 2
```

### 输出

```
DLDLDLUR```

# AI分析结果

### 算法分类
构造

### 综合分析与结论
本题的核心逻辑是通过构造一系列操作序列，将所有袋鼠移动到指定位置。题解的主要思路是先将所有袋鼠聚集到某个角落，然后再移动到目标位置。这种思路的关键在于如何选择最近的角落，并确保操作序列的长度不超过限制。

### 所选题解

#### 1. 作者：WhileTrueRP (赞：7)
- **星级**: 4.5
- **关键亮点**: 思路清晰，代码简洁，直接通过判断目标位置与四个角的距离来选择最优路径，确保操作序列长度不超过限制。
- **核心代码**:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	if(a <= n/2){
		for(int i=1;i<n;i++) printf("U");
		for(int i=1;i<a;i++) printf("D");
	}else{
		for(int i=1;i<n;i++) printf("D");
		for(int i=1;i<n-a+1;i++) printf("U");
	}
	if(b <= n/2){
		for(int i=1;i<n;i++) printf("L");
		for(int i=1;i<b;i++) printf("R");
	}else{
		for(int i=1;i<n;i++) printf("R");
		for(int i=1;i<n-b+1;i++) printf("L");
	}
}
```
- **实现思想**: 通过判断目标位置与四个角的距离，选择最近的角落，先移动到该角落，再移动到目标位置。

#### 2. 作者：small_john (赞：2)
- **星级**: 4
- **关键亮点**: 详细分析了如何通过移动将所有袋鼠聚集到某个角落，并确保操作序列长度不超过限制。
- **核心代码**:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,a,b;
	cin>>n>>a>>b;
	int t = n / 2;
	if(a <= t && b <= t){
		for(int i = 1; i < n; i++) printf("U");
		for(int i = 1; i < n; i++) printf("L");
		for(int i = 1; i < a; i++) printf("D");
		for(int i = 1; i < b; i++) printf("R");
	}
	// 其他情况类似
}
```
- **实现思想**: 通过判断目标位置与四个角的距离，选择最近的角落，先移动到该角落，再移动到目标位置。

#### 3. 作者：Clarinet (赞：0)
- **星级**: 4
- **关键亮点**: 代码简洁，直接通过判断目标位置与四个角的距离来选择最优路径，确保操作序列长度不超过限制。
- **核心代码**:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int main(){
	cin>>n>>x>>y;
	if(2*x<=n){
		for(int i=1;i<n;i++)cout<<"U";
		for(int i=1;i<x;i++)cout<<"D";
	}
	else{
		for(int i=1;i<n;i++)cout<<"D";
		for(int i=n;i>x;i--)cout<<"U";
	}
	if(2*y<=n){
		for(int i=1;i<n;i++)cout<<"L";
		for(int i=1;i<y;i++)cout<<"R";
	}
	else{
		for(int i=1;i<n;i++)cout<<"R";
		for(int i=n;i>y;i--)cout<<"L";
	}
	return 0;
}
```
- **实现思想**: 通过判断目标位置与四个角的距离，选择最近的角落，先移动到该角落，再移动到目标位置。

### 最优关键思路或技巧
1. **选择最近的角落**: 通过判断目标位置与四个角的距离，选择最近的角落，确保操作序列长度最短。
2. **分步移动**: 先将所有袋鼠聚集到某个角落，再移动到目标位置，确保操作序列长度不超过限制。

### 可拓展之处
类似的问题可以通过构造操作序列来解决，例如在网格图中移动多个物体到指定位置。这类问题通常需要选择最优路径，并确保操作序列长度不超过限制。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

---
处理用时：30.61秒