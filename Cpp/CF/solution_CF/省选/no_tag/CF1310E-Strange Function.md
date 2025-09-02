# Strange Function

## 题目描述

Let's define the function $ f $ of multiset $ a $ as the multiset of number of occurences of every number, that is present in $ a $ .

E.g., $ f(\{5, 5, 1, 2, 5, 2, 3, 3, 9, 5\}) = \{1, 1, 2, 2, 4\} $ .

Let's define $ f^k(a) $ , as applying $ f $ to array $ a $ $ k $ times: $ f^k(a) = f(f^{k-1}(a)), f^0(a) = a $ .

E.g., $ f^2(\{5, 5, 1, 2, 5, 2, 3, 3, 9, 5\}) = \{1, 2, 2\} $ .

You are given integers $ n, k $ and you are asked how many different values the function $ f^k(a) $ can have, where $ a $ is arbitrary non-empty array with numbers of size no more than $ n $ . Print the answer modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
3 1```

### 输出

```
6```

## 样例 #2

### 输入

```
5 6```

### 输出

```
1```

## 样例 #3

### 输入

```
10 1```

### 输出

```
138```

## 样例 #4

### 输入

```
10 2```

### 输出

```
33```

# 题解

## 作者：final_trump (赞：13)

# CF1310E Strange Function

我们初看此问题时可能会毫无头绪，不知道怎么设计状态及转移。这启发我们逐步分析问题。我们应该会想到对 $k$ 进行讨论

### $k=1$

相当于我们要统计每个数在 $A$​ 集合里出现了多少次，设求出来的集合为 $B$​ 。而我们知道 $\sum_{x\in B} x=|a|$​ ，且 $B$ 内部无序，所以问题被转化为了求 $\forall_{1\leq i\leq n} i$ 的**划分数** ，简单的 dp 一下就行了。

```cpp
f[0]=1;
for(int i=1;i<=n;++i)
    for(int j=i;j<=n;++j) (f[j]+=f[j-i])%=MOD;
for(int i=1;i<=n;++i) (ans+=f[i])%=MOD;
printf("%d\n",ans);
```

### $k=2$

我们沿用 $k=1$ 时的定义，且设 $C=f(B)$ 。我们尝试着用 $C$ 去推到一个可能的 $A$ 。设 $C=\{c_1,c_2,\dots c_m\}$ ，且 $c_1\geq c_2\geq \cdots \geq c_m $ 。并设 $c_i$ 在 $B$ 中作为 $v_i$ 的出现次数，那我们只要能找到一组 $\{v_i\}$ ，使得 $\sum_{i=1}^m c_iv_i \leq n$ 成立即可。换句话说 我们要在 $C$ 已知的情况下最小化 $\sum_{i=1}^m c_iv_i$ 。根据排序不等式，有 $\sum_{i=1}^m c_iv_i \geq \sum_{i=1}^m c_ii$ 。于是问题被我们转化成了如下问题：

>  给定 $n$​​​ ，求有多少满足条件的 $\{c_i\}$​​​ ，满足 $c_1\geq c_2\geq \cdots \geq c_m $​​​ ，且 $\sum_{i=1}^m c_ii \leq n$​​​ ​

对于该问题，我们先对所有数减去 $c_m$​ ，然后对剩下的所有数减去 $c_{m-1}$ ，以此类推，问题又被我们进一步转化：

> 给定 $n$ ，求有多少满足条件的 $\{c_i\}$ ，满足  $\sum_{i=1}^m c_i\frac{i(i+1)}{2} \leq n$ 

又是简单 dp

```cpp
f[0]=1;
for(int i=1;i*(i+1)/2<=n;++i)
	for(int j=i*(i+1)/2;j<=n;++j) (f[j]+=f[j-i*(i+1)/2])%=MOD;
for(int i=1;i<=n;++i) (ans+=f[i])%=MOD;
printf("%d\n",ans);
```

### $k \geq 3$

当 $k \geq 3$ 时问题变得更复杂了（当然您可以尝试着推一下 $k=3$ 时的 dp ），但我们没有注意到的一点是：当 $n$ 一定时，$k$ 越大 答案越小。设 $k=3$ 时$f^k(A)$ 里的元素和为 $m$ ，我们尝试最小化当前的 $n$ 。对于 $k=2$ 这一层，要想令当前的和最小，那一定是填 $m$ 个 $1$ 最优，则对于 $k=1$ 就只能填 $\{1,2,\dots,m\}$ 其和为 $\frac{m(m+1)}{2}$ 也就是我们最小化的 $n$ 。将 $n=2020$ 代入，解得 $m \leq 64$ 。也就是说，当 $k\geq 3$ 后，其元素和至多为 $64$ 。$64$ 的划分数 $\mathscr{P}(64)=12308138$ ，我们暴力枚举其所有划分，看其对应的 $A$ 的最小值是否小于 $n$ 即可。

暴力代码就不放了



---

## 作者：Alex_Wei (赞：10)

Update on 2022.11.20 重写题解，原题解见 [剪贴板](https://www.luogu.com.cn/paste/abfnhowu)。

[CF1310E Strange Function](https://www.luogu.com.cn/problem/CF1310E)

直接枚举初始集合 $S$ 并对 $f ^ k(S)$ 去重不太可行，转而考虑枚举 $T = f ^ k(S)$ 并检查是否存在 $S$ 使得 $|S| \leq n$ 且 $f ^ k(S) = T$。

考虑从 $T$ 一步步反推得到一个合法的 $S$。因为对 $S$ 的限制 **只有大小不大于 $n$**，所以我们可以尝试求出 $|S|$ 的最小值 $z$。若 $z\leq n$，则 $T$ 合法，否则 $T$ 不合法。

考虑解开一层 $f$ 的过程 $T = f(S)$，设 $T = \{t_1, t_2, \cdots, t_u\}$，则 $S$ 必须包含 $t_i$ 个 $c_i$ 且 $c_i$ 互不相同，即 $|S| = \sum t_i$。可以发现每次解开一层 $f$，$T$ 的大小就会变成它包含的元素之和。自然地，我们希望 $S$ 的元素尽量小。最优方案是将 $t_i$ 从大到小排序后令 $c_i = i$，容易证明这种方案形成的 $S = \{s_1, s_2, \cdots, s_v\}$ 比其他任何方案形成的 $S' = \{s'_1, s'_2, \cdots, s'_{v}\}$ 都要 **严格不劣**，即 $s_i\leq s'_i$，因而保证最终 $|S|$ 的最小性。

换言之，$f$ 是多对一的，我们无法找到其反函数 $f ^ {-1}$。但我们找到了一个解开 $f$ 的方案 $g$，使得最终的 $T$ 在 $k$ 次解开 $f$ 之后得到的 $S = g ^ k(T)$ 满足其为使得 $T = f ^ k(S)$ 的 $|S|$ 最小的 $S$。因此，直接枚举 $T$，若 $|g ^ k(T)| \leq n$ 则合法。

当 $k = 1$ 时，可知 $|S| = \sum t_i$，因此答案即不大于 $n$ 的数的划分数之和，$\mathcal{O}(n ^ 2)$ 计算。

当 $k = 2$ 时，可知 $|S| = \sum it_i$，直接枚举 $i$ 和 $t_i$ DP。因为 $i(i + 1) \leq 2n$ 所以时间复杂度 $\mathcal{O}(n ^ {2.5})$。另一种思路是根据 $t_i\geq t_{i + 1}$ 设 $d_i = t_i - t_{i + 1}$，这样就可以忽略 $t_i\geq t_{i + 1}$ 的要求少记录一维。考虑 $d_i$ 对 $|S|$ 产生的贡献，发现相当于为 $t_1\sim t_i$ 加上 $d_i$，贡献即 $d_ii(i + 1) / 2$。相当于有若干种物品，第 $i$ 种物品的重量为 $i(i + 1) / 2$ 且有无限个，求选择物品使得重量总和 $\leq n$ 的方案数。这是一个类似 $k=1$ 求划分数的完全背包，可以 $\mathcal{O}(n ^ {1.5})$ 带走。

当 $k = 3$ 时，推一推发现贡献和 $t$ 的后缀和有关，很不可做。但我们在做题时应当感受到 $f$ 函数坍缩很快，所以 $T$ 的方案数应该不会太多。这启发我们写个爆搜，判断是否有 $|g ^ k(T)| \leq n$。为了防止在判断过程中浪费太多时间，考虑到我们可以快速求出 $|g ^ 2(T)|$，所以不妨判 $|g ^ 2(T)|$ 而不是 $|g(T)|$。只需进行 $k - 2$ 次令 $T = g(T)$ 并判断是否有 $|g ^ 2(T)| \leq n$。对于 $n = 2020$ 的极限数据，它也能在时间范围内得到解。实际上判 $|g ^ 3(T)| \leq n$ 可以更快，因为它保证了任意时刻 $|T| = \mathcal{O}(\sqrt n)$，但 $|g ^ 3(T)|$ 的表达式较复杂。

对于 $k > 3$，限制只会比 $k = 3$ 更严格，符合条件的 $T$ 大幅减少，上述爆搜可以更快得到解。

时间复杂度上界：注意到 $|g ^ 2(T)| \geq |T|(|T| + 1) / 2$，所以当 $k = 3$ 时，$|g(T)| \leq 62$，$T$ 的方案数上界为 $1\sim 62$ 的划分数之和，在 $10 ^ 7$ 级别。很多不合法的方案都被跳过了，所以实际检查次数很少。

[代码](https://codeforces.com/contest/1310/submission/181679879)。

---

## 作者：Hilaria (赞：0)

### [CF1310E Strange Function](https://www.luogu.com.cn/problem/CF1310E)

- 题意：

对于一个多重集合$a$

我们定义$f(a)$为每个数字出现的次数的多重集合

现在给你 $n$ 和 $k$，求对于所有大小小于等于 $n$ 的初始多重集合$a$，$f^k(a)$有多少种不同的可能，答案对 $998244353$ 取模。

$1\leq n,k\leq 2020$

- 思路：

1. $k=1$

我们假设 $f(S)=a_1\geq a_2\geq a_3\dots a_m$。

此时只要满足 $\sum a_i \leq n$ 即可，即在 $a_1$ 个 $1$，$a_2$ 个 $2\dots$ 时 $n$ 最小。

这个就是求小于等于 $n$ 的数的划分，简单背包即可。

```
void sol1() {
	int res=0;
	f[0]=1;
	for(int i=1;i<=n;i++) {
		for(int j=i;j<=n;j++) (f[j]+=f[j-i])%=P;
	}
	for(int i=1;i<=n;i++) (res+=f[i])%=P;
	cout<<res<<'\n';
}
```


2. $k=2$

我们假设 $f^2(S)=b_1\geq b_2\geq b_3\dots b_m$。

此时只要满足 $\sum b_i\times i \leq n$ 即可，即在 $b_1$ 个 $1$，$b_2$ 个 $2\dots$ 时 $n$ 最小，然后由于这个对 $b_i$ 的大小有限制，我们考虑转换一下。

我们定义 $d_i = b_i - b_{i+1}$，那么一个 $d_i$ 一定能对应唯一的一个 $b_i$。

然后我们就可以代价考虑合法的 $d_i$ 的方案数。

我们进行一个手玩，我们可以发现：

$\sum b_i\times i$

$= (b_1-b_2) + 3\times (b_2-b_3) + 6\times(b_3-b_4)\dots$

$= \sum \dfrac{i\times (1+i)}{2} d_i$

这个又可以简单背包了。


```
void sol2() {
	int res=0;
	f[0]=1;
	for(int i=1;i*(i+1)/2<=n;i++) {
		for(int j=i*(i+1)/2;j<=n;j++) (f[j]+=f[j-(i+1)*i/2])%=P;
	}
	for(int i=1;i<=n;i++) (res+=f[i])%=P;
	cout<<res<<'\n';
}
```

3. $k=3$


我们假设 $f^3(S)=c_1\geq c_2\geq c_3\dots c_m$。

此时需要我们进行手玩，此时由于 $k$ 越大，解的数量越小，此时解的数量其实已经很小了，具体而言，只要满足（tot 为 $c$ 的和）：

```
int res=0,las=tot;
for(int i=1;i<=cnt;i++) res+=(2*las-c[i]+1)*c[i]/2*i,las-=c[i];
res<=n
```

即值大的应该配小的，即转换成 $c_i$ 个 $i$ 时能使 $n$ 最小。

然后我们尝试最小化 $n$，当 $\sum c_i = q$ 时，肯定是当 $c_1=q$ 时最优，然后 $b_i =1$，所以此时 $a_i = 1,2\dots q$，所以此时 $n=\dfrac{q(1+q)}{2}$，那么 $q\leq 64$ 左右，然后我们考虑暴力，先打个表算一下 $q=64$ 时的划分数量，发现是 $12308138$，然后我们按上面的柿子算出 $2020 3$ 是 $451945$，但是到 $2020 4$ 就变成 $687$ 了，答案很小，直接暴力加一点剪枝就行了。

---

