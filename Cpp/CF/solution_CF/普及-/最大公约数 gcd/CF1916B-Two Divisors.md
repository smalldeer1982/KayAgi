# Two Divisors

## 题目描述

A certain number $ 1 \le x \le 10^9 $ is chosen. You are given two integers $ a $ and $ b $ , which are the two largest divisors of the number $ x $ . At the same time, the condition $ 1 \le a < b < x $ is satisfied.

For the given numbers $ a $ , $ b $ , you need to find the value of $ x $ .

 $ ^{\dagger} $ The number $ y $ is a divisor of the number $ x $ if there is an integer $ k $ such that $ x = y \cdot k $ .

## 说明/提示

For the first test case, all divisors less than $ 6 $ are equal to $ [1, 2, 3] $ , among them the two largest will be $ 2 $ and $ 3 $ .

For the third test case, all divisors less than $ 33 $ are equal to $ [1, 3, 11] $ , among them the two largest will be $ 3 $ and $ 11 $ .

For the fifth test case, all divisors less than $ 20 $ are equal to $ [1, 2, 4, 5, 10] $ , among them the two largest will be $ 5 $ and $ 10 $ .

For the sixth test case, all divisors less than $ 12 $ are equal to $ [1, 2, 3, 4, 6] $ , among them the two largest will be $ 4 $ and $ 6 $ .

## 样例 #1

### 输入

```
8
2 3
1 2
3 11
1 5
5 10
4 6
3 9
250000000 500000000```

### 输出

```
6
4
33
25
20
12
27
1000000000```

# 题解

## 作者：One_JuRuo (赞：11)

## 思路

看到题目要求求一个数 $x$，满足它的最大的两个因数分别是 $a$ 和 $b$，并且规定一个数本身不是他的因数。

首先 $x$ 需要是 $a$ 和 $b$ 的倍数，所以想到最小公倍数，如果不考虑最小公倍数等于 $b$，最小公倍数就一定是答案，因为最小公倍数是最小的满足是 $a$ 和 $b$ 倍数的数了，其他的答案都一定是最小公倍数乘以一个数 $k$，但是这样，$a\times k$ 和 $b\times k$ 就比原来的大，一定不是答案。

所以如果最小公倍数不是答案，就没有答案了，而题目又保证了存在答案，所以这种情况最小公倍数就是答案。

再考虑有些情况会导致最小公倍数等于 $b$，也就是 $a$ 是 $b$ 的因数。考虑到答案一定是 $b$ 的倍数，所以考虑答案是 $b$ 乘以几，首先如果是随便的一个 $k$，那么会导致 $a\times k$ 大于 $a$，使得 $a$ 不是次大的因数，所以我们考虑让 $a\times k=b$，这样才可能让 $a$ 成为次大因数，所以答案就是 $b\times \frac b a$。同样的，如果这个答案不合法，就不可能存在其他答案合法，题目又保证一定存在答案，所以这个答案正确。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,a,b,gc;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&a,&b),gc=__gcd(a,b),a/=gc,b/=gc,b*=a;//此时，b是最小公倍数除以最大公因数
		if(a==1) b*=b;//如果b是a的倍数，那么答案需要额外乘以b/a
		printf("%lld\n",b*gc);//记得把最大公因数乘回去
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：6)

## 分析

题目给出的是 $x$ 的两个小于 $x$ 的最大因子，首先考虑 $a$ 不整除 $b$ 的情况。既然 $a$ 不整除 $b$，那么 $a\times b$ 必定是 $x$ 的倍数，但是此时 $a,b$ 就不一定是最大的，所以需要除以一些东西，这个东西要尽可能大，又要保证除完之后 $x$ 是 $a,b$ 的倍数，所以自然想到结果是 $\frac{a\times b}{\gcd(a,b)}$，也就是 $\operatorname{lcm}(a,b)$。

下一步考虑 $b$ 是 $a$ 的倍数的情况。注意到 $x$ 可以表示为 $b\times k(k\in\mathbb{N}^+,k>1)$，那么如果 $k$ 比 $a$ 大，$a$ 就不是最大的了，除非 $k=b$，此时 $x=b^2$。如果 $k$ 比 $a$ 小，$k\times a$ 就比 $a$ 大，同理 $k\times a=b$，此时 $x=\frac{b^2}{a}$，显然此结果比上一个小，所以答案就是它。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long a,b;
		cin>>a>>b;
		if(b%a==0) cout<<b*b/a<<endl;
		else cout<<a*b/__gcd(a,b)<<endl;
	}
	return 0;
}

---

## 作者：__3E24AC7002AD9292__ (赞：3)

令 $p=\gcd(a,b)$，$i=\frac{a}{p}$，$j=\frac{b}{p}$。

此时由于 $1\leq a<b<x$，则 $1\leq i<j<\frac{x}{p}$。

分类讨论：

- $i=1$，则 $\frac{x}{p}$ 有且仅有三个因子，其中包含一个本身。可以得出 $\frac{x}{p}$ 为一个平方数 $j^2$，答案 $x$ 即为 $j^2p$。

- $i>1$，则 $\frac{x}{p}$ 显然为 $ij$，故 $ijp$ 即为 $x$ 的值。

证毕。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,a,b;
signed main(){
	cin>>t;
	while (t--){
		cin>>a>>b;
		int p=__gcd(a,b);
		a/=p,b/=p;
		if (a==1) a=b;//特判第一种讨论情况
		cout<<a*b*p<<'\n';
	}
	return 0;
}
```


---

## 作者：UncleSam_Died (赞：2)

### 解题思路
因为要求 $a$，$b$ 是 $x$ 的两个最大的因数（不包括本身），那么我们可以先找出 $a$ 和 $b$ 的最小公倍数，然后和 $b$ 比较，如果和 $b$ 相同，那么我们再找到 $a$ 和 $b$ 的最小的非 $1$ 因数，和 $b$ 相乘就是答案了。

### AC 代码
```cpp
#include<iostream>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 100005
ll a,b,p[N];int cnt;
inline bool Prim(int x){
    for(register int i=2;i*i<=x;++i)
        if(x%i==0) return false;
    return true;
}
inline void init(){
    for(register int i=2;i<=100000;++i)
        if(Prim(i)) p[++cnt]=i;
}
inline void work(){
    scanf("%lld%lld",&a,&b);
    ll ans=(a*b)/std::__gcd(a,b);
    if(ans!=b){
        printf("%lld\n",ans);
        return;
    }
    ll minta=(a==1?1e9:a),mintb=b;
    for(register ll i=1;p[i]*p[i]<=a&&i<=cnt;++i){
        if(a%p[i]==0){minta=p[i];break;}
    }
    for(register ll i=1;p[i]*p[i]<=b&&i<=cnt;++i){
        if(b%p[i]==0){mintb=p[i];break;}
    }
    ans*=std::min(minta,mintb);
    printf("%lld\n",ans);
}signed main(){
    srand(114514);
    srand(rand());
    srand(time(0));
    init();
    int T;scanf("%d",&T);
    while(T--) work();
    system("pause");
}
```

---

## 作者：zzx0102 (赞：1)

这里令 $x<y$。

显然可得当 $y$ 不是 $x$ 的倍数时，答案为 $\operatorname{lcm}(x,y)$。

因为如果更大的数 $a$ 来，$x,y$ 就一定不是最大的两个除数了，因为 $\operatorname{lcm}(x,y) \mid a$。

如果 $x\mid y$ 时，答案是啥呢？

这里答案是 $\dfrac{y^2}{x}$。

我们令答案 $p=ky$，显然如果 $k>x$，就不符合条件了。

显然 $p$ 除去最小的两个质因子就是 $x,y$，所以 $x$ 要么是 $\dfrac{p}{q}$ 或 $\dfrac{p}{k^2}$。

如果是 $\dfrac{p}{q}$，那么就不满足 $x\mid y$，所以 $x=\dfrac{p}{k^2}$。

然后得 $kx=y$，即 $p=\dfrac{y^2}{x}$。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int main() {
	ios::sync_with_stdio(0);
	int t; cin >> t;
	while(t--) {
		int x, y; cin >> x >> y; if(x > y) swap(x, y);
		if(y % x) cout << 1ll * x * y / __gcd(x, y) << '\n';
		else {
			cout << 1ll * y / x * y << '\n';
		}
	}
	return 0;
}
```

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1916B)

## 题意

给出 $x$ 的次大和最大因子 $a$ 和 $b$（这里规定因子不能等于 $x$ 本身），求 $x$。保证有解。

## 分析

显然最大的因子是又 $x$ 去掉一个最小的质因子 $p$ 得到的，次小因此可能由 $x$ 去掉一个次小的质因子 $q$，也可能是 $b$ 又去掉了一个因子 $p$ 得到的。

所以 $b=\frac{x}{p},a=\frac{x}{q}$ 或 $b=\frac{x}{p},a=\frac{x}{p^2}$。

第一种情况中， $b$ 相对 $a$ 没有 $p$ 这个因子，所以 $b$ 不是 $a$ 的倍数。他们缺失的因子都是对方有的，所以 $x$ 为他们的最小公倍数。

第二种情况中， $b$ 是 $a$ 的倍数。直接求出因子 $p$，那么 $x=bp=\frac{b^2}{a}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
    long long x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
//const int N=;
int t,n; 
ll a,b;
ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
int main(){
	t=read();
	while(t--){
		a=read();b=read();
		ll c=gcd(a,b);
		if(b%a==0) cout<<b*(b/a)<<endl;
		else cout<<c*(b/c)*(a/c)<<endl;
	}
    return 0;
}
```


---

## 作者：Luzhuoyuan (赞：0)

### 题目链接

[[to Luogu]](https://www.luogu.com.cn/problem/CF1916B) [[to Codeforces]](https://codeforces.com/contest/1916/problem/B)

### 题意简述

给出两个正整数 $a,b$，求任意正整数 $x$ 使得 $a,b$ 是 $x$ 的最大的小于 $x$ 的两个因数。每个测试点 $t$ 组测试数据。数据保证有小于等于 $10^9$ 的解。

$$1\le a<b\le 10^9,1\le t\le 10^4$$

### 做法

最大因数好像不太好搞，考虑转化一下，显然 $\frac{x}{b}$ 和 $\frac{x}{a}$ 是 $x$ 的最小的大于 $1$ 的两个因数，那么会有以下两种情况：

1. 它们分别是 $x$ 的两个最小的质因数，此时这两数没有倍数关系，$a,b$ 也没有倍数关系；
2. 它们分别是 $x$ 的最小质因数及其平方，此时 $\frac{x}{b}|\frac{x}{a}$，也就有 $a|b$。

这样就分成两种情况。如果 $a|b$，那么可以求出 $x$ 的最小质因数 $p=\frac{b}{a}$，则存在 $x=bp=\frac{b^2}{a}$；否则，答案显然就为 $a,b$ 两数的最小公倍数。简单计算即可，复杂度为求最小公倍数的复杂度 $O(\log b)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,x,y;
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&x,&y);
        if(y%x)printf("%lld\n",x*y/__gcd(x,y));
        else printf("%lld\n",y*y/x);
    }
    return 0;
}
```

（逃

---

