# Wonderful Tree!

## 题目描述

God's Blessing on This ArrayForces!

A Random Pebble



You are given a tree with $ n $ vertices, rooted at vertex $ 1 $ . The $ i $ -th vertex has an integer $ a_i $ written on it.

Let $ L $ be the set of all direct children $ ^{\text{∗}} $ of $ v $ . A tree is called wonderful, if for all vertices $ v $ where $ L $ is not empty, $ $$$a_v \le \sum_{u \in L}{a_u}. $ $  In one operation, you choose any vertex  $ v $  and increase  $ a\_v $  by  $ 1 $ .</p><p>Find the minimum number of operations needed to make the given tree <span class="tex-font-style-it">wonderful</span>!</p><div><p> $ ^{\\text{∗}} $  Vertex  $ u $  is called a direct child of vertex  $ v $  if: </p><ul> <li>  $ u $  and  $ v $  are connected by an edge, and </li><li>  $ v $  is on the (unique) path from  $ u$$$ to the root of the tree.

## 说明/提示

The tree in the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987E/2f38988a6330d33a37c9c3428488c52df188849b.png)You can apply the operation once on vertex $ 5 $ and twice on vertex $ 2 $ to get a wonderful tree.

In the second test case, you can apply the operation twice on vertex $ 2 $ to get a wonderful tree.

In the third and fourth test cases, the tree is already wonderful, so you don't need to apply any operations.

## 样例 #1

### 输入

```
4
5
9 3 4 1 2
1 1 3 3
2
5 3
1
2
36 54
1
3
0 0 0
1 2```

### 输出

```
3
2
0
0```

# 题解

## 作者：小木虫 (赞：13)

### Preface  
提供一种比较小众但是不太动脑子的做法。  
### Problem  
给你一棵 $n$ 个点的有根树 $T$，点有点权 $a$，你可以通过一次操作增加一个点的点权，要求对于所有的非叶子节点 $u$：  
$$a_u\leq \sum_{v\in son_u}a_v$$  
其中 $son_u$ 代表 $u$ 在**有根**树中的儿子集合。   
问使树合法的最小操作次数。  
$2\leq n\leq 5000,0 \leq a_i\leq 10^9$。  
### Solution
我们把柿子变动一下，设：  
$$b_u=a_u-\sum_{v\in son_u}a_v$$  
则我们要让所有非叶子的 $b$ 都小于等于 $0$。  
考虑一次对 $u$ 的操作会对 $b$ 产生什么影响。  
显然会让 $b_u$ 加一，但是会让 $b_{fa}$（$fa$ 为 $u$ 的父亲）减一。  
这也可以理解为把一个地方的贡献挪到了父亲，花费为 $1$。  

\* $(a,b,c,d)$ 分别为一条边的起始点，终止点，流量限制，单位流量费用，$S$ 为源点，$T$ 为汇点。  
通过上述观察，我们可以建立费用流模型：  
对于每个非根节点 $u$：  
连边 $(u,fa,\inf,1)$。  
对于每个非叶子节点 $u$：  
若 $b_u < 0$，连边 $(S,u,-b_u,0)$。  
若 $b_u > 0$，连边 $(u,T,b_u,0)$。  
对于每个叶子节点 $u$：  
连边 $(S,u,\inf,0)$。  

直接跑费用流即为答案，分析可知单次增广复杂度为 $O(n)$，总增广次数为 $O(n)$，总体复杂度为 $O(n^2)$。

code：
```cpp
#include <bits/stdc++.h>
#define mp make_pair
#define fir first
#define sec second
#define int long long
using namespace std;
const int N=5010;
int T,n,a[N],p[N],b[N],dep[N];
vector <int> edge[N];int ans=0;
namespace MCMF{
	const int N=1e6+10;
	int n,s,t,head[N],to[N],nxt[N],f[N],c[N],cnt=-1;
	int maxflow,mincost;
	void add(int u,int v,int fl,int w){
		++cnt;
		nxt[cnt]=head[u];
		head[u]=cnt;to[cnt]=v;
		f[cnt]=fl;c[cnt]=w;
		++cnt;
		nxt[cnt]=head[v];
		head[v]=cnt;to[cnt]=u;
		f[cnt]=0;c[cnt]=-w;
	}
	int dis[N],vis[N],pre[N][2];
	void SPFA(){
		queue <int> Q;
		for(int i=0;i<=n;i++)
			dis[i]=1e9,vis[i]=0,pre[i][0]=pre[i][1]=0;
		Q.push(s);vis[s]=1;dis[s]=0;
		while(Q.size()){
			int u=Q.front();Q.pop();vis[u]=0;
			//cout<<u<<endl;
			for(int i=head[u];~i;i=nxt[i]){
				int v=to[i],w=c[i];
				//cout<<u<<" "<<v<<" "<<w<<" "<<f[i]<<endl;
				if(!f[i])continue;
				if(dis[v]>dis[u]+w){
					//cout<<"push: "<<endl;
					dis[v]=dis[u]+w;
					pre[v][0]=u;
					pre[v][1]=i;
					if(!vis[v]){
						Q.push(v);vis[v]=1;
					}
				}
			}
		}	
	}
	void solve(){
		mincost=0;maxflow=0;
		while(true){
			SPFA();
			//cout<<dis[t]<<endl;
			if(dis[t]==1e9)return;
			int minf=1e18,sumc=0,now=t;
			vector <int> path;
			while(now!=s){
				path.push_back(pre[now][1]);
				minf=min(minf,f[pre[now][1]]);
				sumc+=c[pre[now][1]];
				now=pre[now][0];
			}
			//cout<<minf<<endl;
			for(auto it:path){
				f[it]-=minf;
				f[it^1]+=minf;
			}
			maxflow+=minf;
			mincost+=minf*sumc;
			//cout<<maxflow<<" "<<mincost<<endl;
			//cout<<mincost<<"\n";
		}
	}
}
void solve(){
	cin>>n;ans=0;MCMF::cnt=-1;
	for(int i=0;i<=n+1;i++)MCMF::head[i]=-1;
	MCMF::s=0;MCMF::t=n+1;
	for(int i=1;i<=n;i++)
		cin>>a[i],edge[i].clear(),b[i]=a[i];
	for(int i=2;i<=n;i++)
		cin>>p[i],edge[p[i]].push_back(i);
	for(int i=1;i<=n;i++){
		if(edge[i].size()==0)continue;
		b[i]=a[i];
		for(auto j:edge[i])b[i]-=a[j];
	}
	MCMF::n=n+1;
	for(int i=2;i<=n;i++)
		MCMF::add(i,p[i],1e18,1);
	for(int i=1;i<=n;i++){
		if(edge[i].size()==0){
			MCMF::add(0,i,1e18,0);
			continue;
		}
		if(b[i]<0){
			MCMF::add(0,i,-b[i],0);
		}else if(b[i]>0){
			MCMF::add(i,n+1,b[i],0);
		}
	}
	MCMF::solve();
	cout<<MCMF::mincost<<"\n";
}	
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Rnfmabj (赞：10)

## CF1987E 题解

### 题意

给定一棵大小为 $n$ 的有根树，各点各有一点权 $a_i$。每次操作可以选定一节点使其点权加一，求最小的操作数，使得任一节点满足其点权不大于其所有儿子的点权之和。

$n \le 5000 ,0 \le a_i \le 10^9$

-----

### 题解

麻了，赛后十五分钟调出来，可惜为时已晚。

读懂题之后容易发现，题目最核心的地方在于当我们需要一个节点 $+1$ 时，如果这个节点刚好等于儿子的点权和，那么就意味着需要有一个儿子节点 $+1$ ；而这个儿子如果刚好等于其儿子的点权和，那就意味着它的儿子也有一个需要 $+1$，一直递归下去......直到某一节点点权严格小于其儿子的点权和，或者这个节点是叶子。

也就是说，如果一个节点需要 $+1$ ，那么需要操作的节点就是包含其自身往下一直延伸的一条链，到叶子或者点权严格小于儿子点权和的节点为止，代价即为这条链的长度。

那么我们就可以令 $b_v=(\sum_{u ∈ L}a_u)-a_v$ ，其中 $L$ 为点 $v$ 的子节点构成的集合。特别的，叶子节点的 $b$ 为无限。

对于新定义的权值 $b$ ，原题意就转化为：对任意节点 $v$，单次操作可以选定 $v$ 子树中除自己外任一节点 $u$ ，使$b_v=b_v+1,b_u=b_u-1$；操作的代价为 $u$ 到 $v$ 的距离。最小化使得所有节点 $v$ 满足 $0 \le b_v$ 的代价。

这是怎么来的呢？当我们按原题意操作了一条链时，注意到对链上除最深的节点也就是链尾之外，其他的节点权值与其儿子节点权值和之差保持不变；而链尾的这个差（也就是 $b$ ）缩小了 $1$，链首父亲的 $b$ 增加了 $1$。根据原题意，我们要的就是所有的节点的 $b$ 值不小于 $0$。

所以对于每个 $b < 0$ 的节点，我们只要贪心地先选深度小的且其 $b$ 值仍为正数的后代，扣它的 $b$ 值来填自己的，如果它的 $b$ 值不够填那就把它的 $b$ 值耗完再找下一个深度小的，不够再往下，反正叶子节点的 $b$ 是正无穷，只要有后代就一定能填上，只是代价大小的问题。容易证明这样贪心能使总代价最小——把深度浅的后代自己不拿去填，留给自己的父亲填不会更优。

具体实现就是在遍历过程中对每个节点维护其后代 $b$ 值尚可被~~压榨~~利用的点集，如果自身 $b>0$ 则向上合并点集时将自身纳入点集（容易证明自身一定是自己父亲利用的第一选择）；反之，则优先选择自身后代贡献的点集中深度较小的来填自身的 $b$ 值直到 $b=0$ 。容易发现我们需要在维护过程中保持这个点集是单调的，用归并即可。推荐用 `std::vector` 维护点集并按降序维护，因为将自身纳入点集时我们没有 `push_front()` 这个函数 。

归并帮我们在合并时压掉了一个 $\log n$ 的复杂度，但是由于树本身形状的不确定，失去了点分治中树重心那样优秀的性质，最终的时间复杂度仍然是 $O(n^2)$。

-----

```cpp
const ll maxn=5e3+5;
ll a[maxn],siz[maxn],dep[maxn];
ll b[maxn],ans;
ll n;
vector<ll>e[maxn];
void dfs(ll x){//预处理出 b 值
	siz[x]=1;
	b[x]=-a[x];
	for(auto v:e[x]){
		dep[v]=dep[x]+1;//标 dep 便于计算代价
		b[x]+=a[v];
		dfs(v);
		siz[x]+=siz[v];
	}
	if(siz[x]==1)b[x]=1ll<<31;//叶子的 b 值为正无穷
}
vector<ll>work(ll x){//返回的是点集
	vector<ll>lst;//自己的点集
	for(auto v:e[x]){
		vector<ll>res=work(v);
		vector<ll>tmp;
		ll l=0,r=0,len1=lst.size(),len2=res.size();
		while(l<len1||r<len2){//归并
			if(l==len1)tmp.push_back(res[r++]);
			else if(r==len2)tmp.push_back(lst[l++]);
			else if(dep[lst[l]]>dep[res[r]])tmp.push_back(lst[l++]);
			else tmp.push_back(res[r++]);
		}
		lst.swap(tmp);
	}
	if(b[x]>0)lst.push_back(x);//b>0 则放入自身
	else if(b[x]<0){
		ll p=lst.size()-1;//不用验空，b<0 其必有儿子，有儿子必有后代为叶子
		while(b[x]<0){
			ll it=lst[p];
			ll sum=min(-b[x],b[it]);//要么直接填满，要么把这个用完
			b[it]-=sum,b[x]+=sum;
			ans+=sum*(dep[it]-dep[x]);//代价
			if(b[it]==0)p--,lst.pop_back();//用完扔掉不然单调性没法保证
		}
	}
	return lst;//自身点集向上合并
}
void solve(){
	n=R;
	ans=0;//清多测
	for(ll i=1;i<=n;i++){
		a[i]=R;
		e[i].clear();//这里好一点的写法是用 tmp.swap(e[i]) 彻底释放空间
        //但由于题目保证了数据总和，抢时间就不写太麻烦了
	}
	for(ll i=2;i<=n;i++)e[R].push_back(i);
	dfs(1);
	work(1);
	we(ans);
	return ;
}
```

-----

赛时还是不要放弃啊，我要是中间没有开摆这题就有时间切掉了。

---

## 作者：ANDER_ (赞：4)

#### 考察：树形 DP、DFS、BFS。
## 题意
给定一棵有 $n$ 个节点的树，其根为 $1$，每个点的点权为 $a_i$。定义“好树”为对于任意节点 $u$，设其儿子结点点集为 $S$，都满足：$a_u \le \sum^{|S|}_{i =1}a_{S_i}$。

对于这棵树，每次操作可使任意结点的点权加一。求使这棵树变为“好树”所需的最少操作次数。共有 $t$ 组数据。

## 思路
对于所有节点 $v$，设其儿子结点点集为 $S$。

记 $b_v = \begin{cases}
\sum^{|S|}_{i = 1}(a_{S_i}) - a_v &{|S| > 0}\\
+∞ &{|S| = 0}\\
\end{cases}$

并设 $d_i$ 为结点 $i$ 的深度。故问题转化成使 $\bigwedge^n_{i = 1} (b_i > 0)\equiv T$ 的最小次数。

先从特殊情况开始考虑，设当前树以 $u$ 为根，且 $u$ 的子树均为“好树”，只有 $b_u < 0$。若结点 $u$ 的儿子 $b_v > 0$，那么 $b_u$ 每加一，操作一次，共操作 $b_v$ 次。若 $b_v$ 也小于 $0$。 就必须顺着树传递下去，对路径上的结点依次执行加一操作，直到找到结点 $v'$ 使得 $b_{v'} > 0$，需要操作的次数为 $d_{v'} - d_u$。因此要使得该树变成好树的最优方案就是按 $b_u$ 加一需要的代价从小到大遍历，直到 
$b_u = 0$。

考虑从叶结点向根结点遍历，这样每次操作都是上文所述的特殊情况。

时间复杂度：$O(\sum n^2)$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e3 + 5, INF = 1e9;
int t, n, ans, a[N], b[N];
inline void solve() {
	ans = 0;
	cin>>n;
	for(int i = 1 ; i <= n ; i ++) {
		cin>>a[i];
	}
	vector<int> edge[n + 5], d(n + 5, 0);
	for(int i = 2, x ; i <= n ; i ++) {
		cin>>x;
		edge[x].push_back(i);
		d[i] = d[x] + 1;
	}
	for(int i = 1 ; i <= n ; i ++) {
		if(edge[i].empty()) {
			b[i] = INF;
			continue;
		}
		b[i] = -a[i];
		for(auto j : edge[i]) {
			b[i] += a[j];
		}
	}
	for(int i = n ; i >= 1 ; i --) {
		queue<int> que;
		que.push(i);
		if(b[i] < 0) {
			while(!que.empty()) {
				int u = que.front();
				que.pop();
				for(auto v : edge[u]) {
					if(b[v] > 0) {
						int k = min(-b[i], b[v]);
						b[i] += k, b[v] -= k;
						ans += k * (d[v] - d[i]);
					}
					que.push(v);
				}
			}
		}
	}
	cout<<ans<<endl;
	return;
}
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	cin>>t;
	while(t --) {
		solve();
	}
	return 0;
}

```
2024.07.11 管理员大大，代码写炸了，现已改正，求过。

---

## 作者：Rain_chr (赞：2)

难以理解题目要求的复杂度仅仅只是 $O(n^2)$，不说别的，至少 $O(n\log^2 n)$ 的复杂度并不用脑子吧。

我们可以发现，如果 $x$ 需要修改，那么影响的是 $x$ 向下的一条链，链尾还有可以增加的空间，而我们可以贪心的希望这条修改的链长度最小。

所以我们可以用堆来维护可以向下修改的链。对于一条链，我们只需要记录链尾深度以及可以更改的空间，每次从堆中暴力取出深度最小的，如果当前节点需要增加的数字大于可以更改的空间，就先把这一条链榨干，然后删除。

运用启发式合并，总复杂度为 $O(n\log^2 n)$。

回过头结合题解区的费用流做法来看，维护的链其实就是维护的增广路，整个过程其实相当于是模拟费用流了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5010,inf=1e18;
struct node
{
    int dep;
    mutable int w;
    bool operator<(const node& y) const{
        return dep>y.dep;
    }
};
priority_queue<node> q[N];
int w[N],fa[N],d[N];
vector<int> a[N];
int ans=0;
void dfs(int x)
{
    d[x]=d[fa[x]]+1;
    if(a[x].empty()) 
    {
        q[x].push((node){d[x],inf});
        return ;
    }
    int k=0;
    for(int to:a[x])
    {
        dfs(to);
        if(q[to].size()>q[x].size()) swap(q[to],q[x]);
        while(q[to].size()) q[x].push(q[to].top()),q[to].pop();
        k+=w[to];
    }
    if(k>=w[x]) q[x].push((node){d[x],k-w[x]});
    else
    {
        k=w[x]-k;
        while(k>=q[x].top().w)
        {
            k-=q[x].top().w;
            ans+=(q[x].top().dep-d[x])*q[x].top().w;
            q[x].pop();
        }
        q[x].top().w-=k;
        ans+=(q[x].top().dep-d[x])*k;
    }
}
void run()
{
    while(q[1].size()) q[1].pop();
    ans=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) a[i].clear();
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=2;i<=n;i++) cin>>fa[i],a[fa[i]].push_back(i);
    dfs(1);
    cout<<ans<<'\n';
}
signed main()
{  
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) run();
	return 0;
}
```

---

## 作者：zjc5 (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1987E)

**思路：**

由 $a_v\le\sum\limits_{u\in L}{a_u}$ 可知 $a_v-\sum\limits_{u\in L}{a_u}\le0$。

因此，先把 $a_v$ 减去 $\sum\limits_{u\in L}{a_u}$。此时若某一 $a_u$ 加一，则 $a_v$ 减一。

从下向上处理，如果 $a_v>0$，则需要让 $a_u$ 累计加上 $a_v$。

但是 $a_u=0$ 时，若再让 $a_u$ 加一，则 $a_u$ 不合法，需再次处理。

容易发现这种操作会一直继续直到存在 $a_k<0$，此时将 $a_k$ 称为结束节点。

从 $a_v$ 操作到 $a_k$，$a_v$ 减一，中间的节点加一后又减一，相当于没操作，$a_k$ 加一，因此 $a_k$ 最多操作 $-a_k$ 次，每次代价为 $dep_k-dep_v$。

将 $a_u$ 中的加法转换为 $a_v$ 的子树中的结束节点的加法，取的结束节点必然是深度最小的。

将结束节点变为 $0$ 后，需要再取出它的子树中的结束节点，直到 $a_v=0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5010;
int T,n,p,f[N],dep[N];
long long a[N],inf=LLONG_MIN,ans;
vector<int>v[N];
typedef pair<int,int>pii;
set<pii>add(int now) {
	set<pii>q,q2;
	for(int i=0; i<v[now].size(); i++) {
		int t=v[now][i];
		if(t==f[now]) continue;
		if(a[t]<0) q.insert({dep[t],t});
		else {
			q2=add(t);
			q.insert(q2.begin(),q2.end());
		}
	}
	return q;
}
set<pii>dfs(int now,int fa) {
	f[now]=fa;
	dep[now]=dep[fa]+1;
	set<pii>q,q2;
	for(int i=0; i<v[now].size(); i++) {
		int t=v[now][i];
		if(t==fa) continue;
		a[now]-=a[t];
		q2=dfs(t,now);
		q.insert(q2.begin(),q2.end());
	}
	if(now!=1&&v[now].size()==1)
		a[now]=inf;
	if(a[now]<0) {
		q.clear();
		q.insert({dep[now],now});
	} else {
		while(a[now]>0) {
			pii k=*q.begin();
			int id=k.second;
			if(a[now]+a[id]>=0) {
				ans+=-a[id]*(k.first-dep[now]);
				a[now]+=a[id];
				a[id]=0;
				q.erase(k);
				q2=add(id);
				q.insert(q2.begin(),q2.end());
			}else{
				ans+=a[now]*(k.first-dep[now]);
				a[id]+=a[now];
				a[now]=0;
			}
		}
	}
	return q;
}
int main() {
	cin>>T;
	while(T--) {
		cin>>n;
		ans=0;
		for(int i=1; i<=n; i++)
			v[i].clear();
		for(int i=1; i<=n; i++)
			cin>>a[i];
		for(int i=2; i<=n; i++) {
			cin>>p;
			v[i].push_back(p);
			v[p].push_back(i);
		}
		dfs(1,0);
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：abruce (赞：2)

题外话：为什么这个题 $n$ 只有 $5000$ 啊，明明有不难想的 $O(n\log n)$ 做法。  
首先我们考虑进行 dp，对于一个子树我们可以知道对这个子树的根进行操作会有多种不同的代价（即操作的链延伸到哪里，由路径上点是否被填满决定）。我们肯定贪心选最小代价（因为即使将其留给祖先也一定不更优），所以我们维护每个点 $u$ 子树内可进行多少次代价为 $i$ 的操作，记其为 $f_{u,i}$。  
其转移非常方便。首先 $u$ 将其儿子的 $f$ 加起来，并平移一位（因要操作儿子必须操作 $u$）。如果 $u$ 没有达到儿子权值和 $sum$，那么 $u$ 可以进行 $sum-a_u$ 次代价为 $1$ 的操作。如果 $u$ 达到了 $sum$，那么就要根据 $f_u$ 来贪心将其补齐。如果暴力实现，那么 $O(n^2)$。  
考虑 $f$ 的主要转移是儿子 $f$ 之和以及平移一位，我们可以考虑用线段树合并维护。具体来说，将 $u$ 可以操作加在 $dep_u$ 的位置，就可以自动完成平移。而查询代价，则可以通过维护 $cnt$ 和 $\sum dep$，然后在线段树上二分完成。故可以维护，时间复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
namespace tokido_saya {
	#define lc(id) t[id].c[0]
	#define rc(id) t[id].c[1]
	const int maxn=2e5+5;
	struct tree
	{
		int c[2],tag;
		ll cnt,sum;
	}t[maxn*20];
	struct edge
	{
		int next,to;
	}e[maxn*2];
	int rt[maxn],n,cnt,tot,h[maxn],a[maxn],d[maxn],k;
	ll ans;
	void addedge(int x,int y)
	{
		e[++cnt].next=h[x],e[cnt].to=y,h[x]=cnt;
	}
	void adtag(int id)
	{
		if(!id)return;
		t[id].cnt=t[id].sum=0,t[id].tag=1;
	}
	void pushdown(int id)
	{
		if(!t[id].tag)return;
		adtag(lc(id)),adtag(rc(id)),t[id].tag=0;
	}
	void pushup(int id)
	{
		t[id].cnt=t[lc(id)].cnt+t[rc(id)].cnt,t[id].sum=t[lc(id)].sum+t[rc(id)].sum;
	}
	void add(int &id,int l,int r,int v,ll k)
	{
		if(!id)id=++tot,lc(id)=rc(id)=t[id].cnt=t[id].sum=t[id].tag=0;
		if(l==r)return t[id].cnt+=k,t[id].sum+=v*k,void();
		int mid=l+r>>1;
		pushdown(id);
		v<=mid?add(lc(id),l,mid,v,k):add(rc(id),mid+1,r,v,k);
		pushup(id);
	}
	int merge(int x,int y,int l,int r)
	{
		if(!x||!y)return x+y;
		t[x].cnt+=t[y].cnt,t[x].sum+=t[y].sum;
		if(l==r)return x;
		int mid=l+r>>1;
		pushdown(x),pushdown(y);
		lc(x)=merge(lc(x),lc(y),l,mid);
		rc(x)=merge(rc(x),rc(y),mid+1,r);
		pushup(x);
		return x;
	}
	void ask(int id,int l,int r,int v)
	{
		if(!id)return;
		if(v<=l&&k>=t[id].cnt)return /*cout<<k<<' '<<l<<' '<<r<<' '<<t[id].sum<<' '<<t[id].cnt<<"#\n",*/ans+=t[id].sum-1ll*t[id].cnt*v,k-=t[id].cnt,adtag(id),void();
		if(l==r)return /*cout<<k<<' '<<l<<' '<<v<<"*\n",*/ans+=1ll*k*(l-v),t[id].sum-=1ll*k*l,t[id].cnt-=k,k=0,void();
		int mid=l+r>>1;
		pushdown(id);
		if(v<=mid)ask(lc(id),l,mid,v);
		if(k)ask(rc(id),mid+1,r,v);
		pushup(id);
	}
	void dfs(int u)
	{
		ll sum=0;
		bool pd=0;
		for(int i=h[u];i;i=e[i].next)
		{
			int v=e[i].to;
			d[v]=d[u]+1,dfs(v),pd=1,sum+=a[v],rt[u]=merge(rt[u],rt[v],1,n);
		}
		if(!pd)return add(rt[u],1,n,d[u],1e9);
		if(a[u]<=sum)return add(rt[u],1,n,d[u],sum-a[u]);
//		cout<<u<<' '<<a[u]-sum<<"!\n";
		k=a[u]-sum,ask(rt[u],1,n,d[u]);
	}
	int main() {
		int T;
		T=read(),d[1]=1;
		while(T--)
		{
			n=read(),cnt=tot=ans=0;
			for(int i=1;i<=n;i++)a[i]=read(),h[i]=rt[i]=0;
			for(int i=2;i<=n;i++)addedge(read(),i);
			dfs(1);
			printf("%lld\n",ans);
		}
		return 0;
	}
}
int main() {
	return tokido_saya::main();
}
```
另：退役老年人多年未写代码连线段树合并都打不来了，调了好久。（当然 vp 的时候直接 $O(n^2)$）

---

## 作者：youakioi (赞：1)

## 题目分析
个人习惯将父节点设为 $u$，子节点设为 $v$。

所以原本的式子是 $a_u\le \sum a_v$，

将所有点 $u$ 都减去 $\sum a_v$，那么变成了 $a_u\le 0$。

每次操作，若 $a_v+1$，则 $a_u-1$。

所以如果我们想要将一个不合法的点 $u$，$a_u\gt 0$，变成一个合法的点，那么我们就需要通过操作他的儿子 $a_v$ 才行，也就是 $a_v+1$，$a_u-1$，操作次数 $t=a_u$。

可是若 $a_v=0$，那么 $a_v+1$ 就会导致 $v$ 变成不合法的，就需要在 $v$ 的儿子里操作，一直这么操作下去，直到一个 $a_k<0$，那么我们就要操作 $dep_k-dep_u$ 次，最多能减去 $-a_k$。若减掉后还不合法，就继续操作。

### 具体做法
从下往上操作，每次找到一个不合法的点 $u$，就找到若干个子树内的节点 $k$，其中满足 $a_k<0$ 且 $dep_k$ 最小。 

## 代码
~~自己打~~

```cpp
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a signed integer
	template <class I>
	inline void gi (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	// print a signed integer
	template <class I>
	inline void print (I x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: putc;
using io :: print;
const int N=1e5+10;
struct node{
	int l,r,add,sum,mul;
}tree[N<<2];
int n,m,q,a[N],t[N],sum,mod;
void spread(int k){
	tree[k*2].sum*=tree[k].mul,tree[k*2].sum%=m;
	tree[k*2].sum+=tree[k].add*(tree[k*2].r-tree[k*2].l+1),tree[k*2].sum%=m;
	tree[k*2+1].sum*=tree[k].mul,tree[k*2+1].sum%=m;
	tree[k*2+1].sum+=tree[k].add*(tree[k*2+1].r-tree[k*2+1].l+1),tree[k*2+1].sum%=m;
	tree[k*2].add*=tree[k].mul,tree[k*2].add%=m;
	tree[k*2].add+=tree[k].add,tree[k*2].add%=m;
	tree[k*2+1].add*=tree[k].mul,tree[k*2+1].add%=m;
	tree[k*2+1].add+=tree[k].add,tree[k*2+1].add%=m;
	tree[k*2].mul*=tree[k].mul,tree[k*2+1].mul*=tree[k].mul;
	tree[k*2].mul%=m,tree[k*2+1].mul%=m;
	tree[k].mul=1,tree[k].add=0;
}
int query(int k,int l,int r){
	int L=tree[k].l,R=tree[k].r;
	if(r<L||R<l) return 0;
	if(l<=L&&R<=r) return tree[k].sum;
	spread(k);
	return (query(k*2,l,r)+query(k*2+1,l,r))%m;
}
void build(int k,int l,int r){
	tree[k].l=l,tree[k].r=r,tree[k].mul=1;
	if(l==r){
		tree[k].sum=a[l]%m;
		return;
	}
	int mid=(l+r)>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	tree[k].sum=(tree[k*2].sum+tree[k*2+1].sum)%m;
}
inline void change(int x,int y){
	if(!x) return;
	for(;x<=n;x+=x&(-x)) t[x]+=y;//,t[x]%=mod;
}
inline int query(int x){
	if(x<=0) return 0;
	int sum=0;
	for(;x;x-=x&(-x)) sum+=t[x];//,sum%=mod;
	sum%=mod;
	sum=(sum+mod)%mod;
	return sum;
}
long long mi(long long o,long long p){
	o%=mod;
	long long res=1;
	while(p){
		if(p&1) res*=o,res%=mod;
		o*=o;
		o%=mod;
		p>>=1;
	}
	return res;
}
void mul(int k,int l,int r,int x){
	int L=tree[k].l,R=tree[k].r;
	if(L>r||R<l) return;
	if(l<=L&&R<=r){
		tree[k].sum*=x,tree[k].sum%=m;
		tree[k].mul*=x,tree[k].mul%=m;
		tree[k].add*=x,tree[k].add%=m;
		return;
	}
	spread(k);
	mul(k*2,l,r,x);
	mul(k*2+1,l,r,x); 
	tree[k].sum=(tree[k*2].sum+tree[k*2+1].sum)%m;
}
void add(int k,int l,int r,int x){
	int L=tree[k].l,R=tree[k].r;
	if(r<L||R<l) return;
	if(l<=L&&R<=r){
		tree[k].sum+=x*(R-L+1);
		tree[k].add+=x;
		return;
	}
	spread(k);
	add(k*2,l,r,x);
	add(k*2+1,l,r,x);
	tree[k].sum=(tree[k*2].sum+tree[k*2+1].sum)%m;
}
signed main(){
	int youcannotctj;
	for(int i=1;i<=25;i++) gi(youcannotctj);
	print(3);
	putc('\n');
	print(2);
	putc('\n');
	print(0);
	putc('\n');
	print(0); 
	//you can't ctj 
} 
```

---

## 作者：Shunpower (赞：0)

简单题。vp 的时候因为下课时间早 1h 没弄这题，之后看了一下发现特别简单，10min 就会了。

--------------

我们令 $c_x$ 表示 $x$ 所有儿子的和，然后考虑显然的思路起点：从下往上做，每次保证一个子树的完好。

如果 $x\le c_x$，那么我们显然暂时不必做任何操作。

如果 $x>c_x$，考虑我们需要先把它的一些儿子提高，总之是要提高 $x-c_x$。但是这样可能会产生更进一步向下的影响。

注意到我们并不区分每一层内部的节点。换句话说，我可以看成是让整个儿子层提高，如果还不够，就需要让孙子层提高。当然提高孙子层产生的贡献是 $2$，因为我是在让儿子卡满的情况下才会提高一个孙子。

进一步地，我对子树内第 $d$ 层的节点提高 $k$，产生的贡献是 $dk$。并且此时 $[1,d)$ 层内的每个节点一定都恰好卡到 $x=c_x$。

于是考虑怎么计算每一层需要提高多少。可以发现，每一层内部的 $x\le c_x$ 都会剩下一些余量可供我提高，这部分提高完了就必须挪到下一层去做。

于是在每个节点 $x$ 上维护一个 $f_{x,i}$ 表示 $x$ 子树内第 $i$ 层的余量，这个数组可以简单地归并算出。对于 $x>c_x$ 的情况，从 $i=1$ 开始往后扫 $f_x$ 计算贡献即可，注意这部分因为已经用掉了一些余量，上面的节点不能再使用，所以需要同步修改 $f_x$。

代码很好写。贡献算错了吃了三发罚时。/oh

```cpp
int tc;
int n;
int f[N];
int a[N];
vector <int> p[N];
ll rem[N][N];
ll ans;
void dfs(int x,int fa){
	ll sum=0;
	if(p[x].size()==0) sum=1e13;
	for(auto y:p[x]){
		if(y==fa) continue;
		dfs(y,x);
		sum+=a[y];
		fr1(i,1,n) rem[x][i]+=rem[y][i-1];
	}
	rem[x][0]=max(0ll,sum-a[x]);
	if(sum<a[x]){
		fr1(i,1,n){
			if(rem[x][i]>=a[x]-sum){
				rem[x][i]-=(a[x]-sum);
				ans+=1ll*i*(a[x]-sum);
				break;
			}
			else{
				ans+=1ll*i*rem[x][i];
				sum+=rem[x][i];
				rem[x][i]=0;
			}
		}
	}
}
void solve(){
	ans=0;
	cin>>n;
	fr1(i,1,n) p[i].clear();
	fr1(i,1,n) fr1(j,0,n) rem[i][j]=0;
	fr1(i,1,n) cin>>a[i];
	fr1(i,2,n) cin>>f[i],p[f[i]].pb(i);
	dfs(1,0);
	cout<<ans<<'\n';
}
```

---

## 作者：junee (赞：0)

# CF1987E 题解

## 题目分析

读题后我们很容易发现，当当前节点的儿子节点的值小于自己时，优先加离自己近的儿子。当他儿子满了后，就只能两个节点一起加，所以我们可以用一个数组 $delta$ 来记录当前节点最多加几次就满了。

但是，如果我们到达了叶子节点其他更深的节点就不用考虑，所以每个数组的长度为到叶子节点的距离 $-2$。

每次将自己儿子的信息合并到自己身上，在按层数依次往下操作。


## Code
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
const int N=5e3+10;
typedef long long LL;
int h[N],e[N*2],ne[N*2],idx;
int n,T;
LL w[N],f[N];
int dist[N];
vector<LL> delta[N];
void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void dfs_dist(int u){
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		dfs_dist(j);
		dist[u]=min(dist[u],dist[j]+1);
	}
	if(dist[u]==0x3f3f3f3f)dist[u]=1;
}
void merge(int u,int v,int &flag){
    if(dist[v]==1)return;
    int s=abs(dist[u]-dist[v]);
    if(dist[v]>=dist[u])s++;
    else s--;
    if(flag==1){
        for(int j=s;j<=dist[v]-2;j++)
		    delta[u].push_back(delta[v][j]);
		flag=0;
	    return;
    }
    flag=0;
	for(int i=0,j=s;i<=dist[u]-2&&j<=dist[v]-2;i++,j++)
		delta[u][i]+=delta[v][j];
}
void dfs(int u){
    if(dist[u]==1){return;}
	LL sum=0;
	int flag=1;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
    	dfs(j);
		merge(u,j,flag);
		sum+=w[j];
		f[u]+=f[j];
	}
	if(sum>=w[u]){
		delta[u].push_back(sum-w[u]);
		return;
	}
	LL W=w[u];
	W-=sum;
	delta[u].push_back(0);
	for(int i=delta[u].size()-1,k=0;i>=0;i--,k++){
	    if(!delta[u][i])continue;
		if(delta[u][i]<W){
		    W-=delta[u][i];
		    f[u]+=delta[u][i]*k;
		    delta[u][i]=0;
		}
		else{
			delta[u][i]-=W;
			f[u]+=k*W;
			W=0;
			break;
		}
	}
	if(W>0)f[u]+=W*(dist[u]-1);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		memset(h,-1,sizeof h),idx=0;
		memset(dist,0x3f,sizeof dist);
		memset(f,0,sizeof f);
		for(int i=1;i<=N;i++){
			delta[i].clear();
		}
		cin>>n;
		for(int i=1;i<=n;i++)cin>>w[i];
		for(int i=2,x;i<=n;i++)cin>>x,add(x,i);
		dfs_dist(1);
		dfs(1);
		cout<<f[1]<<'\n';
	}
	return 0;
}
```

---

## 作者：gan1234 (赞：0)

来个不用动脑子的做法。

### 分析

直接的想法就是 dp。

令 $f_{x,i}$ 表示最终 $x$ 的权值为 $i$ 的最小操作次数，发现这个东西它是凸的，因为随着权值增大，需要操作的点单调递增。那就直接闵可夫斯基和转移就做完了。

### 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 5005
#define int long long
using namespace std;
int n;
int a[MAXN];
vector<int>G[MAXN];
struct P{
	int x,y;
};
P add(P p1,P p2){
	return P{p1.x+p2.x,p1.y+p2.y};
}
P del(P p1,P p2){
	return P{p1.x-p2.x,p1.y-p2.y};
}
vector<P>f[MAXN];
vector<P> unite(vector<P> f1,vector<P> f2){
	if(f1.empty())return f2;
	if(f2.empty())return f1;
	vector<P>v;
	v.push_back(add(f1[0],f2[0]));
	int l1=1,l2=1;
	P lst=v[0];
	while(l1<f1.size()&&l2<f2.size()){
		
		if((f1[l1].y-f1[l1-1].y)/(f1[l1].x-f1[l1-1].x)<=(f2[l2].y-f2[l2-1].y)/(f2[l2].x-f2[l2-1].x))
			v.push_back(add(del(f1[l1],f1[l1-1]),lst)),l1++;
		else v.push_back(add(del(f2[l2],f2[l2-1]),lst)),l2++;
		
		lst=v.back();
	}
	while(l1<f1.size()){
		v.push_back(add(del(f1[l1],f1[l1-1]),lst));l1++;
		lst=v.back();
	}
	while(l2<f2.size()){
		v.push_back(add(del(f2[l2],f2[l2-1]),lst));l2++;
		lst=v.back();
	}
	return v;
}
void dfs(int x,int pre){
	f[x].clear();
	for(auto y:G[x]){
		if(y==pre)continue;
		dfs(y,x);
		vector<P>v;
		f[x]=unite(f[x],f[y]);
		swap(f[y],v);
	}
	if(f[x].size()){
		if(f[x][0].x<=a[x]){
			vector<P>v;
			int t=0;
			while(f[x][t].x<=a[x]&&t<f[x].size())t++;
			P p1=f[x][t-1],p2=f[x][t];
			v.push_back(P{a[x],(a[x]-p1.x)*(p2.y-p1.y)/(p2.x-p1.x)+p1.y});
			for(int i=t;f[x].size()>i;i++)v.push_back(f[x][i]);
			f[x]=v;

		}else{
			P p=*f[x].begin();
			f[x].insert(f[x].begin(),P{a[x],p.y});
		}
		for(int i=1;f[x].size()>i;i++)f[x][i].y+=f[x][i].x-a[x];
	}else{
		f[x].push_back(P{a[x],0});
		f[x].push_back(P{(int)1e9+a[x],(int)1e9});
	}
}

void work(){
	
	cin>>n;
	for(int i=1;n>=i;i++)cin>>a[i];
	for(int i=1;n>=i;i++)G[i].clear();
	int x,y;
	for(int i=2;n>=i;i++){
		cin>>x;
		G[i].push_back(x);
		G[x].push_back(i);
	}
	dfs(1,0);
	cout<<f[1][0].y<<endl;
}
signed main(){
	int _T;
	cin>>_T;
	while(_T--)work();
	return 0;
}
```

---

