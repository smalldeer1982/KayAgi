# [ABC267Ex] Odd Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc267/tasks/abc267_h

長さ $ N $ の整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。

$ A $ から要素を奇数個選ぶ方法のうち、選んだ要素の総和が $ M $ になるものの個数を $ 998244353 $ で割ったあまりを求めてください。

ただし、$ 2 $ つの選び方が異なるとは、ある整数 $ i\ (1\ \le\ i\ \le\ N) $ が存在して、一方の選び方では $ A_i $ を選び、もう一方では選んでいないことを言います。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 10^5 $
- $ 1\ \le\ M\ \le\ 10^6 $
- $ 1\ \le\ A_i\ \le\ 10 $
- 入力は全て整数。

### Sample Explanation 1

条件を満たす選び方は以下の $ 3 $ 通りです。 - $ A_1,A_2,A_3 $ を選ぶ。 - $ A_1,A_2,A_4 $ を選ぶ。 - $ A_5 $ を選ぶ。 $ A_3,A_4 $ を選んだ場合、総和は $ 6 $ ですが選んだ要素の個数が奇数個でないため条件を満たしません。

## 样例 #1

### 输入

```
5 6
1 2 3 3 6```

### 输出

```
3```

## 样例 #2

### 输入

```
10 23
1 2 3 4 5 6 7 8 9 10```

### 输出

```
18```

# 题解

## 作者：NaCly_Fish (赞：7)

[题目链接](https://www.luogu.com.cn/problem/AT_abc267_h)

看到 AT 原题的提交记录中有这个做法，不过没在题解区找到讲这个做法的。比较 tricky 但是不难，我就来讲一下吧。

以下设 $V=\max\{ a_i \}$。

****

首先问题的转化很简单，对于多项式

$$\prod_{i=1}^n(1+y x^{a_i}) \bmod (y^2-1)$$

答案是其 $[x^my^1]$ 系数。使用 DFT 的思想，可以知道答案为

$$[x^m]\frac 12 \left(\prod_{i=1}^n(1+x^{a_i})-\prod_{i=1}^n(1-x^{a_i}) \right)$$

我们只用考虑计算 $F(x)$ 的 $x^m$ 系数，又由于 $V\leq 10$，可以将其写为

$$F(x)=\prod_{i=1}^V(1+x^i)^{c_i}$$

其中 $c_i$ 表示有多少项 $a_j=i$。对等式两边取 $\ln$ 再求导得到

$$\frac{F'(x)}{F(x)}=\sum_{i=1}^V\frac{ic_i x^{i-1}}{1+x^i}$$

将 $F(x)$ 移到等式右边，再提取系数即得

$$(k+1)f_{k+1}=\sum_{i=1}^Vic_i [x^{k-i+1}]\frac{F(x)}{1+x^i}$$

这里 $g_i(x)=F(x)/(1+x^i)$ 的系数是容易动态维护的，直接提取系数就有递推

$$g_{i,k}+g_{i,k-i}=f_k$$

这样从 $f_k$ 推到 $f_{k+1}$ 的时间复杂度就是 $\mathcal O(V)$ 的，总时间复杂度也就是 $\mathcal O(mV)$。

对于另一部分 

$$F(x)=\prod_{i=1}^V(1-x^i)^{c_i}$$

其做法和上一部分几乎是一致的，照着做即可。

---

## 作者：lingfunny (赞：4)

# [ABC267Ex] Odd Sum 题解

没有题解所以写一个，本质上这道题思维上并不困难。

要求奇数，肯定和偶数脱不了干系。常规的 01 背包操作是 $O(nm)$ 的，不能通过本题。

一般的 01 背包问题都是有多项式意义的，比如给定 $n$ 个物品重量分别为 $A_1,A_2,\dots,A_n$，则 $[x^k]\prod (1+x^{A_i})$ 即为凑出重量为 $k$ 的方案数。

## 解法 1

一般情况下暴力乘还是 $O(nm)$ 的，注意到值域非常的小，所以对于重量相同的物品可以看作短多项式快速幂。

短多项式快速幂是可以在 $O(m)$ 的时间内求解的，求解出来之后可以把多项式系数拆分为 $\displaystyle\sum_{i\equiv 0\pmod {2A_i}}a_ix^i$ 和 $\displaystyle\sum_{i\equiv A_i\pmod {2A_i}}a_ix^i$ 的两个多项式，分别表示选偶数个物品和奇数个物品（不过我更建议直接组合意义），不妨设为 $F$ 和 $G$。合并时，有 $F'=F_1F_2+G_1G_2, G'=F_1G_2+G_1F_2$。

好消息是模数是 $998\,244\,353$，这一部分除了 NTT 我也没想到其它解法。

所以总时间复杂度 $O(\lvert A_i \rvert m\log m)$，当然这里 $\lvert A_i \rvert$ 表示值域。

如果还不会 $O(m)$ 求短多项式快速幂的可以看[这里](https://280800.blog.luogu.org/solution-at2180)。

~~明明理论时间复杂度很优却跑不过别人的[提交记录](https://atcoder.jp/contests/abc267/submissions/37068398)。~~

## 解法 2

直接折半，对左右分治求解，最后直接按解法 1 中的规则合并背包即可。

时间复杂度 $T(n)=2T(n/2)+O(10n\log 10n)\approx O(m\log m\log n)$。

官方题解是类似哈夫曼树，差不多也是这个复杂度。

---

题外话：[zhoukangyang](https://atcoder.jp/users/zhoukangyang) 有个神秘的[组合（类似？）做法](https://atcoder.jp/contests/abc267/submissions/34808890)。

---

## 作者：Super_Cube (赞：2)

# Solution

设 $f_{i,j}$ 表示前 $i$ 个数凑出和为 $j$ 的方案数，$g_{i,j}$ 表示前 $i$ 个数用偶数个数凑出和为 $j$ 的方案数减去用奇数个数凑出和为 $j$ 的方案数。初始化 $f_{0,0}=g_{0,0}=1$。转移：$f_{i,j}=f_{i-1,j}+f_{i-1,j-a_i},g_{i,j}=g_{i-1,j}-g_{i-1,j-a_i}$。答案为 $\dfrac{f_{n,m}-g_{n,m}}{2}$。这是个很普通的 0/1 背包问题。

考虑生成函数，设 $F_i(x)=\sum f_{i,j}\cdot x^j,G_i(x)=\sum g_{i,j}\cdot x^j$。

根据前面的 dp 转移式，可以得到：$F_i(x)=F_{i-1}(x)+x^{a_i}F_{i-1}(x),G_i(x)=G_{i-1}(x)-x^{a_i}G_{i-1}(x)$。

所以 $F_n(x)=\displaystyle\prod_{i=1}^n(1+x^{a_i}),G_n(x)=\prod_{i=1}^n(1-x^{a_i})$，最后的答案对应 $\dfrac{[x^m](F_n(x)-G_n(x))}{2}$。

注意到 $a_i\le 10$。设 $c_i$ 为 $a$ 中元素为 $i$ 的个数，那么有 $F_n(x)=\displaystyle\prod_{i=1}^{10}(1+x^i)^{c_i},G_n(x)=\prod_{i=1}^{10}(1-x^i)^{c_i}$。由二项式定理展开得到 $F_n(x)=\displaystyle\prod_{i=1}^{10}\sum_{j=0}^{c_i}\binom{c_i}{j}x^{ij},G_n(x)=\displaystyle\prod_{i=1}^{10}\sum_{j=0}^{c_i}(-1)^{j}\binom{c_i}{j}x^{ij}$。

这样至多进行 $18$ 次多项式乘法，可过。

---

## 作者：EuphoricStar (赞：2)

直接暴力跑背包的复杂度太高了，考虑优化。

发现值域很小，对值域从小到大跑背包。设 $f_i$ 为用奇数个数凑出和为 $i$ 的方案数，相对地 $g_i$ 是用偶数个数。设当前枚举到的值为 $x$，数量为 $c_x$，那么我们要做的就是：

- $f_i \times \binom{c_x}{d} \to f_{i + dx}, d \mid 2$；
- $f_i \times \binom{c_x}{d} \to g_{i + dx}, d \nmid 2$；
- $g_i \times \binom{c_x}{d} \to f_{i + dx}, d \nmid 2$；
- $g_i \times \binom{c_x}{d} \to g_{i + dx}, d \mid 2$。

至此可以观察出卷积形式，NTT 优化。

每次枚举 $x$，实际上要做 $4$ 次卷积，$12$ 次 NTT。直接跑是 $O(120 m \log m)$ 的，还是过不去。考虑做一些上界的优化，$f_i, g_i$ 的下标上界设置为 $\sum\limits_{j=1}^x j \times c_j$，就可以通过了。

[code](https://atcoder.jp/contests/abc267/submissions/41672549)

---

## 作者：junxis (赞：2)

# Perface
也许是因为网上抄的 $\mathtt{NTT}$ 板子，跑到了最优解 rank 2，那就来一篇新手向题解吧。
# Analysis
记 $\text{od}_i$ 为选奇数个数，和为 $i$ 的方案数，$\text{ev}_i$ 为选偶数个数，和为 $i$ 的方案数。

然后设形式幂级数 $O(x)=\sum \text{od}_i x^i,E(x)=\sum \text{ev}_i x^i$。

首先，$F(x)=E(x)+O(x)=\prod\limits_{i=1}^{n}(1+x^{a_i})$，即对 $a$ 做计数背包。

受到和差对偶关系的启发，我们不妨研究一下 $G(x)=\prod\limits_{i=1}^{n}(1-x^{a_i})$ 代表着什么。

记 $\text{coef}=[x^i]G(x)$。

若有 $\sum\limits_{j=1}^m a_{p_j}=i$：

+ $m$ 为奇数

$\text{coef}\gets\text{coef}-1$

+ $m$ 为偶数

$\text{coef}\gets\text{coef}+1$

所以 $[x^i]G(x)=\text{coef}=\text{ev}_i-\text{od}_i$。

即 $G(x) = E(x) - O(x)$。

综上，$O(x)=\dfrac{1}{2}(F(x)-G(x))$。

我们有一个小优化，观察到数据范围中 $x \leq 10$，我们记 $\text{cnt}_i$ 为 $i$ 的出现次数。

那么 $F(x)=\prod\limits_{i=1}^{10}(1+x^{i})^{\text{cnt}_i}$。

$G$ 同理。

用二项式定理展开中间的项，然后分治 $\mathtt{NTT}$ 乘起来就好了。

**[code](https://atcoder.jp/contests/abc267/submissions/37602386)**

---

## 作者：Exschawasion (赞：2)

一个很显然的思路就是设 $f[i][j][o]$ 表示目前到了第 $i$ 个数，和为 $j$、选了 $o$ 个数的方案数然后 dp。$o$ 是用来判断奇偶性的，取值只需要是 $1$ 或 $0$。时间复杂度是 $\mathcal O(nm)$ 的。


0-1 背包组合问题是有多项式意义的。记第 $i$ 个数 $a_i$，则 $\prod _{i=1}^{n}(1+x^{a_i})$ 的 $x^v$ 项的系数就是凑成 $v$ 的方案数。**这是个结论**。

给个简单的证明。找规律：

- $2$ 个物品能凑出的方案数为 $\{0,a_1,a_2,a_1+a_2\}$；
- $3$ 个物品能凑出的方案数为 $\{0,a_1,a_2,a_3,a_1+a_2,a_1+a_3,a_2+a_3,a_1+a_2+a_3\}$；
- ……

非常像子集枚举。但是要把**值相同**的项合并起来，不太好处理。其实加法可以通过指数转化成乘法，即进行 $a_1+a_2 \rightarrow x^{a_1+a_2}$ 的转化。而这可以化成多个多项式相乘的形式：即 $\prod _{i=1}^{n}(1+x^{a_i})$。

因为限制的是奇数个，思考怎么容斥掉选了偶数个的方案数。需要找到某个数，乘以奇数次和乘以偶数次的结果不同。很显然 $-1$ 就满足要求。

因此，$a_i$ 项的系数就是 $-1$。$\prod _{i=1}^{n}(1-x^{a_i})$ 就是符合要求的多项式。感性理解下，奇数个 $x^{a_i}$ 乘起来是负数，而偶数个乘起来是正数。严格证明也不难，就不写了。

令 $F=\prod _{i=1}^{n}(1+x^{a_i}),G=\prod _{i=1}^{n}(1-x^{a_i})$。记 $P[i]$ 表示 $x^i$ 的系数，那么 $F[m]$ 就是**不考虑奇偶**的方案数，$G[m]$ 就是**偶数方案数减去奇数方案数**。

最终答案就是 $\frac{F[m]-G[m]}{2}$。记得除以二，因为奇数被算了两次。时间复杂度 $\mathcal(m\log m \log n)$，能过。关键代码如下：

```cpp
const int mod=998244353,maxn=500000+5;
poly F[maxn],G[maxn];//poly 板子就不放了
int main(){
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)F[i][0]=G[i][0]=1,F[i][a[i]]=1,G[i][a[i]]=mod-1;
    for(int i=2;i<=n;i++)F[i]=F[i-1]*F[i],G[i]=G[i-1]*G[i];
    cout<<1ll*((1ll*F[n][m]-G[n][m])%mod+mod)%mod*qpow(2,mod-2)%mod;
}
```

Lingfunny 有更优的[解法](https://280800.blog.luogu.org/solution-at-abc267-h)，是 $\mathcal O(m\log mV)$ 的。

~~但是没我快~~



---

## 作者：Galois_Field_1048576 (赞：1)

考虑二元 OGF，显然为：
$$
\prod_{i=1}^n (1+x^{a_i} y)
$$
。考虑我们只需要维护对 $y^2 - 1$ 的商环，考虑 $\mathbb R[x]/(x^2-1) \sim \mathbb R^2$，则考虑分成两个多项式 $O,E$。则有：
$$
\begin{aligned}
O(a \sqcup b) = O(a)E(b) + O(b)E(a) \\
E(a \sqcup b) = O(a)O(b) + E(a)E(b)
\end{aligned}
$$
，分治维护即可。

---

