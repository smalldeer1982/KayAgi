# Remainders Game

## 题目描述

Today Pari and Arya are playing a game called Remainders.

Pari chooses two positive integer $ x $ and $ k $ , and tells Arya $ k $ but not $ x $ . Arya have to find the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/74cc0e497602c391113efb814a12e06ebc180bd8.png). There are $ n $ ancient numbers $ c_{1},c_{2},...,c_{n} $ and Pari has to tell Arya ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/d6826eab3568be14654e0e163000c670f1c64e14.png) if Arya wants. Given $ k $ and the ancient values, tell us if Arya has a winning strategy independent of value of $ x $ or not. Formally, is it true that Arya can understand the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/74cc0e497602c391113efb814a12e06ebc180bd8.png) for any positive integer $ x $ ?

Note, that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) means the remainder of $ x $ after dividing it by $ y $ .

## 说明/提示

In the first sample, Arya can understand ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/b93dce9b9ef400fa12cce1ab52784e3449739731.png) because $ 5 $ is one of the ancient numbers.

In the second sample, Arya can't be sure what ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/34daaca50b46751e5d9e1271dc07f186fd9fd248.png) is. For example $ 1 $ and $ 7 $ have the same remainders after dividing by $ 2 $ and $ 3 $ , but they differ in remainders after dividing by $ 7 $ .

## 样例 #1

### 输入

```
4 5
2 3 5 12
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 7
2 3
```

### 输出

```
No
```

# 题解

## 作者：Audrey_Hall (赞：17)

#### [题目传送](https://www.luogu.com.cn/problem/CF687B)

#### [博客食用（如果需要的话）](https://www.luogu.com.cn/blog/fsx/ti-xie-cf687b-remainders-game)

#### 题目简述

给出一个数字 $k$，以及 $n$ 个数字 $\{c_1,c_2,...,c_n\}$，

询问是否对于任意的正整数 $x$，都能根据 $x\ \bmod\ c_i(i=1,2,...,n)$ 的值，求出**唯一的** $x\ \bmod\ k$。

#### 本篇题解的不同之处？

针对一些结论给出了**简单的**证明。

#### 前置知识（不会也没关系，反正会有**简单**证明）

我们先将题目换一个形式：

已知 $\left\{\begin{matrix}x\ \bmod\ c_1=b_1\\x\ \bmod\ c_2=b_2\\...\ ...\\x\ \bmod\ c_n=b_n\end{matrix}\right.$，

询问在 $\bmod\ k$ 的情况下 $x$ 是否有唯一解。

看到这个形式，我们可以很容易地想到[中国剩余定理（CRT）](https://www.luogu.com.cn/problem/P1495)，

再观察题面可以发现 $\{c_1,c_2,...,c_n\}$ 其实并不两两互质，所以这并不是中国剩余定理（或者说并不完全是），而是[扩展中国剩余定理（exCRT）](https://www.luogu.com.cn/problem/P4777)。

~~在脑子中进行了一个查的询，发现脑子中没有留下任何中国剩余定理的相关内容（我太菜了 QAQ），于是匆匆翻找笔记 ing~~

找到了残存的笔记：

$\left\{\begin{matrix}x\ \bmod\ c_1=b_1\\x\ \bmod\ c_2=b_2\end{matrix}\right.\to x\equiv \colorbox{black}{\color{black}数据删除}(\bmod\ \text{lcm}(c_1,c_2))$

好，虽然只找到了一点，但对于解决这道题来说够用了。

#### 题目分析（已经充分掌握前置知识的话可跳过前半部分）

首先，观察题面，发现在不考虑 $\bmod\ k$ 的情况下一定是存在解的

（因为是先有的 $x$，才有的 $\{b_1,b_2,...,b_n\}$）。

假设已经有了一个解 $x'$ 满足上述方程，那么 $x'$ 一定可以写成 $x'=c_1+k_1b_1=c_2+k_2b_2(k_1,k_2\in Z)$ 的形式，

于是 $x''=x'+k_3\text{lcm}(c_1,c_2)(k_3\in Z)$ 也一定是一个解，

因此满足以上同余方程的解有无穷多个，并且两两之间至少相差 $\text{lcm}(c_1,c_2)$，

于是上述同余方程在 $\bmod\ \text{lcm}(c_1,c_2)$ 下至少有一个解。

那么是否有唯一解呢？有如下证明：

假设存在 $0\le x,y<\text{lcm}(c_1,c_2)$，满足：

$\left\{\begin{matrix}x\ \bmod\ c_1=b_1\\x\ \bmod\ c_2=b_2\end{matrix}\right.$，$\left\{\begin{matrix}y\ \bmod\ c_1=b_1\\y\ \bmod\ c_2=b_2\end{matrix}\right.$

那么可得：

$\left\{\begin{matrix}(x-y)\ \bmod\ c_1=0\\(x-y)\ \bmod\ c_2=0\end{matrix}\right.$

因此，$\text{lcm}(c_1,c_2)|(x-y)$，

但 $0\le x,y<\text{lcm}(c_1,c_2)$，

于是只存在一种情况：$x=y\to(x-y)=0$。

所以上述同余方程在 $\bmod\ \text{lcm}(c_1,c_2)$ 的情况下有且仅有一个解。

以上也就是对 $\left\{\begin{matrix}x\ \bmod\ c_1=b_1\\x\ \bmod\ c_2=b_2\end{matrix}\right.\to x\equiv \colorbox{black}{\color{black}数据删除}(\bmod\ \text{lcm}(c_1,c_2))$ 的具体解释。

同理可证，在其它长度为 $\text{lcm}(c_1,c_2)$ 也仅存在唯一解，

所以我们刚刚写的 $x''=x'+k_3\text{lcm}(c_1,c_2)(k_3\in Z)$ 其实包含了所有解，

我们可以发现，对于这些解来说只要 $k|\text{lcm}(c_1,c_2)$，那么在 $\bmod\ k$ 的情况下的结果是唯一的，即 $x'\ \bmod\ k$。

对于 $\left\{\begin{matrix}x\ \bmod\ c_1=b_1\\x\ \bmod\ c_2=b_2\\...\ ...\\x\ \bmod\ c_n=b_n\end{matrix}\right.$ 来说，与 $\left\{\begin{matrix}x\ \bmod\ c_1=b_1\\x\ \bmod\ c_2=b_2\end{matrix}\right.$ 同理。

因此我们只需要判断 $k$ 是否满足 $k|\text{lcm}\{c_1,c_2,...,c_n\}$ 即可。

值得注意的是，直接计算 $\text{lcm}\{c_1,c_2,...,c_n\}$ 的话在 `long long` 中也会溢出，

对此有两种解决方式：

1. 将 $k$ 和 $\text{lcm}\{c_1,c_2,...,c_n\}$ 质因数分解，对每个 $p_k^a$ 判定是否存在 $p_c^b$ 使得 $p_k^a|p_c^b$。

2. 提前取模，防止溢出（~~好事多模嘛~~）

本题解采用的是第二种。

#### Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline void read(int &n){
	n=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')n=(n<<1)+(n<<3)+(ch^48),ch=getchar();
	n*=f;
}
//快读(int)
inline void read_(ll &n){
	n=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')n=(n<<1)+(n<<3)+(ch^48),ch=getchar();
	n*=f;
}
//快读(long long) 
inline void print(int n){
	if(n<0)putchar('-'),n=-n;
	if(n>9)print(n/10);
	putchar(n%10+'0');
}
//快写(int)
inline void print_(ll n){
	if(n<0)putchar('-'),n=-n;
	if(n>9)print_(n/10);
	putchar(n%10+'0');
}
//快写(long long) 
inline void check1(){puts("完成啦！");}
inline void check2(){puts("竟然已经运行到这里了吗？");}
inline void check3(){puts("我已经完全爱上 Warma 啦！");}
//调试程序 
int n,k,c;ll lcm=1;
inline int gcd(int a,int b){return !b?a:gcd(b,a%b);}
//求 gcd
int main(){
	read(n),read(k);
//	读入 
	for(int i=1;i<=n;i++)read(c),(lcm=lcm/gcd(lcm,c)*c)%=k;
//	读入+lcm 计算(注意先除后乘)+取模 
	if(lcm%k)puts("No");else puts("Yes");
//	取模+判断 
	return 0;
}
```

#### [提交记录](https://codeforces.com/contest/687/submission/177713049)

---

## 作者：Grow2011 (赞：13)

# 题意：

给数 $k$ 和 $n$ 个正整数 $a_1$ 到 $a_n$。如果任意数 $x$，可以通过 $x\bmod a_i$ 的值推出 $x\bmod k$ 的值则输出 `Yes` 否则输出 `No`。

# 题解：

由 [EXCRT](https://www.luogu.com.cn/problem/P4777) 可以知道，通过以下两个式子：

$$ \left\{ \begin{aligned} &x\equiv{s_i}\pmod{a_i}\cr &x\equiv{s_{i+1}}\pmod{a_{i+1}}\end{aligned} \right. $$

得出这个式子：

$$x\equiv{\colorbox{black}{\color{black}某个式子}}\pmod{\operatorname{lcm}(a_i,a_{i+1})}$$

其中，$\operatorname{lcm}$ 表示最小公倍数。

虽然我不太懂中国剩余定理，但我们只需要知道这么多就够了。（相当于黑色部分不需要知道）

那上面这个式子到底告诉了我们什么？

这告诉了我们，通过 $x$ 模 $a_i$ 和 $a_{i+1}$ 的值，我们可以得出 $x$ 模 $a_i$ 和 $a_{i+1}$ 的最小公倍数的值！

于是乎，我们可以求出所有 $a_i$ 的最小公倍数，看他是不是 $k$ 的倍数即可。

# AC代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,c,p = 1;
inline int read(){
    register char c = getchar();
	register int f = 1,x = 0;
    while(c<'0'||c>'9'){
    	if(c=='-')f = -1;
		c = getchar();
	}
    while(c>='0'&&c<='9')x = (x<<3)+(x<<1)+c-'0',c = getchar();
    return x*f;
}//快读 
int gcd(int a,int b){return a%b==0?b:gcd(b,a%b);}//最大公因数 
int lcm(int a,int b){return a*b/gcd(a,b);}//最小公倍数 
signed main(){
	cin >> n >> k;
	for(int i = 1;i<=n;i++){
		c = read();
		p = (lcm(p,c))%k;//记得取模 
	}
	if(p%k==0)cout << "Yes";
	else cout << "No";
	return 0;
}
```

---

## 作者：andyli (赞：9)

题意：  
Pari和Arya协定一个数$k$，以及$n$个数${c_i}$，Pari想一个数$x$，并把$x~\text{mod}~c_i (i=1..n)$告诉Arya，问是否对于任意的$x$，Arya都能猜出$x~\text{mod}~k$。  

$1\leq n,k,c_i\leq 10^6$  

容易猜出，答案为“是”当且仅当$k|\text{lcm}\{c_i\}$，可将$k$质因数分解，对于每个$p^a$判定是否存在$p^a|c_i$即可。  

最优解排行第1，总用时$2.79s$。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
const int maxn = 1000005;

int C[maxn];
int main()
{
    int n, k;
    io.read(n, k);
    for (int i = 1; i <= n; i++)
        io.read(C[i]);
    int m = sqrt(k);
    for (int i = 2; i <= m; i++) {
        if (k % i == 0) {
            int t = 1;
            while (k % i == 0)
                t *= i, k /= i;
            bool flag = false;
            for (int i = 1; i <= n && !flag; i++)
                if (C[i] % t == 0)
                    flag = true;
            if (!flag) {
                writeln("No");
                return 0;
            }
        }
    }
    bool flag = false;
    for (int i = 1; i <= n && !flag; i++)
        if (C[i] % k == 0)
            flag = true;
	writeln(flag ? "Yes" : "No");
    return 0;
}
```

---

## 作者：是个汉子 (赞：8)

#### 题目大意

现选定一个 $k$ 与 $x$， $x$ 未知，给出 $n$ 个数 $c$ ,可否根据 $x$ 与 $c$ 之间模数得出 $x$ 模 $k$ 

#### 解题思路

据 $ex$ 中国剩余定理，可以知道

我们总可以将两个同余式子
$$
\begin{cases}x\equiv a_1\pmod {m_1}\\x\equiv a_2\pmod {m_2}\end{cases}
$$
转化为一个式子
$$
x\equiv k_1m_1+a_1\pmod {\operatorname{lcm}(m_1,m_2)}
$$
其中 $k_1$ 为方程 $k_1m_1-k_2m_2=a_2-a_1$ ​的一个解

而易证当 $d|m$ 时，且 $x\mod m$ 确定时 $x\mod d$ 也就确定了

由此，我们只需求出所有的数之间的最小公倍数，观察k是否为这些数中任一的因数即可

#### 代码

```c++
#include<iostream>
#include<cstdio>
#define ll long long

using namespace std;
ll n,k,tmp,x;

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
	return x*f;
}

ll gcd(ll m,ll n){
	return n==0?m:gcd(n,m%n);
}

ll lcm(int x,int y){
	return x/gcd(x,y)*y;
}

int main(){
	n=read();k=read();
	tmp=1;
	for(int i=1;i<=n;i++){
		x=read();
		if(!tmp) continue;
		tmp=lcm(tmp,x);
		tmp%=k;
	}
	printf("%s\n",!tmp?"Yes":"No");
	return 0;
}
```



---

## 作者：black_trees (赞：3)

本篇题解是对题解区的一个疑似正确的做法的补充。

----

本题的做法是简单的。

可以注意到问题等价于给定一个类似 EXCRT 形式的线性同余方程组，问是否有解。

不难想到有解当且仅当 $k \mid \operatorname{lcm}(a_1, a_2, \dots, a_n)$。

这个分解一下质因数就好了。

但是在题解区看到了不一样的做法（[这篇](https://www.luogu.com.cn/blog/676613/ti-xie-cf687b-remainders-game)和[这篇](https://www.luogu.com.cn/blog/jasony/cf687b-remainders-game)）。

大概做法是，判断这个东西是否能被 $k$ 整除：

$val = \operatorname{lcm}(\operatorname{lcm}(\operatorname{lcm}(a_1, a_2)\bmod k, a_3), \dots)\bmod k$

也就是认为 $val = \operatorname{lcm}(a_1, a_2, \dots, a_n)$。

思考一下就能知道这个东西的值和 $\operatorname{lcm}(a_1, a_2, \dots, a_n)$ 不一定相等。

这个“假结论”实际上认为 $\operatorname{lcm}$ 在模意义下也是具有结合律的

可以构造出特例：$\{a_i\} = \{6, 9, 2\}, k = 5$。

因为 $\operatorname{lcm}(6, 9, 2) \equiv 18 \equiv 3 \pmod 5$，而 $\operatorname{lcm}(6, 9) \equiv 3 \pmod 5$ 且 $\operatorname{lcm}(3, 2) \equiv 6 \equiv 1\pmod 5$。

但是这种做法仍然能通过本题，而题解区使用该做法的两篇题解均没有说明这个问题。

笔者思考了一下，认为存在以下结论：

记 $Lcm = \operatorname{lcm}(a_1, a_2, \dots, a_n)$，则有：

> 对于任意 $k$，满足：
>
> 1. 若 $k \mid Lcm$，则 $k \mid val$。
> 
> 2. 若 $k \nmid  Lcm$，则 $k \nmid  val$。
>
> 换句话说，$Lcm, val$ 这两个数在模 $k$ 意义下绝不可能只有一个为 $0$。

如果这个结论是正确的，那么上述的所谓“假做法”应当是正确的。

笔者目前还不会验证这个结论，但是经过暴力枚举，并加以构造验证之后，发现这个猜想有极大可能是对的。

在大约 $10^7$ 次验证里，仍然没有反例存在，验证过程可以看笔者的[博客](https://enonya.github.io/blog/2023-07-10/)。

我们可以假设，笔者的猜想应该是几乎正确的。

鉴于这个做法能通过本题，并且在随机的多组数据下仍然正确，所以我们暂且认为它是正确的，如果后续能够严谨证明这个结论，将作补充。

---

upd：我是 shaber，这结论巨好证。

就是你考虑 $\operatorname{lcm}$ 的本质是什么，对于 $\operatorname{lcm}(x, y)$，它的本质是对于 $x, y$ 两个数质因子集合之并集当中的每个质因子 $p_i$，对 $p_i$ 在 $x, y$ 中分别的指数取 $\max$。

第一个部分是 Easy 的，考虑第二个部分。

然后如果 $k \nmid Lcm$，那么说明对于 $k = \prod p_i^{c_i}$，存在至少一个 $a_j$ 使得 $p_i$ 在 $a_j$ 中对应的指数 $d < c_i$。

而对于 $val$，它的每一步过后都对 $k$ 取了模，值域为 $[0, k)$，指数的大小不可能增加，所以如果 $k \nmid Lcm$，那么 $k \nmid val$。

所以笔者的上述结论是正确的。

---

另外补充一个东西，虽然和这个想法没有太大关系：

“假结论”在值域越大的情况下正确率越高，在值域为 $[1, 10]$ 的时候大约为 $96.7\%$，在值域为 $[1,50]$ 的时候大约为 $99.3\%$。

---

## 作者：Fkxxx (赞：0)

### 题意简述

给出 $n,k,c_1,c_2,...,c_n$，和 $x \bmod c_i$ 问是否能求得 $x \bmod k$。

### 算法描述

似乎是一道中国剩余定理的题，最后只是需要给出是否能求解。~~如果你不会中国剩余定理，通过计算，输出 `Yes` 可得 50 pts。~~

众所周知，如果 $a \bmod bc = x$ 那么 $a \bmod b = x \bmod c$，所以知道 $x$ 模 $k$ 的倍数就能求出 $x \bmod k$。

具体实践起来十分简单，其实我们还要用到扩展中国剩余定理而得到。

$$x\equiv s_i\pmod {a_{i}}$$

$$x\equiv s_{i+1}\pmod{a_{i+1}}$$

所以我们直接求所有 $a_i$ 的 $\operatorname{lcm}$，判断它是否为 $k$ 的倍数即可。

**记得在 $\operatorname{lcm}$ 的过程中对 $k$ 取模。**

---

## 作者：liyp (赞：0)

## 翻译
第一个人和第二个人协定一个数 $k$，以及 $n$ 个数 $c_i$，第一个人想一个数 $x$，并把 $x\mod{c_i}$ 的值告诉第二个人，问是否对于任意的 $x$，第二个人都能猜出 $x\bmod k$。
## 思路
~~哇！好明显的剩余（余数）问题~~

这一题很明显就是一道剩余（余数）问题。

我们可以一步步推出，通过对 $x$ 模 $a_i$ 和 $a_{i+1}$ 的值，得出 $x$ 模 $a_i$ 和 $a_{i+1}$ 的最小公倍数的值。

于是我们只需要求出 $a$ 数组所有元素的最小公倍数，看看这个和是不是 $k$ 的倍数。
## 完整代码
```cpp
#include <bits/stdc++.h>
#define int long long//不开 long long 见祖宗
#define LL long long
using namespace std;
const int MAXN = 1e6 + 10;//数据范围
int a[MAXN], n, m;
LL ans = 0;
inline int read()//快读
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch<'0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
void write(string x)//快写
{
	for (auto c : x) {
		putchar(c);
	}
}
int gcd(int a, int b) {//最大公因数
	return a % b == 0 ? b : gcd(b, a % b);
}
int lcm(int a, int b) {//最小公倍数
	return a * b / gcd(a, b);
	
}
signed main(){//主函数
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T;
	int x = 1;
	n = read(); m = read();//输入
	for (int i = 1; i <= n; i++) {
		a[i] = read();//输入
		x = lcm(x, a[i]) % m; //操作
	}
	if (x % m == 0) {
		write("Yes");
	}
	else write("No");
	putchar('\n');
	return 0;
}
```

---

## 作者：TheShuMo (赞：0)

## 分析

化简题意，可以看作为

$$\begin{cases} x \equiv p_1 \pmod {m_1} \\ x \equiv p_2 \pmod {m_2} \\ \;\;\;\;\vdots \\ x \equiv p_n \pmod {m_n} \end{cases}$$

问能否求出 $x \bmod k$ 的值。

由于题目中并没有给定 $m_1,m_2,m_3,\cdots,m_n$ 是否互质，运用中国剩余定理是无法解决的。

对于仅有两个同余方程的方程组：
$$\begin{cases} x\equiv p_1 \pmod {m_1}\\ x \equiv p_2 \pmod{m_2} \end{cases}\tag{1}$$
我们可以把它化为这样的形式：
$$x = k_1m_1 +p_1= k_2 m_2 + p_2 \tag{2}$$

移项，得：
$$k_1m_1 -k_2m_2 = p_2-p_1 \tag{3}$$
这就是一个典型的二元一次不定方程。根据裴蜀定理，有：

1. 若 $\gcd(m_1,m_2) \mid (p_2-p_1)$ 则原方程有解。
2. 否则，原方程无解。

假设原方程有解，即 $\gcd(m_1,m_2)\mid (p_2,p_1)$，设 $d=\gcd(m_1,m_2)$。
则 $(3)$ 式等价于 $$m_1k_1 \equiv p_2-p_1 \pmod {m_2} \tag{4}$$
等价于 $$\frac{m_1k_1}{d} \equiv \frac{p_2-p_1}{d} \pmod{\frac{m_2}{d}} \tag{5}$$
解得 $$k_1 \equiv (\frac{m_1}{d})^{-1}\times \frac{p_2-p_1}{d}\pmod{\frac{m_2}{d}} \tag{6}$$
即 $$k_1=k\frac{m_2}{d} + (\frac{m_1}{d})^{-1}\times \frac{p_2-p_1}{d} \tag{7}$$
将 $(7)$ 式代入 $(1)$ 式中，可得 $$x = k\frac{m_1m_2}{d} +m_1(\frac{m_1}{d})^{-1}\times \frac{p_2-p_1}{d} + p_1 \tag{8}$$
$(8)$ 式又等价于 $$x \equiv m_1(\frac{m_1}{d})^{-1}\times \frac{p_2-p_1}{d} + p_1 \pmod{\frac{m_1m_2}{d}}\tag{9}$$
令 $(\frac{m_1}{d})^{-1}\times \frac{p_2-p_1}{d} = b$，因为 $\operatorname{lcm}(m_1,m_2)=\frac{m_1m_2}{\gcd(m_1,m_2)}$，所以 $(9)$ 式等于 $$x \equiv m_1b + p_1\pmod{\operatorname{lcm}(m_1,m_2)} \tag{10}$$
自此，我们证明了：若 $(1)$ 式有解，那么它在模 $\operatorname{lcm}(m_1,m_2)$ 下有唯一解。
进而，对于有任意多个的，模数不互质的同余方程组，若它有解，那么它在模 $\operatorname{lcm}(m_1,m_2,\cdots,m_n)$ 的意义下也有唯一解。
推导方法很简单，提取出前两个式子化成 $(10)$ 式的样子，放回去，根据 $\operatorname{lcm}(\operatorname{lcm}(m_1,m_2),m_3) = \operatorname{lcm}(m_1,m_2,m_3)$ 一个个推就得到令最终的答案。

思路类似 P4777 扩展中国剩余定理，大家看完可以去做做。
```
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long

namespace IO {
    #define int long long 
    #define gh getchar
    inline int read(){char ch=gh();int x=0;bool t=0;while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();return t?-x:x;}
    inline char getc(){char ch=gh();while(ch<'a'||ch>'z') ch=gh();return ch;}
    inline void write(int x){if(x < 0){putchar('-');x = -x;}if(x > 9){write(x / 10);}putchar((x % 10 + '0'));}
}
using namespace IO;
using namespace std;
const int Maxn = 100010;
int c[Maxn];
int gcd(int a,int b){
    if(a%b == 0)return b;
    return gcd(b,a%b);
}
signed main(){
    int n = read(), k = read();
    for(int i = 1; i <= n; i++)c[i] = read();
    int lcm = 1;
    for(int i = 1; i <= n; i++){
        lcm = lcm * c[i] / gcd(lcm,c[i]);
        lcm %= k;
    }
    if(lcm == 0)return puts("Yes");
    return puts("No");
}

```

---

## 作者：hsaht2426 (赞：0)

用 $\text{exCRT}$ 的知识可以得到，此题要求的是一堆数的 $\text{lcm}$ 是否为 $k$ 的倍数。

显然不能直接求因为会溢出。

由于此题的特殊性，我们只关心与 $k$ 有关的。

所以我们只用管 $\gcd(c_i,k)$，于是我们对所有 $\gcd(c_i,k)$ 取一个 $\text{lcm}$ 即可，最后判断是否为 $k$。

```cpp

#include<bits/stdc++.h>
using namespace std;

#define ll int
ll n,k,ans=1;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
inline ll lcm(ll a,ll b){
	return 1ll*a*b/gcd(a,b);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		ll x;
		cin>>x;
		ans=lcm(gcd(x,k),ans);
	}
	if(ans==k) cout<<"Yes";
	else cout<<"No";
	return 0;
}

---

## 作者：sto_5k_orz (赞：0)

由扩展中国剩余定理可知，知道了 $x \bmod a_i$，就可以知道 $x \bmod \operatorname{lcm}(a_1,a_2\cdots a_n)$。

那么可以知道 $x\bmod k$ 的话就显然需要 $k\mid \operatorname{lcm}(a_1,a_2\cdots a_n)$ 。

那么考虑给 $1$ 到 $10^6$ 所有数的最小质因子线性筛出来，不会的参考 B3716。

考虑 $k=p_1^{x_1}\times p_2^{x_2}\cdots \times p_m^{x_m}$。

那么对于 $\forall j\in [1,m]$，一定要存在正整数 $1\le i\le n$，满足 $p_j^{x_j}\mid a_i$。

代码实现起来比较抽象，大家自己凑合着看。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000010; int pre[N], p[N], cnt, a[N]; bool f[N];
void init(const int n = 1000000) {
	f[1] = 1; pre[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!f[i]) p[++cnt] = pre[i] = i;
		for(int j = 1; i * p[j] <= n; j++) {
			int k = i * p[j]; f[k] = 1; pre[k] = p[j];
			if(i % p[j] == 0) break;
		}
	}
}
int mx[N]; vector<int> e[N];
signed main() {
	ios::sync_with_stdio(0); int n, k; cin >> n >> k; if(k == 1) cout << "Yes", exit(0); for(int i = 1; i <= n; i++) cin >> a[i]; init();
	n = unique(a + 1, a + 1 + n) - a - 1;
	for(int i = 1; i <= n; i++) {
		int cnt = 0, lst = 0;
		while(a[i] > 1) {
			if(lst == pre[a[i]]) cnt++;
			else cnt = 1, lst = pre[a[i]];
			mx[pre[a[i]]] = max(mx[pre[a[i]]], cnt);
			a[i] /= pre[a[i]];
		}
	}
	int cnt = 0, lst = 0;
	while(k > 1) {
		if(lst == pre[k]) cnt++;
		else cnt = 1, lst = pre[k];
		if(cnt > mx[pre[k]]) {
			cout << "No\n";
			return 0;
		}
		k /= pre[k];
	}
	cout << "Yes";
	return 0;
}
```

---

