# Fractal Origami

## 题目描述

You have a square piece of paper with a side length equal to $ 1 $ unit. In one operation, you fold each corner of the square to the center of the paper, thus forming another square with a side length equal to $ \dfrac{1}{\sqrt{2}} $ units. By taking this square as a new square, you do the operation again and repeat this process a total of $ N $ times.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/de3bbf1154da54ac557ac761cc9644c6d1e0f30d.png) Performing operations for $ N = 2 $ .After performing the set of operations, you open the paper with the same side up you started with and see some crease lines on it. Every crease line is one of two types: a mountain or a valley. A mountain is when the paper folds outward, and a valley is when the paper folds inward.

You calculate the sum of the length of all mountain crease lines on the paper and call it $ M $ . Similarly, you calculate for valley crease lines and call it $ V $ . You want to find the value of $ \dfrac{M}{V} $ .

It can be proved that this value can be represented in the form of $ A + B\sqrt{2} $ , where $ A $ and $ B $ are rational numbers. Let this $ B $ be represented as an irreducible fraction $ \dfrac{p}{q} $ , your task is to print $ p*inv(q) $ modulo $ 999\,999\,893 $ (note the unusual modulo), where $ inv(q) $ is the [modular inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse) of $ q $ .

## 说明/提示

The blue lines in the given figures represent mountain crease lines, and the green lines represent valley crease lines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/656ef1e31fbec994532b6ed88e854868aee0bb9e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/4d56d193615060ea6202f89c8971139a2bc8d811.png)Crease lines after $ 1 $ operation $ (\dfrac{M}{V} = 0) $ .Crease lines after $ 2 $ operations $ (\dfrac{M}{V} = \sqrt{2} - 1) $ .

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
0
1
714285638```

# 题解

## 作者：EuphoricStar (赞：9)

对这种题一点办法都没有。。。

可以手动折叠发现 $n = 3$ 时 $M = 2 + 2 \sqrt{2}, V = 2 + 4 \sqrt{2}$。于是大胆猜结论，第二次折叠开始，每次产生的山谷和山峰的长度相等。

为什么呢？考虑从第二次折叠开始，设当前纸的层数为 $k$（事实上若当前是第 $i$ 次折叠，$k = 2^{i - 1}$）。则奇数层的纸展开后是山谷，偶数层的纸展开后是山峰。所以 $V = M + 2 \sqrt{2}$ 恒成立。

这意味着我们只用计算 $n$ 次折叠后的总折痕长度 $V + M$，就能算出 $M$ 和 $V$ 的值。考虑每次折叠，纸的每一层的折痕长度为上一次折叠时 $\times \frac{1}{\sqrt{2}}$，但是纸的层数为上一次折叠时 $\times 2$。所以每次折叠，总折痕长度为上一次的 $\sqrt{2}$ 倍。于是 $M = \sum\limits_{i = 0}^{n - 2} 2 \sqrt{2}^i, V = 2 \sqrt{2} + \sum\limits_{i = 0}^{n - 2} 2 \sqrt{2}^i$。

至此直接套用等比数列求和公式 $s = \frac{a (1 - q^n)}{1 - q}$ 即可出答案。由于需要快速幂，时间复杂度为 $O(\sum \log n)$。

实现时封装一个 $a + b \sqrt{2}$ 的类会好写很多。

[code](https://codeforces.com/problemset/submission/1924/243701796)

---

## 作者：MaxBlazeResFire (赞：2)

找规律题。

记正方形边长为 $1$，$A$ 为凹折痕长度和，$B$ 为凸折痕长度和。

第一轮，$A=2\sqrt 2$。对于每一轮 $i\geq 1$，将第 $i$ 轮的凹凸边折痕组成的新正方形看作独立的子问题，会对第 $i+1$ 轮分别对称地贡献 $\displaystyle A'=\frac{A}{2\sqrt 2}$ 与 $\displaystyle B'=\frac{B}{2\sqrt 2}$。

于是答案就是

$\displaystyle f_N=\frac{\sum_{i=2}^N\frac{4}{\sqrt 2^i}2^{i-2}}{2\sqrt 2+\sum_{i=2}^N\frac{4}{\sqrt 2^i}2^{i-2}}=\frac{\sqrt 2^{N+2}+\sqrt 2^{N+1}-2\sqrt 2-2}{\sqrt 2^{N+2}+\sqrt 2^{N+1}-2}$。

虽然不太好分母有理化，但是可以对 $N$ 的奇偶性进行讨论规避掉问题。

复杂度 $O(T\log \rm mod)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define mod 999999893

inline int fp( int x , int p ){ int res = 1; while( p ){ if( p & 1 ) res = 1ll * res * x % mod; x = 1ll * x * x % mod; p >>= 1; } return res; }
inline void chkadd( int &x , int k ){ x += k; if( x >= mod ) x -= mod; }
inline int reduce( int x ){ return x + ( x >> 31 & mod ); }

int n;
inline void solve(){
	scanf("%d",&n);
	if( n & 1 ){
		int S = fp( 2 , ( n + 1 ) / 2 ); S = reduce( S - 2 );
		int fra = fp( reduce( 1ll * S * S % mod - fp( 2 , n + 2 ) ) , mod - 2 );
		int J = 1ll * ( mod - 2 ) * S % mod;
		printf("%lld\n",1ll * J * fra % mod);
	}
	else{
		int S = fp( 2 , ( n + 2 ) / 2 ); S = reduce( S - 2 );
		int fra = fp( reduce( 1ll * S * S % mod - fp( 2 , n + 1 ) ) , mod - 2 );
		int J = 1ll * ( mod - 2 ) * S % mod;
		printf("%lld\n",1ll * J * fra % mod);
	}
}

signed main(){
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：lalaouye (赞：1)

发现这个东西有一种隐隐约约的递推藏在里面，然后发现确实是递推。

具体的，我们注意到一个正方形先进行第一次折，我们发现实际上它分成了 $4$ 个小正方形，这四个小正方形是互相独立的，然后折完一次后它们都变成了一个三角形，我们试着分析每个三角形在后一次是怎么折的，发现折完以后还会是一个小三角形。


于是我们设 $f_i$ 表示已经折完 $n$ 次后展开 $i$ 次的每个小三角形（或第一次折之前的小正方形）的凹痕长度和， $g_i$ 则表示凸痕长度和，然后考虑转移。

首先，转移其实就是想象它折完之后再打开的过程，于是我们可以推出：

$$f_i=\frac{f_{i-1}+g_{i-1}}{\sqrt 2}+1$$

$$g_i=\frac{f_{i-1}+g_{i-1}}{\sqrt 2}$$

发现 $f_i=g_i+1$，那么最后要求的 $\frac{M}{V}$ 就是 $\frac{g_n}{g_n+1}=1-\frac{1}{g_n+1}$，由于我们只关心最后求出的 $b$，所以只计算 $-\frac{1}{g_n+1}$ 就行了。

然后我们考虑把 $f_i$ 像虚数一样表示成 $x+y\sqrt 2$，$g_i$ 同理，至于怎么求我想到了两种方法：

1.矩阵乘法，直接转移即可。

2.继续推式子，根据这个上面关于 $g_i$ 的两个式子还可以得到 $g_i=\sqrt 2 \times g_{i-1}+\frac{\sqrt 2}{2}$，对于这种 $g_i=k\times g_{i-1}+w$ 可以转换成另一种形式，$h_i=g_i+v,h_i=k \times h_{i-1}$，解个方程发现有 $h_i=g_i+1+\frac{\sqrt 2}{2},h_i=\sqrt 2 \times h_{i-1}$，其中 $h_1=1+\frac{\sqrt 2}{2}$，然后就有 $g_n+1=(1+\frac{\sqrt 2}{2})\sqrt 2^{n-1}-\frac{\sqrt 2}{2}$，简化一下：

$$\frac{1}{g_n+1}=\frac{1}{2^{\frac{n-1}{2}}+2^{\frac{n-2}{2}}-2^{-\frac{1}{2}}}$$

最后分类讨论 $n$ 的奇偶性求出 $x$ 和 $y$，然后分母有理化就可以求出 $b$ 了。

代码：

```
void solve ()
{
	int n = rd ();
	if (n & 1)
	{
		int x = qpow (2, (n + 1) >> 1);
		int y = 1 - qpow (2, (n - 1) >> 1);
	} else
	{
		int x = qpow (2, n >> 1);
		int y = 1 - x;
	}
	printf ("%lld\n", ((- 2 * y * qpow ((x * x - y * y * 2) % P, P - 2)) % P + P) % P);
}
```


---

## 作者：liaiyang (赞：1)

典型的推理题。

这个折纸很难推，但是我们知道 $V=M+2\sqrt 2$，因为显然每次折纸后山峰和山谷的增加量一样，且第一次的答案是 $M=0$，$V=2\sqrt2$。

而且每一次层数是 $2$ 倍，长度是 $\frac{\sqrt2}2$ 倍，所以每一次增加量是原增加量的 $\sqrt 2$ 倍。

又因为第一次到第二次的增加量是 $2$，所以我们有

$$M=\sum_{i=0}^{n-2}2\sqrt 2^i=2\sum_{i=0}^{n-2}\sqrt 2^i=2\frac{\sqrt 2^{n-1}-1}{\sqrt 2-1}=2(\sqrt2^{n-1}-1)(\sqrt2+1)$$
$$V=M+2\sqrt 2$$

维护有理数添加 $\sqrt2$ 的扩域 $Q(\sqrt2)$，在这上面做即可。

$Q(\sqrt 2)$ 显然是一个域，且所有形式显然一定形如 $a+b\sqrt2$，想一想为什么。

由于有快速幂，所以复杂度为 $O(\sum \log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
// #pragma GCC optimize(1)
// #pragma GCC optimize(2)
// #pragma GCC optimize(3,"Ofast")
#define int long long
#define y0 Y0
#define y1 Y1
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define min(a,b) (a<b?a:b) 
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
#define abs(x) ((x)<0?-(x):(x))
#define submod(x,y,mod) (((x-=y)<0)&&(x+=mod))
#define addmod(x,y,mod) (((x+=y)>=mod)&&(x-=mod))
mt19937 rnd(time(0));
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(int u=0, char c=getchar(), bool f=false){
    for(;!isdigit(c);c=getchar()) f|=c=='-';
    for(;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+(c^'0');
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar((x%10)^'0');
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1;
const int mod=999999893,g=3,gi=332748118;
const int N=2e5+10;
struct node{
    int x,y;
    node(int a,int b):x(a),y(b){}
};
node operator%(const node a,const int p){return node((a.x%p+p)%p,(a.y%p+p)%p);}
node operator+(const node a,const node b){return node(a.x+b.x,a.y+b.y);}
node operator-(const node a,const node b){return node(a.x-b.x,a.y-b.y);}
node operator*(const node a,const node b){return node(a.x*b.x+2*a.y*b.y,a.x*b.y+a.y*b.x);}
node power(node x,int k){
    node res={1,0};x=x%mod;
    while(k){
        if(k&1) res=res*x%mod;
        x=x*x%mod;
        k>>=1;
    }
    return res;
}
int power(int x,int k){
    int res=1;x=x%mod;
    while(k){
        if(k&1) res=res*x%mod;
        x=x*x%mod;
        k>>=1;
    }
    return res;
}
node operator/(const node a,const node b){
    int u=power(b.x*b.x-2*b.y*b.y,mod-2);
    return node((b.x*a.x-2*b.y*a.y)%mod*u%mod,(b.x*a.y-b.y*a.x)%mod*u%mod)%mod;
}
int n,T;
void work(){
    n=rd;
    node m=(((power(node(0,1),n-1)-node(1,0))%mod*node(1,1))%mod*node(2,0))%mod,v=(m+node(0,2))%mod;
    wt((m/v).y,'\n');
}
main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    T=rd;
    while(T--) work();
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

找规律发现每次 $M$ 和 $V$ 的增量是相同的，且是上一次增加量的 $\sqrt2$ 倍。以下定义 $q$ 为 $n-1$。

通过等比数列求和公式，$\frac{M}{V}=\frac{\sqrt2^{q+1}+\sqrt2^{q}-\sqrt2-1}{\sqrt2^{q+1}+\sqrt2^{q}-1}$。将上面式子写做 $\frac{x\sqrt2+y}{z\sqrt2+w}$ 的形式，其中 $x,y,z,w$ 可以直接算出来，对 $q$ 分奇偶讨论一下。

分母有理化，再把 $\sqrt2$ 提出来，可以得到题目最后要求我们输出的就是 $\frac{yz-xw}{2z^2-w^2}$，对分母求一下逆元输出就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=999999893;
int t,n,x,y,z,w,B;
int KSM(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		n--;
		if(n%2==0) x=(KSM(2,n/2)-1+mod)%mod,y=(KSM(2,n/2)-1+mod)%mod;
		else x=(KSM(2,(n-1)/2)-1+mod)%mod,y=(KSM(2,(n+1)/2)-1+mod)%mod;
		z=(x+1)%mod,w=y;
		B=(y*z%mod-x*w%mod+mod)%mod*KSM((z*z%mod*2%mod-w*w%mod+mod)%mod,mod-2)%mod;
		cout<<B<<endl;
	}
	return 0;
}
``````

---

## 作者：Z1qqurat (赞：0)

虽然场上根本没看这题但是赛后自己独立做出来了。本来看到这种想直接走人的结果折了一下发现会了，很有成就感。其实难点就是要发现每轮 $m,v$ 的增量相同的结论。

认真观察一下折纸过程，可以先看一下图（手折到了 $n=4$，不过这里仅展示 $n\le 3$，红线属于 $v$，黑线属于 $m$）

![](https://pic.imgdb.cn/item/65c8355b9f345e8d03bdaab3.jpg)

绿色标出来的正方形是第 $3$ 轮新折出来的，容易发现它以绿色线为对角线以颜色对称分布，想想这条绿线，它在折叠过程中其实相当于下面这条绿线：

![](https://pic.imgdb.cn/item/65c836fe9f345e8d03c16e02.png)

你会发现他其实相当于把自己“均分”给了红边和黑边，而这种绿线是每轮唯一会产生新的折痕的线了。这其实也就说明每一轮后红线和黑线的长度增长量是相同的。

那么这个增长量是多少呢？容易发现，每次的绿边会比上次的长度除掉一个 $\sqrt 2$，但是它的“分身”数量，也就是在各个地方的投影数量会 $\times 2$，所以说增长量每轮较上轮 $\times \sqrt 2$。而初始第一轮，设 $m=0,v=2$，第二轮的增长量就是 $\sqrt 2$，所以最终 $m=(\sqrt2+2)+(2\times\sqrt2+4)+(4\times\sqrt2+8)+\cdots,v=m+2$，我们直接考虑 $m$ 即可。

$m$ 一共会加 $n-1$ 项，分奇数位置项偶数位置项考虑，假设 $m$ 有 $x$ 个奇数位置项和 $y$ 个偶数位置项。奇数位置项之和是 $2^0\times\sqrt2+2^1\times\sqrt2+2^2\times\sqrt2+\cdots+2^{x-1}\sqrt2=(2^0+2^1+\cdots+2^{x-1})\sqrt{2}=(2^x-1)\sqrt2$，类似地可以得到偶数位置项之和是 $(2^y-1)2$。

于是得到 $m=(2^x-1)\sqrt2+(2^y-1)2$，推一下式子就可以求出 $b$ 了，具体就是 $b=\frac{2^x-1}{2^{2y+1}-2^{2x}+2^{x+1}-1}$，直接每次做快速幂再求逆元即可。代码只有 800B 左右。

[Submission.](https://codeforces.com/contest/1924/submission/245767474)

---

## 作者：TLE_Automat (赞：0)

## 题目链接

[https://codeforces.com/contest/1925/problem/F](https://codeforces.com/contest/1925/problem/F)

## 题目大意

![](https://espresso.codeforces.com/1bf93f34e8055ab56549c4ec1ea686c047564085.png)

将一个边长为 $1$ 的正方形按如图所示的方法进行 $N$ 次折叠（上图为 $N = 2$ 的情况），折叠之后展开。

展开后的折痕分为两种，一种是向内凹陷的折痕，总长度记为 $V$，另外一种是向外凸出的折痕，总长度记为 $M$。

可以证明 $\displaystyle\frac{M}{V} = A + B\sqrt{2}$，其中 $A,B$ 均为有理数。求 $B$ 对 $999\text{ }999\text{ }893$ 取模的结果。 

## 数据范围

- $1\le N \le 10^{9}$


## 解题思路

直接拿张纸来手动折几次，经过观察和推理不难发现下列性质：

- 所有凹陷的折痕全都是在奇数层产生的，所有凸出的折痕全都是在偶数层产生的。

- 第 $i$ 次折叠前纸片总共有 $2^{i - 1}$ 层，折叠时对每一层产生总长度为 $\displaystyle\frac{1}{(\sqrt{2})^{i}}$​ 的折痕。

设奇数层的折痕总长度为 $4L_1$，偶数层的折痕总长度为 $4L_2$，根据以上性质能够得到：
$$
\begin{aligned}

L_{1} &= \frac{1}{\sqrt{2}} + \frac{1}{(\sqrt{2})^{2}}\times 2^{0} + \frac{1}{(\sqrt{2})^{3}}\times 2^{1} + \cdots + \frac{1}{(\sqrt{2})^{n}}\times 2^{n - 2} = (\sqrt{2})^{n} + (\sqrt{2})^{n - 1} - 1  \\

L_{2} &= \frac{1}{(\sqrt{2})^{2}}\times 2^{0} + \frac{1}{(\sqrt{2})^{3}}\times 2^{1} + \cdots + \frac{1}{(\sqrt{2})^{n}}\times 2^{n - 2} = (\sqrt{2})^{n} + (\sqrt{2})^{n - 1} - \sqrt{2}- 1 \\

\end{aligned}
$$
我是直接暴力推 $\displaystyle\frac{L_{2}}{L_{1}}$ 算出来 $B$ 的，实际上不用那么麻烦。

实现一个 $a + b\sqrt{2}$ 的类，重载一下加减乘除运算即可，这样省下了推式子的时间，而且还不容易出错。

## 参考代码

[https://codeforces.com/contest/1925/submission/244500846](https://codeforces.com/contest/1925/submission/244500846)

---

## 作者：huazai676 (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1924C)

先考虑计算所有折痕总长度（~~是因为看错题了~~），在折第 $i$ 次前一共有 $2^{i-1}$ 层纸，正常折纸一次折痕长度为 $2 \sqrt 2$，每折一次长度变为原来的 $\frac{1}{\sqrt 2}$，所以第 $i$ 次的贡献为 $2^{i-1} \times 2 \sqrt 2 \times \frac{1}{{\sqrt 2}^{i-1}}$。

（~~然后差点以为做完了~~）然后通过上述分析发现折痕的方向与当前每层纸的方向有关。具体地，如果开始在正面染上黑色，则开始只有一层黑面（朝上），没有白面；折一次有一层黑面，一层白面；折两次有两层黑面，两层白面......每折一次都是把原来的每层纸翻过来盖在上面，除第一层外都是一半黑一半白。而上凸的折痕只有在白面朝上时折才会有，故所求长度之比即为 $\frac{\sum\limits_{i=2}^{N}{\sqrt 2}^i}{\sum\limits_{i=2}^{N}{\sqrt 2}^i+2 \sqrt 2}$。爆算就完了，最后答案可见代码。

[代码](https://codeforces.com/contest/1924/submission/243782040)

---

## 作者：UnyieldingTrilobite (赞：0)

考虑定义 $x_i$ 表示对折 $i$ 次的峰线长度，$y_i$ 表示对折 $i$ 次的谷线长度。由于只需要算比例，以下我们认为原正方形的边长是 $\frac{\sqrt{2}}4$。如此一来，我们对折一次所带来的 $y$ 贡献就是 $\frac{\frac{\sqrt2}4\times4}{\sqrt2}=1$ 了。我们考虑此后的折纸过程，会在小正方形中得到长为 $\frac{x_{i-1}}{\sqrt2}$ 的峰线和 $\frac{y_{i-1}}{\sqrt2}$ 的谷线。往回展平时，不难发现小正方形中的峰线在展品后的四个角长变成了谷线，而谷线变成了峰线。于是综上所述，我们可以得到：

$$\begin{cases}
        x_i=\frac{x_{i-1}+y_{i-1}}{\sqrt2}\\
        y_i=\frac{x_{i-1}+y_{i-1}}{\sqrt2}+1
\end{cases}$$

且

$$\begin{cases}
        x_1=0\\
        y_1=1
\end{cases}$$

不难发现有 $y_i=x_i+1$ 始终成立。而我们要算的就是 $\frac{x_i}{y_i}=1-\frac1{x_i+1}$ 的无理数部分，所以本质上就是要我们把 $x_i$ 算出来。

那么我们把 $x$ 式子里 $y$ 的部分代掉：

$$x_i=\frac{2x_{i-1}+1}{\sqrt2}$$

记录 $z_i=x_i+\frac{\sqrt2}2+1$，则：

$$z_i=\frac{2z_i}{\sqrt2}=\sqrt2z_i$$

又已知 $z_1=\frac{\sqrt2}2+1$，可以得到：

$$x_i=(2^{\frac{i-1}2}+2^{\frac{i-2}2})-(2^{-\frac12}+1)$$

于是 $-(x_i+1)=2^{-\frac12}-(2^{\frac{i-1}2}+2^{\frac{i-2}2})$，然后写个扩域就能算了。代码使用 atcoder lib，仅提供核心部分：

```cpp
using namespace std;
typedef atcoder::static_modint<999999893> mint;
struct ext {
  mint a, b;
  friend ext operator+(ext a, ext b) { return {a.a + b.a, a.b + b.b}; }
  friend ext operator-(ext a, ext b) { return {a.a - b.a, a.b - b.b}; }
  friend ext operator*(ext a, ext b) {
    return {a.a * b.a + a.b * b.b * 2, a.b * b.a + a.a * b.b};
  }
  friend ext operator/(ext a, mint x) { return {a.a / x, a.b / x}; }
  ext inv() const { return ext{a, -b} / (a * a - b * b * 2); }
  friend ext operator/(ext a, ext b) { return a * b.inv(); }
};
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T, n;
  for (cin >> T; T; --T) {
    cin >> n;
    if (n == 1) {
      cout << 0 << '\n';
      continue;
    }
    ext p;
    if (n & 1)
      p = {mint(2).pow((n - 1) >> 1), mint(2).pow((n - 3) >> 1)};
    else
      p = {mint(2).pow((n - 2) >> 1), mint(2).pow((n - 2) >> 1)};
    cout << ((ext{0, mint(2).inv()} - p).inv().b).val() << '\n';
  }
  return cout << flush, 0;
}
```

以上。

---

