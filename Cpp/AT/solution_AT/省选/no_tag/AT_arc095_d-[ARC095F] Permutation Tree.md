# [ARC095F] Permutation Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc095/tasks/arc095_d

高橋くんには $ (1,2,...,n) $ の順列 $ (p_1,p_2,...,p_n) $ を使い、 次の手順で木を作る能力があります。

頂点 $ 1 $、頂点 $ 2 $、 $ ... $、 頂点 $ n $ を用意する。 各 $ i=1,2,...,n $ について次の操作を行う。

- $ p_i\ =\ 1 $ である場合、何もしない。
- $ p_i\ \neq\ 1 $ である場合、$ p_j\ <\ p_i $ であるような $ j $ のうち最大のものを $ j' $ とする。 頂点 $ i $ と 頂点 $ j' $ の間に辺を貼る。

高橋くんはこの能力を使ってお気に入りの木を作ろうとしています。 高橋くんのお気に入りの木は 頂点 $ 1 $ から頂点 $ n $ の $ n $ 頂点からなり、 $ i $ 番目の辺は頂点 $ v_i $ と $ w_i $ を結んでいます。 適切な順列を使うことで、高橋くんのお気に入りの木と同型な木を作ることが可能か 判定して下さい。 可能な場合、そのような順列のうち辞書順で最も小さいものを求めて下さい。

## 说明/提示

### 注意

木が同型であることの定義は[wikipedia](https://ja.wikipedia.org/wiki/%E3%82%B0%E3%83%A9%E3%83%95%E5%90%8C%E5%9E%8B)を参照して下さい。 直感的には、木と木が同型であるとは、頂点の番号を無視すると同じ木になることを言います。

### 制約

- $ 2\ \leq\ n\ \leq\ 10^5 $
- $ 1\ \leq\ v_i,\ w_i\ \leq\ n $
- 与えられるグラフは木である

### Sample Explanation 1

$ (1,\ 2,\ 4,\ 5,\ 3,\ 6) $ という順列を使って木を作ると、次の図のようになります。 !\[\](https://img.atcoder.jp/arc095/db000b879402aed649a1516620eb1e21.png) これは入力のグラフと同型です。

## 样例 #1

### 输入

```
6
1 2
1 3
1 4
1 5
5 6```

### 输出

```
1 2 4 5 3 6```

## 样例 #2

### 输入

```
6
1 2
2 3
3 4
1 5
5 6```

### 输出

```
1 2 3 4 5 6```

## 样例 #3

### 输入

```
15
1 2
1 3
2 4
2 5
3 6
3 7
4 8
4 9
5 10
5 11
6 12
6 13
7 14
7 15```

### 输出

```
-1```

# 题解

## 作者：皎月半洒花 (赞：9)

题意：

> 给定一棵树 $\rm T$, 要求构造一个排列 $p$ .
>
> 对于每一个 $p_i$ ，找到最大的 $j$ 使得 $p_j<p_i$，然后在 $i,j$ 间连边。
>
> 问是否可以构造出与 $\rm T$ 同构的树。
>
> 如果可以，则给出字典序最小的排列。
>
> $n\leq 100,000$

终于可以从 `atcoder` 爬题了QAQ

考虑如果给定一个排列，如何通过这种方式生成一棵树。那肯定是按照权值从小到大枚举每个权值所在的位置，每次在 $\max\_right$ 和枚举的 $i$ 之间连边，并更新 $\max\_right$。

可以发现，由于给定的是排列，局部最大值唯一，那么只会出现「非局部最大值向局部最大值连边」和「上一个版本的局部最大值和当前局部最大值连边」两种连边方式。所以不难看出最后的树的形态就是一个一阶毛毛虫——直径旁边挂着一堆点，每个点与直径的距离均为 $1$ 。所以是否合法求一下直径然后check即可。

考虑如何构造。发现只要求同构，那么肯定是从 $1$ 开始重新编号。对于每个直径上的 $x$，设**与其相连且不在直径上**的点的个数为 $\deg_x$，迄今为止一共有 $s$ 个点已经编完号了，那么只要让 $x=s+\deg_x+1$，剩下的点依次赋值为 $s+1,s+2,s+3\cdots s+\deg_x$ 就完了。可以知道这样一定是最优的方案。

从直径两端分别处理一下取个字典序最小即可。复杂度 $O(n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define to(k) E[k].to
#define next(k) E[k].next

using namespace std ;

const int N = 200010 ;

struct Edge{
    int to, next ;
}E[N * 2] ;
int n ;
int tot ;
int cnt ;
int q[N] ;
int p[N] ;
int d[N] ;
int fa[N] ;
int vis[N] ;
int dep[N] ;
int deg[N] ;
int head[N] ;

void add(int u, int v){
    to(++ cnt) = v, next(cnt) = head[u], head[u] = cnt ;
    to(++ cnt) = u, next(cnt) = head[v], head[v] = cnt ;
}
int dfs(int u, int faa){
    int ret = u, s ;
    fa[u] = faa, dep[u] = dep[faa] + 1 ;
    for (int k = head[u] ; k ; k = next(k)){
        if (to(k) != faa){
            s = dfs(to(k), u) ;
            if (dep[ret] < dep[s]) ret = s ;
        }
    }
    return ret ;
}
int main(){
    cin >> n ;
    int rt1, rt2, num, u, v ;
    for (int i = 1 ; i < n ; ++ i)
        scanf("%d%d", &u, &v), add(u, v) ;
    rt1 = dfs(1, 0) ; fa[rt1] = 0 ;
    dep[rt1] = 0 ; rt2 = dfs(rt1, 0) ;
    //cout << rt1 << " " << rt2 << endl ;
    for ( ; rt2 ; rt2 = fa[rt2])
        vis[rt2] = 1, d[++ tot] = rt2 ;
    //cout << tot << endl ;
    for (int i = 1 ; i <= n ; ++ i){
        if (vis[i]) continue ; bool ans = 0 ;
        for (int k = head[i] ; k ; k = next(k))
            if (vis[to(k)]) { deg[to(k)] ++, ans = 1 ; break ; }
        if (!ans) return puts("-1"), 0 ;
    }
    num = 0 ;
    for (int i = 1 ; i <= tot ; ++ i){
        for (int j = 1 ; j <= deg[d[i]] ; ++ j)
            p[num + j] = num + j + 1 ;
        p[num + deg[d[i]] + 1] = num + 1 ; num += deg[d[i]] + 1 ;
    }
    num = 0 ;
    for (int i = tot ; i >= 1 ; -- i){
        for (int j = 1 ; j <= deg[d[i]] ; ++ j)
            q[num + j] = num + j + 1 ;
        q[num + deg[d[i]] + 1] = num + 1 ; num += deg[d[i]] + 1 ;
    }
    for (int i = 1 ; i <= n ; ++ i)
        if (p[i] != q[i]){
            if (p[i] < q[i]){
                for (int j = 1 ; j <= n ; ++ j)
                    printf("%d ", p[j]) ; puts("") ;
                return 0 ;
            }
            else {
                for (int j = 1 ; j <= n ; ++ j)
                    printf("%d ", q[j]) ; puts("") ;
                return 0 ;
            }
        }
    for (int j = 1 ; j <= n ; ++ j)
        printf("%d ", p[j]) ; puts("") ;
    return 0 ; 
}

```

---

## 作者：CrTsIr400 (赞：7)

## 别想太多！[[ARC095F] Permutation Tree](https://www.luogu.com.cn/problem/AT_arc095_d)

一开始半个小时看错题了（悲）

注意，$j$ 是**最大**的 $j$ 使得 $p_j<p_i$。**并没有**理所当然的 $j<i$ 的情况。

### 破题点

图同构是很困难的。所以不需要往图同构的算法上去想。

研究一棵树的形态问题，可以由直径的框架出发着手。

### 思路

这种构造题先考虑一个必要条件：有没有解。

把第一个样例拉出来，发现有个点下面挂了直系儿子。

![](https://cdn.luogu.com.cn/upload/image_hosting/ow33jqzq.png)

考虑直系儿子的构造方案：我们先按顺序把 $A,B,C,D,E,F$ 从小到大填上数字 $1,2,3,4,5,6$。

这时候只考虑加入一个 $C$ 的儿子 $G$ 点，会发生什么。

此时需要保证 $G$ 能连接到 $C$ 上面，同时有需要保证别的不会乱连上去。

**坐标上**，我们改变直接在 $C$ 之前插入 $G$，那么整个排列的顺序就变成了 $A,B,G,C,D,E,F$。

**数组值上**，先前填上的数字只有 $1,2,3,4,5,6$，想到一个很精巧的构造方案，在 $3$ 之前插入个 $3.5$。这样 $4$ 能继续连接到 $3$，别的也无法变动，但是 $3.5$ 也能连接到 $3$。

（注意这里为了简化研究，我只是构造了个**不重序列** $p$。若要让 $p$ 严格满足排列的性质，其实就移动一下编号就好了）

---

考虑一些扩展情况。若是一个节点 $C$ 有两个**直系儿子** $G,H$（注意不是这张图的情况），能否构造一个可行解。

答案也是肯定的。给 $G$ 赋值 $3.3$ 插在 $B$ 的后面，给 $H$ 赋值 $3.5$ 插在 $G$ 的后面，这也是一种可行的解（实际上，它是最优的）。

多个直系儿子也照样依次从小到大赋值。

----

若是一个点有多层的儿子（就是上图的情况）会有什么问题。

假设我们已经把 $G$ 加进去了，赋值 $3.5$，能否加入一个 $H$ 使得 $H$ 只跟 $G$ 连边？

首先 $H$ 要在 $G$ 的左右两侧，这是毋庸置疑的。因为在其他地方 $H$ 无论怎么赋值都会连到其他节点上。

若要满足 $H$ 能连到 $G$ 上，需要有 $p[H]>p[G]$ 且 $p[H]<p[C]$（因为不能连 $C$）。此时因为需要保证 $p[G]>p[C]$，与题设矛盾，所以无法连接。

所以，$G$ 下面不能再接儿子。

---

总结一下，把直径拉出来，然后把距离直径 $\le 1$ 的点全部选上。全部点都选上了，那就有解。

有解我们再来形式化之前的构造方法。

这里挂在直径上每个点的直系儿子们都可以不用具体记录了，就设 $d[i]$ 为直径上第 $i$ 个点的直系儿子数量，有可能为 $0$。

因为一个点的直系儿子编号要大于其本身编号，但是又不能太大，因为要保证字典序，所以我们先插入一个编号 $i$（对应的是链中第 $x$ 位），在 $i$ 之前再按顺序插入 $d[x]$ 个值 $i+1,i+2...i+d[x]$。

倒着跑一遍可能更优。所以我们正着跑一遍直径，倒着跑一遍直径。

所以这个题就做完了。还有不懂的大概可以看代码（

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I N=1e5+10;
vector<I>e[N],stk,a[2];
I st=1,ed=1,dis,n,d[N],cnt,sd;
V gpa(I x,I&p,I&pd,I fa=0,I dep=0){
	if(dep>pd)pd=dep,p=x;
	for(I y:e[x])if(y^fa)gpa(y,p,pd,x,dep+1);}
bool gst(I x,I t,I fa=0){stk.push_back(x);
	if(x==t)return 1;
	for(I y:e[x])if(y!=fa&&gst(y,t,x))return 1;
	return stk.pop_back(),0;}
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	fo(i,2,n){I x,y;
		cin>>x>>y;e[x].push_back(y);e[y].push_back(x);}
	gpa(1,st,dis);dis=0;
	gpa(st,ed,dis);
	gst(st,ed);
	for(I i:stk){
		d[i]=e[i].size()-2+(i==st)+(i==ed);
		sd+=d[i]+1;}
	if(sd!=n)return puts("-1"),0;
	fo(t,0,1){
		cnt=1;
		for(I x:stk){
			fo(i,1,d[x])
				a[t].push_back(cnt+i);
			a[t].push_back(cnt);
			cnt+=d[x]+1;
		}
		reverse(stk.begin(),stk.end());
	}if(a[0]>a[1])swap(a[0],a[1]);
	for(I i:a[0])printf("%d ",i);
	return 0;}
```

---

后记：这是我不依赖任何题解提示自己做出来的第一道 ARC F 题，也算是一个小小的进步吧。

---

## 作者：逃离地球 (赞：5)

考虑转换 $p$ 的下标和值，即构造新的序列 $q$，满足 $q_{p_i}=i$，则构造这颗树的过程可以看作从左到右扫 $q$，到 $q_i$ 时，找到前缀最大值 $q_j=\max_{k=1}^{i-1}{q_k}$，然后连边 $(q_j,q_i)$。

若新扫到的数 $q_i$ 是新的前缀最大值，那么后面的一些数会连向 $q_i$，否则后面的一些数还会连向 $q_j$（直到出现新的前缀最大值）。

于是可以发现，树的形态一定是一条链上挂了一些点，且链上的点一定是 $q$ 序列的前缀最大值。

于是统计主链上每个点的度数 $d$，设当前编号分配到了 $s$，则把挂在当前点上的点分配 $s+1\sim s+d$，当前点为 $s+d+1$ 即可（由于要求字典序最小，故这样一定是更优的）。

主链的两个方向都做一次，输出字典序较小的即可。

---

## 作者：jun头吉吉 (赞：2)

## 题意

给出 $T$ 构造 $p$ 满足：对每一个 $p_i\ne 1$，找到最大的 $p_j<p_i$ 然后 $i,j$ 之间连边得到的树和 $T$ 同构。
## 题解
首先考虑 $p$ 的逆排列 $q$，即 $q_{p_i}=i$，那么 $i\ge2$ 实际上是向 $q_{1,\dots,i-1}$ 最大值所在的位置连边。

于是如果 $i-1$ 是前缀最大值，则 $fa_i=i-1$ 否则 $fa_i=fa_{i-1}$ ，于是树的形态应该是这样的：

```sto
  o
/|||\
     o
   /|||\
        o
      /|||\
```

如果能够画出这棵树就能得到那些位置是前缀最大值。前缀最大值这个关系我们可以用不等式来约束，也就是如果 $i,j$ 是相邻的前缀最大值，那么 $i+1,\dots,j-1$ 这些点向 $i$ 连边，$i$ 向 $j$ 连边。还有一个就是我们对 $q_n$ 是不是前缀最大值没有约束需要注意。

然后就可以用拓扑排序得到最优解了。

所以我们现在的目的就是把树变成上面的结构。

把所有的叶子删掉应该是一条链，链两端以及两端的叶子可能是上面这个结构的根，因为同一个点的叶子是等价的所以只要对 $4$ 个点分别当做根求解就能得到答案了。

复杂度 $\mathcal O(n\log n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
#define pc putchar
#define chkmx(a,b) (a)=max((a),(b))
#define chkmn(a,b) (a)=min((a),(b))
#define fi first
#define se second
#define orz puts("-1"),exit(0);
using namespace std;
template<class T>
void read(T&x){x=0;char c=getchar();bool f=0;for(;!isdigit(c);c=getchar())f^=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<class T,class ...ARK>void read(T&x,ARK&...ark){read(x);read(ark...);}
template<class T>void write(T x){if(x<0)pc('-'),x=-x;if(x>=10)write(x/10);pc(x%10+'0');}
template<class T,class ...ARK>void write(T x,ARK...ark){write(x);pc(' ');write(ark...);}
template<class ...ARK>void writeln(ARK...ark){write(ark...);pc('\n');}
typedef long long ll;
const int mod=998244353;
struct mint{
	int x;mint(int o=0){x=o;}mint&operator+=(mint a){return(x+=a.x)%=mod,*this;}mint&operator-=(mint a){return(x+=mod-a.x)%=mod,*this;}
	mint&operator*=(mint a){return(x=1ll*x*a.x%mod),*this;}mint&operator^=( int b){mint a=*this;x=1;while(b)(b&1)&&(*this*=a,1),a*=a,b>>=1;return*this;}
	mint&operator/=(mint a){return*this*=(a^=mod-2);}friend mint operator+(mint a,mint b){return a+=b;}friend mint operator-(mint a,mint b){return a-=b;}
	friend mint operator*(mint a,mint b){return a*=b;}friend mint operator/(mint a,mint b){return a/=b;}friend mint operator^(mint a, int b){return a^=b;}
};
#define lowbit(x) ((x)&-(x))
#define mid ((l+r)>>1)
#define lc (x<<1)
#define rc (x<<1|1)
const int N=1e5+100;
int n,deg[N];vector<int>e[N];
int Ans[N];bool vis[N];
namespace solve{
	int dep[N];int cnt[N],has[N];
	void dfs(int u,int fa){
		dep[u]=dep[fa]+1;bool flag=0;
		for(auto v:e[u])if(v!=fa)dfs(v,u),flag=1;
		cnt[dep[u]]++;if(flag)has[dep[u]]++;
	}
	vector<int>e[N];int deg[N],ans[N];priority_queue<int,vector<int>,greater<int>>q;
	void add(int u,int v){
		if(!u||!v)return;
		if(u==n||v==n)return;
		//writeln(u,v);
		e[u].pb(v);deg[v]++;
	}
	int premx[N],top;
	void work(int rt){
		for(int i=1;i<=n;i++)e[i].clear();
		memset(deg,0,sizeof deg);
		memset(cnt,0,sizeof cnt);
		memset(has,0,sizeof has);
		top=0;
		dfs(rt,0);
		for(int i=1;i<=n;i++)if(has[i]>1)return;
		for(int i=1,now=cnt[1];has[i];i++,now+=cnt[i])
			premx[++top]=now;
		premx[++top]=n;
		for(int i=2;i<=top;i++){
			add(premx[i-1],premx[i]);
			for(int j=premx[i-1]+1;j<premx[i];j++)
				add(j,premx[i-1]);
		}
		for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
		int tot=0;
		while(q.size()){
			int u=q.top();q.pop();ans[++tot]=u;
			for(auto v:e[u]){
				deg[v]--;
				if(deg[v]==0)q.push(v);
			}
		}
		for(int i=1;i<=n;i++){
			if(ans[i]==Ans[i])continue;
			if(ans[i]>Ans[i])return;
			else break;
		}
		for(int i=1;i<=n;i++)Ans[i]=ans[i];
	}
}
signed main(){
	read(n);
	if(n==1)return puts("1 2"),0;
	for(int i=1,u,v;i<n;i++)read(u,v),e[u].pb(v),e[v].pb(u),deg[u]++,deg[v]++;
	for(int i=1;i<=n;i++)if(deg[i]==1)vis[i]=1;
	for(int i=1;i<=n;i++)if(vis[i])deg[e[i][0]]--;
	vector<int>kk;
	for(int i=1;i<=n;i++)if(!vis[i]){
		if(deg[i]<=1)kk.pb(i);
		else if(deg[i]!=2)orz;
	}
	Ans[1]=n+1;
	for(auto x:kk){
		solve::work(x);
		for(auto y:e[x])if(vis[y]){solve::work(y);break;}
	}
	for(int i=1;i<=n;i++)write(Ans[i]),pc(' ');
}
```

---

## 作者：xht (赞：1)

> [ARC095F Permutation Tree](https://atcoder.jp/contests/arc095/tasks/arc095_d)

## 题意

- 对于一个 $1\sim n$ 的排列 $p_{1\cdots n}$，可以通过如下方法生成一棵树：
  - 对于 $i$，如果 $p_i \ne 1$，则找到一个最大的 $j$ 满足 $p_j < p_i$，在 $i,j$ 之间连边。
- 现在要求找到一个字典序最小的**生成的树与给定的树同构**的排列，或判断无解。
- $n \le 10^5$。

## 题解

给定树必须要是一个毛毛虫，即去掉叶子之后要是一条链。

正反方向贪心一下，取字典序更小的方案即可。

## 代码

```cpp
const int N = 1e5 + 7;
int n, d[N], c[N], l, r;
vi e[N];
bool v[N];

inline int find(int x) {
	for (int y : e[x])
		if (!v[y] && d[y] != 1) return y;
	return 0;
}

inline vi work(int l, int r) {
	vi ret(1, 1), p(1, d[l] - 2);
	for (int i = 1; i <= n; i++) v[i] = 0;
	while (l != r) v[l] = 1, l = find(l), p.pb(d[l] - 2);
	int t = 1;
	for (int x : p) {
		dbg(x);
		for (int i = 1; i <= x; i++) ret.pb(t + i + 1);
		ret.pb(t + 1), t += x + 1;
	}
	ret.pb(n);
	return ret;
}

int main() {
	rd(n);
	if (n == 2) return prints("1 2"), 0;
	for (int i = 1, x, y; i < n; i++)
		rd(x, y), e[x].pb(y), e[y].pb(x), ++d[x], ++d[y];
	for (int i = 1; i <= n; i++) c[i] = d[i];
	for (int i = 1; i <= n; i++)
		if (d[i] == 1) --c[e[i][0]], --c[i];
	if (*max_element(c + 1, c + n + 1) > 2) return print(-1), 0;
	if (!*max_element(c + 1, c + n + 1)) {
		print(1, ' ');
		for (int i = 3; i < n; i++) print(i, ' ');
		print(2, ' '), print(n);
		return 0;
	}
	for (int i = 1; i <= n; i++)
		if (c[i] == 1) r = i;
	for (int i = n; i; i--)
		if (c[i] == 1) l = i;
	vi ans = min(work(l, r), work(r, l));
	for (int x : ans) print(x, ' ');
	return 0;
}
```

---

## 作者：1saunoya (赞：1)

容易发现如果有解，那么答案是一条链挂上一堆点。


然后具体怎么求一组解:

抓出最长链，然后依次遍历链上的点 $u$

（题目说的是 $i, j$ 如果有边，仅当 $j$ 是最大的满足 $p_j < p_i$）。

我们当前在枚举链，链上挂了一堆点的情况下，链点只能连一条，所以我们需要满足 $p_u < p_v$。（让 v 连向 u）。

那么此时还需要，$p_u$ 是后面最后一个小于 $p_v$ 的。

然而我们可以想到，不如将这个 $p_u$ 作为唯一一个小于 $p_v$ 的。（且在 v 的后面。）

这样就可以符合对于链向每个散点的条件。

接下来是链的问题:

需要将 $u1 \to u2$。

那么 $p_{u1} < p_{u2}$，并且，$p_{u1}$ 是最后面的小于 $p_{u2}$ 的。


那我们只需要顺序构造链和散点之间的边，就刚好符合这一条件。

链有两端，从两边分别跑一遍，取一个字典序最小的即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
 ios::sync_with_stdio(false);
 cin.tie(NULL);
 int n;
 cin >> n;
 vector<vector<int>> e(n);
 for (int i = 1; i < n; i++) {
  int u, v;
  cin >> u >> v;
  --u;
  --v;
  e[u].push_back(v);
  e[v].push_back(u);
 }
 queue<int> q;
 vector<int> w1(n, -1);
 w1[0] = 0;
 q.push(0);
 while (!q.empty()) {
  int u = q.front();
  q.pop();
  for (auto v : e[u]) {
   if (w1[v] == -1) {
    w1[v] = w1[u] + 1;
    q.push(v);
   }
  }
 }
 int p1 = 0;
 for (int i = 1; i < n; i++) {
  if (w1[p1] < w1[i]) {
   p1 = i;
  }
 }
 vector<int> w2(n, -1);
 w2[p1] = 0;
 q.push(p1);
 while (!q.empty()) {
  int u = q.front();
  q.pop();
  for (auto v : e[u]) {
   if (w2[v] == -1) {
    w2[v] = w2[u] + 1;
    q.push(v);
   }
  }
 }
 int p2 = 0;
 for (int i = 1; i < n; i++) {
  if (w2[p2] < w2[i]) {
   p2 = i;
  }
 }
 vector<int> path = {p2};
 while (path.back() != p1) {
  int u = path.back();
  for (auto v : e[u]) {
   if (w2[v] == w2[u] - 1) {
    path.push_back(v);
    break;
   }
  }
 }
 auto d = path;
 sort(d.begin(), d.end());
 vector<int> ans[2];
 for (int k = 0; k < 2; k++) {
  int c = 0;
  for (auto u : path) {
   int c1 = ++c;
   for (auto v : e[u]) {
    if (!binary_search(d.begin(), d.end(), v)) {
     ans[k].push_back(++c);
    }
   }
   ans[k].push_back(c1);
  }
  reverse(path.begin(), path.end());
 }
 vector<int> w = min(ans[0], ans[1]);
 if (w.size() != n) {
  cout << -1 << "\n";
 } else {
  for (auto i : w) {
   cout << i << " ";
  }
 }
 return 0;
}

---

## 作者：Msents (赞：0)

考虑将 $1$ 到 $n$ 依次插入序列中，每次插入元素时，有两种情况：

1.将该元素插到之前所有的元素的左边，那么该元素就会与插入位置右边的元素连边，且当前元素之后不再会与其它元素连边。

2.将该元素插到之前所有的元素的右边，那么该元素就会与之前序列最靠右的元素连边，且当前元素之后还可以与其它元素连边。

可以发现，所有能被构造出来的树都是形如一条链，链上每个点都外挂若干叶子的形态。

于是跑一遍直径，找叶子，就能判断该树是否能找到同构。

现考虑序列怎么才能做到字典序最小。先跑直径，找到直径长度和每个点外挂叶子的个数。考虑当前填了 $s$ 个数字，有 $l$ 个叶子，那么贪心地加入 $s+2,s+3,...,s+l,s+l+1$，再加入 $s+1$ 即可。

还注意到如果将直径序列倒转过来，靠前的节点外挂叶子可能相对更少，那么答案也有可能更优，于是在生成答案前先将直径序列设成正序和反序中字典序更小的那个，这题就完了。

码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=100000;
int n,a[MaxN+1],sign=0;
vector<int>g[MaxN+1];
void DFS(int u,int prt,int dis,int&mxDis,int&ans){
	if(dis>mxDis)mxDis=dis,ans=u;
	for(int v:g[u]){
		if(v==prt)continue;
		DFS(v,u,dis+1,mxDis,ans);
	}
}
vector<int>vec;
bool DFS2(int u,int prt,int t){
	int nxt=0;
	if(u==t)goto onChain;
	for(int v:g[u]){
		if(v!=prt&&DFS2(v,u,t)){
			nxt=v;
			goto onChain;
		}
	}
	return false;
onChain:
	int sum=0;
	for(int v:g[u]){
		if(v==prt||v==nxt)continue;
		if(g[v].size()>1){
			cout<<"-1";
			exit(0);
		}
		sum++;
	}
	vec.push_back(sum);
	return true;
}
void Solve(){
	cin>>n;
	for(int i=1;i<=n-1;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int mxDis=0,ans=0,s,t;
	DFS(1,0,0,mxDis,ans);
	s=ans;
	mxDis=0;
	DFS(s,0,0,mxDis,ans);
	t=ans;
	DFS2(s,0,t);
	for(int i=0;i<vec.size();i++){
		if(vec[i]<vec[vec.size()-i-1]){
			break;
		}else if(vec[i]==vec[vec.size()-i-1]){
			continue;
		}else{
			reverse(vec.begin(),vec.end());
			break;
		}
	}
	for(int sum:vec){
		int t=sign+1;
		for(int i=sign+2,j=1;j<=sum;i++,j++)a[++sign]=i;
		a[++sign]=t;
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
}
int main(){
	cin.tie(0)->sync_with_stdio(false);
	Solve();
	return 0;
}

```

---

## 作者：xlpg0713 (赞：0)

咋是个神秘构造题。

先考虑给你一条链怎么做，很显然，直接从 $1$ 填到 $n$ 就是合法的。

考虑在这个链上某个点挂一个儿子，例如原来有 $5$ 个点，现在在 $3$ 下面又有一个点。

这个点的权值应当大于 $3$ 号点，小于 $4$ 号点，同时应当在 $3$ 号点的左侧。前两条是为了保证这个点连在 $3$ 号点上，后一条是为了 $4$ 号点链接为 $3$ 号点。将排列的后半部分平移，现在的排列是 $\{1,2,4,3,5,6\}$。

同理我们可以得到一个点上挂很多儿子的构造方式：假设链上的点权值为 $x$，就在排列中 $x$ 的前面放 $x+1$ 到 $x+ct$，其中 $ct$ 为儿子个数。链上 $x$ 的后继是 $x+ct+1$。

考虑什么时候不合法，发现当链上的一个点挂了一颗深度大于 $2$ 的子树时，考虑链上点 $x$，$x$ 的儿子 $y$，$y$ 的儿子 $z$。有 $a_z>a_y,a_y>a_x,a_z<a_x$，矛盾。也即合法的图是一个毛毛虫。

实现部分就简单了，找到直径，判断是不是毛毛虫，合法就按照以上方法构造。不过注意从直径的任意一端开始都是合法的，需要做两遍。

应该是易于做到 $O(n)$ 的。

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
const int N = 1e5 + 10;
int n, sm, d[N], f[N], ct[N]; std::vector<int> g[N], vc;
void dfs(int x,int fa){f[x]=fa;for(auto v:g[x])if(v!=fa)d[v]=d[x]+1,dfs(v,x);}
int main(){
    std::cin >> n; for(int i = 1, x, y; i < n; i++)
        std::cin >> x >> y, g[x].push_back(y), g[y].push_back(x);
    dfs(1, 0); int rt = std::max_element(d+1, d+n+1)-d;
    dfs(rt, 0); for(int x = std::max_element(d+1, d+n+1)-d;
        x != rt; x = f[x]) vc.push_back(x); vc.push_back(rt);
    std::reverse(vc.begin(), vc.end());
    for(auto it = vc.begin(); it != vc.end(); it++){
        int x = *it; for(auto v:g[x])
            if(v != f[x] && v != *next(it)) ct[x]++, sm++;
    }
    if(sm + vc.size() != n) return std::cout << -1, 0;
    std::basic_string<int> s, t; int tm = 0;
    for(int i = 0, j, x; i < vc.size(); i++, s += x)
       for(x = ++tm, j = 1; j <= ct[vc[i]]; j++) s += ++tm;
    tm = 0; for(int i = vc.size() - 1, j, x; ~i; i--, t += x)
       for(x = ++tm, j = 1; j <= ct[vc[i]]; j++) t += ++tm;
    s = std::min(s, t); for(int i = 0; i < n; i++) std::cout << s[i] << ' ';
}
```

---

## 作者：hegm (赞：0)

### [[ARC095F] Permutation Tree](https://www.luogu.com.cn/problem/AT_arc095_d)

考虑已经加入了前 $i$ 个数，那么现在加入第 $i+1$ 个数，有两种情况：

1. 自己不放置在最右侧，那么 $i+1$ 的父亲是最右侧的节点，并且自身一定是一个叶子，因为最右侧的节点比 $i+1$ 坐标大并且小于 $i+1$。

2. 自身放置在右侧，那么 $i+1$ 的父亲是除了他以外的最右侧的点。

因此我们发现，如果一个树可以被构建出来，那么一定存在以某一个节点为根，树上的没一个节点满足他的所有孩子中至多只有一个节点不是叶子。

容易发现，这样的树就是“毛毛虫”。

判断做完了，考虑最小的前提。

毛毛虫的根一共就有两种情况：分别是直径的两头，因为其他节点不是毛毛虫或者一定不如这两个优。

考虑构建形式，加入当前的 $i$ 的父亲往上的树合这些节点的叶子孩子已经建好了，那么需要插入当前节点和当前节点的叶子孩子。

一定形如 $fa_i,i+1,i+2,i$ 这样的形式。

这样的话 $i+1,i+2$ 的父亲是 $i$ 并且字典序最小，然后 $i$ 的非叶子孩子放在 $i$ 的后面继续即可。

那么两个方案分别跑一遍取最优即可。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ull unsigned long long
#define make make_pair
#define N 100005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,a[2][N];
bool awa;
struct fig
{
	int to,next;
}k[N*2];int head[N],tot,dep[N],siz[N],son[N];
void add(int from,int to)
{
	k[++tot].to=to;
	k[tot].next=head[from];
	head[from]=tot;
}
int dfs(int now,int f)
{
	dep[now]=dep[f]+1;int p=now;
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==f)continue;
		int x=dfs(k[i].to,now);
		if(dep[x]>dep[p])p=x;
	}
	return p;
}
void solve(int now,int f)
{
	siz[now]=1;son[now]=0;int qwq=0;
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==f)continue;
		solve(k[i].to,now);
		siz[now]+=siz[k[i].to];
		if(siz[son[now]]<siz[k[i].to])son[now]=k[i].to;
		if(siz[k[i].to]!=1)qwq++;
	}
	if(qwq>1)awa=1;
}
int ct,cnt;
void get(int now)
{
	int y=cnt+1;
	for(int i=siz[now]-siz[son[now]]-1;i>=1;i--)
	{
		cnt++;
		a[ct][cnt]=cnt+1;
	}
	a[ct][++cnt]=y;
	if(son[now])get(son[now]);
}
signed main()
{
	n=read();
	for(int i=1,u,v;i<n;i++)
	{
		u=read();v=read();
		add(u,v);add(v,u);
	}
	int S=dfs(1,0);
	int T=dfs(S,0);
	solve(S,0);ct=0;cnt=0;get(S);
	if(awa)
	{
		cout<<"-1\n";
		return 0;
	}
	solve(T,0);ct=1;cnt=0;get(T);
	for(int i=1;i<=n;i++)
	{
		if(a[0][i]!=a[1][i])
		{
			if(a[0][i]<a[1][i])ct=0;
			break;
		}
	}
	for(int i=1;i<=n;i++)cout<<a[ct][i]<<" ";
	return 0;
}

```

---

## 作者：songhongyi (赞：0)

考虑逆序列 $q$，则可以把构造树的方式重写为：

> 对于每一个 $i$，找到最大的 $q_j$ 使得 $j < i$，然后在 $q_i,q_j$ 间连边。

即把 $q$ 中每个数连向其前缀最大值。

不难发现这样连出的树是一个”毛毛虫“，即一条主链旁连着若干个点。这是因为链上的点都是前缀最大值，在下一个极值前的点都直接连向这个最大值。

如果输入的树不满足此要求一定无解，下面我们给出满足此要求时的构造方法。

首先对于主链，显然顺序的排列是最优的。那么如果我们经过了一个有挂着其它点的链上节点，我们发现显然先将能用的最小的点使用上最优，其顺序应该是【从小到大排列挂载的点】+ 【链上的点】。比如目前遍历到 `3`，有一个点挂载了两个点，则添加 `4 5 3`，这也是样例中的情况。

但我们发现主链有两种遍历方式，我们考虑如何求出最优的那个。考虑链上每个点的挂载节点的数量组成的序列，容易发现字典序最小的那个更优。

实现上可以使用求直径的方式求出主链，然后处理难度不高。复杂度 $O(n)$。

---

