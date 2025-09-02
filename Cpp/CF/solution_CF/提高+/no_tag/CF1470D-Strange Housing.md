# Strange Housing

## 题目描述

Students of Winter Informatics School are going to live in a set of houses connected by underground passages. Teachers are also going to live in some of these houses, but they can not be accommodated randomly. For safety reasons, the following must hold:

- All passages between two houses will be closed, if there are no teachers in both of them. All other passages will stay open.
- It should be possible to travel between any two houses using the underground passages that are open.
- Teachers should not live in houses, directly connected by a passage.

Please help the organizers to choose the houses where teachers will live to satisfy the safety requirements or determine that it is impossible.

## 说明/提示

The picture below shows the second example test.

 ![](https://espresso.codeforces.com/a897ddb7078dd022b869fc31de83d3960c42a931.png)

## 样例 #1

### 输入

```
2
3 2
3 2
2 1
4 2
1 4
2 3```

### 输出

```
YES
2
1 3 
NO```

## 样例 #2

### 输入

```
1
17 27
1 8
2 9
3 10
4 11
5 12
6 13
7 14
8 9
8 14
8 15
9 10
9 15
10 11
10 15
10 17
11 12
11 17
12 13
12 16
12 17
13 14
13 16
14 16
14 15
15 16
15 17
16 17```

### 输出

```
YES
8
1 3 4 5 6 9 14 17```

# 题解

## 作者：gyh20 (赞：15)

染色。

如果不连通则无解。

首先，我们随便拿出来一个生成树，然后按 dfs 序染色，如果周围没有已经选择的点就选择当前点。

为什么这样是对的呢？

在过程中，我们其实保证了图的连通，其实是在 dfs 中保证了任意的已访问的 $i$ 与父亲连通，初始没有点，满足要求，在 dfs 的过程中：

若选择了 $i$ 或 $fa_i$，则一定连通，否则若都不能选，则说明都与之前的点连通，所以这两个点依然连通。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,head[600002],cnt,vis[300002],fa[300002],d[300002],v[300002],f[300002];
inline int root(re int x){return x==fa[x]?x:fa[x]=root(fa[x]);}
struct edge{int to,next;}e[600002];
inline void add(re int x,re int y){
	e[++cnt]=(edge){y,head[x]};
	head[x]=cnt,++d[x];
}
inline void dfs(re int x,re int y){
	f[x]=y;
	for(re int i=head[x];i;i=e[i].next)if(!f[e[i].to])dfs(e[i].to,x);
}
inline void dfs1(re int x,re int y){
	re bool ia=1;
	for(re int i=head[x];i;i=e[i].next)if(vis[e[i].to])ia=0;
	if(ia)vis[x]=1;
	for(re int i=head[x];i;i=e[i].next)if(f[e[i].to]==x)dfs1(e[i].to,x);
}
int main(){
	t=read();
	while(t--){
		n=read(),m=read(),cnt=0;
		for(re int i=1;i<=n;++i)fa[i]=i,head[i]=vis[i]=d[i]=v[i]=f[i]=0;
		for(re int i=1,x,y;i<=m;++i)x=read(),y=read(),add(x,y),add(y,x),fa[root(x)]=root(y);
		re bool ia=1;
		for(re int i=1;i<=n;++i)if(root(i)^root(1))ia=0;
		if(!ia){
			puts("NO");
			continue;
		}
		f[1]=1,dfs(1,1),dfs1(1,1);
		puts("YES");
		re int s=0;
		for(re int i=1;i<=n;++i)s+=vis[i];
		printf("%d\n",s);
		for(re int i=1;i<=n;++i)if(vis[i])printf("%d ",i);
		puts("");
	}
}


```


---

## 作者：7KByte (赞：4)

想了一个更简单的方法。

我们可以用归纳法。

对于前 $n-1$ 个点，如果我们构造出了一种方案，那么现在考虑加入第 $n$ 个点，如果与第 $n$ 个点连边的点有一个染了色，那么当前点就不需要染色，否则当前点必定染色。

$n=1$ 时，这个点是否染色都是合法，所以我们依次加入每个点即可，时间复杂度 $\mathcal{O}(N)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 300005
using namespace std;
int n,m,v[N],h[N],tot,in[N];
struct edge{int to,nxt;}e[N<<1];
void add(int x,int y){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;}
queue<int>q;
void solve(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)h[i]=0,v[i]=~0,in[i]=0;tot=0;
	rep(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	while(!q.empty())q.pop();
	v[1]=in[1]=1;q.push(1);
	while(!q.empty()){
		int x=q.front();q.pop();
		bool flag=true;
		for(int i=h[x];i;i=e[i].nxt)if(~v[e[i].to])flag&=!v[e[i].to];
		v[x]=flag;
		for(int i=h[x];i;i=e[i].nxt)if(!in[e[i].to])in[e[i].to]=1,q.push(e[i].to);
	}
	rep(i,1,n)if(!in[i]){puts("NO");return ;}
	puts("YES");int sum=0;
	rep(i,1,n)sum+=v[i];
	printf("%d\n",sum);
	rep(i,1,n)if(v[i])printf("%d ",i);putchar('\n');
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：1)

图不连通肯定不满足条件。下面的分析均基于“图连通”这一条件。

考虑在图中任意选择一棵生成树 $T$，并对其在满足 $1$ 条件的情况下，按照 dfs 顺序贪心的让当前访问到的结点尽可能的上色。此时只需要想办法让其满足 $2$ 条件。然后可以惊喜的发现此时这个生成树上不存在一条边 $u\Leftrightarrow v$，使得 $u,v$ 均未上色。也就是说删除之后生成树 $T$ 仍然不会发生变化。此时图一定仍然连通。于是做完了，时间复杂度 $O(n)$。

[AC Code](https://codeforces.com/contest/1470/submission/299255533)。

---

## 作者：wangyibo201026 (赞：1)

## solution

首先我们钦定 $1$ 为染色了，$-1$ 为没被染色，$0$ 表示没有处理到这个点。

首先很正常的思路是随便拎出一棵生成树，然后在上面跑黑白染色。但是我们发现此时会有很多返祖边，比较搞心态。

分类讨论是不可能分类讨论的，我们考虑直接暴力做：

- 对于一个点，初始先给它染上色，如果周围有不合法的，那么直接不染色。

考虑为什么这个是对的。

我们默认当且处理到 $x$ 时连通 $1$ 到 $x$，那么我们在处理 $v$ 的时候，只可能有两种情况：

- $v$ 没别染色，则可以被周围任意一个染色过的格子连通。
- $v$ 被染色，则可以与 $x$ 相连与 $1$ 连通。

于是，我们这样暴力做就是对的了。

---

## 作者：LCat90 (赞：1)

直接模拟整个过程，假设已经考虑了 $n-1$ 个点，当前加入第 $n$ 个点。

如果 $n$ 和之前染色的点有连边，那么他一定不能染色了。

如果不存在连边，那么就将它染色。

但是这样时间是 $O(n^2)$ 的。

其实，我们跑 DFS 树，到一个点的时候判断周围是否有染色就好了，最后再输出。时间复杂度为 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 3e5 + 5;
int n, m, T, ans, sum, dep[N], Fa[N];
bool vis[N], sb[N];
vector <int> G[N];
vector <int> tree[N];
void dfs(int x, int fa) {
	bool flag = 1; ++sum; 
	for(auto to : G[x]) if(vis[to]) flag = 0;
	vis[x] = flag; sb[x] = 1;
	for(auto to : G[x]) {
		if(to == fa) continue ;
		if(sb[to]) 	continue ;
		dfs(to, x);
	}
}
signed main() {
	cin >> T;
	while(T--) {
		cin >> n >> m;
		for(int i = 1;i <= n; ++i) G[i].clear(), vis[i] = sb[i] = 0;
		for(int i = 1, x, y;i <= m; ++i) {
			cin >> x >> y;
			G[x].pb(y), G[y].pb(x);
		} ans = sum = 0;
		dfs(1, 0);  
		if(sum < n) {
			puts("NO");
			continue ;
		}	
		puts("YES"); 
		for(int i = 1;i <= n; ++i) ans += vis[i];
		cout << ans << "\n";
		for(int i = 1;i <= n; ++i) if(vis[i]) cout << i << " ";
		puts("");
	}
	return 0;
}
/*

*/
```

---

## 作者：Resurgammm (赞：1)

$update:$ 增加了 $\text{Reference}$

首先原图若不连通，那么一定无解。

若连通，考虑归纳法。

不妨设一定有解，那么 $n=1$ 时显然成立，假设 $n=k-1$ 时成立，欲证明 $n=k$ 成立。

现将图中的一个非割点 $u$ 删掉，然后设剩下的连通图中的点集为 $S'$，进行分类讨论：

* 若 $S'$ 中有与 $u$ 相连的点，那么 $S=S'$ 成立。

* 若 $S'$ 中没有与 $u$ 相连的点，那么 $S=S'\cup \{u\}$ 成立。

模拟这个过程即可。

然后注意每次找非割点的复杂度会爆炸，但只要按任意 DFS 序加入便每次都是非割点。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		if(x<0) putchar('-'),x=-x;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(x,y,sizeof(y))
	
	const int maxn=3e5+5;
	
	int T,n,m,tim,ans;
	int dfn[maxn],uid[maxn];
	bool vis[maxn],col[maxn];
	namespace Graph{
		int head[maxn],id;
		struct e{int v,next;}edge[maxn<<1];
		inline void add(int u,int v){
			edge[++id].v=v;
			edge[id].next=head[u];
			head[u]=id;
		}
	}using namespace Graph;
	void dfs(int u){
		vis[u]=1;
		dfn[u]=++tim,uid[tim]=u;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v;
			if(vis[v]) continue;
			dfs(v);
		}
	}
	inline void init(int n,int m){
		for(int i=1;i<=n;i++) head[i]=dfn[i]=uid[i]=0,vis[i]=col[i]=0;
		for(int i=1;i<=m;i++) edge[i]=(e){0,0};
		id=tim=ans=0;
	}

	inline int main(){
		T=read();
		while(T--){
			n=read(); m=read();
			for(int i=1;i<=m;i++){
				int x=read(),y=read();
				add(x,y),add(y,x);
			}
			dfs(1); bool flag=0;
			for(int i=1;i<=n;i++) if(!vis[i]){puts("NO"); flag=1; break;}
			if(flag){init(n,m); continue;}
			puts("YES");
  			for(int i=1;i<=tim;i++){
				int u=uid[i]; bool flag=1;
				for(int j=head[u];j;j=edge[j].next){
					int v=edge[j].v;
					if(col[v]){flag=0; break;}
				}
				if(flag) col[u]=1;
			}
			for(int i=1;i<=n;i++) if(col[i]) ans++;
			printf("%d\n",ans);
			for(int i=1;i<=n;i++) if(col[i]) printf("%d ",i); puts("");
			init(n,m);
		}	
		return 0;
	}
}
signed main(){return CL::main();}
```

 ## $\text{Reference}$
 
 $2021$ 国家集训队论文 《信息学竞赛中构造题的常用解题方法》—蒋凌宇

---

## 作者：zhaocy (赞：1)

##### 解题思路：

由于本题没有要求回答最大/最小数量，于是成为一道构造性题目。

看到删边，又看到保证联通，于是想到生成树相关。

假如有一棵生成树，最显然的做法就是按层分类，一层染，一层不染。

但这时会出现几条边，其两端都被染色，不合题意。

改进一下这个过程，不妨假设以1号节点开始 dfs ，如果当前点**未被判断染或不染**，就将其**染色**，

然后**马上**把与被染色的点相连的所有未被染色的点全部**确定为不染**（符合翻译中的条件1）。

不管**当前点**有没有被染色，选择其中的与当前点相连的未被访问过的点，递归下去。

如果图不连通，输出 NO

否则这样一定能遍历整张连通图。

如果语言表述有不详尽的地方，请参见代码。

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm> 
#include<cmath>
using namespace std;
const int maxn=3e5+5;
const int maxm=3e5+5;
int T,n,m,vis[maxn],sum,ans[maxn];               //vis: 0未访问  1涂色  2不涂色 
bool book[maxn];
int p[maxn],ept;    
struct Edge{int to,next;}E[2*maxm];
void add(int x,int y){
	ept++,E[ept].next=p[x];
	p[x]=ept,E[ept].to=y; 
}
void dfs(int u){
	book[u]=1;
	if(!vis[u]){
		vis[u]=1,ans[++sum]=u;
		for(int i=p[u],v;i!=-1;i=E[i].next){
			v=E[i].to;
			if(vis[v])continue;
			vis[v]=2; 
		}
	}
	for(int i=p[u],v;i!=-1;i=E[i].next){
		v=E[i].to;
		if(book[v]==0)dfs(v);
	}
}
void init(){
	ept=sum=0;
	for(int i=1;i<=n;i++)
		ans[i]=book[i]=vis[i]=0,p[i]=-1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		init();
		int u,v,flag=0;
		for(int i=1;i<=m;i++){
			scanf("%d%d",&u,&v);
			add(u,v),add(v,u);
		}
		dfs(1);
		for(int i=1;i<=n;i++)
			if(vis[i]==0){flag=1;break;}
		if(flag){printf("NO ");}
		else{
			printf("YES\n%d\n",sum);
			sort(ans+1,ans+sum+1);
			for(int i=1;i<=sum;i++)
				printf("%d ",ans[i]);
		}	
		printf("\n");
	}
	return 0;
}
```

###### ~~如果对您有帮助，求赞。~~



---

## 作者：lfxxx (赞：0)

不联通一定无解。

否则去 dfs 并染色，这样构造一定有解。

不妨在 dfs 的过程中归纳证明：被 dfs 过的节点一定与 $1$ 联通。

假设当前点颜色为 $1$，其拓展出去的点不染色，但是一定可以通过当前点与 $1$ 联通。

否则拓展出去的点邻域中假若已经有了被染色的点则可以通过其与 $1$ 联通，否则就会将拓展出去的点染色，则可以通过当前点与 $1$ 联通。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+114;
int col[maxn],vis[maxn];
vector<int> vec,E[maxn];
int cnt,n,m;
void dfs(int u){
    col[u]=1;
    vis[u]=1;
    cnt++;
    for(int v:E[u]){
        if(vis[v]==1&&col[v]==1) col[u]=0;
    }
    if(col[u]==1) vec.push_back(u);
    for(int v:E[u]){
        if(vis[v]==0) dfs(v);
    }
}
void work(){
    cin>>n>>m;
    cnt=0;
    for(int i=1;i<=n;i++) E[i].clear(),vis[i]=col[i]=0;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1);
    if(cnt==n){
        cout<<"YES\n";
        cout<<vec.size()<<'\n';
        for(int x:vec) cout<<x<<' ';
        cout<<'\n';
        vec.clear();
    }else{
        cout<<"NO\n";
        vec.clear();
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--) work();
    return 0;
}

```

---

## 作者：phil071128 (赞：0)

### CF1470D Strange Housing

> 给定一个无向图，你要找到一个独立集，对于一条边，如果 $u,v$ 都不在独立集里，则删去这条边。
>
> 求满足删完后原图仍联通的独立集。$n\le 10^5$。

先把原图不联通的情况判掉。

对于类似独立集/匹配染色的构造题，我们可以先从**二分图**入手，从特殊情况启发得到正解。

如果原图是二分图，那么我们随便选一侧的点染色，显然正确。我们假定对所有左部点染色。

现在考虑原图不是二分图的情况，在二分图且已经染完色的基础上，左部和右部的点之间都有边，但如果左部有边是不合法的，我们就调整二分图，使得左部的点之间都无边，而对于右部内部的边，删掉显然是不影响连通性的。

那我们维护构造左部的过程即可，先随便放一个点进去，将其相连的点都从左部待选点移出，再判断这些点相连的点是否仍在左部待选点里，如果是就放左部，否则放右部。可以发现，这样构造一定能结束。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=3e5+500;
vector<int>s[N];
int lft[N],vis[N];
void dfsR(int x);
void dfsL(int x) {
	vis[x]=1;
	for(int y:s[x]) {
		lft[y]=1;
		
	}
	for(int y:s[x]) {
		dfsR(y);
	}
}
vector<int>ans;
void dfsR(int x) {
	vis[x]=1;
	for(int y:s[x]) {
		if(lft[y]==0) ans.push_back(y),lft[y]=1,dfsL(y);
	}
}
void work() {
	int n=read(),m=read();
	for(int i=1;i<=n;i++) {
		s[i].clear();vis[i]=lft[i]=0;
	}
	ans.clear();
	for(int i=1;i<=m;i++) {
		int u=read(),v=read();s[u].push_back(v);s[v].push_back(u);
	}
	lft[1]=1;
	ans.push_back(1);
	dfsL(1);
	for(int i=1;i<=n;i++) {
		if(vis[i]==0) return puts("NO"),void();
	}
	puts("YES");
	cout<<ans.size()<<endl;
	for(int x:ans) {
		cout<<x<<" ";
	}
	cout<<"\n";
}
int main(){
//	fil();
	int T=read();
	while(T--) work();	
	return 0;
}

```


实际上，如果不从二分图的角度，而是站在**归纳法**上看，或许更为清晰：

对于 $n=1$，染色即可。

对于 $n>1$，前 $n-1$ 个点是一个合法的方案（连通图），我们希望加进 $n$，如果 $n$ 相连的点全部没染色，则 $n$ 必须染色，否则存在一个相连的点染色，那么 $n$ 就必须不能染色。显然这样也一定会结束并构造成功。

---

## 作者：Muse_Dash (赞：0)

显然，两种颜色染色可以想到建任意一个生成树，对于 $\texttt{dfs}$ 序排序并按这个顺序讨论，每次讨论到一个节点，如果其周围的节点都没有被染色，就把它染色。

注意非树边的条件也要满足，所以判断周围的点是否染色也要考虑非树边相连的点。

---

## 作者：ListenSnow (赞：0)

### 思路

假设当前已经将一个大小为 $k$ 的点集合法染色。考虑将点 $i$ 加入到点集中。

如果点集中存在一个点 $j$，满足点 $j$ 与点 $i$ 有边直接相连，且点 $j$ 被染色了，那么直接将点 $i$ 加入点中，仍然合法；

若点集中不存在这样的点 $j$，那么将点 $i$ 染色后加入点集中，仍然合法。

按照这样的步骤逐步扩大点集，如果原图联通，那么必定有解。

同时为了保证新枚举的点与点集中的点有边直接相连，可以按照 dfs 序枚举图上的所有点。

### code：
```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=3e5+10,M=6e5+10;
int h[N],tot,cnt,n,m,idx,q[N];bool vis[N],col[N];
struct edge{int v,nex;}e[M];
void add(int u,int v){e[++idx]=edge{v,h[u]};h[u]=idx;}
void dfs(int u)
{
	vis[u]=true,cnt++;bool used=0;
	for(int v,i=h[u];i;i=e[i].nex) if(vis[v=e[i].v]) used|=col[v];col[u]=used^1;tot+=col[u];
	for(int v,i=h[u];i;i=e[i].nex) if(!vis[v=e[i].v]) dfs(v);
}
void solve()
{
	scanf("%d%d",&n,&m);for(int i=1;i<=n;i++) h[i]=col[i]=vis[i]=0;idx=tot=cnt=0;
	for(int u,v,i=1;i<=m;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);dfs(1);
	if(cnt<n) return puts("NO"),void();puts("YES");printf("%d\n",tot);
	for(int i=1;i<=n;i++) if(col[i]) printf("%d ",i);puts("");
}
int main()
{
	int T;scanf("%d",&T);while(T--) solve();
	return 0;
}
```

---

## 作者：fanfansann (赞：0)

# F - Strange Housing

**Problem F Strange Housing**

给定一个 $n$ 个节点，$m$ 条无向边的图，现在你要给一些点染色，使得：

- 一条边所连接的两个点不能都被染色。
- 在所有连接两个不被染色的点的边都被删除的情况下，这个图满足任意两个点互相可达。

如果有染色方案满足上述要求，输出一行 `YES` 之后输出要染色的点的数量，并升序输出所有被染色的点的编号;否则输出一行 `NO`。

$T$ 组数据。

$1\leq T\leq 10^5;2\leq n\leq 3\times10^5;0\leq m\leq 3\times10^5.$

$\sum n,\sum m\leq 3\times10^5$

**Solution**

又是一个非常简单的题目 ~ 很明显，如果图是一个连通图的话，很明显他一定可以满足题目中的条件，因为一个连通图一定存在一个生成树，那么树的点，染色法，一层染，一层不染，一定能构造出来一种答案。所以我们只需要去判断图是否连通，不连通那肯定为 `No`。

所以我们可以直接使用并查集来判断是否为连通图，然后用 $dfs$ 染色即可。染色的时候，我们对于当前点，如果没有被遍历过，就给他染上色，然后对于他的所有邻点，都判断一下是否被同时染色，如果有一个点在它之前被染上色了，那就把它自己染上的色去掉，因为我们大不了就把这条边删掉，而点是一定不能同色的，原来的点已经确定好了不能改，当前点可以改，因为当前点染色也是试的 ~ 

判断完染色的正确性以后，再对于所有的没有遍历过的子节点，dfs重复上述动作即可。至于升序输出点的编号，我们只需要从小到大枚举即可。

**Code**

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;
const int N = 5000007, M = 5000007, mod = 1e9 + 7;
typedef long long ll;
typedef int itn;
int res;
int n, m, k, t;
int head[N], ver[M], nex[M], tot;
int vis[N], col[N], fa[N];

void add(int x, int y)
{
    ver[tot] = y;
    nex[tot] = head[x];
    head[x] = tot ++ ;
}

int Find(int x)
{
    if(fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}

void dfs(int x, int father)
{
    vis[x] = 1;
    col[x] = !col[father];

    for(int i = head[x]; ~i; i = nex[i]) {//先确定完
        int y = ver[i];
        if(vis[y]) {
            if(col[y]) col[x] = 0;
        }
    }
    for(int i = head[x]; ~i; i = nex[i]) {//再走
        int y = ver[i];
        if(vis[y] == 0 && y != father) {
            dfs(y, x);
        }
    }
}

int main()
{
    scanf("%d", &t);
    while(t -- ) {
        tot = 0;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++ i) {
            vis[i] = 0, fa[i] = i;
            head[i] = -1, col[i] = 0;
        }
        int cnt = n;
        for(int i = 1; i <= m; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            add(x, y);
            if(Find(x) != Find(y)) {
                cnt -- ;
                fa[Find(x)] = fa[y];
            }
            add(x, y), add(y, x);
        }
        if(cnt != 1) {//连了 n-1 次就是一棵树
            puts("NO");
            continue;
        }
        puts("YES");
        dfs(1, 0);
        cnt = 0;
        vector<int> ans;
        for(int i = 1; i <= n; ++ i) {
            if(col[i]) {
                ans.push_back(i);
                cnt ++ ;
            }
        }
        printf("%d\n", cnt);
        for(auto x : ans)
            printf("%d ", x);
        puts("");
    }
    return 0;
}

```



---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1470D)

&nbsp;

### 题目大意：
给定一个有 $n$ 个点和 $m$ 条边的无向图，选取 $n-1$ 条边，使这张图成为一棵树，随后对这棵树黑白染色，需要保证染为黑色的点在原图中**互不相连**，最后输出染黑的点数和点的编号。

&nbsp;

### 解题思路
考虑直接从 $1$ 开始 `bfs` 对原图黑白染色，然后在过程中对于同黑的点进行处理，

不难发现的是，由于 `bfs` 是按照点到起始点的距离分层搜索，所以出现颜色冲突（也就是出现两个在先前被染黑的点间有连边）的两个点到原点的距离必然相等。

正确性是显然的，因为如果这两点到原点的距离不同，同时之间又有连边的话，那它们到原点的距离**必然也就只差 $1$**，而相邻层之间的颜色又必然不相同，于是可以得出这两个点必然是处在同一层的。

同时可以证明对于发生颜色冲突的两点，必然又一个还没有向下搜索，于是便可以更改还未搜索过的点的颜色，这时就相当于把这个点到原点的路径改变，但**并不会影响连通性。**

&nbsp;

```cpp
void bfs(){
	q[l]=1;
	vis[1]=1;
	while(l<=r){
		int u=q[l++];
		int siz=edge[u].size();
		for(int i=0;i<siz;i++){
			int v=edge[u][i];
			if(vis[v]==vis[u]&&vis[u]==1) vis[v]=vis[u]%2+1;//改变颜色
			if(vis[v]) continue;
			vis[v]=vis[u]%2+1;
			q[++r]=v;
		}
	}
}

int main(){    
	while(t--){
		for(int i=1;i<=n;i++){//初始化数组
			vis[i]=0;
			edge[i].clear();
		}
		scanf("%d%d",&n,&m);

		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		
		bfs();
		int cnt=0;
		for(int i=1;i<=n;i++){//判断连通性，同时记录染色点
			if(!vis[i]){
				cnt=0;
				break;
			} 
			if(vis[i]==1) ans[++cnt]=i;
		}
		
		if(cnt==0) printf("NO\n");
		else{
			printf("YES\n%d\n",cnt);
			for(int i=1;i<=cnt;i++){
				printf("%d ",ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
```
**完结撒花 OvO**

---

