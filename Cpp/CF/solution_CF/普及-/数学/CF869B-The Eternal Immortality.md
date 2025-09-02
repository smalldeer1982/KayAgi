# The Eternal Immortality

## 题目描述

Even if the world is full of counterfeits, I still regard it as wonderful.

Pile up herbs and incense, and arise again from the flames and ashes of its predecessor — as is known to many, the phoenix does it like this.

The phoenix has a rather long lifespan, and reincarnates itself once every $ a! $ years. Here $ a! $ denotes the factorial of integer $ a $ , that is, $ a!=1×2×...×a $ . Specifically, $ 0!=1 $ .

Koyomi doesn't care much about this, but before he gets into another mess with oddities, he is interested in the number of times the phoenix will reincarnate in a timespan of $ b! $ years, that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/e1b2fb98f4ea484515a807ebc0e143dd3b54b9f1.png). Note that when $ b>=a $ this value is always integer.

As the answer can be quite large, it would be enough for Koyomi just to know the last digit of the answer in decimal representation. And you're here to provide Koyomi with this knowledge.

## 说明/提示

In the first example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/710c390d7d95fd1e439facb57a8db32614f140ba.png) is $ 2 $ ;

In the second example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/9a0a3742a40de8b41b9545899252cb65c16a80ca.png) is $ 0 $ ;

In the third example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/ba5fe125aa2ce1485bb9c22050da0a9acf975415.png) is $ 2 $ .

## 样例 #1

### 输入

```
2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
0 10
```

### 输出

```
0
```

## 样例 #3

### 输入

```
107 109
```

### 输出

```
2
```

# 题解

## 作者：李至擎 (赞：7)

求管理员手下留情(╥﹏╥...)！！！

[点我看题](https://www.luogu.com.cn/problem/CF869B)

拿到这道题，我们首先想到的方法是根据题目要求算出 $b!$ 和 $a!$ ，然后再相除求出结果。

好的那么今天的题解就到这里了 $\cdots$ 吗？

如果你细心一点，你就会发现这样一句话：

### （ $10^{18}>=b>=a>=0$ )

看一下极端情况：如果 $b=10^{18}$ 

那么 $b!=1*2*3*\cdots*10^{18}$ 

（不光 long long 救不了你，$O(a+b)$的时间复杂度你也过不了）

显然，这种方法是不行的，这时候我们就要对它进行优化：

优化1：

我们化简一下 $\dfrac{b!}{a!}$ ，不难得到：

$\dfrac{b!}{a!}$

展开得：$\dfrac{1*2*3*\cdots*b}{1*2*3*\cdots*a}$

因为一定有 $b>=a$ ，所以原式经约分可化简成：

$(a+1)*(a+2)*(a+3)*\cdots*b$

所以只用算 $(a+1)*(a+2)*(a+3)*\cdots*b$ 的结果就行了。

优化2：

但是，在使用刚才的优化时，如果a与b差距过大，也起不到什么作用，所以，我们要继续化简：

经过分析，我们可以想出一个办法：由于最后的答案只是求商的个位数，我们便可以只用两数的个位去相乘，再对积取个位$\cdots$这样就可以节省很多空间了。

优化3：

想到了刚才那一步，那我们能不能再优化一些呢？答案是肯定的。

让我们想一想：

如果 $b!$ 比 $a!$ 的末尾多一个0的话，那么答案一定就是0；

而想要求出末尾0的个数，就必须知道10的个数；

想找10的个数，就要找2与5两个质因子；

但是2的个数一定比5多，所以我们只要找到$5$的个数便可以找到10的个数了；

同时，我们不难推出：当b比a大5甚至更多时， $b!$ 是肯定比 $a!$ 多至少一个5的；

所以，我们可以推出：当 $b-a>=5$ 时，结果一定为0。

完整代码（自认为讲得比较详细，就不加注释了）：
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,ans=1;
int main()
{
	cin>>a>>b;
	if(b-a>=5)
	{
		cout<<0;
		return 0;
	}
	for(long long i=a+1;i<=b;i++)
	{
		ans=(ans*(i%10))%10;
	}
	cout<<ans;
	return 0;
}
```
完成！！！

## 你都看到这里了，还不点个赞再走吗？

修改记录：

2020.8.9：修改了一部分 $\LaTeX$ ，并精简了一部分语言。

---

## 作者：OI_AKed_me (赞：2)

# CF869B的题解 #
[原题传送门](https://www.luogu.com.cn/problem/CF869B)  
首先，这道题有一个很明显的做法就是暴力算出 $ a ! $ 和 $ b ! $，然后再相除。但这显然会爆掉，所以我们要对它进行优化。


优化 1：因为题目说只需要个位，那么每次模 $ 10 $ 就能把范围缩小到 ``` int ``` 范围内。

优化 2：
我们可以对 $ \dfrac { b !} { a !} $ 进行化简。
$$ \dfrac { b !} { a !} = \dfrac{1 *2 * 3 * \cdots * b}{1 * 2 * 3 * \cdots * a} = ( a + 1 ) * ( a + 2 ) * (a + 3) * \cdots * b $$

优化 3：
如果一个整十数乘以一个整数，他的乘积的末尾还是 $ 0 $。由此可得：只要乘到末尾为 $ 0 $，则可以判定最终其末位一定还是 $ 0 $。

这样，这道题就做完了。


## 代码 ##
最后附上代码的**核心**部分：
```cpp
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b;
	for(ll i=a+1;i<=b;i++){
		ans=(ans*(i%10))%10;
		if(!ans) break;
	}
	cout<<ans<<endl;
	return 0;
}
```
[AC记录](https://cdn.luogu.com.cn/upload/image_hosting/a6l02fby.png)

---

## 作者：995501336_1 (赞：2)

题目描述：给a，b两个数求出求a！/b！的值的最后一位数

题意分析：如果两个数相差大于5，那么他们的的阶乘运算中就一定会出现5*2这一个数5*2=10，所以无论乘什么其他的数，末尾一定是0

a%10是求a的末位的意思，b%10是求b末位的意思，slove函数是在求a,b两个数最后一位的阶乘，相除以后继续对10求余则求出最后一位，即为答案


```cpp
#include<iostream>
using namespace std;
typedef long long ll;
ll slove(ll x)
{
    ll s=1;
    for(ll i=1;i<=x;i++)
        s*=i;
    return s;
}
int main()
{
    long long a,b,ans=1;
    cin>>a>>b;
    if(b-a>=5)//
        cout<<0<<endl;
    else
        cout<<(slove(b%10)/slove(a%10))%10<<endl;
    return 0;
}

```



---

## 作者：RioBlu (赞：1)

思路：如果当前的乘积为0，继续乘毫无意义，结果也一定是0

同时十位数及以上的位数都对结果没用，所以可以用 $mod$ 磨掉
```
#include <stdio.h>
#define max(a,b) a>b?a:b
#define in(a) scanf("%lld",&a)
#define out(a) printf("%lld",a)
#define F(a,b) for(long long s=a;s<=b;s++)
#define F2(a,b) for(long long v=a;v<=b;v++)
long long a,b,ans=1;
int main()
{
	in(a);in(b);//输入
	if(!a)a=1;//特判0!
   a++;//(b! / a! 不包括a,所以a++)
	F(a,b)//for a to b (包括a,b)
	{
		ans=(ans*(s%10))%10;//没用的磨掉即可
		if(!ans)break;//ans等于0时，结果保证为0，继续乘毫无意义
	}
	out(ans);//输出
}
```

---

## 作者：wangyi_c (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF869B)
## 1.题目大意

求 $b!$ 除以 $a!$ 的结果。

## 2.思路讲解
看到简洁的题目，第一个想到的肯定是**暴力**。但是看到珂怕的数据规模：$0 \le a,b \le 10^{18}$，就知道暴力绝对不可能了，long long 肯定会爆掉，那我们就要想如何优化。~~说实话，高精度好像可以过。~~

- 因为我们要求的是个位数，只是个位数，那我们只要每次计算的时候都只求个位数，这样答案就不会太大而超过 long long。

- 我们可以将这两个式子分别展开，即为 $\dfrac{1 \times 2 \times 3 \dots a}{1 \times 2 \times 3 \dots b}$，可进行约分，约为 $(a+1) \times (a+2) \times (a+3) \cdots b$，所以我们只要求从 $a+1$ 乘到 $b$ 就行了，时间复杂度大大降低。

- 如果 $a+1$ 到 $b$ 之差大于等于 $5$ 时，即 $b-(a+1) \ge 5$ 之时，它们之积必包含 $2$ 和 $5$，即乘积的末尾为 $0$。所以我们可以进行特判，符合要求的直接输出 $0$ 就行了

总结一下，此算法时间复杂度为 $O(1)$，足够我们通过此题。

## 3.AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
int a,b,ans=1;
signed main(){
	cin>>a>>b;
	if(b-a>=5){//对应第三个优化
		cout<<0;
		return 0;
	}
	for(int i=a+1;i<=b;i++){//对应第二个优化
		ans=ans*(i%10)%10;//对应第一个优化
	}
	cout<<ans;
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/82311109)

_THE END_

谢谢观看

By wangyi

---

## 作者：ImposterAnYu (赞：0)

# 1. 思路+优化
老师告诉我们，拿到题目，理解题意之后，一定要看数据范围。于是我们就可以发现：这道题不可能要算 $a!$ 和 $b!$，因为 $a$ 和 $b$ 太大了！

但是，一方面，题目很恶心，因为数据范围很大；一方面，题目很良心，因为只要求出个位！

首先，我们要知道，一个个位为 $0$ 的数一定能被 $2$ 和 $5$ 同时整除，因为这个数既然个位为 $0$，那么它一定是 $10$ 的倍数，而 $\operatorname{lcm}(2,5) = 10$。

其次，我们还要知道：在 $a,a + 1,a + 2,…,a + b - 1$ 这 $b$ 个数里，必然有一个数是 $b$ 的倍数。~~懒得解释为什么了，只要知道就行。~~

所以，当 $b - a \ge 5$ 时，就一定存在两个数，使得一个数是 $2$ 的倍数，一个数是 $5$ 的倍数。这时，$\frac{b!}{a!}$（即 $\prod\limits_{i=a + 1}^bi$）的个位一定是 $0$！

那 $b - a \leq 5$ 时怎么办呢？当然是暴力去算啊！

# 2. AC code
```c++
#include<bits/stdc++.h>
#define int1 long long
using namespace std;
int1 a,b,i,s = 1;
int1 read(){//快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
	a = read(),b = read();
  	if(b - a >= 5){//一个小小的优化。 
	  	print(0);
	}else{
		for(i = a + 1; i <= b; i++){//暴力算！ 
			s *= i % 10;//将i提前对 10 取模，以防 s 溢出。 
			s %= 10;
		}
		print(s);
	}
  	return 0;
}
```

---

## 作者：北射天狼 (赞：0)

# [题目通道](https://www.luogu.com.cn/problem/CF869B)

题解：

暴力肯定会爆 所以不行 

我们仔细观察题目 题目求 $\frac{b!}{a!}$  我们将他进行化简

$\frac{b!}{a!}=\frac{b*(b-1)*(b-2)······a*(a-1)*(a-2)······2*1}{a*(a-1)*(a-2)······2*1}=b*(b-1)*(b-2)······(a+2)*(a+1)=S$

加一个特判：

若 $S$ 中有可以被 $10$ 整除的元素,那么 $S$ 的末尾必定为 $0$

结论 当 $S$ 中的元素个数大于等于 $5$ 则 $S$ 必定可以被 $10$ 整除。很简单 自己想想就行了。

最后暴力求 $S$ 的大小就行了 记得开 $long long$

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b;
	cin>>a>>b;
	if (b-a>=5)    cout<<0<<endl;
	else {
		long long sum=1;
		for (long long i=a+1;i<=b;i++)
		    sum=sum*(i%10)%10;
		cout<<sum%10<<endl;
	}
	return 0;
}
```


---

## 作者：Daniel_yao (赞：0)

# 题目大意

给定两个整数 $a$，$b$。求 $a!/b!$ 的个位。

### 具体思路

众所周知，求 $n$ 的阶乘的时间复杂度为 $O(n)$，而这道题的数据范围 10 的 18 次方。显然，~~超时超到外婆家~~。所以，我们要做亿点优化。

小学我们就学过，0 乘任何数都为 0。所以，当个位为 0 时，结果一定都为 0。然后经过化简，约分。我们可以发现，想要求出 $a!/b!$ 的个位，只需要盯着个位算就可以了（意思就是说，每一次计算只需要关注个位）。

怎样提取个位呢？我们只需要在每一次计算过后模 10 就行了。 

### 上代码

```
#include <bits/stdc++.h>
using namespace std;

int main()
{
	while(1) //防抄袭
	long long a, b, al, bl;
	int ans = 1;
	cin >> a >> b;
	if (b - a > 5)//有一个数个位是 0，结果必然是 0;
		cout << 0;
	else
	{
		for (long long i = a + 1; i <= b; i++)
		{
			ans = (ans % 10) * (i % 10);//维护个位
		}
		cout << ans % 10;
	}	
	return 0;//完结！！
}
```


---

## 作者：AllanPan (赞：0)

读完题目，我们可以发现这题实质上就是让我们求两个数的阶乘的商模 $10$ 的余数。但题目中给的数据是 $0\leq a\leq b\leq 10^{18}$ ，显然直接使用阶乘会直接炸掉（用` python` 也会 `TLE`），因此这种方法直接否决。

但是，经过一番观察，我们发现这里 $a!$ 和 $b!(a\leq b)$ 有很大一部分是“重叠”的，即：

$$\dfrac{b!}{a!}=\dfrac{b\cdot (b-1)\cdot\ldots\cdot1}{a\cdot(a-1)\cdot\ldots\cdot1}=b\cdot(b-1)\cdot\ldots\cdot(a+1)$$

因此可以利用这个方法大大减缓计算量。

**但这样还是不行的**。注意在这种情况下，我们并没有对差距特别大的数做出**实际的优化**。比如说我们输入 $1$ 和 $100000000000$ ，用上面的公式还是需要将$100000000000$个数相乘，没有减少计算量。因此还需要发掘其它的性质。

- 这里我们注意到模 $10$ 计算的优点：碰到一个 $5$ 和一个 $2$ 个位基本就是 $0$ 了。
- 进一步看，也即当两个数满足$b-a>5$时，$\dfrac{b!}{a!}$ 的末位一定是 $0$（这里用到了“任何连续 $n$ 个数的乘积一定被 $n$ 整除”这个性质）

- 这样计算就大大优化了。比如说我们输入 $1$ 和 $100000000000$ ，根据上面的算法，无需计算就可以直接得出答案是 $0$ 。因此可以看到，用适当的数学知识可以减轻计算机的工作量！

上代码：
```cpp
#include <iostream>
using namespace std;

int main()
{
	long long a, b, al, bl;
	int ans = 1;
	cin >> a >> b;
	if (b - a > 5)
		cout << 0;
	else
	{
		for (long long i = a + 1; i <= b; i++)
		{
			ans = (ans % 10) * (i % 10);
		}
		cout << ans % 10;
	}	

	return 0;
}
```

（留个赞再走吧

---

