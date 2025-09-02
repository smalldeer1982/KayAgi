# Infinite Set

## 题目描述

You are given an array $ a $ consisting of $ n $ distinct positive integers.

Let's consider an infinite integer set $ S $ which contains all integers $ x $ that satisfy at least one of the following conditions:

1. $ x = a_i $ for some $ 1 \leq i \leq n $ .
2. $ x = 2y + 1 $ and $ y $ is in $ S $ .
3. $ x = 4y $ and $ y $ is in $ S $ .

For example, if $ a = [1,2] $ then the $ 10 $ smallest elements in $ S $ will be $ \{1,2,3,4,5,7,8,9,11,12\} $ .

Find the number of elements in $ S $ that are strictly smaller than $ 2^p $ . Since this number may be too large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, the elements smaller than $ 2^4 $ are $ \{1, 3, 4, 6, 7, 9, 12, 13, 15\} $ .

In the second example, the elements smaller than $ 2^7 $ are $ \{5,11,20,23,39,41,44,47,79,80,83,89,92,95\} $ .

## 样例 #1

### 输入

```
2 4
6 1```

### 输出

```
9```

## 样例 #2

### 输入

```
4 7
20 39 5 200```

### 输出

```
14```

## 样例 #3

### 输入

```
2 200000
48763 1000000000```

### 输出

```
448201910```

# 题解

## 作者：NXYorz (赞：13)

[题目链接](https://www.luogu.com.cn/problem/CF1635D)

-----

### 分析
发现 $p$ 比较大，因此可以将其放在二进制下考虑。因此容易想到看操作在二进制下带来的影响：

- 在其二进制末尾添加一个 $1$
- 在其二进制末尾添加两个 $0$

通过观察可以发现，对于一个数 $x$ ，这两种操作是互不影响，不会重复的(在二进制下显然)。因此如果想要将其添加 $i$ 位的方案数 $f_i = f_{i - 1} + f_{i - 2}$，并且 $f_0 = f_1= 1$，因此对于一个数的方案数就是斐波那契数列的前 $n$ 项和。

对于多个数，发现某个数 $x$ 与其扩展出的方案可能是另一个数 $y$ 的子集（即 $x$ 可以由 $y$ 扩展而来)，这种 $x$ 直接剔除就好。因此问题就转化成了如何判断一个数是否应该被剔除，发现如果一个数被剔除说明它的某一个前缀就在集合中，又因为这两种操作互不影响，所以 $x$ 的上一个状态是唯一确定的，因此只需要向前一步一步推状态，看是否有状态已经存在即可。

最后把所有没有被剔除的元素的方案数加起来求和就可以了

### $\texttt{Code}$
```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;

int n,p,BIT;
vector<int> a,b;
map<int , bool> v;
ll ans,f[N],sum[N];

bool check(int x) {
    
    while(x) {
        if(v[x]) return false;
        if(x & 1) x >>= 1;
        else if(x & 2) break;
        else x >>= 2;
    }
    return true;
}

int main() {
    freopen("aa.in","r",stdin);
    scanf("%d%d",&n,&p);

    for(int i = 1; i <= n; i++) {
        int x; scanf("%d",&x);
        a.push_back(x);
    }

    sort(a.begin() , a.end());

    for(auto x: a) 
        if(check(x)) b.push_back(x) , v[x] = 1;

    f[1] = f[2] = 1;
    sum[1] = 1 , sum[2] = 2;
    for(int i = 3; i <= p + 1; i++)
        f[i] = (f[i - 1] + f[i - 2]) % mod , sum[i] = (sum[i - 1] + f[i]) % mod;

    for(auto x: b) {
        int Bit = 0;
        for(int i = 0; i <= 31; i++)
            if(x >> i) Bit = i + 1;
        if(p + 1 > Bit) ans = (ans + sum[p + 1 - Bit]) % mod;
    }
    printf("%lld",ans);
}
```

---

## 作者：CSP_Sept (赞：9)

### 大意

集合 $S$ 满足：

- $a_i\in S$
- $\forall x\in S$，$2x+1\in S,4x\in S$

求 $S$ 中小于 $2^p$ 的元素数量。

### 解法

本来应该录视频题解的但没时间 /dk

下面把 $2x+1,4x$ 称作「变换」，若 $x$ 可以通过变换得到 $y$，则称「$x\to y$ 存在」。

在学校里笔算做题，找到个很有趣的性质：

我们令 $f(x)=\left\lfloor\log_2x\right\rfloor$。

接下来我们讨论 $f(x)$ 的取值，下图很好的展示了每个 $a_i$ 的 $f$ 值在每次变化中发生了什么变化。

![](https://cdn.luogu.com.cn/upload/image_hosting/hoov8110.png)

容易发现存在 $i\to 2i+1,i\to 4i,2i+1\to 4i+3$。

自下而上每层数字的个数满足关系 $1+1=2$，这是否是巧合呢？

事实上，我们经过简单的数学推导，记 $c(i)$ 表示满足 $f(x)=i$ 且 $x\in S$ 的 $x$ 的个数，于是有 $c(i)=c(i-1)+c(i-2)$。

对于一个 $a_i$，容易发现答案就是 $\sum_{i=0}^{p-1}c(i)$。

但问题随之出现：多个 $a_i$ 可能存在重复状态，例如样例 2 中的 $5,20$。

我们考虑 $x$ 变化时的二进制变换，发现 $2x+1$ 就是在末尾添上 $\texttt1$，$4x$ 就是在末尾添上 $\texttt{00}$。

我们观察到如果 $a_i\to a_j$ 存在，则必然有：

1. $a_i<a_j$。
2. $a_j$ 实际上无效。

性质 2 是因为 $a_j$ 变换产生的任何数都可以由 $a_i$ 变换得到。

设 $U$ 表示有效的 $a_i$ 的集合，元素个数为 $m$，元素记作 $u_1\sim u_m$。

考虑对于每个 $a_i$，依次去掉其二进制末尾的 $\texttt{1/00}$ 直到不能操作为止，若中途有一个数在 $U$ 中，则 $a_i$ 无效，否则将 $a_i$ 加入到 $U$ 中。

当然由于性质 1，我们需要对 $a$ 排序。

最后我们记 $c'(k)=\sum_{i=1}^m[f(u_i)=k]$，则有转移方程：

$$
dp_i=dp_{i-1}+dp_i+c'(i)
$$

考虑答案，仍然是

$$
\sum\limits_{i=0}^{p-1}dp_i
$$

时间复杂度 $O(n\log A\log n+p)$，其中 $A=\max_{i-1}^na_i$。

### 核心代码

```cpp
// 判断是否有效
bool check(int x){
	while(x){
		if(x & 1) x >>= 1;
		else if(((x >> 1) & 1) == 0) x >>= 2;
		else break;
		if(binary_search(v.begin(), v.end(), x)) return 0;
	}
	return 1;
}

// dp 过程，注意取模问题
for(int i = 0 ; i < p ; i++){
	f[i] = c[i] % mod;
	if(i > 0) f[i] = (f[i - 1] + f[i]) % mod;
	if(i > 1) f[i] = (f[i - 2] + f[i]) % mod;
	ans = (ans + f[i]) % mod;
}
```

[完整版（$\textit{147533630}$）](http://codeforces.com/contest/1635/submission/147533630)

---

## 作者：eb0ycn (赞：2)

无心插柳柳成荫，半年前的模拟赛题，现在刷到了。

## 题意

给定一个长度为 $n$ 的数组 $a$。**保证数组 $a$ 中的所有元素互不相同**。

让我们规定一个无穷整数集合 $S$ 具有如下性质：

- $\forall 1\leqslant i\leqslant n$，$a_i$ 一定在集合 $S$ 中。
- 如果 $x$ 在集合 $S$ 中，那么 $2x+1$ 和 $4x$ 也一定都在集合 $S$ 中。

请求出集合 $S$ 中**严格小于** $2^p$ 的数的个数。由于结果可能很大，你只需要输出其对 $10^9+7$ 取模之后的值。


## 思路

“严格小于 $2^p$”，可以转化为“二进制位数小于 $p$（这里规定 $1$ 的二进制位数为 $0$）”。

$x \times 2 + 1$，可以转化为“在二进制下，在末尾加一个 $1$”；$x \times 4$ 类似。

可以发现，这两种操作互不重复。因为只有奇数才可能从一操作转移过来，$4$ 的倍数才可能从二操作转移过来。

设 $f_n$ 为某个数扩展 $n$ 位的方案数。可以发现，它与这个数原来是什么无关。具体地，$f_n = f_{n-1}+f_{n-2}$。

设 $g_n=\sum_{i=0}^n f_i$，那么对于一个数 $a_i$，如果集合中只有它，那么答案就是 $\large g_{p-\log_{2}{a_i}}$，因为它最多扩展到 $p$ 位。

那多个数重复怎么处理呢？我们可以把这个集合的数画成一个二叉森林，那么两个数贡献有交集，当且仅当它们存在祖先关系。考虑把 $a_i$ 从小到大排序，一个个检验是否与前面重复。

怎么处理？我们发现一个数会变成很多种数，但是每个数是由唯一确定的数转移过来的。若 $a_i$ 二进制末尾为 $1$，则只能由操作一转移过来；若 $a_i$ 二进制以 $\texttt{11}$ 结尾，说明它是根节点；若 $a_i$ 是 $4$ 的倍数，则只能由二操作转移过来。

做完了，时间复杂度 $O(n \log n + n \log V)$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,a[200001],f[200001],ans,bit,g[200001];
map<int,bool>mp;
bool ck(int x){
	while(x){
		if(mp[x])return 0;
		if(x&1)x>>=1;
		else if(x&2)return 1;
		else x>>=2;
	}
	return 1;
}
void mod(int&x){if(x>1000000006)x-=1000000007;}
int main(){
	f[0]=f[1]=g[0]=1,g[1]=2;
	for(int i=2;i<200001;++i)f[i]=(f[i-1]+f[i-2])%1000000007,g[i]=g[i-1]+f[i],mod(g[i]);
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		if(ck(a[i])){
			mp[a[i]]=1,bit=0;
			while(a[i])a[i]>>=1,++bit;
			if(p>=bit)ans=(ans+g[p-bit])%1000000007;
		}
	}
	return 0&printf("%d",ans);
}
```

---

## 作者：Cat_shao (赞：2)

给定一个长度为 $n$ 的序列 $a$ 。定义一个无限集合 $S$ ，如果 $x$ 在 $S$ 中只有如下几种情况：
1. $x = a_i \ (1 \le i \le n)$
2. $x = 2y + 1$ 且 $y$ 在 $S$ 中
3. $x = 4y$ 且 $y$ 在 $S$ 中

给定一个 $p$ ，求 $S$ 中 $< 2^p$ 的元素有多少个。

---------------

加入 $a$ 只有一个元素 $x \ (1 \le x < 2^p)$ 怎么做？ $< 2^p$ 的数等同于二进制下只有 $p$ 位，第二种操作相当于二进制下 $x$ 后面多一个 1 ，第三种操作相当于二进制下 $x$ 后面多两个 0 。 $x$ 在二进制下有 $\left \lfloor \log_2(x) \right \rfloor + 1$ 位，也就是说 $x$ 后面可以多出来 $1 \sim p - (\left \lfloor \log_2(x) \right \rfloor + 1)$ 位，这些不是由两个 0 就是由一个 1 组成。

$${\large \underset{ \le p}{\underbrace{\underset{\left \lfloor \log_2(x) \right \rfloor + 1}{\boxed{\qquad x \qquad}} \cdots }}}$$

记 $dp_i$ 为能用 `00` 和 `1` 摆成 $i$ 位的二进制串的个数。显然有

$$dp_i = \left \{\begin{array}{ll} 1 & (i \le 1) \\ dp_{i - 1} + dp_{i - 2} & (2 \le i \le p)\end{array} \right.$$

其中 $dp_{i - 1}$ 的意思是第 $i$ 为放 `1` ， $dp_{i - 2}$ 的意思是第 $i - 1, i$ 位放 `00` 。

对于一个数 $x$ ，从它用操作2、3推出的在 $S$ 中 $< 2^p$ 的数有 $\sum_{i = 0}^{p - (\left \lfloor \log_2(x) \right \rfloor + 1)} dp_i$ 个（包括 $x$ 自己），为方便计算可开一个数组 $sum$ 用于算前缀和， $sum_x = \sum_{i = 0}^{x}dp_i$ 。

------------------------------

现在我们来考虑 $a$ 中有多个元素。 $dp, sum$ 只需要算一遍，时间复杂度 $O(n)$ 。算每一个数都是 $O(1)$ 的，于是我们喜获了一个 $O(n)$ 的解法……吗？

考虑到给我们的 $a$ 中有“废物”。首先 $a$ 中 $\ge 2^p$ 直接不要了即可，记剩下了 $m$ 个元素。如果剩下这 $m$ 个元素中有 $x, y$ ， $x$ 能通过多次操作2、3后得到 $y$ ，则我们不能计算 $y$ （如果算了会算重复）。

怎么把向 $y$ 这样的“废物”扔出去呢？我们先对剩下的 $m$ 个元素排序。考虑到 $x < y$ ，开一个哈希表，从 1 到 $m$ 扫一遍，每到一个数字 $x$ 从后面有 `00` 删 `00` ，有 `1` 删 `1` ，如果删的途中发现这一数字在哈希表中出现过，则 $x$ 是“废物”，跳过这个数字。如果删到没法删了，那么 $x$ 不是废物，加入到哈希表中。

这一做法的时间复杂度是 $O(n \log \min\{\max_{1 \le i \le n}\{ a_i \}, 2^p\})$ ，各位可以大概看成 $O(n \log n)$ ，可以通过此题。

代码中 `& 3` 表示取后两位， `& 1` 表示取后一位。目前提交的人还很少，这份代码是暂时的最优解。

```cpp
//
// Created by Cat-shao on 2022/2/20.
//

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200010;
const int MOD = 1e9 + 7;

int n, p, a[MAX_N], f[MAX_N], sum[MAX_N], ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> p;
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= p - 1; ++i) {
        f[i] = (f[i - 1] + f[i - 2]) % MOD;
    }
    sum[0] = 1;
    for (int i = 1; i <= p - 1; ++i) {
        sum[i] = (sum[i - 1] + f[i]) % MOD;
    }
    unordered_set<int> s;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    n = unique(a + 1, a + n + 1) - (a + 1);
    if (p <= 30) {
        n = lower_bound(a + 1, a + n + 1, 1 << p) - a - 1;
    }
    for (int i = 1; i <= n; ++i) {
        bool flag = false;
        for (int j = a[i]; j; j = (j & 3) == 0 ? j >> 2 : (j & 1 ? j >> 1 : 0)) {
            if (s.find(j) != s.end()) {
                flag = true;
                break;
            }
        }
        if (flag) {
            continue;
        }
        s.insert(a[i]);
        ans = (ans + sum[p - int(log2(a[i])) - 1]) % MOD;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：AmamiyaYuuko (赞：2)

首先可以对 $a$ 做一些处理，如果在 $a$ 中有两个数 $a_i, a_j$ 满足 $a_i$ 可以在经过若干次操作后变为 $a_j$ 就把 $a_j$ 删除。

在二进制意义下，第二种操作相当于把 $x$ 左移一位再加 $1$，第三种操作相当于把 $x$ 左移两位，不难发现经过上述删除操作后的 $a$ 数组中任意两个数经过操作后得到的总是不同的数。

设 $f_i$ 为二进制下长度为 $i$ 的数的数量，有递推式 $f_i = f_{i - 1} + f_{i - 2}$，其中 $f_{i - 1}$ 对应第二种操作，$f_{i - 2}$ 对应第三种操作。最后的答案即为 $\sum f_i$。

代码：

```cpp
#include <bits/stdc++.h>

template <class T>
inline void read(T &x) {
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return ;
}

typedef unsigned long long uLL;
typedef long long LL;

const LL mod = 1e9 + 7;

std::vector<LL> v;
std::map<LL, bool> b;
LL a[200010], f[200010];
LL p, ans;
int n;

bool check(LL x) {
    if (!x)    return true;
    if (b.count(x))    return false;
    bool flag = true;
    if (x % 2)    flag &= check((x - 1) / 2);
    if (x % 4 == 0)    flag &= check(x / 4);
    return flag;
}

int main() {
    read(n), read(p);
    for (int i = 1; i <= n; ++i)    read(a[i]);
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        if (check(a[i])) {
            v.push_back(a[i]);
            b[a[i]] = true;
        }
    }
    for (auto i : v) {
        LL x = i;
        int cnt = 0;
        while (x) {
            ++cnt;
            x >>= 1LL;
        }
        ++f[cnt];
    }
    ans += f[1];
    ans %= mod;
    for (int i = 2; i <= p; ++i) {
        f[i] += f[i - 1] + f[i - 2];
        f[i] %= mod;
        ans += f[i];
        ans %= mod;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：zhangxiao666 (赞：1)

## 前言：
~~好久没写题解了，水一发！（洛谷博客更新后第一篇呢）~~

前置芝士：二进制，斐波那契数列。

## 题意：
给定 $n$ 个数在一个集合内，满足如果 $x$ 在集合中，$2x+1$ 与 $4x$ 也在集合内，且集合内所有数小于 $2^p$
求集合内数的数量。

## 思路:
（第一次计数题没写挂）！

看到 $p$ 很大，且是 $2$ 的幂次方形式，考虑二进制，于是发现一个很有用的性质：
+ $2x+1$ 就是在 $x$ 末尾添个 $1$
+ $4x$ 就是在 $x$ 末尾添个 $00$

所以问题就转变成：对于每个数，可以再末尾添 $1$ 或 $00$，求总位数不超过 $p$ 的方案数。

先只考虑 $1$ 个数，那么不需要每位是什么数，只要管个数就行了。

所以设 $f_i$ 表示添 $i$ 位的方案，则可以且仅可以通过 $2x+1$ 和 $4x$ 转移，即添 $1$ 位或 $2$ 位，所以显然有：$f_i=f_{i-1}+f_{i-2}$，发现这个式子就是斐波那契（虽然这个性质没什么用）。

总方案数就是把每位的方案数加起来即可。

但这个可不可以直接把 $n$ 个数单个算一遍累加呢，显然不行（行的话出题者还搞 $n$ 个干啥），因为会有重复的，如 $101_{(2)}$ 和 $101001_{(2)}$，我们发现，在 $101_{(2)}$ 后加上$00$ 和 $1$ 后，就与$101001_{(2)}$ 重复，答案变多了。

那怎么办呢？其实，发现 $x$ 与 $y$ 重复 $(x<y)$ 当且仅当 $x$ 为 $y$ 的前缀且 $y$ 可通过 $x$ 后填上任意个 $00$ 和任意个 $1$，由于 $00$ 和 $1$ 没有重复部分，所以可以在 $y$ 后面删，直到删不了为止。如果删的过程中没有重复的，说明 $y$ 不会与别的数的方案重复。否则在计算中 $y$ 会与别的数构成的方案重复。

注意我们在重复时要保留小的，因为小的数在扩展时会有更多方案而不与大数重复，如 $101_{(2)}$ 和 $101001_{(2)}$，虽然 $101_{(2)}\to101001_{(2)}$ 重复，但 $101_{(2)}\to10100_{(2)}$ 和 $101_{(2)}\to1011_{(2)}$ 却也要计算。

除了上面说的，前缀也一定要先标记小的，所以要先把原数列排序再做（因为这个调了15min！）

## 代码：
~~我知道都是看这个的qwq~~
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
int n, p, newn, ans;
map<int, bool> vis;
int a[N], newa[N], f[N];

int add(int x, int y)
{
	return x + y >= mod ? x + y - mod : x + y;
}

bool check(int x)
{
	while (x)
	{
		if(vis[x]) return 0;
		if (x & 1) x >>= 1;
		else if (x & 2) break;
		else x >>= 2;
	}
	return 1;
}

void init_Fib()
{
	f[1] = f[2] = 1;
	for (int i = 3; i <= p + 1; i++) f[i] = add(f[i - 1], f[i - 2]);
	for (int i = 1; i <= p + 1; i++) f[i] = add(f[i], f[i - 1]);
}

int bitnum(int x)
{
	int num = 0;
	for (int i = 0; i <= 31; i++)
	{
		if (x >> i) num = i + 1; 
	}	
	return num;
}

signed main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> p;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
	{
		if(check(a[i])) 
		{
			vis[a[i]] = 1;
			newa[++newn] = a[i];
		}
	}
	init_Fib();
	for (int i = 1; i <= newn; i++)
	{
		int num = bitnum(newa[i]);
		if (num < p + 1) ans = add(ans, f[p - num + 1]);  
	}
	cout << ans;
	return 0;
}
```

写题解不易，求过求点赞！！！！

---

## 作者：cryozwq (赞：1)

提供一种自己折腾自己的做法。过于折腾以至于赛时没有写对，下大分了。

首先 $2^p$ 很明显提示了要向二进制考虑，不难发现 $2x+1$ 就是在二进制末尾添加一个 $1$，$4y$ 是在末尾添加两个 $0$。问题就是问二进制位数小于 $p$ 有多少个数字。

这里都还挺正常，接下来就很神必了。

首先有个很蠢的 DP，设 $dp_i$ 表示集合中二进制位数为 $i$ 的数的数量。

不考虑加多的情况转移方程就是 $dp_i=dp_{i-1}+dp_{i-2}+cnt_i$，$cnt_i$ 表示 $a_i$ 中二进制位数为 $i$ 的数的数量。

但是这样会算重。 因为有一些 $a_i$ 可以通过末尾添加表示出其它 $a_i$。这个东西就会重。

怎么判断 $a_i$ 能否通过其它 $a_i$ 表示？首先一定是 $a_i$ 的一个前缀，然后剩下的部分还得能用 $00$ 和 $1$ 表示出来。不难想到预处理每个 $a_i$ 的每个后缀是否可以表示出来，这个很简单，然后 trie 树上查前缀。算出可以表示 $a_i$ 的数量 $d_i$ ，那么 $dp_i=dp_{i-1}+dp_{i-2}+cnt_i-d_i$ 即可。真的是这样吗？

又算少了！因为每个 $dp_i$ 都是去过重的，但是加的是没去重的 $d_i$（赛时栽在这里）。每个 $a_i$ 至多被多算两次（$dp_{i-1}$ 和 $dp_{i-2}$），所以只需要知道 $a_i>>1$ 和 $a_i>>2$ 是否能被表示出来（还是用前面的方法）以及后一位和后两位是否可以表示出来就可以算了，最终答案就是 $\sum\limits_{i=1}^{p-1} dp_i$ 。

[代码](https://codeforces.com/contest/1635/submission/147148555)见 CF 提交。


---

## 作者：LYJ_B_O_Creation (赞：0)

## 题意：
+ 给定 $n$ 个数，都在一个集合内
+ 这个集合内，满足如果 $x$ 在集合中，$2x+1$ 与 $4x$ 也在集合内
+ 且集合内每个数不超过 $2^p$
+ 求集合内数的数量。

## 思路:

考虑二进制，于是发现：
+ $2x+1$ 就是在 $x$ 末尾添 $1$
+ $4x$ 就是在 $x$ 末尾添 $00$

所以问题就转变成：对于每个数，可以再末尾添 $1$ 或 $00$，求总位数小于 $p$ 的方案数。

注：以下数字除特殊说明否则均指二进制下。

先只考虑 $1$ 个数，那么不需要每位是什么数，只要管个数就行了。

所以设 $f_i$ 表示添 $i$ 位的方案，则可以且仅可以通过 $2x+1$ 和 $4x$ 转移，即添 $1$ 位或 $2$ 位，所以显然有：$f_i=f_{i-1}+f_{i-2}$。

记该数位数为 $x$, 该数方案数就是 $\sum^{i<p-x}_{i=1}f_i$

但这个不可以直接把 $n$ 个数单个算一遍累加呢, 因为会有重复的，如 $1$ 和 $1100$，在 $1$ 后加上 $1$ 和 $00$ 后，就与$1100$ 重复。

发现 $x$ 与 $y$ 重复 $(x<y)$ 当且仅当 $x$ 为 $y$ 的前缀且 $y$ 可通过 $x$ 后填上任意个 $00$ 和任意个 $1$，由于 $00$ 和 $1$ 没有重复部分，所以可以在 $y$ 后面删，直到删不了为止。看删的过程中没有重复的即可。

## 代码：

~~代码有防抄袭~~

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
int n, p, newn, ans;
unordered_map<int, bool> vis;
int a[N], newa[N], f[N];

bool check(int x)
{
	while (x)
	{
		if(vis[x]) return 0;
		if (x & 1) x >>= 1;
		else if (!(x & 2))x >>= 2;
		else break;
	}
	return 1;
}

void Fib()
{
	f[1] = f[2] = 1;
	for (int i = 3; i <= p + 1; i++) f[i] = (f[i - 1] + f[i - 2]) % mod;
	for (int i = 1; i <= p + 1; i++) f[i] = (f[i] + f[i - 1]) % mod;
}

int count(int x)
{
	int num = 0;
	for (int i = 0; i <= 31; i++)
	{
		if (x >> i) num = i + 1; 
	}	
	return num;
}

int mian()
{
	cin >> n >> p;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
	{
		if(check(a[i])) 
		{
			vis[a[i]] = 1;
			newa[++newn] = a[i];
		}
	}
	Fib();
	for (int i = 1; i <= newn; i++)
	{
		int num = count(newa[i]);
		if (num < p + 1) ans = (ans + f[p - num + 1]) % mod;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

首先手玩一下样例，发现一个很有意思的事情，就是两个数字各自的贡献是不重复的（第二组样例除外），第二组虽然有重复的，但可以发现一个是另一个的子集，可以去重。

$p$ 太大，考虑二进制，发现两个操作一个是在二进制后面加一，另一个是加两个零，题目的限制也可以转化成位数小于 $p$ 的数的个数，假设我们还要补全 $x$ 位才能得到答案，那么发现 $f_x=f_{x-1}+f_{x-2}$，这不就是斐波那契数列吗。

最后一个问题，验重。发现一个事情，假如一个小的数字能转化成一个大的，那么这个大的就是无效的，所以从小到大判断一下，方法同上，不过是逆过程罢了。

```cpp
while(x>=1){
  if(mp.count(x))flag=0;
  if(x&1) x>>=1;
  else if(x%4==0) x>>=2;
  else break;
}
```

可以用一个 ``map`` 辅助判断。

---

## 作者：Jiyuu_no_Tsubasa (赞：0)

因为对于集合中的数的要求是严格小于 $2^p$，我们可以想到二进制。

那么对集合中数的要求就转化为了位数小于等于 $p$。

接下来我们观察两种操作，分别是 乘 $2$ 加 $1$ 与 乘 $4$，

那么可以分别转化为左移一位、结尾补一与左移两位；

也就是说分别能让位数 $+1$ 与 $+2$。

可以证明：对于一个初始的数 $x$，有进行若干次操作后所得到的数不重复。

因此我们可以直接用 dp 计算位数加 $x$ 时的方案数，

转移方程为 $f_x\gets f_{x-1}+f_{x-2}$，然后我们用前缀和处理就可以了。

接下来要解决的问题是：

数组中可能存在 $x$ 与 $y$ 满足 $y$ 可以由 $x$ 进行若干次操作后得到。

解决这个问题的方法是把数组从小到大排序，

对于每个数 $x$，进行反向操作直到不满足限制为止，

并查询前面的数中有没有可以通过反向操作得到的。

如果有的话，那么这个数的所有方案就已经被计算过了。

[代码](https://codeforces.com/contest/1635/submission/147073999)。

---

## 作者：清烛 (赞：0)

题意：给定一个序列 $a_{1\cdots n}$，令集合 $S$ 如下构造：

- $\forall i$，$a_i\in S$。
- $\forall x\in S$，$2x +1\in S$。
- $\forall x\in S$，$4x\in S$。

问集合 $S$ 中严格小于 $2^p$ 的元素个数，答案对 $10^9+7$ 取模，$n,p\le 2\times 10^5$。

发现 $p$ 很大，且 $2x + 1$ 和 $4x$ 这样的操作让人联想到位运算。所以先在二进制下考虑这个问题的 $n = 1$ 版本。

发现，每次做插入 $2x+1$ 和插入 $4x$ 这样构成了一个决策树，得到的答案绝对不会相交。而 $2x+1$ 相当于将 $x$ 左移一位再将最后一位设成 $1$，$4x$ 相当于将 $x$ 左移两位。所以我们实际上就是将 $x$ 往左移一定的位数，保证最高位 $<p$ 即可。

统计一下这样的方案数：不难发现设 $f_i$ 为左移 $i$ 位能得到的数字个数，有
$$
\begin{cases}
f_1 = 1\\
f_2 = 2\\
f_i = f_{i-1} + f_{i-2} + 1&i\ge 3
\end{cases}
$$
于是 $n=1$ 的情况就考虑完了。对于原来那种“从数集”扩展的模式，最麻烦的就是 $a_i$ 能变换到 $a_j$，这样子方案数就会算重。所以考虑去重。发现从决策树的节点往根跳的过程很容易（因为最后一步是确定的），所以对于每个 $a_i$，都这样往回跳跳，如果跳到了某个 $a_j$，就直接不用考虑 $a_i$ 即可。

于是本题得到了解决。

```cpp
const int maxn = 2e5 + 5;
int n, p, a[maxn];
modint f[maxn];
std::set<int> S;

int main() {
    read(n, p);
    f[p] = 1;
    DEC(i, p - 1, 1) f[i] = f[i + 1] + f[i + 2] + 1;
    FOR(i, 1, n) read(a[i]), S.insert(a[i]);
    modint ans = 0;
    DEC(i, n, 1) {
        bool flg = 1;
        int x = a[i];
        while (x) {
            if (x & 1) x >>= 1;
            else if (x % 4) break;
            else x >>= 2;
            if (S.count(x)) {
                flg = 0;
                break;
            }
        }
        if (flg) {
            int highbit = 0;
            DEC(j, 30, 0) if ((1 << j) & a[i]) {
                highbit = j;
                break;
            }
            ans += f[highbit + 1];
        }
    }
    print(ans);
    return output(), 0;
}
```

---

