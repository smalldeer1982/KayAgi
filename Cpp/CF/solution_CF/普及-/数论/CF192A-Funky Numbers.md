# Funky Numbers

## 题目描述

今年最时髦的数字是三角数（即可表示为 $\frac{k(k+1)}{2}$ 的数字，其中 $k$ 是正整数），而今年最酷的数字是那些可表示为两个三角数之和的数字。

著名的嬉皮士安德烈崇拜一切酷而时髦的东西。但不幸的是，他不擅长数学。给定一个数字 $n$，请帮助他确定这个数字是否能够由两个三角形数的和来表示。（两个三角数可以相同）

## 样例 #1

### 输入

```
256
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
512
```

### 输出

```
NO
```

# 题解

## 作者：Eaoci (赞：3)

我看了其他题解，都是O(nlogn)的

这里我有一种O(n)的做法

首先，题目要求为两个三角数之和，可表示为n=k1*(k1+1)/2+k2*(k2+1)/2
  
我的想法是，去枚举k1，用n-k1求出k2*(k2+1)/2,然后我们就可以~~抄高斯求和~~推一个式子

k2*（k2+1)/2=x  (x即为n-k1)

k2^2+k2=2x

k2^2+k2+1/4=2x+1/4

(k2+1/2)^2=2x+1/4

k2+1/2=sqrt(2x+1/4)

k2=sqrt(2x+1/4)-1/2

然后判断k2是否为整数即可
  
上代码

```
#include<iostream>
#include<cmath>
using namespace std;
long long n,ans,m;
int main(){
	cin>>n;
	m=floor((sqrt(n*2+0.25)-0.5));//如上文高斯求和求范围 
	for(int i=1;i<=m;i++){
		long long cnt=n-i*(i+1)/2;//求n-k1 
		long long cntt=floor((sqrt(cnt*2+0.25)-0.5));//求k2 
		if(cntt*(cntt+1)/2==cnt&&cnt!=0){//显然两个三角数都不可为零 
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";//全都不是即没有 
	return 0;
}
```


---

## 作者：WCG2025 (赞：3)

	首先看这道题的数据范围
	(1<=n<=10^9）
	十分的大
	至少都得nlogn才过的了
	那么，我们可以尝试二分答案


------------

	  首先，题目要求为两个三角数之和，可表示为2*n=k1*(k1+1)+k2*(k2+1).
      就可以有这么一种想法，我去枚举k1，然后二分寻找满足的k2，
      并且这道题也算仁慈，只用输出yes和no，这样就可以了
      具体看代码注释
 ```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
ll A,B;
ll mid;
ll flag;
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=sqrt(2*n);i++)//A必须小与根号下2*n，不然
    //B就无法成立了
    {
        A=i*(i+1);
        ll l=1,r=sqrt(2*n);
        while(l<=r)
        {
            mid=(l+r)/2;//二分常规操作
            B=mid*(mid+1);
            if(A+B>2*n)
            r=mid-1;		
            if(A+B<2*n)
            l=mid+1;
            if(A+B==2*n)
            {
                flag=1;//打标记，避免重复
                break;
            }
        }	
        if(flag==1)
        break;
    }
    if(flag==1)
    cout<<"YES"<<endl;
    else
    cout<<"NO"<<endl;
    return 0;
}
```
	这道题真的可以，二分答案很简单，适合二分入门（codeforces七十一个测试点A了很壮观

---

## 作者：SqrtSecond (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF192A)

$1e9$的数据，马上可以想到用二分。

则如果$n$可以表示为两个三角数

那么存在一组正整数$[a,b]$，使得$n=\frac{a(a+1)}{2}+\frac{b(b+1)}{2}$

即$2n=a(a+1)+b(b+1)$

此时易知$a(a+1)$与$b(b+1)$皆为正整数且$≤n$

所以在$a(a+1)≤2n$时枚举$a$，再二分查找$b$即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l,r,mid,ans;
int main()
{
	cin>>n;n*=2;//n先乘上2，以便后面计算 
	for(long long i=1;i*(i+1)<=n;++i)//枚举a 
	{
		l=1;r=100000;//区间尽量开大点 
		while(l<=r)
		{
			mid=l+(r-l)/2;
			ans=i*(i+1)+mid*(mid+1);//二分模板 
			if(ans>n)r=mid-1;
			if(ans<n)l=mid+1;
			if(ans==n)
			{
				puts("YES");
				return 0; 
			}
		}
	}
	puts("NO");
	return 0;//华丽结束 
}
```



---

## 作者：Insouciant21 (赞：1)

UPDATE: 修改一些问题

这个题目咋一看无从下手 $n<=10^9$

于是转向三角形数的公式 $ \dfrac{k(k+1)}{2} $

设 $ a=\dfrac{k(k+1)}{2} $

即可配方得到 
$$
b=8a+1
=8\times\dfrac{k(k+1)}{2}+1
=4k(k+1)=4k^2+4k+1
=(2k+1)^2
$$

设两个三角形数的和为 $N$

即 $N=a_{1}+a_{2}$

按上面方法配方得 

$$
8N+2=8\times(a_{1}+a_{2})+2=(8a_{1}+1)+(8a_{2}+1)=b_{1}+b_{2}
$$

即可得 $8N+2$ 必为两个奇数的平方和，即证明 $N$ 能由两个三角形数相加得到只需证明 $8N+2$ 是两个奇数的平方和。

又因为 $k>0$ 所以 $2k+1$ 最小值为 $3$ 。

故AC代码如下

``` cpp
#include <bits/stdc++.h>

using namespace std;

long long num;

int main() {
    scanf("%lld", &num);
    long long n = 8 * num + 2;
    int sqt = sqrt(n);
    for (long long i = 3; i <= sqt; i += 2) { // 最小可用奇数为3
        long long p = n - i * i;
        double c = sqrt(p); 
        if (p > 1 && c == int(c) && int(c) % 2 == 1) { // 2k + 1 > 1
            puts("YES");
            return 0;
        }
    }
    puts("NO");
    return 0;
}
```



---

## 作者：Lucifer_Bartholomew (赞：1)

# ~~二分答案~~
枚举a，二分找b
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	int nn=n;
	n*=2;
	bool flag=0;
    for(int i = 1;i*i<=n;++i)
	{
        int fsum=i*(i+1)>>1,r=sqrt(n),l=i,sum=0,mid=(r+l)>>1;
        while(l<=r)
		{
            mid=(r+l)>>1;
            sum=mid*(mid+1)>>1;
            if(fsum+sum<nn)l=mid+1;
            else if(fsum+sum>nn)r=mid-1;
            else
			{
                flag=1;
                break;
            }
        }
    }
    if(flag)puts("YES");
    else puts("NO");
	return 0;
}
```
~~我是蒟蒻~~

---

