# A Creative Cutout

## 题目描述

Everything red frightens Nian the monster. So do red paper and... you, red on Codeforces, potential or real.

Big Banban has got a piece of paper with endless lattice points, where lattice points form squares with the same area. His most favorite closed shape is the circle because of its beauty and simplicity. Once he had obtained this piece of paper, he prepares it for paper-cutting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933D/fba66fdeec16664c87daa27f59929551b565a742.png)He drew $ n $ concentric circles on it and numbered these circles from $ 1 $ to $ n $ such that the center of each circle is the same lattice point and the radius of the $ k $ -th circle is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933D/f2545ba51c140bc44922a670a0d4e8502561a2ce.png) times the length of a lattice edge.

Define the degree of beauty of a lattice point as the summation of the indices of circles such that this lattice point is inside them, or on their bounds. Banban wanted to ask you the total degree of beauty of all the lattice points, but changed his mind.

Defining the total degree of beauty of all the lattice points on a piece of paper with $ n $ circles as $ f(n) $ , you are asked to figure out ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933D/42aed05e24327c5ba0418b29dac5d6f560b757dc.png).

## 说明/提示

A piece of paper with $ 5 $ circles is shown in the following.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933D/65a79d77425901c2fc1a4e4f5cdee759591ef50f.png)There are $ 5 $ types of lattice points where the degree of beauty of each red point is $ 1+2+3+4+5=15 $ , the degree of beauty of each orange point is $ 2+3+4+5=14 $ , the degree of beauty of each green point is $ 4+5=9 $ , the degree of beauty of each blue point is $ 5 $ and the degree of beauty of each gray point is $ 0 $ . Therefore, $ f(5)=5·15+4·14+4·9+8·5=207 $ .

Similarly, $ f(1)=5,f(2)=23,f(3)=50,f(4)=102 $ and consequently ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF933D/e417b5a75ba12c36c31dd616d86cc711bf7c6e0a.png).

## 样例 #1

### 输入

```
5
```

### 输出

```
387
```

## 样例 #2

### 输入

```
233
```

### 输出

```
788243189
```

# 题解

## 作者：GreenDay (赞：8)

**题意**

定义$g(x,y)$表示所有包含点$(x,y)$（含在圆上）的圆编号之和，

若有编号为$i(i\le n)$,半径为$\sqrt{i}$，圆心为原点的圆$n$个，则$f(i)=\sum_{x,y}g(x,y)$,求$\sum_{i=1}^nf(i) \operatorname{mod} 10^9+7.$

$n \le 10^{12}$

[点这里看题](https://www.luogu.com.cn/problem/CF933D)

**做法**

考虑每个点$P(x,y)$的贡献，记$a=x^2+y^2$，枚举每个点被包含圆的编号及其在答案中出现次数：

$$
\sum\limits_{i=a}^ni(n-i+1)
$$

$$
= (1+n)\sum\limits_{i=a}^ni -\sum\limits_{i=a}^ni^2
$$

$$
=\frac 1 2(1+n)(n+a)(n-a+1)-\frac 1 6n(n+1)(2n+1) + \frac 1 6(a-1)a(2a-1)
$$

我们确定一个$x$，则枚举$y$是一个区间和。把a回代入原式子，可以得到关于$y$的6次多项式的一个和式。各位硬核选手直接推式子。我比较菜，所以选择**拉格朗日插值**。6次多项式套上一个$\sum$后为7次，所以我们插8个值就可以了。

$\mathcal O(n^{0.5})$


**code**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
int64 n , nn , inv2 , inv3 , inv6;
int mod = 1e9 + 7, ans;

int64 calc(int64 a) {
    int64 x = (1+nn)*(nn+a)%mod*(nn-a+1)%mod*inv2%mod-nn*(nn+1)%mod*(2*nn+1)%mod*inv6%mod+(a-1)*a%mod*(2*a-1)%mod*inv6%mod;
    return (x%mod+mod)%mod;
}
inline int qpow(int x , int y = mod - 2) {
	int res = 1;
	for(; y ; y >>= 1 , x = 1ll * x * x % mod)
		if(y & 1) res = 1ll * res * x % mod;
	return res; 
} 

int64 val[10] , mul[10] , imul[10] , pre[10] , suf[10];
void init() {
    nn = n % mod;
    for(int i = 1 ; i <= 8 ; ++i) {
        mul[i] = qpow(i);
        imul[i] = qpow(mod - i);
    }
    inv2 = mul[2] , inv3 = mul[3] , inv6 = mul[6];
    for(int i = 2 ; i <= 8 ; ++i) {
        mul[i] = mul[i] * mul[i - 1] % mod;
        imul[i] = imul[i] * imul[i - 1] % mod;
    }
}

int64 lglr(int64 y) {
    if(y <= 8) return val[y];
    for(int i = 1 ; i <= 8 ; ++i) pre[i] = suf[i] = y - i;
    for(int i = 2 ; i <= 8 ; ++i) pre[i] = pre[i - 1] * pre[i] % mod;
    for(int i = 7 ; i >= 1 ; --i) suf[i] = suf[i + 1] * suf[i] % mod;

    int64 ans = 0;
    for(int i = 1 ; i <= 8 ; ++i) {
        int64 b = val[i];
        if(i != 1) b = b * mul[i - 1] % mod * pre[i - 1] % mod;
        if(i != 8) b = b * imul[8 - i] % mod * suf[i + 1] % mod;
        ans = (ans + b) % mod;
    }
    return ans;
}

int main() {
    cin >> n;
    init();

    for(int64 x = 0 ; x*x <= n ; ++x) {
        int64 t = sqrt(n - x*x) , add = calc(x*x%mod);
        
        for(int i = 1 ; i <= 8 ; ++i)
            val[i] = (val[i - 1] + calc((x*x + i*i)%mod)) % mod;
        add = (add + 2*lglr(t)) % mod;

        if(x == 0) ans = (ans + add) % mod;
        else ans = (ans + 2*add) % mod;
    }

    cout << ans << endl;
}
```

---

## 作者：noone___ (赞：7)

题解的 $LaTeX$ 好像炸掉了，可以考虑点右上角或者[戳这里查看](https://noone40404.github.io/2021/10/08/CF933D%20A%20Creative%20Cutout/)。

上面的 $\text{GreenDay}$ 学长在模拟赛中出了这道题，并把数据范围加到了 $n\leq 10^{14}$ 。

与学长的式子相似，仍记 $a=x^2+y^2$ ，点 $(x,y)$ 最早被半径为 $\sqrt a$ 的第 $a$ 个圆包含。

枚举每个点被包含圆的编号 $\times$ 在 $n$ 个圆中的出现次数，即能推出上面的式子。

$$\frac{1}{2}(1+n)(n+a)(n-a+1)-\frac{1}{6}n(n+1)(2n+1)+\frac{1}{6}a(a-1)(2a-1)$$

但由于插值法常数过大，考虑继续将式子化简。

将 $a=x^2+y^2$ 代入并以 $y$ 为主元，能得到：

$$\begin{aligned}
原式
&=\frac{1+n}{2}(x^2+y^2+n)(n-x^2-y^2+1) \\
&\qquad+\frac{1}{6}n(n+1)(2n+1) \\
&\qquad+(\frac{1}{6}x^4+\frac{1}{6}x^2y^2+\frac{1}{6}x^2y^2+\frac{1}{6}y^4-\frac{1}{6}x^2-\frac{1}{6}y^2)\times(2x^2-2y^2-1) \\
&=\frac{1}{3} y^6 \\
&\qquad+(x^2-1-\frac{1}{2}n) y^4 \\
&\qquad+\left(\frac{1}{2}(1+n)(-2x^2+1)+x^4-x^2+\frac{1}{6} \right) y^2 \\
&\qquad+\left(\frac{1}{2}(1+n)(n+x^2)(n-xx^2+1)-\frac{1}{6}(n)(n+1)(n+2)+\frac{1}{6}x^2(x^2-1)(2x^2-1) \right) \\
\end{aligned}$$

该式的结果是点 $(x,y)$ 对答案的贡献，但还可以更加简化：在 $O(\sqrt n)$ 的时间内枚举正半轴上的每个 $x$ ，有 $max_y=\sqrt{n-x^2}$ 。

对于每个 $x$ ，预处理所有的 $y$ 的六次方，四次方，二次方之和，$O(1)$ 求满足 $x^2+y^2\leq n$ 的所有 $y$ ，即，所有满足条件的 $(x,*)$ 点对答案的贡献和。

![看个图理解一下](https://cdn.luogu.com.cn/upload/image_hosting/o3sz8u0e.png)

以 $x=1$ 为例，红线部分就是所求的和。

为了运算方便，实际上代码中求的是：

$$\begin{aligned}
&2\times \frac{1}{3} y^6 \\
&+2\times (x^2-1-\frac{1}{2}n) y^4 \\
&+2\times \left(\frac{1}{2}(1+n)(-2x^2+1)+x^4-x^2+\frac{1}{6} \right) y^2 \\
&+(2\times max_y+1)\times \left(\frac{1}{2}(1+n)(n+x^2)(n-xx^2+1)-\frac{1}{6}(n)(n+1)(n+2)+\frac{1}{6}x^2(x^2-1)(2x^2-1) \right) \\
\end{aligned}$$

也就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/jc9rqc98.png)

$y$ 的部分 $\times 2$ 是为了加上负半轴的贡献，常数项 $\times (2\times max_y+1)$ 中，$+1$ 是绿色点的部分，即在 $x$ 轴上时的情况。

最终统计答案时，再用：


```cpp
ans+=(!x) ? added : 2*added;
```

来处理 $x$ 的正负半轴情况以计算整个圆的情况。

代码复杂度为 $O(\sqrt{n})$ ，其瓶颈在于取模(确信)，若取模过于频繁就会从 $900ms$ 掉到 $4s$ 。

~~然后就可以跑到cf的rk1惹。~~

```cpp
#include <bits/stdc++.h>
#define rei register int
#define ll long long
using namespace std;

const int mod=1e9+7;
const int inv2=500000004,inv3=333333336,inv6=166666668;
ll n,mod_n,ans;

int main(){
	scanf("%lld",&n);
	mod_n=n%mod;
	for(ll x=(ll) sqrt(n+0.1),i=1,sum2=0,sum4=0,sum6=0;~x;--x) {
		ll t=sqrt(n-x*x),x2=x*x%mod;
		for(;i<=t;++i){
			ll pow_2=i*i%mod;
			ll pow_4=pow_2*pow_2%mod;
			sum2=(sum2+pow_2)%mod;
			sum4=(sum4+pow_4)%mod;
			sum6=(sum6+pow_2*pow_4)%mod;
		}
		ll added=((ll)2*inv3*sum6%mod
                    +(2*x2-2-mod_n+2*mod)%mod *sum4%mod
                    +( (1+mod_n)*((mod-2)*x%mod*x%mod+1)%mod + 2*x2*x2%mod-2*x2+inv3+2*mod )%mod *sum2%mod
                    +   (inv2*(1+mod_n)%mod*(mod_n+x2)%mod*(mod_n-x2+mod+1)%mod
                        -inv6*mod_n%mod*(mod_n+1)%mod*(2*mod_n+1)%mod
                        +inv6*(x2-1)%mod*x2%mod*(2*x2-1)%mod
                        +mod
                        )%mod*(2*t+1)%mod
                )%mod;
        ans+=(!x) ? added : 2*added;
	}
	printf("%lld\n",ans%mod);
    getchar(),getchar();
    return 0;
}

```

---

## 作者：qnqfff (赞：2)

不会拉插只能暴推式子，硬控 $3$ 个小时。

### 思路

考虑枚举整数点计算答案，则一个点 $(i,j)$ 的答案为 $\sum\limits_{x=i^2+j^2}^{n}x(n-x+1)$，拆一下 $\sum\limits_{x=i^2+j^2}^{n}(n+1)x-x^2$，前面是等差数列，后面是平方和，令 $x=i^2+j^2$，所以原式等于 $\dfrac{(n+1)(n+x)(n-x+1)}{2}-\dfrac{n(n+1)(2n+1)-(x-1)x(2x-1)}{6}$，痛苦的来了，通分爆拆 $n^3+3n^2+2n-3nx^2+3nx+2x^3-6x^2+4x$，带入 $x=i^2+j^2$，$n^3+3n^2+2n-3ni^4-6ni^2j^2-3nj^4+3ni^2+3nj^2+2i^6+6i^4j^2+6i^2j^4+2j^6-6i^4-12i^2j^2-6j^4+4i^2+4j^2$，这太长了，分成分别带 $j^0,j^2,j^4,j^6$ 的，设 $A_i=n^3+3n^2+2n-3ni^4+3ni^2+2i^6-6i^4+4i^2,B_i=-6ni^2+3n+6i^4-12i^2+4,C_i=-3n+6i^2-6,D_i=2$，则原式等于 $A_i+B_ij^2+C_ij^4+D_ij^6$，考虑怎么算呢，因为 $j\in[-\sqrt{n-i^2},\sqrt{n-i^2}]$，所以 $A,B,C,D$ 可以通过分别预处理 $j$ 的 $2,4,6$ 次方和计算，具体的，设 $pw2_n=\sum\limits_{i=1}^{n}i^2,pw4_n=\sum\limits_{i=1}^{n}i^4,pw6_n=\sum\limits_{i=1}^{n}i^6$，设 $j$ 为 $\sqrt{n-i^2}$ 则最后的答案为 $\sum\limits_{i=-\sqrt{n}}^{\sqrt{n}}A_i(2j+1)+B_i2pw2_j+C_i2pw4_j+D_i2pw6_j$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod=1e9+7,i2=5e8+4,i6=i2/3;
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int T,n,pw2[1000010],pw4[1000010],pw6[1000010];
void solve(){
	n=read();int res=0;
	for(int i=-sqrt(n);i<=sqrt(n);i++){
		int lim=sqrt(n-i*i);
		int A=((n%mod)*(n%mod)%mod*(n%mod)%mod+3*(n%mod)%mod*(n%mod)%mod+2*(n%mod)%mod-3*(n%mod)%mod*i%mod*i%mod*i%mod*i%mod+3*(n%mod)%mod*i%mod*i%mod+2*i%mod*i%mod*i%mod*i%mod*i%mod*i%mod-6*i%mod*i%mod*i%mod*i%mod+4*i%mod*i%mod+2*mod)%mod*(2*lim+1)%mod;
		int B=(3*(n%mod)%mod-6*(n%mod)%mod*i%mod*i%mod+6*i%mod*i%mod*i%mod*i%mod-12*i%mod*i%mod+4+2*mod)%mod*2%mod*pw2[lim]%mod;
		int C=(6*i%mod*i%mod-3*(n%mod)%mod-6+2*mod)%mod*2%mod*pw4[lim];
		int D=4*pw6[lim]%mod;
		(res+=(A+B+C+D)%mod*i6%mod)%=mod;
	}cout<<res<<'\n';
}
signed main(){
	pw2[0]=pw4[0]=pw6[0]=0;for(int i=1;i<=1e6;i++) pw2[i]=(pw2[i-1]+i*i%mod)%mod,pw4[i]=(pw4[i-1]+i*i%mod*i%mod*i%mod)%mod,pw6[i]=(pw6[i-1]+i*i%mod*i%mod*i%mod*i%mod*i%mod)%mod;
	T=1;while(T--) solve();
	return 0;
}
```

---

## 作者：Reunite (赞：1)

### 柿子题。
---
## 一

不妨转化一下，先考虑枚举平面点 $(x,y)$，使得 $x^2+y^2 \le n$，现在我们来考虑这个点对答案的贡献。显然为：
$$\sum_{i= x^2+y^2 }^{n} i\cdot(n-i+1)$$

为方便推导，令 $a=x^2+y^2$。则上式可化为：
$$\frac{(n+1)(a+n)(n+1-a)}{2}+ \frac{(a-1)a(2a-1)-n(n+1)(2n+1)}{6}$$

不妨通分，让分母在最后除去，展开得：
$$n^3+3n^2+2n+2a^3-3a^2n-6a^2+3an+4a$$

令 $sn=n^3+3n^2+2n$。然而这样我们只能做到 $O(n)$ 的，由于 $a$ 的参与到了式子中，这个方法是没有前途的。现在考虑把 $a$ 再代换回去。
$$sn+3i^2n+3nj^2-3i^4n-6i^2nj^2-3j^4n+2i^6+6i^4j^2+6i^2j^4+2j^6-6i^4-12i^2j^2-6j^4+4i^2+4j^2$$

尝试枚举一个 $i$，这是根号级别的，提取出无关项。令 $x=\lfloor \sqrt{n-i^2} \rfloor$，注意到 $j$ 的取值范围是 $[-x,x]$ 的连续变化区间，则上式可化为：

$$(sn+3i^2n-3i^4n+2i^6-6i^4+4i^2)\cdot(2x+1)+2j^6+(6i^2-6-3n)j^4+(3n-6i^2n+6i^4-12i^2+4)j^2$$

前面的部分和 $j$ 无关，直接算，后面的部分我们发现可以分别拆成二次，四次，六次自然幂和的形式，那么就可以做了。剩下的看代码吧。

- 值得注意的是，要多取模，我因为 $n \sqrt{n}$ 会爆卡了很久。

---
## 二

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;

ll n,mod;

inline ll calc(ll x,ll k){
	ll tmp=1;
	while(k){
		if(k&1) tmp=tmp*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return tmp;
}

int main(){
	// scanf("%lld%lld",&n,&mod);
	scanf("%lld",&n);
	mod=1000000007;
	ll s=0;
	ll inv3=calc(3,mod-2);
	ll inv6=calc(6,mod-2);
	ll inv15=calc(15,mod-2);
	ll inv21=calc(21,mod-2);
	ll sq=(ll) sqrt(n);
	ll sn=(n%mod*(n%mod)%mod*(n%mod)%mod+3*n%mod*(n%mod)%mod+2*(n%mod)%mod)%mod;
	for(ll i=-sq;i<=sq;i++){
		ll x=(ll) sqrt(n-i*i);
		ll cnt=(2*x+1)%mod;
		s=(s+(((sn+3*i%mod*i%mod*(n%mod)%mod-3*i%mod*i%mod*i%mod*i%mod*(n%mod)%mod+2*i%mod*i%mod*i%mod*i%mod*i%mod*i%mod-6*i%mod*i%mod*i%mod*i%mod+4*i%mod*i%mod)%mod+mod)%mod)*cnt%mod+mod)%mod;
		ll j2=x%mod*(x+1)%mod*(2*x+1)%mod*inv3%mod;
		s=(s+j2%mod*(((3*n%mod-6*i%mod*i%mod*(n%mod)%mod+6*i%mod*i%mod*i%mod*i%mod-12*i%mod*i%mod+4)%mod+mod)%mod))%mod;
		ll j4=(x%mod*(x+1)%mod*(2*x+1)%mod*((3*x*x%mod+3*x-1)%mod+mod)%mod)*inv15%mod;
		s=(s+j4%mod*(((6*i%mod*i%mod-3*n%mod-6)%mod+mod)%mod))%mod;
		ll j6=(x%mod*(x+1)%mod*(2*x+1)%mod*(((3*x%mod*x%mod*x%mod*x%mod+6*x%mod*x%mod*x%mod-3*x%mod+1)%mod+mod)%mod))%mod*inv21%mod;
		s=(s+2*j6%mod)%mod;
	}
	printf("%lld\n",(s%mod+mod)%mod*inv6%mod);
	
	return 0;
}

```

---

