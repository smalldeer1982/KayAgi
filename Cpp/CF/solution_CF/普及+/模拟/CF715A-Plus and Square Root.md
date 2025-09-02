# Plus and Square Root

## 题目描述

ZS the Coder is playing a game. There is a number displayed on the screen and there are two buttons, ' $ + $ ' (plus) and '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' (square root). Initially, the number $ 2 $ is displayed on the screen. There are $ n+1 $ levels in the game and ZS the Coder start at the level $ 1 $ .

When ZS the Coder is at level $ k $ , he can :

1. Press the ' $ + $ ' button. This increases the number on the screen by exactly $ k $ . So, if the number on the screen was $ x $ , it becomes $ x+k $ .
2. Press the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button. Let the number on the screen be $ x $ . After pressing this button, the number becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/e2db36dd56c863e7b06dd83afaf9d635a860d586.png). After that, ZS the Coder levels up, so his current level becomes $ k+1 $ . This button can only be pressed when $ x $ is a perfect square, i.e. $ x=m^{2} $ for some positive integer $ m $ .

Additionally, after each move, if ZS the Coder is at level $ k $ , and the number on the screen is $ m $ , then  $ m $ must be a multiple of $ k $ . Note that this condition is only checked after performing the press. For example, if ZS the Coder is at level $ 4 $ and current number is $ 100 $ , he presses the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button and the number turns into $ 10 $ . Note that at this moment, $ 10 $ is not divisible by $ 4 $ , but this press is still valid, because after it, ZS the Coder is at level $ 5 $ , and $ 10 $ is divisible by $ 5 $ .

ZS the Coder needs your help in beating the game — he wants to reach level $ n+1 $ . In other words, he needs to press the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button $ n $ times. Help him determine the number of times he should press the ' $ + $ ' button before pressing the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button at each level.

Please note that ZS the Coder wants to find just any sequence of presses allowing him to reach level $ n+1 $ , but not necessarily a sequence minimizing the number of presses.

## 说明/提示

In the first sample case:

On the first level, ZS the Coder pressed the ' $ + $ ' button $ 14 $ times (and the number on screen is initially $ 2 $ ), so the number became $ 2+14·1=16 $ . Then, ZS the Coder pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, and the number became ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/9308f88c365c030e2395e6c4e7fb256c45e3ee80.png).

After that, on the second level, ZS pressed the ' $ + $ ' button $ 16 $ times, so the number becomes $ 4+16·2=36 $ . Then, ZS pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, levelling up and changing the number into ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/7b6a09b10477bfd8c4130abca871a5a72fd33934.png).

After that, on the third level, ZS pressed the ' $ + $ ' button $ 46 $ times, so the number becomes $ 6+46·3=144 $ . Then, ZS pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, levelling up and changing the number into ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/1ca1ffe171430a4d7ba5708c52a6d2103e02de0f.png).

Note that $ 12 $ is indeed divisible by $ 4 $ , so ZS the Coder can reach level $ 4 $ .

Also, note that pressing the ' $ + $ ' button $ 10 $ times on the third level before levelling up does not work, because the number becomes $ 6+10·3=36 $ , and when the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button is pressed, the number becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/7b6a09b10477bfd8c4130abca871a5a72fd33934.png) and ZS the Coder is at Level $ 4 $ . However, $ 6 $ is not divisible by $ 4 $ now, so this is not a valid solution.

In the second sample case:

On the first level, ZS the Coder pressed the ' $ + $ ' button $ 999999999999999998 $ times (and the number on screen is initially $ 2 $ ), so the number became $ 2+999999999999999998·1=10^{18} $ . Then, ZS the Coder pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, and the number became ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/ea4aa948ec20d05a136bf9d7be9348e6b59c2a62.png).

After that, on the second level, ZS pressed the ' $ + $ ' button $ 44500000000 $ times, so the number becomes $ 10^{9}+44500000000·2=9·10^{10} $ . Then, ZS pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, levelling up and changing the number into ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/9d032592276d09e8199b07c1b9d030f7638a4d76.png).

Note that $ 300000 $ is a multiple of $ 3 $ , so ZS the Coder can reach level $ 3 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
14
16
46
```

## 样例 #2

### 输入

```
2
```

### 输出

```
999999999999999998
44500000000
```

## 样例 #3

### 输入

```
4
```

### 输出

```
2
17
46
97
```

# 题解

## 作者：4526_ (赞：6)

[题目链接](https://www.luogu.org/problemnew/show/CF715A)

纯数学题，关键在于推导公式

**主要思想：数学归纳法**

大致思路：

1、设进入第k关时数字为x(k)，过第k关关时数字为x(k+1)

2、“开完平方后的数字是k+1的倍数” -> **（k+1）² | x(k+1)**

3、同理 **k | x(k)**

4、“加号：若屏幕上的数字为x，你在第k关，则变成x+k” -> **k | x(k+1)-x(k)**

5、由3、4可知 k | x(k+1)，那么 **k² | x(k+1)**

6、由上得 **x(k+1)min=k² * (k+1)²**

7、开根号后数字为 **k * (k+1)**

8、由此推知 **x(k)=(k-1) * k**

9、答案即为 **（k² * (k+1)² - (k-1) * k）/k**

10、化简得 **k³+2k²+1**

11、**注意第一关时特殊处理**

AC代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

int n;
long long ans;

int main(){
    scanf("%d",&n);
    printf("2\n");
    for(long long i=2;i<=n;++i){
        ans=(i+2)*i*i+1;
        printf("%lld\n",ans);
    }
    return 0;
}
```

欢迎来[我的blog](https://www.luogu.org/blog/4526-Au/#)看看

---

## 作者：wmrqwq (赞：4)

# 原题链接

[CF715A Plus and Square Root](https://www.luogu.com.cn/problem/CF715A)

# 解题思路

首先，这道题是一个结论题，推论如下：

因为开完平方后数字是 $k+1$ 的倍数时才可以按下根号按钮，所以我们可以得出，按下根号按钮后，那么这个数字一定是 $k \times (k+1)$ 的倍数，这是我们大胆猜想一下，下一关的数字就为 $k \times (k+1)$，这时我们便可以推出式子，随后再化简一下：
![](https://cdn.luogu.com.cn/upload/image_hosting/jh6waby2.png)

即可得出结果。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0;
long long n;
int main()
{
    cin>>n;
    cout<<2<<endl;//注意，这里1要特判
    for(long long i=2;i<=n;i++)
        cout<<i*i*i+i*i*2+1<<endl;//结论式子
    QwQ;//华丽的结束
}
```


---

## 作者：LJ07 (赞：2)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/CF715A)

## 思路简述
+ 容易发现：在通过第 $k$ 关之后，当前数字是 $k\times (k+1)$ 的倍数。
+ 我们不妨猜想：若当通过第 $k$ 关后，数字都可以变为 $k\times (k+1)$。
+ 对于第 $1$ 关，按 $2$ 次按钮即可达成目的。
+ 若第 $k$ 关成立，则按 $\frac{k^2\times(k+1)^2-k\times(k-1)}{k}=k^3+2k^2+1$ 次按钮后也可使得第 $k+1$ 关成立。
+ 综上，对于第一关直接输出 $2$，对于第 $k$ 关 输出 $k^3+2k^2+1$ 即可。$(k\ge 2)$

## 丑陋の代码
[click here](https://www.luogu.com.cn/paste/jlyh8b2x)

---

## 作者：WNico (赞：1)

###### ~~既然没人交Python，我来水一发~~


------------


# 原题：[CF715A 【Plus and Square Root】](https://www.luogu.org/problemnew/show/CF715A)

[my blog](https://a-wnico-blog.blog.luogu.org/)

题目就是输出小于等于输入数的所有平方数，至于为什么前面有人回答了

直接上代码：2行**python2**

```python
for i in range(1,input()+1)： 			//range左闭右开，需要+1
    print 2 if(i==1) else i*(i+1)**2-i+1;	//三目运算符
```

这个代码加了~~许多~~
****点****
问题，各位注意一下


---

## 作者：d909RCA (赞：0)

### 0x00 前言

在同学[CP duel](https://ealex.top/duel/home/)的时候，别人的一道题，同学挂了，我过了。

### 0x01 前置芝士

- 数学
- **将数据范围看对**

### 0x02 思路

考虑你在第 $k$ 关按加号的**最小**次数，显然开平方是最小的数为 $(k^{2}+k)^{2}$ 所以设 $now$ 是上一关的数。答案就是 $\frac{(k^{2}+k)^{2}-now}{k}$。然后挂了。

> Wrong Answer on test 5.

注意到数据范围 $n \le 10^{6}$，所以最大 $k^{4}$ 直接爆了，推答案式子。

$$
\begin{align*}
&=\frac{(k^{2}+k) \times (k^{2}+k)}{k}\\
&=\frac{k^{2}+k}{k} \times (k^{2}+k)\\
&=(k+1) \times (k^{2}+k)\\
&=k^{3}+2k^{2}+k
\end{align*}
$$

最后再减去 $\frac{now}{k}$，最终的答案为 $k^{3}+2k^{2}+k-\frac{now}{k}$。

### 0x03 Code

```cpp
// Problem: A. Plus and Square Root
// Contest: Codeforces - Codeforces Round 372 (Div. 1)
// URL: https://codeforces.com/problemset/problem/715/A
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define pb push_back
#define pii pair<int,int>
#define pq priority_queue
#define il inline
#define rg register
namespace d909RCA_math
{
	int fac[200009];
	void Cinit(int p) 
	{
	    fac[0] = 1;
	    for(int i=1;i<200000;i++)
	    {
	        fac[i]=fac[i-1]*i%p;
	    }
	}
	int qpow(int a,int b,int p) 
	{
	    int ans=1;
	    while(b) 
	    {
	        if(b&1) ans=ans*a%p;
	        a=a*a%p;
	        b>>=1;
	    }
	    return ans;
	}
	int C(int n,int m,int p) 
	{
	    if(m>n||m<0) return 0;
	    return fac[n]*qpow(fac[m],p-2,p)%p*qpow(fac[n-m],p-2,p)%p;
	}
	int Lucas(int n,int m,int p) 
	{
	    if(!m) return 1;
	    return (C(n%p,m%p,p)*Lucas(n/p,m/p,p))%p;
	}
	int GCD(int n,int m,int p) 
	{
	    return __gcd(n,m)%p;
	}
	int LCM(int n,int m,int p) 
	{
	    return n*m%p*qpow(GCD(n,m,p),p-2,p)%p;
	}
}
using namespace d909RCA_math;
namespace d909RCA
{
	int n;
	void inp()
	{
		cin>>n;
	}
	void solve()
	{
		
	}
	void print()
	{
		int now=2;
		for(int i=1;i<=n;i++)
		{
			cout<<(i*i*i+2*i*i+i)-now/i<<'\n';
			now=(i*i+i);
		}
	}
}
using namespace d909RCA;
// #define file 1
// #define multi_test 1
signed main()
{
	int t=1;
	#ifdef file
		freopen(".in","r",stdin);
		freopen(".out","w",stdout);
	#endif
	#ifdef multi_test
		cin>>t;
	#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(t--)
	{
		d909RCA::inp();
		d909RCA::solve();
		d909RCA::print();
	}
	return 0;
}
```

### 0x04 后记

缺省源找回来了，决斗的同学没有过。

---

## 作者：qwq___qaq (赞：0)

注意到第 $k$ 关中的数一定是 $k$ 的倍数。

不妨令进入关卡时的数为 $\Delta\times k$，那么如果 $\Delta<k$，显然一种策略是变成 $k^2(k+1)^2$。

发现这个时候开根满足 $\sqrt{k^2(k+1)^2}=k(k+1)$，其中 $\Delta=k<k+1$，那么显然可以用类似的方法构造。

操作次数？算出增量，每次多 $k$，就是 $(k+1)^2k-(k-1)$。

Tip：$k=1$ 的时候不满足这个形式，需要单独特判。

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF715A)
# 推导
1. 第一关按两下按钮即可，输出 $2$。
2. 接下来 $n-1$ 关 $\left ( n \le 2 \right ) $，容易发现按按钮的次数为 $k \times \left ( k+1 \right )$ 的倍数。
3. 我们可以将结论弱化，假设次数就是等于 $k \times \left ( k+1 \right )$，这样就可以推出式子：若第 $k$ 关成立，则按按钮的次数为 $\frac{k^{2} \times \left ( k+1 \right )^{2}-k \times \left ( k+1 \right )  }{k} $，化简得 $k^{3}+2k^{2}+1$，即按 $k^{3}+2k^{2}+1$ 次按钮后能使 $k+1$ 关成立。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ans;
signed main(){
	cin>>n;
	cout<<2<<endl;
    for(int i=2;i<=n;i++){
        ans=(i+2)*i*i+1;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：正负君 (赞：0)


## CF715A Plus and Square Root 题解

## 思路

假设第 $k$ 关的数字是 $x_k$。

- “加号：若屏幕上的数字为 $x$，你在第 $k$ 关，则变成 $x+k$”，即为 $k | x_{k+1}-x_k$。  

- “开完平方后的数字是 $k+1$ 的倍数”就是 $k+1 | \sqrt{x_{k+1}}$，我们又得知 $(k+1)^2 | x_{k+1}$，经过化简可得 $k | x_k$。  

- 已知 $k | x_k$，我们也可得 $k | x_{k+1}$，也就是 $k^2 | x_{k+1}$。  

- 第 $k$ 关的答案即为： 

$$
\begin{aligned}
& [(x_{k+1})_{\min}-x_k]\div k\qquad(k\ge 2)\\
=& [k^2\times(k+1)^2-(k-1)\times k]\div k \\
=& k\times(k+1)^2-k+1 \\
=& k^3+2k^2+1\\
\end{aligned}
$$

注：第一关特殊处理，按两次按钮即可，应输出 `2`。

## 代码

接下来放出~~你们最爱的完整~~代码：  

```cpp
#include<iostream>
using namespace std;
long long int n,ans=2;//坑点，要用 long long int。答案可能会超 int 存储范围。
int main()
{
  cin>>n;
  cout<<ans<<endl;    //第 1 关的答案是 2，要特殊处理。
  for(long long int k=2; k<=n; k++)
  {
    ans=k*k*k+2*k*k+1;//公式
    cout<<ans<<endl;
  }
  return 0;           //完美结束啦！
}
```

这道题偏思维，需多练数学题。

---

## 作者：liuyifan (赞：0)

## 本题类似于[NOIP2017TGD1T1](https://www.luogu.org/problemnew/show/P3951),公式题

### 公式:A1=2,An=n*(n+1)^2-n+1;
### 然后按照题意输出每个值即可
代码实现:
```
#include<bits/stdc++.h>
#define reg register
#define ll long long
using namespace std;
ll n,a; 
int main()
{
	scanf("%lld",&n);//注意lld 
	for(reg ll i=1;i<=n;i++)a=i==1?2:i*(i+1)*(i+1)-i+1,printf("%lld\n",a);
	//以上等价于if(i==1)a=2;else a=i*(i+1)*(i+1)-i+1;
	//三目运算符压行大法 
	return 0;
} 
```
### Ps:本题评测时带SPJ，答案可能不止一种,但这是最好推的

---

