# The Human Equation

## 题目描述

Petya and his friend, the robot Petya++, went to BFDMONCON, where the costume contest is taking place today.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775E/8672900337cd1aed871edb11b60553e5c1da4d39.png)While walking through the festival, they came across a scientific stand named after Professor Oak and Golfball, where they were asked to solve an interesting problem.

Given a sequence of numbers $ a_1, a_2, \dots, a_n $ you can perform several operations on this sequence.

Each operation should look as follows. You choose some subsequence $ ^\dagger $ . Then you call all the numbers at odd positions in this subsequence northern, and all the numbers at even positions in this subsequence southern. In this case, only the position of the number in the subsequence is taken into account, not in the original sequence.

For example, consider the sequence $ 1, 4, 2, 8, 5, 7, 3, 6, 9 $ and its subsequence (shown in bold) $ 1, \mathbf{4}, \mathbf{2}, 8, \mathbf{5}, 7, 3, \mathbf{6}, 9 $ . Then the numbers $ 4 $ and $ 5 $ are northern, and the numbers $ 2 $ and $ 6 $ are southern.

After that, you can do one of the following:

- add $ 1 $ to all northern numbers and subtract $ 1 $ from all south numbers; or
- add $ 1 $ to all southern numbers and subtract $ 1 $ from all northern numbers.

Thus, from the sequence $ 1, \mathbf{4}, \mathbf{2}, 8, \mathbf{5}, 7, 3, \mathbf{6}, 9 $ , if you choose the subsequence shown in bold, you can get either $ 1, \mathbf{5}, \mathbf{1}, 8, \mathbf{6}, 7, 3, \mathbf{5}, 9 $ or $ 1, \mathbf{3}, \mathbf{3}, 8, \mathbf{4}, 7, 3, \mathbf{7}, 9 $ .

Then the operation ends. Note also that all operations are independent, i. e. the numbers are no longer called northern or southern when one operation ends.

It is necessary to turn all the numbers of the sequence into zeros using the operations described above. Since there is very little time left before the costume contest, the friends want to know, what is the minimum number of operations required for this.

The friends were unable to solve this problem, so can you help them?

 $ ^\dagger $ A sequence $ c $ is a subsequence of a sequence $ d $ if $ c $ can be obtained from $ d $ by the deletion of several (possibly, zero or all) elements.

## 说明/提示

In the first test case, the sequence of operations is as follows: $ \mathbf{1}, 2, \mathbf{-3} \longrightarrow 0, \mathbf{2}, \mathbf{-2} \longrightarrow 0, \mathbf{1}, \mathbf{-1} \longrightarrow 0, 0, 0 $ .

In the second test case, the sequence looks like this: $ \mathbf{1}, 0, 0, \mathbf{-1}, -1 \longrightarrow 0, 0, 0, 0, \mathbf{-1} \longrightarrow 0, 0, 0, 0, 0 $ .

In the fourth test case, simply select the entire sequence as a subsequence, then subtract one from the northern numbers and add one to the southern numbers. Thus, the sequence will be nulled in one operation.

In the fifth test case, you don't need to do any operations, since the sequence already consists of zeros.

## 样例 #1

### 输入

```
5
3
1 2 -3
5
1 0 0 -1 -1
6
2 -4 3 -5 4 1
5
1 -1 1 -1 1
7
0 0 0 0 0 0 0```

### 输出

```
3
2
6
1
0```

# 题解

## 作者：VinstaG173 (赞：6)

精妙的题目。

首先证明一个结论：存在一种最优操作，其中每次操作都不会将任意非负数增大。

若不然，假设 $a_i\ge0,$ 某次操作中将 $a_i$ 增加 $1$，这次操作选择的下标为 $s_1<\dots<s_k=i<s_{k+1}<\dots$（可以不存在 $s_{k+1}$，也可以 $k=1$，以下类似）。则此后必有某次操作将 $a_i$ 减少 $1$，这次操作选择的下标为 $t_1<\dots<t_l=i<t_{l+1}<\dots$，则将这两次操作改为选择 $s_1,\dots,s_{k-1},t_{l+1},\dots$ 与 $t_1,\dots,t_{l-1},s_{k+1},\dots$，并保持操作中对每个数的改变量。则对非负数增加 $1$ 的操作次数减少 $1$。由于操作在有限次内结束，可以不断如此调整直到任意操作都不会将非负数增大。

同理，任意操作都不会将非正数减小。从而所有 $0$ 不会被操作。

因此我们每次操作一定是选择一个正负相间的子序列，将其中的正数减小 $1$，负数增加 $1$。在此基础上我们显然有贪心策略：每次选择尽量长的满足条件的子序列。

考虑证明贪心正确性。事实上若某次操作的后续存在一次操作选择的子序列比这次更长，则可以将两次操作顺序对换，因此可以让操作的子序列长度不减。

若某次操作并非目前最长的子序列，则有两种情况：

一、存在一端可以延长使得子序列仍然正负相间。

不妨设操作的子序列为 $s_1<s_2<\dots<s_k$，且存在 $t>s_k$ 且 $a_t$ 与 $a_{s_k}$ 不同号。则后续存在某操作选择 $a_t$，将该操作中 $a_t$ 及更大下标的位置都放到这次操作中即可让操作子序列变长。另一端同理。

二、存在相邻两个位置间可以插入两个位置使得子序列仍然正负相间。

不妨设可以加入 $b<c$ 两个位置使得子序列仍然正负相间，显然可以取 $b,c$ 相邻（此处相邻定义为 $a_{b+1}=\dots=a_{c-1}=0$），则后续存在某些操作选择 $b,c$。若同一操作选择 $b,c$，则直接将对 $b,c$ 的操作放到这次进行即可让操作子序列变长。否则选取一个对 $b$ 的操作 $s_1<\dots<s_k=b<s_{k+1}<\dots$，一个对 $c$ 的操作 $t_1<\dots<t_l=c<t_{l+1}<\dots$，进行操作 $s_1,\dots,s_{k-1},t_{l+1},\dots$ 与 $t_1,\dots,t_{l-1},s_{k+1},\dots$ 并将 $b,c$ 放到这次操作即可。由于 $b,c$ 相邻，显然上述操作均合法。

由于最长子序列长度有限，因此必然可以在有限次如上调整后将本次操作序列变为最长子序列。上述调整不增加总操作次数。

但是直接每次找最长子序列可以达到 $O(n^2)$。考虑如何快速实现。注意到最长子序列一定可以以第一个非零数为起始，因此我们贪心地每次优先将第一个非零数变为 $0$。

记录两个变量 $ps,ng$ 分别表示当前对正数的剩余有效操作数与对负数的剩余有效操作数。即已经进行过的操作可以让作为当前第一个非零数的正数减少 $ps$，或者让作为当前第一个非零数的负数增加 $ng$。

这也相当于是已经进行过的操作中上一个操作数是负数的个数与上一个操作数是正数的个数，因此我们会发现维护它们非常简单：每扫到一个非零数 $a_i$ 时，若其为正数，则 $ng$ 的值变为 $ng+a_i$，$ps$ 的值变为 $\max\{ps-a_i,0\}$，负数同理。事实上转移式即为 $ps\leftarrow\max\{ps-a_i,0\},ng\leftarrow\max\{ng+a_i,0\}$。总操作次数即为 $ps+ng$。时间复杂度 $O(n)$。

Code:
```cpp
int n;
ll a[200003];
ll ps,ng;
inline void solve(){
	rd(n);ps=ng=0;
	for(rg int i=1;i<=n;++i){
		rd(a[i]);if(a[i]==0){
			--i,--n;continue;
		}if(a[i]>0){
			if(a[i]>ps)ps=a[i];
		}else if(-a[i]>ng)ng=-a[i];
		ps-=a[i],ng+=a[i];
	}printf("%lld\n",ps+ng);
}
```

---

## 作者：Nightingale_OI (赞：6)

## CF1775E

### 大意

给定一个数组 $a$，每次可以选择其一个子序列 $a_{p_i} (p_i<p_{i+1})$ 操作。

一次操作是 $a_{p_{2i}} \pm 1,a_{p_{2i-1}} \mp 1$（子序列中偶数位对应原数组位置 $\pm 1$，奇数位 $\mp 1$）。

求几次可以使 $a$ 元素全归零。

### 思路

记 $b$ 为 $a$ 的前缀和，一次操作就是在 $b$ 中选任意一些数 $\pm 1$。

显然 $b$ 元素全零是 $a$ 元素全零的充要条件。

策略是让正数一直减到结束，负数一直加到结束，直接统计 $b$ 中最大的正数和最小的负数的绝对值相加即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
int a[202020];
inline void doing(){
	cin>>n;
	f(i,1,n)scanf("%lld",&a[i]);
	f(i,1,n)a[i]+=a[i-1];
	s=l=0;
	f(i,1,n){
		if(s<a[i])s=a[i];
		if(a[i]<l)l=a[i];
	}
	printf("%lld\n",s-l);
}
signed main(){
	int t;
	cin>>t;
	while(t--)doing();
	return 0;
} 
```

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18573313)

来个另类解。

# 思路

手玩一下样例，发现减法只会用在正数上，加法只会用在负数上，大概是因为如何在负数上用了减法或在正数上用了加法，都需要额外的次数去消掉。

然后注意到在两个正数中间包这的所有负数可以直接缩成一个数，两个负数中间包着的所有正数也可以直接缩成一个数。那么现在的序列就变成了一个正负相间的序列了，对于每一次操作都可以直接打一个 tag。

考虑简化操作，对于一个序列记其中绝对值最小的数为 $x$，那么在 $|x|$ 次操作后，所有绝对值为 $|x|$ 的位置值都将变成 $0$。但是因为 $0$ 的出现，会导致序列不再正负相间，因此可以用 set 维护，每一次删除 $|x|$ 的数，将其两边的数合在一起。复杂度 $\Theta(n \log n)$。

发现将两边的数 $x,y$ 合在一起成为 $x + y - tag$，因为 $x,y$ 均要减去一个 $tag$，但是单一元素只会减一个 $tag$。将这个模拟过程刻画一下：将两个正数合并的代价是中间的负数大小，将两个负数合并的代价是中间正数的大小。

不妨定义 $dp_i$ 表示包含第 $i$ 个数的最大段的权值和，显然有转移 $dp_i = \max(0,dp_{i - 2} - t_{i - 1}) + t_i$，其中 $t_i$ 表示将正数缩成一个点，负数缩成一个点过后的序列。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define chmax(a,b) (a = max(a,b))

using namespace std;

const int N = 1e6 + 10;
int n;
int num,arr[N],tmp[N],dp[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

#define check(x,y) (((x) <= 0 && (y) <= 0) || ((x) >= 0 && (y) >= 0))

inline void solve(){
    num = 0; n = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    int lst = 0;
    for (re int i = 1;i <= n;i++){
        if (check(lst,arr[i])) lst += arr[i];
        else{
            tmp[++num] = abs(lst);
            lst = arr[i];
        }
    }
    if (lst) tmp[++num] = abs(lst);
    int ans = 0;
    for (re int i = 1;i <= num;i++){
        dp[i] = max(0ll,dp[i - 2] - tmp[i - 1]) + tmp[i];
        chmax(ans,dp[i]);
    }
    printf("%lld\n",ans);
}

signed main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：cff_0102 (赞：2)

设 $b$ 数组记录 $a$ 的前缀和。

假设一次操作中选择的子序列第一个数是 $a_i$，第二个数是 $a_j$，且将 $a_i$ 加上 $1$，$a_j$ 减去 $1$。则 $b_1$ 到 $b_i$ 之间数值不变，$b_i$ 和 $b_{j-1}$ 之间的数会比原来多 $1$，$b_j$ 后面的数不变。

如果将 $a_i$ 减去 $1$，$a_j$ 加上 $1$，则 $b_1$ 到 $b_i$ 之间数值不变，$b_i$ 和 $b_{j-1}$ 之间的数会比原来少 $1$，$b_j$ 后面的数不变。

所以每次操作实际上可以将 $b$ 数组的任意几个数同时加 $1$ 或减 $1$。

原问题转化为求 $b$ 数组全变为 $0$ 需要几次操作。

将 $b$ 数组分成两部分，第一部分全是正数，第二部分全是负数（为 $0$ 的不操作就行了，这里就不管了）。正数部分需要的最少操作数量是最大的那个正数，负数部分需要的最少操作数量是最小的那个负数的绝对值。只要求出这两个数之和，就能知道这道题的答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		long long a[n];
		for(int i=0;i<n;i++)cin>>a[i];
		long long b[n]={a[0]};//前缀和（前缀和数组可能爆 int，所以用 ll） 
		for(int i=1;i<n;i++)b[i]=b[i-1]+a[i];
		long long mx=0/*正数部分最大值*/,mn=0/*负数部分最小值*/;
		for(int i=0;i<n;i++)mx=max(mx,b[i]),mn=min(mn,b[i]);
		cout<<mx-mn<<endl;
	}
	return 0;
}
```

---

## 作者：Mine_King (赞：2)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/17042849.html)

# E. The Human Equation

## Problem

[CF1775E The Human Equation](https://codeforces.com/contest/1775/problem/E)

**题目大意：**

给你一个序列，你可以执行任意次以下操作：

选出一个子序列，将奇数位 $+1$，偶数位 $-1$，或将奇数位 $-1$，偶数位 $+1$。

问最少几次操作使得序列变成全 $0$。

## Solution

显然正数只会 $-1$，负数只会 $+1$。

显然本题可以贪心，即对于每次操作尽量往后扩展。

从前往后考虑每一个数，两个计数器 $z,f$ 分别表示以正数结尾和以负数结尾的操作产生的贡献。

对于当前这个数 $x$，若是正数：若负数产生的贡献大于当前数，则表示当前数可以被加入之前的操作一起消掉。此时这些贡献转化成了正数的贡献。故 $z \leftarrow z + x,f \leftarrow f - x$。  
否则，说明需要额外操作，故答案加上 $x - f$，并且贡献也转化成了正数的贡献，故 $z \leftarrow z + x,f \leftarrow 0$。

对于 $x$ 是负数的情况同理。

为什么这样做是对的？因为对于每次操作，将其贡献加在任意位置都是对的。这种做法将贡献加在了操作的第一个位置，显然正确。

## Code

```cpp
// Think twice, code once.
#include <stack>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int T,n,a[200005];
long long ans;

int main() {
	scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		long long z=0,f=0;
		ans=0;
		for (int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			if (a[i]>0) {
				z+=a[i];
				if (f>=a[i]) f-=a[i];
				else ans+=a[i]-f,f=0;
			} else {
				f-=a[i];
				if (z>=-a[i]) z+=a[i];
				else ans-=a[i]+z,z=0;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：N1K_J (赞：1)

## 题意

给定一个长度为 $n$ 的数组 $\{a_n\}$，每次操作可以对 $\{a_n\}$ 的一个子序列奇偶数项加 $1$ 减 $1$，求至少多少次操作使 $\{a_n\}$ 全为 $0$。

## 思路

一般来说区间修改数组都可以考虑差分或者前缀和。

考虑 $\{a_n\}$ 的前缀和 $\{b_n\}$。

我们考虑取出的子序列是 $\{a_{x_1},a_{x_2},a_{x_3},\cdots\}$。

不妨设奇数项 $+1$，偶数项 $-1$。

那么应有：

$b_{x_1}$ 到 $b_{x_2-1}$ 均 $+1$。


$b_{x_3}$ 到 $b_{x_4-1}$ 均 $+1$。

$\cdots$

因此，可以注意到每次操作可以使得 $b$ 数组若干个区间 $+1$ 或若干个区间 $-1$。

显而易见的对 $\{a_n\}$ 中非负数部分全部用区间 $-1$，对 $\{a_n\}$ 负数部分用区间 $+1$。

故答案为最大的整数减最小的负数。

[Code](https://codeforces.com/contest/1775/submission/245673406)

---

## 作者：Find_Yourself (赞：1)

[The Human Equation](https://www.luogu.com.cn/problem/CF1775E)

思维题。

我们考虑每次 $a$ 数组加一减一对于其前缀和 $sum$ 的影响。

可以发现，假设相邻两次加一和减一的位置分别为 $l$ 和 $r$，那么 $sum$ 在 $[l,r)$ 内会加一。

先减后加也同理。

所以，一次加减操作相当于将 $sum$ 若干段连续序列加一或减一。

而 $sum$ 全部为 $0$ 是 $a$ 都变为 $0$ 的充要条件。

因此我们只需要计算出 $sum$ 归零的最小操作数，也就是 $maxn-minn$，其中 $maxn$ 为最大正数，$minn$ 为最小的负数。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, n; 
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n;
		ll sum = 0, minn = 0, maxn = 0;
		for (int i = 1; i <= n; ++i) {
			ll x; cin >> x; sum += x;
			minn = min(minn, sum);
			maxn = max(maxn, sum);
		}
		cout << maxn - minn << endl;
	}
	return 0;
}

```


---

## 作者：_sunkuangzheng_ (赞：0)



**【题目大意】（摘自题目翻译）**

给定 $n$ 个数 $a_1 \ldots a_n$，随后你可以进行若干次操作，每次操作步骤如下：

* 选出 $a$ 中一个子序列（可以不连续）。 

* 把子序列中的奇数项减一，偶数项加一；或者奇数项加一，偶数项减一。

求把 $n$ 个数全部变成 $0$ 的最少操作次数。

$1\le n\le2\times10^5,-10^9\le a_i\le10^9$，多组数据。

**【题目分析】**

奇偶分开加减不好处理，我们不妨观察 $a$ 的前缀和数组 $b$ 的变化。若一次操作选取位置 $c_1,c_2,\ldots,c_k$ 进行操作，设这次操作为 $a_{c_1} \gets a_{c_1}+1$，那么在前缀和数组上，$[c_1,c_2-1],[c_3,c_4-1],\ldots$ 位置会 $+1$，而其他位置不变。显然原数组全 $0$ 和前缀和数组全 $0$ 是等价的，那么我们的问题转化成，对一个序列 $b$，每次操作可以同时选取若干子段使得它们同时 $+1$ 或 $-1$。贪心的考虑，每一次加法只应用在负数上，减法只应用在正数上。显然操作次数为 $\max\limits_{b_i > 0}\{b_i\}-\min\limits_{b_i < 0}\{b_i\}$。

**【代码】**

核心代码两行。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,mx,mn,x,y;
int main(){
    for(cin >> t;mx = mn = x = 0,t --;cout << mx - mn << "\n")
        for(cin >> n;n --;cin >> y,x += y,mx = max(x,mx),mn = min(x,mn));
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

在 $a$ 上按照奇偶性加减太难处理了，子序列上相邻两个位置刚好一加一减？这让我们联想到差分。我们不如认为 $a$ 是 $p$ 的差分数组。$\sum \limits_{i=1}^n \left[a_i=0\right]=n$ 则可以认为是 $p$ 全部相等了。

考虑对 $a$ 的操作会导致什么？设选出子序列 $q_1,q_2,\cdots,q_k$，我们钦定则 $a_{q_1}\gets a_{q_1}+1$。那么在 $p$ 上对应的就是给 $[a_{q_1},a_{q_2})$ 这个区间加一。同理地，给 $[a_{q_3},a_{q_4})$ 区间加……

由此我们可以看到我们一次对 $a$ 的操作完全可以理解为对 $q$ 的若干个区间加，减同理。也就是可以每次任意挑数减一或者任意挑数加一。

那么，不难发现，最后的答案就是前缀和后的正数最大减负数最小。策略是全部变成 $0$。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
using ll=long long;
const int N=2e5+5; ll inf=1ll<<50;
int n, i, t; ll a[N]; ll mx, mn;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
        mx=mn=0;
		scanf("%d", &n); rep(i, 1, n) scanf("%lld", a+i); rep(i, 1, n) a[i]+=a[i-1];
		rep(i, 1, n) mx=max(mx, a[i]), mn=min(mn, a[i]);
		printf("%lld\n", mx-mn);
	}
	return 0;
}
```

---

## 作者：masonpop (赞：0)

这题核心代码只有短短十行，但却十分神奇。

看到这个一个 $+1$，一个 $-1$ 的结果，是不是想到了我们用差分解决区间加法的方式。注意到我们选取的下标可以不连续，而且根据奇偶交替的特点，我们可以发现：设 $sum_i$ 是 $a_i$ 的前缀和，则**一次操作相当于选取 $sum$ 中某些数同时加一或减一**。 

知道了这个就简单了，让 $a$ 归零就是让 $sum$ 归零。显然，把正数一起减到 $0$，负数一起加到 $0$ 一定最优。因此，答案就是最大的正数与最小的负数的绝对值之和，统计一下即可。

时间复杂度 $O(n)$。[代码](https://codeforces.com/contest/1775/submission/209819217)。

---

## 作者：strcmp (赞：0)

**题目大意：** 给定一个长度为 $n$ 的序列 $a$，每次操作可以选出 $a$ 的任意一个非空子序列。可以使得该**子序列的所有奇数项加一，所有偶数项减一**；或者使得该子序列的所有奇数项**减一**，所有偶数项**加一**。求最少使用多少次操作，能使得 $a$ 中的元素全部变为 $0$。

### Solution

一道很好的妙题，较可惜的是结论比较好猜测。

方便起见，我们将奇数项加一，偶数项减一的操作叫做操作一；奇数项减一，偶数项加一的操作叫做操作二。

首先，对于一些很奇怪的数列操作，原序列不好维护的时候，可以转为前缀和或者差分来看性质。

这题目明显不是差分，在差分之后，整个差分序列为 $0$ 很显然不能告诉我们原序列也为 $0$。这提示我们**观察原序列的前缀和的性质。**

对第三个较强一点的样例，手玩一下，$[2,-4,3,-5,4,1]$ 的前缀和是 $[2,-2,1,-4,0,1]$。如果我们选取子序列为 $[2,-5,1]$ 进行操作一。会将前缀和变为 $[2,-2+1,3+1,-5,4,1+1]$。

观察一下，发现如果我们选取子序列 $[p_1,p_2,\dots,p_k]$ 进行操作一，假设子序列单调递增。则会导致 $[p_1,\,p_2-1]$ 的前缀和全部加上一；$[p_2,\,p_3-1]$ 被之前的加一抵消，不变；$[p_3,\,p_4-1]$ 的前缀和也全部加上一。换句话说，每次我们改变了 $\{[p_1,\,p_2-1],\,[p_3,\,p_4-1],\,[p_5,\,p_6-1],\,\dots\}$ 的前缀和，并将其全部加一。（若子序列长度为 $1$，则改变 $[p_1,\,n]$）

这意味着什么呢？我们**每次可以选取任意多个不相接的区间，并将区间内的前缀和加一。操作二同理，不过是将区间内的前缀和减一。**

那有什么用呢？这意味着我们每次可以选任意个数加一，或者任意个数减一。换句话说，我们将正数一直减到 $0$，将负数一直加到 $0$，最少的次数就是将前缀和全部变为 $0$ 的最小次数。

而前缀和序列的元素全部为 $0$，显然是 $a$ 的元素全部为 $0$ 的充要条件。 

那么问题就转化为在序列中每次任意选取一些数，将这些数同时加一，或者同时减一，求最少将序列元素全部变为 $0$ 的个数。

这就很简单了，假设 $a$ 中正数和负数都有。将正数全部变为 $0$，最少次数当然是 $|\max a|$。而将所有负数全部变为 $0$，最少次数也当然是 $-|\min a|$。将二者加起来就是答案。

如果不一定都有呢？那么最大值和最小值的极差就是答案了。

时间复杂度 $\Theta(n)$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 2e5 + 10;
int t, n; ll a[maxn];
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n); ll mi = 0, mx = 0;
        for (int i = 1; i <= n; i++)scanf("%lld", &a[i]), a[i] += a[i - 1];
        for (int i = 1; i <= n; i++)mi = min(mi, a[i]), mx = max(mx, a[i]);
        printf("%lld\n", mx - mi);
    }
    return 0;
}
```


---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1775E)

显然最优策略是把所有正数减掉，负数加上。

这个不是很好直接处理。考虑使用前缀和求解，原因是前缀和全为 $0$ 能够保证原数组全为 $0$。

那么我们需要减去的是前缀和中的最大值，需要加上的是前缀和中的最小值，每次只能 $\pm1$，因此结果是它们的绝对值之和。

Code:

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=2e5+10;
int T,n;
LL Max,Min,a[N];
LL solve()
{
    scanf("%d",&n);
    Max=Min=0ll;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]+=a[i-1];
    for(int i=1;i<=n;i++)Max=max(Max,a[i]),Min=min(Min,a[i]);
    return Max-Min;
}
signed main()
{
    scanf("%d",&T);
    while(T--)printf("%lld\n",solve());
    return 0;
}
```

---

## 作者：tanghg (赞：0)

## 思路

首先如果要最少次数，那么也就是要尽量少的选择子序列。同时可以发现，由于子序列可以不连续，所以将一个数变得更大是没有意义的。那么就转化成了如何尽量少的减少子序列的选择次数。

之后，如果我想让子序列的个数变少，那么就是要将它变得尽可能长，也就是一次可以带动更多的减。那么就是正负正负或者负正负正最长即可。

我们这样就做出了 $O(n^2)$ 的做法。我们考虑优化。由于每个数早晚都要消掉，那么我们不妨考虑扫一遍每一次要将 $a_i$ 变成 $0$。但是就要问了，如果这样找的话万一中间有一个数比 $a_i$ 小不就分裂了吗，之后奇偶就不确定了。但是我们如果要增加 $1$ 的话就必然要减少 $1$，所以有两个子序列，那么我们用前面增加 $1$ 的子序列排除掉 $i$ 在把第二个减少子序列后的后半除了 $i$ 的拼到一起就可以在奇偶性不变的情况下不会出现问题了。负数同理，所以 $0$ 就不会出现问题了，操作数也不用变。也可以去看 VinstaG173 大佬写的题解。

之后我们可以记录两个变量，$f,z$，为上一个的剩余操作数（贡献），要分负正因为是正负正负或者负正负正，所以要从前面的符号不同的地方更新。那么如果当前是正数，那么自然对负数可以要增加 $a_i$，因为负数可以减少正数所剩余的次数，而正数的剩余操作数要减少 $a_i$ 因为用了这么多。所以可以感觉到是反过来的感觉。之后注意正数最多减到 $0$。所以就是当前数是正数时 $z=\max(z-a_i,0),f=f+a_i$，当前数是负数时 $f=\max(f-a_i,0),z=z+a_i$。

之后自然答案就是负数的剩余次数和正数的剩余次数。

## 代码

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll t,n,a;
int main(){
    scanf("%lld",&t);
    while (t--){
        scanf("%lld",&n);
        ll z=0,f=0;
        for (int i = 1; i <=n ; ++i) {
            scanf("%lld",&a);
            if(a==0){
                continue;
            }else if(a>0){
                z= max(z-a,ll(0));
                f+=a;
            }else{
                a=-a;
                f=max(f-a,ll(0));
                z+=a;
            }
        }
        printf("%lld\n",z+f);
    }
    return 0;
}
```

---

## 作者：Hedgehog_210508 (赞：0)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1775E)

**思路**：考虑观察数组的前缀和。

对于奇数项为 $+1$ 的操作，在前缀和数组中就相当于从某个奇数项到下一项都 $+1$，从一个偶数项到下一项都不变。奇数项为 $-1$ 的操作同理。

在前缀和中“任选一些数 $+1$”显然是可以在一次操作内实现的，且每次操作每项至多 $+1$。那么为了负数都变成 $0$，每次操作把所有任为负的数都 $+1$，那么总操作次数是最小负数的绝对值。对于正数同理。最后答案为前缀和中最大正数减去最小负数。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		ll n,s[200009],mx=-2e9,mn=2e9;
		s[0]=0;
		cin>>n;
		for(ll i=1;i<=n;i++){
			cin>>s[i];
			s[i]+=s[i-1];
			mx=max(mx,s[i]);
			mn=min(mn,s[i]);
		}
		cout<<max(mx,ll(0))-min(mn,ll(0))<<endl;
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# CF1775E 题解



## 思路分析

先考虑一个简单的贪心：每次扫描的时候间隔选择正数和负数操作。

考虑优化，注意到连续的一段正数和连续的一段负数每次操作至多让这一段的所有 $|a_i|$ 的和 $-1$。

因此对于连续的一段符号相同的数缩成一个块，大小为块内所有 $|a_i|$ 的和，那么每次操作能够让每个块的大小 $-1$，如果一个块的大小为 $0$ 就删除并且合并其两边两个块。

注意到虽然操作次数可能很多，但很多操作都是重复的，维护一下最小块的大小，每次直接操作到最小块为空为止，显然可以用 `set` 配合延迟标记法完成，同时我们还需要一个按下标排序的 `set` 来维护每次合并哪两个块，剩下的过程简单维护一下即可。

时间复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
#define int long long
#define pii pair<int,int>
using namespace std;
const int MAXN=2e5+1;
int a[MAXN];
inline pii rev(pii p) {
	return make_pair(p.second,p.first);
}
inline void solve() {
	set <pii> val,sec;
	int n;
	scanf("%lld",&n);
	for(int i=1,id=0,op=0,sum=0;i<=n;++i) {
		scanf("%lld",&a[i]);
		if(a[i]==0) {
			if(i==n) {
				val.insert(make_pair(sum,id));
				sec.insert(make_pair(id,sum));
			}
			continue;
		}
		if(op==0||a[i]*op<0) {
			if(id>0) {
				val.insert(make_pair(sum,id));
				sec.insert(make_pair(id,sum));
			}
			id=i,op=a[i]/abs(a[i]),sum=0;
		}
		sum+=abs(a[i]);
		if(i==n) {
			val.insert(make_pair(sum,id));
			sec.insert(make_pair(id,sum));
		}
	}
	int del=0;
	while(!sec.empty()) {
		int id=val.begin()->second,w=val.begin()->first;
		del=w;
		val.erase(val.begin());
		auto it=sec.find(make_pair(id,w));
		if(it==sec.begin()||prev(it,-1)==sec.end()) {
			sec.erase(it);
			continue;
		}
		pii val_L=*prev(it,1),val_R=*prev(it,-1);
		sec.erase(it);
		sec.erase(sec.find(val_L)),val.erase(val.find(rev(val_L)));
		sec.erase(sec.find(val_R)),val.erase(val.find(rev(val_R)));
		pii val_N=make_pair(val_L.first,val_L.second+val_R.second-del);
		sec.insert(val_N),val.insert(rev(val_N));
	}
	printf("%lld\n",del);
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：MSqwq (赞：0)

超级简单的一道 E，但是这场没打。。。  


------------
题意：  
给你一个 $n$ 个数，每次你可以选一些数单独拎出来，然后对其奇偶位分析，要么奇数位的数全部加一，偶数位的数全部减一，要么奇数位的数全部减一，偶数位的数全部加一，问你多少次操作可以全部变成 $0$。  


------------
题意：  
不难发现，每次操作就是将任意一些数的总和加一减一或者不变，偶数个数的时候就是不变，奇数的时候就看先加还是先减，当然这个不重要，重要的是我们最后要将数组任意一个区间内的区间和都为 $0$。  
那么我们随便手摸一遍数据，就发现加入我操作中间区间的时候两边的数是一定可以顺便操作完的，那么我们只需要操作中间区间就能完成全局。所以这个题就变成了求最大区间和，或者最小区间和。  
代码：  
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=2e5+10;
ll a[N],s[N];
int main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		ll mx1=0,mx2=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=read(),s[i]=s[i-1]+a[i];
			mx1=max(mx1,s[i]);
			mx2=max(mx2,-s[i]);
		}
		cout<<mx1+mx2<<endl;		
	}
	return 0;
}

```


---

