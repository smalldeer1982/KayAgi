# [ARC125B] Squares

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc125/tasks/arc125_b

整数 $ N $ が与えられます． 以下の条件を満たす整数の組 $ (x,y) $ の個数を $ 998244353 $ で割った余りを求めてください．

- $ 1\ \leq\ x,y\ \leq\ N $
- $ x^2-y $ は平方数である．（特に，$ 0 $ も平方数とする．）

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{12} $
- 入力される値はすべて整数である

### Sample Explanation 1

以下の $ 2 $ 通りが考えられます． - $ x=1,y=1 $ - $ x=2,y=3 $

## 样例 #1

### 输入

```
3```

### 输出

```
2```

## 样例 #2

### 输入

```
10```

### 输出

```
8```

## 样例 #3

### 输入

```
10000000000```

### 输出

```
52583544```

# 题解

## 作者：nxd_oxm (赞：3)

~~水社贡ing~~
# 题意
题目说让你找两个数 $x , y$ ，让你使 $x^2 - y$ 是个平方数。

# 思路
那我们就可以设出等式 $x^2 - y = k^2$ 。

我们移波项， $x^2 - k^2 = y$ 。

用平方差公式，得出 $(x-k)(x+k)=y$ 。

那就可以枚举了。我们枚举 $i=(x-k)$ ,那由于 $y \le n$
 , 那 $(x+k) \le \lfloor n \div i \rfloor $ 。
 
 为了不算重复，我们就假设 $(x+k) \ge i$ 。
 
 因为我们知道 $(x-k)$ 和  $(x+k)$ 奇偶性铁定相同，并且我们知道 $i$ ~ $(x+k)$ 里面有 $ (n \div i - i) \div 2 + 1$ 个奇偶性相同的数，所以我们就可以算贡献了。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,sum;
	cin>>n;
	for(int i=1;i*i<=n;i++){
		int j=n/i;
		sum=((j-i)/2%998244353+sum%998244353+1)%998244353;
	}
	cout<<sum;
	return 0;
}

```

---

## 作者：RNTBW (赞：1)

### 序
无序。

~~又来水社贡啦！~~
## 题意
给出一个数 $N$，求满足 $1 \leqslant x,y \leqslant N$ 且 $x^2-y =k^2$（$k$ 为非负整数）的点对 $(x,y)$ 的个数。
## 思路
我们可以移项再使用平方差，变成 $(x+k) \times (x-k)=y$。

之后我们可以枚举每个 $(x-k)$ 算贡献。

由于 $1\leqslant y \leqslant n$，所以当我们枚举到 $x-k=i$ 的时候，这时 $x+k$ 的上限就是 $n\div i$ 向下取整。

为了去重，我们只讨论所有的 $x+k$ 都 $>i$ 的情况。

但是由于 $x,k$ 必须是整数，所以我们的 $x+k,x-k$ 的奇偶性必须相同。

那么已知了 $x-k=i$ 与 $\max_{x+k} = n\div i$，易知 $[i,n\div i]$ 范围内与 $i$ 奇偶性相同的个数为 $(n\div i-i) \div 2 +1$。

所以就可以愉快的写代码啦~

PS：$x+k$ 可以等于 $x-k$，因为 $k$ 可以等于 0。
## 正确代码
超短的哦~

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,i,k,s;
int main()
{
	scanf("%lld",&n);
	for(i=1;i*i<=n;i++)//i != 0 因为 x != 0
	{
		k=n/i;
		s=(s+(k-i)/2+1)%998244353;//算贡献
	}
	printf("%lld",s);
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# AT_arc125_b [ARC125B] Squares 题解

[题面](https://www.luogu.com.cn/problem/AT_arc125_b)

## 思路

题目要求求出数对 $x,y$ 使得 $x^2-y$ 是完全平方数。

1. 我们设 $z$ 使得 $x^2-y=z^2$

2. 我们可以通过移项得到 $x^2-z^2=y$

3. 再通过平方差得到 $(x+z) \times (x-z)=y$

现在我们可以**枚举**了。

1. 我们设 $k=x-z$ 因为题目当中说 0 是完全平方数，则存在 $k=x+z$ 的情况，所以 $x+z$ 最小为 $k$。

2. 因为 $y$ 的最大值为 $n$ ，所以 $x+z$ 的最大值为 $\frac{n}{k}$。

3. 我们得出 $x+z$ 的范围是 $k$ 到 $\frac{n}{k}$。

4. 因为 $x,y,k$ 都为整数，所以 $x+z$ 和 $k$ 的奇偶性相同。所以我们求出在 $k$ 到 $\frac{n}{k}$ 曼珠此奇偶性的个数即可，公式为：$\frac{(\frac{n}{k}-k)}{2}+1$，然后就可以枚举了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int mod=998244353;
int n,sum;

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i*i<=n;i++)
	{
		int j=n/i;
		sum=(((j-i)/2%mod+sum)%mod+1)%mod;
	}
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：白简 (赞：0)

#### 题目大意
给定一个正整数 $N$，求满足下列条件的点对 $(x,y)$ 数量，答案对 $998244353$ 取模。

- $1\leq x,y \leq N$
- $x^2-y$ 是一个完全平方数。特别的，$0$ 也算一个完全平方数。

#### 思路
因为 $x^2-y$ 也是一个完全平方数，所以考虑设 $x^2-y=z^2$。

设 $k=x-z$，那么有

$$(k+z)^2-y=z^2$$

展开后可以消掉 $z^2$，于是有

$$k^2+2kz=y$$

由于 $y \leq N$，那么显然 $k$ 是 $\sqrt{N}$ 级别的，可以考虑枚举 $k$ 得到合法的点对数量。

由上式可以得出两个限制条件：

- $z \leq n - k$
- $z \leq \dfrac{n-k^2}{2b}$

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int Mod = 998244353;

signed main() {
    int n;
    cin >> n;
    int ans = 0;
    for(int b = 1;b * b <= n; b++) {
        ans += min(n - b,(n - b * b) / (2 * b)) + 1;
        ans %= Mod;
    }

    cout << ans << endl;
    return 0;
}
```

---

## 作者：Archy_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc125_b)

## 题目简述:

给出 $n$，求出 $(x,y)$ 的个数对 $998244353$ 取模后的值。

1. $1 \le x,y \le n$。

2. $x^2 - y = z^2$。

## 思路:

等式基本变化后为：

$$x^2-z^2=y$$
$$(x+z)(x-z)=y$$

现在我们可以想办法**枚举**了。

我们令 $k=x-z$，因为题中说 $0$ 是完全平方数，则存在 $k = x + z$ 的情况，所以 $x+z$ 最小为 $k$。

因为 $y$ 最大为 $n$，则 $x+z$ 最大为 $n \div k$。

我们得出 $x+z$ 的范围是 $k$ 至 $n \div k$。

$x,y$ 都为整数，$k$ 也是整数，所以 $x+z$ 与 $k$ 的**奇偶性相同**，要为奇都是奇，要为偶都是偶。所以我们求出在 $k$ 至 $n \div k$ 满足此奇偶性的个数即可，公式为：

$$(n \div k - k) \div 2 + 1$$

现在，我们就可以愉快的枚举啦！

## code:

```cpp
#include<iostream>
#define ll long long
using namespace std;
ll n,mmax,ans;
int main(){
	cin>>n;
	for(register ll i=1;i*i<=n;i++){
		mmax=n/i;
		ans=(ans+(mmax-i)/2+1)%998244353;//此处不能写ans+=
	}
	cout<<ans<<"\n";//记得换行
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

## 题意

给定正整数 $N$，求满足如下条件的正整数对 $(x, y)$ 的数量：

- $1 \le x, y \le N$

- $x^2 - y$ 为完全平方数（$0$ 也是完全平方数）

（$1 \le N \le 10^{12}$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ARC125B.html)

因为 $x^2 - y$ 为完全平方数，设其为 $z^2$，那么有

$$\begin{aligned}
x^2 - y = z^2 \\
\end{aligned}$$

设 $b = x - z$，那么有

$$\begin{aligned}
(z + b)^2 - y &= z^2 \\
y &= 2bz + b^2
\end{aligned}$$

考虑到 $2bz + b^2 = y \le N \Rightarrow b^2 \le N$，因此 $b$ 的取值个数是 $\mathcal{O}(\sqrt{N})$ 级别的，所以可以枚举 $b$ 的取值，接下来快速计算合法的 $z$ 的个数，进而统计数对个数，那么有

$$\begin{aligned}
y &= 2bz + b^2 \Leftrightarrow  z \le \dfrac{N - b^2}{2b}
\end{aligned}$$

有因为 $x = z + b$，所以有

$$x \le N \Leftrightarrow z \le N - b$$

所以有

$$0 \le z \le \min\left\{\dfrac{N - b^2}{2b}, N - b\right\}$$

故在钦定 $b$ 的情况下可以快速计算合法的 $z$ 的取值，总复杂度 $\mathcal{O}(\sqrt{N})$。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;

constexpr valueType MOD = 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    valueType ans = 0;

    for (valueType i = 1; i * i <= N; ++i) {
        ans += (std::min((N - i * i) / (2 * i), N - i) + 1) % MOD;

        ans %= MOD;
    }

    std::cout << ans << std::endl;

    return 0;
}
```

---

