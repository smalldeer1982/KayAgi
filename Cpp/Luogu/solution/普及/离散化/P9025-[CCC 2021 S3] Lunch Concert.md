# [CCC 2021 S3] Lunch Concert

## 题目描述

有 $N$ 个人，第 $i$ 个人的速度为 $W_i$ **秒每米**，听力为 $D_i$，即能听见距离他不超过 $D_i$ 米处的音乐，初始在 $P_i$ 位置。

你要在 $c$ 位置处开音乐会，这个 $c$ 由你决定且为整数。这 $N$ 个人都会靠近你直到能听到你。你要最小化每个人移动的时间之和。

## 说明/提示

$$1\leq N\leq 200000,0\leq P_i\leq 10^9,1\leq W_i\leq 1000,0\leq D_i\leq 10^9$$

译自 [CCC2021 S3](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

###### 2023.8.10 新增一组 hack 数据。

## 样例 #1

### 输入

```
1
0 1000 0
```

### 输出

```
0```

## 样例 #2

### 输入

```
2
10 4 3
20 4 2
```

### 输出

```
20```

## 样例 #3

### 输入

```
3
6 8 3
1 4 1
14 5 2
```

### 输出

```
43```

# 题解

## 作者：_•́へ•́╬_ (赞：14)

## 思路

把一个人转化成一个线段 $[P_i-D_i,P_i+D_i]$，意思是 $c$ 在这个线段上时不需要任何时间，在左边和在右边都需要一定时间去移动。

于是我们就能得到一个分段函数。

利用离散化和差分把所有的分段函数加起来，取个最小值。

注：最小值一定在某个端点处取到。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#define N 444444
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,m,lsh[N],p[N],w[N],d[N];long long a[N],b[N],ans;
inline void add(const int&l,const int&r,const int&x,const long long&y)
	{a[l]+=x;a[r+1]-=x;b[l]+=y;b[r+1]-=y;}
inline void min(long long&x,const long long&y){if(x>y)x=y;}
main()
{
	read(n);
	for(int i=0;i<n;++i)
	{
		read(p[i]);read(w[i]);read(d[i]);
		lsh[m++]=p[i]-d[i];
		lsh[m++]=p[i]+d[i];
	}
	sort(lsh,lsh+m);m=unique(lsh,lsh+m)-lsh;
	for(int i=0,x;i<n;++i)
	{
		x=p[i]-d[i];
		add(0,lower_bound(lsh,lsh+m,x)-lsh,-w[i],(long long)(w[i])*x);
		x=p[i]+d[i];
		add(upper_bound(lsh,lsh+m,x)-lsh,m,w[i],-(long long)(w[i])*x);
	}
	ans=a[0]*lsh[0]+b[0];
	for(int i=1;i<=m;++i)
	{
		a[i]+=a[i-1];b[i]+=b[i-1];
		if(a[i]>>63)min(ans,a[i]*lsh[i]+b[i]);
		else min(ans,a[i]*lsh[i-1]+b[i]);
	}
	printf("%lld",ans);
}
```

---

## 作者：wjh2011 (赞：6)

## 解法：

由于答案是一个单谷函数，所以可以用三分求解。

### 证明如下：

设选定的位置为 $x$ ,则答案为 $\sum_{p_i+d_i<x}(x-p_i-d_i)+\sum_{p_i-d_i>x}(p_i-d_i-x)$ 。

当 $x$ 变大时，满足 $p_i+d_i<x$ 的 $i$ 越来越多， $x$ 的系数就越来越大；满足 $p_i-d_i>x$ 的 $i$ 越来越少， $x$ 的系数也越来越大(因为 $x$ 的系数为负数)。而 $p_i+d_i, p_i-d_i$ 都是常数，所以函数的图像是先朝下再朝上，为单谷函数，函数的最低点就是答案。

## 代码如下:
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define N 200005
int n,p[N],w[N],d[N],ans=1e18;
int work(int x){
	int ans=0;
	for(int i=1;i<=n;i++){
		if(p[i]+d[i]<x) ans+=w[i]*(x-p[i]-d[i]);
		if(p[i]-d[i]>x) ans+=w[i]*(p[i]-d[i]-x);
	}
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i]>>w[i]>>d[i];
	int l=-1e9,r=1e9;
	while(l<=r){
		int lmid=(2*l+r)/3,rmid=(l+2*r)/3;
		int lans=work(lmid),rans=work(rmid);
		if(lans<=rans){
			ans=min(ans,lans);
			r=rmid-1;
		}
		if(lans>rans){
			ans=min(ans,rans);
			l=lmid+1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CmsMartin (赞：3)

[http://www.cmsblog.top/archives/ccc2021s3lunchconcert](更好的阅读体验)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/P9025)

## 思路

题目可以表示为求：

$$
\min\sum_{i=1}^nw_i \times\max(|c - p_i| - d_i,0)
$$

发现对于每一个人，$c$ 移动时的贡献与 $w_i$ 相关。

后面的 $\max(|c - p_i| - d_i,0)$ 其实可以分成两种断点：

+ $c-p_i$ 正负性断点;

+ $\max$ 为 $0$ 断点。

那么动态维护断点答案取最小值就行了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
typedef long long ll;

int n;

struct _ {
	int type; //绝对值分界(1) / max为0(-1) 点
	int pos, id;
};
bool operator < (_ a, _ b) {
	return a.pos < b.pos;
}
struct __ {
	int p, w, d;
} a[MAXN];
vector<_> qwq;
void Add(int a, int b, int c) {
	qwq.push_back({b, a, c});
}

bool Max0[MAXN];
int Belong[MAXN];

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int p, w, d;
		cin >> p >> w >> d;
		Add(p - d, 2, i);
		Add(p, 1, i);
		Add(p + d, 2, i);
		a[i] = {p, w, d};
	}
	stable_sort(qwq.begin(), qwq.end());
	ll c = qwq[0].pos - 1, res = 0, Ans = LLONG_MAX;
	ll Sumw = 0, _Sumw = 0;
	for (int i = 1; i <= n; i++) {
		res += max(abs(c - a[i].p) - a[i].d, 0ll) * a[i].w;
		if (c - a[i].p < 0) Sumw += a[i].w, Belong[i] = 1;
		else _Sumw += a[i].w, Belong[i] = -1;
	}
	Ans = min(Ans, res);
	for (int i = 0; i < qwq.size(); i++) {
		if (qwq[i].type == 1) {
			Belong[qwq[i].id] ^= 1;
		} else if (qwq[i].type == 2) {
			Max0[qwq[i].id] ^= 1;
			if (Max0[qwq[i].id]) {
				if (Belong[qwq[i].id] == 1) 
					Sumw -= a[qwq[i].id].w;
				else
					_Sumw -= a[qwq[i].id].w;
				if (i == 0) res -= a[qwq[i].id].w * (abs(qwq[i].pos - 1 - a[qwq[i].id].p) - a[qwq[i].id].d); 
				else res -= a[qwq[i].id].w * (abs(qwq[i - 1].pos - a[qwq[i].id].p) - a[qwq[i].id].d); 
			} else {
				if (i == 0) res = res + _Sumw - Sumw; 
				else res = res + (_Sumw - Sumw) * (qwq[i].pos - qwq[i - 1].pos);
				if (Belong[qwq[i].id] == 1) 
					Sumw += a[qwq[i].id].w;
				else
					_Sumw += a[qwq[i].id].w;
				goto End;
			}
		}
		if (i == 0) res = res + _Sumw - Sumw; 
		else res = res + (_Sumw - Sumw) * (qwq[i].pos - qwq[i - 1].pos);
		End:;
		Ans= min(Ans, res);
	}
	cout << Ans << endl;
	return 0;
}
```

---

## 作者：yzh_Error404 (赞：3)

理性思考一下，这个距离和应当是一个单峰函数，所以我们可以用三分。

证明如下：

若当前位置为点 $x$，则当前的距离之和为 $\sum\limits_{i=1}^{n}w_i\times\max(0,|x-p_i|-d_i)$。

考虑把它分成两块：左边的和右边的。

则 $f(x)=\sum\limits_{p_i\lt x}w_i\times\max(0,x-p_i-d_i)+\sum\limits_{p_i>x}\times\max(0,p_i-x-d_i)$。

当 $x$ 在某两个点之间移动时（且不进入 $d$ 的范围），左侧和右侧相加或减的距离和是不变的，所以可以看做一个一次函数。

当 $x$ 向右走一步，处于原来的右侧点和右侧点右边的点中间时，左侧的距离和变大，右侧的距离和变小，所以相较于原来的函数斜率变大了。

在最左侧的时候，左半边的距离和为 $0$，所以斜率是负的，在不断向右走的过程中，斜率不断变大，直到最后右半边的距离和为 $0$，将这些一次函数首尾相接，可以发现是一个下凸的单峰函数。

三分板子大家应该都会吧。

代码实现：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
int n;
int p[MAXN],w[MAXN],d[MAXN];
int minn=0x7f7f7f7f7f7f7f7f,maxn=0;
inline int check(int x)
{
    int now=0;
    for(register int i=1;i<=n;i++)
    {
        int dis=abs(x-p[i]);
        if(dis<=d[i])now+=0;
        else now+=(dis-d[i])*w[i];
    }
    return now;
}
signed main()
{
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++)
    {
        scanf("%lld%lld%lld",&p[i],&w[i],&d[i]);
        minn=min(minn,p[i]);
        maxn=max(maxn,p[i]);
    }    
    int l=minn-1,r=maxn+1;
    while(l<r-1)
    {
        int mid=(l+r)>>1;
        int mmid=(mid+r)>>1;
        if(check(mid)>check(mmid))l=mid;
        else r=mmid;
    }
    int ans=min(check(l),check(r));
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：InversionShadow (赞：2)

## P9025 [CCC2021 S3] Lunch Concert 题解

以下思路由不知名的机房大佬提供。

将每个⼈看作线段 $[P_i - D_i, P_i + D_i]$，那么⼀个⼈需要移动当且仅当 $c < P_i - D_i$ 或 $c > P_i - D_i$。因为一个人可以听到的声音范围在 $[P_i - D_i,P_i + D_i]$ 这个区间内。我们设 $f(c)$ 表⽰选在坐标 $c$ 的答案，则 $f(c)$ 是⼀个分段函数，断点在线段端点。

很明显这是⼀个⼀次函数，于是最值⼀定在线段端点上。

尝试枚举每⼀个线段端点，直接暴⼒判断就能获得 $80$ 分。

优化判断的过程，发现 $f(c) = \sum\limits_{P_i + D_i < c}W_i \times (c - P_i - D_i) + \sum\limits_{P_i - D_i > c}W_i \times (P_i - D_i - c)$。第一个算式是在 $c$ 左边的人一共要花的时间，第二个则是在右边的人一共要花费的时间和。

所以可以⼆分寻找答案，时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$。

不过有些大佬场切用的是三分。

放一下三分的代码：

```cpp

#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 2e6 + 100;

int n, l = LLONG_MAX, r, ans;

struct Node{
  int p, w, d;
} a[MAXN];

int f(int x) {
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i].p - a[i].d <= x && x <= a[i].p + a[i].d) { // 在这个区间的人不需要移动
      continue;
    }
    if (x < a[i].p - a[i].d) { // 左边的人
      sum += (a[i].p - a[i].d - x) * a[i].w;
    } else { // 右边的人
      sum += (x - a[i].p - a[i].d) * a[i].w;
    }
  }
  return sum;
}

void find() { // 不会可以参考 https://zhuanlan.zhihu.com/p/100617613
  while (l + 2 < r) {
    int mid = (r - l) / 3;
    int m1 = l + mid;
    int m2 = m1 + mid;
    if (f(m1) <= f(m2)) {
      r = m2;
    } else {
      l = m1;
    }
  }
}

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].p >> a[i].w >> a[i].d;
    l = min(l, a[i].p - a[i].d); // 这个人可以听见的范围
    r = max(r, a[i].p + a[i].d);
  }
  find();
  //cout << l << ' ' << r << endl;
  cout << min({f(l), f(l + 1), f(r)});
  return 0;
}

```

---

## 作者：nr0728 (赞：2)

### 前言

模拟赛有这道题，赛后 A 了，写篇题解纪念一下。

### 思路

考虑对 $c$ 模拟退火。

> **什么是模拟退火？**
> 
> 模拟退火是一种随机化算法。当一个问题的方案数量极大（甚至是无穷的）而且不是一个单峰函数时，我们常使用模拟退火求解。

> **模拟退火如何实现？**
> 
> 如果新状态的解更优则修改答案，否则以一定概率接受新状态。
> 
> 我们定义当前温度为 $T$，新状态与已知状态（由已知状态通过随机的方式得到）之间的能量（值）差为 $\Delta E$（$\Delta E\geq0$），则发生状态转移（修改最优解）的概率为：
> $$P(\Delta E)=\begin{cases}1&\text{the new status is better}\\e^{\frac{-\Delta E}{T}}&\text{otherwise}\end{cases}$$

但是，我们需要注意：

1. 最后输出的是每个人移动时间之和的最小值，而不是 $c$；
2. 退火次数太少会 WA，建议退到即将超过时限再输出。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long  // 一定要开 long long
#define re register
#define rep(i,a,b) for(re int i=(a);i<=(b);++i)
using namespace std;
// 以下是快读
template <typename T> inline void read(T &x) {
    x = 0; re char ch = getchar(); re int f = 1;
    while (!isdigit(ch) && ch ^ '-') ch = getchar();
    if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar(); x *= f;
}
// 以上是快读
int n,w[200001],d[200001],p[200001],mx=-9e18,mn=9e18,ansx,ans=9e18;
mt19937 rnd(1145141919);
int chk(int pos) // 计算当 c=pos 时，每个人移动时间之和
{
	int res=0;
	rep(i,1,n) res+=max(abs(p[i]-pos)-d[i],0ll)*w[i];
	return res;
} 
void SA() // 模拟退火
{
	double T=100000;
	int nowx=ansx,nxtx,now=ans,nxt;
	while(T>1e-3)
	{
		nxtx=nowx+((rand()*1.0/RAND_MAX)*2-1)*T*100,nxt=chk(nxtx);
		if(nxt<now) now=ans=nxt,ansx=nowx=nxtx;
		if(exp((now-nxt)*1.0/T)>rand()*1.0/RAND_MAX) now=nxt,nowx=nxtx;
		T*=.93;
	}
}
signed main()
{
	cin>>n;
	rep(i,1,n) read(p[i]),read(w[i]),read(d[i]),mx=max(mx,p[i]),mn=min(mn,p[i]);
	while(clock()*1.0/CLOCKS_PER_SEC<.95) SA();
	cout<<ans;
	return 0;
}
```

### 后记

其实不难发现答案一定是一个单峰函数，因此也可以使用爬山算法或三分求解，代码留给读者自己编写。

---

## 作者：small_john (赞：2)

## 题目大意

有 $n$ 个人，第 $i$ 个人初始在 $p_i$ 位置，能听到距离他们 $d_i$ 的位置，速度为 $w_i$ 秒每米。求一个位置使所有人靠近至能听到的时间和最小。

## 解题思路

不难发现，答案是一个单峰函数，所以考虑用三分解决这道题，每次用 $O(n)$ 统计出时间之和，所以时间复杂度为 $O(n\log n)$，可以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int n,p[N],d[N],w[N],ans = 1e18;
int f(int x)
{
	int res = 0;
	for(int i = 1;i<=n;i++)
		if(x<p[i]-d[i]) res+=(p[i]-d[i]-x)*w[i];
		else if(x>p[i]+d[i]) res+=(x-p[i]-d[i])*w[i];
	return res;
}
signed main()
{
	cin>>n;
	for(int i = 1;i<=n;i++)
		cin>>p[i]>>w[i]>>d[i];
	int l = -1e9,r = 1e9;
	while(l<=r)
	{
		int mid1 = (2*l+r)/3,mid2 = (l+2*r)/3,f1 = f(mid1),f2 = f(mid2);
		ans = min({ans,f1,f2});
		if(f1<=f2) r = mid2-1;
		else l = mid1+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：OIerBoy (赞：1)

# 分析
提供一个 $O(n)$ 的思路。
由于每一个人的听力是覆盖距离他不超过 $d_i$ 的所有点，那么我们就可以把每一个人直接看成一个线段 $[p_i-d_i,p_i+d_i]$。

我们可以简单发现，由于如果 $c$ 在 $[p_i-d_i,p_i+d_i]$ 内则第 $i$ 个人不用移动，这样就可以发现某个线段的端点一定有答案，因为当 $c$ 在端点时答案不会变劣。

如果 $c$ 不在任何线段内时则可以很好的优化答案，因为 $c$ 向左移动或向右移动可以有一边可以将答案优化，它具有一个指向性。

我们只需要将 $p_i+d_i$ 排序，再通过**前**缀和的优化来预处理 $(p_i+d_i)\times w_i$，同理将 $p_i-d_i$ 排序，再通过**后**缀和的优化来预处理 $(p_i-d_i)\times w_i$。

利用单调性就可以做出来了。
# Code
码风较丑请见谅。
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
#define Mod 1000000007
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define FO(i,j,k) for(int i=j;i;i=k)
#define PB(i) push_back(i)
#define For(i,j,k) for(long long i=j;i<=k;++i)
#define FoR(i,j,k) for(long long i=j;i<k;++i)
#define FOR(i,j,k) for(long long i=j;i>=k;--i)
using namespace std;
template <typename _Tp>void read(_Tp& first) {
	_Tp x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
	first = x * f;
}
struct P{
	int p,w,d;
}g[N];
int n,ans,Max,Min=1e18;
int l=1,r,k,sum;
vector<pair<int,int>>a;
signed main(){
	read(n);
	For(i,1,n){
		read(g[i].p),read(g[i].w),read(g[i].d);
		Max=max(Max,g[i].p);
		Min=min(Min,g[i].p-g[i].d);
		a.PB(MP(g[i].p-g[i].d,i));
		a.PB(MP(g[i].p+g[i].d,i));
	}
	sort(a.begin(),a.end());
	For(i,1,n)l=g[i].p+1;
	For(i,1,n)r-=g[i].w;
	For(i,1,n)ans+=(g[i].p-g[i].d-Min)*g[i].w;
	sum=ans;k=Min;
	Fo(v,a){
		int f=v.first;
		int s=v.second;
		if(f>Max)break;
		sum+=r*(f-k);
		r+=g[s].w;
		k=f;
		ans=min(ans,sum);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

