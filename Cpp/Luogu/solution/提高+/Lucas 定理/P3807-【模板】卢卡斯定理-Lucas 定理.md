# 【模板】卢卡斯定理/Lucas 定理

## 题目背景

这是一道模板题。


## 题目描述

给定整数 $n, m, p$ 的值，求出 $C_{n + m}^n \bmod p$ 的值。

输入数据保证 $p$ 为质数。

注: $C$ 表示组合数。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n, m, p \leq 10^5$，$1 \leq T \leq 10$。

## 样例 #1

### 输入

```
2
1 2 5
2 1 5```

### 输出

```
3
3```

# 题解

## 作者：Lance1ot (赞：389)

卢卡斯定理

---
首先我们需要证明$C_p^i\equiv\frac{p}{i}C_{p-1}^{i-1}\equiv 0~~~(mod~p),(1<=i<=p-1)$

$C_p^i=\frac{p!}{i!(p-i)!}=\frac{p}{i} \frac{(p-1)!}{(i-1)!(p-1-i+1)!} \frac{p}{i} \frac{(p-1)!}{(i-1)!(p-i)!}=\frac{p}{i}C_{p-1}^{i-1}$

得证。

然后根据这种性质和二项式定理。，我们马上得出

$(1+x)^p\equiv C_p^0+C_p^1x^{1}+....+C_p^px^p\equiv C_p^0x^0+C_p^px^p\equiv 1+x^p(mod ~p)$

然后我们接下来要求证，这个式子是我们递归时用到的。

$C_a^b\equiv C_{a_0}^{b_0}\cdot C_{a_1p}^{b_1p} \cdot C_{a_2p^2}^{b_2p^2}.....(mod~p)$

但其实我们令$a=lp+r,b=sp+j$~~随便起的~~  

求证$C_a^b\equiv C_{l}^{s}\cdot C_{r}^{j}(mod~p)$然后利用性质递归求解就可以了。

继续从二次项定理出发

$(1+x)^a=(1+x)^{lp} \cdot (1+x)^r$

然后展开$(1+x)^{lp}$

$(1+x)^{lp} \equiv ((1+x)^p)^l \equiv (1+x^p)^l(mod~p)$

$\therefore (1+x)^a \equiv (1+x^p)^l \cdot (1+x)^r(mod~p)$

观察项$x^b$的系数

$\because C_a^bx^b \equiv C_l^sx^{sp} \cdot C_r^jx^j(mod~p)$

$\therefore C_a^bx^b \equiv C_l^s \cdot C_r^jx^b(mod~p)$

$\therefore C_a^b\equiv C_l^s\cdot C_r^j \equiv C_{\lfloor \frac{a}{p} \rfloor}^{\lfloor \frac{b}{p} \rfloor}\cdot C_{a~mod~p}^{b~mod~p}(mod~p)$

Ps:左边的是原来不经过化简的二项式展开，同时因为保证了$a=lp+r,b=sp+j$,所以右边不会出现其他的项。

---
后：本人已退役qwq。而且并没有用上自己学的（自我感觉省选无望qwq）

而且也系统的学过了二项式（好像暴漏年龄了）

对之前的错误表示抱歉，也欢迎大家继续挑刺/cy

转载什么的就不用问。转~，都可以转~

---

## 作者：_B3nwa1ker_ (赞：29)

 _以下的部分内容参考命题人讲座系列《初等数论》一书_ 

本篇笔记具体介绍卢卡斯定理的内容$,$证明$,$性质以及在$\texttt{OI}$中的用途$,$如有错误和疑问$,$请在评论区写下您的意见$.$

### 内容
《初等数论》一书对卢卡斯$\texttt{(Lucas)}$定理是这么定义的$:$
>	设$p$为素数$,a,b\in N^* ,$并且
$$a=\sum\limits_{i=0}^k a_i p^i,b=\sum\limits_{i=0}^k b_i p^i$$  

>	这里$0\leqslant a_i,b_i\leqslant p-1$都是整数,$i=0,1,2,…,k.$则$:$
$$C_a^b \equiv \prod\limits_{i=0}^k C_{a_i}^{b_i} \pmod{p}$$
>	或者写成这样$:$
$$C_a^b \equiv C_{a_k}^{b_k} \cdot C_{a_{k-1}}^{b_{k-1}} \cdot … \cdot C_{a_0}^{b_0}\pmod{p}$$
$Ps.$如果$b_i>a_i,$那么$C_{a_i}^{b_i} = 0 .$

### 证明
该书对定理的证明运用到了生成函数的知识$,$如果不了解生成函数的话$,$可以上网查一下$,$证明如下$:$
>	引入多项式同余$.$设
$$f(x)=\sum\limits_{i=0}^n a_i x^i,g(x)=\sum\limits_{i=0}^n b_i x^i$$

>	是两个整系数多项式$,$如果对于$0 \leqslant i \leqslant n,$都有$a_i \equiv b_i \pmod{m},$那我们称这两个多项式对模$m$同余$,$即$f(x) \equiv g(x) \pmod{m}.$  
>	显然我们知道对于$k \in N,$无论$x$取何值$,$必定有$f(k) \equiv g(k) \pmod{m}.$  
>	下面我们要证明一个引理$:$
$$(1+x)^p \equiv 1+x^p \pmod{p}$$
  
>	考虑将左边利用二项式定理展开$,$并利用$C_n^m=\frac{n}{m} C_{n-1}^{m-1},$则易得$C_p^1x$到$C_p^{p-1}x^{p-1}$的部分分别模$p$余$0,$剩下的就是右边了$.$  

>	利用该引理，我们可知
$$(1+x)^a = \prod\limits_{i=0}^k ((1+x)^{p^i})^{a_i}$$
$$\qquad\quad\qquad\qquad\qquad\quad \equiv \prod\limits_{i=0}^k (1+x^{p^i})^{a_i} \pmod{p}.\quad (1)$$
>	然后对比两边$x^b$项系数即可$.$

书上给的证明中没有详细讲如何对比$x^b$项的系数$,$这里讲一下$:$
>	对于一个数$,$我们易知它在某某进制下只有一种表示$,$即对于
$$b=\sum\limits_{i=0}^k b_i p^i,$$
>	从$b_0$到$b_n$是确定的$,$那么对于$(1)$式右边$,$我们便有唯一确定的取法凑出$x^b$项$,$即在$a_0$中取$b_0,$在$a_1$中取$b_1,$以此类推$……$  
>	在$(1+x)^{a_0}$中$x^{b_0}$项系数为$C_{a_0}^{b_0},$  
>	在$((1+x)^p)^{a_1}$中$x^{b_1 p}$项系数为$C_{a_1}^{b_1},$  
>	$……$  
>	在$((1+x)^{p^n})^{a_n}$中$x^{b_n p^n}$项系数为$C_{a_n}^{b_n},$  
>	又$b=\sum\limits_{i=0}^k b_i p^i,$  
>	所以将上面的乘起来就是右边所算的$x^b$的系数$,$由多项式同余的定义$,$可知定理成立$.$  

### 性质
该书又介绍了$\texttt{Lucas}$定理的两个性质$:$
>-	当且仅当存在$i \in \{ 0, 1, 2, …,k\}$使得$b_i > a_i$时$,C_a^b \equiv 0 \pmod{p}.$
>-	$C_a^b$ 为奇数的充要条件为二进制表示下$a$的每一位上的数都不小于$b$相应位上的数$.$  


### 应用
>	既然我们都把这东西都证出来了$,$那它有啥用呢$?$

作为一名~~曾经的~~$\texttt{oier},$当然要以实用为主啦$.$  
$\texttt{Lucas}$定理的主要用途在于在$O(\log_p a)$的时间求出$C_a^b \mod p$的结果$.$显然地$,$有一种方法$:$
>	对于$a,$我们预处理出$a_0,a_1,…,a_k,$对于$b$同理$.$然后我们直接算组合数并乘起来$,$注意随时取模$.$如果$p$较小且询问较多$,$可以考虑预处理组合数$.$  

这听起来很容易$,$但做起来好难啊$.$  
这时候我们把秦九韶请出来$,$可以将
$$\sum\limits_{i=0}^k a_i p^i$$ 
变成
$$(((a_kp+a_{k-1})p+a_{k-2})p+…)p+a_0$$
这样的形式$,$对于另一个同理$,$于是我们便可以层层除法$+$取模$,$将求解变成了一个递归形式$,$即$:$
$$Lucas(a,b,p)=Lucas(a/p,b/p,p) \cdot C_{a\%p}^{b\%p},$$
这里的$Lucas(a,b,p)$即要求的$C_a^b \mod p ,$  
代码如下$:$
```cpp
#include<iostream>
using namespace std;
const int maxn=100010;
long long mul[maxn];
long long quickpow(long long a,long long b,long long c)
{
	long long ans=1;a=a%c;
	while(b)
	{
		if(b&1) ans=(ans*a)%c;
		b>>=1;a=(a*a)%c;
	}
	return ans;
}
long long c(long long n,long long m,long long p)
{
	return (m>n)?0:((mul[n]*quickpow(mul[m],p-2,p))%p*quickpow(mul[n-m],p-2,p)%p);
}
long long lucas(long long n,long long m,long long p)
{
	return (m==0)?1:c(n%p,m%p,p)*lucas(n/p,m/p,p)%p;
}
int main()
{
	int t;cin>>t;
	for(int i=1;i<=t;i++)
	{
		long long n,m,p;cin>>n>>m>>p;mul[0]=1;
		for(int i=1;i<=p;i++) mul[i]=(mul[i-1]*i)%p;		//预处理阶乘
		cout<<lucas(n+m,n,p)<<endl;
	}
	return 0;
}
```
这里的代码运用了费马小定理求阶乘逆元以及直接计算组合数$,$如果不了解逆元$,$请左转模板区$($逃  

例题的话$,$那就$:$  
[P3807 【模板】卢卡斯定理](https://www.luogu.org/problem/P3807)  
[P4345 [SHOI2015]超能粒子炮·改](https://www.luogu.org/problem/P4345) 

---

## 作者：从蒟蒻到小犇 (赞：23)

网上对 Lucas 定理的证明基本上都是用二项式定理或者母函数，不过本蒟蒻发现了一个特别妙的证明。（~~可惜地方太小了写不下~~）

Lucas 定理：
当 $p$ 是**质数**时，
$$C_{n}^{m}\equiv C_{\lfloor n/p \rfloor}^{\lfloor m/p \rfloor}\cdot C_{n \bmod p}^{m \bmod p} \pmod p$$ 
其中 $\lfloor~\rfloor$ 表示向下取整。

## 前置知识
- 扩展欧几里得定理
- 逆元：当 $a$ 和 $p$ 互质时， $a$ 在 $\bmod~p$ 意义下的逆元唯一。
## 证明

我们首先把 $C_n^m$ 写成
$$ C_n^m=\frac{(n-m+1)(n-m+2) \cdots n}{1\times2 \cdots m} $$
上下都是 $m$ 个数，然后分开考虑 $p$ 的倍数部分和不是 $p$ 的倍数的部分。

### 引理
引理：当 $n \bmod p \geq m \bmod p$ 时，$C_n^m$ 上下（分子和分母） $p$ 的倍数的数量相等；当 $n \bmod p < m \bmod p$ 时， $C_n^m$ 上面分子中 $p$ 的倍数比下面分母中 $p$ 的倍数多一个。

![](https://cdn.luogu.com.cn/upload/image_hosting/wpnon08p.png)

如图，设 $p=5$，我把 $5$ 的倍数圈了起来，只有当 $n=18$ 或者 $n=19$ 的时候上下 $p$ 的倍数的数量相等，可以感性理解一下，也可以通过比较 $\lfloor \frac m p \rfloor$ 和  $\lfloor \frac n p \rfloor - \lfloor \frac {n-m} p \rfloor$ 来证明。

然后分 $n \bmod p \geq m \bmod p$ 和 $n \bmod p < m \bmod p$ 两种情况讨论。

### $n \bmod p \geq m \bmod p$ 的情况
数论里跟取模有关的事情经常会出现循环，那么组合数取模写出来之后也能发现循环，这里我举了 $p=3,n=17,m=7$ 的例子画图，把 $ C_n^m=\frac{(n-m+1)(n-m+2) \cdots n}{1\times2 \cdots m} $ 里面的数列了出来，然后把p的倍数圈起来，想分成 $p$ 的倍数和不是 $p$ 的倍数两部分考虑。

![](https://cdn.luogu.com.cn/upload/image_hosting/8ie7uigc.png)

图片里圈起来的 $p$ 的倍数部分每个数除以 $p$ 之后就变成连续的一段了，下面分母就是从 $1$ 乘到 $\lfloor \frac m p \rfloor$，而上面分子是从 $\lfloor \frac n p \rfloor$ 开始往下数，一共 $\lfloor \frac m p \rfloor$ 个数乘起来，所以说这部分就等于$C_{\lfloor n/p \rfloor}^{\lfloor m/p \rfloor}$。

然后考虑剩下的不是 $p$ 的倍数的部分，根据逆元唯一性，中间除以 $p$ 的余数相同的部分全都可以直接约掉，上下都剩 $m \bmod p$ 个数，上面分子从 $n \bmod p$ 往下数，下面分母从 $1$ 到 $m \bmod p$，所以这部分就同余于 $C_{n \bmod p}^{m \bmod p}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/gm4ilkmc.png)
于是有$C_{n}^{m}\equiv C_{\lfloor n/p \rfloor}^{\lfloor m/p \rfloor}\cdot C_{n \bmod p}^{m \bmod p} \pmod p$。

### $n \bmod p < m \bmod p$ 的情况
![](https://cdn.luogu.com.cn/upload/image_hosting/o7bd5vom.png)
类似的，上下都提出来 $\lfloor \frac m p \rfloor$ 个 $p$ 的倍数，就是 $C_{\lfloor n/p \rfloor}^{\lfloor m/p \rfloor}$。剩下的部分上面分子中有一个 $p$ 的倍数，那么这个数 $\bmod~p$ 就同余于 $0$，所以说这部分
$\text{分子乘积} \times \text{分母乘积的逆元} \equiv 0 \pmod p$，而 $n \bmod p < m \bmod p$ 时  $C_{n \bmod p}^{m \bmod p}=0$。

所以也有$C_{n}^{m}\equiv C_{\lfloor n/p \rfloor}^{\lfloor m/p \rfloor}\cdot C_{n \bmod p}^{m \bmod p} \pmod p$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mn=1e5;

ll 幂(ll a,ll b,ll p) {
    a%=p;
    ll ans=1%p;
    while(b>0) {
        if(b&1) ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}
ll 逆元(ll a,ll p) {
    return 幂(a,p-2,p);
}

int n,m,p,T;
ll 阶乘[mn+3],阶乘逆[mn+3];
ll C(int n,int m,int p) {
    if(n<m) return 0;
    if(n<p&&m<p) 
        return 阶乘[n]*阶乘逆[m]%p*阶乘逆[n-m]%p;
    return C(n/p,m/p,p)*C(n%p,m%p,p)%p;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("Lucas.in","r",stdin);
    #endif
    cin>>T;
    while(T--) {
        cin>>m>>n>>p;
        n+=m;
        阶乘[0]=1%p;
        for(int i=1;i<=p-1;i++) 阶乘[i]=阶乘[i-1]*i%p;
        阶乘逆[p-1]=逆元(阶乘[p-1],p);
        for(int i=p-1;i>=1;i--) 阶乘逆[i-1]=阶乘逆[i]*i%p;
        cout<<C(n,m,p)<<endl;
    }
    return 0;
}
```

---

## 作者：suxxsfe (赞：13)

题解大部分都是递归实现的，给出一种非递归的形式  
话说上课老师讲的时候没给代码，然后自己些就写成了这样  

对于质数$p$给出卢卡斯定理：  
$$\tbinom{n}{m}=\tbinom{n \bmod p}{m \bmod p}\tbinom{\lfloor \frac{n}{p}\rfloor}{\lfloor \frac{m}{p} \rfloor}\pmod p$$  
其实它还有另一种形式，虽然本质上没啥区别：  
$$\tbinom{n}{m}=\prod_{i=1}^k \tbinom{a_i}{b_i} \pmod p$$  
其中，$a,b$分别为$n,m$的$p$进制下的每一位，$k$是它们位数的较大值，当然如果有数不足$k$位，要补前导0  

-------  
来证明一下  
~~其实证明方法也是看了别人blog才知道的~~  
设$s=\lfloor \dfrac{n}{p}\rfloor,t=\lfloor \dfrac{m}{p}\rfloor$  
则有$q,w$使得$n=sp+q,m=tp+w$  
再考虑一个二项式：
$$(1+x)^n=((1+x)^p)^s(1+x)^q$$  
&nbsp;  
先由费马小定理推个结论：  
$$x^p\equiv x\pmod p \Rightarrow (x^p+1)\equiv (x+1)\pmod p$$  
$$(x+1)^p\equiv (x+1)\pmod p $$  
所以：
$$(x+1)^p\equiv (x^p+1)\pmod p$$  
&nbsp;  
把这个结论带进去：  
$$(1+x)^n\equiv (1+x^p)^s(1+x)^q \pmod p$$  
再由二项式定理把右边展开  
$$(1+x)^n\equiv \sum_{i=1}^s \tbinom{s}{i}x^{pi}\cdot \sum_{j=1}^q \tbinom{q}{j}x^j$$
同样我们可以把左边展开：  
$$(1+x)^n=\sum_{i=1}^{sp+q}\tbinom{sp+q}{i}x^i$$  
然后我们可以发现，左右两遍都有$x^{tp+w}$次项（当然，这是在$m\leq n$的情形下，如果$m>n$结果就是0，不用考虑了）  
比较一下它们的系数  
左边：$\tbinom{sp+q}{tp+w}x^{tp+w}$  
右边：$\tbinom{s}{t}x^{tp}\cdot \tbinom{q}{w}x^w$  
这边要说明一下，不会出现别的次数组合，比如$(t-1)p$和$(w+p)$，因为$w,q<p$  
所以：$\tbinom{sp+q}{tp+w}\equiv \tbinom{s}{t}\tbinom{q}{w}\pmod p$  
即：  
$$\tbinom{n}{m}\equiv\tbinom{n \bmod p}{m \bmod p}\tbinom{\lfloor \frac{n}{p}\rfloor}{\lfloor \frac{m}{p} \rfloor}\pmod p$$  
然后把$\tbinom{\lfloor \frac{n}{p}\rfloor}{\lfloor \frac{m}{p} \rfloor}$这一项不断展开，其实就变为了那种非递归形式  

------------  
好了，我们终于得到了这个定理  
那写代码就简单了，将$n,m$转化为$p$进制  
预处理出阶乘数组，和阶乘的逆元数组  
然后对于这$p$进制的每一位直接套组合数公式就行了  
~~然而代码似乎没有递归的好写~~  
~~另外一共5个点，我错了三遍下载了三个数据来调~~  
那么说一下踩得坑，首先主函数```for```循环里的特判一定要有，避免出现数组下标变成负数，或者使用0的逆元的情况  
还有多测时前导0的位置一定要清零  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<stack>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int n,m,p;
LL fac[200006],g[200006];
int a[100006],b[100006];
inline LL power(LL x,LL y){
	reg LL ans=1;
	while(y){
		if(y&1) ans=(1ll*ans*x)%p;
		y>>=1;x=(x*x*1ll)%p;
	}
	return ans;
}
std::stack<int>s;
inline void pre(){//预处理函数
	a[0]=b[0]=0;
	while(n){
		s.push(n%p);n/=p;
	}
	while(!s.empty()) a[++a[0]]=s.top(),s.pop();
	int tmp=0;
	while(m){
		tmp++;
		s.push(m%p);m/=p;
	}
	while(b[0]+tmp<a[0]) b[++b[0]]=0;//前导零的位置一定要清零 
	while(!s.empty()) b[++b[0]]=s.top(),s.pop();
	fac[0]=1;
	for(reg int i=1;i<p;i++) fac[i]=(1ll*fac[i-1]*i)%p;
	g[p-1]=power(fac[p-1],p-2);
	for(reg int i=p-2;i;i--) g[i]=(1ll*g[i+1]*(i+1))%p;
}
int main(){int t=read();while(t--){
	n=read();m=read();p=read();
	n+=m;m=n-m;
//	std::memset(a,0,sizeof a);std::memset(b,0,sizeof b);
	pre();
//		for(reg int i=1;i<=a[0];i++) std::printf("%d ",a[i]);EN;
//		for(reg int i=1;i<=b[0];i++) std::printf("%d ",b[i]);EN;
//		for(reg int i=0;i<p;i++) std::printf("%d ",fac[i]);EN;
//		for(reg int i=0;i<p;i++) std::printf("%d ",g[i]);EN;
	LL ans=1;
//		std::printf("%d %d\n",a[0],b[0]);
	for(reg int i=1;i<=a[0];i++){
		if(!b[i]) continue;
		if(a[i]<b[i]){ans=0;break;}
		if(a[i]==b[i]) continue;
		ans=(1ll*ans*fac[a[i]])%p;
		ans=(1ll*ans*g[b[i]])%p;
		ans=(1ll*ans*g[a[i]-b[i]])%p;
	}
	std::printf("%lld\n",ans);
}
	return 0;
}
```

---

## 作者：shihanyu2013 (赞：5)

# 卢卡斯定理/Lucas 定理

## 定理

$C^a_n \equiv C^\frac{a}{p}_\frac{n}{p} \times C^{a \bmod p}_{n \bmod p}{\pmod p}$

其中 $C$ 表示组合数，$C^m_n $ 也可以表示为$\displaystyle\binom{n}{m}$。

## 证明

我们考虑 $C^n_p \bmod p$ 的值，根据组合数的公式我们可以发现 $C^n_p = \frac{p!}{n!(p-n)!}$。

分子的质因数分解中 $p$ 的次数为 $1$，故只有 $n=0$ 或 $n=p$ 的情况下，$n!(p-n)!$ 的质因数中才含有 $p$，因此 $C^n_p \bmod p = [n = 0 \vee n = p]$。

进而我们可以得出

$$
\begin{align}
(a+b)^p &= \sum_{n=0}^p C^n_p a^n b^{p-n}\\
&\equiv \sum_{n=0}^p [n=0\vee n=p] a^n b^{p-n}\\
&\equiv a^p + b^p \pmod p
\end{align}
$$

因为过程中没有用到费马小定理，所以这一结论不仅适用于整数，也适用于多项式。因此我们可以考虑二项式 $f^p(x)=(ax^n + bx^m)^p \bmod p$  的结果

$$
\begin{align}
(ax^n + bx^m)^p &\equiv a^p x^{pn} + b^p x^{pm} \\
&\equiv ax^{pn} + bx^{pm}\\
&\equiv f(x^p)
\end{align}
$$

接下来思考二项式 $(1+x)^n \bmod p$，易得

$$
\begin{align}
(1+x)^n &\equiv (1+x)^{p\lfloor n/p \rfloor} (1+x)^{n\bmod p}\\
&\equiv (1+x^p)^{\lfloor n/p \rfloor} (1+x)^{n\bmod p}
\end{align}
$$

注意前者只有在 $p$ 的倍数位置才有取值，而后者最高次项为 $n\bmod p\le p-1$，因此这两部分的卷积在任何一个位置只有最多一种方式贡献取值，即在前者部分取 $p$ 的倍数次项，后者部分取剩余项。

即 $\displaystyle\binom{n}{m}\bmod p = \binom{\left\lfloor n/p \right\rfloor}{\left\lfloor m/p\right\rfloor}\cdot\binom{n\bmod p}{m\bmod p}\bmod p$

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,m,mod;
ll qpow(ll a,ll b,ll p){//快速幂
	if(b==0) return 1;
	if(b==1) return a%p;
	ll x=qpow(a,b/2,p)%p;
	if(b&1){
		return x*x%p*a%p;
	}
	return x*x%p;
}
ll c(ll a,ll b,ll p){
	if(b>a) return 0;
	ll res=1;
	for(int i=1,j=a;i<=b;i++,j--){//阶乘和阶乘逆元
		res=(ll)res*j%p;
		res=(ll)res*qpow(i,p-2,p)%p;
	}
	return res;
}
ll lucas(ll a,ll b,ll p){//lucas定理
	if(a<p&&b<p) return c(a,b,p)%p;
	return (ll)c(a%p,b%p,p)*lucas(a/p,b/p,p)%p;
}
signed main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n>>m>>mod;
		cout<<lucas(n+m,m,mod)<<'\n';
	}
  return 0;//好习惯
}
```

---

## 作者：liuli688 (赞：2)

由于 [OI Wiki](https://oi-wiki.org) 上提供的证明有些难以理解，写一篇题解作为更加易懂的证明及学习笔记．

参考资料：[https://oi-wiki.org/math/number-theory/lucas/](https://oi-wiki.org/math/number-theory/lucas/)，感谢 [vinegarcrab](https://www.luogu.com.cn/user/1176033) 和 [jch123](https://www.luogu.com.cn/user/709433) 对我的帮助．

---

Lucas 定理是指：对于 $p \in \mathbb P$（$\mathbb P$ 是质数集），有 $\dbinom n k \equiv \dbinom{\lfloor n/p \rfloor}{\lfloor k/p \rfloor}\dbinom{n \bmod p}{k \bmod p} \pmod p$．

证明：
> 考虑 $\dbinom p n \bmod p$：由定义可得 $\dbinom p n = \dfrac{p!}{n!(p-n)!}$．
> 
> 若 $n = 0$ 或 $n = p$，有 $n!(p-n)! = p!$，原式等于 $1$．否则，由于 $0 < n < p$，$n$ 和 $p - n$ 均小于 $p$，则 $n!$ 和 $(p-n)!$ 均不含 $p$ 这个因子．$p!$ 中有一个因子 $p$，分式上面含一个因子 $p$，分式下面不含因子 $p$，因子 $p$ 不会被除掉，$\dbinom p n$ 可被 $p$ 整除．因此，得到结论：
> $$\dbinom p n \equiv [n = 0 \lor n = p]$$
> 其中中括号是[艾佛森括号](https://baike.baidu.com/item/%E8%89%BE%E4%BD%9B%E6%A3%AE%E6%8B%AC%E5%8F%B7/22361197)。
>
> 考察 $(ax^n + bx^m)^p$：
> [二项式展开](https://oi-wiki.org/math/combinatorics/combination/#%E4%BA%8C%E9%A1%B9%E5%BC%8F%E5%AE%9A%E7%90%86)得到 $(ax^n + bx^m)^p = \displaystyle \sum_{k=0}^p\binom p k(ax^n)^k(bx^m)^{p-k}$．由刚才的结论 $\dbinom p n \equiv [n = 0 \lor n = p]$ 可得，只有当 $k = 0 \lor k = p$ 时，$\dbinom p k(ax^n)^k(bx^m)^{p-k} \bmod p \ne 0$，而此时 $\dbinom p k \bmod p = 1$．将 $k = 0$ 和 $k = p$ 代入，得
> $$\sum_{k=0}^p\binom p k(ax^n)^k(bx^m)^{p-k} \equiv a^px^{pn}+b^px^{pm} \pmod p$$
> 右边的 $a^px^{pn}+b^px^{pm}$ 分别是 $k = 0$ 和 $k = p$ 时式子的结果．
>
> 由[费马小定理](https://oi-wiki.org/math/number-theory/fermat/#%E8%B4%B9%E9%A9%AC%E5%B0%8F%E5%AE%9A%E7%90%86) $a^p \equiv a \pmod p$ 可以消掉 $a^p$ 和 $b^p$ 的指数，得
> $$a^px^{pn}+b^px^{pm} \equiv ax^{pn}+bx^{pm} \pmod p$$
> 发现相比于原来的式子，去掉了最外面的 $p$ 次幂，但是 $x$ 变为 $x^p$．得到结论：
> $$(ax^n + bx^m)^p \equiv ax^{pn}+bx^{pm} \pmod p$$
> 考察 $(1 + x)^n$：$(1+x)^n = (1+x)^{p\lfloor n/p\rfloor}(1+x)^{n \bmod p}$（拆分指数可直接得出）
> 
> 利用刚才的结论，将 $p$ 提出：$(1+x)^{p\lfloor n/p\rfloor}(1+x)^{n \bmod p} \equiv (1+x^p)^{\lfloor n/p\rfloor}(1+x)^{n \bmod p} \pmod p$
>
> 将 $(1+x)^n$ 二项式展开，$x^k$ 项的系数为 $\dbinom n k \bmod p$（就是杨辉三角里的那个顺序）．左右两边同余，计算右边 $x^k$ 的系数．
>
> 由于 $(1+x^p)^{\lfloor n/p\rfloor}$ 式子内已经有 $x^p$ 了，若 $\lfloor n/p\rfloor$ 个 $(1+x^p)$ 中选中 $q$ 个 $x^p$ 那么指数就是 $x^{pq}$，项的次数肯定是 $p$ 的倍数．$(1+x)^{n \bmod p}$ 中次数最高的项为 $x^{n \bmod p}$，次数小于 $p$，因此 $k$ 只能分解为 $p\lfloor k/p\rfloor+(k \bmod p)$，前半部分是第一个因子 $(1+x^p)^{\lfloor n/p\rfloor}$ 提供的，后半部分是第二个因子 $(1+x)^{n \bmod p}$ 提供的．
>
> 在乘法计算 $(1+x^p)^{\lfloor n/p\rfloor}$ 和 $(1+x)^{n \bmod p} \pmod p$ 时，一个一个相乘逐个计算，每次有两种选择：选 $1$ 或者选含 $x$ 的项．我们需要在左侧选 $\lfloor k/p\rfloor$ 个 $x$，右侧选 $k \bmod p$ 个 $x$，左侧的次数是 $\lfloor n/p\rfloor$，右侧的次数是 $n \bmod p$，那么在 $\lfloor n/p\rfloor$ 个 $x$ 中选 $\lfloor k/p\rfloor$ 个的方案乘上在 $n \bmod p$ 个 $x$ 中选 $k \bmod p$ 个的方案即为 $x^k$ 的系数：
> $$\binom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}\binom{n \bmod p}{k \bmod p}\bmod p$$
>
> 由于等式两边相等，则两边每项系数也相等．$(1+x)^{p\lfloor n/p\rfloor}(1+x)^{n \bmod p}
$ 第 $k$ 项的系数为 $\dbinom n k \bmod p$，$(1+x^p)^{\lfloor n/p\rfloor}(1+x)^{n \bmod p} \pmod p$ 第 $k$ 项的系数为 $\dbinom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}\dbinom{n \bmod p}{k \bmod p}\bmod p$，两边相等，则得到 Lucas 定理：
> $$\dbinom n k \bmod p = \dbinom{\lfloor n/p\rfloor}{\lfloor k/p\rfloor}\dbinom{n \bmod p}{k \bmod p}\bmod p$$
> 证毕．

在代码中，较小的 $\dbinom{n \bmod p}{k \bmod p}$ 可以直接通过预处理阶乘和[逆元](https://oi-wiki.org/math/number-theory/inverse/)计算，较大的另一部分继续递归降低规模，注意边界条件．详见代码．
### 代码
```cpp
#include <cstdio>
using ll = long long;

const int N = 1e5 + 10;
int T, n, m, p; ll fac[N];

ll qpow(ll a, ll b, const ll& p) {
	ll ans = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ans = ans * a % p;
		a = a * a % p;
	}
	return ans;
}

#define inv(a, p) qpow(a, (p) - 2, p)
#define C(n, m, p) ((n) >= (m) ? fac[n] * inv(fac[m], p) % (p) * inv(fac[(n)-(m)], p) % (p) : 0)


ll Lucas(ll n, ll m, ll p) {
	return m ? C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p : 1;
}

signed main() {
	for (scanf("%d", &T); T--; ) {
		scanf("%d%d%d", &n, &m, &p); m += n;
		fac[0] = 1;
		for (int i = 1; i < N; ++i)
			fac[i] = fac[i - 1] * i % p;
		printf("%lld\n", Lucas(m, n, p));
	}
	return 0;
}
```

---

## 作者：totorato (赞：2)

# 统计分子分母中因子p的个数

如果直接在模$P$意义下计算组合数，我们需要利用逆元完成除法。

问题是，当$P$比$N,M$要小的时候，组合数的分子分母中都出现了$P$作为因子，这时会导致分母的数没有逆元而无法计算。

因此，我们不妨把每个数分解为$X=A\times P^t$的形式，其中$A$不含$P$这个因子。这样，最终的答案一定可以表示为：
$$C_n^m = \frac{x\times P^a}{y\times P^b}$$
这样的形式，并且我们知道，$a>b$时答案一定是$0$、$a=b$时约分后可以在模$P$意义下通过$x\times inv(y)$求出答案。并且，不可能出现$a<b$的情况，因为这样意味着组合数不是整数。

具体的实现很简单。如果线性预处理每一个数的分解形式(积性函数)，该方法可以做到$O(P+min(N,M))$。但代码偷懒只做到了$O(P+min(N,M)log_P(N+M))$

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int N, M, P;
int inv[100001];

struct NUM
{
	int x, c;
	NUM (const int& tx = 0, const int& tc = 0) : x(tx), c(tc) {}
	NUM operator * (const NUM& t) {return NUM(1ll*x*t.x%P, c+t.c);}
	NUM operator / (const NUM& t) {return NUM(1ll*x*inv[t.x]%P, c-t.c);}
};

NUM divide(int x)
{
	NUM ret(x, 0);
	while(ret.x % P == 0) ret.x /= P, ret.c ++;
	ret.x %= P;
	return ret;
}

void init()
{
	inv[0] = inv[1] = 1;
	for(int i=2; i<P; i++) inv[i] = (-1ll*(P/i)*inv[P%i]+1ll*P*P)%P;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		NUM ans; ans.x = 1, ans.c = 0;
		scanf("%d%d%d", &N, &M, &P);
		init();
		if(N < M) swap(N, M);
		for(int i=1; i<=M; i++)
			ans = ans*divide(N+i)/divide(i);
		if(ans.c) printf("0\n");
		else printf("%d\n", ans.x);
	}
	return 0;
}
```

---

## 作者：LoongPig (赞：2)

# Lucas 定理

对于质数 $p$，有：
$$\begin{pmatrix}n\\k\end{pmatrix}\equiv \begin{pmatrix}\lfloor n\div p\rfloor\\\lfloor k\div p\rfloor\end{pmatrix}\begin{pmatrix}n \bmod p\\ k\bmod p\end{pmatrix}\pmod p$$

其中，当 $n < k$ 时，二项式系数 $\begin{pmatrix}n\\k\end{pmatrix}$ 规定为 $0$。

## 证明

考虑 $\begin{pmatrix}p\\n\end{pmatrix} \bmod p$ 等于多少。

因为$\begin{pmatrix}p\\n\end{pmatrix}=\frac{p!}{n!(p-n)!}$，所以，当 $n\not = 0$ 且 $n\not = p$ 时，分母中没有因子 $p$，但分子中有分子 $p$，所以该分式一定是 $p$ 的倍数，模 $p$ 的余数是 $0$；当 $n=p$ 或 $n=0$ 时，该分式就等于 $1$。所以：
$$\begin{pmatrix}p\\n\end{pmatrix}\equiv[n=0\vee n=p]\pmod p$$

记 $f(x)=ax^n+bx^m$。一般地，由二项式展开和费马小定理有:
$$\begin{aligned}
f(x)^p&=\sum^p_{k=0}\begin{pmatrix}p\\k\end{pmatrix}(ax^n)^k(bx^m)^{p-k}\\
&=a^px^{pn}+b^px^{pm}\\
&=a(x^p)^n+b(x^p)^m\\
&=f(x^p)\pmod p
\end{aligned}$$

利用这一结论，考虑二项式展开：
$$
\begin{aligned}
(1+x)^n&=(1+x)^{p\lfloor n\div p\rfloor}(1+x)^{n\bmod p}\\
&\equiv (1+x^p)^{\lfloor n\div p\rfloor}(1+x)^{n\bmod p}\pmod p
\end{aligned}
$$
等式左侧中，项 $x^k$ 的系数为 $\begin{pmatrix}n\\k\end{pmatrix}\bmod p$。

计算等式右侧中项 $x^k$ 的系数。第一个因子中各项的次数必然是 $p$ 的倍数，第二个因子中各项的次数必然小于 $p$，而 $k$ 分解成这样两部分的和的方式是唯一的，即带余除法：$k=p\lfloor k\div p\rfloor+(k \bmod p)$。因此，第一个因子只能贡献其 $p\lfloor k\div p\rfloor$ 次项，第二个因子只能贡献其 $k\bmod p$ 次项。所以，右侧等式中 $x^k$ 的系数为两个因子各自贡献的项的系数的乘积：

$$\begin{pmatrix}\lfloor n\div p\rfloor\\\lfloor k\div p\rfloor\end{pmatrix}\begin{pmatrix}n \bmod p\\ k\bmod p\end{pmatrix}\pmod p$$

令两侧系数相等，就可以得到 Lucas 定理。

## 代码

```cpp
long long Lucas(long long n,long long k,long long p) {
  if (k==0) return 1;
  return C(n%p,k%p,p)*Lucas(n/p,k/p,p)%p;
}
```
其中，`C(n,k,p)` 是一个计算 $C_n^k\bmod p$ 的函数。

---

## 作者：King_tissue (赞：1)

这是一道模板 Lucas 定理。

### Lucas 定理 公式定义

设非负整数 $ n, m $ 和质数 $ p $，此时有：
$$
\begin{cases}
n = s p + q, & q = n \bmod p \\
m = t p + r, & r = m \bmod p
\end{cases}
$$
则组合数模 $ p $ 的值为：
$$
\binom{n}{m} \equiv \binom{s}{t} \cdot \binom{q}{r} \pmod{p}
$$
将上面式子表示成递归的形式（也就是C++中经常用到的样子）：
$$
\binom{n}{m} \equiv \binom{\lfloor n/p \rfloor}{\lfloor m/p \rfloor} \cdot \binom{n \bmod p}{m \bmod p} \pmod{p}
$$

### Lucas 定理 证明过程

#### 引理

对素数 $ p $ 和整数 $ x $，有：
$ (1 + x)^p \equiv 1 + x^p \pmod{p} $

#### 引理 证明

由二项式展开可得：$ (1 + x)^p = \sum_{k=0}^{p} \binom{p}{k} x^k $

考虑当 $ 0 < k < p $ 时，$ \binom{p}{k} = \frac{p!}{k!(p-k)!} $ 可以被 $ p $ 整除，故：
$$
(1 + x)^p \equiv 1 + x^p \pmod{p}
$$

#### Lucas 定理 证明
将 $ (1 + x)^n $ 展开为：
$$
(1 + x)^n = (1 + x)^{s \times p + q} = \left[ (1 + x)^p \right]^s \cdot (1 + x)^q
$$
根据 **引理** 转化可得：
$$
(1 + x)^n \equiv (1 + x^p)^s \cdot (1 + x)^q \pmod{p}
$$
此时比较两边 $ x^m $ 的系数。

左侧：$ \binom{n}{m} $。

右侧：仅当 $ m = t \times p + r $ 时，存在 $ \binom{s}{t} x^{t \times p} \cdot \binom{q}{r} x^r $ 项，其他情况无法组合出指数 $ m $。

因此可得：
$$
\binom{n}{m} \equiv \binom{s}{t} \binom{q}{r} \pmod{p}
$$

故得证。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, a[100005], n, r, o, mod, prime[100005];
long long ans = 1;
bool vis[100005];
void init() {
	for (int i = 2; i <= 1e5; i++) {
		if (!vis[i]) prime[o++] = i;
		for (int j = 0; j < o && i * prime[j] <= 1e5; j++) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}
void check(int Gues, int t) {
	for (int m = 0; prime[m] <= Gues; m++) {
		while (Gues % prime[m] == 0 && Gues != 1) {
			Gues /= prime[m]; a[prime[m]] += t;
		}
	}
}
int main() {
	cin >> t; init();
	while (t--) {
		cin >> r >> n >> mod;
		memset(a, 0, sizeof(a));
		n += r; ans = 1;
		for (int i = n - r + 1; i <= n; i++) check(i, 1);
		for (int j = r; j > 1; j--) check(j, -1);
		for (int i = 0; i < o; i++) {
			while (a[prime[i]]--) ans = ans * prime[i] % mod;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

萌新的第三次，求管理通过。

---

## 作者：StarsIntoSea_SY (赞：1)

# 二项式定理

若 $n$ 是正整数，则有：$\begin{aligned} (x+y)^n = \sum_{i=0}^n C_{n}^{i} x^i y^{n-i} \end{aligned}$。

用数学归纳法证明：

当 $n=1$ 时原式显然成立。

假设 $n=k$ 时原式成立，则 $n=k+1$ 时，有：
$$
\begin{aligned}
 (x+y)^{k+1} &= (x+y)(x+y)^k \\
  &=(x+y) \sum_{i=0}^{k}C_{k}^{i} x^i y^{k-i} \\
  &=(x+y) (C_k^0 y^k+C_k^1 x y^{k-1}+\dots+C_k^{k-1}x^{k-1}y+C_k^k x^k) \\
  &=x^{k+1} + y^{k+1} + (C_k^0+C_k^1)xy^k+(C_k^1+C_k^2)x^2y^{k-1}+\dots+(C_k^{k-1}+C_k^k)x^ky \\
  &= x^{k+1} + y^{k+1} + \sum_{i=1}^k (C_k^{i-1}+C_k^{i})x^i y^{k-i+1}
\end{aligned}
$$
因为
$$
\begin{aligned}
C_k^{i-1}+C_k^{i} &= \frac{k!}{(i-1)!(k-i+1)!} +\frac{k!}{i!(k-i)!} \\
&= \frac{k!\:i!\:(k-i)!+k!\:(i-1)!\:(k-i+1)!}{i! \: (i-1)! \: (k-i)! \: (k-i+1)!} \\
&= \frac{(k+1)!}{i! (k-i+1)!} \\
&= C_{k+1}^i
\end{aligned}
$$
所以
$$
\begin{aligned}
(x+y)^{k+1} &= x^{k+1} + y^{k+1} + \sum_{i=1}^k C_{k+1}^ix^i y^{k-i+1} \\
&=\sum_{i=0}^{k+1}C_{k+1}^ix^i y^{k-i+1}
\end{aligned}
$$
因此 $n=k+1$ 时原式也成立，得证。

# 一个引理

若 $p$ 是素数，则有：$(x+y)^p \equiv x^p + y^p \pmod p$。

证明：由二项式定理可知：$\begin{aligned} (x+y)^p = \sum_{i=0}^p C_{p}^{i} x^i y^{p-i} \end{aligned}$。

其中当 $1 \le i < p$ 时：
$$
\begin{aligned}
C_p^i &= \frac{p!}{i!(p-i)!} \\
&= \frac{p\times(p-1)!}{i \times (i-1)!(p-i)!} \\
&= \frac{p}{i} C_{p-1}^{i-1}
\end{aligned}
$$
所以
$$
\begin{aligned}
C_p^i & \equiv \frac{p}{i} C_{p-1}^{i-1} \\
& \equiv \frac{p}{i} C_{p-1}^{i-1} \times i \times inv(i)\\
& \equiv p \times inv(i) C_{p-1}^{i-1} \\
& \equiv 0 \pmod p
\end{aligned}
$$
其中 $inv(i)$ 表示 $i$ 在模 $p$ 意义下的乘法逆元。因为 $p$ 是素数且 $i < p$，故 $inv(i)$ 一定存在。

原式在同余式中只剩下 $i=0,p$ 两项，得证。

# Lucas 定理

若 $p$ 是素数，则有：$C_n^m \equiv C_{\lfloor \frac{n}{p} \rfloor}^{\lfloor \frac{m}{p} \rfloor} \times C_{n \bmod p}^{m \bmod p} \pmod p $。

证明：

根据带余除法，令 $n=ap+b,m=cp+d$，其中 $0 \le b,d < p$。

根据二项式定理得到式子一：
$$
(1+x) ^n \equiv \sum_{i=0}^{n} C_n^i x^i \pmod p
$$
根据二项式定理和引理得到式子二：
$$
\begin{aligned}
 (1+x) ^n &\equiv (1+x)^{ap+b} \\
 &\equiv ((1+x)^p)^a\times(1+x)^b\\
 &\equiv (1+x^p)^a \times(1+x)^b \\
 &\equiv (\sum_{i=0}^a C_a^i x^{ip})(\sum_{j=0}^b C_b^j x^j) \pmod p
\end{aligned}
$$
由式子一可知 $x^m$ 的系数为 $C_n^m$。

由式子二可知 $x^m=x^{cp+d}$ 的系数为 $C_a^c C_b^d$。

因为 $\lfloor \frac{n}{p} \rfloor = a ,\lfloor \frac{m}{p} \rfloor = c,n \bmod p =b,m \bmod p=d$。

所以 $C_n^m \equiv C_{\lfloor \frac{n}{p} \rfloor}^{\lfloor \frac{m}{p} \rfloor} \times C_{n \bmod p}^{m \bmod p} \pmod p$，证毕。

我们发现在求 $C_n^m \bmod p$ 时不太好求，因为是两个很大的数相除，得转换成乘的形式。

因为 $p$ 是素数，根据费马小定理：$m!^{p-1} \equiv 1 \pmod p,(n-m)!^{p-1} \pmod p$。

那么有：
$$
C_n^m=\frac{n!}{m!(n-m)!} \equiv n! \times m!^{p-2} \times (n-m)!^{p-2} \pmod p
$$

但是这样求是有一点问题的，因为 $m!$ 或者 $(n-m)!$ 可能是 $p$ 的倍数，就不能用费马小定理了。

其实具体实现是可以避免的，因为在求 $C_{n \bmod p}^{m \bmod p} \pmod p$ 时费马小定理是肯定成立的，可以直接求。$ C_{\lfloor \frac{n}{p} \rfloor}^{\lfloor \frac{m}{p} \rfloor} \pmod p$ 虽然没法直接求，但是可以利用 Lucas 定理进一步拆开，直到都能够拆成可求解的形式即可。

# Code

```cpp
#include <stdio.h>
#define int long long
int f[100005];
void init(int a,int p){ //求阶乘，f[i]=i!
	f[0]=f[1]=1;
	for(int i=2;i<=a;++i)
		f[i]=(f[i-1]*i)%p;
}
int pow(int a,int b,int p){  //快速幂
	a%=p;
	int res=1;
	while(b>0){
		if(b&1ll) res=(res*a)%p;
		a=(a*a)%p;
		b>>=1ll;
	}
	return res;
}
int C(int m,int n,int p){
	if(m>n) return 0;
	return (f[n]*pow(f[m],p-2,p)%p *pow(f[n-m],p-2,p))%p; //利用费马小定理求C
}
int Lucas(int m,int n,int p){
	if(!m) return 1;
	return C(m%p,n%p,p)*Lucas(m/p,n/p,p)%p;
  //m%p、n%p时可以直接求，m/p、n/p时可能不满足费马小定理则继续递归拆解
}
signed main(){
	int T; scanf("%lld",&T);
	while(T--){
		int n,m,p; scanf("%lld%lld%lld",&n,&m,&p);
		init(n+m,p);
		printf("%lld\n",Lucas(n,n+m,p));
	}
}
```

---

## 作者：TH911 (赞：1)

# 卢卡斯定理 Lucas 定理

Lucas 定理用于求解大组合数取**质数模**。（对于模数不为质数的情况，请参考[exLucas 定理（扩展卢卡斯）](https://www.luogu.com.cn/problem/P4720)）。

Lucas 定理的内容很简单：

$$
\binom{n}{m}\equiv\binom{\lfloor\frac np\rfloor}{\lfloor\frac mp\rfloor}\binom{n\bmod p}{m\bmod p}\pmod p
$$

考虑如何证明。

## 证明

由二项式定理：

$$
(a+b)^p=\sum_{i=0}^p\binom pia^ib^{p-i}
$$

考虑 $\dbinom pi$ 在模 $p$ 意义下的取值。

因为：

$$
\dbinom pi=\dfrac{p!}{i!(p-i)!}
$$

那么如果化简之后，分子 $p!$ 中的 $p$ 项**没有**被约分掉，则有 $\dbinom pi\equiv p\cdot\dfrac{(p-1)!}{i!(p-i)!}\equiv0\pmod p$。

因为 $p$ 为质数，所以 $p$ 项能被约分掉当且仅当 $i!$ 中含有 $p$ 项或 $(p-i)!$ 中含有 $p$ 项。

即：$\dbinom pi\not\equiv0\pmod p$ 当且仅当 $i\equiv0\pmod p$ 或 $p-i\equiv 0\pmod p$。

在二项式定理中，$i$ 满足 $0\leq i\leq p$，所以 $\dbinom pi\not\equiv0$ 当且仅当 $i=0$ 或 $i=p$。

在这两种情况中，都可以计算得到 $\dbinom pi=1$，即 $\dbinom pi\equiv[i=0\lor i=p]$。

重新带回二项式定理，可得：
$$
\begin{aligned}
(a+b)^p&\equiv \dbinom{p}{0}a^0b^p+\dbinom ppa^pb^0\\
&\equiv a^p+b^p
\end{aligned}
\pmod p
$$

***

考虑一个二项式 $(1+x)^n\bmod p$。

$$
\begin{aligned}
(1+x)^n&\equiv (1+x)^{p\lfloor\frac np\rfloor+n\bmod p}\\
&\equiv(1+x)^{p\lfloor\frac np\rfloor}(1+x)^{n\bmod p}\\
&\equiv(1+x^p)^{\lfloor\frac np\rfloor}(1+x)^{n\bmod p}\\
\end{aligned}
\pmod p
$$

由二项式定理，$(1+x)^n$ 的 $x^m$ 项系数为 $\dbinom nm$。

而想要从 $(1+x^p)^{\lfloor\frac np\rfloor}(1+x)^{n\bmod p}$ 中得到 $x^m$，即从 $(1+x^p)^{\lfloor\frac np\rfloor}$ 中选取 $\lfloor\frac mp\rfloor$ 个 $x^p$，再从 $(1+x)^{n\bmod p}$ 中选取 $m\bmod p$ 个 $x$。

即：

$$
\dbinom nm\equiv\dbinom{\lfloor\frac np\rfloor}{\lfloor\frac mp\rfloor}\dbinom{n\bmod p}{m\bmod p}
\pmod p
$$

***

你可能有一个问题：这看起来明明应当是一个**等式**，但为什么是**同余**呢？

即，Lucas 定理应当表述为：
$$
\dbinom nm=\dbinom{\lfloor\frac np\rfloor}{\lfloor\frac mp\rfloor}\dbinom{n\bmod p}{m\bmod p}
$$
但是，你要知道，只有在模 $p$ 意义下才有 $(1+x)^{p\lfloor\frac np\rfloor}=(1+x^p)^{\lfloor\frac np\rfloor}$。

因此，只有在模 $p$ 意义下才有：

$$
\dbinom nm=\dbinom{\lfloor\frac np\rfloor}{\lfloor\frac mp\rfloor}\dbinom{n\bmod p}{m\bmod p}
$$

即：
$$
\dbinom nm\equiv\dbinom{\lfloor\frac np\rfloor}{\lfloor\frac mp\rfloor}\dbinom{n\bmod p}{m\bmod p}\pmod p
$$

## 应用

当 $n$ 比较大而无法使用其他方法（例如预处理 $1\sim n$ 的阶乘再利用乘法逆元）直接求解组合数时，可以使用 Lucas 定理。

Lucas 定理只需要递归使用即可，即递归计算 $\dbinom{\lfloor\frac np\rfloor}{\lfloor\frac mp\rfloor}$，递归终点即 $\dbinom{0}{0}$。

其时间复杂度为：$\mathcal O\left(f(p)\log n\right)$。

其中，$f(p)$ 表示单次计算 $\dbinom{n\bmod p}{m\bmod p}$ 的复杂度，因写法而异。

可以使用乘法逆元，则时间复杂度为 $\mathcal O(\log p\log n)$。

也可以 $\mathcal O(p\log p)$ 递推，时间复杂度为 $\mathcal O(p\log p\log n)$。

* $p$ 较大时，推荐使用乘法逆元。
* $p$ 较小时，可以考虑 $\mathcal O\left(p^2\right)$ 空间复杂度的预处理组合数。

# AC 代码

比较懒，写的 $\mathcal O(p\log p\log n)$。

```cpp
#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
using namespace std;
const int N=1e5;
int ksm(int a,int n,int p){
	if(n==0)return 1;
	int t=ksm(a,n>>1,p);
	t=1ll*t*t%p;
	if(n&1)t=1ll*t*a%p;
	return t;
}
int C(int n,int m,int p){
	static int ans[N+1]={1};
	for(int i=1;i<=m;i++){
		ans[i]=1ll*ans[i-1]*(n-i+1)%p*ksm(i,p-2,p)%p;
	}return ans[m];
}
int Lucas(int n,int m,int p){
	if(m==0)return 1;
	return (1ll*Lucas(n/p,m/p,p)*C(n%p,m%p,p))%p;
}
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	int T,n,m,p;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&n,&m,&p);
		printf("%d\n",Lucas(n+m,n,p));
	}
	
	/*fclose(stdin);
	fclose(stdout);*/
	return 0;
}
```

---

