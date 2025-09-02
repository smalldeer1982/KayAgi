# 「SFMOI Round I」Strange Madoka Game

## 题目背景

> いつも君の側にいるから / 无论何时我都与你同在 \
> 儚すぎて / 世界如此虚幻 \
> 消えて行きそうな世界 / 似乎随时随地都会消失 \
> だけど君がいる / 然而只要有你 \
> それだけで守りたいと思った / 我就心甘情愿将它守护

## 题目描述


**本题和 B2 是不同的问题，请分别仔细阅读两题题面。**

**这是一道交互题。**

**提示**：我们在题目描述的最后提供了一份简要的、形式化描述的题面。

圆和焰在玩游戏。

圆在心中想了一个非负整数 $m$，让焰猜出 $m$ 的值。当然，圆不会为难焰，所以 $\textcolor{red}{0}\le m\le 10^{17}$。圆不会作弊，也就是说，**圆不会悄悄更换想好的数字。**

焰可以问圆：对于**正**整数 $x$，$m\bmod x$ 的值是多少。焰需要用最少的询问次数来猜出 $m$ 的值。（为了得到全部分数，最多只能使用 $2$ 次询问。）

圆一共和焰玩了 $T$ 次游戏。然而，焰的数学很差，于是她找来了你，来帮她猜出这 $T$ 次游戏的答案。



**形式化地**：有一个隐藏的非负整数 $m\in [\textcolor{red}{0},10^{17}]$。每次询问给定**正**整数 $x$，回答 $m\bmod x$。用最少的询问次数找出 $m$。共有 $T$ 组测试数据。$m$ 的数值在事先确定，不会根据询问变化，也就是说，**交互库是非适应性的**。

【实现细节】

对于每个测试点，输入一行一个正整数 $T$，表示游戏次数。

对于每组测试数据，你可以用以下的格式发起一次询问：

- $\texttt{? }x$：询问 $m\bmod x$ 的值。你需要保证 $x$ 是**正**整数，且 $x \in \textcolor{red} {[1,4\times 10^8]}$。

	从标准输入流读入一个整数表示答案。特别地，若整数是 $\texttt{-1}$，你的程序已经被判定为 $\texttt{Wrong Answer}$，此时你需要立刻终止程序。

你可以用以下的格式回答答案：

- $\texttt{! }m$：回答 $m$ 的值。

在发起询问后，需要刷新缓冲区，否则可能导致 TLE。

- 在 C++ 中，使用 `fflush(stdout)` 或 `cout.flush()`。 特别地，利用 `std::endl` 来换行也会刷新缓冲区。
- 在 Pascal 中，使用 `flush(output)`。  
- 在 Python 中，使用 `stdout.flush()`。  
- 对于其它语言，可自行查阅文档。

## 说明/提示


#### 数据范围

对于 $100\%$ 的数据，保证 $1\le T\le 100$，$m$ 为非负整数，$\textcolor{red}{0}\le m\le 10^{17}$。

#### 评分方式

记单个测试点中，你的询问次数的最大值为 $Q$。则得分 $\mathrm{score}$ 如下所示：

$$
\begin{aligned}
\mathrm{score}=\begin{cases}
0, & Q\in [81,+\infty) \\
10, & Q\in [11,81) \\
25, & Q\in [3,11) \\
50, & Q\in [0,3) \\
\end{cases}
\end{aligned}
$$

本题得分为所有测试点得分的最小值。

本题数据点的范围是非严格单调递增的。

## 样例 #1

### 输入

```
1

1

2```

### 输出

```

? 2

? 3

! 5```

# 题解

## 作者：asd890123 (赞：3)

将题目进一步形式化：

输出 $p_1 $和 $p_2$ ，评测机会给出对应的 $r_1$ 和 $r_2$ 

$m \bmod p_1 = r_1$

$m \bmod p_2 = r_2$

我们令

$p1 = 4 \times 10^8$

$p2 = p1 - 1$

相邻两数必然互素， $p_1 , p_2$ 互素。

构造一组 $k_1,k_2$ 
使得：

$k_1p_2 \bmod p_1 = r_1$

$k_2p_1 \bmod p_2 = r_2$

得：$k_1 = p_1 - r_1,k_2 = r_2$  即可满足

所以 $m = [(p_1 - r_1)p_2 + p_1r_2]  \bmod p_1p_2$

代码：

```cpp
#include <iostream>

typedef long long LL;

const LL Max = 4e8;
const LL mod = (LL)1e17 + 1;

int main(){

    std::cin.tie(0)->sync_with_stdio(0);

    int T;

    for (std::cin >> T;T--;){

        LL res1,res2;

        std::cout << "? " << Max << std::endl;
        std::cin >> res1;
        std::cout << "? " << Max - 1 << std::endl;
        std::cin >> res2;
        std::cout << "! " << (Max * res2 + (Max - 1) * Max - (Max - 1) * res1) % (Max * (Max - 1)) << '\n';

    }

    return 0;
}
```

---

## 作者：OIer_Hhy (赞：1)

感觉 B1 比 B2 难？

思路非常简单，就是~~重庆轨道交通~~中国剩余定理（CRT）。

不会中国剩余定理的请[右转](https://oi-wiki.org/math/number-theory/crt/)。

观察到数据范围 $m \in[0,10^{17}]$ 以及 $x \in [1,4×10^8]$ 就知道，用两个互质的大数去除 $m$。

这里我们取 $400000000$ 与 $399999999$ 为 $a_1$ 和 $a_2$，得出余数 $r_1$ 与 $r_2$。

之后就是愉快的[板子](https://www.luogu.com.cn/problem/P1495)了！

[my code](https://www.luogu.com.cn/record/179436524)

---

## 作者：hjm777 (赞：1)

### Strange Madoka Game

本题询问时取两个较大的模数 $m_1 = 4 \times 10 ^ 8 - 1, \ m_2 = 4 \times 10^8$，会返回两个余数。

这就成了一个普通的 CRT（中国剩余定理了）。

请注意：**模数一定要较大，否则会出现多个可能的答案**。

```cpp
// Author : hejinming2012
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define dbg(x) cout << #x " = " << (x) << endl
#define quickio ios::sync_with_stdio(false);
#define quickin cin.tie(0);
#define quickout cout.tie(0);
#define q1 399999999
#define q2 400000000
#define maxn 5
using namespace std;
inline int read() {
    int now = 0, nev = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') nev = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { now = (now << 1) + (now << 3) + (c & 15); c = getchar(); }
    return now * nev;
}
void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int M = 1, ans, m[maxn], t[maxn];
int a[5] = {0, 399999999, 400000000}, b[5];
void exgcd(int a, int b, int &x, int &y) {
    if(a % b == 0) x = 0, y = 1;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}
int inv(int a, int p) {
    int x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
signed main() {
    int T; cin >> T;
    while(T--) {
        M = 1, ans = 0;
        cout << "? " << a[1] << endl;
        cin >> b[1], cout.flush();
        cout << "? " << a[2] << endl;
        cin >> b[2], cout.flush();
        M = a[1] * a[2];
        for(int i = 1; i <= 2; i++)
            m[i] = M / a[i], t[i] = inv(m[i] % a[i], a[i]);
        for(int i = 1; i <= 2; i++)
            ans += (__int128)b[i] % M * t[i] % M * m[i] % M, ans %= M;
        cout << "! " << ans << endl;
        cout.flush();
    }
    return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路
考虑如何两步得出答案。

设两个互质的数为 $a$ 和 $b$，且满足 $a\times b>m$。

第一次询问 $a$，第二次询问 $b$，第一次的答案为 $x$，第二次的答案为 $y$。

有：
$$
\begin{aligned}
\begin{cases}
m\equiv x\pmod a\\
m\equiv y\pmod b
\end{cases}
\end{aligned}
$$
用中国剩余定理求解即可。

设 $a\times p\equiv 1\pmod b$，$b\times q\equiv 1\pmod a$。

则答案为 $(x\times b\times q+y\times a\times p)\bmod (a\times b)$。

由于 $a\times b$ 可能大于 $2^{63}$，故可以使用龟速乘或用 `__int128`。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll A=400000000,B=399999999;
ll mypow(ll a,ll b,ll p)//求解xa≡1(mod p) 的一组解
{
	if(b==0)return 1;
	ll mi=mypow(a,b>>1,p);
	mi=mi*mi%p;
	if(b&1)mi=mi*a%p;
	return mi;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		ll x,y;
		cout<<"? 400000000"<<endl;
		cin>>x;
		cout<<"? 399999999"<<endl;
		cin>>y;
		x=-x;
		__int128 ans=__int128(x*mypow(B,A-2,A)*B)+__int128(y*mypow(A,B-2,B)*A);
		while(ans>=0)ans-=A*B;
		ans+=A*B;
		cout<<"! "<<(ll)(ans)<<endl;
	}
	return 0;
}
```

---

## 作者：coderJerry (赞：1)

B2<<B1。
#
比较显然的想法。询问 $a,b$，得到 $a\bmod m=c,b \bmod m =d$。用 exgcd 解个关于 $x,y$ 的二元一次方程 $ax+c=by+d$，输出 $ax+c$ 就可以了。

接下来就是 $a,b$ 的选取。首先为了保证解唯一，则 $ab>10^{17}$。取 $a=316227766,b=316227767$（$\lfloor \sqrt{10^{17}} \rfloor=316227766$）就能过了。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int a=316227766,b=316227767,mod=a*b;
int t,x,y,c,d;
int qmul(int x,int y,int mod){return (x*y-(long long)(x/(long double)mod*y+1e-3)*mod+mod)%mod;}
int exgcd(int a,int b,int &x,int &y) {
    if(!b){x=1;y=0;return a;}
    int d=exgcd(b,a%b,x,y);int t=x;x=y;
    y=t-(a/b)*y;return d;
}
void swap(int a,int b){int t=a;a=b;b=t;}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        cout<<"? "<<a<<endl;cin>>c;
        cout<<"? "<<b<<endl;cin>>d;
        if(d<c){swap(c,d);swap(a,b);}
        int p=exgcd(a,b,x,y),q=d-c,nx=q/p*x,ny=q/p*y;
        int ans=(qmul(nx,a,mod)+c)%mod;cout<<"! "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

询问 $x_{1}=4\times10^8$，$x_{2}=x_{1}-1$，得到 $a$ 和 $b$。

设 $k_{1}=\lfloor m/x_{1}\rfloor$，$k_{2}=\lfloor m/x_{2}\rfloor$。显然只有两种情况：

当 $k_{1}=k_{2}$ 时，$kx_{1}+a=kx_{2}+b$，得到 $a\le b$。此时解得 $k_{1}=b-a$。

否则 $k_{1}+1=k_{2}$。此时解得 $k_{1}=b-a+x_{1}-1$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,x,y) for(ll i=x;i<=y;i++)

const ll x1_=4e8,x2_=4e8-1;
ll q;

int main(){
	cin>>q;

	while(q--){
		ll a,b,m;
		cout<<"? "<<x1_<<endl;
		cin>>a;
		cout<<"? "<<x2_<<endl;
		cin>>b;
		m=(b-a)*x1_+a;

		if(a<=b) cout<<"! "<<m<<endl;
		else cout<<"! "<<(b-a+x1_-1)*x1_+a<<endl;
	}
}
```

---

## 作者：maka_baka (赞：0)

## 形式化题面
交互题，每次询问给定整数 $m$，回答 $x\bmod m$，最多用 2 次询问求得 $x$。

> $x\in[0, 10^{17}]$；$m\in[1,4\times 10^8]$。多组数据，每个测试点不超过 100 组。

## 评价
一道很适合引入中国剩余定理（CRT）的题目。这篇题解面向熟悉快速幂思想，将要学习 CRT 的读者。

这个做法可以小常数地模拟一些数据范围接近变量最大值的题目，如 [BZOJ 2854 civilization](https://hydro.ac/d/bzoj/p/2854)。

## 思路
联想天干地支纪年法：用年份模 10 和 12 的结果来表示年份模 60 的结果。

取两个大质数，设为 $P$，$Q$。根据询问的答案 $m_1$，$m_2$ 可以列出方程组
$$\begin{cases}
x \bmod P = m_1\\
x \bmod Q = m_2
\end{cases}$$
为什么用质数？首先我们希望 $\text{lcm}(P,Q)$ 能涵盖所有 $x$ 的范围；其次希望询问出的结果能比较简单地合并解出 $x$。满足这两个原则下，比较简单的选择是质数（天生互质、方便寻找、方便合并）。

“比较简单地合并”能有多简单？我们想设
$$
x \equiv w_1m_1+w_2m_2 \pmod {PQ}
$$
- $w_1$ 是 $Q$ 的倍数，而且除以 $P$ 的余数是 1。
- $w_2$ 是 $P$ 的倍数，而且除以 $Q$ 的余数是 1。

可以验证这样的形式符合上面的方程组，实际上这是 CRT 的特殊形式。由于已经要求 $PQ$ 包含所有 $x$ 的范围，这里的同余号实际能取等。

## 代码实现
这是寻找 $P$ 的代码。要寻找 Q，从 $i$ 的起点修改为 $P-1$ 即可。
```cpp
using ll = long long; // 后面省略这行

void prime() {
  for (ll i = 1e17; i; i--)
    if ([](int i) -> bool {
      for (int j = 2; j * j <= i; j++)
        if (i % j == 0) return false;
      return true;
    }(i)) {
      std::cout << i << '\n';
      break;
    }
}
```
然后我找到了 $P=399999959$，$Q=399999949$。$M=PQ=159999963200002091>1.5\times10^{17}$。

这是寻找 $w_1$ 的代码。要寻找 $w_2$，把 $P$ 换成 $Q$，把 $Q$ 换成 $P$ 即可。
```cpp
void weight() {
  for (ll i = 1; i < P; i++)
    if (i * Q % P == 1) {
      std::cout << i << '\n';
      break;
    }
}
```
我找到了 $w_1=143999966840001887$，$w_2=15999996360000205$。

接着是合并。因为相乘的两个数 $x_i$、$m_i$ 的数量级比较大，会溢出，所以模仿快速幂的做法（二进制拆解，分解为多个数求和），设计出算乘法的程序。注意乘法是在模 $M=PQ$ 的意义下进行的。
```cpp
const ll M = P * Q;

ll multiply(ll x, ll y) {
  ll a = 0;
  while (y) {
    if (y & 1) a = (a + x) % M;
    x = x * 2 % M, y >>= 1;
  }
  return a;
}
```

## AC Code
```cpp
#include <iostream>
using ll = long long;
const ll w1 = 143999966840001887ll,
      w2 = 15999996360000205ll, 
      M = 159999963200002091ll;

ll f(ll x, ll y) {
  ll a = 0;
  while (y) {
    if (y & 1) a = (a + x) % M;
    x = x * 2 % M, y >>= 1;
  }
  return a;
}

int main() {
  int t; std::cin >> t; while (t--) {
    ll m1, m2;
    std::cout << "? 399999959" << std::endl;
    std::cin >> m1;
    std::cout << "? 399999949" << std::endl;
    std::cin >> m2;
    std::cout << "! " << (f(w1, m1) + f(w2, m2)) % M << std::endl;
  }
}
```

---

## 作者：RegGniy (赞：0)

$m \le 10^{17}$ ，输出两个数$x_1 x_2$，返回
$\begin{cases}
y_1 = m \bmod x_1\\
y_2 = m \bmod x_2
\end{cases}$ 。

---

 由于本题 $m$ 范围较小，可以用比较取巧的方法。
 
 易发现 $4 \times 10^8 \times (4 \times 10^8 - 1) > 10^{17}$ ，则取 $x_1 = 4 \times 10^8 $ 和 $x_2 = 4 \times 10^8 - 1$ ，有 $m<x_1 \times x_2$。

 设 $k_1 k_2$ ，可列式
$\begin{cases}
m = k_1 \times x_1 + y_1\\
m = k_2 \times x_2 + y_2
\end{cases}$ 。

 由 $m < x_1 \times x_2$ ，有 $k_2 = k_1$ 或 $k_2 = k_1 + 1$ 。

- $k_2 = k_1$ 时， $y_2 - k_1 = y_1$ ，有 $y_2 \ge y_1$ 。（ $k_1$ 可以为 $0$ ）

- $k_2 = k_1 + 1$ 时， $y_2 + x_2 - k_1 = y_1$ 有 $y_2 < y_1$ 。（显然 $k_1 < k_2 < x_2$）

因此只需要判断 $y_1$ 与 $y_2$ 的大小关系就能计算出 $m$ 。

---

 最后给出代码：
```cpp
#include<iostream>
#define X 400000000
using namespace std;
int main()
{
	long long T,y1,y2,m;
	
	cin>>T;
	
	for (int i = 0; i < T; i++)
	{
    	cout << "? " << X << endl;//两次输出并输入余数
		cin >> y1;
		cout << "? " << X - 1 <<endl;
        cin >> y2;
    	if (y1 > y2) y2 += X - 1;//判断y1y2大小关系 
		m = X * (y2 - y1) + y1;
		cout << "! " << m << endl;
	}
	
	return 0;
}
```

---

## 作者：anke2017 (赞：0)

**更新：忘记中国剩余定理只要互质，不用都是质数了。已修改相关描述。**

### 题意

有一个 $x$ 满足 $0\le x\le 10^{17}$，你可以询问两次，每次选定一个 $m$（$1\le m\le 4\times10^8$），得到 $x\bmod m$。求 $x$ 的值。

### 正题

首先，每次询问后，我们可以得到的是一个**同余式**（即 $x \bmod m = x'$）

发现只能问两次。那么显然问的数越大，得到的结果越有价值。（感性理解，因为得到这个结果的概率更小了）

同时，我们想到可以用**中国剩余定理**来合并得到的两个同余式，这可以在两次询问以内得到 $x \bmod m_1 m_2$，在 $m_1,m_2\approx 4\times10^8$，接近题目给定范围时，可以发现，$m_1 m_2\approx 1.6\times 10^{17}>10^{17}$，即 $m_1 m_2$ 超过 $x$ 的范围。也就是说，**合并后的 $x\bmod m_1 m_2$ 等于 $x$**。

为了中国剩余定理的正确性，需要询问两个**互质的数**，这里我直接取了两个质数。

### 代码

```cpp
#include<iostream>

using namespace std;

#define int long long

int mod1=386778277,mod2=357502601;//两个大质数

long long n[11],m[11],s=1;

long long qpow(long long a,int b,int mod)//快速幂
{
    long long ans=1;
    while(b)
    {
        if(b&1)ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return ans;
}

signed main()
{
    int t;cin>>t;
    while(t--){
        s=1;
        cout<<"? "<<mod1<<endl;
        cin>>m[1];n[1]=mod1;
        cout<<"? "<<mod2<<endl;
        cin>>m[2];n[2]=mod2;
        int a=2;//以下为 CRT
        long long x=0;
        for(int i=1;i<=a;i++)s*=n[i];
        for(int i=1;i<=a;i++)
        {
            long long tmp=s/n[i];
            x=(x+((__int128)((tmp*m[i])%s)*qpow(tmp,n[i]-2,n[i])%s))%s;
//炸 long long了，就强转 __int128
        }
        x%=s;
        cout<<"! "<<x<<endl;//正常时不应使用 endl
//IO 交互题时才得用
    }
    return 0;
}
```

---

