# Knapsack Queries on a tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tokiomarine2020/tasks/tokiomarine2020_d

$ N $ 頂点からなる根付き二分木があり、各頂点には $ 1 $ から $ N $ までの番号がついています。 頂点 $ 1 $ が根であり、頂点 $ i $ ($ i\ \geqq\ 2 $) の親は頂点 $ \left[\ \frac{i}{2}\ \right] $ です。

各頂点には $ 1 $ つのアイテムがあります。頂点 $ i $ にあるアイテムの価値は $ V_i $ であり、重さは $ W_i $ です。 そこで、次のクエリに $ Q $ 回答えてください。

- 二分木の頂点 $ v $ 及び正の整数 $ L $ が与えられる。 $ v $ 及び $ v $ の先祖にあるアイテムを、重さの合計が $ L $ 以下となるようにいくつか（$ 0 $ 個でもよい）選ぶ。 このとき、選んだアイテムの価値の総和の最大値を求めよ。

ただし、頂点 $ u $ が頂点 $ v $ の先祖であるとは、頂点 $ u $ が頂点 $ v $ の間接的な親である、つまり、 $ w_1=v $、$ w_k=u $、さらに各 $ i $ について $ w_{i+1} $ が $ w_i $ の親となるような頂点の列 $ w_1,w_2,\ldots,w_k $ ($ k\geqq\ 2 $) が存在することを指します。

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ <\ 2^{18} $
- $ 1\ \leqq\ Q\ \leqq\ 10^5 $
- $ 1\ \leqq\ V_i\ \leqq\ 10^5 $
- $ 1\ \leqq\ W_i\ \leqq\ 10^5 $
- 各クエリで指定される $ v $, $ L $ は $ 1\ \leqq\ v\ \leqq\ N $, $ 1\ \leqq\ L\ \leqq\ 10^5 $ を満たす。
- 入力で与えられる値はすべて整数である。

### Sample Explanation 1

最初のクエリでは、選ぶことのできるアイテムは $ (V,W)=(1,2) $ なるアイテムのみであるので、 $ L=1 $ より $ 1 $ つもアイテムを選ぶことができません。 したがって、答えは $ 0 $ になります。 一方で $ 2 $ 番目のクエリでは、選ぶことのできるアイテムは $ (V,W)=(1,2) $ なるアイテムと $ (V,W)=(2,3) $ なるアイテムの $ 2 $ つであり、 $ L=5 $ より両方を選ぶことができます。 したがって、答えは $ 3 $ になります。

## 样例 #1

### 输入

```
3
1 2
2 3
3 4
3
1 1
2 5
3 5```

### 输出

```
0
3
3```

## 样例 #2

### 输入

```
15
123 119
129 120
132 112
126 109
118 103
115 109
102 100
130 120
105 105
132 115
104 102
107 107
127 116
121 104
121 115
8
8 234
9 244
10 226
11 227
12 240
13 237
14 206
15 227```

### 输出

```
256
255
250
247
255
259
223
253```

# 题解

## 作者：Unordered_OIer (赞：5)

# Knapsack Queries on a tree

给定一个 $N$ 个节点的二叉树，编号 $1$ 到 $N$，根为 $1$，对于任意一个非根节点 $i$，$i$ 的父亲为 $\lfloor \frac{i}{2}\rfloor$，每一个节点 $j$ 都有一个价值 $V_j$ 和权重 $W_j$.

接下来有 $Q$ 次询问，每次询问给出两个正整数 $v$，$L$，请你在 $v$ 和 $v$ 的祖先中选出若干个(可以为 $0$ 个)节点，使得选出的节点的权重不超过 $L$，求最大能选出的价值。

****

模拟赛里爆砍暴力分，感觉对于这些神秘的根号分治（？）题目还是过于不熟悉了。

首先，空间复杂度 $O(W)$ 的 01 背包不难。

发现这个树深度 $\leq 18$，但是 $O(qW)$ 的暴力背包肯定过不去。

根据题目性质发现，在树上的两个点 $u,v$，他们的物品集合有重复部分，即 $\operatorname{lca}(u,v) \rightarrow 1$ 路径上的所有物品，这一部分在暴力背包中要重复做很多次。

所以我们考虑，把某些节点的背包问题直接预先处理出来，但是节点还挺多的，所以不能全部处理。

于是进行根号分治，把 $depth=1 \sim 10$（或者也可以更深/浅）的节点的背包一开始全部跑出来。然后对于 $depth$ 在这一区间内的点的询问，就可以直接回答。

如果是更深的节点 $v$ 的询问，不妨记 $u$ 为 $v \rightarrow 1$ 的链上，$depth=10$ 节点，然后我们暴力枚举 $v \rightarrow u$ 上的所有决策（不超过 $2^8=256$ 种），可以状压实现，每枚举了一种决策，产生了 $sv$ 的价值并占 $sw$ 的权重，那么剩余的权重 $L-sw$ 直接使用预处理出来的前十层节点的背包答案进行回答即可。

复杂度 $O(L\sqrt n+q \sqrt n \log n)$。

```cpp
for(int i=2;i<=min(n,N);i++){
  for(int j=0;j<=lim;j++)
    f[i][j]=f[i>>1][j];
  for(int j=lim;j>=w[i];--j)
    f[i][j]=max(f[i][j],f[i>>1][j-w[i]]+v[i]);
}//预处理背包
q=read();
while(q--){
  int x=read(),L=read();
  vector<int> fas;fas.clear();
  while(x>N){
    fas.emplace_back(x);
    x>>=1;
  }
  int S=fas.size(),ans=0;
  for(int i=0;i<(1<<S);i++){//枚举决策
    int sv=0,sw=0;
    for(int j=0;j<10;j++){
      if(i&(1<<j)){
        sv+=v[fas[j]];
        sw+=w[fas[j]];
      }
    }
    if(sw<=L){
      ans=max(ans,sv+f[x][L-sw]);
    }
  }
  cout<<ans<<'\n';
}
```

---

## 作者：lcfollower (赞：3)

题目大意
---

给定一棵 $n$ 个节点的**完全二叉树**，第 $i$ 个节点有价值 $v_i$ 和权值 $w_i$。

再给出 $Q$ 次询问 $v$，$L$，请从根到 $v$ 的所有节点中选出若干个节点，使得它们的权重和不超过 $L$ 且价值和最大，输出价值和。

$1\le n\le 2^{18}$，$1\le v_i ,w_i ,L ,Q \le 10^5$。


思路
---

因为这是一棵完全二叉树，所以对于一个节点，从根到该节点的个数大约为 $\log n$。

由此推出以下两种算法：

- 暴力枚举节点是否选择并判断是否合法，时间复杂度为 $\mathcal O(Qn)$。

- 将节点选出来，然后跑背包，时间复杂度为 $\mathcal O(QL\log n)$。

然而，以上的时间复杂度都不理想。

于是我们考虑将这棵树分成一部分高 $h$，另一部分高 $18 - h$（这里先默认树高为 $18$）。

第一部分跑背包，可以作预处理，时间复杂度为 $\mathcal O(2^hL)$。

第二部分跑暴力（搜索），时间复杂度为 $\mathcal O(2^{18-h}Q)$。

为了使得上下两部分均衡，即 $\mathcal O(2^hL) = \mathcal O(2^{18-h}Q)$。因为 $Q$，$L$ 同阶，所以 $h = 9$ 最佳，不过你不默认直接解方程也可以，防止 $Q$，$L$ 相差过大产生浪费时间（~~当然我没这么勤快~~）。

读者也可以想一想可不可以第一部分暴力，第二部分背包，这里就不阐述了。

代码
---

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 1e14

using namespace std;

inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}

const int N = 515 ,M = 1e5 + 10 ,NUM = (1 << 18) + 10;
int n ,Q ,v[NUM] ,w[NUM] ,f[N][M];

inline int dfs (int V ,int L){//用 dfs 实现更简单。
  if (V <= 512) return f[V][L];

  if (w[V] <= L) return max (dfs (V >> 1 ,L) ,dfs (V >> 1 ,L - w[V]) + v[V]);//选与不选。
  return dfs (V >> 1 ,L);//不可以选，就不选。

} signed main (){

  n = read ();

  up (i ,1 ,n) v[i] = read () ,w[i] = read () ;

  up (i ,1 ,512)
    dn (j ,1e5 ,0){
      f[i][j] = f[i >> 1][j];
      if (j >= w[i]) f[i][j] = max (f[i][j] ,f[i >> 1][j - w[i]] + v[i]);
    }

  Q = read ();

  while (Q --){
    int V = read () ,L = read () ;

    writeln (dfs (V ,L));
  }
  return 0 ;
}
```

---

## 作者：_determination_ (赞：2)

首先注意到深度很小（即背包物品个数很少），所以我们考虑直接 $O(ql\log n)$ 开冲。但是这样太大了，而且不能很好的利用二叉树的性质，考虑优化。

发现直接把询问离线下来然后做背包，这样能做到 $O(nl)$。这样随便是个树即可，并不能很好的利用性质。

我们回忆背包的做法，发现其实有一个 $O(2^n)$ 的做法，在 $n$ 很少 $l$ 很大的时候甚至是更优的。

我们考虑把树劈成两半，上半和下半。上半部分跑背包，节点数 $\sqrt{n}$，总复杂度 $O(l\sqrt{n})$。下半部分开搜，询问数 $q$，物品数 $\frac{\log n}{2}$，一次背包是 $\sqrt{n}$ 的，总复杂度 $O(q\sqrt{n})$。

这样的话复杂度就是 $O((l+q)\sqrt{n})$ 的，可以通过。

笑点解析：考试的时候数据过水直接被暴力冲过去了，但是 AT 过不去。

---

## 作者：igAC (赞：2)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_tokiomarine2020_d)

[ATlink](https://atcoder.jp/contests/tokiomarine2020/tasks/tokiomarine2020_d)

简要题意：

一棵 $n$ 个节点的二叉树，$i$ 号节点的父亲为 $\lfloor \frac{i}{2} \rfloor$，每个点有重量 $w_i$，价值 $v_i$。

$q$ 次查询给出 $x,l$，在 $ 1 \to x $ 这条链上做背包，背包容量为 $l$。

# $\text{Solution}$

01 背包，状压 dp。

一个很巧妙地方法就是折半去做，对于前 $\sqrt{n}$ 个节点做背包，后面在线状压 dp。

设 $f_{i,j}$ 表示当前为第 $i$ 个节点，已经装了体积为 $j$ 的节点的最大价值。

状态转移方程式很显然：

$$
f_{i,j}=\max(f_{fa,j},f_{fa,j-w_i}+v_i)
$$

然后发现不一定要用完背包空间，于是重新定义状态：$f_{i,j}$ 表示当前为 $i$ 号节点，体积不到 $j$ 的最大价值。

发现这个状态其实就是原来状态的前缀 $\max$。

剩下的节点做状压即可，时间复杂度 $O(m \sqrt{n} + q \sqrt{n} \log n)$。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 262150
#define S 520
#define M 100005 
#define P 511
#define D 100000
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,q,v[N],w[N];
int f[S][M];
bool check(int x,int base){return x>>base&1;}
int main(){
	n=read();
	for(int i=1;i<=n;++i) v[i]=read(),w[i]=read();
	for(int i=1;i<=n && i<=P;++i){
		for(int j=0;j<=D;++j) f[i][j]=f[i>>1][j];
		for(int j=w[i];j<=D;++j) f[i][j]=max(f[i][j],f[i>>1][j-w[i]]+v[i]);
	}
	for(int i=1;i<=n && i<=P;++i) for(int j=1;j<=D;++j) f[i][j]=max(f[i][j],f[i][j-1]);
	q=read();
	while(q--){
		int x=read(),l=read(),ans=0;
		vector<int>g;
		for(;x>P;x>>=1) g.push_back(x);
		for(int s=0;s<(1<<g.size());++s){
			int res=0,sum=0;
			for(int i=0;i<g.size();++i) if(check(s,i)) res+=v[g[i]],sum+=w[g[i]];
			if(sum<=l) ans=max(ans,res+f[x][l-sum]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Mr_Avalon (赞：2)

常见求解背包有 $O(p\times L)$ 的 dp 做法和 $O(2^p)$ 的状压做法（$p$ 为物品件数），直接做都过不了，需要考虑优化。

减小值域是不太可行的，我们考虑减少每次询问关联的点数。由于一次询问的过程是在不断往上跳祖先节点，那么问题转换成让最多要跳的层数尽量小。

因为一棵 $n$ 个点，$k$ 层的完全二叉树的前 $\frac k2$ 层只有 $\sqrt n$ 个点，我们可以用 $O(\sqrt n\times L)$ 的时间把这些点有 $L$ 的容积时的答案 $f_{x,L}$ 预处理出来。对于剩下的 $n-\sqrt n$ 个深度大于 $\frac k2$ 的点，直接在线做，可以用 $O(2^{\frac k2})=O(\sqrt n)$ 的时间算出答案。

总复杂度 $O(\sqrt n \times L+\sqrt n\times q)$。

```cpp
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<algorithm>

inline int read()
{
	int v=0,flag=0;char ch=getchar();
	while('0'>ch||ch>'9') flag|=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9') v=v*10+(ch&15),ch=getchar();
	return flag? -v:v;
}

int n,m,v[1<<18],w[1<<18];
int f[1000][100005];

inline void dfs(int x,int dep)
{
	if(x>n||dep>9) return;

	for(int i=0;i<=1e5;i++) f[x][i]=f[x>>1][i];
	for(int i=1e5;i>=w[x];i--)
		f[x][i]=std::max(f[x][i],f[x][i-w[x]]+v[x]);

	dfs(x<<1,dep+1),dfs(x<<1|1,dep+1);
}

inline int brute(int x,int remain)
{	
	if(x<512) return f[x][remain];

	int ret=0;
	if(remain>=w[x])
		ret=std::max(ret,v[x]+brute(x>>1,remain-w[x]));
	ret=std::max(ret,brute(x>>1,remain));
	return ret;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	freopen("output.out","w",stdout);
	#endif

	n=read();
	for(int i=1;i<=n;i++) v[i]=read(),w[i]=read();

	dfs(1,1);

	m=read();
	while(m--)
	{
		int v=read(),L=read();
		printf("%d\n",brute(v,L));
	}
}
```


---

## 作者：shinkuu (赞：2)

一眼背包。但是谁告诉你背包只能 DP 做的。

考虑对每个点从下到上做背包。设树高为 $h$，则复杂度为 $O(q\times h\times m)$，$m$ 为背包大小。

发现如果用 DP 方式求，则一定至少有 $O(q\times m)$ 的复杂度。而又发现物品数很少。直接爆搜 $O(q\times 2^h)$。

$h$ 太大了。考虑一种类似双向搜索的方法。

进行根号分治：对于深度 $<10$ 的点，直接 $O(2^h)$ 暴力，否则先预处理出深度为 $10$ 的情况，然后查询时爆搜直到深度为 $10$ 的点。结合一下处理出答案。

这里有两种实现方式。一是 DP，时空复杂度 $O((m+q)\times\sqrt n)$。楼上大佬已经讲过了。二是搜索，时间复杂度 $O(n+q\times\sqrt n\times\log n)$，空间 $O(n)$。多出来的在于二分，常数很小，具体可以看代码实现。

code：

```cpp
int n,m,dep[N],w[N],c[N];
vector<pii> pre[1027];
vector<int> g[1027],h[1027];
void init(int u,int sw,int sc){
	if(dep[u]==10){
		for(int i=0;i<=1;i++){
			if(sw+i*w[u]>1e5){
				continue;
			}
			pre[u].push_back(make_pair(sw+i*w[u],sc+i*c[u]));//处理出每种情况下权重和价值
		}
		return;
	}
	for(int i=0;i<=1;i++){
		for(int j=0;j<=1;j++){
			if(sw+j*w[u]>1e5||(u<<1|i)>n){
				continue;
			}
			init(u<<1|i,sw+j*w[u],sc+j*c[u]);
		}
	}
}
int dfs1(int u,int sw,int sc){
	if(!u){
		return sc;
	}
	int ans=0;
	for(int i=0;i<=1;i++){
		if(i*w[u]>sw){
			continue;
		}
		ans=max(ans,dfs1(u>>1,sw-i*w[u],sc+i*c[u]));
	}
	return ans;
}
int dfs2(int u,int sw,int sc){
	if(dep[u]==10){
		int x=upper_bound(g[u].begin(),g[u].end(),sw)-g[u].begin()-1;//找到最大的能产生贡献的位置
		return sc+h[u][x];
	}
	int ans=0;
	for(int i=0;i<=1;i++){
		if(i*w[u]>sw){
			continue;
		}
		ans=max(ans,dfs2(u>>1,sw-i*w[u],sc+i*c[u]));
	}
	return ans;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&c[i],&w[i]);
		dep[i]=dep[i>>1]+1;
	}
	init(1,0,0);
	for(int i=1<<9;i<=min(n,(1<<10)-1);i++){
		sort(pre[i].begin(),pre[i].end());//按权重排序
		g[i].push_back(0);
		h[i].push_back(0);
		for(pii j:pre[i]){//处理出可能产生贡献的值，用了类似单调队列的思路
			if(j.second<h[i].back()){
				continue;
			}
			if(j.first==g[i].back()){
				g[i].pop_back();
				h[i].pop_back();
			}
			g[i].push_back(j.first);
			h[i].push_back(j.second);
		}
	}
	scanf("%d",&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		if(dep[x]<10){
			printf("%d\n",dfs1(x,y,0));
		}else{
			printf("%d\n",dfs2(x,y,0));
		}
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：Union_Find (赞：1)

第一眼，树上背包，秒了。

第二眼，$1 \le n \le 2^{18},L \le 10^5$，我被秒了。

注意到这题 $n$ 的范围很诡异，是 $2^{18}$，而且二叉树的构造是满二叉树，所以时间复杂度应该是 $2$ 的若干次方乘上一个东西。

注意到，一个点的深度不超过 $\log n$，即 $18$。如果只有一次询问，我们可以爆搜出结果，但是这题有 $m$ 次询问。

想了 $60 \times 5$ 秒，想到了一个思路。像这种有两种解法，但是不管哪种解法都无法通过，我们就可以融合一下。具体的，在这题里面，我们有背包和爆搜两种解法，时间复杂度分别是 $O(nL)=O(2^{dep_u}L)$ 和 $O(2^{dep_u}m)$ 的。但是我们发现，其实我们只要把 $dep_u$ 分成两段，前 $2^{\frac{dep_u}{2}}$ 使用背包预处理，后一部分对于每个询问爆搜。这样子时间复杂度就只有 $O(2^{\frac{dep_u}{2}}L + 2^{\frac{dep_u}{2}}m)$ 了。我们可以直接取 $9$ 为 $\frac{dep_u}{2}$，可以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 300005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const ll B = 100000;
ll n = rd(), sqn, v[N], w[N], lg[N], f[(1 << 9) + 5][N], u, m;
ll dfs(ll x, ll sv, ll sw, ll u){
	if (sw > m) return 0;
	if (!u || x > 9) return sv + f[u][m - sw];
	return max(dfs(x + 1, sv, sw, u / 2), dfs(x + 1, sv + v[u], sw + w[u], u / 2));
}
int main(){
	sqn = (1 << 9);
	for (int i = 1; i <= n; i++) v[i] = rd(), w[i] = rd();
	for (int j = w[1]; j <= N; j++) f[1][j] = v[1];
	for (int i = 2; i <= min(n, sqn); i++) for (int j = 0; j <= B; j++)
		f[i][j] = max(f[i / 2][j], j >= w[i] ? (f[i / 2][j - w[i]] + v[i]) : 0);
	for (int T = rd(); T--;){
		u = rd(), m = rd();
		printf ("%lld\n", dfs(1, 0, 0, u));
	}
	return 0;
}

```

---

## 作者：RainySoul (赞：1)

### 题意

给定一颗以 $1$ 为根节点的完全二叉树，每个点有价值 $v_i$ 与权重 $w_i$，求在 $u$ 及其祖先内任意选点，在选择点权重和不超过 $L$ 的情况下最大化收益。

### 思路

显然是一个背包题，但是你直接上个背包是 $O(q \log nL)$ 的，T 飞了，由于是一颗完全二叉树而 $n < 2^{18}$，因此整棵树最多 $18$ 层，爆搜要到的点最多 $18$ 个，但是直接搜也是爆的。

既然分开无法通过，就合起来试一试！

对于前 $9$ 层的点你跑背包，对于后 $9$ 层的点你爆搜搜到前 $9$ 层就停。背包预处理是 $2^9 \times L$ 的，而后面爆搜是 $2^9 \times q$ 的，可以通过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=(1<<18)+10,M=100010;
int n,dp[520][M],w[N],v[N];
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int dfs(int x,int now){
	if(x<512)return dp[x][now];
	int res=0;
	if(w[x]<=now)res=v[x]+dfs(x/2,now-w[x]);
	res=max(res,dfs(x/2,now));
	return res;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)v[i]=read(),w[i]=read();
	for(int i=1;i<=512;i++){
		for(int j=0;j<=1e5;j++)dp[i][j]=dp[i/2][j];
		for(int j=1e5;j>=w[i];j--){
			dp[i][j]=max(dp[i][j],dp[i][j-w[i]]+v[i]);
		}
	}
	int q=read();
	while(q--){
		int a=read(),L=read();
		cout<<dfs(a,L)<<'\n';
	}
	return 0;
}
```

---

## 作者：__3E24AC7002AD9292__ (赞：1)

$\Theta(nL)$ 做法是显然的，对每个点跑背包，考虑预处理答案，直接从父节点转移。

另一种做法是直接暴力 $2^{\log(n)}$ 单次查询，枚举每个节点是否被选中，这样做法复杂度 $\Theta(2^{\log(n)}q)$。

考虑根号分治，只预处理前 $V$ 个节点背包后的结果，当查询的 $x\leq V$ 时直接返回背包得到的结果，否则考虑不断让 $x$ 跳父亲，每次跳到编号 $>V$ 的节点就枚举一下是否被选中，然后暴力过程记录背包剩余容量，跳到 $\leq V$ 的节点直接利用背包的值计算。复杂度 $\Theta(VL+2^{\frac{\log(n)}{\log(V)}}q)$，取 $V=\sqrt n$ 最优。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=(1ll<<18)+5,V=511,M=100005;
int n,v[N],w[N],q,mx,ans[N],dp[V][M];
int solve(int x,int l){
    if (l<0) return -1e18;
    if (x<=V) return dp[x][l];
    return max(solve(x>>1,l),solve(x>>1,l-w[x])+v[x]);
}
int main(){
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>v[i]>>w[i];
    cin>>q;
    for (int i=1;i<=min(V,n);i++){
        for (int j=0;j<M;j++)
            dp[i][j]=dp[i/2][j];
        for (int j=M-1;j>=w[i];j--)
            dp[i][j]=max(dp[i][j],dp[i][j-w[i]]+v[i]);
    }
    while (q--){
        int x,l;
        cin>>x>>l;
        cout<<solve(x,l)<<'\n';
    }
    return 0;
}
```

---

## 作者：Z_AuTwT (赞：0)

## 思路

题意其实就是在树上跑一个 01 背包。我们正常的对这个东西跑 01 背包的话肯定复杂度是超了的。

我们考虑 01 背包的搜索写法，可以发现在搜索树中有很多重复的部分，为了减少搜索量，考虑折半搜索。

直接把所有物品先找出来，然后折半搜索。

正常的想法应该都是对于两半都跑搜索，但你会发现如果是这样就需要加一个树状数组来维护前一半的答案，会增加复杂度，虽然在洛谷可以过，但可以被卡。

我们考虑优化，前一个做法劣在维护答案，那我们可以考虑对前一半进行动态规划，后一半进行搜索，这样就可以不用树状数组了。

## code

```c++
#include<bits/stdc++.h>
#define LL false
#define FST true
#define DEBUG false
#define FIO false
#define STD true
#define IOS false
#define unGet false
#define I128 false

#if STD
using namespace std;
#endif

#if LL
	#define int long long
#endif

#if I128
	#define int __int128
#endif

#if FST
	#define flush() fwrite(obuf,1,O-obuf,stdout)
	#define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
	char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
	inline int read() {
		register int x=0,f=1;
		register char ch=getchar();
		while(!(ch>='0'&&ch<='9'))
			ch=getchar();
		while(ch>='0'&&ch<='9') 
			x=x*10+(ch^48),ch=getchar();
		return x*f;
	}
	inline void write(register int x){
	    if(x>9) 
			write(x/10);
	    putchar((x%10)^48);
	}
	struct Flush{
	    ~Flush(){flush();}
	}_;
	#if unGet
		#undef getchar
	#endif
#else
	inline int read(){
		int x;
		cin>>x;
		return x;
	}
	inline void write(register long long x){
		cout<<x;
	}
#endif

bool st;
int v[1<<18],w[1<<18],dp[610][100010],n,q;
int dfs(int x,int L){
    if(x<=512)//在前一半的位置直接返回dp值
        return dp[x][L];
    if(L>=w[x]) //向下搜索
        return max(dfs(x>>1,L),dfs(x>>1,L-w[x])+v[x]);
    else 
        return dfs(x>>1,L);
}
bool ed;
signed main(){
	#if IOS
	std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0);
	#endif
	#if FIO
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	#endif
	n=read();
    for(register int i=1;i<=n;++i)
        v[i]=read(),w[i]=read();
    for(register int i=1;i<=512;++i)//预处理dp
        for(register int j=100000;j>=1;--j){
            dp[i][j]=dp[i>>1][j];
            if(j>=w[i])
                dp[i][j]=max(dp[i][j],dp[i>>1][j-w[i]]+v[i]);
        }
    q=read();
    while(q--){
        int x=read(),L=read();
        write(dfs(x,L)),putchar('\n');
    }
	#if DEBUG
	cerr<<1.00*clock()/CLOCKS_PER_SEC<<" s\n";
	cerr<<abs(&st-&ed)/1024.00/1024.00<<" MB";
	#endif
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 思路

由于这是一棵完全二叉树，并且 $n \le 2^{18}-1$，所以深度只有 $18$ 层。

考虑根号分治，背包预处理前 $512$ 个点到根这条链上的答案。

查询的时候如果编号小于 $512$，就直接输出。否则，后面的层数也很小，直接拼上预处理的答案，再爆搜就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define debug(x) cout<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=3e5+5,V=1e5+5;
int n;
int q;
int B;
int v[N],w[N];
int dp[520][V];
int a[N],top;
void init(){
	for(int i=1;i<=B;i++){
		for(int j=i;j>=1;j/=2){
			for(int k=V-5;k>=w[j];k--){
				dp[i][k]=max(dp[i][k],dp[i][k-w[j]]+v[j]);
			}
		}
	}
}
inline int ask(int x,int y){
	top=0;
	int au=0,ans=0;
	while(x>=1){
		a[++top]=x;
		if(x<=B&&!au) au=top; 
		x/=2;
	}
	au--;
	for(int bit=0;bit<(1<<au);bit++){
		int nv=0,nw=0;
		for(int i=1;i<=au;i++){
			if(bit&(1<<(i-1))) nv+=v[a[i]],nw+=w[a[i]];
		}
		if(nw>y) continue;
		int lw=y-nw;
		ans=max(ans,nv+dp[a[au+1]][lw]);
	}
	return ans;
}
signed main(){
	IOS;
	cin>>n;
	B=(int)sqrt((double)n);
	for(int i=1;i<=n;i++) cin>>v[i]>>w[i];
	init();
	cin>>q;
	for(int _=1,u,L;_<=q;_++){
		cin>>u>>L;
		cout<<ask(u,L)<<endl;
	}
	return 0;
}
```

---

## 作者：AC_love (赞：0)

有一些物品，每个物品有一个价值 $v$ 和花费 $w$，求在花费少于某个值时能选到的最大价值。这个问题大家都很熟悉，就是经典的 01 背包。

我们重温一下如何解决 01 背包问题，设 $f(i, j)$ 表示当前选到了第 $i$ 个物品，还剩下 $j$ 块钱。转移是：

$$f(i, j) = \max(f(i - 1, j), f(i - 1, j - w_i) + v_i)$$

树上做同理：

$$f(i, j) = \max(f(\lfloor \frac{i}{2}\rfloor, j), f(\lfloor \frac{i}{2}\rfloor, j - w_i) + v_i)$$

我们可以对整棵树做一遍 DP，时间复杂度 $O(NL)$，发现复杂度太高了，根本过不去。

那怎么办呢？

考虑 01 背包其实还有另一种解法：暴力枚举选哪些物品，复杂度 $O(2^n)$，其中 $n$ 是物品个数。

本题由于这棵树是个完全二叉树，所以树高不超过 $18$，对于单词询问，$O(2^n)$ 处理完全可行。但询问次数 $10^5$，似乎这个办法也陷入了绝境。

DP 和爆搜都不行，那我们该怎么办呢？

我们发现：DP 复杂度高的原因是树上节点太多，而爆搜复杂度高的原因是树的深度太深。

有没有办法平衡二者的复杂度，让 DP 处理比较少的节点，而爆搜也搜一下更浅的深度呢？

考虑从根节点往下，预处理出前 $k$ 层的 DP 数组，剩下 $18 - k$ 层爆搜处理。

询问一个叶子节点时，我们爆搜处理出 $2^{18 - k}$ 种情况，然后分别拿每种情况取对应上面的 DP 数组即可。

总复杂度大概是 $O(2^kL + 2^{18 - k}Q)$。

本题 $L, Q$ 同阶，$k$ 取 $9$ 或 $10$ 即可。

[code](https://atcoder.jp/contests/tokiomarine2020/submissions/59471446)

---

## 作者：Sirkey (赞：0)

[或许更好的阅读体验](https://www.cnblogs.com/sirkey2119/articles/18496318)

考试考到的签题。

注意到本题是一颗二叉树，同时 $n$ 只有 $2^{18}-1$ 个，也就是 $17$ 层。

如果我们对每一个询问，把他的祖先储存起来，只有 $17$ 个。

我们由此可以得到一个相对暴力的状压做法。

我们要优化这个状压做法，可以将采用根号分治。

其实思路非常流畅，当树高小于等于 $8$ 的时候是合理的，跟深的时候发现可以拆分成两半。一半预处理一半询问时算。

预处理前 $9$ 层的数，一共 $1023$ 个。对于每一个我们求，他和他的祖先花费 $i$ 的最大贡献。

得到转移：

$f_{i,j} = \max(f_{i/2,j-w_i} + v_i, f_{i/2,j},f_{i,j-1})$

对前 $9$ 层的求出答案，查询就 $O(1)$ 了。

后面的层数直接转呀，每一次情况求出花费 $sum1$  和贡献 $sum2$。

答案是 $f_{i,L-sum1} + sum$ 取最大值。 $i$ 是询问的数祖先从大向小第一个小于 $1023$ 的祖先。

另外空间还是要计算一下。我们 $f$ 数组开了 $1024 \times 10^5$ 的大小，所以不可以开 `long long`。

```
#include<bits/stdc++.h>
#define ll long long
#define debug(x) cout<<#x<<"[:]"<<x,puts("");
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define pb push_back
//
//
//
using namespace std;
inline ll read() {
	ll f = 0, t = 0;
	char c = getchar();
	while (!isdigit(c)) t |= (c == '-'), c = getchar();
	while (isdigit(c)) f = (f << 3) + (f << 1) + c - 48, c = getchar();
	return t ? -f : f;
}
void write(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int MX = 3e5 + 10;
const int MV = 1e5 + 10;
int W[1030][MV];
int w[MX], v[MX];
int h[30];
signed main() {
	ios::sync_with_stdio(0), cout.tie(0);
	int n = read();
	FOR(i,1,n) v[i] = read(), w[i] = read();
	FOR(i,1,1024) {
		FOR(k,1,MV - 10) if(k >= w[i]) W[i][k] = max(W[i][k], max(W[i/2][k - w[i]] + v[i], W[i/2][k]));
		else W[i][k] = max(W[i][k], W[i/2][k]);
		FOR(k,1,MV - 10) W[i][k] = max(W[i][k - 1], W[i][k]);
	}
	int Q = read();
	while(Q--) {
		int x = read(), L = read();
		if(x <= 1024) cout<<W[x][L]<<"\n";
		else {
			int ans = 0;
			int t = x, top = 0;
			while(t>1024) h[++top] = t, t/=2;
			FOR(sub,0,(1<<top) - 1) {
				int sum1 = 0, sum2 = 0;
				FOR(j,0,top - 1) if(sub&(1<<j)) sum1 +=  v[h[j + 1]], sum2 += w[h[j + 1]];
				if(L >= sum2) ans = max(ans, W[t][L - sum2] + sum1);
			}
			cout<<ans<<'\n';
		}
	}
	return 0;
}

```

——end——

---

## 作者：briquette (赞：0)

# 题目意思
讲的很清楚了，不需要过多描述。
# 思路
这道题目的思路很阴，但是想出来了就很好，有手就行的那种。\
所以这里重点描述思路：\
对于前面的 $512$ 个点，深度都不超过 $9$ 可以直接背包，这里大家都会。\
因为二叉树的性质，深度不超过 $18$，剩下的 $9$ 层每一次求解的时候可以跑 DFS 暴力，然后你就过了。\
纯思维，考想法，想到了就可以自己写代码了吧，这里给个简短的代码：
# Code
```cpp
#include<bits/stdc++.h>
#define dep(x) (int)log2(x)+1
using namespace std;
const int N=(1<<18)+9,M=1e5+9,K=1009;
int n,v[N],w[N],V,L,dp[K][M],q;
int dfs(int x,int y){if(y<0)return INT_MIN;if(dep(x)<=9)return dp[x][y];return max(dfs(x/2,y),dfs(x/2,y-w[x])+v[x]);}
int main()
{
    scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d%d",&v[i],&w[i]);scanf("%d",&q);
    for(int i=1;i<=n&&dep(i)<=9;i++)for(int j=1;j<=M-9;j++)dp[i][j]=(j>=w[i]?max(dp[i/2][j],dp[i/2][j-w[i]]+v[i]):dp[i/2][j]);
    while(q--)scanf("%d%d",&V,&L),cout<<(dep(V)<=9?dp[V][L]:dfs(V,L))<<'\n';
    return 0;
}
```

---

