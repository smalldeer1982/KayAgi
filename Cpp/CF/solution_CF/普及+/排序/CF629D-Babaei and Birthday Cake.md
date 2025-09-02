# Babaei and Birthday Cake

## 题目描述

Babaei 打算制作一个特殊的蛋糕。蛋糕由一些已知半径和高度的圆柱体组成，蛋糕的体积等于相应圆柱体的体积之和。

但是，还有一些额外的烹饪限制。编号为 $i$ 的蛋糕只能放在桌子上或编号为 $j$ 的蛋糕上，其中 $j\lt i$。 此外，为了给朋友们留下深刻印象，只有当蛋糕 $i$ 的体积超过蛋糕 $j$ 的体积时，Babaei 才会把蛋糕 $i$ 放在蛋糕 $j$ 上面。

Babaei 想要准备一个总体积最大的生日蛋糕，请你帮助他找到这个最大体积。

## 样例 #1

### 输入

```
2
100 30
40 10
```

### 输出

```
942477.796077000
```

## 样例 #2

### 输入

```
4
1 1
9 7
1 4
10 7
```

### 输出

```
3983.539484752
```

# 题解

## 作者：lotus_grow (赞：3)

### 题目大意
有 $n$ 个**圆柱形**蛋糕，第 $i$ 个蛋糕半径为 $r_i$，高为 $h_i$。

要求把他们按照这样的方式堆起来：
- 下面的编号比上面的小；
- 下面的体积比上面的小。

求把这些蛋糕堆起来能得到的最大体积是多少。

### 思路
一看就是最长上升子序列的题目 ٩(*Ӧ)و

设编号为 $a_i$ ,体积为 $v_i$ .

显然 $dp$ 方程为 $f_i=max${ $f_j$ }$+v_i$ , ($1<=j<i$ , $a_j<a_i$ , $v_j<v_i$)

但如果按**编号**从小到大排序后做这个就$WA$了。

因为题目求的是最大体积，按编号排序后选择并不最优。所以按体积从小到大排序后$dp$.

因为此时编号无序，体积从小到大，对于编号 $a_i$ ，$dp$ 方程为 $f_i=max${ $f_j$ }$+v_i$ , ($1<=j<i$ , $a_j<a_i$ ) 时间复杂度$O(n^2)$

那么就可以用数据结构按编号维护 $f_i$ 的区间最大值，每次转移时用 $[1,a_i)$ 的最大值进行转移，时间复杂度$O(nlogn)$

### 注意
- 排序时，若体积相等，则按编号从大到小排序（想想看为什么∩( ・ω・)∩）
- 因为查询区间是 $[1,a_i)$ ，所以可以用树状数组维护ヾ(Ő∀Ő๑)ﾉ

### 代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;
typedef long long ll;
const double pi=acos(-1.0);

ll f[100001],c[100001];
int n;
struct node
{
	ll v;int id;
	node(ll a,int b){v=a,id=b;}node(){}
	bool operator <(const node &a) const
	{
		return v<a.v || (v==a.v && id>a.id);
	}
}a[100001];

void ins(int x,ll k)
{
	for(;x<=n;x+=x&(-x)) c[x]=max(c[x],k);
}
ll query(int x)
{
	ll res=0;
	for(;x;x-=x&(-x)) res=max(res,c[x]);
	return res;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		ll r,h;scanf("%lld%lld",&r,&h);
		a[i]=node(r*r*h,i);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) 
	{
		f[i]=query(a[i].id-1)+a[i].v;
		ins(a[i].id,f[i]);
	}
	for(int i=1;i<=n;i++) f[0]=max(f[0],f[i]);
	printf("%.9lf\n",f[0]*pi);
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
不难推出暴力 dp 式子：$dp_i=(\max\limits_{j=1}^{i-1}dp_j)+s_i$，$s_i$ 表示第 $i$ 个蛋糕的体积。考虑优化，可以用树状数组快速求出 $\max\limits_{j=1}^{i-1}dp_j$，但是要离散化。因为我懒，所以我换了种方法。

以体积为第一关键字从小到大排序，然后依次枚举数组，最后还是用树状数组解决（此时树状数组的下标代表原数组下标）。
# 注意事项
必须以下标从大到小作为第二关键字，否则你会和我一样 WA#37。

原因：当你出现两个体积相同的蛋糕时，如果你下标从小到大排序了，那你就可以把前一个蛋糕放到后一个上，但事实上是不可以这么做的。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const double pi = acos (-1); //众所周知 π=acos(-1)
struct node {
	int id;
	ll s;
	bool operator < (const node& x) const {
		return s != x.s ? s < x.s : id > x.id;
	}
} a[100005];
int n, x, y;
ll maxx, s, tr[100005];
void add (int x, ll y) {
	while (x <= n)
		tr[x] = max (tr[x], y), x += x & -x;
	return ;
}
ll find (int x) {
	ll maxx = 0;
	while (x)
		maxx = max (maxx, tr[x]), x ^= x & -x;
	return maxx;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i)
		cin >> x >> y, a[i] = {i, (ll) x * x * y};
	sort (a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++ i) {
		s = find (a[i].id - 1) + a[i].s;
		maxx = max (maxx, s);
		add (a[i].id, s);
	}
	cout << fixed << setprecision (10) << pi*maxx;
	return 0;
}
```

---

## 作者：Drind (赞：0)

### 题目解析

给定 $n$ 个圆柱体，要选出其中几个，保证前一个体积大于后一个，且总体积最大。

我们可以先写出一个很简单的动态规划方程。

$$dp_i=\max_{j=1}^{i-1}dp_j[v_i\ge v_j]$$

我们发现 $dp_i$ 能够由 $dp_j$ 转移当且仅当 $i\gt j$ 且 $v_i \ge v_j$，显然是一个二维数点的问题，用树状数组维护即可，复杂度 $O(n\log n)$

记得离散化一下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

struct node{
	int r,h;
	int v;
}a[N];
int tmp[N];

int tree[N];

inline int lowbit(int x){
	return x&(-x);
}

void modify(int p,int val){
	while(p<N){
		tree[p]=max(tree[p],val);
		p+=lowbit(p); 
	}
}

int query(int p){
	int ans=0;
	while(p){
		ans=max(ans,tree[p]);
		p-=lowbit(p);
	}
	return ans;
}

int dp[N];

inline void fake_main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].r>>a[i].h; a[i].v=a[i].r*a[i].r*a[i].h;
		tmp[i]=a[i].v;
	}
	sort(tmp+1,tmp+n+1); int len=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++){
		a[i].v=lower_bound(tmp+1,tmp+len+1,a[i].v)-tmp;
	}
	
	int ans=0;
	for(int i=1;i<=n;i++){
		dp[i]=query(a[i].v-1)+tmp[a[i].v];//注意不要加成离散化后的值
		modify(a[i].v,dp[i]); ans=max(ans,dp[i]);
	}
	//计算的时候可以先不乘上这个 pi
	cout<<fixed<<setprecision(8)<<1.0*ans*acos(-1)<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF629D)

一道比较明显的二维偏序问题。

选择的蛋糕必须体积递增，树状数组需要预先离散化，可以选择使用动态开点的线段树。

可以发现，由于 $V=\pi r^2h$，所以我们的过程量使用整型变量保留精度，只需要在最后统一 $\times \pi$ 即可。

注意到体积会爆 int，所以应当使用 long long，最后再强制转化成 double 输出即可，注意题目对精度的要求较高，$\pi$ 要多取几位。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define N 100010
int n;
ll dp[N];
struct seg
{
	#define mid (l+r)/2
	ll mx[N*45];
	int L[N*45],R[N*45],times;
	seg()
	{
		times = 1;
	}
	inline void pushup(int u) 
	{
		mx[u] = max(mx[L[u]],mx[R[u]]);	
	} 
	ll query(int u,ll l,ll r,ll x,ll y)
	{
		if(!u) return 0;
		if(x <= l&&r <= y) return mx[u];
		ll ret = 0;
		if(x <= mid) ret = max(ret,query(L[u],l,mid,x,y));
		if(y > mid) ret = max(ret,query(R[u],mid+1,r,x,y));
		return ret;
	}
	int update(int u,ll l,ll r,ll x,ll y)
	{
		if(!u) u = ++times;
		if(l == r) 
		{
			mx[u] = max(mx[u],y);
			return u;	
		}
		if(x <= mid) L[u] = update(L[u],l,mid,x,y);
		else R[u] = update(R[u],mid+1,r,x,y);
		pushup(u);
		return u;	
	}
}tree;
ll ans;
int main()
{
	scanf("%d",&n);
	F(i,1,n)
	{
		ll r,h;
		scanf("%lld%lld",&r,&h);
		ll v = 1.0*r*r*h;
		dp[i] = v + tree.query(1,0,1e12,0,v-1.0);
		tree.update(1,0,1e12,v,dp[i]); 
		ans = max(ans,dp[i]);
	}
	printf("%.15lf",(double)ans * 3.14159265358979323846);
	return 0;
}
```


---

## 作者：EastPorridge (赞：0)

第一遍题解说不能直接按下标序 dp 是不完全正确的，这里提供一个用下标序 dp 的方法。 

### 题目分析：

对于题目，有对于当前位置 $i$，体积为 $a_i$，有转移方程 $f[i]= \max (f[j]) + a[i] (j < i,a_j < a_i)$，显然，直接转移是 $O(n^2)$ 的，所以要进行优化。

考虑一下树状数组优化 LIS 的原因，设当前数字为 $a[i]$，之所以可以直接在 $a[i]-1$ 里面查询前缀 $f[j]$ 的最大值 $(j < i)$，是因为树状数组的下标对应的就是 $a[i]$，天然有序的，那在这里也可以使用相同的方法了，我们将每个物品的体积离散化一下，当成下标，每次对于当前的 $i$，就二分出它的有序下标，即树状数组对应的下标，顺序转移就可以了。

### Code.

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const double pi=3.14159265357;
int n,tr[N],f[N],mx,num[N],a[N];
int lowbit(int x) {return x&-x;}
void modify(int x,int k) {for(int i=x;i<=n;i+=lowbit(i)) tr[i]=max(tr[i],k);}
int query(int x) {int res=0; for(int i=x;i;i-=lowbit(i)) res=max(res,tr[i]); return res; }
signed main()
{
	scanf("%lld",&n);
	for(int i=1,r,h;i<=n;i++) {scanf("%lld%lld",&r,&h); num[i]=a[i]=r*r*h; }
	stable_sort(num+1,num+1+n); int cnt=unique(num+1,num+1+n)-num-1;
	for(int i=1;i<=n;i++)
	{
		int tmp=lower_bound(num+1,num+1+cnt,a[i])-num;
		f[i]=query(tmp-1)+a[i]; modify(tmp,f[i]);
	}
	for(int i=1;i<=n;i++) mx=max(mx,f[i]);
	printf("%.7lf",1.0*pi*mx);
	return 0;
}
```


---

## 作者：stntn (赞：0)

## 简要题意

$n$ 个物品，每个物品有一个序号和体积 $v$。求一个体积和最大的子序列满足对于所有 $i<j$ 有 $v_i<v_j$。

**先说在前面，如果你始终 WA 却无法解决，试试算体积时先不算 $\pi$，最后答案再乘上 $\pi$。**

## DP

显然可以 DP，我们设 $f_{i}$ 表示当前以 $i$ 为最大体积结尾的子序列体积和的最大值，有转移方程：

$$
	f_{v_i}=\max_{j<v_i}  f_j+v_i
$$

但有几个问题：

1. 体积为小数，不方便作为状态。

1. 复杂度 $O(n^2)$，过不了。

对于第一个问题，我们发现最多只有 $n$ 个体积作为状态，于是可以用离散化解决。

对于第二个问题，我们发现每次转移就是从所有比它早出现，体积比它小的状态转移过来，这启发我们可以用线段树优化。

我们先对体积进行离散化，线段树维护 $f$ 数组（即按状态体积由低到高，不是编号！）。

转移的时候查询 $t=\max_{j<v_i} f_j$ ，将 $f_{v_i}$ 更新为 $t+v_i$。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 100010
#define int long long
#define ULL unsigned long long
#define DB long double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(i,u) for(int i=head[u];~i;i=e[i].nxt)
#define INF 0x3f3f3f3f3f3f3f
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
const DB pi=3.1415926535897932384626433832795;
struct LT
{
	#define mid ((l+r)>>1)
	#define lc rt<<1
	#define rc rt<<1|1
	DB f[N<<2];
	inline void build(int rt,int l,int r)
	{
		f[rt]=-INF;if(l==r) return;
		build(lc,l,mid);build(rc,mid+1,r);
	}
	inline void update(int rt,int l,int r,int pos,DB val)
	{
		if(l==r){f[rt]=max(f[rt],val);return;}
		if(pos<=mid) update(lc,l,mid,pos,val);
		else update(rc,mid+1,r,pos,val);
		f[rt]=max(f[lc],f[rc]);
	}
	inline DB query(int rt,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return f[rt];
		DB res=-INF;
		if(L<=mid) res=query(lc,l,mid,L,R);
		if(mid<R) res=max(res,query(rc,mid+1,r,L,R));
		return res;
	}
	#undef mid
	#undef lc
	#undef rc
}t;
int n,id[N];
DB a[N];
struct NODE
{
	DB val;int id;
	bool operator < (const NODE &b) const {return val!=b.val ? val<b.val : id>b.id;}
}b[N];
signed main()
{
	read(n);
	rep(i,1,n)
	{
		DB r,h;read(r,h);
		a[i]=b[i].val=r*r*h;
		b[i].id=i;
	}
	sort(b+1,b+1+n);
	rep(i,1,n) id[b[i].id]=i;
	t.build(1,1,n);t.update(1,1,n,id[1],a[1]);
	rep(i,2,n)
	{
		DB f= id[i]>1 ? t.query(1,1,n,1,id[i]-1) : -INF;
		t.update(1,1,n,id[i],max(f+a[i],a[i]));
	}
	printf("%.7Lf\n",t.query(1,1,n,1,n)*pi);
	return 0;
}
```

---

