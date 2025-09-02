# Complete Mirror

## 题目描述

给定一棵包含 $n$ 个顶点的树。选择一个顶点作为根节点，使其满足以下条件：

- 对于所有顶点 $v_1$ 和 $v_2$，如果 $distance(root, v_1) = distance(root, v_2)$，那么 $degree(v_1) = degree(v_2)$。其中 $degree$ 表示该顶点连接的顶点数，$distance$ 表示两个顶点之间的边数。

判断是否存在这样的根节点，并输出任意一个满足条件的根节点编号。如果有多个答案，输出其中任意一个。

## 说明/提示

下图为第一个样例的树结构。$1$、$5$、$7$ 也可以作为合法答案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1182D/bcfdfd4a236e739c696e71629ab4415dcf5e3015.png)

下图为第二个样例的树结构。可以发现无法找到满足条件的根节点。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1182D/20dc627549d275e9f12102ecd454db1d1ee42f2f.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
1 2
2 3
3 4
4 5
3 6
6 7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
1 3
2 3
3 4
4 5
4 6
```

### 输出

```
-1
```

# 题解

## 作者：litble (赞：9)

不难发现，在钦定了这棵树的根后，任何一个点$x$，它的所有儿子们的子树都必须长得一模一样。

所以，若根节点有两个及以上的儿子，它必定是树的重心。

（简单证明：若根为$rt$，它的每个儿子的子树大小为$sz$，则删掉它得到的最大连通块大小为$sz$。而若在它的一个儿子子树中的任意一点，删掉该点得到的最大连通块大小必大于等于$sz+1$）

因此第一步，找到树的重心，然后暴力$O(n)$判断它是否合法。

接下来就只可能是度数为1的点是根了。假设从根节点$x$沿着唯一的路径往树的深处走，走到的第一个度数大于2的点为$y$（产生分岔路），根据树的重心的性质，由于子树$y$的重心为$y$，所以整棵树的重心一定在从$x$到$y$的这条链上。

```plain
     x
     |
     *
     |
     *
     |
     y
    / \
    * *
```

若$rt$只有一棵子树是链，那当然就判断该链的端点是否是根即可。若有多棵子树是链，只有仅出现两种长度的链，且其中一种长度只出现一次，才有可能找到合法解，也就是说检查一遍$rt$的子树，选择两种不同链长的链子树，看它们的端点为根合不合法，若还是不合法，无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
inline int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
const int N=100005,inf=0x3f3f3f3f;
int n,tot,rt,mi,krt,rt2,len_rt2;
int h[N],ne[N<<1],to[N<<1],du[N],sz[N],dep[N];
vector<int> orz[N];

inline void add(int x,int y) {to[++tot]=y,ne[tot]=h[x],h[x]=tot;}
inline void getrt(int x,int las) {//找重心
	sz[x]=1;int bl=0;
	for(RI i=h[x];i;i=ne[i])
		if(to[i]!=las) getrt(to[i],x),bl=max(bl,sz[to[i]]),sz[x]+=sz[to[i]];
	bl=max(bl,n-sz[x]);
	if(bl<mi) mi=bl,rt=x;
}
inline void dfs(int x,int las) {
	dep[x]=dep[las]+1;
	for(RI i=h[x];i;i=ne[i]) if(to[i]!=las) dfs(to[i],x);
}
inline void check(int x) {//检查是否合法
	dfs(x,0);
	for(RI i=1;i<=n;++i) orz[i].clear();
	for(RI i=1;i<=n;++i) orz[dep[i]].push_back(i);
	for(RI i=1;i<=n;++i) {
		for(RI j=1;j<orz[i].size();++j)
			if(du[orz[i][j]]!=du[orz[i][0]]) return;
	}
	printf("%d\n",x);exit(0);
}
inline int is_line(int x,int las) {//是否是链以及链长
	if(du[x]>2) return 0;
	if(du[x]==1) {krt=x;return 1;}
	for(RI i=h[x];i;i=ne[i])
		if(to[i]!=las) {
			int res=is_line(to[i],x);
			if(!res) return 0;
			else return res+1;
		}
}

int main()
{
	int x,y;
	n=read();
	for(RI i=1;i<n;++i) x=read(),y=read(),add(x,y),add(y,x),++du[x],++du[y];
	mi=inf,getrt(1,0);
	check(rt);
	for(RI i=h[rt];i;i=ne[i]) {
		int len=is_line(to[i],rt);
		if(!len) continue;
		if(rt2&&len!=len_rt2) {check(krt);break;}
		if(!rt2) rt2=krt,len_rt2=len,check(krt);
	}
	puts("-1");
	return 0;
}
```

---

## 作者：i207M (赞：5)

ri，这道水题写完之后我TM调了1h才A，我太蠢了！先是把直径的端点当成直径的中点；然后忘了去特地check直径的中点又调了好久...

首先看到这道题，很容易想到与树的直径有关，假如我们求出来树的一条直径，那么最终答案要么

1. 是直径的端点——跑两遍check即可

2. 是直径的中点——再check一遍（注意如果直径有偶数个点，那么是没有中点的！）

3. 是直径的中点的一个儿子

需要特别考虑的就是3.：

我们先求出每个点子树的Hash值，从直径的中点开始递归。如果递归到点x，它的儿子中，每种都出现了偶数次，那么x就是答案；如果只有一种出现了奇数次，那么递归进行；如果多于一种，那么这个点的子树不可能有答案了。

--------------

这里特别说一下为什么不能把2.归为3.：因为可能出现直径的中点挂了奇数个相同的儿子，这是合法的，但是的确有一个儿子出现了奇数次！

```cpp
#define N 100005
il void gun(int ans)
{
	out(ans);
	exit(0);
}
int n;
vector<int> E[N];
int mxd,mxdk;
int fa[N];
void dfs(int x,int _fa,int d)
{
	fa[x]=_fa;
	if(ckmax(mxd,d)) mxdk=x;
	for(solid v:E[x])
	{
		if(v==_fa) continue;
		dfs(v,x,d+1);
	}
}
const int bas=233,md[2]= {(int)1e9+7,(int)1e9+9};
pii h[N];
void efs(int x,int _fa)
{
	vector< pii > hv;
	for(solid v:E[x])
	{
		if(v==_fa) continue;
		efs(v,x);
		hv.pb(h[v]);
	}
	h[x]=mp(1,1);
	sort(hv.begin(),hv.end());
	for(solid v:hv)
	{
		h[x].fi=((LL)h[x].fi*bas+v.fi)%md[0];
		h[x].se=((LL)h[x].se*bas+v.se)%md[1];
	}
}
void gfs(int x,int _fa)
{
	map< pii,vector<int> > mt;
	for(solid v:E[x])
	{
		if(v==_fa) continue;
		mt[h[v]].pb(v);
	}
	pii nx=mp(-1,-1);
	for(solid it:mt)
		if(Size(it.se)&1)
		{
			if(nx.fi!=-1) return;
			nx=it.fi;
		}
	if(nx.fi==-1) gun(x);
	for(solid v:mt[nx]) gfs(v,x);
}
bool ok;
int du[N];
void hfs(int x,int _fa,int d)
{
	if(!ok) return;
	if(!du[d]) du[d]=Size(E[x]);
	else if(du[d]!=Size(E[x]))
	{
		ok=0;
		return;
	}
	for(solid v:E[x])
	{
		if(v==_fa) continue;
		hfs(v,x,d+1);
	}
}
il void check(int x)
{
	mem(du,0);
	ok=1,hfs(x,0,1);
	if(ok) gun(x);
}
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	in(n);
	for(ri i=1,a,b; i<n; ++i)
	{
		in(a,b);
		E[a].pb(b),E[b].pb(a);
	}
	dfs(1,0,1);
	check(mxdk); mxd=0;
	dfs(mxdk,0,1);
	check(mxdk);
	if((mxd&1)==0) gun(-1);
	int x=mxdk;
	for(ri i=1; i<=(mxd>>1); ++i) x=fa[x];
	check(x);
	efs(x,0);
	gfs(x,0);
	gun(-1);
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：2)

首先不难发现以答案为根的树必然满足这个性质，每个点的所有儿子子都是同构的，如果有一个不同构那必然会存在矛盾的点，否则是一定可行的。

然后，树的同构，我们不难想**树哈希**，然后做法就比较显然了，给这棵树进行一个换根dp，先dfs一遍搞出子树内的哈希值以及是否可行（即是否子树内的所有点的儿子的哈希值相等），再dfs一遍搞出每个点父亲去掉这个点的子树再作为根的哈希值以及是否可行。如果一个点有2个儿子都不可行，或者儿子有3种哈希值，那么直接无解，因为不管根在哪个方向都是不行的。然后根就只能在那个与众不同的儿子的子树里，大力讨论一波即可。

另外注意到我们只需要求可行的儿子的哈希值，显然它的所有儿子哈希值都相同，那么我们可以在它的儿子的哈希值后面接一个儿子个数就行了，然后3模数Hash稳过……

是不是很简单粗暴啊……

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define ll long long
#define p1 998244353
#define p2 1000000007
#define p3 1004535809
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	typedef struct _b {
	    int dest;
	    int nxt;
	} bian;
	bian memchi[1000001];
	int gn = 1, heads[100001];
	int deg[100001];
	inline void add(int s, int t) {
	    memchi[gn].dest = t;
	    memchi[gn].nxt = heads[s];
	    heads[s] = gn;
	    gn++;
	    deg[t]++;
	}
	int tmp[100001];
	typedef struct _p {
	    ll a1, a2, a3;
	    _p() { a1 = a2 = a3 = 0; }
	    _p(int x) { a1 = a2 = a3 = x; }
	    _p(ll a, ll b, ll c) {
	        a1 = a;
	        a2 = b;
	        a3 = c;
	    }
	    friend bool operator==(const _p &a, const _p &b) {
	        return (a.a1 == b.a1 && a.a2 == b.a2 && a.a3 == b.a3);
	    }
	    friend bool operator!=(const _p &a, const _p &b) { return (!(a == b)); }
	    friend _p operator+(const _p &a, const _p &b) {
	        return (_p((a.a1 + b.a1) % p1, (a.a2 + b.a2) % p2, (a.a3 + b.a3) % p3));
	    }
	    friend _p operator*(const _p &a, const int &b) {
	        return (_p((a.a1 * b) % p1, (a.a2 * b) % p2, (a.a3 * b) % p3));
	    }
	} pair;
	unsigned char candown[100001];
	pair dp[100001], dpup[100001];
	void dfs(int pt, int baba) {
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        dfs(memchi[i].dest, pt);
	    }
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        if (!candown[memchi[i].dest])
	            return;
	    }
	    int ptr = 1;
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        tmp[ptr] = memchi[i].dest;
	        ptr++;
	    }
	    ptr--;
	    for (register int i = 2; i <= ptr; i++)
	        if (dp[tmp[i]] != dp[tmp[1]])
	            return;
	    if (!ptr) {
	        candown[pt] = 1;
	        dp[pt] = _p(1);
	        return;
	    }
	    dp[pt] = dp[tmp[1]] * 233 + _p(ptr);
	    candown[pt] = 1;
	}
	int n;
	void efs(int pt, int baba) {
	    if (!baba) {
	        int cnt = 0;
	        for (register int i = heads[pt]; i; i = memchi[i].nxt) cnt += (!candown[memchi[i].dest]);
	        if (cnt >= 2) {
	            cout << -1 << endl;
	            exit(0);
	        }
	        int ptr = 1;
	        for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	            if (!candown[memchi[i].dest])
	                continue;
	            tmp[ptr] = memchi[i].dest;
	            ptr++;
	        }
	        ptr--;
	        if (cnt == 1) {
	            for (register int i = 2; i <= ptr; i++) {
	                if (dp[tmp[i]] != dp[tmp[1]]) {
	                    cout << -1 << endl;
	                    exit(0);
	                }
	            }
	            for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	                if (!candown[memchi[i].dest]) {
	                    dpup[memchi[i].dest] = dp[tmp[1]] * 233 + _p(ptr);
	                    efs(memchi[i].dest, pt);
	                    return;
	                }
	            }
	        }
	        int lst = -1;
	        for (register int i = 2; i <= ptr; i++) {
	            if (dp[tmp[i]] != dp[tmp[1]]) {
	                lst = i;
	                break;
	            }
	        }
	        if (lst == -1) {
	            pair me = dp[tmp[1]];
	            for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	                dpup[memchi[i].dest] = me * 233 + _p(ptr - 1);
	                efs(memchi[i].dest, pt);
	            }
	            return;
	        }
	        int cnt1 = 0, cnt2 = 0;
	        for (register int i = 1; i <= ptr; i++) {
	            if (dp[tmp[i]] != dp[tmp[1]] && dp[tmp[i]] != dp[tmp[lst]]) {
	                cout << -1 << endl;
	                exit(0);
	            }
	            if (dp[tmp[i]] == dp[tmp[1]])
	                cnt1++;
	            if (dp[tmp[i]] == dp[tmp[lst]])
	                cnt2++;
	        }
	        if (cnt1 > 1 && cnt2 > 1) {
	            cout << -1 << endl;
	            exit(0);
	        }
	        if (cnt1 == 1 && cnt2 == 1) {
	            dpup[tmp[1]] = dp[tmp[lst]] * 233 + _p(1);
	            dpup[tmp[lst]] = dp[tmp[1]] * 233 + _p(1);
	            int a = tmp[1], b = tmp[lst];
	            efs(a, pt);
	            efs(b, pt);
	            return;
	        }
	        if (cnt1 == 1) {
	            dpup[tmp[1]] = dp[tmp[lst]] * 233 + _p(cnt2);
	            efs(tmp[1], pt);
	            return;
	        }
	        dpup[tmp[lst]] = dp[tmp[1]] * 233 + _p(cnt1);
	        efs(tmp[lst], pt);
	        return;
	    }
	    int cnt = 0;
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        cnt += (!candown[memchi[i].dest]);
	    }
	    if (cnt >= 2) {
	        cout << -1 << endl;
	        exit(0);
	    }
	    int ptr = 1;
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba || !candown[memchi[i].dest])
	            continue;
	        tmp[ptr] = memchi[i].dest;
	        ptr++;
	    }
	    ptr--;
	    if (ptr == 0 && cnt == 0) {
	        cout << pt << endl;
	        exit(0);
	    }
	    if (cnt == 1) {
	        for (register int i = 1; i <= ptr; i++) {
	            if (dp[tmp[i]] != dpup[pt]) {
	                cout << -1 << endl;
	                exit(0);
	            }
	        }
	        for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	            if (memchi[i].dest == baba || candown[memchi[i].dest])
	                continue;
	            dpup[memchi[i].dest] = dpup[pt] * 233 + _p(ptr + 1);
	            efs(memchi[i].dest, pt);
	            return;
	        }
	    }
	    int lst = -1;
	    for (register int i = 1; i <= ptr; i++) {
	        if (dp[tmp[i]] != dpup[pt]) {
	            lst = i;
	            break;
	        }
	    }
	    if (lst == -1) {
	        cout << pt << endl;
	        exit(0);
	    }
	    int cnt2 = 0;
	    for (register int i = 1; i <= ptr; i++) {
	        if (dp[tmp[i]] != dpup[pt] && dp[tmp[i]] != dp[tmp[lst]]) {
	            cout << -1 << endl;
	            exit(0);
	        }
	        if (dp[tmp[i]] == dp[tmp[lst]])
	            cnt2++;
	    }
	    if (cnt2 != 1) {
	        cout << -1 << endl;
	        exit(0);
	    }
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        if (dp[memchi[i].dest] != dpup[pt]) {
	            dpup[memchi[i].dest] = dpup[pt] * 233 + _p(ptr);
	            efs(memchi[i].dest, pt);
	            return;
	        }
	    }
	}
	void ywymain() {
	    n = get();
	    for (register int i = 1; i < n; i++) {
	        int s = get(), t = get();
	        add(s, t);
	        add(t, s);
	    }
	    if (n <= 2) {
	        cout << 1 << endl;
	        return;
	    }
	    int rt = 0;
	    for (register int i = 1; i <= n; i++) {
	        if (deg[i] > 1) {
	            rt = i;
	            break;
	        }
	    }
	    dfs(rt, 0);
	    if (candown[rt]) {
	        cout << rt << endl;
	        return;
	    }
	    efs(rt, 0);
	    cout << -1 << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：xiazha (赞：1)

妙妙神仙题，可爱 qwq

性质一：若一个度数大于 $2$ 的点 $x$ 符合题目要求，则它必定是树的重心。

于是考虑先求出这棵树的重心 $rt$，先暴力 $O(n \log n)$ 判断它是否符合条件。

性质二：若度数为 $1$ 的点 $l$ 符合题目要求，则从 $l$ 出发向下走，直到途中出现分叉的点 $r$，那么 $l$ 至 $r$ 这条链一定有一个点是重心 $rt$。

所以考虑枚举 $rt$ 的孩子的子树，若有一棵孩子的子树是一条链，那么将链尾取出，判断它是否符合条件即可。

这样会被菊花图卡到 $O(n^2\log n)$，怎么办呢？

性质三：注意到同样长度的链是只需要判断一次的，又发现当不同长度的链个数大于 $2$ 时，必定无法满足条件。

将性质三的东西判掉即可。

时间复杂度 $O(n\log n)$，当然，暴力判断其实可以做到 $O(n)$，~~但是我懒了所以直接把距离排序了~~。


```
#include<bits/stdc++.h>
using namespace std;
int n,maxn[100001],minn=1e9,in[100001],siz[100001],deg[100001],cnt,rt,flag,vis[100001],len,ed,kk;
vector<int> g[100001];
struct node
{
	int id,deg;
}d[100001];
bool cmp(node a,node b){return a.deg<b.deg;}
void dfs(int x,int fa)
{
	siz[x]=1;
	for(int y:g[x])
		if(y!=fa)
		{
			dfs(y,x);
			siz[x]+=siz[y];
			maxn[x]=max(maxn[x],siz[y]);
		}
	maxn[x]=max(maxn[x],n-siz[x]);
	if(maxn[x]<minn) minn=maxn[x],rt=x;
}
void dfs1(int x,int fa)
{
	deg[x]=deg[fa]+1;d[++cnt]={x,deg[x]};
	for(int y:g[x])
		if(y!=fa) dfs1(y,x);
}
void check(int i)
{
	cnt=flag=0;dfs1(i,0);
	sort(d+1,d+n+1,cmp);
	for(int j=2;j<=n;j++)
		if(d[j-1].deg==d[j].deg&&in[d[j-1].id]!=in[d[j].id])
		{
			flag=1;
			break;
		}
	if(!flag){cout<<i;exit(0);}
}
void dfs2(int x,int fa)
{
	if(g[x].size()>=3){len=-1;return;}
	len++;ed=x;
	for(int y:g[x])
		if(y!=fa) dfs2(y,x);
}
signed main()
{
	cin>>n;deg[0]=-1;
	if(n==1){puts("1");return 0;}
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
		in[v]++;in[u]++;
	}
	dfs(1,0);
	check(rt);
	for(int i:g[rt])
	{
		if(kk==2) break;
		len=ed=0;dfs2(i,rt);
		if(len!=-1&&!vis[len])
		{
			check(ed);
			kk++;vis[len]=1;
		}
	}
	puts("-1"); 
	return 0;
}
```

---

## 作者：p_b_p_b (赞：1)

[$$\large \color{purple}My\; Blog$$](https://www.cnblogs.com/p-b-p-b/p/11080024.html)

中考考完之后第一个AC，纪念一下qwq

## 思路

简单理解一下题之后就可以发现其实就是要求一个点，使得把它提为根之后整棵树显得非常对称。

很容易想到树哈希来判结构是否相同，而且由于只有完全对称的时候才有用，所以比普通哈希还简单一些……

吗？

你需要求出子树哈希值、祖先哈希值，还要记下来这个点下面是否都相等，还是会有一个捣乱的，还是整个都是乱的。

然后还要特判一个儿子、两个儿子、没有儿子……

于是开开心心地150行了，删掉缺省源之后大概100行。

emmm说的好像不是很清晰，那再说一遍吧。

提为根之后一定是先一段度数为1的点，然后开始分叉，其中每一层的分叉数相同。

如果一个点的儿子的子树全都一样且合法，那就非常好。（~~非常好是什么鬼啊~~）

如果有一个特立独行的儿子，那么根肯定在那里面，要把这个儿子给记下来。

如果有两个以上的不一样的或是不合法的，那么就算是废了。

注意还要换根DP一下搞出一个点上方的哈希值，因为提为根之后上面的就变成了一棵子树了。

注意还要各种特判……

## 代码

哈希值-1表示不合法，$dn,up$表示整棵子树/上方，$W$表示比较普通的儿子的哈希值，$son1$表示记录那个特立独行的儿子。

**感谢@litble神仙指出错误，已经改正。**

```cpp
#include<bits/stdc++.h>
clock_t t=clock();
namespace my_std{
    using namespace std;
    #define pli pair<ll,int>
    #define fir first
    #define sec second
    #define MP make_pair
    #define rep(i,x,y) for (int i=(x);i<=(y);i++)
    #define drep(i,x,y) for (int i=(x);i>=(y);i--)
    #define go(x) for (int i=head[x];i;i=edge[i].nxt)
    #define templ template<typename T>
    #define sz 101010
    #define mod 998244353ll
    typedef long long ll;
    typedef double db;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
    templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
    templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
    templ inline void read(T& t)
    {
        t=0;char f=0,ch=getchar();double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
        if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
        t=(f?-t:t);
    }
    template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
    char __sr[1<<21],__z[20];int __C=-1,__zz=0;
    inline void Ot(){fwrite(__sr,1,__C+1,stdout),__C=-1;}
    inline void print(register int x)
    {
        if(__C>1<<20)Ot();if(x<0)__sr[++__C]='-',x=-x;
        while(__z[++__zz]=x%10+48,x/=10);
        while(__sr[++__C]=__z[__zz],--__zz);__sr[++__C]='\n';
    }
    void file()
    {
        #ifdef NTFOrz
        freopen("a.in","r",stdin);
        #endif
    }
    inline void chktime()
    {
        #ifndef ONLINE_JUDGE
        cout<<(clock()-t)/1000.0<<'\n';
        #endif
    }
    #ifdef mod
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
    ll inv(ll x){return ksm(x,mod-2);}
    #else
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
    #endif
//  inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n;
struct hh{int t,nxt;}edge[sz<<1];
int head[sz],ecnt;
void make_edge(int f,int t)
{
    edge[++ecnt]=(hh){t,head[f]};
    head[f]=ecnt;
    edge[++ecnt]=(hh){f,head[t]};
    head[t]=ecnt;
}

ll dn[sz],up[sz];
int son1[sz];
ll W[sz];
int son[sz];
#define v edge[i].t
void dfs1(int x,int fa)
{
    int cnt=0;
    vector<pli>V;int cc=0,s=0;
    go(x) if (v!=fa)
    {
        dfs1(v,x);++cnt;
        if (dn[v]!=-1) V.push_back(MP(dn[v],v));
        else ++cc,s=v;
    }
    if (cnt==0) return (void)(dn[x]=0,W[x]=son1[x]=-1);
    sort(V.begin(),V.end());
    son[x]=cnt;
    if (cc) dn[x]=-1,son1[x]=s;
    if (cc>1) return (void)(son1[x]=W[x]=-1);
    if (cnt==1)
    {
        if (cc) W[x]=-1;
        else dn[x]=(V[0].fir*sz%mod+1)%mod,W[x]=V[0].fir,son1[x]=-1;
        return;
    }
    if (cc) 
    {
        if (V[0].fir==V[cnt-2].fir) W[x]=V[0].fir;
        else W[x]=-1;
        return;
    }
    if (V[0].fir==V[cnt-1].fir) dn[x]=((W[x]=V[0].fir)*sz%mod+cnt)%mod,son1[x]=-1;
    else if (V[0].fir==V[cnt-2].fir) dn[x]=-1,W[x]=V[0].fir,son1[x]=V[cnt-1].sec;
    else if (V[1].fir==V[cnt-1].fir) dn[x]=-1,W[x]=V[1].fir,son1[x]=V[0].sec;
    else dn[x]=W[x]=son1[x]=-1;
}
void dfs2(int x,int fa)
{
    go(x) if (v!=fa)
    {
        if (son[x]==1)
        {
            if (x==1) up[v]=0;
            else if (up[x]==-1) up[v]=-1;
            else up[v]=(up[x]*sz%mod+1)%mod;
        }
        else if (dn[x]!=-1||son1[x]==v)
        {
            if (x==1) up[v]=(W[x]*sz%mod+son[x]-1)%mod;
            else if (up[x]==W[x]&&up[x]!=-1) up[v]=(W[x]*sz%mod+son[x])%mod;
            else up[v]=-1;
        }
        else if (son[x]==2&&son1[x]!=-1)
        {
            ll w=dn[son1[x]];
            if (w==-1) up[v]=-1;
            else if (x==1) up[v]=(w*sz%mod+1)%mod;
            else if (w==up[x]) up[v]=(w*sz%mod+2)%mod;
            else up[v]=-1;
        }
        else up[v]=-1;
        dfs2(v,x);
    }
}

int main()
{
    file();
    read(n);
    if (n<=3) return puts("1"),0; 
    int x,y;
    rep(i,1,n-1) read(x,y),make_edge(x,y);
    dfs1(1,0);
    rep(i,1,n) up[i]=-1;
    dfs2(1,0);
    if (dn[1]!=-1) return puts("1"),0;
    rep(i,2,n) if (up[i]==W[i]&&dn[i]!=-1&&son[i]) return printf("%d",i),0;
    rep(i,2,n) if (!son[i]&&up[i]!=-1) return printf("%d",i),0;
    puts("-1");
    return 0;
}
```

---

