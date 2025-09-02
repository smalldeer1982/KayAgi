# Chloe and pleasant prizes

## 题目描述

Generous sponsors of the olympiad in which Chloe and Vladik took part allowed all the participants to choose a prize for them on their own. Christmas is coming, so sponsors decided to decorate the Christmas tree with their prizes.

They took $ n $ prizes for the contestants and wrote on each of them a unique id (integer from $ 1 $ to $ n $ ). A gift $ i $ is characterized by integer $ a_{i} $ — pleasantness of the gift. The pleasantness of the gift can be positive, negative or zero. Sponsors placed the gift $ 1 $ on the top of the tree. All the other gifts hung on a rope tied to some other gift so that each gift hung on the first gift, possibly with a sequence of ropes and another gifts. Formally, the gifts formed a rooted tree with $ n $ vertices.

The prize-giving procedure goes in the following way: the participants come to the tree one after another, choose any of the remaining gifts and cut the rope this prize hang on. Note that all the ropes which were used to hang other prizes on the chosen one are not cut. So the contestant gets the chosen gift as well as the all the gifts that hang on it, possibly with a sequence of ropes and another gifts.

Our friends, Chloe and Vladik, shared the first place on the olympiad and they will choose prizes at the same time! To keep themselves from fighting, they decided to choose two different gifts so that the sets of the gifts that hang on them with a sequence of ropes and another gifts don't intersect. In other words, there shouldn't be any gift that hang both on the gift chosen by Chloe and on the gift chosen by Vladik. From all of the possible variants they will choose such pair of prizes that the sum of pleasantness of all the gifts that they will take after cutting the ropes is as large as possible.

Print the maximum sum of pleasantness that Vladik and Chloe can get. If it is impossible for them to choose the gifts without fighting, print Impossible.

## 样例 #1

### 输入

```
8
0 5 -1 4 3 2 6 5
1 2
2 4
2 5
1 3
3 6
6 7
6 8
```

### 输出

```
25```

## 样例 #2

### 输入

```
4
1 -5 1 1
1 2
1 4
2 3
```

### 输出

```
2```

## 样例 #3

### 输入

```
1
-1
```

### 输出

```
Impossible```

# 题解

## 作者：Feyn (赞：7)

英文版的题面很长很长，但中文版的翻译就显得十分干净明了了：

#### 给你一棵树，求两颗不相交的子树使它们的点权总和最大，输出最大的点权和。点权可能为负。

这就好办了，妥妥的树形DP。再一看数据规模$1\le n\le 2\times10^5$，基本可以断定此题要求在$O(N)$的复杂度下求解答案。

所以，二话不说，先把dp数组写出来，因为是$O(N)$的复杂度，所以定义出来的数组应该是个一维的：
```
int dp[200005]
```
数组是写出来了，但$dp[i]$什么意思呢？难不成是以节点$i$为根的子树的所有子树的最大值？

抱着试一试的想法，让我们继续向下推。

假如这个节点是$u$，它的孩子我们设为$v$，以节点$u$为根节点的子树的所有节点的点权和为$sum[u]$，那么$dp[i]=\max(\max(dp[v]),sum[v])$，原因很显然。

那我们心心念念的最大值呢？这道题问的可是不相交的两棵子树的最大值。

其实也很简单。对于每一个节点$u$，枚举所有的$dp[v]$，（$u$、$v$的含义同上)，取其中的最大值和次大值。如果只找到了一个最大值而没有次大值（即是这个节点只有一个孩子），就不计入答案；否则，就用最大值和次大值之和更新答案，取两者的最大值。

最后，漂亮滴输出它。

代码大概如下（附[AC结果](https://www.luogu.com.cn/record/45601519)）：

```
#include<cstdio>
#define N 200005
#define int long long
const int minn=-1e18;

inline int max(int s1,int s2){
	return s1<s2?s2:s1;
}//内联函数稍微减少点时间 

int c[N],dp[N],sum[N];//c[i]是每个节点的点权
                      //dp[]和sum[]都与上文所述相同
 
int head[N],m,sum_;
struct edge{
	int to,next;
}e[N*2];
void add(int f,int t){
	sum_++;
	e[sum_].to=t;
	e[sum_].next=head[f];
	head[f]=sum_;
}//邻接表存边模板，把树当有向图存 

int f[N];//f[i]代表节点i的父亲 
void dfs(int wh,int fa){//wh代表当前需要处理的节点
                        //fa代表当前节点的父亲 
                        //dfs就是为了处理出dp数组 
	f[wh]=fa;
	sum[wh]=c[wh];
	for(int i=head[wh];i!=0;i=e[i].next){//遍历每一条边 
		if(e[i].to==fa)continue;//不可搜回父亲节点 
		dfs(e[i].to,wh);
		sum[wh]+=sum[e[i].to];
	}
	//上面这个for是为了处理出sum数组 
	dp[wh]=sum[wh];
	for(int i=head[wh];i!=0;i=e[i].next){
		if(e[i].to==fa)continue;
		dp[wh]=max(dp[wh],dp[e[i].to]);
	}
	//上面这个for是为了处理出dp数组 
}

signed main(){
	
	scanf("%lld",&m);
	for(int i=1;i<=m;i++)scanf("%lld",c+i);
	for(int i=1;i<m;i++){
		int s1,s2;
		scanf("%lld%lld",&s1,&s2);
		add(s1,s2);
		add(s2,s1);
	}//输入 
	dfs(1,0);//进行dfs 
	int ans=minn;
	for(int i=1;i<=m;i++){//对于每一个节点 
		int b1=minn,b2=minn;//b1、b2分别为最大值和次大值 
		for(int j=head[i];j!=0;j=e[j].next){
			if(e[j].to==f[i])continue;
			if(dp[e[j].to]>b1){
				//比最大值大时 
				b2=b1;
				b1=dp[e[j].to];
			}
			else if(dp[e[j].to]>b2){
				//比最大值小但比次小值大时 
				b2=dp[e[j].to];
			}
		}
		if(b2==minn)continue;//如果连次小值都没有，代表这个节点的孩子不超过一个 
		ans=max(ans,b1+b2);
	}
	if(ans==minn)printf("Impossible");//代表答案一直都没有被更新过 
	else printf("%lld",ans);
	
	return 0;
}
```
## 后记
看了一眼题解，许多题解都用到了一些高级数据结构，本蒟蒻就算会写，也懒得写。能用基础dp做出了的题为什么要用那些花里胡哨的方法呢。我有一个观点哈，就是如果你能用简单的方法解决掉一个复杂的题目，也是证明了你的能力。有的时候，用的方法越复杂，反而显得思维局限。~~个人观点，仅供参考~~。

---

## 作者：皎月半洒花 (赞：5)

一道不是很难的$DP$。

形式上，本文对“子树”和“连通块”不做区分。

我们思考，我们随便指定一个当根，那么我们考虑转移的时候是否需要跨出子树——其然是不需要的。因为我们最终的结果一定会是两棵不相交的最大的子树，所以我们直接令$1$为根。

那么就很显然了，我们只需要对每个$u$找出其子树内最大和次大的连通块，转移就好。我们令$dp[0]$作为最终答案，$dp[u]$记录子树内的最大连通块权值。那么当我们只访问了$u$的时候，记录一下我们是否已经计算过一颗子树，如果是就枚举另一颗子树并且不断更新当前的最大子树即可。

此处有一个小$trick$，即先更新$ans$后更新$dp[u]$，其作用是不言而喻的。

```cpp
#include <cstdio>
#include <iostream>

#define MAXN 300020
#define to(k) E[k].to
#define Fuck -23333666623336LL

using namespace std ;
struct Edge{
    int to, next ;
}E[MAXN] ; int head[MAXN], cnt ;
long long N, base[MAXN], S[MAXN], dp[MAXN], A, B, i ;

inline void Add(int u, int v){
    E[++ cnt].to = v, E[cnt].next = head[u], head[u] = cnt ;
    E[++ cnt].to = u, E[cnt].next = head[v], head[v] = cnt ;
}
void work_on_dp(int now, int f){
    S[now] = base[now] ;
    for (int k = head[now] ; k ; k = E[k].next){
        if (f == E[k].to) continue ;work_on_dp(to(k), now) ; 
        if (dp[now] > Fuck) dp[0] = max(dp[0], dp[now] + dp[to(k)]) ;
        S[now] += S[to(k)], dp[now] = max(dp[now], dp[to(k)]) ; 
    }	
    if (now != 1) dp[now] = max(dp[now], S[now]) ;//dp[now]表示最大子树和（即只选取一颗子树，选取哪一棵） 
}
int main(){
    cin >> N ; fill(dp, dp + N + 2, Fuck) ; 
    for (i = 1 ; i <= N ; ++ i) scanf("%lld", &base[i]) ;
    for (i = 1 ; i < N ; ++ i) scanf("%d%d", &A, &B), Add(A, B) ;
    work_on_dp(1, 0) ;  (dp[0] > Fuck ? cout << dp[0] << endl : cout << "Impossible" << endl) ; return 0 ;
}
```



---

## 作者：Crab_Dave (赞：1)

## CF743D 题解

+ ### 题意

  给出一颗以$1$为根，有$n$个点的树，第$i$个点的点权为$a_i$，要求两颗不相交的子树的最大点权和，若无解，输出 `Impossible`。

+ ### 思路

  先考虑啥是无解的情况。

  显然，当树的形态是一条链的时候无解（其他情况你至少可以选两个叶节点）。

  然后这题我一开始没看到有负点权，于是打算直接贪心在根节点的子树中选两棵权值和最大的。

  ~~结果发现连无解的情况都过不了~~

  啊，有负点权，所以只能老老实实dp了。

  设 $dp[i][1/0]$ 表示以 $i$ 为根的子树中已经选了 $2/1$ 棵子树的最大点权和。

  所以 $dp[i][0]$ 就从儿子中选一个 $dp[][0]$ 值最大的，或者全部选取。

  $dp[i][1]$ 可以从儿子中选一个 $dp[][1]$ 值最大的，或者从儿子中选 $dp[][0]$ 最大和次大的两个（前提是至少得有两个儿子）

  可能实现起来有一点小细节，但是对各位爷爷来说这不是有手就行（

+ ### 部分代码

  ```cpp
  void dfs1(int u,int fa){s[u]=a[u];
  	for(int i=head[u];i;i=e[i].next){
  		int v=e[i].to;if(v==fa)continue;
  		dfs1(v,u);s[u]+=s[v];
  	}
  }
  
  void dfs2(int u,int fa){
  	dp[u][0]=max(dp[u][0],s[u]);
  	ll mx1=-1e18,mx2=-1e18;
  	for(int i=head[u];i;i=e[i].next){
  		int v=e[i].to;if(v==fa)continue;
  		dfs2(v,u);
  		dp[u][0]=max(dp[u][0],dp[v][0]);
  		dp[u][1]=max(dp[v][1],dp[u][1]);
  		if(mx1<=-1e18||dp[v][0]>mx1)mx2=mx1,mx1=dp[v][0];
  		else if(mx2<=-1e18||dp[v][0]>mx2)mx2=dp[v][0];
  	}
  	if(mx2>-1e18)dp[u][1]=max(dp[u][1],mx1+mx2);
  }
  
  int main(){
  	scanf("%d",&n);
  	for(int i=1;i<=n;i++)scanf("%d",&a[i]),dp[i][0]=dp[i][1]=-1e18;
  	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
  	dfs1(1,0);dfs2(1,0);
  	if(dp[1][1]<=-1e18)return printf("Impossible\n"),0;
  	cout<<dp[1][1];
  	return 0;
  }
  ```

  

---

## 作者：6954717a (赞：1)

个人认为是一个树状DP的入门题，而且注意一下毒瘤数据，我看到了不下20组20w的数据qwq。

一定要开long long！

下面开始解析：

这个题其实就是一个裸的树状DP；

但是这个题的实现的思想就是从下到上每个节点的dp值是以该节点为原始节点的最大值

这就需要我们从下到上每一个点的子树和都要求出来，然后我们再在这一个节点的所有子节点与这个点进行一次取最大值

这样我们建立的一个 f[] 数组就满足了对于该点求最大值的操作，因为我们是从下到上来实现的，因此我们在实现的过程中就满足了这个点的所有子树和均已经被更新了(证明了该方法的正确性)，最后我们针对于根节点求最大值就行；

最后，别忘了初始化。

PS.最后别忘了对于一种长链的情况输出Impossible(不过我在代码中没有直接地判断，而是最后在更新ans值的时候进行的判断)

下面上蒟蒻丑陋的代码：
(这个题dalao说可以有一种跑得更快的实现，不过本蒟蒻懒，就没有再写一遍，凑活着看吧qwq)

    #include<iostream>
    #include<cstdio>
    #include<vector>
    #include<cmath>
    #include<algorithm>
    #include<set>
    #include<map>
    #define inf 2147483647888888
    #define ll long long
    using namespace std;
    vector<ll> a[200866];  //使用vector数组来储存节点，更方便于表达 
    ll b[200866];
    ll f[200866];  //中转 
    ll g[200866],x,y,n,ans=-inf;  //最开始不要忘了要将ans重置为-inf 
    void dfs(ll fa,ll n)
    {
        if(a[n].size()==1&&n!=1)  //如果递归到了边界就退出递归 
        {
            g[n]=b[n];  //不要忘了这一步qwq 
            return ;
        }
        ll sum=b[n];  //选取这个点 
        for(ll i=0;i<a[n].size();i++)  //遍历这个点的所有孩子，在这一些操作中选取 
        {
            ll pos=a[n][i]; 
            if(pos==fa)
            continue;
            dfs(n,pos);
            sum+=g[pos];  //sum 和g起到了一种中转同时也保证了原图中的变量不发生变化 
        }
        g[n]=sum;
    }
    void GetDeep(ll fa,ll n)
    {
        if(a[n].size()==1&&n!=1)  //如果递归到了边界就退出 
        {
            f[n]=g[n];
            return ;
        }
        f[n]=g[n]; 
        ll maxn1=-inf,maxn2=-inf,sum=0;  //这之间maxn2其实是起到了一个中转的作用，不要忘了初始化 
        for(ll i=0;i<a[n].size();i++)
        {
            ll pos=a[n][i];
            if(pos==fa)  //假如已经到达，就退出 
            continue;
            GetDeep(n,pos);  //针对于下一层进行操作 
            if(f[pos]>maxn1)  //如果这个点的下一个 
            {
                maxn2=maxn1;  // 这个地方我调了半小时 
                maxn1=f[pos];
            }
            else
            maxn2=max(maxn2,f[pos]);
            f[n]=max(f[n],f[pos]);
        }
        ans=max(ans,maxn1+maxn2);  //这个地方就是一个求最大值 
    }
    int main()
    {
        scanf("%lld",&n);
        for(ll i=1;i<=n;i++)
        scanf("%lld",&b[i]);
        for(ll i=0;i<n-1;i++)
        {
            scanf("%lld%lld",&x,&y); //这里我用了一个vector来储存变量，这样便可以更好地实现储存 
            a[y].push_back(x);  //两个push的操作 
            a[x].push_back(y);
        }
        dfs(0,1);
        GetDeep(0,1);
        if(ans<-2147483647)
        //这个地方其实是一个很玄学的优化，因为我初始置ans==-inf的时候会发现它这个点的初始值假如在没有更改的地方也会有一定的更改 
        //但是它的初始值一定不会更改地很大 
        {
            printf("Impossible");
            return 0;
        }
        printf("%lld",ans);
        return 0;
    }
 
完结撒花

---

## 作者：Ghosty_Neutrino (赞：0)

## 分析
要求的就是在树上找两个不相交的子树 $A$ 和 $B$ 最大，首先，第一步肯定是将无根树转为有根树。

然后，我们考虑先单独求对于每个节点 $i$，以 $i$ 为根节点的最大子树和。

$d_{u,s}$ 当前节点为 $u$，选中状态为 $s$ 的最大子树和，$s=0$ 代表当前节点不选，$s=1$ 代表要选当前节点。

$s=0$ 不选择当前节点，那么一定是从子树中选一个子树和最大的节点作为当前节点的最大子树和。

$s=1$ 即要选择当前节点，那么当前节点及其子树都应该被全部选择。

最后，对于儿子数大于 $2$ 的节点，选出最大的两个子树求和，完工。

最好情况都要特判，判断无解的情况：即为 $1$ 条链的时候无解，统计一下每个节点的儿子节点数即可。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int in() {int x; scanf("%d", &x); return x;}
#define pr(x) {cout << #x << ' ' << x << endl;}
#define LL long long
const int maxn = 200000 + 5;
LL a[maxn], d[maxn][2];
int son[maxn], pa[maxn], n, vis[maxn][2];
vector<int> G[maxn];
LL dfs(int u,int s,int p,int sta) {
    if(vis[u][s]) return d[u][s];
    vis[u][s] = 1;
    pa[u] = p;
    if(G[u].size()==1&&G[u][0]==p) return d[u][s]=(s== 1?a[u]:-1e15);
    if(s==1){
        d[u][s]=a[u];
        for (auto v:G[u]) {
            if(v==p) continue;
            if(sta==1) son[u]++;
            d[u][s]+=dfs(v,1,u,sta);
        }
    }else{
        d[u][s]=-1e15;
        for (auto v:G[u]){
            if(v==p) continue;
            d[u][s]=max(dfs(v,1,u,sta),max(dfs(v,0,u,sta),d[u][s]));
        }
    }
    return d[u][s];
}
LL solve() {
    LL res=-1e18;
    for (int u=1;u<=n;u++) {
        if (son[u]<2) continue;
        vector<LL> tmp;
        tmp.clear();
        for(auto v:G[u]){
            if(v==pa[u]) continue;
            tmp.push_back(max(d[v][1], d[v][0])); 
        }
        sort(tmp.begin(), tmp.end(), greater<LL>());
        LL max1 = tmp[0], max2 = tmp[1];
        res = max(res, max1 + max2);
    }
    return res;
}
int main(){
    n=in();
    bool flag=false;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=0;i<n-1;i++){
        int u=in(),v=in();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,1,-1,1);
    for (int i=1;i<=n;i++) {
        if(son[i]>=2) flag=true;
    }
    if(!flag){cout<<"Impossible"<<endl;return 0;}
    dfs(1,0,-1,0);
    LL res=solve();
    cout<<res<<endl;
    return 0;
}
```

---

## 作者：MvemiY (赞：0)

### 题目描述

给你一棵树，求两颗不相交的子树使它们的点权总和最大，输出最大的点权和。点权可能为负。

### 题目分析

看到子树与不相交的字眼，很容易想到在 DFS 序上选取区间它们不交。

更具体地，我们将每个点为根的子树在 DFS 序上所代表的区间预处理出来，容易得到它为 $[id_u,id_u+size_u-1]$，其中 $id_u$ 表示 $u$ 点在 DFS 序上的位置。那么问题就转化为，给定 $n$ 个线段，每个线段各有一个权值，你需要找出两个互不相交的线段，使得两个线段的权值和最大。

我们知道如果两个线段 $[l_1,r_1]$ 和 $[l_2,r_2]$ 不相交当且仅当 $l_1>r_2$ 或 $l_2>r_1$。那么我们将线段存为两份，一份按左端点排序，一份按右端点排序，最后遍历每个线段，二分查找即可。

那么何时无解？容易想到当 $n=1$ 或树是一条链的时候则找不到两个不相交的线段，即无解。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
typedef long long ll;
inline ll read(){
	ll x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f; 
} 

ll n, a[MAXN], s[MAXN], fa[MAXN], siz[MAXN], dfn[MAXN], dd[MAXN], id[MAXN], tot;
ll pre[MAXN], suf[MAXN];
// pre 给 L2 用，suf 给 L1 用 
vector <int> tr[MAXN];
struct Node{
	ll l, r, val;
}L1[MAXN], L2[MAXN];


void dfs1(int u, int ff){
	dfn[++tot] = u;
	id[u] = tot;
	fa[u] = ff;
	siz[u] = 1;
	s[u] = a[u];
	int len = tr[u].size();
	for(int i = 0; i < len; i++){
		int v = tr[u][i];
		if(v == ff) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		s[u] += s[v];
	}
}

bool check(){
	for(int i = 1; i <= n; i++)
		if(dd[i] > 2) return false;
	return true && dd[1] == 1;
}

bool out(int l1, int r1, int l2, int r2){
	return l1 > r2 || l2 > r1;
}

bool cmp1(Node x, Node y){
	return x.l < y.l;
}
bool cmp2(Node x, Node y){
	return x.r < y.r;
}

int main(){
	n = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	for(int i = 1; i < n; i++){
		int u = read(), v = read();
		tr[u].push_back(v);
		tr[v].push_back(u);
		dd[u]++, dd[v]++;
	}
	dfs1(1, 0);
	if(check() || n == 1){
		cout << "Impossible";
		return 0;
	}
	for(int i = 1; i <= n; i++){
		L1[i].l = id[i], L1[i].r = id[i]+siz[i]-1, L1[i].val = s[i];
		L2[i] = L1[i];
	}
	sort(L1+1, L1+n+1, cmp1);
	sort(L2+1, L2+n+1, cmp2);
	pre[0] = LONG_LONG_MIN;
	suf[n+1] = LONG_LONG_MIN; 
	for(int i = 1; i <= n; i++)
		pre[i] = max(pre[i-1], L2[i].val);
	for(int i = n; i >= 1; i--)
		suf[i] = max(suf[i+1], L1[i].val);
	ll ans = LONG_LONG_MIN;
	for(int i = 1; i <= n; i++){
		ll sum = s[i];
		ll li = id[i], ri = id[i]+siz[i]-1;
		int L = 1, R = n, mid, tmp = 0;
		while(L <= R){
			mid = (L+R) >> 1;
			if(L2[mid].r < li)
				L = mid+1, tmp = mid;
			else R = mid-1; 
		}
		if(out(li, ri, L2[tmp].l, L2[tmp].r) && tmp != 0)
			ans = max(ans, sum + pre[tmp]);
		L = 1, R = n, tmp = 0;
		while(L <= R){
			mid = (L+R) >> 1;
			if(L1[mid].l > ri)
				L = mid+1, tmp = mid;
			else R = mid-1;
		} 
		if(out(li, ri, L1[tmp].l, L1[tmp].r) && tmp != 0)
			ans = max(ans, sum + suf[tmp]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：MuYC (赞：0)

#### 前言

思想：树链剖分

算法：一道不太难的换根(换根$dp$?感觉不算是)+线段树

首先我们明确一个众所周知的事情：

一个子树的$Dfn$(不是欧拉序！)序是连续的，子树的根节点的$Dfn$序是最小的。

然后这个子树中最大的$Dfn$序为$Dfn[root] + siz[root] - 1$

(写过树链剖分的都知道吧。)

#### 思路

因为只需要选择出两个，所以考虑枚举其中一棵子树，然后求最大的和当前字树没有重复节点的一棵子树。

考虑每次我们向儿子换根，因为每一次换根后，我们能够选择的子树的数量相对与没换之前是不断在增加的，这样子比较好维护状态。

**新的可以选择的子树有哪些**？

不难发现，新的 可以选择的子树 即:

```plain

当前节点的父亲节点为根的子树内，

除了当前点为根的子树内的所有点以及当前节点的父亲节点以外的所有节点。
```

你可以画一个图进行理解这句话。**这一句话至关重要，是这个做法的核心！**

然后我们发现，我们需要求最大值的区间被分为了两段：

![](https://cdn.luogu.com.cn/upload/image_hosting/e8jb5bx8.png)

每次能选择的子树只会加入一些新的子树而不需要删除一些子树，所以只需要比较现在能够选择的最大值与新加入的一些子树的最大值即可。

采用DFS的方式，将目前最大值作为一个参数传递，这样子方便更新，也不需要回溯。

注意要预处理一下每一棵子树的权值和，在预处理DFS的时候记录一下每一棵子树有多少个子节点以及子树的权值和。

这道题就做完了

具体可以看一看代码:

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 200005,INF = 1000000000000000000;
int n;
int a[MAXN],dfn[MAXN],sum[MAXN],now = 0;
int start[MAXN],cnt = 0,dfn_id[MAXN],siz[MAXN],Ans = -INF;

//sum[x]表示点x的子树权值和
//dfn[x]表示点x的dfn序
//a[x]表示点x一开始的权值
//siz[x]表示以x为根的子树内一共多少个点
//dfn_id[x]表示dfn序为x的点是哪一个

struct Edge {
	int next,to;
} edge[MAXN * 2];

struct Segment {
	int l,r,Max;	//普通线段树
} T[MAXN * 4];

inline int read()
{
	int x = 0 , flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar())if(ch == '-')flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar())x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

void add(int from,int to)
{
	cnt ++;
	edge[cnt].to = to;
	edge[cnt].next = start[from];
	start[from] = cnt;
	return ;
}

int DFS(int x,int from)
{
	siz[x] = 1;
	now ++;
	dfn[x] = now;
	dfn_id[now] = x;
	for(int i = start[x] ; i ; i = edge[i].next)
	{
		int to = edge[i].to;
		if(to != from && dfn[to] == 0)siz[x] += DFS(to,x);
	}
	return siz[x];
}

int DFS2(int x,int from)
{
	sum[x] = a[x];
	for(int i = start[x] ; i ; i = edge[i].next)
	{
		int to = edge[i].to;
		if(to != from)sum[x] += DFS2(to,x);
	}
	return sum[x];
}

void build(int x,int l,int r)
{
	T[x].l = l , T[x].r = r ;
	if(l == r){T[x].Max = sum[dfn_id[l]] ; return ;}
	int mid = ( l + r ) >> 1;
	build(x << 1 , l, mid);
	build(x << 1 | 1 , mid + 1 , r);
	T[x].Max = max(T[x << 1].Max , T[x << 1 | 1].Max);
	return ;
}

int GetMax(int x,int l,int r)
{
	if(l > r)return -INF;
	int Max = -INF;
	if(T[x].l >= l && T[x].r <= r)return T[x].Max;
	int mid = (T[x].l + T[x].r) >> 1;
	if(l <= mid)Max = max(Max,GetMax(x << 1 , l, r));
	if(r  > mid)Max = max(Max,GetMax(x << 1 | 1 , l , r));
	return Max;
}//线段树找最大值的板子

void Get_Ans(int x,int from,int Max)
{
	if(x != 1)
	{
		int l = dfn[from],r = dfn[from] + siz[from] - 1;
		int L = dfn[x] , R = dfn[x] + siz[x] - 1;
		Max = max((GetMax(1,l + 1,L - 1),GetMax(1,R + 1 , r)),Max);
        //更新最大值，当前点的儿子节点都会用这个最大值
        //l+1是因为当前点的根节点不能选,L-1是因为子树ｘ内的点不能选
        //R + 1是因为Ｒ仍然是子树x内的最大dfn序，被子树x包含了
		if(Max != -INF)
		Ans = max(sum[x] + Max,Ans);
	}
	for(int i = start[x] ; i ; i = edge[i].next)
	{
		int to = edge[i].to;
		if(to != from)Get_Ans(to,x,Max);//换根为自己的儿子节点
	}
	return ;
}

signed main()
{
	n = read();
	for(int i = 1 ; i <= n ; i ++)a[i] = read();
	for(int i = 1 ; i <= n - 1 ; i ++)
	{
		int u = read(), v = read();
		add(u,v);
		add(v,u);
	}
	DFS(1,0);//预处理dfn数组,dfn_id数组以及siz数组
	DFS2(1,0);//预处理sum数组
	build(1, 1 , n);
	Get_Ans(1,0,-INF);//换根获得答案
	if(Ans >= -1e14)cout << Ans;
    else cout << "Impossible";//如果答案过小显然不合法，
	return 0;
}
```


---

## 作者：Tony2 (赞：0)

我来分享一个无脑的算法~~ ~~（其实是我懒得想）~~

## dfs序 + 线段树

我第一个想到的是枚举所有点，然后再枚举一次所有非父节点/子节点的**子树的和**

朴素算法不用写了吧。。。

然后我们就考虑优化

我们发现再dfs序下当R[u]<L[v]时（u和v时枚举的两个点）v肯定不是u的父节点/子节点，也就是把每一个点的**子树的和**扔到dfs序构造成的数组（u点的子树的和的存储位置就是L[u]， 反之，第i个位置存的是dfs序的第i个点）

这个操作就直接在线段树build的时候就操作

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200005;
int n, w[N];
ll sum[N], ans=-0x3f3f3f3f3f3f3f3f;
ll a[N*4];//线段树
int tot=0, c[N], L[N], R[N];
vector<int> e[N];
void up(int now){
	a[now] = max(a[now<<1], a[now<<1|1]);
}
void build(int l, int r, int now){
	if (l == r){
		a[now] = sum[c[l]];//c就是dfs序存储的节点编号
		return;
	}
	int mid = (l+r)>>1;
	build(l, mid, now<<1);
	build(mid+1, r, now<<1|1);
	up(now);
}
ll ask(int l, int r, int now, int s, int t){
	if (s <= l && r <= t) return a[now];
	int mid = (l+r)>>1;
	ll res = -0x3f3f3f3f3f3f3f3f;
	if (s <= mid) res = max(ask(l, mid, now<<1, s, t), res);
	if (t > mid) res = max(ask(mid+1, r, now<<1|1, s, t), res);
	return res;
}
void dfs1(int u, int fa){
	sum[u] = w[u];
	c[++tot] = u;
	L[u] = tot;
	for (int i = 0; i < e[u].size(); i++){
		int v = e[u][i];
		if (v == fa) continue;
		dfs1(v, u);
		sum[u] += sum[v];
	}
	R[u] = tot;
}
int main(){
	std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1; i < n; i++){
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1, 0);
	build(1, n, 1);
	for (int i = 1; i <= n; i++){
		if (R[i]+1 > n) continue;
		ans = max(ask(1, n, 1, R[i]+1, n)+sum[i], ans);
	}
	if (ans >= -1e15) cout << ans;
	else cout << "Impossible";
	return 0;
珍爱生命，远离抄袭
} 
```

## 最后求管理员大大通过！！QWQ

---

