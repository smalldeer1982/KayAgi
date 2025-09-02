# 【模板】Matrix-Tree 定理

## 题目描述

给定一张 $n$ 个结点 $m$ 条边的带权图（可能为无向图，可能为有向图）。

定义其一个生成树 $T$ 的权值为 $T$ 中所有边权的乘积。

求其所有不同生成树的权值之和，对 $10^9+7$ 取模。

---

注意：

1. 本题中，有向图的生成树指的是 **以 $1$ 为根的外向树**；

2. 两棵生成树 $T_1,T_2$ 不同，当且仅当存在存在一条边 $e$，满足 $e\in T_1,\ \ e\notin T_2$。

## 说明/提示

【样例 $1$ 解释】

样例 $1$ 中的无向图如左图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/pxtx9z5a.png)

右图为其一个权值为 $3\times 1\times 2\times 3=18$ 的生成树的例子。

---

【样例 $2$ 解释】

样例 $2$ 中的有向图如左图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/4276yln3.png)

右图为其一个权值为 $1\times 1\times 1\times 2=2$ 的生成树（以 $1$ 为根的外向树）的例子。

---

【数据范围】

对于 $100\%$ 的数据：$1\leq n\leq 300,\ \ 1\leq m\leq 10^5,\ \ t\in \{0,1\},\ \ 1\leq u,v\leq n,\ \ 1\leq w\leq 10^9$。

对于测试点 $1,2,3,4,5,6$，$t=0$；对于测试点 $7,8,9,10,11$，$t=1$。

图中 **可能** 存在重边和自环，重边算作多条边。

## 样例 #1

### 输入

```
5 8 0
2 3 1
1 2 3
4 5 1
4 2 2
3 5 2
3 4 3
3 4 1
3 3 5
```

### 输出

```
144
```

## 样例 #2

### 输入

```
5 9 1
1 2 3
3 2 1
1 3 1
2 4 2
3 5 1
4 3 4
3 5 1
5 4 1
4 4 6
```

### 输出

```
72
```

# 题解

## 作者：command_block (赞：131)

本文同时也作为`P6178`的题解。

# 1.行列式基础

- ## 行列式的定义

对于一个矩阵 $A[1...n][1...n]$ ,其行列式为

$\det(A)=\sum\limits_{P}(-1)^{\mu(P)}\prod\limits_{i=1}^nA[i][p_i]$

(枚举排列 $P[1...n]$ ,其中 $\mu(P)$ 为排列 $P$ 的逆序对数)

( $\det(A)$ 又作 $|A|$ )

也就是说在每一**行**挑一个乘起来,然后再拿逆序对有关的东西做系数。

直接按照定义计算,复杂度是 $O(n!·n)$ 的。

- ## 行列式的性质

知道了下面几条性质之后,我们就能快速计算行列式了。

- (0) 单位矩阵 $I$ 的行列式为 $1$ 。

这个比较显然,因为 $P$ 除了对角线之外没有别的选择,而对角线乘积为 $1$。

类似的,上三角矩阵和下三角矩阵的行列式都是对角线乘积。

- (1) 交换矩阵的两行,行列式变号。

(根据逆序对感性理解即可)

我们考虑对于**每个排列**,这一次交换**只会**影响乘积组前面的逆序对系数。

对于任意一个序列,交换两个数对于逆序对个数的影响必定为**奇数**(可以自己讨论一下)。

所以逆序对系数全部都改变,即变号。

- (2) 若某一**行**乘以 $t$ ,行列式就也乘以 $t$ 。

这个比较好理解,因为这一行**选且只选**一个嘛。

- (3) 看公式:

$\begin{vmatrix}a+a'&b+b'\\c&d\end{vmatrix}=\begin{vmatrix}a&b\\c&d\end{vmatrix}+\begin{vmatrix}a'&b'\\c&d\end{vmatrix}$

还是因为一行选且只选一个,然后**乘法分配律**就好了。

(2,3合起来就是**行**的线性性)

- (4) 有某两行一样的矩阵,行列式是 $0$.

这个证明比较巧妙 : 考虑交换相同的这两行,根据(1)得行列式**变号**。

但是矩阵并没有实质的改变,行列式**不变**,所以行列式的值只能是 $0$.

- (5) 用矩阵的一行加上另一行的倍数,行列式不变。

考虑构造(**省略的部分表示不变**):

欲证$\begin{vmatrix}a&b&c\\.&.&.\\d&e&f\end{vmatrix}=\begin{vmatrix}a&b&c\\.&.&.\\d+ka&e+kb&f+kc\end{vmatrix}$


首先构造一个$\begin{vmatrix}a&b&c\\.&.&.\\a&b&c\end{vmatrix}$,根据(4)得其值为0.

又根据(2)得$\begin{vmatrix}a&b&c\\.&.&.\\ka&kb&kc\end{vmatrix}$也为0。

然后根据(3)得

$$\begin{vmatrix}a&b&c\\.&.&.\\d+ka&e+kb&f+kc\end{vmatrix}=\begin{vmatrix}a&b&c\\.&.&.\\d&e&f\end{vmatrix}+\begin{vmatrix}a&b&c\\.&.&.\\ka&kb&kc\end{vmatrix}=\begin{vmatrix}a&b&c\\.&.&.\\d&e&f\end{vmatrix}$$

- ## 消元求行列式

其实我们上面证明的性质,就是为这个来打基础的。

我们消元的时候,只是用了 {交换两行, 某一行乘一个常数, 一行加上另一行的倍数} 三种操作。

那么,我们对于 $A$ 进行消元,然后记录操作对于行列式的影响,最后得到上三角矩阵,行列式就是对角线乘积,如果消不出来那么返回 $0$。

最后再把影响逆回去即可。

# 2.矩阵树定理与部分扩展

(默认图中**无自环**)

- ## 经典

给出一个无向无权图,设 $A$ 为邻接矩阵, $D$ 为度数矩阵( $D[i][i]=$节点 $i$ 的度数,其他的无值)。

则基尔霍夫(Kirchhoff)矩阵即为 : $K=D-A$

然后令 $K'$ 为 $K$ 去掉**第k行与第k列**(k任意)的结果($n-1$阶主子式),

$\det(K')$ 即为该图的生成树个数。

~~证明不会。感兴趣的同学可以自行百度。~~

**例题** : [P4336 [SHOI2016]黑暗前的幻想乡](https://www.luogu.org/problemnew/show/P4336)

- ## 加权扩展

容易理解 : 带重边的情况,上面的经典矩阵树定理也是能够处理的。

根据乘法原理,对于某种生成树的形态,其贡献为**每条边重的次数的乘积**。

如果把重边次数理解成权值的话,那么矩阵树定理求的就是 : 所有生成树边权乘积的总和。

(这里注意度数矩阵变成了相邻边的权值和)

**例题** : [P3317 [SDOI2014]重建](https://www.luogu.com.cn/problem/P3317)

- ## 有向扩展

前面都是无向图,神奇的是有向图的情况也是可以做的。

(邻接矩阵 $A$ 的意义同有向图邻接矩阵)

那么现在的矩阵 $D$ 就要变一下了。

若 $D[i][i]=\sum\limits_{j=1}^nA[j][i]$ ,即**到该点的边权总和(入)**。

此时求的就是**外向树** (从根向外)

若 $D[i][i]=\sum\limits_{j=1}^nA[i][j]$ ,即从**从该点出发的边权总和(出)**。

此时求的就是**内向树** (从外向根)

(如果考场上不小心忘掉了,可以手玩小样例)

(同样可以加权!)

此外,既然是有向的,那么就需要**指定根**。

前面提过要任意去掉第 $k$ 行与第 $k$ 列,是因为无向图所以不用在意谁为根。

在有向树的时候需要理解为指定根,结论是 : 去掉哪一行就是那一个元素为根。

**例题** : [P4455 [CQOI2018]社交网络](https://www.luogu.com.cn/problem/P4455) (内向树)

本题就是外向树,下面给出代码(出乎意料,跑的还挺快)。

```cpp
#include<algorithm>
#include<cstdio>
#define ll long long
#define mod 1000000007
#define Maxn 305
using namespace std;
ll powM(ll a,int t=mod-2)
{
  ll ans=1;
  while(t){
    if (t&1)ans=ans*a%mod;
    a=a*a%mod;t>>=1;
  }return ans;
}
int n,m;
ll *a[Maxn],_a[Maxn][Maxn];
ll det(ll **a)
{
  ll ans=1;bool tr=0;
  for (int j=1;j<n;j++){
    for (int i=j;i<n;i++)
      if (a[i][j]){
        if (i!=j){
          swap(a[i],a[j]);
          tr=!tr;
        }break;
      }
  	if (a[j][j]==0)return 0;
  	ans=ans*a[j][j]%mod;
  	ll t=powM(a[j][j]);
  	for (int k=j;k<n;k++)a[j][k]=t*a[j][k]%mod;
    for (int i=j+1;i<n;i++){
  	  t=mod-a[i][j];
  	  for (int k=j;k<n;k++)
  	    a[i][k]=(a[i][k]+t*a[j][k])%mod;
    }
  }return tr? (mod-ans)%mod : ans;
}
int op;
int main()
{
  scanf("%d%d%d",&n,&m,&op);
  for (int i=1;i<=n;i++)a[i]=_a[i];
  for (int i=1,f,t,w;i<=m;i++){
    scanf("%d%d%d",&f,&t,&w);
    if (f==n)f=1;else if (f==1)f=n;
    if (t==n)t=1;else if (t==1)t=n;
    if (op==1){
      a[f][t]=(a[f][t]-w+mod)%mod;
      a[t][t]=(a[t][t]+w)%mod;
    }else {
      a[f][t]=(a[f][t]-w+mod)%mod;
      a[t][t]=(a[t][t]+w)%mod;
      a[t][f]=(a[t][f]-w+mod)%mod;
      a[f][f]=(a[f][f]+w)%mod;
    }
  }printf("%lld",det(a));
  return 0;
}
```

---

## 作者：Achtoria (赞：63)

网上貌似证明比较少，而且不全，于是来 ~~水一篇博客~~。

首先介绍行列式及其基本性质：

## 行列式之前

定义奇排列为逆序对数量为奇数的排列，对于偶排列类似。

1. 交换排列两个元素，排列奇偶性改变。

> 一个简单的证明方法：考虑交换相邻两个元素，逆序对数量必 $+1/-1$，奇偶性必改变。
> 
> 那么假设交换排列中两个元素 $p_i, p_j$ 相当于先将 $p_i$ 向右交换 $j - i$ 次，再将 $p_j$ 向左交换 $j - i - 1$ 次，共 $2 \times (j - i) - 1$ 次必改变奇偶性。

2. $n > 1$ 的排列中，对于长度相同的奇偶排列数量相等。

> 不妨将问题转化一下：考虑序列 $f$ 表示每个位置前面比其大的数的个数，那么 $\sum f_i$ 为逆序对数量。
> 
> 不难发现对于任意的序列 $f$，若满足 $\forall i, f_i \in [0, i - 1]$，$f$ 可唯一对应一个排列且不重不漏。证明考虑局限前 $k$ 个数为一个排列，插入一个数将之前不小于其的数 $+1$ 的排列计数方式。
> 
> 再对于原问题使用归纳法，可易证得原命题成立。

## 定义

对于方阵 $A$：

$$
\begin{vmatrix}
a_{1, 1} & a_{1, 2} & \cdots & a_{1, n} \\ 
a_{2, 1} & a_{2, 2} & \cdots & a_{2, n} \\
\vdots & \vdots & \ddots & \vdots \\
a_{n, 1} & a_{n, 2} & \cdots & a_{n, n}
\end{vmatrix}
$$

定义其行列式 $\det(A) = \sum\limits_{p} \mathrm{sgn}(p) \prod\limits_{i = 1} ^ n a_{i, p_i}$ 其中 $p$ 为一个排列。

## 性质

1. 交换行列（方阵转置），行列式值不变。（即将原来的 $a_{i, j} \rightarrow a_{j, i}$）

> 只需证 $\sum\limits_{p} \mathrm{sgn}(p) \prod\limits_{i = 1} ^ n a_{i, p_i} = \sum\limits_{p} \mathrm{sgn}(p) \prod\limits_{i = 1} ^ n a_{p_i, i} \Longleftrightarrow \mathrm{sgn}(p) = \mathrm{sgn}(p')(p'_{p_i} = i)$
> 
> 对于后者，其等价于按照排列权值大小排序后下标的逆序对数量，这与原逆序对定义的数量是一致的。

2. 行列式某一行的倍数可以直接提取到行列式的值的外面

即对于方阵 $A$：

$$
\begin{vmatrix}
a_{1, 1} & a_{1, 2} & \cdots & a_{1, n} \\ 
\vdots & \vdots & \ddots & \vdots \\
ka_{i, 1} & ka_{i, 2} & \cdots & ka_{i, n} \\
\vdots & \vdots & \ddots & \vdots \\
a_{n, 1} & a_{n, 2} & \cdots & a_{n, n}
\end{vmatrix}
$$

其行列式 $\det(A) = k\sum\limits_{p} \mathrm{sgn}(p) \prod\limits_{i = 1} ^ n a_{i, p_i}$，证明是容易的。

3. 可以将行列式某行的值拆成两个部分其余行不变，然后拆开求和原行列式值相等

即：

$$
\begin{vmatrix}
a_{1, 1} & a_{1, 2} & \cdots & a_{1, n} \\ 
\vdots & \vdots & \ddots & \vdots \\
b_{i, 1} + c_{i, 1} & b_{i, 2} + c_{i, 2} & \cdots & b_{i, n} + c_{i, n} \\
\vdots & \vdots & \ddots & \vdots \\
a_{n, 1} & a_{n, 2} & \cdots & a_{n, n}
\end{vmatrix}
=
\begin{vmatrix}
a_{1, 1} & a_{1, 2} & \cdots & a_{1, n} \\ 
\vdots & \vdots & \ddots & \vdots \\
b_{i, 1} & b_{i, 2} & \cdots & b_{i, n} \\
\vdots & \vdots & \ddots & \vdots \\
a_{n, 1} & a_{n, 2} & \cdots & a_{n, n}
\end{vmatrix}
+
\begin{vmatrix}
a_{1, 1} & a_{1, 2} & \cdots & a_{1, n} \\ 
\vdots & \vdots & \ddots & \vdots \\
c_{i, 1} & c_{i, 2} & \cdots & c_{i, n} \\
\vdots & \vdots & \ddots & \vdots \\
a_{n, 1} & a_{n, 2} & \cdots & a_{n, n}
\end{vmatrix}
$$

证明是简单的。

4. 交换行列式两行，行列式值反号。

> 根据排列性质 $1$，相当于交换原排列的两个位置，奇偶性改变 $\rm sgn$ 值也必改变。

5. 若行列式两行成比例，则行列式值为 $0$。

> 首先将比例提出，那么此时行列式存在两行相等，交换两行行列式不变但值反号，可知行列式值为 $0$。

6. 将行列式某一行的 $k$ 倍加到另一行上，行列式值不变。

> 将加后行列式的被加行改写成 $kx + b$ 的形式，利用 $3$ 线性拆开，其中 $kx$ 的行列式根据 $5$ 值为 $0$。

7. 上述所有对行满足的性质，对于列而言也满足。

> 首先将矩阵转置，于是原来列操作等价于转置后的行操作，最后再转回来即可。

## 行列式值求法

**1. 模数为质数** 

对于上三角方阵 $A$：

$$
\begin{vmatrix}
a_{1, 1} & a_{1, 2} & \cdots & a_{1, n} \\ 
0 & a_{2, 2} & \cdots & a_{2, n} \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & a_{n, n}
\end{vmatrix}
$$

其行列式值显然为 $\det(A) = \prod\limits_{i = 1} ^ n a_{i, i}$，因此我们只需要将原行列式变成一个于其值相同的上三角方阵即可。

不难发现可以利用 $6$ 的性质配合高斯消元即可求得行列式的值。

复杂度 $\mathcal{O(n ^ 3)}$。

**2. 一般情况**

若模式不为质数，我们在消元时就不能直接算出 $\dfrac{a_{j, i}}{a_{i, i}}$，因为不存在逆元。

故我们不能使用分数的方式一次性消掉另一行，但注意到我们只需要消除这一行，故可以寻找一些别的方式。

考虑辗转相除的过程，我们每次将第 $j$ 行消去至 $a_{j, i} \rightarrow a_{j, i} \% a_{i, i}$ 然后交换两行，直至 $a_{j, i} = 0$。

因为辗转相除过程中只会变小，因此取模不会影响复杂度，故可以取模。

注意到辗转相除的复杂度为 $a_{i, i}$ 的减小次数，为 $\mathcal{O(\log P)}$，此部分总复杂度为 $\mathcal{O(n ^ 2\log P)}$ 不为瓶颈。

因此复杂度为 $\mathcal{O(n ^ 3)}$。

---

## 定义

1. 对于无向图，定义 $D(G)$ 为图 $G$ 的度数矩阵，其中：

$$
D(G)(i, j) = 
\begin{cases}
\deg_i & (i = j) \\
0 & (i \ne j)
\end{cases}
$$

2. 对于有向图，定义 $D ^ {in}(G)$ 为图 $G$ 的入度矩阵，$D ^ {out}(G)$ 为图 $G$ 的出度矩阵，其中：

$$
D(G) ^ {in}(i, j) = 
\begin{cases}
\mathrm{in}_i & (i = j) \\
0 & (i \ne j)
\end{cases},
D(G) ^ {out}(i, j) = 
\begin{cases}
\mathrm{out}_i & (i = j) \\
0 & (i \ne j)
\end{cases}
$$

3. 定义 $A(G)$ 为图 $G$ 的邻接矩阵，其中：

$$A(G)(i, j) = \text{the number of the path from i to j}$$

4. 定义图 $G$ 的 $\rm kirchhoff$ 矩阵 $K(G) = D(G) - A(G)$。

5. 定义无向图 $G$ 的生成树数量为 $t(G)$，有向图根向树生成树（根为 $u$，下同）数量为 $t ^ {root}(G, u)$，有向图叶向树数量为 $t ^ {leaf}(G, u)$。

6. 定义图 $G$ 的关联矩阵 $M(G)$ 为一个大小为 $n \times m$ 的矩阵，其中（一下的方向对于无向图随意）：

$$
M(G)(i, j) = 
\begin{cases}
-1 & (\text{i is the end of the } edge_j) \\
1 & (\text{i is the start of the } edge_j) \\
0 & (\text{Otherwise}) \\
\end{cases}
$$

7. 定义图 $G$ 的减关联矩阵 $M_0(G)$ 为关联矩阵 $M(G)$ 去掉最后一行后的大小为 $(n - 1) \times m$ 的矩阵。

8. 定义图 $G$ 的子减关联矩阵 $M_0(G)[S]$ 为选出 $M_0(G)$ 中的列构成子集 $S$，满足 $|S| = n - 1, S \subseteq \{1, 2, \cdots m\}$。

## 定理

**以下默认所有数均为正整数，图不存在自环但可存在重边**。

1. 无向图矩阵树定理：

$$\forall i \in [1, n], t(G) = \det K(G) \begin{pmatrix}1, 2, \cdots i - 1, i + 1, \cdots n \\ 1, 2, \cdots i - 1, i + 1, \cdots n\end{pmatrix}$$

2. 有向图矩阵树定理：

$$\forall i \in [1, n], t ^ {root}(G, i) = \det K ^ {out}(G) \begin{pmatrix}1, 2, \cdots i - 1, i + 1, \cdots n \\ 1, 2, \cdots i - 1, i + 1, \cdots n\end{pmatrix}$$

$$\forall i \in [1, n], t ^ {leaf}(G, i) = \det K ^ {in}(G) \begin{pmatrix}1, 2, \cdots i - 1, i + 1, \cdots n \\ 1, 2, \cdots i - 1, i + 1, \cdots n\end{pmatrix}$$

3. $\rm Best$ 定理：设有向欧拉图 $G$ 的欧拉回路数量为 $ec(G)$，则有：

$$\forall i \in [1, n], ec(G) = t ^ {root}(G, i) \prod\limits_{u \in V} (\deg_u - 1)!$$

其中对于欧拉图 $\mathrm{in}, \mathrm{out}$ 均相同，因此 $\deg$ 可任选其一。

若要求欧拉回路起点 $k$，则以 $k$ 为起点的欧拉回路数量 $ec(G, k)$ 为：

$$ec(G, k) = t ^ {root}(G, k) \deg_k \prod\limits_{u \in V} (\deg_u - 1)!$$

此定理下面暂不证明，~~先咕着~~。

以上所有定理，若带权求生成树 / 欧拉回路权值之和，可看 **将权值看作重边** 于是就可以划归到没有权值的情况。

## 证明

以下只证明无向图无根树生成树矩阵树定理。

**1. 引理 $1$**：

$$M \times M ^ {T} = K$$

$$
\begin{aligned}
M \times M ^ {T}(i, j) &= \sum\limits_{k = 1} ^ m M(i, k) \times M ^ {T}(k, j) \\
&= \sum\limits_{k = 1} ^ m M(i, k) \times M(j, k) \\
\end{aligned}
$$

可以发现当且仅当 $i, j$ 都为边 $k$ 的一个端点时，贡献不为 $0$。

若 $i = j$ 则 $M(i, k) = M(j, k)$ 贡献相等，那么两者乘积贡献 $1$。因此总贡献为 $\deg_i$。

若 $i \ne j$ 则 $M(i, k) \ne M(j, k)$ 贡献相反，那么两者乘积贡献 $-1$。因此总贡献为 $-A(i, j)$。

于是有引理 $1$ 成立。

**2. 引理 $2$**：

若 $S$ 构成的边集在原图上构成生成树，那么 $\det M_0[S] = 1 / -1$ 否则 $\det M_0[S] = 0$。

先证后者：

若原图没有构成树，那么至少存在一个简单环 $C(e_{i_1}, e_{i_2}, \cdots e_{i_k})$，记 $e_{{i_j}_u}, e_{{i_j}_v}$ 分别为边 $e_{i_j}$ 的两个端点。

同时，对于 $M_0[S]$ 有如下两点观察：

* 对于同一行（处于简单环对应的行），恰好存在两列（简单环对应列）非 $0$。

* 对于同一列（简单环对应列），恰好存在两行（处于简单环对应的行）一行为 $1$ 一行为 $-1$。（若为最后一行也可视作出现）

下面证明 $M_0[S]$ 对应原简单环中的 $i_1, i_2, \cdots i_k$ 列线性相关，考虑依次合并所有列：

我们首先拿第 $i_1$ 列消 $i_2$ 列，因为简单环上两边共点，因此至少存在一行使得两列上均非 $0$，我们消掉这一行后根据观察 $2$ 必恰好仅有 $e_{{i_1}_u}, e_{{i_2}_v}$ 这两行一行为 $1$ 一行为 $-1$。

假设合并到第 $i_j$ 列，若 $j \ne k$ 那么使用 $i_{j - 1}$ 列合并的结果同第一列消第二列的方式消掉第 $i_j$ 列，于是第 $i_j$ 列消完后必恰好在 $e_{{i_1}_u}, e_{{i_j}_v}$ 这两行一行为 $1$ 一行为 $-1$。

最后合并到第 $i_{k - 1}$ 列时，此时非 $0$ 两行与原 $i_k$ 列未消时一致，故此时可以将第 $i_k$ 列消为全 $0$。

因此这 $i_1, i_2, \cdots i_k$ 列线性相关，$\det M_0[S] = 0$。 

---

再证前者：

考虑将原行列式消成好算的形式，类似于高斯消元的方式，我们钦定一行的主元拿此行去消所有行。

具体地，若 $S$ 构成的边集为一棵树，那么必定能找到叶子节点 $u$，此时选出 $u$ 所在的行，必定恰好只存在一列非 $0$，拿此列去消所有行（事实上只能消掉边的另一个节点所对应的行）。

可以发现这等价于每次在 $M_0[S]$ 中删去树上叶子节点所对应的一条边，故此过程一定可以不断递归直至消去所有边。

最后我们发现，每一行都只剩下恰好一列为其做为叶子时所对应列为 $1 / -1$，故此时行列式值仅在每行选这些列时非 $0$，不论逆序对数量，所得行列式值均为 $1 / -1$。

**3. 引理 $3$（$\rm Binet - Cauchy$ 定理）**：

定义大小分别为 $n \times m, m \times n(n \le m)$ 的矩阵 $A, B$ 则有：

$$\det(AB) = \sum\limits_{S \subseteq \{1, 2, \cdots m\}, |S| = n} \det(A[S]) \times \det(B[S])$$

其中 $A[S], B[S]$ 分别表示 $A$ 取 $S$ 集合内的列，$B$ 取 $S$ 集合内的行所构成的矩阵。

证明引理 $3$ 之前再给出两条引理：

定义 $\lambda(P)$ 为排列 $P$ 的逆序对数量。

* 1. 引理 $1$：

* 定义 $P'$ 为 $P$ 的逆排列，即满足 $P'_{P_i} = i$，那么有：

$$\lambda(P) = \lambda(P')$$

$\quad$ 不妨转化 $P'$ 的逆序对求法，不难发现等价于给定序列 $A$，每个元素存在两个关键字 $x, y$，其中 $A_{i_x} = p_i, A_{i_y} = i$。

$\quad$ 那么 $\lambda(P')$ 等价于将将序列 $A$ 按照第一关键字排序后以第二关键字为权值的逆序对数量。

$\quad$ 在这里等价于按照权值排序后求下标的逆序对，这与直接求原排列的逆序对是等价的。

* 2. 引理 $2$：

* 定义 $P_{Q}$ 为排列 $Q$ 与排列 $P$ 的复合，则 $\lambda(P_{Q})$ 与 $\lambda(P) + \lambda(Q)$ 的奇偶性相同。

$\quad$ 仿照引理 $1$ 的证明方法，那么左式等价去求给定序列 $A$，每个元素存在两个关键字 $x, y$ 其中 $A_{i_x} = Q'_i, A_{i_y} = P_i$，

$\quad$ 那么 $\lambda(P_Q)$ 等价于按照第一关键字排序后以第二关键字为权值的逆序对数量。

$\quad$ 考虑调整证明，可知一开始的逆序对数量为 $\lambda(P)$，排序利用冒泡排序的过程，可知有效的交换仅有 $Q'$ 的逆序对个。

$\quad$ 而我们知道每交换排列里两个元素排列逆序对数奇偶性改变，故总共改变 $\lambda(P)$ 次，所以 $\lambda(P_Q)$ 与 $\lambda(P) + \lambda(Q)$ 奇偶性相同。

---

首先我们展开等式右侧：

$$
\begin{aligned}
& \sum\limits_{S \subseteq \{1, 2, \cdots m\}, |S| = n} \det(A[S]) \times \det(B[S]) \\
&= \sum\limits_{S \subseteq \{1, 2, \cdots m\}, |S| = n} \left(\sum\limits_{P} (-1) ^ {\lambda(P)} \prod\limits_{i = 1} ^ n A_{i, S_{P_i}}\right) \times \left(\sum\limits_{Q} (-1) ^ {\lambda(Q)} \prod\limits_{i = 1} ^ n B_{S_i, Q_i}\right) \\
&= \sum\limits_{S} \sum\limits_{P} \sum\limits_{Q} (-1) ^ {\lambda(P) + \lambda(Q)} \prod\limits_{i = 1} ^ n A_{i, S_{P_i}} \times B_{S_i, Q_i} \\
\end{aligned}
$$

再展开等式左侧：

$$
\begin{aligned}
& \det(AB) \\
&= \sum\limits_{P} (-1) ^ {\lambda(P)} \prod\limits_{i = 1} ^ n \left(\sum\limits_{j = 1} ^ m A_{i, j} \times B_{j, P_i}\right) \\
&= \sum\limits_{P} (-1) ^ {\lambda(P)} \sum\limits_{R} \left(\prod\limits_{i = 1} ^ n  A_{i, R_i} \times B_{R_i, P_i}\right) (|R| = n, \forall i, R_i \in \{1, 2, \cdots m\}) \\
&= \sum\limits_{R} \sum\limits_{P} (-1) ^ {\lambda(P)} \left(\prod\limits_{i = 1} ^ n A_{i, R_i}\right) \times \left(\prod\limits_{i = 1} ^ n B_{R_i, P_i}\right)
\end{aligned}
$$

仔细观察可知，对于可重排列 $R$，若存在 $i < j, R_i = R_j$ 那么交换 $P_i, P_j$ 后后面的积式不变，但逆序对奇偶性改变，因此两者贡献互为相反数可抵消。

因此我们只需钦定每个存在 $i < j, R_i = R_j$ 的可重排列 $R$，让其和交换满足条件的最小 $P_i, P_j$ 交换后的排列 $P$ 的贡献相抵即可。

因为交换最小的 $i, j$ 后依然满足 $i, j$ 为最小的满足条件的点对，因此可以两两唯一配对。

故我们只需枚举不重的序列即可，为此我们首先枚举 $\{1, 2, \cdots m\}$ 的子集，然后枚举一个长度为 $n$ 的排列 $Q$：

$$
\begin{aligned}
& \det(AB) \\
&= \sum\limits_{S} \sum\limits_{Q} \sum\limits_{P} (-1) ^ {\lambda(P)} \prod\limits_{i = 1} ^ n A_{i, S_{Q_i}} \times B_{S_{Q_i}, P_i} \\
&= \sum\limits_{S} \sum\limits_{Q} \sum\limits_{P_{Q'}} (-1) ^ {\lambda(P_{Q'})} \left(\prod\limits_{i = 1} ^ n A_{i, S_{Q_i}}\right) \times \left(\prod\limits_{i = 1} ^ n B_{S_i, P_{Q'_i}}\right) \\
&= \sum\limits_{S} \sum\limits_{Q} \sum\limits_{P_{Q'}} (-1) ^ {\lambda(P) + \lambda(Q)} \left(\prod\limits_{i = 1} ^ n A_{i, S_{Q_i}}\right) \times \left(\prod\limits_{i = 1} ^ n B_{S_i, P_{Q'_i}}\right)
\end{aligned}
$$

整理即可得到从右侧推导得到的式子。

---

下面我们只证明矩阵树定理删去最后一行最后一列是正确的（对于删去其余的情况，只需将 $M_0$ 的定义修改成删去改行即可）。

类似于引理 $1$，我们知道 $K_0 = M_0 \times M_0 ^ T$ 其中 $K_0$ 为 $K$ 去掉最后一行和最后一列得到的方阵。

再根据引理 $3$，可知：

$$
\begin{aligned}
\det K_0 &= \sum\limits_S \det(M_0[S]) \det(M_0 ^ T[S]) \\
&= \sum\limits_S \det{^ 2}(M_0[S])
\end{aligned}
$$

由定理 $2$，若边集 $S$ 不构成生成树，则 $\det(M_0[S]) = 0$，在该式中贡献为 $0$。

若边集 $S$ 构成生成树，则 $\det(M_0[S]) = 1 / -1$，在该式中贡献为 $1$。

故可得到 $\det K_0$ 即为原图的生成树数量。

---

参考资料：

[OI-Wiki](https://oi-wiki.org/graph/matrix-tree/)

[行列式学习笔记 - suxxsfe](https://www.cnblogs.com/suxxsfe/p/12446673.html)

[矩阵树定理（Matrix-tree Theorem）笔记 - silverxz](https://zhuanlan.zhihu.com/p/108209378)

[Binet-Cauchy定理的证明 - lyyi2003](https://www.cnblogs.com/lishuyu2003/p/12093947.html)

---

## 作者：zhylj (赞：55)

## Matrix-Tree 定理

### 前言

似乎这里还没有 Matrix-Tree 定理的证明，这边写一个。

### 内容

对于一张无向带权图，每条边带有交换环 $(R,+,\cdotp)$ 上的边权，记 $\mathcal T$ 是其所有生成树构成的集合，我们有：

（注：你可以将交换环理解为一个定义了加法和乘法运算，并且满足交换律、结合律、分配律以及存在单位元，对任意元素都存在加法逆元，且对这两种运算都封闭的集合）

定义其 Kirchhoff 矩阵为：

$$K_{i,j} = \left\{\begin{aligned}& \sum_{k\neq i} w(i,k) &,i=j\\& -w(i,j) &,i\neq j\end{aligned}\right.$$

记 $M$ 表示 $K$ 删去任意相同编号的行列后的矩阵，则：

$$\sum_{t\in\mathcal T} \prod_{(u,v)\in t} w(u,v) = |M|$$

（即，定义一个生成树的权值是其上所有边权的乘积，求所有生成树的权值和）

其中 $|A|$ 表示 $A$ 的行列式。

### 证明

先记住行列式的定义：

$$|A| = \sum_{p} (-1)^{\tau(p)} \prod_{i} A_{i,p_i}$$

我们先建出不带符号的 Kirchhoff 矩阵。

我们考虑任选一个点做根，并在接下来的处理中把它忽略（只忽略这个点，而不忽略与它相连的边）.

接下来，我们对每个点任取一条出边，统计它的权值（也就是定理中 $M$ 主对角线上的元素之积，可以通过展开乘积的式子发现为任取一条出边的方案数）。

容易发现，这样我们会连出来恰好一棵树，可能会连出来若干基环树。

于是我们考虑对环的个数进行容斥：

- 我们枚举所有环，然后剩下的边随便连，计算这种情况的方案数，并减去它。
- 我们枚举所有不交的两个环，然后剩下的边随便连，计算这种情况的方案数，并加上它。
- ...

我们又注意到一个排列（置换）可以被表示成若干轮换的形式，所以实际上我们相当于枚举排列。

- 可以发现，这个排列对应的权值和为 $\prod M_{i,p_{i}}$，任取的部分同样可以通过展开式子得到。
- 那么容斥系数是什么呢？注意到我们枚举的排列中 $p_i = i$ 表示“随便连”，而不是自环，假如我们统计了排列的轮换个数的话，我们应该给他们（$M_{i,i}$）带上容斥系数 $-1$，以消去这部分的容斥系数。

记 $C(p)$ 表示排列 $p$ 形成轮换的个数

$$\sum(-1)^{C(p)} \prod M_{i,p_i}$$

慢着，虽然我们以及能感觉到上面的式子和行列式的定义很像，但上面说的是“统计排列的轮换个数”的奇偶性，但是行列式式子中却统计了“逆序对个数”的奇偶性，那么这两个值有什么关系呢？

**引理 1**：交换排列中的任意两个数，逆序对个数的奇偶性改变。

**证明**：首先我们显然可以知道交换排列中的相邻两个数，逆序对个数的奇偶性改变，然后我们考虑排列中的两个位置 $p_j,p_k$：

$$p_j,p_{j+1},\cdots,p_{k-1}p_k$$

先不断把 $p_k$ 向前交换到 $p_j$ 原先的位置，记交换了恰好 $x$ 次：

$$p_k,p_j,p_{j+1},\cdots,p_{k-1}$$

然后再把 $p_j$ 不断向右交换，则交换了恰好 $x-1$ 次：

$$p_k,p_{j+1},\cdots,p_{k-1},p_j$$

我们发现，我们总共交换了恰好 $2x - 1$ 次，即奇偶性改变了 $2x - 1$ 次，显然这是奇数，所以逆序对个数的奇偶性必然改变。

**引理 2**：对于排列 $p$，$\tau(p)$ 的奇偶性和排列长度减去轮换的个数的奇偶性相等。

**证明**：考虑对于每个轮换我们都可以交换环长 $-~1$ 次将其上的元素排序，所以总共我们可以通过交换 $\sum$ 环长 $-~1$ 次得到排列 $1,2,\cdots,n$，显然该值等于 $n - C(p)$。注意到我们每次交换两者奇偶性都同时改变，最后排列变为 $1,2,\cdots,n$ 时两者奇偶性相同，故刚开始时两者奇偶性也相同。

这样已经很清楚了，唯一的问题是多了一个 $(-1)^n$，我们只需要把上面 $M$ 的所有系数取相反数就可以把这个系数消去了，同时我们也就得到了行列式的形式。

至此，Matrix-Tree 定理得证。

### 应用

#### 生成树计数

**题目**：计算一张 $n(n\le 300)$ 个点的无向图的生成树的个数。

我们只需要令 $u,v$ 之间的权值为它们之间的边数，然后套用 Matrix-Tree 定理，高斯消元求行列式即可，时间复杂度为 $\mathcal O(n^3)$.

#### 生成树权值和

**题目**：计算一张 $n(n\le 300)$ 个点的无向图的生成树的所有生成树的权值和，其中权值定义为生成树每条边边权之和。

若原来 $u,v$ 之间的边权为 $w$，令它们之间新的边权为一个一次的多项式 $wx+1$，然后我们可以发现两个边权乘积的一次项恰为边权值和，在 $\bmod~x^2$ 意义下定义乘法，套用 Matrix-Tree 定理即可，时间复杂度仍为 $\mathcal O(n^3)$.

#### 有向图树形图计数

**题目**：计算一张 $n(n\le 300)$ 个点的有向图的以 $1$ 为根的外向树形图个数。

假如我们要求某个有向图以某个点为根的外向 / 内向树形图个数，类比无向图，我们变为了枚举入边 / 出边，并且主对角线上的权值就变为了入度 / 出度，在无向图上的 Matrix-Tree 定理的证明的基础上，我们可以很容易的构造矩阵。

### 代码

Luogu 上的板子题。

```cpp
const int kN = 3e2 + 5, kMod = 1e9 + 7;

int n, m, typ, mat[kN][kN];

int Det() {
	int ret = 1, si = 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = i + 1; j <= n; ++j)
			while(mat[j][i]) {
				int t = mat[i][i] / mat[j][i];
				for(int k = i; k <= n; ++k) {
					mat[i][k] = (mat[i][k] - 1LL * t * mat[j][k]) % kMod;
					std::swap(mat[i][k], mat[j][k]);
				}
				si *= -1;
			}
		ret = 1LL * ret * mat[i][i] % kMod;
	}
	return (ret * si % kMod + kMod) % kMod;
}

int main() { 
	rd(n, m, typ); --n;
	for(int i = 1; i <= m; ++i) {
		int u, v, w; rd(u, v, w);
		--u; --v;
		if(!typ) {
			mat[u][u] = (mat[u][u] + w) % kMod;
			mat[v][v] = (mat[v][v] + w) % kMod;
			mat[u][v] = (mat[u][v] - w) % kMod;
			mat[v][u] = (mat[v][u] - w) % kMod;
		} else {
			mat[v][v] = (mat[v][v] + w) % kMod;
			mat[v][u] = (mat[v][u] - w) % kMod;
		}
	}
	printf("%d\n", Det());
}
```

---

## 作者：Leianha (赞：37)

## 矩阵树定理

[ 博客阅读](https://www.cnblogs.com/wljss/p/12421603.html)

想必大家应该都会高斯消元吧，不会的话可以看[模板](https://www.luogu.com.cn/problem/P3389),我们现在着重讲一下建矩阵的方法。

前置知识：我们用到的矩阵，也就是基尔霍夫矩阵的任意一个代数余子式是所有生成树的边权积的和。

当所有边边权为1时求的就是生成树的个数了。

我们以下设 $(x,y,z)$ 为 $x$ 到 $y$ 有一条边权为 $z$ 的 无向/有向 边。

### 1.无向图

假设现在给定一个图 $G$ .

度数矩阵D:若存在边 $(x,y,z)$ ,则 $D[x][x]+=z;D[y][y]+=z;$ 

邻接矩阵C:若存在边 $(x,y,z)$ ,则 $C[x][y]+=z;C[y][x]+=z;$ 

图G的基尔霍夫矩阵 $A$ = $D$ − $C$ 。

删去任意一行和任意一列，求剩下的矩阵行列式即可。

### 2.有向图

假设现在给定一个图G.

度数矩阵D:若存在边 $(x,y,z)$ ,则 外向树中 $D[y][y]+=z;$ 内向树中 $D[x][x]+=z;$

邻接矩阵C:若存在边 $(x,y,z)$ ,则 内向树和外向树中均为 $C[x][y]+=z;$ 

图G的基尔霍夫矩阵 $A$ = $D$ − $C$ 。

删去指定的根所在的行和列，求剩下的矩阵行列式即可。

本题中即为外向树的情况.

```cpp
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int n, m, t, x, y, z, ans = 1;
const int N = 305, mod = 1e9 + 7;
int a[N][N];
int ksm(int a, int b, int mod)
{
	int res = 1;
	for (; b; b >>= 1, a = (LL)a * a % mod)
		if (b & 1)res = (LL)res * a % mod;
	return res;
}
void work()
{
	for (int i = 2, inv, tmp; i <= n; ++i)
	{
		for (int j = i + 1; j <= n; ++j)
			if (!a[i][i] && a[j][i]) {ans = -ans; swap(a[i], a[j]); break;}
		inv = ksm(a[i][i], mod - 2, mod);
		for (int j = i + 1; j <= n; ++j)
		{
			tmp = (LL)a[j][i] * inv % mod;
			for (int k = i; k <= n; ++k)a[j][k] = (a[j][k] - (LL)a[i][k] * tmp % mod) % mod;
		}
	}
}
signed main()
{
	cin >> n >> m >> t;
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d%d%d", &x, &y, &z);
		if (!t)
		{
			(a[x][x] += z) %= mod; (a[y][y] += z) %= mod;
			(a[x][y] -= z) %= mod; (a[y][x] -= z) %= mod;
		}
		else
		{
			(a[y][y] += z) %= mod; (a[x][y] -= z) %= mod;
		}
	}
	work();
	for (int i = 2; i <= n; ++i)ans = (LL)ans * a[i][i] % mod;
	cout << (ans % mod + mod) % mod;
	return 0;
}
```

---

## 作者：yingjingxu_NaS2O3 (赞：11)

作为一个生成树计数中的一个重要定理，Matrix-Tree 拥有通用性强~~和大家都不会证明~~的~~双重~~优点。

# Laplace 矩阵

亦称 Kirchhoff 矩阵。

## 无向图的 Laplace 矩阵

我们定义 Laplace 矩阵 $L = D-A$，其中 $D$ 是该图的度数矩阵，$A$ 是该图的邻接矩阵。

我们规定

$$D_{ij}=\begin{cases}\deg (i),i=j&\\0,i\ne j&\end{cases}$$

至于邻接矩阵，不必多言。

我们不妨记无向图 $G$ 的生成树个数为 $t(G)$。

## 有向图的 Laplace 矩阵

我们定义有向图的出度 Laplace 矩阵 $L^{\mathrm{out}}=D^{\mathrm{out}}-A$，入度 Laplace 矩阵 $L^{\mathrm{in}}=D^{\mathrm{in}}-A$，其中 $D^{\mathrm{out}}$ 是该图的出度矩阵，$D^{\mathrm{in}}$ 是该图的入度矩阵。

我们规定

$$D^{\mathrm{out}}_{ij}=\begin{cases}\deg^{\mathrm{out}}(i),i=j&\\0,i\ne j&\end{cases}$$

同理，有

$$D^{\mathrm{in}}_{ij}=\begin{cases}\deg^{\mathrm{in}}(i),i=j&\\0,i\ne j&\end{cases}$$

我们不妨记有向图 $G$ 以 $k$ 为根的$^\dag$**内向生成树**个数为 $t^{\mathrm{in}}(G,k)$，以 $k$ 为根的外向生成树个数为 $t^{\mathrm{out}}(G,k)$。

$^\dag$内向生成树：有向图生成的满足所有子节点都只向父节点连有向边的树，如下图所示的树即为一棵以节点 $3$ 为根的内向树。

![](https://pic1.imgdb.cn/item/67f22e040ba3d5a1d7eea0f6.png)

同理，外向生成树即有向图生成的满足所有父节点都只向子节点连有向边的树。

# Matrix-Tree 定理

## 定理内容

### 无向图的 Matrix-Tree 定理

一个无向图 $G$，对于 $\forall k\in[1,n]\cap \mathbb Z$，都有

$$t(G)=\det L_{[n]\setminus \{k\},[n]\setminus \{k\}}$$

其中 $\det A$ 是对 $A$ 的行列式求值的结果。

即无向图 Laplace 矩阵的所有 $n-1$ 阶主子式的值与该图的生成树个数均相等。

如果你不会行列式求值，[click here](https://www.luogu.com.cn/article/ezmuawvs)。

### 有向图的内向生成树的 Matrix-Tree 定理

一个有向图 $G$，对于 $\forall k\in[1,n]\cap \mathbb Z$，都有

$$t^{\mathrm{in}}(G,k)=\det L^{\mathrm{out}}_{[n]\setminus \{k\},[n]\setminus \{k\}}$$

即有向图的**出度** Laplace 矩阵删去第 $k$ 行第 $k$ 列得到的主子式的值与该图的**内向**生成树的个数相等。

### 有向图的外向生成树的 Matrix-Tree 定理

一个有向图 $G$，对于 $\forall k\in[1,n]\cap \mathbb Z$，都有

$$t^{\mathrm{out}}(G,k)=\det L^{\mathrm{in}}_{[n]\setminus \{k\},[n]\setminus \{k\}}$$

即有向图的**入度** Laplace 矩阵删去第 $k$ 行第 $k$ 列得到的主子式的值与该图的**外向**生成树的个数相等。

### 带权无向图的 Matrix-Tree 定理

一个无向图 $G$，对于 $\forall k\in[1,n]\cap \mathbb Z$，都有

$$\sum\limits_{T\in \mathcal T(G)}w(T)=\det L_{[n]\setminus \{k\},[n]\setminus \{k\}}$$

其中 $\mathcal T(G)$ 是图 $G$ 的生成树集合。

### 带权有向图的内向生成树的 Matrix-Tree 定理

一个有向图 $G$，对于 $\forall k\in[1,n]\cap \mathbb Z$，都有

$$\sum\limits_{T\in \mathcal T^{\mathrm{in}}(G,k)}w(T)=\det L^{\mathrm{out}}_{[n]\setminus \{k\},[n]\setminus \{k\}}$$

其中 $\mathcal T^{\mathrm{in}}(G,k)$ 是图 $G$ 的内向生成树集合。

### 带权有向图的外向生成树的 Matrix-Tree 定理

一个有向图 $G$，对于 $\forall k\in[1,n]\cap \mathbb Z$，都有

$$\sum\limits_{T\in \mathcal T^{\mathrm{out}}(G,k)}w(T)=\det L^{\mathrm{in}}_{[n]\setminus \{k\},[n]\setminus \{k\}}$$

其中 $\mathcal T^{\mathrm{out}}(G,k)$ 是图 $G$ 的外向生成树集合。

## 定理证明

### Cauchy-Binet 公式

对于一个 $n\times m$ 的矩阵 $A$ 和一个 $m\times n$ 的矩阵 $B$，有

$$\det(AB)=\sum\limits_{S\subset [m]\land |S|=n}\det A_{[n],S}\det B_{S,[n]}$$

#### 证法一

若 $n>m$，由于

$$\operatorname{rank}(AB)\le\min\{\operatorname{rank}(A),\operatorname{rank}(B)\}\le m<n$$

其中 $\operatorname{rank}(A)$ 为矩阵 $A$ 的秩，故 $\det(AB)=0$。

若 $n=m$，该式显然成立。

下面论证 $n<m$ 的情况。

记 $I_n$ 为 $n$ 阶单位矩阵。

首先有引理

$$\begin{vmatrix}I_n&B\\A&I_m\end{vmatrix}=\begin{vmatrix}I_n&B\\0&I_m-AB\end{vmatrix}=|I_m-AB|$$

$$\begin{vmatrix}I_n&B\\A&I_m\end{vmatrix}=\begin{vmatrix}I_n-BA&B\\0&I_m\end{vmatrix}=|I_n-BA|$$

于是有

$$\lambda^n|\lambda I_m-AB|=\lambda^m|\lambda I_n-BA|$$

考虑证明。

当 $\lambda=0$ 时，显然成立。

当 $\lambda\ne 0$ 时，

$$\begin{aligned}\lambda^n|\lambda I_m-AB|&=\lambda^{n+m}|I_m-\lambda^{-1}AB|\\&=\lambda^{n+m}|I_n-\lambda^{-1}BA|\\&=\lambda^m|\lambda I_m -BA|\end{aligned}$$

设 $P=(p_{ij})_{n,n}$，设展开式系数

$$|\lambda I-P|=\lambda^n+\sum\limits_{k=1}^n(-1)^kc_k\lambda^{n-k}$$

下证 $c_k$ 为 $P$ 中所有 $k$ 阶主子式值之和。

不妨引入 Kronecker 符号

$$\delta_{ij}=\begin{cases}1,i=j&\\0,i\ne j&\end{cases}$$

则

$$|\lambda I-P|=\sum\limits_{\sigma \in S_n}\operatorname{sgn}(\sigma)\prod\limits_{i=1}^n (\lambda \delta_{i,\sigma(i)}-p_{i,\sigma (i)})$$

考虑其中对 $\lambda^{n-k}$ 项系数有贡献的部分。

对于 $\forall \sigma \in S_n$，设

$$\mathscr J(\sigma)=\{J\subseteq\{1,2,3,\dots,n\}\big|\forall j\in J,\sigma(j)=j\}$$

$$\mathscr J_k(\sigma)=\{J\in \mathscr J(\sigma)\big| \lvert J\rvert=k \}$$

则有

$$(-1)^kc_k=(-1)^k\sum\limits_{\sigma \in S_n}\operatorname{sgn}(\sigma)\sum\limits_{J\in \mathscr J_{n-k}(\sigma)}\prod\limits_{i \notin j}p_{i,\sigma(i)}$$

$$c_k=\sum\limits_{|J|=k}\sum_{\sigma\in S_{n,j}}\operatorname{sgn}(\sigma)\prod_{i\notin J}p_{i,\sigma(i)}$$

$$c_k=\sum\limits_{|J|=k}|P_{[n]\setminus J,[n]\setminus J}|$$

则我们证明了该引理。

接下来考虑证明 Cauchy-Binet 公式。

$$\lambda^{n-m}|\lambda I_m-AB|=|\lambda I_n-BA|$$

考察左右两侧 $\lambda^{n-m}$ 项系数，

$$(-1)^m|AB|=(-1)^m\sum\limits_{|J|=m}|(BA)_{[n]\setminus J,[n]\setminus J}|$$

故

$$\begin{aligned}|AB|&=\sum\limits_{|J|=m}|(BA)_{[n]\setminus J,[n]\setminus J}|\\&=\sum\limits_{|J|=m}|A_{[n]\setminus [m],[n]\setminus J}||B_{[n]\setminus J,[n]\setminus [m]}|\end{aligned}$$

#### 证法二

直接暴力计算。

---

Cauchy-Binet 公式表明，Laplace 矩阵的主子式其实是一系列子结构的和，每个子结构都反映了对应子图的性质。

对于 Cauchy-Binet 公式的证明，可以看看[这篇](https://zhuanlan.zhihu.com/p/7837458535)。

### 关联矩阵

我们规定不带权无向图的关联矩阵 $M$ 为

$$M_{ij}=\begin{cases}-1,\exist u(e_i=(v_j,u))&\\1,\exist u(e_i=(u,v_j))&\\0,\mathrm{otherwise}&\end{cases}$$

考虑拓展到带权有向图，容易得知出度关联矩阵 $M^{\mathrm{out}}$ 为

$$M^{\mathrm{out}}_{i,j}=\begin{cases}\sqrt{w(e_i)},\exist u(e_i=(v_j,u))\\0,\mathrm{otherwise}&\end{cases}$$

出度关联矩阵 $M^{\mathrm{in}}$ 为

$$M^{\mathrm{in}}_{i,j}=\begin{cases}\sqrt{w(e_i)},\exist u(e_i=(u,v_j))\\0,\mathrm{otherwise}&\end{cases}$$

显然有

$$D^{\mathrm{out}}=(M^{\mathrm{out}})^TM^{\mathrm{out}},A=(M^{\mathrm{out}})^TM^{\mathrm{in}},D^{\mathrm{in}}=(M^{\mathrm{in}})^TM^{\mathrm{in}}$$

进而有

$$L^{\mathrm{out}}=(M^{\mathrm{out}})^T(M^{\mathrm{out}}-M^{\mathrm{in}}),L^{\mathrm{in}}=(M^{\mathrm{in}}-M^{\mathrm{out}})^TM^{\mathrm{in}}$$

#### 引理

对于 $G$ 的一个子图 $(W,S)$，若 $|W|=|S|\le n$，则

子图 $G_s=(V,S)$ 是一个以 $V\setminus W$ 为根节点集的内向森林，当且仅当

$$\det(M^{\mathrm{out}}_{S,W})\det(M^{\mathrm{out}}_{S,W}-M^{\mathrm{in}}_{S,W})\ne 0$$

且当上式成立时，其值必然为

$$\prod\limits_{e\in S}w(e)$$

记之为 $w(G_s)$。

#### 引理的证明

证明我不是很会，可以去 [OI-Wiki](https://oi-wiki.org/graph/matrix-tree/#%E7%94%A8%E5%85%B3%E8%81%94%E7%9F%A9%E9%98%B5%E5%88%BB%E7%94%BB%E5%9B%BE%E7%9A%84%E7%BB%93%E6%9E%84) 查看。

----

现在可以证明 Matrix-Tree 定理了。

我们以带权有向图的内向生成树的 Matrix-Tree 定理为例，记 $W=[n]\setminus\{k\}$ 为除去节点 $k$ 后的点集。

#### 带权有向图的内向生成树的 Matrix-Tree 定理

一个有向图 $G$，对于 $\forall k\in[1,n]\cap \mathbb Z$，都有

$$\sum\limits_{T\in \mathcal T^{\mathrm{in}}(G,k)}w(T)=\det L^{\mathrm{out}}_{[n]\setminus \{k\},[n]\setminus \{k\}}$$

其中 $\mathcal T^{\mathrm{in}}(G,k)$ 是图 $G$ 的内向生成树集合。

#### 证明

根据 Cauchy-Binet 公式，有

$$\begin{aligned}\det L^{\mathrm{out}}_{[n]\setminus \{k\},[n]\setminus \{k\}}&=\det(L^{\mathrm{out}}_{W,W})\\&=\sum\limits_{S\subset [m]\land |S|=n-1}\det M^{\mathrm{out}}_{S,W} \det (M^{\mathrm{out}}_{S,W}-M^{\mathrm{in}}_{S,W})\end{aligned}$$

由关联矩阵引理，当且仅当 $T$ 是一个以 $k$ 为根的内向树时，右侧累加一个 $w(T)$。

# Cayley 公式

$n$ 个节点的有标号不同构无根树数量为 $n^{n-2}$。

## 证法一：一一对应

考虑利用组合数学证明。

钦定 $T$ 是其中一棵树，叶子节点中标号最小的记为 $a_1$，$a_1$ 的邻接点（即有根树中的父亲）记为 $b_1$，从图中删去 $a_1$ 及所有连边，$b_1$ 便成为这棵树的顶点。

在余下的树 $T_1$ 中，叶子节点中标号最小的记为 $a_2$，$a_2$ 的邻接点记为 $b_2$，从图中删去 $a_2$ 及所有连边，$b_2$ 便成为这棵树的顶点。

如此步骤继续 $n-2$ 次，直到剩下最后一条边，于是一棵树 $T$ 对应一个序列

$$b_1,b_2,b_3,\cdots,b_{n-2}$$

其中 $b_i\in [1,n] \cap \mathbb Z$，并且**允许重复**。

为何允许重复比较易懂，留给读者自行思考。

现在证明一个序列对应一棵树。

我们不妨再引入一个序列

$$c_1,c_2,c_3,\cdots,c_n$$

其中 $c_i=i$。

在序列 $c$ 中找出第一个不出现在序列 $b$ 中的数，显然，这个数是 $a_1$，同时，我们有了一条边 $(a_1,b_1)$，我们从 $c$ 中消去 $a_1$，从 $b$ 中消去 $b_1$，在余下的部分中继续执行此操作 $n-2$ 次。最后，$c$ 中剩余两个数，即为 $a_{n-1}$ 和 $b_{n-1}$，是树 $T$ 的最后一条边。

于是我们证明了序列 $b$ 和树 $T$ 一一对应。

考虑计数，由于序列 $b$ 可重，故总方案数为

$$n^{n-2}$$

序列 $b$ 也称为树 $T$ 的 Prüfer 序列。

## 证法二：Matrix-Tree 定理

不妨转化问题，我们发现原问题等价于求 $n$ 个顶点的完全图的生成树数量。

我们写出 Laplace 矩阵

$$L=\left\lgroup\begin{array}{cc}n-1&-1&-1&\cdots&-1\\-1&n-1&-1&\cdots&-1\\-1&-1&n-1&\cdots&-1\\\vdots&\vdots&\vdots&\ddots&\vdots\\-1&-1&-1&\cdots&n-1\end{array}\right\rgroup_{n\times n}$$

计算其任意 $n-1$ 阶主子式，有

$$\begin{aligned}\det(nI_{n-1}-{\bf 1} {\bf 1}^T)&=n^{n-1}\det(I_{n-1}-n^{-1}{\bf 1}{\bf 1}^T)\\&=n^{n-1}(I_{n-1}-n^{-1}{\bf 1}^T{\bf 1})\\&=n^{n-1}(1-\frac{n-1}{n})\\&=n^{n-2}\end{aligned}$$

应用无向图的 Matrix-Tree 定理，原命题得证。

# BEST 定理

设 $G$ 为有向欧拉图，$k$ 为任意顶点，则 $G$ 的不同欧拉回路个数

$$\operatorname{euc}(G)=t^{\mathrm{in}}(G,k)\prod\limits_{v\in V}(\deg(v)-1)!$$

BEST 定理表明，对于 $\forall k,k'\in V_G$，都有 $t^{\mathrm{in}}(G,k)=t^{\mathrm{in}}(G,k')$。

## 证明

考虑图 $G$ 的任意一棵内向树，对于每个节点 $u$，我们给以 $u$ 为起点的所有**不在**内向树上的 $\deg(u)-1$ 条**出边**一个顺序，称这个根向树及这个出边的排列顺序为一个组合。

于是我们只需要证明组合和欧拉回路一一对应。

考虑从根节点开始，每到达一个节点，若不在内向树上的出边都被走过了，就沿着根向树上的边走向其父亲，否则就按照出边的排列顺序走向下一个节点。

注意到这样只会经过每个节点至多一次，现在证明这样会**经过且仅经过每个节点一次**。

不妨设到达节点 $u$ 后无法移动，考虑分类讨论。

若 $u$ 不是根节点，我们经过 $u$ 时会经过其一条入边和一条出边，而无法移动说明只经过了 $u$ 的一条入边，说明 $\deg^{\mathrm{in}}(u)=\deg^{\mathrm{out}}(u)+1$，与 $G$ 为欧拉图矛盾。

这样我们就证明了这种方案一定会形成一个欧拉回路。

现在我们证明了一个组合对应一个欧拉回路，接下来考虑证明一个欧拉回路对应一个组合。

记 $e_u$ 为 $u$ 最后访问的入边，下面证明所有 $e_u$ 构成一棵内向树。

不妨设 $e_u$ 构成的图中有环，首先根节点必然不会出现在环上。现在环上找出任意一个节点 $u$，容易发现 $u$ 沿着环的方向可以再次回到 $u$。由于原图是欧拉图，$\deg^{\mathrm{in}}(u)=\deg^{\mathrm{out}}(u)$，而 $u$ 在环上回到 $u$ 会导致 $\deg^{\mathrm{in}}(u)=\deg^{\mathrm{out}}(u)+1$，矛盾，故所有 $e_u$ 构成树。

其实我觉得到 $\deg^{\mathrm{in}}(u)=\deg^{\mathrm{out}}(u)$ 即可推出结论，因为这说明根节点与这个环的任意一个节点没有连边。

于是一个组合和一个欧拉回路**一一对应**。

# 典例

## SP104 HIGH - Highways

直接连边后求出 Laplace 矩阵，删去任意一个点后高斯消元求解即可。

```cpp
for(int i=1;i<=m;i++)
{
  int u,v;
  scanf("%lld%lld",&u,&v);
  a[u][v]--;
  a[v][u]--;
  a[u][u]++;
  a[v][v]++; 
}
ans=det(n-1);
```

## P4111 [HEOI2015] 小 Z 的房间

同样地，求出 Laplace 矩阵后高斯消元求解即可。

## P3317 [SDOI2014] 重建

给定了 Laplace 矩阵，直接高斯消元求解。

## P4208 [JSOI2008] 最小生成树计数

先跑最小生成树，若没有直接输出 $0$，由于权值相同边至多 $10$ 条，一边并查集合并一边求行列式，最后将贡献加起来即可。

```cpp
if(!kruskal(n,m))
{
  printf("0\n");
  return 0;
}
int ans=1;
for(int i=1;i<=cntv;i++)
{
  init(n);
  for(int j=1;j<n&&tr[j].w!=v[i];j++)
    merge(tr[j].u,tr[j].v);
  for(int j=n-1;j>=1&&tr[j].w!=v[i];j--)
    merge(tr[j].u,tr[j].v);
  cntb=0;
  for(int j=1;j<=n;j++)
    if(fa[j]==j)
      b[j]=++cntb;
  for(int j=1;j<=n;j++)
    b[j]=b[find(j)];
  memset(a,0,sizeof a);
  for(int j=1;j<=m;j++)
  {
    if(e[j].w!=v[i])
      continue;
    a[b[e[j].u]][b[e[j].v]]--;
    a[b[e[j].v]][b[e[j].u]]--;
    a[b[e[j].u]][b[e[j].u]]++;
    a[b[e[j].v]][b[e[j].v]]++;
  }
  ans=ans*det(cntb-1)%mod;
}
```

## P2143 [JSOI2010] 巨额奖金

和最小生成树计数是一个题，略微转化即可。

## P6178 【模板】Matrix-Tree 定理

无向边变为了有向边。建立 Laplace 矩阵的时候删去一半即可，删去的一半和剩下的一半只要对称即可。

```cpp
for(int i=1;i<=m;i++)
{
  int u,v,w;
  scanf("%lld%lld%lld",&u,&v,&w);
  if(u==1||u==n)
    u=n-u+1;
  if(v==1||v==n)
    v=n-v+1;
  a[u][v]=(a[u][v]-w+mod)%mod;
  a[v][v]=(a[v][v]+w)%mod;
  if(!t)
  {
    a[v][u]=(a[v][u]-w+mod)%mod;
    a[u][u]=(a[u][u]+w)%mod;
  }
}
printf("%lld\n",det(n-1));
```

## P2144 [FJOI2007] 轮状病毒

这里讲一种很无脑的做法。

求出 Laplace 矩阵，直接删去中间点后消元，删去中间点的过程可以简化为 $a_{ii}\gets a_{ii}+1$。

高精计算即可，注意优化高精度。

## P4455 [CQOI2018] 社交网络

也是有向图形式的 Matrix-Tree 定理板子。同样高斯消元求解即可。

## P5296 [北京省选集训2019] 生成树计数

建立 Laplace 矩阵时矩阵内的值变成了多项式，考虑 $\exp$ 形式后就很好做。

```cpp
K++;
for(int i=1;i<=n;i++)
  for(int j=1;j<=n;j++)
  {
    int w;
    scanf("%lld",&w);
    if(i>j)
      continue;
    poly tmp=exp(w);
    a[i][j]=a[i][j]-tmp;
    a[j][i]=a[j][i]-tmp;
    a[i][i]=a[i][i]+tmp;
    a[j][j]=a[j][j]+tmp;
  }
printf("%lld\n",det(n-1)[K-1]*fac[K-1]%mod);
```

## P6624 [省选联考 2020 A 卷] 作业题

是上一题的弱化版。以同一种方式考虑即可。

## P5807 【模板】BEST 定理 | Which Dreamed It

BEST 定理的直接应用。套用 BEST 定理直接计算即可。

## P7531 [USACO21OPEN] Routing Schemes P

有人说很难看出来是 BEST 定理，我觉得很显然。直接套用 BEST 定理即可，注意起点和终点的处理，使用一种类似网络流的形式建立超级源点和超级汇点即可。

# 编者按

本文在洛谷、博客园和 CSDN 更新。后续可能会补充。

## 参考资料

[矩阵树定理 - OI Wiki](https://oi-wiki.org/graph/matrix-tree/)

[Matrix Tree 定理及证明 - \_Wallace\_](https://www.cnblogs.com/-Wallace-/p/matrix-tree.html)

[柯西比内Cauchy-Binet公式的3种证明 - 
Whitea](https://zhuanlan.zhihu.com/p/7837458535)

[矩阵树定理&BEST定理学习笔记 - tzc_wk](https://www.cnblogs.com/tzcwk/p/matrix-tree-best-theroem.html)

[代数学讲义 - 李文威](https://www.wwli.asia/index.php/en/books-item-en)

[高等代数（第五版） - 王萼芳、石生明](https://xuanshu.hep.com.cn/front/book/findBookDetails?bookId=5bc22d0ef18f967ee7f37820)

[高等代数 辅导及习题精解（北大|第五版） - 张天德](https://www.hep.com.cn/book/show/9f2bd856-3e5d-4d99-a06c-e362feccc207)

[组合数学（第5版） - 卢开澄、卢华明](https://www.tup.tsinghua.edu.cn/booksCenter/book_07098001.html)

---

## 作者：SSerxhs (赞：10)

## 本文仅讲述行列式求值（任意模数）

众所周知，行列式求值的通用方法是 $ans\leftarrow ans*inv(a_{i,i}),a_{i,i}\leftarrow 1$。

但是，当 $p$ 不是素数时逆元不存在，不能用这种方法。

考虑到行列式行相减不改变值，又注意到这样做本质是为了清 $0$ ，可以考虑对行用辗转相除法的方法完成。复杂度仍为 $O(n^3)$。

证明：$(x,y)$ 两次辗转相除之后最大值减半，势能分析可得这个 $\log $ 其实是摊到 $O(n)$ 行的，也就是 $O(n^2(n+\log p))$。

代码为[行列式求值板子](https://www.luogu.com.cn/problem/U135840)std。

upd：现已加入主题库豪华模板。
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=602;
inline void read(register int &x)
{
	register int c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
int a[N][N];
int n,p,i,j;
int cal(int a[][N],register int n,const int p)
{
	register int i,j,k,r=1,fh=0,l;
	for (i=1;i<=n;i++)
	{
		k=i;
		for (j=i+1;j<=n;j++) if (a[j][i]>a[k][i]) break;
		if (a[k][i]==0) return 0;j=k;
		if (i!=j) {swap(a[j],a[i]);fh^=1;}
		for (j=i+1;j<=n;j++)
		{
			if (a[j][i]>a[i][i]) {swap(a[j],a[i]);fh^=1;}
			while (a[j][i])
			{
				l=a[i][i]/a[j][i];
				for (k=i;k<=n;k++) a[i][k]=(a[i][k]+(ll)(p-l)*a[j][k])%p;
				swap(a[j],a[i]);fh^=1;
			}
		}
		r=(ll)r*a[i][i]%p;
	}
	if (fh) return (p-r)%p;
	return r;
}
int main()
{
	read(n);read(p);
	for (i=1;i<=n;i++) for (j=1;j<=n;j++) {read(a[i][j]);a[i][j]%=p;}
	printf("%d",cal(a,n,p));
}
```

---

## 作者：月下萤火 (赞：5)

### 题目大意：
求解此公式的值：$\sum_{T}^{}\prod_{e\in T}^{}p_{e}$
### 思路：
考点非常明确，即矩阵树定理，矩阵树代码基本都差不多，唯一的区别就在于建图。考虑到本题给出的带权图既可能为无向图，也可能为有向图，分别处理即可
### 建图：
- 无向图

度数矩阵D：若存在边$(x，y，z)$，则 $D[x] [x] + = z$ ; $D[y] [y] + = z$ ;

邻接矩阵A：若存在边$(x，y，z)$，则 $A[x] [y] + = z$ ; $D[y] [x] + = z$ ;

基尔霍夫矩阵 $K = D - A$

删去任意一行和任意一列，求矩阵行列式即可

- 有向图

度数矩阵D：若存在边$(x，y，z)$，则外向树中 $D[y] [y] + = z$ ; 内向树中 $D[x] [x] + = z$;

邻接矩阵A：若存在边$(x，y，z)$，则内向树和外向树中均为 $A[x] [y] + = z$ ;

删去指定根所在的行和列，求矩阵行列式即可

本题的处理：
```c
x--;y--;//本题限定1为根,故要删去根所在的行和列 
if(!op){
	K[x][x]=(K[x][x]+z)%mod;K[y][y]=(K[y][y]+z)%mod;
	K[x][y]=(K[x][y]-z+mod)%mod;
	K[y][x]=(K[y][x]-z+mod)%mod;
}
else{
	K[x][y]=(K[x][y]-z+mod)%mod;
	K[y][y]=(K[y][y]+z)%mod;
}
```

### 代码：
```c
#include<iostream>
#include<cstring>

using namespace std;

typedef long long LL;

const int N=310;
const int mod=1e9+7;

LL K[N][N];
int n,m,op;

inline LL qpow(LL x,LL n){
	LL ret=1;
	while(n){
		if(n&1)
		ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		n>>=1;
	}
	return ret;
}

inline LL gauss(){
	int ret=1;
	n--;
	for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++)
            if(K[j][i]){
                swap(K[i],K[j]);
                if(i!=j)
                    ret=mod-ret;
                break;
            }
        int t=qpow(K[i][i],mod-2);
        for(int j=i+1;j<=n;j++)
            if(K[j][i])
                for(int k=n;k>=i;k--)
                    K[j][k]=(K[j][k]-K[i][k]*t%mod*K[j][i]%mod+mod)%mod;
    }
	for(int i=1;i<=n;i++)
		ret=1ll*ret*K[i][i]%mod;
	return ret;
}

int main(){
	scanf("%d%d%d",&n,&m,&op);
	int x,y,z;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		x--;y--;//本题限定1为根,故要删去根所在的行和列 
		if(!op){
			K[x][x]=(K[x][x]+z)%mod;K[y][y]=(K[y][y]+z)%mod;
			K[x][y]=(K[x][y]-z+mod)%mod;
			K[y][x]=(K[y][x]-z+mod)%mod;
		}
		else{
			K[x][y]=(K[x][y]-z+mod)%mod;
			K[y][y]=(K[y][y]+z)%mod;
		}
	}
	cout<<gauss();
}
```


---

## 作者：_HCl_ (赞：4)

小蒟蒻第一次写模板题解，有错误请见谅。

# P6178 题解（矩阵树定理）

**题意简述**

给定一张无向/有向的带权图，定义一颗生成树的权值为其所有边权的乘积，求该图所有生成树的权值和。

特别地，对于有向图，生成树为以 $1$ 为根的外向树。

**定理介绍**

矩阵树定理可以求出无权图的生成树个数。其中无权图允许重边但不允许自环。

先介绍三个矩阵，度矩阵，邻接矩阵和 Laplace 矩阵。

- 度矩阵 $D$

对于无向图，度矩阵记录每一个节点的度。

$$D_{i,j}=\begin{cases}deg_i&i=j\\0&i\neq j\end{cases}$$

对于有向图，有出度矩阵 $D^{out}$ 和入度矩阵 $D^{in}$。也就是将上式中的度数换成出度/入度。

- 邻接矩阵 $A$

邻接矩阵记录每两个点之间的重边数量。用 $e_{i,j}$ 表示从 $i$ 到 $j$ 的重边数量。

$$A_{i,j}=e_{i,j}$$

- Lapace 矩阵 $L$

对于无向图：

$$L=D-A$$

对于有向图：

$$L^{out}=D^{out}-A\ ,\ L^{in}=D^{in}-A$$

$L^{out}$ 和 $L^{in}$ 被称作出度 Laplace 矩阵和入度 Laplace 矩阵。Laplace 矩阵也被称作 Kirchhoff 矩阵。

我们规定记号 $\text{Sub}(M,i)$ 表示将矩阵 $M$ 去掉第 $i$ 行与第 $i$ 列的 $n-1$ 阶主子矩阵。

（自己乱搞的记号，我不知道有什么数学语言可以表示这个）

**矩阵树定理（Matrix-Tree Theorem）**

对于无向图：

$$t(G)=\det\ \text{Sub}(L(G),i)$$

其中 $t(G)$ 是图 $G$ 的生成树个数，$L(G)$ 是 $G$ 的 Laplace 矩阵，$i$ 是任意数。

对于有向图：

$$t^{out}(G)=\det\ \text{Sub}(L^{in}(G),rt)\ ,\ t^{in}(G)=\det\ \text{Sub}(L^{out}(G),rt)$$

其中 $t^{out}(G)$ 是外向（叶向）生成树个数，$t^{in}(G)$ 是内向（根向）生成树个数，$rt$ 是生成树的根。

**思路引导**

本题虽然是带权图，但是可以将边的权值视为重边数量。

根据乘法原理，点之间连接方式相同的生成树个数就是生成树上所有边的重边数量的乘积，正好与题目中“生成树的权值”对应。

那么题目就转化为了求图的所有生成树个数。使用矩阵树定理解决。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1000000007;
int A[501][501],D[501][501],L[501][501];
int det(int a[501][501],int n){//行列式求值
	int res=1,cur=1;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j){
			while(a[i][i]){
				int div=a[j][i]/a[i][i];
				for(int k=i;k<=n;++k)
					a[j][k]=(a[j][k]+MOD-div*a[i][k]%MOD)%MOD;
				swap(a[i],a[j]),cur=-cur;		
			}
			swap(a[i],a[j]),cur=-cur;
		}
	for(int i=1;i<=n;++i)res=res*a[i][i]%MOD;
	res=(MOD+res*cur)%MOD;
	return res;
}
int n,m,Typ;
signed main(){
	cin>>n>>m>>Typ;
	for(int i=1;i<=m;++i){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		u--,v--;//删去第一行第一列，直接让第一行变成0，到时候不算就可以
		D[v][v]=(D[v][v]+w)%MOD,A[u][v]=(A[u][v]+w)%MOD;
		if(!Typ) D[u][u]=(D[u][u]+w)%MOD,A[v][u]=(A[v][u]+w)%MOD;
	}
	for(int i=1;i<n;++i)
		for(int j=1;j<n;++j)L[i][j]=(D[i][j]+MOD-A[i][j])%MOD;
	cout<<det(L,n-1);
} 
```

---

