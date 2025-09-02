# [Algo Beat Contest 002 F] Famous Basketball Games

## 题目背景

| Problem | Score | Idea | Std | Data | Check | Solution |
| :----------------------------------: | :---: | :---------------------------------------------------: | :---------------------------------------------------: | :---------------------------------------------: | :-------------------------------------------------: | :----------------------------------------------------------: |
|  $\text{F - Famous Basketball Games}$  | $550$ | [篮网总冠军](https://www.luogu.com.cn/user/547238) | [篮网总冠军](https://www.luogu.com.cn/user/547238) | [篮网总冠军](https://www.luogu.com.cn/user/547238) | [LostKeyToReach](https://www.luogu.com.cn/user/764666)  | [Link](https://www.luogu.com.cn/article/k8hp1mrf) by [篮网总冠军](https://www.luogu.com.cn/user/547238)


小 A 可喜欢打街球了......

![](https://cdn.luogu.com.cn/upload/image_hosting/q00do8x8.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)


P.S. 本题出题人是妥妥的篮网球迷！

## 题目描述

小 A 收到了 $n$ 场路人王比赛主办方的邀请，他将会**从家出发**去打比赛。打第 $i$ 场比赛需要 $a_i$ 分钟，在第 $s$ 分钟到达第 $i$ 场比赛场地需要等待 $c_i \times s +b_i$ 分钟才能打比赛。**到达后必须立刻开始等待，等待结束后必须立刻开始比赛**。从小 A 的家中到任何一场比赛的场地和从任何一场比赛的场地到另外一场比赛的场地时间相同，都是 $x$ 分钟。

小 A 因为打比赛会消耗大量的体力，所以带上了**一份**饭。除非他不出去比赛，否则他必须选择**任意一场自己要打的比赛**并在**这场比赛结束后立即吃饭**，吃饭需要 $d$ 分钟。

小 A 的妈妈希望小 A 在出门后的 $T+0.01$ 分钟前**回到家**。问小 A 最多能参加几场比赛？

**注意：无论是吃饭，等待，比赛或行走都必须连续进行，不能分成两段。同时只能进行一项行为，比如不能在行走时吃饭。**

**显然，同一场比赛不能打多次。**

## 说明/提示

**【样例解释 #1】**

对于第一组样例，你可以先出发去第 $2$ 场比赛，在比赛后吃饭，然后回家，总时间为 $15$ 分钟，且不能再打别的比赛。

**【数据范围】**

- $1 \le n \le 2 \times 10^5$。
- $1 \le a_i,b_i,T \le 10^9$，$0 \le x,d,c_i \le 10^9$。

### 请仔细阅读本题题面。

## 样例 #1

### 输入

```
3 2 4 20
1 2 3
2 3 1
1 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
10 11 1256 42668
572 678 14
517 17 20
886 680 24
237 944 12
870 321 2
598 273 13
824 228 20
73 824 6
910 891 10
953 502 9```

### 输出

```
3```

# 题解

## 作者：篮网总冠军 (赞：2)

# 题解

废话不多说，开始讲题。

## step -2 分析算法

首先我们分析一下这道题的算法。

很显然，这题要用 dp 做，但不能只用 dp，必须在前面进行一下排序，这题也就是一道典型的贪心 dp 题。

## step -1：排除无用条件

通过读题，我们可以筛掉一些无用的条件。

因为时间越往后，每个比赛的等待时间会越来越长，所以你一定会把吃饭放到最后一个比赛结束后吃饭。

所以上来 $T\gets T-d$。

同时，你最后一定要留出回家的时间。

所以再 $T\gets T-x$。

## step 0：分类讨论

我们可以看出，$c_i$ 是可能为 $0$ 的。如果 $c_i=0$，那么这场比赛无论何时参加时间都是 $a_i+b_i$，所以我们要把 $n$ 场比赛分成两部分，一部分是 $c_i=0$ 的，还有一部分是 $c_i \gt 0$的。我们先看 $c_i\gt0$ 的部分。

我们通过以下代码进行快排来分类：


```cpp
bool cmp1(node x,node y){
    return x.c>y.c;
}
```

### step 1.0：求出 $c_i$ 不为 $0$ 的比赛的个数


```cpp
long long n1=0;
for(int i=1;a[i].c!=0;i++,n1++);
```


### step 1.1：分析如何排序

我们通过读题，可以找到一些有用的条件。那么，我们现在来分析，对于第 $i$ 场比赛和第 $j$ 场比赛，是先去比第 $i$ 场再去比第 $j$ 场时间短，还是先去比第 $j$ 场再去比第 $i$ 场时间短？

我们可以列式。

在时刻 $t$，对于先去比第 $i$ 场再去比第 $j$ 场，总时间为 $x+c_i \times (x+t)+b_i+a_i+x+c_j \times (t+x+c_i \times (x+t)+b_i+a_i+x)+b_j+a_j$。

在时刻 $t$，对于先去比第 $j$ 场再去比第 $i$ 场，总时间为 $x+c_j \times (x+t)+b_j+a_j+x+c_i  \times(t+x+c_j \times
(x+t)+b_j+a_j+x)+b_i+a_i$。

因为要判断的是两个式子的大小，所以可以将相同的消掉。

化简得上面的式子为 $(x+a_i+b_i) \times c_j$。

下面的式子为 $(x+a_j+b_j) \times c_i$。

按照 $(x+a_i+b_i) \times c_j \lt (x+a_j+b_j) \times c_i$ 进行快排，排序完成。


```cpp
bool cmp(node x1,node y){
    return (x+x1.a+x1.b)*y.c<(x+y.a+y.b)*x1.c;
}
```

为什么这样排序就对了呢？

考虑一个存在 $i,j$ 满足 $i<j$ 且 $(x+a_i+b_i) \times c_j \ge (x+a_j+b_j) \times c_i$ 的排列。显然除了刚才排序得到的排列，其他的任何排列都满足这一条件。

那么只要把第 $i$ 项和第 $j$ 项对调一下，答案一定不劣。最终可以始终不劣地**调整**为我们排序得到的排列。那么证毕。

### step 1.2：预处理

除了上面的排除无用的条件的两步，还要对 dp 数组进行预处理。

自然应该先将所有数赋值 $10^9$，再将第一轮会用到的 $dp_{0,0}$ 赋值为 $0$。


```cpp
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            dp[i][j]=1e9;
        }
    }
    dp[0][0]=0;
```

### step 1.3：进行动态规划

在这里，$dp_{i,j}$ 代表在前 $i$ 场比赛中选择 $j$ 场比赛的最小时间。

对于第 $i$ 场比赛，我们应该干两件事。

首先，我们应该将所有这场比赛不选的情况放入 dp 中。

枚举前 $i$ 个选 $0 \sim i$ 个的情况。

```cpp
for(int j=0;j<=i;j++){
            dp[i][j]=dp[i-1][j];
}
```

接着，我们应该将这场比赛选的情况更新。

枚举前 $i-1$ 个选 $0 \sim i-1$ 个的情况。


```cpp
for(int j=1;j<=i;j++){
            if (dp[i-1][j-1]<T){
                long long t=x+a[i].a+(dp[i-1][j-1]+x)*a[i].c+a[i].b;
                if (t+dp[i-1][j-1]<=T) dp[i][j]=min(dp[i][j],t+dp[i-1][j-1]);
            }
        }
```

这里注意，如果时间超过 $T$ 就可以不求了。

### step 1.4：优化

显然，$O(n^2)$ 肯定超过了时间复杂度。

那么，我们怎么才能进一步优化程序呢？

由于我们要 dp 的这一部分满足 $c_i \gt 0$，所以数据满足 $1 \le a_i,b_i,c_i \le 10^9$，那么我们来分析一下。

我们假设第一次打第 $r$ 场比赛，那么结束时时间为 $x+a_r+b_r+x \times c_r$。

再假设第二次打第 $p$ 场比赛，那么结束时时间为 $x+a_r+b_r+x \times c_r+x+c_p \times (x+a_r+b_r+x \times c_r+x)+a_p+b_p$。

再假设第三次打第 $u$ 场比赛，那么结束时间为 $x+a_r+b_r+x \times c_r+c_p \times (x+a_r+b_r+x \times c_r+x)+a_p+b_p+x+c_u\times(x+a_r+b_r+x \times c_r+c_p \times (x+a_r+b_r+x \times c_r+x)+a_p+b_p+x)+a_u+b_u$。

我们可以得出，对于第一次比赛，其结束时间不小于 $a_r+b_r$。

第二次比赛结束时间不小于 $(a_r+b_r) \times 2+a_p+b_p$。

第三次比赛结束时间不小于 $4 \times (a_r+b_r)+2 \times (a_p+b_p)+a_u+b_u$。

总结一下，我们可以得出，第 $i$ 次比赛结束时间一定不小于 $2^i$，所以最多只能参加 $\log(T)$ 场比赛。

所以我们就可以简化复杂度到 $O(n \times \log(T))$。

此复杂度的 dp 代码如下：


```cpp
for(int i=1;i<=n1;i++){
        for(int j=0;j<=min(31,i);j++){
            dp[i][j]=dp[i-1][j];
        }
        for(int j=1;j<=min(31,i);j++){
            if (dp[i-1][j-1]<T){
                long long t=x+a[i].a+(dp[i-1][j-1]+x)*a[i].c+a[i].b;
                if (t+dp[i-1][j-1]<=T) dp[i][j]=min(dp[i][j],t+dp[i-1][j-1]);
            }
        }
    }
```

这里注意， $31$ 是因为 $\log(T)$ 不会超过 $31$。

### step 2.1：贪心

我们想想，当一个区间 $c_i=0$ 时，应该怎么排序呢？

当然是把 $a_i+b_i$ 从小到大排序。


```cpp
bool cmp2(node x,node y){
    return x.a+x.b<y.a+y.b;
}
```

### step 2.2：求前缀和

为了方便之后查找剩余时间够打几场比赛，我们应该先求出排完序后的后半部分的前缀和。


```cpp
for(int i=n1+1;i<=n;i++){
        s[i]=s[i-1]+a[i].a+a[i].b+x;
    }
```

### step 2.3：更新答案

枚举在 $c_i \gt 0$ 这一部分中选 $0 \sim \min(n_1,\log(t_1))$ 个的可能，再在刚刚准备好的前缀和表中二分查找最多能选的个数，并不断更新最大值，最后输出即可。


```cpp
long long sum=0;
for(int i=min(31ll,n1);i>=0;i--){
        long long o=dp[n1][i];
        if (o>T) continue;
        long long r1=T-o;
        int l=n1,r=n;
        while(l<r){
            int mid=(l+r+1)/2;
            if (s[mid]<=r1) l=mid;
            else r=mid-1;
        }
        sum=max(sum,l-n1+i);
    }
    cout<<sum<<endl;
```

---

## 作者：Genius_Star (赞：0)

### 思路：

奶龙题，这个吃饭有什么意义吗？

显然初始先令 $T \gets T - d$（闲话，我写成 $T - x$ 了都有 90pts）；然后打第 $i$ 个比赛的**总时间**可以看作直线 $c_ix + h_i$，这里 $h_i = a_i + b_i + x$。

先考虑若没有 $c_i = 0$ 时，显然打的比赛的次数最多只有 $\log T$ 次，因为每次打完比赛时刻至少会乘 $2$。

于是，我们考虑贪心的确定一个选取顺序，显然 $c_i = 0$ 的比赛最后打（不然会对 $c_i \ne 0$ 的比赛造成较大影响），然后按照 $c_i$ 从大到小选择。

定义 $dp_{i, j}$ 表示前 $i$ 个比赛打了 $j$ 个所花费的最短时间，那么有：

$$dp_{i, j} = \min(dp_{i - 1, j}, (c_i + 1) dp_{i - 1, j - 1} + h_i)$$

最后我们枚举 $c_i \ne 0$ 的比赛打的数量 $i$，找到剩下的时刻 $T - dp_{lst, i}$，然后贪心的去取 $c_i = 0$ 中 $h_i$ 最小的去打即可。

时间复杂度为 $O(N \log W)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
using namespace std;
#define int long long
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 10, M = 32;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int a, b;
	inline bool operator<(const Node&rhs)const{
		if(a ^ rhs.a)
		  return a > rhs.a;
		return b < rhs.b;
	}
}A[N];
int n, x, now, d, T, ans, cnt;
int a[N], b[N], c[N], s[N];
ll dp[N][M];
signed main(){
	n = read(), x = read(), d = read(), T = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read(), b[i] = read(), c[i] = read();
		a[i] += b[i] + x;
		A[i] = {c[i], a[i]};
	}
	T -= d;
	sort(A + 1, A + n + 1);
	memset(dp, -1, sizeof(dp));
	dp[0][0] = x;
	now = n + 1;
	for(int i = 1; i <= n; ++i){
		if(!A[i].a){
			now = i;
			break;
		}
		dp[i][0] = x;
		for(int j = 1; j <= min(i, M - 1); ++j){
			ll p = 1e18;
			if(dp[i - 1][j] != -1)
			  p = min(p, dp[i - 1][j]);
			if(dp[i - 1][j - 1] != -1)
			  p = min(p, dp[i - 1][j - 1] + 1ll * dp[i - 1][j - 1] * A[i].a + A[i].b);
			if(p > 1e9)
			  dp[i][j] = -1;
			else
			  dp[i][j] = p;
		}
	}
	for(int i = now; i <= n; ++i){
		++cnt;
		s[cnt] = s[cnt - 1] + A[i].b;
	}
	for(int j = 0; j <= min(now - 1, M - 1); ++j){
		if(T < dp[now - 1][j] || dp[now - 1][j] == -1)
		  break;
		int h = T - dp[now - 1][j];
		int g = upper_bound(s + 1, s + cnt + 1, h) - (s + 1);
		ans = max(ans, j + g);
	}
	write(ans);
	return 0;
}
```

---

