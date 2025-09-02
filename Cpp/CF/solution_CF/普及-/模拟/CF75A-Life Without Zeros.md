# Life Without Zeros

## 题目描述

Can you imagine our life if we removed all zeros from it? For sure we will have many problems.

In this problem we will have a simple example if we removed all zeros from our life, it's the addition operation. Let's assume you are given this equation $ a+b=c $ , where $ a $ and $ b $ are positive integers, and $ c $ is the sum of $ a $ and $ b $ . Now let's remove all zeros from this equation. Will the equation remain correct after removing all zeros?

For example if the equation is $ 101+102=203 $ , if we removed all zeros it will be $ 11+12=23 $ which is still a correct equation.

But if the equation is $ 105+106=211 $ , if we removed all zeros it will be $ 15+16=211 $ which is not a correct equation.

## 样例 #1

### 输入

```
101
102
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
105
106
```

### 输出

```
NO
```

# 题解

## 作者：Scherzo (赞：13)

# CF75A Life Without Zeros

## 题目分析

本体核心在于一个函数，功能是将一个整数中每一位上的零都去掉，方法很多，这里介绍栈的做法。

## 栈 (会的人自行跳过)

栈是一种数据类型，具体如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/tzwmdmgs.png) 

图片来源 百度百科

这张图已经很清楚了，我再解释一遍。

一个栈就像一个数组，然而，栈比数组更特殊，他就像一个弹夹，加入元素时只能加到栈顶，弹出元素时也只能弹出栈顶。

一下是栈的一些常用用法.

- 声明(以int类型为例)

```cpp
#include <stack>

stack<int>s;
```

以上代码声明了一个栈s。

------------


- 将一个数压入栈顶

```cpp
s.push(a);
```

以上代码将a压入了栈s的栈顶。

------------

**将s的栈顶元素弹出**

```cpp
s.pop();
```

以上代码弹出了s的栈顶元素。

------------

**获取s的栈顶元素**

```cpp
int a=s.top();
```

以上代码将s的栈顶元素存储到了a中。

------------

**栈是否为空**

```cpp
bool flag=s.empty();
```

以上代码将栈s是否为空存储到了变量flag中。

## 解决题目

首先我们考虑如何实现去掉一个整数中的0。

### 函数

```cpp
stack<int>s;

int removeZero(int num)
{
	while (num>=1)
	{
		if (num%10!=0)
		{
			s.push(num%10);
		}
		num/=10;
	}
	int ans=0;
	while (!s.empty())
	{
		ans=ans*10+s.top();
		s.pop();
	}
	return ans;
}
```

以上函数实现了将一个数的中的所有零去掉，下面是函数的具体实现过程。

#### 第一部分

```cpp
while (num>=1)
{
	if (num%10!=0)
	{
		s.push(num%10);
	}
	num/=10;
}
```
这是一个每一次判断数字 $num$ 的最后一位是否为零，不是则入栈，然后去掉最后一位，直到将 $num$ 除到零为止。

也就是说，现在栈中存储的，是由栈底向栈顶依次排列的，没有零的，$num$ 的每一位。

那现在，只需要一个变量 $ans$ 来把栈的元素合到一起啦。

#### 第二部分

```cpp
int ans=0;
while (!s.empty())
{
	ans=ans*10+s.top();
	s.pop();
}
return ans;
```

最后返回的，就是没有零的 $num$ 啦

把主函数写完，就完成啦

~~这都写出来了，主函数再写不出来就有点说不过去了吧~~

### ~~int mian~~ 主函数部分

```cpp
int main()
{
	int a,b;
	int ans=0;
	scanf("%d%d",&a,&b);
	ans=a+b;
	if (removeZero(a)+removeZero(b)==removeZero(ans))
	{
		cout<<"YES";
	}
	else
	{
		cout<<"NO";
	}
	return 0;
}
```

不讲了，自行理解

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;

stack<int>s;

int removeZero(int num)
{
	while (num>=1)
	{
		if (num%10!=0)
		{
			s.push(num%10);
		}
		num/=10;
	}
	int ans=0;
	while (!s.empty())
	{
		ans=ans*10+s.top();
		s.pop();
	}
	return ans;
}

int main()
{
	int a,b;
	int ans=0;
	scanf("%d%d",&a,&b);
	ans=a+b;
	if (removeZero(a)+removeZero(b)==removeZero(ans))
	{
		cout<<"YES";
	}
	else
	{
		cout<<"NO";
	}
	return 0;
}

```

这是本蒟蒻的第二篇题解，dalao点个赞再走吧

---

## 作者：Kdlyh (赞：7)

# 直接用%处理去0操作即可
```cpp
#include <cstdio>
long long a,b,c,ta,tb,tc,sa,sb,sc;
int main()
{
    scanf("%lld %lld",&a,&b),c=a+b;
    while(a)
        ta=(a%10 == 0) ? ta : ta*10+a%10,a/=10;//每次取末尾的数字判断，如果不是0就加上去
    while(b)
        tb=(b%10 == 0) ? tb : tb*10+b%10,b/=10;//同理
    while(c)
        tc=(c%10 == 0) ? tc : tc*10+c%10,c/=10;//同理
    while(ta)
        sa=(ta%10 == 0) ? sa : sa*10+ta%10,ta/=10;//因为经过第一次处理完的数的顺序是反的，所以要再转成正的。
    while(tb)
        sb=(tb%10 == 0) ? sb : sb*10+tb%10,tb/=10;//同理
    while(tc)
        sc=(tc%10 == 0) ? sc : sc*10+tc%10,tc/=10;//同理
    if(sa+sb == sc)
        printf("YES");
    else
        printf("NO");
}
```


---

## 作者：时律 (赞：4)

出 人 心 裁 的 解 法

~~既然这题那么水，当然要用一些奇怪的方法过，题解才可以过审核啊~~

采用了`stringstream`

`stringstream`可以实现任意类型的转换。

本题中先用`stringstream`将数字转化成字符串，然后删0，再返回转回的数字


```
#include<bits/stdc++.h>
using namespace std;
int num(int u)
{
	stringstream ss;string a,b;int ans;
	ss.clear();
	ss<<u;ss>>a;//把u输给ss，然后把ss输给a
	for(int i=0;i<a.size();i++)
		if(a[i]!='0')
			b+=a[i];
	ss.clear();//注意用过的流会保存原有的数据，要先清空
	ss<<b;ss>>ans;
	return ans;
}
int main()
{
	int a,b;
	cin>>a>>b;
	if(num(a)+num(b)==num(a+b))
		puts("YES");
	else
		puts("NO");
}
```

---

## 作者：FCB_Yiyang2006✈ (赞：2)

# 又是蓝（难）水题！
我提交了3次才过，有许多细节要注意。
## 思路
#### STEP1
a，b用CHAR读入。
#### STEP2
转化为LONG LONG，并去掉零，算出c。
#### STEP3
将c的0除去。
#### STEP4
判断是否相等。
## 细节

### 1 要开 long long
### 2 c去0之前要先倒序。

c++代码（奇葩注释。。。）

```cpp
#include<bits/stdc++.h>//万能脑袋
using namespace std;
char a[25],b[25];//字符串读入
long long a1,b1,c1;//a1,b1c1不去0
long long a2,b2,c2;//a2,b2,c2去0
int main()//主晗二叉树
{
	cin>>a>>b;
	a1=a2=a[0]-48;
	b1=b2=b[0]-48;//初始值
	for(long long i=1;i<strlen(a);i++)
	{
		a1=a1*10+a[i]-48;//不去0
		if(a[i]-48>0)
		{
			a2=a2*10+a[i]-48;//去0
		}
	}
	for(long long i=1;i<strlen(b);i++)
	{
		b1=b1*10+b[i]-48;
		if(b[i]-48>0)
		{
			b2=b2*10+b[i]-48;
		}
	}
	c1=a1+b1;
	long long c=0;
	for(long long i=c1;i>0;i/=10)
	{
		c=c*10+i%10;
	}//将c1倒序
	for(long long i=c;i>0;i/=10)
	{
		if(i%10!=0)
		{
			c2=c2*10+i%10;
		}
	}
	if(a2+b2==c2)
	{
		cout<<"YES";
	}
	else
	{
		cout<<"NO";
	}//判断
	return 0;//结束了！结束了！
} 
```
#### 可以直接复制提交AC(慎用)

---

## 作者：2x6_81 (赞：2)

妈呀，这是一道蓝题欸！吓死我了。

实际上，这题很**。

怎么做呢？楼上（或楼下）是直接检查这个数的某一位，

我和TA一样，不过用的是另一种方法，见代码：
```
#include <iostream>
#include <cstdio>
using namespace std;
const int pow10[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};//用了一下
int a,b,c,aa,bb,cc,la,lb,lc;
int main()
{
	scanf("%d%d",&a,&b);c=a+b;
	while(a>0)if(a%10!=0)aa+=(a%10)*pow10[la++],a/=10;else a/=10;
	while(b>0)if(b%10!=0)bb+=(b%10)*pow10[lb++],b/=10;else b/=10;
	while(c>0)if(c%10!=0)cc+=(c%10)*pow10[lc++],c/=10;else c/=10;
//	printf("aa = %d , bb = %d , cc = %d\n",aa,bb,cc);
	printf("%s\n",aa+bb==cc?"YES":"NO");
}
```
我们假设这一个数$a=101$

则第一次，$aa=1\text{，}a=10$

第二次，因为a%10为0，所以不在$aa$里 $aa=1\text{，}a=1$

第三次，因为a%10不是0，所以在$aa$里 $aa=11\text{，}a=0$

第四次，a=0，跳出循环。

（怎么感觉这是给C++初学者看的呢）

b与c同理。

---

## 作者：封禁用户 (赞：1)

大家好，我这个蓝名蒟蒻又来写题解啦！

这道题并不难，就是判断 去0的a + 去0的b 是否等于 去0的a+b。

下面为去0的函数：

```
int erase(int s)
{
	while(s>0)
	{
		if(s%10!=0)x=x*10+s%10;//一位一位取
		s/=10;
	}
//当然，现在的x已经去0，可是还需再次反过来：
	while(x>0)
	{
		s=s*10+x%10;
		x/=10;
	}
	return s;//最后返回s
}
```

最后，代码如下:

```
#include<iostream>
using namespace std;
int a,b,c,x;
int erase(int s)//函数
{
	while(s>0)
	{
		if(s%10!=0)x=x*10+s%10;
		s/=10;
	}
	while(x>0)
	{
		s=s*10+x%10;
		x/=10;
	}
	return s;
}
int main()
{
	cin>>a>>b;
	c=a+b;
	a=erase(a),b=erase(b),c=erase(c);//用函数分别将a，b，c去0
	if(a+b==c)cout<<"YES";//判断
	else cout<<"NO";
	
	return 0;//完美结束
}
```

---

## 作者：pipiispig (赞：1)

###高精度+判断==水题~}-->(～￣▽￣)～
```#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int f=1,x=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return f*x;
}//没什么用的快读QAQ;
int s[1000],s1[1000],s2[1000];
int main(){//主要思路就是高精度，也就是把int装换成数组呢~
	int n=read(),m=read();
	int w=n+m;
	int x=0,x1=0,x2=0;
	int cnt=1,cnt1=1,cnt2=1;
	while(w!=0){
		s[cnt++]=w%10;
		w/=10;
	}
	while(n!=0){
		cout<<n<<endl;
		s2[cnt2++]=n%10;
		n/=10;
	}
	while(m!=0){
		s1[cnt1++]=m%10;
		m/=10;
	}//其实也不算高精度，w(ﾟДﾟ)w，但是这样方便判断去零；
	for(int i=cnt-1;i>=1;i--){
		if(s[i]!=0)x=x*10+s[i];
	}
	for(int i=cnt2-1;i>=1;i--){
		cout<<s1[i];
		if(s1[i]!=0)x1=x1*10+s1[i];
	}
	for(int i=cnt1-1;i>=1;i--){
		if(s2[i]!=0)x2=x2*10+s2[i];
	}
	cout<<x<<" "<<x1<<" "<<x2<<endl;
	if(x1+x2==x){
		cout<<"YES";
		return 0;
	}
	cout<<"NO";//一个水题就做完了呢，♪(^∇^*)
}```

---

## 作者：tocek_shiki (赞：1)

又是一道恶意评分……

本人表示十分伤(kai)心

---

咳咳，下面步入正题

首先看到这题的翻译，你会发现这是一道很水的模拟

正常情况下，我们第一眼就回去想到字符串乱搞

# 但是

作者特意换了种做法~~（我绝不会告诉你是为了让这篇题解通过~~

首先我们有以下规律

假设a0c为一个整数（不是乘号，表示是数字的那个作者表示找不到

记f(a)为去除a中的0后的值

那么必有f(a0c)=a*10+c

那么我们就可以类推出来整个的转化方法了

纯空间复杂度（去除掉我的bits，for里的i等其他的）为76B

很少吧？

时间复杂度为O(log10(a)+log10(b)+log10(c))，也就是最大为O(27)，反正就是快得不得了


下面贴代码

```cpp
#include <bits/stdc++.h>
#define newline printf ("\n")
#define space printf (" ")
#define cinfalse ios::sync_with_stdio(false)
#define fread(a) freopen (a".in", "r", stdin), freopen(a".out", "w", stdout)
#define rint register int
#define For(i, a, b) for (rint i = a; i <= b; i ++)
#define Low(i, a, b) for (rint i = a; i >= b; i --)
#define FFr(i, a, b, c) for (rint i = a; i <= b; i += c)
#define FLw(i, a, b, c) for (rint i = a; i >= b; i -= c)
#define min(a, b) (a)>(b)?(b):(a)
#define max(a, b) (a)>(b)?(a):(b)
using namespace std；

int A, B, C;
int AA = 0, BB = 0, CC = 0;
int la, lb, lc;

const int pow10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}; 
int main()
{
	scanf ("%d\n%d", &A, &B), C=A+B;
	la = log10(A), lb = log10(B);
	lc = log10(C);
	for (rint i = la; i >= 0; i --)
		if (A/pow10[i]%10)
			AA = AA*10+A/pow10[i]%10;
	for (rint i = lb; i >= 0; i --)
		if (B/pow10[i]%10)
			BB = BB*10+B/pow10[i]%10;
	for (rint i = lc; i >= 0; i --)
		if (C/pow10[i]%10)
			CC = CC*10+C/pow10[i]%10;
	puts(AA+BB==CC?"YES":"NO");
    return 0;
}

```

劝你们不要抄，不然棕名或者比较蠢的直接复制CE的自己负责

---

## 作者：Cesare (赞：0)

很简单的一道题...恶意评分造就了我的第一道黑题（无奈

我的思路很简单，就是求出没去掉零的和去掉零的，然后把没去零的去零和另一个比较。

```cpp
#include <bits/stdc++.h>
#define re sort(a+1,a+n+1)
using namespace std;
typedef long long ll;

string a,b;ll sum1=0,sum2=0,ans=0,anss=0,zz=0,zone[1001],sum=0;

int main(){
    getline(cin,a);getline(cin,b);
    for(re int i=0;i<a.size();i++)
        sum1=sum1*10+a[i]-'0';
    for(re int i=0;i<b.size();i++)
        sum2=sum2*10+b[i]-'0';
    ans=sum1+sum2;sum1=sum2=0;
    for(re int i=0;i<a.size();i++)
        if(a[i]-'0')sum1=sum1*10+a[i]-'0';
    for(re int i=0;i<b.size();i++)
        if(b[i]-'0')sum2=sum2*10+b[i]-'0';
    anss=sum1+sum2;
    while(ans){if(ans%10)zone[zz]=ans%10,zz++;ans/=10;}
    for(re int i=zz-1;i>=0;i--)
        sum=sum*10+zone[i];
    if(sum==anss)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}
```
ps:不建议直接复制。

---

