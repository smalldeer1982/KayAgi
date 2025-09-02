# Frog Jumping

## 题目描述

对于给定的$a,b,k$，初始状态$x=0$，第$i$次操作满足以下规则：  
- $i$为奇数，$x=x+a$  
- $i$为偶数，$x=x-b$  

求$k$次操作后$x$的值

## 样例 #1

### 输入

```
6
5 2 3
100 1 4
1 10 5
1000000000 1 6
1 1 1000000000
1 1 999999999
```

### 输出

```
8
198
-17
2999999997
0
1
```

# 题解

## 作者：damage (赞：1)

~~$\sout{CF}$最近几题怎么都是数学题~~

# 题意

珂朵莉站在数轴原点，有$t$组数据，给定三个整数$a$，$b$，$k$，珂朵莉在数轴上跳$k$次，跳的规则如下：

1. 若已经跳了偶数次（包括初始时），则向右跳$a$格

2. 若已经跳了奇数次，则向左跳$b$格

对于每组数据，输出一行表示珂朵莉跳了$k$步后在数轴上的坐标。

---

# 题解

### 直接膜你

但是$t$最大为$10^{3}$，$k$最大为$10^{9}$，所以直接膜你当然会**炸**！

所以：

### 数学方法

对于每个$k$，会有两种情况：

1. $k$为偶数，因为每跳两次就相当于向右跳了$a-b$格（等于坐标加了$a-b$）。共有$\frac{k}{2}$组，所以珂朵莉的坐标就在$\frac{1}{2}k(a-b)$。

2. 否则$k$为奇数，这时可以把$k$拆成$k-1$和$1$，因为奇数减奇数等于偶数，而$1$就等于坐标增加$a$，所以答案就是$\frac{1}{2}(k-1)(a-b)+a$。不过因为整形变量$k$为奇数时除以$2$就等于$k-1$除以2。**所以就等于第一种情况的答案$+a$**

## 不过注意答案要开$long\ long$
---

# 代码

```cpp
#include<cstdio>
int t;
long long a,b,k,res;
int main()
{
	scanf("%d",&t);
	while(t--) //多组数据
	{
		scanf("%lld%lld%lld",&a,&b,&k); //输入
		if(k&1ll) res=a; //如果k是奇数答案就增加a
		else res=0; //否则答案置零
		printf("%lld\n",res+(a-b)*(k>>1ll)); //如[题解]所说，此处的运算如果不懂的大佬们可以看底下的说明（就是位运算）
	}
	return 0;
}
```

核心代码只有一行：
```cpp
printf("%lld\n",((k&1ll)? a:0)+res+(a-b)*(k>>1ll));
```

---

## 说明

关于本篇涉及到的位运算的讲解

#### ```x&1```的返回值只有两种

1. 当$x$为奇数时，返回$1$

2. 否则返回$0$

此处就等于$x\%2$（或$x\%2==1$）

其实任何$x\%2^{i}$都可以转化为$x\&(2^{i}-1)$

#### ```x>>1```表示```x/2```，其实$x$>>$i$ $=\frac{x}{2^{i}}$。

---

## 完结

---

## 作者：zsc2003 (赞：1)

2018.11.16 codeforces div3 A

### 题目大意

一只青蛙的初始位置在一个数轴的 $ 0 $ 处，现在青蛙要跳跃，它的跳跃满足一下规则：

- 假设当前青蛙位于数轴上的 $ x $ 处，那么：

- 如果该青蛙已经跳了偶数次(不算现在正要跳的这步)，那么这只青蛙要跳去 $ x+a $处

- 否则青蛙跳去 $ x-b $处

现在读入 $ t $

接下来的 $ t $ 行，每行3个整数 $ a,b,k $ ，$ a,b $ 见上面所说, $ k $ 表示这只青蛙一共要跳 $ k $ 次
。问跳 $ k $ 次后青蛙所在的位置

### 思路

一看 $ k $ 的数据范围,肯定是需要 $ \Theta (1) $ 来算出答案的。所以只需对k分类讨论一下

- 若k为偶数，答案只需为 $ ans= a*k-b*k $

- 若k为奇数,则需要比偶数的情况多跳一次 $ a $ ,所以答案为 $ ans=a*k-b*k+a$

注意开 $ long long $ 以免炸 $ int $ 即可
### 代码
```cpp

 #include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read()//读入优化
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
int t;
ll ans,a,b,k,f; //因为答案有可能相乘后爆int，所以使用long long 储存
int main()
{
	t=read();
	while(t--)
	{
		a=read(),b=read(),k=read();
		f=k;
		k>>=1;
		ans=k*a;
		ans-=k*b;
		if(f&1)//如果读入的k为奇数
			ans+=a;
		printf("%I64d\n",ans);//codeforces上输出long long 要使用 %I64d	
	}
	return 0;
}
```

---

## 作者：Chtholly_L (赞：0)

### 题意：

给你三个数 $a$，$b$ 和 $k$，和一个初始状态 $x=0$，进行如下 $k$ 次操作：

* 若操作次数为奇数，$x=x+a$

* 若操作次数为偶数，$x=x+b$

求最后 $x$ 的值。题目有多组数据。

---

### 分析：

看下数据范围，$k≤10^9$，贸然模拟肯定会 TLE，那么，我们只能靠数学只是来解决这道题。

先对要求的操作进行模拟，用样例数据 $5$ $2$ $3$，我们可以得到这个式子：$0+5-2+5=8$

我们可以发现，操作是在循环进行的，由此我们可以直接用 $a-b$ 得出每两次操作会改变的值，而且这个值是永远相等的。

对于操作次数是偶数，我们可以直接将操作次数除二，再乘 $a-b$，就可以得到最终答案。即：

$$\dfrac{k}{2} \times (a-b) $$

而对于操作次数是奇数，我们要先将操作次数整除二，乘 $a-b$，再加上 $a$ 的值。即：

$$\left\lfloor\dfrac{k}{2}\right\rfloor\times (a-b)+a$$

---

### 代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        long long a,b,k;
        cin>>a>>b>>k;
        if(k%2==0){  //操作次数为偶数
            cout<<k/2*(a-b)<<endl;
        }
        else {  //操作次数为奇数
            cout<<k/2*(a-b)+a<<endl;
        }
    }
    return 0;
}
```


---

## 作者：Tiago (赞：0)

## 题意简述

给你三个数 $a$，$b$，$k$，并定义一个数 $sum$（初始值为 $0$），共 $k$ 次操作。

第 $i$ 次操作如下（操作为 $1 \sim k$）：

- $i$ 为奇数，$sum=sum+a$

- $i$ 为偶数，$sum=sum-b$

求 $sum$ 的值。

共 $T$ 组数据。

## 题目分析

首先，直接模拟肯定会超时，所以考虑数论。

拿 `5 2 3` 举例。

| 操作次数 $i$ | $sum$ | $+a$ 或 $-b$ |
| -----------: | -----------: | -----------: |
| $1$ | $5$ | $+a$ |
| $2$ | $3$ | $-b$ |
| $3$ | $8$ | $+a$ |

剩下的样例可以自己去模拟，这里就不赘述了。

于是，我们不难发现：

1. 当 $k$ 为奇数时，共要加 $(k+1) \div 2$ 次 $a$，减 $(k-1) \div 2$ 次 $b$

2. 当 $k$ 为偶数时，共要加 $k \div 2$ 次 $a$，减 $k \div 2$ 次 $b$

所以代码也就显然了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//要开 long long

inline int read()
{
	register int x=0,f=0;register char ch=getchar();
	while(ch<'0' || ch>'9')f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
void work()
{
	int a=read(),b=read(),k=read();
	if(k%2==1)cout<<(((k+1)/2)*a-((k-1)/2)*b);//k 为奇数
		else cout<<((k/2)*a-(k/2)*b);//k 为偶数
	cout<<endl;
}
signed main()
{
	int T=read();
	while(T--)work();

	return 0;
}
```

---

## 作者：Aw顿顿 (赞：0)

直观理解。

对于每两个抱对的操作（即 $i,i+1$），结果都会 $+a-b$，那么对于 $k$ 为偶数的情况，就是 $k\div 2$ 的操作次数，每次 $+a-b$ 也就是：

$$\dfrac{k(a-b)}{2}$$

那么考虑为奇数的情况，依然很简单，在原有的基础上再加 $a$ 即可，也就是：

$$\left\lfloor\dfrac{k}{2}\right\rfloor\times(a-b)+a$$

那么综合一下就是：

$$\left\lfloor\dfrac{k}{2}\right\rfloor\times(a-b)+a\times\left[k\bmod2=1\right]$$

最后面是一个谓词函数，即当 $k\bmod2=1$ 成立时值为 $1$，反之为 $0$，加上 $\times a$ 的权值即可得到想要加上的附加信息。

虽然说式子看着有些麻烦，但是代码实现起来很简单，这里不多赘述。

---

## 作者：Eason_AC (赞：0)

## Content
在一个数轴上有一个动点，初始时在 $0$ 这个位置上，接下来有若干次操作，对于第 $i$ 次操作：

- 如果 $i$ 是奇数，那么动点往右移 $a$ 个单位。
- 如果 $i$ 是偶数，那么动点往左移 $b$ 个单位。

现在有 $t$ 次询问，每次给定 $a,b,k$ 三个数（其中 $a,b$ 含义如上所述），求经过 $k$ 次操作后动点所在的位置。

**数据范围：$1\leqslant t\leqslant 10^3,1\leqslant a,b,k\leqslant 10^9$。**
## Solution
这道题目如果用暴力的话显然爆炸，所以我们来看有什么规律。自己画个数轴，跑几下之后就发现：**如果操作的次数 $k$ 是偶数，那么有 $\dfrac{k}{2}$ 次交替向右移和向左移的操作，答案就是 $\dfrac{k(a-b)}{2}$。** 那么奇数次也就就很简单了，相当于在偶数次的基础上再往右移一次，那么答案就是 $\left\lfloor\dfrac{k}{2}\right\rfloor(a-b)+a$。

注意如果直接相乘的话答案会很大，要开 $\texttt{long long}$。建议开变量的时候直接将 $a,b,k$ 开成 $\texttt{long long}$ 类型的，这样可以省去强制转化这个部分。
## Code
```cpp
int t;

int main() {
	getint(t);
	while(t--) {
		ll a, b, k, ans;
		getll(a), getll(b), getll(k);
		if(k % 2)	ans = a * (k / 2 + 1) - b * (k / 2);
		else	ans = a * k / 2 - b * k / 2;
		writell(ans);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：末置lzy (赞：0)

~~个人感觉的规律，CF不开long long绝对炸~~

# CF1077A题解
### 题目描述翻译

一只青蛙现在位于坐标轴 x 的0点上。它通过以下算法跳跃: 第一次跳跃是右边的 a 单位，第二次跳跃是左边的 b 单位，第三次跳跃是右边的 a 单位，第四次跳跃是左边的 b 单位，依此类推。

形式上: 

如果青蛙跳跃了偶数次(在当前跳跃之前) ，它将从当前位置 x 跳跃到位置 x + ax + a; 否则它将从当前位置 x 跳跃到位置 x-bx-b。你们的任务是计算跳 k 次后青蛙的位置，但是... 还有一件事。你看到的是不同的青蛙，所以你必须回答独立的问题。

#### 分析

这个题其实是一个数学问题，模拟的话会出大问题。（效率太低了）

~~别问为什么我知道，问就是我自己试了~~

由翻译我们可以看出来，这个题的主要地方就是判断跳跃次数是奇数还是偶数，这个代码还是很好打的
```cpp
k%2==0;
```
或者
```cpp
k%2==1;
```
~~以上废话~~

当跳了偶数次时，答案就是x(0)加上(a-b)*(k/2)，

当跳了奇数次时，但就是x(0)加上(a-b)*((i+1)/2)-b.(先多操作一次，再把多操作的部分减去)

### so

## AC CODE

```cpp
#include<bits/stdc++.h>//无解万能头
using namespace std;
int main()
{
	long long n,x,k,a,b;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>k;
		if(k%2==0) x=(a-b)*(k/2);
		if(k%2==1) x=(a-b)*((k+1)/2)+b;//与分析一致
		cout<<x<<endl;
	}
	return 0;//华丽结束
}
```

**好啦，本片题解就结束了**

温馨提示：不要抄题解。~~小心灰名~~

---

## 作者：灵光一闪 (赞：0)

~~看看题解区，感觉好像就我的简单点……~~

再次提醒：  
# 十年OI一场空，不开long long一场空

核心代码： ``ans=a*((c+1)/2)-b*(c/2);``

先贴代码，讲解在后面
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;

int main()
{
    long long n;
    cin>>n;
    long long a,b,c;
    long long ans=0;
    for(int i=0;i<n;i++)
    {
        cin>>a>>b>>c;
        ans=a*((c+1)/2)-b*(c/2);
        cout<<ans<<endl;
    }
    return 0;
}
```


------------

关于核心代码``ans=a*((c+1)/2)-b*(c/2);``的讲解：  
首先，我们可以看出``((c+1)/2)``是个上取整，因为如果c是奇数又不上取整的话，~~吼吼吼~~，WA等着你。

然后，为什么后面不要上取整呢，因为如果c是奇数的话，最后一次不是``-b``而是``+a``。

最后，把``a*((c+1)/2)-b*(c/2)``的值赋给ans并输出~

# end.

---

