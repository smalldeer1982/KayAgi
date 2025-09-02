# [NWRRC 2017] Auxiliary Project

## 题目描述

Anna 刚刚完成了她的课程项目。她有很多七段 LED 显示器作为剩余物品，还有一个小型电源。每个显示器的耗电量与点亮的段数成正比，例如，数字 $9$ 的耗电量是数字 $7$ 的两倍。

Anna 想知道，如果她的电源能够点亮 $n$ 个段，并且她想要恰好点亮 $n$ 个段，那么她能够实现的最大数字和是多少。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7
```

### 输出

```
11
```

## 样例 #3

### 输入

```
6
```

### 输出

```
14
```

# 题解

## 作者：fkcufk (赞：5)


[题目传送门](https://www.luogu.com.cn/problem/P7019)

解析：

我们可以发现，每次如果用 $3$ 根的话，$7$ 显然是最优的。

所以我们可以判断 $3$ 是否能整除 $n$，即可。

得 $0$：直接输出。

得 $1$：去掉 $1$ 根拼成 $4$，然后输出。

得 $2$：那剩下的两条后面拼一个 $1$，输出。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	// 判断
	if(n%3==0) cout<<n/3*7;
	else if(n%3==1) cout<<n/3*7-3;
	else cout<<n/3*7+1;
	return 0;
}
```

---

## 作者：Karry5307 (赞：5)

### 题意

我可能解释的不是很清楚，就不解释了。

$\texttt{Data Range:}2\leq n\leq 10^6$

### 题解

贪心。

很显然 $7$ 的性价比是最高的，所以我们需要多填 $7$，于是很显然对 $n\bmod 3$ 讨论。

- 如果 $n\bmod 3=0$，那么答案很显然为 $\frac{7n}{3}$。

- 如果 $n\bmod 3=1$，由于多的一个无法凑成数字，所以要拿掉之前的一个 $7$ 凑成 $4$，答案为 $\frac{7(n-1)}{3}-3$。

- 如果 $n\bmod 3=2$，那么很明显凑一个 $1$，答案为 $\frac{7(n-2)}{3}+1$。

于是没了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n;
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read();
	printf("%d\n",n/3*7+(n%3==2?1:n%3==1?-3:0));
}
```

---

## 作者：血色黄昏 (赞：2)

根据题意可以发现，每次用3根拼成7是最优的，那么只要判断n是否被3整除就好了。

当除3余0，显然全拼七

当除3余1只能去掉一个七拼成剩下最优的4

当除3余2后面多拼一个1就好

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin>>n;
    if(n % 3 == 0)cout<<n * 7 / 3<<endl;//拼成n/3个7
    else if(n % 3 == 1)cout<<(n%3==1?n/3*7-3:n/3*7+1)<<endl;//压缩代码，自行推导即可
    return 0;
}
```


祝大家CSP rp++！

---

## 作者：xiaofeng_and_xiaoyu (赞：1)

题面：给出 $n$ 段 $\verb!led!$ 灯，求组成一位数的最大和。

范围：$2<n<2$ $\times$ $10^{6}$。

考虑贪心。

自己动手画了一个图，可能有帮助。

![yt](https://cdn.luogu.com.cn/upload/image_hosting/h700of2g.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

从中可以看出，$\verb!‘7’!$ 的权值最大。

所以尽可能凑 $\verb!‘7’!$。

因为 $\verb!‘7’!$ 由三条灯组成，所以要取余三后判断:

1. 得 $0$，直接输出。

2. 得 $1$，此时拿一条灯组成四（因为必须正好为 $n$）。

3. 得 $2$，拿剩下的 $2$ 条组成 $\verb!‘1’!$，加一。

最后输出就可以了，代码如下：

```cpp
#include<iostream>
using namespace std;
int main(){
	int a,b;
	cin>>a;
	b=a/3*7;
	if(a%3==0)cout<<b;
	else if(a%3==1)cout<<b-3;
	else cout<<cout<<b-2;
	return 0;
}
```


---

## 作者：prt_xcdh (赞：0)

# #思路

这道题明显每次用 $3$ 根拼成 $7$ 是最好的，所以只要判断是否是 $3$ 的倍数。

如果是 $3$ 的倍数，显然是全拼 $7$。

如果 $n$ $\bmod$ $3$ = $1$，就去掉一个 $7$ 拼成 $4$。

其他就多拼一个 $1$。

# #代码

```c++
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	if(n%3==0)cout << n/3*7;
	else if(n%3==1)cout << n/3*7-3;
	else cout << n/3*7+1; 
    return 0;
}
```



---

## 作者：____someone____ (赞：0)

本题我用的方法是 **动态规划** ，代码和完全背包很像。

初始化是一个很小的数字， 本题要求**正好用完**。

第一层循环 $i$ 枚举 $0\sim9$ 个数字， 第二层循环 $j$ 枚举 $\texttt{LED}$ 灯管数。

当段数为 $6$ 的时候， 我们不会选择数字 $9$ 而是选择两个 $7$， 所以 $7 + 7 = 14$ 很明显大于 $9$。 然后我们就可以得出 _**状态转移方程**_ ： $ \texttt{f[j] = max(f[j],f[j-shu[i]]+i)} $。

各个数字对应的 $\texttt{LED}$ 灯段数如下表：


| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 6 | 2 | 5 | 5 | 4 | 5 | 6 | 3 | 7 | 6 |

 可以把它们存在一个数组里。

代码如下:


------------
CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,shu[10]={6,2,5,5,4,5,6,3,7,6};   //w用来存每个数字所需段数 
int f[1000010];     //存最大值 

int main()
{
	memset(f,-0x7f7f,sizeof(f));
	cin>>n;
	f[0]=0;    //初始化
	for(int i=0;i<=9;i++)
	  for(int j=1;j<=n;j++)
	    if(j-shu[i]>=0)
	      f[j]=max(f[j],f[j-shu[i]]+i);     //状态转移方程 
	cout<<f[n];
	return 0;
}
```


---

## 作者：qiuweilin666 (赞：0)

本题有三种思路：搜索、贪心、dp。

### 题解
浅讲一下 dp。我们可以设 $f[i]$ 为点亮 $n$ 段 LED 灯时的最大值,
首先我们可以列出 $0 \sim 9$ 每种灯的所需要的段数。

| 数字 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |7 |8  | 9 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 段数 | 6 | 2 | 5 | 5 | 4 | 5 |  6| 3 |  7| 6 |


如果要凑出段数为 $6$ 的时，我们不会选择数字 $9$ 而是 $7+7$。于是我们可以通过前一个已知的最大的 $f[i]$ 来转移到 $f[j]$。得出状态转移方程 $f[j]=\max(f[j],f[j-p[i]]+i)$，$p[i]$ 为数字所用的段数。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int p[2000001]{6,2,5,5,4,5,6,3,7,6};
int f[2000001];
int n;
int main(){
	cin>>n;
	f[0]=0;
	for(int i=0;i<=9;i++){
		for(int j=p[i];j<=n;j++){
			f[j]=max(f[j],f[j-p[i]]+i);
		}
	}
	cout<<f[n];
}
 
```



---

## 作者：lidundun (赞：0)

# Auxiliary Project
本题一致认为有两种思路，贪心和动态规划，但是大致思路差不多，我就选择了动态规划。

这个思维和完全背包差不多，$w[i]$ 表示价值，重量就是 $i$，只是要换一下循环顺序。

初始化必须无穷小，因为本题必须要正好用完，不然可能出现负数的情况。$f[0]$ 也必须初始化为 $0$，不然也会有负数。

外层循环 $i$ 枚举所有数字，第二层循环 $j$ 枚举灯管数，表示当前剩下 $j$ 个灯管然后拼一个数字 $i$ 的情况下的答案最大值。

最后就是注意一下数据范围 $2\le n\le2\times 10^6$，翻译有误。

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w[10]={6,2,5,5,4,5,6,3,7,6},f[1000010];
int main()
{
	scanf("%d",&n);
	memset(f,-0x7f7f,sizeof f);
	f[0]=0;
	for(int i=0;i<=9;i++)
	  for(int j=1;j<=n;j++)
	    if(j-w[i]>=0)
	      f[j]=max(f[j],f[j-w[i]]+i);
	printf("%d",f[n]);
}
```


---

## 作者：yangchenxiao (赞：0)

由于蒟蒻没有思维，决定采用暴力 $dp$   
把每种数字当成一种物品，体积为灯的数量，价值为数码本身，用一个完全背包即可   
由于要求恰好，那么初始化时将除零以外的体积初始化为负无穷

注意翻译中的数据范围有问题，数组要开到 $10^6$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;
int n,f[maxn];
int w[15]={6,2,5,5,4,5,6,3,7,6};
int main(){
	cin>>n;memset(f,-0x3f,sizeof f);
	f[0]=0;
	for(int i=0;i<=9;i++){
		for(int j=w[i];j<=n;j++){
			f[j]=max(f[j],f[j-w[i]]+i);
		}
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Update
- $\texttt{2021.6.24}$ 修改了一处格式上的错误和一处笔误。

## Content
已知用 LED 灯来显示 $0\sim9$ 这十个数字分别需要 $6,2,5,5,4,5,6,3,7,6$ 段 LED 灯管组成，现在，你需要点亮正好 $n$ 段 LED 灯管，使得组成的数字的和最大。

**数据范围：$2\leqslant n\leqslant 2\times 10^5$。**
## Solution
我们不妨用 $\dfrac{\text{数字}}{\text{灯管段数}}$ 来衡量点亮这些数的价值，得到的表格如下：

| 数字 | $0$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 价值（保留 $2$ 位小数） | $0$ | $0.5$ | $0.4$ | $0.6$ | $1$ | $1$ | $1$ | $2.33$ | $1.14$ | $1.5$ |

不难发现这样的话，尽可能多地组成 $7$ 的价值是最大的，所以我们多组成 $7$，假设组完以后的数的和为 $ans$。然后对剩下的灯管数量，也就是 $n\mod 3$，进行分类讨论。

1. $n\mod 3=0$，此时的答案就是 $ans$。
2. $n\mod 3=1$，此时无法再组成数，然而题目限制我们要正好 $n$ 段灯管，所以我们考虑把一个 $7$ 给去掉，然后剩下 $4$ 段灯管，此时可以组成一个 $4$。因此答案就是 $ans-7+4=ans-3$。
3. $n\mod 3=2$，此时可以再组成一个 $1$，不需要再去舍弃了（舍弃了很明显不是最优方案）,那么此时答案就是 $ans+1$。

那么这道题目就做完了。
## Code
```cpp
int n;
long long ans;

int main() {
	scanf("%d", &n);
	ans = n / 3 * 7;
	n %= 3;
	if(n == 1) printf("%d", ans - 3);
	else if(n == 2) printf("%d", ans + 1);
	else printf("%d", ans);
	return 0;
}
```

---

