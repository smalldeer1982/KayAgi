# Joyboard

## 题目描述

Chaneka, a gamer kid, invented a new gaming controller called joyboard. Interestingly, the joyboard she invented can only be used to play one game.

The joyboard has a screen containing $ n+1 $ slots numbered from $ 1 $ to $ n+1 $ from left to right. The $ n+1 $ slots are going to be filled with an array of non-negative integers $ [a_1,a_2,a_3,\ldots,a_{n+1}] $ . Chaneka, as the player, must assign $ a_{n+1} $ with an integer between $ 0 $ and $ m $ inclusive. Then, for each $ i $ from $ n $ to $ 1 $ , the value of $ a_i $ will be equal to the remainder of dividing $ a_{i+1} $ (the adjacent value to the right) by $ i $ . In other words, $ a_i = a_{i + 1} \bmod i $ .

Chaneka wants it such that after every slot is assigned with an integer, there are exactly $ k $ distinct values in the entire screen (among all $ n+1 $ slots). How many valid ways are there for assigning a non-negative integer into slot $ n+1 $ ?

## 说明/提示

In the first test case, one of the $ 2 $ possible ways for Chaneka is to choose $ a_{n+1}=6 $ . If she does that, then:

- $ a_4=a_5\bmod 4=6\bmod 4=2 $
- $ a_3=a_4\bmod 3=2\bmod 3=2 $
- $ a_2=a_3\bmod 2=2\bmod 2=0 $
- $ a_1=a_2\bmod 1=0\bmod 1=0 $
- $ a = [0, 0, 2, 2, 6] $
- There are $ 3 $ distinct values.

In the second test case, the $ 1 $ possible way for Chaneka is to choose $ a_{n+1}=0 $ . If she does that, then $ a = [0, 0, 0] $ . There is only $ 1 $ distinct value.

In the third test case, there is no possible way for assigning a non-negative integer into slot $ n+1 $ .

## 样例 #1

### 输入

```
4
4 6 3
2 0 1
265 265 265
3 10 2```

### 输出

```
2
1
0
5```

# 题解

## 作者：Demeanor_Roy (赞：8)

- [原题链接](https://www.luogu.com.cn/problem/CF1877C)。

- 简单诈骗题。

------------

考虑模拟生成 $a$ 序列的过程，令 $a_{n+1}=x$，显然第一步 $x \rightarrow x \bmod n$，而接下来当模数 $p$ 满足 $p > x \bmod n$ 时，值不变。当 $p=x \bmod n$ 时，$x \bmod n \rightarrow 0$。

这启示我们，合法的 $k$ 的取值应满足 $k \leq 3$。

分类讨论：

- $k=1$：此时 $a_{n+1}=0$，否则 $a$ 序列一定会取到至少两个值。故输出 $1$。

- $k=2$：这要求值一步从初始值变为 $0$，显然初始值要么小于 $n$ 要么是 $n$ 的倍数。故输出 $\min(n-1,m) + \lfloor \frac{m}{n} \rfloor$。

- $k=3$：总数减去 $k < 3$ 的情况，故输出 $m-\min(n-1,m) - \lfloor \frac{m}{n} \rfloor$。

- $k>3$：输出 $0$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,k;
inline void solve()
{
	scanf("%d%d%d",&n,&m,&k);
	if(k>3) puts("0");
	else if(k==1) puts("1");
	else if(k==2) printf("%d\n",min(n-1,m)+m/n);
	else printf("%d\n",m-(min(n-1,m)+m/n));
}
int main()
{
	int T=1;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}

```


---

## 作者：yydfj (赞：2)

这是本蒟蒻第三十九次写的题解，如有错误点请好心指出！

## 问题简述

给你三个整数 $n,m,k$，你将会选一个数 $x(0 \le x \le m)$ 作为 $a_{n+1}$ 的值，然后从 $n$ 到 $1$ 遍历使得 $a_i=a_{i+1} \bmod i$。问有多少个这样的数 $x$，使得 $a_i$ 的值恰好有 $k$ 种。

## 解法综述

考虑从易到难的方向出发，首先当 $k=1$ 的时候答案只有一种，即 $x=0$。

然后考虑 $k=2$ 的情况，我们发现若 $x$ 的值在 $1$ 到 $n$ 之间时，它必然会被某一个 $i$ 模成 $0$，之后遍历到的 $a_i$ 的值都会是 $0$ 且不会改变，符合 $k=2$ 的情况，但是我们发现，如果 $x$ 是 $n$ 的倍数，此时 $a_n=0$，也符合 $k=2$ 的情况。记 $kk$ 为从 $n+1$ 到 $m$ 之间的整数是 $n$ 的倍数的个数，则总答案为 $\min(m,kk+n)$。

之后考虑 $k=3$ 的情况，我们发现若 $x$ 的值在 $n+1$ 到 $m$ 之间，且 $x$ 不是 $n$ 的倍数，此时 $a_n=x \bmod n$，$a_n$ 值的范围在 $1$ 到 $n-1$ 之间，根据上面的结论可知，该值必然会在之后的遍历被模成 $0$，此时符合 $k=3$ 的情况，则总答案为 $\max(0,m-n-kk)$。

根据上面的情况可知，我们无法构造出一种 $a_i$ 的情况使得 $k>3$，则当 $k>3$ 时答案为 $0$。

## 代码描述

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
ll T,n,m,k;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m>>k;
		ll kk=0;
		if(m>=n) kk=m/n-1;//kk为从n+1到m之间的整数是n的倍数的个数
		if(k>3) cout<<0<<endl;
		else if(k==3) cout<<max(0ll,m-n-kk)<<endl;
		else if(k==2) cout<<min(m,kk+n)<<endl;
		else cout<<1<<endl;
	}
	return 0;
}
```

---

## 作者：aCssen (赞：1)

### Solution
我们忽略 $m$ 的限制，考虑 $a_{n+1}$ 的取值：
+ 当 $a_{n+1}=0$ 时，整个序列全为 $0$，此时序列中共有 $1$ 种数。
+ 当 $1 \le a_{n+1} \le n$  时，一定存在一个 $1 \le i \le n$，满足 $a_{n+1}=i$，则对于 $i<j \le n,a_j =a_{n+1}$，因为它们都比 $a_{n+1}$ 大，而对于 $1 \le j \le i,a_j=0$，这个显然，综上，此时序列中共有 $2$ 种数。
+ 当 $n<a_{n+1}$ 且 $a_{n+1} \bmod n \neq 0$ 时，在 $a_{n+1}$ 对 $n$ 取模后就变成了第二种情况，但因为 $n<m$，所以 $a_{n+1} \neq a_n$，故此时序列中共有 $3$ 种数。
+ 当 $n<a_{n+1}$ 且 $a_{n+1} \bmod n = 0$ 时，在 $a_{n+1}$ 对 $n$ 取模后就变成了第一种情况，前 $n$ 个数都为 $0$，又因为 $a_{n+1} \neq a_n$，所以此时序列中共有 $2$ 种数。

综上，我们得到以下结论：

+ 当 $k=1$ 时，输出 $1$。

+ 当 $k=2$ 且 $m \le n$ 时，由于 $a_{n+1} \in [1,n]$ 都满足条件，所以输出 $m$。

+ 当 $k=2$ 且 $m>n$ 时，输出 $n+\lfloor \frac{m}{n} \rfloor-1$，减 $1$ 是因为要去掉前 $n$ 个数的一组。

+ 当 $k=3$ 且 $m \le n$ 时，输出 $0$。
+ 当 $k=3$ 且 $m > n$ 时，输出 $(\lfloor \frac{m}{n} \rfloor-1) \times (n-1)+ m \bmod n$，因为每 $n$ 个数为一组，满足条件的是前 $n-1$ 个，第一组没有满足条件的数。
+ 当 $k>3$ 时，输出 $0$。

然后这题就做完了。
### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
void solve(){
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	if(k==1)
		printf("1\n");
	if(k==2){
		if(m<=n) printf("%d\n",m);
		else printf("%d\n",n-1+m/n);
	}
	if(k==3){
		if(m<=n) printf("0\n");
		else printf("%d\n",(m/n-1)*(n-1)+m%n);
	}
	if(k>3)
		printf("0\n");
}
int main(){
	int t=1;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：LCat90 (赞：1)

注意到题目只对 $a_{n+1}$ 进行了限定。并且对应关系说明了如果 $a_{n+1}$ 固定，那么整个 $a$ 就确定了。

然后考虑对应关系：$a_i=a_{i+1}\bmod i$，这说明 $a_i < i$。而题目要求的是相同的 $a_i$，这说明很可能出现一段连续的 $x$。

手推一下样例，并且注意到样例只给了一个很大的 $k$，且还无解。剩余 $k$ 都很小。就可以大胆推测：$k$ 很大时无解。

发现当 $a_{n+1}=x\le n$ 时，$x$ 这个值会一直延续直到遇到 $x$ 下标，此时变为 $0$，并且一直延续到最后，共 $2$ 个不同的值（当 $x=0$ 时只有 $1$ 个）；当 $a_{n+1}=x>n$ 时，$a_n$ 的时候就会进行突变，然后按照上面的方法继续，答案为 $3$。然后就大胆地猜测 $k$ 的上限是 $3$，超过 $3$ 无解。经过暴力认证正确。

你说得对，但是求方案数。

+ $k=1$。对应 $m=0$，故答案为 $1$。
+ $k=2$。对应 $0\le x\le n$ 的情况，但是还有一种情况是 $a_{n}=0,a_{n+1}\neq 0$，即 $x$ 是 $n$ 的倍数。
+ $k=3$。对应 $n<x\le m$ 的情况，注意减去 $k=2$ 中的特殊情况。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 5;
int T, s, a[N];
void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	int sb = m / n;
	if(k > 3) {
		puts("0");
		return ;
	}
	else if(k == 3) {
		cout << max(0ll, m - n - sb + 1) << "\n";
		return ;
	}
	else if(k == 2) {
		int ans = min(n, m);
		ans += max(0ll, m / n - 1);
		cout << ans << "\n";
		return ;
	}
	else if(k == 1) {
		puts("1");
		return ;
	} 
}
signed main() {
	cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

一个比较明显的结论是，不同的数字个数只可能是 $1,2,3$。

可以随手写一个暴力的输出程序，假定 $n$ 和 $m$，把所有可能的序列都输出来，就可以发现这个规律。

也可以感性思考一下。

如果第 $n+1$ 位是 $0$，那么整个序列都会是 $0$，个数也就是 $1$。

如果第 $n+1$ 位是一个小于 $n$ 的数 $x_0$，那么就会重复若干次 $x_0$，在第 $x_0$ 位开始变为 $0$，所以这种情况的个数是 $2$。

如果第 $n+1$ 位是一个 $n$ 的倍数 $x_1$，那么只会出现一次 $x_1$，此后都是 $0$，这种情况的个数也是 $2$。

其他情况就是不是 $n$ 的倍数并且大于 $n$ 的情况，假设填的是 $x_2$，那么第 $n+1$ 位是 $x_2$，第 $n$ 位就是 $x_2 \bmod n$，重复若干次后直到遇到第 $x_2 \bmod n$ 位，就会变为 $0$，因为 $x_2$ 不是 $n$ 的倍数，所以一定会有三个不同的数字。

所以如果要求的数量大于 $3$ 就无解，即为 $0$。

如果要求的数量是 $1$，只有一种情况。

如果要求的数量是 $2$，情况数就是 $n-1+\lfloor \frac m n\rfloor$。

如果要求的数量是 $3$，情况数就是 $m+1-1-(n-1+\lfloor \frac m n\rfloor)=m-n+1+\lfloor \frac m n \rfloor$。

需要注意 $m<n$ 的情况，这种情况时，数量为 $2$ 的答案就是 $m$，数量为 $3$ 的答案是 $0$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,a,b,c;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		if(c>3) puts("0");
		else
		{
			if(c==1) puts("1");
			else if(c==2) printf("%lld\n",min(b,a-1+b/a));
			else printf("%lld\n",max(0ll,b-a+1-b/a));
		}
	}
	return 0;
}
```

---

