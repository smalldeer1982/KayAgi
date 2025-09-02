# Ehab and the Expected GCD Problem

## 题目描述

我们定义一个函数 $f(p)$，作用于一个排列 $p$。令 $g_i$ 表示 $p_1, p_2, \ldots, p_i$ 的最大公约数（即长度为 $i$ 的前缀的最大公约数）。那么 $f(p)$ 就是 $g_1, g_2, \ldots, g_n$ 中不同元素的个数。

令 $f_{max}(n)$ 表示所有 $1, 2, \ldots, n$ 的排列 $p$ 中 $f(p)$ 的最大值。

给定整数 $n$，请计算有多少个排列 $p$ 满足 $f(p) = f_{max}(n)$。由于答案可能很大，请输出其对 $1000000007 = 10^9 + 7$ 取模的结果。

## 说明/提示

以第二个样例为例，长度为 $3$ 的排列如下：

- $[1,2,3]$，$f(p)=1$。
- $[1,3,2]$，$f(p)=1$。
- $[2,1,3]$，$f(p)=2$。
- $[2,3,1]$，$f(p)=2$。
- $[3,1,2]$，$f(p)=2$。
- $[3,2,1]$，$f(p)=2$。

最大值 $f_{max}(3) = 2$，满足 $f(p)=2$ 的排列有 $4$ 个。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
```

### 输出

```
4```

## 样例 #3

### 输入

```
6
```

### 输出

```
120```

# 题解

## 作者：AThousandSuns (赞：25)

在我的博客食用效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/10987188.html)

一道 Div. 2 的难度 2500 的题，真的不是吹的……

首先考虑排列的第一个数 。假如分解质因子后为 $\prod p_i^{c_i}$，那么此时排列价值的最大值为 $\sum c_i$。

为什么？因为如果 $\gcd$ 变了，那么一定变成原来 $\gcd$ 的约数。每次变化 $\sum c_i$ 至少 $-1$。所以最大值就是 $\sum c_i$。

那么排列的价值达到最大值，只有在第一个数的 $\sum c_i$ 达到最大值才可能，并且每次 $\gcd$ 变化只会令 $\sum c_i$ 减小 $1$。

首先发现，质因子 $p_i$ 中不会有 $\ge 5$ 的数。因为此时可以把 $p_i$ 变成 $2^2$，$\sum c_i$ 更大且仍然合法。

然后，设分解质因子后 $3$ 的次数为 $c$，那么 $0\le c\le 1$。因为当 $c\ge 2$ 时，可以把 $3^2$ 变成 $2^3$，$\sum c_i$ 更大且仍然合法。

所以第一个数可以被表示成 $2^x3^y$，其中 $y\in\{0,1\}$。

那么就能上DP了。~~（为什么每次都那么突然……）~~

设 $f[i][x][y]$ 表示目前填了前 $i$ 位，当前的 $\gcd$ 是 $2^x3^y$，的总合法序列数。

初始状态 $f[1][\lfloor\log_2n\rfloor][0]=1$。如果 $2^{\lfloor\log_2n\rfloor-1}\times 3\le n$，那么还有 $f[1][\lfloor\log_2n\rfloor-1][1]=1$。其它的状态无用，只有这两个状态的 $x+y$ 达到了最大值。

答案为 $f[n][0][0]$。因为排列包含 $1$，所以 $\gcd$ 一定会变为 $1$。

如何转移？（以下设 $cnt(x)=\lfloor\frac{n}{x}\rfloor$，即 $x$ 的倍数的个数）
- $\gcd$ 不变。那么 $f[i][x][y]+=f[i-1][x][y](cnt(2^x3^y)-(i-1))$。因为新选择的数可以是且一定是 $2^x3^y$ 的倍数。然而前 $i-1$ 个位置都是 $2^x3^y$ 的倍数，所以要减掉。
- $\gcd/2$，也就是 $x--$（此时要求 $x<\lfloor\log_2n\rfloor$）。那么 $f[i][x][y]+=f[i-1][x+1][y](cnt(2^x3^y)-cnt(2^{x+1}3^y))$。因为新选择的数一定是 $2^x3^y$ 的倍数，但一定不是 $2^{x+1}3^y$ 的倍数（否则 $\gcd$ 不变）。前 $i-1$ 个位置都是 $2^{x+1}3^y$ 的倍数，所以不用减掉。
- $\gcd/3$，也就是 $y--$（此时要求 $y=0$）。那么 $f[i][x][y]+=f[i-1][x][y+1](cnt(2^x3^y)-cnt(2^x3^{y+1}))$。

时间复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=1000100,mod=1000000007;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,lt,f[maxn][21][2];
inline int cnt(int x){return n/x;}
int main(){
	n=read();
	lt=log2(n);
	f[1][lt][0]=1;
	if((1<<(lt-1))*3<=n) f[1][lt-1][1]=1;
	FOR(i,2,n) FOR(j,0,lt){
		f[i][j][0]=(1ll*f[i-1][j][0]*(cnt(1<<j)-(i-1))+1ll*f[i-1][j+1][0]*(cnt(1<<j)-cnt(1<<(j+1)))+1ll*f[i-1][j][1]*(cnt(1<<j)-cnt((1<<j)*3)))%mod;
		f[i][j][1]=(1ll*f[i-1][j][1]*(cnt((1<<j)*3)-(i-1))+1ll*f[i-1][j+1][1]*(cnt((1<<j)*3)-cnt((1<<(j+1))*3)))%mod;
	}
	printf("%d\n",f[n][0][0]);
}
```

---

## 作者：zombie462 (赞：8)

$O(n)$的做法：

显而易见的结论：

质因子最多的一个数一定能写成$2^x\times3^y$的形式$(y\leq 1)$。

因为如果有$>3$的质因子，那么可以用$2^2$替代。

如果$y\leq2$，那么可以用$2^3$替代。

所以在搜索的某一步：

使得$b_i$不变的数是一样的；

使得$b_i/2$的数是一样的；

使得$b_i/3$的数是一样的。

搜索的时候放在一起就可以了。

此时可以写出$O(C^n_{2n})$的代码

第一步优化：

设$dp_{i,x,y}$表示选了$i$个数，当前$gcd$是$2^x\times3^y$的方案数；

设$f_{x,y}$表示$1\to n$中有多少个数的因子包含$2^x\times3^y$。

若填完这个位置$gcd$不变：

$dp_{i+1,x,y}=dp_{i+1,x,y}+dp_{i,x,y}\times(f_{x,y}-i)$

若填完这个位置$gcd/2$：

$dp_{i+1,x-1,y}=dp_{i+1,x-1,y}+dp_{i,x,y}\times(f_{x-1,y}-f_{x,y})$

若填完这个位置$gcd/3$：

$dp_{i+1,x,y-1}=dp_{i+1,x,y-1}+dp_{i,x,y}\times(f_{x,y-1}-f_{x,y})$

使用记忆化搜索可以使得时间复杂度为$O(n\log n)$。

但是我们还可以优化：

第二步优化：

考虑优化记忆化搜索：

可以发现当前还没填的数，如果填了$gcd$不变的话，那么这个数填在之后任意一个位置都是可以的，直接用组合数计算即可，然后进入下一层。

最终复杂度：

阶乘预处理$O(n)$。

逆元预处理$O(n)$。

记忆化搜索$O(\log n)$。

总时间复杂度$O(n)$。

可以过$n\leq 10^7$的数据。

代码：

```
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define G 11111111
#define mod 1000000007
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
LL f[31][2];
LL fac[G],inv[G];
int n,M;
LL dfs(int left,int x,int y){
	LL tmp[31][2]; //tmp是寄存数组，所以必须是局部变量。用来暂时保存f数组的值
	for (int i=0;i<=M;++i){ //保存f数组的值
		for (int j=0;j<=1;++j){
			tmp[i][j]=f[i][j];
		}
	}
	LL tot=0; //tot记录f数组内的和
	for (int i=x;i<=M;++i){ 
		for (int j=y;j<=1;++j){
			tot+=f[i][j]; 
			f[i][j]=0;
		}
	}
	if (!x && !y){ 
		for (int i=0;i<=M;++i){ //还原f数组的值
			for (int j=0;j<=1;++j){
				f[i][j]=tmp[i][j];
			}
		}
		return fac[tot]; //直接返回阶乘
	}
	LL ans=0;
	if (x) ans+=dfs(left-tot,x-1,y); //如果可以使gcd/=2，递归
	if (y) ans+=dfs(left-tot,x,y-1); //如果可以使gcd/=3，递归
	for (int i=0;i<=M;++i){ //还原f数组的值
		for (int j=0;j<=1;++j){
			f[i][j]=tmp[i][j];
		}
	}
	return fac[left-1]*inv[left-tot]%mod*tot%mod*ans%mod; //返回结果
}
int main(){
	n=read();
	fac[0]=1;
	for (int i=1;i<=n;++i) fac[i]=fac[i-1]*i%mod; //预处理阶乘
	inv[0]=inv[1]=1;
	for (int i=2;i<=n;++i) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for (int i=1;i<=n;++i) inv[i]=inv[i]*inv[i-1]%mod; //预处理逆元的阶乘
	//预处理f数组，具体见上面解析
	f[0][0]=n;
	for (M=1;f[M-1][0];++M){
		f[M][0]=f[M-1][0]>>1;
	} 
	M-=2;
	for (int i=0;i<=M;++i){
		f[i][0]-=f[i+1][0];
	}
	f[0][1]=n/3;
	for (int i=1;i<M;++i){
		f[i][1]=f[i-1][1]>>1;
	}
	for (int i=0;i<M;++i){
		f[i][1]-=f[i+1][1];
	}
	for (int i=0;i<=M;++i){
		f[i][0]-=f[i][1];
	}
	//预处理结束
	LL ans=dfs(n,M,0); //不考虑3的情况
	if ((1<<(M-1))*3<=n) ans+=dfs(n,M-1,1); //考虑3的情况
	cout<<ans%mod<<endl; //输出
	return 0;
}

```


---

## 作者：henrytb (赞：5)

[更好的阅读体验](https://blog.henrytb.ml/2021/06/%E9%A2%98%E8%A7%A3-CF1174E-Ehab-and-the-Expected-GCD-Problem/)

毒瘤 dp 题。

首先显然可以莽一波结论。

可以发现，当排列的第一个数 $a_1=\prod p_i^{c_i},p_i\ \text{is prime}$ 时，题目中所求排列的权值最大值为 $\sum c_i$。

这是因为在第二个数及以后，前缀 $\gcd$ 只会减小，不会增加，而且最好的情况是每次减小一个质因子。可以证明只要有一个确定的第一个数，该最好情况一定可以实现。

那么我们可以考虑找出使 $\sum c_i$ 最大的一个数 $a_1$。

再来猜一波：这个 $a_1$ 的可能性不会太多，它的质因子得小。因为如果有比较大的质因子的话，它的指数 $c_i$ 就会被压榨，会比质因子更小的情况劣。

那么质因子得有多小呢？我们先猜：这个 $a_1=2^x$。

这种情况确实很优，但不久后我们还会发现，$2^x\cdot 3^y$ 似乎也很可以。

但是到 $2^x\cdot 3^2$ 之后就爆炸了，因为有一个比它小但质因数分解后的指数和比它大的数 $2^{x+3}$。

因此，质因子 $3$ 的次数不能大于 $1$。

那么能不能有比 $3$ 大的质因子呢？显然不能。因为 $5>2^2$，用了 $5$ 及以上的不如用一堆 $2$ 来代替。

那么我们可以得出结论：$a_1$ 只能等于 $2$ 的若干次方，或者 $2$ 的若干次方乘上 $3$。

那么就可以愉快设 dp 状态了：令 $f_{i,j,k}$ 表示到了该排列的第 $i$ 个数，当前前缀 $\gcd=2^j\cdot 3^k$ 时，有多少种情况。

转移可以分三类讨论：

- 若加入一个数后 $\gcd$ 不变，那么 $f_{i+1,j,k}$ 需要加上 $f_{i,j,k}\cdot\left(\left\lfloor\frac{n}{2^j\cdot 3^k}\right\rfloor-i\right)$。因为 $\gcd$ 不变，那么加入的数一定是当前 $\gcd$ 的倍数，需要注意前面的所有数一定都是当前 $\gcd$ 的倍数，不可以选已经选过的数，于是情况数需要 $-i$。
- 若加入一个数后 $\gcd$ 变少了 $2$ 倍，那么 $f_{i+1,j-1,k}$ 需要加上 $f_{i,j,k}\cdot\left(\left\lfloor\frac{n}{2^{j-1}\cdot 3^k}\right\rfloor-\left\lfloor\frac{n}{2^{j}\cdot 3^k}\right\rfloor\right)$。由于 $\gcd$ 变少两倍，那么新加入的数一定得是 $\frac{\gcd}{2}$ 的倍数，但它不能是 $\gcd$ 本身的倍数，因为这样的话 $\gcd$ 就不会改变了。而在 $\frac{\gcd}{2}$ 的倍数和 $\gcd$ 本身的倍数中，都考虑了一遍已经加入过的数，抵消掉了，因此不会加入重复的数。
- 若加入一个数后 $\gcd$ 变少 $3$ 被，那么 $f_{i+1,j,k-1}$ 需要加上 $f_{i,j,k}\cdot\left(\left\lfloor\frac{n}{2^{j}\cdot 3^{k-1}}\right\rfloor-\left\lfloor\frac{n}{2^{j}\cdot 3^k}\right\rfloor\right)$。由于 $\gcd$ 变少两倍，那么新加入的数一定得是 $\frac{\gcd}{3}$ 的倍数，但它不能是 $\gcd$ 本身的倍数。类似地，在 $\frac{\gcd}{3}$ 的倍数和 $\gcd$ 本身的倍数中，也抵消掉了重复的数。因此这么干是对的。

代码实现上因为 $3$ 只有可能是 $0$ 次方或 $1$ 次方，可以用三目运算符判断更加方便。

PS：这题十分卡常，还卡 `long long` 数组（如果 `dp` 数组用 `long long` 的话会炸）的空间。我是用火车头 $+$ C++17 才过的（

```cpp
// 代码就不放火车头了
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int mod=1e9+7;
int n;
int dp[1000005][21][3];
int qaq(int x,int y) {
    return (1<<x)*(y?3:1)%mod;
}
int main() {
    scanf("%d",&n);
    int hav3=log2(n/3)+1;
    int nhav3=log2(n);
    dp[1][nhav3][0]=1;
    if(hav3==nhav3) dp[1][nhav3-1][1]=1;
    rep(i,1,n-1) {
        rep(j,0,nhav3) {
            rep(k,0,1) {
                dp[i+1][j][k]=1ll*(1ll*dp[i+1][j][k]+dp[i][j][k]*(1ll*n/qaq(j,k)%mod-i+mod)%mod+mod)%mod;
                if(j>0) dp[i+1][j-1][k]=1ll*(1ll*dp[i+1][j-1][k]+dp[i][j][k]*(1ll*n/qaq(j-1,k)%mod-n/qaq(j,k)%mod)%mod+mod)%mod;
                if(k>0) dp[i+1][j][k-1]=1ll*(1ll*dp[i+1][j][k-1]+dp[i][j][k]*(1ll*n/qaq(j,k-1)%mod-n/qaq(j,k)%mod)%mod+mod)%mod;
            }
        }
    }
    printf("%d\n",dp[n][0][0]);
    return 0;
}
```

---

## 作者：xukehg (赞：2)

题解的复杂度都是 $O(n \log n)$ 或者好写的 $O(n)$ 的 dp 做法，我来一发好理解的~~极为难写的~~ $O(n)$ 纯数学做法。

## 题目大意

- 对于一个 $1 \sim n$ 的排列 $p$，称其**权值**为前缀 $\gcd$ 的不同值个数。
- 设所有排列的最大权值为 $x$，问有多少个排列 $p$ 的权值真的能达到 $x$。
- $n \le 10 ^ 6$。

## 题目解决

设 $p$ 的前缀 $\gcd$ 为 $q$，一个显然的观察是 $q_i$ 整除 $q_{i-1}$。更进一步地，由于 $q_i$ 每次降低会变为原来的至多 $\dfrac{1}{2}$，所以 $x \le \log_2 n$。$x = \left\lfloor\log_2 n\right\rfloor$ 的构造也是容易的，只需令 $q$ 依次为 $2$ 的幂次即可。

考虑符合题意的 $q$ 的数量。设 $k_i = \dfrac{p_i}{p_{i+1}}$，讨论 $k_i$ 的取值：
- 若其中不含有 $\ge 3$ 的值，即为上述构造的情况。
- 若其中含有 $\ge 3$ 的值，不难发现这样的值出现次数至多为 $1$：如果出现 $\ge 2$ 次，由于 $3 ^ 2 > 2 ^ 3$，可知显然不优。

考虑对 $q_i$ 去重（下同），去重后情况数是 $O(\log n)$ 级别的，不妨大力枚举。

记 $S_i$ 表示为 $q_i$ 的倍数但不为 $q_{i-1}$ 倍数的数构成的集合，并设 $h_i=|S_i|$，共有 $l$ 个数（事实上 $l = x$）。枚举改变前缀 $\gcd$ 的那些数，称之为关键数，可知第 $i$ 个关键数有 $h_i$ 种可能，先令 $res = \prod h_i$。

把 $\gcd$ 相同的区间分成若干个块，则从后往前数第 $i$ 个块的第一个数即为关键数。不难发现，对于任意块都有关键数是该块中下标的最小值，考虑倒着插入数字。

首先，$S_l$ 中的数显然只能放在第一个块中。由于关键数已经确定，所以新加进来的数只能放到关键数的后面。因此，对于第一个数的放置，只有一种情况；第二个数的放置，有 $2$ 种情况，即第一个数的前面或后面。显然可以发现，每放一个数，就增加了一个可以放数的位置。综上，$S_l$ 中的数的放置有 $(h_1 - 1)!$ 种情况。注意已经放了一个数当关键数。

考虑 $S_{l - 1}$ 中的数的放置。它不仅可以在第 $l - 1$ 块中放置，而且可以在 $l$ 号块放置，对于 $S_{i}$ 中数的放置也同理。注意到已有的可以放置的位置的数量是固定的，我们可以设计出递推的方法：记 $i - 1$ 号块到第 $1$ 号块的位置数量为 $kw$，则第 $i$ 号块的方案数为 $kw \times (kw + 1) \times\dots\times(kw + h_i - 2)$ 种情况，可以预处理阶乘逆元 $O(1)$ 得出。

许多细节：

- 如果 $h_i = 1$，跳过对这个块贡献的计算，并注意其仍然提供了一个位置；
- $q_l \neq 3$。

然后我们就愉快的通过了这道 2500 的题目。

[记录。](https://codeforces.com/contest/1174/submission/293330829)

---

## 作者：cjZYZtcl (赞：2)

首先不难发现符合条件的排列的前缀 $\gcd$ 序列每次减少量都是一个质因子，且最大项只会形如 $2^x$ 或 $2^x3$。

#### 证明：

首先第一个结论，由于去掉质因子能使最终序列的 $f(p)$ 值等于序列第一个数质因子个数，显然是使 $f(p)$ 最大的构造方案。

然后第二个结论，考虑到每次去掉质因子时去掉 $2$ 最优，所以最后序列的 $f(p)$ 一定等于 $\lfloor \log_2{n} \rfloor + 1$。

此时尝试将一些位置去掉的质因子由 $2$ 更改为更大的。

如果更改后的质因子 $\ge 5$，则可以从中拆分出至少 $2^2$，$f(p)+1$，显然更优。

如果更改后的质因子为 $3$，则不难发现 $3^2 \ge 2^3$，所以至多有一个位置被更改为 $3$。

证毕。

记 $S(p)$ 表示排列 $p$ 的前缀 $\gcd$ 序列中不同的数构成的集合。

所以符合条件的排列的 $S(p)$ 的种类只有 $\log_2{n}$ 级别，且 $|S(p)| = \lfloor \log_2{n} \rfloor + 1$，可以暴力求出。

接下来考虑已知所有不同的 $S(p)$ 之后如何计算答案。

首先记 $a_i$ 表示 $S(p)$ 中第 $i$ 大的数。

显然 $\forall 1 \le i < j \le \lfloor \log_2{n} \rfloor +1,\ a_i | a_j$。

所以我们记 $cnt_i$ 表示是 $a_i$ 的倍数但不是 $a_{i+1}$ 的倍数的数的个数，这个显然可以简单容斥求出。

考虑构造排列的限制条件。

不难发现对于所有 $i > 1$，在所有非 $a_i$ 倍数的数左侧，都需要有至少一个是 $a_i$ 倍数的数。

记 $s_i = \sum\limits_{j=1}^i cnt_j$。

则对于一个 $S(p)$，答案为：

$$\prod_{i=1}^{\lfloor \log_2{n} \rfloor +1} \tbinom{s_i - 1}{cnt_i - 1} \times cnt_i!$$

直接计算即可。

时间复杂度 $O(n)$。

[Code](https://codeforces.com/contest/1174/submission/229998590)

---

## 作者：chenxia25 (赞：2)

![](https://s3.ax1x.com/2020/12/23/rcMXoq.png)

我太菜了/yun 我通篇抄题解/yun 我是傻逼/yun

---

首先莽算是不行的，那样就是莽夫，而我们应该集《智慧和勇敢》于一身。观察得出结论：显然对第一个数 $x=\prod p_i^{\alpha_i}$ 的 $f$ 值上限为 $\sum \alpha_i$，而它显然是能取到的。于是第一个数的 $\sum\alpha_i$ 值需要尽可能大，贪心地取 $p=[2]$。那还可能有别的相等的吗？可能把其中一个 $2$ 改成 $3$（只要 $\leq n$），再多 $3$ 就不可能了，因为 $3^2>2^3$。$5$ 以上也不可能有了，因为 $5>2^2$。

那么我们就考虑如何计算方案数。显然每次改变 $\gcd$ 是新加入一个数使得当前 $\gcd$ 的 $2$ 或 $3$ 的指数 $-1$。很自然的想到一个 DP：$dp_{i,j,k}$ 表示考虑到第 $i$ 位，当前 $\gcd$ 是 $2^j3^k$ 的方案数。这样状态数是线对的，不用愁。然后我就不会了，看了题解发现我是傻逼。

我当时想的是，枚举上一个改变 $\gcd$ 的点，然后用组合数转移。那这样就是平方对数，然后 $(i+j)!$ 的形式又拆不开，不好优化。但实际上我们只需要向 $i-1$ 转移即可……分为三类：$\gcd$ 不变、$2$ 的指数变、$3$ 的指数变。每类在 DP 值前面乘的系数显然是位置 $i-1$ 可以填的数的个数，这个很好算就是了，可能要容斥一下，$n$ 以内 $x$ 的倍数个数就是 $\left\lfloor\dfrac nx\right\rfloor$。所以说有的时候 DP 感觉不可优化了，这时候大概率不是我的相关水平不够，而是转移思路和状态设计需要改一改了……

代码异常好写，复杂度线对。

**_[code](https://www.luogu.com.cn/paste/1ocsishu)_**

---

然后看到题解区有线性做法，去 read 了一下，这不是我想这题的时候想了一段时间然后误认为假了的做法之一吗？

我们考虑枚举整个 $\gcd$ 变化情况，如果全 $2$ 那显然只有一种，如果有 $3$ 那就枚举最后一次出现 $3$ 的位置，是对数的。那考虑对每一种情况算方案数。

我们假设已经固定了改变 $\gcd$ 的 $\log$ 个关键数，显然每个关键数序列是等价的，最后简单乘法原理一下即可。然后我们需要算非关键数的合法排列方案数。显然每个数所能在的区域是一个后缀。因为这个位置比较灵活，就像细胞内的某结构一样，我们考虑这样一个常见思路，把数们一个一个扔进去然后把所有数在被扔进去的时刻可插入的空隙数乘起来。那么后缀不同的显然分为 $\log$ 类，每类数一起插（顺序无所谓）的话，那就是一个等差数列求积，这个阶乘阶乘逆元即可。于是这一部分是二次对数的。

然后阶乘逆元也可以线性求，就做到了线性。

**_[code](https://www.luogu.com.cn/paste/cax8ag9y)_**

---

## 作者：FutaRimeWoawaSete (赞：2)

此题是正睿课上一道 $DP$ 好题。写TJ纪念一下。  
方法：找结论 +  $DP$ 。    
首先像这类全建立在结论上面的 $DP$ ，我们首先得推结论。  
其实也不能用这种毫无思路的方法说，我们首先拿到这道题，发现从时间复杂度分析我们至少需要一个 $O(nlogn)$ 的算法才能跑过这道题。  
在根据题目的性质，我们发现我们的 $logn$ 应该是用在处理 $GCD$ 或者是处理因数级别方面上的。  
~~粗略地分析一道后~~我们就还是回到题目本身：  
题目有一个很有特色的序列权值计算方式，又由于它说的是求权值最大的序列，是否可以从这里先入手？  
我们先着手在这个序列上作一些研究。  
我们发现数列的第一个数决定了整个序列的权值上限，这点很容易发现。  
我们假设序列的第一个数为$x = p1 ^ {k1} * p2 ^ {k2} * p3 ^ {k3}……$，其中${p1 , p2 , p3 ……}$ 均为质数，$k1 , k2 , k3……$ 均为正整数。   
不难发现我们的 $前缀GCD$ 必然是在 $x$ 的各个质因子的指数上进行不上升操作。  
再进一步思考，我们发现这个 $前缀GCD$ 每在其中任意一个质因子的指数上减1， $GCD$ 的种类就会增多。  
令一个以 $x$ 开头的数的序列的权值上限为 $val(x)$ 。  
所以$val(x) = \sum_{i = 1}{ki}$  
想到这里，我们的思路就变得清晰起来了：  
因为一个以 $x$ 开头且权值为 $val(x)$ 的序列一定能被组合出来。  
所以我们直接用贪心考虑所有序列的最优解。  
很显然，$2 ^ 2$可以替换任何一个除 $3$ 以外的质因子的 $1$ 次方，~~还很显然~~的就是 $2 ^ 3$可以替换 $3 ^ 2$。  
这句话很简单，却是本题的关键所在。  
由此我们可以得出两个结论：  
```
1.最优解开头的数一定要 val(x) 尽量大，所以我们就尽量多选 2 ；  
2.最优解开头的数一定只能选择 2 , 3 两个数，并且 3 
的个数只能为 1 or 0 ；
```
其实也很好理解这两个结论：你选一个比 $3$ 大的质因子还不如选 $2$ 个 $2$  ； 你选 $2$ 个 $3$ 还不如选择 $3$ 个 $2$ 。  
于是我们 $DP$ 状态定义就出来了：  

 $dp[i][j][k]$ 表示当前选到了第 $i$ 个位置且此时前缀 $GCD$ 为 $2 ^ j * 3 ^ k$ 。  
 
初始化也很简单，直接看一下我们最优的情况是 $2$ 种还是 $1$ 种然后直接初始化就行了。  
接着我们就考虑状态转移方程。  
当一种状态解决完后，我们的 $GCD$ 只会保持不变，$2$ 的指数减 $1$ ， $3$ 的指数减 $1$ 三种情况。  
为了方便表示，令 $Cnt(x , y) = 2 ^ x * 3 ^ y$。  
对于一个 $dp[k][i][j]$ 
对于第一种情况，我们下一个可以取的只有为 $Cnt(i , j)$ 的倍数。所以直接用 $1 ~ n$ 中 $Cnt(i , j)$ 倍数的个数减去前面已经选了的数的个数(前面选了的数肯定是 $Cnt(i,j)$ 的倍数啊)  
状态转移方程：  
```cpp
dp[k][i][j] += (n / cnt(i,j) - (k - 1)) * dp[(k - 1)][i][j]  
```  
对于第二种情况，我们只用在之前的套路上套下来就行了，不过这里需要注意的是我们还需要减去 $cnt(j + 1 , k)$ 的合理倍数个数。  
第三种情况与第二种情况类似，就是把 $2$ 换成 $3$ 了嘛。  
最后的答案储存在 $dp[n][0][0]$ 中，这道题结束了。  
空间起飞了的同学滚动数组滚一滚就好了。  
代码实现的不是很精练，请读者见谅。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 1e6 + 5;
const long long mod = 1e9 + 7;
long long dp[3][35][2],n,m,c[35][2];
int main()
{
	scanf("%lld",&n);
	int idx = 0,res = 1;
	while(res <= n)
	{
		idx ++;
		res *= 2;
	}
	idx --;
	res = 1;
	c[0][0] = 1 , c[0][1] = 3;
	for(int i = 1 ; i <= idx ; i ++)
	{
		res *= 2;
		for(int j = 0 ; j <= 1 ; j ++)
			c[i][j] = res * ((j == 1) ? 3 : 1);
	}
	if(res / 2 * 3 <= n) dp[1][idx][0] = dp[1][idx - 1][1] = 1;
	else dp[1][idx][0] = 1;
	for(int i = 2 ; i <= n ; i ++)
	{
		for(int j = 0 ; j <= idx ; j ++)
			for(int k = 0 ; k <= 1 ; k ++)
			{
				dp[i % 2][j][k] = 0;
				dp[i % 2][j][k] += (n / c[j][k] - (i - 1)) * dp[(i - 1) % 2][j][k] , dp[i % 2][j][k] %= mod;
				if(j + 1 <= idx) dp[i % 2][j][k] += (n / c[j][k] - n / c[j + 1][k]) * dp[(i - 1) % 2][j + 1][k] , dp[i % 2][j][k] %= mod;	
				if(k == 0) dp[i % 2][j][k] += (n / c[j][k] - n / c[j][k + 1]) * dp[(i - 1) % 2][j][k + 1] , dp[i % 2][j][k] %= mod;
			}
	}
	printf("%d\n",dp[n % 2][0][0] % mod);
	return 0;
} 
```

---

## 作者：「QQ红包」 (赞：2)

菜的人不会dp。

强行解释：我空间优秀！

结论：

$n=\prod p_i^{a_i}$，$\sum a_i$ 最大的时候可以作为开头。如果前缀gcd相同，我们称这些数在同一层。因为最优的方案肯定是在层数变化的时候，某个次数-1.

只有可能是$2^x$ 或者 $2^{x-1}*3$ （因为$3^2>2^3$，如果要取大于等于 $2$ 个 $3$ 不如选$2^3$）

如果第一个数为$2^x$ ，

我们设$f_i$ 为满足 $i\mod 2^{f_i}=0$ 的最大的数。

根据$f_i$我们可以分成log层（ $i$ 所在的层为 $f_i$ ），然后我们在每一层取一个数$x$，表示gcd是通过这个数从$2^{f_x+1}$变化为$2^{f_x}$（或者是作为开头）。假设这些 $x$ 构成一条`主链`

这样的方案数是每层的数的个数的乘积。

考虑剩余的数的方案。每一个数，可以放在这一层中的第一个数的后面的任意位置。

好像这样表述不是很清楚，举个栗子。

假设目前的gcd为$2^{10}$，假装是$2^{10}$这一层最先放的。然后这一层还有$2^{10}\times 3,2^{10}\times 5$ 这两个数。

这两个数可以放 在gcd变成$2^{10}$后 的任意位置，都不会影响结果。

这个部分我们可以从小到大算来求方案数。

举例：

若 n=6 ，若主链为`4,2,1`

0层：`1,3,5`

1层：`2,6`

2层：`4`

我们先放`3,5`，有$1\times 2$ 种方法，

然后放`6`，有 $4$ 种方法（因为此时 $2$ 后面有 $3$ 个数，构成 $4$ 个间隔。

如果第一个数为$2^x\times 3$ ，枚举$x$表示在gcd为$2^x\times 3$之后变成$2^x$，

区别在于，分层的时候，$f_i>x$且 $i\mod 3\not=0$ 分在 $x$ 层，$f_i\ge x$ 且$i\mod 3=0$ 分在$f_i+1$层

然后还是分层直接算，具体参考代码。


```cpp
/*
 * Author: ylx
 * Lang: c++
 * Prog: E
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void qmax(int &x, int y)
{
	if (x < y)
		x = y;
}
void qmin(int &x, int y)
{
	if (x > y)
		x = y;
}
inline ll read()
{
	char s;
	ll k = 0, base = 1;
	while ((s = getchar()) != '-' && s != EOF && !(isdigit(s)))
		;
	if (s == EOF)
		exit(0);
	if (s == '-')
		base = -1, s = getchar();
	while (isdigit(s))
		k = k * 10 + (s ^ '0'), s = getchar();
	return k * base;
}
inline void write(ll x)
{
	static char cnt, num[20];
	cnt = 0;
	if (!x)
	{
		putchar('0');
		return;
	}
	for (; x; x /= 10)
		num[++cnt] = x % 10;
	for (; cnt; putchar(num[cnt--] + 48))
		;
}
const ll mod = 1e9 + 7;
const int maxn = 1e6 + 10;
int N, n;
int vis[maxn], Max; //is best ans?
int prime[maxn], tot;
bitset<maxn> p;
void work1()
{
	for (int i = 2; i <= N; i++)
	{
		if (!p[i])
		{
			tot++;
			prime[tot] = i;
		}
		for (int j = 1; j <= tot; j++)
		{
			if (prime[j] * i > N)
				break;
			p[i * prime[j]] = 1;
			if (i % prime[j] == 0)
				break;
		}
	} //筛素数
}
void check(int x)
{
	int X = x;
	for (int i = 1; i <= tot && (ll)prime[i] * prime[i] <= x; i++)
		if (x % prime[i] == 0)
		{
			while (x % prime[i] == 0)
			{
				x /= prime[i];
				vis[X]++;
			}
			if (x == 1)
				break;
		}
	if (x != 1)
		vis[X]++;
	qmax(Max, vis[X]);
}
bool Flag;
ll ans;
int f[maxn][2], g[maxn]; //g[i]表示层。
int s[30];
void add()
{
	ll sum = 1, s1 = 1;
	for (int i = Max; i >= 0; i--)
		sum = sum * s[i] % mod;
	int z = 0;
	for (int i = 0; i <= Max; i++)
	{
		for (int j = 1; j < s[i]; j++)
		{
			z++;
			s1 = s1 * z % mod;
		}
		z++;
	}
	sum = sum * s1 % mod;
	ans =(ans+ sum)%mod;
}
void get_ans1()
{
	memset(s, 0, sizeof(s));
	memset(g, 0, sizeof(g));
	for (int i = 1, x; i <= n; i++)
	{
		x = i;
		while (x % 2 == 0)
			f[i][0]++, x /= 2;
		if (i % 3 == 0)
			f[i][1] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		g[i] = f[i][0];
		s[g[i]]++;
	}
	add();
}
void get_ans2(int P)
{
	memset(s, 0, sizeof(s));
	memset(g, 0, sizeof(g));
	for (int i = 1; i <= n; i++)
	{
		if (f[i][1] && f[i][0] >= P)
			g[i] = f[i][0] + f[i][1];
		else
			g[i] = min(P, f[i][0]);
		s[g[i]]++;
	}
	add();
}
int main()
{
#ifdef ylx
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	Flag = false;
	n = read();
	N = n;
	work1();
	for (int i = 1; i <= n; i++)
		check(i);
	for (int i = 1; i <= n; i++)
	{
		vis[i] = (Max == vis[i]);
		if (vis[i] && i % 3 == 0)
			Flag = true;
	}
	get_ans1();
	if (!Flag)
	{
		printf("%lld\n", ans);
		return 0;
	}
	for (int i = Max - 1; i >= 0; i--) //2^i*3后变成2^i
	{
		get_ans2(i);
	}
	printf("%lld\n", ans);
	return 0;
}
//2019年 06月 13日 星期四 19:17:55 CST
```

---

## 作者：Azazеl (赞：1)

### CF1174E Ehab and the Expected GCD Problem 题解

#### 题意

> $~~~~$ 定义一个长度为 $n$ 的排列的权值在其前缀 $\gcd$ 中仅出现过一次的数的个数，求有多少个排列的权值最大。

---

#### 题解 

$~~~~$ 比较神仙，但感觉 2500评到黑还是有点勉强。  

$~~~~$ 首先读清楚题，求**不同的数的个数**。首先我们知道前缀 $\gcd$ 一定是一个单调不升的序列，因此排列的**第一个数**一定已经把以它开头的排列的值固定了。  

$~~~~$ 令排列的第一个数为 $p$，并得到它的惟一分解（即分解质因数）。不妨设 $p=\prod k_i^{c_i}$ ，那么这个排列的权值最大只会是$\sum c_i$ 。因为每一次的 $\gcd$ 前缀单调递减，如果我们想让当前的数有贡献，那么下一个数一定要在当前数的分解基础上选一个 $c_i$ 减掉一，否则这两个点都不会有贡献，显然不会更优。  

$~~~~$ 所以第一个数一定要让 $\sum c_i$ 最大，那么什么时候会让 $c_i$ 更大呢？考虑可能的最小的质因子 $2$ ，发现若我们有 $2$ 个 $2$ 的质因子，那么它的效果一定比有一个 $5$ 的质因子更优。因为如果有一个数 $k\times 5\leq n$ ，那么也一定有 $k\times 2^2 \leq n$ 。此时 $\sum c_i$ 甚至更大，当然若因子大于 $5$ 更是如此。所以所有 $k_i$ 一定只有 $2,3$ 两种情况。再来考虑 $2$ 的更高次，发现 $8=2^3<3^2=9$ ，因此同上的原因，$3$ 的最高次是 $1$ 。  

$~~~~$ 综上，第一个数只有两种可能，$2^{\lfloor \log_2^n \rfloor}$ ，同时如果 $2^{\lfloor \log_2^n \rfloor-1}\times 3\leq n$ ，那么这也是满足条件的，此后的 $\gcd$ 也一定只是在第一个的基础上选择系数 $-1$ .  

$~~~~$ ~~自然而然想到~~可以 $\texttt{DP}$ 每一个数的前缀 $\gcd$ ，每一次有当前位置，$\gcd$ 的 $2$ 的系数，$3$ 的系数，同时这个系数一定 $\in[0,1]$ 。所以设 $dp_{i,j,k}$ 表示当前在 $i$ 位置，前缀 $\gcd$ 为 $2^j+3^k$ 。  

$~~~~$ 由于每次系数 $-1$ 或者不变一定才会保持最优，所以我们分三种情况讨论即可。  

$~~~~$ 下文为了方便，设 $\operatorname{calc(i)}$ 表示在 $n$ 以内 $i$ 的倍数个数，计算自然是 $\lfloor \dfrac{n}{i} \rfloor$.

1. $\gcd$ 前缀不变，那么对当前位置贡献为 $dp_{i-1,j,k} \times  (\operatorname{calc(2^j\times 3^k)-(i-1)})$ .  
2. $\gcd$ 中 $2$ 的系数 $-1$ ，那么对当前位置贡献为 $dp_{i-1,j+1,k}\times (\operatorname{calc(2^j\times 3^k)-calc(2^{j+1}\times 3^k)})$ 
3. $\gcd$ 中 $3$ 的系数 $-1$ ，那么对当前位置贡献为 $dp_{i-1,j,k+1}\times (\operatorname{calc(2^j\times 3^k)-calc(2^j\times 3^{k+1})})$ .  

$~~~~$ 注意到第三种情况不能在 $k=1$ 时转移（或者需要把数组第三维开大。）  

$~~~~$ 然后就直接 $\texttt{DP}$ 即可。  

---

#### 代码

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
const int WY=1e9+7;//WY yyds
int dp[1000005][21][2],n;
ll calc(int x){return n/x;}
ll qpow(int a){return a==0?1:3;}
ll c1(int i,int j,int k){return dp[i-1][j][k]*(calc((1<<j)*qpow(k))-(i-1))%WY;}//分成三种情况判断，方便写一点。
ll c2(int i,int j,int k){return dp[i-1][j+1][k]*(calc((1<<j)*qpow(k))-calc((1<<(j+1))*qpow(k)))%WY;}
ll c3(int i,int j,int k){return dp[i-1][j][k+1]*(calc((1<<j)*qpow(k))-calc((1<<j)*qpow(k+1)))%WY;}
int main() {
	scanf("%d",&n);
	int tmp=n,lg=0;
	while(tmp)//计算 log2(n)
	{
		tmp/=2;
		lg++;
	}
	lg--;
    //第一个位置的初始化
	dp[1][lg][0]=1;
	if((1<<(lg-1))*3<=n) dp[1][lg-1][1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<=lg;j++)
		{
			(dp[i][j][0]+=((c1(i,j,0)+c2(i,j,0))%WY+c3(i,j,0))%WY)%=WY;
			(dp[i][j][1]+=(c1(i,j,1)+c2(i,j,1))%WY)%=WY;//这里 k 不可能由+1转移过来
		}
	}
	printf("%d",dp[n][0][0]);
	return 0;
}
```

 



---

## 作者：81179332_ (赞：1)

我们要最大化不同的 $\gcd$ 个数，则显然我们要把 $n$ 以内质因数个数最多的数放在第一个

质因数最多的数只可能有 $2,3$ 两个质因数，因为 $5$ 以上的数可以被 $2^2$ 替换掉，结果更小但是质因数更多

最多只有一个 $3$，因为 $3^2$ 可以被 $2^3$ 替换掉

则我们可以设 $f_{i,j,k}$ 表示考虑到第 $i$ 个数，当前 $\gcd$ 为 $2^j\times 3^k$ 的方案数

分情况讨论转移即可

```cpp
//timeuse:15min
const int N = 1000010;
int n,m,f[N][21][2];
ll cnt(int x) { return n / x; }
int main()
{
	f[1][m = log2(n = read())][0] = 1;
	if((1 << m - 1) * 3 <= n) f[1][m - 1][1] = 1;
	for(int i = 2;i <= n;i++) for(int j = 0;j <= m;j++)
	{
		ll res0 = 0,res1 = 0;
		res0 += (ll)f[i - 1][j][0] * (cnt(1 << j) - i + 1);
		res0 += (ll)f[i - 1][j + 1][0] * (cnt(1 << j) - cnt(1 << j + 1));
	 	res0 += (ll)f[i - 1][j][1] * (cnt(1 << j) - cnt((1 << j) * 3));
		res1 += f[i - 1][j][1] * (cnt((1 << j) * 3) - i + 1);
		res1 += f[i - 1][j + 1][1] * (cnt((1 << j) * 3) - cnt((1 << j + 1) * 3));
		f[i][j][0] = res0 % mod,f[i][j][1] = res1 % mod;
	}fprint(f[n][0][0]);
}

```

---

## 作者：ywy_c_asm (赞：1)

感觉这做法相对于其它两篇更加无脑一些……

显然对于一个排列来说前缀gcd一定是$p_1$的约数，考虑前缀gcd是如何变化的，那肯定就是，$p_i$前面的数都是$g_{i-1}$的倍数，$p_i$是$g_i$的倍数但不是$g_{i-1}$的倍数，那么显然$p_i$有$\lfloor\frac n {g_{i}}\rfloor-\lfloor\frac n{g_{i-1}}\rfloor$种取值。

不难发现这只和前一个g以及后一个g有关，那么我们先考虑求最大值，再在求最大值的过程中统计方案数，我们从后往前dp，令$dp[i]$为我们钦定前缀的$gcd$为i，后面的不同g的个数的最大值，$f[i]$为后面的取最大值的排列的方案数，显然$g_n=1$，我们从这里开始。那么就考虑枚举上一个不同的$g_{pre}$也就是它的倍数，很显然这样的话就必须让前面的数全部都是$g_{pre}$的倍数，然后我们在前面这一段的终结位置的末尾处添加这$\lfloor\frac n {i}\rfloor-\lfloor\frac n{g_{pre}}\rfloor$个是$i$的倍数但不是$g_{pre}$的倍数的数中的任意一个，这样就把前缀$gcd$从$g_{pre}$变成了$i$，然后剩下的这些数我们可以任意插到后面的位置，因为已经满足了$gcd=i$的要求了。那么有转移$dp[i]+1->dp[ki]$，$f[i](\lfloor\frac n {i}\rfloor-\lfloor\frac n{g_{pre}}\rfloor)P(n-\lfloor\frac n{g_{pre}}\rfloor-1,\lfloor\frac n {i}\rfloor-\lfloor\frac n{g_{pre}}\rfloor-1)->f[ki](k>=2)$。

复杂度在枚举倍数，即$O(n\log n)$。

上代码~


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define p 1000000007
using namespace std;
namespace ywy {
	int g[1000001];
	ll jc[1000001], f[1000001], jcny[1000001];
	inline ll mi(int a, int b) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = (ans * tmp) % p;
	        tmp = (tmp * tmp) % p;
	        b >>= 1;
	    }
	    return (ans);
	}
	inline ll P(int n, int m) { return ((jc[n] * jcny[n - m]) % p); }
	void ywymain() {
	    int n;
	    cin >> n;
	    jc[0] = 1;
	    for (register int i = 1; i <= n; i++) jc[i] = (jc[i - 1] * i) % p;
	    g[1] = 1;
	    f[1] = 1;
	    jcny[n] = mi(jc[n], p - 2);
	    for (register int i = n - 1; i >= 0; i--) jcny[i] = (jcny[i + 1] * (i + 1)) % p;
	    for (register int i = 1; i <= n; i++) {
	        for (register int j = i * 2; j <= n; j += i) {
	            ll cjr = (n / i - n / j) * f[i];
	            cjr %= p;
	            cjr *= P(n - n / j - 1, n / i - n / j - 1);
	            cjr %= p;
	            if (g[i] + 1 == g[j]) {
	                f[j] = (f[j] + cjr) % p;
	            }
	            if (g[i] + 1 > g[j]) {
	                g[j] = g[i] + 1;
	                f[j] = cjr;
	            }
	        }
	    }
	    int mx = 0;
	    for (register int i = 1; i <= n; i++) mx = max(mx, g[i]);
	    ll ans = 0;
	    for (register int i = 1; i <= n; i++) {
	        if (g[i] != mx)
	            continue;
	        ans = (ans + f[i]) % p;
	    }
	    cout << ans << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：happybob (赞：0)

观察到结论后就简单了。

考虑什么序列可以让本质不同前缀 $\gcd$ 数量取到最大值。令 $a_1$ 分解质因数结果为 $a_1 = p_1^{k_1} p_2^{k_2} \cdots p_m^{k_m}$，考虑序列的本质不同前缀 $\gcd$ 的数量必然不超过 $(\sum \limits_{i=1}^m k_i)+1$，证明是显然的。进一步地，可以证明这个值可以取到。因为序列是排列，所以可以依次将每个质因数的次幂减到 $0$，故必然可以取到这个值。

注意到 $5^1>2^2$，所以 $a_1$ 必然不含大于等于 $5$ 的质因数。更进一步，发现 $3^2>2^3$，故 $3$ 的次幂不超过 $2$。考虑由此进行 DP。记 $f_{i,j,k}$ 表示已经确定了 $p_1,p_2,\cdots,p_i$，且目前这些数的 $\gcd$ 为 $2^j3^k$，其中 $2^j \leq n$，$k \leq 1$。考虑三类转移，分别是 $\gcd$ 不变，$\gcd$ 在 $2$ 的次幂减少 $1$，或者在 $3$ 的次幂减少 $1$。后两种是类似的。第一种转移时，考虑下一个数 $x$ 必然有 $2^j3^k \mid x$，但 $x$ 不能是之前的 $[1,i]$ 中的数，所以贡献倍数为 $\lfloor \dfrac{n}{2^j3^k} \rfloor - i$。第二个转移相当于限制 $2^{j-1}3^k \mid x$，但是 $2^j3^k \nmid x$。这个转移倍数直接就是 $\lfloor \dfrac{n}{2^{j-1}3^k} \rfloor - \lfloor \dfrac{n}{2^{j}3^k} \rfloor$。第三种是类似的。总复杂度 $O(n \log n)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <queue>
using namespace std;

using ll = long long;

const int N = 1e6 + 5;
const ll MOD = 1e9 + 7;

int f[N][20][2];
int n;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 0; (1ll << i) <= n; i++)
	{
		if ((1ll << (i + 1)) > n)
		{
			f[1][i][0] = 1ll;
		}
		if ((1ll << i) * 3 <= n && (1ll << (i + 2)) > n)
		{
			f[1][i][1] = 1ll;
		}
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			for (int k : {0, 1})
			{
				if (!f[i][j][k]) continue;
				int cnt = max(0, (n / ((1 << j) * (k == 1 ? 3 : 1)) - i));
				f[i + 1][j][k] = (f[i + 1][j][k] + 1ll * cnt * f[i][j][k] % MOD) % MOD;
				if (j >= 1)
				{
					cnt = max(0, n / ((1 << (j - 1)) * (k == 1 ? 3 : 1)) - (n / ((1 << j) * (k == 1 ? 3 : 1))));
					f[i + 1][j - 1][k] = (f[i + 1][j - 1][k] + 1ll * cnt * f[i][j][k] % MOD) % MOD;
				}
				if (k >= 1)
				{
					cnt = max(0, n / (1 << j) - (n / ((1 << j) * (k == 1 ? 3 : 1))));
					f[i + 1][j][k - 1] = (f[i + 1][j][k - 1] + 1ll * cnt * f[i][j][k] % MOD) % MOD;
				}
			}
		}
	}
	cout << f[n][0][0] << "\n";
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

非常好题目，使我的大脑旋转（？）

还是一样，介绍思路。

既然题目让我们计算 $f_{\max}(n)$ 的数量，则先考虑 $f_{\max}(n)$ 的值怎样求得。容易发现，设 $n=\prod p_i^{k_i},p_i\in \operatorname{prime}$ ，则 $f(n)=\sum k_i+1$。注意是 $f(n)$ 不是 $f_{\max}(n)$。简单贪心，发现当 $x=2^m$ 时，$f(x)$ 会尽可能大。

但是还需要知道有没有其他可能的 $x$ 会有一样大的结果。首先发现 $x$ 不能为一个大于 $3$ 的质数的倍数，否则一定可以拆成至少两个 $2$，这样更优。并且，$3$ 对应的指数不能 $>1$，因为 $3^2>2^3$，就可以拆成 $3$ 个 $2$ 了。

综上，得出结论：$f_{\max}(n)$ 会在这样的 $f(x)$ 中取到：设 $k=\left\lfloor \log x\right\rfloor$，$x=2^k$ 或 $x=2^{k-1}\times 3$。

对于这两个数，他们有一个性质：因数不会太多。也就意味着，$f_{\max}(n)$ 里包含的不同的前缀 $\gcd$ 可能取到的值的数量是 $O(\log n)$ 级别的。

于是可以考虑 dp，并存下来当前选了几个数，以及前缀 $\gcd$。转移则考虑当前 $\gcd$ 没变/为原来 $\dfrac{2}{1}$/为原来 $\dfrac{3}{1}$。具体可以手推一下。

其实状态两维就够。

code：

```cpp
int n,m,k,a[N],b[N],dp[N][47];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
int solve(int x){
	k=0,mems(b,0);
	drep(i,n,1)if(x%i==0)a[++k]=i,b[i]=k;
	mems(dp,0),dp[1][1]=1;
	rep(i,2,n){
		rep(j,1,k){
			dp[i][j]=1ll*dp[i-1][j]*(n/a[j]-i+1)%mod;
			if(a[j]*2<=n&&b[a[j]*2])dp[i][j]=Mod(dp[i][j],1ll*dp[i-1][b[a[j]*2]]*(n/a[j]-n/(a[j]*2))%mod);
			if(a[j]*3<=n&&b[a[j]*3])dp[i][j]=Mod(dp[i][j],1ll*dp[i-1][b[a[j]*3]]*(n/a[j]-n/(a[j]*3))%mod);
		}
	}
	return dp[n][k];
}
void Yorushika(){
	scanf("%d",&n),m=__lg(n);
	int x=1<<__lg(n);
	if(x/2*3<=n)printf("%d\n",Mod(solve(x),solve(x/2*3)));
	else printf("%d\n",solve(x));
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：User_Unauthorized (赞：0)

## 题意

对于一个排列 $p$，定义 $g$ 为 $p$ 的前缀最大公约数序列，即 $g_i = \gcd\limits_{j = 1}^{i} p_j$。定义 $f(p)$ 为 $g$ 的元素种类数。

给定 $n$，求长度为 $n$ 的且使得 $f(p)$ 取最大值的排列个数，对 $10^9 + 7$ 取模。

（$1 \le n \le 10^6$）。

## 题解

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-CF1174E.html)**

考虑转化限制条件，定义满足要求的排列的第一个元素为 $s$。因为 $s$ 和任何数的最大公约数一定不大于 $x$，所以有前缀最大公约数序列单调递减。又有递减的过程中每次递减一定是除去当前元素的一个质因子，考虑上元素种类数最大的限制，所以每次除去的一定是质因子。故符合要求的 $s$，一定是 $\left[1, n\right]$ 中质因子最多的数。

首先发现 $2^{\left\lfloor\log_2 n\right\rfloor}$ 一定是符合要求的 $s$，因为不会存在质因子数目多于 ${\left\lfloor\log_2 n\right\rfloor}$ 的数。对于其他的可能，考虑替换其中的质因子 $2$，如果替换了一个大于等于 $4$ 的质因子，那么其质因子数目一定减少，不符合要求，故只能替换质因子 $3$。考虑可以替换的数量，替换 $1$ 个显然合法，如果替换了 $\ge 2$ 个，那么显然有 $2^3 < 3^2$，所以这种情况的质因子数也会减少，不符合要求。

综上，符合要求的 $s$ 一定有 $2^{\left\lfloor\log_2 n\right\rfloor}$，若 $2^{\left\lfloor\log_2 n\right\rfloor - 1} \cdot 3 \le n$，那么 $2^{\left\lfloor\log_2 n\right\rfloor - 1} \cdot 3$ 也符合要求。即符合要求的 $s$ 可以表达为 $2^x \cdot 3^y$ 的形式，其中 $y \in \left\{0, 1\right\}$。

考虑使用 $\text{DP}$，定义 $f_{i, x, y}$ 为取了 $i$ 个数，且当前最大公约数为 $2^x \cdot 3^y$ 的方案数。对于合法的 $s = 2^x \cdot 3^y$，有 $f_{1, x, y}$ 初始值为 $1$，反之为 $0$。转移考虑最大公约数的变化情况。

---

### 最大公约数未改变

有转移

$$\begin{aligned}
f_{i, x, y} \leftarrow f_{i - 1, x, y} \times \operatorname{count}\left(2^x \cdot 3^y\right)
\end{aligned}$$

### 最大公约数除去质因子 $2$

有转移

$$\begin{aligned}
f_{i, x, y} \leftarrow f_{i - 1, x + 1, y} \times \left(\operatorname{count}\left(2^x \cdot 3^y\right) - \operatorname{count}\left(2^{x + 1} \cdot 3^y\right)\right)
\end{aligned}$$

### 最大公约数除去质因子 $3$

有转移

$$\begin{aligned}
f_{i, x, 0} \leftarrow f_{i - 1, x, 1} \times \left(\operatorname{count}\left(2^x\right) - \operatorname{count}\left(2^{x} \cdot 3\right)\right)
\end{aligned}$$

---

其中 $\operatorname{count}(x) = \sum\limits_{i = 1}^{n} \left[x \mid i\right]$，即 $\left[1, n\right]$ 中 $x$ 的倍数个数。最终答案即为 $f_{n, 0, 0}$。

总复杂度 $\mathcal{O}(n \log n)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

typedef std::array<valueType, 2> Data;
typedef std::vector<Data> DataVector;
typedef std::vector<DataVector> DataMatrix;

constexpr valueType MOD = 1e9 + 7;


#define ModOperSafeModOption false

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

int main() {
    valueType N;

    std::cin >> N;

    auto const count = [N](valueType x) {
        return N / x;
    };

    auto const G = [](valueType i2, valueType i3) {
        return (1 << i2) * (i3 == 1 ? 3 : 1);
    };

    valueType M = std::floor(std::log2((long double) N));

    DataMatrix F(N + 1, DataVector(M + 1));

    F[1][M][0] = 1;

    if ((1 << (M - 1)) * 3 <= N)
        F[1][M - 1][1] = 1;

    for (valueType j = M - 1; j >= 0; --j) {
        for (valueType i = 2; i <= N; ++i) {
            Inc(F[i][j][0], mul(F[i - 1][j][0], count(G(j, 0)) - (i - 1)));
            Inc(F[i][j][1], mul(F[i - 1][j][1], count(G(j, 1)) - (i - 1)));

            Inc(F[i][j][0], mul(F[i - 1][j + 1][0], count(G(j, 0)) - count(G(j + 1, 0))));
            Inc(F[i][j][1], mul(F[i - 1][j + 1][1], count(G(j, 1)) - count(G(j + 1, 1))));

            Inc(F[i][j][0], mul(F[i - 1][j][1], count(G(j, 0)) - count(G(j, 1))));
        }
    }

    std::cout << F[N][0][0] << std::endl;

    return 0;
}
```

---

## 作者：chlchl (赞：0)

dp + 数学好题。

~~但是 \*2500 确实跟 \*3000 有差距。~~

## Solution
前缀 $\gcd$ 不同情况最大这个 trick，感觉已经算挺板的了。

首先知道，若 $x=\prod\limits_{i=1}^{k}p_i^{c_i}$，则 $x$ 的因数个数为 $\prod\limits_{i=1}^{k}(c_i+1)$。

因为前缀 $\gcd$ 一定包含第一个数，所以的最好情况是，第一个数选一个因数个数最多的，然后每次 $\gcd$ 刚好减少一个质因数。

然后可以发现，若使开头第一个数因数个数最大，那它一定是形如 $2^j\times 3^k$ 的。

因为要是有一个数的质因子 $\ge 5$，那我可以找一堆带有 $2^2=4$ 的代替，不仅小于原数，乘出来的因数个数也一定比原数大。

而 $k$ 也有限制，它不能大于 $1$。因为如果 $k\ge 2$，那至少有个 $9$，完全可以用 $2^3=8$ 代替它，效果与上面相似。

然后就可以在指数上进行 DP。设 $f_{i,j,k}$ 为填了前 $i$ 位，当前 $\gcd$ 为 $2^j\times 3^k$ 时，合法序列的个数。

从 $i-1$ 转移过来时，做一个分类讨论：
- 若第 $i$ 位填了之后 $\gcd$ 不变，情况数会 $\times\big(\lfloor\dfrac{n}{2^j\times 3^k}\rfloor-(i-1)\big)$。因为第 $i$ 位必须为 $2^j\times 3^k$ 的倍数，而前 $i-1$ 个数也需要是它的倍数才行。
- 若第 $i$ 位填了之后 $\gcd$ 变成 $\frac{1}{2}$，情况数会 $\times\big(\lfloor\dfrac{n}{2^{j}\times 3^k}\rfloor-\lfloor\dfrac{n}{2^{j+1}\times 3^k}\rfloor\big)$。因为第 $i$ 位必须为 $2^{j}\times 3^k$ 的倍数且不为 $2^{j+1}\times 3^k$ 的倍数（否则 $\gcd$ 不变），而前 $i-1$ 个数在两次计算中都被算了一次，相减直接抵消了。
- 若第 $i$ 位填了之后 $\gcd\leftarrow\gcd\div 3$，类似的，情况数会 $\times\big(\lfloor\dfrac{n}{2^j\times 3^{k}}\rfloor-\lfloor\dfrac{n}{2^{j}\times 3^{k+1}}\rfloor\big)$。

边界就是 $f_{0,\lfloor\log_2(n)\rfloor,1}=1$，这个没什么实际意义，自己推一推即可。

---

## 作者：fjy666 (赞：0)

首先我们观察到 $g_i$ 是单调不上升的，每次下降会且仅会删去一个质因数。  
然后就可以推出结论：$p_1=2^k$ 或 $p_1=2^{k-1}\times 3$。（$k=\lfloor\log_2n\rfloor+1$）。  
照理说到这里就能做了，可我就是不会设状态，实在太没用了。  
设 $f_{i,j,k}$ 为当前已经填完了 $i$，前缀 $\gcd$ 为 $2^j\times 2^k$ 的时候的方案数，转移可以分 $\gcd$ 不变、$\gcd\div2$ 和 $\gcd \div 3$ 三种情况转移。  
- $\gcd$ 不变 转移到 $f_{i+1,j,k}$，系数为 $\lfloor\frac{n}{2^j\times 3^k}\rfloor-i$
- $\gcd\div 2$ 转移到 $f_{i+1,j-1,k}$, 系数为 $\lfloor\frac{n}{2^{j-1}\times 3^k}\rfloor-\lfloor\frac{n}{2^{j}\times 3^k}\rfloor$ 注意到用了容斥
- $\gcd\div 3$ 转移到 $f_{i+1,j,k-1}$, 系数为 $\lfloor\frac{n}{2^j\times 3^{k-1}}\rfloor-\lfloor\frac{n}{2^j\times 3^k}\rfloor$ 同样使用容斥

时间复杂度为 $\mathcal{O}(n\log n)$。

[submission](https://codeforces.com/problemset/submission/1174/177083984)

---

## 作者：Leasier (赞：0)

为了让项数尽量多，贪心地，我们肯定会选互异质因数尽量多的数。

令 $m = \lfloor \log_2 n \rfloor$，则 $2^m$ 显然是一个可行的选择。

那含有更大的质因数是否可行呢？

假如我选择了一个质因数 $3$，我肯定不会去选两个 $3$，因为 $2^3 < 3^2$。所以我们至多选择一个 $3$，此时的选择为 $3 \times 2^{m - 1}$（当然这只在这个值小于等于 $n$ 时可行）。

假如我选择了一个质因数 $5$，这显然不优，因为你可以将其替换为 $2^2 < 5$。

所以我们得出结论：**至多选择 $m$ 个 $2$，$1$ 个 $3$**。

贪心地，前缀 $\gcd$ 每次变化至多只会减少一个 $2, 3$。

考虑 dp，设 $dp_{i, j, k}$ 表示已经填了前 $i$ 位，当前 $2$ 的幂次为 $j$，$3$ 的幂次为 $k$ 时第 $1 \sim i$ 位的方案数。

初值：$dp_{1, m, 0} = 1$，$dp_{1, m - 1, 1} = [3 \times 2^{m - 1} \leq n]$。

转移分为三种：

- 前缀 $\gcd$ 不变，当前位的方案数为所有 $2^j 3^k$ 的倍数除去前 $i - 1$ 位选过的：$dp_{i, j, k} \leftarrow dp_{i, j, k} + dp_{i - 1, j, k} (\lfloor \frac{n}{2^j 3^k} \rfloor - (i - 1))$。
- 前缀 $\gcd$ 除以 $2$，当前位的方案数为所有 $2^j 3^k$ 的倍数除去所有 $2^{j + 1} 3^k$ 的倍数：$dp_{i, j, k} \leftarrow dp_{i, j, k} + dp_{i - 1, j + 1, k} (\lfloor \frac{n}{2^j 3^k} \rfloor - \lfloor \frac{n}{2^{j + 1} 3^k} \rfloor)$。
- 前缀 $\gcd$ 除以 $3$，当前位的方案数为所有 $2^j 3^k$ 的倍数除去所有 $2^j 3^{k + 1}$ 的倍数：$dp_{i, j, k} \leftarrow dp_{i, j, k} + dp_{i - 1, j, k + 1} (\lfloor \frac{n}{2^j 3^k} \rfloor - \lfloor \frac{n}{2^j 3^{k + 1}} \rfloor)$。

滚动数组实现即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 1e9 + 7;
ll dp[27][7];

int main(){
	int n, m = 0;
	scanf("%d", &n);
	while ((1 << m) <= n) m++;
	dp[--m][0] = 1;
	if ((1 << (m - 1)) * 3 <= n) dp[m - 1][1] = 1;
	for (int i = 2; i <= n; i++){
		for (int j = 0; j <= m; j++){
			for (int k = 0; k <= 1; k++){
				int val = n >> j;
				if (k == 1) val /= 3;
				if (val < i){
					dp[j][k] = 0;
				} else {
					dp[j][k] = dp[j][k] * (val - (i - 1)) % mod;
					if (j < m) dp[j][k] = (dp[j][k] + dp[j + 1][k] * (val - val / 2) % mod) % mod;
					if (k == 0) dp[j][k] = (dp[j][k] + dp[j][k + 1] * (val - val / 3) % mod) % mod;
				}
			}
		}
	}
	printf("%lld", dp[0][0]);
	return 0;
}
```

---

