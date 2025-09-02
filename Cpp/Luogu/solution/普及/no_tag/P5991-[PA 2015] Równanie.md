# [PA 2015] Równanie

## 题目描述

对于一个正整数 $n$，定义 $\operatorname{f}(n)$ 为它十进制下每一位数字的平方的和。

现在给定三个正整数 $k,a,b$，请求出满足 $a\le n\le b$ 且 $k\times \operatorname{f}(n)=n$ 的 $n$ 的个数。

## 说明/提示

对于 $100\%$ 的数据，$1\le k,a,b\le 10^{18}$，$a\le b$。

---

### 样例解释：

满足的 $3$ 个 $n$ 分别为 $7293,7854$ 和 $7905$。

## 样例 #1

### 输入

```
51 5000 10000```

### 输出

```
3```

# 题解

## 作者：Wind_Smiled (赞：4)

## 题意

对于一个正整数 $n$，定义 $\operatorname{f}(n)$ 为它每一位数字的平方的和。

现在给定三个正整数 $k,a,b$，请求出满足 $a\le n\le b$ 且 $k\times \operatorname{f}(n)=n$ 的 $n$ 的个数。

对于 $100\%$ 的数据，$1\le k,a,b\le 10^{18}$，$a\le b$。

## 思路

1.	模拟函数 $\operatorname{f}(n)$ 对一个数的操作过程。
2.	重复枚举可能的值，累加答案。

### 方案一：纯暴力枚举

令 $n$ 的值从 $a$ 到 $b$ 进行枚举，累加可能值的个数。

但是根据数据范围：$1\le k,a,b\le 10^{18}$，$a\le b$，所以 TLE 是不可避免的。


### 方案二：优化
由题意得：$\operatorname{f}(n)$ 中，$n$ 的取值范围在 $a$ 和 $b$ 之间，令 $a$ 取最小值，$b$ 取最大值时， $n$ 的值最大，极限取值为：$10^{18}-1=99999999999999999$，此时的 $\operatorname{f}(n)$ 的值为 $9^2\times18=1458$。

为方便计算，得出公式：

由题意 $k\times \operatorname{f}(n)=n$

因为两数相等，则每一位相等。

所以 $\operatorname{f}(k\times \operatorname{f}(n))=\operatorname{f}(n)$。

由 $1$ 到 $1458$ 模拟 $\operatorname{f}(n)$ 即可，循环条件为 $\operatorname{f}(n) \times k \le b$。

但是，最后个数会多计算 $\operatorname{f}(n)<a$ 时的一些数，所以，令满足 $\operatorname{f}(n) \le a-1$ 时 $ans$ 逐个减一。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,a,b,sum,ans;
long long f(long long x){
    long long ans=0;
    while(x!=0){
        ans+=(x%10)*(x%10);
        x/=10;
    }
    return ans;
}
int main(){
    cin>>k>>a>>b;
    for(int i=1;i<=1458&&i*k<=b;i++){
        if(f(i*k)==i){
            ans++;
        }
    }
    for(int i=1;i<=1458&&i*k<=a-1;i++){
        if(f(i*k)==i){
            ans--;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_Evergarden_ (赞：1)

### [原题传送门](https://www.luogu.com.cn/problem/P5991)

------------
## 题意

对于一个正整数 $n$，定义 $f(n)$ 为它在十进制下的每一位数字的平方和。

现给出三个正整数 $k,a,b$，求在 $a$ 与 $b$ 之间的所有数中满足 $k$ $\times$ $f(n) = n$ 的个数。

## 思路

### 方法1：

从 $a$ 枚举到 $b$，用函数 $f$ 枚举，并将它们加起来。

当然，TLE 是避免不了的，我们考虑更好的方法。

### 方法2：

数据范围：$1\le k,a,b\le 10^{18}$，也就是说，$n$ 最大为 $10^{18}$，那么要使每一位数字平方和最大，$n$ 为 $10^{18} - 1$，此时函数值为 $9^2$ $\times$ $18=1458$。

为了方便计算，我们可以简化一下式子：

$k \times f(n) = n$

可得出：$f(k \times f(n)) = f(n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long//记得开longlong

using namespace std;

const int N = 1e5 + 10;

int k, a, b, ans;

int work(int n) {
    int tot = 0;
    while(n != 0) {//若分离完成，就跳出
        int b = n % 10;//分离出它的最后一位
        tot += b * b;//加上每一位数字的平方和
        n /= 10;//抛去最后一位
    }
    return tot;//返回总值
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);//读入优化
    cin >> k >> a >> b;
    for(int i = 1; i <= 1458 && i * k <= b; ++ i) {//先枚举1到b符合的值
        if(work(i * k) == i) {//如果满足就加一
            ans ++;
        }
    }
    for(int i = 1; i <= 1458 && i * k < a; ++ i) {//再减去不在a到b区间的符合的值
        if(work(i * k) == i) {//如果满足就减一
            ans --;
        }
    }
    cout << ans;
    return 0;
}
```


---

## 作者：封禁用户 (赞：1)

# 原题：[[PA2015]Równanie](https://www.luogu.com.cn/problem/P5991)


# 一、分析

$∵1\le k,a,b\le 10^{18}$；可以得出 $f(n)$ 的最大值为 $f(999999999999999999)=9^2*18=1458$。

我们可以从 $1$ 至 $1458$ 枚举 $f(n)$ 的值

又 $∵k*f(n)=n$

$∴f(k*f(n))=f(n)$

所以很容易暴力枚举求解。

先算 $f(n)$ 的值：

```cpp
ll f(ll n){
	ll ans=0;
	do{
		ans+=(n%10)*(n%10);
	}while(n/=10);
	return ans;
}
```
# 二、code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll k,a,b,i,ans;
ll f(ll n){
	ll ans=0;
	do{
		ans+=(n%10)*(n%10);
	}while(n/=10);
	return ans;
}
int main(){
	scanf("%lld%lld%lld",&k,&a,&b);
	for(i=1;i<=1458&&i*k<=b;i++)
		if(f(k*i)==i)ans++;
	for(i=1;i<=1458&&i*k<a;i++)
		if(f(k*i)==i)ans--;
	printf("%lld\n",ans);
	return 0；
}
```

---

## 作者：skyskyCCC (赞：1)

**前言。**

- 题意：[题意传送门](https://www.luogu.com.cn/problem/P5991)。
- 方法：一是纯正式暴力，二是数学式暴力。

**分析。**

方法一：纯正式暴力枚举。

但是看到 $1 \le k,a,b \le 10^8$ 时，我们发现，如果数据够大，那么纯暴力是过不了的，但是如果优化一下，也许能卡过去，不过我也没有试过，毕竟此题需要更优的暴力。

代码就不放了。

方法二：数学式暴力枚举。

一个巧妙（？）的思路。  

众所周知，一个正整数，该正整数越大，那么其平方也就越大，表达为：  
如果 $a<b(0<a,b)$ 时，那么 $a^2<b^2$ 的式子成立。

分析其最大值，以减少枚举的数量。

可知 $n$ 可以为 $999999999999999999$ 的最大数。

因为 $9^2=18$ 且 $9$ 的数量为 $18$ 个，那么 $f(999999999999999999)=18 \times 81=1458$ 即 $f(n)$ 的最大值为 $1458$。

确定好枚举范围，就可以愉快地推式子了：  
又题意可知：  
数必须满足 $k \times f(n)=n$ 的关系。  
那么根据[等式的性质](https://baike.baidu.com/item/%E7%AD%89%E5%BC%8F/3517693)可以推出：  
$f(k \times f(n))=f(n)$。  
这样，我们就可以开始暴力枚举了！

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
using namespace std;
long long k,a,b,sum,ans1,ans2;
long long f(long long x){//f(n)
    long long ans=0;//ans是它十进制下每一位数字的平方的和。
    while(x){
        ans+=(x%10)*(x%10);
        x/=10;//一直拆分。
    }
    return ans;//返回。
}
int main(){
    cin>>k>>a>>b;
    for(int i=1;i<=1458;i++){
        if(i*k>b){//已经超出了最大值b。
            break;
        }
        if(f(i*k)==i){//开始统计f(f(i)*k)=f(i)的数量。
            ans1++;//ans1代表从1到b的符合题意的n的数量。
        }
    }
    for(int i=1;i<=1458;i++){
        if(i*k>a-1){//已经超出了最大值。
            break;
        }
        if(f(i*k)==i){
            ans2++;//ans2代表从1到a-1的符合题意的n的数量。
        }
    }
    cout<<ans1-ans2<<"\n";//ans1-ans2代表从a到b中符合题意的n的数量。
    return 0;
}
```
**后记。**

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_xiaxii (赞：1)

#  [题意传送门](https://www.luogu.com.cn/problem/P5991)
# 题意分析：

 对于一个正整数 $n$ ，定义 $\operatorname{f}(n)$ 为它十进制下每一位数字的平方的和。

现在给定三个正整数 $k,a,b$，请求出满足 $a\le n\le b$ 且 $k\times \operatorname{f}(n)=n$ 的 $n$ 的个数。

## 思路1

从 $a$ 到 $b$ 暴力枚举 $n$，这样显然会时间超限：
```cpp
#include <bits/stdc++.h>
using namespace std;

long long k,a,b;
int cnt;

long f(int x)
{
    long sum=0;
    while(x!=0)
    {
        sum+=(x%10)*(x%10);
        x/=10;
    }
    return sum;
}

int main()
{
    
    cin>>k>>a>>b;
    for(int i=a;i<=b;i++)
    {
        if(i%k==0)//缩短时间（但是看起来没什么必要了
        {
            if(f(i)*k==i)
            {
                cnt++;
            }
        }
    }
    cout<<cnt;
    return 0;
}
```
预计得分:[18(TLE)](https://www.luogu.com.cn/record/83806982)。

## 思路二

从数据范围中我们可以知道 $1\le k,a,b\le 10^{18}$，因为 $n\le b$
，所以 $n$ 最大值为 $1000000000000000000$，但是考虑到是每一位的平方之和，所以 $\operatorname{f}(n)$ 最大值为 $\operatorname{f}(999999999999999999)=9^{2}\times 18=1458$。

$\because k\times f(n)=n$  
$\therefore f(k\times f(n))=f(n)$

我们知道了数据范围，将推导的公式代入代码，这能大大节约我们的时间：

```cpp
#include <bits/stdc++.h>
#define ll long long//将所有数据类型换成long long

using namespace std;

ll k,a,b;//定义全局变量是个好习惯
int cnt;//使用cnt对答案计数

ll f(ll x)//定义f(ll x)函数对数进行拆分
{
    ll sum=0;
    while(x!=0)
    {
        sum+=(x%10)*(x%10);
        x/=10;
    }
    return sum;
}

int main()
{
    
    cin>>k>>a>>b;//读入数据
    for(int i=1;i<=1458&&i*k<=b&&i*k>=a;i++)
    {
        if(f(i*k)==i)//调用函数判断是否成立
        {
            cnt++;//对成立的个数进行计数
        }
    }
    
    cout<<cnt;//输出cnt
    return 0;//圆满结束~~
}
```
预计得分:[100](https://www.luogu.com.cn/record/83808296)。

本[蒟蒻](https://www.luogu.com.cn/user/728002)的第一篇题解。

---

## 作者：wangyi_c (赞：1)

## 题意分析

设 $f(n) $ 表示正整数 $n$ 在十进制下每位数字的平方之和，求在 $ a$ 到 $b$ 范围内，满足 $k \times f(n)=n$ 的 $n$ 有多少个。

## 思路讲解

首先，看到那珂怕的数据规模：$1 \le a,b \leq 10^{18}$，就能知道暴力绝对过不去，要想更简单的方法。

可以先找枚举范围：$n$ 的最大值为 $999999999999999999$，因为每个数位上尽量大，平方后之和才会最大，所以 $f(n)$ 的最大值为 $18\times 9^2 =1458$。

然后就可以快乐推式子了：
$$\because k\times f(n)=n$$
$$\therefore f(k\times f(n))=f(n)$$

得出以上所有结论，足够我们解决这道题目了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define n 1458
using namespace std;
int k,a,b;
int check(int x){//检验函数
	int sum=0;
	while(x){//分解数位
		int t=x%10;
		sum+=t*t;
		x/=10;
	}
	return sum;
}
int work(int x){
	int ans=0;
	for(int i=1;i<=n;i++){//枚举1到1458之间所有可能的数
		if(i*k>x) break;//超过就退出
		if(check(i*k)==i) ans++;//满足条件计数器就加1
	}
	return ans;
}
signed main(){
	cin>>k>>a>>b;
	cout<<work(b)-work(a-1);//用前缀和的方法妙求a到b之间的数量
	return 0;
}
```
此算法时间复杂度很低，足以[通过此题了](https://www.luogu.com.cn/record/78666260)。

谢谢观看。

_THE END_

By wangyi

---

## 作者：highscore (赞：1)

审核大大求过

看到这道题还没人写题解，我来第一发；

由于 $ a,b<=10^{18} $; 可以得出 $ f(n) $ 最大值为 

$ f(999999999999999999)=81*18=1458 $

所以我们可以枚举  $ f(n) $ 的值域；

因为 $ k*f(n)=n $ ;

所以 $ f(k*f(n))=f(n) $ 

就可以判定了；
```cpp
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
LL k,a,b;
LL calc(LL x){//判断是否可行
	LL res=0;
	while(x){
		LL tt=x%10;
		res+=tt*tt;
		x/=10;
	}
	return res;
}
LL solve(LL x){
	LL res=0;
	for(int i=1;i<=1458;i++){//枚举答案
		if(i*k>x) break;
		if(calc(i*k)==i) res++;
	}
	return res;
}
int main(){
	scanf("%lld%lld%lld",&k,&a,&b);
	cout<<solve(b)-solve(a-1);	
}
```

---

## 作者：cdhh (赞：0)

看了看 $a$ , $b$ 的数据范围，一个一个枚举不可能过得了所以我们来看看 $n$  。

 $ n $ 的最大值是 $ 999999999999999999 $ ，所以 $f(n)$ 的最大值就是每位数的平方之和，得到 $\max(f( n )) = 1458$ 。

再根据公式 $k \times \ f( n ) = n$ 

推出 $f(k\times f(n))=f(n)$
再逐步枚举即可推出答案。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define n 1458
using namespace std;
int k,a,b;
int find(int x)
{
	int sum=0;
	while(x)
	{
		int t=x%10;
		sum+=t*t;
		x/=10;
	}
	return sum;
}
int anser(int x)
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(i*k>x)
		break;
		if(find(i*k)==i)
		ans++;
	}
	return ans;
}
signed main()
{
	cin>>k>>a>>b;
	cout<<anser(b)-anser(a-1);
	return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，一看这 $1\le k,a,b\le10^8$ 的数据范围，就知道：暴力，绝对不可能。

不过，我们还可以这么操作。

$k\times f(n)=n$ 中，$f(n)$ 代表 $n$ 的十进制下每一位数字的平方的和。显然，每个数位越大，$f(n)$ 就越大。

但是 $f(n)$ 最大能达到多少？只有 $1458$。

因为，当 $n=999999999999999999$（即 $18$ 个 $9$）时，每个数位最大。但此时 $f(999999999999999999)=9\times9\times18=1458$，所以 $f(n)$ 最大也只能达到 $1458$。

我们再将所求的式子转换一下：

$$\because k\times f(n)=n$$

$$\therefore f(k\times f(n))=f(n)$$

这下，我们就可以暴力枚举 $f(n)$ 的所有可能值了！

### 二、完整代码

```cpp
#include<cstdio>
long long k,a,b;
long long calculate(long long num)//计算f(n)。
{
	long long result=0;
	while(num)
	{
		result+=(num%10)*(num%10);
		num/=10;
	}
	return result;
}
long long get_total(long long max_num)
{
	long long result=0;//可能数量。
	for(long long i=1;i<=1458;i++)//这里的i其实指的是f(n)的所有可能。
	{
		if(k*i>max_num)//已经超出了最大值。
		{
			break;
		}
		else
		{
			if(calculate(i*k)==i)//计算f(k*f(n))是否等于f(n)。
			{
				result++;
			}
		}
	}
	return result;//返回结果。
}
int main()
{
	scanf("%lld%lld%lld",&k,&a,&b);
	printf("%lld\n",get_total(b)-get_total(a-1));
	//get_total(b)代表从1到b的符合题意的n的数量，get_total(a-1)代表从1到a-1的符合题意的n的数量，get_total(b)-get_total(a-1)就是代表从a到b的符合题意的n的数量。
	return 0;
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

