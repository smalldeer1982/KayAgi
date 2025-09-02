# Colouring Game

## 题目描述

Alice and Bob are playing a game. There are $ n $ cells in a row. Initially each cell is either red or blue. Alice goes first.

On each turn, Alice chooses two neighbouring cells which contain at least one red cell, and paints that two cells white. Then, Bob chooses two neighbouring cells which contain at least one blue cell, and paints that two cells white. The player who cannot make a move loses.

Find the winner if both Alice and Bob play optimally.

Note that a chosen cell can be white, as long as the other cell satisfies the constraints.

## 说明/提示

In the notes, the cell numbers increase from left to right.

In the first testcase for Alice, she has two choices: paint the first and the second cells, or paint the second and the third cells. No matter what choice Alice makes, there will be exactly one blue cell after Alice's move. Bob just needs to paint the blue cell and its neighbour, then every cell will be white and Alice can't make a move. So Bob is the winner.

In the second testcase no matter what Alice chooses, Bob can choose to paint the fourth and fifth cells in $ 2 $ turns.

In the third testcase at first, Alice paints the third and the fourth cells. It doesn't matter if Bob paints the first and the second cells or the fifth and sixth cells, as Alice can paint the other two cells.

In the fourth testcase at first, Alice paints the second and the third cells. If Bob paints the fifth and the sixth cells or the fourth and the fifth cells, then Alice paints the seventh and the eighth cells. If Bob paints the seventh and the eighth cells, then Alice paints the fifth and the sixth cells.

In the fifth Alice chooses the middle two cells at first, then Bob obviously has only two options, whichever variant he chooses, Alice can choose the other one and win.

In the eighth no matter what Alice chooses, Bob can choose the other two symmetrical cells.

## 样例 #1

### 输入

```
8
3
BRB
5
RRBBB
6
RBRBRB
8
BBRRBRRB
6
BRRBRB
12
RBRBRBRBRRBB
12
RBRBRBRBBBRR
4
RBBR```

### 输出

```
Bob
Bob
Alice
Alice
Alice
Alice
Bob
Bob```

# 题解

## 作者：dottle (赞：14)

**前置知识：** SG 函数。

首先，我们从 A 的角度分析此问题，也就是说下面的“我”指 A。

我每次选择是以下三种之一（忽略左右顺序），RB、RW 或 RR。我们考察场上已经没有 RB 的情形。这时胜负关系之和先后手以及 R/B 分别的数量有关。因此在进入这个局面前，我想要最大化 R 个数与 B 个数的差值。因此，比起选择 RW，我更应该选择 RB，因为这样可以使 B 的个数也减少 1。对于 B 来说，也应该是这样的策略。

那么我就理解了双方的游戏策略了：

1.  若场上有 RB，则选择一个取掉。
2.  否则，根据场上的 R/B 数量以及目前的前后手判断谁输谁赢。

在第二步中，若 R/B 数量不等，则无论先后谁，都是谁多谁赢。而第一步中，场上 R/B 数量之差不会变化。也就是说，如果最开始 R/B 数量不同，则直接判断，谁多谁赢。

否则，R/B 数量相等，那么在第二步中，就是谁先手谁输。也就是说，谁先无法选择 RB 取掉，谁就输了。因为取 RB 只会发生在异色段中，因此这是若干独立的游戏。我们将所有异色段的 SG 异或起来就是整个游戏的 SG。

那么我们来算一段的 SG，枚举我们这次选的 RB 是 $i$ 和 $i+1$，分出两个子游戏，异或起来，求所有这些异或值的 mex 即可。然后打一个表出来找规律，肉眼跑一个 KMP 发现循环节是 68，这个问题就解决了。其实循环节是 34，但我找到的是 68，这没什么影响。

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1000005;
using namespace std;

int sg[N];
bool fl[100];

void init(){
	sg[2]=1;
	for(int i=3;i<1000;i++){
		for(int j=1;j<i;j++){
			fl[sg[j-1]^sg[i-j-1]]=1;
		}
		for(int j=0;j<100;j++){
			if(fl[j]==0){
				sg[i]=j;break;
			}
		}
		memset(fl,0,sizeof(fl));
	}
	for(int i=1000;i<N;i++)sg[i]=sg[i-68];
}

void solve(){
	int n;cin>>n;
	string s;cin>>s;
	int a=count(s.begin(),s.end(),'R');
	int b=count(s.begin(),s.end(),'B');
	if(a>b){
		cout<<"Alice"<<endl;
		return ;
	}
	if(a<b){
		cout<<"Bob"<<endl;
		return ;
	}
	int S=0;
	int len=0;
	for(int i=0;i<n;i++){
		if(i&&s[i]==s[i-1]){
			S^=sg[len];
			len=0;
		}
		len++;
	}
	S^=sg[len];
	if(S)cout<<"Alice"<<endl;
	else cout<<"Bob"<<endl;
}

main(){
	init(); 
	ios::sync_with_stdio(0);
	int _T=1;cin>>_T;
	while(_T--)solve();
}

```



---

## 作者：周子衡 (赞：12)

方便起见下面称 Alice 为红方，Bob 为蓝方。

容易发现，在有相邻的红蓝方格时，双方的最优决策一定是先消除红蓝方格。在没有相邻的红蓝方格后，如果此时红方先手，那么红格必须严格大于蓝格数量，红方才能获胜；反之亦然。我们不妨称这两个阶段为阶段一、阶段二。注意到阶段一的过程中双方格子数量的差值是不变的。那么，终结阶段一，逼迫对方开启阶段二就是双方在阶段一的唯一目标。

此时，阶段一的胜负条件变为“不能行动的一方负”。这是一个典型的 Nim 博弈。设 $a_n$ 为一条长度为 $n$ 的极长红蓝交错段的 SG 值。我们有

$$
a_n=\operatorname{mex}_{i+j=n-2}\{a_{i}\operatorname{xor}a_j\}
$$

特别地，$a_0=a_1=0$。

直接计算时间复杂度 $O(n^2)$，不能承受。可以算出若干项后上 [OEIS](http://oeis.org/A002187) 上找一下，可以看到这个序列有长为 $34$ 的周期。当然也可直接打表找出这一点。这样就可以轻松解决此题了。

---

## 作者：Watware (赞：12)

下称Alice为红方，Bob为蓝方。

很容易注意到，当双方颜色块数量不同的时候，少的那人一定会取胜，不妨设该方为红方。这是因为除非整个序列全部都是红色，这种情况下显然红方必胜，否则红蓝双方方一定能找到一种策略，使得每次操作本方颜色块数量只会减少一，显然这种策略对于双方来说都是最优的，而在这种策略下蓝方依然会比红方先行取完，红方必然获胜。

故排除掉双方颜色数量不同的情况，仅考虑颜色数量相同的情况：当场上存在红蓝两块相邻时，双方必然要优先选择这样的两块消除，否则己方的颜色块数量就会少于对方，从而落入必败的局面。这样不断的消除下去，在最后得到的局面下，红蓝双方的最优策略是每次消掉一个自己颜色的块，显然后手必胜。

综上所述，我们很自然地想到，将序列分割成若干个极大的双色相间段，那么这些段之间是互相独立的：双方无论如何都不会选择消掉两个相同颜色的块。
我们定义 $SG_i$  是一个长度为 $i$ 的红蓝相间块的 $SG$ 值，当其为 $0$ 时，先手必败，否则先手必胜，那么它的递推式子如下：

$ SG_0=SG_1=0$

$SG_n=Mex_{i=1}^{n-1}{SG_{i-1}\oplus SG_{n-i-1}}$

$SG_0=0$ 由题目定义的失败局面得到，$SG_1=0$ 是因为一个单独的颜色块，周边没有和它异色的颜色块，那么它在最优策略下会在博弈的最后阶段被消除，而且对答案没有影响，故它和任何的 $SG$ 值结合都应当得到该 $SG$ 值，故它应当是异或的单位元 $0$（当然由递推式它也应当是 $0$）

故对于双方颜色块数量相同的初始局面，我们只要得到了$SG$ 函数的值，将原序列划分为极大的双色相间段，并且将这些相间段的长度的 $SG$ 值异或起来，如果等于 $0$，Bob获胜，否则Alice获胜；对于双方颜色块数量不相同的初始局面，颜色块少的那方必胜。

注意到暴力求 $SG$ 是 $O(n^2)$ 的，不可接受，但这个序列有长为 $34$ 的循环节，仅在几个较小的值有例外，故我们可以较快求出 $SG$ 值~



```cpp
#include <bits/stdc++.h>
using namespace std;
const int M = 5010, N = 501000;
int t, n, ans, tp;
char s[N];
int tb[34] = {4, 8, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5,
              5, 9, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7};
int tsg(int x)
{
    switch (x)
    {
    case 0 : return 0;
    case 1 : return 0;
    case 15 : return 0;
    case 17 : return 2;
    case 18 : return 2;
    case 32 : return 2;
    case 35 : return 0;
    case 52 : return 2;
    default : return tb[x % 34];
    }
}
int main()
{
    scanf("%d", &t);
    for (int o = 0; o < t; o++)
    {
        scanf("%d %s", &n, s), ans = 0, tp = 0;
        for (int i = 0; i < n; i++) tp += (s[i] == 'R');
        if (tp < n - tp) printf("Bob\n");
        else if (tp > n - tp) printf("Alice\n");
        else
        {
            for (int i = 0, j; i < n; i = j)
            {
                j = i + 1;
                while (j < n && s[j] != s[j - 1]) j++;
                ans ^= tsg(j - i);
            }
            printf(ans ? "Alice\n" : "Bob\n");
        }
    }
    return 0;
}
```



---

## 作者：xujindong_ (赞：1)

显然我们操作时应该尽量减少取自己颜色的数量，同时争取把对方的格子也取掉，因此双方的策略是先取一红一蓝，如果没有了，就取一红/蓝一白。取一红一蓝不改变个数之差，若红的个数大于蓝的个数，Bob 一定先不能取。同理，红比蓝少判 Alice 负。

当红蓝相等，谁先没得取一红一蓝谁负。取出每个红蓝相间的极长段，每个段是完全独立的。同一段内的规则可以表示为一个 $1\times n$ 的棋盘，每次可以在相邻两格下棋。

这个游戏被称为 Dawson's Kayles。这个游戏包含了将一堆石子分成两部的操作，对于这类游戏，有一个统一的称呼：八进制游戏。

八进制游戏在某一堆内取走 $i$ 个石子，其可能允许三种操作：

- 取走 $i$ 个石子，用这次操作把这一堆取完；
- 取走 $i$ 个石子，剩下非空的一堆；
- 取走 $i$ 个石子，将剩下的分成非空的两堆。

我们可以将八进制游戏的规则简写为一个小数，小数点后第 $i$ 位用三个布尔值表示三个操作是否可行，也就是 $\mathbf{d}_0.\mathbf{d}_1\mathbf{d}_2\mathbf{d}_3\cdots$，其中 $\mathbf{d}_i=e_{i,0}+2e_{i,1}+4e_{i,2}$。Dawson's Kayles 是游戏 $\mathbf{0.07}$。

是否每个八进制游戏的 SG 都有周期是 Open problem，但我们可以证明一个八进制游戏的 SG 的周期性：

八进制游戏周期性定理：对于有限长八进制游戏 $\Gamma=\mathbf{d}_0.\mathbf{d}_1\mathbf{d}_2\mathbf{d}_3\cdots\mathbf{d}_k$，若存在 $n_0\geq 1,p\geq 1$ 使 $\forall n_0\leq n<2n_0+p+k,\mathscr{G}(n+p)=\mathscr{G}(n)$，则 SG 的循环节从 $n_0$ 开始，长度为 $p$。

证明：归纳。对于 $n\geq 2n_0+p+k$，考虑 $n+p$ 的其中一个后继状态 $(a,b)$，有 $a+b\geq 2n_0+2p$。不妨设 $a\geq 0,b\geq n_0+p$，则 $\mathscr{G}(a)\oplus\mathscr{G}(b)=\mathscr{G}(a)\oplus\mathscr{G}(b-p)$。而 $(a,b-p)$ 是 $n$ 的一个后继状态（$i$ 都是 $n+p-a-b$，因为 $b\geq n_0+p$，$(a,b),(a,b-p)$ 都从属于规则二或规则三）。同理可证 $n$ 的任一后继状态也对应到 $n+p$ 的后继状态，因此 $\mathscr{G}(n+p)=\mathscr{G}(n)$。

对 Dawson's Kayles，在计算 $176$ 项后可以得 $n_0=53,p=34$，因此可以 $O(1)$ 得到单个红蓝相间段的 SG，只需要将所有 SG 异或起来即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int sg[87]={0,0,1,1,2,0,3,1,1,0,3,3,2,2,4,0,5,2,2,3,3,0,1,1,3,0,2,1,1,0,4,5,2,7,4,0,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,2,3,3,0,1,1,3,0,2,1,1,0,4,5,3,7,4,8,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,9};
int t,n,d,ans;
char s[500005];
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cin>>t;
  while(t--){
    cin>>n>>s+1,s[n+1]=s[n];
    for(int i=1;i<=n;i++)s[i]=='R'?d++:d--;
    for(int i=1,cnt=0;i<=n+1;i++){
      if(s[i]==s[i-1])ans^=sg[cnt<=52?cnt:(cnt-53)%34+53],cnt=1;
      else cnt++;
    }
    puts(d?d>0?"Alice":"Bob":ans?"Alice":"Bob"),d=ans=0;
  }
  return 0;
}
```

---

## 作者：AC_love (赞：1)

显然，这个游戏会分成两部分。第一部分每个人消除一个蓝格子和一个红格子，第二部分每个人只能消除一个自己颜色的格子。

首先，如果某一方格子更多，那么他一定能赢。

原因很简单：第一部分两个人每次都会减少自己一个格子和对方一个格子，此时两个人格子个数的差值不变。第二部分每个人每个回合都只会减少一个自己的格子（除非所有格子都是同一个颜色，但是此时胜负是显然的），那么谁格子多就能坚持更多个回合。

然后我们来讨论一下双方格子一样多的时候谁会赢。

不难发现，一些 `R` 或 `B` 的连续段可以将整个段分成很多 `RBRB` 交错的段，显然只有 `RBRB` 交错的段可能会队胜负产生影响，因此我们只考虑 `RBRB` 交错的段即可。

我们对不同长度的交错段求一下它的 SG，显然可以 $O(n ^ 2)$ 求出。

但是问题是本题 $n$ 很大，$O(n^2)$ 注定要寄了。

那么我们可以考虑求出 $n$ 比较小时的 SG 值，然后尝试找规律。

发现整体而言这个 SG 值是个循环节长度为 $34$ 的周期，但是在一些特值上需要进行特判，全部找出即可。

---

## 作者：JWRuixi (赞：1)

~~我不会写代码……~~

- 题意

给定长度为 $n$ 的由 ```R``` 和 ```B``` 构成的串。每一轮 Alice 选择两个相邻的位置，其中至少一个是 ```R```，并将两个位置都改为 $W$，Bob 反之，他选择的两个位置至少有一个 ```B```。Alice 先手，不能操作者输，问胜者是谁。

- 分析

整个游戏大概可以分为两个阶段：

1. 两人都取 ```RB``` 或 ```BR```，在这个过程中，```R``` 的数量和 ```B``` 的数量均减少 $1$。
2. 两人都取 ```WC``` 或 ```CW```，```C``` 可以为 ```R``` 或 ```B```。

于是一个很显然的结论就是，如果 ```R``` 的数量多余 ```B``` 的数量，那么显然是 Alice 赢，反之亦然。

否则如果两者数量相等，那么谁先进入第二阶段显然会输掉游戏，于是考虑 SG 函数求解第一阶段。

整个序列可以被分为若干个 ```R```，```B``` 交替出现的连续段，对于其中一段，显然只有长度影响答案。

于是设 $SG_i$ 为当连续段长度为 $i$ 时的 SG 值。

选取一个 $i \in [1,n-1]$ 考虑同时删掉 $(s_i,s_{i+1})$，有转移方程：

$$SG_n = \text{mex}_{i=0}^{n-2}SG_i\bigoplus SG_{n-i-2}$$ 

于是直接 SG 定理即可。

- code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
//	#if ONLINE_JUDGE
//	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
//	#else
	#define gh() getchar()
//	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(5e5 + 500);
int T, n, SG[maxn], flg[105], S;
char s[maxn];

inline void solve () {
	n = read();
	scanf("%s", s + 1);
	int cr = 0, cb = 0;
	for (int i(1); i <= n; ++i) {
		if (s[i] == 'R') ++cr;
		else ++cb;
	}
	if (cr > cb) return puts("Alice"), void();
	if (cr < cb) return puts("Bob"), void();
	S = 0;
	int len = 0;
	for (int i = 1; i <= n; i++) {
		if (i > 1 && s[i] == s[i - 1]) S ^= SG[len], len = 0;
		++len; 
	}
	S ^= SG[len];
	puts(S ? "Alice" : "Bob");
}

signed main () {
	SG[2] = 1;
	for (int i = 3; i <= 100; i++) {
		for (int j = 0; j < i - 1; j++) flg[SG[j] ^ SG[i - j - 2]] = 1;
		while (flg[SG[i]]) ++SG[i];
		memset(flg, 0, sizeof(flg));
	} 
	for (int i = 101; i < maxn; i++) SG[i] = SG[i - 34];
	for (int i = 1; i <= 34; i++) fprintf(stderr, "%lld%c", SG[i], " \n"[i == 34]);
	T = read();
	while (T--) solve();
}
```

---

## 作者：baka24 (赞：0)

博弈论题目，可以先考虑其规则有哪些性质，玩家的策略是怎样的。

对于此题，就考虑，如果我是 Alice，我的策略是什么。

我希望尽可能多的操作，也就是说，我希望我的操作次数尽量多。对应的，我希望对方的操作次数尽量少。

观察题目，发现对于两人而言，每次操作一定会减少至少一个自己代表色的颜色块，同时颜色块数量不会增加。

那么为了尽可能增加我的操作次数，减少对方的操作次数，我应该优先取走形如 `RB` 或 `BR` 的颜色块。

对应的，对方的策略也相同。也就是说，Alice 和 Bob 在场上存在 `RB` 或 `BR` 块时，一定优先取这些块。

那么当场上不存在这些块时怎么办？

此时，因为场上不存在 `RB` 或 `BR`，那么每个连续非白颜色块将只有一种颜色。

任何人都无法减少对方的操作次数，只能增加自己的操作次数。

那么此时的策略应该是从两侧开始取，每次操作一个颜色块和一个白块。

于是，每个人的操作次数便是剩余的自己代表色色块数量。

假设某个时刻，场上已经不存在 `RB` 或 `BR`，此时有 $x$ 个 `R`，$y$ 个 `B`。
- 如果 $x>y$，那么 Alice 将获胜。
- 如果 $x=y$，那么后手获胜。
- 如果 $x<y$，那么 Bob 将获胜。

也就是说，当 $x\ne y$ 时，获胜方是不由谁是先手而决定的。

同时，注意到每次取走一个 `RB` 或 `BR` 段时，`R` 和 `B` 的差并不会改变。综上可以得到，当场上 `R` 和 `B` 数量不相等时，胜者已经确定了。

如果 `R` 的数量比 `B` 的数量多，Alice 将获胜。

如果 `B` 的数量比 `R` 的数量多，Bob 将获胜。

接下来考虑较特殊的情况：二者数量相等。

此时取走最后一个 `RB` 或 `BR` 段的人将获胜，那么游戏变化为给定一个字符序列，两人每次取走一个 `RB` 或 `BR`，取不了的人输。

观察其有什么性质。首先可以把连续多个同色的端切开，使其形成若干个子游戏，因为它们之间不会互相干扰。

例子：
```
BRBRRRBBRBR->BRBR R RB BRBR
```

既然我们想合并几个子游戏，首先可以想到 SG 函数。

考虑一个如何表示一个子游戏的状态。

因为该字符序列是 `RB` 相间的，所以一个子游戏的 SG 值是什么只和序列长度有关。

考虑一个状态的后继状态，玩家可以选择一个 $i$ 并取走 $i,i+1$。也就是说 $SG(n)$ 后继状态为 $SG(i-1)\oplus SG(n-i-1)$。

那么有 $SG$ 函数递推式：$SG(n)=\operatorname{mex}\{\forall 1\le i<n,SG(i-1)\oplus SG(n-i-1)\}$。

此递推式为 $O(n^2)$ 级别，无法通过此题。

不过，在输出 $SG$ 函数的序列后，会发现它每一项值不大。可以猜测它存在循环节。

经过肉眼观察或者写一个 KMP 之后，可以得到其循环节长度为 $34$，于是在开始循环之后没必要再单次 $O(n)$ 递推，直接按照循环节构建即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;if(c==EOF)return -1;c=getchar();}while(c<='9'&&c>='0')x=x*10+c-'0',c=getchar();return x*f;}
const int MAXN=500010;
int n,m,ans,a[MAXN],sg[MAXN],q[MAXN];
char c[MAXN];
void init(){
    for(int i=1;i<=1000;i++){
        for(int j=1;j<i;j++)q[sg[j-1]^sg[i-j-1]]=1;
        int mex=0;
        while(q[mex])mex++;
        sg[i]=mex;
        for(int j=1;j<i;j++)q[sg[j-1]^sg[i-j-1]]=0;
        // cout<<sg[i]<<" ";
    }
    // cout<<endl;
    for(int i=1001;i<=MAXN-5;i++)sg[i]=sg[i-34];
}
void slv(){
    n=read();
    scanf("%s",c+1);
    for(int i=1;i<=n;i++)a[i]=c[i]=='R';
    int p0=0,p1=0;
    for(int i=1;i<=n;i++)p0+=a[i]^1,p1+=a[i];
    if(p0!=p1){
        printf("%s\n",p0>p1?"Bob":"Alice");
    }
    else{
        int lst=1;ans=0;
        for(int i=1;i<n;i++){
            if(a[i]==a[i+1])ans^=sg[i-lst+1],lst=i+1;
        }
        ans^=sg[n-lst+1];
        printf("%s\n",ans?"Alice":"Bob");
    }
}
signed main(){
 	freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    init();
    int _=read();while(_--)
    slv();
    return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定 $n$ 个格子，第 $i$ 个格子有颜色红色或蓝色；先手可以选择两个相邻的格子满足至少一个格子为红色，然后将这两个格子染成白色；后手可以选择两个相邻的格子满足至少一个格子为蓝色，然后将这两个格子染成白色。无法进行操作的输，求先手还是后手必胜。 

## 思路

显然这是个不平等博弈，考虑转化。由于先手和后手的每一步操作都会使自己颜色的格子个数减一，于是最优的策略应为在减少自己颜色的同时尽可能使对方颜色也减少，即先手和后手每次都应该尽可能选择一个红蓝相间的段。而当满足条件的段用完时，显然是剩下颜色更多的一方胜。于是我们将原题的博弈转化为了两个阶段：

1. 先手和后手应当不断删去红蓝相间的段直到找不到这样的段；
2. 开始消耗自己剩下的颜色储备，最终颜色更多的一方胜。

注意到第一阶段的操作是平等博弈，可以使用 NG 函数和 Nim 博弈相关的技巧去做；而且从第一阶段到第二阶段的过程中红蓝颜色格子的个数之差是保持不变的，所以当红蓝颜色格子数量不等时，我们就可以直接得出谁胜；否则最终游戏的 SG 值由这么几个子游戏，即几条极长的红蓝仙剑的段的 SG 值异或得到。记长度为 $k$ 的红蓝相间的段的 SG 值为 $f(k)$，且 $a_0=a_1=0$；考虑枚举断点，有
$$
f(k)=\operatorname{mex}_{i+j+2=k}\{a_i\oplus a_j\}
$$
考虑找一下规律，打个表发现这玩意除了 $0,1$ 项每 $34$ 项为一个周期（建议对表跑一个 KMP），那么就做完了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5, maxv = 105;
int f[maxn]; bool vis[maxv]; // 记录 sg 函数值 & mex
void init() {
    f[0] = f[1] = 0, f[2] = 1;
    for (int i = 3; i <= 100; i ++) {
        memset(vis,0,sizeof(vis));
        for (int j = 1; j < i; j ++)
            vis[f[j - 1] ^ f[i - j - 1]] = 1;
        for (int j = 0; j < maxv; j ++)
            if (!vis[j]) { f[i] = j; break; }
    } for(int i = 101; i <= maxn - 5; i ++) f[i] = f[i - 34]; // 接着就可以直接预处理了
}
int n; char S[maxn];
void work() {
    scanf("%d %s", &n, S + 1);
    int Rcnt = 0, Bcnt = 0;
    for (int i = 1; i <= n; i ++)
        S[i] == 'R' ? ++ Rcnt : ++ Bcnt;
    if (Rcnt != Bcnt) 
        return puts(Rcnt < Bcnt ? "Bob" : "Alice"), void(0);
    int ops = 0;
    for (int i = 2, j = 1; i <= n; i ++, j ++) {
        if (S[i - 1] == S[i]) ops ^= f[j], j = 0;
        if (i == n) ops ^= f[j + 1];
    } puts(ops ? "Alice" : "Bob");
}
int main() {
    int T; scanf("%d", &T), init();
    while (T --) work();
    return 0;
}
```

---

## 作者：chlchl (赞：0)

用一种有趣的方式理解题面：

> 有 $n$ 个细胞，每个细胞是红色或蓝色的，A 只能用红色细胞，B 只能用蓝色细胞（A 先 B 后）。每次选定一个细胞并消耗掉，并且可以顺便“带走”一个相邻细胞（如果有的话）。没有细胞的人就 ~~die~~ 输了。

## Solution
首先，消耗细胞对自己是不利的，不过，如果可以带走别人一个细胞，那是不亏的。

所以很容易理解一个策略：每次一定是选择 ``RB`` 来操作，主打一个~~自己没了，别人也不能好过~~同归于尽的策略。

而且在这种策略下，红蓝细胞的数量差是不变的。

再考虑剩下所有细胞都不相邻的情况。这个时候先手的细胞数必须严格大于后手才能赢。

所以对于一开始先手的 A 来说，如果它的细胞数是严格大于 B 的，先同归于尽然后一个一个消除，他是必胜的。

同理，如果 B 的细胞数严格大于 A，那么 B 也是必胜的。

问题只剩下两种细胞相等时怎么做。

注意到这时是有策略的，比如 ``RBRBWWBWR``，如果 A 消耗了最前面的 ``RB``，B 把剩下那个 ``RB`` 也拿掉，显然是 A 输。

**但是如果 A 拿的是第 $2,3$ 个位置的 ``BR``，那么他是可以赢的。**

换言之，对于每位玩家来说，都必须要避免先进入“无法消耗形如 ``RB``”的情况，不妨设这个情况为白热化阶段。

问题成了一个 Nim 游戏。所以考虑对于所有极大的 ``RB`` 连续串，计算出 SG 函数的异或和。

再来思考此时的策略，可以发现一定是尽量断开原有的 ``RB`` 连续串，这样可以使游戏更快进入到白热化阶段。

所以对于一个长度为 $len$ 的 ``RB`` 连续串，我们有：

$$SG(len)=\text{mex}_{i+j=len-2}\ SG(i)\oplus SG(j)$$

边界是 $SG(0)=SG(1)=0$。

但是直接计算是 $O(n^2)$ 的。~~打个表~~观察可得这个 SG 函数有一个长度为 $34$ 的循环节（**请注意循环节不是从一开始就有的**）。

所以懂得都懂。

~~这题怎么出出来的啊……~~


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
int T, n, sg[N], vis[110];
char s[N];

int get(char c){
	return (c == 'B');
}

void solve(){
	scanf("%d", &n);
	scanf("%s", s + 1);
	int res = 0, col[2] = {0, 0};
	for(int i=1;i<=n;i++)
		col[get(s[i])]++;
	if(col[0] > col[1])//红的多 
		return printf("Alice\n"), void();
	if(col[1] > col[0])
		return printf("Bob\n"), void();
	for(int i=1;i<=n;i++){
		int j = i;
		int op = get(s[i]);
		while(j < n && get(s[j + 1]) == op ^ 1)
			++j, op ^= 1;
		res ^= sg[j - i + 1];
		i = j;
	}
	printf(res ? "Alice\n" : "Bob\n");
}

int main(){
	sg[0] = sg[1] = 0, sg[2] = 1;
	for(int i=3;i<=300;i++){
		memset(vis, 0, sizeof(vis));
		for(int j=0;j<=i-2;j++)
			vis[sg[i - 2 - j] ^ sg[j]] = 1;
		for(int j=0;j<=100;j++){
			if(!vis[j]){
				sg[i] = j;
				break;
			}
		}
	}
	for(int i=300;i<=N-5;i++)
		sg[i] = sg[i - 34];
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```

---

