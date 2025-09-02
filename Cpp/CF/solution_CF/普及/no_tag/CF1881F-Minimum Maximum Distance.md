# Minimum Maximum Distance

## 题目描述

一棵树有 $n$ 个点，其中有一些节点被打了标记。保证树是联通且无环的。

定义 $ f_i $ 为第 $ i $ 个节点到所有被标记节点距离的最大值。

你的任务是找出所有点的 $ f_i $ 的最小值。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1881F/d0163dde57a696d8d96936900f0fefe6ef32a7ae.png)
 
举个例子，一棵树如上图所示，被标记节点为 $ 2 $ , $ 6 $ , $ 7 $。 因此 $ f(i) = [2, 3, 2, 4, 4, 3, 3] $。$ f_i $  最小的为 $ 1 $ 和 $ 3 $ 节点，且最小值为 $2$。

## 样例 #1

### 输入

```
6
7 3
2 6 7
1 2
1 3
2 4
2 5
3 6
3 7
4 4
1 2 3 4
1 2
2 3
3 4
5 1
1
1 2
1 3
1 4
1 5
5 2
4 5
1 2
2 3
1 4
4 5
10 8
1 2 3 4 5 8 9 10
2 10
10 5
5 3
3 1
1 7
7 4
4 9
8 9
6 1
10 9
1 2 4 5 6 7 8 9 10
1 3
3 9
9 4
4 10
10 6
6 7
7 2
2 5
5 8```

### 输出

```
2
2
0
1
4
5```

## 样例 #2

### 输入

```
3
6 1
3
1 2
1 3
3 4
3 5
2 6
5 3
1 2 5
1 2
1 3
2 4
3 5
7 1
2
3 2
2 6
6 1
5 6
7 6
4 5```

### 输出

```
0
2
0```

# 题解

## 作者：_299817_ (赞：10)

## Part 0：前言
赛时想出了 F 但是没有想出 E，鉴定为：对动态规划一窍不通。
## Part 1：主要思路
我们先来手模题面中给的样例。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1881F/d0163dde57a696d8d96936900f0fefe6ef32a7ae.png)

不难发现一件事情，我们这里最后的答案所在的点是 $1$ 和 $3$ 号点。

我们有没有发现一个性质：就是这两个点都是红点间的路径上的，而且最后的答案就是最长的红点间的距离的长度除以二上取整。

那么，我们怎么找到最长的红点间的距离呢？

很显然，$O(n^2)$ 枚举两个点然后求距离是会超时的。

这里有一个比较奇妙的算法，就是先钦定一个红点为根节点，然后不停地删除每一条边上的叶子节点，直到这个叶子节点为红点位置就停止在这一条树枝上的操作。

接着，我们删完点后，求出整棵树的直径，也就是红点间的最长距离。

具体为什么呢？

因为很显然，我们删完点后，所有的叶子结点都是红色节点，而直径本身就是从一个叶子节点到另外一个叶子节点，所以这个时候我们求出来的答案救赎对的。

最后我们只需要把直径的长度除以二后向上取整即可。

这里删除节点的复杂度是 $O(n)$ 的，而求直径的两遍 $\operatorname{dfs}$ 也是 $O(n)$ 的，所以最后的复杂度显然就是 $O(n)$ 的。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#define rep(i, l, r) for(int i = signed(l); i <= signed(r); i++)
#define per(i, l, r) for(int i = signed(l); i >= signed(r); i--)
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

struct edge{
    int from, to;
    int nxt;
};

int T;
int n, m;
int is[200010];
int root;
edge e[400010];
int head[400010];
int cnt;
int vis[200010];
int hhead;
int now;

void add(int x, int y){ // 加边函数
    cnt++;
    e[cnt] = {x, y, head[x]};
    head[x] = cnt;
}

void dfs0(int u, int fa){ // 删点函数
    int cnt = 0; // 记录这个点有多少个有效的子节点
    for(int i = head[u]; i != 0; i = e[i].nxt){
        int v = e[i].to;
        if(v == fa){
            continue;
        }
        dfs0(v, u);
        if(vis[v] != 1){ // 如果子节点也被删掉了那么这个子节点就不能算有效的子节点
            cnt++;
        }
    }
    if(cnt == 0 && is[u] == 0){ // 如果这个点的有效的子节点个数为 0 而且这个点不为红点
        vis[u] = 1;
    }
}

void dfs1(int u, int fa, int stp){
    if(stp > now){ // 记得更新答案
        now = stp;
        hhead = u;
    }
    for(int i = head[u]; i != 0; i = e[i].nxt){
        int v = e[i].to;
        if(v == fa || vis[v] == 1){ // 记得判断子节点有没有被删除
            continue;
        }
        dfs1(v, u, stp + 1);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        now = 0, hhead = 0;
        cnt = 0;
        rep(i, 1, n){
            head[i] = 0;
        }
        rep(i, 1, n){
            is[i] = 0;
            vis[i] = 0;
        }
        // 记得初始化
        cin >> n >> m;
        rep(i, 1, m){ // 记录哪些点是红点
            int t;
            cin >> t;
            is[t] = 1;
            root = t;
        }
        rep(i, 1, n - 1){ // 输入，加边
            int x, y;
            cin >> x >> y;
            add(x, y);
            add(y, x);
        }
        dfs0(root, 0); // 删点
        dfs1(root, 0, 0);
        root = hhead;
        now = 0;
        dfs1(root, 0, 0); // 两遍 dfs 求直径
        cout << ceil(now / 2.0) << endl; // 输出答案
    }
    return 0;
}
```

---

## 作者：iiiiiyang (赞：5)

[逆天的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17761038.html)

[题目链接](https://www.luogu.com.cn/problem/CF1881F)

先钦定一个根跑出所有点的深度，这样就得到了钦定的根到所有关键点的距离最大值。换根的过程考虑对于一条边 $u \to v$，$v$ 子树内的点深度会减一，子树外的点深度会加一。拍到 dfs 序上就变成了区间加减一，求全局最大值，可以线段树维护。对于标记点的限制，建线段树的时候将标记点权值设为 $dep$，其余都设为 -INF 即可。简单更改线段树维护的内容，就可以做[更强的东西](https://www.luogu.com.cn/problem/CF337D)。这样复杂度是 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmax(T &a,T b,Args... args) {a=max({a,b,args...});}
    TA inline void cmin(T &a,T b,Args... args) {a=min({a,b,args...});}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=200010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int T,n,m,x,y,ans;
    int dep[MAX],lt[MAX];
    int L[MAX],R[MAX],id[MAX],tot;
    vector<int> G[MAX];
    
    namespace SegmentTree
    {
    	int info[MAX<<2],tag[MAX<<2];
    	inline void pushup(int i) {info[i]=max(info[i<<1],info[i<<1|1]);}
    	inline void down(int i,int k) {tag[i]+=k,info[i]+=k;}
    	inline void pushdown(int i) {if(tag[i]) down(i<<1,tag[i]),down(i<<1|1,tag[i]),tag[i]=0;}
    	inline void build(int i,int l,int r)
    	{
    		info[i]=0,tag[i]=0;
    		if(l==r) return info[i]=lt[id[l]]?dep[id[l]]:-INF,void();
    		int mid=(l+r)>>1;
    		build(i<<1,l,mid),build(i<<1|1,mid+1,r);
    		pushup(i);
		}
    	void modify(int i,int l,int r,int L,int R,int k)
    	{
    		if(r<L||R<l) return;
    		if(l<=L&&R<=r) return down(i,k);
    		pushdown(i); int mid=(L+R)>>1;
    		if(l<=mid) modify(i<<1,l,r,L,mid,k);
    		if(r>mid)  modify(i<<1|1,l,r,mid+1,R,k);
    		pushup(i);
		}
		inline void modify(int l,int r,int k) {modify(1,l,r,1,n,k);}
	}
	using namespace SegmentTree;
    
    inline void lmy_forever()
    {
    	read(T);
    	while(T--)
    	{
    		read(n,m),ans=INF,tot=0,dep[0]=-1;
    		for(int i=1;i<=n;++i) G[i].clear(),lt[i]=L[i]=R[i]=id[i]=dep[i]=0;
    		for(int i=1;i<=m;++i) lt[read()]=1;
    		for(int i=1;i<n;++i)  read(x,y),G[x].eb(y),G[y].eb(x);
    		
    		auto dfs1=[&](auto dfs1,int now,int father)->void
    		{
    			L[now]=++tot,id[tot]=now,dep[now]=dep[father]+1;
    			for(auto to:G[now]) if(to!=father) dfs1(dfs1,to,now);
    			R[now]=tot;
			}; dfs1(dfs1,1,0);
			
			build(1,1,n);
			
			auto dfs2=[&](auto dfs2,int now,int father)->void
			{
				cmin(ans,info[1]);
				for(auto to:G[now]) if(to!=father)
				{
					modify(1,L[to]-1,1),modify(R[to]+1,n,1),modify(L[to],R[to],-1);
					dfs2(dfs2,to,now);
					modify(1,L[to]-1,-1),modify(R[to]+1,n,-1),modify(L[to],R[to],1);
				}
			}; dfs2(dfs2,1,0);
			
    		write(ans,'\n');
    	}
	}
}

bool Med;

signed main()
{
    //file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：LHLeisus (赞：4)

[原题链接](https://codeforces.com/contest/1881/problem/F)

[更好的阅读体验](https://www.cnblogs.com/LHLeisus/p/17763332.html)


这题可以换根 dp，可以 dfs 序加线段树，但是还以一种更简便的做法，直接求两端都是标记点的最长路径就可以了。若路径长度是 $L$，则答案是 $\left\lceil\frac{L}{2}\right\rceil$。具体做法就是和求直径一样，两次 dfs 即可。

- 至于为什么，其实很简单。设这条路径两个端点分别为 $u,v$。考虑不在这条路径上的点 $i$，$f_i$ 一定是先到路径上的某一点 $x$ 的距离，再加上 $f_x$，一定不会更优。
- 接着考虑在路径上的点 $x$。如果 $x$ 距离 $u$ 更近，那么 $f_x=dist_{x,v}$。反之亦然。显然只有取路径中点的时候最优，此时路径被分成两半，但 $L$ 不一定是偶数，并且 $f_x$ 应取最大值，所以要记得上取整。故最后答案为 $\left\lceil\frac{L}{2}\right\rceil$。
- 最后别忘了特判只有一个标记点的情况，答案应为 $0$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<utility>
#include<vector>
#include<queue>
#include<bitset>
#include<map>
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
inline int read();
typedef long long ll;
typedef double db;
const int N=2e5+5;
const int INF=0x3f3f3f3f;
int n,m,k;
int mark[N];
struct E{
	int to,nex;
}edge[N<<1];
int head[N],cnt=0;
void add(int u,int v){
	edge[++cnt]=(E){v,head[u]};
	head[u]=cnt;
}
int c,L=0;
int dist[N];
void dfs(int u,int fa){
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		if(v==fa) continue;
		dist[v]=dist[u]+1;
		dfs(v,u);
		if(mark[v]&&dist[v]>dist[c]) c=v;
	}
}
int main()
{
	int T=read();
	while(T--){
		n=read(),k=read();
		memset(mark,0,sizeof mark);
		memset(head,0,sizeof head);
		memset(dist,0,sizeof dist);
		cnt=0;
		FOR(i,1,k)
			mark[read()]=1;
		FOR(i,1,n-1){
			int u=read(),v=read();
			add(u,v);add(v,u);
		}
		if(k==1){
			puts("0");
			continue;
		}
		FOR(i,1,n){
			if(mark[i]){
				dist[i]=0;
				L=0;
				c=0;
				dfs(i,0);
				break;
			}
		}
		dist[c]=0;
		dfs(c,0);
		L=dist[c];
		printf("%d\n",(L+1)/2);
	}
	return 0;
}


inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}
```


---

## 作者：shinzanmono (赞：3)

看到题目，可以发现比较像 dp。

设 $f_u$ 表示 $u$ 到 $u$ 子树里的关键点的距离最大值，$g_u$ 表示 $u$ 到 $u$ 子树外的关键的的距离最大值。

可以得出状态转移方程。

$$
f_u=\left\{
\begin{aligned}
\max(0,\max_{v\in son_u}f_v+1)&\ \ \ \ \text{u is a key point}\\
\max_{v\in son_u}f_v+1 &\ \ \ \ \text{otherwise}
\end{aligned}
\right.
$$

$$
g_u=\left\{
\begin{aligned}
\max(0,g_{fa_u}+1,\max_{v\in brother_u}f_v+2)&\ \ \ \ \text{u is a key point}\\
\max(g_{fa_u}+1,\max_{v\in brother_u}f_v+2) &\ \ \ \ \text{otherwise}
\end{aligned}
\right.
$$

然后根据换根 dp 老套路，记录每个点的兄弟节点，跑两边 DFS 即可，时间复杂度 $O(n)$。

---

## 作者：wangyishan (赞：3)

# CF1881F 题解

[题面Link](https://www.luogu.com.cn/problem/CF1881F)

我们发现有一个性质——记最远两个标记点的距离为 $d$，答案一定为 $\lceil \frac{d}{2} \rceil$。

找到 $d$ 可以参考求树的直径的方法，两遍 `DFS` 即可。时间复杂度 $O(n)$

特别的，当树上只有一个标记点时，答案为 $0$。

[Code](https://codeforces.com/contest/1881/submission/228996622):
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200050], vis[200050];
vector<int> e[200050];
int T, n, k;
int read() {
  int w = 1, kk = 0;
  char c = getchar();
  while (!(c >= '0' && c <= '9'))
    c = getchar();
  while (c >= '0' && c <= '9') {
    kk = kk * 10 + c - '0';
    c = getchar();
  }
  return w * kk;
}
int f[200050], d[200050];
void dfs1(int x, int fa) {
  if (fa != -1)
    f[x] = f[fa] + 1;
  for (auto i : e[x]) {
    if (i == fa)
      continue;
    dfs1(i, x);
  }
}
void dfs2(int x, int fa) {
  if (fa != -1)
    d[x] = d[fa] + 1;
  for (auto i : e[x]) {
    if (i == fa)
      continue;
    dfs2(i, x);
  }
}
int main() {
 // freopen("1.out", "w", stdout);
  T = read();
  while (T--) {
    n = read();
    k = read();
    for (int i = 1; i <= n; i++)
      e[i].clear(), d[i] = f[i] = a[i] = 0;
    for (int i = 1; i <= k; i++)
      a[i] = read();

    for (int i = 1; i <= n - 1; i++) {
      int u, v;
      u = read(), v = read();
      e[u].push_back(v);
      e[v].push_back(u);
    }
    if (k == 1) {
      cout << 0 << endl;
      continue;
    }
    f[0] = -1, d[0] = -1;
    dfs1(1, -1);
    int ans = a[1];
    for (int i = 1; i <= k; i++) {
      if (f[a[i]] > f[ans]) {
        ans = a[i];
      }
    }
    dfs2(ans, -1);
    ans = a[1];
    for (int i = 1; i <= k; i++) {
      //  cout << i << " ";
      if (d[a[i]] > d[ans]) {
        ans = a[i];
      }
    }
    //    for (int i = 1; i <= n; i++) {
    //      cout << d[i] << " ";
    //    }
    cout << (d[ans] + 1) / 2 << endl;
  }
  return 0;
}
```

---

## 作者：AtCo (赞：1)

[题目传送门](https://codeforces.com/contest/1881/problem/F)

## 题意

给你一个 $n$ 个节点的树， 树上有 $k$ 个节点被标记了

函数 $f(i)$ 表示第 $i$ 个点到距离 $i$ 最远的标记 $j$ 的距离

求最小的 $f(i)$ 是多少

## 思路

找到最远的 $2$ 个标记 $i$ , $j$ 之间的距离 $dis$ 的中点

## 做法

DFS

先找到距离原点最远的被标记的点 $i$

然后找到距离 $i$ 最远的被标记的点的距离

向上取整除以 $2$

结束

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e6 + 5;
int n, k, biaoji[maxn], mx = -1, mxid;
vector <int> e[maxn];
void dfs(int now, int lst, int dis) {
	if (biaoji[now] && dis > mx) {mx = max(mx, dis), mxid = now;}
	for (auto nxt : e[now]) if (nxt != lst) dfs(nxt, now, dis + 1);
	return ;
}
void solve() {
	cin >> n >> k; mx = -1;
	for (int i = 1; i <= n; i++) biaoji[i] = false, e[i].clear();
	for (int i = 1; i <= k; i++) {int x; cin >> x; biaoji[x] = true;}
	for (int i = 1; i < n; i++) {int u, v; cin >> u >> v; e[u].push_back(v), e[v].push_back(u);}
	dfs(1, -1, 0);
	mx = 0;
	dfs(mxid, -1, 0);
	cout << (mx + 1) / 2 << endl;
}
int main() {
	int t; cin >> t;
	while (t--) solve();
}
```

---

## 作者：Jason_Harry_Song (赞：0)

# 题解：CF1881F Minimum Maximum Distance

结论：若令由 $d$ 为两端都是被标记点的最长路径的长度，则答案为 $\lceil\frac{d}{2}\rceil$。选择的点自然是这条路径的中点。

实现很简单，类似于找直径那样跑两遍 dfs 就 OK 了，难点在于证明。

令“最长路径”的两个端点为 $u$ 和 $v$，选择的点——“最长路径”的中点为 $x$，$dis(a,b)$ 表示 $a$ 与 $b$ 的距离。

若存在一个点 $w$ 使得 $dis(x,w)>dis(x,u)$ 且 $dis(x,w)>dis(x,v)$，那么 $dis(u,w)$ 与 $dis(v,w)$ 中必有一个大于 $dis(u,v)$，与 $u$ 和 $v$ 是“最长路径”的两个段点矛盾。这样一来就能证明在选择点 $x$ 的情况下答案一定是 $\lceil\frac{d}{2}\rceil$。

继续考虑：如果不选择点 $x$，而选择点 $y$。由于 $x$ 为“最长路径中点”，$\max(dis(u,y),dis(v,y))$ 一定不比 $\max(dis(u,x),dis(v,x))$ 来的小。因此选择 $x$ 一定最优。

综上，选择 $x$ 一定最优并且当选择 $x$ 时答案为 $\lceil\frac{d}{2}\rceil$。

证明完毕，奉上代码！

```cpp
#include <bits/stdc++.h>
#define N 200000
#define K N
using namespace std;
int t, n, k, a[K + 1], u, v;
vector<int> edge[N + 1];
int d[N + 1];
void dfs(int node);
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= k; i++) {
			scanf("%d", &a[i]);
		}
		for (int i = 1; i <= n; i++) {
			edge[i].clear();
		}
		for (int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		for (int i = 1; i <= n; i++) {
			d[i] = -1;
		}
		d[a[1]] = 0;
		dfs(a[1]);
		int id = 1;
		for (int i = 2; i <= k; i++) {
			if (d[a[i]] > d[a[id]]) {
				id = i;
			}
		}
		for (int i = 1; i <= n; i++) {
			d[i] = -1;
		}
		d[a[id]] = 0;
		dfs(a[id]);
		int mx = 0;
		for (int i = 1; i <= k; i++) {
			mx = max(mx, d[a[i]]);
		}
		printf("%d\n", (mx + 1) / 2);
	}
	return 0;
}
void dfs(int node) {
	for (int i : edge[node]) {
		if (d[i] == -1) {
			d[i] = d[node] + 1;
			dfs(i);
		}
	}
	return;
}
```

---

## 作者：jr_inf (赞：0)

因为白点对 $f_i$ 没有贡献，所以可以重构出一棵原树的子树，使得所有的叶子都为标记点且标记点数量不变（没有删去标记点）。因为没有标记被删去且结构不变，所以这棵树的答案与原树答案相同。

现在，对于所有节点，到它距离最大的标记点一定在叶子上。那么问题就变为：求出树上任意一点到所有叶子节点的最大距离的最小值。显然，这个点一定在直径上，否则可以通过把点调整到直径上来减小答案。令此时的树的直径为 $l$，那么答案就是 $\lceil \frac{l}{2} \rceil$。时间复杂度 $O(n)$。

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

在一棵有 $n$ 个节点的树上有 $k$ 个节点被标记。定义 $f_x$ 为树上距离 $x$ 最远的被标记的点与 $x$ 的距离，求最小的 $f_x$。

## 题目分析

纯暴力想法就可以了。每个点只需要知道自己子树内深度最大的，祖先里深度最小的，以及对于每个祖先，非当前点所在子树内深度最大的，第一个直接预处理，后两个在 dfs 中维护即可。复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L xd[x].l
#define R xd[x].r
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const signed N =2e5+5,M=1e6+5,inf=(1LL<<31)-1;
using namespace std;
int T=read(),n,a[N],k,h[N],to[N<<1],nxt[N<<1],cnt;
bool sig[N];
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
int dep[N],mx[N];
inline void dfs(int x,int fa){
	dep[x]=dep[fa]+1;
	mx[x]=-inf;
	if(sig[x])mx[x]=dep[x];
	e(x)if(y^fa)dfs(y,x),mx[x]=max(mx[x],mx[y]);
}
int mxk[N],ans;//disx=dep[x]+k[x]
inline void Dfs(int x,int fa,int mindp){
	int mxnow=-inf;
	if(sig[x])mindp=min(mindp,dep[x]);
	ans=min(ans,max({mx[x]-dep[x],dep[x]+mxk[x],dep[x]-mindp}));
	vector<int>s;
	e(x)if(y^fa){
		s.pb(y),mxk[y]=max(mxk[y],mxnow);
		mxnow=max(mxnow,mx[y]-dep[x]*2);
	}
	int siz=s.size();
	mxnow=-inf;
	per(i,siz-1,0){
		int y=s[i];
		mxk[y]=max({mxk[y],mxk[x],mxnow});
		mxnow=max(mxnow,mx[y]-dep[x]*2);
		Dfs(y,x,mindp);
	}
}
signed main(){
	while(T--){
		n=read(),k=read();
		rep(i,1,n)h[i]=sig[i]=0,mxk[i]=-inf;
		cnt=0;
		rep(i,1,k)sig[read()]=1;
		for(int i=1,x,y;i^n;i++)x=read(),y=read(),add(x,y),add(y,x);
		ans=inf;
		dfs(1,0),Dfs(1,0,inf);
		pf(ans),putchar('\n');
	}
	return 0;
}
```


---

## 作者：2020kanade (赞：0)

来一个复杂化原问题的逆（N）天（T）写法。

我们给树定一个根，那么一定有一颗最小子树包含所有的红点，实际上也是包含所有红点的虚树根的子树。

考虑这颗子树外的点，到它的距离一定是到这个点的距离加上这个点到离它最近的红点的距离。

这颗子树内的点就不太好整了，因为某个子树内的点的子树外的红点也会参与贡献，考虑直接换根 DP 求出该部分。

设 $f_u$ 为答案，$g_u$ 为结点 $u$ 子树外红点最近距离，预处理每颗子树最远距离与去掉最远距离贡献子树后的最远距离，具体细节参考 code，不难。

虚树根考虑直接求 $k$ 次 LCA。

时间复杂度 $\Theta((n+k)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=200011;
struct edge
{
	int t,nt;
}G[N];int h[N<<1],ct;
inline void add_edge(int u,int v)
{
	G[++ct]={v,h[u]};h[u]=ct;
}
int anc[N<<1][20];
int d[N],mi[N],se[N],f[N],sz[N],dfn[N],hs[N],dfc;bool bk[N];
inline void dfsa(int u,int f,int dep)
{
	anc[u][0]=f,d[u]=dep,dfn[u]=++dfc,sz[u]=1;
	for(int i=1;i<=19;++i)
	{
		anc[u][i]=anc[anc[u][i-1]][i-1];
		//ancmi[u][i]=min(ancmi[u][i-1],ancmi[anc[u][i-1]][i-1]);
	}
	for(int i=h[u];i;i=G[i].nt) if(G[i].t^f)
	{
		//dis[G[i].t]=dis[u]+G[i].val,//ancmi[G[i].t][0]=G[i].val;
		dfsa(G[i].t,u,dep+1);sz[u]+=sz[G[i].t];
	}
}
inline int lca(int u,int v)
{
	if(d[u]<d[v]) swap(u,v);
	for(int i=19;i>=0;--i) if(d[u]-(1<<i)>=d[v])
	{
    	u=anc[u][i];
    }
 	if(u==v)return u;
 	for(int i=19;i>=0;--i) if(anc[u][i]^anc[v][i])
    {
   		u=anc[u][i],v=anc[v][i];
  	}
 	return anc[u][0];
}
int dis(int u,int v)
{
	return d[u]+d[v]-2*d[lca(u,v)];
}
void dfsb(int u,int f)
{
	if(bk[u]) mi[u]=se[u]=0;
	else mi[u]=se[u]=-INT_MAX/2;
	for(int i=h[u];i;i=G[i].nt)
	{
		int v=G[i].t;if(v==f) continue;
		dfsb(v,u);
		if(mi[v]+1>mi[u]) mi[u]=mi[v]+1,hs[u]=v; 
	}
	for(int i=h[u];i;i=G[i].nt)
	{
		int v=G[i].t;if(v==f) continue;
		if(v==hs[u]) continue;
		if(mi[v]+1>se[u]) se[u]=mi[v]+1; 
	}
}
int dpmin[N];
void dfsc(int u,int fa,int mxs)
{
	dpmin[u]=mxs;
	f[u]=max(mxs,mi[u]);
	for(int i=h[u];i;i=G[i].nt)
	{
		int v=G[i].t;if(v==fa) continue;
		dfsc(v,u,max(v==hs[u]?se[u]:mi[u],mxs)+1);	
	}	
}
int n,m,k,t,rt;vector<int> bks;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=k;++i) cin>>m,bk[m]=1,bks.push_back(m);
		for(int i=1;i<n;++i)
		{	
			int u,v;cin>>u>>v;
			add_edge(u,v),add_edge(v,u);
		}
		dfsa(1,0,0);rt=0;
		for(auto x:bks) rt=rt?lca(rt,x):x;
		dfsb(rt,anc[rt][0]);
		dfsc(rt,anc[rt][0],-INT_MAX/2);
		ll ans=LLONG_MAX;
		//cout<<rt<<endl;
		//for(int i=1;i<=n;++i) cout<<i<<":"<<dfn[i]<<" "<<f[i]<<" "<<mi[i]<<" "<<se[i]<<" "<<hs[i]<<" "<<dpmin[i]<<endl;
		//cout<<mi[4]<<" "<<se[4]<<" "<<hs[4]<<endl;
		for(int i=1;i<=n;++i)
		{
			if(dfn[i]<dfn[rt]+sz[rt]&&dfn[rt]<=dfn[i]) ans=min(ans,1ll*f[i])/*,cout<<"A\n"*/;
			else ans=min(ans,1ll*dis(i,rt)+f[rt])/*,cout<<"B\n"*/;
		}
		cout<<ans<<endl;
		for(int i=1;i<=n;++i)
		{
			for(int j=0;j<=19;++j) anc[i][j]=0;
			h[i]=f[i]=0;d[i]=mi[i]=se[i]=hs[i]=0;
			bk[i]=0;
		}
		dfc=ct=0;bks.clear();
	}
	return 0;
}
/*
1
10 8
1 2 3 4 5 8 9 10
2 10
10 5
5 3
3 1
1 7
7 4
4 9
8 9
6 1
*/
```


---

## 作者：__vector__ (赞：0)

听（我妈）说有人想跟我探讨这题做法，就写这题较为详细题解了。  

先钦定 $1$ 是根节点。  

可以先将每个点的答案分别计算出来最后取最小值。  

为了方便计算，自然能想到分子树内和子树外分别计算，具体地，设 $f_i$ 表示 $i$ 为根的子树内离 $i$ 最远的关键点的距离，设 $g_i$ 表示 $i$ 为根的子树**以外**离 $i$ 最远的关键点的距离。  

$f_i$ 的计算是很简单的树形 dp。  

考虑 $g_i$，有两种转移。设 ${fa}_i$ 表示 $i$ 的父节点，${bro}_i$ 表示 $i$  的兄弟节点。    
- 从父节点继承，即 $g_i = g_{fa_i} + 1$。  
- 从兄弟节点继承，即 $g_i = g_{bro_i} + 2$。   

完结。  

https://codeforces.com/contest/1881/submission/227980730



---

## 作者：ForgotDream_CHN (赞：0)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17761619.html)

> 给定一棵树，树上的一些点被打上了标记，定义一个节点的贡献为其到所有标记节点距离的最大值，求最小贡献。  
> $n \le 2 \times 10^5$。

这道题的原题是 CF337D（甚至要更困难一些）。

很套路的换根 DP 啊。我们考虑设 $f_i$ 为 $i$ 子树内的标记节点到 $i$ 的最大距离，$g_i$ 为子树外到 $i$ 的最大距离。首先，$f$ 的转移是显然的：

$$
f_i = \max_{j \in \operatorname{subtree}(i)} \left\{ f_j + 1 \right\}
$$

直接从子树中转移，取最大值即可。

再来考虑 $g$ 的转移。我们设 $fa_i$ 为 $i$ 的父亲，那么 $i$ 子树外的点可划分为两个部分：$fa_i$ 子树外的点与 $fa_i$ 子树中去掉 $i$ 的子树的部分。其中 $fa_i$ 子树外的点的贡献显然就是 $g_{fa_i} + 1$，而剩余部分的贡献也不难看出是其子树内部的最大距离再加上它与 $i$ 的距离，后者显然为 $2$。

那么可以得到 $g$ 的转移方程：

$$
g_i = \max \left\{ g_{fa_i} + 1, \max_{j \in \operatorname{subtree}(fa_i) \land j \not= i} \left\{ f_j + 2 \right\} \right\}
$$

最后是一些转移方面的问题。对于 $f$ 那没有什么好说的，直接自底向上转移就完事了。对于 $g$，一种朴素的转移方法是直接枚举 $fa_i$ 的所有儿子然后转移，但是这样转移的复杂度是不对的，考虑一个菊花图，那么我们会发现每个点被枚举到的次数为 $\mathcal{O}(n)$ 的，那么总的时间复杂度会变成 $\mathcal{O}(n^2)$，这当然无法接受。一种更聪明的转移方法是在计算 $f$ 时同时记录下每个点 $f$ 最大与次大的儿子，那么在转移 $g$ 时，如果当前点是其父亲的最大的儿子，我们就从次大的儿子转移，否则就从最大的儿子转移，这样转移就是 $\mathcal{O}(1)$ 的了。

当然，这个题的初始化也要小心，要注意特别考虑被标记的点。那么总体的时空复杂度都为 $\mathcal{O}(n)$。

由于比赛没有打，所以代码也没写。不过实现方面也没有什么难度，相信聪明的你一定能写出来的。

---

