# 「MCOI-Zero / AC6-M14」Gracemeria Patrol

## 题目背景

「Talisman，一会你能不能和 Avalanche 一起出去而不是我？」

「我今晚想一个人静静。」

「我的妻女都死了。   
　刚刚确认的……」
 
 「我保护了我的国家，   
　但我却守护不了我的家庭。」
 
  「什么样的王牌   
　连自己的家庭都保护不了？」
 
 「Monica……   
　还有 Jessica……」
 
**「How could I let this happen！！」**

 「这个任务结束之后，   
　我将离开空军。」
 
  「我受够了。   
　我没有继续飞行的理由了。」
 
 ……

「一个不明物体正在高速飞行   
　在东北方。」

「这是战机？在这个时候？！」

「在雷达上确认未知物体，   
　这不是战机，它的速度太快了！」

「未知物体在雷达上消失了。   
　等一下……」

「一些物体在相同的方向上飞行。我认为这是……」

「我看到了，这些是导弹！」

「Ghost Eye，   
　我们遭到巡航导弹袭击了！」

「全机，拦截那些巡航导弹！   
　保护我们的城市！」

……

「资料检查……   
　增援的隐形飞机正在接近。」

「这些人不懂得放弃吗？」

『我们为了你而回来了，Emmeria！』

「这些人到底是怎么了？还觉得死的人不够多吗？！」

$$_{{\frac{\large\text{ACE COMBAT }\Large6}{\tiny{\text{F i r e s\quad O f\quad L i b e r a t i o n}}}}}\\ \text{Mission 14} \\\Large\text{Gracemeria Patrol}\\\tiny -\textit{ City Lights }-$$

![](https://cdn.luogu.com.cn/upload/image_hosting/g0d60mgz.png)

## 题目描述

给定一个 $n\times m$ 的 01 矩阵，每一次操作可以改变一个位置以及其上面、左边、右边的值。如果原值是 $0$，则改变之后变成 $1$；否则变成 $0$。

例如下面矩阵在改变中括号表明的位置之后的形态：

$$\begin{bmatrix}0&1&0&1&1\\1&0&[0]&1&0\\0&0&0&0&1\end{bmatrix}\rightarrow \begin{bmatrix}0&1&1&1&1\\1&1&1&0&0\\0&0&0&0&1\end{bmatrix}$$

**特别的，如果操作点在边界上，那么仅改变未超出边界的部分。**

现给定 $q$ 组询问，每组询问一个区间 $[l,r]$ 和一个常数 $k$，请你对行号在 $l,r$ 内的 01 子矩阵求出通过选出一些位置进行一次操作使其变为全 $0$ 的方案中，第 $k$ 行被操作了几次。

特别的，如果没有或者有多种选择操作位置的方法，输出 $-1$。

询问之间相互独立。

## 说明/提示

- Subtask 1（10 pts）：$n,m\leq 3,q\leq 10$。
- Subtask 2（20 pts）：$n,m,q\leq 10$。
- Subtask 3（20 pts）：$n,q\leq 50,m\leq 10$。
- Subtask 4（20 pts）：$n,q\leq 10^4,m\leq 10$。
- Subtask 5（30 pts）：无特殊限制。

对于 $100\%$ 的数据，满足 $1\leq n\leq 5\times 10^4$，$1\leq m\leq 50$，$1\leq q\leq 5\times 10^5$，$1\leq l\leq k\leq r\leq n$。

idea：Sol1，solution：Sol1 & ethan\_zhou，code：Sol1，data：Sol1

---

 「Talisman……」

 「一个天使不会交出它的翅膀除非   
　跳完最后一支舞，对不对？」

## 样例 #1

### 输入

```
10 4 2
1010
0110
0101
0000
1011
0111
1110
1011
0001
1100
1 10 6
2 5 3```

### 输出

```
2
2```

# 题解

## 作者：hy233 (赞：6)

如果确定了第一行的操作，那么其他行的操作也确定了。因为若操作了前 $i$ 行，第 $i+1$ 行的位置能操作当且仅当其正上方为 $1$。

我们不妨用广义矩阵刻画这一转移：设 $\boldsymbol{a_i}$ 为第 $i$ 行的数所构成的向量，$\boldsymbol{f_i}$ 为修改完前 $i$ 行之后第 $i$ 行构成的向量。令 $\boldsymbol A=\begin{bmatrix}  
  1 & 1 & 0 & 0 & \cdots \\  
  1 & 1 & 1 & 0 & \cdots \\  
  0 & 1 & 1 & 1 & \cdots \\  
  \vdots & \vdots & \vdots & \vdots & \ddots \\  
\end{bmatrix}$，则 $\boldsymbol{f_i=f_{i-1}A\oplus a_i}$。其中 $\oplus$ 为异或。

所以 $\boldsymbol{f_n=((f_1A\oplus a_2)A\oplus a_3\cdots)A\oplus a_n}$，第 $n$ 行没有下一行给他消了，所以 $\boldsymbol{f_n=0}$。化简把 $\boldsymbol{f_1}$ 提出可得：

$$\boldsymbol{f_1A^{n-1}=\sum_{i=2}^na_iA^{n-i}}$$

右边显然可以预处理，如果 $\boldsymbol{A^{-1}}$ 存在那么移到右边去就结束了。打表发现 $\boldsymbol{A^{-1}}$ 不存在当且仅当 $m \equiv 2 \pmod 3$。

>Proof：考虑方程 $\boldsymbol{xA=v}$：
>$$\boldsymbol{\exist x_1\ne x_2,x_1A=x_2A=v\Leftrightarrow (x_1-x_2)A=0\Leftrightarrow \exist u\ne 0,uA=0 }$$
> 如果存在 $\boldsymbol{uA=0}$，那么 $\boldsymbol{f_1}$  就有多个解，不符合条件。尝试构造这样的 $\boldsymbol{u}$，上式等价于：


$$\left\{\begin{matrix} 
  u_1\oplus u_2=0 \\  
  u_1\oplus u_2\oplus u_3=0 \\  
\cdots\\
u_{m-2}\oplus u_{m-1}\oplus u_m=0\\
u_{m-1}\oplus u_m=0
\end{matrix}\right.$$



>若 $u_1=u_2=0$，则$\boldsymbol{u=0}$。
>
>否则 $u_1=u_2=1$，$\boldsymbol{u}=(1,1,0,1,1,0,\cdots)$，当且仅当 $m \equiv 2 \pmod 3$ 时满足 $u_{m-1}\oplus u_m=0$。
>
> 所以当 $m \equiv 2 \pmod 3$ 时 $\boldsymbol{xA=v}$ 有多解，反之则有唯一解。
> 归纳可以得到 $\forall k,\boldsymbol{xA^k=v}$ 有着同样的性质。

所以区间询问时，当  $m \equiv 2 \pmod 3$ 时我们输出 $-1$，否则直接解出 $\boldsymbol{f_l=(\sum_{i=l+1}^ra_iA^{r-i})A^{-(r-l)}}$。验证一下 $\boldsymbol{a_l}$ 是否可以唯一得到 $\boldsymbol{f_l}$ 即可。$k=l$ 时，答案为 $\boldsymbol{a_l\rightarrow f_l}$ 需要的操作次数，反之即为
$\boldsymbol{f_{k-1}}$ 中 $1$ 的个数。

关于数值计算，预处理 $\boldsymbol{A^k},k\in [-n,n]$，$\boldsymbol{\sum_{i=l+1}^ra_iA^{r-i}}$ 类似的东西可以差分计算。注意到 $m\le 50$，用 `ull` 压一下可以去掉一个 $m$ ，复杂度 $O(nm^2+qm)$。

---

## 作者：Sol1 (赞：6)

~~idea 来自 emacs 的 5x5~~

不难发现当第一行的操作确定之后，所有位置的操作就都确定了：因为第三行的操作无法影响到第一行，所以第二行的操作必须把第一行翻为全 $0$，余下的行同理。

设 $F(x)=\left(x\oplus 2x\oplus \left\lfloor\dfrac{x}{2}\right\rfloor\right)\bmod 2^m$。

则如果第 $i$ 行的操作方式是 $x_i$ 的二进制表示，第 $i$ 行的原状态是 $a_i$ 的二进制表示，则有：

$$F(x_i)\oplus a_i=x_{i+1}$$

发现本质上是求一个函数方程的解：

$$F(F(F\cdots F(F(x_l)\oplus a_l)\oplus a_{l+1}\cdots)\oplus a_{r-1})\oplus a_r=0$$

又观察到 $F$ 满足 $F(x\oplus y)=F(x)\oplus F(y)$，所以上述方程可以拆开成：

$$F^{r-l+1}(x_l)=F^{r-l}(a_l)\oplus F^{r-l-1}(a_{l+1})\oplus\cdots\oplus F(a_{r-1})\oplus a_r$$

RHS 是一个定值，不妨假设我们可以求出它的值。

对于任意 $k\in [0,2^m-1]$，$F(x)=k$ 当且仅当 $F(x)=0$ 有唯一解时有唯一解，因为若存在 $K$ 使得 $F(K)=0$，则若 $F(x)=k$，则必然 $F(K\oplus x)=F(K)\oplus F(x)=F(x)=k$。反之，如果存在 $F(x_1)=F(x_2)=k$，则 $F(x_1\oplus x_2)=0$。

可以证明 $F$ 满足：**$F(x)=0$ 当且仅当 $m\not\equiv 2\pmod 3$ 时有唯一解。**

---

证：设 $x=(\overline{d_{m-1}d_{m-2}d_{m-3}\cdots d_1d_0})_2$。

则 $F(x)=0$ 等价于方程组：

$$\begin{cases}d_0\oplus d_1=0\quad (0)\\d_0\oplus d_1\oplus d_2=0\quad (1)\\d_1\oplus d_2\oplus d_3=0\quad (2)\\\cdots\\d_{m-3}\oplus d_{m-2}\oplus d_{m-1}=0\quad (m-2)\\ d_{m-2}\oplus d_{m-1}=0\quad (m-1)\end{cases}$$

由 $(0)$ 得 $d_0=d_1=0$ 或 $d_0=d_1=1$。

如果 $d_0=d_1=0$：

假设 $d_i=d_{i+1}=0$，那么由 $(i+1)$，必然有 $d_{i+2}=0$。

归纳得到 $\forall i\in [0,m-1],d_{i}=0$，即 $x=0$。

如果 $d_0=d_1=1$：

由 $(1)$ 得 $d_2=0$。

现假设 $d_{3k}=1,d_{3k+1}=1,d_{3k+2}=0$。

由 $(3k+2)$ 得 $d_{3k+3}=1$，由 $(3k+3)$ 得 $d_{3k+4}=1$，由 $(3k+4)$ 得 $d_{3k+5}=0$。

而方程 $(m-1)$ 要求 $d_{m-2}=d_{m-1}$，显然只在 $m=3k+2$ 时满足条件。

综上，原命题得证。

---

所以当 $m\not\equiv 2\pmod 3$ 时，则 $F$ 必然是一个 $[0,2^m-1]$ 的排列；否则，$F(x)=k$ 必然没有唯一解。

归纳易得对于任意 $k\in \mathbb N^+$，$F^k$ 也具有上述所有性质。

于是对于 $m\equiv 2\pmod 3$，对所有询问输出 $-1$ 即可。

对于 $m\not\equiv 2\pmod 3$，问题转变为快速求出 $F^i(x)$，其中 $0\leq x<2^{m}$，$-n\leq i\leq n$。

---

下证当 $m\not\equiv 2\pmod 3$ 时，$F^i(x)\oplus F^i(y)=F^i(x\oplus y)$，其中 $i\in \mathbb Z$，$0\leq x,y<2^m$。

已知 $F(x)\oplus F(y)=F(x\oplus y)$，先考虑证明 $F^{-1}(x)\oplus F^{-1}(y)=F^{-1}(x\oplus y)$。

考虑到 $F^{-1}(F(x)\oplus F(y))=F^{-1}(F(x\oplus y))=x\oplus y=F^{-1}(F(x))\oplus F^{-1}(F(y))$，又因为 $F(x)$ 可以取到 $[0,2^m)$ 的所有值，故 $F^{-1}(x)\oplus F^{-1}(y)=F^{-1}(x\oplus y)$。

再考虑归纳，假设 $F^n(x)\oplus F^n(y)=F^n(x\oplus y)$ 成立（$n=\pm1$ 时已证明为成立），则：

$$F^{n+1}(x)\oplus F^{n+1}(y)=F(F^n(x))\oplus F(F^n(y))=F(F^n(x)\oplus F^n(y))=F(F^n(x\oplus y))=F^{n+1}(x\oplus y)$$

同理可证 $F^{n-1}(x)\oplus F^{n-1}(y)=F^{n-1}(x\oplus y)$。从而原命题得证。

---

那么为了求出 $F^i(x)$，可以利用该性质，仅预处理 $F^i(2^x)$，然后就可以对 $x$ 二进制分解后 $O(m)$ 求出 $F^i(x)$。

由于现在可以简单求出 $F^{-i}(x)$，所以那个方程的等号右边的部分可以通过类似区间哈希值的差分方法来求。

这样就可以做到 $O(nm^2+qm)$，可以通过。

---

## 作者：流水行船CCD (赞：1)

[更好的阅读体验（慎点）](https://cdn.luogu.com.cn/upload/image_hosting/lnv7hi2w.png)。

感谢 hy233 大佬的题解，用线性代数来解题真的是一种不错的思路！本文更多的是对其中一些模糊地方（如定义，式子推导）的补充说明。

其实用线性代数做法是不需要 hy233 和 Sol1 两位大佬题解中提到的 $m$ 同余的神秘结论的，算是降低了很多思维难度。

## 算法一 

我会爆搜！

时间复杂度：$\mathcal{O}(qnm2^{nm})$。期望得分：$10$~$30$ 分。

## 算法二

我会状压！

设 $f_i(S)$ 表示考虑到前 $i$ 行，$[l,i-1]$ 行已经被消成全 $0$，第 $i$ 行操作了 $S$ 中的位置的方案数。

- **观察一**：如果第 $i-1$ 行的操作位置 $S'$ 确定，那当前行的操作位置 $S$ 也确定。
- 证明：因为每一个当前行的操作点对 $i-1$ 行的影响效果就是把 $i-1$ 行中和它同一列的数取反，因此上一行操作完后仍为 $1$ 的列就是当前行需要操作的列。

因此转移可以做到 $\mathcal{O}(1)$，最后判断是否存在 $f_r(S)=1$，倒推回去即可。

时间复杂度：$\mathcal{O}(qn2^m)$。期望得分：$50$ 分。

## 算法三

我会线性代数！

为了方便，在这里令 $l=1,r=n$。

由**观察一**，不难发现我们仅需要确定第 $1$ 行的操作就可以确定所有的操作。

类比线性基的思想，将第 $i$ 行原本的数表示为行向量 $\mathbf{a}_i = \begin{bmatrix}
 o_1 & o_2 & \cdots & o_m
\end{bmatrix}$。同理，可以令第 $i$ 行的操作点为行向量 $\mathbf{S}_i$，前 $i$ 行操作完后第 $i$ 行的数为行向量 $\mathbf{F}_i$。

为了方便，约定下面所提到的矩阵中的值均为 $0/1$。

定义两个矩阵的 $+$ 运算是：

$$\mathbf{c}_{i,j}= \mathbf{a}_{i,j} \oplus \mathbf{b}_{i,j}$$

定义两个矩阵的 $\times$ 运算是：

$$\mathbf{c}_{i,j}= \bigoplus_k \mathbf{a}_{i,k} \land \mathbf{b}_{k,j}$$

- **观察一**：换成矩阵表示就是：$\mathbf{S}_i=\mathbf{F}_{i-1}$。
- **观察二**：令 $\mathbf{A}$ 是一个 $m\times m$ 的矩阵 $\begin{bmatrix}  
  1 & 1 & 0 & 0 &\cdots & 0 \\  
  1 & 1 & 1 & 0 & \cdots & 0 \\  
  0 & 1 & 1 & 1 & \cdots & 0 \\  
  \vdots & \vdots & \vdots &\vdots & \ddots & \vdots \\  
  0 & \cdots & 0 & 1 & 1 & 1 \\
  0 & \cdots & 0 & 0 & 1 & 1 
\end{bmatrix} $，则 $\mathbf{F}_i = \mathbf{S}_i\times\mathbf{A} + \mathbf{a}_i = \mathbf{F}_{i-1}\times\mathbf{A} + \mathbf{a}_i$。

证明：因为 $\mathbf{A}$ 矩阵就是把操作点位置组成的向量转化为了受操作点影响而翻转位置组成的向量。

根据**观察二**，将迭代式暴力展开，有方程：

$$
\begin{align}
\mathbf{F}_n = \mathbf{0} = \mathbf{F}_{n-1}\times\mathbf{A}+\mathbf{a}_n=((\cdots((\mathbf{F}_1\mathbf{A}+\mathbf{a}_2)\mathbf{A}+\mathbf{a}_3)\mathbf{A}\cdots)\mathbf{A}+\mathbf{a}_{n-1})\mathbf{A}+\mathbf{a}_n
\end{align}
$$

- **观察三**（分配律）：$\mathbf{(a+b) \times A}=\mathbf{a\times A+b\times A}$，其中 $\mathbf{a,b}$ 是两个 $1\times m$ 的行向量。

证明：把 $\mathbf{a,b}$ 看做为操作点位置组成的向量，上式组合意义显然。

利用分配律，$(1)$ 式可以化简为：

$$
\mathbf{0}= \mathbf{F}_1\mathbf{A}^{n-1}+\sum_{i=2}^n \mathbf{a}_i\mathbf{A}^{n-i}
$$

注意由于这里的加法的实际定义是异或，所以 $\mathbf{a}+\mathbf{b}=\mathbf{a}-\mathbf{b}$，所以上式也就是：

$$
\left\{\begin{align}
\mathbf{F}_1 &= (\sum_{i=2}^n \mathbf{a}_i\mathbf{A}^{n-i})\mathbf{A}^{1-n}\\
\mathbf{S}_1 &= (\mathbf{F}_1 + \mathbf{a}_i) \times \mathbf{A}^{-1}
\end{align}\right.
$$

目标就转化为了判断 $(2)$ 式解的情况，也就是判断 $\mathbf{A}$ 是否存在逆元。如果 $\mathbf{A}^{-1}$ 存在，那么 $\mathbf{F}_1$ 的值一定是唯一确定的，根据 $(3)$ 式就可以唯一确定 $\mathbf{S}_1$ 的值，也就可以确定第一行的操作方案，那整个子矩阵操作的方案也就唯一确定下来了。

这就很简单了，写个矩阵求逆的模板就可以求出来是否存在逆元 $\mathbf{A}^{-1}$。此时，我们要求的就是 $\mathbf{S}_k = (\mathbf{F}_k+\mathbf{a}_k) \times \mathbf{A}^{-1}$，也就是求：

$$
\begin{aligned}
\mathbf{F}_k &= ((\cdots((\mathbf{F}_1\mathbf{A}+\mathbf{a}_2)\mathbf{A}+\mathbf{a}_3)\mathbf{A}\cdots)\mathbf{A}+\mathbf{a}_{k-1})\mathbf{A}+\mathbf{a}_k\\
&=\begin{align}  \mathbf{F}_1 \mathbf{A}^{k-1}+\sum_{i=2}^k \mathbf{a}_i\mathbf{A}^{k-i}\end{align}
\end{aligned}
$$

将 $(2)$ 带入 $(4)$ 得 $F_k$ 的表达式：

$$
\begin{align}
\mathbf{F}_k =  (\sum_{i=2}^n \mathbf{a}_i\mathbf{A}^{n-i} )\mathbf{A}^{k-n} +\sum_{i=2}^k \mathbf{a}_i\mathbf{A}^{k-i}
\end{align}
$$


因此预处理 $\mathbf{A}^p(p \in [-n,n])$ 的值即可 $\mathcal{O(nm)}$ 的算出答案。同时注意到如果我们把一个行向量压缩成一个数进行计算，可以省掉一个 $m$ 的复杂度。

时间复杂度：$\mathcal{O}(nm^2+qnm)$。期望得分：$70$ 分。

## 算法四（正解）

我会优化！

类比区间 hash 值的计算，预处理 $\sum \mathbf{a}_i \mathbf{A}^{n-i}$ 的前缀和即可快速计算，具体细节可以参考代码实现。

时间复杂度：$\mathcal{O}(nm^2+qm)$。期望得分：$100$ 分。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
namespace fast_IO{
    const int IOSIZE=(1<<21);static unsigned int precision=6,POW[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};static char obuf[IOSIZE],*p3=obuf;static char ibuf[IOSIZE],*p1=ibuf,*p2=ibuf;
#define getchar()((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x)((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
    template<typename T>static inline bool read(T&s){s=0;int w=1;char ch;while(ch=getchar(),!(ch>47&&ch<58)and(ch!=EOF))if(ch=='-')w=-1;if(ch==EOF)return false;while((ch>47&&ch<58))s=s*10+ch-48,ch=getchar();return s*=w,true;}template<typename T>static inline void print(T x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10+48);}static inline bool read(char&s){while(s=getchar(),isspace(s)and s!=EOF);return s!=EOF;}static inline void print(char x){putchar(x);}static inline bool read(char*s){char ch;while(ch=getchar(),(ch<33)&&ch!=EOF);if(ch==EOF)return false;while(!(ch<33)and(ch!=EOF))*s++=ch,ch=getchar();*s='\0';return true;}static inline void print(char*x){while(*x)putchar(*x++);}static inline void print(const char*x){for(int i=0;x[i];i++)putchar(x[i]);}static inline bool read(std::string&s){s="";char ch;while(ch=getchar(),(ch<33)and ch!=EOF);if(ch==EOF)return false;while(!(ch<33))s+=ch,ch=getchar();return true;}static inline void print(std::string x){for(int i=0,n=x.size();i<n;i++)putchar(x[i]);}static inline bool read(bool&b){char ch;while(ch=getchar(),(ch<33)and ch!=EOF);return ch==EOF?false:(b=ch^48,true);}static inline void print(bool b){putchar(b+48);}static inline bool read(double&x){char ch=getchar();int f=1;for(;(ch<48||57<ch)and(ch!=EOF);ch=getchar())if(ch=='-')f=-1;if(ch==EOF)return false;for(x=0;47<ch&&ch<58;ch=getchar())x=x*10+(ch^48);if(ch!='.')return x*=f,true;double y=0.1;for(ch=getchar();47<ch&&ch<58;ch=getchar())x+=y*(ch^48),y/=10;return x*=f,true;}static inline void print(double x){if(x<0)putchar('-'),x=-x;if(!precision)print((ull)(x-(ull)(x)>=0.5?x+1:x));else{ull xx=x;double y=((x-xx)*POW[precision]);ull yy=(y-(ull)(y)>=0.5?y+1:y);if(yy==POW[precision])xx++,yy=0;print(xx),putchar('.');for(int j=precision-1;~j;j--)putchar(48+yy/POW[j]%10);}}static inline bool read(long double&x){char ch=getchar();int f=1;for(;(ch<48||57<ch)and(ch!=EOF);ch=getchar())if(ch=='-')f=-1;if(ch==EOF)return false;for(x=0;47<ch&&ch<58;ch=getchar())x=x*10+(ch^48);if(ch!='.')return x*=f,true;long double y=0.1;for(ch=getchar();47<ch&&ch<58;ch=getchar())x+=y*(ch^48),y/=10;return x*=f,true;}static inline void print(long double x){if(x<0)putchar('-'),x=-x;if(!precision)print((ull)(x-(ull)(x)>=0.5?x+1:x));else{ull xx=x;long double y=((x-xx)*POW[precision]);ull yy=(y-(ull)(y)>=0.5?y+1:y);if(yy==POW[precision])xx++,yy=0;print(xx),putchar('.');for(int j=precision-1;~j;j--)putchar(48+yy/POW[j]%10);}}template<typename T,typename...T1>static inline int read(T&a,T1&...other){return read(a)+read(other...);}template<typename T,typename...T1>static inline void print(T a,T1...other){print(a),print(other...);}static struct Fast_IO{bool flag=1;inline~Fast_IO(){fwrite(obuf,p3-obuf,1,stdout);}inline void FUCKLD(int x){precision=x;}inline operator bool(){return flag;}}jyt;Fast_IO&operator>>(Fast_IO&io,char*b){return io.flag&=read(b),jyt;}template<typename T>static Fast_IO&operator>>(Fast_IO&io,T&b){return io.flag&=read(b),jyt;}template<typename T>static Fast_IO&operator<<(Fast_IO&io,T b){return print(b),jyt;}
    struct IO{char buf[IOSIZE],*p1,*p2;IO(){p1=p2=buf;}inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}IO&operator>>(char&x){while(x=gc(),x==' '||x=='\n');return*this;}template<typename T>IO&operator>>(T&x){x=0;bool f=0;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-')f^=1;ch=gc();}while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=gc();f?x=-x:0;return*this;}}ld;
}using namespace fast_IO;
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
#define clean(name) memset(name, 0, sizeof(name))
// #define ld cin
// #define jyt cout
// #define int long long
const int N = 5e4 + 7;
const int inf = 1e9 + 7;
const int P = 998244353;
namespace JoKing {
    int n, m, q; ull a[N], A[N][50], B[N][50], pre[N]; __uint128_t tmp[50];
    /*
    A[i]: A^i
    B[i]: A^-i
    */
    signed main() { int l, r, K; char ch;
        jyt >> n >> m >> q, --m;
        REP(i, 1, n) REP(j, 0, m) jyt >> ch, a[i] |= (static_cast<ull>(ch == '1') << j);
        REP(i, 0, m) A[1][i] = (i ^ 0 ? 1ull << (i - 1) : 0ull) | (1ull << i) | (i ^ m ? 1ull << (i + 1) : 0ull);
        REP(i, 0, m) tmp[i] = (static_cast<__uint128_t>(1) << (m + 1 + i)) | A[1][i];
        bool flag = true;
        REP(i, 0, m) { // 矩阵求逆
            REP(j, i, m) if (tmp[j] & (1ull << i)) {swap(tmp[i], tmp[j]); break;}
            if (!(tmp[i] & (1ull << i))) {flag = false; break;}
            REP(j, 0, m) if (i ^ j && (tmp[j] & (1ull << i))) tmp[j] ^= tmp[i];
        }
        if (!flag) { // 不存在 A^-1
            REP(i, 1, q) jyt >> l >> r >> K, jyt << "-1\n";
            return 0;
        }
        REP(i, 0, m) B[1][i] = tmp[i] >> (m + 1), A[0][i] = B[0][i] = (1ull << i);
        REP(R, 2, n) REP(i, 0, m) REP(k, 0, m) // 预处理 A[R],B[R]
            (A[R - 1][i] & (1ull << k)) && (A[R][i] ^= A[1][k]), 
            (B[R - 1][i] & (1ull << k)) && (B[R][i] ^= B[1][k]); 
        REP(R, 1, n) REP(k, 0, m) (a[R] & (1ull << k)) && (pre[R] ^= A[n - R][k]);
        REP(R, 2, n) pre[R] ^= pre[R - 1]; // 预处理 \sum a_i·A^{n-i}
        REP(R, 1, q) {
            jyt >> l >> r >> K;
            ull tmp1 = pre[r] ^ pre[l], tmp2 = pre[K] ^ pre[l], clac1 = 0, clac2 = 0, Res = 0, Ans = 0;
            REP(k, 0, m) (tmp1 & (1ull << k)) && (clac1 ^= B[n - r][k]), (tmp2 & (1ull << k)) && (clac2 ^= B[n - K][k]);
            // clac1 = \sum(l+1 <= i <= r) a_i A^{r-i}
            // clac2 = \sum(l+1 <= i <= k) a_i A^{k-i}
            REP(k, 0, m) (clac1 & (1ull << k)) && (Res ^= B[r - K][k]);
            // Res = clac1·A^r-k
            // F_l = Res ^ clac2
            Res = Res ^ clac2 ^ a[K];
            // Ans = S_l = (F_l ^ a[k])·A^-1
            REP(k, 0, m) (Res & (1ull << k)) && (Ans ^= B[1][k]);
            jyt << __builtin_popcountll(Ans) << '\n';
        }
        return 0;
    }
}
signed main() {
#ifdef WYY
    // freopen("files/code.in", "r", stdin);
    // freopen("files/code.out", "w", stdout);
    // freopen("files/code.err", "w", stderr);
#endif
    //	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    JoKing::main(); return 0;
}
// c.o[i][j] = a.o[i][k] & b.o[k][j]
// enum i,k
// c.o[i] ^= a.o[i][k] & b.o[k]
```

---

