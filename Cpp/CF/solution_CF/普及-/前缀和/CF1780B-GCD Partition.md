# GCD Partition

## 题目描述

While at Kira's house, Josuke saw a piece of paper on the table with a task written on it.

The task sounded as follows. There is an array $ a $ of length $ n $ . On this array, do the following:

- select an integer $ k > 1 $ ;
- split the array into $ k $ subsegments $ ^\dagger $ ;
- calculate the sum in each of $ k $ subsegments and write these sums to another array $ b $ (where the sum of the subsegment $ (l, r) $ is $ {\sum_{j = l}^{r}a_j} $ );
- the final score of such a split will be $ \gcd(b_1, b_2, \ldots, b_k)^\ddagger $ .

The task is to find such a partition that the score is maximum possible. Josuke is interested in this task but is not strong in computer science. Help him to find the maximum possible score.

 $ ^\dagger $ A division of an array into $ k $ subsegments is $ k $ pairs of numbers $ (l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k) $ such that $ l_i \le r_i $ and for every $ 1 \le j \le k - 1 $ $ l_{j + 1} = r_j + 1 $ , also $ l_1 = 1 $ and $ r_k = n $ . These pairs represent the subsegments.

 $ ^\ddagger $ $ \gcd(b_1, b_2, \ldots, b_k) $ stands for the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the array $ b $ .

## 说明/提示

In the first test case, you can choose $ k = 2 $ and split the array into subsegments $ (1, 2) $ and $ (3, 4) $ .

Then the score of such a partition will be equal to $ \gcd(a_1 + a_2, a_3 + a_4) = \gcd(2 + 2, 1 + 3) = \gcd(4, 4) = 4 $ .

In the fourth test case, you can choose $ k = 3 $ and split the array into subsegments $ (1, 2), (3, 5), (6, 6) $ .

The split score is $ \gcd(1 + 2, 1 + 1 + 1, 3) = 3 $ .

## 样例 #1

### 输入

```
6
4
2 2 1 3
2
1 2
3
1 4 5
6
1 2 1 1 1 3
10
12 30 37 88 12 78 89 17 2 12
6
7 7 7 7 7 7```

### 输出

```
4
1
5
3
1
21```

# 题解

## 作者：wzc_IOI_czl (赞：7)

**0. 前言**  
一个比较常见的套路了。  

**0.5. 题意**  
给定一个长度为 $n$ 的序列，你需要自选一个 $k$（$1< k\le n$），自选方式把序列划分成 $k$ 个子段，让所有子段的 $\gcd$ 最大。  

**1. 分析**  
首先考虑一个方案 $\{b_k\}$（我们假设 $b_i$ 是第 $i$ 段的子段和），假设其 $\gcd$ 为 $d$。因为子段都是连续的，所以我们可以合并 $b_1$ 和 $b_2$。此时，任意一段仍然是 $d$ 的倍数。  
就有一个现象：对于任意一个长度大于 $2$ 的方案，总有一个长度等于 $2$ 的方案，使得它们的结果一样大。  
换句话说，如果最大值为 $d_0$，且长度为 $2$ 的方案不存在答案为 $d_0$ 的，那么这个 $d_0$ 最多只能在 $k=1$ 取到。  
所以，我们只需要每次把整个序列分成 $2$ 段，就一定能找出最优解。  
方法就是，枚举断点，前缀和统计。  
```cpp
cin >> n;
for(int i = 1; i <= n; i++) {
	cin >> x[i];
	s[i] = s[i - 1] + x[i];//前缀和
}
int ans = -1ll;
for(int i = 1; i < n; i++) { //枚举的是左边那个子段的结束坐标
	int l = s[i], r = s[n] - s[i];
	ans = max(ans, __gcd(l, r));//__gcd是C++某个库（好像是math）自带的 gcd 函数。
}
cout << ans << endl;
```  

**2. 后言**  
C题出锅了，D题是恶心交互，E题不会，下班力（喜

---

## 作者：RNTBW (赞：3)

### 序。
准备多刷 CF 题了。

这道题很水，不过很有趣。
## 思路
先说一个人尽皆知的结论：$\gcd(a,b,c) \leqslant \gcd(a+b,c)$。

为什么呢？

考虑证明，设 $a=px,b=py,c=pz$。

则 $a+b=p(x+y)$。

则 $\gcd(a,b,c)=\gcd(px,py,pz)=p$，

$\gcd(a+b,c)=\gcd(p(x+y),pz)=p\times \gcd(x+y,z)$。

$\because \gcd(x+y,z) \geqslant 1$

所以 $p\times \gcd(x+y,z) \geqslant p$。

即 $\gcd(a+b,c) \geqslant \gcd(a,b,c)$。

之后有了这个结论，做法显而易见，用一个前缀和数组 $s$，每次枚举断点 $i$，$ans=\max^{n-1}_{i=1} \gcd(s_i,s_n-s_i)$。

## 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200001],s[200001];
int t,n,i,k;
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);k=-1ll;//k=-1需注意		for(i=1;i<=n;i++) scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
		for(i=1;i<n;i++) k=max(k,__gcd(s[i],s[n]-s[i]));//注意这里是i<n而不是i<=n，因为i=n会使得s[n]-s[i]=0
		printf("%lld\n",k);
	}
	return 0;
}
```


---

## 作者：Enjoy2024 (赞：2)

结论：$\gcd(a,b,c)\le \gcd(a,b+c)$。

考虑证明。

容易发现，当 $b$ 和 $c$ 的最大公因数为 $k$ 的时候，有 $k\mid b$，$k\mid c$ 。根据整除的基础性质，容易发现有 $k\mid b+c$。也就是说，$\gcd(a,b+c)$ 的值不可能小于 $\gcd(a,b,c)$ 的值。

那么通过这个结论，发现将区间划分成两段一定不会更劣，所以枚举中间点，求出中间点两遍的和，取 $\gcd$ 的最大值即可。

求区间的和可以使用线段树解决。

时间复杂度 $O(n\log n)$。

---

## 作者：zhicheng (赞：1)

### 思路

首先有一个结论，$\gcd(a,b,c)\leq \gcd(a+b,c)$。因为假设 $\gcd(a,b,c)=m$，$a=k_1\times m$，$b=k_2\times m$。那么 $a+b$ 就是 $(k_1+k_2)\times m$，显然是 $m$ 的倍数，所以 $\gcd(a+b,c)$ 一定不会小于 $m$，得证。

我们通过~~观察样例~~上面的结论看出一定是分成两段，因为如果不是两段，你把某些段合起来之后一定不会劣。所以就用前缀和维护区间和，枚举两段。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200010];
int main(){
	int t,n;
	long long ans;
	scanf("%d",&t);
	while(t--){
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);  //注意开 long long
			a[i]+=a[i-1];  //前缀和
		}
		for(int i=1;i<=n-1;i++){  //枚举，注意边界
			ans=max(ans,__gcd(a[i],a[n]-a[i]));
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Erotate (赞：0)

### solution

首先令 $b_1,b_2,\dots ,b_k$ 为每一段的值。那么显然有：

$$\gcd(b_1,b_2,\dots,b_k) \leq \gcd(b_1,b_2,\dots,b_{k-1}+b_k)$$

以此类推

$$\gcd(b_1,b_2,\dots,b_{k-1}+b_k) \leq \gcd(b_1,b_2,\dots,b_{i-1},b_i+ \dots  + b_{k-1}+b_k)$$

也是成立的（其中 $1 \leq i \leq k$）。

进一步的

$$\gcd(b_1,b_2,\dots,b_{i-1},b_i+ \dots  + b_{k-1}+b_k) \leq \gcd(b_1+b_2+\dots+b_{i-1},b_i+ \dots  + b_{k-1}+b_k)$$

也是成立的。

从上面的不等式可以看出 当 $k$ 取到 $2$ 的时候（即把原数组分成两段的时候） $\gcd$ 是最大的，所以我们只需要枚举分成那两部分并取 $\gcd$ 的最大值即可。

### code
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N=2e5+5;
int T,n,a[N];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        int sum=0,cnt=0,ans=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            sum+=a[i];
        }
        for(int i=1;i<n;++i){
        	cnt+=a[i];
			  ans=max(ans,__gcd(sum-cnt,cnt));
		   }
        cout<<ans<<endl;
    }
    return 0;
}

```


---

## 作者：tZEROちゃん (赞：0)

显然 $k=2$ 时是最优解，用前缀和记录，扫一遍更新最大值即可。

考虑证明，考虑如果把这个数字分成 $m(m>2)$ 个数组，那么显然 $\gcd(b_1,b_2,\cdots,b_m)\leq \gcd(b_1+b_2,b_3,\cdots,b_m)$。也就是说我们可以用 $b_1+b_2$ 代替 $b_1,b_2$，且答案不会更劣。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)

#define int long long
void solve() {
  int n; cin >> n;
  vector<int> a(n + 1), sum(n + 1, 0);
  rep (i, 1, n) cin >> a[i], sum[i] = sum[i - 1] + a[i];
  int best = 0;
  rep (i, 1, n - 1) {
    // cout << sum[i] << ' ' << sum[n] - sum[i] << '\n';
    best = max(best, __gcd(sum[i], sum[n] - sum[i]));
  }
  cout << best << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int q; cin >> q;
  while (q--) {
    solve();
  }

  return ~~(0 ^ 0);
}
```

---

