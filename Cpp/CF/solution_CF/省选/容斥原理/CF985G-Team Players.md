# Team Players

## 题目描述

### 题目大意

有 $n$ 个点和 $m$ 条边，点编号依次为 $0,1,\cdots, n-1$。

如果一个点的三元组 $(i,j,k)~(i<j<k)$ 两两**没有边**相连，那么它的贡献为 $A\times i+B\times j+C\times k$。

求出所有三元组的贡献和，答案对 $2^{64}$ 取模。

## 样例 #1

### 输入

```
4 0
2 3 4
```

### 输出

```
64
```

## 样例 #2

### 输入

```
4 1
2 3 4
1 0
```

### 输出

```
38
```

## 样例 #3

### 输入

```
6 4
1 5 3
0 3
3 5
5 4
4 3
```

### 输出

```
164
```

# 题解

## 作者：Hanx16Kira (赞：12)

# CF985G Team Players

[Luogu CF985G](https://www.luogu.com.cn/problem/CF985G)

## Solution

两两不连边不好计算，考虑容斥，分为所有三元组、至少有一条边相连的、至少有两条边相连的、至少有三条边相连的。

第四种很好计算，直接套三元环计数板子即可，考虑剩余的如何计算。

由于笔者习惯，以下所有节点编号改为 $[1,n]$，因此在计算对答案的贡献的时候会 $-1$。

- 所有三元组 $(x,y,z)$：

  枚举 $i\in[1,n]$，分讨 $i$ 在三元组中的位置：

  - $x=i$：此时 $y,z$ 只需要满足大于 $x$，因此对答案贡献 $A\cdot\dfrac{(n-i)(n-i-1)}2\cdot (i-1)$；
  - $y=i$：此时 $x\in[1,y)$，$z\in(y,n]$，因此对答案贡献 $B\cdot (i-1)(n-i)(i-1)$；
  - $z=i$：此时 $x,y$ 只需要满足小于 $z$，因此对答案贡献 $C\cdot\dfrac{(i-1)(i-2)}2\cdot(i-1)$。

- 至少有一条边相连：

  枚举所有边 $u\leftrightarrow v$，不妨设 $u<v$，考虑分讨第三个元素 $t$ 与 $u,v$ 的大小关系：

  - $x=u$：此时只需要 $t>x$，因此对答案贡献为 $A\cdot(u-1)(n-u-1)$；
  - $y=u$：此时只需要 $t<x$，因此对答案贡献为 $B\cdot(u-1)(u-1)$；
  - $y=v$：此时只需要 $t>y$，因此对答案贡献为 $B\cdot(v-1)(n-v)$；
  - $z=v$：此时只需要 $t<y$，因此对答案贡献为 $C\cdot(v-1)(v-2)$；
  - $x=t$：此时 $t\in[1,u)$，利用等差数列求和公式得到贡献为 $A\cdot \dfrac{(u-1)(u-2)}2$；
  - $y=t$：此时 $t\in(u,v)$，同理得到贡献为 $B\cdot\dfrac{(u+v-2)(v-u-1)}2$；
  - $z=t$：此时 $t\in(v,n]$，贡献为 $C\cdot\dfrac{(n+v-1)(n-v)}2$。

- 至少有两条边相连：

  考虑枚举每个点的出边，先将出边按照到达节点的编号排序。设当前枚举的节点是 $u$，到达的节点为 $v$，在 $u$ 的所有可到达节点中排名第 $i$，$u$ 所有可到达的节点个数为 $tn$。分讨一下 $u,v$ 的大小关系，设第三个元素的编号为 $t$。

  - $v<u$：
    - 若 $t<v$，则 $v$ 对答案贡献 $A\cdot (v-1)(tn-i-1)$；
    - 若 $t>v$，则 $v$ 对答案贡献 $B\cdot(v-1)(i-1)$。

  - $v > u$：
    - 若 $t<v$，则 $v$ 对答案贡献 $C\cdot(v-1)(i-2)$；
    - 若 $t>v$，则 $v$ 对答案贡献 $B\cdot(v-1)(tn-i)$。

  对于 $u$ 对答案的贡献，也进行分讨：

  - $x=u$：此时为 $t,v>u$，贡献为 $A\cdot\dfrac{(tn-i)(tn-i-1)}2\cdot(u-1)$；
  - $y=u$：此时 $t,v$ 分居 $u$ 两侧，贡献为 $B\cdot(tn-i)(i-1)\cdot(u-1)$；
  - $z=u$：此时 $t,v<u$，贡献为 $C\cdot\dfrac{(i-1)(i-2)}2\cdot(u-1)$。

分讨完了过后将所有情况乘上容斥系数加起来即是答案。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ui64 = unsigned long long;

int n, m;
ui64 A, B, C;
ui64 ans = 0;
constexpr int _N = 2e5 + 5;
vector<int> oe[_N], ne[_N];
int deg[_N], fr[_N], to[_N];

ui64 GetAns1() {
	ui64 sum = 0;
	
	for (int X = 1; X <= n; ++X)
		for (int Y : ne[X]) {
			int x = min(X, Y), y = max(X, Y);
			sum += A * (x - 1) * (n - x - 1);
			sum += B * (x - 1) * (x - 1);
			sum += B * (y - 1) * (n - y);
			sum += C * (y - 1) * (y - 2);
			sum += A * (x - 1) * (x - 2) / 2;
			sum += B * (y + x - 2) * (y - x - 1) / 2;
			sum += C * (n + y - 1) * (n - y) / 2;
		}
	
	return sum;
}

ui64 GetAns2() {
	ui64 sum = 0;
	
	for (int X = 1; X <= n; ++X) {
		oe[X].emplace_back(X);
		sort(oe[X].begin(), oe[X].end());
		int tn = oe[X].size() - 1;
		
		for (int i = 0; i <= tn; ++i) {
			int Y = oe[X][i];
			
			if (Y != X) {
				if (Y < X) {
					sum += A * (Y - 1) * (tn - i - 1);
					sum += B * (Y - 1) * i;
				} else {
					sum += B * (Y - 1) * (tn - i);
					sum += C * (Y - 1) * (i - 1);
				}
			} else {
				sum += A * (tn - i) * (tn - i - 1) / 2 * (X - 1);
				sum += B * i * (tn - i) * (X - 1);
				sum += C * i * (i - 1) / 2 * (X - 1);
			}
		}
	}
	
	return sum;
}

int vis[_N];

ui64 GetAns3() {
	ui64 sum = 0;
	
	for (int X = 1; X <= n; ++X) {
		for (int Y : ne[X]) vis[Y] = X;
		
		for (int Y : ne[X]) for (int Z : ne[Y]) {
			if (vis[Z] != X) continue;
			
			int t[] = {X, Y, Z};
			sort(t, t + 3);
			sum += (t[0] - 1) * A + (t[1] - 1) * B + (t[2] - 1) * C;
		}
	}
	
	return sum;
}

ui64 GetAll() {
	ui64 sum = 0;
	
	for (int i = 1; i <= n; ++i) {
		sum += A * (n - i) * (n - i - 1) / 2 * (i - 1);
		sum += B * (i - 1) * (n - i) * (i - 1);
		sum += C * (i - 1) * (i - 2) / 2 * (i - 1);
	}
	
	return sum;
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m >> A >> B >> C;
	
	for (int i = 1; i <= m; ++i) {
		cin >> fr[i] >> to[i]; ++fr[i], ++to[i];
		oe[fr[i]].emplace_back(to[i]);
		oe[to[i]].emplace_back(fr[i]);
		++deg[fr[i]], ++deg[to[i]];
	}
	
	for (int i = 1; i <= m; ++i) {
		int x = fr[i], y = to[i];
		
		if (deg[x] > deg[y] || (deg[x] == deg[y] && x > y)) swap(x, y);
		
		ne[x].emplace_back(y);
	}
	
	ui64 all = 0, sum = 0;
	all = GetAll();
	sum = GetAns1() - GetAns2() + GetAns3();
	cout << all - sum << '\n';
}
```



---

## 作者：chenxia25 (赞：6)

这题的计数部分还是挺有趣的，虽然涉及到的知识以及思维难度并不难。

---

映入脑帘的是建补图然后三元环计数。但那样边数没有保证。

正难则反，我们考虑先求所有三元组的贡献和，然后减去至少有一条边的。u1s1 普通的正难则反不容易想到，但这题是要求反，实际上是个「反难则正」，这应该很容易想到吧（

总贡献的话，把加法拆开，算每个点的贡献即可。就加一加它作为最小、次小、最大的贡献，容易算出。

然后是至少有一条边的三元组。那就分成一条边、两条边、三条边来算。

一条边：似乎不是很好算。考虑这样一个过程：对每条边，算出所有其他点与这两个点的贡献和，最后加起来。这样得到的既不是恰好一条边的，也不是至少一条边的，而是一条边的算了一次，两条边的算了两次，三条边的算了三次。那么我们如果知道了两条边、三条边的答案，一条边也就出来了，而本来也要求这两个，难度没变化。于是不妨就这样搞。而这个非常容易算，还是枚举这两个点的排名，想必来做这题的人都不用听了。

两条边：似乎也不是很好算。考虑统计每条三元链的贡献和，这样得出来的是两条边一遍，三条边（三元环）三遍。那么如果求出这个和三元环的答案，两条边也自然就出了。而三元环是本来就需要算的，难度并没有增加。于是不妨就这样算。那么这玩意怎么算呢，考虑对一个特定的点的有序邻居序列做事情，显然可以分成左右两部分，分别小于和大于该点编号。那么考虑一个类似分治的东西，算左边的内部的、右边内部的、一左一右~~（像 \* 的 \*\*\*）~~的，都好算（

三元环就直接套板子吧。

总结一下，对一条边和两条边这两个难算的东西，我们并没有硬刚，而是通过类似正难则反的「总值减去好算的剩下值」的方式算，包括开头的反难则正也是这个道理，容斥大概也有这味。计数 / 贡献统计类题目做法的本质其实就是不断地把难算的转化为容易算的。

---

## 作者：vectorwyx (赞：4)

简单容斥，感觉评分虚高。

第一想法是建反图后直接数三元环，但是边数炸了。

正难则反，考虑容斥，由于是三个点，所以只有四种情况：三个点的子图无边相连；有一条边；有两条边；有三条边。

第一种情况为所求，第四种可以直接拉三元环计数板子。

第二种情况只需要枚举这条边 $(x,y)$，然后对第三个点位于 $[0,x),(x,y),(y,n)$ 中的哪个区间进行分类讨论。

第三种情况稍稍麻烦一点，但和第二种思想一致。由于这两条边一定有一个共同的顶点，所以我们只需要枚举该顶点 $x$，对 $x$ 的所有出边排序后，枚举 $x$ 的一条出边，仿照第二种情况的分类讨论做就行。总时间复杂度 $O(m\sqrt m)$。

代码如下：

```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e5+5;
int n,m,deg[N],vis[N],ti;
ull a,b,c;
pii ed[N];
vector<int> e[N],g[N];

ull calc1(){
	ull sum=0;
	fo(i,1,n)
		for(int j:e[i]){
			int x=min(i,j),y=max(i,j);
			sum+=a*(n-x-1)*(x-1);
			sum+=b*(x-1)*(x-1);
			sum+=b*(n-y)*(y-1);
			sum+=c*(y-2)*(y-1);
			sum+=a*(x-2)*(x-1)/2;
			sum+=b*(x+y-2)*(y-x-1)/2;
			sum+=c*(y+n-1)*(n-y)/2; 
		}
	return sum;
}

ull calc2(){
	ull sum=0;
	fo(i,1,n){
		g[i].pb(i);
		sort(g[i].begin(),g[i].end());
		int siz=g[i].size();
		fo(j,0,siz-1){
			int x=g[i][j];
	 		if(x!=i){
				if(x<i){
					sum+=a*(siz-j-2)*(x-1);
					sum+=b*j*(x-1);
				}else{
					sum+=b*(siz-j-1)*(x-1);
					sum+=c*(j-1)*(x-1);
				}
			}else{
				sum+=c*j*(j-1)/2*(x-1);
				sum+=b*j*(siz-j-1)*(x-1);
				sum+=a*(siz-j-1)*(siz-j-2)/2*(x-1);
			}		
		}
	} 
	return sum;
}

ull calc3(){
	ull sum=0;
	fo(i,1,n){
		++ti;
		for(int j:e[i]) vis[j]=ti;
		for(int j:e[i]) for(int k:e[j])if(vis[k]==ti){
			if(i<j){
				if(j<k) sum+=a*i+b*j+c*k;
				else if(i<k) sum+=a*i+b*k+c*j;
				else sum+=a*k+b*i+c*j;
			}else{
				if(j>k) sum+=a*k+b*j+c*i;
				else if(i>k) sum+=a*j+b*k+c*i;
				else sum+=a*j+b*i+c*k; 
			}sum-=a+b+c;
		}
	}
	return sum;
}

signed main(){
	cin>>n>>m>>a>>b>>c;
	fo(i,1,m){
		int x=read()+1,y=read()+1;
		g[x].pb(y),g[y].pb(x);
		ed[i]=mk(x,y);
		deg[x]++,deg[y]++;
	}
	fo(i,1,m){
		int x=ed[i].fi,y=ed[i].se;
		if(deg[x]>deg[y]||(deg[x]==deg[y]&&x>y)) swap(x,y);
		e[x].pb(y);
	}
	ull sum=calc1();
	sum-=calc2();//不要忘了乘容斥系数
	sum+=calc3();
	ull all=0;
	fo(i,1,n){
		all+=a*(n-i)*(n-i-1)/2*(i-1);
		all+=b*(i-1)*(n-i)*(i-1);
		all+=c*(i-1)*(i-2)/2*(i-1);
	}
	cout<<all-sum;
	return 0;
}
```



---

## 作者：roger_yrj (赞：3)

本文着重讲解三元环计数问题。

## 三元环计数

### 题意

给你 $n$ 个点 $m$ 条边的无向图，求三元环的个数。$m\le 2\times10^5$。

### 题解

先考虑暴力。

枚举三元环中的其中一个点 $u$，再枚举 $u$ 邻域中的一个点 $v$，再枚举 $v$ 邻域中的一个点 $w$，判断 $w$ 是否在 $u$ 的邻域中。

枚举 $u$ 和 $v$ 实际上就是枚举了图中的边，所以暴力的时间复杂度是 $O(m^2)$ 的。

我们考虑给无向边定向，把无向图变成 DAG。

我们按照度数把点排序，度数小的连向度数大的。为了使图为 DAG，**当度数相同时，编号小的连向编号大的**，不然可能连出环。

我们发现按度数连边，每个点的**出度**不会很大。

- 当点的度数 $\le \sqrt m$ 时，出度也 $\le \sqrt m$。
- 当点的度数 $> \sqrt m$ 时，假设出度 $> \sqrt m$，那么就有至少 $\sqrt m$ 个点的度数  $> \sqrt m$，显然矛盾。

所以每个点的出度都 $\le \sqrt m$。

接下来我们只需要去统计形如 $u\to v,v\to w,u\to w$ 的三元环，枚举 $w$ 的这一步就优化成了 $O(\sqrt m)$。

总时间复杂度为 $O(m\sqrt m)$。

### 例题 CF985G Team Players

#### 题意

给你 $n$ 个点 $m$ 条边的无向图。

如果一个点的三元组 $(i,j,k)~(i<j<k)$ 两两无边，那么它的贡献为 $A\times i+B\times j+C\times k$。

求出所有三元组的贡献和。

#### 题解

题解中点的编号从 $1$ 开始。

直接做边太多了，考虑容斥。分四种情况考虑。

1. 边数 $\ge0$。
   - 直接暴力数三元组即可。
   - 贡献为 $\sum\limits_{i=1}^ni\times A\times \dbinom{n-i}{2}+\sum\limits_{i=1}^ni\times B\times (i-1)\times(n-i)+\sum\limits_{i=1}^ni\times C\times \dbinom{i-1}{2}$
   - 时间复杂度 $O(n)$。
2. 边数 $\ge 1$。
   - 枚举这条边 $(u,v)$，钦定 $u<v$，考虑第三个点 $w$ 的位置。
   - $w<u$ 时，贡献为 $\sum\limits_{w=1}^{u-1}w\times A+u\times B+v\times C=(u-1)\times (u\times B+v\times C)+\cfrac{u\times(u-1)}{2}\times A$
   - $u<w<v$ 时，贡献为 $\sum\limits_{w=u+1}^{v-1}u\times A+w\times B+v\times C=(u-v-1)\times (u\times A+v\times C)+\cfrac{(u+v)\times(u-v-1)}{2}\times B$
   - $v<w$ 时，贡献为 $\sum\limits_{w=v+1}^{n}u\times A+v\times B+w\times C=(n-v)\times (u\times A+v\times B)+\cfrac{(v+1+n)\times(n-v)}{2}\times C$
   - 时间复杂度 $O(m)$。
3. 边数 $\ge 2$。
   - 枚举两条边的交点 $u$，枚举 $u$ 邻域中的点 $v$，考虑第三个点 $w$ 的位置。钦定 $w<v$。
   - 设 $rk$ 为邻域中编号小于 $u$ 的点的数量，$i$ 为 $v$ 在邻域中的排名，$cntr=\sum\limits_{i\in N(u),i\le rk}i$，$cntv=\sum\limits_{i\in N(u),i<v}i$。
   - 当 $w\le v\le u$ 时，贡献为 $\sum\limits_{w\in N(u),w<v}w\times A+v\times B+u\times C=(i-1)\times(v\times B+u\times C)+cntv*A$
   - 当 $w\le u\le v$ 时，贡献为 $\sum\limits_{w\in N(u),w<u}w\times A+u\times B+v\times C=rk\times(u\times B+v\times C)+cntr*A$
   - 当 $u\le w\le v$ 时，贡献为 $\sum\limits_{w\in N(u),u<w<v}u\times A+w\times B+v\times C=(v-rk-1)\times(u\times A+v\times C)+(cntv-cntr)*B$
   - 时间复杂度 $O(m)$。
4. 边数 $\ge 3$。
   - 其实就是三元环计数。时间复杂度 $O(m\sqrt m)$。

简单容斥可得 $ANS=Cnt_0-Cnt_1+Cnt_2-Cnt_3$。

#### 代码

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int N=2e5+10;
int n,m,d[N],vis[N];
ll C0,C1,C2,C3,A,B,C;
int fst[N<<1],to[N<<1],nxt[N<<1],ecnt;
void adde(int u,int v){
	ecnt++;
	to[ecnt]=v;
	nxt[ecnt]=fst[u];
	fst[u]=ecnt;
}
struct edge{int u,v;}E[N];
vector<int>e[N];
int main(){
	cin>>n>>m>>A>>B>>C;
	for(int i=1;i<=n;i++){//0
		C0+=(ll)(n-i)*(n-i-1)/2*A*(i-1);
		C0+=(ll)(i-1)*(n-i)*B*(i-1);
		C0+=(ll)(i-1)*(i-2)/2*C*(i-1);
	}
	for(int i=1;i<=n;i++)e[i].push_back(0);
	for(int i=1,u,v;i<=m;i++){//1
		cin>>u>>v;u++,v++;
		d[u]++,d[v]++;
		E[i]=(edge){u,v};
		e[u].push_back(v);
		e[v].push_back(u);
		if(u>v)swap(u,v);
		C1+=(u-1)*((u-1)*B+(v-1)*C)+(ll)(u-2)*(u-1)/2*A;
		C1+=(v-u-1)*((u-1)*A+(v-1)*C)+(ll)(v+u-2)*(v-u-1)/2*B;
		C1+=(n-v)*((u-1)*A+(v-1)*B)+(ll)(v+n-1)*(n-v)/2*C;
	}
	for(int i=1;i<=n;i++)sort(e[i].begin(),e[i].end());
	for(int u=1;u<=n;u++){//2
		ll rk=0,cntr=0,cnt=0;
		for(int i=1;i<=d[u];i++){
			if(e[u][i]<u)rk=i,cntr+=e[u][i]-1;
			else break;
		}
		for(int i=1;i<=d[u];i++){
			int v=e[u][i];
			if(v<u)C2+=(i-1)*((u-1)*C+(v-1)*B)+cnt*A;
			else{
				C2+=(i-rk-1)*((u-1)*A+(v-1)*C)+(cnt-cntr)*B;
				C2+=rk*((u-1)*B+(v-1)*C)+cntr*A;
			}
			cnt+=v-1;
		}
	}
	for(int i=1;i<=m;i++){
		if(d[E[i].u]<d[E[i].v]||(d[E[i].u]==d[E[i].v]&&E[i].u<E[i].v))adde(E[i].u,E[i].v);//注意这一行 
		else adde(E[i].v,E[i].u);
	}
	for(int u=1;u<=n;u++){//3
		for(int i=fst[u];i;i=nxt[i])vis[to[i]]=1;
		for(int i=fst[u];i;i=nxt[i]){
			int v=to[i];
			for(int j=fst[v];j;j=nxt[j]){
				int w=to[j];
				if(vis[w])C3+=(min({u,v,w})-1)*A+(u+v+w-min({u,v,w})-max({u,v,w})-1)*B+(max({u,v,w})-1)*C;
			}
		}
		for(int i=fst[u];i;i=nxt[i])vis[to[i]]=0;
	}
	cout<<C0-C1+C2-C3;
}
```

---

## 作者：_szh_ (赞：3)

## CF985G
### 题意

给出一个无向图，如果点$\ i,j,k$，满足$i<j<k$，并且**两两之间没有边**相连，给定$\ A,B,C$，计算所有$\ A⋅i+B⋅j+C⋅k$之和

$n,m<=2e5$ $\ \ A,B,C<=1e6$

---
（这篇题解方法比较繁复但是很好懂。）

### 做法
我们按照边的数量将所有三元组分为四类

设$\ A1,A2,A3,A4\ $为各自答案

我们要求的就是$A1$了。

直接算肯定是不行的，我们需要大力容斥。

#### 第一步

计算所有三元组的答案 

即 $S1=\sum_{i=0}^{n-1}\sum_{j=i+1}^{n-1}\sum_{k=j+1}^{n-1}Ai+Bj+Ck$

这一步比较简单，把求和号一个个拆开记录后缀和即可。


复杂度$\ O(n)$


```cpp
inline void Calc1()
{
	for(int i=n-1;i>=0;i--)s1[i]=s1[i+1]+C*i;
	for(int i=n-2;i>=0;i--)s2[i]=s2[i+1]+s1[i+1]+B*i*(n-i-1),num[i]=num[i+1]+n-i-1;
	for(int i=n-3;i>=0;i--)S1+=s2[i+1]+A*i*num[i+1];
}
```
显然$\ S1=A1+A2+A3+A4$

#### 第二步

枚举每一条边，任意选取第三个点，计算答案。

这一步需要搞清楚计算的东西。

$[0,u-1],[u+1,v-1],[v+1,n-1]\ $三部分答案的计算方式是不同的

复杂度$\ O(m)$

```cpp
inline void Calc2()
{
	for(int i=1;i<=m;i++)
	{	
		if(u[i]>v[i])swap(u[i],v[i]);
		S2+=u[i]*(u[i]-1)/2*A;
		S2+=(v[i]-u[i]-1)*(u[i]+v[i])/2*B;
		S2+=(v[i]+n)*(n-v[i]-1)/2*C;
		S2+=u[i]*(B*u[i]+A*(n-u[i]-2));
		S2+=v[i]*(C*(v[i]-1)+B*(n-v[i]-1));
	}	
}
```
这里比起上面略有不同，会发现被记进的次数和组内边数有关，所以

$S2=A2+2*A3+3*A4$

#### 第三步

依旧枚举每一条边，分别计算与左右两端点相连的点的答案。

贴个图。计算的答案即为图中红色和蓝色部分

![](https://cdn.luogu.com.cn/upload/image_hosting/t7pkm426.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


这里的计算方式就比较麻烦了。

可以使用$\ vector\ $或者动态开点线段树来维护与每个点相连的点集及区间和。

复杂度$\ O(m\log_2n)$

这边使用的是动态开点线段树。
```cpp
inline void Update(int &x,int l,int r,int p)
{
	if(!x)x=++cnt;sum1[x]+=p;sum2[x]+=1;
	if(l==r)return ;
	int mid=l+r>>1;
	if(p<=mid)Update(ls[x],l,mid,p);
	else Update(rs[x],mid+1,r,p);
}
inline ll Query1(int x,int l,int r,int L,int R)
{
	if(!x || L>R)return 0;
	if(l>=L && r<=R)return sum1[x];
	int mid=l+r>>1;
	ll ans=0;
	if(L<=mid)ans+=Query1(ls[x],l,mid,L,R);
	if(R>mid)ans+=Query1(rs[x],mid+1,r,L,R);
	return ans;
}
inline ll Query2(int x,int l,int r,int L,int R)
{
	if(!x || L>R)return 0;
	if(l>=L && r<=R)return sum2[x];
	int mid=l+r>>1;
	ll ans=0;
	if(L<=mid)ans+=Query2(ls[x],l,mid,L,R);
	if(R>mid)ans+=Query2(rs[x],mid+1,r,L,R);
	return ans;
}
inline ll Q1(int x,int y,int l,int r){return Query1(rt[x],0,n-1,l,r)+Query1(rt[y],0,n-1,l,r);}
inline ll Q2(int x,int y,int l,int r){return Query2(rt[x],0,n-1,l,r)+Query2(rt[y],0,n-1,l,r);}
inline void Calc3()
{
	for(int i=1;i<=m;i++)Update(rt[u[i]],0,n-1,v[i]),Update(rt[v[i]],0,n-1,u[i]);
	for(int i=1;i<=m;i++)
	{
		if(u[i]>v[i])swap(u[i],v[i]);
		S3+=A*Q1(u[i],v[i],0,u[i]-1);
		S3+=B*Q1(u[i],v[i],u[i]+1,v[i]-1);
		S3+=C*Q1(u[i],v[i],v[i]+1,n-1);
		S3+=u[i]*(B*Q2(u[i],v[i],0,u[i]-1)+A*Q2(u[i],v[i],u[i]+1,n-1)-A);
		S3+=v[i]*(C*Q2(u[i],v[i],0,v[i]-1)+B*Q2(u[i],v[i],v[i]+1,n-1)-C);
	}
}
```
对于第三类来说，每条边都使其被计算一次。

对于第四类（三元环），每条边都使其被计算两次

$S3=2*A3+6*A4$

#### 第四步

最开心的一步，拉个三元环板子。

这步就没什么好说的了，不会三元环的可以去学一下。

复杂度$\ O(m\sqrt{m})$

```cpp
inline void Calc4()
{
	for(int i=1;i<=m;i++)deg[u[i]]++,deg[v[i]]++;
	for(int i=1;i<=m;i++)
	{	
		int s=u[i],t=v[i];
		if(deg[s]>deg[t] || (deg[s]==deg[t] && s>t))swap(u[i],v[i]);
		G[u[i]].push_back(v[i]);
	}
	for(int k=1;k<=m;k++)
	{
		for(int i=0;i<G[u[k]].size();i++)vis[G[u[k]][i]]=k;
		for(int i=0;i<G[v[k]].size();i++)if(vis[G[v[k]][i]]==k)S4+=Calc((ll)u[k],(ll)v[k],(ll)G[v[k]][i]);
	}
}
```
这一步很显然，$S4=A4$

### 第五步

最后一步，我们已经计算出了四种答案，分别是：

$S1=A1+A2+A3+A4$

$S2=A2+2*A3+3*A4$

$S3=2*A3+6*A4$

$S4=A4$

肉眼观察一下就可以得到，$A1=S1-S2+S3/2-S4$

完结撒花！

---
### 后记

其实还没完，还有一些细节没讲。

这道题对$\ 2^{64}\ $取模，开$ull$即可。

由于最后输出答案的时候涉及除法，2在这里又没有逆元，所以还得做处理。

设$S3=2^{64}q+r$，求$\lfloor \frac{2^{64}q+r}{2}\rfloor \% \ 2^{64}$

可以得到答案为$\ (2^{63}q+\lfloor \frac{r}{2}\rfloor) \% \ 2^{64}$

发现后面那个$\ \lfloor \frac{r}{2}\rfloor\ $就是现在代码里的，那个$\ p\ $也就是$\ S3\ $加上一个数反而变小的次数（代码中$S5$）。

修改后的代码

```cpp
inline void Calc3()
{
	ll pre;
	for(int i=1;i<=m;i++)Update(rt[u[i]],0,n-1,v[i]),Update(rt[v[i]],0,n-1,u[i]);
	for(int i=1;i<=m;i++)
	{
		pre=S3;
		//中间一样
		if(pre>S3)S5++;
	}
}
```

___

### 真 · 代码
```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#define N 200010
#define ll unsigned long long
using namespace std;
inline int read()
{
	int neg=1,num=0;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')neg=-1;
	for(;isdigit(c);c=getchar())num=(num<<1)+(num<<3)+c-'0';
	return neg*num;
}
int n,m,cnt,deg[N],vis[N],rt[N],ls[N*50],rs[N*50];
ll A,B,C,S1,S2,S3,S4,S5,u[N],v[N],s1[N],s2[N],num[N],sum1[N*50],sum2[N*50];
vector<int> G[N];
inline ll Calc(ll x,ll y,ll z)
{
	if(x>y)swap(x,y);
	if(y>z)swap(y,z);
	if(x>y)swap(x,y);
	return A*x+B*y+C*z; 
}
inline void Calc1()
{
	for(int i=n-1;i>=0;i--)s1[i]=s1[i+1]+C*i;
	for(int i=n-2;i>=0;i--)s2[i]=s2[i+1]+s1[i+1]+B*i*(n-i-1),num[i]=num[i+1]+n-i-1;
	for(int i=n-3;i>=0;i--)S1+=s2[i+1]+A*i*num[i+1];
}
inline void Calc2()
{
	for(int i=1;i<=m;i++)
	{	
		if(u[i]>v[i])swap(u[i],v[i]);
		S2+=u[i]*(u[i]-1)/2*A;
		S2+=(v[i]-u[i]-1)*(u[i]+v[i])/2*B;
		S2+=(v[i]+n)*(n-v[i]-1)/2*C;
		S2+=u[i]*(B*u[i]+A*(n-u[i]-2));
		S2+=v[i]*(C*(v[i]-1)+B*(n-v[i]-1));
	}	
}
inline void Update(int &x,int l,int r,int p)
{
	if(!x)x=++cnt;sum1[x]+=p;sum2[x]+=1;
	if(l==r)return ;
	int mid=l+r>>1;
	if(p<=mid)Update(ls[x],l,mid,p);
	else Update(rs[x],mid+1,r,p);
}
inline ll Query1(int x,int l,int r,int L,int R)
{
	if(!x || L>R)return 0;
	if(l>=L && r<=R)return sum1[x];
	int mid=l+r>>1;
	ll ans=0;
	if(L<=mid)ans+=Query1(ls[x],l,mid,L,R);
	if(R>mid)ans+=Query1(rs[x],mid+1,r,L,R);
	return ans;
}
inline ll Query2(int x,int l,int r,int L,int R)
{
	if(!x || L>R)return 0;
	if(l>=L && r<=R)return sum2[x];
	int mid=l+r>>1;
	ll ans=0;
	if(L<=mid)ans+=Query2(ls[x],l,mid,L,R);
	if(R>mid)ans+=Query2(rs[x],mid+1,r,L,R);
	return ans;
}
inline ll Q1(int x,int y,int l,int r){return Query1(rt[x],0,n-1,l,r)+Query1(rt[y],0,n-1,l,r);}
inline ll Q2(int x,int y,int l,int r){return Query2(rt[x],0,n-1,l,r)+Query2(rt[y],0,n-1,l,r);}
inline void Calc3()
{
	ll pre;
	for(int i=1;i<=m;i++)Update(rt[u[i]],0,n-1,v[i]),Update(rt[v[i]],0,n-1,u[i]);
	for(int i=1;i<=m;i++)
	{
		pre=S3;
		if(u[i]>v[i])swap(u[i],v[i]);
		S3+=A*Q1(u[i],v[i],0,u[i]-1);
		S3+=B*Q1(u[i],v[i],u[i]+1,v[i]-1);
		S3+=C*Q1(u[i],v[i],v[i]+1,n-1);
		S3+=u[i]*(B*Q2(u[i],v[i],0,u[i]-1)+A*Q2(u[i],v[i],u[i]+1,n-1)-A);
		S3+=v[i]*(C*Q2(u[i],v[i],0,v[i]-1)+B*Q2(u[i],v[i],v[i]+1,n-1)-C);
		if(pre>S3)S5++;
	}
}
inline void Calc4()
{
	for(int i=1;i<=m;i++)deg[u[i]]++,deg[v[i]]++;
	for(int i=1;i<=m;i++)
	{	
		int s=u[i],t=v[i];
		if(deg[s]>deg[t] || (deg[s]==deg[t] && s>t))swap(u[i],v[i]);
		G[u[i]].push_back(v[i]);
	}
	for(int k=1;k<=m;k++)
	{
		for(int i=0;i<G[u[k]].size();i++)vis[G[u[k]][i]]=k;
		for(int i=0;i<G[v[k]].size();i++)if(vis[G[v[k]][i]]==k)S4+=Calc((ll)u[k],(ll)v[k],(ll)G[v[k]][i]);
	}
}
signed main()
{
	n=read();m=read();A=read();B=read();C=read();
	for(int i=1;i<=m;i++)u[i]=read(),v[i]=read();
	Calc1();Calc2();Calc3();Calc4(); 
	for(int i=1;i<=63;i++)S5=S5*2;
	cout<<S1-S2+(S3/2+S5)-S4<<endl;	
	return 0;
}
```





---

## 作者：james1BadCreeper (赞：2)

一眼看去在补图上跑三元环计数，然后发现边数爆炸，直接告辞。

但是唯一会的好像就是数三元环。考虑求答案的补集，答案应该是所有三元组的答案，减去至少有一条边的三元组的答案。

然后后面这个怎么做呢？我们肯定是要去看边的，这样就会导致对于一个有两条边的三元组，被统计两次。因此后面这个也需要容斥。

最终答案就是所有三元组的答案（1），减去至少有一条边的答案（2），加上至少有两条边的答案（3），减去有三条边的答案（4）。接下来分别看这四个东西怎么做。

1. 枚举 $u\in [0,n)$ 中在三元组 $(i,j,k)$ 的位置，然后利用乘法原理计算答案。

2. 只有一条边，那么枚举所有边 $(x,y)$，不妨令 $x<y$，然后令第三个点为 $z$，考虑 $x,y,z$ 对三元组 $(i,j,k)$ 的贡献。

   - $x=i$，此时 $z>x$，$x$ 的贡献为 $A\times x\times (n-x-2)$；
   - $x=j$，此时 $z<x$，$x$ 的贡献为 $B\times x\times x$；
   - $y=j$，此时 $z>y$，$y$ 的贡献为 $B\times y\times (n-y-1)$；
   - $y=k$，此时 $z<y$，$y$ 的贡献为 $C\times y\times (y-1)$；
   - $z=i$，此时 $0\le z<x$，$z$ 的贡献为 $\displaystyle A\times \sum_{p=0}^{x-1}p=A\times \frac {x\times (x-1)} 2$；
   - $z=j$，此时 $x<z<y$，$z$ 的贡献为 $\displaystyle B\times \sum_{p=x+1}^{y-1}p=B\times\frac{(x+y) \times (y-x-1)} 2$；
   - $z=k$，此时 $y<z<n$，$z$ 的贡献为 $\displaystyle C\times \sum_{p=y+1}^{n-1}p=C\times \frac{(n+y)\times (n-y-1)} 2$。

3. 两条边，要求的是三个点的链。不妨考虑枚举的是中间点 $x$，此时 $x=j$。枚举 $x$ 的每一条出边到达点 $y$，设 $x$ 的出度为 $t$。由于 $x$ 也会影响 $y$ 充当的是 $i,j$ 还是 $k$，因此不妨把 $x$ 也加进 $x$ 的出边中（$t$ 同时也增大 $1$）。设 $y$ 在这些数中的排名为 $r$，分两种情况计算 $y$ 的贡献：

   - $y<x$，此时考虑第三个点 $z$ ：
     - $z>y$，$y$ 的贡献为 $A\times y\times (t-r-2)$；
     - $z<y$，$y$ 的贡献为 $B\times y\times r$；
   - $y>x$，此时考虑第三个点 $z$；
     - $z>y$，$y$ 的贡献为 $B\times y\times (t-r-1)$；
     - $z<y$，$y$ 的贡献为 $C\times y\times (r-1)$。

   然后对于 $x$ 自己要进行一个统计，考虑三种情况：

   - $y,z<x$，$x$ 的贡献为 $C\times x\times \dfrac{r\times (r-1)}{2}$；
   - $y,z>x$，$x$ 的贡献为 $A\times x\times \dfrac{(t-r-1)\times (t-r-2)}{2}$；
   - $y<x,z>x$，$x$ 的贡献为 $B\times x\times r\times (t-r-1)$。

4. 直接搞一个三元环计数模板就行。

于是就很高兴地做完了，时间复杂度应该是 $O(n)+O(m)+O(n+m)+O(m\sqrt{m})=O(n+m\sqrt{m})$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
typedef unsigned long long u64; 

int n, m, u[200005], v[200005], deg[200005]; 
u64 A, B, C; 
vector<int> G[200005], E[200005]; 

u64 calc0(void) {
	u64 ans = 0; 
	for (int i = 0; i < n; ++i) {
		ans += A * (n - i - 1) * (n - i - 2) / 2 * i; 
		ans += B * i * (n - i - 1) * i; 
		ans += C * i * (i - 1) / 2 * i; 
	}
	cerr << "A0 " << ans << "\n"; 
	return ans; 
}
u64 calc1(void) {
	u64 ans = 0; 
	for (int i = 0; i < m; ++i) {
		int x = u[i], y = v[i]; 
		ans += A * x * (n - x - 2); // cerr << A * x * (n - x - 2) << " AT\n"; 
		ans += B * x * x; // cerr << B * x * x << " BT\n"; 
		ans += B * y * (n - y - 1); // cerr << B * y * (n - y - 1) << " CT\n"; 
		ans += C * y * (y - 1); // cerr << C * y * (y - 1) << " DT\n"; 
		ans += A * x * (x - 1) / 2; // cerr << A * x * (x - 1) / 2 << " ET\n"; 
		ans += B * (x + y) * (y - x - 1) / 2; // cerr << B * (x + y) * (y - x - 1) / 2 << " FT\n"; 
		ans += C * (n + y) * (n - y - 1) / 2; // cerr << C * (n + y) * (n - y - 1) / 2 << " GT\n"; 
	}
	cerr << "A1 " << ans << "\n"; 
	return ans; 
}
u64 calc2(void) {
	u64 ans = 0; 
	for (int x = 0; x < n; ++x) {
		int t = G[x].size(); // 算 x 自己
		for (int i = 0; i < t; ++i) {
			int y = G[x][i]; 
			if (y < x) {
				ans += A * y * (t - i - 2); // cerr << A * y * (t - i - 2) << " AT\n"; 
				ans += B * y * i; // cerr << B * y * i << " BT\n"; 
			} else if (y > x) {
				ans += B * y * (t - i - 1); // cerr << B * y * (t - i - 1) << " CT\n"; 
				ans += C * y * (i - 1); // cerr << C * y * (i - 1) << " DT\n"; 
			} else {
				ans += C * i * (i - 1) / 2 * x; // cerr << C * x * (1ull * i * (i - 1) / 2) << " ET\n"; 
				ans += A * (t - i - 1) * (t - i - 2) / 2 * x; // cerr << A * x * (1ull * (t - i - 1) * (t - i - 2) / 2) << " FT\n"; 
				ans += B * i * (t - i - 1) * x; // cerr << B * x * (1ull * i * (t - i - 1)) << " GT\n"; 
			}
		}
	}
	cerr << "A2 " << ans << "\n"; 
	return ans;  
}
int vis[200005]; 
u64 calc3(void) {
	u64 ans = 0; memset(vis, 0xff, sizeof vis); 
	for (int x = 0; x < n; ++x) {
		for (int y : E[x]) vis[y] = x; 
		for (int y : E[x]) for (int z : E[y]) if (vis[z] == x) {
			int t[] = {x, y, z}; sort(t, t + 3); 
			ans += A * t[0] + B * t[1] + C * t[2]; 
		}
	}
	cerr << "A3 " << ans << "\n"; 
	return ans; 
}

int main(void) {
	ios::sync_with_stdio(0); 
	cin >> n >> m >> A >> B >> C; 
	for (int i = 0; i < m; ++i) {
		cin >> u[i] >> v[i]; ++deg[u[i]]; ++deg[v[i]]; 
		G[u[i]].emplace_back(v[i]); G[v[i]].emplace_back(u[i]); 
		if (u[i] > v[i]) swap(u[i], v[i]); 
	}
	for (int i = 0; i < n; ++i) G[i].emplace_back(i), sort(G[i].begin(), G[i].end()); 
	for (int i = 0; i < m; ++i) {
		int x = u[i], y = v[i]; 
		if (deg[x] > deg[y] || (deg[x] == deg[y] && x > y)) swap(x, y);   
        E[x].emplace_back(y);
	}
	cout << calc0() - calc1() + calc2() - calc3() << "\n"; 
	return 0; 
}
```

---

## 作者：hater (赞：2)

~~发抖way怎么用树状数组，/qiao~~

这里来一个更简单的做法。

题目一眼容斥。

答案等于：所有的 $3$ 元组 $-$ 满足至少有一条边的 $3$ 元组 $+$ 满足至少有两条边的 $3$ 元组 $+$ 满足有三条边的 $3$ 元组。

第一个很简单随便做， 

第二个我们稍稍讨论，

分成 $3$ 类 ： 

 $i$ 和 $j$ 有边 ； $i$ 和 $k$ 有边 ； $j$ 和 $k$ 有边 ；

我们枚举边就好了。 

第三种也是分类讨论。

分成 $3$ 类 ： 

$i$ 和 $j$ ， $j$ 和 $k$ 有边 ；  

$i$ 和 $j$ ， $i$ 和 $k$ 有边 ； 

$i$ 和 $k$ ， $j$ 和 $k$ 有边 ；

这个稍微复杂，

思路是枚举那个共顶点的点。

排序做前缀和，查询时二分即可。

第 $4$ 种是经典的三元环计数，左转模板区粘板子。 

代码：

```cpp
#include<bits/stdc++.h>  
#define rg register 
#define u60 unsigned long long 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i )
using namespace std ; 
const int N = 2e5+10 ; 
struct node { int x , y ; } E[N] ; 
vector <int> v[N] , v2[N] ;   
vector <u60> s2[N] , s1[N] ;  
u60 sc[N] , sb[N] , ans , A , B , C , n , m , b[5] ; 
int rea[N] , deg[N] ;  
u60 calc( u60 x , u60 y , u60 z ) { 
  b[0] = x ; b[1] = y ; b[2] = z ; sort( b , b+3 ) ; 
  return b[0] * A + b[1] * B + b[2] * C ; 
} 
void all( ) { 
  fq( i , 0 , n-1 ) sc[i] = sc[i+1] + i * C ; 
  fq( i , 0 , n-1 ) sb[i] = sb[i+1] + B * i * (n-1-i) + sc[i+1] ; 
  fq( i , 0 , n-1 ) ans += A * i * ( (n-1-i) * (n-1) - (n+i)*(n-1-i)/2ull ) + sb[i+1] ;  
} 
void i_j( ) { 
  u60 x , y ; 
  fp( i , 1 , m ) { 
    x = E[i].x ; y = E[i].y ; if( x > y ) swap( x , y ) ; 
    ans -= ( A * (n-1-y) * x + B * (n-1-y) * y + C * ( (n+y)*(n-1-y)/2ull ) ) ; 
  } 
} 
void j_k( ) { 
  u60 x , y ; 
  fp( i , 1 , m ) { 
    x = E[i].x ; y = E[i].y ; if( x > y ) swap( x , y ) ; 
    ans -= ( B * x * x + C * x * y + A * ( (x-1)*x/2ull ) ) ; 
  } 
} 
void i_k( ) { 
  u60 x , y ; 
  fp( i , 1 , m ) { 
    x = E[i].x ; y = E[i].y ; if( x > y ) swap( x , y ) ; 
    u60 len = y-1-x ; 
    ans -= ( A * x * len + B * ( (x+y)*len/2ull ) + C * y * len ) ;
  } 
} 
void i_jandj_k( ) { 
  u60 p ; 
  fp( i , 0 , n-1 ) { 
    if( v[i].size() == 0 ) continue ; 
    p = lower_bound( v[i].begin() , v[i].end() , i ) - v[i].begin() ; 
	int l = v[i].size() ; 
	if( p == l || p == 0 ) continue ; 
	ans += ( A * s1[i][p-1] * (l-p) + B * i * p * (l-p) + C * s2[i][p] * p ) ; 
  } 
} 
void i_kandj_k( ) { 
  u60 x , y ; 
  fp( i , 0 , n-1 ) { 
    if( v[i].size() == 0 ) continue ; 
    int l = v[i].size() ; 
    fp( j , 0 , l-1 ) { 
      y = v[i][j] ; if( y > i ) break ; 
	  ans += ( A * ( j ? s1[i][j-1] : 0 ) + B * y * j + C * i * j ) ;  
	} 
  } 
} 
void i_jandi_k( ) { 
  u60 x , y ; 
  fp( i , 0 , n-1 ) { 
    int l = v[i].size() ; 
    fq( j , 0 , l-1 ) { 
      y = v[i][j] ; if( i > y ) break ; 
      ans += ( A * i * (l-1-j) + B * y * (l-1-j) + C * ( j!=l-1 ? s2[i][j+1] : 0 ) ) ; 
	} 
  } 
} 
void cir( ) { 
  fp( i , 0 , n-1 ) { 
    u60 y , z ; 
    fp( j , 0 , (int)(v2[i].size())-1 ) 
      y = v2[i][j] , rea[y] = i+1 ; 
	fp( j , 0 , (int)(v2[i].size())-1 ) { 
	  y = v2[i][j] ; 
	  fp( k , 0 , (int)(v2[y].size()-1) ) { 
	    z = v2[y][k] ; 
	    if( rea[z] == i+1 ) 
	      ans -= calc( i , y , z ) ; 
	  } 
	} 
  } 
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  cin >> n >> m ; 
  cin >> A >> B >> C ; 
  fp( i , 1 , m ) { 
    cin >> E[i].x >> E[i].y ; 
    deg[E[i].x] ++ ; deg[E[i].y] ++ ; 
    v[E[i].x].push_back(E[i].y) ; 
    v[E[i].y].push_back(E[i].x) ; 
  } 
  all( ) ; 
  i_j( ) ; j_k( ) ; i_k( ) ; 
  fp( i , 0 , n-1 ) { 
    sort( v[i].begin() , v[i].end() ) ; 
    int l = v[i].size() ; 
    s1[i].resize( l ) ; s2[i].resize( l ) ;   
    fp( j , 0 , l-1 ) s1[i][j] = ( j ? s1[i][j-1] : 0 ) + v[i][j] ; 
	fq( j , 0 , l-1 ) s2[i][j] = ( j!=l-1 ? s2[i][j+1] : 0 ) + v[i][j] ;   
  } 
  i_jandj_k( ) ; i_kandj_k( ) ; i_jandi_k( ) ; 
  fp( i , 1 , m ) { 
    if( deg[E[i].x] > deg[E[i].y] ) swap( E[i].x , E[i].y ) ; 
    if( deg[E[i].x] == deg[E[i].y] && E[i].x > E[i].y ) swap( E[i].x , E[i].y ) ; 
    v2[E[i].x].push_back(E[i].y) ; 
  } 
  cir( ) ; 
  cout << ans << '\n' ;  
  return 0 ; 
} 
```


---

## 作者：HPXXZYY (赞：0)

> 我敢赌，就算你知道怎么做，也必然得调试半天才能 AC。

$\color{blue}{\texttt{[Analysis]}}$

显然不可能正面计算。所以被迫正难则反。

把所有三元组分成四类：不考虑有没有边相连；有且只有一条边连接；有且只有两条边连接；三个点形成三元环。

每种情况分别考虑。

1. 不考虑有没有边相连。

    等价于对所有 $(i,j,k) \quad \text{s.t.} \quad  0 \leq i <j<k<n$ 求出 $\sum\limits_{\text{legal (i,j,k)}} Ai+Bj+Ck$。
  
    枚举 $k$，则 $(i,j)$ 只能在 $[0,k-1]$ 中取值，共 $\dfrac{k(k-1)}{2}$ 种情况。
  
    对于固定的 $k$，$\sum\limits_{0 \leq i < j <k}Ai+Bj=\sum\limits_{0 \leq i < k-1}\left ( \sum\limits_{i<j<k}Ai+Bj \right )=\sum\limits_{0\leq i <k-1} \left ( Ai(k-i-1)+\sum\limits_{i<j<k}Bj\right )$
   
    然后把括号内的项展开，可以得到关于 $\sum i^2$，$\sum i$ 的式子，这些式子都是有公式可以 $O(1)$ 计算的。
3. 有且只有一条边连接的三元组。
    
    枚举每条边 $(u,v) \quad \text{s.t.} \quad u<v$，则第三个点 $w$ 只有三种情况：$w<u<v$，$u<w<v$，$u<v<w$。每种情况下 $u,v$ 的贡献都是确定的，而 $w$ 的和是连续正整数的和，可以用公式求出。
   
    **注意：** 用这种方法求出的三元组包含了第三步和第四步的情况。因此，准确地说，第二种情况是**有边相连的三元组**。

3. 有且只有两条边连接的三元组。
    
    这是最不好想的一种情况。不仅容易漏掉，也不好想解决方法。
   
    正解还是很惊艳的。三个点有且只有两条边连接，必然两条边有一个公共点。枚举这个公共点 $u$，那么 $v,w$ 就只能在和 $u$ 有边相连的点集中取值。
   
    问题是，这个点集可能很大，怎么办？
   
    那我们就不要同时考虑 $v,w$，仅考虑单个点对答案的贡献。
   
    如果 $v<u$，那么 $v$ 前面的系数可能是 $A$ 或者 $B$（绝对不会是 $C$）。如果系数是 $A$，那么 $w$ 比 $v$ 大。在一个有限的点集中，我们很容易知道这样的 $w$ 有多少个，因此 $Av$ 的系数我们就可以求出来（**请注意，我们只算 $v$ 的贡献，至于 $w$ 的和我们先不考虑**）。其它情况同理。
   
    枚举点集里的所有点，即可求出第三种情况的贡献。
   
    **注意：** 第三步里也重复计算了第四步的情况。
4. 有三条边连接的三元组。
    
    这部分最简单了。直接用三元组计数的模板即可。
     
    （当然，不会这个模板就是送命。）

现在来考虑容斥系数。分别记四个步骤算出来的结果为 $S_1,S_2,S_3,S_4$。
- 所有的三元组都会在第一步中计算且仅计算一次。
- 第二步中，有且仅有一条边连接的三元组仅计算了一次，两条边相连的三元组计算了两次，三条边相连的三元组计算了三次。
- 第三步中，有两条边相连的二元组计算了一次；三条边相连的三元组计算了三次。
- 第四步中，三条边连接的三元组都仅计算了一次。

因此，通过你聪明的大脑，你一定可以发现，答案就是 $S_1-S_2+S_3-S_4$。

就这么开心的写代码吧。小心细节不要 WA 哦。

$\color{blue}{\text{Code}}$

```cpp
typedef unsigned long long ll; 

const int N=2e5+100; 

int n,m,A,B,C,u[N],v[N];
ll ans;
vector<int> edge[N],e[N];

ll pre_sqr(int n){
	return 1ull*n*(n+1)/2*(2*n+1)/3;
}
ll pre_sum(int n){
	return 1ull*n*(n+1)/2;
}
ll get_sum(int a,int b){
	int t=(b-a+1);
	return 1ull*(a+b)*t/2;
}

ll get_all(){
	ll cnt,tmp1,tmp2,res=0;
	
	for(int j=2;j<n;j++){
//		从 0 到 j-1 中选出两个数
		int i=j-1;//写着简单 
		
		cnt=pre_sum(i);
		tmp1=1ull*i*pre_sum(i-1)-pre_sqr(i-1);
		tmp2=pre_sqr(i);
		
		res+=1ull*tmp1*A;
		res+=1ull*tmp2*B;
		res+=1ull*cnt*C*j;
	}
	
	return res;
}//第一步

ll get_minus(){
	ll res=0;
	
	for(int i=1;i<=m;i++){
		if (u[i]>v[i]) swap(u[i],v[i]);
		
		//(x, u[i], v[i])
		if (u[i]>0)
			res+=1ull*A*pre_sum(u[i]-1)+1ull*u[i]*(1ull*B*u[i]+1ull*C*v[i]);
		
		//(u[i], x, v[i])
		if (v[i]-u[i]>1)
			res+=1ull*B*get_sum(u[i]+1,v[i]-1)+(1ull*A*u[i]+1ull*C*v[i])*(v[i]-u[i]-1);
		//(u[i], v[i], x)
		if (v[i]<n-1)
			res+=1ull*C*get_sum(v[i]+1,n-1)+(1ull*A*u[i]+1ull*B*v[i])*(n-1-v[i]);
	} 
	
	return res;
}//第三步

int ind[N],vistime[N];

ll get_triple(){
	ll res=0;
	
	for(int i=1;i<=m;i++){
		++ind[u[i]];
		++ind[v[i]];
	}
	
	for(int i=1;i<=m;i++){
		if (ind[u[i]]>ind[v[i]]) swap(u[i],v[i]);
		else if ((ind[u[i]]==ind[v[i]])&&(u[i]>v[i])) swap(u[i],v[i]);
		
		edge[u[i]].push_back(v[i]);
	}
	
	memset(vistime,-1,sizeof(vistime));//注意这里，不然可能会多算出一些三元组
	for(int i=0;i<n;i++){
		for(int j:edge[i]) vistime[j]=i;
		
		for(int j:edge[i])
			for(int k:edge[j])
				if (vistime[k]==i){//因为这里
					int t[]={i,j,k};
					sort(t,t+3);
					
					res+=1ull*A*t[0]+1ull*B*t[1]+1ull*C*t[2];
				}
	}
	
	return res;
}//第四步，三元环计数的板子

ll get_add(){
	for(int i=1;i<=m;i++){
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
	}
	
	ll res=0;
	
	for(int u=0;u<n;u++){
		e[u].push_back(u);
		sort(e[u].begin(),e[u].end());
		
		int x=e[u].size()-1;
		if (x==0) continue;
		
		for(int i=0;i<=x;i++){
			int v=e[u][i];
			
			if (v<u)
				res+=1ull*A*v*(x-i-1)+1ull*B*v*i;
			else if (v>u)
				res+=1ull*B*v*(x-i)+1ull*C*v*(i-1);
			else
				res+=1ull*v*(1ull*(x-i)*(x-i-1)/2*A+1ull*B*(x-i)*i+1ull*i*(i-1)/2*C); 
		}
	}//第二步
	
	return res;
}

int main(){
	n=read();m=read();
	A=read();B=read();C=read();
	for(int i=1;i<=m;i++){
		u[i]=read();
		v[i]=read();
	}
	
	ans=get_all()-get_minus()+get_add()-get_triple();
	
	cout<<ans<<endl;
	
	return 0;
}
```

最后，Good luck to you。

---

## 作者：Phartial (赞：0)

考虑对一个团队中冲突的个数容斥：

### 无限制

枚举每个人 $u$ 并计算其贡献即可，时间复杂度 $\Theta(n)$。

### 有至少一对冲突

枚举这对冲突 $(u,v)$（$u<v$），对第三个人的位置分类讨论并计算贡献即可，时间复杂度 $\Theta(m)$。

### 有至少两对冲突

枚举两个冲突的共用点 $u$，对其邻点按编号从小到大做扫描线并计算贡献即可，时间复杂度 $\Theta(m\log m)$。

### 有至少三对冲突

这就是无向图三元环计数，时间复杂度 $\Theta(m\sqrt{m})$。

具体的式子可以看代码，不难推。

```cpp
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
using ull = unsigned long long;

const int kN = 2e5 + 1;

int n, m, d[kN], v[kN];
pair<int, int> r[kN];
vector<int> e[kN];
ull a[3], ans;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (ull &i : a) {
    cin >> i;
  }
  for (int i = 1; i <= m; ++i) {
    cin >> r[i].first >> r[i].second;
    ++d[r[i].first], ++d[r[i].second];
  }
  // 无限制
  for (int i = 0; i < n; ++i) {
    ans += a[0] * i * (1ull * (n - 1 - i) * (n - 2 - i) / 2);
    ans += a[1] * i * i * (n - 1 - i);
    ans += a[2] * i * (1ull * i * (i - 1) / 2);
  }
  // 有至少一对冲突
  for (int i = 1; i <= m; ++i) {
    int x = r[i].first, y = r[i].second;
    x > y && (swap(x, y), 0);
    ans -= a[0] * (1ull * (x - 1) * x / 2) + (a[1] * x + a[2] * y) * x;
    ans -= a[1] * (1ull * (x + y) * (y - x - 1) / 2) + (a[0] * x + a[2] * y) * (y - x - 1);
    ans -= a[2] * (1ull * (y + n) * (n - y - 1) / 2) + (a[0] * x + a[1] * y) * (n - y - 1);
  }
  // 有至少两对冲突
  for (int i = 1; i <= m; ++i) {
    e[r[i].first].push_back(r[i].second);
    e[r[i].second].push_back(r[i].first);
  }
  for (int i = 0; i < n; ++i) {
    sort(e[i].begin(), e[i].end());
    int c0 = 0, c1 = 0;
    ull s0 = 0, s1 = 0;
    for (int j : e[i]) {
      if (j < i) {
        ans += a[0] * s0 + (a[1] * j + a[2] * i) * c0;
        ++c0, s0 += j;
      } else {
        ans += a[0] * s0 + (a[1] * i + a[2] * j) * c0;
        ans += a[1] * s1 + (a[0] * i + a[2] * j) * c1;
        ++c1, s1 += j;
      }
    }
  }
  // 有至少三对冲突
  for (int i = 0; i < n; ++i) {
    e[i].clear();
  }
  for (int i = 1; i <= m; ++i) {
    if (tie(d[r[i].first], r[i].first) > tie(d[r[i].second], r[i].second)) {
      swap(r[i].first, r[i].second);
    }
    e[r[i].first].push_back(r[i].second);
  }
  fill_n(v, n, -1);
  for (int i = 0; i < n; ++i) {
    for (int j : e[i]) {
      v[j] = i;
    }
    for (int j : e[i]) {
      for (int k : e[j]) {
        if (v[k] == i) {
          int b[3] = {i, j, k};
          sort(b, b + 3);
          ans -= a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
        }
      }
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：lfxxx (赞：0)

这哪来的 2700？

考虑容斥一下，用所有三元组的贡献减去至少有一条存在于三元组之间的边的三元组的贡献。

至少存在边 $(i,j)$ 的情况考虑枚举 $i,j$，然后满足条件的 $k$ 是一段后缀，可以简单计算，其余两条边同理。

至少存在边 $(i,j),(i,k)$ 的情况可以考虑将 $i$ 所有大于其的出边排序后从小往大加入，动态维护下可选的 $j$ 的和即可简单计算，其余情况同理。

三条边同时存在就是三元环计数板子，可以 $O(m \sqrt m)$ 地计算。

总时间复杂度 $O(m \sqrt m)$。

[代码](https://codeforces.com/contest/985/submission/290760380)

---

## 作者：bluewindde (赞：0)

本题直接算答案很困难，建其完全图的补图然后跑三元环计数边数会爆炸（设原图 $G_0 = (V_0, E_0)$，其完全图 $G_1 = (V_1, E_1)$，补图 $G_2 = (\complement_{V_1}V_0,\complement_{E_1}E_0)$，也就是说，补图至少有 $\frac 1 2 n \cdot (n - 1) - m = 19,999,700,000$ 条边）。

考虑容斥计算答案，设 $x$ 表示三个点之间至少有一条边的答案，$y$ 表示三个点之间至少有两条边的答案，$z$ 表示三个点之间有三条边的答案。$w$ 表示所有可能的三元组的答案。

---

一次三元环计数可以处理出 $z$，这里不再赘述。时间复杂度 $O(m \sqrt m)$。

---

考虑处理 $x$，枚举每个点 $a$ 的相连点 $b$。

不妨设 $a < b$，三元组的另外一个点为 $c$。

1. $a$ 的贡献：
    - 作为三元组第一个元素，后两个元素一个为 $b$，另一个有 $n - a - 2$ 种取值，贡献 $A \cdot a \cdot (n - a - 2)$；
    - 作为三元组第二个元素，第一个元素有 $a$ 种取值，贡献 $B \cdot a \cdot a$；
    - 不可能作为三元组第三个元素。
2. $b$ 的贡献：
    - 不可能作为三元组第一个元素；
    - 作为三元组第二个元素，第三个元素有 $n - b - 2$ 种取值，贡献 $B \cdot b \cdot (n - b - 1)$；
    - 作为三元组第三个元素，前两个元素一个为 $a$，另一个有 $b - 1$ 种取值，贡献 $C \cdot b \cdot (b - 1)$。
3. $c$ 的贡献：
    - 作为三元组第一个元素，取值范围是 $[0, a)$，贡献 $\frac 1 2 A \cdot a \cdot (a - 1)$；
    - 作为三元组第二个元素，取值范围是 $(a, b)$，贡献 $\frac 1 2 B \cdot (a + b) \cdot (b - a - 1)$；
    - 作为三元组第三个元素，取值范围是 $(b, n]$，贡献 $\frac 1 2 C \cdot (b + n) \cdot (n - y - 1)$。

时间复杂度 $O(n + m)$。

---

考虑处理 $y$，仍然枚举每个点 $a$ 的相连点 $b$。但这次枚举将 $a$ 认为是三元组中两条边的交点，与上面的枚举不同。

设三元组的另外一个点为 $c$，$a$ 的度数为 $deg_a$。在点 $a$ 和点 $a$ 的相连点中，编号小于 $b$ 的点个数为 $less_b$。

1. $a > b$ 时 $b$ 的贡献：
    - 作为三元组第一个元素，后两个元素一个为 $a$，另一个有 $deg_a - less_b - 1$ 种取值，贡献为 $A \cdot b \cdot (deg_a - less_b - 1)$；
    - 作为三元组第二个元素，第一个元素有 $less_b$ 种取值，贡献为 $B \cdot b \cdot less_b$。
    - 不可能作为三元组第三个元素；
2. $a < b$ 时 $b$ 的贡献：
    - 不可能作为三元组第一个元素；
    - 作为三元组第二个元素，第三个元素有 $deg_a - less_b$ 种取值，贡献为 $B \cdot b \cdot (deg_a - less_b)$；
    - 作为三元组第三个元素，前两个元素一个为 $a$，另一个有 $less_b - 1$ 种取值，贡献为 $C \cdot b \cdot$
3. $a$ 的贡献：
    - 作为三元组第一个元素，另外两个元素的取值范围是 $(a, n]$，贡献为 $\frac 1 2 A \cdot a \cdot (deg_a - less_a) \cdot (deg_a - less_a - 1)$；
    - 作为三元组第二个元素，另外两个元素的取值范围分别是 $[0, a)$ 和 $(a, n]$，贡献为 $B \cdot a \cdot (deg_a - less_a) \cdot less_a$；
    - 作为三元组第三个元素，另外两个元素的取值范围是 $[0, a)$，贡献为 $\frac 1 2 C \cdot a \cdot less_a \cdot (less_a - 1)$。

时间复杂度 $O(n + m \log_2 m)$。

---

考虑处理 $w$，枚举每个点 $a$ 作为每个位置时的贡献。

- 作为三元组第一个元素，另外两个元素的取值范围是 $(a, n]$，贡献为 $\frac 1 2 A \cdot a \cdot (n - a - 1) \cdot (n - a - 2)$；
- 作为三元组第二个元素，另外两个元素的取值范围分别是 $[0, a)$
 和 $(a, n]$，贡献为 $\frac 1 2 A \cdot a \cdot a \cdot (n - a - 1)$；
- 作为三元组第三个元素，另外两个元素的取值范围是 $[0, a)$，贡献为 $\frac 1 2 A \cdot a \cdot a \cdot (a - 1)$；

时间复杂度 $O(n)$。

---

最后，根据容斥原理，答案为 $w - x + y - z$。

---

**回顾**：本题的难点在于计算各种贡献，极其容易出错；重点在于转化为容斥问题，是一道不可多得的好题。

[code.](https://www.luogu.com.cn/paste/u5itcau0)

本题有些卡常。（还是我常数大？）


---

## 作者：Argon_Cube (赞：0)

这是 \*2700？

* **【解题思路】**

首先显然正难则反。

1. 至少有一条边：枚举是哪一条边，分 $3$ 种情况计算贡献。
2. 至少有两条边：枚举公共点 $u$，然后考虑这个点所有能到达的点。枚举剩下两个点中编号较大那个，分 $3$ 种情况计算贡献。
3. 三元环：直接套板子。

然后直接容斥。

* **【代码实现】**

```cpp
/*********************************************************************
    Author:Unnamed Cube
    Datetime: 2023/1/31 17:19:18
*********************************************************************/
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <array>

using namespace std;

inline unsigned long long rgsuml(unsigned long long a,unsigned long long b)
{
	return b*(b+1)-a*(a-1)>>1;
}

array<vector<int>,200000> graph,graph2;
bitset<200000> islinked;
vector<int> linkls,linkgtr;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	unsigned long long a,b,c,answer=0,cnt,cnte;
	cin>>cnt>>cnte>>a>>b>>c;
	for(int i=0;i<cnt;i++)
		answer+=a*i*((cnt-i-1)*(cnt-i-2)>>1)+b*i*i*(cnt-i-1)+c*i*(i*(i-1ull)>>1);
	for(int i=0;i<cnte;i++)
	{
		int nd1,nd2;
		cin>>nd1>>nd2;
		graph[nd1].push_back(nd2),graph[nd2].push_back(nd1);
	}
	for(int i=0;i<cnt;i++)
	{
		for(int j:graph[i])
		{
			if(j>i)
				answer-=a*rgsuml(0,i-1)+i*(b*i+c*j)+b*rgsuml(i+1,j-1)+(j-i-1)*(a*i+c*j)+c*rgsuml(j+1,cnt-1)+(cnt-1-j)*(a*i+b*j),linkgtr.push_back(j);
			else
				linkls.push_back(j);
			if(make_pair(graph[i].size(),i)<make_pair(graph[j].size(),j))
				graph2[i].push_back(j);
		}
		sort(linkls.begin(),linkls.end()),sort(linkgtr.begin(),linkgtr.end());
		unsigned long long tmpsum1=0,tmpsum2=0;
		for(int j=0;j<linkls.size();j++)
			answer+=a*tmpsum1+j*(b*linkls[j]+c*i),tmpsum1+=linkls[j];
		for(int j=0;j<linkgtr.size();j++)
			answer+=a*tmpsum1+linkls.size()*(b*i+c*linkgtr[j])+b*tmpsum2+j*(a*i+c*linkgtr[j]),tmpsum2+=linkgtr[j];
		linkls.clear(),linkgtr.clear();
	}
	for(int i=0;i<cnt;i++)
	{
		for(int j:graph2[i])
			islinked.set(j);
		for(int j:graph2[i])
			for(int k:graph2[j])
				if(islinked[k])
				{
					int tmpmin=min(i,min(j,k)),tmpmax=max(i,max(j,k));
					answer-=a*tmpmin+b*(i+j+k-tmpmin-tmpmax)+c*tmpmax;
				}
		for(int j:graph2[i])
			islinked.reset(j);
	}
	cout<<answer;
	return 0;
}

```

---

## 作者：Msents (赞：0)

题目依托够使

直接统计答案很难，故反着来。

先计算所有三元组的贡献。

然后去掉三个点中至少连了一条边的三元组的贡献，这个在读入边的时候可以直接算。

发现对于三个点中连了至少两条边的三元组的贡献在上一步被多减了，遍历每个点和与这个点相连的边，再把贡献加回来。

最后发现三元环的贡献又被加回来了，再跑一遍[三元环计数](/problem/P1989)，减去三元环的贡献，然后没了，输出答案。

然后你就会发现这题就是典**容斥**。

虽然这题解最后一句话就能概括完了，但我调了两天。

码：

```cpp20
#include<bits/stdc++.h>
using namespace std;
using ullong=unsigned long long;
#define int ullong
const int MaxN=200000;
int n,m,a,b,c,d[MaxN];
vector<int>g[MaxN],g2[MaxN];
pair<int,int>edge[MaxN];
bool vst[MaxN];
int temp[MaxN];
void Solve(){
	cin>>n>>m>>a>>b>>c;
	int ans=0;
	for(int i=0;i<n;i++)ans+=i*a*((n-i-1)*(n-i-2)/2);
	for(int i=0;i<n;i++)ans+=i*b*i*(n-i-1);
	for(int i=0;i<n;i++)ans+=i*c*(i*(i-1)/2);
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		if(u>v)swap(u,v);
		edge[i]=make_pair(u,v);
		d[u]++;
		d[v]++;
		ans-=(u*(u-1)/2)*a+u*(u*b+v*c);
		ans-=(n-1-v)*(u*a+v*b)+((n+v)*(n-1-v)/2)*c;
		ans-=(v-u-1)*(u*a+v*c)+((u+1+v-1)*(v-1-u)/2)*b;
	}
	for(int i=0;i<m;i++){
		int u,v;
		tie(u,v)=edge[i];
		if(d[u]>d[v])swap(u,v);
		g[u].push_back(v);
		g2[u].push_back(v);
		g2[v].push_back(u);
	}
	for(int u=0;u<n;u++){
		vector<int>l,r;
		int sum=0;
		for(int v:g2[u]){
			sum++;
			if(v<u)l.push_back(v);
			else r.push_back(v);
		}
		sort(l.begin(),l.end());
		sort(r.begin(),r.end());
		for(int i=0;i<l.size();i++)ans+=l[i]*(a*(sum-1-i)+b*i);
		for(int i=0;i<r.size();i++)ans+=r[i]*(b*(r.size()-1-i)+c*(i+l.size()));
		ans+=u*(c*(l.size()*(l.size()-1)/2)+b*(l.size()*r.size())+a*(r.size()*(r.size()-1)/2));
	}
	for(int u=0;u<n;u++){
		for(int v:g[u])vst[temp[++temp[0]]=v]=true;
		for(int v:g[u]){
			for(int w:g[v]){
				if(vst[w]){
					int arr[]={u,v,w};
					if(arr[0]>arr[1])swap(arr[0],arr[1]);
					if(arr[0]>arr[2])swap(arr[0],arr[2]);
					if(arr[1]>arr[2])swap(arr[1],arr[2]);
					ans-=(arr[0]*a+arr[1]*b+arr[2]*c);
				}
			}
		}
		while(temp[0])vst[temp[temp[0]--]]=false;
	}
	cout<<ans;
}
#undef int
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	Solve();
	return 0;
}
```

---

