# [ICPC 2024 Xi'an I] Make Them Straight

## 题目描述

有一个长度为 $n$ 的非负整数序列 $a$，其中第 $i$ 个元素为 $a_i(1\leq i\leq n)$。

如果存在一个非负整数 $k(0\leq k\leq 10^6)$ 满足以下条件，则该序列被定义为「好」序列：

对于所有 $1\leq i\leq n$，都有 $a_{i}=a_{1}+(i-1)k$。

为了使这个序列成为「好」序列，对于每个 $i(1\leq i\leq n)$，你可以选择不做任何操作，或者支付 $b_i$ 个硬币将 $a_i$ 替换为任意非负整数。

问题是，使这个序列成为「好」序列的最小代价是多少。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5
1 4 3 2 5
1 1 1 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1 4 3 2 5
1 9 1 1 1```

### 输出

```
3```

# 题解

## 作者：yywlp (赞：8)

挺有意思的题。

题目中 $0\le a_i\le 10^6$ 是非常重要的限制，因为这让我们可以枚举 $k$。显然当 

$$(i-1)\times k\ge 10^6$$

的时候后面的 $a_i$ 一定都不满足了，那么设 $M=10^6$，每次其实只用枚举前 $\frac{M}{k}$ 个 $a_i$ 即可，这个形式刚刚好是**调和级数**，复杂度 $\Theta(M\log M)$。

又通过题目中的定义：

$a_{i}=a_{1}+(i-1)k$，（$1\leq i\leq n$）。

发现这其实是一条直线 $y=kx+b$。

其中 $k$ 就是题中的 $k$，$b$ 就是 $a_1$。

所以枚举 $k$，枚举 $a_i$，当 $(i-1)\times k\ge 10^6$ 时停止枚举，同时以 $a_i-(i-1)\times k$ 为下标，$b_i$ 为值，开个桶存一下看哪个 $a_1$ 可以使直线碰到的点价值总和最大即可。

复杂度即为开始所说的 $\Theta(M\log M)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int M=1e6+10;
int n;
int a[M],b[M],sum=0;
int p[4*M];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]),sum+=b[i];
	int ans=1e18;
	for(int i=0;i<=1e6;i++){
		for(int j=1;(j-1)*i<=1e6&&j<=n;j++)p[a[j]-(j-1)*i+2*M]+=b[j],ans=min(ans,sum-p[a[j]-(j-1)*i+2*M]);
		for(int j=1;(j-1)*i<=1e6&&j<=n;j++)p[a[j]-(j-1)*i+2*M]-=b[j];
	}
	cout<<ans<<endl;
}
```

---

## 作者：Zzqyoung (赞：3)

# P10556 [ICPC2024 Xi'an I] Make Them Straight 

## 分析题意：
有一个长度为 $n$ 的非负整数序列 $a$。对于每一个 $a_i$，可以花费 $b_i$ 的代价将 $a_i$ 修改为任意非负整数，求最少多少的代价可以把 $a$ 数组修改成从左到右，公差在 $[0,10^6]$ 的等差数列。

## 思路：
可以枚举如果保留 $a_i$ 后，首项和公差分别是什么，并记录在这样的首项和公差下，可以节省多少代价，最后求出最大节约，用总代价 $-$ 最大节约即可。

### 注：等差数列
$d=(a_n-a_1)\div(n-1)$

$a_n=a_1+d\times(n-1)$

$a_1=a_n-d\times(n-1)$

## AC Code

```cpp
#include <iostream>
#include <bits/stdc++.h>
#include <map>
#define int long long
using namespace std;

int n;
int a[200005],b[200005],ans,sum;
map<pair<int,int>,int> M;

signed main(){
	cin>>n;
	for (int i=1;i<=n;i++)	cin>>a[i];
	for (int i=1;i<=n;i++){
		cin>>b[i];
		sum+=b[i];
	}
	for (int i=1;i<=n;i++){
		for (int j=0;j<=1000000/i;j++){
			int x=a[i]-(i-1)*j;
			if (x>=0){
				pair<int,int> p(x,j);
				M[p]+=b[i];
				ans=max(ans,M[p]);
			}
		}
	}
	cout<<sum-ans;
} 
```

---

## 作者：gavinliu266 (赞：2)

fix：修正一些错误。
# 前 17 个测试点
## 思路
可以想到暴力枚举不动的那个点，然后枚举另外一点，计算斜率，把相同斜率的 $b_i$ 累加起来得到最大值 $maxn$，最后答案便是 $\sum b_i - maxn$。

可以用 unordered_map，时间复杂度 $\Omega(n^2)$。

也可以用数组，时间复杂度 $\Theta(n^2)$，但效果一样。

## 代码实现
```cpp
#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;
int n, a[200005], b[200005], x;
long long sum, maxn;
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &b[i]);
        sum += b[i];
    }
    for(int i = 1; i <= n; ++i) {
        unordered_map<long long, long long> mp;
        for(int j = 1; j <= n; ++j)
            if(i != j) {
                if((a[j] - a[i]) % (j - i) != 0) continue; // k 为整数
                mp[(a[j] - a[i]) / (j - i)] += b[j];
            }
        for(auto p : mp)
            if(p.first >= 0) maxn = max(maxn, p.second + b[i]);  // k 为非负数
    }
    printf("%lld\n", sum - maxn);
}
```

# 正解
## 思路
由题意，$a_i=a_1+(i-1)k$，所以 $a_1=a_i-(i-1)k$。

可以考虑枚举 $k$，然后对于每个点，计算对应的 $a_1$，若 $a_1$ 相同，则共线。答案按类似方法计算即可。

注意 $a_i \le 10^6$，所以当枚举的点 $i$ 满足 $(i-1)k > 10^6$ 时，$a_1$ 为负，所以此时退出循环。

设 $M=10^6$，则时间复杂度：$\sum\limits_{i=1}^M{\frac{M}{i}}=\Theta(M\log M)$。恰好可通过。

## 代码实现
```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int M = 1e6;
int n, a[200005], b[200005];
long long sum, maxn, t, mp[1000005];
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &b[i]);
        sum += b[i];
    }
    for(int k = 0; k <= 1000000; ++k)  {
        vector<int> v;
        for(int i = 1; (i - 1) * k <= 1000000 && i <= n; ++i) {
            t = a[i] - (i - 1) * k;  // 避免重复计算
            if(t >= 1) {
                if(!mp[t]) v.push_back(t);
                mp[t] += b[i], maxn = max(maxn, mp[t]);
            }
        }
        for(auto p : v)
            mp[p] = 0;  // 不能暴力清空，会 TLE
    }
    printf("%lld\n", sum - maxn);
}
```

---

## 作者：Cypher_404 (赞：2)

# 题解：P10556 [ICPC2024 Xi'an I] Make Them Straight

首先感谢 @ma_niu_bi 的思路。

我不确定数据是否有锅。

## 分析题意

给定一个长度为 $n$ 的非负整数序列 $a$，其中第 $i$ 个元素为 $a_i(1\leq i\leq n)$。

一个序列被定义为“好”的，当且仅当存在一个非负整数 $k(0\leq k\leq 10^6)$ 满足以下条件：

对于所有 $1\leq i\leq n$，$a_{i}=a_{1}+(i-1)k$。

为了使这个序列变成“好”的，对于每个 $i(1\leq i\leq n)$，你可以选择不做任何操作，或者支付 $b_i$ 个硬币来用任意非负整数替换 $a_i$。

求最小成本是多少。

### 思路

由题：
$$
a_i=a_1+(i-1)k
$$

$$
a_i\le 10^6
$$

可得：
$$
a_1+(i-1)k\le 10^6
$$
推出：
$$
i\le \frac{10^6-a_1}{k}+1
$$
所以枚举 $k$，$i$ 只用枚举到 $\frac{10^6}{k}$。通过 $k$ 和 $i$ 计算出 $a_1$ 即可。

时间复杂度： 
$$
\sum_{k=1}^{10^6} \frac{10^6}{k}=10^6\times \log 10^6
$$
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//没准是好习惯？
int n;
int a[200050];
int b[200040];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
	}//输入部分不讲了
	int minn=LONG_LONG_MAX;//被扶苏的问题（P1253）坑了以后的后遗症
	for(int st=0;st<=1050;st++)//枚举第一个数（题目要求非负）
	for(int i=0;i<=min(1050ll/*统一数据类型需要在数字后面+ll*/,1000000/n);i++)
	{
		int num=0;
		for(int j=1;j<=n;j++)//暴力跑
		{
			if(st+(j-1)*i!=a[j])
			{
				num+=b[j];
				if(num>minn)//比最小值还大直接跳出
				{
					goto fuck;//别在意，goto用多了
				}
			}
		}
		minn=min(minn,num);
		fuck:;
	}
	cout<<minn;//输出
	return 0;
}
```

然后惊奇的发现可以 AC。

[AC记录](https://www.luogu.com.cn/record/161122076)

---

## 作者：_Hzq_ (赞：1)

# P10556 \[ICPC 2024 Xi'an I] Make Them Straight 题解

### 分析题意

题目中要求 $a_{i}=a_{1}+(i-1)k$，变形后即为 $a_{i}=a_{i-1}+k$，也就是要求将 a 数组变为一个差为 $k%=$ 的等差数列的最小代价。

### 具体做法

由于 $k$ 非负，所以 $a$ 数组是一个上升的等差数列。题目中提到 $0\leq a_i\leq 10^6$，所以 $a_{n}\leq10^6$，带入 $a_{i}=a_{1}+(i-1)k$ 中，即为 $a_{1}+(n-1)k\leq10^6$，又因为 $a_{1}$ 也是可变的，最小为 $0$，所以 $(n-1)k\leq10^6$，进而得 $k\leq10^6/(n-1)$。可以发现 $k$ 的取值范围是比较小的，故我们可以枚举 $k$ 来求得答案。\
枚举时，我们把 $a_{i}$ 全部减去 $(i-1)k$，存在 $temp$ 数组中，再用一个桶来记 $temp$ 中每一种树的花费。要得到一个等差数列，就要让 $temp$ 中每一个数相等，花费的最小代价就为改变每一个数的总代价减去刚才用桶记录的最大花费，因为最大的花费可以不使用，便可以得到最小花费。

### 代码

```cpp line-numbers
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+7;
int n,a[N],b[N],temp[N],maxk,val[N],res=LLONG_MAX,sum;
signed main()
{
	cin >> n;
	int i,j,k;
	for(i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(i=1;i<=n;i++) scanf("%lld",&b[i]),sum+=b[i];//求总花费
	maxk=1e6/（n-1）;
	for(k=0;k<=maxk;k++)
	{
		int maxn=LLONG_MIN;
		for(i=1;i<=n;i++)
		{
			temp[i]=a[i]-(i-1)*k;
			if(temp[i]>=0) 
			{
				val[temp[i]]+=b[i]; //记录改变每一种数的总花费
				maxn=max(maxn,val[temp[i]]);
			}
		}
		res=min(res,sum-maxn);
		for(i=1;i<=n;i++)//清空桶
			if(temp[i]>=0) 
				val[temp[i]]=0;
	}
	cout << res << endl;
	return 0;
}
```

## 注意

- 总花费有可能超过 $int$ 数据范围，要使用 $long long$。
- $temp$ 数组有可能为负，要特判才能存入桶中。
- 直接使用 $memset$ 清空数组会超时，要手动清空。

---

## 作者：鸡枞_ (赞：1)

# P10556 [ICPC2024 Xi'an I] Make Them Straight
## 题意
给定一个非负整数序列 $a$。对于每一个 $a_i$，可以花费 $b_i$ 的代价将 $a_i$ 修改为任意非负整数，求最小的代价，使得序列 $a$ 变为一个各项非负的等差数列。
## 思路
注意到序列是非负的，所以公差 $d$ 应该满足 $n \times d \leq 10^6$，此处 $10^6$ 是 $a_i$ 的取值上界。范围很小，可以直接枚举公差来计算代价。

计算代价时，把每一个 $a_i$ 减去 $i \times d$，问题就可以从等差变为相等，便于统计代价。具体方法见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;

const int MAXN = 2e5 + 10;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

mt19937 rnd(114514);

void solve()
{
    ll n;
    cin >> n;

    vector<ll> a(n + 1, 0), b(n + 1, 0);
    ll sum = 0;
    for(ll i = 1; i <= n; ++i) cin >> a[i];
    for(ll i = 1; i <= n; ++i)
    {
        cin >> b[i];
        sum += b[i];
    }

    ll ans = INFLL;

    for(ll i = 0; i * n <= 1e6; ++i)
    {
        auto f = a;
        map<ll, ll> cnt;
        for(ll j = 1; j <= n; ++j)
        {
            f[j] -= j * i;
            cnt[f[j]] += b[j];
        }

        ll res = INFLL;

        for(ll j = 1; j <= n; ++j)
        {
            res = min(res, sum - cnt[f[j]]);
        }

        ans = min(ans, res);
    }

    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int Task = 1;
    // cin >> Task;
    while(Task--)
    {
        solve();
    }

    return 0;
}
```

---

