# 题目信息

# Bessie's Birthday Cake (Easy Version)

## 题目描述

[Proof Geometric Construction Can Solve All Love Affairs - manbo-p](https://soundcloud.com/alice-law-314125270/manbo-p-proof-geometric-construction-can-solve-all-love-affairs)

⠀



This is the easy version of the problem. The only difference between the two versions is the constraint on $ y $ . In this version $ y = 0 $ . You can make hacks only if both versions are solved.

Bessie has received a birthday cake from her best friend Elsie, and it came in the form of a regular polygon with $ n $ sides. The vertices of the cake are numbered from $ 1 $ to $ n $ clockwise. You and Bessie are going to choose some of those vertices to cut non-intersecting diagonals into the cake. In other words, the endpoints of the diagonals must be part of the chosen vertices.

Bessie would only like to give out pieces of cake which result in a triangle to keep consistency. The size of the pieces doesn't matter, and the whole cake does not have to be separated into all triangles (other shapes are allowed in the cake, but those will not be counted).

Bessie has already chosen $ x $ of those vertices that can be used to form diagonals. She wants you to choose no more than $ y $ other vertices such that the number of triangular pieces of cake she can give out is maximized.

What is the maximum number of triangular pieces of cake Bessie can give out?

## 说明/提示

In test cases $ 1 $ , $ 2 $ and $ 3 $ , you can get $ 2 $ , $ 6 $ and $ 2 $ non-intersecting triangular pieces of cake, respectively. A possible construction is shown in the following pictures:

The green dots represent vertices that can be used, the blue lines represent diagonals that are drawn, and the red numbers represent triangles that are counted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C1/a4f3a6e3efd4b2b24052c536629245c4fd02196b.png)

## 样例 #1

### 输入

```
3
8 4 0
1 6 2 5
8 8 0
1 3 2 5 4 6 7 8
4 2 0
1 3```

### 输出

```
2
6
2```

# AI分析结果

### 题目内容重写

#### Bessie的生日蛋糕（简单版）

这是问题的简单版本。两个版本之间的唯一区别是对 $y$ 的约束。在此版本中，$y=0$。只有当两个版本都得到解决时，您才能进行黑客攻击。

Bessie从她最好的朋友Elsie那里收到了一个生日蛋糕，它以一个规则的多边形的形式出现，带有 $n$ 面。蛋糕的顶点编号为顺时针方向 $1$ 到 $n$。你和Bessie将选择其中一些顶点来切割不相交的对角线到蛋糕中。换言之，对角线的端点必须是所选顶点的一部分。

Bessie只想分发一块蛋糕，这会导致一个三角形以保持一致性。碎片的大小无关紧要，整个蛋糕不必分成所有三角形（蛋糕中允许其他形状，但不计算在内）。

Bessie已经选择了可用于形成对角线的 $x$ 个顶点。她希望你选择的顶点不超过 $y$ 个，这样她可以给出的三角形蛋糕的数量就会最大化。

Bessie最多可以送出三角形蛋糕多少块？

### 题解分析与结论

本题的核心在于如何通过给定的 $x$ 个顶点最大化三角形的数量。由于 $y=0$，我们只需要考虑这 $x$ 个顶点。通过将 $x$ 个顶点看作一个多边形，我们可以利用多边形的性质来计算三角形的数量。具体来说，$x$ 个顶点可以构成 $x-2$ 个三角形。此外，如果两个顶点之间的距离为 $2$，它们也可以构成一个三角形。

### 精选题解

#### 题解作者：littlebug (3星)

**关键亮点：**
- 通过将 $x$ 个顶点看作一个多边形，直接得出 $x-2$ 个三角形。
- 通过排序和遍历，找到所有距离为 $2$ 的顶点对，增加三角形数量。
- 代码简洁，逻辑清晰。

**代码实现：**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define il inline
using namespace std;
const int MAXN=2e5+5;
int n,x,y;
int a[MAXN];
il void solve()
{
	cin>>n>>x>>y;
	for(int i=1;i<=x;++i)
		cin>>a[i];
	sort(a+1,a+x+1);
	int ans=x;
	for(int i=2;i<=x;++i)
	{
		if(a[i]-a[i-1]==2)
			++ans;
	}
	if(a[1]+n-a[x]==2)
		++ans;
	cout<<ans-2<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

#### 题解作者：luobotianle (3星)

**关键亮点：**
- 利用多边形的性质，直接计算 $x-2$ 个三角形。
- 通过遍历找到距离为 $2$ 的顶点对，增加三角形数量。
- 代码简洁，逻辑清晰。

**代码实现：**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int T,n,x,y;
int a[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n>>x>>y;
		for(int i=1;i<=x;i++)cin>>a[i];
		sort(a+1,a+1+x);
		int ans=x-2;
		for(int i=2;i<=x;i++)if(a[i]-a[i-1]==2)ans++;
		if(a[x]+2-n==a[1])ans++;
		cout<<ans<<"\n";
	}
	return 0;
}
```

#### 题解作者：Atserckcn (3星)

**关键亮点：**
- 通过多边形的性质，直接计算 $x-2$ 个三角形。
- 通过遍历找到距离为 $2$ 的顶点对，增加三角形数量。
- 代码简洁，逻辑清晰。

**代码实现：**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,x,y,T,a[MAXN],ans;
int main(){
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&x,&y);
		for(int i=1;i<=x;i++)
			scanf("%d",&a[i]);
		ans=x-2;
		sort(a+1,a+x+1);
		for(int i=2;i<=x;i++)
			if(a[i]-a[i-1]==2)
					ans++;
		if(a[x]-n==a[1]-2) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```

### 最优关键思路

1. **多边形性质**：将 $x$ 个顶点看作一个多边形，直接得出 $x-2$ 个三角形。
2. **距离为2的顶点对**：通过排序和遍历，找到所有距离为 $2$ 的顶点对，增加三角形数量。
3. **环状处理**：注意首尾顶点之间的距离是否为 $2$，增加三角形数量。

### 拓展思路

本题的解法可以推广到其他类似的几何问题，尤其是涉及多边形分割和三角形计数的问题。通过利用多边形的性质和顶点之间的距离关系，可以有效地解决这类问题。

### 推荐题目

1. [P1357 三角形的个数](https://www.luogu.com.cn/problem/P1357)
2. [P1358 三角形的最大面积](https://www.luogu.com.cn/problem/P1358)
3. [P1359 三角形的最大周长](https://www.luogu.com.cn/problem/P1359)

### 个人心得

在解决几何问题时，充分利用多边形的性质和顶点之间的关系，可以大大简化问题的复杂度。通过排序和遍历，可以有效地找到符合条件的顶点对，从而增加三角形的数量。在处理环状结构时，注意首尾顶点的处理，避免遗漏。

---
处理用时：54.49秒