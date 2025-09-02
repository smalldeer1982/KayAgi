# Ski Resort

## 题目描述

Dima Vatrushin is a math teacher at school. He was sent on vacation for $ n $ days for his good work. Dima has long dreamed of going to a ski resort, so he wants to allocate several consecutive days and go skiing. Since the vacation requires careful preparation, he will only go for at least $ k $ days.

You are given an array $ a $ containing the weather forecast at the resort. That is, on the $ i $ -th day, the temperature will be $ a_i $ degrees.

Dima was born in Siberia, so he can go on vacation only if the temperature does not rise above $ q $ degrees throughout the vacation.

Unfortunately, Dima was so absorbed in abstract algebra that he forgot how to count. He asks you to help him and count the number of ways to choose vacation dates at the resort.

## 说明/提示

In the first test case of the example, Dima can go on any day, so the suitable dates for him are \[1\], \[2\], \[3\], \[1, 2\], \[2, 3\], \[1, 2, 3\].

In the second and fourth test cases of the example, Dima cannot go on any day due to the high temperature, so there are no suitable dates.

In the third test case of the example, Dima can only go on the dates \[1, 2, 3\].

## 样例 #1

### 输入

```
7
3 1 15
-5 0 -10
5 3 -33
8 12 9 0 5
4 3 12
12 12 10 15
4 1 -5
0 -1 2 5
5 5 0
3 -1 4 -5 -3
1 1 5
5
6 1 3
0 3 -2 5 -4 -4```

### 输出

```
6
0
1
0
0
1
9```

# 题解

## 作者：MornStar (赞：4)

# CF1840C Ski Resort 题解

[CF题面](https://codeforces.com/problemset/problem/1840/C)
## 题目大意
给定 $n$，$k$，$q$ 和一个长度为 $n$ 的序列 $a$。

在 $a$ 中选出一个连续的序列，序列的长度需大于等于 $k$ 并且序列中的最大值小于等于 $q$。

求共有多少种选法？
## 思路
我们可以注意到，序列中大于 $q$ 的数将整个序列分成了若干个互不重叠的段。

因为要选择连续的一段，所以选择的序列肯定不能越过大于 $q$ 的数。

对于一个满足条件的子区间，要从中截取一个长度大于等于 $k$ 的区间，有多少种方法呢？很明显，对于一个长度为 $l$ 的子区间，方案总数为：

$$\sum_{i=1}^{l-k+1} i$$

而这个可以预处理出来。
## code
```cpp
// by mornstar
// Jun/06/2023 23:24
#include<bits/stdc++.h>
using namespace std;
long long n,k,q,a[200005],sum[200005],ans,cnt;
int main(){
	for(int i=1;i<=200005;i++)	sum[i]=sum[i-1]+i;
	int T;
	cin>>T;
	while(T--){
		ans=cnt=0;
		cin>>n>>k>>q;
		for(int i=1;i<=n;i++)	cin>>a[i];
		for(int i=1;i<=n;i++){
			if(a[i]>q){
				if(cnt>=k)	ans+=sum[cnt-k+1];
				cnt=0;
			}else{
				cnt++;
			}
		}
		if(cnt>=k)	ans+=sum[cnt-k+1];//末尾区间特判。
		cout<<ans<<endl;
	}
}
```

---

## 作者：hycqwq (赞：2)

## Problem

给定一个序列 $a$，问在其中有多少个连续的长度不小于 $k$ 且所有数不大于 $q$ 的子序列。

## Solution

读入时统计在 $a_i$ 和 $a_i$ 前面有多少个不大于 $q$ 的数，设其为 $d_i$，于是以 $a_i$ 结尾的复合条件的子序列个数为 $\max\{0, d_i - k + 1\}$。累加即可。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
#define elif else if
#define il inline

int t, n, k, q, a[200005];

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> k >> q;
        int d = 0;
        ll ans = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            if (a[i] <= q)
                d++;
            else
                d = 0;
            ans += max(0, d - k + 1);
        }
        cout << ans << endl; 
    }
    return 0;
}
```

---

## 作者：川寰boy (赞：2)

# CF1840C Ski Resort 题解

## 题目大意

共 $T$ 组数据，对于每组数据：

给定 $n, k, q$ 和一个长度为 $n$ 的序列 $a$，在其中选出一个子串，满足子串长度大于等于 $k$，且子串中每个数均小于等于 $q$，求选择子串的方案数。

数据保证 $1\le \sum n\le 2\times 10^5,1\le k\le n$。

## 解题思路

我们可以注意到，大于 $q$ 的数把序列分为很多不重合的合法子串，即我们只需要求每个合法子串中选取子串的方案数，最后求和。


例如，对于样例中第七组数据：

```
6 1 3
0 3 -2 5 -4 -4
```

此时 $q=3$，则序列中大于 $q$ 的数只有 $5$。

它将序列分为两段：`0 3 -2` 和 `-4 -4`。

对于已经寻找到的合法子串（段），再进行下一步的计算。

注意到数据范围中，$n\leq2\times10^5$，不能考虑 $n^2$ 复杂度，应该是要推数学式子。

对于每个合法的长度为 $l$ 的子串，可以选长度为 $l$ 的合法子串（即其本身），可选 $1$ 个，一直选到长度为 $k$ 的合法子串，可选 $(l-k+1)$ 个。

我们在其中选取合法子串的方案数为

$$\Large{\displaystyle\sum^{{l - k + 1}}_{{i = 1}}i}$$

将该和式拆解，得到 $\frac{(l-k+1+1)\times(l-k+1)}{2}$，可以 $O(1)$ 计算。

## 时空复杂度

-   时间复杂度：$O(n)$.
-   空间复杂度：$O(n)$ 或 $O(1)$ 都能实现。

## Code

``` cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10;
const int MOD = 998244353;
const int INF = 0x7fffffff;
const int FillINF = 0x3f3f3f3f;

signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        bool flag = 0;
        int n, k, q, i, j, ans = 0, cnt = 0, flagIndex;
        cin >> n >> k >> q;
        for (i = 0; i < n; i++)
        {
            int s;
            cin >> s;
            if (s <= q && !flag)
            {
                flag = 1;
                flagIndex = i;
                continue;
            }
            if (s > q && flag)
            {
                flag = 0;
                if (k > i - flagIndex)
                {
                    continue;
                }
                ans += (i - flagIndex - k + 2) * (i - flagIndex - k + 1) / 2;
            }
        }
        if (flag)
        {
            flag = 0;
            if (k > i - flagIndex)
            {
                cout << ans << '\n';
                continue;
            }
            ans += (i - flagIndex - k + 2) * (i - flagIndex - k + 1) / 2;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

~~马蜂奇丑轻喷~~

---

## 作者：Jerry_heng (赞：1)

（一）

一段一段找。

固定左节点 $l$，右节点 $r$ 越远越好。

然后 $l=r+1$ 继续搜。

如果 $l$ 和 $r$ 的距离不小于 $k$:

新增 $1+2+...+(r-l+1-k+1)=\frac{(r-l+2-k)\times(r-l+3-k)}{2}$ 个。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,q,a[200001];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld",&n,&k,&q);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		int l=1,r=1,ans=0;
		while(1){
			while(l<=n&&a[l]>q)l++;
			if(l>n)break;
			r=l;
			while(r<n&&a[r+1]<=q)r++;
			if(r-l+1>=k)ans+=(r-l+2-k)*(r-l+3-k)/2;
			l=r+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：linxuanrui (赞：0)

### 思路

十分暴力的想法。

就是二分 + ST 表。先预处理出任意区间的最大值，然后枚举左端点，二分右端点。

时间复杂度：$\mathcal{O}(qn\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
int t,n,k,q,st[200001][31],ans,LOG[200001];
int ask(int l,int r){
	int k = LOG[r - l + 1];
	return max(st[l][k],st[r - (1 << k) + 1][k]);
}
signed main(){
	ios::sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n >> k >> q;
		LOG[0] = -1,ans = 0;
		for(int i = 1;i <= n;i++)cin >> st[i][0],LOG[i] = LOG[i >> 1] + 1;
		for(int j = 1;j <= LOG[n];j++){
			for(int i = 1;i + (1 << j) - 1 <= n;i++){
				st[i][j] = max(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
			}
		}
		for(int i = 1;i + k - 1 <= n;i++){
			int l = i + k - 1,r = n + 1;
			while(r - l > 1){
				int mid = (l + r) >> 1;
				if(ask(i,mid) <= q)l = mid;
				else r = mid;
			}
			if(ask(i,l) <= q)ans += min(l,n) - (i + k - 1) + 1;
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Iniaugoty (赞：0)

# problem

给定 $n$，$k$，$q$ 和一个长度为 $n$ 的序列 $a$。

在 $a$ 中选出一个连续的序列，序列的长度需大于等于 $k$ 并且序列中所有数都不大于 $q$。

问，共有多少种选法？

# solution

组合数学题。

先考虑在单个所有数都不大于 $q$ 的序列中有多少种选法。设其长度为 $len$。

- 若 $len<k$，选出来的序列肯定不满足长度要求，所以答案为 $0$。

- 长度为 $i$ 的连续子序列可以选 $len-i+1$ 个，选的连续子序列最短 $k$，最长 $len$，所以答案为 $\displaystyle\sum_{i=k}^{len}(len-i+1)$。容易发现这是个等差数列，带入求和公式就是 $\dfrac{(len-k+1+len-len+1)(len-k+1)}{2}=\dfrac{(len-k+2)(len-k+1)}{2}$

找到原序列的所有满足条件的连续子序列（找出来的序列两边的数都要比 $q$ 大），将每个的答案加起来即可。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int T,n,k,q,a[N],len,ans;
signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		ans=len=0;\\ans 是答案，len 是目前找到的连续序列的长度
		cin>>n>>k>>q;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++){
			if(a[i]<=q) len++;
			else{//已经找到一个连续序列了，加上答案
				if(len>=k) ans+=(len-k+2)*(len-k+1)/2;
				len=0;//找下一个连续序列，长度清零
			}
		}
		if(len>=k) ans+=(len-k+2)*(len-k+1)/2;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：0)

发一波最笨的办法：st 表加双指针。

看这题的时候感觉它就是个 RMQ（静态区间最值），所以就写了个 st 表。不会的看 [P3865](https://www.luogu.com.cn/problem/P3865)，这里就不再讲了。

可以对于每个 $l$，二分查找出最靠后的 $r$ 满足区间 $[l,r]$ 的最大值 $\le q$。但是这样时间复杂度会带两个 $\log$，比较慢，所以就改用双指针查找了。

对于每个 $l$ 查找出上述的 $r$ 之后，不难发现区间 $[l,l+k-1],[l,l+k],[l,l+k+1],\dots,[l,r]$ 都满足要求，所以把这些的数量都加上就行了。

最后提醒一句：**十年 OI 一场空，不开 long long 见祖宗！**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int t,n,k,q,a[200010],st[200010][20];
void pre()
{
    for(int i=1;i<=n;i++)st[i][0]=a[i];
    int len=2;
    for(int i=1;len<=n;i++)
    {
        for(int l=1;l+len-1<=n;l++)
            st[l][i]=max(st[l][i-1],st[l+(len>>1)][i-1]);
        len<<=1;
    }
}
int query(int l,int r)
{
    int m=0,len=1;
    while((len<<1)<=r-l+1)m++,len<<=1;
    return max(st[l][m],st[r-len+1][m]);
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&k,&q);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        pre();
        int l=1,r=1;
        long long ans=0;
        for(;l<=n;l++)
        {
            if(r<l)r++;
            while(r<=n)
            {
                if(query(l,r)>q)break;
                r++;
            }
            ans+=max(0,r-l+1-k);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：FinderHT (赞：0)

### 思路分析：

数学题，我们可以设区间的长度为 $l$，对于长度为 $k$ 的区间，选择方式有 $l-k+1$ 个，对于长度为 $k+1$ 的区间，选择方式有 $l-k$ 个，故总数为 $\sum _{i=1} ^ {l-k+1}$。根据高斯求和化解可得 $\frac{(l-k+2)(l-k+1)}{2}$。

### Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
void solve(){ 
    int n,k,q;
    scanf("%d%d%d",&n,&k,&q);
    vector<int>a(n+1);
    for(int i=1;i<=n;i++)cin>>a[i];
    ll ans=0;//数据范围很大，会爆int
    for(int i=1;i<=n;i++){
        if(a[i]<=q){//保证区间最大值小于等于q
            ll l=0;
            for(;i<=n&&a[i]<=q;i++)l++;//求出l
            if(l>=k)ans+=(l-k+2)*(l-k+1)/2;//如果区间满足条件，维护答案
   	    }		
    }
    printf("%lld\n",ans);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--)
		solve();
    return 0;
}

```

# 完结撒花！

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
我们对于每一个 $a_i$ 大于 $q$ 都不能选，那么就相当于用不能选的 $a_i$ 把序列分割。

对于我们可以选的序列假设长度 $len$ 大于等于 $k$，那么我们可以选 $1+2+3+\dots+len-k+1$，如果小于 $k$ 就不能选了，最后遍历一遍记录小于 $k$ 的连续个数就行了。

最后注意 $ans$ 要开 `long long`。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
i64 a[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		int n, k, q;
		cin >> n >> k >> q;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		i64 cnt = 0, ans = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i] > q) {
				if (cnt >= k) {
					i64 len = cnt - k + 1;
					ans += (len + 1) * len / 2;
				}
				cnt = 0;
			} else {
				cnt++;
			}
		}
		if (cnt >= k) {
			i64 len = cnt - k + 1;
			ans += (len + 1) * len / 2;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

Dima 可以在第 $1$ 至 $n$ 天中选取一段天数不小于 $k$ 的连续的假期，并且这段区间内每天的温度 $a_i$ 都不大于 $q$，求有多少中选择方案。

**解题思路**

我们可以寻找所有区间 $l$ 至 $r$ 长度为 $\text{tot}$ 并满足 $a_{l-1},a_{r+1}>q$、$\text{tot}\ge k$ 且 $a_i\le q(l\le i\le r)$，那么这段区间内的方案为 $1+2+\cdots+(\text{tot}-k+1)$ 即 $(\text{tot}-k+1)\times(\text{tot}-k+2)\div 2$，每次计算完后不要忘记将 $\text{tot}$ 变为 $0$。


**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N];
signed main() {
    int t;
    cin >> t;
    while(t--) {
        int n, k, q, tot = 0, ans = 0;
        cin >> n >> k >> q;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            if(a[i] <= q) {
                ++tot;
            } else {
                if(tot >= k) {
                    ans += (tot - k + 1) * (tot - k + 2) / 2;
                }
                tot = 0;
            }
        }
        if (tot >= k) {
            ans += (tot - k + 1) * (tot - k + 2) / 2;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

