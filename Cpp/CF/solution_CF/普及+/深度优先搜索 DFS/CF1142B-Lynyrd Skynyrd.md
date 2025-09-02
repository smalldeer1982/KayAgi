# Lynyrd Skynyrd

## 题目描述

*题目名称：Lynyrd 与 Skynyrd*  


最近 Lynyrd 和 Skynyrd 去了一个商店，在那里 Lynyrd 买了一个长度为$n$的排列$p$，Skynyrd 买了一个一个长度为$m$的数列$a$，并且$a_i \in[1,n], a_i \in Z$。  

Lynyrd 和 Skynyrd 感到无聊，所以他们给了你$q$个询问，每个询问格式如同：“$a$的**子段**$[l, r]$是否有一个**子序列**$s$，满足$s$是$p$的一个循环移位？”请你回答这些询问。  

一个长度为$n$的*排列*是一个由$n$个整数组成的序列，满足从$1$到$n$的所有整数在其中恰好出现$1$次。

一个排列$(p_1, p_2, \ldots, p_n)$的*循环移位*是排列$(p_i, p_{i+1}, \ldots, p_n, p_1, p_2, \ldots, p_{i-1})$，其中$i \in [1, n]$。例如：排列$(2, 1, 3)$有$3$个显然的循环移位：$(2, 1, 3); (1, 3, 2); (3, 2, 1)$。

一个序列$a$的子段$[l, r]$的*子序列*是一个序列$a_{i_1}, a_{i_2}, \ldots a_{i_k}$，其中$l \leq i_1 < i_2 < \ldots < i_k \leq r$。

## 说明/提示

样例1中子段$[1, 5]$是$\underline1, 2, \underline3, 1, \underline2$，它包含的一个子序列$1, 3, 2$是给定排列的一个循环移位；子段$[2, 6]$包含的子序列$2, 1, 3$与给定排列等价；子段$[3, 5]$只有一个长度为$3$的子序列$3, 1, 2$，但是这不是给定序列的循环移位。  

样例2中所有可能的循环移位是$1, 2$和$2, 1$。子段$[1, 2]$是$1, 1$，不包含任何循环移位；子段$[2, 3]$是$1, 2$，是一个循环移位；子段$[3, 4]$是$2, 2$，它的所有子段中没有一个是给定排列的循环移位。

## 样例 #1

### 输入

```
3 6 3
2 1 3
1 2 3 1 2 3
1 5
2 6
3 5
```

### 输出

```
110
```

## 样例 #2

### 输入

```
2 4 3
2 1
1 1 2 2
1 2
2 3
3 4
```

### 输出

```
010
```

# 题解

## 作者：SSerxhs (赞：22)

并不知道为什么题解都是$O(nlog_2n)$的...明明可以线性的啊

目前你谷最优解，还有很多没卡常的地方

这题是子序列问题，且通过p数组可以知道每个数字的后继（这也是p唯一用途，以下均只讨论a数组的情况），且可以贪心证明每个数字只需要距离它最近的那个后继，可以考虑通过这一点把序列自动机优化到线性构建。

具体方法：对于每个数字记录pre数组表示上一个相同的数字的位置（通过动态记录一个lst数组表示某个数字最晚出现位置实现），然后从左到右扫一遍，扫到$a_i$时从$lst[a_i]$开始沿着pre边向上跳，只要其没有出边就把出边记为当前位置，这样出边的含义就是距离最近的后继。

正常思路到这里就可以倍增解决了（因为只要看跳n-1次之后到哪个节点），然而这个log并不是必要的。考虑出边都是向右连的（无出边视为出边为m+1），且每个点都有一个出边，这说明什么？这说明出边构成了一棵内向树。考虑把出边反向变成外向树，则我们需要求的跳n-1次的含义就是其n-1级祖先。

考虑dfs的过程，实际上这个过程中程序内部开了一个栈来递归，这个栈在任意时刻存的都是根到当前节点的路径。这样思路就很明显了：每个节点进栈的时候顺便把当前深度的节点（nd数组）记为自己，那x的n-1级祖先就是nd[dep[x]-(n-1)]了，只要一遍dfs就可以全部求出。

实际上代码极短

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N=2e5+2;
int p[N],a[N],lst[N],inxt[N],pre[N],c[N],dep[N],nd[N],r[N],lj[N],nxt[N],fir[N];
int n,m,q,i,j,cc,bs;
inline void add(int x,int y)
{
	lj[++bs]=y;
	nxt[bs]=fir[x];
	fir[x]=bs;
}
inline void read(int &x)
{
	cc=getchar();
	while ((cc<48)||(cc>57)) cc=getchar();
	x=cc^48;cc=getchar();
	while ((cc>=48)&&(cc<=57))
	{
		x=x*10+(cc^48);
		cc=getchar();
	}
}
void dfs(int x)
{
	int i;nd[dep[x]]=x;if (dep[x]>=n) r[x]=nd[dep[x]-(n-1)]; else r[x]=m+1;
	for (i=fir[x];i;i=nxt[i])
	{
		dep[lj[i]]=dep[x]+1;
		dfs(lj[i]);
	}
}
int main()
{
	read(n);read(m);read(q);
	for (i=1;i<=n;i++) {read(p[i]);inxt[p[i]]=p[i-1];}
	inxt[p[1]]=p[n];
	for (i=1;i<=m;i++)
	{
		read(a[i]);pre[i]=lst[a[i]];lst[a[i]]=i;
		for (j=lst[inxt[a[i]]];(j)&&(c[j]==0);j=pre[j]) c[j]=i;
	}for (i=1;i<=m;i++) if (!c[i]) c[i]=m+1;
	for (i=1;i<=m;i++) add(c[i],i);dfs(m+1);
	for (i=m-1;i;i--) r[i]=min(r[i+1],r[i]);
	while (q--)
	{
		read(i);read(j);
		putchar(48+(r[i]<=j));
	}
}
```


---

## 作者：伟大的王夫子 (赞：8)

这题的思路实在是太过巧妙了，简直让我无法想象。刚好感觉讨论区有些题解可能讲的不是很清楚或者代码有点乱或者排版不好，那么就让我来补充一下。

我们先把问题转化成求 $x$ 走了 $n - 1$ 步后到达的点，然后取一个后缀最小值。

首先，我们先用 $b_x$ 记下 $x$ 在 $p$ 中出现的位置，并且将 $b_{a_i}$ 赋值给 $a_i$，那样就相当于是在 $a$ 中寻找 $(1, 2, \cdots, n)$ 的循环子序列。此时，1 的后继是 2，2 的后继是 3，$n$ 的后继是 1。容易发现，只有离一个数最近的一个后继才是有用的。我们可以倒序枚举 $i \in [1, m]$，一个一个去计算，把结果记在数组 $c$ 中。

然后我们将 $c_i$ 与 $i$ 连边，形成一个 $m+1$ 个点的树。其中 $c_m = m + 1$。我们采用回溯搜索的方式遍历这棵树，搜到一个点后现将其进栈，然后搜完了再弹出。那么栈中存储的便是 $m+1$ 到 $x$ 路径上的所有点。这样就能方便找出 $x$ 走了 $n - 1$ 步后到哪个点了。

代码方面，由于参考了第一篇题解，所以可能会有点相似。不过为了方便阅读，换成了可爱的 LaTeX 码风，希望大家喜欢。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, T, a[200005], b[200005], g[200005], ansR[200005], c[200005];
int tot, vc[200005], Ne[200005], he[200005], stk[200005], p, dep[200005];
inline void add(int x, int y) {
	vc[++tot] = y, Ne[tot] = he[x], he[x] = tot;
}
void dfs(int x) {
	stk[++p] = x;
	if (dep[x] > n - 1) ansR[x] = stk[p - (n - 1)];
	else ansR[x] = m + 1;
	for (int i = he[x]; i; i = Ne[i]) {
		int y = vc[i];
		dep[y] = dep[x] + 1;
		dfs(y);
	}
	--p;
}
int main() {
	scanf("%d%d%d", &n, &m, &T);
	for (int i = 1, x; i <= n; ++i) scanf("%d", &x), b[x] = i;
	for (int i = 1; i <= m; ++i) scanf("%d", a + i), a[i] = b[a[i]];
	for (int i = 1; i <= n; ++i) b[i] = m + 1;
	for (int i = m; i; --i) {
		int y = a[i] == n ? 1 : a[i] + 1;
		c[i] = b[y];
		b[a[i]] = min(b[a[i]], i);
	}
	for (int i = 1; i <= m; ++i) add(c[i], i);
	dep[m + 1] = 1;
	dfs(m + 1);
	ansR[m + 1] = m + 1;
	for (int i = m; i; --i) ansR[i] = min(ansR[i], ansR[i + 1]);
	for (int i = 1, l, r; i <= T; ++i) {
		scanf("%d%d", &l, &r);
		putchar('0' + (ansR[l] <= r));
	}
}
```

时间复杂度为 $O(n)$。应该说是比较套路的一道题，做多了就熟悉了。

---

## 作者：Mosklia (赞：8)

[~~点击这里食用效果更佳哦~~](https://www.sparky-14145.com/2019/04/01/%E9%A2%98%E8%A7%A3_CF_1142B%E3%80%90Lynyrd_Skynyrd%E3%80%91/)  

# 1 思路解析

这题……乍一看好像没办法一眼秒掉……  
考虑把它拆分成多个$\mathrm{subtask}$来解决~~假装自己在打$\mathrm{NOIp}$水部分分~~。  

## 1.1 $\mathrm{subtask \; 1}$：只有一个询问，且询问$p$（不是循环移位）是否为$a$的子序列

这个应该简单……设$s_i$满足$p_{s_i} = i$，即$i$在$p$中的位置。用$s_i$替换$a_i$（执行赋值操作：`a[i] = s[a[i]]`），再想办法验证现在的$a$是否有一个子序列$1, 2, 3,\ldots,n$即可。

## 1.2 $\mathrm{subtask \; 2}$：只有一个题目中给定的询问

循环移位还是比较麻烦的。首先不难想到如果匹配的子序列的第$i$位（下文称为“前驱”）已经确定，那么第$i+1$位（下文称为“后继”）肯定越靠前越好。这样，每个位置的后继位置是唯一确定的，于是问题转化为是否存在一个$i(a_i = p_1, i \in [l, r])$，使得它的第$i-1$个后继也在给定的区间中。如果从前驱像后继连一条有向边，那么我们会得到一幅有向无环图，且每个点的出度至多为$1$。联系《开车旅行》，我们发现在这种图上“某个点的第$k$个后继”可以用倍增法求得，于是本$\mathrm{subtask}$得解。  

## 1.3 $\mathrm{subtask \; 3}$：多组询问，询问要求子序列严格与$p$相同（而不是$p$的循环移位）

上一个$\mathrm{subtas}$启发我们：是否可以把问题转化成求有向无环图上点的后继。答案很显然：可以。  
仿照刚刚的思路，前驱和后继连好点，每个左端点记录一下自己右边（包括自己）最接近自己的$p_1$的位置，倍增求出它的第$n-1$个后继的位置，判断其是否位于询问区间内即可。

## 1.4 $\mathrm{subtask \; 4}$：多组询问，且询问循环移位

考虑继续“改造”上一个$\mathrm{subtask}$。“循环移位”看上去很麻烦，其实反倒放宽了限制：给定区间内任何一个位置都有可能是子序列的起点。只要有任何一个位置的第$n-1$个后继再询问区间内，那么这次询问的答案就是`1`。  
预处理出每个位置的第$n-1$个后继，将它们的位置存进$\mathrm{ST}$表。每次询问查询给定区间所有满足要求的子序列终点最靠前的那一个的终点位置，如果它再给定区间内，则输出`1`；否则输出`0`。  

这样我们就嘴巴了本题。

# 2 代码实现

由于图的特殊性质，我们不需要邻接表或者邻接矩阵，一个数组即可。  
还有需要注意的就是特判$m < n$无解（全部询问输出`0`）。详细内容参见代码。  

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn = 200005, maxv = 200002;
//maxv是一个特殊的点，用来表示某个点的某个后继不在a中

int n, m, q;
int a[maxn], next[25][maxn], p[maxn << 1], s[maxn], pos[maxn]; //next存图，pos辅助建图
int st[25][maxn], lg[maxn]; //ST表辅助数组

int query(int p) { //处理每一个位置
    for (int i = 21; i >= 0; --i)
        if ((m - 1) & 1 << i)
            p = next[i][p];
    return p;
}

int main() {
    std::cin >> m >> n >> q; //此处适应个人习惯，m和n村的东西相反
    if (m > n) { //特判
        while (q--) std::cout << '0';
        std::cout << std::endl;
        return 0;
    }
    for (int i = 1; i <= m; ++i)
        std::cin >> p[i],
        p[i + m] = p[i], //倍长p是为了建图方便
        s[p[i]] = i;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    for (int i = 1; i <= maxv; ++i)
        pos[i] = next[0][i] = maxv; //初始化
    for (int i = n; i >= 1; --i)
        pos[a[i]] = i, //pos[i]表示最近的i的位置
        next[0][i] = pos[p[s[a[i]] + 1]];
    for (int i = 1; 1 << i <= n; ++i)
    for (int j = 1; j <= maxv; ++j)
        next[i][j] = next[i-1][next[i-1][j]];
    //预处理ST表的lg数组
    for (int i = 1; 1 << i <= n; ++i)
        lg[1 << i] = i;
    for (int i = 1; i <= n; ++i)
        if (!lg[i]) lg[i] = lg[i - 1];
    for (int i = 1; i <= n; ++i)
        st[0][i] = query(i);
    //预处理ST表
    for (int i = 1; 1 << i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
        int len = 1 << (i - 1);
        if (len + j - 1 > n)
            break;
        st[i][j] = std::min(st[i - 1][j], st[i - 1][j + len]);
    }
    // 输出答案
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        int temp = lg[r - l + 1], len = 1 << temp;
        temp = std::min(st[temp][l], st[temp][r - len + 1]);
        std::cout << (temp <= r ? '1' : '0');
    }
    std::cout << std::endl;
    return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：5)

### 思路

把 $a$ 中的 $p_i$ 变成 $i$。例如，$p=(2,1,3)$，就把 $a$ 中的所有 $2$ 变成 $1$，所有 $1$ 变成 $2$，所有 $3$ 变成 $3$。

这样这个排列就变成了 $(1,2,\cdots,n)$，后面好处理。

从右往左跑一遍，得到：以 $i$ 为起点，要得到 $a_i,a_i+1,\cdots,n$ 这个序列，右端点（就是那个 $n$ 的下标）最左是啥子。我的代码把当前结果记录在 `c` 数组，答案永久记录在 `d` 数组中。

从左往右跑一遍，得到：以 $i$ 为终点，要得到 $1,2,\cdots,a_i$ 这个序列，左起点（就是那个 $1$ 的下标）最右时啥子，跟上面那个算法一样。当前结果记录在 `c` 数组。

如果能快速把上面两个东西拼起来，就能得到以 $i$ 为右端点，要得到 $a_i+1,a_i+2,\cdots,n,1,2,\cdots,a_i$ 这个序列，左端点（就是那个 $a_i+1$ 的下标）最右是啥子，记录在 $e$ 数组。最后取前缀最小值，比较询问中的 $l$ 与 $e[r]$ 就能知道是否可行。

从左往右做的时候，需要迅速找到最大的 $j$，满足 $a_j==a_i-1$ 且 $d[j]<c[i]$，这个 $j$ 就是答案。我们开 $n$ 个单调队列，每个队列中 $j$ 与 $d[j]$ 都递增（这个要求维护队尾）。由于我们查询的 $c[i]$ 单调不减，我们只保留满足 $d[j]<c[i]$ 的最大（也就是最后一个）的 $j$（这个性质维护队首）。查询直接拿队首。别忘了做的时候把前面的 `d` 捡起来塞到队列里面。

复杂度 $O(n)$，为了卡常用链表手写了双端队列，目前最优解。这个方法是自己 yy 出来的。~~捣鼓了一天。~~

### code

代码中 `b` 是 $a$，`a` 是 $p$。

```cpp
#include<stdio.h>
#define N 200001
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
struct list{int maxn,maxi,l,r;}g[N];int sz;
struct deque//手写链表deque
{
	int l,r,cnt;
	inline void pop_back(){r=g[r].l;--cnt;}
	inline void pop_front(){l=g[l].r;--cnt;}
	inline void push_back(const int&x,const int&y)
	{
		++cnt;
		g[sz].maxn=x;g[sz].maxi=y;
		if(cnt==1)l=r=sz++;
		else g[r].r=sz,g[sz].l=r,r=sz++;
	}
}f[N];
int n,m,q,a[N],b[N],c[N],d[N],e[N],nowans=-1;
inline void u(const int&i,const int&j,const int&k)
//k~j    i~n-1
{//入队
	if(f[i].cnt&&k<=g[f[i].r].maxn)return;//他不如已经在队中的，不入队
	for(;f[i].cnt&&g[f[i].r].maxi>=j;f[i].pop_back());//已经在队中的不如他，出队
	f[i].push_back(k,j);
}
inline void p(const int&i,const int&j)
{
	if(!f[i].cnt)return;
	if(g[f[i].l].maxi>j)return;//没有
	for(;f[i].cnt>1;)
	{
		if(g[g[f[i].l].r].maxi>j)break;
		f[i].pop_front();//出队
	}
	if(g[f[i].l].maxn>nowans)nowans=g[f[i].l].maxn;//更新答案
}
main()
{
	read(n);read(m);read(q);
	for(int i=0,x;i<n;read(x),a[x]=i++);
	for(int i=0;i<m;read(b[i]),b[i]=a[b[i]],++i);
	for(int i=0;i<n;c[i++]=m);
	for(int i=m-1;i>=0;--i)//从右往左做
		if(b[i]==n-1)d[i]=c[n-1]=i;
		else d[i]=c[b[i]]=c[b[i]+1];
	for(int i=0;i<n;c[i++]=-1);
	for(int i=0;i<m;++i)//从左往右做
	{
		u(b[i],d[i],i);//捡起d
		if(!b[i])c[0]=i;
		else c[b[i]]=c[b[i]-1];
		if(~c[b[i]])
			if(b[i]<n-1)p(b[i]+1,c[b[i]]);
			else if(nowans<c[n-1])nowans=c[n-1];//此处特判序列1,2,...,n，这个不是两段拼起来的
		e[i]=nowans;
	}
	for(int i=0,u,v;i<q;++i)
	{
		read(u);read(v);--u;--v;
		putchar('0'+(e[v]>=u));
	}
}
```

---

## 作者：SunnyYuan (赞：3)

洛谷的题解太抽象啦，蒟蒻看不懂，在线膜拜大神。

我来讲一讲我的做法，时间复杂度 $O(n \log n)$。
~~适宜阅读~~

2024/7/26 upd：都快写成流水账了。

---

首先，我们定义 $p$ 数组中一个数字 $p_i$ 的下一个数字为：

对于 $1 \le i \le n - 1$，$p_i$ 的下一位为 $p_{i + 1}$。

对于 $i = n$，$p_i$ 的下一位为 $p_1$。

我们将这个数字记为 $f(p_i)$。

比如 $[1, 3, 4, 5, 2]$，

$1$ 的下一位就是 $3$，$f(1) = 3$；

$3$ 的下一位就是 $4$，$f(3) = 4$；

$4$ 的下一位就是 $5$，$f(4) = 5$；

$5$ 的下一位就是 $2$，$f(5) = 2$

$2$ 的下一位就是 $1$，$f(2) = 1$。（注意这里）

---

然后我们回到 $a$ 数组。

对于每个数字 $a_i$，我们将 $i$ 和在 $i$ 右边第一个 $f(a_i)$ 所在位置相连。

比如 $p = [3, 1, 2], a = [3, 2, 1, 3, 1, 2]$。

首先 $f(3) = 1, f(1) = 2, f(2) = 3$。

然后我们开始连边。

我们开始枚举 $a$ 数组。

$a_1 = 3$，查询得 $f(3) = 1$，找到 $3$ 右边第一个 $1$，发现在位置 $3$，我们将点 $1$ 和点 $3$ 连接。

$a_2 = 2$，查询得 $f(2) = 3$，找到 $2$ 右边第一个 $3$，发现在位置 $4$，我们将点 $2$ 和点 $4$ 连接。

$a_3 = 1$，查询得 $f(1) = 2$，找到 $1$ 右边第一个 $2$，发现在位置 $6$，我们将点 $3$ 和点 $6$ 连接。

$a_4 = 3$，查询得 $f(3) = 1$，找到 $3$ 右边第一个 $1$，发现在位置 $5$，我们将点 $4$ 和点 $5$ 连接。

$a_5 = 1$，查询得 $f(1) = 2$，找到 $1$ 右边第一个 $2$，发现在位置 $6$，我们将点 $5$ 和点 $6$ 连接。

对于找不到下一个数字在哪里的直接连到 $m + 1$ 上面去。

$a_6 = 2$，查询得 $f(2) = 3$，发现 $6$ 号位后没有数字 $2$，我们就将点 $6$ 和点 $m + 1 = 7$ 相连。

---

然后，我们可以发现，如果从一个点沿着刚刚连的边跳 $n - 1$ 次还没跳到 $m + 1$，说明从它开始跳 $n - 1$ 步所经过的所有点就可以构成一个序列，而不会跑到外面去。

比如从第 $1$ 个点，我们接下来跳 $n - 1 = 2$ 步：从位置 $1$ 跳到位置 $3$，从位置 $3$ 跳到位置 $6$，发现 $6 < m + 1 = 7$，这说明什么？这说明一定跳出了一个序列！这个序列就是 $3, 1, 2$，分别在位置（索引）$1, 3, 6$。

再比如从第 $2$ 个点跳 $n - 1 = 2$ 步：从位置 $2$ 跳到位置 $4$，从位置 $4$ 跳到位置 $5$，发现 $5 < m + 1 = 7$，这说明可以构成一个题目要求的序列，即 $2, 3, 1$，分别在位置（索引）$2, 4, 5$。

但是，每个点都跳 $n - 1$ 步实在是太慢啦！我们套路地选择倍增，参考倍增求 LCA 的做法即可，这里不多说了。

---

然后我们就得出了每个点 $i$ 跳 $n - 1$ 步到达点，我们将它记为 $g(i)$。

对于每个询问 $l, r$，我们可以枚举从 $l, r$ 的每一个点 $i$，即 $l \le i \le r$，如果 $g(i) \le r$，就说明从点 $i$ 开始跳，跳 $n - 1$ 步不会超过 $r$，那么整个序列也就在 $l$ 到 $r$ 这段之间。

对于每个询问，每次枚举 $l, r$，时间爆炸！$O(nq)$ 的时间复杂度直接让我们之前全白干了。

所以我们又套路地选择 RMQ（ST 表） 来求解，ST 表的基础用法在这里不再赘述。

用 ST 表求出从 $l$ 到 $r$ 间最小的 $g(i)$，如果它的最小值比 $r$ 小，说明一定存在序列在 $l$ 到 $r$ 间。

---

时间复杂度：

倍增：$O(n \log n)$，ST 表初始化：$O(n \log n)$，询问：$O(q)$

总时间复杂度：$O(n \log n)$。

### 代码

注意：第 40 个点 $m < n$ 坑人，注意初始化时选择 $n$ 还是选择 $m$。

```cpp
// Problem: Lynyrd Skynyrd
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1142B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

const int N = 200010;	// N 个点

int n, m, q;			// n, m, q
int a[N], b[N];			// a 数组， b 数组
int lst[N], nxt[N];		// lst 记录一个数字最近的位置。 nxt 记录 a 数组中下一个数字，相当于 f(n)。
int fa[25][N];			// 树上倍增
int jump[N];			// jump[i] 记录从点 i 跳 n - 1 步到达的点

int jump_n_steps(int u, int step) {	// 求点 i 跳 n - 1 步到达的点
	for (int i = 24; i >= 0; i--) {	// 套路，不多说了
		if (step >> i & 1) {
			u = fa[i][u];
		}
	}
	return u;
}

int st[25][N];						// 存储 ST 表

void getst() {						// 初始化 ST 表，不多说
	for (int j = 1; (1 << j) <= m; j++) {
		for (int i = 1; i + (1 << j) - 1 <= m; i++) {
			st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
		}
	}
}

int query(int l, int r) {			// ST 表操作：询问 l, r 的最小的 g(i)，不多说
	int len = r - l + 1;
	if (len <= 0) return 0x3f3f3f3f;
	int lg = __lg(len);
	return min(st[lg][l], st[lg][r - (1 << lg) + 1]);
}

int main() {
	ios::sync_with_stdio(false);	// 优化输入
	cin.tie(nullptr);				// 优化输入
	
	cin >> n >> m >> q;				// 输入
	for (int i = 1; i <= n; i++) {	// 输入
		cin >> a[i];
		if (i > 1) nxt[a[i - 1]] = a[i];	// 对于 1 ~ n - 1, p[i] 的下一个数字为 p[i + 1]
	}
	nxt[a[n]] = a[1];						// 对于点 n, p[n] 的下一个数字为 p[1] 
	for (int i = 1; i <= m + 1; i++) fa[0][i] = m + 1;// 初始化第一个点跳出的位置为 m + 1
	for (int i = 1; i <= n; i++) lst[i] = m + 1;	// 第 40 个测试数据坑人，这里初始化用 n
	for (int i = 1; i <= m; i++) cin >> b[i];		// 输入
	for (int i = m; i >= 1; i--) {			// 连边
		fa[0][i] = lst[nxt[b[i]]];
		lst[b[i]] = i;
	}
	
	for (int j = 1; j < 25; j++) {
		for (int i = m + 1; i >= 1; i--) {
			fa[j][i] = fa[j - 1][fa[j - 1][i]];		// 树上倍增，不多说
		}
	}
	
	for (int i = 1; i <= m; i++) jump[i] = jump_n_steps(i, n - 1); // 跳 n - 1 步
	for (int i = 1; i <= m; i++) st[0][i] = jump[i];				// 记录 g(i)
	getst();							// 初始化 ST 表
	
	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << (query(l, r) <= r); 	// 询问
	}
	return 0;
}
```

---

## 作者：hsfzLZH1 (赞：3)

## 题目大意

给定一个 $1\sim n$ 的排列 $p$ ，和一个长度为 $m$ 的数组 $a$ ，数组中的每个元素都为 $1\sim n$ 中的数。 $q$ 次询问，每次询问给出一个区间 $[l,r]$ ，问 $a_{[l,r]}$ 中是否包含一个 **子序列** ，使得其为排列 $p$ 的环形移位。如果是，输出字符 `1` ，否则输出字符 `0` 。

对于任意的 $1\le k\le n$ ， $p_{k+1},p_{k+2},...p_{n},p_1,p_2,...,p_k$ 即称为排列 $p$ 的环形移位。

$1\le n,m\le 2\times 10^5,1\le l\le r\le m$

## 解题思路

观察到无论排列 $p$ 怎么环形移位，在符合条件的子序列中，一个数前面要么没有值（即该数是第一个数），要么是排列 $p$ 环形移位中的前一个数字，即其在排列中的前一个数字是固定的。

**贪心性质** ：若满足条件的数前面有数字，值等于排列 $p$ 中该数前的一个，而且当那个数时满足条件的最后的数字时最优，不满足条件时一定没有其他的以该点结尾的子序列。

所以，我们姑且定义一个最优解，只需预处理出在最优解中一个点前面的点（由以上的贪心性质，这样的点只有一个，预处理的时间复杂度为 $O(n)$ ），然后将所有 $[l,r]$ 中的点都向前跳 $n-1$ 次，如果这些点全部存在，且最后跳到的点的位置 $\ge l$ ，那么就可以判断存在这样的子序列。

我们可以将一个点前面的最优点类似地必做父亲，那么我们可以用倍增法预处理出每个结点跳到的位置，用数据结构维护无修改区间最小值即可。

时间复杂度 $O(n\log_2 n)$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=400010;
int n,m,q,p[maxn],lstcol[maxn],a[maxn],lstd[maxn],lg[maxn],f[maxn][20],st[maxn][20],l,r;
int rmq(int l,int r)
{
    int k=lg[r-l+1];
    return max(st[l][k],st[r-(1<<k)+1][k]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)scanf("%d",p+i);
    p[0]=p[n];
    for(int i=1;i<=n;i++)lstcol[p[i]]=p[i-1];
    for(int i=1;i<=m;i++)scanf("%d",a+i);
    for(int i=1;i<=m;i++)
    {
        f[i][0]=lstd[lstcol[a[i]]];
        lstd[a[i]]=i;
    }
    for(int i=2;i<=max(n,m);i++)lg[i]=lg[i/2]+1;
    for(int i=1;i<=lg[n];i++)for(int j=1;j<=m;j++)f[j][i]=f[f[j][i-1]][i-1];
    for(int i=1;i<=m;i++)
    {
        st[i][0]=i;
        for(int j=0;j<=lg[n-1];j++)if((n-1)&(1<<j))st[i][0]=f[st[i][0]][j];
    }
    for(int i=1;i<=lg[m];i++)for(int j=1;j+(1<<i)-1<=m;j++)
    st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
    while(q--)
    {
        scanf("%d%d",&l,&r);
        if(rmq(l,r)>=l)printf("1");
        else printf("0");
    }
    printf("\n");
    return 0;
}
```

---

## 作者：foryou_ (赞：1)

对于 $[l,r]$ 中的每个数 $i$，我们都尝试将其作为 $p$ 的循环移位的终点，

从 $i$ 不断往前跳 $n-1$ 次，记录它在 $a_i$ 能跳到的点 $b_i$，

把 $b_i$ 扔进 ST 表中，对于每组询问 $[l,r]$ 取 $\max$，

若这个值 $\ge l$，则说明存在，否则不存在。

具体实现细节见 [code](https://www.luogu.com.cn/paste/e50ug095)。

---

## 作者：xiaohuang (赞：1)

[更好的阅读体验](https://xiaohuang888.github.io/2019/09/03/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces1142B%20Lynyrd%20Skynyrd/)

### Solution

我们可以先预处理出$a_i$在$p$序列中的前一个数为$\mathrm{last}_i$。如果它能构成一个合法的循环序列，就代表它能够向前位移$n - 1$次$\mathrm{last}$。所以我们可以用倍增来解决。我们取一个最大的合法循环序列的头表示为$\mathrm{b}_i$，那么最后的条件就是：

$$\max ^ {r} _ {i = l}{\mathrm{b}_i} \ge l$$

满足就输出$1$，否则输出$0$。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN = 1000005, MAXM = 30;
int n, m, q, l, r, a[MAXN], b[MAXN], p[MAXN], last[MAXN], pos[MAXN], st[MAXN][MAXM];
inline int calc_step(int x) {
    int s = 0;
    for (int i = 25; i >= 0; i--)
        if (s + (1 << i) < n) {
            x = st[x][i];
            s += 1 << i;
        }
    return x;
}
inline int query(int l, int r) {
    int x = (int)log2(r - l + 1);
    return max(st[l][x], st[r - (1 << x) + 1][x]);//询问ST表
}
int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        pos[p[i]] = i;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
        if (pos[a[i]] == 1) st[i][0] = last[p[n]]; else st[i][0] = last[p[pos[a[i]] - 1]];
        last[a[i]] = i;
    }
    for (int j = 1; j <= 25; j++)
        for (int i = 1; i <= m; i++)
            st[i][j] = st[st[i][j - 1]][j - 1];
    for (int i = 1; i <= m; i++)
        b[i] = calc_step(i);
    memset(st, 0, sizeof(st));
    for (int i = 1; i <= m; i++)
        st[i][0] = b[i];
    for (int j = 1; j <= (int)log2(m); j++)
        for (int i = 1; i <= m - (1 << j) + 1; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);//ST表
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &l, &r);
        if (query(l, r) >= l) printf("1"); else printf("0");
    }
    return 0;
}
```

---

## 作者：内拉组里 (赞：0)

# Statement :

> 给定 $ [1,n] $ 的排列 $ p $，以及有 $ m $ 个数字的数组 $ a $，
>
> $ q $ 次询问，查询 $ a $ 数组的 $ [l,r] $ 中是否存在子序列为 $ p $ 的循环排列。

# Thoughts :

对于排列 $ p $，显而易见的是一个单射 $ \varphi : [1,n] \rightarrow [1,n] $。

而对于数组 $ a $ 中的数字而言，只需要找到自身以及子序列中下一个数字在 $ p $ 中的位置。

考虑开桶记录 $ [1,n] $ 在 $ p $ 中出现的位置，而 $ a $ 数组只需记录每一个 $ a_i $ 在 $ p $ 中的位置。

然后倒序遍历 $ a $ 数组即可得到每一个 $ a_i $ 在子序列中下一个数字的最近位置，记为 $ nxt[i] $。

接下来有两种做法：数据结构 & 图论。

先说数据结构，用倍增把 $ nxt $ 数组预处理一下得到以每一个数为起点的长度为 $ n $ 的子序列，

总时间复杂度 $ \Theta (M \log{M} + Q) $。

***

图论方法，考虑倒序建图，连接每一条 $ nxt[i] \rightarrow i $，

由于映射 $ i \rightarrow nxt[i] $ 为单射，故所有节点都只有一个父节点，

于是形成了一棵以 $ \infin $ 为根的树，方便起见，将 $ \infin $ 记为 $ m + 1 $，避免空间浪费。

从根节点开始 dfs，手写栈维护根节点到当前节点的路径，

当 dfs 到当前节点时，若栈中元素个数 $ \ge n $，那么说明能够形成完整的子序列，

即依次从栈中取出的 $ n $ 个数字，并且以最后一个取出的数字为终点，记为 $ ans[u] $。

然后向下继续遍历即可，最后记得回溯。

# Analyses :

> 总时间复杂度 $ \Theta (M + Q) $ 
>
> 总空间复杂度 $ \Theta (M) $ 

# Code :

```cpp
/* reference : @SYZOJ.donny */
/* reference : @Luogu.162196 */
#include	<iostream>
#include	<vector>
using namespace std;
constexpr int maxn = 2e5+4;

int a[maxn];
int rt[maxn];
int ans[maxn];
int buc[maxn];
int nxt[maxn];
int n, m, q, tp;
vector<int> G[maxn];

void dfs (int u)
{
	rt[++tp] = u;
	if (tp >= n) ans[u] = rt[tp - n + 1];
	else ans[u] = m + 1;
	for (auto v : G[u]) dfs (v);
	tp--;
}

signed main (void)
{
	cin >> n >> m >> q;
	for (int x, i = 1; i <= n; i++)
	{
		cin >> x;
		buc[x] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> a[i];
		a[i] = buc[a[i]];
	}
	for (int i = 1; i <= n; i++) buc[i] = m + 1;			/* clear */
	for (int i = m; i; i--)
	{
		nxt[i] = buc[(a[i] % n + 1)];
		buc[a[i]] = i;
	}
	for (int i = 1; i <= m; i++) G[nxt[i]].push_back(i);	/* reverse edging */
	dfs (m + 1);
	ans[m + 1] = m + 1;
	for (int i = m; i; i--) ans[i] = min (ans[i], ans[i + 1]);
	while (q--)
	{
		int l, r;
		cin >> l >> r;
		if (ans[l] > r) cout << 0;
		else cout << 1;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

循环移位后的 $p$ 与要求的子序列等价，不仅相互之间有映射关系，更能反映出他们之间的前后继关系。实际上，我们只需要确定一个子序列的开头和结尾就可以刻画这个子序列。

我们希望在询问的区间中包含这样一个符合条件的子序列，那么对于一个满足 $p$ 所描述的前后继关系的子序列，我们要尽可能的使子序列的右端点靠左。

设 $r(l)$ 为以 $a_l$ 为开头的所有合法子序列的最左末尾。这个定义等价于子序列的末尾。朴素的求法是贪心的选取最近的且满足对应到 $p$ 的后继关系的元素。

如何加速这一过程？我们发现若区间 $[u,r(u)]$ 存在一个合法的子序列，那么任意一个 $1 \le x \le u$ 也应该存在应该子序列。那么对于每个位置，都固定这个位置为 $r(u)$，从右往左扫描，这里用 $\text{DFS}$ 实现，复杂度并没有变化。然而非前继是不可能刻画的，把满足关系的建树，这样就做到了 $O(n)$。

最后，对于一个询问 $[ql,qr]$，如果满足 $ql \le l \le r(l) \le qr$ 则存在，否则不存在。显然 $x \le r(x)$，那么当 $u$ 满足 $x \le u $ 时 $r(x) \le r(u)$，维护 $\min_{l \le x \le m} r(x)$ 即可。

~~这题难在转化题意吧。~~

---

## 作者：Piwry (赞：0)

正解有点出乎我的预料...

## 解析

对于题目给出的排列 $p$，我们其实可以认为它给出了每个**数字的前后关系**

例如 `2 1 3` 就意味着 `2` 的前驱是 `3`、后继是 `1`

&nbsp;

设函数 $check(l, r, x)$。若 $[l, r]$ 有一个子序列 $s$，满足 $s$ 是 $p$ 的一个循环移位，且 $s$ 的开头为 $x$ 时，$check(l, r, x)$ 的值为 $1$；否则其值为 $0$

再设 $f(x)$，其值为最小的 $r$ 满足 $check(x, r, a_x)=1$；若这个 $r$ 不存在，那么我们就规定 $f(x) =\inf$（可以理解为先选择 $a_x$，再往后按 $p$ 给出的前后关系一个个选元素，直到得到 $p$ 的一个循环移位）

假设我们在可接受的复杂度内求出了 $f(x), x\in [1, m]$，考虑接下来怎么回答每个询问

对于询问 $[l, r]$，若至少有一个 $x\in [l, r]$ 满足 $f(x)\leq r$，显然 $[l, r]$ 的答案就为 `1`。我们可以直接维护 $\min\limits_{l\leq i\leq r}\{f(i)\}$

接着又发现 $f(x)$ 还满足 $f(x)\geq x$，因此可以直接维护一个后缀 $\min\limits_{l\leq i\leq m}\{f(i)\}$。这些处理都可以在 $O(n)$ 的复杂度内完成

&nbsp;

最后我们考虑怎么预处理 $f$

对于 $f(x)$，我们考虑找到其值对应的子序列，则 $f(x)$ 就为该子序列最后一个元素的下标

因此可以想到要使子序列最后一个元素的下标尽可能小。首先子序列第一个元素必须要是 $a_x$；每次我们按 $p$ 给出的前后关系，为已选择的最后一个元素选择下一个元素时，总是选离最后一个元素**最近的**满足前后关系的元素（可参考代码）。可以证明这个贪心是对的

对于所有 $f$ 的计算，我们发现每个元素会被选择很多次，而下一次的选择**仅取决于上一个选择的元素**，因此可以考虑将一个元素所有被选择到的询问一次性处理掉。具体实现可以用类似 dfs 的方式，从右往左遍历 $a$ 数组，每次找一个未遍历过的元素，从它开始 dfs，结点 $u$ 的儿子就是所有满足 “下一个最近的满足前后关系的元素为 $u$” 的结点（可能有点难描述，因为实际上类似把 $f(x)$ 的计算倒过来做，并把重复的部分合并起来，就得到了一个类似树的结构...具体还是看代码吧 \fad）

由于每个元素仅会被 dfs 一遍，这样我们就在 $O(n)$ 的复杂度内做完了这题

## CODE

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using std::min;

const int MAXN =2e5+20;

/*------------------------------Map------------------------------*/

int first[MAXN], tote;
struct edge{
	int to, net;
}e[MAXN];

inline void addedge(const int &u, const int &v){
	++tote;
	e[tote].to =v, e[tote].net =first[u];
	first[u] =tote;
}

/*------------------------------Array------------------------------*/

int n, m, q;
int p[MAXN], a[MAXN];

int p_pre[MAXN], p_net[MAXN];/*每个数字在环 ( 排列 ) 上的上一个/后一个数字*/
int ans_r[MAXN]/*最后一位的位置*/, suf_min_ans_r[MAXN];

/*------------------------------Dfs------------------------------*/

bool vis[MAXN];
int stk[MAXN];

void dfs(int i, int dep){
	if(dep >= n-1)
		ans_r[i] =stk[dep-(n-1)];
	else
		ans_r[i] =0x3f3f3f3f;/*就是指不可能*/
	
	vis[i] =1;
	stk[dep] =i;
	for(int l =first[i]; l; l =e[l].net)
		dfs(e[l].to, dep+1);
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int last_pos[MAXN];/*每个数字最后一次出现位置*/

int main(){
	n =read(), m =read(), q =read();
	for(int i =0; i < n; ++i)
		p[i] =read();
	for(int i =0; i < m; ++i)
		a[i] =read();
	
	for(int i =0; i < n; ++i){
	//	p_pre[p[i]] =p[(i-1+n)%n];
		p_net[p[i]] =p[(i+1)%n];
	}
	memset(last_pos, -1, sizeof(last_pos));
	for(int i =m-1; i >= 0; --i){
		addedge(last_pos[p_net[a[i]]], i);/*贪心选最近的*/
		last_pos[a[i]] =i;
	}
	for(int i =m-1; i >= 0; --i)
		if(!vis[i])
			dfs(i, 0);
	suf_min_ans_r[m] =0x3f3f3f3f;
	for(int i =m-1; i >= 0; --i)/*可以直接用后缀回答，不影响答案*/
		suf_min_ans_r[i] =min(ans_r[i], suf_min_ans_r[i+1]);
	while(q--){
		int l =read()-1, r =read()-1;
		putchar('0'+(suf_min_ans_r[l] <= r));
	}
}
```

---

