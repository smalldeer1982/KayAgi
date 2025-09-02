# [ABC166D] I hate Factorization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc166/tasks/abc166_d

$ A^5-B^5\ =\ X $ を満たす整数の組 $ (A,B) $ をひとつ示してください。 ただし、与えられる $ X $ に対して、条件を満たす整数の組 $ (A,B) $ が存在することが保証されています。

## 说明/提示

### 制約

- $ 1\ \leq\ X\ \leq\ 10^9 $
- $ X $ は整数である。
- 条件を満たす整数の組 $ (A,B) $ が存在する。

### Sample Explanation 1

$ A=2,B=-1 $ のとき、$ A^5-B^5 $ の値は $ 33 $ になります。

## 样例 #1

### 输入

```
33```

### 输出

```
2 -1```

## 样例 #2

### 输入

```
1```

### 输出

```
0 -1```

# 题解

## 作者：冷却心 (赞：5)

## 题意如下

找一组 $A,B$ ,满足 ${A^5}-{B^5}= X$ , $X≤{10^9}$ 

## 思路

如果直接暴力枚举，相信我一定会超时（不信自己试，~~试试就逝世~~）

通过复杂的手算，我们可以发现：

1.  $A$ 与 $B$ 的差越小， ${A^5}-{B^5}$ 也越小

2. 由于  ${150^5}-{149^5}$  就已经大于  $10^9$ （运用第1条）,所以 $A$ 与 $B$ 的范围就是 $[-150,150]$ 

## 献上代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll y;
ll f(ll x){return x*x*x*x*x;};//5次方函数
int main(){
	cin>>y;
  	//枚举
	for(int i=-150;i<=150;i++){
		for(int j=-150;j<=150;j++){
			if(f(i)-f(j)==y){//如果i^5-j^5==Y
				printf("%d %d",i,j);
				return 0;
			}
		}
	}
	return 0;
} 
```

## Tips

long long别忘记

## 最后

**管理员大大给个过吧！**

---

## 作者：wangkangyou (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT5404)

简述一下题意：~~(其实也没什么好简述的了)~~
给你一个数 $x$ , 试求方程 $a^{5} - b^{5}=x$ 的一组解 $a,b$。
## 讲一下我的思路：
暴力枚举即可。此题难在判断枚举范围上。其实我们可以从 $x$ 下手。由于 $x$ 为两个数相减的差，我们可以极端一点，假设两项的底数一定是相邻的，那么我们可以一个个枚举一组组相邻底数的 $5$ 次方的差:

$\{1,2\} = 1^{5} - 2^{5} = - 31,
\{2,3\} = 2^{5} - 3^{5} = - 211,
\{3,4\} = 3^{5} - 4^{5} = - 781,\{4,5\} = 4^{5} - 5^{5} = - 2,101……$

其实我们从以上过程中可以发现，差的绝对值在几乎是在直线增长。终于到了第 $119$ 组的时候我们发现：

$\{119,120\} = 119^{5} -120^{5} = - 1,019,663,401$

差已经大于了$10^{9}$了。但是还没完，我们统计的是 $a,b$ 为正数且递增的情况，正数的答案虽然有可能是 $a,b$ 为正数且递减的情况下，然而更多可能是存在于 $-120$ 至 $0$ 的范围中。于是我们的枚举范围就变成了从 $-120$ 到 $120$ 这一个区间内。

参考代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int sum=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) sum=(sum<<3)+(sum<<1)+(ch^48);
	return sum*f;
}
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar('0'+x%10);
	return;
}
const int inf=1e10;
const int N=1e6+10;
int qpow (int a, int b){//快速幂，相当于a^b,理解即可
	if (b == 0) return 1;
	if (b == 1) return a;
	int t = qpow (a, b / 2);
	if (b % 2 == 1) return t * t * a;
	return t * t;
}
signed main(){
	int x = read ();
	for (int i = -150; i <= 150; ++ i){
		for (int j = -150; j <= 150; ++ j){
			int a = qpow (i, 5);
			int b = qpow (j, 5);
			if (a - b == x){
				write (i);
				putchar (' ');
				write (j);
				return 0;
			}
		}
	}
	return 0;
}

```

---

## 作者：wangyi_c (赞：2)

[你谷题目传送门](https://www.luogu.com.cn/problem/AT5404)

[AT 题目传送门](https://atcoder.jp/contests/abc166/tasks/abc166_d)

## 1.题目大意

给出一个 $x$，求出不定方程 $a^5-b^5=x$ 的一组 $a,b$ 值。

## 2.思路讲解

这道题只能暴力枚举来解决，但是到了枚举就肯定要找一个枚举范围。不难算出 $120^5-119^5>10^9$，所以范围就是 $-120$ 到 $120$，肯定不会超时。

## 3.AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x;
int k(int a,int b){//计算方程函数
	return a*a*a*a*a-b*b*b*b*b;
}
signed main(){
	cin>>x;
	for(int i=-120;i<=120;i++){
		for(int j=-120;j<=120;j++){
			if(k(i,j)==x){//发现了解
				cout<<i<<" "<<j;//输出
				return 0;//结束程序
			}
		}
	}
	return 0;
}
```
_THE END_

谢谢观看

By wangyi

---

## 作者：Fr0sTy (赞：2)

### 题意简述
------------

题目给定一个整数 $X$，让你求出两个整数 $A$，$B$，使 $A$ 和 $B$ 满足 $A^5 - B^5 = X$。

### 解题思路
------------

**枚举**可以解决这道题。

题目要求 $A^2 - B^2 = X$，数据范围有这样写：$1 \leqslant X \leqslant 10^9$。

通过计算可得，因为 $120^5-119^5>10^9$，所以$A$ 的取值范围是 $-120 \leqslant A \leqslant 120$，$B$ 的取值范围为 $-120 < B < 120$。

两重循环枚举 $A$，$B$ 的值即可。

注意：**一定要开** `long long`！

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
long long x;
long long doit(long long n) { return n*n*n*n*n;}
int main() {
	scanf("%lld",&x);
	for(int i=-120;i<=120;i++) {
		for(int j=-120;j<=120;j++) {
			if(doit(i)-doit(j)==x) {
				printf("%d %d\n",i,j);
				return 0;
			}
		}
	}
	return 0;
}
//code by TheCedar
```

---

## 作者：_byta (赞：2)

可以发现 500 的 5 次方已经大于了 10 的 9 次，所以我们可以枚举 A 和 B，为了使解的范围更大，我们在枚举 B 时可以从负数开始枚举，至于从哪个负数，可以自己定，只要小于负 100 即可。我们找到答案就可以退出了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100002;
int n,m,k,p,q,ans,sum,tot,cnt,a[N],b[N],c[N],d[N];
signed main()
{
	cin>>n;
    for(int i=1;i<=700;i++)
    {
    	for(int j=-600;j<=600;j++)
    	{
    		p=i*i;
    		p=p*i;
    		p=p*i;
    		p=p*i;
    	    q=j*j;
    		q=q*j;
    		q=q*j;
    		q=q*j;
    		if(p-q==n)
    		{
    			cout<<i<<" "<<j;
    			return 0;
			}
		}
	}
	return 0;
}

```





---

## 作者：RBI_GL (赞：1)

## 题意

已知 $a^5-b^5=x$，$a,b∈Z$，$x∈Z^+$
，$x≤10^9$。

给定 $x$，求出一组 $a,b$ 的值。

## 思路

直接枚举肯定超时，所以可以考虑缩小枚举范围。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int a = 1;
    while(1) {
    	a++;
    	if (a * a * a * a * a - (a - 1) * (a - 1) * (a - 1) * (a - 1) * (a - 1) > 1e9) {
    		cout << a << endl;
    		return 0;
		}
	}
	return 0;
}
```
通过以上程序可以得出 $a,b$ 的枚举上下界为 $±120$。

然后枚举即可。得到一组解就结束。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long //注意五次方有可能超过 int
int x;
int qp(int b, int p) { //快速幂
    int ans = 1, base = b;
    while(p > 0) {
        if (p % 2 == 1) ans *= base;
        base *= base;
        p >>= 1;
    }
    return ans;
}
signed main() {
	cin >> x;
	for(int i = -120; i <= 120; ++i) {
		for(int j = -120; j <= 120; ++j) {
			if (qp(i, 5) - qp(j, 5) == x) {
				cout << i << " " << j << endl;
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：_Kagamine_Rin_ (赞：0)

### 题意
给定一个数 $x$，找出满足 $a^5-b^5=x$ 的一组 $a,b$ 的值。

### 思路
如果直接暴力枚举，一定会超时，所以我们要缩小枚举范围。按一下计算器，可以得到 $150^5+149^5\gt 10^9$ ，所以我们只要把 $a,b$ 从 $-150$ 枚举到 $150$ 就可以了。
### 代码实现
```cpp
#include<stdio.h>
long long x;
int main(){
	scanf("%lld",&x);
	for(long long a=-150;a<=150;a++)
		for(long long b=-150;b<=150;b++)
			if(a*a*a*a*a-b*b*b*b*b==x)
				return 0&printf("%lld %lld",a,b);
}
```

---

## 作者：Otue (赞：0)

非常的疑惑，为什么远古时代 ABC 难度只有这么点啊？深感时代变了...

## 思路
我们可以发现 $X\leq10^9$，然而 $200^5-199^5>10^9$。

可以知道，$x^5-(x-1)^5< x^5-(x-k)^5$ （$k>1$），故其他的数字更不可能达成条件了。

即满足条件的 $X,Y$ 最大为 $200$，枚举即可！

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
int x;

signed main() {
	cin >> x;
	for (int i = -200; i <= 200; i++) {
		for (int j = -200; j <= 200; j++) {
			if (i * i * i * i * i - j * j * j * j * j == x) {
				cout << i << ' ' << j << endl;
				return 0;
			}
		}
	}
}
```

---

## 作者：achjuncool (赞：0)

[题目](https://www.luogu.com.cn/problem/AT5404)

[博客](https://www.luogu.com.cn/blog/achjuncool/solution-at5404)

# 题目大意

给一个正整数 $X$，找出任意两个整数 $A,B$，满足 $A^5-B^5=X$。

# 解法

暴力枚举即可。

$1\le X\le10^9$。

如果 $A,B$ 都从 $-10^9$ 枚举到 $10^9$ 肯定会超时，那么我们需要缩小范围。

选一个较大的数，比如 $500$，通过计算~~器~~可得，$500^5-499^5=311252497501$，肯定大于 $10^9$，所以 $A,B$ 都从 $-500$ 枚举到 $500$ 即可。

最坏情况下一共枚举 $10^6$ 次，肯定不会超时。

最后，**要开 ```long long``` ！！！**

# Code

[AC](https://www.luogu.com.cn/record/80764440)

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll x;
int main(){
	cin >> x;
	for(ll a = -500; a <= 500; a++){
		for(ll b = -500; b <= 500; b++){
			if((a * a * a * a * a - b * b * b * b * b) == x){
				cout << a << " " << b << endl;
				return 0;
			}
		}
	}
    return 0;
}
```

---

## 作者：Chouquet (赞：0)

其实D题真的没有那么难，就是需要事先计算 $A,B$ 的范围。

首先计算 $1000^5-999^5=4,990,009,995,001>10^9$ ,然后不断试算下去……最后可以发现：

$\because 120^5-119^5>10^9$ 且 $119^5-118^5<10^9$

$\therefore -120 \le A,B \le 120$ （$A,B$ 可为负数）

**注：如果官方题解中 $-118 \le A \le 119,-119 \le B \le 118$ 这个范围不知道怎么得出的话，用上面 $A,B$ 的范围就可以了。**

然后注意要开long long就没了。

代码：

```cpp
#include <stdio.h>
long long x;//不用解释这个了吧
main(){
    scanf("%lld",&x);
    for(long long a=-120;a<=120;++a)
        for(long long b=-120;b<=120;++b)
        //枚举，一定要开long long
            if(a*a*a*a*a-b*b*b*b*b==x)//判断
                return printf("%lld %lld\n",a,b),0;
                //压行写法，好孩子请勿模仿
}
```


---

## 作者：fighter (赞：0)

题目名称又是来误导人的……

一看题目名称因式分解，但是初中那些恶心的因式分解题告诉我，分解后的柿子长成这个鬼样子：

$$
a^5-b^5=(a-b)(a^4+a^3b+a^2b^2+ab^3+b^4)
$$

后面这一串显然非常不可做。

然后看一眼数据范围，发现$0\leq x\leq 10^9$，于是心血来潮：

![YPqoef.jpg](https://s1.ax1x.com/2020/05/05/YPqoef.jpg)

这就意味着当a的绝对值比较大的时候，$a^5-(a-1)^5$就会远远超过$10^9$。

从图片可以看出，a,b的绝对值都在2000以内，所以我们只要暴力枚举两个数判断就好了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    ll X;
    cin >> X;
    for(int i = -2000; i <= 2000; i++){
        for(int j = -2000; j <= i; j++){
            ll x = (ll)i*i*i*i*i, y = (ll)j*j*j*j*j;
            if(x - y == X){
                cout << i << " " << j << endl;
                return 0;
            }
        }
    }

    return 0;
}
```

---

## 作者：钓鱼王子 (赞：0)

本题看起来很难，实际上就是枚举。

随便打个表，发现 $1000^5-999^5>10^9$，也就是说最后答案的绝对值不会大于 $1000$,直接枚举即可，记得要判负数。

同时还要开 long long。

```cpp
#include<bits/stdc++.h>
#define in inline
#define int long long
#define re register
using namespace std;
in int read() {
	re int t=0;
	re char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9') {
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t;
}
int n,m,ans;
signed main(){
	n=read();
	for(re int i=-1000;i<=1000;++i){
		for(re int j=-1000;j<=1000;++j){
			if(i*i*i*i*i-j*j*j*j*j==n){
				printf("%lld %lld\n",i,j);
				return 0;
			}
		}
	}
}

```


---

