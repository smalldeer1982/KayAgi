# Tenzing and Triangle

## 题目描述

There are $ n $ pairwise-distinct points and a line $ x+y=k $ on a two-dimensional plane. The $ i $ -th point is at $ (x_i,y_i) $ . All points have non-negative coordinates and are strictly below the line. Alternatively, $ 0 \leq x_i,y_i, x_i+y_i < k $ .

Tenzing wants to erase all the points. He can perform the following two operations:

1. Draw triangle: Tenzing will choose two non-negative integers $ a $ , $ b $ that satisfy $ a+b<k $ , then all points inside the triangle formed by lines $ x=a $ , $ y=b $ and $ x+y=k $ will be erased. It can be shown that this triangle is an isosceles right triangle. Let the side lengths of the triangle be $ l $ , $ l $ and $ \sqrt 2 l $ respectively. Then, the cost of this operation is $ l \cdot A $ .The blue area of the following picture describes the triangle with $ a=1,b=1 $ with cost $ =1\cdot A $ .
  
   ![](https://espresso.codeforces.com/6c0866a02bd460b12e9d8d70663a9287aa4aea58.png)
2. Erase a specific point: Tenzing will choose an integer $ i $ that satisfies $ 1 \leq i \leq n $ and erase the point $ i $ . The cost of this operation is $ c_i $ .

Help Tenzing find the minimum cost to erase all of the points.

## 说明/提示

The picture of the first example:

Tenzing do the following operations:

1. draw a triangle with $ a=3,b=2 $ , the cost $ =1\cdot A=1 $ .
2. erase the first point, the cost $ =1 $ .
3. erase the second point, the cost $ =1 $ .
4. erase the third point, the cost $ =1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1842E/1bdc200b88d7bb8c2291ceda44aa78ea1247cdcf.png)The picture of the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1842E/5b751ee33521bd352511b2cb69c1137f569b64ee.png)

## 样例 #1

### 输入

```
4 6 1
1 2 1
2 1 1
1 1 1
3 2 6```

### 输出

```
4```

## 样例 #2

### 输入

```
6 7 1
4 2 1
3 3 1
5 1 4
3 2 5
4 1 1
0 6 4```

### 输出

```
4```

## 样例 #3

### 输入

```
10 4 100
0 0 1
0 1 1
0 2 50
0 3 200
1 0 1
1 1 1
1 2 1
2 0 200
2 1 200
3 0 200```

### 输出

```
355```

# 题解

## 作者：honglan0301 (赞：6)

## 题目分析

看起来很板，事实上暴力线段树优化也确实很无脑。

首先考虑围三角形的代价为什么要与边长线性，然后你会发现这其实保证了任意两个三角形不会有交（否则换成更大的三角形把二者都围起来显然不劣），于是我们套路地想到 $\text{dp}$。

设 $f_i$ 表示对 $y$ 值从上到下考虑完 $y\geq i$ 这个部分，并且当前最后一个围的三角形的下边界在 $y=i$ 时的最小代价（注意这个三角形可以边长 $=0$）。那么转移的时候就只需枚举当前三角形的上边界在哪里，并加上没有被三角形围住的孤立点代价，得到：

$$f_i=\min\{f_j+(j-i-1)\times A+\sum_{p=1}^n c_p[x_p<k-i][i\leq y_p<j]\}$$

接下来考虑优化，这种区间取 $\min$ 的常见套路是把与 $i$ 有关的东西提出去，然后数据结构维护最小值。所以我们变成 $f_i+A(i+1)=\min\{f_j+jA+\sum c\}$ 之后尝试对每个位置 $j$ 维护 $f_j+jA+\sum c$。

前两项是简单的，下面看最后一项。我们只需要注意到在 $i$ 逐渐变小的过程中，需要考虑的 $c$ 只会不断变多，于是就一边转移一边把新扫到的点的贡献加进去：一个在 $(x,y)$ 的点会且仅会对 $y<j\leq k-x$ 的 $j$ 产生贡献，那么从上到下扫的时候每考虑到一个点 $(x_p,y_p,c_p)$ 就对 $[y+1,k-x]$ 所维护的东西区间加 $c$ 即可。

于是做完了，我们需要支持：单点修改，区间加，区间取 $\min$。暴力上线段树，时间复杂度线性对数。

## 代码

```cpp
// 线段树板子，cz单点修，czadd区间加，ask区间取min

signed main()
{
	cin>>n>>k>>A;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i]>>c[i]; e[y[i]].pb(mp(x[i],c[i]));
	}
	build(1,k,1); dp[k]=0; cz(1,k,k,k*A,1);
	for(int i=k-1;i>=0;i--)
	{
		for(auto j:e[i])
		{
			int ll=i+1,rr=k-j.fi; czadd(1,k,ll,rr,j.se,1);
		}
		dp[i]=min((k-i)*A,ask(1,k,i+1,k,1)-(i+1)*A);
		cz(1,k,i,dp[i]+i*A,1);
	}
	cout<<dp[0]<<endl;
}
```


---

## 作者：快乐的大童 (赞：6)

## CF1842E	Tenzing and Triangle
[题目传送门](https://www.luogu.com.cn/problem/CF1842E)

考虑 dp，设 $f_i$ 表示考虑完 $x\le i$ 的部分时的最小花费。转移方程为 $f_{i}=\min_{j=0}^{i-1}f_{j}+(i-j-1)\cdot A+\sum_{1\le l\le n,j\le x_l<i,y_l<k-j-1}c_l$，时间复杂度 $O(n^2)$，无法通过。

考虑优化，对所有 $f_i$ 建立一颗线段树，那么，花费将由三部分组成。

1. $f_j$。计算完 $f_j$ 直接单点赋值即可。
2. $A\cdot (i-j-1)$。每次将要计算 $f_i$ 的时候对 $[0,i-2]$ 部分区间加 $A$，因为每次从 $i-1\rightarrow i$，$j$ 与 $i$ 的距离大 $1$。取 $f_{i-1}$ 表示这里不涂三角形。当 $i=1$ 时，如果要在这里涂三角形的话，那么其必须要从 $f_{-1}$ 转移，导致维护的信息不够，所以我们将线段树维护区间拓展为 $[-1,k]$，并从 $0$ 开始递推，此时也应该改为对 $[-1,i-2]$ 区间加 $A$。
3. $\sum_{1\le l\le n,x_l\le j,k-i\le y_l\le k-j-1}c_l$。考虑固定一个端点，预处理纵坐标为 $k-y_i$ 的点，每次我们取出 $k-y_i=i$ 的所有点，考虑哪些 $j$ 能对这个点做贡献，转化一下不等式，得到 $x_l\le j\le k-y_l-1$，对这段区间进行区间加 $c_l$ 操作。

现在，$i$ 的答案已经存在线段树里了。计算 $f_i$ 的时候，对 $[-1,i-1]$ 进行区间最小值查询操作（由于 $i\sim n$ 没有被赋值，所以全局查询和区间查询等价，代码中使用了区间查询）。时间复杂度 $O(n\log n)$，可以通过。
## 代码
```cpp
#include<bits/stdc++.h>
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
#define lson(x) (x<<1)
#define rson(x) (x<<1|1)
#define int long long
using namespace std;
inline int rd(){
	int x=0,f=1;int ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x,char ch='\0'){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[40];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);if(ch!='\0')putchar(ch);
}
const int maxn=2e5+5,inf=0x3f3f3f3f3f3f3f3f;
int n,k,A,a[maxn];
int x[maxn],y[maxn],c[maxn];
vector<int>vet[maxn],vec[maxn];
int f[maxn];
int d[maxn<<2],b[maxn<<2];
void pushup(int p){
	d[p]=min(d[lson(p)],d[rson(p)]);
}
void pushdown(int p){
	if(b[p]){
		d[lson(p)]+=b[p],d[rson(p)]+=b[p];
		b[lson(p)]+=b[p],b[rson(p)]+=b[p];
		b[p]=0;
	}
}
void build(int l,int r,int p){
	if(l==r){
		d[p]=inf,b[p]=0;
		return;
	}
	int mid=l+r>>1;
	build(l,mid,lson(p));build(mid+1,r,rson(p));
	pushup(p);
}
void update(int ll,int rr,int l,int r,int p,int v){
	if(ll<=l&&r<=rr){
		d[p]+=v,b[p]+=v;
		return;
	}
	int mid=l+r>>1;pushdown(p);
	if(ll<=mid) update(ll,rr,l,mid,lson(p),v);
	if(rr>mid) update(ll,rr,mid+1,r,rson(p),v);
	pushup(p);
}
void modify(int x,int l,int r,int p,int v){
	if(l==r){
		d[p]=v;
		return;
	}
	int mid=l+r>>1;pushdown(p);
	if(x<=mid) modify(x,l,mid,lson(p),v);
	else modify(x,mid+1,r,rson(p),v);
	pushup(p);
}
int query(int ll,int rr,int l,int r,int p){
	if(ll<=l&&r<=rr) return d[p];
	int mid=l+r>>1,res=inf;pushdown(p);
	if(ll<=mid) res=min(res,query(ll,rr,l,mid,lson(p)));
	if(rr>mid) res=min(res,query(ll,rr,mid+1,r,rson(p)));
	return res;
} 
signed main(){
	n=rd(),k=rd(),A=rd();
	rep(i,1,n)x[i]=rd(),y[i]=rd(),c[i]=rd(),vet[k-y[i]].push_back(i);
	build(-1,k,1);modify(-1,-1,k,1,0);
	rep(i,0,k){
		if(i) update(-1,i-2,-1,k,1,A);
		for(int j:vet[i]) update(x[j],k-y[j]-1,-1,k,1,c[j]);
		f[i]=query(-1,i-1,-1,k,1);
		modify(i,-1,k,1,f[i]);
	}
	write(f[k]);
}

```


---

## 作者：kernel_panic (赞：4)

## 思路

注意到选出的三角形一定没有公共部分．若存在有公共部分的两个三角形，则这两个三角形可以合并成一个大三角形，代价不增的同时可能可以覆盖到更多的点，一定更优．

于是考虑 DP．设 $f_i$ 表示考虑了 $x$ 坐标在 $[0, i]$ 内的所有点，存在一个右下角的横坐标为 $i$ 的三角形时的最小代价．枚举上一个三角形的结束位置，我们有如下转移：

$$
f_i = \min_{j < i} \{f_j + (i - j - 1)A + \mathrm{cost}\}
$$

其中 $\mathrm{cost}$ 为所有满足 $x \in (j, i], y \in [1, k - i)$ 的点的 $c$ 之和．

注意到每次 $i - 1 \rightarrow i$ 的过程中，只有满足 $x = i$ 或 $y = k - i$ 的点会对一些 $j$ 的 $\mathrm{cost}$ 造成影响，故考虑直接维护 $\min$ 里面的东西．

具体而言，在 $i - 1 \rightarrow i$ 的过程中，我们会有一些形如 $(p, k - i)$ 的点，这些点的 $c$ 需要从 $p$ 之前的 $\mathrm{cost}$ 中去掉；我们还会有一些形如 $(i, \dots)$ 的点，这些点的 $c$ 需要加入 $i$ 之前的 $\mathrm{cost}$ 中．这些操作对 $\min$ 里面东西的影响都形如前缀加，而 $(i - j - 1)A$ 这一项的贡献也是前缀加．用一个支持前缀加前缀 $\min$ 的数据结构维护即可．

注意 $-1$ 处的东西是有用的，表示所有点都未被考虑的状态，需要维护．

## 代码

使用线段树实现．

```cpp
#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

using pii = std::pair<int, int>;
using i64 = long long;
const int N = 2e5;

int n, k, A;

#define lch (p * 2)
#define rch (p * 2 + 1)
#define mid ((cl + cr) >> 1)
struct node {
	i64 mn, tg;
	void upd(i64 d) {
		mn += d, tg += d;
	}
} t[N * 4 + 5];
void pushup(int p) { t[p].mn = std::min(t[lch].mn, t[rch].mn); }
void pushdown(int p) {
	if (!t[p].tg) return;
	t[lch].upd(t[p].tg), t[rch].upd(t[p].tg);
	t[p].tg = 0;
}
void upd(int l, int r, i64 d, int p = 1, int cl = -1, int cr = k) {
	if (cl == l && cr == r) return t[p].upd(d);
	pushdown(p);
	if (r <= mid) upd(l, r, d, lch, cl, mid);
	else if (l > mid) upd(l, r, d, rch, mid + 1, cr);
	else upd(l, mid, d, lch, cl, mid), upd(mid + 1, r, d, rch, mid + 1, cr);
	pushup(p);
}
i64 que(int l, int r, int p = 1, int cl = -1, int cr = k) {
	if (cl == l && cr == r) return t[p].mn;
	pushdown(p);
	if (r <= mid) return que(l, r, lch, cl, mid);
	else if (l > mid) return que(l, r, rch, mid + 1, cr);
	else return std::min(que(l, mid, lch, cl, mid), que(mid + 1, r, rch, mid + 1, cr));
}
#undef lch
#undef rch
#undef mid

std::vector<pii> a[N + 5];
i64 ct[N + 5], f[N + 5];

int main() {
	n = rd(), k = rd(), A = rd();
	for (int i = 1; i <= n; i++) {
		int x = rd(), y = rd(), c = rd();
		a[y].emplace_back(x, c);
		if (x + y != k) ct[x] += c;
	}
	for (int i = 0; i <= k; i++) {
		for (auto [x, c] : a[k - i]) upd(-1, x - 1, -c);
		upd(-1, i - 1, ct[i]);
		if (i != 0) upd(-1, i - 2, A);
		f[i] = que(-1, i - 1), upd(i, i, f[i]);
	}
	printf("%lld\n", f[k]);
	return 0;
}
```


---

## 作者：六楼溜刘 (赞：3)

## 题意

- 现在在平面直角坐标系内有 $n$ 个点，每个点有一个权值 $w_i$，对于所有点 $(x_i,y_i)$，有 $0 \le x_i,y_i,x_i+y_i < k$。
- 现在丁真想要删除这个平面上的所有点，有两种删点的方法：
	1. 直接删掉某个点，代价为该点的权值 $w_i$。
   1. 任意选择一个点 $(x_0,y_0)$（不一定在原来的点集中），需要保证 $0 \le x_0,y_0,x_0+y_0 < k$，删除所有满足 $x_i \ge x_0$ 且 $y_i\ge y_0$ 的点，即删除这个点与函数 $y=-x+k$ 的图像围成的等腰直角三角形中所有点。代价为三角形直角边长 $l\times A$。
- 两个操作可以执行任意次，求删除所有点的最小代价。

## 题解

这道题赛时想了个贪心伪掉了。

首先容易证明假如有两个三角形重合了必定不优：

![](https://cdn.luogu.com.cn/upload/image_hosting/r5v1lhk9.png)

在左图中，原本两个三角形只覆盖了绿色区域，不仅没有覆盖到黄色区域，代价还比红色三角形大，故两个黑色三角形必定不优，另外像右图一样只有一点重合的也不优，证明同理。

然后还有一个转化，假设所有点都用操作一删除，然后每次一个对 $(x_0,y_0)$ 操作二就会对答案产生 $l\cdot A-s(x_0,y_0)$ 的贡献，其中 $s(x_0,y_0)$ 表示点 $(x_0,y_0)$ 围出的三角形中所有点的权值和。原来的代价和就转化为了 $\left(\sum y_i\right)+\left[\sum l\cdot A-s(x_0,y_0)\right]$。我们的问题就转化成了求 $\sum h(x_0,y_0)=l\cdot A-s(x_0,y_0)$ 的最小值。

容易想到 dp，设 $dp_i$ 表示所有 $x_0 \ge i$ 的操作二的 $h$ 的和的最小值。

假设有一个操作二 $x_0=i$，这个三角形直角边长为 $len$（如果没有那么 $len=0$），易得转移方程：

$$dp_i=\min_{len=0}^{k-i}\{dp_{i+len+1}+len\cdot A +s(i,k-i-len)\}$$

由于重合了不优所以要从 $dp_{i+len+1}$ 转移过来（而不是 $dp_{i+len}$，不然就重合了），后面的都很好理解，自己画图推一推。

发现 $dp_{i+len+i}$ 看起来很烦，考虑设 $j=i+len+1$，那么 $len=j-i-1$，易得转移方程：

$$dp_i=\min_{j=i+1}^{k+1}\{dp_{j}+(j-i-1)\cdot A +s(i,k-j+1))\}$$

这里 $k+1$ 就是一个边界，不用管它。

然后我们把和 $i$ 相关的提出来：

$$dp_i=\min_{j=i+1}^{k+1}\{dp_{j}+(j-1)\cdot A +s(i,k-j+1))\}-i\cdot A$$

对于一个特定的 $i$，设 $g(j)=dp_{j}+(j-1)\cdot A +s(i,k-j+1))$，那么就变成了：

$$dp_i=\min_{j=i+1}^{k+1}\{g(j)\}-i\cdot A$$

现在难点就是对 $s(i,k-j+1)$ 的处理，对于一个操作二，我们很难求出点的权值和，不妨反过来想，一个权值为 $w$ 的点会影响多少个 $g(j)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/aekw8ldk.png)

假设有一个点坐标为 $(i,y)$，那么对于所有横坐标小于等于 $i$，纵坐标小于等于 $y$ 的操作二都会产生影响，这样的操作二所对应的 $g(j)$ 必定满足 $j \ge k-y+1$，并且所有满足 $j \ge k-y+1$ 的 $j$ 都必定会被影响，原因显然。

那么就可以用一棵线段树维护 $g(j)$ 的区间加，转移的时候区间取最小值，具体见代码。

### code

```cpp
//author: six-floor-slip-liu

#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(i64 i=(s);i<=(e);i++)
#define fordown(i,s,e) for(i64 i=(s);i>=(e);i--)
using namespace std;
using i64=long long;
#define gc getchar()
inline i64 read(){
    i64 x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const i64 N=2e5+5,inf=1e18;
i64 n,k,a,ans;
struct Node{
	i64 x,y,cst;
}s[N];
bool cmp(Node a,Node b){
	if(a.x!=b.x) return a.x>b.x;
	return a.y>b.y;
}
i64 dp[N];
struct SegmentTree{
	#define mid ((l+r)>>1)
	#define lson l,mid,id<<1
	#define rson mid+1,r,id<<1|1
	i64 querymin[N<<2],mark[N<<2];
	void PushUp(i64 id){//回溯
		querymin[id]=min(querymin[id<<1],querymin[id<<1|1]);
	}
	void PushDown(i64 id){//下传懒标记
		querymin[id<<1|1]+=mark[id];
		querymin[id<<1]+=mark[id];
		mark[id<<1|1]+=mark[id];
		mark[id<<1]+=mark[id];
		mark[id]=0;
	}
	void QueryAdd(i64 L,i64 R,i64 X,i64 l=0,i64 r=k+1,i64 id=1){
	//区间加
		if(L<=l&&r<=R){
			querymin[id]+=X;
			mark[id]+=X;
			return;
		}
		if(mark[id]&&l<r) PushDown(id);
		if(L<=mid) QueryAdd(L,R,X,lson);
		if(mid< R) QueryAdd(L,R,X,rson);
		PushUp(id);
	}
	i64 AskMin(i64 L,i64 R,i64 l=0,i64 r=k+1,i64 id=1){
	//区间取最小值
		if(L<=l&&r<=R){
			return querymin[id];
		}
		if(mark[id]&&l<r) PushDown(id);
		i64 res=inf;
		if(L<=mid) res=min(res,AskMin(L,R,lson));
		if(mid< R) res=min(res,AskMin(L,R,rson));
		PushUp(id);
		return res;
	}
}mt;
signed main(){
	n=read();k=read();a=read();
	forup(i,1,n){
		s[i].x=read();s[i].y=read();s[i].cst=read();
		ans+=s[i].cst;
	}
	sort(s+1,s+n+1,cmp);
	i64 l=1;
	mt.QueryAdd(k+1,k+1,k*a);//先上传边界
	fordown(i,k,0){
		while(s[l].x==i){//把所有 x=i 的全部上传
			mt.QueryAdd(k-s[l].y+1,k+1,-s[l].cst);
			++l;
		}
		dp[i]=min(0ll,mt.AskMin(i+1,k+1)-i*a);
		mt.QueryAdd(i,i,dp[i]+(i-1)*a);
		//单点上传 dp[j]+(j-1)*A，s 放到后面处理。
	}
	printf("%lld",ans+dp[0]);//注意加上权值总和。
}
```


---

## 作者：Creeper_l (赞：2)

题意不多赘述。

## 思路

如果两个所选的三角形有重合部分的话，那么这种情况肯定是不会出现的。因为如果把这两个三角形合成一个大三角形的话，不仅覆盖面积会增大，而且花费的代价还不会多。

于是我们可以想到用 dp 来解决，设 $dp_{i}$ 表示删完横坐标为 $0$ 到 $i$ 中的点的最小代价，很容易得到状态转移方程：$dp_{i}=\min(dp_{j}+(i-j-1)\times A+cost)$。这里的 $cost$ 指的是所有满足 $j<x\le i,1\le y<k-i$ 的条件的点，因为只有这些点没有被当前所选的这个三角形所包含，所以需要加上这些点的代价。但是这个方程转移的时间复杂度是 $O(n^{2})$ 的，所以还需要优化。

我们可以发现一些性质，首先方程中的 $A\times(i-j-1)$ 一定是递减的，而 $cost$ 值的变化也有一些规律。从 $i$ 变到 $i+1$ 的过程中，需要加上满足 $x=i$ 的点的代价，减去满足 $y=k-i$ 的点的代价，其余的点不会变化。所以我们发现每一次从 $i$ 变为 $i+1$ 我们都可以只修改之前所有 $A$ 和 $cost$ 的值就行了，每一次的值就是前面所有数的最小值，而这两个操作都可以用线段树来维护，时间复杂度 $O(n \log n)$。注意线段树维护的每一个 $j$ 的值已经是 $dp_{j}+(i-j-1)\times A+cost$ 了，所以直接查询最小值就可以了。

注意因为坐标轴的最小值为 $0$，所以我们还需要维护一个下标为 $-1$ 的值，这个值代表前面还什么都没有选时的代价。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define re register
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 1e6 + 10;
int n,x,y,c,cost[MAXN],k,A,dp[MAXN];
struct SegmentTree{int id,l,r,mn,add;}tree[MAXN];
inline void Pushup(int id){tree[id].mn = min(tree[ls].mn,tree[rs].mn);}
inline void Build(int id,int l,int r)
{
	tree[id].l = l,tree[id].r = r;
	if(l == r){tree[id].mn = 0;return;}
	int mid = (l + r) >> 1;
	Build(ls,l,mid),Build(rs,mid + 1,r);
}
inline void Pushdown(int id)
{
	if(tree[id].add == 0) return;
	tree[ls].mn += tree[id].add,tree[ls].add += tree[id].add;
	tree[rs].mn += tree[id].add,tree[rs].add += tree[id].add;
	tree[id].add = 0;
}
inline void Add(int id,int l,int r,int a,int b,int c)
{
	if(a <= l && b >= r)
	{
		tree[id].mn += c;
		tree[id].add += c;
		return;
	}
	Pushdown(id);
	int mid = (l + r) >> 1;
	if(a <= mid) Add(ls,l,mid,a,b,c);
	if(b > mid) Add(rs,mid + 1,r,a,b,c);
	Pushup(id);
}
inline int Query(int id,int l,int r,int a,int b)
{
	if(a <= l && b >= r) return tree[id].mn;
	Pushdown(id);
	int mid = (l + r) >> 1,res = 1e18;
	if(a <= mid) res = min(res,Query(ls,l,mid,a,b));
	if(b > mid) res = min(res,Query(rs,mid + 1,r,a,b));
	return res;
}
std::vector <pii> a[MAXN];
signed main()
{
	cin >> n >> k >> A;
	Build(1,-1,k);
	for(int i = 1;i <= n;i++)
	{
		cin >> x >> y >> c;
		a[y].emplace_back(x,c);
		if(x + y != k) cost[x] += c;
	}
	for(int i = 0;i <= k;i++)
	{
		for(int j = 0;j < a[k - i].size();j++) Add(1,-1,k,-1,a[k - i][j].first - 1,-a[k - i][j].second);
		Add(1,-1,k,-1,i - 1,cost[i]);
		if(i != 0) Add(1,-1,k,-1,i - 2,A);
		dp[i] = Query(1,-1,k,-1,i - 1),Add(1,-1,k,i,i,dp[i]);
	}
	cout << dp[k]; 
	return 0;
}		
```



---

## 作者：Hisaishi_Kanade (赞：2)

显然的，任意三角形无交。证明比较简单，因为这样肯定不优。

那么这样可以直接动态规划，$f(i)$ 表示已经处理了 $x\le i$ 的情况所需的最小花费。

转移方程大概长成 $f(i)=\min\{f(j)+A\times(i-j-1)+\sum c_k\}\mid x_k\in(j, i],y\in[0,k-i)$。

考虑如何取计算这个东西，令 $g_j=f(j)+A\times(i-j-1)+\sum c_k\mid x_k\in(j, i],y\in[0,k-i)$，在 $i-1\to i$ 的时候有没有办法快速把他更新出来？

求解 $i$ 时，先对于所有 $j\in[-1,i-1]$，$g_j\gets g_j+A$，因为对于这些情况的，$(i-j-1)\times A$ 这一项他会多一个，你会发现如果这样 $g_{i-1}$ 也被加了，而实际上没有这个，怎么办呢？这简单，我们只需要求解完 $f_i$ 后将 $g_{i}$ 赋值 $f_{i}-A$，下一次自然就抵消了。

然后如何维护 $\sum c_k$ 这个玩意呢，我们发现可能造成变化的无非是 $y=k-i$ 或者 $x=i$ 的点。对于前者以往怎么覆盖都覆盖不到，对于后者，以往并没有去考虑，所以这些的贡献需要重算。

对于 $y=k-i$，这个点必然形如 $(x, k-i)$，显然的，对于 $j\in[-1,x)$ 的，算 $\sum c_k$ 的时候这个点就不再被考虑到了，因为它会被横直角边在 $[j+1,i]$ 的这个三角形覆盖掉啊，所以对于每一个 $j$ 进行 $g_{j}\gets g_{j}-c$。

对于 $x=i$，首先特判掉此时刚好 $y=k-i$，对于其他的，你怎么覆盖都没有任何用，所以必然对于前面的 $g$ 都要加上他的 $c$。

那么综上你只需要维护一个区间加和区间最小值，这显然线段树即可。 

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define lc(id) (id<<1)
#define rc(id) (id<<1|1)
#define mid (l+r>>1)
#define root 1, -1, k
#define left lc(id), l, mid
#define right rc(id), mid+1, r
using namespace std;
using ll=long long;
const int N=2e5+5;
const ll inf=1e18;
ll tr[N<<2], tag[N<<2];
int n, k, a;
ll f[N], x[N], y[N], c[N], tot[N];
vector<pair<int, int>> dy[N];
inline void push_up(int id)
{
	tr[id]=min(tr[lc(id)], tr[rc(id)]);
	return ;
}
inline void push_down(int id)
{
	if(!tag[id]) return ;
	tr[lc(id)]+=tag[id];
	tag[lc(id)]+=tag[id];
	tr[rc(id)]+=tag[id];
	tag[rc(id)]+=tag[id];
	tag[id]=0;
}
inline void update(int id, int l, int r, int ql, int qr, int x)
{
	if(r<ql || qr<l) return ;
	if(ql<=l && r<=qr)
	{
		tr[id]+=x;
		tag[id]+=x;
	//	printf("%d %d %d %d %d\n", id, l, r, ql, qr);
		return ;
	}
	push_down(id);
	update(lc(id), l, mid, ql, qr, x);
	update(rc(id), mid+1, r, ql, qr, x);
	push_up(id);
	return ;
}
inline ll query(int id, int l, int r, int ql, int qr)
{
	if(r<ql || qr<l) return inf;
	if(ql<=l && r<=qr) return tr[id];
	push_down(id);
	return min(query(left, ql, qr), query(right, ql, qr));
}
int main()
{
	scanf("%d %d %d", &n, &k, &a);
	int i; rep(i, 1, n)
	{
		scanf("%lld %lld %lld", x+i, y+i, c+i);
		if(y[i]+x[i]!=k) tot[x[i]]+=c[i];
		dy[y[i]].emplace_back(x[i], c[i]);
	}
	update(1, -1, k, -1, -1, -a);// return 0;
	rep(i, 0, k)
	{
		for(auto tmp : dy[k-i]) update(root, -1, tmp.first-1, -tmp.second);
		update(root, -1, i-1, tot[i]); update(root, -1, i-1, a);
		f[i]=query(root, -1, i-1); update(root, i, i, f[i]-a);
	//	printf("%lld\n", f[i]);
	}
	printf("%lld", f[k]);
	return 0;
}
```

---

## 作者：_saltFish_ (赞：1)

# 简要题意

平面上 $n$ 个点，每个点有权值 $c_{i}$，保证对于每个点 $i$ 有 $x_{i}+y_{i}<k$ 且 $x_{i},y_{i}\ge0$。可以删除一个点，代价为 $c_{i}$，或任选一个以直线 $x+y=k$ 为斜边的等腰直，删除这个等腰直中的所有点，代价为 $l\cdot A$，其中 $l$ 为这个等腰直的直角边长，$A$ 为一个常数。
$$
1\leq n,k\leq 2\cdot 10^5,1\leq A\leq 10^4
$$

# 思路

可以将坐标系拍扁，将一个点 $(x_{i},y_{i})$ 变成一个区间 $[x_{i},k-y_{i}]$。转化为若干个区间，可以选择直接删掉一个给定的区间 $i$，代价 $c_{i}$，或跳过任意一个区间 $[l,r]$，代价为 $A(r-l)$。明显是等价的。由于代价的总和是一定的，所以可以转化为选择一些区间，最小化这些区间的代价和，选择一个区间 $[l,r]$ 的代价定义为 $A(r-l)$ 减去被这个区间包含的给定区间的 $c_{i}$ 之和。设 $f_{i}$ 表示考虑完所有 $r\le i$ 的区间的最小代价，设 $sum(l,r)$ 表示右端点为 $r$，左端点小于等于 $l$ 的区间的 $c_{i}$ 之和。有转移 $f_{i}=\min\limits_{j=1}^{i}f_{j-1}+A\cdot(i-j)-(sum(i,i)-sum(j-1,i))$。这个式子实现精细的话是 $O(n^{2})$ 的。但是可以发现，上面这个式子用线段树优化非常方便（这个式子其实是我先写了线段树优化，然后对着线段树优化写出来的）。线段树优化其实不用求出 $sum(j,i)$，将所有右端点为 $i$ 的区间扫一遍，每个区间在线段树上做一个前缀加即可。答案就是 $f_{k}+\sum c_{i}$。

---

## 作者：王熙文 (赞：1)

## 思路

考虑将每个点右上的等腰三角形与 $x+y=k$ 的直线相交的部分看做 $x+y=k$ 上的一段区间，那么一个点的等腰三角形包含另一个点等价于这个点的区间包含那个点。这样就把题意转化成了：在一条线上有 $n$ 个区间，单独消去一个区间需要花费 $c_i$ 的代价，用一个大区间小于它包含的小区间需要花费长度$\text{}\times A$ 的代价，求最小代价。

考虑设 $dp_i$ 表示消去所有区间右端点小于等于 $i$ 的最小代价。则

$$dp_i = \min(dp_{i-1}+\sum_{r_j=i} c_j,\min_{j \le i-1} dp_j+A(i-j-1)+ \sum_{l_k \le j<r_k\le i} c_k)$$

后面部分将 $A(i-1)$ 提出来，剩下的需要维护 $dp_j-Aj+\sum_{l_k \le j<r_k\le i} c_k)$ 的最小值。每一次从 $i-1$ 移动到 $i$ 的时候，枚举 $r_k=i$，将 $j \in [l_k,r_k-1]$ 加上 $c_k$ 即可，线段树维护区间加区间最小值。

上面是正解，但是请考虑一个问题：一般来说我们对若干个区间做 dp 都是将区间排序，dp 的下标是区间的编号，为什么这道题的下标是坐标？

可以发现，按编号排序后 dp 的优势是排序后区间之间有一些大小关系可以直接利用，比如选的一定是排好序的一段区间之类的。而这道题无论怎么排序，选的都不一定一个区间。而且这道题看重的是区间本身，两个端点的变化都可能影响答案，而有些题，比如要求区间之间有交集一类的在转移等时候只需要关注一个端点，就可以按编号排序。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int n,k,qz;
vector<pair<int,int>> vec[200010];
struct Seg_tree
{
	int in[800010],tag[800010];
	void push_down(int now,int l,int r)
	{
		int mid=(l+r)>>1;
		in[now<<1]+=tag[now],tag[now<<1]+=tag[now];
		in[now<<1|1]+=tag[now],tag[now<<1|1]+=tag[now];
		tag[now]=0;
	}
	void upd(int now,int l,int r,int ql,int qr,int qz)
	{
		if(ql<=l && r<=qr) return in[now]+=qz,tag[now]+=qz,void();
		int mid=(l+r)>>1; push_down(now,l,r);
		if(ql<=mid) upd(now<<1,l,mid,ql,qr,qz);
		if(qr>mid) upd(now<<1|1,mid+1,r,ql,qr,qz);
		in[now]=min(in[now<<1],in[now<<1|1]);
	}
	int query(int now,int l,int r,int ql,int qr)
	{
		if(ql<=l && r<=qr) return in[now];
		int mid=(l+r)>>1,ans=2.1e9; push_down(now,l,r);
		if(ql<=mid) ans=min(ans,query(now<<1,l,mid,ql,qr));
		if(qr>mid) ans=min(ans,query(now<<1|1,mid+1,r,ql,qr));
		return ans;
	}
} seg;
int dp[200010];
int main()
{
	cin>>n>>k>>qz;
	for(int i=1; i<=n; ++i)
	{
		int x,y,z; cin>>x>>y>>z;
		vec[k-y].push_back({x,z});
	}
	seg.upd(1,-1,k,-1,-1,qz);
	for(int i=0; i<=k; ++i)
	{
		int sum=0;
		for(pair<int,int> j:vec[i])
		{
			sum+=j.second;
			if(j.first!=i) seg.upd(1,-1,k,j.first,i-1,j.second);
		}
		if(i==0) dp[i]=sum;
		else dp[i]=min(dp[i-1]+sum,qz*(i-1)+seg.query(1,-1,k,-1,i-1));
		seg.upd(1,-1,k,i,i,dp[i]-qz*i);
	}
	cout<<dp[k];
	return 0;
}
```

---

## 作者：mod998244353 (赞：1)

可以发现，有最优方案满足，所有三角形一定不会覆盖重复的部分。

如果有两个直角边长为 $a,b$ 的三角形覆盖重复的部分，那么可以直接用一个直角边长为 $a+b$ 的三角形替代它们。

设 $f_{i}$ 表示只处理 $x\leq i$ 的部分的最小代价，$f_{-1}=0$。

设 $b_{l,r,z}$ 表示满足 $l\leq x\leq r,0\leq y<z$ 的点 $(x,y)$ 的 $c$ 之和。

$f_i=\min(f_j+b_{j+1,i,k-i}+A(i-j-1)),-1\leq j<i$

$f_i=\min(f_j+b_{j+1,i-1,k-i}-Aj)+A(i-1)+b_{i,i,k-i}$

用区间加、单点修改、全局最小值的线段树维护 $f_j+b_{j+1,i-1,k-i}-Aj$ 的最小值就可以转移。

为了实时维护 $b_{j+1,i-1,k-i}$，需要在时刻 $i$ 将 $y=k-i$ 的点的贡献减去，将 $x=i$ 的点的贡献加上。

由于 $k-i$ 递减，可以用大根堆维护计算了贡献的点。

时间复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=200005;
inline int read() {
    static int x=0,c=getchar(),f=1;
    for(f=1; c<=47||c>=58; c=getchar())f=f&&(c^45);
    for(x=0; c>=48&&c<=57; c=getchar())x=(x<<3)+(x<<1)+(c&15);
    return f?x:-x;
}
int n,k,A;
ll f[MAXN],sum[MAXN];
struct node {
    int x,y,c;
    bool operator<(const node b) const {
        return y<b.y;
    }
} a[MAXN];
priority_queue<node>q;
struct Tree {
    int l,r;
    ll mn,lt;
} tr[MAXN<<2];
vector<node>vec[MAXN];
void build(int num,int l,int r) {
    tr[num].l=l,tr[num].r=r,tr[num].lt=0,tr[num].mn=1e18;
    if(l==r) return;
    build(num<<1,l,l+r>>1),build(num<<1|1,l+r+2>>1,r);
}
inline void push_up(int num) {
    tr[num].mn=min(tr[num<<1].mn,tr[num<<1|1].mn);
}
inline void upd(int num,ll x) {
    tr[num].mn+=x,tr[num].lt+=x;
}
inline void push_down(int num) {
    if(tr[num].lt) {
        upd(num<<1,tr[num].lt),upd(num<<1|1,tr[num].lt);
        tr[num].lt=0;
    }
}
void update(int num,int x,ll val) {
    if(tr[num].l==tr[num].r) {
        tr[num].mn=val;
        return;
    }
    push_down(num);
    update(num<<1|(tr[num<<1].r<x),x,val);
    push_up(num);
}
void add(int num,int l,int r,ll v) {
    if(l<=tr[num].l&&tr[num].r<=r) return upd(num,v);
    push_down(num);
    if(l<=tr[num<<1].r) add(num<<1  ,l,r,v);
    if(tr[num<<1].r <r) add(num<<1|1,l,r,v);
    return push_up(num);
}
ll query(int num,int l,int r) {
    if(l<=tr[num].l&&tr[num].r<=r) return tr[num].mn;
    push_down(num);
    ll res=1e18;
    if(l<=tr[num<<1].r) res=min(res,query(num<<1  ,l,r));
    if(tr[num<<1].r <r) res=min(res,query(num<<1|1,l,r));
    return res;
}
int main() {
    n=read(),k=read(),A=read();
    for(int i=1; i<=n; ++i) {
        a[i].x=read(),a[i].y=read(),a[i].c=read();
        sum[a[i].x]+=a[i].c;
        vec[a[i].x].push_back(a[i]);
    }
    build(1,-1,k),update(1,-1,A);
    for(int i=0; i<=k; ++i) {
        while(!q.empty()&&q.top().y>=k-i) {
            add(1,-1,q.top().x-1,-q.top().c);
            q.pop();
        }
//        for(int j=-1; j<i; ++j) printf("%lld ",query(1,j,j)+A*j);
//        printf("\n");
        f[i]=tr[1].mn+A*(i-1ll)+sum[i];
//        f[i]=query(1,-1,i-1)+A*(i-1ll)+sum[i];
        update(1,i,f[i]-A*1ll*i);
        for(node&tmp:vec[i])
            q.push(tmp),add(1,-1,i-1,tmp.c);
    }
    printf("%lld\n",f[k]);
    return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
~~有点长就不贴了~~
### 分析
首先观察到选出来的三角形不交，显然可以用一个更大的包含它们并且代价小于它们俩之和。这告诉我们每个点最多被包含在一个选出的三角形内。

所以我们可以考虑这样的 DP：先把所有的点单独删去，再计算在直线 $x+y=k$ 上选出若干段形成的等腰直角三角形能为我们省下的最大代价。

我们定义 $f_i$ 表示到横坐标到 $i$ 时的最大节省代价，钦定 $i$ 为右端点，暴力枚举左端点，转移则是：
$$f_i=\max_{j=0}^{i-1}f_{j-1}+c_{j,i}-A(i-j)$$
这个东西显然跑不过去，但也是显然的 sgt 优化，扫描线扫描到 $i$ 的时候加入所有纵坐标为 $k-i$ 的点，它们都是对某个前缀产生贡献；然后再对全局 $-A$，因为右端点右移了一位，这样再直接查询全局 $\max$ 就行了，所以是区间加全局最大值（当然把 $f_i$ 单点赋到 $i+1$ 可以并到区间加里面）。

时间复杂度 $O(n\log n)$。
### 代码
见 [CF](https://codeforces.com/problemset/submission/1842/271045083)。

---

## 作者：Nelofus (赞：0)

线段树维护决策。

令 $dp_i$ 表示覆盖 $y\ge i$ 的所有点的最小代价。

在维护上述序列的过程中，同时维护一个对于 $t\in[0,k]$，删除 $t$ 一列左侧所有点的最小代价，我们用考虑 $g_t$ 表示。

![屏幕截图 2023-06-29 081336.png](https://s2.loli.net/2023/06/29/ybuSkaqAGfOpvH2.png)

则
$$
dp_y\leftarrow g_i+A(k-y-(i+1))
$$
考虑把所有带 $i$ 的项单独维护，我们维护 $g_i-A(i+1)$，而 $A(k-y)$ 需要时再加上即可。

因为是最小代价，所以我们希望这个这个数越小越好。

考虑在当前 $y$ 的行上有一个新的点的贡献，假设这个点横坐标为 $x$，因为线段树当前维护的三角形全都是在 $y+1$ 以上的，所以为了消掉这个点，$x\sim k-y$ 的三角形必须加上 $c_i$ 的代价。

![屏幕截图 2023-06-29 082416.png](https://s2.loli.net/2023/06/29/MLW42YPaH3k6mXw.png)

在计算出所有新的点带来的额外代价后只要在所有的 $g_i$ 之间取 $\min$ 所得的就是最小的代价。

计算出 $dp_y$ 之后要再加入当前的这个三角形，其横坐标是 $k-y$，而删掉 $k-y$ 左侧所有点此时的最小代价就是 $dp_y$，也就是令 $g_{k-y}= dp_y-A(k-y+1)$。

![屏幕截图 2023-06-29 081938.png](https://s2.loli.net/2023/06/29/uIcJ81XMUVnSpsg.png)

那么我们要维护的信息即是区间加，查询全局 $\min$，单点取 $\min$，用线段树维护。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

typedef long long ll;
const int N = 2e5 + 10;
int n, k;
ll sum, A;
ll dp[N];
std::vector<std::pair<int, int>> p[N];

struct node {
	int l, r;
	ll tag;
	ll minv;
}tr[N << 2];

inline void pushup(int u) {
	tr[u].minv = std::min(tr[u << 1].minv, tr[u << 1 | 1].minv);
}

inline void pushdown(int u) {
	node &ls = tr[u << 1], &rs = tr[u << 1 | 1];
	ls.tag += tr[u].tag;
	rs.tag += tr[u].tag;
	ls.minv += tr[u].tag;
	rs.minv += tr[u].tag;
	tr[u].tag = 0;
}

void build(int u, int l, int r) {
	tr[u].tag = 0;
	tr[u].l = l, tr[u].r = r;
	if (l == r) {
		tr[u].minv = 1e12;
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void modify1(int u, int p, ll k) {
	if (tr[u].l == tr[u].r) {
		tr[u].minv = std::min(tr[u].minv, k);
		return ;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (p <= mid)
		modify1(u << 1, p, k);
	if (p > mid)
		modify1(u << 1 | 1, p, k);
	pushup(u);
}

void modify(int u, int l, int r, ll k) {
	if(l <= tr[u].l && tr[u].r <= r) {
		tr[u].tag += k;
		tr[u].minv += k;
		return ;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid)
		modify(u << 1, l, r, k);
	if (r > mid)
		modify(u << 1 | 1, l, r, k);
	pushup(u);
}

ll query(int u, int l, int r) {
	if (l <= tr[u].l && tr[u].r <= r) {
		return tr[u].minv;
	}
	pushdown(u);
	ll ans = 1e13;
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid)
		ans = std::min(ans, query(u << 1, l, r));
	if (r > mid)
		ans = std::min(ans, query(u << 1 | 1, l, r));
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cin >> n >> k >> A;
	for (int i = 1; i <= n; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		p[y].push_back({x, w});
	}
	build(1, 0, k);
	for (int i = k; i >= 0; i--) {
		for (auto a : p[i]) {
			//k-i即当前x
			modify(1, a.first, k - i, a.second);
		}
		dp[i] = 1ll * (k-i) * A;
		dp[i] = std::min(dp[i], 1ll * (k-i) * A + query(1, 0, k - i));
		modify1(1, k - i, dp[i] - 1ll * (k - i + 1) * A);
	}
	std::cout << dp[0] << '\n';
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

一个很显然的观察：选择的三角形两两重叠面积为 $0$，否则合并更优。

考虑 dp，设 $f_i$ 为删完 $x_j \ge i$ 的所有点的最小花费。转移就枚举选择的三角形直角边长 $l$，那么 $f_i = \min(f_{i + 1} + \sum\limits_{x_p = i} c_p, \min\limits_l f_{i + l} + \sum\limits_{i \le x_p < i + l \land y_p < k - i - l} c_p)$，就是把三角形下方的那坨矩形的点的 $c_i$ 算进去。

考虑直接线段树维护后面那坨式子的最小值，设 $g_j = \sum\limits_{i \le x_p < j \land y_p < k - j} c_p$，$i + 1 \to i$ 时，对于每个 $x_p = i$ 的点，让 $g_{i + 1 \sim k - y_p - 1}$ 加上 $c_p$ 即可。

时间复杂度 $O((n + k) \log k)$。

[code](https://codeforces.com/contest/1842/submission/210996967)

---

