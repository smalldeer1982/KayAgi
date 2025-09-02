# [ABC172D] Sum of Divisors

## 题目描述

### 题意翻译
- $f(x)$ 表示正整数 $x$ 的因数个数
- 现在给你一个正整数 $ N $ ，让你求出 $  \sum_{K=1}^N\ K\times\ f(K) $  。
----------


-------------

## 说明/提示

-  $ 1\ \leq\ N\ \leq\ 10^7 $
- $f(1)=1 $ ,  $ f(2)=2 $ ,  $ f(3)=2 $ ,  $ f(4)=3 $ , 所以答案为  $ 1\times\ 1\ +\ 2\times\ 2\ +\ 3\times\ 2\ +\ 4\times\ 3\ =23 $ 。

 _Translated by qinmingze_

## 样例 #1

### 输入

```
4```

### 输出

```
23```

## 样例 #2

### 输入

```
100```

### 输出

```
26879```

## 样例 #3

### 输入

```
10000000```

### 输出

```
838627288460105```

# 题解

## 作者：Jessica2333 (赞：3)

## 思路
我们可以从因子的角度考虑每个数对答案的贡献。对于一个数 $x$，在它的所有小于 $n$ 的倍数中会产生贡献，比如说 $2$ 就会在 $2,4,6,8,10\dots $ 中产生贡献；在 $2$ 中，$2$ 作为因子产生的贡献是 $2$（因为题目让求的是 $k\times f(k)$，所以对于一个数 $k$，它的每个因子都会产生 $k$ 的贡献）；在 $4$ 中，$2$ 作为因子产生的贡献是 $4$；在 $6$ 中，$2$ 作为因子产生的贡献是 $6\dots$ 我们发现，一个数 $x$ 作为因子时产生的贡献是 $x+2x+3x+4x+\dots$ 也就是一个首项为 $x$，公差为 $x$ 的等差数列，而项数就是 $\lfloor \frac{n}{x}\rfloor$，末项就是 $\lfloor \frac{n}{x}\rfloor \times x$（也就是它的小于 $n$ 的最大的倍数），那么我们只需要遍历 $1$ 到 $n$，用等差数列求出每个数在作为因子时的贡献之和，再加到一起就可以了。
## 代码
```cpp
#include<iostream>
#define ll long long
using namespace std;
ll n;
int main()
{
	ll i,j,k,ans=0;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		ans+=(i+n/i*i)*(n/i)/2;
		//n/i*i是末项，即小于n的最大的倍数
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：BlackPanda (赞：1)

*[Problem](https://www.luogu.com.cn/problem/AT_abc172_d)*

------------
## Description

给定 $N$，求 $\sum_{K=1}^N K\times f(K)$ 的值，其中 $f(x)$ 表示正整数 $x$ 的因数个数。

------------
## Solution

题目时间限制为 $\verb!3S!$，可以直接暴力求解，枚举 $1 \sim N$ 中所有正整数的因数个数，存到计数数组中，最后累加即可。

具体枚举步骤：

- 双重循环，外层循环枚举 $1 \sim N$ 这 $N$ 个数。

- 内层循环从 $i$ 开始向外扩展，枚举 $N$ 以内 $i$ 的所有倍数，因为枚举到的数都可以被自己整除，所以因子个数增加。

由于外层循环是从 $1$ 循环到 $N$，而内层循环是从 $i$ 开始到 $N$ 每次加上 $i$，所以时间复杂度为 $\mathcal{O(n \log n)}$，足以通过本题。

本题空间限制为 $\verb!1GiB!$，所以我们可以直接开一个数组容量为 $10^7$ 的数组来存储因数个数。

------------
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
int f[10000005];
int res;

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++ )
	{
		for (int j = i; j <= n; j += i )
		{
			f[j] ++ ;	
		}
	}
	for (int i = 1; i <= n; i ++ )
		res += f[i] * i;
	cout << res;
	return 0;
}
```

---

## 作者：saixingzhe (赞：1)

# 思路
首先，我们可以写一个双重循环，外层循环 $n$ 个数，内层循环通过不断地加 $i$，得出每个数的因数个数，直到循环到 $n$ 结束。还有一个循环负责根据题目的要求求答案。

由于是第二层循环是每次加 $i$，所以复杂度是 $O(n \log  n)$ 的，足以通过本题。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[10000010],ans,n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i){//求因数个数
            a[j]++;
        }
    }
    for(int i=1;i<=n;i++)   ans+=a[i]*i;//根据题意求答案
    cout<<ans<<endl;
    return 0;
}
```
**不开 `long long` 见祖宗**

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc172_d)

### 题解（数论）
枚举每一个数，把它的倍数的因子数量加 $1$，即逆向思考。

**时间复杂度：**$O(n \log_2 n)$
### 代码
```cpp
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 1e7 + 10;
int n;
int f[N];
int main () {
	cin >> n;
	for (int i = 1;i <= n;i++) {
		for (int j = i;j <= n;j += i) f[j]++;
	}
	LL ans = 0;
	for (int i = 1;i <= n;i++) ans += (LL)i * f[i];
	cout << ans << endl;
	return 0;
}
```
### 优化（思维）目前最优解！
经过一定的思考，可以发现 $\sum\limits_{i=1}^{n}i\times f(i)$ 就相当于求 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{\lfloor\frac{n}{i}\rfloor}(i\times j)$。也就是说一个数 $i$，他会是 $i$，$i\times2$，$i\times 3,\cdots,i\times\lfloor\frac{n}{i}\rfloor$ 的因数，而 $i$ 恰好被所有的它的倍数所统计。把式子转化一下，可以得到 $\sum\limits_{i=1}^{n}(i\times \sum\limits_{j=1}^{\lfloor\frac{n}{i}\rfloor} j)$，而求和部分可以用等差数列公式 $O(1)$ 求得，所以最终答案为 $\sum\limits_{i=1}^{n}(i\times\dfrac{\lfloor \frac{n}{i}\rfloor \times (\lfloor \frac{n}{i}\rfloor + 1)}{2})$。

**时间复杂度：**$O(n)$
### 代码
```cpp
#include <iostream>
using namespace std;
typedef long long LL;
LL n;
int main () {
	cin >> n;
	LL ans = 0;
	for (int i = 1;i <= n;i++) ans += (n / i + 1) * (n / i) / 2 * i;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc172_d)
## 思路
由于题目很贴心地给了我们 1GB 的空间，这就意味着我们完全可以开一个 $10^7 + 10$ 的大数组用来储存 $1$ $\sim $ $n$ 的因数个数，其次我们用双层循环来查出每个数的因数个数，实现方法如下：
```cpp
for(int i = 1; i <= n; i++){//n个数
	   for(int j = i; j <= n; j += i){//因数慢慢地扩展
			a[j]++;
		}
	}
```
首先，外层循环 $n$ 个数，其次，内层通过扩展因数的方法来慢慢得出每个数的因数个数。剩下的代码就是跟题意一样的输出了，就不做过多的解释了。
# AC 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e7 + 10;

long long a[N];//这里一定要开long long作者就因为没开long long，WA了很多样例

int main(){
	int n;
	cin >> n;
  //上头说明了，这里不做过多解释
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j += i){
			a[j]++;
		}
	}
	long long sum = 0;
	for(int i = 1; i <= n; i++){
		sum += i * a[i];//按题目描述算
	}
	cout << sum << endl;//输出答案，别忘了回车啊
   return 0;
}
```
### [已AC](https://www.luogu.com.cn/record/96199242)

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc172_d)

## 思路

首先放上时空限制：$1.00$ $\mathrm{GiB}$，$1.00$ $\mathrm{S}$。
这意味着我们可以开一个 $10^7$ 的数组，但是要求我们搞一个时间复杂度低于 $O(n\log n)$ 的算法出来。

由于题目翻译中的题意已经写地很清楚了，所以题意就不在此过多赘述。我们要做的就是用二重循环枚举每个数的因数并求和。在第二重循环时，我们定义一个变量 $j$，而 $j$ 要从第一重循环的基数 $i$ 上每次再增加 $i$，直到 $j=n$ 时退出循环。这样就能保证每次增加后的 $j$ 都能被 $i$ 整除，成为 $i$ 的因数。

- 数据可能会很大，别忘开 long long。
- 别忘最后换行。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long a[10000010],ans,n;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        for(int j=i;j<=n;j+=i){
            a[j]++;
        }
    }
    for(int i=1;i<=n;++i)ans+=a[i]*i;
    cout<<ans<<endl;
    return 0;
}

~~~

[已 AC](https://www.luogu.com.cn/record/96314223)

---

