# Lucky Tickets

## 题目描述

Gerald has a friend, Pollard. Pollard is interested in lucky tickets (ticket is a sequence of digits). At first he thought that a ticket is lucky if between some its digits we can add arithmetic signs and brackets so that the result obtained by the arithmetic expression was number 100. But he quickly analyzed all such tickets and moved on to a more general question. Now he explores $ k $ -lucky tickets.

Pollard sais that a ticket is $ k $ -lucky if we can add arithmetic operation signs between its digits to the left or right of them (i.e., "+", "-", " $ × $ ") and brackets so as to obtain the correct arithmetic expression whose value would equal $ k $ . For example, ticket "224201016" is 1000-lucky as $ (-2-(2+4))×(2+0)+1016=1000 $ .

Pollard was so carried away by the lucky tickets that he signed up for a seminar on lucky tickets and, as far as Gerald knows, Pollard will attend it daily at 7 pm in some famous institute and will commute to it in the same tram for $ m $ days. In this tram tickets have eight digits. And Gerald wants to make a surprise for Pollard: each day Pollard will receive a tram $ k $ -lucky ticket. The conductor has already agreed to give Pollard certain tickets during all these $ m $ days and he only wants Gerald to tell him what kind of tickets to give out. In this regard, help Gerald pick exactly $ m $ distinct $ k $ -lucky tickets.

## 样例 #1

### 输入

```
0 3
```

### 输出

```
00000000
00000001
00000002
```

## 样例 #2

### 输入

```
7 4
```

### 输出

```
00000007
00000016
00000017
00000018
```

# 题解

## 作者：Kazdale (赞：2)

提供一种乱搞做法。

- ## 分析

	不难想到分治成两个部分使这两个部分和差为 $k$，然后看到 $0 \leq k \leq 10^{4}$ 发现如果从中间分成左右两个部分，每个部分各四个数，那么每个部分取任意范围内正数都是合法的（即另一部分都可以有值是两边的和或差的绝对值等于 $k$）。
    
    因为不能重复，所以我们需要想办法去重。对于不同数，可能构造出的数字串是相同的，所以我们如果只构造一个数的话就可以避免重复。那么我们先确定左半部分的大小 $x$，然后右半部分我们取 $y=|k-x|$，为什么？因为如果我认定是和 $x + y = k$，那么可能会出现 $y$ 为负数的情况，若为差，因为我们可以将被减数和减数之间互换使新答案为原答案的相反数，所以 $y$ 一定可以是非负的（因为 $x$ 已经取了一个正数的合法值，我们不需要担心无解，就可以取 $0$）。
    
    这样每次构造 $y$ 的时候 $x$ 都是不同的，所以这样构造不会出现重复。
    
    如何构造 $m$ 组数列？我们观察到 $1 \leq m \leq 3 \times 10^{5}$，于是大胆猜测，对于任意 $k$ 都能构造出 $3 \times 10 ^ {5}$ 个数列。
    
    设一个数 $a$ 在长度为 $4$ 的数列中的构造方案数为 $cnt_i$，这时我们的总方案数 $Z$ 显然等于 $\sum_{i=1}^{9999}cnt_{|k-i|}$，那么如果对于所有 $k$ 的取值的最小总方案数 $Z_{\min} = \min_{k=0}^{10000}\sum_{i=1}^{9999}cnt_{|k-i|} \geq 3 \times 10 ^{5}$，这个做法就是正确的。
    
    我们发现 $cnt$ 比较难算，因为会有由 $1 \sim 4$ 个数构成，计算符号不同，计算优先度不同（括号）的多种不同情况。
    
    那么我们先尝试写一个程序来计算只算一部分情况的最小总方案数 $Z_{\min}$，若此时 $Z_{\min} \geq 3 \times 10^{5}$，那么我们只需要计算这一部分情况即可。
    
    先使右半部分一定只有一个数，那么此时 $Z_{\min}=9999$。
    
    继续增加情况，使右半部分最多只有两个数，那么此时 $Z_{\min}=93940$。
    
    继续增加情况，使右半部分最多只有三个数且不存在括号，那么此时 $Z_{\min}=298162$。
    
    继续增加情况，使右半部分最多只有三个数且可能存在括号，那么此时 $Z_{\min}=374545 \geq 3 \times 10^{5}$，符合条件，所以我们只需要对于每个数，算出所以最多分成三个数且存在括号经过运算后能等于这个数且长度为 $4$ 的数列即可。
    
    此做法的时间复杂度为 $\mathcal{O(kw^{4}+m)(w = 10)}$，空间复杂度为 $\mathcal{O(Z_{\max})}$，经过计算，$Z_{\max} = 734992$，可以通过本题。
    
- ## 代码
	[这里是计算 $Z$ 的代码](https://www.luogu.com.cn/paste/tcgi0390)
    
    [这里是答案代码](https://www.luogu.com.cn/paste/smpog31e)

---

## 作者：AsunderSquall (赞：2)

[xyf](https://www.luogu.com.cn/user/68273) 吃饭的时候跟我说的这题，感觉挺妙的，过来氵篇题解。  

## 题意  
给出 $k,m$，让你输出 $m$ 个字符串，每个字符串由 $8$ 个数字构成，使得在这些字符串中添加 `+-*()` 可以构成一个合法的表达式，并且表达式的结果是 $k$。  
$0 \le k < 10^4 ,m \le 3\times 10^5$  

## 题解  
一个 naive 的想法是，比如说我们用前 4 个数字直接构成 $k$，后 4 个数字用来表示 0。  
如果后 4 个数字可以表示出 0，那么我们就直接 +0 上去就行了。  

且不说后 4 个数字能不能表示出 0，即使全部都行也只能输出 $10^4$ 个。  

但是这给我们一个启示，就是说能不能用后 4 个和前 4 个拼起来做成什么东西。  
比如说，如果后 4 个数表示出了 $y$，那么我们能不能让前 $4$ 个是 $k+y$ 或者 $k-y$ 或者 $y-k$ 之类（应该可以在最前面加个负号的）。  

那么我们枚举后 4 个能拼成什么东西，然后再和前面的去拼就行了。  

这样次数是对的，但是我不会证明/kk。大概全部枚举出来输出一下看看就能证明了。  

而且这样估计是比较宽的，因为我的代码可能没有枚举完，但是他也过了。  

给出我的垃圾实现代码  
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ri int
#define rd(x) x=read()
using namespace std;
const int N=18;
const int M=505;
const int maxn=5e6+5;
const int mod=998244353;
const int inf=3e18;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline int ksm(int x,int y=mod-2,int z=mod){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}

int k,m,tot;
int a,b,c,d,e;
set<int> S;
void out(int x){if (x<10) cout<<0;if (x<100) cout<<0;if (x<1000) cout<<0;cout<<x;}
void out(int x,int y){if (S.find(x*10000+y)!=S.end()) return;S.insert(x*10000+y);out(x);out(y);cout<<"\n";tot++;if (tot==m) exit(0);}
void put(int y)
{
    if (k+y<10000 && k+y>=0) {out(k+y,e);if (e!=k+y) out(e,k+y);}
    if (y-k<10000 && k-y<=0) {out(y-k,e);if (e!=y-k)out(e,y-k);}
    if (k-y<10000 && k-y>=0) {out(k-y,e);if (e!=k-y)out(e,k-y);}
}
void solve3(int A,int B,int C){put((A+B)+C);put((A+B)-C);put((A+B)*C);put((A-B)+C);put((A-B)-C);put((A-B)*C);put((A*B)+C);put((A*B)-C);put((A*B)*C);put(A+(B+C));put(A+(B-C));put(A+(B*C));put(A-(B+C));put(A-(B-C));put(A-(B*C));put(A*(B+C));put(A*(B-C));put(A*(B*C));}
int op(int A,int B,int C){if (C==1) return A+B;if (C==2) return A-B;if (C==3) return A*B;}
void solve4(int A,int B,int C,int D,int E,int F,int G){put(op(op(op(A,B,E),C,F),D,G));}
void solve(int x)
{
    S.clear();
    e=x;d=x%10;x/=10;c=x%10;x/=10;b=x%10;x/=10;a=x%10;x/=10;
    put(e);put((a*10+b)*(c*10+d));put((a*10+b)+(c*10+d));put((a*10+b)-(c*10+d));put((a*100+b*10+c)*(d));put((a*100+b*10+c)+(d));put((a*100+b*10+c)-(d));put((a)*(b*100+c*10+d));put((a)+(b*100+c*10+d));put((a)-(b*100+c*10+d));
    solve3(a*10+b,c,d);solve3(a,b*10+c,d);solve3(a,b,c*10+d);
    for (int i=1;i<=3;i++) for (int j=1;j<=3;j++) for (int k=1;k<=3;k++) 
    {
        solve4(a,b,c,d,i,j,k);solve4(b,c,a,d,i,j,k);solve4(b,c,d,a,i,j,k);solve4(b,c,a,d,i,j,k);
        put(op(op(a,b,i),op(c,d,j),k));
    }
}
signed main()
{
    rd(k);rd(m);
    for (int i=0;i<10000;i++) solve(i);    
}
```

---

## 作者：happybob (赞：1)

提供一个小丑做法。

看着就有一个做法是，选择一个区间放上 $k$，前后缀填一些使得结果都为 $0$ 或 $1$。

这样构造出来的数量明显不够。

聪明一点，枚举 $k=a+b$，把 $a,b$ 放入两个区间，分出来的三部分结果都要求为 $0$ 或 $1$。

这样可能还不够，在尝试 $k=ax+b$，或者 $k=ax+by$，$k=a-b$，$k=ax-b$ 之类的，多尝试一些组合就可以构造出 $3 \times 10^5$ 的。

代码太屎了，估计没人想看。

---

