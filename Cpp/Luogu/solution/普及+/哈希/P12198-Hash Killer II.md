# Hash Killer II

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
    val = (val * base + s[i] - 'a') % MOD;
```

u64 是无符号 int64，范围是 $[0, 2^{64})$。VFleaKing 让 val 自然溢出。

base 是一个常量，VFleaKing 会根据心情决定其值。

$\text{MOD}=10^9+7$

VFleaKing 还求出来了 $base^l \bmod \text{MOD}$，即 base 的 $l$ 次方除以 $\text{MOD}$ 的余数，这样就能方便地求出所有长度为 $l$ 的子串的哈希值。

然后 VFleaKing 给哈希值排序，去重，求出有多少个不同的哈希值，把这个数作为结果。

其算法的 C++ 代码如下:

```cpp
typedef unsigned long long u64;
const int MaxN = 100000;
inline int hash_handle(const char *s, const int &n, const int &l, const int &base)
{
    const int Mod = 1000000007;
    u64 hash_pow_l = 1;
    for (int i = 1; i <= l; i++)
        hash_pow_l = (hash_pow_l * base) % Mod;
    int li_n = 0;
    static int li[MaxN];
    u64 val = 0;
    for (int i = 0; i < l; i++)
        val = (val * base + s[i] - 'a') % Mod;
    li[li_n++] = val;
    for (int i = l; i < n; i++)
    {
        val = (val * base + s[i] - 'a') % Mod;
        val = (val + Mod - ((s[i - l] - 'a') * hash_pow_l) % Mod) % Mod;
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

## 作者：WorldMachine (赞：10)

> 我赌他没卡我的单模哈希。

看起来有点难搞，但根据 Pollard-Rho 的结论，即生日悖论，期望随机 $\mathcal O(\sqrt p)$ 个串就能有重复的哈希值，具体地说，是 $\sqrt{\dfrac{\pi p}{2}}$。那么随机输出就行了。

注意 $l$ 不能开得太小了，不然总方案数到不了 $\mathcal O(\sqrt p)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n = 1e5, l = 20;
	printf("%d %d\n", n, l), srand(time(0));
	for (int i = 1; i <= n; i++) putchar('a' + rand() % 26);
}
```

---

## 作者：dg114514 (赞：7)

> 如果一个房间里有 $23$ 个以上的人，那么至少有两个人的生日相同的概率要大于 $50\%$。——[生日悖论](https://baike.baidu.com/item/%E7%94%9F%E6%97%A5%E6%82%96%E8%AE%BA/2715290)

通过生日悖论可以得出，从 $n$ 个数随机取数，取到相同的数所需要的期望次数为 $O(\sqrt{n})$。而单模数哈希实际上就等价与从 $mod$ 个数随机取。所以只要让单模数哈希求 $\sqrt{mod}$ 次哈希就大概率会造成哈希冲突进而卡掉它。\
如果怕不够保险，可以适当让取哈希的次数变多。所以输出随机字符串即可过题。（注：$l$ 不能过大，否则可能会 WA，亲测）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	mt19937 rnd(114514);
	cout<<1e5<<" "<<1145<<"\n";
	for(int i=1;i<=1e5;i++)
		putchar(rnd()%26+'a'); 
} 
```

### 后记

终于知道为什么周泰大多数时候都只能触发四次不屈了。

---

## 作者：yuhong056 (赞：3)

# 题解：P12198 Hash Killer II
首先，单 Hash 有一个很重要的特性：

> 对于模数为 $K$ 的单 Hash，期望 $\sqrt K$ 次即可出现冲突。

证明可见 [oiwiki](https://oiwiki.33dai.wiki/string/hash/#hash-%E7%9A%84%E9%94%99%E8%AF%AF%E7%8E%87%E5%88%86%E6%9E%90)。

而此题模数为 $10^9 + 7$，期望 $\sqrt {10^9 + 7} = 31622$ 次即可出现冲突，我们只需要比他大一点即可出现冲突。我的代码中使用的是 $10^5$。

至于 $L$，多少都可以，因为和冲突无关，我的代码中使用的是 $20$。

## Code
```cpp
#include<bits/stdc++.h>

using namespace std;

int main() {
	srand(time(0));
    cout << "100000 20\n";
	for(int i = 1; i <= 1e5; i++) {
		cout << char('a' + rand() % 26);
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：3)

## 思路
看到这个题本来是想学习 CF 造数据的“精髓”的，一看这不水题么。

想要用好哈希必须知道一个经典定理：在大小为 $N$ 的集合中随机取出元素，期望 $O(\sqrt{N})$ 次后第一次取出重复的元素。由于在此题哈希中 $N=10^9+7,\sqrt{N}\approx31623$，**这个问题只需要我们在输出的字符串中创建远大于 $31623$ 个的长度为 $l$ 的不同连续子串即可。取 $n=10^5,l=10^3$，字符串随机生成可以满足要求**。

进一步，经过计算可以得出，用值域大小为 $N$ 的随机哈希生成 $n$ 个数，**不产生冲突**的概率为：
$$
\prod_{i=N-n+1}^N(1-\frac{i}{N})=\frac{n!\times C(N,n)}{N^n}
$$
令 $N=10^9+7$，经过计算，此值大约在 $n\ge 37234$ 时降至 $50\%$，$n\ge95970$ 时降至 $1\%$，$n\ge 166222$ 时降至百万分之一。

取 $n=10^5,l=10^3$，不冲突的概率约为 $0.74\%$，足以通过本题。

注意 $l$ 过小会导致哈希值没有随机性并提高子串实际相同的概率，$l$ 过大会导致可能缺乏足够多的子串以产生冲突。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long double ans = 1,x;
int main(){
	printf("100000 1000\n");
	for(int i = 1;i <= 100000;i ++) printf("%c",rand() % 26 + 'a');
	return 0;
}
```
## 启示
单哈希随手都能卡。

改进方法如下：
- 用不同方法生成多个哈希值，全部哈希值相同时才判定字符串相等，令不同哈希值的值域为 $D_i$，则随机情况下冲突的期望次数为 $O(\sqrt{\prod D_i})$。
- 不使用哈希，在不同情况下平替有 KMP、Manacher、后缀树组等。
- [见此](https://www.luogu.com.cn/problem/P11615)，期望线性的哈希表应在对应位置处开动态数组存储内容。

---

## 作者：lsd110504lsd (赞：3)

>VFleaKing:?
>
>hzhwcmhf:切。

根据生日悖论，如果可以随机选取一列数字，出现重复数字需要的抽样规模的期望也是  $O(\sqrt n)$  的。所以期望随机 $\sqrt{10^9+7}$ $\approx30000 $ 个串中就会有相同的哈希值，所以让字符串的长度变长，就可以卡掉单模哈希。

~~[生日悖论传送门](https://oi.wiki/math/number-theory/pollard-rho/#%E7%94%9F%E6%97%A5%E6%82%96%E8%AE%BA)~~


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(0));
	int n,l;
	n=1e5,l=520;
	cout<<(int)n<<" "<<l<<endl;
	for(int i=1;i<=n;i++){//相当输出一个长度为n的字符串
		char s='a'+rand()%26;
		cout<<s;
	}
}
```

---

## 作者：Aurelia_Veil (赞：2)

# 题解：P12198 Hash Killer II

这题以为很难呢，结果就是一道简单的概率题。

首先，根据题目我们可以知道，这题需要生日悖论的结论，对于模数为 $L$ 的哈希，$\sqrt{L}$ 次就会有很大概率发生哈希冲突，所以长度就确定了，就是 $\sqrt{MOD} = \sqrt{10^9 + 7} \approx 31622.776$，所以我们可以取比这个数大的数，建议 $10^5$ 以上。

那怎么输出字符串呢？不管了，直接胡乱输出，因为这样哈希冲突的概率最大。

代码太简单了，就不给了咩～

---

## 作者：easy42 (赞：1)

根据生日悖论，从 $n$ 个数中取数，期望随机 $O(\sqrt n)$ 即可以产生冲突。哈希等价于从 $mod$ 取中取数产生冲突，即至少取 $\sqrt {mod}$ 个数即可。

```cpp
#include<bits/stdc++.h>
int main(){
    srand(time(0));
    std::cout<<100000<<" "<<20<<std::endl;
    for(int i=1;i<=100000;i++) std::cout<<char('a'+rand()%26);
}
```

---

## 作者：the_Short_Path (赞：1)

~~为什么我感觉 II 比 I 简单。~~

注意 $l$ 不能太大，也不能太小，$20$ 左右就行了。

那么只要 $n$ 足够大，单哈希就会冲突。证明：

从 $n$ 个数中随机取数第 $i$ 个数不是重复数的概率为: 
$$\begin{equation}
P(i)=\left( \frac{n-1}{n} \right)^{i-1}
\end{equation}$$
不是重复数的期望为：
$$\begin{equation}
\begin{split}   E(n) &=\sum_{i=1}^{n}{P(i)}\\
      &=\sum_{i=1}^{n}{\left( \frac{n-1}{n} \right)^{i-1}}\\
      &=\frac{1-\left( \frac{n-1}{n} \right) ^n}{1-\frac{n-1}{n}}\\
      &=n-n\left( \frac{n-1}{n} \right) ^n
\end{split}
\end{equation}$$
所以重复数的个数的期望为：
$$\begin{equation}
\begin{split}   E'(n)&=n-E(n)\\
      &=n\left( \frac{n-1}{n} \right) ^n
\end{split}
\end{equation}$$
则重复数的百分比的期望为：
$$\begin{equation}
\begin{split}   r(n)&=\frac{E'(n)}{n}\\
      &=\left( \frac{n-1}{n} \right) ^n\\
      &=\left( 1-\frac{1}{n} \right)^n
\end{split}
\end{equation}
$$
当 $n$ 趋于无穷时：
$$\begin{equation}
\begin{split}  \lim_{n \rightarrow \infty }{r(n)}&=\lim_{n \rightarrow \infty}{\left( 1-\frac{1}{n} \right)^n}\\
      &=\frac{1}{e}\\
      &\approx0.36788
\end{split}
\end{equation}$$
也可以参照[生日悖论](https://baike.baidu.com/item/%E7%94%9F%E6%97%A5%E6%82%96%E8%AE%BA/2715290)来理解。总之求 $\sqrt{mod}$ 次就卡掉了（$mod$ 为模数）。
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n = 100000, l = 20;
int main() {
    // 不需要加 srand(time(NULL)) 等代码，直接调用 rand() 就行了
    cout << n << " " << l << endl;
    for (int i = 1; i <= n; i++) cout << (char) (rand() % 26 + 'a');
    return 0;
}
```

---

## 作者：ILearnedSomeCoding (赞：1)

这题很好过的。
## 生日悖论
> 如果一个房间里有超过 $23$ 个人，那么至少有两个人的生日相同的概率要大于 $50\%$。

根据结论，期望随机 $O(\sqrt{p})$ 个哈希就能有重复。$\sqrt{10^9+7} \approx 30000$，所以随机输出 $100000$ 个字母就可以了。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    cout << "100000 100\n";
    for(int i = 1;i <= 100000;i++){
        printf("%c", 'a'+(rand()&15));
    }
}
```
其实如果运气特别差的话，也有可能不行。但是概率特别小，多试几次就答对了。
## 结论
单哈希随机的一个大的数据就能卡，所以我们可以使用多哈希，或者直接用标准库。



---


本蒟蒻第二次写题解，上次题解关了，这次管理求过。

---

## 作者：Merlin_Meow (赞：1)

## Analysis

单模哈希实际上是非常好卡的。

由生日悖论可知，对于一个模数为 $p$ 的哈希，取 $\sqrt{p}$ 次就大概率会发生哈希冲突。于是我们只需要胡乱输出随机字符就可以卡掉它。$\sqrt{10^9+7}\approx 31629.78$，为了保险我们直接取 $10^5$ 次即可稳定通过。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    mt19937 RAND(time(0));
    int n = 100'000, l = 100;
    cout << n << " " << l << endl;
    for (int i = 1; i <= n; i++)
        cout << char(RAND() % 26 + 'a');
    cout << endl;
    return 0;
}
```

---

## 作者：lkjlkjlkj2012 (赞：0)

> ~~我赌双哈希能过~~ [P12201](https://www.luogu.com.cn/problem/P12201)
### 思路
我们直接随机字符串，那么一共有 $n-l+1$ 个子串。因为我们的字符串是随机的，那么这些字串可以看作全部是随机的。由生日悖论，因为我们的状态空间大小为 $\omega=10^9+7$，所以只要 $n-l+1>O(\sqrt{\omega}) \approx 3 \times 10^4$ 就有大概率通过。
### 实现细节
注意如果 $l$ 开太大 $n-l+1$ 就会很小，但如果 $l$ 开太小字串就没有随机性了。
### 代码

```cpp
#include <bits/stdc++.h>
#define DEBUG
using namespace std;

int main()
{
 	#ifndef DEBUG
 	#ifndef ONLINE_JUDGE
 	freopen(".in","r",stdin);
 	freopen(".out","w",stdout);
 	#endif
 	#endif
 	ios::sync_with_stdio(0);
 	cin.tie(0);
 	cout.tie(0);
    srand(time(0));
    int n=100000,l=10;
    cout<<n<<" "<<l<<endl;
    for(int i=1;i<=n;i++)
        cout<<(char)('a'+rand()%26);
 	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

哈希冲突的概率可以转化为生日悖论，相当于有 $p$ 天，同时有 $n-l+1$ 个人，求生日相同的概率。

根据生日悖论的结论：有 $n$ 天，其中有相同生日的人时，期望总人数是 $O(\sqrt{n})$ 的（具体证明见 [ OI-wiki](https://oi-wiki.org/math/number-theory/pollard-rho/#%E7%94%9F%E6%97%A5%E6%82%96%E8%AE%BA)）。

根据生日悖论，模数是 $x$ 的哈希期望上需要 $O(\sqrt{x})$ 次，所以随即输出很长的字符串时。

相当于需要 $O(\sqrt{p})$ 个字符串，大约 $3.2\times 10^4$。显然此时 $n>3.2\times 10^4$，所以随机一个特别长的字符串就行，$l$ 设置的小点就行，别太小（太小就没有随机性了）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<char>randchar('a','z');
int main(){
    cout<<"100000 17\n";
    for(int i=1;i<=100000;i++)
        cout<<randchar(rnd);
    return 0;
}
```

---

## 作者：Jorisy (赞：0)

前置内容：「生日悖论」。

设一年有 $n$ 天，随机选择 $k$ 人，考虑计算存在两人生日相同的概率（随机的生日在 $n$ 天中均匀分布，人与人相互独立）。

设事件 $A$ 为「所有人生日互不相同」，容易得到：

$$
P(A)=\prod\limits_{i=0}^{k-1}\dfrac{n-i}n
$$

则原问题的概率就是 $P(\overline A)=1-P(A)$。

「生日悖论」本身，是在算可以使得 $P(\overline A)
\ge\dfrac 12$ 的 $k_{\min}$。我们这里计算一下：

$$
\begin{aligned}
P(A)&=\prod\limits_{i=0}^{k-1}\dfrac{n-i}n\\
&=\prod\limits_{i=0}^{k-1}\left(1-\dfrac{i}n\right)\\
&\le\prod\limits_{i=0}^{k-1}\exp\left(-\dfrac{i}n\right)\\
&=\exp\left(-\dfrac{k(k-1)}{2n}\right)
\end{aligned}
$$

以上推导使用了十分经典的不等式 $x+1\le e^x$，证明导一下就可以了，这里不就此展开。

然后我们代入 $\dfrac12$，有：

$$
\exp\left(-\dfrac{k(k-1)}{2n}\right)\le\dfrac12
$$

如果将 $n=365$ 代入，会得到 $k\ge 23$，这十分反生活直觉，因此会被称作「悖论」。

期望下遇到重复生日的人数是 $O(\sqrt n)$ 量级的。

---

回到原题，对 $p$ 取模相当于在 $[0,p)$ 内随机取数了，那么我们把 $l$ 取小一点，$n$ 取满，串直接随机即可。

---

## 作者：undefined_Ryan (赞：0)

生日悖论。看起来这个东西不好搞，但其实可以直接随机。假设每个子串的哈希值是 $[0,p-1]$ 之间的相互独立的等概率随机数，那么对于 $k$ 个这样的字串，哈希值互不相同的概率是

$$\frac{p(p-1)(p-2)\cdots(p-k+1)}{p^k}.$$

生日悖论就是指这个结果在 $k$ 达到 $\sqrt p$ 左右的时候会反直觉地小。在这道题的条件下（$n=100000$，$l=100$）时这个概率大约是 $0.68\%$（如果真的出现了这种情况建议调一下随机数种子）。

注意 $l$ 不能过小或过大，因为 $l$ 过小时哈希值与字符串一一对应，$l$ 过大时 $k$ 会比较小（$l=10000$ 时概率为 $17.4\%$，不足以通过本题）。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    cout<<"100000 10\n";
    for (int i=1;i<=100000;i++) cout<<char(rand()%26+'a');
    cout<<endl;
}
```

---

