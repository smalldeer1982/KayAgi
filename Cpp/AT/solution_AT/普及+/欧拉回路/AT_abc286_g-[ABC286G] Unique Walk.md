# [ABC286G] Unique Walk

## 题目描述

给定一个有 $N$ 个顶点、$M$ 条边的简单连通无向图 $G$。  
$G$ 的顶点编号为 $1,2,\ldots,N$，边编号为 $1,2,\ldots,M$，其中第 $i$ 条边连接顶点 $U_i$ 和顶点 $V_i$。  
此外，给定一组边的子集 $S=\{x_1,x_2,\ldots,x_K\}$。

请判断在 $G$ 上是否存在一条“步道”，使得对于任意 $x\in S$，边 $x$ 恰好被经过一次。  
对于不在 $S$ 中的边，可以经过任意次数（包括 $0$ 次）。

步道的定义如下：  
在无向图 $G$ 上，步道是指由 $k$ 个（$k$ 为正整数）顶点和 $k-1$ 条边交替组成的序列 $v_1,e_1,v_2,\ldots,v_{k-1},e_{k-1},v_k$，其中每条边 $e_i$ 连接顶点 $v_i$ 和 $v_{i+1}$。序列中顶点和边可以重复出现。步道经过边 $x$ 恰好一次，指的是在 $1\leq i\leq k-1$ 中，只有唯一的 $i$ 使得 $e_i=x$。

## 说明/提示

### 限制条件

- $2\leq N\leq 2\times 10^5$
- $N-1\leq M\leq \min\left(\frac{N(N-1)}{2},2\times 10^5\right)$
- $1\leq U_i<V_i\leq N$
- 若 $i\neq j$，则 $(U_i,V_i)\neq (U_j,V_j)$
- $G$ 是连通图
- $1\leq K\leq M$
- $1\leq x_1<x_2<\cdots<x_K\leq M$
- 输入均为整数

### 样例解释 1

用 $v_i$ 表示顶点 $i$，$e_j$ 表示边 $j$，则序列 $(v_1,e_1,v_3,e_3,v_4,e_4,v_5,e_6,v_6,e_5,v_4,e_3,v_3,e_2,v_2)$ 表示的步道满足条件。  
即在 $G$ 上按顶点 $1\to 3\to 4\to 5\to 6\to 4\to 3\to 2$ 的顺序移动。  
该步道恰好经过了边 $1,2,4,5$ 各一次，满足条件。

### 样例解释 2

不存在一条步道恰好经过边 $1,2,3$ 各一次，因此输出 `No`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 6
1 3
2 3
3 4
4 5
4 6
5 6
4
1 2 4 5```

### 输出

```
Yes```

## 样例 #2

### 输入

```
6 5
1 2
1 3
1 4
1 5
1 6
3
1 2 3```

### 输出

```
No```

# 题解

## 作者：_shine_ (赞：5)

UPD：更新了对缩点的赘述，并增加了对关键部分的理解

接下来把可以走多次的边称作次要边。
### 思路
本题像是一道裸的无向欧拉路径问题，但在图中还包含了不是关键边的次要边（可以走多次，而关键边只能走一次），显然是把其进行化简。

不妨先只看次要边，然后把这些次要边组成的联通块看做一个个点，看成点（即缩点）之后再一起看就变成了由点（次要边联通块）、关键边组成的无向图，此时显然即可使用欧拉路径。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m,k;
int a[maxn],b[maxn];
bool vis[maxn];//判断是否为关键边
int c[maxn];
int f[maxn],in[maxn];//并查集和记录该点的度
int find(int x){
	if(f[x]==x)return x;
	else return f[x]=find(f[x]);
}
signed main(){
	cin >> n >> m;
	for(int i=1;i<=n;++i){//初始化
		f[i]=i;
	}
	for(int i=1;i<=m;++i){
		cin >> a[i] >> b[i];
	}
	cin >> k;
	for(int i=1;i<=k;++i){//标记关键边。
		cin >> c[i];
		vis[c[i]]=true;
	}
	for(int i=1;i<=m;++i){//先把关键边除去，只看次要边。
		if(vis[i]!=true){
			f[find(a[i])]=find(b[i]);
		}
	}
	for(int i=1;i<=k;++i){//记录缩点后点的度
		in[find(a[c[i]])]++,in[find(b[c[i]])]++;
	}
	int ans=0;//欧拉回路
	for(int i=1;i<=n;++i){
		if(in[i]%2!=0){
			ans++;
		}
	}
	if(ans<=2)puts("Yes");
	else puts("No");
	return 0;
}
```

---

## 作者：小木虫 (赞：4)

### Preface  
图论套路聪明题。  

### Problem  
给你一个无向图，其中有一些边是一次性的，即只能走过一次，问有没有一种路径，使得这条路径走过所有一次性边。  

### Solution  
考虑将所有的一次性边断开，剩下的图会碎成若干个连通块。  
由于其它边并没有通过次数限制，即可以在里面随便走，所以每个连通块可以抽象为一个点。  

然后随便考虑一下在连通块内部，即两端点在同一个连通块的一次性边。  
显然只要到了这个连通块就可以直接走掉，无需考虑。  

然后我们现在拿到了一个无向图，要求找到一条路径走掉所有的边恰好一次。  
显然这是欧拉路径问题，当奇数度点为 0 个或 2 个的时候为 $\text{Yes}$，否则为 $\text{NO}$。  

连通块的度数由于是奇偶性，可以直接并查集维护：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,k,x,vis[N],u[N],v[N],fa[N],deg[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);y=find(y);
	if(x==y)return;
	fa[y]=x;deg[x]+=deg[y];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
		cin>>u[i]>>v[i],deg[u[i]]++,deg[v[i]]++;
	cin>>k;
	for(int i=1;i<=k;i++)
		cin>>x,vis[x]=1;
	for(int i=1;i<=m;i++){
		if(vis[i])continue;
		merge(u[i],v[i]);
	}int cnt=0;
	for(int i=1;i<=n;i++){
		if(fa[i]!=i)continue;
		cnt+=(deg[i]%2);
	}
	if(cnt<=2){
		cout<<"Yes";
	}else{
		cout<<"No";
	}
	return 0;
}
```


---

## 作者：zlqwq (赞：2)

通过题意我们可以发现，每一个联通分量之间其实互不相干，因此我们将这些连通分量看做是一个点就可以了。

进行一个缩点操作，将这张图进行简化，就得到了一张新的无向图。

最后判断一下是否存在欧拉路径即可。


```cpp
#include<iostream>
#define int long long
#define debug cout << "zlqwq"
#define inf 1e18
using namespace std;
const int N = 2e5 + 5;
int n,m,k;
int fa[N];
int u[N],v[N],x[N],vis[N];
int find(int x) {
	return x == fa[x] ? x : fa[x] == find(fa[x]);
}
void merge(int u,int v) {
	fa[find(u)] = find(v);
}
int d[N];
signed main() {
	cin >> n >> m;
	for(int i = 1;i <= n;++i) {
		fa[i] = i;
	}
	for(int i = 1;i <= m;++i) {
		cin >> u[i] >> v[i];
	}
	cin >> k;
	for(int i = 1;i <= k;++i) {
		cin >> x[i];
		vis[x[i]] = 1;
	}
	for(int i = 1;i <= m;++i) {
		if(!vis[i]) merge(u[i],v[i]); 
	}
	for(int i = 1;i <= k;++i) {
		d[find(u[x[i]])]++;
		d[find(v[x[i]])]++;
	}
	int cnt = 0;
	for(int i = 1;i <= n;++i) {
		if(d[i] % 2) cnt++;
	} 
	cout << (cnt < 3 ? "Yes" : "No");
	return 0;
}
```

---

## 作者：_Flame_ (赞：1)

### $\text{solution}$

常用的小套路。

考虑断开所有关键边，整个图会变成一个个由非关键边组成的连通块。

在非关键边组成的连通块内怎么走显然无关紧要，所以将所有的非关键边连通块缩成一个个点，这里可以用并查集维护连通块。

现在整个图变成了一个由关键边组成的无向图，用欧拉路径问题的判断方法判断是否有一条经过每一条边恰一次的路径即可。

### $\text{code}$

```cpp
int n,m,k;

int u[maxn],v[maxn];

int e[maxn];

bool bk[maxn];

int fa[maxn],d[maxn];

int find(int x){
	if(fa[x]==x){
		return x;
	}
	else{
		return fa[x]=find(fa[x]);
	}
}

void merge(int x,int y){
	int nx=find(x),ny=find(y);
	fa[nx]=ny;
	return ;
}

void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
}

int euler(){
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(d[i]%2!=0){
			cnt++;
		}
		if(cnt>2){
			return 0;
		}
	}
	return 1;
}

void solve(){
	n=read(),m=read();
	init();
	for(int i=1;i<=m;i++){
		int u1=read(),v1=read();
		u[i]=u1;
		v[i]=v1;
	}
	k=read();
	for(int i=1;i<=k;i++){
		e[i]=read();
	}
	for(int i=1;i<=k;i++){
		bk[e[i]]=1;
	}
	for(int i=1;i<=m;i++){
		if(bk[i]){
			continue ;
		}
		else{
			merge(u[i],v[i]);
		}
	}
	for(int i=1;i<=m;i++){
		int nu=find(u[e[i]]),nv=find(v[e[i]]);
		d[nu]++;
		d[nv]++;
	}
	if(euler()){
		puts("Yes");
		return ;
	}
	else{
		puts("No");
		return ;
	}
	return ;
}
```


---

## 作者：This_Rrhar (赞：1)

我们发现非关键边可以走任意次，也就是说：如果图中有一个连通分量中的边都是非关键边，那么这个连通分量就可以简化成一个点，因为我们可以经过这个连通分量任意次。我们依照这个条件对图进行缩点操作，得到的新图中的边就都是关键边，最后我们判断新图是否存在欧拉路径即可。

代码如下（C++20）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _r return*this
#define _o &operator
namespace IO
{
	const int _S=1<<21;
	char b[_S],*p1=b,*p2=b,pb[_S],*pp=pb;
	void fl(){fwrite(pb,1,pp-pb,stdout),pp=pb;}
	struct input
	{
		char gc(){if(p1==p2)p2=(p1=b)+fread(b,1,_S,stdin);return p1==p2?' ':*p1++;}
		input _o>>(char&c){do c=gc();while(c==' '||c=='\n'||c=='\r'||c=='\t');_r;}
		template<class T>input _o>>(T&x)
		{
			char c=gc();T f=1;
			for(x=0;!isdigit(c);)(c=='-'?f=-1:1),c=gc();
			while(isdigit(c))x=(x*10)+(c^48),c=gc();
			x*=f;_r;
		}
		input(){}
	}in;
	struct output
	{
		void pc(char c){*pp++=c;if(pp-pb==_S)fl();}
		output _o<<(char c){pc(c);_r;}
		template<class T>output _o<<(T x)
		{
			if(!x){pc(48); _r;}
			if(x<0)pc('-'),x=-x;
			int s[64],t=0;
			while(x)s[++t]=x%10,x/=10;
			while(t)pc(s[t--]+48);
			_r;
		}
		output _o<<(const char*s){int c=0;while(s[c])pc(s[c++]);_r;}
		output(){}
	}out;
	struct fe{~fe(){fl();}}fls;
}
using IO::in;
using IO::out;
using ll=long long;

#define N 200001

ll u[N],v[N],sp[N];
bool vis[N];

ll f[N];
ll F(ll i){return i==f[i]?i:f[i]=F(f[i]);}

ll n,m,k;
ll deg[N];
ll ans;

int main()
{
	in>>n>>m;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)in>>u[i]>>v[i];
	in>>k;
	for(int i=1;i<=k;i++)in>>sp[i],vis[sp[i]]=true;
	for(int i=1;i<=m;i++)if(!vis[i])f[F(u[i])]=F(v[i]);
	for(int i=1;i<=k;i++)deg[F(u[sp[i]])]++,deg[F(v[sp[i]])]++;
	for(int i=1;i<=n;i++)ans+=deg[i]&1;
	if(ans<=2)out<<"Yes";
	else out<<"No";
}
```

---

## 作者：Shunpower (赞：1)

## 思路

很容易想到我们的路径上两条关键边之间是若干非关键边。于是考虑去掉关键边之后什么情况。可以注意到原图被我们分成了若干连通块，由于原图是无向图，所以可以想到在同一个连通块里面的关键边是一定可以不重不漏地走完的。

把连接两个不同连通块的关键边单拎出来，然后把连通块缩成点建图，那么我们的目的就变成了一条路径不重不漏地走完整个图，说白了就是一笔画。因为连通块内部的关键边一定能走完，并且由于点之间构成连通块所以可以从任意一个点开始，也可以停在任意一个点所以缩成一个点只要能到这个点就行；连通块之间的边因为肯定是关键边所以必须走且只能走一次。

问题转成欧拉路径的判断性问题，只需要判断缩点之后的图是否有 $0$ 个或 $2$ 个奇数度点就行了。

## 代码

用 `map` 标记关键边之后跑 DFS 做无向图连通块标颜色就行，然后统计两端颜色不一样的边，对两端点的度数做贡献。


```cpp
int n,m,k;
pii e[N];
map <pii,bool> p;
int tot;
int vis[N];
int col[N];
int ins[N];
vector <int> g[N];
void dfs(int x,int c){
	col[x]=c;
	vis[x]=1;
	fv(i,g[x]){
		int y=g[x][i];
		if(!vis[y]&&!p.count(mp(x,y))){
			dfs(y,c);
		}
	}
}
int cnt;
int main(){
	cin>>n>>m;
	fr1(i,1,m){
		int u,v;
		cin>>u>>v;
		e[i]=mp(u,v);
		g[u].pb(v);
		g[v].pb(u);
	}
	cin>>k;
	fr1(i,1,k){
		int x;
		cin>>x;
		p[e[x]]=1;
		p[mp(e[x].se,e[x].fi)]=1;
	}
	fr1(i,1,n){
		if(!vis[i]){
			tot++;
			dfs(i,tot);
		}
	}
	for(auto d:p){
		pii x=d.fi;
		if(col[x.fi]!=col[x.se]){
			ins[col[x.fi]]++;
			ins[col[x.se]]++;
		}
	}
	fr1(i,1,tot){
		ins[i]>>=1;
		if(ins[i]&1){
			cnt++;
		}
	}
	if(cnt!=0&&cnt!=2){
		cout<<"No"<<endl;
	}
	else{
		cout<<"Yes"<<endl;
	}
    ET;
}
//ETERNAL LOVE FOR Zhang Junhao, Zuo Hang and Mu Zhicheng.
//ALL FOR Zhang Junhao.
```


---

## 作者：CQ_JiJi (赞：1)

# 思路
这玩意，和一笔画问题没太大区别。

对于这种有边只能走 $1$ 次的题，首先考虑断开这些边，然后我们会得到一堆连同快，接着就是缩点的思想，首先，在联通块里面走是无意义，所以我们直接将联通块缩成一个点，再连上只能走 $1$ 次的边，那剩下的就是正常的能否一笔画了。根据小学奥数的结论，若一笔画能跑完，则满足所有点能直接到达的点的个数为奇数的点的个数为 $0$ 或 $2$，又因为是无向图，所以可以直接用并查集。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e6+10;
using namespace std;
int n,m,u[N],v[N],k,x[N],fa[N],cnt,out[N];
bool vis[N];
int find(int x)//查找 
{
	if(x!=fa[x]) return fa[x]=find(fa[x]);
	return x;
}
void merge(int x,int y)//合并 
{
	fa[find(x)]=fa[y=find(y)];
	return;
}
signed main()
{
	cin>>n>>m;
	rep1(i,1,n) fa[i]=i;
	rep1(i,1,m) cin>>u[i]>>v[i];
	cin>>k;
	rep1(i,1,k)
	{
		cin>>x[i];
		vis[x[i]]=1;//等会要排掉重要边缩点 
	}
	rep1(i,1,m) if(!vis[i]) merge(u[i],v[i]);//排掉重要边建立并查集 
	rep1(i,1,k)
	{
		//缩完点后记录每个点的能直接到达点的数量 
		int a=find(u[x[i]]),b=find(v[x[i]]); 
		++out[a];
		++out[b];
	}
	rep1(i,1,n) if(out[i]&1) ++cnt;//有几个点的直接到达点数量为奇数 
	if(cnt<=2) puts("Yes");//不可能存在cnt=1的情况，故直接判断cnt<=2 
	else puts("No");
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

先考虑限制的边，只能走一次，说明存在欧拉回路，也就是度数为奇数的点只有 $0$ 个或者 $2$ 个。

在考虑没有限制的点，因为是无向图，所以联通的无向边可以随便走，相当于一个大点。

于是考虑缩点，把有限制的边去掉，剩下的联通块缩成一个点，再加回有限制的边，用上面的方法判断欧拉回路是否存在。

并查集缩点，时间复杂度 $O((n + m) \log (n + m))$。

```cpp
#include<bits/stdc++.h>
//#define int long long
//#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 2e5+114;
int fa[maxn];
int found(int u){return fa[u]==u?u:fa[u]=found(fa[u]);}
struct Node{
	int u,v,flag;
}edge[maxn];
void merge(int u,int v){
	u=found(u),v=found(v);
	fa[u]=v;
}
int d[maxn],flag[maxn];
int n,m,k;
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>n>>m;
for(int i=1;i<=n;i++) fa[i]=i;
for(int i=1;i<=m;i++){
	int u,v;
	cin>>edge[i].u>>edge[i].v;
}
cin>>k;
for(int i=1;i<=k;i++){
	int x;
	cin>>x;
	flag[x]=1;
}
for(int i=1;i<=m;i++){
	if(flag[i]==0) merge(edge[i].u,edge[i].v);
}
for(int i=1;i<=m;i++){
	if(found(edge[i].u)!=found(edge[i].v)) d[found(edge[i].u)]++,d[found(edge[i].v)]++;
}
int cnt=0;
for(int i=1;i<=n;i++){
	if(fa[i]==i){
		if(d[i]%2==1) cnt++;
	}
}
cout<<((cnt==0||cnt==2)?"Yes\n":"No\n");
return 0;
}

```


---

## 作者：Alexandr (赞：0)

##  problem description 

有一张 $n$ 个点 $m$ 条边的无向连通图,已知 $k$ 条边为关键边,需要经过每条关键边恰好一次,非关键边无限制,判断能否满足条件。

------
解题思路

我们可以把所有关键边切断,整个图就变成了若干个连通块,然后我们知道非关键边的边可以无限走，那么我们就可以抽象地把这个连通块视为一个点。

执行以上操作后就整个图就变成了由关键边组成的一个无向图,整个问题就变成了让我们找一条路走完所有条边,且每条边都只走了 $1$ 次。这个就是欧拉路径问题了,如果有 $0$ 或 $2$ 个度数为奇数的点,则输出```Yes```,否则输出```No```。

至于怎么求出连通块的度数,我们只需要用一个并查集来维护即可。

上代码！

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl;
typedef double db;
const int N=2e5+10;
int n,m,k,vis[N],du[N],u[N],v[N],fa[N],ans;
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
int find(int x)
{
	if(x==fa[x]) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return;
	fa[y]=x; du[x]+=du[y];
} 
int main()
{
	n=read();m=read();
	_rep(i,1,n) fa[i]=i;
	_rep(i,1,m)
	{
		u[i]=read();v[i]=read();
		du[u[i]]++;du[v[i]]++;
	}
	k=read();
	_rep(i,1,k) vis[read()]=true;
 	_rep(i,1,m) if(!vis[i]) merge(u[i],v[i]);
 	_rep(i,1,n) if(fa[i]==i) ans+=(du[i]%2);
 	if(ans<=2) printf("Yes\n");
	else printf("No\n");
	return 0;
}

```


---

## 作者：Galex (赞：0)

先考虑 $S=E$（$E$ 表示图的所有边组成的集合，即全部边都只能恰好经过一遍）的情况：就是一个一笔画问题，结论为当且仅当有 $0$ 个或者 $2$ 个奇点（即度数为奇数的点）才能一笔画完。

那么当 $S \not= E$ 的时候，我们可以先把 $S$ 从 $E$ 中删除，然后把剩下的连通块缩成一个点，就变成 $S=E$ 的情况了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

#define N 200005
#define M 400005

int n, m;
int to[M], nxt[M], head[N], tot = 1;
bool f[N] = {0};

void add(int u, int v) {
	to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
}

int col[N], cnt = 0;
int deg[N];

void dfs(int p, int fa) {
	col[p] = cnt;
	for (int i = head[p]; i; i = nxt[i])
		if (to[i] != fa && !col[to[i]] && !f[i >> 1])
			dfs(to[i], p);
}

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	int k = read();
	while (k--)
		f[read()] = true;
	for (int i = 1; i <= n; i++)
		if (!col[i])
			cnt++, dfs(i, 0);
	for (int i = 1; i <= n; i++)
		for (int j = head[i]; j; j = nxt[j])
			if (f[j >> 1] && i < to[j])
				deg[col[i]]++, deg[col[to[j]]]++;
	int res = 0;
	for (int i = 1; i <= cnt; i++)
		if (deg[i] & 1)
			res++;
	printf(res <= 2 ? "Yes" : "No");
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：0)

# [ABC286G-Unique Walk](https://atcoder.jp/contests/abc286/tasks/abc286_g)

题意：有一张 $n$ 个点 $m$ 条边的无向图，已知 $k$ 条边为关键边，需要经过恰好一次，能否满足条件。

题解：缩点包治百病（不是），在这题大有作用。

因为非关键边不限次数，所以对于所有非关键边所连接的点集缩成一个强联通分量。这里可以使用并查集计算。

然后发现这张图只剩下关键边了。

现在就要求遍历所有边恰好一次。

于是求解欧拉通路可行性就搞定啦。

```cpp
const I N=2e5+10;
I ey[N],ex[N],n,m,k,f[N],cnt,d[N];
bool b[N];
I getf(I x){
	return x==f[x]?x:f[x]=getf(f[x]);
}int main(){
	in(n,m);
	for(I i=1;i<=n;++i)f[i]=i;
	for(I i=1;i<=m;++i)in(ex[i],ey[i]);
	in(k);
	for(I i=1,x;i<=k;++i)in(x),b[x]=1;
	for(I i=1;i<=m;++i)if(!b[i])f[getf(ex[i])]=getf(ey[i]);
	for(I i=1;i<=n;++i)f[i]=getf(i);
	for(I i=1;i<=m;++i)if(b[i]){
		++d[getf(ex[i])];
		++d[getf(ey[i])];
	}for(I i=1;i<=n;++i)if(d[i]&1)++cnt;
	if(cnt>2)puts("No");
	else puts("Yes");
	return 0;
}

```

---

