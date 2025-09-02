# [POI 2012] PEN-Salaries

## 题目描述

**译自 POI 2012 Stage 3. Day 1「[Salaries](https://szkopul.edu.pl/problemset/problem/_qn633f6DVAHRkv0OX3LQaph/site/?key=statement)」**

有一个 $n$ 个点的有根树，每个点的权值分别为 $1 \ldots n$，且大于其儿子的权值。其中一部分点的权值是公开的，且每个权值已知的点的父亲权值也一定已知。求能够根据已知信息推算出来的权值未知的点的权值。

## 说明/提示

对于 $54\%$ 的数据有 $n \le 10^4$.

对于所有数据有 $1 \le n \le 10^6$。

翻译来自于 [LibreOJ](https://loj.ac/p/2700)。

## 样例 #1

### 输入

```
10
2 2
2 10
1 0
2 9
2 5
4 0
6 0
6 0
5 0
5 0```

### 输出

```
2
10
1
9
5
8
0
0
0
0```

# 题解

## 作者：skylee (赞：7)

题目大意：

给定一棵n带权树，每个点的权值在[1,n]范围内且互不相等，并满足子结点的权值一定小于父结点。

现在已知一个包含根结点的联通块中个点的权值，求剩下哪些点的权值能够被求出，并求出这些权值。

思路：

贪心。

很显然，对于某一个结点x，如果当前只有一个可取的权值w，且小于其父结点的权值，那么这个结点的权值一定是w。

事实上所有未知结点权值都可以尝试用这样的方法得出，关键是如何唯一确定下这个权值w。

我们可以用一个数组max记录每个结点权值的上界，再用一个数组last记录小于某个权值能取的最大权值。

max数组可以用一趟DFS递归出来。

然后顺序枚举每一个权值，如果可用就加入到一个“黑箱”中，如果现在黑箱中只有一个权值w并且有未知权值的结点，说明这个节点的权值就是w。

然后如果现在黑箱中有多个权值，未知的结点也很多，那么这些权值就作废。

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
inline int getint() {
    char ch;
    while(!isdigit(ch=getchar()));
    int x=ch^'0';
    while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
    return x;
}
const int V=1000001;
std::vector<int> c[V];
int n;
int w[V],s[V],par[V],max[V],cnt[V],last[V],root;
int find(const int x) {
    return x==last[x]?x:last[x]=find(last[x]);
}
void dfs(const int x) {
    if(!max[x]) {
        max[x]=find(max[par[x]]-1);
        s[max[x]]=x;
        cnt[max[x]]++;
    }
    for(unsigned i=0;i<c[x].size();i++) {
        dfs(c[x][i]);
    }
}
int main() {
    n=getint();
    for(int i=1;i<=n;i++) last[i]=i;
    for(int i=1;i<=n;i++) {
        int p=getint();
        w[i]=max[i]=getint();
        if(p!=i) {
            c[p].push_back(i);
            par[i]=p;
        } else {
            root=i;
            w[i]=n;
        }
        last[w[i]]=w[i]-1;
    }
    dfs(root);
    for(int i=1,tmp=0;i<=n;i++) {
        if(last[i]==i) tmp++;
        if(cnt[i]&&tmp==1) w[s[i]]=i;
        tmp-=cnt[i];
    }
    for(int i=1;i<=n;i++) printf("%d\n",w[i]);
    return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

> **[P3542 [POI2012]PEN-Salaries](https://www.luogu.com.cn/problem/P3542)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

大大大大大大大神仙题！我初始的想法是对整棵树进行一遍 dfs，将所有儿子按照 $z$ 从小到大排序，先考虑 $z$ 非零的那些点，若已经处理过的子树大小之和 $s$ 加上当前儿子 $v$ 的子树大小等于 $z_v$，说明 $v$ 的子树内的值域唯一确定，为 $[s+1,z_v]$，对 $v$ 进行 dfs，否则直接返回。这保证被深搜到的结点的值域被唯一确定，而**儿子的值域确定建立在父亲的值域确定基础上**，因此遇到第一个不符合的子结点就要立刻返回。

很显然，这样是错的。原因是我们没有考虑到已经被钦定的 $z$ 值。例如 $z$ 值较大的结点 $v$ 有较小 $z$ 值的儿子 $w$，当我们考虑 $v$ 父亲的所有子结点时，就不会将 $z_w$ 的占位计算在内。

一个神仙想法：考虑**每个结点的最大可能 $z$ 值 $mx_i$**。记 $pre_i$ 表示 $\leq i$ 的最大的没有被钦定的 $z$ 值，这可以通过对于所有被钦定的 $z$ 值令 $pre_z=z-1$，然后 $i$ 从小到大扫一遍 $pre_i=pre_{pre_i}$ 预处理出来。那么 $mx_i$ 即：
$$
mx_i =
\begin{cases}
z_i & (z_i\neq 0) \\
pre_{mx_{fa_i} - 1} & (z_i = 0)
\end{cases}
$$
记 $sum_i$ 表示 $cnt_i$ 即 $mx$ 值等于 $i$ 的数的个数的前缀和，由于保证有解，故 $sum_i\leq i$。我们断言 $mx$ 值为 $i$ 的结点的 $z$ 值可以被钦定为 $i$ 当且仅当 $sum_i=i$ 且 $sum_{i-1}=i-1$。这是因为**若一个或多个 $mx$ 值对应多个空余的 $z$ 值，则它们全都不能被确定**，或者说 $sum_{i-1}=i-1$ 说明前 $i-1$ 个值已经被 $i-1$ 个位置内部消化，就算这 $i-1$ 个位置没有唯一确定一个 $z$ 值，后面的位置的 $z$ 值也不可能 $\leq i-1$（否则就无解了）。那么就做完了，时间复杂度线性，凭借小常数拿到了最优解（2021.12.19）。

```cpp
const int N = 1e6 + 5;
int n, root, sz[N], q[N], pre[N], mx[N], p[N], z[N];
int cnt, hd[N], nxt[N], to[N];
void add(int u, int v) {nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v;}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) pre[i] = i;
	for(int i = 1; i <= n; i++) {
		p[i] = read(), z[i] = read(), pre[z[i]] = z[i] - 1;
		p[i] == i ? (root = i, void()) : add(p[i], i);
	} z[root] = n;
	for(int i = 1; i <= n; i++) pre[i] = pre[pre[i]];
	static int qu[N], l = 1, r = 0; qu[++r] = root;
	while(l <= r) {
		int t = qu[l++];
		mx[t] = z[t] ? z[t] : pre[mx[p[t]] - 1];
		sz[mx[t]]++, q[mx[t]] = t;
		for(int i = hd[t]; i; i = nxt[i]) qu[++r] = to[i]; 
	} for(int i = 1, r = 0; i <= n; i++) {
		r += 1 - sz[i];
		if(!r && sz[i] == 1) z[q[i]] = i;
	} for(int i = 1; i <= n; i++) print(z[i]), pc('\n');
	return flush(), 0;
}
```

---

## 作者：MoyunAllgorithm (赞：1)

**题意**

一棵 $N$ 点树，每个点有点权，点权构成 $1 \sim N$ 排列。一些点的点权被隐去了，且已知点权的点构成包含根节点的连通块。父亲的点权高于儿子点权。你需要猜出尽可能多的被隐藏的点权。

**分析**

如果一个点的点权虽然被隐藏但你可以猜出来，说明满足：

- 这个点的点权不能更大；

-  这个点的点权不能更小。

这看起来是废话，因此根据题意进行转化。假如这个点的点权被确定为 $x$，则有：

- 父亲的点权被确认为 $x+1$；

- 有 $x-1$ 个点被确认点权在 $[1,x-1]$ 之间。

不妨从第一个限制入手。定义 $dp(i)$ 为 $i$ 可能的最大点权。根节点的 $dp$ 值为 $N$。

从根到叶子进行递推：

- 若节点 $u$ 的值已经被输入数据给出则直接赋值；

- 否则，$dp(u)$ 为所有 $<dp(\text{fa}(u))$ 的所有没有被输入数据指定为某点点权的正整数中最大的。

这样，第一个限制就能被表示。那如何表示第二个限制呢？将所有 $dp$ 从小到大排序。如果一个数 $x$ 是恰好一个点的 $dp$ 值，且有 $x-1$ 个 $dp$ 值是 $<x$ 的，则这个 $x$ 所对应的点的点权能被确认为  $x$。这其中蕴含了类似于前缀和差分的思想：有 $x$ 个点的 $dp$ 值 $\le x$ 且 $x-1$ 个点的 $dp$ 值 $\le x-1$ 是“$x$ 是恰好一个点的 $dp$ 值”的充要条件。

根据实现不同，时间复杂度为 $O(N)$ 或 $O(N \log N)$。都可以通过。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5; 
vector<int>gra[MAXN];
int f[MAXN],M=0;
int N,z[MAXN],rt;
int dp[MAXN],low[MAXN],siz[MAXN],cnt[MAXN],id[MAXN];
bool exi[MAXN];
void dpfs(int u,int fa)
{
	siz[u]=1;
	for(int v:gra[u])
	{
		if(v==fa) continue;
		if(z[v]) dp[v]=z[v];
		else dp[v]=low[dp[u]-1];
		dpfs(v,u);
		siz[u]+=siz[v];
	}
	return;
}
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		int x;
		scanf("%d %d",&x,&z[i]);
		if(i==x) rt=x;
		else gra[x].push_back(i);
		exi[z[i]]=1;
		low[z[i]]=z[i];
	}
	int mx=0;
	for(int i=1;i<=N;i++)
	{
		if(exi[i]) continue;
		f[++M]=i;
	}
	for(int i=1;i<=N;i++)
	{
	//	if(exi[i]) continue;
		low[i]=f[upper_bound(f+1,f+M+1,i)-f-1];
	}
	dp[rt]=N;
	dpfs(rt,0);
	for(int i=1;i<=N;i++) 
	{
		id[dp[i]]=i;
		cnt[dp[i]]++;
	}
	int S=0;
	for(int i=1;i<=N;i++)
	{
		if(S==i-1&&cnt[i]==1) z[id[i]]=i;
		S+=cnt[i];
	}
	for(int i=1;i<=N;i++) printf("%d\n",z[i]);
	return 0;
}
```

---

## 作者：void_zxh (赞：0)

对于这题，我们先将每个节点最大的可能取值求出来。


然后排序。


枚举每个值i


若i以前的值已经都被确定或模糊确定（比如说节点x y z取 2 3 4等等）


那么这个值就一定为i


这样子就可以求出全部的答案


附上代码

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <map>
using namespace std;
#define ll unsigned long long

inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
    while(c<='9'&&c>='0'){x=x*10+c-48;c=getchar();}
    return x*f;
}

struct edge
{
    int to,next;
}e[1000005];

struct node
{
    int mx,id;//最大可能取值与点的编号 
}a[1000005];

int n,cnt,root,m;
int head[1000005];
int v[1000005];
int vis[1000005];
int lit[1000005];//对于每个值最大可能取到的值 

bool cmp(node xi,node yi)
{
    return xi.mx<yi.mx; 
} 

void addedge(int x,int y)
{
     e[++cnt].to=y;e[cnt].next=head[x];head[x]=cnt;
}

void dfs(int x,int limit)
{
    int i,vi;
    if(!v[x])
        a[++m]=(node){limit,x};
    for(i=head[x];i!=-1;i=e[i].next)
    {
        vi=e[i].to;
        if(!v[vi]) dfs(vi,lit[limit-1]);
        else dfs(vi,v[vi]); 
    } 
}

int main()
{
    int i,fa,wi,j; 
    n=read();
    for(i=1;i<=n;i++)
        head[i]=-1;
    for(i=1;i<=n;i++)
    {
        fa=read(); wi=read();
        v[i]=wi;
        vis[wi]=1;
        if(fa==i)
        {
            root=i;
            if(v[i]==0)
                v[i]=n;
        }
        else
            addedge(fa,i); 
    }
    /*for(i=1;i<=n;i++)
    {
        printf("%d: ",i); 
        for(j=head[i];j!=-1;j=e[j].next)
            printf("->%d",e[j].to);
        printf("\n");
    }*/
    for(i=1;i<=n;i++)
        if(vis[i])
            lit[i]=lit[i-1];//因为i已经固定了，所以以后的点顶多取到lit[i-1] 
        else
            lit[i]=i;//若没取过，就为i 
    dfs(root,v[root]);
    sort(a+1,a+m+1,cmp);
    int hc=0,dc=0,cou;//hc：当前枚举的值i之前原本给定数有几个，
    //dc：当前枚举的值i之前具体值固定或范围固定的数有几个 
    j=1;//第几个排序后的点 
    for(i=1;i<=n;i++)
    {
        if(vis[i])
            hc++;
        else
        {
            cou=0;
            while(a[j].mx==i)
                j++,cou++;
            if(cou==1&&hc+dc==i-1)
                v[a[j-1].id]=i;
            dc+=cou; 
        }
    }
    for(i=1;i<=n;i++)
        printf("%d\n",v[i]); 
    return 0;
}
```

---

