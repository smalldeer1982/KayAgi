# 「MCOI-04」Dream and Strings

## 题目描述

Tommy 的加密系统用了如下的字符串哈希算法：

```cpp
int Hash(std::string s, int base, int mod) {
  int result = 0;
  for(int i=0; i<s.length(); i++)
    result = (1ll * result * base + s[i]) % mod;
  return result;
}
```

其中 $\texttt{base}$ 和 $\texttt{mod}$ 是给定参数，满足 $257\le\texttt{base}\le\texttt{mod}\le10^9+9$，并且 $\texttt{mod}$ 是一个质数。

现在 Dream 要破解 Tommy 的密文，先需要找到一个适合的哈希碰撞。给定 $\texttt{base}$，$\texttt{mod}$，和一个字符串 $S$，请找一个一样长度的字符串 $T$ 使得 $|S|=|T|$，$\texttt{hash(S)=hash(T)}$，但是 $S$ 和 $T$ 有至少一个位置不同。

如果有多个合法的 $T$，输出任意一个即可。

## 说明/提示

#### 数据规模与约定

如果 $S$ 是一个字符串，$|S|$ 是它的长度。 

对于前 $10\%$ 的数据，$\texttt{mod}=997$。  
对于前 $40\%$ 的数据，$|S|=2\times10^5$ 并且 $S$ 随机。  
对于 $100\%$ 的数据，$50\le|S|\le2\times10^5$，$257\le\texttt{base}<\texttt{mod}\le10^9+9$，$\texttt{mod}$ 是一个质数。

#### 说明

[Minecraft OI Round 4](https://www.luogu.com.cn/contest/33344) D          
idea & solution：w33z8kqrqk8zzzx33 check：MatKave

## 样例 #1

### 输入

```
257 997
aabdccbabdcdcadbcabcabaabdbbddbaabcadabcbcdacbbaac```

### 输出

```
lmzaeccihyailccmzzaxshssgbvjvhthllyofzudraatifnzxy```

# 题解

## 作者：yzy1 (赞：3)

~~我怎么感觉这个 D 比 A 简单？好吧原来 D 才是这场比赛签到题。~~

## 题目大意

给定正整数 $b,p$ 和字符串 $S$。构造一个字符集为 $[\tt a,z]$，长度为 $|S|$ 的字符串 $T$，满足 $S\ne T$ 且两个字符串对进行进制为 $b$、模数为 $p$ 的单哈希后得到的结果相等。

$50\le |S| \le 10^5$，$257 \le b \le p \le 10^9+9$ 且 $p$ 为质数。

## 大体解法

首先这题肯定 $|S|$ 越大越好做，所以只要考虑 $|S|=50$ 的情况。首先预处理出一个 $50$ 位全是 `a` 的字符串的 hash 值和 $b^k \bmod p$ 的结果。问题转化为你要构造一个长度为 $50$ 且每一位 $\in [0,25]$ 的整数数列，满足 $\sum_{i=0}^{49} a_ib^k = H$。

考虑构造一堆 $50$ 位的 $01$ 串 mask。mask 每一位为 $1$ 代表把这一位的字符串 ASCII $+1$，每生成一个跟现有的所有 mask 匹配一下，匹配的过程就是对于每一位 $i$，令 $T_i \gets a_i+b_i + \mathtt{'a'}$，生成一个字符集为 $[\tt a,c]$ 的字符串，匹配可以直接 $O(1)$ 查 `unordered_map`，看看能不能构造出题目给定的 hash。

由于随机 $N$ 个 mask 可以生成 $O(N^2)$ 个不同的 hash，所以这种随机化算法成功率相当高。

## 参考代码

```cpp
const int N = 2e5 + 9;
const ull MASK = (1ull << 50) - 1;
int b, mo, n, need, bpw[N];
char s[N];
unordered_map<ull, ull> mp;
mt19937_64 rnd;

void Out(ull x, ull y) {
  re (i, n - 50)
    cout << s[i];
  per (i, 49, 0)
    cout << char('a' + ((x >> i) & 1) + ((y >> i) & 1));
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> b >> mo >> (s + 1), n = strlen(s + 1);
  bpw[0] = 1;
  re (i, 55)
    bpw[i] = 1ll * bpw[i - 1] * b % mo;
  rep (i, n - 49, n)
    need += 1ll * bpw[n - i] * (s[i] - 'a') % mo, umod(need);
  while (1) {
    ull x = rnd() & MASK;
    int ha = 0;
    rep (i, 0, 49)
      ha += ((x >> i) & 1) * bpw[i], umod(ha);
    mp[ha] = x;
    if (mp.count((need - ha + mo) % mo)) Out(x, mp[(need - ha + mo) % mo]), exit(0);
  }
  return 0;
}
```

---

好像被 w33z hack 了？没关系，可以把代码中的字符 `a` 全都改成一个 $[\tt a,x]$ 范围内的随机字符，设这个字符为 $C$，则构造出来的字符串字符集为 $[C,C+3]$。

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

# D：【Dream and Strings】

### $m=997$ 部分分

当 $S$ 随机，$H(S)$ 函数可以看做一个随机在 $[0,m)$ 里面的数。

如果随机选取长度为 $|S|$ 的字符串，选出来的字符串是一个哈希碰撞可能性大概就是 $\frac{1}{m}$。

计算期望，得到需要的选取次数是 $m$。

时间复杂度是期望 $O(|S|*m)$；如果采用 dfs 那么可以达到期望 $O(m)$。

### 正解

首先，把 $|S|$ 长度降低到 $50$ 来让 $O(|S|*m)$ 降低到 $O(m)$。可以把 $S$ 的长度为 $|S|-50$ 后缀保持一样，直接固定前 $50$ 字符的哈希一样。

考虑以上的拓展：如何快速选出来一大堆随机字符串呢？来选出来 $O(n)$ 个字符串，不一定需要 $O(n)$ 的时间，因为存在更好的字符串表示方法。

例如如果造出来 $O(\sqrt n)$ 个前缀以及 $O(\sqrt n)$ 个后缀，会形成 $O(n)$ 个字符串，但是只需要 $O(\sqrt n)$ 的时间来构造和判断有没有构造一个哈希值。

具体方法：

 - 用任意方法构造 $O(\sqrt{m})$ 级别的长度为 $25$ 的前缀以及它们的哈希
 - 用任意方法构造 $O(\sqrt{m})$ 级别的长度为 $25$ 的后缀以及它们的哈希
 - 注意给定长度为 $25$ 的前缀的哈希与长度为 $25$ 的后缀的哈希，长度为 $50$ 的整体哈希等于 $(P\cdot b^{25}+S)\bmod m$
 - 有 $T$；想要 $P\cdot b^{25}+S\equiv T\pmod m$
 - 等价 $T-P\cdot b^{25}\equiv S\pmod m$
 - 对所有 $S$ 存一个 set 或者 unordered_set；这样可以直接 $O(1)$ 或者 $O(\log\sqrt n)$ 时间找到存在不存在一个 $S$ 来把前缀补成 $m$。

为了安全，std 固定生成 $2\times10^5$ 个前缀和后缀。

可以这样分析成功概率。我们将前缀和后缀抽象为均匀随机函数，整体哈希自然也是均匀随机函数。没有一个碰撞的概率是

$$(1-\frac{1}{m})^{Q^2}$$

其中 $Q$ 为产生前缀后缀数量。想要 

$$(1-\frac{1}{m})^{Q^2}=\varepsilon$$

则

$$Q=\sqrt{\frac{\log \varepsilon}{\log (m-1)-\log(m)}}$$

$Q=2\times10^5$ 接近于 $\varepsilon=4\times10^{-18}$，完全充足。

---

