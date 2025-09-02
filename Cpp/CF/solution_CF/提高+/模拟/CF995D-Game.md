# Game

## 题目描述

## 题意

定义一从 $n$ 位 $\texttt{01}$ 串映射到实数的函数 $f$，即 $f:\{0, 1\}^n \to \mathbb{R}$

现有一个 $n$ 位的 $\texttt{01}$ 串，但它其中的元素都还未确定。不妨设 $x_i$ 表示该串第 $i$ 位的值（编号从 $1$ 开始），未确定的值就设为 $-1$

又有 $\texttt{A}, \texttt{B}$ 两位玩家，他们将共执行 $n$ 次操作确定这个 $\texttt{01}$ 串；对于每次操作，将会等概率地选择 $\texttt{A}, \texttt{B}$ 其中一人，被选中的人则会选择 $x_i$ 满足 $x_i=-1$，并将其设为 $0$ 或 $1$

其中 $\texttt{A}$ 想要最大化最终确定的串带入 $f$ 的值，$\texttt{B}$ 则想要最小化最终确定的串带入 $f$ 的值

现给出 $n$，以及对每种 $\texttt{01}$ 串带入 $f$ 得到的值；问最终确定的串的期望的带入 $f$ 得到的值

共有 $r+1$ 组询问；但对于 $r>1$ 组的询问，仅会修改一种 $\texttt{01}$ 串带入 $f$ 得到的值，其余和上一组询问完全相同

## 样例 #1

### 输入

```
2 2
0 1 2 3
2 5
0 4
```

### 输出

```
1.500000
2.250000
3.250000
```

## 样例 #2

### 输入

```
1 0
2 3
```

### 输出

```
2.500000
```

## 样例 #3

### 输入

```
2 0
1 1 1 1
```

### 输出

```
1.000000
```

# 题解

## 作者：Piwry (赞：3)

upd:

感觉之前写的解释太假，于是就改了下 \kk

改完后可能写得有点太简洁X

主要思路其实就是考虑从终局状态逆推；而社论中的归纳总感觉有些奇怪（即我之前写的），于是就没采用那个思路 \fad

&nbsp;

（以下是原内容（前言）：）

做虚拟赛时前面几题没啥思路，就来看最后一题（div.2）

看懂题意时没什么想法，然而瞄了一眼数据发现答案都是数列的平均值；于是就试着写了一份交上去，居然过了，也没 fst \fad

结论的推导还是有一定难度的；然而这个结论实在过于优美，加上样例给得也挺足，感觉作为题目被瞎蒙出来的概率挺大...

## 解析

我们需要证明答案期望为 $\frac {\sum\limits_{x=0}^{2^n}f(x)} {2^n}$（也就是 $\{c_n\}$ 的平均值）

考虑从终局状态开始归纳：

### Part1

如果仅有一个位置未被确定，不妨设为 $i$，**此时**的答案显然为当前串 $x$（仅有 $i$ 位未确定）$i$ 位为 $0$ 与 $i$ 位为 $1$ 的平均值

（两位玩家的机会是等概率的，且一定是一个人想使该位为 $0$，一个人想使该位为 $1$）

### Part2

如果结论在 $k$ 时成立，我们考虑证明结论在 $k+1$ 时仍成立（有 $k+1$ 个位置未被确定）

设想使值最大的玩家为 $\texttt{A}$，想使值最小的玩家为 $\texttt{B}$；我们先假设该轮由 $\texttt{A}$ 决策，并考虑他的决策

此时应有 $2^{k+1}$ 个可能的最终的 $\texttt{01}$ 串状态；如果我们将第 $i$ 位的值确定，就相当于与将 $2^{k+1}$ 个状态划成两半，从中选择一半成为接下来的可能状态

首先此时 $\texttt{A}$ 应当会使接下来状态的**期望**值尽量大（原因可能有点玄学；算是约定成俗？）。由于我们已经证明结论在 $k$ 时成立，因此 $\texttt{A}$ 应当会选择所有划分中（所有可选择的位置 $i$ 中）的两个集合中平均值最大的那个集合，并相应地确定某个位置的值。不妨设 $\texttt{A}$ 将第 $i$ 位确定为了 $t$

接着我们考虑该轮由 $\texttt{B}$ 决策时 $\texttt{B}$ 会做出的决策。显然 $\texttt{B}$ 和 $\texttt{A}$ 恰好相反；他是要找到平均值最小的那个集合，并做出相应的操作。考虑我们**划分的过程**，不难发现这其实就是将第 $i$ 位确定为 $1-t$

而 $k+1$ 轮的答案就是 $\texttt{A}$ 操作得到的期望与 $\texttt{B}$ 操作得到的期望的平均（玩家的机会是等概率的）；由于 $\texttt{A}, \texttt{B}$ 选择的都是同一个位置，即划分出的两个状态集合没有交，因此 $k+1$ 轮的答案仍是这 $2^{k+1}$ 个状态的平均值（即结论仍成立）

## CODE

感觉其实没什么必要放 \kk

---

## 作者：XL4453 (赞：2)

### 题目分析：

首先观察数据，发现答案正好就是所有的值的平均数，然后一交就 AC 了。

考虑为什么会这样，可以发现，假如有一个点要求值更大的那一个玩家要选择放 $1$，那么一定有要求值最小的玩家放 $0$，反之亦然。由此可以得到每一个位置放 $0$ 还是放 $1$ 的概率是一样的，所以取到每一个值的概率也是一样的。

根据期望公式，可以直接得到最终期望就是所有可能结果的平均值。

------------
实现上，记录下当前的结果总和，对于每一个询问，消除原来数的影响，加上现在的数，修改数组，得到结果。



------------
### 代码：
```cpp
#include<cstdio>
using namespace std;
long long t,n,ans,c[262160],x,y;
int main(){
	scanf("%d%d",&n,&t);
	for(int i=0;i<1<<n;i++)
	scanf("%d",&c[i]),ans+=c[i];
	printf("%.6lf\n",(double)ans/(double)(1<<n));
	for(int i=1;i<=t;i++){
		scanf("%d%d",&x,&y);
		ans=ans-c[x]+y;
		c[x]=y;
		printf("%.6lf\n",(double)ans/(double)(1<<n));
	}
	return 0;
}
```


---

## 作者：Karry5307 (赞：2)

### 题意

略。

$\texttt{Data Range:}1\leq n\leq 18$

### 题解

很显然答案为所有 $c_i$ 的平均值。

考虑两个人某一轮的决策。对于每一个二进制位 $i$ 来说，将所有可能的状态划分为两个集合：所有满足这一位上为 $1$ 的数 $x$ 的 $c_x$ 划分进 $S_i$ 中，否则划分进 $T_i$ 中。

接下来我们说一个集合最大或最小指的是所有元素之和最大或最小。

如果 A 先决策，那么他会去选择满足没有被选过，并且 $S_i$ 或者 $T_i$ 最大的那个二进制位 $i$ 上。如果 B 先决策则会去选择那个没有被选过同时 $S_i$ 或者 $T_i$ 最小的那个二进制位 $i$ 上。

注意一个条件，由于 $S_i\cap T_i$ 为空且 $S_i\cup T_i$ 为全集，所以如果 $S_i$ 为最大的集合那么 $T_i$ 必然为最小的集合，反之亦然。于是很明显，如果 A 先决策选了位置 $i$，那么 B 先决策也一定会选择位置 $i$，而且两人所填的值是不一样的。

同时，这一回合的操作方是等概率选取的，所以被选中的二进制位的填上 $0$ 或 $1$ 是等概率的。

倒退回第一轮能发现，每个位置填 $0$ 或 $1$ 的概率均等，也就是说最终的 $x$ 取遍每个可能值的概率都是均等的，期望很明显为平均值。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=262151;
ll n,kk,pos,v;
li sum;
ll x[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read(),kk=read();
	for(register int i=0;i<(1<<n);i++)
	{
		sum+=(x[i]=read());
	}
	printf("%.6lf\n",1.0*sum/(1<<n));
	for(register int i=1;i<=kk;i++)
	{
		pos=read(),v=read(),sum+=v-x[pos],x[pos]=v;
		printf("%.6lf\n",1.0*sum/(1<<n));
	}
}
```

---

## 作者：bsdsdb (赞：0)

有一个映射 $f:\{0,1\}^{n\le18}\rightarrow\mathbb R$ 和初始全为 $-1$ 的 $X=(x_1,\ldots,x_n)$。有一半的可能性 A 来决定 $i$（$x_i=-1$）与 $x_i$ 的值，B 同理，直到所有值都被决定为止。A 想要 $f(X)$ 尽可能大，B 反之。$f$ 的值有 $r\le2^n$ 轮单点修改，要求对初始情况和每轮修改之后求 $f(X)$ 的期望值。

提示：多搞几组样例，结论不难猜。

设目前可能达到的所有数为 $S$，让 A 行动会达到状态 $C$，让 B 行动会达到状态 $D$，整体期望值为 $e_S=\dfrac{e_C+e_D}2$，可能达到的所有数的平均值为 $a_S$，下证 $e_S=a_S$。

如果所有数都已经填好，那么结论显然成立：$e_S=a_S=f(S)$。否则，因为后面的行动方完全随机，A 应该找到 $e_C=a_C$ 最大的 $C$ 进行移动，B 同理。当 $a_C>a_D$ 时，有 $D=\complement_S^C$，故 $C\cup D=\varnothing,C\cap D=S,e_S=\dfrac{e_C+e_D}2=\dfrac{a_C+a_D}2=a_S$。否则，所有下一步状态的期望值相等，$e_S=\dfrac{e_C+e_D}2=\dfrac{e_C+e_{\complement_S^C}}2=a_S$，证毕。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
ldb sum;
ll n, r, sc[1 << 19];
 
int main() {
    read(n), read(r);
    for (ll i = 1; i <= (1 << n); ++i) {
        read(sc[i]);
        sum += sc[i];
    }
    cout << fixed << setprecision(12) << sum / (1 << n) << endl;
    while (r--) {
        ll a, b;
        read(a), read(b);
        ++a;
        sum -= sc[a] - b;
        sc[a] = b;
        cout << fixed << setprecision(12) << sum / (1 << n) << endl;
    }
	return 0;
}
 
;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;
 
   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

