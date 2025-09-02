# Count Subrectangles

## 题目描述

You are given an array $ a $ of length $ n $ and array $ b $ of length $ m $ both consisting of only integers $ 0 $ and $ 1 $ . Consider a matrix $ c $ of size $ n \times m $ formed by following rule: $ c_{i, j} = a_i \cdot b_j $ (i.e. $ a_i $ multiplied by $ b_j $ ). It's easy to see that $ c $ consists of only zeroes and ones too.

How many subrectangles of size (area) $ k $ consisting only of ones are there in $ c $ ?

A subrectangle is an intersection of a consecutive (subsequent) segment of rows and a consecutive (subsequent) segment of columns. I.e. consider four integers $ x_1, x_2, y_1, y_2 $ ( $ 1 \le x_1 \le x_2 \le n $ , $ 1 \le y_1 \le y_2 \le m $ ) a subrectangle $ c[x_1 \dots x_2][y_1 \dots y_2] $ is an intersection of the rows $ x_1, x_1+1, x_1+2, \dots, x_2 $ and the columns $ y_1, y_1+1, y_1+2, \dots, y_2 $ .

The size (area) of a subrectangle is the total number of cells in it.

## 说明/提示

In first example matrix $ c $ is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1323B/e15101752e569619838a0f9859eb0706f1619714.png)There are $ 4 $ subrectangles of size $ 2 $ consisting of only ones in it:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1323B/980c0eb5f8be8a323efa10a6215da0fcea6f84eb.png)In second example matrix $ c $ is:

 ![](https://espresso.codeforces.com/3109dd0bc266b26bdd9a8a0f1f6c5f6f8cd64093.png)

## 样例 #1

### 输入

```
3 3 2
1 0 1
1 1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
3 5 4
1 1 1
1 1 1 1 1```

### 输出

```
14```

# 题解

## 作者：yunsenl (赞：3)

观察题目可知，题意就是求a序列的一段长为x连续1区间与b序列的一段长为y连续1区间的个数，且$x \times y = k $

所以可以计算出a序列中连续为1的区间长度，b区间连续为1的区间长度，然后各排一次序。

在处理a的连续1区间时，去一下重，方便我们后面枚举x。

枚举a区间中长度为1的区间长度x，然后去b区间二分查找第一个y满足$x \times y = k$，那么当前x对答案的贡献就是 ： a序列中区间长度为x的区间个数 $ \times $ b序列中长度大于等于y的区间个数。

```
#include <cstdio>
#include <algorithm>
#define LL long long
#define gc() getchar()
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
const int N = 4e5 + 5;
LL n, m, k, cnt, a[N], b[N], s1[N], vis[N], val[N];
LL c[N];

struct S {
	int pre, id;	
}s[N];

inline int read() {
	char ch = gc();
	int ans = 0;
	while (ch > '9' || ch < '0') ch = gc();
	while (ch >= '0' && ch <= '9') ans = (ans << 1) + (ans << 3) + ch - '0', ch = gc();
	return ans;
}

inline bool cmp(S x, S y) {
	return x.pre < y.pre;	
}

inline LL search(LL x) {
	int left = 1, right = m, ret = 0;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (s[mid].pre >= x) ret = mid, right = mid - 1;
		else left = mid + 1;
	}
	return ret ? (m - ret + 1) : 0;
}

int main() {
	n = read(), m = read(), k = read();
	rep(i, 1, n) {
		a[i] = read();
		if (a[i]) {
			s1[i] = s1[i - 1] + a[i];
			if (!vis[s1[i]]) val[++cnt] = s1[i];
			++vis[s1[i]];
		}
	} 
	rep(i, 1, m) {
		b[i] = read();
		s[i].id = i; s[i].pre = b[i - 1] && b[i] ? b[i] + s[i - 1].pre : b[i];
	}
	sort(s + 1, s + 1 + m, cmp);
	sort(s1 + 1, s1 + 1 + cnt);
	rep(i, 1, cnt) c[i] = c[i - 1] + vis[val[i]];
	LL ans = 0; LL tot = c[val[cnt]];
	rep(i, 1, cnt) if (val[i] && k % val[i] == 0) ans += (1LL * (tot - c[i - 1])) * search(k / val[i]);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：TEoS (赞：3)

**题意**

通过两个仅由$0$和$1$构成的数列$a,b$描述一个矩阵$c$，$c_{i,j}=a_i⋅b_j$，求这个矩阵中仅由$1$构成的大小为$k$的子矩阵数

**分析**

可以想到将一个矩阵分成行和列来看，例如$k=i·j$，行上有$x$种$i$的情况，列上有$y$种$j$的情况，则这可以构成$x·y$种情况。

因此可以分别统计行上和列上每种长度的情况数，最后统计即可。

**实现**

情况可以暴力地统计，但完全的暴力可能过不了。在统计列的情况的时候，若当前统计到$z$的情况，可以从$z-1$的情况拓展而来，不需要重新暴力统计。

若$z-1$新增的情况有$f(z-1)$种，则$z$的情况为$2f(z-1)$再加上列长度为$z$的矩阵的情况。

大概要开long long 

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
const int N=4e4+100;
int n,m,la;
ll k,ans,now;
int a[N],b[N],cnt[N];
int main()
{
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(!a[i])
		{
			for(int j=1;j<=i-la-1;j++)
				cnt[j]+=i-la-j;
			la=i;
		}
	}//统计行
	for(int j=1;j<=n-la;j++)
		cnt[j]+=n+1-la-j;la=0;//统计行
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		if(b[i])
		{
			ans+=now;
			if(k%(ll)(i-la)==0 && k/(ll)(i-la)<=n)
				ans+=cnt[k/(ll)(i-la)],now+=cnt[k/(ll)(i-la)];
		}
		else
			la=i,now=0;
	}//统计列，同时统计答案
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：流绪 (赞：3)

思维题吧。首先观察发现 b 数组的一项与 a 数组的全体相乘的结果是矩阵的一行，那么子矩阵的面积应该是 a,b 数组连续的几项组成的。那么我们可以预处理 a 数组连续的一段长度，若能从 b 数组找出一段长度与其乘积为 S，则 ans++。

细节：对于每一个子段，他可以再细分乘更小的，那能分成几种呢？由于分完的必须是连续的一段，所以能分成，总长 - 小段长 +1 种。

优化上述做法，找到 a 数组每一条最长子段长后，把其能分的更小段种数记录下来，然后对 b 一样的操作，若 k%b==0 且 k/b 的值被记录过，ans+= 这个值的种数。

注意：子段长最大为 40000，注意舍去大于此的情况。

可能讲得有点乱，看代码吧，有详细注释。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mod 1e9+9
#define db() cout << 1 << endl
#define eps 0.000001
using namespace std;
int a[50000],b[50000],sum[maxn]={0};
signed main()
{
	ios::sync_with_stdio(0);
	int n,m,k;
	cin >> n >> m >> k;
	int p=0,cnt=0;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		if(a[i])
			cnt++;记录子段长度
		else//若a[i] = 0,子段达到最长
		{
			for(int j=1;j<=k&&j<=cnt;j++)//枚举子段再分的长度
				sum[j]+=cnt-j+1;//记录其有多少种
			cnt=0;//子段长归零
		}
	}
	for(int i=1;i<=cnt&&i<=k;i++)
		sum[i]+=cnt-i+1;//结束了要再做一次,末尾可能没有0
	cnt=0;
	int ans = 0;
	for(int i=1;i<=m;i++)
	{
		cin >> b[i];
		if(!b[i])//子段达到最长
		{
			for(int j=1;j<=cnt&&j<=k;j++)//枚举子段再分的种数
				if(k%j==0)//若能构成所需矩形
					if(k/j<=40000)//边长要小于40000
						ans += (cnt-j+1)*sum[k/j];
			cnt=0;				//计算面积
		}
		else
			cnt++;
	}
	for(int i=1;i<=cnt&&i<=k;i++)
		if(k%i==0)
			if(k/i<=40000)
				ans += (cnt-i+1)*sum[k/i];//同样的结束了再做一次
	cout << ans; 
	return 0;
}
```


---

## 作者：Anita_Hailey (赞：0)

## 暴力

史上最慢的题解

我考场时，暴力水过去了2333

就是一块一块检查符合的矩形就完了（笑）

但是检查的时候我加了不少优化

1. 对于区间长度做排序（笑
2. 提前处理k的因数


最后时间在最慢在982ms过去了。。
放心肯定能交过的暴力

```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int Maxn = 4e4 + 11;

int k, a[Maxn], b[Maxn], n, m, cnt, kk[Maxn], cnt1;

long long ans;

struct Node{
	int l, r;
}aa[Maxn];

bool cmp(Node a, Node b) {
	return a.r - a.l > b.r - b.l;
}

int main() {
 	// freopen("test.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);
	cin >> n >> m >> k;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= m; ++i) cin >> b[i];
	int las = 0;
	for(int i = 1; i <= n; ++i) {
		if(a[i] && !a[i + 1]) aa[++cnt].l = las + 1, aa[cnt].r = i;
		if(!a[i]) las = i; 
	}
	las = 0;
	for(int i = 1; i <= sqrt(k); ++i)
		if(k % i == 0) kk[++cnt1] = i;
	int cc = cnt1;
	for(int i = cc; i >= 1; --i)
		if(k != kk[i] * kk[i]) kk[++cnt1] = k / kk[i];
	sort(aa + 1, aa + 1 + cnt, cmp);
	for(int i = 1; i <= m; ++i) {
		if(!b[i]){
			las = i;
			continue;
		}
		if(b[i + 1]) continue;
		// las + 1 - i
		int nn = i - las;
		for(int o = 1; o <= cnt; ++o) {
			int l = aa[o].l, r = aa[o].r;
			int mm = r - l + 1;
			if(nn * mm < k) break;
			else if(nn * mm == k) ans += 1;
			else 
			for(int j = 1; j <= cnt1; ++j)
				if(nn - kk[j] + 1 > 0 && mm - k / kk[j] + 1 > 0)
					ans += (nn - kk[j] + 1) * (mm - k / kk[j] + 1);
				else if(nn - kk[j] + 1 <= 0) break;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：VinstaG173 (赞：0)

我真的不是数据结构学傻的选手，只是看见我一时半会不会的题就想数据结构（

我在考场上 naive 地用的树状数组做法。

想到肯定是由 $a$ 中连续 $i$ 个 $1$ 和 $b$ 中连续 $j$ 个 $1$ 组成的一个矩形，其中 $ij=k$。

于是我们只要统计一个数列中连续 $x$ 个 $1$ 的数量就可以了。

下面开始发傻。

我们令连续一段为 $1$ 且两端都为 $0$ 的序列长度为 $k$ 的有 $t_k$ 个，上面要求的东西显然是

$$\sum_{i=x}^n t_i(i-x+1)$$

于是我一眼看见 B 后一时没思路，于是我很 naive 地想了个树状数组。

我们对于每个数列开一个树状数组，反向一下，一个每次给第 $i$ 位加 $i$，另一个加 $1$，然后我们就得到了

$$\sum_{i=x}^n t_i \cdot i$$

和

$$\sum_{i=x}^n t_i$$

用上面减去下面的 $i-1$ 倍就完了，枚举一下 $k$ 的因数，又臭又长还带个 $\log$，被吊打。

技不如人，肝败吓疯。

Code:
```cpp
#include<cstdio>
#define ll long long
ll ans;
int n,m,K,v,s;
int c1[70003],c2[70003],c3[70003],c4[70003],l[70003];
inline void a1(int x,int k)
{
	while(x<=n)
	{
		c1[x]+=k;
		x+=l[x];
	}
}
inline int s1(int x)
{
	int t=0;
	while(x>0)
	{
		t+=c1[x];
		x-=l[x];
	}
	return t;
}
inline void a2(int x,int k)
{
	while(x<=m)
	{
		c2[x]+=k;
		x+=l[x];
	}
}
inline int s2(int x)
{
	int t=0;
	while(x>0)
	{
		t+=c2[x];
		x-=l[x];
	}
	return t;
}
inline void a3(int x,int k)
{
	while(x<=n)
	{
		c3[x]+=k;
		x+=l[x];
	}
}
inline int s3(int x)
{
	int t=0;
	while(x>0)
	{
		t+=c3[x];
		x-=l[x];
	}
	return t;
}
inline void a4(int x,int k)
{
	while(x<=m)
	{
		c4[x]+=k;
		x+=l[x];
	}
}
inline int s4(int x)
{
	int t=0;
	while(x>0)
	{
		t+=c4[x];
		x-=l[x];
	}
	return t;
}
int main()
{
	scanf(" %d %d %d",&n,&m,&K);
	for(int i=1;i<=((n>m)?n:m);++i)l[i]=i&(-i);
	for(int i=0;i<n;++i)
	{
		scanf(" %d",&v);
		if(v)++s;
		else
		{
			if(s)a1(n-s+1,1),a3(n-s+1,s);
			s=0;
		}
	}
	a1(n-s+1,1),a3(n-s+1,s);
	s=0;
	for(int i=0;i<m;++i)
	{
		scanf(" %d",&v);
		if(v)++s;
		else
		{
			if(s)a2(m-s+1,1),a4(m-s+1,s);
			s=0;
		}
	}
	a2(m-s+1,1),a4(m-s+1,s);
	for(int i=1,j;i<=n&&i*i<=K;++i)
	{
		if(K%i)continue;
		j=K/i;
		if(j<=m)
		{
			ans+=(s3(n-i+1)-1ll*(i-1)*s1(n-i+1))*(s4(m-j+1)-1ll*(j-1)*s2(m-j+1));
		}
	}
	for(int i=1,j;i<=m&&i*i<K;++i)
	{
		if(K%i)continue;
		j=K/i;
		if(j<=n)
		{
			ans+=(s4(m-i+1)-1ll*(i-1)*s2(m-i+1))*(s3(n-j+1)-1ll*(j-1)*s1(n-j+1));
		}
	}
	printf("%lld\n",ans);
	return 0;
	
}
```

---

## 作者：Meatherm (赞：0)

容易观察到 $c$ 的一个子矩阵若全为 $1$，则它对应的 $a$ 序列和 $b$ 序列中的这一段一定都是 $1$。

考虑求出 $a$ 序列和 $b$ 序列中每一段连续的 $1$。设这样的段有 $das$/$dbs$ 个，第 $i$ 段的长是 $da_i$/$db_i$。

从 $1$ 到 $n$ 枚举满足 $x|k$ 的 $x$，统计 $x\times \frac kx$ 的全 $1$ 矩阵数量。显然，这样的矩阵数量有 $\sum_{i=1}^{das} \max \{da_i-x+1,0\} \times \sum_{j=1}^{dbs} \max\{db_j-\frac kx +1,0\}$ 个。

答案即为所有合法矩阵数量的和。

看到这里可能有人要问了，从 $1$ 到 $n$ 枚举 $x$，然后统计上式的复杂度是 $O(n \times (n+m))$ 的，无法通过本题。我们选择在 $x\nmid k$ 的时候跳过，减少运行时间。由于 $[1,40000]$ 中因子最多的数只有 $96$ 个因子，则上式最多被统计 $96$ 次，复杂度可以接受。

这道题需要使用 `long long`，否则会在 #6 WA。

```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N=100010,INF=0x3f3f3f3f;
int a[N],b[N];
int n,m,k;
int da[N],das;
int db[N],dbs;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
signed main(void){
	n=read(),m=read(),k=read();
	for(rr int i=1;i<=n;++i){
		a[i]=read();
	}
	for(rr int i=1;i<=m;++i){
		b[i]=read();
	}
	bool flag=false;
	int cnt=0;
	for(rr int i=1;i<=n;++i){
		if(!a[i]){
			if(flag){
				da[++das]=cnt;
				cnt=0;
				flag=false;
			}
		}else{
			if(!flag){
				flag=true;
			}
			++cnt;
		}
	}
	if(flag){
		da[++das]=cnt;
		cnt=0;
		flag=false;
	}
	for(rr int i=1;i<=m;++i){
		if(!b[i]){
			if(flag){
				db[++dbs]=cnt;
				cnt=0;
				flag=false;
			}
		}else{
			if(!flag){
				flag=true;
			}
			++cnt;
		}
	}
	if(flag){
		db[++dbs]=cnt;
		cnt=0;
		flag=false;
	}
	int ans=0;
	for(rr int i=1;i<=n;++i){
		if(k%i)
			continue;
		int j=(k/i),cnta=0,cntb=0;
		for(rr int k=1;k<=das;++k){
			cnta+=std::max(0ll,(da[k]-i+1));
		}
		for(rr int k=1;k<=dbs;++k){
			cntb+=std::max(0ll,(db[k]-j+1));
		}
		ans+=cnta*cntb;
	} 
	printf("%I64d",ans);
	return 0;
}
/*
1 0 1 1
1 0 1 1
0 0 0 0
1 0 1 1
*/
```

### 

---

