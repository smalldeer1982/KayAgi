# Yurii Can Do Everything

## 题目描述

Yurii is sure he can do everything. Can he solve this task, though?

He has an array $ a $ consisting of $ n $ positive integers. Let's call a subarray $ a[l...r] $ good if the following conditions are simultaneously satisfied:

- $ l+1 \leq r-1 $ , i. e. the subarray has length at least $ 3 $ ;
- $ (a_l \oplus a_r) = (a_{l+1}+a_{l+2}+\ldots+a_{r-2}+a_{r-1}) $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

In other words, a subarray is good if the bitwise XOR of the two border elements is equal to the sum of the rest of the elements.

Yurii wants to calculate the total number of good subarrays. What is it equal to?

An array $ c $ is a subarray of an array $ d $ if $ c $ can be obtained from $ d $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

There are $ 6 $ good subarrays in the example:

- $ [3,1,2] $ (twice) because $ (3 \oplus 2) = 1 $ ;
- $ [1,2,3] $ (twice) because $ (1 \oplus 3) = 2 $ ;
- $ [2,3,1] $ because $ (2 \oplus 1) = 3 $ ;
- $ [3,1,2,3,1,2,3,15] $ because $ (3 \oplus 15) = (1+2+3+1+2+3) $ .

## 样例 #1

### 输入

```
8
3 1 2 3 1 2 3 15```

### 输出

```
6```

## 样例 #2

### 输入

```
10
997230370 58052053 240970544 715275815 250707702 156801523 44100666 64791577 43523002 480196854```

### 输出

```
2```

# 题解

## 作者：MoonPie (赞：12)

### 题目描述

---

给你一个大小为 $n$  ($n\le 2e5$) 的数组 $a$，其中 $a_i$（$1\le a_i<2^{30}$）.

定义一个 $a$ 中一个字串 $a[l\dots r]$ 是好的，当 $(a_l \oplus a_r) = a_{l+1}+a_{l+2}+\dots a_{r-2}+a_{r-1}$.

请输出数组 $a$ 中好的字串的个数.

### 题解

----

$O(n^2)$ 的暴力十分好写，只要枚举字串的左右端点并判断即可.

考虑一个暴力的优化：

我们先确定一个左端点 $l$，记 $a_l$ 在二进制下的最高位为 $k$

然后往右枚举右端点 $r$ ，事实上，当 $a_{l+1}+a_{l+2}+\dots +a_{r-2}+a_{r-1} \ge 2^{k+1}$ 时

就不用继续往右枚举了.

原因是 $a_l$ 异或上任何一个不大于 $a_l$ 的正整数都不会大于等于 $2^{k+1}$.

然后，让我们分析一下这个 “暴力” 的复杂度：

考虑一个 $a_i$ 作为右端点被枚举到的次数，对于每一种 $k$ ，$a_i$ 最多只会被访问到两次，

因为如果有第三个这样的 $k$ ，在这个数与 $a_i$ 中就有两个数最高位是 $k$ ，这两个数之和就大于等于$2^{k+1}$了.

于是，我们会发现这个“暴力”的复杂的是 $n log a_i$ 的，可以通过本题.

最后有一点需要提醒，为了防止遗漏，要从左往右扫一遍在从有往左扫一遍然后去重.

### code
---
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace moonpie {
	#define P pair<int,int>
    const int N=2e5+5;
    int n,a[N];
    set<P> s;
    void solve() {
        cin>>n;
        for(int i=1;i<=n;++i) scanf("%d",&a[i]);

        int cnt=0;
        for(int i=1;i<=n;++i) {
            int x = log2(a[i]);
            int sum = 0;
            for(int j=i+1;j<n;++j) {
                sum += a[j];
                if(sum > (1<<(x+1))) break;
                if(sum == (a[i]^a[j+1])) s.insert(P(i,j+1));
            }
        }

        for(int i=n;i>=1;--i) {
            int x = log2(a[i]);
            int sum = 0;
            for(int j=i-1;j>1;--j) {
                sum += a[j];
                if(sum > (1<<(x+1))) break;
                if(sum == (a[i]^a[j-1])) s.insert(P(j-1,i));
            }
        }

        cout<<s.size()<<endl;
        
    }
}
signed main() {
    moonpie::solve();
    return 0;
}
```

---

## 作者：Cutest_Junior (赞：8)

## CF1438E 【Yurii Can Do Everything】

### 题意

+ 一个数组 $a[l,r]$ 是好的，当且仅当 $r-l\le2$ 且 $a_l\oplus a_r=sum_{r-1}-sum_{l}$，$sum$ 为 $a$ 的前缀和数组；
+ 一个长度为 $n$ 的数组 $a$，求 $a$ 有几个子数组是好的；
+ $n\le2\times10^5,a\le10^9$。

### 做法

直接枚举子数组 $O(n^2)$，显然不行。

发现一个性质：$a\oplus b<\max(\operatorname{highbit}(a),\operatorname{highbit}(b))\times2$。所以我们可以枚举 $l$，向右枚举 $r$，找到所有 $a_l\ge a_r$ 的好的子数组，当 $sum_{r-1}-sum_{l}\ge\operatorname{highbit}(a_l)\times2$ 时，退出枚举，因为不可后面不可能有答案，再枚举 $r$，向左枚举 $l$，找到所有 $a_r>a_l$ （相等的情况已经统计过）的好的子数组，当 $sum_{r-1}-sum_{l}\ge\operatorname{highbit}(a_r)\times2$ 时，退出枚举。

这样看起来对于每个 $l$ 都可能是 $O(n)$ 级别的枚举，但我们仔细分析一下：以固定 $l$ 找 $r$ 为例，对于每一个 $r$，考虑第一个找到它的 $l$，此时 $sum_{r-1}-sum_{l}\ge\operatorname{highbit}(a_l)\times2$，则 $(l,r)$ 中满足 $\operatorname{highbit}(a_i)=\operatorname{highbit}(a_l)$ 的 $i$ 不超过 $1$ 个，则对于每个 $r$，每种 $\operatorname{highbit}$ 的 $l$ 最多只会枚举到 $2$ 次，总复杂度不超过 $O(n\log a)$。

---

## 作者：nkwhale (赞：3)

[我觉得会好一点的阅读体验](https://www.cnblogs.com/whale-at-cola/p/solution-cf1438e.html)

发现我的垃圾做法好像和别人有些不同，分享一下。

题目传送门：[luogu](https://www.luogu.com.cn/problem/CF1438E)，[CF](https://codeforces.com/problemset/problem/1438/E)。

规定：记序列 $s$ 表示序列 $a$ 的前缀和，$highbit(x)$ 表示数 $x$ 的最高位，序列 $a$ 值域为 $m$。

首先考虑枚举一个端点找答案，不妨枚举 $l$，然后寻找枚举 $r$ 的性质来减少枚举。

考虑左端点 $l$，不难发现对于一个 $l$ 之后最小的位置 $k$ 满足 $highbit(s_k-s_l)>highbit(a_l)$，$k$ 之后的所有位置 $j$ 若要作为右端点 $r$，因为 $a_l$ 的第 $highbit(s_{j-1}-s_l)$ 位必然为 $0$，所以 $j$ 必须满足 $highbit(a_j) \geq highbit(s_{j-1}-s_l)$，这时，对于 $j$ 后的每一个位置 $j'$，显然 $highbit(s_{j'-1}-s_l)$ 大于 $highbit(s_{j-1}-s_l)$，而 $highbit$ 至多增大到 $\log_2 m$，所以 $k$ 后满足条件的右端点数量最多只有 $\log m$ 个。根据这个结论，只要对于每个位置预处理它后面第一个 $highbit(a_j)$ 大于某个位的位置 $j$，即可将对满足 $r>k$ 的右端点 $r$ 的枚举优化到 $O(n\log_2 m)$ 的复杂度。

然后考虑 $r\leq k$ 的情况，直接暴力做复杂度就是对的，别的题解里都有这部分的证明，我就不再赘述。

时空复杂度均为 $O(n\log_2 m)$，代码见下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
typedef long long ll;
inline int win(){
	int x=0,w=0;char c=getchar();
	while(c>'9'||c<'0') w|=c=='-',c=getchar();
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return w?-x:x;
}

const int N=202020;
int p[N][31];ll a[N],s[N];

signed main(){
	int n=win(),ans=0;
	for(re int i=1;i<=n;++i) a[i]=win(),s[i]=a[i]+s[i-1];
	for(re int j=0;j<30;++j) p[n][j]=n+1;
	for(re int i=n,l;i>=1;--i){
		l=63-__builtin_clzll(a[i]);
		for(re int j=0;j<=l;++j) p[i-1][j]=i;
		for(re int j=l+1;j<30;++j) p[i-1][j]=p[i][j];
	}
	for(re int i=1,j,lmt;i<=n;++i){
		j=i+1,lmt=64-__builtin_clzll(a[i]);
		for(;j<n&&s[j]-s[i]<(1ll<<lmt);++j) if(s[j]-s[i]==(a[i]^a[j+1])) ++ans;
		if(j<n){
			lmt=63-__builtin_clzll(s[j]-s[i]),j=p[j][lmt];
			for(;j<=n&&lmt<=30;lmt=63-__builtin_clzll(s[j]-s[i]),j=p[j][lmt]) if((a[j]^a[i])==s[j-1]-s[i]) ++ans;
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Piwry (赞：3)

## 解析

（这里先分析复杂度相关，然后再讲具体做法（最后可能有很多可行的实现方式））

### Part0

首先不难发现 $a+b\geq a⊕b$

于是我们的大致思路就是枚举满足 $a_l+a_r\geq \sum\limits_{i=l+1}^{r-1}a_i$ 的区间；只要证明最终满足要求的区间个数不多，这种思路就是可行的

### Part1

可以证明这样的区间个数是不超过 $n\log a$ 的：

&nbsp;

首先我们发现，在任意满足要求的区间中，一定能找到一点 $k, l < k < r$ 满足 $a_l\geq\sum\limits_{i=l+1}^{k}, a_r\geq\sum\limits_{i=k+1}^{r-1}$。证明只需考虑反证法

于是我们考虑枚举这个中间点 $k$，并向左右 “扩张”；不难发现左右满足要求的 $l, r$ 各不会超过 $\log a$ 个。这里只对 $r$ 做证明：只需考虑，对于两个答案点 $r_1, r_2$，不妨设 $r_1<r_2$，发现 $\sum\limits_{i=k+1}^{r_2-1}$ 一定**包含** $a_{r_1}$，于是 $a_{r_2}$ 相比 $a_{r_1}$ 必定翻倍

枚举的中间点 $k$ 不超过 $n$ 个；于是这样算出的区间个数上界就是 $n\log^2 a$ 的

&nbsp;

但发现每个区间其实可能会被不同的 $k$ 多次统计

我们具体分析下，当 $k$ 变为 $k+1$ 时，合法左端点集合 $\{l_i\}$ 与合法右端点集合 $\{r_i\}$ 的变化

对于 $\{l_i\}$，可以发现：对于原先不在 $\{l_i\}$ 的端点，仍旧不能作为合法的左端点（只需考虑端点处值不变，但 $\sum$ 变大了）；原先在 $\{l_i\}$ 中的端点，此时可能 “失效” 了；而新增的左端点，只有可能是 $k$ 这个点

对于 $\{r_i\}$，可以发现：对于原先不在 $\{r_i\}$ 的端点，此时可能成为新的合法的右端点（证明仍考虑值不变，$\sum$ 变大）；原先在 $\{r_i\}$ 中的端点，此时基本都在；唯一一个例外是是 $k+1$ 这个点可能从 $\{r_i\}$ 中消失

于是不难发现，当 $k$ 变为 $k+1$ 时，$\{l_i\}, \{r_i\}$ 的元素变化个数都是**均摊** $O(1)$ 的（这里具体说起来其实有点有趣：$\{l_i\}$ 是删除时均摊 $O(1)$ 个，而 $\{r_i\}$ 正好反过来）。于是对于 $k$ 变为 $k+1$，新增的不同区间事实上只有约 $2\cdot\log a$ 个（新加入的 $l, r$ 端点分别与原先存在的端点组合）

于是总的不同区间个数就是 $n\log a$ 的

### Part2

最后考虑如何实现

一种方式是，考虑先反着扫一遍，预处理出每个 $k$ 的 $r$ 点（具体实现的话，反着扫 $\{r_i\}$ 的变化情况就和顺着扫的 $\{l_i\}$ 一样了，于是只需从已有的 $\log a$ 个 $\{r_i\}$ 中检查）；这样对每个 $k$ 就可以 $O(1)$ 得知其的 $\{r_i\}$ 集合（否则的话，每次都要检查所有不在 $\{r_i\}$ 内的元素，是 $O(n)$ 的）。再结合刚才的证明过程，顺着扫一次，统计时不要多次检查同一个区间即可。这样直接实现的时间复杂度是 $O(n\log a)$ 的，但空间复杂度也是 $O(n\log a)$ 的；可能有类似思路的写法可以优化空间复杂度

另一种方式是，既然已经证明不同的区间个数仅有 $n\log a$ 个，那么就直接枚举左端点 $l$，利用线段树查询满足要求的右端点 $r$。这样的时间复杂度是 $O(n\log a\log n)$ 的

对于第二种方式，具体来说的话，就是考虑我们需要对每个 $l$ 找到所有的 $r$ 满足 $a_l+a_r\geq \sum\limits_{i=l+1}^{r-1}a_i$。设 $s_i$ 表示前缀和数组，上式即 $s_r-s_{l-1}\geq 2(s_{r-1}-s_l)$，即 $s_r-2s_{r-1}\geq s_{l-1}-2s_l$。于是线段树维护区间最大的 $s_r-2s_{r-1}$，线段树询问函数内暴力向下递归所有可能有答案的区间即可。具体实现细节可见下面代码

## CODE

这里仅有线段树的实现（另一种暂时咕咕 \fad）

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using std::max;

const int MAXN =2e5+20, MAXT =1<<19;

/*------------------------------Array------------------------------*/

int a[MAXN];
ll s[MAXN];

/*------------------------------Seg------------------------------*/

int N =1;
ll mx[MAXT];

/*s_r-2s_{r-1} \geq s_{l-1}-2s_l*/
void query(const int &l, const int &r, const int &pos, int &ans, const int &nl =1, const int &nr =N, const int x =1){
	int mid =(nl+nr)>>1;
	if(nl == nr){
		if(nl-pos >= 2 && (a[pos]^a[nl]) == s[nl-1]-s[pos+1 -1])
			++ans;
	}
	else if(l == nl && r == nr){
		if(mx[x<<1] >= s[pos-1]-2*s[pos])
			query(nl, mid, pos, ans, nl, mid, x<<1);
		if(mx[x<<1^1] >= s[pos-1]-2*s[pos])
			query(mid+1, nr, pos, ans, mid+1, nr, x<<1^1);
	}
	else{
		if(r <= mid)
			query(l, r, pos, ans, nl, mid, x<<1);
		else if(l >= mid+1)
			query(l, r, pos, ans, mid+1, nr, x<<1^1);
		else
			query(l, mid, pos, ans, nl, mid, x<<1), query(mid+1, r, pos, ans, mid+1, nr, x<<1^1);
	}
}

inline void pushup(const int &x){
	mx[x] =max(mx[x<<1], mx[x<<1^1]);
}

/*------------------------------Main------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

int main(){
	int n =read();
	for(int i =1; i <= n; ++i)
		a[i] =read(), s[i] =s[i-1]+a[i];
	
	while(N < n)
		N <<=1;
	for(int i =N; i < N+n; ++i)
		mx[i] =s[i-N+1]-2*s[(i-N+1)-1];
	for(int i =N+n; i < N*2; ++i)
		mx[i] =-0x3f3f3f3f3f3f3f3f;
	for(int i =N-1; i >= 1; --i)
		pushup(i);
	
	int ans =0;
	for(int l =1; l <= n; ++l)
		query(l, n, l, ans);
	printf("%d", ans);
}
```

---

## 作者：Clouder (赞：3)

看看官方题解，利用了异或的性质。

$$a_l \oplus a_r < 2^{highbit + 1}$$

此处 $highbit$ 指 $a_l$ 与 $a_r$ 的最高为 $1$ 的位。  

首先枚举左端点，跳右端点，我们假定 $a_l \ge a_r$ 来统计。

等一会翻转数组，再统计一遍，就可以覆盖所有的情况。再去个重就行了。

然后考虑怎么统计。

对于每个 $l$，暴力枚举 $r$ 去检查，保证 $\sum \limits _{i=l+1}^{r-1} a_i < 2^{highbit+1}$ 即可。

这样复杂度是如何保证的？看上去每个 $l$ 都可能跑满 $O(n)$，而导致最后退化为 $O(n^2)$ 的复杂度。

然而使用奇怪的整体分析，可以发现这样复杂度是真的。

对每一个 $highbit$ 单独考虑复杂度。

对于若干个 $a_{b_i}$ 满足其最高位为 $highbit$ 时，其下标序列为 $b_1 < b_2 < \ldots < b_k$

考虑 $l = b_i$ 时的情况，可以发现它的右端点 $r$ 至多走到 $b_{i+2}$ 就会停止，因为两个最高位相加进位了，不再满足 $\sum \limits _{i=l+1}^{r-1} a_i < 2^{highbit+1}$。

那么一共会走过 $\sum \limits _{i = 1}^k (b_{i+2} - b_i)$ 个位置，这个的上界是 $2 \times n$，那么每位的总时间都是线性的。

总复杂度 $O(n \log a_i)$

```cpp
#include <cstdio>
#include <algorithm>
#include <set>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
int n, a[maxn], hb[maxn];
set<pair<int,int> > S;
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = 29; j >= 0; --j) if (a[i] & (1 << j)) { hb[i] = j; break; }
    for (int l = 1; l <= n; ++l)
    {
        int maxx = 1 << (hb[l] + 1);
        long long now = a[l + 1];
        for (int r = l + 2; r <= n; ++r)
        {
            if (now >= maxx) break;
            if ((a[l] ^ a[r]) == now) S.insert(make_pair(l, r));
            now += a[r];
        }
    }
    for (int r = n; r > 0; --r)
    {
        int maxx = 1 << (hb[r] + 1);
        long long now = a[r - 1];
        for (int l = r - 2; l > 0; --l)
        {
            if (now >= maxx) break;
            if ((a[l] ^ a[r]) == now) S.insert(make_pair(l, r));
            now += a[l];
        }
    }
    printf("%d\n",S.size());
    return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 题解思路：
我们会发现一个性质：满足条件的区间不会很多。

因为满足条件的数很少，所以我们就可以用暴力。

我们先假设，这个区间是以 $a_l$ 为主导的，就是 $a_l$ 是 $a_l$ 和 $a_r$ 里二进制最高的一位。

对于这样的情况下，那么我们就暴力求满足条件的区间就可以了。

先对于 $l$ 枚举 $r$。

终止条件是什么呢？

我们假设最高位是第 k 位，那么 $\sum^{n}_{i = 1}a_i$ 一定要 $\le 2^{k + 1}$，首先我们最大值在第 k 位上，而异或又是不进位加法，所以这个区间的和就是一定要 $\le 2^{k + 1}$ 的。

所以我们就暴力枚举 $r$，当遇到不符合这个条件的 $r$ 时，就终止就可以了。

然后再倒着，对于 $r$ 枚举 $l$，就可以了。

## 证明时间复杂度：
假设这是以第 $k$ 位二进制，那么最多有 $\log n$ 位二进制。对于每个二进制的情况下呢，我们去讨论。

我们假设二进制最高位为 $k$，的下标有： $p_1 , p_2 ... ... p_n$，假设 $l = p_1$，那么当 $r = p_3$ 时一定会终止，因为要是 $l = p_1 , r = p_3$ 时，累加和就是：$p_2 + p_3$ 而这个数一定会超过 $2^{k + 1}$。

那么对于每个下标累加和是多少：
$\sum^{x}_{i = 3} p_i - p_{i - 2}$

那么这些数的累加和算下来他就是 $p_x + p_{x - 1} - p_1 - p_2 \le 2n$，就是一个 $O(n)$ 级别的。

有 $\log n$ 次操作，，每次 $O(n)$ 总时间复杂度为 $O(n \log n)$

## AC CODE:
```cpp
#include <iostream> 
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include <set>
using namespace std;
typedef long long ll;
const int N = 200010;
int n;
int a[N];
set <pair <int , int>> s;//用set去重
int log2 (int x) {//求log2 
	int cnt = 0;
	while (x) {
		++ cnt;
		x >>= 1;
	}
	return cnt;
}
void solve (bool op) {//0代表正着，1代表倒着 
	vector <int> pre (n + 10);
	for (int i = 1; i <= n; ++ i)
		pre[i] = pre[i - 1] + a[i];//求前缀和 
	for (int i = 1; i <= n - 2; ++ i) {
		ll sum = a[i + 1];
		int x = log2 (a[i]) + 1;
		for (int j = i + 2; j <= n; ++ j) {
			if ((a[i] ^ a[j]) == pre[j - 1] - pre[i]) {//看看这个区间是否满足这个性质 
				if (!op) s.insert ({i , j});//正着直接插入 
				else s.insert ({n - j + 1 , n - i + 1});//倒着 
			}
			if ((sum + a[i]) > (1ll << x)) break;//超过了范围，break 
			sum += a[j];
		}
	}
}
int main() {
	scanf ("%d" , &n);
	for (int i = 1; i <= n; ++ i)
		scanf ("%d" , &a[i]);
	solve (0);//正着来
	reverse (a + 1, a + 1 + n);
	solve (1);//倒着来
	printf ("%d\n" , (int)s.size());//输出答案
	return 0;
}
```
码字不易，求赞！

---

## 作者：Albedo (赞：0)

# CF1438E Yurii Can Do Everything

## Introduction

技不如人，甘拜下风。

## Solution

我们首先观察题目给出的条件:
$$
a(l)\oplus a(r)=\sum_{l+1}^{r-1} a(i)
$$
那么其实我们可以有一个结论：如果 $ \sum_{l+1}^{r-1} a(i) $ 已经大于了 $ \max(a(l),a(r)) $ 的二进制最高位的后一位，那么他一定是不可能合法的。有了这个结论，我们可以有一个高妙的做法，就是我们从 $ l $ 的这一段开始，$ r $ 用一根指针一直向后扫，知道他大于了 $ a(l) $ 的二进制最高位的后一位为止，然而这样子一定是有重复的，如何解决？我们可以从 $ r $ 的那一段再向前扫，用同样的做法，为什么这样子是可行的呢？

因为这个二进制最高位的后一位的大小在起始点给定后是不会变的，所以长度是单调的，不存在移动到一半就停下来，再后面又可以的情况。

正确性已经证明了，我们还需要解决的是为什么他的复杂度是正确的，我们考虑对每一位进行分析。

我们假设现在在处理的这一位是 $ x $，那么他最多经过两个最高位是他之后就不行了，那么对每一位所会移动的最大次数都是 $ n $，而总共只有 $ 30 $ 几位，所以复杂度就保证了。

## Code

```c++
	n=read();
	for (i=1;i<=n;i++) a[i]=read();
	for (lft=1;lft<=n-2;lft++){
		up=check(a[lft]);
		
		rit=lft+2;sum=a[lft+1];
		while ((rit<=n)&&(sum<=up)){
			if (sum==(a[rit]^a[lft])) G.insert(make_pair(lft+1,rit-1));
			sum+=a[rit];rit++;
		}
	}
	for (rit=n;rit>=3;rit--){
		up=check(a[rit]);//找到二进制最高位的后一位
		lft=rit-2;sum=a[rit-1];
	    while ((lft>=1)&&(sum<=up)){
	    	
			if (sum==(a[rit]^a[lft])) G.insert(make_pair(lft+1,rit-1));
			sum+=a[lft];lft--;
		}
	}
	cout<<G.size()<<endl;
```

## Enlightenment

看到一些看似没有用处的优化的时候，不要直接放弃，花一点时间去思考一下暴力优化是否就是正解。

---

