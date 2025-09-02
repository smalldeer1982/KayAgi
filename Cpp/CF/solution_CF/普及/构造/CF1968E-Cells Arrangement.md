# Cells Arrangement

## 题目描述

You are given an integer $ n $ . You choose $ n $ cells $ (x_1,y_1), (x_2,y_2),\dots,(x_n,y_n) $ in the grid $ n\times n $ where $ 1\le x_i\le n $ and $ 1\le y_i\le n $ .

Let $ \mathcal{H} $ be the set of distinct Manhattan distances between any pair of cells. Your task is to maximize the size of $ \mathcal{H} $ . Examples of sets and their construction are given in the notes.

If there exists more than one solution, you are allowed to output any.

Manhattan distance between cells $ (x_1,y_1) $ and $ (x_2,y_2) $ equals $ |x_1-x_2|+|y_1-y_2| $ .

## 说明/提示

In the first testcase we have $ n=2 $ . One of the possible arrangements is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/75dc943a7c64415a7537c95e5a0a8ab6f7bb8c40.png) The arrangement with cells located in $ (1,1) $ and $ (1,2) $ .  In this case $ \mathcal{H}=\{|1-1|+|1-1|,|1-1|+|2-2|,|1-1|+|1-2|\}=\{0,0,1\}=\{0,1\} $ . Hence, the size of $ \mathcal{H} $ is $ 2 $ . It can be shown that it is the greatest possible answer.In the second testcase we have $ n=3 $ . The optimal arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c33264fb4d38aae733c98659eb0f28334deed2c9.png) The arrangement with cells located in $ (2,1) $ , $ (2,3) $ and $ (3,1) $ . $ \mathcal{H} $ = $ \{|2-2|+|1-1|,|2-2|+|3-3|,|3-3|+|1-1|,|2-2|+|1-3|,|2-3|+|1-1|,|2-3|+|3-1|\} $ = $ \{0,0,0,2,1,3\} $ = $ \{0,1,2,3\} $ .

For $ n=4 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c8c88e231569a366e81dbe59dfe40f3bca88662e.png)For $ n=5 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/3a3f9b43e6fc8c9643d27a1bfc597d0efe1c8425.png)For $ n=6 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/b0bf5b17a4bc6da02c3ed5a2113cf7373a9e3ccc.png)

## 样例 #1

### 输入

```
5
2
3
4
5
6```

### 输出

```
1 1
1 2

2 1
2 3
3 1

1 1
1 3
4 3
4 4

1 1
1 3
1 4
2 1
5 5

1 4
1 5
1 6
5 2
5 5
6 1```

# 题解

## 作者：JuRuoOIer (赞：9)

# 题解 CF1968E - Cells Arrangement

### 题意

已提交翻译。

给定 $n$，要求在 $n\times n$ 的网格上选 $n$ 个点，令 $H$ 为这些点两两之间的曼哈顿距离的集合，要求给出一种构造方案，使得 $H$ 中不同的元素个数最多。

数据范围：$t \le 50,n \le 10^3$。

### 做法

众所周知，找规律肯定不能看样例解释的图。

首先考虑 $H$ 中不同的元素应该有哪些。显然曼哈顿距离的最大值是两个对着的角上放两个点，这两个点之间的曼哈顿距离为 $2(n-1)$。于是大胆猜想：正确的 $H$ 应该包含 $0$ 到 $2(n-1)$ 之间的全部值。随便找一个 $n$ 试试。

当 $n=4$ 时，按照刚才的思路：
- 我们先给左上角和右下角各放一个，于是 $0$ 和 $6$ 就有了；
- 接着我们需要 $1$ 到 $5$。现在我们的图长这样：
```
1000
0000
0000
0001
```
- 首先 $1$ 肯定得横竖相邻，于是往左上角的右边（下面也行）扔一个点。于是我们有了 $1$ 和 $5$。
```
1100
0000
0000
0001
```
- 现在我们需要只放一个点就加上 $2,3,4$，所以显然这个点到另外三个点的距离应该分别为 $2,3,4$。而左上角的两个是连着的，于是我们分两种情况尝试：
  - 使新点到这两个点的距离分别为 $2,3$，我们可以将其放在 $(2,3)$、$(3,2)$、$(1,4)$ 或者 $(3,1)$。此时只有 $(3,1)$ 到右下角的曼哈顿距恰好为 $4$，符合要求。
  - 使新点到这两个点的距离分别为 $3,4$，此时 $(2,4)$，$(3,3)$ 和 $(4,2)$ 都可以。

这时，我们发现我们有四种选择！这该怎么办呢？

不要慌，我们还是先把图画一下。

```
1100 1100 1100 1100
0000 0001 0000 0000
1000 0000 0010 0000
0001 0001 0001 0101
```

我们发现，上面四种正确的构造方案中，只有第三种看上去有点规律性：填入 $(1,2)$ 和左上 - 右下对角线上除 $(2,2)$ 外的所有点！按照这种思路，$n=5$ 和 $n=6$ 时的图应该长这样：

```
11000 110000
00000 000000
00100 001000
00010 000100
00001 000010
      000001
```

经过验证，这些图都符合要求。于是我们便得到了构造方案。

证明其正确性：
- 首先 $2 \le n \le 4$ 时是正确的；
- 接着我们假设 $n=k(k \ge 4)$ 时是正确的，即左上部的 $k\times k$ 的部分中的 $H$ 已经包含了 $0$ 至 $2\times(k-1)$ 的所有整数，此时我们往右下角加的点 $(k+1,k+1)$ 与 $(1,1)$ 和 $(1,2)$ 的曼哈顿距离恰好分别是 $2k$ 和 $2k-1$，这样当 $n=k+1$ 时 $H$ 中就包含了 $0$ 至 $2k$ 的所有数。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<"1 1\n1 2\n";
		for(int i=3;i<=n;i++){
			cout<<i<<' '<<i<<endl;
		}
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：liuhongyang123 (赞：3)

# 题目大意

共有 $T$ 组数据，每组数据中给定 $?$，要求在 $? \times ?$ 的网格上选 $n$ 个点，令 $H$ 为这些点两两之间的曼哈顿距离的集合，要求给出一种构造方案，使得 $H$ 中不同的元素个数最多。

# 方法

最大的哈夫曼距离肯定是放在对角上，为 $2(n-1)$，所以 $H$ 应该 $0$ 到 $2(n-1)$ 都有。

所以考虑全放对角线，可是手玩发现这样距离只有偶数，那么我们把 $(2,2)$ 的点放在 $(1,2)$ 去，这样我们就有距离为奇数。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		cout<<"1 1"<<endl<<"1 2"<<endl;
		for(int i=3;i<=n;i++) cout<<i<<" "<<i<<endl;
		cout<<endl;
	}
	return 0;
} 
```

---

## 作者：Watersphere (赞：2)

## 解题思路
拿到题先观察一遍样例， 原题点
[这里](https://codeforces.com/contest/1968/problem/E)
 。

发现样例给的很散乱，但是对于 $n>3$ 的样例可以看出都有一组斜对角放了两个点，并且集合 $H$ 都为 $\{0,1\dots2n-2\}$，其中 $2n-2$ 即两个斜对角间的曼哈顿距离。所以我们以这个为思路来琢磨。

--------------------------
这里以 $n=6$ 为例，当我们将一颗棋子放在 $(1,4)$ 处时，它对两颗对角线棋子的**贡献**分别为$\textcolor{blue}{深蓝\ 4-1=3\ }$与$\textcolor{lightblue}{浅蓝\ 6-1+6-4=7 }$。
![](https://cdn.luogu.com.cn/upload/image_hosting/nph68vxa.png)

--------------------
那么我们设一颗放在 $(1,x)$ 的棋子编号为 $x$，则可以推出点 $x$ 对集合 $H$ 的贡献两个元素，一个为 $x-1$，另一个为 $n-x+n-1$ 即 $2n-x-1$ 。

这时，当我们将剩余的 $n-2$ 颗棋子放满区间 $[2,n-1]$ 时，集合 $H$ 为 $\{0,1,\dots n-2,n,\dots 2n-2\}$。
![](https://cdn.luogu.com.cn/upload/image_hosting/bvzdyeyh.png)

有没有发现少了什么？没错，$n-1$ 。

于是考虑将点 $n-1$ 从 $(1,n-1)$ 移动到关于两个对称点相连的对称轴对称的点 $(n-1,1)$，这时这个点由于对称性对 $(1,1)$ 和 $(n,n)$ 的贡献不变，但是与点 $2$ 贡献了长度为 $n-1$ 的曼哈顿距离。如下图的蓝色线：

![](https://cdn.luogu.com.cn/upload/image_hosting/z2ug4tjl.png)

此时集合 $H$ 为 $\{0,1,\dots 2n-2\}$，由于不可能有比对角的曼哈顿距离还大的点对，所以这就是 $H$ 的最大大小。

## 特判
其实很简单，对于 $n=2$，无论两个点怎么放，$H$ 始终为 $\{0,1\}$ 或 $\{0,2\}$ 中的一个，大小不变，所以随意放都行。

## 代码实现
一个 for 循环输出 $(1, 1\sim n-2)$ ，再输出 $(n-1, 1)$ 与 $(n, n)$ 即可。由于 $2-2=0$ ，不会执行 for 循环，所以不用写特判代码。

## ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200200];
int main(){
	cin>>t;
	for(int o=1;o<=t;o++){
		cin>>n;
		for(int i=1;i<=n-2;i++){
			cout<<1<<" "<<i<<"\n";
		}
		cout<<n-1<<" "<<1<<"\n";
		cout<<n<<" "<<n<<"\n";
	}
}

---

## 作者：junee (赞：1)

# CF1968E 题解

## 前置知识

构造。

## 题目分析

我们研究一下样例发现，$ \mathcal{H} $ 的大小是 $2 \times n - 1$,为了构造出距离 1，我们可以先将两个点放在 $(1,1),(1,2)$,然后剩下的点依次放在对角线上。

那么对于对角线上的点 $(x,x)$，他与 $(x+1,x+1)$ 的距离为 2 ，而他与 $(1,1),(1,2)$ 的分别距离为 $ 2 \times x - 2,2 \times x - 3$,这样就可以得到一个大小为 $2 \times n-1 $ 的 $ \mathcal{H} $。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int T,n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		cout<<1<<' '<<1<<'\n'<<1<<' '<<2<<'\n';
		for(int i=3;i<=n;i++)cout<<i<<' '<<i<<'\n';
	}
	return 0;
}
```

---

## 作者：___Furina___ (赞：1)

### 题目简述：
无。
### 题解：
~~官方题解写的还挺清楚的。~~

不妨来讲讲我自己的想法：

我们很容易想到，把所有的棋子放在对角线上，但是很显然，我们并不能把答案最大化。

怎么办呢？我们发现，我们目前只能重复的表示偶数长度，不妨我们加入一个与**其他点横纵坐标之和奇偶不同**的点，这样我们就可以表示出奇数长度啦！

### 代码如下：
```
#include<bits/stdc++.h>
#define I_love_Furina return//发电+防抄袭（？）
#define forever 0
#define foreverr 1
//#define int long long
using namespace std;
int n,t,m;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n-2;i++)cout<<i<<" "<<i<<endl;
		cout<<n-1<<" "<<n<<endl<<n<<"  "<<n<<endl;//往最后一个点上面加一个点
	}
    I_love_Furina forever;//完结撒花~~~
}
```

点个赞再走！

---

## 作者：g1ove (赞：1)

非常神秘构造题，使我考场大脑旋转。

目前收获已经 154 个差评。

我们肯定想构造一种方案，使得集合最大，即 $[0,2n-2]$，大小为 $2n-1$。

我们有一种数学直觉。就是在 $n$ 很大时，一定能取到全集。

我们来看看最简单的构造方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/tlxkzfil.png)

显然，这要 $2n-1$ 次涂色，肯定是不行的。

我们想想怎么优化。我们发现有一部分是没用的，这一部分可以去掉。

![](https://cdn.luogu.com.cn/upload/image_hosting/848udj81.png)

这样，我们将涂色部分转为了 $n+1$。

我们仔细分析一下这个部分的贡献。我们发现保留下面那一段红色是因为每个点和左上角的方格会产生贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/wmjsosuz.png)

这一部分的贡献我们换成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/gcophpld.png)

然后就做完了。我们只需要 $\lceil \frac{n}{2} \rceil+3$ 次涂色就能达到目标。

多余的格子随便涂就行。

注意，只有当 $n\ge 6$ 时，$\lceil \frac{n}{2} \rceil+3\le n$，所以 $n<6$ 直接输出样例即可。

code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;
int g;
int n;
struct node{
	int r[8][2];
}f[8];
int main()
{
	f[2]=(node){{
	1,1,
	1,2 
	}};
	f[3]=(node){{
	2,1,
	2,3,
	3,1	 
	}};
	f[4]=(node){{
	1,1,
	1,3,
	4,3,
	4,4
	}};
	f[5]=(node){{
	1, 1,
	1, 3,
	1, 4,
	2 ,1,
	5 ,5
	}};
	scanf("%d",&g);
	while(g--)
	{
		scanf("%d",&n);
		if(n>=6)
		{
			printf("%d %d\n%d %d\n%d %d\n%d %d\n",1,1,1,n,n,1,n,n);
			for(int i=2;i<=n-4+1;++i)
				printf("%d %d\n",1,i);
			printf("\n");
		}
		else
		{
			for(int i=0;i<n;i++)
				printf("%d %d\n",f[n].r[i][0],f[n].r[i][1]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：cheng2010 (赞：0)

# Cells Arrangement
## 题意
给你一个 $n \times n$ 的网格，选 $n$ 个点，设 $H$ 为所有点两两间的曼哈顿距离，求 $H$ 中的元素的最大值。

## 思路

首先我们知道，想要放两个点使他们的曼哈顿距离最大，那么我们应该把这两个点放在网格的对顶角上。

此时，它们的曼哈顿距离便为：$2 \times (n-1)$ 所以，$H$ 中的元素肯定是包含 $0 \sim 2 \times (n-1)$ 的，再手玩一下样例：

```
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
```

发现，如果选的点都在一条对角线上，那么所有除开 $0$，偶数我们都选到了，但奇数和 $0$ 呢？

再看，其实有很多曼哈顿距离是重复的，拿走几个点根本无伤大雅，所以可以把一个点移动到另一个旁边，此时就会发现，$0$ 和奇数的距离都有了。

如：

```
1 1 0 0
0 0 0 0
0 0 1 0
0 0 0 1
```

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n; 
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		puts("1 1\n1 2");
		for(int i=3;i<=n;i++) cout<<i<<" "<<i<<"\n";
		puts("");
	}
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
赛时始终百思不得其解，赛后看了他人代码恍然大悟。

先看一下我画的 $n=5$ 时的做法（`x` 表示选择的点）：

```
xx...
.....
..x..
...x.
....x
```

首先距离为 $0$ 是一定存在的，然后距离为 $1$ 就在第一行，$2$ 在 $a_{i,i},a_{i+1,i+1}(3\le i<n)$，$3$ 在 $a_{1,2},a_{3,3}$，$4$ 在 $a_{1,1},a_{3,3}$，$2i-3$ 在 $a_{1,2},a_{i,i}$，$2i-2$ 在 $a_{1,1},a_{i,i}$，这一来，$0\sim 2n-2$ 都凑齐了（$n=2,3$ 除外，但也是最优解）。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		cout << "1 1\n1 2\n";
		for (int i = 3; i <= n; ++ i)
			cout << i << ' ' << i << '\n';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：0)

## 解题思路

注意到 $\mathcal{H}$ 最大为 $2n-1$，考虑何时可以达到这个值。

- $n\leq 3$ 时，相互距离只有 $1+\frac {n(n-1)} {2}$ 种，一定达不到 $2n-1$。

- 否则我们认为其可能可以达到这个值。

对于 $n \geq 3$ 我们考虑构造：

- 为了得到 $2n-2$，我们需要在 $(1,1)$ 和 $(n,n)$ 放置两个点。

- 为了得到 $1,2,\cdots,n-2,n,n+1,\cdots,2n-3$，我们需要在 $(i,1),i\in[2,n]$ 放置 $n-2$ 个点。

- 但是这样我们得不到 $n-1$，考虑将 $(1,n-1)$ 的点转移到 $(n,2)$，这样我们在失去 $n-2$ 和 $n$ 的同时得到了 $n-2,n-1$ 和 $n$。（$n-2,n-1$ 和 $n$ 分别来自 $(n,n),(2,1)$ 以及 $(1,1)$）

这样我们就得到了最大值。特判 $n\leq 3$ 即可。

---

## 作者：wflhx2011 (赞：0)

## 题意

在 $n\times n$ 的网格中选择 $n$ 个点，使他们任意一对点之间曼哈顿距离不同的数量最大。多组解可任意输出一组。

## 思路

我先自己尝试去构造。

首先，我取了 $(1,1)$ 这个点，当然，也可以选另外 $3$ 个角上的。

然后，通过第一组样例，我们知道，接下来的点与 $(1,1)$ 的距离为 $1$，我们选择旁边的一个点，我选的是 $(2,1)$。

题目说在 $n\times n$ 的网格中选，于是，不难想到在一条斜线中选，这能让新的距离与之前尽量不重复。

注意，此时看似选 $(3,2)$ 也是最优解，实则选 $(3,3)$ 才是。

虽然当 $n=3$ 时集合大小都为 $4$ 并无差别，但当 $n=4$ 时，选 $(3,2)$ 和 $(4,3)$ 的集合大小为 $6$ ，选 $(3,3)$ 和 $(4,4)$ 的集合大小为 $7$，这里就会差 $1$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cout<<i<<" "<<(i==2?1:i)<<endl;
    cout<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}

```

---

## 作者：DrAlfred (赞：0)

摘要：构造

[传送门：https://www.luogu.com.cn/problem/CF1986E](https://www.luogu.com.cn/problem/CF1986E)

## 题意

给定一个参数 $n$。你有一个 $n \times n$ 的矩阵，试在该矩阵上构造 $n$ 个点 $(x_1, y_1), (x_2, y_2), \cdots, (x_n, y_n)$，使得他们两两的曼哈顿距离构成的集合 $H$ 最大。

## 分析思路

乍一看似乎没什么思路，[手玩](https://www.luogu.com.cn/paste/vxrbq433)几组样例试试看。

对于 $n = 3$，样例是一组构造，$H$ 的大小为 $4$，下文讨论 $n > 3$ 的情况。

注意到对于每个 $n$，$H$ 的大小为 $2 \times n - 1$，也就是能构造出在 $n \times n $ 的矩阵里所有的曼哈顿距离。

由于我们要构造出曼哈顿距离 $1$，则必须有两个贴在一起。不妨令他们是 $(1, 1)$ 与 $(2, 1)$。

剩余的点，经过暴力打表可以发现安排在 $y = x$ 的对角线上是合法的构造。

原理在于，对于 $n > 3$，至少有两个除 $(1, 1)$ 以外的点被安排在了对角线上，这些点之间可以构造出曼哈顿距离 $2$。

然后对于在第 $i$ （$i \geq 3$）行的被安排在对角线上的点 $(i, i)$，注意到它与 $(1, 1)$ 构造出了 $2i - 2$，与 $(2, 1)$ 构造出了 $2i - 3$。我们将其罗列可以发现会构造出 $\{3, 4, \cdots, 2\times n - 2\}$，再加上之前构造出的曼哈顿距离 $\{0, 1, 2\}$，最终构造出的 $H$ 的大小就是 $2 \times n - 1$，符合结论。

时间复杂度 $O\left(n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 t, n;
inline void solve(void) {
    cin >> n, cout << "1 1\n2 1\n";
    for (int i = 3; i <= n; i++) {
        cout << i << ' ' << i << '\n';
    }
    cout << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

