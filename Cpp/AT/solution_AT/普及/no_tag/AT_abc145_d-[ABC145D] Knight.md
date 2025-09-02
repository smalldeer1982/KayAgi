# [ABC145D] Knight

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc145/tasks/abc145_d

二次元グリッドの原点 $ (0,0) $ にチェスのナイトの駒があります。

ナイトの駒はマス $ (i,j) $ にあるとき $ (i+1,j+2) $ か $ (i+2,\ j+1) $ のどちらかのマスにのみ動かすことができます。

ナイトの駒をマス $ (X,Y) $ まで移動させる方法は何通りありますか？

$ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X\ \leq\ 10^6 $
- $ 1\ \leq\ Y\ \leq\ 10^6 $
- 入力中のすべての値は整数である。

### Sample Explanation 1

$ (0,0)\ \to\ (1,2)\ \to\ (3,3) $ と $ (0,0)\ \to\ (2,1)\ \to\ (3,3) $ の $ 2 $ 通りが考えられます。

### Sample Explanation 2

$ (2,2) $ にナイトの駒を移動させることはできません。

### Sample Explanation 3

方法の数を $ 10^9+7 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
999999 999999```

### 输出

```
151840682```

# 题解

## 作者：洛璟 (赞：2)

## Solution：

大概是黄+到绿题的难度。

有些人可能第一眼想到的是dp，但是由于其极大（确信）的数据范围，dp明显会爆炸。所以大家应该会想到用数学方法解决。

那么在经过不懈地推式子之后，我们发现了第一个规律，两边长相加必定为3的倍数，否则无解，同时，我们也会得到一个二元一次方程，通过此我们就可以得到向右两步与向右一步的走法的个数（易证这两种走法的步数固定，建议自己好好推一推）。

有了个数，同时也确定了它们个数不变，很容易想到只能改变这些步数的先后顺序。那么我们也就不难想到这道题是组合数数论题了，设一共要走 $n$ 步，向右两步的有 $m$ 步，一共的走法数量就是$C_{n}^{m}$。

组合数公式：$C_{n}^{m}= $ $ \frac{n!}{m!(n-m)!}$，但是由于分数取模后答案不同，因此我们需要引进乘法逆元的概念，因为乘法取模后答案不变，这就可以把分数除法变为乘法从而得以取模，也就是说，我们可以**大概**认为，乘法逆元就是原除数在模P的情况下的倒数。

如果 $a\times b ≡ 1 (mod\space p)$，则称 $a$ 是 $b$ 的逆元，$b$ 是 $a$ 的逆元，但 $a$ 与 $p$ 必须互质。根据费马小定理，我们得出 $a$ % $p$ 的乘法逆元就是 $a^{p-2}$（当定理去记罢）。

更多、更详细请看（作者非本人，但我觉得写得不错 ~~（我没有收钱）~~）：

[Link](https://blog.csdn.net/liuzibujian/article/details/81346595)

那么有了这个这道题就简单了。

我们先把$ \frac{n!}{m!(n-m)!}$中的 $n!$与 $(n-m)!$ 单独取出进行除法，即把 $(n-m)$ 到 $n$ 的所有数相乘，然后去单独计算 $m$ 的逆元来进行组合数的计算。不过应当注意的是，这里的逆元应当去用快速幂去算，这里的余数非常大，若不用快速幂，则会TLE。

其余详见代码：
```cpp
//开long long则会WA 1个点，但是开了unsigned long long则AC
//所以在过程中不会出现负数且可能会爆long long的代码中记得要用ull இ௰இ
#include<bits/stdc++.h>
#define int unsigned long long
#define mo 1000000007
using namespace std;
int n, m;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int Pow(int b, int base)//快速幂，不懂的右转题库快速幂模板
{
    int ans = 1;
    while (base > 0)
    {
        if (base & 1 == 1)
        {
            ans = (ans * b) % mo;
        }
        b = (b * b) % mo;
        base = base >> 1;
    }
    return ans;
}
int C(int n, int m)//求组合数
{
    if (n < m)
        return 0;
    int ans = 1;
    for (int i = 1;i <= m;i++)
    {
        ans = (ans * (n - m + i) % mo * Pow(i, mo - 2) % mo) % mo;
    }
    return ans;
}
//关于ans=……的我解释一下，这也是核心代码
//首先ans是组合数答案，因此ans应当乘上后面的玩意
//而(n-m+i)则是上文提到的n!/（n-m）！的实现代码，从(n-m)开始乘到n
//Pow中计算的则是i的乘法逆元i^(p-2),这里实现分母中的m!
signed main()
{
    n = read();
    m = read();
    if ((n + m) % 3 != 0)
    {
        printf("0");
        return 0;
    }
    int tmp = (n + m) / 3;
    int a = n - tmp, b = m - tmp;//二元一次方程求解向右一步或两步的个数
    printf("%lld", C(a + b, b));
    return 0;
}
```


---

## 作者：Escapism (赞：0)

国际象棋的题目多，花样也多。

# 题意

不难理解。

# 思路

第一眼大部分人的想法是 DP，然而这个数据范围......

所以要用**数学方法**。

首先摆一摆可以发现，根据题目中的走法限制（就是在一个马的八个可走的格子中只能向右上的两个格子走），它只能走到 $x+y$ 为 $3$ 的倍数的地方。

要证明也不难，设当前所在的位置为 $(i,j)$，则无论走哪一格下面的 $i,j$ 之和都是 $i+j+3$。因为初始的格子是 $i=j=0$，所以之后能走到的格子都是 $i+j$ 能整除 $3$ 的。

因而所有 $(x+y)$ 无法整除 $3$ 的都输出 $0$。

---

假设 $a$ 是向上两格向右一格的步数，$y$ 是向右两格向上一格的步数，那么显然有 $2a+b=m$ 和 $a+2b=n$，然后就可以解出 $a,b$。

考虑最终的方案数，也就是在总共的次数中选若干次作为向右两步（或者向右一步也行）的次数，就可以用组合数了。

显然最终答案是 $C_{a+b}^a$，写成分数形式就是 $\dfrac{(a+b)!}{a! \times b!}$。

可能有人想暴力去求这个东西，或者说约分之后暴力去求这个东西。由于有模数存在，所以就算暴力有足够的速度也会受到局限。

因而得加一个[逆元](https://oi-wiki.org/math/number-theory/inverse/)。

# 代码

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
 
const int MOD = 1e9 + 7;
ull n, m;
ull Pow(ull k, ull base){//快速幂
    ull ans = 1;
    while (base > 0){
        if (base & 1 == 1) ans = (ans * k) % MOD;
        k = (k * k) % MOD;
        base = base >> 1;
    }
    return ans;
}
ull C(ull n, ull m){ //组合数
    if (n < m) return 0;
    ull ans = 1;
    for (ull i = 1;i <= m;i++) ans = (ans * (n - m + i) % MOD * Pow(i, MOD - 2) % MOD) % MOD;
    return ans;
}
int main(){
	cin>>n>>m;
    if ((n + m) % 3 != 0){
        printf("0");
        return 0;
    }
    int tmp = (n + m) / 3;
    int a = n - tmp, b = m - tmp;//二元一次方程求解向右一步或两步的个数
    printf("%lld", C(a + b, b));
    return 0;
}
```

[原题 AC 记录](https://atcoder.jp/contests/abc145/submissions/38759574)

---

## 作者：极寒神冰 (赞：0)

设$x,y$表示走了$x$次$(+2,+1)$,$y$次$(+1,+2)$.$x,y$均为非负整数.

有$2x+y = n$和$2y+x=m$.

解得$x+y= \frac {n+m}{3} $ 以及$x=n- \frac{n+m}{3},y=x=m- \frac{n+m}{3}$

方案数为 $\binom{x}{x+y}$

```
const int qwq=7000010;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}

inline int check(){
	if((n<tot)||(n+m)%3||n>(2*tot)){
		return puts("0")&0;
	}
	return 1;
}
signed main()
{
	init_C();	
	{
		n=read(),m=read();		
		tot=(n+m)/3;
		if(!check()) return 0;
		printf("%lld\n",F[tot]*Finv[n-tot]%mod*Finv[tot*2-n]%mod);
	}
}
```


---

## 作者：shenmadongdong (赞：0)

首先显然必须 $(x+y)\ mod\ 3=0$ ，否则一定输出 0  

否则它会走 $(x+y)/3$ 步，其中有 $x-(x+y)/3$ 步在横坐标上移动的两个单位长度  

那么方案数就是 $C((x+y)/3,x-(x+y)/3)$，注意组合数在 $n<m$ 或 $m<0$ 时要特判输出 0

组合数的具体求解过程：  
我们知道，$C(n,m)=\dfrac{n!}{m!\ (n-m)!}$  

然后可以把阶乘预处理出来，再对底下求个逆元即可

不知道逆元是什么的请点[这里](https://oi-wiki.org/math/inverse/)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const unsigned mod=1e9+7;
long long x,y,fac[7000010];
long long ksm(long long x,long long y){long long ret=1;while(y){if(y&1ll)ret=ret*x%mod;y>>=1ll;x=x*x%mod;}return ret;}
//快速幂
int main()
{
    fac[0]=1;
    for(int i=1;i<=7000000;i++) fac[i]=fac[i-1]*i%mod;//预处理阶乘
    cin>>x>>y;
    if ((x+y)%3!=0||x<(x+y)/3||x>2*(x+y)/3) return puts("0"),0;//判掉特殊情况
    cout<<fac[(x+y)/3]*ksm(fac[x-(x+y)/3],mod-2)%mod*ksm(fac[(x+y)/3*2-x],mod-2)%mod<<'\n';//计算组合数并输出
    return 0;
}
```

---

