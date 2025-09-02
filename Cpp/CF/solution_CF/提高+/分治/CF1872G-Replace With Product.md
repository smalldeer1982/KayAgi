# Replace With Product

## 题目描述

Given an array $ a $ of $ n $ positive integers. You need to perform the following operation exactly once:

- Choose $ 2 $ integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) and replace the subarray $ a[l \ldots r] $ with the single element: the product of all elements in the subarray $ (a_l \cdot \ldots \cdot a_r) $ .

For example, if an operation with parameters $ l = 2, r = 4 $ is applied to the array $ [5, 4, 3, 2, 1] $ , the array will turn into $ [5, 24, 1] $ .

Your task is to maximize the sum of the array after applying this operation. Find the optimal subarray to apply this operation.

## 说明/提示

In the first test case, after applying the operation with parameters $ l = 2, r = 4 $ , the array $ [1, 3, 1, 3] $ turns into $ [1, 9] $ , with a sum equal to $ 10 $ . It is easy to see that by replacing any other segment with a product, the sum will be less than $ 10 $ .

In the second test case, after applying the operation with parameters $ l = 3, r = 4 $ , the array $ [1, 1, 2, 3] $ turns into $ [1, 1, 6] $ , with a sum equal to $ 8 $ . It is easy to see that by replacing any other segment with a product, the sum will be less than $ 8 $ .

In the third test case, it will be optimal to choose any operation with $ l = r $ , then the sum of the array will remain $ 5 $ , and when applying any other operation, the sum of the array will decrease.

## 样例 #1

### 输入

```
9
4
1 3 1 3
4
1 1 2 3
5
1 1 1 1 1
5
10 1 10 1 10
1
1
2
2 2
3
2 1 2
4
2 1 1 3
6
2 1 2 1 1 3```

### 输出

```
2 4
3 4
1 1
1 5
1 1
1 2
2 2
4 4
1 6```

# 题解

## 作者：Zelotz (赞：6)

刚看到这道题的时候就第一感觉应该是乘积比加和更优。

发现如果序列中所有数的乘积比 $2\times10^{14}$ 更大，在区间左右端点不为 $1$ 时，全乘起来一定更优。

若左右端点为 $1$，则找到两端的第一个非 $1$ 位置即为答案。

否则，发现 $2^{49}>2\times10^{14}$，则区间内非 $1$ 的位置一定小于 $50$ 个，只需枚举区间左右端点取最大值即可，实现时注意不要爆 `long long` 以及全是 $1$ 的情况。

本题思想主要在于排除掉乘积比 $2\times10^{14}$ 更大的情况后暴力的时间复杂度得到了保障。

```
#define int ll
const int N = 2e5 + 5, MAX = 2e14;
int a[N], n, sum[N], mul[N];
vector <int> v;
void solve()
{
    cin >> n; rer(i, 1, n, a);
    int now = 1;
    R(i, 1, n)
    {
        if (now > MAX / a[i]) 
        {
            int l = 1, r = n;
            while (a[l] == 1) ++l;
            while (a[r] == 1) --r;
            cout << l << ' ' << r << '\n';
            return ;
        }
        now *= a[i];
    }
    mul[0] = 1;
    v.clear();
    R(i, 1, n) 
    {
        mul[i] = mul[i - 1] * a[i], sum[i] = sum[i - 1] + a[i];
        if (a[i] != 1) v.pb(i);
    }
    int l = 1, r = 1, ans = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = i; j < v.size(); ++j)
        {
            // cout << v[i] << ' ' << v[j] << endl;
            int tmp = sum[n] - sum[v[j]] + sum[v[i] - 1];
            tmp += mul[v[j]] / mul[v[i] - 1];
            // cout << tmp << endl;
            if (tmp > ans) 
            {
                ans = tmp;
                l = v[i], r = v[j];
            }
        }
    }
    cout << l << ' ' << r << '\n';
}
signed main() 
{
    cout.tie(0);
    int T = 1; 
    read(T);  
    while (T--) solve();
    return 0;
}
```



---

## 作者：Zwb0106 (赞：6)

[**原题链接**](https://codeforces.com/contest/1872/problem/G)

------------

场上过了 F 之后的 48min 一直坐牢，然后熄灯后躺在床上想了一会就会了，急了。

------------
## 思路

把一段和替换为乘积，对于已确定的区间 $[l,r]$，如果 $a_{l-1}=a_{r+1}=1$，继续扩大这个区间才有可能不优。

考虑把整个序列划分为若干个块，每块内是极长的 $1$ 或者大于 $1$ 的数，为便于叙述，前者我们称为白块，后者我们称为黑块。这里我们略去整个序列均为 $1$ 的情况，那么序列一定有黑白块交替构成，并且能够发现我们的答案区间一定是某两个黑块（可能为同一个）以及之间的块组成的，这是因为边上的白块不选一定更优，边上的黑块内的数全选一定会更优。

然而，我们其实不能确定到底舍弃哪些黑块，例如 $\{2,1,1,1,2\}$，将整个序列乘起来会更劣。

现在考虑另外一个性质，即区间的乘积充分大的情况（大于 $10^{15}$），答案一定是原序列去掉两侧的白块。这是由于，单个黑块的乘积一定不小于 $2$，若序列足够大，我们舍弃一个黑块造成的乘积的减小至少是序列乘积的一半，而整个序列的和最大只有 $2 \times 10^{14}$，因此这样一定不优。所以我们把这种情况判掉。（这里的界限 $10^{15}$ 仅是粗略估计，事实上可以更小）

现在序列的乘积应当不超过 $10^{15}$ 了，又因为单个黑块的乘积最少是 $2$，那么序列中的黑块总数不超过 $\lfloor \log_2{10^{15}} \rfloor = 49$，预处理一下序列的前缀和以及前缀积，直接暴力判断选哪些黑块即可。

时间复杂度 $O(n + \log^2 V)$。

------------
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define gc getchar
#define pc putchar
#define fs first
#define sc second
using namespace std;

ll read()
{
	ll x=0,f=1;
	char ch=gc();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc();
	}
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=gc();
	return x*f;
}
void print(ll x)
{
	if(x<0)pc('-'),x=-x;
	if(x>9)print(x/10);
	pc(x%10+48);
}

const int N=2e5+5;
const ll INF=1e15;
int T,n;
ll a[N],s[N],x[N];
struct block
{
	int l,r,op;
}b[N];

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	T=read();
	while(T--)
	{
		n=read();
		__int128 flg=1;
		x[0]=1;
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			s[i]=s[i-1]+a[i],x[i]=x[i-1]*a[i];
			flg*=a[i];
			if(flg>INF)flg=0;
		}
		
		if(!flg)
		{
			int l=1,r=n;
			while(a[l]==1)l++;
			while(a[r]==1)r--;
			print(l),pc(' '),print(r),pc('\n');
			continue;
		}
		
		int tot=0,l=1,r=1,op=(a[1]==1);
		while(l<=n)
		{
			while(r<n&&op==(a[r+1]==1))r++;
			b[++tot]={l,r,op};
			op^=1,l=r+1,r=l;
		}
		
		l=1,r=tot;
		if(b[1].op)l++;
		if(b[tot].op)r--;
		
		if(l>r)
		{
			print(1),pc(' '),print(1),pc('\n');
			continue;
		}
		
		ll mx=s[n],ml=1,mr=1;
		for(int i=l;i<=r;i+=2)
			for(int j=i;j<=r;j+=2)
			{
				int L=b[i].l,R=b[j].r;
				if((s[n]-s[R]+s[L-1])+x[R]/x[L-1]>mx)
				{
					mx=(s[n]-s[R]+s[L-1])+x[R]/x[L-1];
					ml=L,mr=R;
				}
			}
		
		print(ml),pc(' '),print(mr),pc('\n');
	}
	
	return 0;
}
```

---

## 作者：loser_seele (赞：4)

目前的所有题解都没有提到这个上限是怎么来的，补充一点证明。

首先给出结论：区间积大于 $ 2n $ 时选择整个区间作为答案一定不会更劣。

证明：考虑最差情况，肯定是由中间若干个 $ 1 $ 和两头的两个数构成的，不妨设区间长度为 $ n $，两端的数字为 $ x,y $。

则合并变劣的条件为 $ x+y+(n-2) \geq xy $，需要证明 $ xy \leq 2n $，这样逆否命题：$ xy>2n $ 时合并一定不劣。

则有 $ y \leq \frac{x-n-2}{x-1},xy \leq \frac{x^2+xn-2x}{x-1}=n+x-1+\frac{n-1}{x-1} $。

发现后面的东西是对勾函数，最大值在两端，将 $ x=2,n $ 代入解得 $ xy \leq 2n $，于是得证。

所以当区间积大于 $ 2n $ 时合并整个区间一定不会更劣，然后同其他题解的思路即可，变成可以暴力解决的问题。

代码：

https://codeforces.com/problemset/submission/1872/225306947

---

## 作者：Super_Cube (赞：2)

# Solution

先判掉全 $1$ 或全不为 $1$ 的情况。

设从左往右第一个非 $1$ 的位置为 $l$，从右往左第一个非 $1$ 的位置为 $r$。如果 $l\sim r$ 的乘积足够大就直接选择它们为答案，否则 $l\sim r$ 中只会有 $\log$ 个非 $1$ 位置，答案的端点只有可能在这些位置取到，暴力判断即可。

时间复杂度：$O(n+\log^2 n)$。

---

## 作者：LCat90 (赞：2)

类似于 ABC315 F。

乘法极易产生溢出，那么问题一定可以排除掉大部分。

如果序列中所有数的乘积比这个区间的理论最大和更大，则可以直接选取整个序列。特殊情况是除掉首尾的 $1$。

否则我们就在区间中暴力选取左右端点，前提是不为 $1$。由于所有数的乘积小于理论最大和，那么大于 $1$ 的数的数量一定小于 $M=50$，因为 $2^{50}\ge 2\times 10^{14}$。复杂度上限是 $O(M^2)$，稳过。

判断乘积是否大于一个值的时候，为了防止越界，可以将一个乘数移到另一边改为除法。（NOI 春测遗留技巧）

回顾 ABC315 F，此题中我们通过 $2^x$ 的增量大发现 $x$ 的上界极小，于是从此出发优化了 DP 转移。

总结起来，从上界的局限性出发，这也不失为一种优化算法的新方法。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 2e14 + 5, N = 2e5 + 5;
int t, n, a[N], pre[N], s[N];
signed main() {
	cin >> t;
	while(t--) {
		int sum = 1;
		cin >> n; int ansl = 1, ansr = 1;
		for(int i = 1;i <= n; ++i) cin >> a[i];
		int lst = 0;
		for(int i = 1;i <= n; ++i) {
			if(sum >= M / a[i]) break ;
			sum *= a[i]; lst = i;
		}
		if(lst != n) {
			ansl = 1, ansr = n;
			while(ansl < n and a[ansl] == 1) ansl ++;
			while(ansr > 1 and a[ansr] == 1) ansr --;
			cout << ansl << " " << ansr << "\n";
		}
		else {
			pre[0] = 1; int maxn = 0;
			for(int i = 1;i <= n; ++i) pre[i] = pre[i - 1] * a[i], s[i] = s[i - 1] + a[i];
			for(int l = 1;l <= n; ++l)
				if(a[l] != 1) 
					for(int r = l;r <= n; ++r) {
						int tot = s[n] - (s[r] - s[l - 1]) + pre[r] / pre[l - 1];
						if(tot > maxn) maxn = tot, ansl = l, ansr = r;
					}
			cout << ansl << " " << ansr << "\n";
		}
	}
	return 0;
}
/*
1
5
1 1 1 1 1
*/
```

---

## 作者：sunkuangzheng (赞：2)

> 选自 [CF1872 题解集](https://www.luogu.com.cn/blog/skz/cf1872-solution)。

$\textbf{G \;Replace With Product}$

**【简要题意】**

有一个长度为 $n$ 的序列 $a$，你可以任选一段子区间，将 $[l,r]$ 中的所有元素替换为 $\prod\limits_{i=l}^ra_i$，问操作一次后数组的和的最大值。不需要求值，只输出方案。

$1 \le n \le 2 \times 10^5,1 \le a_i \le 10^9$。

**【题解】**

晚上过 F 后看这题几眼没想出来就睡了，今天一起来就会了 :)

首先如果序列里没有 $1$，那么全乘起来肯定最优。我们找到第一个非 $1$ 位置和最后一个非 $1$ 位置记为 $l,r$，如果中间那段的乘积大于 $2 \times 10^{15}$，显然直接输出 $l,r$ 是最优的，因为就算全是 $10^9$ 和最多也就 $2 \times 10^{15}$。

然后如果乘起来没有超过那个值，说明非 $1$ 元素数量肯定不超过 $\log_2 2 \times 10^{15}$ 个。又因为区间包含多余的 $1$ 肯定不优，所以答案一定是这些点两两组合构成的区间。暴力枚举即可。时间复杂度 $\mathcal O(n+\log^2 V)$。

[代码](https://codeforces.com/contest/1872/submission/222378151)。

upd：上面的代码被 hack 了，事实上只要乘积 $\ge 2 \times 10^6$ 即可退出。如果一定要使用 $2 \times 10^{15}$，记得开 __int128。


---

## 作者：ran_qwq (赞：1)

转化题意，求一个区间 $[l,r]$ 使得 $\prod\limits_{i=l}^ra_i-\sum\limits_{i=l}^ra_i$ 最大。即 $1$ 对答案产生 $-1$ 的贡献，其他数产生非负贡献。

设一个非 $1$ 连续段是极大的，且不包含 $1$ 的子段。则如果 $l$ 在某个连续段内，它一定在这个连续段的最左侧；如果 $r$ 在某个连续段内，它一定在这个连续段的最右侧。

容易发现如果 $\prod\limits_{i=l}^ra_i>2n$，可以无视所有 $1$ 的负贡献。此时将所有非 $1$ 数全部取完，令 $l$ 为第一个非 $1$ 数位置，$r$ 为最后一个非 $1$ 数位置。

此时特判全 $1$ 情况，随便输出一个 $l=r$ 的区间。

当 $\prod\limits_{i=l}^ra_i\le2n$，注意到每个非 $1$ 数至少对乘积产生乘 $2$ 的贡献，所以非 $1$ 数最多只有 $\log 2n$ 个，非 $1$ 连续段就更少。枚举每个非 $1$ 连续段作为左、右端点，暴力算即可。

---
有根号分治，我愿称这个 trick 为“log 分治”。

不太懂题解区为什么都将一个很大的数作为乘积最值？真不怕爆 long long？

---

## 作者：mango2011 (赞：1)

首先，我们的第一感觉一定是“哇，乘起来好大呀！”。

呃，确实如此。

有了上面的想法，我们就可以通过“乘”的特点，观察几个性质：

性质 $1$：

如果选中的区间的左端点或者右端点是 $1$，那么一定不是最优的。

证明：

由对称性，不妨设左端点是 $1$，那么可以假设这一段区间内的数是 $1,p_2,p_3,p_4,\dots,p_k$，由于这一段内乘起来和其他的部分不影响，而 $1\times\Pi_{i=2}^{k} p_i<\Pi_{i=2}^{k} p_i+1$。

性质 $2$：

如果数列中所有数的乘积不小于所有数的和，那么把所有数都先选中，然后按照性质 $1$ 删除左右是 $1$ 的部分。

性质 $2$ 是解决这一道题目的关键，证明非常简单，这里就略去了。

有了上面的性质，我们记 $M=\Pi_{i=1}^{n} a_i,S=\sum_{i=1}^{n} a_i$。

1) 若 $M\ge S$，则输出最左边大于 $1$ 的数和最右边大于 $1$ 的数的位置。

2) 若 $M<S$，则考虑记录所有大于 $1$ 的数的位置，由于这样的数不小于 $2$，故记录的位置总数不超过 $\lceil\log{M}\rceil$。又由性质 $1$，我们使用双重循环，枚举记录的位置作为左右端点，使用 long long 范围的数记录答案以及位置即可。

综上，我们就解决了这一道题目。

实现的时候，主要是要注意初始化以及数据类型，别的没了。

代码就不贴了，想要代码的，可以私信我哟！

---

## 作者：灵乌路空 (赞：1)

[https://codeforces.com/contest/1872/problem/G](https://codeforces.com/contest/1872/problem/G)

记非 1 位置坐标依次为：$p_1, p_2, \dots, p_k$，显然答案只能是非 1 的位置，另外显然当非 1 位置较多时，答案为 $[p_1, p_k]$ 肯定是最优的。

于是考虑定一个非 1 元素乘积的上界，当乘积大于该上界时就直接输出 $[p_1, p_k]$，否则 $k$ 较小，直接暴力枚举答案区间即可。

上界定为 $2^{60}$ 就差不多了，此时 $k\le 60$，总复杂度 $O(\left\lfloor\frac{n}{60}\right\rfloor\times 60^2) = O(60\times n)$。

为了方便写了 py，其实用 int128 也行。

```py
T = int(input())
lim = 2 ** 60

while T > 0:
  T = T - 1
  n = int(input())
  a = [0]
  p = [0]
  sum1 = [0]
  sum = [1]
  prod = 1

  s = input().split(' ')
  for i in range(1, n + 1):
    a.append(int(s[i - 1]))
    sum1.append(sum1[i - 1] + a[i])
    if a[i] > 1:
      p.append(i)
      if prod < lim:
        prod = prod * a[i]

  if prod >= lim:
    print(p[1], p[-1])
    continue
  
  for i in range(1, len(p)):
    sum.append(a[p[i]])
    sum[i] = sum[i] * sum[i - 1]

  delta = 0
  ansl, ansr = (1, 1)
  for i in range(1, len(p)):
    for j in range(i + 1, len(p)):
      l, r = p[i], p[j]
      if ((sum[j] / sum[i - 1] - sum1[r] + sum1[l - 1]) > delta):
        ansl, ansr = (l, r)
        delta = sum[j] / sum[i - 1] - sum1[r] + sum1[l - 1]
  print(ansl, ansr)
'''
1
4
2 1 1 3
'''
```

---

## 作者：luogu_gza (赞：1)

中间的 $1$ 会减少我们的贡献，所以我们需要判断一个区间是否值的乘。

大眼观察可以发现一个最好的区间首尾一定 $\geq 1$。

考虑乘上一个 $\geq 1$ 的数最多乘 $50$ 次左右就可以判定这是值得乘的。

然后预处理出每一个 $\geq 1$ 的数的位置，每个位置向后枚举 $50$ 位计算答案即可。

---

## 作者：wwxxbb (赞：0)

### 题意

> 给定一个长度为 $n$ 的数组 $a$，现在可以：
>
> 选择两个正整数 $l,r(l\le r)$，将 $a[l\dots r]$ 的所有数删除，并替换为 $\prod\limits_{i=l}^ra_i$。
>
> 最大化总和，输出 $l$ 和 $r$。

### 思路

乘法绝大多数情况下都比加法优，除非有 $1$ 在，否则尽量选择乘法。

如果 $[l,r]$ 是可以的，$a_{l - 1} \neq 1 \wedge a_{r + 1} \neq 1$，那么这个区间可以继续扩展，否则这个区间是最优的。

但如果所有数的乘积很大，那整个区间和都不会超过它，则将整个序列乘起来才是最优的。这时我们要找到从起点开始第一个不是 $1$ 的下标和从终点开始第一个不是 $1$ 的下标，即为 $l,r$。

这个数我一开始想的是 $2 \times 10 ^ {14}$，因为有 $2 \times 10 ^ 5$ 个数，每个数最大为 $10 ^ 9$，乘起来就是。

这样每个数最小是 $2$ 才能对答案产生贡献，所以最多有 $\lceil \log_2 (2\times 10 ^{14}) \rceil = 49$ 个（设为 $m$)，枚举两端点维护前缀和和前缀积即可 $\mathcal{O}(m^2)$ 判断。

所以我们的思路是：

- 如果乘积大于这个数，则找到两端第一个非 $1$ 的下标。
- 否则，维护好两个前缀数组，枚举两个不是 $1$ 的端点，判断最大值并更新答案。

总复杂度 $\mathcal{O}(n + m ^ 2)$，取决于上界大小。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;
const int N = 200010;
const ll INF = 2e14;

int t, n, a[N];
ll s[N];
lll mul[N] = {1};

void solve() {
    cin >> n;
    int l = 1, r = n; bool flag = 0;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        mul[i] = mul[i - 1] * a[i];
        if (mul[i] > INF) flag = 1;
    }
    if (flag) {
        while (l <= n && a[l] == 1) l ++;
        while (r >= 1 && a[r] == 1) r --;
        return cout << l << ' ' << r << '\n', void();
    }
    lll ans = 0; l = r = 1;
    for (int i = 1; i <= n; i ++) {
        if (a[i] == 1) continue;
        for (int j = i; j <= n; j ++) {
            lll t = s[n] - (s[j] - s[i - 1]) + mul[j] / mul[i - 1];
            if (t > ans) ans = t, l = i, r = j;
        }
    }
    cout << l << ' ' << r << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t --) solve();
    return 0;
}
```

### 感想

由于上界是 $2 \times 10 ^ {14}$ 如果再乘一个 $10 ^ 9$ 的数会爆 long long，所以要开 int128，然而我并不会用，CE 了好多发，用了 C++20 才过。所以我在想，这个上界能不能小一点呢？

看了官方题解才知道上界只需要 $2n$。下面借用一下神犇 @llqqhh 的启发来证明一下。

神犇说：

> 极限情况下两端非 $1$ 中间全 $1$，只要两端的数乘起来大于全部数的和就可以了。

我们设两端的数为 $x, y$，长度为 $n$。

那么要满足的情况就是 $xy \le x + y + n - 2$。

即区间积小于等于区间和时才更劣。

把 $x$ 当成主元，移项：
$$
\begin{aligned}
x &\le \frac{y + n - 2}{y - 1}\\
xy &\le \frac{(y + n - 2)y}{y - 1}\\
xy &\le \frac{(y - 1)(y - 1 + n) + n - 1}{y - 1}\\
xy &\le y - 1 + \frac{n - 1}{y - 1} + n
\end{aligned}
$$
发现右边是对勾函数，由于我们要的是最大值，所以取两端，即取 $y = 1$ 时得 $xy \le 2n$。

所以只需将原来那么大的上界换成那么小的上界了。

是不是很神奇？

---

## 作者：Hoks (赞：0)

## 前言
同学 duel 到的题，感觉挺有意思的，顺手写了下。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
乘法，感性理解，肯定会比加法大很多。

除了一个特殊情况，就是 $1$。

那么我们先考虑下什么时候，都乘起来肯定是更优的。

显然，如果加法可能的最大值都没有乘法大，无脑乘法即可。

而这个最大值也就是 $2\times10^5\times10^9=2\times10^{14}$。

把这个判掉了剩下就是考虑哪一段 $[l,r]$ 乘起来正贡献最大。

不难发现，因为 $\prod\limits_{i=1}^n a_i\le2\times10^{14}$，所以大于 $1$ 的 $a_i$ 一定不会很多。

具体的估算一下就会发现 $2^{48}>2\times10^{14}$，所以剩下来的大于 $1$ 的数不会超过 $48$ 个。

我们把连续的大于 $1$ 的数看做一段，那么这种段一定不会超过 $48$ 段，考虑暴力枚举 $i,j$，合并第 $i$ 段到第 $j$ 段，更新答案即可。

复杂度 $O(n+\log^2(nV))$。
## 代码

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
const int N=3e6+10,INF=2*1e14,mod=1e9+7;
int n,ans,al,ar,tot,a[N],s[N],p[N],xl[N],xr[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void ot()
{
    for(int i=1;i<=n;i++) if(a[i]!=1){print(i);break;}put(' ');
    for(int i=n;i>=1;i--) if(a[i]!=1){print(i);break;}put('\n');
}
inline void solve()
{
    n=read();tot=0;int f=0;for(int i=p[0]=1;i<=n;i++)
    {
        a[i]=read(),s[i]=s[i-1]+a[i],p[i]=p[i-1]*a[i];
        if(p[i]>INF) f=1;
    }if(f) return ot();int l=1;while(a[l]==1&&l<=n) l++;ans=s[n],al=1,ar=1;
    while(l<=n)
    {
        int r=l;while(a[r]!=1&&r<=n) r++;if(a[r]==1||r>n) r--;
        xl[++tot]=l,xr[tot]=r;l=r+1;while(a[l]==1&&l<=n) l++;
    }
    for(int i=1;i<=tot;i++)
        for(int j=i,r,res;j<=tot;j++)
        {
            l=xl[i],r=xr[j];res=s[n]-(s[r]-s[l-1])+p[r]/p[l-1];
            if(res>ans) ans=res,al=l,ar=r;
        }print(al),put(' '),print(ar),put('\n');
}
signed main()
{
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：zhu_wen (赞：0)

## G. Replace With Product

通过贪心，我们肯定是选择非 $1$ 的区间。

但一些情况可能分段：

- 对于乘积超过 $10^9$ 我们肯定选择这段区间，因为加和再怎么加，也不会超过这一段相乘。

- 对于乘积小于 $10^9$ 我们就直接暴力枚举每对位置即可，在这里我们需要用到前缀和，前缀积优化，否则时间复杂度过大，最后取得最大值的那段区间就是答案。 

如果 $l$ 没有被改变，那么就是无解，输出 $-1$。

### 代码

```cpp
void solve()
{
    int n,l=-1,r=-1;//表示答案区间
    ll s=1;
    vector<int> v;
    scanf("%d",&n);
    mul[0]=1;//初始化
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=1)
        {
            v.push_back(i);
            if(l==-1) l=i;//第一个非1数字
            r=i;//最后一个非1数字
        }
        sum[i]=sum[i-1]+a[i];
        mul[i]=mul[i-1]*a[i];
    }
    for(int i=1;i<=n;i++)
    {
        s*=a[i];
        if(s>=1e9)
        {
            printf("%d %d\n",l,r);
            return;
        }
    }
    ll mx=0;
    for(int i=0;i<v.size();i++)
    {
        for(int j=i;j<v.size();j++)
        {
            int x=v[i],y=v[j];
            if(sum[x-1]+mul[y]/mul[x-1]+sum[n]-sum[y]>mx)
            {
                mx=sum[x-1]+mul[y]/mul[x-1]+sum[n]-sum[y];
                l=x,r=y;
            }
        }
    }
    if(l==-1) l=1,r=1;
    printf("%d %d\n",l,r);
}
```

---

## 作者：huangrenheluogu (赞：0)

两个不是 $1$ 的数乘起来显然更加优秀。

原因是 $ab>a+b(a,b>1,a,b\in \mathbb{N})$。应该显然吧，因为 $ab-a-b+1=(a-1)(b-1)\ge1\Rightarrow ab-a-b\ge0$。

那么，我们就可以把序列划分为若干个连续的 $1$ 和若干个连续的数字。

我们可以猜想，如果总乘积比较大，那么为了乘一个大于 $1$ 的数，中间耗费多少个 $1$ 应该都没有关系。

比如乘上二就可以越过 $n$ 个 $1$，说明乘积大于等于 $n$ 的时候，取所有不是一的数乘起来是最优的，但是因为我们最后要乘上一个数（可能是 $2$，所以增加的其实是 $\dfrac{mul}{a_i}(a_i-1)\ge n$，我们需要 $mul\ge n+\dfrac{mul}{a_i}$），其中 $mul$ 是其他数字的乘积。

为了保险，我们可以当所有数的乘积大于 $n^2$ 的时候说明可以取尽量多的不是 $1$ 的数，找到最左边的一段 $1$ 和最右边的一段 $1$ 即可。

> 在这里证明一下，$mul\ge n^2$ 的时候，$mul(1-\dfrac{1}{a_i})\ge mul\times\dfrac{1}{2}\ge\dfrac{1}{2}n^2$，而 $\dfrac{n^2}{2}\ge n$ 在 $n\ge 2$ 的时候成立。$n=1$ 的时候反正改变不了就算了。

不然，我们可以分成 $\log_2n^2$ 级别数量组 $1$ 和非 $1$ 构成的串，这个数量记为 $tot$，显然 $n^2$ 不会爆 long long，那么这个数量不会超过 $63\times2=126$ 组（这是粗略的估计的）。

那么，可以直接枚举哪两组之间取 $\max$，初始为取 $1$ 个数（不改变）。

这里可以加一个 trick 减小常数，我们肯定不会以连续的 $1$ 开头，这样开头只有不超过 $63$ 个。

[code](https://codeforces.com/contest/1872/submission/239031920)

总结一下，主要就是发现这个组数不是很多。

注意，上面的代码使用洛谷 C++14 提交会 Compile Error，需要使用 C++17 提交。但是在我的 Linux 上可以编译。

---

## 作者：Daniel_yao (赞：0)

## Problem
给定一个长度为 $n$ 的数组 $a$，现在可以进行一次操作：
- 选择两个正整数 $l,r(l\le r)$，将 $a[l\dots r]$ 的所有数删除，并替换为 $\prod\limits_{i=l}^ra_i$；

最后的总贡献为所有数的加和，请选择 $l,r$，最大化总贡献。
## Solve
小 trick 题。

首先，前缀和后缀 $1$ 选入操作区间显然是不会优的，因为他对于乘法是没有贡献的，而对于加法有 $+1$ 的贡献。

发现一个性质：如果一些数的乘积很大，达到了某一个上限时，这些数的和一定比这些数的乘积要小。这个上限具体为多少我们并不知道，但是，只要它是一个很大的数字，那么上述事件发生的概率就会很大。考虑到 $1 \le a_i \le 10^9$，我们就将上限设为 $10^{18}$，这是一个接近于 $2^{60}$ 的数字。这也就意味着，当所有数的乘积小于 $10^{18}$ 时，所有大于 $2$ 的数字不会超过 $60$ 个。

对于所有乘积大于上限的数，直接摒弃前缀和后缀 $1$ 之后的区间即为答案，因为要尽可能的让乘积变大。

显然，操作区间的左右端点不会出现在数字 $1$ 上，因为出现在了数字 $1$ 上肯定会比出现在大于 $1$ 的数字上更劣。所以只要暴力枚举所有大于 $1$ 的数的位置，然后利用前缀和与前缀积快速统计贡献，最后取最大贡献所对应的区间即可。

时间复杂度 $O(TnK^2)$，其中 $K\le 60$。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007
#define inf 1e18

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 2e5 + 10;

int T, n, a[N], sum[N], ans, ansl, ansr, len, no1[N], pre[N];

void solve() {
  read(n);
  For(i,1,n) read(a[i]), sum[i] = sum[i-1] + a[i];
  int l, r, k; __int128 p = 1; len = 0, ans = 0, ansl = 1, ansr = 1;
  For(i,1,n) {
    p *= a[i];
    if(p > inf) break;
  }
  if(p > inf) {
    For(i,1,n) {
      l = i;
      if(a[i] != 1) {
        break;
      }
    }
    FOR(i,n,1) {
      r = i;
      if(a[i] != 1) {
        break;
      }
    }
    cout << l << ' ' << r << '\n'; 
    return ;
  }
  pre[0] = 1; 
  For(i,1,n) pre[i] = pre[i-1] * a[i];
  For(i,1,n) {
    if(a[i] != 1) no1[++len] = i;
  }
  For(i,1,len) {
    For(j,1,len) {
      if(no1[i] > no1[j]) continue;
      if(ans < sum[n] - (sum[no1[j]] - sum[no1[i]-1]) + (pre[no1[j]] / pre[no1[i]-1])) {
        ans = sum[n] - (sum[no1[j]] - sum[no1[i]-1]) + (pre[no1[j]] / pre[no1[i]-1]);
        ansl = no1[i], ansr = no1[j];
      }
    }
  }
  cout << ansl << ' ' << ansr << '\n';
}

signed main() {
  read(T);
  while(T--) { 
    solve();
  }
  return 0;
}
```

---

