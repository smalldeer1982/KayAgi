# RationalLee

## 题目描述

Lee just became Master in Codeforces, and so, he went out to buy some gifts for his friends. He bought $ n $ integers, now it's time to distribute them between his friends rationally...

Lee has $ n $ integers $ a_1, a_2, \ldots, a_n $ in his backpack and he has $ k $ friends. Lee would like to distribute all integers in his backpack between his friends, such that the $ i $ -th friend will get exactly $ w_i $ integers and each integer will be handed over to exactly one friend.

Let's define the happiness of a friend as the sum of the maximum and the minimum integer he'll get.

Lee would like to make his friends as happy as possible, in other words, he'd like to maximize the sum of friends' happiness. Now he asks you to calculate the maximum sum of friends' happiness.

## 说明/提示

In the first test case, Lee should give the greatest integer to the first friend (his happiness will be $ 17 + 17 $ ) and remaining integers to the second friend (his happiness will be $ 13 + 1 $ ).

In the second test case, Lee should give $ \{10, 10, 11\} $ to the first friend and to the second friend, so the total happiness will be equal to $ (11 + 10) + (11 + 10) $

In the third test case, Lee has four friends and four integers, it doesn't matter how he distributes the integers between his friends.

## 样例 #1

### 输入

```
3
4 2
1 13 7 17
1 3
6 2
10 10 10 10 11 11
3 3
4 4
1000000000 1000000000 1000000000 1000000000
1 1 1 1```

### 输出

```
48
42
8000000000```

# 题解

## 作者：budaiyanjing (赞：3)


   前 $k$ 大的数每个数单独放在一个瓶子里作为最大值出现，并且尽可能优先放在体积小的瓶子里，这样他可能既作为最大值也作为最小值，产生双倍贡献。
   其次，在放再从最小值放，优先将小的值放在数量多的瓶子里，这样可以快速跳过一些比较小的值，让后面的瓶子的最小值变得更大。


```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long i64;

const int N = 2e5 + 10;

int n, k;
int a[N], b[N];

void solve() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    for (int i = 1; i <= k; i ++ ) scanf("%d", &b[i]);

    sort(a + 1, a + n + 1);
    sort(b + 1, b + k + 1);
    
    i64 ans = 0;
    for (int i = n, j = 1; j <= k; i -- , j ++ ) {
        ans += a[i];
        if (! -- b[j]) ans += a[i];
    } 

    for (int i = k, j = 1; i; i -- ) 
        if (b[i]) ans += a[j], j += b[i];

    printf("%lld\n", ans);
}

int main() {
    int _; scanf("%d", &_);
    while (_ -- ) solve();
    return 0;
}
```


---

## 作者：JWRuixi (赞：0)

~~我不知道该说什么……~~

- 题意

给定长度为 $n$ 的序列 $a$，将 $a$，分为 $m$ 个集合，是的第 $i$ 个集合的大小为 $b_i$，定义集合 $S$ 的价值为 $\max\limits_Sa_i+\min\limits_Sa_i$，求 $m$ 个集合的最大价值。

- 分析

考虑直接贪心，先选前 $m$ 大作为最大值。

然后考虑选最小值，我们考虑将 $a$ 排序，按 $b_i$ 从大到小选，每次选一个长度为 $b_i$ 的连续段，正确性显然。

注意特判 $b_i=0$ 的点即可。

复杂度 $\mathcal O(n\log n)$。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
#define writesp(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n')
#define FileIO(ch) freopen(ch".in", "r", stdin), freopen(ch".out", "w", stdout)
using namespace std;

namespace IO {
#define gh() getchar()
    inline long long read() {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    template <typename _Tp>
    inline void write(_Tp x) {
    	static char stk[64], *top = stk;
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        do *top++ = x % 10, x /= 10;
        while (x);
        while (top != stk) putchar((*--top) | 48);  
    }
}

using IO::read;
using IO::write;

const int maxn(2e5 + 500);
int n, a[maxn], b[maxn], m, k;
LL ans;

inline void slv () {
	n = read(), m = read(), ans = k = 0;
	for (int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) b[i] = read() - 1, k += !b[i];
	sort(b + 1, b + m + 1, [](const int &x, const int &y) { return x > y; });
	for (int i = 1; i <= m; i++) ans += a[n - i + 1];
	for (int i = 1; i <= k; i++) ans += a[n - i + 1];
	for (int i = 1, j = 1; i <= m; i++) if (b[i]) ans += a[j], j += b[i];
	writeln(ans);
}

int main() {
	int T = read();
	while (T--) slv();
}
// I love WHQ!
```

---

## 作者：11D_Beyonder (赞：0)

### Idea
&emsp;&emsp;显然要让 $k$ 个最大的 $a_i$ 发挥作用，让 $k$ 个最小的 $a_i$ 尽可能少量的产生贡献。

&emsp;&emsp;对于 $w_i=1$ 的袋子，将最大的 $a_i$ 放入，产生的贡献为 $2a_i$，较大值直接产生两倍贡献，这肯定是最优的；对于 $w_i>1$ 的袋子，将最大的 $a_{i(\max)}$ 放入，然后将最小的 $a_{i(\min)}$ 放入，中间依次填充较小的 $a_i$，这样就能尽可能屏蔽 $k$ 个最小的 $a_i$ 产生的贡献。

###  Code

```cpp
/******************************************************************
Copyright: 11D_Beyonder All Rights Reserved
Author: 11D_Beyonder
Problem ID: CF1369C
Date: 01/14/2020
Description: Greedy, Math
*******************************************************************/
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200006;
int _;
ll a[N],w[N];
int n,k;
int main(){
	for(cin>>_;_;_--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=k;i++){
			cin>>w[i];
		}
		ll ans=0;
		int l=1,r=n;
		//从大到小排
		sort(a+1,a+1+n,greater<ll>());
		sort(w+1,w+1+k,greater<ll>());
		for(int i=k;i>=1;i--){
			if(w[i]==1){
				//先将最大的几个放入w=1中
				//贡献为2倍
				ans+=2*a[l++];
			}else{
				break;
			}
		}
		for(int i=1;i<=k;i++){
			if(w[i]==1){
				break;
			}else{
				//将最大的先放入 再放入最小的
				//中间w-2个用小的填补 相当于小的贡献被忽略了
				ans+=a[l++]+a[r--];
				r-=w[i]-2;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```



---

## 作者：zhangyuxing (赞：0)

考虑贪心，则肯定第一步对a数组进行排序，推导过程当中使用降序

从简单情况入手，首先考虑分成两组的情况

设要将 $n$ 个数分为 $i$ 个和 $n-i$ 个，不妨设 $i<\frac{2}{n}$ ，则考虑以下几种选法

$Case 1:{a_1}$~${a_i}$ ， $a_{i+1}$~$a_n$，此时$Ans={a_1}+{a_i}+a_{i+1}+{a_n}$

$Case 2:a_1$~${a_{n-i}}$ ， $a_{n-i+1}$~$a_n$，此时$Ans={a_1}+{a_{n-i}}+a_{n-i+1}+{a_n}$

根据 $i<\frac{2}{n}$ 得 $i<n-i$ 得 $a_i\geq{a_{n-i}},a_{i+1}\geq{a_{n-i+1}}$，所以显然应该优先选择情况1，根据这两组比较得出结论，应该将小的数集中排在需求量大的人那里。

$Case 3:$ 将$Case 2$ 中的 $a_2$ 与 $a_{n-i+1}$ 调换，则此时 $Ans=a_1+a_2+a_{n-i+1}+a_n$，比 $Case 2$ 更优。

所以我们发现，将最大的几个数分别分在不同的人手中，也就是把 $a_1$ ~ $a_k$ 给不同的k个人。同时根据将小的数集中排在需求量大的人那里，将其余越小的数给需求量越大的人。

代码实现中因为懒得写cmp使用了升序，同时特判 $w=1$ 时应优先选取尽量大的值，因为此时最大值与最小值相同。

code:
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[200050],w[200050];
int main()
{
    int t,n,k,l,r,i;
    long long ans;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        for(i=1;i<=n;++i)scanf("%d",a+i);
        for(i=1;i<=k;++i)scanf("%d",w+i);
        sort(a+1,a+n+1);sort(w+1,w+k+1);
        ans=0;i=1;
		while(w[i]==1)
        {
            ans+=2ll*a[n];
            --n;++i;
        }
       	l=1;r=n;
        while(i<=k)
        {
            ans+=a[l]+a[r];
            l+=w[k]-1;--r;
            --k;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

