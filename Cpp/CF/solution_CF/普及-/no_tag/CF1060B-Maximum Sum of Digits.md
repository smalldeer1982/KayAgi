# Maximum Sum of Digits

## 题目描述

You are given a positive integer $ n $ .

Let $ S(x) $ be sum of digits in base 10 representation of $ x $ , for example, $ S(123) = 1 + 2 + 3 = 6 $ , $ S(0) = 0 $ .

Your task is to find two integers $ a, b $ , such that $ 0 \leq a, b \leq n $ , $ a + b = n $ and $ S(a) + S(b) $ is the largest possible among all such pairs.

## 说明/提示

In the first example, you can choose, for example, $ a = 17 $ and $ b = 18 $ , so that $ S(17) + S(18) = 1 + 7 + 1 + 8 = 17 $ . It can be shown that it is impossible to get a larger answer.

In the second test example, you can choose, for example, $ a = 5000000001 $ and $ b = 4999999999 $ , with $ S(5000000001) + S(4999999999) = 91 $ . It can be shown that it is impossible to get a larger answer.

## 样例 #1

### 输入

```
35
```

### 输出

```
17
```

## 样例 #2

### 输入

```
10000000000
```

### 输出

```
91
```

# 题解

## 作者：sahmaykf (赞：3)

## 题意
给定n，要求一对数a，b使得a+b=n，且a与b分离数位的和最大。n<=1e12
## 做法一
从1扫到n/2，保证了正确性但显然是超时的。
## 做法二
通过打表，我们可以发现，左边的数一定有len-1个9。len为n的位数。

且a=b-n，则a+1=b-n+1，如果右边进位，答案肯定会变小，如果不进位，则答案一致。

所以我们只要管左边就行了。

只要左边的9最多，并且使得左边的第len位上的数字x加上右边不会导致进位，答案即为最大。

比赛时脑抽去枚举了第len位,还是trl

下面是代码

```cpp
#include<cstdio>
#include<cstring>
long long max(long long a,long long b)
{
	return a>b?a:b;
}
int main()
{
	long long n;
	scanf("%I64d",&n);
	long long ans=-1;
	long long len=0,count=n;
	while(count)
	{
		len++;
		count/=10;
	}//求出n的位数
	long long p=1;
	for(long long i=1;i<len;i++)p*=10;//求出10的len-1次方
	for(long long a=p-1;a<=(p-1)*10+9&&a<=n;a+=p)//p-1为len-1个9
	{										//保证a在n范围内
		long long b=n-a;
		long long sum=0;
		while(b)
		{
			sum+=b%10;
			b/=10;
		}//分离b的数位
		ans=max(ans,sum+(len-1)*9+a/p);//取最大答案
	}
	printf("%I64d",ans);
	return 0;
} 
```

---

## 作者：alex_liu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1060B)

# 思路：

贪心：疯狂取 $9$ 就行了，保证数码值最大。

只要把 $a$ 给处理完，那么 $b$ 就是 $n-a$ 了。

详细的解释请看代码注释。

# AC CODE:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x,b,val=0;//m 和 x 都是 n 的替身，防止 n 的值改变； val 是 a 和 b 的数码值 
signed main(){
	cin>>n;
	m=x=n;//复制 
	while(x>=10)x/=10;//求出 n 的首位 
	int a=x-1;//想一下为什么 a 要先赋值为 x-1（思考题） 
	while(m){//求出 a 的最优解 
		m/=10;
		a=a*10+9;
	}
	a/=10;//多乘的要除回来 
	b=n-a;//b=n-a 
	while(a){
		val+=a%10;
		a/=10;
	}//a 的数码和 
	while(b){
		val+=b%10;
		b/=10;
	}//b 的数码和 
	cout<<val<<endl;//输出 
	return 0;//结束程序 
}
```
# 思考题答案：
为了保证 $a$ 和 $b$ 的数码和最大，就需要让 $a$ 和 $b$ 的位数最大，那么 $x-1$ 就能保证 $a$ 与 $b$ 的位数与 $n$ 相同或者小一位。

---

## 作者：lhjy666 (赞：1)

多弄点9就好了
另外的减一下
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll n,t=0;
	scanf("%lld",&n);
	ll w=0;
	while(1)
	{
		w=w*10+9;
		t+=9;
		if(w>n)
		{
			t-=9;
			w=w-9;
			w=w/10;
			break;
		}
	}
	ll k=n-w;
	while(1)
	{
		t+=k%10;
		k=k/10;
		if(k==0) break;
	}
	printf("%lld",t);
	return 0;
}
```

---

## 作者：cecilia_sankta (赞：1)

T2:

两遍过

贪心，多选⑨就行了

尝试证明：

设最优解中a第i位为$a_i$,b第i位为$b_i$(a>b);N第i为记为$N_i$

若$\forall i\in\{i |a_i\neq 9\}$，则将$a_i$改为9

若不退位则照常，退位就会多


```cpp
#include<bits/stdc++.h>
#define int		long long
using namespace std;
int N;
int S(int s){
	int val=0;
	while(s){
		val+=s%10;
		s/=10;
	}
	return val;
}
int gettop(int M){
	while(M>=10)M/=10;
	return M;
}
signed main(){
	cin>>N;
	int M = N;
	int a=gettop(N)-1,b=1;
	while(M){
		a=a*10+9;
		M/=10;
	}
	a/=10;
	b=N-a;
	cout<<S(a)+S(b)<<endl;;
}
```

---

## 作者：ly618x (赞：0)

一、题意

现在给出一个数字 $n$ ，找出一个数对 $a,b$ ，要求他们的和为 $n$，并且他们的每一位的和加起来最大。

二、思路

为了和最大，我们优先选 $9$ ，如果再选一个就 $a\ge n$ 时就停下，然后 $b\gets n-a$ ，再输出他们每一位的和即可。

三、代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int ans(int x)
{
	int anss=0;
	while(x!=0)
	{
		anss+=x%10;
		x=x/10;
	}
	return anss;
}
signed main()
{
	int n;
	int cnt=0;
	int sum=0;
	cin>>n;
	while(sum*10+9<n)
	{
		cnt++;
		sum=sum*10+9;
	}
	cout<<ans(sum)+ans(n-sum);
	return 0;
}
```

---

## 作者：zwy__ (赞：0)

### 题意
记 $S(x)$ 为 $x$ 的各位数字之和。有一整数 $n$，求一对自然数 $a,b$，令 $S(a)+S(b)$ 最大，并且满足 $a+b=n$。
### 思路
1. 直接做，枚举其中一个数，但题目说 $1 \le n \le 10^{12}$，所以必定会超时，但可以水一点分。
2. 贪心。我们可以进行思考，怎样能使数字和最大？其实只需要在数上面尽可能多9就可以了。为什么呢？因为0的数字和是最小的，我们要保证数之间不能存在进位，所以我们先构造出最大的一个数，另外一个数就是 $n-$ 我们构造出来的这个数。如果记 $n$ 的位数为 $m$，组成的最大数应该这样组成。

 $\qquad \quad \quad \quad \,\,\,\,\, n$ 的最高位 $-1 \times 10^m+99\cdots9$，$9$ 的个数为 $m-1$。
### 代码
[开了完隐，用原站上的记录](https://codeforces.com/contest/1060/submission/199389009)
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,t,sum;
int main()
{
	cin>>n;
	t=n;
	while(t>=10)t/=10;
	x=t-1;
	t=n/10;
	while(t>0)
	{
		x*=10;
		x+=9;
		t/=10;
	}
	y=n-x;
	while(x>0)
	{
		sum+=x%10;
		x/=10; 
	}
	while(y>0)
	{
		sum+=y%10;
		y/=10;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Sternenlicht (赞：0)

思路：贪心。

因为想要数码值最大，就必须让 $a$ 不停地取 $9$，取到不能取为止。取多少个 $9$ 呢？设 $n$ 有 $k$ 位，则最多有 $k-1$ 个 $9$ 可以给 $a$，剩下部分给 $b$ 就行了。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

int main(){
	LL n=read(),ans=0,maxn=0;
	do{
		maxn=maxn*10+9;ans+=9;
	}while(maxn<=n);//不停取9 
	maxn=(maxn-9)/10;ans-=9;//多取了一次，扣回去 
	LL rest=n-maxn;//剩余部分 
	do{
		ans+=rest%10;
		rest/=10;
	}while (rest);//加上剩余部分的各个位之和 
	write(ans);//输出结果 
	return 0;
}
```

---

## 作者：EthanOI (赞：0)

## 前言
写这篇题解有三个目的：加咕值、纪念橙名的第一天，给深中高三学长加油！
## 前置芝士
学过小学奥数的应该都知道，加法运算中，如果两个一位数相加大于 $10$ ，就需要进位，即前面一位的结果 $+1$ 。
## 做法
通过这个知识点，我们下面来考虑 $S(a)+S(b)$ 与 $S(a+b)$ 的大小。

首先，如果在 $a+b$ 的过程中不存在进位，那么每一位仅仅是 $a$ 与 $b$ 中的数位相加，因此 $S(a+b)=S(a)+S(b)$ 。现在考虑每一次进位，设这一位上 $a$ 与 $b$ 的数码分别为 $x$ 与 $y$ ，则进位后 $a+b$ 的这一位是 $x+y-10$ ，而其后面一位的结果 $+1$ ，由此可知，每次进位 $S(a+b)$ 在不进位基础下 $-9$ ，换句话说，就是进位次数越多，相加后的数码和就越小。

回到原题，设 $a+b$ 过程中进了 $k$ 位，有 

$S(n)=S(a+b)=S(a)+S(b)-9k$ 

从而得到：

$\boxed{S(a)+S(b)=S(n)+9k}$

由于 $S(n)$ 的值固定，要是 $S(a)+S(b)$ 最大，必然有 $k$ 最大。因此只需要考虑一个数表达为两个数之和最多进的位数。设 $n$ 为 $t$ 位数。当末位不为 $9$ 时，如果首位 $\leqslant3$ ，则最多进行 $t-1$ 次进位；如果首位 $\geqslant 4$ ，则最多进 $t$ 位。当末位为 $9$ 时，每种情况比前一种少 $1$ （这应该很好理解，因为最后一位不能进位），这样思路就出来了。
## 代码
按照思路写的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, first, last, d, s;
int main()
{
	cin >> n;
	last = n % 10;
	while (n)
	{
		if (n < 10) first = n;
		s += n % 10;
		d++;
		n /= 10;
	}
	//cout << first << " " << d << " " << s;
	/*若末位为9*/
	if (last == 9)
	{
		if (first <= 2) cout << s + 9 * (d - 2);
		else cout << s + 9 * (d - 1);
	}
	else
	{
		if (first <= 2) cout << s + 9 * (d - 1);
		else cout << s + 9 * d;
	}
}
```
交了之后，[第一个数据](https://www.luogu.com.cn/record/77060188)都过不去，恶心的是 CF 不能看评测结果。随手试了下 $0$ ，输出 $-9$ ，好像一位数要特判

代码就不贴了，因为[………](https://www.luogu.com.cn/record/77060531)

看来思路和 AC CODE 之间还是有差距的，又试了试 $39$ ，得到 $21$ ，因为第一位和最后一位 $9$ 挨在一起，所以两位数也要特判 

---

