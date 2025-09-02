# 「Wdoi-2」夜空中的 UFO 恋曲

## 题目背景

土地变得泥泞，曾被寒冰覆盖的大地上，万物开始复苏。  
覆盖着幻想乡的少量积雪，封住了在这个冬天苏醒的地灵们，   
也足以使妖精们的活动变得迟钝。这样安稳沉睡的季节也即将告一段落。

博丽神社的巫女博丽灵梦从居住在森林里的魔法使那儿听到了一个传闻说，有人目击到云的缝隙中有不可思议的船在空中飞行。

——船中空空如也。  
曾在船中的金银财宝早已散佚，剩下的东西也散发着  
陈年霉臭。  
仅凭凛冽春风，仍不足以将那霉味吹散。  
但是，只有那位大人留下的宝物，即使变成碎片也不会失去威力吧。

只是那些碎片依旧以不可思议不可理解的形态飘在幻想乡各处，对扑簌迷离的真相加盖了疑问的迷雾。

貌似有很深的原因。我们不知道的某种东西，在酝酿着什么。

## 题目描述

### 简要题意
给定正整数 $a,b,c$，满足 $a,b,c\textcolor{red} > 1$。对于函数 $f_k$，给出如下定义：

$$f_{k}(x)=\begin{cases}
x^{2c}\oplus c & k = 1\\
f_{k-1}(x^{2c}\oplus c) & k > 1
\end{cases}$$

其中 $\oplus$ 表示二进制下的异或操作。

现在要求计算出 $\operatorname{lowbit}(f_{b}(a))$。其中 $\operatorname{lowbit}(x)$ 表示二进制下 $x$ 最右侧的 $1$ 所在位置对应的二进制值，例如：

$$\operatorname{lowbit}(101101\cdots 10\textcolor{red}1\underbrace{00\cdots000}_{k\text{ 个 }0})=2^k$$

特别地，若 $x=0$，则 $\operatorname{lowbit}(x)=0$。
### 原始题意
为了去除碎片上附加的「不明的因子」，主角组需要破开[【正体不明】](https://www.luogu.com.cn/user/35891)附加的法术。

不明的因子是一种小蛇一般的飞行物，在不同人的眼中具有不同的形象。  
当有人看到它时，会按照自己的常识，把它看成自己认识的、认为合理的东西。

碎片的表面有一个由红蓝组成的长串，妖怪贤者发现，若将红看作 $0$，蓝看作 $1$，它就成了一个二进制数字 $x$。  
碎片上一共有 $k$ 层不明因子，每破开一层都会使数字 $x$ 变为 $x^{2c}\oplus c$（其中 $\oplus$ 表示二进制下的异或操作）。  
为了破解法术，主角组需要根据给定的常数 $c$，初始值 $a$ 和层数 $k=b$ 先破开所有的不明因子，然后计算剩下的数字所代表的串中， 最右侧的「蓝色」所在位置对应的二进制值。

经过主角们一定的分析，她们发现了 $a,b,c\textcolor{red} > 1$。

紫把[式神计算机](https://www.luogu.com.cn/user/149196)搬了出来就回去睡觉了，把编制程序的任务交给了可怜的金发小女孩。你的任务就是帮她完成程序的编制，彻底肃清异变的影响，找回丢失的记忆。

## 说明/提示

### 样例 1 解释

- $f_{2}(5)=f_1(5^8\oplus 4)=f_1(390{,}629)$；
- $f_1(390{,}629)=390{,}629^8\oplus 4=542{,}145{,}496{,}755{,} 385{,}548{,}075{,}315{,}235{,}215{,}044{,}149{,}100{,}456{,}165$；
- 容易发现，$f_{2}(5)$ 的 $\text{lowbit}$ 值为 $1$。

### 数据范围及约定

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|}\hline
\textbf{Subtask} & \bm{a,b,c\le} & \textbf{特殊性质} & \textbf{分值} \cr\hline
1 & 11 & - & 25 \cr\hline
2 & 10^{18} & \text{A} & 35 \cr\hline
3 & 10^{18} & - & 40 \cr\hline
\end{array}$$

- **特殊性质** $\textbf{A}$：保证 $c$ 为偶数。

对于全部数据，保证 $1 \textcolor{red}< a,b,c\le 10^{18}$。

## 样例 #1

### 输入

```
5 2 4```

### 输出

```
1```

## 样例 #2

### 输入

```
1000000000000000000 1000000000000000000 1000000000000000000```

### 输出

```
262144```

# 题解

## 作者：max0810 (赞：10)

~~考试的时候在乱猜结论，交了几遍就过了，证明当然是赛后才想的（）~~

文中加粗部分是需要读者稍微思考一下原因的地方 ~~（不是重点）~~。

---
先考虑一下样例二，将 $10^{18}$ 化成二进制：$1101...001000000000000000000$。

其实只需要知道末尾有 $18$ 个 $0$ 就行了，因为在 $x$ 变为 $x^{2c}$ 时，后面 $18$ 个 $0$ 就会变成 $18\times 2c$ 个 $0$，如果再异或 $c$，就相当于把末尾的几位变成 $c$，此时除了末尾上的 $c$，$x^{2c}\oplus c$ 的前面部分的数已经不会影响结果了（因为最后求 $\operatorname{lowbit}$ 就只关心末几位的值）。所以**每做一次操作，末几位都是 $c$**，那么最后的 $\operatorname{lowbit}$ 就是 $\operatorname{lowbit}(c)$。

再扩展到一般情况：

- $c$ 是偶数，$a$ 是奇数，那么二进制中的最后一位就始终都是 $1$，所以最后的 $\operatorname{lowbit}$ 就是 $1$。

- $c$ 是偶数，$a$ 是偶数，这个就和样例二差不多：$a$ 的二进制末尾至少有一个 $0$，$a^{2c}$ 的末尾就至少有 $2c$ 个 $0$，肯定比 $c$ 的二进制的位数多，异或 $c$ 就相当于把末尾的几位变成 $c$，又因为 $c$ 是偶数，所以 $a^{2c}\oplus c$ 的末尾也至少有一个 $0$，又变成了开始的情况，只不过末几位是 $c$ 而不是 $a$。一直推下去，最后的 $\operatorname{lowbit}$ 就是 $\operatorname{lowbit}(c)$。

- $c$ 是奇数，此时根据 $a$ 的奇偶又分成两种情况：
  - $a$ 是偶数，和前面一样：$a^{2c}$ 的末尾至少有 $2c$ 个 $0$，异或 $c$ 就相当于把末尾的几位变成 $c$，因为我们只关心末几位，所以就可以**把原数看成 $c$**。
  - $a$ 是奇数，那么 $a^{2c}$ 也是奇数，因为 $c$ 也是奇数，奇数异或奇数就变成了偶数，然后又变成了上一个情况，即奇偶交替。
  - 如果最后的数是个奇数，那么 $\operatorname{lowbit}$ 就是 $1$。
  - 如果最后是个偶数，那么就要考虑倒数第二步。因为 $b>1$，所以**倒数第二步的数的二进制末尾一定是 $c$**，那么最后答案就相当于 $\operatorname{lowbit}(c^{2c}\oplus c)$。
  
其实做到这就已经做完了，但是 $\operatorname{lowbit}(c^{2c}\oplus c)$ 还可以化简一下。

考虑用二项式定理展开 $c^{2c}$：

$$c^{2c}=(c-1+1)^{2c}=\sum_{i=0}^{2c} C_{2c}^{i}\times (c-1)^i=1+2c(c-1)+C_{2c}^{2}\times (c-1)^2+...+(c-1)^{2c}$$

我们将上式所有项按 $\operatorname{lowbit}$ 大小来排序，最小的两项当然是 $1$ 和 $2c(c-1)$，因为 $c-1$ 是偶数，所以 $\operatorname{lowbit}(2c(c-1))=\operatorname{lowbit}(c-1)\times 2$

从第三项开始，所有项的 $\operatorname{lowbit}$ 都不小于 $\operatorname{lowbit}(c-1)\times 2$，所以 $c^{2c}$ 一定可以被表示为 $k\times \operatorname{lowbit}(2(c-1))+1$，其中 $k\in N^+$。

~~形象点~~，把 $c^{2c}$ 和 $c$ 的二进制分别表示出来（随便一个例子，只需要看后五位）：

$c^{2c}$：$1101...1010001$

$c$：     $\ \ 1010...0101001$

可以发现，最末尾的 $1$ 会抵消，但倒数第二位不会，所以 $\operatorname{lowbit}(c^{2c}\oplus c)=\operatorname{lowbit}(c-1)$。
```cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll a,b,c;
ll lb(ll x){return x&-x;}
int main()
{
    cin >> a >> b >> c;
    if(c&1)
    {
        if((a&1)^(b&1))cout << 1; //ab不同奇偶，那么最后答案就是奇数
        else cout << lb(c-1); //ab同奇偶，最后答案就是偶数
    }
    else cout << ((a&1)?1:lb(c));
    return 0;
}

```

---

## 作者：dutianchen1 (赞：3)

# 题意翻译
给一个常数 $c$，对于函数 $f_{b}(a)$，执行 $b$ 次操作，每次使得 $a$ 变成 $a^{2c} \oplus c$。求 $ \operatorname{lowbit}(f_{b}(a))$ 的值。

# 思路简析

显然，较大的数据范围不允许我们每次都把 $a^{2c} \oplus c$ 的值算出，于是我们考虑寻找规律。

显然可以发现，$a^{2c}$ 转化为二进制后，某位几位都是 $0$，只有个位可能为 $1$，也就是说，$a^{2c}$ 与 $c$ 进行异或运算后的结果与 $\operatorname{lowbit}(c)$ 相差不大。

再一定思考过后，就会发现，本题的答案与 $a,b,c$ 奇偶性有关，所以下文，我们进行分类讨论。

### 1. 当 $a$ 为偶数时：
  - 当 $c$ 为**偶数**，显然，无论我们执行几次操作，最后的答案都是 $\operatorname{lowbit}(c)$
  - 当 $c$ 为**奇数**后，我们看 $b$ 的奇偶性。如果 $b$ 为奇数，前面偶数次异或之后，此时结果为偶数。再与进行一次异或之后，结果就会变成奇数，而所求的 $\operatorname{lowbit}(a^{2c} \oplus c)$ 一定为 $1$。
  - 若 $b$ 为**偶数**，答案就是去掉 $c$ 末尾的 $1$ 之后的 $\operatorname{lowbit}(c)$。也就是 $\operatorname{lowbit}(c-1)$。
### 2. 当 $a$ 为奇数时：
 - 显然，当 $b$ 与 $c$ 任意一个为**偶数**，最后结果一定为奇数，求得的 $\operatorname{lowbit} (a^{2c} \oplus c)$ 一定为 $1$。
 - 而当两者都是**奇数**时，我们执行一次操作，$a$ 变为偶数，$b$ 变为偶数。此时，我们可以直接套用我们之前推导出来的结论，直接输出 $\operatorname{lowbit}(c-1)$ 即可。

代码如下：（丑陋马蜂，见谅）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;

inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline ll lowbit(ll x){return x&(-x);}
ll a,b,c; 
int main()
{
	a=read();b=read();c=read();
	if(!(a&1))
	{
		
		if(!(c&1))cout<<lowbit(c)<<'\n';
		else if(b&1)cout<<1<<'\n';
		else cout<<lowbit(c-1)<<'\n';
	}
	else
	{
		if(!(b&1)||!(c&1))cout<<1<<'\n'; 
		else cout<<lowbit(c-1)<<'\n';
	}
	
	return 0;
}


```

---

## 作者：离散小波变换° (赞：2)

## 题解

考虑每一次操作：

$$a\gets a^{2c}\oplus c$$

按照奇偶进行讨论。首先讨论两种简单情形：

- $a$ 是奇数，$c$ 是偶数。那么每次变换后，$a$ 都是奇数。这是因为 $a^{2c}$ 必然是奇数，异或上 $c$ 后肯定还是奇数。
- $a$ 是偶数，$c$ 是偶数。  
  设 $a=u\cdot 2^p,c=v\cdot 2^q$，其中 $u,v$ 均为奇数，且 $p,q\ge 1$。  
那么第一次变换后，$a\gets u^{2c}\cdot 2^{2pv2^q}\oplus v\cdot 2^q$。$\oplus$ 两侧，前者的 $\text{lowbit}$ 值为 $2^{2pv2^q}$，后者为 $2^q$。由于 $2pv2^q>q$，于是 $a$ 的 $\text{lowbit}$ 为 $2^q$。设此时 $a$ 为 $w\cdot 2^q$。  
于是第二次变换后，$a\gets w^{2c}\cdot 2^{2qv2^q}\oplus v\cdot 2^q$，发现 $a$ 的 $\text{lowbit}$ 还是 $2^q$。以此类推，任意次操作后，$a$ 的 $\text{lowbit}$ 都是 $2^q$。 

接着是要考虑剩下的两种复杂点的情形：

- $c$ 是奇数，$a$ 是偶数。
- $c$ 是奇数，$a$ 是奇数。第一次操作后，$a\gets a^{2c}\oplus c$ 变成了一个偶数。可以归纳到上一种情形里。


考虑前者。下文中，取 $2c\ge 2^d>c$。

同样地，设 $a=u\cdot 2^p$，那么 $a^{2c}\oplus c=u^{2c}\cdot 2^{2pc}\oplus c\equiv c\pmod{2^{2c}}\equiv c\pmod {2^d}$。下次迭代后成了 $c^{2c}\oplus c$。下面证明 $c^{2c}\oplus c\not\equiv 0\pmod {2^d}$。

也就是要证明：

$$c^{2c-1}-1\not\equiv 0\pmod{2^d}$$

考虑直接使用二项式定理将左侧展开。

$$(c-1+1)^{2c-1}-1=\sum_{i=0}^{2c-1}\binom{2c-1}{i}(c-1)^i-1=\sum_{i=1}^{2c-1}\binom{2c-1}{i}(c-1)^i$$

注意到，$c-1$ 是一个偶数，由于 $c>1$，上式的 $\text{lowbit}$ 值就是 $c-1$ 的 $\text{lowbit}$ 值。那么，

$$\operatorname{lowbit}(c^{2c-1}-1) = \operatorname{lowbit}(c-1)<2^d$$

所以，

$$c^{2c-1}-1\not\equiv 0\pmod{2^d}$$

## 代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef long long i64;
const int INF =2147483647;
i64 qread(){
    i64 w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
i64 lowbit(i64 x){
    return x&-x;
}
i64 power(i64 x,i64 y){
    u64 r=1,t=x;
    while(y){if(y&1) r=r*t; t=t*t,y>>=1;}
    return r;
}
void solve(i64 b,i64 c){
    if(b%2==1) printf("%lld\n",lowbit(c));
    else       printf("%lld\n",lowbit(power(c,2*c)^c));
}
int main(){
    i64 a=qread(),b=qread(),c=qread();
    if(a%2==1&&c%2==0) puts("1"),exit(0);
    if(a%2==0&&c%2==0) printf("%lld\n",lowbit(c)),exit(0);
    if(a%2==0&&c%2==1) solve(b  ,c);
    if(a%2==1&&c%2==1) solve(b-1,c);
    return 0;
}
```

---

## 作者：int08 (赞：0)

# 前言
本来是想整一大堆引理，然后写那种特别正经的题解。

~~但是我觉得那样我自己后来都不一定看得懂。~~

# Solution

先说相信大家都看出来的一点：**这题通过对 $a,b,c$ 的奇偶分析，分类讨论得到结果。**

**注：以下所有说一个数末尾 $0$ 数量都是在二进制下。**
### 1、$a,c$ 皆为偶数

这种情况是最简单的。因为 $a$ 的末尾至少有一个 $0$，所以 $a^{2c}$ 的末尾至少就会有 $2c$ 个，显然是比 $c$ 本身末尾 $0$ 的数量要多的。

所以 $\text{lowbit}(a^{2c}⊕c)=\text{lowbit}(c)$。

同时又因为 $c$ 也是偶数，$\text{lowbit}(c)>1$，所以根据上文推导同理可得 $\text{lowbit}(c^{2c}⊕c)=\text{lowbit}(c)$。

于是此时答案就是 $\text{lowbit}(c)
$。

### 2、$a$ 为偶数，$c$ 为奇数

此时情况稍微复杂。当你操作次数为奇数的时候，$\text{lowbit}(a^{2c})>1,\text{lowbit}(c)=1,\text{lowbit}(a^{2c}⊕c)=1$。

当你刚刚操作完奇数次，操作第偶数次的时候，
$\text{lowbit}(a)=1,\text{lowbit}(a^{2c})=1,\text{lowbit}(c)=1$。

看来最后一个 $1$ 会被抵消掉，但是倒数第二个就不会了。

与上文类似的，因为 $a-1$ 的末尾至少有一个 $0$，所以 $a^{2c}-1$ 的末尾至少就会有更多个0，显然是比 $c-1$ 本身末尾 $0$ 的数量要多的。

（这一点可以通过二项式定理得出来，不过还是建议各位手推，这样结论更明显，此处我就不赘述了。）

$\text{lowbit}(a^{2c}⊕c)=\text{lowbit}(c-1)$。

所以当 $b$ 为奇数时，答案为 $1$，$b$ 为偶数时，答案为 $\text{lowbit}(c-1)$。

### 3、$a$ 为奇数，$c$ 为偶数

更加简单的情况。

$a^{2c}$ 显然仍然是奇数，那么 $a^{2c}⊕c$ 就肯定一直是奇数了。

所以答案始终是 $1$。

### 4、$a$ 为奇数，$c$ 为奇数

复杂的情况。

#### （1）$b$ 为偶数

我们还不知道 $b$ 为奇数的时候答案为多少，但是我们可以肯定不是 $1$。那么此时

$\text{lowbit}(a^{2c})>1,\text{lowbit}(c)=1,\text{lowbit}(a^{2c}⊕c)=1$。

答案为 $1$。

#### （2）$b$ 为奇数

题目中那个非常关键的被反复标红的信息作用来了： $a,b,c>1$。

所以这个时候我们容易得到 $b≥3$。

这就很关键了。在进行完第一次操作时，

$\text{lowbit}(a^{2c})=1,\text{lowbit}(c)=1,\text{lowbit}(a^{2c}⊕c)>1$。

换句话说，现在的 $a$ 已经是偶数了，而 $c$ 仍然为奇数，$b>1$。

直接就被转化为了上文第二种情况中的第二个分支。

答案仍然是 $\text{lowbit}(c-1)$。

于是这道题就做完了。

# AC code

```cpp
#include<bits/stdc++.h>
#define ull long long
using namespace std;
ull a,b,c;
ull lowbit(ull x)
{
	ull i;
	for(i=2;x%i==0;i*=2);
	return i/2;
}
int main()
{
	cin>>a>>b>>c;
	if(a%2==0) 
	{
		if(c%2==0)
			cout<<lowbit(c);
		else
		{
			if(b%2==1) cout<<1; 
			else cout<<lowbit(c-1);
		} 
			return 0;
	}
	if(c%2==0)
	{
		cout<<1;return 0;
	}
	if(b%2==0)
	{
		cout<<1;return 0;
	}
	cout<<lowbit(c-1);
	return 0;
} 
```
~~个人码风稍显奇怪，不过应该是很好懂的。~~

---

## 作者：Lyrella (赞：0)

# 前言
**stO离散小波变换°Orz**
# 题意
定义：
$$f_{k}(x)=\begin{cases} x^{2c}\oplus c & k = 1\\ f_{k-1}(x^{2c}\oplus c) & k > 1 \end{cases}$$
给定 $a,b,c$，求 $\text{lowbit}(f_b(a))$。
# 思路
因为数据范围 $1 \leq a,b,c\leq 10^{18}$，所以这题肯定推结论。

首先看 $\text{subtask2}$ 的性质：保证 $c$ 为偶数。所以想到通过奇偶性破题。
# 题解
**注：以下的数皆为二进制下的数**
### 当 $c$ 为偶数时
1. 如果 $a$ 为**偶数**，每次操作前 $a=1001011.......001010$，那么 $a$ 变成 $a^{2c}$ 后 $a$ 的末尾就会有**至少** $2c$ 个 $0$（比如：$1001011......1001000...0$），那么每次异或上 $c$ 过后（相当于加上 $c$），答案就为 $\text{lowbit(c)}$。
2. 如果 $a$ 为**奇数**，每次操作前 $a=1001011.......001011$，那么 $a$ 变成 $a^{2c}$ 后末尾**一定**是 $1$，那么每次异或上 $c$ 过后，因为 $c$ 为**偶数**（$c$ 的末尾为 $0$），所以答案为 $1$。

### 当 $c$ 为奇数时
那么每次操作后 $a$ 的奇偶性会发生改变，具体的讲，如果 $a$ 现在是奇数，$a$ 变成 $a^{2c}$ 后它还是奇数，异或上 $c$ 后为偶数；如果 $a$ 现在是偶数，$a$ 变成 $a^{2c}$ 后它还是偶数，异或上 $c$ 后为奇数，它的奇偶性在**有规律**地变化，所以只用讨论最后 $a$ **是奇是偶**。

如果 $a$ **是奇**，那么**毫无疑问**答案是 $1$。

如果 $a$ **是偶**，那情况就有些复杂了，先从奇数推。

当 $a$ 为奇数时，$a$ 的末尾肯定是 $c$，因为 $a$ 为偶数时乘方会有**很多**的 $0$，将现在的 $a$ （奇数）乘方，因为对结果有影响的只有 $a$ 的**末尾**也就是 $c$，所以只看 $c$。考虑把 $c$ 写成 $2^n\times A_n+2^{n-1}\times A_{n-1}+......+2^0\times A_0$ 的形式（其中 $A$ 为 $c$ 每一位上的数），再把上柿做乘方。可以发现，如果第 $i$ 位为 $0$，无论乘方多少次都不变。因为求 $\text{lowbit(a)}$，所以从后往前分析 $1$。

1. 第一个 $1$：乘方后一定是 $1$，最后异或上 $c$ 为 $0$，跳过。

2. 第二个 $1$：设第二个 $1$ 在第 $k$ 位，那么第 $k$ 位的数值一定由**它本身**以及其**后面的数**相乘得到。这时将上面的狮子的第 $k$ 位找到，就是 $2^{n-k}\times A_{n-k}$，我们看它后面的单项式。求第 $k$ 位的数就**等价于**每次在 $2^{n-k}\times A_{n-k}+......+2^0\times A_0$ 中选一个单项式，选 $2c$ 次，满足 $2^{n-k}=2^{i1}\times 2^{i2}\times ...\times 2^{i2c}$。可以发现如果选了第 $i$ 位且 $A_i=0$，那么对第 $k$ 位就**没有影响**。（因为 $0$ 乘以任何数为 $0$）所以对第 $k$ 位有影响的**只有**第 $k$ 位和倒数第 $1$ 位。此时如果满足 $2^{n-k}=2^{i1}\times 2^{i2}\times ...\times 2^{i2c}$，显然我们只能选**一个** $2^{n-k}\times A_{n-k}$ 和 $2c-1$ 个 $2^0\times A_0$。（因为一个$2^{n-k}$ 乘上 $2c-1$ 个 $2^0$ 等于 $2^{n-k}$）然后就有 $C_{2c}^1=2c$ 个 $1$ 相加等于 $0$，（偶数个 $1$ 相加为 $0$）

之后异或上 $c$ 后第 $k$ 位为 $1$，其后面的 $n-k+1$ 位都是 $0$。所以这种情况下答案为 $2^{n-k}$ 也就是 $\text{lowbit(c-1)}$。时间是 $O(1)$ 的。**最后此题得解**！
# 注意
不开 $\text{long long}$ 见祖宗！

当 $c$ 为奇数时，判断 $a$ 最后是否为奇数用 `(a&1)^(b&1)` 就行了。（不打括号见祖宗）
# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a, b, c, ans;
void read(ll &x){
	ll f = 1ll; char ch = getchar(); x = 0;
	while(ch < '0' or ch > '9'){if(ch == '-')f = - f; ch = getchar();}
	while(ch >= '0' and ch <= '9'){x = (x << 3) + (x << 1) + ch - 48; ch = getchar();}
	x *= f;
}
void write(ll x){
	if(x < 0)putchar('-'), x = - x;
	if(x > 9)write(x / 10);
	putchar(x % 10 + 48);
}
ll lowbit(ll x){
	return x & - x;
}
void in(){
	read(a); read(b); read(c);
}
void solve(){
	if((c & 1) == 0){
		if((a & 1) == 0)ans = lowbit(c);
		else ans = 1;
		return;
	}
	if((a & 1) ^ (b & 1))ans = 1;
	else ans = lowbit(c - 1);
}
void out(){
	write(ans);
}
signed main(){
	in();
	solve();
	out();
	return 0;
}
```

---

