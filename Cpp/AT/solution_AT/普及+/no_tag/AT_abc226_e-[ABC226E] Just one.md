# [ABC226E] Just one

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc226/tasks/abc226_e

$ N $ 頂点 $ M $ 辺の無向グラフが与えられます。 頂点は頂点 $ 1 $ ,頂点 $ 2 $ , $ \ldots $ ,頂点 $ N $、辺は辺 $ 1 $ ,辺 $ 2 $ , $ \ldots $ ,辺 $ M $ と番号付けられており、特に辺 $ i $ $ (1\ \leq\ i\ \leq\ M) $ は頂点 $ U_i $ と頂点 $ V_i $ を結んでいます。 また、このグラフは単純であることが保証されます。すなわち、自己ループや多重辺は存在しません。

このグラフの $ M $ 本の辺すべてに向き付けをする方法は $ 2^M $ 通り考えられますが、 そのうち、どの頂点についても、その頂点から他の頂点に向かう辺がちょうど $ 1 $ 本ずつ存在するような向き付けの方法は何通りありますか。 答えは非常に大きくなる可能性があるので、$ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ U_i,V_i\ \leq\ N $
- $ U_i\ \neq\ V_i $
- 入力は全て整数である。
- 与えられるグラフは単純である。

### Sample Explanation 1

条件をみたす辺の向き付けの方法は、 - $ 1\rightarrow\ 2 $ , $ 2\rightarrow\ 3 $ , $ 1\leftarrow\ 3 $ - $ 1\leftarrow\ 2 $ , $ 2\leftarrow\ 3 $ , $ 1\rightarrow\ 3 $ の $ 2 $ 通りです。

### Sample Explanation 2

すべての頂点から $ 1 $ 本ずつ辺が出ているようにすることは明らかに不可能です。

## 样例 #1

### 输入

```
3 3
1 2
1 3
2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1
1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
7 7
1 2
2 3
3 4
4 2
5 6
6 7
7 5```

### 输出

```
4```

# 题解

## 作者：AzureHair (赞：4)

简明题干：

$n$ 个点 $m$ 条边的无向图，求每个点有且仅有一条出边的方案总数。

首先容易发现一个点仅对应一条出边所以 $n$ 和 $m$ 一定是相等的，如果不相等则无解输出0。

接下来能够发现 $n=m$ 所以这应该是一个基环森林，那么对于一个基环树，对于叶子节点向上取边作为出度，由于根节点一定在基环上，所以最终只需考虑一个环上能产生多少贡献即可，容易发现环上只有正向和反向两种情况，所以答案即为 $2^x$，$x$ 为连通块的个数，但是要注意，如果连通块内不是基环树那么答案为零，记得要判断，代码也比较简单，直接放下代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m,cnt=0,head[200010],cntn,cntm,vis[200010],ans=1;
struct node
{
	int next,to;
}e[400010];
void add(int from,int to)
{
	e[++cnt].next=head[from];
	e[cnt].to=to;
	head[from]=cnt;
}
void dfs(int x,int fa)
{
	vis[x]=1;cntn++;
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		cntm++;
		if(to==fa)continue;
		if(vis[to])continue;
		dfs(to,x);
	}
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	if(n!=m)
	{
		cout<<0<<endl;
		return 0;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cntn=0,cntm=0;
			dfs(i,0);
			if(cntn!=cntm/2)
			{
				cout<<0<<endl;
				return 0;
			}
			ans=ans*2%mod;
		}
	}
	cout<<ans%mod<<endl;
	return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：2)

# 思路
通过看题对于每一个连通分量只能有一个环。

下面的这一个图是个图的遍历顺序，这里不遍历父节点，然后金色的边是遍历到已经遍历到的节点，那么如果金色的边不是 $2$ 条那就一定不是只有一个环，最后如果一个连通分量满足条件就有两种方式。

![](https://cdn.luogu.com.cn/upload/image_hosting/arhugrmf.png)

因为每个连通分量如果可以的话反着建边也一定是可以的，那么最后的总方案数就是 $2^{\text{连通分量的个数}}$，如果有一个连通分量不满足条件，那就一定不存在方案。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000000,mod=998244353;
vector<int>e[maxn];int vis[maxn],cnt;
void dfs(int u,int f){
	vis[u]=1;
	for(int v:e[u]){
		if(v!=f){
			if(!vis[v]){
				dfs(v,u);
			}
			else{
				cnt++;
			}
		}
	}
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	int ans=1;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			cnt=0;
			dfs(i,0);
			// cout<<cnt<<"\n";
			ans=(ans*(cnt==2?2:0))%mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：HEzzz (赞：1)

## 思路

首先容易发现一个点仅对应一条出边所以 $n$ 和 $m$ 一定是相等的，如果不相等则无解输出 $0$。然后我们把它建成一个图，可以发现它是长这样子。

![](https://cdn.luogu.com.cn/upload/image_hosting/f1uovvrg.png)

可以发现对于我标蓝色的结点，他们的根节点都是包括在中间那个环里面，所以只需要考虑这个环上能产生多少贡献即可，接着我们可以得出答案为 $2^x$，$x$ 为连通块的个数。

然而有一个特殊情况，就是连通块内不是基环树，那么答案就是 $0$。

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl;
typedef double db;
const int N=2e5+10,Mod=998244353;
int vis[N],cnt,n,m,ans=1;
vector<int>e[N];
template<typename Type=int> inline Type read(){
	Type x=0,f=1;char ch=getchar();
	while(!isdigit(ch))(ch=='-')&&(f=-f),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x*f;
}
template<typename Type> void write(Type x){
	if(x<0) putchar('-'),x=-x;
	if(x<10) return putchar(x+'0'),void();
	write(x/10);putchar(x%10+'0');
}
void dfs(int u,int fa)
{
	vis[u]=1;
	for(int v:e[u])
	{
		if(v!=fa)
		{
			if(!vis[v]) dfs(v,u); 
			else cnt++; 
		}
	}
}
int main()
{
	n=read();m=read();
	_rep(i,1,m)
	{
		int u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	} 
	_rep(i,1,n)
	{
		if(!vis[i])
		{
			cnt=0;
			dfs(i,0);
			if(cnt==2) ans=ans*2%Mod;
			else ans=0;
		}
	}
	write(ans);
	return 0;
}

---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc226_e)

每个点出一条边，图不一定联通，这显然是一个基环森林。

考虑一棵基环树有多少种方案。环上的点有且仅有顺逆时针两种指向，其他点只能向自己的父亲指，方案数为 $2$。

那么对于每个联通块判一下是不是基环树，如果是则答案翻倍，否则输出 $0$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,mod=998244353;
int n,m,ans,E,D;
bool vis[N];
vector<int>e[N];
void dfs(int u){
    if(!vis[u])D++;else return;
    vis[u]=1;
    for(int v:e[u])if(!vis[v])dfs(v);
    E+=e[u].size();
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<=m;i++){
        scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    ans=(m==n);
    for(int i=1;i<=n;i++)if(!vis[i])
        {E=D=0;dfs(i);if(D==E/2)ans=2ll*ans%mod;else ans=0;}
    printf("%d\n",ans);
    // system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/135015633)

---

## 作者：Nicrobot (赞：0)

对每个连通块分别考虑，乘起来。

设连通块有 $n$ 个点，$m$ 条边。

当 $m\neq n$ 时，显然无法满足要求。整个图答案是 $0$。

当 $m=n$ 时是一个基环树。环上的点可以顺着逆着两个方向走；环外的点只能连向环。

使用并查集维护连通块点和边的数量，判断是不是相等的，即可判断一个连通块是不是基环树。

---

## 作者：wangyishan (赞：0)

# [ABC226E] Just one 题解

## 题目翻译

给你一个 $N$ 个点 $M$ 条边的无向图，保证没有重边和自环。

要求你给每一条边加附一个方向，使得这张图上的所有点有且只有一条出边。

由于答案可能很大，你只需要输出答案取模 $ 998244353 $ 的值。

$N,M\leq 2\times 10^5$

## 思路

首先如果每个点有且只有一条出边的话，那么边数一定和结点个数相等。这就是一个基环树森林（对于每一个连通块，都是一个基环树）。

我们观察一个基环树，发现 ta 有两种构造方法：顺时针和逆时针。
所以对于 $n$ 个联通块，就会有 $2^n$ 种可能（前提是 ta 们都是基环树）。有一个不是，那么答案就是 $0$。

那么如何判断基环树呢？~~你当然可以用并查集~~，但是根据基环树的性质，只要判断结点个数和边数是否相等即可。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
#define int long long 
vector<int>e[200010];
const int mod=998244353;
int color[200010];
int tot=0;
int bs=0;
int dfs(int u,int col){//dfs搜连通块
    color[u]=col;
    int ans=0;//点数
    for(auto i:e[u]){
        if(!color[i])ans+=dfs(i,col);
        bs++;//边数
    }
    ans++;
    return ans;
}
int qpow(int a,int b,int m){//快速幂
    int ans=1,base=a;
    while(b){
        if(b&1)ans=base*ans%m;
        base=base*base%m;
        b>>=1;
    }
    return ans;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!color[i]){
            tot++;bs=0;
            int num=dfs(i,tot);
            if(num!=bs/2){//因为存了双向边，所以要除以二
                cout<<0;
                return 0;
            }
        }
    }
    cout<<qpow(2,tot,mod);
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

题意：给一张无向图，求给每条边定向，使得每个点都恰好有一条出边的方案数。

观察到实际上符合条件的图只有基环树，且给每个基环树定向只有 $ 2 $ 种方案，因此统计原图中基环树的数量 $ m $ 之后答案即为 $ 2^m $。

证明：首先因为每个连通块恰好有一条出边，所以原图一定是一个 $ n $ 个点 $ n $ 条边的结构，这样的图一定是一个基环树，然后根据乘法原理只需要把每个基环树的答案相乘即可，注意到基环树的边定向只有内向树和外向数两种可能，得证。

求基环树数量可以用并查集维护，时间复杂度 $ \mathcal{O}(n+m) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int father[200020],ans[200020],sizei[200020];
long long binpow(long long a,long long b,long long m)
{
    a%=m;
    long long res=1;
    while(b>0)
    {
        if(b&1) 
        res=res*a%m;
        a=a*a%m;
        b>>=1;
    }
    return res%m;
}
int find(int x)
{
    if(x==father[x])
    return x;
    else
    {
        father[x]=find(father[x]);
        return father[x];
    }
}
void conj(int a,int b)
{
    if(find(a)!=find(b))
    {
        ans[father[b]]+=ans[father[a]]+1;
        ans[father[a]]=ans[father[b]];
        father[find(a)]=father[b];
    }
    else
    ans[find(a)]++;
}
int main()
{
ios::sync_with_stdio(0);
int n,m;
cin>>n>>m;
for(int i=1;i<=n;i++)
father[i]=i;
for(int i=1;i<=m;i++)
{
int a,b;
cin>>a>>b;
conj(a,b);
}
//for(int i=1;i<=n;i++)
//cout<<father[i]<<endl;
for(int i=1;i<=n;i++)
sizei[find(i)]++;
int cnt=0;
for(int i=1;i<=n;i++)
{
if(sizei[i])
if(sizei[i]==ans[i])
cnt++;
else
{
cout<<0<<endl;
return 0;
}
}
//for(int i=1;i<=n;i++)
//cout<<sizei[i]<<' '<<ans[i]<<endl;
if(cnt==0)
cout<<0;
else
cout<<binpow(2,cnt,998244353);
}
```


---

