# Valera and Queries

## 题目描述

Valera loves segments. He has recently come up with one interesting problem.

The $ Ox $ axis of coordinates has $ n $ segments, the $ i $ -th segment starts in position $ l_{i} $ and ends in position $ r_{i} $ (we will mark it as $ [l_{i},r_{i}] $ ). Your task is to process $ m $ queries, each consists of number $ cnt_{i} $ and a set of $ cnt_{i} $ coordinates of points located on the $ Ox $ axis. The answer to the query is the number of segments, such that each of them contains at least one point from the query. Segment $ [l,r] $ contains point $ q $ , if $ l<=q<=r $ .

Valera found the solution of this problem too difficult. So he asked you to help him. Help Valera.

## 样例 #1

### 输入

```
3 3
1 3
4 5
6 7
3 1 4 7
2 4 5
1 8
```

### 输出

```
3
1
0
```

# 题解

## 作者：mrclr (赞：7)


这题刚开始以为是一个简单题，后来越想越不对劲，然后就卡住了。

瞅了一眼网上的题解（真的只瞅了一眼），几个大字令人为之一振：正难则反！

没错，把点看成区间，比如2, 5, 6, 9就是[1, 1], [3, 4], [7, 8], [10, INF]。然后只要看给定的哪些线段完全包含在这些区间里了。

预处理出这些区间后，离线下来，按左端点从大到小，右端点从从小到大排序。遇到一个线段就加进树状数组里，遇到一个区间就查一下R的前缀和。因为我们是左端点从大到小扫的，所以一定保证加进树状数组的线段的左端点大于等于当前查询区间的左端点。所以只用考虑右端点即可。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define In inline
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 3e5 + 5;
const int maxN = 1e6 + 5;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n, m, Max = 0;
struct Seg
{
  int L, R, id;
  In bool operator < (const Seg& oth)const
  {
    if(L ^ oth.L) return L > oth.L;
    if(R ^ oth.R) return R < oth.R;
    return id < oth.id;
  }
}t[maxn << 2];

int cnt = 0, tp[maxn], ans[maxn];

int c[maxN];
In int lowbit(int x) {return x & -x;}
In void add(int pos)
{
  for(; pos < maxN; pos += lowbit(pos)) ++c[pos];
}
In int query(int pos)
{
  int ret = 0;
  for(; pos; pos -= lowbit(pos)) ret += c[pos];
  return ret;
}

int main()
{
  n = read(); m = read(); cnt = n;
  for(int i = 1; i <= n; ++i) t[i].L = read(), t[i].R = read(), t[i].id = 0;
  for(int i = 1; i <= m; ++i)
    {
      int tot = read();
      for(int j = 1; j <= tot; ++j) tp[j] = read();
      for(int j = 1; j <= tot; ++j)
	if(tp[j] > 1 && tp[j - 1] < tp[j] - 1) t[++cnt] = (Seg){tp[j - 1] + 1, tp[j] - 1, i};
      t[++cnt] = (Seg){tp[tot] + 1, maxN - 5, i};
    }
  sort(t + 1, t + cnt + 1);
  for(int i = 1; i <= cnt; ++i)
    if(t[i].id) ans[t[i].id] += query(t[i].R);
    else add(t[i].R);
  for(int i = 1; i <= m; ++i) write(n - ans[i]), enter;
  return 0;
}
```

---

## 作者：hzjnsy (赞：3)

lxl 上课讲的例题，来补个题解。2200 的 DS 都不会了，加训 /fn。

**[CF](https://codeforces.com/problemset/problem/369/E) [洛谷](https://www.luogu.com.cn/problem/CF369E)**

> - 给出 $n$ 条线段 $[l_i,r_i]$ 和 $m$ 个询问，每个询问给出 $cnt_i$ 个点 $p_1,p_2,\dots,p_{cnt_i}$（按从小到大的顺序给出），你要回答有多少条线段覆盖了至少一个点。
>
> - $n,m,\sum_{i=1}^mcnt_i\le 3\times 10^5$，所有输入数据不超过 $10^6$。

考虑容斥成线段总数减去一个点都没有覆盖的线段条数。对于一个询问，$p_1\sim  p_{cnt_i}$ 将数轴划分成了若干段，而我们要求的就是每一段内部的线段个数。

形式化的，对于 $j\,(1\le j<cnt_i)$，我们要求满足 $p_j < l_k$ 且 $r_k < p_{j+1} $ 的 $k$ 的个数。为了方便转化成闭区间的形式：$p_j+1\le l_k$ 且 $r_k\le p_{j+1}-1$。类似地，还有边角的两个区间。

然后就变成了二维偏序模板，把一维排序，另一维树状数组算贡献即可。这题貌似卡快排，要用 `stable_sort`。

设值域为 $V$，时间复杂度为 $\mathcal{O}\left(\left(\sum_{i=1}^mcnt_i+n\right)\log|V| \right)$，空间复杂度为 $\mathcal{O}\left(n+m+\sum_{i=1}^m cnt_i+|V|\right)$。

```cpp
#include <bits/stdc++.h>
using namespace std; const int N = 1e6 + 5;
int n, m, cnt, tmp[N], ans[N];
struct node { int x, y, id; } p[N];
struct BinaryIndexedTree {
    int sum[N]; int lb(int x) { return x & (-x); }
    void init() { memset(sum, 0, sizeof sum); }
    void modify(int k, int v) { while (k < N) sum[k] += v, k += lb(k); }
    int query(int k) 
        { int ret = 0; while (k) ret += sum[k], k -= lb(k); return ret; }
} bit; 
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
void pushq(int x, int y, int id) {
    if (x > y) return; p[++cnt] = {x, y, id};
}
signed main() {
    read(n), read(m); bit.init();
    for (int i = 1, x, y; i <= n; ++i) 
        { read(x), read(y); p[++cnt] = {x, y, 0}; }
    for (int i = 1, x, y; i <= m; ++i) {
        ans[i] = n; read(x); for (int j = 1; j <= x; ++j) read(tmp[j]);
        for (int j = 1; j < x; ++j) pushq(tmp[j] + 1, tmp[j + 1] - 1, i);
        pushq(1, tmp[1] - 1, i); pushq(tmp[x] + 1, 1e6, i);
    }
    stable_sort(p + 1, p + 1 + cnt, [&](node u, node v)
        { return u.x != v.x ? u.x > v.x : !u.id; });
    for (int i = 1; i <= cnt; ++i) 
        if (p[i].id) ans[p[i].id] -= bit.query(p[i].y);
        else bit.modify(p[i].y, 1);
    for (int i = 1; i <= m; ++i) print(ans[i]);
    return 0;
}
```




---

## 作者：Altwilio (赞：1)

### $0.$ 前言
正难则反，回去再想想再来看题解。

### $1.$ 题意
给定 $n$ 条线段以及 $m$ 次询问，每次询问给定 $cnt$ 个点，问有多少条线段至少覆盖一个点。$n,m,\sum cnt \le 3 \times 10^5$。

### $2.$ 思路
当正着想怎么都不对时，考虑正难则反。

因为至少覆盖一个不确定可能覆盖几个，考虑求有多少条线段完全不覆盖点。

将题目中的问题转化，用给定询问的点分割数轴，假设红色的点为一次询问，如图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/tkl8t2s0.png)

当一条线段的两个端点分别在两个蓝色的区间时，这条线段就至少覆盖一个点。所以不覆盖点的区间一定包含于蓝色区间内。（与品酒大会某一步相似）

问题转化为求有多少条给定的线段完全包含与求出的区间中，这样的线段一定不包含任意一个点。


### $3.$ 代码

代码就不放了，离线询问，在树状数组上查查就行了。

---

## 作者：nynkqh_yzp (赞：0)

直接算会算重，因此考虑正难则反。

没有覆盖 $p_i$ 的区间，即被区间 $[p_i+1,p_{i+1}-1]$ 包含的区间，一个区间在一次查询中只会被一个区间 $[p_i+1,p_{i+1}-1]$ 包含，不会算重。

可以直接离线下来使用二维偏序，扫描线加树状数组解决。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,ans[300001],b[1000001];
struct ac{
	int l,r,v;
}a[900001];
bool cmp(ac x,ac y){
	if(x.r==y.r)
		return x.v<y.v;
	return x.r<y.r;
}
void xg(int x){
	for(int i=x;i<=(1e6);i+=(i&-i))
		b[i]++;
}
int ch(int x){
	int an=0;
	for(int i=x;i>0;i-=(i&-i))
		an+=b[i];
	return an;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].l,&a[i].r);
	cnt=n;
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d",&x);
		y=0;
		while(x--){
			scanf("%d",&z);
			a[++cnt].l=y+1;
			a[cnt].r=z-1;
			a[cnt].v=i;
			y=z;
		}
		a[++cnt].l=y+1;
		a[cnt].r=1e6;
		a[cnt].v=i;
	}
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
		if(a[i].v==0)
			xg(a[i].l);
		else
			ans[a[i].v]+=ch(1e6)-ch(a[i].l-1);
	for(int i=1;i<=m;i++)
		printf("%d\n",n-ans[i]);
	return 0;
}
```

---

## 作者：longlinyu7 (赞：0)

# 思路

[369E - Valera and Queries](https://codeforces.com/problemset/problem/369/E)。

数据结构题，看到只有查询没有修改就想到了离线做法，想到需要排序，然后就以每个**点**进行考虑，算他被几个线段覆盖了，对当前询问做了多少贡献，然后打了个树状数组板子，结果错了。

仔细想想后明白了，一个线段可能覆盖好几个点，那么上述做法这几个点算的贡献就重了，需要更换做法，但大体思路不变，仍需离线。那么以**线段**为考虑角度，**正难则反**，如果不好判断线段覆盖了几个点，那我就看哪个线段不做贡献，即哪个线段一个点也不覆盖。

怎么判断呢。考虑一个线段不做贡献，他应该是位于两个相邻的点之间，把每两个相邻的点之间的地方看成一个区间。

问题转化为：给定若干个线段，每次给若干个区间，判断有多少线段完全被某一个区间包含。

仍然考虑离线处理，需要排序。怎么排序？以谁为关键字来排序？看了看题解，有很多种套路，说一种。

1. 以左端点为关键字，从大到小排序。
2. 以右端点为关键字，从小到大排序。

为什么这样呢，左端点从大到小，那么已经扫描过的线段的左端点一定是大于等于当前区间的左端点，因此只考虑右端点的情况即可。每次遇到一个线段，将其右端点的贡献加一，然后遇到区间时，直接加上当前区间右端点的前缀和，即可判断有多少线段在这个区间之内。

> 总结：
>
> - 查询不带修，可以考虑离线做法。但离线后，怎么排序很重要，代表着如何处理这些贡献。
> - 正难则反，一个线段可能覆盖多个点，仅以点考虑会算重，以线段考虑正着来又不好弄，可以考虑有多少线段做不了贡献。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+10;
const int inf=1e6+10;
const int MOD=1e9+7;
int n,m;
int cnt,u,v,x;
int t[N];
int lowbit(int x){return x&(-x);}
int sum(int x){
    int ans=0;
    for(int i=x;i;i-=lowbit(i)){
        ans+=t[i];
    }
    return ans;
}
void add(int x,int y){
    for(int i=x;i<= 1000000 ;i+=lowbit(i)){
        t[i]+=y;
    }
}
struct node{
    int id,l,r;
    //! 左端点从大到小， 右端点从小到大
    friend bool operator<(node a,node b){
        if(a.l!=b.l)return a.l>b.l;     
        if(a.r!=b.r)return a.r<b.r;
        return a.id<b.id;
    }
}a[N];
int ans[N],b[N];
int ttt;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>u>>v;
        a[++ttt]=(node){0,u,v};
    }

    for(int i=1;i<=m;i++){
        cin>>cnt;
        for(int j=1;j<=cnt;j++){
            cin>>b[j];
        }   
        sort(b+1,b+1+cnt);
        for(int j=1;j<=cnt;j++){
            if(b[j-1]+1 > b[j]-1 )continue;
            a[++ttt]=(node){i,b[j-1]+1,b[j]-1};
        }
        a[++ttt]=(node){i,b[cnt]+1,inf};
    }
    sort(a+1,a+1+ttt);
    //! 需要算右端点
    // 算有多少区间被包含了。

    for(int i=1;i<=ttt;i++){  
        if(a[i].id){
            ans[a[i].id] += sum(a[i].r);
        }    
        else add(a[i].r,1);
    }
    for(int i=1;i<=m;i++){
        cout<<n-ans[i]<<"\n";
    }

    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

只需要把所有线段分成：

- 经过 $p_1$；
- 不经过 $p_1$，但经过 $p_2$；
- 不经过 $p_2$，但经过 $p_3$；
- ……
- 不经过 $p_{cnt-1}$，但经过 $p_{cnt}$。

这样发现左端点的范围是 $(p_i,p_{i+1}]$，右端点范围是 $[p_{i+1},+\infty)$。

离线后使用扫描线+二维数点即可。

你也可以使用主席树做到在线。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10,MAXM=1e6+10;
int n,m,t=1000000,ans[MAXN];
vector<int> upd[MAXM];
vector<pair<int,pair<int,int>>> qr[MAXM];
int tr[MAXM];
void update(int pos,int v) {
	pos=t-pos+1;
	while(pos<=t) tr[pos]+=v,pos+=pos&-pos;
	return ;	
}
int query(int pos) {
	pos=t-pos+1;
	int ans=0;
	while(pos) ans+=tr[pos],pos-=pos&-pos;
	return ans;	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) {int l,r;cin>>l>>r,upd[l].push_back(r);}
	ffor(i,1,m) {
		int cnt; cin>>cnt;
		vector<int> pos;
		ffor(j,1,cnt) {int id;cin>>id,pos.push_back(id);}
		int lst=0;
		ffor(j,0,cnt-1) qr[lst].push_back({-1,{i,pos[j]}}),qr[pos[j]].push_back({1,{i,pos[j]}}),lst=pos[j];
	}
	ffor(i,1,t) {
		for(auto id:upd[i]) update(id,1);
		for(auto pr:qr[i]) ans[pr.second.first]+=pr.first*query(pr.second.second);
	}
	ffor(i,1,m) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

简单题，评紫可能偏高了，CF 上才 \*2200 呢。
### 题意
有 $n$ 条线段，$m$ 个询问，
每次询问给出 $cnt_i$ 个点，输出有多少线段至少覆盖这 $cnt_i$ 个点中的一个。
### 分析
发现直接计数并不好做，绕来绕去总会有重或者有漏，这启发我们考虑容斥，用 $n$ 减去没有覆盖任何点的线段数。

没有覆盖任何点的线段，就是夹在两个相邻点之间的线段，相当于我们给定了若干个区间，求完全包含在区间内的线段数，即对于一个区间 $[x,y]$，我们要数出满足 $x\leq l_i$ 并且 $r_i\leq y$ 的 $i$ 有几个。

这个问题就十分套路了，离线下来，把所有线段和询问区间按右端点排序，开一颗权值树状数组维护当前遍历到的所有左端点，扫描一遍即可。这里值域只有 $10^6$，还省了一个离散化。

最后时间复杂度 $\mathcal O(n\log_2n)$，随便过了。

代码并不是很难写，这里重构以后轻微压行了。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=3e5+5;
const int maxm=1e6+5;
const int N=1e6;
int n,m,cnt;
int ans[maxn];
vector<int> x[maxm];
struct node{int id,l;};
vector<node> q[maxm];
struct Fenwick_Tree{
	int c[maxm];
	int lowbit(int x){ return x&(-x); }
	void update(int x,int k){ while(x<=N){ c[x]+=k; x+=lowbit(x);} }
	int query(int x){int res=0; while(x){ res+=c[x]; x-=lowbit(x);} return res; }
}tr;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		int l=read(),r=read();
		x[r].push_back(l);
	}
	for(int i=1;i<=m;i++){
		int t=read(),x=0;
		for(int j=1;j<=t;j++){
			int y=read();
			if(x+1<y) q[y-1].push_back((node){i,x+1});
			x=y;
		}
		if(x+1<=N) q[N].push_back((node){i,x+1});
		ans[i]=n;
	}
	for(int i=1;i<=N;i++){
		if(x[i].size()) for(int l:x[i]) tr.update(l,1);
		if(q[i].size()) for(node k:q[i]) ans[k.id]-=tr.query(i)-tr.query(k.l-1);
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

## 思路

容斥一下，考虑每次查询转换为总数减去两两点之间的线段覆盖的线段的数量。

问题转化为计算某条线段覆盖了多少条线段。

先按 $l$ 排递减序，然后每次查询就查询 $l\sim r$ 之间的总和，添加线段则在 $r$ 位置加一。

容易发现后扫到的不会被先扫到的覆盖，后扫到的覆盖的所有都要求 $r'<r$，故上述解法是正确的。

是离线的。

复杂度 $O((n+q)\log n)$，会有点常数，随便搞个快读就能过。

## 代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
struct node{
	int num,l,r,tp;
}q[1000005];
int top=0;
bool cmp(node x,node y){
	if(x.l!=y.l) return x.l>y.l;
	return x.r<y.r;
}
struct sgt{
	int f[4000005];
	void change(int i,int l,int r,int pos){
		if(l==r) return f[i]++,void();
		if(pos<=mid) change(i*2,l,mid,pos);
		else change(i*2+1,mid+1,r,pos);
		f[i]=f[i*2]+f[i*2+1];
	}
	int qry(int i,int l,int r,int ql,int qr){
		return ((ql<=l&&r<=qr)?(f[i]):((ql>r||qr<l)?0:(qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr))));
	}
}tree;
int b[1000005],ans[1000005];
vector<int> vc[300005];
int read(){
	char c; int ans=0; int z=1;
	while(!isdigit(c=getchar()))z-=2*(c=='-');
	do{ans=(ans*10+c-'0');}while(isdigit(c=getchar()));
	return ans*z;
}
void print(int x){
	if(x<0) putchar('-');
	if(llabs(x)>=10) print(llabs(x)/10);
	putchar((llabs(x)%10)+'0');
}
signed main(){
	int n=read(),m=read();
	int x[n+1],y[n+1];
	for(int i=1;i<=n;i++) x[i]=read(),y[i]=read(),q[++top].l=x[i],q[top].r=y[i],q[top].tp=1;
	for(int i=1;i<=m;i++){
		int cnt=read();
		int lst=0;
		for(int j=1;j<=cnt;j++){
			int tt=read();
			if(tt!=lst+1){
				vc[i].push_back(++top);
				q[top].tp=2,q[top].num=top,q[top].l=lst+1,q[top].r=tt-1;
			}
			lst=tt;
		} 
		if(1000001!=lst+1){
			vc[i].push_back(++top);
			q[top].tp=2,q[top].num=top,q[top].l=lst+1,q[top].r=1000000;
		}
	}
	sort(q+1,q+top+1,cmp);
	for(int i=1;i<=top;i++){
		int fst=i;
		if(q[i].tp==1) tree.change(1,1,1000000,q[i].r);
		while(q[i].l==q[i+1].l&&q[i].r==q[i+1].r){
			i++;
			if(q[i].tp==1) tree.change(1,1,1000000,q[i].r);
		}
		for(int j=fst;j<=i;j++) if(q[j].tp==2) ans[q[j].num]=tree.qry(1,1,1000000,q[i].l,q[i].r);
	}
	for(int i=1;i<=m;i++){
		int sum=n;
		for(auto v:vc[i]){
			sum-=ans[v];
		}
		cout<<sum<<endl;
	}
	return 0;
}
```

---

