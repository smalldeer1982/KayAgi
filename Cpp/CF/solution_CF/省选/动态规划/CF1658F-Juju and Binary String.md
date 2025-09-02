# Juju and Binary String

## 题目描述

The cuteness of a binary string is the number of $ \texttt{1} $ s divided by the length of the string. For example, the cuteness of $ \texttt{01101} $ is $ \frac{3}{5} $ .

Juju has a binary string $ s $ of length $ n $ . She wants to choose some non-intersecting subsegments of $ s $ such that their concatenation has length $ m $ and it has the same cuteness as the string $ s $ .

More specifically, she wants to find two arrays $ l $ and $ r $ of equal length $ k $ such that $ 1 \leq l_1 \leq r_1 < l_2 \leq r_2 < \ldots < l_k \leq r_k \leq n $ , and also:

- $ \sum\limits_{i=1}^k (r_i - l_i + 1) = m $ ;
- The cuteness of $ s[l_1,r_1]+s[l_2,r_2]+\ldots+s[l_k,r_k] $ is equal to the cuteness of $ s $ , where $ s[x, y] $ denotes the subsegment $ s_x s_{x+1} \ldots s_y $ , and $ + $ denotes string concatenation.

Juju does not like splitting the string into many parts, so she also wants to minimize the value of $ k $ . Find the minimum value of $ k $ such that there exist $ l $ and $ r $ that satisfy the constraints above or determine that it is impossible to find such $ l $ and $ r $ for any $ k $ .

## 说明/提示

In the first example, the cuteness of $ \texttt{0011} $ is the same as the cuteness of $ \texttt{01} $ .

In the second example, the cuteness of $ \texttt{11000011} $ is $ \frac{1}{2} $ and there is no subsegment of size $ 6 $ with the same cuteness. So we must use $ 2 $ disjoint subsegments $ \texttt{10} $ and $ \texttt{0011} $ .

In the third example, there are $ 8 $ ways to split the string such that $ \sum\limits_{i=1}^k (r_i - l_i + 1) = 3 $ but none of them has the same cuteness as $ \texttt{0101} $ .

In the last example, we don't have to split the string.

## 样例 #1

### 输入

```
4
4 2
0011
8 6
11000011
4 3
0101
5 5
11111```

### 输出

```
1
2 3
2
2 3
5 8
-1
1
1 5```

# 题解

## 作者：dead_X (赞：5)

## 思路
脑筋急转弯，为什么不是 div.2 C 呢。

记字符串有 $A$ 个 $\texttt{0}$ 和 $B$ 个 $\texttt{1}$，那么将一个 $\texttt{0}$ 的价值记为 $-B$，一个 $\texttt{1}$ 的价值为 $A$，显然价值和为 $0$ 的子串的可爱度和整个串的可爱度就是一样的。

抛出一个重磅结论：我们把最后一个字符和第一个字符连起来，形成一个环，环上一定存在一个长度为 $m$ 的区间的价值和为 $0$。

证明：如果每个区间价值和都 $>0$ 或每个区间价值和都 $<0$，整个串的价值和不可能为 $0$。如果存在一个 $>0$ 的区间和 $<0$ 的区间，因为相邻区间中字符 $\texttt{1}$ 的数量的变化量不超过 $1$，所以中间总存在一个价值和为 $0$ 的区间。

于是答案不超过 $2$，检查答案是否能为 $1$ 即可。

别忘了特判一个串里要有小数个 $\texttt{1}$ 的情况，这一定是不合法的。
## 代码
```cpp
signed main()
{
	for(int T=read();T--;)
	{
		int n=read(),m=read();
		scanf("%s",s+1);
		int c0=0;
		for(int i=1; i<=n; ++i) c0+=s[i]=='1';
		if((m*c0)%n)
		{
			puts("-1");
			continue;
		}
		for(int i=1; i<=n; ++i)
			a[i]=s[i]-48,a[n+i]=s[i]-48;
		int N=n<<1;
		for(int i=1; i<=N; ++i) if(a[i]) a[i]=n-c0; else a[i]=-c0;
		for(int i=1; i<=N; ++i) a[i]+=a[i-1];
		int l=0,r=0;
		for(int i=m; i<=N; ++i)
			if(a[i-m]==a[i])
			{
				l=i-m+1,r=i;
				break;
			}
		assert(l);
		if(r<=n) puts("1"),printf("%lld %lld\n",l,r);
		else puts("2"),printf("%lld %lld\n",1ll,r-n),printf("%lld %lld\n",l,n);
	}
	return 0;
}
```

---

## 作者：TernaryTree (赞：3)

这个题，骗我呢？？？

设 $cnt$ 为序列中 $1$ 的个数。存在解的必要条件是 $m\cdot cnt\bmod n=0$。

一个搞笑的结论：将原串首尾成环，必然存在长为 $m$ 的子串满足条件。考虑若所有子串都大于/小于整串密度，显然不可能。若存在一个子串大于，一个子串小于，由于一个子串删头添尾之后 $1$ 的个数增加量绝对值 $\le 1$，所以中间必然经过一个子串密度等于原串密度。

然后前缀和判一下答案是否为 $1$，否则为 $2$。做完了，真是搞搞又笑笑啊。

---

## 作者：Jorisy (赞：1)

神人题？？？？？

设 $s$ 中 $\tt 1$ 的个数为 $c_1$，则选取的子串的 $\tt 1$ 个数和为 $c=\dfrac{c_1m}n$，故 $n\nmid c_1m$ 则无解。

由于要最小化答案，我们先考虑一个串的情况。

但是显然地，我们相当有可能取不到答案，如样例二的 $\tt 11000011$，会发现我们取 $m=6$ 的子串的 $\tt 1$ 个数全是 $<c$ 的。

考虑循环移位地取，这样子串个数最多为二。

然后你会发现一个搞笑的事情，你在取的过程中一定是 $>c$ 和 $<c$ 的情况都有的，而对于这两种情况，他们中间必然是对 $\tt 1$ 的个数进行 $\pm1$ 的调整，所以一定会出现 $=c$ 的情况。

取若干子串，循环移位必有解，答案上界二。

最难绷。

---

## 作者：Zelotz (赞：0)

[CF1658F](https://www.luogu.com.cn/problem/CF1658F)

首先，令 $a,b$ 分别为 $0,1$ 的个数。那么 $1$ 的数量 $cnt=\dfrac{bm}{n}$。若 $bm$ 不为 $n$ 的倍数无解。

将数组首尾连接为一个环。

给出一个结论：在环上一定有一个长度为 $m$ 符合条件的区间，故答案上界为 $2$。

给出一个观察：设 $c_i =$ $s[i \dots i + m - 1]$ 中 $\texttt{1}$ 的数量（此处数组首位连接为环形数组）。

不难发现有 $|c_i-c_{i+1}| \leq 1$ ，并且对于所有 $y$ 满足 $\min(c_i) \leq y \leq \max(c_i)$ ，存在 $c_i = y$ 。

若所有子串都小于/大于整串密度显然是不可能的，根据上面的观察，中间必然经过一个字串密度等于原串密度。

```
#define int ll
const int N = 4e5 + 5;
int n, m, s[N];
void solve() {
    cin >> n >> m; int a = 0, b = 0;
    R(i, 1, n) {
        s[i] = s[i - 1];
        char c; cin >> c;
        if (c == '0') ++a;
        else ++b, s[i]++;
    }
    if (b * m % (a + b)) return puts("-1"), void();
    R(i, m, n) {
        int cnt = s[i] - s[i - m];
        if (b * m == cnt * n) {
            cout << 1 << '\n';
            cout << i - m + 1 << ' ' << i << '\n';
            return ;
        }
    }
    R(i, 1, m - 1) {
        int cnt = s[i] + s[n] - s[n - (m - i)];
        if (b * m == cnt * n) {
            cout << 2 << '\n';
            cout << 1 << ' ' << i << '\n';
            cout << n - (m - i) + 1 << ' ' << n << '\n';
            return ;
        }
    }
}
signed main() {
    int T; cin >> T;
    while (T--) solve();    
    return 0;
}
```

---

