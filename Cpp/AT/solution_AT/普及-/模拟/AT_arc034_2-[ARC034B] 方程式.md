# [ARC034B] 方程式

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc034/tasks/arc034_2

正整数 $ n $ に対し、$ n $ の十進表記における各桁の数の和を $ f(n) $ で表す。例えば、 $ f(123)\ =\ 1\ +\ 2\ +\ 3\ =\ 6, $ $ f(4)\ =\ 4 $ となる。

正整数 $ N $ が与えられる。等式 $ x\ +\ f(x)\ =\ N $ を満たす正整数 $ x $ を全て求めよ。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 20 $ 点分のテストケースは $ 1\ ≦\ N\ ≦\ 1000 $ を満たす。

### Sample Explanation 1

問題文で述べたように $ f(4)\ =\ 4 $ であり、 $ 4 $ 以外に題意を満たす正整数は存在しない。

### Sample Explanation 2

複数の解が存在することがある。

### Sample Explanation 3

解が存在しないこともある。

## 样例 #1

### 输入

```
8```

### 输出

```
1
4```

## 样例 #2

### 输入

```
101```

### 输出

```
2
91
100```

## 样例 #3

### 输入

```
108```

### 输出

```
0```

# 题解

## 作者：张文奕 (赞：4)

先和大家说一下数字和的概念：数字和是指一个数的各位数字相加得到的和，比如123，数字和就是1+2+3=6

n的范围是10^18，所以n的数字和最大只能是18*9=162.所以循环只需要从n-162开始至n结束。（题目很坑，我一开始把n的范围看成了1018，直接从1开始循环，结果TLE了10个点）

上代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
long long n;//n^18,不开long long会爆
int ans;
int work(long long x){//求x的数字和
    int sum=0;
    while (x){
        sum+=x%10;
        x/=10;
    }
    return sum;
}
int main(){
    scanf ("%lld",&n);
    for (long long i=n-162;i<=n;i++)//从n-162开始循环
        if (i+work(i)==n) ans++;//如果i和i的数字和之和等于n,解的总数++
    printf ("%lld\n",ans);//先输出解的总数
    for (long long i=n-162;i<=n;i++)//反正循环范围小，重复劳动也不会超时
        if (i+work(i)==n) printf ("%lld\n",i);
    return 0;
}```

---

## 作者：cyn2006 (赞：3)

**为什么没人发题解？不就是样例错了么……**

**这里纠正样例3#: **

**input:**

**108**

**output:**

**0**

一道典型的数学题QwQ

因为我们知道一个数的数字和最大不超过len*9(len表示数的位数)QwQ

于是可以确定循环下界为max(n-len*9,1)QwQ

重点在这里：为什么是max(n-len*9,1)呢?QwQ

给定f(x)=x的数字和QwQ

则有可能x<= 19*9=171 (因为n<=10^18)QwQ

所以x不能为非正整数，于是有了公式QwQ(雾)

```
for(rll i=max(n-len*9,1);i<=n;i++)
    if(f(i)+i==n) -> a[++ans]=i;
```
详见代码：(QwQ)
```
#include<bits/stdc++.h>
#define ll long long
#define Re register
#define rll Re ll//宏定义register，据说可以加快速度
using namespace std;
ll n,a[1000],ans;
inline ll max(ll x,ll y){return x>y?x:y;}
int main(){
    cin>>n;
    ll x=n,len=0;
    while(x)x/=10,len++;
    for(rll i=max(n-len*9,1);i<=n;i++){//确定下界，极大的减少了循环次数
        x=i;ll cnt=0;
        while(x)cnt+=x%10,x/=10;//计算数字和
        if(cnt+i==n)a[++ans]=i;//如果满足条件，加入数组，最后输出答案
    }
    //if(ans==0)return 0;
    //切记！不能无输出(你直接puts("0")会惊奇地过了10个点)
    cout<<ans<<endl;
    for(rll i=1;i<=ans;i++)cout<<a[i]<<endl;
    return 0;
}
```
**有那么坑的吗？谁能告诉我每个测试点的时间为什么都是1ms？？……QwQ**

**顺便说一下，我在讨论区写了翻译，dalao们可以去看看QwQ(那个叫做此题翻译的帖子)**

---

## 作者：happybob (赞：1)

这道题目`n`的范围其实是 $\large 10^{18}$。

所以暴力肯定是会 T 飞的。

那我们来想一下：

这里数字和最大是不是18个9是不是162？

那我们直接从 $\large n - 162$ 枚举不就完了？

代码：

```cpp
#include <iostream>
using namespace std;

#define int long long

inline int Digit_sum(const int& x)
{
    int tmp = x, sum = 0;
    while(tmp) {sum += tmp % 10; tmp /= 10;}
    return sum;
}

int ans[1020];

signed main()
{
    int n;
    int cur = 0;
    cin >> n;
    for(register int i = n - 162; i <= n; i++)
    {
        if(i + Digit_sum(i) == n) ans[++cur] = i;
    }
    cout << cur << endl;
    for(register int i = 1; i <= cur; i++) cout << ans[i] << endl;
    return 0;
}
```


---

## 作者：周子衡 (赞：1)

各种其他方法不讲了，这里讲一种优化

显然$f(i)\equiv i(mod 9)$，那么$i+f(i)\equiv 2\times i(mod9)$，可以直接得出$i$除以$9$的余数，从而将枚举量缩小到约$\frac{1}{9}\times 162=18$，可以很快得出答案

（关于$162$的具体来历见其他题解）

当然，本人代码稍稍放宽了一些，枚举到$200$，也是可以的

代码：

```cpp
#include<cstdio>
#include<algorithm> 

using namespace std;

long long ans[10001]={};

long long bit_sm(long long p)
{
    long long ans=0;
    while(p)
    {
        ans+=p%10;
        p/=10;
    }
    return ans;
}

int main()
{	
    long long n=0;
    int fl=0;
    scanf("%lld",&n);
    long long i=max((long long)0,n-200);
    while((i+i)%9!=n%9)
    {
		i++;
    }
    for(;i<=n;i+=9)
    {
        if(i+bit_sm(i)==n)
        {
            fl++;
            ans[fl]=i;
        }
    }
    printf("%d\n",fl);
    for(int i=1;i<=fl;i++)
    {
        printf("%lld\n",ans[i]);
    }
    
    return 0;
}
```

---

## 作者：CCF_zkskyer (赞：1)

# 这道题的数据请求加强！！！

没错，你们可能问我为什么希望数据加强，因为这样我就可以写一篇~~难度提高一点的题解~~了！！！

好的，进入正题：
### 1.题面
题目中的$N$在$20$分中的数据范围是$1$到$1000$，所以我们可以推断出$X$最大的每位数字之和为$27$（即$999$），所以就$X$本身就必须大于$1000-27=973$，因此我们可以发现我们直接从$973$开始循环就可以了。

于是经过我多次尝试（套数据），我发现，最大数据中的$N$应该不超过$10^{18}$，别看这个数大，其实时间复杂度很小：

最大数字之和是$9 \times 18=162$，因此我们总共只需要循环$162$个数就行了。

接着，每个数字找到以后，我们需要进行它的每一位数字之和，这很简单，只要每次先$mod10$，即取个位数字，然后把原数除以$10$，如此循环，直到该数为零时，结束。

但是，这道题有坑，我们得考虑$0$的情况，所以得写成$max(1,n-weishu \times 9)$，但是我们又发现$N$最大$10^{18}$，所以单纯用$max(a,b)$会$CE$，因此我们还要亲自写一个函数。


### 2.代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ri register long long //宏定义是个好东西。 
#define Max max //max还是不变。 

long long max(int a,long long b)
{
	if (a>b) return a;
	else return b;
} //重新定义的函数。 

const int maxn=100005;

long long n; //由于听他人说数据是10^18,所以用long long存。 
int ans; // ans就不需要了。 
long long ansnum[maxn]; //这个存数字的需要。 
int weishu; //这里存n的位数。 

inline long long numplus(long long num) //用来求各个位数之和。 
{
	long long sum=0; //最终答案。 
	while (num!=0)
	{
		sum+=num%10;
		num/=10;
	} //操作。 
	return sum;
}

int main()
{
    scanf("%lld",&n);
    
    long long n1=n; // 不能直接用n。 
    while(n1!=0)
    {
    	n1/=10;
    	weishu++;
	} //求n的位数。 
    
    for (ri i=max(1,n-163);i<=n;++i) //按前面的方法，只求这个范围。 
    {
    	if (i+numplus(i)==n) //如果成立。 
    	{
    		ansnum[++ans]=i; //那么存下来，并且ans++。 
		}
	}
	
	printf("%d\n",ans); //先输出ans。 
	for (ri i=1;i<=ans;++i) 
	{
	    printf("%lld\n",ansnum[i]); //再挨个输出答案。	
	}
	
	return 0;
}
```
### 3.结语
这道题不难，就是坑多，请管理员大大通过吧！！！
# 谢谢观看！！！

---

## 作者：Fengxiang008 (赞：0)

## 题意理解
数字和的概念：数字和是指一个数的各位数字相加得到的和，比如 $985$ ，数字和就是 $9+8+5=22$

$\therefore $ n的范围是 $ \begin{matrix}\underbrace{100\cdots00}\\18\end{matrix} $ ，所以 $ n $的数字和 $ q $ 取最大时为 $\begin{matrix}\underbrace{99\cdots99}\\18\end{matrix}$ ，  
此时数字和为 $18 \times 9 = 162$.  
$\because$ 循环只需从 $ 162 $ 即可.

## 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
int check(long long x)
{
    int sum=0;
    while(x)
	{
        sum+=x%10;
        x/=10;
    }
    return sum;
}
int main()
{
    cin>>n;
    for (long long i=n-162;i<=n;i++)
    {
        if (i+check(i)==n)
		{
			ans++;
		}
	}
    cout<<ans<<endl;
    for (long long i=n-162;i<=n;i++)
    {
        if (i+check(i)==n)
		{
			printf ("%lld\n",i);
		}
	}
    return 0;
}
```



---

## 作者：Jiyuu_no_Tsubasa (赞：0)

这道题很坑，我做了好几遍才过。

首先，数据范围有误：

+ 洛谷的体面中写的是 $n\le 1018$；
+ AtCoder 中的却是 $n\le 10^{18}$；

因此相信不少大佬莫名其妙的 WA 与 TLE。

然后得知了正确数据范围的我们开始做题。

$10^{18}$ 的数据范围直接枚举显然无法接受，

因此我们需要进行一些优化。

具体怎么优化呢？我们可以从题中的数字和这一概念入手。

ps. 数字和即一个数各位数字的和

因为 $n\le 10^{18}$，因此数字和最大为 $9\times 18$，

也就是 $999999999999999999$ 的情况。

所以我们可以从 $n-9\times18$ 开始枚举，求出答案。

这样既节省了时间，又不会影响答案的正确性。

代码如下：

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int f(ll x){
    int sum=0;
    ll v=x;
    while(v)
        sum+=v%10,v/=10;
    return sum;
}
ll ans[9*18+10];
int main(){
    ll n; cin>>n;
    int cnt=0;
    for(ll i=n-18*9;i<n;i++)
        if(i+f(i)==n)
            ans[++cnt]=i;
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++)
        cout<<ans[i]<<endl;
    return 0;
}

```

---

## 作者：Pkixzx (赞：0)

看到这道题后，我发现我对数字和这个概念不是很清楚，其实数字和就是**这个数每一个数字的和**。

举个栗子，233的数字和就是2+3+3=8。

我原来的思路是从1循环到n，求出这个数的数字和，然后用这个数加上数字和后，判断是不是等于n，如果是就输出这个数。

但是这道题有个坑点，就是数据是**10^18**次方，如果单纯循环一定会TLE的。

怎么办呢？因为数据最大是10^18次方，也就是说，最大的数的数字和是**18*9=162**，取近似值为200。这样这道题就可以AC了。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
long long jia(long long n)//求数字和
{
	long long t=0;
	while(n)
	{
		t+=(n%10);
		n/=10;
	}
	return t;
}
int main()
{
   long long n,i,j,k,m,x,y,t=0,min,max;
    cin>>n;
    for(i=n-200;i<=n;i++)
    {
    	if(i+jia(i)==n)//判断，如果符合条件，计数器t++
    	t++;
	}
	cout<<t<<endl;//输出个数
	for(i=n-200;i<=n;i++)
	{
		if(i+jia(i)==n)
		cout<<i<<endl;//输出符合条件的数
	}
    return 0;
}
```


---

## 作者：cq_loves_Capoo (赞：0)

这题应该不算很难，不过倒是有很多坑，所以还是讲讲我的做法吧。    
1.先从n-1000左右的地方开始循环（或许有少次数的循环，但如果是不想算太久的话，1000应该是比较稳定的了），如果这个数符合要求，那么答案+1。  
2.输出答案后，再次跑一遍循环（这是我的做法，大家可以用数组装好后输出），判断是否符合要求，如果符合则输出。  
上代码时间到！
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<stdio.h>//头文件
using namespace std;
int n,ans;
int f(int x)//求出x和x的所有数字和
{
	int sum=x;
	for(int i=x;i>=1;i/=10) sum+=i%10;//数位分离并相加
	return sum;
}
int main()
{
	scanf("%d",&n);
	for(int i=n-1018;i<=n;i++)
		if(f(i)==n) ans++;//循环并累加
	printf("%d\n",ans);
	for(int i=n-1018;i<=n;i++)//再跑一遍循环
		if(f(i)==n) printf("%d\n",i);//如果符合输出
}
```
这个代码交上去，发现WA了14个点，仔细一看，原来是数据范围是long long！  
修改后的代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<stdio.h>
#define ll long long
using namespace std;
ll n,ans;//全部变量什么的都用long long（我的习惯）
ll f(ll x)
{
	ll sum=x;
	for(ll i=x;i>=1;i/=10) sum+=i%10;
	return sum;
}
int main()
{
	scanf("%lld",&n);
	for(ll i=n-1018;i<=n;i++)
		if(f(i)==n) ans++;
	printf("%lld\n",ans);
	for(ll i=n-1018;i<=n;i++)
		if(f(i)==n) printf("%lld\n",i);
}
```



---

