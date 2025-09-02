# About Bacteria

## 题目描述

游侠  $Qwerty$  接受了一项政府的工作并来到了火星。他需
要呆在神奇实验室里做一些关于细菌的实验，这些实验十分有趣和不寻常。这项工作不难，却又很高的报酬。

第一次实验中，试管里只有1个细菌，每秒钟每个细菌会分裂成  $k$  个，同时通过一些不寻常的变化，还会再多出  $b$  个细菌。也就是说，一开始试管中有  $x$  个细菌，那么一秒后试管中就会有  $kx+b$  个细菌。

第一次实验中发现，当一开始在试管中放入1个细菌时，经过  $n$  秒之后，刚刚好有  $z$  个细菌

第二次实验，游侠  $Qwerty$  会对试管消毒（也就是说没有细菌了），然后他再把  $t$  个细菌放进去。在没有开始实验前，他突然想知道：按照第一次实验中的分裂模式，他至少需要多少秒钟才能够让试管中有  $z$  个细菌呢？

帮助  $Qwerty$  找出这个最小秒数吧！

## 样例 #1

### 输入

```
3 1 3 5
```

### 输出

```
2```

## 样例 #2

### 输入

```
1 4 4 7
```

### 输出

```
3```

## 样例 #3

### 输入

```
2 2 4 100
```

### 输出

```
0```

# 题解

## 作者：wmrqwq (赞：5)

# 原题链接

[CF198A About Bacteria](https://www.luogu.com.cn/problem/CF198A)

# 题目简述

有一个试管中有 $t$ 个细菌，每秒钟一个细菌会分裂成 $k$ 个细菌，且每秒钟试管内还会额外多出 $b$ 个细菌，求出至少需要多少秒钟才能够让试管中有 $z$ 个细菌。

# 解题思路

首先，写这一道题的代码是一定不能写模拟的，否则当 $t=10^6$ 且 $k=10^6$ 的时候，显然是会爆 ```long long``` 的，所以，我们就要换一种思路，我们不难发现，如果我们循环到第 $a$ 秒的时候现在细菌的数量不等于目标数量，这时只需要减去这个时间即可，但是，需要注意的是，如果无法实现，就要输出 $0$ 即可。

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0
long long a,b,c,d,e=1,sum=0;
int main()
{
	cin>>a>>b>>c>>d;
	while(e<=d && sum<=c) 
	{
		sum++; //当没有达到目标数量,将时间加上1
		e=a*e+b;
	}
	cout<<c-sum+1;//注意，这里一定要加上1
	QwQ;//华丽的结束
}
```


---

## 作者：miraculously (赞：2)

分析：

这道题如果用模拟，会爆 long long。仔细思考一下，会发现不用遍历到 $n$ 就能找到答案，只要求出到第 $i$ 秒 $a$ 的值一直小于等于 $t$，总时间减去这个时间就是答案。这里稍微证明一下，如果这一秒 $a$ 刚好等于 $t$，显然过了 $n-i$ 秒后，$t$ 等于 $z$，如果在这一秒 $a$ 刚好小于 $t$（指下一秒 $a$ 就比 $t$ 大），那过了 $n-i$ 秒 $t$ 刚好大于 $z$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long k,b,n,t,a=1,cnt=0;
	scanf("%lld%lld%lld%lld",&k,&b,&n,&t);
	for(int i=1;i<=n;i++)
	{
		a=a*k+b;
		if(a<=t)
		cnt=i;
		else
		break;//a大于t直接结束循环
	}
	printf("%lld",n-cnt);
}
```


---

## 作者：zmt2016 (赞：1)

刚看到题目，四个10^6次方的范围。z最大10^6的10^6次方。然后在电脑前思索了15分钟的高精度。接着，准备放弃。

但看着只有一人通过，又不甘心，所以我又去CF上骗了几个数据看看，希望有什么发现，看着看着，发现真的来了—— 
答案和天数n离的很近，只差一点，灵感突然就来了。


------------


------------

下面是重点： 

既然这样，10^6的大小完全足够。只要求出第一次的，达到第二次的细菌初始量要几秒，再用原先的天数减就可以了。

接下来就不用多说了，已经非常简单了。直接上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int k,b,n,t;
	long long z=1,z2,ans=0;//ans记录几秒
	cin>>k>>b>>n>>t;
	while(z<=t && ans<=n) z=k*z+b,ans++;//主要程序，当1变到t要几秒 
	cout<<n-ans+1;//别忘记加一 
	return 0;
}
```

---

## 作者：baiABC (赞：1)

$\texttt{upd: 改了一处打错的地方}$

硬核数学做法。

设最开始细胞数为 $a_0$，$i$ 秒后细胞数为 $a_i$。由题意，$i>0$ 时，有 $a_i = ka_{i-1}+b$，下面分两种情况考虑：
## type 1
若 $k=1$，则 $a_i=a_{i-1}+b$，是等差数列，有 $a_i=ib+a_0$，取 $a_0=1$ 得 $z=nb+1$。

设答案为 $x$，则取 $a_0=t$ 时，要有 $a_x\geq z$，即 $xb+t\geq nb+1$，得 $x\geq n-\dfrac{t-1}{b}$，故 $x\geq n-\left\lfloor\dfrac{t-1}{b}\right\rfloor$（这里用到了 $\left\lceil x\right\rceil=-\left\lfloor -x\right\rfloor$），答案为 $\max\left(n-\left\lfloor\dfrac{t-1}{b}\right\rfloor,0\right)$。
## type 2
若 $k>1$，则利用不动点法，得 $a_i+\dfrac{b}{k-1}=k\left(a_{i-1}+\dfrac{b}{k-1}\right)$，故 $a_i+\dfrac{b}{k-1}=k^i\left(a_0+\dfrac{b}{k-1}\right)$，则 $a_i=k^i\left(a_0+\dfrac{b}{k-1}\right)-\dfrac{b}{k-1}$，取 $a_0=1$ 得 $z=k^n\left(1+\dfrac{b}{k-1}\right)-\dfrac{b}{k-1}$。

设答案为 $x$，则取 $a_0=t$ 时，要有 $a_x\geq z$，即 $k^x\left(t+\dfrac{b}{k-1}\right)-\dfrac{b}{k-1}\geq k^n\left(1+\dfrac{b}{k-1}\right)-\dfrac{b}{k-1}$，化简得 $x\geq n+\dfrac{\ln\left(\dfrac{1+\dfrac{b}{k-1}}{t+\dfrac{b}{k-1}}\right)}{\ln k}$，故答案为 $\max\left(n+\left\lceil\dfrac{\ln\left(\dfrac{1+\dfrac{b}{k-1}}{t+\dfrac{b}{k-1}}\right)}{\ln k}\right\rceil,0\right)$。

没有被卡精度。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
   int k, n, t; double b; cin >> k >> b >> n >> t;
   if(k > 1)
   {
      b /= k-1;
      cout << max(0, (int)ceil(log((1+b)/(t+b))/log(k))+n) << '\n';
   }
   else cout << max(0, n-(int)floor((t-1)/b)) << '\n';
   return 0;
}
```

---

## 作者：yzc20100218 (赞：0)

## CF198A 题解
这道题一眼看过去是一道模拟题，但是一看数据范围：$1\le k\le 10^6$，这种情况肯定是需要高精度的，但是高精度写多了就厌倦了……

首先，我们看一下细菌生成方法：  
$1\to k+b \to (k+b)\times k+b \to\dots\to z$  
但是如果我们把这个过程倒过来：  
$z\to \dfrac{d-b}{k}\to\dots\to1$

如果是从 $x$ 开始，一样把过程倒过来，我们会发现这个过程包含于刚才那个工程，但是上面的过程多了一部分：  
$x\to \dfrac{x-b}{k}\to\dots\to1$

假如 $x$ 通过 $ans$ 秒得到 $1$，则我们可以得到 $x$ 得到 $z$ 的秒数为 $n-ans+1$。当然，$n<ans$ 就不可能得到以上步骤，所以此时输出 $0$。

放代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll k,b,n,t;

int main()
{
	scanf("%lld %lld %lld %lld",&k,&b,&n,&t);
	ll st = 1,cur = 0;
	while(st <= t and cur <= n)
	{
		st = st * k + b;
		cur++;
	}
	if(cur > n)
	{
		puts("0");
	}
	else
	{
		printf("%lld\n",n - cur + 1);
	}
	return 0;
}
```

---

## 作者：Colead (赞：0)

### 代码绝对新手友好

仔细思考一下发现很简单，细菌的繁衍是一个重复过程。换而言之，如果经过某些次数的繁衍它正好能够达到第二次的初始个数，那直接减一减就可以了，反正对于相同的起始个数繁衍过程都是相同的。所以对于理想情况，只要求出前一段从 $1$ 到 $t$ 的次数，然后用 $n$ 减掉就可以了。

但是呢？有可能不是正正好好是 $t$ ,所以算到比 $t$ 严格大的数就可以了。然后简单处理一下。因为本来 $t$ 和更大的数应该分开处理的，但严格大于可以避免这一点。

看代码，最直观：

```
#include<bits/stdc++.h>
using namespace std;
long long k,b,n,t;
int main()
{
	cin>>k>>b>>n>>t;
	long long s=1,sum=0;
	while(s<=t)
	{
		sum++;
		s=k*s+b;
	}
	cout<<max(n-sum+1,0LL)<<endl;
	return 0;
}
```


---

## 作者：小杨小小杨 (赞：0)

## 题意
给你一种病菌，这种病菌在第零秒有1个，第一秒有 $1 \times k + b$ 个，第二秒有 $(1 \times k + b) \times k + b$ 个，第三秒有 $((1 \times k + b) \times k + b)\times k + b$ 个……以此类推，经过 $n$ 秒后，刚好就有 $z$ 个病菌。问：现在已经有了 $t$ 种病菌，问以此类推，经过几秒后刚好也有 $z$  个病菌？
## 思路
暴力肯定是行不通滴。我们可以发现，我们现在已经有了 $t$ 个病菌，那么我们是不是就可以把病菌数量从1个到 $t$ 个病菌之间的过程给省略了？那么我们其实只要知道我们省略了多少时间，再用总时间去减去省略的时间即可。如果无法实现，那么就输出0。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,b,n,t,ans,times;
int main(){
	scanf("%lld%lld%lld%lld",&k,&b,&n,&t);//记得开long long
	ans=1;//初始有一个病菌
	while (ans<=t&&times<=n) ans=ans*k+b,times++;//判断是否已经超过了现在的数量
	if (times>n) printf("0");//如果不可能，输出0
	else printf("%lld\n",n-times+1);//如果可以，输出时间。
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

思路 
---
一开始用模拟，但是显然不能模拟，会爆。

所以，错了十多次后，总结了一下规律，会发现一个循环到如果第 $i$ 秒 $a$ 不超过 $t$ ，减去这个时间就可以。

证明：分情况讨论。
- 第 $i$ 秒时，细菌数量正好是 $z$ ,则时间恰好为 $n-i$ ；
- 第 $i$ 秒时，细菌数量大于 $z$ ,则时间也取整为 $n-i$ 。

上代码：
```cpp
#include<bits/stdc++.h>
#define NOIP long long
using namespace std;
NOIP k,b,n,t,rp,p=1;
int main() {
  scanf("%lld%lld%lld%lld",&k,&b,&n,&t);//输入
	for(;p<=t;){
	  rp++;//时间++
		p=k*p+b;//该阶段细菌数量
	}
	printf("%lld\n",max(n-rp+1,(long long)(0)));
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

这道题显然不能用模拟，随手一算，肯定会爆 long long。

## $\text{1. 思路}$

那么既然不能模拟，这应该是一道找关系类型的数学的题。

我们只需要考虑 $t$ 可以由一个细菌多少秒分裂形成。

因为，一旦在第 $x$ 秒的时候细菌数量大于等于了 $t$，那么 $n - x$ 秒之后分裂出来的细菌数量一定大于等于 $z$。同时，如果第 $x$ 秒时数量小于 $t$，那么~~根据小学学的数学~~可以得知 $n - x$ 秒之后分裂出来的数量一定小于 $z$。

或者这样说，令 $f(x) = kx+b$，那么怎么知道 $f(t)$ 嵌套多少层之后能大于等于 $z$ 呢？只需要知道 $f(1)$ 嵌套多少次能大于等于 $t$，以及 $f(1)$ 嵌套多少次能到达 $z$ 。这样 $f(t)$ 嵌套次数就是后者减去前者。

那么代码就很好写了。注意判断有的时候会出现负数，这个时候为了符合实际情况应该输出 0（比如第二个样例），以及记得开 long long（第 75 个点）！

## $\text{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long k,b,n,t,x=1,cnt=0;
	scanf("%lld%lld%lld%lld",&k,&b,&n,&t); //输入
	while(k*x+b<=t) x=k*x+b,cnt++; // 找答案
	printf("%lld",max(0ll,n-cnt)); // 输出答案，注意判小于 0 的情况
	return 0;
}
```

完结撒花 ~ qwq

---

