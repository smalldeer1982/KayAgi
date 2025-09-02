# [ARC171E] Rookhopper's Tour

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc171/tasks/arc171_e

縦 $ N $ マス、横 $ N $ マスのグリッドがあります。グリッドの上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と呼びます。また、 $ 1 $ 個の黒石と $ M $ 個の白石があります。  
 あなたはこれらの道具を使って $ 1 $ 人でゲームをすることにしました。

ゲームのルールを説明します。はじめに、あなたは黒石を $ (A,\ B) $ に置きます。その後、 $ M $ 個の白石をグリッドのいずれかのマスに $ 1 $ 個ずつ置きます。ただし、

- $ (A,\ B) $ に白石は置けません。
- 白石は $ 1 $ つの行に高々 $ 1 $ 個しか置けません。
- 白石は $ 1 $ つの列に高々 $ 1 $ 個しか置けません。
 
その後、あなたは操作を行えなくなるまで以下の操作を行います。

- 黒石が $ (i,\ j) $ にあるとする。次の $ 4 $ 通りの操作のいずれかを行う。
  - $ (i,\ k) $ $ (j\ \lt\ k) $ に白石が置いてある時、その白石を取り除いて $ (i,\ k\ +\ 1) $ に黒石を動かす。
  - $ (i,\ k) $ $ (j\ \gt\ k) $ に白石が置いてある時、その白石を取り除いて $ (i,\ k\ -\ 1) $ に黒石を動かす。
  - $ (k,\ j) $ $ (i\ \lt\ k) $ に白石が置いてある時、その白石を取り除いて $ (k\ +\ 1,\ j) $ に黒石を動かす。
  - $ (k,\ j) $ $ (i\ \gt\ k) $ に白石が置いてある時、その白石を取り除いて $ (k\ -\ 1,\ j) $ に黒石を動かす。
      - ただし、黒石を動かす先のマスが存在しない場合はそのような動きは出来ない。
 
図で例示すると以下のようになります。ここで `B` は黒石、 `W` は白石、`.` は何もないマス、`O` は黒石を動かせるマスを意味します。

 ```
..O...
..W...
......
......
..B.WO
......
```

操作を終了した時点で以下の条件を全て満たしているとき、ゲームはあなたの勝利となります。そうでない場合は敗北となります。

- グリッドから白石が全て取り除かれている。
- 黒石が $ (A,\ B) $ に置かれている。
 
はじめの $ M $ 個の白石の配置としてあり得るもののうち、その後の操作をうまく行うことでゲームに勝利することが可能である配置は何通りありますか？答えを $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ M\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A\ \leq\ N $
- $ 1\ \leq\ B\ \leq\ N $
- $ N,\ M,\ A,\ B $ は整数
 
### Sample Explanation 1

例えば白石を以下の図のように配置したとします。 ``` ...... ..BW.. .....W ...... ..W... ....W. ``` このときあなたは次の手順で黒石を動かすことでゲームに勝利することが出来ます。 - $ (5,\ 3) $ にある白石を取り除いて $ (6,\ 3) $ に黒石を動かす。 - $ (6,\ 5) $ にある白石を取り除いて $ (6,\ 6) $ に黒石を動かす。 - $ (3,\ 6) $ にある白石を取り除いて $ (2,\ 6) $ に黒石を動かす。 - $ (2,\ 4) $ にある白石を取り除いて $ (2,\ 3) $ に黒石を動かす。 - グリッドから全ての白石を取り除き、かつ黒石が $ (A,\ B)\ =\ (2,\ 3) $ に置かれた状態になったので、あなたはゲームに勝利する。 ゲームに勝利することが可能である白石の配置は全部で $ 4 $ 通りあります。

## 样例 #1

### 输入

```
6 4 2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
5 3 1 3```

### 输出

```
0```

## 样例 #3

### 输入

```
200000 47718 21994 98917```

### 输出

```
146958602```

# 题解

## 作者：lanos212 (赞：7)

### I. 挖掘一些基本的性质

首先我们发现，黑石子一定是横纵交替着移动的。

(证明：如果连续横向移动两次，则该行出现了 $\ge 2$ 个白石子，与题面矛盾，纵向同理。)

那么当 $M$ 为奇数时，我们一定无法回到起点。

(证明：$M$ 为奇数时，我们发现第一次移动和最后一次移动在同一列或同一行上，也就是该列或行出现了 $\ge 2$ 个白石子，与题面矛盾。)

而当 $M\le 2$ 时，也显然无解。

所以接下来，我们只考虑 $M\ge 4$ 且 $M$ 为偶数的情况。

---

### II. 涂色

我们考虑对于一种合法的局面，模拟黑石子的移动过程，并且在移动过程中对行列进行**涂色**。

具体地，在黑石子纵向移动时，我们对这次移动使用的白石子所在行**染黄**，然后在黑石子停下的行**染绿**：

![](https://cdn.luogu.com.cn/upload/image_hosting/m602i40m.png)

同样地，在横向移动时，白石子所在列**染黄**，黑石子停下的列**染绿**（列染色与行染色独立，不互相影响，重叠）：

![](https://cdn.luogu.com.cn/upload/image_hosting/3uy9lax8.png)

特别地，在最开始，我们将黑子所在行列都直接**染绿**：

![](https://cdn.luogu.com.cn/upload/image_hosting/w3kyms6p.png)

---
### III. 整个染色过程与白子摆放的双射

我们考虑将整个黑子移动过程中，分成下面两部分：

- 前 $M-2$ 次移动，我们会给相邻 $2$ 行/列染上颜色，**并且这 $2$ 行/列在之前没有颜色**（如果有颜色，则存在一行/列出现 $\ge 2$ 个白石子，或者黑石子在下一步无法移动）。

- 最后 $2$ 次移动，我们在染色时，绿色行/列将和**最初黑子所在行列的绿色**重合，黄色行/列靠在绿色行/列旁边。（这一部分看下面的例图）

![](https://cdn.luogu.com.cn/upload/image_hosting/xqr5x6tw.png)

我们考虑钦定最后两次操作**染黄的行**在黑子最初所在行的下方，**染黄的列**在黑子最初所在列的右侧（也就是黑石子在最后两次操作前，相对初始位置所在的方向被钦定）。

我们再钦定，倒数第二次操作是纵向移动，最后一次是横向移动。（这一部分也可以再看上面的例图）

那么我们只要对最初的 $(A,B)$ 翻转八种情况，即可把所有的方案数全：

![](https://cdn.luogu.com.cn/upload/image_hosting/lkab53jz.png)

那么现在，我们的合法染色过程如下：

- 最初黑子所在行为绿，下一行为黄，所在列与下一列同理。

- 第一次操作，任取未被染色的相邻两行，靠近黑子的一侧染黄，远离的一侧染绿，移动黑子，放置白子。

- 第二次操作，任取未被染色的相邻两列，靠近黑子的一侧染黄，远离的一侧染绿，移动黑子，放置白子。

- $\dots$

- 倒数第四次操作，其余部分和第一次操作同理，不同的是，**选择的相邻两行必须在黑子最初所在行下方**。（否则无法保证最后两次操作黄绿位置正确）。

- 倒数第三次操作，其余部分和第二次操作同理，不同的是，**选择的相邻两行必须在黑子最初所在列右方**。（否则无法保证最后两次操作黄绿位置正确）。

- 进行倒数第二次和第一次操作，移动黑子的过程放白子，最终回到起始位置。

我们发现，染色过程和**确定白子摆放方案及找出任意一种合法操作顺序**的方案数相同。

虽然这和题目要求计数的不太一样，我们先算一下这个的方案数：

- 行列互相独立，分别计算方案数相乘即可，下面设 $m=\frac{M}{2}-1$ 。

- 按顺序染相邻两行，染 $m$ 次，且**最后一次染色在黑子初始行下方**，枚举在黑子初始行下方有多少行，计算方案数为 $\sum\limits_{d=0}^{m}d\binom{N-A-1-d}{d}\binom{A-1-(m-d)}{m-d}(m-1)!$（下方染 $d$ 次，上方染 $m-d$ 次，分别确定染的位置，然后确定染色顺序，注意最后一次染色在下方）。

- 列的计算与行同理。

实际上，计算**确定白子摆放方案及找出任意一种合法操作顺序**的方案数与答案等价。

此时我们只需要证明，对于一种合法摆放白子的方案，只有**唯一一种操作方式**使黑子操作后回到初始位置。

大致思路就是考虑反证，由于第一次操作如果不变，后面的操作就会都唯一确定，那么只可能存在另一种第一次操作不同的操作方案。

那么从黑子初始位置开始，往外延伸出的两条道路都要能往外走，也能往里走回来。

然后通过归纳，白子将像下图一样无限延伸，最终超出棋盘：

![](https://cdn.luogu.com.cn/upload/image_hosting/b17a8znk.png)

所以对于一种合法摆放方式，其可行操作方案的唯一性得证。

那么按照前面的方式计算方案数就可以了，时间复杂度 $O(N)$。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mo=998244353;
long long n,m,A,B,ans;
long long jc[1000001],inv[1000001];
inline long long ksm(long long x,long long y){if (mo==1) return 0; long long ans=1;for (int i=0;(y>>i);++i){if (y>>i&1) ans=ans*x%mo; x=x*x%mo;}return ans;}
inline long long invv(long long x){return ksm(x,mo-2);}
inline void init(int x){jc[0]=1; for (int i=1;i<=x;++i) jc[i]=jc[i-1]*i%mo;inv[x]=invv(jc[x]); for (int i=x-1;i>=0;--i) inv[i]=inv[i+1]*(i+1)%mo;}
inline long long C(long long x,long long y){if (x<y) return 0;return jc[x]*inv[y]%mo*inv[x-y]%mo;}
inline void cal(long long x,long long y){
	long long H=0,W=0;
	for (int ii=0;ii<2;++ii){
		for (int d=0;d<=m;++d){
			int u=m-d;
			H=(H+C(n-x-1-d,d)*C(x-1-u,u)%mo*jc[m-1]%mo*d)%mo;
		}
		swap(H,W); swap(x,y);
	}
	ans=(ans+H*W)%mo;
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); init(1e6);
	cin>>n>>m>>A>>B;
	if (m%2 || m<=2){cout<<0; return 0;} m=m/2-1;
	cal(A,B); cal(n-A+1,B); cal(A,n-B+1); cal(n-A+1,n-B+1);
	cal(B,A); cal(B,n-A+1); cal(n-B+1,A); cal(n-B+1,n-A+1);
	cout<<ans;
	return 0;
}
```

---

## 作者：E_firework (赞：3)

upd on 2-14：改了个错别字。

upd on 2-16：改了一个逻辑不流畅的地方。

让我们用每次移动的的行和列表示整个移动的过程，可以发现这是和合法的摆放方案一一对应的。

例如下图中的移动路径可以用“r4 c8 r8 c5 r1 c2”表示。

![](https://cdn.luogu.com.cn/upload/image_hosting/1av6y6oo.png)

首先发现相邻两次移动只能是一次行、一次列，否则会导致两块石头在同一行或者列。同样的，第一次移动与最后一次移动也只能是一次行、一次列，所以移动数（也就是白色石头数 $M$）不能是奇数，同时发现他不能是 $2$。在这两种情况下答案为 $0$。

接下来分析发现，如果黑色石头要从第 $x$ 行到达第 $y$ 行（假设 $x<y$），那么第 $x$、$y$ 以及 $y-1$ 行都必须有白色石头，而黑色石头在哪一列并没有影响，对称的，黑色石头在列间移动时，他在哪一行也没有影响。不难发现，行和列的移动其实是独立的。接下来我们只考虑行上的方案数。

下图是我们把上面例子中行间移动单独提出得到的结果：

![](https://cdn.luogu.com.cn/upload/image_hosting/1u67n2lz.png)

其中圈出的元素是行间移动跳过的那些石头。

我们可以把相邻的一对白色石头分为一组，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/85witc5n.png)

这里圈出的元素是**列**间移动跳过的那些石头。

发现如果一组的上一组石头在他的左边，那么圈在这一组的右边，否则在左边。

我们令黑色石头的坐标为 $A$。

注意到有一个限制是我们要从一个给定的坐标 $A$ 开始，也就是说 $A$ 必须是圈中的。分类讨论同一组中另一块石头在他的左边还是右边。然后我们枚举在 $A$ 的左边有多少组，知道某一边放石头的组数也就知道了那一边的空位有多少个，算一个石头的组和空位错开放的组合数后就得到了放置的方案。然后我们只要确定了这些组的遍历顺序，就可以知道每一组中圈出的石头是哪些，也就确定了一个方案。如果与 $A$ 同一组中另一块石头在他的左边就说明最后一个经过的位置在 $A$ 的左边，反之在右边，答案要乘上左边或者右边的组数。剩下 $\frac{M}{2}-2$ 组的顺序可以任选，也就是说方案还要乘 $(\frac{M}{2}-2)!$。

将行的答案和列的答案相乘在乘 $2$（可以先走行或先走列）就是最终答案。

如果有不理解的地方可以先看代码。

code:

```cpp
#include<bits/stdc++.h>
#define LL long long
#define mes(s, x) memset(s, x, sizeof s)
#define Maxn 200005
#define mod 998244353
using namespace std;
inline LL read(){char c;c = getchar();while(!(('0' <= c && c <= '9') || c == '-')) c = getchar();bool flag = 0;if(c == '-'){flag = 1;c = getchar();}LL tot = 0;while('0' <= c && c <= '9'){tot = 10 * tot + c - '0';c = getchar();}return flag ? -tot : tot;}
LL inv[Maxn], frac[Maxn], _frac[Maxn];
void init(int n){
    inv[1] = 1;
    for(int i = 2; i <= n; i++) inv[i] = mod - mod / i * inv[mod % i] % mod;
    frac[0] = _frac[0] = 1;
    for(int i = 1; i <= n; i++){
        frac[i] = i * frac[i - 1] % mod;
        _frac[i] = inv[i] * _frac[i - 1] % mod;
    }
}
LL C(int i, int j){//这是组合数
    if(i < 0 || i > j) return 0;
    return frac[j] * _frac[i] % mod * _frac[j - i] % mod;
}
LL solve(int n, int m, int x){
    LL sum = 0;
    for(int i = 0; i < m; i++){//枚举左边的组数i
        sum = (sum + (m - i - 1) * frac[m - 2] % mod * C(i, x - 1 - i) % mod * C(m - i - 1, n - x - 1 - (m - i - 1)) % mod) % mod;//另一块石头在右边
        sum = (sum + i * frac[m - 2] % mod * C(i, x - 2 - i) % mod * C(m - i - 1, n - x - (m - i - 1)) % mod) % mod;//另一块石头在左边
    }//放不下的情况组合数为0，所以不需要额外讨论
    return sum;
}
int main(){
    int n = read(), m = read(), a = read(), b = read();
    init(n);
    if(m % 2 || m == 2){//特判M为奇数或者2的情况
        puts("0");
        return 0;
    }
    m /= 2;
    printf("%lld", 2 * solve(n, m, a) * solve(n, m, b) % mod);
	return 0;
}
```

---

## 作者：Felix72 (赞：1)

我们手玩一下合法方案，看看它满足什么性质。如下就是一组方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/7lw4fp98.png)

如图，我们规定上下移动时经过的白色石头（图中为蓝色）对应一条横向橙色线，左右移动时经过的白色石头对应一条纵向绿色线。这样，我们把放石头转化成了选定若干条直线。

从中我们能得到一些结论：

- 橙线、绿线的合法性独立，可以分开计数；
- 同色的线与线之间分顺序，位置一样但顺序不同是两种方案；
- 我们若在某个位置选定一条线，同时就禁选了另一个位置；
- 每种颜色的最后一条线必然挨着起点，并与倒数第二条线在起点同一侧。

对于结论三的解释：比如这一步纵向移动越过了某个石头，之后必然会横向移动，也就是说这个石头所在行和相邻的一行都不再能放石头；

对于结论四的解释：最后要回到起点。回来之前，倒数第二步需要在一个正确的方位。

于是我们枚举最后一步从哪个方向回到起点，对选线的方案计数。设 $f_{n,k}$ 为 $n$ 个空行（或列），确定 $k$ 条直线的方案数，由于确定一条直线相当于禁用两个位置，而且直线处于其中哪个位置在知道直线顺序时是固定的，我们有 $f_{n,k} = \binom{n - k}{k}$。枚举起点左右（或上下）两侧分别有几条直线，直接计算即可。

```cpp
/*蛋糕鱼乐园*/
#include <bits/stdc++.h>
using namespace std;

const int N = 200010, mod = 998244353;
int n, m, sx, sy; long long ans;

long long fac[N], inv[N];
inline long long qpow(long long a, long long b)
{
	long long ans = 1;
	while(b)
	{
		if(b & 1) ans = ans * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return ans;
}
inline long long C(int n, int m)
{if(n < m) return 0; return fac[n] * inv[m] % mod * inv[n - m] % mod;}
inline void init()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 200000; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[200000] = qpow(fac[200000], mod - 2);
	for(int i = 199999; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}

inline long long work(int num)
{
	int nx = num - 1, ny = n - 1 - num;
	if(nx < 0 || ny < 0) return 0;
	long long res = 0;
	for(int i = 1; i <= m; ++i)
		res = (res + C(nx - i, i) * C(ny - (m - i - 1), m - i - 1) % mod * i % mod * fac[m - 2] % mod) % mod;
	return res;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> sx >> sy; init();
	if(m <= 2 || m % 2 == 1) {cout << 0 << '\n'; return 0;}
	m /= 2;
	cout << (work(sx - 1) + work(n - sx)) * (work(sy - 1) + work(n - sy)) % mod * 2 % mod << '\n';
	return 0;
}
/*

*/
```

---

## 作者：XYQ_102 (赞：0)

## E - Rookhopper's Tour

> ### Problem Statement
> 
> There is a grid with $N$ rows and $N$ columns. Let $(i, j)$ denote the cell at the $i$-th row from the top and the $j$-th column from the left. Additionally, there is one black stone and $M$ white stones.  
> You will play a single-player game using these items.
> 
> Here are the rules. Initially, you place the black stone at $(A, B)$. Then, you place each of the $M$ white stones on some cell of the grid. Here:
> 
> +   You cannot place a white stone at $(A, B)$.
> +   You can place at most one white stone per row.
> +   You can place at most one white stone per column.
> 
> Then, you will perform the following operation until you cannot do so:
> 
> +   Assume the black stone is at $(i, j)$. Perform one of the four operations below:
>     +   If there is a white stone at $(i, k)$ where $(j \lt k)$, remove that white stone and move the black stone to $(i, k + 1)$.
>     +   If there is a white stone at $(i, k)$ where $(j \gt k)$, remove that white stone and move the black stone to $(i, k - 1)$.
>     +   If there is a white stone at $(k, j)$ where $(i \lt k)$, remove that white stone and move the black stone to $(k + 1, j)$.
>     +   If there is a white stone at $(k, j)$ where $(i \gt k)$, remove that white stone and move the black stone to $(k - 1, j)$.
>         +   Here, if the cell to which the black stone is to be moved does not exist, such a move cannot be made.
> 
> The following figure illustrates an example. Here, `B` reprfesents the black stone, `W` represents a white stone, `.` represents an empty cell, and `O` represents a cell to which the black stone can be moved.
> 
> ```auto
> ..O...
> ..W...
> ......
> ......
> ..B.WO
> ......
> ```
> 
> You win the game if all of the following conditions are satisfied when you finish performing the operation. Otherwise, you lose.
> 
> +   All white stones have been removed from the grid.
> +   The black stone is placed at $(A, B)$.
> 
> In how many initial configurations of the $M$ white stones can you win the game by optimally performing the operation? Find the count modulo $998244353$.
> 
> $1 \le n,m \le 2\times 10^5$。

感觉非常有意思的题目，一眼会感觉到有很多性质，但是又不太能具体出来。

首先容易发现走的路线一定只有两种：

+   沿着行 $\to$ 沿着列 $\to$ 沿着行 $\to \dots \to$ 沿着列
+   沿着列 $\to$ 沿着行 $\to$ 沿着列 $\to \dots \to$ 沿着行

于是容易发现，这里我们要求 $m$ 一定是偶数，反之无解。

而会发现，我们的这两种路线不会同时成立，于是我们可以分开来讨论。

> 证明感觉可以感性理解，因为如果同时成立，那么我们每一次跳一定只跳两格，这与定义中的每行每列只能一个不符合，
> 
> 而又一定不会存在一种路径可以正反各走一次。

所以我们只需要先考虑第一种情况，第二种是同理的（最终答案其实乘个 $2$ 就可以了）。

这时候我们考虑把每一次变化用数学语言表示出来了，

我们假设他先往下走，那么原来在 $(A,B)$ 跳过一个 $(x,B)$ 的石头，到了 $(x+1,B)$，

这时我们再假设它往右边跳，要去跳 $(x+1,y)$ 的石头，到了 $(x+1,y+1)$。

于是就有了一个性质：发现这里的两个石头是分别在第 $x$ 行和第 $x+1$ 行，而先是跳 $x$ 行的还是 $x+1$ 行的取决于你是从上面跳下来还是从下面跳上去。

而类似分析一下，发现列也是同样有这样的性质，就是所有石子一定两两相邻！！！
  
有了这个性质似乎就可以直接用组合数计算了，枚举一下你是从左边来的还是从右边来的就可以了，

而行列其实本质相同，互相独立且互不干扰，

由于我们最后要回到 $(A,B)$，所以有些东西其实是必定的，比如在这种情况中，最后一个石头必须在 $B$ 这一列这样的。

于是其实排除掉分类讨论，其实随便排的只有 $m-2$ 组（这里我们将原来的 $m$ 除以 $2$ 来计算）。

所以具体实现中，我们枚举一下当前这种情况它左边有多少组，右边有多少组，直接组合计数就可以了。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N=2e5+5,mod=998244353;
int n,m,A,B,fac[N],inv[N];

int qpow(int a,int b){
  int res=1;
  while(b){if(b&1) res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}
  return res;
}

void init(){
  fac[0]=1;
  for(int i=1;i<N;i++) fac[i]=1ll*fac[i-1]*i%mod;
  inv[N-1]=qpow(fac[N-1],mod-2);
  for(int i=N-1;i>=1;i--) inv[i-1]=1ll*inv[i]*i%mod;
}

int binom(int n,int m){
  if(n<m||m<0) return 0;
  return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int sol(int L,int R){
  int res=0;
  for(int l=0,r;l<=m;l++){
    r=m-l;
    if(2*l>L||2*r>R) continue;
    if(l&&2*l+1<=L) res=(res+1ll*binom(L-l-1,l)*binom(R-r,r)%mod*l%mod)%mod;
    if(r&&2*r+1<=R) res=(res+1ll*binom(L-l,l)*binom(R-r-1,r)%mod*r%mod)%mod;
  }
  return 1ll*res*fac[m-1]%mod;
}

int main(){
  cin>>n>>m>>A>>B;init();
  if((m&1)||m==2) cout<<0,exit(0);
  m=(m>>1)-1;
  cout<<(1ll*sol(A-1,n-A)*sol(B-1,n-B)%mod*2ll%mod);
  return 0;
}
```

---

## 作者：eastcloud (赞：0)

[更好的阅读体验](https://www.cnblogs.com/eastcloud/p/18014180)

首先把 $m=2$ 和 $m$ 为奇数的情况判掉，由于我们要对合法的摆放方案计数，而一个摆放方案要判断合法性就必须通过一组合法的移动过程，对移动的状态进行记录以此转移和优化显然没啥前途，因此我们考虑摆放方案和移动过程之间的联系。

一个比较显然的观察是摆放方案和移动过程是一组双射，移动显然能还原唯一一组摆放，那反过来呢？我们只要考虑移动过程形成的环能不能逆着走就行，你尝试构造会发现这个摆放方案其实比较唯一而且不合法。

那接下来我们就开始对移动过程计数，同样此时也出现了一个问题：什么样的移动方案是合法的？

对白色石头的限制是任意两个白色石头都不能出现在同一行或者同一列，如果你有尝试画出路线就会发现这引出了一条对于路线的限制：跳过一个白色石头之后必然要拐弯，原因显然，也就是说我们其实是在交错横向纵向移动，这其实启发我们把两个维度拆开考虑。

而两个白色石头能出现在同一行或者同一列，我们会想去思考：那移动过程中的两个黑色石头能不能出现在同一行或者同一列？

为了引出这个这个条件，我们尝试把黑色和白色石头捆绑考虑，和一个黑色石头捆绑的那个白色石头的位置取决于黑色石头移动过来的方向，再画画图，会发现这个黑色石头再纵向移动的时候其实还带来了一个在这一列的白色石头，如果我们只看行这一位其实这个横向移动带来了在这个方向上的两个障碍，读者可以画画图自己感受一下。

也就是说，我们每次横向移动的黑色石头不能与前面的黑色石头重合，也不能和前面那个跳过的白色石头重合，但前面这个白色石头的相对位置是不确定的，这为我们计数带来了一些困难。

先整理一下情况，现有的条件要求我们对一个大概是选出若干个横坐标表示每次移动到这个坐标，然后这些坐标及其带来的附加东西不能重合，这个附加东西和坐标组成一个大小为 2 的块，然后我们要对这个东西组成的序列计数。

整理完之后就会发现其实我们只要把那一堆看做一个大小为 2 的块然后求在序列里面放这个东西不能重叠的方案数就好了，因为序列是有遍历顺序的，一个顺序就唯一确定了黑色和白色石头的相对位置，跟原本的移动路径就是双射。

最后还有一点小问题，就是我们回到最开始的那个黑色块所带来的白色块的位置是不确定的，我们枚举它，然后就要求在一行里面放下若干个长度为 2 的块，不能重叠，块有标号且最大标号的块一定在我们枚举的那个方向，组合数随便算算就行，记得最后答案乘二，因为我们不知道是先走横的还是先走竖的。

```cpp
ll solve(ll n,ll m,ll x){
	ll ans=0;
	for(ll i=0;i<m;i++){
		ans=(ans+(i*fac[m-2]%mod)*(C(x-2-i,i)*C(n-x-(m-i-1),m-i-1)%mod))%mod;
		ans=(ans+((m-i-1)*fac[m-2]%mod)*(C(x-1-i,i)*C(n-x-1-(m-i-1),m-i-1)%mod))%mod;
	}
	return ans;
}
int main(){
	ll n=read(),m=read(),a=read(),b=read();prework();
	if(m&1 || m==2){cout<<0;return 0;}
	cout<<(solve(n,m/2,a)*solve(n,m/2,b)*2)%mod;
	return 0;
}
```


---

