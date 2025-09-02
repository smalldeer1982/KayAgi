# Straight «A»

## 题目描述

Noora is a student of one famous high school. It's her final year in school — she is going to study in university next year. However, she has to get an «A» graduation certificate in order to apply to a prestigious one.

In school, where Noora is studying, teachers are putting down marks to the online class register, which are integers from $ 1 $ to $ k $ . The worst mark is $ 1 $ , the best is $ k $ . Mark that is going to the certificate, is calculated as an average of all the marks, rounded to the closest integer. If several answers are possible, rounding up is produced. For example, $ 7.3 $ is rounded to $ 7 $ , but $ 7.5 $ and $ 7.8784 $ — to $ 8 $ .

For instance, if Noora has marks $ [8,9] $ , then the mark to the certificate is $ 9 $ , because the average is equal to $ 8.5 $ and rounded to $ 9 $ , but if the marks are $ [8,8,9] $ , Noora will have graduation certificate with $ 8 $ .

To graduate with «A» certificate, Noora has to have mark $ k $ .

Noora got $ n $ marks in register this year. However, she is afraid that her marks are not enough to get final mark $ k $ . Noora decided to ask for help in the internet, where hacker Leha immediately responded to her request. He is ready to hack class register for Noora and to add Noora any number of additional marks from $ 1 $ to $ k $ . At the same time, Leha want his hack be unseen to everyone, so he decided to add as less as possible additional marks. Please help Leha to calculate the minimal number of marks he has to add, so that final Noora's mark will become equal to $ k $ .

## 说明/提示

Consider the first example testcase.

Maximal mark is $ 10 $ , Noora received two marks — $ 8 $ and $ 9 $ , so current final mark is $ 9 $ . To fix it, Leha can add marks $ [10,10,10,10] $ ( $ 4 $ marks in total) to the registry, achieving Noora having average mark equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF810A/b75d87f7c46ec7c9f8f2851b79244a71ffa349ba.png). Consequently, new final mark is $ 10 $ . Less number of marks won't fix the situation.

In the second example Leha can add $ [5,5,5] $ to the registry, so that making average mark equal to $ 4.5 $ , which is enough to have $ 5 $ in the certificate.

## 样例 #1

### 输入

```
2 10
8 9
```

### 输出

```
4```

## 样例 #2

### 输入

```
3 5
4 4 4
```

### 输出

```
3```

# 题解

## 作者：L2_sheep (赞：8)

其实这道题有一个数学方法：
设n个数的总和为s，要加x个k。
列出不等式：
s + kx >= (k - 0.5)(n + x) 
求解得 x >= (2k - 1)n - 2s
还有一个条件：x必须是个非负数，所以当算出来是一个负数，答案应该是0。

代码如下：
```cpp
#include <stdio.h>


int main() 
{
    int n, k, s = 0, x, i, a;
        
    scanf("%d%d", &n, &k);
    for(i = 0; i < n; i++){
    	scanf("%d", &x);
    	s += x;
	}
	a = (2 * k - 1) * n - 2 * s;
    if(a < 0) a = 0;
    printf("%d", a);
    return 0;
}
```

---

## 作者：C_Cong (赞：5)

[使用我的博客食用](https://dgsyrc.github.io/2020/03/25/洛谷题解%20CF810A%20【Straight%20《A》】/#more)

这题的思路：

简单循环枚举即可，因为数据量小。

主要的问题在于四舍五入。

枚举虽然看起来偷懒，但是在赛场上在数据以及时间空间限制允许的情况下，总比你跑数论好（省做题时间）。

我们知道`1.5`、`1.6`、`1.7`、`1.8`、`1.9`、`2.0`、`2.1`、`2.2`、`2.3`、`2.4`四舍五入都为2，我们可以将其扩大十倍，即`15`、`16`、`17`、`18`、`19`、`20`、`21`、`22`、`23`、`24`。

由于C++中的`/`是整除，这样我们就可以判断当扩大后的数被整除后，与k*10的误差范围为-5~4时即可判断相等。

至于小数点后面第二位及以后的数其实对此影响不大，因为扩大十倍后`15.00001`在整除中还是`15`,`24.999999`在整除中还是`24`。



代码如下：


```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int n,k,num[110],cot=0,sum=0;

int main()
{
	scanf("%d%d",&n,&k);
	k=k*10;//扩大十倍
	for(int a=1;a<=n;a++)
	{
		scanf("%d",&num[a]);
		sum=sum+num[a]*10;//扩大十倍
	}
	while(true)//无限循环判断
	{
		if((sum+cot*k)/(n+cot)>=k-5&&(sum+cot*k)/(n+cot)<k+5)
		{
			printf("%d\n",cot);
			break;
		}
		cot++;//累加k的个数
	}
	return 0;
}
```


---

## 作者：动态WA (赞：2)

本题解做法不涉及小数

基本思路：把所有数都扩大10倍，再进行模拟。设z为当前所有数的和，每次循环使z+=k，而n++，表示在两个变量中都加了一次k。若z/n<k-5，说明四舍五入后结果能为k，结束循环，输出结果。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
int n,k;
int main(){
	cin>>n>>k;
	k*=10;
	int d,z=0;
	for (int i=1;i<=n;i++){
		cin>>d;
		z+=d;
	}
	z*=10;
	int last=n;
	while (z/n<k-5){
		z+=k;
		n++;
	}
	cout<<n-last;
}
```
该程序缺陷:如果有像k=5,而z/n=4.45的数据（需要多次四舍五入的）会被卡，则需要把数据都扩大10^x倍，保证不出现多次四舍五入。


---

## 作者：TRZ_2007 (赞：1)

### 题解 [CF810A 【Straight «A»】](https://www.luogu.com.cn/problem/CF810A)  

# Solution  
这道题目我们可以用**不等式**来解决，下面写出数学推导。  

**解**：  
设要加上 $m$ 个 $k$ 能使平均数四舍五入后等于 $k$。  
由题意得：  
$$(k+0.4)(n+m)\ge \sum\limits_{i=1}^n a_i+mk\ge (k-0.5)(n+m)$$  
因为我们要求最小值，所以我们只需要解不等式：  
$$\sum\limits_{i=1}^n a_i+mk\ge (k-0.5)(n+m)$$  
$$\sum\limits_{i=1}^n a_i\ge nk-0.5n-0.5m$$  
$$\sum\limits_{i=1}^n a_i+0.5n+0.5m-nk\ge 0$$  
$$2\times\sum\limits_{i=1}^n a_i+n+m-2nk\ge 0$$  
$$m\ge 2nk-n-2\times\sum\limits_{i=1}^n a_i$$  


所以说，如果我们要取 $m$ 的最小值，那么 $m=2nk-n-2\times\sum\limits_{i=0}^n a_i$。  
但是注意，我们有一个默认条件：$m\ge 0$，所以当解出的值小于0时，要把它换成0。  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

int n,k,m,s;
int a[N];

int main() {
	scanf("%d %d",&n,&k);
	for(int i = 1;i <= n;i++) {
		scanf("%d",&a[i]);
		s += a[i];
	}
	m = 2 * n * k - n - s * 2;
	if(m <= 0) m = 0;
	printf("%d\n",m);
	return 0;
}
```

---

## 作者：PrincessYR✨～ (赞：1)

一道简单的小学数学题。

详解见代码：

```
#include<bits/stdc++.h>
using namespace std;
double tot,pd;
int a,b,c,num;
int main()
{
	cin>>a>>b;
	pd=b-0.5;//判断标准，即四舍五入要满足的条件，如果所得的平均数大于pd，呢么四舍五入后就可以为b(k) 
	for(int i=1;i<=a;i++)
	{
		cin>>c;
		tot+=c;//先把总数加起来 
	}
	if(tot/a>=pd)//如果不需要加数就为b(k) 
	{
		cout<<"0";//输出0 
		return 0;
	}
	while(1)
	{
		num++;//要加多少个b(k) 
		if((tot+b*num)/(a+num)>=pd)//如果满足四舍五入后为b(k)，那么直接输出num个数 
		{
			cout<<num;
			return 0;
		}
	}
 } 
```


---

## 作者：IOCTYCNconbill (赞：1)

# 这道题是真的很简单，认真想一下就出来了
## 首先先将前n个数加起来为sum，然后做一个无限的循环，从i=0开始做循环，然后当floor(sum/(n+i)+0.5)==m；只要满足条件，则输出i并return 0；结束程序就好了。
## 附上AC代码


# -------------------------------------
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	double sum=0;
	int x;
	for (int i=1;i<=n;i++){
		cin>>x;
		sum+=x;
	}
	int z=m;
	for (int i=0;;i++){
	if(floor(sum/(n+i)+0.5)==m) {//判断条件
		cout<<i;return 0;}
		sum+=z;//i从0开始循环，所以要后加z。
	}
}
```

---

## 作者：happybob (赞：0)

大家都用起来了数学方法，只有我还在用while一次次循环哎哎哎

不过这个题目思路很简单，不用数组，只需要把n个数加起来用while循环就ok，不过记得double

其实四舍五入一点都不难，不用自己写，直接cmath+round搞定

这里讲一下round:

round是四舍五入函数，头文件cmath，round函数只有一个参数，要用double，这个题用int你还要四舍五入干嘛……

继续说，round函数是四舍五入取整，如果需要将x保留n位小数，只需要先乘再除

比如round函数将9.9839保留3位小数

```cpp
round(9.9839 * 1000) / 1000
```

那么学会了round，代码就简单啦

AC code：
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double n, k, sum = 0, x, ans = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
    {
        cin >> x;
        sum += x;
    }
    while(round(sum / n) != k)
    {
        ans++;
        n++;
        sum += k;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：学而思李老师 (赞：0)

介绍一下这道题的 $O(1)$ 处理方法：

首先我们考虑四舍五入：如果 $n$ 四舍五入后等于 $k$，那么要满足 $k-\dfrac{1}{2}\leq n<k+\dfrac{1}{2}$。

根据平均数只和这些数的和和这些数的个数有关，我们可以只考虑所有已经给出的数的和。设之前的数的和等于 $sum$，我们现在要求的答案为 $x$，所以现在一共有 $(n+x)$ 个数，那么根据初一课内数学，我们可以列出不等式：

$$(k-\dfrac12)(n+x)\leq sum+xk$$

把所有关于 $x$ 的项挪到一边就可以发现 $x\geq(2k-1)n-2\times sum$。但是根据题意，$x\geq0$，所以我们只需要输出 $\max((2k-1)n-2\times sum,0)$ 即可。

---

## 作者：SIXIANG32 (赞：0)

一道显而易见的模拟题。  
我们要解决这个问题需要解决如下几个子问题：  

- 子问题1：平均数
- 子问题2：四舍五入将平均数变成整数

解决方案：  

- 子问题1：小学数学知识，总和除以总数
- 子问题2：C++的```cmath```库自带把小数四舍五入的```round```函数。   

最后我们再总结流程：  

1. 输入并得出它们的总和
2. 无限枚举加上$i$\*$k$，除以$n+i$并用```round```函数进行四舍五入。注意$i$是从$0$开始枚举的，有的时候可能是不用加的。如果最后得到的值等于$k$，输出$i$并结束程序。  

顺便总结个坑点：  

- C++如果要用```round```函数来四舍五入除以的数必须要乘$1.0$，因为和是整数，$n+i$也是整数，整数除以整数是整数所以要变成实数。 


很简单吧，下面我们来写代码：
```cpp
#include<iostream>
#include<cmath>//round头文件
using namespace std;
int main()
{
	int n,a[100001],k,sum=0;//sum是总和
	cin>>n>>k;
	for(int p=1;p<=n;p++)//步骤1
		cin>>a[p],sum+=a[p];
	for(int p=0;;p++)//步骤2
		if(round((sum+p*k)/(1.0*(n+p)))==k)
		{
			cout<<p<<endl;
			return 0;
		}
}
```

---

## 作者：Clever_Jimmy (赞：0)

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <cstdlib>

using namespace std;

int n,k;
int t,cnt;
double sum;

int round_double(double number)
{
    return (number > 0.0) ? (number + 0.5) : (number - 0.5); 
}//我们自己设置一个round_double()函数，它可以帮助我们四舍五入

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		sum=sum+t;//先把总和算出来
	}
	while(round(sum/(cnt+n))!=k)//如果四舍五入后还不到k
	{
		sum+=k;
		cnt++;//我们就继续
	}
	printf("%d",cnt);
	return 0;
}
```

---

## 作者：Victory_Defeat (赞：0)

这道题作为一道CF红题，还是比较水的，不过测试点整整有106个点，可以说在CF里也算测试点多的了~~反正CF红题都很水~~

先说一下思路：

1. 求出初始平均值

2. 不断在序列中加入k，并求出平均值

**注意：还有不需要加入k平均值即为k的情况**

具体的见代码注释即可：

```cpp
#include<cstdio>
#include<cmath>//使用round必须要调用cmath库
int n,x,sum,k,av;//x为一个变量代替数组（因为本题无需使用数组），av表示平均数，sum表示当前所有数的和
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&x);
        sum+=x;
    }//输入并计算初始和
    int n1=n;//记录初始个数
    double t=sum*1.0/n;
    av=round(t);//计算出在不插入k的情况下的平均数，作为特判
    while(av!=k)//只要平均数不为k
    {
        sum+=k;
        ++n;
        t=sum*1.0/n;
        av=round(t);//在序列中插入k，并求出新的平均数
    }
    printf("%d",n-n1);//输出答案，最终个数减去初始个数
}

```

---

