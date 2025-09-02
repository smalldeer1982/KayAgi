# [POI 2005] DZI-Hollows

## 题目描述

在 Byteotia 有两棵非常高的树，而每一棵的树干上都被挖出了许多洞，高度各不相同。现在 $n$ 只可以飞得非常快的鸟决定住在这些洞里，它们中的一些互相认识因此它们想要访问认识的的鸟。鸟们飞得非常快，而且通常沿着一条直线走。为了避免在飞行中撞到别的鸟，它们决定找到某种居住的方式可以满足下面的条件：

- 任何的鸟都可以访问它认识的鸟，而使访问的路线不与其他鸟访问的路线相交（但是可以有同一个终点）.

此外，还要使每只鸟居住的高度尽量低，保证树洞比鸟多。

我们都知道鸟的大脑很小，所以它们请你帮它们算一共有多少个方法可以满足以上条件，将答案模 $k$ 输出。

## 样例 #1

### 输入

```
3 2 10
1 2
1 3```

### 输出

```
4```

# 题解

## 作者：EatBread (赞：2)

这题属实是有点阴间了，一道计数题，做的时候不能下载数据，不给大样例，题目的小样例约等于没有，再加上没有题解，直接给我调的妈妈生的。

于是做完决定写篇题解造福一下后人，虽然这题似乎怪冷门的。

~~再吐槽一下这个题面，哪个天才翻译的，我 ccf 要了！~~

### 形式化题面

给你一个一个 $n$ 个点 $m$ 条边的图（不一定联通，没有重边、自环），你需要将这些点分进两个点集里，每个点集内部不能有边，且两个点集之间没有交叉的边，问有多少种可能的分法，答案对 $k$ 取模。

#### 先初步观察一下

看数据范围，$n\leq 10^6$，$m\leq 10^7$ 很显然要求线性复杂度，然后我们发现这个 $m$ 大的有点离谱了（我觉得是般题人搞错了），看看能不能缩小。

然后可以发现一个性质，那就是**原图不能有环**，手玩几个有环的情况，发现确实，因为在有环的情况下会造成点集内部有边，不符合题意。

所以我们将 $m$ 缩小到了 $n-1$ 的范围（大于的话直接输出 $0$），再根据刚才的发现，我们可以得到一个显而易见的结论，**原图是森林**。 

#### 然后考虑答案为 $0$ 的情况

我们先不考虑森林，我们将每棵树独立出来考虑，众所周知，树是二分图，所以我们天然就可以将树上的点分为两个点集，且只能这么分，否则点集内部会有边，那么我们只需要考虑什么情况下两个点集之间会有交叉的边就可以了。

我们可以发现，在取最优情况下，叶子节点必不产生影响。因为叶子节点只对它的父亲之间有边，换言之，**它只链接另一个点集中的 $1$ 个点**，所以它十分的自由，可以避免与其他边的交叉。

然后我们观察一下去掉叶子节点后的树。

![](https://cdn.luogu.com.cn/upload/image_hosting/nsgb3b68.png)![](https://cdn.luogu.com.cn/upload/image_hosting/rzvdgx96.png)

可以发现，在符合条件的情况下，去掉叶子节点，树会变成一条链，于是大胆猜测，**在去掉叶子节点的情况下，如果树变成链，则可行，否则输出 $0$。**

采用反证法证明：如果树不构成链，则有点的度数 $\geq3$ 在每个点都有儿子的情况下（因为删去了叶子节点），这种情况显然会交叉，所以不可行。

所以我们可以得到判断输出是否为 $0$ 的代码（深搜实现）。


```cpp
void pd0(int u,int fa){
	int big=0;
	vis[u]=1;
	if(!is_leaf[fa])big++;//父亲也要算
	for(auto v:e[u]){
		if(v^fa){
			if(vis[v]){pd=0;}//出现环 
			if(!pd)break;
			if(!is_leaf[v])big++;
			pd0(v,u);	
		}
	}
	if(big>2)pd=0;//某个点的度>2 
}
```

#### 接着思考如何计算答案

很显然，直接计算森林是不可能的，所以我们需要将每棵树的贡献都算出来，最后用乘法原理计算最终答案就行。

根据判断 $0$ 我们得到了启发，那就是每棵树去掉叶子节点后是一条链，而链上任何点的顺序是改变不了的（除了反过来，我们待会再考虑），所以也就是说，只有去掉的那些叶子节点对答案产生了贡献。

而每个不同父亲的叶子节点之间也不可能产生贡献（否则一定交叉），所以我们只需要算每个点有几个儿子是叶子节点，然后将贡献乘在一起就好了。

发现一个很容易得出的结论：**同属一个父亲的叶子节点可以随意排列**，因为它们不管怎么放都对别的点没有影响。

所以根据小学就学过的知识，我们可以得出每一棵树的贡献的公式：$\prod\limits_{j=1}^{js_i}son_j!$，而答案的公式为 $tot!\times\prod\limits_{i=1}^{tot}\prod\limits_{j=1}^{js_i}son_{i,j}!$。

但这很显然不是最终的公式，我们还要考虑上文提到整棵树反过来的情况以及两个点集放哪一个的情况。

而很显然，每一棵树都有两种放法（有两个点集），而当树去掉叶子节点之后的链长 $\geq2$ 时我们就可以将树反过来放，给个图片配合理解一下。

链长 $<2$：只能有一种放法。

![](https://cdn.luogu.com.cn/upload/image_hosting/pu6n0mv0.png)

链长 $\geq2:$ 可以反过来放。

![](https://cdn.luogu.com.cn/upload/image_hosting/3whw9iz8.png)

所以需要额外加上这两种可能的贡献，然后写出代码。

```cpp
for(int i=1; i<=tot; i++){
		int res=2,p=0;
		for(auto j:d[i]){
			res=res*jc[leaf[j]]%mod;
			if(!is_leaf[j])p++;
		}
		if(p>1)res=res*2%mod;
		ans=ans*res%mod;
}
```
#### 特殊情况

交过之后就会发现，这玩意错的离谱，所以我们少考虑了一种情况，也就是单个点的情况。

单个点显然可以放在两个点集中的任何位置，因为它无论如何也不会与其他的边产生冲突，所以我们需要特判单个点的情况，最后再计算单个点的贡献，然后才能 A 了此题。

#### 总结&闲话

这题实话说并不难，~~真的不一定有紫~~，只是不给大样例且不能下载数据太阴间了，调了我好久~~为此弃掉了学校的 noip 模拟赛~~。

然后就是我闲着没事交了一发这个：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e4+5;
int n,m;
signed main(){
	cin>>n>>m;
	if(m>=n)cout<<0;
	else while(1);
	return 0;
}
```
得到了全 TLE 的好成绩，所以我觉得 $m$ 这么大是搬题人搞错了。

最后再吐槽一下题意，说的什么玩意。

~~其实我为了这篇题解又弃掉了模拟赛的评讲，我发现我在这题一共交了 25 发，写题解的欲望格外的大~~。

放一下代码吧，自己调计数题太折磨了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int n,m,k[N],mod,pd=1,vis[N],js[N];
vector<int>e[N],d[N];
int leaf[N],tot=0,is_leaf[N];
void dfs(int u,int fa){
	vis[u]=1,js[tot]++;
	int son=0,jl=fa;
	for(auto v:e[u]){
		if(!vis[v]){
			dfs(v,u);
			son++,jl=v;
		}
	}
	if(fa==0&&son==1||(!son))leaf[jl]++,is_leaf[u]=1;
	d[tot].push_back(u);
}
void pd0(int u,int fa){
	int big=0;
	vis[u]=1;
	if(!is_leaf[fa])big++;
	for(auto v:e[u]){
		if(v^fa){
			if(vis[v]){pd=0;}
			if(!pd)break;
			if(!is_leaf[v])big++;
			pd0(v,u);	
		}
	}
	if(big>2)pd=0;
}
int jc[N];
void ycl(){
	jc[0]=1;
	for(int i=1; i<=N-5; i++)jc[i]=jc[i-1]*i%mod;
}
signed main(){
	cin>>n>>m>>mod,ycl();
	if(m>=n){cout<<0;return 0;}
	int root=1;
	for(int i=1,u,v; i<=m; i++){
		scanf("%lld%lld",&u,&v);
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=1; i<=n; i++)if(!vis[i])tot++,dfs(i,0);
	memset(vis,0,sizeof vis),leaf[0]=0,is_leaf[0]=1;
	for(int i=1; i<=n; i++)if(!vis[i])pd0(i,0);
	if(!pd){cout<<0;return 0;}
	int ans=1,cnt=0;
	for(int i=1; i<=tot; i++){
		int res=2,p=0;
		if(js[i]==1){cnt++;continue;}
		for(auto j:d[i]){
			res=res*jc[leaf[j]]%mod;
			if(!is_leaf[j])p++;
		}
		if(p>1)res=res*2%mod;
		ans=ans*res%mod;
	}
	ans=ans*jc[tot-cnt]%mod;
	for(int i=n-cnt; i<n; i++)ans=ans*(i+2)%mod;
	cout<<ans;
	return 0;
}
```
完结撒花。

~~没有数据机更没对拍机~~。

---

## 作者：_Cheems (赞：0)

题意：有两棵树，每个树有无穷个不同的洞，需要将 $n$ 个鸟分配到不同的洞里。同时给出 $m$ 对关系，定义一种方案是合法的当且仅当将所有关系连线不交叉（可以同一个点），且连线必须在两棵不同的树间。认为两种方案不同当且仅当存在一只鸟在两种方案中位于不同的树上或同一棵树上相对位置不同。

题意真的恶心，不过应该能发现如下几点：

1. 应当为二分图，所以不能存在奇环。其实偶环也不行因为不可能调整至不交叉。

2. 连边构成若干连通块，除去孤立点，则连通块之间不能交叉，因此单独计算一种连通块的方案最后再乘起来。

手玩下感觉合法方案类似于一条链上长着一些菊花。对于任意一点，假如存在 $p$ 个相邻节点还与其它点连边，那么它们向外连边的方向不能一样且只能放在两侧，否则一定交叉，那么 $p>2$ 时无解。假如存在 $q$ 个相邻节点只与它相连，那么它们可以随意交换顺序所以乘上个阶乘然后扔掉。

一番调整后所有点度数 $\le 2$ 且连通，所以就是条链，假如节点数 $\ge 2$ 那么可以将链左右翻转得到不同方案，也就是乘个 $2$。方案也可以上下翻转再乘个 $2$。

所有连通块的方案乘起来再乘个阶乘，现在加入 $k$ 个孤立点，放在哪里都行，方案数为 $A^{gl}_{n+1}$。复杂度 $O(n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define NO {puts("0"); return 0;}
const int N = 1e6 + 5;
int n, m, mod, u, v, jc[N], ans, gl, whl, col[N];
bool cir;  
vector<int> to[N], fhr;

inline void dfs(int u, int from, int c){
	col[u] = c, fhr.push_back(u);
	for(auto v : to[u])
		if(!col[v]) dfs(v, u, 3 - c);
		else if(v ^ from) cir = true;
}
signed main(){
	cin >> n >> m >> mod;
	ans = jc[0] = 1;
	for(int i = 1; i < N; ++i) jc[i] = 1ll * jc[i - 1] * i % mod;
	for(int i = 1; i <= m; ++i) scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i)
		if(!col[i]){
			if(to[i].empty()) {++gl; continue;}
			cir = false, fhr.clear();
			dfs(i, 0, 1);
			if(cir) NO
			for(auto p : fhr){
				int cnt = 0;
				for(auto p2 : to[p]) if(to[p2].size() == 1) ++cnt, col[p2] = 3;
				ans = 1ll * ans * jc[cnt] % mod;
			}
			int cnt = 0;
			for(auto p : fhr){
				int du = 0;
				for(auto p2 : to[p])
					if(col[p] != 3 && col[p2] != 3) ++du;
				if(du > 2) NO
				cnt += col[p] != 3;	
			}
			if(cnt >= 2) ans = 2ll * ans % mod;
			ans = 2ll * ans % mod;
			++whl;
		}   
	for(int i = n + 2 - gl; i <= n + 1; ++i) ans = 1ll * ans * i % mod;
	cout << 1ll * ans * jc[whl] % mod;
	return 0;
}
```

---

