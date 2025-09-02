# 「WyOJ Round 1」启 · 破茧初阳

## 题目背景

>一叶渔船两小童，收篙停棹坐船中。怪生无雨都张伞，不是遮头是使风。
>
>—— 杨万里 《舟过安仁》

## 题目描述

求从公元后 $1$ 年至公元后 $n$ 年有多少年为快乐年？  

快乐年的定义为：能被 $a$ 整除且不能被 $b$ 整除，或者是能被 $c$ 整除的年份，即将闰年定义中的 $4,100,400$ 依次替换为 $a,b,c$。

## 说明/提示

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le n\le 10^{18}$，$1\le a,b,c\le 10^9$。

| 测试点 | 特殊性质 |
| :-----------: | :-----------: |
| $1\sim 4$ | $1\le T\le 5$，$1\le n\le 10^6$ |
| $5\sim 10$ | 无特殊性质 |


## 样例 #1

### 输入

```
5
2024 5 4 7
1024 5 10 15
114514 5 3 9
998244 3 5 3
353998 7 9 6```

### 输出

```
549
136
27991
332748
98332```

# 题解

## 作者：TimADE (赞：3)

## 思路

这道题看起来很水，直接把闰年判断里的代码改一下就好了，但这样会 WA + RE。

为什么呢？因为 $n$ 可以非常大（高达 $10^{18}$），直接遍历每个年份是不可行的，必须使用数学方法进行高效计算。

所以为了高效计算，我们使用容斥原理来避免重复计算，具体方法就是总数为满足条件 A 的数目加上满足条件 B 的数目，再减去同时满足 A 和 B 的数目。

我们用 LCM（最小公倍数） 来搞定这个问题，判断当 LCM 超过 $n$ 时返回 $0$。

## 答案公式

然后就可以写出公式：

$sum = \left \lfloor \frac{n}{a} \right \rfloor - \left \lfloor \frac{n}{\operatorname{lcm}(a,b)} \right \rfloor  + \left \lfloor \frac{n}{c} \right \rfloor - \left \lfloor \frac{n}{\operatorname{lcm}(a,c)} \right \rfloor  - \left \lfloor \frac{n}{\operatorname{lcm}(a,b,c)} \right \rfloor $

注：因为 $n$ 高达 $10^{18}$，所以要开 long long！

## AC Code

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
ll lcm(ll x, ll y, ll n) {
    ll g = __gcd(x, y);
    x /= g;
    return (y > n / x) ? n + 1 : x * y;
}
ll ck(ll n, ll x) {
    return n / x;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n, a, b, c;
        cin >> n >> a >> b >> c;
        ll d = lcm(a, b, n);
        ll e = lcm(a, c, n);
        ll f = lcm(e, b, n);
        ll g = ck(n, a);
        ll h = ck(n, d);
        ll i = ck(n, c);
        ll j = ck(n, e);
        ll k = ck(n, f);
        ll m = g - h + i - j + k;
        cout << m << "\n";
    }
    return 0;
}
```

---

## 作者：Tomwsc (赞：2)

# P12226 「WyOJ Round 1」启 · 破茧初阳 题解

## 思路

发现数据范围很大，所以我们考虑快速计算答案。如何快速计算答案呢？推式子！

很明显，这道题目只需要我们简单的推个式子即可。设在 $n$ 以内能被 $a$ 整除的数的个数为 $x$，能被 $\operatorname{lcm}(a,b)$ 整除的数的个数为 $y$，能被 $c$ 整除的数的个数为 $z$，能被 $\operatorname{lcm}(a,c)$ 整除的数的个数为 $p$，能被 $\operatorname{lcm}(a,b,c)$ 整除的数的个数为 $q$，答案为 $ans$，则有：

$$ans = x-y+z-p+q$$

为什么，画个韦恩图然后容斥一下就清楚了……

![](https://cdn.luogu.com.cn/upload/image_hosting/e6uz77q6.png)

如图，阴影部分即为所求。所以令人想到用 $a$ 的圆圈加上 $c$ 的圆圈。但因为橙色部分会被多次计算，所以剪掉 $a$ 与 $b$ 以及 $a$ 与 $c$ 重合的部分，即 $\operatorname{lcm}(a,b)$ 和 $\operatorname{lcm}(a,c)$。此时，不难发现，绿色部分被多减掉了一次，所以还要再加回来，于是便有了加上绿色的部分，即 $\operatorname{lcm}(a,b,c)$。

接下来的问题就变成怎样计算最小公倍数了，有这么一个式子：

$$\operatorname{lcm}(a,b)=a\div \gcd(a,b)\times b$$

所以只要知道两数的最大公因数即可，辗转相除法可以计算两数的最大公因数，并且时间复杂度是 $O(\log \min(a,b))$。

## 代码

**注意**，数据很大，要开 ```__int128```。

```cpp
#include<bits/stdc++.h>
#define int __int128
#define inf (1ll << 62)
#define regint register int
#define pb push_back
#define mp make_pair
#define PII pair<int , int>
using namespace std;
int t , n , a , b , c;

int gcd(int a , int b) {
	if(!b)
		return a;
	return gcd(b , a % b);
}

inline int lcm(int a , int b) {
	return a / gcd(a , b) * b;
}

inline int read() {
	char c = getchar();
	int x = 0 , s = 1;
	while(c < '0' || c > '9') {
		if(c == '-')
			s = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * s;
}

void write(int x) {
	if(x >= 10)
		write(x / 10);
	putchar(x % 10 + '0');
	return;
}

signed main() {
	t = read();
	while(t --) {
		n = read();
		a = read();
		b = read();
		c = read();
		write(n / a - n / lcm(a , b) + n / c - n / lcm(a , c) + n / lcm(lcm(a , b) , c));
		printf("\n");
	}
	return 0;
}
```

---

## 作者：fiee_Lina (赞：2)

# [P12226 「WyOJ Round 1」启 · 破茧初阳](https://www.luogu.com.cn/problem/P12226)

### 题目

求从公元后 $1$ 年至公元后 $n$ 年有多少年为快乐年？  

快乐年的定义为：能被 $a$ 整除且不能被 $b$ 整除，或者是能被 $c$ 整除的年份，即将闰年定义中的 $4,100,400$ 依次替换为 $a,b,c$。

### 思路

这里有两种情况： 
- **能被 $a$ 整除且不能被 $b$ 整除**。
- **能被 $c$ 整除的年份**。

根据容斥原理，我们就可以写成 $ A + B - A \cap B $。

第一种情况就是 $ \lfloor \frac{n}{a} \rfloor - \lfloor \frac{n}{\operatorname{lcm}(a,b)} \rfloor $。

第二种情况就是 $ \lfloor \frac{n}{c} \rfloor $。

而两种情况的并集就是 $ \lfloor \frac{n}{\operatorname{lcm}(a,c)} \rfloor + \lfloor \frac{n}{\operatorname{lcm}(\operatorname{lcm}(a,b),c)} \rfloor $。

### Code


```cpp
#include<bits/stdc++.h> 
#define int __int128//注意由于数据过大，需要用到 __int128 来代替 long long
using namespace std;

int T;
int n,a,b,c;

void read(int &x) {
    x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}

void print(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int gcd(int a,int b)
{
    while(b!=0)
	{
        a%=b;
        swap(a,b);
    }
    return a;
}

int lcm(int a,int b)
{
	return (a/gcd(a,b))*b;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	read(T);
	while(T--)
	{
		read(n),read(a),read(b),read(c);
		int a_b=lcm(a,b);
		int a_c=lcm(a,c);
		int a_b_c=lcm(a_b,c);
		
		int x=n/a-n/a_b;
		int y=n/c;
		int x_y=n/a_c-n/a_b_c;
		print(x+y-x_y);
		printf("\n");
	}
	
	return 0;
}
```

---

## 作者：Meteor1212 (赞：2)

## 1.题意简述
共 $T$ 组，每一组给定一个数 $n$ 和 $A,B,C$ 求出满足能被 $A$ 整除且不被 $B$ 整除，或能被 $C$ 整除的数的个数。
## 2.解决方法
按照题目要求可以分为三块：能被 $A$ 整除且不被 $B$ 整除（记为 $left$）和能被 $C$ 整除的数的个数（记为 $right$），能被 $A$ 和 $C$ 整除但是不能被 $B$ 整除的数（记为 $mid$）。

利用容斥原理可知答案为总面积。

即 $left+right-mid$。

![](https://cdn.luogu.com.cn/upload/image_hosting/tgs6ynuh.png)

### 介绍 $\operatorname {lcm}$：

$\operatorname {lcm}$ 是最小公倍数。

定理：$a$，$b$ 两个整数的最小公倍数乘以它们的最大公约数等于 $a$ 和 $b$ 本身的乘积。

可以由此倒推出 $ \operatorname {lcm} $ 的公式为：
```
int lcm(int a,int b)
{
		return a/gcd(a,b)*b;
}
```
我们可以发现：
### 对于第一块：


能被 $A$ 整除的个数减去同时能被 $A$ 和 $B$ 整除的个数 就可以将第一块完成（避免被 $B$ 整除同时保证被 $A$ 整除）。


即 $left = $ $\lfloor \frac{n}{a} \rfloor-\lfloor \frac{n}{\operatorname {lcm}(a,b)} \rfloor$。

### 对于第二块：
能被 $C$ 整除的个数。

即 $right=$ $\lfloor \frac{n}{c} \rfloor$。


### 对于第三块：
能被 $A$ 和 $C$ 整除但是不能被 $B$ 整除的数。

即 $mid=$ $\lfloor \frac{n}{\operatorname {lcm}(a,c)} \rfloor-\lfloor \frac{n}{\operatorname {lcm}(a,\operatorname {lcm}(b,c))} \rfloor$。

答案为 $left+right-mid$。

## 3.注意事项
在求 $\operatorname {lcm}$ 的过程中会爆`long long` 利用 `__int128`。

使用`__int128`时用快读快写实现输入输出。

## 4.代码实现
```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
inline __int128 read()//快读 
{
	__int128 x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if (ch == '-') 
			f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(__int128 x)//快写 
{
	if (x<0) putchar('-'),x=-x;
	if (x>9) write(x/10);
	putchar(x%10+'0');
}
//求lcm 
__int128 gcd(__int128 a,__int128 b)
{
	 return b>0?gcd(b,a%b):a;
}
__int128 lcm(__int128 a,__int128 b)
{
		return a/gcd(a,b)*b;
}
int main()
{
	
	__int128 t;
	t=read();
	while(t--)
	{
		__int128 n,a,b,c;
		n=read(),a=read(),b=read(),c=read(); 
		__int128 left=n/a-(n/lcm(a,b));
		__int128 right=n/c;
		__int128 mid=n/lcm(a,c)-n/lcm(a,lcm(b,c));
		write(left+right-mid);
		puts("");
	}
	return 0;
}
```
时间复杂度 $O(T\log n)$。

---

## 作者：EDG_AKUYTRE (赞：1)

## P12226 「WyOJ Round 1」启 · 破茧初阳

---


不难发现是容斥，不妨设条件  $A$ 为当前年份能被  $a$  整除且不能被  $b$  整除，条件  $B$  为能被  $c$  整除，则答案为：满足条件 $A$ 的年份数 + 满足条件 $B$ 的年份数 - 同时满足条件 $A$ 和条件 $B$ 的年份数。求 $\operatorname{lcm}$ 可以通过 $a×b÷\gcd(a,b)$ 得到，因为两个数的最小公倍数与两个数的最大公约数的成绩就是这两个数的乘积。

注意中间结果会爆 long long ，可以上 ```__int128```
。

很简单，直接上代码。
```cpp
#include<iostream>
#include<cstdio>
#include<map>
#define int __int128
using namespace std;
inline int read(){
	char ch=getchar();int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*f;
}
inline void write(int x){
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
int lcm(int a,int b){
	return a*b/gcd(a,b);
}
int solve(int n,int a,int b,int c){
	int cnt1=n/a-n/lcm(a,b);
	int cnt2=n/c;
	int cnt3=n/lcm(a,c)-n/lcm(lcm(a,b),c);
	return cnt1+cnt2-cnt3;
}
int T;

signed main(){
	T=read();
	while(T--){
		int n,a,b,c;
		n=read();a=read();b=read();c=read();
	//	cin>>n>>a>>b>>c;
		int ans=solve(n,a,b,c);
		write(ans);
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：WuMin4 (赞：1)

## 思路

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rx7xnxo2.png)

显然答案即为阴影部分。

首先我们先找出能被 $a$ 整除但不能被 $b$ 整除的数。

![](https://cdn.luogu.com.cn/upload/image_hosting/x5mo9fvb.png)

能被 $a$ 整除但不能被 $b$ 整除的数显然为黄色区间，即为能被 $a$ 整除的所有数与能同时被 $a,b$ 整除的数之差。

![](https://cdn.luogu.com.cn/upload/image_hosting/awxi6rli.png)

然后我们再加上能被 $c$ 整除的数，可以发现橙色部分被算了两次。

![](https://cdn.luogu.com.cn/upload/image_hosting/zk4vwcuf.png)

此时我们可以选择加上能同时被 $a,b,c$ 整除的数，再把橙色区域减去，即减去能同时被 $a,c$ 整除的数，便得到了答案。

最后答案即为：

$$
\lfloor\frac{n}{a}\rfloor-\lfloor\frac{n}{\text{lcm}(a,b)}\rfloor+\lfloor\frac{n}{c}\rfloor+\lfloor\frac{n}{\text{lcm}(a,b,c)}\rfloor-\lfloor\frac{n}{\text{lcm}(a,c)}\rfloor
$$

注意因为 $a,b,c\le 10^9$，所以 $\text{lcm}(a,b,c)$ 的上界来到了 $10^{27}$，直接计算需要开 `__int128`。~~但是我太懒了，所以我用 python 写过去了。~~

## 代码

```py
from math import *
T=int(input())
for i in range(T):
    n,a,b,c=map(int,input().split())
    print(n//a-n//lcm(a,b)+n//c+n//lcm(a,b,c)-n//lcm(a,c))
```

[记录](https://www.luogu.com.cn/record/214223480) ~~挑战最劣解~~

---

## 作者：zxh_qwq (赞：1)

### P12226 题解

考虑容斥。

令能被 $a$ 整除且不能被 $b$ 整除为条件 $A$，令能被 $c$ 整除 为条件 $B$。

答案就是满足 $A$ 条件的年份加满足 $B$ 条件的年份，再减去同时满足 $A,B$ 两个条件的年份。

从简单的开始，满足 $B$ 条件的年份有且仅有 $\dfrac{c}{n}$ 个。

接下来观察满足 $A$ 的条件的年份。容易发现最小正周期为 $T_1=\operatorname{lcm} (a,b)$。所以分整周期和剩下的部分就行了。每个周期一共是 $(b-1)$ 个满足条件的年份。剩余的部分如果长度为 $k$ 的话，还会有 $\dfrac{k}{a}$ 个满足条件的年份。

同时满足 $A,B$ 条件的，相当于能被 $a,c$ 整除，不能被 $b$ 整除。分析思路同上一段，只需要将其中的 $a$ 改为 $\operatorname{lcm} (a,c)$ 就行了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll __int128
using namespace std;
ll gcd(ll a,ll b){
    if(b==0)return a;
    return gcd(b,a%b);
}
main(){
    int t;
    cin>>t;
    while(t--){
        int tn,ta,tb,tc;
        cin>>tn>>ta>>tb>>tc;
        ll n=tn,a=ta,b=tb,c=tc;
        ll k2=n/c; //task2
        
        ll temp=a/gcd(a,b)*b;
        ll cycles=n/temp;
        ll remain=n%temp;
        ll k1=cycles*(temp/a-1)+remain/a; //task 1

        ll d=a/__gcd(a,c)*c;
        temp=d/__gcd(b,d)*b;
        cycles=n/temp;
        remain=n%temp;
        ll k12=cycles*(temp/d-1)+remain/d;

        int ans=k1+k2-k12;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：canwen (赞：0)

小清新容斥题，三个 `int` 相乘 `unsigned long long` 也不行，注意开 `__int128`。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ciibdlwk.png)。

答案即红色部分：$\textcircled{1} +\textcircled{2}+\textcircled{3}+\textcircled{4}+\textcircled{5}$。

比较显然的：

$\textcircled{2}+\textcircled{3}+\textcircled{4}+\textcircled{5}=\lfloor \frac{n}{c} \rfloor$，即能被 $c$ 整除的个数；$\textcircled{1}+\textcircled{2} = (\textcircled{1}+\textcircled{2}+\textcircled{3}+\textcircled{6})-(\textcircled{3}+\textcircled{6}) = \lfloor \frac{n}{a} \rfloor - (\lfloor \frac{n}{\operatorname{lcm}(a,b)} \rfloor)$；这两个式子相加，重叠部分 $\textcircled{2} = \lfloor \frac{n}{\operatorname{lcm}(a,c)} \rfloor-\lfloor \frac{n}{\operatorname{lcm}(a,b,c)} \rfloor$。

整理答案即 $\lfloor \frac{n}{c} \rfloor+\lfloor \frac{n}{a} \rfloor - (\lfloor \frac{n}{\operatorname{lcm}(a,b)} \rfloor)-(\lfloor \frac{n}{\operatorname{lcm}(a,c)} \rfloor-\lfloor \frac{n}{\operatorname{lcm}(a,b,c)} \rfloor)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int __int128
int in(){
	int res = 0;
	char a = getchar();
	while(!isdigit(a)){
		a = getchar();
	}
	while(isdigit(a)){
		res = res * 10 + a - '0', a = getchar();
	}
	return res;
}
void out(int a){
	if(a > 9) out(a / 10);
	putchar(a % 10 + '0');
}
int lcm(int a,int b){
	return a * b / __gcd(a,b);
}
signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0), cout.tie(0);
	int T;
	T = in();
	while(T--){
		int n,a,b,c;
		n = in(), a = in(), b = in(), c = in(); 
		int ans = 0;
		ans = n / c;
		ans += n / a - n / lcm(a,b);
		ans -= n / lcm(a,c) - n / lcm(lcm(a,b),c);
		out(ans), putchar('\n');
	}
	return 0;
} 
```

---

## 作者：_luogu_huowenshuo_ (赞：0)

## 思路
### 公式
使用容斥原理计算并集的大小：总数 $=$ （能被 $a$ 整除但不能被 $b$ 整除的年份数）$+$（能被 $c$ 整除的年份数）$-$（同时满足这两种情况的年份数）。
## 代码
```py
import sys
import math
def main():
    input = sys.stdin.read().split()
    idx = 0
    T = int(input[idx])
    idx += 1
    r = []
    for _ in range(T):
        n = int(input[idx])
        a = int(input[idx + 1])
        b = int(input[idx + 2])
        c = int(input[idx + 3])
        idx += 4
        g_ab = math.gcd(a, b)
        lcm_ab = a * b // g_ab
        
        g_ac = math.gcd(a, c)
        lcm_ac = a * c // g_ac
        
        g_ab_c = math.gcd(lcm_ab, c)
        lcm_abc = lcm_ab * c // g_ab_c
        t1 = n // a
        t2 = n // lcm_ab
        t3 = n // c
        t4 = n // lcm_ac
        t5 = n // lcm_abc
        
        t = (t1 - t2) + t3 - (t4 - t5)
        r.append(t)
    sys.stdout.write('\n'.join(map(str, r)) + '\n')

if __name__ == '__main__':
    main()
```

---

## 作者：huanglihuan (赞：0)

### Solution
本来 $\lfloor \frac na\rfloor$ 是一定的，但是是 $b$ 的倍数的话，那么同时是 $a$ 和 $b$ 的倍数的就需要减去。

然后所有 $\lfloor \frac nc\rfloor$ 个是一定的，因为是 $c$ 的倍数一定可以，但是会和上面有重复，同时是 $a$ 和 $c$ 的倍数会算两次。

但是 $a$ 和 $c$ 的倍数中，也有已经被淘汰的同时是 $a$ 和 $b$ 的倍数的数，因此要加上同时是 $a,b,c$ 的倍数的数，因为这些数会被多减。

注意开 `__int128`。
### Code

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5,maxn = 5e3 + 5,INF = 2e9;
int a [N];
inline __int128 read ()
{
	__int128 x = 0;
	char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return x;
}
inline void write (__int128 x)
{
	if (x < 0) putchar ('-'),x = -x;
	if (x > 9) write (x / 10);
	putchar ((int) (x % 10) + '0');
	return ;
}
__int128 gcd (__int128 x,__int128 y)
{
	while (y != 0)
	{
		__int128 temp = y;
		y = x % y;
		x = temp;
	}
	return x;
}
__int128 lcm (__int128 x,__int128 y) {return x / gcd (x,y) * y;}
signed main ()
{
	int T;
	cin >> T;
	while (T --)
	{
		__int128 n,a,b,c;
		n = read (),a = read (),b = read (),c = read ();
		write (n / a - n / lcm (a,b) + n / c - n / lcm (a,c) + n / lcm (lcm (a,b),c));
		cout << endl;
	}
	return 0;
}
```

---

## 作者：l15130880055 (赞：0)

## P12226 「WyOJ Round 1」启 · 破茧初阳

### Problem
给定 $n$，求出 $1 \leq i \leq n$ 中的满足能被 $A$ 整除且不被 $B$ 整除，或能被 $C$ 整除的数的个数。

### Solution

显然是容斥裸题，放张图先。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ujytw63.png)

答案就是这两个圆的总和，也就是两部分相加减去中间重叠的部分。

$1 \leq i \leq n$ 中的能被 $A$ 整除的数显然是 $\lfloor \frac{n}{A} \rfloor$，能被 $A$ 和 $B$ 同时整除的显然是 $\lfloor \frac{n}{\operatorname{lcm}(A,B)} \rfloor$，这两者相减就是左边部分的答案，右边部分能被 $C$ 整除的显然是 $\lfloor \frac{n}{C} \rfloor$，重叠的部分就是能被 $A$ 和 $C$ 整除但是不能被 $B$ 整除的数，所以中间重叠的部分答案就是 $\lfloor \frac{n}{\operatorname{lcm}(A,C)} \rfloor - \lfloor \frac{n}{\operatorname{lcm}(A,B,C)} \rfloor$。

所以最后的答案就是 $\lfloor \frac{n}{A} \rfloor - \lfloor \frac{n}{\operatorname{lcm}(A,B)} \rfloor + \lfloor \frac{n}{C} \rfloor - (\lfloor \frac{n}{\operatorname{lcm}(A,C)} \rfloor - \lfloor \frac{n}{\operatorname{lcm}(A,B,C)} \rfloor)$。

### Caution

因为 $1 \leq A,B,C \leq 10^9$，当这三个数都达到极限并且互质时，$\operatorname{lcm}(A,B,C)$ 的值会达到 $10^{27}$，这时就需要使用科技 `__int128` 了。

### Code

```cpp
int a, b, c;
inline int lcm(int a, int b){
	return a / __gcd(a, b) * b;
} 
inline void solve(){
	Fastio::cin >> n >> a >> b >> c;
	Fastio::cout << n / a - n / lcm(a, b) + n / c - (n / lcm(a, c) - n / lcm(lcm(a, b), c)) << '\n';
}
```

---

## 作者：Misserina (赞：0)

形式化题意：给出三个整数 $a,b,c$，找出 $1$ 至 $n$ 间能被 $a$ 整除且不能被 $b$ 整除的数或能被 $c$ 整除的数字的个数。

由数学知识，不难得到：

> $1$ 至 $n$ 中能被 $a$ 整除的数字个数为 $\lfloor \frac{n}{a} \rfloor$。

> 全部既能被 $a$ 整除又能被 $b$ 整除的数字等效于全部能被 $\operatorname{lcm} (a,b)$ 整除的数字，其中 $\operatorname{lcm}$ 指最小公倍数。

因此，我们可以把数字分为 $8$ 类：

1. 不是 $a,b,c$ 中任意一个数的倍数的数。
2. 仅为 $a$ 的倍数。
3. 仅为 $b$ 的倍数。
4. 仅为 $c$ 的倍数。
5. 仅为 $a,b$ 的倍数。
6. 仅为 $a,c$ 的倍数。
7. 仅为 $b,c$ 的倍数。
8. 为 $a,b,c$ 的倍数。

满足要求的数包括第 $2,4,6,7,8$ 类。

现在分类讨论各类数字的个数：

- 能被 $a$ 整除的数，包括第 $2,5,6,8$ 类，个数为 $\lfloor \frac{n}{a} \rfloor$，记为 $x_1$。
- 能被 $c$ 整除的数，包括第 $4,6,7,8$ 类，个数为 $\lfloor \frac{n}{c} \rfloor$，记为 $x_2$。
- 能被 $a,b$ 整除的数，包括第 $5,8$ 类，个数为 $\lfloor \frac{n}{\operatorname{lcm}(a,b)} \rfloor$，记为 $x_3$。
- 能被 $a,c$ 整除的数，包括第 $6,8$ 类，个数为 $\lfloor \frac{n}{\operatorname{lcm}(a,c)} \rfloor$，记为 $x_4$。
- 能被 $a,b,c$ 整除的数，包括第 $8$ 类，个数为 $\lfloor \frac{n}{\operatorname{lcm}(a,b,c)} \rfloor$，记为 $x_5$。

由容斥思想，最终结果就是 $x_1+x_2-x_3-x_4+x_5$。

由于 $a,b,c \le 10^9$，因此在求 $a,b,c$ 三数的最小公倍数时需要开 `__int128`。

赛时代码如下（注释是后加的）：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define i128 __int128
int t;
ll n,a,b,c;
const ll inf=3e18;
ll gcd(ll a,ll b) {
	if (b==0) return a;
	return gcd(b,a%b);
}
ll lcm(ll a,ll b) {
	return (ll) ((i128)a*(i128)b/(i128)gcd(a,b));
}
int main() {
	scanf("%d",&t);
	while (t--) {
		scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
		ll n1=lcm(a,b),n2=lcm(a,c),n3=gcd(n1,c),n4=0;
		if (n1/n3>inf/c) n4=inf; //防止 n4 爆 long long
		else n4=lcm(n1,c);
		printf("%lld\n",n/a+n/c-n/n1-n/n2+n/n4); //分别对应题解中的 x1，x2，x3，x4，x5。
	}
}
```

---

## 作者：Billhqh9 (赞：0)

## 审题
大致意思是找出 $1$ 到 $n$ 的整数中符合以下两种情况中任意一种的数的个数。
- 情况一：能被 $a$ 整除且不能被 $b$ 整除；
- 情况二：能被 $c$ 整除。

明显的，暴力是一种码量较小的做法。但是，暴力是会 TLE 的。看看 $n$ 的范围，非常大，大到离谱：$n\le10^{18}$，而且还有多组测试数据：$T\le10^5$。这其实就是在说明：对每一组数据，时间复杂度必须达到常数，或者接近常数，比如带 $\log$ 的那种。

## 正解思路
对于符合第一种情况的数，其实可以从能被 $a$ 整除的数里剔除能被 $b$ 整除的数。也就是符合条件的数的个数等于能被 $a$ 整除的数的个数减能同时被 $a$ 和 $b$ 整除的数（即能被 $a$ 和 $b$ 的最小公倍数整除的数）的个数。

对于第二种情况，直接计算能被 $c$ 整除的数的个数即可。

另外，把两种情况的答案相加后，还要再减掉两种情况重复的数的数量，也就是同时满足情况一和情况二的数，即能被 $a$ 和 $c$ 的最小公倍数整除，但不能被 $b$ 整除的数。同样，先计算能被 $a$ 和 $c$ 的最小公倍数整除的数，然后减去同时能被 $a$ 和 $c$ 的最小公倍数和 $b$ 整除的数（即能被 $a$，$b$ 和 $c$ 的最小公倍数整除的数）的个数。

至于怎么算 $1$ 到 $n$ 的整数中能被 $k$ 整除的数有几个嘛，其实很简单，就是 $\lfloor \frac{n}{k} \rfloor$。

最后看看时间复杂度。我们使用欧几里得算法求最小公倍数和最大公约数的话，那么时间复杂度是 $O(T \times \log \max\{a, b, c\})$，是可以通过的。

~~其实最后码量也很小的，只比暴力多一点。~~

## 注意
- 此题开 `long long` 不够，要开 `__int128`。~~这个错我调了好久。~~
- `__int128` 类型的输入输出要用快读快写。

---

