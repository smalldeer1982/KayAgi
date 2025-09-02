# [JOI 2020 Final] 火灾 / Fire

## 题目背景

因为数据包过大，所以本题只测试 Subtask 4 & 5。

Subtask 1 & 2 & 3 请在 [这里](https://www.luogu.com.cn/problem/U132672) 测试。

## 题目描述

给定一个长为 $N$ 的序列 $S_i$，刚开始为时刻 $0$。

定义 $t$ 时刻第 $i$ 个数为 $S_i(t)$，那么：

$$\begin{cases}
        S_0(t)=0\\S_i(0)=S_i\\S_i(t)=\max\{S_{i-1}(t-1),S_i(t-1)\} 
\end{cases}$$

你将对 $Q$ 个操作进行评估，第 $j$ 个操作让时刻 $T_j$ 时的区间 $[L_j,R_j]$ 全部变为 $0$。

执行一个操作需要一定的代价，执行第 $j$ 个操作需要以下的代价：

$$\sum\limits_{k=L_j}^{R_j}S_k(T_j)$$

求每个操作需要的代价。

注意：每个操作都是独立的。

## 说明/提示

#### 样例 1 解释

- $S_i(0)=\{9,3,2,6,5\}$。
- $S_i(1)=\{9,9,3,6,6\}$，第一个操作需要的代价为 $9+9+3=21$。
- $S_i(2)=\{9,9,9,6,6\}$，第二个操作需要的代价为 $9+9+9+6+6=39$。
- $S_i(3)=\{9,9,9,9,6\}$，第三个操作需要的代价为 $9+9+9+9+6=33$。
- $S_i(4)=\{9,9,9,9,9\}$，第四个操作需要的代价为 $9$。
- $S_i(5)=\{9,9,9,9,9\}$，第五个操作需要的代价为 $27$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（1 pts）：$N,Q \le 200$。
- Subtask 2（6 pts）：$T_j$ 互相相等。
- Subtask 3（7 pts）：$L_j=R_j$。
- Subtask 4（6 pts）：$S_i \le 2$。
- Subtask 5（80 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $1 \le N \le 2 \times 10^5$。
- $1 \le Q \le 2 \times 10^5$。
- $1 \le S_i \le 10^9$。
- $1 \le T_j \le N$。
- $1 \le L_j \le R_j \le N$。

#### 说明

翻译自 [第19回日本情報オリンピック　本選](https://www.ioi-jp.org/joi/2019/2020-ho/index.html) [E 火事](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t5.pdf)。

## 样例 #1

### 输入

```
5 5
9 3 2 6 5
1 1 3
2 1 5
3 2 5
4 3 3
5 3 5```

### 输出

```
21
39
33
9
27```

## 样例 #2

### 输入

```
10 10
3 1 4 1 5 9 2 6 5 3
1 1 6
2 8 10
4 2 7
8 3 3
6 1 10
3 2 8
5 1 9
7 4 5
9 7 9
10 10 10```

### 输出

```
28
21
34
4
64
43
55
9
27
9```

## 样例 #3

### 输入

```
10 10
3 1 4 1 5 9 2 6 5 3
1 6 6
2 8 8
4 2 2
8 3 3
6 1 1
3 4 4
5 5 5
7 10 10
9 8 8
10 7 7```

### 输出

```
9
9
3
4
3
4
5
9
9
9```

## 样例 #4

### 输入

```
10 10
3 1 4 1 5 9 2 6 5 3
7 1 6
7 8 10
7 2 7
7 3 3
7 1 10
7 2 8
7 1 9
7 4 5
7 7 9
7 10 10```

### 输出

```
28
27
34
4
64
43
55
9
27
9```

## 样例 #5

### 输入

```
20 20
2 1 2 2 1 1 1 1 2 2 2 1 2 1 1 2 1 2 1 1
1 1 14
2 3 18
4 10 15
8 2 17
9 20 20
4 8 19
7 2 20
11 1 5
13 2 8
20 1 20
2 12 15
7 1 14
12 7 18
14 2 17
9 19 20
12 12 12
6 2 15
11 2 15
19 12 17
4 1 20```

### 输出

```
25
30
12
32
2
24
38
10
14
40
8
28
24
32
4
2
28
28
12
40```

# 题解

## 作者：ytb2024 (赞：20)

思路易懂，代码简单。

[题目传送门](/problem/P6881)

附：[AT原题目](https://atcoder.jp/contests/joi2020ho/tasks/joi2020ho_e)

题意：开始有一个序列。在每一个时间，你从后往前将每个值变为它与它前面一个值的 $\max$。有一些询问，问你在一些时间的某个区间的和。 

先将序列想象成一个矩阵。

下面是图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5mf4wh85.png)

经过观察几组数据的图可以发现，序列上每个点的区域行成了一个平行四边形，设第 $i$ 个平行四边形纵长为 ${\text{g1}} _ {i}$，横长为 ${\text{g2}} _ {i}$。

可以发现，$\mathrm{g1}$ 为 $i$ 与 $i-1 \sim 1$ 中第一个大于 $i$ 位置上值的坐标的差。例如上图中的 ${\text{g1}} _ {4} = 3$，因为第一个大于 $6$ 的是 $9$，${\text{g1}} _ {2} = 1$，因为第一个大于 $2$ 的是 $3$。

$\mathrm{g2}$ 为 $i+1 \sim n$ 中第一个大于等于 $i$ 位置上值的坐标与 $i$ 的差。例如上图中的 ${\text{g2}} _ {3} = 1$，因为第一个大于等于 $2$ 的是 $6$，${\text{g2}} _ {2} = 2$，因为第一个大于等于 $3$ 的是 $6$。

需要注意的是，$i$ 的前面如果没有比它大的，会形成一个三角行（图上那坨屎，后面再处理）。但如果 $i$ 的后面没有大于等于它的，我们可能要在 $n+1$ 这个点上设一个无穷大，防止没有上限。

用单调栈求解，时间复杂度 $\mathrm{O}\left(\mathrm{n}\right)$。

代码：

```cpp
a[n+1]=mx+1,stk[++stp]=n+1;
per(i,1,n)
{
	while(a[i]>a[stk[stp]])stp--;
	r[i]=stk[stp];
	if(a[i]==a[stk[stp]])stk[stp]=i;
	else stk[++stp]=i;
}
stp=0;
rep(i,1,n)
{
	while(stp&&a[i]>=a[stk[stp]])stp--;
	if(!stp)stk[++stp]=i;
	else l[i]=stk[stp],stk[++stp]=i;
}
```

转换为矩阵问题，考虑如何用数据结构维护 $n \times n$ 个点。

一个显然的地方，对于一个等腰直角三角形，我们可以暴力加点，$\frac{n ^ {2}}{2}$ 个点只需要 $n$ 次操作。例如上图中的那坨屎，就可以暴力处理。考虑如何处理平行四边形。

下面是图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5l8i308q.png)

可以发现上图为两种情况。

第一种，上面下面分别一个三角形，中间一个正方形。用前面的方法处理三角形，正方形不用管。

第二种，上面下面分别一个三角形，可以直接处理。平行四边形可以采用让询问左移的方法。

代码：

```cpp
rep(i,1,n)mx=max(dep,r[i]-i),gg2[i]=r[i]-i;
rep(i,1,n)
{
	if(!l[i])
	{
		gg1[i]=dep-gg2[i]+1;
		rep(j,gg1[i]+1,dep)w1[j].push_back(upd{j-gg1[i]-1+i,a[i]});
	}
	else gg1[i]=i-l[i];
}
rep(i,1,n)if(gg1[i]>=gg2[i])rep(j,1,gg2[i])w1[j].push_back(upd{i+j-1,a[i]}),w1[gg1[i]+j].push_back(upd{i+j-1,-a[i]});else rep(j,1,gg1[i])w2[j].push_back(upd{i-j+1,a[i]}),w2[gg2[i]+j].push_back(upd{i-j+1,-a[i]});
rep(i,1,dep)
{
	for(auto y:w1[i])add(y.id,y.add,0);
	for(auto y:w2[i])add(y.id+n,y.add,1);
	for(auto y:ques[i-1])ans[y.id]=que(y.r,0)-que(y.l-1,0)+que(y.r-i+1+n,1)-que(y.l-i+n,1);
}
```

注：设 $\mathrm{mx}$ 为 $\max \left( {\text{g2}} _ {i} \right)$，对与层数大于 $\mathrm{mx}$ 的，特殊处理一下。

代码：

```cpp
rep(i,1,n)b[i]=max(a[i],b[i-1]),add(i,b[i],2);
rep(i,mx,n)for(auto y:ques[i])ans[y.id]=que(y.r,2)-que(y.l-1,2);
```

时间复杂度 $\mathrm{O}\left(\mathrm{n} \log{\mathrm{n}}\right)$。

[Record](https://atcoder.jp/contests/joi2020ho/submissions/45248987)

---

## 作者：xtx1092515503 (赞：19)

数据结构好题。

------------

我们考虑画出每一时刻所有位置的值：

![](https://cdn.luogu.com.cn/upload/image_hosting/qmgzwyrw.png)

这其中，我们可以找到最标准的情形：里面的元素 $\color{cyan}{7}$。可以看到，随着时间增加，它呈现一个平行四边形。

那么这个平行四边形由上面构成呢？我们考虑用单调栈找出每个位置向左向右第一个比它大的位置 $l_i,r_i$。则我们会发现，平行四边形的四个顶点是 $(i,0),(r_i-1,r_i-i-1),(r_i-1,r_i-l_i-2),(i,i-l_i-1)$。

我们考虑此时的询问，在坐标系上，就成为了一段水平线段。考虑差分一下，就变成了两条沿 $x$ 轴负方向的的射线。

考虑把一个平行四边形拆成三个三角形：

![](https://cdn.luogu.com.cn/upload/image_hosting/75of4m75.png)

如图，绿色平行四边形=大三角形-蓝三角形-紫三角形。

然后我们发现，每个三角形的形状都是一样的，并且都有一条腰在 $x$ 轴上。故我们可以用其上方顶点来唯一确定一个三角形。则有大三角形顶点 $(r_i-1,r_i-l_i-2)$，蓝三角形顶点 $(i-1,i-l_i-2)$，紫三角形顶点 $(r_i-1,r_i-i-2)$。

我们考虑一条沿 $x$ 轴负方向的射线与三角形的交线段长度：

![](https://cdn.luogu.com.cn/upload/image_hosting/35jshr42.png)

如图，如果该射线是绿线（原点在三角形内），可以将其平移至紫线位置，然后就可以拆括号计算了。如果该直线是棕线，则也可以简单计算。

于是我们可以用扫描线维护对于递增的射线原点的 $x$ 坐标，相应的位于其左侧的三角形们和位于其右侧的三角形们，然后分别转移即可。

至于如何转移，可以各通过两棵树状数组，一棵维护系数和，一棵维护带权坐标和，然后分别转移即可。共需四棵树状数组。

时间复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,a[200100],l[200100],r[200100],stk[200100],tp,lim,mil;
ll res[200100];
namespace BIT1{//a BIT for triangular summary.
	ll t1[600100],t2[600100];//t1 for weighted sum, t2 for common sum.
	void ADD(int x,int y){
		x--;
		ll tmp=1ll*y*x;
		for(int i=x+n+1;i<=3*n;i+=i&-i)t1[i]+=tmp,t2[i]+=y;
	}
	ll SUM(int x){
		ll ret=0;
		for(int i=x+n+1;i;i-=i&-i)ret-=t1[i],ret+=t2[i]*x;
		return ret;
	}
}
namespace BIT2{
	ll t1[600100],t2[600100];
	void ADD(int x,int y){
		x++;
		ll tmp=1ll*y*x;
		for(int i=x+n+1;i;i-=i&-i)t1[i]+=tmp,t2[i]+=y;
	}
	ll SUM(int x){
		ll ret=0;
		for(int i=x+n+1;i<=3*n;i+=i&-i)ret+=t1[i],ret-=t2[i]*x;
		return ret;
	} 
}
void ADD1(int x,int y,int z){BIT1::ADD(x-y,z);}
void ADD2(int x,int y,int z){BIT2::ADD(y,z);}
struct Query{
	int x,y,id;
	Query(int u=0,int v=0,int w=0){x=u,y=v,id=w;}
	friend bool operator <(const Query &x,const Query &y){return x.x<y.x;}
}q[400100];
struct Tri{
	int x,y,a;
	Tri(int u=0,int v=0,int w=0){x=u,y=v,a=w;}
	friend bool operator <(const Tri &x,const Tri &y){return x.x<y.x;}
}p[800100];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=n;i>=1;i--){
		while(tp&&a[i]>a[stk[tp]])l[stk[tp--]]=i;
		stk[++tp]=i;
	}
	while(tp)l[stk[tp]]=stk[tp]-n-1,tp--;
	for(int i=1;i<=n;i++){
		while(tp&&a[stk[tp]]<=a[i])r[stk[tp--]]=i;
		stk[++tp]=i;
	}
	while(tp)r[stk[tp--]]=n+1;
	for(int i=1;i<=n;i++){
		p[++lim]=Tri(i-1,i-l[i]-2,-a[i]);
		p[++lim]=Tri(r[i]-1,r[i]-l[i]-2,a[i]);
		p[++lim]=Tri(r[i]-1,r[i]-i-2,-a[i]);
	}
	for(int i=1;i<=lim;i++)ADD1(p[i].x,p[i].y,p[i].a);
	sort(p+1,p+lim+1);
	for(int i=1,t,l,r;i<=m;i++){
		scanf("%d%d%d",&t,&l,&r);
		q[++mil]=Query(l-1,t,-i);
		q[++mil]=Query(r,t,i);
	}
	sort(q+1,q+mil+1);
	for(int i=1,j=1;i<=mil;i++){
		while(j<=lim&&p[j].x<q[i].x)ADD1(p[j].x,p[j].y,-p[j].a),ADD2(p[j].x,p[j].y,p[j].a),j++;
		int lambda=(q[i].id>0?1:-1);q[i].id=abs(q[i].id);
		res[q[i].id]+=(BIT1::SUM(q[i].x-q[i].y)+BIT2::SUM(q[i].y))*lambda;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",res[i]);
//	for(int i=1;i<=n;i++)printf("%d %d\n",l[i],r[i]);
	return 0;
} 
```

---

## 作者：Chen_jr (赞：13)

如果把每个数向前面第一个比他大的数连边，那么构成一个树形结构

可以发现对于一个 $x$ 一直到下一个大于等于他的数之前的区间都会被他所影响，即都是他的子树，那么也就是说每个结点的子树是一个连续区间

因为是连续区间，所以他们被改变的时间也是连续的，我们考虑维护随时间变化的增量

在这个树形结构中他的父亲比他的父亲的父亲先影响到他，所以我们维护儿子与父亲的增量即可

其实上面这些废话只是告诉我们可以对每个位置得到一个四元组 $(t_0, l, r, d)$

表示在 $[l,r]$ 区间, 从 $t_0$ 时刻开始， 按照从左到右的位置顺序每个时刻都会在对应位置多 $d$ 的贡献

我们把询问拆成查询两个前缀相减的形式 $ans_r - ans_{l - 1}$ ，然后按照对时间进行扫描线，这样每个四元组的贡献大概就是下面这样

~~图有点丑，将就看吧~~


发现可以写成两个直角三角形差分的形式，如下下图


![](https://cdn.luogu.com.cn/upload/image_hosting/1pzfjjxt.png)


![](https://cdn.luogu.com.cn/upload/image_hosting/gwk77zpr.png)

绿色减去紫色

所以四元组变成了两个三元组，就能够处理了

三元组 $(t_0, l, d)$ 表示 $l$ 位置从 $t_0$ 时刻开始每时刻向后面有 $d$ 的增量

考虑对一个前缀 $p$ 进行 $t$ 时刻的询问， 他的贡献可以写成 $(min(p, l + t - t_0) - min(p, l - 1)) \times d$

这样对于 $p < l$ 我们也不需要特殊处理，因为一减就变成 $0$ 了

也就是 $(t + min(p - t, l - t_0) - min(p, l - 1)) \times d$

那么我们开四棵线段树分别维护

1. 在 $l$ 位置维护 $l \times d$

2. 在 $l - t_0$ 位置维护 $(l - t_0) \times d$

3. 在 $l$ 位置维护 $d$

4. 在 $l - t_0$ 位置维护 $d$

询问对 $min$ 取的是哪个值分开讨论即可

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 200005;
inline int read(){
	int x = 0; char c = getchar();
	while(c < '0' || c > '9')c = getchar();
	do{x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}while(c <= '9' && c >= '0');
	return x;
}
int n, q, a[maxn];
int sta[maxn], fa[maxn], r[maxn];
struct que{
	int p, t, id, opt;
	friend bool operator < (const que &x, const que &y){
		return x.t < y.t;
	}
}ask[maxn + maxn];
struct opt{
	int t0, l, d;
	friend bool operator < (const opt &x, const opt &y){
		return x.t0 < y.t0;
	}
}o[maxn + maxn];
ll ans[maxn];
struct tree{
	struct node{ll val, tag;}t[maxn << 3 | 1];
	void push_up(int x){
		t[x].val = t[x << 1].val + t[x << 1 | 1].val;
	}
	void modify(int x, int l, int r, int pos, ll val){
		if(l == r){
			t[x].val += val;
			return;
		}
		int mid = (l + r) >> 1;
		if(pos <= mid)modify(x << 1, l, mid, pos, val);
		else modify(x << 1 | 1, mid + 1, r, pos, val);
		push_up(x);
	}
	ll query(int x, int l, int r, int L, int R){
		if(L <= l && r <= R)return t[x].val;
		int mid = (l + r) >> 1; ll ans = 0;
		if(L <= mid)ans += query(x << 1, l,  mid, L, R);
		if(R > mid)ans += query(x << 1 | 1, mid + 1, r, L, R);
		return ans;
	}
}t[4];
ll sum[maxn];
int main(){
	n = read(), q = read();
	for(int i = 1; i <= n; ++i)a[i] = read();
	for(int i = 1; i <= n; ++i)sum[i] = sum[i - 1] + a[i];
	for(int i = 1; i <= q; ++i){
		int t = read(), l = read(), r = read();
		ask[i + i - 1].id = ask[i + i].id = i;
		ask[i + i - 1].t = ask[i + i].t = t;
		ask[i + i - 1].p = l - 1, ask[i + i - 1].opt = -1;
		ask[i + i].p = r, ask[i + i].opt = 1;
	}
	int top = 0;
	for(int i = 1; i <= n; ++i){
		while(top && a[sta[top]] < a[i])r[sta[top]] = i, --top;
		fa[i] = sta[top]; sta[++top] = i;
	}
	while(top)r[sta[top--]] = n + 1;
	sort(ask + 1, ask + q + q + 1);
	int cnt = 0;
	for(int i = 1; i <= n; ++i)if(fa[i]){
		o[++cnt].d = a[fa[i]] - a[i];
		o[cnt].l = i; o[cnt].t0 = i - fa[i];
		if(r[i]){
			o[++cnt].d = a[i] - a[fa[i]];
			o[cnt].l = r[i]; o[cnt].t0 = r[i] - fa[i];
		} 
	}
	sort(o + 1, o + cnt + 1);
	int op = 1;
	for(int i = 1; i <= q + q; ++i){
		while(op <= cnt && o[op].t0 <= ask[i].t){
			t[0].modify(1, 0, n, o[op].l - 1, 1ll * (o[op].l - 1) * o[op].d);
			t[1].modify(1, 0, n + n, o[op].l - o[op].t0 + n, 1ll * (o[op].l - o[op].t0) * o[op].d);
			t[2].modify(1, 0, n, o[op].l - 1, o[op].d);
			t[3].modify(1, 0, n + n, o[op].l - o[op].t0 + n, o[op].d);
			++op;
		}
		ll nans = 0;
		if(ask[i].p == 0)nans = 0;
		else{
			nans = ask[i].t * t[2].query(1, 0, n, 1, n);
			nans = nans + t[1].query(1, 0, n + n, 1, ask[i].p - ask[i].t + n);
			nans = nans + t[3].query(1, 0, n + n, ask[i].p - ask[i].t + n + 1, n + n) * (0ll + ask[i].p - ask[i].t);
			nans = nans - t[0].query(1, 0, n, 1, ask[i].p);
			nans = nans - t[2].query(1, 0, n, ask[i].p + 1, n) * 1ll * ask[i].p;
			nans = nans + sum[ask[i].p];
		}
		ans[ask[i].id] += nans * ask[i].opt;
	}
	for(int i = 1; i <= q; ++i)printf("%lld\n", ans[i]);
	return 0;
}
```


---

## 作者：User_Unauthorized (赞：8)

## 题面
给定一个长为 $N$ 的序列 $S_i$，刚开始为时刻 $0$。

定义 $t$ 时刻第 $i$ 个数为 $S_i(t)$，那么：

$$\left\{
        \begin{array}{ll}
        S_0(t)=0\\S_i(0)=S_i\\S_i(t)=\max\{S_{i-1}(t-1),S_i(t-1)\} 
        \end{array}
    \right.$$

共有 $Q$ 个询问，每次询问给出 $T_j, L_j, R_j$，求

$$\sum\limits_{k=L_j}^{R_j}S_k(T_j)$$

（$1 \le N, Q \le 2 \times 10^5$）

## 题解
我们可以列出一个 $N \times (N + 1)$ 的矩阵，其中第一行为初始数据，第 $i$ 行为第 $i - 1$ 时刻时数列的状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/a6jd6qsa.png)

不难看出询问的实质上是一个 $1 \times M$ 的矩形和，我们可以差分为查询两个前缀和然后相减。

发现题中数列变化的本质是较大数每个时刻均向右覆盖一个较小数，我们把同一个数覆盖的区域用同一种颜色表示，可以得到下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/v0wg28k5.png)

可以发现，每个数的贡献区域都可以近似看作一个平行四边形，下面以数 $6$ 所覆盖的区域为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/hj5opfhu.png)

我们可以发现，这个平行四边形的左侧会被一个比他小的数阻挡，而右侧会被一个比他大的数阻挡。

但是我们可以发现，一个平行四边形是很难处理的，于是我们考虑将其拆成三个三角形。

![](https://cdn.luogu.com.cn/upload/image_hosting/e31ol8sv.png)

如上图的红色格子构成的平行四边形的和，可以看作一个大三角形与两个小三角形的差。即绿色、红色、蓝色三个颜色构成的大三角形与绿色、蓝色两个小三角形的差。

好的，现在我们已经成功的将平行四边形问题转化为了三角形问题，接下来我们考虑如何处理三角形问题。

我们可以发现这道题中的三角形都是等腰直角三角形，我们考虑将其转化为边平行于坐标轴的矩形，然后用扫描线处理。

我们首先考虑将这个直角三角形的水平右方向全部填充上相同的数，即假设让其产生额外的贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/5tx23g50.png)

然后我们将这个图形向左倾斜，使其左边界竖直。

![](https://cdn.luogu.com.cn/upload/image_hosting/3djrph6s.png)

注意在这个过程中与图形相关的查询也要同时向左平移。

这个时候我们发现向左移动完成后的图形便是一个矩形，可以利用扫描线求解。

图中的绿的部分不会产生贡献，因为不会有询问对那些格子进行查询，所以无需去除这部分的影响。

图中的蓝色部分在平移之前也是一个矩形，可以利用扫描线求解。

![](https://cdn.luogu.com.cn/upload/image_hosting/kgfayi8j.png)

现在我们已经成功的处理了平行四边形，下面我们考虑如何计算贡献。

可以发现，矩形对前缀和的影响是一个有定义域的一次函数，例如上图蓝色部分在 $x \le 5$ 时不会产生影响，在 $x > 5$ 时产生的影响呈一次函数关系。根据一次函数的表达式

$$y = ax + b$$

于是我们可以分开处理斜率（$a$）和截距（$b$），用两个树状数组维护即可。

对于平移之后的图同理，再开两个树状数组维护即可。

我们再回顾一下最开始的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/v0wg28k5.png)

我们发现第一个数字 $3$ 所覆盖的访问貌似不是一个平行四边形，但是我们可以发现其也可以转化为三个三角形。

![](https://cdn.luogu.com.cn/upload/image_hosting/rwkyv5u2.png)

这就意味着在这道题目中，计算左边第一个比它大的数时对于左边不存在比它大的数要合理的设置边界值。右侧同理。

## Code
```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MAX = INT_MAX >> 1;

class TreeArray {
public:
    typedef valueType sizeType;

    static constexpr sizeType shifting = 2e5 + 5;

private:
    sizeType size;

    ValueVector data;

    static valueType lowBit(valueType x) {
        return x & -x;
    }

public:
    explicit TreeArray(sizeType n) : size(n + shifting), data(size, 0) {};

    void insert(sizeType pos, valueType key) {
        pos += shifting;

        while (pos < size) {
            data.at(pos) += key;
            pos += lowBit(pos);
        }
    }

    valueType sum(sizeType pos) const {
        pos += shifting;

        valueType result = 0;

        while (pos > 0) {
            result += data.at(pos);
            pos -= lowBit(pos);
        }

        return result;
    }
};

struct Query {
    valueType id;
    valueType l, r, t;

    Query() : id(-1), l(-1), r(-1), t(-1) {};

    Query(valueType id, valueType l, valueType r, valueType t) : id(id), l(l), r(r), t(t) {};
};

typedef std::vector<Query> QueryVector;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;
typedef std::vector<QueryVector> QueryMatrix;
typedef std::vector<PairVector> PairMatrix;

int main() {
    valueType N, Q;

    std::cin >> N >> Q;

    ValueVector source(N + 100), leftBound(N + 100), rightBound(N + 100);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> source.at(i);

    std::deque<ValuePair> queue;

    queue.emplace_back(MAX, -N - 1);

    for (valueType i = 1; i <= N; ++i) {
        while (!queue.empty() && source.at(i) >= queue.back().first)
            queue.pop_back();

        leftBound.at(i) = queue.back().second;

        queue.emplace_back(source.at(i), i);
    }

    queue.clear();
    queue.emplace_back(MAX, N + 1);

    for (valueType i = N; i >= 1; --i) {
        while (!queue.empty() && source.at(i) > queue.back().first)
            queue.pop_back();

        rightBound.at(i) = queue.back().second;

        queue.emplace_back(source.at(i), i);
    }

    TreeArray tree1(N + 100), tree2(N + 100), tree3(N + 100), tree4(N + 100);

    PairMatrix task1(2 * N + 100), task2(2 * N + 100), task3(2 * N + 100), task4(2 * N + 100);

    typedef std::function<void(valueType, valueType, valueType)> addFunction;

    addFunction add = [&](valueType l, valueType r, valueType key) {
        task1.at(0).emplace_back(r, -key);
        task2.at(0).emplace_back(r, (r - 1) * key);
        task3.at(0).emplace_back(l + 1, key);
        task4.at(0).emplace_back(l + 1, -l * key);

        task1.at(r - l).emplace_back(r, key);
        task2.at(r - l).emplace_back(r, -(r - 1) * key);
        task3.at(r - l).emplace_back(l + 1, -key);
        task4.at(r - l).emplace_back(l + 1, l * key);
    };

    typedef std::function<valueType(valueType, valueType)> calcFunction;

    calcFunction calc = [&](valueType x, valueType t) -> valueType {
        return x * tree1.sum(x) + tree2.sum(x) + (x - t) * tree3.sum(x - t) + tree4.sum(x - t);
    };

    for (valueType i = 1; i <= N; ++i) {
        add(leftBound.at(i), i, -source.at(i));
        add(i, rightBound.at(i), -source.at(i));
        add(leftBound.at(i), rightBound.at(i), source.at(i));
    }

    QueryMatrix query(N + 100);
    ValueVector ans(Q);

    for (valueType i = 0; i < Q; ++i) {
        valueType l, r, t;

        std::cin >> t >> l >> r;

        query.at(t).emplace_back(i, l, r, t);
    }

    for (valueType i = 0; i <= N; ++i) {
        for (auto const &iter: task1.at(i)) tree1.insert(iter.first, iter.second);
        for (auto const &iter: task2.at(i)) tree2.insert(iter.first, iter.second);
        for (auto const &iter: task3.at(i)) tree3.insert(iter.first, iter.second);
        for (auto const &iter: task4.at(i)) tree4.insert(iter.first, iter.second);

        for (auto const &iter: query.at(i)) {
            ans.at(iter.id) = calc(iter.r, i) - calc(iter.l - 1, i);
        }
    }

    for (valueType i = 0; i < Q; ++i)
        std::cout << ans.at(i) << '\n';

    std::cout << std::flush;

    fclose(stdin);
    fclose(stdout);

    return 0;
}
```

---

## 作者：luogubot (赞：8)

给定 $a_{1\cdots n}$，记 $[a_i]^T=\max_{j=\max(1,i-T)}^i\{a_j\}$，$q$ 次询问给定 $T,l,r$，求 $\sum_{i=l}^r [a_i]^T$。

$n,q\leq 2\times 10^5$，$1\leq a_i\leq 10^9$。

以增量的形式描述每个点向右覆盖带来的影响。对于每个点找到其左边第一个比自己严格大的点作为父亲，则 $i$ 的子树是一个区间 $[i,r_i]$，满足 $r_i+1$ 是一个比自己大的位置，意义是每个点会影响到自己的子树，每个点上的值，会依次被自己祖先影响。也就是说，对于存在父亲的点 $l$，$[l,r_l]$ 中的点会从时刻 $t=l-fa_l$ 开始，逐步加上 $d=a_{fa_l}-a_l$，即在 $t+i$（$i\ge 0$）时刻，$a_{l+i}$ 会加上 $d$。

对于这样一个四元组 $(t,l,r,d)$，我们把它拆成没有右端点的 $(t,l,d)$ 与 $(t+r-l+1,r+1,-d)$，这样就是有 $O(n)$ 个三元组 $(t,l,d)$，表示从 $t$ 时刻开始，$l$ 位置开始的元素会依次加上 $d$。

询问拆成前缀之后就形如 $(T,x)$，表示询问 $T$ 时刻前缀 $[1,x]$ 的和。考虑增量三元组 $(t,l,d)$ 对询问 $(T,x)$ 的贡献：如果 $x\ge l$ 且 $T\ge t$，则会贡献 $d\times \min(x-l+1,T-t+1)$。

你发现钦定 $\min$ 也有三个偏序关系，但是别急。假设钦定 $x-l+1\leq T-t+1$，移项变为 $x-T\leq l-t$，则此时如果满足 $x\ge l$ 且 $x-l+1\leq T-t+1$，则 $T-t+1\ge (x-l)+1\ge 1$，天然满足 $T\ge t$。

于是离线按照 $x,l$ 双指针，$l-t$ 为下标放入树状数组维护 $\sum d$ 和 $\sum td$。另一部分同理。

$O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=4e5+10,D=2e5+1; 
int n,q,m,o,a[N],s[N],ans[N];
struct mdf{int t,l,d;}b[N];
bool cmp1(mdf a,mdf b){return a.t<b.t;}
bool cmp2(mdf a,mdf b){return a.l<b.l;}
struct qry{
	qry(){}
	qry(int tt,int xx,int mm,int ii){T=tt,x=xx,mul=mm,id=ii;}
	int T,x,mul,id;
}z[N];
bool CMP1(qry a,qry b){return a.T<b.T;}
bool CMP2(qry a,qry b){return a.x<b.x;}
void ADD(int t,int l,int r,int d){b[++m]=(mdf){t,l,d},b[++m]=(mdf){t+r-l+1,r+1,-d};}
int fa[N],R[N],stk[N],tp;
struct BIT{
	#define lowbit(x) (x&-x)
	int c[N],sum;
	void init(){memset(c,0,sizeof c),sum=0;}
	void add(int u,int x){sum+=x,u+=D;for(int i=u;i<N;i+=lowbit(i))c[i]+=x;}
	int ask(int u,int s=0){u+=D;for(int i=u;i;i-=lowbit(i))s+=c[i];return s;}//<=u
	int ASK(int u){return sum-ask(u);}//>u
}c1,c2;
signed main(){
	n=read(),q=read();For(i,1,n)a[i]=read(),s[i]=s[i-1]+a[i];
	Rof(i,n,1){while(tp&&a[i]>a[stk[tp]])fa[stk[tp--]]=i;stk[++tp]=i,R[i]=i;}
	For(i,1,n)if(fa[i])R[fa[i]]=i;Rof(i,n,1)R[fa[i]]=max(R[fa[i]],R[i]);
	For(l,1,n){int r=R[l];if(fa[l])ADD(l-fa[l],l,r,a[fa[l]]-a[l]);}
	For(i,1,q){
		int t=read(),l=read(),r=read();
		z[++o]=qry(t,r,1,i);
		z[++o]=qry(t,l-1,-1,i);
		ans[i]=s[r]-s[l-1];
	}sort(b+1,b+1+m,cmp2),sort(z+1,z+1+o,CMP2);//l<=x
	for(int i=1,j=1;i<=o;i++){
		int T=z[i].T,x=z[i].x,mul=z[i].mul,id=z[i].id;
		while(j<=m&&b[j].l<=z[i].x){
			int t=b[j].t,l=b[j].l,d=b[j].d;j++;
			c1.add(l-t,d),c2.add(l-t,l*d);
		}ans[id]+=mul*((x+1)*c1.ASK(x-T-1)-c2.ASK(x-T-1));
	}
	c1.init(),c2.init();
	sort(b+1,b+1+m,cmp1),sort(z+1,z+1+o,CMP1);//t<=T
	for(int i=1,j=1;i<=o;i++){
		int T=z[i].T,x=z[i].x,mul=z[i].mul,id=z[i].id;
		while(j<=m&&b[j].t<=z[i].T){
			int t=b[j].t,l=b[j].l,d=b[j].d;j++;
			c1.add(l-t,d),c2.add(l-t,t*d);
		}ans[id]+=mul*((T+1)*c1.ask(x-T-1)-c2.ask(x-T-1));
	}For(i,1,q)printf("%lld\n",ans[i]);
	return 0;
}
```



---

## 作者：jerry3128 (赞：7)

- 题意: $mx[l][r]$ 表示区间 $(l,r)$ 的最大值，询问  $\sum_{i=L}^{R}max[i-T][i]$ 

------------

随着时间的推移，大数字会覆盖后面的小数字，对于覆盖来讲，每一个数字的影响范围需要讨论的情况就较多了，所以我们对于所有的“覆盖操作”差分转为加减操作。那么每一个差分后数字的影响区间就如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/ofkdhosz.png)
从自己开始扩展，到达 $r[i]-1$ 后停止。

------------

于是我们我们可以通过数据结构维护。我们就是计算面积中的权值，能想到差分。离线询问将竖直段线和斜线段分开处理即可。

```
#include<bits/stdc++.h>
using namespace std;
long long p1=1000000,p2=0;
char buf[1000005],wb[1000005];
//long long gc() {
//	if(p1>=1000000)fread(buf,1,1000000,stdin),p1=0;
//	return buf[p1++];
//}
#define gc getchar
long long getint() {
	long long ret=0,flag=1;
	char c=gc();
	while(c<'0'||c>'9') {
		if(c=='-')flag=-1;
		c=gc();
	}
	while(c<='9'&&c>='0') {
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=gc();
	}
	return ret*flag;
}
void pc(char x) {
	if(p2>=1000000)fwrite(wb,1,1000000,stdout),p2=0;
	wb[p2++]=x;
}
void wrt(long long x) {
	if(x<0)pc('-'),x=-x;
	long long c[24]= {0};
	if(!x)return pc('0'),void();
	while(x)c[++c[0]]=x%10,x/=10;
	while(c[0])pc(c[c[0]--]+'0');
}
int n,Q;
int s[200005],l[200005],r[200005];
long long a[200005],sum[200005];
long long ans[200005];
struct opr {
	int place;
	long long val;
};
vector<opr> vec[200005];
struct que {
	int l,r,id;
};
vector<que> q[200005];
struct Segment_tree {
	struct node {
		int l,r,len;
		long long stag1,stag2;
		long long val1,val2;
	} v[1200005];
	void push_sum1(int rt,long long val) {
		v[rt].stag1+=val;
		v[rt].val1+=val*v[rt].len;
	}
	void push_sum2(int rt,long long val) {
		v[rt].stag2+=val;
		v[rt].val2+=val*v[rt].len;
	}
	void push_down(int rt) {
		if(v[rt].stag1) {
			push_sum1(rt<<1,v[rt].stag1);
			push_sum1(rt<<1|1,v[rt].stag1);
			v[rt].stag1=0;
		}
		if(v[rt].stag2) {
			push_sum2(rt<<1,v[rt].stag2);
			push_sum2(rt<<1|1,v[rt].stag2);
			v[rt].stag2=0;
		}
	}
	void push_up(int rt) {
		v[rt].val1=v[rt<<1].val1+v[rt<<1|1].val1;
		v[rt].val2=v[rt<<1].val2+v[rt<<1|1].val2;
	}
	void build(int rt,int l,int r) {
		v[rt].l=l,v[rt].r=r,v[rt].len=v[rt].r-v[rt].l+1;
		if(l==r) {
			v[rt].val1=0,v[rt].val1=0;
			return;
		}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid);
		build(rt<<1|1,mid+1,r);
		push_up(rt);
	}
	void add1(int rt,int l,int r,long long val) {
		if(l<=v[rt].l&&v[rt].r<=r) {
			push_sum1(rt,val);
			return;
		}
		int mid=(v[rt<<1].r);
		push_down(rt);
		if(l<=mid)add1(rt<<1,l,r,val);
		if(mid<r)add1(rt<<1|1,l,r,val);
		push_up(rt);
	}
	void add2(int rt,int l,int r,long long val) {
		if(l<=v[rt].l&&v[rt].r<=r) {
			push_sum2(rt,val);
			return;
		}
		int mid=(v[rt<<1].r);
		push_down(rt);
		if(l<=mid)add2(rt<<1,l,r,val);
		if(mid<r)add2(rt<<1|1,l,r,val);
		push_up(rt);
	}
	long long ask1(int rt,int l,int r) {
		if(l<=v[rt].l&&v[rt].r<=r)return v[rt].val1;
		push_down(rt);
		int mid=(v[rt<<1].r);
		if(r<=mid)return ask1(rt<<1,l,r);
		if(mid<l)return ask1(rt<<1|1,l,r);
		return ask1(rt<<1,l,r)+ask1(rt<<1|1,l,r);
	}
	long long ask2(int rt,int l,int r) {
		if(l<=v[rt].l&&v[rt].r<=r)return v[rt].val2;
		push_down(rt);
		int mid=(v[rt<<1].r);
		if(r<=mid)return ask2(rt<<1,l,r);
		if(mid<l)return ask2(rt<<1|1,l,r);
		return ask2(rt<<1,l,r)+ask2(rt<<1|1,l,r);
	}
} S;
int main() {
	n=getint();
	Q=getint();
	for(int i=1; i<=n; i++)a[i]=getint(),sum[i]=sum[i-1]+a[i];
	for(int i=1; i<=Q; i++) {
		int t=getint(),l=getint(),r=getint();
		ans[i]=sum[r]-sum[l-1];
		q[t].push_back({l,r,i});
	}
	for(int i=1; i<=n; ++i) {
		while(s[0]&&a[i]>=a[s[s[0]]])r[s[s[0]--]]=i;
		l[i]=s[s[0]],s[++s[0]]=i;
	}
	for(int i=1; i<=n; ++i) {
		if(l[i]) {
			vec[i-l[i]].push_back({i,a[l[i]]-a[i]});
			if(r[i])vec[r[i]-l[i]].push_back({r[i],a[i]-a[l[i]]});
		}
	}
	S.build(1,-n,n);
	for(int i=1; i<=n; i++) {
		int vsz=vec[i].size(),qsz=q[i].size();
		for(int j=0; j<vsz; j++)S.add1(1,-n,vec[i][j].place-i,vec[i][j].val),S.add2(1,-n,vec[i][j].place-1,vec[i][j].val);
		for(int j=0; j<qsz; j++)ans[q[i][j].id]+=S.ask1(1,q[i][j].l-i,q[i][j].r-i)-S.ask2(1,q[i][j].l,q[i][j].r);
	}
	for(int i=1; i<=Q; i++)wrt(ans[i]),pc('\n');
	fwrite(wb,1,p2,stdout);
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：6)

写一个非常清新的分块做法。做的时候就完全没想到 log 的做法，只能去瞎想根号。

首先考虑 $L=1,R=N$ 怎么做。每个 $s_i$ 在每时刻会覆盖一段区间。我们发现每个 $s_i$ 覆盖的区间会不断右移。$a_i$ 表示 $s_i$ 覆盖的区间左端点开始动的时间，即最大的 $j$ 满足 $s[i-j,i)\le s_i$；同理 $b_i$ 表示区间右端点停止的时间，即最大的 $j$ 满足 $s(i,i+j]<s_i$。考虑 $f_t$ 表示 $t$ 时间的和，那么 $s_i$ 对 $f_t$ 的贡献是一个类似梯形的一个关于 $t$ 的函数，我们可以轻易通过 $a_i,b_i$ 找到 $i$ 对 $f$ 的二阶差分的贡献的位置。

然后考虑分块，同理我们也可以对于每个块，处理出它的 $f$，遍历每个 $i$ 看 $s_i$ 对这个块的 $f$ 的二阶差分的贡献的位置。具体而言，对于块 $[L,R]$，块左边的贡献为 $L-i$ 处 $+s_i$，$L-i+a_i+1$ 处 $-s_i$，$\min(R-i,b_i)+1$ 处 $-s_i$，$\min(R-i,b_i)+a_i+2$ 处 $+s_i$。块内部点的贡献后面两个是相同的，前面的是 $0$ 处 $+s_i$ 以及 $a_i+1$ 处 $+s_i$。

复杂度 $O(m\sqrt n)$。下面写丑了，求 $a,b$ 单调栈就可以了。

```cpp
const int N=4e5+5,inf=0x3f3f3f3f;
int n,Q,B,s[N],l[N],r[N],t[N],d[N],a[N],b[N],f[20][N],ans[N];

int qry(int r,int k) {
  ++k; k=min(k,r); int h=__lg(k);
  return max(f[h][r-k+1],f[h][r-(1<<h)+1]);
}
void work(int L,int R) {
  rep(i,0,n+1) d[i]=0;
  rep(i,1,R) {
    if(i+b[i]<L) continue;
    else if(i<L) d[L-i]+=s[i], d[L-i+a[i]+1]-=s[i];
    else d[0]+=s[i], d[a[i]+1]-=s[i];
    d[min(R-i,b[i])+1]-=s[i];
    d[min(R-i,b[i])+a[i]+2]+=s[i];
  }
  rep(i,1,n) d[i]+=d[i-1];
  rep(i,1,n) d[i]+=d[i-1];
  rep(i,1,Q) {
    int x=max(L,l[i]), y=min(R,r[i]);
    if(x>y) continue;
    else if(x==L&&y==R) ans[i]+=d[t[i]];
    else {rep(j,x,y) ans[i]+=qry(j,t[i]);}
  }
}

signed main() {
  n=read(), Q=read(), B=sqrt(n);
  rep(i,1,n) s[i]=read(), f[0][i]=s[i];
  s[n+1]=inf; f[0][n+1]=inf;
  rep(h,1,18) rep(i,1,n) if(i+(1<<h)-1<=n+1)
    f[h][i]=max(f[h-1][i],f[h-1][i+(1<<h-1)]);
  rep(i,1,n) {
    int l=1, r=i; a[i]=n+1;
    while(l<=r) {
      int mid=l+r>>1;
      if(qry(i,mid)<=s[i]) l=mid+1;
      else r=mid-1, a[i]=mid-1;
    }
    l=1, r=n-i+1; b[i]=n+1;
    while(l<=r) {
      int mid=l+r>>1;
      if(qry(i+mid,mid-1)<s[i]) l=mid+1;
      else r=mid-1, b[i]=mid-1;
    }
  }
  rep(i,1,Q) t[i]=read(), l[i]=read(), r[i]=read();
  for(int pos=1;pos<=n;pos+=B) work(pos,min(n,pos+B-1));
  rep(i,1,Q) printf("%lld\n",ans[i]);
  return 0;
}
```

---

## 作者：zzw4257 (赞：4)

>给定一个初始序列 $\{a_i\}$ ,定义 $\displaystyle a^{[T]}_{i}=\max_{j=\max\{1,i-T+1\}}^i\{a_i\}$
多次询问$\displaystyle \sum_{i=l}^ra^{[T]}_{i}$

考虑我们不看位置而是看值被谁覆盖了

或者这样说我们在时间轴上如果$T$时刻内$i$位置**存在一个时刻值**从$a$变成了$b$那么在$t-v$图像上就在$(T,i)$初加上一个$b-a$

设$L_i=\max\{j|j<i,a_{j}>a_i\}$,$R_i=\min\{j|j>i,a_{j}>a_i\}$

则以$i$为右端点的区间当左端点$\in[i,R_i)$时$a_i$会变成$a_{L_i}$

图可以自己画下

化简答案，考虑每个位置，对$i$位置贡献分别考虑询问差分后的情况$(t,[1,x])$为$(a_{L_i}-a_i)(\min\{x,L_i+t\}-\min\{x,i-1\})$

然后化法就千奇百怪了，原则是把询问和位置独立，询问和询问分类(指去掉$\min\{\}$)

因为我懒得把化简结果写完就不放代码了

---

## 作者：takanashi_mifuru (赞：3)

我从来没有想过这个专栏名字真的能和题目名字这么契合。。

---

开题不会做，数据范围根号能过，先想想分块。

首先这个东西转化一下就是时刻 $k$ 的时候第 $i$ 个点变成往前数 $k+1$ 个数的最大值。

考虑分块之后变成了整块和散块，散块可以 ST 表直接查询，问题就是整块。

考虑如果我们能对第 $i$ 个整块求出其在第 $j$ 个时刻的和就可以了。

如果要维护每个点的变化这是不可能求出的，我们考虑只考虑这个块，如果块外面有一个神秘权值想要影响进来的话，他必须打过第一个点，这意味着每次从外面进来的权值必然是递增的，这启发我们暴力计算块内贡献再考虑块外贡献。

具体地，先用 ST 表暴力算出 $j$ 在块长以下的时候的答案，然后考虑这个时候这个块里必然是一个单谷的，每次操作相当于是第一个点和前面的打架，赢的加入，然后谷前面的区间整体右移，再把谷丢掉。

这个东西是很好实现的，所以就做完了。

当然 256 兆肯定存不下，逐块处理就可以了。

时间复杂度 $O(n\sqrt n)$，空间复杂度 $O(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define ll long long
#define rep(i, f, t) for (int i = (f), ed##i = (t); i <= ed##i; ++i)
#define re(i, t) rep (i, 1, t)
#define per(i, t, f) for (int i = (t), ed##i = (f); i >= ed##i; --i)
#define ste(i, f, t, s) for (int i = (f), ed##i = (t); i <= ed##i; i += s)
#define each(i, x) for (auto& i : (x))
#define nxt(i, f, g) for (int i = g.h[f]; i; i = g.e[i].n)
#define dbg(x) (cerr << "(dbg) " << #x " = " << (x) << '\n')
#define umod(x) ((x) >= mo && ((x) -= mo))
#define dmod(x) ((x) < 0 && ((x) += mo))
#define up(x, y) (((x) < (y)) && ((x) = (y)))
#define down(x, y) (((x) > (y)) && ((x) = (y)))
#define y1 y1__
namespace FastIO {
    const int SZ=(1<<23)+1;
    struct I {
        char ibuf[SZ],*iS,*iT,c;int f,_eof;FILE*fi;
        I(FILE*f):fi(f){}
        inline char Gc(){return iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SZ,fi),(iS==iT?EOF:*iS++)):*iS++;}
        inline ll operator()(){ll x;operator()(x);return x;}
        inline I&operator()(char&x){x=Gc();return*this;}
        inline I&operator()(char*s){for(c=Gc();c<32||c>126||c==' ';)c=Gc();for(;c>31&&c<127&&c!=' '&&c!='\n'&&c!='\r';++s,c=Gc())*s=c;*s=0;return*this;}
        template<class T>inline I&operator()(T&x){_eof=0;for(f=1,c=Gc();(c<'0'||c>'9')&&!_eof;c=Gc()){if(c=='-')f=-1;_eof|=c==EOF;}for(x=0;c<='9'&&c>='0'&&!_eof;c=Gc())x=x*10+(c&15),_eof|=c==EOF;x*=f;return*this;}
        template<class T>I&operator()(T*x,const int&n,const int&st=1){rep(i,st,n){operator()(x[i]);}return*this;}
    } in(stdin);
    struct O {
        char obuf[SZ],*oS=obuf,*oT=oS+SZ-1,qu[55];int f,qr;FILE*fi;
        O(FILE*f):fi(f){}
        ~O(){Flush();}
        inline void Flush(){fwrite(obuf,1,oS-obuf,fi),oS=obuf;}
        inline O&operator()(char x){*oS++=x;if(oS==oT)Flush();return*this;}
        inline O&operator()(const char*s){int len=strlen(s);for(f=0;f<len;++f)operator()(s[f]);return*this;}
        template<class T>inline O&operator()(T x){if(!x)operator()('0');if(x<0)operator()('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)operator()(qu[qr--]);return*this;}
        template<class T>O&operator()(T*x,const int&n,const char&ed=' ',const int&st=1){rep(i,st,n)operator()(x[i])(ed);return*this;}
    } out(stdout);
}
using FastIO::in;using FastIO::out;
// #define int long long
// using namespace std;
int n,q;
int a[200005];
struct node{
    int tim,lt,rt;
}Q[200005];
long long ans[200005];
int Block,num;
int st[200005];
int ed[200005];
int belone[200005];
int L[200005];
int stk[200005];
int top;
class rmq{
    public:
    int ST[200005][20];
    int lg[200005];
    void init(int a[],int n){
        lg[0]=-1;
        for(int i=1;i<=n;i++){
            lg[i]=lg[i/2]+1;
        }
        for(int i=1;i<=n;i++){
            ST[i][0]=a[i];
        }
        for(int j=1;j<=18;j++){
            for(int i=1;i+(1<<j)-1<=n;i++){
                ST[i][j]=std::max(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
            }
        }
        return;
    }
    int query(int lt,int rt){
        int len=rt-lt+1;
        return std::max(ST[lt][lg[len]],ST[rt-(1<<lg[len])+1][lg[len]]);
    }
}P;
long long need[200005];
signed main(){
    in(n)(q);
    for(int i=1;i<=n;i++){
        in(a[i]);
    }
    P.init(a,n);
    for(int i=1;i<=q;i++){
        int tim,lt,rt;
        in(tim)(lt)(rt);
        Q[i]=node{tim,lt,rt};
    }
    for(int i=n;i>=1;i--){
        while(top&&a[stk[top]]<a[i]){
            L[stk[top]]=i;
            top--;
        }
        stk[++top]=i;
    }
    Block=sqrt(n);
    num=(n+Block-1)/Block;
    for(int i=1;i<=num;i++){
        st[i]=(i-1)*Block+1;
        ed[i]=std::min(i*Block,n);
        for(int j=st[i];j<=ed[i];j++){
            belone[j]=i;
        }
    }
    for(int i=1;i<=num;i++){//处理第Block个块的答案，然后枚举每个询问录入答案。
        for(int j=0;j<=n;j++)need[j]=0;
        for(int k=st[i];k<=ed[i];k++){
            int Max=0;
            for(int j=0;j<=Block;j++){
                if(k>j)Max=std::max(Max,a[k-j]);
                need[j]+=Max;
            }
        }
        int S=st[i],T=st[i]-1;
        int Min=2e9,mini=-1;
        for(int k=st[i];k<=ed[i];k++){
            stk[++T]=P.query(std::max(k-Block,1),k);
        }
        int posL=-1,posR=-1;
        for(int i=S;i<T;i++){
            if(stk[i]<stk[i+1]){//以点i为谷底
                posL=i,posR=i+1;
                break;
            }
        }
        if(posL==-1)posL=T,posR=T+1;
        int seta=P.query(std::max(st[i]-Block,1),st[i]);
        for(int j=Block+1;j<=n;j++){
            if(j<st[i]){//仍在取用新的贡献点
                seta=std::max(seta,a[st[i]-j]);
                stk[--S]=seta;
            }
            //永远不丢掉第一个，如果最小值是第一个那就不做
            need[j]=need[j-1];
            if(posR>T){
                if(posL==S){//不丢第一个
                    continue;
                }
                need[j]+=stk[S]-stk[posL--];
            }
            else{
                if(stk[posL]<stk[posR]){
                    if(posL==S)continue;
                    need[j]+=stk[S]-stk[posL--];
                }
                else{
                    need[j]+=stk[S]-stk[posR++];
                }
            }
        }
        for(int j=1;j<=q;j++){
            if(Q[j].lt<st[i]&&Q[j].rt>ed[i]){
                ans[j]+=need[Q[j].tim];
            }
        }
        //现在stk是单谷的，每次就会丢掉谷的权值，也就是最小值。
    }
    for(int i=1;i<=q;i++){
        int lt=Q[i].lt,rt=Q[i].rt;
        int L=belone[lt];
        int R=belone[rt];
        if(L==R){
            for(int j=lt;j<=rt;j++){
                ans[i]+=P.query(std::max(j-Q[i].tim,1),j);
            }
            continue;
        }
        for(int j=lt;j<=ed[L];j++){
            ans[i]+=P.query(std::max(j-Q[i].tim,1),j);
        }
        for(int j=st[R];j<=rt;j++){
            ans[i]+=P.query(std::max(j-Q[i].tim,1),j);
        }
    }
    for(int i=1;i<=q;i++){
        out(ans[i])('\n');
    }
    return 0;
}
```

---

## 作者：oliver326 (赞：2)

这篇题解非正解，但是在此时仍获得了最优解（注：已经被同桌抢了），如果有意卡可以卡到 $O(n^2)$。仅仅是开拓一下思路。

介绍一下题意：$i$ 点的数值在 $t$ 时刻是 $\max(a_{\max(i-t,1)},\dots,a_i)$，多次询问某时刻的区间和。

首先这个题没有强制在线，并且多组输入并不保证 $t$ 不断增加。很显然让时间顺序推进肯定有好处，所以离线一下。

区间求和是简单问题，树状数组就足以维护。现在考虑这个多次的区间最值如何更新。

$t$ 不断增大的过程中，数组中的值会发生改变。而改变的条件是当前位置旁边有距离不超过 $t$ 的、更大的数值。很自然的想到预处理出每个点左边最近的比它大的值的位置，也就是[【模板】单调栈](https://www.luogu.com.cn/problem/P5788)。

上面说了，距离越近的两个点，会更早的被连接起来，也就是说需要我们更早得维护和更新。于是我们想到用优先队列来维护每个点的值下一次变大的时间，这个时间越早的必然会被先更新。并且由于会有比更新这个点值的那个值更大的值，所以在从优先队列队首取出一个点更新后可能还要在优先队列中加入下一个能更新这个点的位置。这也是为啥这个算法卡一卡就是 $O(n^2)$。

比如说我们给出一个单调递减的序列，那么一个点左边的所有点都可以更新该点的值，那么每个点都会被更新 $O(n)$ 次。模拟赛考场上，我发扬人类智慧，特判一个数列是否单调递减。对于单调递减的数列，$i$ 点最大值显然是 $a_{i-t}$，这个问题就又变的可以直接维护了。数据很水，此做法已经获得了最优解。

[提交记录](https://www.luogu.com.cn/record/177062771)

经过上面做法的启发，我们又发现：其实在 $i$ 点往左更新 $t$ 个时刻的结果，和在 $i-t$ 点往右更新 $t$ 个时刻的结果相同，而往左更新会被单调递减序列或大量递减的数据卡掉，这种情况下不妨用往右更新来处理。

当然这种做法还是可以被卡的，但我认为出题人应该不会考虑到如此鬼畜的做法，也就不会为此造一些奇葩数据吧，那我们就骗到分了。希望给大家带来了快乐。

[提交记录](https://www.luogu.com.cn/record/177153770)

---

## 作者：Delov (赞：2)

我们考虑维护增量，将每一个位置与前边第一个大于它的位置连边，边的权值为大减小，那么我们可以得到一个森林，发现时间线每增加一，就是在树上将每条边的权值向下传递一次，或者可以理解为每条边对应着一个一次函数，这个一次函数在某个位置，并且有限制的定义域。一条边能贡献的位置一定是连续的一段，我们把每条边的贡献离线下来，然后按照时间轴扫。

设一条边的贡献为一个四元组的形式 $(p,t,te,d)$ 表示这条边从第 $p$ 个位置，第 $t$ 秒开始 产生贡献，第 $te$ 秒时就没有了贡献。于是一次查询实际上就是查询所有的边对查询的位置造成的贡献，考虑把询问差分成求 $l-1$ 和 $r$ 两个前缀，这样就少了一个边界限制。于是对于一个询问 $(x,i)$，即询问第i秒时x位置的前缀和，一条边的贡献就是

$$
d \times (\min(p+i-t,x)-\min(p,x))
$$
(目前这个式子是不严谨的，后面会说一点细节)  

式子的意义就是考虑当前这条边已经扩展到了哪个位置，终点与起点作差算出来扩展了多少个位置，取 $\min$ 是去掉一些不合法的边。  

首先，这个式子只对还为终止贡献的边有效，也就是 $te$ 大于当前时间的边，如果一条边已经终止贡献，那么其的贡献形式就变成了一个常函数，直接把它区间加到序列上就行。  

其次，对于上边这个式子，我们很完美的把不合法的部分去掉，但是左边的 $\min$ 是终点，右边的 $\min$ 是起点，对于合法的边，我们算区间长度时并没有加一，于是需要特殊考虑一下。

对于上边这个式子，我们把左边的 $\min$ 里的 $i$ 提出来，变成
$$
d \times (i+\min(p-t,x-i)-\min(p,x))
$$

这样询问的时间就与边无关了，我们就可以静态的维护一些东西。由于取 $\min$并不太好搞，于是我们考虑分情况讨论 $\min$ 到底取了谁，用两棵线段树维护 $(p-t) \times d$，$p \times d$，线段树的下标就分别是 $p$ 和 $p-t$，然后对于两种下标，再开两棵线段树维护每个位置上的 $d$，然后我们就可以讨论 $\min$ 取哪一项，然后取出对应的树上的信息算就行，注意当一条边合法的时候，还需要维护 $d$ 的下标为 $p-t$ 那棵树的合法的那一部分再加一次，也就是算区间长度时的那个加一。

纯文字描述比较乏力，不懂可以看代码。

## code

```cpp


#include <bits/stdc++.h>
typedef long long ll;typedef unsigned long long ull; typedef double db;typedef long double ldb;
#define fre(x) freopen(#x ".in","r",stdin),freopen(#x ".out","w",stdout)
#define Rep(i,a,b) for(int i=a;i<=b;++i) 
#define Dwn(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define mair make_pair
#define fir first
#define sec second
#define int ll
using namespace std;

const int maxn=5e5+10,LN=-maxn+8,RN=maxn-8,INF=1e9+20051107; 

#define gc if(++ip==ie)fread(ip=buf,1,SZ,stdin)
const int SZ=1<<21;char buf[SZ],*ie=buf+SZ,*ip=ie-1;
inline int read(){ gc;while(*ip<'-')gc; bool f=*ip=='-';if(f)gc; int x=*ip&15;gc; while(*ip>'-'){x*=10;x+=*ip&15;gc;} return f ? -x : x; }
struct Seg{
	ll tr[maxn<<2],lazy[maxn<<2];
	void Pushup(int rt){tr[rt]=tr[rt<<1]+tr[rt<<1|1];}
	void Update(int rt,int l,int r,ll w){ tr[rt]+=(r-l+1)*w;lazy[rt]+=w; }
	void Pushdown(int rt,int l,int r){
		int mid=(l+r)>>1;
		Update(rt<<1,l,mid,lazy[rt]),Update(rt<<1|1,mid+1,r,lazy[rt]),lazy[rt]=0;
	}
	void Modify(int rt,int l,int r,int s,int t,ll w){
		if(s<=l && t>=r)return Update(rt,l,r,w);
		int mid=(l+r)>>1;
		if(lazy[rt])Pushdown(rt,l,r);
		if(s<=mid)Modify(rt<<1,l,mid,s,t,w);
		if(t>mid)Modify(rt<<1|1,mid+1,r,s,t,w);
		Pushup(rt);
	}
	int Query(int rt,int l,int r,int s,int t){
		if(!tr[rt])return 0;
		if(s<=l && t>=r)return tr[rt];
		int mid=(l+r)>>1,res=0;
		if(lazy[rt])Pushdown(rt,l,r);	
		if(s<=mid)res+=Query(rt<<1,l,mid,s,t);
		if(t>mid)res+=Query(rt<<1|1,mid+1,r,s,t);
		return res;
	}
}KA,KB,KxA,KxB,C;

int n,q;ll a[maxn>>1],ans[maxn>>1];
int L[maxn>>1],R[maxn>>1];

struct Ver{ int opt,p,t,d; };

vector<pii>Q[maxn>>1];
vector<Ver>Op[maxn>>1];

int st[maxn>>1],top;

void Sol(int Tim){
	for(auto it : Op[Tim]){
		if(it.opt==1){
			KxA.Modify(1,LN,RN,it.p,it.p,it.d);
			KxB.Modify(1,LN,RN,it.p-it.t,it.p-it.t,it.d);
			KA.Modify(1,LN,RN,it.p,it.p,it.p*it.d);
			KB.Modify(1,LN,RN,it.p-it.t,it.p-it.t,(it.p-it.t)*it.d);
		}else{
			KxA.Modify(1,LN,RN,it.p,it.p,-it.d);
			KxB.Modify(1,LN,RN,it.p-it.t,it.p-it.t,-it.d);
			KA.Modify(1,LN,RN,it.p,it.p,-it.p*it.d);
			KB.Modify(1,LN,RN,it.p-it.t,it.p-it.t,-(it.p-it.t)*it.d);
			C.Modify(1,1,n,it.p,it.p+Tim-it.t-1,it.d);
		}
	}
	for(auto it : Q[Tim]){
		int x=it.fir;if(x==0)continue;
		ll res=Tim*KxA.tr[1]+a[x];
		res+=KB.Query(1,LN,RN,LN,x-Tim);
		res+=KxA.Query(1,LN,RN,LN,x);
		res-=KA.Query(1,LN,RN,LN,x);
		res+=KxB.Query(1,LN,RN,x-Tim+1,RN)*(x-Tim);
		res-=KxA.Query(1,LN,RN,x+1,RN)*x;
		res+=C.Query(1,1,n,1,x);
		if(it.sec>0)ans[it.sec]+=res;
		else ans[-it.sec]-=res;
	}
}

void solve(){//fre(o);
	n=read(),q=read();
	Rep(i,1,n)a[i]=read();
	Rep(i,1,n){
		while(top && a[i]>=a[st[top]])R[st[top--]]=i;
		L[i]=st[top];
		st[++top]=i;
	}
	while(top)R[st[top--]]=n+1;
	Rep(i,1,n)if(L[i]){
		int t=i-L[i],d=a[L[i]]-a[i],tx=R[i]-i;
		Op[t].push_back(Ver{1,i,t,d});
		Op[t+tx].push_back(Ver{-1,i,t,d});
	}
	Rep(i,1,q){
		int t,l,r;
		t=read(),l=read(),r=read();
		Q[t].push_back(mair(l-1,-i));
		Q[t].push_back(mair(r,i));
	}
	Rep(i,1,n)a[i]+=a[i-1];
	Rep(i,1,n)Sol(i);
	Rep(i,1,q)printf("%lld\n",ans[i]);
}

#undef int 
int main (){ return solve(),0; }


```

---

## 作者：Felix72 (赞：1)

差分好题，虽然只用树状数组就能使实现，但是思维难度不低。

如果把题目中的每个时间点的状态记录下来，我们就会得到一个二维数组。每个询问相当于求一个长为一的矩形的和。对于这个大矩阵，直接维护肯定是不行的，但是我们发现可以离线，再从左往右扫一遍，这样就只用维护当前位置的每个历史版本了。

我们发现，原来每个数组在这个矩阵内产生了一个类似平行四边形的东西。那么我们分直线和斜线分别维护，对离线询问拆成两个离线询问即直线和斜线，就能解决单点查询问题。

那么如何把单点查询变为区间查询？类似区修区查树状数组，我们用整体乘若干倍减去每个点乘下标，求出一个前缀，再用两个前缀差分出所求区间。对于斜线的修改，我们把区间修改换为在差分数组上区间修改，就能做到插入等差数列了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 200010;
int n, m, a[N], l[N], r[N], sta[N], top;
long long ans[N];
struct BIT
{
	long long c[2][N * 2];
	inline void add(int id, int pos, int num)
	{
		for(int i = pos; i <= n * 2; i += lowbit(i))
			c[id][i] += num;
	}
	inline long long ask(int id, int pos)
	{
		long long ans = 0;
		for(int i = pos; i; i -= lowbit(i)) ans += c[id][i];
		return ans;
	}
	inline void insert(int l, int r, int num)
	{
		add(0, l, num), add(0, r + 1, -num);
		add(1, l, l * num), add(1, r + 1, -num * (r + 1));
	}
	inline long long sum(int l, int r)
	{
		if(l > r) return 0;
		return ((r + 1) * ask(0, r) - ask(1, r)) - (l * ask(0, l - 1) - ask(1, l - 1));
	}
};
BIT T1, T2, T3, T4;
int n1, n2, tot;
struct node {int pos, from, to; long long num;};
node s1[N * 2], s2[N * 2];
struct query {int opt, tim, pos, id;} q[N * 2];
inline bool cmp1(node x, node y) {return x.pos < y.pos;}
inline bool cmp2(query x, query y) {return x.pos < y.pos;}
inline bool cmp3(query x, query y) {return x.pos - x.tim + 1 < y.pos - y.tim + 1;}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) cin >> a[i], l[i] = 0, r[i] = n + 1;
	for(int i = 1; i <= n; ++i)
	{
		while(top && a[sta[top]] < a[i]) r[sta[top]] = i, --top;
		sta[++top] = i;
	}
	top = 0;
	for(int i = n; i >= 1; --i)
	{
		while(top && a[sta[top]] <= a[i]) l[sta[top]] = i, --top;
		sta[++top] = i;
	}
	for(int i = 1; i <= n; ++i)
	{
		int l1 = n1, l2 = n2;
		int cur = l[i];
		if(!cur) s1[++n1].pos = i, s1[n1].from = 1, s1[n1].to = n + 1, s1[n1].num = a[i];
		else
		{
			if(cur < i - 1) s1[++n1].pos = i, s1[n1].from = 1, s1[n1].to = i - cur - 1, s1[n1].num = a[i];
			s2[++n2].pos = i - (i - cur - 1), s2[n2].from = i - cur, s2[n2].to = min({n + 1, i - cur + r[i] - i - 1}), s2[n2].num = a[i];
		}
		cur = r[i];
		if(cur > i + 1) s2[++n2].pos = i + 1, s2[n2].from = 1, s2[n2].to = cur - i - 1, s2[n2].num = -a[i];
		if(cur != n + 1)
		{
			s1[++n1].num = -a[i];
			s1[n1].pos = cur, s1[n1].from = cur - i;
			if(l[i] == 0) s1[n1].to = n + 1;
			else s1[n1].to = cur - l[i] - 1;
		}
	}
	for(int i = 1; i <= m; ++i)
	{
		int ti, x, y; cin >> ti >> x >> y;
		++ti;
		if(x > 1) q[++tot].opt = -1, q[tot].pos = x - 1, q[tot].tim = ti, q[tot].id = i;
		q[++tot].opt = 1, q[tot].pos = y, q[tot].tim = ti, q[tot].id = i;
	}
	sort(s1 + 1, s1 + n1 + 1, cmp1);
	sort(s2 + 1, s2 + n2 + 1, cmp1);
	sort(q + 1, q + tot + 1, cmp2);
	int at = 1;
	for(int i = 1; i <= tot; ++i)
	{
		while(at <= n1 && s1[at].pos <= q[i].pos)
		{
			T1.insert(s1[at].from, s1[at].to, s1[at].num);
			T2.insert(s1[at].from, s1[at].to, s1[at].num * s1[at].pos);
			++at;
		}
		ans[q[i].id] += q[i].opt * (T1.sum(q[i].tim, q[i].tim) * (q[i].pos + 1) - T2.sum(q[i].tim, q[i].tim));
	}
	sort(q + 1, q + tot + 1, cmp3);
	at = 1;
	for(int i = 1; i <= tot; ++i)
	{
		while(at <= n2 && s2[at].pos <= q[i].pos - q[i].tim + 1)
		{
			T3.insert(s2[at].from, s2[at].to, s2[at].num);
			T4.insert(s2[at].from, s2[at].to, s2[at].num);
			T4.insert(s2[at].from, s2[at].from, s2[at].num * (s2[at].pos + s2[at].from - 2));
			if(s2[at].to + 1 <= n + 1) T4.insert(s2[at].to + 1, s2[at].to + 1, -s2[at].num * (s2[at].to - s2[at].from + 1 + s2[at].pos + s2[at].from - 2));
			++at;
		}
		if(q[i].pos - q[i].tim + 1 >= 1)
			ans[q[i].id] += q[i].opt * (T3.sum(q[i].tim, q[i].tim) * (q[i].pos + 1) - T4.sum(1, q[i].tim));
	}
	for(int i = 1; i <= m; ++i) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：irris (赞：1)

> 树状数组 / **二维平面拆贡献** / 笛卡尔树断点求和 / **差分** / 扫描线

看似人畜无害，实则暗藏杀机。完全不会数据结构啊。/ll

不直接对着平面嗯差分了，咱来点暴力 $\log^2$。

我们考虑，**计算一个点对后续时刻的贡献**。我们可以单调栈求出 $L_i, R_i$ 表示 $i$ 之前 / 后第一个大于 / 大于等于 $i$ 的数的下标。

一个点产生的贡献如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/e64gmquk.png)

我们考虑一个很臭的想法：由于笛卡尔树的 **经典结论**，$\displaystyle\sum \min(R_i - i, i - L_i)$ 的和为 $\mathcal O(n\log n)$ 级别，不过显然卡不满（证明考虑启发式合并）。

所以就分类讨论暴力计算贡献喽。

1. $R_i - i \leq i - L_i$，这时可以直接转化为 $R_i - i$ 个**竖线加**，一些**横线查**。**对询问差分**，直接扫描线即可解决问题。
2. $i - L_i \lt R_i - i$。这时我们转化为 $i - L_i$ 个斜线加，什么玩意这是？关键的一步：考虑进行坐标系 **转换**，让 $(x, y) \Rightarrow (x - y, y)$（这一步非常重要！台上讲的老哥轻描淡写，我想了好几天 /ng），那么同样变成了竖线加，横线查，处理方式相同。

对这些部分分开维护即可，封装写起来码量不大。时间复杂度极小常数 $\mathcal O(n\log^2 n)$。

代码：

```cpp
#include <bits/stdc++.h>

namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
}; using namespace FastIO;

struct Oper {
	int x, l, r, v;
	Oper () {}
	Oper (int X, int L, int R, int V) : x(X), l(L), r(R), v(V) {}
	const bool operator < (const Oper& k) const { return x < k.x; }
};
struct Query {
	int id, l, r, y;
	Query () {}
	Query (int I, int L, int R, int Y) : id(I), l(L), r(R), y(Y) {}
};

#define MAXN 200005
struct Bit {
	private :
		int N = 0;
		long long t[MAXN];
	public :
		Bit () { memset(t, 0, sizeof t); }
		Bit (int n) : N(n) { memset(t, 0, sizeof t); }
		inline void setBound(int n) { N = n; }
		void add(int l, int r, int v) { while (l <= N) t[l] += v, l += l & (-l); ++r; while (r <= N) t[r] -= v, r += r & (-r); }
		long long query(int p) { long long ans = 0; while (p) ans += t[p], p -= p & (-p); return ans; }
};

int N, Q;
std::vector<long long> solve(std::vector<Oper> op, std::vector<Query> q) {
	std::vector<std::pair<int, int>> t; Bit s(N);
	for (Query u : q) t.push_back({u.l - 1, -u.id - 1}), t.push_back({u.r, u.id + 1});
	std::sort(op.begin(), op.end()), std::sort(t.begin(), t.end());
	std::vector<long long> ans((int)q.size(), 0);
	for (int i = 0, co = 0, no = (int)op.size(), ct = 0, nt = (int)t.size(); ct < nt; ++i) {
		while (co < no && op[co].x == i) s.add(op[co].l, op[co].r, op[co].v), ++co;
		while (ct < nt && t[ct].first == i) if (t[ct].second > 0) 
			ans[t[ct].second - 1] += s.query(q[t[ct].second - 1].y), ++ct;
		else ans[-t[ct].second - 1] -= s.query(q[-t[ct].second - 1].y), ++ct;
	}
	return ans;
}

int a[MAXN], L[MAXN], R[MAXN];
int main() {
	N = read<int>(), Q = read<int>();
	for (int i = 1; i <= N; ++i) a[i] = read<int>();
	std::stack<int> pre; for (int i = N; i; --i) {
		while (!pre.empty() && a[pre.top()] < a[i]) L[pre.top()] = i, pre.pop();
		pre.push(i);
	}
	std::stack<int> nxt; for (int i = 1; i <= N; ++i) {
		while (!nxt.empty() && a[nxt.top()] <= a[i]) R[nxt.top()] = i, nxt.pop();
		nxt.push(i);
	}
	for (int i = 1; i <= N; ++i) if (L[i] == 0) L[i] = -5 * N;
	for (int i = 1; i <= N; ++i) if (R[i] == 0) R[i] = N + 1;
	std::vector<Query> q0(Q), q1(Q);
	for (int i = 0, l, r, t; i < Q; ++i) {
		t = read<int>(), l = read<int>(), r = read<int>();
		q0[i] = Query(i, l, r, t), q1[i] = Query(i, l + N - t, r + N - t, t);
	}
	std::vector<Oper> t0, t1;
	for (int i = 1; i <= N; ++i) if (R[i] - i <= i - L[i]) 
		for (int j = i, l = 0, r = i - L[i] - 1; j < R[i]; ++j, ++l, ++r) 
			t0.push_back(Oper(j, std::max(l, 1), r, a[i]));
	else for (int j = i, l = 0, r = R[i] - i - 1; j > L[i]; --j, ++l, ++r) 
			t1.push_back(Oper(j + N, std::max(l, 1), r, a[i]));
	auto ans0 = solve(t0, q0), ans1 = solve(t1, q1);
	for (int i = 0; i < Q; ++i) print<long long>(ans0[i] + ans1[i], '\n');
	return 0;
}
```

---

## 作者：stjp (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P6881)
我们首先来康一康题目 ~~(有点糊了)~~：
![](https://cdn.luogu.com.cn/upload/image_hosting/18e30h03.png)
~~乍一看，就是一道线段树，可实际上呢，也就是一道线段树。~~

好了好了，切入正题。

---
这道题有两种思路：

**第一种：**
- 先以位置为横轴,时刻为数轴,写出一个矩阵,每一位分别对应每个时刻每个位置的权值.然后考虑每个位置对这里权值变化的贡献。
- 对于一个位置 $i$ ,它可以在之后的一段时间内覆盖后面一段权值更小的位置,直到碰到权值 $≥$ 它的位置后停止,设这个停止位置为 $nti$ (这个位置显然是 $i$ 后面第一个权值不小于 $i$ 的位置),那么在  $t∈[1,nti−i)$ 时刻第 $i+t$ 位置的权值会被覆盖为 $si$ .我们把上述的覆盖看做是先减去原来的值,然后加上现在的值,那么也就是 $i$ 号位会在 $t$ 时刻给 $i+t$ 号位加上 $si$ 。

- 然后考虑减权值部分.一个位置的权值显然是被往前走第一个权值更大的位置覆盖,记此位置为 $fti$ ,那么从 $fti$ 上的权值覆盖到 $i$ 开始,之后一段时间还会去依次覆盖后面的一些位置,直到到 $nti$ 这一位没有 $i$ 覆盖的贡献.形式化的讲,就是在 $t∈[i−fti,nti−fti)$ 时刻,第 $i+t−(i−fti)$ 位会减去原有权值,即 $si$ 。
- 可以发现上述的贡献总数是在 $O(n)$ 级别的.对于一个询问 $(t,l,r)$ ,先套路的拆成是 $(t,1,r)−(t,1,l−1)$ .然后现在一个 $(t,1,i)$ 就是在纵坐标为 $t$ 的一排里前 $i$ 位的和.现在我们把原来的对应每个时刻每个位置的权值的矩阵的相邻两行差分,就可以差分矩阵为前面讨论到的所有贡献的叠加,其中一种贡献在差分后的矩阵上是一段斜着的线段.另外现在的每个询问也就是对应区间的初值加一个前缀的矩阵的和
- 对于一个斜的线段,起始点和终止点分别为 $(x,y),(x′,y′)$ ,我们可以看成是一个正贡献点 $(x,y)$ 和一个负贡献点 $(x′+1,y′+1)$ 往右上方的贡献
- 对一个贡献点 $(x,y)$ ,设其权值为 $w$ ,对询问 $(t,1,i)(i≥x,t≥y)$ 的贡献为 $w∗min(t−y+1,i−x+1)$ .那么可以发现取出 $(i,t)$ 点所在的左下-右上对角线后,取到 $t−y+1$ 这一部分的贡献点全在对角线上方,反之全在对角线下方.所以对于对角线进行扫描线,先把所有贡献点放在对角线下方的贡献里,然后扫到当前对角线后把线上的贡献点贡献一到对角线上方的贡献里;对于端点经过当前对角线的询问,只要查询前缀 $i$ 的下方贡献以及前缀 $t$ 的上方贡献即可.我们把贡献记在树状数组里,如果树状数组上第 $i$ 为权值为 $wi$ ,那么对询问前缀 $n$ 的贡献为 $(n−i+1)wi$ ,把贡献拆为 $(n+1)wi$ 和 $−iwi$ 两部分,那么树状数组分别维护 $∑wi$ , $∑iwi$ 即可

---
最后，代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 200010;
struct Query {
    int l, r, t, id;
    ll ans;
} q[MAXN];
struct Event {
    int pos, k, b, t;
    Event(int u = 0, int v = 0, int w = 0, int z = 0) {
        pos = u, k = v, b = w, t = z;
    }
} e[MAXN * 4];
int n, qu, cnt, a[MAXN], lg[MAXN], pre[MAXN], nx[MAXN], st[MAXN][20];
ll sum[2][MAXN * 4];
stack <int> s;
bool cmp1(Query a, Query b) {
    return a.t < b.t;
}
bool cmp2(Query a, Query b) {
    return a.id < b.id;
}
bool cmp3(Event a, Event b) {
    return a.t < b.t;
}
int query(int l, int r) {
    l = max(l, 1);
    int k = lg[r - l + 1];
    return (a[st[l][k]] > a[st[r - (1 << k) + 1][k]] ? st[l][k] : st[r - (1 << k) + 1][k]);
}
void modify(int p, int l, int r, int pos, ll v, int k) {
    if (l == r) {
        sum[k][p] = v;
        return;
    }

    int mid = (l + r) >> 1;

    if (pos <= mid) {
        modify(p << 1, l, mid, pos, v, k);
    } else {
        modify((p << 1) | 1, mid + 1, r, pos, v, k);
    }

    sum[k][p] = sum[k][p << 1] + sum[k][(p << 1) | 1];
    return;
}
ll query(int p, int l, int r, int xl, int xr, int k) {
    if (xr < l || r < xl) {
        return 0;
    }

    if (xl <= l && r <= xr) {
        return sum[k][p];
    }

    int mid = (l + r) >> 1;
    return query(p << 1, l, mid, xl, xr, k) + query((p << 1) | 1, mid + 1, r, xl, xr, k);
}
int main() {
    scanf("%d%d", &n, &qu);
    lg[0] = -1;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        lg[i] = lg[i >> 1] + 1, st[i][0] = i;
    }

    for (int i = 1; i <= 18; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            st[j][i] = (a[st[j][i - 1]] > a[st[j + (1 << (i - 1))][i - 1]]
                        ? st[j][i - 1] : st[j + (1 << (i - 1))][i - 1]);
        }
    }

    for (int i = 1; i <= n; i++) {
        while (s.size() && a[i] >= a[s.top()]) {
            nx[s.top()] = i;
            s.pop();
        }

        pre[i] = (s.size() ? s.top() : 0);
        s.push(i);
    }

    for (int i = 1; i <= n; i++) {
        if (nx[i] == 0) {
            nx[i] = n + 1;
        }

        if (pre[i] == 0) {
            e[++cnt] = Event(i, 1, 1, 0);
            e[++cnt] = Event(i, 0, nx[i] - i, nx[i] - i);
        } else {
            e[++cnt] = Event(i, 1, 1, 0);

            if (i - pre[i] > nx[i] - i) {
                e[++cnt] = Event(i, 0, nx[i] - i, nx[i] - i);
                e[++cnt] = Event(i, -1, nx[i] - pre[i] - 1, i - pre[i]);
            } else if (i - pre[i] == nx[i] - i) {
                e[++cnt] = Event(i, -1, nx[i] - pre[i] - 1, i - pre[i]);
            } else {
                e[++cnt] = Event(i, 0, i - pre[i], i - pre[i]);
                e[++cnt] = Event(i, -1, nx[i] - pre[i] - 1, nx[i] - i);
            }

            e[++cnt] = Event(i, 0, 0, nx[i] - pre[i]);
        }
    }

    for (int i = 1; i <= qu; i++) {
        scanf("%d%d%d", &q[i].t, &q[i].l, &q[i].r);
        q[i].id = i;
    }

    sort(q + 1, q + qu + 1, cmp1);
    sort(e + 1, e + cnt + 1, cmp3);
    int cura = 1, curb = 1;

    for (int i = 0; i <= n; i++) {
        while (cura <= cnt && e[cura].t == i) {
            int tmp = e[cura].pos;
            modify(1, 1, n, tmp, 1ll * e[cura].k * a[tmp], 0);
            modify(1, 1, n, tmp, 1ll * e[cura].b * a[tmp], 1);
            cura++;
        }

        while (curb <= qu && q[curb].t == i) {
            int tmp = query(q[curb].r - i, q[curb].r);
            int nl = max(tmp, pre[tmp] == 0 ? 0 : pre[tmp] + i + 1);
            q[curb].ans += 1ll * (q[curb].r - nl + 1) * a[tmp];
            q[curb].ans += 1ll * query(1, 1, n, 1, tmp - 1, 0) * i + query(1, 1, n, 1, tmp - 1, 1);

            if (q[curb].l == 1) {
                curb++;
                continue;
            }

            q[curb].r = q[curb].l - 1;
            tmp = query(q[curb].r - i, q[curb].r);
            nl = max(tmp, pre[tmp] == 0 ? 0 : pre[tmp] + i + 1);
            q[curb].ans -= 1ll * (q[curb].r - nl + 1) * a[tmp];
            q[curb].ans -= 1ll * query(1, 1, n, 1, tmp - 1, 0) * i + query(1, 1, n, 1, tmp - 1, 1);
            curb++;
        }
    }

    sort(q + 1, q + qu + 1, cmp2);

    for (int i = 1; i <= qu; i++) {
        printf("%lld\n", q[i].ans);
    }

    return 0;
}


```


---

## 作者：7KByte (赞：0)

这题看起来人畜无害，非常小清新的 DS 题，但写起来就不会这么想了。

题目大意，给定一个长度为 $N$ 的序列 $S$ ，需要回答 $Q$ 次询问，每次询问 $\sum\limits_{L\le i\le R}\max\limits_{i-T\le j\le i}\{S_j\}$ 。

子任务 $1$ ，直接模拟，时间复杂度 $\mathcal{O}(QN^2)$ 。

子任务 $2$ ，$T_i$ 相等，直接算出 $T$ 时刻的序列，然后求一个前缀和即可。计算序列时可以单调队列做到 $\mathcal{O}(N)$ 。

子任务 $3$ ，$L_i=R_i$ ，单点询问，直接计算 $\max\limits_{L-T\le i\le L}\{S_i\}$ ，ST 表可以做到 $\mathcal{O}(N\log N+Q)$ 。

子任务 $4$，$1\le S_i\le 2$ 。

我们不妨列出一个表格，$S_{i,j}$ 表示时刻 $i$ ，序列第 $j$ 位的是 $1$ 还是 $2$ 。

先将整个表格用 $1$ 填充，然后发现如果第 $i$ 位为 $2$ ，那么表格中位于直线 $y=x-i$ 斜上方（包括）的且位置 $\ge i$ 的所有格子都被填上 $2$ 。

这就是扫描线模板，差分一下可以做到 $\mathcal{O}(N+Q\log N)$ 。

对于满分做法，我们考虑延续前面的思路。

对于每一个位置 $i$ 上的数，如果前面有比它大的数，那么它在表格中填充的部分一定是平行四边形，否则一定是一个直角梯形。

对于一个平行四边形，我们拆成三个在 $x$ 轴上的等腰直角三角形。

现在只用考虑三角形的情况。

我们可以用一条斜率为 $1$ 的直线和 $x$ 轴切出一个等腰直角三角形的一个角。

对于这个角的对边，我们再拆成一个等腰直角三角形和一个长方形。

长方形已经可以直接做了，这两个等腰直角三角形都具有可以向右无限扩展的特点，我们可以用两条直线表示，在形如 $y=x+b$ 的直线协下方，在形如 $y=a$ 的直线上方。

转化为差分，我们需要支持区间加和区间求和。可以树状数组再做一次差分，也可以直接线段树。

由于笔者写法比较丑需要负数下标，所以使用了线段树。时间复杂度 $\mathcal{O}((N+Q)\log N)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
#define int long long
using namespace std;
int n,m,s[N],sta[N],pre[N],nxt[N],ans[N],top;
typedef pair<int,int> Pr;
vector<Pr>c[N],d[N];
struct seg{
	struct node{
		int l,r,tag,sum;
	}a[N<<2];
	#define L a[x].l
	#define R a[x].r
	#define ls (x<<1)
	#define rs (ls|1)
	#define T a[x].tag
	#define S a[x].sum
	inline int g(int l,int r){return l+(r-l)/2;}
	void build(int x,int l,int r){
		L=l;R=r;S=T=0;
		if(l==r)return ;
		int mid=g(l,r);
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
	void pushup(int x,int val){T+=val;S+=(R-L+1)*val;}
	void down(int x){if(T)pushup(ls,T),pushup(rs,T),T=0;}
	void change(int x,int l,int r,int val){
		if(L>=l&&R<=r)pushup(x,val);
		else{
			down(x);int mid=g(L,R);
			if(mid>=l)change(ls,l,r,val);
			if(mid<r)change(rs,l,r,val);
			S=a[ls].sum+a[rs].sum;
		}
	}
	int ask(int x,int l,int r){
		if(L>=l&&R<=r)return S;
		down(x);int sum=0,mid=g(L,R);
		if(mid>=l)sum+=ask(ls,l,r);
		if(mid<r)sum+=ask(rs,l,r);
		return sum;
	}
}p,q;
void tri(int l,int r,int val){
	//cout<<"cc "<<l<<" "<<r<<" "<<val<<endl;
	if(l>r)return;
	c[0].push_back(make_pair(l,val));
	c[r-l+1].push_back(make_pair(l,-val));
	d[0].push_back(make_pair(r+1,-val));
	d[r-l+1].push_back(make_pair(r+1,val));
}
void par(int l,int r,int len,int val){
	int st=l-len+1;
	tri(st,r,val);tri(st,l-1,-val);tri(l+1,r,-val);
}
struct node{int t,l,r,op;bool operator<(const node o)const{return t<o.t;}}u[N];
signed main(){
	scanf("%lld%lld",&n,&m);int ll=-n-5,rr=n+5;
	rep(i,1,n)scanf("%lld",&s[i]);
	rep(i,1,n){
		while(top&&s[sta[top]]<=s[i])nxt[sta[top]]=i,top--;
		if(top)pre[i]=sta[top];else pre[i]=-n-2;
		sta[++top]=i;
	}
	rep(i,1,n)if(!nxt[i])nxt[i]=n+1;
	//rep(i,1,n)printf("ss %lld %lld \n",pre[i],nxt[i]);
	rep(i,1,n)par(i,nxt[i]-1,i-pre[i],s[i]);
	rep(i,1,m)scanf("%lld%lld%lld",&u[i].t,&u[i].l,&u[i].r),u[i].op=i;
	sort(u+1,u+m+1);int j=1;
	p.build(1,ll,rr);q.build(1,ll,rr);
	rep(t,0,n){
		//cout<<"st "<<t<<endl;
		for(int i=0;i<(int)c[t].size();i++){
			p.change(1,c[t][i].first,rr,c[t][i].second);
			//cout<<"Add A  "<<c[t][i].first<<" "<<c[t][i].second<<endl;
		}
		for(int i=0;i<(int)d[t].size();i++){
			q.change(1,d[t][i].first,rr,d[t][i].second);
			//cout<<"Add B  "<<d[t][i].first<<" "<<d[t][i].second<<endl; 
		}
		while(j<=m&&u[j].t==t){
			ans[u[j].op]=q.ask(1,u[j].l,u[j].r)+p.ask(1,u[j].l-t,u[j].r-t);
			j++;
		}
	}
	rep(i,1,m)printf("%lld\n",ans[i]);
	return 0;
}
```



---

