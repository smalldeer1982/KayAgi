# Integers Have Friends

## 题目描述

British mathematician John Littlewood once said about Indian mathematician Srinivasa Ramanujan that "every positive integer was one of his personal friends."

It turns out that positive integers can also be friends with each other! You are given an array $ a $ of distinct positive integers.

Define a subarray $ a_i, a_{i+1}, \ldots, a_j $ to be a friend group if and only if there exists an integer $ m \ge 2 $ such that $ a_i \bmod m = a_{i+1} \bmod m = \ldots = a_j \bmod m $ , where $ x \bmod y $ denotes the remainder when $ x $ is divided by $ y $ .

Your friend Gregor wants to know the size of the largest friend group in $ a $ .

## 说明/提示

In the first test case, the array is $ [1,5,2,4,6] $ . The largest friend group is $ [2,4,6] $ , since all those numbers are congruent to $ 0 $ modulo $ 2 $ , so $ m=2 $ .

In the second test case, the array is $ [8,2,5,10] $ . The largest friend group is $ [8,2,5] $ , since all those numbers are congruent to $ 2 $ modulo $ 3 $ , so $ m=3 $ .

In the third case, the largest friend group is $ [1000,2000] $ . There are clearly many possible values of $ m $ that work.

## 样例 #1

### 输入

```
4
5
1 5 2 4 6
4
8 2 5 10
2
1000 2000
8
465 55 3 54 234 12 45 78```

### 输出

```
3
3
2
6```

# 题解

## 作者：Prean (赞：19)

在日报上面看到的，发现 NOIP 模拟赛考过这个 trick（

首先我们把题目要求的条件这么写：
$$ a_i=x_i \times m+k $$
那么我们要找到满足条件的数组，差分后的数组一定都是 $ m $ 的倍数，换句话说差分后的 $ \gcd $ 一定大于 $ 1 $。

这里已经可以用线段树+st 表大力草了，但是显然我们并不满足于此。

我们考虑通过双指针，钦定右端点，然后移动左端点。

然后你发现不可能删掉左区间的元素，所以我们考虑用两个栈来维护这个区间。

大概就是给定了一个中点 $ mid $，然后对于 $ i \in [l,mid] $ 维护一个 $ \gcd_{k=i}^{mid}a_k $，对于 $ i \in (mid,r] $ 维护一个 $ \gcd_{k=mid+1}^i a_k $。

于是移动左端点的时候就只需要直接 check 就好了。

当 $ l > mid $ 时，令 $ mid=r $，然后重构整个左边的栈，把右边的栈清空。

可以知道每一个元素只会被加入一次和被重构一次，所以复杂度很明显是 $ O(n\log V) $ 的。
```cpp
#include<cstdio>
typedef unsigned ui;
typedef unsigned long long ull;
const ui M=2e5+5;
ui T,n;ull a[M],f[M];
inline ull gcd(const ull&a,const ull&b){
	return b?gcd(b,a%b):a;
}
signed main(){
	ui i,j,l,mid,ans;scanf("%u",&T);
	while(T--){
		scanf("%u",&n);l=mid=1;ans=0;
		for(i=1;i<=n;++i)scanf("%llu",a+i),a[i-1]=a[i-1]>a[i]?a[i-1]-a[i]:a[i]-a[i-1];
		for(i=1;i<n;++i){
			f[i]=i==1||i-1==mid?a[i]:gcd(f[i-1],a[i]);
			while(l<=mid&&gcd(f[l],f[i])==1)++l;
			if(l>mid){
				f[i]=a[mid=i];
				for(j=i-1;j>=l;--j)f[j]=gcd(a[j],f[j+1]);
				while(l<=i&&f[l]==1)++l;
			}
			if(i-l+1>ans)ans=i-l+1;
		}
		printf("%u\n",++ans);
	}
}
```

---

## 作者：HoshizoraZ (赞：18)

这题第一眼看上去，可能会有点迷茫。

但是如果做过 [CF1216D Swords](https://codeforces.com/contest/1216/problem/D) 和 [CF1547F Array Stabilization (GCD version)](https://codeforces.com/contest/1547/problem/F) 并且熟悉这类思路的话，这题就可以被迅速做完。

首先观察一下题目的要求，发现需要求序列一个最长的子区间，使得存在一个不小于 $2$ 的整数 $m$，子区间内所有数对 $m$ 取模后余数相等。

如果题目强制要求**取模后余数为** $0$（即被 $m$ 整除），这个限制就可以转化成**子区间的 $\gcd$ 大于 $1$** ，因为 $m \ge 2$。

我们希望转化成上面一个问题，即用一种办法能把同余变为整除，而这个办法就是 **作差**。

由于两个数对 $m$ 取模余数相等，作差后余数抵消为 $0$，即差 $m$ 的倍数。

那题目刚好求的是子区间，我们可以只对相邻的两数**作差**，然后在这些**差值**组成的序列找到最大的子区间，使得该区间 $\gcd$ 大于 $1$。

上述内容的求法可以**st 表 + 二分/双指针**，我在 [CF1547F 的题解](https://www.luogu.com.cn/problem/solution/CF1547F) 说得比较详细，下面说几个易错点：

- $n$ 个数只有 $n-1$ 个相邻差值，因此差值序列的最大子区间长度要 $+1$ 才是正确答案。
- 差值可能是负数，因为正负与否并不影响整除关系，负数可以直接取相反数。
- 差值绝对值为 $1$ 的时候，此时该差值代表的两个原数**不能被放入一个合法子区间**。

放上代码：

```cpp
#include <bits/stdc++.h>
#define INF 1e9
#define eps 1e-6
typedef long long ll;
using namespace std;

int t, n, ans;
ll a[200010], sub[200010], st[200010][20];

ll gcd(ll x, ll y){
    if(!y) return x;
    return gcd(y, x % y);
}
 
ll query(int i, int j){
    int k = log2(j - i + 1);
    return gcd(st[i][k], st[j - (1 << k) + 1][k]);
}

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){

	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		if(n == 1){
			puts("1");
			continue;
		}
		for(int i = 1; i < n; i++){
			sub[i] = a[i] - a[i + 1];
			if(sub[i] < 0) sub[i] = -sub[i];
		}
		n--;
		for(int i = 1; i <= n; i++)
			st[i][0] = sub[i];
		for(int j = 1; (1 << j) <= n; j++) 
            for(int i = 1; i + (1 << j) - 1 <= n; i++)
                st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        ans = 0;
		for(int i = 1, l, r; i <= n; i++){
			l = i, r = n;
			while(l < r){
				int mid = (l + r + 1) >> 1;
				if(query(i, mid) == 1) r = mid - 1;
				else l = mid;
			}
			if(sub[i] != 1) ans = max(ans, l - i + 1);	// sub[i] = 1 时不可取答案
		}
		printf("%d\n", ans + 1);
	}

	return 0;
}
```

---

## 作者：rouxQ (赞：7)

一道不错的 st 表练习题。
## $\operatorname{Description}$
给定一个正整数数列 $a_1,a_2,...,a_n$，求长度最大的区间 $[i,j]$，使存在一个正整数 $m(m>1)$，满足 $a_i\equiv a_{i+1}\equiv ... \equiv a_j \pmod{m}$。

## $\operatorname{Solution}$
我们发现条件里面既不知道模数，也不知道余数，所以考虑先消掉一个未知变量。容易发现差分可以很好地消去余数，所以作差分 $b_i=a_{i+1}-a_i$，即求最长的区间 $[i,j]$，使存在正整数 $m$，满足 $\forall k\in[i,j]\cap \mathbb{N}_+$，$m|a_k$。

换种叙述，即求最长的区间 $[i,j]$，使 $\gcd(a_i,a_{i+1},...,a_j)>1$，显然符合条件的区间长度是单调的，所以可以二分答案，判断区间是否可行需要计算区间 $\gcd$，这是 st 表的经典应用。注意在差分数组上算完答案之后回到原数组时数组长度要 $+1$ 即可。

除此以外，需要特判一下 $n=2,|a_1-a_2|=1$ 的情况，这时候答案是 $1$，因为 $m$ 不能是 $1$。

看上去时间复杂度是 $O(N\log N\log \text{值域})$，但是 cf 官方题解貌似给出了复杂度更低的证明（可是现在那篇题解打不开了）。

## $\operatorname{Code}$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5, LogN = 19;
ll st[20][N], Log[N], a[N];int n, m;
ll gcd(ll x, ll y){return y == 0 ? x : gcd(y, x % y);}
bool work(int len){
    for (int i = 1; i <= m - len + 1; i++){
        int l = i, r = i + len - 1;
        int s = Log[len];
        if (gcd(st[s][l], st[s][r - (1 << s) + 1]) > 1)return 1;
    }
    return 0;
}
int main (){
    int T;
    ios::sync_with_stdio(false);
    cin >> T;
    for (int i = 2; i <= 2e5; i++)
        Log[i] = Log[i / 2] + 1;
    while(T--){
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        if (n == 2 && abs(a[1] - a[2]) == 1){
            cout << 1 << endl;
            continue;
        }
        m = n - 1;
        for (int i = 1; i < n; i++) 
            st[0][i] = abs(a[i] - a[i + 1]);//注意这里要加绝对值，不然有负数的情况下gcd可能有问题。
        st[0][n] = 1;
        for (int i = 1; i <= LogN; i++)
            for (int j = 1; j + (1 << i) - 1 <= m; j++)
                st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        int l = 1, r = m, mid;
        while(l <= r){
            mid = l + r >> 1;
            if (work(mid))l = mid + 1;
            else r = mid - 1;
        }
        cout << l << endl;
    }
    return 0;
}
```

---

## 作者：Gokix (赞：4)

[CF1548B](https://www.luogu.com.cn/problem/CF1548B)

我当时离正解只差一点……

------------

同余问题并不好解决，考虑转化。

**引理**：若 $a \mod m=b \mod m$，则 $\operatorname{abs}(a-b)\mid m$。

正确性显然。

我们对原数组 $a$ 前后两项作差并取绝对值，得到一个新数组 $b$。即 $b_i=\operatorname{abs}(a_i-a_{i+1})$。

如此以来，若 $a_l,a_{l+1},...,a_{r}$ 是好的，则 $\exists m > 1,m \mid b_l,m \mid b_{l+1},...,m \mid b_{r-1}$。

找一堆数的一个大于 1 的公共因子听起来好像并不好直接求，但注意到我们并不需要管 $m$ 到底是几，只要有就行因此我们就钦定 $m$ 是这些数的 $\gcd$。用线段树或 ST 表维护区间 $\gcd$（建议用 ST 表，不仅少一个 $\log$，还能规避一些特判）。寻找答案的时候枚举区间右端点，左端点一直加（注意左端点不必每次从 1 开始，从上一次开始就行）直至区间 $\gcd>1$，更新答案。

最后注意一点，如果你像本题解写了线段树，注意**特判 $n=1$** ! 不然由于 $b$ 比 $a$ 少一个数，线段树建树的时候就会 `build(1,0,1)`，直接暴毙。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;

long long T,n;
long long a[200010],b[200010];

struct seg{
	long long sum;
}t[800010];
long long gcd(long long aa,long long bb){
	if(bb==0) return(aa);
	return gcd(bb,aa%bb);
}
void refresh(long long u){
	long long ls=u<<1,rs=u<<1|1;
	t[u].sum=gcd(t[ls].sum,t[rs].sum);
}
void build(long long l,long long r,long long u){
	long long ls=u<<1,rs=u<<1|1,mid;
	if(l==r){
		t[u].sum=b[l];
		return;
	}
	mid=(l+r)>>1;
	build(l,mid,ls);
	build(mid+1,r,rs);
	refresh(u);
}
long long query(long long l,long long r,long long u,long long x,long long y){
	long long ls=u<<1,rs=u<<1|1,mid;
    long long ans=0;
	if(x<=l && r<=y)
		return t[u].sum;
	mid=(l+r)>>1;
	if(x<=mid)
		ans=gcd(ans,query(l,mid,ls,x,y));
	if(mid+1<=y)
		ans=gcd(ans,query(mid+1,r,rs,x,y));
	refresh(u);
	return ans;
}
void init(){
    long long i;
    for(i=0;i<=n+1;i++) b[i]=0;
    for(i=0;i<=4*n+1;i++) t[i].sum=0;
}

int main(){
    long long i,j,u,v,ans;
    cin>>T;
    while(T--){
        scanf("%lld",&n);
        init();
        for(i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(i=1;i<n;i++) b[i]=abs(a[i+1]-a[i]);
        if(n==1){
            printf("1\n");
            continue;
        }
        ans=1;
        build(1,n-1,1);
        j=1;
        for(i=1;i<n;i++){
            while(j<=i && query(1,n-1,1,j,i)==1) j++;
            ans=max(ans,i-j+2);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1548B)

很多题解都是一只 $\log$ 的，我来提供一种两只 $\log$ 的不用动脑的解法。
## 思路
我们先思考 $a_i \equiv k\pmod m,m \ge 2$，是不是等价于 $\gcd(|a_{l+1}-a_l|,...,|a_r-a_{r-1}|)=m \ge 2$？这个很好证明，留给各位读者自行完成。

接下来，我们发现这个答案显然具有单调性，具体说来，长度小于等于最大值肯定有某个区间满足要求，长度大于最大值肯定没有某个区间满足要求，所以我们可以二分。

我们二分出来了一个长度，判断的时候就枚举左端点，用 $\verb!ST!$ 表维护一下 $\gcd$ 就好了。

时间复杂度 $O(n \log^2n)$。
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=2e5+10;
int a[N],f[N][30],n;
inline int query(int x,int l){
    int ans=0;
    for (int i=18;~i;--i)
        if (l>=(1LL<<i)){
            l-=(1LL<<i);
            ans=__gcd(ans,f[x][i]);
            x+=(1LL<<i);
        }
    return ans;
}
inline bool check(int l){
    for (int i=1;i<=n-l+1;++i)
        if (query(i+1,l-1)>1) return 1;
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int T;cin>>T;
    while (T--){
        cin>>n;
        for (int i=1;i<=n;++i){
            cin>>a[i];
            if (i>1) f[i][0]=abs(a[i]-a[i-1]);
        }
        for (int j=1;(1LL<<j)<=n;++j)
            for (int i=2;i+(1LL<<(j-1))<=n;++i)
                f[i][j]=__gcd(f[i][j-1],f[i+(1LL<<(j-1))][j-1]);//ST 表预处理
        int l=1,r=n;
        while (l<r){
            if (l+1==r){
                if (check(r)) l=r;
                break;
            }//边界特判
            int mid=(l+r)>>1;
            if (check(mid)) l=mid;
            else r=mid-1;
        }
        cout<<l<<'\n';
    }
    return 0;
}

```


---

## 作者：XL4453 (赞：2)

### 解题思路:

遇事不决想差分。

初步转换原问题，可以得到：对于这其中所有的 $a_i$ 满足 $a_i-k\bmod  m=0$，其中 $m\ge 2$。

这里的处理难点就是 $k$ 不方便找出，考虑整个数组作差，这样无论 $k$ 取什么值，都有原命题的一个充分必要条件：$a_i\equiv a_{i+1}\pmod m$，问题转化为差分数组（不妨记作 $d$）中最长的一段 $\gcd_{i=l}^{r}(d_i) \ge 2$。

这个问题比较经典了，直接 ST 表预处理出区间 $\gcd$，然后双指针判断即可，复杂度 $O(n\log n)$。

---

注意差分后的数组的位置和原数组不太一样。

---
### 代码：

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
#define int long long
int T,n,l,r,a[200005],f[25][200005],ans;
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int query(int l,int r){
	int k=log2(r-l+1);
	return gcd(f[k][l],f[k][r-(1<<k)+1]);
}
int max(int a,int b){
	if(a<b)return b;
	return a;
}
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		
		for(int i=1;i<=n;i++){
			scanf("%I64d",&a[i]);
			f[0][i]=abs(a[i]-a[i-1]);
		}
		if(n==1){printf("1\n");continue;}
		for(int i=1;i<=20;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
		f[i][j]=gcd(f[i-1][j],f[i-1][j+(1<<(i-1))]);
		l=1;r=2;ans=0;
		while(r<=n){
			while(l<r&&query(l+1,r)<2)l++;
			ans=max(ans,r-l+1);
			r++;
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
```


---

## 作者：liangbowen (赞：1)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1548B)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1548b)

做法：ST 表加尺取。

## 思路

看到同余，立刻想到**作差**。我们建立差分数组 $c_i = |a_i - a_{i-1}|$，注意取了绝对值。

此时，我们只需在 $c_i$ 中寻找最长区间 $\left[l, r\right]$，使得 $\gcd(c_l, c_{l+1}, \cdots, c_r) > 1$。

这东西显然能用 ST 表维护。代码是模板，不需解释。

```cpp
typedef long long LL;
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x%y);}
struct ST
{
	LL dp[N][20];
	void build()
	{
		for (int i = 1; i <= n; i++) dp[i][0] = c[i]; //c 数组是差分数组
		int k = log2(n);
		for (int j = 1; j <= k; j++)
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				dp[i][j] = gcd(dp[i][j-1], dp[i + (1 << (j-1))][j - 1]);
	}
	LL query(int l, int r)
	{
		int k = log2(r - l + 1);
		return gcd(dp[l][k], dp[r - (1 << k) + 1][k]);
	}
	
}st;
```

然后就是简单的尺取了，依次枚举右端点并更新左端点。

```cpp
bool chk(int l, int r) {return st.query(l, r) > 1;}
int zlttql() //尺取，顺便膜拜神仙 zlt
{
	int maxn = 0;
	for (int l = 1, r = 1; r <= n; r++)
	{
		for (; l < r && !chk(l+1, r); l++);
		maxn = max(maxn, r - l + 1);
	}
	return maxn;
}
```

最后输出答案就完成了。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define endl putchar('\n')
#define space putchar(' ')
using namespace std;
typedef long long LL;
LL read()
{
	char op = getchar(); LL x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
const int N = 2e5 + 5;
LL a[N], c[N]; //c:差分 
int n;
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x%y);}
struct ST
{
	LL dp[N][20];
	void build()
	{
		for (int i = 1; i <= n; i++) dp[i][0] = c[i];
		int k = log2(n);
		for (int j = 1; j <= k; j++)
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				dp[i][j] = gcd(dp[i][j-1], dp[i + (1 << (j-1))][j - 1]);
	}
	LL query(int l, int r)
	{
		int k = log2(r - l + 1);
		return gcd(dp[l][k], dp[r - (1 << k) + 1][k]);
	}
	
}st;
bool chk(int l, int r) {return st.query(l, r) > 1;}
int zlttql() //尺取 
{
	int maxn = 0;
	for (int l = 1, r = 1; r <= n; r++)
	{
		for (; l < r && !chk(l+1, r); l++);
		maxn = max(maxn, r - l + 1);
	}
	return maxn;
}
int main()
{
    int T = read();
    while (T--)
    {
     	n = read();
        for (int i = 1; i <= n; i++) a[i] = read(), c[i] = abs(a[i] - a[i-1]);
        st.build();
        //差分后，需满足：一段区间 gcd > 1
        write(zlttql()), endl;
    }
	return 0;
}
```

希望能帮助到大家！

---

## 作者：dd_d (赞：1)

## Solution  
先考虑仅有 $2$ 个数 $x$ 和 $y$ 的情况。  
若 $x$ 和 $y$ 在 $ \bmod\ m$ 的意义下相等，容易证明，$m$ 一定能整除 $x-y$。  
考虑二分。  
记区间的左端点为 $l$，右端点为 $r$，显然，若固定了 $l$，这段区间的 $\gcd$ 一定随着 $r$ 的增加单调递减。  
那么对数组进行差分，用 ST 表来维护差分数组的 $gcd$ 即可。  
时间复杂度 $O(n \log n)$。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=2e5+10;
int Gcd[N][20],n,m,T,l,r,ans,a[N];
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
int Query(int l,int r)
{
    int k=log2(r-l+1); 
    return gcd(Gcd[l][k],Gcd[r-(1<<k)+1][k]);
}
signed main()
{
    T=read();
    while (T--)
	{
    	n=read(); l=0; r=0;
    	for(int i=1;i<=n;i++) 
		{
			int x=read();
			r=x;
			Gcd[i-1][0]=abs(r-l);
			l=x;
		}
		Gcd[n][0]=1;
    	for(int j=1;j<=19;j++)
       		for(int i=1;i+(1<<(j))-1<=n;i++)
            	Gcd[i][j]=gcd(Gcd[i][j-1],Gcd[i+(1<<(j-1))][j-1]);
      	ans=0;
      	for (int i=1;i<n;i++)
      	{
      		l=i; r=n-1;
      		while (l<=r)
      		{
      			int mid=l+(r-l)/2;
      			int x=Query(i,mid);
      			if (x!=1)
      			{
      				ans=max(ans,mid-i+1);
      				l=mid+1;
				}
			else r=mid-1;	
			}
		}
		writeln(ans+1);
    }
}


```


---

## 作者：NXYorz (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1548B)

-------
### 题目大意
给定数组 $a_n$，求最长区间满足$a_l \mod m=a_{l+1}\mod m=...a_r\mod m$，其中 $m\ge 2$。

-------
### 分析

令 $a_l \mod m=a_{l+1}\mod m=...a_r\mod m = x$。那么就有：

- $a_l - x = k_l\times m $。
- $a_{l+1} - x = k_{l+1}\times m $。
- $a_r - x = k_r\times m $。

也就是说 $a_l,a_{l+1}...a_r$ 之间相差是 $m$ 的整数倍。

那么就可以将原数列做差得到一个新的数列，在新数列中符合条件的区间的 $\gcd$ 一定不为 $1$。

因此可以考虑枚举每一个位置进行二分，用线段树维护一下就好啦。

复杂度 $O(N + N\log{N}\log{N})$

---------
### $\texttt{Code}$
```cpp
#include<cstdio>

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int t,n;
ll a[N],d[N];

ll gcd(ll a , ll b)
{return b ? gcd(b , a % b) : a;}

inline int max(int x , int y)
{return x > y ? x : y;}

inline ll abs(ll x)
{return x > 0 ? x : -x;}

struct El
{
    int l;
    int r;
    ll w;
};
struct SigmenT
{
    El t[N << 2];

    void Pushup(int p)
    {t[p].w = gcd(t[p << 1].w , t[p << 1 | 1].w);}

    void Build(int p , int l , int r)
    {
        t[p].l = l; t[p].r = r;
        if(l >= r) {t[p].w = d[l];return;}
        int mid = (l + r) >> 1;
        Build(p << 1 , l , mid); Build(p << 1 | 1 , mid + 1 , r);
        Pushup(p); return;
    }

    ll Query(int p , int l , int r)
    {
        if(l <= t[p].l && r >= t[p].r) return t[p].w;
        ll ans = 0; ll mid = (t[p].l + t[p].r) >> 1;
        if(l <= mid) ans = gcd(Query(p << 1 , l , r) , ans);
        if(r > mid) ans = gcd(Query(p << 1 | 1 , l , r) , ans);
        return ans;
    }
}tr;

void work()
{
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
    for(int i = 1; i < n; i++) d[i] = abs(a[i + 1] - a[i]);
    tr.Build(1 , 1 , n - 1); int ans = 0;
    for(int i = 1; i < n; i++)
    {
        int l = i; int r = n;
        while(l < r)
        {
            int mid = (l + r) >> 1;
            ll g = tr.Query(1 , i , mid);
            if(g == 1) r = mid;
            else l = mid + 1 , ans = max(ans , mid - i + 1);
        }
    }
    printf("%d\n",ans + 1);
}

int main()
{
  //  freopen("aa.in","r",stdin);
    scanf("%d",&t);
    while(t--)
        work();
}
```

---

## 作者：Inui_Sana (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1548B)

解题思路：二分+ST 表

如果有两个数 $a$ 和 $b$，$a\equiv k\pmod{m}$，$b\equiv k\pmod{m}$，那么 $m\mid \operatorname{abs}(a-b)$。

那么易得结论：如果一个区间满足要求，那么 $\gcd\limits_{l}^{r-1}(\operatorname{abs}(a_i-a_{i-1})) \neq 1$（默认 $\gcd(x,0)=x$）。

二分答案区间长度，用 ST 表维护即可。

要特别注意的是，因为相邻两数可能相等，所以要特判有 $0$ 的情况。

code：

```cpp
int n,m,pre[20],lg[maxn];
ll e[maxn],st[maxn][20];
ll gcd(ll a,ll b){return a%b?gcd(b,a%b):b;}//值得一提的是，不知道为什么__gcd总是炸，所以建议手写（这个写得有点奇怪）
bool check(int len){
	int k=lg[len];
	for(int l=1;l+len-1<n;l++){
		int r=l+len-1;
		if((st[l][k]==0||st[r-pre[k]+1][k]==0)&&max(st[l][k],st[r-pre[k]+1][k])!=1||gcd(st[l][k],st[r-pre[k]+1][k])>=2ll)return true;//又臭又长的特判
	}
	return false;
}
void solve(){
	scanf("%lld",&n);
	pre[0]=1;
	for(int i=1;1<<i-1<=n;i++)pre[i]=pre[i-1]<<1;
	for(int i=1;i<=n;i++)lg[i]=log2(i);
	for(int i=1;i<=n;i++)scanf("%lld",&e[i]);
	for(int i=1;i<n;i++)st[i][0]=abs(e[i+1]-e[i]);
	for(int j=1;pre[j]<n;j++){
		for(int i=1;i+pre[j]-1<n;i++){
			if(st[i][j-1]==0||st[i+pre[j-1]][j-1]==0)st[i][j]=max(st[i][j-1],st[i+pre[j-1]][j-1]);//特判2
			else st[i][j]=gcd(st[i][j-1],st[i+pre[j-1]][j-1]);
		}
	}
	int l=1,r=n-1,ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	printf("%lld\n",ans+1);
}

---

## 作者：registerGen (赞：0)

如果一个数组是合法的，那么这个数组的差分数组的 $\gcd$ 要 $\gt 1$。

先求出 $a$ 的差分数组 $d$。对于每个 $l\in[1,n-1]$，我们要找到最大的 $r$，使得 $\gcd_{i=l}^rd_i\gt 1$。

倍增实现即可。具体细节见代码：

```cpp
typedef long long ll;

const int N=2e5;
const int LOGN=20;

int n;
ll a[N+10],d[N+10],f[N+10][LOGN+5]; // f 是倍增数组

ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}

void mian(){
	for(int i=1;i<=n+1;i++){
		a[i]=d[i]=0;
		for(int j=0;j<=LOGN;j++)
			f[i][j]=0;
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	for(int i=1;i<=n;i++)
		d[i]=std::abs(a[i+1]-a[i]),f[i][0]=d[i];
	for(int j=1;j<=LOGN;j++)
		for(int i=1;i+(1<<(j-1))<=n;i++)
			f[i][j]=gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	int ans=1;
	for(int i=1;i<=n;i++){
		ll now=d[i];
		int r=i;
		if(now<=1)continue;
		for(int j=LOGN;~j;j--) // 倍增
			if(r+(1<<j)<=n&&f[r][j]>1&&gcd(now,f[r][j])>1)now=gcd(now,f[r][j]),r+=(1<<j); // 如果这个新的 r 能使当前的 gcd > 1，就更新 r
		ans=std::max(ans,r-i+1);
	}
	printf("%d\n",ans);
}
```

---

## 作者：Retired_lvmao (赞：0)

### 题意

给定一个长度为 $n$ 的正整数序列 $a_1,a_2\dots a_n$，求一个最长的长度使得存在一个对应长度的子区间 $[L,R]$ 满足 $a_L\bmod m= a_{L+1}\mod m=\dots =a_{R}\bmod m$，其中 $m\not= 1$。

### 题解

先考虑只有两个数。让两个数 $x\bmod m=y\bmod m$当且仅当 $m$ 是 $|x-y|$ 的因数。

将这个结论推导至多个数，让多个数对 $m$ 取模的结果一样，则 $m$ 为任意两个相邻的数差的公因数。

因此只需要二分答案查询长度，再使用 ST 求区间 $\gcd$ 即可，复杂度 $O(n\log^2n )$。

注意这个做法需要特判 $n=1$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000010];
int g[500010][21];
int n,t;
void init()
{
	for(int i=1;i<=n;i++)
		g[i][0]=a[i];
 	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i<=n;i++)
			g[i][j]=__gcd(g[i][j-1],g[i+(1<<j-1)][j-1]);
}
int query(int l,int r)
{
	int k=0;
	while((1<<k+1)<=r-l+1)
		k++;
	return __gcd(g[l][k],g[r-(1<<k)+1][k]);
}
bool check(int x)
{
	for(int i=1;i<=n-x+1;i++)
		if(query(i,i+x-1)!=1)
			return 1;
	return 0;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		if(n==1)
		{
			puts("1");
			continue;
		}
		n--;
		for(int i=1;i<=n;i++)
			a[i]=abs(a[i]-a[i+1]);
		init();
		int l=1,r=n,ans=0;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid))
				l=mid+1,ans=mid;
			else
				r=mid-1;
		}
		printf("%lld\n",ans+1);
	}
}
```

---

