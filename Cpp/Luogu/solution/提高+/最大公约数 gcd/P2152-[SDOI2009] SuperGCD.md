# [SDOI2009] SuperGCD

## 题目描述

Sheng bill 有着惊人的心算能力，甚至能用大脑计算出两个巨大的数的最大公约数！因此他经常和别人比赛计算最大公约数。有一天Sheng bill很嚣张地找到了你，并要求和你比赛，但是输给 Sheng bill 岂不是很丢脸！所以你决定写一个程序来教训他。

## 说明/提示

#### 数据规模与约定
- 对于 $20\%$ 的数据，有 $0<a,b\le 10^{18}$。
- 对于 $100\%$ 的数据，有 $0<a,b\le 10^{10000}$。

## 样例 #1

### 输入

```
12
54```

### 输出

```
6```

# 题解

## 作者：Log_x (赞：58)

楼上一群神犇……我就解释下原理吧

对于 $a,b$ 的 $GCD(a, b)$ 有：

[1]. 若 $a$ 为奇数，$b$ 为偶数，$GCD(a, b) = GCD(a, b / 2)$

表示 $b$ 存在2这个因子而 $a$ 不存在，则将 $b$ 除以2,，不考虑因子2；

[2]. 若 $a$ 为偶数，$b$ 为奇数，$GCD(a, b) = GCD(a / 2, b)$

表示 $a$ 存在2这个因子而 $b$ 不存在，则将 $a$ 除以2，不考虑因子2；

[3]. 若 $a$ 为偶数，$b$ 为偶数，$GCD(a, b) = 2GCD(a / 2, b / 2)$

表示 $a, b$ 都存在2这个因子，则 $GCD(a, b)$ 也存在因子2，则将当前答案乘以2，$a, b$ 都除以2；

[4]. 若 $a$ 为奇数，$b$ 为奇数，$GCD(a, b) = GCD(a - b, b) (a > b)$

即**辗转相减法（更相减损术）**，实际上可以看做辗转相除法的变形（因为减到不能再减实际上就是取余）。


最后顺便附上**辗转相除法**的证明：

（摘自[http://blog.sina.com.cn/s/blog\_6938cd0501010pj1.html](http://blog.sina.com.cn/s/blog\_6938cd0501010pj1.html)）

设两数为$a,b(a>b)$，求它们最大公约数的步骤如下：用 $b$ 除 $a$ ，得 $a = bq + r(0 \le r < b)$（ $q$ 是这个除法的商）。若 $r = 0$ ,则 $b$ 是$a$ 和 $b$ 的最大公约数。若 $r \ne 0$，则继续考虑。

首先，应该明白的一点是任何 $a$ 和 $b$ 的公约数都是 $r$ 的公约数。要想证明这一点，就要考虑把 $r$ 写成 $r = a - bq$。现在，如果 $a$ 和 $b$ 有一个公约数 $d$，而且设 $a = xd , b = yd$， 那么 $r = xd - ydq = (x - yq)d$。因为这个式子中，所有的数（包括 $x - yq$ )都为整数，所以 $r$ 可以被 $d$ 整除。

对于所有的 $d$ 的值，这都是正确的；所以 $a$ 和 $b$ 的最大公约数也是 $b$ 和 $r$  的最大公约数。因此我们可以继续对 $b$ 和 $r$ 进行上述取余的运算。这个过程在有限的重复后，可以最终得到 $r = 0$ 的结果，我们也就得到了 $a$ 和 $b$ 的最大公约数。


---

## 作者：阮行止 (赞：51)

# 辟谣

本题使用更相减损术可以通过，但是请注意：更相减损术的复杂度是$O(n)$，其中$n$为$A,B$中较大的那个一个。

我们给一个例子：$A=10^{10000},B=1$.此时更相减损术会挂掉。


更相减损术的原理是：$\gcd(a,b)=\gcd(a,a-b)$.  
辗转相除法的原理为GCD递归定理：$\gcd(a,b)=\gcd(b,a\%b)$.

容易看出，两个定理是等价的。而辗转相除法由于**以取模代替多次减法**，复杂度为$O(\log n)$.

这个复杂度有一个很美妙的证明。

- 情况一：$a<b$.此时GCD递归定理完成$a,b$的交换，转为情况二。  
- 情况二：$a\geqslant b$.我们注意到：**一个数模比自己小的数，至少减少一半。**故$a$至少减少一半。

情况一的出现次数不会高于情况二的出现次数；而情况二的出现次数至多为$O(\log n)$.自此完成复杂度证明。

事实上，辗转相除法面临的最坏情况是斐波那契数列的相邻两项。读者可以想一想这是为什么。



最后，请各位老老实实地写辗转相除法。**除非数据有特殊性质，否则不要使用更相减损术来求gcd.**




---

## 作者：parallet (赞：19)

本题的恶搞题解到此为止。

为防止新人受到误导，不要再使用 python 蒙混过关。

以前的保留不会删除，但请不要再提交错解。

---

辗转相减的话，若 $a=1,b=10^9$，那么计算 $\gcd$ 也就达到了 $10^9$ 级别。

考虑如何优化这个过程。

我们发现，如果 $a,b$ 是一奇一偶，那么 $2$ 这个因子不会对 $\gcd$ 产生贡献，那么完全可以把偶数除以二，去除 $2$ 这个因子。

如果 $a,b$ 均为偶数，那么 $2$ 这个因子显然会产生贡献，我们把答案乘 $2$，然后 $a,b$ 均把 $2$ 这个因子除掉。

如果 $a,b$ 均为奇数，我们没有别的做法，采用辗转相减。

复杂度也很好证明，每次辗转相减后必定出现一个偶数，偶数的情况每次除以 $2$，最多 $\log $ 次，所以复杂度是 $\log n$ 级别的。

这样我们的大整数类型只需要实现高精减，高精除以 2，高精乘 $2$。

细节方面，不要写递归的形式，容易 $\text{MLE}$；不必要的判断尽量不加，这个说起来很蛋疼，我一个 $\text{TLE}$ 的代码中的一部分：

```cpp
for(register int i=len;i>=1;--i)
	{
		if(x[i]&1)
		{
			int now=((num*10+x[i])>>1)<<1;
			ans[i]=(num*10+x[i])>>1;
			num=(num*10+x[i])-now;
		}
		else if(x[i]%2==0)
		{
			ans[i]=(num*10+x[i])>>1;
			num=0;
		}
	}
```

只需要将 `x[i]%2==0` 的判断删去，就可以过。很牛逼。

放一下代码，间断地写+调用了几个周的样子（

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN(1e5+10);
int n,m,k,a[MAXN],b[MAXN],G[MAXN],sol[MAXN];
char s1[MAXN],s2[MAXN];
inline int Min(int x,int y){return x<y?x:y;}
inline bool check()
{
	if((n==1&&a[1]==0)||(m==1&&b[1]==0)) return false;
	return true;
}
inline void print(int*x,int len)
{
	for(register int i=len;i>=1;--i) putchar(x[i]^48);
	return;
}
inline void mul2(int*x,int&len)
{
	bool flag(false);
	for(register int i=1;i<=len;++i)
	{
		x[i]<<=1;
		if(flag) x[i]|=1;
		if(x[i]>=10) x[i]-=10,flag=true;
		else flag=false;
	}
	if(flag)
	{
		++len;
		x[len]=1;
	}
	return;
}
inline void div2(int*x,int&len)
{
	int num(0);
	int ans[MAXN];
	for(register int i=len;i>=1;--i)
	{
		if(x[i]&1)
		{
			int now=((num*10+x[i])>>1)<<1;
			ans[i]=(num*10+x[i])>>1;
			num=(num*10+x[i])-now;
		}
		else
		{
			ans[i]=(num*10+x[i])>>1;
			num=0;
		}
	}
	for(register int i=len;i>=1;--i)
		if(ans[i]==0) --len;
		else break;
	if(len==0) ++len;
	for(register int i=1;i<=len;++i)
		x[i]=ans[i];
	return;
}
inline bool cmp()
{
	if(n<m) return false;
	if(n>m) return true;
	for(register int i=n;i>=1;--i)
		if(a[i]<b[i]) return false;
		else if(a[i]>b[i]) return true;
	return true;
}
inline void solve(int*x,int&l1,int*y,int l2)
{
	for(register int i=1;i<=l2;++i)
	{
		x[i]-=y[i];
		if(x[i]<0) --x[i+1],x[i]+=10;
	}
	if(l1==1) return;
	while(l1>0&&x[l1]==0) --l1;
	if(l1==0) l1=1;
	return;
}
inline void change(int*x,int&l1,int*y,int l2)
{
	l1=l2;
	for(register int i=1;i<=l1;++i) x[i]=y[i];
	return;
}
int len,cnt;
int main()
{
	scanf("%s%s",s1+1,s2+1);
	n=strlen(s1+1),m=strlen(s2+1);
	G[++k]=1;
	for(register int i=1,j=n;i<=n;++i,--j) a[j]=s1[i]-'0';
	for(register int i=1,j=m;i<=m;++i,--j) b[j]=s2[i]-'0';
	while(check())
	{
		if(a[1]%2==0&&b[1]%2==0) div2(a,n),div2(b,m),++cnt;
		else if(a[1]%2==0&&(b[1]&1)) div2(a,n);
		else if((a[1]&1)&&b[1]%2==0) div2(b,m);
		else
		{
			if(!cmp()) solve(b,m,a,n);
			else solve(a,n,b,m);
		}
	}
	if(cmp()) change(sol,len,a,n);
	else change(sol,len,b,m);
	for(register int i=1;i<=cnt;i++) mul2(sol,len);
	print(sol,len);
	return 0; 
}
```



---

## 作者：ADay (赞：13)

## Solutionn
$\texttt{Ruby}$ 的运算也是自带高精的，并且据说内部是用 $\text{FFT}$ 实现的，那么直接运用辗转相除法求 $\gcd$ 就好。  

具体地，$\texttt{Ruby}$ 中如果数大于 $2^{62}-1$ 则会转化成 $\text{Bignum}$ 类型，使用特殊运算。  

至于为什么用了 $\text{FFT}$ 还比 $\texttt{python}$ 慢呢？是因为本题位数较小而常数大，会慢于正常高精。
## Code
```python
a,b=gets.to_i,gets.to_i
while b>0
    a,b=b,a%b
end
print a
```

---

## 作者：λᴉʍ (赞：13)

上次代码发错了orz


这题还是可以用py水的.


人生苦短我用python


应该是测试数据有坑(比如多了回车空格什么的),只需要一直读就行了,读完之后直接gcd


涉及到的内容:map,list,切片,try..except


233333
```python
s=[]
while True:
    try:
        Str=input()
        while Str.find('  ')==0:Str=Str.replace('  ',' ')
        if Str==' ' or Str=='':continue
        if Str[0]==' ':Str=Str[1:len(Str)]
        if Str[-1]==' ':Str=Str[0:len(Str)-1]
        if Str.count(' ')==0:s.append(Str)
        else:s+=Str.split(' ')
    except:break
a,b=map(int,s)
while(b!=0):a,b=b,a%b
print(a)
```

---

## 作者：hongzy (赞：8)

**题意**

求$\gcd(a, b)$，其中$a,b\leq10^{10000}$

**题解**

使用$\text{Stein}$算法，其原理是不断筛除因子$2$然后使用更相减损法

如果不筛$2$因子的话复杂度是线性的，比如$a=1,b=10^{10000}$

再证明下更相减损术，即$\gcd(a,b)=gcd(a-b,b)$：

假设$d=\gcd(a,b)$，则$a=pd,b=qd$

根据定义可知$\gcd(p,q)=1$

因此$px+qy=1$存在解$x,y$

此时$a-b=pd-q-d=(p-q)d,b=qd$

$(p-q)x+q(x+y)=px+qy=1$

得到$\gcd(p-q,q)=1$，根据定义得到$d=\gcd(a-b,b)$

注意一下高精要压位，不然常数巨大

```cpp
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int base = 1e9;
const int N = 1e4 + 10;

struct Int {
    int len, n[N / 9 + 10];
    Int() {}
    Int(char * s) {
        int x = strlen(s);
        len = x / 9 + (x % 9 ? 1 : 0);
        int p = x - 1;
        for(int i = 1; i <= len; i ++) {
            n[i] = 0;
            for(int j = min(p, 8); j >= 0; j --)
                n[i] = n[i] * 10 + (s[p - j] & 15);
            p -= 9;
        }
    }
    bool zero() { return len == 1 && n[1] == 0; }
    bool judge() { return !zero() && 0 == (n[1] & 1); }
    bool operator < (const Int &b) const {
        if(len != b.len) return len < b.len;
        for(int i = len; i >= 1; i --)
            if(n[i] != b.n[i]) return n[i] < b.n[i];
        return 0;
    }
    bool operator -= (const Int &b) {
        for(int i = 1; i <= len; i ++) {
            if(i <= b.len) {
                n[i] -= b.n[i];
                if(n[i] < 0) n[i + 1] --, n[i] += base;
            }
        }
        for(; !n[len] && len > 1; len --);
        return zero();
    }
    void div2() {
        for(int i = 1; i <= len; i ++) {
            if(n[i] & 1) n[i - 1] += base >> 1;
            n[i] >>= 1;
        }
        for(; !n[len] && len > 1; len --);
    }
    void operator <<= (const int &x) {
        for(int t = 1; t <= x; t ++) {
            n[len + 1] = 0;
            for(int i = len; i >= 1; i --) {
                n[i] <<= 1; n[i + 1] += n[i] / base; n[i] %= base;
            }
            if(n[len + 1]) len ++;
        }
        this -> print();
    }
    void print() {
        for(int i = len; i >= 1; i --)
            if(i == len) printf("%d", n[i]);
            else printf("%09d", n[i]);
        printf("\n");
    }
} x, y;

int main() {
    static char A[N], B[N];
    scanf("%s %s", A, B);
    x = Int(A), y = Int(B);
    if(x.zero()) return y.print(), 0;
    if(y.zero()) return x.print(), 0;
    int i = 0, j = 0;
    for(; x.judge(); i ++) x.div2();
    for(; y.judge(); j ++) y.div2();
    while(1) {
        if(!(x < y)) {
            if(x -= y) return y <<= min(i, j), 0;
            while(x.judge()) x.div2();
        } else {
            if(y -= x) return x <<= min(i, j), 0;
            while(y.judge()) y.div2();
        }
    }
    return 0;
}

```



---

## 作者：LJ07 (赞：7)

使用优化版的更相减损术。

$(a,b)=\left \{ \begin{matrix}(\frac{a}{2},\frac{b}{2})&2\mid a,2\mid b\\(\frac{a}{2},b)&2\mid a,2\nmid b\\(a,\frac{b}{2})&2\mid b,2\nmid a\\(b,a-b) &2\nmid a,2\nmid b\end{matrix}\right.(a\ge b)$。

不加上高精，复杂度为对数级别的。感性理解一下：前三种情况每次会将 $a$，$b$ 缩小 $\frac{1}{2}$，第四种情况会在下一步转化为第二或第三种情况。而一共只会缩小对数级别次。

本题高精要压位，否则会 TLE。

[code](https://www.luogu.com.cn/paste/flnu2r75)

---

## 作者：aiyougege (赞：6)

### [SDOI2009]SuperGCD
#### Solution
　　其实如果不需要高精度是很好做的, 就是需要注意递归会爆栈(递归层数太多), 需要用循环模拟.~~这个题提醒我们尽量少写函数和递归~~

　　因为c++写高精度实在太鬼畜, 所以就用Python水一下.
#### Code
递归版, 只有40, 和c++一样

```
def gcd(a,b):
    if b==0:
    	return a
    else:
        return gcd(b,a%b)

a=int(input())
b=int(input())
print(gcd(a,b))
```

循环版, 100分
Python 语法比较神奇
$$a,b,c,\cdots =s_1,s_2,s_3,\cdots $$
将$s_1,s_2,s_3,\cdots $的值分别赋给$a,b,c,\cdots$


```
a=int(input())
b=int(input())

while b:
    a,b=b,a%b
    
print(a)
```

---

## 作者：诸君拔剑吧 (赞：3)

 看到大家对这道题爱的如此深沉
 
 我急（sang）中（xin）生（bing）智（kuang）地想到了一个黑科技，那就是 拥有奇（gua）葩（bi）函（zuo）数（cheng）的 java.math.BigInteger（Caster Merlin）！
 
 代码大家应该都能看懂。。。嗯，，gcd直接返回最大公约数。。。
 

------------
 
 ```java
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        BigInteger a = new BigInteger(in.next());
        BigInteger b = new BigInteger(in.next());
        System.out.println(a.gcd(b));
    }
}

```

------------


---

## 作者：cmk666 (赞：3)

[题目链接](/problem/P2152)

题意：求 $\gcd(a,b)$，其中 $a,b\le10^{10000}$。

在 OI 中，常见的、较为高效的求 $\gcd$ 的方式无非就 $3$ 种：

$1)$ **更相减损术：**

出自《九章算术》。

原理：当 $a>b$ 时，$\gcd(a,b)=\gcd(a,a-b)$。

证明：

> 设 $c$ 为 $a,b$ 的公约数，则设 $a=pc,b=qc$，其中 $p,q$ 为整数。
>
> 那么有 $a-b=(p-q)c$，即 $c$ 是 $a-b$ 的约数。
>
> 所以 $c$ 是 $a,a-b$ 的公约数。也就是说，$a,b$ 的公约数集合和 $a,a-b$ 的公约数集合是一样的。那么其中最大的那个也是一样的。
>
> 因此 $\gcd(a,b)=\gcd(a,a-b)$。得证。

代码也很好写（无高精）：
```cpp
inline int gcd(int a, int b)
{
	if ( a < b ) swap(a, b);
	if ( !b ) return a;     // gcd(a, 0) = a
	return gcd(a, a - b);
}
```
时间复杂度最坏是 $O(n)$ 的，例如当 $a$ 很大，$b=1$ 时需要迭代 $a-1$ 轮。显然无法通过本题。

$2)$ **欧几里得算法：**

原理：$\gcd(a,b)=\gcd(b,a\bmod b)$。

证明：

> 设 $c$ 为 $a,b$ 的公约数，则设 $a=pc,b=qc$，其中 $p,q$ 为整数。
>
> 再记 $a=kb+r$，其中 $k=\left\lfloor\dfrac ab\right\rfloor,r=a\bmod b$，则 $pc=kqc+r$，转化得 $r=(p-kq)c$，即 $c$ 是 $a\bmod b$ 的约数。
>
> 所以 $c$ 是 $b,a\bmod b$ 的公约数。也就是说，$a,b$ 的公约数集合和 $b,a\bmod b$ 的公约数集合是一样的。那么其中最大的那个也是一样的。
>
> 因此 $\gcd(a,b)=\gcd(b,a\bmod b)$。得证。

跟上面的很像对吧。

事实上，取模可以看成连续减很多次，因此二者近乎一样。

代码也同样很好写（无高精）：
```cpp
inline int gcd(int a, int b)
{
	if ( !b ) return a;     // gcd(a, 0) = a
	return gcd(b, a % b);
}
```
时间复杂度是 $O(\log n)$ 的，因为每次取模都会让大的数至少减半。最坏情况下是求斐波那契数列的相邻两项的 $\gcd$，达到最大复杂度。

理论上这题可以使用，但写高精除高精和高精对高精取余两个操作过于繁琐了。那有没有更好的方法呢？

$3)$ **更相减损术，但“可半者半之”：**

“可半者半之”这句话是在《九章算术》中“更相减损术”的第一句。

原理：当 $a>b$ 时，$\gcd(a,b)=\begin{cases}2\gcd(\dfrac a2,\dfrac b2)&2\mid a,2\mid b&(1)\\\gcd(\dfrac a2,b)&2\mid a,2\nmid b&(2)\\\gcd(a,\dfrac b2)&2\nmid a,2\mid b&(3)\\\gcd(a,a-b)&2\nmid a,2\nmid b&(4)\end{cases}$。

证明：

> $(1)$：若 $a,b$ 都有 $2$ 因子，那么它们的 $\gcd$ 必然含有 $2$ 因子。将 $2$ 除去各自计算即可；
>
> $(2),(3)$：若 $a,b$ 仅有一个有 $2$ 因子，则这个 $2$ 因子一定不会产生任何贡献，直接除掉即可；
>
> $(4)$ 的证明见上。

代码略微繁琐一点（无高精）：
```cpp
inline int gcd(int a, int b)
{
	if ( a < b ) swap(a, b);
	if ( !b ) return a;     // gcd(a, 0) = a
	if ( ( a & 1 ) && ( b & 1 ) ) return gcd(a, a - b);
	if ( a & 1 ) return gcd(a, b >> 1);
	if ( b & 1 ) return gcd(a >> 1, b);
	return gcd(a >> 1, b >> 1) << 1;
}
```
因为大多数操作都是除以 $2$ 和对 $2$ 取模，可以使用位运算，高精写起来也方便一些。

因为 $(1),(2),(3)$ 情况都会使一个数 $\div2$，即让规模变成原来的一半。$(4)$ 操作当且仅当二者都为奇数的时候才会触发，但二者相减后又会出现偶数，又可以 $\div2$。因此时间复杂度是 $O(\log n)$ 的。

简单加一手高精就行了。高精自己写，完整代码不贴。

---

## 作者：slothfulxtx (赞：2)

好吧，这道题用了一种很掉节操的方法进行查错

说一下这道题要注意的几个地方：

1.一定要用数位压缩

2.辗转相减

3.使用函数和过程注意局部变量与全局变量（ToT）

4.字符串读入比字符读入快


```delphi

program p2152;
type
  arr=array[0..2000]of longint;
var
  s:ansistring;
  i,t,two:longint;
    a,b:arr;
procedure div2(var a:arr);
var i:longint;
begin
  for i:=a[0] downto 1 do begin
      if a[i]mod 2=1 then inc(a[i-1],1000000);
      a[i]:=a[i]shr 1;
    end;
  for i:=a[0]downto 1 do
      if a[i]<>0 then break;
  a[0]:=i;
end;
procedure minus(var a:arr;b:arr);
var i:longint;
begin
  for i:=1 to b[0] do begin
      a[i]:=a[i]-b[i];
    if a[i]<0 then begin
      inc(a[i],1000000);
          dec(a[i+1]);
    end;
  end;
  for i:=a[0]downto 1 do
      if a[i]<>0 then break;a[0]:=i;
end;
function compare:integer;
var i:longint;
begin
  if a[0]>b[0] then exit(1);
    if a[0]<b[0] then exit(-1);
    for i:=a[0] downto 1 do begin
      if a[i]>b[i] then exit(1);
        if a[i]<b[i] then exit(-1);
    end;
    exit(0);
end;
procedure change(var a:arr);
var p,l,i,t:longint;
begin
  l:=length(s);
    p:=l div 6;
    if l mod 6<>0 then inc(p);
    fillchar(a,sizeof(a),0);
    for i:=l downto 1 do begin
      t:=ord(s[i])-ord('0');
        case (l-i)mod 6 of
          0:inc(a[(l-i)div 6+1],t);
          1:inc(a[(l-i)div 6+1],t*10);
          2:inc(a[(l-i)div 6+1],t*100);
            3:inc(a[(l-i)div 6+1],t*1000);
            4:inc(a[(l-i)div 6+1],t*10000);
            5:inc(a[(l-i)div 6+1],t*100000);
        end;
  end;
  a[0]:=p;
end;
procedure double;
var i,g:longint;
begin
  g:=0;
  for i:=1 to a[0] do begin
        a[i]:=a[i]*2+g;
    g:=a[i]div 1000000;
    a[i]:=a[i]mod 1000000;
  end;
    if g<>0 then begin inc(a[0]);a[a[0]]:=g;end;
end;
procedure print(a:arr);
var i:longint;
begin
  write(a[a[0]]);
    for i:=a[0]-1 downto 1 do begin
      if a[i]<100000 then write('0');
        if a[i]<10000 then write('0');
        if a[i]<1000 then write('0');
        if a[i]<100 then write('0');
        if a[i]<10 then write('0');
        write(a[i]);
  end;writeln;
end;
begin
    readln(s);
  change(a);
    readln(s);
    change(b);
    two:=0;
  while not(odd(a[1])or odd(b[1])) do begin
      div2(a);div2(b);inc(two);
  end;
    while true do begin
    while not odd(a[1]) do div2(a);
        while not odd(b[1]) do div2(b);
    t:=compare;
    if t=0 then break;
        if t=1 then minus(a,b) else minus(b,a);
    end;
  for i:=1 to two do double;
    print(a);
end.

```

---

## 作者：zesqwq (赞：2)

# P2152 [SDOI2009] SuperGCD 题解

~~阅读了一下题面，以为是一道大水题。结果发现，数据范围有点不对经。~~

[原题链接](https://www.luogu.com.cn/problem/P2152)

这个问题就是让我们求 $2$ 个大数的最大公约数，但是直接暴力是不行的，首先要解决的问题就是如何快速求 $2$ 个整数的公约数。

## 辗转相减法

辗转相减法的过程是这样的:

$$(a >= b) \gcd(a,b) = \begin{cases} a &b = 0 \\ \gcd(a - b, b) & b \not= 0\end {cases}$$

给出一个非常不严谨的证明：

假设：$A =ka,B=kb, a \bot b,a>=b$， 即 $\gcd(A,B)=k$。

那么 $\gcd(A-B,B) = \gcd((a-b)k,bk)$，又因为 $a \bot b$，所以 $a-b\bot b$，即 $\gcd(A,B)=\gcd(A-B,B)=k$。

但是我们发现这个东西跑的特别慢，比如说计算 $\gcd(x,1)$ 的时候就要进行整整 $x$ 次运算，比暴力还慢了。于是，我们就有而一个优化:

$$(a >= b) \gcd(a,b) = \begin{cases} a &b = 0 \\ \gcd(a/2,b/2) \times 2 & \text{a is even and b is even} \\ \gcd(a/2,b) & \text{a is even and b is odd} \\ \gcd(a,b/2) & \text{a is odd and b is even} \\ \gcd(a - b, b) & \text{otherwise} \end {cases}$$

其正确性是显然的，但是可以带来非常显著的优化：如果 $a$ 或 $b$ 是偶数，那么一次除以 $2$ 后其要计算的大小就会减半。如果都不是偶数，那么过了 $1$ 次检法就会出现偶数。所以，感性理解其时间复杂度为 $O(\log n)$ 的。

回到这道题目上，如果你要问为什么不用辗转相除法，原因就是要写高精度。高精度的取模是常数巨大的，但是上文提到的方法只需要涉及判断奇偶，乘 $2$，除以 $2$，以及相减，这些操作的常数较小，因此可以跑得较快。

另外提一句：用这种方法求最大公约数，可以凭借常数优势暴力通过 [快速GCD](https://www.luogu.com.cn/problem/P5435) 这个题目。

本题具体的实现可以参考代码。

$code$

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long P = 10000000000000000ll;
const int N = 700;
long long a[N], b[N];
char read_tmp[N << 4];
inline long long stol(char tmp[], int l, int r) {
    long long ans = 0, now = 1;
    for (int i = l; i <= r; i++) ans = ans + (tmp[i] ^ 48) * now, now *= 10ll;
    return ans;
}
inline void read(long long a[]) {
    scanf("%s", read_tmp + 1);
    int i, len = a[0] = strlen(read_tmp + 1);
    a[0] = a[0] + 15 >> 4;
    for (i = 1; i <= (len >> 1); i++) swap(read_tmp[i], read_tmp[len - i + 1]);
    for (i = 1; i + 15 <= len; i += 16) a[i + 15 >> 4] = stol(read_tmp, i, i + 15);
    if (i <= len)
        a[a[0]] = stol(read_tmp, i, len);
}
inline void print(long long a[]) {
    printf("%lld", a[a[0]]);
    for (int i = a[0] - 1; i >= 1; i--) printf("%016lld", a[i]);
}
inline void cpy(long long a[], long long b[]) { memcpy(b, a, N << 3); }
inline void clear(long long a[]) { memset(a, 0, N << 3); }
inline bool isEven(long long a[]) { return !(a[1] & 1); }
bool divtmp[N];
inline void div2(long long a[]) {
    memset(divtmp, 0, sizeof(divtmp));
    if (!a[0]) return;
    for (int i = a[0]; i; i--) divtmp[i - 1] = a[i] & 1, a[i] >>= 1;
    for (int i = a[0]; i; i--)
        if (divtmp[i]) a[i] += P >> 1;
    while (a[0] && !a[a[0]]) --a[0];
}
inline void mul2(long long a[]) {
    long long c = 0;
    for (int i = 1; i <= a[0] + 1ll; i++) a[i] = (a[i] << 1) + c, c = a[i] / P, a[i] %= P;
    while (a[a[0] + 1]) ++a[0];
}
inline int cmp(long long a[], long long b[]) {
    if (a[0] > b[0]) return 1;
    if (a[0] < b[0]) return -1;
    for (int i = a[0]; i; i--) {
        if (a[i] > b[i]) return 1;
        if (b[i] > a[i]) return -1;
    }
    return 0;
}
inline void subs(long long a[], long long b[], long long ans[]) {
    clear(ans);
    for (int i = 1; i <= a[0]; i++) {
        ans[i] += a[i] - b[i];
        if (ans[i] < 0) ans[i] += P, --ans[i + 1];
    }
    ans[0] = a[0];
    while (ans[0] && !ans[ans[0]]) --ans[0];
}
long long gcdTmp[N], ans[N];
inline void gcd(long long a[], long long b[]) {
    clear(ans);
    if (cmp(a, b) == -1) cpy(a, gcdTmp), cpy(b, a), cpy(gcdTmp, b);
    bool aa, bb;
    int cnt = 0;
    while (b[0]) {
        aa = isEven(a), bb = isEven(b);
        if (aa && bb)
            ++cnt, div2(a), div2(b);
        else if (!aa && bb)
            div2(b);
        else if (aa && !bb)
            div2(a);
        else
            subs(a, b, gcdTmp), cpy(gcdTmp, a);
        if (cmp(a, b) == -1) cpy(a, gcdTmp), cpy(b, a), cpy(gcdTmp, b);
    }
    cpy(a, ans);
    while (cnt--) mul2(ans);
}
int main() {
    read(a), read(b), gcd(a, b), print(ans);
    return 0;
}
```


---

## 作者：AirQwQ (赞：2)

Ruby 党的福利来了，Ruby 和 Python 一样，都是自带高精度。

所以依旧是[辗转相除法](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95/1647675fromtitle=%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4%E6%B3%95&fromid=4625352&fr=aladdin) $5$ 行搞定。


```ruby
x,y=gets.to_i,gets.to_i
while y!=0
    x,y=y,x%y
end
print x
```

---

## 作者：ddwqwq (赞：1)

这题太变态了，写了整整一天才AC。在此写下我的经验，顺便贴代码。

众所周知，最大公约数有两种算法，更相减损术和欧几里得算法（辗转相除法）。对于它们的时间复杂度，我只知道欧几里得算法是O(lg min(a,b)),更相减损法则不大清楚，但一般来说似乎是欧几里得算法更快（不确定）？不过本题中更相减损法更具优势，因为它只需高精加减和除二，都是O（lgN）速度，无需O(N^2)的乘除运算。但对于一些数据，如9999999999999999999999999和1，欧几里得算法还是快一些。所以，我们可以在lg a - lg b较大时采用欧几里得算法，之后转入更相减损法（我想破脑袋想出的优化，但这道题里似乎没什么效果）。

之后就是一些高精的细节了。高精都是用的竖式思想，容易理解（FFT之类的，本人太弱，实在不懂）。再有，重载运算符似乎不能引用套引用，会冒出一堆左值右值之类的令蒟蒻一头雾水的东西(VS是warning，洛谷是error)。就像这样：

```cpp
myint operator * (myint &b, int a);
myint operator % (myint &b, myint &a)
{
    myint t;
    int i = 0;

    while (!b.c[i])
        i++;
    for (; i < LEN; i++)
    {
        t = t * mod;//%套着*,都有&引用
        t = t + b.c[i];//VS的warning:1>main.cpp(119): note: 非常量引用只能绑定到左值
        if (cmp(a, t))
            t = t - a*search(t, a);
        else if (a == t)
            memset(t.c, 0, sizeof(t.c));
    }
    return t;
}
```
我不知如何解决这种问题，所以下面的代码都放弃了引用加速,大家可以研究下如何解决。以下AC代码（简直比平衡树都长了）

```cpp
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <cstring>
#include <time.h>

#define INF 2000000000//2 * 10^9
#define mod 1000000
#define mod_len 6
#define LEN 2000
#define max(a,b) ((a>b)?(a):(b))
#define min(a,b) ((a<b)?(a):(b))

struct myint;
int search(myint *a, myint *b);
bool cmp(myint *a, myint *b);
struct myint {
    long long c[LEN];
    myint()
    {
        memset(c, 0, sizeof(c));
    }
    myint operator + (myint &a)
    {
        myint ret;
        int i;
        for (i = 0; i < LEN; i++)
            ret.c[i] = c[i] + a.c[i];
        for (i = LEN - 1; i > 0; i--)
        {
            ret.c[i - 1] += ret.c[i] / mod;
            ret.c[i] %= mod;
        }
        return ret;
    }
    myint operator * (myint a)
    {
        myint ret;
        int i, j;
        for (i = LEN - 1; i > 0; i--)
            for (j = LEN - 1; j > LEN - 1 - i; j--)
                ret.c[j - LEN + 1 + i] += c[j] * a.c[i];
        for (i = LEN - 1; i >= 0; i--)
        {
            ret.c[i - 1] += ret.c[i] / mod;
            ret.c[i] %= mod;
        }
        return ret;
    }
    myint operator * (int a)
    {
        myint ret;
        int i;
        for (i = LEN - 1; i > 0; i--)
            ret.c[i] = c[i] * a;
        for (i = LEN - 1; i > 0; i--)
        {
            ret.c[i - 1] += ret.c[i] / mod;
            ret.c[i] %= mod;
        }
        return ret;
    }
    myint operator - (int a)
    {
        int i;
        myint ret;
        memcpy(ret.c, c, sizeof(c));

        ret.c[LEN - 1] -= a;
        for (i = LEN - 1; ret.c[i] < 0; i--)
        {
            ret.c[i] += mod;
            ret.c[i - 1] = ret.c[i - 1] - 1;
        }
        return ret;
    }
    myint operator + (int a)
    {
        int i;
        myint ret;
        memcpy(ret.c, c, sizeof(c));

        ret.c[LEN - 1] += a;
        for (i = LEN - 1; i > 0; i--)
        {
            if (ret.c[i] / mod < mod)
                break;
            ret.c[i - 1] += ret.c[i] / mod;
            ret.c[i] %= mod;
        }
        return ret;
    }
    myint operator - (myint a)
    {
        myint ret;
        int i;
        memcpy(ret.c, c, sizeof(c));

        for (i = LEN - 1; i > 0; i--)
            ret.c[i] = ret.c[i] - a.c[i];
        for (i = LEN - 1; i > 0; i--)
            if (ret.c[i] < 0)
            {
                ret.c[i - 1]--;
                ret.c[i] += mod;
            }
        return ret;
    }
    bool operator == (myint a)
    {
        int i;
        for (i = LEN - 1; i >= 0; i--)
            if (c[i] != a.c[i])
                return false;
        return true;
    }
    myint operator % (myint a)
    {
        myint t;
        int i = 0;

        while (!c[i])
            i++;
        for (; i < LEN; i++)
        {
            t = t * mod;
            t = t + c[i];
            if (cmp(&a, &t))//二分查找，复杂度似乎可以降到O(n*log n)
                t = t - a*search(&t, &a);
            else if (a == t)
                memset(t.c, 0, sizeof(t.c));
        }
        return t;
    }
    int len()
    {
        int i;
        for (i = 0; i < LEN; i++)
            if (c[i] != 0)
                break;
        return LEN - i;
    }
    void divide2()
    {
        long long i = 0, t = 0;

        while (c[i] == 0)
            i++;
        for (; i < LEN; i++)
        {
            t = t*mod;
            t += c[i];
            c[i] = t / 2;
            t %= 2;
        }
    }
    bool check()
    {
        if (c[LEN - 1] & 1)
            return false;
        return true;
    }
};
const myint zero;

bool cmp(myint *a, myint *b)
{
    int i;
    for (i = 0; i < LEN; i++)
        if (a->c[i] < b->c[i])
            return true;
        else if (a->c[i] > b->c[i])
            return false;
    return false;
}
int search(myint *a, myint *b)
{
    int l = 0;
    int r = mod;
    myint temp;
    while (l + 1 < r)
    {
        int mid = (l + r) / 2;
        temp = *b * mid;
        if (cmp(a, &temp))
            r = mid;
        else
            l = mid;
    }
    return l;
}

myint getmyint()
{
    int i, j, t;
    myint ret;
    char s[LEN * 10];

    scanf("%s", s);

    j = LEN - 1;
    for (i = strlen(s) - mod_len; i >= 0; i = i - mod_len)
    {
        t = atoi(s + i);
        ret.c[j--] = t;
        s[i] = 'a';
    }
    s[i + mod_len] = 0;
    t = atoi(s);
    ret.c[j--] = t;

    return ret;
}
void putmyint(myint a)
{
    int i;
    bool flag = false;
    for (i = 0; i < LEN; i++)
    {
        if (flag)
            printf("%06lld", a.c[i]);
        if (!flag && a.c[i] > 0)
        {
            flag = true;
            printf("%lld", a.c[i]);
        }
    }
    if (!flag)
        printf("0");
}

void swap(myint &a, myint &b)
{
    myint t;
    t = a;
    a = b;
    b = t;
}

myint gcd(myint a, myint b)
{
    myint cnt;
    if (cmp(&a, &b))
        swap(a, b);

    while (!(a == b))
    {
        if (a.check() && b.check())
        {
            a.divide2();
            b.divide2();
            cnt = cnt + 1;
        }
        else if (b.check())
            b.divide2();
        else if (a.check())
            a.divide2();
        else
            a = a - b;
        if (cmp(&a, &b))
            swap(a, b);
    }

    while (cmp((myint *)&zero, &cnt))
    {
        a = a * 2;
        cnt = cnt - 1;
    }

    return a;
}

myint gcd2(myint a, myint b)
{
    myint temp;

    if (cmp(&a, &b))
        swap(a, b);

    while (1)
    {
        if (b == zero)
            break;
        if (a.len() - b.len() < 5)
            return gcd(a, b);

        temp = a;
        a = b;
        b = temp%b;
    }
    return a;
}

int main()
{
    myint a, b;

    a = getmyint();
    b = getmyint();

    putmyint(gcd2(a,b));

//    system("pause");
    return 0;
}
```

---

