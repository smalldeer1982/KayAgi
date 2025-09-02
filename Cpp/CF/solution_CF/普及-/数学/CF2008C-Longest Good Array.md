# Longest Good Array

## 题目描述

Sakurako 今天在研究数组问题。我们说一个数组 $a$ 是“优秀的”，当且仅当：

- 这个数组是严格递增的，也就是对每个 $2 \le i \le n$，都有 $a_{i - 1} < a_i$；
- 相邻元素的差值也是严格递增的，即对于每个 $2 \le i < n$，都有 $a_i - a_{i-1} < a_{i+1} - a_i$。

Sakurako 给定了两个边界值 $l$ 和 $r$，她希望构造一个最长的优秀数组，使得数组中的每个元素 $a_i$ 满足 $l \le a_i \le r$。

请你帮助 Sakurako 找出在给定 $l$ 和 $r$ 条件下，最长优秀数组的长度。

## 说明/提示

例如，当 $l=1$ 和 $r=5$ 时，一个可能的优秀数组是 $(1, 2, 5)$。可以证明，给定这些边界值，不存在长度为 $4$ 的优秀数组。

当 $l=2$ 和 $r=2$ 时，唯一的数组是 $(2)$。

当 $l=10$ 和 $r=20$ 时，一个唯一的优秀数组是 $(10, 11, 13, 16, 20)$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
1 2
1 5
2 2
10 20
1 1000000000```

### 输出

```
2
3
1
5
44721```

# 题解

## 作者：chenxi2009 (赞：3)

## Upd
修改了错误。感谢@Cxys10 的提醒。
## Upd
上次修改代码没有保存到。
# 思路
一个“好的数组”，根据题意，要求严格递增且相邻两项之间的差严格递增。也就是说，$a_2-a_1$ 至少为 $1$，$a_3-a_2$ 至少为 $2$，归纳得出 $a_{i+1}-a_i$ 至少为 $i$。题意要让数组在指定值域内尽可能长。根据前面的推论发现
$$
r-l\ge a_n-a_1\ge\sum_{i=1}^{n-1}i\\
=\frac{n\times(n-1)}{2}
$$
视 $r-l+1$ 为常数，这就是一个关于 $n$ 的一元二次方程，解出来向下取整即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,l,r,x;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%d%d",&l,&r);
		r = r - l;
		x = int((1.0 + sqrt(8.0 * r + 1.0)) / 2.0);
		printf("%d\n",x);
	}
	return 0;
}
```

---

## 作者：alan1118 (赞：2)

简单构造题。

## 题意

给定 $l,r$，请你构造一个数列，第一项为 $l$，最后一项为 $r$。

这个数列有两个要求：

+ 数列是递增的。

+ 数列中相邻两项的差也是递增的。

也就是说对于所有元素，$a_{i-1}<a_i,\ a_i-a_{i-1}<a_{i+1}-a_i$。

请你求出这个数列最长的长度。

## 思路

首先如果想让数列最长，那么相邻两个元素的差就要尽可能小，这样我们就可以让他们的差为 $1,2,3,\dots$，一位一位算出来。

于是问题就来了：如果这样算下去没法得到 $r$ 怎么办？其实也很好解决，我们只需要让倒数第二个不超过 $r$ 的数 $x$ 加 $r-x$ 就可以了。如果不理解可以看下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vidf5asn.png?x-oss-process=image/resize,m_lfit,h_400,w_10000)

因此，当 $l=1,r=9$ 时，数列最长为 $4$。

所以我们只需要循环找到倒数第二个数，最后再加一就可以了。

但是要注意，如果刚好能加到 $r$，就不再需要加一了。

#### 时间复杂度

我们可以计算一下，当 $l=1,r=10^9$ 时，需要循环 $10^5$ 次，算上 $t$，最多到 $10^9$，题目里给的时间限制是 $2.00s$，可以通过。

## Code

``` cpp
#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int l, r;
		cin >> l >> r;
		int i;
		for(i = 1; l+i+i+1 <= r; i++) l += i;
		cout << i+(l!=r) << endl;
	}
	return 0;
}
```

---

## 作者：liuzhengtao (赞：1)

## 题目大意
鉴于这道题并没有提供题目翻译，那么本蒟蒻在这篇题解先大概说一下题目要求什么。

首先会给出边界 $l$ 和 $r$，请你构造出一个数列，数列满足单调递增，并且这个数列每相邻的两个元素的差值从左到右依次递增。对于所有的元素，其值都不大于 $r$ 且不小于 $l$，请求出这个序列的最大长度。
## 思路分析
首先，这个数列一定是像 $[1,2,4,7,11,16]$ 这种的，并且第一项是 $l$，而我们可以知道在这个数列中每一项都可以求出，因为差值是递增的，也就是总的差值可以用等差数列求和公式得出，表示为 $\displaystyle \frac{n×(n−1)}{2}$，也就是第 $n$ 项为 $l+\displaystyle \frac{n×(n−1)}{2}≤r$。接下来看代码。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,l,r,x;
int main()
{
	cin>>T;
	while(T--)
    {
		cin>>l>>r;
		int a=r-l+1;
		ans=int((1.0 + sqrt(8.0*a-7.0))/2.0);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

为了让构造出的序列更长，肯定使 $a_1=l$，且相邻两数的差值为正整数序列，那么 $a_n=l+\dfrac{n(n-1)}{2}\le r$。解不等式得到 $n$ 的上界即可。

# Code

```cpp
#include<bits/stdc++.h>
int T,l,r;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&l,&r);
		printf("%d\n",(int)((sqrt(1+8.0*(r-l))-1)/2)+1);
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

为了让构造出的序列更长，可以发现最优的数列一定为 $[1,2,4,7,11,16]$，则该数列的第 $i$ 项为 $\frac{i \times (i - 1)}{2} + 1$。

显然具有单调性，可以二分求解。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
bool check ();
void findans ();
bool check (ll x, ll r) {
	if (1 + (x * (x - 1)) / 2 <= r) return true;
	return false;
}
void findans() {
	ll L, R;
	cin >> L >> R;
	R -= L - 1; L = 1;
	ll l = 1, r = 6e4;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (check (mid, R)) l = mid + 1;
		else r = mid - 1;
	}
	cout << r << endl;
}
int main() {
	ll T;
	cin >> T;
	while (T --) findans ();
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路
由于要求序列递增且差值递增，需要让序列长度尽可能长，因此差值应尽可能小。由于差值最小为 $1$，所以使 $a_2 - a_1 = 1$，$a_3 - a_2 = 2$，以此类推。观察到数列长度为 $n$ 时 $\sum_{i = 2} ^ n a_{i+1} - a_i = \sum_{i=1} ^ {n - 1} i = \dfrac{n(n - 1)} 2$，所以可以取 $\max n$ 使 $\dfrac{n(n - 1)} 2 \le r - l$。二分或解方程 $\dfrac{n ^ 2} 2 - \dfrac n 2 = r - l$ 即可。
### 代码
二分实现。
```cpp
#include <cstdio>
#include <algorithm>

constexpr int N = 1e5;
int T, l, r; long long a[N];
signed main()
{
    for (int i = 1; i < N; ++i)
        a[i] = i * (i - 1ll) >> 1;
	for (scanf("%d", &T); T--; )
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", std::upper_bound(a + 1, a + N, r - l) - a - 1);
    }
    return 0;
}
```

---

## 作者：linjinkun (赞：0)

简单构造贪心题。

首先我们要知道，要使数列最长，那这个数列任意两个相邻的数他们的差只会以最慢的速度递增，也就是说，要使这个数列是这样的：$a_2 = a_1+1,a_3 = a_2+2,a_4 = a_3+3$，这样子，你就会发现它们的差值形成了一个差值为 $1$ 的等差数列，那么我们运用等差数列求和公式，就可以得知，如果这个序列长度为 $mid$，那么这个序列的尾项就是 $a_1+mid \times (mid-1) \div 2$。
于是我们发现他有单调性，然后就可以二分了。

**注意，要开 ```long long```。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
signed main()
{
	int _;
	scanf("%lld",&_);
	while(_--)
	{
		int L,R;
		scanf("%lld %lld",&L,&R);
		int l = 1,r = 50000;
		int ans = 0;
		while(l<=r)
		{
			int mid = l+r>>1;
			if(L+mid*(mid-1)/2<=R)
			{
				ans = mid;
				l = mid+1;
			}
			else
			{
				r = mid-1;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Lfz312g (赞：0)

# CF2008C Longest Good Array
## 题意简述
给出边界 $l$ 和 $r$，构造一个递增数列 $a$，相邻元素的差值也递增，问对于所有 $a_i$，满足 $l \le a_i \le r$ 时，$a$ 的最大长度。
## 题目分析
为了让生成的数列长度最大，可以发现最优的数列一定为 $[1,2,4,7,11,16]$，该数列的第 $i$ 项为 $\displaystyle \frac{i \times (i - 1)}{2}+1$。  
显然具有单调性，可以二分求解。当然暴力枚举也行，时间复杂度为 $O(t)$。  
这里给出二分实现代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool check(long long x,int r)
{
	if (1+(x*(x-1))/2<=r) return true;
	return false;
}
void solve()
{
	int L,R;
	cin>>L>>R;
	R-=L-1;
	L=1;
	int l=1,r=60000;
	while (l<=r)
	{
		long long mid=(l+r)/2;
		if (check(mid,R)) l=mid+1;
		else r=mid-1;
	}
	cout<<r<<endl;
}
int main()
{
	int t;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

---

