# Tricky Sum

## 题目描述

In this problem you are to calculate the sum of all integers from $ 1 $ to $ n $ , but you should take all powers of two with minus in the sum.

For example, for $ n=4 $ the sum is equal to $ -1-2+3-4=-4 $ , because $ 1 $ , $ 2 $ and $ 4 $ are $ 2^{0} $ , $ 2^{1} $ and $ 2^{2} $ respectively.

Calculate the answer for $ t $ values of $ n $ .

## 说明/提示

The answer for the first sample is explained in the statement.

## 样例 #1

### 输入

```
2
4
1000000000
```

### 输出

```
-4
499999998352516354
```

# 题解

## 作者：houpingze (赞：4)

此题需要一些~~小学~~数学知识QWQ

思路：

首先我们把1~n的数全部都加起来，**不能用暴力**，$10^9$绝对会TLE,那就用高斯求和呗~

公式：

$1+2+3+...+n$
  $=$$(1+n)*n/2$
  
最后，再枚举$2^n$，**减去2次**即可

### 最后：不开longlong见祖宗！

code：

```cpp
#include<iostream>
typedef long long ll;
using namespace std;
ll n,cnt,m,t;//不开longlong见祖宗！！！ 
int main(){
	cin>>t;//t组数据 
	while(t--){
		cin>>n;
	 	ll sum=(1+n)*n/2;//高斯公式 
	 	ll i=1;
	 	while(i<=n){
	 		sum-=i*2;//减2次！！！ 
	 		i*=2; //下一次减的数量
		}
		cout<<sum<<endl;//输出 
	}
}


```

---

## 作者：bjrjk (赞：1)

这道题目本来一开始是想要搞暴力的，但是第一个就超时。不得已换了个数学方法。

首先用小学生都会的数列求和：

（首项+末项）*项数/2 

把从1到n的和算出来，然后计算出不大于n的2的幂次共有多少个，用等比数列求和公式求出它们的和，减去两倍即可。
上代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long try2(long long n){ //函数try2就是计算从1到n之间所有不大于n的2的幂次之和，可结合等比数列求和公式推导后再领悟，不懂可以看下面的解释。
	long long m2=1;
	while(m2<=n)m2*=2;
	return m2-1;
}
void process(){
	long long n;
	cin>>n;
	cout<<((1+n)*n/2-2*try2(n))<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--)process();
}
```
其实做这道题是要数学功底的。。。我还是把具体的推导过程说一下好了。我们想要求出小于n的所有2的幂次方项之和，根据等比数列求和公式可知:$$2^0+2^1+2^2+...+2^n=2^{n+1}-1$$所以我们只要找到最大的小于n的2的幂次再乘2减1就可以了。具体代码可参见函数try2()。

---

## 作者：WanderingTrader (赞：0)

本来想打暴力的，结果：
>$n\le10^9$

那就算了吧，还是用数学方法比较好。
### 题目分析
我们发现，题目所求其实就是：
$$\large{\sum\limits_{i=1}^ni-2\times\prod\limits_{i=0}^{\log_2n}2^i}$$

同时我们知道
$$\sum\limits_{i=1}^ni=\dfrac{n(n+1)}{2}$$  
$$\prod\limits_{i=0}^{\log_2n}2^i=2^{i+1}-1$$
（不理解这两个公式的，请移步[this](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F)和[this](https://baike.baidu.com/item/%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F)）  
那么用 $O(1)$ 的时间就能解决了
### 代码
很容易：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
inline int read()
{
 	int x=0,f=1;
 	char c=getchar();
 	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
 	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
 	return x*f;
}
int main()
{
	int T=read();
	while(T--)
	{
		ll n=read();
		ll ans=n*(n+1)/2;
		int Log=log(n)/log(2)+1e-10;
		ll Ans=(1<<Log+1)-1;
		ans-=(Ans<<1);
		printf("%lld\n",ans);
	}
	return 0;
}
```
需要注意的是：
1. n要用long long，否则算ans时会溢出
2. Log要做精度调整，否则在计算中极易出事故  
比如 $\log_28$ 可能就被计算成 $2$ 了。  
而且精度要做的非常小，本人曾试过 $10^{-7}$ 的精度，然而失败了，取到 $10^{-10}$ 才成功。

$$\texttt{The End.}$$

---

## 作者：FutureThx (赞：0)

## 题目大意

题面：[传送门](https://www.luogu.com.cn/problem/CF598A)

## 前备知识

### 1. 一点点小学奥数
理解题目意思后，本来想打一个暴力混过此题，奈何出题人太不良心，$O(nt)$ 的时间复杂度让你哭的地方都没有，怎么办？这个时候我们就可以开始推式子了

设一个等差数列 $A$ , $A_i=A_i+1$ ,长度为 $n$ ,

 $ \ \ \ \ A_1+A_2+A_3 …… +A_n$

$= A_1 + (A_1+1) + (A_1+2) …… (A_1+n-1)$

$= A_1 · n + (1 + 2 + …… + n - 1)$

$= A_1 · n + (1 + 2 + 3 + …… + n - 3 + n - 2 + n - 1) $

$= A_1 · n + \frac{n - 1}{2}· n$

$= n·(A_1 +\frac{n - 1}{2})$
### 2. 一个可以用的脑子

~~是个人都有这个东西~~

## 思路
我们推出了公式后，就可以开始写代码了，因为题目中要求若一个数满足 $2^i$ 则变加为减，所以只需要枚举区间 $[1 ,n]$ 中所有的为 $2$ 的次幂的数，然后让起始总和减去这些数总和的 $ 2 $ 倍，为什么是 $ 2 $ 倍呢？因为总和在先前已经加上此数了，必须减去 $2$ 次才可以变加为减。

## 代码

$\ \ 100pts:$
```cpp
#include <iostream>
int main()
{
    int T;
    std::cin >> T;
    while(T--){
        long long n,t,x = 1;
        std::cin >> n;
        t = double(n * (1 + (double)(n - 1)/2));
        while(x <= n)
            t -= x *= 2;
        std::cout <<  t << std::endl;
    }
    return 0;
}
```
这是本蒟蒻的第三篇题解，求管理员通过

---

## 作者：Suuon_Kanderu (赞：0)

简单数学题。

一句话题意： 

$$\sum^{i = 1}_{i \leq n}{i} -2 \times\sum_{2^i \leq n}^{i=0} 2^i $$

（因为前面 2 次幂加了一次，现在需要减两次）

直接套用等差数列求和公式和等比数列求和公式即可。但因为用等比数列求和公式也是 $\log$ 级别的，所以直接暴力算就可。

附：等差数列求和公式

![](https://dss1.baidu.com/6ONXsjip0QIZ8tyhnq/it/u=2838679063,299287394&fm=58)

(来自百度，公式中首项为$a_1$，末项为$a_n$，项数为$n$，公差为$d$，前n项和为$S_n$。)

本人小学证明(归纳法)：

我们将等式两边加上$a_{n+1}$,也就是加上$a_1 + (n+1-1)\times d$
化简：
$$S_{n+1} = n a_1 + \frac{n(n-1)}{2}d + a_1 + n\times d $$
$$~~~~~~~~~~ = (n+1) a_1 + [\frac{n(n-1)}{2}+n]\times d $$
$$~~~~~~~~~~~~ = (n+1) a_1 + [\frac{(n-1)n}{2}+\frac{2n}{2}]\times d $$
$$~~~~~~~~~~~~~~~~~ = (n+1) a_1 + [\frac{(n+1)(n+1-1)}{2}]\times d $$

我们观察可得，所有的 n 都换成了 n+1 。所以说当某个等差数列只要当$n = k$时柿子成立，$k+1$ 项时这个
柿子是也没错。 n=1 时柿子铁定成立，我们就可以确定$n \in N^*$时柿子成立。





---

## 作者：chufuzhe (赞：0)

这道题暴力显然会超时，所以需要思考一个数学方法。

可以先用高斯求和的方法求出1到$n$的和（高斯求和：(首项+末项)$\times$项数/2），因为2的次幂本来应该减掉这里却加上了，所以要减去1-$n$中的2的次幂的和的两倍。

求1-$n$中的2的次幂的和只要从1开始不断乘2，如果小于等于$n$就加上这个数，否则停止乘2。

代码：
```cpp
#include<bits/stdc++.h> //万能头
using namespace std;
int mi(int n) //求1-$n$中的2的次幂的和
{
	int a=1,s=0; //1-2的次幂，1-$n$中的2的次幂的和
	while(a<=n) //小于等于$n$
	{
		s+=a; //加上这个数
		a<<=1; //位运算乘2
	}
	return s; //返回1-$n$中的2的次幂的和
}
int main() //主函数
{
	long long s; //答案
	int t,n; //t表示数据组数
	cin>>t; //输入
	while(t--)
	{
		cin>>n;
		s=(((1+n)*1ll*n)>>1)-(mi(n)<<1);
		//((1+n)*1ll*n)>>1表示1到n的和
		//(mi(n)<<1)表示1-n中的2的次幂的和的两倍
		cout<<s<<endl; //输出
	}
	return 0; //结束
}
```


---

## 作者：hensier (赞：0)

题目重要关键词：
> $1\le t\le 100$

> $1\le n\le 10^9$

假如本题使用暴力算法，那么时间复杂度将达到$O(nt)$，这可以达到$10^{11}$，而它远远大于$3\times10^8$（大致为$1s$时间限制）。因此必定超时。

我们只能通过别的方法解决。本题可以使用到等差数列，但是要考虑负数的问题，而单单考虑负数的话可以节约一大把时间。这时时间复杂度大致为$O(t·\lceil{log_n}\rceil)$（以$2$为底）。而$n\le10^9$，而$2^{30}=1073741824$，这略大于$10^9$，所以最大时间复杂度只有$100\times 30=3000$。

现在要先求：

$$\sum_{i=1}^ni$$

我们不妨设上式为$S$，即$S=1+2+...+n$。现在假设$S'=n+(n-1)+...+1$。而$S=S'$。

我们计算：

$$S+S'=(1+n)+(n+n-1)+...+(n+1)=n(n+1)$$

因此：

$$S=\frac{S+S'}{2}=\frac{n(n+1)}{2}$$

即：

$$\sum_{i=1}^ni=\frac{n(n+1)}{2}$$

然后我们先设置一个变量$i=0$，然后不停地累加，如果$2^i\le n$则减去$2\times2^i$，即等同于将原来的加变为减。

我们可以得到代码：

```python
n = int(input())//输入个数n
for times in range(n)://外层循环
    a = int(input())//输入a
    s = int((1 + a) * a / 2)//先求和
    i = 0//初始化i=0
    while True:
        if 2 ** i <= a://判断幂是否小于等于输入的数
            s -= 2 ** i * 2//a**b等同于以a为底数，b为指数的幂的结果
            i += 1//计数器加1
        else:
            break//大于的话就退出
    print(s)//输出自带换行
```

注意！上述代码在$Py3$下写成，但洛谷$Py3$无法通过（第一个$WA$的测试点有大约$4$的误差），只有使用$Py2$才能$AC$。

当然，$C++$的速度和内存较优于$Python$，但是作为入门训练，不妨练一练$Python$。

---

## 作者：cold_cold (赞：0)

[安利一波博客](https://www.cnblogs.com/cold-cold/p/10023927.html)

其实做法很简单，把从1到n的和用等差数列算出来，然后用log2n计算出不大于n的2的幂次共有多少个，用等比数列求和公式求出它们的和，减去两倍的它即可。

但是我发现WindowsXP居然卡精度严重，有很高的精度流失，

kepa=log(n)/log(2);当n=8时在Linux和Windows7下跑出来kepa都是3，

但WindowsXP跑出来居然是2，为了解决这个问题我们只能这样写kepa=(log(n)/log(2)+0.0000000001);

总体代码如下：

```cpp

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline ll read()
{
    register ll p(1),a(0);register char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
ll t,n,kepa;
inline ll fast(ll a,ll b)
{
    ll ans=1;
    while(b)
    {
        
        if(b&1) ans*=a;
        a*=a;
        b>>=1;
    }
    return ans;
}
int main()
{
//    freopen("input","r",stdin);
//    freopen("output","w",stdout);
    t=read();
    while(t--)
    {
        n=read();
        kepa=(log(n)/log(2)+0.0000000001);
//        printf("%d",kepa);
        printf("%I64d\n",( (1ll+n)*n/2ll )-( (fast(2,kepa+1)-1ll)*2ll) );
    }
    return 0;
}
```


---

