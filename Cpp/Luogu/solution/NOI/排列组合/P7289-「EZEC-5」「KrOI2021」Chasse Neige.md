# 「EZEC-5」「KrOI2021」Chasse Neige

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/kben34ml.png)

『我喜欢雪。』

『之前虽然讨厌寒冷，现在却是最喜欢了。』

![](https://cdn.luogu.com.cn/upload/image_hosting/sbuj1tnc.png)

## 题目描述

Rikka 给了你 $T$ 组询问，每组询问给定两个正整数 $n,k$，你需要告诉 Rikka 有多少个长度为 $n$ 的排列 $\pi$ 满足如下条件：

- $\pi_1<\pi_2$

- $\pi_{n-1}>\pi_{n}$

- 恰好存在 $k$ 个位置 $i(2\leq i\leq n-1)$ 满足 $\pi_{i-1}<\pi_{i}$ 且 $\pi_{i}>\pi_{i+1}$。

答案对 $998244353$ 取模。

## 说明/提示

### 样例解释 1

对于第一组询问，$n=3,k=1$，$(1,3,2)$ 和 $(2,3,1)$ 均满足条件，答案为 $2$。

对于第二组询问，满足条件的排列为：

$$(1,3,2,5,4),(1,4,2,5,3),(1,4,3,5,2),(1,5,2,4,3),(1,5,3,4,2)\\(2,3,1,5,4),(2,4,1,5,3),(2,4,3,5,1),(2,5,1,4,3),(2,5,3,4,1)\\(3,4,1,5,2),(3,4,2,5,1),(3,5,1,4,2),(3,5,2,4,1),(4,5,1,3,2),(4,5,2,3,1)$$

共 $16$ 个，所以答案为 $16$。

### 数据范围

| 子任务编号 | 分值 | $T\leq $ | $r\leq $ | 其他限制 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| Subtask 1 | $1$ | $1$ | $10$ |  |
| Subtask 2 | $5$ | $2\times 10^5$ | $10$ |  |
| Subtask 3 | $13$ | $1$ | $2\times 10^3$ |  |
| Subtask 4 | $13$ | $2\times 10^5$ | $2\times 10^3$ |  |
| Subtask 5 | $16$ | $2\times 10^5$ | $2\times 10^5$ | $k=\lfloor\frac{n-1}{2}\rfloor$ 且 $n$ 为奇数 |
| Subtask 6 | $16$ | $2\times 10^5$ | $2\times 10^5$ | $k=\lfloor\frac{n-1}{2}\rfloor-1$ |
| Subtask 7 | $36$ | $2\times 10^5$ | $2\times 10^5$ |  |

对于 $100\%$ 的数据，$1\leq T\leq 2\times 10^5,3\leq n\leq r\leq 2\times 10^5,\max(1,\lfloor\frac{n-1}{2}\rfloor-10)\leq k\leq \lfloor\frac{n-1}{2}\rfloor$。




## 样例 #1

### 输入

```
2 10
3 1
5 2```

### 输出

```
2
16```

# 题解

## 作者：Karry5307 (赞：19)

### 题意

$T$ 组询问，求有多少个长度为 $n$ 的排列 $\pi$ 满足如下条件：

- $\pi_1<\pi_2$

- $\pi_{n-1}>\pi_{n}$

- 恰好存在 $k$ 个位置 $i(2\le i\le n-1)$ 满足 $\pi_{i-1}<\pi_{i}$ 且 $\pi_{i}>\pi_{i+1}$。

答案对 $998244353$ 取模。

$\texttt{Data Range:}1\leq T\leq 2\times 10^5,3\leq n\leq r\leq 2\times 10^5,\max(1,\lfloor\frac{n-1}{2}\rfloor-10)\leq k\leq \lfloor\frac{n-1}{2}\rfloor$

### 前言

[题目名来源请右转这里](https://www.bilibili.com/video/BV1hE411Q7Ti)

Rikka 可爱！

### 题解

首先考虑暴力 DP。由于我们只需要关心极大值有多少个，只需要看有多少个极长单调子段。讨论一下第一个和最后一个位置所处子段的单调性就可以设四个东西来：

- 设 $f_{n,k}$ 表示长度为 $n$ 并满足 $\pi_1<\pi_2,\pi_{n-1}>\pi_n$ 且有 $k$ 个极大值的排列个数。

- 设 $g_{n,k}$ 表示长度为 $n$ 并满足 $\pi_1>\pi_2,\pi_{n-1}>\pi_n$ 且有 $k$ 个极大值的排列个数。

- 设 $g^{\prime}_{n,k}$ 表示长度为 $n$ 并满足 $\pi_1<\pi_2,\pi_{n-1}<\pi_n$ 且有 $k$ 个极大值的排列个数。

- 设 $h_{n,k}$ 表示长度为 $n$ 并满足 $\pi_1>\pi_2,\pi_{n-1}<\pi_n$ 且有 $k$ 个极大值的排列个数。

这里排列的第一个和最后一个位置并不算极大值，下面的图中，左上表示 $f_{n,k}$，右上表示 $g_{n,k}$，左下表示 $g^{\prime}_{n,k}$，右下表示 $h_{n,k}$，红圈圈出来的表示计入的极大值，必须要恰有 $k$ 个，一个极长单调子段中只标出了首尾元素。

![](https://cdn.luogu.com.cn/upload/image_hosting/3m0b5pjn.png)

同时有两个性质：如果 $(\pi_1,\cdots,\pi_n)$ 是被计入 $g$ 的，那么 $(\pi_n,\cdots,\pi_{1})$ 则会被计入 $g^{\prime}$，也即 $g_{n,k}=g^{\prime}_{n,k}$。如果 $(\pi_1,\cdots,\pi_n)$ 是被计入 $h$ 的，那么 $(n-\pi_1+1,\cdots,n-\pi_n+1)$ 则会被计入 $f$，但是要多统计一个极大值，也即 $h_{n,k}=f_{n,k+1}$。

这样只需要对 $f_{n,k}$ 和 $g_{n,k}$ 进行 DP。考虑将 $n$ 插到长度为 $n-1$ 的排列中。注意到插到极大值两边不会造成 $k$ 的增加，别的地方均可以造成极大值的增加（这也是为什么首尾不计入极大值的原因），于是可以列出如下式子：

$$\begin{cases}f_{i,j}=2jf_{i-1,j}+(i-2j)f_{i-1,j-1}+g_{i-1,j-1}+g^{\prime}_{i-1,j-1}\\g_{i,j}=2jg_{i-1,j}+(i-2j-1)g_{i-1,j-1}+g_{i-1,j}+f_{i-1,j}+h_{i-1,j-1}\end{cases}$$

第一个式子中右边分别表示插在极大值两侧，不插在极大值两侧，插在满足 $g$ 的排列的前两个位置之间，满足 $g^{\prime}$ 的后两个位置之间。第二个式子中右边分别表示插在极大值两侧，不插在极大值两侧，插在满足 $g$ 的排列的最左边，满足 $f$ 的最左边以及满足 $h$ 的前两个位置之间。

但是根据之前的两个性质可以简化一下这个式子：

$$\begin{cases}f_{i,j}=2jf_{i-1,j}+(i-2j)f_{i-1,j-1}+2g_{i-1,j-1}\\g_{i,j}=(2j+1)g_{i-1,j}+(i-2j-1)g_{i-1,j-1}+2f_{i-1,j}\end{cases}$$

注意到这两个式子长得很像，所以可以合并成一个。设 $f^{\prime}_{i,2j}=f_{i,j},f^{\prime}_{i,2j+1}=g_{i,j}$，那么很明显可以合并成这样：

$$f^{\prime}_{i,j}=jf^{\prime}_{i-1,j}+(i-j)f^{\prime}_{i-1,j-2}+2f^{\prime}_{i-1,j-1}$$

$O(n^2)$ DP 即可拿到 32pts。

注意数据范围有一个 $\max(1,\lfloor\frac{n-1}{2}\rfloor-10)\leq k\leq \lfloor\frac{n-1}{2}\rfloor$，相当于是只需要你回答靠近对角线位置的值，所以看看能不能快速求出对角线上的值。

这里存在另外一个 DP。设 $f_n$ 表示长度为 $n$ 的排列中每个数交错并且 $\pi_1<\pi_2,\pi_{n-1}>\pi_n$ 的排列个数，$g_n$ 表示长度为 $i$ 的排列中每个数交错并且 $\pi_1>\pi_2,\pi_{n-1}>\pi_{n}$ 的排列个数，枚举 $n$ 放在哪里可以得到以下式子：

$$\begin{cases}f_{n}=\sum\limits_{i\text{ is odd}}\binom{n-1}{i}f_{i}f_{n-1-i}\\g_n=\sum\limits_{i\text{ is even}}\binom{n-1}{i}g_{i}f_{n-1-i}\end{cases}$$

到这一步可以 $O(n\log^2n+n(n-2k))$ 分治 FFT，然而这个做法不优秀，但本题可以通过。

钦定 $f_n$ 在 $n$ 为偶数的时候，$g_n$ 在 $n$ 为奇数的时候为 $0$，设 $F(x),G(x)$ 为 $f,g$ 的 EGF，则有

$$F^{\prime}(x)=F^2(x)+1,G^{\prime}(x)=F(x)G(x)$$

考虑解这个微分方程，鉴于讲评时的反响，这里给出具体解法。

$$
\def\rd{\ \mathrm{d}}
\frac{\rd F(x)}{\rd x}=F^2(x)+1\\\ \\
\frac{1}{F^2(x)+1}\rd F(x)=\rd x\\\ \\
\int \frac{1}{F^2(x)+1}\rd F(x)=\int\rd x\\\ \\
\tan^{-1}F(x)=x+C\\\ \\
F(x)=\tan (x+C)
$$

可以自行检验 $C=0$，即 $F(x)=\tan x$，以及

$$
\def\rd{\ \mathrm{d}}
\frac{\rd G(x)}{\rd x}=G(x)\tan x\\\ \\
\frac{1}{G(x)}\rd G(x)=\tan x\rd x\\\ \\
\int \frac{1}{G(x)}\rd G(x)=\int \tan x\rd x\\\ \\
\ln\vert G(x)\vert=\ln\vert\sec x\vert+C\\\ \\
\vert G(x)\vert=C\vert\sec x\vert
$$

可以自行检验 $C=1$ 且绝对值取正，所以 $G(x)=\sec x$。

于是，$f^{\prime}_{n,n}=[x^n](\tan x+\sec x)$，多项式求逆即可，然后再递推回来得到所有的 $f^{\prime}$，时间复杂度 $O(n\log n+n(n-2k))$。

代码就不放了，实在需要代码的找我。

彩蛋：

![](https://cdn.luogu.com.cn/upload/image_hosting/gp621hfo.png)


![](https://cdn.luogu.com.cn/upload/image_hosting/hphuouv9.png)

---

## 作者：Mars_Dingdang (赞：4)

在 Analytic Combinatorics（分析组合学）一书的预言章中，引入了如下一个问题：

>Here is another more subtle problem. Assume that you are interested in permutations such that the first element is smaller than the second, the second is larger than the third, itself smaller than the fourth, and so on. The permutations go up and down and they are diversely known as up-and-down or zigzag permutations, the more dignified name being alternating permutations. Say that $n = 2m + 1$ is odd.

我们知道一个排列可以对应到一个大根笛卡尔树，其中每个节点的权值大于其左右儿子的权值，并且整棵树的中序遍历对应整个排列，如下所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/l4h98cvb.png)

考虑使用符号化方法刻画如下一棵树的构造方法：

1. 对于大小为 $1$ 的树，节点为 $1$；

2. 选择当前最大值作为根节点，然后有标号地递归构造左右子树。

即，$\mathcal F=\{1\}\cup (\mathcal F\star \max\star \mathcal F)$。根据书中关于 Order constraints 的论述，有 $\mathcal A=(\mathcal B^\square\star \mathcal C)$ 可以得到（$\square$ 表示要求 $\mathcal B$ 中的元素为最小，由于此处 $\min$ 和 $\max$ 等价，故使用之）：

$$A(z)=\int_0^z \partial_t(B(t))C(t) \text{d}t $$

其中 $\partial_t=\dfrac{\text d}{\text dt}$ 为微分算子。

其证明方法如下：

EGF 的乘积对应的卷积形式为

$$A_n=\sum_{k=1}^n \binom{n-1}{k-1}B_kC_{n-k}=\dfrac{1}{n}\sum_{k=0}^{n}\binom{n}{k}(kB_k)C_{n-k}$$

观察到 $kB_k$ 就是对应项求导后的系数，因此该式子吻合积分式。$\square$

那么，写出 zigzag permutation 组合类对应的生成函数表示

$$F(z)=z+\int_0^z F(t)^2 \text dt$$

两边对 $z$ 求导得到

$$F'(z)=1+F(z)^2$$

$$\dfrac{F'(z)}{1+F(z)^2}=1$$

两边对 $z$ 积分得到 $\arctan F(z)=z$，进一步计算得到 $F(z)=\tan z$。

与此同时我们考虑另一类问题：zigzag permutation 两边去掉一个，得到的长度为偶数的 zigzag permutation。我们观察这样的排列对应的笛卡尔树的形态，容易发现就是树中恰好有一个节点少了一个右儿子或者一个左儿子。我们记这样的组合类为 $\mathcal G$，类似地，$\mathcal G$ 可以看作将最大值放在根，然后一棵树是完整的 $\mathcal F$，另一棵树是 $\mathcal G$，即 $\mathcal G=\{\epsilon\}\cup(\max\star\mathcal G\star\mathcal F)$。写成生成函数的形式，有：

$$G(z)=1+\int_0^z F(t)G(t)\text dt$$

$$\dfrac{\text dG(z)}{\text dz}=G(z)\tan z, \dfrac{1}{G(z)}\text dG(z)=\tan z \text{d}z$$

两边积分，得到 $\ln |G(z)|=\ln |\sec z|+C$，进一步计算得到 $G(z)=\sec z$。

![](https://cdn.luogu.com.cn/upload/image_hosting/iefp98gm.png)

至此我们已经处理好这个用来引入的问题了。回到原问题，考虑 DP，很容易发现我们得到的实际上是对角线上 DP 值 $f_{n,n}$ 的生成函数，即 $f_{n,n}=[x^n](F(x)+G(x))$。然而本题中允许少数几个位置不为 zigzag，因此我们考虑对 $f_{i,j}$ 的第二维 $j$ 进行递推。

对于排列的 DP 通常可以考虑将当前值 $i$ 作为最大值插入。我们进行分类讨论。由于只要求最后得到的是 M 形状的排列（即 $\pi_1<\pi_2, \pi_n<\pi_{n-1}$），在插入前可能是 N 形（即 $\pi_1<\pi_2,\pi_n>\pi_{n-1}$），反 N 形（即 $\pi_1>\pi_2,\pi_n<\pi_{n-1}$）或者 W 形（即 $\pi_1>\pi_2,\pi_n>\pi_{n-1}$）。这一部分可以参考卡老师的题解。

然后我们发现上述的 DP 式子可以合并，比如 N 和反 N，M 和 W 显然具有很高的对称性；再比如 N 对应长度为偶数，M 对应长度为奇数，将奇数和偶数合并即可得到 $f_{i,j}=j\times f_{i-1,j}+2f_{i-1,j-1}+(i-j)f_{i-1,j-2}$。当然这个式子本身也有组合意义，只不过从 N 和 M 形状来考虑，其组合意义可能要分奇偶考虑，这个问题困扰了我一个上午依然不是很好解决。

然后我们就可以使用后面两项递推得到前面一项，用 NTT 求出对角线系数之后倒退即可。倒推的计算量为 $O(n-2k)=O(20)$。

总的时间复杂度为 $O(n\log n+20n)$。

更进一步的，其实这类问题还有更加一般的情形也可以解决。在 Analytic Combinatorics 一书的 Part C 中提出了使用多变量生成函数（Multivariate Generating Functions, MGF）解决此类问题的方法，感兴趣的同学们可以参考阅读。

---

