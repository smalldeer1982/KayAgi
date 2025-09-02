# [POI 2006] ORK-Ploughing

## 题目描述

Byteasar, the farmer, wants to plough his rectangular field. He can begin with ploughing a slice from any of the field's edges, then he can plough a slice from any unploughed field's edges, and so on, until the whole field is ploughed. After the ploughing of every successive slice, the yet-unploughed field has a rectangular shape. Each slice has a span of $1$, and the length and width of the field are the integers $n$ and $m$.

Unfortunately, Byteasar has only one puny and frail nag (horse) at his disposal for the ploughing. Once the nag starts to plough a slice, it won't stop until the slice is completely ploughed. However, if the slice is to much for the nag to bear, it will die of exhaustion, so Byteasar has to be careful. After every ploughed slice, the nag can rest and gather strength. The difficulty of certain parts of the field varies, but Byteasar is a good farmer and knows his field well, hence he knows every part's ploughing-difficulty.

Let us divide the field into $m\times n$ unitary squares - these are called tiles in short.

We identify them by their coordinates $(i,j)$, for $1\le i\le m$ and $1\le j\le n$.

Each tile has its ploughing-difficulty - a non-negative integer.

Let $t_{i,j}$ denote the difficulty of the tile which coordinates are $(i,j)$.


For every slice, the sum of ploughing-difficulties of the tiles forming it up cannot exceed a certain constant $k$ - lest the nag dies.

A difficult task awaits Byteasar: before ploughing each subsequent slice he has to decide which edge of the field he'll plough, so that the nag won't die. On the other hand, he'd like to plough as few slices as possible.

TaskWrite a programme that:

reads the numbers $k$,$m$ and $n$ from the input file, as well as the ploughing-difficulty coefficients,     determines the best way to plough Byteasar's field,     writes the result to the output file.

Byteasar想耕种他那块矩形的田，他每次能耕种矩形的一边（上下左右都行），在他每次耕完后，剩下的田也一定是矩形，每块小区域边长为$1$，耕地的长宽分别为$m$和$n$，不幸的是Byteasar只有一匹老弱的马，从马开始耕地开始，只有当它耕完了一边才会停下休息。但有些地会非常难耕以至于马会非常的累，因此Byteasar需要特别小心。当耕完了一边之后，马可以停下来休息恢复体力。每块地耕种的难度不一，但是Byteasar都非常清楚。我们将地分成$m\times n$块单位矩形——我们用坐标$(i,j)$来定义它们。每块地都有一个整数$t_{i,j}$,来定义$(i,j)$的耕种难度。所以每次马耕一边地时的难度就是所有它耕种的地的难度总和，对于这匹虚弱的马而言，这个值不能超过他的体力值。Byteasar想知道在马不死掉的情况下最少需要耕多少次才能把地耕完。


## 说明/提示

感谢@NaVi\_Awson 提供翻译


## 样例 #1

### 输入

```
12 6 4
6 0 4 8 0 5
0 4 5 4 6 0
0 5 6 5 6 0
5 4 0 0 5 4```

### 输出

```
8```

# 题解

## 作者：Alex_Wei (赞：7)

> *[P3444 [POI2006]ORK-Ploughing](https://www.luogu.com.cn/problem/P3444)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

有趣的思维题。

考虑到最后必然是行或者列被删完，所以我们不妨设行被删完。

接下来，考虑固定左右各删去多少列，即设 $f_{l,r}$ 表示还剩 $l\sim r$ 这些列时，尽量删行之后剩下来的行数的区间 $[p_{l,r},q_{l,r}]$（因为我们要让行尽快被删完）。

区间 $[p,q]$ 是**唯一的**，反证法可证：假设存在另一个区间 $[p',q']$，不妨设 $q'<q$，那么可以删到 $[p,q']$，与 “尽量删” 的定义矛盾。同理，若 $p<p'$，我们也可以删到 $[p,q]$。$\square$

考虑如何求出 $f_{l,r}$。显然，它要从 $f_{l-1,r}$ 和 $f_{l,r+1}$ 转移过来。如果 $f_{l-1,r}$ 最左边一列能删掉，即 $k\geq \sum_{\\i=p_{l-1,r}}^{q_{l-1,r}}t_{i,j}$，那么 $f_{l,r}$ 继承 $f_{l-1,r}$。同理，若 $f_{l,r+1}$ 最右边一列能删掉，$f_{l,r}$ 也可以继承 $f_{l,r+1}$。任意继承不会影响复杂度：均摊证明时间复杂度是 $\mathcal{O}(nm)$ 的。

同理，假设列被删完再做一遍上述算法即可得到正确答案。

```cpp
const int N = 2e3 + 5;
int n, m, k, ans = N << 1, row[N][N], c[N][N];
pii f[N][N];
int main(){
	cin >> k >> m >> n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			c[i][j] = c[i - 1][j] + (row[i][j] = read()), row[i][j] += row[i][j - 1];
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
			f[i][j] = {0, m}; f[1][n] = {1, m};
	for(int len = n; len; len--)
		for(int l = 1, r = len; r <= n; l++, r++) {
			int p = f[l][r].fi, q = f[l][r].se;
			if(!p) continue;
			while(p <= q && c[r][p] - c[l - 1][p] <= k) p++;
			while(p <= q && c[r][q] - c[l - 1][q] <= k) q--;
			if(p > q) cmin(ans, n - len + m);
			if(row[l][q] - row[l][p - 1] <= k) f[l + 1][r] = {p, q};
			if(row[r][q] - row[r][p - 1] <= k) f[l][r - 1] = {p, q};
		}
	for(int i = 1; i <= m; i++)
		for(int j = i; j <= m; j++)
			f[i][j] = {0, n}; f[1][m] = {1, n};
	for(int len = m; len; len--)
		for(int l = 1, r = len; r <= m; l++, r++) {
			int p = f[l][r].fi, q = f[l][r].se;
			if(!p) continue;
			while(p <= q && row[p][r] - row[p][l - 1] <= k) p++;
			while(p <= q && row[q][r] - row[q][l - 1] <= k) q--;
			if(p > q) cmin(ans, n + m - len);
			if(c[q][l] - c[p - 1][l] <= k) f[l + 1][r] = {p, q};
			if(c[q][r] - c[p - 1][r] <= k) f[l][r - 1] = {p, q};
		}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：龙神哈迪斯 (赞：7)

[更优美的阅读体验](http://www.cnblogs.com/cjyyb/p/8466936.html)

我们知道，如果我们选定了以横向为主，或者纵向为主，
那么就有尽可能减少另一个方向上耕地的次数

所以分开贪心，但是本质相同，所以接下来只**考虑纵向为主**

既然确定了以纵向为主，那么就要尽可能减少横向操作的次数
所以，只要能够纵向耕地，就不考虑横向耕地
可是，如果到了某个时候，纵向无法耕了
此时必须横向耕
但是我们不知道应该从上面开始还是下面开始

为了解决这个问题
**我们假设上面最多耕的次数是有限次**
换种想法，我们假设上面至少耕这么多次
既然上面的次数确定，那么下方的耕地次数越少越好
所以耕地的优先级：
**左-右-上-下**
只要能够耕就一定耕
这样，**枚举-贪心的做法**(~~是不是很玄学~~)就可以做啦
横向、纵向分别算一遍
时间复杂度O((n+m)^2)

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int _=2005;
inline int read()
{
    char ch='!';int z=1,num=0;
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')z=-1,ch=getchar();
    while(ch<='9'&&ch>='0')num=(num<<3)+(num<<1)+ch-'0',ch=getchar();
    return z*num;
}
int K,m,n;
int ans=1e9,g[_][_],f[_][_];
int work1(int st)
{
    int s1=1,s2=1,t1=n,t2=m,cnt=0;
    int sum=0;
    while(s1<=t1&&s2<=t2)
    {
        cnt++;
        //左
        sum=g[t1][s2]-g[s1-1][s2];
        if(sum<=K){s2++;continue;}
        //右
        sum=g[t1][t2]-g[s1-1][t2];
        if(sum<=K){t2--;continue;}
        //上
        sum=f[s1][t2]-f[s1][s2-1];
        if(sum<=K&&s1<st){s1++;continue;}
        //下
        sum=f[t1][t2]-f[t1][s2-1];
        if(sum<=K){t1--;continue;}
        cnt=1e9;break;
    }
    return cnt;
}
int work2(int st)
{
    int s1=1,s2=1,t1=n,t2=m,cnt=0;
    int sum=0;
    while(s1<=t1&&s2<=t2)
    {
        cnt++;
        //上
        sum=f[s1][t2]-f[s1][s2-1];
        if(sum<=K){s1++;continue;}
        //下
        sum=f[t1][t2]-f[t1][s2-1];
        if(sum<=K){t1--;continue;}
        //左
        sum=g[t1][s2]-g[s1-1][s2];
        if(sum<=K&&s2<st){s2++;continue;}
        //右
        sum=g[t1][t2]-g[s1-1][t2];
        if(sum<=K){t2--;continue;}
        cnt=1e9;break;
    }
    return cnt;
}
int main()
{
    K=read();m=read();n=read();
    int x;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            x=read();
            f[i][j]=f[i][j-1]+x;
            g[i][j]=g[i-1][j]+x;
        }
    }
    for(int i=1;i<=n;i++)
    {
        ans=min(ans,work1(i));
    }//限制上方最多移动到第i行
    for(int i=1;i<=m;i++)
    {
        ans=min(ans,work2(i));
    }//限制左方最多移动到第j列
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：CatFromMars (赞：2)

很巧妙的题目！

不妨用 0/1 代表删除最上面一行/最下面一行，2/3 代表删除最左边一列/最右边一列。容易想到，总共的删除方式分成两大种：一个最后一次删除列，每一次删除行本质上是在为删除列服务；另一个最后一次删除行，每一次删除列本质上是在为删除行服务。

这两种情况将读入的矩阵转置即可，本质一致。接下来只讨论第一种情况。

无疑，这种情况下能够删除列就尽量删除列，那么删除行的情况呢？

容易想到最显然的暴力：能删除列就删除列，否则 dfs 当前删除最上面的一行，还是最下面的一行。如果将操作序列列出来，是非常无序的。

考虑进行一个简单的“有序化”操作。如果对于两个操作序列，出现的 0 的次数和 1 的次数分别一样多，那么这两个操作序列明显等价。我们只保留字典序较小的那个。通过这样的化简，可以得到一个贪心策略——在 0，1 操作均可进行时，会优先选择 0 操作。

当然，这样的贪心策略是有瑕疵的。当第一行和最后一行都可以删除。先删除最后一行的时候，接下来可以删除列，但是删除第一行接下来仍然无法删除列，此时这个策略就不正确了。

接下来更细致的分析接下来的盘面，从而对策略进行一定调整：

- 先删除进行 1 操作，此后不进行 0 操作。
  - 此时 0 的数量已经确定。这启发我们通过枚举“0 的数量上界”对这些情况进行统计。
  - 更详细的来说，设 0 操作最多会进行 $l$ 次。在 $l$ 次以内都尽可能进行 0 操作，否则进行 1 操作。

- 先进行 1 操作，接下来仍会进行 0 操作。
  - 此时显然先进行 0 操作再进行 1 操作符合“字典序最小”的原则。反而是先进行 1 操作再进行 0 操作不满足“字典序最小”。因此“优先进行 0 操作”的策略仍成立。

此时这道题的做法也已得出：通过枚举 0 操作数量上界 $l$，分别计算最小操作次数。由上面的分析可知，这样可以覆盖到所有可能的最优情况。

一些代码上的小细节问题（这道题样例较弱，没办法下数据，我太菜了调了很久 QAQ）：
1. $l$ 一定是从 $0$ 开始枚举！（不进行 0 操作的情况）
2. 注意删除列和行的时候要保证它们存在。（一开始没有判断导致 70pts 调了好一会 QAQ） 

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2000;
int qk, n, m, A[N + 10][N + 10], b[N + 10][N + 10];
int suml[N + 10][N + 10], sumc[N + 10][N + 10];
void change() {//矩阵转置
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			b[j][i] = A[i][j];
	swap(n, m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			A[i][j] = b[i][j];
}
int work(int lim) {//计算 0 操作在 lim 次以内的最小操作次数
	int cnt = 0, up = 0, dn = 0;
	int x1 = 1, x2 = n, y1 = 1, y2 = m;
	while(cnt < m) {//cnt 是已删除列的数量
		int a = sumc[x2][y1] - sumc[x1 - 1][y1];
		int b = sumc[x2][y2] - sumc[x1 - 1][y2];
		if(a <= qk && y1 <= m) y1++, cnt++;
		else if(b <= qk && y2 > 0) y2--, cnt++;
		else {
			int c = suml[x1][y2] - suml[x1][y1 - 1];
			int d = suml[x2][y2] - suml[x2][y1 - 1];
			if(c <= qk && up < lim && x1 <= n) up++, x1++;
			else if(d <= qk && x2 > 0) dn++, x2--;
			else return N * 2 + 10;
		}
	}
	return cnt + up + dn;
}
int main() {
	cin >> qk >> m >> n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> A[i][j];

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			suml[i][j] = suml[i][j - 1] + A[i][j];
			sumc[i][j] = sumc[i - 1][j] + A[i][j];
		}
	int ans1 = N * 2 + 10;
	for(int i = 0; i <= n; i++)
		ans1 = min(ans1, work(i));
	change();

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			suml[i][j] = suml[i][j - 1] + A[i][j];
			sumc[i][j] = sumc[i - 1][j] + A[i][j];
		}
	int ans2 = N * 2 + 10;
	for(int i = 0; i <= n; i++)
		ans2 = min(ans2, work(i));
	cout << min(ans1, ans2) << endl;
}
```

---

## 作者：mountzhu (赞：1)

首先可以记搜，然后可以随机化贪心，然后可以退火。

但这个贪心确实难想。

考虑最后的形态必然是只剩一行或一列，那么这启发我们以行为主或以列为主来贪心。

这相当于为我们规定了一个优先级，在这个优先级下的贪心才是正确的，因为和最后的子结构是吻合的。

那我们两个都做一遍，是类似的，下面以行优先为例。

那么考虑我们的贪心策略应该是先把行删完，那么我们在过程中一定**不能删太多的列**，这样不符合结构，对答案不优。或者说，我们一次性删列，把列**留到一起删**是最优的（我们**答案下界正是这样的**，只删行或者只删列，~~这样看起来就是非常优美的~~）。

但是总有删列的时候，所以我们枚举删多少列，然后每次按照 “上下左右” 的顺序删，取最小则是对的。列优先同理。

具体证明看大神 Alex_wei 的题解吧。

#### $\mathrm{Code}$

------
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e3+5;
int n,m,K,fi[N][N],suml[N][N],sumr[N][N];
int ans=1e9+1;
int read(){
	char ch=getchar();int x=0,f=1;
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int main(){
	K=read(),m=read(),n=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)fi[i][j]=read();
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)sumr[i][j]=sumr[i][j-1]+fi[i][j];
	}
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j)suml[j][i]=suml[j-1][i]+fi[j][i];
	}
	for(int i=1;i<=m;++i){
		int lx=1,ly=1,rx=n,ry=m,ans1=0;
		while(lx<=rx&&ly<=ry){
			++ans1;
			if(sumr[lx][ry]-sumr[lx][ly-1]<=K){++lx;continue;}
			if(sumr[rx][ry]-sumr[rx][ly-1]<=K){--rx;continue;}
			if(suml[rx][ly]-suml[lx-1][ly]<=K&&ly<i){++ly;continue;}
			if(suml[rx][ry]-suml[lx-1][ry]<=K){--ry;continue;} 
			ans1=1e9+1;break;
		}ans=min(ans,ans1);
	}
	for(int i=1;i<=n;++i){
		int lx=1,ly=1,rx=n,ry=m,ans2=0;
		while(lx<=rx&&ly<=ry){
			++ans2;
			if(suml[rx][ly]-suml[lx-1][ly]<=K){++ly;continue;}
			if(suml[rx][ry]-suml[lx-1][ry]<=K){--ry;continue;} 
			if(sumr[lx][ry]-sumr[lx][ly-1]<=K&&lx<i){++lx;continue;}
			if(sumr[rx][ry]-sumr[rx][ly-1]<=K){--rx;continue;}
			ans2=1e9+1;break;
		}ans=min(ans,ans2);
	}printf("%d",ans);
	return 0;
}
```

---

## 作者：hovny (赞：1)

## 解题思路

**枚举+贪心**

### 分析

~~这个也不是很显然，~~$n\times m$ 的矩形，则 $ans \in [min(n,m),n+m]$，并且 $n$ 或 $m$ 肯定会完整地做出贡献

我们可以把这个模型抽象为有两个长度分别为 $n$ 和 $m$ 的队列，矩形消完的条件便是存在一个队列为空

那么我们现在假设 $n$ 一定能完整地做出贡献，也就是说只要有一行能删，就可以优先删去

因为无论如何，$n$ 可以完整做出贡献，则每行会进行一个删去的操作，先删和后删是等价的（假设我们已经得出删列的最优方案），所以只要贪心选择，能删就删即可

接着再考虑列的删除情况

左或右，删多少，两个变量，对于这种情况，由于列的数目比较小，直接枚举左侧或右侧**最多**能删去的列数，如此一来就可以贪心地得出另一侧最少需要删多少列，也就可以得出这种情况（一侧确定删去列数）下最少次数

也就是说，我们只需要按照 **上下>左>右 的优先级顺序**，即可贪心地得出该种情况的最少次数

同理，我们能够处理出 $m$ 能完整做出贡献的情况

在所有情况中取最小即可

### Warning

1、枚举一侧删去的行列数时，可能存在不删（即为 $0$ ）的情况，从 $0$ 开始枚举即可

2、注意优先级顺序，以及行列切勿弄混

## Code

```cpp
#include<bits/stdc++.h>
#define rgt register
#define rint rgt int
#define LL long long
#define rll rgt LL
#define inf 0x7f7f7f7f
#define N 2003
using namespace std;
template<class K>inline bool cmax(K&a,const K&b){return(a<b)?a=b,1:0;}
template<class K>inline bool cmin(K&a,const K&b){return(a>b)?a=b,1:0;}
inline int read() {
	rgt int s=0;
	rgt char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) s=(s<<1)+(s<<3)+c-'0',c=getchar();
	return s;
}
int k,n,m,f[N][N],g[N][N],ans=inf;
inline void solve1(rint val) {
	rint l=1,r=n,i=1,j=m;
	while(i<=j) {
		if(g[r][i]-g[l-1][i]<=k) ++i;//优先左
		else if(g[r][j]-g[l-1][j]<=k) --j;//其次从右侧
		else if(l<=val&&f[l][j]-f[l][i-1]<=k)//在枚举范围内的话从上侧删
			while(l<=val&&f[l][j]-f[l][i-1]<=k) ++l;
		else if(f[r][j]-f[r][i-1]<=k) --r;//否则贪心取下侧
		else return;
	}cmin(ans,n+m-(r-l+1));
}
inline void solve2(rint val) {
	rint l=1,r=m,i=1,j=n;
	while(i<=j) {
		if(f[i][r]-f[i][l-1]<=k) ++i;//优先上
		else if(f[j][r]-f[j][l-1]<=k) --j;//其次下侧
		else if(l<=val&&g[j][l]-g[i-1][l]<=k)//如果允许从左侧
			while(l<=val&&g[j][l]-g[i-1][l]<=k) ++l;
		else if(g[j][r]-g[i-1][r]<=k) --r;//否则贪心右侧
		else return;
	}cmin(ans,n+m-(r-l+1));
}
int main() {
	rint i,j,c;k=read(),m=read(),n=read();
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			c=read(),
			f[i][j]=f[i][j-1]+c,//每行的前缀和
			g[i][j]=g[i-1][j]+c;//每列的前缀和
	for(i=0;i<=n;i++) solve1(i);//枚举上侧最多删去行数
	for(j=0;j<=m;j++) solve2(j);//枚举左侧最多删去列数
	printf("%d",ans);
	return 0;
}
```

---

## 作者：zong15632539rongjuan (赞：0)

##### 题目翻译 
Byteasar 想耕种他那块矩形的田，他每次能耕种矩形的一边（上下左右都行），在他每次耕完后，剩下的田也一定是矩形，每块小区域边长为 $1$，耕地的长宽分别为 $m$ 和 $n$，不幸的是 Byteasar 只有一匹老弱的马，从马开始耕地开始，只有当它耕完了一边才会停下休息。但有些地会非常难耕以至于马会非常的累，因此 Byteasar 需要特别小心。当耕完了一边之后，马可以停下来休息恢复体力。每块地耕种的难度不一，但是 Byteasar 都非常清楚。我们将地分成 $m\times n$ 块单位矩形——我们用坐标 $(i,j)$ 来定义它们。每块地都有一个整数 $t_{i,j}$,来定义 $(i,j)$ 的耕种难度。所以每次马耕一边地时的难度就是所有它耕种的地的难度总和，对于这匹虚弱的马而言，这个值不能超过他的体力值。Byteasar 想知道在马不死掉的情况下最少需要耕多少次才能把地耕完。
##### 算法
###### 贪心
只需要做出在当前看来是最好的选择就能获得最好的结果，而不需要考虑整体上的最优，即使目光短浅也是没有关系的。
##### 分析
我们先从左到右枚举最小难度，就要以左——右——上——下的顺序来耕地（左到右耕地如果成功了就不用上下耕地了，使左右优先，上下尽量不耕地）。上下也是一样，以上——下——左——右的顺序来耕地（上到下耕地如果成功了就不用左右耕地了，使上下优先，左右尽量不耕地）。  
不过我们如果每一次都把这次耕地的难度求出来可能非常浪费时间，所以我们可以用两个前缀和数组———行和列，这样每次求难度就比较省时了。
##### 过程分析
1. 预处理每行和每列耕种难度的前缀和。
2. 纵向枚举最小难度。
3. 横向继续枚举最小难度。
1. 输出最终的最小难度。

———————————————————————————————
##### 代码
```
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
const int max_n = 2005;
inline int k, m, n, t[max_n][max_n], u[max_n][max_n], l[max_n][max_n];
inline int xs, ys, xe, ye, ans = 1e9;
inline int zx(int x) {
    int s = 0;
    xs = ys = 1;
    xe = n;
    ye = m;
    for (int i = 1; xs <= xe && ys <= ye; ++i) {
        ++s;
        if (l[xe][ys] - l[xs - 1][ys] <= k) {
            ++ys;
            continue;
        }
        if (l[xe][ye] - l[xs - 1][ye] <= k) {
            ye--;
            continue;
        }
        if (u[xs][ye] - u[xs][ys - 1] <= k && xs < x) {
            ++xs;
            continue;
        }
        if (u[xe][ye] - u[xe][ys - 1] <= k) {
            xe--;
            continue;
        }
        s = 1e9;
        break;
    }
    return s;
}
inline int hx(int x) {
    int s = 0;
    xs = ys = 1;
    xe = n;
    ye = m;
    for (int i = 1; xs <= xe && ys <= ye; ++i) {
        ++s;
        if (u[xs][ye] - u[xs][ys - 1] <= k) {
            ++xs;
            continue;
        }
        if (u[xe][ye] - u[xe][ys - 1] <= k) {
            xe--;
            continue;
        }
        if (l[xe][ys] - l[xs - 1][ys] <= k && ys < x) {
            ++ys;
            continue;
        }
        if (l[xe][ye] - l[xs - 1][ye] <= k) {
            ye--;
            continue;
        }
        s = 0x3f3f3f3f;
        break;
    }
    return s;
}
int main() {
    scanf("%d%d%d", &k, &m, &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) scanf("%d", &t[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            u[i][j] = u[i][j - 1] + t[i][j];
            l[i][j] = l[i - 1][j] + t[i][j];
        }
    for (int i = 1; i <= n; ++i) ans = min(ans, zx(i));
    for (int i = 1; i <= m; ++i) ans = min(ans, hx(i));
    printf("%d\n", ans);
    return 0;
}
```

---

