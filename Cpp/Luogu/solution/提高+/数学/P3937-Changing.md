# Changing

## 题目描述

有 $n$ 盏灯环形排列，顺时针依次标号为 $1\cdots n$。初始时刻为 $0$，初始时刻第 $i$ 盏灯的亮灭 $a_i$ 给定，$0$ 表示灭，$1$ 表示亮。下一时刻每盏灯的亮灭取决于当前时刻这盏灯与顺时针方向下一盏灯的亮灭。若两盏灯状态相同，则下一时刻该灯灭，否则该灯亮。


试求时刻 $t$ 第 $k$ 盏灯的状态。


## 说明/提示

- 对于 $25\%$ 的数据，有$1\leq t, k\leq n\leq 1000$。 
- 对于 $60\%$ 的数据，有$1\leq t, k\leq n\leq 10^5$。 
- 对于 $100\%$ 的数据，有$1\leq t, k\leq n\leq 3\times 10^6$。


## 样例 #1

### 输入

```
4 2 1
1 0 1 0```

### 输出

```
0```

# 题解

## 作者：Snakes (赞：18)

#### 算法一

我会随机！

由于我忘了设置多组数据，期望得分$0$至$100$。

#### 算法二

我会模拟！

复杂度$O(t^2)$，期望得分$60$。

但是很多人忘记题目给出的是环形……

#### 算法三

我会正解！

实际上是数学题，显然时刻$t$第$k$盏灯的状态为

$$\left(\sum_{i=0}^t C_t^ia_{(k+i-1) \bmod n+1}\right) \bmod 2$$

求和即可。复杂度$O(t)$，期望得分$100$。

#### 给证明？

实际上，这道题是这个问题的子问题。

#### 亮灯问题

　　有$n$盏灯环形排列，顺时针依次标号为$0..n-1$。初始时刻为$0$，所有灯的亮灭（我们称之为状态）*随机*。下一时刻每盏灯的亮灭取决于当前时刻这盏灯与顺时针方向下一盏灯的亮灭。若两盏灯状态相同，则下一时刻该灯灭，否则该灯亮。  
　　试求：当$n$满足什么条件时，能保证在*初始状态随机*的情况下，时刻$n$所有灯均为灭？

#### 答案

$$n=2^p \quad (p \in \mathbb{N})$$

#### 证明

　　环形排列下，直接对灯的标号进行加减可能会出现越界的情况，所以我们需要对结果取模，即第$i$盏灯顺时针方向下$k$盏灯为第$(i+k) \bmod n$盏灯。

　　定义$S_t^i$表示时刻$t$第$i$盏灯的亮灭，$0$表示灭，$1$表示亮。

#### 异或？

　　异或运算应用于逻辑运算（也可以看作为二进制下）。$\oplus$为异或运算符。其运算法则相当于*不带进位*的二进制加法：
  
$$\begin{aligned}0 \oplus 0=0\\ 1 \oplus 0=1\\ 0 \oplus 1=1\\ 1 \oplus 1=0\end{aligned}$$

　　即二进制位相同则结果为$0$，不同为$1$。

　　根据*异或*运算的定义及题意，我们可以得到：

$$S_t^i=S_{t-1}^i \oplus S_{t-1}^{(i+1)\bmod n}$$

　　又因为异或运算等价于不带进位的加法，而我们只关注$S_t^i$的奇偶，所以有：

$$S_t^i=\left(S_{t-1}^i+S_{t-1}^{(i+1)\bmod n}\right) \bmod 2$$

　　由于在时刻$t$，标号为$i$的灯受到上一时刻标号$i$、$(i+1) \bmod n$的灯的影响，而在时刻$(t-1)$，标号$(i+1) \bmod n$灯受到时刻$(t-2)$下标号$(i+1) \bmod n$、$(i+2) \bmod n$灯的影响。继续推导可知，时刻$t$下$i$灯受到时刻$0$下$i$灯到$(i+t) \bmod n$灯初始状态的影响，*并且可能不止一次*。

　　注意有$a \bmod p+b \bmod p=(a+b) \bmod p$的性质，所以方便起见，我们可以将取模运算放在最后操作。以下$S$的值域将会扩充到自然数集，但是其意义仍为$S \bmod 2$。

#### 受几次影响？

　　定义$Z_t^k$表示时刻$t$下标号为$i$的灯受到$(i+k) \bmod n$灯初始状态的影响次数，则有：

$$S_t^i=\sum_{j=0}^t Z_t^j S_0^{(i+j) \bmod n}$$

　　根据$S$与$Z$的定义，我们有：

$$S_{t+1}^i=\sum_{j=0}^{t+1} Z_{t+1}^j S_0^{(i+j) \bmod n}=S_t^i+S_t^{i+1}$$

　　展开上式，得：

$$\sum_{j=0}^{t+1} Z_{t+1}^j S_0^{(i+j) \bmod n}=\sum_{k=0}^t Z_t^k S_0^{(i+k) \bmod n}+\sum_{l=0}^t Z_t^l S_0^{(i+l+1) \bmod n}$$

　　因为$Z$的定义，所以$Z_t^{-1}$与$Z_t^{t+1}$是无意义的，值为$0$，则上式可改写成下式形式：

$$\begin{aligned}\sum_{j=0}^{t+1} Z_{t+1}^j S_0^{(i+j) \bmod n}&=\sum_{k=0}^{t+1} Z_t^k S_0^{(i+k) \bmod n}+\sum_{l=0}^{t+1} Z_t^{l-1} S_0^{(i+l) \bmod n}\\ &=\sum_{k=0}^{t+1} \left(Z_t^k S_0^{(i+k) \bmod n}+Z_t^{k-1} S_0^{(i+k) \bmod n}\right)\\ &=\sum_{k=0}^{t+1} \left(Z_t^k+Z_t^{k-1}\right) S_0^{(i+k) \bmod n} \end{aligned}$$

　　所以有$Z$的推导公式：

$$Z_{t+1}^k=Z_t^{k-1}+Z_t^k$$

　　根据定义可以得到边界条件：

$$Z_0^0=1$$

　　不难发现$Z$与$C$的边界条件与推导公式相同，则有：

$$Z_t^k=C_t^k$$

$$S_t^i=\left(\sum_{j=0}^t C_t^j S_0^{(i+j) \bmod n}\right) \bmod 2$$

#### 均灭？

　　若时刻$n$所有灯均灭，则上一时刻即时刻$(n-1)$时，标号$i$的灯应受所有灯影响或不受任何一灯影响。但通过$C_{n-1}^k$的奇偶性我们发现，不受任何一灯影响是不可能的。则$i$灯应受所有灯影响，即为：

$$C_{n-1}^k=1 \quad (n \in Result, k \in \mathbb{N}, 0 \leq k \leq n-1)$$

　　不妨将$C_t^k \bmod 2$（即杨辉三角对$2$取模的图形）列出来。不难发现*规律*：第$2^p-1$行符合全为$1$的条件，也就是说，答案为$n=2^p (p \in \mathbb{N})$（别忘了$n=1$的情况！）而如果我们将$1$染为黑色等边三角形，将$0$染为白色等边三角形（如图），我们将得到*Sierpinski三角形*（谢尔宾斯基三角形）。Sierpinski三角形是分形图形的一个经典图形，在[Matrix67的博客](http://www.matrix67.com/blog/archives/280)里也有提及。

#### Sierpinski三角形？

　　接下来，我们需要证明为什么第$2^p-1$行符合全为$1$的条件。则我们需要证明：

$$C_{2^p-1}^k \equiv 1 \pmod 2 \quad (k \in \mathbb{N}, 0 \leq k \leq 2^p-1)$$

　　展开得：

$$\frac{(2^p-1)!}{k!(2^p-1-k)!} \equiv 1 \pmod 2$$

　　定义$G_i$表示$i$分解质因数后$2$的个数。定义$T_r^l=\sum_{j=l}^r G_j$，则上式可由下式证得：

$$T_k^1=T_{2^p-1}^{2^p-k}$$

　　若将$i$写为二进制，则$G_i$为二进制下$i$末尾$0$的个数。不难发现有以下两条性质：

$$G_i=G_{i+2^j} \quad (i, j \in \mathbb{Z^{+}}, 2^j \gt i)$$

$$G_{2^j}=j \quad (j \in \mathbb{Z^{+}})$$

　　二进制下$(i+2^j)$可由二进制下$i$的第$j$位由$0$变$1$得到，由于第$j$位在限制条件下一定比$i$的最高位更高，所以在第$j$位添加$1$对末尾$0$的个数即$G$无影响，第一条式子得证。第二条式子也可以根据$G$的定义得到。

　　接下来我们需要证明：在$1..2^p-1$的范围内，$G$以$2^{p-1}$为轴对称。

　　首先注意到，在$p=1$的条件下，该结论成立。我们需要将结论扩展到$p \in \mathbb{Z^{+}}$。

　　若在$1..2^p-1$范围内，$G$以$2^{p-1}$为轴对称，则有：

$$G_i=G_{2^{p-1}+(2^{p-1}-i)}=G_{2^p-i}$$

　　又因为$G_i=G_{i+2^p}$，所以：

$$G_{i+2^p}=G_i=G_{2^p-i}$$

　　并且有$G_{2^p}=G_{2^p}$，所以在$1..2^{p+1}-1$范围内，$G$以$2^p$为轴对称。所以我们可以将$p=1$下的结论扩展到$p \in \mathbb{Z^{+}}$。

　　根据$G$的对称性，我们有下式成立：

$$T_k^1=T_{2^p-1}^{2^p-k}$$

　　所以下式成立：

$$\frac{(2^p-1)!}{k!(2^p-1-k)!} \equiv 1 \pmod 2$$

　　得：

$$C_{2^p-1}^k \equiv 1 \pmod 2 \quad (k \in \mathbb{N}, 0 \leq k \leq 2^p-1)$$

　　得证。

　　根据第$2^p-1$行均为$1$，我们可以推得第$2^p$行只有$C_{2^p}^0$与$C_{2^p}^{2^p}$为$1$，其余为$0$，这两个$1$将分别向下扩展到$2^{p+1}-1$行，形成与$1$到$2^p-1$行相同的Sierpinski三角形。

　　所以杨辉三角在对$2$取模的情况下，将会形成Sierpinski三角形。

　　我们的问题也证明完毕，证得答案为$n=2^p (p \in \mathbb{N})$。

#### 所以细心的你看完这篇文章一定会证明啦～

　　实际上，我们用到的是受影响次数的计算式，将其代入题目就能得到题解给出的式子啦！

---

## 作者：Trrui (赞：8)

第一眼只会$O(t*\lceil n/32\rceil)$bitset优化模拟，然后上一届dalao一眼切掉了......

直接上生成函数。

构造多项式$(a_0 * x^0+a_1 * x^1+...+a_n * x^{n-1})$，其中$x^i$项的系数$a_i\pmod 2$表示第$i$盏灯的亮灭情况。

那么每次操作，即将原多项式乘上$(1+x^{-1})$。共$t$次操作，
即乘上$(1+x^{-1})^t$。由二项式定理即可快速得出每一项的系数，
最后加上每一项对$x^k$的系数的贡献即可。

答案即为：$\sum_{i=0}^t a[(i+k)\%n]* \dbinom{t}{i}\pmod 2$

期望时间复杂度$O(t)$。(注意我的编号是从0开始的，别搞混了)。

---

## 作者：初雪_matt (赞：5)

先考虑生成函数。

设 $f(x)=\displaystyle\sum_{i=0}^{n-1}(a_i\times x^i)$，显然其中 $a_i$ 代表灯灭与亮，$0$ 为灭，$1$ 为亮。

考虑将每项乘上 $ \left ( \dfrac{x+1}{x}\right )^t$，再与 $2$ 取模，发现已经完成了题目中要求的操作。

如果只做了一次操作，由于对于第 $i$ 项都会被变为形如 $x^i+x^{i-1}$ 的形式，与 $2$ 取模后是可以完成这个操作的。

然后根据二项式定理可得 $ \left ( \dfrac{x+1}{x}\right )^t=(1+x^{-1})=\displaystyle\sum_{i=0}^{t}\displaystyle\binom{t}{i}x^{i-1}$。

$x^{i-1} \bmod 2$ 的值可以直接得出，我们需要考虑如何快速求出组合数的奇偶性。

由于 $2$ 是质数，所以可以通过 Lucas 定理推出 $\displaystyle\binom{t}{i}=\displaystyle\prod_ {}^{} {\binom{p_k}{c_k}} \bmod 2$。

其中 $p_k$ 是 $t$ 二进制下某一位，$c_k$ 则是 $i$ 的二进制中某一位。

当且仅当 $p_k=0,c_k=1$ 时为 $0$，其他情况均为 $1$。

所以问题转换成了如果出现过 $p_k=0,c_k=1$ 的情况就为偶数，其他就为奇数。

所以只要对 $t$ 向 $i$ 按位与，如果为 $i$ 则为奇数，否则为偶数，时间复杂度 $O(t)$。

```cpp
#include<bits/stdc++.h>
#define N 3000005
#define mod 2
#define int long long
using namespace std;
int n,t,k,a[N],b[N],c[N],res;
signed main(){
    cin>>n>>t>>k;
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=0;i<=t;i++) res=(res+b[(i+k-1)%n+1]*((t&i)==i?1:0))%mod;
    cout<<res;
}
```

---

## 作者：Mizuhara (赞：5)

对于出题人大大的证法表示太高深。

这里用高考范围内的知识给出更为简洁，严谨的证明。

为了方便起见，一下$A{i,j}$中的$j$按$mod n$理解。

首先，我们要证的命题是$:$

若对于任意的正整数$t$及任意的自然数$k$，

有$A_{t,k}=A_{t-1,k}+A_{t-1,k+1}$，

则对任意的自然数$t,k$，

$A_{t,k}=\sum_{i=0}^{t}C_t^iA_{0,k+i}$.

现对$t$用数学归纳法证明命题。

$1.$当$t=0$时，显然$A_{0,k}=\sum_{i=0}^{0}C_0^iA_{0,k+i}$.

$2.$假设$t=m$时命题成立，即对任意的自然数$k$,

有$A_{m,k}=\sum_{i=0}^{m}C_m^iA_{0,k+i}$.

则当$t=m+1$时，对任意的自然数$k$,

有$A_{m+1,k}=A_{m,k}+A_{m,k+1}$

$=\sum_{i=0}^{m}C_m^iA_{0,k+i}+\sum_{i=0}^{m}C_m^iA_{0,k+1+i}$

$=\sum_{i=0}^{m}C_m^iA_{0,k+i}+\sum_{i=1}^{m+1}C_m^{i-1}A_{0,k+i}$

$=C_m^0A_{0,k+0}+\sum_{i=1}^{m}C_m^iA_{0,k+i}+\sum_{i=1}^{m}C_m^{i-1}A_{0,k+i}+C_m^{m}A_{0,k+m+1}$

$=C_{m+1}^0A_{0,k+0}+\sum_{i=1}^{m}(C_m^i+C_m^{i-1})A_{0,k+i}+C_{m+1}^{m+1}A_{0,k+m+1}$

$=C_{m+1}^0A_{0,k+0}+\sum_{i=1}^{m}C_{m+1}^iA_{0,k+i}+C_{m+1}^{m+1}A_{0,k+m+1}$


$=\sum_{i=0}^{m+1}C_{m+1}^iA_{0,k+i}$
故命题对$t=m+1$也成立。

综上命题得证。

```
#include<iostream>
#include<cstdio>
void read(int &s);
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int maxn=3000030;

int gt(int nn){
	int s=0;
	for(int i=2;i<=nn;i*=2)s+=nn/i;
	return s;
}
int n,t,k,Ans,a[maxn];
int main(){
	read(n);read(t);read(k);
	rep(i,1,n)read(a[i]);
	Ans=0;
	rep(i,0,t){
		int C;
		C=(gt(t)-gt(i)-gt(t-i))?0:1;
		Ans=(Ans+C*a[(k+i-1)%n+1])%2;
	}
	cout<<Ans;
	return 0;
}
void read(int &s){
	int k=1;s=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')k=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	s*=k;
}
```

---

## 作者：zerolt (赞：5)

我们可以手动模拟一下时刻$t$第$k$盏灯的情况（设为$tot$）
- $t=(001)_2$时, $tot=a_k$^$a_{k+(001)_2}$
- $t=(010)_2$时, $tot=a_k$^$a_{k+(001)_2}$^$a_{k+(001)_2}$^$a_{k+(010)_2}=a_k$^$a_{k+(010)_2}$
- $t=(011)_2$时, $tot=a_k$^$a_{k+(001)_2}$^$a_{k+(010)_2}$^$a_{k+(010)_2}$
- $t=(100)_2$时, $tot=a_k$^$a_{k+(100)_2}$
 
 ......
 
 大概能看出规律了（如果还不行可以继续列）
 
$$tot=XOR_{I\subseteq t}$$（$I\subseteq t$ 表示$I$是$t$的二进制集合下的子集）

代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int N=3000010;
int n, t, k, a[N], ans;

int read(){
	int out=0, f=1; char c=getchar(); 
    while(c < '0' || c > '9') {if(c == '-') f=-1; c=getchar();}
	while(c >= '0' && c <= '9') 
    {out=(out<<1)+(out<<3)+c-'0'; c=getchar();} 
    return out*f;
}

void solve(){
	n=read(), t=read(), k=read();
	for(int i=1; i <= n; i++) a[i]=read(); ans=a[k];
	for(int i=1; i <= t; i++) if((t|i) == t){
		int next=i+k; next%=n; 
        if(!next) next=n;
		ans^=a[next];
	}
	printf("%d", ans);
}

int main(){solve(); return 0;}

```

~~至于正确性证明我不会,并且出题者的正解我看不懂~~

欢迎$dalao$们来指导或者$hack$

 

---

## 作者：zzqDeco (赞：4)

很容易发现，每一个时间的操作就是异或

那么我们直接考虑异或是模 $2$ 意义下的加法，那我们直接就当作加法来考虑就行了

可以发现我们操作的序列是这样的序列（下面仅展现一部分，太丑了

[![Biko7T.png](https://s1.ax1x.com/2020/10/22/Biko7T.png)](https://imgchr.com/i/Biko7T)

我们可以发现这个和杨辉三角的递推过程是等价的

那么就可以说明，是让我们求其中一些位置和杨辉三角的某些项的乘积和

考虑到我们最后要对 $2$ 取模，那么我们可以看看杨辉三角在模 $2$ 意义下的规律

~~我们可以发现，全 $1$ 的必然会导出中间全 $0$ 的行，依次向下形成倒三角，中间的 $0$ 并且还是连续的，旁边还是分形，这样就可以 $O(logt)$ 求了~~

然而上面的并没有p用，又考虑到直接预处理阶乘求组合数不太可行，因为偶数在此意义下没有逆元

我们直接考虑组合数公式

$$
C=\frac{n!}{r!\times(n-r)!}
$$

实际就是看上下的 $2$ 因子数量，考虑预处理出`we`数组表示 $2$ 的次幂的位数，辅助`lowbit`来预处理阶乘的 $2$ 因子数量

然后就可以暴力 $O(t)$ 解决这个问题了

```cpp
#include <cstdio>

using namespace std;

int n,t,k;

int zb,zl;

int a[3000010],fra[3000010],we[5000010],ans;

int lowbit(int x)
{
  return x&(-x);
}

void init()\\这里是预处理2因子数量
{
  for(int i=1;i<=21;i++) we[1<<i]=i;
  fra[0]=0;
  for(int i=1;i<=t+1;i++) fra[i]=fra[i-1]+we[lowbit(i)];
}

int get(int x)
{
  if(fra[t]-fra[x-1]-fra[t-x+1]>0) return 0;
  return 1;
}

int main()
{
  scanf("%d%d%d",&n,&t,&k);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  init();
  for(int i=1;i<=t+1;i++) ans=(ans+a[(k+i-2)%n+1]*(get(i))%2)%2;
  printf("%d",ans);
}
```

update：

今天翻看资料的时候发现，这东西叫做Sierpinski三角形

然后发现这个东西有很nb的结论来看 $01$ 状态

看这里:http://www.matrix67.com/blog/archives/280

```cpp
#include <cstdio>

using namespace std;

int n,t,k;

int a[3000010],fra[3000010],we[5000010],ans;

int get(int x)
{
  if(((x-1)&t)==(x-1)) return 1;
  return 0;
}

int main()
{
  scanf("%d%d%d",&n,&t,&k);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  init();
  for(int i=1;i<=t+1;i++) ans=(ans+a[(k+i-2)%n+1]*(get(i))%2)%2;
  printf("%d",ans);
}
```

---

## 作者：bluewindde (赞：2)

### 随机化

本题没有捆绑，随机数可以拿一半左右的部分分：

```python
import random
print(random.randint(1,3)%2)
```

### 模拟

对于样例，不难发现，其亮灭状态如此变化：

$$a_{t_0}\{1,0,1,0\}$$

$$a_{t_1}\{1,1,1,1\}$$

$$a_{t_2}\{0,0,0,0\}$$

$$a_{t_3}\{0,0,0,0\}$$

$$\dots$$

$$a_{t_n}\{0,0,0,0\}$$


发现当一个数组全部变为 $0$ 时，可以直接输出答案 $0$，当一个数组变为已经出现过的数组时，可以直接查找历史记录输出答案。加上这两个策略，使用模拟可以得 $50\sim60$ 分（好像不用策略也有这么多分）。

### 正解

数学题就要先模拟找规律。

设 $t=0$ 时第 $k$ 盏灯（下标从 $0$ 开始）的亮灭状态为 $a_k$。

$t=1$ 时 $ans_1=a_k\oplus a_{(k+1)\mod n}$

$t=2$ 时 $ans_2=a_k\oplus a_{(k+2)\mod n}$

$t=3$ 时 $ans_3=a_k\oplus a_{(k+1)\mod n}\oplus a_{(k+2)\mod n}\oplus a_{(k+3)\mod n}$

$t=4$ 时 $ans_4=a_k\oplus a_{(k+4)\mod n}$

发现

$$ans_t=\bigoplus\limits_{i\subseteq t}\  a_{(k+i)\mod n}$$

**结论：当且仅当 $i$ 是 $t$ 在二进制下的子集，它对答案产生贡献。**

### 推导

设 $b_t$ 表示时刻为 $t$ 时灯的亮灭状态，**$b_t$ 的下标 $0$ 对应 $a$ 数组中的下标 $k$**。

因为每盏灯的亮灭**仅取决于**当前时刻这盏灯与顺时针方向下一盏灯的亮灭，所以可以得到 $b$ 的递推式：

$$b_{t_i}=b_{t-1_i}\oplus b_{t-1_{i+1}}$$

再模拟一次：

若 $t=0=(0)_2$，有 $b=\{a_k,a_{k+1},a_{k+2},\dots\}$。

若 $t=1=(1)_2$，有 $b=\{a_k\oplus a_{k+1},a_{k+1}\oplus a_{k+2},a_{k+2}\oplus a_{k+3},\dots\}$。

若 $t=2=(10)_2$，有 $b=\left\{\begin{matrix}a_k\oplus a_{k+1}\oplus a_{k+1}\oplus a_{k+2},\\a_{k+1}\oplus a_{k+2}\oplus a_{k+2}\oplus a_{k+3},\\a_{k+2}\oplus a_{k+3}\oplus a_{k+3}\oplus a_{k+4},\\\dots\end{matrix}\right\}$

若 $t=3=(11)_2$，有

$$b=\left\{
\begin{matrix}
a_k\oplus a_{k+1}\oplus a_{k+1}\oplus a_{k+1}\oplus a_{k+2}\oplus a_{k+2}\oplus a_{k+2}\oplus a_{k+3},\\
a_{k+1}\oplus a_{k+2}\oplus a_{k+2}\oplus a_{k+2}\oplus a_{k+3}\oplus a_{k+3}\oplus a_{k+3}\oplus a_{k+4},\\
a_{k+2}\oplus a_{k+3}\oplus a_{k+3}\oplus a_{k+3}\oplus a_{k+4}\oplus a_{k+4}\oplus a_{k+4}\oplus a_{k+5},\\
\dots
\end{matrix}
\right\}$$

大家应该都发现了：因为 $b_{t_i}=b_{t-1_i}\oplus b_{t-1_{i+1}}$，由异或运算的自反性，在 $b_{t_i}$ 中每个元素被异或的次数 $w_{t_i}=\begin{cases}w_{t-1_i}+w_{t-1_{i+1}}&t\ge1\\1&t=0\end{cases}$，统计每个 $w_{t_i}$，写成下面这个矩阵，它的第 $t$ 行第 $i$ 项表示在时刻 $t$ 时第 $k+i$ 盏灯的亮灭状态：

$$\begin{matrix}
1,\\
1,1,\\
1,2,1,\\
1,3,3,1,\\
1,4,6,4,1,\\
\dots
\end{matrix}$$

**这不就是[杨辉三角](https://baike.baidu.com/item/%E6%9D%A8%E8%BE%89%E4%B8%89%E8%A7%92/215098)吗？**

于是引出第一种解法，由二项式系数的奇偶性，快速求出答案是否包含这一位：若 $n\&k=k$，二项式系数 $\left(\begin{matrix}n\\k\end{matrix}\right)$ 为偶数，否则为奇数。

[证明二项式系数的奇偶性](https://www.cnblogs.com/Beckinsale/p/7469842.html)

**但是，有更方便的方法！**

在模 $2$ 的意义下，该矩阵为：

$$\begin{matrix}
1,\\
1,1,\\
1,0,1,\\
1,1,1,1,\\
1,0,0,0,1,\\
\dots
\end{matrix}$$

去掉每行的最后一项，得到：

$$\begin{matrix}
0,\\
1,\\
1,0,\\
1,1,1,\\
1,0,0,0,\\
\dots
\end{matrix}$$

容易发现每一行的第 $i$ 项就是 $t$ 的二进制表示的（从左往右）第 $i$ 位，得到结论：当且仅当 $i$ 是 $t$ 在二进制下的子集，它对答案产生贡献。

**因为我们去掉了最后一项，所以最后不要忘记异或上 $a_k$！**

### 代码

```cpp
#include <iostream>
using namespace std;

int n,t,k;
int a[3000005];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>t>>k;
    for(int i=1;i<=n;++i) {
        bool x;
        cin>>x;
        a[i]=x;
    }
    int ans=a[k];
    for(int i=t;i>0;i=(i-1)&t) { // 枚举 t 的子集
        int x=i+k;
        x%=n;
        if(x==0) x=n;
        ans^=a[x];
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：hanzhongtlx (赞：0)

这个玩意好像挺经典的。  

我们发现 $t<n$ 时，递推式是一个倒金字塔的样子，容易得到： 

$$a_{i,j}=a_{i-1,j}\;\text{xor}\;a_{i-1,j+1}$$  

$a_{i,j}$ 代表着 $i$ 时刻 $j$ 位置的值，这时我们容易想到先把数组平移一下，让第 $k$ 位到第一位去。  

然后我们拆一下式子发现当层数 $p$ 为 $2$ 整数次幂时，满足 

$$a_{i,j}=a_{i-p,j}\;\text{xor}\; a_{i-p,j+p}$$  

然后就可以 $\mathcal O(n\log n)$ 解决这个问题了。  

注意空间不太够，所以滚动数组一下就可以了。


```
#include"iostream"
#include"cstdio"
#include"cmath"
using namespace std;

#define MAXN 3000000
#define read(x) scanf("%d",&x)

int n,t,k;
int a[MAXN][2];
int f=0;

int main()
{
	read(n),read(t),read(k);
	for(int i=1;i<=n;i++) read(a[i][0]);
	for(int i=k;i<=n;i++) a[i-k+1][1]=a[i][0];
	for(int i=1;i<k;i++) a[n-k+1+i][1]=a[i][0];
	if(t==1) return printf("%d\n",a[1][1]^a[2][1]);
	for(int i=19;i>=0;i--)
	{
		int rt=1<<i;
		if(rt>t) continue;
		for(int j=1;j<=n-rt;j++) a[j][f]=a[j][f^1]^a[j+rt][f^1];
		f^=1,t-=rt;
	}
	printf("%d\n",a[1][f^1]);
	return 0;
}
```

---

## 作者：limi_sanhua (赞：0)

[少爷，来玩玩儿嘛~](https://www.cnblogs.com/ling-zhi/p/11774108.html)

找下规律，易得 N(log(N)/log(2)) 作法

先假设 **k=1** ,我们就看**答案要的这一位**

**0** 时刻，ans = **a1**

1 时刻，ans = a1^a2

**2** 时刻，ans = a1^a2^a2^a3 = **a1^a3**

3 时刻，ans = a1^a2^a3^a4

**4** 时刻，ans = a1^a2^a2^a3^a3^a4^a4^a5 = **a1^a5**

5 ......................................................................................

6 ............................................................................................

7 ...................................................................................................

**8** 时刻，ans = ......................................................................................... = **a1^a9**


这样 log(N)/log(2) 就出来了，事实上并不会T

与倍增法求LCA有相似处
```cpp
#include<iostream>
#include<cstdio>

#define ri register int
#define u int

namespace opt {

	inline u in() {
		u x(0),f(1);
		char s(getchar());
		while(s<'0'||s>'9') {
			if(s=='-') f=-1;
			s=getchar();
		}
		while(s>='0'&&s<='9') {
			x=(x<<1)+(x<<3)+s-'0';
			s=getchar();
		}
		return x*f;
	}

}

using opt::in;

#include<cmath>
#include<algorithm>

#define NN 3000005

namespace mainstay {

	u N,T,K,a[NN<<1];

	inline void solve() {
		while(~scanf("%d%d%d",&N,&T,&K)) {
			for(ri i(1); i<=N; ++i) a[i]=a[i+N]=in();
			u ans(a[K]);
			while(T) {
				u k(std::log(T)/std::log(2));
				u p(std::pow(2,k));
				ans^=a[K+p];
				for(ri i(1); i<=N; ++i) a[i]^=a[i+p];
				for(ri i(1); i<=N; ++i) a[i+N]=a[i];
				T-=std::pow(2,k);
			}
			printf("%d\n",ans);
		}
	}

}

int main() {

	std::ios::sync_with_stdio(false);
	mainstay::solve();

}
```


---

