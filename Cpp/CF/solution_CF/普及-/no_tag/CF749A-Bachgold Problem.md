# Bachgold Problem

## 题目描述

Bachgold problem is very easy to formulate. Given a positive integer $ n $ represent it as a sum of maximum possible number of prime numbers. One can prove that such representation exists for any integer greater than $ 1 $ .

Recall that integer $ k $ is called prime if it is greater than $ 1 $ and has exactly two positive integer divisors — $ 1 $ and $ k $ .

## 样例 #1

### 输入

```
5
```

### 输出

```
2
2 3
```

## 样例 #2

### 输入

```
6
```

### 输出

```
3
2 2 2
```

# 题解

## 作者：Daniel_He (赞：4)

[$\color{blue}\text{My Blog}$](https://www.luogu.com.cn/blog/danielcode/#)

__第一步：题意__

题目大概的意思为：给你一个整数$n$，要求你算出$n$能分解成几个质数的和（可以一样），把这些数列举出来。

__第二步：思路__

本题的思路为：最小的质数是$2$，由于题目允许分成多个相同的质数，所以如果$n$是偶数的话，能够分解成的质数最多的数量就是$n\div2$，所以第一行输出$n\div2$得到的结果，在第二行输出$n\div2$个$2$就可以AC了。

那么$n$不是偶数怎么办呢？因为第二小的质数为$3$，$3$是一个奇数，所以如果$n$是奇数的话，只要在第一行输出$(n-1)\div2$的结果，在第二行输出$n\div2-1$个$2$和一个$3$就可以AC了。

__第三步：代码__

附代码：
```cpp
#include<iostream>
using namespace std;
int main(){
    int a;//a是题目中的n
    cin>>a;//输入
    cout<<a/2<<endl;//因为int类型是将算出的结果自动向下取整，所以奇数和偶数都可以用a/2来解决
    if(a%2==0){//如果是偶数
        for(int x=1;x<=a/2;x++){
            cout<<2<<" ";//重复输出a/2遍2
        }
    }
    else{//如果是奇数
        for(int x=1;x<=a/2-1;x++){
            cout<<2<<" ";//先输出a/2-1个2
        }
        cout<<3;//最后将3输出
    }
    return 0;//结束
}

```
最后点个赞再走吧！

---

## 作者：monstersqwq (赞：1)

#### 题目大意：

给出一个数，问它最多能分成几个质数（可以重复）。

这道题良心之处就在于，可以重复使用相同的质数，既然要取最大，就多选最小的质数 $2$，分两种情况讨论。

当 $n \bmod 2=0$ 时，答案就是 $n \div 2$ 个 $2$，按照题目要求格式输出即可。

当 $n \bmod 2=1$ 时，不能全取 $2$，那就尽可能多取，即 $(n-1) \div 2$ 个，将其中的一个 $2$ 替换成 $3$ 即可达到最大值 $(n-1) \div 2$，由 $(n-1) \div 2-1$ 个 $2$ 和 $1$ 个 $3$ 组成，按照题目格式输出即可。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int main()
{
	int n;
	cin>>n;
	if(n%2==0)
	{
		cout<<n/2<<endl;
		for(int i=1;i<=n/2;i++)
		{
			cout<<"2 ";
		}
		cout<<endl;
	}
	else
	{
		cout<<(n-1)/2<<endl;
		for(int i=1;i<=(n-1)/2-1;i++)
		{
			cout<<"2 ";
		}
		cout<<"3"<<endl;
	}
	return 0;
}
```

拓展：你以为到这里就结束了？并不是，这道题如此简单是因为出题人非常善良，而毒瘤的出题人可能会把题出成这样：给出一个整数 $n$，求最多能分成几个不同质数的和？无解输出0。~~没有要求输出方案是因为有输出方案我的 dp 就死了。~~

接下来说说这道题的思路：首先肯定要把质数筛出来，这里推荐一种 $\Theta(n)$ 筛出 $2$ 至 $n$ 的质数的方法：[欧拉筛（线性筛）](https://blog.csdn.net/Soul_97/article/details/81228047)，泥谷也正好有[模板题](https://www.luogu.com.cn/problem/P3383)，虽然此题范围不大，也可用埃氏筛，但快一点总归好一点。

接下来是重点的 dp 环节（不懂什么是 dp 的小萌新们看这里[动态规划](https://baike.baidu.com/item/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/529408?fr=aladdin)）

dp 三部曲：初始化、dp、输出答案，这里我一步步讲。

初始化：肯定要先筛质数，然后需要有这些数组：$prime_i$ 记录第 $i$ 个质数（在筛质数的时候就可以记录了）、$psum_i=\sum\limits_{j=1}^i prime_j$（这个可以递推）。

明确 $dp$ 数组的维数及含义：一维肯定无法存，因为不知道可以取哪些质数，所以我对取的质数自动进行升序排序，用二维 $dp_{i,j}$ 表示和为 $i$，最大的质数是第 $j$ 个质数时，最多能取多少个。

对于每个 $i$，初始化 $dp_{prime_i,i}=1$，原因请参照含义自行理解。

dp：状态转移方程：
$$dp_{i,j}=\sum\limits_{k=1}^{j-1}\max(dp_{i-prime_j,k}+1)\quad (dp_{i-prime_j,k}\ge1)$$

相信大家都能看懂，解释一下 $dp_{i,j}$ 更新条件：如果 $dp_{i-prime_j,k}\ge1$，即 $dp_{i-prime_j,k}$ 有解，就更新，无解不更新。

说一下 $psum$ 数组怎么用：如果 $psum_j < i$，即用前 $j$ 个质数不可能凑出 $i$，就进行下一次循环，而如果 $prime_j>i$，就直接跳出循环（注意，这两个不一样，一个是 continue，不能写在循环条件中，另一个是直接 break，可以写在循环条件中）。

至于答案，就很简单了： $ans=\sum\limits_{i=1}^{cur}\max(dp_{n,i})$（cur 为 $1$ 到 $n$ 的质数总数，也是蛮有用的），输出即可。

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
bool isprime[10005];
int prime[10005],cur=0,dp[10005][1505],psum[10005];
void p(int q)//欧拉筛质数
{
	for(int i=2;i<=q;i++)
	{
		if(isprime[i])
		{
			cur++;
			prime[cur]=i;
		}
		for(int j=1;j<=cur&&i*prime[j]<=q;j++)
		{
			isprime[i*prime[j]]=false;
			if(i%prime[j]==0)
			{
				break;
			}
		}
	}
}
int main()
{
	int n;
	cin>>n;
	memset(isprime,true,sizeof(isprime));
	isprime[1]=false;
	p(n);
	for(int i=1;i<=cur;i++)
	{
		psum[i]=psum[i-1]+prime[i];
	}
	for(int i=1;i<=cur;i++)
	{
		dp[prime[i]][i]=1;
	}
    //初始化
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=cur&&prime[j]<=i;j++)
		{
            if(psum[j]<i) continue;
			if(prime[j]!=i)
			{
				for(int k=1;k<j;k++)
				{
					if(dp[i-prime[j]][k]>=1) dp[i][j]=max(dp[i][j],dp[i-prime[j]][k]+1);
				}
			}
		}
	}
    //dp主体
	int ans=-1;
	for(int i=1;i<=cur;i++)
    {
        ans=max(ans,dp[n][i]);
    }
    cout<<ans<<endl;
    //记录答案并输出
	return 0;
}
```


作者亲测，1s 大约能跑 $3500$ 左右的数据，2s 大约能跑 $5000$。

我知道这篇题解完全跑题了，但是可以启发大家从水题中找到挑战，希望能给大家以启发，做一名更强的 OIer！谢谢。

望管理员通过，谢谢。

---

## 作者：k3v1n070828 (赞：1)

很多大佬们看到题可能会觉得得用深搜、筛法之类的算法，其实这就是一个简单的数学题。

讲讲思路：**要想分解成尽量多的质数，则需要每个质数尽量的小，最小的质数是$2$，其次是$3$**

本题良心的一点是：可以有重复的质数

我们来找一找关于$n$的规律：

$n=4$  最多分成$2$个质数，$2+2$，无$3$

$n=5$  最多分成$2$个质数，$2+3$，有$3$

$n=6$  最多分成$3$个质数，$2+2+2$，无$3$

$n=7$  最多分成$3$个质数，$2+2+3$，有$3$

$n=8$  最多分成$4$个质数，$2+2+2+2$，无$3$

找到规律：$n$是奇数时，则有一个$3$，其余都是$2$；$n$是偶数时，总共有$n/2$个$2$。最多能分成$n/2$个质数。

找出了规律，就能AC，给大家一个参考代码：

```cpp
#include<cstdio> 
using namespace std;
int n; 
int main(){//准备工作 
	scanf("%d",&n);//输入
	printf("%d\n",n/2);//先不用考虑别的，先输出总共的质数
	if(n%2==0)//如果n是偶数
		for(int i=1;i<=n/2;i++)
			printf("2 ");//输出时别忘了加空格
	else//如果n是奇数
	{
		for(int i=1;i<n/2;i++)//输出n/2-1个2
			printf("2 ");
		printf("3");//再输出一个3
	}
 	printf("\n");//养成结尾换行好习惯
   return 0;
}
```
望大佬们点个赞，Bye~

感谢一位大佬的提醒，一个小错误已改正!

---

## 作者：Take_A_Single_6 (赞：0)

继续水题解~
==
###### ~~这道题相当简单~~  
- 首先，我们要明确最小的偶数质数是2；  
最小的奇数质数是3。
  
- 然后，这道题就分成了两种情况，奇数和偶数。  
任何偶数都是2的倍数，奇数-3都是偶数（本题不考虑1
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if(n%2)//奇数
    {
        n-=3;//-3变成偶数
        cout<<1+n/2<<endl;//记得还有一个3
        for(;n>0;n-=2)//每次-2并输出，为0即止
            cout<<"2 ";
        cout<<"3 ";//记得还有一个3
    }
    else//偶数
    {
        cout<<n/2<<endl;
        for(;n>0;n-=2)//同奇数
            cout<<"2 ";
    }
    return 0;
}
```

---

## 作者：thomas_zjl (赞：0)

蒟蒻的我又来水题解了。

这道题很简单，如果你要找最多质数的和为输入的$n$。

那么就用$2$和$3$就可以了。

个数就是$\lfloor n/2\rfloor$就可以了。

后来分为偶数和奇数两类。

1. 偶数：输出$\lfloor n/2\rfloor$个$2$。
1. 奇数：输出$\lfloor n/2\rfloor-1$个$2$,在输出一个$3$。

接下来就是代码了。

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	cout<<n/2<<endl;//因为C++自带向下取整，所以可以直接输出。
	if(n%2==0)//如果n是奇数。
	{
		for(int i=1;i<=n/2;i++)
		{
			cout<<2<<' ';
			//输出n/2个'2'。
		} 
	}
	else
	{
		for(int i=1;i<n/2;i++)
		{
			cout<<2<<' ';
			//输出n/2-1个'2'。			
		} 
		cout<<3;//在输出一个'3'。
	}
    return 0;
}
```


---

## 作者：Autism_ever (赞：0)

### 本题将一个数转换为质数，可以相同
### 最小的质数为2
### 可以判断n是否为奇数或偶数
### 偶数输出2。
### 奇数则用3（最小的奇质数）
***
### 非常水
### 太牛了

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int n;
int main()
{
	cin>>n;
	if(n%2==0)//判断是否为奇数或偶数 
	{
		cout<<n/2<<endl;//有多少个 
		for(int i=1;i<=n/2;i++)//输出一半即可 
		{
			cout<<2<<" ";//疯狂输出2 
		}
	}
	else if(n%2==1)//奇数 
	{
		cout<<(n-1)/2<<endl;//有多少个 
		for(int i=1;i<=n/2-1;i++)//循环输出 
		{
			cout<<2<<" ";
		}
		cout<<3;//奇数输出一个3 
	}
	return 0;
}

```


---

## 作者：Eason_AC (赞：0)

## Content
给定一个数 $n$，求它最多能够拆分成多少个质数，并输出拆分成的每一个质数。

**数据范围：$2\leqslant n\leqslant 10^5$。**
## Solution
我们考虑尽可能地用小的数拆分。

由样例 $2$ 可知，拆分成的质数可以重复，那么就考虑用最小的两个—— $2$ 和 $3$，来拆分。

我们通过奇偶性来分类讨论：

- 当 $n$ 为奇数，此时我们可以考虑 $n-3$ 用 $\dfrac{n-3}{2}$ 个 $2$ 来拆分，最后用 $3$。至于为什么不是先拆分成 $\dfrac{n-1}{2}$ 个 $2$……因为最后剩个 $1$ 没法拆分啊……
- 当 $n$ 为偶数，此时直接用 $\dfrac{n}{2}$ 个 $2$ 来拆分就好。

## Code
```cpp
#include <cstdio>
using namespace std;

int n;

int main() {
	scanf("%d", &n);
	printf("%d\n", n / 2);
	if(n % 2) {
		for(int i = 1; i <= (n - 3) / 2; ++i)
			printf("2 ");
		printf("3");
	} else
		for(int i = 1; i <= n / 2; ++i)
			printf("2 ");
}
```

---

## 作者：封禁用户 (赞：0)

### 小学数学题

其实这道题并不需要那么多if和for,直接一个循环一个特判就够了

首先,要尽量多输出$2$(最小质数,数越小个数越多),然后每次$n=n-2$(当$n$为真),如果$n=3$就输出$3$并停止循环($3$是除$2$外的最小质数,注意,$n=3$的特判要放在循环中的最前面,否则后果自负),则此时质数的个数一定为$n$ $\div$ $2$个。

上代码($c++$):

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin>>n;
	cout<<n/2<<endl;
	while(n)
	{
		if(n==3)
		{
			cout<<3<<" ";
			return 0;
		}//特判放前面
		cout<<2<<" ";
		n=n-2;
	}
	return 0;
}
```


---

## 作者：LucasXu80 (赞：0)

Python 题解~

带大家找找规律，这题规律不太难找。

看样例不难发现，第一行的个数一定是$n/2$。

为什么呢？

我们都知道，最小的质数是$2$，它是一个偶数。

也就是说，如果$n$是一个偶数，显然输出$n/2$个$2$就可以了。

那如果$n$是一个奇数，如果不断输出$2$，会输出$n/2$个$2$，但是会**剩下一个**$1$，而$1$**不是质数**。

所以这个时候我们要做出一些取舍，在输出$n/2-1$个$2$后，输出一个$3$。（$3$是质数）所以总共还是$n/2$个数。

当然，你可以写一个if-else，然后分别写1句输出以及1个循环输出。

像这样：（这个不是重点，就不注释了）

```python
n=int(input())
if n%2==0:
    print(n//2)
    for i in range(n//2):
        print(2,end=' ')
else:
    print(n//2)
    for i in range(n//2-1):
        print(2,end=' ')
    print(3)
```
但是，像我~~这么懒~~如此追求极简代码的人，肯定不满足于此。有没有更短的代码呢？

其实化简代码就像**提取公因数**一样，把一样的东西提出来。

首先，显然可以把print(n//2)提出来。

那么剩下的怎么提呢？

你会发现，在for循环的range函数括号内，一个是$n//2$，一个是$n//2-1$。

而这个$-1$可以看作是$-n$%$2$，因为当$n$是偶数的时候，正好是$-0$。

到此为止，我们就把公因式提完了。上[AC](https://www.luogu.com.cn/record/33729751)代码！

```python
n=int(input()) #输入n
print(n//2) #先输出n//2（print自带换行）
for i in range(n//2-n%2): #前面解释过啦
    print(2,end=' ') #别忘了空格结尾，不然会换行的
if n%2==1: #是奇数，还需要输出一个3
    print(3)
```
代码长度98B，又一次成功地压进了100B~

希望大家喜欢，求过求赞~

---

## 作者：18lxxrz (赞：0)

### 题意

要你把一个数尽可能地拆分成若干质数的和，求拆分出的质数最大的数量。


------------


### 那么……思路
直接贪心选取2，如果偶数肯定就是n/2个2，奇数的话会剩下1，那么2变成3就行。（即n/2-1个2+1个3）~~巨佬从不看括号~~


------------

话不多说，上代码，借鉴一下。


------------


```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;

int main ()
{
    int n;//输入数n
    scanf("%d",&n);
    printf("%d\n",n/2);//总数都是n/2个
    for(register int i=1;i<n/2;++i) 
        printf("2 ");//前n/2-1个都是2，输出即可
    return 0*printf("%d\n",2+bool(n&1));
}
```


---

## 作者：Caishifeng666 (赞：0)

# 易得，每一个数都可以分解为任意个2与3之和，证明如下：
## 设这个数为n，
① 如果n%2==0 显然 它可以拆分成n个2相加

② 如果n%2!=0 他可以拆分成n/2-1个2与一个3（这样拆，拆出的数最多）。
下面是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	if (n%2!=0){printf("%d\n",n/2);for (int i=1;i<=n/2-1;i++) printf("2 ");printf("3");}
	else {printf("%d\n",n/2);for (int i=1;i<=n/2;i++) printf("2 ");}
	return 0;	
}
```

---

## 作者：我是蒟弱 (赞：0)

### 这道题的思路如下：

1.判断**奇偶性**

2.统计**总个数**

3.统计**2的个数**

4.统计**3的个数**

就这么**简单**

任何一个偶数都可以拆成n个2相加（2 is prime），这也是最多的拆法

任何一个奇数减了最小的奇质数（3）也是偶数，所以说奇数的拆法就是1个3加上很多2。

具体实现见代码【C++】：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int n;//声明一个数 
	scanf("%d",&n);//输入 
	if(n%2==0){//偶数
		//毫无疑问，偶数能拆成n个2相加 
		printf("%d\n",n/2);//除以2看看能拆成几个2，输出个数（不要忘了换行） 
		for(register int i=1;i<=(n/2);i++){//把2一个一个输出 
			printf("2 ");//不要忘了空格 
		}
	}else{//奇数 
		//奇数，就输出一个3，剩下都是2就行了，不是吗？ 
		printf("%d\n",((n+1)/2)-1);//计算总个数：把n加1变成偶数，除以2再减1，减1是因为你多算了一个（加了个1），当然也可以（n-3）/ 2 + 1 
		for(register int i=1;i<=(((n+1)/2)-1-1);i++){//计算2，输出 
			printf("2 ");//不要忘了空格 
		}
		printf("3");//最后输出一个3 
	}
	return 0;//~~完美~~ 
} 
```

---

