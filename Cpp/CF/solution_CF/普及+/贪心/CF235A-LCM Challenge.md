# LCM Challenge

## 题目描述

Some days ago, I learned the concept of LCM (least common multiple). I've played with it for several times and I want to make a big number with it.

But I also don't want to use many numbers, so I'll choose three positive integers (they don't have to be distinct) which are not greater than $ n $ . Can you help me to find the maximum possible least common multiple of these three integers?

## 说明/提示

The least common multiple of some positive integers is the least positive integer which is multiple for each of them.

The result may become very large, 32-bit integer won't be enough. So using 64-bit integers is recommended.

For the last example, we can chose numbers $ 7 $ , $ 6 $ , $ 5 $ and the LCM of them is $ 7·6·5=210 $ . It is the maximum value we can get.

## 样例 #1

### 输入

```
9
```

### 输出

```
504
```

## 样例 #2

### 输入

```
7
```

### 输出

```
210
```

# 题解

## 作者：chinaxjh (赞：18)

# 前言：
这是一道不错的数论题，对于最大公倍数的考察比较到位，适合普及选手练习。
# 题面
找到3个不超过$n$的正整数（可以相同），使得它们的$lcm$（最小公倍数）最大。输出最大的$lcm$
# 分析
最容易想到的应该是暴力枚举这三个整数，但时间复杂度是$O(n^3)$，对于$10^6$必然会超时，所以我们需要用数论优化
# 高能分析时间
## 写在分析之前
其他题解对数学的推导比较快，有的更是直接带过，这里我争取对推导过程进行较为详细的解析，方便大家理解。
## 开始分析
### $lcm$咋么算
啥都不说了，丢公式

$lcm(n,m)=n*m/gcd(n,m)$
(gcd为最大公约数)

### 先从很简单的定理引入
如果我们有两个整数$n$和$m$($n$>$m$)，它们的最大公约数为$k$，则$k$必然$n-m$的约数

这个结论不需要太多解释，这是最大公约数的一个定理。

~~但这与我们需要解决的问题有什么关系哪~~

我们可以从中得出几个定理，相邻的两个数必定互质（差为1），当一个数$n$为奇数时$n$和$n-2$必定互质（差为2且$n$ $mod$ 2!=0）......
### 当$n$为奇数时
由之前我们得出的结论可以得到$n$,$n-1$,$n-2$三个数，$n$的$n-1$必定互质,$n-1$和$n-2$必定互质，而$n$因为是奇数，所以$n$和$n-2$也互质。

再由$lcm$的公式可得这三个数相乘必然是最大的$lcm$（最好情况就是3个数都互质且乘积最大）

公式

$lcm_{maxn}$=$n$*$(n-1)$*$(n-2)$
### 补充
讲到这里，有些同学可能会问，问什么它们的最大公约数必须是1哪？我们可以简单的通过$lcm$的公式来了解一下

很显然，当它们$gcd$不为1时，最小的$gcd$为2，而当n稍微大一点时我们可以通过调整一个乘数的大小来避免除以$gcd$的情况，而且调整需要的量是很小的，代价远远小于除以2及以上的数，所以这几个数最好互质并且最大
### 当$n$为偶数时
这时的情况就复杂了，因为我们需要讨论两种情况。
#### 想法1，将偶数化为奇数
显然，当$n$为偶数是，$n-1$必定为奇数，这样我们就可以套用我们之前得出来的公式

$lcm_{maxn}$=$(n-1)$*$(n-2)$*$(n-3)$
#### 想法2,调整并寻求互质
由于$n$为偶数，所以$n-1$与$n-3$必然互质，$n$的$n-1$必定互质，而当$n$与$n-3$互质时，得出来的必然是最大值（因为除去$n-2$外，这三个数最大）

$lcm_{maxn}$=$n$*$(n-1)$*$(n-3)$

#### 问题
如果$n$与$n-3$不互质怎么办，要不要讨论$n-5$，$n-7$之类的情况哪，其实是不需要的，我们可以证明

$(n-1)$*$(n-2)$*$(n-3)$>$n$*$(n-1)$*$(n-5)$（其他情况比这个更小，就不用讨论了）

两边同时除以$n-1$得

$(n-2)$*$(n-3)$>$(n-1)$*$(n-5)$

将括号展开

$n^2$-$5n$+$6$>$n^2$-$6n$+$5$

加减消元得

$n$>-$1$

因为$n>0$，所以式子恒成立

证毕，所以得出结论

$lcm_{maxn}$=$(n-1)$*$(n-2)$*$(n-3)$($n$与$n-3$不互质时)

$lcm_{maxn}$=$n$*$(n-1)$*$(n-3)$($n$与$n-3$互质时)

> 讨论结束了，撒花

# TIPS
注意$n<3$的情况

# AC CODE
```pascal
var
  lcm,max:int64;
  n,i,j,k:int64;//要开int64
function gcd(x,y:int64):int64;
begin
  if y=0 then exit(x);
  exit(gcd(y,x mod y));
end;//求最大公约数，其实可以用同余来简单判断，这样有点复杂
begin
  readln(n);
  if n<3 then
  begin
  writeln(n);
  halt;
  end;//特殊情况
  if n mod 2=1 then
  begin
   writeln(n*(n-1)*(n-2));
halt;
end;//奇数
  max:=(n-1)*(n-2)*(n-3);//情况1
  i:=n;
  j:=n-1;
  k:=n-3;
  lcm:=i*j div gcd(i,j);
  lcm:=lcm*k div gcd(lcm,k);
  if lcm>max then max:=lcm;//偶数情况分别讨论
  writeln(max);//输出最大值
end.
```
# 总结
此题难度不大，但要分情况讨论，需要细心一点把情况讨论全，否则很容易WA，代码实现难度不高，是一道偏重思维的题。

---

## 作者：FCB_Yiyang2006✈ (赞：14)

## 1.做这道题前需要掌握
> ##### (1) $lcm$ 的一些基本性质
> ##### (2) $lcm$ 的一些基本求法
> ##### (3) $gcd$ 的一些基本性质
> ##### (4) 辗转相除

## 	2.一个小引理
因为此题是求三个数 $lcm$, 所以珂以随意取三个数的 $lcm$ 来考虑。

### step1
不妨设三个数 $a$,$b$,$c$。
### step2
令：

$gcd(a,b)=p$, $gcd(a,c)=q$, $gcd(b,c)=k$， $gcd(a,b,c)=g$

### step3
先可考虑 $a$,$b$。

若：

$a=p*{a}'$

$b=p*{b}'$

则

$lcm(a,b)=p*{a}'*{b}' $

进而推广至三个数：

$lcm(a,b,c)=lcm(lcm(a,b),c)=lcm(p*{a}'*{b}',c)=(a*b*c)/(p*q*k)*g$

(就直接连等了，各位巨佬珂以自己推一推)

### 所以我们得到结论
三个数的 $lcm$ 的大小与 三数乘积 和 两两之间的 $gcd$ 有关。

## 3.进入正题
题目描述清晰明了，不用多做解释。

### 思路

在 $n$ 个数中满足

1.三个数乘积大

2.三个数两两的 $gcd$ 尽可能小

分成两种情况：

#### 1. $n$ 为奇数

乘积最大的三个数：$n$, $n-1$, $n-2$。

在考虑这三个数的 $gcd$:

根据辗转相除性质:

$gcd(n,n-1)=1$

$gcd(n-1,n-2)=1$

又因为 $n$ 为奇数

$gcd(n,n-2)=1$

所以这三个数也两两互质。

那我们就当然输出 $n*(n-1)*(n-3)$ 了！

#### 2. $n$ 为偶数(有点复杂)

我们还是可以考虑乘积最大的三个数：$n$, $n-1$, $n-2$。

但是此时就翻车了...

因为 $n$, $n-2$ 都为偶数

所以 $gcd(n,n-2)=2$

输出时就是：$n*(n-1)*(n-3)/2$

#### 因为这里出现除以2，$n$ 较大时，$lcm$ 较小，所以我们问：还有没有更大的结果呢？

我们可以把其中一个偶数换掉换成略小的一个

将 $n-2$ 换为 $n-3$

这在 $n$ 较大时且 $n$ 不整除3时显然可以输出

$n*(n-1)*(n-3)$

#### 再问：$n$ 较大时，且 $n$ 整除3时，有木有更大的结果？

当然是有的，我们还可以将 $n$ 变为 $n-1$ 就与奇数情况相同了。

输出：

$(n-1)*(n-2)*(n-3)$

#### 当然，保险来说，$n$ 为偶数的情况就上述的三种情况取一次$MAX$(因为 $n$ 较小时有些玄学)

## 4.注意事项

>#### 1.$n$ 小于3时会出现负数，单独考虑。
>#### 2.此题结果要开 $longlong$。
>#### 3.$C++$ 库中的 $max$ 函数两个参数都是 $int$, 所以我们要手写 $MAX$ 函数。

## 5.上代码
```
#include<bits/stdc++.h>
using namespace std;
long long n;//保险写法，类型转换不出错
long long Max(long long a,long long b)//手写Max
{
	if(a>b)
	{
		return a;
	}
	return b;
}
int main()
{
	scanf("%lld",&n);
	if(n==1)
	{
		printf("1");
		return 0;
	}
	if(n==2)
	{
		printf("2");
		return 0;
	}//特殊考虑
	if(n%2==1)
	{
		printf("%lld",n*(n-1)*(n-2));
	}//奇数情况
	else
	{
		if(n%3!=0)
		{
			printf("%lld",Max(n*(n-1)*(n-2)/2,n*(n-1)*(n-3)));
		}//偶数不整除3情况
		else
		{
			printf("%lld",Max(n*(n-1)*(n-2)/2,Max((n-1)*(n-2)*(n-3),n*(n-2)*(n-3)/3)));
		}//偶数整除3的情况
	}
	return 0;
}
```
(蒟蒻心地善良，可以直接 $AC$)
## 6.最后

#### 感谢CF题库供题，洛谷管理员维护和翻译者的翻译

因为我比较弱，有些讲得不清楚的地方敬请谅解，可以在评论区提出。(~~不要忘了点赞鼓励哦~~)

祝各位早日 $AC$ 本题！

---

## 作者：溪水瑶 (赞：5)

## 这题好毒瘤啊 
（特别是long long的坑，调了半天没调好！！）
先将你特判一下小于3的话直接输出就是惹，不是的话就判断一下它能不能被2整除如果不能就直接输出n*（n-1）*（n-2）否则进行枚举
枚举核心代码：
```cpp
	LL sum=0;
	sum=i*j/gcd(i,j);
	sum=sum*k/gcd(sum,k);
	ans=max(ans,sum);
```
求三个数的最小公倍数。
## 以下是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL ans,n;
LL gcd(LL a,LL b){
	if(!b)return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%lld",&n);
	if(n<=2){
		printf("%lld",n);
		return 0;
	}
	if(!(n%2)){
		for(LL i=n;i>=n-100;i--){
			if(i==0)break;
			for(LL j=n;j>=n-100;j--){
				if(j==0)break;
				for(LL k=n;k>=n-100;k--){
					if(k==0)break;
					LL sum=0;
					sum=i*j/gcd(i,j);
					sum=sum*k/gcd(sum,k);
					ans=max(ans,sum);
				}
			}
		}
	}
	else ans=(n*(n-1)*(n-2));
	printf("%lld",ans);
	return 0;
}
```
本章完结QAQ

---

## 作者：WCG2025 (赞：4)

这道题的确是一道暴力枚举题，但是他有一定的技巧性

首先是如何枚举的问题：这里就要用到一点贪心的思想，三个数，如果想要最小公倍数最大，那么这三个数肯定就要互质，这里就不严格证明了。

但是，如果只是单纯的暴力枚举，你会发现在CF上过不了，因为N的范围甚至可以达到10^6，~~怕是只有超算一秒钟才算的出来~~
明显的这是一道n^3方问题，自然就要将枚举范围压缩在100以内，于是我们将枚举范围从n到1缩小到了n到n-100以内过得了了，但这明显是运气

仔细分析后，我们发现如果n是奇数，直接n*（n-1）*(n-2)，他们一定互质，
如果n是偶数，就相对麻烦：如果n和n-2互质，那么答案就是n*(n-1)*(n-2)，因为他们是最大的3个互质的数。但是n和n-2肯定不互质，那么答案是(n-3)*(n-1)*(n-2)，因为n-1之后肯定是奇数了，用奇数的方法思想就可以推出
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long ans;
inline long long read()
{
    char ch=getchar();
    long long x=0,f=1;
    while(ch<'0'&&ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar(); 
    } 
    return x*f;
}
long long gcd(long long x,long long y)
{
    if(y==0)
    return x;
    else
    return gcd(y,x%y);
}
long long solve(long long i,long long j,long long k)
{
    long long temp=0;
    temp=i*j/gcd(i,j);
    temp=temp*k/gcd(temp,k);
    return temp;
}
int main()
{
    n=read();
    int f=100;
    for(long long i=n;i>=n-f&&i>=1;i--)
    for(long long j=n;j>=n-f&&j>=1;j--)
    for(long long k=n;k>=n-f&&k>=1;k--)
        ans=max(ans,solve(i,j,k));
    printf("%lld",ans);
    return 0;			
} 
```
这个是暴力代码，其实这个f甚至可以压缩至3，但是以防万一，开到了一百

---

## 作者：alan1118 (赞：3)

## 题意

给定一个正整数 $n$，请你确定不大于 $n$ 的三个正整数的最小公倍数的最大可能是多少。

## 思路

这里我分享我的一个想法，代码很简短，目前没有看到题解区有这个思路。

显而易见的是，我们不能选相同的数，否则就白选了。有了这一点，问题就很好解决了。

首先要注意的第一点是要特判 $n<3$ 的情况，这时直接输出 $n$ 即可。

接着如果 $n$ 是奇数，直接输出 $n\times (n-1)\times (n-2)$。因为这三个数中必定有两个奇数，它们相差 $2$，所以他们必定没有除 $1$ 外的公约数，而相邻的两个数一定互质，所以这三个数必定两两互质。

如果 $n$ 是偶数，正常来说与上面同理，选出两奇一偶，输出 $n\times (n-1)\times (n-3)$ 即可。但有个特殊情况，就是 $n$ 是 $6$ 的倍数的时候，$n$ 和 $n-3$ 有一个公因子 $3$ 所以这时候要输出 $(n-1)\times (n-2)\times (n-3)$。

以上就是完整思路，最后记得开 long long。

## Code
``` cpp
#include <iostream>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    if(n < 3) return cout << n << endl, 0;
    if(!(n % 2))
    {
        if(n % 6) return cout << n*(n-1)*(n-3) << endl, 0;
        else return cout << (n-1)*(n-2)*(n-3) << endl, 0;
    }
    else return cout << n*(n-1)*(n-2) << endl, 0;
    return 0;
}
```
是不是非常简单！

---

## 作者：yzx72424 (赞：1)

暴力枚举。

思路：枚举i,j，k三个数（满足互质。有点贪心的思想，如果不互质的话ans一定更小），每次相乘的值取max即可。

**注意点：开 long long!**

---

## 作者：K0stlin (赞：0)

## O(N)暴力

首先来看
 _找到2个不超过n的正整数（可以相同），使得它们的lcm（最小公倍数）最大_
的解:n*(n-1),这是最大的一对互质。

同理，我们在将这个确定了后，再枚举剩下的一个数即可。

### 但是

可能n的约数很多，互质的数很少。可以再多做几组，如：(n-1)*(n-2) ......

讲一个求解公式：n*m=gcd(n,m)*lcm(n,m)

这个用小学的同除法能证。（在A,B,C处用）

CODE:
```cpp
#include<cstdio>
int n;
long long ans,k,maxn;
long long gcd(long long a,long long b){return b==0?a:gcd(b,a%b);}
int main(){
	scanf("%d",&n);
	if(n<=2){printf("%d\n",n);return 0;}//特判，防止为0或负数
    	//当n=0,1,2时三个n为最优解
	ans=1ll*n*(n-1);//第一组
	for(int i=1;i<=n;++i){
		k=gcd(ans,1ll*i);
		if(ans*1ll*i/k>maxn)maxn=ans*1ll*i/k;//maxn为lcm
        //A
	}
	ans=1ll*(n-1)*(n-2);//第二组
	for(int i=1;i<=n;++i){
		k=gcd(ans,1ll*i);
		if(ans*1ll*i/k>maxn)maxn=ans*1ll*i/k;//同上
        //B
	}
	/*
	ans=1ll*(n-2)*(n-3);//第三组
	for(int i=1;i<=n;++i){
		k=gcd(ans,1ll*i);
		if(ans*1ll*i/k>maxn)maxn=ans*1ll*i/k;
        //C
	}
    此组最好加上，但止步于此之后是最佳的。
	*/
	printf("%lld\n",maxn);
	return 0;
}

```
-完-

---

