# Dark roads

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2678

[PDF](https://uva.onlinejudge.org/external/116/p11631.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11631/3b6d8ed066db76a33df958a6c0c60e1de6f08826.png)

## 样例 #1

### 输入

```
7 11
0 1 7
0 3 5
1 2 8
1 3 9
1 4 7
2 4 5
3 4 15
3 5 6
4 5 8
4 6 9
5 6 11
0 0```

### 输出

```
51```

# 题解

## 作者：baokun (赞：6)

# UVA11631 Dark roads 题解
## 题意简述
共有 $n$ 个点 $m$ 条边，用最小边权联通所有点，输出节省掉的边权总和。
## 思路
由于是无向边，所以判断使用最小生成树。

先用最小生成树联通所有点，可用 Kruskal 或 Prim 算法，推荐使用前者（~~因为好写~~）。然后用总边权减去联通所用边的边权即为答案。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
#define man main
using namespace std;
struct node{
	int now,to,dis;
}a[1145141];
int t,f[200005],sum=0,ans=0,cnt=1;
int find_father(int x){
	if(f[x]!=x) f[x]=find_father(f[x]);
	return f[x];
}
bool cmp(node q,node p){
	return q.dis < p.dis ;
}
signed man(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n,m;
	while(cin>>n>>m){
		if(n==0 && m==0)break;
		sum=0;ans=0;cnt=0;
		for(int i=0;i<=n;i++)f[i]=i;
		for(int i=1;i<=m;i++){
			cin>>a[i].now>>a[i].to>>a[i].dis;
			sum+=a[i].dis;
		}
		sort(a+1,a+m+1,cmp);
		for(int i=1;i<=m;i++){
			int f1=find_father(a[i].now);
			int f2=find_father(a[i].to);
			if(f1 != f2){
				f[f1]=f2;
				ans+=a[i].dis;
				cnt++;
			}
			if(cnt==n-1)break;
		}
		cout<<sum-ans<<endl;
	}
	return 0;
}
```
## 后记
$\bullet$ 数组开大一些（~~本人因此栽了跟头~~）。

$\bullet$ UVA 格式管理严，需要注意（[一道类似的题](https://www.luogu.com.cn/problem/UVA10147)）。

---

## 作者：Xssion37_XY (赞：4)

### 前情提要

[题目链接](https://www.luogu.com.cn/problem/UVA11631)

[更好的阅读体验](https://www.luogu.com.cn/blog/778802/solution-uva11631)


### 题目大意

若一个图删去一定的边仍能保持连通，求这些边权值加和的最大值。

### 实际分析

一眼最小生成树板子。

删掉一些边后边权值加和的最大值，不就等于整张图减去边权值加和的最小值吗？

那么就是最小生成树板子题了，我这里使用的是 Kruskal 算法。

这里就要涉及到最小生成树的相关的知识点了，建议大家去看看这两道题。

- [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)

- [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)

当然我这里还是简述一下最小生成树的概念以及重要属性。

概念：一个连通图的生成树是一个极小的连通子图，它包含图中全部的 $n$ 个顶点，但只有构成一棵树的 $n-1$ 条边。

属性（这里只介绍最重要的一个属性）：生成树当中**不存在环**。

当你充分理解了以上的知识点后，你做这道题就很轻松了。

当然如果你还是不懂，我这里还贴心的准备里一个视频。

![](bilibili:BV11N4y1F7wv)

### 代码部分

```
#include <iostream>
#include <algorithm>
#include <cstring>
#define int long long
using namespace std;
const int MAXX = 2000005;
int cnt, sum, sum_sum, n, m;
int fa[MAXX];
struct edge {
	int u, v, w;
} e[MAXX];
int find(int x) {
	if (x != fa[x]) return fa[x] = find(fa[x]);
	return x;
}
bool cmp(edge a, edge b) {
	return a.w < b.w;//排序最小的边
}
void tree() {//Kruskal 大法好
	sort(e + 1, e + 1 + m, cmp);
	for (int i = 1; i <= m; i++) {
		int u = find(e[i].u);
		int v = find(e[i].v);
		if (u == v) {
			continue;//如果有环则跳过
		}
		sum += e[i].w;//累加最小生成树的权值和
		fa[u] = v;//设置u的爸爸是v，当然这里写 fa[v]=u 也没问题
	}
}
signed main() {
	while (cin >> n >> m) {
		if (n == 0 and m == 0) {
			break;
		}
		sum_sum = 0;
		sum = 0;
		memset(e, 0, sizeof(e));//记得清空
		for (int i = 0; i <= n - 1; i ++) {
			fa[i] = i;//将自己设定为自己的爸爸
		}
		for (int i = 1; i <= m; i ++) {
			cin >> e[i].u >> e[i].v >> e[i].w;
			sum_sum += e[i].w;//累加整张图的边权之和
		}
		tree();
		cout << sum_sum - sum << endl;//边权之和减去最小边权和就是一删去一定的边仍能保持连通的边权值和的最大值
	}
	return 0;
}
```

完结撒花！

---

## 作者：Never_care (赞：2)

图论最小生成树
### 思路
要删掉一定数量的边使图依然连通，同时使删除的边权最大。

很明显的最小生成树板子，使用 Prim 或 Kruskal 算法，[不懂的看这里](https://www.bilibili.com/video/BV1wG411z79G/?spm_id_from=333.337.search-card.all.click)。同时建议数组多开，容易被卡。
### code
```cpp
#include<bits/stdc++.h>
#define long long ll
using namespace std;
const int N=2e5+5;
int d[N];
int n,m,ll=0;
struct node{
	int u,v,w;
}a[N];
bool cmp(const node &a,const node &b){
	return a.w<b.w;
}
int dfs(int dep){
	if(dep==d[dep]){
		return dep;
	}
	d[dep]=dfs(d[dep]);
	return d[dep];
}
void add(int f1,int f2){
	f1=dfs(f1);
	f2=dfs(f2);
	if(f1==f2){
		return;
	}
	d[f1]=f2;
}
int main(){
	while(cin>>n>>m){
    	int ti=0,cnt=0;
	    if(n==0&&m==0){
	    	return 0;
		}
		int sum=0;
    	for(int i=0;i<=n;i++){
    		d[i]=i;
    	}
    	for(int i=1;i<=m;i++){
    		cin>>a[i].u>>a[i].v>>a[i].w;
    		sum+=a[i].w;
    	}
    	sort(a+1,a+m+1,cmp);
    	for(int i=1;i<=m;++i){
    		int t1=dfs(a[i].u);
			int t2=dfs(a[i].v);
    		if(t1==t2){
    			continue;
    		}
			else{
    			add(a[i].u,a[i].v);
    			cnt+=a[i].w;
    			ti++;
    		}
    		if(ti==n-1){
    			break;
    		}
    	}
    	cout<<sum-cnt<<'\n';
	}
	return 0;
}
```

---

## 作者：Wi_Fi (赞：2)

题目翻译大意：若一个图删去一定的边仍能保持连通，求这些边权值加和的最大值。

这就是模板题啊。模板题是求剩下的最小值，这道题是求去掉的最小值，不是正好对上吗？

思路：求最小生成树补图的权值和，即先按照模板题求出最小生成树的权值和，再在输入时统计一下整个图的权值和，用整个图的权值和减去最小生成树的权值和。

Code：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int INF=0x3f3f3f3f,N=1e6+5;
long long i,n,m,ans,fa[2*N],sum;
struct node
{
	int u,v,w;
}a[N*3];
bool cmp(node a,node b)
{
	return a.w<b.w;
}
int find(int x)
{
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	while(cin>>n>>m)
	{
		if(n==0&&m==0)break;
		ans=sum=0;
		memset(a,0,sizeof a);
		for(i=1;i<=m;i++)
		{
			cin>>a[i].u>>a[i].v>>a[i].w;
			sum+=a[i].w;
		}
		sort(a+1,a+m+1,cmp);
		for(i=0;i<n;i++)fa[i]=i;
		for(i=1;i<=m;i++)
		{
			int u=find(a[i].u),v=find(a[i].v);
			if(u==v)continue;
			fa[u]=v,ans+=a[i].w;
		}
		cout<<sum-ans<<endl;
	}
	return 0;
}
```


---

## 作者：cqbzhzf (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA11631)

[博客食用效果更佳！！！](https://www.luogu.com.cn/article/13ngg9a6)
### 一句话题意
请你根据所出数据求出最小生成树的大小，得出**边权之和**与**这棵最小生成树大小**的差。

### 最小生成树
最小生成树（Minimum Spanning Tree，简称 MST）是一种在连通图中生成一棵树的算法，该树包含了图中所有的顶点，并且边的权值之和最小。

最常用的两种最小生成树算法是 Prim 算法和 Kruskal 算法。

    Prim 算法：
        1. 选择一个起始顶点，将其加入最小生成树中。
        2. 从与最小生成树相邻的顶点中选择一个权值最小的边，将其加入最小生成树。
        3. 重复上述步骤，直到最小生成树包含了图中所有的顶点。 
    Kruskal 算法：
        1. 将图中的所有边按照权值从小到大进行排序。
        2. 依次选择权值最小的边，如果该边的两个顶点不在同一个连通分量中，则将其加入最小生成树，并将这两个顶点合并到同一个连通分量中。
        3. 重复上述步骤，直到最小生成树包含了图中所有的顶点。
但是这里的数据范围明显开不下一个 $cost$ 二维数组，所以本题用 Prim 做法会更加复杂（使用邻接表存储变量，没试过），故考虑 Kruskal。
### MLE代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+2;
int n,m,cost[N][N],mincost[N],sum;
bool vis[N];
int prim()//最小生成树
{
	for(int i=0;i<n;i++)
	{
		mincost[i]=INT_MAX;
		vis[i]=false;
	}
	mincost[1]=0;
	int res=0;
	while(true)
	{
		int v=-1;
		for(int u=0;u<n;u++)
		{
			if(!vis[u]&&(v==-1||mincost[u]<mincost[v]))
				v=u;
		}
		if(v==-1)
			break;
		vis[v]=true;
		res+=mincost[v];
		for(int u=0;u<n;u++)
			mincost[u]=min(mincost[u],cost[v][u]);
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	memset(cost,0x3f,sizeof(cost));
	while(m--)
	{
		int i,j,k;
		cin>>i>>j>>k;
		sum+=k;//计算边权和
		cost[i][j]=cost[j][i]=min(k,min(cost[i][j],cost[j][i]));
	}
	cout<<sum-prim();
	return 0;
}
```
###  AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5002,INF=0x3f3f3f3f;
struct node
{
	int u,v,w;
}e[MAXN],ans[MAXN];
int fa[MAXN],n,m,tot,sum1,sum2;
void init_set()
{
	for(int i=1;i<=n;i++)
		fa[i]=i;
}
int find_set(int x)
{
	if(x==fa[x])
		return x;
	return fa[x]=find_set(fa[x]);
}
void merge_set(int x,int y)
{
	x=find_set(x),y=find_set(y);
	if(x!=y)
		fa[x]=y;
}
bool cmp1(node x,node y)
{
	return x.w<y.w;
}
bool cmp2(node x,node y)
{
	if(x.u<y.u)
		return 1;
	if(x.u==y.u&&x.v<y.v)
		return 1;
	return 0;
}
void kruskal()
{
	stable_sort(e+1,e+m+1,cmp1);
	init_set();
	for(int i=1;i<=m;i++)
	{
		if(find_set(e[i].u)!=find_set(e[i].v))
		{
			ans[++tot]=e[i];
			merge_set(e[i].u,e[i].v);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		sum1+=c;//计算边权和
		if(a>b)
			swap(a,b);
		e[i].u=a,e[i].v=b,e[i].w=c;
	}
	kruskal();
	sort(ans+1,ans+tot+1,cmp2);
	for(int i=1;i<=tot;i++)
		sum2+=ans[i].w;//计算最小生成树的大小
	cout<<sum1-sum2;
	return 0;
}
```

---

## 作者：Keids (赞：1)

# UVA11631 Dark roads 题解

洛谷链接：<https://www.luogu.com.cn/problem/UVA11631>

题目翻译：

对于一张连通图，删掉一些边，但是仍保证图的连通，求删掉的边之和的最大值。

注意有多组输入输出，当 $n=m=0$ 时输入结束。

很明显，最小生成树的板子。稍微改一下就可以了。

前置知识：最小生成树。链接：<https://www.luogu.com.cn/problem/P3366>

改的部分。对于 $ans$ 来说，先把全部边权加在一起，求生成树时减去要保留的边即可。

完整代码：

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e6+5;
int fa[N];
int Find(int x){//并查集
	if(x==fa[x])return x;
	return fa[x]=Find(fa[x]);
}
int n,m;
struct node{
	int v,u,w;
}e[N];
bool cmp(node x,node y){//把边从小到大排序
	return x.w<y.w;
}
int sum=0;
void kru(){//最小生成树
	memset(e,0,sizeof(e));
	sum=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
		sum+=e[i].w;
	}
	for(int i=0;i<n;i++)fa[i]=i;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		int x=Find(e[i].u);
		int y=Find(e[i].v);
		if(x==y)continue;
		sum-=e[i].w;
		fa[x]=y;
	}
	printf("%d\n",sum);	
}
int main(){
	while(1){
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)break;
		else kru();
	}
	return 0;
}
```



---

## 作者：fyc123 (赞：1)


一句话题意：给定一个图，删去最多的边且保证图联通。

思路：用边权之和减去给定图补图的最小生成树权值和。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
//十年OI一场空，不开long long见祖宗
using namespace std;
const int N=2e5+9;
struct node{
	int u,v,w;
}edge[N];
int n,m,sum=0,fa[N],ran[N];
void init(int n){
//初始化并查集，把每个节点的父亲设为他本身
	for(int i=0;i<=n;i++){
		ran[i]=0,fa[i]=i;
	}
}
int find(int x){
//路径压缩
	if (x==fa[x]){
		//找到了就返回
     return fa[x];
	}
	return fa[x]=find(fa[x]);
	//否则就继续去找
}
void merge(int a,int b){
//按秩合并
	if (ran[a]<ran[b]){
    //把a的父亲设为b
		fa[a]=b;
	}
	else{
		if(ran[a]==ran[b]){
			ran[a]++;
		}
     //否则把b的父亲设为a
		fa[b]=a;
	}
}
bool cmp(node a,node b){
//按边权从小到大排序，也可以重载运算符
	return a.w<b.w;
}
int kruskal(int n,int m){
	sort(edge,edge+m,cmp);
	init(n);
    int ans=0;
	for(int i=0;i<m;i++){
		int fx=find(edge[i].u),fy=find(edge[i].v);
		if(fx!=fy){ 
			merge(fx,fy);
			ans+=edge[i].w;
        //统计权值和
		}
	}
	return ans;
}
signed main(){
    ios::sync_with_stdio(false);//读入优化
	while(cin>>n>>m&&n+m){
		sum=0;//每组数据都要把总权值和设为0
		for (int i=0;i<m;i++){
			cin>>edge[i].u>>edge[i].v>>edge[i].w;
			sum+=edge[i].w;
		}
		cout<<sum-kruskal(n,m)<<endl;
        //输出答案，记得换行
	}
	return 0;
}
```


---

## 作者：_YyD_ (赞：1)

**题意：**

求能一个图能删去最多的边权且保证图还是连通图

**做法：**

将题意可转化为求最小生成树的补图的权值之和。

那就可以求出最小生成树，再用 $z$ 的总和减去最小生成树的权值和。

**Code：**

```cpp
#include<bits/stdc++.h>
#define _ ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define lep(i,l,r) for(int i=l;i>=r;i--)
using namespace std;
inline int read() {
	int X=0;
	bool flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') flag=0;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		X=(X<<1)+(X<<3)+ch-'0';
		ch=getchar();
	}
	if(flag) return X;
	return ~(X-1);
}
struct node {
	int u,v,w;
} tree[200005];
int fa[200005],n,m,ans,eu,ev,cnt;
bool cmp(node a,node b) {
	return a.w<b.w;
}
int find(int x) {
	while(x!=fa[x]) x=fa[x]=fa[fa[x]];
	return x;
}
void kruskal() {
	sort(tree,tree+m,cmp);
	rep(i,0,m-1) {
		eu=find(tree[i].u), ev=find(tree[i].v);
		if(eu==ev) {
			continue;
		}
		ans+=tree[i].w;
		fa[ev]=eu;
		if(++cnt==n-1) {
			break;
		}
	}
}
int main() {
	while(cin>>n>>m,n&&m) {
		long long sum=0;
		ans=0;
		rep(i,1,n) {
			fa[i]=i;
		}
		rep(i,0,m-1) {
			tree[i].u=read(),tree[i].v=read(),tree[i].w=read();
			sum+=tree[i].w;
		}
		kruskal();
		cout<<sum-ans<<endl;
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

rt，我们只需使用 Kruskal 或 Prim 算法求一遍最小生成树，然后拿总边权减去这个最小生成树的大小即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int F[200005];
int find(int x){
	if(x==F[x]) return x;
	F[x]=find(F[x]);
	return F[x];
}
void add(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return ;
	F[x]=y;
}
const int N=2E5+5;
struct Edge{
	int u,v,w;
}a[N];
bool cmp(Edge x,Edge y){
	return x.w<y.w;
}
signed main(){
	int n,m,ll=0;
	while(cin>>n>>m){
	    ll=0;
	    if(n==0&&m==0) return 0;
    	for(int i=0;i<=n;++i){
    		F[i]=i;
    	}
    	for(int i=1;i<=m;++i){
    		cin>>a[i].u>>a[i].v>>a[i].w;
    		ll+=a[i].w;//总边权
    	}
    	sort(a+1,a+m+1,cmp);
    	int q=0,ans=0;
    	for(int i=1;i<=m;++i){
    		int x=find(a[i].u),y=find(a[i].v);
    		if(x==y){
    			continue;
    		}else{
    			ans+=a[i].w;
    			add(a[i].u,a[i].v);
    			++q;
    		}
    		if(q==n-1){
    			break;
    		}
    	}
    	cout<<ll-ans<<endl;
	}
	return 0;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA11631)
## 思路
很明显，是一道最小生成树板子题。

这里用 Kruskal 算法，用并查集维护选中的道路，使最终需要用的答案最小，省下来的钱就最大。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

struct node
{
	int x, y, z;
	void read()
	{
		scanf("%d%d%d", &x, &y, &z);
	}
} a[N];

int T, n, m, sum;
int fa[N]; // 存储每一个节点的祖先

bool cmp(node x, node y)
{
	return x.z < y.z;
}

int find(int x) // 并查集模板
{
	return x == fa[x] ? x : fa[x] = find(fa[x]); 
}

void kruskal()
{
	int ans = 0, cnt = 0; // ans 是需要用的钱数，cnt 是已建道路
	for (int i = 1; i <= m; i++)
	{
		int f1 = find(a[i].x), f2 = find(a[i].y);
		if (f1 == f2) continue;
		fa[f1] = f2;
		cnt++;
		ans += a[i].z;
	}
	printf("%d\n", sum - ans);
}

int main()
{
	while (scanf("%d%d", &n, &m))
	{
		if (!n && !m) return 0;
		sum = 0;
		for (int i = 0; i < n; i++)
			fa[i] = i;
		for (int i = 1; i <= m; i++)
		{
			a[i].read();
			sum += a[i].z;
		}
		sort(a + 1, a + m + 1, cmp); // 每一次选择边权尽可能小的路
		kruskal();
	}
   	return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

[原题链接](https://www.luogu.com.cn/problem/UVA11631)   
[博客链接](https://www.luogu.com.cn/blog/533160/solution-uva11631)
### Part.1 题目大意    
给定一个无向图，求在删去一些边后仍然使各个点相连的情况下，删去边的边权和最大是多少。 
### Part.2 思路    
很明显，保留下来的是最小生成树，这样就使删去的边权和最大。我们只需要用一个 $sum$ 来表示总边权和，用 $ans$ 表示 MST 的边权和，输出 $sum-ans$ 即可。   
### Part.3 代码    
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2000010;
struct node{int x,y,z;}a[maxn];
int father[maxn],n,m,ans,cnt,sum;
void init(){for(int i=1;i<=n;i++)father[i]=i;}//初始化
bool cmp(node x,node y){return x.z<y.z;}
int get(int x)
{
	if(father[x]==x)return x;
	return father[x]=get(father[x]);//路径压缩
}
void merge(int x,int y){if(get(x)!=get(y))father[get(y)]=get(x);}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(true)
	{
		cin>>n>>m;
		if(n==0&&m==0)break;
		sum=0,ans=0,cnt=0;//多测不清空，爆零两行泪
		init();
		for(int i=1;i<=m;i++)
		{
			cin>>a[i].x>>a[i].y>>a[i].z;
			a[i].x++,a[i].y++;//注意题目点是从 0 开始的
			sum+=a[i].z;
		}
		sort(a+1,a+m+1,cmp);
		for(int i=1;cnt<=n-1&&i<=m;i++)
		{
			if(get(a[i].x)!=get(a[i].y))
			{
				merge(a[i].x,a[i].y);
				cnt++;
				ans+=a[i].z;
			}
		}
		cout<<sum-ans<<'\n';		
	}
	return 0;
}
```

---

## 作者：Fireworks_Rise (赞：0)

# 题意

对于一张连通图，删掉其中的一些边，要使图仍然保证连通，求删掉的边之和的最大值。

# 解题思路

题目需求删掉的边之和的最大值，可以想到用最小生成树做。

所谓是“正难反则易”，那么我们只需要先把整张图中所有的边权加起来，跑一边 kruskal，减去其路径上所有的边权即可。

也是非常简单的模板题...

下面贴上蒟蒻的小小代码。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int oo=0x3f3f3f3f;
const int N=1e6+10;
int n,m,res;
struct Edge {
	int x,y,z;
}edge[N<<1];
int fa[N];
bool cmp(Edge x,Edge y) {
	return x.z<y.z;
}
void init_() {
	for(int i=0;i<=n;i++)
		fa[i]=i;
}
int findp(int x) {
	if(fa[x]==x) return x;
	return fa[x]=findp(fa[x]);
}
void kruskal() {
	for(int i=1;i<=m;i++) {
		int u=edge[i].x;
		int v=edge[i].y;
		int w=edge[i].z;
		int xp=findp(u);
		int yp=findp(v);
		if(xp!=yp) {
			res-=w;
			fa[xp]=yp;
		}
	}
	return ;
}
signed main() {
	while(scanf("%lld%lld",&n,&m)&&n) {
		res=0;
		init_();
		for(int i=1;i<=m;i++) {
			scanf("%lld%lld%lld",&edge[i].x,&edge[i].y,&edge[i].z);
			res+=edge[i].z;
		}
		sort(edge+1,edge+m+1,cmp);
		kruskal();
		printf("%lld\n",res);
	}
	return 0;
}
```


---

## 作者：Garbage_fish (赞：0)

## 题目翻译：

给你一个有 $m$ 个点 $n$ 条边的连通图，让你删掉一些边，删掉的边的权值的和越大越好，但是要保证图仍连通，输出删掉的边的权值和的最大值。

有多组数据，每组数据先输入一行 $m,n$，再输入 $n$ 行，每一行输入 $u,v,w$，表示 $u$ 和 $v$ 之间有一条长度为 $w$ 的边。

**$u$ 和 $v$ 的范围是 $0\le u,v<m$！！！**

## 题解部分：

看完题目翻译，学过最小生成树的应该都会了吧，只需要用整棵树的权值和减去最小生成树的权值和就好了。

没学过的可以先做[这道模板题](https://www.luogu.com.cn/problem/P3366)。

~~都找得到这题了没有没学过最小生成树的了吧。~~

**[AC](https://www.luogu.com.cn/record/124690635) Code：**

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair <int,int>
using namespace std;
void fread(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
const int N=2e5+10,inf=0x7fffffff;
int n,m,dis[N],cnt,ans,f[N];
bool vis[N];
struct EDGE{
	int u,v,w;
}edge[N*2];
bool cmp(EDGE x,EDGE y){
	return x.w<y.w;
}
int gf(int x){
	if(f[x]!=x)f[x]=gf(f[x]);
	return f[x];
}
void kruskal(){
	for(int i=0;i<=n;i++){
		f[i]=i;
	}
	cnt=0;
	for(int i=1;i<=m;i++){
		int u=edge[i].u;
		int v=edge[i].v;
		int w=edge[i].w;
		int fu=gf(u);
		int fv=gf(v);
		if(fu!=fv){
			f[fu]=fv;
			ans-=w;
		}
	}
}
signed main(){
	fread();
	while(1){
		cin>>n>>m;
		if(!n and !m)return 0;
		ans=0;
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			ans+=w;
			edge[i]=(EDGE){u,v,w};
		}
		sort(edge+1,edge+m+1,cmp);
		kruskal();
		cout<<ans<<"\n";
	} 
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

## 题意

（此处 $n,m$ 与原题含义相反）给出 $n$ 个点、$m$ 条边的无向连通图。现在要求出：在所有点能够互相连通的前提下，删去边权总和的最大值。 

## Solution

最小生成树板子题。

总的边权和不变，删去的边权之和最大意味着保留的边权值和最小。同时我们要保证任意两点可以连通，很容易发现最终保留的就是原图的一棵 $\text{MST}$。

因此，答案为总边权和（输入时即可求出）减去 $\text{MST}$ 中的边权和（在跑 $\text{Kruskal}$ 或 $\text{Prim}$ 时计算）。


```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,m,tot,ans,fa[N];

int find(int x){
	return x==fa[x] ? x : fa[x]=find(fa[x]);
}

void unity(int x,int y){
	fa[find(x)]=find(y);
}

struct edge{
	int u,v,w;
	bool operator < (const edge &e) const{
		return w<e.w;
	}
}e[N];

bool solve(){
	n=wrd(),m=wrd(),ans=tot=0;
	if(!n) return 0;
	
	for(int i=0;i<n;++i) fa[i]=i;
	for(int i=1;i<=m;++i) e[i]={wrd(),wrd(),wrd()},ans+=e[i].w;
	sort(e+1,e+m+1);
	
	for(int i=1;i<=m;++i){
		if(find(e[i].u)^find(e[i].v)){
			unity(e[i].u,e[i].v),++tot,ans-=e[i].w;
			if(tot==n-1) break;
		}
	}
	return printf("%lld\n",ans),1;
}

main(){
	while(solve());
	return 0;
}
```

---

## 作者：Maysoul (赞：0)

建议浏览:[P2820](https://www.luogu.com.cn/problem/P2820)

简述一下题意：将一个图的某些边删去后仍保留原图的连通性，求被删除的边的最大值。

显然，要使删去的边最大，等价于使剩下的边长度最小。那我们就可以把它转化为最小生成树问题。

其他题解好像都是 Kruskal 算法，那我就用一下 Prim 算法吧。

Prim 算法的思想就是以任意节点为根，再找出与之相邻的所有边，选取最小的一条放入生成树中，以此类推，直到生成树构建完成为止。

```
//2023/5/8
//别着急，先通读一遍题目
//别忘了开long long
//写完先看一遍怎么降复杂度
//要么开全局变量要么给定初值
//想想看，有什么情况需要特判
//看看数组开的够不够大
//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int num,ans;
int n,m;
int head[1100000];
int vis[1100000];
int escnt;
struct node{
	int dis,id,f;
	node()
	{
		f=0;id=0;dis=0;
	}
	node(int az,int bz,int cz)
	{
		f=az;id=bz;dis=cz;
	}
};
auto cmp=[](node x,node y)->bool{return x.dis>y.dis;};
priority_queue<node,vector<node>,decltype(cmp)> que(cmp);
struct linkstar{
	int to,from,w,next;
}edge[1100000];
void add(int from,int to,int w)
{
	edge[++escnt].from=from;
	edge[escnt].to=to;
	edge[escnt].w=w;
	edge[escnt].next=head[from];
	head[from]=escnt;
}
int Prim()
{
	int result=0;
	int rcnt=0;
	memset(vis,0,sizeof(vis));
	que.push(node(-1,0,0));
	while(rcnt<n)
	{
		if(que.empty())
		{
			return 0;
		}
		node cp=que.top();
		que.pop();
		if(vis[cp.id]) continue;
		vis[cp.id]=1;
		rcnt++;
		if(rcnt>1) 
		{
			result+=cp.dis;
		}
		for (int i=head[cp.id];i!=-1;i=edge[i].next)
		{
			if(!vis[edge[i].to])
			{
				que.push(node(cp.id,edge[i].to,edge[i].w));
			}
		}
	}
	return result;
}
int main()
{
	memset(head,-1,sizeof(head));
	cin>>n>>m;
	while(m!=0&&n!=0)
	{
		for (int i=1;i<=m;i++)
		{
			int x,y,w;
			cin>>x>>y>>w;
			add(x,y,w);
			add(y,x,w);
			num+=w;
		}
		cout<<num-Prim()<<endl;
		cin>>n>>m;
		num=0;
		memset(head,-1,sizeof(head));
		while(que.size())
		{
			que.pop();
		}
		escnt=0;
	}
	return 0;
}

```


---

