# Array and Operations

## 题目描述

你有一个长度为n的数组a和m对数$(i_1,j_1),(i_2,j_2)...,(i_m,j_m)$   .对于每对数都满足$i_k + j_k$   是一个奇数，且每个数都在1到n之间。

你每次操作可需要挑一对数（给定的m对里面）$ i_k,j_k$   ，然后使$a[i_k]=\frac{a[i_k]}{v},a[j_k]=\frac{a[j_k]}{v}$   ,v是一个不等于1的正整数,且$v$  是a[i]和a[j]的公约数

问最多可以进行多少次操作

## 样例 #1

### 输入

```
3 2
8 3 8
1 2
2 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 2
8 12 8
1 2
2 3
```

### 输出

```
2
```

# 题解

## 作者：Reaepita (赞：5)

首先我们可以看到 
	  
$i_k + j_k $  是一个奇数

所以可以考虑奇数位的点与源点连边，

偶数位的点与汇点连边

为了得到了最多的操作次数

每次操作一定是除以两个数的公共的质因数。

所以我们对于每个数的每一个质因数建图

先处理出每个数的质因数和质因数的个数

对于一个操作 $(i_k , j_k)$ 我们就对

第 $i_k$ 个数 ，第 $j_k$ 个数

的每个相同的质因数连边

边权为两个点这个质因数的数量中较小的那一个

奇数点的每个质因数与源建边，边权为这个质因数的个数

偶数点同理，与汇建边，然后跑最大流。

```cpp
#include<iostream>
#include<cstring>
#include<queue>
#include<cmath>
#include<cstdio>
using namespace std;
const int maxn=100000*8+10,maxl=70000+111,inf=0x3f3f3f3f;
struct edge
{
	int v,next;
	int w;
}e[maxn];
int head[maxl],cnt=0,dep[maxl],n,m,ans=0,s,t,a[maxl];
inline void add(int u,int v,int w)
{
	e[cnt]=(edge){v,head[u],w};
	head[u]=cnt++;
	e[cnt]=(edge){u,head[v],0};
	head[v]=cnt++;
}
bool bfs()
{
	memset(dep,-1,sizeof(dep));
	dep[s]=0;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=e[i].next)
		{
			int v=e[i].v;
			if(dep[v]==-1&&e[i].w>0)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t]>-1;
}
int dfs(int u,int cap)
{
	
	if(u==t)return cap;
	int flow=0;
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(dep[v]==dep[u]+1&&e[i].w)
		{
			int temp=dfs(v,min(e[i].w,cap-flow));
			flow+=temp;
			e[i].w-=temp;
			e[i^1].w+=temp;
			if(flow==cap)return flow;
		}
	}
	if(!flow)dep[u]=-2;
	return flow;
}
int dinic()
{
	int solve=0,f;
	while(bfs())
	{
		while(f=dfs(s,inf))solve+=f;
	}
	return solve;
}
vector<int>yue[maxl],num[maxl];
void make(int k)
{
	int lim=sqrt(a[k]+0.5),temp=a[k];
	for(int i=2;i<=lim;i++)
	if(temp%i==0){
		int cn=0;
		while(temp%i==0)cn++,temp/=i;
		yue[k].push_back(i),num[k].push_back(cn);
	}
	if(temp>1)yue[k].push_back(temp),num[k].push_back(1);
}
void update(int x,int y)
{
	int N=yue[x].size(),M=yue[y].size();
	for(int i=0;i<N;i++)
	for(int j=0;j<M;j++)
	if(yue[x][i]==yue[y][j])add((x-1)*n+i+1,(y-1)*n+j+1,min(num[x][i],num[y][j]));
}
int u,v;
int main()
{
	cnt=0;
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	s=0,t=n*50+10;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(!(i&1))
		{	
			make(i);
			for(int j=0;j<yue[i].size();j++)
			add(s,(i-1)*n+j+1,num[i][j]);
		}
		else 
		{
			make(i);
			for(int j=0;j<yue[i].size();j++)
			add((i-1)*n+j+1,t,num[i][j]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		if(u&1)swap(u,v);
		update(u,v);
	}
	printf("%d\n",dinic());
}
```

---

## 作者：Binary_Lee (赞：1)

## [题面传送门](https://www.luogu.com.cn/problem/CF498C)

### 前置芝士

最大流。~~推销~~安利我的博客：[网络流：最大流最小割](https://www.cnblogs.com/binary1110011/p/16880037.html)

### 解决思路

首先考虑，要同时除以一个公约数，而且要操作次数最多，所以每次除以的要是公共质因数。

同时，对于每对数都满足 $i_k+j_k$ 是一个奇数，启示我们把所有数分成两类：下标为奇数的和下标为偶数的。问题转换成：多次在奇数堆中选一个数，偶数堆中选一个数（前提是这两个数在一组中），选他们的若干个公共质因数删掉，问最多能删多少对。

所以网络流的模型就浮现出来了。我们对于每一个出现过的质因数建一张图。设源点为 $0$，汇点为 $n+1$。钦定数 $x$ 所含质因数 $p$ 的数量为 $f(x,p)$。考虑对于某一个质因数 $p$ 如何连边：

- 对于所有下标为奇数的数 $a_i$，从 $0$ 向 $i$ 连一条容量为 $f(a_i,p)$ 的边。

- 对于所有下标为偶数的数 $a_i$，从 $i$ 向 $n+1$ 连一条容量为 $f(a_i,p)$ 的边。

- 对于所有数对 $(i_k,j_k)$，**钦定 $i_k$ 为奇数**，从 $i_k$ 向 $j_k$ 连一条容量为 $\min(f(a_{i_k},p),f(a_{j_k},p))$ 的边，意为选 $(a_{i_k},a_{j_k})$ 最多可以删这么多次。

然后，从源点到汇点的最大流就是整个数列中可以删除 $p$ 的数量了。

所以可以把最大流封装一下，对于每一个质因数跑一遍最大流，把答案加起来就好了。

具体细节可以看代码，其中 $id_p$ 代表的是质因数 $p$ 的编号。

### AC Code

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
#define inf 1e16
#define qwq cout<<"qwq"<<endl
using namespace std;
int n,m,a[20005];
int u,v,cntt,Ans;
map<int,int> mp,id;
struct MaxFlow{    //dinic最大流板子
	int tot=1,head[2005],cur[2005],dep[2005];   //封装的话数组、变量要定义在里面（
	struct node{
		int to,nxt,f;
	}e[2005];
	void add(int u,int v,int f){
		e[++tot]={v,head[u],f},head[u]=tot;
		e[++tot]={u,head[v],0},head[v]=tot;
	}
	queue<int> q;
	int bfs(int s,int t){
		while(q.size()) q.pop();q.push(s);
		memset(dep,0,sizeof(dep));dep[s]=1;
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=head[x];i;i=e[i].nxt){
				node tmp=e[i];
				if(tmp.f&&!dep[tmp.to]){
					dep[tmp.to]=dep[x]+1;
					q.push(tmp.to);
				}
			}
		}
		return dep[t];
	}
	int dfs(int s,int t,int f){
		if(s==t||!f) return f;
		int ans=0;
		for(int i=cur[s];i;i=e[i].nxt){
			node &x=e[i];cur[s]=i;
			if(x.f&&dep[x.to]==dep[s]+1){
				int tmp=dfs(x.to,t,min(f,x.f));
				x.f-=tmp,e[i^1].f+=tmp;
				ans+=tmp,f-=tmp;
				if(f<=0) break;
			}
		}
		return ans;
	}
	int dinic(int s,int t){
		int ans=0;
		while(bfs(s,t)){
			memcpy(cur,head,sizeof(head));
			ans+=dfs(s,t,inf);
		}
		return ans;
	}
}mf[205];
void build(int i,int j){   //连接数对
	int ans=0,t1=a[i],t2=a[j];
	mp.clear();
	for(int i=2;i*i<=t1;i++){
		while(t1%i==0) t1/=i,mp[i]++;
	}
	if(t1>1) mp[t1]++;   //对其中一个分解质因数
	for(auto k:mp){  
		int tmp=t2,cnt=0;
		while(cnt<k.se&&tmp%k.fi==0) tmp/=k.fi,cnt++;  //容量取min
		if(cnt) mf[id[k.fi]].add(i,j,cnt);
	}
}
void calc(int z,int x,int op){   //连接源点、汇点
	mp.clear();
	for(int i=2;i*i<=x;i++){
		while(x%i==0) x/=i,mp[i]++;
	}
	if(x>1) mp[x]++;   //分解质因数
	for(auto k:mp){
		if(!id[k.fi]) id[k.fi]=++cntt; 
		if(!op) mf[id[k.fi]].add(0,z,k.se);   //奇数下标连源点
		else mf[id[k.fi]].add(z,n+1,k.se);   //偶数下标连汇点
	}
}
signed main(){
	IOS;TIE;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i&1) calc(i,a[i],0);
		else calc(i,a[i],1);
	}
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		if(v&1) swap(u,v);   //保证第一个下标是奇数
		build(u,v);
	}
	for(auto i:id) Ans+=mf[i.se].dinic(0,n+1);   //所有质因数最大流之和
	cout<<Ans<<endl; 
	return 0;
}
```

---

## 作者：wcyQwQ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF498C)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/09/15/CF498C%20Array%20and%20Operations/)

## 前言

暑假的一道集训题目，今天想起来补一发题解。

### 前置芝士

网络流


## 分析

首先题目里面的限制非常多而且复杂，所以我们考虑用网络流解决。

首先我们看到下标之和为奇数这个限制就会想到把整个序列按下标奇偶分组，建一个二分图，然后我们考虑怎么解决。

首先我们很容易发现要使操作次数最多，每次除的肯定是一个质因数，所以我们预处理出每个数的质因数以及每个因数的指数。

然后我们按如下方式连边:

1. 将序列中的每个下标拆成 $x$ 个点，其中 $x$ 为这个数不同的质因数个数。
2. 按下标奇偶分组，然后对每个点分别向源点/汇点连容量为这个质因数指数的边。
3. 对于每一个组合，如果这两个数有公共的质因数，就将这两个质因数代表的点连上容量为 $inf$ 的边。

建完图跑最大流即可。

具体实现见代码。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10, INF = 1 << 30;
int a[N];
int h[N], e[N], ne[N], f[N], idx;
vector<int> fac[N];
vector<int> cnt[N];
int n, m, s, t;
int d[N], cur[N];

int read()
{
	int x = 0, y = 1; char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') y = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * y;
}

void add(int a, int b, int c)
{
	e[idx] = b;
	f[idx] = c;
	ne[idx] = h[a];
	h[a] = idx++;
}

void init(int id)
{
	int tmp = a[id];
	for (int i = 2; i <= tmp / i; i++)
		if (tmp % i == 0)
		{
			fac[id].push_back(i);
			int cntt = 0;
			while (tmp % i == 0)
				cntt++, tmp /= i;
			cnt[id].push_back(cntt);
		}
	if (tmp > 1) fac[id].push_back(tmp), cnt[id].push_back(1);
}

int get(int i, int j)
{
	return (i - 1) * n + j + 1;
}

bool bfs()
{
	memset(d, -1, sizeof d);
	queue<int> q;
	q.push(s);
	d[s] = 0, cur[s] = h[s];
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int i = h[u]; ~i; i = ne[i])
		{
			int v = e[i];
			if (d[v] == -1 && f[i])
			{
				d[v] = d[u] + 1;
				cur[v] = h[v];
				if (v == t) return true;
				q.push(v);
			}
		}
	}
	return false;
}

int find(int u, int lim)
{
	if (u == t) return lim;
	int flow = 0;
	for (int i = cur[u]; ~i && flow < lim; i = ne[i])
	{
		cur[u] = i;
		int v = e[i];
		if (d[v] == d[u] + 1 && f[i])
		{
			int t = find(v, min(f[i], lim - flow));
			if (!t) d[v] = -1;
			f[i] -= t, f[i ^ 1] += t, flow += t;
		}
	}
	return flow;
}

int dinic()
{
	int res = 0, flow;
	while (bfs()) while (flow = find(s, INF)) res += flow;
	return res;
}

int main()
{
	memset(h, -1, sizeof h);
	n = read(), m = read();
	s = 0, t = N - 1;
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) init(i);
	for (int i = 1; i <= n; i++)
	{
		if (i & 1)
			for (int j = 0; j < fac[i].size(); j++)
				add(s, get(i, j), cnt[i][j]), add(get(i, j), s, 0);
		else
			for (int j = 0; j < fac[i].size(); j++)
				add(get(i, j), t, cnt[i][j]), add(t, get(i, j), 0);
	}
	while (m--)
	{
		int a = read(), b = read();
		if (b & 1) swap(a, b);
		for (int i = 0; i < fac[a].size(); i++)
			for (int j = 0; j < fac[b].size(); j++)
				if (fac[a][i] == fac[b][j])
					add(get(a, i), get(b, j), INF), add(get(b, j), get(a, i), 0);
	}
	printf("%d\n", dinic());
	return 0;
}
```



---

## 作者：Drind (赞：0)

### 题目解析

我们发现可以消除的两个数下标和为奇数，也就是两个下标和奇偶性不同，容易发现这是一张二分图。

我们又发现如果要让消除次数最大化，那么每次消除的数尽可能小，也就是每次只能删除质数。

我们对于每个质数单独处理，最后把所有匹配数加起来即可。

省略最大流板子代码如下

```cpp
unordered_map<int,int>mp;
int a[N];

inline void fake_main(){
	memset(head,-1,sizeof head);
	int n,m; cin>>n>>m; s=n+1; t=s+1;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		if(i%2==1) adde(s,i,0);
		else adde(i,t,0);
	}
	int rd=cnt;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		if(u%2==0) swap(u,v);
		adde(u,v,1e9);//注意加边方向
	}
	int ans=0;
	for(int i=1;i<=n;i++){//枚举每个数的每个质因子
		int cd=a[i];
		for(int j=2;j*j<=cd;j++){
			if(cd%j==0){
				while(cd%j==0&&cd!=0) cd/=j;
				if(!mp[j]){
					mp[j]=1;
					for(int k=1;k<=n;k++){
						int tmp=a[k],tot=0;
						while(tmp%j==0){//枚举每个数含有多少个质因子
							tot++; tmp/=j;
						} 
						edge[(k-1)*2].flow=tot;//初始化边
						edge[(k-1)*2+1].flow=0;
					}
					for(int ii=rd+1;ii<=cnt;ii+=2) edge[ii].flow=1e9,edge[ii^1].flow=0;//初始化边
					ans+=dinic();
				}
			}
		}
		if(cd!=1){//同上
			if(!mp[cd]){
				mp[cd]=1;
				for(int k=1;k<=n;k++){
					int tmp=a[k],tot=0;
					while(tmp%cd==0){
						tot++; tmp/=cd;
					}
					edge[(k-1)*2].flow=tot;
					edge[(k-1)*2+1].flow=0;
				}
				for(int ii=rd+1;ii<=cnt;ii+=2) edge[ii].flow=1e9,edge[ii^1].flow=0;
				ans+=dinic();
			}
		}
	}
	cout<<ans<<"\n";
}
```

---

## 作者：TernaryTree (赞：0)

复健 flow 第一题。*2100。

这个 $i+j$ 为奇数的条件，提示很明显。就奇数位置扔一边，偶数扔一边。

有限制关系的最优化问题，引导我们去用网络流考虑。

容易注意到，除掉一个合数是不优的，因为我们一次一次除它的质因子，这样可以达到更多次。

然后从质因子考虑，把每个数分解质因数，然后一次操作相当于两个位置的某一个质因子次数减一。

把每个质因子拆开来，因为质因子之间互不影响。总的质因子个数很小，所以完全可以对每个质因子都建一个图跑 dinic。

对于每个质因子单独考虑的建图比较显然。对于 $m$ 组可操作数对，奇数位置向偶数位置连边，最大容量为 $u$ 的当前质因子次数与 $v$ 的当前质因子次数最小值。然后源点向奇数位置连边，最大容量为这个位置的当前质因子次数；偶数位置同理。

复杂度是 能过。

```cpp
int n, m, cnt;
int a[maxn];
int b[maxn];
umap<int, int> p[maxn];
Flow g[maxn];

int f(int x, int y) {
	if (p[x].count(y)) return p[x][y];
	else return 0;
}

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		int x = a[i];
		for (int d = 2; d * d <= x; d++) {
			if (x % d == 0) {
				x /= d;
				if (p[i].count(d)) p[i][d]++;
				else p[i][d] = 1, b[++cnt] = d;
				d--;
			}
		}
		if (x > 1) {
			if (p[i].count(x)) p[i][x]++;
			else p[i][x] = 1, b[++cnt] = x;
		}
	}
	sort(b + 1, b + 1 + cnt);
	cnt = unique(b + 1, b + 1 + cnt) - b - 1;
	for (int i = 1; i <= cnt; i++) {
		g[i].init(0, n + 1);
		for (int j = 1; j <= n; j++) {
			if (j & 1) g[i].add(0, j, f(j, b[i]));
			else g[i].add(j, n + 1, f(j, b[i]));
		}
	}
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		if (v & 1) swap(u, v);
		for (int j = 1; j <= cnt; j++) g[j].add(u, v, min(f(u, b[j]), f(v, b[j])));
	}
	int ans = 0;
	for (int i = 1; i <= cnt; i++) ans += g[i].dinic();
	cout << ans << endl;
	return 0;
}
```

---

## 作者：chenxia25 (赞：0)

当年觉得这是个 hot tea 来着。

显然最优方案是每次除掉一个质因数。

注意到 $i+j$ 是奇数，显然分奇偶建二分图。然后要除的质因数相等这个怎么破呢。显然把一个数拆成若干个质因数，log 级别的，到 $s/t$ 的容量就是个数。然后 $i,j$ 的所有相等质因数对连边，跑多重匹配。

---

