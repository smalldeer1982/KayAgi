# Hidden Bipartite Graph

## 题目描述

**这是一道交互题。**

给定一个连通图（不包括自环和重边），你可以询问一个点集 $s$，系统会返回在 $s$ 中有两个端点的边的数量。你最多可以询问 $20000$ 次。

你需要判断这个图是不是一个二分图。

## 样例 #1

### 输入

```
4
4
0
1
1
1
0```

### 输出

```
? 4 
1 2 3 4
? 2
1 2
? 2
1 3
? 2
1 4
? 2
2 4
? 2
3 4
Y 2
1 2```

## 样例 #2

### 输入

```
4
4
3```

### 输出

```
? 4
1 4 2 3
? 3
1 2 4
N 3
2 1 4```

# 题解

## 作者：DeaphetS (赞：11)

题目链接：[1033E - Hidden Bipartite Graph](https://codeforces.com/contest/1033/problem/E "1033E - Hidden Bipartite Graph")

题目大意：交互题，有一个点数为 $n\le 600$ 的无向连通图（$n$ 给定），有 $20000$ 次询问机会。每次询问可以给出一个点集，返回点集内的点两两之间一共有多少条边。要求判断图是否为二分图，若是则输出其中一边，若不是则输出其中一个奇环。

考虑将图分层，一开始第一层对应点集 $S_1={1}$，之后如果对每一层 $S_i$，都能找到所有与 $S_i$ 有边相连的点，那么就能有一个新的点集 $S_{i+1}$，一直这样下去就能建起一棵生成树，实现对图的分层。

那么现在就需要处理若干个这样的子问题：有点集 $S,T$，要求在 $T$ 中找到所有与 $S$ 有边相连的点。

考虑分治，对点集 $T$ ，可以把所有点都存在 `vector` 中，这样每个区间就对应着 $T$ 中的一个子集。我们把 $T$ 分成两部分 $T_L=[l,mid],T_R=(mid,r]$，如果我们能判断出 $T_L,T_R$ 与 $S$ 之间的连边关系，对有边的区间继续询问下去，就能够进行递归求解求出所有满足条件的点。

现在相当于我们需要判断两个点集 $S,t$ 之间是否有连边，那么我们知道，当询问的点集为 $S\cup t$ 时，返回的边数里包含了 $S$ 内部以及 $t$ 内部自身的连边。所以我们相当于要判断 $Ask(S\cup t)-Ask(S)-Ask(t)$ 的值。而由于在每一层，$S$ 都是固定的，所以可以提前存下 $Ask(S)$ 的值，就可以做到两次询问实现判断了。

我们分析一下这样做需要耗费的询问次数。其实可以类比线段树的单点修改操作，对于所有满足条件的点，与之相关的区间都只会有 $O(\log n)$ 个，于是可以得出总的询问次数就是 $O(n\log n)$ 的。

现在我们求出了每一层有哪些点，接下去就可以进行判断。只需要把奇数层和偶数层分别放到一起，判断内部是否有连边即可。那么是二分图的情况非常好弄，直接输出就好，不是二分图的情况就不是很好搞，因为我们需要找到一个奇环。

我们知道，出现矛盾是因为奇数层（或偶数层）内部有边相连，那么如果我们能够找到这条边 $(x,y)$，并找到 $x$ 与 $y$ 到这棵生成树上 $\operatorname{LCA}(x,y)$ 的路径，就相当于找到了一个奇环。

那么这里就面临着两个问题：

- 怎么找到 $(x,y)$；
- 怎么找到 $\operatorname{LCA}(x,y)$，或者怎么找一个点 $x$ 在生成树上的父亲。

首先，我们可以通过枚举集合内部的点 $i$，并判断 $i$ 与集合内其他点是否有连边找到其中的一个端点 $x$。找到 $x$ 之后，我们只需要在剩下的集合中找到一个与 $x$ 相邻的点即可。

而关于找 $x$ 在生成树上的父亲，我们可以在分层的时候就可以记录每个点对应的层数 $v_x $，那么我们只需要找到一个在 $v_x-1$ 层的一个点与 $x$ 相邻即可。如果能实现这一操作，我们就能够一步步往上跳暴力找到两个点的 $\operatorname{LCA}$。

可以发现，这两个问题最终都需要我们处理一个操作：给定集合 $T$ 与点 $x$，找到 $T$ 中任意一个与 $x$ 有边相连的点。可以套用之前的做法分治，但是因为这里只需要找到任意一个满足条件的点，二分查找就足够了，这一部分所需要的询问次数也是 $O(n\log n)$ 的。

于是在最坏情况下，每次操作都需要耗费两个询问次数，大概需要询问 $4n\log n$ 次，正好卡在 $20000$ 以内，最后本人代码的最多询问次数为 $16675$，还是比较充裕的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 666
int n,cnt,v[N],t;
vector<int>d,s,tmp,O,E,f[N];
int Ask(vector<int>D)//询问 
{
	if(D.size()<2)return 0;//点集大小不超过2时，可以不用询问 
	printf("? %d\n",(int)D.size());
	for(auto i:D)printf("%d ",i);
	printf("\n");
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}
int Count(int l,int r)//计算S和区间[l,r]内的点之间的边数 
{
	tmp.clear();
	for(int i=l;i<=r;i++)tmp.push_back(d[i]);
	int Self=Ask(tmp);//计算[l,r]内部边数 
	for(auto i:s)tmp.push_back(i);
	int Sum=Ask(tmp);//计算并集的总边数 
	return Sum-Self-t;//t的值在之前已经提前求过了，是S内部的边数 
}
void Find(int l,int r)//利用分治的思想找到每个与S有连边的点 
{
	if(l==r){
		if(Count(l,r)){//单独判断d[l]与S是否有连边 
			v[d[l]]=cnt;//v[i]表示i号结点在第几层 
			f[cnt].push_back(d[l]);//把每一层的结果存下来，后面找父亲要用 
		}
		return;
	}
	int mid=l+r>>1;//这里的操作和线段树单点修改类似 
	if(Count(l,mid))Find(l,mid);
	if(Count(mid+1,r))Find(mid+1,r);
}
int Find2()//已知点x与d内的点有连边，二分找出一个与x有连边的点 
{
	int l=0,r=d.size()-1;
	while(l<r){
		int mid=l+r>>1;
		if(Count(l,mid))r=mid;
		else l=mid+1;
	}
	return d[l];
}
int getf(int x)//对于点x，在树上的父亲一定在v[x]-1这一层 
{
	t=0;
	d=f[v[x]-1];
	s.clear();
	s.push_back(x);
	return Find2();
}
void rua(vector<int>D)//找奇环 
{
	int m=D.size(),x,y;
	for(int i=0;i<m;i++){//通过枚举找到一个与其他点有连边的x 
		tmp.clear();
		for(int j=0;j<m;j++)
			if(j!=i)tmp.push_back(D[j]);
		if(Ask(tmp)<t){
			x=D[i];
			break;
		}
	}
	t=0;
	d=tmp;
	s.clear();
	s.push_back(x);
	y=Find2();//找到一个与x有连边的y 
	vector<int>ansx,ansy;//分别存储x,y到其祖先的路径，直接暴力找LCA 
	ansx.push_back(x);
	ansy.push_back(y);
	while(v[x]<v[y]){
		x=getf(x);
		ansx.push_back(x);
	}
	while(v[y]<v[x]){
		y=getf(y);
		ansy.push_back(y);
	}
	while(x!=y){
		x=getf(x);
		y=getf(y);
		ansx.push_back(x);
		ansy.push_back(y);
	}
	printf("N %d\n",ansx.size()+ansy.size()-1);
	for(auto i:ansx)printf("%d ",i);
	ansy.pop_back();
	reverse(ansy.begin(),ansy.end());//因为之前输出的是x到LCA的路径，所以要翻转 
	for(auto i:ansy)printf("%d ",i);
}
int main()
{
	scanf("%d",&n);
	v[1]=++cnt;
	s.push_back(1);
	f[1].push_back(1);
	for(int i=2;i<=n;i++)d.push_back(i);
	while(!d.empty()){
		cnt++;
		t=Ask(s);//提前计算S内部的连边，减少询问次数 
		Find(0,d.size()-1);
		d.clear(),s.clear();
		for(int i=1;i<=n;i++){
			if(!v[i])d.push_back(i); //所有还没访问过的点作为集合T
			if(v[i]==cnt)s.push_back(i);//把当前层的点作为新的S 
		}
	}
	for(int i=1;i<=n;i++)//奇偶分别存，判断是否存在奇环 
		if(v[i]&1)O.push_back(i);
		else E.push_back(i);
	t=Ask(O);
	if(t){
		rua(O);
		return 0;
	}
	t=Ask(E);
	if(t){
		rua(E);
		return 0;
	}
	printf("Y %d\n",(int)O.size());
	for(auto i:O)printf("%d ",i);
	return 0;
}
```



---

## 作者：wurzang (赞：3)

[题意](https://www.luogu.com.cn/paste/zja2tt3d)

先考虑怎么判断二分图。

可以直接构造一棵生成树，然后判断一下奇数层内是否有边，偶数层内是否有边就可以了。

在生成树上 bfs，设当前 bfs 的节点是 $u$，考虑对于当前未加入生成树中的点，有哪些可以成为 $u$ 的儿子。

可以在未加入生成树中的点里分治，如果 $[l,r]$ 与 $u$ 有边，就分成 $[l,mid]$ 和 $[mid+1,r]$，否则直接 return。至于如何判断有边，点集 $s_1$ 和点集 $s_2$ 之间的边数可以表示成 $query(s_1 \cup s_2)-query(s_1)-query(s_2)$

毛估估一下，交互次数大概是 $n\log n$ 级别的，可以过。

那么考虑如何输出方案。如果是二分图的话，直接输出奇数层的点就行了。

如果不是二分图，就需要判断奇数层/偶数层里连着的那条边。

这里有一种比较好写的做法。

如果直接像上面一样对着点集分治，有可能分出的两个点集里都没有连着的边。如果没有的话，可以直接对点集随机分治，直到有一个点集有连着的边，期望次数大概是 $2$。

这样就以 $2$ 的代价将点集缩小一半（因为只需要找到一条连着的边），期望操作次数是$n\log n$，可以过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=605;
int query(vector<int> vec){
    int n=vec.size();
    if(n<=1) return 0;
    cout<<"? "<<n<<endl;
    for(int i=0;i<n;++i)
        cout<<vec[i]<<((i==n)?"\n":" ");
    fflush(stdout);
    int ans;
    cin>>ans;
    return ans;
}
queue<int> q;
int vis[N],dep[N],fa[N];
void add(int u,int f){
    if(vis[u]) return;
    vis[u]=1; dep[u]=dep[f]+1; fa[u]=f;
    q.push(u);
}
void calc(int u,vector<int> v){
    if(v.size()==0) return;
    int m1=query(v),m2;
    v.push_back(u); m2=query(v);
    if(m2==m1) return;
    v.pop_back();
    if(v.size()==1) return add(v.front(),u);
    int mid=v.size()/2;
    vector<int> v1,v2;
    for(int i=0;i<mid;++i) v1.push_back(v[i]);
    for(int i=mid;i<v.size();++i) v2.push_back(v[i]);
    calc(u,v1),calc(u,v2);
}
void find(int u,int v){
    int lca=0,a=u,b=v;
    while(a^b){
        if(dep[a]<dep[b]) swap(a,b);
        a=fa[a];
    }
    lca=a;
    vector<int> ans;
    for(int i=u;i;i=fa[i]){
        ans.push_back(i);
        if(i==lca) break;
    }
    reverse(ans.begin(),ans.end());
    for(int i=v;i^lca;i=fa[i])
        ans.push_back(i);
    cout<<"N "<<ans.size()<<endl;
    for(int v:ans) cout<<v<<" ";
    exit(0);
}
void solve(vector<int> v){
    if(v.size()<=1) return;
    if(v.size()==2) return find(v.front(),v.back());
    while(1){
        random_shuffle(v.begin(),v.end());
        int mid=(v.size()+1)/2;
        vector<int> v1=v; v1.resize(mid);
        if(query(v1)) return solve(v1);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    srand(time(0));
    int n;
    cin>>n;
    add(1,0);
    while(!q.empty()){
        int u=q.front();q.pop();
        vector<int> v;
        for(int i=1;i<=n;++i)
            if(!vis[i]) v.push_back(i);
        calc(u,v);
    }
    vector<int> vec[2];
    for(int i=1;i<=n;++i)
        vec[dep[i]&1].push_back(i);
    if(query(vec[0])) solve(vec[0]);
    else if(query(vec[1])) solve(vec[1]);
    cout<<"Y "<<vec[0].size()<<endl;
    for(auto v:vec[0]) cout<<v<<" ";
    return 0;
}
```


---

## 作者：Purslane (赞：2)

# Solution

先考虑判定，并且如果是二分图把点集划分出来。

这个是容易的。我们钦定 $1$ 号点在左部，目前得到了点集 $L$ 和 $R$。

如果 $L \cup R$ 不是全集，必定存在一个点和 $L$ 有连边或者和 $R$ 有连边。必定能用 $O(\log n)$ 次操作得到（直接对集合进行二分即可）。

这样得到了 $O(n \log n)$ 的判定方法。

可惜你要找到环。

所以问题出在哪里呢？发现如果往 $L$ 中加了一个点，但是它本身和 $L$ 有连边，就倒闭了。。

每次加点的时候，反向二分一次，得到它和哪个点联通。直接在上面跑一个可行路径就行了。

详细分析操作次数：每次加一个点，需要 $3 \log n$ 次用来二分。而用 $2$ 次判定哪个集合加点，用 $1$ 次判定是否

所以一共是 $3n + 3 n \log n$ 次，看起来就够。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=700+10;
int n,cnt,fa[MAXN],vis[MAXN];
vector<int> L,R,G[MAXN];
int query(vector<int> vc) {if(vc.size()<=1) return 0;cout<<"? "<<vc.size()<<endl;for(auto id:vc) cout<<id<<' ';cout<<endl,cout.flush();int res;cin>>res;return res;}
vector<int> operator +(vector<int> A,vector<int> B) {for(auto id:B) A.push_back(id);return A;}
int check(vector<int> ad,vector<int> ori) {return query(ad+ori)-query(ad);}
int find_point(vector<int> ad,vector<int> ori) {
	if(ad.size()==1) return ad[0];
	vector<int> ll,rr;
	ffor(i,0,(ad.size()/2)-1) ll.push_back(ad[i]);
	ffor(i,ad.size()/2,ad.size()-1) rr.push_back(ad[i]);
	if(check(ll,ori)) return find_point(ll,ori);
	return find_point(rr,ori);
}
int find_connect(vector<int> ad,vector<int> ori) {
	if(ori.size()==1) return ori[0];
	vector<int> ll,rr;
	ffor(i,0,(ori.size()/2)-1) ll.push_back(ori[i]);
	ffor(i,ori.size()/2,ori.size()-1) rr.push_back(ori[i]);
	if(check(ad,ll)) return find_connect(ad,ll);
	return find_connect(ad,rr);
}
void add_edge(int u,int v) {return G[u].push_back(v),G[v].push_back(u),void();}
void output(int rt,int fin) {
	memset(vis,-1,sizeof(vis));
	vis[rt]=0;
	queue<int> q;
	q.push(rt);
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(auto v:G[u]) if(vis[v]==-1) vis[v]=vis[u]+1,q.push(v),fa[v]=u;
	}
	vector<int> res;
	while(fin!=rt) res.push_back(fin),fin=fa[fin];
	res.push_back(rt);
	cout<<"N "<<res.size()<<endl;
	for(auto id:res) cout<<id<<' ';
	cout<<endl,cout.flush();
	return ;
}
int main() {
	cin>>n;
	L.push_back(1),cnt=1,vis[1]=1;
	while(cnt<n) {
		vector<int> nw;
		ffor(i,1,n) if(!vis[i]) nw.push_back(i);
		if(check(nw,L)) {
			int p=find_point(nw,L);
			if(check({p},R)) {
				add_edge(find_connect({p},L),p);
				int wa=find_connect({p},R);
				output(p,wa);
				return 0; 
			}
			add_edge(find_connect({p},L),p),R.push_back(p),vis[p]=1;
		}
		else {
			int p=find_point(nw,R);
			if(check({p},L)) {
				add_edge(find_connect({p},R),p);
				int wa=find_connect({p},L);
				output(p,wa);
				return 0; 
			}
			add_edge(find_connect({p},R),p),L.push_back(p),vis[p]=1;
		}
		cnt++;
	}
	cout<<"Y "<<L.size()<<endl;
	for(auto id:L) cout<<id<<' ';
	cout<<endl,cout.flush();
	return 0;
}
```

---

## 作者：chlchl (赞：2)

~~题单全是交互题是要整人吗……~~

但是不得不说是个好题，再次拜谢黄队/bx/bx/bx。

## Solution
首先要知道，查询点 $x$ 与点集 $S$ 的连边数量的代价为 $2$，即 $query(\{x\}\cup S)-query(S)$。

然后如果 $|S|=1$，显然你找到了一条边。

简单连通图，还要判二分图，可以联想到生成树。只要我们知道随便一棵生成树，那么只要看深度为奇数、偶数的点集内部是否有连边，就能知道是不是二分图了。

考虑到 $n$ 只有 $600$，可以试试暴力一点的做法。

先钦定初始的点集 $S$ 只有 $1$，未连边的点集 $T$ 为 $2\sim n$。每次我们钦定一个 $S$ 内的点 $u$，暴力找 $u$ 和 $T$ 中的点的连边。

这个是 $O(n^2)$ 级别的，有点太过暴力。可以二分优化，每次将 $T$ 拆成左右两部分，这样最多 $\log$ 次就可以使 $|T|=1$（然后就可以直接连边），查询次数降为 $O(n\log n)$ 级别。

注意一次查询需要进行两次询问，所以会有个 $2$ 的常数。

然后是二分图的情况就做完了，直接输出深度为奇数或偶数的所有点即可。

不是二分图的情况，我们需要在某个集合 $A$ 中找到一条非树边 $(u,v)$，这样 $u,v$ 的树上路径加上 $(u,v)$ 一定是一个奇环。

有很多种做法，一种比较好做的是，对集合 $A$ 随机分治，即随机挑出一半的点作为 $A'$，判断 $A'$ 是否有连边，如果有就一直递归，没有就重新挑点。

这样随机的期望次数约为 $2$，总查询次数可以在 $4n\log n$ 左右，但是因为实际上跑不满，可以通过。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 600 + 10;
int n, vis[N], fa[N], dep[N];
queue<int> q;

int query(vector<int> xyr){
	if(xyr.size() <= 1)
		return 0;
	int res = 0;
	printf("? %d\n", xyr.size());
	for(int u: xyr)
		printf("%d ", u);
	printf("\n");
	fflush(stdout);
	scanf("%d", &res);
	return res;
}

void add(int u, int v){
	vis[v] = vis[u] = 1;
	fa[v] = u, dep[v] = dep[u] + 1;
	q.push(v);
}

void find(int u, vector<int> vec){
	if(vec.empty())
		return ;
	int e1 = query(vec);
	vec.push_back(u);
	int e2 = query(vec);
	if(e1 == e2)
		return ;//u 与 vec 没有连边
	vec.pop_back();
	if(vec.size() == 1){//点集只有一个点，连边确定 
		add(u, vec[0]);
		return ;
	}
	int mid = vec.size() >> 1;
	vector<int> chl, xyr;
	for(int i=0;i<mid;i++)
		chl.push_back(vec[i]);
	for(int i=mid;i<vec.size();i++)
		xyr.push_back(vec[i]);
	find(u, chl);
	find(u, xyr);
}

int LCA(int u, int v){
	if(dep[u] < dep[v])
		swap(u, v);
	while(dep[fa[u]] >= dep[v])
		u = fa[u];
	if(u == v)
		return u;
	while(fa[u] != fa[v])
		u = fa[u], v = fa[v];
	return fa[u];
}

void find_path(int u, int v){//已经知道是 u, v 出现奇环 
	int lca = LCA(u, v);
	vector<int> path;
	for(int now=u;now!=lca;now=fa[now])
		path.push_back(now);
	path.push_back(lca);
	reverse(path.begin(), path.end());
	
	for(int now=v;now!=lca;now=fa[now])
		path.push_back(now);
	printf("N %d\n", path.size());
	for(int now: path)
		printf("%d ", now);
	printf("\n");
	fflush(stdout);
}

void solve(vector<int> vec){
	if(vec.size() < 2)
		return ;
	if(vec.size() == 2){
		find_path(vec[0], vec[1]);
		return ;
	}
	while(1){
		random_shuffle(vec.begin(), vec.end());
		int mid = vec.size() >> 1;
		vector<int> xyr;
		for(int i=0;i<=mid;i++)
			xyr.push_back(vec[i]);
		if(query(xyr)){
			solve(xyr);
			return ;
		}
	}
}

int main(){
	srand(time(0));
	scanf("%d", &n);
	if(n == 1)
		return printf("Y 1\n1\n"), 0;
	add(0, 1);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vector<int> vec;
		for(int i=1;i<=n;i++)
			if(!vis[i])//还没有连边的点全部扔进去 
				vec.push_back(i);
		find(u, vec);
	}
	//奇数深度 
	vector<int> chl;
	for(int i=1;i<=n;i++)
		if(dep[i] & 1)
			chl.push_back(i);
	if(query(chl))
		solve(chl);
	//偶数深度 
	chl.clear();
	for(int i=1;i<=n;i++)
		if(!(dep[i] & 1))
			chl.push_back(i);
	if(query(chl))
		solve(chl);
	
	printf("Y %d\n", chl.size());
	for(int u: chl)
		printf("%d ", u);
	printf("\n");
	fflush(stdout);
	return 0;
}
```

---

## 作者：Leap_Frog (赞：2)

### P.S.  
半个上午和半个下午被这题折磨光光了/ll /ll /ll  
本文共出现了 10 次 **binary search** /tuu  
这个做法可能比较菜，最大的点用了 **18729** 个询问。  
![](https://z3.ax1x.com/2021/10/27/5HuiHx.png "求赞 /kel --xtw")  

### Description.
交互，有张 $n(n\le 600)$ 的联通图，每次你给一个点集，交互库返回导出子图边数。  
在 $20000$ 次内判断图是否是二分图，如果是就输出一侧的所有点，否则就输出任意一个奇环。  

### Solution.
**Stop learning useless algorithms, go and solve some problems, learn how to use binary search.**  
这题基本从上到下有无数个 **binary search**。  

挖一些询问方式
1. $\text{qry}(S\cup\{x\})-\text{qry}(S)$ 可以询问出 $x$ 到 $S$ 的边数。  
2. $\text{qry}(S\cup T)-\text{qry}(S)-\text{qry}(T)$ 可以询问出 $S$ 和 $T$ 集合之间的边。  

首先，我们考虑假设给了一条链怎么做。  
找到一个起点，每次往两端扩展，总共需要扩展 $O(n)$ 次。  
每次相当于要从剩下的集合中找到一个和当前端点相邻的点集，并扩展。  
这时我们就可以用 **binary search** 来解决这个问题了。  
每次查寻前缀和当前端点有几条连边，具有单调性，可以 **binary search**。  
总复杂度 $O(n\log n)$

**注：这一段做法可能不够优秀，但是最后的能 AC 的做法是基于这个做法优化的**  
发现这个东西可以扩展，可以把 **binary search** 扩展成分治。  
我们先把当前所有的没被扩展的点拿出来，排成一个序列。  
我们每次询问，可以询问的是当前扩展的**点集**和序列中的若干点有无连边。  
可以考虑分治，如果当前这段区间有就继续，否则就没有。  
复杂度分析一下发现是 $O(\min(n,cnt\times \log n))$ 的，和线段树的单点查询有点类似。  
其中 $cnt$ 表示的是和当前**点集**相邻的点数量。  
每次找到和当前相邻的点集，判断内部有无连边，然后继续扩展。  
发现均摊一下每个点只可能被扩展一次，总复杂度 $O(n\log n)$。  

然后发现有一个重要问题没有考虑：怎么输出奇环。  
可以考虑建出一个生成树，然后找到奇偶相同层之间的连边。  
这个东西可以 **binary search**，就二分序列。  
如果左边内部有边，就二分左边，否则如果右边有边，就二分右边。  
否则必然是左右连的边，就 **binary search** 找到左边的和右边有边的点，然后 **binary search** 找到右边的和左边有连边的点。  
然后这两个点肯定构成一个奇环，直接输出生成树上两点链就行了。  

然后生成树怎么建：类似于 bfs 一样一层一层扩展。  
每扩展到下一层，在分治边缘，需要把新点加到当前树中。  
此时可以直接用 **binary search** 找到任意一个和当前这个点有连边的点。  
然后让当前新扩展到的点的父亲是他就行了。  

分析一下复杂度，找父亲每个点要找一遍 $O(n\log n)$。  
分治总复杂度是 $O(n\log n)$，找奇环总复杂度是 $O(\log n)$。  
总复杂度 $O(n\log n)$，在 $600$ 下跑在 $20000$ 以内**应该**很稳。  

[冲了一发](https://codeforces.com/contest/1033/submission/133222400)  
次数超了！！！观察上面代码的分治过程。  
发现每次分治需要 $2.5$ 的常数，每个点二分父亲时大概需要 $2$ 的常数。  
总询问次数上限是 $4.5n\log n \approx 24917$。  
所以你被卡常了！！！本地测了一下，发现 $600$ 的环大概需要 $21530$ 次。  
而且这个也没办法优化，常数巨大，瞬间爆毙。  

考虑能不能从方法上优化这个东西，发现这个东西本质上就是在做 `bfs`。  
如果我们每次枚举一个点作为父亲让他来扩展，这样就不需要在底层二分了，去掉了 $2$ 的常数。  
同时分治时也不需要查寻三次只需要查寻两次了，又减少了 $1$ 的常数。  
这样就能过了。  

### Coding.
稍微写了点注释  
[有一大堆调试信息的代码（有点精污，就不放在版面上了](https://codeforces.com/contest/1033/submission/133225550)  

```cpp
//Coded by leapfrog on 2021.10.27 {{{
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int N=605;typedef vector<int>vi;int n,fa[N],dep[N];char vs[N];
inline int qry(vi q)
{//询问
	int x=0;if((int)q.size()<2) return 0;
	printf("? %d\n",(int)q.size());for(auto x:q) printf("%d ",x);
	putchar('\n'),fflush(stdout);read(x);if(x==-1) exit(0);else return x;
}
inline vi split(const vi &a,int l,int r)
{//取一个 vector 的区间
	vi rs;for(int i=l;i<=r;i++) rs.push_back(a[i]);
	return rs;
}
inline vi merge(const vi &a,const vi &b)
{//合并两个 vector
	vi r;if(a.size()>b.size()) {r=a;for(auto x:b) r.push_back(x);}
	else {r=b;for(auto x:a) r.push_back(x);}
	return r;
}
inline vi solve(const vi &x,int ls,int l,int r)
{//分治
	int md=(l+r)>>1,vl;vi rs,tmp;
	if(l==r) return rs.push_back(x[l]),dep[x[l]]=dep[fa[x[l]]=ls]+1,rs;
	tmp=split(x,l,md),vl=qry(tmp),tmp.push_back(ls),vl=qry(tmp)-vl;
	for(int i=l;i<=md;i++) vl-=vs[x[i]];
	if(vl) rs=merge(rs,solve(x,ls,l,md));
	tmp=split(x,md+1,r),vl=qry(tmp),tmp.push_back(ls),vl=qry(tmp)-vl;
	for(int i=md+1;i<=r;i++) vl-=vs[x[i]];
	if(vl) rs=merge(rs,solve(x,ls,md+1,r));
	return rs;
}
inline int LCA(int x,int y)
{//暴跳求 LCA
	if(dep[x]<dep[y]) swap(x,y);
	while(dep[x]>dep[y]) x=fa[x];
	while(x!=y) x=fa[x],y=fa[y];
	return x;
}
inline void NOT(vi v)
{//输出奇环
	int l=0,r=v.size()-1,md=(l+r)>>1;
	for(;l<=r;md=(l+r)>>1)
	{//第一次二分
		if(qry(split(v,l,md))) r=md;
		else if(qry(split(v,md+1,r))) l=md+1;
		else break;
	}int rsl=-1,rsr=-1;//后两次二分↓↓
	for(int L=l,R=md,mid=(L+R)>>1;L<=R;mid=(L+R)>>1)
		if(qry(merge(split(v,l,mid),split(v,md+1,r)))) rsl=mid,R=mid-1;else L=mid+1;
	for(int L=md+1,R=r,mid=(L+R)>>1;L<=R;mid=(L+R)>>1)
		if(qry(merge(split(v,rsl,rsl),split(v,L,mid)))) rsr=mid,R=mid-1;else L=mid+1;
	int x=v[rsl],y=v[rsr],lc=LCA(x,y);printf("N %d\n",dep[x]+dep[y]-dep[lc]*2+1);
	vector<int>tp;while(x!=lc) printf("%d ",x),x=fa[x];
	printf("%d ",lc);while(y!=lc) tp.push_back(y),y=fa[y];
	reverse(tp.begin(),tp.end());for(auto w:tp) printf("%d ",w);
	putchar('\n'),fflush(stdout),exit(0);
}
int main()
{
	queue<int>q;read(n),vs[1]=1,q.push(1);
	while(!q.empty())
	{//bfs
		int x=q.front();q.pop();vi nw;
		for(int i=1;i<=n;i++) if(!vs[i]) nw.push_back(i);
		int qwq=qry(nw);nw.push_back(x),qwq=qry(nw)-qwq,nw.pop_back();if(!qwq) continue;
		vi tp=solve(nw,x,0,nw.size()-1);for(auto x:tp) q.push(x),vs[x]=1;
	}
	vi tp;for(int i=1;i<=n;i++) if(dep[i]&1) tp.push_back(i);
	if(qry(tp)) return NOT(tp),0;else tp.clear();
	for(int i=1;i<=n;i++) if(!(dep[i]&1)) tp.push_back(i);
	if(qry(tp)) return NOT(tp),0;else printf("Y %d\n",(int)tp.size());
	for(auto x:tp) printf("%d ",x);
	return putchar('\n'),fflush(stdout),0;
}
```

---

## 作者：⑨_Cirno_ (赞：2)

~~为什么这么久远的题没人做~~

我们考虑图是否是二分图，其实可以找出任意一棵生成树，然后把它染色，问一下黑点集合和白点集合内部是否有边即可判断。

我们考虑开始有1号点，随后往里依次加一个不在当前联通块的点。

对于这个问题，我们考虑二分，我们首先要确定一个与联通块有边相连的点，我们先询问联通块内部有多少边，然后把外部点平分成两部分，询问其中一部分的内部边数，再将这一部分与现有联通块一起再问一次，如果前两者的和等于后一个的答案，那么显然我们可以确定联通块与该集合中至少有两点相连，我们就继续对这一部分执行该过程，否则一定没有边，我们就舍弃这一部分，对另一部分继续处理，直到只剩下一个点。

对于这一个点，我们还要确定它与联通块中哪一个点有边相连，我们继续二分，把联通块分成两部分，询问其中一部分内部的边数与加上该点内部的边数是否相等，由此判断该点与这一部分是否有边相连，有则对这一部分继续二分，没有则对另一部分二分，因为图是联通的，所以我们每次肯定能加入一个点，询问次数就是nlogn

这样我们就能确定原图的一棵生成树，对于二分图就很好办了，但非二分图我们还要在同色点中找到任意一条边，我们随机一下，每个点以1/2的概率选择，如果询问得到选择的点之间有边或非选择的点之间有边就选择该集合，这样每次我们期望询问两次即可缩小点集，并且期望缩小到原来的1/2，期望询问次数logn

这样我们就能在总询问次数nlogn次解决此题

```cpp
#include<bits/stdc++.h>  
using namespace std;
typedef long long ll;
#define ri register int
int n,m,g[605][605],f[605],c[605],col[605],a[605],p,q,b[605],l,r,tmp[605],vis[605],pos,sta[605],top,ans[605],anss,i,j,k,query,ep[605];
bool flag;
int Find(int x)
{
	if(f[x]==0)
		return x;
	return f[x]=Find(f[x]);
}
void uniot(int u,int v)
{
	int x=Find(u),y=Find(v);
	if(x!=y)
		f[x]=y;
}
int Ask(int a[],int n)
{
	query++;
	if(n==0||n==1)
		return 0;
	int i;
	printf("? %d\n",n);
	for(i=1;i<=n;i++)
		printf("%d ",a[i]);
	printf("\n");
	fflush(stdout);
	int ans;
	scanf("%d",&ans);
	return ans;
}
void dfs2(int i,int s)
{
	int j;
	if(col[i]==-1)
		col[i]=s;
	else
		return;
	for(j=1;j<=n;j++)
		if(g[i][j])
			dfs2(j,s^1);
}
void Find3(int a[],int n)
{
	if(n==2)
	{
		g[a[1]][a[2]]=g[a[2]][a[1]]=1;
		col[a[1]]=col[a[2]]=-1;
		uniot(a[1],a[2]);
		return;
	}
	if(n<=4)
	{
		int i,j,t[3];
		for(i=1;i<=n;i++)
			for(j=i+1;j<=n;j++)
			{
				t[1]=a[i];
				t[2]=a[j];
				if(Ask(t,2))
				{
					g[t[1]][t[2]]=g[t[2]][t[1]]=1;
					col[t[1]]=col[t[2]]=-1;
					uniot(t[1],t[2]);
					return;
				}
			}
		return;
	}
	int i,j,p=0,t[605],e[605];
	for(i=0;;i++)
	{
		p=0;
		for(i=1;i<=n;i++)
			e[i]=rand()%2;
		for(j=1;j<=n;j++)
			if(e[j])
				t[++p]=a[j];
		if(p>=2&&Ask(t,p))
		{
			Find3(t,p);
			return;
		}
		p=0;
		for(j=1;j<=n;j++)
			if(!e[j])
				t[++p]=a[j];
		if(p>=2&&Ask(t,p))
		{
			Find3(t,p);
			return;
		}
	}
}
void dfs3(int i,int fa)
{
	int j;
	if(vis[i]==1)
	{
		for(j=top;sta[j]!=i;j--)
			ans[++anss]=sta[j];
		ans[++anss]=i;
		printf("N %d\n",anss);
		for(i=1;i<=anss;i++)
			printf("%d ",ans[i]);
		fflush(stdout);
		exit(0);
	}
	vis[i]=1;
	sta[++top]=i;
	for(j=1;j<=n;j++)
		if(g[i][j]&&j!=fa)
			dfs3(j,i);
	top--;
}
int main()
{
	srand(time(0));
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		p=q=0;
		for(j=1;j<=n;j++)
			if(Find(1)==Find(j))
				a[++p]=j;
			else
				b[++q]=j;
		int aa=Ask(a,p);
		l=1,r=q;
		while(l<r)
		{
			int mid=(l+r)/2;
			for(k=l;k<=mid;k++)
				tmp[k-l+1]=b[k];
			int ty=Ask(tmp,mid-l+1);
			for(k=l;k<=mid;k++)
				tmp[k-l+1+p]=b[k];
			for(k=1;k<=p;k++)
				tmp[k]=a[k];
			if(ty+aa!=Ask(tmp,p+mid-l+1))
				r=mid;
			else
				l=mid+1;
		}
		int s=b[l];
		l=1,r=p;
		while(l<r)
		{
			int mid=(l+r)/2;
			for(k=l;k<=mid;k++)
				tmp[k-l+1]=a[k];
			int ty=Ask(tmp,mid-l+1);
			tmp[mid-l+2]=s;
			if(Ask(tmp,mid-l+2)!=ty)
				r=mid;
			else
				l=mid+1;
		}
		uniot(s,a[l]);
		g[s][a[l]]=g[a[l]][s]=1;
	}
	memset(col,-1,sizeof(col));
	dfs2(1,0);
	p=0;
	for(i=1;i<=n;i++)
		if(col[i]==0)
			a[++p]=i;
	if(Ask(a,p))
	{
		Find3(a,p);
		dfs3(1,0);
	}
	p=0;
	for(i=1;i<=n;i++)
		if(col[i]==1)
			a[++p]=i;
	if(Ask(a,p))
	{
		Find3(a,p);
		dfs3(1,0);
	}
	printf("Y %d\n",p);
	for(i=1;i<=p;i++)
		printf("%d ",a[i]);
	fflush(stdout);
}
```


---

## 作者：DerrickLo (赞：1)

首先找到一颗 DFS 生成树。

假设我们目前到了点 $u$，那么我们找到还没有访问到的最小结点 $v$，使得有 $u\rightarrow v$ 这一条边，这个 $v$ 可以二分出来。具体地：设现在没访问到的节点所构成的序列是 $a_1\sim a_m$，如果查询 $u$ 和 $a_1\sim a_x$ 这个点集之间的边与 $a_1\sim a_x$ 这个点集之间的边的个数不同，那么 $u$ 和 $a_1\sim a_x$ 间就必然有一条边。

找到了 DFS 生成树之后，我们考虑假设 $1$ 为根，那么将深度为奇数的点染黑，深度为偶数的点染白，那么这个图是二分图的充要条件就是黑点间和白点间无边，这里可以直接询问这两个点集，如果都没有边则直接输出其中一个点集即可，如果有边我们也不难通过 $\mathcal O(n)$ 次询问找到其中的一条边。

总的询问次数是 $\mathcal O(n\log n)$ 的，可以通过此题。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,now[605],vis[605],col[605],p[605],q[605],xx,f[605],dep[605],ans[605],anscnt;
vector<int>ve[605];
void dfs(int u){
	vis[u]=1;
	int cnt=0;
	for(int i=1;i<=n;i++)if(!vis[i])cnt++;
	if(cnt==0)return;
	for(int i=1;i<=cnt;i++){
		int cntt=0;
		for(int i=1;i<=n;i++)if(!vis[i])now[++cntt]=i;
		if(cntt==0)return;
		int l=1,r=cntt,ans=cntt+1;
		while(l<=r){
			int mid=l+r>>1,x,y;
			cout<<"? "<<mid+1<<endl;
			cout<<u<<" ";
			for(int i=1;i<=mid;i++)cout<<now[i]<<" ";cout<<endl,cin>>x;
			cout<<"? "<<mid<<endl;
			for(int i=1;i<=mid;i++)cout<<now[i]<<" ";cout<<endl,cin>>y;
			if(x!=y)ans=mid,r=mid-1;
			else l=mid+1;
		}
		if(ans!=cntt+1)ve[u].emplace_back(now[ans]),dfs(now[ans]);
		else break;
	}
}
void dfs2(int u,int fa){
	col[u]=col[fa]^1,f[u]=fa,dep[u]=dep[fa]+1;
	for(int v:ve[u])dfs2(v,u);
}
signed main(){
	cin>>n;
	dfs(1),dfs2(1,0);
	int cnt1=0,cnt2=0,x=0,y=0;
	for(int i=1;i<=n;i++){
		if(col[i])cnt1++;
		else cnt2++;
	}
	if(cnt1){
		cout<<"? "<<cnt1<<endl;
		for(int i=1;i<=n;i++)if(col[i])cout<<i<<" ";cout<<endl;cin>>x;
	}
	if(cnt2){
		cout<<"? "<<cnt2<<endl;
		for(int i=1;i<=n;i++)if(!col[i])cout<<i<<" ";cout<<endl;cin>>y;
	}
	if(x==0&&y==0){
		cout<<"Y"<<" "<<cnt1<<endl;
		for(int i=1;i<=n;i++)if(col[i])cout<<i<<" ";cout<<endl;
		return 0;
	}
	cnt1=cnt2=0;
	for(int i=1;i<=n;i++)if(col[i])p[++cnt1]=i;
	for(int i=1;i<=n;i++)if(!col[i])q[++cnt2]=i;
	if(x){
		for(int i=2;i<=cnt1;i++){
			cout<<"? "<<cnt1-i+1<<endl;
			for(int j=i;j<=cnt1;j++)cout<<p[j]<<" ";cout<<endl;cin>>xx;
			if(xx!=x){
				for(int j=i;j<=cnt1;j++){
					cout<<"? "<<2<<endl<<p[i-1]<<" "<<p[j]<<endl;cin>>xx;
					if(xx==1){
						int u=p[i-1],v=p[j];
						if(dep[u]<dep[v])swap(u,v);
						while(u!=f[v])ans[++anscnt]=u,u=f[u];
						cout<<"N "<<anscnt<<endl;
						for(int k=1;k<=anscnt;k++)cout<<ans[k]<<" ";cout<<endl;
						return 0;
					}
				}
			}
		}
	}
	else{
		for(int i=2;i<=cnt2;i++){
			cout<<"? "<<cnt2-i+1<<endl;
			for(int j=i;j<=cnt2;j++)cout<<q[j]<<" ";cout<<endl;cin>>xx;
			if(xx!=y){
				for(int j=i;j<=cnt2;j++){
					cout<<"? "<<2<<endl<<q[i-1]<<" "<<q[j]<<endl;cin>>xx;
					if(xx==1){
						int u=q[i-1],v=q[j];
						if(dep[u]<dep[v])swap(u,v);
						while(u!=f[v])ans[++anscnt]=u,u=f[u];
						cout<<"N "<<anscnt<<endl;
						for(int k=1;k<=anscnt;k++)cout<<ans[k]<<" ";cout<<endl;
						return 0;
					}
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：liyixin0514 (赞：1)

# [Hidden Bipartite Graph](https://www.luogu.com.cn/problem/CF1033E)

## 题意

交互题。有一个 $n \le 600$ 的图，你可以询问至多 $20000$ 次。每次问一个点集 $S$，返回满足两个端点都在 $S$ 中的边的个数。你需要判断这个图是不是二分图，如果是，则分别输出左部和右部的点，否则**按顺序**输出任意一个奇环。

## 思路

先判断二分图。一个十分巧妙的方法是，先找出一棵生成树，然后染色，然后再拓展判断是否是二分图。这样做是因为生成树是好找的（图保证连通），而且树是特别的二分图。

现在我们任意找出一棵生成树。我们发现判断一个点 $x$ 和一个点集 $S$ 有没有连边是容易的，只需要先问 $S+x$，然后再问 $S$，然后相减。

设已经连通的点集为 $T$，剩余点集为 $S$。初始 $T=\{1\},S=2 \sim n$。

找树边的时候我们逮住 $T$ 的一个点 $x$，然后二分的方式找出和它相连的所有点，并把这些点加入 $T$，然后 $x$ 的使命就结束了了，可以把它从 $T$ 删除，因为它无法再用来更新边了。

这样每个点加入生成树最多要 $2 \log n$ 次询问，一共 $2n \log n$ 左右，大概 $10800$。

然后我们就找到了一棵生成树。然后给这棵树黑白染色，就是奇数层染黑色，偶数层染白色。然后黑、白两个点集分别查询一下内部是否有边，如果没有，那么这两个点集就是二分图的左右部，否则不存在二分图。

如果不存在二分图，我们还需要找一个奇环。只要生成树上奇数层和奇数层或者偶数层和偶数层有连边，就行成了一个奇环。环包括书上路径和非树边的那一条边。因此我们对于每个奇数层的点（当然偶数层也同理可以），采用同样的方式二分所有奇数层的点（除去它自己），先判断一下有没有连边，如果有就找到一个和它有连边的点。一共大概 $2n+2 \log n$ 次询问。完全足够。

总共询问次数大概 $2 n \log n + 2n + 2 \log n$。CF 上最大跑了 $19307$ 次。

## code

```cpp
#include<bits/stdc++.h>
//#define LOCAL
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
const int N=1000;
int n;
vector<int> res;
int st[N],top;
int m;
int dep[N],fa[N];
vector<int> to[N];
int write(vector<int> &vec,int l,int r) {
	if(r-l+1<2) return 0;
	cout<<"? "<<r-l+1<<endl;
	rep(i,l,r) cout<<vec[i]<<' ';
	cout<<endl;
	cin>>m;
	return m;
}
int write(vector<int> &vec,int l,int r,int y) {
	if(r-l+1<=0) return 0;
	cout<<"? "<<r-l+1+1<<endl;
	rep(i,l,r) cout<<vec[i]<<' ';
	cout<<y<<endl;
	cin>>m;
	return m;
}
int write(int x,int y) {
	cout<<"? 2"<<endl;
	cout<<x<<' '<<y<<endl;
	cin>>m;
	return m;
}
vector<int> del;
void solve(int u,int l,int r) {
	if(l==r) {
		int m=write(u,res[l]);
		if(m) del.push_back(l),st[++top]=res[l],to[u].push_back(res[l]),to[res[l]].push_back(u);
		return;
	}
	int m=write(res,l,r,u)-write(res,l,r);
	if(!m) return;
	int mid=(l+r)>>1;
	solve(u,l,mid);solve(u,mid+1,r);
}
vector<int> lb,rb;
int col[N];
void dfs(int u) {
	if(col[u]==1) lb.push_back(u);
	else rb.push_back(u);
	for(int v:to[u]) {
		if(col[v]) continue;
		dep[v]=dep[u]+1;fa[v]=u;
		col[v]=col[u]==1?2:1;
		dfs(v);
	}
}
bool check() {
	if(lb.size()>=2) {
		cout<<"? "<<lb.size()<<endl;
		for(int u:lb) cout<<u<<' ';
		cout<<endl;
		cin>>m;
		if(m) return 0;
	}
	if(rb.size()>=2) {
		cout<<"? "<<rb.size()<<endl;
		for(int u:rb) cout<<u<<' ';
		cout<<endl;
		cin>>m;
		if(m) return 0;
	}
	return 1;
}
bool check(vector<int> &vec,int u) {
	return write(vec,0,vec.size()-1,u)-write(vec,0,vec.size()-1);
}
bool check(int u,vector<int> &vec,int l,int r) {
	return write(vec,l,r,u)-write(vec,l,r);
}
int find(int u,vector<int> &vec,int l,int r) {
	if(l==r) return vec[l];
	int mid=(l+r)>>1;
	if(check(u,vec,l,mid)) return find(u,vec,l,mid);
	else return find(u,vec,mid+1,r);
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
//	freopen("my.out","w",stdout);
	#endif
	cin>>n;
	rep(i,2,n) res.push_back(i);
	st[++top]=1;
	while(!res.empty()) {
		int u=st[top--];
		solve(u,0,(int)res.size()-1);
		vector<int> tmp;
		sort(del.begin(),del.end());
		int op=0;
		rep(i,0,(int)res.size()-1) {
			if(op<(int)del.size()&&i==del[op]) op++;
			else tmp.push_back(res[i]);
		}
		del.clear();
		res=tmp;
	}
	col[1]=1;
	dep[1]=1;
	dfs(1);
	if(check()) {
		sort(lb.begin(),lb.end());
		int k=unique(lb.begin(),lb.end())-lb.begin();
		cout<<"Y "<<k<<endl;
		for(int j=0;j<k;j++) cout<<lb[j]<<' ';
		cout<<endl;
	}else{
		rep(i,0,(int)lb.size()-1) {
			vector<int> tmp;
			rep(j,0,i-1) tmp.push_back(lb[j]);
			rep(j,i+1,(int)lb.size()-1) tmp.push_back(lb[j]);
			if(check(tmp,lb[i])) {
				int x=find(lb[i],tmp,0,tmp.size()-1);
				vector<int> lp,lp2;
				int y=lb[i];
				if(dep[x]<dep[y]) swap(x,y);
				while(dep[x]>dep[y]) {
					lp.push_back(x);
					x=fa[x];
				}
				while(x!=y) {
					lp.push_back(x),lp2.push_back(y);
					x=fa[x],y=fa[y];
				}
				lp.push_back(x);
				cout<<"N "<<lp.size()+lp2.size()<<endl;
				for(int u:lp) cout<<u<<' ';
				for(int k=lp2.size()-1;k>=0;k--) cout<<lp2[k]<<' ';
				cout<<endl;
				return 0;
			}
		}
		rep(i,0,(int)rb.size()-1) {
			vector<int> tmp;
			rep(j,0,i-1) tmp.push_back(rb[j]);
			rep(j,i+1,(int)rb.size()-1) tmp.push_back(rb[j]);
			if(check(tmp,rb[i])) {
				int x=find(rb[i],tmp,0,tmp.size()-1);
				vector<int> lp,lp2;
				int y=rb[i];
				if(dep[x]<dep[y]) swap(x,y);
				while(dep[x]>dep[y]) {
					lp.push_back(x);
					x=fa[x];
				}
				while(x!=y) {
					lp.push_back(x),lp2.push_back(y);
					x=fa[x],y=fa[y];
				}
				lp.push_back(x);
				cout<<"N "<<lp.size()+lp2.size()<<endl;
				for(int u:lp) cout<<u<<' ';
				for(int k=lp2.size()-1;k>=0;k--) cout<<lp2[k]<<' ';
				cout<<endl;
				return 0;
			}
		}
	}
}
```

---

## 作者：happybob (赞：0)

题意：

交互。

有一个 $n$ 个点 $m$ 条边的无向简单联通图，你不知道除了 $n$ 外的任何其他信息，每次询问选择一个点集 $S$，交互库返回有多少条边的两端都在 $S$ 内，你需要在至多 $2 \times 10^4$ 次询问内判定图是否为二分图。如果是，你需要求出黑白染色结果，若不是，你需要求出图的一个奇环。交互库可能自适应。

$1 \leq n \leq 600$，$0 \leq m \leq \dfrac{n(n-1)}{2}$。

解法：

不可能将整个图的形态求出。

但是对于图上的这类问题，常见做法是能不能考虑 DFS 生成树。

事实上，我们可以在 $O(n \log n)$ 次询问内求出图的一棵 DFS 生成树。具体地，维护目前未被访问过的点集，每次往下 DFS 时二分找到集合中第一个和其有边的点即可。

然后对树进行黑白染色，考虑询问黑白内部是否有边即可判定是否为二分图。若不是，容易直接求出同色的一条边，在树上选这条边的端点对应路径就找到了一个奇环。

范围很松，我的实现最坏询问次数不超过 $12000$。

[Submission Link.](https://codeforces.com/problemset/submission/1033/290510157)

---

## 作者：Mashu77 (赞：0)

对原图建立生成树，判断深度奇偶性相同的点是否有连边。

但建树的复杂度已经是 
$O
(
n^
2
)$，且难以优化。注意到条件仅对深度有要求，那么尝试忽略树的形态，仅找出所有点的深度。

可以得出这样一个算法：先找到深度为 
$0$
 的点集（即 $\{
1
\}$），然后找出所有与其有连边的点，即为深度为 
$2$
 的点集。依次类推。

考虑一下找出 
$S$
 中与 
$T$
 有连边的所有点的复杂度。显然有一个 
$O
(
|
S
|
)$
 的做法，但不够。我们需要其与答案个数有关，便于均摊。那么考虑分治。判断 
$S$
 与 
$T$
 是否有连边，可以通过 
$a
s
k
(
S
∪
T
)
−
a
s
k
(
S
)
−
a
s
k
(
T
)$。

那么就通过 
$O
(
n
\log
n
)$
 得出了所有点的深度。于是可以判断二分图。还有一个问题是，若不是二分图，怎么找到奇环？

不妨设 
$S$
 为所有偶深度点的集合，且 
$a
s
k
(
S
)>
0$。那么通过枚举所有 
$x
∈
S$，可以找出一个与 
$S
∖
\{
x
\}$
 有连边的点。再枚举一遍，就找到一条边 
$(
x
,
y
)$。那么再找到它们到根的路径上的所有点即可，也就是找父亲。这显然可以通过二分。于是此题得解。

---

## 作者：Dovish (赞：0)

## 题解
首先非常简单的一点是，我们可以用两个询问来获取一个点到一个集合中的连边情况。

其次，我们肯定是没法直接把图建出来的，我们只用选择一些关键的边来建。

那我们不妨先把二分图染色（$\text{bfs}$ 写法）的过程表示出来，注意染过色的点就不再连边了。

那所以我们要建的边数是 $O(n)$ 的，只不过我们不能一个一个去枚举这个点是否和其他点有连边，因为这样是有 $O(n^2)$ 次询问的。我们用一种类似分治的方法，根据上文第一点，我们判断在这个集合内是否有连边。若有就向下递归直到集合大小为1，直接询问二者是否有连边。这样询问就是 $O(n\log n)$ 次的了。

注意我们这样建边是建出来一个二分图（严格来说是一棵树），并没有考虑集合内部的连边情况。

那么此时，这个图不是二分图的充要条件就是两个集合内部存在连边。

然后如果是二分图，就输出其中一个集合的大小及其元素。如果不是，要输出一个奇环。

我们不妨先在内部有连边的集合内考虑找到连接两个点的一条边。这一步类似建图的过程，我们只要找到第一个就可结束程序，确保询问次数不会太多。

那我们找到这一部中相连的两点后，就可以钦定其中一点，然后去 $\text{dfs}$ 找另外一个点，然后输出路径即可。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,inf=1e9,mod=998244353;
int n,head[N],tot;
struct sx
{
	int next,to;
}e[N*2];
void add(int u,int v)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	head[u]=tot;
}
int c[N],vis[N];
map<int,set<int>>q;;
queue<int>s;
int visedge[N];
stack<int>ans;
void getans(int u,int zd)
{
	visedge[u]=1;
	ans.push(u);
	if(u==zd)
	{
		cout<<"N "<<ans.size()<<endl;
		while(ans.size())
		{
			cout<<ans.top()<<" ";
			ans.pop();
		}
		exit(0);
	}
	for(int i=head[u];i;i=e[i].next)
	if(!visedge[e[i].to])
	{
		getans(e[i].to,zd);
	}
	ans.pop();
}
int ls[N],res;
void build(int l,int r,int u)
{
	if(l==r)
	{
		cout<<"? 2"<<endl<<u<<" "<<ls[l]<<endl;
		int y;
		cin>>y;
		if(y)
		{
			add(u,ls[l]);
			add(ls[l],u);
			c[ls[l]]=-c[u];
			q[c[ls[l]]].insert(ls[l]);
			s.push(ls[l]);
			vis[ls[l]]=1;
		}
		return ;
	}
	int a,b;
	cout<<"? "<<r-l+1<<endl;
	for(int i=l;i<=r;i++)cout<<ls[i]<<" ";cout<<endl;
	cin>>a;
	cout<<"? "<<r-l+1+1<<endl;
	for(int i=l;i<=r;i++)cout<<ls[i]<<" ";cout<<u<<endl;
	cin>>b;
	if(a==b)return;
	int mid=(l+r)/2;
	build(l,mid,u);
	build(mid+1,r,u);
}//分治建图
signed main()
{
	cin>>n;
	if(n==1)
	{
		cout<<"Y 1"<<endl;
		cout<<1;return 0;
	}//注意特判只有1个点的情况
	c[1]=-1;
	q[c[1]].insert(1);
	vis[1]=1;
	s.push(1);
	while(s.size())
	{
		int u=s.front();
		s.pop();
		if((int)(q[1].size()+q[-1].size())==n)break;
		res=0;
		for(int i=1;i<=n;i++)
		if(!vis[i])ls[++res]=i;
		if(res>=1)build(1,res,u);
	}//bfs染色
	int last1,last_1;
	cout<<"? "<<q[1].size()<<endl;
	for(auto u:q[1])cout<<u<<" ";cout<<endl;
	cin>>last1;
	cout<<"? "<<q[-1].size()<<endl;
	for(auto u:q[-1])cout<<u<<" ";cout<<endl;
	cin>>last_1;
  //获取集合内部的连边情况
	if(!last1&&!last_1)
	{
		cout<<"Y "<<q[1].size()<<endl;
		for(auto u:q[1])cout<<u<<" ";
		return 0;
	}
	if(last1)
	{
		if(q[1].size()>1)
		for(auto u:q[1])
		{
			cout<<"? "<<q[1].size()-1<<endl;
			for(auto v:q[1])if(v!=u)cout<<v<<" ";cout<<endl;
			int y;cin>>y;
			if(y!=last1)//u这个点向其集合内的其他点有连边
			{
				for(auto v:q[1])
				if(v!=u)
				{
					cout<<"? "<<2<<endl;
					cout<<u<<" "<<v<<endl;
					int x;
					cin>>x;
					if(x)//u连向v
					{
						getans(u,v);
						return 0;
					}
				}
			}
		}	
	}
	else
	{
		if(q[-1].size()>1)for(auto u:q[-1])
		{
			cout<<"? "<<q[-1].size()-1<<endl;
			for(auto v:q[-1])if(v!=u)cout<<v<<" ";cout<<endl;
			int y;cin>>y;
			if(y!=last_1)
			{
				for(auto v:q[-1])
				if(v!=u)
				{
					cout<<"? "<<2<<endl;
					cout<<u<<" "<<v<<endl;
					int x;
					cin>>x;
					if(x)
					{
						getans(u,v);
						return 0;
					}
				}
			}
		}	
	}
	return 0;
}
```

---

## 作者：Aonynation (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF1033E "题目链接")
**[my cnblogs](https://www.cnblogs.com/Oier-GGG/p/16496384.html)**

这题看上去一脸不可做，对，我看什么题都不可做。。。

然后瞄一眼题解，发现一个小 $\tt Trick$ ：

**判定二分图可以先拉出一个生成树，対生成树进行染色然后看相同颜色内有没有连边。**

所以现在的第一步是拉出一个生成树。

首先，我们先把题目中要求的交互函数写出来，我用一个 $\tt vector$ 记录查询的点集。

同时在我自己测试时发现可能会询问重复的点集，所以用一个 $\tt map$ 来记录已经查过的答案。

```cpp
inline int ask(std::vector<int> chose) {
  if (chose.size() == 1) return 0;
  std::sort(chose.begin(), chose.end());
  if (ma[chose]) return ma[chose];
  printf("? ");
  write(chose.size()), Enter;
  for (int t : chose) write(t), quad; Enter;
  fflush(stdout);
  int ret; read(ret); 
  ma[chose] = ret; return ret;
}
```

接下来就按照生成树的角度进行思考。

首先我们需要并查集，这个非常简单不在累述，然后我们会发现要进行 $n-1$ 次连边操作。

对于每个连边操作，我们都要找到一个和根节点所在集合有边的点 $p$ 然后连边。

那么怎么找到这样的点 $p$ 呢？这里有一个显然的结论：

> 对于点集 $A$ 和 $B$ ，如果 $A$ 和 $B$ 中的点有边相连，那么满足 $ask(A)+ask(B)<ask(A\cup B)$


运用这个结论，我们就可以找到上文所讲的 $p$ 。


我们令根节点所在的点集为 $A$ ，其他的点构成的点集为 $B$ 。

同时我们令上文结论中的查询方式为 $check(A,B)$ ，及调用 $check(A,B)$ 就可以知道是否有边。

因为询问次数控制较为严格，我们考虑 $O(n\log n)$ 的较大常数做法。

直接能够想到的是二分做法：（假设 $B$ 集合的大小为 $L$）

* 我们把 $B$ 按照大小平均分成两个集合 $B_1$ 和 $B_2$ 。

* 分别查询 $check(B_1,A)$ 和 $check(B_2,A)$ ，如果一个为真则取为真的，否则任意取一个。

* 不难发现，最后集合 $B$ 只会剩下一个节点，那个节点就是 $p$ 。复杂度 $O(\log n)$ 。

找到了 $p$ ，我们还要知道 $p$ 和根节点集合中的哪一个点有边，按照相似的方法即可。

只不过此次查询的 $check$ 操作更为简洁，复杂度还是 $O(\log n)$ 。

重复 $n-1$ 次上述的操作，我们就找到了一个生成树，接下来对树染色非常简单。

我们令染为白色和黑色的点集分别为 $white$ 和 $black$ ，进行一次 $check(white,black)$ 即可判断二分图。

如果是二分图，那么接下来非常简单，现在来讨论非二分图的情况。

我的做法是随机化，每一次对集合进行一次 $\tt random\_shuffle$ ，然后取 $\frac{L}{2}$ 。

进行查询，如果可以的话让点集大小直接减半，~~不知道对不对，反正我过了~~

所以这样下来，复杂度约为 $O(n\log n)$ 带上 $3\sim 5$ 倍常数，可以通过。

具体可以看代码：
```cpp
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <string>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
#define quad putchar(' ')
#define Enter putchar('\n')

using std::abs;
using std::pair;
using std::string;
using std::make_pair;

// #define int long long

template <class T> void read(T &a);
template <class T> void write(T x);

template <class T, class ...rest> void read(T &a, rest &...x);
template <class T, class ...rest> void write(T x, rest ...a);

const int N = 1005;

int n, root_edge, tot, ok[N], edgetot, col[N];
int deep[N], fa[N][15], sta[N], top;
std::vector <int> now, rt, white, black;
std::vector <int> dis[N];

std::map <std::vector<int>, int> ma;

struct Edge {
  int x, y;
  Edge (int _x = 0, int _y = 0) {x = _x; y = _y;}
} edge[N * N];
namespace UFST {
int fa[N], siz[N];
inline int find(int);
inline void rebuild(int);
inline void merge(int, int);
}

inline int ask(std::vector<int> chose) {
  if (chose.size() == 1) return 0;
  std::sort(chose.begin(), chose.end());
  if (ma[chose]) return ma[chose];
  printf("? ");
  write(chose.size()), Enter;
  for (int t : chose) write(t), quad; Enter;
  fflush(stdout);
  int ret; read(ret); 
  ma[chose] = ret; return ret;
}
inline bool check(int l, int r) {
  now.clear();
  for (int i = l; i <= r; i++) now.emplace_back(ok[i]);
  int edge1 = ask(now);
  for (int t : rt) now.emplace_back(t);
  int edge2 = ask(now);
  if (edge1 + root_edge < edge2) return true;
  return false;
}
inline bool check2(int l, int r, int p) {
  now.clear();
  for (int i = l; i <= r; i++) now.emplace_back(ok[i]);
  int edge1 = ask(now);
  now.emplace_back(p);
  int edge2 = ask(now);
  if (edge1 < edge2) return true;
  return false;
}

inline void DFS(int, int);
inline int LCA(int, int);

signed main(void) {
  read(n); UFST::rebuild(n);
  if (n == 1) {
    printf("Y 1 \n1");
    return 0;
  }
  now.emplace_back(1); 
  root_edge = ask(now);
  rt = now;
  for (int edgenum = 1, rootteam; edgenum < n; edgenum++) {
    root_edge = ask(rt);
    tot = 0, rootteam = UFST::find(1);
    for (int i = 1; i <= n; i++)
      if (UFST::find(i) != rootteam) ok[++tot] = i;
    int left = 1, right = tot, mid;
    while (left < right) {
      mid = (left + right) / 2;
      if (check(left, mid)) right = mid;
      else left = mid + 1; 
    }
    int point = ok[left];
    tot = 0;
    for (int t : rt) ok[++tot] = t;
    left = 1; right = tot;
    while (left < right) {
      mid = (left + right) / 2;
      if (check2(left, mid, point)) right = mid;
      else left = mid + 1;
    }
    UFST::merge(ok[left], point);
    edge[++edgetot] = Edge(ok[left], point);
    rt.emplace_back(point);
  }
  for (int i = 1; i <= edgetot; i++) {
    Edge p = edge[i];
    dis[p.x].emplace_back(p.y);
    dis[p.y].emplace_back(p.x);
  }
  DFS(1, 0);
  for (int i = 1; i <= n; i++) {
    if (col[i] == 0) white.emplace_back(i);
    else black.emplace_back(i);
  }
  // for (int num : white) write(num), quad; Enter;
  // for (int num : black) write(num), quad; Enter;
  int edge1 = ask(white), edge2 = ask(black);
  // printf("!!!");write(white.size(), edge1);
  int p1, p2;
  if (edge1 == 0 && edge2 == 0) {
    printf("Y "); write(white.size()), Enter;
    for (int num : white) write(num), quad; Enter;
    return 0;
  } else if (edge1 != 0) {
    tot = 0;
    for (int num : white) ok[++tot] = num;
    while (1) {
      now.clear();
      std::random_shuffle(ok + 1, ok + 1 + tot);
      for (int i = 1; i * 2 - 1 <= std::max(tot, 3); i++) now.emplace_back(ok[i]);
      // for (int t : now) write(t), quad; Enter; write(ask(now)); Enter;
      if (ask(now)) { 
        if (now.size() == 2) {p1 = ok[1]; p2 = ok[2]; break;}
        tot = (tot + 1) / 2;
      }
    }
  } else if (edge2 != 0) {
    tot = 0;
    for (int num : black) ok[++tot] = num;
    while (1) {
      now.clear();
      std::random_shuffle(ok + 1, ok + 1 + tot);
      for (int i = 1; i * 2 - 1 <= tot; i++) now.emplace_back(ok[i]);
      if (ask(now)) { 
        if (now.size() == 2) {p1 = ok[1]; p2 = ok[2]; break;}
        tot = (tot + 1) / 2;
      }
    }
  }
  printf("N "); 
  int lca = LCA(p1, p2);
  write(deep[p1] + deep[p2] - 2 * deep[lca] + 1); Enter;
  while (1) {
    write(p1), quad;
    p1 = fa[p1][0];
    if (p1 == lca) break;
  } 
  while (1) {
    sta[++top] = p2;
    if (p2 == lca) break;
    p2 = fa[p2][0];
  }
  while (top) write(sta[top]), quad, top --; Enter;
  return 0;
}

inline void DFS(int now, int father) {
  deep[now] = deep[father] + 1;
  col[now] = 1 - col[father];
  for (int i = 0; i <= 12; i++) fa[now][i + 1] = fa[fa[now][i]][i];
  for (int t : dis[now]) {
    if (t == father) continue;
    fa[t][0] = now;
    DFS(t, now);
  }
}
inline int LCA(int x, int y) {
  if (deep[x] < deep[y]) std::swap(x, y);
  for (int i = 13; i >= 0; i--)
    if (deep[fa[x][i]] >= deep[y]) x = fa[x][i];
  if (x == y) return x;
  for (int i = 13; i >= 0; i--)
    if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
  return fa[x][0];
}

namespace UFST {
inline int find(int x) {
  return x == fa[x] ? x : fa[x] = find(fa[x]);
}
inline void rebuild(int n) {
  for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
}
inline void merge(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return ;
  if (siz[x] > siz[y]) std::swap(x, y);
  fa[x] = y; siz[y] += siz[x];
}
}

template <class T> void read(T &a) {
  int s = 0, t = 1;
  char c = getchar();
  while (!isdigit(c) && c != '-') c = getchar();
  if (c == '-') c = getchar(), t = -1;
  while (isdigit(c)) s = s * 10 + c - '0', c = getchar();
  a = s * t;
}
template <class T> void write(T x) {
  if (x == 0) putchar('0');
  if (x < 0) putchar('-'), x = -x;
  int top = 0, sta[50] = {0};
  while (x) sta[++top] = x % 10, x /= 10;
  while (top) putchar(sta[top] + '0'), top --;
  return ;
}

template <class T, class ...rest> void read(T &a, rest &...x) {
  read(a); read(x...);
}
template <class T, class ...rest> void write(T x, rest ...a) {
  write(x); quad; write(a...);
}
```
``

---

