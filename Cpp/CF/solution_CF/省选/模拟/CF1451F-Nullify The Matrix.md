# Nullify The Matrix

## 题目描述

Jeel and Ashish play a game on an $ n \times m $ matrix. The rows are numbered $ 1 $ to $ n $ from top to bottom and the columns are numbered $ 1 $ to $ m $ from left to right. They play turn by turn. Ashish goes first.

Initially, each cell of the matrix contains a non-negative integer. Each turn, a player must perform all of the following actions in order.

- Choose a starting cell $ (r_1, c_1) $ with non-zero value.
- Choose a finishing cell $ (r_2, c_2) $ such that $ r_1 \leq r_2 $ and $ c_1 \leq c_2 $ .
- Decrease the value of the starting cell by some positive non-zero integer.
- Pick any of the shortest paths between the two cells and either increase, decrease or leave the values of cells on this path unchanged. Note that: 
  - a shortest path is one that passes through the least number of cells;
  - all cells on this path excluding the starting cell, but the finishing cell may be modified;
  - the resulting value of each cell must be a non-negative integer;
  - the cells are modified independently and not necessarily by the same value.

If the starting and ending cells are the same, then as per the rules, the value of the cell is decreased. No other operations are performed.

The game ends when all the values become zero. The player who is unable to make a move loses. It can be shown that the game will end in a finite number of moves if both players play optimally.

Given the initial matrix, if both players play optimally, can you predict who will win?

## 说明/提示

In the first test case, the only cell of the matrix is 0. There are no moves Ashish can make. Jeel is the winner.

In the second test case, Ashish can choose $ (r_1, c_1) = (r_2, c_2) = (1,3) $ and reduce the cell to $ 0 $ , leaving $ [0, 0, 0] $ . Jeel cannot perform any moves. Ashish wins.

## 样例 #1

### 输入

```
4
1 1
0
1 3
0 0 5
2 2
0 1
1 0
3 3
1 2 3
4 5 6
7 8 9```

### 输出

```
Jeel
Ashish
Jeel
Ashish```

# 题解

## 作者：Demoe (赞：12)

### [题目传送门](https://www.luogu.com.cn/problem/CF1451F)

## 题意

- 给定一个矩阵。

- 每次操作选定一个初位，一个末位。初位需减去一个正数。

- 可选定初位到末位的一个最短路径，可对其中除初位以外的所有位置进行任意放缩。（不可缩至负数）

- 最终局面为所有位全归零。

- 问如果两人都很聪明，先手胜还是后手胜。

#### 题外话（

本来这场上 M 挺开心的。（

然后发现 F 不难还没开，早上花了 $\text{30 min}$ 解决了。

人都傻了。

## Sol

定义 $line_x$ 为行列和为 $x$ 的点的集合，即一条斜线。

考虑一个最短路径，初位 $(r_1,c_1)$ 末位 $(r_2,c_2)$。

它会对 $line_x (r_1+c_1\le x\le r_2+c_2)$ 造成影响。

考虑到本题将第二个操作删去后即为 $\text{Nim}$ 板子，我们考虑 $\text{XOR}$。

---

类似 [CF1149E](https://www.luogu.com.cn/problem/CF1149E) 的，我们将 $line_x$ 分为一组，记录其元素的 $\text{XOR}$ 值，令其为 $sum_x$。

对于任一个 $sum_x$，我们对它进行分析。

考虑到目标状态为 $\forall x,sum_x=0$，我们考虑将 $\exists x,sum_x>0$ 的局面转换为目标状态。

---

对于第一个 $sum_x>0$，我们考虑将其变为 $0$。

考虑到初位取在 $line_x$ 上，我们只能对某一元素进行减操作。

那么取 $line_x$ 中的一个元素满足其二进制中 $sum_x$ 二进制最高 $1$ 位上为 $1$，操作其即可。

考虑为什么选该元素。

发现我们要让 $s \oplus sum_x<s$，发现减去 $\sum_x$ 二进制最高位后必减小。

显然存在这样的元素。（不然 $sum_x$ 的那一位咋来的）

---

考虑后面的 $sum_x$，我们可以任意操作一个数，所以容易让所有 $sum_x \to 0$

---

对于一个 $\forall x,sum_x=0$ 的局面，显然再做一次操作又会返回 $\exists x,sum_x>0$。

即可以两种局面反复横跳。（

考虑为什么这样是最优策略。

若当前局面为 $\forall x,sum_x=0$，那么此时通过反复横跳的操作，后手必胜。

若当前局面为 $\exists x,sum_x>0$，先手有办法将局面转换为 $\forall x,sum_x=0$，从而先手必胜。

可能会考虑到这样是否会结束游戏，甚至一直结束不了了。

>It can be shown that the game will end in a finite number of moves if both players play optimally.

题目说可以咱就可以吧。（

那么对于初局每个 $line_x$ 判断 $sum_x=0$ 即可。

#### $Code$

```cpp
// wish to get better qwq

#include<bits/stdc++.h>
#define re register int
#define pb push_back

using namespace std;
typedef long long ll;

template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}

// ---------- IO ---------- //

const int N=105;
int T,n,m,sum[N<<1],ans;

// ---------- XOR ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(T);
	while(T--){
		rd(n);rd(m);int qaq;
		memset(sum,0,sizeof(sum));
		for(re i=1;i<=n;i++)
			for(re j=1,x;j<=m;j++) rd(x),sum[i+j]^=x;
		for(qaq=2;qaq<=n+m;qaq++) if(sum[qaq]){puts("Ashish");break;}
		if(qaq==n+m+1) puts("Jeel");
	}
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：liangbowen (赞：5)

[problem](https://www.luogu.com.cn/problem/CF1451F) & [blog](https://www.cnblogs.com/liangbowen/p/17533595.html)。

这题原本的题解满是废话，让我写一篇（

---

这边直接给结论了。令 $val_p = \oplus_{x+y=p}\ a_{x,y}$，设 $S=\Big[\normalsize \forall val_i=0\Big]$，当 $S=\text{true}$ 时，后手必胜；否则先手必胜。

证明也是典中典。证两个条件即可。

+ 证明 $\forall S \Rightarrow \neg S$：起点那里强制操作，并且你无法从 $(x,y)\to(s,t) (s<x \vee t<y)$，所以起点那一斜行的 $\oplus a_{x,y}$ 是不可能维持 $0$ 了。
+ 证明 $\exists \neg S \Rightarrow S$：找到最小的 $i$ 满足 $val_i\ne 0$，它对应的斜行是 $i$。取这一斜行**二进制最高位**所在的那个 $a_{x,y}$ 作为起点，终点取右下角。
  + 对于起点：$a_{x,y}\gets(a_{x,y}\oplus val_i)$ 显然可以使 $val_{i}'=0$。由于 $a_{x,y}$ 最高位在手，必定有 $a_{x,y}\ge(a_{x,y}\oplus val_i)$。
  + 对于路径上的其他斜行：由于可以加，直接变成 $(a_{i,j}\oplus val_{i+j})$ 当然有正确性。

注意到先手必输态（全为 $0$）对应 $S=\text{true}$，也就有了一开始的结论。综上我们完成证明。

[代码](https://codeforces.com/contest/1451/submission/212399409)，时间复杂度 $O(Tnm)$。

---

## 作者：Cutest_Junior (赞：4)

## CF1451F 【Nullify The Matrix】

### 题意

+ $n\times m$ 的棋盘，每个点有非负权值 $a$；
+ Ashish 和 Jeel 轮流操作，Ashish 先手；
+ 每次选两个坐标，$(x_1,y_1),(x_2,y_2)$，需保证 $x_1\le x_2,y_1\le y_2,a_{x_1,y_1}>0$，把 $a_{x_1,y_1}$ 减去一个正整数（保证它还是非负整数），选一条 $(x_1,y_1)$ 到 $(x_2,y_2)$ 最短路径（包括 $(x_2,y_2)$，不包括 $(x_1,y_1)$，为同一点则不操作），路径上每一点可以改为任意非负整数（可以不改）；
+ 不能操作者输；
+ $n,m\le100,a\le10^6$。

### 做法

定义第 $x$ 个斜列表示所有横纵坐标和为 $x$ 的点集，点集内所有点异或和记为 $sum_x$。

$SG$ 函数等于 $0$ 当且仅当所有 $sum_x$ 均等于 $0$。

证明：
1. 最终状态即全零时 $SG$ 函数等于 $0$；
2. $SG$ 函数等于 $0$ 时操作一次后，$SG$ 函数一定不为 $0$，因为 $sum_{x_1+y_1}$ 一定会改变；
3. $SG$ 函数不为 $0$ 时，一定能找到一种操作使操作后 $SG$ 函数等于 $0$，对于最小的 $x$ 使 $sum_x\neq0$，设 $sum_x$ 在二进制下最高位为 第 $d$ 位，一定存在 $a_{i,j}$ 使 $i+j=x$ 且 $a_{i,j}$ 的二进制第 $d$ 位为 $1$，这时候让 $a_{i,j}$ 异或 $sum_x$，$a_{i,j}$ 一定变小，且 $sum_x$ 此时变为 $0$，而通过改变路径上的点也很容易使后面的 $sum$ 均变为 $0$，至此，便构造出一种使 $SG$ 函数等于 $0$ 的方案。

---

## 作者：baka24 (赞：1)

首先，观察题目有什么比较好的性质。

规则规定全部变成 $0$ 游戏就结束了，可以联想到 $SG$ 函数。

那么我们希望找到一种 $SG$ 函数的构造，使得不为 $0$ 的状态可以通过一步操作变成 $0$，为 $0$ 的状态无论怎么操作都变不成 $0$。

从后者入手，每次修改除了起点以外都可以随意更改甚至不更改。如果我们希望起点的修改会使 $SG=0$ 的状态后继一定不为 $0$，那么不应该有任何其他数的修改可以修正起点的修改。

略微抽象，举个失败的 $SG$ 构造的例子。

比如，我们定义 $SG(S)$ 为 $S$ 状态每一行异或和或在一起。

那么当 $SG(S)=0$ 时，玩家可以选择任意一个不为 $0$ 的点作为起点，之后通过修改它其中一条最短路上同行的一个点，使这一行的异或和依然是 $0$。

于是，这个构造不符合我们所期望的性质。

那么它不好在哪里？因为玩家可以修改能够抵消起点修改的某个值，上例中它是和起点同行的某个最短路上的数。

什么是最短路上的所有点都影响不到的关键字呢？

注意到 $(x,y)$ 到 $(n,m)$ 最短路上的点都可以表示为 $(x+a,y+b)$，其中 $a+b>0$。

也就是说，最短路上每个点的 $x+y$ 一定和起点不同！

我们定义 $SG$ 函数为每条斜线的异或和或起来。

当 $SG$ 为 $0$ 仅当每个斜线异或和均为 $0$，在一次修改中只能修改起点所在斜线一个点且一定发生改变，此时 $SG$ 一定不为 $0$。

那么如何操作使任意 $SG(S)\ne 0$ 的 $S$ 变成 $0$？

首先，起点一定在 $x+y$ 最小且异或和不为 $0$ 的斜线上，根据 Nim 游戏的结论，可以知道我们一定可以选出一个点这条斜线异或和变成 $0$。

同时，这条斜线之后的斜线上一定有处于最短路上的点，修改这些点使这些斜线异或和为 $0$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;if(c==EOF)return -1;c=getchar();}while(c<='9'&&c>='0')x=x*10+c-'0',c=getchar();return x*f;}
const int MAXN=210;
int n,m,k,ans,sg[MAXN];
void slv(){
    n=read(),m=read();k=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)sg[i+j]^=read();
    for(int i=1;i<=n+m;i++)k|=sg[i],sg[i]=0;
    printf("%s\n",k?"Ashish":"Jeel");
}
signed main(){
 	freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    int _=read();while(_--)
    slv();
    return 0;
}
```

---

## 作者：_lxy_ (赞：1)

### 分析

定义 $line_i$ 为点 $(x,i-x)$ 组成的一条斜线， $sum_i$ 为 $line_i$ 的异或和。

设状态：
$$
\begin{aligned}
  &S: \forall i,sum_i=0 \\
                 &S':\exists i,sum_i \neq 0
\end{aligned}
$$
结论：若初始时状态为 $S$，则后手必胜。

证明：

引理一：$S$ 状态下，任何操作都会使状态变为 $S'$。

证明：选择任意一个最短路径都需要减少起始点的值，而减少后所在斜线的异或和必然会发生改变，不能保持为 $0$，此时状态变为 $S'$。

引理二：$S'$ 状态下，一定存在至少一个操作使得状态变为 $S$。

证明：对于最小的 $x$ 使得 $sum_x \neq 0$，$line_x$ 上一定有 $a_{i,j}$ 满足 $a_{i,j}$ 的二进制下其 $sum_x$ 最高位对应的位为 $1$，因为 $sum_x$ 是异或得到的，一定有 $a_{i,j}$ 的那一位为 $1$ 才能保证异或后不会因为都是 $0$ 而导致异或和该位为 $0$。因此，可以让点 $(i,j)$ 作为起始点，因为行列和更小的无需修改，并让 $a_{i,j} \leftarrow a_{i,j} \oplus sum_x$ 使其异或和变为 $0$，此时 $a_{i,j}$ 必然减小，然后通过改变路径上的其他点就能使其它的 $sum$ 变为 $0$，此时状态变为 $S$。

根据引理一和引理二，且由于最终局面为 $S$ 状态，局面一定是在 $S$ 和 $S'$ 之间反复切换的，所以结论得证。

### 核心代码

```cpp
while(T--)
{
    mem(sum,0);
    qread(n,m);for(i=0;i<n;i++) for(j=0;j<m;j++) qread(a[i][j]),sum[i+j]^=a[i][j];
    for(i=0;i<=n+m-2;i++) if(sum[i]) goto label;
    printf("Jeel\n");continue;
    label:;printf("Ashish\n");
}
```


---

