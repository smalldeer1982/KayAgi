# Different Divisors

## 题目描述

Positive integer $ x $ is called divisor of positive integer $ y $ , if $ y $ is divisible by $ x $ without remainder. For example, $ 1 $ is a divisor of $ 7 $ and $ 3 $ is not divisor of $ 8 $ .

We gave you an integer $ d $ and asked you to find the smallest positive integer $ a $ , such that

- $ a $ has at least $ 4 $ divisors;
- difference between any two divisors of $ a $ is at least $ d $ .

## 说明/提示

In the first test case, integer $ 6 $ have following divisors: $ [1, 2, 3, 6] $ . There are $ 4 $ of them and the difference between any two of them is at least $ 1 $ . There is no smaller integer with at least $ 4 $ divisors.

In the second test case, integer $ 15 $ have following divisors: $ [1, 3, 5, 15] $ . There are $ 4 $ of them and the difference between any two of them is at least $ 2 $ .

The answer $ 12 $ is INVALID because divisors are $ [1, 2, 3, 4, 6, 12] $ . And the difference between, for example, divisors $ 2 $ and $ 3 $ is less than $ d=2 $ .

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
6
15```

# 题解

## 作者：fls233666 (赞：4)

因为最后要求得的 $a$ 要尽可能小，所以 **$a$ 的因子也要尽可能小。**

观察样例，我们发现样例的答案都有且仅有四个因子。进一步分析，我们发现，因为要满足每个因子之间差至少为 $d$ 的条件，所以如果最终答案的因子个数超过了四个，得到的 $a$ 就一定不是最小的。**所以最终的 $a$ 一定只有四个因子。**

由于 $a$ 本身与 $1$ 也算两个因子，因此对于剩下的两个因子，进行枚举。

首先想到的枚举思路是，因为因子之间的最小差值为 $d$ ，所以剩下的两个因子是 $d+1$ 与 $d+d+1$ ，最终有 $a=(d+1) \times (d+d+1)$ 。这种思路的错误是显然的：当 $d+1$ 或 $d+d+1$ 为合数时，$a$ 的因子就不只有四个，同时因子之间最小差值为 $d$ 的要求也不能被满足。

重新考虑枚举方案。设枚举得到的两个因子为 $x_1$ 与 $x_2$ ，那么 $x_1$ 与 $x_2$ 必须为质数，这样才能保证 $a$ 有且仅有四个因子。又因为要满足差值最小为 $d$ ，所以对于 $x_1$ ，我们暴力找到大于 $d+1$ 的最小质数，同理对于 $x_2$ ，我们找到大于 $d+x_1$ 的最小质数。最后的答案就有 $a=x_1 \times x_2$。

下面是本题的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 3e5+5;

bool tag[mxn];

inline void prepare(){  //用筛法暴力处理出质数
	for(rgt i=2;i<mxn;i++){
		if(!tag[i]){
			for(rgt j=i+i;j<mxn;j+=i)
				tag[j]=true;
		}
	}	
}

int main(){
	int test,d,div1,div2;
	prepare();
	scanf("%d",&test);
	while(test--){
		scanf("%d",&d);
		for(div1=1+d;tag[div1];div1++);  //找到第一个因子
		for(div2=div1+d;tag[div2];div2++);  //找到第二个因子
		printf("%d\n",div1*div2);  //输出答案
	}
	return 0;
} 
```


---

## 作者：hensier (赞：1)

对于一个正整数 $a$（$a \gt 1$），其必有正因子 $1$ 和 $a$。由于 $a$ 应至少有四个正因子，所以除了 $1$ 和 $a$ 之外，$a$ 必定还有两个其它的正因子。

设这两个正因子分别为 $x,y$（$x \lt y$）。根据题意，可知 $x \ge d+1$，$y \ge x+d$。且 $(1,x)$ 和 $(x,y)$ 范围内均无 $a$ 的因子。

由于 $(1,x)$ 内无 $a$ 的正因子，因而 $(1,x)$ 也无 $x$ 的正因子。所以 $x$ 必定为质数。假如 $x$ 不为质数，则 $(1,x)$ 内必有 $x$ 的其它正因子。由于 $x$ 为 $a$ 的正因子，因此该正因子也为 $a$ 的正因子。这与题意相矛盾。于是 $x$ 为质数。同理 $y$ 也为质数。

经过分析可知，当 $a$ 有四个正因子时，$a$ 的正因子分别为 $1,x,y,a$。那么此时必有 $a=xy$。我们只需求出最小的 $x,y$ 即可。

$x \ge d+1$，所以 $x$ 应为大于等于 $d+1$ 的最小素数。而 $y \ge x+d$，因此 $y$ 应为大于等于 $x+d$ 的最小素数。

我们不妨先 $\mathcal O(\text{maxn})$ 筛出 $2 \sim \text{maxn}$ 内的所有素数。由于 $d \le 10^4$，因此 $\text{maxn}$ 为大于等于 $2 \times 10^4$ 的最小素数即可。这里 $\text{maxn}=20011$，取一个稍大一些的数尚可，影响不大。

接着再用 $\mathcal O(\log\text{cnt})$ 的复杂度（其中 $\text{cnt}$ 为 $2 \sim \text{maxn}$ 内素数个数，经试验 $\text{cnt} \lt 3000$），运用二分分别找到大于等于 $d+1$ 的最小素数作为 $x$，再找到大于等于 $x+d$ 的最小素数作为 $y$ 即可。对于每组数据，输出 $xy$ 即可。

`C/C++` 代码：

```cpp
#include<stdio.h>
#include<stdbool.h>
const int maxn=20011;
int t,prime[3001];
bool vis[20012];
void init() // O(n) 筛素数
{
    for(int i=2;i<=maxn;++i)
    {
        if(!vis[i])prime[++prime[0]]=i;
        for(int j=1;i*prime[j]<=maxn&&j<=prime[0];++j)
        {
            vis[i*prime[j]]=true;
            if(i%prime[j]==0)break;
        }
    }
}
int find(int x) // 二分查找大于等于 d+1, x+d 的最小素数
{
    int l=1,r=prime[0],mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(prime[mid]>=x)r=mid-1;
        else l=mid+1;
    }
    return prime[l];
}
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
int main()
{
    init();
    t=read();
    while(t--)
    {
        int d=read(),x=find(d+1);
        printf("%d\n",x*find(x+d)); // 这里 find(x+d) 即为 y
    }
    return 0;
}
```

---

## 作者：UperFicial (赞：1)

# 数论

### 前言

挺简单的数论，但对于我这种菜鸡还是 $INF$ 眼题（

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF1474B)

### 题意简述

要求你构造一个正整数 $a$，使得：

- $a$ 至少有 $4$ 个正因子（包括 $1$ 和它本身）

- 对于 $a$ 的任意两个不同的正因子 $x,y\ (y>x)$ ，都有 $y-x\ge d$。

给你 $d$，求 $a$。

### 题目分析

$a$ 的最小的正因子肯定是 $1$，只要我们再求出 $a$ 的两个质因子就能求出 $a$。

不难想出只要求出两个最小的质数也就是 $a$ 的质因子 $p_1,p_2\ (p_1<p_2)$ 使 $p_1-1\ge d$ 且 $p_2-p_1\ge d$，那么 $a$ 就是 $p_1p_2$。

枚举质因子也有技巧：

- 枚举奇数，因为只有奇数才可能是质数（$2$ 除外）

- 因为第一个正因子是 $1$，那么根据题意，第一个质因子 $p_1\ge d+1$。

- 枚举第二个质因子时同理，记录一下第一个质因子 $p_1$，对于第二个质因子 $p_2$，$p_2\ge d+p_1$。

- 判断是否是奇数的话我打了个筛子。

代码就不放了，实现很简单。

$AC$ 记录：[$\text{Link}$](https://www.luogu.com.cn/record/45560036)

$$\texttt{The End.by UF}$$



---

## 作者：pengyule (赞：1)

对于最后的这个我们要输出的数，它应当有且仅有四个因数，因为如果少了就不符合条件，如果多了就一定有比它更小的满足条件的数。因此这四个因子应该分别是：$1$，一个质数，另一个质数，它本身。对于“一个质数”，我们查找大于等于 $1+d$ 的最小质数，记作 $a$，这就是它的第二小因数；对于“另一个质数”，我们查找大于等于 $a+d$ 的最小质数，记作 $b$，这就是它的第二大因数。则答案即为 $a\times b$。

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int c[30005],v[30005];
int main()
{
	v[1]=1;
	for(int i=2;i<=30000;i++) if(!v[i]){
		for(int j=i+i;j<=30000;j+=i) v[j]=1;
	}
	for(int i=30000;i>=2;i--){
		if(!v[i]) c[i]=i;
		else c[i]=c[i+1];
	}
	int T,d;
	cin>>T;
	while(T--){
		cin>>d;
		cout<<(long long)c[d+1]*c[c[d+1]+d]<<endl;
	}
	return 0;
}
```

---

## 作者：ytcccf (赞：0)

### 题意简述

给定一个正整数 $d$ ，你需要求出满足条件的最小的、至少有 $4$ 个正因子的、任意两个正因子的差大于等于 $d$ 的正整数 $a$ 。

### 题目分析

题目难度：普及/提高-

$\text{AC code}$ 时间复杂度最差大概是 $\Theta(Td\sqrt d)$

### 解题思路 

因为要求的正整数 $a$ 需要尽量小，所以其因子也需要尽可能小，由于每个因子之间差至少为 $d$，所以最终答案的因子若超过四个，得到的 $a$ 一定不会是最小的满足条件的，故最终得到的 $a$ 一定有且仅有四个因子。

又因为 $a$ 和 $1$ 也算作其中的两个因子，所以只需求出另外的两个因子即可，因为每个因子之间差至少为 $d$ ，所以两次从前一个因子加上 $d$ 的和向上枚举找质数，最后把两次找到的质数乘在一起就可以得到满足条件的最小的正整数 $a$ 了。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
bool is_prime(int a)//试除法判定素数 
{
	for(int i=2;i*i<=a;i++)
	{
		if(a%i==0) return false;
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);//cin、cout优化 
	int t,d,x,y;
	cin>>t;
	while(t--)
	{
		cin>>d;
		for(int i=d+1;;i++)//寻找第一个素因数，至少为 d+1 
		{
			if(is_prime(i))
			{
				x=i;
				break;
			}
		}
		for(int i=x+d;;i++)//寻找第二个素因数，至少为 x+d，(x为找到的第一个素因数) 
		{
			if(is_prime(i))
			{
				y=i;
				break;
			}
		}
		cout<<x*y<<endl;//输出两个质因数的和即可 
	}
	return 0;//完结撒花~ 
}
```

---

## 作者：Fa1thful (赞：0)

### 题意：
找一个不超过 $a$ 的一个最小的最少有四个因数且每个因数之间的差大于等于 $b$ 的数。
### 分析：
我们可以想到，有更多因数的数绝对比只有四个因数的要大（后面会有证明），也就是说四个因数的数一定是最优的。那么第一个想法就出来了：枚举两个因数，然后再判断相乘。

可是这个想法有一些问题，因为如果枚举的是合数，那么这个和数又能分解成两个或多个因数，所以枚举的因数必须是质数。

附：证明四个因数的数比五个因数的数小。

设 $c$ 为第二小的因数，$c+b$ 为第三大的因数，$c+2b$ 为第四小的因数。那么只有四个因数的数只有 $c,d$ 。

依题意，四个因数就是 $ac(c+b)$,五个因数就是$ac(c+2b)(c+b)$.


因为 $a,b,c$ 都大于$1$。所以四个因数一定小于五个因数

### 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
const int NR = 3e5 + 5;
bool prime[NR];                    //是否为素数 
inline void s()                    //暴力筛素数 
{
	for (int i = 2; i < NR; i++)
	{
		if (!prime[i])
		{
			for (int j = i + i; j < NR; j += i)
			{
				prime[j] = true;
			}
		}
	}	
}
int main()
{
	int T;
	cin >> T;
	while (T--)                           //多组数据 
	{
		int ans = 0, ans1 = 0;      
		int d;
		cin >> d;
		s();                                                 //寻找质数 
		for (ans = 1 + d; prime[ans]; ans++);                //找第一个因数 
		for (ans1 = ans + d; prime[ans1]; ans1++);           //找第二个因数 
		cout << ans * ans1 << endl;
	}
}
```


---

## 作者：B_lhx (赞：0)

[CF1474B Different Divisors](https://www.luogu.com.cn/problem/CF1474B)
====
题目翻译：
---
正整数$x$是$y$的因子,当$y$可以被$x$整除。举个例子，1是7的因子而3不是8的因子。

我们给了你一个正整数$d$并要求你找到最小的正整数$a$可以做到如下：

- 1.$a$有至少四个因数
    
- 2.$a$两个因数的差至少是$d$

思路：
---
从$d+1$往上枚举，由于差必须大于$d$，必须是质因数，枚举两次

代码：
---
```
#include <bits/stdc++.h>
using namespace std;
bool prime(int u){//质数判断
	for(int i = 2;i*i<=u;i++){//循环
		if(u%i==0){
			return false;
		}
	}
	return true;
}
int main(){
	int t;//t组数据
	cin>>t;
	while(t--){//循环
		int d;//d定义和输入
		cin>>d;
		int re=0,a=0;//记录与结果
		for(int i = d+1;i<1000000;i++){//第一个质因数
			if(prime(i)){ //如果是质数
				re=i;//记录并跳出
				break;
			}
		}
		a=re;//记录入答案
		for(int i = re+d;i<1000000;i++){//第二个质因数，必须与前面一个差d
			if(prime(i)){//如果是质数
				a*=i;//计算答案并跳出
				break;
			}
		}
		cout<<a<<endl;//输出答案
	}
    return 0;
}
```


---

