# Boboniu Walks on Graph

## 题目描述

Boboniu有一条n个点和m条边的有向图

每个点的出度最大为k

每一条边都有一个权值，没有两条边有相同的权值。

Boboniu喜欢在图上以某种特定的方式走路，这个方式可以表示为特定的集合$(c_1,c_2,\dots,c_k)$。如果他现在在的点的初度为$i$，那么他会走到u的出边中权值第$c_i$小的边

现在bobiniu要你计算所有满足下列条件的边数：
- 对于任意的i（$1 \leq i \leq k$），$1 \leq c_i \leq i$
- 对于任意的点u，按上述方式都可以走回自己

## 说明/提示

样例1有两种方案：(1,1,3)和(1,2,3)，图中蓝的边是boboniu决定走的边

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1394B/5474f0f6fffa7d56fd7564b7610d64e683f8dbda.png)

样例3只有一种方案：(1,2,2,2)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1394B/274580f276e993aef252a750c707d368ffc4c21a.png)

点的出度表示从这个点出去的边的条数

## 样例 #1

### 输入

```
4 6 3
4 2 1
1 2 2
2 4 3
4 1 4
4 3 5
3 1 6```

### 输出

```
2```

## 样例 #2

### 输入

```
5 5 1
1 4 1
5 1 2
2 5 3
4 3 4
3 2 5```

### 输出

```
1```

## 样例 #3

### 输入

```
6 13 4
3 5 1
2 5 2
6 3 3
1 4 4
2 6 5
5 3 6
4 1 7
4 3 8
5 2 9
4 2 10
2 1 11
6 1 12
4 6 13```

### 输出

```
1```

# 题解

## 作者：YLWang (赞：7)

有趣的题。

容易发现最终的要求就是所有点的入度为 1。

那么只要预处理出来一开始每一种类型的边会使哪些点的入度+1，最后枚举一下方案并 check 就行了。

有三种实现这个的方法。

- bitset。复杂度 $O(\dfrac{nk!}{w})$。大力卡常理论上可以过去。实际上由于 STL 的 bitset 常数过大会裂开来，需要手写。

- 考虑如果一个点入度大于等于 2 则不行。那么预处理出两两的互斥关系，最后 $O(k^2)$ check 就可以了。

- Hash。给每个点赋随机权值，最后检查和。简单好写但会被叉。

代码就不放了，挑一种实现即可，极其容易。

---

## 作者：Rainbow_qwq (赞：5)

[CF1394B Boboniu Walks on Graph](https://www.luogu.com.cn/problem/CF1394B)

---

一开始想暴力，总共 $9!=362880$ 种情况，每一种 $O(n)$ 暴力找环，肯定过不去。

分析一下特殊性质。

首先，在每种情况下，每个点肯定只有一条出边，又要求点 $u$ 出发能回到自己，那图上只能是一大堆环。

所以每个点只有一个入度，假设 $i$ 的出边到达 $p_i$ ，那么 $p_1,p_2,\dots,p_n$ 一定是 $1,2,\dots,n$ 的一个排列。

可以 **哈希** 快速判断。

把点按出度分成 $k$ 类，预处理一下 $sum(i,j)$ 表示 $c_i=j$ ，出度为 $i$ 的所有点都走第 $j$ 边，所到达的所有点的集合的 hash 值。

如何对集合 hash，可以借鉴一下 [P6688](https://www.luogu.com.cn/problem/P6688) 的搞法。

最后 $O(k!)$ 暴力 dfs 一下算出集合并集的 hash 值是否等于 $\{1,2,\dots,n\}$ 的哈希值。

（我 CF 写单哈希居然没被卡 qwq

Code ~~有点丑~~
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define int long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define x first 
#define y second
#define pb push_back
#define mkp make_pair
#define maxn 200005
typedef pair<int,int>pii;
int res,n,m,k;
vector<pii>e[maxn];
vector<int>v[13];
const int b1=19491001;
unsigned long long pw[maxn],sumn,sum[13][13],qwq;
void dfs(int u)
{
	if(u==k+1){
		res+=(qwq==sumn);
		return;
	}
	For(i,0,u-1){
		qwq+=sum[u][i];
		dfs(u+1);
		qwq-=sum[u][i];
	}
}
signed main()
{
	n=read(),m=read(),k=read();
	pw[0]=1;
	For(i,1,n)pw[i]=pw[i-1]*b1,sumn+=pw[i];
	For(i,1,m){
		int u=read(),v=read(),w=read();
		e[u].pb(mkp(w,v));
	}
	For(i,1,n)sort(e[i].begin(),e[i].end()),
				v[e[i].size()].pb(i);
	For(i,1,k)
		For(j,0,i-1){
			unsigned long long now=0;
			for(int p=0;p<v[i].size();++p)
				now+=pw[e[v[i][p]][j].y];
			sum[i][j]=now;
		}
	dfs(1);
	cout<<res;
    return 0;
}
```

---

## 作者：rizynvu (赞：2)

考虑先分析最后的图会长成什么样。  
因为每个点都只会连出一条有向边，且最后还能走回自己。  
所以可以知道的是图会有许多个环来组成，且每个环都无交。

但是这个判定条件明显不是很优秀，考虑继续转化。  
考虑到对于一个有向环，每个点的出度和入度都需要为 $1$。  
那么出度为 $1$ 题目本身就要求满足了，所以实际上只需要使得每个点的入度都为 $1$ 就可以了。

那么继续转化，考虑反面，那就是要求不存在点的入度 $> 1$。  
（为什么不考虑入度 $= 0$ 的？因为边数总共为 $n$，有入度为 $0$ 就一定有入度 $> 1$ 的。）

那么就比较好做了，处理出一个点 $v$ 对应的入边 $(u, v, w)$ 在 $u$ 处对应的出边的排名和 $u$ 的入度，表示为二元组 $(rk_{(u, v, w)}, deg_u)$。  
那么对于两条入边 $(u, v, w)$ 和 $(u', v, w')$，就要求这两条边对应的二元组 $(rk_{(u, v, w)}, deg_u), (rk_{(u', v, w')}, deg_{u'})$ 不能同时被选中。

那么因为总共的二元组个数不超过 $1 + 2 + \cdots + 9 = 45$ 个，可以直接二进制压缩。  
用 $f_u$ 表示选了 $u$ 就不能选的二元组的集合，可以通过每一个点 $v$ 的情况推出。

那么就可以直接爆搜，每次选出一个出度对应的二元组后判断是否会产生冲突即可。

时间复杂度 $\mathcal{O}(nk\log k + k!)$。

```cpp
#include<bits/stdc++.h>
using ll = long long;
constexpr int maxn = 2e5 + 10;
constexpr int pre[10] = {0, 0, 1, 3, 6, 10, 15, 21, 28, 36};
inline int id(int x, int y) {
   return x + pre[y];
}
int n, m, k;
std::vector<std::pair<int, int> > to[maxn];
int c[maxn][45];
ll f[maxn], g[45];
int ans;
void dfs(int d, ll mask) {
   if (d > k) {
      return ans++, void();
   }
   for (int i = 0; i < d; i++) {
      if (g[id(i, d)] & (mask | (1ll << id(i, d)))) continue;
      dfs(d + 1, mask | (1ll << id(i, d)));
   }
}
int main() {
   scanf("%d%d%d", &n, &m, &k);
   for (int x, y, z; m--; ) {
      scanf("%d%d%d", &x, &y, &z);
      to[x].emplace_back(z, y);
   }
   for (int i = 1; i <= n; i++) {
      std::sort(to[i].begin(), to[i].end());
      for (int j = 0; j < to[i].size(); j++) {
         int v = to[i][j].second, w = id(j, to[i].size());
         c[v][w]++;
         f[v] |= 1ll << w;
      }
   }
   for (int i = 1; i <= n; i++) {
      for (int w = 0; w < 45; w++) {
         if (f[i] >> w & 1ll) {
            g[w] |= f[i] ^ ((ll)(c[i][w] == 1) << w);
         }
      }
   }
   dfs(1, 0);
   printf("%d\n", ans);
   return 0;
}
```

---

## 作者：_Freedom_ (赞：2)

[题面](https://www.luogu.com.cn/problem/CF1394B)

发现 $k$ 很小，考虑枚举 $(c_i,c_2, \cdots,c_k )$。

稍微思考后发现，若 $(c_i,c_2, \cdots,c_k )$ 确定下来了，则图中的边也确定了。其中每个点的出度都为 $1$，要求每个点都可以回到自己，那么当且仅当图中剩下的 $n$ 条边构成了一些**环**。

发现这个条件等价于在最后的图中，每个点的入度都为 $1$，那么考虑维护最终选出来的边指向的点的集合是否为 $\{ 1 \cdots n\}$。
 
考虑类似**哈希**的做法。

为每个点附上一个**随机权值**，如果最后所有边指向的点的异或和等于 $1 \cdots n$ 的异或和，那么可以近似认为选出的点的集合为 $\{ 1 \cdots n \}$。

具体做法先预处理出数组 $s_{i,j}$ 表示 $c_i=j$ 时的所有出度为 $i$ 的点指向的点的权值异或和，然后枚举每个 $(c_i,c_2, \cdots,c_k )$，计算 $s_{i,c_i}$ 的异或和是否等于 $1 \cdots n$ 的异或和即可。

时间复杂度 $O(nk^2+k!)$。

~~顺带一提，这种异或随机权值的哈希几乎卡不掉~~

$code$

```cpp
# include <bits/stdc++.h>

using namespace std;

void read(int &x){
	static char c=getchar();
	int f=1;
	x=0;
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+(c^'0');
		c=getchar();	
	}
	x*=f;
}

const int N=200010;

typedef pair<int,int> pii;

int val[N],sum;

int dee[N];

vector <pii> e[N];

int k,s[10][10],ans;

void dfs(int x,int ss){
	if(x==k+1){
		if(ss==sum) ans++;
		return ; 	
	}
	for(int i=1;i<=x;i++) dfs(x+1,s[x][i]^ss);
}

int main(){
	
	srand(time(0));

	int n,m,u,v,w;
	
	read(n),read(m),read(k);
	
	for(int i=1;i<=n;i++) {
		val[i]=(1ll*rand()<<15)+rand();
		sum^=val[i];
	}
	
	for(int i=1;i<=m;i++){
		read(u),read(v),read(w);
		e[u].push_back(pii(w,v));
		dee[u]++;
	}
	
	for(int i=1;i<=n;i++) sort(e[i].begin(),e[i].end());
		
	for(int i=1;i<=k;i++){
		for(int j=1;j<=i;j++){
			for(int u=1;u<=n;u++){
				if(dee[u]==i) s[i][j]^=val[e[u][j-1].second];				
			}
		}
	}

	dfs(1,0);
	
	printf("%d\n",ans);

	return 0;	
}
```


---

## 作者：intel_core (赞：1)

要让每个点都能走回自己，就等价于每个点都在环上，也等价于每个点的入度恰好为 $1$。

很明显答案最多是 $9!=362880$，然后很自然的想到暴力检查，很明显因为点太多过不了。

我们换一种思路，令点对 $(x,y)$ 代表 $c_x=y$ 这个状态，那么状态数就是 $1+2+\cdots+9=54$ 个。

首先，我们先处理出每个点的出度，再把一个点的出边排个序。

然后检查每个状态，把所有出度为 $x$ 的点连出的第 $y$ 条边连向的点拿出来，看一看有没有重复的。

判断 $(x_1,y_1)$ 和 $(x_2,y_2)$ 是否冲突，直接枚举复杂度是 $O(k^2n)$ 的，莽不过去。

换个思路，我们把每个点的入边拿出来，记录边的起点的度数和这是第几条边，不难发现这构成了一个状态 $(x,y)$。

把每个点存好的状态两两之间标记无法共存，最后直接大力枚举 $9!$ 种情况。

因为一个点的入边可能有很多，注意要把状态去个重。

总的复杂度 $O(k^2\times k!+n)$。

---

## 作者：Cry_For_theMoon (赞：1)

[传送门](https://codeforces.ml/contest/1394/problem/B)

$k\le 9$ 不用想都是入手点。一个显然的想法是 $dfs$ 所有的 $c$ 最多也只有 $9!$ 种。如果我们能在不差于 $O(\log n)$ 的时间内判断就可以了。

考虑到确定了 $c$ 以后，整个图就是一个每个点为起点有且仅有一条边的 $n$ 边有向图。同时要求每个点都在至少一个简单环内。容易得到：

结论：每个点的入度也恰好为一。

证明：首先 $\sum in(i)=\sum out(i)=n$  这个没有问题，然后考虑某个点的入度不能为 $0$，因为这样它就不可能回到自身。同时某个点的入度不能大于 $1$，因为这样就会让另外某个点的入度为 $0$. 证毕。

同时考虑预处理 $S(i,j)$ 代表如果 $c_i=j$，所有原图上出度为 $i$ 的点下一步会走到的点所构成的多重集。那么点集 $S$ 应该满足 $S=\sum S(i,c_i)=\{n \cdot 1\}$ . 考虑快速判断集合之间的相等以及快速处理集合的相加，可以想到对集合进行哈希。姿势可以参考[无论怎样神树大人都会删库跑路](https://www.luogu.com.cn/problem/P5270)这一道题。具体说来，我们指定一个质数 $base$ 作为基数。一个点 $i$ 的贡献是 $base^i$. 容易发现这样的话直接把哈希值相加就实现了集合的相加。BTW，这里模数采用自然溢出，为了减少被卡的几率，我们做双模数哈希，$base_1=13331,base_2=998244353$ 减少 WA 几率。（竟然跑的飞快）。

```C++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2e5+10;
const ull base1=13331,base2=998244353; 
vector<pi>edge[MAXN];
int n,m,k,ans;
ull power1[MAXN],power2[MAXN];
ull hash1[10][10],hash2[10][10];
ll val1,val2,tgt1,tgt2;
void dfs(int r){
	if(r==k+1){
		if(val1==tgt1 && val2==tgt2)ans++;
		return;
	}
	rep(i,1,r){
		//枚举c[r]
		val1+=hash1[r][i]; 
		val2+=hash2[r][i];
		dfs(r+1);
		val1-=hash1[r][i];
		val2-=hash2[r][i];
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,m){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);edge[u].pb(mp(w,v));
	}
	rep(i,1,n){sort(edge[i].begin(),edge[i].end());}
	power1[0]=power2[0]=1;rep(i,1,n)power1[i]=power1[i-1]*base1,power2[i]=power2[i-1]*base2;
	rep(i,1,n)tgt1+=power1[i],tgt2+=power2[i];
//	printf("%llu %llu\n",tgt1,tgt2);
	rep(i,1,k){
		rep(j,1,i){
			//当c[i]为j时产生的点集
			//printf("c[%d]:%d\n",i,j);
			rep(x,1,n){
				if(edge[x].size()!=i)continue;
				hash1[i][j]+=power1[edge[x][j-1].se];
				hash2[i][j]+=power2[edge[x][j-1].se];
			//	printf("%d->%d\n",x,edge[x][j-1].se);
			} 
		}
	}
	dfs(1);
	printf("%d",ans);
	return 0;
}

```





---

## 作者：寒鸽儿 (赞：0)

观察性质可以发现 , 任何一个tuples下每个点有至多一条出边。所有可能的情况是基环内向森林或者一堆环(或者一个)。  

满足条件的显然是环的情况。  

一堆环的特殊性质在于 , 每个点的入度和出度均为 $1$ 。

考虑将入点按照边的位次统计成集合。  

如果枚举tuple , 然后匹配入点集合与 $\{1, 2, \cdots, n\}$ 是否相同 , 显然是会T的。  

据说使用bitset优化匹配集合的过程 , 大力卡常是可以过的。  

然而有一种更优秀的方法。

集合的相同性可以用hash来判断 , 支持集合并 , 这样就比较集合可以做到 $\mathcal{O(1)}$ 的时间复杂度。  

注意到集合的相同性取决于集合的元素值的大小而非顺序 , 所以根据集合元素大小设计hash函数。  
$$
f(S) = \sum_{a_i \in S} base^{a_i}
$$
base可以取一些小质数。  

在模意义下判断hash函数值即可近似认为集合等价。  

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct edge {
    int x, w;
    edge() {}
    edge(int x, int w): x(x), w(w) {}
};
typedef vector< vector<edge> > Graph;

const int Mod = 998244353;

inline int Inc(int a, int b) {
    return (a += b) >= Mod ? a - Mod : a;
}
inline int Dec(int a, int b) {
    return (a -= b) < 0 ? a + Mod : a;
}
inline int Mul(int a, int b) {
    return 1ll * a * b % Mod;
}

const int base = 3, maxn = 200010;

int Pow[maxn], hsh[15][15], tp[15], stdd = 0, ans = 0, k;

void dfs(int depth) {
    if(depth == k + 1) {
        int cur = 0;
        for(int i = 1; i <= k; ++i) cur = Inc(cur, hsh[i][tp[i]]);
        if(cur == stdd) ++ans;
        return ;
    }
    for(int i = 1; i <= depth; ++i) {
        tp[depth] = i;
        dfs(depth + 1);
    }
}

Graph G;

int main() {
    int n, m, u, v, w;
    cin >> n >> m >> k;
    G.resize(n + 1);
    for(int i = 1; i <= m; ++i) {
        cin >> u >> v >> w;
        G[u].push_back(edge(v, w));
    }
    Pow[0] = 1; for(int i = 1; i <= n; ++i) Pow[i] = Mul(Pow[i-1], base);
    for(int i = 1; i <= n; ++i) {
        sort(G[i].begin(), G[i].end(), [&](edge& a, edge&b){ return a.w < b.w; });
        int s = G[i].size();
        for(int j = 0; j < s; ++j)
            hsh[s][j + 1] = Inc(hsh[s][j + 1], Pow[G[i][j].x]);
    }
    for(int i = 1; i <= n; ++i) stdd = Inc(stdd, Pow[i]);
    dfs(1);
    cout << ans << endl;
    return 0;
}
```

---

