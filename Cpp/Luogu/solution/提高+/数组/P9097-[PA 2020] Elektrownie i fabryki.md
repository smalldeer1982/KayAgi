# [PA 2020] Elektrownie i fabryki

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 2 [Elektrownie i fabryki](https://sio2.mimuw.edu.pl/c/pa-2020-1/p/ele/)**

为了应对不断上升的失业率，Byteotia 政府决定创造新的就业机会。为此将建设现代化的工厂，还要建设为工厂供电的新发电厂。

一条很长的高速公路穿过 Byteotia，沿途有 $n$ 个城市。为了简单起见，我们从 $1$ 到 $n$ 对城市进行编号。每两个相邻城市之间都相距一公里。

目前已经决定一些城市建设工厂，另一些城市建设发电厂。对于第 $i$ 个城市有一个值 $a_i$。如果它是正数，则在第 $i$ 个城市将建造一个发电容量为 $a_i$ 兆瓦的发电厂，如果它是负数，则在该城市将建造一个消耗电能 $a_i$ 兆瓦的工厂。如果 $a_i=0$，则说明该城市没有建设计划。

你的任务是设计一个电网，将电力从发电站输送到工厂。对于每一对相邻的城镇，你必须决定是否在它们之间建立一条输电线。如果这个城市被输电线直接或间接连接到某个有发电站的城市，电力就可以从发电站流向这个城市的工厂。如果每个工厂的电力需求都得到满足，那么电网的设计就是正确的。电网的成本与电网输电线的总长度（以公里计）成正比。

写一个程序计算设计一个正确的电网最小成本是多少。

## 说明/提示

#### 样例 1 解释

下面是一个包含 $n=17$ 个城市的样例，其中将建造三个工厂（白圈）和四个发电厂（黑圈）。$12$ 公里的正确电网用灰色部分标记。

![](https://cdn.luogu.com.cn/upload/image_hosting/2wee5eoz.png)

------------

#### 数据范围

**本题采用捆绑测试**

对于一些子任务，满足 $n\le 5\times 10^3$。

对于 $100\%$ 的数据，保证 $1\le n\le 5\times 10^5$，$-10^9\le a_i\le 10^9$。

## 样例 #1

### 输入

```
17
2 -5 0 2 0 0 0 4 0 0 -1 4 0 0 0 0 -3```

### 输出

```
12```

# 题解

## 作者：_Spectator_ (赞：3)

[可能更好的食用体验](/article/btwsjpm1) $|$ 
[题目传送门](/problem/P9097) $|$ 
[我的其他题解](/user/523641#article.2)

------------
### ${\color{#00CD00}\text{思路}}$

考虑 $\tt{DP}$。定义 $s_i=\sum\limits_{j=1}^i a_i$，$f_i$ 表示**满足前 $i$ 个城市的需求所需的最小花费**。根据这个定义，可以得到以下的状态转移方程：  
$$f_i = \min_{j=1}^i \left\{f_{j-1} + i - j\right\},s_i - s_{j-1} \ge 0$$

它的含义是：枚举一个分界点 $j$，如果 $i\sim j$ 这一段城市可以“自给自足”（$s_i - s_{j-1} \ge 0$），就使用 $i-j$ 条电线将 $i\sim j$ 这一段城市连接起来，再加上前 $j-1$ 个城市的花费，求最小的花费。

写成代码是这样的：
```cpp
memset(f, 0x3f, sizeof(f)), f[0] = 0;
for(int i=1; i<=n; i++){
    for(int j=1; j<=i; j++){
        if(s[i] - s[j-1] >= 0) f[i] = min(f[i], f[j-1] + i - j);
    }
}
```

朴素的 $\tt{DP}$ 是 $O(n^2)$ 的，会超时。考虑优化转移。观察这个转移方程，发现结果只与 $f_j - j$ 有关。于是可以转化为：对于所有小于等于 $s_i$ 的 $s_j$，求 $f_j - j$ 的最小值。这是可以用树状数组之类的数据结构维护的。于是我们就将转移优化为了 $O(n\log n)$，可以通过本题。

具体地，先将所有的 $s_i$ 离散化，对于每个 $i$，查询 $s_i$ 以内的 $f_j - j$ 的最小值，假设为 $t$，$f_i$ 即为 $t + i - 1$。然后在树状数组中将 $s_i$ 这一位更新为 $f_i - i$ 即可。

------------
### ${\color{#00CD00}\text{代码}}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
long long n, s[N], rk[N];
int a[N], f[N];
struct BIT{
	int c[N], lowbit(int x){return x & -x;}; BIT(){memset(c, 0x3f, sizeof(c));}
	void update(int x, int k){while(x < N) c[x] = min(c[x], k), x += lowbit(x);}
	int query(int x){int s = N; while(x) s = min(s, c[x]), x -= lowbit(x); return s;}
} t;
signed main(){
	cin.tie(nullptr) -> sync_with_stdio(false);
	cin >> n; 
	for(int i=1; i<=n; i++) cin >> a[i], rk[i] = s[i] = s[i-1] + a[i];
	sort(rk, rk + 1 + n); int k = unique(rk, rk + 1 + n) - rk;
	for(int i=0; i<=n; i++) s[i] = lower_bound(rk, rk + 1 + k, s[i]) - rk + 1;
	t.update(s[0], 0);
	for(int i=1; i<=n; i++){
		f[i] = t.query(s[i]) + i - 1;
		t.update(s[i], f[i] - i);
	}
	cout << (f[n] > n ? -1 : f[n]);
	return 0;
}
```

---

## 作者：wuudii (赞：3)

## I.暴力算法
首先看到数据范围，考虑 dp，设 $f_i$ 表示使前 $i$ 个城市满足要求的最小代价，易得此状态没有后效性，可以 dp。

接着考虑状态转移方程，可以考虑枚举一个 $j$，表示将从 $j$ 到 $i$ 中的所有城市连接起来。则转移必须满足 $\sum_{k=j}^i a_i\ge0$，于是考虑用前缀和维护。易得一个被连接起来的左右端点必为一个有发电厂或工厂的城市（若区间两端都为工厂或发电厂，而向左或向右延伸为空白城市，则延伸显然不会更优）。所以，我们可以记录一个数组 $pre_i$，表示一个点左侧（包括这个点）的第一个非空白城市的位置，则易得转移方程为：
$$f_i=\min\{f_i,f_{pre_{j-1}}+i-j\}$$
同时，注意一个发电厂可以不与其他城市连接，故当 $i$ 为发电厂时，还有：
$$f_i=\min\{f_i,f_{pre_{i-1}}\}$$

最后，答案显然只用取最后一个非空城市的 $f$ 值即可。

时间复杂度 $O(n^2)$，可以得到 $50pts$。

## II.优化算法

发现转移方程中 $f_{pre_{j-1}}-j$ 只与 $j$ 有关，所以可以考虑用数据结构维护。要求满足 $sum_i-sum_{j-1}\ge0$，则转化成求所有满足 $sum_{j-1} \le sum_i$ 的 $j$ 中 $f_{pre_{j-1}}-j$ 的最小值。需要支持单点修改和从 $1$ 至 $n$ 的区间查询，考虑树状数组。每次将 $f_{pre_{i-1}}-i$ 加入到 $sum_{i-1}$ 的位置，查询时询问 $1$ 到 $sum_i$ 的区间最小值。由于 $sum_i$ 较大，考虑先对 $sum_i$ 的值离散化后再处理。

离散化后，最多只有 $n$ 个不同的值，时间复杂度 $O(n \log n)$，可以通过。
### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,a[510000],sum[510000],pre[510000],nxt[510000],f[510000];
long long minf[510000],book[510000],ans=1e9;
void add(int x,long long num){
	for(;x<=n;x+=(x&-x)){
		minf[x]=min(minf[x],num);
	}
}
long long query(int x){
	long long ans=1e18;
	for(;x;x^=(x&-x)){
		ans=min(ans,minf[x]);
	}
	return ans;
}
int main(){
	cin>>n;
	bool flag=true;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
		pre[i]=pre[i-1];
		if(a[i]<0)flag=false;
		if(a[i]!=0){
			nxt[pre[i]]=i;
			pre[i]=i;
		}
	}
	if(flag){
		printf("0");
		return 0;
	}
	nxt[pre[n]]=n+1;
	if(sum[n]<0){
		printf("-1");
		return 0;
	}
	book[0]=0;
	for(int i=1;i<=n;i++){
		book[i]=sum[i];
	}
	sort(book,book+n+1);
	int tot=unique(book,book+n+1)-book;
	for(int i=0;i<=n;i++){
		sum[i]=lower_bound(book,book+tot,sum[i])-book; 
		sum[i]++;
	} 
	memset(minf,0x3f,sizeof(minf)); 
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=nxt[0];i<=n;i=nxt[i]){
		if(a[i]>0)f[i]=f[pre[i-1]];
		f[i]=min(f[i],i+query(sum[i]));
		add(sum[i-1],f[pre[i-1]]-i);
	}
	for(int i=n;i>=1;i--){
		if(a[i]!=0){
			printf("%lld",f[i]);
			return 0;
		}
	}
	
} 
```

## 提示

+ 当 $sum_n < 0$ 时，不存在合法的方案，输出 `-1`。

+ 可能存在没有非空白城市的情况，进行特判即可。

---

## 作者：qiliu (赞：2)

### 思路

#### part one 暴力

首先从暴力做起，暴力先打过来再优化。

我们发现一条线路若为最优，它的两个端点必然为一个工厂或者发电站且各点和必然大于等于零。

所以我们用一个前缀和数组 $sum$ 维护每个数列是否合法（当数列和法时有 $sum_i-sum_j\geq 0$），然后用一个 $f$ 来记录前 $i$ 个点中使其合法的最小代价，于是有：

$$f_i=\min \{ f_i,f_j+(i-j-1)|0 \le j < i , \sum_{k=j}^i \geq0\}$$

并且因为一个发点站可以不连边，所以当此点大于零时有：

$$f_i=\min \{ f_i,f_{i-1} \}$$

所以暴力代码就是枚举每一个非零点进行以上操作。

#### part two 正解

我们发现，在上面的 DP 式中，影响答案的只有 $f_j-j$，于是我们考虑用一个树状数组（不会的看看[这里](https://www.luogu.com.cn/problem/P3374)）来维护最小值。于是我们可以用树状数组来维护这个最小值，就可以做到在 $\log(n)$ 的复杂度中寻找最小值。

#### part three 代码

有注释，请放心食用。

```cpp
#include<bits/stdc++.h>
#define int long long
#define DEBUG(x) cerr<<#x<<'='<<x<<endl
using namespace std;
const int N=1e6+100;
const int INF=1e8;
int n,m;
int f[N];//这是DP数组 
int tree[N];//treeeee
int book[N],sum[N];//sum文中提到过，book下面会讲 
int lowbit(int x)
{
	return x&(-x);
}
void change(int x,int v)
{
	for(;x<=m;x+=lowbit(x))
	tree[x]=min(tree[x],v);
}
int findd(int x)
{
	int t=1e9;
	for(;x;x-=lowbit(x))
	t=min(t,tree[x]);
	return t;
}//树状数组单点修改区间查询，P3374 
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	int t;
    	cin>>t;
    	sum[i]=book[i]=sum[i-1]+t;
	}
	sort(book+1,book+n+2);
	m=unique(book+1,book+n+2)-book-1;//unique 对于数组或容器中相邻且相同的元素，将其中一个放到数组或容器末尾，返回去重后末尾指针。 
	for(int i=1;i<=m;i++)
	{
		tree[i]=INF;
	}
	for(int i=0;i<=n;i++)
	{
		int w=lower_bound(book+1,book+m+1,sum[i])-book;
		//lower_bound(l,r,x)是在[l,r]中二分出第一个大于等于x的数字的位置，减去book头指针得到下标。 
		//如果w这个位置满足条件，那么在这个树状数组中他的子节点一定也满足。  
		if(i==0)
		{
			change(w,-1);
			continue;
		}
		f[i]=findd(w)+i;
		if(sum[i]-sum[i-1]>=0)
		{
			f[i]=min(f[i],f[i-1]);
		}
		change(w,f[i]-i-1);//注意这个树状数组中的点是文中的f[j]-j-1。 
	}
	if(f[n]>n)cout<<-1;
	else cout<<f[n];
    //fclose(stdin);
    //fclose(stdout);
	return 0;
}
```

感谢收看~

---

## 作者：lovely_nst (赞：1)

# [P9097 [PA2020] EIF](https://www.luogu.com.cn/problem/P9097)

## 前置

1. 分段 DP

2. 树状数组

3. 二分等其它算法

## 正文

设 $f_i$ 为以 $i$ 为一段区间结束点，前 $i$ 个点的最小连边数。可以易得以下转移方程：

$$
f_i=\min\{f_j+(i-j-1)|(\sum_{k=j+1}^ia_i)\ge 0\}
$$

时间复杂度为 $O(n^3)$，用前缀和可优化为 $O(n^2)$。

接下来要优化，发现转移方程可以写成：

$$
f_i=i-1+\min\{f_j-j|(\sum_{k=j+1}^ia_i)\ge 0\}
$$

只与 $f_j-j$ 的值有关。若前缀和 $s_r\ge s_{l-1}(l\le r)$，则 $(\sum_{k=l}^ra_i)\ge 0$。因此用树状数组维护即可，记得离散化。

## AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n , m , x , s[500005] , S[500005] , d[500005] , f[500005];
void upd (int pos , int c) { while (pos <= m) d[pos] = min (d[pos] , c) , pos += (pos & -pos); }
int qry (int pos) { int ans = 1e9; while (pos) ans = min (ans , d[pos]) , pos -= (pos & -pos); return ans; }
signed main ()
{
	ios::sync_with_stdio (0) , cin.tie () , cout.tie ();
	cin >> n;
	for (int i = 1;i <= n;i ++)
		cin >> x , S[i] = s[i] = s[i - 1] + x , d[i] = 1e18;
    d[n + 1] = 1e18;
	sort (S + 1 , S + n + 2);
	m = unique (S + 1 , S + n + 2) - S - 1;
	for (int i = 1;i <= m;i ++)
		if (S[i] == 0)
			upd (i , 0);
	for (int i = 1;i <= n;i ++)
	{
		int fd = lower_bound (S + 1 , S + m + 1 , s[i]) - S;
		f[i] = qry (fd) + i - 1;
		upd (fd , f[i] - i);
	}
	if (f[n] > n)
	    f[n] = -1;
	cout << f[n];
	return 0;
}
```

---

## 作者：xs_siqi (赞：1)

可以考虑 dp。

首先这个东西转移顺序很迷啊，所以考虑钦定顺序。钦定顺序是从后往前的。

$f_i$ 表示到 $i$ 号点为止的最小代价。考虑把当前的点（发电站或用电站，其他的空地可以不管）连到一个段里面去。

然后显然这个段的总电量是需要比 $0$ 大的，否则就出现了供应负电的情况。然后这个东西可以考虑使用一个前缀和来维护判断它是否可行。

转移方程就是 $f_i=\min\{{f_{j-1}+dis_{i,j}}\}$ 且有 $j\leq i$。意思就是当前的段左端点为 $j$，右端点为 $i$，然后这一段的代价就是 $dis_{i,j}$（其实就是 $i-j$）。关键代码（$d$ 是两个点的位置，$sum$ 是对于电量的前缀和）：

```cpp

for(int i=1;i<=m;i++)
	for(int j=i;j>=1;j--)
		if(sum[i]-sum[j-1]>=0)
			f[i]=min(f[i],f[j-1]+d[i]-d[j]);
```
然后考虑如何去优化这个东西。发现这个式子的大小只与 $f_{j-1}-d_j$ 有关，那么我们离散化完，树状数组和权值线段树二选一维护最小值就好了。

下面那个线段树不用 `pushdown` 的原因是每次修改都是单点的，只是我比较迷把它写成区间修改了。

```cpp
#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const int maxn=5e5+5;
int n,m,a[maxn],b[maxn],tot,d[maxn],f[maxn],inf,tr[maxn*4],q[maxn],t;
long long sum[maxn],p[maxn];
void pushup(int rt){tr[rt]=min(tr[ls],tr[rs]);}
void modify(int rt,int l,int r,int ql,int qr,int v){
	if(ql<=l&&r<=qr){tr[rt]=min(tr[rt],v);return ;}
	int mid=l+r>>1;
	if(ql<=mid)modify(ls,l,mid,ql,qr,v);
	if(qr>mid)modify(rs,mid+1,r,ql,qr,v);
	pushup(rt);
}
int query(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[rt];
	int ans=1e9,mid=l+r>>1;
	if(ql<=mid)ans=query(ls,l,mid,ql,qr);
	if(qr>mid)ans=min(ans,query(rs,mid+1,r,ql,qr));
	return ans;
}
int main(){
	memset(f,63,sizeof f);
	memset(tr,63,sizeof tr);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)if(a[i]!=0)b[++m]=a[i],d[m]=i;
	for(int i=1;i<=m;i++)sum[i]=sum[i-1]+b[i],p[i]=sum[i];
	p[m+1]=0;
	sort(p+1,p+m+2);
	int r=unique(p+1,p+m+2)-p-1;
	for(int i=0;i<=m;i++)sum[i]=lower_bound(p+1,p+r+1,sum[i])-p;
	inf=f[0];f[0]=0;
	bool fl=0;
	for(int i=1;i<=m;i++)
		modify(1,1,r,sum[i-1],sum[i-1],f[i-1]-d[i]),
		f[i]=min(f[i],d[i]+query(1,1,r,1,sum[i]));
	printf("%d\n",f[m]==inf?-1:f[m]);
	return 0;
}
```


---

## 作者：Fzrcy (赞：1)

设 $f_i$ 表示只考虑前 $i$ 个城市的最小成本，若不存在一个正确的电网，则 $f_i=\infty$。设 $s_i=\sum_{j=1}^ia_j$。

有：
$$
f_i=\min\{f_j+(i-j-1)\mid 0\le j<i,s_j\le s_i\}
$$
若 $a_i\ge 0$，还有 $f_i=\min(f_i,f_{i-1})$。

直接用树状数组维护 $f_i-i-1$ 的最小值即可，时间复杂度为线性对数。

```cpp
// qwq
#include <bits/stdc++.h>
#define gc getchar()
using namespace std;
inline int in(){
    char c;int x=0,bo=0;
    while(!isdigit(c=gc))if(c=='-')bo=1;
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=gc;
    return bo?-x:x;
}
typedef long long ll;
constexpr int N=1e6+8;ll b[N],a[N];int n,m,f[N],c[N];
void add(int x,int v){for(;x<=m;x+=x&-x)c[x]=min(c[x],v);}
int Q(int x){int r=1e9;for(;x;x-=x&-x)r=min(r,c[x]);return r;}
int main(){
    n=in();
    for(int i=1;i<=n;i++)
        a[i]=b[i]=a[i-1]+in();
    sort(b+1,b+n+2),m=unique(b+1,b+n+2)-b-1;
    for(int i=1;i<=m;i++)c[i]=1e8;
    for(int i=0;i<=n;i++){
        int x=lower_bound(b+1,b+m+1,a[i])-b;
        if(!i){add(x,-1);continue;}
        f[i]=Q(x)+i;
        if(a[i]-a[i-1]>=0)f[i]=min(f[i],f[i-1]);
        add(x,f[i]-i-1);
    }
    cout<<(f[n]>n?-1:f[n])<<'\n';
    return 0;
}
```



---

## 作者：hjyowl (赞：1)

### 思路

首先考虑用分段动态规划，令 $f_i$ 表示以为 $i$ 这段结尾前 $i$ 个所需最少的边数，用了前缀和优化后时间复杂度 $\Theta(n^2)$。

我们发现，只有对于 $s_{j-1} \le s_i$ 才去和 $f_{j-1}+i-j$ 取最小，所以说对于这种满足特定条件求最小，我们考虑对 $s$ 离散化，然后每次查询 $s_i$ 之前的最小的 $f_j - j$，我们发现可以用树状数组实现，我们得到这个最小的 $f_j-j$ 然后加上 $i-1$ 即可，实现复杂度可以做到 $\Theta(n \log n)$。

为了避免 $s$ 里的值过大，需要对 $s$ 进行离散化。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 500010;
long long f[N],s[N],a[N];
long long tr[N];
	long long n;
long long lowbit(long long x){
	return x & -x;
}
void add(long long x,long long d){
	for (long long i = x; i < N; i += lowbit(i)){
		tr[i] = min(tr[i],d);
	}
}
long long sum(long long x){
	long long res = N;
	for (long long i = x; i ; i -= lowbit(i)){
		res = min(res,tr[i]);
	}
	return res;
} 
int main(){
	memset(tr,0x3f,sizeof tr);
	cin >> n;
	vector<long long>vec;
	set<long long>tt; 
	for (long long i =1; i <= n; i ++ ){
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
		vec.push_back(s[i]);
	}
	vec.push_back(0);
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for (long long i = 0; i <= n; i ++ ){
		s[i] = lower_bound(vec.begin(),vec.end(),s[i]) - vec.begin() + 1;
	}
	add(s[0],0);
	for (long long i = 1; i <= n; i ++ ){
		long long t = sum(s[i]);
		f[i] = t + i - 1;
		add(s[i],t - 1);
	}
	if (f[n] <= n){
		cout << f[n];
		return 0;
	}
	cout << -1;
	return 0;
} 
```

---

## 作者：wth2026 (赞：1)

# 题目大意
有 $n$ 个点，每一个点的点权为 $a_i$，要将一部分点连起来，使得每一部分的权值不为负。求最少连接多长。
# 思路
设 $f_i$ 表示只考虑前 $i$ 个城市的最小成本，有 $f_i = \min\{f_i + i - j - 1\}$。
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define float double
#define int long long
#define inf 0x3f3f3f3f

using namespace std;

struct Tree_array {
	int c[500005], n;
	
	int loubit(int s) {
		return s & -s;
	}
	
	void add(int k, int x) {
		for (int i = k; i <= n; i += loubit(i)) {
			c[i] = min(c[i], x);
		}
	}
	
	int ask(int k) {
		int ans = inf;
		
		for (int i = k; i; i -= loubit(i)) {
			ans = min(ans, c[i]);
		}
		
		return ans;
	}
} tr;

int n, m, a[500005], b[500005], f[500005], in, x;

void init() {
	memset(tr.c, inf, sizeof(tr.c));
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	
	cin >> n;
	tr.n = n;
	
	for (int i = 1; i <= n; ++ i) {
		cin >> in;
		a[i] = b[i] = a[i - 1] + in;
	}
	
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - b;
	
	for (int i = 0; i <= n; ++ i) {
		x = lower_bound(b + 1, b + m + 1, a[i]) - b;
		
		if (i == 0) {
			tr.add(x, -1);
			continue;
		}
		
		f[i] = tr.ask(x) + i;
		
		if (a[i] >= a[i - 1]) {
			f[i] = min(f[i], f[i - 1]);
		}
		
		tr.add(x, f[i] - i - 1);
	}
	
	if (f[n] > n) {
		cout << -1;
	} else {
		cout << f[n];
	}
	
	return 0;
}

```

---

## 作者：_ayaka_ (赞：0)

### 思路

似乎不难发现题意可以转化成另一个问题：

> 将一个长度为 $n$ 的序列分成若干个和 $\ge 0$ 的段，询问至多可以分成多少段。

然后考虑 DP。

DP 初值 $dp_0=0$，显然有 $O(n^2)$ 的式子：$dp_i=\max_{j=0}^{i-1} (dp_j+1)\times[sum_i-sum_j\ge 0]$。

然后考虑优化，$sum_i-sum_j\ge0$ 可以转化为 $sum_i\ge sum_j$，离散化 $sum$ 后以 $sum$ 为下标做一个线段树，查询在区间 $[1,sum_i]$ 这个区间中的最大值之后再把 $dp_i$ 存入线段树即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define ll (k<<1)
#define rr (k<<1|1)
int n, a[500005], sum[500005], dp[500005];
int st[1000005], un, nsum[1000005];
struct tree {
	int l, r, num;
} t[4000005];
inline void pushup(int k) {
	t[k].num = max(t[ll].num, t[rr].num);
	return ;
}
void build(int k, int l, int r) {
	t[k].l = l, t[k].r = r;
	if (l == r) {
		return ;
	}
	build(ll, l, mid);
	build(rr, mid + 1, r);
	pushup(k);
}
void update(int k, int c, int p) {
	if (t[k].l > c || t[k].r < c) return;
	if (t[k].l >= c && t[k].r <= c) {
		t[k].num = max(t[k].num, p);
		return ;
	}
	update(ll, c, p);
	update(rr, c, p);
	pushup(k);
}
int query(int k, int c) {
	if (t[k].l > c) return 0;
	if (t[k].r <= c) return t[k].num;
	return max(query(ll, c), query(rr, c));
}
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
		st[i] = sum[i];
	}
	if (sum[n] < 0) {
		cout << "-1";
		return 0;
	}//特判
	sort(st + 1, st + n + 1);
	un = unique(st + 1, st + n + 1) - st - 1;
	for (int i = 1; i <= n; i++) {
		nsum[i] = lower_bound(st + 1, st + un + 1, sum[i]) - st;
	}
	build(1, 1, un);
	for (int i = 1; i <= n; i++) {
		if (sum[i] < 0) dp[i] = -1;//也是特判
		else dp[i] = query(1, nsum[i]) + 1;
		update(1, nsum[i], dp[i]);
	}
	cout << n - dp[n];
	return 0;
}
```

---

