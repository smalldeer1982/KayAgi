# [ABC186D] Sum of difference

## 题目描述

### 题意简述
输入 $n$ 个整数 $a_1,a_2,...a_n$，

求在满足 $1 \leq i < j \leq n$ 的所有 $\lvert a_i-a_j \rvert$ 的和 $X$ 。

即求 $X=\sum_{i=1}^{n-1}\sum_{j=i+1}^{n} \lvert a_i-a_j\rvert$ 。

## 样例 #1

### 输入

```
3
5 1 2```

### 输出

```
8```

## 样例 #2

### 输入

```
5
31 41 59 26 53```

### 输出

```
176```

# 题解

## 作者：loser_seele (赞：2)

把数据预先排序并不会影响答案，于是 $ a $ 单调不减，可以把绝对值符号去掉，原式子变为求 $ \sum_{i=1}^{N-1}\sum_{j=i+1}^{N}\ (a_j-a_i) $。

而 $ \sum_{i=1}^{N-1}\sum_{j=i+1}^{N}\ (a_j-a_i)=\sum_{i=1}^{N}(\sum_{j=i+1}^{N}\ a_j-(N-i)\times a_i)$，于是可以预处理前缀和 $ s $，式子变为 $ \sum_{i=1}^{N}(s_n-s_i-(N-i)\times a_i) $，然后枚举每个 $ i $ 即可 $ \mathcal{O}(1) $ 计算出后面的答案。

时间复杂度 $ \mathcal{O}(n\log{n}) $，来自排序的复杂度，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
#define int long long
int a[maxn],sum[maxn];
signed main()
{
	int t=1;
	while(t--)
	{
    int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i];
    sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
    sum[i]=sum[i-1]+a[i];
    int ans=0;
    for(int i=1;i<=n;i++)
    ans+=sum[n]-sum[i]-(n-i)*a[i];
    cout<<ans<<'\n';;
    }
}
```


---

