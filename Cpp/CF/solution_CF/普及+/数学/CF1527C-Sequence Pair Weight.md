# Sequence Pair Weight

## 题目描述

The weight of a sequence is defined as the number of unordered pairs of indexes $ (i,j) $ (here $ i \lt j $ ) with same value ( $ a_{i} = a_{j} $ ). For example, the weight of sequence $ a = [1, 1, 2, 2, 1] $ is $ 4 $ . The set of unordered pairs of indexes with same value are $ (1, 2) $ , $ (1, 5) $ , $ (2, 5) $ , and $ (3, 4) $ .

You are given a sequence $ a $ of $ n $ integers. Print the sum of the weight of all subsegments of $ a $ .

A sequence $ b $ is a subsegment of a sequence $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

- In test case $ 1 $ , all possible subsegments of sequence $ [1, 2, 1, 1] $ having size more than $ 1 $ are: 
  1. $ [1, 2] $ having $ 0 $ valid unordered pairs;
  2. $ [2, 1] $ having $ 0 $ valid unordered pairs;
  3. $ [1, 1] $ having $ 1 $ valid unordered pair;
  4. $ [1, 2, 1] $ having $ 1 $ valid unordered pairs;
  5. $ [2, 1, 1] $ having $ 1 $ valid unordered pair;
  6. $ [1, 2, 1, 1] $ having $ 3 $ valid unordered pairs.
  
   Answer is $ 6 $ .
- In test case $ 2 $ , all elements of the sequence are distinct. So, there is no valid unordered pair with the same value for any subarray. Answer is $ 0 $ .

## 样例 #1

### 输入

```
2
4
1 2 1 1
4
1 2 3 4```

### 输出

```
6
0```

# 题解

## 作者：npqenqpve (赞：10)

### 题意：

给定长度为 $n$ 序列，求每个子段 $[l,r]$ 中 $a_i=a_j$ $(l\leq i<j\leq r)$ 的个数

$1\leq n\leq 10^5$

### 思路：

首先考虑 $O(n^2)$ 做法，找到每一对 $a_i=a_j$ $(1\leq i<j\leq n)$，对答案累加 $i\times (n-j+1)$ 因为包含 $[i,j]$ 的区间 $[l,r]$ 的 $l$ 有 $i$ 种选择，$r$ 有 $n-j+1$ 种选择，优化这种方法，可以对每一个数分别考虑有哪些与其相等，比如与 $x$ 相等的有 $a_i$，$a_{j}$，$a_{k}$，假设 $1\leq i<j<k \leq n$，那么答案增加了 $(i+j+k)\times (n-k+1)$，设 $b_i$ 为所有满足 $a_i=a_j$ $(j<i)$ 的下标 $j$ 之和，那么对答案的贡献将增加 $b_i\times (n-i+1)$，对每个数分别统计即可。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long 
#define ld long double
using namespace std;
int t,a[100005],b[100005];
map<int,int>num;
signed main()
{
    cin>>t;
    while(t--)
    {
        int n;cin>>n;
        for(int i=1;i<=n+1;i++) a[i]=0;
        num.clear();
        for(int i=1;i<=n;i++) 
        {
            cin>>a[i];
        }
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            ans+=num[a[i]]*(n-i+1);
            num[a[i]]+=i;
        }
        cout<<ans<<"\n";
    }
    system("pause");
}
```



---

## 作者：封禁用户 (赞：7)

# 1.前言
[题目链接](http://codeforces.com/contest/1527/problem/C)

**题目大意：**
有 $n$ 个整数的数组，对于一个数组的 weight，定位数组中所有的 $[i,j]$，有多少个满足 $a[i]==a[j]$。问数组的所有子数组中，所有的 weight 有多少。
# 2.解析：
### 样例分析
以数字 $[1,1,2,2,1,1]$ 为例，看看中间 $[2,2]$ 有多少种情况：
- 向左边延伸，左边起点有 $[2,x],[1,2,x],[1,1,2,x]$ 三种可能；
- 向右边延伸，右边结尾有 $[x,2],[x,2,1],[x,2,1,1]$ 三种可能；

包括 $[2,2]$ 的所有子数组，即是从左边起点选择一个起点（$3$ 种可能），从右边结尾选择一个结点（$3$ 种可能，一共有 $3\times 3=9$ 种可能。

容易知道，对于 $[i,j]$，假如有 $a[i]==a[j]$，则一共会有 $i*(n-j+1)$ 的可能。（$i$ 下标从1开始）

我们用 $left[i]$ 来表示 $i$，$right[i]$ 来表示 $n-i+1$，则上面的公式表示为 $left[i]\times right[j]$。
 
当有 $[i,j,k]$ 满足 $a[i]==a[j]==a[k]$ 的时候，我们有 $left[i]\times right[j]+left[i]\times right[j] + left[j]\times right[k]$。
 
 
所分组累计下，用 map 区分；然后逐个计算下即可。
 
注意超 long long 的 trick。
# 3.code
```cpp
typedef long long lld;

class Solution {
    static const int N = 100010;
public:
    int n, m;
    int a[N];
    map<int, vector<int>> h;
    
public:
    void solve() {
        int t;
        cin >> t;
        while (t--) {
            cin >> n;
            h.clear();
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
            }
            for (int i = 0; i < n; ++i) {
                if (h.find(a[i]) != h.end()) {
                    h[a[i]].push_back(i + 1);
                }
                else {
                    vector<int> tmp;
                    tmp.push_back(i + 1);
                    h[a[i]] = tmp;
                }
            }
            lld ans = 0;
            for (map<int, vector<int> > :: iterator it = h.begin(); it != h.end(); ++it) {
                vector<int> vec = it->second;
                lld sum = 0;
                for (int i = 0; i < vec.size(); ++i) {
                    sum += (n - vec[i] + 1);
                }
                for (int i = 0; i < vec.size(); ++i) {
                    sum -= (n - vec[i] + 1);
                    ans += 1LL * vec[i] * sum;
                }
            }
            cout << ans << endl;
        }
    }
}
ac;
int main(){
    ac.solve();
    return 0;
}

```


---

## 作者：ZCETHAN (赞：4)

[传送门](http://codeforces.com/problemset/problem/1527/C)

## 题目大意
给定一个长度为 $n$ 的序列 $a$，求：
$$\sum_{1\le l<r\le n}\sum_{l\le x<y\le r}[a_x=a_y]$$
即：求每一个连续区间内的相等数对之和。

## Solution
套路题，如果直接求不好求，那么算每一部分的贡献。

首先考虑如果两个数 $a_i=a_j$（$i<j$），那么其产生的贡献是 $i\times (n-j+1)$，也就是有 $i\times (n-j+1)$ 个区间包含它。

此时考虑如果有第三个 $a_k=a_i=a_j$（$k>j$），这个时候贡献会加上：
$$i\times (n-k+1)+j\times (n-k+1)$$
$$=(i+j)\times (n-k+1)$$

于是我们想到，对于每一个值，我们记录这个值的下标的和为 $sum$，当这个值新加入了一个下标时，我用这个和来更新答案：
$$ans=ans+sum\times (n-i+1)$$
其中 $i$ 为新加入的下标。

那么问题是值域比较大，所以用到离散化即可。

## Code
```cpp
#include<bits/stdc++.h>
#define inf 1<<30
#define INF 1ll<<60
#define ll long long
using namespace std;
const int MAXN=1e5+10;
int a[MAXN],b[MAXN];
ll sum[MAXN];
void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	int cnt=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+cnt,a[i])-b;
	//离散化
	ll ans=0;
	for(int i=1;i<=n;i++){
		if(!sum[a[i]]) sum[a[i]]+=i;
		else{
			ans+=sum[a[i]]*(n-i+1);
			sum[a[i]]+=i;
		}
	}printf("%lld\n",ans);
	for(int i=1;i<=cnt;i++) sum[i]=0;//注意不要用 memset 全部更新，这题能卡掉（亲测）
}
int main()
{
	int T;
	for(scanf("%d",&T);T--;)
		solve();
}
```

---

## 作者：_xbn (赞：3)

分享一种 $dp$ 做法，我们设 $f(i)$ 表示所有以 $i$ 结尾的子段的权重和。

由于 $f(i)$ 必定包含第 $i$ 个数，所以转移时我们可以找到他之前与他相等的数进行转移，暴力做法就是枚举一遍之前出现过的与他相等的数，这样太慢，我们可以用 $map$ 存 $i$ 之前与 $a(i)$ 相等的数。

那相等的两个数的贡献怎么计算呢，由于包含这两个数的子段才能产生贡献，我们设另一个数在 $j$ 处出现，那要包含 $i$ 和 $j$ 的子段就是所有以 $j$ 结尾的子段与 $j$ 到 $i$ 的子段拼接形成的子段，可以发现总共有 $j$ 个。

所以我们用 $map$ 与 $i$ 相等的数的出现位置，按照上述方法计算答案即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 600002;
int n, m, k, p, ans, sum, t, tot, cnt, a[N], b[N], c[N], d[N], f[N];
map<int,int> mp;
inline int read()
{
    register int x = 0, f = 1;
	char ch = getchar();
    while(!isdigit(ch))
	{
		if(ch == '-') f=-1;
		ch = getchar();
	}
    while(isdigit(ch))
	{
		x=(x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
    return x * f;
}
signed main()
{
    int T = read();
    while(T--)
    {
        n = read();
        mp.clear();
        ans = 0;
        for(int i = 1; i <= n; i++)
        {
            a[i] = read();
            f[i] = 0;
        }
        for(int i = 1; i <= n; i++)
        {
            if(i > 1) f[i] = f[i - 1];
            if(mp.count(a[i]))
            {
                f[i] += mp[a[i]];
            }
            mp[a[i]] += (i);
            ans += f[i];
        }
        cout << ans << endl;
    }
    return 0;
}
```


---

## 作者：Cutest_Junior (赞：2)

## 题解 CF1527C 【Sequence Pair Weight】

### 题意

+ 定义 $a$ 的权重为数组 $a$ 中具有相同值的无序索引对 $(i,j)(i\ne j)$ 的个数；
+ 求序列 $a$ 的所有子段的权重之和；
+ 多组数据，$n\le10^5$，$a_i\le10^9$。

### 做法

相同的值才对答案有贡献，不同的值贡献独立，所以可以分别求所有值的贡献，最后相加。

发现 $a_i\le10^9$，直接枚举值已经 TLE 了，考虑到值的大小对答案没有影响，可以离散化，将 $a_i$ 的值域降到 $10^5$。

考虑如何计算每个值的贡献。

对于任意值相同的索引对 $(i,j)$，对答案的贡献为包含 $a_i,a_j$ 的子段的个数，这是一经典计数问题，答案为 $i\times(n-j+1)$。

对于值为 $x$ 的索引，设有 $k$ 个，分别为 $b_1,b_2\dots b_k$，则值为 $x$ 的索引对答案的贡献为 

$\begin{aligned}
ans(x)&=\sum_{1\le i<j\le n}b_i\times (n-b_j+1)\\
&=\sum_{j=1}^n \sum_{i=1}^{j-1}b_i\times (n-b_j+1)\\
&=\sum_{j=1}^n\left[(n-b_j+1)\times\sum_{i=1}^{j-1}b_i\right]
\end{aligned}$

时间复杂度均摊为 $O(N^2)$。

可以使用前缀和维护 $\sum\limits_{i=1}^{j-1}b_i$，使总时间复杂度优化到线性。

### 代码

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

vector<int> v;

int id(int x) {
	return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

int a[N];

ll ans[N];
ll sum[N];

void solve() {
	vector<int>().swap(v);
	int n;
	scanf("%d", &n);
	for (int i = 0; i <= n; ++i) {
		ans[i] = sum[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 1; i <= n; ++i) {
		int x = id(a[i]);
		ans[x] += (ll)(n + 1 - i) * sum[x];
		sum[x] += i;
	}
	ll anss = 0;
	for (int i = 0; i <= n; ++i) {
		anss += ans[i];
	}
	printf("%lld\n", anss);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}
```

---

