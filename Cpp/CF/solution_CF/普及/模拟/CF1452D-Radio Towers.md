# Radio Towers

## 题目描述

There are $ n + 2 $ towns located on a coordinate line, numbered from $ 0 $ to $ n + 1 $ . The $ i $ -th town is located at the point $ i $ .

You build a radio tower in each of the towns $ 1, 2, \dots, n $ with probability $ \frac{1}{2} $ (these events are independent). After that, you want to set the signal power on each tower to some integer from $ 1 $ to $ n $ (signal powers are not necessarily the same, but also not necessarily different). The signal from a tower located in a town $ i $ with signal power $ p $ reaches every city $ c $ such that $ |c - i| < p $ .

After building the towers, you want to choose signal powers in such a way that:

- towns $ 0 $ and $ n + 1 $ don't get any signal from the radio towers;
- towns $ 1, 2, \dots, n $ get signal from exactly one radio tower each.

For example, if $ n = 5 $ , and you have built the towers in towns $ 2 $ , $ 4 $ and $ 5 $ , you may set the signal power of the tower in town $ 2 $ to $ 2 $ , and the signal power of the towers in towns $ 4 $ and $ 5 $ to $ 1 $ . That way, towns $ 0 $ and $ n + 1 $ don't get the signal from any tower, towns $ 1 $ , $ 2 $ and $ 3 $ get the signal from the tower in town $ 2 $ , town $ 4 $ gets the signal from the tower in town $ 4 $ , and town $ 5 $ gets the signal from the tower in town $ 5 $ .

Calculate the probability that, after building the towers, you will have a way to set signal powers to meet all constraints.

## 说明/提示

The real answer for the first example is $ \frac{1}{4} $ :

- with probability $ \frac{1}{4} $ , the towers are built in both towns $ 1 $ and $ 2 $ , so we can set their signal powers to $ 1 $ .

The real answer for the second example is $ \frac{1}{4} $ :

- with probability $ \frac{1}{8} $ , the towers are built in towns $ 1 $ , $ 2 $ and $ 3 $ , so we can set their signal powers to $ 1 $ ;
- with probability $ \frac{1}{8} $ , only one tower in town $ 2 $ is built, and we can set its signal power to $ 2 $ .

The real answer for the third example is $ \frac{5}{32} $ . Note that even though the previous explanations used equal signal powers for all towers, it is not necessarily so. For example, if $ n = 5 $ and the towers are built in towns $ 2 $ , $ 4 $ and $ 5 $ , you may set the signal power of the tower in town $ 2 $ to $ 2 $ , and the signal power of the towers in towns $ 4 $ and $ 5 $ to $ 1 $ .

## 样例 #1

### 输入

```
2```

### 输出

```
748683265```

## 样例 #2

### 输入

```
3```

### 输出

```
748683265```

## 样例 #3

### 输入

```
5```

### 输出

```
842268673```

## 样例 #4

### 输入

```
200000```

### 输出

```
202370013```

# 题解

## 作者：ql12345 (赞：6)

[传送门](https://www.luogu.com.cn/problem/CF1452D)

### 题面：

一行有n个城市，在一些城市上放上信号塔，每个城市放上信号塔的概率互不影响，都为$\frac 1 2$，求有多少概率使得放完信号塔之后，存在一个各个信号塔信号分配方案，满足以下条件：

- 1到n的所有城市都有信号，且0和n+1城市没有信号

- 所有城市可以接收到信号的城市只有1个

一个信号塔分配了r的信号，就可以覆盖包含自身在内的半径为r的范围内的城市

第二条限制解释：01010是不合法的方案，因为给2塔和4塔半径为2的信号虽然满足第一条限制，但由于3城市可以接收到信号的城市有2和4两个，所以不满足第二条限制

答案对998244353取模

### Solution：

有概率不好搞，但看样例解释很容易发现，其实$\frac 1 2$这个数字没用，最终答案一定为$\frac {a_n} {2^n}$，$a_n$表示方案个数，也就是求出方案个数再乘上2的次幂对998244353的逆元即可

求方案个数：不难想到暴力$dp$，枚举最左端被覆盖的半径

```cpp
a[0] = a[1] = a[2] = 1;
for (int i = 3; i <= n; ++i)
	for (int j = 1; j <= i; j += 2)
		a[i] = (a[i] + a[i - j]) % P;
```

看式子，不难想到前缀和优化，因为每次是```j+=2```，所以奇偶分开统计前缀和，令$f[i],s[i]$分别表示i为偶数和奇数时的奇偶性相同的前缀和，因为方程中下标每次减的都是奇数，所以i为奇数的时候要从偶数前缀和统计答案，然后将算出的$a_i$加入奇数前缀和

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2000005, P = 998244353;
int a[N], f[N], s[N];
inline int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = a * a % P)
        if (b & 1) res = res * a % P;
    return res;
}
signed main() {
    int n;
    cin >> n;
    a[0] = a[1] = a[2] = 1;
    s[1] = 1, f[2] = 2;
    for (int i = 3; i <= n; ++i) {
        if (i & 1) {
            a[i] = f[i - 1];
            s[i] = (s[i - 2] + a[i]) % P;
        } else {
            a[i] = s[i - 1];
            f[i] = (f[i - 2] + a[i]) % P;
        }
    }
    cout << power(power(2, n), P - 2) * a[n] % P;
    return 0;
}
```

---

## 作者：vectorwyx (赞：3)

每一个 $n$ 都有与之对应的唯一的答案，这种题目的思路一般都是**找到问题与其子问题之间的关系，利用递推求解。**

由于每个位置都只能被一个信号塔覆盖，所以如果从最左面的灯塔起有 $x$ 个连续的位置没有信号塔（即 $a_{1…x}$ 均为 $0$），**第 $x+1$ 个位置必须要建信号塔，而且信号塔的强度只能为 $x+1$**。因为如果它的强度小于 $x+1$，那么 $1…x$  中就会有一段前缀无法被覆盖；而如果强度大于 $x+1$，第 $0$ 个灯塔就会被覆盖，这是不合法的。同时，既然第 $x+1$ 个位置上的信号塔的强度一定为 $x+1$，那么 $x+2…2x+1$ 这段也被覆盖了，它不能再被右面的任何一个信号塔覆盖，因此问题就转化成了 $n=n-2x-1$ 时的子问题。

令 $dp_{i}$ 表示当 $n=i$ 时合法的概率，$dp_{i}=\sum_{j=0}^{\frac{i-1}{2}}dp_{i-2j-1}\cdot \frac{1}{2^{2j+1}}$。$\frac{1}{2^{2j+1}}$ 是 $1…j,j+2…2j+1$ 这两段区间没有信号塔且第 $j+1$ 个位置有信号塔的概率。用前缀和维护可以做到 $O(n)$ 的时间复杂度。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int yrz=998244353;
int ksm(int x,int y){
	if(y==0) return 1;
	int ret=ksm(x,y/2);
	ret=1ll*ret*ret%yrz;
	if(!(y&1)) return ret;
	return 1ll*ret*x%yrz;
}

int ny(int x){
	return ksm(x,yrz-2);
}

const int N=2e5+5;
int f[N],g[N],pw[N],ni[N],ny_3,sum[N];

int main(){
	int n=read();
	pw[0]=1;
	fo(i,1,n) pw[i]=pw[i-1]*2%yrz;
	ni[n]=ny(pw[n]);
	go(i,n-1,0) ni[i]=ni[i+1]*2%yrz;
	ny_3=ny(3);
	//fo(i,0,n) printf("%d ",pw[i]);puts("");
	//fo(i,0,n) printf("%d ",ni[i]);puts("");
	fo(i,0,2) f[i]=ni[i];
	sum[2]=(f[2]+1ll*f[0]*ni[2])%yrz;
	sum[1]=f[1];
	sum[0]=f[0];
	fo(i,3,n){
		f[i]=1ll*sum[i-1]*ni[1]%yrz;
		sum[i]=(1ll*sum[i-2]*ni[2]+f[i])%yrz;
	}
	cout<<f[n];
	return 0;
}

```


---

## 作者：Oxide (赞：3)

[或许？](https://www.cnblogs.com/AWhiteWall/p/14083524.html)

# $\text{Solution}$

容易发现其实就是将长度为 $n$ 的区间划分成若干奇数段的总方案数再除以 $2^n$。

解释一下就是因为每个小镇选与不选的概率都是 $\frac{1}{2}$，那么每种方案的概率都是一样的。

我们发现 $0,n+1$ 不能收到信号其实就是将 $[1,n]$ 阻断起来，很容易联想到 $\text{DP}$ 的子状态：$f[i]$ 表示 $i$ 个小镇的总方案数，那我们就有转移柿（枚举最后一段长度为 $2\times j+1$，$f[0]=0$）：



- 若 $i$ 为偶数：

$$
f[i]=\sum_{j=0}^{\frac{i-1}{2}} f[i-2\times j-1]
$$

- 若 $i$ 为奇数（加 $1$ 是因为本身可以成为一种长度为 $i$ 方案）：

$$
f[i]=1+\sum_{j=0}^{\frac{i-1}{2}} f[i-2\times j-1]
$$



这个时候就可以分奇偶做前缀和优化以 $\mathcal O(n)$ 的优秀复杂度通过此题。



但其实这个柿子暗藏玄机，其实 $f[n]$ 就是 $\text{Fib}[n]$！~~（针对数据思考）~~



首先 $f[1],f[2]$ 肯定满足。



还是分奇偶讨论：



- 若 $n$ 为偶数：


$$
f[n]=f[1]+f[3]+f[5]+...+f[n-1]
$$

$$
=f[2]+f[3]+f[5]+...+f[n-1]
$$

$$
=f[4]+f[5]+...+f[n-1]
$$

$$
=f[n-2]+f[n-1]
$$

- 若 $n$ 为奇数：


$$
f[n]=1+f[2]+f[4]+...+f[n-1]
$$

$$
=f[1]+f[2]+f[4]+...+f[n-1]
$$

$$
=f[3]+f[4]+...+f[n-1]
$$

$$
=f[n-2]+f[n-1]
$$



从 $3$ 开始我们这样递推地证明，可以一直推到 $n$。

# $\text{Code}$

```cpp
#include <cstdio>
#define rep(i,_l,_r) for(signed i=(_l),_end=(_r);i<=_end;++i)
#define print(x,y) write(x),putchar(y)

template <class T> inline T read(const T sample) {
	T x=0; int f=1; char s;
	while((s=getchar())>'9'||s<'0') if(s=='-') f=-1;
	while(s>='0'&&s<='9') x=(x<<1)+(x<<3)+(s^48),s=getchar();
	return x*f; 
} 

template <class T> inline void write(T x) {
	if(x<0) return (void)(putchar('-'),write(-x));
	if(x>9) write(x/10);
	putchar(x%10^48);
}

#include <iostream>
using namespace std;

const int mod=998244353;

int n,a=1,b=1;

int qkpow(int x,int y) {
	int r=1;
	while(y) {
		if(y&1) r=1ll*r*x%mod;
		x=1ll*x*x%mod; y>>=1;
	}
	return r;
}

int main() {
	n=read(9);
	rep(i,3,n) a=(a+b)%mod,swap(a,b);
	print(1ll*b*qkpow(qkpow(2,n),mod-2)%mod,'\n');
	return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：2)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16920768.html)

[题目传送门](http://codeforces.com/problemset/problem/1452/D)

### 题目大意
在数轴上有 $n+2$ 个小镇，位置为 $0,1,\dots,n,n+1$。  
现在在 $1,2,\dots ,n$ 的小镇都有 $\dfrac{1}{2}$ 的概率建设一个信号发射器。  
对于任意一个信号发射器，你都可以选择一个整数作为强度 $p$。如果一个信号发射器的位置是 $x$，那么位于 $[x-p,x+p]$ 的小镇都能收到一个信号。  
现在求能够通过设置信号值，使 $1,2,\dots,n$ 恰好能接受到一个信号，$0,n+1$ 不能接受到信号的概率，对 $998244353$ 取模。

### 题解
设 $f_i$ 为 $n=i$ 的时候的方案数。显然 $f_0=f_1=1$。  
考虑如何转移  
假设我们最后一个位置是 $i-j$。  
那么显然这个位置的强度是 $j$，这样 $[i-j\times2,i]$ 这段区间就被覆盖了，此时的方案数就是 $f_{i-j\times 2}$。  
枚举 $j$，我们可以知道  
$$f_i=\sum_{j< i\ , i\not\equiv j\pmod 2}f_j$$
所以只需要预处理 $i$ 模 $2$ 不同的前缀和就可以了。

```cpp
int n; ll f[maxn],s[2];
ll fastpow(ll x,ll y){
	ll tmp=x,res=1;
	while(y){
		if(y&1) res=res*tmp%MOD;
		tmp=tmp*tmp%MOD; y>>=1;
	} return res;
}
int main(){
	int i; n=read(); f[0]=1; s[0]=1; f[1]=1; s[1]=1;
	for(i=2;i<=n;i++) f[i]=s[(i&1)^1],f[i]%=MOD,s[i&1]+=f[i],s[i&1]%=MOD;
	print(f[n]*fastpow(499122177,n)%MOD);
	return 0;
}
```

---

## 作者：ChuTian (赞：2)

# 题意：
在一条线上有$n+2$个镇，编号从$0\sim n+1$。在$1\sim n$个镇上每个镇都有$\frac{1}{2}$的概率安装一个信号塔，所有事件相互是独立的。如果一个在$i$位置的信号塔的强度为$p$，那么处于$|c-i|\lt p$的镇$c$都会收到信号。你可以给信号塔设置强度$p$。现在要求，装好的信号塔不能覆盖$0$和$n+1$这两个镇，并且$1\sim n$的镇**会且只会被$1$个**信号塔的信号覆盖。求满足这种条件的概率有多大。
# 思路：
设有$n+2$个镇的时候，满足要求的情况有$f(n)$种。
显然答案是$\frac{f(n)}{2^n}$,然后手推几下发现$f(n)$满足斐波那契数列，所以答案为$\frac{Fib(n)}{2^n}$。

以下试推之：

我们可以显然得到$n=1$时，$f(1)=1$,只有且仅只有在$1$号镇上存在信号塔的时候才满足。

对于下面情况，我们只用考虑在$1\sim \lceil\frac{n}{2}\rceil$上面放$1$个信号塔时候，剩余的区域应该如何去放置信号塔。因为一旦大于这个数，显然他就无法保证在能够覆盖到$1$号镇的情况下不覆盖到$n+1$号镇。

在$n=2$的时候，在$1$号镇装信号塔的话，那么对于剩下的镇$(2)$，就成了$n=1$时候的情况。也就是说$f(2)=f(1)$。

在$n=3$的时候，在$1$号镇装信号塔的话，那么对于剩下的镇$(2,3)$，就成了$n=2$的状况；在$2$号镇装信号塔的话，就可以正好覆盖所有镇。也就是$f(3)=f(2)+1$。

在$n=4$的时候，在$1$号镇装信号塔的话，那么对于剩下的镇$(2,3,4)$，就是$n=3$的状况；在$2$号镇装信号塔的话，对于剩下的镇$(4)$，就是$n=1$的状况。也就是$f(4)=f(3)+f(1)$。

在$n=5$的时候，在$1$号镇装信号塔的话，那么对于剩下的镇$(2,3,4,5)$，就是$n=4$的状况；在$2$号镇装信号塔的话，对于剩下的镇$(4,5)$，就是$n=2$的状况;在$3$号镇装信号塔的话，就可以正好覆盖所有镇。也就是$f(5)=f(4)+f(2)+1$。

$\cdots\cdots$

这样是不是发现了一些规律。

显然，假设信号塔建在$i(i\in[1,\lceil\frac{n}{2}\rceil])$的时候,为了能够覆盖到$1$号镇，它的信号强度就为$i$,也就是说，它能够覆盖$[1,2i-1]$的镇。那么对于$[2i,n]$的镇来说，我们可以把它看成求$f(n-2i+1)$。
那么我们可以得到下面的式子：

$f(n)=\begin{cases}f(n-1)+f(n-3)+\cdots+f(2)+1&\text{n is odd}\\f(n-1)+f(n-3)+\cdots+f(1)&\text{n is even}\end{cases}$

根据斐波那契数列的性质：

$Fib(1)+Fib(3)+\cdots+Fib(2n-1)=Fib(2n)$,
$Fib(2)+Fib(4)+\cdots+Fib(2n)=Fib(2n+1)-1$。

我们显然可以通过这个化简得到：$f(n)=Fib(n)$。

---

## 作者：vеctorwyx (赞：1)

~~赛前做一道概率题有助于思路的产生~~

### 题目大意

有$n +2$个点，编号从$0$开始，线性排列，从点$1$到点$n$每个点被取到的概率为$\large \frac{1}{2}$，求能产生合法覆盖的概率对$998244353$取模。

每个点若向左覆盖了$x$个点，则他必须同时向右覆盖$x$个点，即覆盖范围$i - x$到$i + x$。

当每个点仅被覆盖一次，且点$0$和点$n-1$不被覆盖时，覆盖合法。

### sol

~~众所周知，概率题只需要会一个公式：~~

$\Large P(A) = \frac{a}{b}$

很明显$b$为总方案数，$2^n$。

难点在于怎么求$a$。

1. 暴力

	枚举每种合法的覆盖方式

	为了保证覆盖合法，可以在DFS时每次往后跳奇数个单位，保重不被重复覆盖。
    
    时间复杂度$O(n^2)$，会超时。
    
    代码大概是这样的：
    
    ```
    void dfs(int x){
        if(x == n + 1){
            ji = (ji + 1) % p;
            return;
        }
        ji = (ji + 1) % p;
        for(int i = 1 ; i <= n ; i++){
            if(x + i * 2 - 1 > n + 1)
                break;
            dfs(x + i * 2 - 1);
        }
        return ;
    }

    ```
    
2. 优化

	考虑每个点的转移。
    
    第$i$个点上的方案数会从它前面的第$i-1$、$i-3$、$i-5$......这些点上的方案数转移过来。
    
    满足DP。
    
    记录两个变量$sum1,sum2$，$sum1$表示下标为偶数的点的方案数之和，$sum2$表示下标为奇数的点的方案数之和。
    
    转移方程：
    
    $dp_{i*2-1} = sum1$
    
    $dp_{i*2} = sum2$
    
    ~~好像有点敷衍。~~
    
    还是代码比较直观：
    
    ```
    
    dp[0] = 1, sum1 = 1, sum2 = 0;
	for(int i = 1; i <= n ; i++).{
		if(i&1){
			(dp[i] = sum1) %= p;
			(sum2 += dp[i]) %= p;//奇数点处理
		}
		else{
			(dp[i] = sum2) %= p;
			(sum1 += dp[i]) %= p;//偶数点处理
		}
	}
    ```
    
   时间复杂度$O(n)$。
    
    ~~完整代码就不放了。~~
    

---

## 作者：LinkWish (赞：1)

答案的计算其他题解已经说得很清楚了，即枚举 $i,j$，计算 $i,j$ 在答案中的贡献，即如果 $i=j$，设离 $i$ 距离在 $R$ 内的蛇的个数为 $x$ ，则贡献为 $a_i^2\times(\binom{n}{m}-\binom{n-x}{m})$；否则设离 $i$ 距离在 $R$ 内但离 $j$ 距离不在 $R$ 内的蛇的个数为 $x$，离 $j$ 距离在 $R$ 内但离 $i$ 距离不在 $R$ 内的蛇的个数为 $y$，离 $i,j$ 距离都在 $R$ 内的蛇的个数为 $z$，则贡献为 $2\times a_i\times a_j \times (\binom{n}{m}-\binom{n-z}{m}+\binom{n-z}{m}-\binom{n-z-x}{m}-\binom{n-z-y}{m}+\binom{n-z-x-y}{m})$。

我在这里提供一种较慢，但好写的求 $x,y,z$ 的做法。我们使用 ```STL::bitset``` 来计算两个集合的并集与交集，更具体地：

设 $f_{i,j}=[dis_{i,j}\le R]$。


当 $i=j$ 时，$x=\sum\limits_{k=1}^n f_{i,k}$，即 ```f[i].count()```。

否则，$x=\sum\limits_{k=1}^nf_{i,k}[f_{i,k}\ne f_{j,k}]$，即 ```(f[i]|f[j]).count()-f[i].count()```；

同理， $y=\sum\limits_{k=1}^nf_{j,k}[f_{i,k}\ne f_{j,k}]$，即 ```(f[i]|f[j]).count()-f[j].count()```；

$z=\sum\limits_{k=1}^nf_{i,k}\times f_{j,k}$，即 ```(f[i]&f[j]).count()```。

枚举 $i,j$ 的时间复杂度是 $\Theta(n^2)$ 的，中间 bitset 计算的时间复杂的是 $\Theta(\frac{n}{32})$ 的，所以总时间复杂度为 $\Theta(\frac{n^3}{32})$，常数不大的话即可通过。

关于代码部分：代码仅放出主体部分，因为前面的模板（快读与modint）太长影响阅读，对本题没有太大影响，而且仅凭主体部分已经足以辅助理解。在代码中没有任何取模操作，因为我使用了自己封装的modint类型使代码更加简洁易读，不代表本题不需要取模。

```cpp
//Linkwish's code
const int N=2005;
modint p[N],inv[N];
int n,m,r;
inline modint qpow(modint x,int y){
	modint res={1};
	while(y){
		if(y&1)res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
inline void init(){
	p[0]={1};
	for(int i=1;i<=n;i++)p[i]=p[i-1]*i;
	inv[n]=qpow(p[n],mod-2);
	for(int i=n-1;i>=0;i--)inv[i]=inv[i+1]*(i+1);
}
inline modint c(int x,int y){
	if(x<0||y<0||x<y)return {0};
	return p[x]*inv[y]*inv[x-y];
}
bitset<N> is[N];
int x[N],y[N];
modint a[N];
signed main(){
	read(n),read(m),read(r);
	init();
	for(int i=1;i<=n;i++)read(x[i]),read(y[i]),read(a[i].val);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(max(abs(x[i]-x[j]),abs(y[i]-y[j]))<=r)
				is[i][j]=1;
	modint ans={0};
	for(int i=1,now,tx,ty,all;i<=n;i++){
		ans+=a[i]*a[i]*(c(n,m)-c(n-is[i].count(),m));
		for(int j=i+1;j<=n;j++){
			now=(is[i]&is[j]).count();
			all=(is[i]|is[j]).count();
			tx=all-is[j].count(),ty=all-is[i].count();
			ans+=a[i]*a[j]*2*(c(n,m)-c(n-tx-now,m)-c(n-ty-now,m)+c(n-tx-ty-now,m));
		}
	}
	writeln(ans.val);
	return 0;
}
```


---

## 作者：_Flame_ (赞：0)

## 思路

这是一道概率题，思路很明显是 **递推** 。

观察一下题目，根据题意，当有 $n+2$ 个小镇时，设信号塔有 $k$ 种分布方案，很容易得出答案为 $\tfrac{k}{2^n}$  。我们可以先枚举找出当有 $n+2$ 个小镇时 $k$ 的值。

很明显 $n=1$ 时 $k$ 只有 $1$ 种情况, $n=2$ 时也只有一种情况，当 $n=3$ 时，可以在三个小镇各装一个 $p=1$ 的信号塔，也可以在二号小镇装一个 $p=2$ 的信号塔，这样编号为一和三的两小镇也能被覆盖到，此时 $k=3$ 。由此类推，可以发现 $k$ 的值是一个斐波那契数列。这样就能通过递推求出 $k$ 的值，再写一个快速幂求出 $2^n$ ，最后模上模数，输出答案就好了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long long a[1000010];
long long b[1000010];
long long mod=998244353;
long long ans;
long long ksm(long long a,long long b,long long p){
    long long ans=1;
    while(b>0){
        if(b&1) ans=ans*a%p;
        a=a*a%p;
        b/=2;
    }
    return ans%p;
}
int main(){
	cin>>n;
	ans=ksm(2,n,mod);
	a[1]=1;
	a[2]=1;
	for(int i=3;i<=n;i++){
		a[i]=a[i-1]+a[i-2];
		a[i]%=mod;
	} 
	cout<<a[n]*ksm(ans,mod-2,mod)%mod;
	
}
```




---

## 作者：dead_X (赞：0)

## 思路
概率题大概率可以转成**合法方案数除以总方案数**的形式，这题也不例外。

总方案数显然有 $2^{n}$ 个，现在开始考虑怎么求合法方案。

注意到由于每个城市只能被**恰好一盏灯**覆盖，因此我们考虑划分整个区间到几段。不难发现每一段的长度都是奇数。

于是问题转化成了覆盖的种类，这不难递推出来。只需要记录奇数和偶数格的前缀和即可。
## 代码
```
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
long long qp(int x,int y)
{
	int ans=1;
	for(int now=x; y; now=now*now%p,y>>=1) if(y&1) ans=ans*now%p;
	return ans;
}
int ans[200003];
signed main()
{
	int n=read();
	ans[0]=1;
	int prea=1,preb=0;
	for(int i=1; i<=n; i++) if(i&1) ans[i]=prea,preb+=ans[i],preb%=p;
	else  ans[i]=preb,prea+=ans[i],prea%=p;
	printf("%lld\n",ans[n]*qp(qp(2,n),998244351)%p);
	return 0;
}
```

---

## 作者：WitheredZeal (赞：0)

这个大猪头在比赛的时候降智了，掉了一堆rating  

都快把D搞出来了又去搞其他题了，结果很慢才做出来，大猪头。  

# 题意  
有$n$个点，每个点有$\dfrac{1}{2}$的概率会有一个信号源。你可以任意选择信号源的强度$a$，如果点$x$上有一个强度为$a$的信号源，那么$\forall |y-x|<a$的点会接收到这个信号源的信号。  
你需要构造信号源强度，使得：  
- $0$号点和$n+1$号点没有被覆盖到  
- $\forall x\in[1,n],x \in \mathbb{N}$，$x$号点恰好被覆盖一次  

问你能成功实现构造的概率。  

# 题解  
所谓的概率，其实就是在数数上面套了个外壳。  
你只需要算出方案数，然后除以$2^n$就行了  


上面这个题意比较复杂，我们考虑转换题意  
现在有$n$个点，我们选择一个强度为$a$的信号源，本质上就是把$2a-1$个点捆绑在了一起，变成了一个点，那么我们可以把题意转换成这样：  
把$n$个点分成若干个段，每段长度都为奇数的方案数。  
这个东西看上去非常可做，它也确实非常可做。  
这里提供一种$O(n)$的解法，不知道有没有大佬会$O(\log n)$的  
我们枚举分成 $i$ 段的方案数  
`for (int i=n;i>=0;i-=2)`  
然后我们考虑这个东西怎么算。  
我们把所有的数加上$1$，但后除以$2$，就变成了将$k=\dfrac{n+i}{2}$个小球放入$i$个盒子里，盒子不可以为空的nt题了  
这个东西是${k-i \choose i-1}$的，证明：隔板法。  
然后预处理组合数就可以$O(n)$解决问题。  
由于组合数是从缺省源上拉过来的，所以开得比较大，关系不大。  
```cpp
#include<bits/stdc++.h>
#define int long long 
#define rd(x) x=read()
using namespace std;
const int N=1e5+5;
const int M=1e6+5;
const int maxn=5e6+5;
const int mod=998244353;
const int inf=0x3f3f3f3f3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline int ksm(int x,int y,int z){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}
inline int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
inline int INV(int x){return ksm(x,mod-2);}
int fac[maxn],inv[maxn];
 
void init()
{
    fac[0]=1;for (int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod;
    inv[maxn-1]=INV(fac[maxn-1]);for (int i=maxn-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m)
{
	if (m==n || m==0) return 1;
	if (m>n || m<0) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
	
}
int n,cnt;
signed main()
{
	init();
	cin>>n;
	for (int i=n;i>=0;i-=2)
	{
		int k=(n+i)/2;
		//将k个小球放入i个盒子中，盒子不同，小球相同，不可空 
		cnt+=C(k-1,i-1);cnt%=mod;
	}
	cout<<cnt*INV(ksm(2,n))%mod<<endl;
}
```

---

