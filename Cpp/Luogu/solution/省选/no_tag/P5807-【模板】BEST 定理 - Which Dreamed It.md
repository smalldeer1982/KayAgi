# 【模板】BEST 定理 | Which Dreamed It

## 题目背景

请注意本题与真正的 BEST 定理略有出入：BEST 定理没有从 $1$ 出发的限制，且回路的边序列是循环同构的。

## 题目描述

有 $n$ 个房间，每个房间有若干把钥匙能够打开特定房间的门。

最初你在房间 $1$。每当你到达一个房间，你可以选择该房间的一把钥匙，前往该钥匙对应的房间，并将该钥匙丢到垃圾桶中。

你希望最终回到房间 $1$，且垃圾桶中有所有的钥匙。

你需要求出方案数，答案对 $10^6 + 3$ 取模。两组方案不同，当且仅当使用钥匙的顺序不同。

注意，每把钥匙都是不同的。

原 BZOJ3659。

## 说明/提示

### 样例解释

* 样例 $1$ 说明

在第一组样例中，没有钥匙，则方案数为 $1$。

在第二组样例中，你不可能使用第二个房间的钥匙，所以方案数为 $0$。

* 样例 $2$ 说明

只要使用完所有的钥匙即可，不一定要经过所有的房间。

* 样例 $3$ 说明

前三组数据在取模前的答案分别是 $2,190080,49476320425715737559040000000$。

### 数据范围

对于 $50\%$ 的数据，$n \le 4$，$\sum s \le 30$。

对于 $100\%$ 的数据，$1 \le T \le 15$，$1 \le n \le 100$，$0 \le \sum s \le 3141592$。

2021/5/14 加强 by [SSerxhs](https://www.luogu.com.cn/user/29826)&[滑大稽](https://www.luogu.com.cn/user/203743)

## 样例 #1

### 输入

```
2
1
0
2
1 1
1 2
```

### 输出

```
1
0
```

## 样例 #2

### 输入

```
5
3
1 2
1 3
1 2
3
1 2
1 1
0
3
1 2
1 1
1 3
3
1 2
1 3
1 1
3
0
0
0```

### 输出

```
0
1
0
1
1
```

## 样例 #3

### 输入

```
4
6
1 4 
1 4 
1 2 
2 5 5 
2 3 1 
0 
7
2 6 5 
3 3 6 1 
4 4 2 4 5 
3 3 7 2 
4 6 3 1 6 
4 4 2 5 5 
1 3 
10
7 8 9 2 6 7 9 6 
5 6 10 5 1 3 
5 5 7 7 9 6 
4 5 7 9 7 
4 1 2 7 9 
6 4 10 8 1 10 3 
8 2 3 4 10 5 1 3 8 
7 7 10 6 1 2 3 7 
8 8 8 10 2 4 4 6 1 
6 9 8 1 8 9 9 
15
11 10 10 10 11 2 13 10 8 14 9 14 
9 5 3 10 1 15 11 8 13 11 
7 1 15 13 7 15 8 5 
7 8 14 7 1 2 3 8 
3 11 4 10 
7 7 12 7 4 12 11 12 
10 10 12 3 13 15 1 2 8 11 12 
12 9 4 13 10 2 6 13 10 7 6 7 11 
6 4 1 2 8 12 1 
15 1 11 9 9 7 7 6 6 2 8 12 2 8 12 2 
10 12 10 6 10 3 1 6 3 9 4 
12 15 14 10 14 14 9 8 7 7 11 13 4 
7 12 3 10 6 1 1 4 
6 12 5 8 3 8 12 
5 10 10 1 11 2 
```

### 输出

```
2
190080
120594
887148
```

# 题解

## 作者：约瑟夫用脑玩 (赞：23)

欧拉图相关中唯一需要点证明的东西，我尝试从偏理解的角度出发但不失严谨。

## 题意

给你一个有向图，求从 $1$ 出发的欧拉回路的方案数。

两种回路不同当且仅当边序列中某一位置两序列中的边不同。

## 解法

首先这得是个欧拉图才能有欧拉回路，判定结论是入度等于出度。

证明的话必要性显然，$1$ 有出必有入，其他点有入必有出。

充分性的话用套圈证明，先随便走一个回路，可能导致有些边没走到，再走那些没走过的边走一个回路，当成一个圈套进当前回路直至套完所有边。

那么当前图是欧拉图了，我们考虑计数回路方案。

先考虑不好计数的地方在哪里：

![](https://cdn.luogu.com.cn/upload/image_hosting/ac58mtvj.png?x-oss-process=image/resize,m_lfit,h_170,w_175)

比如这个图，第一次走到 $3$ 的时候就只能走 $3\to 4$ 而不能走 $3\to 1$。

显然问题在于不加限制的走的话可能走了一条当前图的割边导致图不连通，那么我们需避开这些边，但这使得计数十分困难，我们需要寻求一种平凡的方式来避开这些边。

考虑一条欧拉回路，发现对于除了 $1$ 号点的节点的最后一条出边是特别的。

具体来说，将他们都拿出来一定不会形成环。

------------

证明：

假设成了环：

![](https://cdn.luogu.com.cn/upload/image_hosting/8ungjrwd.png?x-oss-process=image/resize,m_lfit,h_170,w_175)

图一直满足半欧拉图的度数性质，如果取出的边形成了环，由于 $x_1\to x_2$ 已经是 $x_1$ 的最后一条出边，那么不可能还有入边，故一定不会有 $x_m\to x_1$ 这条边。

------------

考虑除了 $1$ 都有出边且不会形成环的图是什么？内向树啊！所有我们得到结论，一个欧拉图通过取出每个节点的最后一条出边得到一棵内向树。

实际上可以证明，将结论反过来是成立的，即一个欧拉图的每个点都以一个内向树上的边为最后一条出边时，其他怎么走都可以形成一个欧拉回路。

------------

证明：

设内向树上 $x$ 指向的节点为 $fa_x$。

对于一条边 $x\to y$，如果它不是割边，说明还有路径 $y\to x$。

对于一张对于当前的半欧拉图（或欧拉图）来说，走过过后的度数一定仍然满足半欧拉图的性质，同时连通性也可以保证，那么还是一张半欧拉图，直到走完所有边。

而除了在内向树上的边，其他边都不可能成为割边。

因为走了 $x\to y$ 后起码还有 $x\to fa_x\to fa_{fa_x}\to\dots\to 1$ 的路径，同时也有 $y\to fa_y\to fa_{fa_y}\to\dots\to 1$ 的路径。

那么 $x,y$ 还是连通的，故只有 $x\to fa_x$ 时才可能导致 $x,y$ 不连通，由于内向树上的边 $x\to fa_x$ 为 $x$ 的最后一条出边，所以 $x$ 已经成为了一个孤立点，没有关系。

------------

那么我们钦定一棵内向树，然后对于其他边任意定顺序，一定**唯一**对应了一个欧拉回路。

这样的计数得到的一组方案是唯一对应一条欧拉回路的，充分性有了，必要性呢？

显然也有，我们才证明了对于每条欧拉回路都能拿出最后一条出边得到一棵内向树，其他边依次定顺序即可对应计数**唯一**的一种方案。

所以计数的答案就是：$ans=\sum_{T\text{是原图的一棵内向树}}\text{任意定顺序走出一条欧拉回路的方案数}$

只剩下随意走的方案数了，对于每个点 $x$，第 $i$ 次经过它时会带来 $du'_ x-i+1$ 种不同的方案，即从 $du'_ x-i+1$ 条出边中任选一条走都是不同的方案。

那么一个点 $x$ 对方案的总贡献贡献就是 $du' _ x!$，所有点的贡献就是 $\prod_xdu'_ x!$。

注意 $du' _ x$ 表示除掉内向树上的边以外的出度，设原图节点 $x$ 的出度为 $du_x$，发现不管内向树长什么样 $du'$ 总不变，均为 $du' _ x=du_x-[x\neq1]$

所以 $ans=\sum_{T\text{是原图的一棵内向树}}\prod_xdu'_ x!=(\text{内向树个数})\times(\prod_{x=2}^n{(du_x-1)!}\times du_1!)$。

内向树个数可以用矩阵树定理求，这道题除了判断一开始是否为欧拉图外没什么坑点，[随便写写](https://www.luogu.com.cn/paste/9ehs6eul)就完了。

## BEST 定理

讲了这么多不顺便把 $\text{BEST}$ 定理讲了可惜了，这个定理求的是一个有向图的欧拉回路的数量。

和这道题有什么区别？没有从 $1$ 出发的区别，即一个回路的边序列是循环同构的。

考虑以 $1$ 为起点求出的回路被重复计数了多少次，我们取出一个欧拉回路的点序列（由于是回路最后回到 $1$ 时 $1$ 不加入点序列），发现如果有 $k$ 个 $1$ 我们将每个 $1$ 旋到第一个位置得到的序列都对应了一个以 $1$ 为起点出发形成的欧拉回路。

于是每条欧拉回路多算了 $k$ 次，而一个点 $x$ 会被经过 $du_x$ 次，那么 $k$ 显然就是 $du_1$，除以一个 $du_1$ 即可。

那么有 $sum=ans/du_1=(\text{内向树个数})\times(\prod_{x=2}^n({du_x-1})!\times du_1!)/du_1=(\text{内向树个数})\times(\prod_{x=1}^n({du_x-1})!)$。

故 $BEST$ 定理的表述就是：

一个有向图的欧拉回路的数量为 
$sum=(\text{内向树个数})\times(\prod_{x=1}^n({du_x-1})!)$

挺好看的是吧。

---

## 作者：juju527 (赞：15)

### 前置知识
#### Best 定理

对于一个有向欧拉图，记点 $i$ 的出度为 $\text{out}_i$，其本质不同的欧拉回路个数为：
$$
T\prod_{i}(out_i-1)!
$$
$T$ 为图的内向生成树个数。

显然，$T$ 可以有矩阵树定理求得。

宣传下：[矩阵树定理学习笔记](https://www.cnblogs.com/juju527/p/15183866.html)。

##### 证明

记 $s$ 为起点。

对于一条欧拉回路，我们把所有点的最后一条出边拿出来去除掉 $s$ 的出边，

一定形成一棵以 $s$ 为根的内向树。

原因是如果成环，由于所有点出度等于入度，环上最后走的一条边到达的位置仍会有一条出边未走，矛盾。

此时其他所有非树边随便排列，考虑构造一组方案。

至于从根出发的非树边有 $out_s$ 条，全部重排应该是 $out_s!$。

但考虑从任意一条边开始，由于最终走了一条回路，所以会造成一次轮换。

最后一条本质相同的的回路将被算 $out_s$ 次，最终除掉即可。

从 $s$ 出发按选择的出边顺序走，最后走树边由于出度等于入度，一定能走完所有边。

由于所有点的最后一条出边中一定有欧拉回路顺序中的最后一条边，该条边一定回到 $s$，得到回路。
### $\texttt{Solution}$
模板题，题目中要求的答案即为有向图欧拉回路计数。

值得注意的是，其为并未去除循环同构的欧拉回路。

我们得到答案后应乘上 $out_1$，原因在上述证明中。

边界情况是注意 Best 定理是在**欧拉图**上使用的，

应特判不是欧拉图的情况。

时间复杂度 $O(Tn^3)$。

[code](https://www.luogu.com.cn/paste/xgahoqzn)

---

## 作者：皎月半洒花 (赞：12)

如果题解区公式锅了，可以考虑直接去博客查看（（

Best Theorem 的板子题…

Best Theorem 本质上是用来统计有向图中欧拉回路数目定理。记 $t_x$ 表示以 $x$ 为根的树形图的数量，$G=\{V,E\}$， 那么有

$$\mathrm{ec}(G)= t_x \prod _{i\in V}(\deg_i-1)!$$

其中 $\deg_x$ 表示 $x$ 的度。如果图中有欧拉回路，那么存在 $\deg_{(in)x}=\deg_{(out)x}$，所以可以随便选一种来统计。

考虑如何统计出以某个点为根的生成树。发现其实从欧拉回路的数量上来证明，取哪个点都一样。所以就考虑把某个点删除之后的生成树数量，这就是以该点为根的生成树数量。这部分直接 Matrix Tree + 辗转相除 即可。

但是这题还没完。考虑起点为 $1$ ，所以以 $1$ 为开头的路，是可以循环同构的，而其他的点是不能循环同构的，也就是本质上，原来的best已经把从所有点出发的循环同构算过一遍了，唯独不算从根开始的全局同构。但现在要求算上，于是最后的结果需要乘上 $\deg_1$。

upd：

然后这个题因为叙述不严谨存在一些细节问题。首先用 Best 定理求解时原图必须存在欧拉回路，可以用出入度来判断；其次考虑如果要走完全部的边，不包含 1 的极大连通子图的大小至多为 1，否则必定有边走不到。其它细节稍注意一下就好了。

orz `JKlover`

```cpp
const int N = 110 ;
const int M = 500010 ;
const int P = 1000003 ;

typedef long long LL ;

int T ;
int n ;
int I[M] ;
int fa[M] ;

LL res ;
LL fac[M] ;
LL deg[M] ;
LL D[N][N] ;
LL K[N][N] ;
LL A[N][N] ;

LL Gauss(){
    LL ans = 1 ;
    for (int i = 1 ; i < n ; ++ i){
        for (int j = i + 1 ; j < n ; ++ j){
            while(K[j][i]){
                LL t = K[i][i] / K[j][i] ;
                for(int k = i ; k < n ; ++ k)
                    K[i][k] = (K[i][k] - t * K[j][k]) % P ;
                swap(K[i], K[j]), ans = (-ans % P + P) % P ;
            }
        }
		if (K[i][i]) (ans *= K[i][i]) %= P ;
    }
    return (ans % P + P) % P ;
}
void clear(){
    memset(K, 0, sizeof(K)) ;
    memset(A, 0, sizeof(A)) ;
    memset(D, 0, sizeof(D)) ;
    memset(I, 0, sizeof(I)) ;
	for (int i = 1 ; i <= n ; ++ i) fa[i] = i ; 
}
int find_f(int x){
    return x == fa[x] ? x : fa[x] = find_f(fa[x]) ;
}
int main(){
    cin >> T ; fac[0] = 1 ;
    for (LL i = 1 ; i <= 500000 ; ++ i)
        fac[i] = fac[i - 1] * i % P ;
    while (T --){
        scanf("%d", &n) ; clear() ;
        for (int i = 1 ; i <= n ; ++ i){
            int k, s ; cin >> s ; deg[i] = s ;
            for (int j = 1 ; j <= s ; ++ j){
                cin >> k ; A[i][k] ++, D[k][k] ++, ++ I[k] ;
                if (find_f(i) != find_f(k)) fa[find_f(i)] = find_f(k) ;
            }
        }
        for (int i = 1 ; i <= n ; ++ i)
            for (int j = 1 ; j <= n ; ++ j)
                K[i][j] = ((D[i][j] - A[i][j]) % P + P) % P ;
        for (int i = 1 ; i <= n ; ++ i)
            if (I[i] != deg[i])  goto lalala ;
        for (int i = 1 ; i <= n ; ++ i)
            if (find_f(i) != find_f(1) && deg[i]) goto lalala ;
        res = deg[1] * Gauss() % P ; 
        for (int i = 1 ; i <= n ; ++ i)
            if (deg[i]) (res *= fac[deg[i] - 1]) %= P ;
        for (int i = 2 ; i <= n ; ++ i) 
            if (find_f(i) == find_f(1)) goto lelele ; 
        cout << fac[deg[1]] << endl ; continue ; 
        lalala : puts("0") ; continue ;
        lelele : cout << res << endl ;
    }
    return 0 ;
}

```

---

## 作者：do_it_tomorrow (赞：6)

[更好的阅读体验](https://www.doittomorrow.xyz/post/best-ding-li/)
# 定义
对于欧拉回路满足回路数量 $cnt$ 满足：
$$cnt=T\prod_{i=1}^{n}(out_i-1)!$$
其中 $T$ 为图中一任一点为根的内向生成树（根据欧拉图的性质所有的节点作为根的结果都是一样的），$out_i$ 表示 $i$ 点的出度。

显然，$T$ 可以使用矩阵树定理进行求解。
# 证明
令 $s$ 为根，如果一个图为以 $s$ 点为根的内向生成树那么满足一共有 $n-1$ 条有向边期且对于任一点都可以找到一条路径到 $s$。

对于任意一条欧拉路，将所有的点在遍历时访问到的最后一条出边删掉，特别的根节点 $s$ 的所有出边都要删除，剩下的图一定成为一棵以 $s$ 为根的内向生成树。

例如下面这张图：
![](https://cdn.luogu.com.cn/upload/image_hosting/kiiz1enx.png)
假设路径为 $s\to 1\to 2\to 3\to 4\to 5\to s\to 2\to 4\to s$，那么经过处理图就成为了这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/eupzhm00.png)
经过整理之后就得到了一个以 $s$ 为根的内向生成树：
![](https://cdn.luogu.com.cn/upload/image_hosting/ntn33zgj.png)
因为所有的点均保留了自己的最后一条出边而且所有的节点在最后全部到达了 $s$ 点，那么所有的点一定有一个路径可以到达 $s$ 点。假设成为了环，那么交点处因为入度等于出度，一定还会有一条出边，所以形成环与条件相矛盾。

从起点 $s$ 出发最终回到 $s$ 点一共 $out_s$ 次就一共有 $out_s!$ 种可能性。因为剩下的所有点都有 $out_i-1$ 条没有被固定的出边，所有都有 $(out_i-1)!$ 种方案。因为乘法原理，所以将它们乘起来即可。

由于所有点的保留的出边中一定有欧拉回路顺序中的最后一条边，所以通过这条边一定可以回到 $s$，得到了这种构造方式的正确性。

但考虑从任意一条边开始，那么在上面的方法中我们将所有的路径以 $s$ 划分成了 $out_s$ 段。但是因为不在存在起点，所以这且路径本质上是相同的，那么答案就应该除以 $out_s$。
# 实现
需要注意 Best 定理只能在欧拉图上使用，所以在每一次使用前都应该判断输入的是否是欧拉图。

因为可能有一些节点是独立的不与任何节点有连边，那么这个节点就是不需要考虑的，需要在实现中特判掉。

根据定理求出的数量时间复杂度为 $O(T\cdot n^2\log W)$ 其中 $W$ 为值域。

# Code
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#define int long long
using namespace std;
const int N=105,M=2e5+5,mod=1e6+3;
int n,m,in[N],out[N],a[N][N],jc[M],cnt;
bool vis[N];
vector<int> v[N];
void dfs(int x){
	for(int i:v[x]){
		cnt++;
		if(!vis[i]){
			vis[i]=1;
			dfs(i);
		}
	}
}
bool ck(){
	vis[1]=1,cnt=0,dfs(1);
	if(m!=cnt){
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(out[i]!=in[i]){
			return 0;
		}
	}
	return 1;
}
int get(){
	int ans=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]) continue;
		for(int j=i+1;j<=n;j++){
			if(!vis[j]) continue;
			while(a[j][i]){
				int tot=a[i][i]/a[j][i];
				for(int k=1;k<=n;k++){
					a[i][k]=(a[i][k]-a[j][k]*tot%mod+mod)%mod;
				}
				swap(a[i],a[j]);
				ans*=-1;
			}
		}
	}
	for(int i=2;i<=n;i++){
		if(vis[i]) ans=(ans*a[i][i]%mod+mod)%mod;
	}
	return ans;
}
void solve(){
	cin>>n,m=0;
	memset(in,0,sizeof(in));
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++) v[i].clear();
	for(int i=1;i<=n;i++){
		cin>>out[i];
		for(int j=1,x;j<=out[i];j++){
			cin>>x;
			v[i].push_back(x);
			in[x]++;
			a[i][i]++;
			a[i][x]--;
			m++;
		}
	}
	if(!ck()){
		cout<<0<<'\n';
		return;
	}
	int ans=get()*jc[out[1]]%mod;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			continue;
		}
		ans=ans*jc[out[i]-1]%mod;
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;cin>>T;
	jc[0]=1;
	for(int i=1;i<M;i++){
		jc[i]=jc[i-1]*i%mod;
	}
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：Acoipp (赞：5)

## 分析

这是一道模板题，对于一道包含欧拉回路的有向图，有 BEST 定理：

$$
cnt=T \prod_{i=1}^n(ot_i-1)!
$$

其中 $ot_i$ 表示第 $i$ 个点的出度，$T$ 表示这幅图的内向生成树的个数（取任何一个节点为根都可以，答案都相等，这是包含欧拉回路的有向图的性质）。

**注意：这是把循环同构的欧拉回路去除掉的答案！**

而这道题要求从 $1$ 开始，从 $1$ 结束，所以我们需要乘上 $ot_1$，证明在下面。

## 证明

偏感性。

首先考虑对于任意一条欧拉回路保留除去起始点 $s$ 剩下点的最后一条出边，那么这些出边一定构成一个以 $s$ 为根的内向树。

如果成环，那就说明形成了一个 $\rho$ 形，交点处因为入度等于出度，一定还会有一条出边，于是不可能成环。

接下来考虑反向构造，如果固定了起点和终点为 $s$，那么从 $s$ 到外面走有 $ot_s!$ 种走法，对于每个点，因为固定了一条出边，所以都有 $(ot_i-1)!$ 种走法，乘起来即可。

如果不固定起点，在上面的方案中，每种欧拉回路都因为 $s$ 的最后一条出边是任意选择的，所以除掉 $ot_s$ 就变成了文章一开始的形式。（也可以理解为 $s$ 把任何路径划分成了 $ot_s$ 段，但是对于整幅图来说这 $ot_s$ 段循环同构，所以需要除一下 $ot_s$）

## 实现

首先需要判断这个有向图有没有欧拉回路，判定条件为去掉独立点之后从 $1$ 开始能不能遍历到所有点，并且不是独立点的点的入度必须等于出度。

如果含有欧拉回路，用矩阵树定理求 $T$ 的值即可。

注意，这里求 $T$ 如果选第 $i$ 行和第 $i$ 列删掉，一定要保证 $i$ 不是独立点，代码选的是 $i=1$，当然你也可以选择以 $3$ 为根的内向树，但是要判断 $3$ 是不是独立点。

## 代码

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 105
#define M 200005
#define mod 1000003
using namespace std;
vector<ll> op[N];
ll T,n,m,i,j,x,y,a[N][N],ans,jc[M],in[N],ot[N],vis[N],vit;
ll qmi(ll a,ll b,ll p){
	ll res = 1%p,t=a;
	while(b){
		if(b&1) res=res*t%p;
		t=t*t%p;
		b>>=1;
	}
	return res;
}
void dfs(ll x){
	vis[x] = 1;
	for(ll i=0;i<op[x].size();i++){
		vit++;
		if(vis[op[x][i]]) continue;
		dfs(op[x][i]);
	}
}
bool check(){
	dfs(1);
	if(vit!=m) return 0;
	for(ll i=1;i<=n;i++) if(in[i]!=ot[i]) return 0;
	return 1;
}
ll solve(){
	ll ans=1,has=0;
	for(ll i=1;i<=n;i++){
		if(i==1||!vis[i]) continue;
		for(ll j=i+1;j<=n;j++){
			if(j==1||!vis[j]) continue;
			if(!a[i][i]) swap(a[i],a[j]),has^=1;
			ll res = a[j][i]*qmi(a[i][i],mod-2,mod)%mod;
			for(ll k=i;k<=n;k++){
				if(k==1||!vis[k]) continue;
				a[j][k] = (a[j][k]-a[i][k]*res%mod+mod)%mod;
			}
		}
	}
	for(ll i=1;i<=n;i++) if(i!=1&&vis[i]) ans=ans*a[i][i]%mod;
	if(has) ans=(mod-ans)%mod;
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	jc[0] = 1;
	for(i=1;i<=2e5;i++) jc[i]=jc[i-1]*i%mod;
	cin>>T;
	while(T--){
		vit=0,m=0;
		cin>>n;
		for(i=1;i<=n;i++){
			cin>>x;
			while(x--) cin>>y,op[i].push_back(y),a[y][i]--,a[i][i]++,in[y]++,ot[i]++,m++;
		}
		if(check()){
			ans = solve();
			for(i=1;i<=n;i++){
				if(!vis[i]) continue;
				if(i==1) ans=ans*jc[ot[i]]%mod;
				else ans=ans*jc[ot[i]-1]%mod;
			}
			cout<<ans<<endl;
		}
		else cout<<0<<endl;
		for(i=1;i<=n;i++) op[i].clear(),in[i]=0,ot[i]=0,vis[i]=0;
		for(i=1;i<=n;i++) for(j=1;j<=n;j++) a[i][j]=0;
	}
	return 0;
}
```

---

