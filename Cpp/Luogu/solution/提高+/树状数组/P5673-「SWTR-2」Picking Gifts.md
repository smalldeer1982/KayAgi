# 「SWTR-2」Picking Gifts

## 题目背景

$\mathrm{Sunny}$ 有个 $npy$ 叫做小 $\mathrm{b}$。

小 $\mathrm{b}$ 的生日就要到了，$\mathrm{Sunny}$ 想给她买一些礼物。

## 题目描述

商店里摆着琳琅满目的商品，每个商品都有：

- 编号，**从左到右**依次为 $1,2,\dots n$。

- 种类，分别为 $p_1,p_2,\dots p_n$。

- 价值，分别为 $v_1,v_2,\dots v_n$。

$\mathrm{Sunny}$ 想从中挑选一个区间，将这个区间里的所有礼物买下来送给小 $\mathrm{b}$。

小 $\mathrm{b}$ 会**从右往左**依次查看 $\mathrm{Sunny}$ 送给他的礼物，如果她看到同一种类的礼物出现了 $k$ 次，那么她就不会再去查看这种礼物（包括第 $k$ 个），当然，这些礼物也就失去了原本的价值。

现在，$\mathrm{Sunny}$ 给你了 $m$ 个区间，想让你求出在小 $\mathrm{b}$ 眼中，这个区间的价值。

具体的价值计算见样例。

## 说明/提示

---

### 样例说明

$[1,1]:7$。

$[1,2]:3+7=10$。

$[1,3]:8+3=11$，因为编号为 $1$ 的礼物种类为 $1$，这是种类 $1$ 出现的第 $k(k=3)$ 次，所以她不会再看这种礼物（包括这个）。

$[1,4]:9+8+3=20$。

$[2,6]:5+6+9+8=28$。

$[3,6]:5+6+9+8=28$。

---

### 数据范围与约定

测试点 $1-4:n\leq 100,m\leq 100$。

测试点 $5-6:n\leq 5000,m\leq 5000$。

测试点 $7-10:n\leq 2\times 10^4,m\leq 10^4$。

测试点 $11-15:n\leq 2\times 10^5,m\leq 2\times 10^5$。

测试点 $16-20:n\leq 10^6,m\leq 5\times 10^5$。

对于测试点 $1,2,7,8,11,12,16,17$，有 $k=n$，其余测试点有 $2\leq k<n$。

对于所有测试点，有 $1\leq p_i\leq n,1\leq v_i\leq 2000,1\leq l \leq r \leq n$。

---

对于测试点 $1-10$，每个 $3$ 分。

对于测试点 $11-20$ 中 $k=n$ 的，每个 $4$ 分。

其余测试点每个 $9$ 分。

---

对于测试点 $1-6$，时间限制 $500ms$。

对于测试点 $7-15$，时间限制 $750ms$。

对于测试点 $16-20$，时间限制 $1.5s$。

对于所有测试点，空间限制 $128MB$。

---

当然了，SWTR-02 的出题人们是不可能有 girlfriends 的。

## 样例 #1

### 输入

```
6 11 3
1 1 1 2 1 3
7 3 8 9 6 5
1 1
1 2
1 3
1 4
1 5
1 6
2 6
3 6
4 6
5 6
6 6```

### 输出

```
7
10
11
20
23
28
28
28
20
11
5```

# 题解

## 作者：kind_aunt (赞：10)

# P5673 「SWTR-2」Picking Gifts 题解
~~声明：在写代码前未看题解。~~  
这是一道单点修改和区间查询的树状数组好题，跟 [P1972](https://www.luogu.com.cn/problem/P1972) 十分相似（Alex_Wei 已指出），所以我们先去看一下 那题。  
大意为：给定1个长度为 $n$ 序列 $a$，并给定 $q$ 个询问。对于每个询问给定 $l$ 和 $r$，求区间 $[l,r]$ 中有多少个不同的数。  
嗯，一眼就可以看出用树状数组做。但具体怎么做呢，我们来手打一个样例：
```
2 3 2 5 2 1
```
可以发现，对于每个 $r$ 为 $3$ 的区间,下标为 $1$ 的那个 $2$ 就显得有些多余了。$r$ 为 $5$ 时同理，前面的两个 $2$ 也就多余了。那么我们就可以将 $r$ 从小到大排序（$l$ 先后次序不管）。来照样例模拟一下试试（初始化全部为 $0$）。  
$i=1$：`1 0 0 0 0 0//2第一次出现。`  
$i=2$：`1 1 0 0 0 0//3第一次出现。`  
$i=3$：`0 1 1 0 0 0//2第二次出现，将前面一个2更改为0。`  
$i=4$：`0 1 1 1 0 0//5第一次出现。`  
$i=5$：`0 1 0 1 1 0//2第三次出现，将前面一个2更改为0。`  
$i=6$：`0 1 0 1 1 1//1第一次出现。`  
假设求区间 $[2,5]$，那么就在 $i=5$ 的时候求 $sum(5)-sum(2-1)$。  

## Code

```
#include<bits/stdc++.h>
#define int long long 
#define lowbit(x) (x&-x)
#define rank kkk
using namespace std;
const int N=1e6+5;
int n,q;
int a[N],v[N];
int tree[N];
int c[N];
int now[N];//now[i]存储数前一个i最后出现的位置
void update(int x,int k){
	while(x<=n){
		tree[x]+=k;
		x+=lowbit(x);
	}
}
int sum(int x){
	int ans=0;
	while(x){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
struct node{
	int l,r,id;
}qus[N];
int ans[N];
bool cmp(node a,node b){
	return a.r<b.r;
}
bool cmp2(node a,node b){
	return a.id<b.id;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		v[i]=a[i];
	}
	sort(v+1,v+n+1);
	int k=unique(v+1,v+n+1)-v-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(v+1,v+k+1,a[i])-v;
	cin>>q;
	for(int i=1;i<=q;i++)
		cin>>qus[i].l>>qus[i].r,qus[i].id=i;
	sort(qus+1,qus+q+1,cmp);
	int qe=1;
	for(int i=1;i<=q;i++){//枚举question
		for(;qe<=qus[i].r;qe++){//枚举
			if(now[a[qe]])
				update(now[a[qe]],-1)/*,c[now[a[qe]]]--*/;
			update(qe,1);
			now[a[qe]]=qe;
			/*c[qe]++;*/
		}
		ans[qus[i].id]=sum(qus[i].r)-sum(qus[i].l-1);
//		for(int i=1;i<=n;i++)
//			cout<<c[i]<<" ";
//		cout<<'\n';
	}
	for(int i=1;i<=q;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
```
回归正题，来看看两道题的差距：  
1. 从只保留 $1$ 个变为保留 $k$ 个（顺序还是从右往左）。
2. 增添了价值（也就是价值从 $1$ 变为 $v_i$）。

第二个还是很好处理的，重点是第一个。之前可以用 $now_i$ 来存储种类为 $i$ 的物品的之前的位置，然后再将 $now_i$ 更改为目前位置。那现在怎么处理呢，不妨我们用 `vector` 存种类为 $i$ 的物品的各个位置。

```
vector<int> now[N];//种类i的物品出现的各个位置
```
再开一个 $vis$ 数组存当前种类为 $i$ 的物品出现的次数，那 `update` 就变成了这样：
```
int num=now[a[e].p][vis[a[e].p]-k];//a[e].p就为题目中的p[i]
update(e,a[e].v);
update(num,-a[num].v);
```
## Code

```
#include<bits/stdc++.h>
#define int long long 
#define lowbit(x) (x&-x)
using namespace std;
const int N=1e6+5;
struct node{
	int p,v;
}a[N];
int pp[N];
struct node2{
	int l,r,id;
}qu[N];
bool cmp(node2 a,node2 b){
	return a.r<b.r;
}
int n,m,k,tree[N];
int ans[N];//答案
int vis[N]={0};//来记录当前种类i出现的次数
vector<int> now[N];//种类i的物品出现的各个位置
void update(int x,int k){
	while(x<=n){
		tree[x]+=k;
		x+=lowbit(x);
	}
}
int sum(int x){
	int ans=0;
	while(x){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].p;
		pp[i]=a[i].p;
	}
	for(int i=1;i<=n;i++)
		cin>>a[i].v;
	sort(pp+1,pp+n+1);
	int vs=unique(pp+1,pp+n+1)-pp-1;
	for(int i=1;i<=n;i++){
		a[i].p=lower_bound(pp+1,pp+vs+1,a[i].p)-pp;
		now[a[i].p].push_back(i);
	}
	//离散化（可有可无）
	for(int i=1;i<=m;i++){
		cin>>qu[i].l>>qu[i].r;
		qu[i].id=i;
	}
	sort(qu+1,qu+m+1,cmp);
	int e=1;
	for(int i=1;i<=m;i++){
		for(;e<=qu[i].r;e++){
			vis[a[e].p]++;
			if(vis[a[e].p]<k)
				update(e,a[e].v);
			else{
				int num=now[a[e].p][vis[a[e].p]-k];
				update(e,a[e].v);
				update(num,-a[num].v);
			}
		}
		ans[qu[i].id]=sum(qu[i].r)-sum(qu[i].l-1);
	}
	for(int i=1;i<=m;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
```
希望大家多点赞，这是蒟蒻的第一篇蓝题题解。

---

## 作者：Alex_Wei (赞：10)

$\color{#00cfff}T3.\ Picking\ Gifts$

[$\color{#00cfff}\text{题面}$](https://www.luogu.org/problem/P5673)

$\color{#00cfff}\text{官方题解}$

---

比赛中有人指出本题和 [$P1972$](https://www.luogu.org/problem/P1972) 有些相似

就当它是加强版吧，反正也就是个套路题（还是刷题刷太少了啊）

---

本题主要考察树状数组（数据结构）和离线回答询问

暴力分：$18\%-30\%$

---

$Sol\ 1:18\%-30\%$

$\Theta(n^2)$ 暴力，如果你运气好能拿到 $50\%$

部分代码（第 $9$ 个测试点跑了 $498ms$）：

```cpp
for(int i=1;i<=m;i++){
	int l=read(),r=read(),ans=0;
	memset(cnt,0,sizeof(cnt));
	for(int j=r;j>=l;j--){
		cnt[p[j]]++;
		if(cnt[p[j]]<k)ans+=v[j];
	}
	cout<<ans<<endl;
}
```

---

$Sol\ 2:28\%$

对于所有 $k=n$ 的测试点，前缀和暴力回答询问即可

特判一下所有 $p_i$ 都相等的情况

部分代码：

```cpp
for(int i=1;i<=n;i++)
	p[i]=read(),cnt[p[i]]++;
for(int i=1;i<=n;i++)
	v[i]=read(),sum[i]=sum[i-1]+v[i];
for(int i=1;i<=m;i++){
	int l=read(),r=read();
	if(l==1&&r==n&&cnt[p[1]]>=k)
		cout<<sum[n]-v[1]<<endl;
	else cout<<sum[r]-sum[l-1]<<endl;
}
```

---

$Sol\ 3:34\%-46\%$

结合 $Sol\ 1,2$ 可得到 $34\%-46\%$ 的高分

代码不贴了

---

$Sol\ 4:100\%$

前置知识：树状数组，如果您不会，请先移步 [$P3374$](https://www.luogu.org/problem/P3374/)

正解：将所有询问离线，用树状数组维护

记第 $i$ 次询问的答案为 $ans_i$

从左往右依次扫过每个礼物，假设现在扫到了第 $i$ 个礼物，它的种类为 $j$，它是第 $j$ 种礼物出现的第 $x$ 次

如果 $x\ge k$，那就意味着第 $j$ 种礼物中的第 $x-k+1$ 个**完全失去了它的价值**，记该礼物的编号为 $y$

因为我们是从左往右计算，所以如果询问的右端点 $\ge i$，那么小 $\mathrm{a}$ 在看到第 $y$ 个礼物之前肯定至少看了 $k-1$ 个第 $j$ 种礼物，就不会看第 $y$ 个礼物，我们就可以把它的价值当做 $0$，即 $v_y=0$

然后我们就可以计算出所有**右端点在 $i$ 上的询问**，假设该询问的左端点为 $l$，编号为 $c$，则 $ans_c=\sum_{d=l}^{i}v[d]$

这就将题目转化为了一个 **单点修改，区间查询** 的题目，用树状数组维护即可（线段树常数过大）

时间复杂度 $\Theta(n\log n)$

欢迎爆踩标算！

代码（最慢的一个点跑了将近 $1s$）：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0;char s=getchar();
	while(!isdigit(s))s=getchar();
	while(isdigit(s))x=(x<<1)+(x<<3)+(s^48),s=getchar();
	return x;
}
inline void print(int x)
{
	if(x<10)putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
const int N=1e6+5;
int n,m,k,p[N],v[N],l[N],ans[N];
vector <int> pos[N],q[N];
//pos[i] 存储第 i 种礼物的编号，q[i] 存储右端点在 i 上的询问编号
struct BIT//树状数组
{
	int c[N];
	int lowbit(int x){return x&(-x);}//树状数组基本操作
	void add(int x,int y)//在第 x 位上加上 y
	{
		while(x<=n){
			c[x]+=y;
			x+=lowbit(x);
		}
	}
	int query(int x)//查询前缀和
	{
		int sum=0;
		while(x){
			sum+=c[x];
			x-=lowbit(x);
		}
		return sum;
	}
}t;
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		p[i]=read();
	for(int i=1;i<=n;i++)
		v[i]=read(),t.add(i,v[i]); 
	for(int i=1;i<=m;i++){
		int r;
		l[i]=read(),r=read(); 
		q[r].push_back(i);//记录右端点在 r 上的所有询问编号
	}
	for(int i=1;i<=n;i++){
		pos[p[i]].push_back(i);//记录第 p[i] 中礼物的位置
		if(pos[p[i]].size()>=k){//如果第 p[i] 种礼物出现了不小于 k 次
			int del_id=pos[p[i]][pos[p[i]].size()-k];//找到礼物位置
			t.add(del_id,-v[del_id]);//删掉，即 v[del_id]=0
		}
		for(int j=0;j<q[i].size();j++){
			int id=q[i][j];//询问编号
			ans[id]=t.query(i)-t.query(l[id]-1);//区间求和，即答案
		}
	}
	for(int i=1;i<=m;++i)
		print(ans[i]),putchar('\n');
	return 0;
}
```


---

## 作者：fush (赞：3)

我们先看一道弱化版：[P1972](https://www.luogu.com.cn/problem/P1972)。

在 P1972 中，我们将询问离线，每个颜色当前的最后一位才有贡献。

在这道题，我们每个颜色有了不同的贡献，从保留一位变成保留 $k$ 个。

我们先对当前位置单点加。  
如果超出 $k$ 个，就把最前面的数减去。  
答案就是当前的区间和。

用树状数组做单点修改、区间查询，用 vector 访问前面的数。

```c++
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
#define FL(a, b, c) for(int a = (b), a##end = (c); a <= a##end; a++)
#define FR(a, b, c) for(int a = (b), a##end = (c); a >= a##end; a--)
#define lowbit(x) ((x) & -(x))
constexpr int N = 1e6 + 10;
int w[N], n, p[N], v[N], vis[N], ans[N];
vector<int>d[N];
void add(int x, int v){while(x <= n)w[x] += v, x += lowbit(x);}
int query(int l, int r, int ans = 0){
	while(r > l)ans += w[r], r -= lowbit(r);
	while(l > r)ans -= w[l], l -= lowbit(l);
	return ans;
}
struct A{int l, r, id;}c[N];
int32_t main(){
	cin.tie(0)->sync_with_stdio(0);
	int q, k;
	cin >> n >> q >> k;
	FL(i, 1, n)cin >> p[i], d[p[i]].emplace_back(i);
	FL(i, 1, n)cin >> v[i];
	FL(i, 1, q)cin >> c[i].l >> c[i].r, c[i].id = i;
	sort(c + 1, c + 1 + q, [](A&i, A&j){return i.r < j.r;});
	int j = 1, z;
	FL(i, 1, n){
		vis[p[i]]++, add(i, v[i]);
		if(vis[p[i]] >= k){
			z = d[p[i]][vis[p[i]] - k];
			add(z, -v[z]);
		}
		while(c[j].r == i)
        ans[c[j].id] = query(c[j].l - 1, c[j].r), j++;
		if(j > q)break;
	}
	FL(i, 1, q)
	cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：Melo_DDD (赞：1)

线段树常数大，比树状数组慢好多。

所以我选择线段树（单个测试点一秒半你慌什么）。

## 观察题目
分析一下题目。

注意到是从右往左数，这给我们一些启发，注意到对于当前的右端点 $r_0$，如果一个点 $p$ 已经非法，那么对任意的 $r_t\ge r_0$，$p$ 也一定不合法。

所以我们按右端点从小到大的顺序计算即可，注意题目中第 $k$ 个也不会查看。
## 实现
根据上面的分析，考虑采用离线做法，即对于每个右端点，记录它所对应的左端点。

在右端点从左往右扫的过程中，我们记录每种礼物的出现位置（以及次数），如果这个种类的出现总次数已经不小于 $k$，那么应当将最左边的还没去掉的礼物的价值设为 $0$。

最后直接对当前的区间统计区间和即可。

转化一下：单点修改加上区间查询，线段树没跑了。

代码：

```cpp
#include <bits/stdc++.h>
#define ls (cur) << 1
#define rs (cur) << 1 | 1
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
const int N = 5e5 + 7 ;
const int M = 1e6 + 7 ;
int n ,m ,k ,p[M] ,v[M] ,l[N] ,ans[N] ;
vector < int > r[M] ,loc[M] ;
struct segment_tree {
	int l ,r ,ans ;
	#define l(cur) t[cur].l
	#define r(cur) t[cur].r
	#define ans(cur) t[cur].ans 
} t[M << 2] ;
namespace melo {
	inline void pushup (int cur) {
		ans (cur) = ans (ls) + ans (rs) ;
	}
	inline void build (int cur ,int l ,int r) {
		l (cur) = l ;
		r (cur) = r ;
		ans (cur) = 0 ;
		if (l == r) return ;
		int mid = l + r >> 1 ;
		melo :: build (ls ,l ,mid) ;
		melo :: build (rs ,mid + 1 ,r) ;
	}
	inline void modify (int cur ,int x ,int add) {
		if (l (cur) == r(cur)) {
			ans (cur) += add ;
			return ;
		}
		int mid = l (cur) + r (cur) >> 1 ;
		if (x <= mid) {
			melo :: modify (ls ,x ,add) ;
		} else {
			melo :: modify (rs ,x ,add) ;
		}
		melo :: pushup (cur) ;
	}
	inline int query (int cur ,int nowl ,int nowr) {
		if (nowl <= l (cur) && nowr >= r (cur)) {
			return ans (cur) ;
		}
		int mid = l (cur) + r (cur) >> 1 ,sum = 0 ;
		if (nowl <= mid && l (cur) <= nowr) {
			sum += melo :: query (ls ,nowl ,nowr) ;
		}
		if (nowr > mid && r (cur) >= nowl) {
			sum += melo :: query (rs ,nowl ,nowr) ;
		}
		return sum ;
	}
}
int main () {
	read (n) ,read (m) ,read (k) ;
	melo :: build (1 ,1 ,n) ;
	f (i ,1 ,n ,1) {
		read (p[i]) ;
	}
	f (i ,1 ,n ,1) {
		read (v[i]) ;
		melo :: modify (1 ,i ,v[i]) ;
	}
	f (i ,1 ,m ,1) {
		int rr ;
		read (l[i]) ,read (rr) ;
		r[rr].emplace_back (i) ;
	}
	f (i ,1 ,n ,1) {
		loc[p[i]].emplace_back (i) ; // 存储这个种类的出现位置
		if (loc[p[i]].size () >= k) {
			melo :: modify (1 ,loc[p[i]][loc[p[i]].size () - k] ,-v[loc[p[i]][loc[p[i]].size () - k]]) ; // loc.size () 即为目前这个种类的出现总数
		}
		if (! r[i].size ()) continue ;
		for (auto j : r[i]) {
			ans[j] = melo :: query (1 ,l[j] ,i) ; 
		} 
	}
	f (i ,1 ,m ,1) {
		cout << ans[i] << '\n' ;
	}
	return 0 ;
}
```
###### 彩蛋
既然线段树能过，分块一定可以。

所以我用分块写了一遍，结果半秒压死线段树（~~完了完了这回真的碾标算了~~）。

放上代码：

```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
const int N = 5e5 + 7 ;
const int M = 1e6 + 7 ;
const int S = 1007 ;
int n ,m ,k ,p[M] ,v[M] ,ll[N] ,ans[N] ,belong[M] ,b[M] ;
vector < int > r[M] ,loc[M] ;
int l[S] ,ri[S] ,sum[S] ;
namespace melo {
	inline void modify (int x ,int add) {
		int p = belong[x] ;
		b[x] += add ;
		sum[p] += add ;
	}
	inline int query (int L ,int R) {
		int p = belong[L] ,q = belong[R] ,ans = 0 ;
		if (p == q) {
			f (i ,L ,R ,1) {
				ans += b[i] ;
			}
			return ans ;
		} 
		f (i ,L ,ri[p] ,1) {
			ans += b[i] ;
		}
		f (i ,p + 1 ,q - 1 ,1) {
			ans += sum[i] ;
		}
		f (i ,l[q] ,R ,1) {
			ans += b[i] ;
		}
		return ans ;
	}
}
int main () {
	read (n) ,read (m) ,read (k) ;
	int t = sqrt (n) ;
	f (i ,1 ,t ,1) {
		l[i] = (i - 1) * t + 1 ;
		ri[i] = i * t ;
	}
	if (ri[t] < n) {
		t ++ ;
		l[t] = ri[t - 1] + 1 ;
		ri[t] = n ;
	}
	f (i ,1 ,t ,1) {
		f (j ,l[i] ,ri[i] ,1) {
			belong[j] = i ;
		}
	}
	f (i ,1 ,n ,1) {
		read (p[i]) ;
	}
	f (i ,1 ,n ,1) {
		read (v[i]) ;
		melo :: modify (i ,v[i]) ;
	}
	f (i ,1 ,m ,1) {
		int rr ;
		read (ll[i]) ,read (rr) ;
		r[rr].emplace_back (i) ;
	}
	f (i ,1 ,n ,1) {
		loc[p[i]].emplace_back (i) ;
		if (loc[p[i]].size () >= k) {
			melo :: modify (loc[p[i]][loc[p[i]].size () - k] ,-v[loc[p[i]][loc[p[i]].size () - k]]) ;
		}
		if (! r[i].size ()) continue ;
		for (auto j : r[i]) {
			ans[j] = melo :: query (ll[j] ,i) ; 
		} 
	}
	f (i ,1 ,m ,1) {
		cout << ans[i] << '\n' ;
	}
	return 0 ;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

树状数组求解。

可参考题目 [[SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)  

两道特别有趣的蓝题，其实都是一个思路。

我们考虑使用扫描线将询问区间离线下来，当一个颜色没有出现 $k$ 次时我们就用树状数组单点加区间修改。          

当一个颜色出现 $k$ 次时我们就删最开始加入的那个位置即可。

时间复杂度 $O(n \log n)$ 。

``` cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
vector<int> G[1000005];
int n,m,k,p[1000005],v[1000005],tot[1000005],ans[1000005],c[1000005],zhi[1000005];
struct node
{
	int l,r,wh;
}ques[1000005];
bool cmp(node x,node y)
{
	return x.r < y.r;
}
int lowbit(int x)
{
	return x & (-x);
}
void add(int x,int d)
{
	while(x <= n)
	{
		c[x] += d;
		x += lowbit(x);
	}
}
long long query(int x)
{
	long long res = 0;
	while(x > 0)
	{
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}
int main()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1; i <= n ; i ++)
		scanf("%d",&p[i]);
	for(int i = 1; i <= n; i ++)
		scanf("%d",&v[i]);
	for(int i = 1; i <= m; i ++)
	{
		scanf("%d %d",&ques[i].l,&ques[i].r);
		ques[i].wh = i;
	}
	sort(ques + 1,ques + 1 + m,cmp);
	int nex = 0;
	for(int i = 1; i <= m; i ++)
	{
		while(nex < ques[i].r)
		{
			G[p[nex]].push_back(nex);
			nex ++;
			tot[p[nex]] ++;
			add(nex,v[nex]);
			if(tot[p[nex]] >= k)
				add(G[p[nex]][zhi[p[nex]] ++],-v[G[p[nex]][zhi[p[nex]]]]);
		}
		ans[ques[i].wh] = query(ques[i].r) - query(ques[i].l - 1);
	}
	for(int i = 1; i <= m; i ++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：joe_zxq (赞：0)

# Part 1 - 算法思路

~~我是一个正在恶补数据结构的彩笔。~~

这道题与 P1972 十分相像，考虑将询问离线，使用树状数组维护，算法涉及内容为 P3374。

我们使用 vector 记录每一个右端点的询问编号。从左到右依次扫描每一个礼物，用 vector 记录每一个种类当目前为止出现过的下标。对于当前枚举的位置，令下标为 $i$，种类为 $t$，该种类出现了 $a$ 次，如果 $a \ge k$，用树状数组将第 $a - k + 1$ 个礼物的价值赋为 $0$，因为它已经完全失去价值。

对于每一个该右端点对应的询问，设询问的左端点为 $l$，那么答案就是第 $l$ 个礼物到第 $i$ 个礼物当前价值之和，用树状数组进行计算。最后按顺序输出答案即可。

# Part 2 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, k, a[1000005], c[1000005], v[1000005];
int l[1000005], ans[1000005];
vector<int> r[1000005];
vector<int> p[1000005];

int lowbit(int x) {
	return x & -x;
}

void update(int x, int k) {
	for (int i = x; i <= n; i += lowbit(i)) {
		c[i] += k;
	}
}

int query(int x, int res = 0) {
	for (int i = x; i >= 1; i -= lowbit(i)) {
		res += c[i];
	}
	return res;
}

int calc(int l, int r) {
	return query(r) - query(l - 1);
}

int main() {

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &v[i]);
		update(i, v[i]);
	}
	for (int i = 1, rr; i <= m; i++) {
		scanf("%d %d", &l[i], &rr);
		r[rr].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		p[a[i]].push_back(i);
		if ((int)p[a[i]].size() >= k) {
			update(p[a[i]][(int)p[a[i]].size() - k], -v[p[a[i]][(int)p[a[i]].size() - k]]);
		}
		for (int id : r[i]) {
			ans[id] = calc(l[id], i);
		}
	}
	for (int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}

	return 0;
}
```

---

## 作者：Ccliang (赞：0)

思路：树状数组+莫队

还是一道比较简单的离线操作的题目，和[HH的项链](https://www.luogu.com.cn/problem/P1972)还有[采花](https://www.luogu.com.cn/problem/P4113)的做法是一样的。

先将询问按照 $r$ 从小到大排序。

然后依次遍历这些询问，将小于当前询问 $r$ 编号的物品的价值加入树状数组中维护前缀和，设加入的是第 $i$ 个礼物，操作即 $change(i,w[i])$。

在此过程中同时将看到的次数$=k$ 的品种的礼物在树状数组上删去第一个（没删去的第一个），设这第一个礼物的编号为 $j$ ，操作即 $change(j,-w[i])$。

最后该询问的答案 $ans=query(r)-query(l-1)$ 。

复杂度：$O(nlogn)$

具体操作实现可以看我代码：

不开$O2$的效率：$4.03s/51.32MB$

开$O2$后：$2.00s/51.36MB$，最优解第二，~~还算比较快吧。~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e6 + 10;
const int M = 5e5 + 10;

inline int read()
{
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')res=(res<<1)+(res<<3)+(ch^48),ch=getchar();
	return res;
}

struct query{
	int l,r,id;
}Q[M];

bool cmp(query x,query y)
{
	return x.r<y.r;
}

int sum[N],ans[M],p[N],w[N],n,m,k,cnt=1;
#define lowbit(x) ((x)&(-x))
void change(int x,int v)
{
	while(x<=n)
		sum[x]+=v,x+=lowbit(x);
}

int getsum(int x)
{
	int res=0;
	while(x>0)
		res+=sum[x],x-=lowbit(x);
	return res;
}

vector<int>q[N];

int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		p[i]=read();
	for(int i=1;i<=n;i++)
		w[i]=read();
	for(int i=1;i<=m;i++)
		Q[i].l=read(),Q[i].r=read(),Q[i].id=i;
	sort(Q+1,Q+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		while(cnt<=Q[i].r)
		{
			change(cnt,w[cnt]),q[p[cnt]].push_back(cnt);
			if(q[p[cnt]].size()>=k)
				change(q[p[cnt]][q[p[cnt]].size()-k],-w[q[p[cnt]][q[p[cnt]].size()-k]]);
			cnt++;
		}
		ans[Q[i].id]=getsum(Q[i].r)-getsum(Q[i].l-1);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

