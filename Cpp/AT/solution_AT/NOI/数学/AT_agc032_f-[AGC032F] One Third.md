# [AGC032F] One Third

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc032/tasks/agc032_f

円形のピザがあります。 すぬけ君は、なるべくこのピザの $ 1/3 $ に近い分量食べたいです。

すぬけ君は、以下のようにピザを切って食べることにしました。

まず、すぬけ君はピザに $ N $ 回ナイフを入れて $ N $ 個のピースに分割します。 ナイフを入れると、ピザの中心とピザの周上の点を結ぶ線分に沿ってピザに切れ込みが入ります。 ただし、すぬけ君はピザを切るのがとても下手なので、線分の角度は一様ランダムであり、毎回独立であるものとします。

次に、すぬけ君は一個以上のいくつかの **連続する** ピースをなるべく合計量が $ 1/3 $ に近くなるように選んで食べます。 (合計量を $ x $ とすると、 $ |x\ -\ 1/3| $ が最小となるように連続するピースを選びます。)

このとき、 $ |x\ -\ 1/3| $ の期待値を求めてください。 この値は有理数となることが示せます。これを注記で述べるように mod $ 10^9\ +\ 7 $ で出力してください。

## 说明/提示

### 注記

有理数を出力する際は、まずその有理数を分数 $ \frac{y}{x} $ として表してください。ここで、$ x,\ y $ は整数であり、$ x $ は $ 10^9\ +\ 7 $ で割り切れてはなりません (この問題の制約下で、そのような表現は必ず可能です)。そして、$ xz\ \equiv\ y\ \pmod{10^9\ +\ 7} $ を満たすような $ 0 $ 以上 $ 10^9\ +\ 6 $ 以下の唯一の整数 $ z $ を出力してください。

### 制約

- $ 2\ \leq\ N\ \leq\ 10^6 $

### Sample Explanation 1

期待値は $ \frac{5}{36} $ です。

### Sample Explanation 2

期待値は $ \frac{11}{162} $ です。

## 样例 #1

### 输入

```
2```

### 输出

```
138888890```

## 样例 #2

### 输入

```
3```

### 输出

```
179012347```

## 样例 #3

### 输入

```
10```

### 输出

```
954859137```

## 样例 #4

### 输入

```
1000000```

### 输出

```
44679646```

# 题解

## 作者：关怀他人 (赞：20)

#### Lemma
>在$[0,1)$上随机取$n-1$个点，把线段分成了$n$段中所有段长度的最小值的期望是$\frac{1}{n^2}$

证明：设最短的一段长度为$x$，那么剩下的$n-1$段的长度都要大于等于$x$，考虑先将每条线段的长度减去$x$，于是就变成了在剩下的长度为$1-nx$的线段上随机取$n-1$个点，那么就有
$$
P(L_{min}\geq x)=(1-nx)^{n-1}
$$
于是
$$
\begin{aligned}
E(L_{min})&=\int_0^{\frac{1}{n}}P(L_{min}\geq x)dx\\
&=\int_0^{\frac{1}{n}}(1-nx)^{n-1}dx\\
&=-\frac{1}{n}\int_0^{\frac{1}{n}}(1-nx)^{n-1}d(1-nx)\\
&=-\frac{1}{n^2}(1-nx)^n\Big\lvert_0^{\frac{1}{n}}\\
&=\frac{1}{n^2}
\end{aligned}
$$
如果考虑次长段的期望，那么就是剩下的$1-nx$中最短的一段的期望，即
$$
\frac{1-nE(L_{min})}{(n-1)^2}+E(L_{min})=\frac{1}{n}(\frac{1}{n}+\frac{1}{n-1})
$$
于是可以归纳得出第$k$短的长度的期望为
$$
E(L_k)=\frac{1}{n}(\frac{1}{n}+\frac{1}{n-1}+\cdots +\frac{1}{n-k+1})
$$
#### Solution
首先可以转化一下题意，令其中某一条边为起点，顺时针每$\frac{2}{3}\pi$划分为一个区域，将三个区域中的线段分别染成红绿蓝三种颜色，然后把所有线段的夹角$\mod \frac{2}{3}\pi$之后都放到一个区间内，于是问题就变成了
>在$[0,\frac{2}{3}\pi)$中随机取$n-1$个点，然后将每个点随机染成红绿蓝三种颜色中的一种，求两端颜色不同的线段长度的最小值的期望

考虑枚举答案是第$k$小的线段，那么要求前$k-1$小的线段必须同色，根据容斥可以得出这样的概率为$\frac{1}{3^{k-1}}-\frac{1}{3^k}$，然后根据上面的**Lemma**不难得出答案为
$$
\begin{aligned}
ans &= \frac{1}{3}\sum_{i=1}^n(\frac{1}{3^{i-1}}-\frac{1}{3^i})E(L_i)\\
&=\frac{1}{3n}\sum_{i=1}^n(\frac{1}{3^{i-1}}-\frac{1}{3^i})\sum_{j=1}^i\frac{1}{n-j+1}\\
&=\frac{1}{3n}\sum_{j=1}^n\frac{1}{n-j+1}\sum_{i=j}^n(\frac{1}{3^{i-1}}-\frac{1}{3^i})\\
&=\frac{1}{n}\sum_{j=1}^n\frac{1}{3^j(n-j+1)}
\end{aligned}
$$
#### Code
```cpp
int n,ans;
int fac[MAXN],ifac[MAXN];

int main(){
    scanf("%d",&n);
    fac[0] = ifac[0] = 1;
    for(int i = 1;i <= n;i++)
        fac[i] = 1ll * fac[i - 1] * i % MOD;
    ifac[n] = Inv(fac[n]);
    for(int i = n - 1;i >= 1;i--)
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % MOD;
    int inv3 = Inv(3);
    for(int i = 1,tmp = inv3;i <= n;i++,tmp = 1ll * tmp * inv3 % MOD)
        addmod(ans,1ll * tmp * ifac[n - i + 1] % MOD * fac[n - i] % MOD);
    ans = 1ll * ans * ifac[n] % MOD * fac[n - 1] % MOD;
    printf("%d\n",ans);
    return 0;
}

---

## 作者：zzw4257 (赞：16)

这篇题解的目的是在于纠正和补充 @关怀他人 题解的一些内容

首先不加证明的给出以下引理:

在 $[0,1]$ 上随机撒 $n-1$ 点将区间划分为 $n$ 个段，其中的第 $k$ 小距离是
$$\boxed {E(L_{\min_k})=\frac{1}{n}\left(\sum_{i=0}^{k-1}\frac{1}{n-i}\right)}$$

证明就基于 $\displaystyle E(L_{\min})=\int_{0}^{x}E([L_{\min}\geqslant x])\mathrm dx$ 然后运用类似抽板的思想得到递推式即可

详细过程可以见 @关怀他人 题解

我们将第一条线的极角设为$0$ ,对极角 $[0,\frac{2}{3}\pi),[\frac{2}{3}\pi,\frac{4}{3}\pi),[\frac{4}{3}\pi,0)$ 的区域染上不同的颜色不妨设为RBG

设刚才的图为第一张图，然后造一张新图，让线染上**第一张图中所处区域颜色**并将其极角对 $\frac{2}{3}\pi$ 取模，也就是放到同一个 $1/3$ 圆周的相应位置

![](https://cdn.luogu.com.cn/upload/image_hosting/edhwbcju.png)

下面的讨论均只包含 $[0,\frac{2}{3}\pi\color{red}]$ 区域内的**含 $\frac{2}{3}\pi$ 处分界线**的 $n+1$ 条线段(分界线染 $[\frac{2}{3}\pi,\frac{4}{3}\pi)$ 的颜色)

(这里是我手误上下的染色不一样，下面 $[0,\frac{2}{3}\pi),[\frac{2}{3}\pi,\frac{4}{3}\pi),[\frac{4}{3}\pi,0)$ 的颜色分别是红,蓝，绿)

紧接着我们就可以说明所求转化为了该区域内异色线段的最小距离

分2类情况来证明

- 原本异色：很显然，本来该减掉的 $\frac{1}{3}\pi$ 就体现在转到同一个圆弧的转角差量中
- 原本同色
	- 是 $[0,\frac{2}{3}\pi),[\frac{2}{3}\pi,\frac{4}{3}\pi)$ 的颜色,也即与两个边界其中一个同
    ![](https://cdn.luogu.com.cn/upload/image_hosting/dawaz7z2.png)
    则会发现紫色即应有的贡献$<$橙色即靠近异色分界线造成的贡献
   - 是 $[\frac{4}{3}\pi,0)$
   ![](https://cdn.luogu.com.cn/upload/image_hosting/0hmpvc4z.png)
   与上文类似
   
因此这样我们即可完整的转化所求

>在 $\color{red}{[0,\frac{1}{3}]}$ 中随机撒 $\color{red}{n-1}$ 点(即真正的 $2\to n$ 号刀的"相对"位置)，再随机定色，钦定 $0,\frac{2}{3}\pi$ 处各额外有两个点(1号点和强制的边界)，颜色也随机但必须相异，求其中异色点对距离最小值


首先考虑至少 $i$ 个**指定的**(在本题中这个指定即对距离排序的前 $i$ 小)点对同色的概率为 $[i<n]\frac{1}{3^{{i}}}$ 因为我们钦定了两个边界异色

那么最小异色对由全局的第 $k$ 小对距离取到的概率为 $\frac{1}{3^{{k-1}}}-[k<n]\frac{1}{3^{{k}}}$

因此答案为

$$
ans=\frac{1}{3}\sum_{i=1}^{n}(\frac{1}{3^{{i-1}}}-[i<n]\frac{1}{3^{{i}}})E(L_{\min_i})=\sum_{i=1}^n\frac{1}{3^i(n-i+1)}
$$

(这一步中仿佛许多题解都神奇的列错了(多了个 $-\frac{1}{3^n}$ 这个不存在的项)依然得到了正确答案~~)



---

## 作者：qwaszx (赞：10)

第一步转换:标记一刀为红色，旋转 $\dfrac{\pi}{3}$ 后标记为绿色，再旋转 $\dfrac{\pi}{3}$ 后标记为蓝色，那么现在就是要求异色线之间角度的最小值的期望（这相当于把 $x+1/3$ 和 $x-1/3$ 都标记出来）.

用第一刀标记的三条线把圆切成等大的三份（左闭右开），那么每一刀生成的三条线各在其中一份中，由于对称性我们我们只要取其中一份来计算. 现在问题可以转换成，在一条长为 $\dfrac{1}{3}$ 的线段上均匀随机独立地撒 $n-1$ 个点，每个点随机染三种颜色之一，线段的两个端点的颜色已经固定为红色和蓝色，求异色点之间距离的最小值的期望. 显然最小值由相邻的两个点取到，所以只需要计算这些点切出来的 $n$　条线段的最小值的期望. 我们先忽略颜色的限制，考虑如何计算这个期望. 为了方便先设线段长度为 $1$，最后再乘上 $\dfrac{1}{3}$ 即可. 我们来计算概率分布 $P(X \geq x)$，那么我们把每条线段先抽掉 $x$ 长度，这样就变成在 $1-nx$ 长度的线段上均匀随机撒 $n-1$ 个点，即 $P(X\geq x)=(1-nx)^{n-1}$. 然后直接使用定义计算期望:

$$
\begin{aligned}
&\int_0^{1/n}p(X=x)x\ \mathrm{d}x\\
=&\int_0^{1/n}p(X=x)\int_0^x\ \mathrm{d}t\ \mathrm{d}x\\
=&\int_0^{1/n}\int_t^{1/n}p(X=x)\mathrm{d}x\ \mathrm{d}t\\
=&\int_0^{1/n}P(X\geq t)\mathrm{d}t\\
=&\int_0^{1/n}(1-nt)^{n-1}\ \mathrm{d}t\\
=&-\frac{1}{n}\int_{1}^0u^{n-1}\ \mathrm{d}u\\
=&\frac{1}{n^2}
\end{aligned}
$$

然后来考虑颜色的限制，这相当于最小的若干条线段中存在同色的. 我们可以枚举答案是第 $k$ 小的，然后用 $E(kth\min)$ 乘上这个概率 $\dfrac{1}{3^{k-1}}-\dfrac{1}{3^k}$. 于是现在我们需要计算 $E(kth\min)$. 我们可以用 $\min-\max$ 容斥计算 $E(kth\max)$:

$$
E(kth\max)=\sum_{\varnothing\subset T\subseteq S}(-1)^{|T|-k}\binom{|T|-1}{k-1}E(\min(T))
$$

考虑 $E(\min(T))$，显然它只和 $|T|$ 有关. 设 $|T|=t$，我们还是来计算 $P(X\geq x)$，现在它变成了 $(1-tx)^{n-1}$，那么我们容易得到

$$
E(\min(T))=\int_0^{1/k}(1-tx)^{n-1}\ \mathrm{d}x=\frac{1}{nt}
$$

代入计算:

$$
\begin{aligned}
E(kth\max)=&\sum_{\varnothing\subset T\subseteq S}(-1)^{|T|-k}\binom{|T|-1}{k-1}E(\min(T))\\
=&\sum_{t>0}\binom{n}{t}\binom{t-1}{k-1}(-1)^{t-k}\frac{1}{nt}\\
=&[u^k]\frac{1}{n}\sum_{t\geq 0}\binom{n}{t+1}\frac{1}{t+1}\sum_{j}u^j\binom{t}{j-1}(-1)^{t+1-j}\\
=&[u^k]\frac{1}{n}\sum_{t\geq 0}\binom{n}{t+1}\frac{1}{t+1}u(u-1)^t\\
=&[u^{k-1}]\frac{1}{n}\sum_{t\geq 0}\binom{n}{t+1}\int_0^1(x(u-1))^t\ \mathrm{d}x\\
=&[u^{k-1}]\frac{1}{n}\int_0^1\sum_{t\geq 0}\binom{n}{t+1}(x(u-1))^t\ \mathrm{d}x\\
=&[u^{k-1}]\frac{1}{n}\int_0^1\frac{(1+x(u-1))^n-1}{x(u-1)}\mathrm{d}x\\
=&[u^{k-1}]\frac{1}{n}\int_0^1\sum_{i=0}^{n-1}(1+x(u-1))^i\ \mathrm{d}x\\
=&[u^{k-1}]\frac{1}{n}\sum_{i=0}^{n-1}\frac{1}{u-1}\int_1^{u}x^i\ \mathrm{d}x\\
=&[u^{k-1}]\frac{1}{n}\sum_{i=1}^n\frac{u^i-1}{u-1}\frac{1}{i}\\
=&[u^{k-1}]\frac{1}{n}\sum_{i=1}^{n}\frac{1}{i}\sum_{j=0}^{i-1}u^j\\
=&\frac{1}{n}\sum_{i=k}^n\frac{1}{i}
\end{aligned}
$$

那么最终的答案就是

$$
\begin{aligned}
&\frac{1}{3}\sum_{i=1}^n(\frac{1}{3^{i-1}}-\frac{1}{3^i})E(ith\min)\\
=&\frac{1}{3}\sum_{i=1}^n(\frac{1}{3^{i-1}}-\frac{1}{3^i})\sum_{j=1}^i\frac{1}{n-j+1}\\
=&\frac{1}{3}\sum_{j=1}^n\frac{1}{n-j+1}\sum_{i=j}^n(\frac{1}{3^{i-1}}-\frac{1}{3^i})\\
=&\sum_{j=1}^n\frac{1}{3^j(n-j+1)}
\end{aligned}
$$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1050000,mod=1000000007,iv3=(mod+1)/3;
int inv[N],n;
int main()
{
    scanf("%d",&n);inv[1]=1;for(int i=2;i<=n;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    int pw=iv3,ans=0;
    for(int i=1;i<=n;i++)ans=(ans+1ll*pw*inv[n-i+1])%mod,pw=1ll*iv3*pw%mod;
    cout<<1ll*ans*inv[n]%mod<<endl;
}
```

---

## 作者：feecle6418 (赞：7)

画了两张图，可能会比较好理解。并且对其他题解含糊不清的地方做了解释。

首先要用到 [随机红包](https://www.luogu.com.cn/problem/P6130) 的结论，即 $n$ 个和为 $1$ 的数，第 $k$ 小值的期望是 $\dfrac 1n\sum\limits_{j=1}^k \dfrac 1{n-j+1}$。证明需要积分。

然后有一个神仙的转化，把切的每一刀染成红色，旋转 120° 染成绿色，旋转 -120° 染成蓝色，那么 **固定第一刀切的位置，取第一刀的红色、绿色之间的部分（包括端点），这部分里面异色刀间距离最小值就是答案。**

可以看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lh9p03t6.png)

把问题放在线段上，就是：有 $n-1$ 个点均匀随机撒在长度为 $\dfrac 13$ 的线段上，每个点随机染红绿蓝色，线段两端固定是一端红一端绿。求端点异色最短线段期望长度。

显然异色线段一定存在于两个相邻点之间。枚举异色线段是 $n$ 条线段中第 $K$ 长的的，这要求所有前 $K-1$ 短的线段两端颜色都相同，那么中间 $n-1$ 个点中，有 $n-1-(K-1)$ 个点颜色没有受限制。概率是 $\dfrac{3^{n-1-(K-1)}}{3^{n-1}}=3^{1-K}$；并且要求前 $K$ 短的线段线段两端颜色不都相同。综上，这种情况的概率是 $3^{1-K}-3^{-K}[K\ne n]$，因为第 $n$ 短的线段两端颜色一定不同。

所以答案是下式，容易变形至 $O(n)$。
$$
\dfrac 13\sum_{K=1}^n(3^{1-K}-3^{-K}[K\ne n])\dfrac 1n\sum_{i=1}^K \dfrac 1{n-i+1}
$$

---

## 作者：Arghariza (赞：5)

首先先证明几个引理。

- $\text{Lemma \#1}$：

> 长度为 $1$ 的线段上**随机**取 $n-1$ 个点，将其分成 $n$ 段，长度最短段的长度期望为 $\dfrac{1}{n^2}$。

证明：

我不知道能不能 $\text{Min-Max}$ 容斥，但有更简单的做法。

假设最小段长度为 $l_{\min}$，考虑枚举 $x$，计算 $x\le l_{\min}$ 的概率。

由于要求最小值 $\ge x$，所以可以先将所有区间长度减去 $x$，剩下的长度为 $1-nx$，由于取出 $n-1$ 个点，所以 $P(l_{\min}\ge x)=(1-nx)^{n-1}$，可以当作合法方案除以总方案来理解。

根据期望公式：

$$\begin{aligned}\mathbb E(l_{\min})&=\int_0^{\frac{1}{n}}P(l_{\min}\ge x)dx\\&=\int _{0}^{\frac{1}{n}}(1-nx)^{n-1}dx\end{aligned}$$

由于 $\dfrac{d(1-nx)}{dx}=-n$：

$$\begin{aligned}\mathbb E(l_{\min})&=\int _{0}^{\frac{1}{n}}(1-nx)^{n-1}dx\\&=-\frac{1}{n}\int_0^{\frac{1}{n}}(1-nx)^{n-1}d(1-nx)\\&=\frac{1}{n^2}\end{aligned}$$

证毕。

- $\text{Lemma \#2}$：

> 长度为 $1$ 的线段上**随机**取 $n-1$ 个点，将其分成 $n$ 段，长度第 $k$ 短段的长度期望为 $\dfrac{1}{n}\sum\limits_{i=1}^k\dfrac{1}{n-i+1}$。

手算发现 $\mathbb E(l_{\min_2})=\mathbb E(l_{\min})+\dfrac{1-n\mathbb E(l_{\min})}{(n-1)^2}=\dfrac{1}{n^2}+\dfrac{1}{n(n-1)}$，就是先减去最小值的长度，再在剩余的长度里面取最小值。

同理，$\mathbb E(l_{\min_3})=\mathbb E(l_{\min_2})+\dfrac{1-n\mathbb E(l_{\text{min}})-(n-1)\left(\mathbb E(l_{\text{min}_2})-\mathbb E(l_{\min})\right)}{(n-2)^2}=\dfrac{1}{n^2}+\dfrac{1}{n(n-1)}+\dfrac{1}{n(n-2)}$。


归纳可证。

知道了这个你就可以把[随机红包](https://www.luogu.com.cn/problem/P6130)切了。

- $\text{Solution}$

我们可以把披萨旋转一下，使得第一刀位于水平线上。（假如披萨是立着放的。）于是我们只需要考虑剩下 $n-1$ 刀。

然后我们把平面分成 $3$ 个区域，每个区域都是 $\dfrac{2\pi}{3}$ 的角度。考虑一个转换：

> 在一个长度为 $\dfrac{1}{3}$ 的线段中，随机撒 $n-1$ 个 $3$ 颜色随机的点，求两端颜色不同的段的长度的期望。

相当于把所有半径映射到一个扇形中。

我们钦定前 $k-1$ 短的段两端颜色相同，第 $k$ 短的段符合我们的条件。容斥一下，这个概率为 $\dfrac{1}{3^{k-1}}-\dfrac{1}{3^k}$，然后带入 $\text{Lemma \#2}$ 的结论再交换求和号即可得到答案。

$$\begin{aligned}\text{ans}&=\frac{1}{3}\sum\limits_{k=1}^n\left(\frac{1}{3^{k-1}}-\frac{1}{3^k}\right)\frac{1}{n}\sum\limits_{i=1}^k\frac{1}{n-i+1}\\&=\frac{1}{n}\sum\limits_{i=1}^n\frac{1}{3^i(n-i+1)}\end{aligned}$$

朴素 $O(n\log n)$ 计算即可。

[评测记录。](https://atcoder.jp/contests/agc032/submissions/38696218)

---

## 作者：liaiyang (赞：4)

题意可以转换为在长度为 $1$ 的线段上随机选 $n-1$ 个点，任意两端点长度最接近 $\frac 1 3$ 的期望。

$\mathcal{Lemma}\;1$:

在长度为 $1$ 的线段上随机戳 $n-1$ 个点，$n$ 段中最小值的期望为 $\frac 1 {n^2}$。

枚举最小段的值至少为 $x$，给每一段选择增量 $\Delta x\ge 0$，这相当于在增量组成的长 $1-nx$ 的线段上选出 $n-1$ 个点。
$$
\begin{aligned}
E(\operatorname{min})&=\int_{0}^\frac 1 nxP(\operatorname{min}=x)dx\\
&=\int_{0}^\frac 1 nP(\operatorname{min}\ge x)dx\\
&=\int_{0}^{\frac 1 n}(1-nx)^{n-1}dx\\
&=-\frac 1 n\int_0^{\frac 1 n}(1-nx)^{n-1}d(1-nx)\\
&=-\frac 1 n\frac {(1-nx)^n}n|_0^{\frac 1 n}\\
&=\frac 1 {n^2}
\end{aligned}
$$
$\mathcal{Lemma}\;2$:

在长度为 $1$ 的线段上随机戳 $n-1$ 个点，$n$ 段中 $k$ 小值的期望为 $\frac 1 n\sum_{i=1}^{k}\frac 1 {n-i+1}$。

考虑先取走前 $k-1$ 小值的期望之使用 $\mathcal{Lemma}\;1$ 求出增量最小值的期望。
$$
\begin{aligned}
E(x_k)&=\frac{1-\sum_{i=1}^{k-1}(n-i+1)(E(x_i)-E(x_{i-1}))}{(n-k+1)^2}+E(x_{k-1})\\
&=\frac{1-\sum_{i=1}^{k-1}(n-i+1)\frac 1 n\frac 1 {n-i+1}}{(n-k+1)^2}+\frac 1 n\sum_{i=1}^{k-1}\frac 1 {n-i+1}\\
&=\frac{1-\frac {k-1} n}{(n-k+1)^2}+\frac 1 n\sum_{i=1}^{k-1}\frac 1 {n-i+1}\\
&=\frac{1}{n(n-k+1)}+\frac 1 n\sum_{i=1}^{k-1}\frac 1 {n-i+1}\\
&=\frac 1 n\sum_{i=1}^k\frac 1 {n-i+1}
\end{aligned}
$$
到此，可以解决 [P6130 随机红包](https://www.luogu.com.cn/problem/P6130)。

对于这道题，我们考虑转化为在一条长 $\frac 1 3$ 的线段上随机取 $n-1$ 个可能取值为 $0/1/2$ 的点，线段的两端点异色，求相邻两异色点形成的区间长度最小值期望。

我们考虑对于画出的每一条半径顺时针旋转 $\frac {2\pi} 3$，$\frac{4\pi} 3$，并分别染色 $0/1/2$，再以某一条半径为边界把圆三等分，则对于每个扇形，内部有 $n-1$ 条边，且对所有相邻的异色半径，它们可以形成一组配对，且面积为 $|x-\frac1 3|$。

枚举第 $k$ 长的段满足，则前 $k-1$ 长的段必不满足，概率为前 $k-1$ 段不满足的概率减去前 $k$ 段不满足的概率，为 $\frac 1 {3^{k-1}}-\frac 1 {3^k}[k\not=n]$，所以答案为
$$
\begin{aligned}
ans&=\sum_{k=1}^n(\frac 1 {3^{k-1}}-\frac 1 {3^k}[k\not=n])\frac 1 n\sum_{i=1}^k\frac 1 {n-i+1}\\
&=\frac 1 n\sum_{i=1}^n\frac 1 {n-i+1}\sum_{k=i+1}^n(\frac 1 {3^{k-1}}-\frac 1 {3^k}[k\not=n])\\
&=\frac 1 n\sum_{i=1}^n\frac 1 {3^i(n-i+1)}
\end{aligned}
$$
预处理逆元，时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
// #pragma GCC optimize(1)
// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#define int long long
#define y0 Y0
#define y1 Y1
#define lc (now<<1)
#define rc (now<<1|1)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define mkp make_pair
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod)
#define rd read()
#define lowbit(x) ((x)&(-(x)))
#define abs(x) ((x)<0?-(x):(x))
#define submod(x,y) (((x-=y)<0)&&(x+=mod))
#define addmod(x,y) (((x+=y)>=mod)&&(x-=mod))
#define addval(x,y) (x+y>=mod?x+y-mod:x+y)
#define subval(x,y) (x-y<0?x-y+mod:x-y)
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define fflush() fwrite(obuf,1,O-obuf,stdout),O=obuf
char buf[(1<<21)+10],*p1=buf,*p2=buf,obuf[(1<<21)+10],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define putchar(x) (O-obuf<(1<<21)?*O++=(x):(fwrite(obuf,1,1<<21,stdout),O=obuf,*O++=(x)))
inline int read(int u=0, char c=getchar(), bool f=false){
    for(;!isdigit(c);c=getchar()) f|=c=='-';
    for(;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+(c^'0');
    return f?-u:u;
}
inline void read(string &s,char c=getchar()){
    for(;(c<'A'||c>'Z')&&(c<'a'||c>'z')&&(c<'0'||c>'9');c=getchar());s.clear();
    for(;(c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9');c=getchar()) s.push_back(c);
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar((x%10)^'0');
}
inline void wt(string s){for(char c:s) putchar(c);}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1,iinf=1e18;
const int mod=1e9+7,g=3,gi=332748118,seed=19260817;
const int N=1e6+10;
int n,ans,inv[N];
main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=rd,inv[1]=1;for(int i=2;i<=max(n,3);i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1,pw=inv[3];i<=n;i++,pw=pw*inv[3]%mod) ans=(ans+inv[n-i+1]*pw)%mod;wt(ans*inv[n]%mod,'\n');
    return fflush(),0;
}
```

---

## 作者：A6n6d6y6 (赞：3)

## 前言

在做题的时候发现一些题解的某些部分不够详细，需要结合其它题解才能明白过程。

本题解讲得比较详细，可能有不足之处，欢迎大家指出。

默认大家都会一点微分学和积分学知识，对连续概率有一定了解。

## 题意

把圆随机划分成 $n$ 个扇形，求其中连续若干块的面积与 $\dfrac{1}{3}$ 的差的绝对值的最小值的期望。

[传送门](https://www.luogu.com.cn/problem/AT_agc032_f)

## 思路

### 题意转化

首先这个角度与圆不太好处理，考虑转化：

随便以一刀为**水平线**，设其角度为 $0$，**逆时针**为**正方向**，圆周的角度为**单位** $3$。

对于每一刀，设其**角度**为 $\theta$，将 $\theta$ 这一刀染成**红色**，再在角度 $\theta-1$ 和 $\theta+1$ 处各切一刀，颜色分别染**绿色**和**蓝色**。

可以发现，任意**同色刀**所切的角度与 $1$ 的**差**可以转化为对应**异色刀**间的角度，所以原最小值等价于**异色刀间距离最小值**。

显然这个图形是对称的，所以只用**考虑**一个圆心角为 $1$ 的**扇形**就可以了。

如果只注意一个扇形，相当于每个点从红绿蓝三色中**等概率随机染色**，而角度可以转化为**数轴上的点**。

也就是说，把线段 $[0,1]$ **随机**分成 $n$ 份，将端点**随机染色**，$0$ 必为红色，$1$ 必为蓝色，求最短的端点**异色**线段的期望长度。

### 弱化情况

先从**没有限制**的情况考虑，不妨先求出把线段 $[0,1]$ 分成了 $n$ 段中长度的**最小值**的期望，设为 $L$。

注意到， $L$ 的**定义域** $[0,\dfrac{1}{n}]$ 是**连续**的，其对应**单点概率**恒为$0$，且相关函数在定义域外的区域为 $0$。

**钦定**最短的一段长度为 $x$，那么剩下的 $n$ 段的长度都要**不小于** $x$。

考虑先将每条线段的长度**减去** $x$，于是就变成了在**剩下的**长度为 $1−nx$ 的线段上随机取 $n−1$ 个点。

原来每个点的**值域**为 $[0,1]$，而**限制后**的值域为 $[0,1-nx]$，所以满足限制的**概率**为 $(1-nx)^{n-1}$。

因为这是**钦定**，没有保证有一段长度恰为 $x$，所以它在**概率意义**下为 $\mathrm{P}(L\ge x)$。

不难得到 CDF **累计分布函数** $\mathrm{F}_L(x)=\mathrm{P}(L\le x)=1-(1-nx)^{n-1}$。

那么它与**概率密度函数** $f_L$ 的关系就有：
$$
\mathrm{F}_L(x)=\int_{-\infty}^{x}f_L(t)\mathrm{d}t=\int_{0}^{x}f_L(t)\mathrm{d}t=(\int f_L)(x)\bigg|_0^{x}=(\int f_L)(x)
$$
所以 $f=\mathrm{F}'_L$，带入 $\mathrm{E}[L]$ 的**定义式**中：
$$
\begin{aligned}
\mathrm{E}[L]&=\int_{0}^{\frac{1}{n}}tf(t)\mathrm{d}t\\
&=\int_{0}^{\frac{1}{n}}t\mathrm{F}'_L(t)\mathrm{d}t\\
&=t\mathrm{F}_L(t)\bigg|_0^\frac{1}{n}-\int_{0}^{\frac{1}{n}}\mathrm{F}_L(t)\mathrm{d}t\\
\end{aligned}
$$
将 $\mathrm{F}_L(x)=1-(1-nx)^{n-1}$ 带入，有 $\mathrm{F}_L(0)=0$，$\mathrm{F}_L(\frac{1}{n})=1$，那么：
$$
\begin{aligned}
\mathrm{E}[L]&=t\mathrm{F}_L(t)\bigg|_0^\frac{1}{n}-\int_{0}^{\frac{1}{n}}\mathrm{F}_L(t)\mathrm{d}t\\
&=\dfrac{1}{n}-\int_{0}^{\frac{1}{n}}1-(1-nt)^{n-1}\mathrm{d}t\\
&=\dfrac{1}{n}-\dfrac{1}{n}+\int_{0}^{\frac{1}{n}}(1-nt)^{n-1}\mathrm{d}t\\
&=\int_{0}^{\frac{1}{n}}(1-nt)^{n-1}\mathrm{d}t\\
\end{aligned}
$$
因为 $\dfrac{\mathrm{d}t}{\mathrm{d}(1-nt)}=-\dfrac{1}{n}$，**换元**并**更换上下界**：
$$
\begin{aligned}
\mathrm{E}[L]&=\int_{0}^{\frac{1}{n}}(1-nt)^{n-1}\mathrm{d}t\\
&=-\dfrac{1}{n}\int_{1}^{0}t^{n-1}\mathrm{d}t\\
&=-\dfrac{1}{n}\Bigg(\dfrac{t^n}{n}\bigg|_1^0\Bigg)\\
&=\dfrac{1}{n^2}
\end{aligned}
$$
综上，$\mathrm{E}(L)=\dfrac{1}{n^2}$。

我们还需要求出第 $k$ 小的期望，设为 $\mathrm{E}(L_k)$，**特别地**，$\mathrm{E}(L_0)=0$。

考虑**相邻**两项的**差**：
$$
\mathrm{E}[L_{i+1}]-\mathrm{E}[L_i]=\dfrac{1-\sum_{j=0}^{i-1}(n-j)(\mathrm{E}[L_{j+1}]-\mathrm{E}[L_{j}])}{(n-i)^2}
$$
这个式子的意义就是将前面的长度**一起减掉**，**剩下** $n-i$ 个线段中最小值的期望。

发现有一个**递归**的形式，用**数学归纳法**可以证明 $\mathrm{E}[L_{i+1}]-\mathrm{E}[L_i]=\dfrac{1}{n(n-i)}$，下证：

- 对于 $\mathrm{E[L_2]-\mathrm{E}(L_1)}=\dfrac{1-n\mathrm{E}(L_1)}{(n-1)^2}=\dfrac{1}{n(n-1)}$，显然成立。

- 假设对于 $k\le i$，$\mathrm{E}[L_{k+1}]-\mathrm{E}[L_k]=\dfrac{1}{n(n-k)}$ 都成立。

- 对于$\mathrm{E}[L_{i+1}]-\mathrm{E}[L_i]$，可以直接**带入**前面的结论：
  $$
  \begin{aligned}
  \mathrm{E}[L_{i+1}]-\mathrm{E}[L_i]&=\dfrac{1-\sum_{j=0}^{i-1}(n-j)(\mathrm{E}[L_{j+1}]-\mathrm{E}[L_{j}])}{(n-i)^2}\\
  &=\dfrac{1-\sum_{j=0}^{i-1}(n-j)(\dfrac{1}{n(n-j)})}{(n-i)^2}\\
  &=\dfrac{1-\sum_{j=0}^{i-1}\dfrac{1}{n}}{(n-i)^2}\\
  &=\dfrac{1-\dfrac{i}{n}}{(n-i)^2}\\
  &=\dfrac{1}{n(n-i)}\\
  \end{aligned}
  $$

这样，我们证明了 $\mathrm{E}[L_{i+1}]-\mathrm{E}[L_i]=\dfrac{1}{n(n-i)}$。

### 最终答案

最后把限制加回来，**枚举**前面有 $k$ 条线段比它短，即它是第 $k+1$ 短的。

**钦定**前 $k$ 条线段**都同色**的概率显然为 $\dfrac{1}{3^{k}}$，此时期望**加上** $\mathrm{E}[L_{k+1}]-\mathrm{E}[L_k]$。

综上，答案即为：
$$
\sum_{k=0}^{n-1}\dfrac{(\mathrm{E}[L_{k+1}]-\mathrm{E}[L_{k}])}{3^{k}}=\sum_{k=0}^{n-1}\dfrac{1}{3^{k}n(n-k)}
$$

由于是从 $[0,3]$ 中选 $[0,1]$，所以还需要乘上 $\dfrac{1}{3}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int ksm(int a,int b){
	int c=1;
	while(b){
		if(b&1)c=c*a%mod;
		a=a*a%mod;b>>=1;
	}
	return c;
}
signed main(){
	int n,ans=0;cin>>n;
	for(int k=0;k<=n-1;k++)
		ans=(ans+ksm(ksm(3,k)*n%mod*(n-k)%mod,mod-2))%mod;
	cout<<ans*ksm(3,mod-2)%mod;
	return 0;
} 
```

---

## 作者：xht (赞：3)

## [One Third](https://atcoder.jp/contests/agc032/tasks/agc032_f)

### 题意

- 有一个披萨，将它在 $n$ 条随机的半径切一刀。
- 你会选择若干块相邻的披萨饼，使其总和最接近 $\frac 13$。
- 求选择的披萨饼大小与 $\frac 13$ 之差的绝对值的期望值。
- $n \le 10^6$，答案对 $10^9+7$ 取模。

### 题解

先转化，对于每一刀，先将其染成红色，再在 $+ \frac 13$ 和 $-\frac 13$ 各切一刀，分别染蓝色和绿色。

将每一刀 $\bmod \frac 13$，于是问题等价于有一条长 $\frac 13$ 的线段，$0$ 处为红，$\frac 13$ 处为蓝，中间还有 $n-1$ 个位置和颜色随机的点，将整个线段分成了 $n$ 段，求最短的两端颜色不同的线段长度的期望。

把所有线段拿出来排序，考虑答案为第 $k$ 短的线段，经过积分可以得到为 $\sum_{i=1}^{k} \frac{1}{3n(n+1-i)}$。

考虑最短的，答案为 $\frac{1}{3n^2}$，如果同色考虑次短的，要加上 $\frac{1}{3n(n-1)}$ 乘上同色的概率 $\frac 13$，以此类推，答案为 $\sum_{k=1}^{n} \frac{1}{3^kn(n+1-k)}$。

时间复杂度 $\mathcal O(n)$。

### 代码

```cpp
int n;
modint ans, a = 1;

int main() {
	rd(n), init(max(n, 3));
	for (int k = 1; k <= n; k++) ans += (a *= v[3]) * v[n+1-k];
	print(ans * v[n]);
	return 0;
}
```

---

## 作者：moongazer (赞：2)

# [AGC032F] One Third 题解

## 分析

考虑转化，可以转化为在 $\left[0,\frac{1}{3}\right]$ 上等概率随机分成 $n$ 份，并从 $1,2,3$ 中等概率随机赋上一种颜色，$0$ 初始颜色已为 $1$，$\frac{1}{3}$ 初始颜色已为 $2$，求最短的两端点颜色不同的线段的期望长度

先从没有限制的长度为 $1$ 的线段开始考虑，不妨设其互补累积分布函数 $F_{L_1}(x)=P(L>x)=(1-nx)^{n-1}$ 可得其期望：

$$\begin{aligned}\operatorname{E}[L_1] & =\int_0^\frac{1}{n}x\times\left[-(F_{L_1}(x))^\prime\right]dx\\
& =\int_0^\frac{1}{n}F_{L_1}(x)dx \text{ (分部积分) }     \\
& =\int_0^\frac{1}{n}(1-nx)^{n-1}dx                       \\
& =\frac{1}{n}\int_0^1\left(\frac{n-nx}{n}\right)^{n-1}dx \\
& =\frac{1}{n}\int_0^1\left(1-x\right)^{n-1}dx            \\
& =\frac{1}{n}\int_0^1x^{n-1}dx \text{ (换元) }           \\
& =\frac{1}{n^2}\end{aligned}$$

考虑次小值，削除 $n$ 段最小值后的最小值再加上最小值：$\operatorname{E}[L_2]=\frac{1-n\operatorname{E}[L_1]}{(n-1)^2}+\operatorname{E}[L_1]$
变形得 $\operatorname{E}[L_2]-\operatorname{E}[L_1]=\frac{1}{n(n-1)}$，归纳得 $\operatorname{E}[L_{k+1}]-\operatorname{E}[L_k]=\frac{1}{n(n-k)}$
考虑乘上至少前 $i$ 条线段都不满足条件的概率 $\frac{1}{3^i}$ 答案即为 $\frac{1}{n}\sum\limits_{i=1}^n\frac{1}{3^i(n-i+1)}$

## 代码

```cpp
constexpr int N = 1000005;
constexpr int Mod = 1000000007;

int pow(int a, int b, int m);

int inv[N];
int n;

int main() {
  read(n);
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = (Mod - Mod / i) * 1ll * inv[Mod % i] % Mod;
  }
  int ans = 0;
  int iv3 = pow(3, Mod - 2, Mod);
  for (int i = 1, p3 = inv[n]; i <= n; ++i) {
    p3 = p3 * 1ll * iv3 % Mod;
    ans = (ans + p3 * 1ll * inv[n - i + 1] % Mod) % Mod;
  }
  write(ans), EL;
  return 0;
}

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
```

---

## 作者：littlez_meow (赞：0)

很厉害的积分题。

[题目指路](https://atcoder.jp/contests/agc032/tasks/agc032_f)。

### 题意

把圆随机划分成 $n$ 个扇形，求其中连续若干块的面积与 $\dfrac 1 3$ 的差的绝对值的最小值的期望。

### 思路

考虑一条线段随机分成 $n$ 段最小段长度的期望。

把每段全部减掉 $x$，再随机分成 $n$ 段，得到的就是最小段长度 $L$ 大于等于 $x$ 的概率，根据几何概型，即 $P(L\ge x)=(1-nx)^{n-1}$。

再求期望，连续随机变量用积分，有：

$$E(L)=\int_{0}^{\frac 1 n}P(L\ge x)\mathrm{d}x$$

带入式子：

$$E(L)=\int_{0}^{\frac 1 n}(1-nx)^{n-1}\mathrm{d}x$$

设 $t=1-nx$，则 $x=\dfrac {1-t} n,\mathrm{d}x=-\dfrac 1 n\mathrm{d}t$，换元得：

$$E(L)=-\dfrac 1 n\int_{1}^{0}t^{n-1}\mathrm{d}t$$

多项式函数积分：

$$E(L)=-\dfrac 1 {n^2}\left(0^n-1^n\right)$$

得到结果：

$$E(L)=\dfrac 1 {n^2}$$

再考虑第二小的，是 $1-nE(L)$ 中最小段，为 $\dfrac 1 n(\dfrac 1 n+\dfrac 1 {n-1})$。

归纳可得第 $k$ 小期望长度为 $\dfrac 1 n\sum\limits_{i=0}^{k-1}\dfrac 1 {n-i}$。

一个很漂亮的结论。

然后转化题目，把切的 $n$ 刀染成红色，旋转 $120^\circ$ 染成蓝色，再转 $120^\circ$ 染成绿色。这时，答案为第一个 $120^\circ$ 中两半径异色的角度。

映射到线段上，即为在长为 $\dfrac 1 3$ 的线段上随机撒 $n-1$ 个点，每随机是红绿蓝三种颜色，线段开头为红，结尾为绿，求两端异色线段长度最小值的期望。

考虑枚举第 $k$ 长的段满足，则前 $k-1$ 长的必不满足，概率为 $\dfrac 1 {3^{k-1}}$，再减掉第 $k$ 长不满足，不过 $k=n$ 时不用减，得到最后概率 $\dfrac 1 {3^{k-1}}-\dfrac 1 {3^k}[k\neq n]$。

知道概率期望也好求了。为下式：

$$\sum\limits_{k=1}^n(\dfrac 1 {3^{k-1}}-\dfrac 1 {3^k}[k\neq n])\dfrac 1 n\sum\limits_{i=0}^{k-1}\dfrac 1 {n-i}$$

交换求和号：

$$\dfrac 1 n\sum\limits_{i=0}^{n-1}\dfrac 1 {n-i}\sum\limits_{k=i+1}^n(\dfrac 1 {3^{k-1}}-\dfrac 1 {3^k}[k\neq n])$$

裂项相消：

$$\dfrac 1 n\sum\limits_{i=0}^{n-1}\dfrac 1 {n-i}\dfrac 1 {3^{i+1}}$$

调整一下上下限：

$$\dfrac 1 n\sum\limits_{i=1}^{n}\dfrac 1 {3^i(n-i+1)}$$

时间复杂度 $O(n\log n)$，线性预处理逆元可以到 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i) 
#define ll long long
using namespace std;
const int MOD=1e9+7,INV3=333333336;
inline ll qpow(ll base,int expo){
	ll res(1);
	while(expo){
		(expo&1)&&(res=res*base%MOD);
		base=base*base%MOD,expo>>=1;
	}
	return res;
}
int n;
int inv[1000001];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	inv[1]=1;
	F(i,2,n) inv[i]=MOD-MOD/i*1ll*inv[MOD%i]%MOD;
	ll qwq=INV3;
	int ans(0);
	F(i,1,n) ans=(ans+inv[n-i+1]*qwq)%MOD,qwq=qwq*INV3%MOD;
	cout<<ans*qpow(n,MOD-2)%MOD;
	return 0;
}
```

---

## 作者：Leasier (赞：0)

首先是一个神仙的转化：

- 以切出来的某一刀为其中一条轴，把圆三等分。
- 将三个区域内的每一刀分别染成三种颜色。
- 对每一刀，将其角度 $\bmod \ 120 \degree$ 后放到一个 $120 \degree$ 的扇形中。
- 则我们要求的就是此时**异色**两刀间占比差的最小值的期望。

首先不考虑颜色，直接将这个扇形切 $n - 1$ 刀变成 $n$ 份，然后再给每一刀染色。

考虑枚举所求为第 $k$ 小的角度差，则前 $k - 1$ 小不合法而第 $k$ 小合法的概率为 $\frac{1}{3^{k - 1}} - \frac{1}{3^k}$。

接下来考虑第 $k$ 小的占比差的期望，我们用 $L(k)$ 表示答案。

首先有 $L(1) = \displaystyle\int_0^{\frac{1}{n}} (1 - nx)^n dx = \frac{1}{n} \displaystyle\int_0^1 x^n dx = \frac{1}{n^2}$。

我们尝试用 $L(k - 1)$ 推出 $L(k)$，根据期望的线性性有 $L(k) = L(k - 1) + \dfrac{1 - \displaystyle\sum_{i = 1}^{k - 1} L(i)}{(n - k + 1)^2}$。

进而可归纳得 $L(k) = \dfrac{1}{n}(\dfrac{1}{n} + \dfrac{1}{n - 1} + \cdots + \dfrac{1}{n - k + 1})$。

然后不难化简原式，接下来线性求逆即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

const int mod = 1e9 + 7;
ll inv[2000007], power[1000007];

inline void init(int n){
	inv[0] = inv[1] = 1;
	for (register int i = 2; i <= n; i++){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}
	power[0] = 1;
	for (register int i = 1; i <= n; i++){
		power[i] = power[i - 1] * inv[3] % mod;
	}
}

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int n;
	ll ans = 0;
	scanf("%d", &n);
	init(max(n, 3));
	for (register int i = 1; i <= n; i++){
		ans = (ans + inv[n - i + 1] * power[i] % mod) % mod;
	}
	printf("%lld", ans * inv[n] % mod);
	return 0;
}
```

---

