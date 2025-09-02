# Working for the World

## 题目描述

s先生代替他的因为感冒而休息的朋友，负责了某个巨大的”SNS”的维修。 他根据朋友留下的纸条，在”SNS”登录时，需要输入密码。密码是给出的数字的质因数的最大值。 但是不擅长数学的s先生不知道质因数是什么。所以，你的工作是为了s先生，制作出从给出的数字中来寻求密码的程序。

# 题解

## 作者：zhanghzqwq (赞：3)

## 挑战最短代码

看着大佬们都用很长的素数筛法，蒟蒻我在这里介绍一种比较短的方法。

这种方法就是从2开始筛，只要发现n%i=0,i就不变，n除以i。因为比较大的合数肯定是较小的素数乘以一个数。这样的话，筛到最后n就肯定是那个最大的素数。其中的奇妙，你们自己去体会吧！时间复杂度是$O(sqrt(n))$，很快。

上代码：
```cpp
#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	while(n){//判断是否不为零
		for(int i=2;i*i<=n;i++){
			if(n%i==0){
				n/=i;
				i--;//一定要减一
			}
		}
		cout<<n<<endl;输出
		cin>>n;
	}
	return 0;//华丽的结束
} 
```


---

## 作者：曼恩薄荷 (赞：3)


  不得不吐槽一下洛谷的评分机制（~~被我秒的题怎么可能会是蓝题~~）鹅且这个题的数据也十分的水（有多水泥萌自己体会一下）
   
   
咳咳：我的做法是，从一到n进行枚举，枚举到n的因子就暴力判断另一个因子是否为质数，完了（没错就完了QwQ）



上代码：



```cpp
#include<bits/stdc++.h>
using namespace std;



bool isp(int x)//暴力筛素数 
{
	for(int i=2;i<=sqrt(x);i++)
		if(x%i==0) return 0;
	return 1;
}

int main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(!n) break;
		for(int i=1;i<=n;i++)
			if(n%i==0)//如果是n的因子且另一个因子为质数，直接输出就完了√ 
				if(isp(n/i))
				{
					printf("%d\n",n/i);
					break;
				}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

一道模板题

双倍经验：[P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

你只要知道这个：

```cpp
int pd(int x) {
	for(int i=2; i*i<=x; ++i)
		if(x%i==0) return 0;
	return 1;
}
```

网上讲解欧拉筛、线性筛的很多，阔以自己去康康。

按照普通的做题思路，TLE一片。

$TLE$ $code$


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,y;
int pd(int x) {
	for(int i=3; i*i<=x; ++i)
		if(x%i==0) return 0;
	return 1;
}
int main() {
	while(cin>>n) {
		if(n==0) return 0;
		for(int i=n; i>=2; --i) {
			if(n%i==0) {
				if(i==2) {
					printf("2\n");
					break;
				} else {
					if(i%2==0) continue;
					else if(pd(i)) {
						printf("%d\n",i);
						break;
					}
				}
			}
		}
	}
	return 0;
}
```


优化办法：

如果$n\%i=0$，则$n\%(n/i)=0$

如果$a*b=c$，$c$不变的情况下，$a$越小，$b$越大。

那就$for$循环跑一遍，每次枚举$a$，然后判断$n/a$是否为$n$的质因数，是就输出，否就继续循环。

$AC$ $code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,y;
int pd(int x) {
	for(int i=2; i*i<=x; ++i)
		if(x%i==0) return 0;
	return 1;
}
int main() {
	while(cin>>n) {
		if(n==0) return 0;//遇到0就结束程序
		for(int i=1; i<=n; ++i) {
			if(pd(n/i)&&n%i==0) {//小优化
				printf("%d\n",n/i);
				break;//找到了就输出并打断
			}
		}
	}
	return 0;
}
```

---

## 作者：redegg (赞：0)

首先呢，翻译这题的是我一个同学。~~orz%%orz~~

我一看，啊~，不是简单的质因数分解吗？

然后就TLE了QAQ。

然后想了想，找可以被整除的质数就可以了啊~

然后因为枚举范围太大依然是TLE了QAQ。

细节决定成败啊！！！

循环枚举i，如果i是质数且可以被整除，就说明他是其中一个质因数，这个循环i只用枚举到sqrt（n）下，但是要同时记一下n/i，因为n/i也可能是质因数之一。

为什么要这样缩小呢，因为这样我们可以把枚举范围缩小到10^4，而质因数最多也就2*10^4。如果不优化，万一范围就变成10^8也不好说是吧。

（但是之前那篇题解没有这样优化，当然直接break循环也是可以的，但是万一万一万一有个质因数非常非常小呢？总之这个优化是很稳的）。

剩下的还有记住判断指数的函数枚举也是从2到sqrt（n）。

之前我从来都不注意这个小细节，然后今天就被水题给搞崩了QWQ。

```
#include <bits/stdc++.h>
using namespace std;

long long n;
long long ans;

bool zhi(long long x)
{
    for(long long i=2;i*i<=x;i++)
    {
        if(x%i==0)return false;
    }
    return true;
}

int main()
{
    while(1)
    {
        scanf("%lld",&n);
        if(n==0)break;
        long long last=0;
        for(long long i=1;i*i<=n;i++)
        {
            if(n%i!=0)continue;
            if(zhi(n/i))
                last=max(n/i,last);
            if(zhi(i))
                last=max(i,last);
        }
        printf("%lld\n",last);
    }


    return 0;
}

```

---

