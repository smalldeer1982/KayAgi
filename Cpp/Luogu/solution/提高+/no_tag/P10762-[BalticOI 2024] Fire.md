# [BalticOI 2024] Fire

## 题目背景

翻译自 [BalticOI 2024 Day2 T1](https://boi2024.lmio.lt/tasks/d2-fire-statement.pdf)。

## 题目描述

我们将一天划分为 $M$ 个时间，同时有 $N$ 个人，每个人愿意工作的时间分别为 $(s_i,e_i)$，如果 $s_i > e_i$，说明这个人愿意工作到第二天的 $e_i$ 时间，每个人最多连续工作时间不会超过一整天。

你需要安排一些人工作，使得他们工作时间可以覆盖一整天，请求出这个人数。

## 说明/提示

对于第一组样例，选择 $1,2,4$。

对于第二组样例，显然无解。

| 子任务编号 | 特殊性质 | 分值 |
| :-----------: | :----------- | :-----------: |
| $1$ | $N \leq 20$ | $14$ |
| $2$ | $N \leq 300$ | $17$ |
| $3$ | $N \leq 5000$ | $9$ |
| $4$ | 保证 $s_i < e_i$ 或 $e_i = 0$ | $13$ |
| $5$ | 保证每个人工作的时间相同 | $21$ |
| $6$ | 无特殊性质 | $26$ |

对于所有数据，$1 \leq N \leq 2 \times 10^5$，$2 \leq M \leq 10^9$，$0 \leq s_i,e_i < M$。

## 样例 #1

### 输入

```
4 100
10 30
30 70
20 40
60 20```

### 输出

```
3```

## 样例 #2

### 输入

```
1 100
30 40```

### 输出

```
-1```

# 题解

## 作者：北文 (赞：5)

建议管理增加描述：  
要覆盖所有时间而不是所有整点！（调了很久）  

那么讲讲这题怎么做。  
这题有个很显然的贪心策略：如果已经选取了一段，那么在选取的这段中，选取能往后延伸最长的那一个进行扩展。  
但是也有一个显然的问题，那就是不知道第一个取哪一个。怎么确定呢，枚举吗？也许只能枚举。  
那么我们考虑加速这个贪心过程。选取哪一个作为第一个并不影响每一个位置的决策，考虑用倍增进行优化。  
记 $f[i][j]$ 表示在第 $i$ 个位置**再选取** $2^j$ 个人能到达什么位置，f 数组的计算可以用 dp，这都是比较简单的。  
还有就是数据范围太大需要离散化处理。  

我的代码是建立在覆盖所有整点的题意上改过来的，所以有亿点丑。  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5, inf=1e9;
int n, lsh[N*3], m, cn, f[N*3][21], nn;
pair<int, int> a[N*3], b[N*3];
#define fi first
#define se second
bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.fi<b.fi; 
}
inline void ckmax(int &x, int y) { if(y>x) x=y; }
int main() {
	scanf("%d %d", &n, &nn);
	for(int i=1; i<=n; i++) {
		scanf("%d %d", &a[i].fi, &a[i].se);
		lsh[++m]=a[i].fi; lsh[++m]=a[i].se;
		if(a[i].fi!=0)
		lsh[++m]=a[i].fi-1; 
		if(a[i].se!=0)
		lsh[++m]=a[i].se-1;
		if(a[i].fi!=nn-1)
		lsh[++m]=a[i].fi+1; 
		if(a[i].se!=nn-1)
		lsh[++m]=a[i].se+1;
	}
	lsh[++m]=nn-1;
	lsh[++m]=0;
	sort(lsh+1, lsh+1+m);
	m=unique(lsh+1, lsh+1+m)-lsh-1;
	for(int i=1; i<=n; i++)
		a[i].fi=lower_bound(lsh+1, lsh+1+m, a[i].fi)-lsh-1,
		a[i].se=lower_bound(lsh+1, lsh+1+m, a[i].se)-lsh-1; 
	for(int i=1; i<=n; i++) {
		if(a[i].fi<a[i].se) {
			b[++cn]=a[i];
			b[++cn]={a[i].fi+m, a[i].se+m};
		} else {
			b[++cn]={a[i].fi, a[i].se+m};
		}
	}
	for(int i=1; i<=cn; ++i) {ckmax(f[b[i].fi][0], b[i].se);}
	for(int i=0; i<=m*2; ++i) {ckmax(f[i+1][0], f[i][0]);}
	for(int k=1; k<=18; ++k) {
		for(int i=0; i<=m*2; ++i)
			f[i][k]=f[f[i][k-1]][k-1];
		for(int i=0; i<=m*2; ++i)
			ckmax(f[i+1][k], f[i][k]);
	}
	int ans=inf;
	for(int i=0; i<m; ++i) {
		int u=i, t=0;
		for(int k=18; k>=0; --k) {
			if(f[u][k]<=i+m-1) {
				t+=1<<k; 
				u=f[u][k];
			}
		}
		if(f[u][0]>i+m-1) {
			ans=min(ans, t+1);
		}
	}
	if(ans>=inf) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
} 
```

---

## 作者：CQ_Bab (赞：3)

# 前言
题目中的区间为左闭右开。
# 思路
首先我们考虑定义一个基于贪心的状态为 $f_{i,j}$ 表示所选的区间包含 $i$ 一共选了 $j$ 个区间能到达的最大的右端点，然后我们发现这样是 $n^2$ 的所以考虑用倍增进行优化，$f_{i,j}$ 表示所选的区间包含 $i$ 一共选了 $2^j$ 个区间能到达的最大的右端点，转移与普通的倍增相同 $f_{i,j}=f_{f_{i,j-1},j-1}$。然后我们考虑如何统计答案，发现如果固定必须要包含的区间 $l\sim r$ 就可以求出最少用的区间了，所以我们考虑去枚举左端点 $i$ 然后能算出他需要覆盖到的地方为 $i+m$（毕竟左闭右开）然后我们就可以去暴力跳看是否满足条件，最后我们只需要判断当前到的点 $x$ 完后跳一个区间是否能跳到 $i+m$ 及以后就行了，因为这道题的范围较大所以要离散化。

又因为这道题有 $l>r$ 的情况所以我们考虑将一天变为两天即可。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,m;
const int N=8e5+10;
int f[N][20],tot;
int s[N],e[N],arr[N],idx;
vector<pair<int,int>>v;
void solve() {
	in(n),in(m);
	rep(i,1,n) {
		in(s[i]),in(e[i]);
		if(s[i]>e[i]) e[i]+=m,arr[++tot]=s[i],arr[++tot]=e[i],v.pb({s[i],e[i]});
		else {
			arr[++tot]=s[i];
			arr[++tot]=e[i];
			arr[++tot]=s[i]+m;
			arr[++tot]=e[i]+m;
			v.pb({s[i],e[i]});
			v.pb({s[i]+m,e[i]+m}); 
		}
	}
	sort(arr+1,arr+1+tot);//离散化
	idx=unique(arr+1,arr+1+tot)-arr-1;
	for(auto to:v) {
		to.first=lower_bound(arr+1,arr+1+idx,to.first)-arr;
		to.second=lower_bound(arr+1,arr+1+idx,to.second)-arr;
		f[to.first][0]=max(f[to.first][0],to.second);
	}
	int res=INT_MAX;
	rep(i,1,idx) f[i][0]=max(f[i][0],f[i-1][0]);
	rep(j,1,19) {
		rep(i,1,idx) f[i][j]=f[f[i][j-1]][j-1];
		rep(i,1,idx) f[i][j]=max(f[i][j],f[i-1][j]);
	}
	rep(i,1,idx) {
		int r=false,x=i;
		int id=lower_bound(arr+1,arr+1+idx,arr[i]+m)-arr;
		if(arr[id]<arr[i]+m) break;//相当于将区间变为了闭区间所以要将目标区间的右端点也加一
		rep1(j,19,0) {//暴力跳
			if(arr[f[x][j]]<arr[i]+m) {
				x=f[x][j];
				r+=(1<<j);
			}
		}
		if(arr[f[x][0]]>=arr[i]+m) r++;//最多再跳一步看是否满足条件
		else continue;
		res=min(res,r); 
	}
	if(res==INT_MAX) puts("-1");
	else printf("%lld\n",res);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：LDR___ (赞：3)

## 题解
提供一种使用最短路算法的做法。

由于 $M$ 范围太大，先将所有时间离散化。

---
先假设没有 $s_i\gt e_i$ 的情况，此时有一种经典的建图方法：

- 对于所有的 $i \in [1,N]$，从 $s_i$ 向 $e_i$ 连一条权值为 $1$ 的边。
- 对于所有的 $i \in [1,M]$，从 $i$ 向 $i-1$ 连一条权值为 $0$ 的边。
 
 
答案即为 $0$ 到 $M$ 的最短路。

（正确性证明就不讲了，请自行理解）

---
再考虑 $s_i\gt e_i$ 的情况：（为了方便，下文称其为上夜班）

若拆成 $(0,e_i)$ 和 $(s_i,M)$ 两条边，我们会发现会有重复统计的情况。

于是可以将每个边 $(0,e_i)$ 标记颜色 $i$，跑最短路的同时维护每个点的颜色 $col_u$，表示点 $u$ 的最短路需要经过颜色为 $col_u$ 的边。

统计答案时，枚举每个上夜班的人 $i$，若 $col_{s_i}=i$，说明 $i$ 在之前已经统计过了，答案为 $dis_i$，否则答案为 $dis_i+1$。

时间复杂度 $O(n \log n)$。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+5,M=8e5+5,inf=1e9;
int n,m,tot,siz,ans=inf;
int s[N],t[N];
int dis[N],col[N],vis[N];
vector<int>v;
struct edg{
	int v,w,nxt,col;
}e[M];
int head[N];
void add(int u,int v,int w,int col){
	e[++tot].v=v;
	e[tot].w=w;
	e[tot].nxt=head[u];
	head[u]=tot;
	e[tot].col=col;
}
struct A{
	int u,dis;
};
bool operator <(const A &x,const A &y){
	return x.dis>y.dis;
}
void dijk(int s){
	for(int i=0;i<=m;i++)dis[i]=inf;
	dis[s]=0;
	priority_queue<A>q;
	q.push(A{s,0});
	while(!q.empty()){
		A x=q.top();q.pop();
		vis[x.u]=1;
		for(int i=head[x.u];i;i=e[i].nxt){
			int v=e[i].v,w=e[i].w,c=e[i].col;
			if(vis[v])continue;
			if(dis[x.u]+w<dis[v]){
				dis[v]=dis[x.u]+w;
				col[v]=max(col[x.u],c);
				q.push(A{v,dis[v]});
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&s[i],&t[i]);//t[i]即为题目的e[i] 
		v.push_back(s[i]);
		v.push_back(t[i]);
	}
	v.push_back(0);
	v.push_back(m);
	sort(v.begin(),v.end());
	siz=unique(v.begin(),v.end())-v.begin();
	for(int i=1;i<=n;i++){
		s[i]=lower_bound(v.begin(),v.begin()+siz,s[i])-v.begin();
		t[i]=lower_bound(v.begin(),v.begin()+siz,t[i])-v.begin();
	}
	m=lower_bound(v.begin(),v.begin()+siz,m)-v.begin();
	for(int i=1;i<=n;i++){
		if(s[i]<t[i])add(s[i],t[i],1,0);
		else if(s[i]>t[i]){
			add(0,t[i],1,i);
		}
	}
	for(int i=0;i<m;i++)add(i+1,i,0,0);
	dijk(0);
	ans=dis[m];//有可能没有人上夜班 
	for(int i=1;i<=n;i++){
		if(s[i]<=t[i])continue;
		ans=min(ans,dis[s[i]]+(col[s[i]]!=i));
	}
	if(ans>=inf)cout<<-1;
	else cout<<ans;
	return 0;
}/*
*/
```

---

## 作者：george0929 (赞：3)

前置知识：**贪心**，**倍增**。

首先断环为链，若 $s_i>e_i$，则令 $e_i\leftarrow e_i+M$。

题意转换为选出尽可能少的区间，覆盖长度为 $M$ 的区间。

考虑一个 $O(n^2)$ 的做法：

- 将区间按右端点升序排序。
- 枚举第一个区间，以这个区间的 $s$ 作为起点。
- 进行最少区间覆盖的贪心套路：每次选出左端点小于当前右端点中右端点最大的一个区间。

考虑优化：

注意到第三步中，满足【左端点小于当前右端点中右端点最大的一个区间】是唯一且确定的，所以可以倍增优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int l,r,id,mxr;
}a[200005],b[200005];
bool cmpl(node a,node b){
	if(a.l==b.l) return a.r<b.r;
	return a.l<b.l;
}
bool cmpr(node a,node b){
	if(a.r==b.r) return a.l<b.l;
	return a.r<b.r;
}
int f[200005][21];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		if(a[i].r<a[i].l) a[i].r+=m;
	}
	sort(a+1,a+1+n,cmpr);
	for(int i=1;i<=n;i++){
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmpl);
	for(int i=1;i<=n;i++){
		b[i].l=a[i].l,b[i].r=a[i].r,b[i].id=a[i].id;
	}
	sort(a+1,a+1+n,cmpr);
	int now=1,mx=0;
	for(int i=1;i<=n;i++){//预处理 f[i][0]
		while(now<=n&&b[now].l<=a[i].r){
			if(!mx||b[mx].r<b[now].r){
				mx=now;
			}
			now++;
		}
		a[i].mxr=b[mx].id;
	}
	for(int i=1;i<=n;i++){
		if(a[i].mxr==a[i].id) a[i].mxr=0;
	}
	for(int i=1;i<=n;i++){
		f[i][0]=a[i].mxr;
	}
	for(int j=1;j<=20;j++){//倍增预处理
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	int ans=1e9;
	for(int st=1;st<=n;st++){//枚举第一个区间
		int L=a[st].l,R=a[st].l+m,res=1,now=st;
		for(int i=20;i>=0;i--){//倍增
			if(f[now][i]&&a[f[now][i]].r<R){
				res+=(1<<i);
				now=f[now][i];
			}
		}
		if(f[now][0]&&a[f[now][0]].r>=R){
			res++;
			ans=min(ans,res);
		}
	}
	if(ans>n){
		cout<<-1;
	}else{
		cout<<ans;
	}
	return 0;
} 
```

---

## 作者：To_our_starry_sea (赞：2)

### Solution
本题在题意上有些问题，覆盖一整天指的是能覆盖区间 $[s, s + M]$，即覆盖了所有的时刻（第一二天不区分）。

首先如果你做过 [CF1175E Minimal Segment Cover](https://www.luogu.com.cn/problem/CF1175E)，你会发现这道题其实是那题的双倍经验。考虑本题值域较大，我们自然地将所有人工作时间的端点进行离散化，注意对于 $s_i > e_i$ 的情况，我们将 $e_i \gets e_i + M$。容易的，我们可以把问题转化为已知 $n$ 条覆盖了 $[l_i, r_i]$ 的线段，对于正整数 $i$ 满足 $1 \le i \le M$，求出能覆盖区间 $[i,i + M]$ 的最少线段数量。

接着我们预处理出从每一个点出发经过***仅***一条线段所能到达的最远点，记为 $dp_{i, 0}$。然后我们还需要从小到大依序扫描每个点，若 $j < i$ 且 $dp_{j, 0} > dp_{i, 0}$，那么 $dp_{i, 0} \gets dp_{j, 0}$。因为线段在彼此覆盖时可能会有重叠的地方。

然后我们套路的用倍增求出 $dp_{i, j}$，即以 $i$ 为左端点用 $2^j$ 条线段能覆盖的最远端点。求答案的时候类似 LCA 的，倍增跳远端点即可。

时空复杂度都是 $O(n \log n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int n, m, cnt = 0, b[MAXN << 2], maxn[MAXN << 2], dp[MAXN << 2][21];
struct node {
	int s, e;
} a[MAXN << 2];
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) {
		a[i].s = read(), a[i].e = read();
		if (a[i].s > a[i].e) a[i].e += m;
		b[++cnt] = a[i].s, b[++cnt] = a[i].e;
	}
	sort(b + 1, b + cnt + 1);
	cnt = unique(b + 1, b + cnt + 1) - b - 1;
	for (int i = 1; i <= n; i++) {
		int way = lower_bound(b + 1, b + cnt + 1, a[i].s) - b;
		a[i].s = way;
		way = lower_bound(b + 1, b + cnt + 1, a[i].e) - b;
		a[i].e = way;
	}
	for (int i = 1; i <= n; i++) maxn[a[i].s] = max(maxn[a[i].s], a[i].e);
	for (int i = 1; i <= cnt; i++) maxn[i] = max(maxn[i], maxn[i - 1]), dp[i][0] = maxn[i];
	for (int j = 1; j <= 20; j++) {
		for (int i = 1; i <= cnt; i++) dp[i][j] = dp[dp[i][j - 1]][j - 1];
	}
	int ans = n + 1;
	for (int i = 1; i <= n; i++) {
		int l = a[i].s, r = b[a[i].s] + m, res = 0;
		for (int j = 20; j >= 0; j--) {
			if (b[dp[l][j]] < r) l = dp[l][j], res += (1 << j);
		}
		if (b[dp[l][0]] >= r) ans = min(ans, res + 1);
	}
	if (ans == n + 1) puts("-1");
	else printf("%d\n", ans);
	return 0;
}
```

---

## 作者：nahidaa (赞：0)

## [传送门](https://www.luogu.com.cn/problem/P10762)

## 题目补充：
区间为左闭右开

## 思路：
首先是一个简单的贪心思路：如果已经选取了一段，下一个被选择要合并的段左端符合可以合并的情况下，选取右端最远的情况下最优。（为方便，将以上操作记为“操作1”）

但是如此一来，则需要枚举一个段作为首段，时间复杂度：$O(n^2)$ ，这是我们所不能接受的。

通过思考，我们又可以发现：对于每次访问到同一个段时，“操作1”的结果不变。因此想到可以用倍增来解决问题，实现以 $O(n\log_{}{n})$ 为时间复杂度解决问题。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,l,r,bei[200005][30],big,now,ge;
struct duan{
	int x,y;
}d[200005];
bool com(const duan& x,const duan& y){
	if(x.x==y.x)return x.y>y.y;
	return x.x<y.x;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>d[i].x>>d[i].y;
		if(d[i].x>d[i].y){
			d[i].y+=m;
		}
	}
	sort(d+1,d+n+1,com);
	r=0;
	for(int i=1,far=0,farh;i<=n;++i){
		while(d[r+1].x<=d[i].y&&r<n){
			r++;
			if(far<d[r].y){
				far=max(far,d[r].y);
				farh=r;
			}
		}
		if(far>d[i].y){
			bei[i][0]=farh;
		}else{
			bei[i][0]=-1;
		}
	}
	for(int i=1;i<=20;++i){
		for(int j=1;j<=n;++j){
			if(bei[j][i-1]==-1)bei[j][i]=-1;
			else bei[j][i]=bei[bei[j][i-1]][i-1];
		}
	}
	big=2e9;
	for(int i=1;i<=n;++i){
		ge=1;
		now=i;
		for(int j=20;j>=0;--j){
			if(bei[now][j]!=-1&&d[bei[now][j]].y<=d[i].x+m-1){
				ge+=1<<j;
				now=bei[now][j];
			}
		}
		if(bei[now][0]!=-1){
			ge++;
			big=min(big,ge);
		}
	}
	cout<<(big!=2e9 ? big : -1)<<"\n";
	return 0;
}
```

---

## 作者：Exp10re (赞：0)

模拟赛没有说明覆盖时间，被硬控两发罚时。

## 解题思路

题意等价于给定若干环上线段，要求取其中若干段覆盖环。

以上又等价于选取最少数量的线段使其连续覆盖长度至少为 $n$ 的区间。

因为题意是覆盖给定长度的区间，起点不明确，常规全覆盖策略很难实现。而在某个已知的覆盖方案的基础上选取一条线段使得新覆盖的总长度最大本身就是一个很典的贪心：将所有区间按左端点排序，右端点排序，双指针即可求解。

根据已知信息，我们可以得到一个经典暴力做法：钦定一条线段的末端为起点，然后按照上述求解的方案进行贪心覆盖，时间复杂度 $O(n^2)$。

考虑优化：我们在得到“在某个已知的覆盖方案的基础上选取一条线段使得新覆盖的总长度最大”的策略的基础上可以使用倍增得到“在某个已知的覆盖方案的基础上选取 $2^w$ 条线段使得新覆盖的总长度最大”的策略。

每一个方案都是独立的，与起点无关，因此用倍增可以加速上述过程得到 $O(n\log n)$ 复杂度的做法，预处理也是 $O(n\log n)$ 的，故总时间复杂度为 $O(n\log n)$。

无解的充分条件为存在一个线段右端点不被其他线段右端点在该端点右端的线段包含，扫一遍就能判无解。

---

## 作者：wchengk09 (赞：0)

本题其实就是区间覆盖问题，只不过是环上的区间覆盖。只要我们能把环处理好，这道题就解决了。

考虑 **破环为链**，将一天 $[0,m)$ 的时间复制一份，变成 $[0,2m)$。然后对于原题中的每一个人 $(s_i,t_i)$，执行以下流程：

- 如果 $s_i\leq t_i$（也就是这个人的工作没有跨天），则新增两个区间 $[s_i,t_i)$ 和 $[s_i+m,t_i+m)$。
- 如果 $s_i>t_i$（也就是这个人工作到了第二天），则新增一个区间 $[s_i,t_i+m)$。

然后就是一个重要的 **引理** ：

> 如果上述新增的区间可以覆盖 $[0,2m)$ 中 **任意一个长度为 $m$ 的区间 $[l,l+m)$**，原问题就有解。

正确性显然。因为一个长度为 $m$ 的区间刚好是一整天的时间，你只需要对于每一天重复使用该覆盖方式即可。

  并且不难发现，对于所有长度为 $m$ 的时间区间 $[l,l+m)$，我们都求一下最少需要多少个区间才能覆盖它，最后取 $\min$，就是答案。

怎么求呢？

## 方法一

枚举区间 $[l,l+m)$ 的起始点 $l$，然后暴力跑一遍区间覆盖。

这样做的时间复杂度为 $O(nm)$，无法通过本题。

## 方法二

我们假设新增的区间为 $q_1,q_2,\ldots,q_n$。

我们枚举选择的第一个区间 $q_i$，然后每次找到 **与上一个区间有交集的最后一个区间** （经典区间覆盖问题的贪心策略），并选择该区间，直到选择的区间覆盖的总长度 $\geq m$。

时间复杂度为 $O(n^2)$，同样无法通过本题。

## 方法三

考虑如何加速上述贪心过程。

考虑 **建图** 。对于区间 $q_i$，我们可以通过二分（双指针也行）找到与它有交集的最后一个区间 $q_j$，并连一条 $i\rightarrow j$ 的边。

如果 $i$ 后面没有任何一个区间与 $i$ 有交集，则 $i$ 不连边。

容易发现，每个点最多有一条出边，而且最后一个点一定没有出边（因为最后一个区间后面就没区间了！），所以 $\text{边数}\leq\text{点数}-1$。因此，我们连出来的图一定是一个 **森林** 。

既然是森林，我们就先从最简单的情况开始考虑：这个森林中只有一棵树。

那么方法二的贪心过程就可以看作：选择树中的一个结点 $i$，然后不断跳 $i$ 的祖先，直到覆盖的总长度大于等于 $m$。

跳祖先？想到了什么？**倍增！**

类似倍增 LCA，我们设 $F_{i,j}$ 表示 $i$ 的第 $2^j$ 级祖先是谁。这个可以通过一次 DFS 求出来。求答案时，先枚举选择的第一个区间 $i$，然后倍增跳祖先，找到深度最浅的区间 $j$，使得 $i$ 到 $j$ 覆盖的总长度 $\geq m$。

对于多棵树的情况，不难发现每棵树都是独立的，因此对于每棵树都按照上述方法求一遍答案，最后取 $\min$ 即可。

时间复杂度 $O(n\log n)$，可以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e5 + 5;
int n,m;
struct Range{
    int l,r;
    Range(){}
    Range(int l,int r):l(l),r(r){}
};
Range rs[MAXN];
int top;
vector<int> G[MAXN];
int F[MAXN][21];
vector<int> roots;

inline bool operator < (Range a,Range b){
    return a.l < b.l;
}

// a in b
inline bool in(Range a,Range b){
    return a.l >= b.l && a.r <= b.r;
}

inline bool jiao(Range a,Range b){
    return !(a.r < b.l || b.r < a.l);
}

void dfs(int x){
    for (auto y : G[x]){
        F[y][0] = x;
        for (int i = 1;i <= 20;i ++)
            F[y][i] = F[F[y][i - 1]][i - 1];
        dfs(y);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    int top = n;
    for (int i = 1;i <= n;i ++){
        scanf("%d%d",&rs[i].l,&rs[i].r);
        if (rs[i].l <= rs[i].r)rs[++top] = Range(rs[i].l + m,rs[i].r + m);
        else rs[i].r += m;
    }
    n = top;
    sort(rs + 1,rs + n + 1);

    top = 0;
    for (int i = 1;i <= n;i ++){
        if (i == 1 || !in(rs[i],rs[top]))
            rs[++top] = rs[i];
    }
    n = top;
    
    for (int i = 1;i <= n;i ++){
        int l = i,r = n;
        while (l < r){
            int mid = (l + r + 1) >> 1;
            if (jiao(rs[i],rs[mid]))l = mid;
            else r = mid - 1;
        }
        if (r == i)roots.push_back(i);
        else G[r].push_back(i);
    }
    
    for (auto it : roots)
        dfs(it);
    
    int ans = 0x3f3f3f3f;
    for (int i = 1;i <= n;i ++){
        int cur = i,cnt = 1;
        for (int j = 20;j >= 0;j --){
            if (F[cur][j] && rs[F[cur][j]].r - rs[i].l < m){
                cur = F[cur][j];
                cnt += 1 << j;
            }
        }
        if (!F[cur][0])continue;
        if (rs[F[cur][0]].r - rs[i].l < m)continue;
        ans = min(ans,cnt + 1);
    }
    printf("%d",ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

首先我们可以断环为链。

设计状态 $dp_{i,j}$ 表示第一块木板放在位置 $i$ 处，填满 $[i,j]$ 这个区间所需要的最小木板数。

首先我们发现这个 dp 性质很优美，具体而言，有对于任意 $l1 \leq l2 \leq r_2 \leq r_1$ 而言，有 $dp_{l_2,r_2} \leq dp_{l1,r_1}$，然后可以考虑对于每一个位置 $i$ 处理出 $L_i$ 表示覆盖 $i$ 的木板的最小左端点，由于上面的性质，所以直接从最小左端点转移是正确的，也就是 $dp_{i,j} = dp_{i,L_j} + 1$，但是要注意的是 $dp_{j,j} = 0$，接着考虑一块木板 $s_i,e_i$ 对 $L_j$ 的影响是使得 $s_i \leq j \leq e_i$ 的 $L_j \gets \min(L_j,s_i)$，这部分可以用线段树维护，然后我们将 dp 状态的第一维放到主席树上，每次令 $dp_j(i)$ 先复制为 $dp_{L_j}(i)$，然后运用全局标记处理 $+1$ 操作，最后再令 $dp_{j}(j)$ 为 $0$ 即可完成转移，最后查询 $\min_{0 \leq i \leq j-m}(dp_{i,j})$ 即可。

时间复杂度与空间复杂度均为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 6e5+114;
int tr[maxn*22],ls[maxn*22],rs[maxn*22];
int rt[maxn],n,m,tot;
int T[maxn<<2];
void cover(int cur,int lt,int rt,int l,int r,int c){
    if(rt<l||r<lt) return ;
    if(l<=lt&&rt<=r){
        T[cur]=min(T[cur],c);
        return ;
    }
    int mid=(lt+rt)>>1;
    cover(cur<<1,lt,mid,l,r,c);
    cover(cur<<1|1,mid+1,rt,l,r,c);
}
int ask(int cur,int lt,int rt,int p){
    if(lt==rt) return T[cur];
    int mid=(lt+rt)>>1;
    if(p<=mid) return min(T[cur],ask(cur<<1,lt,mid,p));
    else return min(T[cur],ask(cur<<1|1,mid+1,rt,p));
}
int Add[maxn];
void ins(int &cur,int lst,int lt,int rt,int p,int v){
    cur=++tot;
    tr[cur]=tr[lst];
    if(lt==rt){
        tr[cur]=v;
        return ;
    }
    int mid=(lt+rt)>>1;
    if(p<=mid){
        rs[cur]=rs[lst];
        ins(ls[cur],ls[lst],lt,mid,p,v);
    }else{
        ls[cur]=ls[lst];
        ins(rs[cur],rs[lst],mid+1,rt,p,v);
    }
    tr[cur]=min(tr[ls[cur]],tr[rs[cur]]);
}
int ans=1e9+7;
int query(int cur,int lt,int rt,int l,int r){
    if(cur==0) return maxn;
    if(rt<l||r<lt) return 0x3f3f3f;
    if(l<=lt&&rt<=r) return tr[cur];
    int mid=(lt+rt)>>1;
    return min(query(ls[cur],lt,mid,l,r),query(rs[cur],mid+1,rt,l,r));
}
set<int> S;
map<int,int> lsh;
int rk[maxn];
int s[maxn],e[maxn];
int t;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    memset(T,0x3f3f3f,sizeof(T));
    memset(tr,0x3f3f3f,sizeof(tr));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s[i]>>e[i];
        if(s[i]>e[i]) e[i]+=m;
        S.insert(s[i]);
        S.insert(e[i]);
        if(e[i]>m) S.insert(e[i]-m);
    }
    for(int x:S) lsh[x]=lsh.size()+1,rk[lsh[x]]=x,t=lsh[x];
    for(int i=1;i<=n;i++){
        s[i]=lsh[s[i]];
        e[i]=lsh[e[i]];
        cover(1,1,t,s[i],e[i],s[i]);
    }
    for(int i=1;i<=t;i++){
        int lt=ask(1,1,t,i);
        if(lt>=i){
            ins(rt[i],rt[0],0,t,i,0);
            continue;
        }
        Add[i]=Add[lt]+1;
        ins(rt[i],rt[lt],0,t,i,-Add[i]);
    }
    for(int i=1;i<=t;i++){
        if(rk[i]<m) continue;
        ans=min(ans,query(rt[i],0,t,0,lsh[rk[i]-m])+Add[i]);
    }
    cout<<(ans<=n?ans:-1)<<'\n';
    return 0;
}

```

---

