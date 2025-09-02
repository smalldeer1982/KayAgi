# Bipartite Segments

## 题目描述

You are given an undirected graph with $ n $ vertices. There are no edge-simple cycles with the even length in it. In other words, there are no cycles of even length that pass each edge at most once. Let's enumerate vertices from $ 1 $ to $ n $ .

You have to answer $ q $ queries. Each query is described by a segment of vertices $ [l;r] $ , and you have to count the number of its subsegments $ [x;y] $ ( $ l<=x<=y<=r $ ), such that if we delete all vertices except the segment of vertices $ [x;y] $ (including $ x $ and $ y $ ) and edges between them, the resulting graph is bipartite.

## 说明/提示

The first example is shown on the picture below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901C/9b1dc17b2719bb085fa0c10624f2d9373bdbe5c5.png)

For the first query, all subsegments of $ [1;3] $ , except this segment itself, are suitable.

For the first query, all subsegments of $ [4;6] $ , except this segment itself, are suitable.

For the third query, all subsegments of $ [1;6] $ are suitable, except $ [1;3] $ , $ [1;4] $ , $ [1;5] $ , $ [1;6] $ , $ [2;6] $ , $ [3;6] $ , $ [4;6] $ .

The second example is shown on the picture below:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901C/d6699797f2ea521389d1d5d2e2e1a5397ed46123.png)

## 样例 #1

### 输入

```
6 6
1 2
2 3
3 1
4 5
5 6
6 4
3
1 3
4 6
1 6
```

### 输出

```
5
5
14
```

## 样例 #2

### 输入

```
8 9
1 2
2 3
3 1
4 5
5 6
6 7
7 8
8 4
7 2
3
1 8
1 4
3 8
```

### 输出

```
27
8
19
```

# 题解

## 作者：FjswYuzu (赞：4)

提供一个 $O(n+q \log n)$ 的做法。

感谢 [@reanap](https://www.luogu.com.cn/user/171554) 找到这道题并和我一起探讨研究（准确来说，都是她的思路）。在此膜拜。

虽然说 $2300$ 是黑题确实有点假，但是这道题确实很有意思。

以下根据我和她做这道题的思路进行解题。

---

根据题目描述分析性质。

题目描述地很清楚，这个图**没有偶环**。众所周知，二分图不能有奇环。而我们需要求一个区间 $[l,r]$ 内有多少个子区间 $[x,y](l \leq x \leq y \leq r)$，使得节点 $x,x+1,x+2,\cdots,y$ 构成的图是一个二分图。

考虑一个很简单的东西，如果区间 $[l,r]$ 内所有节点构成的一个图不能够构成一个二分图，那么区间 $[l-1,r]$ 内所有节点构成的一个图不能够构成一个二分图。

证明：区间 $[l,r]$ 内所有节点已经构成的一个图不能够构成一个二分图，新加入的节点 $l-1$ 只会对图造成更大的负担，而不会分担不能染色的节点所面临的问题。

定义 $nxt_l$ 为：$[l,nxt_l]$ 内所有节点能够构成一个二分图并且 $nxt_l$ 最大。根据我们上文的分析，对于任意一个 $i$，满足 $nxt_i \geq nxt_{i-1}$。现在的问题就是我们要如何求出 $nxt$ 数组和解决查询了。

先考虑处理这个 $nxt$ 数组。我们想找出 $nxt$ 数组，就要快速判断一个区间内是否有环。定义 $cou_i$ 为当前已经加入的点中，属于环 $i$ 的节点有多少个。因为 $nxt_i \geq nxt_{i-1}$，我们就用双指针 $l,r$ 去维护当前确定的区间，每次加入一个点 $p$ 属于环 $q$（或者不属于任何一个环，这个时候可以不用去管它），将 $cou_q$ 加上 $1$。如果 $cou_q$ 的大小已经等于环 $q$ 的大小，这个时候就不会构成二分图了，$r \gets r-1$，此时的 $nxt_l=r$。挪动指针 $l$，删除一个点同理。其实这个地方也有点像莫队（

在一个图上找环是一件非常麻烦的事情，似乎并不怎么好找。有一个非常可疑的点仿佛还没有用完——这个图**没有偶环**。图没有偶环，说明不可能有两个奇环合并在一起（因为这样会构成一个偶环）。所以对于这道题来说**没有两个环共用一条边**。诶好像有点熟悉，这难道不就是**仙人掌**吗？

---

注：其实这个是非常有用的两个性质：

- 如果图没有偶环，图一定为仙人掌（**但是仙人掌是可能有偶环的**）；   
- 如果图没有奇环，图一定为二分图（反之亦然）。

---

于是我们确定了：这个图是由树，基环树（包含了环）与仙人掌构成的一个图（~~或者说，沙漠绿洲~~）。然而这并没有什么用，因为我们只需要两个环不会共用一条边的结论就能求出这个图里面的环了（

现在我们已经求出了 $nxt$ 数组，找到最大的那个 $s$，使得 $nxt_s \leq r$。这个时候 $[s+1,r]$
 内所有的区间都是合法的，可以计算；计算 $[l,s]$ 的方案数，我们首先计算一下 $nxt$ 数组的前缀和，答案就是 $sum_s -sum_{l-1} - \frac{(s-l+1)\times (s+l-2)}{2}$。
 
另外，图中最多只有 $\lfloor \dfrac{n}{3} \rfloor$ 个奇环，可以把数组开小一点。然后为什么我在 CF 上根本没看到评测给我返回 WA 啊。
 
代码细节挺少的，适合我这种傻逼选手，除了二分锅了看了下题解（

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
vector<LL> G[300005],cir[300005];
LL n,m,q,bel[300005],dep[300005],fa[300005],sz[100005],nxt[300005],cou[100005],sum[300005],cnt;
void get(LL x,LL y)
{
	if(dep[x]<dep[y])	return ;
	++cnt;
	cir[cnt].push_back(y);
	bel[y]=cnt;
	while(x!=y)	cir[cnt].push_back(x),bel[x]=cnt,x=fa[x];
	sz[cnt]=cir[cnt].size();
}
void dfs(LL now,LL pre)
{
	fa[now]=pre;
	dep[now]=dep[pre]+1;
	for(unsigned int i=0;i<G[now].size();++i)
	{
		LL to=G[now][i];
		if(to==pre)	continue;
		if(dep[to])	get(now,to);
		else	dfs(to,now);
	}
}
void avoidWarning()
{
	while(q-->0)
	{
		LL ll,rr;
		scanf("%lld %lld",&ll,&rr);
		LL l=ll,r=rr,ans=ll;
		while(l<=r)
		{
			LL mid=(l+r)>>1;
			if(nxt[mid]<rr)	l=mid+1,ans=mid;
			else	r=mid-1;
		}
		if(nxt[ans]>rr)	--ans;
		printf("%lld\n",(rr-ans)*(rr-ans+1)/2+sum[ans]-sum[ll-1]-(ans-ll+1)*(ans+ll-2)/2);
	}
}
int main(){
	scanf("%lld %lld",&n,&m);
	for(LL i=1;i<=m;++i)
	{
		LL u,v;
		scanf("%lld %lld",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(LL i=1;i<=n;++i)	if(!dep[i])	dfs(i,0);
	LL l=1,r=0;
	while(l<=n)
	{
		while(r<n)
		{
			++r;
			LL pos=bel[r];
			++cou[pos];
			if(cou[pos]==sz[pos])
			{
				--cou[pos];
				--r;
				break;
			}
		}
		nxt[l]=r;
		LL pos=bel[l];
		--cou[pos];
		++l;
	}
	for(LL i=1;i<=n;++i)	sum[i]=sum[i-1]+nxt[i];
	scanf("%lld",&q);
	avoidWarning();
	return 0;
}
```

---

## 作者：「QQ红包」 (赞：4)

在本题中，只要没环即可。

要求符合条件的区间构成一个森林。

$f(l,r)$表示区间$(l,r)$是否构成二分图。

固定区间的$l$，可以发现，$f(l,i)$相当于序列$11110000$，考虑从右到左枚举$l$，合法的$r$是单调递减的。然后是否构成二分图我们可以用LCT动态维护，

然后统计答案的话，我们可以离线。从右到左随便维护就好。（用线段树什么的都可以）

LCT+扫描线+线段树

~~这种写法思路自然，写起来毒瘤~~。

1.5KB的写法是啥啊。

因为这题没有偶环只有奇环，那么没有环套环。

所以给的图是个**仙人掌**。

在一个点双上，每条边有一个出现时刻$\min$和一个出现时刻$\max$，跨过这个的所有区间都不合法。

然后我们可以维护$L_i$表示以$i$为右端点，做端点编号最大的不合法的区间。然后可以记下不合法的区间的个数。二分找出最靠左的，包含在区间$(l,r)$内的环的右端点，然后就可以很容易求出不合法的区间了。

缩点+二分就没了。

~~果真我数据结构学傻了。~~

```cpp
/*
 * Author: ylx
 * Lang: c++
 * Prog: p2387
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void qmax(int &x, int y)
{
    if (x < y)
        x = y;
}
void qmin(int &x, int y)
{
    if (x > y)
        x = y;
}
inline int read()
{
    char s;
    int k = 0, base = 1;
    while ((s = getchar()) != '-' && s != EOF && !(isdigit(s)))
        ;
    if (s == EOF)
        exit(0);
    if (s == '-')
        base = -1, s = getchar();
    while (isdigit(s))
        k = k * 10 + (s ^ '0'), s = getchar();
    return k * base;
}
inline void write(ll x)
{
    static char cnt, num[20];
    cnt = 0;
    if (!x)
    {
        putchar('0');
        return;
    }
    for (; x; x /= 10)
        num[++cnt] = x % 10;
    for (; cnt; putchar(num[cnt--] + 48))
        ;
}
const int maxn=3e5+10;
int n,m,q,vis[maxn],stk[maxn],top,loop[maxn];
int po[maxn],to[maxn<<1],ne[maxn<<1],id;
int L[maxn];
ll sum[maxn];
void add(int x,int y)
{
    id++;
    to[id]=y,ne[id]=po[x],po[x]=id;
}
void dfs(int x,int fa)
{
    vis[x]=1;
    stk[++top]=x;
    for (int i=po[x];i;i=ne[i])
    if (to[i]!=fa && !loop[to[i]])
    {
        if (!vis[to[i]]) dfs(to[i],x);
        else
        {
            int mx=0,mn=n+1;
            for (int j=top,y;;j--)
            {
                y=stk[j];
                qmax(mx,y);
                qmin(mn,y);
                loop[y]=1;
                if (stk[j]==to[i]) break;
            }
            if (!L[mx]) L[mx]=mn;
            else qmax(L[mx],mn);
        }
    }
    --top;
}
int main()
{
    n=read();
    m=read();
    for (int i=1,x,y;i<=m;i++)
    {
        x=read();
        y=read();
        add(x,y);
        add(y,x);
    }
    for (int i=1;i<=n;i++) 
        if (!vis[i]) 
            dfs(i,0);
    for (int i=1;i<=n;i++) 
    {
        qmax(L[i],L[i-1]);
        sum[i]=sum[i-1]+L[i];
    }
    q=read();
    int x,y,mid,l,r,s;
    ll ans;
    while (q--)
    {
        x=read(),y=read();
        l=x,r=y;
        s=y+1;
        while (l<=r)
        {
            mid=(l+r)>>1;
            if (L[mid]>=x)
                r=mid-1,s=mid;
            else l=mid+1;
        }
        ans=(ll)(y+x)*(y-x+1)/2-(sum[y]-sum[s-1])-(ll)(x-1)*(s-x);
        write(ans);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：Awdrgysxc (赞：3)

## 【Analysis】
有一个重要的结论：
#####  如果一个无向图是二分图，则图中不存在奇环
因为题目保证不会有偶环，那么只要存在环就不行，那么题目就转化成了询问区间$[L,R]$,有多少区间满足$[L`,R`]$不存在环；
不妨设$f_l$表示$r_{max}$满足$[l,r]$不存在环，那么$Ans = \sum_{i = l}^{r} min(f_{i}, r) - i +1$
也就是$Ans = \sum_{i = l}^{r}min(f_{i} + 1, r + 1) - i$
不难发现，$f$是单调不降的，那么就可以二分一下$f + 1\le r + 1$的位置,然后用前缀和  $O(1)$算一下
那么如何快速计算出$f$；先用$Tarjan$把环找出来,顺便把每个环的最小值和最大值求出来，令$H$为环，则$f_i + 1 = min(H_{jmax})$当且仅当$H_{jmin}\le i$ 可以倒叙枚举一下n，把环排个序就可以$O(N)$求出来了
总复杂度为$O(N + Q\cdot log_{2} \cdot N)$
## 【Code】
```cpp
// luogu-judger-enable-o2
#include <cstdio>
#include <set>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
 
namespace IO
{
    inline char gc()
    {
        static char s[1<<20|1]={0},*p1=s,*p2=s;
        return (p1==p2)&&(p2=(p1=s)+fread(s,1,1<<20,stdin),p1==p2)?EOF:*(p1++);
    }
//	inline char gc() { return getchar(); }
	inline long long read()
	{
		long long ret=0;bool flag=0;char c=gc();
		while ((c<'0')|(c>'9')) flag ^= !(c^'-'),c=gc();
		while ((c>='0')&(c<='9')) ret=(ret<<1)+(ret<<3)+(c^'0'),c=gc();
		return flag?-ret:ret;
 	}
 	char OutputAns[1<<20|1],*OutputCur = OutputAns;
 	inline void output()
 	{
 		OutputCur -= fwrite(OutputAns,1,OutputCur - OutputAns,stdout);
	}
	inline void print(long long ans)
	{
		char s[20]={0};
		if (OutputCur - OutputAns + sprintf(s,"%I64d",ans) >> 20) output();
		OutputCur += sprintf(OutputCur,"%I64d",ans);
	}
	inline void printc(char c)
	{
		if (OutputCur - OutputAns + 1 >> 20) output();
		*(OutputCur++) = c;
	}
}
 
using IO::read;
using IO::print;
using IO::printc;
using IO::output;
 
template <class T> inline T max (T x, T y) { return x > y ? x : y; }
 
template <class T> inline T min(T x, T y) { return x < y ? x : y; }
 
const int M = 3e5 + 11;
 
int Nxt[M<<1], To[M<<1], Fir[M], L[M], R[M], F[M];
 
long long Sum[M];
 
int n, m, q, cur, tot, cur2;
 
std::pair <int, int> H[M];
 
class Tar
{
	private: 
		int Low[M], Sta[M];
		
		int _cl;
	public:
		int Dfn[M];
		
		void Tarjan(int u, int fa)
		{
			Sta[++Sta[0]] = u, Dfn[u] = Low[u] = ++_cl;
			for (int i = Fir[u];i;i = Nxt[i])
			{
				int v = To[i];
				if (!Dfn[v]) Tarjan(v, u), Low[u] = std::min(Low[u], Low[v]);
				else if (fa != v) Low[u] = std::min(Low[u], Dfn[v]);
			}
			if (Low[u] == Dfn[u])
			{
				L[++cur] = R[cur] = u;  int tmp;
				do tmp = Sta[Sta[0]--], L[cur] = min(L[cur], tmp), R[cur] = max(R[cur], tmp); while (tmp ^ u);
			}
		}
};
 
Tar _ta;
 
inline void AddEdge(int u,int v)
{
	Nxt[++tot] = Fir[u], To[tot] = v, Fir[u] = tot;
}
 
inline void Input()
{
	n = read(), m = read();
	for (int i = 1;i <= m; ++i)
	{
		int u = read(), v = read();
		AddEdge(u, v); AddEdge(v, u);
	} q = read();
	for (int i = 1;i <= n; ++i)
		if (!_ta.Dfn[i]) _ta.Tarjan(i, -1);
}
 
inline void Solve()
{
	for (int i = 1;i <= cur; ++i)
		if (L[i] < R[i]) H[++cur2] = std::make_pair(L[i], R[i]); std::sort(H + 1, H + 1 + cur2);
	for (int i = n, j = cur2, tmp = n + 1; i; --i)
	{
		while (j && H[j].first >= i) tmp = min(tmp, H[j--].second); 
		F[i] = tmp;
	}
	for (int i = 1;i <= n; ++i) Sum[i] = Sum[i - 1] + F[i];
	while (q--)
	{
		int liml = read(), limr = read(); int pos = std::lower_bound(F + 1, F + 1 + n, limr + 1) - F;
		long long ans = 0;
		if (pos < liml) ans = (long long)(limr - liml + 1) * (limr + 1);
		else if (pos > limr) ans = Sum[limr] - Sum[liml - 1];
		else ans = (long long)Sum[pos - 1] - Sum[liml - 1] + (long long)(limr - pos + 1) * (limr + 1);
		ans -= (long long)(limr + liml) * (limr - liml + 1) >> 1;printf("%I64d\n", ans);
	}
}
 
int main(void)
{
//	freopen("count.in", "r", stdin), freopen("count.out", "w", stdout);
	Input();
	Solve();
	output();
	return 0;
}
```

---

## 作者：fush (赞：2)

给出一个线性做法。

题目保证没有偶环，说明是仙人掌。  
二分图中没有奇环，而题目保证没有偶环，所以等于判是否有环。

我们把一个环抽象为一段区间，区间范围是最小点到最大点。  
那么满足要求的点对不会包含这样的区间。  
我们对每个点求出一个 $nxt_i$，表示它最多能到达的右端点。     
答案就是：
$$
\begin{aligned}
ans &= \sum_{i=l}^r \min(nxt_i, r)-i+1\\
&=\sum_{i=l}^r \min(nxt_i, r) - \sum_{i=l}^r i - 1
\end{aligned}
$$
第二项很好求，我们考虑怎么求第一项~~直接数据结构~~。  

显然，$nxt_i$ 单调不降，那么 $\min$ 能取到后面的是一个后缀。    
我们每次询问二分，或者双指针预处理即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FL(a,b,c) for(int a=(b),a##end=(c);a<=a##end;++a)
#define FR(a,b,c) for(int a=(b),a##end=(c);a>=a##end;--a)
#define eb emplace_back
#define int long long
#define vt vector
#define max(a, b)({auto f7r=(a);auto j3h=(b);f7r<j3h?j3h:f7r;})
#define cmax(a, b)({auto j3h=(b);(j3h>a)&&(a=j3h);})
#define min(a, b)({auto f7r=(a);auto j3h=(b);f7r>j3h?j3h:f7r;})
#define cmin(a, b)({auto j3h=(b);(j3h<a)&&(a=j3h);})
constexpr int N = 3e5 + 10;
vt<int>e[N];
int sum[N], nxt[N], low[N], dfn[N], tot, stk[N], top, in[N];
void tarjan(int x, int fa){
	low[x] = dfn[x] = ++tot, in[stk[++top] = x] = 1;
	for(auto&v : e[x])if(v != fa)
		if(!dfn[v])tarjan(v, x), cmin(low[x], low[v]);
		else if(in[v])cmin(low[x], dfn[v]);
	if(low[x] == dfn[x]){
		int ma = 0, mi = 1e9;
		do{cmax(ma, stk[top]), cmin(mi, stk[top]), in[stk[top]] = 0;}while(stk[top--] != x);
		if(ma != mi)nxt[mi] = ma - 1;
	}
}
int32_t main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, m, u, v, q, l;
	cin >> n >> m, l = 1;
	FL(i, 1, n)nxt[i] = n + 1;
	FL(i, 1, m)cin >> u >> v, e[u].eb(v), e[v].eb(u);
	cin >> q;
	FL(i, 1, n)if(!dfn[i])tarjan(i, 0);
	FR(i, n - 1, 1)cmin(nxt[i], nxt[i + 1]);
	FL(i, 1, n){
		while(l <= i && nxt[l] < i)l++;
		low[i] = l, sum[i] = sum[i - 1] + nxt[i];
	}
	while(q--){
		int l, r, p;
		cin >> l >> r, p = max(l, low[r]);
		int s = sum[p - 1] - sum[l - 1] + (r - p + 1) * r;
		cout << s - (r - l + 1) * (r + l) / 2 + (r - l + 1) << endl;
	}
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：2)

注意到没有偶环，那么只剩下奇环，题目好做了许多。

众所周知，一个图是二分图当且仅当不存在奇环，那么要让题目中的子图是二分图的话需要满足不包含奇环。这个东西比较难搞，不放把每个环 $P$ 映射成一个区间 $[x_{\text{min}}, x_{\text{max}}]$，其中 $\displaystyle x_{\text{min}} = \max_{x \in P} x, x_{\text{max}} = \min_{x \in P} x$，此时一个包含 $[l, r]$ 点的子图不是二分图当且仅当 $l \ge x_{\text{min}}$ 且 $r < x_{\text{max}}$。

那么我们怎么找环？显然地，我们构建一下图的 DFS 生成树并存储非树边，那么我们发现当我们把非树边加入生成树就产生了环。环怎么映射成区间？（~~虽然也没啥好讲的~~）

考虑如下的图的生成树（样例 $2$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/sdjzsw3r.png)

加入边 $(7, 8)$：

![](https://cdn.luogu.com.cn/upload/image_hosting/6fdql0mn.png)

此时我们找到了一个环，此时可以映射出区间 $[3, 8]$，然后你发现我们只要去求解一下 $7$ 到 $8$ 的简单路径的点的最小值和最大值就行了。这个地方可以使用倍增实现。

接下来我们要求解的是这个式子：

$$
\sum_{x = l}^r \sum_{y = x} ^ r \left[y < \min_{x_{\text{min}} \ge l} \{x_{\text{max}} \}\right]
$$

注意上述式子中的括号是艾弗森括号，接下来考虑优化，预处理 $p_l$：

$$
p_l = \min_{x_{\text{min}} \ge l} \{x_{\text{max}} \}.
$$

原式转换为：

$$
\sum_{x = l}^r \sum_{y = x} ^ r [y < p_x].
$$

由于 $p_l$ 是后缀形式，必然单调不降，那么令 $\displaystyle z = \min_{p_i > r} i$，又可以转换为：

$$
\sum_{x = l} ^ {z - 1} (p_x - x) + \sum_{x = z} ^ r (r - x + 1) = \sum_{x = l} ^ {z - 1} p_x + (r - z + 1)(r + 1) - \sum_{x = l}^r x.
$$

预处理前缀和再二分查找即可，时间复杂度 $\mathcal{O}((n + q) \log n)$。

参考代码：

```cpp
/*
 * author: LostKeyToReach
 * created time: 2025-05-16 10:12:51
 */
#include <bits/stdc++.h>
#define int long long
#define vi vt<int>
using ll = long long; using pii = std::pair<int, int>;
template<typename T> using vt = std::vector<T>;
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define For(i, a, b) for(int i = (a); i <= (b); ++i)
#define Rof(i, a, b) for(int i = (a); i >= (b); --i)
#define S std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0)
template<typename T> T chkmax(T& x, T y) {
    return (x < y) ? (x = y, y) : x;
} template<typename T> T chkmin(T& x, T y) {
    return (x > y) ? (x = y, y) : x;
}int fio = (S, 0); constexpr int N = 5e5 + 5;
int32_t main() {int n, m; vt<pii> bk;
    std::cin >> n >> m; vi dep(n + 1, 0);
    vt<vi> adj(n + 1); For(i, 1, m){
        int x, y; std::cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    } vt<vi> anc(20, vi(n + 1, 0)), mn = anc, mx = anc;
    auto dfs = [&](auto&&self, int x, int s) -> void {
        for (auto&y : adj[x]) {if (y ^ anc[0][x]) {
            if (!dep[y] && y != s) {
                anc[0][y] = x, mn[0][y] = std::min(x, y);
            mx[0][y] = std::max(x, y), dep[y] = dep[x] + 1;
            self(self, y, s);
            } else if (dep[y] < dep[x] - 1) bk.emplace_back(x, y);
        } } }; For(i, 1, n) if (!dep[i]) {
        anc[0][i] = mn[0][i] = mx[0][i] = i;
        dfs(dfs, i, i);
    } For(i, 1, 19) For(j, 1, n) {
        anc[i][j] = anc[i - 1][anc[i - 1][j]];
        mn[i][j] = std::min(mn[i - 1][j], mn[i - 1][anc[i - 1][j]]);
        mx[i][j] = std::max(mx[i - 1][j], mx[i - 1][anc[i - 1][j]]);
    } auto query = [&](int x, int y) -> pii {
        int minn = std::min(x, y), maxn = std::max(x, y);
        if (dep[x] < dep[y]) std::swap(x, y);
        int d = dep[x] - dep[y]; For(i, 0, 19) if (d & (1 << i)) {
            chkmin(minn, mn[i][x]), chkmax(maxn, mx[i][x]);
            x = anc[i][x];} if (x == y) return std::make_pair(minn, maxn);
        Rof(i, 19, 0) if (anc[i][x] != anc[i][y]) {
            chkmin(minn, std::min(mn[i][x], mn[i][y]));
            chkmax(maxn, std::max(mx[i][x], mx[i][y]));
            x = anc[i][x], y = anc[i][y];}
        chkmin(minn, std::min(mn[0][x], mn[0][y]));
        chkmax(maxn, std::max(mx[0][x], mx[0][y]));
        return std::make_pair(std::min(minn, anc[0][x]), std::max(maxn, anc[0][x]));
    }; vt<vi> buc(n + 1); vi lim(n + 1, 0);
    for (auto&[x, y] : bk) { auto [a, b] = query(x, y);
        buc[a].emplace_back(b);
    } int cur = n + 1;Rof(i, n, 1) {
        for (auto&x : buc[i]) chkmin(cur, x); lim[i] = cur;
    } vi tmp = lim; For(i, 1, n) lim[i] += lim[i - 1];
    int q; std::cin >> q; while (q--) {
        int l, r; std::cin >> l >> r;
        int lo = l, hi = r, p = r + 1; while (lo <= hi){
            int mid = (lo + hi) >> 1; if (tmp[mid] <= r)
                lo = mid + 1; else hi = (p = mid) - 1;
        } std::cout << lim[p - 1] - lim[l - 1]
         + (r - p + 1) * (r + 1) - r * (r + 1) / 2 + l * (l - 1) / 2 << "\n";
    }
}
```

---

## 作者：Eric998 (赞：2)

好题。和同学 ```duel``` 到的。做了 ```1.2h```，是不是有点唐了。

~~省选 d1t1 放这个就好了~~

#### Lemma 1：该图是仙人掌。

证明：我们假设有一条边同时属于两个简单环，则由题意得这两个环只能是奇环。

我们注意到若两个大小为  $x,y$ 的环若有交，设大小为 $s$，则一定存在一个大小为 $x+y-2s$ 的环。

$x,y$ 是奇数，则 $x+y-2s$ 为偶数。与题意矛盾。

#### Lemma 2：若选出子图有环，则一定不是二分图

由题意得，环必定是奇环。

考虑做法。先用 ```tarjan``` 找出每个环，做出每个环的最大和最小编号。由于图是仙人掌，一个点/边双显然只有一个环。

注意到若 $[x,y]$ 包含了一个环的最小号节点和最大号节点，则一定非法。我们直接扫描线搞出每个 $x$ 对应的最大 $y$，记为 $rv_i$，有单调性。

对于询问 $[L,R]$，答案为  $\displaystyle(\sum_{i=L}^R\min(rv_i,R))-\frac {R(R+1)-L(L-1)}2$。由于 $rv_i$ 的单调性，二分用脚维护即可。我写了，不需要任何脑子！

code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 300005
int vis[N], dfn[N], low[N], st[N], cut[N], rv[N], tot, n, m, cct, sum, top, rt, q;
vector<int> E[N], bcc[N], pos[N];
long long pre[N];

void tarjan(int u, int fa) {
	low[u] = dfn[u] = ++tot;
	st[++top] = u;
	int child = 0;
	for (auto nxt : E[u]) {
		if (dfn[nxt] == 0) {
			child++;
			tarjan(nxt, u);
			low[u] = min(low[u], low[nxt]);
			if (low[nxt] >= dfn[u]) {
				sum++;
				int tmp;
				do
					tmp = st[top--], bcc[sum].push_back(tmp);
				while (tmp != nxt);
				bcc[sum].push_back(u);
			}
		} else if (dfn[nxt] < dfn[u] && nxt != fa)
			low[u] = min(low[u], dfn[nxt]);
	}
	if (u == rt && child == 0)
		bcc[++sum].push_back(u);
}

long long rq(int l, int r) {
	long long res = 1ll * r * (r + 1) / 2;
	res -= 1ll * l * (l - 1) / 2;
	return res;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, l, r; i <= m; i++)
		cin >> l >> r, E[l].push_back(r), E[r].push_back(l);
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			rt = i, tarjan(i, 0);
	for (int i = 0; i < N; i++)
		if (bcc[i].size() > 2) {
			int mn = 0x3f3f3f3f, mx = 0xc0c0c0c0;
			for (int it : bcc[i])
				mx = max(mx, it), mn = min(mn, it);
			pos[mn].push_back(mx);
		}
	set<int> st;
	st.insert(0x3f3f3f3f);
	for (int i = N - 1; ~i; --i) {
		for (int it : pos[i])
			st.insert(it);
		rv[i] = *st.begin();
	}
	for (int i = 1; i <= n; i++)
		pre[i] = pre[i - 1] + rv[i];
	cin >> q;
	while (q--) {
		int l, r, p;
		cin >> l >> r, p = upper_bound(rv + l, rv + r + 1, r) - rv;
		cout << (pre[p - 1] - pre[l - 1] + 1ll * (r - p + 1)*r) - rq(l, r) + r - p + 1 << '\n';
	}
}
```

---

## 作者：do_it_tomorrow (赞：2)

没有偶还还全部是二分图，显然应该是一个森林。

搞一个 tarjan 去把环找出来，记录这个环最小和最大的编号，那么包含这个环的区间都死了。

我们设 $f_{x}$ 表示 $[x,f_x]$ 是合法的，但是 $[x,f_x+1]$ 不合法。

那么如果一个环的两个极值为 $mn,mx$，那么所有 $i\in [1,mn]$ 的 $f_i$ 都要 $f_i\gets \min(f_i,mx-1)$。

求解出 $f$ 后答案就很显然了：

$$ans=\sum\limits_{i=l}^r \min(f_i,r)-i+1$$

简化一下：

$$ans=\dfrac{(2-l-r)\times(r-l+1)}{2}+\sum\limits_{i=l}^r \min(f_i,r) $$

因为 $f_i$ 是单调的，所以可以二分一下 $\min$ 取到的后缀，于是复杂度为 $O(n+q\log n)$。

需要注意当 $mn=mx$ 的时候的处理。


[Submission #320476111 - Codeforces](https://codeforces.com/contest/901/submission/320476111)

---

## 作者：wptt (赞：1)

判定二分图的充要条件是没有奇环，题目保证没有偶环，而两个奇环拼起来是个偶环，那么题目中所有环都是简单环。

也就是说我选的区间不能有环，也就是不能把某个环的所有点全部包含，就是不能包含某个环的两个极值。

用个倍增什么的，求出每个环最大最小值，然后我们将询问离线。

对于每个右端点 $r$，对每个 $i$ 求出 $[i, r]$ 是否合法，我们考虑合法的肯定是一段后缀，求出第一个合法的点 $x$，然后将 $[x, r]$ 全部加 $1$。

最后扫的时候遇到询问 $[l, r]$ 就直接求 $[l, r]$ 的和就行。

时间复杂度 $\mathcal{O}((n + q) \log n)$ 。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3E5 + 5;
constexpr int inf = 1E9;

int n, m, q;
i64 ans[N];

struct Query {
	int l, id;
	Query(int _l = 0, int _id = 0) : l(_l), id(_id) {}
};

std::vector<Query> que[N];
std::vector<int> seg[N];

struct SegmentTree {
	#define ls(u) u << 1
	#define rs(u) u << 1 | 1

	i64 s[N << 2];
	int tag[N << 2];

	void PushDown(int u, int l, int r) {
		if (!tag[u]) return;
		int &add = tag[u];
		int mid = l + r >> 1;
		s[ls(u)] += 1ll * (mid - l + 1) * add, s[rs(u)] += 1ll * (r - mid) * add;
		tag[ls(u)] += add, tag[rs(u)] += add;
		add = 0;
	}

	void modify(int u, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			s[u] += r - l + 1, tag[u]++;
			return;
		}

		PushDown(u, l, r);

		int mid = l + r >> 1;

		if (ql <= mid) modify(ls(u), l, mid, ql, qr);
		if (qr > mid) modify(rs(u), mid + 1, r, ql, qr);

		s[u] = s[ls(u)] + s[rs(u)];
	}

	i64 query(int u, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			return s[u];
		}

		PushDown(u, l, r);

		int mid = l + r >> 1;
		i64 ans = 0;

		if (ql <= mid) ans += query(ls(u), l, mid, ql, qr);
		if (qr > mid) ans += query(rs(u), mid + 1, r, ql, qr);

		return ans;
	}

	#undef ls
	#undef rs
}t;

std::vector<int> G[N];
std::bitset<N> vis;
int dep[N];
int fa[20][N], mx[20][N], mn[20][N];

std::pair<int, int> calc(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	int Mx = 0, Mn = inf;
	for (int i = 19; i >= 0; i--) {
		if (dep[fa[i][u]] >= dep[v]) {
			Mx = std::max(Mx, mx[i][u]);
			Mn = std::min(Mn, mn[i][u]);
			u = fa[i][u];
		}
	}
	Mx = std::max(Mx, v), Mn = std::min(Mn, v);
	return std::make_pair(Mx, Mn);
}

void dfs(int u, int FA) {
	vis[u] = true;
	dep[u] = dep[FA] + 1;
	fa[0][u] = FA;
	mx[0][u] = u, mn[0][u] = u;
	for (int i = 1; i < 20; i++) {
		fa[i][u] = fa[i - 1][fa[i - 1][u]];
		mx[i][u] = std::max(mx[i - 1][u], mx[i - 1][fa[i - 1][u]]);
		mn[i][u] = std::min(mn[i - 1][u], mn[i - 1][fa[i - 1][u]]);
	}
	for (auto v : G[u]) {
		if (!vis[v]) {
			dfs(v, u);
		} else if (v != FA) {
			if (dep[v] > dep[u]) continue;
			auto t = calc(u, v);
			seg[t.first].push_back(t.second);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs(i, 0);
		}
	}

	std::cin >> q;

	for (int i = 1; i <= q; i++) {
		int l, r;
		std::cin >> l >> r;
		que[r].emplace_back(l, i);
	}

	int l = 1;
	for (int r = 1; r <= n; r++) {
		for (auto x : seg[r]) {
			l = std::max(l, x + 1);
		}
		if (l <= r) t.modify(1, 1, n, l, r);
		for (auto [l, id] : que[r]) {
			ans[id] = t.query(1, 1, n, l, r);
		}
	}

	for (int i = 1; i <= q; i++) {
		std::cout << ans[i] << "\n";
	}
	return 0;
}
```

---

## 作者：zhengrunzhe (赞：1)

感谢楼下 **「QQ红包」** 提供的宝贵LCT思路

~~然而他写了另一个算法~~

那我这边就把这个东西实现一下

实际上可以不用什么线段树

#### 题面:给你一个有n个点的无向图，没有偶环。

那就是如果有环就只能是奇环，所以判有没有环就可以知道能不能构成二分图

首先可以预处理出一个东西比如记作$f()$

 $$f(l)=max \left \{ r \right \}([l,r]\text{无环})$$

假定$Rm=f(l)$，那么$ \forall r \in[l,Rm],\text{都有}[l,r] \text{无环}, \forall r \in (Rm,n],\text{都有}[l,r] \text{有环}$

类似 **Two-Pointers** ，所以我们可以从$n$到1枚举$l$，每次$l$往前拓展的时候，看$[l,r]$是否有环，不断尝试往前缩小$r$直到无环，就可以对每个$l$预处理出$f(l)=r$

有了这个玩意，我们怎么统计询问呢？

将询问离线下来按r从小到大排序

比如当前的询问右端点为$qr$

对于所有的$i \ s.t. f(i)<=qr,i$的单点贡献为$f(i)-i+1$，记这样最大的$i=last$，并把所有i的贡献记下来存到前缀和数组里记作$sum[i]$

然后对于询问$[ql,qr]$

如果$ql>last$，答案就是$\frac {(qr-ql+1)(qr-ql)}{2}$

否则答案为$sum[last]-sum[ql-1]+ \frac {(qr-last)*(qr-last+1)}{2}$


我们来手模一下这个玩意

对于样例1：

$i:\ \ \ \ \ 1 \  \ \  2 \ \ \  3 \ \ \  4 \ \ \  5 \ \ \  6$

$f(i):2 \ \ 5 \ \ \ 5 \ \ \ 5 \ \ \ 6 \ \ \ 6$

询问：$[1,3],[1,6],[4,6]$

从1开始扫

1的时候什么也没发生

2的时候有1使得$f(1)=2$，贡献为2-1+1=2，last=1

装到贡献数组$a$里：$2$

3的时候有询问$[1,3]$

此时答案为$a[1]+\frac {(3-2+1)(3-2+1+1)}{2}=2+3=5$

继续扫，4什么也没发生

5有$f(2)=f(3)=f(4)=5$，贡献分别为$5-2+1=4,5-3+1=3,5-4+1=2,last=4$

装到a里:$2,4,3,2$

继续扫6，有$f(5)=f(6)=6$，贡献分别为$6-5+1=2,6-6+1=1$

装到a里:$2,4,3,2,2,1$

有询问$[4,6]$，答案为a的$[4,6]$区间和为$2+2+1=5$

有询问$[1,6]$，答案为a的$[1,6]$区间和为$2+4+3+2+2+1=14$

然后这道题就做完了

询问思路特别鸣谢@[ZYyboT](https://www.luogu.org/space/show?uid=14375)

#### 时间复杂度：

##### lct预处理：

$r$指针最多移动n次，每移动一次需要用lct删除所有出边，$O(n)+O(m log n)=O(m log n)$

##### 离线询问:

显然$O(n)+O(m)$

#### 总复杂度$O(m log n)$
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using std::min;
using std::sort;
using std::swap;
using std::vector;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)putchar('-'),out=-out;
	write(out);
	putchar('\n');
}
typedef long long ll;
const int N=3e5+10;
class Link_Cut_Tree
{
	private:
		struct tree
		{
			bool rev;
			int son[2],fa;
			inline const void reverse()
			{
				swap(son[0],son[1]);rev^=1;
			}
		}t[N];
		inline const bool identity(int p)
		{
			return t[t[p].fa].son[1]==p;
		}
		inline const bool nroot(int p)
		{
			return t[t[p].fa].son[0]==p||identity(p);
		}
		inline const void rotate(int p)
		{
			bool f=identity(p);
			int fa=t[p].fa,gfa=t[fa].fa,q=t[p].son[f^1];
			if (nroot(fa))t[gfa].son[identity(fa)]=p;
			t[t[p].son[f^1]=fa].son[f]=q;
			t[t[t[q].fa=fa].fa=p].fa=gfa;
		}
		inline const void pushdown(int p)
		{
			if (t[p].rev)
				t[t[p].son[0]].reverse(),
				t[t[p].son[1]].reverse(),
				t[p].rev=0;
		}
		inline const void relieve(int p)
		{
			if (nroot(p))relieve(t[p].fa);
			pushdown(p);
		}
		inline const void splay(int p)
		{
			relieve(p);
			for (int fa;nroot(p);rotate(p))
				if (nroot(fa=t[p].fa))
					rotate(identity(p)^identity(fa)?p:fa);
		}
		inline const void access(int x)
		{
			for (int y=0;x;x=t[y=x].fa)splay(x),t[x].son[1]=y;
		}
		inline const void makeroot(int x)
		{
			access(x);splay(x);t[x].reverse();
		}
		inline const void split(int x,int y)
		{
			makeroot(x);access(y);splay(y);
		}
		inline const int findroot(int x)
		{
			access(x);splay(x);
			while (t[x].son[0])pushdown(x=t[x].son[0]);
			splay(x);return x;
		}
	public:
		inline const bool connected(int x,int y)
		{
			return findroot(x)==findroot(y);
		}
		inline const bool link(int x,int y)
		{
			if (findroot(x)==findroot(y))return 0;
			makeroot(x);t[x].fa=y;
			return 1;
		}
		inline const void cut(int x,int y)
		{
			split(x,y);t[x].fa=t[y].son[0]=0;
		}
}lct;
ll ans[N];
int n,m;
bool inf[N];
int head[N],edc,to[N<<1],next[N<<1];
inline const void link(int u,int v)
{
	next[++edc]=head[u];to[head[u]=edc]=v;
	next[++edc]=head[v];to[head[v]=edc]=u;
}
struct query
{
	int l,r,id;
	inline const bool operator<(const query &q)const
	{
		return r<q.r;
	}
}q[N];
vector<int>from[N];
ll sum[N];
inline const ll Sum(int l,int r)
{
	return sum[r]-sum[l-1];
}
int main()
{
	read(n);read(m);
	for (int u,v;m--;)read(u),read(v),link(u,v);
	read(m);
	for (int i=1;i<=m;i++)read(q[i].l),read(q[i].r),q[i].id=i;
	sort(q+1,q+m+1);
	for (int r=n,l=n;l;l--)
	{
		inf[l]=1;
		int j=head[l];
		while (j)
		{
			if (!inf[to[j]]){j=next[j];continue;}
			if (lct.link(l,to[j])){j=next[j];continue;}
			for (;lct.connected(l,to[j])&&r>=l;inf[r--]=0)
				for (int k=head[r];k;k=next[k])
					if (inf[to[k]])
						lct.cut(r,to[k]);
		}
		from[r].push_back(l);
	}
	for (int k=1,last=0,i=1;i<=n;i++)
	{
		for (int j=from[i].size()-1;~j;j--)
			sum[from[i][j]]=i-from[i][j]+1+sum[from[i][j]-1];
		if (!from[i].empty())last=*from[i].begin();
		for (int len;q[k].r<=i&&k<=m;k++)
			if (q[k].l>last)
				len=q[k].r-q[k].l+1,
				ans[q[k].id]=static_cast<ll>(len)*(len+1)/2;
			else 
				len=q[k].r-last,
				ans[q[k].id]=static_cast<ll>(len)*(len+1)/2+Sum(q[k].l,last);
	}
	for (int i=1;i<=m;i++)writeln(ans[i]);
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF901C)

## 思路

震惊，怎么能没有主席树题解。

首先，题目告诉我们这张图没有偶环，也就是没有环套环的情况。

然后，找出图中所有的环就等价于找出所有的边双，我们记录每个边双内节点的 $\min$ 和 $\max$，把它们记为 $l,r$，那么假如 $x,y$ 内存在一段完整的区间 $l,r$，那就不合法，所以我们可以预处理出 $nxt_i$ 表示 $i$ 往右最多延伸到哪个节点。

考虑答案如何计算，容易发现答案就是：$\sum_{i=l}^r \min(nxt_i,r)-i+1$。不妨拆一拆贡献，化简成为 $\sum_{i=l}^r\min(nxt_i,r)-\sum_{i=l}^r i-1$，右边这个可以直接 $\mathcal O(1)$ 求出，左边分类讨论一下，然后直接用主席树求得即可。

时间复杂度 $\mathcal O(n \log n)$。

## 码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
int const N=3e5+10;
int vis[N],tot,del[N],nxt[N],root[N];
vector< pair<int,int> >a[N];
struct node{int u,v;}b[N];
int dfn[N],low[N],ind[N],minx,cnt,maxx,s[N],top;
inline void tarjan(int x,int fa){
	dfn[x]=low[x]=++cnt;
	s[++top]=x;ind[x]=1;
	for (auto [v,id]:a[x]){
		if (v==fa) continue;
		if (!dfn[v]){
			tarjan(v,x);
			if (low[v]>dfn[x]) del[id]=1;
			low[x]=min(low[x],low[v]);
		}else if (ind[v]) low[x]=min(low[x],dfn[v]);
	}
	if (low[x]==dfn[x]){
		while (1){
			int X=s[top--];
			ind[X]=0;
			if (X==x) break;
		}
	}
}
int go;
inline void dfs(int x){
	vis[x]=1;minx=min(minx,x);
	maxx=max(maxx,x);++go;
	for (auto [v,id]:a[x]){
		if (vis[v]) continue;
		if (del[id]) continue;
		dfs(v);
	}
}
inline bool cmp(node x,node y){return x.u>y.u;}
struct hjt_Tree{
	int lc[N*28],rc[N*28],c[N*28];
	long long d[N*28];
	inline void update(int &x,int la,int l,int r,int p){
		x=++cnt;c[x]=c[la];d[x]=d[la];lc[x]=lc[la];rc[x]=rc[la];
		if (l==r){++c[x];d[x]+=p;return;}
		if (p<=mid) update(lc[x],lc[la],l,mid,p);
		else update(rc[x],rc[la],mid+1,r,p);
		c[x]=c[lc[x]]+c[rc[x]];
		d[x]=d[lc[x]]+d[rc[x]];
	}
	inline pair<int,long long> query(int x,int l,int r,int ll,int rr){
		if (ll<=l && r<=rr) return {c[x],d[x]};
		long long res1=0,res2=0;
		if (ll<=mid){auto down=query(lc[x],l,mid,ll,rr);res1+=down.first,res2+=down.second;}
		if (mid<rr){auto down=query(rc[x],mid+1,r,ll,rr);res1+=down.first,res2+=down.second;}
		return {res1,res2};
	}
}T;
inline long long run(int x,int y){return 1ll*(x+y)*1ll*(y-x+1)/2;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;cin>>n>>m;int u1=0;
	for (int i=1;i<=m;++i){
		int u,v;cin>>u>>v;
		if (!u1) u1=u;
		a[u].push_back({v,i});
		a[v].push_back({u,i});
	}
	for (int i=1;i<=n;++i) if (!dfn[i]) tarjan(i,0);
	for (int i=1;i<=n;++i)
		if (!vis[i]){
			minx=1e9,maxx=-1e9;go=0;
			dfs(i);
			if (go>1) b[++tot].u=minx,b[tot].v=maxx;
		}
	sort(b+1,b+tot+1,cmp);
	int now=n+1,l=1;
	for (int i=n;i;--i){
		while (l<=n && b[l].u>=i) now=min(now,b[l].v),++l;
		nxt[i]=now-1;
	}
	root[0]=cnt=1;
	for (int i=1;i<=n;++i) T.update(root[i],root[i-1],0,n,nxt[i]);
	int q;cin>>q;
	int tag=0;
	while (q--){
		int l,r;cin>>l>>r;
		long long res=T.query(root[r],0,n,0,r).second-T.query(root[l-1],0,n,0,r).second;
		res+=1ll*(T.query(root[r],0,n,r+1,n).first-T.query(root[l-1],0,n,r+1,n).first)*r;
		res-=run(l-1,r-1);
		cout<<res<<'\n';
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

区间询问子区间点对构成二分图个数。             

如果能有偶环的话估计会不可错，但是由于题目保证只有奇环所以只要出现环就可以保证原图不是二分图。            

根据这个性质，我们随机造一棵 dfs 树然后暴力把所有的环拿出来问一遍，显然这个环上的最大点和最小点构成的区间都是不能选择的，我们考虑离线路径或者树剖维护上述的信息。          

接着你发现其实如果我们能知道序列上一个点向后能极长延伸到哪里那么原问题就变成了个平凡的对区间值取 $\min$ 后区间查询的问题，令 $Far_x$ 表示一个点 $x$ 最远延伸到了哪里。

现在我们有多组限制信息形如二元组 $(x,y)$ 表示不能选择区间 $[x,y]$，我们只要让所有的 $Far_x = \min y$ 后再滚一个后缀 $\min$ 就可以维护所有 $Far_x$ 的信息了，时间复杂度 $O((n + m) \log n)$。           

```cpp
/*
考虑计算出每个点的极长延伸然后直接主席树
没有偶环代表着只要出现环就挂了
现在只要知道如何判断一些边是否出现环即可
好像可以直接dfs环吧，不清楚，反正总之最后可以离线做就对了 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 3e5 + 5 , Inf = 1e9;
int n,m,q,vis[Len],val[Len],head[Len],cnt,tim[Len],dfn;
int Minn[Len << 2],Maxn[Len << 2];
long long sum[Len << 2],num[Len << 2],Print[Len];
struct Node
{
	int opt,val,id;
	Node(){opt = val = id = 0;}
	Node(int OPT,int VAL,int ID){opt = OPT , val = VAL , id = ID;}
};
vector<Node> v[Len]; 
vector<int> G[Len];
#define ls(p) p << 1
#define rs(p) p << 1 | 1
void Push_up(int x)
{
	Minn[x] = min(Minn[ls(x)] , Minn[rs(x)]);
	Maxn[x] = max(Maxn[ls(x)] , Maxn[rs(x)]);
}
void build(int p,int l,int r)
{
	Minn[p] = Inf , Maxn[p] = -Inf;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);build(rs(p) , mid + 1 , r);
}
void Update(int p,int l,int r,int idx,int val)
{
	if(l == r) 
	{
		if(val == -1)
		{
			Minn[p] = Inf;
			Maxn[p] = -Inf;
		}
		else Minn[p] = Maxn[p] = val;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) Update(ls(p) , l , mid , idx , val);
	else Update(rs(p) , mid + 1 , r , idx , val);
	Push_up(p);
}
int queryMin(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return Minn[p];
	int mid = (l + r) >> 1 , res = Inf;
	if(nl <= mid) res = min(res , queryMin(ls(p) , l , mid , nl , nr));
	if(nr > mid) res = min(res , queryMin(rs(p) , mid + 1 , r , nl , nr));
	return res;
}
int queryMax(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return Maxn[p];
	int mid = (l + r) >> 1 , res = -Inf;
	if(nl <= mid) res = max(res , queryMax(ls(p) , l , mid , nl , nr));
	if(nr > mid) res = max(res , queryMax(rs(p) , mid + 1 , r , nl , nr));
	return res;
}
void Calc(int x,int to)
{
	int minn = queryMin(1 , 1 , n , min(tim[x] , tim[to]) , max(tim[x] , tim[to]));
	int maxn = queryMax(1 , 1 , n , min(tim[x] , tim[to]) , max(tim[x] , tim[to]));
	val[minn] = min(val[minn] , maxn);
	//printf("%d %d %d %d\n",x,to,minn,maxn);
}
void dfs(int x,int f)
{
	vis[x] |= 1;
	tim[x] = ++ dfn;
	Update(1 , 1 , n , dfn , x);
	for(int i = 0 ; i < G[x].size(); i ++)
	{
		int to = G[x][i];
		if(to == f || tim[to] > tim[x]) continue;
		if(!vis[to]) 
		{
			dfs(to , x);
			continue;
		}
		Calc(x , to);
	}
	Update(1 , 1 , n , dfn , -1);
	dfn --;
}

void push_up(int x)
{
	sum[x] = sum[ls(x)] + sum[rs(x)];
	num[x] = num[ls(x)] + num[rs(x)];
}
void update(int p,int l,int r,int idx)
{
	if(l == r)
	{
		sum[p] += idx;
		num[p] ++;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx);
	else update(rs(p) , mid + 1 , r , idx);
	push_up(p); 
}
long long query(int p,int l,int r,int val)
{
	if(l == r) return sum[p];
	int mid = (l + r) >> 1;
	if(val <= mid) return query(ls(p) , l , mid , val) + 1ll * num[rs(p)] * val;
	else return query(rs(p) , mid + 1 , r , val) + sum[ls(p)];
}

long long Sum[Len];
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i = 1 ; i <= n ; i ++) 
	{
		Sum[i] += Sum[i - 1];
		Sum[i] += i;
		sort(G[i].begin() , G[i].end()); 
	}
	for(int i = 1 ; i <= n ; i ++) val[i] = n + 1;
	val[n + 1] = n + 1;
 	for(int i = 1 ; i <= n ; i ++) if(!vis[i]) dfs(i , 0);
	for(int i = n ; i >= 1 ; i --) val[i] = min(val[i] , val[i + 1]);
	for(int i = 1 ; i <= n ; i ++) 
	{
		val[i] --;
		//printf("%d ",val[i]);
	}
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		Print[i] -= Sum[y - 1] - Sum[max(0 , x - 2)];
		v[x - 1].push_back(Node(-1 , y , i));
		v[y].push_back(Node(1 , y , i));
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		update(1 , 1 , n , val[i]);
		for(int j = 0 ; j < v[i].size() ; j ++) Print[v[i][j].id] += 1ll * v[i][j].opt * query(1 , 1 , n , v[i][j].val);
	}
	for(int i = 1 ; i <= q ; i ++) printf("%lld\n",Print[i]);
	return 0;
}
```

---

