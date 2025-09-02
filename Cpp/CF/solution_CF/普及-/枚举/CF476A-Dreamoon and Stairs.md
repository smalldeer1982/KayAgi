# Dreamoon and Stairs

## 题目描述

Dreamoon wants to climb up a stair of $ n $ steps. He can climb $ 1 $ or $ 2 $ steps at each move. Dreamoon wants the number of moves to be a multiple of an integer $ m $ .

What is the minimal number of moves making him climb to the top of the stairs that satisfies his condition?

## 说明/提示

For the first sample, Dreamoon could climb in 6 moves with following sequence of steps: {2, 2, 2, 2, 1, 1}.

For the second sample, there are only three valid sequence of steps {2, 1}, {1, 2}, {1, 1, 1} with 2, 2, and 3 steps respectively. All these numbers are not multiples of 5.

## 样例 #1

### 输入

```
10 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 5
```

### 输出

```
-1
```

# 题解

## 作者：ahawzlc (赞：5)

首先分析题：

上台阶一步可以 1 个或者 2 步。

所以要想到达顶端，当 n 为偶数时，最少用 $\frac{n}{2}$步（$\{2,2,2,···,2,2\}$）；当 n 为奇数时，最少用$\frac{n}{2}+1$步（$\{2,2,2,···,2,1\}$）。最多当然就是 n 步（$\{1,1,1,···,1,1\}$）。

接下来我们要做的，就是在这个范围内枚举，从小到大找出最小的能被 $m$ 整除的那个步数 $x$ 。找到就直接结束，找不到就输出```-1```。

~~不愧是橙题~~

```
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n,m,x,ccf=0;//勿喷变量名
	cin>>n>>m;
	if(n&1) ccf=1;//等同于n%2==1
	int mn=n/2+ccf,mx=n;
	for(int i=mn;i<=mx;i++) {
		if(i%m==0) {
			cout<<i<<endl;
			return 0;
		}
	}
	puts("-1");//找不到就输出-1
	return 0;
}
```


---

## 作者：Nt_Tsumiki (赞：2)

### 题意
有一个人想上台阶，他可以一次上两级，也可以一次上一级，现在他上台阶用了 $x$ 步，给你台阶数 $n$ 和 $m$，问 $x$ 是否为 $m$ 的倍数，是，输出 $x$，否，输出 $-1$。
### 做法
这道题的标签是暴力所以我们可以从暴力的角度来解，首先我们需要求出它的范围，最大的 $x$ 肯定是 $n$，最小的就是 $\lceil\frac{n}{2}\rceil$，这个想一下就可以得出，如果你每次都上两级，就是最小的 $x$，但台阶数是单数时，最后就只需上一级，所以总结一下即 $\lceil\frac{n}{2}\rceil$。

代码框架就很好出了，先输入 $n$， $m$，再求出最小的 $x$，进行暴力一遍一遍判断，在最后输出答案。
### Code
```cpp
#include<cmath>//ceil函数库
#include<iostream>

using namespace std;
int n,m;//台阶数

int main() {
	cin>>n>>m;//输入
	int x;
	x=ceil(double(n)/2);//最小步数，因为n为int，所以要double化
	for (int i=x;i<=n;i++) {//暴力
		if (i%m==0) {//判断
			cout<<i<<endl;
			return 0;
		}
	}
    cout<<-1;//没找到
	return 0;
}
```
### 结论
主要考察对于暴力界限的查找，和对向上取整函数的运用。

---

## 作者：Register (赞：2)

## ~~为了咕值发题解~~
	我们考虑两个极端，最多和最少
	步数最少：ceil(n/2)即尽量走两步
	为什么说尽量呢？因为有可能n为奇数，所以会有一次1步
	所以说是ceil（n/2）
	步数最大：n，即每次都走一步
由于$n$的取值很小，所以我们可以在$ceil(n/2)$到$n$这个区间内枚举
	
    如何保证ceil(n/2)到n这个区间所有的数都能走出来：
    只要每次将1、1变为2或将2变为1、1就可以走出区间内所有连续的自然数
奉上代码：

```cpp
#include <iostream>
using namespace std;
int ceil2(int x){//n除以2向上取整
	return x%2?x/2+1:x/2;
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=ceil2(n);i<=n;i++)//枚举区间
		if(i%m==0) {cout<<i<<endl;return 0;}
	cout<<-1<<endl;//没有解
	return 0;
}
```

---

## 作者：「已注销」 (赞：2)

发现$x\in[\lceil\frac{n}{2}\rceil,n]$

只需求出第一个比$\lceil\frac{n}{2}\rceil$大的$m$的倍数即可
```cpp
#include<iostream>
using namespace std;
int n,m,l;
int main(){
    cin>>n>>m;
    l=n+1>>1;
    if(n/m*m<l)cout<<-1;
    else cout<<l+(m-l%m)%m;
}
```

---

## 作者：lmndiscyhyzdxss (赞：1)

## 首先分析题：

- 台阶一步可以上 $ 1 $ 个或者 $ 2 $ 个。

- 所以要想到达顶端，当 $ n $ 为偶数时,最少用 $ n/2 $ 步。  

- 当n为奇数时,最少用 $ n/2+1 $ 步或 $ (n+1)/2 $ 步。   

- 总结是 $ (n+1)/2 $ 步。               

- 最多是 $ n/1 $ 就是 $ n $ 步。           

- 然后在区间里枚举就行了。      

## 话不多说，直接上代码 ...... 

```cpp
#include<iostream>                     
#include<fstream>                             
#include<cmath>                               
#include<algorithm>                                   
#include<cstdio>
using namespace std;    
int n,m;                    
int main()            
{        
    cin>>n>>m;      
    for(int i=(n+1)/2/*最少级数*/;i<=n/*最大级数*/;i++)//暴力枚举
    {                   
        if(i%m==0)//如果找到了，输出
        {                
             cout<<i<<endl; 
             return 0;                         
        }                            
    }                        
    cout<<"-1"<<endl;//如果没找到，输出-1  
    return 0;                                     
}  
```
            

---

## 作者：西宋太祖 (赞：1)

## 这一题数据量不大，一一枚举即可
1.枚举范围

(1)所有上完台阶的可能。

(2)所有上完台阶的可能就相当于是从n/2到n

(3)如果出现了奇数，那就是n/2+1（这里的n/2是指自动截去小数部分）

2.判断

(1)i从n/2(n/2+1)枚举到n，一一试过去，一旦实处结果就马上`return 0`。

(2)直接在枚举的后面输出-1，因为如果有可能就在循环中结束程序了。
## AC代码
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,m,f,i;
	cin>>n>>m;
	f=n/2;//枚举的起点 
	if(n%2==1)//如果n是奇数那么枚举的起点+1 
		f++;
	for(i=f;i<=n;i++)//枚举判断 
		if(i%m==0)//如果找到了 
		{
			cout<<i<<endl;//输出 
			return 0;//结束 
		}
	cout<<"-1"<<endl;//循环结束后程序还没有结束，说明找不到合适的结果，无需判断，直接输出-1即可 
	return 0;
}
```

---

## 作者：Chtholly_L (赞：0)

### 题意：

一个人上 $n$ 级台阶，台阶可以一步走两个也可以一步走一个，现在问你所走的步数的所有可能性中是否有一种是 $x$ 的倍数，如果有就输出最小的，否则输出 -1 。

---

### 分析：

上台阶的步数有很多种，但全部都在一个区间之内。如果是偶数，范围是从 $\frac{n}{2}$ 到 $n$ （全部两个两个走到全部一个一个走）；如果是奇数，范围是 $\frac{n}{2}+1$ 到 $n$ （全部两个两个走，最后一个一步走到全部一个一个走）。

然后枚举出所有的情况，判断是否为 $x$ 的倍数，如果是，输出步数否则输出 -1 。

---

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,x,minn;
	cin>>n>>x;
	if(n%2==0)minn=n/2;  //如果是偶数
	else minn=n/2+1;  //如果是奇数
	for(int i=minn;i<=n;i++)  //枚举
	{
		if(i%x==0)
		{
			cout<<i;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

题目传送>>[CF476A](https://www.luogu.com.cn/problem/CF476A)  
### 题意简述：  
爬一 $n$ 级台阶，每步可爬 $1$ 或 $2$ 级，求爬到顶最少需几步，且步数 $x$ 为 $m$ 的倍数，无解则输出 $-1$。 
### 题目分析：  
对于爬的方式，如果我们一级一级地爬，那么就需要 $n$ 次，显然此时步数最多。如果想要使步数最少，我们应尽量以最大步幅向上爬，即每步 $2$ 级，如 $n$ 为偶数，那么我们刚好只需 $\frac{n}{2}$ 步即可到顶，如 $n$ 为奇数，那么所需步数就为 $\frac{n}{2}+n\%2$。综上，要想能爬到顶，那么步数 $x\in[\frac{n}{2}+n\%2,n]$。那么求最少步数 $x$，且 $x$ 为 $m$ 的倍数，就是 $[\frac{n}{2}+n\%2,n]$ 中最小能被 $m$ 整除的数。  
### Code:  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int n,m,x=0;   //定义台阶数，m，步数
	cin>>n>>m;
	while(x<(n/2+n%2))
	{
		x+=m;     //寻找最小步数x
	}
	if(x>n)    //无解
	{
		x=-1;
	}
	cout<<x;
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/kyhtd3u7.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：LucasXu80 (赞：0)

本题解内容：Python代码+向上取整小技巧

看完题目，只有一个问题：$x$的范围。

先来看当总阶梯数$n$是偶数的情况。最大值当然是$x=n$，也就是一级一级上；最小值也没问题，是$x=n/2$，总是两级两级上。

当$n$是奇数，最大值不变，因为还是一级一级上；而最小值会变为$x=(n+1)/2$，在代码中也可以写成$n/2+1$，原因就不赘述了。

接下来就是从小到大遍历每一个$i$，只要$i$%$k=0$就输出$i$、结束程序。

再次想讲一下向上取整的一个小技巧。

$n/2$向上取整可以写作$n/2+n$%$2$。这其中的道理还是很简单的，但是可以避免写一个if语句。

好了话不多说，上[AC](https://www.luogu.com.cn/record/33674043)代码咯~

```python
import sys #后面提前结束程序要用
n,k=map(int, input().split()) #输入
m=int(n/2+n%2) #m是n/2向上取整，也就是x的最小值
for i in range(m,n+1): #别忘了n+1
    if i%k==0: #满足条件
        print(i) #输出这个i
        sys.exit() #直接结束，保证只输出最小值
print('-1') #循环结束还没有找到，输出-1表示无解
```
Python大佬勿喷QwQ

---

## 作者：_Qer (赞：0)

这里提供一种$\mathcal{O}(\dfrac{n}{2})$的方法

因为这里只有走$1$步和走$2$步的走法，那么最多需要的步数，即为每次都只走一步，为$n$次，最少需要的步数为每次走两步，即$\dfrac{n}{2}$种，而由于每步可以走$1$或$2$格，所以步数为$\dfrac{n}{2}$至$n$的走法都有，于是我们只需要在这个范围内枚举即可。（本人蒟蒻没有证明，大佬有方法就留言一下啦）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
//如题目要求
int main()
{
    cin >> n >> m;
    if (m > n)//超出范围
    {
        cout << -1 << endl;
        return 0;
    }
    for (int i = (int)((double)n / 2 + 0.5); i <= n; ++i)
    {//从n/2开始枚举（向上取整）到n（由于是要最小的，所以从小到大枚举）
        if (i % m == 0)//满足条件
        {
            cout << i << endl;
            return 0;//结束
        }
    }
    cout << -1 << endl;//没找到
    return 0;
}
```

---

