# Hash Killer I

## 题目描述

这天天气不错，hzhwcmhf 神犇给 VFleaKing 出了一道题：

给你一个长度为 $n$ 的字符串 $s$，求有多少个不同的长度为 $l$ 的连续子串。

两个字符串被认为是不同的当且仅当某个位置上的字符不同。

VFleaKing 一看觉得这不是 Hash 的裸题么！于是果断写了哈希 + 排序。

而 hzhwcmhf 神犇心里自然知道，这题就是后缀数组的 height 中 $< l$ 的个数 +1，就是后缀自动机上代表的长度区间包含 $l$ 的结点个数，就是后缀树深度为 $l$ 的结点的数量。

但是 hzhwcmhf 神犇看了看 VFleaKing 的做法表示非常汗。于是想卡掉他。

VFleaKing 使用的是字典序哈希，其代码大致如下：

```cpp
u64 val = 0;
for (int i = 0; i < l; i++)
    val = val * base + s[i] - 'a';
```

u64 是无符号 int64，范围是 $[0, 2^{64})$。VFleaKing 让 val 自然溢出。

base 是一个常量，VFleaKing 会根据心情决定其值。

VFleaKing 还求出来了 $base^l$，即 base 的 $l$ 次方，这样就能方便地求出所有长度为 $l$ 的子串的哈希值。

然后 VFleaKing 给哈希值排序，去重，求出有多少个不同的哈希值，把这个数作为结果。

其算法的 C++ 代码如下:

```cpp
typedef unsigned long long u64;
const int MaxN = 100000;
inline int hash_handle(const char *s, const int &n, const int &l, const int &base)
{
    u64 hash_pow_l = 1;
    for (int i = 1; i <= l; i++)
        hash_pow_l *= base;
    int li_n = 0;
    static u64 li[MaxN];
    u64 val = 0;
    for (int i = 0; i < l; i++)
        val = val * base + s[i] - 'a';
    li[li_n++] = val;
    for (int i = l; i < n; i++)
    {
        val = val * base + s[i] - 'a';
        val -= (s[i - l] - 'a') * hash_pow_l;
        li[li_n++] = val;
    }
    sort(li, li + li_n);
    li_n = unique(li, li + li_n) - li;
    return li_n;
}
```

hzhwcmhf 当然知道怎么卡啦！但是他想考考你。

## 说明/提示

本题的评分为：在 SPJ 中预设了 10 个 base 用作测试，每让一个 base 出现哈希冲突记 10 分，满分为 100 分。

# 题解

## 作者：WorldMachine (赞：27)

> 我赌他没卡我的自然溢出。

对于 $b$ 为偶数的情况，只要串够长 $b^n$ 就变成 $0$ 了。

对于奇数的情况，Thue Morse 序列可以让它爆炸。

对于二进制串 $s$，定义 $\bar s$ 为按位翻转后的串。令 $0$ 阶 Thue Morse 序列 $t_0=\texttt{0}$，$t_n=t_{n-1}+\overline{t_{n-1}}$，有 $\text{hash}(t_n)=b^{2^{n-1}}\text{hash}(t_{n-1})+\text{hash}(\overline{t_{n-1}})$，$\text{hash}(\overline{t_n})=b^{2^{n-1}}\text{hash}(\overline{t_{n-1}})+\text{hash}(t_{n-1})$，记 $h_n=\text{hash}(t_n)-\text{hash}(\overline{t_n})$，有 $h_n=(b^{2^{n-1}}-1)h_{n-1}$。

由于 $b^{2^{n-1}}-1=(b-1)(b^{2^{n-2}}+1)(b^{2^{n-3}}+1)\dots(b+1)$，而 $b$ 是奇数，那么每一项都是偶数，故 $2^n|b^{2^{n-1}}-1$，那么 $2^{\frac{n(n+1)}{2}}|f_n$，对于 $n\ge11$，$\dfrac{n(n+1)}{2}>64$，自然溢出就爆炸了。

那么输出长度为 $2^{11}$ 的 Thue Morse 序列即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n = 1 << 11, l = n >> 1;
	printf("%d %d\n", n, l);
	for (int i = 0; i < n; i++) putchar('a' + (__builtin_popcount(i) & 1));
}
```

---

## 作者：_H17_ (赞：3)

## 题目分析

要卡自然溢出哈希。

考虑 $base$ 是偶数：当长度超过 $64$ 就可以让 $base^l\equiv 0\pmod{2^{64}}$。

考虑 $base$ 是奇数，使用 Thue Morse 序列，具体情况如下。

Thue Morse 序列是这样的，考虑有一个 $\texttt{01(ab)}$ 串。

定义 $¬(x)$ 表示对 $x$ 进行按位取反的串。

$s_0=\texttt{0}$，$s_i=s_{i-1}+¬(s_{i-1})$。

考虑做差 $\begin{aligned}
s_i-¬(s_i)&=(s_{i-1}\times base^{(2^{i-2})}+¬(s_{i-1}))+(¬(s_{i-1})\times base^{(2^{i-2})}+s_{i-1})\\
&=(s_{i-1}-¬(s_{i-1}))\times(base^{(2^{i-2})}-1)
\end{aligned}$。

进行换元：$f_i=s_i-¬(s_i),g_i=base^{(2^{i-2})}-1$。

即 $f_i=f_{i-1}\times g_i$，进而可推出 $f_i=f_1\times(\Pi_{j=2}^{i}g_j)$。

不难发现 $g$ 一定是偶数，但是这样太长了。

考虑优化 $g_i=base^{(2^{i-2})}-1=(base^{(2^{i-3})}-1)\times (base^{(2^{i-3})}+1)$，即 $g_i=g_{i-1}\times (base^{(2^{i-3})}+1)$。注意到后者也是偶数，经过推算，$i=12$ 即可。

部分内容参考 [OI Wiki](https://oiwiki.33dai.wiki/string/hash/#b-%E4%B8%BA%E5%A5%87%E6%95%B0)。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n=100000;
string s="",t;
int main(){
    s+=(char)(0);
    for(int i=1;i<=14;i++){
        t="";
        for(int i=0;i<s.size();i++)
            t+=(char)(s[i]^1);
        s=s+t;
    }
    s=s+(char)(1);
    for(int i=1;i<=64;i++)
        s=s+(char)(0);
    s=s+(char)(1);
    for(auto&c:s)
        if(c)
            c='b';
        else
            c='a';
    cout<<s.size()<<' '<<s.size()/2<<'\n'<<s;
    return 0;
}
```

---

## 作者：yuhong056 (赞：2)

# 题解：P12197 Hash Killer I
对于自然溢出 Hash，我们可以分情况讨论。
## 情况 1
$base$ 可以被 $2$ 整除。

很明显，当字符串足够长，Hash 的前面几项 Hash 值都会变为 $0$。

所以只需要在字符串后有足够多的 $\texttt a$ 即可。
## 情况 2
$base$ 不可以被 $2$ 整除。

在这种情况下，我们可以使用“Thue Morse 序列”。

定义 $!s$ 为 $s$ 二进制反转后得到的串。

我们可以构造一个字符串序列，满足 $s_i = s_{i - 1} + !s_{i - 1}$（ $+$ 代表字符串连接）。

取 $s_{12}$ 和 $!s_{12}$ 即可得到冲突。

至于为什么是 $12$ 可参考 [oiwiki](https://oiwiki.33dai.wiki/string/hash/#b-%E4%B8%BA%E5%A5%87%E6%95%B0)。

$L$ 则是 $s_{12}$ 的长度 $\div 2$。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n = 1 << 12;
	cout << n << ' ' << n / 2 << '\n';
	for (int i = 0; i < n; i++) {
		cout << char('a' + (__builtin_popcount(i) & 1)); // 构造 Thue Morse 序列
	}
	return 0;
}
```

---

