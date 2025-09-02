# Trains

## 题目描述

程序员Vasya有两个女友，一个叫Dasha，另一个叫Masha。她们分别住在Vasya所在地铁线路的两个始发站。

当Vasya有空闲时间时，他会去找他的一个女友。他在某个时间下降到火车站，等待第一班火车到来（地铁去哪，他就去哪个女友那里）。但两个方向的火车发车时间不同，向Dasha方向的火车a分钟一班，向Masha方向的火车b分钟一班。如果两列火车同时到达，Vasya会朝着发车时间较长的方向前进。在第0分钟，两班火车同时从Vasya所在站的前一个站和后一个站开出。（chinaxjh这个蒟蒻无法翻译的更好一点了）

问Vasya去哪个女友那里的概率大。（输出英文名即可，如果一样输出“Equal”，引号不用输出）

## 样例 #1

### 输入

```
3 7
```

### 输出

```
Dasha
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
Masha
```

## 样例 #3

### 输入

```
2 3
```

### 输出

```
Equal
```

# 题解

## 作者：_Gabriel_ (赞：1)

### 思路&大意

给定两个数 $a,b$，求出 $\operatorname{lcm}(a,b)$ (要在这个时间内)，然后用 $\operatorname{lcm}(a,b)$ 除以这两个数。

也就是 $a=\operatorname{lcm}(a,b)/a$，$b=\operatorname{lcm}(a,b)/b$。

然后判断 $a$ 是否比 $b$ 大，如果是，$b$ 加 $1$，否则 $a$ 加 $1$。

最后判断如果 $a$ 大，输出 `Dasha`，如果 $b$ 大，输出 `Masha`，如果 $a,b$ 一样大，则输出 `Equal`。

我们知道任意两个正整数 $a,b$，$\operatorname{lcm}(a,b)=a$ $\times$ $b
/(\operatorname{gcd}(a,b))$ (其中 $\operatorname{gcd}(a,b)$ 指 $a,b$ 的最大公因数，$\operatorname{lcm}(a,b)$ 指 $a,b$ 的最小公倍数)。

c++自带 `__gcd(a,b)` 这个函数，当然也可以手写 $\operatorname{gcd}$ 函数。

#### 注意：$a,b$ 要开 long long!

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll lcm(ll x, ll y) {
	return x * y / __gcd(x, y);
}

ll a, b;

int main() {
	cin >> a >> b;
	ll ans = lcm(a, b);
	a = ans / a;
	b = ans / b;
	if (a > b) {
		b++; 
	} else {
		a++;
	}
	if (a > b) {
		cout << "Dasha" << "\n";
	} else if (a == b) {
		cout << "Equal" << "\n";
	} else {
		cout << "Masha" << "\n";
	}
	return 0;
}
```


---

## 作者：Arrtan_73 (赞：1)

# 题解 CF87A
## 题目思路&做法
首先我们可以知道列车到达是有一个周期性的，比如：列车甲两分钟一次，列车乙三分钟一次，那么每过六分钟就同时到达一次。这个周期其实就是他们的最小公倍数，我们又知道单位时间，也就是发车间隔，那么一个周期里两辆列车的停靠数也就知道了，不就求出来了吗？但这样还有问题，最后一次两辆列车是同时到达的，那么就多求了一次，就把间隔长的加上一次就可以了。当然，不想手写 $\text{lcm}$，可以这样求 $\dfrac{a \times b}{ \text{gcd(a,b)}}$，其中的 $\text{gcd}$ 函数是标准库自带的。

P.S.一定要开 long long！
```cpp
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::__gcd;
long long a, b;

int main() {
	cin >> a >> b;
	long long cnt = a * b / __gcd(a, b);//求最小公倍数
	a = cnt / a;
	b = cnt / b;
	if (a > b)//处理重复计算
		b++;
	else
		a++;
	if (a > b)//判断，输出
		cout << "Dasha";
	else if (a == b)
		cout << "Equal";
	else
		cout << "Masha";
}
```


---

## 作者：chinaxjh (赞：1)

作为第一个在luogu上AC此题的人，就留一篇题解吧

这道题非常简单，唯一麻烦的就是理解题意（我的翻译可能有一点不清楚），看完这片题解你应该就完全明白了。

这其实是一个判断余数的题目，大数的倍数（即大数 *1 *2 *3......） 除以小数的余数必然会循环，累加这个循环里的所有余数，就可以得出有多少时间他回去发车时间长的那个人。再和这两个数的最小公倍数和这个时间的差进行比较就可以得出答案。

画个图来模拟一下第一个样例：
![1](https://cdn.luogu.com.cn/upload/pic/57802.png)
这样子大家应该都懂了吧，但题目里还有一个注意点
> 如果两列火车同时到达，Vasya会朝着发车时间较长的方向前进

这个意思就是说如果前面余数为0的话，总时间应该加上小的那个发车时间（可以自己画图理解一下）

上个code辅助理解：
```
#include<bits/stdc++.h>
using namespace std;
long long k,ans,t,a,b,i;//开long long一定要开long long
bool x[5000000];//标记该余数有没有出现
int main()
{
   scanf("%d%d",&a,&b);
   k=a*b/__gcd(a,b);//最小公倍数
   if (a>b)//找大数
   {
   	for (i=1;i<=b+1;i++)
   	{
   		t=a*i%b;
   		if (x[t]==true) break;
   		ans+=t;
   		x[t]=true;
   	}//余数的累加和
   	if (a*(i-1)%b==0) ans+=b;//如果两列火车同时到达，Vasya会朝着发车时间较长的方向前进，所以为0就加较小数
   	if (ans>k-ans) puts("Dasha");
   	else if (ans<k-ans) puts("Masha");
   	else puts("Equal");//判断概率大小
   }//下面的和上面一部分差不多，只是a,b改了一下
   else {
   	for (i=1;i<=a+1;i++)
   	{
   		t=b*i%a;
   		if (x[t]==true) break;
   		ans+=t;
   		x[t]=true;
   	}
   	   	if (b*(i-1)%a==0) ans+=a;
   	if (ans<k-ans) puts("Dasha");
   	else if (ans>k-ans) puts("Masha");
   	else puts("Equal");//这里ans指的是较小数的，所以判断条件和上面反一下
   }
}

```
还有，一定要开long long，否则就会像我一样WA2次

注：在cf上还有一些跟简单的做法（吊打本蒟蒻，但蒟蒻看不懂），可以自行去理解查看。

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF87A)

## 题目大意

两个方向的发车时间不同，向女友一方向的火车 $a$ 分钟一班，向女友二方向的火车 $b$ 分钟一班。如果两列火车同时到达，```Vasya``` 会朝着发车时间较长的方向前进。在第 $0$ 分钟，两班火车同时从 ```Vasya``` 所在站的前一个站和后一个站开出。

问 ```Vasya``` 去哪个女友那里的概率大。（输出英文名即可，如果一样输出 ```Equal```，引号不用输出）。

## 分析

可以发现，列车到达是有周期性的。而这个周期，就是 $a$ 与 $b$ 的最小公倍数。我们也知道发车间隔，就可以求出每个周期两种火车的停靠数。最后一次两车同时到达，只要给发车间隔长的加一就可以了。

备注：一定要开 ```long long```！

## 下面是 AC 代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b;
	cin>>a>>b;
	long long lcm=(a*b)/__gcd(a,b);
	long long a1=lcm/a;
	long long b1=lcm/b;
	if(a1>b1)
	{
		b1++; 
	}
	else
	{
		a1++;
	}
	if(a1>b1)
	{
		cout<<"Dasha";
	}
	if(a1==b1)
	{
		cout<<"Equal"; 
	}
	if(a1<b1)
	{
		cout<<"Masha";
	}
 } 
```

---

## 作者：lizulong (赞：0)

## 思路
首先我们可以知道列车到达是有一个周期性的，题目又告诉你了单位时间，也就是发车间隔，那么一个周期里两辆列车的停靠数也就知道了，求最小公倍数就是 $\frac{a\times b}{\gcd(a,b)}$。

然后用最小公倍数除以这两个数：

$a=\operatorname{lcm(a,b)}\div a$

$b=\operatorname{lcm(a,b)}\div b$

判断 $a$ 和 $b$ 之间谁大谁小，$a$ 大输出 ```Dasha```，$b$ 大输出 ```Masha```，相等输出 ```Equal```。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
#define gcd __gcd
using namespace std;
int lcm(int a,int b){//最小公倍数函数 
  return a/gcd(a,b)*b;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加快cin,cout 
	int a,b;
	cin>>a>>b;
   	int t= lcm(a,b);
	a=t/a,b=t/b;
	if(a>b) b++;else a++;
	if(a>b) cout<<"Dasha\n";
	else if(a==b) cout<<"Equal\n";
	else cout<<"Masha\n";
}
```


---

## 作者：Play_with (赞：0)

[CF87A Trains](https://www.luogu.com.cn/problem/CF87A)
### [前置芝士](https://zhuanlan.zhihu.com/p/77669220)
### 题意
容我翻译一下本题的~~阴间~~翻译：给出两个周期不同的车次，按题目中的要求求出他搭上哪一趟的概率最大，概率相等也纳作考虑。

------------
### 思路
知晓周期分别为 $a$ 和 $b$，便可以求出 $\gcd(a,b)$，进而可以求出列车的周期为 $\operatorname{lcm}(a,b)=\dfrac{a \times b}{\gcd(a,b)}$。此时还有一个坑：在周期的最后，两趟车同时到达，需作特殊处理。最后，考虑到 $a$ 和 $b$ 的范围已经达到了十的六次方，注意要使用**长整型!**
```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,la,lb;
int main(){
	scanf("%lld%lld",&a,&b);
	c=__gcd(a,b);//稍稍化简可知  
	la=b/c,lb=a/c;
	if(la>lb) lb++;
	else la++;
	if(la==lb) printf("Equal");
	else printf("%s",la>lb?"Dasha":"Masha");
	return 0;
}
```

---

## 作者：Lemon_zqp (赞：0)

### 思路
首先我们可以知道列车到达是有一个周期性的，eg：列车 a 两分钟一次，列车 b 三分钟一次，那么每过六分钟就同时到达一次。这个周期其实就是他们的最小公倍数，题目又告诉你了单位时间，也就是发车间隔，那么一个周期里两辆列车的停靠数也就知道了，求最小公倍数就是 $\dfrac{a\times b}{\gcd \left( a,b\right) }$，那么怎么求最大公约数呢，这时候有种方法，辗转相除法，方法：用较小数除较大数，再用出现的余数去除除数，再用出现的余数去除第一个余数，如此反复，直到最后余数是 $0$ 为止。如果是求两个数的最大公约数，那么最后的除数就是这两个数的最大公约数。但这样还有问题，最后一次 a 和 b 列车是同时到达的，那么就多求了一次，就把间隔长的加上一次就可以了。

### 代码

```
#include<bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b)
{ 
    int t = a % b;
    while(t != 0)
    {
    	a = b;
    	b = t;
    	t = a % b;
    }
    return b; 
}

int main()
{
	long long a, b;//不开 long long见祖宗 
	cin >> a >> b;
	long long lcm = a * b / gcd(a, b);
	a = lcm / a;
	b = lcm / b;
	if (a > b)
	{
		b++;
	}
	else
	{
	    a++;
	}
	if (a > b)
	{
		cout << "Dasha" ;
	}
	else if (a == b)
	{
		cout << "Equal";
	}
	else
	{
		cout << "Masha";
	}
		
	return 0;
}

```


---

## 作者：hcl156 (赞：0)

题目大意是说，Vasya 有两个女朋友住在不同位置，他要经常去看望她们中的一个，去往她们两个人家的火车发车频率分别是 $a,b$ 分钟一趟。题目要求他去哪个女友家更频繁一些。所以我们需要对比在一个周期，也就是 $ \operatorname{lcm}(a,b)$ 时间内，去哪个女友家概率更大一点，也就是比较时间长短。

首先令 $a,b$ 分别除以 $\gcd(a,b)$，然后比较大小，小的那个就是答案。相等的情况是$\left| a-b \right| = 1$。

为了方便解释，假设 $a \leq b$ （此时 $a,b$ 互素）,我们来计算能去 Masha 家的时间段总长度，其中的每个时间段满足：
  
- 大小不超过 $ a $ 。
- 所有时间段都是不相等的 。
- 所有时间段至少是 $ 1 $ 。

则 $ Length _{Masha}$ = $\sum_{1}^{a} x = \frac{a \times (a+1)}{2} \leq\frac{a \times b}{2}  $ 当 $a=b-1$ 时取等。

## AC Code

### python:

```python
from math import gcd
arr = input().split()
a, b = int(arr[0]), int(arr[1])
a, b = a//gcd(a, b), b//gcd(a, b)

if abs(a-b) == 1:
    print("Equal")
elif a > b:
    print("Masha")
else:
    print("Dasha")

```
### c++

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b=1,c=1;
	cin>>a>>b;
	if(abs(a/__gcd(a,b)-b/__gcd(a,b))<2){
		cout<<"Equal";
	}
	else{
		if(a>b){
			cout<<"Masha";
		}
		else{
			cout<<"Dasha";
		}
	}
	return 0;
}

```



---

## 作者：xmkevin (赞：0)

## 题目大意

给定两个数 $n$ 和 $m$，求出他们的最小公倍数 $\operatorname{lcm}(n, m)$，然后用最小公倍数分别除以这两个数，即 $n = \dfrac{\operatorname{lcm}(n, m)}{n}$，$m = \dfrac{\operatorname{lcm}(n, m)}{m}$。如果 $n$ 比 $m$ 大，那么 $m = m + 1$，否则 $n = n + 1$。

如果 $n$ 大，那么就要输出 `Dasha`。
如果 $m$ 大，那么就要输出 `Masha`。
如果 $n = m$，那么就要输出 `Equal`。

## 解题思路

首先我们知道 $n \times m = \operatorname{lcm}(n, m) \times \gcd(n, m)$，所以如果要求 $\operatorname{lcm}(n, m)$, 就可以用 $\dfrac{n \times m}{\gcd(n, m)}$。

然后按照题目大意模拟即可。

$\gcd(n, m)$ 可以用系统的 `__gcd(n, m)`，也可以手写辗转相除法。

P.S.一定要开 long long！

## 代码

14行。

```
#include<bits/stdc++.h>
using namespace std;

int main() {
    long long n, m;
    long long p = n * m / __gcd(n, m);
    n = p / n, m = p / m;
    if(n > m) m += 1;
    else n += 1;
    if(n > m) cout << "Dasha";
    else if(n == m) cout << "Equal";
    else cout << "Masha";
    return 0;
}
```

---

## 作者：guozhetao (赞：0)

## 题意
题意翻译没看懂，就按照了[这篇题解](https://www.luogu.com.cn/blog/xxzx-syl-blog/solution-cf87a)猜了一下题目大意。
给 $a$ 和 $b$，进行如下操作：
- $c = \operatorname{lcm(a,b)}$。
- $a = \dfrac{c}{a},b = \dfrac{c}{b}$。

- 当 $a > b$ 时 $b \gets b + 1$。
- 否则 $a \gets a + 1$。

求 $a$ 与 $b$ 谁大。

- $a > b$，输出 `Dasha`。
- $a = b$，输出 `Equal`。
- 否则输出 `Masha`。

## 思路
首先，$\operatorname{lcm(a,b)} = \dfrac{a \times b}{\gcd(a,b)}$。

其次，$\gcd(a,b)$ 可以用 `__gcd(a,b)` 来实现，这样就不用手写函数了。

最后按照题目模拟即可。
## 代码
13 行[AC](https://www.luogu.com.cn/record/97805743)
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	long long a,b,c; 
	scanf("%lld %lld",&a,&b),c = a * b / (__gcd(a,b));
	a = c / a,b = c / b;
	if(a > b) b++;
	else a++;
	if(a > b) printf("Dasha\n");
	else if(a == b) printf("Equal\n");
	else printf("Masha\n");
    return 0;
}
```
当然你也可以不用系统自带函数来压到 12 行成为[目前最优解](https://www.luogu.com.cn/record/97806624)：
```cpp
#include<cstdio>
#define ll long long
ll gcd(ll x,ll y){return y==0?x:gcd(y,x % y);}
int main() {
	ll a,b,c; 
	scanf("%lld%lld",&a,&b),c=a*b/(gcd(a,b));
	a=c/a,b=c/b;
	a>b?b++:a++;
	if(a>b)printf("Dasha\n");
	else if(a==b)printf("Equal\n");
	else printf("Masha\n");
}
```

## Update
2022/12/23 完成题解，通过审核。

2022/12/24 修改打错的变量名。

---

## 作者：abensyl (赞：0)

原题：[CF87A Trains](https://www.luogu.com.cn/problem/CF87A)

看到这题难度 $1500$，~~我直接懵逼了~~！

但是好像这题并不难，但没人写题解，我就来凑个热闹。

~~好像 Vasya 是个海王。~~

## 思路

本题大体就是一个最小公倍数问题。

### 做法：

1. 读入 $a$ 和 $b$。

2. 求 $a$ 和 $b$ 的最小公倍数。

- Q.：为什么求最小公倍数？

> 因为我们知道，Vasya 找女友是有规律的，而且有循环周期，而这个循环周期就是两数的最小公倍数。

3. 用最小公倍数分别除以 $a$ 和 $b$。

- Q：为什么要除以 $a$ 和 $b$？

> 因为除以 $a$ 的结果就是我们要去找 Dasha 的可能性，而除以 $b$ 的结果则是找 Masha 的可能性。

4. 如果 $a \leq b $ 将找 Masha 的可能性加一，否则将找 Dasha 的可能性加一。

5. 比较两可能性的大小，并输出。

## 代码（别的大佬代码很长，但本蒟蒻代码只有16行）
```cpp
#include <bits/stdc++.h>
#define ll long long
ll gcd(ll a, ll b) { 
  return b ? gcd(b, a % b) : a; 
}
int main() {
  ll a, b;
  std::cin >> a >> b;
  ll p = a * b / gcd(a, b);  //最小公倍数
  ll cnta = p / a, cntb = p / b;  //计算
  (a > b) ? cnta++ : cntb++;
  if (cnta > cntb) std::cout << "Dasha"; //比较、输出
  else if (cnta == cntb) std::cout << "Equal\n";
  else std::cout << "Masha\n";
  return 0;
}
```
[我的AC记录](https://www.luogu.com.cn/record/83464371)

走过路过，各位看官大佬，点个赞呗！

---

## 作者：serverkiller (赞：0)

亲，这边推荐直接模拟的呢（雾

其实就是一道模拟的水题，但是一定要注意一点：long long！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}
 
int main()
{
    ll a,b,c,n,m;
    scanf("%lld%lld",&a,&b);
    c=gcd(a,b);
    ll res=a*b/c;
    res--;
    n=res/a;
    m=res/b;
    if(n>m)m++;
    else if(n<m)n++;
    else
    {
        printf("Equal\n");
        return 0;
    }
    if(n>m)puts("Dasha");
    else if(n==m)printf("Equal\n");
    else printf("Masha\n");
    return 0;
}
```


---

