# Duff in Love

## 题目描述

## 问题描述

如果不存在一个数 $ a (a>1)$ ，使得 $ a^2 $ 是 $ n $ 的约数，我们就称 $ n $ 是一个可爱的数。

给出一个正整数 $ n $ ，在 $ n $ 的所有约数中，寻找最大的可爱的数。

## 样例 #1

### 输入

```
10
```

### 输出

```
10
```

## 样例 #2

### 输入

```
12
```

### 输出

```
6
```

# 题解

## 作者：b6e0_ (赞：5)

[CF题面传送门](https://codeforces.com/contest/588/problem/B) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF588B) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF588B)

可以看出，可爱的数就是所有质因子的指数都是 $1$ 的数。所以，设 $n=p_1^{k_1}p_2^{k_2}\cdots p_m^{k_m}$，答案就是 $p_1p_2p_3\cdots p_m$。对 $n$ 做质因数分解即可。注意为了保证复杂度，循环条件一定要写成 $i^2\le n$ 而不是 $i\le n$，最后剩下的 $n$ 假如不是 $1$ 那就再将答案乘上 $n$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//开long long
signed main()
{
	int n,i,ans=1;
	cin>>n;
	for(i=2;i*i<=n;i++)
		if(n%i==0)
		{
			ans*=i;//累乘答案
			while(n%i==0)
				n/=i;//除掉i这个质因子
		}
	if(n>1)//假如大于1表示剩下的还是一个质数
		ans*=n;
	cout<<ans;
	return 0;
}
```
时间复杂度为 $\mathcal O(\sqrt n)$

---

## 作者：SqrtSecond (赞：1)

可以看出，所谓“可爱的数”就是没有约数是平方数的数。

也就是说，他不同的质因数只有$0$或$1$个。

所以，将原数判断一下，如果相同质因数有$2$个及以上，那么将原数除以那个质因数即可。

于是，我写了这样一篇代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin>>n;
	int k=sqrt(n);
	for(int i=2;i<=k;++i)
	{
		while(!(n%(i*i)))n/=i;
	}
	cout<<n;
	return 0;
}
```
先别走！

当我把它提交上去时，第$10$个点WA了！

于是我重新看了一下数据范围：$10^{12}$！

不服气的我又写了第二篇代码：

```
#include<bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	cin>>n;
	long long k=sqrt(n);
	for(int i=2;i<=k;++i)
	{
		while(!(n%(i*i)))n/=i;
	}
	cout<<n;
	return 0;
}
```
然而，这次代码又RE了。

后来我又自己测试了一下，发现了即使是$i$也要开$long long$。

呃……

最终，我还是AC了。

完整代码如下（带注释）：

```
#include<bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	cin>>n;
	long long k=sqrt(n);//质因数的上限 
	for(long long i=2;i<=k;++i)
	{
		while(!(n%(i*i)))n/=i;//除去质因数 
	}
	cout<<n;
	return 0;//华丽结束 
}
```
当然也可以这个样子：

```
#include<bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	cin>>n; 
	for(long long i=2;i<=sqrt(n);++i)
	{
		while(!(n%(i*i)))n/=i;//除去质因数 
	}
	cout<<n;
	return 0;//华丽结束 
}
```
好了，写完了$\textcolor{white}{qwq}$

---

## 作者：StudyingFather (赞：1)

首先对 $ n $ 进行质因数分解，设分解的结果为 $ n = {p_1}^{x_1} {p_2}^{x_2} \ldots $ ，根据定义， $ p_1 p_2 \ldots $ 一定是最大的可爱的数。（特别地，当所有质因子的次数均为1时， $ n $ 就是最大的可爱的数）

```cpp
#include <iostream>
using namespace std;
int main()
{
 long long n,ans=1,cur=2;
 cin>>n;
 long long n1=n;
 while(n1!=1)
 {
  if(cur*cur>n)
  {
   ans*=n1;
   break;
  }
  bool flag=false;
  while(n1%cur==0)n1/=cur,flag=true;
  if(flag)ans*=cur;
  cur++;
 }
 cout<<ans<<endl;
 return 0;
}
```

---

## 作者：MattL (赞：0)

[原题链接](http://codeforces.com/problemset/problem/588/B) & [洛谷链接](https://www.luogu.com.cn/problem/CF588B)

㵘

---

**读题：**

原题：
>如果不存在一个数 $ a (a>1)$ ，使得 $ a^2 $ 是 $ n $ 的约数，我们就称 $ n $ 是一个可爱的数。

>给出一个正整数 $ n $ ，在 $ n $ 的所有约数中，寻找最大的可爱的数。

设 $n={p_1}^{a_1} \times {p_2}^{a_2} \times {p_3}^{a_3} \times  \cdots \times{p_m}^{a_m} (p_1,p_2,p_3,\cdots,p_m$均为质数)

由于如果有 $a_i \geq 2$ ，则 $n$ 定有约数 ${p_i}^2$ ，所以对于所有的 $a_i$ 都要 $=1$ 

所以答案 $ans=p_1 \times p_2 \times p_3 \times  \cdots \times p_m $

然后这题就成了分解质因数。

---

**代码：**

忠言：十年 OI 一场空，忘开```long long``` 见祖宗。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans=1;//注意ans=1，不然答案为0
int main()
{
    cin>>n;
    for(long long i=2;i*i<=n;i++)//注意i*i<=n 的时间小优化
        if(n%i==0)
        {
            ans*=i;
            while(n%i==0)//有可能指数不为1
                n/=i;
        }
    cout<<ans*n<<endl;//注意要*n，不然有剩下的会没乘上
    return 0;
}
```

---

## 作者：一只大龙猫 (赞：0)

这是一篇 **Python** 题解，文末也会放上 C++ 代码。

首先，一个可爱的数中每个质因数的次数**都小于 $2$。**

为什么？

假设一个数中质因数 $p$ 的次数大于等于 $2$，那么 $p^2$ 也是这个数的因数，那这个数就不是可爱的数了。

设 $n=p_1^{x_1} \times p_2^{x_2} \times p_3^{x_3} \times ... \times p_m^{x_m}$，因为我们刚才分析过一个可爱的数中每个质因数的次数都小于 $2$，所以在 $n$ 的因数中，最大的可爱的数即为 $p_1 \times p_2 \times p_3 \times ... \times p_m$。

代码如下：

Python

```python
def check(x):
    i=2
    while i*i<=x:
        if x%i==0:
            return 0
        i=i+1
    return 1
a=int(input())
ans=1
while a!=1 and check(a)==0:
    now=2
    while a%now!=0:
        now=now+1
    ans=ans*now
    while a%now==0:
        a=a//now
ans=ans*a
print(ans)
```

C++

```cpp
#include<iostream>
using namespace std;
long long a,ans=1;
long long check(long long x){
	long long i=2;
	while(i*i<=x){
		if(x%i==0){
			return 0;
		}
		i++;
	}
	return 1;
}
signed main(){
	cin>>a;
	while(a!=1&&check(a)==0){
		long long now=2;
		while(a%now!=0){
			now++;
		}
		ans*=now;
		while(a%now==0){
			a/=now;
		}
	}
	ans*=a;
	cout<<ans;
}
```

代码中，`ans`为答案，`now`为当前`a`最小的质因数，`a=a//now`（Python）和`a/=now;`（C++）的作用是消去`now`这个质因数。

这里做了一点小优化：当`a`为质数时，一个一个找`a`最小的质因数的耗时会很大（Python 会直接超时）。`check()`函数的作用是判断一个数是否为质数，当`a`为质数时，`a`的最小的质因数即为`a`，且只有这一个质因数，所以可以直接将`ans`乘上`a`后输出。

---

## 作者：Nozebry (赞：0)

## $Problems$
如果不存在一个数 $a$ $($ $a>1$ $)$ , 使得 $a^2$ 是 $n$ 的约数，我们就称 $n$ 是一个可爱的数。

给出一个正整数 $n$ $($ $1\le n \le 10^{12}$ $)$ ，在 $n$ 的所有约数中，寻找最大的可爱的数。
## $Answer$
这道题的翻译不是特别能说明这道题是要我们干什么，但其实不难发现，其实就是叫我们求 $n$ 的质因数之积。

为什么说是求 $n$ 的质因数之积呢？因为质数不可能是任意一个数的平方，而合数却有可能成为某个数的平方。

例如 $4$ 是 $2^2$，而题目说是**不存在一个数**$a$，但这个合数 $4$ 存在了一个数 $2$，不符合题意，所以合数是不可以算进去的。

这样一来题目就十分简单了，只需判断 $i$ 是否为 $n$ 的因数，再把 $i$ 再 $n$ 内全部清除，直到 $i$ 已经大于 $n$ 了。
## $Code$
```pascal
var
    n,i,ans:int64;
begin
    readln(n);
    i:=2;ans:=1;
    while (i<=trunc(sqrt(n))) do
    begin
        if n mod i=0 then//在这段程序里，任何一个能被n整除的数都会是质数，因为从2开始，每个质数的倍数都会从n里删去
        begin
            ans:=ans*i;
            while n mod i=0 do n:=n div i;//这里就是体现了为什么不需要判断 i 是不是质数的部分，因为在这里，i 的小于 n 的所有倍数都会被整除去掉
        end;
        inc(i);
    end;
    writeln(ans*n);//注意，最后 n 自己本身也需要乘进去
end.
```

---

