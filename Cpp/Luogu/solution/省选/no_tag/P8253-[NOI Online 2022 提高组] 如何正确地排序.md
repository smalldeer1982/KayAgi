# [NOI Online 2022 提高组] 如何正确地排序

## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

**这一题中出现了评测记录测试点编号错乱的问题，是民间数据命名方式冲突导致的。但是我们保证其相对顺序没有混乱。**

民间数据提供者：@QwQcOrZ。

## 题目描述

有一个 $m\times n$ 的数组 $a_{i,j}$。  
定义：

$$f(i,j)=\min\limits_{k=1}^m(a_{k,i}+a_{k,j})+\max\limits_{k=1}^m(a_{k,i}+a_{k,j})$$

你需要求出 $\sum\limits_{i=1}^n\sum\limits_{j=1}^nf(i,j)$。

## 说明/提示

**【样例 1 解释】**

以 $f(3,5)$ 为例：

$$\begin{aligned}f(3,5)&=\max(a_{1,3}+a_{1,5},a_{2,3}+a_{2,5},a_{3,3}+a_{3,5})+\min(a_{1,3}+a_{1,5},a_{2,3}+a_{2,5},a_{3,3}+a_{3,5})\\&=\max(9,7,10)+\min(9,7,10)\\&=10+7\\&=17\end{aligned}$$

下面给出 $f(i,j)$ 的数表，第 $i$ 行第 $j$ 列表示 $f(i,j)$：

$$\begin{array}{|c|c|c|c|c|}\hline20&27&18&22&20\\\hline27&34&24&29&23\\\hline18&24&20&22&17\\\hline22&29&22&24&22\\\hline20&23&17&22&18\\\hline\end{array}$$

它们的和是答案 $564$。

**【样例 2, 3, 4】**

见选手目录下的 `sort/sort*.in` 与 `sort/sort*.ans`。

**【数据范围与提示】**

对于所有测试点：$2\le m\le 4$，$1\le n\le 2\times {10}^5$，$1\le a_{i,j}\le 2\times 10^5$。

每个测试点的具体限制见下表

![](https://cdn.luogu.com.cn/upload/image_hosting/h38vdmnj.png)

## 样例 #1

### 输入

```
3 5
1 7 2 2 7
9 10 4 10 3
7 7 8 10 2```

### 输出

```
564```

# 题解

## 作者：enucai (赞：71)

## Preface

**二维偏序**解法。来一篇代码简单一点的题解，代码长度 $1.12$ KB。

## Analysis

**正难则反**。我们很难正向计算每个数的贡献（三维偏序），那么我们假设所有数对 $\max$ 和 $\min$ 都有贡献，则答案为 $2n\times sum$，这个很容易计算。

接下来我们要减去没有对 $\max$ 产生贡献的与没有对 $\min$ 产生贡献的数。假设现在有**三个**数组 $A,B,C$。我们要算对于 $B$ 中的每一个数 $B_i$，有多少个 $j$ 满足一下条件：

$$
\begin{cases}
A_i+A_j\le B_i+B_j\\
B_i+B_j\le C_i+C_j
\end{cases}
$$

移项一下，得：

$$
\begin{cases}
A_i-B_i\le B_j-A_j\\
B_i-C_i\le C_j-B_j
\end{cases}
$$

这是一个二维偏序问题，可以 $O(n\log n)$ 解决。

所以我们只要枚举任意有序的三个数组，进行上述算法即可算出所有不合法的数的总和，减去即可。时间复杂度 $O(n\log n)$，带一个 $24$ 的**常数**。

需要注意的是，可能有相等的数，执行上述算法两者都会被减去，因此**强制规定**：若两个数相同，编号小的数组中的元素 $<$ 编号大的数组中的元素。

## Code

**Talk is cheap, show me the code.**

奉上极简代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define N 200010
#define base 200001
int n,m,a[4][N],ans=0,c[2*N],tot;
struct que{
	int op,x,y,val;
	bool operator<(const que &p)const{
		if(x!=p.x) return x<p.x;
		return op<p.op;
	}
}q[400010];
void upd(int x){
	while(x<2*base) c[x]++,x+=x&(-x);
}
int qry(int x){
	int res=0;
	while(x) res+=c[x],x-=x&(-x);
	return res;
}
int calc(int x,int y,int z){
	int res=0;
	memset(c,0,sizeof(c)),tot=0;
	For(i,1,n){
		q[++tot]=(que){0ll,a[x][i]-a[y][i]+(x>y),a[y][i]-a[z][i]+(y>z),0ll};
		q[++tot]=(que){1ll,a[y][i]-a[x][i],a[z][i]-a[y][i],a[y][i]};
	}
	sort(q+1,q+tot+1);
	For(i,1,tot){
		if(q[i].op==0) upd(q[i].y+base);
		else res+=q[i].val*qry(q[i].y+base);
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>m>>n;
	For(i,0,m-1) For(j,1,n) cin>>a[i][j];
	For(i,m,3) For(j,1,n) a[i][j]=a[i-m][j];
	For(i,0,3) For(j,1,n) ans+=2*n*a[i][j];
	For(i,0,3) For(j,0,3) For(k,0,3) if(i!=j&&j!=k&&k!=i) ans-=calc(i,j,k);
	cout<<ans;
}
```

---

## 作者：peppaking8 (赞：28)

### 题目描述

原题是最简洁的题面，[链接](https://www.luogu.com.cn/problem/P8253)。

### 解答

**upd**：感觉代码不加注释很难说清楚...加了点注释


**说明**：这个解答只适用于 $m\le 4$ 的情况，不能拓展到 $m\ge 5$。我会写出一些我的思考过程。

首先考虑 $m=2$ 的部分分，这还挺简单的，因为只有两个数取 $\min,\max$，所以
$$f(i,j)=a_{1,i}+a_{1,j}+a_{2,i}+a_{2,j}$$
把它们累加起来，容易得到
$$ans=2n\times \sum\limits_{i=1,2\ 1\le j\le n} a_{i,j}$$
在 $m=3$ 时，情况就变得复杂了，因为是三个数的最值，夹在中间的不会被算进答案。比较显然的想法是分开 $\min$ 和 $\max$ 计算答案。比如说我们要求 $\max$，容易想到分开考虑三个位置，对于位置 $p$，我们想要求出
$$\sum\limits_{P(i,j)} (a_{p,i}+a_{p,j})$$
其中，$P(i,j)$ 即 $a_{p,i}+a_{p,j}$ 是 $a_{1,i}+a_{1,j},\cdots,a_{3,i}+a_{3,j}$ 中的最大值。细致分析，若 $a_{p,i}+a_{p,j}\ge a_{q,i}+a_{q,j}$，那么
$$a_{p,i}-a_{q,i}\ge -(a_{p,j}-a_{q,j})$$
为什么要这么写呢？相当于两边都是独立的了，记 $x_i=a_{p,i}-a_{q,i}$，那么上式相当于一个偏序关系：$x_i\ge -x_j$。同理有另外一个差 $y_i$，也应该有 $y_i\ge -y_j$。固定 $i$ 求 $j$ 的个数，这是一个经典的**二维偏序**问题，离线下来用树状数组即可 $O(n\log n)$ 求出答案。

我们需要求多少次呢？三个位置，分别求最小值、最大值，常数是 $6$，可以通过。

我们更进一步：$m=4$ 时呢？如果直接把上面的东西推广，则需要处理一个三维偏序的问题，虽然 CDQ 分治常数很小，但是毕竟常数 $4\times 2=8$，TLE 的风险很大。

这时，妙的地方就来了：可以把 $m=4$ 转化为 $m=3$ 的情形！如果我们把这 $4$ 行中的每三行都用 $m=3$ 的方法求一遍，来看看会发生什么。对于 $(i,j)$，一共有四个数，$ans$ 是把最大的和最小的都统计进答案。如果每三行都处理一遍，那么容易得到：最大、最小的被统计了 $3$ 遍，次大、次小的被统计了 $1$ 遍。

所以说，减去所有数对的和，然后除以 $2$，就能得到题目所让我们求的值啦！时间复杂度 $O(n\log n)$，常数相比先前要乘 $4$，故为 $24$。虽然 $3s$ 仍看起来吃力，但是 $n\log n$ 的瓶颈是排序和树状数组，这两个是常数极小二人组，所以没啥问题。

赛时代码在 $m=4,n=2\times 10^5$ 时约为 $1.5s$。

### 需要注意的细节

虽说是求 $\min,\max$，但是如果两个数相等，有可能会被计算两次。所以我们可以规定一个序来保证不会算重。在下面的代码里，```Solve(i1,i2,i3,o)``` 表示 $i_1$ 行是 $i_1,i_2,i_3$ 行里面最值的答案，```o``` 是用来保证不算重的工具。我们强制钦定，若两个数相同，则列数更小的那组更小。

### 赛时代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200005;
int m,n;
int a[4][N];
ll ans=0,sum=0;
struct Node{
	int x,y;
	int v;
}b[N];
int c[N<<1];
inline int lowbit(int x){
	return x&(-x);
}
inline void add(int x,int k=1){
	for(int i=x;i<(N<<1);i+=lowbit(i)) c[i]+=k;
}
inline int ask(int x){
	int ret=0;
	for(int i=x;i;i-=lowbit(i)) ret+=c[i];
	return ret;
}
bool cmp(Node k1,Node k2){
	return k1.x<k2.x;
}
void Solve(int i1,int i2,int i3,int o){
	for(int i=1;i<=n;i++){// 要对 b[i].x,b[i].y 做二维偏序
		b[i].x=a[i2][i]-a[i1][i];
		b[i].y=a[i3][i]-a[i1][i];
		b[i].v=a[i1][i];
	}
	sort(b+1,b+n+1,cmp); // 按照 x 排序，然后用树状数组记录 y 维，经典的处理手段
	int R=n;
	while(R>=1 && -b[R].x-(!o)<b[1].x) R--; 
    // 这里我把点和询问放到一起了，因为询问恰好满足 (x,y)=(-b[i].x,-b[i].y)，故排序的时候和点恰好是倒序关系。R 记录当前已经处理好的询问。
    // o=0时，只需要 -b[R].x<=b[1].x 即可，否则需要小于。下面同理。
    // 为什么前面要加一个 while 呢？因为有可能询问的 x 坐标不包含所有的点，这时要把它们直接跳过。 
	for(int i=1;i<n;i++){
		add(b[i].y+N);
		while(R>=1 && -b[R].x-(!o)<b[i+1].x){ // 同理
			ans+=(ll)b[R].v*ask(-b[R].y-(o<=1)+N);
			R--;
		}
	}
	add(b[n].y+N);
	while(R>=1){
		ans+=(ll)b[R].v*ask(-b[R].y-(o<=1)+N);
		R--;
	}
   // 处理剩下的询问
	for(int i=1;i<=n;i++) add(b[i].y+N,-1); // 将树状数组清零
	R=1; // 接下来就是倒过来处理了，相当于求最小值的贡献
	while(R<=n && -b[R].x+(o>=1)>b[n].x) R++;
	for(int i=n;i>1;i--){
		add(-b[i].y+N);
		while(R<=n && -b[R].x+(o>=1)>b[i-1].x){
			ans+=(ll)b[R].v*ask(b[R].y-(o==2)+N);
			R++;
		}
	}
	add(-b[1].y+N);
	while(R<=n){
		ans+=(ll)b[R].v*ask(b[R].y-(o==2)+N);
		R++;
	}
	for(int i=1;i<=n;i++) add(-b[i].y+N,-1);
}
int main(){
	//freopen("sort.in","r",stdin);
	//freopen("sort.out","w",stdout);
	scanf("%d%d",&m,&n);
	for(int j=0;j<m;j++) for(int i=1;i<=n;i++) scanf("%d",&a[j][i]),sum=(sum+(ll)(n<<1)*a[j][i]);
	if(m==2){printf("%lld\n",sum);}
	if(m==3){
		Solve(0,1,2,0);
		Solve(1,0,2,1);
		Solve(2,0,1,2);
		ans<<=1;
		printf("%lld\n",ans);
	}
	if(m==4){
		Solve(0,1,2,0);Solve(1,0,2,1);Solve(2,0,1,2);
		Solve(0,1,3,0);Solve(1,0,3,1);Solve(3,0,1,2);
		Solve(0,2,3,0);Solve(2,0,3,1);Solve(3,0,2,2);
		Solve(1,2,3,0);Solve(2,1,3,1);Solve(3,1,2,2);
		ans<<=1;
		printf("%lld\n",(ans-sum)/2ll);
	}
	return 0;
}
/*
3 5
1 7 2 2 7
9 10 4 10 3
7 7 8 10 2
4 4
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
*/
```
提交的时候竟然拿到了 luogu 最优解？？

---

## 作者：_Diu_ (赞：13)

赛时降智 cdq 写挂了，来写一发题解纪念一下。

以下分享我的赛时思路。

我们一档一档部分分来考虑。

## $n\le 3000$

按题意模拟，直接暴力即可。

```cpp
void subtask_1(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int mx=-Inf,mn=Inf;
			for(int k=1;k<=m;k++)mx=max(mx,A[k][i]+A[k][j]),mn=min(mn,A[k][i]+A[k][j]);
			ans+=mx+mn;
		}
	}
	printf("%lld\n",ans);
	exit(0);
}
```

## $m=2$

我们发现，对于一对 $(i,j)$ 如果 $a_{1,i}+a_{1,j}\not= a_{2,i}+a_{2,j}$，那么必然一定是一大一小，每一对都会计算一次，否则两个算谁都无所谓，也拆成每一对都计算一次，所以答案全部加起来再乘以 $n\times2$，因为每一个位置会作为 $i$ $n$ 次，$j$ 也一样。

```cpp
void subtask_2(){
	int sum=0;
	for(int i=1;i<=m;i++)
		for(int x,j=1;j<=n;j++)
			scanf("%lld",&x),sum+=x;
	printf("%lld\n",sum*n*2);
	exit(0);
}
```

## $m=3$

我们先只考虑求 $\min$ 的部分，求 $max$ 的部分可以类似做出来。

我们考虑调换求和顺序，枚举一个 $k,i$，计算有多少个 $j$ 会使得 $a_{k,i}$ 在统计 $f(i,j)$ 的 $\min$ 部分被统计。

$$
Ans_{\min}=\sum_{k=1}^m\sum_{i=1}^na_{k,i}\sum_{j=1}^{n}[\forall l \not = k,a_{k,i}+a_{k+j}\le a_{l,i}+a_{l,j}]
$$

我们发现这样统计答案可能是错误的，因为如果有多个最小值的话，会重复统计。

所以我们分开来统计，对于一个 $k$，$1\le l<k$ 的部分去 $<$，$k<l\le m$ 的部分去 $\le$，避免计重。

$$
Ans_{\min}=\sum_{k=1}^m\sum_{i=1}^na_{k,i}\sum_{j=1}^{n}[\forall 1\le l<k,a_{k,i}+a_{k,j}< a_{l,i}+a_{l,j},\forall k<l\le m ,a_{k,i}+a_{k,j}\le a_{l,i}+a_{l,j}]
$$

这样答案就正确了。

我们对右边的式子进行移项（为了方便，这里统一取 $\le$）：

$$
a_{k,i}+a_{k,j}\le a_{l,i}+a_{l,j}
$$
$$
a_{k,i}-a_{l,i}\le a_{l,j}-a_{k,j}
$$

如果是 $<$，因为 $a$ 都是正整数，在右侧补一个 $-1$ 即可。

我们发现，左边的都和 $i$ 有关，右边的只和 $j$ 有关。

对于一个固定的 $k$，我们记 $A_{l,i}=a_{k,i}-a_{l+(l\ge k),i},B_{l_i}=a_{l+(l\ge k),i}-a_{k,i}-(l\ge k)$，

然后我们发现对于一个 $j$，如果它对 $i$ 有贡献，要求满足 $\forall 1\le l<m,A_{l,i}\le B_{l,j}$，发现是一个二维偏序，然后就可以树状数组或者双指针。

```cpp
struct cho{
	int a,b,c,w;
	bool operator<(const cho h)const{return a>h.a;}
}x[N];
struct becho{
	int a,b,c;
	bool operator<(const becho h)const{return a>h.a;}
}y[N];
int c[N<<2];
void add(int i,int x){++i;for(;i<N+N;c[i]+=x,i+=i&-i);}
int sum(int i){int s=0;++i;for(;i;s+=c[i],i-=i&-i);return s;}
void subtask_3(){
	for(int k=1;k<=m;k++){
//		printf("Min:%lld\n",k);
		for(int i=1;i<=n;i++){
			for(int l=1;l<k;l++)b[l]=A[l][i]-A[k][i]-1,a[l]=-b[l]-1;
			for(int l=k;l<m;l++)b[l]=A[l+1][i]-A[k][i],a[l]=-b[l];
			x[i]={a[1]+N,a[2]+N,0,A[k][i]};
			y[i]={b[1]+N,b[2]+N,0};
//			printf("%lld %lld %lld %lld %lld\n",i,a[1],a[2],b[1],b[2]);
//			if(a[1]<=b[1]&&a[2]<=b[2])ans+=A[k][i],printf("Del:%lld\n",A[k][i]);
		}
		sort(x+1,x+n+1),sort(y+1,y+n+1);
		int p=1;
		for(int i=1;i<=n;i++){
			while(p<=n&&y[p].a>=x[i].a)add(y[p].b,1),++p;
			ans+=x[i].w*(p-1-sum(x[i].b-1))*2;
//			printf("%lld %lld\n",x[i].w,(p-1-sum(x[i].b-1)));
		}
		for(int i=1;i<p;i++)add(y[i].b,-1);
//		printf("%lld\n",ans);
	}
//	printf("%lld\n",ans);
	for(int k=1;k<=m;k++){
		for(int i=1;i<=n;i++){
			for(int l=1;l<k;l++)b[l]=A[l][i]-A[k][i]+1,a[l]=-b[l]+1;
			for(int l=k;l<m;l++)b[l]=A[l+1][i]-A[k][i],a[l]=-b[l];
			x[i]={a[1]+N,a[2]+N,0,A[k][i]};
			y[i]={b[1]+N,b[2]+N,0};
//			if(a[1]>=b[1]&&a[2]>=b[2])ans+=A[k][i];
		}
		sort(x+1,x+n+1),sort(y+1,y+n+1);
		int p=n;
		for(int i=n;i>=1;i--){
			while(p&&y[p].a<=x[i].a)add(y[p].b,1),--p;
			ans+=x[i].w*sum(x[i].b)*2;
		}
		for(int i=n;i>p;i--)add(y[i].b,-1);
	}
	printf("%lld\n",ans);
	exit(0);
}
```

结合前面，一共获得 `50pts`，也是我赛时写出来的。

## $m=4$

我们发现，前面 $m=3$ 的思路扩展到 $m=4$ 也是用，变成了三维偏序，直接上 cdq 分治就过了。

具体一点，把每个点拆成两个，一个存三个 $A$ 和 $a_{k,i}$ 的值，另一个存 $B$，一个负责统计贡献，另一个负责给别的点贡献。

对于 $\max$ 也差不多。

但是考场降智不知为啥 cdq 分治都能写挂。

```cpp
struct cow{
	int op,a,b,c,w;
}s[N<<1],t[N<<1];
bool cmp(cow a,cow b){
	if(a.a^b.a)return a.a>b.a;
	return a.op;
}
bool cmp2(cow a,cow b){
	if(a.a^b.a)return a.a<b.a;
	return a.op;
}
void cdq(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	int p=l,pp=l-1,tot=0;
	for(int i=mid+1;i<=r;i++){
		while(p<=mid&&s[p].b>=s[i].b){
			if(s[p].op)add(s[p].c,1),++tot;
			t[++pp]=s[p++];
		}
		t[++pp]=s[i];
		if(!s[i].op)ans+=(tot-sum(s[i].c-1))*s[i].w;
	}
	for(int i=l;i<p;i++)if(s[i].op)add(s[i].c,-1);
	for(;p<=mid;)t[++pp]=s[p++];
	for(int i=l;i<=r;i++)s[i]=t[i];
}
void cdq2(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	cdq2(l,mid),cdq2(mid+1,r);
	int p=l,pp=l-1;
	for(int i=mid+1;i<=r;i++){
		while(p<=mid&&s[p].b<=s[i].b){
			if(s[p].op)add(s[p].c,1);
			t[++pp]=s[p++];
		}
		t[++pp]=s[i];
		if(!s[i].op)ans+=sum(s[i].c)*s[i].w;
	}
	for(int i=l;i<p;i++)if(s[i].op)add(s[i].c,-1);
	for(;p<=mid;)t[++pp]=s[p++];
	for(int i=l;i<=r;i++)s[i]=t[i];
}
void subtask_4(){
	for(int k=1;k<=m;k++){
		for(int i=1;i<=n;i++){
			for(int l=1;l<k;l++)b[l]=A[l][i]-A[k][i]-1,a[l]=-b[l]-1;
			for(int l=k;l<m;l++)b[l]=A[l+1][i]-A[k][i],a[l]=-b[l];
			s[i]={0,a[1]+N,a[2]+N,a[3]+N,A[k][i]};
			s[i+n]={1,b[1]+N,b[2]+N,b[3]+N,0};
		}
		sort(s+1,s+2*n+1,cmp);
		cdq(1,2*n);
	}
	for(int k=1;k<=m;k++){
		for(int i=1;i<=n;i++){
			for(int l=1;l<k;l++)b[l]=A[l][i]-A[k][i]+1,a[l]=-b[l]+1;
			for(int l=k;l<m;l++)b[l]=A[l+1][i]-A[k][i],a[l]=-b[l];
			s[i]={0,a[1]+N,a[2]+N,a[3]+N,A[k][i]};
			s[i+n]={1,b[1]+N,b[2]+N,b[3]+N,0};
		}
		sort(s+1,s+2*n+1,cmp2);
		cdq2(1,2*n);
	}
	printf("%lld\n",ans*2);
	exit(0);
}
```

## code

不完全完整的代码如下，因为大部分是赛时写的，有很多冗余操作，看看就好了。

~~另外所有点的答案输出全部留在上面忘拿下来了。~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int Inf=1e12;
int n,m,A[5][N],a[5],b[5],ans;
void subtask_2(){
	int sum=0;
	for(int i=1;i<=m;i++)
		for(int x,j=1;j<=n;j++)
			scanf("%lld",&x),sum+=x;
	exit(0);
}
struct cho{
	int a,b,c,w;
	bool operator<(const cho h)const{return a>h.a;}
}x[N];
struct becho{
	int a,b,c;
	bool operator<(const becho h)const{return a>h.a;}
}y[N];
int c[N<<2];
void add(int i,int x){++i;for(;i<N+N;c[i]+=x,i+=i&-i);}
int sum(int i){int s=0;++i;for(;i;s+=c[i],i-=i&-i);return s;}
void subtask_3(){
	for(int k=1;k<=m;k++){
//		printf("Min:%lld\n",k);
		for(int i=1;i<=n;i++){
			for(int l=1;l<k;l++)b[l]=A[l][i]-A[k][i]-1,a[l]=-b[l]-1;
			for(int l=k;l<m;l++)b[l]=A[l+1][i]-A[k][i],a[l]=-b[l];
			x[i]={a[1]+N,a[2]+N,0,A[k][i]};
			y[i]={b[1]+N,b[2]+N,0};
//			printf("%lld %lld %lld %lld %lld\n",i,a[1],a[2],b[1],b[2]);
//			if(a[1]<=b[1]&&a[2]<=b[2])ans+=A[k][i],printf("Del:%lld\n",A[k][i]);
		}
		sort(x+1,x+n+1),sort(y+1,y+n+1);
		int p=1;
		for(int i=1;i<=n;i++){
			while(p<=n&&y[p].a>=x[i].a)add(y[p].b,1),++p;
			ans+=x[i].w*(p-1-sum(x[i].b-1))*2;
//			printf("%lld %lld\n",x[i].w,(p-1-sum(x[i].b-1)));
		}
		for(int i=1;i<p;i++)add(y[i].b,-1);
//		printf("%lld\n",ans);
	}
//	printf("%lld\n",ans);
	for(int k=1;k<=m;k++){
		for(int i=1;i<=n;i++){
			for(int l=1;l<k;l++)b[l]=A[l][i]-A[k][i]+1,a[l]=-b[l]+1;
			for(int l=k;l<m;l++)b[l]=A[l+1][i]-A[k][i],a[l]=-b[l];
			x[i]={a[1]+N,a[2]+N,0,A[k][i]};
			y[i]={b[1]+N,b[2]+N,0};
//			if(a[1]>=b[1]&&a[2]>=b[2])ans+=A[k][i];
		}
		sort(x+1,x+n+1),sort(y+1,y+n+1);
		int p=n;
		for(int i=n;i>=1;i--){
			while(p&&y[p].a<=x[i].a)add(y[p].b,1),--p;
			ans+=x[i].w*sum(x[i].b)*2;
		}
		for(int i=n;i>p;i--)add(y[i].b,-1);
	}
	exit(0);
}
void subtask_1(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int mx=-Inf,mn=Inf;
			for(int k=1;k<=m;k++)mx=max(mx,A[k][i]+A[k][j]),mn=min(mn,A[k][i]+A[k][j]);
			ans+=mx+mn;
		}
	}
	exit(0);
}
struct cow{
	int op,a,b,c,w;
}s[N<<1],t[N<<1];
bool cmp(cow a,cow b){
	if(a.a^b.a)return a.a>b.a;
	return a.op;
}
bool cmp2(cow a,cow b){
	if(a.a^b.a)return a.a<b.a;
	return a.op;
}
void cdq(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	int p=l,pp=l-1,tot=0;
	for(int i=mid+1;i<=r;i++){
		while(p<=mid&&s[p].b>=s[i].b){
			if(s[p].op)add(s[p].c,1),++tot;
			t[++pp]=s[p++];
		}
		t[++pp]=s[i];
		if(!s[i].op)ans+=(tot-sum(s[i].c-1))*s[i].w;
	}
	for(int i=l;i<p;i++)if(s[i].op)add(s[i].c,-1);
	for(;p<=mid;)t[++pp]=s[p++];
	for(int i=l;i<=r;i++)s[i]=t[i];
}
void cdq2(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	cdq2(l,mid),cdq2(mid+1,r);
	int p=l,pp=l-1;
	for(int i=mid+1;i<=r;i++){
		while(p<=mid&&s[p].b<=s[i].b){
			if(s[p].op)add(s[p].c,1);
			t[++pp]=s[p++];
		}
		t[++pp]=s[i];
		if(!s[i].op)ans+=sum(s[i].c)*s[i].w;
	}
	for(int i=l;i<p;i++)if(s[i].op)add(s[i].c,-1);
	for(;p<=mid;)t[++pp]=s[p++];
	for(int i=l;i<=r;i++)s[i]=t[i];
}
void subtask_4(){
	for(int k=1;k<=m;k++){
		for(int i=1;i<=n;i++){
			for(int l=1;l<k;l++)b[l]=A[l][i]-A[k][i]-1,a[l]=-b[l]-1;
			for(int l=k;l<m;l++)b[l]=A[l+1][i]-A[k][i],a[l]=-b[l];
			s[i]={0,a[1]+N,a[2]+N,a[3]+N,A[k][i]};
			s[i+n]={1,b[1]+N,b[2]+N,b[3]+N,0};
		}
		sort(s+1,s+2*n+1,cmp);
		cdq(1,2*n);
	}
	for(int k=1;k<=m;k++){
		for(int i=1;i<=n;i++){
			for(int l=1;l<k;l++)b[l]=A[l][i]-A[k][i]+1,a[l]=-b[l]+1;
			for(int l=k;l<m;l++)b[l]=A[l+1][i]-A[k][i],a[l]=-b[l];
			s[i]={0,a[1]+N,a[2]+N,a[3]+N,A[k][i]};
			s[i+n]={1,b[1]+N,b[2]+N,b[3]+N,0};
		}
		sort(s+1,s+2*n+1,cmp2);
		cdq2(1,2*n);
	}
	exit(0);
}
signed main(){
	scanf("%lld%lld",&m,&n);
	if(m==2)subtask_2();
	for(int i=1;i<=m;i++)
		for(int x,j=1;j<=n;j++)scanf("%lld",&A[i][j]);
	if(m==3)subtask_3();
//	if(n<=3000)subtask_1();
	subtask_4();
}
```

---

## 作者：FjswYuzu (赞：11)

首先考虑 $m=2$，这个很好搞，因为 $f(i,j)$ 的 $\min$ 和 $\max$ 可以分别归到 $1,2$ 中的某一个，那么每对数会算 $2n$ 次。$m=2$ 的时候答案就是 $2n\sum a$。

然后考虑 $m=3$。我们对 $\min$ 和 $\max$ 分开算，并且发现我们将 $a$ 取反之后的 $\min$ 就是 $\max$，我们只讨论 $\min$ 就好了。我们假设 $a_{1,i} + a_{1,j} \leq \min(a_{2,i}+a_{2,j},a_{3,i}+a_{3,j})$。记 $A_i = a_{1,i} - a_{2,i},B_i = a_{1,i} - a_{3,i}$把这个拆成两个限制移项得到：

$$
\begin{cases}
A_j \leq -A_i\\

B_j \leq -B_i
\end{cases}
$$


将 $(A_j,B_j)$ 看成点，如果这个点在 $(-A_i,-B_i)$
 的左下角，那么就会产生 $a_{1,i} + a_{2,i}$ 的贡献。

那么这样就转化成了一个二维数点的问题，可以直接树状数组扫一遍。

当然有一个问题是这个会算重。我们对三个东西钦定一个顺序就好了。

最后考虑 $m=4$。这个时候我们不考虑 $\min,\max$ 分开算，而考虑 min-max 容斥。写出其基本形式：

$$
\min(S) = \sum_{\varnothing \neq T ⊆ S} (-1)^{|T|-1} \max(T)
$$

$$
\max(S) = \sum_{\varnothing \neq T ⊆ S} (-1)^{|T|-1} \min(T)
$$

两者相加，将右边的 $-\max(S)-\min(S)$ 移到等式左边。记 $P(S) = \max(S) + \min(S)$，可知：

$$
2P(S) = \sum_{\varnothing \neq T ⫋ S} (-1)^{|T|-1} P(T)
$$

当 $|T|=1$ 或 $|T|=2$ 的时候，这个问题是显然的。当 $|T|=3$ 的时候，这个问题被归到了 $m=3$ 的子问题，做 $4$ 次 $m=3$ 时的算法就好了。

时间复杂度 $O(mn\log n)$。有二倍常数。

```cpp
const LL UP=800004;
LL n,N,a[5][200005];
inline LL lowbit(LL x){return x&(-x);}
struct BinaryIndexedTree{
	LL tr[800005];
	void clear(){for(LL i=1;i<=UP;++i)	tr[i]=0;}
	void modify(LL x,LL v){for(LL i=x;i<=UP;i+=lowbit(i))	tr[i]+=v;}
	LL query(LL x){LL ans=0;for(LL i=x;i;i^=lowbit(i))	ans+=tr[i];return ans;}
}bit1,bit2;
struct node{
	LL v,p,t,d;
	node(){}
	node(LL V,LL P,LL T,LL D){v=V,p=P,t=T,d=D;}
	inline bool operator < (node ano) const {return v<ano.v || (v==ano.v && t>ano.t);}
}P[400005];
LL cnt;
const LL Cur=400000;
LL Solve(LL p,LL q,LL r)
{
	LL ans=0;
	bit1.clear(),bit2.clear(),cnt=0;
	for(LL i=1;i<=n;++i)
	{
		P[++cnt]=node(a[p][i]-a[q][i]+Cur,a[p][i]-a[r][i]+Cur,0,a[p][i]);
		P[++cnt]=node(a[q][i]-a[p][i]+Cur+1,a[r][i]-a[p][i]+Cur+1,i,0);
	}
	sort(P+1,P+1+cnt);
	for(LL i=1;i<=cnt;++i)
	{
		if(P[i].t)	ans+=a[p][P[i].t]*bit1.query(P[i].p-1)+bit2.query(P[i].p-1);
		else	bit1.modify(P[i].p,1),bit2.modify(P[i].p,P[i].d);
	}
	bit1.clear(),bit2.clear(),cnt=0;
	for(LL i=1;i<=n;++i)
	{
		P[++cnt]=node(a[q][i]-a[p][i]+Cur,a[q][i]-a[r][i]+Cur,0,a[q][i]);
		P[++cnt]=node(a[p][i]-a[q][i]+Cur,a[r][i]-a[q][i]+Cur+1,i,0);
	}
	sort(P+1,P+1+cnt);
	for(LL i=1;i<=cnt;++i)
	{
		if(P[i].t)	ans+=a[q][P[i].t]*bit1.query(P[i].p-1)+bit2.query(P[i].p-1);
		else	bit1.modify(P[i].p,1),bit2.modify(P[i].p,P[i].d);
	}
	bit1.clear(),bit2.clear(),cnt=0;
	for(LL i=1;i<=n;++i)
	{
		P[++cnt]=node(a[r][i]-a[p][i]+Cur,a[r][i]-a[q][i]+Cur,0,a[r][i]);
		P[++cnt]=node(a[p][i]-a[r][i]+Cur,a[q][i]-a[r][i]+Cur,i,0);
	}
	sort(P+1,P+1+cnt);
	for(LL i=1;i<=cnt;++i)
	{
		if(P[i].t)	ans+=a[r][P[i].t]*bit1.query(P[i].p-1)+bit2.query(P[i].p-1);
		else	bit1.modify(P[i].p,1),bit2.modify(P[i].p,P[i].d);
	}
	for(LL i=1;i<=N;++i)	for(LL j=1;j<=n;++j)	a[i][j]=-a[i][j];
	bit1.clear(),bit2.clear(),cnt=0;
	for(LL i=1;i<=n;++i)
	{
		P[++cnt]=node(a[p][i]-a[q][i]+Cur,a[p][i]-a[r][i]+Cur,0,a[p][i]);
		P[++cnt]=node(a[q][i]-a[p][i]+Cur+1,a[r][i]-a[p][i]+Cur+1,i,0);
	}
	sort(P+1,P+1+cnt);
	for(LL i=1;i<=cnt;++i)
	{
		if(P[i].t)	ans-=a[p][P[i].t]*bit1.query(P[i].p-1)+bit2.query(P[i].p-1);
		else	bit1.modify(P[i].p,1),bit2.modify(P[i].p,P[i].d);
	}
	bit1.clear(),bit2.clear(),cnt=0;
	for(LL i=1;i<=n;++i)
	{
		P[++cnt]=node(a[q][i]-a[p][i]+Cur,a[q][i]-a[r][i]+Cur,0,a[q][i]);
		P[++cnt]=node(a[p][i]-a[q][i]+Cur,a[r][i]-a[q][i]+Cur+1,i,0);
	}
	sort(P+1,P+1+cnt);
	for(LL i=1;i<=cnt;++i)
	{
		if(P[i].t)	ans-=a[q][P[i].t]*bit1.query(P[i].p-1)+bit2.query(P[i].p-1);
		else	bit1.modify(P[i].p,1),bit2.modify(P[i].p,P[i].d);
	}
	bit1.clear(),bit2.clear(),cnt=0;
	for(LL i=1;i<=n;++i)
	{
		P[++cnt]=node(a[r][i]-a[p][i]+Cur,a[r][i]-a[q][i]+Cur,0,a[r][i]);
		P[++cnt]=node(a[p][i]-a[r][i]+Cur,a[q][i]-a[r][i]+Cur,i,0);
	}
	sort(P+1,P+1+cnt);
	for(LL i=1;i<=cnt;++i)
	{
		if(P[i].t)	ans-=a[r][P[i].t]*bit1.query(P[i].p-1)+bit2.query(P[i].p-1);
		else	bit1.modify(P[i].p,1),bit2.modify(P[i].p,P[i].d);
	}
	for(LL i=1;i<=N;++i)	for(LL j=1;j<=n;++j)	a[i][j]=-a[i][j];
	return ans;
}
int main(){
//	freopen("sort.in","r",stdin);
//	freopen("sort.out","w",stdout);
	N=read(),n=read();
	for(LL i=1;i<=N;++i)	for(LL j=1;j<=n;++j)	a[i][j]=read();
	if(N==2)
	{
		LL sum=0;
		for(LL i=1;i<=n;++i)	sum+=a[1][i]+a[2][i];
		write(sum*n*2);
	}
	else if(N==3)	write(Solve(1,2,3));
	else
	{
		LL ans=Solve(1,2,3)+Solve(1,2,4)+Solve(1,3,4)+Solve(2,3,4); // +Ans(3)
		for(LL i=1;i<=N;++i)	for(LL j=1;j<=n;++j)	ans-=a[i][j]*2*n; // -Ans(2)+Ans(1) = -3Ans(1)+Ans(1)
		write(ans/2);
	}
	return 0;
}
```

---

## 作者：Sol1 (赞：7)

给个 $O(2^mn\log^{m-2-[2|m]} n)$ 的做法（在本题范围下为 $O(n\log n)$）。

首先 $m\leq 4$ 提示这个题大概率是要把 $m$ 放到指数上，或者直接分类讨论。

分类讨论难以下手，那么放到指数上会是什么？

暴力枚举大小关系？似乎没啥用，而且有 $8!=40320$ 种。再优化枚举似乎也很难处理这个加起来的 max。

尝试一下 min-max 容斥？记 $S_{i,j}=\{a_{k,i}+a_{k,j}|1\leq k\leq m\}$，推一下发现：

$$\max S_{i,j}+\min S_{i,j}=\sum_{S'\subseteq S_{i,j}}(-1)^{|S'|+1}\min S'+\min S_{i,j}$$

而在 $m=4$ 的时候子集求和的部分里面全集 $\min$ 的系数是 $-1$，与外面的 $+1$ 恰好消去，于是我们成功地把 $m=4$ 转化成了 $m=3$。但是并不能把 $m=3$ 转化成 $m=2$，因为此时全集 $\min$ 带 $+1$。

那么现在我们要求出子集 $\min$，怎么办？

- 我直接限制其他所有元素比其中一个大行不行？

发现限制是两个 $[a_{X,i}+a_{X,j}\geq a_{Y,i}+a_{Y,j}]$ 状物，移项变为 $[a_{X,i}-a_{Y,i}\geq a_{Y,j}-a_{X,j}]$。

- 这不就是二维数点？

恭喜你做完了……

具体来说，假设上面 min-max 枚举到的子集是 $\{X,Y,Z\}$，那么我们要求的是：

$$\sum_{i=1}^n\sum_{j=1}^n\min_{k\in\{X,Y,Z\}}a_{k,i}+a_{k,j}$$

拆开 $\min$，保证剩下的都比自己大：

$$\sum_{i=1}^n\sum_{j=1}^n\begin{aligned}&(a_{X,i}+a_{X,j})[a_{Y,i}+a_{Y,j}>a_{X,i}+a_{X,j}][a_{Z,i}+a_{Z,j}>a_{X,i}+a_{X,j}]\\+&(a_{Y,i}+a_{Y,j})[a_{X,i}+a_{X,j}\geq a_{Y,i}+a_{Y,j}][a_{Z,i}+a_{Z,j}>a_{Y,i}+a_{Y,j}]\\+&(a_{Z,i}+a_{Z,j})[a_{X,i}+a_{X,j}\geq a_{Z,i}+a_{Z,j}][a_{Y,i}+a_{Y,j}\geq a_{Z,i}+a_{Z,j}]\end{aligned}$$

（注意这里的 $\geq$ 和 $>$，这样可以保证不重不漏）

然后直接跑三遍二维数点即可。

两个元素是类似的，只不过限制少一个。把二维偏序换成序列二分即可。

一个元素直接算即可。

$\min$ 变成 $\max$ 只需要把所有元素取相反数即可。

然后就都能做了，总复杂度 $O(2^mn\log^{m-2-[2|m]}n)$，因为 $m$ 是偶数的时候可以用 min-max 折掉一维限制，代价是要枚举子集。

感觉这题其实是一个处理一个 $\min/\max$ 的新思路，类似于计数题的拆贡献。我认为计数题拆贡献本质是这样：

需要计算

$$\sum_{x\in S}\sum_{y\in T}[(x,y)\text{ satisfies some condition}]$$

而且有 $|T|\ll |S|$，这时可以考虑交换求和顺序：

$$\sum_{y\in T}\sum_{x\in S}[(x,y)\text{ satisfies some condition}]$$

然后对于固定的 $y$，如果 $\sum_{x\in S}[(x,y)\text{ satisfies some condition}]$ 可以快速计算，那么就做完了。

这题是类似的，区别是计数题中一般 $|T|=O(\operatorname{poly}(n))$，而 $|S|$ 是指数级；这题中 $|S|$ 是 $O(n^2)$ 的，但是 $|T|$ 是一个很小的常数 $4$。但是都可以利用这个思想来优化。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

int n, m;
long long a[5][200005], c[2][1000005], pre[200005];
pair <long long, int> tmp[200005];

struct Point {
	int x, y, tp;
	long long w;
	Point() {}
	Point(int x, int y, int tp, long long w) : x(x), y(y), tp(tp), w(w) {}
	bool operator < (const Point& b) const {
		if (x != b.x) return x < b.x;
		return tp < b.tp;
	}
};
Point p[1000005];
int psz, py[1000005], ysz;

inline void Read() {
	m = qread(); n = qread();
	for (int i = 1;i <= m;i++) {
		for (int j = 1;j <= n;j++) a[i][j] = qread();
	}
}

inline long long Work2(int X, int Y) {
	long long ans = 0;
	for (int i = 1;i <= n;i++) tmp[i] = make_pair(a[X][i] - a[Y][i], i);
	sort(tmp + 1, tmp + n + 1);
	for (int i = 1;i <= n;i++) {
		pre[i] = pre[i - 1] + a[X][tmp[i].second];
	}
	for (int i = 1;i <= n;i++) {
		int idx = lower_bound(tmp + 1, tmp + n + 1, make_pair(a[Y][i] - a[X][i], 0)) - tmp - 1;
		ans += a[X][i] * idx + pre[idx];
	}
	
	swap(X, Y);
	for (int i = 1;i <= n;i++) tmp[i] = make_pair(a[X][i] - a[Y][i], i);
	sort(tmp + 1, tmp + n + 1);
	for (int i = 1;i <= n;i++) {
		pre[i] = pre[i - 1] + a[X][tmp[i].second];
	}
	for (int i = 1;i <= n;i++) {
		int idx = upper_bound(tmp + 1, tmp + n + 1, make_pair(a[Y][i] - a[X][i], 0x3f3f3f3f)) - tmp - 1;
		ans += a[X][i] * idx + pre[idx];
	}
	return ans;
}

inline int Lowbit(int x) {
	return x & -x;
}

inline void Update(int k, int i, long long x) {
	for (int j = i;j <= ysz;j += Lowbit(j)) c[k][j] += x;
}

inline long long Query(int k, int i) {
	long long ans = 0;
	for (int j = i;j >= 1;j -= Lowbit(j)) ans += c[k][j];
	return ans;
}

inline long long Count() {
	long long ans = 0;
	sort(p + 1, p + psz + 1);
	for (int i = 1;i <= psz;i++) py[i] = p[i].y;
	sort(py + 1, py + psz + 1);
	ysz = unique(py + 1, py + psz + 1) - py - 1;
	for (int i = 1;i <= psz;i++) p[i].y = lower_bound(py + 1, py + ysz + 1, p[i].y) - py;
	memset(c, 0, sizeof(c));
	for (int i = 1;i <= psz;i++) {
		if (p[i].tp == 0) {
			Update(0, p[i].y, 1);
			Update(1, p[i].y, p[i].w);
		} else ans += p[i].w * Query(0, p[i].y) + Query(1, p[i].y);
	}
	return ans;
}

inline long long Work3(int X, int Y, int Z) {
	long long ans = 0;

	psz = 0;
	for (int i = 1;i <= n;i++) {
		p[++psz] = Point(a[X][i] - a[Y][i], a[X][i] - a[Z][i], 0, a[X][i]);
		p[++psz] = Point(a[Y][i] - a[X][i] - 1, a[Z][i] - a[X][i] - 1, 1, a[X][i]);
	}
	ans += Count();

	psz = 0;
	for (int i = 1;i <= n;i++) {
		p[++psz] = Point(a[Y][i] - a[X][i], a[Y][i] - a[Z][i], 0, a[Y][i]);
		p[++psz] = Point(a[X][i] - a[Y][i], a[Z][i] - a[Y][i] - 1, 1, a[Y][i]);
	}
	ans += Count();

	psz = 0;
	for (int i = 1;i <= n;i++) {
		p[++psz] = Point(a[Z][i] - a[X][i], a[Z][i] - a[Y][i], 0, a[Z][i]);
		p[++psz] = Point(a[X][i] - a[Z][i], a[Y][i] - a[Z][i], 1, a[Z][i]);
	}
	ans += Count();

	return ans;
}

inline void Solve() {
	if (m == 2) {
		long long ans = 0;
		for (int i = 1;i <= m;i++) {
			for (int j = 1;j <= n;j++) ans += 2ll * a[i][j] * n;
		}
		cout << ans << endl;
		return;
	}
	if (m == 3) {
		long long ans = Work3(1, 2, 3);
		for (int i = 1;i <= m;i++) {
			for (int j = 1;j <= n;j++) a[i][j] = -a[i][j];
		}
		ans -= Work3(1, 2, 3);
		cout << ans << endl;
		return;
	}
	if (m == 4) {
		long long ans = Work3(1, 2, 3) + Work3(1, 2, 4) + Work3(1, 3, 4) + Work3(2, 3, 4)
					  - Work2(1, 2) - Work2(1, 3) - Work2(1, 4) - Work2(2, 3) - Work2(2, 4) - Work2(3, 4);
		for (int i = 1;i <= m;i++) {
			for (int j = 1;j <= n;j++) ans += 2ll * a[i][j] * n;
		}
		cout << ans << endl;
	}
}

int main() {
	Read();
	Solve();
	#ifdef CFA_44
	while (1) getchar();
	#endif
	return 0;
}
```







---

## 作者：_lbw_ (赞：4)

这是一篇数学题解，不是一篇数据结构题解。

题意：求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n\min\limits_{k=1}^m(a_{k,i}+a_{k,j})+\max\limits_{k=1}^m(a_{k,i}+a_{k,j})$

记 $f(*a,*b)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n\min(a_i+a_j,b_i+b_j)$

$f(*a,*b,*c)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n\min(a_i+a_j,b_i+b_j,c_i+c_j)$

$f(*a,*b,*c,*d)$ 同理，先考虑 $m=3$ 的情况。

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\min\limits_{k=1}^m(a_{k,i}+a_{k,j})+\max\limits_{k=1}^m(a_{k,i}+a_{k,j})$$

$$=\sum\limits_{i=1}^n\sum\limits_{j=1}^n\min\limits_{k=1}^m(a_{k,i}+a_{k,j})+\sum\limits_{i=1}^n\sum\limits_{j=1}^n\max\limits_{k=1}^m(a_{k,i}+a_{k,j})$$

$$f(a_1,a_2,a_3)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n\min\limits_{k=1}^m(a_{k,i}+a_{k,j})$$

$$f(*a,*b,*c)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n\min(a_i+a_j,b_i+b_j,c_i+c_j)$$

$$f(*a,*b,*c)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n\min(a_i+a_j,b_i+b_j,c_i+c_j)$$

枚举 $a$ 为最小值的情况，剩下两种同理

$$=\sum\limits_{i=1}^na_i\sum\limits_{j=1}^n[a_i+a_j=\min(a_i+a_j,b_i+b_j,c_i+c_j)]$$


$$=\sum\limits_{i=1}^na_i\sum\limits_{j=1}^n[a_i+a_j\leq b_i+b_j,a_i+a_j\leq c_i+c_j]$$

$$=\sum\limits_{i=1}^na_i\sum\limits_{j=1}^n[a_j-b_j\leq b_i-a_i,a_j-c_j\leq c_i-a_i]$$

于是便变成了【模板】二维数点

然后考虑 $m=4$ 的，容易发现可以用三维数点，但是还有另一种 min-max 容斥做法。

$\max(S)=\sum\limits_{T\subseteq S}(-1)^{|T|+1}\min(T)$
 
$\min(a_1,a_2,a_3,a_4)+\max(a_1,a_2,a_3,a_4)=$

记 $S_k=\sum\limits_{T\subseteq S}(-1)^{|T|+1}\min(T)[|T|=k]$

$\min(a_1,a_2,a_3,a_4)+\max(a_1,a_2,a_3,a_4)=S_4-S_4+S_3-S_2+S_1=S_3+S_1-S_2$

于是乱搞一波，变成求 $S_3,S_2,S_1$ ，于是求 $4$ 次二维数点，$6$ 次一维数点，$4$ 次零维数点

```cpp
ll n,m,a[5][maxn],cnt,ans[maxn];
struct node{ll x,y,id;}qwq[5*maxn];ll Ans;
struct BIT{
	ll c[maxn*5],ans;IV clear(){mem(c,0);}
	IV add(ll pos,ll val){for(;pos<=3*MAX;pos+=pos&-pos)c[pos]+=val;}
	I query(ll pos){ans=0;for(;pos;pos-=pos&-pos)ans+=c[pos];return ans;}
}bit;
IV solve(){
	sort(qwq+1,qwq+1+cnt,[](node X,node Y){return X.x==Y.x?X.id<Y.id:X.x<Y.x;});bit.clear();
	F(i,1,cnt)if(qwq[i].id<1||qwq[i].id>n)bit.add(qwq[i].y,1);else ans[qwq[i].id]=bit.query(qwq[i].y);
}
IV maxget(ll*x,ll*y,ll*z,ll mul,ll tp1,ll tp2){
	cnt=0;F(i,1,n){
		qwq[++cnt]=node{x[i]-y[i]+MAX-tp1,x[i]-z[i]+MAX-tp2,i};
		qwq[++cnt]=node{y[i]-x[i]+MAX,z[i]-x[i]+MAX,0};
	}
//	F(i,1,cnt)cout<<qwq[i].x<<' '<<qwq[i].y<<' '<<qwq[i].id<<endl;
	solve();F(i,1,n)Ans+=mul*ans[i]*x[i];//,cout<<ans[i]<<" ";puts("");
}
IV minget(ll*x,ll*y,ll*z,ll mul,ll tp1,ll tp2){
	cnt=0;F(i,1,n){
		qwq[++cnt]=node{y[i]-x[i]+MAX-tp1,z[i]-x[i]+MAX-tp2,i};
		qwq[++cnt]=node{x[i]-y[i]+MAX,x[i]-z[i]+MAX,0};
	}
//	F(i,1,cnt)cout<<qwq[i].x<<' '<<qwq[i].y<<' '<<qwq[i].id<<endl;
	solve();F(i,1,n)Ans+=mul*ans[i]*x[i];//,cout<<ans[i]<<" ";puts("");
}
struct Node{ll x,id;}q[maxn*5];
IV solve2(){ll sum=0;
	sort(q+1,q+1+cnt,[](Node X,Node Y){return X.x==Y.x?X.id<Y.id:X.x<Y.x;});
	F(i,1,cnt)if(q[i].id<1||q[i].id>n)sum++;else ans[q[i].id]=sum;//,cout<<qwq[i].id<<' '<<sum<<endl;
}
IV minget(ll*x,ll*y,ll mul,ll tp1){
	cnt=0;F(i,1,n){
		q[++cnt]=Node{y[i]-x[i]+MAX-tp1,i};
		q[++cnt]=Node{x[i]-y[i]+MAX,0};
	}
	solve2();F(i,1,n)Ans+=mul*ans[i]*x[i];
}
IV solvemin(ll*x,ll*y,ll mul){
	minget(x,y,mul,0);
	minget(y,x,mul,1);
}
IV solvemax(ll*x,ll*y,ll*z,ll mul){
	maxget(x,y,z,mul,0,0);
	maxget(y,x,z,mul,1,0);
	maxget(z,x,y,mul,1,1);
}
IV solvemin(ll*x,ll*y,ll*z,ll mul){
	minget(x,y,z,mul,0,0);
	minget(y,x,z,mul,1,0);
	minget(z,x,y,mul,1,1);
}
int main(){
//	freopen("1.in","r",stdin);
	m=read();n=read();ll S=0;
	F(i,1,m)F(j,1,n)a[i][j]=read(),S+=a[i][j];
	if(m==2){
		F(k,1,n)F(i,1,m)Ans+=a[i][k]*n;
		return cout<<Ans*2,0;
	}
	if(m==3){
		solvemax(a[1],a[2],a[3],1);
		solvemin(a[1],a[2],a[3],1);
		return cout<<Ans*2,0;
	}
	if(m==4){Ans=S*n;
		solvemin(a[1],a[2],-1);
		solvemin(a[1],a[3],-1);
		solvemin(a[1],a[4],-1);
		solvemin(a[2],a[3],-1);
		solvemin(a[2],a[4],-1);
		solvemin(a[3],a[4],-1);
		solvemin(a[1],a[2],a[3],1);
		solvemin(a[1],a[2],a[4],1);
		solvemin(a[1],a[3],a[4],1);
		solvemin(a[2],a[3],a[4],1);
		return cout<<Ans*2,0;
	}
	return 0;
}
```




---

## 作者：vectorwyx (赞：4)

# 题解 P8253 [NOI Online 2022 提高组] 如何正确地排序

看题 10min 后想出的做法，然而把时限看成了 1s 以为它卡不过去，写了个暴力然后摆烂了/youl

首先把 min 和 max 拆开算，而 max 的贡献可以通过把所有数取反再算一遍 min 得到。接下来默认求 min 的贡献。

先来考虑 $m=2$ 时怎么算。把上下两行看做不同的两个一维数组 $a,b$。首先对于 $a$ 的每个位置 $a_i$，考虑哪些位置 $j$ 满足 $a_{i}+a_{j}$ 是 $a_{i}+a_{j},b_i+b_j$ 中的最小值，我们需要求这样的 $j$ 有多少个以及满足条件的 $j$ 对应 $a_j$ 的和 。$a_i+a_j\le b_i+b_j\iff a_j-b_j\le b_i-a_i$，如果把每一列看做一个点，$a_j-b_j$ 看做坐标，那么这是一个一维偏序。而 $b$ 中的每个位置的贡献也是一个一维偏序的形式。

上述做法显然可以推广到 $m>2$ 的场景。同样是考虑 $(i,j)$ 会与同行的哪些位置 $(i,k)$ 产生贡献，限制是 $a_{i,j}\le a_{1,j}+a_{1,k},……,a_{m,j}+a_{m,k}$，有一项是与自己比较的可以去掉，剩下的限制稍微转化一下就是一个 $m-1$ 维偏序。由于 $m\le 4$，所以只需要套层 cdq。复杂度为 $O(mn\log^2n)$。两个 log 分别是 cdq 和树状数组，所以常数够小，在 infoj 和洛谷都跑了不到 2.5s。

具体实现还有些细节，比如为了避免 $a_{i,j}+a_{i,k}$ 与其它值相同时最小值贡献多次，需要钦定值相同时行编号小的更小。

代码如下：

```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define lbit(x) (x&(-x))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){int ch=getchar(),x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e5+5,inf=1e9;
ll ans;
struct Point{
	int x,y,z,v,qwq;
	void out(){printf("(%d,%d,%d) %d\n",x,y,z,v);} 
	Point(){x=y=z=v=0;} 
	Point(int a,int b,int c,int d,int e=0){x=a,y=b,z=c,v=d,qwq=e;} 
};
bool operator<(Point &x,Point &y){
	if(x.x!=y.x) return x.x<y.x;
	return x.v<y.v;
}
struct ThreeD{
	Point P[N<<1]; 
	int m=0,V=0,tmp[N*6],trash[N],top,tr2[N*6];
	ll tr[N*6];
	void upd(int x,int k){
		//printf("upd(%d,%d)\n",x,k);
		while(x<=V){tr[x]+=k,tr2[x]+=k<0?-1:1;x+=lbit(x);}
	}	
	pair<ll,int> ask(int x){
		pair<ll,int> ret=mk(0,0);//printf("ask(%d) ",x);
		while(x){ret.fi+=tr[x],ret.se+=tr2[x];x-=lbit(x);}
		//printf("%lld,%d\n",ret.fi,ret.se);
		return ret;
	} 
	//static auto cmp=[](Point &x,Point &y){return x.y<y.y;};
	static bool cmp(const Point &x,const Point &y){return x.y<y.y;} 

	void ins(int x,int y,int z,int num,int qq){P[++m]=Point(x,y,z,num,qq);}//printf("ins(%d,%d,%d,%d)\n",x,y,z,num);} 
	void cdq(int l,int r){ 
		if(l==r) return;
		int mid=(l+r)>>1;
		cdq(l,mid);
		cdq(mid+1,r);
		//printf("cdq(%d,%d)\n",l,r);
		int id=l-1;
		fo(i,mid+1,r) if(P[i].v==inf){
			while(id<mid&&P[id+1].y<=P[i].y){
				++id;
				if(P[id].v<inf) upd(P[id].z,P[id].v);
			}
			pair<ll,int> qaq=ask(P[i].z);
			//printf("ans=%lld,",ans);
			//printf("qaq=(%lld,%d)",qaq.fi,qaq.se);
			ans+=qaq.fi+(ll)qaq.se*P[i].qwq;
		//	printf("ans=%lld\n",ans);
		}
		fo(i,l,id) if(P[i].v<inf) upd(P[i].z,-P[i].v);
		inplace_merge(P+l,P+mid+1,P+r+1,cmp);
	}
	
	void rank_(int &x){x=lower_bound(tmp+1,tmp+1+V,x)-tmp;} 
	void solve(){
		//fo(i,1,m) tmp[++V]=P[i].x,tmp[++V]=P[i].y,tmp[++V]=P[i].z;
		//puts("solve()");fo(i,1,m) P[i].out();
		fo(i,1,m) tmp[i]=P[i].z;V=m;
		sort(tmp+1,tmp+1+V);V=unique(tmp+1,tmp+1+V)-tmp-1;
		//fo(i,1,m) rank_(P[i].x),rank_(P[i].y),rank_(P[i].z);
		//out(tmp,1,V);
		fo(i,1,m) rank_(P[i].z);
		//fo(i,1,m) P[i].out();
		sort(P+1,P+1+m);
		cdq(1,m);
	}
}wyx[4];
int a[5][N],n,m;

void solve(){
	fo(i,0,3) wyx[i].m=0;
	fo(i,1,n)
		fo(j,1,m){
			int tmp[3]={0},id=0;
			fo(k,1,n) if(k!=i) tmp[id++]=a[k][j]-a[i][j];
			fo(k,0,i-2) tmp[k]--;
			//printf("(%d,%d) ",i,j);out(tmp,0,3);
			wyx[i-1].ins(tmp[0],tmp[1],tmp[2],inf,abs(a[i][j]));//插入 
			fo(k,0,i-2) tmp[k]++;
			wyx[i-1].ins(-tmp[0],-tmp[1],-tmp[2],abs(a[i][j]),0);
		}
	fo(i,0,n-1) wyx[i].solve();
	//printf("ans=%lld\n",ans);
}

signed main(){
	cin>>n>>m;
	fo(i,1,n) fo(j,1,m) a[i][j]=read();
	solve();
	fo(i,1,n) fo(j,1,m) a[i][j]*=-1;
	solve();
	cout<<ans;
	return 0;
}
/*
-------------------------------------------------
*/
```



---

## 作者：grass8cow (赞：3)

#### case1：m=2

发现 $max(a,b)+min(a,b)=a+b$ ，所以记所有数和为 $S$ ，答案就是 $2nS$ 。

但也可以 sort+前缀和 。

#### case2: m=3

以求 $max(a_i+a_j,b_i+b_j,c_i+c_j)$ 的和为例。

分别讨论谁最大，比如 $a_i+a_j$ 最大时要满足

$b_i+b_j\le a_i+a_j,c_i+c_j\le a_i+a_j$

转换一下 $b_i-a_i\le a_j-b_j,c_i-a_i\le a_j-c_j$

发现就是个二维数点。 sort+BIT 搞搞就行了。

#### case3:m=4

可以直接三维数点。

但我们把 $min(a_i+a_j,b_i+b_j,c_i+c_j,d_i+d_j)$ 用 $min-max$ 容斥弄开，发现其中一项是 $-max(a_i+a_j,b_i+b_j,c_i+c_j,d_i+d_j)$ ，刚好和后面抵消了。剩下的项用 $m=2,m=3$ 时的方法算一下就好了。

所以是 $O(n\log n)$ 乘上一些常数。

赛时 $code$ :

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int I=200001;
int m,n,a[4][201000];
struct qq{int x,y;}p[200100];
bool cmp(qq a,qq b){return a.x-a.y<b.x-b.y;}
struct BIT{
	ll tr[400100];
	inline ll ask(int x){ll s=0;for(;x;x-=(x&-x))s+=tr[x];return s;}
	inline void add(int x,ll z){for(;x<=400002;x+=(x&-x))tr[x]+=z;}
	inline void clear(){memset(tr,0,sizeof(tr));}
}T1,T2;
ll qzx[201000],qzy[200100]; 
ll sol2(int p1,int p2){
	ll an=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)an+=max(a[p1][i]+a[p1][j],a[p2][i]+a[p2][j]);
	for(int i=1;i<=n;i++)p[i]=(qq){a[p1][i],a[p2][i]};
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++)qzx[i]=qzx[i-1]+p[i].x,qzy[i]=qzy[i-1]+p[i].y;
	ll ans=0;int R=n;ll sp=0;
	for(int i=1;i<=n;i++){
		while(R&&p[R].x-p[R].y+p[i].x-p[i].y>=0)R--;
		ans+=1ll*(n-R)*p[i].x+1ll*R*p[i].y+qzy[R]-qzx[R]+qzx[n];
	}
	return ans;
}
struct node{int x,y,t,z;}q[400100];
int cn;
bool cmp2(node a,node b){
	if(a.x!=b.x)return a.x<b.x;
	if(a.y!=b.y)return a.y<b.y;
	return a.t>b.t;
}
ll KOT(){
	sort(q+1,q+cn+1,cmp2);
	T1.clear(),T2.clear();ll ans=0;
	for(int i=1;i<=cn;i++){
		if(!q[i].t)ans+=T1.ask(q[i].y+I)*q[i].z+T2.ask(q[i].y+I);
		else T1.add(q[i].y+I,1ll),T2.add(q[i].y+I,q[i].z);
	}
	return ans;
}
ll sol3(int p1,int p2,int p3){
	ll an=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)an+=max(max(a[p1][i]+a[p1][j],a[p2][i]+a[p2][j]),a[p3][i]+a[p3][j]);
	cn=0;
	for(int i=1;i<=n;i++){
		int x=a[p1][i],y=a[p2][i],z=a[p3][i];
		q[++cn]=(node){x-y,x-z,0,x};
		q[++cn]=(node){y-x,z-x,1,x};
	}
	ll ans=KOT();
	cn=0;
	for(int i=1;i<=n;i++){
		int x=a[p1][i],y=a[p2][i],z=a[p3][i];
		q[++cn]=(node){y-x,y-z,0,y};
		q[++cn]=(node){x-y+1,z-y,1,y};
	}
	ans+=KOT();
	cn=0;
	for(int i=1;i<=n;i++){
		int x=a[p1][i],y=a[p2][i],z=a[p3][i];
		q[++cn]=(node){z-x,z-y,0,z};
		q[++cn]=(node){x-z+1,y-z+1,1,z};
	}
	ans+=KOT();
	return ans;
}
int main(){
	cin>>m>>n;ll S=0;
	for(int i=0;i<m;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]),S+=a[i][j];
	if(m==2)return printf("%lld",S*n*2),0;
	if(m==3){
		ll ans=S*n*2;
		//a+b+c-max(a,b)-max(b,c)-max(a,c)+2*max(a,b,c)
		ans-=sol2(0,1)+sol2(1,2)+sol2(0,2);ans+=sol3(0,1,2)*2;
		printf("%lld",ans);
		return 0;
	}
	//a+b+c+d-max(a,b)-……+max(a,b,c)+max(b,c,d)+max(a,c,d)+max(a,b,d) 
	ll ans=S*n*2;
	for(int i=0;i<4;i++)for(int j=i+1;j<4;j++)ans-=sol2(i,j);
	ans+=sol3(0,1,2),ans+=sol3(0,1,3),ans+=sol3(0,2,3),ans+=sol3(1,2,3);
	return printf("%lld",ans),0;
}
```


---

## 作者：黑影洞人 (赞：2)

不得不说，这确实是一道好题。

第一眼看到以为是 ST 表，看了题解后发现实际上这题是一道三维偏序。

本题解可以算是对 HikariS 大佬题解的补充。

先考虑 $max$ 的情况：

考虑计算 $a_{i,j}$ 对答案的贡献。

$a_{i,j}$ 对答案有贡献，当且仅当满足以下柿子：

$$ a_{t,j}+a_{t,k}\le a_{i,j}+a_{i,k} (2\le t\le 4,t\not= i)$$

很显然，这是一个三维偏序问题。

珂以转化成四组三维偏序的形式：

$$\begin{cases} 
	a_{2,j}+a_{2,k}\le a_{1,j}+a_{1,k} \\ 
	a_{3,j}+a_{3,k}\le a_{1,j}+a_{1,k} \\ 
   a_{4,j}+a_{4,k}\le a_{1,j}+a_{1,k} \\
\end{cases}
$$  
$$\begin{cases} 
   a_{1,j}+a_{1,k}< a_{2,j}+a_{2,k} \\ 
	a_{3,j}+a_{3,k}\le a_{2,j}+a_{2,k} \\ 
   a_{4,j}+a_{4,k}\le a_{2,j}+a_{2,k} \\ 
 \end{cases}
$$  
$$\begin{cases} 
   a_{1,j}+a_{1,k}< a_{3,j}+a_{3,k} \\ 
	a_{2,j}+a_{2,k}< a_{3,j}+a_{3,k} \\ 
   a_{4,j}+a_{4,k}\le a_{3,j}+a_{3,k} \\ 
 \end{cases}
$$  
$$\begin{cases} 
   a_{1,j}+a_{1,k}< a_{4,j}+a_{4,k} \\ 
	a_{2,j}+a_{2,k}< a_{4,j}+a_{4,k} \\ 
   a_{3,j}+a_{3,k}< a_{4,j}+a_{4,k} \\ 
\end{cases}
$$

我们为了避免重复，要将编号小的放在前面，这也就解释了为什么在第 $2,3,4$ 组三维偏序里出现了小于号，这相等情况之前意见计算过一次，所以不用重复计算了。

但是这里的柿子 $j,k$ 并不是一组的，而是两组的，我们要稍微转化一下：

$$\begin{cases} 
	a_{2,j}-a_{1,j}\le a_{1,k}-a_{2,k} \\ 
	a_{3,j}-a_{1,j}\le a_{1,k}-a_{3,k} \\ 
   a_{4,j}-a_{1,j}\le a_{1,k}-a_{4,k} \\
\end{cases}
$$  
$$\begin{cases} 
   a_{1,j}-a_{2,j}< a_{2,k}-a_{1,k} \\ 
	a_{3,j}-a_{2,j}\le a_{2,k}-a_{3,k} \\ 
   a_{4,j}-a_{2,j}\le a_{2,k}-a_{4,k} \\
 \end{cases}
$$  
$$\begin{cases} 
   a_{1,j}-a_{3,j}< a_{3,k}-a_{1,k} \\ 
	a_{2,j}-a_{3,j}< a_{3,k}-a_{2,k} \\ 
   a_{4,j}-a_{3,j}\le a_{3,k}-a_{4,k} \\ 
 \end{cases}
$$  
$$\begin{cases} 
   a_{1,j}-a_{4,j}< a_{4,k}-a_{1,k} \\ 
	a_{2,j}-a_{4,j}< a_{4,k}-a_{2,k} \\ 
   a_{3,j}-a_{4,j}< a_{4,k}-a_{3,k} \\ 
\end{cases}
$$

现在我们保证了不等号一边的第二元坐标值一样了，剩下的操作当然就是无脑的三维偏序。

有人会问 $2$ 维偏序怎么办 ，还有 $1$ 维的怎么办？

我们强行令多处来的维度为一个极大或极小值即可。

这是构造三维偏序的代码

```cpp
int solve(){//按照我们上面的不等式进行构造
	int res=0;cnt=0;
	for(int i=1;i<=n;i++){
		q[++cnt]={w[1][i]-w[2][i],w[1][i]-w[3][i],w[1][i]-w[4][i],0,1};
		q[++cnt]={w[2][i]-w[1][i],w[3][i]-w[1][i],w[4][i]-w[1][i],w[1][i],0};
	}
    res+=getans();cnt=0;
```
$$\begin{cases} 
	a_{2,j}-a_{1,j}\le a_{1,k}-a_{2,k} \\ 
	a_{3,j}-a_{1,j}\le a_{1,k}-a_{3,k} \\ 
   a_{4,j}-a_{1,j}\le a_{1,k}-a_{4,k} \\
\end{cases}
$$ 
```cpp
	for(int i=1;i<=n;i++){
		q[++cnt]={w[2][i]-w[1][i],w[2][i]-w[3][i],w[2][i]-w[4][i],0,1};
		q[++cnt]={w[1][i]-w[2][i]+1,w[3][i]-w[2][i],w[4][i]-w[2][i],w[2][i],0};
	}
	res+=getans();cnt=0;
```
$$\begin{cases} 
   a_{1,j}-a_{2,j}< a_{2,k}-a_{1,k} \\ 
	a_{3,j}-a_{2,j}\le a_{2,k}-a_{3,k} \\ 
   a_{4,j}-a_{2,j}\le a_{2,k}-a_{4,k} \\
 \end{cases}
$$ 
```cpp
	for(int i=1;i<=n;i++){
		q[++cnt]={w[3][i]-w[1][i],w[3][i]-w[2][i],w[3][i]-w[4][i],0,1};
		q[++cnt]={w[1][i]-w[3][i]+1,w[2][i]-w[3][i]+1,w[4][i]-w[3][i],w[3][i],0};
	}
	res+=getans();cnt=0;
```
$$\begin{cases} 
   a_{1,j}-a_{3,j}< a_{3,k}-a_{1,k} \\ 
	a_{2,j}-a_{3,j}< a_{3,k}-a_{2,k} \\ 
   a_{4,j}-a_{3,j}\le a_{3,k}-a_{4,k} \\ 
 \end{cases}
$$  

```cpp
	for(int i=1;i<=n;i++){
		q[++cnt]={w[4][i]-w[1][i],w[4][i]-w[2][i],w[4][i]-w[3][i],0,1};
		q[++cnt]={w[1][i]-w[4][i]+1,w[2][i]-w[4][i]+1,w[3][i]-w[4][i]+1,w[4][i],0};
	}
	res+=getans();
```
$$\begin{cases} 
   a_{1,j}-a_{4,j}< a_{4,k}-a_{1,k} \\ 
	a_{2,j}-a_{4,j}< a_{4,k}-a_{2,k} \\ 
   a_{3,j}-a_{4,j}< a_{4,k}-a_{3,k} \\ 
\end{cases}
$$

```cpp
	return res;
}
```

是不是很直观地对应起来了？

唯一要强调的是为了减少代码量，我们把 $<$ 操作加一，这样全部珂以转化为 $\le$

```cpp
int sb2(){//把多余的部分用-200000代替，有数值的部分换成相反数，然后再跑一遍最小值查询
	int res=solve();
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)w[i][j]=-w[i][j];
	for(int i=1;i<=n;i++)w[3][i]=w[4][i]=-200000;
	return 2*(res-solve());
}
int sb3(){//和sb2同理，把多余的部分用-200000代替，有数值的部分换成相反数，然后再跑一遍最小值查询
	int res=solve();
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)w[i][j]=-w[i][j];
	for(int i=1;i<=n;i++)w[4][i]=-200000;
	return 2*(res-solve());
}
int sb4(){//标准的三维偏序
	int res=solve();
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)w[i][j]=-w[i][j];
	return 2*(res-solve());
}  
```

我们发现一个数字最终只会被计算一次，而题目要求我们计算全部，于是我们将答案乘以 $2$ 即可。

这是 `CDQ` 分治部分的代码，供大家参考，要注意的是树状数组为了避免负数的出现同一加上最大值。

```cpp
struct unsigned_bit{
	int t[N];
	void clear(){memset(t,0,sizeof(t));}
	int lowbit(int x){return x&-x;}
	void add(int x,int v){x+=200001;for(;x<N;x+=lowbit(x))t[x]+=v;}
	int query(int x){
		int ans=0;x+=200001;
		for(;x;x-=lowbit(x))ans+=t[x];
		return ans;
	}
	void assign(int x,int v){x+=200001;for(;x<N;x+=lowbit(x))t[x]=v;}
}b;
struct Q{
	int x,y,z,w,typ;
	bool operator<(const Q &a)const{
		return x==a.x?(y==a.y?(z==a.z?typ<a.typ:z<a.z):y<a.y):x<a.x;
	}
}q[N],tmp[N];
int ans=0,cnt;
void cdq(int l,int r){
	if(l==r)return;
	int mid=(l+r)/2;
	cdq(l,mid);cdq(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(q[i].y<=q[j].y){
			if(!q[i].typ)b.add(q[i].z,q[i].w);
			tmp[k++]=q[i++];
		}else{
			if(q[j].typ)ans+=b.query(q[j].z);
			tmp[k++]=q[j++];
		}
	}
	while(i<=mid){
		if(!q[i].typ)b.add(q[i].z,q[i].w);
		tmp[k++]=q[i++];
	}
	while(j<=r){
		if(q[j].typ)ans+=b.query(q[j].z);
		tmp[k++]=q[j++];
	}
	for(int i=l;i<=mid;i++)if(!q[i].typ)b.assign(q[i].z,0);
	for(int i=l;i<=r;i++)q[i]=tmp[i];
}
int getans(){
	sort(q+1,q+cnt+1);
	ans=0;
	cdq(1,cnt);
	return ans;
}
```
完整代码到这里相信读者应该都会写了，就不给出了。

完结撒花。


---

## 作者：WeLikeStudying (赞：2)

- 我靠完全不会做，这个要注意。
- 主要的问题在于没有想到统计贡献的思想。
- 完全不会代码实现，这个也要注意，难道我已经连一维偏序也不会打了吗。
- 难道是因为我不会最快速的排序方法：[bogo 排序](https://en.wikipedia.org/wiki/Bogosort)吗？
- ``民之从事，常于几成而败之；慎终如始，则无败事。``

**题意**
- [题意](https://www.luogu.com.cn/problem/P8253)。
- 给定一个 $m\times n$ 的矩阵，求任意两列的和的最大值和最小值之和。
- $m\le 4,n\le 2\times 10^5$。

**分析**
- 啊，$m=2$ 的情况容易解决，答案即为 $O(n\sum a_{i,j})$，[代码](https://www.luogu.com.cn/paste/d5w1jca0)。
- 对于 $m=3$ 的情况，容易参变分离转化为二维偏序，也就是说：$a_i+a_j\ge b_i+b_j$ 的情况可以转化为 $a_i-b_i\ge b_j-a_j$，所以问题可以理解成求 $6$ 次二维偏序，这里对于去重的方面考虑可要仔细了，不过有大样例的话一般没什么问题，[代码](https://www.luogu.com.cn/paste/lu103n77)。
- 对于 $m=4$ 的情况，难道要做 $24$ 次三维偏序？并不一定，你看 $m=2$ 的情况十分好算，我们枚举在中间的每种情况，然后减去它，[代码](https://www.luogu.com.cn/paste/8dsx94qz)。
- 怎么证明它是对的呢，如果不求甚解的话，枚举 $4!$ 种可能的大小关系即可证明，但实际上，这种做法可以拓展到一般的情况，复杂度为 $O(m!n\log n)$。
- 实际上，原问题的本质是利用了这个结论：对于 $1$ 到 $m$ 的所有排列，使得第 $i$ 个位置大于第 $j$ 个位置，小于第 $k$ 个位置（$i,j,k$ 互不相等）的方案数一定是 $n!/3!$，可以利用概率分析证明，因此明确了这个结论，不仅可以写出简洁的代码，还可以拓展到一般的情况。
- 我们在信息学研究中，也应该对常见的问题进行总结和推广，不仅对自己有收获，更有可能丰富大众的思维。

---

## 作者：BBD186587 (赞：1)

在下面的做法中，$\min$ 和 $\max$ 本质相同。所以只针对 $m=4$ 时，只考虑 $\min$ 的情况进行讲述。

先枚举最小值由哪一行取到，对于每种情况都统计一次答案。不失一般性地，假设枚举到了第一行。

若 $\min \limits_{k=1}^m (a_{k,i}+a_{k,j}) =a_{1,i}+a_{1,j}$，则需要满足 $a_{1,i}+a_{1,j} \le a_{2,i}+a_{2,j}$ 等一系列限制。

发现不等式两边相等的情况可能会导致算重，考虑能否通过一些简单的处理把两边相等的情况去掉。

可以把限制转化为：

- $4a_{1,i}+4a_{1,j}<4a_{2,i}+4a_{2,j}+1$
- $4a_{1,i}+4a_{1,j}<4a_{3,i}+4a_{3,j}+2$
- $4a_{1,i}+4a_{1,j}<4a_{4,i}+4a_{4,j}+3$

移一下项，把同一个字母放到一边，得到 $4a_{1,i}-4a_{2,i}<4a_{2,j}-4a_{1,j}+1$ 这样的形式。

那么，分别令：$A_i=4a_{1,i}-4a_{2,i},B_i=4a_{1,i}-4a_{3,i},C_i=4a_{1,i}-4a_{4,i}$，
限制就变成了：$A_i<-A_j+1,B_i<-B_j+2,C_i<-C_j+3$。

这是一个类似于三维偏序的问题，CDQ 分治即可。

同样使用这个方法，$m=2,3$ 的情形都是简单的，不再赘述。

时间复杂度 $O(8\times n \log^2 n)$。

使用 min-max 容斥等手段改写式子后，可以把 $\min(a,b,c,d)$ 这样的项消掉。最后得到的式子显然就等价于一个 $m \le 3$ 的问题。时间复杂度自然也优化到了求解二维偏序时的 $O(n \log n)$。

给出 $O(n \log^2 n)$ 做法的关键代码。

```cpp
namespace Q4
{
	ll ans;
	int c[N];
	struct node{int tp,a,b,c,o;}A[N],v[N];
	bool cmpa(node x,node y){return x.a<y.a;}
	bool cmpb(node x,node y){return x.b<y.b;}
	struct BIT
	{
		ll a[N];
		int lowbit(int x){return x&-x;}
		void upd(int x,int k)
		{
			while(x<=n*2) a[x]+=k,x+=lowbit(x);
		}
		ll query(int x)
		{
			ll sum=0;
			while(x) sum+=a[x],x-=lowbit(x);
			return sum;
		}
	}B1,B2;
	void solve(int l,int r)
	{
		if(l==r) return;
		int mid=(l+r)/2;
		solve(l,mid),solve(mid+1,r);
		int t=mid+1;
		for(int i=l;i<=mid;i++)
		{
			while(t<=r&&A[t].b<A[i].b)
				{if(A[t].tp) ans+=B2.query(A[t].c-1),ans+=1ll*A[t].o*B1.query(A[t].c-1);t++;}
			if(!A[i].tp) B1.upd(A[i].c,1),B2.upd(A[i].c,A[i].o);
		}
		while(t<=r){if(A[t].tp) ans+=B2.query(A[t].c-1),ans+=1ll*A[t].o*B1.query(A[t].c-1);t++;}
		for(int i=l;i<=mid;i++) if(!A[i].tp) B1.upd(A[i].c,-1),B2.upd(A[i].c,-A[i].o);
		t=mid+1;
		for(int i=l;i<=mid;i++)
		{
			while(t<=r&&A[t].b<A[i].b)
				{if(!A[t].tp) ans+=B2.query(A[t].c-1),ans+=1ll*A[t].o*B1.query(A[t].c-1);t++;}
			if(A[i].tp) B1.upd(A[i].c,1),B2.upd(A[i].c,A[i].o);
		}
		while(t<=r){if(!A[t].tp) ans+=B2.query(A[t].c-1),ans+=1ll*A[t].o*B1.query(A[t].c-1);t++;}
		for(int i=l;i<=mid;i++) if(A[i].tp) B1.upd(A[i].c,-1),B2.upd(A[i].c,-A[i].o);
		int t1=l,t2=mid+1,cnt=0;
		while(t1!=mid+1||t2!=r+1)
		{
			if(t1==mid+1) cnt++,v[cnt]=A[t2++];
			else if(t2==r+1) cnt++,v[cnt]=A[t1++];
			else
			{
				if(A[t1].b<A[t2].b) cnt++,v[cnt]=A[t1++];
				else cnt++,v[cnt]=A[t2++];
			}
		}
		for(int i=l;i<=r;i++) A[i]=v[i-l+1];
	}
	void main()
	{
		for(int k=1;k<=m;k++)
		{
			for(int i=1,t=0;i<=m;i++)
			{
				if(i==k) continue;t++;
				for(int j=1;j<=n;j++)
				{
					if(t==1) A[j].a=(a[k][j]-a[i][j])*4,A[j+n].a=-A[j].a+i-k;
					if(t==2) A[j].b=(a[k][j]-a[i][j])*4,A[j+n].b=-A[j].b+i-k;
					if(t==3) A[j].c=(a[k][j]-a[i][j])*4,A[j+n].c=-A[j].c+i-k;
				}
			}
			for(int i=1;i<=n;i++) A[i].o=A[i+n].o=a[k][i];
			for(int i=1;i<=n;i++) A[i].tp=0,A[i+n].tp=1;
			for(int i=1;i<=n*2;i++) c[i]=A[i].a;sort(c+1,c+n*2+1);
			for(int i=1;i<=n*2;i++) A[i].a=lower_bound(c+1,c+n*2+1,A[i].a)-c;
			for(int i=1;i<=n*2;i++) c[i]=A[i].b;sort(c+1,c+n*2+1);
			for(int i=1;i<=n*2;i++) A[i].b=lower_bound(c+1,c+n*2+1,A[i].b)-c;
			for(int i=1;i<=n*2;i++) c[i]=A[i].c;sort(c+1,c+n*2+1);
			for(int i=1;i<=n*2;i++) A[i].c=lower_bound(c+1,c+n*2+1,A[i].c)-c;
			sort(A+1,A+n*2+1,cmpa),solve(1,n*2);
		}
		printf("%lld",ans);
	}
}
```

---

## 作者：HikariS (赞：1)

要高考了我在干啥。。文化课越差心态越好了属于是

### 做法一

先考虑求 $\max$ 的总和( $\min$ 同理)，考虑枚举每一行，思考一对列二元组 $(i,j)$ 答案会取在这一行当且仅当满足以下条件（以第一行为例）：

$$ \left\{
\begin{aligned}
a_{1,i}+a_{1,j} & \geq & a_{2,i}+a_{2,j} \\
a_{1,i}+a_{1,j} & \geq & a_{3,i}+a_{3,j} \\
a_{1,i}+a_{1,j} & \geq & a_{4,i}+a_{4,j} \\
\end{aligned}
\right.
$$

也即

$$ \left\{
\begin{aligned}
a_{1,i}-a_{2,i} & \geq & a_{2,j}-a_{1,j} \\
a_{1,i}-a_{3,i} & \geq & a_{3,j}-a_{1,j} \\
a_{1,i}-a_{4,i} & \geq & a_{4,j}-a_{1,j} \\
\end{aligned}
\right.
$$

这样就是三维数点的格式了。

注意当考虑其他行时，为避免最大值相同出现重复计算，应该在不同行大小相同时强制钦定一个顺序，如值相同时则比较行号。

注意三维数点在特殊情况下是存在 $O(n\log n)$ 的优秀做法的，详见[陶爷爷的博客](https://www.cnblogs.com/Tiw-Air-OAO/p/14026192.html)，本题也可以利用此原理优化成  $O(n\log n)$ ，不过笔者~~因为太懒~~仅给出 $O(n \log^2 n)$ 的实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fp(i,l,r) for(register int (i)=(l);(i)<=(r);++(i))
#define fd(i,l,r) for(register int (i)=(l);(i)>=(r);--(i))
#define fe(i,u) for(register int (i)=front[(u)];(i);(i)=e[(i)].next)
#define mem(a) memset((a),0,sizeof (a))
#define O(x) cerr<<#x<<':'<<x<<endl
#define int long long
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)wr(x/10);
	putchar('0'+x%10);
}
const int MAXN=4e5+10;
struct poi{
	int x,y,z,w,id;
	inline bool operator<(const poi &b)const{
		if(x!=b.x)return x<b.x;
		if(y!=b.y)return y<b.y;
		if(z!=b.z)return z<b.z;//necessary!
		return id<b.id;
	}
}a[MAXN],tmp[MAXN];
int C[MAXN],n,w[5][MAXN/2],ans,m,tot,res;
inline int ask(int i){
	int res=0;i+=200001;
	for(;i;i-=i&-i)res+=C[i];
	return res;
}
inline void add(int i,int v){
	i+=200001;
	for(;i<=400002;i+=i&-i)C[i]+=v;
}
void solve(int l,int r){
	if(l==r)return;
	int mid=l+r>>1,p=l-1,t=0;
	solve(l,mid);solve(mid+1,r);
	fp(i,mid+1,r){
		while(p<mid&&a[p+1].y<=a[i].y){
			tmp[++t]=a[++p];if(a[p].id==0)add(a[p].z,a[p].w);
		}
		tmp[++t]=a[i];if(a[i].id==1)ans+=ask(a[i].z);
	}
	fp(i,l,p)if(a[i].id==0)add(a[i].z,-a[i].w);while(p<mid)tmp[++t]=a[++p];
	fp(i,l,r)a[i]=tmp[i-l+1];
}
inline int dcount(){
	sort(a+1,a+1+tot);ans=0;mem(C);
	solve(1,tot);
	return ans;
}
inline int doit4(){
	tot=0;int res=0;
	fp(i,1,n){
		a[++tot]={w[1][i]-w[2][i],w[1][i]-w[3][i],w[1][i]-w[4][i],0,1};
		a[++tot]={w[2][i]-w[1][i],w[3][i]-w[1][i],w[4][i]-w[1][i],w[1][i],0};
	}
	res+=dcount();tot=0;
	fp(i,1,n){
		a[++tot]={w[2][i]-w[1][i],w[2][i]-w[3][i],w[2][i]-w[4][i],0,1};
		a[++tot]={w[1][i]-w[2][i]+1,w[3][i]-w[2][i],w[4][i]-w[2][i],w[2][i],0};
	}
	res+=dcount();tot=0;
	fp(i,1,n){
		a[++tot]={w[3][i]-w[1][i],w[3][i]-w[2][i],w[3][i]-w[4][i],0,1};
		a[++tot]={w[1][i]-w[3][i]+1,w[2][i]-w[3][i]+1,w[4][i]-w[3][i],w[3][i],0};
	}
	res+=dcount();tot=0;
	fp(i,1,n){
		a[++tot]={w[4][i]-w[1][i],w[4][i]-w[2][i],w[4][i]-w[3][i],0,1};
		a[++tot]={w[1][i]-w[4][i]+1,w[2][i]-w[4][i]+1,w[3][i]-w[4][i]+1,w[4][i],0};
	}
	res+=dcount();tot=0;
	return res;
}
inline void subtask4(){
	int res=0;
	res+=doit4();
	fp(i,1,m)fp(j,1,n)w[i][j]=-w[i][j];
	res-=doit4();
	printf("%lld\n",res*2);
}
inline void subtask3(){
	int res=0;
	res+=doit4();
	fp(i,1,m)fp(j,1,n)w[i][j]=-w[i][j];
	fp(j,1,n)w[4][j]=-200000;
	res-=doit4();
	printf("%lld\n",res*2);
}
inline void subtask2(){
	int res=0;
	fp(i,1,m)fp(j,1,n)res+=w[i][j];
	printf("%lld\n",res*2*n);
}
main(){
	m=read();n=read();
	fp(i,1,m)fp(j,1,n)w[i][j]=read();
	if(m==2)subtask2();
	else if(m==3)subtask3();
	else if(m==4)subtask4();
	return 0;
}
```

### 做法二

这题有一点特殊性质

$$ 
\begin{aligned}
ans &= \sum_i\sum_j\min_{k \in\{1,2,3,4\} }(a_{k,i}+a_{k,j}) + \max_{k \in\{1,2,3,4\} }(a_{k,i}+a_{k,j}) \\
&= \sum_i\sum_j\sum_{T \subseteq \{1,2,3,4\}}(-1)^{|T|-1}\max_{k \in T}(a_{k,i}+a_{k,j}) + \max_{k \in\{1,2,3,4\} }(a_{k,i}+a_{k,j})\\
&= \sum_i\sum_j\sum_{T \subsetneq \{1,2,3,4\}}(-1)^{|T|-1}\max_{k \in T}(a_{k,i}+a_{k,j}) \\
\end{aligned}
$$
然后转化为 $m \leq 3$ 的情况，使用二维数点就足以解决。

时间复杂度 $O(n\log n)$ ，效率优于解法一。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fp(i,l,r) for(register int (i)=(l);(i)<=(r);++(i))
#define fd(i,l,r) for(register int (i)=(l);(i)>=(r);--(i))
#define fe(i,u) for(register int (i)=front[(u)];(i);(i)=e[(i)].next)
#define mem(a) memset((a),0,sizeof (a))
#define O(x) cerr<<#x<<':'<<x<<endl
#define int long long
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)wr(x/10);
	putchar('0'+x%10);
}
const int MAXN=4e5+10;
struct poi{
	int x,y,w,id;
	inline bool operator<(const poi &b)const{
		if(x!=b.x)return x<b.x;
		if(y!=b.y)return y<b.y;
		return id<b.id;
	}
}a[MAXN],tmp[MAXN];
int b1[MAXN],b2[MAXN];
int C[MAXN],n,w[5][MAXN/2],ans,m,tot,res;
inline int ask(int i){
	int res=0;i+=200001;
	for(;i;i-=i&-i)res+=C[i];
	return res;
}
inline void add(int i,int v){
	i+=200001;
	for(;i<=400002;i+=i&-i)C[i]+=v;
}
inline int count2d(){
	sort(a+1,a+1+tot);ans=0;mem(C);
	fp(i,1,tot){
		if(a[i].id==0)add(a[i].y,a[i].w);
		else ans+=ask(a[i].y);
	}
	return ans;
}
inline int count1d(){
	mem(b1);mem(b2);
	fp(i,1,tot)if(a[i].id==0)b1[a[i].x+200001]+=a[i].w;
	else b2[a[i].x+200001]++;
	ans=0;int tmp=0;
	fp(i,0,MAXN-1){
		tmp+=b1[i];
		if(b2[i])ans+=tmp*b2[i];
	}
	return ans;
}
inline int doit1(int w1[]){
	int res=0;
	fp(i,1,n)res+=w1[i];
	return res*n;
}
inline int doit2(int w1[],int w2[]){
	tot=0;int res=0;
	fp(i,1,n){
		a[++tot]={w1[i]-w2[i],0,0,1};
		a[++tot]={-w1[i]+w2[i],0,w1[i],0};
	}
	res+=count1d();tot=0;
	fp(i,1,n){
		a[++tot]={w2[i]-w1[i],0,0,1};
		a[++tot]={-w2[i]+w1[i]+1,0,w2[i],0};
	}
	res+=count1d();tot=0;
	return res;	
}
inline int doit3(int w1[],int w2[],int w3[]){
	tot=0;int res=0;
	fp(i,1,n){
		a[++tot]={w1[i]-w2[i],w1[i]-w3[i],0,1};
		a[++tot]={-w1[i]+w2[i],-w1[i]+w3[i],w1[i],0};
	}
	res+=count2d();tot=0;
	fp(i,1,n){
		a[++tot]={w2[i]-w1[i],w2[i]-w3[i],0,1};
		a[++tot]={-w2[i]+w1[i]+1,-w2[i]+w3[i],w2[i],0};
	}
	res+=count2d();tot=0;
	fp(i,1,n){
		a[++tot]={w3[i]-w1[i],w3[i]-w2[i],0,1};
		a[++tot]={-w3[i]+w1[i]+1,-w3[i]+w2[i]+1,w3[i],0};
	}
	res+=count2d();tot=0;
	return res;
}
inline void subtask4(){
	int res=0;
	res+=doit1(w[1])+doit1(w[2])+doit1(w[3])+doit1(w[4]);
	fp(i,1,4)fp(j,i+1,4)res-=doit2(w[i],w[j]);
	res+=doit3(w[1],w[2],w[3])+doit3(w[1],w[2],w[4])+doit3(w[1],w[3],w[4])+doit3(w[2],w[3],w[4]);
	printf("%lld\n",res*2);
}
inline void subtask3(){
	int res=0;
	res+=doit3(w[1],w[2],w[3]);
	fp(i,1,m)fp(j,1,n)w[i][j]=-w[i][j];
	res-=doit3(w[1],w[2],w[3]);
	printf("%lld\n",res*2);
}
inline void subtask2(){
	int res=0;
	fp(i,1,m)fp(j,1,n)res+=w[i][j];
	printf("%lld\n",res*2*n);
}
main(){
//	freopen("sort4.in","r",stdin);
	m=read();n=read();
	fp(i,1,m)fp(j,1,n)w[i][j]=read();
	if(m==2)subtask2();
	else if(m==3)subtask3();
	else if(m==4)subtask4();
	return 0;
}
```

> 后生可畏，焉知来者之不如今也？


---

## 作者：Purslane (赞：0)

# Solution

$\rm CDQ$ 分治模板题。

直接考虑 $m=4$ 的情况，并且分别求解 $\min$ 和 $\max$。

求 $\rm max$ 的操作可以通过取相反数化归为 $\rm min$。

对于每个 $k$，我们求出他对哪些 $(i,j)$ 是满足 $a_{k,i} + a_{k,j}$ 作为最小值。（很显然同一个 $(i,j)$ 可能有多个 $k$ 使值相同。所以可能要修改为严格偏序关系）

以 $k=1$ 为例，显然等价于：$a_{1,i}+a_{1,j} \le a_{2,i} + a_{2,j}$，$a_{1,i}+a_{1,j} \le a_{3,i} + a_{3,j}$，$a_{1,i}+a_{1,j} \le a_{4,i} + a_{4,j}$。

这时候考虑枚举 $i$，看看有多少个满足条件的 $j$，在答案里加入 $a_{k,i} \times 2cnt_j$。则必须分离 $i$ 和 $j$。

令 $c_{1,i} = a_{1,i} - a_{2,i}$，$c_{2,i} = a_{1,i} - a_{3,i}$，$c_{3,i}=a_{1,i}-a_{4,i}$。等价于：

$c_{1,i}+c_{1,j} \le 0$，$c_{2,i}+c_{2,j} \le 0$，$c_{3,i}+c_{3,j} \le 0$。这就是一个赤裸裸的三维偏序模版。（你也可以看出来，如果 $m < 4$，可以令 $c_{3,i} \equiv 0$。）

没被卡常。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=4e5+10;
int m,n,ans,tot,lcnt,a[5][MAXN],c[5][MAXN],tr[MAXN],lsh[MAXN];
void update(int pos,int v) {while(pos<=lcnt)tr[pos]+=v,pos+=pos&-pos;return ;}
int query(int pos) {int ans=0;while(pos)ans+=tr[pos],pos-=pos&-pos;return ans;}
struct INFO {int x,y,z,id,op;}t[MAXN],tmp[MAXN];
int cdq(int l,int r,int op) {
	if(l==r) return 0;
	int mid=(l+r>>1),ans=cdq(l,mid,op)+cdq(mid+1,r,op);
	vector<int> upd;
	int L=l,R=mid+1,pos=0;
	while(L<=mid&&R<=r) {
		if(t[L].y<=t[R].y) {
			tmp[++pos]=t[L];
			if(t[L].op==0) update(t[L].z,1),upd.push_back(t[L].z);
			L++;
		}
		else {
			tmp[++pos]=t[R];
			if(t[R].op==1) ans+=a[op][t[R].id]*query(t[R].z);
			R++;	
		}
	}
	while(L<=mid) {
		tmp[++pos]=t[L];
		if(t[L].op==0) update(t[L].z,1),upd.push_back(t[L].z);
		L++;
	}
	while(R<=r) {
		tmp[++pos]=t[R];
		if(t[R].op==1) ans+=a[op][t[R].id]*query(t[R].z);
		R++;
	}
	ffor(i,l,r) t[i]=tmp[i-l+1];
	for(auto id:upd) update(id,-1);
	return ans;
}
int solve(void) {
	int tans=0;
	ffor(i,1,m) {
		tot=0;
		ffor(j,1,n) {
			int id=0;
			ffor(x,1,m) if(x!=i) id++,c[id][j]=a[i][j]-a[x][j];
			if(m==3) c[3][j]=0;
			t[++tot]={-c[1][j],-c[2][j],-c[3][j],j,1};
			if(i>=2) t[tot].x--;if(i>=3) t[tot].y--;if(i>=4) t[tot].z--;
		}
		ffor(j,1,n) t[++tot]={c[1][j],c[2][j],c[3][j],j,0};
		lcnt=0; ffor(j,1,tot) lsh[++lcnt]=t[j].z; sort(lsh+1,lsh+lcnt+1),lcnt=unique(lsh+1,lsh+lcnt+1)-lsh-1;
		ffor(j,1,tot) t[j].z=lower_bound(lsh+1,lsh+lcnt+1,t[j].z)-lsh;
		sort(t+1,t+tot+1,[](INFO A,INFO B){if(A.x!=B.x) return A.x<B.x;return A.op<B.op;});
		tans+=cdq(1,tot,i);
	}
	return tans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>m>>n;
	ffor(i,1,m) ffor(j,1,n) cin>>a[i][j];
	if(m==2) {
		int ans=0;
		ffor(i,1,n) ans+=2*n*(a[1][i]+a[2][i]);
		return cout<<ans,0;
	}
	ans=solve();
	ffor(i,1,m) ffor(j,1,n) a[i][j]=-a[i][j];
	ans-=solve(),cout<<ans*2;
	return 0;
}
```

---

## 作者：KingPowers (赞：0)

## 前言

[题目链接](https://www.luogu.com.cn/problem/P8253)

114514 年前就听过的题了，现在终于是写上了。

巨大二/三维数点题，甚至还能带上 min-max 容斥。

## 正文

首先注意到 $\min$ 和 $\max$ 的做法本质上是相同的，下文只讨论 $\max$ 该怎么做，$\min$ 的部分偷懒的话可以直接将所有数取相反数再跑一边 $\max$。

由于 $m$ 很小，且观察数据点 $m$ 的分布，此题做法一定和 $m$ 是强相关的，因此下文对 $m=2,3,4$ 的情况分开讨论。

为了方便，提前约定 $a_i,b_i,c_i,d_i$ 为原题中的 $a_{1,i},a_{2,i},a_{3,i},a_{4,i}$。

### Case 1：$m=2$

这里有个重要的且下文会一直沿用的思想：考虑每对 $i,j$ 会对答案贡献几次。

假如 $a_i+a_j$ 会被算作最大值，那么有一条限制就是 $a_i+a_j\ge b_i+b_j$，移项得到 $a_i-b_i\ge b_j-a_j$。

贡献可以写成：

$$
\sum_{i=1}^n\sum_{j=1}^n[a_i-b_i\ge b_j-a_j](a_i+a_j)
$$

换个写法：
$$
\sum_{i=1}^n(a_i\sum_{j=1}^n[a_i-b_i>b_j-a_j]+\sum_{j=1}^n[a_i-b_i>b_j-a_j]a_j)
$$
每个 $i$ 拆出属性为 $a_i-b_i$ 和 $b_i-a_i$ 的点，实际上是个一维数点，直接排序或者树状数组统计即可。

同理，如果 $b_i+b_j$ 会被算作最大值，那么限制为 $b_i-a_i>a_j-b_i$（注意这里是大于号，用于防止算重），再跑一遍一维数点即可。

时间复杂度 $O(n\log n)$。

给出核心代码：

```cpp
int lowbit(int x){return x & (-x);}
void add(int x, int y){
	x += 200001;
	while(x <= 400005){
		sum[x] += y; cnt[x]++;
		x += lowbit(x);
	}
}
int query_sum(int x){
	int res = 0; x += 200001;
	for(; x; x -= lowbit(x)) res += sum[x];
	return res;
}
int query_cnt(int x){
	int res = 0; x += 200001;
	for(; x; x -= lowbit(x)) res += cnt[x];
	return res;
}
int solve2(int a[], int b[]){
	int res = 0;
	For(i, 1, n) add(b[i] - a[i], a[i]);
	For(i, 1, n) res += query_cnt(a[i] - b[i]) * a[i] + query_sum(a[i] - b[i]);
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum);
	For(i, 1, n) add(a[i] - b[i], b[i]);
	For(i, 1, n) res += query_cnt(b[i] - a[i] - 1) * b[i] + query_sum(b[i] - a[i] - 1);
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum);
	return res;
}                      
```

### Case 2：$m=3$

考虑继续沿用 $m=2$ 的做法，假如 $a_i+a_j$ 被算作最大值，限制为：
$$
\begin{cases}
a_i+a_j\ge b_i+b_j \\
a_i+a_j\ge c_i+c_j
\end{cases}
$$
同样进行移项，可以得到：
$$
\begin{cases}
a_i-b_i\ge b_j-a_j  \\
a_i-c_i\ge c_j-a_j
\end{cases}
$$
那么贡献写出来和 $m=2$ 那个式子其实是一样的，只是方括号中的条件变成了满足上面这两个式子。

如果你真正理解了 $m=2$ 的做法，那么不难发现这部分的贡献可以直接跑一个二维数点算出来，每个点的属性为 $(a_i-b_i,a_i-c_i)$ 或 $(b_i-a_i,c_i-a_i)$。

同理，$b_i+b_j$ 被算作最大值的限制就是：
$$
\begin{cases}
b_i-a_i>a_j-b_j \\
b_i-c_i\ge c_j-b_j
\end{cases}
$$
$c_i+c_j$ 被算作最大值的限制为：
$$
\begin{cases}
c_i-a_i>a_j-c_j \\
c_i-b_i>b_j-c_j
\end{cases}
$$
一定要注意不等号，否则会算重或算漏。

那这部分直接跑三遍二维数点就做完了，时间复杂度 $O(n\log n)$。

同样放出核心代码：

```cpp
struct node{
	int x, y, w, op;
}q[N];
bool cmp(const node &a, const node &b){
	if(a.x != b.x) return a.x < b.x;
	if(a.y != b.y) return a.y < b.y;
	return a.op < b.op;
}
int lowbit(int x){return x & (-x);}
void add(int x, int y){
	x += 200001;
	while(x <= 400005){
		sum[x] += y; cnt[x]++;
		x += lowbit(x);
	}
}
int query_sum(int x){
	int res = 0; x += 200001;
	for(; x; x -= lowbit(x)) res += sum[x];
	return res;
}
int query_cnt(int x){
	int res = 0; x += 200001;
	for(; x; x -= lowbit(x)) res += cnt[x];
	return res;
}
int solve3(int a[], int b[], int c[]){
	int res = 0, tot = 0;
	For(i, 1, n){
		q[++tot] = {a[i] - b[i], a[i] - c[i], a[i], 1};
		q[++tot] = {b[i] - a[i], c[i] - a[i], a[i], 0};
	}
	sort(q + 1, q + tot + 1, cmp);
	For(i, 1, tot){
		if(q[i].op == 1) res += query_cnt(q[i].y) * q[i].w + query_sum(q[i].y);
		else add(q[i].y, q[i].w);
	}
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum); tot = 0;
	For(i, 1, n){
		q[++tot] = {b[i] - a[i] - 1, b[i] - c[i], b[i], 1};
		q[++tot] = {a[i] - b[i], c[i] - b[i], b[i], 0};
	}
	sort(q + 1, q + tot + 1, cmp);
	For(i, 1, tot){
		if(q[i].op == 1) res += query_cnt(q[i].y) * q[i].w + query_sum(q[i].y);
		else add(q[i].y, q[i].w);
	}
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum); tot = 0;
	For(i, 1, n){
		q[++tot] = {c[i] - a[i] - 1, c[i] - b[i] - 1, c[i], 1};
		q[++tot] = {a[i] - c[i], b[i] - c[i], c[i], 0};
	}
	sort(q + 1, q + tot + 1, cmp);
	For(i, 1, tot){
		if(q[i].op == 1) res += query_cnt(q[i].y) * q[i].w + query_sum(q[i].y);
		else add(q[i].y, q[i].w);
	}
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum); tot = 0;
	return res;
}
```

看着码量略大，其实重复的部分相当多，多写一个函数应该就能缩短很多。

### Case 3：$m=4$

同样如果你也理解了 $m=3$ 的做法，$m=4$ 你或许也已经会了：继续沿用上面的做法，每行的限制写出来，直接跑三维数点，复杂度 $O(n\log^2n)$，但是要跑四遍所以可能会比较慢。

事实上可以不用跑三维数点，注意到我们有 min-max 容斥：
$$
\min(S)=\sum_{T\subseteq S}(-1)^{|T|+1}\max(T)
$$
写出来我们要求的东西：
$$
\sum_{i=1}^n\sum_{j=1}^n(\max_{k\in\{1,2,3,4\}}(a_{k,i}+a_{k,j})+\min_{k\in\{1,2,3,4\}}(a_{k,i}+a_{k,j}))
$$
直接用 min-max 容斥把后面那个 $\min$ 给替换掉：
$$
\sum_{i=1}^n\sum_{j=1}^n(\max_{k\in\{1,2,3,4\}}(a_{k,i}+a_{k,j})+\sum_{k\in T,T\subseteq\{1,2,3,4\}}(-1)^{|T|+1}\max(a_{k,i}+a_{k,j}))
$$
注意到当 $T=\{1,2,3,4\}$ 时系数为 $-1$，与前面正好相抵消，所以实际上是求：
$$
\sum_{i=1}^n\sum_{j=1}^n\sum_{k\in T,T\subsetneq\{1,2,3,4\}}(-1)^{|T|+1}\max(a_{k,i}+a_{k,j})
$$
可以拆成若干个 $m=1,2,3$ 的答案相加减得到。

$m=1$ 的答案为所有数的和乘上 $2n$，直接考虑每个 $a_i$ 被算入答案的次数即可证明。

复杂度 $O(n\log n)$，当然这个二维数点实际上要跑十遍左右，但应该还是比摁跑三维数点要快。

最后给出本题完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 5e5 + 5;
int m, n, a[5][N], cnt[N], sum[N];
struct node{
	int x, y, w, op;
}q[N];
bool cmp(const node &a, const node &b){
	if(a.x != b.x) return a.x < b.x;
	if(a.y != b.y) return a.y < b.y;
	return a.op < b.op;
}
int lowbit(int x){return x & (-x);}
void add(int x, int y){
	x += 200001;
	while(x <= 400005){
		sum[x] += y; cnt[x]++;
		x += lowbit(x);
	}
}
int query_sum(int x){
	int res = 0; x += 200001;
	for(; x; x -= lowbit(x)) res += sum[x];
	return res;
}
int query_cnt(int x){
	int res = 0; x += 200001;
	for(; x; x -= lowbit(x)) res += cnt[x];
	return res;
}
int solve1(int a[]){
	int sum = 0;
	For(i, 1, n) sum += a[i];
	return sum * 2 * n;
}
int solve2(int a[], int b[]){
	int res = 0;
	For(i, 1, n) add(b[i] - a[i], a[i]);
	For(i, 1, n) res += query_cnt(a[i] - b[i]) * a[i] + query_sum(a[i] - b[i]);
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum);
	For(i, 1, n) add(a[i] - b[i], b[i]);
	For(i, 1, n) res += query_cnt(b[i] - a[i] - 1) * b[i] + query_sum(b[i] - a[i] - 1);
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum);
	return res;
}
int solve3(int a[], int b[], int c[]){
	int res = 0, tot = 0;
	For(i, 1, n){
		q[++tot] = {a[i] - b[i], a[i] - c[i], a[i], 1};
		q[++tot] = {b[i] - a[i], c[i] - a[i], a[i], 0};
	}
	sort(q + 1, q + tot + 1, cmp);
	For(i, 1, tot){
		if(q[i].op == 1) res += query_cnt(q[i].y) * q[i].w + query_sum(q[i].y);
		else add(q[i].y, q[i].w);
	}
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum); tot = 0;
	For(i, 1, n){
		q[++tot] = {b[i] - a[i] - 1, b[i] - c[i], b[i], 1};
		q[++tot] = {a[i] - b[i], c[i] - b[i], b[i], 0};
	}
	sort(q + 1, q + tot + 1, cmp);
	For(i, 1, tot){
		if(q[i].op == 1) res += query_cnt(q[i].y) * q[i].w + query_sum(q[i].y);
		else add(q[i].y, q[i].w);
	}
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum); tot = 0;
	For(i, 1, n){
		q[++tot] = {c[i] - a[i] - 1, c[i] - b[i] - 1, c[i], 1};
		q[++tot] = {a[i] - c[i], b[i] - c[i], c[i], 0};
	}
	sort(q + 1, q + tot + 1, cmp);
	For(i, 1, tot){
		if(q[i].op == 1) res += query_cnt(q[i].y) * q[i].w + query_sum(q[i].y);
		else add(q[i].y, q[i].w);
	}
	memset(cnt, 0, sizeof cnt); memset(sum, 0, sizeof sum); tot = 0;
	return res;
}
void Solve(){
	cin >> m >> n;
	For(i, 1, m) For(j, 1, n) cin >> a[i][j];
	if(m == 2){
		int ans = solve2(a[1], a[2]);
		For(i, 1, m) For(j, 1, n) a[i][j] = -a[i][j];
		ans -= solve2(a[1], a[2]);
		cout << ans << '\n';
	}
	else if(m == 3){
		int ans = solve3(a[1], a[2], a[3]);
		For(i, 1, m) For(j, 1, n) a[i][j] = -a[i][j];
		ans -= solve3(a[1], a[2], a[3]);
		cout << ans << '\n';
	}
	else{
		int ans = solve1(a[1]) + solve1(a[2]) + solve1(a[3]) + solve1(a[4]);
		ans -= solve2(a[1], a[2]) + solve2(a[1], a[3]) + solve2(a[1], a[4]) + solve2(a[2], a[3]) + solve2(a[2], a[4]) + solve2(a[3], a[4]);
		ans += solve3(a[1], a[2], a[3]) + solve3(a[1], a[2], a[4]) + solve3(a[1], a[3], a[4]) + solve3(a[2], a[3], a[4]);
		cout << ans << '\n';
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; //cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

