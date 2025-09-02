# [AGC011D] Half Reflector

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc011/tasks/agc011_d

高橋君は，ある特殊な装置をたくさん持っています． この装置は筒状で，左右からボールを入れることができます． また，この装置には $ 2 $ 種類の状態 A, B があります． 各状態について，装置にボールを入れたときの動作は次のようになっています．

- 状態 A の装置にボールを入れると，入れた側と同じ側からボールが飛び出してきて，その後すぐに装置の状態は B に変化します．
- 状態 B の装置にボールを入れると，入れた側と反対側からボールが飛び出してきて，その後すぐに装置の状態は A に変化します．

装置の状態の変化はとても速いので，$ 1 $ つの装置にボールを入れた後，次にボールが入ってくるまでの間には必ず状態の変化は終わっています．

高橋君は，この装置を $ N $ 個つなげたものを作りました．つまり，

- 左から $ i $ ($ 1\ \leq\ i\ \leq\ N-1 $) 番目の装置の右端から飛び出したボールは，すぐに左から $ i+1 $ 番目の装置に左端から入ります．
- 左から $ i $ ($ 2\ \leq\ i\ \leq\ N $) 番目の装置の左端から飛び出したボールは，すぐに左から $ i-1 $ 番目の装置に右端から入ります．

左から $ i $ 番目の装置の最初の状態は，文字列 $ S $ の $ i $ 番目の文字で表されます． 次に高橋君は，一番左の装置の左端からボールを入れ，ボールがどちらかの端から出てくるまで待つということを $ K $ 回行いました． ここで，ボールがいつまで経っても出てこないということは起きないことが証明できます． $ K $ 回ボールを入れた後の各装置の状態を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200,000 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ |S|=N $
- $ S $ の各文字は `A` または `B` である

### Sample Explanation 1

この入力では，一番左の装置の左端からボールを入れると，同じところからボールが出てきます．

## 样例 #1

### 输入

```
5 1
ABAAA```

### 输出

```
BBAAA```

## 样例 #2

### 输入

```
5 2
ABAAA```

### 输出

```
ABBBA```

## 样例 #3

### 输入

```
4 123456789
AABB```

### 输出

```
BABA```

# 题解

## 作者：myee (赞：6)

### 前言

嗯，感觉这种题，不手玩没得做啊！

### 思路

用 `R` 表示向右的球，`L` 表示向左的球。模拟一下样例一、二。

`RABAAA` `LBBAAA`

`RBBAAA` `ARBAAA` `AARAAA` `AALBAA` `ABRBAA` `ABARAA` `ABALBA` `ABBRBA` `ABBARA` `ABBALB` `ABBBRB` `ABBBAR`

规律逐渐浮现了：

如果开头为 `A`，则直接弹回并把开头改为 `B`。

如果开头为 `B`，会将所有下一项为 `A` 的元素变为 `B`，将下一项为 `B` 的元素变为 `A`，最后一项变为 `A`。

因此开头为 `B` 时就是全局轮转并翻转！

当 $k$ 很小时，我们可以暴力 $O(n+k)$ 模拟。

我们把这个算法先用伪代码描述一下（`A` 为 $0$，`B` 为 $1$，从 $0$ 标号）：[伪代码](https://www.luogu.com.cn/paste/txf4xgu9)。（由于博客渲染有问题，请在此查看）

于是，到了 $p$ 从 $n-1$ 变为 $0$ 的那一步之后，整个序列（按初始时标号）的形态是确定的：$2|n$ 时为 `BABABA...BA`，$2\nmid n$ 时为 `BABABA...AB`。

之后的过程，容易发现 $a$ 的形态有循环节；在 $2|n$ 时为 $n$，在 $2\nmid n$ 时为 $4n$。

~~其实答案有一个更短的循环节。~~

直接取模，然后继续模拟即可。

总复杂度 $O(n)$。

### Code

给出 C++ 和 Python 实现。

```cpp
chr C[200005];
bol A[200005];
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    // freopen("QAQ.out","w",stdout);
#endif
    uint n,k,p=0,op=0;scanf("%u%u%s",&n,&k,C);
    for(uint i=0;i<n;i++)A[i]=C[i]=='B';
    for(;p<n&&k;k--)if(A[p]==op)A[p]=!A[p];else op=!op,p++;
    if(k)for(k%=4*n,p=0;k;k--){
        if(A[p]==op)A[p]=!A[p];else op=!op,p=(p+1)%n;
    }
    for(uint i=0;i<n;i++)putchar("BA"[A[(i+p)%n]==op]);
    return 0;
}
```

```python
n,k=map(int,input().split())
p,op=0,False
s=input()
a=[]
for i in range(n):
    a.append(s[i]=='B')
while k and p<n:
    if a[p]==op:
        a[p]=not a[p]
    else:
        op=not op
        p=p+1
    k-=1
k%=n*4
p%=n
while k:
    if a[p]==op:
        a[p]=not a[p]
    else:
        op=not op
        p=(p+1)%n
    k-=1
for i in range(p-n,p):
    print('BA'[a[i]==op],end='')
print('')
```



---

## 作者：Kewth (赞：6)

这。。。O(k) 能过？我本来只是想验证个猜想来着，一不小心就 AC 了。。。

不难归纳出串 S 经过一次碰撞后有两种情况：

1. S 的开头就是 A ，球直接弹飞，S 的开头变为 B
2. S 的开头不是 A ，球一定可以经过所有点，此后 S 取反后循环左移一位即为新的 S

关于第 2 点的证明：  
首先球如果刚跨过第 i 个点时第 i 个点一定是 A ，  
因为能跨过它说明之前该点为 B ，那么跨过后就变成了 A 。  
那么分两种情况（箭头表示当前球的位置和方向）：  

- A -> B ，直接变为 A A ->
- A -> A ，来回碰撞后变为 B A ->

不难发现每次第 i 个点就变成了第 i + 1 个点的相反。  
对于边界，由于碰撞之前开头一定是 B ，碰撞之后结尾一定是 A ，所以也是成立的。

那么把 S 看作一个环，记一个反转标记和起点位置即可 O(k) 模拟，常数极小，可以 AC 。  
（官方给出的做法是 deque ，这个常数会大得多，O(k) 基本没戏）

正解的话也很简单，事实上 S 的转移是 pho 形的，且链的长度是 2n 的因子，环的长度是 2 的因子．  
令 k = 2n + (k - 2n) % 2 即可（仅适用于 k > 2n ）．  
具体证明不会．

参考实现：

```cpp
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
char s[maxn];

int main() {
	int n = read, k = read;
	scanf("%s", s + 1);

	if(k > (n << 1)) {
		k -= n << 1;
		k &= 1;
		k += n << 1;
	}

	int p = 1, A = 'A';
	while(k --) {
		if(s[p] == A)
			s[p] = 'A' + 'B' - s[p];
		else {
			A = 'A' + 'B' - A;
			++ p;
			if(p > n) p = 1;
		}
	}

	for(int i = p; i <= n; i ++)
		printf("%c", "BA"[s[i] == A]);
	for(int i = 1; i < p; i ++)
		printf("%c", "BA"[s[i] == A]);
	puts("");
}
```

---

## 作者：zhylj (赞：4)

对于每次操作：（``o`` 代表球）

- 若 $s_1 =$ ``A``: 令开头变为 ``B``。
- 若 $s_1 =$ ``B``: 则必然可以遍历整个数列，对于第 $i$ 个元素，假设能遍历到它，则它前面一定是 ``A``（取反完的 ``B``）
  - 若 $s_i =$ ``A``，则会反弹到前一个，然后回来（$i$ 被取反了两次），此时 $s_{i-1}, s_{i}$ 变为 ``B Ao...``。
  - 若 $s_i =$ ``B``，则继续滚过，此时 $s_i$ 取反变为 ``A``。此时 $s_{i-1}, s_{i}$ 变为 ``A Ao...``。
  
  这种情况下，一个初步的结论是：一个球撞击时，取反所有 ``B``，将原来的 ``A`` 的前面变为 ``B``，但是这样是不便于模拟的。

  可以很容易证明，在以上的操作中，每次的 $s_i$ 都是 $s_{i+1}$ 取反，甚至 $s_n$ 是 $s_1$ 取反，也就是取反后循环移位，在这基础上即可在 $\mathcal O(k)$ 时间内模拟。

可以发现所有形如 ``...BABA`` 的**后缀**都不会被破坏。（取反完变成 ``...ABAB``，且 $s_1$ 是 ``A``）而且每次循环移位都会造成一对新的 ``BA`` 出现。（可以在纸上模拟一下更容易理解）

最后的状态一定会变成 ``BABAB...``（$n$ 为偶数）或 ``xBABA...``（$n$ 为奇数，此时只有第一个在交替变化）。

容易发现每两次扔球至少会有一次可以遍历整个数列，而只要出现 $\mathcal O(n)$ 次循环移位即可把整个数列变为 ``(x)BABA...``，所以我们只需要模拟 $\mathcal O(n)$ 次（比如 $2n$ 次），如果 $n$ 是奇数，再把剩下的 $k$ 对 $2$ 取个模即可。

---

## 作者：qczrz6v4nhp6u (赞：2)

PrinceX 大神推的题，~~数学课做出来了~~，感觉很好玩。

### Solution

- 为方便叙述，约定 $\texttt{A}=\rm false=0$，$\texttt{B}=\rm true=1$。

考虑手玩一下 $s=\texttt{AAAAA}$ 时是如何变化的：

| 步数 | $s=$ |
| :---: | :---: |
|$0$|$\texttt{AAAAA}$|
|$1$|$\texttt{BAAAA}$|
|$2$|$\texttt{BBBBA}$|
|$3$|$\texttt{AAABA}$|
|$4$|$\texttt{BAABA}$|
|$5$|$\texttt{BBABA}$|
|$6$|$\texttt{ABABA}$|
|$7$|$\texttt{BBABA}$|

在第 $7$ 步出现了循环。

如果你的注意力足够集中，你就可以发现状态是按照如下规律变化的：

- 若 $s_1=\texttt A$，则操作相当于 $s_1\gets \texttt B$；
- 否则，操作相当于 $s_n\gets\texttt{A}$，且对于 $s$ 的每个极长的相同连续段，反转除该段最后一个字符以外的字符，如 $\texttt{BBB|AAAAA|BB}\to \texttt{AAB|BBBBA|AA}$。

上面的 ad-hoc 部分建议自行手玩感受一下。

---

现在我们考虑如何维护。

通过上面的转化，我们可以观察到更多性质：

- 如果 $s$ 存在一段后缀是以 $\texttt A$ 结尾的 $\texttt{AB}$ 相间的形式（下文称之为不动串），则这段后缀在后面的操作中不会改变。
- 如果 $s_1=\texttt B$ 且 $s_n=\texttt A$，则操作相当于找到最小的 $p$ 满足 $[p,n]$ 是不动串，并令 $\forall 1\le i< p,s'_i\gets \neg s_{i+1}$，以及 $s_{p}\gets (n-p)\bmod 2$。
- 如果 $k$ 足够大，则最终的情况分为两种：
  - 若 $2|n$，最终的 $s$ 会变为 $\texttt{BABA}\cdots\texttt{BA}$ 的形式；
  - 否则最终 $s$ 会在 $\texttt{BBABA}\cdots\texttt{BA}$ 与 $\texttt{ABABA}\cdots\texttt{BA}$ 间转移。

现在我们有相当强的性质来刻画这些条件，唯一的问题就是有的时候 $s_1=\texttt A$，导致我们无法一次做完。

注意到 $s'_1=\texttt{A}$ 当且仅当 $s_1=s_2=\texttt B$，结合上述“移位”的性质，判掉即可。

于是我们在 $O(n)$ 时间内解决了这题。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=2e5+5;
int n,k;char s[N];
void trans(){
	if(s[1]=='A')s[1]='B';
	else{
		for(int i=1;i<n;i++)
			if(s[i]==s[i+1])
				s[i]='A'+'B'-s[i];
		s[n]='A';
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>s[i];
	while(k&&(s[n]=='B'||s[1]=='A'))trans(),k--;
	if(!k){
		for(int i=1;i<=n;i++)cout<<s[i];
		return 0;
	}
	int shift=n+1;bool flag=s[1]=='A';
	for(int i=1;k&&i<n;i++){
		if(k&&flag)k--,flag=0;
		if(k){
			k--,shift=max(shift-1,1);
			flag=s[i+1]=='A'+(i&1);
		}
	}
	flag^=(k&1)&&(n&1);
	s[1]='B'-flag;
	for(int i=2;i<shift;i++)s[i]=(n-shift)&1?s[i+n-shift+1]:'A'+'B'-s[i+n-shift+1];
	for(int i=shift;i<=n;i++)s[i]='A'+((n-i)&1);
	for(int i=1;i<=n;i++)cout<<s[i];
	cout<<'\n';
	return 0;
}
```

---

PrinceX 好像有个简单做法，大家快去膜拜他！

哦直接 `deque` 维护就可以。我是唐诗。

---

## 作者：山田リョウ (赞：0)

# AGC011 D. Half Reflector

首先如果第一位是 `A` 则肯定是将其修改为 `B` 然后结束，否则手玩下可以发现遇到第一个 `A` 后会回头撞到前一位（现在已经变为 `A` 了） 然后将其重新变为 `B` 后继续向前留下一个 `A`。

**观察下发现，第二种情况其实是全局翻转再轮换一位。**

那可以先跑一轮使得恰好轮换了 $n$ 次，接下来如果 $n$ 是偶数则每次拿到的第一位都一定为 `B`，否则一定为 `A`，因此前者循环节为 $n$，后者循环节为 $4n$，模拟即可。

[submission](https://atcoder.jp/contests/agc011/submissions/61982778)

---

## 作者：zifanwang (赞：0)

用 $1$ 表示 `A`，$0$ 表示 `B`，观察进行一次操作后字符串会发生什么变化。首先当第一个数为 $1$ 时，只会将第一个数变为 $0$。对于剩下的情况，手玩一下可以发现会将第一个数移到末尾，然后将所有数异或 $1$。

先考虑暴力怎么做，可以记一个指针 $i$ 和当前应该给全体数异或的值 $c$。如果 $a_i\neq c$，则将 $a_i$ 改为 $1$，否则将 $i$ 往后移一位，$c$ 取反。发现操作等价从左到右将每个数依次跟 $i\bmod 2$ 比较，如果不同就改正，最多进行 $2n$ 次操作后就会进入循环。当 $n$ 为偶数时循环节长度为 $1$，奇数长度为 $2$，将 $k$ 缩小后暴力操作即可，时间复杂度 $\mathcal O(n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define mxn 200003
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
int n,k,c,a[mxn];
char s[mxn];
signed main(){
	scanf("%d%d%s",&n,&k,s+1);
	rep(i,1,n)a[i]=s[i]=='A'?0:1;
	if(!(n&1))k=min(k,n*2);
	else if(k>=n*4)k=(k-n*2)%(n*2)+n*2;
	int r=1;
	rept(i,0,k){
		if(a[r]==c)a[r]^=1;
		else c^=1,r=r%n+1;
	}
	rept(i,0,n)putchar((a[r]^c)?'B':'A'),r=r%n+1;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc011_d)

**题目大意**

> 给定 $n$ 个门，初始有开有关，$k$ 次操作从第一个门左侧扔一个球进去，如果一个门是开的，球会穿过，否则会被反弹，在此之后门会改变开关状态，求最终每个门的状态。
>
> 数据范围：$n\le 2\times 10^5,k\le 10^9$。

**思路分析**

如果第一个门是关的，会打开第一个门并结束，否则考虑整个过程：对于第 $i$ 个门，球第一次经过时一定是从左到右，且此时第 $i-1$ 个门是关着的。

如果第 $i$ 个门是开着的，那么会直接穿过并继续，否则会发开第 $i-1$ 个门并反弹。

那么第 $i-1$ 个门最终的状态就是第 $i$ 个门原始的状态取反。

因此第一个门是开着的时，会将所有门翻转并循环左移一位。

那么维护当前的偏移量，可以 $\mathcal O(1)$ 维护每次扔球的过程。

打表发现，经过 $\mathcal O(n)$ 次操作后序列的状态构成长度为 $2$ 的循环节，因此只要模拟 $\mathcal O(n)$ 次。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
char s[MAXN];
signed main() {
	int n,k;
	scanf("%d%d%s",&n,&k,s);
	k=min(k,4*n+(k&1));
	int i=0;
	while(k--) {
		if(s[i%n]==(i&1?'B':'A')) s[i%n]^=3;
		else ++i;
	}
	for(int j=i;j<i+n;++j) printf("%c",s[j%n]^(i&1?3:0));
	return 0;
}
```

---

## 作者：Sktic (赞：0)

[AT2340 [AGC011D] Half Reflector ](https://www.luogu.com.cn/problem/AT2340)

$2022:10:11$ 修复部分 $\text{Latex}$。


大家好，因为我非常喜欢暴力，所以我用暴力模拟草过了这题。~~其实是自己做的时候没有发现 $2n$ 循环节的规律。~~



题目大意：有 $n$ 个门排成一排，每个门会开着或者关着，如果门开着球就可以直接通过，关着的话球撞到上面就会反弹。只要球碰到一个门，这个门就会改变自己的形态。现在有 $k$ 个球，依次从所有门的最左端滚进去，问 $k$ 次后每个门的状态。门开着用 $B$ 表示，门关着用 $A$ 表示。



为方便表达，本文令开为 $\texttt{0}$，关为 $\texttt{1}$，球为 $\texttt{*}$，球的方向为 $\texttt{>}$ 或 $\texttt{<}$。



我们可以通过手玩发现一个很有意思的事情，如果第一个门是关着的，那么球就会直接被弹回去而不会影响后面的门。而剩余第一个门开着的情况，球就一定会从最右边出来。



我们可以简单证明一下，如果第一个门是开着的，球经过后这个门就会关上，而当第二个门（第一个门后面第一个关上的门，可以不一定是第二个，类比即可）是关上的时候，球就会反弹，此时将第二个门打开，又弹到第一个门，再将第一个门打开，于是又弹回第二个门，将其关上，然后继续向下走。如果觉得抽象可以看下面这个图： $\texttt{*>01} \to \texttt{1*>1} \to \texttt{1*<0} \to \texttt{0*>0} \to \texttt{01*>}$。



很容易发现，球过了第二个门之后第二个门也关上了，这就又构成了一个子问题，把第二个门也当作第一个门来看，因此发现球永远不会再从头出来。



发现递归这个性质以后我们可以考虑归纳法。设球现在滚到了第 $i$ 个门，若第 $i$ 个门是关上的，那么球会弹回去，再将第 $i$ 个门打开，于是我们就确定了此时的门状态为 $0$。



接下来分类讨论，设第 $i$ 个门状态为 $0$，$i+1$ 个门状态也为 $0$，那么球经过后第 $i$ 个门一定会变成 $1$，因为球经过第 $i$ 位后就会立即通过 $i+1$ 位，不会再回到第 $i$ 位（也就是开头的结论）。此时状况：$\texttt{*>00} \to \texttt{1*>0} \to \texttt{11*>}$。



若第 $i$ 个门状态为 $0$ ，第 $i+1$ 个门状态为 $1$ ，那么球经过后第 $i$ 个门一定会变成 $0$ 。因为球一开始通过第 $i$ 个门时它变为 $1$ ，而球会被 $i+1$ 个门反弹回来，然后在被 $i$ 反弹回去通过 $i+1$ ，然后就不会再回到 $i$ 了。此时状况：$\texttt{*>01} \to \texttt{1*>1} \to \texttt{1<*0} \to \texttt{0*>0} \to \texttt{01*>}$ 。



于是我们可以发现除了最后一位以外，每一个门在通过一个球之后的状态都是它下一个门的状态的取反，而最后一个门则固定关上（球通过开了的门出去，然后门关上了），而除了球一开始就被弹飞的情况外第一个门都是开的，因此我们可以把门的状态看成一个环，除了球被弹飞以外的状况，其他都是将环循环左移一位并取反。



于是我们只需要维护一个指针指向第一个门，在维护一个是否取反的变量，循环 $k$ 次即可。时间复杂度 $O(k)$，因为常数极小所以最慢的点也只需要 $100ms$，完全不用考虑 $2n$ 的循环节。（因为我不会证明）



AC Code:

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
typedef long long ll;
int a[maxn];
char s[maxn];
int main()
{
	int n,k;
	cin>>n>>k;
	cin>>(s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='A')
			a[i]=1;
		else
			a[i]=0;
	}
	int tp=1,f=0;
	for(int i=1;i<=k;i++)
	{
		if(f==0)
		{
			if(a[tp]==1)
				a[tp]=0;
			else
				f=1,tp++;
		}
		else
		{
			if(a[tp]==0)
				a[tp]=1;
			else
				f=0,tp++;
		}
		if(tp==n+1)
			tp=1;
	}
	if(f==0)
	{
		for(int i=tp;i<=n;i++)
			if(a[i]==1)
				putchar('A');
			else
				putchar('B');
		for(int i=1;i<tp;i++)
			if(a[i]==1)
				putchar('A');
			else
				putchar('B');
	}
	else
	{
		for(int i=tp;i<=n;i++)
			if(a[i]==0)
				putchar('A');
			else
				putchar('B');
		for(int i=1;i<tp;i++)
			if(a[i]==0)
				putchar('A');
			else
				putchar('B');
	}
	return 0;
}
```



---

## 作者：fade_away (赞：0)

# AGC011D - Half Reflector
[安利博客](https://blog.csdn.net/xmr_pursue_dreams/article/details/112599527)
## Solution
先考虑改变一次。
我们令$L$表示往左走的球，$R$表示往右走的球，$x$表示任意种类的球，$(-x)$表示与$x$相反种类的球。

- 当球处于$ARA$的状态（即有一个向右的球在两个$A$机器人之间）时，状态会这样改变：$ARA\to ALB\to BRB \to BAR$。

- 当球处于$ARB$的状态，$ARB\to AAR$。

观察这两种变化，可以得到下列信息：

- 按此过程进行时，做完一个$ARx$之后会变成$(-x)AR$，然后$R$的位置后推一个单位。
- 进行一次该过程会让$R$前面的球的种类变成$R$后面一个球的种类
- 当$R$前面有一个$A$之后，后面的所有状态$R$前面都是$A$。也就是如果某一时刻能做了，这个过程能一直做直到$R$在最末尾。
- 结束之后最末尾是$A$。

因此倘若初始时第一个球是$A$，那么我们必然不能进行该过程，则把它改成$B$。
否则会把前面连续一段$B$变成$A$，状态变成$AAA...RAxx...x$的形式，然后开始做上面的过程，从$R$左边的$A$开始的每个球变成它后面一个球的种类取反，这个过程相当于循环左移一个单位再整体取反。

于是我们可以维护一个$rev$表示全局翻转的次数，用类似队列的东西$O(k)$做了。

然后这题还有一个性质：
最多$2n$次之后，序列会循环变化，这个循环大小为$1$或$2$。
每整体循环位移一次之后，都会在末尾加一个$A$，而每次循环位移之前的整体取反会让之前的$A$变成$B$因此最多$2n$次之后，会变成$xBABABA$的形式。

因此我们做$min(k,2n+(k\;mod\;2))$次操作得到的序列就是答案了。

时间复杂度$O(k)$
## Code

```cpp
char st[MAXN];
int flag[MAXN];
signed main()
{
	int n=read(),k=read(),t=min(k,n*2+(k&1)),nw=1,rev=0;
	scanf("%s",st+1);
	for (int i=1;i<=n;i++) flag[i]=st[i]-'A';
	for (int i=1;i<=t;i++)
	{
		if (flag[nw]^rev) rev^=1,flag[nw+n]=flag[nw],nw++; 
		else flag[nw]^=1;
	}
	for (int i=nw;i<=nw+n-1;i++) putchar((flag[i]^rev)+'A');
	return 0;
}
```


---

## 作者：zhimao (赞：0)

对于此题 @Ryoku 讲得很好了 ， 我在这只是讲一下具体实现 ， 贴个代码 。

首先我们先模拟 $min(k,2n)$ 次 ，可以使用队列实现 ， 每次查看队首是否为 $A$ ， 是则取反 ， 否则取出队首 ， 在末尾加入一个 $B$ ,  再取反整个队列 。 但这样是 $O(n^2)$ 的 ， 会超时 。于是我想到一个办法 ， 差分 ， 每次累加差分数组 ， 可以判断出每个元素要反转几次（ 即是非反转 ）。

之后还原队列 ， 即把每个元素按应反转次数反转回来 。

最后判断队首是否要变即可 。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r,bo[10000000],lr[1000000];
char s[1000000];
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) lr[i]=s[i]-65;
	l=1;r=n;
	for(int i=1,boo=0;i<=(n<<1)&&m;i++,m--)
		if(!((lr[l]^boo)&1)) lr[l]^=1;
		else
		{
			bo[l+1]^=1;
			boo^=bo[++l];
			lr[++r]=1;
			bo[r+1]^=1;
		}
	for(int i=1,boo=0;i<=r;i++,boo^=bo[i]) lr[i]^=boo;//还原
	lr[l]=(lr[l]+(m&n&1))&1;//判断队首 ，当且仅当 n , m 都为奇数 
	for(int i=l;i<=r;i++) printf("%c",char(lr[i]+65));
	return 0;
}
```


---

## 作者：Graphcity (赞：0)

~~纪念第一道自己独立做出来的 AGC D。~~

题目描述的操作很有意思，不妨手玩一下小样例。这里总结出几种特殊情况：

- `BBBBBBB`，球从左往右之后变为 `AAAAAAA`。
- `BA`，球从左往右之后变为 `BA`。
- `AAAAAA`，球从第一个 `A` 的右边出发，经过后变为 `BBBBBA`。

根据以下规律，我们可以知道，对于这样一组样例 `BBBAAAABBBAAA`，做完一次操作之后会变成 `AABBBBAAABBBA`。

这个时候，神奇的事情就发生了：做一次操作，**相当于对原串进行一次循环移位，然后将原本的 `A` 变为 `B`，`B` 变为 `A`**。当然如果第一个字符就是 `A` 的话，只需要把它变成 `B` 即可。

这样我们就可以通过队列和翻转标记来快速进行一次操作。但是本题的操作次数非常多，我们猜想会出现一定的循环节。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

char s[Maxn+5]; int n;

int main()
{
    scanf("%s",s+1); n=strlen(s+1);
    for(int id=1;;id++)
    {
        if(s[1]=='A') s[1]='B';
        else {For(i,2,n) s[i-1]='A'+'B'-s[i]; s[n]='A';}
        printf("%2d: ",id);
        printf("%s\n",s+1);
        _sleep(500);
    }
    return 0;
}
```

写出打表程序后，测几组小样例，发现的确有循环节。

| 初始值 | 最终值 | 操作次数 |
| :-----------: | :-----------: | :-----------: |
| `AABBABAB` | `BABABABA` | 13 |
| `BBBBAAAABA` | `BABABABABA` | 10 |
| `AAABABBBB` | `ABABABABA` / `BBABABABA` | 17 |
| `AAAAAAA` | `ABABABA` / `BBABABA` | 8 |

很容易发现如下规律：

- $n$ 为偶数时，最终结果一定为 `BABABA... 。

- $n$ 为奇数时，最终会两次一循环。

- 到达循环节的次数几乎跟 $n$ 在同一级别。

所以暴力做完前面 $wn$ 次操作（这里取 $w=20$），最后再特判一下即可通过。时间复杂度 $O(wn)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e6;

int n,k,tag,val[Maxn+5]; char s[Maxn+5];

int main()
{
    scanf("%d%d%s",&n,&k,s+1); int id,l,r;
    For(i,1,n) val[i]=s[i]-'A';
    for(id=1,l=1,r=n;id<=n*20;id++)
    {
        if((val[l]^tag)==0) val[l]^=1;
        else val[++r]=val[l++],tag^=1;
        if(id==k)
        {
            For(j,l,r) putchar((val[j]^tag)==0?'A':'B');
            putchar('\n'); return 0;
        }
    }
    if(n%2==0)
    {
        For(i,1,n) putchar((i&1)?'B':'A');
        putchar('\n'); return 0;
    }
    if((k-n*20)&1)
    {
        if((val[l]^tag)==0) val[l]^=1;
        else val[++r]=val[l++],tag^=1;
    }
    For(i,l,r) putchar((val[i]^tag)==0?'A':'B');
    putchar('\n');
    return 0;
}
```

---

