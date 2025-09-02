# Christmas Chocolates

## 题目描述

Christmas is coming, Icy has just received a box of chocolates from her grandparents! The box contains $ n $ chocolates. The $ i $ -th chocolate has a non-negative integer type $ a_i $ .

Icy believes that good things come in pairs. Unfortunately, all types of chocolates are distinct (all $ a_i $ are distinct). Icy wants to make at least one pair of chocolates the same type.

As a result, she asks her grandparents to perform some chocolate exchanges. Before performing any chocolate exchanges, Icy chooses two chocolates with indices $ x $ and $ y $ ( $ 1 \le x, y \le n $ , $ x \ne y $ ).

In a chocolate exchange, Icy's grandparents choose a non-negative integer $ k $ , such that $ 2^k \ge a_x $ , and change the type of the chocolate $ x $ from $ a_x $ to $ 2^k - a_x $ (that is, perform $ a_x := 2^k - a_x $ ).

The chocolate exchanges will be stopped only when $ a_x = a_y $ . Note that other pairs of equal chocolate types do not stop the procedure.

Icy's grandparents are smart, so they would choose the sequence of chocolate exchanges that minimizes the number of exchanges needed. Since Icy likes causing trouble, she wants to maximize the minimum number of exchanges needed by choosing $ x $ and $ y $ appropriately. She wonders what is the optimal pair $ (x, y) $ such that the minimum number of exchanges needed is maximized across all possible choices of $ (x, y) $ .

Since Icy is not good at math, she hopes that you can help her solve the problem.

## 说明/提示

In the first test case, the minimum number of exchanges needed to exchange a chocolate of type $ 6 $ to a chocolate of type $ 9 $ is $ 5 $ . The sequence of exchanges is as follows: $ 6 \rightarrow 2 \rightarrow 0 \rightarrow 1 \rightarrow 7 \rightarrow 9 $ .

In the second test case, the minimum number of exchanges needed to exchange a chocolate of type $ 4 $ to a chocolate of type $ 8 $ is $ 2 $ . The sequence of exchanges is as follows: $ 4 \rightarrow 0 \rightarrow 8 $ .

## 样例 #1

### 输入

```
5
5 6 7 8 9```

### 输出

```
2 5 5
```

## 样例 #2

### 输入

```
2
4 8```

### 输出

```
1 2 2```

# 题解

## 作者：MatrixCascade (赞：8)

因为昨天只能打 30min 就根本没看这个题，今天看见就补了一下  。

感觉没什么技巧的题，不知道为啥这个题放在了 E。

首先，手模了一下发现这个图是一棵树。(证明也很容易，每一个非 0 节点有且仅有一条边连向比自己小的节点，并且如果考虑数值在 $0\to2^i$ 内的点，边数是 $2^i$ 条。 )

然后此题就转换成了一个树的直径问题。

我们令节点 0 为根节点，不难证明 $x$ 号节点的深度最大是 $\log_2^x$ 级别的，如果要求 $x$ 到根节点的距离只需暴力跳父亲节点就行，$x$ 号的父亲节点是 $\ge x$ 的最小 $2^i$，显然可以在 $\log$ 时间内计算出来。(可能可以 $O(1)$?)

然后根据直径的性质，求出离 $a_1$ 最远的点，下标记做 $x$。再求出离 $a_x$ 最远的点即可。

关于如何求两个点的距离，考虑暴力求出两个点在原树上的 lca，由于深度是 $\log$ 级别的，直接用最原始的 lca 方法暴力跳，加上找父亲的 $\log$，复杂度是 $(\log)^2$，总复杂度 $O(n(\log_2^n)^2)$。

大概花了~~半节地理课~~(20min 左右)想出这个方法，写的话貌似就写了 15 分钟左右。

代码(完全没细节，很容易理解)

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
int a[202020];
int get(int x)
{
	//暴力求 father
	int nw=1;
	while(nw<x)
	{
		nw*=2;
	}
	return nw-x;
}
int dis(int x)
{
	//求一个点到根节点(0)的距离
	if(x==0)return 0;
	int ans=0;
	return dis(get(x))+1;
}
int lca(int x,int y)
{
	if(dis(x)<dis(y))
	{
		swap(x,y);
	}
	int a=dis(x),b=dis(y);
	while(a>b)
	{
		x=get(x);
		--a;
	}
	if(x==y)return x;
	while(x!=y)
	{
		x=get(x);y=get(y);
	}
	return x;
   //暴力求 lca
}
int dist(int x,int y)
{
	return dis(x)+dis(y)-2*dis(lca(x,y));
   //求两个点在原树上的距离
}
signed main()
{
	int T=1;
	//cout<<lca(3,13);
	while(T--)
	{
		rdn;
		upn rd(a[i]);
        
      //树的直径  
      
		int px=1;
		up(i,2,n)
		{
			if(dist(1,a[i])>dist(1,a[px]))
			{
				px=i;
			}
		}
		int py=px;
		up(i,1,n)
		{
			if(dist(a[px],a[i])>dist(a[px],a[py]))
			{
				py=i;
			}
		}
		cout<<px<<" "<<py<<" "<<dist(a[px],a[py]);
	}
}
```


---

## 作者：Otomachi_Una_ (赞：3)

一道很奇怪的淼淼题。

## 题目简述

- 定义对 $x$ 的操作为随便找一个 $k,2^k\geq x$，$x\leftarrow 2^k-x$。
- 定义 $dis(x,y)$ 为对 $x$ 进行若干次操作使得 $x=y$ 的最小操作数。
- 最大化 $dis(a_i,a_j)$。
- $n\leq2\times 10^5$。

## 解题思路

我们建一张无穷节点图，两个点 $u,v$ 相连当且仅当 $u+v$ 是 $2$ 的方幂。

我们会得到一张奇怪的图。下面证明这张图是一个树。

首先题目说到了

> We can show that $m \le 10^9$ for any pair of chocolates.

所以这张图是联通的。

假设存在 $u_1,u_2\dots u_k$ 使得 $u_1,u_2,\dots u_k$ 构成一个环。那么不妨假设 $u_1$ 是最大者，那么 $u_k,u_2\leq u_1$，所以说 $u_k=u_2$ 矛盾！

所以这张图是一棵树。

现在的问题变成了树上直径的问题，这就非常简单了。

定义 $fa(x)$ 函数是寻找 $x$ 节点父亲的函数，实现见代码。这样下去就是一个简单的直径问题。

## 参考代码

```cpp
#include<iostream>
using namespace std;
const int MAXN=2e5+5;
int n;
int a[MAXN];
int fa(int x){
	for(int i=0;;i++) if((1<<i)>=x) return (1<<i)-x;
}
int dis(int x,int y){
	int ans=0;
	while(x!=y){
		if(x>y) swap(x,y);
		ans++;
		y=fa(y);
	}
	return ans;
}
int maxx(int x){
	int id=1,pre=dis(a[x],a[1]);
	for(int i=2;i<=n;i++)
		if(pre<dis(a[x],a[i])){
			id=i;
			pre=dis(a[x],a[i]);
		}
	return id;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int t1=maxx(1),t2=maxx(t1);
	cout<<t1<<" "<<t2<<" "<<dis(a[t1],a[t2]);
}
```


---

## 作者：Querainy (赞：2)

想象一下，操作过程必然是，先不停操作掉最高位让 $x$ 变小，然后不停操作产生新的最高位直到达到 $y$。判断一个数能否达到 $y$，可以不停操作掉 $y$ 的最高位，这样会得到 $O(\log v)$ 个数。可以发现，对于每个 $a_i$，不停操作掉它的最高位得到一个序列，那么我们实际上是求两个序列的长度和减去它们 lcp 长度的 $2$ 倍的最小值。由于这个序列显然是递减的，它给出一棵根为 $0$ 的内向树，操作数就是这个树上的距离，所以求直径即可。复杂度 $O(n\log v)$。

因为不是很理解如何一眼建出图来所以写一篇。

---

## 作者：voruala (赞：1)

## 写在前面

这个题的其它题解好像没太说清楚树到底是怎么建的，我在这再详细解释一下.

## 题目分析

通过阅读原题的$Note$：$6\rightarrow2\rightarrow0\rightarrow1\rightarrow7\rightarrow9$，可以发现$6$和$2$之间要有边，$2$和$0$之间要有边，$0$和$1$之间要有边，等等. 也就是说，$6$到$9$通过一些边到达，并且"交换巧克力"次数就是两点间的距离。

容易发现，对于$i\in[1,10^9]$，都可以经过一些边连接到$0$.

连边的方式就是【$x$和$2^k-x$之间】，其中$k$是令$2^k-x\geq0$的最小的$k$.

对于每一个图都大概长这样（只列举了一些比较小的数）：

![](https://cdn.luogu.com.cn/upload/image_hosting/9fo9uksh.png)

往下是求树的直径，别的题解已经写的很清楚了。

---

## 作者：Tyyyyyy (赞：1)

# CF1617E
#### 题意简述
- 给定 $n$ 个**互不相同**的非负整数 $a_1,\dots,a_n$。

- 希望能把其中一对整数 $a_x,a_y$ 变为相等的。选定下标 $x,y$ 后，可以进行如下操作直到 $a_x=a_y$：选择一个满足 $2^k\geq a_x$ 的非负整数 $k$，并使 $x\gets 2^k-x$。
- 在将 $a_x$ 变成 $a_y$ 的过程中，总是会选择操作次数最小的方式来进行操作。
- 希望选出一对下标 $(x,y)$，使得**将 $a_x$ 变成 $a_y$ 的最小次数最大化**。
- 输出这对下标和操作次数。若有多解，输出任意一组。
- $2 \leq n \leq 2\times 10^5,0 \leq a_i \leq 10^9$。可以证明，将任何一个 $a_x$ 变为 $a_y$ 的最小步数在 $10^9$ 步以内。

#### 题目分析
考虑将题目中的变化过程转化为一张图。可以发现这张图是一棵树。

严谨地，有以下结论：对于任何一个 $i \in[0,10^9]$，则有唯一的 $j \in[0,i)$，使得 $i+j=2^k$ 对于某个 $k$ 成立。

证明如下：

设 $0 \leq j_2 \leq j_1 <i,i+j_1=2^{k_1},i+j_2=2^{k_2}$，则 $j_1-j_2=2^{k1}-2^{k2}=2^{k2}(2^{k_1-k_2}-1)$。故有 $j_1 \bmod 2^{k2}=j_2\bmod 2^{k2}$。因为 $j_1,j_2<i\leq 2^{k2}$，所以 $j_1=j_2$。 

将题目中所给的 $a_i$ 看作叶子节点，则问题转化为了树上的直径问题。

接下来只需要解决一个问题：这棵树的规模在 $10^9$ 级别，无法存下。

通过观察可以发现这棵树上的节点满足父节点代表的数总是大于子节点代表的数。因此树高最多为 $\operatorname{log}10^9$。我们考虑只连 $a_i$ 及它（们）的祖先之间的边，则这棵树的大小最多为 $n\operatorname{log}10^9$，可以存下。

至此该问题得到了解决，时空复杂度均为 $O(n\operatorname{log}10^9)$。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010];
vector<int>anc[200010];
vector<int>v;
int tot,h[6000010];
struct node
{
	int v,nxt;
}e[12000010];
void add(int u,int v)
{
	e[++tot]=(node){v,h[u]};
	h[u]=tot;
}
int dis[6000010];
bool vis[6000010];
void dfs(int u,int fa)
{
	dis[u]=dis[fa]+1;
	vis[u]=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		dfs(v,u);
	}
} 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		int cur=a[i];
		anc[i].push_back(cur);
		for(int j=30;j>=1;j--)
			if((1<<j-1)<cur&&(1<<j)>cur)cur=(1<<j)-cur,anc[i].push_back(cur);
		if(cur!=0)anc[i].push_back(0);
		for(auto j:anc[i])v.push_back(j);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(int)anc[i].size();j++)
			anc[i][j]=lower_bound(v.begin(),v.end(),anc[i][j])-v.begin()+1;
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j+1<(int)anc[i].size();j++)
			add(anc[i][j],anc[i][j+1]),add(anc[i][j+1],anc[i][j]);
	dis[0]=-1;
	dfs(1,0);
	int mx=1;
	for(int i=1;i<=n;i++)if(dis[anc[i][0]]>dis[anc[mx][0]])mx=i;
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis)); 
	dis[0]=-1;
	dfs(anc[mx][0],0);
	int mx2=1;
	for(int i=1;i<=n;i++)if(dis[anc[i][0]]>dis[anc[mx2][0]])mx2=i;
	printf("%d %d %d",mx,mx2,dis[anc[mx2][0]]);
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：0)

感觉最直观最显然的做法，不知道为什么没有人提。

考虑手玩一下样例，一个二的次幂减掉数 $x$，我们反过来考虑 $x$ 加上什么数会变成 $2$ 的次幂。

![](https://pic1.imgdb.cn/item/67eb9f200ba3d5a1d7e9066b.png)

容易发现其实是这样，首先 lowbit 不变，比 lowbit 低的位也都不变，因为需要进位。

然后到你打算变成的二的次幂的前一位打止，所有位都取反。

然后考虑我们知道这个变化规则之后怎么来做这个题。

1. lowbit 不同

显然我们只能先消成 0，再合并回我要变成的数，那么也就是两个数变成 0 的次数加和。

2. lowbit 相同

考虑我们可以通过消除其中一些前缀连续段使得后缀连续段相同。

所以有一个自然而然的想法就是把 lowbit 扔掉之后建立反向 01trie 然后直接搜，然后他是假的。

然后你考虑为什么，其实是因为我只关心连续段而并不关系其具体数值，所以我们考虑对其二进制位做异或差分，然后再建立反向 01trie，此时即可直接搜索计算答案。

时间复杂度 $O(n\log V)$。

可能稍微有一点点细节和边界判断。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int A[200005];
int lowbit(int x){return x&-x;}
int get0(int x){
   if(!x)return 0;
   int tmp=1;
   while(!(x&1))x>>=1;
   x>>=1;
   while(x){
      tmp++;
      if(x&1){
         while(x&1)x>>=1;
      }
      else{
         while(!(x&1))x>>=1;
      }
   }
   return tmp;
}
int calc(int x,int y){
   if(lowbit(x) xor lowbit(y)){
      return get0(x)+get0(y);
   }
   bool flg=false;
   int num=0;
   for(int i=__lg(lowbit(x))+1;i<=30;i++){
      if((((x>>i)&1)xor((x>>(i+1))&1))xor(((y>>i)&1)xor((y>>(i+1))&1))){
         flg=true;
      }
      if(flg){
         num+=((((x>>i)&1)xor((x>>(i+1))&1)));
         num+=((((y>>i)&1)xor((y>>(i+1))&1)));
      }
   }
   return num;
}
pair<int,int> tmp;
vector<int> id[100];
struct node{
   int x,y,z;
   bool friend operator < (const node &a,const node &b){
      return a.z<b.z;
   }
};
class trie01{
   public:
   int ch[200005<<5][2];
   int Max[200005<<5];
   int Maxid[200005<<5];
   int tot;
   void clear(){
      for(int i=0;i<=tot;i++){
         ch[i][0]=ch[i][1]=Max[i]=0;
      }
      tot=0;
      return;
   }
   void insert(int id,int x,int j){
      int now=0;
      for(int k=j+1;k<=30;k++){
         int nxt=((((x>>k)&1)xor((x>>(k+1))&1)));
         if(!ch[now][nxt])ch[now][nxt]=++tot;
         now=ch[now][nxt];
      }
      Maxid[now]=id;
      return;
   }
   void getMax(int cur){
      if(ch[cur][0]){
         getMax(ch[cur][0]);
         if(Max[ch[cur][0]]>=Max[cur]){
            Maxid[cur]=Maxid[ch[cur][0]];
            Max[cur]=Max[ch[cur][0]];
         }
      }
      if(ch[cur][1]){
         getMax(ch[cur][1]);
         if(Max[ch[cur][1]]+1>=Max[cur]){
            Maxid[cur]=Maxid[ch[cur][1]];
            Max[cur]=Max[ch[cur][1]]+1;
         }
      }
      return;
   }
   node getans(int cur){
      node ans={0,0,0};
      if(ch[cur][0])ans=max(getans(ch[cur][0]),ans);
      if(ch[cur][1])ans=max(getans(ch[cur][1]),ans);
      if(ch[cur][0]&&ch[cur][1])ans=max(ans,node{Maxid[ch[cur][0]],Maxid[ch[cur][1]],Max[ch[cur][0]]+Max[ch[cur][1]]+1});
      return ans;
   }
}T;
node ans;
int pmax;
void solve(int j){
   T.clear();
   for(int i=0;i<id[j].size();i++){
      int tmp=A[id[j][i]];
      T.insert(id[j][i],tmp,j);
   }
   T.getMax(0);
   node tmp=T.getans(0);
   ans=max(ans,tmp);
   if(pmax){
      for(int i=0;i<id[j].size();i++){
         int tmp=A[id[j][i]];
         ans=max(ans,node{id[j][i],pmax,get0(tmp)+get0(A[pmax])});
      }
   }
   for(int i=0;i<id[j].size();i++){
      int tmp=A[id[j][i]];
      if(get0(tmp)>get0(A[pmax]))pmax=id[j][i];
   }
   return;
}
int main(){
   scanf("%d",&n);
   for(int i=1;i<=n;i++){
      scanf("%d",&A[i]);
   }
   for(int i=1;i<=n;i++){
      if(!A[i]){
         pmax=i;
         continue;
      }
      id[__lg(lowbit(A[i]))].push_back(i);
   }
   for(int j=0;j<=30;j++){
      solve(j);
   }
   printf("%d %d %d\n",ans.x,ans.y,ans.z);
   return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/imfvlbnu.png?x-oss-process=image)

教会你如何 5 分钟找到规律并通过这题。

考虑对 $x\to 2^k-x$ 这个事情建图。比较重要的事情是发现操作可逆，所以我们完全可以只保留一个方向的边，比如只保留 $x<2^k-x$ 的边，这样形成一张 DAG。

看起来没什么头绪，所以先打一点表看一下，发现居然连成一棵树，$x(x\neq 0)$ 的父亲是最小的满足 $2^k\ge x$ 的 $2^k-x$。也就是说每个 $[2^k+1,2^{k+1}]$ 区间内的点恰好连向了 $[0,2^k-1]$ 的点。所以容易发现树的深度是 $\mathcal O(\log V)$ 的。

既然深度很小，求 $m$暴力就行了。原题要求的是最远点对，也就是直径。套用树上直径的经典维护方式即可，每次维护当前的直径端点，和新的点组成新的路径，判断是否更优。时间复杂度 $\mathcal O(n\log V)$。我一开始写成 $\mathcal O(n\log^2V)$ 了也能过。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=2e5+9;
ll n,a[N];
ll Fa(ll x){
    ll o=__lg(x);
    if((1ll<<o)==x)return 0;
    return (1ll<<(o+1))-x;
}
ll Dep(ll x){
    ll dep=0;
    while(x)dep++,x=Fa(x);
    return dep;
}
ll Dis(ll x,ll y){
    ll dis=0,dx=Dep(x),dy=Dep(y);
    while(x!=y){
        if(dx<dy)swap(x,y),swap(dx,dy);
        x=Fa(x),dis++,dx--;
    }
    return dis;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,1,n)a[i]=read();
    ll X=1,Y=1,D=0;
    rep(i,2,n){
        ll d1=Dis(a[i],a[X]),d2=Dis(a[i],a[Y]);
        if(d1>=d2&&d1>=D)D=d1,Y=i;
        else if(d2>=d1&&d2>=D)D=d2,X=i;
    }
    write(X),putchar(' '),write(Y),putchar(' '),write(D),putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：0)

牛魔神必做法。

考虑 $0$ 操作到 $x$ 的最优策略。

发现 $(x-(y-z)) = x - y + z$，也就是说，在一个数的基础上可以用两次操作直接加上 $2^{k_1}-2^{k_2}(k_1>k_2)$，也即在其二进制表示下，在高位加上连续一段 $1$。

特别地，当前数为 $0$ 时，可以用 $1$ 次操作在某一位上加上 $1$。

$x$ 在二进制表示下可以从高位到低位分解为 $[l_1,r_1],[l_2,r_2]\cdots [l_m,r_m]$ 这 $m$ 段 $1$，依据上文分析可得从 $x$ 到 $0$ 的最小操作次数为 $2m-[l_m = r_m]$。

并且我们可以知道需要进行的操作具体是什么。

假设需要操作的分别是 $2^{k_1},2^{k_2},\cdots 2^{k_s}$，则记 $m_x=\displaystyle \sum_{i=0}^{l}2^{k_i}$，可得不同的 $x$ 所对应的 $m_x$ 也不同。

那么 $x$ 到 $y$ 可以用 $m_x+m_y$ 次操作完成，先 $x$ 到 $0$ 再 $0$ 到 $y$。当然不一定要这么干，完全可以不搞到 $0$。

集中注意力，发现假设 $x$ 要操作的是 $2^{k_1},2^{k_2},\cdots 2^{k_{l_x}}$，$y$ 要操作的是 $2^{k'_1},2^{k'_2},\cdots 2^{k'_{l_y}}$（递增排序），且 $\forall i\in [1,t] \ \text{s.t.} 2^{k_i}=2^{k'_i}$，则最少操作次数为 $m_x+m_y-2t$，原因在于在两步的公共前缀的操作都可以互相抵消，不用做了。

于是剩下的简单了，把 $m_{a_i}$ 都插到 trie 上，结点上保存子树内的 $\max\{\operatorname{popcount(m_x)}\}$ ，dfs 枚举 $m_{a_i}$ 和 $m_{a_j}$ 对应的 lcp 即可。

code 

```cpp
#include <bits/stdc++.h>
int n, a[200005];
int ch[200005 * 31][2], tot = 1, vm[200005 * 31], vs[200005 * 31];
int ans = -100, v1, v2;
void insert(int x, int y){
  int now = 1; int t = __builtin_popcount(x);
  for(int w = 0; w <= 30; ++w){
    int s = (x & (1 << w)) ? 1 : 0;
    if(!ch[now][s]) ch[now][s] = ++tot;
    now = ch[now][s];
    if(t > vm[now]) vm[now] = t, vs[now] = y;
  }
  return ;
}
void dfs(int now, int p){
  if(ch[now][0] && ch[now][1]){
    if(ans < vm[ch[now][0]] + vm[ch[now][1]] - p * 2){
      ans = vm[ch[now][0]] + vm[ch[now][1]] - p * 2;
      v1 = vs[ch[now][0]], v2 = vs[ch[now][1]];
    }
  }
  if(ch[now][0]) dfs(ch[now][0], p);
  if(ch[now][1]) dfs(ch[now][1], p + 1);
  return ;
}
int main(){
  scanf("%d", &n);
  for(int i = 1; i <= n * 31; ++i) vm[i] = -100;
  for(int i = 1; i <= n; ++i){
    scanf("%d", &a[i]);
    int msk = 0; int sa = 1;
    for(int j = 0, k; j <= 29; j = k + 1){
      k = j;
      if(!(a[i] & (1 << j))) continue;
      while(k < 29 && (a[i] & (1 << k + 1))) ++k;
      if(sa && j == k) msk |= (1 << j);
      else msk |= ((1 << j) | (1 << k + 1));
      sa = 0;
    }
    insert(msk, i);
  }
  dfs(1, 0);
  printf("%d %d %d\n", v1, v2, ans);
  return 0;
}
```




---

## 作者：syzf2222 (赞：0)

抽象成一个图论问题。无向图，无穷个点，若 $x+y=2^k$ 则有边，求 $n$ 个特殊点中两两最短路的最大值。

因为是无向图，我们考虑大的往小的连边。我们惊喜地发现这样的边只有一条，即 $2^k$ 恰好大于 $x$ 时有解。易证。

于是原图退化成了一棵 $n\log n$ 级别个点的树。求两叶子节点间的最大距离即可。随意实现。我的实现比较诡异。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
#define fi first
#define se second
#define pii pair<int,int>
#define mkp make_pair
map<int,pii>mp;
inline int f(int x){for(int i=0;;i++)if((1<<i)>=x)return (1<<i);}
int n,m,k,s,u,v,ans;
int main(){
	n=read();
	for(int i=1,x;i<=n;i++)
		x=read(),mp[x]=mkp(0,i);
	while(k=(--mp.end())->fi){
		s=f(k)-k;
		if(mp.find(s)!=mp.end()&&ans<mp[s].fi+mp[k].fi+1){
			ans=mp[s].fi+mp[k].fi+1;u=mp[s].se,v=mp[k].se;
		}if(mp[s].fi<mp[k].fi+1)mp[s]=mkp(mp[k].fi+1,mp[k].se);
		mp.erase(k);
	}printf("%d %d %d\n",u,v,ans);
    return 0;
}
```

深深地感到自己的弱小。

---

