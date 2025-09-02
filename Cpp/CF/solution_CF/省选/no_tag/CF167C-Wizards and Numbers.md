# Wizards and Numbers

## 题目描述

In some country live wizards. They love playing with numbers.

The blackboard has two numbers written on it — $ a $ and $ b $ . The order of the numbers is not important. Let's consider $ a<=b $ for the sake of definiteness. The players can cast one of the two spells in turns:

- Replace $ b $ with $ b-a^{k} $ . Number $ k $ can be chosen by the player, considering the limitations that $ k&gt;0 $ and $ b-a^{k}>=0 $ . Number $ k $ is chosen independently each time an active player casts a spell.
- Replace $ b $ with $ b mod a $ .

If $ a&gt;b $ , similar moves are possible.

If at least one of the numbers equals zero, a player can't make a move, because taking a remainder modulo zero is considered somewhat uncivilized, and it is far too boring to subtract a zero. The player who cannot make a move, loses.

To perform well in the magic totalizator, you need to learn to quickly determine which player wins, if both wizards play optimally: the one that moves first or the one that moves second.

## 说明/提示

In the first sample, the first player should go to (11,10). Then, after a single move of the second player to (1,10), he will take 10 modulo 1 and win.

In the second sample the first player has two moves to (1,10) and (21,10). After both moves the second player can win.

In the third sample, the first player has no moves.

In the fourth sample, the first player wins in one move, taking 30 modulo 10.

## 样例 #1

### 输入

```
4
10 21
31 10
0 1
10 30
```

### 输出

```
First
Second
Second
First
```

# 题解

## 作者：MyukiyoMekya (赞：5)

设 $f(a,b)$ 为 $1$ 时先手必胜，为 $0$ 时先手必败。假设 $a<b$。

1. $a=0,f(a,b)=0$
2. $a=1,f(a,b)=1$

然后根据 $b\leftarrow b \bmod a$ 这个操作，很自然的想到如果 $f(a,b \bmod a)=0$ ，那么 $f(a,b)=1$

否则的话就要考虑 $b \leftarrow b-a^k$ 这个操作了，

考虑到 $b \bmod a$ 其实上是 $b-ga$ ，这个 $g=\lfloor \dfrac{b}{a} \rfloor$，然后把上面那个操作一改 $b-a(a^{k-1})$，对比一下：

$b\leftarrow b-(a^{k-1})a$，$b\leftarrow b-ga$，发现不管怎么执行 $b\leftarrow b-a^k$ ，最后一定会经过 $(a,b-ga)$

因为 $f(a,b \bmod a)=1$ ，所以取到这个的就必败了。

梳理一下，现在问题变成了有 $g$ 个石子，现在每个人一轮可以取 $1,a,a^2,\cdots$ 个石子，取到最后一个石子的人输，问是否先手必胜。

感觉很像巴什博弈，我们可以通过构造来达到巴什博弈的效果：$h(g)=g \bmod (a+1)$

发现 $h(a^0)=1,h(a^1)=a,h(a^2)=1,h(a^3)=a,\cdots$

所以实际上在 $\bmod (a+1)$ 意义下就归结为 $-1$ 和 $-a$ 两种操作，然后由于 $(a+1) \bmod (a+1)=0$ ，所以必胜一方可以模仿操作。

然后到了只剩 $a$ 个的时候没人会傻到直接啪的一下取 $a$ 个然后白给 lose，所以肯定是一个一个取，

所以就是 $(g \bmod (a+1))\bmod 2=0$ 的时候 $f(a,b)=1$，否则 $f(a,b)=0$l

时间复杂度 $\mathcal O(T\log \max(a,b))$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
inline int f(int x,int y) // 0 lose   1 win
{
	if(x>y)std::swap(x,y);
	if(!x)return 0;
	if(x==1)return 1;
	if(!f(x,y%x))return 1;
	return (((y/x)%(x+1))&1)^1;
}
inline void work()
{
	int x,y;read(x,y);
	std::puts(f(x,y)?"First":"Second");
}
signed main(void)
{
	int t;read(t);
	while(t--)
		work();
	return 0;
}
```



---

## 作者：hgckythgcfhk (赞：2)

由于本题题面的翻译没有 LaTeX，且标点符号混乱，让人有一种明明题不长却不想看的感觉，这里给出形式化题意：

给定两个正整数 $a$，$b$，我们假设当前 $a>b$ 你可以进行以下两种操作：

1. $a\gets a \bmod b$

2. 任选一个正整数 $k$ 使得 $a-b^k$ 非负，$a\gets a-b^k$

求判断先手是否必胜。

对于博弈题，我们会先想真正把博弈图的反图出来跑拓扑排序，然后将等价的边合并，用套上基本的博弈模板，用 SG 函数，找性质等方法，但是这题反图似乎并不是很好建，直接正着 dp。

显然，根据题意，我们可以写出这样一个函数。


```cpp
inline bool aa(const ll a,const ll b){if(!a||!b)return 0;if(!aa(b,a%b))return 1;
for(register ll c=b;c<=a;c*=b)if(a>=a-c&&!aa(a,a-c)||a<a-c&&!aa(a-c,a))return 1;return 0;}
```

且不考虑边数搜索树每个点的度数，深度就是 $O(\frac{a}{b})$ 的，时间复杂度显然不对。

发现是操作 $2$ 费时间，考虑优化操作 $2$，我们发现，每次取 $b^1,b^2 \dots$，这个过程就是巴什博弈，顺便指出第一篇题解的一个错误，$k$ 是正整数 $b^0$ 不合法，所以当且仅当 $b=1$ 时才会出现 $1$，但是这被操作 $1$ 判掉了，所以一定不可能有 $1$。

由于操作与取模和幂有关，自然的想到找循环节，现给出结论：

```cpp
inline unsigned aa(cit ll a,cit ll b){if(!a||!b)return 0;if(!aa(b,a%b))return 1;cit ll c=(a/b-1)%(b+1);return (c&1)||c==b;}
```

证明：根据巴什博弈是在模 $b+1$ 意义下的操作，先考虑对 $b+1$ 取模很自然，发现：

对于任意的正整数 $x$ 有：

$$x^2\equiv 1 \pmod{x+1} $$

这个正确性显然，因为：

$$x^2-1 \equiv (x+1)(x-1) \equiv 0 \pmod{x+1}$$

所以任意 $b$ 的正偶数次方都等价于 $1$，那么要么选 $b$ 个要么选 $1$ 个，也就是说，在模 $b+1$ 意义下，先手选 $1$ 后手就可以通过选 $b$ 来回到原来的局面，故算法正确性显然。

证明公式正确性，$c$ 表示先全一次选 $1$ 一次选 $b$ 消耗完后剩下的数，后面只能选 $1$，这等价于只有 $0$ 和 $1$ 两种情况，显然 $0$ 先手必败而 $1$ 先手必胜，当然，剩下 $b$ 也显然先手必胜。

最后证明这个 $c$ 是剩下的数，由于可能存在一些方案取不到，比如 $a\le b^2$，这里的处理方法是让 $a$ 除以 $b$，这样相当于选 $b^1$ 和 $b^0$ 一定能取到，如果不能取 $b$ 其实无所谓，这一步不会有贡献，关于减 $1$，由于我不太喜欢处理边界，我选择反正只有加 $1$ 减 $1$ 和什么也不做这 $3$ 种情况，全试一遍，看哪种可以用哪种，一般情况下这种边界并不多，全试一遍大概率比硬推快，就不要为难自己了，有时候 OI 不需要死扣一个严谨的证明，能说服自己就够了，哪怕是看题解，有几行没看懂且没解释的程序我觉得最好的理解方法就是试着说服自己，如果说服不了自己，比如对于本题解如果你对所谓的“先手必胜”的“先手”和最开始的“先手”不理解，那是水平没达到，最好的方法是跳过这个题，等水平达到之后和这个题有缘再见，比如本题，你如果分不清先手必胜的先手和真正的先手，那请先学以下博弈论，找篇题解死扣这个题没有意义，我认为我已经把其他打表题解没说的东西说的很口语化了，博弈论的基础知识请自己自行找资料学习。

```
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),freopen("1.in","r",stdin),freopen("1.out","w",stdout)
using namespace std;constexpr unsigned N=1e3+1,p=1e9+7;
#define int register unsigned
#define ll long long
inline unsigned aa(cit ll a,cit ll b){if(!a||!b)return 0;if(!aa(b,a%b))return 1;cit ll c=(a/b-1)%(b+1);return (c&1)||c==b;}
signed main(){open;int t;cin>>t;while(t--){int ll a,b;cin>>a>>b;cout<<((a>b?aa(a,b):aa(b,a))?"first":"second")<<'\n';}}

```


---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF167C)看题目。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;题目大意：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;略
# 分析  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;找规律的神题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~其实就是写不来证明。~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先，如果在游戏的过程中出现了$a>b$的情况，麻烦手动调换成$a<b$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$f(a,b)$表示当玩家手中的状态为$(a,b)$时是否有必胜策略，输出值为布尔。$T$代表有，$F$代表没有。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下面根据题意分析。
### Part1
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(0,k)=F$（$k\not=0$）  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~凉都凉了还想翻身？~~  
### Part2
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;若$f(b\%a,a)=F$，则$f(a,b)=T$（$a,b\not=0$）  
### Part3
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本题主要的~~找规律~~过程要开始了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$k=\lfloor\frac{b}{a}\rfloor$；  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;当$a=1$时，此时可以发现，当$k$为奇数时，$f(a,b)=F$，反之$f(a,b)=T$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;当$a=2$时，此时可以发现，$f$的值存在一个长度为$3$的最小循环节。设$k'=k\mod 3$，若$k'$为奇数，则$f(a,b)=F$，反之$f(a,b)=T$；  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;当$a=3$时，可以发现类似于$a=1$的规律。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;当$a=4$时，$f$的值存在一个长度为$5$的最小循环节。设$k''=k\mod 5$，若$k''$为奇数，则$f(a,b)=F$，反之$f(a,b)=T$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;......   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;总结一下：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$g(x)$表示当$a=x$时$f(a,b)$的值的最小循环节长度。则可以知道：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$g(x)=\begin{cases}2&x\equiv1\mod 2\\a+1&x\equiv0\mod 2\end{cases}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$k'=k\mod g(x)$。在循环节中，存在如下规律：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(x,b)=\begin{cases}T&x\equiv0\mod2\\F&x\equiv1\mod2\end{cases}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;证明需要分类讨论加数学归纳法。~~我又懒又笨，不写了。~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;用这个规律来快速判断胜负情况即可。时间$O(\log_2(\max\{a,b\}))$  
# 代码
```cpp
#include <cstdio>
#include <cstdlib>

typedef long long LL;

const int MAXA = 5005, MAXB = 5005;

template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s < '0' || '9' < s ){ if( s == '-' ) f = -1; s = getchar(); }
    while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ){ putchar( '-' ), x = -x; }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

LL A, B;

bool check( LL a, LL b )
{
	if( a > b ) a ^= b, b ^= a, a ^= b;
	if( ! a ) return false;
	LL times = b / a;
	bool last = check( b % a, a );
	if( ! last ) return true;
	if( a & 1 )
	{
		if( last ) return  ! ( times & 1 );
		else return times & 1;
	}
	else
	{
		times %= ( a + 1 );
		if( last ) return ! ( times & 1 );
		else return times & 1;
	}
}

int main()
{
//	freopen( "game.in", "r", stdin );
//	freopen( "game.out", "w", stdout );
	int T;
	read( T );
	while( T -- )
	{
		read( A ), read( B );
		if( check( A, B ) ) puts( "First" );
		else puts( "Second" );
	}
	return 0;
}
```

---

## 作者：Rainybunny (赞：0)

( 本文也作7.26考试题解, 附[题目链接](https://www.luogu.org/problem/CF167C) ).  
这是一道博弈题, 而其精髓呢, 在于找规律. 设现有数字$(a,b),a<b$, 我们有两种操作:  
- 将$b$对$a$取模, 即$b$变为$b\,mod\,a$;  

- 从$b$中减去$a$的幂, 不能减成负数, 即$b$变为$b-a^k$ ( $b-a^k\ge0,k\in N_+$ ).  

我们用函数$Solve(a,b)$来表示该状态下的胜负, $Solve(a,b)=true$为先手胜, 否则为后手胜. 第一种操作是能够单次递归实现的, 即:  
$$
Solve(b\%a,a)=false\Rightarrow Solve(a,b)=true
$$
若满足此情况, 直接返回$true$.  
否则, 有$Solve(b\%a,a)=true$, $(b\%a,a)$成为了先手必胜态, 借此, 我们来讨论操作二的得失. 设$b=ka+b\%a$, 我们手玩一波:  

| 是否为必胜态 | $a=1$ | $a=2$ | $a=3$ | $a=4$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $k=0$ | $T$ | $T$ | $T$ | $T$ |
| $k=1$ | $F$ | $F$ | $F$ | $F$ |
| $k=2$ | $T$ | $T$ | $T$ | $T$ |
| $k=3$ | $F$ | $T$ | $F$ | $F$ |
| $k=4$ | $T$ | $F$ | $T$ | $T$ |
| $k=5$ | $F$ | $T$ | $F$ | $T$ |
是否发现, $a=x$时, 有长度为$x+1$的状态循环节?~~不要砸电脑/滑稽~~.  
那么在循环节中, 第偶数个状态为必胜态, 否则为必败态. 即:
$$
2|k\%(a+1)\Rightarrow Solve(a,b)=true
$$
该结论可以数学归纳证明 ( 某机房$dalao$: 有规律就盘, 证它干吗 ).  
该下结论啦:
$$
Solve(a,b)=!Solve(b\%a,a)\,or\,2|k\%(a+1)
$$
上代码:
```cpp
#include <cstdio>

#define Int register int

typedef long long int LL;

inline bool Solve ( const LL a, const LL b ) {
	if ( ! a || ! b ) return false;
	if ( ! Solve ( b % a, a ) ) return true;
	LL k = ( b / a - 1 ) % ( a + 1 );
	return k & 1 || k == a;
}

inline void Work () {
	int T;
	LL a, b;
	scanf ( "%d", &T );
	while ( T -- ) {
		scanf ( "%lld %lld", &a, &b );
		if ( a > b ) a ^= b, b ^= a, a ^= b;
		puts ( Solve ( a, b ) ? "First" : "Second" );
	}
}

int main () {
//	freopen ( "game.in", "r", stdin );
//	freopen ( "game.out", "w", stdout );
	Work ();
	return 0;
}
```

---

