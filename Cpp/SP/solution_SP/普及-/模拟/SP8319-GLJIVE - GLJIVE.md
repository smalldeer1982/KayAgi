# GLJIVE - GLJIVE

## 题目描述

 In front of Super Mario there are **10 mushrooms**, arranged in a row. A certain amount of points is awarded for picking each of the mushrooms. Super Mario must pick mushrooms **in order** they appear, but is not required to pick them all – his goal is to score a number of points **as close as possible to 100**.

In case there exist two such numbers which are equally close to 100 (e.g. 98 and 102), Mario will pick the **greater** one (in this case 102).

Help Super Mario and tell him how many points he will score.

## 样例 #1

### 输入

```
10
20
30
40
50
60
70
80
90
100```

### 输出

```
100```

# 题解

## 作者：skysun0311 (赞：6)

### 思路： 
求出 $a_1\sim a_t(t=10)$ 的前缀和， 用求绝对值函数取出 $a$ 数组中每个 $\left\vert a_i -100\right\vert$ 的值，如果比答案更优，更新答案为当前 $\left\vert a_i -100\right\vert$  的值，输出答案。

### 模拟过程：  
 
|  $\quad i\quad$ | $\quad1\quad$ | $\quad2\quad$ | $\quad3\quad$ | $\quad4\quad$ | $\quad5\quad$ | $\quad6\quad$ | $\quad7\quad$ | $\quad8\quad$ | $\quad9\quad$ | $\quad10\quad$ |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :---: |
| $\quad n\quad$  | $10$ | $20$ | $30$ | $40$ | $50$ | $60$ | $70$ | $80$ | $90$ | $100$ |
| $\quad\;\; a_i\quad$  | $10$ | $30$ | $60$ | $100$ | $150$ | $210$ | $280$ | $360$ | $450$ | $550$ |
| $\quad\left\vert a_i -100\right\vert\quad$ | $90$ | $70$ | $40$ |  $0$  | $50$ | $110$ | $180$ | $260$ | $350$ | $450$ |

**解释**：　   
当 $i=1$ 时， $n=10$ ， 由于 $a_1$ 之前没有数，所以此时的前缀和 $a_i=n=10$  。  
当 $i=2$ 时， $n=20$ ， $a_{i-1}=a_1=10$ ，所以前缀和 $a_2=n+a_1=10+20=30$   。  
当 $i=3$ 时， $n=30$ ， $a_{i-1}=a_2=30$ ，所以前缀和 $a_3=n+a_2=10+20+30=30+30=60$  。    
以此类推……   
接下来是关于表格中 $a_{i}-100$ 的绝对值的推导过程：   
$\because a_1=10$ ， $\therefore\left\vert a_1 -100\right\vert=\left\vert 90-100\right\vert=\left\vert -10\right\vert=10$ 。  
$\because a_2=30$ ， $\therefore\left\vert a_2-100\right\vert=\left\vert 30-100\right\vert=\left\vert -70\right\vert=70$ 。  
$\because a_3=60$ ， $\therefore\left\vert a_3 -100\right\vert=\left\vert 60-100\right\vert=\left\vert -40\right\vert=40$ 。
### 前缀和求法
```cpp
//使用循环求解
for(int i=1;i<=t;i++){
	cin>>n;//输入n  
	a[i]=n+a[i-1];//第a[i]个数是当前n加上a数组中上一个数
}
```
### $\begin{aligned}\large\colorbox{white}{\color{#52C410}AC }\end{aligned}$ 代码:  
```cpp
#include<bits/stdc++.h>  
using namespace std;
const int t=10;//定义常量 
long long n,ans,a[110];
void input(){//输入函数 
	for(int i=1;i<=t;i++){
		cin>>n;//输入n  
		a[i]=n+a[i-1];//求前缀和
	}
}
int main(){
	input();//使用输入函数
	for(int i=t;i>0;i--)//从大到小模拟，如果与 100 的差值相同，取大的那一个 
		if(abs(ans-100)>abs(a[i]-100))ans=a[i];//如果有更优解，更新答案 
	cout<<ans<<endl;//输出ans 
	return 0;
} 

```


---

## 作者：guozhetao (赞：3)

## 题意翻译

给定 $10$ 个整数，询问一个前缀和使得它与 $100$ 的差值最小，如果与 $100$ 的差值相同，取大的那一个。

## 思路
运用绝对值判断，剩下的按照题目写的模拟。

因为差相同取较大数，所以要从大到小循环。
## 知识点
[绝对值](https://baike.baidu.com/item/%E7%BB%9D%E5%AF%B9%E5%80%BC/3995097?fr=aladdin)是指一个数到原点的距离。正数的绝对值是它本身，负数的绝对值是它的相反数，$0$ 的绝对值还是 $0$。

$|a| = \begin{cases}
a&(a \geq 0)\\
-a&(a < 0)
\end{cases}$


------------

在 c++ 中，绝对值是这样运用的：

```cpp
#include<cmath>
//头文件
  
abs(a - b)
//a - b 的绝对值
```

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int a[11];
	a[0] = 0;
	for(int i = 1;i <= 10;i++) {
		int x;
		scanf("%d",&x);
		a[i] = a[i - 1] + x;
	}
	int ans = a[10];//注意要放在循环外面定义 
	for(int i = 9;i >= 1;i--) {//只需循环9次 
		if(abs(a[i] - 100) < abs(ans - 100)) {
			ans = a[i]; 
		}
	}
	printf("%d",ans);
}

```


---

## 作者：_lmz_ (赞：0)

题面非常容易理解，先说说思路：

首先，要计算出从 $a_1$ 加到 $a_i$ 的前缀和 $s_i$，再计算出在 $s_1$ 到 $s_{10}$ 中，和 $100$ 相减最小的那一个值，然后就直接输出这个值。

注意，这里有个细节，因为题面说要最大的那一个，所以要从 $10$ 到 $1$ 来枚举。

代码：

太丑，不放了。

---

## 作者：u2004 (赞：0)

题意简述：

给定十个整数，询问一个前缀和使得它与 $100$ 的差值最小，如果与 $100$ 的差值相同，取大的那一个。

注意原题面描述不清。我们读入十个数，记录前缀和并更新答案即可。

```cpp
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int ans=0;

int main() {
	int num=0;
	int l;
	for(int i=0; i<10; i++) {
		cin>>l;
		num+=l;
		if(abs(ans-100)>abs(num-100)) {
			ans=num;
		} else if(abs(abs(ans-100)-abs(num-100))<0.000001) {
			if(num>ans) ans=num;
		}
		if(num>100) break;
	}
	cout<<ans;
	return 0;
}
```




---

## 作者：ForeverCC (赞：0)

因为这十个整数按照顺序给出，所以按照题目模拟即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n=10,t,a,ans;
int main() {
	for(int i=1;i<=n;i++){
		scanf("%d",&t);
		a+=t;
		if(abs(ans-100)>abs(a-100))ans=a;//取更接近100的那一个 
		if(abs(ans-100)==abs(a-100))ans=max(ans,a);//一样近，取更大的那一个 
		if(a>100)break;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：hopeless_hope (赞：0)

模拟题，根据题意模拟即可

AC Code：（注释已给出）

```cpp
#include<iostream>
#include<cmath> //数学库，abs函数需要此头文件
using namespace std;
int a[15],ans;
int main()
{
    for(int i=1;i<=10;i++)
    {
        int x;
        cin>>x;
        a[i]=a[i-1]+x;//计算出每一步的前缀和
    }
    for(int i=10;i>=1;i--)//如果有相同答案，取最大，所以这里直接倒着循环
    {
        if(abs(a[i]-100)<abs(ans-100))//根据题意模拟，abs(x)代表绝对值
        {
            ans=a[i];//将答案更新
        }
    }
    cout<<ans<<endl;//输出答案
    return 0;
}
```


---

