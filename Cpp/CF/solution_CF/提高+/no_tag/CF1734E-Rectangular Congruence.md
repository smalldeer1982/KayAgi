# Rectangular Congruence

## 题目描述

You are given a prime number $ n $ , and an array of $ n $ integers $ b_1,b_2,\ldots, b_n $ , where $ 0 \leq b_i < n $ for each $ 1 \le i \leq n $ .

You have to find a matrix $ a $ of size $ n \times n $ such that all of the following requirements hold:

- $ 0 \le a_{i,j} < n $ for all $ 1 \le i, j \le n $ .
- $ a_{r_1, c_1} + a_{r_2, c_2} \not\equiv a_{r_1, c_2} + a_{r_2, c_1} \pmod n $ for all positive integers $ r_1 $ , $ r_2 $ , $ c_1 $ , and $ c_2 $ such that $ 1 \le r_1 < r_2 \le n $ and $ 1 \le c_1 < c_2 \le n $ .
- $ a_{i,i} = b_i $ for all $ 1 \le i \leq n $ .

Here $ x \not \equiv y \pmod m $ denotes that $ x $ and $ y $ give different remainders when divided by $ m $ .

If there are multiple solutions, output any. It can be shown that such a matrix always exists under the given constraints.

## 说明/提示

In the first example, the answer is valid because all entries are non-negative integers less than $ n = 2 $ , and $ a_{1,1}+a_{2,2} \not\equiv a_{1,2}+a_{2,1} \pmod 2 $ (because $ a_{1,1}+a_{2,2} = 0 + 0 \equiv 0 \pmod 2 $ and $ a_{1,2}+a_{2,1} = 1 + 0 \equiv 1 \pmod 2  $ ). Moreover, the values on the main diagonals are equal to $ 0,0 $ as required.

In the second example, the answer is correct because all entries are non-negative integers less than $ n = 3 $ , and the second condition is satisfied for all quadruplets $ (r_1, r_2, c_1, c_2) $ . For example:

- When $ r_1=1 $ , $ r_2=2 $ , $ c_1=1 $ and $ c_2=2 $ , $ a_{1,1}+a_{2,2} \not\equiv a_{1,2}+a_{2,1} \pmod 3 $ because $ a_{1,1}+a_{2,2} = 1 + 1 \equiv 2 \pmod 3 $ and $ a_{1,2}+a_{2,1} = 2 + 1 \equiv 0 \pmod 3  $ .
- When $ r_1=2 $ , $ r_2=3 $ , $ c_1=1 $ , and $ c_2=3 $ , $ a_{2,1}+a_{3,3} \not\equiv a_{2,3}+a_{3,1} \pmod 3 $ because $ a_{2,1}+a_{3,3} = 1 + 1 \equiv 2 \pmod 3 $ and $ a_{2,3}+a_{3,1} = 0 + 1 \equiv 1 \pmod 3  $ .

 Moreover, the values on the main diagonal are equal to $ 1,1,1 $ as required.

## 样例 #1

### 输入

```
2
0 0```

### 输出

```
0 1 
0 0```

## 样例 #2

### 输入

```
3
1 1 1```

### 输出

```
1 2 2
1 1 0
1 0 1```

## 样例 #3

### 输入

```
5
1 4 1 2 4```

### 输出

```
1 0 1 3 4
1 4 3 1 0
2 4 1 0 2
1 2 2 2 2
2 2 0 1 4```

# 题解

## 作者：星星与辰 (赞：26)

## 题意
给出一个质数 $n(n\leq 350)$ 和一个长度为 $n$ 的序列 $b_1,b_2,b_3 \dots,b_n$，保证对于 $\forall 1 \leq i \leq n, $ 有 $0\leq b_i \lt n$，试构造一个 $n\times n$ 的矩阵 $a$，满足：

$\bullet$ 对于 $\forall i, j \leq n$，有 $0\leq a_{i,j} \lt n$。

$\bullet$ 对于 $\forall x_1, x_2 ,y_1,y_2\leq n$，有 $a_{x_1,y_1} +a_{x_2,y_2} \not\equiv a_{x_1,y_2} +a_{x_2,y_1}\pmod n$。


$\bullet$ 对于 $\forall i \leq n$，有 $a_{i,i} =b_i$。
## 思路
完整地讲一下我是如何想到怎样构造的。

我们看到每一个条件，尝试去做到满足它们。

看到条件一，显而易见，这个基本上没有限制任何构造，容易满足。

而看到第二个条件的式子，将其转化一下，变为
$$a_{x_1,y_1} -a_{x_1,y_2} \not\equiv a_{x_2,y_1} -a_{x_2,y_2}\pmod n$$

这有什么用呢，事实上，我们将一个原来的矩形两个相对的顶点相加不等的条件变为了两个矩形两个同行的顶点相减不等。

我们知道如果使两个数加上同一个值，他们的差不变，那么如果给原来合法的矩阵某一行全部同时加上一个数，那么得到的矩阵也合法。

有什么用呢？可以帮助我们达成条件三，也就是说如果我们可以在不满足条件三的情况下构造了一个合法的矩阵，那么可以通过给某一行的数字同时加上一个数字来达成条件三。

现在的三个条件就转化成了满足一个条件二即可。

假设我们如果有一个初始矩阵，我们现在考虑如何令它一定合法，为方便考虑，我们的初始矩阵上的每一个数字都是 $0$，即
$$
\begin{matrix}
0 & 0 & 0 &\cdots & 0\\
0 & 0 & 0 &\cdots & 0\\
0 & 0 & 0 &\cdots & 0\\
\vdots & \vdots & \vdots & \ddots & \vdots\\
0 & 0 & 0 &\cdots & 0\\
\end{matrix}
$$

通过我们刚刚转化的式子得，简单点想，满足条件二事实上只需要每一对不在同一行的数字差值不等即可，那我们尝试控制差值，这里给出一种方案，我们可以使第一行差值为 $0$， 使第二行差值为 $1$，使第三行差值为 $2$，以此类推，即使第 $i$ 行的差值为 $i-1$，正好 $n$ 行，我们正好用到差值为 $n-1$ 时停下，也就是说，我们的矩阵现在长这样：
$$
\begin{matrix}
0 & 0 & 0 &\cdots & 0\\
0 & 1 & 2 &\cdots & n-1\\
0 & 2 & 4 &\cdots & 2\times(n-1)\mod n\\
\vdots &\vdots & \vdots &\ddots & \vdots\\
0 & n-1 & 2\times(n-1)\mod n &\cdots &  (n-1)\times(n-1)\mod n \\
\end{matrix}
$$

这时，就有人有疑问了，这样子构造会不会仍不合法，我们定义 $i,j$ 为两个差值，$k$ 为一个系数，那么是否可能有
$\exists i,j,k(i\neq j,0\leq i,j\leq n-1,1\leq k\leq n-1)$ 使得 $k\times (n-i)\equiv k\times(n-j) \pmod n$，比如说 $2\times (8-2)\equiv 2\times(8-6) \pmod n$

No,no,no,不会存在这样的情况，为什么呢？我们发现
$$k\times (n-i)\equiv k\times(n-j) \pmod n\iff k\times(i-j)\equiv 0 \pmod n$$
也就是只有 $i,j$ 的两个差值的差值与 $k$ 的乘积为 $n$ 的倍数时，才可能出现这样的情况，但是
$$\because i\neq j,0\leq i,j\leq n-1,1\leq k\leq n-1$$
$$\therefore 1\leq i-j\leq n-1,1\leq k\leq n-1$$
$$\because n \in \text{primes}$$
$$\therefore \forall 1\leq x,y \leq n-1,x\times y\not\equiv 0\pmod n$$
$$\therefore \forall 1\leq i-j,k \leq n-1,k\times (i-j)\not\equiv 0\pmod n$$

所以我们可以证明这样是一定正确的。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int num=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))num=(num<<1)+(num<<3)+(ch&15),ch=getchar();
	return num;
}
int a[400][400];
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			a[i][j]=(a[i][j-1]+i-1)%n;
			//第i行的差值为i-1
		}
	}
	for(int i=1;i<=n;++i){
		int x=read()-a[i][i];
		//调整矩阵 
		for(int j=1;j<=n;++j){
			a[i][j]=(a[i][j]+x+n)%n;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			printf("%d ",a[i][j]);
		}
		puts("");
	}
}
```

 ### 总结
 这道题的瓶颈主要在于第二个条件的转换，以及条件的化简，对于矩阵的正确性的证明在做题时很容易会漏掉，但是它是值得注意的，做题时应留心。

---

## 作者：c202201 (赞：8)

[题面传送门](https://www.luogu.com.cn/problem/CF1734E)

## 简化题意 

给出一个质数 $ n $ 和一个序列 $ b_1 , b_2 , \cdots , b_n $，构造一个矩阵满足：

1. 所有数在 $ [ 0 , n ) $ 中。
2. $ \forall 1 \leq i \leq n $, 都有 $ a_{i,i} = b_i $ 。
3. 矩阵中任意一个矩形的两组对角上的数之和在模 $ n $ 的值不同。

## 思路

显然对于所有的 $ a < b , c < d $, 都存在 $ a c + b d \not\equiv  a d + b c \pmod n $, 因为 $ n $ 是个质数。  

那我们设四边形的四个点的位置分别为 $ (i_1,j_1),(i_1,j_2),(i_2,j_1),(i_2,j_2) $, 那么一定存在 $ i_1j_1 + i_2j_2 \not\equiv i_1j_2 + i_2j_1 \pmod n $。

那我们就有了一种构造方案，即 $ i $ 行 $ j $ 列放 $ i \times j \mod n$，此时我们只需在满足条件2即可。

可以考虑将每个位置加上一个值，使任意一个矩形依旧存在 $ i_1j_1 + i_2j_2 \not\equiv i_1j_2 + i_2j_1 \pmod n $ 并且 $ a_{i,i} = b_i $。

考虑一下主对角线（即 $ a_{i,i} $）上的值是什么，显然是 $ i \times i $， 要是它变为 $ b_i $， 那让它加上 $ b_i - i \times i $ 即可。我们在看看其他的位置加上 $ b_i - i \times i $ 后的变化，那么对于任意一个四边形，其四个点上的值就分别是 $ i_1j_1+b_{i_1}-{i_1}^2$，$ i_1j_2+b_{i_1}-{i_1}^2 $，$i_2j_1+b_{i_2}-{i_2}^2 $ ，$ i_2j_2+b_{i_2}-{i_2}^2  $，那么就会变成 $ i_1j_1 + i_2j_2 +b_{i_1} +b_{i_2} -{i_1}^2 -{i_2}^2 \not\equiv i_1j_2 + i_1j_2 +b_{i_1} +b_{i_2} -{i_1}^2 -{i_2}^2 \pmod n $，两边同时减去 $ +b_{i_1} +b_{i_2} -{i_1}^2 -{i_2}^2$，就会变成 $ i_1j_1 + i_2j_2 \not\equiv i_1j_2 + i_2j_1 \pmod n$，变回了上那个成立的式子，符合题目要求。

所以答案即为 $i$ 行 $j$ 列填 $i \times j+b_i-i \times i$。 

## 代码 

talking is cheap, show me your code.

```c++
#include <cstdio>
#define il inline
#define int long long
using namespace std;
const int N=355;
int n,b[N],a[N][N];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) a[i][j]=i*j%n;
	for(int i=1;i<=n;++i){
		int c=(b[i]-a[i][i]+n)%n;
		for(int j=1;j<=n;++j) printf("%lld ",(c+a[i][j])%n);
		puts("");
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：4)

> 题意：你需要构造一个 $n \times n$ 的矩阵（$n$ 是**质数**），对角线的值已经给定。满足：对于 $1 \le x < p \le n,1 \le y < q \le n$，$a_{x,y}+a_{p,q} \not\equiv a_{x,q}+a_{p,y} \pmod{n}$。

首先有一个 Basic Trick：对于一个质数 $n$，若 $i \not\equiv j \pmod{n},k \not\equiv 0 \pmod{n}$，则 $ik \not\equiv jk \pmod{n}$。

我们考虑将原式变形为：$a_{x,q}-a_{x,y} \not\equiv a_{p,q}-a_{p,y} \pmod{n}$。那如何联系到上面的结论呢？会发现如果第 $i$ 行满足两两相邻的数之差为 $i$。那么原式就变为了 $x(q-y) \not\equiv p(q-y) \pmod{n}$，这是恒成立的。

所以构造方案为：对于第 $i$ 行，$a_{i,i}=b_{i},a_{i,j}=(a_{i,j-1}+i) \pmod{n}(j \ne i)$。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 360;
int n,a[MAXN][MAXN],b[MAXN];
signed main() {
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> b[i];
	for(int i = 1;i <= n;i++) {
		a[i][i] = b[i];
		for(int j = i - 1;j >= 1;j--) 
			a[i][j] = (a[i][j + 1] + i) % n;
		for(int j = i + 1;j <= n;j++) 
			a[i][j] = (a[i][j - 1] - i + n) % n;
	}
	for(int i = 1;i <= n;i++,puts(""))
		for(int j = 1;j <= n;j++) cout << a[i][j] << " ";
	return 0;
}
```

---

## 作者：FFTotoro (赞：4)

本题需要使用一些数论的特殊性质。

观察题目的第二个条件，如果我们不看第一个条件的话，可以构造出一个矩阵 $A$，其中 $a_{i,j}=i\times j\pmod n$，满足第二个条件。

赛后看了 CF 官方题解，里面阐述了一个定理：只要 $a_{i,j}$ 满足 $ai^2+bij+cj^2+di+ej+f$ 的形式（$a,b,c,d,e,f$ 是整数），且 $b\not\equiv 0\pmod n$，那么这样的矩阵 $A$ 就是满足条件的。所以我们前面的方法是正确的，这个定理的证明可参考 CF 官方题解。

现在我们再来考虑第一个条件。实现之前，先要明白——如果一个矩阵满足第二个条件，那么给其中的某一行或某一列中的全部元素都加上一个定值，那么第二条件**仍然成立**。

到这里解法已经呼之欲出了：对于 $i=1,2,\ldots,n$，**给第 $i$ 行的每一个元素都加上 $b_i-a_{i,i}$**，即可满足两个条件。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n;
    vector<vector<int>> a(n,vector<int>(n));
    vector<int> b(n);
    for(auto &i:b)cin>>i;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j]=i*j%n; // 构造初始矩阵
    for(int i=0;i<n;i++){
        int x=(b[i]-a[i][i]+n)%n; // 经典模加模
        for(int j=0;j<n;j++)
            (a[i][j]+=x)%=n; // 给每一个元素加上差值
    }
    for(int i=0;i<n;i++,cout<<endl)
        for(int j=0;j<n;j++)cout<<a[i][j]<<' ';
    return 0;
}
```

---

## 作者：optimize_2 (赞：2)

## 题意

给定一个质数 $n$（$n \leq 350$） 和一个序列 $b_1, b_2, ..., b_n$（对于 $\forall i$ 有 $0 \leq b_i < n$），你需要构造一个 $n \times n$ 的矩阵 $a$，满足：

 - 对于 $\forall i, j \leq n$ 有 $0 \leq a_{i, j} < n $。

 - 对于 $\forall 1 \leq r_1 \leq r_2 \leq n, 1 \leq c_1 \leq c_2 \leq n$ 有 $a_{r1, c1} + a_{r2, c2} \not\equiv a_{r1, c2} + a_{r2, c1} \pmod n $。
 
 - 对于 $\forall 1 \leq i \leq n, 1 \leq c_1 \leq c_2 \leq n$ 有 $ a_{i, i} = b_i $。

## 题解

一条一条限制分析。

对于第一个没什么好说的，第二个太丑了，用人话讲就是：在矩阵里找一个矩形，满足左上角加右下角不等于左下角加右上角（取模意义下，下同）。

然后移一下项，变成左上角减左下角不等于右上角减右下角。

为什么这样做呢，因为这个移项把不等号同侧的数拉到了同一列。

所以这个不等式其实告诉了我们对于任意两列，他们同一行位置上的数，减去这一行向下相同长度的数值都不一样。

这就可以构造了，令第一列是公差为 $0$ 的等差数列，第二列是公差为 $1$ 的等差数列，第三列是公差为 $2$ 的等差数列，以此类推。

因为 $n$ 是个质数，所以对于常数 $p$，变量 $q$， $pq \bmod n$ 的循环节长度为 $n$，就可以保证数值不一样。

然后看限制三，因为列之间是独立的，只要令第 $i$ 列是公差为 $i - 1$ 的等差数列即可，所以整列加上一个偏移量 $\Delta = b_i - a_{i, i}$ 就做完啦。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

inline int read() {
    char c; bool f = true;
    while (!isdigit(c = getchar())) f = c != '-';
    int x = c ^ 48;
    while (isdigit(c = getchar())) x = x * 10 + (c ^ 48);
    return f ? x : -x;
}

const int N = 510;
const int p = 1000000007;

int n, b[N], a[N][N];

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        b[i] = read();
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[j][i] = a[j - 1][i] + i - 1;
            // if (a[j][j] != n) a[j][i] %= n;
            a[j][i] %= n;
        }
    }
    for (int i = 1; i <= n; i++) {
        int delta = b[i] - a[i][i];
        for (int j = 1; j <= n; j++) {
            a[j][i] += delta;
            a[j][i] += n;
            a[j][i] %= n;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
```

---

## 作者：hexu2010 (赞：2)

# CF1734E Rectangular Congruence 题解

## 题目大意

给定一个质数 $n$（$n \leq 350$），你要构造出 $n\times n$ 的矩阵。其中，矩阵的左上-右下对角线已经给出，你要使得这个矩阵中所有的数都在 $[0,n-1]$ 的范围内，同时满足任意一个矩形中两条对角线顶点上的数之和在模 $n$ 意义下同余。

## 分析

用题目中的式子表示，就是说对于任意的 $r_1,r_2,c_1,c_2\in[0,n-1]$，满足 $a_{r_1,c_1}+a_{r_2,c_2}\not\equiv a_{r_1,c_2}+a_{r_2,c_1}\pmod n$.看到这种东西，我们最好希望它们变简单一点，每一边的共同因素多一点。我们就可以移项，变成如下形式：
$$a_{r_1,c_1}-a_{r_1,c_2}\not\equiv a_{r_2,c_1}-a_{r_2,c_2}\pmod n$$

这时候就可以发挥构造的超长特点：肆意控制变量或不变量。
我们只要让 $c_1,c_2$ 相同的时候两边不等即可。显然，构造一个等差数列即可。令第 $i$ 行的公差为 $i-1$，这样就能满足条件。

证明：

反证法。

假设第 $i$ 行公差为 $i-1$ 时存在 $c_1,c_2,r_1,r_2\in[1,n]$ 使得 $a_{r_1,c_1}-a_{r_1,c_2}\equiv a_{r_2,c_1}-a_{r_2,c_2}\pmod n$.根据定义可得 $LHS=(c_1-c_2)(r_1-1)$，$RHS=(c_1-c_2)(r_2-1)$。即 $(c_1-c_2)(r_1-1)\equiv(c_1-c_2)(r_2-1)\pmod n$。移项，得 $(c_1-c_2)(r_1-r_2)\equiv0\pmod n$。注意到 $n$ 为质数，故 $n\mid c_1-c_2$ 或 $n\mid r_1-r_2$，易得当 $r_1\neq r_2$ 且 $c_1\neq c_2$ 两式不成立。

证毕。

## 结论

只要使得第 $i$ 行的公差为 $i-1$ 即可。利用这个结论，我们可以退出公式 $a_{i,j}=(i-j)(i-1)+b_i$，其中 $b_i$ 为题目中给定，还要注意一下**取模**。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
	for(; ch >= '0' && ch <= '9'; s = 10 * s + ch - '0', ch = getchar());
	return s * w;
}
const int MAXN = 355;
int n, a[MAXN];
signed main(){
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cout << (((j - i) * (i - 1) + a[i]) % n + n) % n << " ";
		}
		cout << endl;
	}
	return 0;
}
```



---

## 作者：LinkZelda (赞：2)

考虑改写一下条件：$a_{r_1,c_1}-a_{r_2,c_1}\not\equiv a_{r_1,c_2}-a_{r_2,c_2}\pmod n$。

那么问题转化为任意两行对应位置作差后，任意两个位置的值在模 $n$ 意义下不相等。

因为只有 $n$ 个数，我们只能让对应位置做差的结果是一个排列。这里给出的一种构造方案是直接让相邻两行的差（模 $n$ 意义下）就是 $0\cdots n-1$。

考虑正确性，相邻两行显然满足。

如果跨过 $k(k\geq1)$ 行的话，假设存在两个位置 $i,j(i\neq j)$ 使得 $ki\equiv kj\pmod n$，那么 $k(i-j)\equiv 0\pmod n$，因为题目保证 $n$ 是质数且 $k<n$，那么 $i-j\equiv 0\pmod n$，所以假设不成立。所以这样构造是可以让任意两行作差后模意义下是个排列的。

因为只有对角线元素确定，所以肯定可以构造出一组解（不会有一开始就冲突的问题）。

[代码](https://www.luogu.com.cn/paste/3x9zqefy)。

---

## 作者：SFlyer (赞：1)

首先考虑没有限制怎么做。

因为我数学不是很好，可以考虑凑。显然如果 $a_{i,j}=(i+j)\bmod n$ 会完蛋，然后就想到了 $a_{i,j}=(ij)\bmod n$，手玩发现对了！

为什么对：设 $a_{r_1,c_1}$ 之类的为 $a,b,c,d$。那么要证明 $ab+cd\neq ac+bd\pmod n$，则是 $(a-d)(b-c)\neq 0\pmod n$。因为 $a,b,c,d$ 不可能相差 $\ge n$，而且 $n$ 是质数，没有办法分解，因此得证。

有了这个有限制就简单了。考虑如果一行相加一个相同的数，不会改变不等的性质，因为增加的会是一样的。因此做完了。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 355;

int n,a[N],b[N][N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=0; i<n; i++){
		cin>>a[i];
		for (int j=0; j<n; j++){
			b[i][j]=i*j%n;
		}
	}
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			cout<<(b[i][j]+a[i]-b[i][i]+n)%n<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Hadtsti (赞：1)

### 题意简述
给出质数 $n(2\le n<350)$，并给出 $b_1,b_2,\cdots,b_n(0\le b_i<n)$，要求构造 $n\times n$ 的矩阵 $a$，使得：

- $\forall i,j\in[1,n],a_{i,j}\in[0,n)$
- $\forall i\in [1,n],a_{i,i}=b_i$
- $\forall i,j,x,y\in[1,n](i\neq x,j\neq y),a_{i,j}+a_{x,y}\neq a_{i,y}+a_{x,j}$

### 题目分析
欢迎来到思维难度 $\gg$ 代码难度的构造题。

首先分析一下条件：

- 第一个条件比较好实现，只要我们构造出的矩阵在模 $n$ 意义下仍满足第三个条件即可。

- 第二个条件看似奇怪，似乎不容易构造出既满足第三个条件又满足第二个条件的矩阵，但是我们发现有这样一个性质：

	$(a_{i,j}+c)+a_{x,y}\neq (a_{i,y}+c)+a_{x,j}\Leftrightarrow  a_{i,j}+a_{x,y}\neq a_{i,y}+a_{x,j}$（$c$ 是任意常数）。
    
    这意味着如果我们构造出了任意一个满足第三个条件的矩阵，我们只需要对每行各指定一个常数 $c$，让该行所有元素都加上这个常数就可以满足第二个条件。
    
- 第三个条件就是本题的重点了。我们对其进行一个转换得到：

	$$a_{i,j}+a_{x,y}\neq a_{i,y}+a_{x,j}\Leftrightarrow a_{i,j}-a_{i,y}\ne a_{x,j}-a_{x,y}$$

	也就是说，矩阵的每两行对应位置的两个元素之差皆不相等。这样我们不妨令第 $1$ 行的相邻元素之差都为 $1$，第 $2$ 行的相邻元素之差都为 $2$……第 $n-1$ 行的相邻元素之差都为 $n-1$，第 $n$ 行的相邻元素之差都为 $n$。一个例子就是 $a_{i,j}=ij$，即：

	$$a=  \begin{bmatrix}  1& 2&3 &\cdots  & n \\  2& 4& 6&\cdots  & 2n \\   3& 6& 9&\cdots  & 3n \\  \vdots & \vdots & \vdots&\ddots & \vdots \\    n& 2n& 3n&\cdots  & n^2  \end{bmatrix}  $$
   
   这个矩阵就满足第三个条件。

现在我们分析完了三个条件，只需要看一下刚刚构造的满足第三个条件的矩阵是否可以转变成满足前两个条件的形式即可。

首先这个矩阵是满足第一个条件的。这是因为 $ij+xy-iy-xj=(i-x)(j-y)$，而 $i\neq x,j\neq y$，且 $n$ 为质数，所以有 $\gcd(i-x,n)=\gcd(j-y,n)=1$，即 $(i-x)(j-y)\not\equiv0 \pmod n$。所以 $ij+xy\not\equiv iy+xj \pmod n$。因此将该矩阵所有元素对 $n$ 取模同样满足第三个条件。
    
为了满足第二个条件，我们让第 $i$ 行的所有元素加上 $b_i-i^2$ 即可，记得取模。

本题至此就解决了，代码十分简单（字面意思）。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[360];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;printf("\n"),i++)
		for(int j=1;j<=n;j++)
			printf("%d ",((i*j+a[i]-i*i)%n+n)%n);//原始值是 i*j，为了满足第二个条件加上a[i]-i*i，为了满足第一个条件对 n 取模
	return 0;
}
```

---

## 作者：Presentation_Emitter (赞：1)

~~你这 E 怎么比 D 水啊（~~

观察条件中的式子 $a_{r_1, c_1} + a_{r_2, c_2} \not\equiv a_{r_1, c_2} + a_{r_2, c_1}$，移项得 $a_{r_1, c_1} - a_{r_1, c_2} \not\equiv a_{r_2, c_1} - a_{r_2, c_2} \pmod n$。这个式子的意义即为：对于任意两行，将其对应位置在膜 $n$ 意义下相减后需要形成一个 $0 \sim n-1$ 的排列。不难发现这是一个充要条件。

对行做差分得到 $n-1$ 个排列 $P_i$。由上面的转化得，任取 $1 \le l \le r \lt n$，$P_l+P_{l+1}+\cdots+P_r$ 形成一个排列，其中 $P_a+P_b$ 表示将这两个排列对应位置模意义下相加形成的序列。

我们钦定一个 $0 \sim n-1$ 的排列 $Q$，令 $P_i=k_iQ$。由于 $n$ 是个质数，所以 $\forall k \in [1,n] \cap \mathbb{Z}$，$kQ$ 均为 $0 \sim n-1$ 的排列，题意转化为构造 $n-1$ 个 $k_i$ 使得任意一个子段的和不为 $n$ 的倍数。令所有 $k_i=1$ 即可。

时间复杂度 $\Theta(n^2)$。

Code:

```cpp
ll n,a[355][355];
int main()
{
	n=rd();for(int i=1;i<=n;++i)a[i][i]=rd();
	for(int i=2;i<=n;++i)for(int j=1;j<=i-1;++j)a[i][j]=(a[i-1][j]+j)%n;
	for(int i=n-1;i>=1;--i)for(int j=i+1;j<=n;++j)a[i][j]=(a[i+1][j]-j+n)%n;
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)prt(a[i][j]," \n"[j==n]);
	ret 0;
}
```

---

## 作者：zuytong (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1734E)


------------
## 思路

我们考虑将不等式移个项：

$$a_{r_1,c_1}-a_{r_1,c_2}\not \equiv a_{r_2,c_1}-a_{r_2,c_2}$$

也就是说，在任意两行中，他们任意两个**相同**列上的数，在模意义下的差不相同。

由于模数 $n$ 是质数，我们可以考虑以下构造方法：

对于第 $i$ 行，相邻两个数在模意义下的差（默认右边减左边）为 $i-1$。

- 证明：

- 考虑两个不同的行 $i,j$，对于任意两列 $c_1,c_2$，$i$ 行的差为 $(c_2-c_1)\times (i-1)$，$j$ 行的差为 $(c_2-c_1)\times (j-1)$。

- 由于 $n$ 是质数，且 $i-1\not = j-1$，那么就有 $(c_2-c_1)\times (i-1) \not \equiv (c_2-c_1)\times (j-1) \pmod n$。


------------
## 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
#define FOR(i, x, y) for(int i = (x); i <= (y); i++)
#define ROF(i, x, y) for(int i = (x); i >= (y); i--)
using namespace std;
inline int rd()
{
	int sign = 1, re = 0; char c = getchar();
	while(!isdigit(c)) {if(c == '-') sign = -1; c = getchar();}
	while(isdigit(c)) {re = re * 10 + (c - '0'); c = getchar();}
	return sign * re;
}
int n;
int ans[355];
signed main()
{
	n = rd();
    FOR(i, 1, n)
    {
        int a = rd();
        ans[i] = a;
        ROF(j, i - 1, 1) ans[j] = (ans[j + 1] - i + n) % n;
        FOR(j, i + 1, n) ans[j] = (ans[j - 1] + i) % n;
        FOR(j, 1, n) printf("%d ", ans[j]);
        puts("");
    }
	return 0;
}
```


---

## 作者：ran_qwq (赞：0)

被模拟赛一大坨的构造题创爆了，构造题只要不出在 OI 赛制上（没 SPJ 没大样例）都是很好玩的捏。

方便起见，以下用 $i,j,k,l$ 分别表示题目中的 $r1,r2,c1,c2$。

先不考虑 $b_i=a_{i,i}$ 的限制。

题目中 $a_{i,k}+a_{j,l}\not\equiv a_{i,l}+a_{j,k}\pmod n$ 两边都有四个不同下标的形式很烦，我们给它移个项：

$$\forall 0\le i<j<n,0\le k<l<n,a_{i,k}-a_{i,l}\not\equiv a_{j,k}-a_{j,l}\pmod n$$

因为 $a_{i,j}$ 的值域是 $[0,n-1]$，所以 $\forall 0\le i<n$，满足 $0\le k<l<n,a_{i,k}-a_{i,l}\pmod n$ 要互不相同。

这时再看一眼题，发现有个非常奇怪的限制：$n$ 是质数。

$n$ 是质数，结合这道题的互不相同，就想到了 $\forall d\in[0,n-1]$，满足 $\forall k\in[0,n-1],dk\mod n$ 互不相同。

这两个式子形式非常相似，构造 $a_{i,j}=ij$，令 $d=l-k$ 就是两个相同的式子。

再考虑 $b_i=a_{i,i}$ 的限制。

我们对一行 $i$ 同时模 $n$ 意义下加一个数 $c$，$\forall 0\le j<k<n,a_{i,j}-a_{i,k}\pmod n$ 不变。所以可以通过加数调整使得 $b_i=a_{i,i}$。

---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/17135585.html)

[题目传送门](https://codeforces.com/problemset/problem/1734/C) [to luogu](https://www.luogu.com.cn/problem/CF1734E)

~~为什么只有 VP 才会遇到这种简单 E。~~

### 题目大意
给定一个质数 $n$ 和长度为 $n$ 的序列 $b$，要求构造一个 $n\times n$ 矩阵 $a$，满足所有 $r_1,r_2,c_1,c_2$（$1\le r_1<r_2\le n$，$1\le c_1<c_2\le n$），有 $a_{r_1,c_1}+a_{r_2,c_2}\not\equiv a_{r_1,c_2}+a_{r_2,c_1}\pmod n$，同时 $a_{i,i}=b_i$。  
数据范围：$2\le n\le 350$。
### 题目解析
对原式移项，得到 $a_{r_1,c_1}-a_{r_1,c_2}\not\equiv a_{r_2,c_2}-a_{r_2,c_2}\pmod n$。  
也就是说，对于任意的 $1\le l<r\le n$，$(a_{l,i}-a_{r,i})\bmod n$ 两两不同，换句话说，构成一个 $0\sim n-1$ 的一个排列。  
注意到我们如果给一行都加上一个数不会影响 $a_{l,i}-a_{r,i}$，所以 $a_{i,i}=b_i$ 的限制可以忽略，只需要最后整行加上一个数即可。  

接下来考虑如何得到一个任意的合法的 $a$。  
首先假设 $a_{2,i}-a_{1,i}=i$，然后考虑怎么构造 $a_{3,i}$。  
我们发现直接让 $a_{3,i}-a_{2,i}=i$ 即可。  
换句话说可以直接，$a_{i,j}=i\times j\bmod n$。  
我们来证明这样是正确的。  

换句话说，对于任意的 $0\le x<n$，$xy\bmod n$（$0\le y<n$）两两不同。  
使用反证法，假设 $0\le i<j<n$ 有 $xi\equiv xj\pmod n$。  
发现因为 $n$ 是质数，$\gcd(x,n)=1$，所以 $i\equiv j\pmod n$，得到 $i=j$，矛盾，所以假设不成立，证毕。（类似于欧拉定理证明里的一步）

最后为了让 $a_{i,i}=b_i$，所以得到 $a_{i,j}$ 的通项：

$$a_{i,j}=(i\times j-i\times i+b_i)\bmod n$$

```cpp
int n,b[maxn];
int main(){
	n=read(); int i,j; for(i=1;i<=n;i++) b[i]=read();
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) print((i*j-i*i%n+b[i]+n)%n),pc(" \n"[j==n]);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1734E 题解



## 思路分析

注：数值计算均在 $\bmod n$ 意义下进行，数组下标范围为 $[0,n)$。

首先考虑对 $a_{r_1,c_1}+a_{r_2,c_2}\ne a_{r_1,c_2}+a_{r2,c_1}$ 进行变形：得到 $a_{r_1,c_1}-a_{r_2,c_1}\ne a_{r_2,c_1}-a_{r2,c_2}$。

那么对于 $a$ 中的任意两行 $r_1,r_2$，我们将其对位相减得到 $d_i=a_{r_1,i}-a_{r_2,i}$，简记为 $a_{r_1}-a_{r_2}=d$。

那么由题目的限制我们知道 $d_i$ 两两不同，因此原限制等价于对于任意 $r_1,r_2$，$d$ 都是 $0~n-1$ 的一个排列。

考虑一种构造：对于所有 $i\in[1,n)$：$a_{i}-a_{i-1}=\{0,1,2,\cdots,n-1\}$。

此时：对于任意 $r_1,r_2$，都满足 $a_{r_1}-a_{r_2}=\{d\times0,d\times1,d\times2,\cdots,d\times(n-1)\}$，其中 $d=|r_1-r_2|$。

由于 $n$ 是质数，因此我们知道对于任意 $k\ne 0$，$\{0\times k,1\times k,2\times k,\cdots,(n-1)\times k\}$ 依然是一个 $0\sim n-1$ 的排列，所以这种构造是合法的。

此时第 $i$ 列是一个公差为 $i$ 的等差序列，从 $a_{i,i}$ 出发依次赋值即可。

时间复杂度 $\Theta(n^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=350;
int a[MAXN][MAXN];
signed main() {
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i) {
		scanf("%d",&a[i][i]);
		for(int j=i,k=a[i][i];j>=0;--j,k=(k+n-i)%n) a[j][i]=k;
		for(int j=i,k=a[i][i];j<n;++j,k=(k+i)%n) a[j][i]=k;
	}
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			printf("%d ",a[i][j]);
		}
		puts("");
	}
	return 0;
}
```



---

## 作者：cryozwq (赞：0)


当不限制主对角线的时候，一种构造方案是 $i$ 行 $j$ 列放 $ij$（从 $0$ 开始编号），那么对于任意 $a,b,c,d$，均有 $ab+cd$ 和 $ad+bc$ 模 $n$ 不同，因为 $n$ 是一个质数。

现在限制了主对角线，那么每一行的数只要全部偏移到主对角线满足这个限制就可以了。

代码见 CF 提交。

---

