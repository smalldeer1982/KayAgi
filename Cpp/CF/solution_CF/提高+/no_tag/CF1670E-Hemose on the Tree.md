# Hemose on the Tree

## 题目描述

After the last regional contest, Hemose and his teammates finally qualified to the ICPC World Finals, so for this great achievement and his love of trees, he gave you this problem as the name of his team "Hemose 3al shagra" (Hemose on the tree).

You are given a tree of $ n $ vertices where $ n $ is a power of $ 2 $ . You have to give each node and edge an integer value in the range $ [1,2n -1] $ (inclusive), where all the values are distinct.

After giving each node and edge a value, you should select some root for the tree such that the maximum cost of any simple path starting from the root and ending at any node or edge is minimized.

The cost of the path between two nodes $ u $ and $ v $ or any node $ u $ and edge $ e $ is defined as the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all the node's and edge's values between them, including the endpoints (note that in a tree there is only one simple path between two nodes or between a node and an edge).

## 说明/提示

The tree in the first test case with the weights of all nodes and edges is shown in the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670E/4eb503eb5f64afb2d876c0f890af3abc91c77200.png)The costs of all paths are:

- $ 3 $ ;
- $ 3\oplus 7=4 $ ;
- $ 3\oplus 7\oplus 6=2 $ ;
- $ 3\oplus 2=1 $ ;
- $ 3\oplus 2\oplus 1=0 $ ;
- $ 3\oplus 2\oplus 1\oplus 4=4 $ ;
- $ 3\oplus 2\oplus 1\oplus 4\oplus 5=1 $ .

The maximum cost of all these paths is $ 4 $ . We can show that it is impossible to assign the values and choose the root differently to achieve a smaller maximum cost of all paths.

The tree in the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1670E/6834d138a5c76fd79b1db4fed4c1d1a14f21fafa.png)

## 样例 #1

### 输入

```
2
2
1 2
2 3
3 4
3
1 2
2 3
3 4
1 5
1 6
5 7
5 8```

### 输出

```
3
5 1 3 6
4 2 7
5
1 2 8 11 4 13 9 15
6 14 3 7 10 5 12```

# 题解

## 作者：shinkuu (赞：2)

推了好一会儿最后发现推出来发现结论很显然的构造题。

对于位运算的题，一般来说都是可以用拆位做的套路的。但是这道题不太适合，因为这样做不好满足所有数为排列的这个要求。

考虑观察性质。发现**答案一定至少为 $n$**。证明可以观察每个点从低到高第 $p$ 位，很简单，就省略了。然后考虑能不能构造使答案为 $n$。

然后发现，$\forall i\in[1,n),i\oplus(i+n)=n$。再考虑这样一棵树：它的每个节点点权都是 $n$，那每个节点到根的点权即为 $0$ 或 $n$。于是可以把原树上每个节点和它到父亲的边绑在一起成一个节点，成为上面所说的树。此时只要考虑边到根的异或和不超过 $n$ 即可。

解决这个问题，分讨一下：

- 如果这条边所对应的父亲节点到根的异或和为 $n$，那么边权就设为上文中的 $i+n$。

- 否则为 $i$。

这样异或和一定不超过 $n$。

code：

```cpp
int n,m,cnt,g[N],h[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
inline void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void dfs(int u,int f,bool flag){//flag 记录父亲对应异或和是 0 还是 n
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)
			continue;
		cnt++;
		if(flag){
			g[v]=cnt;
			h[(i+1)/2]=n+cnt;
		}else{
			g[v]=n+cnt;
			h[(i+1)/2]=cnt;
		}
		dfs(v,u,!flag);
	}
}
void solve(){
	scanf("%d",&m);
	n=1<<m;
	tot=cnt=0;
	for(int i=1;i<=n;i++)
		head[i]=0;
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	g[1]=n;
	dfs(1,0,1);
	puts("1");
	for(int i=1;i<=n;i++)
		printf("%d ",g[i]);
	puts("");
	for(int i=1;i<n;i++)
		printf("%d ",h[i]);
	puts("");
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# CF1670E 题解



## 思路分析

诈骗题，注意到如下观察：

> 观察：
>
> 对于任意的一棵树，$\text{MaxDis}\ge n$。
>
> 考虑反证法，假如每个距离都 $<n$，那么我们考虑 $n$ 个 $\ge n$ 的权值和 $n-1$ 条边。
>
> 根据抽屉原理，至少有一条边的权值 $\ge n$，那么由于我们的假设，不妨设这条边为 $(f_u,u)$，其中 $f_u$ 表示 $u$ 的父亲，且 $w(f_u,u)=x\ge n$。
>
> 那么由于 $dis(f_u)<n$，那么 $dis(f_u,u)=dis(f_u)\oplus x$，由于 $dis(f_u)<n=2^p$，因此 $dis(f_u)$ 的第 $p$ 位一定是 $0$，而 $x\ge n$ 因此 $x$ 的第 $p$ 位一定是 $1$，异或后得到 $dis(f_u,u)$ 的第 $p$ 位上是 $1$，则 $dis(f_u,u)\ge 2^p=n$，与假设矛盾，故原命题得证。

根据观察，答案至少为 $n$，结合样例，大胆猜测答案恰好为 $n$。

注意到对于所有 $k\in[1,2\times n-1],k\ne n$，$k$ 与 $k\oplus n$ 成对出现时具有非常良好的性质，即 $k\oplus(k\oplus n)=n$。

因此考虑除了根以外，每一对 $\{w(u),w(u,f_u)\}$ 都是 $\{k,k\oplus n\}$，而 $w(root)=n$ 那么此时到每个节点的 $dis$ 都应该是  $0$ 或 $n$，所以根据 $f_u$ 等于 $0$ 还是 $n$ 判断 $w(u,f_u)$ 取 $>n$ 的还是 $<n$ 的那个权值。

根据上面的分析，我们知道对于任意指定的树根，都存在 $\text{MaxDis}=n$ 的赋权方法，因此随便选一个树根然后 dfs 一遍整棵树就可以得到答案。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int MAXN=3e5+1;
vector <pii> G[MAXN];
int p,n,ev[MAXN],nv[MAXN];
inline void dfs(int p,int f,int x) {
	for(auto e:G[p]) {
		int v=e.first,id=e.second,w=n-v+1;
		if(id==f) continue;
		if(x==0) ev[id]=w,nv[v]=w^n;
		else ev[id]=w^n,nv[v]=w;
		dfs(v,id,x^n);
	}
}
inline void solve() {
	scanf("%d",&p); n=1<<p;
	for(int i=1;i<=n;++i) G[i].clear();
	for(int i=1;i<n;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(make_pair(v,i));
		G[v].push_back(make_pair(u,i));
	}
	dfs(1,0,n),nv[1]=n;
	puts("1");
	for(int i=1;i<=n;++i) printf("%d ",nv[i]);puts("");
	for(int i=1;i<n;++i) printf("%d ",ev[i]);puts("");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：小木虫 (赞：1)

### Preface  
由于不怎么会构造，故找来一些构造题刷，看到这道题觉得质量很好，故写一篇题解。  
### Problem  
给你一棵 $2^p$ 个节点的树，点和边的权值应是 $[1,2^{p+1}-1]$ 的排列，请你构造一种方案使得从你选择的根到任意点或边的结尾的权值异或和的最大值最小。  
$p\leq17$

### Solution  
发现一个很有意思的性质，就是你去 “bfs” 这棵树，总能找到一个深度最浅的地方的权值的第 $i$ 位为 1。这意味的它的祖先不可能有第 $i$ 位的 1，所以这个位置的异或和 $\geq 2^i$。  

然后你就知道，整棵树的答案 $\geq2^p$。  
所以我们尝试构造答案为 $2^p$。  

由于其它情况不好控制，我们直接钦定任意一个点为根，这个点的权值为 $2^p$。  
然后剩下 $n-1$ 个点和 $n-1$ 个边，剩下 $n-1$ 个小于 $2^p$ 的权值，$n-1$ 个大于 $2^p$ 的权值，所以尝试讲点和边配对赋权，将他们抵消。  

我们从上往下构造，根的权值为 $2^p$，那么第一层的边应该都是大于 $2^p$ 的，设为 $2^p+x$,然后这个边的末尾的异或和就是 $x$，然后我们的点可以设为 $x$，这样到这个点的结尾的异或和就是 0。  

接着来看第二层，由于上一层的异或和为 0，那么这层的边应该小于 $2^p$，用 $x$ 表示，然后相似地，这层的点权就为边权 $+2^p$，为 $x+2^p$，然后这个点结尾的异或值就为 $2^p$。

发现什么事了？  
这个点的结尾的异或值为 $2^p$！  
这不就是根节点的状态吗？  
这样就可以按照奇偶性递归求解了吧。  
code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int p,n,U[N],V[N];
vector <int> edge[N];
int dres[N],eres[N],cnt;
void dfs(int u,int fa){
	for(int i=0;i<edge[u].size();i++){
		int vid=edge[u][i],v=0;
		if(U[vid]==u)v=V[vid];
		else v=U[vid];
		if(v==fa)continue;
		if((dres[u]>>p)&1){
			dres[v]=++cnt;
			eres[vid]=cnt+(1<<p);
		}else{++cnt;
			dres[v]=cnt+(1<<p);
			eres[vid]=cnt;
		}
		dfs(v,u);
	}
}int T;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>p;n=(1<<p);cnt=0;
		for(int i=1;i<=n;i++)
			U[i]=V[i]=dres[i]=eres[i]=0,edge[i].clear();
		for(int i=1;i<n;i++){
			cin>>U[i]>>V[i];
			edge[U[i]].push_back(i);
			edge[V[i]].push_back(i);
		}
		dres[1]=(1<<p);dfs(1,0);cout<<1<<"\n";
		for(int i=1;i<=n;i++)cout<<dres[i]<<" ";
		cout<<"\n";
		for(int i=1;i<n;i++)cout<<eres[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：RegenFallen (赞：1)

## 题意

   给定一个节点数为 $n$ 的树，保证树的节点数量为2的幂次，即 $n = 2 ^ p (p \in \mathbb{N})$。你需要给每条边一个边权，同时给每个点一个点权。所有点的点权与所有边的边权应形成一个长度为 $2 n - 1$ 的排列。然后你需要指定一个根节点，使得从这个根节点到达所有点**或边**的路径异或和最大值最小。

## 思路

1. 由 $1 \leq p \leq 17$ 可得，我们显然要用 $O(n)$ 左右的时间复杂度解决这个问题。
2. 仔细观察题目给的翻译发现，两个样例的异或和的最小值都为 $n$ 。那么我们可以考虑是否任何一棵树都可以使得异或和最小值为 $n$。
   - 可以发现，最小值不可能低于 $n$ 。因为一定存在一个点与一条边，使得点权小于 $n$ 而边权大于等于 $n$，且因为 $n$ 为2的幂次，那么此时异或和一定不会小于$n$ 。因此如果可以构造出最小值为 $n$ 的方案，那么该方案一定为最优解。
3. 题目说可以指定根节点，那么我们首先要尝试的应该是，如果随机根节点，比如无论树的形状，指定根节点为1，是否可以直接构造出最优解。

---

有了以上的条件，我们的目标就变成了让任意一个点与一条边的异或和不超过 $n$ 。那么对于每一个不小于 $n$的数字 $x$ ，与它相连的两条边的边权（如果这个数字作为了点权）或两个点的点权（如果这个数字被作为了边权）$y$，必须满足以下条件之一：

- $x \oplus y < n$ (下文以 $\oplus$ 代指异或)：此时由于$x \geq n$，那么 $y \geq n$ 也需要成立。
- $x \oplus y = n$ : 此时由于 $x \geq n$，那么 $y = n - x$ 。

于是我们发现，如果从一个节点要扩展到另一个节点，需要使用两个整数。而对于 $n$ 个节点的树，需要扩展 $n - 1$ 次。每次使用的两个整数必须满足以下两种情况之一：

- 一个数不小于 $n$ ，另一个数小于 $n$。
- 两个数都小于 $ n $。

这样才可以有可能令每个路径的异或和不超过 $n$。

作为一个构造题，我们在这两种情况中抉择后（可能需要经过一番思考），可以选择一个数不小于 $n$, 另一个数小于 $n$， 找到这样的 $n - 1$ 组数据，就可以构造出这个树。

此时我们发现如果根节点为 $n$ 时，有一些不错的性质。我们可以若令边权为 $n + k$， 下一个点的点权为 $k(1 \leq k \lt n)$ 可让，即到达下一个点时的异或和为 $0$。

同时如果到当前节点异或和为 $0$ 时，我们只需要让边权为 $k$，下一个点的点权为 $ n + k$，即可使到达下一个点的异或和为 $n$。形成了一个奇妙的循环。



## 做法

我们可以将第一个点的权值设为 $n$ ，同时用DFS去更新每条边和每个点的权值。更新时，下一个边权和点权的设置值与当前点的权值有关。

- 当前点异或和为 $n$ 时，下一条边权值为 $n + k$ ，下一个点的权值为 $k$ 。
- 当前点异或和为 $0$ 时，下一条边权值为 $k$ ，下一个点的权值为 $n + k$ 。



## 代码

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1000005;
typedef pair<int,int> PII;
vector<PII> e[maxn]; // 存每条边的终点及边的序号
int node_ans[maxn], e_ans[maxn]; // 每个节点的点权和每个边的边权
bool vis[maxn]; // 每个点是否被访问过
int num = 1;
int n, p;
void dfs(int now, int flag) {
    vis[now] = true;
    for (int i = 0; i < e[now].size(); i++){
        int nxt = e[now][i].first;
        int e_num = e[now][i].second;
        if (vis[nxt]) continue ;
        e_ans[e_num] = flag ^ num;
        node_ans[nxt] = flag ^ n ^ num;
        num ++;
        dfs(nxt, flag ^ n);
    }
}

void solve(){
    cin >> p;
    n = 1 << p;
    num = 1;
    for (int i = 1; i <= n; i++) vis[i] = false;
    for (int i = 1; i <= n; i++) e[i].clear();
    for (int i = 1; i <= n - 1; i++){
        int u, v; cin >> u >> v;
        e[u].push_back({v, i});
        e[v].push_back({u, i});
    }
    node_ans[1] = n;
    dfs(1, n);
    cout << 1 << endl;
    for (int i = 1; i <= n; i++){
        cout << node_ans[i] << " \n"[i == n];
    }
    for (int i = 1; i <= n - 1; i ++){
        cout << e_ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    int T;
    T = 1;
    cin >> T;
    while (T--){
        solve();
    }
    return 0;
}
```

---

## 作者：Yasuraoka_Hanabi (赞：0)

构造题是我的弱项实锤了。

------------

首先不考虑构造方案，尝试猜测一个答案的可能下界。容易发现 $ans\ge n$。发现样例都满足 $ans=n$。这个位置的题，一般这就是结论了。我们尝试总是构造出一组 $ans=n$ 的解。

这里我认为题目让你自己定根的过程有点诈骗，会让选手误以为还要发掘树的某些结构性质，那么就会让不少人弃疗。反而大胆猜测任选根都有解，做出这题的希望会变大。

那么我们就钦定 $1$ 节点为根了。然后开始构造。

注意到实质上有 $n$ 个要填的数（$n\sim 2n-1$）都是大于等于 $n$ 的。所以除了很特殊的情况（比如纯菊花图）以外，肯定会出现这样的情况：还没走完，此时异或和已经等于 $n$ 了。此时我们要考虑如何往下填。

那么此时你不能放一个 $\lt n$ 的数上去，否则异或和就大于 $n$ 了（注意到这里的 $n$ 是 $2^p$！）。所以必须放一个 $\ge n$ 的数上去，这样最高位会由于异或的性质被消掉。  

然后你接着往下放，又一定不能放一个 $\ge n$ 的，不然最高位又出现力，这玩意就 $\gt n$ 了。

所以发现把数关于 $n$ 去左右分界，似乎填的过程是大小交替地去填。

此时不难想到根节点填 $n$，这样剩下 $n-1$ 个点，$n-1$ 条边。而且恰好左右两部分的数各剩下 $n-1$ 个。此时这个题已经呼之欲出了：就是利用对称性去填。

具体的，当你走到当前点的异或和为 $n$ 的话，那么此时往下的一条边就是填 $n+k$，然后走到的点填 $k$；注意到上面的过程后再往下走一步，异或和会变成 $0$。此时显然反过来，往下的一条边填 $k$，然后走到的点填 $n+k$ 即可。然后这个 $k$ 你可以随意地去分配，不重不漏即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int MAXN=(1<<17)+10;
int T,p,n,u[MAXN],v[MAXN],cur;
int pv[MAXN],ev[MAXN];
vector<array<int,2> >e[MAXN];
void dfs(int u,int fa,int state){
    for(auto V:e[u])if(V[0]!=fa){
        cur++;
        ev[V[1]]=n+cur;
        pv[V[0]]=cur;
        if(state)swap(ev[V[1]],pv[V[0]]);
        dfs(V[0],u,state^1);
    }
}
void solve(){
    cin>>p;n=(1<<p);
    rep(i,1,n)e[i].clear();
    rep(i,1,n-1){
        cin>>u[i]>>v[i];
        e[u[i]].push_back({v[i],i});e[v[i]].push_back({u[i],i});
    }
    pv[1]=n;cur=0;
    dfs(1,1,0);
    cout<<1<<'\n';
    rep(i,1,n)cout<<pv[i]<<' ';cout<<'\n';
    rep(i,1,n-1)cout<<ev[i]<<' ';cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin>>T;while(T--)solve();

    return 0;
}
```

---

