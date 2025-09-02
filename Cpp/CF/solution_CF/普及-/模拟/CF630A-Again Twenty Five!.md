# Again Twenty Five!

## 题目描述

The HR manager was disappointed again. The last applicant failed the interview the same way as 24 previous ones. "Do I give such a hard task?" — the HR manager thought. "Just raise number $ 5 $ to the power of $ n $ and get last two digits of the number. Yes, of course, $ n $ can be rather big, and one cannot find the power using a calculator, but we need people who are able to think, not just follow the instructions."

Could you pass the interview in the machine vision company in IT City?

## 样例 #1

### 输入

```
2
```

### 输出

```
25```

# 题解

## 作者：SqrtSecond (赞：4)

这道题其实是道数论题。

首先取每个数后两位相当于$\bmod100$

然后易知$5^2\equiv25(\bmod100)$

于是$5^3=5^2*5=25*5=125\equiv25(\bmod100)$

从而$5^4=5^3*5\equiv25*5=125\equiv25(\bmod100)$

继而$5^5=5^4*5\equiv25*5=125\equiv25(\bmod100)$

......

所以只要$5^n\equiv25(\bmod100)$，则$5^{n+1}=5^n*5\equiv25*5=125\equiv25(\bmod100)$

而$5^2\equiv25(\bmod100)$

所以可证$5^k\equiv25(\bmod100)$($k$为任意大于等于$2$的整数

得证。

简洁的四行代码
```cpp
#include<bits/stdc++.h>
int main(){
	printf("25");
}
```


---

## 作者：封禁用户 (赞：3)

看到这道题的数据范围,你可能会大吃一惊。

但是仔细思考思考你会发现，$5^n$($n≥2$)后两位都是$25$。

然而为什么呢？

若$5^n$每个数后两位都是$25$,则每$5^n$都能写成$x*100+25$的形式,$(x*500+125)$为$5^{n+1}$,$x*500$末两位绝对是零,而$125$末两位是$25$,将$x*500$和$125$相加为$(5*x+1)*100+25$,所以$5^n$($n≥2$)后两位都是$25$。

然后上代码($c++$):
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin>>n;
	cout<<25;
	return 0;
}
```
最后,点个赞再走吧(QAQ)。

---

## 作者：封禁用户 (赞：2)

### 前言

找规律题。


### 思路

仔细看题，数据范围是$2\sim 2*10^{18}$

写了个代码计算$5$ 的$1\sim 27$次方。

因为数字范围超$\sf long long$了，所以后面就不算下去了。

```cpp
1^5=5
2^5=25
3^5=125
4^5=625
5^5=3125
6^5=15625
7^5=78125
8^5=390625
9^5=1953125
10^5=9765625
11^5=48828125
12^5=244140625
13^5=1220703125
14^5=6103515625
15^5=30517578125
16^5=152587890625
17^5=762939453125
18^5=3814697265625
19^5=19073486328125
20^5=95367431640625
21^5=476837158203125
22^5=2384185791015625
23^5=11920928955078125
24^5=59604644775390625
25^5=298023223876953125
26^5=1490116119384765625
27^5=7450580596923828125
```

### $\sf Code$

先找规律。。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n=5;
int main() {
	cout<<"1^5=5"<<endl;
	for(int i=2; i<=100; i++) {
		n*=5;
		cout<<i<<"^5="<<n<<endl;
	}
	return 0;
}
```
然后的代码就简短啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin>>n;
	cout<<25<<endl;
	return 0;
}
```


---

## 作者：naroanah (赞：1)

关于这道题，本菜鸡的想法是这样的：

~~标题告诉我们了~~

把5的幂都求出来看一看就好了。

于是，我熟练地复制了以前快速幂的代码（快速幂思路可去[P1226](https://www.luogu.com.cn/problem/P1226)处获取），为了更快看出，可以直接 $mod$ 100看最后两位，便写出了如下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n=5,k,m=100,ans=1;
long long  ppow(int x,int k)
{
	while(k)
	{
		if(k&1)
		{
			ans=((ans%m)*(x%m))%m;
		}
		x=((x%m)*(x%m))%m;
		k>>=1;
	}
	return ans;
}
int main()
{
	cin>>k;
	for(int i=2;i<=k;i++) 
	{
		cout<<ppow(n,i)<<endl;
	}
	return 0;
}
```
输个 1000 进去一看，怎么都是 25 啊，于是代码就来了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	cout<<"25"<<endl;
	return 0;
}
```
完美AC！

PS：其实这是道数学题，本蒟蒻却把它做成了找规律，证明可以看其他几位大佬的题解。



---

## 作者：_cmh (赞：1)

本题不简单吗

我们先把$5^n$全列出来：

```
1^5=5
2^5=25
3^5=125
4^5=625
5^5=3125
6^5=15625
7^5=78125
8^5=390625
9^5=1953125
10^5=9765625
11^5=48828125
12^5=244140625
13^5=1220703125
14^5=6103515625
15^5=30517578125
16^5=152587890625
17^5=762939453125
18^5=3814697265625
19^5=19073486328125
20^5=95367431640625
...
```

发现$5^n$的后两位都是25（除$5^1$外）

而且因为$n >= 2$

所以我们直接连输入都不用，直接输出25即可。

```cpp
#include<iostream>//头文件
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int main(){
	cout<<25;//直接输出25
 	return 0;
}
```

点个赞再走呗~

---

## 作者：小鲍bob (赞：1)

### 此题就是考察微弱的数论知识

题意清楚的告诉了我们n>=2，所以不用考虑0和1的情况，直接输出25就可以了。

下面给出严格的证明过程：

由题可知：$5^{2}$=25，末两位为25，且$5^{k}$又等于$5^{2}$ * $5^{k-2}$

所以$5^{k}$必定可以写成25*$5^{k-2}$的形式

又因为$5^{k-2}$ mod 4等同于$1^{k-2}$ mod 4，


又因为1的任何次方都等于1

所以$5^{k-2}$mod 4=1

所以$5^{k}$末尾必定为25*1=25

证毕

下面给出标程：

```
#include<iostream>
using namespace std;
int main()
{
	cout<<"25";//因为输入的n大于2，所以直接输出25，不用输入节省时间
	return 0;//不加易超时(当然这题肯定不会)
 }
```


---

## 作者：yuangq (赞：1)

~~~
这题比较简单，我就简单证明一下 
n>=2时5^n≡25(mod 100) 

首先我们知道n²=125

所以，我们只需要证明末尾为25的数乘以5末尾还是25

我们设那个数为 n*100+25 (n ∈ N+)

它乘以5后得到 
 n*500+125
=(5*n)*100+100+25
=(5*n+1)*100+25
≡25(mod 100)
~~~

所以末尾是25的数乘以5后末尾还为25

所以这题只需输出25即可

代码

~~~
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	cout<<25;
	return 0;
}
~~~

---

## 作者：CobaltChloride (赞：1)

```
对于n>=2可得5^n≡25(mod 100)
简单了
#include<bits/stdc++.h>
using namespace std;
int main(){
    cout<<"25";
    return 0;
}
```

---

## 作者：Franka (赞：0)

### **题目**
输出$5^n$的**后两位**。

$2$ ≤ $n$ ≤ $2⋅10^{18}$
### **思路**
首先枚举一下：

$5^2=25$

$5^3=125$

$5^4=625$

$5^5=3125$

$5^6=15625$

$5^7=78125$

$5^8=390625$

⋅

⋅

⋅

## 可以发现，后两位都是25

### **代码**
#### Pascal
```pascal
begin write(25);end.
```
#### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	cout<<25<<endl;
	return 0;
}
```

---

## 作者：_Legacy (赞：0)

#### 分析

~~从题目可得知"又是25"，所以输出25就行了~~

如果要从$5^n$的得数来看的话我们可以看到一个现象：
```
                  5
                 25
                125
                625
               3125
              15625
              78125
             390625
            1953125
            9765625
           48828125
          244140625
         1220703125
         6103515625
        30517578125
       152587890625
       762939453125
      3814697265625
     19073486328125
     95367431640625
    476837158203125
   2384185791015625
  11920928955078125
  59604644775390625
 298023223876953125
1490116119384765625
7450580596923828125
```
我们一列列地看会发现$5^n$的得数每一位都是有规律的：

个位：5 的循环

十位：2 的循环

百位：1->6 的循环

千位：3->5->8->0 的循环

万位：1->7->9->5->6->2->4->0 的循环

十万位：3->9->7->8->1->7->5->5->8->4->2->3->6->2->0->0 的循环

(大家可能都发现了末尾都是25，但没发现每一位都有规律)

而它们的循环长度又都是$2^n$中的数。

但由于本题只要求输出后两位，所以只要
```cout << 25;```
便可以了。


------------

如果有dalao可以解释这一现象请在评论区留言

---

## 作者：Fuko_Ibuki (赞：0)

首先看题目,根据常识知道当$n\geq 2$的时候$5^{n}$的最后两位一定是25.  
再看数据范围我直接高兴地跳起来了.  
$2\leq n\leq 10^{18}$
所以就很简单了.
```c
main(){puts("25");}
```

---

## 作者：МiсDZ (赞：0)

题目思路很简单。

观察下列数列：
>$5^0=1$
>
>$5^1=5$
>
>$5^2=25$
>
>$5^3=125$
>
>$5^4=625$

你会发现，除了$5^0$和$5^1$之外其余的末尾两位数均为25（废话），所以只需要特判一下0和1的情况即可。

（这题的标题也是真的妙啊）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    if(n==0) cout<<1<<endl;
    else if(n==1) cout<<5;
    else cout<<25;
    return 0;
}

```

---

## 作者：UKE自动稽 (赞：0)

这一题……其实挺水的。

题目说了：输出$5^n$的后两位，那我们就找规律：

$5^0=1$

$5^1=5$

$5^2=25$

$5^3=125$

$5^4=625$

…………

最后发现，除了第一、二行，其他的末两位都是25，那么就特判一下前两种情况，剩下就输出25就行了。

另外，这一题需要以文件结束符（EOF）结束

```

#include<iostram>
int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		int ans=25;
		if(n==0)
		{
			ans=1;
		}
		else if(n==1)
		{
			ans=5;
		}
		printf("%d\n",ans);
	}
	return 0;


```

~~其实这一题的数据挺水的，不需要那么多特判也能AC~~

```
#include<iostream>
int main()
{
	ll n;
	while(scanf("%lld",&n)!=EOF)
	{
		printf("25\n");
	}
	return 0;
}

```

PS:程序中有语法错误，想抄就会CE,别怪我没提醒。

---

## 作者：monstersqwq (赞：0)

#### ~~传说中的~~一句话题意：

求 $5^n$ 的后两位。

很好的快速幂练手题（数论做也是没问题的辣）。

首先转换一下题意：求 $5^n \bmod 100$。

看到数据范围：$n \le 2 \times 10^{18}$，就知道 $\Theta(n)$ 的一边乘一边取模的暴力方法过不了，于是就要采用 $\Theta(\log n)$ 的快速幂。

作为一个快得很的求积方法（不过必须要有膜数，不然大概要搞高精），泥谷有[模板题](https://www.luogu.com.cn/problem/P1226)，具体写法看题解即可，只需要将输入的底数和模数换成 $5,100$。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
long long tmp,n,ans=1;
int main()
{
	cin>>n;
	tmp=5;
	while(n>0)
	{
		if(n%2==1)
		{
			ans*=tmp;
			ans%=100;
		}
		tmp*=tmp;
		tmp%=100;
		n/=2;
	}
	cout<<ans%100<<endl;
    return 0;
}
```


---

