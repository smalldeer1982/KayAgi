# GCD Counting

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Let's denote the function $ g(x, y) $ as the greatest common divisor of the numbers written on the vertices belonging to the simple path from vertex $ x $ to vertex $ y $ (including these two vertices). Also let's denote $ dist(x, y) $ as the number of vertices on the simple path between vertices $ x $ and $ y $ , including the endpoints. $ dist(x, x) = 1 $ for every vertex $ x $ .

Your task is calculate the maximum value of $ dist(x, y) $ among such pairs of vertices that $ g(x, y) > 1 $ .

## 样例 #1

### 输入

```
3
2 3 4
1 2
2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 3 4
1 3
2 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 1 1
1 2
2 3
```

### 输出

```
0
```

# 题解

## 作者：Realityang (赞：17)

## [题目传送门](https://www.luogu.com.cn/problem/CF1101D)

## [一种更好的题解食用方式](https://www.cnblogs.com/yang-RA-NOI/p/12594636.html)

# 题目大意：

$给出一棵n个节点的树，每个节点上有点权a_i$

$求最长的树上路径，满足条件：$

$路径上经过节点（包括两个端点）点权的gcd和不等于1$

###数据范围

$\circ$ $n\le2\times10^5$

$\circ$ $1\le a_i\le2\times10^5$

#题解

首先当然会想到

若要几个的gcd不等于0

我们可以用他们的其中一个非1的因数DP

向下DP显然不妙，于是决定DFS树，回溯时去DP

那么对于一个点，遍历他的儿子

对于每一个子节点回溯时找他们两个的所有相同质因子

进行DP，同时更新答案

最后输出答案即可

对于找共同质因子，只要预先处理：

    
   先找到质数家族，
   再一个一个$a_i$分解质因数，把它们放在数组里储存。
    
怕数组空间炸？不用担心，一个数最多也就$7,8$个不同的质因子

$2\times3\times5\times7\times11\times13\times17\times23>2\times10^5$

所以就问题不大了！详见下方代码↓↓↓

#AC代码：

```
#include<bits/stdc++.h>
using namespace std;
int tot=0,n,cnt,head[200010];
int maxx=200010,a[200010],vis[300010],f[200010][10],y[200010][10],ans,p[200010];
//p是质数家族 ，y[i][j]是指a[i]的第j大的质因子 
struct abc{
	int to,nxt;
}e[800010];
void add(int u,int v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void make_zhi(){//求质数的欧拉筛，不懂自行百度（相信各位大佬定会的） 
	for(int i=2;i<=maxx;i++){
		if(!vis[i])p[++tot]=i;
		for(int j=1;j<=tot&&p[j]*i<=maxx;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	//cout<<p[10]<<endl;
}
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(fa==v)continue;
		dfs(v,u);
		for(int j=1;j<=y[u][0];j++){
			for(int k=1;k<=y[v][0];k++){
				if(y[u][j]==y[v][k]){
					ans=max(ans,f[u][j]+f[v][k]+1);
					f[u][j]=max(f[u][j],f[v][k]+1);
				}
			}
		}
	}
}
int main(){
	make_zhi();
	int ff=1;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=1)ff=0;
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	if(ff){//特判全1时 
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;p[j]*p[j]<=a[i];j++){
			if(a[i]==1)break;
			if(a[i]%p[j]==0){
				y[i][++y[i][0]]=p[j];//太懒于是用y[i][0]存质数个数 
				while(a[i]%p[j]==0)a[i]/=p[j];//统统除掉 
			}
		}
		if(a[i]!=1)y[i][++y[i][0]]=a[i];//剩下了他自己怎么办？靠他了 
	}
	dfs(1,0);
	cout<<ans+1;
} 
//加一什么的多调几次就会发现的了 
```

### 支持一下吧，关注，点赞，评论都好

# THE END


---

## 作者：夜猫子驱蚊器 (赞：8)

虽然说这题有简单的方法，可是这其实是个点分治裸题欸

假设当前的分治到的重心为$x$，很显然，经过$x$的那些合法的链，肯定链中每个数都含有起码一个相同的$a[x]$的质因子，因为$gcd|a[x]$嘛。把$a[x]$分解质因数，然后对每个质因子$p$，都做一次dfs，求出离$x$最远的两个点$u,v$，这两个点到x的路径上的数当然都要被$p$整除，然后$ans=max(ans,dis(u)+dis(v))$，$dis(u)$表示$u$到$x$的距离。要注意$u,v$不能在一个子树内。

然后每次找重心，不停把树分割就行了。

点分治码量比较大，但是熟练之后打起来其实还是挺快的。。~~大多都是板子，比赛的时候复制粘贴23333~~

我是蒟蒻，有啥问题跟我说哈（QQ私信Email之类随便啥都行）  
然后宣传一波[博客](https://blog.csdn.net/ymzqwq/article/details/88697367)

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define ll long long
#define fr(i,x,y) for(int i=(x);i<=(y);i++)
#define rf(i,x,y) for(int i=(x);i>=(y);i--)
#define frl(i,x,y) for(int i=(x);i<(y);i++)
using namespace std;
const int N=200002;
const int M=N<<1;
int n,a[N];
int cnt,head[N],Next[M],v[M];
int b[N];
int rt,mx,mxx;
int sz[N],mmx[N],s[M];
int ans=-1;
vector<int> p[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
}

void add(int x,int y){
	Next[++cnt]=head[x];
	head[x]=cnt;
	v[cnt]=y;
}

int findrt(int x,int fa,int n){ //找重心
    sz[x]=1;mmx[x]=0;
    int ans=0,tt;
    for(int i=head[x];i;i=Next[i])
     if (v[i]!=fa&&!b[v[i]]){
        tt=findrt(v[i],x,n);
        if (mmx[tt]<mmx[ans]) ans=tt;
        sz[x]+=sz[v[i]];
        mmx[x]=max(mmx[x],sz[v[i]]);
     }
    mmx[x]=max(mmx[x],n-sz[x]);
    if (mmx[x]<mmx[ans]) ans=x;
    return ans;
}

int getdis(int x,int fa,int vv){
	int mx=0;
	for(int i=head[x];i;i=Next[i])
	 if (v[i]!=fa&&!b[v[i]]&&a[v[i]]%vv==0)
	  mx=max(mx,getdis(v[i],x,vv));
	return mx+1;
}

int cal(int x,int vv){ //找最远的两个点
	ans=max(ans,0);
	int mx=-1,mxx=-1;
	for(int i=head[x];i;i=Next[i])
	 if (!b[v[i]]&&a[v[i]]%vv==0){
	 	int xx=getdis(v[i],x,vv);
	 	if (xx>mx) mx=xx;
	 	if (mx>mxx) swap(mx,mxx);
	 }
	return max(mx+mxx,mxx);
}

void dfs(int x,int n){ //分割树
	b[x]=1;int tmp=a[x];
	frl(i,0,p[tmp].size())
	 ans=max(ans,cal(x,p[tmp][i])); //对每个质因子都找最远的
	for(int i=head[x];i;i=Next[i])
	 if (!b[v[i]]){
	 	int rt=findrt(v[i],0,sz[v[i]]);
	 	assert(rt>0);
	 	dfs(rt,s[i]);
	 }
}

void init(){ //分解质因数
	frl(i,2,N)
	 if (!b[i]){
	 	p[i].push_back(i);
	 	for(int j=2*i;j<N;j+=i)
	 	 p[j].push_back(i),b[j]=1;
	 }
	memset(b,0,sizeof b);
}

int main(){
	init();
	read(n);
	fr(i,1,n) read(a[i]);
	int x,y;
	fr(i,2,n){
		read(x);read(y);
		add(x,y);add(y,x);
	}
	//int rt=findrt(1,0,n);
	mmx[0]=2e9;
	dfs(findrt(1,0,n),n);
	cout<<ans+1<<endl;
	return 0;
}
```

---

## 作者：Strelitzia (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1101D)

---

直接暴力搜索可能会 $\operatorname T$，看题目，很容易想到树形 $\text{dp}$，怎么 $\operatorname d$ 呢？


我们可以发现，其实一个数的质因数不是很多，所以我们可以先分解质因数。

有没有相同的质因数，有的话，就说明这两个数的 $\gcd$ 不为1。

定义 $dp_{u,x}$ 表示以 $\operatorname u$ 为断点最长的一条链，质因数是x。

注意答案统计，要算两条链合起来的路径。

```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 200005;

int nxt[maxn << 1],ver[maxn << 1],head[maxn],tot;
void addEdge(int x,int y) {
    nxt[++ tot] = head[x];ver[tot] = y;head[x] = tot;
}

int n,col[maxn],a[maxn],sz[maxn],ans;
vector<int> dp[maxn];
vector<int> prime[maxn];

void dfs(int u,int fa) {
	for (int e = head[u] ; e ; e = nxt[e]) {
		int v = ver[e];
		if (v == fa) continue;
		dfs(v,u);
		for (int i = 0 ; i < prime[u].size() ; ++ i) {
			for (int j = 0 ; j < prime[v].size() ; ++ j) {
				if (prime[u][i] == prime[v][j]) {
					ans = max(ans,dp[v][j] + dp[u][i]);
					dp[u][i] = max(dp[u][i],dp[v][j] + 1);
				}
			}
		}
	}
}

int main () {
	read(n);
	for (int i = 1 ; i <= n ; ++ i) {
		read(a[i]);
		if (a[i] ^ 1) ans = 1;
		for (int j = 2 ; j * j <= a[i] ; ++ j) {
			if (a[i] % j == 0) {
				prime[i].push_back(j);
				dp[i].push_back(1);
				while (a[i] % j == 0) a[i] /= j;
			}
		}
		if (a[i] ^ 1) prime[i].push_back(a[i]),dp[i].push_back(1);
	}
	int x,y;
	for (int i = 1 ; i < n ; ++ i) {
		read(x);read(y);
		addEdge(x,y);
		addEdge(y,x);
	}
	dfs(1,0);
	print(ans);
    return 0;
}
```

---

## 作者：lxzy_ (赞：3)

考点：树形Dp、质因数分解

__处理链 $(u,v)$ 的问题一般是拆成 $(u,lca_{u,v})$ 和 $(v,lca_{u,v})$ 解决__ ，因此每一个点只需要考虑其子节点的情况，可以使用树形DP解决。

由于最大公约数只与点权的所有质因子有关，且点权最大只有 $2\times 10^5$ ，拆成质因子之后其个数仅有不到 $10$ 个，同时其对答案有影响~~废话~~ ，可以考虑将每个数质因数分解，并将分解后的质因子作为DP的一维。

设 $f_{u,i}$ 表示点 $u$ 第 $i$ 个质因子作为 __以$u$为起点的__ 链上所有点权的公约数时链的最大长度（注意这里不是最大公约数），很容易就可以推出方程：

$$f_{u,i}=\max\limits_{v\in son_u,fac_{u,i}=fac_{v,j}}(f_{v,j})+1$$

这里的 $fac_{i,j}$ 表示点 $i$ 的第 $j$ 个质因子。

然后，回到一开始时的拆链操作，现在合并，将同一个点的 $f$ 合并在一起。定义 $g_{u,i}$ 表示以 $u$ 为顶点、所有点权的因数为 $i$ 的最长链，也就是答案，有：

$$g_{u,i}=\max\limits_{v,w\in son_u,fac_{v,j}=fac_{w,k}=fac_{u,i}}(f_v,j+f_w,k)$$

看着很复杂，但实际上和第一个式子有很多相似之处，可以同时转移。具体可以见代码。

```cpp
//燊，我的燊~
#include<cstdio>
#include<iomanip>

using namespace std;
const int N=2e5+50,M=34;
struct edge{
	int to,nxt;
}a[N<<1];
int head[N],f[N][M],g[N][M],cnt,n,ans;
int Fac[N][M],Cnt[N],w[N];
inline int Max(int a,int b){return a>b?a:b;}
void Div(int x,int pos)//质因数分解 
{
	for(int i=2;i*i<=x;i++){
		if(x%i==0) Fac[pos][++Cnt[pos]]=i;
		while(x%i==0) x/=i;
	}
	if(x>1) Fac[pos][++Cnt[pos]]=x;
}
void add(int u,int v)
{
	cnt++;
	a[cnt].to=v;
	a[cnt].nxt=head[u];
	head[u]=cnt;
}
void DFS(int u,int fa)
{
	for(int k=head[u];k;k=a[k].nxt){
		int v=a[k].to;
		if(v!=fa){
			DFS(v,u);
			for(int i=1;i<=Cnt[u];i++){
				for(int j=1;j<=Cnt[v];j++){
					if(Fac[u][i]==Fac[v][j]){
						g[u][i]=Max(g[u][i],f[u][i]+f[v][j]);
						//这个地方，是在转移当前的 $f_{u,i}$ 之前。
						//此时 $f_{u,i}$ 已经代表了此前访问过的所有 u 的儿子中符合要求且最长的链
						//只需要与当前所转移的 f[v][j]求和即可  
						
						//如果不懂的话，可以类比一下求一个序列中最大值和次大值的和 
						f[u][i]=Max(f[u][i],f[v][j]+1);
					}
				}
			}
		}
	}
	
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
		Div(w[i],i);
	}
	int u,v;
	for(int i=1;i<=n-1;i++){
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=Cnt[i];j++) f[i][j]=g[i][j]=1;
	}//一开始每一个点都是一条链 
	DFS(1,0);
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=Cnt[i];j++) ans=Max(ans,g[i][j]);
		//这里注意每一个点都可以作为链的顶点 
	}
	printf("%d\n",ans);
	return 0;
}
```

讲完力Orz

---

## 作者：A_Pikachu (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1101D)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf1101d-gcd-counting)）

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

题目要求树上有限制的最长链，考虑分析这个限制。

既然点权的范围在 $2 \times 10^5$ 以内，那么其至多会拥有 $6$ 个不同质因数 $(2 \times 3 \times 5 \times 7 \times 11 \times 13 \times 17 = 510510 > 2 \times 10^5)$，那么不难想到对于每个拥有相同质因子的点求一次直径。由于每个点至多出现 $6$ 次，再考虑到利用去重储存待遍历的质因子使用了 $\text{map}$ 或者 $\text{set}$，就可以得到一种 $\Theta(n\log n)$ 的~~优秀~~做法。

更进一步地，我们发现每次求直径的流程是雷同的，所以为了~~减少码量~~优化复杂度，可以将正常的求直径的过程（当前节点最长链+遍历到的子节点最长链）转化为有限制的转移，条件即为两点有相同质因子。又因为每个质因子之间是独立的，所以要用 $6$ 倍的数组来记录不同质因子的情况。 

$\Large\mathscr{Part\,\,2\;\;}\text{Code}$

```cpp
#include <cstdio>
#include <vector>
using namespace std;
const int N=2e5+5,V=2e5+5,M=10;
int n,u,v,tot,ans,isnp[V],prm[V],nxt[V],val[N][M],f[N][M]; // f[x][j] 表示质因子为 val[x][j] 时以 x 为根最大的深度
// nxt[x] 表示 x 的最小质因子，val[x][0] 表示 x 的质因子个数，val[x] 储存 x 的质因子
vector<int> vec[N];
void pre(){
	isnp[1]=1;
	for(int i=2; i<V; i++){
		if(!isnp[i]) prm[++tot]=i,nxt[i]=i;
		for(int j=1; j<=tot&&1LL*prm[j]*i<V; j++){
			isnp[i*prm[j]]=1;
			nxt[i*prm[j]]=prm[j];
			if(!(i%prm[j])) break;
		}
	}
}
void dfs(int x,int fa){
	for(int j=1; j<=val[x][0]; j++) f[x][j]=1;
	for(int i=0; i<vec[x].size(); i++){
		int y=vec[x][i];
		if(y==fa) continue;
		dfs(y,x);
		for(int j=1,k=1; j<=val[x][0]; j++){
			while(val[y][k]<val[x][j]&&k<val[y][0]) ++k;
			if(val[y][k]==val[x][j]){
				ans=max(ans,f[x][j]+f[y][k]);
				f[x][j]=max(f[x][j],f[y][k]+1);
			}
		}
	}
}
int main(){
	pre();
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&u);
		if(u!=1) ans=1;
		while(u!=1){
			while(nxt[u]==nxt[u/nxt[u]]) u/=nxt[u];
			val[i][++val[i][0]]=nxt[u];
			u/=nxt[u];
		}
	}
	for(int i=1; i<n; i++){
		scanf("%d%d",&u,&v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
```

时间复杂度 $\Theta(n)$。

---

## 作者：YLWang (赞：2)

首先容易发现我们只需要记录每个数有哪些质因子就可以了。我们并不关心他们的次数。

发现不同质因子个数非常少。那有个想法就是在dp的时候记录当前余下的质因子有哪些。

然后你会发现这个转移超级劲爆。复杂度也很高。

考虑优化状态。

一条链上，我们只需要一个共同的质因数就可以使其满足题意。

那么我们只需要记录这个质因数即可。

实现技巧见代码：
https://www.luogu.com.cn/paste/of0x9c7e

---

## 作者：FlyInTheSky (赞：2)

[Blog 链接](http://blog.flyinthesky.win/Codeforces1101D/)

题意：给出一棵无向带点权树，定义$dist(x,y)$为$x,y$之间的点(包含$x,y$)的个数，$g(x,y)$为$x,y$之间所有点权$gcd$，求最大的$dist(x,y)$，并且$g(x,y) \geq 2$

由于$2 \times 10^5$以内的数最多$7$种质数相乘，所以可以对点权分解质因数，指数不重要，只考虑质因子，因为质因子相同的$gcd$一定$\geq 2$。

所以我一开始想对每个质因子建一棵树，然后在树上做类似直径的DP。
这样的树的总大小不会超过$7n$，但是空间就比较爆炸，虽然可以用`map`之类的搞但是麻烦得要死还带了$log$。

其实不需要建那么多棵树，直接一次DFS，找到孩子如果和自己有公质因数，那么像树直径DP那样转移即可，每个点初始化长度更新为1。

注意这里距离为点的个数而不是边的条数，DP 方程要特别注意

赛场上没调出来...就是因为上面那个问题

```c++
//==========================Head files==========================
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<set>
#include<iostream>
#include<map>
#define LL long long
#define db double
#define mp make_pair
#define pr pair<int, int>
#define fir first
#define sec second
#define pb push_back
#define ms(i, j) memset(i, j, sizeof i)
using namespace std;
//==========================Templates==========================
inline int read() {
    int x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9'){if (c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9'){x = x * 10 + c - '0'; c = getchar();}
    return x * f;
}
inline LL readl() {
    LL x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9'){if (c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9'){x = x * 10 + c - '0'; c = getchar();}
    return x * f;
}
int power(int a, int b) {
	int ans = 1;
	while (b) {
		if(b & 1) ans = ans * a;
		b >>= 1; a = a * a;
	}
	return ans;
}
int power_mod(int a, int b, int mod) {
	a %= mod;
	int ans = 1;
	while (b) {
		if(b & 1) ans = (ans * a) % mod;
		b >>= 1, a = (a * a) % mod;
	}
	return ans;
}
LL powerl(LL a, LL b) {
	LL ans = 1ll;
	while (b) {
		if(b & 1ll) ans = ans * a;
		b >>= 1ll;a = a * a;
	}
	return ans;
}
LL power_modl(LL a, LL b, LL mod) {
	a %= mod;
	LL ans = 1ll;
	while (b) {
		if(b & 1ll) ans = (ans * a) % mod;
		b >>= 1ll, a = (a * a) % mod;
	}
	return ans;
}
LL gcdl(LL a, LL b) {return b == 0 ? a : gcdl(b, a % b);}
LL abssl(LL a) {return a > 0 ? a : -a;}
int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b);}
int abss(int a) {return a > 0 ? a : -a;}
//==========================Main body==========================
#define LD "%I64d"
#define D "%d"
#define pt printf
#define sn scanf
#define pty printf("YES\n")
#define ptn printf("NO\n")
//==========================Code here==========================
const LL MAXN = 200000 + 5;

LL n, a[MAXN], ans = 1ll;
vector<LL > st_a[MAXN];
vector<LL > G[MAXN];
vector<pair<LL, LL> > st_dfs[MAXN];

void dfs(LL u, LL fa) {
	for (LL i = 0; i < (LL)st_a[u].size(); ++i) st_dfs[u].push_back(make_pair(st_a[u][i], 1));
	for (LL i = 0; i < (LL)G[u].size(); ++i) {
		LL v = G[u][i];
		if (v != fa) {
			dfs(v, u);
			for (LL j = 0; j < (LL)st_dfs[v].size(); ++j) { // st_dfs[v][j]
				LL whw = st_dfs[v][j].first;
				for (LL k = 0; k < (LL)st_dfs[u].size(); ++k) { // st_dfs[u][k]
					LL gg = st_dfs[u][k].first;
					if (whw == gg) {
						ans = max(ans, st_dfs[u][k].second + st_dfs[v][j].second);
						
						//printf("ans=%d, u=%d, v=%d, whw=%d\n", ans, u, v, whw);
						
						st_dfs[u][k].second = max(st_dfs[u][k].second, st_dfs[v][j].second + 1);
					}
				}
			}
		}
	}
}

int main() {
	cin >> n;
	for (LL i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	int fl = 0;
	for (LL i = 1; i <= n; ++i) if (a[i] != 1) fl = 1;
	if (!fl) return printf("0\n"), 0;
	for (LL u = 1; u <= n; ++u) {
		LL tmp = a[u];
		for (LL i = 2; i * i <= tmp; ++i) if (tmp % i == 0) {
			st_a[u].push_back(i);
			while (tmp % i == 0) tmp /= i;
		}
		if (tmp != 1) st_a[u].push_back(tmp);
		sort(st_a[u].begin(), st_a[u].end());
	}
	
	for (LL x, y, i = 1; i < n; ++i) {
		scanf("%lld%lld", &x, &y);
		G[x].push_back(y), G[y].push_back(x);
	}
	
	dfs(1, 0);
	
	cout << ans;
	
	return 0;
}

```

---

## 作者：我和鱼过不去 (赞：1)

是一道比较有思考性的点分治练习题。

每次都深搜并寻找路径的 $gcd$ ，这样复杂度过高。  
那么可以反向思考，固定一个数为 $gcd$，并寻找相应的最长路径。但是这样直接深搜也不合适。   

这时候考虑点分治：找一个**中继节点**，每次以一个质数为链的 $gcd$ 从该节点往下深搜。这样，拥有同一个 $gcd$ 的两条最长链可以通过这个节点连接起来，就形成了一条更长的链。   

显然应该选择子树的重心作为中继节点，并将重心权值的每个不同的质因子作为链的 $gcd$ 一次进行上述的深搜操作。

### 思路
1. 每次先找到**当前子树**的重心；
2. 分别以**当前子树重心**权值的质因子作为当前链的 $gcd$ ，向下深搜：若当前节点的权值不含该质因子则返回；
3. 记录以**不同质因子**进行深搜的最长的两条链（不含子树的根节点）的长度，则这棵子树中的最长链的长度为这两条链长度之和 +1。

注意的是要先用线性筛法筛出素数表，在进行分治的时候对重心的权值进行质因数分解，再进行深搜。


------------

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=9e5+5;
struct Edge
{
	int v,next;
} edge[maxn<<1];
int n,m,cnt,node,tot,sum,ans,maxd,pNum;
int head[maxn],siz[maxn],mxpt[maxn],w[maxn],prime[maxn];
bool vis[maxn],isPrime[maxn];
inline int gcd(int a,int b)
{
	if(!b) return a;
	return gcd(b,a%b);
}
inline void add(int u,int v)
{
	edge[++cnt] = {v,head[u]};
	head[u] = cnt;
	edge[++cnt] = {u,head[v]};
	head[v] = cnt;
	return;
}
inline void getPrime(int x)   //线性筛 
{
	for(register int i=2;i<=x;i++)
	{
		if(!isPrime[i])
		{
			prime[++pNum] = i;
		}
		for(register int j=1;j<=pNum&&i*prime[j]<=x;j++)
		{
			isPrime[i*prime[j]] = true;
			if(i%prime[j]==0) break;
		}
	}
	return;
}
inline void dfs(int u,int fath)    //寻找子树的重心 
{
	siz[u] = 1;
	mxpt[u] = 0;
	for(register int i=head[u];i!=-1;i=edge[i].next)
	{
		int v = edge[i].v;
		if(v==fath||vis[v]) continue;
		dfs(v,u);
		siz[u] += siz[v];
		mxpt[u] = max(mxpt[u],siz[v]); 
	}
	mxpt[u] = max(mxpt[u],tot-siz[u]);
	if(mxpt[u]<mxpt[node])
	{
		node = u;
	}
	return;
}
inline void query(int u,int fath,int dist,int val)
{	
	if(gcd(w[u],val)!=val) return;       //如果当前点的权值不含该质因子，则直接返回 
	maxd = max(maxd,dist);               //寻找子树中的最长链 
	for(register int i=head[u];i!=-1;i=edge[i].next)
	{
		int v = edge[i].v;
		if(v==fath||vis[v]) continue;
		query(v,u,dist+1,val);
	}
	return;
}
inline void calc(int u,int val)
{
	int dep1=0,dep2=0;
	for(register int i=head[u];i!=-1;i=edge[i].next)
	{
		int v = edge[i].v;
		if(vis[v]) continue;
		maxd = 0;
		query(v,u,1,val);
		if(maxd>dep1) dep2=dep1,dep1=maxd;       //保存两条最长链的长度 
		else if(maxd>dep2) dep2=maxd;
	}
	ans = max(ans,dep1+dep2+1);           //将这两条链通过节点u接起来 
	return;
}
inline void solve(int u)
{
	vis[u] = true;
	int tmp = w[u];
	for(register int i=1;prime[i]*prime[i]<=tmp;i++)    //分解质因数 
	{
		if(tmp%prime[i]==0) calc(u,prime[i]);
		while(tmp%prime[i]==0)
		{
			tmp/=prime[i];
		}
	}
	if(tmp!=1) calc(u,tmp);
	for(register int i=head[u];i!=-1;i=edge[i].next)
	{
		int v = edge[i].v;
		if(vis[v]) continue;
		node = 0;
		tot = siz[v];
		dfs(v,u);              //寻找子树重心 
		solve(node);           //点分治 
	}
	return;
}
int main()
{
	getPrime(2e5);
	memset(head,-1,sizeof(head));
	memset(siz,0x3f3f3f,sizeof(siz)); 
	scanf("%d",&n);
	for(register int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(register int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	mxpt[0] = n;
	tot = n;
	dfs(1,0);
	solve(node);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：MuYC (赞：0)

#### 前置知识：

素数判断（$Miller Rabin$ 素数探测可用可不用吧，因为本题数据没有针对质因数分解） + $DFS$求直径

#### 具体做法

观察题目，发现题目要求我们求 $gcd$ 不等于 $1$ 的一条最长链。

那么如果这条链上所有的节点的 $gcd$ 都不为 $1$，那么它们肯定有着至少一个相同的质因子。

所以我们考虑将拥有相同质因子的节点放在一起处理，然后对于具有相同质因子的节点中求一条最长链就行了。

另外这个题要特判全部都是 $1$ 的情况，这样的话答案就是 $0$。

求最长链的过程用 $DFS$ 实现即可。

于是这个题目的解决流程是这样子的：
```plain

对于所有的给出的节点的权值进行质因数分解。
有着相同质因子的数我们就放入 map 中，定义一个 <int,vector<int> > 类型的 map 即可。

然后遍历所有出现过的质因子（可以用另外一个数组记录，并且用 map 来防止重复入队）

对于有着相同质因子的所有节点各求最长链。

求出最大值即可。
```

这个题目的复杂度看似无法保证。但是我们可以分析一下这道题目的最坏情况下的复杂度。

我们的主要目标就是要使得 $map$ 中记录的节点最多。（因为对于 $map$ 中的节点我们每一个都会访问一次）

那么也就是说，对于同一个数，我们总是希望它被分在不同的组里面，这样子就能使得这个程序被卡(bushi。

但是对于一个 $2e5$ 以内的数，它最多有 $6$ 个**不同** 的质因子，所以整个 $map$ 中的节点最多是 $n * 6$ 个，并且我们可以得出使得这个程序跑满的那一个权值： $180180 = 2^2 * 3^2 * 5 * 7 * 11 * 13$

笔者闲着无聊就写了一个 $Miller-Rabin$ 以应对 $a_i$ 更大的情况.....

于是这个题目的最坏复杂度大概就是 $O(n * 6 * log(n))$，非极限情况复杂度大概是 $O(nlogn)$ ($log$ 是来自 $map$ 的)。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 50;
#define int long long
int n,start[MAXN], data[MAXN];
int Prime[MAXN],tot = 0 ,cnt = 0, book[MAXN];
int vis[MAXN],D[MAXN * 11],dis[MAXN] , tail = 0 , q[MAXN];
int Ans = 1,Mod,A[11] = {0,2,3,5,7,11,13,17,19,23,61}; // A就是Miller Rabin 探测的底数
unordered_map <int,vector<int> > mp;
unordered_map <int,int > M;//记录哪一些质因子出现过
  
struct Edge {
    int next,to;
    void add(int from,int To) {to = To , next = start[from], start[from] = tot;}
} edge[MAXN * 2];
  
inline int read() {
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
  
void GetPrime() {//素数筛选
    for(int i = 2 ; i <= 5e4 ; i ++) {
        if(!book[i]) Prime[++cnt] = i;
        for(int j = 1 ; j <= cnt ; j ++) {
            if(Prime[j] * i > 5e4) break;
            book[Prime[j] * i] = 1;
            if(i % Prime[j] == 0) break;
        }
    }
    return ;
}
  
long long quickpower(long long x,long long y) {
    long long ans = 1 , op = x;
    while(y) {
        if(y & 1ll) ans *= op , ans %= Mod;
        op *= op , op %= Mod;
        y >>= 1ll;
    }
    return ans;
}
  
int Miller_Rabin(int x) {//素数探测算法
    Mod = x;
    int s = 0;
    if(x == 2) return 1;
    if(x % 2 == 0 || x == 1) return 0;
    int p = x - 1 ;
    while(p % 2 == 0) p/= 2 , s ++;
    for(int j = 1 ; j <= 5 ; j ++) {
        long long B = quickpower(A[j] , p);
        for(int i = 1 ; i <= s ; i ++) {
            long long K = (B * B) % Mod;
            if(K == 1ll && B != 1ll && B != Mod - 1) return 0;//如果二次探测发现这个不是质数
            B = K;
        }
        if(B != 1ll) return 0;//利用费马小定理判断
    }
    return 1;//探测正常结束
}
  
void DFS(int x,int P,int from) {
    vis[x] = 1;//处理与 x 点在同一个连通块的情况。
    q[++tail] = x;
    dis[x] = dis[from] + 1;
    for(int i = start[x] ; i ; i = edge[i].next) {
        int to = edge[i].to;
        if(to == from) continue;
        if(data[to] % P == 0)
        DFS(to,P,x);
    }
    return ;
}
  
int solve(int x,int P) {//笔者采用两次DFS求直径的方法来求出最长链
    tail = 0;
    int ans = 0;
    vis[x] = 1;
    DFS(x,P,0);//进行一次DFS求出离当前点最远的点P
    int f = 0;
    for(int i = 1 ; i <= tail ; i ++)
        if(dis[q[i]] > dis[f]) f = q[i];//找出离自己最远的
        for(int i = 1 ; i <= tail ; i ++) dis[q[i]] = 0;
    tail = 0;
    DFS(f,P,0);//第二次DFS
    f = 0;
    for(int i = 1 ; i <= tail ; i ++)
        if(dis[q[i]] > dis[f]) f = q[i];//找出离P最远的点Q
    return dis[f];//这个连通块的最长链
}
  
signed main() {
    n = read();
    GetPrime();
    memset(data,0,sizeof(data));
    for(int i = 1 ; i <= n ; i ++) data[i] = read();
    for(int i = 1 ; i <= n - 1; i ++) {
        int u = read() , v = read();
        edge[++tot].add(u,v);
        edge[++tot].add(v,u);
    }
    cnt = 0;
    for(int i = 1 ; i <= n ; i ++) {
        int x = data[i];
        int p = Miller_Rabin(x);
        if(p == 1) {//如果是质数就直接入列
            mp[x].push_back(i);
            if(M[x] != 1) M[x] = 1 , D[++cnt] = x;//新出现的质因子
            continue;
        }
        for(int j = 1 ; Prime[j] * Prime[j] <= x ; j ++)
            while(x % Prime[j] == 0) { //分解质因数
                x /= Prime[j] , mp[Prime[j]].push_back(i);
                if(M[Prime[j]] == 0) M[Prime[j]] = 1 , D[++cnt] = Prime[j];
            }
        if(x != 1) {
            mp[x].push_back(i);
            if(M[x] != 1) M[x] = 1 , D[++cnt] = x;
        }
    }
    for(int i = 1 ; i <= cnt ; i ++) {
        int len = mp[D[i]].size();
        for(int j = 0 ; j < len ; j ++)
        if(!vis[mp[D[i]][j]]) Ans = max (Ans , solve(mp[D[i]][j],D[i])) ;//还没被遍历的话就遍历
        for(int j = 0 ; j < len ; j ++) vis[mp[D[i]][j]] = 0 , dis[mp[D[i]][j]] = 0;
    }
    for(int i = 1 ; i <= n ; i ++)
        if(data[i] != 1)//特判是否全部为1
        {cout << Ans; return 0;}
    cout << 0;
    return 0;
}
```

---

