# GCD Sum

## 题目描述

The $ \text{ $ gcdSum $ } $ of a positive integer is the $ gcd $ of that integer with its sum of digits. Formally, $ \text{ $ gcdSum $ }(x) = gcd(x, \text{ sum of digits of } x) $ for a positive integer $ x $ . $ gcd(a, b) $ denotes the greatest common divisor of $ a $ and $ b $ — the largest integer $ d $ such that both integers $ a $ and $ b $ are divisible by $ d $ .

For example: $ \text{ $ gcdSum $ }(762) = gcd(762, 7 + 6 + 2)=gcd(762,15) = 3 $ .

Given an integer $ n $ , find the smallest integer $ x \ge n $ such that $ \text{ $ gcdSum $ }(x) > 1 $ .

## 说明/提示

Let us explain the three test cases in the sample.

Test case 1: $ n = 11 $ :

 $ \text{ $ gcdSum $ }(11) = gcd(11, 1 + 1) = gcd(11,\ 2) = 1 $ .

 $ \text{ $ gcdSum $ }(12) = gcd(12, 1 + 2) = gcd(12,\ 3) = 3 $ .

So the smallest number $ \ge 11 $ whose $ gcdSum $ $ > 1 $ is $ 12 $ .

Test case 2: $ n = 31 $ :

 $ \text{ $ gcdSum $ }(31) = gcd(31, 3 + 1) = gcd(31,\ 4) = 1 $ .

 $ \text{ $ gcdSum $ }(32) = gcd(32, 3 + 2) = gcd(32,\ 5) = 1 $ .

 $ \text{ $ gcdSum $ }(33) = gcd(33, 3 + 3) = gcd(33,\ 6) = 3 $ .

So the smallest number $ \ge 31 $ whose $ gcdSum $ $ > 1 $ is $ 33 $ .

Test case 3: $ \ n = 75 $ :

 $ \text{ $ gcdSum $ }(75) = gcd(75, 7 + 5) = gcd(75,\ 12) = 3 $ .

The $ \text{ $ gcdSum $ } $ of $ 75 $ is already $ > 1 $ . Hence, it is the answer.

## 样例 #1

### 输入

```
3
11
31
75```

### 输出

```
12
33
75```

# 题解

## 作者：张语诚ZYC (赞：1)

## 题目翻译

定义一种新运算 $\texttt{gcdSum(x)}$，通俗的解释，如果 $s$ 是 $n$ 的每一位数字之和，$\texttt{gcdSum(x)}=\gcd(x,s)$，给定一个 $n$ 求出一个最小的 $x$ 使 $\texttt{gcdSum(x)}>1$ 且 $x \ge n $ 。

## 题目分析

还是那句老话：$\text{\color{red}{暴力出奇迹}}$，关于时间复杂度，会在稍后分析。

已知 $n$ ，要向上寻找一个值寻找 $x$ 使 $\texttt{gcdSum(x)}>1$，我们只需要暴力枚举就可以。使用欧几里得法暴力判断二者的公因数是否大于 $1$。

关于为什么不会超时：

先复习一下 $3$ 的倍数的特征：能被 $3$ 整除，且各个数位的和是 $3$ 的倍数。也就是说，只要 $x$ 是 $3$ 的倍数，就一定满足 $\texttt{gcdSum(x)}>1$，也就是说，最多在每一组数据上枚举三次，不会超时。 

## $\texttt{AC Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long int read_long_long_int() {
	long long int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			w=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
long long int gcd(int a,int b) {
	return (!b ? a : gcd(b, a%b));
}
int main() {
	int t=read_long_long_int();
	for(int ti=0; ti<t; ti+=1) {
		long long int n=read_long_long_int();
		long long int backup=n;
		while(true) {
			long long int x=n;
			long long int cnt=0;
			long long int t=x;
			while(x!=0) {
				cnt+=x%10;
				x/=10;
			}
			if(gcd(t,cnt)>1) {
				break;
			}
			n+=1;
			if(n-backup==3){
				n-=3;
			}
		}
		printf("%lld \n",n);
	}
	return 0;
}

```

## 后记

如果你不知道什么是$\texttt{\color{Fuchsia}{gcd}}$，请点击[这里](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308)。

如果你不知道什么是$\texttt{\color{Fuchsia}{欧几里得法}}$，请点击[这里](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95/1647675)。

温馨提示：十年$\texttt{OI}$一场空，不开$\texttt{\color{Fuchsia}{long long }}$见祖宗。


$$\texttt{The End by Yucheng}$$

---

## 作者：Leasier (赞：1)

看完题面不难想到暴力枚举，然后交上去居然 AC 了。

为什么没有 TLE 呢？我们来分析一下。

考虑一个整除规律：任何能被 $3$ 整除的数，其各位和能被 $3$ 整除。

用数值原理即可证得以上规律。

所以，**最多**枚举 $3$ 个数，就可以找到一个符合题意的 $x$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a % b);
}

inline ll gcdsum(ll n){
	ll m = 0;
	for (register ll i = n; i > 0; i /= 10){
		m += i % 10;
	}
	return gcd(n, m);
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		ll n, ans;
		scanf("%lld", &n);
		ans = n;
		while (gcdsum(ans) == 1) ans++;
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：cunzai_zsy0531 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF1498A)

考场上有点小蒙，冷静下来之后发现，只要是 $3$ 的倍数都必定满足 $gcdSum\geq 3$。所以对于任意一个 $n$，在 $n,n+1,n+2$ 中都必定有一个 $gcdSum > 1$，即可 $O(t)$ 求解。

代码:

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long gcd(long long a,long long b){return !b?a:gcd(b,a%b);}
bool ggcd(long long n){
	int res=0;long long tmp=n;//注意这个地方修改了n，需要再开一个变量存n的值。注意变量类型！！！
	while(n) res+=n%10,n/=10;
	return gcd(tmp,res)>1;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		long long n;
		scanf("%lld",&n);
		while(!ggcd(n)) ++n;//只需要判断最多3次，复杂度 O(1)
		printf("%lld\n",n);
	}
	return 0;
}
```


---

## 作者：vectorwyx (赞：0)

看到各位数码之和不难联想到 $3$ 的整除特性：一个数被 $3$ 整除的充要条件是各位数码之和被 $3$ 整除，所以 $3$ 的倍数一定满足条件。又因为连续的三个自然数中一定有一个数是 $3$ 的倍数，所以答案一定小于等于 $n+2$，对 $n,n+1,n+2$ 分别进行判断即可。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register ll i=x;i<=y;++i)
#define go(i,x,y) for(register ll i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

bool check(ll x){
	ll t=x,s=0;
	while(x){
		s+=x%10;
		x/=10;
	}
	return __gcd(t,s)>1;
}

void work(){
	ll n;
	cin>>n;
	fo(i,n,n+2)	if(check(i)){
		printf("%lld\n",i);
		return;
	}
	//puts("");
}

int main(){
	int T=read();
	while(T--) work(); 
	return 0;
}
```


---

## 作者：SpeedStar (赞：0)

#### 算法分析

注意到，一个数如果是 $3$ 的倍数，那么它的 `digitsum` 一定也是 $3$ 的倍数。所以，每三个数里至少存在一个数的 `gcdsum` 大于 $1$。

#### C++ 代码

```cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using ll = long long;

ll gcd_sum(ll n) {
	ll tmp = n, digitsum = 0;
	
	while (tmp) {
		digitsum += tmp % 10;
		tmp /= 10;
	}
	
	ll res = std::gcd(n, digitsum);
	return res;
}

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		ll n;
		cin >> n;
		if (gcd_sum(n) > 1) cout << n << '\n';
		else if (gcd_sum(n + 1) > 1) cout << n + 1 << '\n';
		else if (gcd_sum(n + 2) > 1) cout << n + 2 << '\n';
	}
	
	return 0;
}
```


---

## 作者：Daidly (赞：0)

考虑怎么算 $\sum^k_{i=1}{a_i}$。

将这个数每一位模 $10$，每次除 $10$，相加即可。

判断是否成立：
```cpp
bool check(ll n){
	ll tmp=n;
	int sum=0;
	while(tmp){
		sum+=tmp%10;
		tmp/=10;
	}
	return gcd(tmp,sum)>1;
}
```
求最大公因数：
```cpp
ll gcd(ll a,ll b){
	if(b==0)return a;
    return gcd(b,a%b);
}
```

考虑一个特殊数使得 $\gcd(x,\sum^k_{i=1}{a_i})$ 与它有一些联系，$3$。

因为 $3$ 的倍数的 $gcdSum\ge 3$。

而每次最多只用 `check` 三次。

$O(t)$。

开 `long long`。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a,ll b){
	if(b==0)return a;
    return gcd(b,a%b);
}
bool check(ll n){
	ll tmp=n;
	int sum=0;
	while(n){
		sum+=n%10;
		n/=10;
	}
	return gcd(tmp,sum)>1;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		ll n;
		cin>>n;
		while(check(n)==false){
			n++;
		}cout<<n<<endl;
	}
	return 0;
}
```


---

