# Digital root

## 题目描述

一个非负数的数字根由反复的数位和计算得来，每一次计算
使用前一次计算得来的结果计算数位和，直到计算结果为1位数为止。
若将x的数字根称作S(x)，则S(5)=5

S(38)=S(3+8=11)=S(1+1=2)=2

S(10)=S(1+0=1)=1

现在需要你找出数字根为x的第k个正数。（每个测试点有n个这样的问题）

## 样例 #1

### 输入

```
3
1 5
5 2
3 1
```

### 输出

```
5
38
19
```

# 题解

## 作者：SqrtSecond (赞：2)

我们首先还是分析一下题面中给出的$S(x)$的结果。

## 第一组数据：$S(38)=2$

首先，$S(38)=S(3+8)=S(11)$，$38$的数字和为$11$,**即$38$与$11$模$9$同余。**

然后，$S(11)=S(1+1)=S(2)$，$11$的数字和为$2$，**即$11$与$2$模$9$同余。**

因此，**$38$模$9$余$2$，而且$38$的数字根为$2$。**

有没有发现什么规律？

再看看第二组：

## 第二组数据：$S(10)=1$

**$10$模$9$余$1$，而$10$的数字根为$1$。**

于是我们可以得到一个猜想：

> ## 某个数的数字根就为这个数模$9$的余数。

证明也不难，我们采用归纳法。

易知当$1\le x\le 9$时，$S(x)=x$。

若当$x=1,2,3,…,k$时有$S(x)=x\bmod9$成立

则当$x=k+1$时

设$x'$为$x$的数字和

则有$S(x)=S(x')$

而$x\equiv x'\pmod{9}$且$x'<x$

所以$S(x)=S(x')=x'\bmod 9=x\bmod 9$

于是可得，对于任意整数$n$，$S(n)=n\bmod9$

附上~~简洁的~~代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,x;//要开long long 
int main()
{
	scanf("%lld",&n);
	while(n--)
	{
		scanf("%lld%lld",&k,&x);
		printf("%lld\n",(k-1)*9+x);//多组数据换行 
	}
	return 0;//养成好习惯 
}
```

---

## 作者：SunsetVoice (赞：1)

鉴定为水题。

令伪数字根指一个数各个数位上数字的和，则一个数的数字根指的是其伪数字根的伪数字根的伪数字根——直到一个数的伪数字根 $\le 10$。

一个数的数字根等于其模 $9$ 的值。（证明在小学课本上，真的！），但如果值为 $0$ 需要看做 $9$。

code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	int i,j,n,T;
	cin>>T;
	while(T--){
		cin>>i>>j;
		cout<<9*i-9+j<<endl;
	}
	system ("pause");
}

```


---

## 作者：cff_0102 (赞：1)

众所周知，一个数的数字根就是它除以 $9$ 的余数（余 $0$ 相当于余 $9$）。

题目要求出第 $k$ 个数字根为 $x$ 的数，那就相当于求第 $k$ 个除以 $9$ 余 $x$ 的数。

所以答案就是 $9\times(k-1)+x$。

题目数据范围达到了 $10^{12}$，所以要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){//题目有 t 组数据 
		long long k,x;cin>>k>>x;
		cout<<9*(k-1)+x<<endl;//别忘记换行 
	} 
	return 0;
}
```

---

## 作者：_louhc (赞：1)

# 思路

这题看上去很不可做的样子,实际上找到规律就炒鸡简单。

先打表找规律

```
S(1)=1
S(2)=2
..
S(10)=1
S(11)=2
..
S(18)=9
S(19)=1
```

不管怎么说吧,根据从1到1000所有的数(自己写个代码验证就好了)Digital root都是从1到9不断循环的。

咋证明呢？我们先来证明一个引理：

设$F(N)$表示$N$每位数的和。$F(N)\equiv N(\mod 9)$

![](https://cdn.luogu.com.cn/upload/pic/50593.png)  

实际上,$S(N)$就是若干$F$运算嵌套在一起。

即$S(N)=F(F(F(...F(N))))$

而根据上述结论来看$N\equiv F(N) \equiv F(F(N))\equiv F(F(F(N)))....(\mod 9)$

所以,$S(N)\equiv N(\mod 9)$

而$S(N)$不为0且为个位数,因此$S(N)=(N-1)\mod 9+1$

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long

int T;
LL k; int x;

int main(){
	scanf( "%d", &T );
	while( T-- ) scanf( "%I64d%d", &k, &x ), printf( "%I64d\n", ( k - 1 ) * 9 + x );
	return 0;
} 
```



---

## 作者：ciwomuli (赞：1)

经过打表找规律我们可以发现S函数是1-9循环的
让后就可以做了
打表代码
```

const int maxn = 35;
int S[maxn];
int main(){
    int t;
    read(t);
    for(int i=1;i<=9;i++)
        S[i] = i;
    for (int i = 10; i <= 30;i++){
        int sum=0;
        int tmp=i;
        while(tmp){
            sum+=tmp%10;
            tmp /= 10;
        }
        S[i] = S[sum];
        cout << i<<" "<< S[i] << endl;
    }
}
```
code:
```cpp
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#define LL long long
#define P pair<int,int>
using namespace std;
template <typename T>
inline void read(T &t)
{
    int f = 0, c = getchar();
    t = 0;
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        t = t * 10 + c - 48, c = getchar();
    if (f)
        t = -t;
}
template <typename T, typename... Args>
inline void read(T &t, Args &... args)
{
    read(t);
    read(args...);
}
const int maxn = 35;
int S[maxn];
int main(){
    int t;
    read(t);
    for (int i = 1; i <= t;i++){
        LL k,x;
        read(k,x);
        cout << (k - 1) * 9 + x << endl;
    }
}
```                                   

---

## 作者：Frictional (赞：0)

这道题可以找下规律。我们打表找下规律，就会发现，每个数的数字根的是 $1\sim9$ 重复出现。这样我们就可以每次询问 $O(1)$ 求出来了。

## AC code
```cpp
#include<bits/stdc++.h>//M
#define int long long
using namespace std;
int n;
int k,x;
signed main(){
	cin>>n;
	while(n--){
		cin>>k>>x;
		cout<<9*(k-1)+x<<endl;
	}
	return 0;
}
```


---

