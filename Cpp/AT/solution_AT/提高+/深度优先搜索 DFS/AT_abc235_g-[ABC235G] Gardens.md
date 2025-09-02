# [ABC235G] Gardens

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc235/tasks/abc235_g

高橋君は $ A $ 株のリンゴの苗、 $ B $ 株のバナナの苗、$ C $ 株のサクランボの苗を持っています。同じ種類の苗は区別できません。  
 $ N $ 園の庭を持っている高橋君は、次の条件をすべて満たすように持っている苗を植えることにしました。

- すべての庭に少なくとも $ 1 $ 株以上の苗を植える。
- $ 1 $ つの庭に同じ種類の果物の苗を $ 2 $ 株以上植えてはいけない。
- 持っているすべての苗を植える必要はない。

条件を満たす植え方は何通りありますか？答えを $ 998244353 $ で割ったあまりを求めてください。  
 ただし、植え方が異なるとは、ある庭が存在して、片方の植え方でその庭に植えられた果物の苗の集合がもう片方と異なることをいいます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^6 $
- $ 0\ \leq\ A\ \leq\ N $
- $ 0\ \leq\ B\ \leq\ N $
- $ 0\ \leq\ C\ \leq\ N $
- 入力はすべて整数である。

### Sample Explanation 1

条件を満たす植え方は $ 21 $ 通りあり、図示すると以下のようになります。 (縦に並んだ $ 2 $ つの枠が庭で、$ A,B,C $ はそれぞれリンゴの苗、バナナの苗、サクランボの苗を意味しています。) !\[image\](https://img.atcoder.jp/ghi/30cbec3c4cc587889e3c37933da06c3f.png)

### Sample Explanation 2

条件を満たす植え方が存在しない場合もあります。

## 样例 #1

### 输入

```
2 2 1 1```

### 输出

```
21```

## 样例 #2

### 输入

```
2 0 0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
2 0 2 2```

### 输出

```
9```

## 样例 #4

### 输入

```
100 12 34 56```

### 输出

```
769445780```

## 样例 #5

### 输入

```
5000000 2521993 2967363 3802088```

### 输出

```
264705492```

# 题解

## 作者：EuphoricStar (赞：9)

考虑不要求每个盒子至少放一个球，答案即为 $\sum\limits_{i=0}^A \binom{n}{i} \times \sum\limits_{i=0}^B \binom{n}{i} \times \sum\limits_{i=0}^C \binom{n}{i}$。

加上这个条件，考虑容斥，钦定 $i$ 个盒子不能放球，其他随意，则答案为 $\sum\limits_{i=0}^n (-1)^i \binom{n}{i} \sum\limits_{j=0}^A \binom{n-i}{j} \times \sum\limits_{j=0}^B \binom{n-i}{j} \times \sum\limits_{j=0}^C \binom{n-i}{j}$。

似乎没有快速算 $\sum\limits_{i=0}^m \binom{n}{i}$ 的方法，但是观察发现式子中 $m$ 不变，$n$ 每次减一，考虑递推。设 $f_i = \sum\limits_{j=0}^A \binom{i}{j}$，则根据 $\binom{n}{m} = \binom{n-1}{m} + \binom{n-1}{m-1}$，可得 $f_i = \frac{f_{i+1} + \binom{i}{A}}{2}$。按照相同的方法递推出 $g_i = \sum\limits_{j=0}^B \binom{i}{j}$ 和 $h_i = \sum\limits_{j=0}^C \binom{i}{j}$，答案即为 $\sum\limits_{i=0}^n (-1)^i \binom{n}{i} f_{n-i} g_{n-i} h_{n-i}$。

[code](https://atcoder.jp/contests/abc235/submissions/38580844)

---

## 作者：Cx114514 (赞：2)

### 题目链接：[[ABC235G] Gardens](https://www.luogu.com.cn/problem/AT_abc235_g)
先不考虑“每个盒子至少放一个球”的限制，则有 $n$ 个盒子的答案为 $\sum\limits_{i=0}^{A}C_{n}^{i} \times \sum\limits_{i=0}^{B}C_{n}^{i} \times \sum\limits_{i=0}^{C}C_{n}^{i}$。接下来考虑如何计算该限制下的方案数。

由容斥原理易得答案为**至少 $0$ 个盒子不放 $-$ 至少 $1$ 个盒子不放 $+$ 至少 $2$ 个盒子不放 $-\cdots+/-$ 至少 $n$ 个盒子不放的方案**。

套路地，本问题就转化为了求：

 $$\sum\limits_{i=0}^{n}\left(-1\right)^{i}C_{n}^{i}\left(\sum\limits_{j=0}^{A}C_{n-i}^{j} \times \sum\limits_{j=0}^{B}C_{n-i}^{j} \times \sum\limits_{j=0}^{C}C_{n-i}^{j}\right)$$ 

这个时候，如果我们暴力地统计前缀和，时间复杂度将会到达恐怖的 $O\left(n^2\right)$，是显然无法通过的。

考虑组合数的递推公式 $C_{n}^{m}=C_{n-1}^{m-1}+C_{n-1}^{m}$。

有了该公式，可得：

 $$\sum\limits_{j=0}^{A}C_{i}^{j}=\sum\limits_{j=0}^{A}C_{i-1}^{j-1}+C_{i-1}^{j}=\left(2\times\sum\limits_{j=0}^{A}C_{i-1}^{j}\right)-C_{i-1}^{A}$$ 

设 $f_{i}=\sum\limits_{j=0}^{A}C_{i}^{j}$。

由上式可得递推式：

$$f_{i}=2\times f_{i-1}-C_{i-1}^{A}$$

设 $g_{i}=\sum\limits_{j=0}^{B}C_{i}^{j}$，$h_{i}=\sum\limits_{j=0}^{C}C_{i}^{j}$。

同理可得：

$$g_{i}=2\times g_{i-1}-C_{i-1}^{B}$$

$$h_{i}=2\times h_{i-1}-C_{i-1}^{C}$$

在求得 $f$，$g$，$h$ 后，直接计算答案即可，因为本题数据规模较大，所以需要递推求逆元以及阶乘的逆元，时间复杂度为 $O\left(n\right)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed int mod = 998244353;

int n, a, b, c, ans, fac[5000005], inv[5000005], facinv[5000005], f[5000005], g[5000005], h[5000005];

int C(int x, int y)
{
	if (x < y) return 0;
	return (fac[x] * facinv[x - y] % mod) * facinv[y] % mod;
}

signed main()
{
	cin >> n >> a >> b >> c;
	fac[0] = 1;
	for (int i = 1; i <= 5000000; i++)
		fac[i] = (fac[i - 1] * i) % mod;
    inv[1] = 1;
    for (int i = 2; i <= 5000000; i++)
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
    facinv[0] = 1;
    for (int i = 1; i <= 5000000; i++)
        facinv[i] = facinv[i - 1] * inv[i] % mod;
	f[0] = 1;
	for (int i = 1; i <= n; i++)
		f[i] = (2 * f[i - 1] - C(i - 1, a) + mod) % mod;
	g[0] = 1;
	for (int i = 1; i <= n; i++)
		g[i] = (2 * g[i - 1] - C(i - 1, b) + mod) % mod;
	h[0] = 1;
	for (int i = 1; i <= n; i++)
		h[i] = (2 * h[i - 1] - C(i - 1, c) + mod) % mod;
	for (int i = 0; i <= n; i++)
		if (i % 2 == 0) ans = (ans + ((C(n, i) * f[n - i] % mod) * g[n - i] % mod) * h[n - i]) % mod;
        else ans = (ans - ((C(n, i) * f[n - i] % mod) * g[n - i] % mod) * h[n - i]) % mod;
	cout << (ans + mod) % mod << endl;
    return 0;
}

```

---

## 作者：Super_Cube (赞：2)

# Solution

考虑二项式反演，钦定 $i$ 个盒子放球，枚举要放 $a$ 个第一类球，$b$ 个第二类球，$c$ 个第三类球进行计算方案。

$$\sum_{i=0}^N(-1)^{N-i}\binom{N}{i}\sum_{a=0}^A\binom{i}{a}\sum_{b=0}^B\binom{i}{b}\sum_{c=0}^C\binom{i}{c}$$

而 $\displaystyle\sum_{i=0}^m\binom{n}{i}=\sum_{i=0}^m\binom{n-1}{i-1}+\binom{n-1}{i}=2\sum_{i=0}^m\binom{n-1}{i}-\binom{n-1}{m}$，于是把后面那三大坨递推出来就好了。

---

## 作者：Tomatonia (赞：1)

设 $P_m$ 表示有至多 $m$ 个盒子里放球时的方法数，则容易写出
$$P_m=\binom{n}{m}\sum_{j=0}^{a}\binom{m}{j}\sum_{k=0}^{b}\binom{m}{k}\sum_{l=0}^{c}\binom{m}{l}$$
那么根据容斥原理，所求方案数为
$$P_n-P_{n-1}+P_{n-2}-\cdots=\sum_{m=0}^{n}(-1)^{n-m}P_m$$
设 $P_m$ 中的三个求和式分别为 $A_m,B_m$ 和 $C_m$，则由恒等式 $\binom{m}{n}=\binom{m-1}{n}+\binom{m-1}{n-1}$ 可以得到递推关系（其余同理）：
$$\begin{aligned}
A_m&=\sum_{j=0}^{a}\binom{m}{j}\\
&=\sum_{j=0}^{a}\binom{m-1}{j}+\sum_{j=0}^{a-1}\binom{m-1}{j}\\
&=2\sum_{j=0}^{a}\binom{m-1}{j}-\binom{m-1}{a}
\end{aligned}$$
下面考虑程序的实现：可以建立 $(-1)^{n-m}\binom{n}{m},A_m,B_m,C_m,\binom{m}{a},\binom{m}{b}$ 和 $\binom{m}{c}$ 这 $7$ 个量之间的递推关系，分别设为 $f_0(m)$ 至 $f_6(m)$，用一个长度为 $7$ 的 `temp` 数组记录。那么有：
$$\begin{aligned}
f_0(m)&=-\frac{n-m+1}{m}\cdot f_0(m-1)\\
f_1(m)&=2f_1(m-1)-f_4(m-1)\\
f_4(m)&=\frac{m}{m-a}\cdot f_4(m-1)
\end{aligned}$$
即：
```cpp
temp[0] = - temp[0] * (n - m + 1) % mod * inv[m] % mod;
temp[1] = (2 * temp[1] % mod - temp[4]) % mod;
temp[2] = (2 * temp[2] % mod - temp[5]) % mod;
temp[3] = (2 * temp[3] % mod - temp[6]) % mod;
temp[4] = temp[4] * m % mod * inv[m - a] % mod;
temp[5] = temp[5] * m % mod * inv[m - b] % mod;
temp[6] = temp[6] * m % mod * inv[m - c] % mod;
```
注意在 $m=a,b,c$ 时，`temp[4], temp[5], temp[6]` 会从 $0$ 突变至 $1$，需要人工赋值。

总代码：
```cpp
#include <iostream>
using ll = long long;
const int mod = 998244353;
const int maxn = 5e6 + 5;
int n, a, b, c;
ll inv[maxn] = {0}, temp[7] = {0}, ans = 0;
void solve(int m){
    if(m == 0){    //初始化temp数组
        if(n % 2 == 0){
            temp[0] = 1, temp[1] = 1, temp[2] = 1, temp[3] = 1;
            temp[4] = (a == 0), temp[5] = (b == 0), temp[6] = (c == 0);
        }else{
            temp[0] = -1, temp[1] = 1, temp[2] = 1, temp[3] = 1;
            temp[4] = (a == 0), temp[5] = (b == 0), temp[6] = (c == 0);
        }
    }else{
        temp[0] = - temp[0] * (n - m + 1) % mod * inv[m] % mod;
        temp[1] = (2 * temp[1] % mod - temp[4]) % mod;
        temp[2] = (2 * temp[2] % mod - temp[5]) % mod;
        temp[3] = (2 * temp[3] % mod - temp[6]) % mod;
        if(m == a) temp[4] = 1;    //特判突变处
        else if(m > a) temp[4] = temp[4] * m % mod * inv[m - a] % mod;
        if(m == b) temp[5] = 1;
        else if(m > b) temp[5] = temp[5] * m % mod * inv[m - b] % mod;
        if(m == c) temp[6] = 1;
        else if(m > c) temp[6] = temp[6] * m % mod * inv[m - c] % mod;
    }
    ans += temp[0] * temp[1] % mod * temp[2] % mod * temp[3] % mod;
    ans %= mod;
    return;
}
int main(){
    std::cin >> n >> a >> b >> c;
    inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = - (mod / i) * inv[mod % i] % mod;    //递推求数论倒数
    for(int i = 0; i <= n; i++)
        solve(i);
    std::cout << (ans + mod) % mod;
    return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

有 $A$ 个林檎，$B$ 个香蕉，$C$ 个樱桃。你需要从中选出任意个放到 $N$ 个篮子里。要求每个篮子至少有一个水果，且每个篮子里不能存在两个相同的水果。

你需要输出方案数，对 $998,244,353$ 取模。

$1 \leq N \leq 5 \times 10^6,0 \leq A,B,C \leq N$

## 思路

考虑使用容斥原理直接计数，枚举至少 $k$ 个篮子放球，内层分别枚举林檎放 $a$ 个，香蕉放 $b$ 个，樱桃放 $c$ 个，则有：

$$
\sum_{k=0}^{N}(-1)^{n-k}\binom{N}{k}\left(\sum_{a=0}^{A}\binom{k}{a}\right)\left(\sum_{b=0}^{B}\binom{k}{b}\right)\left(\sum_{c=0}^{C}\binom{k}{c}\right)
$$

时间复杂度 $O(N(A+B+C))$。考虑优化内层的组合数求和。

设 $f(k)$ 为：

$$
f(k)=\sum_{a=0}^{A}\binom{k}{a}
$$

按照杨辉三角组合恒等式和简单的拆式子，可以得：

$$
\begin{aligned}
&f(k)=\sum_{a=0}^{A}\left(\binom{k+1}{a} - \binom{k}{a-1}\right)\\
&=\sum_{a=0}^{A}\binom{k+1}{a}-\sum_{a=0}^{A-1}\binom{k}{a}\\
&=f(k+1)-f(k)+\binom{k}{A}
\end{aligned}
$$

解方程 $f(k)=f(k+1)-f(k)+\binom{k}{A}$ 得：

$$
f(k)=\frac{1}{2}\left(f(k+1)+\binom{k}{A}\right)
$$

求和上界为 $B,C$ 时同理。

于是我们就可以倒着计算一边容斥一边递推组合数求和。就可以做到 $O(N+A+B+C)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e6+5;
int n,a,b,c,fact[N],inv[N];
const int mod = 998244353, inv2 = 499122177;

int fastpow(int x,int y){
    int ans = 1;
    while(y){
        if(y&1) ans = ans*x%mod;
        x = x*x%mod;
        y >>= 1;
    }
    return ans;
}

int C(int x,int y){
    if(x < y || x < 0 || y < 0) return 0;
    return (fact[x] * inv[y] % mod) * inv[x-y] % mod;
}

signed main(){
    cin>>n>>a>>b>>c;
    fact[0] = fact[1] = inv[1] = inv[0] = 1;
    for(int i=2;i<=n;i++){
        fact[i] = fact[i-1] * i % mod;
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    for(int i=2;i<=n;i++) inv[i] = inv[i] * inv[i-1] % mod;
    int f = 0, g = 0, h = 0, ans = 0;
    for(int i=0;i<=a;i++) f = (f + C(n, i)) % mod;
    for(int i=0;i<=b;i++) g = (g + C(n, i)) % mod;
    for(int i=0;i<=c;i++) h = (h + C(n, i)) % mod;
    for(int i=n;~i;i--){
        int tmp = ((C(n, i) * f % mod) * g % mod) * h % mod;
        if((n - i) & 1) tmp = mod - tmp;
        ans = (ans + tmp) % mod;
        f = inv2 * (f + C(i - 1, a)) % mod;
        g = inv2 * (g + C(i - 1, b)) % mod;
        h = inv2 * (h + C(i - 1, c)) % mod;
    }
    cout<<(ans % mod);
    return 0;
}
```

---

