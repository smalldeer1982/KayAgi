# Smart Cheater

## 题目描述

有条路，路上有 $n$ 个车站，车站 $i$ 位于 $x_i$，每天有 $m$ 个人坐车，第 $j$ 个人从 $a_j$ 坐到 $b_j$。  
从车站 $i$ 坐到车站 $j$ 的票价为 $x_j-x_i(i<j)$ 卢布。

现在售票员想要多拿点钱，对于一个乘客，假设从车站 $A$ 坐到车站 $B$，则售票员可以选择两个车站编号 $C,D (A\leqslant C\leqslant D \leqslant B)$ 免去该乘客 $\left[C,D\right]$ 这一段的路费，也可以选择不免去任何路费。若免去一部分路费，那么这些免去的路费将会平均分给售票员和这位乘客作为利润。每一个乘客的 $C,D$ 可以不同。

相应的，每两个相邻车站 $i,i+1$ 的路段都有 $p_i$ 的概率被检查，如果被检查且存在没有购买这个路段车票的乘客，则每有一个没有购买这个路段车票的乘客，售票员都会被罚款 $c$ 卢布（乘客不管了，反正不影响答案）。

求售票员获得利润的最大期望。

## 说明/提示

$0 = x_1<x_2<\dots<x_n \leqslant 10^9$  
$2\leqslant n \leqslant 150000, 1\leqslant m \leqslant 300000, 1\leqslant c \leqslant 10000$  
$0\leqslant p_i \leqslant 100$

## 样例解释

样例 1：

第一位和第三位乘客都购买了 $[1,2]$ 路段的车票。  
第二位和第三位乘客 $[2,3]$ 这一路段的路费被免去，且一定不会被检查（$p_2=0$）  
总利润期望即为 $0 + \frac{90}2 + \frac{90}2 = 90$

## 样例 #1

### 输入

```
3 3 10
0 10 100
100 0
1 2
2 3
1 3
```

### 输出

```
90.000000000
```

## 样例 #2

### 输入

```
10 8 187
0 10 30 70 150 310 630 1270 2550 51100
13 87 65 0 100 44 67 3 4
1 10
2 9
3 8
1 5
6 10
2 7
4 10
4 5
```

### 输出

```
76859.990000000
```

# 题解

## 作者：Jerryfish (赞：1)

# Solution
因为对于每个乘客之间没有联系且任意两个不同的段赚的钱的期望之间也没有联系，所以将**和的期望**看作**期望的和**。

于是我们只关注在两个相邻的站点连成的段里优惠顾客所得利润的期望，因为有 $p_i$ 的概率被罚款 $c$ 元，所以可得期望：

$$
\operatorname{E}(money)=\frac{x_{i+1}-x_i}{2}-p_i\times c
$$

于是每两个相邻站点连成的段里的期望利润就可以求出来了。

现在回归到题目问的问题，我们可以把每个乘客上下车的站点看做一个区间，售票员只能在这个区间里一个连续的段里赚钱，所以这是一个没有修改，区间查询的最大连续字段和问题，线段树维护即可，$O(m\log n)$ 轻松跑过。

还是比较板。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
typedef double db;
const int N = 15e4 + 5;

struct Tree{
	int l, r;
	db Max, lmax, rmax, sum;
}tree[N << 2];

int n, m, c;
int x[N];
db p[N], ans;

void pushup(Tree &a, Tree &b, Tree &c) {
	a.sum = b.sum + c.sum;
	a.Max = max(b.Max, max(c.Max, b.rmax + c.lmax));
	a.lmax = max(b.sum + c.lmax, b.lmax); a.rmax = max(c.sum + b.rmax, c.rmax);
}

void build(int u, int l, int r) {
	tree[u].l = l; tree[u].r = r;
	if(l == r) {
		tree[u].Max = tree[u].lmax = tree[u].rmax = tree[u].sum = (db)(x[l + 1] - x[l]) / 2 - p[l] * c;//期望式子
		return ;
	}
	build(ls, l, mid); build(rs, mid + 1, r);
	pushup(tree[u], tree[ls], tree[rs]);
}

Tree query(int u, int l, int r, int L, int R) {
	if(L <= l && r <= R) return tree[u];
	Tree res1, res2, ans; int f1 = 0, f2 = 0;
	if(mid >= L) res1 = query(ls, l, mid, L, R), ++ f1 ;
	if(mid < R) res2 = query(rs, mid + 1, r, L, R), ++ f2 ;
	if(f1 && f2) pushup(ans, res1, res2);
	else if(f1) ans = res1;
	else ans = res2;
	return ans;
}

int main(){
	ios::sync_with_stdio(0);
	cin >> n >> m >> c;
	for (int i = 1; i <= n; ++ i ) cin >> x[i];
	for (int i = 1; i < n; ++ i ) {
		int tmp; cin >> tmp;
		p[i] = 1.0 * tmp / 100;
	}
	build(1, 1, n - 1);
	while(m -- ) {
		int xx, yy;
		cin >> xx >> yy;
		ans += max(0.0, query(1, 1, n - 1, xx, yy - 1).Max);
	}
	cout << fixed << setprecision(6) << ans;
	return 0;
}

```

---

## 作者：operator_ (赞：0)

# Smart Cheater

[题目传送门](https://www.luogu.com.cn/problem/CF150C)

## 题解

首先显然的，每个乘客是独立计算的，然后我们发现，一个乘客在 $i$ 到 $i+1$ 不买票的期望贡献是一定的，为 $\dfrac{x_{i+1}-x_i}{2}-c\times p_i$，所以我们其实就是要对于每个乘客的区间求最大子段和，简单线段树板子，感觉也没啥细节。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
	int s=0,m=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
	while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return m?-s:s;
}
int n,m,c;
double x[150005],p[150005],a[150005];
struct Node {int l,r;double ans,lans,rans,d;};
struct Segment_Tree {
  	Node t[4*150005];
	int ls(int p) {return p<<1;}
	int rs(int p) {return p<<1|1;}
	void pushup(int p) {
		t[p].d=t[ls(p)].d+t[rs(p)].d;
		t[p].ans=max(max(t[ls(p)].ans,t[rs(p)].ans),t[ls(p)].rans+t[rs(p)].lans);
		t[p].lans=max(t[ls(p)].lans,t[ls(p)].d+t[rs(p)].lans);
		t[p].rans=max(t[ls(p)].rans+t[rs(p)].d,t[rs(p)].rans);
	}
	void build(int p,int l,int r) {
		t[p].l=l,t[p].r=r;
		if(l==r) {t[p].d=t[p].lans=t[p].rans=t[p].ans=a[l];return;}
		int m=(l+r)>>1;
		build(ls(p),l,m);build(rs(p),m+1,r);
		pushup(p);
	}
	Node query(int p,int l,int r) {
		if(t[p].r<l||t[p].l>r) return {0,0,0,0,0,0};
		if(l<=t[p].l&&t[p].r<=r) return t[p];
		double s=0;int m=(t[p].l+t[p].r)>>1;
		Node x=query(ls(p),l,r),y=query(rs(p),l,r),ans;
		ans.d=x.d+y.d;
		ans.ans=max(max(x.ans,y.ans),x.rans+y.lans);
		ans.lans=max(x.lans,x.d+y.lans);
		ans.rans=max(x.rans+y.d,y.rans);
		return ans;
	}
}t;
double ans;
signed main() {
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++)
		scanf("%lf",&x[i]);
	for(int i=1;i<n;i++)
		scanf("%lf",&p[i]),p[i]/=100;
	for(int i=1;i<n;i++)
		a[i]=(x[i+1]-x[i])/2.0-c*p[i];
	t.build(1,1,n-1);
	while(m--) {
		int l=rd(),r=rd();
		ans+=t.query(1,l,r-1).ans;
	}
	printf("%.6lf",ans);
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意
一辆公交车依次经过直线上的 $n$ 个站，坐标依次为 $x_{1},x_{2}...x_{n}$，从第 ${i}$ 站到第 ${i+1}$ 站需要购买一张价格为 $x_{i+1}-x_{i}$ 的车票。有 $m$ 个乘客，他们分别从 $a_{i}$ 站上车，$b_{i}$ 站下车，，而对于每一个乘客，售票员可以选择一段区间 $[C_{i},D_{i}]$，使得这名乘客在这段区间无需买票，然后后售票员和乘客平分所获利润。但是，对于一段路 $[i,i+1]$，会有 $p_{i}$ 的概率查票，并对每一名没票的乘客处罚 $c$ 元。求售货员能得到的利润的期望的最大值。

$2\leqslant n\leqslant150000$，$1\leqslant m\leqslant300000$。

## 题目分析
题面有一些绕，要仔细阅读，理解题意。只要把握了题意，就可以很轻松地得到：道路与道路之间，乘客与乘客之间的期望是互相独立，互不影响的，可以单独计算期望，再根据期望可加性累加。

首先来处理道路。道路的价格、查票的概率和罚款都是固定的，所以对于每一个在这一段没票的乘客所得的利润的期望是可以直接算出来的，等于查票的概率乘利润减去罚款的差加上不查票的概率乘利润，也即 $p_{i}(\frac{(x_{i+1}-x_{i})}{2}-c)+(1-p_{i})\frac{(x_{i+1}-x_{i})}{2}$。

而对于每一个乘客，能得到的利润的期望就是指定区间中所选子区间的所有道路的期望值总合，如果把每条道路设为一个点，点权为所计算的期望，问题就赫然变为最大连续子段和，可以直接用线段树维护，支持区间查询就可以啦！如果线段树不明白可以直接看代码。

总复杂度 $O(m\log{n})$，可以轻松通过。

```cpp
#include<bits/stdc++.h>
#define mid (l+r>>1)
#define L x<<1
#define R x<<1|1
#define lc L,l,mid
#define rc R,mid+1,r
using namespace std;
const int N=15e4+5;
const double eps=1e-6;
int n,m,c,x[N],p[N];
double b[N],ans;
int l[N*2],r[N*2];
struct node{
	double w,lmax,rmax,mmax;//这四个变量分别表示区间和，左端区间最大和，右端区间最大和，整体的区间最大值和
}xd[N*4];
void getup(int x){
	xd[x].w=xd[L].w+xd[R].w;
	xd[x].lmax=max(xd[L].lmax,xd[L].w+xd[R].lmax);//左端的最大区间和，等于左儿子的左端最大区间和，或者左儿子的区间和加右儿子的左端最大区间和。
	xd[x].rmax=max(xd[R].rmax,xd[R].w+xd[L].rmax);//右端同理
	xd[x].mmax=max(xd[L].rmax+xd[R].lmax,max(xd[L].mmax,xd[R].mmax));//整体的最大区间和，要么跨过左右儿子的分界线，要么单独分布在左儿子或右儿子。
}
void build(int x,int l,int r){
	if(l==r){
		xd[x].lmax=xd[x].rmax=xd[x].mmax=xd[x].w=b[l];
		return;
	}
	build(lc),build(rc);
	getup(x);
}
node query(int x,int l,int r,int ll,int rr){
	if(l>=ll&&r<=rr)return xd[x];
	if(rr<=mid)return query(lc,ll,rr);
	if(ll>mid)return query(rc,ll,rr);
	node X=query(lc,ll,rr),y=query(rc,ll,rr),z;
	z.w=X.w+y.w;
	z.lmax=max(X.lmax,X.w+y.lmax);
	z.rmax=max(y.rmax,y.w+X.rmax);
	z.mmax=max(X.rmax+y.lmax,max(X.mmax,y.mmax));
	return z;
}
inline int read(){
	int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;
}
int main(){
	n=read(),m=read(),c=read();
	for(int i=1;i<=n;i++)x[i]=read();
	for(int i=1;i^n;i++)p[i]=read();
	for(int i=1;i<=m;i++)l[i]=read(),r[i]=read();
	for(int i=1;i^n;i++)b[i]=1.0*(x[i+1]-x[i])/2.0*(100-p[i])/(100*1.0)+1.0*p[i]/100*(1.0*(x[i+1]-x[i])/2.0-c);
	build(1,1,n-1);
	for(int i=1;i<=m;i++){
		node tmp=query(1,1,n-1,l[i],r[i]-1);
		double tr=tmp.mmax;
		if(tr>0)
		ans+=tr;
	}
	printf("%.6lf",ans);
	return 0;
}
```


---

