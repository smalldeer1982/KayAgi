# Maximum Sum of Products

## 题目描述

You are given two integer arrays $ a $ and $ b $ of length $ n $ .

You can reverse at most one subarray (continuous subsegment) of the array $ a $ .

Your task is to reverse such a subarray that the sum $ \sum\limits_{i=1}^n a_i \cdot b_i $ is maximized.

## 说明/提示

In the first example, you can reverse the subarray $ [4, 5] $ . Then $ a = [2, 3, 2, 3, 1] $ and $ 2 \cdot 1 + 3 \cdot 3 + 2 \cdot 2 + 3 \cdot 4 + 1 \cdot 2 = 29 $ .

In the second example, you don't need to use the reverse operation. $ 13 \cdot 2 + 37 \cdot 4 = 174 $ .

In the third example, you can reverse the subarray $ [3, 5] $ . Then $ a = [1, 8, 3, 6, 7, 6] $ and $ 1 \cdot 5 + 8 \cdot 9 + 3 \cdot 6 + 6 \cdot 8 + 7 \cdot 8 + 6 \cdot 6 = 235 $ .

## 样例 #1

### 输入

```
5
2 3 2 1 3
1 3 2 4 2```

### 输出

```
29```

## 样例 #2

### 输入

```
2
13 37
2 4```

### 输出

```
174```

## 样例 #3

### 输入

```
6
1 8 7 6 3 6
5 9 6 8 8 6```

### 输出

```
235```

# 题解

## 作者：水沝淼㵘 (赞：12)

### 本人的第一篇题解，写的不好还请见谅!


------------


# 题意理解
给定两个序列 $a$ 和 $b$ ，将 $a$ 中的一个子序列翻转后 ( 也可以不翻转 ) ，使得 $a$，$b$ 对应项乘积和最大。即：
$$\sum_{i=1}^{n}a_i\times b_i$$


------------

# 思路
对于每一个需要枚举区间的题目，首先考虑的是 $n^2$ 直接枚举；如果数据范围较大，可以考虑通过某种性质优化为 $nlogn$ 的分治算法，比如单调性等。因为本题的范围较小 ( $n\leq 5000$ )，所以可以直接枚举每个区间。那么，如何统计每个区间的翻转后的结果呢？

# 暴力

首先，不难想到将每个区间内的元素遍历求乘积和，再与原先区间乘积和相减，这样就能找出更改后最佳的值；区间乘积和可以用前缀和 $O(1)$ 查询。核心代码如下：

```cpp
inline void query(int l,int r){
	long long res=0;
	for(int i=l;i<=r;i++) res+=a[i]*b[l+r-i];
	ans=max(ans,res-(sum[r]-sum[l-1]));
}
```
但是，这样做的时间复杂度为：
$$\sum_{i=1}^{n}i\times (n-i)$$
显然是过不了的，所以要考虑优化。

# ~~优化后的暴力~~
对于 $a$ 中的任意两个元素 $a_i$ 与 $a_j$ $(i<j)$ ，他们交换后，对整体和的改变量为：
$$a_i\times b_j+a_j\times b_i-a_i\times b_i-a_j\times b_j$$
即：
$$(a_i-a_j)\times (b_j-b_i)$$
那么我们的思路就来了：

### 每一个大区间可以视为对应的小区间加上两个端点得到，所以只需要枚举每个最小区间的位置，再逐渐向外拓展，统计改变量最大的区间即可。

最小区间有两种，分别是**单个元素**和**相邻的两个元素构成的区间**，所以只需要枚举这两种最小区间，向外拓展，就能得到正确的答案。

因为每个区间都被枚举到，向外拓展的时间复杂度为 $O(1)$ ，所以整体的时间复杂度为 $O(n^2)$ 。

# Code
```cpp
#include<cstdio>
#define re register
#define maxn(a,b) (a>b?a:b)
#define N 5010
using namespace std;

long long n,a[N],b[N];
long long tmp,sum;

//tmp记录最大的改变量，sum为初始区间乘积和 

template<typename T>
inline void read(T&x){
	x=0;re bool f=true;re char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=false;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	x=f?x:-x;
}

template<typename T>
inline void write(T x){
	if(x<0) x=~x+1,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

int main(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;i++) read(b[i]),sum+=a[i]*b[i];
	//枚举以单个元素为最小区间的所有区间 
	for(int i=1;i<=n;i++){
		long long tmp1=0;
		for(int j=i,k=i;j>=1&&k<=n;j--,k++){
			tmp1+=(a[j]-a[k])*(b[k]-b[j]);
			tmp=maxn(tmp,tmp1);
		}
	}
	//枚举以相邻的两个元素为最小区间的所有区间 
	for(int i=1;i<=n;i++){
		long long tmp2=0;
		for(int j=i,k=i+1;j>=1&&k<=n;j--,k++){
			tmp2+=(a[j]-a[k])*(b[k]-b[j]);
			tmp=maxn(tmp,tmp2);
		}
	}
	write(sum+tmp);
	return 0;
}
```


---

## 作者：RedreamMer (赞：4)

[$\Large\texttt{CF1519D}$](https://www.luogu.com.cn/problem/CF1519D)

## 题意

给定长度为 $n$ 序列 $a, b$，你可以翻转一次 $a[l,r]$，使得 $\sum_{i=1}^{i\le n} a_i\times b_i$ 最大。

## 思路

我愿称其为 div.2 最水 D 题，~~评分也只有1600~~。

枚举每一种翻转区间，但是枚举完了之后单次计算这个翻转区间是 $\mathcal O(n)$ 的，考虑优化。

容易想到，每个翻转区间的中心位置只有 $n$ 个，所以可以枚举每个翻转中心，然后 $\mathcal O(n)$ 向外扩展即可，每次更新一个区间的复杂度是 $\mathcal O(1)$ 的。

然后做一遍前缀后缀和算贡献即可。

注意：反转中心可能为下标是 $\frac{i+(i+1)}{2}$，这可以像 manacher 一样增添 $0$ 位，或者直接特判一下。

复杂度 $\mathcal O(kn^2)$ ($k$ 是一个小常数)，$\mathcal O(1e8)$ 在 CF 机子上跑的飞快。

## 代码

```cpp
int a, s1[N + 5], s2[N + 5], L[N + 5], R[N + 5];

signed main() {
	// freopen("in1.in", "r", stdin);
	// freopen("out.out", "w", stdout);
	a = read();
	rep(i, 1, a) {
		s1[i * 2 - 1] = read();
		s1[i * 2] = 0;
	}
	rep(i, 1, a) {
		s2[i * 2 - 1] = read();
		s2[i * 2] = 0;
	}
	rep(i, 1, 2 * a) L[i] = L[i - 1] + s1[i] * s2[i];
	per(i, 2 * a, 1) R[i] = R[i + 1] + s1[i] * s2[i];
	int ans = 0;
	rep(i, 1, 2 * a) {
		int tmp = 0;
		rep(j, 1, min(i, 2 * a - i + 1)) {
			int l = i - j + 1, r = i + j - 1;
			tmp += s1[l] * s2[r] + s1[r] * s2[l];
			if (l == r) tmp -= s1[l] * s2[r];
			ans = max(ans, tmp + L[l - 1] + R[r + 1]);
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：_shining (赞：3)

## 题意

这题就是让我们求操作后 $\sum_{i=1}^{n}a_i\times b_i$ 的最大值。

## 思路

先用暴力求解，直接按照题意，模拟每一次操作，用一个变量 $ans$ 记录答案，再还原回去，输出即可。枚举每一个区间为 $O(n^2)$，再区间里操作 $O(n)$，那么总共时间复杂度就是 $O(n^2\times n)=O(n^3)$，$n\le 5000$，超时。

考虑如何优化，既然要反转，那么我们每一次操作都相当于在图形上做反转，而且这个反转是根据对称轴来反转的，那么我们是不是可以枚举反转中心，然后计算反转的贡献，取最大值，就可以迎刃而解了。

接下来考虑贡献的问题，对于反转的每一组元素 $a_l$ 和 $b_r$，它们的贡献 $t=a_l\times b_r+a_r\times b_l-a_l\times b_l-a_r\times b_r$。那么我们可以像求阶乘那样一步步向外扩展，在对每一次扩展计算即可。

注意，也可以不反转，所以先求出不反转的答案，在与其他的比较，而且对于对称轴，可能长度为奇数或偶数，所以要分类讨论，代码中有解释。

总体时间复杂度为 $O(n^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 5005; 
int n;
ll ans, res;
ll a[N], b[N];
int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i]; 
	for(int i = 1; i <= n; ++i) cin >> b[i], ans += a[i] * b[i];//先计算出原先还未翻转的贡献 
	res = ans;//先求出不翻转的价值，防止后面覆盖掉 
	for(int i = 1; i <= n; ++i){//长度为奇数的区间
		int l = i, r = i; 
		ll t = res;
		while(l >= 1 && r <= n){ 
			ans = max(ans, t);
			l--, r++;//向外扩展 
			if(l < 1 || r > n) break;//超出区间就退出 
			t += a[l] * b[r] + a[r] * b[l] - a[l] * b[l] - a[r] * b[r];//计算贡献 
		}
	}
	for(int i = 1; i < n; ++i){//长度为偶数的区间 
		int l = i, r = i + 1;
		ll t = res - a[i] * b[i] - a[i + 1] * b[i + 1] + a[i] * b[i + 1] + a[i + 1] * b[i];//提前计算出[i,i+1]的答案 
		while(l >= 1 && r <= n){
			ans = max(ans, t);
			l--, r++;//向外扩展
			if(l < 1 || r > n) break;//超出区间就退出
			t += a[l] * b[r] + a[r] * b[l] - a[l] * b[l] - a[r] * b[r];//计算贡献 
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ZCETHAN (赞：3)

[传送门](http://codeforces.com/contest/1519/problem/D)

## 题目大意
给定两个序列 $a$ 和 $b$。你可以对 $a$ 的一段区间翻转，也可以不翻转，要求翻转后 $a$ 与 $b$ 对应位置之积的和最大。即求下式的值最大：
$$\sum_{i=1}^na_i\times b_j$$

## Solution
首先看到 $n\le 5000$，想到 $O(n^2)$ 做法。

可以设 $dp_{i,j}$ 表示 $a$ 翻转 $i\sim j$ 这段区间内的元素后，表达式的值是多少。那我们可以很容易得出扩展区间的转移式：

$$dp_{i,j}=dp_{i+1,j-1}-a_i\times b_i-a_j\times b_j+a_i\times b_j+a_j\times b_i$$

这比较好理解，就是左右各向外一格，就会导致最两端的元素互换，就可以用上述方式递推。

所以我们可以枚举左右端点求解。最后再 $O(n^2)$ 找最大值就可以了。

复杂度 $O(n^2)$。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5010;
ll a[MAXN],b[MAXN];
ll dp[MAXN][MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	ll t=0;
	for(int i=1;i<=n;i++)
		scanf("%lld",&b[i]),t+=a[i]*b[i];
	for(int i=1;i<=n;i++) dp[i][i]=t,dp[i+1][i]=t;//初始化
	for(int len=2;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			dp[i][j]=dp[i+1][j-1]-a[i]*b[i]-a[j]*b[j]+a[i]*b[j]+a[j]*b[i];
		}//类似区间 dp 的做法
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)
			ans=max(ans,dp[i][j]);
	}printf("%lld\n",ans);
}
//
```

---

## 作者：OIerJiang_1017 (赞：2)

## [CF1519D 题目传送门](https://www.luogu.com.cn/problem/CF1519D)

## 题目大意
给定两个长度为 $n$ 的整数数组 $a$ 和 $b$。您可以翻转数组 $a$ 中的至多一个子数组，而且是连续的子段。你的任务是翻转这样一个子数组，使得 $\sum\limits_{i = 1}^{n} a_i \cdot b_i$ 的值最大。

## 解决思路
这道题用**暴力**一次一次算，然后比较，求出最大的乘积和输出就好。通过以每个位置 $i$ 为中心，尝试交换其左右两侧的元素对，重新计算总和，并与当前最大总和 $ans$ 进行比较，不断更新 $ans$，最终得到最大的总和。~~还有一些解释在代码注释中~~详情请看代码注释。

## 代码展示
```cpp
#include <iostream>
#define ll long long
//不开long long见祖宗
using namespace std;

const int N = 5010;
int n;
ll sum, a[N], b[N];
//sum表示a,b对应元素mul之和(mul表示乘积)

int main()
{
    scanf("%d", &n);//建议scanf,更快
    for(int i = 1; i <= n; i++)
	    scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]); 
        sum += a[i] * b[i];
		//计算初始sum 
    } 
    ll ans = sum;
    for(int i = 1; i <= n; i++)
    {//尝试以每个位置i为中心,调整左右两侧的元素对,以获取更大的总和
        ll sm1 = sum;
        for(int j = i - 1, k = i + 1; j >= 1 && k <= n; j--, k++)
        {//长度为奇数
            sm1 -= a[j] * b[j] + a[k] * b[k];
            sm1 += a[j] * b[k] + a[k] * b[j];
			//减去当前的mul，加上交换后的mul
            ans = max(ans, sm1);//为保证mul之和最大，每次取操作前后更大的值
        }
        sm1 = sum;
        for(int j = i, k = i + 1; j >= 1 && k <= n; j--, k++)
        {//长度为偶数
            sm1 -= a[j] * b[j] + a[k] * b[k];
            sm1 += a[j] * b[k] + a[k] * b[j];
            ans = max(ans, sm1);//方法一样
        }
    }
    printf("%d\n", ans);//建议printf,更快
    return 0;//换行是个好习惯
}
```

---

## 作者：oimaster (赞：2)

简单模拟题。

我们可以枚举这个需要翻转区间的中心，然后向外扩散即可。

其中，反转的区间有两种可能：

1. 区间大小为奇数，此时区间的正中心是一个数。
2. 区间大小为偶数，此时区间的正中心是两个数。

我们分别进行枚举，就可以得到反转这个区间后可以得到的贡献。此时只需要把我们原始数列求出的结果加上贡献输出即可。

因为每次枚举中心是 $n$ 次，内循环 $\frac{n}{2}$ 次，时间复杂度为 $\operatorname{O}(n^2)$，可以通过。

```cpp
#include<iostream>
using namespace std;
#define int long long
signed main(){
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;++i)
		cin>>a[i];
	int b[n+1];
	for(int i=1;i<=n;++i)
		cin>>b[i];
	int ans;
	ans=0;
	for(int i=1;i<=n;++i)
		ans+=a[i]*b[i];
	int maxv=0;
	for(int i=1;i<=n;++i){
		int j=i;
		int k=i;
		int tmp=0;
		while(j>=1&&k<=n){
			tmp+=(a[j]-a[k])*(b[k]-b[j]);
			maxv=max(maxv,tmp);
			--j;
			++k;
		}
	}
	for(int i=1;i<n;++i){
		int j=i;
		int k=i+1;
		int tmp=0;
		while(j>=1&&k<=n){
			tmp+=(a[j]-a[k])*(b[k]-b[j]);
			maxv=max(maxv,tmp);
			--j;
			++k;
		}
	}
	cout<<maxv+ans<<endl;
}
```

---

## 作者：WZKQWQ (赞：1)

一开始看见这题还以为有什么高妙的做法，

我们先从暴力开始想，枚举 $i,j$，我们翻转区间 $[i,j]$。

令 $c_i = a_i \times b_i$，我们对 $c_i$ 做前缀后缀和，暴力的计算翻转的部分的答案再加上前缀后缀的答案，最后取最大值。

这么做是 $O(n^3)$ 的，怎么优化呢？

不难发现，翻转区间 $[l,r] $的答案就是翻转区间 $[l + 1,r - 1]$ 的答案加上 $a[l] \times b[r] + a[r] \times b[l]$ 再减去 $a[l] \times b[l] + a[r] \times b[r]$。

实现的话可以枚举区间中点 $k$,从翻转区间 $[k,k]$ 和 $[k,k + 1]$ 出发，计算所有情况。

代码（混了一个第四快，欸嘿）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5005;
int n;
ll a[N],b[N],s[N],t[N],ans;
ll read(){
	ll x = 0;
	char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar());
	for(;ch >= '0' && ch <= '9';ch = getchar()) x = x * 10 + ch - '0';
	return x;
}
int main(){
	n = read();
	for(int i = 1;i <= n;++i) a[i] = read();
	for(int i = 1;i <= n;++i) b[i] = read();
	for(int i = 1;i <= n;++i) s[i] = s[i - 1] + a[i] * b[i];
	for(int i = n;i >= 1;--i) t[i] = t[i + 1] + a[i] * b[i];
	ans = s[n];
	for(int i = 1;i <= n;++i){
		int l = i - 1,r = i + 1;
		ll tmp = a[i] * b[i];
		while(l >= 1 && r <= n){
			tmp += a[l] * b[r] + a[r] * b[l];
			ans = max(ans,tmp + s[l - 1] + t[r + 1]);
			--l,++r;
		}
		l = i,r = i + 1;
		tmp = 0;
		while(l >= 1 && r <= n){
			tmp += a[l] * b[r] + a[r] * b[l];
			ans = max(ans,tmp + s[l - 1] + t[r + 1]);
			--l,++r;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：Allanljx (赞：1)

# CF1519D Maximum Sum of Products

### 难度：$1600$

## 题意

### 题意翻译

有两个长为 $n$ 的序列 $a$ 和 $b$。你可以将 $a$ 序列的一段翻转，也可以不翻转。问在操作后将 $a$ 和 $b$ 的每一位相乘再加起来后，和最大是多少。

## 思路

因为 $1 \leq n \leq 5000$ 所以我们可以用 $O(n^2)$ 的时间复杂度来枚举翻转的位置。但是如何来查翻转后的答案呢？如果正常查找要用 $O(n)$ 的时间复杂度。这时我们发现了一个规律：翻转区间 $[i,j]$ 相当于翻转区间$[i+1,j-1]$再加上：$(a_i*b_j+a_j*b_i)-(a_i*b_i+a_j*b_j)$。就等于：$(a_i-a_j)*(b_j-b_i)$。比如说翻转区间 $[3,7]$ 相当于将区间 $[4,6]$ 翻转再加上：$(a_3*b_7+a_7*b_3)-(a_3*b_3+a_7*b_7)$ 。就等于：$(a_3-a_7)*(b_7-b_3)$ 。

这时候我们就可以想到区间 $dp$ 了。用 $dp_{i,j}$ 表示翻转区间 $[i,j]$  后的答案。我们要先将 $dp_{i,i}$ 赋成 $value$（初始不翻转的答案）。同时，也要将 $dp_{i,i-1}$ 赋成 $value$。因为：当 $l=1$ 时 $dp_{i,j}=dp_{i+1,j-1}$ 会变成 $dp_{i,j}=dp_{i+1,i}$ 。所以必须将  $dp_{i,i-1}$ 赋成 $value$，要不然当翻转相邻的两个数时 $dp_{i,i-1}$ 就会变成 $0$。

根据我们之前推出的公式，就可得出转移方程：$dp_{i,j}=dp_{i+1,j-1}+(a_i-a_j)*(b_j-b_i)$。

## 代码

``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int b[5001],a[5001],dp[5001][5001];
int value,sum,ans;
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		value+=a[i]*b[i];
	}
	ans=value;
	for(int i=1;i<=n;i++) dp[i][i]=dp[i][i-1]=value;
	for(int l=1;l<=n;l++)
	{
		for(int i=1;i+l<=n;i++)
		{
			int j=i+l;
			value=dp[i+1][j-1]+(a[i]-a[j])*(b[j]-b[i]);
			dp[i][j]=max(value,dp[i][j]);
			ans=max(ans,dp[i][j]); 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Lcm_simida (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1519D)

注意数据可知，只枚举反转区间左右端点的时间复杂度完全是够的，因此我们只需要知道反转一段固定区间之后的答案。

不难看出用 $dp_{i,j}$ 表示反转完此区间这个区间所带来的代价，即可转移 $dp_{i,j}=dp_{i+1,j-1}+a_i*b_j+a_j*b_i$，而对于反转区间之外的贡献，可用前缀和算出 $i$ 之前的和 $j$ 之后的 $a_i*b_i$ 的值。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5005],b[5005],dp[5005][5005],sum[5005],ans=0;
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) dp[i][i]=a[i]*b[i],sum[i]=sum[i-1]+a[i]*b[i];
	for(int i=1;i<n;i++) dp[i][i+1]=a[i]*b[i+1]+a[i+1]*b[i];
	for(int len=3;len<=n;len++)
		for(int i=1;i+len-1<=n;i++)
			dp[i][i+len-1]=dp[i+1][i+len-2]+a[i]*b[i+len-1]+a[i+len-1]*b[i];
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) ans=max(ans,dp[i][j]+sum[i-1]+sum[n]-sum[j]);
	cout<<ans;
	return 0;
}
```

---

## 作者：pioneer2000 (赞：0)

### 思路：

尝试区暴力枚举翻转区间的左右端点，再去计算最后的值取最大，时间复杂度就到了惊人的 $O(n^3)$，因为 $n$ 小于等于五千，所以肯定不行。

考虑去优化这一个暴力的过程，手玩一些数据可以发现，翻转就是将一些数字两两进行交换，那么我们可以很容易的求出变化的量，即为 $a_i\times b_j+a_j\times b_i-a_i\times b_i-a_j\times b_j$，那么我们进行一下因式分解就可以得到每交换两数字所产生的价值为 $(a_i-a_j)(b_j-b_i)$。

那么枚举左右端点的过程就可以优化了。

考虑枚举中心端点，向两边拓展（类似双指针的样子），每次记录总变化值，最后求解出最大变化值，最后加上原来的值即可，注意，中心端点既有可能在数字上，也有可能在数字之间，所以分两种情况写，时间复杂度在这时候就已经优化到了 $O(n^2)$。 

若无论怎么交换都不会更优，就选择不交换。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e3+5;
ll n,a[N],b[N],sum,tmp,cnt;
int main(){
	ios::sync_with_stdio(0);//关闭输入输出流
	cin.tie(0),cout.tie(0);
	cin>>n;//输入
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		sum+=a[i]*b[i];
	}
	for(int i=1;i<=n;i++){
		cnt=0;
		for(int j=i,k=i;j>=1&&k<=n;j--,k++){
			cnt+=(a[j]-a[k])*(b[k]-b[j]);
			tmp=max(cnt,tmp);
		}
	}
	for(int i=1;i<=n;i++){
		cnt=0;
		for(int j=i,k=i+1;j>=1&&k<=n;j--,k++){
			cnt+=(a[j]-a[k])*(b[k]-b[j]);
			tmp=max(cnt,tmp);
		}
	}
	tmp=max(tmp,0ll);
	cout<<sum+tmp;
	return 0;
}

```

---

## 作者：Special_Tony (赞：0)

# 思路
我们设 $dp_{i,j}$ 表示翻转 $a_i\sim a_j$ 后和增加了几。$a_i,a_{i+1},a_{i+2},\dots,a_{j-2},a_{j-1},a_j$ 反转后变成了 $a_j,a_{j-1},a_{j-2},\dots,a_{i+2},a_{i+1},a_i$，而 $a_{i+1},a_{i+2},\dots,a_{j-2},a_{j-1}$ 翻转后成为了 $a_{j-1},a_{j-2},\dots,a_{i+2},a_{i+1}$，我们发现，其中 $a_{i+1}\sim a_{j-1}$ 翻转前后都是重复的，所以不用重复算那一段，$dp_{i,j}$ 从 $dp_{i+1,j-1}$ 转移过来，$dp_{i,j}=dp_{i+1,j-1}+a_i\times b_j+b_i\times b_i-a_i\times b_i-a_j\times b_j$。然后区间 dp 就从长度入手，先枚举长度再枚举左右端点转移即可。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n;
ll dp[5005][5005], a[5005], b[5005], sum, maxx;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i)
		cin >> a[i];
	for (int i = 1; i <= n; ++ i)
		cin >> b[i], sum += a[i] * b[i];
	for (int len = 2; len <= n; ++ len)
		for (int l = 1, r = len; r <= n; ++ l, ++ r)
			maxx = max (maxx, dp[l][r] = dp[l + 1][r - 1] + a[l] * b[r] - a[l] * b[l] + a[r] * b[l] - a[r] * b[r]);
	cout << maxx + sum;
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

# 题意
给定两个长为 $n$ 的序列 $a$ 和 $b$。你可以对 $a$ 的一段区间翻转，也可以不翻转，要求翻转后 $a$ 与 $b$ 对应位置之积的和最大。即求下式的值最大 $$\sum_{i=1}^na_i\times b_i$$

$1\le n\le 5000$，$1\le a_i,b_i\le10^7$。
# 思路
考虑使用DP

设 $f_{i,j}$ 表示翻转 $[i,j]$ 区间后的 $\sum_{i=1}^na_i\times b_i$。

可以想到，翻转 $[l,r]$ 区间等同于翻转 $[l+1,r-1]$ 区间后，再将 $l$ 和 $r$ 调换。

那么可以得到状态转移方程：$f_{i,j}=f_{i+1,j-1}+a_j \times b_i+a_i \times b_j-a_i \times b_i-a_j \times b_j$。
意为在翻转 $[i+1,j-1]$ 的答案的基础上，减去两端原来相乘的积，再加上两端调转后的积。最终的答案就是 $\max(f_{i,j})$。

下面是代码，一些初始化问题已经有详细注释：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

#define ll long long //数据较大需要long long
const int maxn=5e3+10;
int n;
ll a[maxn],b[maxn];
ll f[maxn][maxn],t[maxn];
ll s[maxn],sum,ans;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	
	for(int i=1;i<=n;i++) sum+=a[i]*b[i]; //不翻转情况的答案
	for(int i=1;i<=n;i++) f[i][i]=sum,f[i+1][i]=sum; //初始化，翻转(i,i)区间等同于不翻转，f[i+1][i]=sum是为了避免状态转移时出现问题
	
	for(int i=n;i>=1;i--)
		for(int j=i+1;j<=n;j++) //注意递推顺序
			f[i][j]=f[i+1][j-1]+a[i]*b[j]+a[j]*b[i]-a[i]*b[i]-a[j]*b[j];
			
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) ans=max(ans,f[i][j]);//统计答案
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Eric_jx (赞：0)

## 思路：

首先可以想到三重循环的暴力。我们枚举要反转区间的左端点和右端点，然后计算这个区间反转后的贡献，再加上其他的贡献即可，其他的贡献可以用前缀和维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000005],b[1000005],sum[1000005];
int main(){
	long long n,ans=0;
	cin>>n;
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(long long i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		sum[i]=sum[i-1]+a[i]*b[i];
	}
	for(long long i=1;i<=n;i++){
		for(long long j=i+1;j<=n;j++){
			long long s=0;
			for(long long k=i;k<=j;k++){
				s+=a[k]*b[j-k+i];
			}
			ans=max(ans,s+sum[i-1]+sum[n]-sum[j]);
		}
	}cout<<max(ans,sum[n]);
	return 0;
}
```
时间复杂度 $O(n^3)$。显然过不掉。

我们考虑优化。枚举反转区间左端点和右端点肯定是少不了的，所以我们可以优化第三重循环。通过区间 dp 预处理出 $[i,j]$ 区间反转后的贡献，再二重循环计算答案即可。

时间复杂度 $O(n^2)$。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
    long long x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
inline void write(long long x){
    if(x==0){putchar('0');return;}
    long long len=0,k1=x,c[10005];
    if(k1<0)k1=-k1,putchar('-');
    while(k1)c[len++]=k1%10+'0',k1/=10;
    while(len--)putchar(c[len]);
}
long long a[100005],b[100005],f[5005][5005],sum[10005];
int main(){
	long long n=read(),ans=0;
	for(long long i=1;i<=n;i++){
		a[i]=read();
	}
	for(long long i=1;i<=n;i++){
		b[i]=read();
		f[i][i]=a[i]*b[i];
		sum[i]=sum[i-1]+f[i][i];
	}
	for(long long i=1;i<n;i++){
		f[i][i+1]=a[i]*b[i+1]+a[i+1]*b[i];
	}
	for(long long l=3;l<=n;l++){
		for(long long i=1;i+l-1<=n;i++){
			long long j=i+l-1;
			f[i][j]=f[i+1][j-1]+a[i]*b[j]+a[j]*b[i];
		} 
	}
	for(long long i=1;i<=n;i++){
		for(long long j=i+1;j<=n;j++){
			ans=max(ans,sum[i-1]+sum[n]-sum[j]+f[i][j]);
		}
	}cout<<max(ans,sum[n]);
	return 0;
}
```

---

## 作者：02Ljh (赞：0)

## CF1519D

## 题解

首先观察数据，$n\leq5000$ 说明完全可以枚举区间的左右端点来解，我们必须 $O(1)$ 求出翻转 $l,r$ 之间数的结果。

考虑前缀和求出前 $i$ 个数中 $a_i \times b_i$ 的值，把总共的值减去 $l,r$ 区间的值在加上反转区间新贡献的值即为解。

翻转 $l,r$ 之间的值为 $tot+\sum_{j=l}^r a_i\times b_i-a_{r-j+1} \times b_j$，拆分成 $\sum_{j=l}^r a_i\times b_i-\sum_{j=l}^ra_{r-j+1} \times b_j$ 而我们要处理的是后面一段。数形结合来看我们所求的正是在正方形一个对角线的一段区间内的值，用对角线前缀和轻松解决。

注意开 ```long long```！

## 代码

```cpp
// Problem: Maximum Sum of Products
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1519D
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define int long long
#define ull unsigned long long
#define ll long long
#define MAXN 5019
#define WA cout<<"CCF\n";
#define eps 1e-5
#define ls i*2
#define rs i*2+1
#define none -1145141919
#define pii pair<int,int>
#define Y cout<<"Yes\n"
#define N cout<<"No\n"
#define H cout<<"\n"
const int MOD=1e9+7;
int a[MAXN],b[MAXN],s[MAXN];
int dp[MAXN][MAXN];
int n;
int calc(int l,int r)
{
    return s[r]-s[l-1]-(dp[l][r]-dp[r+1][l-1]);
}
 main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++)
    {
        s[i]=s[i-1]+(a[i]*b[i]);
    }
    for(int j=1;j<=n;j++)
    {
        for(int i=1;i<=n;i++)
        {
            dp[i][j]=dp[i+1][j-1]+a[i]*b[j];
        }
    }
    int tot=s[n];
    int maxn=-1;
    for(int l=1;l<=n;l++)
    {
        for(int r=l+1;r<=n;r++)
        {
            //cout<<l<<" "<<r<<" "<<tot-calc(l,r)<<"\n";
            maxn=max(maxn,tot-calc(l,r));
        }
    }
    cout<<max(maxn,tot);
    return 0;
}
//hope to pass
```

---

## 作者：Fa1thful (赞：0)

### 题意：
给定两个数组，现在可以将第一个数组的一段翻转，求两个数组对应位相乘的结果再相加的最大值。
### 思路1(暴力)：
这题显然是一道 `dp`，这道题最开始会想到一位一位地枚举，然后再求和与 `dp` 数组取最大值。但是看数据范围$a_i,b_i\le10^7$ ,再一相乘肯定会爆 `int`。所以我们开`long long`。

在这个暴力中：

状态：$dp_{i,j}$表示修改 `i-j` 的区间，所得到的最大值。

转移：只需要保证最大，那么和自己以及乘积和取 `max` 即可。
```cpp
dp[i][j] = max(dp[i][j], tmp);   //tmp表示这样修改的和
```

因为枚举两个修改的头尾需要 $O(n^2)$的时间复杂度，算和又需要一个 $O(n)$ ，所以整个 `dp` 需要 $O(n^3)$ 的时间复杂度，只能过七个点。
### 思路1代码：
```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
int a[100000];
int b[100000];
int dp[5001][5001];
int c[100000];
int d[100000];
signed main()
{
	int ans = 0;
	int n;
	cin >> n;
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		c[i] = a[i];             //将数组进行复制，为了计算翻转后的数组 
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> b[i];
		d[i] = b[i];
	}
	for (int i = 1; i <= n; i++)
	{
		sum += a[i] * b[i];     //计算不翻转的和 
	}
	for (int i = 1; i <= n; i++)
	{
		dp[i][i] = sum;     //修改从i到i相当于没修改，所以等于不翻转的最大和 
	}
	int p = 1;         //记录另一个数组反过来复制 
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int tmp = 0;       //反转后的和 
			for (int k = 1; k <= n; k++)
			{
				c[k] = a[k];
				d[k] = b[k];     //每次将数组返回原状，为不影响下一步翻转
			}
			p = i;//从i翻转到j 
			for (int k = j; k >= i; k--)
			{
				c[p] = a[k];
				p++;         //翻转 
			} 
			for (int k = 1; k <= n; k++)
			{
				tmp += c[k] * d[k];     //计算反转后的和 
			}
			dp[i][j] = max(dp[i][j], tmp);     //与其他翻转方法取max 
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			ans = max(ans, dp[i][j]);        //计算最大的翻转所能达到的和 
		}
	}
	cout << ans << endl;     //输出 
	return 0;
}
```
或许是因为暴力拿分太少，在考试时的我才会思考满分做法吧......
### 思路2(满分做法)
一开始我打出来暴力的时候我就想能不能用一个数组维护好不用翻转的其他值，但是想了很久也没想到任何一种我学过的数据结构可以。于是我就想一个翻转区间更大的，可以通过被它包含在内的小区间翻转旁边的两个得到，所以说满分思路就出现了。

`dp`状态：$dp_{i,j}$ 表示翻转 `i-j` 的区间，所得到的最大值。

`dp`转移：因为大的可以通过包含在内的小的加上旁边两个翻转后的结果，所以：
```cpp
dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] a[i] * b[i] - a[j] * b[j] + a[j] * b[i] + a[i] * b[j]);    //后面一串表示翻转的值
```
这只需要枚举两个区间的 `l` 和 `r`，所以复杂度为 $O(n^2)$ 可以过。
### 思路2代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
long long a[5001];
long long b[5001];
long long dp[5001][5001];
long long c[5001];
long long d[5001];
int main()
{
	long long ans = 0;
	int n;
	cin >> n;
	long long sum = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i]; 
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> b[i];
	}
	for (int i = 1; i <= n; i++)
	{
		sum += a[i] * b[i];    //计算不翻转的和 
	}
	for (int i = 1; i <= n; i++)
	{
		dp[i][i] = dp[i][i - 1] = sum;       //赋dp[i][i-1]的原因是这个可能会在后面的转移里面被区间长度为2的用到  
	}
	ans = sum;
	for (int len = 1; len <= n; len++)       //枚举区间长度 
	{
		for (int i = 1; i + len <= n; i++)      //枚举起始点 
		{
			int j = i + len;           //终点 
			dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] - a[i] * b[i] - a[j] * b[j] + a[j] * b[i] + a[i] * b[j]);  //转移 
			ans = max(ans, dp[i][j]);//更新最大的翻转情况 
		}
	}
	cout << ans << endl; //输出 
	return 0;
}
```
 谢谢观赏

---

## 作者：kradcigam (赞：0)

先考虑显然的暴力怎么做就是枚举要翻转的区间，然后暴力翻转，暴力求值，时间复杂度 $O(n^3)$。

我们发现每次枚举到要翻转的区间都要重新求值，这显然是可以优化的。我们发现由于是区间翻转，所以可以找到中心点，然后不断向两边扩展，就可以将时间复杂度优化为 $O(n^2)$。

一个小 trick 就是像处理字符串那样在相邻两个数中间添加 $0$。

code:

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define int long long
#define mp make_pair
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=10010;
int a[N],b[N],s;
signed main(){
	int n=read();
	F(i,1,n)a[(i<<1)]=read();//添0
	F(i,1,n)b[(i<<1)]=read();//添0
	n=(n<<1|1);//添0
	F(i,1,n)s+=a[i]*b[i];//不翻转
	const int z=s;
	F(i,1,n){
		int l=z;
		F(j,1,min(i-1,n-i)){
			l-=a[i-j]*b[i-j];
			l-=a[i+j]*b[i+j];
			l+=a[i-j]*b[i+j];
			l+=a[i+j]*b[i-j];//向两边扩展
			s=max(s,l);
		}
	}cout<<s;
	return 0;
}
```

---

