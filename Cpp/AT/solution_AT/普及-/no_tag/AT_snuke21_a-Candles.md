# Candles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/snuke21/tasks/snuke21_a



# 题解

## 作者：xiaoshumiao (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_snuke21_a)

设摆到第 $k$ 行恰好有 $n$ 根蜡烛，则

$$k \times (k+1) \div 2=n$$

$$k \times (k+1)=2 \times n$$

由于 $k^2<k \times (k+1)<(k+1)^2$，所以

$$ k^2<2 \times n<(k+1)^2$$

开方得：

$$ k<\sqrt{2 \times n}<k+1$$

所以 $\left\lfloor\sqrt{2 \times n}\right\rfloor=k$，先用 `sqrt` 函数计算出 $\sqrt{2 \times n}$，然后判断 $k \times (k+1)$ 是否 $=2 \times n$ 即可。注意开 `long long`。
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int main() {
  long long n;
  scanf("%lld",&n);
  int k=sqrt(2*n);
  if(1LL*k*(k+1)==2*n)
    printf("%d",k);
  else
    printf("-1");
  return 0;
}
```

---

## 作者：xuchuhan (赞：2)

## Analysis

摆放 $n$ 根蜡烛时，若刚好可以摆放 $x$ 行，则有 $\dfrac{x \times (x+1)}{2}=n$，则 $x \times (x+1)=2 \times n$。

又有对于任意正整数 $x$，有 $x^2 < x \times (x+1) < (x+1)^2$。所以 $x^2 < 2 \times n < (x+1)^2$。所以 $x=\lfloor\sqrt{2 \times n}\rfloor$，也就是说，若存在，那么可以摆放 $\lfloor\sqrt{2 \times n}\rfloor$ 行。

当然肯定也有不存在的情况，那么对于所有情况，我们可以先求出 $x=\lfloor\sqrt{2 \times n}\rfloor$，再判断 $x \times (x+1)$ 等不等于 $2 \times n$，若是，输出 $x$；否则，输出 `-1`。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long//记得开long long
using namespace std;
int k;
signed main(){
	cin>>k;
	k*=2;
	int x=sqrt(k);
	//判断
	if(x*(x+1)==k)
		cout<<x;
	else
		cout<<-1;
	return 0;
}
```

---

## 作者：Mason123456 (赞：2)

## Candles

### 思路

先找规律。

对于第一行，一共有 $1$ 个蜡烛。

对于第二行，一共有 $2+1=3$ 个蜡烛。

对于第三行，一共有 $3+2+1=6$ 个蜡烛。

对于第 $k$ 行，一共有 $k+k-1+\dots +2+1 = \frac{k\cdot (1+k)}{2}$ 个蜡烛。

我们设 $n = \frac{k\cdot (1+k)}{2}$，所以 $n$ 满足 $2\cdot n=k+k^2=k\cdot(1+k)$​。 

### 朴素做法

试！或者二分答案，最终复杂度在 $O(\sqrt n)$ 或 $O(\log\sqrt n)$，能过，但是不是最优解。但还是把代码贴这了：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	unsigned long long n;
	cin>>n;
	for(unsigned long long i = 1;i <= 2000000000;i++){
		if(i * (i+1) == 2 * n){
			cout<<i<<"\n";
			return 0;
		}
	} 
	cout<<-1<<"\n";
	return 0;
}
```

### 正解

不难发现，$k$ 不会小于 $\sqrt{2n} + 1$ 也不会大于 $\sqrt{2n}$，所以当 $\lfloor \sqrt{2n} \rfloor \times \lfloor \sqrt{2n} + 1 \rfloor = 2n$ 时，$\lfloor \sqrt{2n}\rfloor$​ 即为答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	unsigned long long n;
	cin>>n;
	unsigned long long p = sqrt(2 * n);
	if(p * (p+1) == 2 * n){
		cout<<p<<"\n";
		return 0;
	}
	cout<<-1<<"\n";
	
}
```

Danke.

---

## 作者：hyc1026 (赞：2)

本题题意：

给你一个数 $x$，如果 $\sqrt{2\times x} \times (\sqrt{2\times x} + 1) = 2\times x$，那么输出 $\sqrt{2\times x}$，否则输出 $-1$。

注意使用 long long。

AC Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long x;
    cin >> x;
    long long t = sqrt(x*2);
    if(t*(t+1) == x*2) cout << t;
    else cout << -1;
    return 0;
}
```


---

## 作者：世末OIer (赞：2)

题解：

由于数据范围很大($10^{18}$)，所以不能枚举。

很容易得出$n^2<n*(n+1)<(n+1)^2 (n>=1)$

所以就先算出$\sqrt{k*2}$的整数，然后再将这个整数乘上它+1再/2

如果得到的是k，答案就是它了；

反之，没有答案。

```cpp
int main(){
	ll x;
	cin>>x;
	x*=2;
	ll t=sqrt(x);
	if(t*(t+1)==x) cout<<t;
	else cout<<-1;
}
```

---

## 作者：danny101 (赞：1)

我们先分析一下题目。

“
蜡烛的排布方式是：第 $i$ 排摆 $i$ 根蜡烛。

Snuke 想知道，他要摆几排蜡烛就可以摆出正好 $n$ 根蜡烛。

如果无解，输出 $-1$ 。”

假设摆了 $k$ 行，可以进行如下推导（上一篇题解讲得不够清晰，我补充一下）：

$k\times (k+1)\div2=n$

$\quad \quad \!\!k\times (k+1)=n\times 2$

因为 $k^2<k\times(k+1)<(k+1)^2$，也即 $k^2<2\times n<(k+1)^2$ ，开方可以得到 $k<\sqrt{2\times n}<k+1$ ，说明 $\lfloor \sqrt{2\times n} \rfloor = k$ 。

所以可以通过判断 $\lfloor \sqrt{2\times n} \rfloor
\times(\lfloor \sqrt{2\times n} \rfloor+1)$ 是否等于 $n \times 2$ 即可。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k;
int main(){
	cin>>n;
	k=sqrt(n*2);
	if(k*(k+1)/2==n)cout<<k;
	else cout<<-1;
        return 0;
}
```

---

## 作者：__XU__ (赞：1)

## AT\_snuke21\_a Candles 题解

### 思路：

不等式的技巧与运用，暴力化简。

#### 做法一：

暴力判断。遍历到一个大一点的数，用高斯求和公式判断相等即可。（当然，非常的不优雅）。

#### 做法二：

还是高斯求和。由 $n \times (n+1)=2 \times n$ 得：

$n^2+n=2 \times n$

即运可转化为不等式：$n^2<2n<n^2+2 \times n+2$

因式分解为：$n^2<2 \times n<(n+1)^2$

再次转化：$n<\sqrt{2 \times n}<n+1$

那么现在只需 $O(1)$ 进行判断操作即可。（具体看代码）。

## AC code

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int x;
signed main(){
	cin>>x;
	int y=sqrt(2*x); 
	if(y*1ll*(y+1)==2*1ll*x){
		cout<<y;
	}
	else{
		cout<<-1;
	}
	return 0;
}

```

谢谢观看。

---

## 作者：G1yu (赞：1)

## [\[AT\_snuke21\_a\]Candles](https://www.luogu.com.cn/problem/solution/AT_snuke21_a)

### 思路

本题代码难度不大，主要考察**思维**。

阅读题面，不难得知我们要找的 $k$ 能使得 $1 + 2+ 3+\cdots+k = n$。 

此时我们着重观察这个式子，能将其逐步化解为以下形式：$k^2+k = 2n$。

因为我们知道 $k^2 \leq 2 \times n \leq k^2+k$, 所以 $k^2 = 2n$，开方后可得 $\lfloor \sqrt{2n}\rfloor = k$。

### 代码实现

我们用 `math` 库中的 `sqrt` 函数求出 $\lfloor \sqrt{2n}\rfloor$ 的值，也就是 $k$ , 再检查 $k$ 是否满足 $k^2+k = 2n$ 即可。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n;
	cin>>n;
	n *= 2;
	cout<<(((long long)sqrt(n)*((long long)sqrt(n)+1) == n)?(long long)sqrt(n):-1); //一定要向下取整！
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

考虑二分答案。设当前二分到的答案是 $p$，那么只需要套用公式前 $p$ 行共有 $\frac{p(p+1)}{2}$ 根蜡烛，然后判断大小关系即可。时间复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n; cin >> n;
    int l = 1, r = 2e9, best = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        int ans = (mid + 1) * mid / 2;
        if (ans == n) {
            cout << mid << '\n';
            return 0;
        }
        else if (ans > n)
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << -1;
    return 0;
}
```

---

## 作者：Ivan422 (赞：0)

怎么大家都在用数学解啊，这里放个二分解法。

题目大意：求 $\frac{k(k+1)}{2} = n$ 是否存在，如果存在输出 $k$，不存在输出 $-1$。

思路：设数轴上一点为 $k$，则 $\frac{k(k+1)}{2}$ 会在数轴上单调递增。于是 $k$ 就满足了单调性，直接考虑二分 $k$。

二分边界：由数据范围，$k\leq 10^{18}$。

只要中间值是满足 $\frac{k(k+1)}{2} < n$ 的，可以往大缩小二分范围。同理，满足 $\frac{k(k+1)}{2} < n$ 的，往下缩小范围。最后只会留下一种可能，也就是找到答案，直接输出即可。

这里要注意乘法可能会越界，可以使用 `__int128` 来进行运算，而不用写麻烦的高精度。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
long long n;
__int128 l,r,mid;
signed main(){
    cin>>n;
    l=0,r=1e18+1;
    while(l+1<r){
        mid=(l+r)/2;
        if(mid*(mid+1)/2<n)l=mid;
        else if(mid*(mid+1)/2>n)r=mid;
        else{cout<<int(mid);return 0;}
    }
    cout<<-1;
    return 0;
}
```

---

## 作者：Laoda_Bryant (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_snuke21_a) | [更好的体验](https://www.luogu.com.cn/article/gbneshtg)   
## 本题题意  
给定一个数 $n$，求 $n$ 是否可以写成 $1+2+3+4+\ldots+k$ 的形式。若可以，输出那个 $k$，否则输出 $-1$。
## 思路
### 做法一：  
暴力模拟 ```k```。
### code:
```cpp
#include<iostream>
using namespace std;
long long n,candles=0;
int main(){
	cin>>n;
	for(int i=1;1;i++){
		candles+=i;若不够，加一排蜡烛
		if(candles==n){
			cout<<i;若等于n，则输出那个k
			return 0;
		}
		if(candles>n) break; 否则跳出
	}
	cout<<-1;
	return 0;
}
```
~~过是能过。可是提交上去之后你会发现，时间最慢的直接给你飙到了 **600ms** 以上。~~  
有没有快一点的方法呢，答案是有的。  
### 前置知识：
[等差数列求和公式](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F/7527418?fr=ge_ala)
### 做法二： 
设 $n=1+2+3+4+\ldots+k$，那么根据等差数列求和公式可得出  
$$
n=\frac{k\times(k+1)}{2}  \\
$$
去分母得
$$
2\times n={k\times(k+1)}  \\
$$
由于 $k^2<k\times(k+1)<(k+1)^2$，所以  
$$
k^2<2\times n<{(k+1)^2}
$$
同时开方得  
$$
k<\sqrt{2\times n}<{k+1}
$$  
那么可以得出 
$$k=\lfloor\sqrt{2\times n}\rfloor$$  
得出结论：用 $k=\lfloor\sqrt{2\times n}\rfloor$ 来求出 $k$  ，然后判断 $k\times(k+1)$ 是否等于 $2\times n$。
### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long n;
int main(){
	cin>>n;
	long long k=sqrt(2*n);求出k
	if(k*(k+1)==2*n) cout<<k;
	else cout<<-1;
	return 0;
}
```

---

## 作者：pfrig729 (赞：0)

### 分析
想要摆放 $k$ 行时蛋糕上正好有 $n$ 根蜡烛，就需要 $n$ 等于 $1 + 2 + 3 + \cdots + k$，根据等差数列求和公式，也就是等于 $k \times ( k + 1 ) \div 2$。换言之，只要我们找到一个整数 $k$ 满足 $k \times ( k + 1 )$ 等于 $2 \times n$ 就行了，否则输出 `-1`。注意 $n \le 10^{18}$，需要使用 `long long`。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n;
inline long long _(long long x)
{
	if((long long)sqrt(x)*(long long)(sqrt(x)+1)==x)return sqrt(x);
	return -1;
}
int main()
{
	scanf("%lld",&n);
	printf("%lld",_(2*n));
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：0)

# 题解：AT_snuke21_a Candles
若存在，则有 $k\times (k+1)\div 2=n$，化简得 $k\times (k+1)=n\times 2$。

因为 $k^2\le k\times (k+1)\le (k+1)^2$，所以若存在，则 $k=\lfloor\sqrt{2\times n}\rfloor$，检验即可。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std ;
int n , k ;
signed main()
{
    cin >> n ;
    k = sqrt(n * 2) ;
    if(k * (k + 1) == n * 2)    cout << k ;
    else    cout << -1 ;
    return 0 ;
}
```

---

## 作者：dvsfanjo (赞：0)

# 题解：AT\_snuke21\_a Candles

## 思路：

反推，如果知道了 $k$ 求 $n$ 的话，可以直接使用公式计算第 $1 \sim k$ 行有几个（感谢高斯），那么只需要知道 $n$ 反推 $k$ 即可。

## 做法：

$k \times (k + 1) \div 2 = n$

$k \times (k + 1) = 2 \times n$

$因为：k^2 < k \times (k + 1) < (k + 1)^2$

$所以：k^2 < 2 \times n < (k + 1)^2$

$k < \sqrt{2 \times n} < k + 1$

所以 $k$ 是 $\sqrt{2 \times n}$ 的整数部分，只要判断是否 $k \times (k + 1) \div 2 = n$ 即可！

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, k;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	k = sqrt(n * 2);
	if (k * (k + 1) / 2 == n) cout << k << endl;
	else cout << -1 << endl;
	return 0;
}
```

AC 记录：[link](https://www.luogu.com.cn/record/155456716)

---

