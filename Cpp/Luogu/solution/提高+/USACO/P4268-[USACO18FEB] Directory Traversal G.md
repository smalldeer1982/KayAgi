# [USACO18FEB] Directory Traversal G

## 题目描述

奶牛 Bessie 出人意料地精通计算机。她在谷仓的电脑上将所有珍贵文件存储在一系列目录中；例如：

```
bessie/
  folder1/
    file1
    folder2/
      file2
  folder3/
    file3
  file4
```

有一个单一的“顶级”目录，名为 `bessie`。

Bessie 可以导航到她想要的任何目录。从给定目录中，任何文件都可以通过“相对路径”引用。在相对路径中，符号 `..` 表示父目录。如果 Bessie 在 `folder2` 中，她可以通过以下方式引用四个文件：

```
../file1
file2
../../folder3/file3
../../file4
```

Bessie 希望选择一个目录，使得从该目录到所有文件的相对路径长度之和最小。

## 说明/提示

此输入描述了上面给出的示例目录结构。

最佳解决方案是位于 `folder1` 中。从该目录中，相对路径为：

```
file1
folder2/file2
../folder3/file3
../file4
```

题目来源：Mark Gordon

## 样例 #1

### 输入

```
8
bessie 3 2 6 8
folder1 2 3 4
file1 0
folder2 1 5
file2 0
folder3 1 7
file3 0
file4 0```

### 输出

```
42```

# 题解

## 作者：DengDuck (赞：4)

换根 DP 基础题。

这道题相当于问你，一棵树，选一个节点使得其到所有叶子节点的路径之和最小（因为路径上必然会经过所有节点）。

我们发现从一个点换到另外一个相邻的点中间相差的部分是很容易算出来的。

让我们画个图理解一手。

![](https://cdn.luogu.com.cn/upload/image_hosting/usu44cjq.png)

如图，我们进行转移 $A \to B$，边 $(A,B)=w,(B,A)=fw$，那么显然，蓝色部分的点到达我们选择的点距离减少了 $w$，而红色部分的点到我们选择的点距离增加了 $fw$。

我们需要预处理 $sz_x$ 表示 $x$ 子树中的**叶子节点数量**，根据这个数据，我们就知道每次转移需要减多少 $w$，加多少 $fw$，从而得到方程：

$$
f_B=f_A+(n-sz_x)\times fw-sz_x\times w
$$

显然时间复杂度为 $\mathcal O(n)$ 的。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5+5;
struct node
{
	LL to,w,fw;
};
LL n,tot[N],y,cnt,f[N],sz[N],ans=1e18;
vector<node>v[N];
vector<LL>a[N];
char c[N][25];
void get(LL x,LL fa,LL len)
{
	
	for(auto i:v[x])
	{
		if(i.to==fa)continue;
		get(i.to,x,len+i.w);
		sz[x]+=sz[i.to];
	}
	if(tot[x]==0)
	{
		f[1]+=len;
		cnt++;
		sz[x]++;		
	}

}
void dfs(LL x,LL fa)
{
	ans=min(ans,f[x]);
	for(auto i:v[x])
	{
		if(i.to==fa)continue;
		f[i.to]=f[x]-sz[i.to]*i.w+(cnt-sz[i.to])*i.fw;
		dfs(i.to,x);
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",c[i]);
		scanf("%lld",&tot[i]);
		for(int j=1;j<=tot[i];j++)
		{
			scanf("%lld",&y);
			a[i].push_back(y);
		}
	}
	for(int i=1;i<=n;i++)
	{	
		for(LL y:a[i])
		{
			LL t=strlen(c[y])+1;
			if(tot[y]==0)t--;
			v[i].push_back({y,t,3});
			v[y].push_back({i,3,t});
		}
	}
	get(1,0,0);
	dfs(1,0);
	printf("%lld\n",ans);
}
```

---

## 作者：Diaоsi (赞：4)

[[USACO18FEB]Directory Traversal G](https://www.luogu.com.cn/problem/P4268)


**二次扫描+换根 dp**

观察到文件夹的结构构成了一个树形结构（显然调用的路径不会成一个环，即在当前文件夹无法直接回到两级以上的祖先文件夹）。

那就考虑从题目中给定的根目录 ```bessie``` 为树根节点开始进行第一次遍历扫描，直接处理出从根目录出发到各个叶子节点的“路径长度”，在第二次扫描时通过根节点的答案去推出以其他非叶子节点作为根节点时的“路径长度”，然后在这其中取最小值就是最终答案。

以题目中的样例为例：

![树](https://cdn.luogu.com.cn/upload/image_hosting/mr7sp6iq.png)

其中加粗的为非叶子节点。

设：

+ $x$ 为任意节点， $y$ 为 $x$ 的子节点， $root$ 表示根目录所在的节点。

+ $w(x)$ 表示 $x$ 的父亲节点到 $x$ 的路径长度，特别地: $w(root)=0$ 。

+ $leaf(x)$ 表示以 $x$ 为根的子树内叶子节点的数量。

+ $dist(x)$ 表示根节点到 $x$ 节点的“路径长度” $+1$ (为方便计算，多计入了一个"/")。

+ $F(x)$ 表示以 $x$ 为根节点时到所有叶子结点的“路径长度”的总和。

在预处理以及第一次扫描时可以根据定义处理出 $\forall x \in [1,n] ,w(x), leaf(x),dist(x)$ 以及 $F(root)$ 。

在第二次遍历时我们观察到，当根节点由 $x$ 转移到 $y$ 时，对于任意的叶子节点 $u$ 有：

+ 当 $u$ 在以 $y$ 为根的子树内时， $u$ 到 $y$ 的“路径长度”为 $dist(y)-dist(x)-1=dist(u)-w(y)-1$ ，对结果的贡献为 $-w(y)-1$ 。

+ 当 $u$ 不在以 $y$ 为根的子树内时， $u$ 到 $y$ 的“路径长度”为 $dist(u)+3$ ，其中 $3$ 为"../"的长度，对结果的贡献为 $3$ 。

对于每类贡献，乘上他们对应的叶子节点数即可。

可以通过深度优先遍历进行转移，转移方程就呼之欲出了：

$$F(y)=F(x)-(w(y)+1) \ast leaf(y)+3*(leaf(root)-leaf(y))$$

$$ans=\min\{{F(x)\}}$$

注意一个细节，由于答案不可能在叶子节点上，所以转移只能在非叶子节点上进行。

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=100010,M=1000010,INF=0x3f3f3f3f3f3f3f3f;
long long head[N],ver[M],Next[M],tot;
long long n,root,ans=INF,w[N],F[N],v[N],dist[N],leaf[N];
inline long long Max(long long x,long long y){return x>y?x:y;}
inline long long Min(long long x,long long y){return x<y?x:y;}
inline void Swap(long long &x,long long &y){x^=y,y^=x,x^=y;}
void add(long long x,long long y){
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
}
void dfs1(long long x,long long fa){
	if(v[x])leaf[x]=1,F[root]+=dist[x]-1;
	for(long long i=head[x];i;i=Next[i]){
		long long y=ver[i];
		if(y==fa)continue;
		dist[y]=dist[x]+w[y]+1;
		dfs1(y,x);
		leaf[x]+=leaf[y];
	}
}
void dfs2(long long x,long long fa){
	if(x!=root)F[x]=F[fa]-(w[x]+1)*leaf[x]+(leaf[root]-leaf[x])*3;
	ans=Min(ans,F[x]);
	for(long long i=head[x];i;i=Next[i]){
		long long y=ver[i];
		if(y==fa||v[y])continue;
		dfs2(y,x);
	}
}
int main(){
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		long long x;
		string s;
		cin>>s;
		w[i]=(long long)s.size();
		if(s=="bessie")root=i,w[root]=0;
		scanf("%lld",&x);
		if(!x)v[i]=1;
		for(long long j=1;j<=x;j++){
			long long y;
			scanf("%lld",&y);
			add(i,y),add(y,i);
		}
	}
	dfs1(root,0);
	dfs2(root,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：cmrhhh (赞：3)

# [P4268 [USACO18FEB] Directory Traversal G](https://www.luogu.com.cn/problem/P4268)
## 题目描述：
个人感觉这道题目读着费劲，大概意思是说文件夹里有文件，问**最大的**从某个文件夹到文件（叶子）的**距离和**（就是“../../folder3/file3”这类操作的“相对路径”长度和）
## 输入：
请自行观看代码
## 算法分析：
用类似**换根 dp**的操作。由于如果使用朴素算法时复杂度有些许炸裂，我们考虑优化。注意到从某个文件夹转移到另一个文件夹的时候，他们之间有极大的关联性，换言之有如下关系： 
$$f[v] = f[u] - (w[v] + 1) \times leaf[v] + 3 \times (leaf[root] - leaf[v])$$
其中，$u$ 是 $v$ 的父亲，$f[i]$ 表示**某个文件夹到其子树的所有叶子节点的路径长度**，$leaf[i]$ 表示某个节点的**叶子数目**，$w[v]$ 表示某个节点与父节点之间的**相对路径长度**，即在这里，$w[v]$ 为文件（夹）名的长度。

是什么意思呢？就是说对于 $u$ 的下一个节点 $v$，他的 $f[v]$ 要由 $f[u]$ 减去向 $v$ 方向多走的 $u->v$ 的道路，道路有 $leaf[v]$ 条，权值为 $w[v] + 1$，加一是指（/），并且加上向 $u$ 方向少走的 $v->u$，条数为非 $v$ 的叶子的叶子数，权值为**三**（../）。
## 代码（马蜂还行）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e5+10;
int n,m,w[MAXN+10],root;
int head[MAXN+10],tot;
int leaf[MAXN+10],f[MAXN+10],sz[MAXN+10],dis[MAXN+10];//dis 根到x 的wi+1(/) 
int ans;
struct Edge{
	int to,nxt;
}edge[MAXN*2+10];
inline void add(int u,int v){
	edge[++tot]=(Edge){v,head[u]};
	head[u]=tot;
}
//二次扫描+换根DP 
inline void dfs1(int u,int fa){
	if(sz[u])leaf[u]=1,f[root]+=dis[u]-1;//处理root 
	for(register int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa)continue;
		dis[v]=dis[u]+w[v]+1;
		dfs1(v,u); 
		leaf[u]+=leaf[v];
	}
}
inline void dfs2(int u,int fa){
	for(register int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa||leaf[v]==1)continue;
		f[v]=(long long)(f[u]-1ull*(w[v]+1)*leaf[v]+3ull*(leaf[root]-leaf[v])); 
		if(ans>f[v])ans=f[v];
		dfs2(v,u);
	}
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	string c;
	for(register int i=1;i<n+1;++i){
		int op;
		cin>>c>>m;
		if(!m)sz[i]=1; 
		if(c=="bessie")root=i,w[i]=0;
		else w[i]=(long long)c.length();//文件名也有用 
		for(register int j=1;j<m+1;++j){
			cin>>op;
			add(i,op);
			add(op,i);
		}
	}
	dfs1(root,0);//cout<<f[root]<<"\n";
	ans=f[root];//注意 
	dfs2(root,0);
	//for(int i=1;i<=n;++i)cout<<leaf[i]<<" ";cout<<"\n";
	cout<<ans;
	return 0;
} 
```

---

## 作者：CR_Raphael (赞：3)

搜索题

文件信息是一棵树

先求根节点的总路径长度

同时把各节点下文件个数求出来

再依次由父节点的总路径长度推出子节点的总路径长度：

①把父节点所有路径中父节点到子节点的路径减去。这样的路径数量等于该节点下文件个数，长度等于文件名长度+1（加上“/”）

②把子节点所有路径中子节点到父节点的路径减去。这样的路径数量等于：总文件数 减 该节点下文件个数，长度等于3（“../”）

最后找最小的

注意long long

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define son sons[x]
#define dfa dfs_for_ans
#define LL (long long int)
#define LLI long long int
using namespace std;

const int MAXN=100005;
const LLI inf=9223372036854775807;

vector <int> sons[MAXN];
int n,nf;
int filee[MAXN];
int num[MAXN];
int fa[MAXN];
int down_num[MAXN];
LLI go_down[MAXN];
LLI dist[MAXN];

void dfs(int x){
	int t,i,k=son.size();
	down_num[x]=filee[x];
	go_down[x]=0;
	
	for(i=0;i<k;i++){
		t=son[i];
		dfs(t);
		
		down_num[x] += down_num[t];
		go_down[x]  += go_down[t] + LL(num[t]*down_num[t]);
	}
	
	return;
}

void dfs_for_ans(int x){
	int t,i,k=son.size(),F=fa[x];
	
	if(x==1)dist[x]= go_down[x];
	else	dist[x]= dist[F] - LL(down_num[x]*num[x]) + 3*LL(nf-down_num[x]);
	
	for(i=0;i<k;i++){
		t=son[i];
		dfa(t);
	}
	
	return;
}

int main(){
	int i,j,d,t;
	LLI minn;
	string s;
	cin>>n;
	
	nf=0;
	
	for(i=1;i<=n;i++){
		cin>>s;
		num[i]=s.size()+1;
		
		cin>>d;
		if(d!=0){
			filee[i]=0;
			for(j=1;j<=d;j++){
				cin>>t;
				fa[t]=i;
				sons[i].push_back(t);
			}
		}
		else filee[i]=1,num[i]--,nf++;
	}
	
	dfs(1);
	dfa(1);
	
	
	minn=inf;
	for(i=1;i<=n;i++){
		if(filee[i]==0 && dist[i]<minn)minn=dist[i];
	}
	
	cout<<minn<<endl;
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：3)

十分显然文件夹和文件组成了一个树形结构（会用cmd的人都知道，在 CMD 中显示路径的目录结构就是输入 ```tree```）。

不过这个树有点特殊。对于一条边 $(u,v)$（$u$ 是 $v$ 的父亲），从 $v$ 走到 $u$ 需要 ```../```，从 $u$ 走到 $v$ 需要 ```name/```，也就是说向上走的cost是 $3$，向下走的cost是 $v$ 的长度加一。

既然是要选定一个点求值且数据范围如此，我们可以想到用**二次扫描法**做这题（其实就是换根DP但是这题上下不一样所以不能叫做换根DP）.

$s_u$ 代表 $u$ 子树内有多少个叶节点，$f(u)$ 表示 $u$ 子树内叶节点到 $u$ 的路径和，$g(u)$ 表示字数外叶节到 $u$ 的路径和。

$$
f(u)=\sum_{v\in son_u} w_{u,v}\times s_v+f(v)
$$

$f$ 很好求，我们来看 $g$。

画张图。可大致分为两种：兄弟子树，父亲的 $g$。

父亲 $u$ 的 $g$ 对 $v$ 做出的贡献是 $3\times (s_1-s_u)+g(u)$。兄弟对 $v$ 做出的贡献是 $3\times (s_u-s_v)+f(u)-w\times s_v-f(v)$，加起来即可。

注意，答案是 $f(u)+g(u)-s_1$，因为对于每一个叶节点我们多算了一个末尾的 ```/```。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=100009;

int n,a[N],s[N],f[N],g[N],ans=0x3f3f3f3f3f3f3f3f;
vector<int>y[N],w[N];

void dfs1(int u,int fa) {
	if(y[u].size()) rep(j,0,y[u].size()-1) {
		int v=y[u][j];
		if(v==fa) continue;
		dfs1(v,u);
		s[u]+=s[v];
		f[u]+=w[u][j]*s[v]+f[v];
	}
	if(!y[u].size()) s[u]=1;
}

void dfs2(int u,int fa) {
	if(y[u].size()) rep(j,0,y[u].size()-1) {
		int v=y[u][j];
		if(v==fa) continue;
		g[v]=3*(s[1]-s[v])+g[u]+f[u]-w[u][j]*s[v]-f[v];
		dfs2(v,u);
	}
	if(y[u].size()) ans=min(ans,f[u]+g[u]-s[1]);
}

signed main() {
	scanf("%lld",&n);
	rep(i,1,n) {
		string s; cin>>s; a[i]=s.size();
		int m; cin>>m;
		rep(j,1,m) {
			int v; scanf("%lld",&v);
			y[i].push_back(v);
		}
	}
	rep(i,1,n) if(y[i].size())
		rep(j,0,y[i].size()-1) {
			w[i].push_back(a[y[i][j]]+1);
		}
	dfs1(1,0), dfs2(1,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：曹老师 (赞：3)

不要以为名字没有用！！！

输入什么的就不说了（逃

dfs1:求出从根节点到其他点的相关信息

dfs2:求答案

len:文件夹或文件名字长度

dis:距离

z:叶节点的数目

f:答案（相对路径长度）

leaf:总的叶节点的个数

son:存子节点

**重点是dfs2! ! !**

```cpp
f[o]=f[x]-(len[o]+1)*z[o]+3*(leaf-z[o]);
```

~~重点式子↑↑↑↑↑~~

怎么理解？f[x]是父节点的答案 f[o]是子节点的答案

无非就是父节点更新子节点的递推关系式

(len[o]+1)*z[o]   表示从x点到o点的距离（很显然要减去）

3*(leaf-z[o])  为什么是3？ ../ 不就是3嘛

也就是从o到x要加多少 ../

于是递推式就出来了~

剩下的就是找答案了~

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define INF 2147483640
#define MOD 100000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
using namespace std;
const int L=1e5+5;
LL int n,len[L],leaf,dis[L],z[L],f[L],ans;
vector<int>son[L];
void dfs1(int x)
{
	for(int i=0;i<son[x].size();i++)
	{
		int o=son[x][i];
		dis[o]=dis[x]+len[o]+1;
		dfs1(o);
		z[x]+=z[o];
	}
	if(!son[x].size())
	{
		z[x]=1;
		dis[x]--;
		f[1]+=dis[x];
	}
}
void dfs2(int x)
{
	for(int i=0;i<son[x].size();i++)
	{
		int o=son[x][i];
		if(!son[o].size())
			continue;
		f[o]=f[x]-(len[o]+1)*z[o]+3*(leaf-z[o]);
		ans=min(ans,f[o]);
		dfs2(o);
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		LL int m;
		char s[20];
		scanf("%s",s+1);
		len[i]=strlen(s+1);
		scanf("%lld",&m);
		if(!m)
			leaf++;
		for(int j=1;j<=m;j++)
		{
			LL int t;
			scanf("%lld",&t);
			son[i].push_back(t);
		}
	}
	dfs1(1);
	ans=f[1];
	dfs2(1);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：zhmshitiancai (赞：2)

[门](https://www.luogu.org/problem/P4268)


解：树形dp+二次扫描，换根法。

$a[x]$:此节点的文件名长度。

$dp[x]$:$x$到其子树的所有叶子节点的路径长度。

$si[x]$:以$x$为根的子树中，叶子节点的个数。

$ans[x]$:二次扫描，存答案

第一遍dfs:
$$dp[x]=\sum(dp[son]+(a[son]+1)*si[son])$$

**第二遍dfs:**

$$ans[son]=3*(tot-si[son])+ans[x]-(a[son]+1)*num[son]$$

### Tips:
1. minv初值要赋大一点。
2. 开始时向下走没有$ \times si[son]$。

**Code:**
```
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int INF=0x3f3f3f3f,MAX=1e5+5;
int n;
long long a[MAX],dp[MAX],si[MAX],ans[MAX],tot;
bool leaf[MAX],vis[MAX];
int head[MAX],to[2*MAX],cnt,Next[2*MAX];
void add(int x,int y)
{
	cnt++;
	Next[cnt]=head[x];
	to[cnt]=y;
	head[x]=cnt;
}
void dfs(int x)
{
	int i;
	vis[x]=true;
	si[x]=leaf[x];
	for(i=head[x];i;i=Next[i])
	{
		int son=to[i];
		if(vis[son]) continue;
		dfs(son);
		si[x]+=si[son];
		dp[x]+=dp[son]+(ll)(a[son]+1)*si[son];
	}
}
void dfs2(int x)
{
	int i;
	vis[x]=true;
	for(i=head[x];i;i=Next[i])
	{
		int son=to[i];
		if(vis[son]) continue;
		ans[son]=3*(ll)(tot-si[son])+ans[x]-(ll)(a[son]+1)*si[son];
		dfs2(son);
	}
}
int main()
{
//	freopen("nine.in","r",stdin);
//	freopen("9.ans","w",stdout);
	int i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		a[i]=s.size();
		int m;
		scanf("%d",&m);
		if(m==0) 
		{
			tot++;
			leaf[i]=1;	
		}
		
		while(m-->0)
		{
			int x;
			scanf("%d",&x);
			add(i,x);
			add(x,i);
		}
	}
	dfs(1);
	memset(vis,0,sizeof(vis));
	ans[1]=dp[1];
	dfs2(1);
	
	long long minv=9223372036854775807;
	for(i=1;i<=n;i++)
	{
		if(!leaf[i]) minv=min(minv,ans[i]-tot);	
	}
//	cout<<INF<<endl;	
	cout<<minv<<endl;
}
```

---

## 作者：liugh_ (赞：0)

其实感觉根本算不上换根 dp，只需要预处理一些信息，扫一遍就能统计答案。

- 记点 $u$ 名称长度为 $w_u$，为方便，在文件夹的名称末尾添一个 `/`。
- 记点 $u$ 子树的叶子数量为 $c_u$。
- 记从 $u$ 到子树内所有叶子的路径长度和为 $f_u$，显然有 $f_u=\sum_{v\in son_u} (f_v+c_vw_v)$。

考虑维护当前点 $u$ 到子树外所有叶子的路径长度和 $cur$，显然 $u$ 对答案的贡献为 $cur+f_u$。

考虑从 $u$ 走到 $v$，

- $v$ 子树外的所有叶子都需多经过一个 `../`，即 $cur\xleftarrow{+} 3(c_1-c_v)$。
- 属于 $u$ 子树而不属于 $v$ 子树的叶子的贡献需要加入，即 $cur\xleftarrow{+} f_u-f_v-c_vw_v$。

```cpp
auto dfs1=[&](auto&&dfs1,int u)->void{
    c[u]=G[u].empty();
    for(auto v:G[u]){
        dfs1(dfs1,v);
        f[u]+=f[v]+c[v]*s[v].size();
        c[u]+=c[v];
    }
};dfs1(dfs1,1);
auto dfs2=[&](auto&&dfs2,int u,int lst,LL sum)->void{
    if(lst)sum+=3*(c[1]-c[u])+f[lst]-f[u]-c[u]*s[u].size();
    tomin(ans,sum+f[u]);
    for(auto v:G[u])dfs2(dfs2,v,u,sum);
};dfs2(dfs2,1,0,0);
```

---

## 作者：hytallenxu (赞：0)

## 前言
这道题细节很多，出题人 ~~**[数据删除]**~~ 出的真好。

## 正文
换根 DP 简（kun）单（nan）题。

不妨先考虑将文件夹设为主文件夹 `bessie` 时如何计算答案 $f_1$。

首先以 $1$ 为根，递归获取每个节点 $i$ 的子树的叶子节点数量 $siz_i$。这部分是简单的。

我们可以设 $f_u$ 为 「编号为 $u$ 的文件夹走到其**子树下**所有叶子节点所需的路径长度」。

我们可以推出来 $f_u$ 应该是一个和，这个和包括了

1. $f_v$，以及

2. 在 $v$ 的子树下的叶子节点数量乘以当前目录的长度。

于是可以得到如下式子：

$$f_u=\sum_{v\in son_u} (f_v+siz_v \times(\text{length of file } u+tmp))$$

其中当 $v$ 是叶子节点时，$tmp=0$，否则 $tmp$ 则为 $1$。

为什么需要添加 $tmp$ 呢？因为当 $v$ 是文件（并非文件夹）时，路径最后不需要添加 `/` 指示符。

我们现在得到了根为 $1$ 时的结果，考虑如何将问题扩展到任意根。

首先朴素每个点跑一遍肯定是不行的，时间复杂度 $O(n^2)$。

考虑换根，从父亲节点的答案推到子节点。

来看样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/fu5cwsa8.png)

我们首先已经通过上方的算法，计算出了 $f_1$。

设 $dp_u$ 为 「编号为 $u$ 的文件夹走到**所有叶子节点**所需的路径长度」，我们有初始值 $dp_1=f_1$，我们看如何把状态转移到 $dp_2$。

对于编号 $2$，走到紫色圈内的叶子节点的话，每次需要回退到父亲节点 $1$，产生一次贡献 `../`。

同时，走到绿色圈内的叶子节点的话，每次需要少进入子节点 $(\text{length of file } 2) +1$ 次，我们可以相对应的减少贡献。

所以，我们有：

$$dp_v=dp_u+(siz_1-siz_v) \times 3-siz_v \times (\text{length of file }v+1)$$

## Code
总时间复杂度显然为 $O(n)$，需要注意的是细节比较多。


```cpp
#include <bits/stdc++.h>
#define int long long
#define mp make_pair
#define pb emplace_back
#define endl "\n"
using namespace std;
using ll = long long;
int n,t,cnt=0,ans=1e18;
int arr[100001],siz[100001],f[100001],dp[100001],head[200001];
bool isLeaf[100001];
struct{int from,to,next;}edge[200001];
inline void add(int u, int v){
	edge[cnt].from=u;edge[cnt].to=v;edge[cnt].next=head[u];
    head[u]=cnt++;
}
inline void init(){for(int i=1;i<=n;i++)edge[i].next=head[i]=-1;}

void dfs(int u, int fa){
	if(isLeaf[u]){
		siz[u]=1;
		return;
	}
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		f[u]+=(f[v]+siz[v]*(arr[v]+(isLeaf[v]?0:1)));
	}
}

void dfs2(int u, int fa){
	if(!isLeaf[u]) ans=min(ans,dp[u]);
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v==fa) continue;
		dp[v]=dp[u]+(siz[1]-siz[v])*3-siz[v]*(arr[v]+1);
		dfs2(v,u);
	}
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n;init();
	for(int i=1;i<=n;i++){
		string s;int res;cin>>s>>res;
		arr[i]=s.size();
		if(res){
			for(int j=1;j<=res;j++){
				int v;cin>>v;
				add(i,v);
				add(v,i);
			}
		}else{
			isLeaf[i]=1;
		}
	}
	dfs(1,0);
	dp[1]=f[1];
	dfs2(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：Violet___Evergarden (赞：0)

# 换根dp
通过观察可发现，文件夹和文件之间的包围关系可看做一棵跟为 $1$ 的树。

那么对于每个文件节点 $i$，设其深度为 $deep_i$，它到根节点包括自己、不包括跟节点的文件和文件夹名字长度总和为 $l$ ，于是从根节点到这个节点的路径一共有 $deep_i-deep_1-1$ 个斜杠，那么从根节点到它路径长度是 $deep_i-deep_1-1+l$。

设选择节点 $i$ 时，所有文件的相对路径的长度之和是 $dp_i$，那么我们就可以求出 $dp_1$ 的情况。
```cpp
for(int i=2;i<=n;i++)//枚举节点
{
  if(!f[i].m)//该节点为文件
  {
    num++;
    dp[1]+=qzh[i]-qzh[1]+deep[i]-deep[1]-1;//此处qzh[i]表示从根到 i 路径上节点名字长度和
  }
}
```


------------

然后我们从根到每个节点扩展 $dp$ 数组，如果从节点 $i$ 扩展到它的儿子 $j$，设总文件数量是 $num$，$j$ 的子树包含 $s_j$ 个文件，$j$ 节点名字长度为 $l_j$。

你会发现，因为从 $i$ 到 $j$ 其实是往下走，所以会有 $num-s_j$ 个文件的路径多一个
```../```，但是又会有 $s_j$ 个文件的路径少了一个 $l_j$ 的长度和一个斜杠，于是转移方程如下：
$$dp_j=dp_i+3 \times (num-s_j)-s_j \times (l_j+1)$$
于是你就可以 A 了这道题了。
```cpp
#include <iostream>
#include <cstring>
#define int long long
using namespace std;
const int kMaxN=1e5+1;
struct F
{
  string name;
  int m;
}f[kMaxN];
int n;
struct EDGE
{
  int to,nt;
}e[kMaxN*2];
int hd[kMaxN],cnt;
int deep[kMaxN],howmany[kMaxN],qzh[kMaxN];//deep[i]指i的深度，howmany[i]指i的子树中有多少个文件
int dp[kMaxN],ans,num;
void Add(int a,int b)//两个点之间连边
{
  e[++cnt].to=b;
  e[cnt].nt=hd[a];
  hd[a]=cnt;
}
void Dfs(int now,int last)//预处理各种数组
{
  deep[now]=deep[last]+1;
  qzh[now]=qzh[last]+f[now].name.length();
  if(!f[now].m)
  {
    howmany[now]=1;
    return;
  }
  for(int i=hd[now];i;i=e[i].nt)
  {
    if(e[i].to==last)continue;
    Dfs(e[i].to,now);
    howmany[now]+=howmany[e[i].to];
  }
}
void Dp(int now,int last)//换根dp
{
  if(!f[now].m)return;//只能选择文件夹不能选文件
  int that=num-howmany[now];
  dp[now]=dp[last]+that*3-howmany[now]*(f[now].name.length()+1);
  ans=min(ans,dp[now]);
  for(int i=hd[now];i;i=e[i].nt)
  {
    if(e[i].to==last)continue;
    Dp(e[i].to,now);
  }
}
signed main()
{
freopen("dirtraverse.in","r",stdin);
freopen("dirtraverse.out","w",stdout);
cin>>n;
for(int i=1;i<=n;i++)
{
  cin>>f[i].name>>f[i].m;
  for(int j=1;j<=f[i].m;j++)
  {
    int x;
    cin>>x;
    Add(i,x);
    Add(x,i);
  }
}
Dfs(1,0);
for(int i=2;i<=n;i++)//计算dp[1]
{
  if(!f[i].m)
  {
    num++;
    dp[1]+=qzh[i]-qzh[1]+deep[i]-deep[1]-1;
  }
}
ans=dp[1];
for(int i=hd[1];i;i=e[i].nt)
{
  Dp(e[i].to,1);
}
cout<<ans;
return 0;
}
```

---

