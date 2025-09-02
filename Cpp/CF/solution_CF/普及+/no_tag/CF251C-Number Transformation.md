# Number Transformation

## 题目描述

Little Petya likes positive integers a lot. Recently his mom has presented him a positive integer $ a $ . There's only one thing Petya likes more than numbers: playing with little Masha. It turned out that Masha already has a positive integer $ b $ . Petya decided to turn his number $ a $ into the number $ b $ consecutively performing the operations of the following two types:

1. Subtract 1 from his number.
2. Choose any integer $ x $ from $ 2 $ to $ k $ , inclusive. Then subtract number $ (a\ mod\ x) $ from his number $ a $ . Operation $ a\ mod\ x $ means taking the remainder from division of number $ a $ by number $ x $ .

Petya performs one operation per second. Each time he chooses an operation to perform during the current move, no matter what kind of operations he has performed by that moment. In particular, this implies that he can perform the same operation any number of times in a row.

Now he wonders in what minimum number of seconds he could transform his number $ a $ into number $ b $ . Please note that numbers $ x $ in the operations of the second type are selected anew each time, independently of each other.

## 说明/提示

In the first sample the sequence of numbers that Petya gets as he tries to obtain number $ b $ is as follows: 10 $ → $ 8 $ → $ 6 $ → $ 4 $ → $ 3 $ → $ 2 $ → $ 1.

In the second sample one of the possible sequences is as follows: 6 $ → $ 4 $ → $ 3.

## 样例 #1

### 输入

```
10 1 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6 3 10
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1000000000000000000 1 3
```

### 输出

```
666666666666666667
```

# 题解

## 作者：Leap_Frog (赞：4)

### PS.
刚开始没开longlong，结果样例都没过。。。

### Problem.
具体可以见题目翻译（是我翻的，应该写的还好吧~~心虚~~

### Solution.
首先，我们第一个操作基本不用考虑的。  
那么我们来考虑第二个操作。  

第二个操作的本质是把$n$变成比$n$小的最大的$t$的倍数。  
然鹅$t$不是固定的，是$[2,k]$之间的一个整数。（1显然没用  
那么我们就没法算了吗？  
不，等等，我们发现$k\leq15$！  
那么$\text{lcm}\ 1,2...k$肯定是$t$的倍数，而那个$\text{lcm}$也不大，大概是$3\times10^5$左右。  
那么也就是说，如果我们不断进行第二个操作，肯定会走到比$n$小的最大的$\text{lcm}$的倍数那里的。  
而且这个肯定是最优的走法（肯定比一直减一好  

那么我们就可以首先先把整数域按照整除$\text{lcm}$的结果分层。  
- 如果$a$和$b$在同一层，那么就可以用一种方法（挖个坑）来做。  
- 如果$a$和$b$不在同一层，那么就首先先把$a$变成比它小的最大$\text{lcm}$倍数，  
然后再变道比$b$大的最小$\text{lcm}$倍数，然后变成$b$。   

于是，我们便可以把$a$和$b$的数据范围压缩成了$3\times10^5$。  

然后再来填一下上面那个坑，如何求$a$到$b$最少要走几步。  
因为$a$和$b$的范围被压缩了，所以我们可以考虑用dp来做。  
设$f[i]$表示从$a$出发，走到$i$的最少步数。  
那么$f[i]$可以转移到$f[i-1]$以及$f[i-i\ \text{mod}\ t]$。  
状态转移很显然，虽然$a$可能不同，需要跑不止一遍的dp。  
但是那也是常数的问题了。  

然后这题就做完了，完结撒花，无耻求赞。  

### Coding.
~~哦，还没玩，接下来才是某些人最希望的重头戏！~~  
**上代码，详情见代码注释**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,k,lcm,ans=0,f[400005];
inline long long gcd(int a,int b) {return a==0||b==0?a:gcd(b,a%b);}
//求lcm时要用到的gcd
inline long long dp(int a,int b)//指从b到a需要用几步
{//把dp封装了一下，虽然常数大点，但是代码更简洁
	memset(f,0x3f,sizeof(f)),f[b]=0;//初始化，从b到b需要0步
	for(int i=b;i>a;i--)//迭代
	{
		f[i-1]=min(f[i]+1,f[i-1]);//转移到f[i-1]
		for(int j=2;j<=k;j++) if((i-i%j)>=a) f[i-i%j]=min(f[i-i%j],f[i]+1);//转移到f[i-i%j]
	}
	return f[a];//返回答案
}
int main()
{
	scanf("%lld%lld%lld",&a,&b,&k),lcm=1;//读入，初始化lcm
	for(int i=1;i<=k;i++) lcm=lcm/gcd(lcm,i)*i;//求lcm
	if(a/lcm==b/lcm) return printf("%lld\n",dp(b%lcm,a%lcm)),0;
//这个是当a和b在同一个阶段时，直接%后dp就好了
	return printf("%lld\n",dp(0,a%lcm)+1ll*(a/lcm-b/lcm-1)*dp(0,lcm)+dp(b%lcm,lcm)),0;
//当a和b在不同阶段时，按照上面的第二种情况分别加起来也就好了
}
```
**真·完结撒花**

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$

---
### 解题思路：

操作一平凡，关键看操作二。

恒等变形，有：$a-a\bmod t=a-(a-a\times \left\lfloor \dfrac{a}{t}\right\rfloor)=a\times \left\lfloor \dfrac{a}{t}\right\rfloor$。

也就是每一次都向下跳到比这个数小的最大的 $t$ 的倍数。可以发现，如果一直进行这个操作，直到进行任何操作都不能更改数值，不得不用操作一为止，得到的数一定是 $\text{lcm}_ {i=1}^k i$。而这样的操作再从 $t\times\text{lcm}_ {i=1}^k i$ 到 $(t-1)\times\text{lcm}_ {i=1}^k i$ 进行的操作是重复的，可以直接跳过。而 $\text{lcm}_ {i=1}^{15}=360360$，是一个很小的数。

逆向操作可以推到同样的结论，这里不赘述。

---
然后用动态规划计算一下就好了。这里也有两种方法，刷表法和填表法。刷表法平凡，不赘述。填表法其实也平凡，但没有人说过，所以以下是填表法的内容。

设 $f_i$ 表示从 $a$ 到 $i$ 至少需要几步。考虑 $i$ 可以从哪些点转移过来，首先肯定是根据操作一能到达的点，也就是 $i+1$。

设 $i$ 最大的因数为 $k$，那么任意的 $[i,i+k)$ 用操作二，设定参数为 $k$，就一定能到达 $i$。对于 $i$ 的其它因数，他们能做的 $k$ 一定能做，可以不用考虑。

转移一下就好了。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long a,b,k,LCM,f[360365],ans;
long long gcd(long long a,long long b){
	if(b==0)return a;
	return gcd(b,a%b);
}/*
long long calc(long long a,long long b){
	f[a]=0;
	for(int i=b;i<a;i++)
	f[i]=9223372036854775807;
	for(int i=a;i>=b;i--){
		f[i-1]=min(f[i]+1,f[i-1]);
		for(int j=1;j<=k;j++){
			f[i-i%j]=min(f[i-i%j],f[i]+1);
		}
	}
	return f[b];
}//刷表法 */
long long calc(long long a,long long b){
	f[a]=0;
	for(int i=b;i<a;i++)
	f[i]=9223372036854775807;
	for(int i=a-1;i>=b;i--){
		f[i]=min(f[i],f[i+1]+1);
		int flag=0;
		for(int j=k;j>=1;j--){
			if(i%j==0||flag==1){
				flag=1;
				f[i]=min(f[i],f[i+j-1]+1);
			}
		}
	}
	return f[b];
}//填表法 
int main(){
	scanf("%I64d%I64d%I64d",&a,&b,&k);
	LCM=1;
	for(int i=1;i<=k;i++)LCM=i/gcd(LCM,i)*LCM;
	if(a/LCM==b/LCM)ans=calc(a%LCM,b%LCM);
	else ans=calc(a%LCM,0)+(a/LCM-b/LCM-1)*calc(LCM,0)+calc(LCM,b%LCM);
	printf("%I64d",ans);
	return 0;
}
```


---

