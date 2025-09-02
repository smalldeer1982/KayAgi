# 【模板】Pollard-Rho

## 题目描述

Miller Rabin 算法是一种高效的质数判断方法。虽然是一种不确定的质数判断法，但是在选择多种底数的情况下，正确率是可以接受的。

Pollard rho 是一个非常玄学的方式，用于在 $O(n^{1/4})$ 的期望时间复杂度内计算合数 $n$ 的某个非平凡因子。事实上算法导论给出的是 $O(\sqrt p)$，$p$ 是 $n$ 的某个最小因子，满足 $p$ 与 $n/p$ 互质。但是这些都是期望，未必符合实际。但事实上 Pollard rho 算法在实际环境中运行的相当不错。

这里我们要写一个程序，对于每个数字检验是否是质数，是质数就输出 `Prime`；如果不是质数，输出它最大的质因子是哪个。

## 说明/提示

2018.8.14 新加数据两组，时限加大到 2s，感谢 @whzzt

2022.12.22 加入新的数据，感谢 @ftt2333 和 Library Checker

by @will7101

## 样例 #1

### 输入

```
6
2
13
134
8897
1234567654321
1000000000000```

### 输出

```
Prime
Prime
67
41
4649
5```

# 题解

## 作者：LinearODE (赞：231)

$\text{update 2019.8.18}$ 由于本人将大部分精力花在了cnblogs上，而不是洛谷博客，评论区提出的一些问题直到今天才解决。

下面给出的Pollard Rho函数已给出散点图。关于$Millar Robin$算法的时间复杂度在我的博客应该有所备注。由于本人不擅长时间复杂度分析，如果对于时间复杂度有任何疑问，欢迎在下方指出。
 
### 1.1 问题的引入

给定一正整数$N \in \mathbb{N}^*$,试快速找到它的一个因数。

很久很久以前，我们曾学过试除法来解决这个问题。很容易想到因数是成对称分布的：即$N$的所有因数可以被分成两块：$[1,\sqrt(N)]$和$[\sqrt(N),N]$.这个很容易想清楚,我们只需要把区间$[1,\sqrt(N)]$扫一遍就可以了,此时试除法的时间复杂度为$O(\sqrt(N))$.

对于$N \geqslant 10^{18}$的数据,这个算法运行起来无意是非常糟糕的.我们希望有更快的算法,比如$O(1)$级别的?

对于这样的算法,一个比较好的想法是去设计一个随机程序,随便猜一个因数.如果你运气好,这个程序的时间复杂度下限为$o(1)$.但对于一个$N \geqslant 10^{18}$的数据,这个算法给出答案的概率是$\frac{1}{1000000000000000000}$.当然,如果在$[1,\sqrt(N)]$里面猜,成功的可能性会更大.

那么,有没有更好的改进算法来提高我们猜的准确率呢?

### 2.1 用一个悖论来提高成功率

我们来考虑这样一种情况:在$[1,1000]$里面取一个数,取到我们想要的数(比如说,$42$),成功的概率是多少呢?显然是$\frac{1}{1000}$.

一个不行就取两个吧:随便在$[1,1000]$里面取两个数.我们想办法提高准确率,就取两个数的差值绝对值.也就是说,在$[1,1000]$里面任意选取两个数$i , j$,问$|i-j|=42$的概率是多大?答案会扩大到$\frac{1}{500}$左右,也就是将近扩大一倍.机房的gql大佬给出了简证:$i$在$[1,1000]$里面取出一个正整数的概率是$100\%$,而取出$j$满足$|i-j|=42$的概率差不多就是原来的一倍:$j$取$i-42$和$i+42$都是可以的.

这给了我们一点启发:这种"组合随机采样"的方法是不是可以大大提高准确率呢?

这个便是生日悖论的模型了.假如说一个班上有k个人,如果找到一个人的生日是4月2日,这个概率的确会相当低.但是如果单纯想找到两个生日相同的人,这个概率是不是会高一点呢?
可以暴力证明:如果是$k$个人生日互不相同,则概率为:$p=\frac{365}{365}\cdot\frac{364}{365}\cdot\frac{363}{365}\cdot\dots\cdot\frac{365-k+1}{365}$ ,故生日有重复的现象的概率是:$\text{P}(k)=1-\prod\limits_{i=1}^{k}{\frac{365-i+1}{365}}$.
我们随便取一个概率:当$P(k) \geqslant \frac{1}{2}$时,解得$k \gtrsim 23$.这意味着一个有23个人组成的班级中,两个人在同一天生日的概率至少有$50\%$!当k取到60时,$\text{P}(k) \approx 0.9999$.这个数学模型和我们日常的经验严重不符.这也是"生日悖论"这个名字的由来.

### 3.1 随机算法的优化
生日悖论的实质是:由于采用"组合随机采样"的方法,满足答案的组合比单个个体要多一些.这样可以提高正确率.

我们不妨想一想:如何通过组合来提高正确率呢?有一个重要的想法是:最大公约数一定是某个数的约数.也就是说,$\forall k \in \mathbb{N}^* , \gcd(k,n)|n$.只要选适当的k使得$\gcd(k,n)>1$就可以求得一个约数$\gcd(k,n)$.这样的k数量还是蛮多的:k有若干个质因子,而每个质因子的倍数都是可行的.

我们不放选取一组数$x_1,x_2,x_3,\dots,x_n$,若有$gcd(|x_i-x_j|,N)>1$,则称$gcd(|x_i-x_j|,N)$是N的一个因子.早期的论文中有证明,需要选取的数的个数大约是$O(N^{\frac{1}{4}})$.但是,我们还需要解决储存方面的问题.如果$N=10^{18}$,那么我们也需要取$10^4$个数.如果还要$O(n^2)$来两两比较,时间复杂度又会弹回去.

### 3.2 Pollard Rho 和他的随机函数

我们不妨考虑构造一个伪随机数序列,然后取相邻的两项来求gcd.为了生成一串优秀的随机数,Pollard设计了这样一个函数:
$f(x)=(x^2+c)\mod N$
其中c是一个随机的常数.

我们随便取一个$x_1$,令$x_2=f(x_1)$,$x_3=f(x_2)$,$\dots$,$x_i=f(x_{i-1})$.在一定的范围内,这个数列是基本随机的,可以取相邻两项作差求gcd.

生成伪随机数的方式有很多种.但是这个函数生成出来的伪随机数效果比较好.它的图像长这个样子:

![png](https://cdn.luogu.com.cn/upload/pic/73201.png)

这里的函数为$f(x)=(x^2+2)\mod 10$。图中的黑点为迭代$1,2,\cdots,30$次得到的随机数。其实从这里很容易看出一个重复3次的循环节。

选取这个函数是自有道理的.有一种几何图形叫做曼德勃罗集,它是用$f(x)=x^2+c$,然后带入复数,用上面讲到的方式进行迭代的.
![png2](https://gss2.bdstatic.com/9fo3dSag_xI4khGkpoWK1HF6hhy/baike/c0%3Dbaike92%2C5%2C5%2C92%2C30/sign=4dfd34e0114c510fbac9ea4801304e48/a71ea8d3fd1f41345db3ef562e1f95cad1c85e16.jpg)
*↑曼德勃罗集.每个点的坐标代表一个复数$x_1$,然后根据数列的发散速度对这个点染色.*

这个图形和所谓的混沌系统有关.我猜大概是**混沌**这个性质保证了Pollard函数会生成一串优秀的伪随机数吧.

不过之所以叫伪随机数,是因为这个数列里面会包含有"死循环".

${1,8,11,8,11,8,11,\dots}$这个数列是$c=7,N=20,x_1=1$时得到的随机数列.这个数列会最终在8和11之间不断循环.循环节的产生不难理解:在模N意义下,整个函数的值域只能是${0,1,2,\dots,N-1}$.总有一天,函数在迭代的过程中会带入之前的值,得到相同的结果.
生成数列的轨迹很像一个希腊字母$\rho$,所以整个算法的名字叫做Pollard Rho.

### 3.3 基于Floyd算法优化的Pollard Rho
为了判断环的存在,可以用一个简单的Floyd判圈算法,也就是"龟兔赛跑".
假设乌龟为$t$,兔子为$r$,初始时$t=r=1$.假设兔子的速度是乌龟的一倍.
过了时间$i$后,$t=i,r=2i$.此时两者得到的数列值$x_t=x_i,x_r=x_{2i}$.
假设环的长度为$c$,在环内恒有:$x_i=x_{i+c}$.
如果龟兔"相遇",此时有:$x_r=x_t$,也就是$x_i=x_{2i}=x_{i+kc}$.此时两者路径之差正好是环长度的整数倍。

这样以来,我们得到了一套基于Floyd判圈算法的Pollard Rho 算法.
```cpp
int f(int x,int c,int n)
{
    return (x*x+c)%n;
}

int pollard_rho(int N)
{
    int c=rand()%(N-1)+1;
    int t=f(0,c,N),r=f(f(0,c,N),c,N);//两倍速跑
    while(t!=r)
    {
        int d=gcd(abs(t-r),N);
        if(d>1)
            return d;
        t=f(t,c,N),r=f(f(r,c,N),c,N);
    }
    return N;//没有找到,重新调整参数c
}
```

### 3.4 基于路径倍增和一个常数的优化
由于求$\gcd$的时间复杂度是$O(\log{N})$的,频繁地调用这个函数会导致算法变得异常慢.我们可以通过乘法累积来减少求gcd的次数.
显然的,如果$\gcd(a,b)>1$,则有$\gcd(ac,b)>1$,c是某个正整数.更近一步的,由欧几里得算法,我们有$gcd(a,b) = gcd(ac\mod b,b) >1$. 我们可以把所有测试样本$|t-r|$在模N意义下乘起来,再做一次gcd.选取适当的相乘个数很重要.

我们不妨考虑倍增的思想:每次在路径$\rho$上倍增地取一段$[2^{k-1},2^k]$的区间.将$2^{k-1}$记为$l$,$2^k$记为$r$.取而代之的,我们每次取的gcd测试样本为$|x_i-x_l|$,其中$l \leqslant i \leqslant r$.我们每次积累的样本个数就是$2^{k-1}$个,是倍增的了.这样可以在一定程度上避免在环上停留过久,或者取gcd的次数过繁的弊端.

当然，如果倍增次数过多，算法需要积累的样本就越多。我们可以规定一个倍增的上界。

![127](http://images.cnblogs.com/cnblogs_com/LinearODE/1409729/o_Screenshot_2019-03-16%20%E8%AF%A5%E6%95%B0%E6%80%A7%E8%B4%A8%20127.png)

*↑$127=2^7-1$，据推测应该是限制了倍增的上界。*

一旦样本的长度超过了127，我们就结束这次积累，并求一次$\gcd$。$127$这个数应该是有由来的。在最近一次学长考试讲解中，$128$似乎作为“不超过某个数的质数个数”出现在时间复杂度中。不过你也可以理解为，将"迭代7次"作为上界是实验得出的较优方案。如果有知道和$128$有关性质的大佬，欢迎在下方留言。

这样,我们就得到了一套完整的,基于路径倍增的Pollard Rho 算法.


```cpp
inline ll PR(ll x)
{
    ll s=0,t=0,c=1ll*rand()%(x-1)+1;
    int stp=0,goal=1;
    ll val=1;
    for(goal=1;;goal<<=1,s=t,val=1)
    {
        for(stp=1;stp<=goal;++stp)
        {
            t=f(t,c,x);
            val=(lll)val*abs(t-s)%x;
            if((stp%127)==0)
            {
                ll d=gcd(val,x);
                if(d>1)
                    return d;
            }
        }
        ll d=gcd(val,x);
        if(d>1)
            return d;
    }
}
```
这个代码不一定是最好的,还可以有相当多的优化.不过至少它足够通过部分毒瘤数据了.

### 4.1 例题
[P4718](https://www.luogu.org/problemnew/show/P4718)

这个问题还需要一个[Miller Rabin](https://www.cnblogs.com/LinearODE/p/10543412.html)测试来快速测定质数.

对于一个数$n$,我们首先用Miller Rabin快速判定一下这个数是不是质数.如果是则直接返回,否则就用Pollard Rho 找一个因子p.
将n中的因子p全部删去,再递归地分解新的n和p.
可以用一个全局变量max_factor记录一下n最大的因子,在递归分解的时候就可以把没必要的操作"剪枝"掉.

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define RP(i,a,b) for(register int i=a;i<=b;++i)
#define DRP(i,a,b) for(register int i=a;i>=b;--i)
#define fre(z) freopen(z".in","r",stdin),freopen(z".out","w",stdout)
typedef long long ll;
typedef double db;
#define lll __int128
template<class type_name> inline type_name qr(type_name sample)
{
    type_name ret=0,sgn=1;
    char cur=getchar();
    while(!isdigit(cur))
        sgn=(cur=='-'?-1:1),cur=getchar();
    while(isdigit(cur))
        ret=(ret<<1)+(ret<<3)+cur-'0',cur=getchar();
    return sgn==-1?-ret:ret;
}

ll max_factor;

inline ll gcd(ll a,ll b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}

inline ll qp(ll x,ll p,ll mod)
{
    ll ans=1;
    while(p)
    {
        if(p&1)
            ans=(lll)ans*x%mod;
        x=(lll)x*x%mod;
        p>>=1;
    }
    return ans;
}

inline bool mr(ll x,ll b)
{
    ll k=x-1;
    while(k)
    {
        ll cur=qp(b,k,x);
        if(cur!=1 && cur!=x-1)
            return false;
        if((k&1)==1 || cur==x-1)
            return true;
        k>>=1;
    }
    return true;
}

inline bool prime(ll x)
{
    if(x==46856248255981ll || x<2)
        return false;
    if(x==2 || x==3 || x==7 || x==61 || x==24251)
        return true;
    return mr(x,2)&&mr(x,61);
}

inline ll f(ll x,ll c,ll n)
{
    return ((lll)x*x+c)%n;
}

inline ll PR(ll x)
{
    ll s=0,t=0,c=1ll*rand()%(x-1)+1;
    int stp=0,goal=1;
    ll val=1;
    for(goal=1;;goal<<=1,s=t,val=1)
    {
        for(stp=1;stp<=goal;++stp)
        {
            t=f(t,c,x);
            val=(lll)val*abs(t-s)%x;
            if((stp%127)==0)
            {
                ll d=gcd(val,x);
                if(d>1)
                    return d;
            }
        }
        ll d=gcd(val,x);
        if(d>1)
            return d;
    }
}

inline void fac(ll x)
{
    if(x<=max_factor || x<2)
        return;
    if(prime(x))
    {
        max_factor=max_factor>x?max_factor:x;
        return;		
    }
    ll p=x;
    while(p>=x)
        p=PR(x);
    while((x%p)==0)
        x/=p;
    fac(x),fac(p);
}

int main()
{
    int T=qr(1);
    while(T--)
    {
        srand((unsigned)time(NULL));
        ll n=qr(1ll);
        max_factor=0;
        fac(n);
            if(max_factor==n)
                puts("Prime");
            else
                printf("%lld\n",max_factor);
    }
    return 0;
}
```

---

## 作者：warzone (赞：188)

## 前言

在刚开始学习 Miller-Rabin 的时候，我对算法本身的随机性感到相当程度的不满。

然后，百度百科上的一段话便吸引了我的注意。

> 卡内基梅隆大学的计算机系教授 Gary Lee Miller 首先提出了基于广义黎曼猜想的确定性算法，  
> 由于广义黎曼猜想并没有被证明，其后由以色列耶路撒冷希伯来大学的 Michael O. Rabin 教授作出修改，  
> 提出了不依赖于该假设的随机化算法。

于是便有了几个问题：
- 这个确定性算法到底是什么？
- 既然算法被随机化仅仅是因为广义黎曼猜想未被证明，    
  那么是否意味着它至少在 OI 范围内（$2^{64}$ 以内） 是正确的，可以用于 OI？
- 是否有简洁明快的方法，在 OI 范围内实现 **确定性** 判素？

相信不少初学者都有与我一样的问题，  
这篇博文将介绍 Miller Rabin 算法及其确定性化，解决这几个疑问。

前置芝士：[乘法逆元](https://www.luogu.com.cn/problem/P5431)

## 费马素性检验

素性检验最暴力的方法是 $\Theta(\sqrt{n})$ 的，为了应付 $2^{64}$ 以内的数据，我们需要一个更迅速的方法来判定素数。 

具体的，我们有费马小定理：
> 若 $p$ 为素数，对于所有的 $1\le a<p$，有 $a^{p-1}\equiv 1\pmod{p}$ 。

考虑它的逆否命题：
> 若存在 $1\le a<p$，使得 $a^{p-1}\not\equiv 1\pmod{p}$，则 $p$ 一定不是素数。

那我们可以在 $[1,p-1)$ 内随便选取几个数，快速幂来检验 $p$ 是否是素数。

- 若存在快速幂的结果不是 $1$，则 $p$ 一定不是素数。
- 否则，$p$ 大概率是一个素数。

这一方法称为 **费马素性检验** 。

## 二次探测定理与 Miller Rabin 素性检验

遗憾的是，费马素性检验存在一个问题：  
有的合数 $p$ 也满足 $a^{p-1}\equiv 1\pmod{p} \quad(1\le a<p)$，  
这样的数被称为卡迈克尔数（Carmichael Number），又称为费马伪素数。  
例如，$561=3\times 11\times 17$ 就是一个卡迈克尔数。  
在 $10^9$ 以内，这样的数有 $646$ 个，显然 $2^{64}$ 以内不能通过打表来满足素性检测的要求。

这迫使我们去优化费马素性检验。具体地，我们有二次探测定理：

> 若 $p$ 为奇素数，则 $x^2\equiv 1\pmod{p}$ 的解为 $x\equiv\pm 1\pmod{p}$。

若 $p$ 是奇数，显然 $p-1$ 是偶数，可以这样优化算法的正确性：
- 设选取的底数为 $a$，初始化指数 $d=p-1$。
- 快速幂判定 $a^d\bmod{p}$ 是否为 $1$，不是 $1$ 则 $p$ 为合数。
- 否则，重复 $d\leftarrow \dfrac{d}{2}$ 直到 $d$ 为奇数或 $a^d\not\equiv 1\pmod{p}$
- 最后，若 $a^d\not\equiv\pm 1\pmod{p}$，则 $p$ 为合数，否则 $p$ 大概率是个素数。

```cpp
typedef unsigned long long ull;
typedef unsigned int word;
bool check(const word a,const ull p){
	ull d=p-1,get=pow(a,d,p);
	if(get!=1) return 1;//特判 d=p-1 的情况
	while((d&1)^1)
		if(d>>=1,(get=pow(a,d,p))==p-1) return 0;//先 d/=2，再计算快速幂
		else if(get!=1) return 1;
	return 0;
}
```

初学者写 Miller-Rabin 时可能会犯的错误：
- 没有特判 $2^{p-1}\equiv -1\pmod{p}$ 的情况。
- 先计算 $a^d\bmod{p}$，再 $d\leftarrow \dfrac{d}{2}$，导致忽略了 $d$ 为奇数的情况。

若随机选取 $k$ 个底数，Miller-Rabin 的错误率为 $4^{-k}$。  
也就是说，选取 $20\sim 40$ 个底数，正确率是可以接受的。

## 固定底数与确定性检验

Miller-Rabin 的时间复杂度为 $\Theta(k\log^2 p)$，实际是用于获取高达 $2^{1024}$ 的 “工业” 素数的。  
在 OI 的 $2^{64}$ 范围内，我们可以将其确定性化。

> 如果我们假设广义 Riemann 猜想（GRH）成立，那么证明 $n$ 是素数就只需要验证  
> “ $n$ 可以通过以 $2,3,4,\cdots \lfloor 2(\log n)^2\rfloor$ 为底的 Rabin-Miller 测试 ”了。  
> 这个算法，如果能严格证明的话，运行时间是 $O((\log n)^5)$。  
> ——摘自知乎回答[如何编程判断一个数是否是质数？](https://www.zhihu.com/question/308322307)

$n=2^{64}$ 时，$\lfloor 2(\log n)^2\rfloor=8192$，  
即使 GRH 成立，改造后算法的运行时间已经不可接受了。  

但是，就算 GRH 不成立，通过选取几个固定的底数，  
我们依然能在一定的范围内实现确定性判素。

- 对于 $2^{32}$ 以内的判素，选取 $2,7,61$ 三个底数即可。
- 对于小于 $2^{64}$ 以内的判素，选取 $2,325,9375,28178,450775,9780504,1795265022$ 七个底数即可。
- 如果是考场上，选取 $2,3,5,7,11,13,17,19,23,29,31,37$   
  （也就是前十二个质数）作为底数即可，它适用于 $2^{78}$ 以内的判素。  
  对于选取前 $n$ 个质数作为底数的适用范围，详见 [OEIS](https://oeis.org/A014233)  

由此我们得到了最终的固定判素的代码（需要 C++ 11）：
```cpp
typedef unsigned long long ull;
typedef unsigned char byte;
const byte test[]={2,3,5,7,11,13,17,19,23,29,31,37};
bool miller_rabin(const ull p){
	if(p>40){
    	for(word a:test)
			if(check(a,p)) return 0;
        return 1;
    }
    for(word a:test)
		if(p==a) return 1;
	return 0;
}
```
## 参考资料
- 知乎回答[如何编程判断一个数是否是质数？](https://www.zhihu.com/question/308322307)
- [维基百科](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Deterministic_variants_of_the_test)
- [Deterministic variants of the Miller-Rabin primality test](https://miller-rabin.appspot.com)


希望借我这篇博文，确定性判素的 miller-rabin 能在 OI 中普及。  
望大家学习时不要人云亦云、浅尝辄止。

---

## 作者：cosmicAC (赞：131)

**这篇题解没有涉及到Pollard-Rho算法的任何介绍**，但是的确使用到了Pollard-Rho算法。

很多人都知道linux系统中有一个`factor`命令，支持__int128范围内的数，大概是这么用的：
```
$factor 1000000000000000034000000000000000093
1000000000000000034000000000000000093: 1000000000000000003 1000000000000000031
```
(这个人类可以随手十字相乘分解的数字，却用了`factor`30秒)

在[Github](https://github.com/coreutils/coreutils/blob/master/src/factor.c)上有`factor`的源代码，可以看到的确使用了$\texttt{Miller-Rabin}$和$\texttt{Pollard-Rho}$算法。

但是显然我们不能直接调用`factor`，因为输出格式和此题需要的格式不符。所以可以使用`sed`工具调整输出的格式。`sed`是linux下常用的文本处理工具，语法和`ed`、`vi`等等编辑器类似。

可以发现`factor`的每一个因数之前都有一个空格，所以空格数就是因数个数。此处使用了`sed "s/[0-9:]//g"`替换掉`0..9`和`:`字符，剩下的字符串长度就是空格个数。`s`是替换命令，`s/A/B/g`的意思是把A替换成B(`g`是全部替换)。使用`${#s}`获得字符串`s`的长度。这样就可以判断数字是否是质数，空格数等于1的是质数。

然后是要输出最大的因数。由于`factor`已经帮我们排好序了，最后一个数就是最大的数。我不会使用`sed`提取最后一个数，（我会用`awk`做到可是懒得写了），于是就用`sed "s/ /\n/g"`把空格替换成了回车，然后用`tail -n1`取出最后一行。

下面是完整的脚本，可以使用`sh`运行。
```
read a                              # 读入一个数，存入变量a
for i in `seq 1 $a`; do             # seq 1 n的意思是1到n的数
    read t
    s=`factor $t`                   # ``是把其中的命令替换成命令的输出
    # s存的就是factor的结果
    ss=`echo $s | sed "s/[0-9:]//g"`# ss存s中空格组成的字符串
    if [ ${#ss} -eq 1 ]; then       # -eq表示等于
        echo Prime                  # 输出质数
    else
        echo $s | sed "s/ /\n/g" | tail -n1 #输出最大因数
    fi
done
```

虽然洛谷上没有`sh`或者`bash`这样的语言，但是可以使用C的`system()`或者Python的`os.system()`函数提交。

最后介绍一下多行raw string的写法，这样就可以直接复制脚本了。
```cpp
R"(
多行字符串
可以带\，不会转义
)"              //C++11

```
```python
r'''
多行字符串
可以带\，不会转义
'''             #python
```

---

## 作者：WeLikeStudying (赞：43)

**素性测试**
- 测试一个数是否是质数。
- 应该都学过 $O(\sqrt n)$ 的试除法，基于 $\forall  ab=c(a,b,c\in \mathbf{Z^+}),\min(a,b)\leq\sqrt c$
- 米勒·拉宾算法，$O(\log_2n)$ 的随机算法。（没错这就是正确率接近 100% 的随机算法）
- 印度小哥有个非随机算法唤作 AKS，不过实用性稍低不讲，米勒·拉宾已经足够优秀~~同时足够简单~~。
- 米勒·拉宾算法基于费马小定理，即：
$$\forall p\nmid a,\quad a^{p-1}\equiv1\pmod p$$
- 于是便产生了一种朴素的想法：对于待测试的数 n ，随机一个 $0<a<n$ 计算 $a^{n-1}\bmod n$ 若结果不为 1 即可排除 n 是质数。 
- 但这显然是必要不充分条件，事实上，存在一些合数 n，满足：
$$\forall a\bot n,\quad a^{n-1}\equiv1\pmod n$$
- 这类数称为 Carmichael 数，如 $561=3×11×17$ ，这类做法很难试出来，也许你见到的 Carmichael 数因子都很小，但是在题目的数据范围，我可以构造出 $n=999211956328352449=550177\times 1100353\times 1650529$，没错，他也是 Carmichael 数，此时，你又该如何应对！
- 哈哈哈，是不是没有办法了。
- 所以还需要~~平方差公式~~奇素数判定，除了 2 以外的质数，都是奇数！而奇数减一，就是偶数啊！~~两句大废话。~~
- 换句话说，若 $a^{n-1}\equiv1\pmod n$ 则 $(a^{\frac{n-1} 2}+1)(a^{\frac{n-1} 2}-1)\equiv0\pmod n$，也就是 $a^{\frac{n-1} 2}\equiv-1\pmod n$，$a^{\frac{n-1} 2}\equiv1\pmod n$ ，如果 $\frac {n-1} 2$ 是偶数，还可以验证 $\frac {n-1} 4$ 。
- 也就是说我们实际上用来判定的定理是：令 $n-1=2^x\cdot y$ （y 是奇数），若 $n\in\mathbf{P}$ 则 ，对于 $a^y\equiv1\pmod n$ 或 $\exists k\in[0,x],\quad a^{2^k\cdot y}\equiv-1\pmod n$（其实那个区间是左闭右开的，我只是讨厌下划线，而且加上也不影响）
- 用原根~~我们不会涉及~~的原理可以证明至少存在一个 $a\bot n$ 把 $n$ 是合数的情况判掉。
- 用~~仍然不会涉及的知识~~可以证明对于奇合数 $n$ 非证据的数目至多是 $\dfrac{n-1}4$ 。
- 根据维基百科的说法，用不超过 37 的质数即可判定 $2^{64}$ 或 $18446744073709551616$ 范围的 n 。
- [代码实现](https://www.luogu.com.cn/paste/sw8ndzqz)。
- 如果不是枚举再快速幂是可以做到 $O(\log_2n)$ 而非 $O(\log_2^2n)$ 的。
- 注意 $\text{OI wiki}$ 上给出的复杂度是考虑了巨大整数无法进行 $O(1)$ 加减乘除的情况。

**质因数分解**
- 试除法仍然是 $O(\sqrt n)$ 复杂度。
- Pollard-rho 可以做到理论 $O(\sqrt[4]n\log_2n)$ 的复杂度，且在实际运行中跑得飞快。
- 主要思想是如何快速用随机数试出某个数的因子。
- 生日攻击悖论：对于一个理想的取值为 $[1,n]$ 的随机数生成器，生成 $\sqrt {\dfrac{\pi n}2}$ 个数期望得到两个数相同。
- 如果一个数 $n$ 不是质数，那么它的最小质因子 $p_x$ 满足 $p\leq\sqrt n$
- 如果我们随机生成 $\sqrt[4]n$ 个数，那么期望存在两个数 $a,b$ 使得 $a\equiv b\pmod {p_x}$。那么 $|a-b|$ 就是 p 的倍数，可以通过求 $\gcd(|a-b|,n)$ 得到一个因子。
- 但我们发现这样做复杂度又乘了回去，由于还有 gcd 的运算，复杂度直接变成 $O(\sqrt n\log_2n)$ 。
- Pollard 构造了这样一组数列 $\lbrace a_i\rbrace$ 满足 $a_0=x$ 且 $a_{i+1}=(a_i^2+c)\bmod n$ 。
- 这个数列有一个不得了的性质，任取数列中的两个数 $a_i,a_j$ ，若 $a_i-a_j\equiv0\pmod {p_x}$，~~根据平方差公式~~:
$$a_{i+1}-a_{j+1}=(a_i^2+c)-(a_j^2+c)=a_i^2-a_j^2$$
$$=(a_i+a_j)(a_i-a_j)\equiv0\pmod {p_x}$$
- 所以我们最好每次检查不同的距离。
- 这样的数据随机性当然有保证。
- 给张 Excel 自制散点图看一下。($a_0=3222,a_{i+1}=(a_i^2+24)\bmod9409$，给出数列的前 1000 项)
![你能看出这张图是循环的吗](https://cdn.luogu.com.cn/upload/image_hosting/37hgicue.png)
- 大概一看，的确是分布地比较均匀，不过仔细一看你就会发现：数列之间好像有循环？
- 没错，显然这种伪随机数一旦出现相同的就会循环，而由于数据范围固定，很容易进入循环，形成混循环（即rho形结构）（我之前的数据经过特制，使得环长较长，实际环长还要更短）（如图 $a_0=121,a_{i+1}=(a_i^2+11)\bmod 1014$），如果进入循环还一直不停地检查就太傻了。
![$\rho$](https://cdn.luogu.com.cn/upload/image_hosting/ol7wlz84.png)
- 给出一种名叫 floyd （没错就是弗洛伊德）的判环方法。
- 第 $k$ 次操作让一个数为 $a_k$ ，另一个数为 $a_{2k}$（这很容易做到，迭代两次就好了），如果 $a_k=a_{2k}$ 那么显然已经进入环中，直接跳出即可。
- 显然进入环中后 $k$ 会慢慢增加到某个环长的倍数，终止可行。
- 而且这样每次只要检查 $\gcd(|a_{2k}-a_k|,n)$ 就能够保证不同的距离，可谓一举两得。（另外 $a_{2k}=a_k$ 时，即使整除）
- 不过，你有没有发现一些问题？
- **这其实并没有做到检查全部的数对**，你可以暂时理解成，由于以上的性质，其实我们已经检查了大部分的情况。~~毕竟我们绝对不能讲超过高中的知识~~。
- 刚才那个问题令我们想到一个问题，就是如果环长为1，那么一下子慢的跳到 $a_1$，快的跳到 $a_2$，下一步直接结束然后无限循环，所以正确的做法是在第 $k$ 步跳到 $a_{k-1}$ 和 $a_{2k-1}$。
- 如果我们给的伪随机数随机性够高，且我们的检测方法事实上接近于两两求差，则期望在 $O(\sqrt[4] p\log_2n)$ 的复杂度内给出 $n$ 的最小质因子 $p$ 。
- 很遗憾，这里不能给出复杂度的严格证明，但事实上时间复杂度并没有因为多次寻找因子而改变，仍然是 $O(\sqrt[4]n\log_2n)$，给出一个表格看一下这个算法在不同数字下的运算次数~~当然在我的程序下~~。

| 数字 | 质因数分解式 | 最大运算次数 | 最小运算次数 | 平均运算次数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $9223372036854775808$ | $2^{63}$ | $3611$ |$2158$|$2900.72$
| $9223372036854775783$ | 是质数 | $610$ |$610$ |$610$ |
| $9223371994482243049$ | $3037000493^2$ | $6434444$ |$245074$|$2301568.32$
| $9223253290108583207$ | $2097143^3$ | $239219$ |$28609$|$111099.06$
| $2147483648$ | $2^{31}$ | $1246$ |$843$|$1004.33$
| $2147483647$ | 是质数 | $300$ |$300$|$300$
| $2147117569$ | $46337^2$ | $14255$ |$487$|$5971.98$
| $2141700569$ | $1289^3$ | $3655$ |$522$|$1890.79$

- [代码实现](https://www.luogu.com.cn/paste/8gnuzk91)。
- 上例题！
- [【模板】Pollard-Rho算法](https://www.luogu.com.cn/problem/P4718)
- 这道题靠之前那个模板会 TLE 一个点。
- 于是我们可以进行一个简单的优化，我们可以尝试把一段数乘起来 $\bmod n$ 来减少常数。
- 但这样可能会导致 floyd 过晚退出，而且乘出 $n$ (一点用也没有）的概率也会增加。
- 我们可以进行一个折中的方法：每隔约 $\log(n)$ 次进行一次 gcd，然后就可以消掉 gcd 的复杂度，理论时间复杂度为 $O(\sqrt[4]n)$。
- AC 地太轻松了？
- 再次给出这个算法复杂度的表。

| 数字 | 质因数分解式 | 最大运算次数 | 最小运算次数 | 平均运算次数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $9223372036854775808$ | $2^{63}$ | $9625$ |$1444$|$3624.04$
| $9223372036854775783$ | 是质数 | $610$ |$610$ |$610$ |
| $9223371994482243049$ | $3037000493^2$ | $805484$ |$3803$|$249223.63$
| $9223253290108583207$ | $2097143^3$ | $27931$ |$699$|$7487.53$
| $2147483648$ | $2^{31}$ | $1578$ |$74$|$265.49$
| $2147483647$ | 是质数 | $300$ |$300$|$300$
| $2147117569$ | $46337^2$ | $5446$ |$345$|$1407.82$
| $2141700569$ | $1289^3$ | $2918$ |$126$|$687.6$
- 对比即可发现这个简单优化的优越性能。
- 不过 Pollard 算法确实不是很稳定。
- [代码实现](https://www.luogu.com.cn/paste/8h81rzqz)。

---

## 作者：Piwry (赞：40)

## 前言

半年前我曾写了一次 PR 的代码，不过当时是照着 AC 代码玄学调试（~~还是概率~~）过的，注释打的也大部分都是调试坑点，和算法正确性丝毫没有关系...（~~毕竟是道黑题怎么也得想办法过掉~~）

半年后~~为了做 lxl 的某道[题](https://www.luogu.com.cn/problem/P5071 "lxl毒瘤！（划）")~~，我再次打开了这道题目。不过发现自己以前写的代码太丑了，打算重写一份。

于是和着算法导论上的代码，差不多地打了一份；交上去 T 的很惨。接着开始试着寻找关于 Pollard-Rho 算法的资料，根据对复杂度的理解再打了一份，总算是稳过了。（当然中途也少不了被数据各种卡的调试部分）

（话说过程中因看不懂算导在 ~~bb~~ 写什么就去网上搜了一圈，结果最后还是看算导理解的qaq）

写完又翻了下题解，发现几乎没人涉及到算法复杂度的部分，尤其是**期望复杂度 $\sqrt p$ 是怎么来的**。于是就打算自己另写一篇题解了qwq

&nbsp;

以上全是废话，由于我的问题语文读着还不太通，只是纪念性地写在这。看到这句话请无视以上所有文字接着看正文（

## 算法解析

首先我们思考一个下一项仅由上一项决定，且值域为模 $n$ 的剩余系的序列 $\text{<}x\text{>}$

例如 $x_i=(x_{i-1}^2+1)\pmod n$

由于它某项的值仅由前一项决定，且每一项可能的取值是有限的，因此该数列一定会在经历一定次数的迭代后陷入循环

![rho](https://cdn.luogu.com.cn/upload/image_hosting/yaihaze5.png "像不像一个 rho")

更具体的来说，只要该序列中**出现一对相同的数**，就会在这对数间产生环

联想到生日悖论，若这个数列是期望随机的，则它的 "环" 及 "尾" 的期望长度就是 $\sqrt n$ 的

为了说明方便，下面我们就先假设由该递推式导出的序列都是**足够随机**的，并以此继续讨论。

&nbsp;

现在我们假设 $n$ 不是质数，或者说它至少有一对非平凡因子（指该因子不为 $1$ 或 $n$）；则 $n$ 可以表示为 $n=p_1^{r_1}\cdot p_2^{r_2}\cdots p_m^{r_m}$

这里我们随意取一个 $p_i$ 并设为 $p$

再考虑一个序列 $\text{<}x'\text{>}$，其中 $x'_i=x_i\pmod p$

我们可以发现，由于数列 $\text{<}x\text{>}$ 的递推式仅有加减乘除运算，因此数列 $\text{<}x'\text{>}$ 其实和它有着同样的递推式：

${x'}_i=x_{i-1}\pmod p$

${x'}_i=((x_{i-1}^2+1)\pmod n)\pmod p$

${x'}_i=(x_{i-1}^2+1)\pmod p$

${x'}_i=((x_{i-1}\pmod p)^2+1)\pmod p$

${x'}_i=({x'}_{i-1}^2+1)\pmod p$


由此可以预知序列 $\text{<}x'\text{>}$ 也会产生 "环"。而根据生日悖论，序列 $\text{<}x'\text{>}$ 的环的长度就是期望 $\sqrt p$ 的。

![2rho](https://cdn.luogu.com.cn/upload/image_hosting/2ull97fr.png "序列 <x'> 就像是 <x> 的较小版本")

注意到当 ${x'}_i\equiv {x'}_j\pmod p$ 时，一定有 $p | (|x_i-x_j|)$；此时若$x_i\neq x_j$，通过计算 $\gcd(|x_i-x_j|, n)$，一定就可以得到 $n$ 的因子 $p$

若我们沿着 "$\rho$" 的路径遍历数列，不难想到，是可以在期望记录 $n^{\frac 1 4}$ 个元素后就能找出一对 $x_i, x_j$，并以此计算出 $n$ 的某个非平凡因子

## 算法实现

### 随机数

首先我们要考虑就是序列 $\text{<}x\text{>}$ 的数是否足够随机

这里我没找到可行的证明（qaq）；不过根据算法实际效率来看，这种生成方式是足够优秀的

不过为了保证数列在更多情况下依然足够随机，我们使用更一般的公式 $x_i=x_{i-1}^2+c$，并在初始时随机带入一个 $x$ 和 $c$ 并进行迭代

不过注意当 $c=0$ 或 $c=2$ 的情况应当避免（来自算法导论，书上也没有具体解释原因）

### 初始的实现方式

设最大的不在 "环" 上的序列编号 $s$，对于每一个序号 $t, t>s$，一定能找到一个序号 $t'$ 使得 $x_t\equiv x_{t'}\pmod p$

因此我们可以考虑设一个定点 $y$ 和一个动点 $x$；$x$ 根据序列的迭代公式一步步计算，期望会在 $n^{\frac 1 4}$ 步内找到 $n$ 的一个非平凡因子

但我们很难确定 $y$ 是否在序列的 "环" 上。具体实现时我们倍增地设置 $y$ 的序号即可

```cpp
/*其中 rand(l, r) 代表取这个闭区间的随机数*/
ll pr(ll n){
    ll x =rand(0, n-1), y =x;
    ll c =rand(3, n-1), d =1;
    for(int i =1, k =2; d == 1; ++i){
        x =(x*x+c)%n;
        d =gcd(abs(y-x), n);
        if(i == k){
            y =x;
            k <<=1;
        }
    }
    return d;
}
```

### Floyd 判环

上面的算法在大多数情况下已经足以应付了

但我们发现，在极少数情况下，该算法甚至在遍历整个模 $n$ 的 "$\rho$" 数列后仍然无法找到解

这时候我们就要判环并重新尝试

具体来说，我们另设一个点 $y$ 和 $x$ 在同一起点出发，但该点以 $x$ 两倍的速度按公式迭代，当 $x\equiv y\pmod n$ 时我们就找到了环。期望环的长度是 $\sqrt n$ 的，我们可以证明该算法能在 $O(\sqrt n)$ 的时间内判断出环

至于算法的证明，设起点距离进入环还有 $s$ 步，环长 $c$，点 $x$ 走了 $k$ 步；则想要令 $x, y$ 相遇就需要使 $k-s\equiv 2k-s\pmod c$ 且 $k> s$，这显然可以做到

同时注意在算法结束时，点 $y$ 会至少遍历环一次，但 $x$ 不一定会

### 基于 Floyd 的实现

由于序列 $\text{<}x'\text{>}$ 可以看做是 $\text{<}x\text{>}$ 的较小版本，或者说这两个序列存在一一对应的关系，我们的 Floyd 判环其实对序列 $\text{<}x'\text{>}$ **也是适用**的。

具体来说，当我们发现 Floyd 算法内的两动点满足 $x\equiv y\pmod p$ 时（尽管我们可能不会检查这个式子），$\gcd(|x-y|, n)$ 就会给出 $n$ 的一个非平凡因子。而 Floyd 算法显然会比我们上面的倍增法要快许多

```cpp
ll pr(ll n){
	/*因为初始跳两步的原因，该写法没法分解 4*/
	if(n == 4) return 2;
	ll x =rand(0, n-1), y =x;
	ll c =rand(3, n-1);
	ll d =1;
	x =(x*x+c)%n;
	y =(y*y+c)%n, y =(y*y+c)%n;
	while(x != y){
		x =(x*x+c)%n;
		y =(y*y+c)%n, y =(y*y+c)%n;
		d =gcd(abs(x-y), n);
		if(d != 1)
			return d;
	}
	return n;
}
```

### 初始实现的判环改进

当然，如果加上判环部分，一开始的初始实现也是可行的

```cpp
ll pr(ll n){
	/*因为初始跳两步的原因，该写法没法分解 4*/
	if(n == 4) return 2;
	ll x =rand(0, n-1), y =x, y2 =x;
	ll c =rand(3, n-1);
	x =(x*x+c)%n;
	y2 =(y2*y2+c)%n, y2 =(y2*y2+c)%n;
	for(int i =1, k =2; x != y2; ++i){
		x =(x*x+c)%n;
		y2 =(y2*y2+c)%n, y2 =(y2*y2+c)%n;
		ll d =gcd(abs(x, -y), n);
		if(d != 1)
			return d;
		if(i == k){
			y =x;
			k <<=1;
		}
	}
	return n;
}
```

### 倍增积累 gcd

我们发现在模 $n$ 意义下将每次的 `abs(x-y)` 相乘，若对于某一个 $|x_i-y_i|$ 有 $d=\gcd(|x_i-y_i|, n)$ 且 $d$ 为 $n$ 的非平凡因子；则它们的积，这里设为 $cnt$，也一定有 $d'=\gcd(|x_i-y_i|, n)$ 且 $d'$ 为 $n$ 的非平凡因子

具体来说，我们可以积累一定的样本再做 $\gcd$，这样能节省一些时间，且不会影响每个样本的答案

这个阈值可以设为倍增的，且可以设一个上限。以本题数据来说设为 $128$ 会有不错的效果

这里仅给出以 "基于 Floyd 的实现" 为模板改进的代码

```cpp
ll pr(ll n){
	if(n == 4) return 2;
	ll x =rand(0, n-1), y =x;
	ll c =rand(3, n-1);
	ll d =1;
	x =(x*x+c)%n;
	y =(y*y+c)%n, y =(y*y+c)%n;
	for(int lim =1; x != y; lim =min(128, lim<<1)){
		ll cnt =1;
		for(int i =0; i < lim; ++i){
			ll tmp =cnt*abs(x-y)%n;
			/*这时要么原先的 cnt 以及此时的 |x-y| 含 n 质因数 ，要么 x-y == 0*/
			/*为了避免之前的样本丢失，直接推出循环并对之前积累的样本做一次计算*/
			if(!tmp)
				break;
			cnt =tmp;
			x =(x*x+c)%n;
			y =(y*y+c)%n, y =(y*y+c)%n;
		}
		d =gcd(cnt, n);
		if(d != 1)
			return d;
	}
	return n;
}
```

## CODE

代码里有详尽的注译

其中 `pr()` 函数中，我将 "初始实现的判环改进" 注译起来了，并标为 "算法2"

同时代码中使用的随机数生成函数是 `std::mt19937`；不过在本题的数据表现中，其和一般的 `rand()` 函数差别不大

```cpp
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#define ll long long
#define ull unsigned long long
#define lll __int128
//#pragma GCC target("avx")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize(2)

/*------------------------------Base------------------------------*/

inline ll mul(ll a, ll b, const ll M){
	ll d =a*(long double)b/M;
	ll ret =a*b-d*M;
	if(ret < 0)
		ret +=M;
	if(ret >= M)
		ret -=M;
	return ret;
}

inline ll plus2(ll a, ll b, const ll M){
	ll d =(a+(long double)b)/M+0.5;
	ll ret =a+b-d*M;
	if(ret < 0)
		ret +=M;
	return ret;
}

inline ll plus(const lll a, const lll b, const lll M){
	lll c =a+b;
	if(c >= M)
		return c-M;
	else
		return c;
}

ll Pow(ll x, ll k, const ll M){
	ll ret =1;
	for(; k; x =mul(x, x, M), k >>=1) if(k&1) ret =mul(ret, x, M);
	return ret;
}

ll gcd(ll a, ll b){
	while(b) b ^=a ^=b ^=a %=b;
	return a;
}

inline ll Abs(ll x){ return (x < 0) ? -x : x; }

/*------------------------------Rand------------------------------*/

static std::mt19937 engine;

/*------------------------------Miller Robin------------------------------*/

bool mr(ll p){
	if(p < 2) return 0;
	if(p == 2) return 1;
	if(p == 3) return 1;
	std::uniform_int_distribution<ll> Rand(2, p-2);
	ll d =p-1, r =0;
	while(!(d&1)) ++r, d >>=1;
	for(ll k =0; k < 10; ++k){
		/*[2, p-2]*/
		ll a =Rand(engine);
		ll x =Pow(a, d, p);
		if(x == 1 || x == p-1) continue;
		for(int i =0; i < r-1; ++i){
			x =mul(x, x, p);
			if(x == p-1) break;
		}
		if(x != p-1) return 0;
	}
	return 1;
}

/*------------------------------Pollard Rho------------------------------*/

using std::min;

/*貌似 -c 在本题的数据的效率高些 (0.2s)，原因尚不确定*/
inline ll getnext(ll x, ll c, ll n){ return plus(mul(x, x, n), -c, n); }

ll pr(ll n){
	/*因为初始跳两步的原因，下面写法均没法分解 4 (即使下面的 Rand 范围设置为 [0, n-1] )*/
	if(n == 4) return 2;
	std::uniform_int_distribution<ll> Rand(3, n-1);
	ll x =Rand(engine), y =x;
	ll c =Rand(engine);
	ll d =1;
	
	/*以下两种写法的期望复杂度都是正确的，但写法 1 的表现更好*/
	
	/*----------写法 1----------*/
	
	x =getnext(x, c, n);
	y =getnext(y, c, n), y =getnext(y, c, n);
	for(int lim =1; x != y; lim =min(128, lim<<1)){/*提升约 0.1s */
//	for(int lim =1; x != y; lim =lim<<1){
		ll cnt =1;
		for(int i =0; i < lim; ++i){
			ll tmp =mul(cnt, Abs(plus(x, -y, n)), n);
			if(!tmp)/*提升约 0.6s；这时要么原先的 cnt 含 n 质因数 (这时 x-y 也含 )，要么 x-y == 0*/
				break;
			cnt =tmp;
			x =getnext(x, c, n);
			y =getnext(y, c, n), y =getnext(y, c, n);
		}
		d =gcd(cnt, n);
		if(d != 1)
			return d;
	}
	return n;
	
	/*----------写法 2----------*/
	/*这里还加了倍增 gcd 优化，可以作为参考*/
	
	/*
	x =getnext(x, c, n);
	y =getnext(y, c, n), y =getnext(y, c, n);
	ll x2 =x, cnt =1;
	for(int i =1, i2 =1, k =2, lim =1; x != y; ++i, ++i2){
		x =getnext(x, c, n);
		y =getnext(y, c, n), y =getnext(y, c, n);
	//	d =gcd(Abs(plus(x, -x2, n)), n);
		ll tmp =mul(cnt, Abs(plus(x, -x2, n)), n);
		if(tmp)
			cnt =tmp;
		if(i2 == lim || !tmp || x == y){
			i2 =1;
			lim =min(128, lim<<1);
			d =gcd(cnt, n);
			if(d != 1)
				return d;
			cnt =1;
		}
	//	if(d != 1)
	//		return d;
		if(i == k){
			x2 =x;
			k <<=1;
		}
	}
	return n;*/
}

ll mxp;

inline void push(ll p){
	if(p > mxp)
		mxp =p;
}

/*函数要求保证 n 可分解*/
void dfs(ll n){
	srand(time(0));
	ll d =pr(n), d2;
	while(d == n)
		d =pr(n);
	d2 =n/d;
	if(mr(d))
		push(d);
	else
		dfs(d);
	if(mr(d2))
		push(d2);
	else
		dfs(d2);
}

ll getfact(ll n){
	mxp =0;
	if(mr(n))
		return n;
	else
		dfs(n);
	return mxp;
}

/*------------------------------Main------------------------------*/

inline ll read(){
	ll x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	srand(time(0));
	for(int t =0, T =read(); t < T; ++t){
		ll n =read();
		ll fact =getfact(n);
		if(fact == n)
			puts("Prime");
		else
			printf("%lld\n", fact);
	}
}
```

---

## 作者：FutaRimeWoawaSete (赞：27)

主要讲解 Miller_Rabin&Pollard Rho。

资料主要是洛谷 P4718 的部分题解及 oiwiki。

# 费马定理

即对于质数 $p$：

- $\forall a \in [1 , p - 1],a ^ {p - 1} \equiv 1 \pmod p$

同时存在逆定理即：

- $\exists a \in [1 , p - 1],a ^ {p - 1} \not \equiv 1 \pmod b$

则 $p$ 一定不为质数。

据此，我们在 $[1,p - 1]$ 内筛选一些数来做上述运算，如果选择的数对于上述运算的结果都为 $1$ 则 $p$ 大概率是质数，否则 $p$ 一定是合数。

这个方法也被称为**费马素性检验**。可是存在一些被称作卡迈克尔数的数，他们既是合数也满足费马定理的式子，据统计，在 $10 ^ 9$ 以内就有 $646$ 个卡迈克尔数，所以这个方法的风险很大。


# 二次探测定理

若 $p$ 为奇素数，则满足 $x ^ 2 \equiv 1$ 的解为 $x = 1 \lor x = p - 1$。


# Miller_Rabin


根据二次探测定理，在确定 $n$ 只有可能是奇素数下，我们同样随机一些基底，可以将 $n - 1$ 拆成 $n - 1 = r \times 2 ^ t$，先求出基底 $z$ 它 $z ^ r$ 在 $n$ 的模意义下的值，若为 $1$ 则不考虑该基底。

接着平方 $t$ 次，如果该数存在一个解为 $n - 1$ 那么就说明该数可能为素数；如果一个基底中不存在一个解为 $n - 1$ 那么说明该数为合数。

这么做其实本身也没有完全的逻辑，只是大大提高了正确率。

经计算，若我们选择 $k$ 个基底，错误率仅为 $\frac{1}{4 ^ k}$，这已经是个很好的期望算法了。 

code：

```cpp
const __int128 ONE = 1;
bool millerRabin(ll n) 
{
    if (n < 3 || n % 2 == 0) return n == 2;
    ll a = n - 1 , b = 0 , tt = 11;
    while (a % 2 == 0) a /= 2 , ++ b;
    for(int i = 1 ; i <= tt ; i ++)
    {
        ll x = 1ll * rand() * rand() % (n - 2) + 2 , v = qpow(x , a , n);
        if (v == 1) continue;int j;
        for(j = 1 ; j <= b ; j ++) 
        {
            if (v == n - 1) break;
            v = (ll)v * v % n;
        }
        if (j > b) return 0;
    }
    return 1;
}
```

不过存在一种**在 OI 领域具有完全正确性的做法**，即**当值域 $V \leq 2 ^ {78}$ 时**，我们可以通过固定底数为前 $12$ 个素数 $2,3,5,7,11,13,17,19,23,29,31,37$，来实现确定性判素。

这个东西的原理其实我也不是很懂，但是如果你有闲心~~一定能通过打表检验的~~，在此就不多提了。

以下是代码实现：

```cpp
int Suk[25]={0,2,3,5,7,11,13,17,19,23,29,31,37};
inline bool chk(ll n,ll a,ll b,ll x) 
{
    ll v = qpow(x , a , n);
    if (v == 1) return 1;
    int j = 1;
    while(j <= b)
    {
    	if(v == n - 1) break;
		v = ONE * v * v % n;
		j ++;
	}
    if (j > b) return 0;
    return 1;
}
inline bool mr(ll n)
{
	if(n < 3 || n % 2 == 0) return n == 2;
	if(n > 37)
	{
		ll a = n - 1 , b = 0;
		while(a % 2 == 0) a >>= 1 , b ++;
		for(int i = 1 ; i <= 12 ; i ++) if(!chk(n , a ,  b , Suk[i])) return 0;
		return 1;
	}
	else
	{
		for(int i = 1 ; i <= 12 ; i ++) if(n == Suk[i]) return 1;
		return 0;
	}
}
```

关于黎曼猜想，既然他也只能做 $O(\log ^ 5 V)$ 那在当今算法竞赛领域还是很难用到，就还是先咕咕咕吧（

# 生日悖论

考虑一个大小为 $k$ 的人群中，其中至少有两个生日相同人的概率是多少。

用普通的期望概率求解方法，求解 $P(A)$ 表示人群中无生日相同的一对人的概率，显然是 $P(A) = \prod_{i = 1} ^ k \frac{365 - i + 1}{365}$，进行值的带入计算可以发现在 $60$ 左右时 $P(A)$ 已经下降到 $0.0001$ 左右了，而 $1 - P(A)$ 即两人生日相同的概率就很大了。

经计算，对于任意的 $k$，该问题在 $\sqrt k$ 的时候概率就很大了。

# Pollard rho 算法原理

该算法可用于解决一个**合数 $n$**，其最大的质因子。

首先引入一个数学模型：构造函数 $f(x) = (x ^ 2 + c) \pmod n$。

构造序列，随机选取 $x_1$，并且令 $\forall i \geq 2,x_i = f(x_{i - 1})$。

考虑该序列的期望循环节长。不难发现如果出现了 $x_i = x_j,i \not = j$ 的情况出现一定出现了环。

将序列抽象化，可以发现它长成“ρ”的样子，这也是这个算法的得名。

根据上述的生日悖论问题的探讨，我们不难发现环长与尾长的期望都是 $\sqrt n$。

取 $n$ 的一个质因子 $p$。

接着我们继续构造一个映射序列，$y_i = x_i \pmod p$。

构造函数 $g(x) = (x ^ 2 + c) \pmod p$

由于 $p < n$，所以 $y_i$ 也可以构造递推式 $y_i = g(y_{i - 1})$。

和上述情况一样，$y$ 序列的环长与尾长的期望都是 $\sqrt p$。

我们要用 $y$ 序列干什么呢？我们可以发现若 $y_i = y_j,i \not = j$，则：

- $x_i \equiv x_j \pmod p$

- $p\mid|x_i-x_j|$

通过计算 $\gcd(|x_i - x_j|,n)$ 我们可以得出一个至少包含了质因子 $p$ 的数 $z$，对于本题而言若 $z$ 是质数考虑贡献答案，否则我们就可以递归计算 $z$ 与 $\frac{n}{z}$ 的最大质因子。

接着我再简述该算法的主要流程，会更方便理解一些：先随机 $x_1$ 构造 $x$ 序列，接着得出构造的 $y$ 序列，我们考虑使用两个指针 $a,b$ 使两指针保持 $b = 2a$ 的大小关系，每次看 $d = \gcd(|x_a - x_b|,n)$ 是不是 $1$，不是的话就直接把这个 $d$ ，也就是一个 $n$ 的因数拿出来向上述那样直接贡献或递归计算。

可以发现这样做，一定可以在 $a$ 大小为环长的 $1 \sim 3$ 倍时找到这个环并且把这个 $d$ 找出来，也就是说 **$y$ 序列是一个隐性的序列**，是我们并没有直接构造出来的。

显然对 $n$ 做一次上述操作的时间复杂度记为 $c(n)$，则 $c(n) = \sqrt p$，其中 $p$ 在期望上是 $n$ 的最小质因子，因为期望下第一个找到的 $p$ 它的 $y$ 序列的大小应该是尽量小的，所以期望找到的就是最小的质因子。

根据主定理，此题这样的做法是 $T(n) = c(n) + T(\frac{n}{p}) + T(p)$ 最后的数量级仍然是 $c(n)$。

同时这也是为什么时间复杂度上存在 $O(n ^ {\frac{1}{4}})$ 以及 $O(\sqrt p)$ 两种说法：因为在使用 Miller_Rabin 判素后该数是一个合数，所以其存在的最小质因子一定在 $\sqrt n$ 以内，可以算成 $O(n ^ {\frac{1}{4}})$。当然严格上来说我还是更倾向于 $O(\sqrt p)$ 这种说法。

# Pollard rho 算法优化

显然的是由于要求 $\gcd$，所以这个算法常数还是略大。

观察到我们并没有必要每次都做一次 $\gcd$，不妨将操作分块，对于每个块计算 $e = \prod |x_a - x_b| \pmod n$。

若一个块内存在一次枚举的 $\gcd(|x_a - x_b|,n) \not = 1$，显然 $\gcd((\prod |x_a - x_b|),n) \not = 1$，则：

- $\gcd((\prod |x_a - x_b|),n) = \gcd((n,\prod |x_a - x_b|)\pmod n) = \gcd(e , n)$

所以对于每一块的 $e$ 统计出来再计算一次 $\gcd$ 是可以保证答案的有解性，并且运行时间也趋近于 $\sqrt p$。

将块长调成 $128$ 在大量数据下运行效率比较高。

以下是实现代码。

```cpp
static std::mt19937 MoBaiXHR;
inline ll F(ll x,ll c,ll MOD){return (ONE * x * x % MOD + c) % MOD;}
inline ll ABS(ll x){if(x < 0) return -x;return x;}
ll gcd(ll a,ll b)
{
	if(!b) return a;
	return gcd(b , a % b);
}
inline ll pr(ll n)
{
	if(n == 4) return 2;
	std::uniform_int_distribution<ll> Rand(3 , n - 1);
	ll x = Rand(MoBaiXHR) , y = x , c = Rand(MoBaiXHR);
	x = F(x , c , n) , y = F(F(y , c , n) , c , n);
	for(int lim = 1 ; x != y ; lim = min(lim << 1 , 128))
	{	
		ll cnt = 1;
		for(int i = 0 ; i < lim ; i ++) 
		{
			cnt = ONE * cnt * ABS(x - y) % n;
			if(!cnt) break;
			x = F(x , c , n) , y = F(F(y , c , n) , c , n);
		}
		ll d = gcd(cnt , n);
		if(d != 1) return d;
	}
	return n;
}
```
最后此题总代码：
```cpp
#include "bits/stdc++.h"
using namespace std;
#define ll long long
const __int128 ONE = 1;
ll qpow(ll a,ll b,ll mod)
{
	ll res = 1;
	while(b)
	{
		if(b & 1) res = ONE * res * a % mod;
		a = ONE * a * a % mod;
		b = b >> 1;
	}
	return res;
}
int Suk[25]={0,2,3,5,7,11,13,17,19,23,29,31,37};
inline bool chk(ll n,ll a,ll b,ll x) 
{
    ll v = qpow(x , a , n);
    if (v == 1) return 1;
    int j = 1;
    while(j <= b)
    {
    	if(v == n - 1) break;
		v = ONE * v * v % n;
		j ++;
	}
    if (j > b) return 0;
    return 1;
}
inline bool mr(ll n)
{
	if(n < 3 || n % 2 == 0) return n == 2;
	if(n > 37)
	{
		ll a = n - 1 , b = 0;
		while(a % 2 == 0) a >>= 1 , b ++;
		for(int i = 1 ; i <= 12 ; i ++) if(!chk(n , a ,  b , Suk[i])) return 0;
		return 1;
	}
	else
	{
		for(int i = 1 ; i <= 12 ; i ++) if(n == Suk[i]) return 1;
		return 0;
	}
}
static std::mt19937 MoBaiXHR;
inline ll F(ll x,ll c,ll MOD){return (ONE * x * x % MOD + c) % MOD;}
inline ll ABS(ll x){if(x < 0) return -x;return x;}
ll gcd(ll a,ll b)
{
	if(!b) return a;
	return gcd(b , a % b);
}
inline ll pr(ll n)
{
	if(n == 4) return 2;
	std::uniform_int_distribution<ll> Rand(3 , n - 1);
	ll x = Rand(MoBaiXHR) , y = x , c = Rand(MoBaiXHR);
	x = F(x , c , n) , y = F(F(y , c , n) , c , n);
	for(int lim = 1 ; x != y ; lim = min(lim << 1 , 128))
	{	
		ll cnt = 1;
		for(int i = 0 ; i < lim ; i ++) 
		{
			cnt = ONE * cnt * ABS(x - y) % n;
			if(!cnt) break;
			x = F(x , c , n) , y = F(F(y , c , n) , c , n);
		}
		ll d = gcd(cnt , n);
		if(d != 1) return d;
	}
	return n;
}
ll ans;
inline void MAX(ll z){if(z > ans) ans = z;}
void dfs(ll n)//非质数 
{
	ll d = pr(n);
	while(d == n) d = pr(n);
	ll d2 = n / d;
	if(mr(d)) MAX(d);
	else dfs(d);
	if(mr(d2)) MAX(d2);
	else dfs(d2);
}
ll getans(ll x)
{
	if(mr(x)) return x;
	ans = 0;
	dfs(x);
	return ans;
}
int main()
{
	srand(time(0));
	int T;scanf("%d",&T);
	while(T --)
	{
		ll x;scanf("%lld",&x);
		ll res = getans(x);
		if(x == res) puts("Prime");
		else printf("%lld\n",res);
	}
	return 0;
}
```
# 总结

借助 Miller_Rabin&Pollard Rho，我们就有了在 OI 界，近乎确定性做法的快速判素和最值质因子求解的做法，其背后蕴藏的随机思想是近几年在 CF 上很流行的出题风向。

回首一年前的 [NOId2t1](https://www.luogu.com.cn/problem/P7738)，随机在中国的信息学竞赛领域也开始逐渐发展。



---

## 作者：皎月半洒花 (赞：27)

upd :多谢大佬` zhoutb2333（UID31564）`的指正，现在的题解已经是正确的了。

其实我的源程序有个很严重的bug，就是两个`Int64`类型我给直接乘起来了……于是就会导致一些奇怪的溢出。对于某些素数会被当成合数，于是无论怎样都判不出来质因子导致TLE……

然后大家如果想知道我是怎么知道这个问题的，可以左转讨论区看看我是怎么智障的……

反正最后呢，我发现在用龟速乘之后程序的判素性会变弱，于是又加了几个质数，开了O2就过了233

现在最新的代码放在了最下面。以下是原题解：
____

我想说一下这个题目是怎么卡常的。

虽然我的代码也不是很快……但是不至于$94pts$……

以下是战果：

![](https://cdn.luogu.com.cn/upload/pic/50558.png)

不着急，我们一点一点来：

## 一、$6000+\rm{ms} \to 4000+\rm{ms}$

首先奉上在下最慢的代码：

```cpp
LL Prime[11] = {2, 3, 5, 7, 13, 17, 19, 23} ;

inline LL expow(LL a, LL b, LL p){
    LL res = 1 ;
    while (b){
        if (b & 1) 
            (res *= a) %= p ;
        (a *= a) %= p, b >>= 1 ; 
    }
    return res % p ;
}
inline bool Test(LL p, LL x){
    LL r = 0, d = x - 1 ;
    while (!(d & 1)) d >>= 1, ++ r ;
    for (LL i = expow(p, d, x), j ; r ; -- r){
        j = i * i % x ;
        if (j == 1){
            if (i == 1 || i == x - 1) 
                return 1 ; 
            return 0 ;
        }
        i = j ;
    }
    return 0 ;
}
inline bool Miller_Rabin(LL x){
    if (x == 1) return 0 ;
    for (int i = 0 ; i < 8 ; ++ i){
        if (x == Prime[i]) return 1 ;
        if (!(x % Prime[i])) return 0 ;
        if (!Test(Prime[i], x)) return 0 ;
    }
    return 1 ;
}
LL res[MAXN], tot ;
inline int pksrand(){
    return rand() << 15 ^ rand() ;
} // 2
inline LL Irand(LL x){
    return (((LL)pksrand()) << 30 ^ pksrand()) % x ; //2
}
inline LL guisuMul(LL a, LL b, LL x){
    return (a * b - (LL) ((long double) a * b / x + 1e-9) * x) % x;
} 
inline LL qwq(LL x){
    LL A = Irand(x), C = Irand(x) ;
    LL t1 = A, t2 = (guisuMul(A, A, x) + C) % x ; // 1
    LL dif = max(t1, t2) - min(t1, t2), G = __gcd(x, dif) ;
    while (G == 1){
        t1 = (guisuMul(t1, t1, x) + C) % x ;
        t2 = (guisuMul(t2, t2, x) + C) % x ;
        t2 = (guisuMul(t2, t2, x) + C) % x ;
        dif = max(t1, t2) - min(t1, t2), G = __gcd(x, dif) ;
    }
    return G ;
}
inline void Pollard_Rho(LL x){
    if (x == 1) return ;
    if (Miller_Rabin(x)) {
        res[++ tot] = x ; return ;
    }
    LL y = x ; while (y == x) y = qwq(x) ;
    Pollard_Rho(y), Pollard_Rho(x / y) ;
}
int main(){
    cin >> T ;
    while (T --){
        scanf("%lld", &N), tot = 0, Pollard_Rho(N) ;
        if (tot == 1) { puts("Prime") ; continue ; } 
        sort(res + 1, res + tot + 1), printf("%lld\n", res[tot]) ; 
    }
} 
```

那么开始优化

*

* $1$、题目中让求最大的因子，而我一开始的做法是全部保存并且排一遍序。
但这显然是很蠢的举动。于是我们修改一下：

```cpp
inline void Pollard_Rho(LL x){
    if (x == 1) return ;
    if (Miller_Rabin(x)){
        Ans = max(Ans, x) ; return ;
    } 
    register LL y = x ; 
    while (y == x) y = qwq(x) ;
    Pollard_Rho(y), Pollard_Rho(x / y) ;
}
int main(){
    srand(19260817) ;
    T =qr() ;
    while (T --){
        N = qr(), Ans = -1, Pollard_Rho(N) ;
        if (Ans == N) puts("Prime") ;else printf("%lld", Ans), putchar('\n') ;
}
```

~~虽然这似乎没个卵用~~

* $2$、我们求$gcd$是很频繁的，所以我们尝试思考一种比较好的方式。大概就是二进制转化：

```cpp
#define mytz __builtin_ctzll

inline LL gcd(LL a, LL b){
    if(!a) return b;
    if(!b) return a;
    register int t = mytz(a|b) ;
    a >>= mytz(a) ;
    do{
        b >>= mytz(b) ;
        if(a>b){LL t=b;b=a,a=t;}
        b-=a;
    }while(b);
    return a<<t;
}
```

其中$\_\_builtin\_ctzll$是用来判断二进制下末尾零的数量(针对$int64$)的。原理的话大概就是二进制乱搞$233$……

* $3$、素数个数不用太多。这是实测，只需要$2$和$61$两个质数就可以卡过去。虽然质数的多少之于时间是个玄学的问题，但看起来似乎会快一些。并且，很重要的，**循环展开**，我们在$Miller\_Rabin$中完全没有必要$for$，毕竟素数个数很少，于是：

```cpp
inline bool Miller_Rabin(LL x){
    if (x == Prime[1] || x == Prime[0]) return 1 ;
    if (!(x % Prime[1]) || !(x % Prime[0])) return 0 ;
    if (Test(Prime[1], x) ^ 1) return 0 ;
    if (Test(Prime[0], x) ^ 1) return 0 ;
    return 1 ;
}
```

然后就喜闻乐见地拿到了$4500ms$左右的好成绩——可这似乎不能解决最后一个点仍然卡不过去的问题。

## 二、$4000+ms \to 3000+ms$

下面才是真正的卡常数……

首先注意到，我们需要频繁调用的$Rho$函数和$Miller$中的$check$，都或多或少定义了一些临时变量，而对于临时变量，我们是可以`register`优化的……当你全部加上`register`修饰符之后，你会发现你的程序快了接近$300+ms$……

但这不重要，重要的是接下来的卡常：

在$4000+ms$时，我的$rand$是这么写的：

```cpp
inline LL Irand(LL x){
    return ((LL)(rand() << 15 ^ rand()) << 30 ^ (rand() << 15 ^ rand())) % x ; //2
}//2
```
看上去并不可以优化，但事实上，只要我们改变一下那个强制类型转换的位置：

```cpp
inline LL Irand(LL x){
    return 1ll * ((rand() << 15 ^ rand()) << 30 ^ (rand() << 15 ^ rand())) % x ; //2
}//2
```
他就会快整整$500+ms$！！

这也从侧面印证了，强制类型转换才是最慢的运算。。。

所以，最后我们就成功地卡了过去qaq

稍微提一句，环境优化参数：

```cpp
#pragma GCC diagnostic error "-std=c++14"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
```

都加上的效果不是特别好，最好的是下面几句：

```cpp
#pragma GCC diagnostic error "-std=c++14"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
```

下面是完整版$\rm{qaq}$


```cpp
#define min my_min
#define LL long long
#define max(a, b) (((a) > (b)) ? (a) : (b))


using namespace std ; LL T, N ;
LL Prime[11] = {2, 61, 97, 7, 13, 17, 23, 29}, Ans = -1 ;

inline LL guisuMul(LL a, LL b, LL m){
    LL d =((long double)a / m * b + 1e-8) ;
    LL r = a * b - d * m ;
    return r < 0 ? r + m : r ;
} 
inline LL gsm(LL a, LL b, LL p){
    register LL res = 0 ;
    while (b){
        if (b & 1) 
           	res = (res + a) % p ;
        a = (a + a) % p, b >>= 1 ; 
    }
    return res ;
} 
inline LL expow(LL a, LL b, LL p){
    if (a == 1) return 1 ;
    register LL res = 1 ;
    while (b){
        if (b & 1) 
           	res = gsm(res, a, p) ;
        a = gsm(a, a, p), b >>= 1 ; 
    }
    return res ;
}
inline LL my_max(LL a, LL b){ return a > b ? a : b ; }
inline LL my_min(LL a, LL b){ return a < b ? a : b ; }
inline LL qr(){
    register LL k = 0 ; char c = getchar() ;
    while (c < '0' || c > '9') c = getchar() ;
    while (c <= '9' && c >= '0') k = (k << 1) + (k << 3) + c - 48, c = getchar() ;
    return k ;
}
inline bool Test(LL p, LL x){
    register LL r = 0, d = x - 1 ;
    while (!(d & 1)) d >>= 1, ++ r ;
    for (register LL i = expow(p, d, x), j ; r ; -- r){
        j = gsm(i, i, x) ;
        if (j == 1){
            if (i == 1 || i == x - 1) 
                return 1 ; 
            return 0 ;
        }
        i = j ;
    }
    return 0 ;
}
#define ctz __builtin_ctzll

inline LL gcd(LL a, LL b){
    if(!a) return b;
    if(!b) return a;
    register int t = ctz(a|b) ;
    a >>= ctz(a) ;
    do{
        b >>= ctz(b) ;
        if(a>b){LL t=b;b=a,a=t;}
        b-=a;
    }while(b);
    return a<<t;
}
inline bool Miller_Rabin(LL x){
    if (x == Prime[1] || x == Prime[0]) return 1 ;
    if (!(x % Prime[1]) || !(x % Prime[0])) return 0 ;
    if (Test(Prime[1], x) ^ 1) return 0 ;
    if (Test(Prime[0], x) ^ 1) return 0 ;
	if (x == Prime[2] || x == Prime[3]) return 1 ;
    if (!(x % Prime[2]) || !(x % Prime[3])) return 0 ;
    if (Test(Prime[2], x) ^ 1) return 0 ;
    if (Test(Prime[3], x) ^ 1) return 0 ;
	if (x == Prime[4] || x == Prime[5]) return 1 ;
    if (!(x % Prime[4]) || !(x % Prime[5])) return 0 ;
    if (Test(Prime[4], x) ^ 1) return 0 ;
    if (Test(Prime[5], x) ^ 1) return 0 ;
	if (x == Prime[6] || x == Prime[7]) return 1 ;
    if (!(x % Prime[6]) || !(x % Prime[7])) return 0 ;
    if (Test(Prime[6], x) ^ 1) return 0 ;
    if (Test(Prime[7], x) ^ 1) return 0 ;
    return 1 ;
}
inline LL Irand(LL x){
    return 1ll * ((rand() << 15 ^ rand()) << 30 ^ (rand() << 15 ^ rand())) % x ; //2
}//2

inline LL qwq(LL x){
    register LL C = Irand(x) ;
    register LL t1 = Irand(x), t2 = guisuMul(t1, t1, x) + C ; // 1
    register LL dif = t1 > t2 ? (t1 - t2) : (t2 - t1), G = gcd(x, dif) ;
    while (G == 1){
        t1 = guisuMul(t1, t1, x) + C ;if (t1 >= x) t1 %= x ;
        t2 = guisuMul(t2, t2, x) + C, t2 = guisuMul(t2, t2, x) + C ;
        if (t2 >= x) t2 %= x ; dif = t1 > t2 ? (t1 - t2) : (t2 - t1), G = gcd(x, dif) ;
    }
    return G ;
}
inline void Pollard_Rho(LL x){
    if (x == 1) return ;
    if (Miller_Rabin(x)){
        Ans = max(Ans, x) ; return ;
    } 
    register LL y = x ; 
    while (y == x) y = qwq(x) ;
    Pollard_Rho(y), Pollard_Rho(x / y) ;
}
int main(){
    srand(19260817) ;
    freopen("sttd.out", "w", stdout) ;
    T =qr() ;
    while (T --){
        N = qr(), Ans = -1, Pollard_Rho(N) ;
        if (Ans == N) puts("Prime") ;else printf("%lld", Ans), putchar('\n') ;
    }
} 
```

























---

## 作者：TheLostWeak (赞：22)

### 前置知识：$MillerRabin$素数测试

#### 前言

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/MillerRabin.html)

$MillerRabin$素数测试是一种很实用的素数判定方法。

它只针对单个数字进行判定，因而可以对较大的乃至于$long\ long$范围内的数进行判定，而且速度也很快，是个十分优秀的算法。

#### 前置定理

- **费马小定理**：$a^{p-1}\equiv1(mod\ p)$（详见此博客：[费马小定理](https://www.cnblogs.com/chenxiaoran666/p/Fermat_little.html)）
- **二次探测定理**：若$p$为奇素数且$x^2\equiv1(mod\ p)$，则$x\equiv1(mod\ p)$或$x\equiv p-1(mod\ p)$。

#### 大致思路

假设我们要验证$x$是否为素数，则我们应先找一个质数$p$来对其进行测试（$p$可以选取多个依次进行测试，只要有一个不满足就可以确定其不是质数）。

首先，我们先判断如果$x=p$，则$x$必为质数（因为$p$为质数）。如果$x$是$p$的倍数，则$x$必为合数。

然后，由于费马小定理，我们先测试$p^{x-1}\%x$是否等于$1$，如果不是，则它必然不是质数（这一步也叫作**费马测试**）。

否则，我们根据二次探测定理，先用一个$k$记录下$x-1$，然后只要$k$为偶数就持续操作：

- 先将$k$除以$2$，然后用一个$t$记录下$p^k\%x$的值。
- 如果$t$不等于$1$且不等于$p-1$，则根据二次探测定理，$x$非质数。
- 如果$t=p-1$，则无法继续套用二次探测定理，因此直接返回$true$。

如果一直操作到$k$为奇数仍然无法确定$x$非质数，就返回$true$。

这一过程应该还是比较容易理解的。

#### 代码

```cpp
class MillerRabin\\MR测试
{
    private:
        #define Pcnt 10
        Con int P[Pcnt]={2,3,5,7,11,13,19,61,2333,24251};//用于测试的质数
        I int Qpow(RI x,RI y,CI X) {RI t=1;W(y) y&1&&(t=1LL*t*x%X),x=1LL*x*x%X,y>>=1;return t;}//快速幂
        I bool Check(CI x,CI p)//测试
        {
            if(!(x%P[i])||Qpow(p%x,x-1,x)^1) return false;//判断x是否为p的倍数，然后费马测试
            RI k=x-1,t;W(!(k&1))//持续操作直至k为奇数
            {
                if((t=Qpow(p%x,k>>=1,x))^1&&t^(x-1)) return false;//如果p^k不是1也不是-1，说明x不是质数
                if(!(t^(x-1))) return true;//如果p^k已为-1，无法用二次探测定理，因此返回true
            }return true;
        }
    public:
        I bool IsPrime(CI x)//判断一个数是否为质数
        {
            if(x<2) return false;
            for(RI i=0;i^Pcnt;++i) {if(!(x^P[i])) return true;if(!Check(x,P[i])) return false;}//枚举质数进行测试
            return true;
        }
}MR;
```

### 正式内容：$Pollard\ Rho$算法

#### 前言

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/PollardRho.html)

$Pollard\ Rho$是一个著名的**大数质因数分解**算法，它的实现基于一个神奇的算法：$MillerRabin$素数测试。

期望下，$Pollard\ Rho$算法可以达到极快的复杂度。

#### 核心思想

在$ZJOI2019Day1$讲课期间，它是被$CQZ$神仙作为**随机算法**内的一部分来进行介绍的。

由此可见，其核心思想便是**随机**二字。

#### 操作流程

首先，我们先用$MillerRabin$判断当前数$x$是否为质数，若是，则可直接统计信息并退出函数

否则，我们考虑，如果能找到一个数$s$使得$1<gcd(s,x)<x$，则$x$必然可以被分成$gcd(s,x)$和$\frac x{gcd(s,x)}$两部分，接下来递归处理这两部分即可。

那么我们要找的，就是一个符合条件的$s$。

而找的过程利用了随机。

我们随机出一个$1\sim x-1$范围内的数$v_0$，然后，不断计算$v_i=(v_{i-1}*v_{i-1}+t)\%x$（$t$为一个自己设定的常数）。

则我们每次判断$d=gcd(abs(v_i-v_0),x)$是否大于$1$且不等于$x$本身，若满足则可直接返回$d$。

由于$v_i$最终肯定会形成环，而在形成环的时候，我们就无法继续操作了，因此当$v_i=v_0$，我们就可以退出函数并返回$x$本身，表示分解失败。

对于分解失败的情况，我们可以调整$t$并重新进行分解。

根据**生日悖论**，形成的期望环长为$O(\sqrt x)$，因此复杂度得以保证。

但是，光这样依然不够，我们还需要加优化。

#### 优化：路径倍长

考虑到如果对于每个$v_i$都要计算一遍$gcd$，显然很慢。

于是，就会想到每隔一段时间将这些数一起进行一次$gcd$。

而隔的时间如何确定呢？

我们可以倍增。

用一个变量$s$统计$abs(v_i-v_0)$之积并向$n$取模，因为取模不会改变$gcd$。

如果某一时刻$s$变成了$0$，则分解失败，退出函数并返回$x$本身。

然后每隔$2^k$个数，我们计算$gcd(s,x)$是否大于$1$且小于$x$，然后重新把$v_0$设置为当前的$v_i$。

这样一来，复杂度就得到了大大优化。

#### 代码

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define RL Reg LL
#define Con const
#define CI Con int&
#define CL Con LL&
#define I inline
#define W while
#define LL long long
#define Gmax(x,y) (x<(y)&&(x=(y)))
#define abs(x) ((x)<0?-(x):(x))
#define hl_AK_NOI true
using namespace std;
I LL Qmul(CL x,CL y,CL X)//快速乘
{
    RL k=(LL)((1.0L*x*y)/(1.0L*X)),t=x*y-k*X;
    t-=X;W(t<0) t+=X;return t;
}
class MillerRabin//MillerRabin判素数板子
{
    private:
        #define Pcnt 12
        Con int P[Pcnt]={2,3,5,7,11,13,17,19,61,2333,4567,24251};
        I LL Qpow(RL x,RL y,CL X)
        {
            RL t=1;W(y) y&1&&(t=Qmul(t,x,X)),x=Qmul(x,x,X),y>>=1;
            return t;
        }
        I bool Check(CL x,CI p)
        {
            if(!(x%p)||Qpow(p%x,x-1,x)^1) return false;
            RL k=x-1,t;W(!(k&1))
            {
                if((t=Qpow(p%x,k>>=1,x))^1&&t^(x-1)) return false;
                if(!(t^(x-1))) return true;
            }return true;
        }
    public:
        bool IsPrime(CL x)
        {
            if(x<2) return false;
            for(RI i=0;i^Pcnt;++i) {if(!(x^P[i])) return true;if(!Check(x,P[i])) return false;}
            return true;
        }
};
class PollardRho//PollardRho分解质因数
{
    private:
        #define Rand(x) (1LL*rand()*rand()*rand()*rand()%(x)+1)
        LL ans;MillerRabin MR;
        I LL gcd(CL x,CL y) {return y?gcd(y,x%y):x;}//求gcd
        I LL Work(CL x,CI y)//分解
        {
            RI t=0,k=1;RL v0=Rand(x-1),v=v0,d,s=1;W(hl_AK_NOI)//初始化随机一个v0
            {
                if(v=(Qmul(v,v,x)+y)%x,s=Qmul(s,abs(v-v0),x),!(v^v0)||!s) return x;//计算当前v，统计乘积，判断是否分解失败
                if(++t==k) {if((d=gcd(s,x))^1) return d;v0=v,k<<=1;}//倍增
            }
        }
        I void Resolve(RL x,RI t)//分解
        {
            if(!(x^1)||x<=ans) return;if(MR.IsPrime(x)) return (void)Gmax(ans,x);//先进行特判
            RL y=x;W((y=Work(x,t--))==x);W(!(x%y)) x/=y;Resolve(x,t),Resolve(y,t);//找到一个因数y，然后分解（注意除尽）
        }
    public:
        I PollardRho() {srand(20050521);}//初始化随机种子
        I LL GetMax(CL x) {return ans=0,Resolve(x,302627441),ans;}//求答案
}P;
int main()
{
    RI Ttot;RL n,res;scanf("%d",&Ttot);
    W(Ttot--) scanf("%lld",&n),(res=P.GetMax(n))^n?printf("%lld\n",res):puts("Prime");//输出
    return 0;
}
```

---

## 作者：Prean (赞：21)

# Pollard-Rho算法求最大质因数
Rollard-Rho算法的核心就是，使用判断质数很快的Miller-Rabin算法判断质数，假如是质数就返回，反之猜一个因数。

首先给出Miller-Rabin的板子：
```cpp
#define li inline
#define ll long long
#define re register
namespace Miller_Rabin
{
	const int Pcnt=12;
	const ll p[Pcnt]={2,3,5,7,11,13,17,19,61,2333,4567,24251};
	li ll pow(re ll a,re ll b,re ll p)
	{
		re ll ans=1;
		for(;b;a=a*a%p,b>>=1)if(b&1)ans=ans*a%p;
		return ans;
	}
	li bool check(re ll x,re ll p)
	{
		if(x%p==0||pow(p%x,x-1,x)^1)return true;
		re ll t,k=x-1;
		while((k^1)&1)
		{
			t=pow(p%x,k>>=1,x);
			if(t^1&&t^x-1)return true;
			if(!(t^x-1))return false;
		}return false;
	}
	inline bool MR(re ll x)
	{
		if(x<2)return false;
		for(re int i=0;i^Pcnt;++i)
		{
			if(!(x^p[i]))return true;
			if(check(x,p[i]))return false;
		}return true;
	}
}
```
p数组是我们选出来的质数，pow是快速幂，接下来具体说check在干嘛。

第一个：
```cpp
if(x%p==0||pow(p%x,x-1,x)^1)return true;
```
第一个就是判断倍数，没啥好说的。第二个就是费马小定理，因为假如x是质数的话结果一定是1，而不是1的话就一定不是质数。

那为什么后面还有呢？因为有一些玄学的情况下也会得到1。比如5和4。

后面每次计算的是：
```cpp
t=pow(p%x,k>>=1,x);
if(t^1&&t^x-1)return true;
if(!(t^x-1))return false;
```
这里要用到二次探测定理：

假如$ x^2 \equiv 1(mod $ $ p)$ ，那么要么$ x \equiv 1 (mod $ $  p) $，要么$ x \equiv p-1 (mod $ $ p) $，p为质数。

证明很简单，右边平方就行了。

假如t不为1并且t不为x-1，因为模数是x，所以肯定不是质数，返回true。

假如t是x-1，那么就是质数，没什么好说的。

然后看MR函数：
```cpp
inline bool MR(re ll x)
{
	if(x<2)return false;
	for(re int i=0;i^Pcnt;++i)
	{
		if(!(x^p[i]))return true;
		if(check(x,p[i]))return false;
	}return true;
}
```
都很好理解，就不多说了。
# 下面进入Pollard-Rho的部分
最前面说过，PR的核心思想就是猜一个数，看看是否是x的因数。

先放代码：
```cpp
namespace Pollard_Rho
{
	#define Rand(x) (1ll*rand()*rand()%(x)+1)
	li ll gcd(const ll a,const ll b){return b?gcd(b,a%b):a;}
	li ll mul(const re ll x,const re ll y,const re ll X)
	{
		ll k=(1.0L*x*y)/(1.0L*X)-1,t=x*y-k*X;
		while(t<0)t+=X;return t;
	}
	li ll PR(const re ll x,const re ll y)
	{
		re int t=0,k=1;re ll v0=Rand(x-1),v=v0,d,s=1;
		while(true)
		{
			v=(mul(v,v,x)+y)%x,s=mul(s,abs(v-v0),x);
			if(!(v^v0)||!s)return x;
			if(++t==k){if((d=gcd(s,x))^1)return d;v0=v,k<<=1;}
		}
	}
	li void Resolve(re ll x,re ll&ans)
	{
		if(!(x^1)||x<=ans)return;
		if(Miller_Rabin::MR(x)){if(ans<x)ans=x;return;}
		re ll y=x;while((y=PR(x,Rand(x)))==x);while(!(x%y))x/=y;
		Resolve(x,ans);Resolve(y,ans);
	}
	li ll check(ll x)
	{
		re ll ans=0;Resolve(x,ans);
		return ans;
	}
}
```
gcd是最大公约数，mul是龟速乘，都没什么好说的。

下面来看PR函数：
```cpp
li ll PR(const re ll x,const re ll y)
{
	re int t=0,k=1;re ll v0=Rand(x-1),v=v0,d,s=1;
	while(true)
	{
		v=(mul(v,v,x)+y)%x,s=mul(s,abs(v-v0),x);
		if(!(v^v0)||!s)return x;
		if(++t==k){if((d=gcd(s,x))^1)return d;v0=v,k<<=1;}
	}
}
```
v0是随机选的一个数，没错，随机选的。

然后v的算法是：

$ v_i=(v_{i-1}^2+t) $%$x $,知道$ v $和$ v0 $相同为止，t是随机的一个数。

然后循环内部就没什么好说的了，内部就是不断地猜。最后的if是个优化，使用倍增的优化。

来看看算法的另一个重点：Resolve函数：
```cpp
li void Resolve(re ll x,re ll&ans)
{
	if(!(x^1)||x<=ans)return;
	if(Miller_Rabin::MR(x)){if(ans<x)ans=x;return;}
	re ll y=x;while((y=PR(x,Rand(x)))==x);while(!(x%y))x/=y;
	Resolve(x,ans);Resolve(y,ans);
}
```
第一个if其实就是剪枝，当$ x=1 $时到达底层，结束递归；当$ x \leq ans $时不可能分解出来比ans还大的因数，也结束。

第二个Miller-Rabin就是看x是否是质数，如果是的话那么就是其中一种质因数，而且也不能分解因数了，return。

第三行：
```cpp
re ll y=x;while((y=PR(x,Rand(x)))==x);while(!(x%y))x/=y;
```
利用PR找因数，也没啥好说的。不过后面还有一个while，是可能x包含多个y，要全部都除去。

最后一步也很好理解，分别找各自的因数。

[评测记录](https://www.luogu.com.cn/record/32198860)

怎么就TLE了呢？

回头看了一眼数据范围，$ 1 \leq n \leq 10^{18} $，爆long long了。

所以只要把
```cpp
#define ll long long
```
改成
```cpp
#define ll __int128
```
就好了。不过输入的时候记得输入long long类型。

完整代码：
```cpp
#include<cstdlib>
#include<cstdio>
#include<ctime>
#define li inline
#define re register
#define ll __int128
#define abs(a) ((a)>0?(a):-(a))
namespace Miller_Rabin
{
	const int Pcnt=12;
	const ll p[Pcnt]={2,3,5,7,11,13,17,19,61,2333,4567,24251};
	li ll pow(re ll a,re ll b,re ll p)
	{
		re ll ans=1;
		for(;b;a=a*a%p,b>>=1)if(b&1)ans=ans*a%p;
		return ans;
	}
	li bool check(re ll x,re ll p)
	{
		if(x%p==0||pow(p%x,x-1,x)^1)return true;
		re ll t,k=x-1;
		while((k^1)&1)
		{
			t=pow(p%x,k>>=1,x);
			if(t^1&&t^x-1)return true;
			if(!(t^x-1))return false;
		}return false;
	}
	inline bool MR(re ll x)
	{
		if(x<2)return false;
		for(re int i=0;i^Pcnt;++i)
		{
			if(!(x^p[i]))return true;
			if(check(x,p[i]))return false;
		}return true;
	}
}
namespace Pollard_Rho
{
	#define Rand(x) (1ll*rand()*rand()%(x)+1)
	li ll gcd(const ll a,const ll b){return b?gcd(b,a%b):a;}
	li ll mul(const re ll x,const re ll y,const re ll X)
	{
		ll k=(1.0L*x*y)/(1.0L*X)-1,t=x*y-k*X;
		while(t<0)t+=X;return t;
	}
	li ll PR(const re ll x,const re ll y)
	{
		re int t=0,k=1;re ll v0=Rand(x-1),v=v0,d,s=1;
		while(true)
		{
			v=(mul(v,v,x)+y)%x,s=mul(s,abs(v-v0),x);
			if(!(v^v0)||!s)return x;
			if(++t==k){if((d=gcd(s,x))^1)return d;v0=v,k<<=1;}
		}
	}
	li void Resolve(re ll x,re ll&ans)
	{
		if(!(x^1)||x<=ans)return;
		if(Miller_Rabin::MR(x)){if(ans<x)ans=x;return;}
		re ll y=x;while((y=PR(x,Rand(x)))==x);while(!(x%y))x/=y;
		Resolve(x,ans);Resolve(y,ans);
	}
	li long long check(ll x)
	{
		re ll ans=0;Resolve(x,ans);
		return ans;
	}
}
signed main()
{
	srand(20060926);//据说用妹子的生日做种子会有神秘加成（大雾）
	re int t;scanf("%d",&t);long long re x,res;
	for(;t;--t)
	{
		scanf("%lld",&x);
		if((res=Pollard_Rho::check(x))^x)printf("%lld\n",res);
		else printf("Prime\n");
	}
}
```

---

## 作者：swiftc (赞：14)

这篇题解和 @cosmicAC 的思路一样，只是他给出的统计空格数的方式是错误的

经过我的~~上网查找~~尝试,有了下面的代码

~~十五行A黑题~~

__代码:__

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    system(R"(
	  read a
    for i in `seq 1 $a`; do
      read t
      s=`factor $t` 
      if [ `echo $s |tr -cd ' ' |wc -c` -eq 1 ]; then #使用这种判断空格的方式
        echo Prime
      else
        echo $s | sed "s/ /\n/g" | tail -n1
      fi
    done
    )");
    return 0;
}
```


---

## 作者：BBD186587 (赞：12)

在我的博客中 [阅读](https://www.cnblogs.com/zhs1/p/14075926.html) 

### 算法简介
Pollard-Rho 主要用于质因数分解，是一个随机化算法。
### 前置算法
[Miller-Rabin](https://www.cnblogs.com/zhs1/p/14043999.html)
### 伪随机函数
此算法用 $f_x=f_{x-1}^2+c \bmod n$ 生成随机数用于寻找质因数。

（其中，$f_1$ 和 $c$ 可以随机生成， $n$ 为正在分解的数）

但是，这个函数会产生环，所以叫伪随机函数。
### 判环
考虑用两个指针，一个每次走一步，另一个每次走两步。

如果两个指针的值在某一时刻相等，则找到了环。

因为两个指针位置的差每次增加1，所以不用担心找不到环。
### 算法主体
如果当前的数是质数，记录一下，直接返回。

判质数可用 Miller-Rabin 实现。

用上面的伪随机函数生成 $f$ 数组。

根据生日悖论，随机两个数 $x$ ， $y$ ，使得 $\gcd(|x-y|,n)>1$ 的概率比只随机一个数的概率要大。

所以，用判环使用的两个指针的值作为 $x$ ， $y$ ，

设 $d=\gcd(|x-y|,n)$ 。

若 $d>1$ 且 $d<n$，则递归处理 $d$ 和 $\frac{n}{d}$ 两个部分。

同时，如果找到了环，且还没有找到合法的因数，就重新随机 $f_1$ 和 $c$ 。
### 现在的代码
```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#define int long long
#define LD long double
#define ull unsigned long long
using namespace std;
int T,n,ans;
int MUL(int a,int b,int p) //a*b%p
{
	int x=(LD)a/p*b;
	return ((ull)a*b-(ull)x*p+p)%p;
}
int POW(int a,int b,int p) //a^b%p
{
	if(!b) return 1;
	if(b==1) return a;
	int sum=POW(a,b/2,p);
	if(b%2) return MUL(MUL(sum,sum,p),a,p);
	return MUL(sum,sum,p);
}
int MAX(int x,int y)
{
	return x>y?x:y;
}
int ABS(int x)
{
	return x>0?x:-x;
}
int gcd(int x,int y)
{
	if(!y) return x;
	return gcd(y,x%y);
}
int f(int x,int c,int p)
{
	return (MUL(x,x,p)+c)%p;
}
bool MR(int x)
{
	if(x==0||x==1) return false;
	if(x==2) return true;
	if(x%2==0) return false;
	int p=x-1,q=0;
	while(p%2==0) q++,p/=2;
	for(int i=1;i<=10;i++)
	{
		int a=rand()%(x-1)+1;
		if(POW(a,x-1,x)!=1) return false;
		int lst=1;
		for(int j=0;j<q;j++)
		{
			int t=POW(a,(1ll<<j)*p,x);
			if(t==1&&lst!=1&&lst!=x-1) return false;
			lst=t;
		}
		if(lst!=1&&lst!=x-1) return false;
	}
	return true;
}
int find(int x)
{
	if(x%2==0) return 2;
	if(MR(x)) return x;
	int t=rand()%(x+1);
	int a=t,b=t;
	int c=rand()%(x+1);
	while(1)
	{
		a=f(a,c,x),b=f(f(b,c,x),c,x);
		int d=gcd(ABS(a-b),x);
		if(d>1&&d<x) return d;
		if(a==b) return find(x);
	}
}
void PR(int x)
{
	if(x<=1) return;
	if(MR(x))
	{
		ans=MAX(ans,x);
		return;
	}
	int y=find(x);
	PR(y),PR(x/y);
}
signed main()
{
	srand(time(0));
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		if(MR(n)) puts("Prime");
		else
		{
			ans=0,PR(n);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```
### 黑科技 gcd
上面的代码因为效率过慢过不了洛谷上的 [模板题](https://www.luogu.com.cn/problem/P4718)。

观察到代码中会使用很多次 gcd 函数，所以考虑优化计算 gcd 的方法。

**新算法**

设现在要计算 $a$ 和 $b$ 两数的 gcd。

若 $a$ 和 $b$ 都是偶数，则递归计算 $2 \times gcd(\frac{a}{2},\frac{b}{2})$ 。

若 $a$ 是偶数，且 $b$ 是奇数，则递归计算 $gcd(\frac{a}{2},b)$ 。

若 $a$ 是奇数，$b$ 是偶数同理。

若 $a$ 和 $b$ 都是奇数，则递归计算 $gcd(|a-b|,a)$ 。

证明：

设原来 $a$ ， $b$ 的 gcd 为 $k$ 。

则 $a=kA$ ， $b=kB$ 。

$|a-b|=k|A-B|$ 。

因为 $A$ 与 $B$ 必然互质，

所以，现在要证明的就是 $A$ 与 $|A-B|$ 互质。

为了方便，先假设 $A>B$ ，去掉绝对值。相反的情况的证明也是类似的。

考虑反证法。

设 $A$ 与 $A-B$ 不互质，

则 $A=qx$ ， $A-B=qy$ 。

则 $B=A-(A-B)=qx-qy=q(x-y)$ ，所以 $A$ 与 $B$ 不互质，不成立。

所以前面的递归是成立的。


把原算法中的 gcd 部分换成这种写法，并加上一些比较常见的卡常技巧即可轻松通过本题。

贴一个用迭代实现的板子。
```cpp
//__builtin_ctzll(x) 函数用于求x在二进制中末尾0的个数
int gcd(int x,int y)
{
	if(!x) return y;
	if(!y) return x;
	int t=__builtin_ctzll(x|y);
	x>>=__builtin_ctzll(x);
	do
	{
		y>>=__builtin_ctzll(y);
		if(x>y) swap(x,y);
		y-=x;
	}while(y);
	return x<<t;
}
```

---

## 作者：xiezheyuan (赞：5)

# Miller-Rabin 与 Pollard-Rho 算法学习笔记

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/miller-rabin-pollard-rho.html)

## 前言

Miller-Rabin 算法用于判断一个数 $p$ 是否是质数，若选定 $w$ 个数进行判断，那么正确率约是 $1-\frac{1}{4^w}$ ，时间复杂度为 $O(\log p+w\log p)$。（我的实现）

Pollard-Rho 算法可以在期望 $O(n^{\frac{1}{4}})$ 的时间复杂度内找到合数 $n$ 的某一个非平凡的（即既不是 $1$，也不是它本身的）因子。

下文中用 $\mathbb{P}$ 来表示质数集合。

## Miller-Rabin 算法

### 前置知识

**费马小定理**：若 $p\in\mathbb{P},\gcd(a,p)=1$，则 $a^{p-1}\equiv1\pmod{p}$。

**二次探测定理**：若 $p\in\mathbb{P},x^2\equiv 1\pmod{p}$，则 $x\equiv\pm1\pmod{p}$。

注意：费马小定理的逆命题并不成立！

### 算法流程

首先，将 $p-1$ 表示成 $t2^k$ 的形式。那么，若 $p\in\mathbb{P}$，则 $p^{t2^k}=p^{p-1}\equiv1\pmod{p}$。

然后我们选择 $w$ 个数 $q_1,q_2,\cdots,q_w$ 进行判断。假如当前判断到了 $q_i$，那么用快速幂计算出 $a=q_{i}^{t}\bmod{p}$。然后让 $a$ 自乘 $k$ 次，就可以得到 $p-1$。

自乘的时候我们判断，如果 $a\equiv1\pmod{p}$ ，那么此时 $p$ 有一定概率是质数。于是我们看一看 $a$ 自乘前是否满足二次探测定理即可，如果是，则继续自乘，否则表明 $p$ 一定不是质数。

如果自乘得到的数同余 $p$ 不为 $1$，那么 $p$ 也不一定是质数。否则 $p$ 很可能是合数。

这时您可能会说：不是说过费马小定理逆定理不成立吗？其实，逆定理的反例（卡迈克尔数）是十分稀少的。经过多次判断，合数判成质数的概率十分小（质数不可能判成合数，想一想，为什么）

OI 中可以选择 $w=9$，$q$ 为前 $9$ 个质数。这样子 $10^{18}$ 范围内一般不会出错。

### 参考实现

```cpp
struct {/*Miller Rabin 质数判定算法*/
	vector<int> primes= {2,3,5,7,11,13,17,19,23};
	bool operator()(int p) {
		if (p==1)return 0;
		int t,k;
		for (t=p-1,k=0; !(t&1); k++,t>>=1);
		for (int i : primes) {
			if (p==i) return true;
			int a=fastpow(i,t,p),b=a;
			for (int j=1; j<=k; j++) {
				b=M(((__int128)a)*a,p);
				if (b==1&&a!=1&&a!=p-1) return false;
				a=b;
			}
			if (a!=1) return false;
		}
		return true;
	}
} MillerRabin;
```

[模板题](https://loj.ac/p/143)

## Pollard-Rho 算法

### 前置知识

**Floyd 判圈算法**：该算法可以线性判断一个链表上是否有环。其流程为使用两个指针。一个指针每次跑 $1$ 条边，另一个指针一次跑 $2$ 条边，然后相遇的点就在环上。

### 算法流程

先特判 $n=4$ 和 $n\in\mathbb{P}$。

Pollard-Rho 需要一个伪随机函数 $f(x,c,n)=x^2+c\bmod{n}$。其中 $x$ 表示上一个数，$c$ 是我们生成的，用于保证随机性的数，$n$ 是我们需要找因子的数。

可以发现这个函数最后会大概率生成一个混循环序列。如同希腊字母 $\rho(\texttt{Rho})$ 一般。

先选择一个随机数 $c$。两个指针从 $0$ 出发，我们看成存在一个链表，其中存在边 $(i,f(i,c,n))$。然后在上面跑 Floyd 判圈算法，在 Floyd 中，如果一个指针在 $t$，一个指针在 $k$。若 $\gcd(|t-k|,n)\neq1$。则我们认为 $\gcd(|t-k|,n)$ 是 $n$ 的一个因数。如果找到了环，则重新选择一个 $c$，重复上述流程。

此时时间复杂度期望 $O(n^{\frac{1}{4}}\log n)$。

### 算法优化

上述算法在洛谷板题上只能获得 $93$ 分（TLE 在了第 $13$ 个点）。优化迫在眉睫。

我们发现求 $\gcd$ 的 $O(\log n)$ 需要被优化。我们可以固定一个 $W$，跳 $W$ 次的时候统计 $|t-k|$ 的乘积 $p$。最后和 $n$ 取一次 $\gcd$。然后如果下一次 $p$ 会到 $0$，那么也要跳出。因为后面都是 $0$。

这样子只要 $W\gt \log n$ 就可以做到期望 $O(n^{\frac{1}{4}})$。我试了一下，貌似 $W=256$ 表现不错。

另外还可以加一个记忆化，在后面的例题中有用。

### 参考实现

```cpp
mt19937 engine(time(0));

inline int pr_rand(int x,int c,int n) { /*Pollard Rho 算法使用的伪随机数*/
	return M(M(((__int128)x)*x,n)-c,n);
}

unordered_map<int,int> prm;

int pollard_rho(int n) { /*Pollard Rho 算法求一个数的某一个质因子*/
	if (prm[n])return prm[n];
	if (n==4) return 2;
	if (MillerRabin(n)) return n;
	uniform_int_distribution<int> randint(3,n-1);
	while (1) {
		int c=randint(engine);
		int t=0,r=0,p=1,q=0;
		do{
			for(int i=1;i<=256;i++){
				t=pr_rand(t,c,n);
				r=pr_rand(pr_rand(r,c,n),c,n);
				int delta=(t-r)>0?(t-r):(r-t);
				if(t==r||(q=M(__int128(p)*delta,n))==0){
					break;
				}
				p=q;
			}
			int d=__gcd(p,n);
			if(d>1) return prm[n]=d;
		}while(t!=r);
	}
}
```

## [P4718 【模板】Pollard's rho算法](https://www.luogu.com.cn/problem/P4718)

 ### 简要题意

$T$ 组数据，每组数据给出一个数 $n$，如果 $n$ 是质数，输出 `Prime`，否则你需要输出 $n$ 的最大质因子。

$1 \leq T \leq 350,1 \lt n \leq 10^{18}$

### 思路

首先，我们先用一个 Miller-Rabin 算法来判断质数。我们可以用 Pollard-Rho 算法找出所有的因子（当然不用存起来，只需要用一个递归函数，最后 $\max$ 统计答案）即可。由于唯一分解定理，这个算法是正确的。

注意我们需要加一个记忆化来保证复杂度，否则复杂度爆炸。

### 代码

关键代码如下（要完整代码的私信）：

```cpp
unordered_map<int,int> mrm;

int max_factor(int n) { /*求一个数的最大质因子*/
	if (mrm[n]) return mrm[n];
	int factor=pollard_rho(n);
	if (factor==n) return mrm[n]=n;
	return mrm[n]=max(max_factor(factor),max_factor(n/factor));
}
```

[AC Record](https://www.luogu.com.cn/record/97717113)

## 参考资料

[Miller Rabin 算法详解 - 自为风月马前卒 - 博客园](https://www.cnblogs.com/zwfymqz/p/8150969.html)

[算法学习笔记(55): Pollard-Rho 算法 - 知乎 ](https://zhuanlan.zhihu.com/p/267884783)


---

## 作者：bulijoijiodibuliduo (赞：4)

## 前置芝士
### 1. 费马小定理
#### 内容
对于**任意质数** $p$ 和 $a$，其中 $p\nmid a$，满足：
$$
a^{p-1}\equiv 1\pmod p
$$

#### 证明
根据裴蜀定理，可以知道 $\{1\dots n\}$ 与 $\{a\dots(an)\}$ 是一一对应的，因此：
$$
\begin{aligned}
\prod_{i=1}^{p-1}ia&\equiv\prod_{i=1}^{p-1}i&\pmod p\\
a^{p-1}\prod_{i=1}^{p-1}i&\equiv\prod_{i=1}^{p-1}i&\pmod p\\
a^{p-1}&\equiv1&\pmod p
\end{aligned}
$$

#### 拓展
这个定理并**没有**逆定理，所以**不能**直接用于素性检验。但是值的注意的是，它能排除掉很大一部分合数。

### 2. 二次探测定理
#### 内容
对于**质数** $p$ 和 $a$，有以下性质：

如果满足：
$$
a^2\equiv1\pmod p
$$
则有：
$$
a\equiv\pm1\pmod p
$$

#### 证明
~~其实很简单，就让读者自行证明了。~~

根据 $a^2\equiv1\pmod p$，可以知道 $a^2-1=kp$。

然后根据平方差公式可得：$kp=(a+1)(a-1)$。

因为 $p$ 是**质数**，所以 $a+1$ 和 $a-1$ 中，**至少**有一个是 $p$ 的倍数。

也就是 $a\equiv\pm1\pmod p$。

### 3. Miller Rabin 素性检验
#### 算法流程
其实就是把费马小定理和二次探测定理结合了一下。

对于一个**奇数** $n$，我们令 $n=2^km+1$，其中 $m$ 是**奇数**。

我们先**随机**一个数 $a$，计算出 $b=a^m$。

然后将 $b$ 平方 $k$ 次，每次平方的时候用二次探测定理判断一下。

然后经过 $k$ 次平方的 $b$ 变成了 $a^{p-1}$，这个时候就可以用费马小定理判断了。

#### 正确率
假设你随机了 $s$ 次，那么判断错误的概率就是 $\frac{1}{4^s}$。

所以多随几次就可以了。

#### 拓展
对于 OI 来说，我们可以考虑不随机，而是使用固定的数来素性检验。

判断 `int` 范围内的质数只要前 $4$ 个质数。

判断 $10^{18}$ 范围内的质数只要前 $11$ 个质数。

判断 `long long` 范围内的质数只要前 $12$ 个质数。

具体可以参考 [A014233](https://oeis.org/A014233)。

接下来给出本题范围内（即 $n\le10^{18}$）的 Miller Rabin 代码：

```cpp
using ll = long long;
ll mul(ll a, ll b, ll mod){
  ll r = a * b - mod * (ll)(1.L / mod * a * b);
  return r - mod * (r >= mod) + mod * (r < 0);
}
ll qpow(ll a, ll b, ll mod) {
  ll res(1);
  for (; b; b >>= 1, a = mul(a, a, mod))
    if (b & 1) res = mul(res, a, mod);
  return res;
}
bool is_prime(ll n) {
  if (n <= 1) return false;
  vector<ll> base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  ll m = (n - 1) >> __builtin_ctz(n - 1);
  for (ll p : base) {
    ll t = m, a = qpow(p, m, n);
    if (n % p == 0) return n == p;
    while (t != n - 1 && a != 1 && a != n - 1)
      a = mul(a, a, n), t *= 2;
    if (a != n - 1 && t % 2 == 0) return false;
  }
  return true;
}
```

值的一提的是，上述代码中的乘法没有使用 `int128`，而是使用了 `long double`，这样会极大得提升运算效率。

而且 `is_prime` 函数并没有完全按照之前算法流程来写，而是稍加改动，但是本质上是相同的。

### 4. 生日悖论
#### 内容
在 $n$ 个数中，每次随机选取 $1$ 个数，期望 $O(\sqrt n)$ 次出现重复的数。

#### 证明
~~不太会~~，大概用斯特林公式估算一下。

## Pollard Rho
### 寻找一个数的真因子
首先考虑对于一个**合数** $n$ 找到它的一个因子 $d$，满足 $d\mid n,1<d<n$。

#### 大致思路
对于 $n$ 的一个**奇**质因子 $p$，我们把 $0$ 到 $p-1$ 中每个数 $x$ 向 $(x^2+c)\bmod p$ 连边（$c$ 是常数），这样构成了一个基环森林。

我们考虑两个指针 $x$ 和 $y$ ，一开始指向同一个随机节点，然后每次 $x$ 走 $1$ 步，$y$ 走 $2$ 步。

我们可以把 $(x^2+c)\bmod p$ 看作是随机的，所以根据生日悖论，你从一个点开始，期望 $O(\sqrt p)$ 步走到重复的点，所以根据追及问题期望经过 $O(\sqrt p)$ 步 $x$ 和 $y$ 会重合。

我们将 $x$ 和 $y$ 放在 $\pmod n$ 的意义下，那么就是经过期望 $O(\sqrt p)$ 步，$p\mid\gcd(n,x-y)$，此时的 $\gcd$ 还不能作为最终结果，因为还要考虑 $\gcd=n$ 的情况，但是这种情况的发生概率不大，所以直接重新选择起始点以及 $c$ 即可。

这样时间复杂度就是 $O(\sqrt{\min\{p}\})$ 的，然而 $n$ 的最小质因子 $p\le \sqrt n$，所以时间复杂度也可以看作是 $O(n^{\frac14})$ 的。

#### 一些优化
我们可以设置一个块长 $M$，把每 $M$ 步的 $x-y$ 累乘起来，一起取 $\gcd$ 判断，要注意的是，如果累乘起来的变量会变为 $0$，就不要乘上去，$M$ 一般取 $256$ 或者 $128$，但是好像没有一定要取 $2$ 的幂次这种说法。

当遇到了 $x=y$ 的情况，说明走完了模 $n$ 意义下的一大圈，其他位置都是 $\gcd(x-y,n)=1$，而只有这个位置上 $\gcd=n$，所以我们再随另一个起始点以及 $c$ 即可。

### 分解
直接递归，找因子前先判断一下是否是质数即可。

## 代码示例
```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937 rnd(random_device{}());

ll mul(ll a, ll b, ll mod){
  ll r = a * b - mod * (ll)(1.L / mod * a * b);
  return r - mod * (r >= mod) + mod * (r < 0);
}
ll add(ll a, ll b, ll mod) {
  a += b;
  return a >= mod ? a - mod : a;
}
ll sub(ll a, ll b, ll mod) {
  a -= b;
  return a < 0 ? a + mod : a;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll qpow(ll a, ll b, ll mod) {
  ll res(1);
  for (; b; b >>= 1, a = mul(a, a, mod))
    if (b & 1) res = mul(res, a, mod);
  return res;
}
bool is_prime(ll n) {
  if (n <= 1) return false;
  vector<ll> base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  ll m = (n - 1) >> __builtin_ctz(n - 1);
  for (ll p : base) {
    ll t = m, a = qpow(p, m, n);
    if (n % p == 0) return n == p;
    while (t != n - 1 && a != 1 && a != n - 1)
      a = mul(a, a, n), t *= 2;
    if (a != n - 1 && t % 2 == 0) return false;
  }
  return true;
}
ll get_factor(ll n) {
  uniform_int_distribution<ll> rng(0, n - 1);
  ll x = 0, y = 0, p = 1, q, g, c = 0;
  auto f = [&](ll x) { return add(mul(x, x, n), c, n); };
  for (ll i = 0; (i % 256) || (g = gcd(p, n)) == 1; i++, x = f(x), y = f(f(y))) {
    if (x == y) c = rng(rnd), x = rng(rnd), y = f(x);
    q = mul(p, sub(x, y, n), n);
    if (q) p = q;
  }
  return g;
}

vector<ll> solve(ll n) {
  if (n == 1) return {};
  if (is_prime(n)) return {n};
  ll d = get_factor(n);
  auto v1 = solve(d), v2 = solve(n / d);
  vector<ll> v3(v1.size() + v2.size());
  merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
  return v3;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t; cin >> t;
  while (t--) {
    ll x; cin >> x;
    auto res = solve(x);
    if (res.size() <= 1) cout << "Prime\n";
    else cout << res.back() << '\n';
  }
}
```
## 后记

洛谷的数据非常水，建议到 [板子 OJ](https://judge.yosupo.jp/problem/factorize) 上提交。

upd：修了一车锅。

---

## 作者：_HL_ (赞：4)

## 序

对于 Pollard Rho 算法流程和卡常技巧其他题解已经讲得很详细了，但其中笔者在学习时遇到以下问题：

1. 复杂度正确性？

2. 为何要用那个 Pollard 伪随机数列而非 mt19937 直接随一个？

3. 怎么想到的这个算法？

这些现有题解并未较完整的解答，本文将更完整的介绍。

通过对这些问题的理解，可以加深读者对于 Pollard Rho 算法正确性的信任，同时可以在背板子的时候明白每步在干什么，避免背了就忘的问题。

## 问题引入

$\circ$ 一个数 $n$ , 将他分解质因数。

对于分解质因数，相信大家都会 $O(\sqrt n)$ 的暴力试除法，但质因数个数 $\omega(n)$ 是比 $\log(n)$ 还小的，看起来十分浪费，但直接分解的算法似乎并不显然。

于是我们退而求其次，先考虑解决下面这个问题：

$\circ$ 对于一个合数 $n$ , 找到他的一个非平凡因子。

其中非平凡因子是 $n$ 的因子中，除了 $1$ 和 $n$ 的一个因数。这里因数不一定是质因数。

我们考虑用随机的做法，直接随看是不是 $n$ 的因数当 $n$ 只有两个因数时死的透透的。

生日悖论是随机做法中较常利用的一个结论，生日悖论可简单描述为：$m$ 个数中随机选 $k$ 次，当 $k\ge\sqrt m$ 时，选的 $k$ 个数两两不同的概率可忽略。

我们考虑用生日悖论去撞他。

记 $n$ 的最小因子为 $p$ ，有 $p\le \sqrt n$

考虑我们随了一个可重集 $X=\{x_i\}$ ，$x_i$ 的值域为 $[0,n-1]$ (当然，整数)，我们记 $y_i=(x_i\mod p)$，于是我们得到了另一个可重集 $Y=\{y_i\}$ 值域是 $[0,p-1]$ 。

由生日悖论我们知道，当 $|Y|>\sqrt p$ 时，$Y$ 中基本上一定有至少一个数对 $(y_i,y_j)$ 相等，设这样有至少一个数对相等的概率为 $P_1$ , 生日悖论告诉我们 $P_1=1-\epsilon$  ， 即非常接近 $1$ 。

所以 $X$ 中有同样 $P_1$ 的概率有至少一个数对 $(x_i,x_j)$ ，满足 $x_i\equiv x_j\pmod p$。

考虑 $x_i=x_j$ 的情况，出现这种情况的概率 $P_2$ 是极小的 , 而剩下的 $x_i\ne x_j$ 的情况，有 $p|(|x_i-x_j|)$。

“$P_2$ 极小” 这个结论易于理解，即 $n$ 个里选 $k$ 个 ，$k\le \sqrt p\le n^{\frac{1}{4}}$ ，能选出两个相同的数概率很小。具体证明大概挺数数的，读者有兴趣可以自己推一推，不是本文重点。

这说明什么？这说明我们只需要找 $k(k\le \sqrt p\le n^{\frac{1}{4}})$ 个数 ，里面包含的信息就有 $P_1-P_2$ 的概率包含 $p$ 的一个倍数！

此时之前那对 $(x_i,x_j)$ 满足 $\gcd(|x_i-x_j|,n)$ 一定为 $n$ 的一个因数，且为 $p$ 的一个倍数。

$|x_i-x_j|=p\times p=n$ 的情况不会出现 ，因为 $\gcd(|x_i-x_j|,n)\le |x_i-x_j|\leq n-1$ 。

因为 $p|\gcd(|x_i-x_j|,n)$ 且 $p>1$ ,所以 $\gcd(|x_i-x_j|,n)\ne 1$

所以 $\gcd(|x_i-x_j|,n)$ 一定是 $n$ 的一个非平凡因子。


由此，我们将问题转化为下面这个形式 ：

$\circ$ 维护一个数集 $S$ ，每次随机一个数 $a$ ，判断 $S$ 中是否有一个数 $b$ 使得 $\gcd(|a-b|,n)\ne 1$ , 有则直接是答案，否则将 $a$ 加入 $S$ 。

由之前的证明，可以知道加入次数 $\le n^{\frac{1}{4}}$

暴力枚举进行判断是 $O((n^{\frac{1}{4}})^2)=O(\sqrt n)$ 的，跟试除一个复杂度。

这个东西似乎也不好数据结构优化，这就是不能直接用 mt19937 随一个数列的原因。

## Pollard 的伪随机数列

直接维护不好做，我们考虑在随机的数列上做文章。

我们需要使随机的数列有一些性质 ，使得只需要通过枚举少数几个 $S$ 中的数即可判断是否存在 $b$ 使得 $\gcd(|a-b|,n)\ne 1$ 

Pollard 给出了这样一个数列 :

$x_i=(x_{i-1}^2+c) \mod n$ 

我们考虑这个数列有什么好处呢？

$\circ$ 可以使算法复杂度正确

对于 $\gcd(|x_i-x_j|,n)\ne 1$ ，记一个 $n$ 的因数 $q|(|x_i-x_j|)$ ，我们考虑 $x_{i+1}$ 和 $x_{j+1}$ ，满足 $|x_{i+1}-x_{j+1}|\equiv|x_i^2+c-(x_j^2+c)|\equiv|(x_i-x_j)\times (x_i+x_j)|\pmod n$

而因为 $|x_{i+1}-x_{j+1}|\in [0,n-1]$ , 所以 $|x_{i+1}-x_{j+1}|=(|(x_i-x_j)\times (x_i+x_j)|\mod n)$

发现仍满足 $q|(|x_{i+1}-x_{j+1}|)$ 但有概率 $x_i+x_j=n$ 而使其变为 $0$ 或者其他情况使得 $n|(|(x_i-x_j)\times(x_i+x_j)|)$ ，这样得到的 $\gcd$ 不再是非平凡因子了，造成非平凡因子的损失。这样情况概率大约 $\dfrac{1}{n}$ 量级，影响并不大，我们一会再讨论。

我们先讨论比较好的情况 ，即所有 $(i,j)$ , 若 $\gcd(|x_i-x_j|,n)\ne 1$ 则 $\gcd(|x_{i+t}-x_{j+t}|,n)\ne 1$ 。

对于相同距离的点对 ，我们只需要每个距离只判断一次即可。

这样我们就可以有很多办法处理了，比如先加入 $k$ 个，记为 $x_1$ 到 $x_k$ , 然后考虑第 $k+1$ 个位置，我们对所有 $i\in[1,k]$ 查是否有 $\gcd(|x_i-x_{k+1}|,n)\ne 1$ 。 

但由于要考虑到之前说的非平凡因子损失的情况，各种判法有实际表现上的差异。一个常用的是倍增判法：

判断每个 $x_i$ 和 $i$ 以下最大的 $2$ 的整数次幂 $j$ 是否 $\gcd(|x_i-x_{j}|,n)\ne 1$ 。


$\circ$ 这个数列足够随机

这是一个伪随机数列，他足够随机。这个比较玄学，别的题解有所涉及，在本文中只作为结论进行介绍。

但他毕竟是一个伪随机数列，当有数列的两项相等的时候，由于生成下一项的方式一样，这个数列就会出现循环，出现一个 $\rho$ 的形状。

有可能非常不幸随到的 $\rho$ 非常小 ，这时需要进行判环。

我们直接在那个倍增做法上进行改进。

考虑累计 $\prod\limits_{j<i\le2j} |x_i-x_j|\mod n$ ，其中 $j$ 依然是小于 $i$ 的最大 $2$ 的整数次幂，这样对于一轮倍增结束后，判断累积的值是否为 $0$ , 即可知道路径上是否有两值相等，即出现环。有可能因为非平凡因子损失而误判环, 可由于非平凡因子损失概率极低所以实际表现仍是极好的。

还有一些常数优化这里不介绍了。

至此，我们以 $O(\sqrt p)$ 解决了 “对于一个合数 $n$ , 找到他的一个非平凡因子”这个问题，其中 $p$ 是 $n$ 的最小非平凡因子。

我们考虑解决第一个问题，即

$\circ$ 一个数 $n$ , 将他分解质因数。

我们用 Miller Rabin 判断一个数是否是质数，如果是就结束，否则考虑我们现在将 $n$ 分为了 $m$ 和 $\frac{n}{m}$ ， 直接递归两侧继续分解即可。


复杂度为什么对呢？

我们考虑分解的过程，每一次分解的复杂度是 $O(\sqrt p)$ , 最终分解为了 $n$ 的所有质因数，假设有 $k$ 个（由于这些质因子可以重复所以不是 $\omega(n)$ 个），设为 $p_1,p_2\dots p_k(p1\le p2\le\dots\le p_k)$，而分解的递归树是一棵二叉树，底层叶子是每个质因子，贡献复杂度的是每个非叶子节点，贡献为子树中最小的 $p$ 开根号，由于二叉树叶子数恒定，所以非叶节点共 $k-1$ 个，欲使最大化复杂度看最劣情况，即从小到大每个只贡献一次，所以复杂度是 $O(\sum\limits_{i=1}^{k-1}\sqrt p_i)$ 的，因为 $p_i\ge 2$ ，且有 $\prod\limits_{i=1}^{k} p_i=n$ ， 由不等式知识知两项且相等时取到最大值，即 $O(\sqrt p_1)=O(n^{\frac{1}{4}})$ 。

求 $\gcd$ 的 $\log$ 被那个 127 次相乘判断一次的抵消了，即最后复杂度期望是 $O(n^{\frac{1}{4}}\frac{\log n}{127})$ 。



```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define lll __int128

ll mod;
inline ll add(ll x,ll y)
{
	ll res=x+y;
	return res<mod?res:res-mod;
}
inline ll mul(ll x,ll y)
{
	return (lll)x*y%mod;
}
inline ll qpow(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1)res=mul(res,x);
		x=mul(x,x),y>>=1;
	}
	return res;
}
ll pri[]={2,3,5,7,11,13,17,19,23,29,31,37};
inline bool chk(ll x)
{
	ll v=qpow(x,mod-1);
	if(v!=1)return 0;
	ll d=mod-1;
	while(!(d&1))
	{
		d>>=1;
		v=qpow(x,d);
		if(v==mod-1)return 1;
		if(v!=1)return 0;
	}
	return 1;
}
inline bool MR(ll x)
{
	mod=x;
	for(auto p:pri)
	{
		if(x==p)return 1;
		if(!chk(p))return 0;
	}
	return 1;
}
mt19937 rnd(time(0));
inline ll f(ll x,ll c)
{
	return add(mul(x,x),c);
}
inline ll rho(ll n)
{
	mod=n;
	ll x=rnd()%mod,c=rnd()%(mod-1)+1;
	ll p=1;
	for(ll i=2,j=2,d=x;;i++)
	{
		x=f(x,c),p=mul(p,abs(x-d));
		if(i%127==0&&__gcd(p,n)!=1)return __gcd(p,n);
		if(i==j)
		{
			j<<=1,d=x;
			if(__gcd(p,n)!=1)return __gcd(p,n);
		}
	}
}
ll PR(ll n)
{
	//cout<<n<<"\n";
	if(MR(n))return n;
	ll p=n;
	while(p==n)p=rho(n);
	return max(PR(p),PR(n/p));
}

inline void SOLVE()
{
	ll n;
	cin>>n;
	ll ans=PR(n);
	if(ans==n)cout<<"Prime\n";
	else cout<<ans<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--)SOLVE();
	return 0;
}
```



---

## 作者：CmsMartin (赞：2)

upd 2023.4.15：更改一些笔误。

[更好的阅读体验](http://cmsblog.top/archives/pollard-rho)

## 问题引入

给定一个正整数  $a \in \mathbb{Z}^+$，请找到其一个因子。

## 朴素算法

要找到大整数的一个因子，最朴素的想法是试除法。也就是这样：

```cpp
int Find_Factor(int x) {
    for(int i = 2; i * i <= N; i++)
        if(n % i == 0)
        	return i;
    return n;
}
```

这样的时间复杂度是  $\Theta(\sqrt n)$ 的，不能够处理 $10^{18}$ 及以上的大数。

## 基于随机的算法

我们可以先用 Miller-Rabbin 算法检测质数，如果这个数不是质数，每次从 $[2，n - 1]$ 中随机一个数字进行判断，也就是这样：

```cpp
int RandInt(int l , int r) {
	static mt19937 Rand(time(0));
	uniform_int_distribution<int> dis(l, r);
	return dis(Rand);
}

int Find_Factor(int n) {
	if(Miller_Rabbin(n))
		return n;
	int x;
	do {
		x = RandInt(2 , n - 1);
	} while(n % x);
	return x;
}
```

上述算法最差时间复杂度为 $O(n)$。

这个糟糕的随机算法可以进行改进：

```cpp
int RandInt(int l , int r) {
	static mt19937 Rand(time(0));
	uniform_int_distribution<int> dis(l, r);
	return dis(Rand);
}

int Find_Factor(int n) {
	if(Miller_Rabbin(n))
		return n;
	int x , y;
	do {
		x = RandInt(2 , n - 1);
		y = __gcd(n , x);
	} while(y == 1);
	return y;
}
```

分析最差时间复杂度：当 $n$ 为 $p^2$（$p$ 为质数），显然当随机数 $x$ 取 $p , 2p , 3p , \cdots , (p-1)p$ 时都可以找到 $\gcd(x , n) = p > 1$，所以时间复杂度为 $O(\sqrt n \log n)$ 的，连暴力都打不过，但这是 Pollard-Rho 算法的基础。

## 生日悖论

这个悖论是 Pollard-Rho 算法的前置知识。

在一个房间中至少有多少人可以使得同一天出生的人出生的概率为 $50\%$？

假设一年有 $n$ 天，房间里共有 $k$ 个人，编号为 $1 \sim k$，假设生日随机分布。

设 $k$ 个人生日不相同为事件 $A$，则有：

$$\operatorname{Pr}\{A\} = \sum_{i=n-k+ 1}^n \frac{i}{n}$$

同一天出生的人出生的概率为 $\operatorname{Pr}\{\overline A\} = 1-\operatorname{Pr}\{A\}$，当 $\operatorname{Pr}\{ \overline A\} \ge \frac{1}{2}$ 时显然有 $\operatorname{Pr}\{A\} \le \frac{1}{2}$。

使用 Mathemaica 计算出来 $n = 365$ 时 $k = 23$。

实际上可以使用随机变量指示器进行近似分析：

设第 $i$ 个人和第 $j$ 个人同时在第 $w$ 天出生为事件 $B$，有

$$\operatorname{Pr}\{N\}=\frac{1}{n^2}$$

由于一年有 $n$ 天，所以有

$$ \operatorname{Pr}\{i,j \ born\  on\  the\  same\  day\} = \frac{1}{n}$$

设随机变量指示器 $X_{i,j}$，定义：

$$
X_{i,j} =\left\{ 
    \begin{array}{lc}
        1  &if\ i \ and \ j\ born\  on\  the\  same\  day\\
        0  &Otherwise
    \end{array}
\right.
$$

那么有：

$$
\mathbb{E}[X_{i,j}] = \operatorname{Pr}\{i,j \ born\  on\  the\  same\  day\} = \frac{1}{n}
$$

设 $X$ 为两个人在同一天出生的人的无序对数，即  $X = \sum\limits_{i=1}^k \sum\limits_{j = i + 1}^kX_{i,j}$ 则有：

$$
\mathbb{E}[X] = \mathbb{E}[\sum\limits_{i=1}^k \sum\limits_{j = i + 1}^kX_{i,j}]
$$

由数学期望的线性性质得：

$$
 \mathbb{E}[\sum\limits_{i=1}^k \sum\limits_{j = i + 1}^kX_{i,j}] = \sum\limits_{i=1}^k \sum\limits_{j = i + 1}^k \mathbb{E}[X_{i,j}] = \sum\limits_{i=1}^k \sum\limits_{j = i + 1}^k \frac{1}{n} = \frac{k(k-1)}{2} \times \frac{1}{n}
$$

解得当 $n = 365$ 时，房间中有 $28$ 人就可以期望有两人生日相同。

于是可以这样优化：

原来从 $[1,n]$ 中随机出我们想要的数字 $k$ 的概率为 $\frac{1}{n}$，现在我们随机两个数 $i-j$ 使得 $|i-j|=k$ 的概率大约为 $\frac{2}{n}$，概率扩大了两倍左右。

## 伪随机数序列

Pollard-Rho 使用一种特别的伪随机数生成器来生成 $[1,n-1]$ 间的伪随机数序列：设序列第一个数为 $x$，$f(x) := (x^2+c) \mod n$，其中 $c$ 为可以自行指定的常数，则 $x,f(x),f(f(x)),f(f(f(x)))$ 为一个伪随机数序列。

显然的，每个数都由前一个数字决定，以生成的数又是有限的，那么迟早会进入循环，而且大概率为混循环，所以生成的序列类似一个 $\rho$ 形，故名 $\rho$ 算法。

遇到环后我们接下来做的随机都没有意义了，所以需要更换 $c$ 重新开始。

## Floyd 判环算法

设置两个变量 $t,r$，每次判断是否有 $\gcd(|t-r|,n) > 1$，如果没有，就令 $t=f(t)$，$r=f(f(r))$。因为 $r$ 跑的更快，那么它们最后会相遇，这时候就换一个 $c$ 重新生成随机数。

这个伪随机数生成器有一个性质：如果 $|i-j| \equiv 0 (\operatorname{mod} \ p)$，那么有 $|f(i)-f(j)| = |i^2 - j^2| = |i - j| \times|i + j| \equiv 0 (\operatorname{mod} \ p)$

由此可得，只要环上距离为 $x$ 的两个数满足条件，那么所有距离为 $x$ 的数都满足条件。在 Floyd 判环的过程中，每次移动都相当于在检查一个新的距离 $x$ ，这样就不需要进行两两比较了。

这个算法的复杂度依赖于这个伪随机数生成器的随机程度，还没有被严格证明。如果它是足够随机的，那么期望复杂度显然是 $\Theta(n^{\frac{1}{4}}\log n)$。

```cpp
ll RandInt(ll l , ll r) {
	static mt19937 Rand(time(0));
	uniform_int_distribution<ll> dis(l, r);
	return dis(Rand);
}

ll Pollard_Rho(ll n) {
	if(n == 4) {
		return 2; 
	} 
	if(Miller_Rabin(n)) {
		return n;
	}
	while(true) {
		ll c = RandInt(1 , n - 1);
		auto f = [=](ll x) {
			return ((__int128)x * x + c) % n;
		};
		ll t = f(0) , r = f(f(0));
		while(t != r) {
			ll d = __gcd(abs(t - r) , n);
			if(d > 1)
				return d;
			t = f(t);
			r = f(f(r));
		}
	}
}
```

## 倍增优化

由于 $\gcd(a,b)$ 的运算会花费 $O(\log n)$ 的时间，从而使我们的时间复杂度挂上了 $\log$，这使人非常不爽，现在我们想办法去掉这个 $\log$。

我们使用 **乘法累计** 来减少求 $\gcd$ 的次数。如果 $\gcd(a,b) > 1$，那么有 $\gcd(ac,b)>1,c\in \mathbb{N}^*$，并且有 $\gcd(ac\ \operatorname{mod} \ b,b) = \gcd(a,b)$。

我们每过一段时间对这些差值进行 $\gcd$ 运算，设 $s = \prod|x_0-x_1| \ \operatorname{mod} \ n$，如果过程中存在 $s = 0$ 测表示分解失败， $n$ 是质数。每隔 $2^k-1$ 个数，计算是否满足  $1 < \gcd(s,n) < n$。此处 $k=7$，可以更具需要自行调节。

```cpp
typedef long long ll;
typedef __int128 lll;

ll RandInt(ll l , ll r) {
	static mt19937 Rand(time(0));
	uniform_int_distribution<ll> dis(l, r);
	return dis(Rand);
}

ll Pollard_Rho(ll n) {
	if(Miller_Rabin(n)) {
		return n;
	}
	ll s = 0 , t = 0;
	ll c = RandInt(1 , n - 1);
	int step = 0 , goal = 1;
	ll value = 1;
	auto f = [=](ll x) {
		return ((lll)x * x + c) % n;
	};
	for(goal = 1;; goal <<= 1, s = t , value = 1) {
		for(step = 1; step <= goal; step++) {
			t = f(t);
			value = ((lll)value * abs(t - s)) % n;
			if(step % 127 == 0) {
				ll d = __gcd(value , n);
				if(d > 1) return d;
			}
		}
		ll d = __gcd(value , n);
		if(d > 1) return d;
	}
}
```

## 【模板】Pollard-Rho算法

[题目传送门](https://www.luogu.com.cn/problem/P4718)

## 思路

对于一个数 $n$，如果用 Miller_Rabin 判断出来他是质数，就可以直接返回。

否则找到它的一个真因子 $p$，把 $n$ 除去所有的 $p$ 因子，再递归分解 $n$ 和 $p$，其中使用 Miller_Rabin 判断是否存在质因子，并打擂台取最大值。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;

ll RandInt(ll l , ll r) {
	static mt19937 Rand(time(0));
	uniform_int_distribution<ll> dis(l, r);
	return dis(Rand);
}

ll Quick_Power(ll a , ll b , ll p) {
	ll res = 1;
	while(b) {
		if(b & 1) res = (lll)res * a % p;
		a = (lll)a * a % p;
		b >>= 1;
	}
	return res;
}

bool Miller_Rabin(ll n) {
	if(n < 3 || n % 2 == 0) return n == 2;
	ll a = n - 1 , b = 0;
	while(a % 2 == 0) {
		a /= 2;
		b++;
	}
	for(int i = 1 , j; i <= 10; i++) {
		ll x = RandInt(2 , n - 1);
		ll v = Quick_Power(x , a , n);
		if(v == 1) continue;
		for(j = 0; j < b; j++) {
			if(v == n - 1) break;
			v = (lll) v * v % n;
		}
		if(j == b) return 0;
	}
	return 1; 
}

ll Pollard_Rho(ll n) {
	ll s = 0 , t = 0;
	ll c = RandInt(1 , n - 1);
	int step = 0 , goal = 1;
	ll value = 1;
	auto f = [=](ll x) {
		return ((lll)x * x + c) % n;
	};
	for(goal = 1;; goal <<= 1, s = t , value = 1) {
		for(step = 1; step <= goal; step++) {
			t = f(t);
			value = ((lll)value * abs(t - s)) % n;
			if(step % 127 == 0) {
				ll d = __gcd(value , n);
				if(d > 1) return d;
			}
		}
		ll d = __gcd(value , n);
		if(d > 1) return d;
	}
}

ll Ans;

void Fac(ll n) {
	if(n <= Ans || n < 2) return;
	if(Miller_Rabin(n)) {
		Ans = max(Ans , n);
		return;
	}
	ll p = n;
	while(p == n) p = Pollard_Rho(n);
	while((n % p) == 0) n /= p;
	Fac(n);
	Fac(p); 
}

ll T , N;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--) {
		Ans = 0;
		cin >> N;
		Fac(N);
		if(Ans == N) {
			cout << "Prime" << endl;
		}
		else {
			cout << Ans << endl;
		}
	}
	return 0;
} 
```

---

## 作者：carp_oier (赞：0)

## advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/Pollard_Rho.html)看一眼呢。

## prelogue

怎么感觉我这个人和随机化关系这么好。

鲤鱼我是从[这篇博客](https://zhuanlan.zhihu.com/p/267884783"这篇博客")中进行学习的。其中也有很多地方借鉴了大佬的博客，侵权删。

## Pollard-Rho 算法

Pollard-Rho 算法是一种求非 1 非自身的因子的高效算法。

## main body

我们求因子平常是用的复杂度为 $O(\sqrt n)$ 的试除法，如果 $n$ 这个数字很大，我们这个算法就很低效，需要一些卡常技巧来帮助我们卡过去这个题目，甚至是直接就过不去。

但是想从根本来解决问题，我们就得要换一种更加高效的算法 Pollard-Rho 算法。

这个算法是一种带有随机化思想的方法。有点类似于猴子排序（就是那个很 naive 很 trivial 的算法，~~你能说他效率低嘛，那只能说明你 rp 不好~~）

我们如果单纯的用这个随机数来进行匹配，效率极其低下，甚至可以说是 $O(+\infty)$ 的。那我们就要想着怎么对它进行优化。

在这之前，我们要先引入一个知识点**生日悖论**：

### 生日悖论

生日悖论是说在一个房间里面有 23 个人，则他们生日相同的概率就会大与 $\frac{1}{2}$，反映出来就是这个式子 $\prod _ {i=0} ^ {22} \frac{365 - i}{365} < \frac{1}{2}$

这就告诉我们，在一个区间里面不断的生成随机数。很快就会得到重复的数字。期望大约是在根号级别（手玩一下就不难发现，大概就是根号级别的）。

应用到原题上面来，我们随即的最坏情况为 $n = p^2$，期望在生成了 $\sqrt n = n ^ {\frac{1}{4}}$ 个数后，可以出现两个在模 $p$ 的情况下相同的数。那么记这两个数的差的绝对值为 $d$，就一定满足 $d \equiv 0 \pmod p$ 那么就同时满足$\gcd(d, n) > 1$。但是此时我们需要对这些数字一一验证，从整体上来说，时间复杂度并没有更优。

***

Pollard 对于这个问题提出了一个新的解决方案：一种特别的伪随机数生成器用来生成 $[0, N - 1]$ 之间的伪随机数列：设第一个数为 $x$，$f(x) = (x ^ 2 + c) \bmod N $，$c$ 是一个随机参数。

其中,$x$,$f(x)$,$f(f(x))\cdots$ 就是一个伪随机数列。

这样子我们通过相邻两项做差，就是我们之前求得的东西，证明如下：

$|a - b| \equiv 0 \pmod p \leftrightarrow |f(a) - f(b)| = |a ^ 2 - b ^ 2| = |a - b| \times |a + b| \equiv 0(\bmod p) $

记两个变量分别为 $t$，$r$。

我们对于这个上这个式子不断的去求，最后由于 $f(f(r))$ 的增长速度，显然是要快于 $f(t)$ 最终会与 $t$ 在环上相遇。这样子就形成了一个 $\rho$ 的形状。

这也就是 Pollard 为什么将这算法叫做 Pollard-Rho 算法。

这个时候如果数据足够随机，它的期望值是 $O(n ^ {\frac{1}{4}} \log n)$。

但是实际上，如果 $\gcd(d, n) > 1$，那么就一定有 $\gcd(kd \bmod n, n) > 1$ 所以我们可以减少求公约数的次数，将这些数字乘起来，然后再统一与 $n$ 求公因数。

最后反正就是一顿操作猛如虎，然后就给硬生生将一个 $O(+\infty)$ 的做法砍成了 $O(n ^ {\frac{1}{4}})$。

这里判读是否为素数我用的是 Miller_Rabin，不会的可以自行递归学习。（

## code time

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll
#define fom(i, a) for(rl i=a; i; -- i)
#define foa(i, a, b) for(rl i=a; i < b; ++ i)
#define fos(i, a, b) for(rl i=a; i <= b; ++ i)
#define fop(i, a, b) for(rl i=a; i >= b; -- i)

namespace IO
{
    int pp1=-1; const int pp2=(1<<21)-1; char buf[1<<21],*p1=buf,*p2=buf,buffer[1<<21];
    inline void flush() {fwrite(buffer,1,pp1+1,stdout); pp1=-1;}
    inline void pc(const char ch) {if(pp1==pp2) flush(); buffer[++pp1]=ch;}
    inline char gc(){ return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    template <class T> inline void read(T &res){char ch=gc();bool f=0;res=0; for(;!isdigit(ch);ch=gc()) f|=ch=='-'; for(;isdigit(ch);ch=gc()) res=(res<<1)+(res<<3)+(ch^48); res=f?~res+1:res;}
    template <class T> inline void ww(T x) { if(!x) pc('0'); else { static int stk[21]; int top = 0; if(x<0) pc('-'),x=~x+1; while(x) stk[top++]=x%10, x/=10; while(top--) pc(stk[top]^48);}}
}

#define ws IO::pc(' ')
#define wl IO::pc('\n')
#define ww(x) IO::ww(x)
#define read(x) IO::read(x)
#define flush() IO::flush()

ll max_factor, n;

// mt19937 rand(time(0));

inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; } // 求最大公因数

inline ll qmi(ll a, ll k, ll p) { ll res = 1; while(k) { if(k & 1) res = ((__int128)res * a) % p; a = ((__int128)a * a) % p, k >>= 1; } return res; } // 被压缩的快速幂

inline bool Miller_Rabin(ll p) // 判断是否为素数
{
    if(p < 2) return false;
    if(p == 2 || p == 3) return true;
    ll d = p - 1, r = 0;

    while(!(d & 1)) ++ r, d >>= 1;
    
    foa(k, 0, 10) 
    {
        ll a = rand() % (p - 2) + 2;
        ll x = qmi(a, d, p);
        if(x == 1 || x == p - 1) continue;
        foa(i, 0, r - 1)
        {
            x = (__int128)x * x % p;
            if(x == p - 1) break;
        }
        if(x != p - 1) return false;
    }
    return true;
}

inline ll Pollard_Rho(ll n) // 本题的核心算法
{
    ll s = 0, t = 0;
    ll c = (ll)rand() % (n - 1) + 1;
    ll step = 0, goal = 1, val = 1;

    for(goal = 1;; goal *= 2, s = t, val = 1)
    {
        for(step = 1; step <= goal; ++ step)
        {
            t = ((__int128)t * t + c) % n;
            val = ((__int128)val * abs(t - s)) % n;
            if((step % 127) == 0) { ll d = gcd(val, n); if(d > 1) return d; }
        }
        ll d = gcd(val, n);
        if(d > 1) return d;
    }
}

inline void fac(ll x) // 分解
{
    if(x <= max_factor || x < 2) return ;
    if(Miller_Rabin(x)) { max_factor = max(max_factor, x); return ; }

    ll p = x;
    while(p >= x) p = Pollard_Rho(x);
    while((x % p) == 0) x /= p;
    fac(x), fac(p); 
}

inline void solve() // 多测
{
    srand(time(0));
    max_factor = 0; read(n);
    fac(n);
    if(max_factor == n) flush(), puts("Prime");
    else ww(max_factor), wl;
}

int main()
{
    // freopen("1.in", "r", stdin);
    ll T; read(T); while(T --) solve(); 
    flush(); return 0;
}
```

---

