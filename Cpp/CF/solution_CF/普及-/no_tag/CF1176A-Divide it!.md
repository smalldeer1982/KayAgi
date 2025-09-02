# Divide it!

## 题目描述

给你一个整数$n$

你可以对这个数进行任意多次（可以为$0$）如下的操作

1. 如果$n$是$2$的倍数，把$n$替换成$\frac{n}{2}$
2. 如果$n$是$3$的倍数，把$n$替换成$\frac{2n}{3}$
3. 如果$n$是$5$的倍数，把$n$替换成$\frac{4n}{5}$

举个例子，你可以通过操作$1$把$30$变成$15$，用操作$2$把$30$变成$20$，用操作$3$把$30$变成$24$

你的任务是找到把$n$变成$1$的最少操作次数，或者说不可能做到

你需要回答$q$个独立的询问

## 样例 #1

### 输入

```
7
1
10
25
30
14
27
1000000000000000000
```

### 输出

```
0
4
6
6
-1
6
72
```

# 题解

## 作者：shenxinge (赞：3)

# 这道题目实在是~~太水~~了！
- 首先是这个拆分，例如30可以写成30=2 * 3 * 5，也就是任何一个可以拆分的数都可以整除2,3,5，所以不是2,3,5的倍数的数一定都输出-1；（但我的方法比较慢）
### 接下来就是模拟
以下是关键代码，按照题目来模拟：
```cpp
int ans=0;
	while(1)
	{
		if(k==1)
		{
			cout << ans << endl;
			break;
		}
		ans++;
		if(k%2==0) k/=2;
		else if(k%3==0) k=k*2/3;
		else if(k%5==0) k=k*4/5;
		else
		{
			cout << "-1" << endl;
			break;
		}
	}
```
### 然后就是连接代码，一个一个的输出；
```cpp
#include<iostream>
using namespace std;
int main(){
	int n;
	cin >> n;
	for(int i=0;i<n;i++)
	{
		long long k=0;
		cin >> k;
		int ans=0;
		while(1)
		{
			if(k==1)
			{
				cout << ans << endl;
				break;
			}
			ans++;
			if(k%2==0) k/=2;
			else if(k%3==0) k=k*2/3;
			else if(k%5==0) k=k*4/5;
			else
			{
				cout << "-1" << endl;
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：Kubic (赞：2)

开门见山：

操作$1$：去掉当前数中的$1$个质因数$2$

操作$2$：将当前数中的质因数$2$增加$1$个，去掉当前数中的$1$个质因数$3$

操作$2$：将当前数中的质因数$2$增加$2$个，去掉当前数中的$1$个质因数$5$

所以我们可以得出，如果$n$中含有除了$2,3,5$以外的质因数，就一定变不成$1$

接下来考虑统计答案

质因数$2$：用$1$次操作$1$，共$1$次

质因数$3$：用$1$次操作$2$，$1$次操作$1$，共$2$次

质因数$5$：用$1$次操作$3$，$2$次操作$1$，共$3$次

所以，每遇到一个质因数$2$，就将答案加上$1$，每遇到一个质因数$3$，就将答案加上$2$，每遇到一个质因数$5$，就将答案加上$3$

时间复杂度：$<q*O(log_2n)$

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int T;ll n,ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;scanf("%lld",&n);
		while(!(n%2)) n/=2,++ans;//质因子2
        while(!(n%3)) n/=3,ans+=2;//质因子3
        while(!(n%5)) n/=5,ans+=3;//质因子5
		if(n!=1) ans=-1;//无法变成1
        printf("%lld\n",ans);
	}
}
```

---

## 作者：Lips (赞：1)

# 一道很好的贪心~~大水~~题！

**思路：** 对于任意一个正整数$x$，作如下处理：

- 如果$x\bmod2==0$，便将$x$更新为：$\frac{x}{2}$

- 如果$x\bmod3==0$，便将$x$更新为：$\frac{2x}{3}$

- 如果$x\bmod5==0$，便将$x$更新为：$\frac{4x}{5}$

- 如果$x$都不能除尽$2,3,5$则直接输出$-1$

- 如果$x==1$则跳出循环并输出最后答案$\text{ans}$

**注：每进行一次操作，便要将$\text{ans}$更新为：$\text{ans+1}$**

~~这么一道水题~~也没什么好讲的，直接上$Code$吧！

```cpp
#include<cstdio>
using namespace std;
int q,ans;
long long n;
int main()
{
    scanf("%d",&q);
    while(q--)
    {
    	scanf("%lld",&n),ans=0;
    	while(1)
    	{
    		if(n==1){printf("%d\n",ans);break;}
	    	if(n%2!=0&&n%3!=0&&n%5!=0){printf("-1\n");break;}
			if(n%2==0){n/=2;ans++;continue;}
			if(n%3==0){n=2*n/3;ans++;continue;}
			if(n%5==0){n=4*n/5;ans++;continue;}
		}
	}
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

# 题意
  有 $ q $ 次操作  ,  给出一个整数 $ n $ ,  每次操作可以执行以下操作  : 
  
 $ 1 . $ 如果 $ n $ 是 $ 2 $ 的倍数 , 那么将 $ n $ 替换成 $ \frac{n}{2} $
 
 $ 2 . $ 如果 $ n $ 是 $ 3 $ 的倍数  ,  那么将 $ n $ 替换成 $ \frac{2n}{3} $ 
 
 $ 3 . $ 如果 $ n $ 是 $ 5 $ 的倍数  ,  那么将 $ n $ 替换成 $ \frac{4n}{5} $
 
 求把 $ n $ 变为 $ 1 $ 的最少操作次数，若无法变为 $ 1 $ 则输出 $ -1 。 $
 
# 思路 #

  此题只需根据题意模拟即可  。  
  
  $ 1 . $ 如果 $ n $ 除得尽 $ 2 $ , 那么将 $ n \div 2 $ ,  并且将次数 $ +  1 。 $ 
  
  $ 2 . $ 如果 $ n $ 除得尽 $ 3 $ , 那么将 $ n \times 2 \div 3 $ ,  并且将次数 $ +  1 。 $  
  
  $ 3.  $ 如果 $ n $ 除得尽 $ 5 $ , 那么将 $ n \times 4 \div 5 $ ,  并且将次数 $ +  1 $ 。  
  
  $ 4 . $ 如果 $ n $ $ = $ $ 1 $  ，  那么结束此次操作  ,  输出次数。 
  
  $ 5 . $ 如果 $ n $ 无法除尽 $ 2 $ 、 $ 3 $  、 $ 5 $   ,  那么输出 $ -1 $ 。
  
# 代码 # 

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q;
int main(){
	scanf("%lld",&q);
	while(q--){
		long long sum=0;
		scanf("%lld",&n);
		while(1){
			if(n==1){printf("%lld\n",sum);break;}
			if(n%2!=0&&n%3!=0&&n%5!=0){printf("-1\n");break;}
			if(n%2==0)n/=2;
			else if(n%3==0)n=n*2/3;
			else if(n%5==0)n=n*4/5;
			sum++;
		}
	}
	return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

**这是一道模拟题。**

因为 $1\leq q\leq 1000$，所以不需要做优化，直接暴力模拟就能过。

在如何判定可不可能做到这一点上则是唯一需要思考一下的。但是很容易就可以发现：如果 $n$ 不是 $2,3,5$ 的倍数且不为 $1$ 的话，那么 $n$ 自然也就不能再运算，也就不能转化为 $1$ 了。

根据以上结论，我们就可以理清以下思路：
1. 如果 $n$ 已经为 $1$，那么直接输出步骤。
2. 判断 $2,3,5$ 是否能整除 $n$，并做出响应的运算。
3. 如果都不能整除，那么输出 $-1$。否则继续转到步骤 $1$。

还有很重要的一点，题目中 $1\leq n\leq 10^{18}$，所以要开 ```long long```。

代码很简单，如下
```cpp
#include<cstdio>

#define LL long long

using namespace std;

int q;

int main()
{
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		LL n;
		scanf("%lld",&n);
		int ans=0;
		while(true)
		{
			if(n==1)			//步骤 1 
			{
				printf("%d\n",ans);
				break;
			}
			ans++;
			if(n%2==0) n=n/2;	//步骤 2 
			else if(n%3==0) n=(2*n)/3;
			else if(n%5==0) n=(4*n)/5;
			else				//步骤 3 
			{
				printf("-1\n");
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：zilingheimei (赞：0)

蒟蒻来写题解了

先看题目：

[CF1176A Divide it!](https://www.luogu.com.cn/problem/CF1176A)


------------

思路如下：

1. 先判断$n$是不是等于$1$。

```cpp
if(n[i]==1){
	cout<<ans<<endl;
	break;//记得结束，不然会死循环
}
```


2. 再判断$n$是否满足题目的要求：被$2$或$3$或$5$整除。

3. 如果整除就按题目的处理方法：

- 如果$n$是$2$的倍数，把$n$替换成$\frac{n}{2}$。	
 
- 如果$n$是$3$的倍数，把$n$替换成$\frac{2n}{3}$。
 
- 如果$n$是$5$的倍数，把$n$替换成$\frac{4n}{5}$。

```cpp
if(n[i]%2==0){
	n[i]=n[i]/2;
	ans++;
}
else if(n[i]%3==0){
	n[i]=n[i]*2/3;
	ans++;
}
else if(n[i]%5==0){
	n[i]=n[i]*4/5;
	ans++;
}
```


4. 如果不是就说明无法变成$1$，直接输出$-1$。

```cpp
else{
	cout<<-1<<endl;
	break;//记得结束，不然会死循环
}
```


------------
代码的核心前面放了，这里就不放了(

---

## 作者：EuphoricStar (赞：0)

## 简单的贪心 + 模拟

根据题意模拟即可，每次替换就 $ans$++。如果循环中出现 $n$ 不能被 $2,3$ 或 $5$ 整除的情况，直接输出 $-1$ 并接着下一轮循环。

**注意开 $long$ $long$**

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int q;
long long n;

int main()
{
    ios::sync_with_stdio(0); // 输入输出优化
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        cin >> n;
        int ans = 0;
        while (n != 1)
        {
            if (n % 2 && n % 3 && n % 5) // 无法被 2,3,5 整除
            {
                cout << -1 << endl;
                goto NEXT;
            }
            if (n % 2 == 0) n = n / 2, ans++;
            if (n % 3 == 0) n = n * 2 / 3, ans++;
            if (n % 5 == 0) n = n * 4 / 5, ans++;
        }
        cout << ans << endl;
        NEXT: ;
    }
    return 0;
}
```


---

## 作者：Franka (赞：0)

### **题目**
如翻译。
### **思路**
将这个数**分解质因数**，如果这个数的质因数**不是**$2$、$3$、$5$其中的一个，则输出$-1$，否则**输出分解质因数的次数**。

但是这里还要注意一点：$1\leq n\leq 10^{18}$，也就是说，n得开$long$ $long$（$int64$）。

### **代码**
只贴核心代码，也就是分解质因数的代码。
```pascal
 readln(x);//读入x
 s:=0;//s清零
 p:=false;//反证法
 while x<>1 do//当x不为1时
  begin
   if x mod 2=0 then//如果是2的倍数
    begin
     x:=x div 2;//算出x现在的值
     inc(s);//次数加一
    end else
    if x mod 3=0 then//如果是3的倍数
     begin
      x:=x*2 div 3;//算出x现在的值
      inc(s);//次数加一
     end else
     if x mod 5=0 then//如果是5的倍数
      begin
       x:=x*4 div 5;//算出x现在的值
       inc(s);//次数加一
      end else
      begin
       p:=true;//反过来
       break;//退出这个循环
      end;
  end;
 if p then writeln(-1)//如果有别的因数。输出-1
  else writeln(s);//否则输出次数
```


---

## 作者：TRZ_2007 (赞：0)

## Solution

这是一道数学题啊！！~~给点对他的尊重好吗？~~  

这题刚刚看到的时候，心里的第一个反应就是$dfs$——毕竟这是A题嘛！复杂度也不大，就是$\Theta(3^n.q)$（逃……）。结果看到了这样一个东西：$1\le n \le 10^{18},1\le q \le 1000$。

内心是自闭的，于是开始想正解……

通过仔细观察题目，发现要求最小的步数，于是我们就尽量通过最少的步数让$n$的值最小，所以若$n | 5$时，就把$n$变成$\dfrac{4}{5}n$，$n|3$时，就把$n$变成$\dfrac{2}{3}n$，当$n|2$时，就把$n$变成$\dfrac{1}{2}n$。

然后照着这个思路敲代码就好啦，复杂度大约是$\Theta(q)$，但是常数巨大，但是还能过。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

int q;

int main() {
	scanf("%d",&q);
	while(q--) {
		long long cnt = 0,n;
		scanf("%lld",&n);
		while(n % 5 == 0) {
			n = n / 5 * 4;
			cnt++;
		}
		while(n % 3 == 0) {
			n = n / 3 * 2;
			cnt++;
		}
		while(n % 2 == 0) {
			n /= 2;
			cnt++;
		}
		if(n == 1) printf("%d\n",cnt);
			else puts("-1");
		cnt = 0;
	}
}
```

---

## 作者：C20212724杨京朝 (赞：0)

附上~~并不严谨的~~数学证明

------------
一共可进行三种操作，则我们可以分别讨论：

1.如果n是5的倍数，把n替换成4/5n。因为n%5==0，所以n/5是个正整数，n/5*4必然是个偶数。

2.如果n是3的倍数，把n替换成2/3n。因为n%3==0，所以n/3是个正整数，n/3*2必然是个偶数。

3.如果n是2的倍数，把n替换成n/2。

结论：如果一个数可以进行1，2操作则必然可以进行3操作

------------
我们不难发现n%5==0，n%2==0时，操作顺序不影响结果，原因：2，5互质，一奇一偶
同理，n%3==0，n%2==0时，操作顺序不影响结果，原因同上。

//这里补一下上面的证明，n进行操作1之后会变为一个偶数，n进行操作2以后还是并不影响n%5==0.

那么n%3==0,n%5==0时呢？以15为例：15 / 3 * 2=10,15 / 5 * 4=12,证明同上

结论：操作顺序并不影响最终结果

------------
最后贴上代码：
```cpp
#include <cstdio>
#define LL long long
inline long long read() {
    int x = 0,f = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
    while (c <='9' && c >='0') {x = x * 10 + c - '0';c = getchar();}
    return x * f;
}
int main() {
	int n;
	scanf("%d",&n);
	for(register int i = 1;i <= n;i ++) {
		LL x,tot = 0;
		scanf("%lld",&x);
		while(x % 5 == 0) x = x / 5 * 4,tot ++;
		while(x % 3 == 0) x = x / 3 * 2,tot ++;
		while(x % 2 == 0) x /= 2,tot ++;
		if(x == 1) printf("%lld\n",tot);
		else printf("-1\n");
	}
	return 0;
}
```


---

