# Choose a Square

## 题目描述

Petya 最近发现了一个名为“选择正方形”的游戏。在这个游戏中，有 $n$ 个点，编号从 $1$ 到 $n$，分布在一张无限大的平面上。第 $i$ 个点的坐标为 $(x_i, y_i)$，其权值为 $c_i$。

你需要选择一个正方形，使得其边平行于坐标轴，下左角和上右角都在直线 $y = x$ 上，且所有角的坐标均为整数。

你的得分为被所选正方形覆盖的所有点的权值之和减去正方形的边长。注意，边长可以为零。

Petya 想让你计算在只选一个正方形的情况下，所能获得的最大得分。

## 说明/提示

下图对应于第一个样例：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1221F/e9d6acfe5801db49535c73c7e3aac9d122102fde.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
0 0 2
1 0 -5
1 1 3
2 3 4
1 4 -4
3 1 -1
```

### 输出

```
4
1 1 3 3
```

## 样例 #2

### 输入

```
5
3 3 0
3 3 -3
0 2 -1
3 1 3
0 0 -2
```

### 输出

```
0
1 1 1 1
```

# 题解

## 作者：jun头吉吉 (赞：9)

# CF1221F 【Choose a Square】
[$\color{red}\Large{\text{宣}}\color{black}\small\text{传}^{blog}$](https://chen-jia-liang.gitee.io/blog/2020/10/03/%E9%A2%98%E8%A7%A3-CF1221F-%E3%80%90Choose-a-Square%E3%80%91/)
## 题意
平面上有$n$个点$(x_i,y_i)$，每个点有一个权值$c_i$，请构造一个左下角与右上角在$y=x$上的正方形，使得正方形内的点的权值和减去正方形的边权最大。

> $p.s.$这里的`边权`可能翻译成`边长`更合适

> 边长可以为$0$

> $1\le n\le 5\cdot 10^5,0\le x_i,y_i\le 10^9,-10^6\le c_i\le 10^6$

## 题解

这是一个非常厉害的题目。

~~首先我们要明明确一个基本事实（雾：CF道道结论题~~
 
假设我们有一个正方形$(L,L)\to (R,R)$，那么我们来考虑$(x,y)$在其内部的条件是什么：

$$\begin{cases}L\le x\\ x\le R\\ L\le y\\ y\le R\end{cases}$$

整理得到$L\le \min(x,y),\max(x,y)\le R$，因此$x,y$的顺序并没有关系（从正方形的对称性也同样可以得到相同的结论）。

所以我们把一个点$(x,y)$看作是一条权值为$c$，$\min(x,y)\to \max(x,y)$的线段。记$l_i=\min(x_i,y_i),r_i=\max(x_i,y_i)$那么只有$[L,R]$完全包含$[l_i,r_i]$，才能统计$c_i$的权值。

首先根据国际惯例，对$x_i,y_i$，进行离散。~~由于是`CF`题，我们要多用用STL~~

进行离散过后，我们得到了所有边界的离散值。很显然，正方形在若不在边界上，权值和在边界上相同，边长更大，不是最优解。（只有一种情况不满足，等下会说）因此我们只需考虑边界。

假设我们有一个端点$L$，那么$L$的最大答案应该是多少呢？

首先，若一条线段$[l_i,r_i]$可能有贡献，则必然有$L\le l_i$，因此我们可以从大往小处理。

记$f(R)=\sum_{L\le l_i\land r_i\le R}c_i$，则显然$L\to R$的答案为

$$f(R)-(R-L)=f(R)-R+L$$

我们希望这个柿子最大，此时$L$已经定住了，实际上就是要求$f(R)-R$的最大值。

这个东西可以用线段树维护。记离散化后一共有$siz$个点，辣么先把$i$的初值赋为$-\text{对应的值}$，即原式中的$-R$，因为当一条线都没有的时候，$f(x)=0$。

然后考虑加线。从后往前加，则$L\le l$必然成立，只需考虑$r\le R$的成立即可。很容易得到，就是给$[r,siz]$全部$+=c$

再维护一下最大值以及位置就好了。

值得注意的一点，因为边长可以等于零，所以当所有点权都小于零时，最大值必然是$0$。此时不再边界时去到，一开始赋初值即可。

## 代码
~~用iPad打的很丑不要介意~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
struct Point{
    int l,r,w;
}P[N];
struct node{
    pair<long long,int>ans;
    long long tag;
    int l,r;
}T[N*8];
#define lson (x<<1)
#define rson (x<<1|1)
void pushup(int x){
    T[x].ans=max(T[lson].ans,T[rson].ans);
}
void pushdown(int x){
    if(T[x].tag){
        T[lson].tag+=T[x].tag;T[lson].ans.first+=T[x].tag;
        T[rson].tag+=T[x].tag;T[rson].ans.first+=T[x].tag;
        T[x].tag=0;
    }
}
vector<int>num;
void build(int x,int l,int r){
    T[x].l=l,T[x].r=r;
    if(l==r){T[x].ans={-num[l],l};return;}
    int mid=l+r>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    pushup(x);
}
pair<long long,int>query(int x,int l,int r){
    if(l<=T[x].l&&T[x].r<=r)return T[x].ans;
    pushdown(x);
	int mid=T[x].l+T[x].r>>1;
    if(r<=mid)return query(lson,l,r);
    if(mid<l)return query(rson,l,r);
    return max(query(lson,l,r),query(rson,l,r));
}
void upd(int x,int l,int r,int val){
    if(l<=T[x].l&&T[x].r<=r){T[x].ans.first+=val;T[x].tag+=val;return;}
    pushdown(x);
    int mid=T[x].l+T[x].r>>1;
    if(l<=mid)upd(lson,l,r,val);
    if(mid<r)upd(rson,l,r,val);
    pushup(x);
}
int n;
#define pb push_back
vector<pair<int,int>>v[N*2];
signed main(){
    scanf("%d",&n);
    for(int i=1,x,y,w;i<=n;i++)
        scanf("%d%d%d",&x,&y,&w),
        num.pb(x),num.pb(y),
        P[i]=(Point){min(x,y),max(x,y),w};
    sort(num.begin(),num.end());
    num.resize(unique(num.begin(),num.end())-num.begin());
    for(int i=1;i<=n;i++){
        int l=lower_bound(num.begin(),num.end(),P[i].l)-num.begin();
        int r=lower_bound(num.begin(),num.end(),P[i].r)-num.begin();
        v[l].pb({r,P[i].w});
    }
    build(1,0,num.size()-1);
    long long ans=0,ansl=2e9,ansr=2e9;
    for(int i=num.size()-1;i>=0;i--){
        for(auto to:v[i])
            upd(1,to.first,num.size()-1,to.second);
        auto ret=query(1,i,num.size()-1);
        ret.first+=num[i];
        if(ret.first>ans)
            ans=ret.first,
            ansl=num[i],ansr=num[ret.second];
    }
    cout<<ans<<"\n"<<ansl<<" "<<ansl<<" "<<ansr<<" "<<ansr;
}
```

---

## 作者：ljc20020730 (赞：4)

首先设正方形左下角坐标为$(l,l)$，右上角坐标是$(r,r)$,

那么对于所有满足$l \leq a,b \leq r $的点$(a,b)$，都在这个正方形内部。

即$min(a,b) \geq l , max(a,b) \leq r$同时成立。

所以，一个点就变成一段$[min(a,b) , max(a,b)]$的区间。

原问题就转化为

> 在线段上找到一个区间$[L,R]$使得这个区间内所有线段权值和加上$R-L$的值最小。

首先，我们先不管$R-L$这部分贡献，其他的东西都可以离散化后从末尾扫到$1$，每个遇到区间开头$l$，就将区间结尾$r$ 到末尾区间 $+w_i$。

所以，我们需要维护一棵线段树记录最大值及其所在编号。

对于一段确定的区间的左端点固定，右端点只需要在线段树里一开始加上$-R$的贡献即可，接下去的方法就同上了。

比较坑的地方是，离散化后元素个数会到$2n$级别，所以需要开$10^6$级别的数组。

时间复杂度是$O(n log_2 n)$


```cpp
# include <bits/stdc++.h>
# define int long long
# define inf (1e14)
using namespace std;
const int N=1e6+10;
int n;
vector< pair<int,int> >v[N];
vector< int >tmp;
struct Seg {
	int ret,id,tag;
	Seg() { ret=-inf;}
}tr[N<<2];
struct node{ int l,r,w; }a[N];
# define lson ls,l,mid
# define rson rs,mid+1,r
# define mid (l+r>>1)
# define ls (x<<1)
# define rs (x<<1|1)
void up(int x) {
	tr[x].ret = max(tr[ls].ret,tr[rs].ret);
	if (tr[ls].ret < tr[rs].ret) tr[x].id = tr[rs].id;
	else tr[x].id = tr[ls].id;
}
void down(int x) {
	if (!tr[x].tag) return;
	tr[ls].tag+=tr[x].tag; tr[ls].ret+=tr[x].tag;
	tr[rs].tag+=tr[x].tag; tr[rs].ret+=tr[x].tag;
	tr[x].tag=0;
}
void build(int x,int l,int r) {
	if (l==r) { tr[x].ret = -tmp[l-1],tr[x].id=l; return;}
	build(lson); build(rson);
	up(x);
}
void update(int x,int l,int r,int opl,int opr,int d) {
	if (opl<=l&&r<=opr) {
		tr[x].tag+=d; tr[x].ret+=d;
		return;
	}
	down(x);
	if (opl<=mid) update(lson,opl,opr,d);
	if (opr>mid) update(rson,opl,opr,d);
	up(x);
}
pair<int,int> query(int x,int l,int r,int opl,int opr) {
	if (opl<=l && r<=opr) {
		return make_pair(tr[x].ret,tr[x].id);
	}
	down(x);
	pair<int,int> ret = make_pair(-inf,-1);
	if (opl<=mid) ret = max(ret,query(lson,opl,opr));
	if (opr>mid) ret= max(ret,query(rson,opl,opr));
	return ret;
}
signed main() {
	scanf("%lld",&n);
	for (int i=1;i<=n;i++) {
		int x,y,c; scanf("%lld%lld%lld",&x,&y,&c);
		tmp.push_back(x); tmp.push_back(y);
		a[i] = (node) {min(x,y),max(x,y),c};
	}
	int T = 0;
	sort(tmp.begin(),tmp.end());
	tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
	for (int i=1;i<=n;i++) {
		int l = lower_bound(tmp.begin(),tmp.end(),a[i].l) - tmp.begin() + 1;
		int r = lower_bound(tmp.begin(),tmp.end(),a[i].r) - tmp.begin() + 1;
		T=max(T,r);
		v[l].push_back(make_pair(r,a[i].w));
	}
	build(1,1,T);
	int ans = -inf,ansl,ansr;
	for (int i=T;i>=1;i--) {
		for (int j=0;j<v[i].size();j++) {
			pair<int,int> to = v[i][j];
			update(1,1,T,to.first,T,to.second);
		}
		pair<int,int>ret = query(1,1,T,i,T);
		ret.first +=tmp[i-1];
		if (ret.first > ans) {
			ans  = ret.first;
			ansl = tmp[i-1]; ansr = tmp[ret.second-1];
		}
	}
	if (ans < 0) {
		ans = 0; ansl=ansr=tmp[T-1]+1;
	}
	printf("%lld\n%lld %lld %lld %lld\n",ans,ansl,ansl,ansr,ansr);
	return 0;
}
```

---

## 作者：XiaoQuQu (赞：3)

翻了一下题解，发现已有的题解讲的好像不是很清楚，这里投一篇比较好理解的题解。

对于一个点 $(x,y)$，他能被一个两端点为 $l,r$ 的正方形覆盖，当且仅当 $l\le \min(x,y)\le \max(x,y)\le r$。由于正方形具有对称性，对于每一个 $x>y$ 的点 $(x,y)$，我们不妨将它对于 $y=x$ 这条直线对称过去，得到 $(y,x)$，这样就保证了每个点 $(x,y)$ 都有 $x<y$。

将这个“点”的概念再抽象一下，我们可以将问题转化为：给定 $n$ 端区间 $[l_i,r_i]$，求选出一个区间 $[x,y]$，使得被 $[x,y]$ 完全包含的区间的权值和减去 $y-x$ 的值最大，我们将“被 $[x,y]$ 完全包含的区间权值和”设为 $f(x,y)$，也就是要最大化 $f(x,y)-(y-x)=f(x,y)-y+x$。

考虑固定左端点 $x$ 不动，问题转换成了求一个 $y$，使得 $f(x,y)-y$ 最大（因为 $x$ 已被固定，所以不用考虑）。

这样我们很自然的就可以想到从大到小枚举每个 $x$，对于每个 $x$，将以 $x$ 为左端点的区间加入到我们需要考虑的范围内，然后求出一个 $f(x,y)-y$ 更新答案。

发现其实求 $f(x,y)-y$ 的过程，就是一个求区间最大值的过程，直接用线段树维护即可。

```cpp
/*
* mid: (l + r) >> 1
* lson: (p << 1)
* rson: (p << 1 | 1)
*/
const int MAXN = 2e6 + 5;
struct _point {
	int l, r, w;
} p[MAXN];
vector<_point> t[MAXN];
struct _node {
	int r, mx, tg;
} tr[MAXN << 1];
int n, m, anss, pos1 = 1e9 + 114514191, pos2 = 1e9 + 114514191;
vector<int> v;

void pushup(int p) {
	if (tr[lson].mx > tr[rson].mx) tr[p].mx = tr[lson].mx, tr[p].r = tr[lson].r;
	else tr[p].mx = tr[rson].mx, tr[p].r = tr[rson].r;
}

void addtag(int p, int l, int r, int k) {
	tr[p].mx += k, tr[p].tg += k;
}

void pushdown(int p, int l, int r) {
	if (!tr[p].tg) return;
	addtag(lson, l, mid, tr[p].tg); 
	addtag(rson, mid + 1, r, tr[p].tg);
	tr[p].tg = 0;
}

void build(int p, int l, int r) {
	if (l == r) return tr[p] = {r, -v[r], 0}, void();
	build(lson, l, mid); build(rson, mid + 1, r);
	pushup(p);
}

void update(int p, int l, int r, int L, int R, int k) {
	if (L <= l && r <= R) return addtag(p, l, r, k);
	pushdown(p, l, r);
	if (L <= mid) update(lson, l, mid, L, R, k);
	if (mid < R) update(rson, mid + 1, r, L, R, k);
	pushup(p);
}

void query(int p, int l, int r, int L, int R, int &ans, int &pos) {
	if (L <= l && r <= R) return ans = tr[p].mx, pos = tr[p].r, void();
	pushdown(p, l, r);
	if (mid >= R) return query(lson, l, mid, L, R, ans, pos);
	if (L > mid) return query(rson, mid + 1, r, L, R, ans, pos);
	int a1, p1, a2, p2;
	query(lson, l, mid, L, R, a1, p1); query(rson, mid + 1, r, L, R, a2, p2);
	if (a1 >= a2) return ans = a1, pos = p1, void();
	else return ans = a2, pos = p2, void();
}

void work() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i].l >> p[i].r >> p[i].w;
		if (p[i].l > p[i].r) swap(p[i].l, p[i].r);
		v.push_back(p[i].l), v.push_back(p[i].r);
	}
	sort(v.begin(), v.end());
	m = unique(v.begin(), v.end()) - v.begin();
    v.resize(m);
	for (int i = 1; i <= n; ++i) {
	    p[i].l = lower_bound(v.begin(), v.end(), p[i].l) - v.begin();
	    p[i].r = lower_bound(v.begin(), v.end(), p[i].r) - v.begin();
	    t[p[i].l].push_back({p[i].l, p[i].r, p[i].w});
 	}
    build(1, 0, m - 1);
 	for (int i = m - 1; i >= 0; --i) {
 		for (int j = 0; j < (int)t[i].size(); ++j) update(1, 0, m - 1, t[i][j].r, m - 1, t[i][j].w);
        int ans, pos; query(1, 0, m - 1, i, m - 1, ans, pos);
        ans += v[i];
        if (ans > anss) anss = ans, pos1 = v[i], pos2 = v[pos];
 	}
    cout << anss << endl;
    cout << pos1 << ' ' << pos1 << ' ' << pos2 << ' ' << pos2 << endl;
}
```

[完整代码](http://175.155.65.14:10375/r?cid=3daf0059-ccd6-488b-b80c-be471b9c0b81)。

---

## 作者：cjlak1o1 (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1221F)  

[博客食用更佳哦](https://www.cnblogs.com/windseekerblog/p/16556342.html)

蒟蒻真的是菜啦，花一天时间才过这道题。

如果您是巨佬，还请移步至楼上@jun头吉吉的题解。

### 题目大意

有 $n$ 个点求构造一个内部点权（包含边界）减去边长最大的，对角线在 $y=x$ 上的正方形。输出内部点权减去边长的值，以及正方形左下角和右上角的坐标。

### 核心思路

正方形需要考虑直线 $y=x$ 两边的操作，方便起见，根据正方形的对称性，我们直接把在直线下方的点关于直线对称到直线上方（将横纵坐标交换即可），那么这道题就变成了求一个等腰直角三角形。

考虑到如果三角形的边界上没有点的话，相当于在一个边界有点的三角形的基础上进行扩大，边权变大，显然较劣，所以每次都考虑边上有点的情况。

由于边都是平行于 $x$ 轴和 $y$ 轴的，所以我们想到用线段树家扫描线的方法求解。

### 具体操作

我们按照 $y$ 为第一关键字从小到大排序。

对 $x$ 和 $y$ 分别进行离散操作，以离散后的 $x$ 序列的下标为叶子节点建立线段树。

接下来考虑两种操作：

1. 在当前扫描线上加点。

对于这种情况，由于新加点只会被三角形顶点的 $x$ 坐标更小的包含，所以我们进行区间加，从 $1$ 到 $idx$ 加 $w$。（$idx$ 表示离散后的位置）

2. 扫描线上移，并新加点。

这种情况就比较麻烦了。

- 由于上一条线已经处理完了，所以我们要对其询问取 $\max$ ，取从 $1$ 到 $x$ 的最大值。

- 扫描线上移，意味着每一个 $x$ 上建立三角形的边长会增加，我们分两部分处理，一部分是上一次线上包含的 $x$ ,另一部分是新加的 $x$ ,分别为图中标蓝和标红的区域。蓝色区间加，红色暴力枚举修改。

![](https://cdn.luogu.com.cn/upload/image_hosting/6tsnod55.png)

还要记得预处理第一根线。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
#define fi first
#define se second
#define ls rt<<1
#define rs rt<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
using namespace std;
const int N=5e5+1e4,Inf=1e15+7;

int read(){
	int res=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<1)+(res<<3)+(c^48);
	return res*f;
}

int n,Px[N],cntx,Py[N],cnty,last=-1;
struct node{
	int x,y,w;
	bool operator < (const node &b)const{return y==b.y?x<b.x:y<b.y;}
}a[N];

struct TREE{
	int sum,id,lazy;
}t[N<<2];
void push_up(int rt){
	t[rt].sum=max(t[ls].sum,t[rs].sum);
	t[rt].id=t[ls].sum>t[rs].sum?t[ls].id:t[rs].id;
}
void push_down(int rt,int l,int r){
	if(t[rt].lazy){
		int k=t[rt].lazy,mid=(l+r)>>1,Len=mid-l+1,Ren=r-mid;
		t[ls].sum+=k,t[rs].sum+=k,t[ls].lazy+=k,t[rs].lazy+=k,t[rt].lazy=0; 
	}
}
void build(int rt,int l,int r){
	if(l==r) return t[rt].id=l,void();
	int mid=(l+r)>>1;build(lson),build(rson),push_up(rt);
}
void update(int rt,int l,int r,int ul,int ur,int k){
	if(ul<=l&&r<=ur) return t[rt].sum+=k,t[rt].lazy+=k,void();
	push_down(rt,l,r);int mid=(l+r)>>1;
	if(ul<=mid) update(lson,ul,ur,k);
	if(mid<ur) update(rson,ul,ur,k);
	push_up(rt);
}
void update(int rt,int l,int r,int ul,int ur){
	
}
pair<int,int> query(int rt,int l,int r,int ql,int qr){
	if(ql>r||l>qr) return mp(0ll,-1ll);
	if(ql<=l&&r<=qr) return mp(t[rt].sum,t[rt].id);
	int mid=(l+r)>>1;
	return max(query(lson,ql,qr),query(rson,ql,qr));
}

pair<int,int> ans;
int upup;

signed main(){
	n=read();upup=1e9+1,ans.se=1e9+1;//蒟蒻比较菜，初始化还请参考其他巨佬，这样卡数据上界也可以过
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read(),a[i].w=read();
		if(a[i].x>a[i].y) swap(a[i].x,a[i].y);
		Px[++cntx]=a[i].x;Py[++cnty]=a[i].y;
	}
	sort(a+1,a+n+1);sort(Px+1,Px+n+1);sort(Py+1,Py+n+1);
	cntx=unique(Px+1,Px+n+1)-Px-1;
	cnty=unique(Py+1,Py+n+1)-Py-1;
	build(1,1,cntx);//以离散后的x为叶子节点建树 
	int ur1=upper_bound(Px+1,Px+cntx+1,a[1].y)-Px-1;
	for(int i=1;i<=ur1;i++) update(1,1,cntx,i,i,Px[i]-a[1].y);
	int idx,_idx,idy,_idy;
	for(int i=1;i<=n+1;i++){
		if(i<=n) idx=lower_bound(Px+1,Px+cntx+1,a[i].x)-Px,idy=lower_bound(Py+1,Py+cnty+1,a[i].y)-Py;
		if((i!=1&&idy!=_idy)||i==n+1){//扫描线上移
			last=a[i-1].y;
			pair<int,int> sum=query(1,1,cntx,1,_idx);
			if(sum.fi>ans.fi) ans.fi=sum.fi,ans.se=Px[sum.se],upup=a[i-1].y;
			if(i==n+1) break;
			int ur=upper_bound(Px+1,Px+cntx+1,a[i-1].y)-Px-1,uR=upper_bound(Px+1,Px+cntx+1,a[i].y)-Px-1;
			//ur,uR分别表示两条线上最靠右的存在的x
			update(1,1,cntx,1,ur,a[i-1].y-a[i].y);//蓝色部分
			for(int j=ur+1;j<=uR;j++) update(1,1,cntx,j,j,Px[j]-a[i].y);//红色部分
		}
		if(i<=n) update(1,1,cntx,1,idx,a[i].w);
		_idx=idx,_idy=idy;
	}
	printf("%lld\n%lld %lld %lld %lld\n",ans.fi,ans.se,ans.se,upup,upup);
	return 0;
}
/*
7
5461255 4302067 16
1325913 2652299 15
1735 2640383 11
5293204 2140683 29
3729701 5526121 14
2769558 6182111 22
4396749 3148205 17
*/
/*
0
500000 500000 500000 500000
*/
```

---

## 作者：cxoi1610 (赞：1)

首先，我们不能考虑直接做。

所以我们把所有在 $x=y$ 这条直线以下的所有点全部对称到上面，这样原本的正方形就变成了等腰直角三角形，更加方便我们去维护。

然后，我们将所有点的坐标离散化。

现在，我们就可以建出线段树，维护每个纵坐标的权值，线段树当前的值为负的纵坐标。

考虑怎么去统计答案，我们可以从上到下枚举一条直线，令当前直线为 $i$。
我们把将在当前直线之上的点全部加入线段树。

最后我们查询纵坐标在 $[i,n]$ 中的权值最大值，然后在加上当前直线 $i$ 的横坐标，这就相当于求出来权值和(边长)了。

---

## 作者：strcmp (赞：1)

显然对于正方形 $(u,\,u),\,(v,\,v)$。$(x,\,y)$ 包含在其内部的充要条件是 $u \le \min(x,\,y) \le \max(x,\,y) \le v$。

原问题转化为求 $[l,\,r]$，使得 $l \le \min(x,\,y) \le \max(x,\,y) \le r$ 的点权值和减去 $r - l$ 最大。

即求 $[L,\,R]$ 包含的所有线段权值总和减去 $R - L$ 最大。

不妨考虑扫描线，每次加入一个右端点 $R$，找出来所有 $r$ 在这个右端点上的 $[l,\,r]$ 对，给线段树 $[1,\,l]$ 这区间加上 $[l,\,r]$ 的贡献。然后查询全局的最大值。

有一个妙妙的方法处理掉这个 $r - l$，就是对于 $1 \le i \le p$（$p$ 为离散化后的点坐标数），把 $i$ 加上 $a_i$。（$a$ 是排序且去重了的坐标序列）

那么每次得到最大值都把它减去 $a_R$，就可以还原出减去了 $r - l$ 的最大值了。

时间复杂度 $\Theta(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef long long int ll;
const int maxn = 1e6 + 10;
const ll inf = 114514191981052013LL;
using pll = pair<ll, ll>; int n;
struct Node {
    ll mx, tg;
} t[maxn << 2];
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mx(x) (t[x].mx)
#define tg(x) (t[x].tg)
inline void pushup(int x) { mx(x) = max(mx(ls(x)), mx(rs(x))); }
inline void pushdw(int x) {
    if (tg(x)) {
        tg(ls(x)) += tg(x), tg(rs(x)) += tg(x);
        mx(ls(x)) += tg(x), mx(rs(x)) += tg(x); tg(x) = 0;
    }
}
void modfiy(int l, int r, int ml, int mr, ll v, int x) {
    if (ml <= l && r <= mr) { mx(x) += v; tg(x) += v; return; }
    int mid = l + r >> 1; pushdw(x);
    if (ml <= mid) modfiy(l, mid, ml, mr, v, ls(x));
    if (mr > mid) modfiy(mid + 1, r, ml, mr, v, rs(x));
    pushup(x);
}
ll x[maxn], y[maxn], z[maxn], a[maxn], ans = 0; int p = 0;
vector<pll> v[maxn];
int findwz(int l, int r, int x) {
    if (l == r) return l;
    int mid = l + r >> 1; pushdw(x);
    if (mx(x) == mx(ls(x))) return findwz(l, mid, ls(x));
    else return findwz(mid + 1, r, rs(x));
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld", &x[i], &y[i], &z[i]);
        a[++p] = x[i], a[++p] = y[i];
    }
    sort(a + 1, a + p + 1);
    p = unique(a + 1, a + p + 1) - a - 1;
    for (int i = 1; i <= n; i++) {
        x[i] = lower_bound(a + 1, a + p + 1, x[i]) - a, y[i] = lower_bound(a + 1, a + p + 1, y[i]) - a;
        v[max(x[i], y[i])].push_back({ min(x[i], y[i]), z[i] });
    }
    ll ax = 2e9 - 1, ay = 2e9 - 1;
    for (int i = 1; i <= p; i++) {
        for (auto d : v[i]) modfiy(1, p, 1, d.X, d.Y, 1);
        modfiy(1, p, i, i, a[i], 1);
        if (mx(1) - a[i] > ans) ans = mx(1) - a[i], ax = a[findwz(1, p, 1)], ay = a[i];
    }
    printf("%lld\n%lld %lld %lld %lld\n", ans, ax, ax, ay, ay);
    return 0;
}
```

---

## 作者：Hollis_Yang (赞：1)

首先，我们把所有 $y<x$ 的点按直线 $y=x$ 对称，这样显然不会影响答案的计算。

然后问题就变成了画一个等腰直角三角形，使得其内部的点的权值和减直角边最大。


我们把与x轴平行的那条三角形的边叫做横边，另一条叫做竖边。


考虑我们已经确定了三角形的竖边所在的 $x$ 值，现在要截一条横边，使得其内部的点的权值和减去 ( (横边和竖边的交点的 $x$ 值) 和 (竖边的所在的 $x$ 值) 的差)最大。

![](https://cdn.luogu.com.cn/upload/image_hosting/vy50wchl.png)

绿色的是竖边，黄色的是横边，蓝色的是点。

然后有一个非常显然的结论是我们的这两条边都是截在点上的。

于是我们扫描线一下从大到小枚举所有点的 $x$ 值,尝试把竖边放在这里，然后我们需要知道横边截在哪里可以使得答案最大。

我们考虑直接用数组维护截在每一个 $y$ 的时候的答案，每次对于现在的竖边所在的  $x$ 值找出第一个比它大的点的 $y$ 值，然后就是对于每个后缀查询最大值。

考虑怎么在竖边移动时维护这个数组，我们使用线段树，每次把现在竖线上的点对应 $y$ 值加上其权值，然后考虑还要减去每个 $y$ 值和当前 $x$ 的差，不好维护，我们把它差分一下，变成对于每个后缀查询最大前缀和，不会的可以先学一学区间最大子段和。

具体实现可以看代码，就是写的比较屎，不够优美（虽然是 114514 倍常数的线段树，但是最慢的点还是 1.5s 左右）

还有一个感觉比较有趣的内容是答案的初始化，可以看看代码（（（



虽然是

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls p<<1
#define rs p<<1|1
#define hor(i,l,r) for(register int i=l;i<=r;i++)
#define lor(i,l,r) for(register int i=l;i>=r;i--)
using namespace std;
const int N=5e5+10;
int a[N],n,cnt,ans,mp[N],_x,_y;
struct node{
	int lsum,sum,pos;
	void out(){printf("%lld %lld %lld\n",lsum,sum,pos);}
};struct sgt{
	node t[4*N];
	node merge(node a,node b){node rt;
		if(a.lsum>(a.sum+b.lsum)) rt=(node){a.lsum,a.sum+b.sum,a.pos};
		else rt=(node){a.sum+b.lsum,a.sum+b.sum,b.pos};return rt;
	}void build(int p,int l,int r){
		if(l==r){
			t[p].lsum=t[p].sum=-(a[l]-a[l-1]);
		//	printf("%lld %lld\n",l,t[p].sum);
			return (void)(t[p].pos=l);
		}build(ls,l,mid);build(rs,mid+1,r);
		t[p]=merge(t[ls],t[rs]);
	}void update(int p,int l,int r,int pos,int v){
		if(l==r) return (void)(t[p].lsum=t[p].sum=v);
		if(pos<=mid) update(ls,l,mid,pos,v);
		if(pos>mid) update(rs,mid+1,r,pos,v);
		t[p]=merge(t[ls],t[rs]);
	}void add(int p,int l,int r,int pos,int v){
		if(l==r){
			t[p].lsum+=v;
			t[p].sum+=v;
			//printf("!!!!%d %d %d\n",t[p].sum,l,v);
			return;
		}if(pos<=mid) add(ls,l,mid,pos,v);
		else add(rs,mid+1,r,pos,v);
		t[p]=merge(t[ls],t[rs]);
	//	printf("!!%d %d %d %d %d\n",p,l,r,pos,v);
	}node query(int p,int l,int r,int L,int R){
	//	printf("%d %d %d %d %d %d\n",p,l,r,L,R,t[p].sum);
		if(L<=l&&r<=R) return t[p];
		if(R<=mid) return query(ls,l,mid,L,R); 
		if(mid<L) return query(rs,mid+1,r,L,R);
		return merge(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
	}
}T;
struct point{
	int x,y,c;
}p[N];
bool cmp(point a,point b){return a.x>b.x;}
signed main(){
	scanf("%lld",&n);
	hor(i,1,n){
		scanf("%lld%lld%lld",&p[i].x,&p[i].y,&p[i].c);
		if(p[i].x<=n+1&&p[i].y<=n+1&&p[i].x==p[i].y) mp[i]=1;
		if(p[i].y<p[i].x) swap(p[i].x,p[i].y);a[i]=p[i].y;
	}sort(a+1,a+n+1);cnt=unique(a+1,a+1+n)-a-1;
	T.build(1,1,cnt);
	int lst=0;sort(p+1,p+n+1,cmp);
	hor(i,1,n+1) if(!mp[i]) _x=_y=i;
//	hor(j,1,cnt) printf("%d\n",T.query(1,1,cnt,j,j).sum);
	hor(i,1,n){
		if(i!=n&&p[i+1].x==p[i].x) continue;
		hor(j,lst+1,i){
			int ad=lower_bound(a+1,a+cnt+1,p[j].y)-a;
			T.add(1,1,cnt,ad,p[j].c);
		//	printf("%d %d\n",p[j].c,ad);
		}
		lst=i;
		int pos=lower_bound(a+1,a+cnt+1,p[i].x)-a;if(pos>cnt) break;
	//	hor(j,1,cnt) printf("%d ",T.query(1,1,cnt,j,j).sum);printf("\n");
		T.add(1,1,cnt,pos,a[pos]-a[pos-1]);
		T.add(1,1,cnt,pos,-(a[pos]-p[i].x));
		node pp=T.query(1,1,cnt,pos,cnt); 
	//	hor(j,1,cnt) printf("%d ",T.query(1,1,cnt,j,j).sum);printf("\n");
		T.add(1,1,cnt,pos,(a[pos]-p[i].x));
		T.add(1,1,cnt,pos,-(a[pos]-a[pos-1]));
		//printf("%d %d %d\n",pp.sum,pp.lsum,pp.pos);
		if(pp.lsum>ans) _x=p[i].x,_y=a[pp.pos],ans=pp.lsum;
	}printf("%lld\n",ans);
	printf("%lld %lld %lld %lld",_x,_x,_y,_y);
	return (0-0);
}



```


---

## 作者：Chthologist7507 (赞：1)

upd：句末加了句号（。

毒瘤扫描线/tuu。

题意说的很清楚了，然后注意一下 **正方形边长可以是 0**。

我们知道一个点 $(x,y)$ 在正方形 $(l,l)\rightarrow(r,r)$ 内时有 $l\leq x,y\leq r$。

然后考虑一条直线 $y=x$，我们将其下的点全部沿它对称翻到上面去这样就有 $x\leq y$，连接 $(x,y)$ 和 $(y,x)$ 得到一条权值为 $c$ 的线段，这样就将题意化为被正方形包含的边的边权和与正方形边长的差。

具体来说，就是求
$$\sum\limits_{i\in[1,n],l\leq l_i,r_i\leq r}c_i-r+l$$

的最大值。

$l$ 不变，就只用求前面那一坨的最大值了。

这样就可以扫描线了，用线段树维护。

设离散化后有 $m$ 个点，从后往前把线加进去，显然有  $l_i>l$，那么只要让 $r_i<r$ 即可，将 $[r_i,m]+c$，查询 $[i,m]$。

然后维护一下最大值，位置即可，注意最大值小于 0 时要特判一下即可。

code:

```cpp
// Problem: CF1221F Choose a Square
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1221F
// Memory Limit: 250 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define inl inline
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)
#define pii pair<int,int>
using namespace std;
const int N=1e6+10,inf=1e13;
int n,tag[N<<2];
#define s first
#define id second
pii t[N<<2];
struct Node{
	int x,y,c;
}a[N];
vector<int>v;
vector<pii>g[N];
namespace tree{
	#define ls k<<1
	#define rs k<<1|1
	#define mid ((l+r)>>1)
	#define pushup(k)t[k]=make_pair(max(t[ls].s,t[rs].s),t[ls].s<t[rs].s?t[rs].id:t[ls].id)
	inl void pushdown(int k,int l,int r){
		if(!tag[k])return ;
		tag[ls]+=tag[k];tag[rs]+=tag[k];
		t[ls].s+=tag[k];t[rs].s+=tag[k];
		tag[k]=0;
	}
	inl void build(int k,int l,int r){
		if(l==r){t[k]=make_pair(-v[l-1],l);return;}
		build(ls,l,mid);build(rs,mid+1,r);pushup(k);
	}
	inl void update(int k,int l,int r,int x,int y,int v){
		if(x>r||y<l)return ;
		if(x<=l&&y>=r){tag[k]+=v;t[k].s+=v;return ;}
		pushdown(k,l,r);update(ls,l,mid,x,y,v);update(rs,mid+1,r,x,y,v);pushup(k);
	}
	pii query(int k,int l,int r,int x,int y){
		if(x>r||y<l)return make_pair(-inf,-inf);
		if(x<=l&&y>=r)return t[k];
		pushdown(k,l,r);
		return max(query(ls,l,mid,x,y),query(rs,mid+1,r,x,y));
	}
}
using namespace tree;
signed main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	rep(i,1,n){
		int x,y,c;cin>>x>>y>>c;
		v.push_back(x);v.push_back(y);a[i]=(Node){min(x,y),max(x,y),c};
	}
	int m=0;
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	rep(i,1,n){
		int x=lower_bound(v.begin(),v.end(),a[i].x)-v.begin()+1,y=lower_bound(v.begin(),v.end(),a[i].y)-v.begin()+1;
		m=max(m,y);
		g[x].push_back(make_pair(y,a[i].c));
	}
	build(1,1,m);
	int ans=-inf,l,r;
	pre(i,m,1){
		rep(j,0,g[i].size()-1){
			pii tmp=g[i][j];
			update(1,1,m,tmp.first,m,tmp.second);
		}
		pii tmp=query(1,1,m,i,m);
		tmp.first+=v[i-1];
		if(tmp.first>ans){
			ans=tmp.first;
			l=v[i-1],r=v[tmp.second-1];
		}
	}
	if(ans<0)ans=0,l=r=v[m-1]+1;
	cout<<ans<<'\n'<<l<<' '<<l<<' '<<r<<' '<<r;
}

```

---

## 作者：Southern_Dynasty (赞：0)

首先先把所有点转到 $y=x$ 上方。这样图形就变成了一个等腰直角三角形，而且不影响答案。

具体操作就是 `if(x>y) swap(x,y);`。

然后离散化。

显然最优正方形的左下角和右下角坐标都是等于某个点的坐标的。证明可以考虑把正方形扩大，此时边长也会扩大，显然不优。

考虑扫描线。从小到大枚举存在的点的纵坐标 $y$，将横坐标等于 $y$ 的点加入一个数据结构内维护。

具体地，维护一个线段树。每一个叶子 $x$ 存的值是以 $(x,x)$ 为左下角，$(y,y)$ 为右上角的正方形的权值和。

很明显，以 $(x,x)$ 为左下角，$(y,y)$ 为右上角的正方形的价值为：

$$
(\sum c_i)-(lsh_y-lsh_x)
$$

$lsh$ 就是离散化前的值。

发现 $lsh_y$ 是定值。所以只需要维护 $(\sum c_i)+lsh_x$ 的最大值即可。

然后由于要求坐标，所以对于每个节点再记录一下其最大价值是由哪个叶子节点得来的，合并显然。

现在考虑所有横坐标 $=y$ 的点 $i$，设其为 $(x,y)$。显然该点对于所有的 $(j,j),1\le j\le x$ 都有贡献。对线段树上 $[1,x]$ 区间集体加上 $c_i$ 即可。

注意 $c_i$ 可能有负数，并且边长会变，所以对于每个 $y$ 都要求一下最大值。而且边长可以为 $0$，所以答案初始设为 $0$ 即可。

一点点小细节：枚举 $y$ 前先建出线段树，每个点的权值为 $lsh_x$，然后枚举。还有离散化数组要开到 $2n$。还有在建树时，只能初始化 $x$ 坐标对应叶子节点的值。

时间复杂度 $O(n\log n)$。

[Code](https://codeforces.com/contest/1221/submission/214346663)

---

## 作者：AKPC (赞：0)

复健后我秒掉的第一道紫题。

将坐标离散化后，因为选取正方形的左下端、右上端都在 $y=x$ 直线上，所以可以转化题意：

>有 $n$ 个线段，第 $i$ 个线段的左右两端为 $\min\{x_i,y_i\},\max\{x_i,y_i\}$，权值为 $c_i$。你需要选取一个区间使得得分最大。其中选取区间的得分为，这个区间完全包含的线段权值总和减去选取区间的长度。

套路地枚举左端点 $L$，把区间长度的贡献算进去（注意是离散化前的下标差），然后把 $l_i\geq L$ 的每个线段 $i$ 对应的贡献算入（当选取区间右端点 $R\geq r_i$，则得分加上 $c_i$）。这些操作直接线段树维护区间加，对每个 $L$ 求答案查一次全局 $\max$ 即可，具体可以看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fr first
#define sc second
const int N=1e6+5;
int n,l[N],r[N],v[N],a[N],len,ans,id1,id2;
vector<int>e[N];
struct sgm{
    #define lc(x) (x<<1)
    #define rc(x) (x<<1|1)
    #define mid(l,r) ((l+r)>>1)
    int mx[N<<2],id[N<<2],tag[N<<2];
    void build(int x,int l,int r){
        if (l==r){
            id[x]=l;
            return;
        }
        build(lc(x),l,mid(l,r));
        build(rc(x),mid(l,r)+1,r);
        id[x]=id[lc(x)];
    }
    void add(int x,int l,int r,int ql,int qr,int k){
        if (qr>len)
            return;
        if (ql<=l&&r<=qr){
            mx[x]+=k,tag[x]+=k;
            return;
        }
        tag[lc(x)]+=tag[x],tag[rc(x)]+=tag[x];
        mx[lc(x)]+=tag[x],mx[rc(x)]+=tag[x],tag[x]=0;
        if (ql<=mid(l,r)) add(lc(x),l,mid(l,r),ql,qr,k);
        if (qr>mid(l,r)) add(rc(x),mid(l,r)+1,r,ql,qr,k);
        if (mx[lc(x)]>=mx[rc(x)]) mx[x]=mx[lc(x)],id[x]=id[lc(x)];
        else mx[x]=mx[rc(x)],id[x]=id[rc(x)];
    }
}book;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>l[i]>>r[i]>>v[i];
        a[i*2-1]=l[i],a[i*2]=r[i];
    }
    sort(a+1,a+n*2+1);
    len=unique(a+1,a+n*2+1)-a-1;
    book.build(1,1,len);
    for (int i=2;i<=len;i++)
        book.add(1,1,len,i,i,a[1]-a[i]);
    for (int i=1;i<=n;i++){
        l[i]=lower_bound(a+1,a+len+1,l[i])-a;
        r[i]=lower_bound(a+1,a+len+1,r[i])-a;
        if (l[i]>r[i]) swap(l[i],r[i]);
        book.add(1,1,len,r[i],len,v[i]);
        e[l[i]].push_back(i);
    }
    a[len+1]=2e9;
    id1=len+1,id2=len+1;
    for (int i=1;i<=len;i++){
        if (book.mx[1]>ans){
            ans=book.mx[1];
            id1=i,id2=book.id[1];
        }
        book.add(1,1,len,i,i,-1e18);
        for (auto j:e[i])
            book.add(1,1,len,r[j],len,-v[j]);
        book.add(1,1,len,i+1,len,a[i+1]-a[i]);
    }
    id1=a[id1],id2=a[id2];
    cout<<ans<<'\n'<<id1<<' '<<id1<<' '<<id2<<' '<<id2<<'\n';
    return 0;
}
```

祝大家新年快乐！

---

## 作者：ifffer_2137 (赞：0)

扫描线入门题。
### 题意
二维平面上若干带权点，选出一个左下角和右上角都在 $y=x$ 上的矩形（可以为空），使得矩形内点权和减去矩形边长最大，构造方案。
### 分析
首先应当离散化，因为选的坐标值在点集中存在显然不劣。

然后上个扫描线，扫左下角 $L$，动态维护每个右上角 $R$ 的权值。你考虑一个点会产生贡献，当且仅当 $L\le x,y \le R$，所以我们把这个点的权值在 $[\max(x,y),+\infty]$ 内加上，然后当左下角扫到 $\min(x,y)$ 时把这个点删掉，容易发现这样我们的修改次数在扫描过程中是均摊 $O(1)$，直接用 sgt 维护区间加区间 $\max$ 和 $\text{maxpos}$，复杂度 $O(n\log n)$。

然后你发现矩形边长的代价可以拆开来统计，提前在线段树里加好每个点作为右上角的代价，查询时额外加上左下角的贡献即可。

注意矩形边长可以为 $0$，初值记得赋好。
### 代码
封装了 sgt 还是比较好看的 qwq。
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
mt19937 rnd(time(NULL));
const int maxn=1e6+5;
int n;
int ans;
int X,Y;
struct node{int x,y,c;}a[maxn];
int t[maxn],tt;
vector<pii> Ax[maxn];
class Segment_Tree{
private:
	#define ls (o<<1)
	#define rs (o<<1|1)
	int mx[maxn<<2],pos[maxn<<2],tag[maxn<<2];
	void pushup(int o){
		mx[o]=max(mx[ls],mx[rs]);
		if(mx[o]==mx[ls]) pos[o]=pos[ls];
		else pos[o]=pos[rs];
	}
	void pushtag(int o,int k){tag[o]+=k,mx[o]+=k;}
	void pushdown(int o){
		if(!tag[o]) return;
		pushtag(ls,tag[o]);
		pushtag(rs,tag[o]);
		tag[o]=0;
	}
public:
	void build(int o,int l,int r){
		if(l==r) return mx[o]=-t[l],pos[o]=l,void();
		int m=(l+r)>>1;
		build(ls,l,m),build(rs,m+1,r);
		pushup(o);
	}
	void update(int o,int l,int r,int x,int y,int k){
		if(x<=l&&r<=y) return pushtag(o,k),void();
		int m=(l+r)>>1;pushdown(o);
		if(x<=m) update(ls,l,m,x,y,k);
		if(y>m) update(rs,m+1,r,x,y,k);
		pushup(o); 
	}
	pii query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return mkpr(mx[o],pos[o]);
		int m=(l+r)>>1;pushdown(o);
		pii L={-inf,0},R={-inf,0};
		if(x<=m) L=query(ls,l,m,x,y);
		if(y>m) R=query(rs,m+1,r,x,y);
		return max(L,R);
	}
}sgt;
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		t[++tt]=a[i].x=read();
		t[++tt]=a[i].y=read();
		a[i].c=read();
	}
	sort(t+1,t+tt+1),tt=unique(t+1,t+tt+1)-t-1;
	sgt.build(1,1,tt);
	for(int i=1;i<=n;i++){
		a[i].x=lower_bound(t+1,t+tt+1,a[i].x)-t;
		a[i].y=lower_bound(t+1,t+tt+1,a[i].y)-t;
		int mn=min(a[i].x,a[i].y),mx=max(a[i].x,a[i].y);
		sgt.update(1,1,tt,mx,tt,a[i].c);Ax[mn].eb(mkpr(mx,a[i].c));
	}
	ans=0,X=Y=t[tt]+1;
	for(int i=1;i<=tt;i++){
		pii res=sgt.query(1,1,tt,i,tt);res.fir+=t[i];
		if(res.fir>ans) ans=res.fir,X=t[i],Y=t[res.sec];
		for(pii j:Ax[i]) sgt.update(1,1,tt,j.fir,tt,-j.sec);
	}
	cout<<ans<<'\n';
	cout<<X<<' '<<X<<' '<<Y<<' '<<Y<<'\n';
	return 0;
}
```

---

## 作者：SmileMask (赞：0)

# 题解
首先，我们考虑直接做的话很麻烦，所以我们把所有在 $x=y$ 这条直线以下的所有点全部对称到上面，这样原本的正方形就变成了等腰直角三角形，更加方便我们去维护。

然后，我们将所有点的坐标离散化。

建出线段树，维护每个纵坐标的权值，线段树当前的值为负的纵坐标。

考虑怎么去统计答案，我们考虑从上到下枚举一条直线，令当前直线为 $i$。

我们把将在当前直线之上的点全部加入线段树。

我们查询纵坐标在 $[i,n]$ 中的权值最大值，然后在加上当前直线 $i$ 的横坐标，这就相当于求出来权值和-边长了。

```
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define x first
#define y second
using namespace std;
inline int rd(){
	int num=0,sign=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') sign=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') num=(num<<3)+(num<<1)+(ch^48),ch=getchar();
	return num*sign;
}
const int N=5e5+10;
struct Point{
	int x,y,c;
}p[N];
int n;
vector <int> num;
namespace SGT{
	struct node{
		int mx,idx,tag;
		friend node operator +(node x,node y){
			node z;
			if(x.mx<y.mx) z={y.mx,y.idx,0};
			else z={x.mx,x.idx,0};
			return z;
		}
	}t[N<<3];
	#define mid (l+r>>1)
	void build(int l,int r,int id){
		if(l==r){
			t[id]={-num[l],l,0};
			return ;
		}
		build(l,mid,id<<1),build(mid+1,r,id<<1|1);
		t[id]=t[id<<1]+t[id<<1|1];
	}
	void upd(int id,int v){
		t[id].mx+=v,t[id].tag+=v;
	}
	void pushdown(int id){
		if(!t[id].tag) return ;
		upd(id<<1,t[id].tag),upd(id<<1|1,t[id].tag);
		t[id].tag=0;
	}
	void add(int l,int r,int id,int L,int R,int v){
		if(L<=l&&r<=R) return upd(id,v),void();
		pushdown(id);
		if(L<=mid) add(l,mid,id<<1,L,R,v);
		if(mid<R) add(mid+1,r,id<<1|1,L,R,v);
		t[id]=t[id<<1]+t[id<<1|1];
	}	
	node query(int l,int r,int id,int L,int R){
		if(L<=l&&r<=R) return t[id];
		pushdown(id); 
		if(R<=mid) return query(l,mid,id<<1,L,R);
		if(mid<L) return query(mid+1,r,id<<1|1,L,R);
		return query(l,mid,id<<1,L,R)+query(mid+1,r,id<<1|1,L,R);
	}
}using namespace SGT;
vector <PII> v[N*2];
signed main(){
	n=rd();
	for(int i=1;i<=n;i++){
		int x=rd(),y=rd(),z=rd();
		p[i]={min(x,y),max(x,y),z};
		num.push_back(x),num.push_back(y);
	}
	sort(num.begin(),num.end());
	num.erase(unique(num.begin(),num.end()),num.end());
	for(int i=1;i<=n;i++){
		int l=lower_bound(num.begin(),num.end(),p[i].x)-num.begin();
		int r=lower_bound(num.begin(),num.end(),p[i].y)-num.begin();
		v[l].push_back({r,p[i].c});
	}
	n=num.size()-1;
	build(0,n,1);//0-R
	int ans=0,l=2e9,r=2e9;
	for(int i=n;~i;i--){
		for(int j=0;j<v[i].size();j++){
			add(0,n,1,v[i][j].x,n,v[i][j].y);
		}
		node x=query(0,n,1,i,n);
		x.mx+=num[i];
		if(x.mx>ans)
			ans=x.mx,l=num[i],r=num[x.idx];
	}
	cout<<ans<<endl<<l<<' '<<l<<' '<<r<<' '<<r<<endl;
	return 0;
}
```

---

## 作者：JWRuixi (赞：0)

### 题意

给定平面上的 $n$ 个点，每个点坐标 $(x_i, y_i)$，价值 $c_i$。定义一个左下/右上两个顶点在直线 $y = x$ 上的正方形的价值为：包含在正方形内的点的价值之和，减去正方形边长。求价值最大的正方形的价值和一个可能的正方形的两个顶点坐标。

$n \le 5 \times 10^5, x_i,y_i \le 10^9, |c_i| \le 10^6$，提交地址：<https://codeforces.com/problemset/problem/1221/F>。

### 分析

考虑一个正方形 $((L, L), (R, R))$，它包含点 $(x, y)$ 的充要条件是 $L \le x, y \le R$。于是我们可以将点/正方形转换成区间，于是将问题变成了求 $\max\limits_{L \le R}(\sum\limits_{L \le x_i, y_i \le R}c_i - (R - L))$。考虑扫描线，从左到右扫右端点，用线段树维护在左端点加入一个点的价值，同时维护全局最大值及其位置即可。

时间复杂度 $\mathcal O(n\log n)$。

### Code

提交记录：<https://codeforces.com/contest/1221/submission/229990295>。



---

## 作者：Felix72 (赞：0)

考虑维护差分数组。因为带修，所以枚举左下找右上，差分数组变成线段树。这里用了一个技巧，对于在直线下面的点，将它翻转到上面。

这样就解决了点的问题。线段数维护前缀最大值即可。而对于正方形边长，我们在对应的坐标上减去差值，一样可以塞到线段树里。

枚举时，按照坐标从小到大。计算完后删去之前的所有点和坐标的差分值，就不会影响后续求前缀了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010;
long long n, cnt, trans[N * 2], chk[N * 2];
long long ans, ps, pt;
struct node {long long ox, oy, x, y, val;} s[N];
struct lsh {long long num, id, opt;} org[N * 2];
inline bool cmp(lsh u, lsh v) {return u.num < v.num;}
inline bool cmp1(node u, node v) {return u.ox < v.ox;}
inline bool cmp2(node u, node v) {return u.oy < v.oy;}
int rt, idx;
struct SGT
{
	int ls, rs; long long sum, maxn, rec;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define sum(x) tree[x].sum
	#define maxn(x) tree[x].maxn
	#define rec(x) tree[x].rec
}tree[N * 4];
inline void pushup(int now)
{
	sum(now) = maxn(now) = 0;
	if(ls(now))
	{
		if(rs(now))
		{
			sum(now) = sum(ls(now)) + sum(rs(now));
			if(maxn(ls(now)) >= sum(ls(now)) + maxn(rs(now)))
				rec(now) = rec(ls(now)), maxn(now) = maxn(ls(now));
			else rec(now) = rec(rs(now)), maxn(now) = sum(ls(now)) + maxn(rs(now));
		}
		else
		{
			sum(now) = sum(ls(now));
			rec(now) = rec(ls(now));
			maxn(now) = maxn(ls(now));
		}
	}
}
inline void build(int &now, int l, int r)
{
	if(!now) now = ++idx;
	if(l == r) {rec(now) = l; chk[l] = now; return ;}
	int mid = l + r >> 1;
	if(l <= mid) build(ls(now), l, mid);
	if(mid < r) build(rs(now), mid + 1, r);
}
inline void insert(int now, int l, int r, int pos, long long num)
{
	if(l == r) {sum(now) += num, maxn(now) += num; return ;}
	int mid = l + r >> 1;
	if(pos <= mid) insert(ls(now), l, mid, pos, num);
	else insert(rs(now), mid + 1, r, pos, num);
	pushup(now);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> s[i].ox >> s[i].oy >> s[i].val;
	for(int i = 1; i <= n; ++i)
		if(s[i].ox > s[i].oy)
			swap(s[i].ox, s[i].oy);
	for(int i = 1; i <= n; ++i)
	{
		org[i * 2 - 1].num = s[i].ox, org[i * 2 - 1].id = i, org[i * 2 - 1].opt = 1;
		org[i * 2].num = s[i].oy, org[i * 2].id = i, org[i * 2].opt = 2;
	}
	sort(org + 1, org + 2 * n + 1, cmp);
	for(int i = 1; i <= 2 * n; ++i)
	{
		assert(i == 1 || org[i].num >= org[i - 1].num);
		if(i == 1 || org[i].num != org[i - 1].num)
			trans[++cnt] = org[i].num;
		if(org[i].opt == 1) s[org[i].id].x = cnt;
		if(org[i].opt == 2) s[org[i].id].y = cnt;
	}
	build(rt, 1, cnt);
	for(int i = 1; i <= n; ++i) insert(rt, 1, cnt, s[i].y, s[i].val);
	sort(s + 1, s + n + 1, cmp1);
	for(int i = 2; i <= cnt; ++i)
		insert(rt, 1, cnt, i, -trans[i] + trans[i - 1]);
	ans = 0, ps = 2e9, pt = 2e9;
	int bj = 1, tot = 2;
	for(int i = 1; i <= n; ++i)
	{
		if(i != 1 && s[i].ox == s[i - 1].ox) continue;
		while(tot <= cnt && tot <= s[i].x) insert(rt, 1, cnt, tot, trans[tot] - trans[tot - 1]), ++tot;
		long long cur = maxn(rt);
		if(cur > ans)
		{
			ans = cur;
			ps = s[i].ox, pt = trans[rec(rt)];
		}
		while(bj <= n && s[bj].ox == s[i].ox) insert(rt, 1, cnt, s[bj].y, -s[bj].val), ++bj;
	}
	cout << ans << '\n' << ps << " " << ps << " " << pt << " " << pt << '\n';
	return 0;
}
```

---

