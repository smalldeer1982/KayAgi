# Dexterina’s Lab

## 题目描述

Dexterina 和 Womandark 从认识开始就是死对头。 因为她们都是超级聪明的少女，她们总是试图用和平和非暴力的方式解决争端。 他们给对方带来了很多挑战，他们的分数相等，他们都想在各种游戏中打败对方。 这一次，Dexterina 挑战 Womadark 来玩 一个叫做nim的游戏。

nim 是一个双人游戏，玩家轮流从不同堆中拿走东西。 在每一回合中，玩家必须拿走至少一个东西。 不能转身的玩家就输了。 根据他们的协议，桩的大小是随机选择范围[0，x ]。 每一堆的大小都是从游戏开始前已知的同一个概率分布中独立取得的。

Womandark想出了一个全新的主意来阻挠Dexterina的计划，所以她没有太多的空余时间。 她给了你一些关于如何打扮得漂漂亮亮的建议，作为交换，你要帮助她在nim游戏中取胜。 你的任务是告诉她，根据上面的规则，第一个玩家获胜的概率是多少。

## 样例 #1

### 输入

```
2 2
0.500000 0.250000 0.250000
```

### 输出

```
0.62500000
```

# 题解

## 作者：teylnol_evteyl (赞：1)

## 题意描述

一个有 $n$ 堆石子的 nim 游戏，每堆石子的个数在范围 $[0,x]$ 内，给定每堆石子的个数是 $i$ 的概率 $P_i$，求最优先手策略下先手获胜的概率。

## 题目分析

nim 游戏中，先手必胜的充要条件是石子堆数的异或和不为 $0$。考虑递推，设 $f_{i,j}$ 表示前 $i$ 堆石子异或和为 $j$ 的概率，则 $f_{0,0}=1$，$f_{i,j}=\sum_{k=0}^{2^7}f_{i-1,k}P_{k\oplus j}$，最终答案为 $1-f_{n,0}$。可以用矩阵快速幂优化递推。时间复杂度 $O(m^3\log n)$。

## 参考代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 130;

int n, m;
double p[N];
double a[N][N], c[N][N], t[N][N];

void mul(double a[][N], double b[][N], double c[][N])
{
	memset(t, 0, sizeof t);
	for(int i = 0; i < m; i ++ )
		for(int j = 0; j < m; j ++ )
			for(int k = 0; k < m; k ++ )
				t[i][k] += a[i][j] * b[j][k];
	memcpy(c, t, sizeof t);
}
void ksm(int k)
{
	c[0][0] = 1;
	while(k)
	{
		if(k & 1) mul(a, c, c);
		mul(a, a, a);
		k >>= 1;
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= m; i ++ ) scanf("%lf", &p[i]);
	m = 1 << 7;
	for(int i = 0; i < m; i ++ )
		for(int j = 0; j < m; j ++ )
			a[i][j] = p[i ^ j];
	
	ksm(n);
	printf("%.10lf\n", 1 - c[0][0]);
	return 0;
}
```

---

## 作者：jhdonghj (赞：1)

# 题意

$n$堆石子，每堆石子的个数在$[0,x]$之间根据给出的概率分布$P(X)$随机，问最后先手获胜的概率。

# 题解

这是一个经典的$Nim$游戏，有如下引理：$n$堆石子先手获胜的充要条件是$\bigoplus\limits_{i=1}^na_i\neq0$。可以用$SG$函数证明，不会$SG$函数的请出门右转模板区。

不考虑$n$的范围限制，显然我们可以使用$DP$解决该问题，令$f_{i,j}$为前$i$堆石子异或和为$j$的概率，有转移方程$f_{i,j}=\sum\limits_{k=0}^{127}f_{i-1,k}P(j\oplus k)$在$O(nk)$的时间复杂度内解决该问题。

观察到显然实际上这个转移方程可以改写为两个矩阵的乘积，即$F=F'*A$，其中$A$矩阵为转移矩阵，$F,F'$矩阵分别为目前答案矩阵和上一次答案矩阵，根据矩乘的定义式我们可以推出$\forall i,j\in[0,127],A_{i,j}=P(i\oplus j)$，然后根据矩乘运算的结合律$F_{ans}=F_{init}A^n$，于是我们就可以用矩阵快速幂在$O(127^3logn)$的时间复杂度内解决该问题。

总的来说，这题还是挺套路的，写出$DP$转移方程然后用矩乘改写就做完了，应该算是这类题目里的基础题吧。

# Code

```c++
#include <bits/stdc++.h>
using namespace std;
using db = double;

const int B = 128; int n, x; db p[130];
struct Matrix {
    db a[130][130];
    Matrix() { memset(a, 0, sizeof(a)); }
    void init() { for(int i = 0; i < B; i++) a[i][i] = 1; }
} A;
Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix res;
    for(int i = 0; i < B; i++)
        for(int j = 0; j < B; j++)
            for(int k = 0; k < B; k++)
                res.a[i][j] += a.a[i][k] * b.a[k][j];
    return res;
}
Matrix qpow(Matrix a, int b) {
    Matrix res; res.init();
    while(b) {
        if(b & 1) res = res * a;
        a = a * a, b >>= 1;
    }
    return res;
}
signed main() {
    scanf("%d %d", &n, &x);
    for(int i = 0; i <= x; i++)
        scanf("%lf", &p[i]);
    for(int i = 0; i < B; i++)
        for(int j = 0; j < B; j++)
            A.a[i][j] = p[i ^ j];
    A = qpow(A, n), printf("%.10lf\n", 1 - A.a[0][0]);
    return 0;
}
```



---

## 作者：1234567890sjx (赞：0)

跳到的。考虑设 $f_{i,j}$ 表示前 $i$ 个数，异或和为 $j$ 的概率。因为 Nim 游戏若所有元素异或后为 $0$ 则先手必败否则先手必胜，所以答案就是 $1-f_{n,0}$。

又因为 $n$ 很大但是 $x$ 很小，所以使用矩阵快速幂优化转移。时间复杂度为 $O(x^3\log n)$。

```cpp
struct qwq {
    double a[128][128];
    qwq () {
        memset(a, 0, sizeof a);
    }
};
qwq operator*(const qwq &l, const qwq &r) {
    qwq a;
    for (int k = 0; k < 128; ++k)
        for (int i = 0; i < 128; ++i)
            for (int j = 0; j < 128; ++j)
                a.a[i][j] += l.a[i][k] * r.a[k][j];
    return a;
}
qwq ksm(qwq a, int b) {
    if (b == 1) return a;
    qwq c = ksm(a, b >> 1);
    c = c * c;
    if (b & 1) c = c * a;
    return c;
}
double p[128];
void run() {
    int n = read(), x = read();
    for (int i = 0; i <= x; ++i) cin >> p[i];
    qwq m1;
    for (int i = 0; i < 128; ++i)
        for (int j = 0; j < 128; ++j)
            m1.a[i][j] = p[i ^ j];
    qwq m2 = ksm(m1, n);
    printf("%.20lf\n", 1 - m2.a[0][0]);
}
```

---

## 作者：ZLCT (赞：0)

# CF717D Dexterina’s Lab
## 题目翻译
给定 $n$ 堆石子，每堆的个数从 $[0,x]$ 中选取，其中有 $i$ 个石子的概率是 $P_i$ 求进行 Nim 先手必胜概率。
## 关于 Nim
这个游戏我们都很熟悉，它的先手必胜的充要条件为各堆石子的异或和不为 $0$。
## 最暴力的思路
我们暴力地利用先手必胜概率 $=$ 先手必胜局面数 $\div$ 总局面数，暴力地枚举每一堆石子的数量，算出有多少先手必胜的局面。\
但是这样的时间复杂度会来到惊人的 $O(x^n)$。
## 较为优化的思路
因为观察到每堆石子是相互独立的，这满足 dp 的无后效性，于是我们考虑 dp。\
设 $f_{i,j}$ 表示取前 $i$ 堆石子，所有石子堆的异或和为 $j$ 的概率。那么答案就是 $1-f_{n,0}$。\
转移时我们直接枚举这一堆石子数量，那转移就是 $f_{i,j}=\sum\limits_{k=0}^{127(异或可能大于 x)}P_k\times f_{i-1,j\oplus k}$\
想法确实很丰满，这样的复杂度也就是 $O(nx)$，比刚才好多了，但是看到题目 $n\le 10^9$，这种方法也不可以。
## 最终思路
注意到每次转移都只与前面一次转移有关，而每次转移的转移方程都是固定的，于是我们可以考虑矩阵加速。\
具体的，我们开 $127$ 维的状态矩阵和转移矩阵分别表示取石子堆异或和为 $i$ 时的概率和每次转移时转移的方程。\
这样的时间复杂度就变成了 $O(x^3\log n)$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
double p[151];
struct matrix{
    double G[151][151];
    void clear(){
        memset(G,0,sizeof(G));
    }
    void init(){
        for(int i=0;i<133;++i)G[i][i]=1;
    }
    friend matrix operator *(matrix &a,matrix &b){
        matrix res;res.clear();
        for(int k=0;k<=127;++k){
            for(int i=0;i<=127;++i){
                for(int j=0;j<=127;++j){
                    res.G[i][j]+=a.G[i][k]*b.G[k][j];
                }
            }
        }
        return res;
    }
}a;
matrix ksm(int b){
    matrix res;res.clear();
    res.G[0][0]=1;
    while(b){
        if(b&1){
            res=a*res;
        }
        b>>=1;
        a=a*a;
    }
    return res;
}
signed main(){
    cin>>n>>x;
    for(int i=0;i<=x;++i){
        cin>>p[i];
    }
    for(int i=0;i<=127;++i){
        for(int j=0;j<=127;++j){
            a.G[i][j]=p[i^j];
        }
    }
    matrix st=ksm(n);
    printf("%.6lf\n",1.000000-st.G[0][0]);
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

[博弈论 if you need](https://www.luogu.com.cn/article/00mwsr77)

首先 nim 游戏的结论是先手必败当且仅当异或和为 $0$。

因此，我们可以定义 $dp_{i,j}$ 表示前 $i$ 堆异或起来答案是 $j$ 的概率。

时间复杂度是 $O(nx^2)$ 的。

但是可以考虑矩阵加速，所以时间复杂度就是 $O(x^3\log n)$。

[code link](https://codeforces.com/contest/717/submission/259113555)

---

