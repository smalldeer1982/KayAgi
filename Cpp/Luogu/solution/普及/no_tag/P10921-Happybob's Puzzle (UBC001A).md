# Happybob's Puzzle (UBC001A)

## 题目描述

给定一棵有 $n$ 个点的树，每条边的长度都是 $1$，你需要构造一个 $1\sim n$ 的排列 $p$，满足以下条件：

- 对于每个满足 $1\le i<n$ 的整数 $i$，点 $p_i$ 到点 $p_{i+1}$ 的简单路径长度为奇数。

如果有解，请输出字典序最小的排列 $p$；否则，输出 $-1$。

## 说明/提示

**数据范围**

对于所有数据，都有 $1\le t,n,\sum n\le 10^5$，保证有 $1 \leq u, v \leq n$ 且 $u \neq v$。保证输入构成一棵树。其中 $\sum n$ 表示所有测试数据的 $n$ 的总和。

## 样例 #1

### 输入

```
2
3
1 2
2 3
7
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
1 2 3
-1```

# 题解

## 作者：Autumn_Rain (赞：6)

### 思路

- 以 $1$ 为根搜索一遍，把深度为奇数的放入集合 $A$，偶数的放入集合 $B$。

- 发现当 $x,y$ 之间距离为奇数时，当且仅当 $x\in A,y\in B$ 或者 $x\in B,y\in A$。


- 因此给两个集合排个序再轮流取数。发现无法轮流取的时候就输出 $-1$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
//建树 
int T,n,u,v,h[N],d[N],cnt;
struct node{int nxt,to;}e[N];
void add(int u,int v){ 
    e[++cnt].nxt=h[u];
    e[cnt].to=v;
    h[u]=cnt;
}
//遍历整棵树 
void dfs(int u,int fa){
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		d[v]=d[u]+1;//d代表节点深度 
		dfs(v,u);
	}
} 
//两个集合，小根堆维护 
priority_queue<int,vector<int>,greater<int> >S1;
priority_queue<int,vector<int>,greater<int> >S2;
void out1(){//先取第一个集合 
	for(int i=1;i<=n;i++){
		if(i&1){cout<<S1.top()<<" ";S1.pop();continue;}
		else{cout<<S2.top()<<" ";S2.pop();continue;}
	} 
	cout<<"\n";return;
}
void out2(){//先取第二个集合 
	for(int i=1;i<=n;i++){
		if(i&1){cout<<S2.top()<<" ";S2.pop();continue;}
		else{cout<<S1.top()<<" ";S1.pop();continue;}
	} 
	cout<<"\n";return;
}
void clear(){//清空队列 
	while(!S1.empty())S1.pop();
	while(!S2.empty())S2.pop();
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;cnt=0;//清空 
		memset(e,0,sizeof(e));
		memset(h,0,sizeof(h));
		memset(d,0,sizeof(d));
		clear();
		//输入建树 
		for(int i=1;i<n;i++){cin>>u>>v;add(u,v);add(v,u);}
		d[1]=0;dfs(1,0);
		//如果深度奇数放入S1,否则S2 
		for(int i=1;i<=n;i++){
			if(d[i]&1)S1.push(i);//x&1==1代表x是奇数，否则偶数 
			else S2.push(i);
		}
		//两个集合大小 
		int cnt1=S1.size(),cnt2=S2.size();
		if(n&1){//n奇数，无法使两个集合一样多 
			if(max(cnt1,cnt2)-min(cnt1,cnt2)!=1){cout<<"-1\n";continue;}
			//模拟一下发现，cnt1和cnt2只能相差1，不然不可能轮流取
			//且必须先从多的那个集合开始取	
			if(cnt1>cnt2){out1();continue;}
			else{out2();continue;}	
			continue;
		}
		//否则n为偶数时 
		if(cnt1!=cnt2){cout<<"-1\n";continue;}//不相等就无法轮流取 
		out2();continue;//因为d[1]=0，且1是字典序最小的节点，所以从集合2开始输出 
	}
	return 0;
}
```

---

## 作者：luxiaomao (赞：2)

## [P10921](https://www.luogu.com.cn/problem/P10921) 简单思维题

## Problem

给定一棵有 $n$ 个点的树，每条边的长度都是 $1$，你需要构造一个 $1\sim n$ 的排列 $p$，满足以下条件：

- 对于每个满足 $1\le i<n$ 的整数 $i$，点 $p_i$ 到点 $p_{i+1}$ 的简单路径长度为奇数。

如果有解，请输出字典序最小的排列 $p$；否则，输出 $-1$。

## Solution

祭出黑白染色大法，发现树上两点的距离如果是奇数，那么这两个点的颜色肯定不同。

最后的解定然是黑、白、黑、白……的形式。

那么我们先将树进行黑白染色，统计黑点和白点各有多少个。如果这两个数量之差超过 $1$，显然无解，输出 `-1`。

如果有解，我们特判：

- 黑点数量多一个，显然是黑、白、黑、白、黑的形式。

- 白点数量多一个，显然是白、黑、白、黑、白的形式。

- 黑白点一样多，我们看“编号最小的黑点”和“编号最小的白点”哪个编号小就用哪个。

对于相同颜色的点，我们优先选取编号更小的，这里笔者用了小根堆 `priority_queue` 维护，可读性强，用排序之类的也是可以的。

时间复杂度 $O(Tn \log n)$，可以通过本题。

## Code

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;

int T,n;

struct edge{int v,nex;}e[2*N];
int tot,head[N];
void add(int u,int v)
{
	e[++tot].v = v;
	e[tot].nex = head[u];
	head[u] = tot;
}

int c0,c1;
int c[N];
void dfs(int las,int u,int now)
{
	c[u] = now;
	if(now)c1++;
	else c0++;
	for(int i = head[u];i;i = e[i].nex)
	{
		int v = e[i].v;
		if(v == las)continue;
		dfs(u,v,1-now);
	}
}

priority_queue<int,vector<int>,greater<int> > q0,q1;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)head[i] = 0;tot = 0;
		c0 = c1 = 0;
		for(int i = 1;i < n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v),add(v,u);
		}
		dfs(0,1,0);
		if(abs(c0-c1) > 1)
		{
			printf("-1\n");
			continue;
		}
		for(int i = 1;i <= n;i++)
		{
			if(c[i])q1.push(i);
			else q0.push(i);
		}
		int now;
		if(c0 == c1)now = q1.top() < q0.top();
		if(c0 > c1)now = 0;
		if(c0 < c1)now = 1;
		while(!q0.empty() || !q1.empty())
		{
			if(now == 0)
			{
				printf("%d ",q0.top());
				q0.pop();
			}
			else
			{
				printf("%d ",q1.top());
				q1.pop();
			}
			now = 1-now;
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：dabenBbx (赞：1)

## 题目入口：[原题](https://www.luogu.com.cn/problem/P10921)。


### 题意

  求一个序列 $A$ 中，$A _ {n}$ 到 $A _ {n} + 1$ 在这个树上的距离都为奇数。如果有这样的树，就按字典序大小，输出这个合法序列；反则输出负一。

### 分析

分析这道题，我们可以发现如想要两点距离为奇数，则这两点间的深度一定不在一层以及相隔偶数层。只有在奇数层的距离时，才会两点间是奇数。

所以我们先存图排列，以一为根算出每个点的深度，并判断是奇数层还是偶数层。统计完后要对奇数层和偶数层进行由小到大排序，再轮番输出即可。但如果奇数层点数与偶数层点数相差超过一，则本题就无解了，因为奇偶肯定要轮番输出，相差超过一就一定会有奇奇或偶偶在一起，如此便无解了。


 >注意：合法时要判断奇数多还是偶数多，哪个多就先输出，再交替输出另一个即可。

### AC 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int t,n,he[200005],cnt,deep[200005],cj[200005],co[200005],jdd,odd;
struct edge{
	int to,nxt;
}e[200005];
inline void add(int u,int v){
	e[++cnt].nxt = he[u];
	he[u] = cnt;
	e[cnt].to = v;
}
inline void dfs(int u,int fa){
//	cout<<u<<" "<<fa<<endl;;
	deep[u] = deep[fa] + 1;
	if(deep[u] != 0) if(deep[u]%2 == 0) co[++odd] = u;
    else cj[++jdd] = u;
	for(int i = he[u];i;i = e[i].nxt){
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v,u); 
	}

} 
int main(){
	cin>>t;
	while(t--){
		memset(deep,0,sizeof deep);
		memset(he,0,sizeof he);
		cnt = 0;
		cin>>n;
		for(int i = 1;i < n;i++){
			int x,y;
			cin>>x>>y;
			add(x,y);
			add(y,x);
		}
		jdd = 0,odd = 0;
		dfs(1,0);
		if(abs(odd - jdd) > 1){
			cout<<-1<<"\n";
		}else{
			sort(co+1,co+odd+1);
			sort(cj+1,cj+jdd+1);
			if(odd>jdd){
				cout<<co[1]<<" ";
				odd--;
				for(int i = 1;i <= odd;i++){
				   cout<<cj[i]<<" "<<co[i+1]<<" "; 
			    }
			    cout<<"\n";
	    	}else
	    	if(jdd>odd){
	    		cout<<cj[1]<<" ";
	    		jdd--;
	    		for(int i = 1;i <= jdd;i++){
	    			cout<<co[i]<<" "<<cj[i+1]<<" ";
				}
				cout<<"\n";
			}else{
				for(int i = 1;i <= jdd;i++){
					cout<<cj[i]<<" "<<co[i]<<" ";
				}
				cout<<"\n";
			}
	}
}
	return 0;
} 
```

---

## 作者：ZYXzyx1006 (赞：1)

## 题意与思路
这道题有构造两字，说明此题答案具有一定的规律。仔细观察数据，发现以节点 $1$ 为根进行 BFS 操作，用红蓝二色对树逐层染色，红色层只能前往蓝色层，蓝色层只能前往红色层。

故将双色节点的编号分别储存，进行排序后再交替输出即可完成此题。特别地，两色节点数量之差大于 $1$ 时无解。若两色节点数量之差等于 $1$，则要先输出数量多的那种颜色的节点。

具体注释见代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t,q=1,p=0;
int trji[114514],trou[114514],t1,t2;
vector<int> v[114514];
bool ff[114514];
struct p1 {
	int num,c;
} q1[114514],tr[114514];
int main() {
	cin>>t;
	for(int i1=1; i1<=t; i1++) {

		memset(trji,0,sizeof(trji));
		memset(trou,0,sizeof(trou));
		memset(ff,0,sizeof(ff));
		
		t1=t2=0;
		cin>>n;

		for(int j=1,x,y; j<=n-1; j++) {//建树 
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		p=0,q=1;
		q1[p].num=1,q1[p].c=1;//c 以 1  0 表示两种颜色   num 记录节点编号 
		while (p<q) {//宽搜染色 
			p1 node=q1[p];
			for (int i=0; i<v[node.num].size(); i++) {
				int f=v[node.num][i];
				if(!ff[f]) {
					ff[f]=1; 
					q1[q].num=f;
					q1[q].c=(q1[p].c ^ 1);//异或操作对颜色编号取反 
					tr[f]=q1[q];
					q++;
				}
			}

			p++;
		}
		for(int i=1; i<=n; i++) {//储存节点编号 
			if(tr[i].c==1)
				trji[++t1]=tr[i].num;
			else
				trou[++t2]=tr[i].num;
		}
		if(abs(t1-t2)>=2) {
			//cout<<t1
			cout<<-1;
		} else {

			//排序输出 
			sort(trji+1,trji+1+t1);
			sort(trou+1,trou+1+t2);
			int kk=max(t1,t2);
			if(t1>t2) {
				cout<<trji[1]<<" ";
				for(int i=1; i<=t2; i++)
					cout<<trou[i]<<" "<<trji[i+1]<<" ";
			}
			if(t2>t1) {
				cout<<trou[1]<<" ";
				for(int i=1; i<=t1; i++)
					cout<<trji[i]<<" "<<trou[i+1]<<" ";
			}
			if(t2==t1) {
				for(int i=1; i<=t2; i++)
					cout<<trji[i]<<" "<<trou[i]<<" ";
			}
		}
		cout<<endl;
		for(int i=1; i<=n; i++) {
			v[i].clear();
		}
	}
}
```

---

## 作者：mediocre_ (赞：1)

刚看到题目就可以想到标记每个点的深度以此来判断每个点距离的奇偶。

也就是每个点的深度相减的绝对值看模 $2$ 是否为 $1$ 如果是，那么这两个点的距离就为奇数；反之，这两个点的距离就为偶数。

然后用一个深搜来枚举所有可以的情况。

于是就出现了我们的TLE代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 6;
int T, n, dep[N], vis[N], b[N], ok;
vector <int> p[N];
void dfs(int x, int deep) {
	dep[x] = deep;
	for (int i = 0; i < p[x].size(); ++i) {
		int to = p[x][i];
		if (to == 1 || dep[to]) continue;
		dfs(to, deep + 1);
	}
}
void made(int x, int deep) {
	/*
	for (int i = 1; i <= deep; ++i)
		printf("%d ", b[i]);
	puts("");
	*/
	if (ok) return ;
	if (deep == n) {
		ok = 1;
		for (int i = 1; i <= n; ++i)
			printf("%d ", b[i]);
		puts("");
		return ;
	}
	for (int i = 1; i <= n; ++i) {
		int now = dep[x];
		int to = dep[i];
		if ((!(abs(now - to) & 1) && x) || vis[i]) continue ;
		// printf(".\n");
		vis[i] = 1;
		b[deep + 1] = i;
		made(i, deep + 1);
		vis[i] = 0;
	}
}
int main() {
    scanf("%d", &T);
    while (T--) {
		scanf("%d", &n);
		memset(vis, 0, sizeof(vis));
		memset(dep, 0, sizeof(dep));
		memset(b, 0, sizeof(b));
		ok = 0;
		for (int i = 1; i <= n; ++i) p[i].clear();
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			p[u].push_back(v);
			p[v].push_back(u);
		}
		dfs(1, 0);
		//for (int i = 1; i <= n; ++i) printf("%d ", dep[i]);
		//puts("");
		made(0, 0);
		if (!ok) puts("-1");
	}
    return 0;
}
```

于是我们只能另寻他法。

因为我们以深度相减的绝对值来判断距离是奇还是偶。

那小学学过的性质就搬上来。

奇偶性相同相减为偶数，奇偶性不同相减为奇数。

所以我们可以直接输出一个深度为奇数的，一个深度为偶数的或一个深度为偶数的，一个深度为奇数的。

但是如果奇数的深度减去偶数的深度的绝对值 $>1$ 的话，就无法构造这样的一个排列了（因为肯定会有两个奇偶性相同的数在这个构造的序列里相邻）。

那么，这道题就解决了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 6;
int T, n, dep[N], vis[N], b[N], ok, ji[N], ou[N];
vector <int> p[N];
void dfs(int x, int deep) {
	dep[x] = deep;
	for (int i = 0; i < p[x].size(); ++i) {
		int to = p[x][i];
		if (to == 1 || dep[to]) continue;
		dfs(to, deep + 1);
	}
}
int main() {
    scanf("%d", &T);
    while (T--) {
		scanf("%d", &n);
		memset(dep, 0, sizeof(dep));
		memset(ji, 0, sizeof(ji));
		memset(ou, 0, sizeof(ou));
		for (int i = 1; i <= n; ++i) p[i].clear();
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			p[u].push_back(v);
			p[v].push_back(u);
		}
		dfs(1, 0);
		int j = 0, o = 0;
		for (int i = 1; i <= n; ++i)
			if (dep[i] & 1) ++j, ji[j] = i;
			else ++o, ou[o] = i;
		if (abs(j - o) > 1) puts("-1");
		else if (j > o) {
			o = j = 0;
			for (int i = 1; i <= n; ++i)  {
				if (i & 1) printf("%d ", ji[++j]);
				else printf("%d ", ou[++o]);
			}
			puts("");
		}
		else {
			o = j = 0;
			for (int i = 1; i <= n; ++i)  {
				if (!(i & 1)) printf("%d ", ji[++j]);
				else printf("%d ", ou[++o]);
			}
			puts("");
		}
	}
    return 0;
}
```

---

## 作者：Anins (赞：1)

## [Happybob's Puzzle (UBC001A)](https://www.luogu.com.cn/problem/P10921)

### 思路
黑白染色：对树上的点进行染色，相邻点颜色不同，那么颜色不同的点间的距离一定是奇数。也就是说要求排列中的任意相邻点的颜色不同。


---


思路有了还需要解决以下问题：

- 怎么判断是否有解？

若黑色和白色点数量之差不大于 $1$，那么就有解。否则排列内会有相邻点颜色相同，即它们之间的距离为偶数。

- 怎么输出？

用两个优先队列交替从小到大输出，若两个颜色的点数量不同，从点数量多的队列开始输出，否则先输出第一个点序号小的。

---

时间复杂度：$O(Tn\log n)$

---

代码内有详细注释可以参照。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n; //点数 
priority_queue<ll, vector<ll>, greater<ll>> cl[2]; //用以记录两种颜色集合有的点 
vector<ll> e[1000005]; //邻接表存图 
void clear() {
	for(int i=1; i<=n; i++) e[i].clear();
	while(!cl[0].empty()) cl[0].pop(); //优先队列的清空 
	while(!cl[1].empty()) cl[1].pop();
}
void dfs(ll u, ll fa, ll nowcl) {
	cl[nowcl].push(u); //把当前元素放入所属队列 
	for(ll v:e[u]) { //相当于枚举 u 的出边所到达的点的编号 
		if(v==fa) continue;
		dfs(v, u, 1-nowcl);
	}
}
void solve() {
	ll u, v;
	cin >> n;
	clear(); //多测别忘了清空 
	for(int i=1; i<n; i++) {
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0, 0);
	ll k=0, check=cl[0].size()-cl[1].size();
	if(abs(check)<=1) { //两个队列内元素数量差不大于 1 则可以构成序列 
		//确定从哪个队列开始 
		if(cl[0].size()<cl[1].size()) k=1;
		else if(!cl[0].empty()&&!cl[1].empty()&&cl[1].top()<cl[0].top()) k=1;
		//按顺序输出 
		while(cl[k].size()) {
			cout << cl[k].top() << " ";
			cl[k].pop();
			k=1-k;
		}
	} else {
		cout << -1;
	}
}
int main(){
	ios::sync_with_stdio(0);
	ll t;
	cin >> t;
	while(t--) {
		solve();
		cout << endl;
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：1)

考虑什么时候路径长度为奇数。

我们发现：钦定 $1$ 为根，对于两个深度相同的店，路径长度为偶数，进一步，我们发现路径长度为奇数当前仅当两个节点深度奇偶性不同。

我们证明 $s$ 到 $t$ 这一点。假设 $s$ 深度为 $a$，$lca$ 深度为 $b$，$t$ 深度为 $c$，此时路径长度 $a+c-2\times b$，其中 $-2\times b$ 显然对路径奇偶性没影响，$a+c$ 为奇数当且仅当其中恰好只有一个奇数。

于是每次我们需要且只需要走到深度奇偶性不同的地方。

我们把偶数和奇数分开，然后经过的深度奇偶性是奇数偶数交替的。

因此需要保证奇数偶数的数量相差不超过一，同时如果相差为 $1$，第一个数的奇偶性已经确定。

于是我们就很简单了，只需要把奇数偶数分别放入两个数组，按编号排序，然后统计数量，贪心即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct st{
	int v,ne;
}sd[1000009];
int inn;
int h[1000009];
void add(int u,int v){
	sd[++inn].v=v;
	sd[inn].ne=h[u];
	h[u]=inn;
}
bool dep[1000009];
int z;
void dfs(int t,int fa){
	dep[t]=(dep[fa]^1);
	if(dep[t]){
		z++;
	}
	for(int i=h[t];i;i=sd[i].ne){
		if(sd[i].v!=fa){
			dfs(sd[i].v,t);
		}
	}
}
queue<int> q[2];
void _main(){
	z=0;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		h[i]=0;
		dep[i]=0;
	}
	inn=0;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0);
	if(abs(n-2*z)>1){
		cout<<-1<<endl;
		return;
	}
	for(int i=1;i<=n;i++){
		if(dep[i]){
			q[1].push(i);
		}else{
			q[0].push(i);
		}
	}
	bool c;
	c=0;
	if(abs(n-2*z)){
		if(2*z>n){
			c=1;
		}else{
			c=0;
		}
	}else{
		c=1;
	}
	while(q[0].size()||q[1].size()){
		cout<<q[c].front()<<" ";
		q[c].pop();
		c^=1;
	}
	cout<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：mysterys (赞：1)

雀食是一道好题。
# 思路
1. 考虑 $01$ 染色，将树划分成两个集合。
1. 容易发现：由于边权为 $1$ ，同集合内的两个点距离都是偶数。

1. 所以，每一次挑选 $p_i$,即从集合 $A$ 到集合 $B$，或者从集合 $B$ 到集合 $A$。

1. 这样，我们就只需要处理字典序最小了。而这也很简单，开两个优先队列维护集合，而 ```-1``` 的情况就是输出的数的数量不是 $n$ 的情况特判即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
#define endl '\n'
#define ll long long
const int N=1e5+5;
int n,t;
vector<int>g[N];
priority_queue<int,vector<int>,greater<int> >q;
priority_queue<int,vector<int>,greater<int> >h;
queue<int>s;
inline void dfs(int u,int fa,bool flag){
	if(flag){
		q.push(u);
	}else h.push(u);
	for(int v:g[u]){
		if(v==fa) continue;
		dfs(v,u,!flag);
	}
}
inline void print(bool flag){
	if(t==n) return;
	if(flag){
		if(q.empty()) return;
		s.push(q.top());
		++t;
		q.pop();
		print(0);
	}else{
		if(h.empty()) return;
		s.push(h.top());
		++t;
		h.pop();
		print(1);
	}
}
inline void solve(){
	for(int i=0;i<=n;i++) g[i].clear();
	while(!h.empty()) h.pop();while(!q.empty()) q.pop();
	cin>>n;
	t=0;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0,1);
	int len=max(q.size(),h.size());
	if(len==(int)q.size()){
		if(q.size()==h.size()){
			if(q.top()==1) print(1);
			else print(0);
		}
		else print(1);
	}else{
		print(0);
	}
	if(t!=n){
		while(!s.empty()) s.pop();
		cout<<-1<<endl;
	}else{
		while(!s.empty()){
			cout<<s.front()<<' ';
			s.pop();
		}
		cout<<endl;
	}
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--) solve();
	return 0;
}
```
# 优化
事实上，并不需要优先队列。可以从 $1$ 遍历到 $n$，用双指针维护两个集合的最小值，可以做到优秀的线性。

代码较简单，所以这一部分留给读者自己实现。

---

## 作者：Crazyouth (赞：1)

### Sol.

我们可以转化题意。首先提出一个结论：$u$ 到 $v$ 的路径长度与 $u$ 和 $v$ 的深度差同奇偶。证明：

不妨先假设 $d_u\le d_v$（$d_i$ 表示节点 $i$ 的深度），那么我们分类：

- 如果 $u$ 是 $v$ 的祖先，那么命题显然成立；
- 否则 $\operatorname{dist}(u,v)=\operatorname{dist}(u,\operatorname{lca}(u,v))+\operatorname{dist}(v,\operatorname{lca}(u,v))\equiv \operatorname{dist}(1,u)+\operatorname{dist}(1,v)=d_u+d_v\equiv d_v-d_u(\bmod\ 2)$。其中 $\operatorname{dist}(u,v)$ 表示 $u$ 到 $v$ 的简单路径长度，$\operatorname{lca}(u,v)$ 表示 $u,v$ 的最近公共祖先。


于是题目转化为 $p_i$ 与 $p_{i+1}$ 在深度奇偶性不同的位置。那么自然地，如果树奇数层与偶数层节点数差大于 $1$，那么输出 `-1`。否则我们将树黑白染色，把黑节点和白节点编号排序，如果某一颜色的节点个数多，那么先输出它；否则先输出最小编号更小的那一组。在输出完一个数后，两种颜色的节点编号交错输出即可。

### Std.
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> G[100010],col[2];
void dfs(int u,int fa,int nc)
{
	col[nc].push_back(u);
	for(auto v:G[u])
	{
		if(v==fa) continue;
		dfs(v,u,nc^1);
	}
}
void solve()
{
	col[0].clear();col[1].clear();
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) G[i].clear();
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0,0);
	if(abs((int)col[0].size()-(int)col[1].size())>1)
	{
		cout<<-1<<'\n';
		return;
	}
	sort(col[0].begin(),col[0].end());
	sort(col[1].begin(),col[1].end());
	if(col[0].size()==col[1].size())
	{
		if(*col[0].begin()>*col[1].begin()) swap(col[0],col[1]);
		auto it=col[1].begin();
		for(auto i:col[0])
		{
			cout<<i<<' '<<*it<<' ';
			it++;
		}
		cout<<'\n';
	}
	else
	{
		if(col[0].size()<col[1].size()) swap(col[0],col[1]);
		auto it=col[1].begin();
		for(auto i:col[0])
		{
			cout<<i<<' ';
			if(it!=col[1].end()) cout<<*it<<' ',it++;
		}
		cout<<'\n';
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：liuyi0905 (赞：0)

考虑使用黑白染色法，到点 $1$ 距离为奇数的染成黑，偶数染成白。若点 $u$ 到点 $v$ 的距离为奇数，那么 $u,v$ 的颜色必然不同，所以最后的答案一定为一个黑白交错的序列。
+ 当两种颜色的节点数之差大于 $1$，无解。
+ 当黑色比白色多，则答案为黑、白、黑、……、白、黑。
+ 当白色比黑色多，则答案为白、黑、白、……、黑、白。
+ 如果一样多，哪种颜色的最小编号更小就先选哪种。

用小根堆维护每种颜色的元素，轮换输出即可。

时间复杂度 $O(Tn\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,c[2];
vector<int>e[N];
priority_queue<int,vector<int>,greater<int>>q[2];
void S(int u,int f,bool o){
  c[o]++,q[o].push(u);
  for(auto v:e[u]){
    v!=f&&(S(v,u,!o),1);
  }
}
int main(){
  for(cin>>t;t;t--){
    cin>>n;
    for(int i=1;i<=n;i++){
      e[i].clear();
    }
    for(int i=1,u,v;i<n;i++){
      cin>>u>>v;
      e[u].push_back(v);
      e[v].push_back(u);
    }
    for(int i=0;i<2;i++){
      for(c[i]=0;q[i].size();q[i].pop()){
      }
    }
    S(1,0,0);
    if(abs(c[0]-c[1])>1){
      cout<<"-1\n";
      continue;
    }
    bool o=(c[0]==c[1]?q[1].top()<q[0].top():c[1]>c[0]);
    for(;q[0].size()||q[1].size();o^=1){
      cout<<q[o].top()<<" ",q[o].pop();
    }
    cout<<"\n";
  }
  return 0;
}

---

## 作者：CNS_5t0_0r2 (赞：0)

$p_i$ 和 $p_{i + 1}$ 之间的距离为奇数，等价于 $p_i$ 和 $p_{i + 1}$ 到 $1$ 的奇偶性不同。

有了这个转化，这题就很简单了。

算出所有点到 $1$ 号点的距离（$1$ 到自己的距离为 $0$），记到 $1$ 的距离为奇数的节点数量为 $cnt_1$，到 $1$ 的距离为偶数的节点数量为 $cnt_2$。

我们肯定希望 $1$ 排第一个（字典序肯定最优），所以如果能按照“偶奇偶奇”排列肯定最好，这种情况要求 $cnt_2 = cnt_1$ 或 $cnt_2 = cnt_1 + 1$。如果 $cnt_1 = cnt_2 + 1$，那么就只能按照“奇偶奇偶”的方式排列。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int T;
int n;
struct edge{
	int to,nex;
} e[N << 1];
int head[N],ecnt;
void addedge(int u,int v){
	ecnt++;
	e[ecnt] = (edge){v,head[u]};
	head[u] = ecnt;
}

int dis[N];
void dfs(int u,int fa){
	for(int i = head[u];i;i = e[i].nex){
		int v = e[i].to;
		if(v == fa)
			continue;
		dis[v] = dis[u] + 1;
		dfs(v,u);
	}
}
int vec1[N],top1;
int vec2[N],top2;
void clear(){
	ecnt = top1 = top2 = 0;
	for(int i = 1;i <= n;i++)
		head[i] = dis[i] = 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while(T--){
		cin >> n;
		clear();
		for(int i = 1;i < n;i++){
			int u,v;
			cin >> u >> v;
			addedge(u,v);
			addedge(v,u);
		}
		dfs(1,0);
		for(int i = 1;i <= n;i++){
			if(dis[i] & 1)
				vec1[++top1] = i;
			else
				vec2[++top2] = i;
		}
		if(top1 == top2)
			for(int i = 1;i <= top1;i++)
				cout << vec2[i] << ' ' << vec1[i] << ' ';
		else if(top1 == top2 + 1){
			for(int i = 1;i <= top2;i++)
				cout << vec1[i] << ' ' << vec2[i] << ' ';
			cout << vec1[top1];
		}
		else if(top1 == top2 - 1){
			for(int i = 1;i <= top1;i++)
				cout << vec2[i] << ' ' << vec1[i] << ' ';
			cout << vec2[top2];
		}
		else
			cout << -1;
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：StarsIntoSea (赞：0)

# Solution

一个很显然的性质：

对于任意两树上任意两个点 $x,y$，其树上距离的奇偶性等于
$|dep[x]-dep[y]|$ 的奇偶性。这里 $dep[i]$ 表示 $i$ 号点的深度。

问题就变成了求一个排列 $p$，使得 $dep[p_i]$ 与 $dep[p_{i+1}]$ 的差为奇数。

我们可以对整个树 dfs，求出每个点的深度，再把一个深度为奇数的点与深度为偶数的点分别记录。如果**深度为奇数的点的数量与深度为偶数的点的数量差值大于 $1$**，那么无解。否则**就是从两个点集中轮流取出编号最小的点**。

时间复杂度 $O(n \log_2 n)$，瓶颈在于排序。

# Code


```cpp
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
int dep[100005],h[100005],idx=0,n=0;
struct node{int v,ne;}e[2000005];
int j[100005],o[100005],l1,l2;
void dfs(int x,int f){
	if(dep[x]) return ;
	dep[x]=dep[f]+1;
	if(dep[x]&1) j[++l1]=x;
	else o[++l2]=x;
	for(int i=h[x];i;i=e[i].ne){
		int y=e[i].v;
		if(y==f) continue;
		dfs(y,x);
	}
}
void add(int a,int b){
	e[++idx]={b,h[a]};
	h[a]=idx;
}
void sol(){
	for(int i=1;i<=idx;++i) e[i]={0,0};
	for(int i=1;i<=n;++i) h[i]=dep[i]=0;
	idx=0;
	l1=l2=0;
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	if(abs(l1-l2)>1){ //两个点集之差大于1就无解
		printf("-1\n"); return ;
	} 
	int l=0,r=0;
	sort(j+1,j+l1+1);
	sort(o+1,o+l2+1);
	if(l1>l2){ //如果某一个点集更大，就需要先输出更大的那一个
		printf("%d ",j[++l]);
		while(l<l1){
			printf("%d ",o[++r]);
			printf("%d ",j[++l]);
		}
	}
	else if(l2>l1){ //同上
		printf("%d ",o[++r]);
		while(l<l1){
			printf("%d ",j[++l]);
			printf("%d ",o[++r]);
		}
	}
	else{
		if(j[1]>o[1]){ //如果一样大就找第一个点较小的那一个，因为要求字典序最小
			while(l<l1){
				printf("%d ",o[++r]);
				printf("%d ",j[++l]);
			}
		}
		else{
			while(l<l1){
				printf("%d ",j[++l]);
				printf("%d ",o[++r]);
			}
		}
	}
	printf("\n");
}
int main(){
	int _;scanf("%d",&_);
	while(_--) sol();
}
```

---

## 作者：modfish_ (赞：0)

## 思路
考虑先给该树定一个根，计算每个点的深度。

这样，我们在树上每走一步，都相当于将深度加一或减一。所以，**一条路径的长度**和**它两端的点的深度差**的奇偶性相同。虽然很显然但还是简单证明一下：

设两个点为 $u,v$，它们的最近公共祖先为 $lca$，树根为 $root$，任意两点距离为 $dis_{x,y}$，则路径长度为 $dis_{u,lca}+dis_{v,lca}$，深度（在此为了方便，以边算深度，结论换成点算深度也是一样的）差为 $\lvert dis_{u, root}-dis_{v,root}\rvert=\lvert dis_{u,lca}+dis_{lca,root}-(dis_{v,lca}+dis_{lca,root})\rvert=\lvert dis_{u,lca}-dis_{v,lca}\rvert$，这两个奇偶性显然相同。

于是我们把所有深度为奇数和深度为偶数的点交替排列即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;

int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
int dep[maxn], res = 0, od[maxn], ed[maxn], oc = 0, ec = 0;

void merge(int u, int v){
	nxt[++ cnt] = head[u], to[cnt] = v, head[u] = cnt;
}

void dfs(int x, int f){
	dep[x] = dep[f] + 1;
	if(dep[x] & 1) res ++;
	else res --;
	for(int i = head[x]; i; i = nxt[i]){
		int j = to[i];
		if(j == f) continue;
		dfs(j, x);
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n;
		scanf("%d", &n);
		for(int i = 1; i < n; i ++){
			int u, v;
			scanf("%d %d", &u, &v);
			merge(u, v), merge(v, u);
		}
		dfs(1, 0);
		if(res > 1 || res < -1){
			printf("-1\n");
			for(int i = 1; i <= n; i ++) dep[i] = head[i] = od[i] = ed[i] = 0;
			for(int i = 1; i <= cnt; i ++) nxt[i] = to[i] = 0;
			cnt = oc = ec = res = 0;
			continue;
		}
		for(int i = 1; i <= n; i ++){
			if(dep[i] & 1) od[++ oc] = i;
			else ed[++ ec] = i;
		}
		int x = 1, y = 1, pr;
		if(res == 1) printf("%d ", od[x ++]), pr = 1;
		else if(res == -1) printf("%d ", ed[y ++]), pr = 0;
		else{
			if(od[x] < ed[y]) printf("%d ", od[x ++]), pr = 1;
			else printf("%d ", ed[y ++]), pr = 0;
		}
		for(int i = 1; i <= n - 1; i ++){
			if(pr) printf("%d ", ed[y ++]);
			else printf("%d ", od[x ++]);
			pr ^= 1;
		}
		printf("\n");
		for(int i = 1; i <= n; i ++) dep[i] = head[i] = od[i] = ed[i] = 0;
		for(int i = 1; i <= cnt; i ++) nxt[i] = to[i] = 0;
		cnt = oc = ec = res = 0;
	}
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

在本文中，我们用 $f(i,j)$ 表示点 $i$ 到点 $j$ 的简单路径的长度，$\text{lca}(i,j)$ 表示点 $i$ 与点 $j$ 的最近公共祖先，$dep_i$ 表示点 $i$ 的深度。

根据最近公共祖先的定义我们可以知道：

$$f(x,y)=f(x,\text{lca}(x,y))+f(\text{lca}(x,y),y)$$

$$f(x,y)=dep_x-dep_{\text{lca}(x,y)}+dep_y-dep_{\text{lca}(x,y)}$$

$$f(x,y)=dep_x+dep_y-2\times dep_{\text{lca}(x,y)}$$

因为这题只讨论奇偶性，所以：

$$f(x,y)\equiv dep_x+dep_y\pmod{2}$$

所以我们只需要对于每个点求出深度，分奇偶性存储，输出时我们奇偶交替即可，注意分讨使答案字典序最小。

如果奇偶数量差太多显然是无解的。

警惕输出出锅，警钟长鸣！

---

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>ve[100005];
vector<int>odd,even;
void dfs(int x,int f,int dp){
    if(dp%2)odd.push_back(x);
    else even.push_back(x);
    for(int i=0;i<ve[x].size();i++)
    if(ve[x][i]!=f)dfs(ve[x][i],x,dp+1);
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        odd.clear(),even.clear();
        for(int i=1;i<=n;i++)
        ve[i].clear();
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            ve[u].push_back(v);
            ve[v].push_back(u);
        }
        dfs(1,0,1);
        sort(odd.begin(),odd.end());
        sort(even.begin(),even.end());
        if(abs((int)(odd.size()-even.size()))>1)puts("-1");
        else{
            if(odd.size()>even.size()){
                for(int i=0;i<even.size();i++)
                cout<<odd[i]<<' '<<even[i]<<' ';
                cout<<odd[odd.size()-1]<<' ';
            }else if(odd.size()<even.size()){
                for(int i=0;i<odd.size();i++)
                cout<<even[i]<<' '<<odd[i]<<' ';
                cout<<even[even.size()-1]<<' ';
            }else if(odd[0]<even[0]){
                for(int i=0;i<even.size();i++)
                cout<<odd[i]<<' '<<even[i]<<' ';
            }else if(odd[0]>even[0]){
                for(int i=0;i<even.size();i++)
                cout<<even[i]<<' '<<odd[i]<<' ';
            }
            cout<<endl;
        }
    }
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

又是一道欧拉路。

## 思路

在一个树上，两点 $(u,v)$ 之间的距离是 $dep_u+dep_v-2\times dep_{\operatorname{lca}(u,v)}$（其中 $dep$ 指深度，$\operatorname{lca}(u,v)$ 指 $u$ 和 $v$ 的最近公共祖先）。

因为这个题只讨论奇偶性，所以求了 lca 也无用。只需要求出深度即可。

然后就会发现：一个奇数深度的要和偶数度数的在一起；一个偶数深度的要和奇数深度的在一起。

考虑图论建模：奇数深度说明后面要接偶数，就是奇数向偶数连边；偶数后面要接奇数，就是偶数向奇数连边。

然后检验这张只由奇偶两个点组成的图中存不存在欧拉路就行。判定方法：设奇数深度点数为 $x$，偶数深度点数为 $y$，要求 $|x-y|\le 1$。

然后就是输出了。我们记录下奇数深度和偶数深度的点并按字典序排序。

- 如果 $x-y=0$，则我们比较字典序最小的奇数深度的和偶数深度点，看哪个更小。如果奇数的更小，我们按照奇数至偶数至奇数至偶数的顺序输出；反之是偶数到奇数到偶数。
- 如果 $x-y=1$，则必须以奇数开始，按字典序循环输出即可。
- 如果 $x-y=-1$，与上面的情况类似。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int T,n;
struct edge{
	int u,v,nxt;
}e[200005];
int cnt,head[100005],dep[100005],ou[100005],ji[100005],du,cnt1,cnt2;
void add(int u,int v){
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int now,int fa,int d){
	dep[now]=d;
	for(int i=head[now];i;i=e[i].nxt){
		if(e[i].v==fa)continue;
		dfs(e[i].v,now,d+1);
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(head,0,sizeof(head));
		cnt=0;
		memset(e,0,sizeof(e));
		memset(ji,0,sizeof(ji));
		cnt1=0;
		cnt2=0;
		memset(ou,0,sizeof(ou));
		memset(dep,0,sizeof(dep));
		for(int i=1,u,v;i<n;i++){
			scanf("%d%d",&u,&v);
			add(u,v);
			add(v,u);
		}
		dfs(1,1,1);
		for(int i=1;i<=n;i++){
			if(dep[i]&1){
				ji[++cnt1]=i;
			}
			else{
				ou[++cnt2]=i;
			}
		}
		if(cnt1-cnt2>1||cnt1-cnt2<-1){
			printf("-1\n");
			continue;
		}
		sort(ji+1,ji+cnt1+1);
		sort(ou+1,ou+cnt2+1);
		if(cnt1==cnt2){
			if(ji[1]<ou[1]){
				for(int i=1,j=1;i<=cnt1;i++,j++){
					printf("%d %d ",ji[i],ou[j]);
				}
			}
			else{
				for(int i=1,j=1;i<=cnt1;i++,j++){
					printf("%d %d ",ou[j],ji[i]);
				}
			}
		}
		else{
			if(cnt1==cnt2+1){
				printf("%d ",ji[1]);
				for(int i=2,j=1;i<=cnt1;i++,j++){
					printf("%d %d ",ou[j],ji[i]);
				}
			}
			else{
				printf("%d ",ou[1]);
				for(int i=2,j=1;i<=cnt2;i++,j++){
					printf("%d %d ",ji[j],ou[i]);
				}
			}
		}
			printf("\n");
	}
	return 0;
}
```

---

