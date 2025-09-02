# PolandBall and Hypothesis

## 题目描述

PolandBall is a young, clever Ball. He is interested in prime numbers. He has stated a following hypothesis: "There exists such a positive integer $ n $ that for each positive integer $ m $ number $ n·m+1 $ is a prime number".

Unfortunately, PolandBall is not experienced yet and doesn't know that his hypothesis is incorrect. Could you prove it wrong? Write a program that finds a counterexample for any $ n $ .

## 说明/提示

A prime number (or a prime) is a natural number greater than $ 1 $ that has no positive divisors other than $ 1 $ and itself.

For the first sample testcase, $ 3·1+1=4 $ . We can output $ 1 $ .

In the second sample testcase, $ 4·1+1=5 $ . We cannot output $ 1 $ because $ 5 $ is prime. However, $ m=2 $ is okay since $ 4·2+1=9 $ , which is not a prime number.

## 样例 #1

### 输入

```
3
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
```

### 输出

```
2```

# 题解

## 作者：tZEROちゃん (赞：4)

直接从1开始枚举不就行了...

思路如下：

1.先定义一个判断是不是质数的函数
```
int pd(int n)
{
	if(n==1)return true;
	if(n==2)return false;
	for(int i=2;i*i<=n;i++)
		if(n%i==0)return true;
	return false;
}
```
2.从1开始枚举，可以直接使用
`for(int i=1;;i++)`
进行枚举

3.判断i是否满足要求，调用函数，如果满足，就直接输出i并且break或return 0

```
for(int i=1;;i++)
	{
		if(pd(n*i+1))
		{
			cout<<i;
			return 0;
		}
	}
```

```cpp
#include <bits/stdc++.h>
using namespace std;
int pd(int n)
{
	if(n==1)return true;//特判
	if(n==2)return false;
	for(int i=2;i*i<=n;i++)
		if(n%i==0)return true;
	return false;
}//判断是不是素数
int main()
{
	long long n;
	cin>>n;
	for(int i=1;;i++)
	{
		if(pd(n*i+1))//按照题目里的公式判断
		{
			cout<<i;
			return 0;//找到了，return
		}
	}//枚举
	return 0;
}
```


---

## 作者：tangyifei009 (赞：1)

> 做题时未想到特例，~~愚蠢地~~采用逐一枚举质数方法。
```cpp
    #include<iostream>
    #include<cstdio>
    #include<cmath>
    using namespace std;
     
    int prime[1000]={2, 3, 5, 7, 11, 13, 17, 19};
    int cnt = 7;
     
    bool is_prime(int x);
     
    int main()
    {
        int n, ans;
        scanf("%d", &n);
        for(int i = 21; i <= 1000; i++)
        {
            if(is_prime(i)) 
                prime[++cnt] = i;
        }
        
        for(int i = 1; i <= 1000; i++)
        {
            if(!is_prime(n*i+1))
            {
                printf("%d", i);
                return 0;
            }
        }
    }
     
    bool is_prime(int x)
    {
        int e = sqrt(x);
        bool flag = 1;
        for(int i = 0; prime[i] <= e; i++)
        {
            if(x % prime[i] == 0) 
            {
                flag = 0; 
                break;
            }
        }
        return flag;
    }
```


---

## 作者：xsI666 (赞：0)

我们可以发现，当n>2时，n·(n-2)+1=(n-1)·(n-1)，因此，输出n-2即可。

如果n<=2，我们可以发现：

	当n=2时，2·4+1=9不是质数，输出4即可；
    
    当n=1时，1·3+1=4不是质数，输出3即可。

至此，此题就被我们解决了！

AC代码：
```cpp
#include <bits/stdc++.h>//万能头文件

using namespace std;//使用标准名字空间

inline int read()//快速读入
{
	int f=1,x=0;
	char c=getchar();

	while(c<'0' || c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}

	while(c>='0' && c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}

	return f*x;
}

int n,m;

int main()
{
	n=read();//输入n
	
	if(n>2)//如果n>2
	{
		printf("%d",n-2);//就输出n-2
		
		return 0;
	}
	
	if(n==2)//如果n=2
	{
		printf("4");//就输出4
		
		return 0;
	}
	
	if(n==1)//如果n=1
	{
		printf("3");//就输出3
		
		return 0;
	}
	
	return 0;//结束
}
```


---

