# [GCJ 2008 #1A] Numbers

## 题目描述

在本题中，你需要找出数字 $(3 + \sqrt{5})^n$ 小数点前的最后三位数字。

例如，当 $n = 5$ 时，$(3 + \sqrt{5})^5 = 3935.73982\dots$，答案是 $935$。

当 $n = 2$ 时，$(3 + \sqrt{5})^2 = 27.4164079\dots$，答案是 $027$。

## 说明/提示

**数据范围**

- $1 \leq T \leq 100$

**小数据集（15 分，测试点 1 - 可见）**

- $2 \leq n \leq 30$

**大数据集（35 分，测试点 2 - 隐藏）**

- $2 \leq n \leq 2\times10^{10}$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5
2```

### 输出

```
Case #1: 935
Case #2: 027```

# 题解

## 作者：RAY091016 (赞：3)

### 1. 题意解释

求出 $(3+\sqrt5)^n$ 的整数部分的后三位。

### 2. 思路

显然不可以 double 直接暴力算，精度会炸。

高精度吗？出门右转[高精度开根](https://www.luogu.com.cn/problem/P2293)，看看什么难度。

我们考虑拆开括号，容易发现 $(3+\sqrt5)^n=A_n+B_n\sqrt5$，其中 $A_n,B_n$ 都为整数。

同理有 $(3-\sqrt5)^n=A_n-B_n\sqrt5$。

故我们有 $(3+\sqrt5)^n+(3-\sqrt5)^n=2A_n$。

移项，有 $(3+\sqrt5)^n=2A_n-(3-\sqrt5)^n$。

而我们知道 $2^2=4<5<9=3^2$，故有 $2<\sqrt5<3$。

故有 $0<3-\sqrt5<1$。

因此 $0<(3-\sqrt5)^n<1$。

所以我们知道 $(3+\sqrt5)^n$ 的整数部分即为 $2A_n-1$。

考虑如何求出 $A_n$。

我们不难发现 $(3+\sqrt5)(A_i+B_i\sqrt5)=A_{i+1}+B_{i+1}\sqrt5$。

拆开括号即得 $3A_i+5B_i=A_{i+1},A_i+3B_i=B_{i+1}$。

不难想到矩阵加速。

我们构造矩阵 $\begin{bmatrix}3&5\\1&3\end{bmatrix}$，不难发现 $\begin{bmatrix}A_i\\B_i\end{bmatrix}\times\begin{bmatrix}3&5\\1&3\end{bmatrix}=\begin{bmatrix}3A_i+5B_i\\A_i+3B_i\end{bmatrix}=\begin{bmatrix}A_{i+1}\\B_{i+1}\end{bmatrix}$。

而我们又有 $A_0=1,B_0=0$。

故而有 $\begin{bmatrix}1\\0\end{bmatrix}\times\begin{bmatrix}3&5\\1&3\end{bmatrix}^n=\begin{bmatrix}A_n\\B_n\end{bmatrix}$。

至此这道题就做完了，记得注意输出格式。

### 3. 代码实现

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1000;
int n,t,tot=1;
struct matrix{
	int a[5][5];
};
matrix operator*(matrix A,matrix B){
	matrix C;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=2;j++){
			int cnt=0;
			for(int k=1;k<=2;k++){
				cnt=(cnt+A.a[i][k]*B.a[k][j])%mod;
			}
			C.a[i][j]=cnt;
		}
	}
	return C;
}//矩乘
matrix qpow(matrix base,int up){
	matrix ret;
	memset(ret.a,0,sizeof ret.a);
	for(int i=1;i<=2;i++){
		ret.a[i][i]=1;
	}
	while(up){
		if(up&1){
			ret=ret*base;
		}
		base=base*base;
		up>>=1;
	}
	return ret;
}//矩阵快速幂
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<"Case #"<<tot<<": ";
		tot++;
		matrix A;
		A.a[1][1]=3,A.a[1][2]=5,A.a[2][1]=1,A.a[2][2]=3;//转移矩阵
		matrix tmp=qpow(A,n);
		int ans=(tmp.a[1][1]*2-1)%mod;//最后乘上初始矩阵算答案
		if(ans>=100&&ans<=999){
			cout<<ans<<endl;
		}
		else if(ans>=10&&ans<=99){
			cout<<"0"<<ans<<endl;
		}
		else{
			cout<<"00"<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：__coderyc__ (赞：1)

## 题意
求 $(3+\sqrt{5})^n$ 的小数点最后三位数。

## 思路
可以递推求解，但注意到数据范围很大，所以先推导再加速。

令 $a_n=(3+\sqrt{5})^n$，又 $0\le (3-\sqrt{5})^n\le 1$，所以就有 $(3+\sqrt5)^n = a_n - (3-\sqrt5)^n$，则 $a_n$ 的整数部分为 $ a_n - 1$。

因为 $a_n-3=\sqrt5$，那么 $(a_n-3)^2=5$，则 $ a_n
^2-6t+4=0$，其中 $3+\sqrt{5}$ 以及 $3-\sqrt{5}$ 为方程的解。

即可得出递推方程：

$$
a_n = \begin{cases}
  2 &  n=0 \\
  6 & n=1 \\
  6a_{n-1} - 4a_{n-2} & \text{otherwise.}
\end{cases}
$$

定义 $M = \begin{bmatrix} 6 & -4 \\ 1 & 0 \end{bmatrix}$，那么我们只需计算矩阵 $M$ 的 $n-1$ 次幂，然后乘以向量 $(6,2)^T$，得到的第一个元素就是 $a_n$。

再计算除以 $1000$ 的余数即可。

如果计算为负数，加上 $1000$ 即可。

使用矩阵快速幂进行计算，这里不多解释。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1000;
struct Matrix {
    long long m[2][2];
};
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix res;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            long long t = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j];
            t %= mod;
            if (t < 0) t += mod;
            res.m[i][j] = t;
        }
    }
    return res;
}
Matrix power_matrix(Matrix base, long long exp) {
    Matrix res;
    res.m[0][0] = 1; res.m[0][1] = 0;
    res.m[1][0] = 0; res.m[1][1] = 1;
    while (exp) {
        if (exp & 1) 
            res = multiply(res, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return res;
}
int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        long long n;
        scanf("%lld", &n);
        Matrix M;
        M.m[0][0] = 6; M.m[0][1] = -4;M.m[1][0] = 1; M.m[1][1] = 0;
        Matrix M_exp = power_matrix(M, n-1);
        long long x = (M_exp.m[0][0] * 6 + M_exp.m[0][1] * 2) % mod;
        if (x < 0) x += mod;
        long long result = (x - 1) % mod;
        if (result < 0) result += mod;
        printf("Case #%d: %03lld\n", t, result);
    }
    return 0;
}
```

---

## 作者：chen_zhe (赞：1)

本题解来自于[《挑战程序设计竞赛》](https://www.luogu.com.cn/training/813583)。

---

如果用 double 来计算 $(3 + \sqrt{5})^{n}$ ，精度显然是不够的。虽然使用 Java 中支持高精度小数的 BigDecimal 可以通过 Small 测试数据，但是，要通过 Large 测试数据，就必须把 $\sqrt{5}$ 的值计算到大约 $n$ 位精度，因此朴素的方法是无法求出答案的。其实，经过仔细分析可以发现，这个问题不需要求出 $\sqrt{5}$ 的值也可以求解。

首先将 $(3 + \sqrt{5})^{n}$ 展开之后可以发现是 $a_{n} + b_{n} \sqrt{5}$ 的形式。同样地，我们有 $(3 - \sqrt{5})^{n} = a_{n} - b_{n} \sqrt{5}$ 。因此，$(3 + \sqrt{5})^{n} + (3 - \sqrt{5})^{n} = 2a_{n}$ 是个整数，其中 $0 < (3 - \sqrt{5})^{n} < 1$ ，这正是解题的关键。由于 $(3 + \sqrt{5})^{n} = 2a_{n} - (3 - \sqrt{5})^{n}$ ，所以 $(3 + \sqrt{5})^{n}$ 的整数部分等于 $2a_{n} - 1$ 。

根据上面的推导，只要高效地求出 $a_{n}$ 就可以解决这个问题了。由于 $(3 + \sqrt{5})^{n+1} = (3 + \sqrt{5})(3 + \sqrt{5})^{n} = (3 + \sqrt{5})(a_{n} + b_{n} \sqrt{5})$ ，我们可以得到 $a_{n}$ 、$b_{n}$ 和 $a_{n+1}$ 、$b_{n+1}$ 的递推关系。

$a_{n+1} = 3a_{n} + 5b_{n}$

$b_{n+1} = a_{n} + 3b_{n}$

$a_{0} = 1$ $b_{0} = 0$

我们可以使用矩阵表示这个递推关系，因此可以使用快速幂运算，在 $O(\log n)$ 的时间内求出 $a_{n}$ 和 $b_{n}$ 。由于只需要最后 $3$ 位，因此运算时 $\bmod 1000$ 就可以了。

```cpp lines=13-13
const int MOD = 1000;

typedef vector<int> vec;
typedef vector<vec> mat;

// 输入
int n;

void solve() {
    mat A(2, vec(2, 0));
    A[0][0] = 3; A[0][1] = 5;
    A[1][0] = 1; A[1][1] = 3;
    A = pow(A, n);
    printf("%03d\n", (A[0][0] * 2 + MOD - 1) % MOD);
}
```

我们称 $a - b\sqrt{n}$ 与 $a + b\sqrt{n}$ 互为共轭。$(a + b\sqrt{n})(a - b\sqrt{n}) = a^2 - nb^2$ ，$(a + b\sqrt{n}) + (a - b\sqrt{n}) = 2a$ ，因此一对共轭的数具有相加或者相乘之后可以得到整数的性质。此外，还有相乘后取共轭和先取共轭再相乘结果相同等良好性质。如果记住这些结论，在解题时往往能比较容易想到解法。

这个问题的输出格式比较特殊，如果不足 $3$ 位则要补足前导 $0$ 。不过因为样例中包含了这种情况，所以如果忘记了也会注意到这个问题。但是也有许多问题的样例并不包含一些特殊情况，需要特别注意。此外，C 和 Java 中都可以通过 `printf("%03d", answer)` 的方法自动补上需要的前导 $0$ 。

---

## 作者：_Null_Ptr (赞：0)

注意到 $(3 + \sqrt{5})^n+(3 - \sqrt{5})^n$ 是一个整数。这是因为 $(3 + \sqrt{5})$ 和 $(3 - \sqrt{5})$ 是共轭的，它们的和或差的幂次展开后，所有包含 $\sqrt{5}$ 的项都会相互抵消，只剩下整数部分。

由于 $0<3-\sqrt{5}<1$，所以 $(3 - \sqrt{5})^n$ 是一个非常小的正数，随着 $n$ 增大，它趋近于 $0$。因此，$(3 + \sqrt{5})^n$ 的整数部分可以近似为 $(3 + \sqrt{5})^n + (3 - \sqrt{5})^n-1$。

关于递推式的推导，不妨设 $(3 + \sqrt{5})^n = x_n + y_n\sqrt{5}$，那么 $(3+\sqrt{5})^{n+1} = (3 + \sqrt{5})^n \times (3+\sqrt{5}) = (3 + \sqrt{5}) \times (x_n + y_n\sqrt{5})$，观察这个式子可以知道

$$x_n+1=3x_n+5y_n \\
  y_n+1=x_n+3y_n
$$

所以可以通过矩阵幂来表达这个关系，下面普及一下矩阵快速幂（[模板](https://www.luogu.com.cn/problem/P3390)）。

矩阵快速幂，顾名思义就是矩阵乘法加上快速幂。先讲快速幂，计算 $a^n$ 就相当于求 $\underbrace{a \times a \cdots \times a}_{n\text{ 个 a}}$。利用分治思想，我们可以不断地把这个式子拆成 $a^\frac{n}{2}\times a^\frac{n}{2}$。

然后我们还可以用二进制优化，举个例子。
$$
3^1 = 3 \\
3^2 = \left(3^1\right)^2 = 3^2 = 9 \\
3^4 = \left(3^2\right)^2 = 9^2 = 81 \\
3^8 = \left(3^4\right)^2 = 81^2 = 6561
$$

因此若要计算 $3^{n}$，我们只需要将对应二进制位为 $1$ 的整系数幂乘起来就行了。

然后是矩阵快速幂，要开一个存储漏单奇数，结果的矩阵，初始为单位矩阵，用其去跟原矩阵相乘，具体实现见代码。

```python
def mtx_mult(A, B, mod): #矩阵乘法
    return [
        [(A[0][0] * B[0][0] + A[0][1] * B[1][0])%mod, (A[0][0] * B[0][1] + A[0][1] * B[1][1])%mod],
        [(A[1][0] * B[0][0] + A[1][1] * B[1][0])%mod, (A[1][0] * B[0][1] + A[1][1] * B[1][1])%mod]
    ]

def mtx_pow(mtx, power, mod):#矩阵快速幂
    res=[[1, 0],[0, 1]]
    base=mtx
    while power>0:
        if power & 1 == True:
            res = mtx_mult(res, base, mod)
        base = mtx_mult(base, base, mod)
        power //= 2
    return res

def solve(n):
    mod=1000
    mtx=[[3, 5], [0, 3]]
    res=mtx_pow(mtx, n, mod)
    return res[0][0]*2%mod-1 

T=int(input())
for i in range(1, T + 1):
    n = int(input())
    res = solve(n)
    print(f"Case #{i}: {res:03d}") #补齐前导0
```

---

