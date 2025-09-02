# Big Maximum Sum

## 题目描述

Ahmed和Mostafa曾经一起竞争在许多编程比赛好几年了。他们的教练Fegla要求他们解决一个具有挑战性的问题，当然Ahmed能够解决它，但是Mostafa不能。
这个问题类似于最大连续子段和问题，但它有不同的格式和约束。
在最大连续子段和问题中，你得到一组整数，你必须在这个数组中找到一个或多个连续的元素，它们的和是最大可能的和。 
但在这个问题上，你有n个小数列和一个索引，这个索引里一次包含着小数组的编号，根据这一个索引将小数列串成一个大的数列，每个小数组可能出现不止一次，求大数列的最大连续子段和。例如，假设小数组是{ 1, 6，- 2 }，{ 3, 3 }和{ - 5, 1 }。大数组中的索引是{ 2, 3, 1，3 }。因此大数组中的实际值在将它格式化为小数组的串联之后将是{ 3, 3，- 5, 1, 1，6，- 2，- 5, 1 }。在这个例子中，最大和是9。你能帮Mostafa解决这个问题吗？

## 样例 #1

### 输入

```
3 4
3 1 6 -2
2 3 3
2 -5 1
2 3 1 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
6 1
4 0 8 -3 -10
8 3 -2 -5 10 8 -9 -5 -4
1 0
1 -3
3 -8 5 6
2 9 6
1
```

### 输出

```
8
```

# 题解

## 作者：玖梦 (赞：3)

## 题意简述

给定 $n(n<=50)$ 个长度不超过 $l(l<=5000)$ 的序列，以及一个长度为 $m(m<=250000)$ 的索引序列，每个索引表示某一序列的编号，然后按照这 $m$ 个索引的顺序，将小序列组成一个大序列，求这个大序列的最大子段和。

## 算法概述

首先看到数据范围，就知道暴力求大序列肯定不行。
考虑大序列的最大子段和的组成，无非以下两种情况：

* 某个小序列的最大子段和；
* 从某个小序列开始，到某个小序列结束。

对于第一种情况，我们只需对每个小序列都求一遍最大子段和，然后取 $m$ 个小序列中的最大值即可。

主要看第二种情况，我们可以设 $f[i]$ 表示以第 $i(1<=i<=m)$ 个小序列为结尾的最大子段和。

考虑枚举 $j$，表示以第 $j$ 个小序列为开头，则整段最大子段和即为第 $j$ 个小序列的最大后缀和，加上第 $j+1$ 到第 $i-1$ 个序列的和，再加上第 $i$ 个序列的最大前缀和。于是我们就得到了状态转移方程：

$f[i]=max(r[j]+sum[i-1]-sum[j]+l[i])$

其中 $sum[i]$ 表示从第 $1$ 个小序列首位开始到第 $i$ 个小序列的末位为止的所有数的总和，$l[i]$ 表示第 $i$ 个小序列的最大前缀和（至少包含 $1$ 个数），$r[i]$ 表示第 $i$ 个小序列的最大后缀和（至少包含 $1$ 个数），由于题目要求最大子段和至少要选择一个数，所以最大前缀和与最大后缀和均不能为空。

将状态转移方程整理得：

$f[i]=sum[i-1]+l[i]+max(r[j]-sum[j])$

我们发现，当 $i$ 固定的时候，我们 $sum[i-1]+l[i]$ 也就固定了，我们只需得到 $r[j]-sum[j]$ 的最大值即可，而 $j$ 的范围是 $1<=j<=i-1$，可以发现当 $i$ 增大时，$j$ 的范围只有右边界会发生改变，如果我们每次计算 $f[i]$ 的时候都将 $j$ 全部枚举一遍的话，会产生很多冗余计算，浪费时间。故我们没有必要循环枚举 $j$,只需用一个变量 $maxv$ 记录从1到当前为止的 $r-sum$ 的最大值，在循环 $i$ 的时候，先计算 $f[i]$ ，再将当前的 $r[i]-sum[i]$ 与 $maxv$ 比较，取较大值更新 $maxv$即可。于是我们就成功以 $O(m)$ 的时间完成了对 $f$ 数组计算。

故这种情况的答案即为 $f[1…m]$ 中的最大值。

将两种情况的答案取 $max$，就得到了整个大序列的最大子段和。

时间复杂度 $O(n*l+m)$。

## 参考代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=3e5+10,LEN=5e3+10,S=51,INF=1e18;

ll f[N],l[N],r[N],sum[N]; //以索引的顺序为序，记录以序列i为结尾的最大子段和、序列i的最大前缀和、序列i的最大后缀和、到序列i末位为止的总和 
ll lq[S],rq[S],sq[S],mq[S]; //以各序列的输入顺序为序，记录序列i的最大前缀和、最大后缀和、总和、最大子段和 
ll a[LEN],sx[LEN],mx[LEN]; //记录当前序列的值、前缀和、最大子段和 
int n,m;

int main()
{
	scanf("%d%d",&n,&m);
	memset(mq,-0x3f,sizeof mq);
	for(int i=1,s;i<=n;i++)
	{
		scanf("%d",&s);
		for(int j=1;j<=s;j++)scanf("%lld",&a[j]);
		for(int j=1;j<=s;j++)sx[j]=sx[j-1]+a[j];
		for(int j=1;j<=s;j++){mx[j]=max(mx[j-1]+a[j],a[j]);mq[i]=max(mq[i],mx[j]);}
		lq[i]=a[1]; //前缀不为空 
		for(int j=2;j<=s;j++)lq[i]=max(lq[i],sx[j]); 
		rq[i]=a[n]; //后缀不为空 
		for(int j=s-2;j>=0;j--)rq[i]=max(rq[i],sx[s]-sx[j]); 
		sq[i]=sx[s];
	}
	ll res=-INF;
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		l[i]=lq[x];
		r[i]=rq[x];
		sum[i]=sum[i-1]+sq[x];
		res=max(res,mq[x]);
	}
	
	f[1]=l[1];
	ll maxv=r[1]-sum[1],ans=f[1];
	for(int i=2;i<=m;i++)
	{
		f[i]=sum[i-1]+l[i]+maxv;
		maxv=max(maxv,r[i]-sum[i]);
		ans=max(ans,f[i]);
	}
	
	printf("%lld\n",max(ans,res));
	return 0;
}
```


---

## 作者：wxzzzz (赞：2)

### 题意

给定 $n$ 个序列，按顺序从这 $n$ 个序列里面选择 $m$ 个拼成一个新序列（可重复挑选），求新序列的最大子段和。

### 思路

设当前考虑到 $m$ 个序列中前 $i$ 个组成的序列，最大子段和为：

$$\max_{j=1}^{i-1}(suf_j+ss_{i-1}-ss_j+pre_i)$$

其中：

- $ss_i$ 表示前 $i$ 个序列所有元素之和。

- $pre_i$ 表示第 $i$ 个序列的最大前缀和。

- $suf_i$ 表示第 $i$ 个序列的最大后缀和。

然后这个式子可简化为：

$$pre_i+ss_{i-1}+\max_{j=1}^{i-1}(suf_j-ss_j)$$

然后枚举 $i$，答案取所有 $i$ 的最大值。

不过答案还有可能是某个小序列的最大子段和，预处理时顺便记下即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, tmp, l[1000005], t[1000005], ord[1000005], now[1000005];
long long ans = -1e18, maxn = -1e18, s[1000005], ss[1000005], pre[1000005], suf[1000005], maxs[1000005];
vector<long long> a[105];
void get(long long x) {
    long long ret = -1e18, sump = 0, sums = 0;
    memset(t, 0, sizeof t);

    for (int i = 1; i <= l[x]; i++)
        now[i] = a[x][i], s[x] += now[i];

    for (int i = 1; i <= l[x]; i++) {
        sump += now[i];
        pre[x] = max(pre[x], sump);
        t[i] = max(now[i], t[i - 1] + now[i]);
        ret = max(ret, t[i]);
    }

    for (int i = l[x]; i >= 1; i--) {
        sums += now[i];
        suf[x] = max(suf[x], sums);
    }

    maxs[x] = ret;
}
int main() {
    memset(pre, -0x3f, sizeof pre);
    memset(suf, -0x3f, sizeof suf);
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> l[i];
        a[i].push_back(0);

        for (int j = 1; j <= l[i]; j++) {
            cin >> tmp;
            a[i].push_back(tmp);
        }

        get(i);
    }

    for (int i = 1; i <= m; i++) {
        cin >> ord[i];
        ss[i] = ss[i - 1] + s[ord[i]];
        ans = max(ans, maxs[ord[i]]);
    }

    ans = max(ans, pre[ord[1]]);

    for (int i = 1; i <= m; i++) {
        if (i > 1)
            ans = max(ans, ss[i - 1] + pre[ord[i]] + maxn);

        maxn = max(maxn, suf[ord[i]] - ss[i]);
    }

    cout << ans;
    return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

[GSS 1](https://www.luogu.com.cn/problem/SP1043) 的超级弱化。

考虑如何合并两个区间 $A,B$，求出合并后的最大子段和。

不难发现只有三种情况：

1. 全在 $A$；
2. 全在 $B$；
3. 一部分在 $A$，一部分在 $B$。

显然前两种情况在 $A,B$ 已经处理过，第三种情况显然是 $A$ 的最大后缀加上 $B$ 的最大前缀。

也就是同时维护最大前缀和最大后缀，也是类似的，不再赘述。

那么解决 GSS 1 就是简单的了，用线段树维护这个过程。而注意到合并：


```cpp
ret.tr=ls.tr+rs.tr;
ret.lv=max(ls.lv,ls.tr+rs.lv);
ret.rv=max(rs.rv,rs.tr+ls.rv);
ret.val=max(max(ls.val,rs.val),ls.rv+rs.lv);
```

显然的，这个题就是让我们合并，所以构建 $m$ 个结构体变量然后按照上面的依次合并过去即可。模拟赛场上我写了一个封装。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;  
const int K=55, N=2.5e5+5;
int qt, n, i, j, m, psum, ssum, tot, x;
class node
{
public:
	ll pre, suf, tot, mx;
} ans, t[N];
template <typename T>
void in(T &x){
	char c=getchar(), f=1;
	while ((c<'0' || c>'9') && c!='-') c=getchar();
	if (c=='-') f=-1, c=getchar();
	for (x=0; c>='0' && c<='9'; c=getchar())
		x=x*10+c-'0';
	x*=f;
}
template <typename T>
void out(T x){
	if (x<0) putchar('-'), x=-x;
	if (x){
		out(x/10);
		putchar(x%10);
	}
}
inline const void operator+=(node &y, const node &x) 
{
	ans.pre=max(x.pre, x.tot+y.pre);
	ans.suf=max(y.suf, y.tot+x.suf);
	ans.mx=max(max(x.mx, y.mx), x.suf+y.pre);
	ans.tot=x.tot+y.tot;
	y=ans;
	return ;
}
int d[K][N], pre[K], suf[K], sori[K], s[K], k[K], nori[K];
int main()
{ 
	in(n); in(m);
	rep(i, 1, n) pre[i]=suf[i]=nori[i]=-1e18,s[i]=0;
	rep(i, 1, n)
	{
		in(k[i]); rep(j, 1, k[i]) in(d[i][j]);
		psum=ssum=0;
		rep(j, 1, k[i]) s[i]+=d[i][j]; rep(j, 1, k[i]) psum+=d[i][j], pre[i]=max(pre[i], psum);
		req(j, k[i], 1) ssum+=d[i][j], suf[i]=max(suf[i], ssum);
		tot=0; rep(j, 1, k[i])
		{
			tot+=d[i][j]; nori[i]=max(nori[i], tot);
			if(tot<0) tot=0;
		}
	}
	rep(i, 1, m)
	{
		in(x); 
		t[i].pre=pre[x]; t[i].suf=suf[x]; t[i].tot=s[x]; t[i].mx=nori[x];
		if(i>1) t[i]+=t[i-1];
	} printf("%lld\n", t[m].mx); 
}
```

---

## 作者：封禁用户 (赞：1)

小数组组成的大数组的最大子段和可能在一个小数组内，也可能在跨越了若干的小数组。

那么我们处理前 $i$ 个数组元素之和 $s_i$，前缀最大和 $pre_i$，后缀最大和 $suf_i$，和每个小数组的最大子段和 $mx_i$。

记 $f_i$ 为在大数组中以 $i$ 结尾的最大子段和，记该子段的开头为 $j$，有转移方程 $f_i = s_{i-1} + l_i - s_j + r_j (j \le i)$。实际上，有许多个 $i$ 是共用同一个 $j$ 的。那么在转移过程中维护 $\min_{1 \le j\le i}{-s_i+r_i}$。

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF75D)
## 思路
简单题。

考虑我们的答案有可能由两部分组成：

+ 每个序列的最大连续子段和。
+ 跨序列。

第一个部分非常的简单，直接预处理。

第二个部分需要 $\verb!DP!$，设 $f_i$ 表示以 $i$ 为结尾的最大连续子段和。

则转移方程为 $f_i= \max (p_i,l_{a_i}+sum_{i-1}+(r_{a_j}-sum{j}))$，发现可以直接前缀 $\max$，然后 $O(n)$ 做。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int a[N],sum[N],f[N],l[N],r[N],p[N],sigma[N];
inline int maxlen(int l,int r){
    int now=0,num=-1e9;
    for (int i=l;i<=r;++i){
        now+=a[i];
        num=max(num,now);
        if (now<0) now=0;
    }
    return num;
}
inline int maxl(int l,int r){
    int sum=0,now=0;
    for (int i=l;i<=r;++i){
        sum+=a[i];
        now=max(now,sum);
    }
    return now;
}
inline int maxr(int l,int r){
    int sum=0,now=-9e18;
    for (int i=r;i>=l;--i){
        sum+=a[i];
        now=max(now,sum);
    }
    return now;
}
signed main(){
    int n,m;
    //读入
    for (int i=1;i<=n;++i){
        int x;
        //读入
        for (int j=1;j<=x;++j) io.read(a[j]),sigma[i]+=a[j];
        p[i]=maxlen(1,x);
        l[i]=maxl(1,x);
        r[i]=maxr(1,x);
    }
    int maxx=-9e18,ans=-9e18;
    memset(f,-0x3f,sizeof(f));
    for (int i=1;i<=m;++i){
        io.read(a[i]);sum[i]=sum[i-1]+sigma[a[i]];
        f[i]=max(f[i],p[a[i]]);
        f[i]=max(f[i],l[a[i]]+sum[i-1]+maxx);
        maxx=max(maxx,r[a[i]]-sum[i]);
        ans=max(ans,f[i]);
    }
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：lgx57 (赞：0)

**温馨提示：本人的代码较长，思路较繁，请谨慎阅读。**

很明显的线段树维护最大子段和，先处理出每一个小数组的数据，在放到线段树上面合并即可，合并方式参见 [GSS1](https://www.luogu.com.cn/problem/SP1043)。

但是这题有一点比较坑，这题中选出来的最大子段不能为空，于是我们需要另外维护一些数据，并且保证选出来至少一个数。然后在求全局最大子段和时就不用向 $0$ 取 $\max$ 了。具体实现可以看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pii pair<int,int>
#define endl '\n'
#define pb push_back
#define ls(p) ((p)<<1)
#define rs(p) ((p)<<1|1)
#define lowbit(x) ((x)&(-(x)))
#define abs(x) ((x)>0?(x):(-(x)))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define gc getchar
#define pc putchar
#define sz(v) ((int)(v.size()))
using namespace std;
mt19937_64 Rand(chrono::steady_clock::now().time_since_epoch().count());
inline int read(){
	int x=0,f=1;
	char ch=gc();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=gc();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=gc();}
	return x*f;
}
inline void print(int x){
	if (x<0) pc('-'),x*=-1;
	if (x<10) pc(x+'0');
    else print(x/10),pc(x%10+'0');
}
const int N=55;
const int M=250005;
struct node{
	int len;//小数组的长度
	int lmax,rmax,sum;//小数组前缀和的最大值，后缀和的最大值，以及整个数组的和
	int ma;//最大子段和
	int lmax2,rmax2,ma2;//保证不为空的数据，意义与上面相同
}a[N],t[M<<2];//上面都是 GSS1 的常见操作
int b[M];
void push_up(int p){
	t[p].sum=t[ls(p)].sum+t[rs(p)].sum;
	t[p].lmax=max(t[ls(p)].lmax,t[ls(p)].sum+t[rs(p)].lmax);
	t[p].rmax=max(t[rs(p)].rmax,t[rs(p)].sum+t[ls(p)].rmax);
	t[p].ma=max(max(t[ls(p)].ma,t[rs(p)].ma),t[ls(p)].rmax+t[rs(p)].lmax);
	t[p].lmax2=max(t[ls(p)].lmax2,t[ls(p)].sum+t[rs(p)].lmax);
	t[p].rmax2=max(t[rs(p)].rmax2,t[rs(p)].sum+t[ls(p)].rmax);
	t[p].ma2=max(max(t[ls(p)].ma2,t[rs(p)].ma2),max(t[ls(p)].rmax2+t[rs(p)].lmax2,max(t[ls(p)].rmax2+t[rs(p)].lmax,t[ls(p)].rmax+t[rs(p)].lmax2)));//这里要注意细节，可能有很多种情况。
	if (p!=1){//不在求全局的时候向 0 取 max
		t[p].lmax=max(t[p].lmax,0ll);
		t[p].rmax=max(t[p].rmax,0ll); 
		t[p].ma=max(t[p].ma,0ll);
	}
}
void build(int p,int pl,int pr){
	if (pl==pr){
		t[p]=a[b[pl]];
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
int dp[N];
void sol(){
	int n,m;
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		cin>>a[i].len;
		vector<int> v;v.pb(0);
		a[i].lmax=a[i].rmax=a[i].sum=a[i].ma=0;
		a[i].lmax2=a[i].rmax2=a[i].ma2=-1e9;//因为不能为空，所以一开始不能取 0
		for (int j=1;j<=a[i].len;j++){
			int x;
			cin>>x;
			v.pb(x);
			a[i].sum+=x;
		}
		int now=0;
		for (int j=1;j<=a[i].len;j++){
			now+=v[j];
			a[i].lmax=max(a[i].lmax,now);
			a[i].lmax2=max(a[i].lmax2,now);
		}
		now=0;
		for (int j=a[i].len;j>=1;j--){
			now+=v[j];
			a[i].rmax=max(a[i].rmax,now);
			a[i].rmax2=max(a[i].rmax2,now);
		}
		now=0;
		for (int j=1;j<=a[i].len;j++){
			now=max(now+v[j],0ll);
			a[i].ma=max(a[i].ma,now);
		}
		int mx=-1e9;
		for (int j=1;j<=a[i].len;j++){
			mx=max(mx,v[j]);
		}
		if (mx<0) a[i].ma2=mx;//如果整个数组中所有数都 <0，那么这个数组最大的非空的子段和为数组中的最大值
		else a[i].ma2=a[i].ma;//否则，就是最大子段和
	}
	for (int i=1;i<=m;i++) cin>>b[i];
//	for (int i=1;i<=n;i++) cout<<"!! "<<a[i].lmax<<' '<<a[i].rmax<<' '<<a[i].sum<<' '<<a[i].ma<<endl<<"?? "<<a[i].lmax2<<" "<<a[i].rmax2<<" "<<a[i].ma2<<endl;
	build(1,1,m);//建线段树
	cout<<t[1].ma2;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;
	while (t--) sol();
	return 0;
}

```

---

