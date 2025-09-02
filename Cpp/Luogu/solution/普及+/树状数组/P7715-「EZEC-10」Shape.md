# 「EZEC-10」Shape

## 题目背景

规定 $(x,y)$ 表示第 $x$ 行第 $y$ 列的格子。

## 题目描述

小 A 有一个 $n\times m$ 的网格，一些为白色格子，剩余为黑色格子。

小 A 选择四个整数 $x_1,x_2,y_1,y_2$，满足如下条件：

1. $1\le x_1<x_2\le n$ 且 $1\le y_1<y_2\le m$。
2. $x_1+x_2$ 为偶数。

若 $(x_1,y_1)\to (x_2,y_1),(x_1,y_2)\to (x_2,y_2),(\frac{x_1+x_2}{2},y_1)\to (\frac{x_1+x_2}{2},y_2)$ 这三段中的格子均为白色，则称这三段构成的图形为 H 形。

小 A 想知道，这个网格中存在多少不同的 H 形。

**两个 H 形相同，当且仅当两个 H 形的 $x_1,x_2,y_1,y_2$ 均相同。**

## 说明/提示

**【样例 1 解释】**

$(x_1,x_2,y_1,y_2)=(1,3,3,4)$ 的 H 形符合。

**【样例 2 解释】**

$(x_1,x_2,y_1,y_2)=(1,5,1,3),(2,4,1,3)$ 的 H 形符合。

**【数据规模与约定】**

**本题采用捆绑测试。**

- Subtask 1（1 point）：$n=2$。
- Subtask 2（9 points）：$ n,m\le 50$。
- Subtask 3（10 points）：$ n,m\le 100$，**时限为 $500ms$**。
- Subtask 4（30 points）：$ n,m\le 500$。
- Subtask 5（50 points）：无特殊限制。

对于 $100\%$ 的数据，$2\le n,m\le 2\times 10^3$。

## 样例 #1

### 输入

```
3 4
1 0 0 0
1 1 0 0
1 0 0 0```

### 输出

```
1```

## 样例 #2

### 输入

```
5 3
0 1 0
0 1 0
0 0 0
0 1 0
0 1 0```

### 输出

```
2```

# 题解

## 作者：_Arahc_ (赞：7)

## 题意简述

给定一个 $n\times m$ 的 $0-1$ 矩阵，定义一个 H 形为一个长得像 H （感性理解，具体见[题目描述](https://www.luogu.com.cn/problem/P7715)）的图形，求有几个由 $0$ 组成的 H 形。

例如下图图示（白色为 $0$，黑色为 $1$），一共有 $6$ 个 H 形，这也告诉我们 **H 形是可以互相有重叠甚至有包含关系的**（但不同的 H 形不会完全恰好重合）。

![](https://cdn.luogu.com.cn/upload/image_hosting/b2tuqlvi.png)

## 题目分析

考虑到 $n,m\leqslant 2\times 10^3$。需要设计一个 $n\times m$ （或带一个 log ）的算法，直接暴力枚举四元组中的任意两个都无法完成，需要找到 H 形中的一个特性。 

首先考虑是否可以枚举 H 的竖线（每个 H 有两个竖线，这里考虑左侧）。考场上糊了一个想法：记录每一条竖着的白线，以及每一个点往右可以到达的最近的点，图示情况可以后续推乘法原理加法原理的式子做到 $\operatorname{O}{(1)}$。随后很快发现了不可行，因为即使我记录了每一个点向右最多可以到达哪些点，整体判断一个 H 的两条竖线是否一一对应还是 $\operatorname{O}{(n)}$ 的。

除此之外，即使两个 $H$ 竖线部分是包含关系，也不一定代表横线部分重合，例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/4xrx7usr.png)      ![](https://cdn.luogu.com.cn/upload/image_hosting/egdm24nr.png)

这两种情况都无法简单地区分，例如左侧这种，高度为 $3$ 的 H 和高度为 $9$ 的 H 竖线部分共线但是横线部分不共线。右侧这种情况说明不能只记录每一个白格子右侧第一个白格子，因为两个 H 可能只有一个竖线共线。

因此考虑竖线的情况比较难处理，又因为 H 里面只有一条横线，来考虑横线的情况。

对于任何一个 H，显然横线的两端刚好是竖线的中点。因此选择一个横线的两个端点，向上和向下延伸同样的高度（且都是白格子），就一定可以得出一个 H。

基于这种思想我们记录每一个格子向上最多可以延伸多少个格子，向下最多可以延伸多少个格子。

而显然一个横线两端的点向上和向下延伸的白格子应该是相同的，因此对于某一个格子而言，向上延伸和向下延伸的格子数取最小值，才会是以它为横线的一个端点，可能形成的高度最大的 H 的高度的一半。

（也就是 H 的最大高度为 $\min{(up,dn)}\times 2+1$）。


 ```cpp
// a 数组为输入的 0-1 矩阵
for(register int j=1;j<=m;++j){
	for(register int i=1;i<=n;++i){
		if(a[i][j]) up[i][j]=0;
		else up[i][j]=up[i-1][j]+1;
	}// 向上
	for(register int i=n;i>=1;--i){
		if(a[i][j]) dn[i][j]=0;
		else dn[i][j]=dn[i+1][j]+1;
	}// 向下
for(register int i=1;i<=n;++i)
	for(register int j=1;j<=m;++j)
		s[i][j]=min(up[i][j],dn[i][j]);
// 取 min
// 注意 H 的真正高度为 s[i][j]*2-1
// 因为中间那一个白格子在这里也算进去了
}
```

通过放在最前面的第一张图，我们知道同一个横线上可能出现多个大小不同的 H。假设每个横线上有若干白格子。我们发现……

（注：下图的白格子高度指的是最底下一行的横线的 $s$ ）


![](https://cdn.luogu.com.cn/upload/image_hosting/xq0vooh1.png)


第 $3$ 个可以和第 $1,4,7,8,11,12,13$ 个匹配出一个 H，第 $4$ 个可以和第 $1,7,8,12,13$ 个匹配成一个 H……

发现高度小的一定可以和高度大于等于它的匹配。且按照这种方法匹配得出的 H 不重不漏。

因此可以每次取出一段白色的横线（设长度为 $k$），取出横线上每个点的 $s$ 值，如果我们从小到大排个序，就会发现第 $i$ 个一定可以和第 $i+1,i+2,\dots,k$ 个匹配，一共有 $k-i$ 个 H。

每一段白色的横线取出并逐个计算，累加答案。由于有一个排序，最多有 $n$ 个长度为 $m$ 的横线，因此总的复杂度为 $\operatorname{O}{(n\times m\log m)}$ 的，可过。且只要有黑色的格子这东西就不会卡满。因此效率是非常可观的。


主要处理的部分：

 ```cpp
    int i=1;j=1;
	while(i<n){
		while(a[i][j] && j<=m) ++j;
		
		if(j>m){ // 避免 j 越界
			++i,j=1;
			continue;
		}

		tot=0;
		while(!a[i][j] && j<=m){ // 不要忘记 j<=m，会越界
			p[++tot]=s[i][j]-1; // 这里要-1（参见上面预处理代码注释）
			++j;
		}

		std::sort(p+1,p+1+tot); // 小到大排序

		for(register int k=1;k<=tot;++k) ans+=p[k]*(tot-k);
        // 对于每一个 k 一共 tot-k 个 H 可以匹配

		if(j>m){ // 越界判断
			++i,j=1;
			continue;
		}
	}
```

## 告诫后人

考场上本来用的优先队列 ```priority_queue```，惨遭 TLE，个人觉得可能是因为其每次插入和删除都是 $\log n$，也就是两个 $n\log n$，因此整体带了一个常数（再加上 STL 可能还有常数）。而 ```sort``` 是一个 $n\log n$，后续处理是 $n$ 的。整体常数小一些。

如果用优先队列 TLE 的话，如果算法没有错误可以改成直接存数组里再排序，说不定就 A 了呢~

---

## 作者：pengyule (赞：4)

*changelog: 2021.7.13 增加 50pts 的部分分代码。*

与众不同（？）但有些繁琐（！）的树状数组解法。

## 题意简述
在给定的 01 矩阵中统计由 `0` 构成的“H”形的数量。符合要求的“H”形满足：
1. 两竖一样长，且长度是大于 $1$ 的奇数
2. 横连接两竖的中点
3. 特殊地，满足 1.、2. 且完全相邻的两竖也算一个“H”形
4. 两个“H”形相同当且仅当它们在同一个位置完全重合

## 题解
### 分析
我们发现，确定一个“H”形只需要确定横杠的所在行和长度、一条竖线的所在列和长度。考虑枚举左侧交叉点的坐标。预处理出 $d_{i,j}$ 表示点 $(i,j)$ 作为“H”形的竖的中心，它到竖的上（或下）端点的距离最大值；$f_{i,j}$ 表示点 $(i,j)$ 作为“H”形横的左端点，能够向右延伸的最长长度，$g_{i,j}$ 则是作为右端点向左延伸的最长长度。

![image.png](https://i.loli.net/2021/07/12/EU2ONruLA63VjDo.png)
#### 50pts
在此基础上，我们只需要统计当竖线半径取长度 $x(x\le d_{i,j})$ 时，当前点 $(i,j)$ 右侧有几个点满足 $d_{i,?}\ge x(j<?<i+f_{i,j}-1)$。这就有点像“正序对”，只不过每个位置是 $x$，代码实现见[此](https://paste.ubuntu.com/p/kBZTQSrfWM/)。
#### 100pts
考虑优化 $x$ 的枚举。我们发现，当两侧竖线半径取长度 $l_1,l_2(l_1\le l_2)$ 时，答案为 $l_1-1$。因此，我们在原来的值域树状数组上，第一次从右到左枚举左端点，真正统计正序对，把以 $i,j$ 为左端点的正序对（两竖长度可以相等）的个数乘上 $(d_{i,j}-1)$；同理，第二次从左到右枚举右端点，真正统计逆序对，把以 $i,j$ 为右端点的逆序对（枚举的竖必须短于另一竖）个数乘上 $(d_{i,j}-1)$。这样，第一次就统计出所有 $l_1\le l_2$ 的“竖”对产生的答案，第二次就统计出所有 $l_1>l_2$ 的“竖”对产生的答案。（竖 $l_1$ 在 $l_2$ 左侧）

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2005][2005],d[2005][2005],f[2005][2005],c[2005],g[2005][2005];
void add(int x,int y){
	for(;x<=2000;x+=x&-x)c[x]+=y;
}
int ask(int x){
	int ans=0;
	for(;x;x-=x&-x)ans+=c[x];
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=m;i++){
		int mx=1;
		for(int j=1;j<=n;j++){
			if(a[j][i])mx=j+1;
			if(!a[j][i])d[j][i]=j-mx+1;
		}
		mx=n;
		for(int j=n;j>=1;j--){
			if(a[j][i])mx=j-1;
			if(!a[j][i])d[j][i]=min(d[j][i],mx-j+1);
		}
	}
	for(int i=1;i<=n;i++){
		int mx=m;
		for(int j=m;j>=1;j--){
			if(a[i][j])mx=j-1;
			else f[i][j]=mx-j+1;
		}
		mx=1;
		for(int j=1;j<=m;j++){
		    if(a[i][j])mx=j+1;
		    else g[i][j]=j-mx+1;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(c,0,sizeof(c));
		for(int j=m,k=m;j>=1;j--){
			if(a[i][j])continue;
			if(d[i][j]>1){
				while(k>j+f[i][j]-1){
					if(!a[i][k])add(d[i][k],-1);
					k--;
				}
				ans+=(d[i][j]-1)*(ask(n)-ask(d[i][j]-1));
				add(d[i][j],1);
			}
		}
		memset(c,0,sizeof(c));
		for(int j=1,k=1;j<=m;j++){
			if(a[i][j])continue;
			if(d[i][j]>1){
				while(k<j-g[i][j]+1){
					if(!a[i][k])add(d[i][k],-1);
					k++;
				}
				ans+=(d[i][j]-1)*(ask(n)-ask(d[i][j]));
				add(d[i][j],1);
			}
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：Suzt_ilymtics (赞：2)

[题目传送](https://www.luogu.com.cn/problem/P7715)

[更好的阅读体验？](https://www.cnblogs.com/Silymtics/p/15000439.html)

并没有用标签的做法，属于乱搞做法，复杂度比较依赖数据。

## Solution

- $O(n^5)$ 做法：

枚举 $x_1,y_1,x_2,y_2$，然后 $O(n)$判断是否合法。

- $O(n^4)$ 做法：

可以维护一个前缀和 $O(1)$ 判断两个点之间是否都是 $0$。

- $O(n^3)$ 做法：

预处理一个 $up_{i,j}$ 和 $down_{i,j}$ 分别表示这个点向上和向下最多延伸的距离。取 $\min$ 就可以得到该点的最大延伸距离 $h_{i,j}$。

考虑枚举每一条长度为 $0$ 的横线 $[l,r]$，假设这条横线在第 $i$ 行，那么这条横线的贡献就是两个端点的最大延伸距离的较小值。即 $\min(h_{i,l},h_{i,r})$。

枚举行数加上枚举每条横线的两个端点，总复杂度 $O(n^3)$。

- $O(n^2) \sim O(n^3)$ 的做法

发现每次枚举到一条横线只是计算了它两端点的贡献，考虑把横线上两点之间的贡献一起算。

如果固定一个点 $x$，考虑它对横线上其他点 $y$ 的贡献。那么当且仅当 $h_{i,x} \le h_{i,y}$ 时，这两个点形成的 “H”  的贡献为 $h_{i,x}$。

不过这样做当 $h_{i,x} = h_{i,y}$ 时 $h_{i,x}$ 的贡献会被计算两次，把这部分单独拿出来特判掉即可。

如何快速的找到 $\ge h_{i,x}$ 的值的数量？

我这里使用的是桶排，把每个 $h_{i,x}$ 放进桶里，从后向前做前缀和，$h_{i,x}$ 位置对应的前缀和 $-1$ 就是 $\ge h_{i,x}$ 的值的数量。

这里我先找到了这段横线中最大的 $h_{i,x}$，可以在预处理前缀和的时候减少枚举量。

这个做法在随机数据下跑的很快，感谢出题人没有把我卡成 $O(n^3)$。

- $O(n^2 \log n)$ 的做法

如果把上面的横线放进树状数组维护，复杂度是稳定的 $\log$ 。

## Code

代码写的是倒数第二个做法。

```cpp
/*
Work by: Suzt_ilymics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define int long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

int n, m, Ans = 0;
bool a[2020][2020];
int sumh[2020][2020];
int up[2020][2020], down[2020][2020];
int cnt[2020];

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

signed main()
{
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            a[i][j] = read();
            sumh[i][j] = sumh[i][j - 1] + a[i][j];
            if(a[i][j]) {
                up[i][j] = i;
            } else {
                up[i][j] = up[i - 1][j];
            }
        }
    }
    for(int i = 1; i <= m; ++i) {
        down[n + 1][i] = n + 1;
    }
    for(int i = n; i >= 1; --i) {
        for(int j = m; j >= 1; --j) {
            if(a[i][j]) {
                down[i][j] = i;
            } else {
                down[i][j] = down[i + 1][j];
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            up[i][j] = min(i - up[i][j] - 1, down[i][j] - i - 1);
        }
    }
    
    for(int i = 1; i <= n; ++i) {
        a[i][m+1] = 1;
        for(int j = 1, l = 1, r = 0; j <= m + 1; ++j) {
            if(a[i][j]) {
                if(l < r) {
                    int Sum = 0, Sum2 = 0;
                    memset(cnt, false, sizeof cnt);
                    int Max = -1;
                    for(int g = l; g <= r; ++g) cnt[up[i][g]] ++, Max = max(Max, up[i][g]);
                    for(int g = Max; g >= 0; --g) cnt[g] += cnt[g + 1];
                    for(int g = l; g <= r; ++g) Sum2 += up[i][g] * (cnt[up[i][g]] - cnt[up[i][g]+1] - 1), Sum += up[i][g] * cnt[up[i][g] + 1];
                    Ans += Sum + Sum2 / 2;
                }
                l = r = j + 1;
            } else {
                r = j;
            }
        }
    }
    printf("%lld", Ans);
    return 0;
}
```

---

## 作者：Eason_AC (赞：2)

## Content
有一个 $n\times m$ 的网格，网格上的格子被涂成了白色或者黑色。

设两个点 $(x_1,y_1)$ 和 $(x_2,y_2)$，如果以下三个条件均满足：

- $1\leqslant x_1<x_2\leqslant n$ 且 $1\leqslant y_1<y_2\leqslant m$。
- $2\mid (x_1+x_2)$。
- $(x_1,y_1)\rightarrow(x_2,y_1)$，$(x_1,y_2)\rightarrow(x_2,y_2)$，$(\dfrac{x_1+x_2}2,y_1)\rightarrow(\dfrac{x_1+x_2}2,y_2)$ 这三段中的格子均为白色。

那么我们称第三个条件中的三段构成的图形为 H 形。求 $n\times m$ 的网格里面有多少个不同的 H 形。

**数据范围：$2\leqslant n,m\leqslant 2\times 10^3$。**
## Solution
本题解分 Subtask 讲解。
### Subtask 1 (1 pt)：$n=2$
在这个 Subtask 中，我们无论如何选择两个点都不能同时满足前两个条件。因此答案是 $0$。
### Subtask 2 (9 pts)：$n,m\leqslant 50$
我们可以用 $\mathcal O(n^2m^2)$ 枚举出两个点 $(x_1,y_1)$ 和 $(x_2,y_2)$，然后我们直接枚举三段并判断是否三段都是白色格子，最后如果三个条件都满足的话，将其统计入答案即可。
### Subtask 3&4 (40 pts)：$n,m\leqslant 500$。
我们发现我们直接枚举两个点的话太耗费时间了，能否有更快的方法？

我们为什么不枚举两个中间点呢？因为这两个点都在同一行，枚举的复杂度可以降至 $\mathcal O(nm^2)$。

但是如果再去枚举三段的话又太浪费时间了，能否有更快的方法？

这时候预处理就派上用场了。我们可以先预处理出点 $(i,j)$ 向上最多能够到达的连续 $0$ 的个数 $s_{i,j}$ 和向下最多能够到达的连续 $0$ 的个数 $d_{i,j}$。可以通过枚举坐标再去向上向下直接暴力推，复杂度是 $\mathcal O(n^2m)$ 的。

然后枚举中间点的时候就可以直接求出两个中间点 $(a,b)$、$(c,d)$ 能够得到的 H 形的个数为 $\min\{s_{a,b},d_{a,b},s_{c,d},d_{c,d}\}$。直接统计入答案即可。
### Subtask 5 (50 pts)：正解
我们发现 $n,m\leqslant 2\times 10^3$ 的时候，上面的算法的复杂度还是太大了。能否有更快的方法？

一开始想能否用线段树/树状数组处理，然而还是我太 naive 了没有想出来。后来想到了一个可以用栈来处理的方法。

我们直接扫一遍这个网格，每逢被涂成黑色的格子或者到了一行的尽头，就把这个栈里头的所有元素拿出来，按照从小到大的顺序排个序，然后每一个在栈里头的元素 $st_k$，其对答案的贡献是 $st_k\times (top-k)$（其中 $top$ 指原来栈里面的元素个数），把这个贡献加入里面去并清空整个栈。否则将 $f_{i,j}=min\{s_{i,j},d_{i,j}\}$ 放入栈里头，复杂度大概是 $\mathcal O(nm\log m)$ 的？

预处理也可以变成 $\mathcal O(nm)$ 的，具体的就不多做赘述了，看代码吧。
## Code
```cpp
const int N = 2007;
int n, m, a[N][N], s[N][N], d[N][N], f[N][N];

namespace sub1 {
    iv work() {return printf("0"), void();}
}
namespace sub2 {
    iv work() {
        int ans = 0;
        F(int, x, 1, n) F(int, y, 1, m) Fo(int, x_, x + 2, n, 2) F(int, y_, y + 1, m) {
            int fl = 1;
            F(int, i, x, x_) if(a[i][y]) {fl = 0; break;}
            F(int, i, x, x_) if(a[i][y_]) {fl = 0; break;}
            F(int, j, y, y_) if(a[(x + x_) / 2][j]) {fl = 0; break;}
            ans += fl;
        }
        return write(ans), void();
    }
}
namespace sub3 {
    iv work() {
        int ans = 0;
        F(int, i, 1, n) F(int, j, 1, m) if(!a[i][j]) F(int, k, j + 1, m) if(!a[i][k]) {
            ans += min(min(min(s[i][j], d[i][j]), s[i][k]), d[i][k]);
        } else break;
        return write(ans), void();
    }
}
namespace sub4 {
    int st[N], top;
    ll ans = 0;
    iv work() {
        F(int, i, 1, n) {
            top = 0;
            F(int, j, 1, m + 1) if(a[i][j] == 1 || j == m + 1) {
                if(top) {
                    sort(st + 1, st + top + 1)/*, print_array1(st, top), puts("-------");*/;
                    F(int, k, 1, top - 1) ans += 1ll * st[k] * (top - k);
                    top = 0; 
                }
            } else st[++top] = f[i][j];
        }
        return write(ans), void();
    }
}

int main() {
    n = Rint, m = Rint;
    F(int, i, 1, n) F(int, j, 1, m) a[i][j] = Rint;
    // F(int, i, 1, n) F(int, j, 1, m) if(!a[i][j]) {
    //     F(int, k, i + 1, n) if(a[k][j] == 0) s[i][j]++; else break;
    //     R(int, k, i - 1, 1) if(a[k][j] == 0) d[i][j]++; else break;
    //     f[i][j] = min(s[i][j], d[i][j]);
    // } //这是 O(n^2m) 的预处理
    F(int, j, 1, m ) R(int, i, n, 1) s[i][j] = (a[i][j] == 0 ? ((a[i + 1][j] == 1 || i == n) ? 0 : s[i + 1][j] + 1) : 0);
    F(int, j, 1, m) F(int, i, 1, n) d[i][j] = (a[i][j] == 0 ? ((a[i - 1][j] == 1 || i == 1) ? 0 : d[i - 1][j] + 1) : 0);
    F(int, i, 1, n) F(int, j, 1, m) f[i][j] = min(s[i][j], d[i][j]); //这是 O(nm) 的预处理
    if(n == 2) sub1 :: work();
    else if(n <= 100 && m <= 100) sub2 :: work();
    else if(n <= 500 && m <= 500) sub3 :: work();
    else sub4 :: work();
    return 0;
}
```

---

## 作者：Ecrade_ (赞：1)

### $\text{Subtask 1}$

注意到 H 形高度必不小于 $3$，故直接输出 $0$ 即可。

---
### $\text{Subtask 2}$

依照题意暴力即可。

时间复杂度 $O(n^2m^2(n+m))$。

---
### $\text{Subtask 3}$

先预处理每行每列的前缀和，这样判断时可以做到 $O(1)$。

时间复杂度 $O(n^2m^2)$。

---
### $\text{Subtask 4}$

考虑枚举 H 形中的横杠。

定义 $f_{i,j}$ 为满足 $(i-k,j)\to (i+k,j)$ 这一段中格子均为白色的最大的 $k$。

那么横杠 $(x,y_1)\to (x,y_2)$ 的贡献为 $\min(f_{x,y_1},f_{x,y_2})$。

预处理 $f$ 数组后枚举横杠即可。

时间复杂度 $O(nm^2)$。

---
### $\text{Subtask 5}$

注意到枚举所有横杠太耗时，故考虑枚举每段极长横杠。（满足 $(x,y_1-1),(x,y_2+1)$ 均为黑色的横杠 $(x,y_1)\to (x,y_2)$ 即为极长横杠。）

每一段极长横杠 $(x,y_1)\to (x,y_2)$ 的总贡献即为 $\sum\limits^{y_2}_{a=y_1}\sum\limits^{y_2}_{b=a+1}\min(f_{x,a},f_{x,b})$。

将 $f_{x,y_1}$ 至 $f_{x,y_2}$ 从小到大排序，发现 $f_{x,y}$ 的贡献即为 $f_{x,y}\times (y_2-y)$。

时间复杂度 $O(nm\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,ans,a[2009],f[2009][2009];
bool ch[2009][2009];
inline ll read(){
	ll s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
inline bool readbool(){
	char ch = getchar();
	while (ch > '9' || ch < '0') ch = getchar();
	return ch ^ 48;
}
ll calc(ll x,ll l,ll r){
	if (l > r) return 0;
	ll cnt = 0,res = 0;
	for (ll i = l;i <= r;i += 1) a[cnt ++] = f[x][i];
	sort(a,a + cnt);
	for (ll i = 0;i < cnt;i += 1) res += a[i] * (cnt - i - 1);
	return res;
}
int main(){
	n = read(),m = read();
	for (ll i = 1;i <= n;i += 1) for (ll j = 1;j <= m;j += 1) ch[i][j] = readbool();
	for (ll i = 1;i <= m;i += 1){
		for (ll j = 1,cur = -1;j <= n;j += 1){
			if (ch[j][i]) cur = -1;
			else cur += 1;
			f[j][i] = cur;
		}
		for (ll j = n,cur = -1;j >= 1;j -= 1){
			if (ch[j][i]) cur = -1;
			else cur += 1;
			f[j][i] = min(f[j][i],cur);
		}
	}
	for (ll i = 1;i <= n;i += 1){
		ll pre = 1;
		for (ll j = 1;j <= m;j += 1) if (ch[i][j]) ans += calc(i,pre,j - 1),pre = j + 1;
		ans += calc(i,pre,m);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Zxsoul (赞：0)

**前言**
> 思路来自讲评，大体说一下，并且点出我的错误 

**思路**

先从小的入手，对于一条中间没有黑格子的横杠，他所产生的贡献取决于两边向**竖直方向**的最小延伸距离，因此我们可以预处理出每个点的最小延伸长度 $f_{i,j}$ ，然后枚举横杠，横杠的判断需要前缀和操作

下面是我处理 $f_{i,j}$ 的代码，看了 @[Ecrade](https://www.luogu.com.cn/user/322075) 的代码，发现自己的处理并不是 $O(nm)$，而是 $O(n^2m)$，都是极品数据
```c
		for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int k=1;
			while (1)
			{
				if (a[i+k][j]+a[i-k][j]>0 || i+k>n || i-k<1) break;
				k++;
			}
			f[i][j]=k-1;//处理出从每个点上下的的最小值 
		}

```
向两头延伸法坏处就是容易被卡成 $O(n^2m)$

**说正解** 

既然 $f$ 我们可以处理，转换到横杠上是否也可以，不难发现，一条长横杠中包含子横杠，这些子横杠也会产生贡献，因此我们可以直接枚举长横杠，对于横杠内的一个点，产生的贡献就是和比他 $f$ 大的个数，将 $f$ 进行排序，每个点做的贡献就 $f[i][k]\times (y_2-y)$，其中 $y$ 是区间枚举，最终在 $O(nm\log m)$ 完成题目
```c
/*
	从贡献去考虑
	对于一条横杠，他产生的贡献就是两边能够向上或下延伸的最小公共值
	横杠需要枚举，并判断是否是白色的，横杠内部是否全为白格子，用前缀和
	这样就可以拿到 50 分 
*/
#include <bitset>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

const int A = 1e7+10;
const int B = 1e6+10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
//int sum[2009][2009];
int a[2009][2009];
int n,m;
int ans;
int f[2009][2009];
main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			a[i][j]=read();
//			sum[i][j]=sum[i][j-1]+a[i][j];
		}
	}
	for (int i=1;i<=m;i++)
	{
		for (int j=1,cur=-1;j<=n;j++)
		{
			if (a[j][i]) cur=-1;
			else cur++;
			f[j][i]=cur;//处理出从每个点上下的的最小值 
		}
		for (int j=n,cur=-1;j>=1;j--)
		{
			if (a[j][i]) cur=-1;
			else cur++;
			f[j][i]=min(f[j][i],cur);
		}
	}
	for (int i=1;i<=n;i++)
	{
		int last=1,now=0,tot=0;
		a[i][m+1]=1;
		for (int j=1;j<=m+1;j++)
		{
			if (!a[i][j]) continue;
			else 
			{
				if (j-now-1<=1) {now=j;continue;}
				else//中间有白色格子 
				{
					int y1=now+1;
					int y2=j-1;
//					sort(&a[i][y1], &a[i][y2 + 1]);
					sort(f[i]+y1,f[i]+y2+1);
					for (int k=y1;k<=y2;k++)
						ans+=f[i][k]*(y2-k);
					now=j;
				}
			}
		}
	} 
	printf("%lld",ans);
} 


```

---

