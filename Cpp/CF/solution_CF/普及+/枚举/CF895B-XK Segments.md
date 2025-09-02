# XK Segments

## 题目描述

While Vasya finished eating his piece of pizza, the lesson has already started. For being late for the lesson, the teacher suggested Vasya to solve one interesting problem. Vasya has an array $ a $ and integer $ x $ . He should find the number of different ordered pairs of indexes $ (i,j) $ such that $ a_{i}<=a_{j} $ and there are exactly $ k $ integers $ y $ such that $ a_{i}<=y<=a_{j} $ and $ y $ is divisible by $ x $ .

In this problem it is meant that pair $ (i,j) $ is equal to $ (j,i) $ only if $ i $ is equal to $ j $ . For example pair $ (1,2) $ is not the same as $ (2,1) $ .

## 说明/提示

In first sample there are only three suitable pairs of indexes — $ (1,2),(2,3),(3,4) $ .

In second sample there are four suitable pairs of indexes $ (1,1),(2,2),(3,3),(4,4) $ .

In third sample every pair $ (i,j) $ is suitable, so the answer is $ 5*5=25 $ .

## 样例 #1

### 输入

```
4 2 1
1 3 5 7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 2 0
5 3 1 7
```

### 输出

```
4
```

## 样例 #3

### 输入

```
5 3 1
3 3 3 3 3
```

### 输出

```
25
```

# 题解

## 作者：LiRewriter (赞：4)

蛮有趣的一道题。

先来说说题意，大概是：对一个数组a，定义符合条件的二元组$(i, j)$表示恰好存在$k$个整数，满足$a_i \leq y \leq a_j$且$y$为$x$的倍数，求符合条件的二元组数量。

注意二元组是互异并且考虑顺序的。


---

一上来有些懵逼，不妨先找找规律。

我们知道，假定存在$k$个这样的整数，那么首先$[L, L + (k - 1) \* x]$一定是符合条件的一个区间，然后考虑拓展，右端点范围应当是$[L + (k - 1) \* x, L + k \* x - 1]$，因为这个时候一定能找到符合条件的$k$个整数。

接下来的问题就是如何找到$L$。假如$a[i]$不是$x$的倍数，那么$a[i]$本身不会算到$k$个数中间去，所以此时$L = (a[i] / x + 1) \* x$；否则，$a[i]$也是$k$的一份子，所以$L = a[i]$。

对数组排序之后，我们可以遍历一遍整个数组，然后对每一个数求一下在$[L + (k - 1) \* x, L + k \* x - 1]$范围内有多少数即可。

最后考虑如何实现。由于我们只是统计个数，所以我们可以二分查找出$l = L + (k - 1) \* x$，$r =  L + k \* x $第一个大于等于这两个数的数所在的位置相减即可。可以采用algorithm库的lower\_bound实现。

当然这样有个问题，就是对k = 0的情况应当有一些特判，此时我们发现如果$a[i]$是$x$的倍数，区间就是$a[i], a[i]$那么结果为0，而此时$L = a[i]$；否则区间应当是$a[i], L$，此时由于$k = 0$所以$L = r$，所以只需要对$l$加一个特判即可。


---

AC代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL a[100003], ans;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    LL n, x, k;
    cin>>n>>x>>k;
    for(int i = 1; i <= n; ++i) cin>>a[i];
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; ++i) {
        LL L = (a[i] % x) ? ((a[i] / x + 1) * x) : a[i];
        LL l = L + (k - 1) * x, r = L + k * x;
        if(!k) l = a[i];
        ans += lower_bound(a + 1, a + n + 1, r) - lower_bound(a + 1, a + n + 1, l);
    }
    cout<<ans<<endl;
    return 0;
} 
```

---

## 作者：liboxuan223 (赞：3)

# 思路
第一反应肯定是暴力，算一下，是 $O({n^2})$，肯定不行。

------------

仔细想想，升级一下。
我们可以发现，$a$ 数组是不会变的，我们可以先排序，然后枚举 ${a_i}$，由于给出了 $k$，所以可以求出右端点，再二分查找左端点即可。

别忘了特判 $k=0$ 的情况哦。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 10;
ll a[N];
ll n, x, k;
ll ans = 0;

int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> x >> k;
	for (ll i = 1;i <= n; i ++) {
		cin >> a[i];
	}
	
	sort(a + 1, a + n + 1);
	
	for(ll i = 1;i <= n; i ++) {
		ll l1,l2, r;
		if(a[i] % x) {
			l1 = (a[i] / x + 1) * x;
		}else {
			l1 = a[i];
		}
		l2 = l1 + (k - 1) * x;
		r = l1 + k * x;
		if(!k) l2 = a[i]; // 特判 k = 0 的情况 
		
		ans += lower_bound(a + 1, a + n + 1, r) - lower_bound(a + 1, a + n + 1, l2);
	}
	
	cout << ans;
	
	return 0;
}
``````

---

## 作者：ZLCT (赞：0)

# CF895B XK Segments
## 题目翻译
给定一个长度为 $n$ 的序列 $a$，求有多少个二元组 $(i,j)$ 满足 $a_i\le a_j$ 且 $[a_i,a_j]$ 中有 $k$ 个 $x$ 的倍数。
## 思路
### 暴力
这道题暴力思路很简单，就是枚举 $i,j$，判断是否满足条件即可。
### 初步优化
我们可以观察到如果确定 $a_i$，那么 $a_j$ 的取值一定是一段连续的区间。于是我们可以先排序，每次如果 $[a_i,a_j]$ 中有多于 $k$ 个 $x$ 的倍数则 `continue`。
### 进一步优化
上一步我们把多于 $k$ 的情况优化掉了，这就启发我们把小于 $k$ 的情况也优化掉。然后就想到我们可以二分出第一个满足区间有 $k$ 个 $x$ 的倍数点，然后一直遍历到大于 $k$ 个为止。
### 最终优化
其实上一步优化结束后这个优化就自然浮出水面了。我们可以利用同样的思路去二分最后一个满足条件的点，两个点之间的元素一定都是满足条件的。\
具体实现上我们可以进行上一步的二分操作，只是把 $k$ 改成 $k+1$，最后再减掉当前的即可。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+555;
const int inf=1e18+888;
int n,x,k,a[N],ans;
signed main(){
    cin>>n>>x>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    a[n+1]=inf;
    for(int i=1;i<=n;++i){
        int l=0,ll=0,r=0;
        if(a[i]%x==0){
            l=lower_bound(a+1,a+2+n,a[i]+(k-1)*x)-a;
            ll=lower_bound(a+1,a+2+n,a[i])-a;
            l=max(l,ll);
            r=lower_bound(a+1,a+2+n,a[i]+k*x)-a-1;
            if(l>r)continue;
            ans+=r-l+1;
        }else{
            int y=a[i]/x;y*=x;
            l=lower_bound(a+1,a+2+n,y+k*x)-a;
            ll=lower_bound(a+1,a+2+n,a[i])-a;
            l=max(l,ll);
            r=lower_bound(a+1,a+2+n,y+(k+1)*x)-a-1;
            if(l>r)continue;
            ans+=r-l+1;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

为什么都在用二分？

考虑在 $[l,r]$ 内合法的个数为  $\lfloor \frac{r}{x} \rfloor - \lceil \frac{l}{x} \rceil + 1$。

所以要使得上式值为 $k$，那么可以从大到小枚举 $a_i$，然后用 map 分别存储 $\lfloor \frac{a_i}{x} \rfloor$ 以及 $\lceil \frac{a_i}{x} \rceil$，然后判断将 $a_i$ 设为左端点然后累计合法的右端点个数即可。

注意当 $a_i$ 相同时，要同时统计 $\lfloor \frac{a_i}{x} \rfloor$ 以及 $\lceil \frac{a_i}{x} \rceil$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, x, k;
int a[100010];
map<int, int> s1, s2;

int main() {
	scanf("%d%d%d", &n, &x, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}

	sort(a + 1, a + 1 + n);
	reverse(a + 1, a + 1 + n);
	long long ans = 0;

	for (int i = 1; i <= n; ++i) {
		int cnt = 1;
		s1[a[i] / x]++;
		s2[(a[i] + x - 1) / x]++;
		while (i + 1 <= n && a[i + 1] == a[i]) {
			++i;
			++cnt;
			s1[a[i] / x]++;
			s2[(a[i] + x - 1) / x]++;
		}

		for (int j = i + 1 - cnt; j <= i; ++j)
			ans += 1ll * s1[(a[j] + x - 1) / x + k - 1];
	}

	printf("%lld\n", ans);

	return 0;
}
```

---

## 作者：U•ェ•*U (赞：0)

[我的 CSDN 原文地址，转载请标明](https://blog.csdn.net/LZXLSMLTZLLM/article/details/139448941)

这道题好水，就是不好理解而已……

## 思路
暴力的复杂度是 $n^2$，显然不可能通过。

不难想到先排序，然后再使用二分查找。

发现 $a$ 数组不会变，且枚举 $a_i$ 的过程相当于查找符合条件的区间中元素的个数。

首先排序数组，然后遍历，最后求每个数在这个范围内有多少，就是最后的答案。

当然对于这道题我们为了优化时间复杂度需要用到二分查找，`lower_bound(begin, end, num)` 可以返回一个**有序序列**的不小于 $num$ 的值的地址，不存在则返回 $end$。常用用法：通过返回的地址减去起始地址 $begin$，得到找到数字在数组中的下标。

要开 `long long`。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, x, k, a[100010], cnt;
int main() {
	ios :: sync_with_stdio(false);
	cin >> n >> x >> k;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i ++) {
		int l = (a[i] - 1) / x, r = l + k;
		cnt += lower_bound(a + 1, a + n + 1, (r + 1) * x) - lower_bound(a + 1, a + n + 1, max(r * x, a[i]));
	}
	cout << cnt << endl; 
	return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# CF895B XK Segments 题解

## 题目描述

[CF895B XK Segments ](https://www.luogu.com.cn/problem/CF895B)

## 题目解法

### 朴素想法

最简单的想法就是枚举二元组 $(i,j)$ 的第一项 $i$，然后再枚举 $j$，找到一个满足条件的 $a_j$，然后更新答案。

很明显，该做法的时间复杂度为 $O(n^2)$，无法通过本题。

### 二分

我们发现，$a$ 数组不会更改，并且每次枚举 $a_j$ 的过程相当于查找符合条件的区间中元素的个数。

先算出大于等于 $a_i$ 的第一个 $x$ 的倍数 $a_i$。

$$
\begin{cases}
a_i'=(\lfloor \frac{a_i}{x} \rfloor + 1)\times x & (a_i \not\equiv 0 \mod x)\\ 
a_i'=a_i & (a_i \equiv 0 \mod x) 
\end{cases}
$$

符合条件的区间的左端点 $l=a_i'+(k-1)\times x$。

符合条件的区间的右端点 $r=a_i'+k\times x$。

记得特判 $k=0$ 的情况。

先排序再二分端点，迭代器相减即可。

记得开 `long long`。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, x, k;
vector<int> vc;

signed main()
{
    cin>>n>>x>>k;
    int ans=0;
    for(int i=1, v;i<=n;i++)
        cin>>v, vc.push_back(v);
    sort(vc.begin(), vc.end());
    for(auto i:vc)
    {
        int nx=(i%x)?(i/x+1)*x:i;
        int l=k?nx+(k-1)*x:i, r=nx+k*x;
        auto it1=lower_bound(vc.begin(), vc.end(), r);
        auto it2=lower_bound(vc.begin(), vc.end(), l);
        ans+=it1-it2;
    }
    cout<<ans;
}
```

---

## 作者：andyli (赞：0)

先排序，然后枚举 $j$。对于每个 $a_j$，考虑合法的 $a_i$ 的范围 $\left[l,r\right]$，然后二分即可。  
可以考虑 $a_i'=\lfloor \dfrac{a_i}{x} \rfloor \cdot x$，然后容易发现区间为 $\left(a_i' - k\cdot x , \min\{a_i' - (k-1)\cdot x, a_i\}\right]$。 
```cpp
int main() {
    dR(int, n, x, k);
    dRV(i64, a, n);
    sort(a);
    i64 ans = 0;
    _for (i, n) {
        // [l, r]
        i64 l = a[i] / x * x - i64(k) * x + 1;
        i64 r = min(a[i] / x * x - i64(k - 1) * x, a[i]);
        ans += UB(a, r) - LB(a, l); // upper_bound - lower_bound
    }
    print(ans);
    return 0;
}
```

---

