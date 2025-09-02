# Sasha and a Bit of Relax

## 题目描述

Sasha likes programming. Once, during a very long contest, Sasha decided that he was a bit tired and needed to relax. So he did. But since Sasha isn't an ordinary guy, he prefers to relax unusually. During leisure time Sasha likes to upsolve unsolved problems because upsolving is very useful.

Therefore, Sasha decided to upsolve the following problem:

You have an array $ a $ with $ n $ integers. You need to count the number of funny pairs $ (l, r) $ $ (l \leq r) $ . To check if a pair $ (l, r) $ is a funny pair, take $ mid = \frac{l + r - 1}{2} $ , then if $ r - l + 1 $ is an even number and $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_{mid} = a_{mid + 1} \oplus a_{mid + 2} \oplus \ldots \oplus a_r $ , then the pair is funny. In other words, $ \oplus $ of elements of the left half of the subarray from $ l $ to $ r $ should be equal to $ \oplus $ of elements of the right half. Note that $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

It is time to continue solving the contest, so Sasha asked you to solve this task.

## 说明/提示

Be as cool as Sasha, upsolve problems!

In the first example, the only funny pair is $ (2, 5) $ , as $ 2 \oplus 3 = 4 \oplus 5 = 1 $ .

In the second example, funny pairs are $ (2, 3) $ , $ (1, 4) $ , and $ (3, 6) $ .

In the third example, there are no funny pairs.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
3 2 2 3 7 6
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
42 4 2
```

### 输出

```
0
```

# 题解

## 作者：zhangqiuyanAFOon2024 (赞：3)

### 思路
我们要找有几对 $l$ 和 $r$。

首先 $q$ 是前缀和数组。

题目中两个东西要相等。

这里用到了一个性质：两个相同的数异或起来是等于 $0$ 的，所以可以抵消。

即第一个是 $\bigoplus_{i=l}^{(l+r-1)/2}a_i=q_{l-1}\bigoplus q_{(l+r-1)/2}$。

第二个是 $\bigoplus_{i=(l+r-1)/2+1}^{r}a_i=q_r\bigoplus q_{(l+r-1)/2}$。



那么 $q_{l-1}\bigoplus q_{(l+r-1)/2}=q_r\bigoplus q_{(l+r-1)/2}$ 也就是 $q_{l-1}=q_r$。

因为要求 $l-r+1=l-(r-1)$ 为偶数，所以 $l$ 和 $r-1$ 同奇偶。

我们可以弄一个 `map` 来记录，第一维存奇偶，第二维存数值，如果两个相等就是中间的那一段为 $0$，然后记录答案。

### 代码

注意一下，$mp_{0,0}$ 要等于 $0$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
map<int,int>mp[2];
int a[N],q[N];
signed main(){
	int n,cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		q[i]=q[i-1]^a[i];
	}
	mp[0][0]=1;
	for(int i=1;i<=n;i++){
		cnt+=mp[i%2][q[i]];
		mp[i%2][q[i]]++;//记录，i%2是奇偶
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：decoqwq (赞：3)

因为两边异或值相等，所以原题等价于求有多少个区间$⨁\limits_{i=l}^r a_i=0$

那么容易想到记录一个异或前缀和，每次加上之前前缀和相同的个数即可
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300010];
int k[300010];
map<pair<int,int>,int> mp;
int main()
{
    int n;
    cin>>n;
    long long int ans=0;
    pair<int,int> k1;
    k1.first=0,k1.second=1;
    mp[k1]++;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        k[i]=k[i-1]^a[i];
        int x=!(i&1);
        pair<int,int> p;
        p.first=k[i],p.second=x;
        ans+=mp[p];
        mp[p]++;
    }
    cout<<ans;
}
```


---

## 作者：Echoternity (赞：2)

既然过了就写一篇题解吧。

题意已经有翻译了，就不必赘述。这里讲一些这道题的特点。

### 异或和

首先 $x \oplus x = 0$ 以及 $x \oplus 0 = x$ 这两个公式是必要的，而我们设

$sum_1=a_l \oplus a_{l+1} ... \oplus a_{(l+r-1)/2}$

$sum_2=a_{(l+r)/2} \oplus a_{(l+r+1)/2} ... \oplus a_{l+r}$

由题意得 $sum_1=sum_2$ ，则有 $sum_1 \oplus sum_2 =0$

而异或运算满足加法性质，即 $(a \oplus b) \oplus c = a \oplus (b \oplus c)$ 的性质。

那么我们需要查找的区间也就是满足 $ \bigoplus\limits_{i=l}^rval_i=0$ 的区间即可。我们又有 $x \oplus x=0$ 那么对于一个区间满足上述式子，

记 $sum_i$ 为该数列的异或前缀和，则有 $sum_{l-1} \oplus sum_r =0$ 满足上述式子，也就是 $sum_{l-1}=sum_r$ 的区间，用 `map` 来存储即可。

记得判断 `(r-l+1)\mod 2=0` 可以用位运算 `(r-l+1)&1==0` 来代替。

最后几个点比较大，记得开 `long long` 。否则会 WA

``` c++
省略预处理代码
using namespace std;
const int MAXN=3e5+1;
template<class T>
inline void read(T &x)
{
    x=0;
    char ch=gh(),t=0;
    while(ch<'0'||ch>'9') t|=ch=='-',ch=gh();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=gh();
    if(t) x=-x;
}
ll n,val,sum[MAXN];
ll res;
map<pair<ll,ll>,ll>M;
int main()
{
    // freopen("segment.in","r",stdin);
    // freopen("segment.out","w",stdout);
    read(n);
    ++M[make_pair(0,1)];
    for(int i=1;i<=n;++i)
    {
        read(val);
        sum[i]=sum[i-1]^val;
        ll x=!(i&1);
        res+=M[make_pair(sum[i],x)];
        ++M[make_pair(sum[i],x)];
    }
    printf("%lld",res);
    return 0;
}
/*
5
1 2 3 4 5
6
3 2 2 3 7 6

x^x=0
x^0=x
*/
```

上述代码是用 STL 库中的 `map` 写的，下面给出手写代码。因为其 `val` 值最大是 $2^{20}$ 所以所有的异或和不会超过 $2^{21}-1$ 所以数组开那么大就合适了。维护一个 `bool` 值表示当前位置是奇数还是偶数，然后加答案后统计该位置所对应的 `(r-l+1) \mod 2 = 0` 的位置后统计答案即可。

``` c++
依然省略头文件
using namespace std;
const int MAXN=3e5+1;
const int MAXS=1<<21;
template<class T>
inline void read(T &x)
{
    x=0;
    char ch=gh(),t=0;
    while(ch<'0'||ch>'9') t|=ch=='-',ch=gh();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=gh();
    if(t) x=-x;
}
ll n,val,sum[MAXN];
ll res,ans[MAXS][2];
int main()
{
    // freopen("segment.in","r",stdin);
    // freopen("segment.out","w",stdout);
    read(n);
    ++ans[0][1];
    for(int i=1;i<=n;++i)
    {
        read(val);
        sum[i]=sum[i-1]^val;
        ll x=!(i&1);
        res+=ans[sum[i]][x];
        ++ans[sum[i]][x];
    }
    printf("%lld",res);
    return 0;
}
/*
5
1 2 3 4 5
6
3 2 2 3 7 6

x^x=0
x^0=x
*/
```

欢迎来蒟蒻的[blog](https://violeteternal.github.io/Eternity/)来 cue 。

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1109/A)
我们需要找到数组中满足以下条件的子数组对 $(l,r)$：
1. 子数组长度为**偶数。**
2. 子数组的左半部分的异或和等于右半部分的异或和。

## 思路
需要一点前置知识，如果知道的话那么此题十分简单。

首先，如果直接暴力枚举的话，时间复杂度为 $ \mathcal{O}(n^3) $。如果用**前缀和**优化区间异或和计算的话，可以将复杂度降至 $ \mathcal{O}(n^2) $，可还是过不了。

再看一下题目，题目要求我们找到满足：

1. $r-l+1 \equiv 0 \pmod 2$
2. $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_{mid} = a_{mid + 1} \oplus a_{mid + 2} \oplus \ldots \oplus a_r $
3. $l \leq r$

的 $(l,r)$ 组数。

注意第二条，记左边部分为 $p$，右边部分为 $q$，那么第二条就转换为 $p = q$。

如果还没看出来什么的话，可以去了解一下[异或的性质](https://blog.csdn.net/m0_46202073/article/details/116902135)。

因为异或具有**自反性**，$(p \oplus q)$ 成立**当且仅当** $p = q$。

不妨记录一个前缀异或数组，一一枚举 $r$。

问题来了，$l$ 怎么找？

看看上面的第一条：

> $r-l+1 \equiv 0 \pmod 2$

这意味着，$l-1$ 与 $r$ 奇偶性相同。

用一个 `unordered_map` 记录**前缀异或值**的出现次数，分为**奇数和偶数**两种情况即可。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300005];
int s[300005];// 前缀异或数组
// 哈希表记录前缀异或值的出现次数
// 分为奇数和偶数两种情况
unordered_map<int, int> cnt[2];
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		s[i] = s[i - 1] ^ a[i - 1];
	}
	cnt[0][0] = 1; // s[0] = 0，且 s[0] 的奇偶性为偶数
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		int k = i % 2; // 当前前缀的奇偶性
		if (cnt[k].count(s[i])) {
			ans += cnt[k][s[i]];
			cnt[k][s[i]]++;
		} else {
			cnt[k][s[i]] = 1;
		}
	}
	cout << ans << endl;
	return 0;
}
```
时间复杂度 $ \mathcal{O}(n) $，可以通过本题。

---

## 作者：heyZZZ (赞：1)

翻译：

求有多少个区间内的数异或值为 $0$。

思路：

处理出前缀异或数组 $q$。

如果 $q_i=q_j$，则区间是存在的。

代码楼上楼下都已经写的很明白了，我就不在赘述了。

---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1109A)

## 分析

求：

$$\sum_{1 \le l \le r \le n}[\bigoplus \limits_{i=l}^{k} a_i= \bigoplus \limits_{j=k+1}^{r} a_j]$$

其中 $r-l+1$ 一定是偶数且 $k=\dfrac{l+r-1}{2}$。

首先令 $s_i = \bigoplus \limits_{j=1}^{i} a_j$，那么就有 $s_k \bigoplus s_{l-1}=s_r \bigoplus s_k \rightarrow s_{l-1} = s_r$，于是变成了简单的统计相等数对的问题。对于区间长度为偶数的限制，不难发现 $l-1$ 与 $r$ 的奇偶性相同。

## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e6 + 10;
int n, a[N], cnt[2][N];
ll ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] ^= a[i - 1];
	for (int i = 0; i <= n; i++) ans += cnt[i & 1][a[i]], cnt[i & 1][a[i]]++;
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：JWRuixi (赞：0)

~~啊，尽然没有一眼~~

- 题意

给定长度为 $n$ 的序列 $a$，求有多少区间 $[l,r]$ 满足 $r-l+1\equiv0\bmod2\land \bigoplus_{i=l}^{mid}a_i=\bigoplus_{i=mid+1}^ra_i$。

- 分析

因为是是异或运算，所以上述条件等价于 $\bigoplus_{i=l}^ra_i=0\land r-l+1\equiv0\bmod2$。
于是可以直接统计有多少个长度为偶数且区间异或和为 $0$ 的区间，由于至于很小，直接开个 $cnt_{0/1}$ 数组分别统计端点是偶数还是奇数是的前缀和 $cnt$ 数组就行了。

复杂度 $\mathcal O(n)$。

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
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
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

const int maxn(3e5 + 500);
int n, a[maxn], c[2][2000007];
LL ans;

int main() {
	n = read(), c[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		a[i] = read() ^ a[i - 1];
		ans += c[i & 1][a[i]], c[i & 1][a[i]]++;
	}
	write(ans);
}
// I love WHQ!
```

---

## 作者：David_H_ (赞：0)

## 题意简述

给定一个含 $n$ 个整数的序列 $a$，定义 $(l,r)$ 是一个“有趣的序列”当且仅当$r>l$，$r-l+1$ 为偶数，且 $a$ 中下标自 $l$ 到 $\dfrac{l+r-1}{2}$ 的数的异或和等于下标自 $\dfrac{l+r-1}{2}+1$ 到 $r$ 的数的异或和。求序列 $a$ 中“有趣的序列”的个数。

## 思路简述

我们看到题目，首先想到的是异或前缀和。

显然
$$\left(\bigoplus_{i=l}^{\frac{l+r-1}{2}}a_i\right)\oplus\left(\bigoplus_{i=\frac{l+r-1}{2}+1}^{r}a_i\right) = 0$$

所以题目即求有多少个区间 $(l,r)$ 使得
$$\bigoplus_{i=l}^{r}a_i = 0$$

然而对于任意的数 $p$，均满足
$$p\oplus 0 = p$$

所以，求
$$\bigoplus_{i=l}^{r}a_i = 0$$
即求有多少个区间前缀和相等，这样中间的就是 $0$ 了。

注意还要判断奇偶性。
## 代码

实现比较简单，就不贴了。

---

