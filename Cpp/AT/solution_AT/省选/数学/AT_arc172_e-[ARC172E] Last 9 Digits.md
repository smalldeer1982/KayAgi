# [ARC172E] Last 9 Digits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc172/tasks/arc172_e

$ n^n $ を $ 10^9 $ で割った余りが $ X $ となるような正の整数 $ n $ が存在するか判定し、存在する場合は最小のものを求めてください。

$ Q $ 個のテストケースが与えられるので、それぞれに対して答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 10000 $
- $ 1\ \leq\ X\ \leq\ 10^9\ -\ 1 $
- $ X $ は $ 2 $ の倍数でも $ 5 $ の倍数でもない
- 入力はすべて整数
 
### Sample Explanation 1

この入力例は $ 2 $ 個のテストケースからなります。 - $ 1 $ 個目：$ 3^3\ =\ 27 $ を $ 10^9 $ で割った余りは $ 27 $ なので、$ n\ =\ 3 $ で条件を満たします。 - $ 2 $ 個目：$ 11^{11}\ =\ 285311670611 $ を $ 10^9 $ で割った余りは $ 311670611 $ なので、$ n\ =\ 11 $ で条件を満たします。

## 样例 #1

### 输入

```
2
27
311670611```

### 输出

```
3
11```

# 题解

## 作者：大眼仔Happy (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc172_e)

### 简要题意

给定 $x$，求出最小的 $n$，满足 $n^n\equiv x\pmod{10^9}$。

保证 $x$ 既不是 $2$ 的倍数也不是 $5$ 的倍数。

------------

妙妙数学题，被同学安利的。

观察得到 $n$ 同样满足 $\color{red}2\nmid n,5\nmid n$ 的性质，可以直接用欧拉定理。但是暴力 $\varphi(10^9)$ 范围还是太大，可以先从弱化版做起。

### 弱化版

给定 $x$，求出最小的 $n$，满足 $n^n\equiv x\pmod{100}$。

这个弱化版当然是直接暴力就行了。

### 拓展

考虑从这里拓展。将 $n\gets 100t+n$，其中 $t\in [0,9]$。根据二项式定理可以得到

$$
\begin{aligned}
(n+100t)^{n+100t} 
& \equiv n^{n+100t}+\binom{n+100t}{1}\times n^{n+100t-1}\times 100t & \pmod{1000}\\
& \equiv n^{n+100t}+n^{n+100t}\times 100t & \pmod{1000}\\
& \equiv (n^n+n^n\times 100t)\times n^{100t} & \pmod{1000}
\end{aligned}
$$

而由欧拉定理得到

$$
n^{100}=
\begin{cases}
(n^{\varphi(8)})^{25} & \equiv 1 & \pmod{8}\\ 
n^{\varphi(125)} & \equiv 1 & \pmod{125}
\end{cases}
$$

且 $8\perp 125$，故 $n^{100}\equiv 1\pmod{1000}$。

最后我们就得到了 $(n+100t)^{n+100t}\equiv n^n+n^n\times 100t\pmod{1000}$。

从这个柿子我们可以得到 $\{(n+100t)^{n+100t}|\,t\in [0,9]\}$ 在模 $1000$ 的意义下正好对应 $\{(n^n\bmod 100)+100t|\,t\in [0,9]\}$。（假设 $n^n$ 的百位为 $k$，那么 $n^n+n^n\times 100t$ 的百位则为 $(k+(n\bmod 10)t)\bmod 10$，与 $[0,9]$ 一一对应。）

而且用 ~~打表/看题解~~ 等方法得到 $\{1,3,7,9,\cdots,99\}$ 和 $\{1^1,3^3,7^7,9^9,\cdots 99^{99}\}$ 在模 $100$ 的意义下一一对应。

于是一般而言，将 $100$ 替换成 $10^k$，$1000$ 替换成 $10^{k+1}$ 时，上面种种规律在 $k\ge 2$ 依然成立（数学归纳法证得）。

这从侧面印证了所有的符合条件的 $x$ 都有解。

- $k=1$ 不成立的原因是存在 $n$ 不满足 $n^{10}\equiv 1\pmod{100}$。

### 算法设计

感觉逐渐清晰是吗？

设问题 $k$ 为，$n^n\equiv x\pmod{10^k}$，答案为 $a_k$。

当 $k=2$ 的时候，暴力计算得到 $a_k$。当 $k>2$ 的时候，通过 $a_{k-1}$，且枚举 $a'_ k=10^{k-1}\times t+a_{k-1},t\in [0,9]$，来检验 $a'_ k$ 是否合法。

于是单个询问的时间复杂度就是 $O(L^2)$，其中 $L=9$。~~好像还漏算了一个快速幂。~~

~~所以，这么难的题怎么可能是我自己想的。~~

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int T,ans[105];ll n,a[10],base;
ll qp(ll a,ll b,ll mod){ll res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
void init()
{
	for(int i=1;i<=100;i++)
	{
		if(i%2==0||i%5==0)continue;
		int pw=qp(i,i,100);
		ans[pw]=i;
	}
}
void solve()
{
	n=read();a[2]=ans[n%100];base=10;
	for(int i=3;i<=9;i++)
	{
		base*=10;
		for(int t=0;t<=9;t++)
		{
			a[i]=t*base+a[i-1];
			if(qp(a[i],a[i],base*10)==n%(base*10))break;
		}
	}
	printf("%lld\n",a[9]);
}
int main(){
	init();T=read();while(T--)solve();
	return 0;
}
```

---

## 作者：Jian_Yu (赞：6)

[题目链接](https://atcoder.jp/contests/arc172/tasks/arc172_e)

讲一种比较暴力的做法。

写一个暴力随便尝试几个数，容易发现对于一个数 $x$，当 $y\ge2$ 且 $x$ 与 $10$ 互质时，有
$$
(x+10^y)^{(x+10^y)}\equiv x^x\pmod{10^y}
$$
具体证明可以看[这里](https://atcoder.jp/contests/arc172/editorial/9351)。

而我们发现题目中刚好保证了 $x$ 与 $10$ 互质，所以我们只需要取 $y\ge2$ 即可

于是可以直接预处理出 $1\sim10^6$ 中每个数 $x$ 的 $x^x\bmod10^6$ 的值，然后每次询问时查表可以得到后六位，接下来只需要枚举前三位逐一判定即可。

全部跑满大概是 $10^6\log10^6+10^4\times10^3\log10^9$ 也就是 $4\times10^8$ 次运算，实际跑不满，所以卡卡常就能通过。

具体代码实现非常的简单。

```c++
#include <iostream>
using namespace std;
const int MOD = 1e9;
typedef long long ll;
const int M = 1e6, K = 1e3;
ll qpow(ll x, int k){
	ll res = 1;
	for(; k; k >>= 1, x = x * x % MOD)
		if(k & 1) res = res * x % MOD;
	return res;
}

ll q, x;
int v[M+50];
int main(){
	for(int i = 1; i <= M; ++i){
		int val = qpow(i, i);
	  v[val % M] = i;
	} 
	for(cin >> q; q--; ){
		cin >> x;
		int pre = v[x%M];
		for(int j = 0; j < K; ++j){
			int nxt = j * M + pre;
			if(qpow(nxt, nxt) == x){
				cout << nxt << "\n";
				break;
			}
		}
	}
}
```

---

## 作者：NATO (赞：3)

提供一种赛时想到的和官方[题解](https://atcoder.jp/contests/arc172/editorial/9351)的做法有一定出入的做法。

#### 一句话题意：

$$n^n \equiv x\pmod{10^9}$$

给定 $x$ 且保证 $x$ 不是 $2$ 或 $5$ 的倍数，求最小的 $n$。

### 解题思路：

在模数任意的情况下似乎除了枚举并不是很可做的样子，于是我们从模数入手。

注意到模数 $10^9$ 是一个很不寻常的模数，它竟然不是一个质数，那么为什么题目会给出一个这样的模数呢？

考虑到 $10^9$ 是 $10$ 的次幂，也就是说对它取模就相当于是保留了一个数的最后 $9$ 位，那么既然 $x$ 不是 $2$ 或 $5$ 的倍数，$n$ 也就不是 $2$ 或 $5$ 的倍数，否则 $n^n$ 保留了最后 $9$ 位必然是 $2$ 或 $5$ 的倍数。那么当 $n$ 既不是 $2$ 或 $5$ 的倍数时 $n^n$ 的后 $9$ 位有什么性质呢？

暴力枚举一下吧。

我们通过暴力枚举后发现似乎当 $n<10^9$ 时，每个余数是唯一的，那么我们猜想 $n^n$ 对于 $\forall k\in\mathbb{N}^+,10^k$ 取模是否也存在当 $n<10^k$ 且 $n$ 既不是 $2$ 或 $5$ 的倍数时每个余数是唯一这样的结论呢（~~赛时谁会去证结论啊，用就完事了~~）？

具体证明过程比较长，且笔者数学水平低下，赛时没证，赛后也只会复述官方题解的证法，故此处不做证明，证明可参考官方[题解](https://atcoder.jp/contests/arc172/editorial/9351)的证明。

那么我们在有了这一结论后该怎么做呢？官方的解法是一位一位去确定这个数，但赛时笔者没有想到可以就此一位一位确定，却想到了一种很奇怪的解法：

由于当 $n<10^k$ 且 $n$ 既不是 $2$ 或 $5$ 的倍数时 $n^n$ 对 $\forall k\in\mathbb{N}^+,10^k$ 取模每个余数唯一，我们可以预处理出小于等于一定位数 $k$ 的所有 $n^n\bmod 10^k$，再把它们扔进一个映射中。对于一个数 $x$，先通过 $x\bmod 10^k$ 确定 $n$ 的末 $k$ 位，再枚举 $1,2,...,10^{9-k}-1$，和确定的 $n$ 的末 $k$ 位拼在一起验证 $\bmod 10^9$ 是否为 $x$ 即可。

时间复杂度 $O(10^k\log 10^k+q10^{9-k}\log v)$，其中 $v$ 为值域大小，根据 $q$ 的范围，$k=6$ 时取得的复杂度较小，可以通过本题。

#### 参考代码：

直接放赛时代码的[链接](https://atcoder.jp/contests/arc172/submissions/50425512)吧。

---

## 作者：cnyzz (赞：2)

提供一个相当劣但是思维难度很低的做法。

$10^9=2^95^9$，注意到 $n^n$ 在 $2^9$ 的循环节是 $2^9$，$5^9$ 的循环节是 $4\times 5^9$，均可以暴力预处理出每个 $x$ 对应的数在这些循环节下可能的数，这样的数对不会太多，于是令 $x$ 模 $2^9$ 下对应 $a$，模 $4\times 5^9$ 下对应 $b$，枚举 $b+k\times 4\times 5^9$ 并检验是否符合 $a$ 即可，需要注意 $0^0=0$。

时间复杂度不会算，成功在 1.96s 内通过。

---

## 作者：XYQ_102 (赞：0)

## E - Last 9 Digits

> Determine whether there is a positive integer $n$ such that the remainder of $n^n$ divided by $10^9$ is $X$. If it exists, find the smallest such $n$.
> 
> You will be given $Q$ test cases to solve.
> 
> $1 \leq Q \leq 10000,1 \leq X \leq 10^9 - 1$，$X$ is neither a multiple of $2$ nor a multiple of $5$.

告诉我们要勇于猜结论（在你不会证明的时候）。

首先还是手玩，猜结论：对于每一个 $X$，有且仅有一个数满足条件（在 $10^9$ 以内）。

而我们容易发现模数是较大的，所以我们考虑减小模数，从小的模数推过来，同时完成证明。

以下的规律从 $10^2$ 才开始有用，后面会进行阐释。

首先对于 $\text{mod}=10^2$ 的情况，我们发现确实对于每一个满足条件的 $X$ 都有且仅有一个答案，假设现在的答案是 $n$，满足 $n^n \equiv X \pmod {10^2}$，我们猜测（打表之类的发现）当模数变成  $10^3$ 时，满足条件的是 $n+100t$ 中的一个，其中 $t \in \{0,1,2,3,4,5,6,7,8,9 \}$。

于是就进行一些推式子：（省略 $\pmod {1000}$）

$$(n+100t)^{n+100t} = n^{n+100t} + (n+100t)n^{n+100t-1}(100t)^1+ \dots + n^0(100t)^{n+100t-1} $$

> 根据二项式定理。

$$\begin{align} & = n^{n+100t}+(n+100t)n^{n+100t-1}100t\\ & = n^{n+100t}+n^{n+100t} \times 100t\\ & = (n^n + n^n \times 100t)(n^{100})^t \end{align} $$

> 由于后面的每一项都有 $(100t)^2$，也就是 $10000$ 可以被整除掉。

$$=(n^n + n^n \times 100t) $$

> 发现 $n^{100} \equiv 1 \pmod {1000}$，这是由于欧拉定理：
> 
> $n^{\phi(8)} \equiv n^4 \equiv 1 \pmod 8$，那么 $n^{100} \equiv 1 \pmod 8$；（由于 $\phi(2)=1$ 所以对于 $mod=10$ 是不成立的）
> 
> $n^{\phi(125)} \equiv n^{100} \equiv 1 \pmod{125}$。
> 
> 而综合这两个条件，一定满足 $n^n \equiv 1 \pmod {1000}$。

而容易发现这个式子 $n^n + n^n \times 100t \pmod {1000}$ 的最后两位一定和 $n^n \pmod {100}$ 的最后两位是相同的，

所以这里的 $X$ 只会多出前面的一位，是满足条件的。

于是乎，从 $100 \to 1000$，这里满足条件的 $n$ 只有可能是 $n+100t$，这样转移就可以了。

而这样推出来之后，每一个数有且仅对应一个也就很容易证明了。

那么代码就是直接模拟即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n,ans=0;

int qpow(int a,int H){
  int res=1,b=a;a=a%H;
  while(b){if(b&1) res=1ll*res*a%H;a=1ll*a*a%H;b>>=1;}
  return res;
}

void sol(){
  scanf("%d",&n);
  for(int i=1;i<100;i++) if(qpow(i,100)==n%100){ans=i;break;}
  for(int i=2,t=100,P=1000;i<9;i++,t*=10,P*=10)
    for(int j=0;j<10;j++) if(qpow(ans+j*t,P)==n%P){ans+=j*t;break;}
  printf("%d\n",ans);    
}

int main(){
  int _;scanf("%d",&_);
  while(_--) sol();
  return 0;
}
```

---

## 作者：cwfxlh (赞：0)

# [AT_arc172_e](https://www.luogu.com.cn/problem/AT_arc172_e)        

考虑对于 $k>1$，$n\bot10,n=a+b\times 10^k$，则：      

$$\begin{aligned}n^n&\equiv (a+b\times 10^k)^n \pmod {10^{k+1}} \\&\equiv a^n+n\times b\times 10^k\times a^{n-1} \pmod {10^{k+1}}\\&\equiv (b\times 10^k+1)\times a^n \pmod {10^{k+1}}\\&\equiv (b\times 10^k+1)\times a^a\times a^{b\times 10^k} \pmod {10^{k+1}}\end{aligned}$$    

当 $a\bot 10$ 时：    

$$\begin{aligned}a^{10^k}&\equiv (a^{2^k})^{5^k} \pmod {2^{k+1}} \\&\equiv 1 \pmod {2^{k+1}}\end{aligned}$$   


$$\begin{aligned}a^{10^k}&\equiv (a^{5^k\times 4})^{2^{k-2}} \pmod {5^{k+1}}\\&\equiv 1 \pmod {5^{k+1}}\end{aligned}$$    
$$a^{10^k}\equiv 1 \pmod {10^{k+1}}$$     

所以 $n^n\equiv(b\times 10^k+1)\times a^a \pmod {10^{k+1}}$，有 $n^n\equiv a^a \pmod {10^k}$。    

于是思路可以转化为求出模 $10^k$ 的解，接下来枚举 b，得到更高位的解。对于模 100 的情况不符合上述推论，可以暴力求解。然后可以发现没有无解的情况，具体原因是模 100 的时候打表发现全部有解，其他情况 10 种 b 刚好对应 10 种不同的最高位。        

代码：       

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
__int128 bbb=1;
int k1,k2,k3,k4,k5,k6,k7,k8,k9,fsp[503];
int fstp(int X,int Y,int mod){
    int ret=1,bse=X%mod;
    while(Y){
        if(Y%2==1)ret=bbb*ret*bse%mod;
        bse=bbb*bse*bse%mod;
        Y/=2;
    }
    return ret;
}
int q,n,f[503];
signed main(){
    ios::sync_with_stdio(false);
    fsp[0]=1;
    for(int i=1;i<=12;i++)fsp[i]=fsp[i-1]*10ll;
    cin>>q;
    while(q--){
        cin>>n;
        for(int i=1;i<100;i++){
            if(fstp(i,i,100)==n%100){
                f[2]=i;
                break;
            }
        }
        for(int i=3;i<=9;i++){
            for(int j=0;j<=9;j++){
                k1=f[i-1]+fsp[i-1]*j;
                if(fstp(k1,k1,fsp[i])==n%fsp[i]){
                    f[i]=k1;
                    break;
                }
            }
        }
        cout<<f[9]<<'\n';
    }
    return 0;
}
```

---

## 作者：AzusidNya (赞：0)

## E Last 9 Digits

### Description

给定一个数 $X$，求一个最小的数 $n$ 满足 $n ^ n \equiv X\pmod {10 ^ 9}$，其中 $X$ 不是 $2$ 或 $5$ 的倍数。

### Solution

证明是看官方题解才懂的。

第一眼没什么思路，所以尝试暴力找规律。

但是 $10 ^ 9$ 太大了，不好暴力，所以先取小一点的模数暴力找下规律。

取模数为 $10 ^ 5$，$X = 3$，得到在 $[1, 10^6]$ 区间内的答案：

```
98427 198427 298427 398427 ... 798427 898427 998427
```

取模数为 $10 ^ 5$，$X = 49$，得到在 $[1, 10^6]$ 区间内的答案：

```
62449 162449 262449 362449 ... 762449 862449 962449
```

发现规律很明显，猜想此时对于任意满足题目条件的 $X$，在区间 $[1, 10^5]$ 内只有一解，设这一解为 $Y$，则其通解为 $X + 10^5 \cdot t \ (t \in N)$。

继续找规律。

取模数为 $10^6$，$X = 3$，得到在 $[1, 10^7]$ 区间内的答案：

```
998427 1998427 2998427 3998427 ... 7998427 8998427 9998427
```

取模数为 $10^7$，$X  = 3$，得到在 $[1, 10^8]$ 区间内的答案：

```
5998427 15998427 25998427 35998427 ... 75998427 85998427 95998427
```

取模数为 $10^6$，$X = 49$，得到在 $[1, 10^7]$ 区间内的答案：

```
62449 1062449 2062449 3062449 ... 7062449 8062449 9062449
```

取模数为 $10^7$，$X = 49$，得到在 $[1, 10^8]$ 区间内的答案：

```
3062449 13062449 23062449 33062449 ... 73062449 83062449 93062449
```

规律找到这里，这题基本就做完了。

**猜想 $1$：** 当模数为 $10^k$ 时，满足 $n ^ n \bmod 10^k = X$ 的解 $n$ 在 $[1, 10^k]$ 内有且仅有一个。

**猜想 $2$：** 当模数为 $10^k$ 时，设满足 $n ^ n \bmod 10 ^{k - 1}$ 的在 $[1, 10^{k -1}]$ 内的解为 $n'$，则满足 $n ^ n \bmod 10^k = X$ 的在 $[1, 10^k]$ 内的解 $n$ 为 $n' + 10^k \cdot t \left (t \in[0,9] \right)$。

这两个猜想在 $k \ge 2$ 的时候是正确的，下面给出证明。

> **证明：**
>
> 数学归纳法。
>
> 当 $k = 2$ 时，经过验证 $1^1, 3^3, 7^7,\dots, 97^{97}, 99^{99}$ 对 $100$ 取模的值刚好取遍 $1, 3, 7, \dots, 97, 99$ 各一次。
>
> 假设有 $n ^ n \equiv X \pmod{100}$，考虑 $k = 3$ 的情况。
> $$\begin{aligned}
 (n + 100t) ^ {n + 100t} &= n ^ {n + 100t} + (n + 100t) \cdot n^{n + 100t - 1} \cdot 100t + \cdots + n^0 \cdot (100t)^{n + 100t} \\
 &\equiv n ^ {n + 100t} + (n + 100t) \cdot n^{n + 100t - 1} \cdot 100t \pmod{1000} \\
 &\equiv n ^{n + 100t} + n ^{n + 100t} \cdot 100t + 100t \cdot n^{n + 100t - 1} \cdot 100t \pmod {1000} \\
 &\equiv n ^ {n + 100t} + n ^ {n + 100t} \cdot 100t \pmod{1000} \\
 &\equiv (n^{100}) ^t \cdot (n ^ n + n ^ n \cdot 100t) \pmod{1000}
 \end{aligned}$$
>
> 下面证明 $n ^ {100} \bmod 1000 = 1$。
>
> 由欧拉定理，有：
>
> - 因为 $\varphi(8) = 4$，所以 $n ^ {100} \bmod 8 = n ^ {100 \bmod 4} \bmod 8 = n ^ 0 \bmod 8 = 1$。
> - 因为 $\varphi(125) = 100$，所以 $n ^ {100} \bmod 125 = n ^ {100 \bmod 100} \bmod 125 = n^0 \bmod 125 = 1$。
>
> 因为 $8 \perp 125$，所以用 CRT 合并一下就可以得到 $n ^ {100} \bmod 1000 = 1$。
>
> 最终得到：
> $$(n + 100t) ^ {n + 100t} \equiv n ^ n + n ^ n \cdot 100t \pmod{1000}$$
> 因为 $n ^ n$ 不是 $2$ 或 $5$ 的倍数，所以 $n ^ n, (n + 100) ^ {n + 100}, \dots, (n + 900) ^ {n + 900}$ 对 $1000$ 取模得到的数刚好取遍 $n ^ n \bmod 100, (n ^ n \bmod 100) + 100, (n ^ n \bmod 100) + 200, \dots, (n ^ n \bmod 100)+900$ 各一次，又因为$n ^ n \equiv X \pmod{100}$，所以一定能取到 $X \bmod 1000$。
>
> 综上，我们从 $k = 2$ 时猜想是正确的推出了 $k = 3$ 时猜想是正确的，同理可以推出 $k \ge 2$ 时这一猜想都是正确的。

有了这一结论，很容易设计出以下算法。

1. 先暴力求出满足 $n ^ n \equiv X \pmod{100}$ 的解 $n_2$。
2. 枚举 $t$，验证 $n_2 + t \cdot 10^2 \left(t\in[0,9]\right)$ 哪个满足题目条件，得到 $n_3$。
3. 同理推出 $n_4, n_5, \dots, n_9$ 即可，$n_9$ 即为所求。

时间复杂度 $O(L^2Q)$，其中 $L = 9$。

### Code

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#define int long long
using namespace std;
namespace solve1{
	int n;
	int ksm(int u, int v, int modd){
		int ret = 1;
		while(v){
			if(v & 1) ret = ret * u % modd;
			u = u * u % modd, v >>= 1;
		}
		return ret;
	}
	int a[10];
	int main(){
		cin >> n;
		int nw = 100;
		int x = n % nw;
		for(int i = 1; i < 100; i ++){
			int u = ksm(i, i, nw);
			if(u == x){
				a[2] = i;
				break;
			}
		}
		for(int i = 3; i <= 9; i ++){
			nw = nw * 10;
			int lst = a[i - 1];
			int tar = n % nw;
			for(int j = 0; j < 10; j ++){
				int x = lst + (nw / 10) * j;
				int u = ksm(x, x, nw);
				if(u == tar){
					a[i] = x;
					break;
				}
			}
		}
		cout << a[9] << "\n";
		return 0;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	while(T --)
		solve1::main();
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

从打表到打表的好题。

### 1 题意

给定一个数 $x$，满足 $1\le x<10^9$ 且 $x$ 既不是 $2$ 的倍数也不是 $5$ 的倍数（即 $\gcd(x,10)=1$），求最小的 $n$ 满足 $n^n\equiv x\pmod{10^9}$，若无解输出 $-1$。

多次（最多 $10^4$ 次）询问。

### 2 思路

省流：对于每个 $1\le y<5\times10^6$ 且 $\gcd(y,10)=1$，预处理出满足 $i^i\equiv y\pmod{5\times10^6}$ 的最小的 $i$（一定存在且只存在一个 $1\le i<5\times10^6$ 的解）。询问 $x$ 时，对于 $y=x\bmod(5\times10^6)$，$\Theta(1)$ 得到对应的 $i$，它就是 $n\bmod(5\times10^6)$ 的值，然后简单枚举 $n$ 判断即可。

首先想到预处理出每个 $x$ 的答案，对于每次询问 $\Theta(1)$ 回答。

~~显然我们无法估计 $n$ 的上限，时间复杂度不可接受。~~

显然，当 $n$ 是 $2$ 的倍数时，$n^n\bmod{10^9}$ 也是 $2$ 的倍数，这与 $x$ 的限制矛盾，这意味着 $n$ 不可能是 $2$ 的倍数，同理也不可能是 $5$ 的倍数。

考虑到 $x$ 既不是 $2$ 的倍数也不是 $5$ 的倍数，我们只需要对 $4\times10^8$ 个 $x$ 预处理答案即可。

开始新一轮打表，暂时只考虑 $n<10^9$ 的情况（一共 $4\times10^8$ 个）所产生的所有 $n^n\bmod10^9$，惊讶地发现产生了刚好 $4\times10^8$ 个本质不同的结果，**这意味着，$n$ 和 $x$ 形成了一个双射，也就是说不可能无解且 $n$ 有了一个清晰的限制（$10^9$）**。

~~显然预处理出这 $4\times10^8$ 种可能同样是无法接受的。~~

根据欧拉函数相关性质，当 $\gcd(a,m)=1$ 时，$a^{\varphi(m)}\equiv1\pmod m$。事实上，在本题 $m=10^9$ 的情况下，上式可写为 $a^{5\times10^6}\equiv1\pmod m$，即使 $5\times10^6$ 远小于 $\varphi(10^9)$。

回到这题，显然：

$$n^{n\bmod(5\times10^6)}\equiv n^n\pmod{10^9}$$

因为 $5\times10^6$ 是 $10^9$ 的因数，所以：

$$n^{n\bmod(5\times10^6)}\equiv n^n\pmod{5\times10^6}$$

$$[n\bmod(5\times10^6)]^{n\bmod(5\times10^6)}\equiv n^n\pmod{5\times10^6}$$

同时：

$$[n\bmod(5\times10^6)]^{n\bmod(5\times10^6)}\equiv n^n\equiv x\bmod(5\times10^6)\pmod{5\times10^6}$$

而预处理满足要求的 $n\bmod(5\times10^6)$ 的时间复杂度是可以接受的，那么 $\Theta(1)$ 得出 $n\bmod(5\times10^6)$ 后，枚举 $n$ 即可得出答案，显然最多枚举 $200$ 个。

### 3 代码与记录

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000000ll
#define eu 5000000ll
long long a[eu+2];
int q;
long long ans=0;
long long qp(long long a,long long b,long long p=mod){
	long long res=1;
	while(b){
		if(b&1)res=res*a%p;
		a=a*a%p; b>>=1;
	}
	return res;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("e_1.in","r",stdin);
	freopen("e_1.out","w",stdout);
	#endif
	memset(a,0,sizeof(a));
	for(int i=1;i<=eu;++i){
		if(i%2==0||i%5==0)continue;
		long long w=qp(i,i,eu);
		if(!a[w])a[w]=i;
	}
	scanf("%d",&q);
	for(int ca=1;ca<=q;++ca){
		long long x,y;
		scanf("%lld",&x); y=x%eu;
		ans=a[y];
//		printf("x=%lld y=%lld\n",x,y);
		for(;;ans+=eu){
			if(qp(ans,ans)==x){printf("%lld\n",ans); break;}
		}
	}
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/147581278)

By **dengziyue**

---

