# [ABC126D] Even Relation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc126/tasks/abc126_d

$ N $ 頂点の木があります。 この木の $ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結んでおり、その長さは $ w_i $ です。 あなたは以下の条件を満たすように、この木の頂点を白と黒の $ 2 $ 色で塗り分けたいです (すべての頂点を同じ色で塗っても構いません)。

- 同じ色に塗られた任意の $ 2 $ 頂点について、その距離が偶数である。

条件を満たす塗り分け方を $ 1 $ つ見つけて出力してください。この問題の制約下では、そのような塗り分け方が必ず $ 1 $ つは存在することが証明できます。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ N $
- $ 1\ \leq\ w_i\ \leq\ 10^9 $

## 样例 #1

### 输入

```
3
1 2 2
2 3 1```

### 输出

```
0
0
1```

## 样例 #2

### 输入

```
5
2 5 2
2 3 10
1 3 8
3 4 2```

### 输出

```
1
0
1
0
1```

# 题解

## 作者：Zhangikun (赞：4)

### 题目大意
给定一颗无根树，让你给每个点染黑和白色，前提是两点之间的边权如果是奇数，两点的颜色就不能一样。颜色用 $0$ 和 $1$ 表示，输出任意一种方案即可。
## 分析
由于是任意一种方案，也就是说只要成立就可以。其实就可以直接来一个深搜，如果 $cur$ 点和 $nxt$ 点的边权是偶数，那么可以直接照搬 $cur$ 点的颜色，否则就取反 $cur$ 点的颜色。
## 代码实现：
```cpp
#include<bits/stdc++.h>//无能头文件
using namespace std;
const int cxk=1e5+5;
struct ikun//其实可以用pair<int,int>
{
  int go,w;
};
vector<ikun>nbr[cxk];//nbr[x]表示所有与x连的边的点和边权
bool ans[cxk];//存颜色
void dfs(int cur,int fa)//当前点和父节点
{
  if(nbr[cur].size()==0)return;//叶子节点就直接return
  for(int i=0;i<nbr[cur].size();i++)
  {
    int nxt=nbr[cur][i].go,w=nbr[cur][i].w;
    if(nxt==fa)continue;
    if(w%2==0)//偶数
    {         
      ans[nxt]=ans[cur];//照搬
    }         
    else      //只因数
    {
      ans[nxt]=(ans[cur]==0);//取反
    }
    dfs(nxt,cur);//别忘了递归
  }
  return;
}
int main()
{
  int n;
  cin>>n;
  for(int i=1,x,y,z;i<n;i++)
  {
    cin>>x>>y>>z;
    nbr[x].push_back({y,z});
    nbr[y].push_back({x,z});
  }
  ans[1]=0;//初始化（其实可以不要）
  dfs(1,0);//由于是无根树，所以从任一点开始递归即可
  for(int i=1;i<=n;i++)
  {
    cout<<ans[i]<<"\n";//输出
  }
  return 0;//好习惯
}
```


---

## 作者：lrb12345 (赞：2)

 ### 题目大意
有 $n$ 个顶点，再给你 $n-1$ 条边，如果他们之间的权值为偶数则为相同颜色。
### 整体思路
这道题十分的简单，一个图的 dfs 遍历就 ok 了，我们只需判断权值是否为偶数就可以了，开始我们随便找个点当根节点标记为1（白色），然后开始模拟遍历。
### 代码（这里建图采用的是链式前向星）
```
#include<bits/stdc++.h>
using namespace std;
long long n,ans,tot=1,head[999999],o[999999];
struct t//构建链式前向星
{
	long long xy,nx,qz;
};
t a[999999];
void js(long long u,long long v,long long w)//存图
{
	a[tot].xy=v;
	a[tot].qz=w;
	a[tot].nx=head[u];
	head[u]=tot++;
};
void dfs(long long g)//搜索
{
	for(int i=head[g];i;i=a[i].nx)//遍历临接点
	{
		if(o[a[i].xy]==0)//如果当前没有颜色，则进入染色
		{
		if(a[i].qz%2==0)//颜色相同
		{
			o[a[i].xy]=o[g];
		}
		else
		{
			if(o[g]==1)//如果不同且点为白则染成黑
			{
				o[a[i].xy]=2;
			}
			else
			o[a[i].xy]=1;//反之染白
		}
		dfs(a[i].xy);//继续向下遍历
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		long long u,v,w;
		cin>>u>>v>>w;
		js(u,v,w);
		js(v,u,w);//由于式前向星是建单向边所以要两个边都存
	}
	o[1]=1;//标记为白色（2为黑色，这样个人认为更方便）
	dfs(1);
	for(int i=1;i<=n;i++)
	{
		cout<<o[i]-1<<endl;//因为前面数字代表的颜色大了1所以减去
	 } 
}
```
本蒟蒻第一发题题解，如有不足括更优解请指出。

---

## 作者：fengenrong (赞：2)

### 题意
你需要算出每一个点的颜色，满足一条边如果是 $2$ 的倍数就要连接它的两个顶点的颜色相同。
### 思路
考虑图论，先将编号为 $1$ 的点设置为 $1$，然后开始遍历它的邻接点。要是边是 $2$ 的倍数，就将它的值设为与编号为 $1$ 的点相同，否则取反。接着，在将它继续遍历，直到遍历完为止。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct op{
	int from,to,sum;//链式前项星存图
}a[200005];
int cnt=1;
int head[200005];
void hb(int x,int y,int sum)//合并
{
	a[cnt].from=head[x];
	a[cnt].to=y;
	a[cnt].sum=sum;
	head[x]=cnt++;
}
int ans[200005];
bool bj[200005];
void dfs(int x)//搜索
{
	for(int i=head[x];i!=0;i=a[i].from)//遍历邻接点
	{
		int y=a[i].to;//求出邻接点
		if(bj[y]==1)//如果遍历过
		{
			continue;
		}
		if(a[i].sum%2==0)//是二的倍数
		{
			bj[y]=1;//标记
			ans[y]=ans[x];//设为相同
			dfs(y);//继续搜索
		}
		else
		{
			bj[y]=1;//标记
			if(ans[x]==1)//设为相反
			{
				ans[y]=0;
			}
			else
			{
				ans[y]=1;
			}
			dfs(y);//继续搜索
		}
	}
}
signed main()
{
	cin>>n;
	int x,y,z;
	for(int i=1;i<n;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&z);
		hb(x,y,z);//合并x到y
		hb(y,x,z);//合并y到x
	}
	ans[1]=1;//将颜色设为1
	bj[1]=1;//标记已经遍历过
	dfs(1);//搜索
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",ans[i]);//输出答案
	}
	return 0;
}
```

---

## 作者：Rannio (赞：1)

### 题意

对一棵有 $N$ 个点，$N-1$ 条边的树进行黑白染色，使得每两个距离为偶数的点颜色都一致。

### 思路

首先让我们回顾一下加法的性质：
- 偶 $+$ 偶 $=$ 偶
- 奇 $+$ 奇 $=$ 偶
- 偶 $+$ 奇 $=$ 奇

不难看出，距离为偶数的关系是可以传递的，而距离为奇数的关系不行。

我们只需要做一遍 `dfs`，对一个点 $x$ 的邻接点中距离 $x$ 为偶数的点染成与 $x$ 相同的颜色，否则染成另外一种颜色，便可通过此题。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,s,d[100005],f;
ll ans;
ll head[200005],cnt=1;
ll color[100005];
bool flag[100005];
struct node{
    ll to,next,val;
}edge[200005];
void add(ll x,ll y,ll z){
    edge[cnt].to=y;
    edge[cnt].val=z;
    edge[cnt].next=head[x];
    head[x]=cnt++;
}
void dfs(ll x){
    flag[x]=1;
    for(int i=head[x];i;i=edge[i].next){
        ll u=edge[i].to;
        if(flag[u]){
            continue;
        }
        if(edge[i].val%2==0){
            color[u]=color[x];
            dfs(u);
        }
        else{
            color[u]=!color[x];
            dfs(u);
        }
    }
}
int main(){
    scanf("%lld",&a);
    for(int i=1;i<=a-1;i++){
        ll x,y,z;
        scanf("%lld%lld%lld",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    dfs(1);
    for(int i=1;i<=a;i++){
        printf("%lld\n",color[i]);
    }
    return 0;
}
```


---

## 作者：flangeborg (赞：1)

~~一道超水的模拟题~~

## 题目大意
给定一个有 $n$ 个节点、$n-1$ 条边的无根树，现在对这棵树进行染色（$2$ 种颜色），对于任意两个点 $(i,j)$，若两点间的距离 $dis$ 为偶数，两点染成相同颜色，若不为偶数，则相反，要求我们给出任意一个合法解。

### 解题思路
- 首先我们能想到，并且题目中也提到了对于这样一棵树进行染色一定会有至少一个合法的解。~~如果证明出是错的可以去想一想你构造的数据是不是棵树。~~

- 因为这是一棵树，所以我们可以使用深度或者广度优先遍历，对于这一道题我用的是深度优先遍历。对于当前遍历到的节点 $p$，枚举其的所有出边，如果连接到的点 $q$ 并没有被遍历过（使用 $check$ 数组记录），判断出边长度 $dis$ 是否为偶数，染色形式依据大意来进行。

### AC代码
```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>
//一些常用的头文件 
using namespace std;
struct node{int to,val;};//结构体存储边的信息 
vector<node>edge[100005];//使用邻接表存图 
bool check[100005];//记录该点是否被遍历过 
int n,col[100005];//col：每个点的颜色 
void dfs(int now,int co)//now：当前遍历到的点的编号 ，co：当前点的颜色 
{
	col[now] = co;//染色 
	for(int i = 0; i < edge[now].size(); i++)
	{
		int  _to = edge[now][i].to,dis = edge[now][i].val;
		if(!check[_to])//判断出边指向的点是否被遍历过 
		{
			check[_to] = true;//记录 
			if(dis % 2 == 1)
			{
				if(co) dfs(_to,0);
				else dfs(_to,1);
			}
			else dfs(_to,co);//判断边权是否为偶数 ，并染色 
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1; i < n; i++)
	{
		int s1,s2,s3;
		scanf("%d%d%d",&s1,&s2,&s3);
		edge[s1].push_back({s2,s3});
		edge[s2].push_back({s1,s3});
	}//输入，建图 
	check[1] = true;
	dfs(1,0);//深度优先遍历 
	for(int i = 1; i <= n; i++) printf("%d\n",col[i]);//输出答案 
	return 0;
}
```

解题的思路和代码方法就都在这里了，希望能对大家有所帮助。

---

## 作者：JWRuixi (赞：1)

~~大佬们应该是一眼秒吧？~~
- 题意：

给你一棵 $n$ 个节点的带边权树，对其进行黑白染色，使得任意两个相同颜色节点的距离为偶数。

- 分析：

其实是一个纸老虎。

首先，因为这关心奇偶，所以边权设为 $0$ 或 $1$。

然后注意把所有节点的颜色反转没有影响，所以不妨设 $1$ 节点为白色。

直接从上及下搜索，判断中间的边权是偶还是奇，是奇数这变换颜色，否则直接继承。

时间复杂度线性。

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		for (; !isdigit(c); c = getchar()) {
			if (c == '-') f = -1;
		}
		for (; isdigit(c); c = getchar()) {
			x = (x << 1) + (x << 3) + c - '0';
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

const int maxn = 1e5 + 5;

struct edge {
	int v, nxt, w;
}e[maxn << 1];

int n, head[maxn], tot, ans[maxn];

void add (int u, int v, int w) {
	e[++tot] = {v, head[u], w};
	head[u] = tot;
}

void dfs (int u, int fa) {
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (v == fa) continue;
		if (e[i].w) ans[v] = !ans[u];//奇数
		else ans[v] = ans[u];//偶数
		dfs(v, u);
	}
}

int main () {
	n = read();
	for (int u, v, w, i = 1; i < n; i++) {
		u = read(), v = read(), w = read() & 1;//边权设为0/1
		add(u, v, w);
		add(v, u, w);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) write(ans[i]), puts("");
} 
```


---

## 作者：PineappleSummer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc126_d)

AtCoder Problems 评分：$\color{Cyan}1279$

由于题目保证有解，不妨钦定 $1$ 号节点为根，标记为白色，然后从 $1$ 号节点出发 DFS 便利每个节点，如果该节点与 $1$ 号节点的距离为偶数，将该节点标记为白色，否则标记为黑色。

这个做法实现非常简单，那么我来说明一下这样写的正确性。首先看一个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/noxfrdn2.png)

假定：
- $1$ 号节点到 $4$ 号节点的路径长度为偶数
- $1$ 号节点到 $5$ 号节点的路径长度为偶数

则无非就是一下两种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/80ofncdg.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/5rflpjkd.png)

可以很直观地看出来，这两种情况中 $4$ 号节点与 $5$ 号节点的距离均为偶数。

其它情况也很好证明。

核心代码：
```cpp
void dfs(int k,int fa)
{
	vis[k]=dis[k]&1;//深度为奇数标记为1，为偶数标记为1
	for(auto i:G[k])
	{
		LL y=i.y,v=i.v;
		if(y==fa) continue;
		dis[y]=dis[k]+v;//计算深度
		dfs(y,k);
	}
}
```

[完整代码](https://atcoder.jp/contests/abc126/submissions/51170651)，时间复杂度 $O(n)$。

---

## 作者：ys_kylin__ (赞：0)

## 题目大意
有一颗带权值的无根无向树，要进行染色（黑白）使任何两个同色节点距离（计算权值）为偶数。
## 思路
考虑到数据范围小，直接模拟遍历一遍。当一个节点离你为偶数时染同色，否则染异色。这样子，就算两个同色点离得很远也能保证距离是偶数。

注意几点：
+ 用链式前向星或者邻接表存图，要存下所有数据可以用结构体。
+ 用任意一种方法即可通过，只要符合要求。

然后就可以快乐的 AC 了！
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node {
	int v,w;
};
vector<node> ve[100005];//邻接表
int vis[100005],ans[100005];//ans记录颜色（答案）
void dfs(int u,int col) {//col代表当前颜色,0白1黑
	vis[u]=1,ans[u]=col;
	for(int i=0;i<ve[u].size();i++) {
		node v=ve[u][i];//v代表目标节点
		if(vis[v.v]) continue;
		vis[v.v]=1;
		if(v.w%2==1) dfs(v.v,col^1);//异或可以快速01转换
		else dfs(v.v,col);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		ve[u].push_back({v,w});//读入数据
		ve[v].push_back({u,w});
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：FreedomKing (赞：0)

简单搜索题。

### 思路

直接模拟题意肯定是不可行的，考虑简化一下要求构造出的树的限制。对于任意相同色块间距离为偶数，我们直接保证任意最近的两个距离为偶即可，读者自证不难。这样只要把同一奇长度的边相连的节点染成不同颜色即可。

代码实现主要就是搜索，因为只要是任意满足题目要求的构造就行，直接随便找个节点赋个颜色开始搜，如果跨过的边的长度是奇数就变颜色，否则不变。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=1e4+5,mod=1e9+7;
int a[N],b[N],dp[mN][mN],n,m,k,ans;
map<pair<int,int>,bool>mp;
priority_queue<int,vector<int>,greater<int>>pq;
vector<pair<int,int>>e[N];
inline int qread(){
#define qr qread()
	int x=0,c=getchar(),t=1;
	while(c<'0'||c>'9'){
		t^=(c=='-');
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return (t?x:-x);
}
inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
	if(x<0) x=-x,putchar('-');
	if(x>9) qwrite(x/10);
	putchar(x%10+'0');
	return;
}
inline int qpow(int x,int p,int mod){
	x=(p?x:1);
	mod=(mod?mod:LONG_LONG_MAX);
	int t=1;
	while(p>1){
		if(p&1) t=(t*x)%mod;
		x=(x*x)%mod;
		p>>=1;
	}
	return (x*t)%mod;
}
bool vis[N];
inline void dfs(int x){
	if(vis[x]) return;
	vis[x]=true;
	for(int i=0;i<e[x].size();i++){
		int v=e[x][i].first,w=e[x][i].second;
		if(w&1) a[v]=!a[x];
		else a[v]=a[x];
		dfs(v);
	}
}
signed main(){
	n=qr;
	for(int i=1;i<n;i++){
		int u=qr,v=qr,w=qr;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	a[1]=1;
	dfs(1);
	for(int i=1;i<=n;i++) qwe(a[i]);
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

【树上奇偶性问题】要求给一棵树上的节点染色（$0/1$），要求如果有两个节点颜色相同，则其间距离为偶数。

### 思路：

树上两个节点 $u,v$ 距离的定义是：

$$dep_u+dep_v-2 \times dep_{lca(u,v)}$$

因此要使距离为偶数，当且仅当 $dep_u+dep_v$ 为偶数。

而这当且仅当 $dep_u$ 与 $dep_v$ 奇偶性相同。

因此我们只需要计算每个点到根节点的距离是奇数还是偶数。

所有奇数的染成一种颜色，所有偶数的染成另一种颜色即可。

事实上，我们还有一种更简单的实现方法，一个点到根节点的距离奇偶性取决于父亲的奇偶性以及它与父亲之间的距离。

因此如果一个点和它父亲距离为偶数，则与父亲同色，否则与父亲异色。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    int n;
	cin>>n;
	vector<vector<pair<int,int>>> g(n);
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		--u,--v;
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	}
    vector<ll>d(n);
	vector<bool>vis(n);
	function<void(int,ll)>dfs=[&](int u,ll val){
        d[u]=val;
		for(auto[v,w]:g[u]){
			if(!vis[v]){
				vis[v]=true;
				dfs(v,val+w);
			}
		}
    };
    dfs(0,0);
    vector<int>ans(n);
    for(int i=0;i<n;i++)
	  if(d[i]&1)
      ans[i]=1;
    for(auto&x:ans)
	  cout<<x<<endl;
	return 0;
}
```


---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT4753)

**思路:**

这是一颗带边权的树。

我们可以把 $1$ 看成树的根，颜色是 $0$。

**对于任意两个相同颜色的节点，它们之间的距离是偶数。**

所以：

如果边权是偶数，则它的颜色和父亲节点一样。

否则，它的颜色和父亲节点相反。

这时，只要从 $1$ 号点出发，遍历一下整棵树就好了。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int en,l;
};
int n,a,b,c;
vector<node>v[100010];
bool k[100010];
void dfs(int now,int fa){
	for(int i=0;i<v[now].size();i++){
		node t=v[now][i];
		if(t.en==fa) continue;
		if(t.l) k[t.en]=!k[now];
		else k[t.en]=k[now];
		dfs(t.en,now);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>a>>b>>c;
		v[a].push_back((node){b,c%2});
		v[b].push_back((node){a,c%2});
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	if(k[i]) puts("1");
	else puts("0");
	return 0;
}
```

---

## 作者：GoldenFishX (赞：0)

### 题目大意

对点进行黑白染色，使得任意两个同色的点之间的距离都是偶数。

### 具体思路

- 用邻接表存图，再用dfs遍历一遍。（如果连接下一个点的距离为偶数，就把下一个点染成这个点的颜色，否则染成这个点的相反色）

- 由于输出任何一个解都能过，所以只要从一个点开始搜索

- 时间复杂度 O(n)

### 代码部分

#### 1. 存图
```cpp
struct Node {		//边
  int w, u;		//边的权值与指向的点的下标下标
};
struct Node1 {
  int x;		//下标
  bool color = 0; 	//点的颜色
  vector<Node> u;	//与点x连接的点
} g[MAXN];
```
#### 2. 建图
```cpp
for (int i = 1; i <= n - 1; i++) {  //下标从1开始,n-1条边
    int u, v, w;
    cin >> u >> v >> w;
    Node x;			        //先定义好，方便存
    x.u = v;			    //指向的点v
    x.w = w;			    //权值w
    g[u].u.push_back(x);
    x.u = u;			    //由于之前已经给权值赋过值了，所以只需要改指向的点
    g[v].u.push_back(x);
}
```
#### 3.染色
```cpp
void dfs(int x) {
  vis[x] = 1;       //标记已经染色过
  for (int i = 0; i < g[x].u.size(); i++) {
    if (!vis[g[x].u[i].u]) {                //这个点没有染色
      if (g[x].u[i].w % 2 == 0) {           //偶数的情况
        g[g[x].u[i].u].color = g[x].color;  //颜色相同
        dfs(g[x].u[i].u);
      } else {                              //奇数的情况
        g[g[x].u[i].u].color = !g[x].color; //颜色相反
        dfs(g[x].u[i].u);
      }
    }
  }
}
```
#### 完整代码
```cpp
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 5;
struct Node {		//边
  int w, u;		//边的权值与指向的点的下标下标
};
struct Node1 {
  int x;		//下标
  bool color = 0; 	//点的颜色
  vector<Node> u;	//与点x连接的点
} g[MAXN];
bool vis[MAXN];
void dfs(int x) {
  vis[x] = 1;       //标记已经染色过
  for (int i = 0; i < g[x].u.size(); i++) {
    if (!vis[g[x].u[i].u]) {                //这个点没有染色
      if (g[x].u[i].w % 2 == 0) {           //偶数的情况
        g[g[x].u[i].u].color = g[x].color;  //颜色相同
        dfs(g[x].u[i].u);
      } else {                              //奇数的情况
        g[g[x].u[i].u].color = !g[x].color; //颜色相反
        dfs(g[x].u[i].u);
      }
    }
  }
}
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n - 1; i++) {  //下标从1开始,n-1条边
    int u, v, w;
    cin >> u >> v >> w;
    Node x;			        //先定义好，方便存
    x.u = v;			    //指向的点v
    x.w = w;			    //权值w
    g[u].u.push_back(x);
    x.u = u;			    //由于之前已经给权值赋过值了，所以只需要改指向的点
    g[v].u.push_back(x);
}
  dfs(1); //因为只需要输出一种答案，所以可以随便从一个点开始搜索
  for (int i = 1; i <= n; i++) {
    cout << g[i].color << endl;
  }
  return 0;
}
```
（考试时没看清题，其实是棵树....）


---

## 作者：YueYang1235 (赞：0)

题目大意：

有一个拥有 $ N $ 个顶点的树。该树的第 $ i $ 条边上的两个节点是 $ u_i $ 和 $ v_i $ ,长度为 $ w_i $ 。你需要在满足以下的条件下，将树上的所有节点涂上黑色和白色。（可以将所有的顶点都涂上同样的颜色），所有涂有相同颜色的节点，它们之间的距离必须是偶数。



------------

这是一道树形结构题，我们不妨先不考虑奇偶性，先考虑一下怎样算任意两点 $ A $ 和 $ B $ 它们之间的距离。

下面是一棵树的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/fm8d7wc8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

点 $ A $ 和点 $ B $ 的距离很明显 $ 2+5=7 $

但是，我们还有一个算法：设点 $ E $ 为根，那么 $ A $ 和点 $ B $ 的距离为 $ dis(E,A) + dis(E,B) - dis(E,C)  \times 2 $ ，这让我们求奇偶性非常有用，因为 $ dis(E,C) \times 2 $ 是偶数，他不影响前面 $ dis(E,A) +  dis(E,B) $ 的奇偶性

由于奇数 $ + $ 奇数 $ = $ 偶数，偶数 $ + $ 偶数 $ = $ 偶数，所以我们遇到边长为奇数时，答案（0或1）就取反。（其实这样做连距离都不用求了）

另：样例 $ 2 $ 错了，应该是全 $ 0 $

$ code $:

```
#include<bits/stdc++.h>
using namespace std;
int n;
struct edge{
	int v,w,next;
}e[405000];
int head[405000],cnt;
int ans[405000];
void add(int u,int v,int w){
	++cnt;
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa,int sum){
	ans[u]=sum;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa)continue;
		if(e[i].w%2)dfs(v,u,sum^1);
		else dfs(v,u,sum);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;++i){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	dfs(1,-1,0);
	for(int i=1;i<=n;++i)cout<<ans[i]<<endl; 
}
```


---

