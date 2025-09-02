# Substring Compression

## 题目描述

我们定义对一个由至少 $2$ 个 $1$ 到 $9$ 的数字组成的字符串 $t$ 的压缩操作如下：

- 将其分割为偶数个非空子串——设这些子串为 $t_1, t_2, \dots, t_m$（因此 $t = t_1 + t_2 + \dots + t_m$，其中 $+$ 表示连接操作）；
- 写下字符串 $t_2$ 共 $t_1$ 次，然后写下字符串 $t_4$ 共 $t_3$ 次，依此类推。

例如，对于字符串 "12345"，可以这样分割：("1", "23", "4", "5")，然后写下 "23" 共 $1$ 次，"5" 共 $4$ 次，得到 "235555"。

定义函数 $f(t)$，表示对字符串 $t$ 进行上述操作后，能够得到的最短字符串长度。

给定一个由 $n$ 个 $1$ 到 $9$ 的数字组成的字符串 $s$，以及一个整数 $k$。请计算 $s$ 的所有长度恰好为 $k$ 的连续子串的 $f$ 值。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 4
5999```

### 输出

```
14```

## 样例 #2

### 输入

```
10 3
1111111111```

### 输出

```
2 2 2 2 2 2 2 2```

## 样例 #3

### 输入

```
11 4
49998641312```

### 输出

```
12 18 17 15 12 7 7 2```

# 题解

## 作者：ZhongYuLin (赞：4)

考虑转化题意，变为：将原序列划分为若干长度大于等于 2 的段，设第 $i$ 段的长度为 $len_i$，开头数字为 $a_i$，则第 $i$ 段的代价为 $a_i\times(len_i-1)$。最小化代价。

不难借助此题意写出暴力 dp。设 $f_{i,j}$ 表示考虑前 $i$ 个，最后一段的开头数字为 $j$ 的最小代价。方便起见，设 $\min_i=\min_{j=0}^9 f_{i,j}$。

$\begin{cases} & f_{i,j}=f_{i-1,j}+j \\ & f_{i,a_{i-1}}=\min(f_{i,a_{i-1}},\min_{i-2}+a_{i-1}),i\geq4 \end{cases}$

考虑 ddp，使用广义矩阵乘法，定义加法为 $\min$，乘法为加法，设计状态向量为：

$$\begin{bmatrix} f_{i-1,1}\\ f_{i-1,2}\\ f_{i-1,3}\\ f_{i-1,4}\\ f_{i-1,5}\\ f_{i-1,6}\\ f_{i-1,7}\\ f_{i-1,8}\\ f_{i-1,9}\\ \min_{i-1}\\ \min_{i-2} \end{bmatrix}$$

分两步进行转移，先转移 $f_i$，列出矩阵：

$$\begin{bmatrix}
1 &  &  &  &  &  &  &  &  &  &  \\
  &2 &  &  &  &  &  &  &  &  &  \\
  &  &3 &  &  &  &  &  &  &  &  \\
  &  &  &4 &  &  &  &  &  &  &  \\
  &  &  &  &5 &  &  &  &  &  &  \\
  &  &  &  &  &6 &  &  &  &  &  \\
  &  &  &  &  &  &7 &  &  &  &  \\
  &  &  &  &  &  &  &8 &  &  &  \\
  &  &  &  &  &  &  &  &9 &  &  \\
  &  &  &  &  &  &  &  &  &0 &  \\
  &  &  &  &  &  &  &  &  &  &0 
\end{bmatrix}$$

特别地，$\forall i\geq 2$，矩阵的第 $a_{i-1}$ 行第 $11$  列为 $a_{i-1}$。

接下来转移 $\min_i$。容易列出矩阵：

$$\begin{bmatrix}
0 & & & & & & & & & & \\
 &0 & & & & & & & & & \\
 & &0 & & & & & & & & \\
 & & &0 & & & & & & & \\
 & & & &0 & & & & & & \\
 & & & & &0 & & & & & \\
 & & & & & &0 & & & & \\
 & & & & & & &0 & & & \\
 & & & & & & & &0 & & \\
0 &0 &0 &0 &0 &0 &0 &0 &0 & & \\
 & & & & & & & & &0 & \\
\end{bmatrix}$$

容易用线段树维护区间积，但是应该会超时。注意到每次询问等长，分块即可。

代码：

```cpp
#pragma GCC optimize("Ofast,no-stack-protector,fast-math",3)
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+3,INF=0x3f3f3f3f;
template<class T1,class T2>void ckmn(T1 &x,T2 y){if(x>y)x=y;}
struct Mat{
    int a[12][12];
    Mat(){memset(a,0x3f,sizeof(a));}
    friend Mat operator*(const Mat &x,const Mat &y){
        Mat z;
        for(int i=1;i<=11;++i)
            for(int k=1;k<=11;++k){
                if(x.a[i][k]>=INF)continue;
                for(int j=1;j<=11;++j)
                    ckmn(z.a[i][j],x.a[i][k]+y.a[k][j]);
            }
        return z;
    }
}g[N],pre[N],suf[N];
int n,K,len;
int a[N],ans[N];
string s;
Mat query(int l,int r){
    if(l==r)return g[l];
    return suf[r]*pre[l]; 
}
void solve(){
    cin>>n>>K>>s;s="#"+s;
    Mat A,B;
    for(int i=1;i<=9;++i)
        A.a[10][i]=0,A.a[i][i]=0;
    A.a[11][10]=0;
    for(int i=1;i<=9;++i)
        B.a[i][i]=i;
    B.a[10][10]=B.a[11][11]=0;
    for(int i=1;i<=n;++i){
        a[i]=s[i]-'0';
        g[i]=B;
        if(i>1)g[i].a[a[i-1]][11]=a[i-1];
        g[i]=A*g[i];
    }
    len=K-3;
    if(len>0){
        for(int i=1;i<=n;i+=len){
            int lim=min(n,i+len-1);
            pre[lim]=g[lim];
            for(int j=lim-1;j>=i;--j)
                pre[j]=pre[j+1]*g[j];
        }
        for(int i=1;i<=n;i+=len){
            int lim=min(n,i+len-1);
            suf[i]=g[i];
            for(int j=i+1;j<=lim;++j)
                suf[j]=g[j]*suf[j-1];
        }
    }
    for(int i=1;i<=n-K+1;++i){
        Mat res;
        res.a[a[i]][1]=a[i];
        res.a[10][1]=a[i];
        if(K>2)res=query(i+2,i+K-1)*res;
        int ans=INF;
        for(int i=1;i<=9;++i)
            ckmn(ans,res.a[i][1]);
        printf("%d ",ans);
    }
    puts("");
}
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;for(T=1;T--;)solve();
    return 0;
}
```

---

## 作者：ZeroOf149 (赞：3)

# [CF2004G Substring Compression](https://www.luogu.com.cn/problem/CF2004G)

## 闲话

由于我想让这道 *3200 的题有 *2500 的效果，所以我写得尽可能详细一些。  
为了叙述的方便，一个数字串 $t$ 也可以表示其指代的数字，请读者注意辨别。

## 题目描述

给一个数字串 $s$，**自行**选取一个**偶数** $m$，并将其适当地划分为 $m$ 段**非空**数字串，记为 $\{t_m\}$。  
定义这个划分的权值为：对所有 $1 \leq k \leq \dfrac{m}{2}$，将 $t_{2k}$ 重复 $t_{2k-1}$ 次后，全体拼接而成的字符串长度。  
记所有可能的划分的最小权值为 $f(s)$，则对于长度为 $n$ 的数字串 $S$，请你依次求出 $S$ 所有长度为 $k$ 的连续子串所对应的函数值。  
$2 \leq k \leq n \leq 2 \times 10^5$，保证 $S$ 中只含 $1$ 至 $9$ 的数字。

## 解法说明

### 动态规划部分

首先，我们不难发现：$|t_{2k-1}|=1\left(1 \leq k \leq \dfrac{m}{2}\right)$。  
证明：调整法。  
若 $|t_{2k-1}|>1$，记 $a = \lfloor\dfrac{t_{2k-1}}{10}\rfloor, b = t_{2k-1} \bmod 10,L = |t_{2k}|$，则原方案的贡献为 $W_1 = L(10a+b)$，将 $t_{2k-1}$ 的最后一位数字移动至 $t_{2k}$ 的贡献为 $W_2 = a(L+1)$，做差知 $W_1 - W_2 = L(9a+b)-a > 10L-9 \geq 1$，因此 $W_1 > W_2$。

通过这一点，我们不难设计一个朴素的 dp：记 $dp_{i,a}$ 表示对 $s$ 的前 $i$ 位，限制 $t_{m-1} = a$ 的最小权值。  
转移分两种情况：
  - 将当前位接上 $t_{m}$，有 $dp_{i,a}=dp_{i-1,a}+a$；
  - 将上一位单独划分，即 $t_{m-1}=s_{i-1}, t_m = s_i$，有 $dp_{i, s_{i-1}} \gets \min\{dp_{i, s_{i-1}},\displaystyle\min_{a=1}^9\{dp_{i-2, a}\}+s_{i-1}\}$。

容易发现这可以被改写为 $(\min, +)$ 矩阵乘，因此我们能够进行区间查询。  
更详细地，我们对位置 $i$ 定义状态 $v_i = (dp_{i,1}, dp_{i,2}, \cdots, dp_{i,9}, \displaystyle\min_{a=1}^9\{dp_{i-1, a}\},\displaystyle\min_{a=1}^9\{dp_{i, a}\})$，仿照上文写出 $i$ 处的转移矩阵 $G=g_i$：
  - 将当前位接上 $t_{m}$，有 $G_{a,a} = a(1 \leq a \leq 9)$；
  - 将上一位单独划分，有 $G_{10, s_{i-1}}=s_{i-1}$；
  - 将剩下两个 $\min$ 转移，有 $G_{11,10}=0,G_{a,11}=a(1 \leq a \leq 9),G_{10,11}=s_{i-1}$；
  - 其它位置上的值都是 $+\infty$。

若定义 $v_0 = (\overbrace{+\infty, \cdots, +\infty}^{9\text{ }个}, +\infty, 0)$，不难验证 $v_{i-1}g_i=v_i$。

### 区间查询部分

此时，问题变为：对所有长度为 $k$ 的连续子区间，求区间矩阵积。  
在此之前先别急着写数据结构，因为你会发现：你无论如何都需要做至少 $n$ 次矩阵乘法，也就是说时间复杂度至少有 $\Theta(n\times A^3)$，这里 $A=11$ 是矩阵大小。这显然难以通过 2 秒的时间限制。  
但是，若你仔细观察上文 $g_i$ 的定义，你会发现它事实上是稀疏矩阵，有效值是 $\Theta(A)$ 级别的。如果我们调换枚举顺序为 ikj，并且忽略所有满足 $G_{i,k}=+\infty$ 的位置，单次乘法的时间复杂度可以变成 $\Theta(A^2)$。  

此时我们可以想到使用线段树维护，但当 $k=n$ 时你一定会对 $3n$ 个非叶子节点做一次矩阵乘法，对其他情况，再加上查询则再有 $\Theta((n-k)\log n)$ 次矩阵乘法，只需取 $k = \dfrac{n}{2}$ 就可发现共有约 $3n-1+k\log n$ 次（必须的）矩阵乘法，仍然难以通过。   

我们重新审视题目中的区间询问，发现它们都有相同长度。这启发我们将每 $k$ 个矩阵分为一块，对每块都算出前后缀积，查询时要么查询整块，要么拼接前后缀即可。  
以上方法做了不多于 $2n+2(n-k+1)$ 次矩阵乘法，足以通过本题。

## [代码实现](https://codeforces.com/contest/2004/submission/320484462)

为了实现方便，矩阵是 0-indexed 的。

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

constexpr int _0 = 0x3f3f3f3f, _1 = 0;

template <int N, int M = N>
struct Matrix {
  Matrix() {
    for (int i = 0; i < N; ++i) std::fill(data[i], data[i] + M, _0);
  }
  
  int* operator[](std::size_t idx) { return data[idx]; }

  const int* operator[](std::size_t idx) const {
    return const_cast<const int*>(data[idx]);
  }

  void output(int n = N, int m = M) const {
    for (int i = 0; i < n; ++i, putchar('\n'))
      for (int j = 0; j < m; ++j)
        data[i][j] == _0 ? printf("Inf ") : printf("%d ", data[i][j]);
  }

  int data[N][M] = {{}};
};

template <int N>
Matrix<N> unit() {
  Matrix<N> u;
  for (int i = 0; i < N; ++i) u[i][i] = _1;
  return u;
}

template <int N, int M, int P>
Matrix<N, P> operator*(const Matrix<N, M>& a, const Matrix<M, P>& b) {
  Matrix<N, P> c;
  for (int i = 0; i < N; ++i)
    for (int k = 0; k < M; ++k) {
      if (a[i][k] >= _0) continue;
      for (int j = 0; j < P; ++j)
        c[i][j] = std::min(c[i][j], a[i][k] + b[k][j]);
    }
  return c;
}

template <int N, int M>
Matrix<N, M>& operator*=(Matrix<N, M>& a, const Matrix<M>& b) {
  return a = a * b;
}

constexpr int N = 2e5 + 5, A = 11;

int n, k, c[N];
Matrix<A> nm, a[N], pre[N], suf[N];
Matrix<1, A> x;

int mp(int i) { return (i - 1) / k + 1; }
int L(int b) { return (b - 1) * k + 1; }
int R(int b) { return std::min(b * k, n); }

int query(int l) {
  auto x = ::x;
  if ((l - 1) % k) {
    x *= suf[l];
    x *= pre[l + k - 1];
  } else
    x *= pre[R(mp(l))];
  return x[0][10];
}

int main() {
  scanf("%d %d", &n, &k);
  for (int c = 0; c < 9; ++c) nm[c][c] = nm[c][10] = c + 1;
  x[0][10] = 0;
  nm[10][9] = _1;
  for (int i = 1; i <= n; ++i) {
    char ch;
    scanf(" %c", &ch);
    c[i] = ch - '0' - 1;
    a[i] = nm;
    a[i][9][c[i - 1]] = a[i][9][10] = c[i - 1] + 1;
  }
  for (int i = 1; i <= n; ++i) {
    int bel = mp(i);
    pre[i] = (i == L(bel) ? a[i] : pre[i - 1] * a[i]);
  }
  for (int i = n + 1; --i;) {
    int bel = mp(i);
    suf[i] = (i == R(bel) ? a[i] : a[i] * suf[i + 1]);
  }
  for (int i = 1; i + k - 1 <= n; ++i) printf("%d ", query(i));
}
```

---

## 作者：piggy123 (赞：3)

究竟是卡在哪一步了呢？？

Observation 1：奇数段的长度不可能超过 $1$。

Proof for Observeation 1：假设偶数段长度为 $x$，奇数段长度为 $y>1$，则将奇数段长度调整为 $1$，最坏情况下长度增加 $1-\frac{10^y-1}{9}\leq 0$。

所以我们有 $dp_{i}$ 表示以 $i$ 结尾的最小长度，容易做到 $\Theta(n)$ 转移。注意到转移的贡献可以均摊到偶数段每个点上，改设 $dp_{i,j}$ 表示钦定当前偶数段所匹配的奇数位为 $j$ 的最小代价（如果 $j=0$ 那么说明这一位是奇数位，下一位必须选），转移容易。

注意到 $j\leq 9$，所以我们可以用矩阵来刻画上面 DP，上各类数据结构维护，可以做到 $w^3\log n$ 单次询问，其中 $w=10$。

注意到上面做法可以做任意区间询问，这没有利用到题目询问区间为滑动窗口的性质。这里有一种做法：将原序列按 $k-1$ 为块长分块，预处理块内前缀积与后缀积，由于询问长度 $=k$，必定跨块，所以可以一次矩阵乘法求得答案。复杂度 $\Theta(w^3n)$。

官方题解中使用了一个双栈模拟队列的 trick，实际上在这里并不适用。这一 trick 一般适用于维护合并复杂度较高、插入复杂度较低且答案容易合并的结构，比如背包、线段树。但是这题求答案仍然需要一次矩阵乘法，答案并不容易合并，所以使用这一 trick 和上面做法没有本质区别。

---

## 作者：yshpdyt (赞：2)

## 题意

给定长为 $2\le n\le2\times10^5$ 的纯数字不含 `0` 字符串 $s$ 和 $k$，你需要对 $s$ 的每个长为 $k$ 的连续子串 $t$ 求出 $f(t)$：

$f(t)$ 的含义为：将 $t$ 分成 $2p$ 份连续子串 $t_1,t_2,\cdots ,t_{2p}$，记 $f(t)$ 的值为，对于所有 $i\le p$，写 $t_{2i-1}$ 次字符串 $t_{2i}$ 后拼接起来的字符串的最小长度。

即求出：$$f(t)=\min\limits_{\forall t_i,p} \left\{\sum\limits_{i=1}^p t_{2i-1}\times|t_{2i}| \right\}$$

前者为奇数段是字符串对应的数，后者为偶数段是字符串对应的长度。
## Sol

参考了 [这个视频的解法](https://www.bilibili.com/video/BV1KVeAehEVU)。

考虑如果 $k=n$ 的情况如何处理：

有一个比较显然的贪心：奇数段 $t_{2i-1}$ 的长度永远是 $1$，否则答案会更劣。

~~感性理解~~反证法证明，假设存在某个位置使得我们要写 $10x+y$ 次长为 $l$ 的段，得到的长度是 $(10x+y)l$，如果考虑把 $10x+y$ 的最后一位 $y$ 分配给 $l$，得到的新长度为:
$$x(l+1)=xl+x< xl+9xl<10xl+yl=(10x+y)l$$


知道了奇数段只能选一个就很好考虑了，设 $f_i$ 表示考虑前 $i$ 个位置，钦定 $i$ 位置为偶数段的最后一位，即 $i+1$ 为奇数段，不难得到转移：

$$f_i=\min_{j<i}\left\{f_j+s_{j+1}\times (i-j+1)\right\}$$

这样做是 $O(n^2)$ 的，注意到奇数段受到 $j$ 的限制，不好分离贡献，考虑倒着转移，使奇数段和当前转移的 $i$ 绑定，该变状态为 $f_i$ 表示考虑了 $[i,n]$ 位，选择 $i$ 位为奇数段的最小答案：

$$f_i=\min_{i<j} \left\{f_{j+1}+s_{i}\times(j-i)\right\}=\min_{i<j} \left\{f_{j+1}+j\times s_i\right\}-i\times s_{i}$$

由于 $s_i\in [1,9]$，所以可以记录 $g_{s_i}=\min_{i<j}\left\{f_{j+1}+j\times s_i\right\}$，转移变成 $f_i=g_{s_i}-i\times s_i$，这样复杂度是 $O(n)$ 的，带个 $9$ 的常数。

考虑 $k$ 的限制，注意到我们的转移方式比较固定且具有结合律（可以先转移左边再转移右边，再用右边的 $g_i$ 更新左边，与从右到左依次更新效果一样），可以用广义矩阵乘法，改 $*/+$ 操作为 $\min/+ $，需要维护 $f_i$ 和对应的 $g_{s_i}$，即维护 $10\times 10$ 大小的矩阵：

考虑 $i$ ，$s_i=5$ 时矩阵 $A_i$ 的样子，使 $A_{mid+1,r}$ 右乘一个 $A_{l,mid}$ 可以得到 $A_{l,r}$。

$$
A_i=\begin{bmatrix}
+\infty &i &2 i &3 i &4 i&5 i&6 i&7 i&8i &9i\\
+\infty&0&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&\\
+\infty&+\infty&0&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&\\
+\infty&+\infty&+\infty&0&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&\\
+\infty&+\infty&+\infty&+\infty&0&+\infty&+\infty&+\infty&+\infty&+\infty&\\
-s_i\times i&+\infty&+\infty&+\infty&+\infty&0&+\infty&+\infty&+\infty&+\infty&\\
+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&0&+\infty&+\infty&+\infty&\\
+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&0&+\infty&+\infty&\\
+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&0&+\infty&\\
+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&+\infty&0&\\
\end{bmatrix}
$$

解释一下这样填的意义：
- $(0,0)$ ：即此时的 $f_i$，由于此时只有一个元素，所以没有答案填 $+\infty$。
- $(0,j)$ ：即此时的 $g_j$，此时候选只有 $i$，而 $f_{i+1}=0$，所以就是 $i\times j$。
- $(j,j)$ ：转移时 $g_j$ 不更新的情况，需要保证仍然可以取 $g_j$。
- $(0,s_i)$ ：转移时得到 $f_i$ 的答案需要 $-i\times s_i$。

手摸一次矩阵乘法后即可发现转移方式。

考虑得到矩阵后如何计算答案，可以使用分块，块长为 $k$，维护块内前缀矩乘 $pre_i$ 和后缀矩乘 $suf_i$。
$$pre_i=A_i\times pre_{i-1}$$

$$suf_i=suf_{i+1} \times A_i$$


对于考虑计算 $[i-k+1,i]$ 时的答案为 $A_{i-k+1,i}$：
- $i \equiv 0\pmod k$ ，答案为 $suf_i$
- 其它情况，答案为 $A_{i-k+1,i}=A_{kp+1,i}\times A_{i-k+1,kp}=pre_i\times suf_{i-k+1}$。

时间复杂度 $O(nm^3)$，$m$ 是矩阵的大小。
##  Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;

ll n,k,fl;
string s;

struct mx{
    ll n,m;
    ll f[11][11];
    void clear(ll x){
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                f[i][j]=x;
            }
        }
    }
    void build(ll x,ll y,ll fl){
        n=x,m=y;
        clear(fl);
    }  
    void reset(){
        clear(0);
        for(int i=0;i<=n;i++)f[i][i]=1;
    }
    friend mx operator*(const mx &a,const mx &b){
        mx c;
        c.build(a.n,b.m,inf);
        for(int k=0;k<=a.m;k++){
            for(int i=0;i<=a.n;i++){
                for(int j=0;j<=b.m;j++){
                    if(i==0&&j==9&&fl)cout<<k<<" "<<a.f[i][k]<<" "<<b.f[k][j]<<" "<<c.f[i][j]<<endl;
                    c.f[i][j]=min(c.f[i][j],a.f[i][k]+b.f[k][j]);
                }
            }
        }
        return c;
    }
    friend mx operator+(const mx &a,const mx &b){
        mx c;
        c.build(a.n,a.m,0);
        for(int i=0;i<=a.n;i++){
            for(int j=0;j<=a.m;j++){
                c.f[i][j]=(a.f[i][j]+b.f[i][j]);
            }
        }
        return c;
    }
    void wrt(){
        cout<<"["<<n<<"*"<<m<<"]"<<endl;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                cout<<f[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}le[N],ri[N],a[N];
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>k>>s;
    s=" "+s;
    for(int i=1;i<=n;i++){
        a[i].build(9,9,inf);
        ll x=s[i]-'0';
        for(int j=1;j<=9;j++){
            a[i].f[0][j]=j*i;
            a[i].f[j][j]=0;
        }
        a[i].f[x][0]=-x*i;   
    }
    ll m=(n-1)/k+1;
    for(int i=1;i<=m;i++){
        ll l=(i-1)*k+1,r=min(i*k,n);
        le[l]=a[l],ri[r]=a[r];
        for(int j=l+1;j<=r;j++)le[j]=a[j]*le[j-1];
        for(int j=r-1;j>=l;j--)ri[j]=ri[j+1]*a[j];
        ri[l].wrt();
    }
    for(int i=k;i<=n;i++){
        if(i%k==0)cout<<le[i].f[0][0]<<" ";
        else cout<<(le[i]*ri[i-k+1]).f[0][0]<<" ";
    }
    return 0;
}
//499 9864 1 312
//499 9864 1 312

```

---

## 作者：forest114514 (赞：1)

感觉这题单独任何一个部分没有 *3200，但是 VP 时一直卡着某个点结束后光速补了，说明全部想清楚还是比较困难的。

先考虑单组询问，首先最暴力的 $O(n^3)$ DP 就是直接枚举 $(t_{2i-1},t_{2i})$ 的段和段内怎么划分，然后注意到其实 $\forall i,t_{2i-1}=1$ 即重复次数不会超过 $10$ 次，证明的话就是如果存在一个超过两位的数把重复次数变成一位发现一定不劣，然后就能优化到 $O(n^2)$ 了。

发现每个数的贡献只和重复次数有关而且独立，所以考虑一个类轮廓线的转移，就是设 $f_{i,c}$ 表示 $i-1$ 延伸过来的段的重复次数是 $c$ 的时候的最小长度，特殊的 $c=0$ 的时候就是 $i-1$ 是一段的末尾（就是这个小小的转化直接卡了我一万年），转移是容易的，显然从 $f_{i-1,?}$ 处转移过来，那么单次 DP 就优化到了 $O(nc),c=10$ 了。

对所有长为 $k$ 的区间做的话首先注意到 $f_{i}$ 只从 $f_{i-1}$ 处转移，显然可以矩阵快速幂优化，但是直接线段树查询区间矩阵乘积的话 $O(nc^3\log n)$ 过不去。但注意到询问区间端点单增，显然可以双指针，但是你发现区间矩阵乘积难以删除但是可以拆成两个区间合并，就套个不删双指针 baka's trick 即可（~~虽然直接分块简单好懂，不过 wtcl 没想到）~~，时间复杂度 $O(nc^3),c=10$。

code：

```cpp
const int N=2e5+100;
int n,k,a[N];
string s;
struct Matrix{
	int s[10][10];
	Matrix(){
		rep(i,0,9) rep(j,0,9) s[i][j]=inf;
	}
}T[N],I,F,L[N],R;
Matrix operator *(const Matrix &A,const Matrix &B){
	Matrix C;
	rep(i,0,9)  rep(k,0,9) rep(j,0,9) C.s[i][j]=min(C.s[i][j],A.s[i][k]+B.s[k][j]);
	return C;
}
Matrix getf(int c){
	Matrix C;
	rep(i,1,9) C.s[i][i]=i,C.s[i][0]=0;
	C.s[0][c]=c;
	return C;
}
int l,r,mid;
void rebuild(){
	mid=l+r>>1;
	L[mid+1]=R=I;
	per(i,mid,l) L[i]=T[i]*L[i+1];
	rep(i,mid+1,r) R=R*T[i];
}
signed main(){
	read(n,k);
	cin>>s;s=' '+s;
	rep(i,1,n) T[i]=getf(s[i]-'0');
	if(k==2){
		rep(i,1,n-1) write(s[i]-'0',' ');return 0;
	}
	rep(i,0,9) I.s[i][i]=0;
	F.s[0][0]=0;
	l=1,r=k-1;
	rebuild();
	rep(i,1,n-k+1){
		R=R*T[++r];
		Matrix res=F*L[l]*R;
		write(res.s[0][0],' ');
		if(l<n-k+1){
			++l;if(l>mid) rebuild();
		}
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution

先考虑 $k=n$ 怎么做。

不难注意到一个性质：对于 $t$ 的所有奇数位置 $x$，都满足 $\vert t_x\vert=1$，证明很简单，这里就不证了。

然后考虑 $\text{DP}$，设 $f_{x,y}$ 表示考虑 $s$ 的前 $x$ 个位置，$t$ 的上一个奇数位置为 $y$ 的答案，但是这样设计状态不太好限制每个偶数位置的串都非空，考虑再令 $f_{x,0}$ 表示 $x$ 为一个偶数位置的串的结尾的答案，对于 $f_{x,y}(y\neq0)$ 我们强制让 $x$ 不为一个偶数位置的串的结尾。

这样转移就很简单了：

+ 对于下一个位置为奇数位置的串时，转移就为 $f_{x,0}\to f_{x+1,s_{x+1}}$。
+ 对于下一个位置为偶数位置的串的结尾时，转移就为 $f_{x,y}\to f_{x+1,0}+y$。
+ 对于下一个位置为偶数位置的串中不为结尾的位置时，转移就为 $f_{x,y}\to f_{x+1,y}+y$。

再考虑 $k\neq n$ 时怎么做。

首先对于 $\text{DP}$，我们可以用矩阵来维护，一次转移就相当于乘（这里是 $(+,\min)$ 乘法）一个转移矩阵。

那么这样对于一个询问就相当于查询这个区间的矩阵的乘积，由于 $(+,\min)$ 矩阵乘法不能求逆，且区间单调递增，考虑不带删尺取，直接这样做时间复杂度为 $O(10^3\times n)$，就已经能过了。

实际上这里由于转移矩阵很稀疏，对于在队尾插入操作，由于转移矩阵不为 $+\infty$ 的位置就只有 $19$ 个，可以优化到 $O(10^2\times n)$。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
const int N=2e5+1;
int n,m; char s[N];

struct custom_hash
{
	static uint64_t splitmix64(uint64_t x) {
		x+=0x9e3779b97f4a7c15;
		x=(x^(x>>30) )*0xbf58476d1ce4e5b9;
		x=(x^(x>>27) )*0x94d049bb133111eb;
		return x^(x>>31);
	}
	size_t operator() (uint64_t x) const {
		static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x+FIXED_RANDOM);
	}
};
int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
struct Matrix
{
	int a[10][10];
	Matrix() { memset(a,0x3f,sizeof a); }
	Matrix friend operator +(Matrix a,Matrix b) //右乘单点矩阵
	{
		Matrix c;
		for (int i=0;i<10;i++)
			for (int j=0;j<10;j++) {
				c.a[i][j]=min(a.a[i][j]+b.a[j][j],a.a[i][0]+b.a[0][j]);
				c.a[i][0]=min(c.a[i][0],a.a[i][j]+b.a[j][0]);
			}
		return c;
	}
	Matrix friend operator -(Matrix a,Matrix b) //左乘单点矩阵
	{
		Matrix c;
		for (int i=0;i<10;i++)
			for (int j=0;j<10;j++) {
				c.a[i][j]=min(a.a[i][j]+b.a[i][i],a.a[0][j]+b.a[i][0]);
				c.a[0][j]=min(c.a[0][j],a.a[i][j]+b.a[0][i]);
			}
		return c;
	}
}base[10];

namespace Queue
{
	stack<pair<Matrix,Matrix> > suf,pre;
	void push(Matrix val) {
		if (pre.empty() ) pre.push({val,val});
		else pre.push({pre.top().first+val,val});
	}
	void pop()
	{
		if (suf.empty() ) {
			suf.push({pre.top().second,pre.top().second}),pre.pop(); while (!pre.empty() )
			suf.push({suf.top().first-pre.top().second,pre.top().second}),pre.pop();
		}
		suf.pop();
	}
	int calc(int ans=INT_MAX) {
		if (suf.empty() ) return pre.top().first.a[0][0]; for (int i=0;i<10;i++)
		ans=min(ans,suf.top().first.a[0][i]+pre.top().first.a[i][0]); return ans;
	}
}
main()
{
	n=read(),m=read(),scanf("%s",s);
	for (int i=1;i<10;i++) {
		for (int j=1;j<10;j++)
		base[i].a[j][j]=base[i].a[j][0]=j;
		base[i].a[0][i]=0;
	}
	for (int i=0;i<n;i++) {
		if (i>=m) Queue::pop();
		Queue::push(base[s[i]&15]);
		if (i>=m-1) printf("%lld ",Queue::calc() );
	}
	return 0;
}
```

---

