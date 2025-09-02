# New Game with a Chess Piece

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Petya and Vasya are inventing a new game that requires a rectangular board and one chess piece. At the beginning of the game the piece stands in the upper-left corner of the board. Two players move the piece in turns. Each turn the chess piece can be moved either one square to the right or one square down or jump $ k $ squares diagonally down and to the right. The player who can’t move the piece loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF36D/6de962072be4a9388ec093a95ba4343538d648ef.png)The guys haven’t yet thought what to call the game or the best size of the board for it. Your task is to write a program that can determine the outcome of the game depending on the board size.

## 样例 #1

### 输入

```
10 2
1 1
1 2
2 1
2 2
1 3
2 3
3 1
3 2
3 3
4 3
```

### 输出

```
-
+
+
-
-
+
-
+
+
+
```

# 题解

## 作者：A_Pikachu (赞：11)

### [题目传送门](https://www.luogu.com.cn/problem/CF36D)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-jie-cf36d-new-game-with-a-chess-piece)）

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

这里是人话理解题目：在一个 $n \times m$ 的棋盘上，$(1,1)$ 的位置有一个棋子，这个棋子每次能往下走一格或往右走一格或往右下移动 $k$ 格，每次移动不能超出棋盘，如果棋子恰好移动到 $(n,m)$ 则移动的人赢，问你如果你先手（先移动），你是否有必胜策略。

不难想，当 $n,m$ 比较小时，我们能够用简单的有向无环图解决，但这里 $1 \leq n,m \leq 10^{9}$，所以这题就变成了一道博弈论的题目。

现在已知 $n,m,k$，我们不妨设 $f\ (\ i\ ,\ j\ )$ 表示当棋子在 $(\ i\ ,\ j\ )$ 时，先手是否能获胜，特别地，$f\ (\ 1\ ,\ 1\ )=0$。那么根据我们的定义，$f\ (\ i\ ,\ j\ )=\neg\ \Big(\ f\ (\ i-1\ ,\ j\ )\ \land\ f\ (\ i\ ,\ j-1\ )\ \land\ f\ (\ i-k\ ,\ j-k\ )\ \Big)$，而且超出棋盘外的地方不会参与运算。

那么我们现在就来分析 $f\ (\ n\ ,\ m\ )$ 的规律。很容易发现，在第一行或第一列时，能够影响这个点的值只有第一行的上一列或第一列的上一行，又已知 $f\ (\ 1\ ,\ 1\ )=0$ ，所以第一行和第一列的 $f$ 值均是 $0,1$ 交替出现的。接下来 $k-1$ 行和 $k-1$ 列，由于 $f\ (\ i\ ,\ j\ )$ 不受 $f\ (\ i-k\ ,\ j-k\ )$ 的影响，所以$f\ (\ i\ ,\ j\ )=\neg\ \Big(\ f\ (\ i-1\ ,\ j\ )\ \land\ f\ (\ i\ ,\ j-1\ )\ \Big)$，又由于第一行和第一列的值是 $0,1$ 交替出现的，所以前 $k$ 行和前 $k$ 列均是 $0,1$ 交替的。如下是 $k=3$ 时的 $f$ 值：

$\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1$

$\ 1\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1\ 0$

$\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1$

$\ 1\ 0\ 1\ \ddots\ \ddots\ \ddots$

$\ 0\ 1\ 0\ \ddots\ \ddots\ \ddots$

$\ 1\ 0\ 1\ \ddots\ \ddots\ \ddots$

通过上表可知，在第 $k+1$ 行的第 $k$ 列及 $k+1$ 列的第 $k$ 行后的每个数均为 $1$，即均能获胜。因为在第 $k+1$ 行第 $i$ 列或在第 $k+1$ 列第 $i$ 行时，若 $(i-k)\equiv 1\pmod 2$ 则第 $1$ 行第 $i-k$ 列或第 $i-k$ 行第 $1$ 列一定为 $0$，反之，第 $k-1$ 行第 $i$ 列或第 $i$ 行第 $k-1$ 列一定为 $0$。于是，就填出了下表：

$\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1$

$\ 1\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1\ 0$

$\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1\ 0\ 1$

$\ 1\ 0\ 1\ 1\ 1\ 1\ 1\ 1\ 1\ 1$

$\ 0\ 1\ 0\ 1\ \ddots\ \ddots\ \ddots$

$\ 1\ 0\ 1\ 1\ \ddots\ \ddots\ \ddots$

再往下填 $k$ 行和 $k$ 列时，发现 $\ f\ (\ i\ ,\ j\ )=\neg \ f\ (\ i-k-1\ ,\ j-k-1\ )$， ~~（具体证明略，）~~ 自然，再往下填 $1$ 行 $1$ 列时，这 $1$ 行 $1$ 列均为 $1$。需要注意的情况是在第 $n \times (k+1)$ 行第 $m$ 列时，若 $m < n \times (k+1)$，则其满足的情况为 $0,1$ 交替。

而且不难发现，$f$ 的值具有对称型，所以 $f\ (\ n\ ,\ m\ )=f\ (\ m\ ,\ n\ )$，这对于需要特别判断大小的情况比较方便。

然后要注意的是当 $k=1$ 时，需要特判（因为这时不满足 $\ f\ (\ i\ ,\ j\ )=\neg \ f\ (\ i-k-1\ ,\ j-k-1\ )$ 的性质）。

$\Large\mathscr{Part\,\,2\;\;}\text{Code}$

没什么好说的，唯一要注意的是要注意文件输入输出（虽然你谷上没有但CF上有）。

```cpp
#include <cstdio>
int t,k,n,m,div;
void swap(int &a,int &b){a^=b^=a^=b;}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&t,&k);
	while(t--){
		scanf("%d%d",&n,&m);
		if(k==1){ //特判 k=1 时的情况
			printf("%c\n",((n&1)&(m&1)?'-':'+'));
			continue;
		}
		if(n<m) swap(n,m); //n 一定大于等于 m
		div=m/(k+1); //选择小的数作商
		n-=(k+1)*div; m-=(k+1)*div; //把式子化简
		if(m==0) printf("+\n"); //唯一情况即同行或同列有必胜策略
		else printf("%c\n",((n&1)^(m&1))^(div&1)?'+':'-'); //判断是否有必胜策略 
	}
	return 0;
}
```

福利：[$\color{green}{AC}$](https://www.luogu.com.cn/record/33056287)后别忘了去领[双倍经验](https://www.luogu.com.cn/problem/SP7602)！

---

## 作者：mcDinic (赞：5)

[更好的体验](https://www.cnblogs.com/mcDinic/p/17654184.html)

## 前言：

~~都大半年没在洛谷上提交过题解了。~~

SPOJ 上有双倍经验，题号为 SP7602。

我看题解区的大佬们都是打表的，但是感觉只讲了打表可以得 XXX，没有讲得很形象，这篇题解将**生动讲述做法**，从打表前的转移方程到打完表后的分析都会很具体。

## 正文：

### Step 1：基本解法（打表找规律）

为了方便起见，我们不妨令 $n \le m$，显然交换 $n,m$ 对答案无影响。

令 $b_{i,j}$ 表示从第 $i$ 行第 $j$ 列出发，是胜还是败。如果胜，$b_{i,j}=1$，否则 $b_{i,j}=0$。

我们**先不考虑**越界的问题，如果 $b_{i+1,j},b_{i,j+1},b_{i+k,j+k}$ 中至少有一个为零（具体意义就是，从第 $i$ 行第 $j$ 列出发可以走到一个对手会败的位置），那么 $b_{i,j}=1$，否则 $b_{i,j}=0$。

也就是说，$b_{i,j}=\lnot(b_{i+1,j} \bigwedge b_{i,j+1} \bigwedge b_{i+k,j+k})$。

状态转移时，如果越界的话，那么那个越界的值就不参与运算，所以为了方便起见，可以设它为 1.

附上[打表程序](https://www.luogu.com.cn/paste/iuzpyzhj)

为了直观，我先放一张表来给大家解释（洛谷的加颜色会使每位数字占的宽不同，比较难弄，我就把自己的表传到图床了）：

![](https://cdn.luogu.com.cn/upload/image_hosting/e6ald46h.png)

我们发现整个图被红色标记的反 L 形给切割成若干段，每段里面都是 0，1 交替的矩阵，特殊的就是这几个反 L 形，全是 1。

由于我们要求的是 $b_{1,1}$ 的值，所以只需考虑起始点是否在反 L 形里。

如果在**就需要特判**，这个反 L 形会浓缩成一个宽为 1 的矩形（因为它不可能向上延伸了），而每两个反 L 形间从行看，夹了 $k$ 行，从列看，夹了 $k$ 列。所以无论从行列看，都可以当作 $k+1$ 行（或列）为一个周期，那么当且仅当 $n$ 为 $k+1$ 的倍数，起始点在反 L 形内，此时 $b_{1,1}=1$。

如果不在：我们观察一下上表中蓝色标记的数，也就是每个反 L 形围成的矩形的右下角，以及整个图形的右下角。注意到了吗，它们是 0,1 交替的，所以我们可以通过反 L 形的个数，判断最里层矩阵右下角位于哪一行（记为第 $x$ 行）和哪一列（记为第 $y$ 列），以及它对应的数（记为 $z$）。考虑从起始点走到该点需要走 $x+y-2$ 步（因为是最里层的矩形，向右下角走就走出该矩形了，不能到达该矩阵右下角），所以我们只需判断 $x+y-2$ 的奇偶性，就能知道 $b_{1,1}$ 是否与 $z$ 相同。

那么现在这题就做完了，提交一下——我们发现在第 13 个点寄掉了，这是什么原因呢？

考虑一下 $k=1$ 的时候，每个蓝色标记的位置无伦选用三种走法的哪一种，都会走到 1 的位置，此时每个蓝色标记的数就都为 0，**这个需要特判**。

~~现在是真的做完了。~~

### Step 2：Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define linf 0x3f3f3f3f3f3f3f3f
#define inf 0x7fffffff
#define v e[i].y
using namespace std;
inline ll read(){
    char ch=getchar();ll x=0,w=1;
    while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
inline void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x<10){putchar(48+x);return;}
    write(x/10),putchar(x%10+48);
}
ll T,n,m,K,sx,s,sy;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    T=read(),K=read();
    while(T--){
        bool w;
        n=read(),m=read();
        if(n>m)swap(n,m);
        s=n/(K+1),sx=n-s*(K+1),sy=m-s*(K+1);//s代表“1围成的反L形”的个数
        if(sx==0)w=1;
        else{
            if(K==1)w=0;//特判
            else w=s&1;
            if((sx+sy)&1)w^=1;
        }
        printf(w?"+\n":"-\n");
    }
    return 0;
}
```


---

## 作者：VinstaG173 (赞：5)

这道题挺有趣的。

多列几个表（手算），发现规律：当$N,M$大于$2K+2$时与$N \bmod 2K+2,M \bmod 2K+2$胜负情况是一样的。

显然$M,N$互换是一样的。考虑$M \ge N,N \le 2K+2$的情况。

此时如果$N=K+1$或$2K+2$，容易发现全是必胜情况。

如果$N<K+1$，那么$M-N$为偶数时必败，否则必胜。

其他情况$M-N$为奇数时必败，否则必胜。

然后就出代码了（这题要文件输入输出，我当时没有看到CF上一行小字卡了好久）

Code:

```cpp
#include<cstdio>
int T,N,M,K,L;
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf(" %d %d",&T,&K);
    while(T--)
    {
        scanf(" %d %d",&N,&M);
        if(K==1)
        {
            printf("%c\n",((N&1)&(M&1))?'-':'+');
            continue;
        }
        (N>M)&&(L=N,N=M,M=L);
        L=N-((N-1)%(2*K+2)+1);
        N-=L,M-=L;
        L=M-N;
        if(N<=K)printf("%c\n",(L&1)?'+':'-');
        else if(N==K+1||N==2*K+2)printf("+\n");
        else printf("%c\n",(L&1)?'-':'+');
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## CF36D

### 题意

大小为 $n\times m$ 的棋盘，两人轮流移动棋子。每一次移动，棋子可以向右移动一格，或者向下移动一格，或者斜向下和向右移动 $k$ 格，直到不能移动棋子的一方输掉。他们还没想好该怎么称呼这个游戏，也没想好棋盘的最佳尺寸。你的任务是编写一个程序，根据棋盘大小求出游戏的结果。

### 标签

博弈论

### 做法

首先考虑 $k \ge 2$ 的情况。

令 $f_{n, m}$ 表示在 $n\times m$ 的棋盘上先手是否必胜，先手必胜就为 $1$，否则为 $0$。由题意知 $n \times m$ 的棋盘可以由一步操作转化为 $(n - 1) \times m$，$n \times (m - 1)$，$(n - k) \times (m - k)$ 的棋盘，于是有 $f_{n, m} = 1 - \min\{f_{n - 1, m}, f_{n, m - 1}, f_{n - k, m - k}\}$。

不妨设 $n \le m$。

首先考虑 $n \le k$ 的情况，这种情况因为 $n - k \le 0$ 是无法使用第三种转移到 $(n - k) \times (m - k)$ 的，于是只考虑前两项，即 $f_{n, m} = 1 - \min\{f_{n - 1, m}, f_{n, m - 1}\}$。由初始条件为 $f_{1, 1} = 0$ 易得 $f_{n, m} = (n + m) \bmod 2$。

接下来观察 $n = k + 1$ 的情况。发现如果此时 $m \equiv k \pmod 2$，$f_{n - 1, m} = (n - 1 + m) \pmod 2 = (k + k)\pmod 2 = 0$，所以可以转移至 $(n - 1) \times m$ 取得胜利，所以 $f_{n, m} = 1$。否则有 $m \equiv k + 1 \pmod 2$，则由 $f_{n - k, m - k} = (n - k + m - k) \pmod 2 = (1 + k + 1 - k) \pmod 2 = 0$ 知 $f_{n, m} = 1$。

然后观察 $k + 1 < n < 2k + 2$ 的情况。注意到对于任意 $n \ge k + 1, m \ge k + 1$ 的 $n$ 和 $m$ 都有 $f_{k + 1, m} = f_{n, k + 1}$，因此 $f_{n, m} = 1 - \min\{f_{n - 1, m}, f_{n, m - 1}, f_{n - k, m - k}\}$。 中的 $f_{n - 1, m}, f_{n, m - 1}$ 是不受第一种情况范围内的值的影响的，只是初始值从第一种情况的 $0$ 变成了 $1$。不过还有 $f_{n - k, m - k}$ 的一项，因此能够得到 $f_{n, m} = 1 - \min\{f_{n, m - 1}, f_{n - 1, m}, f_{n - k, m - k}\} = 1 - \min\{f_{n, m - 1}, f_{n - 1, m}, ((n - k) + (m - k)) \bmod 2\}$。因此有 $f_{k + 2, k + 2} = 1$，而且有 $((n - k) + (m - k)) \bmod 2 = f_{n, m - 1} = f_{n - 1, m}$，因此 $f_{n, m} = (n + m + 1) \bmod 2$，即 $f_{n, m} = 1 - f_{n - (k + 1), m - (k + 1)}$。

对于剩余的情况，同理有 $k + 1 \nmid n$ 时 $f_{n, m} = 1 - f_{n - (k + 1), m - (k + 1)}$，于是就求得了在 $k \ge 2$ 的情况下的答案，即如果 $k + 1 | n$ 就有 $f_{n, m} = 1$，否则 $f_{n, m} \equiv n + m + \lfloor\frac n {k + 1}\rfloor \pmod 2$。

考虑 $k = 1$ 的情况，与 $k \ge 2$ 的情况不同点就是 $k + 1 \nmid n$ 时的 $(n, m)$ 无法从 $(n - k, m - k)$ 转移过来了，因为 $k + 1 \nmid n$ 时就会有 $f_{n - k, m - k} = 1$，对 $f_{n, m}$ 无影响，所以不会有第二个范围内的答案与第一个范围内的答案相反的情况。特判掉即可。

### 代码

```cpp
#include <stdio.h>
int t, k, n, m;
int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d", &t, &k);
	for (; t --; ) {
		scanf("%d%d", &n, &m);
		if (n > m) n ^= m ^= n ^= m;
		puts(((!(n % (k + 1))) || (((n + m) & 1) ^ (k == 1 ? 0 : ((n / (k + 1)) & 1)))) ? "+" : "-");
	}
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

~~这种题一看就是[打表](https://www.luogu.com.cn/paste/x5khu360)找规律啊（打表程序见剪切板）。~~

本题如果想正经找规律的话，对于每一个 $n$ 和 $m$ 都做一遍是很麻烦的，考虑用 $f_{n,m}$ 表示该大小的棋盘是先手必胜还是后手必胜。

显然，$f_{1,1}$ 是必败的。对于每一个 $f_{n,m}$ 如果 $f_{n-1,m}$，$f_{n,m-1}$ 或者 $f_{n-k,m-k}$ 中有任意一个是必败的，那么做出相应的决策就是必胜的了。形式化地，有：$f_{n,m}=(\lnot f_{n-1,m})\lor (\lnot f_{n,m-1})\lor (\lnot f_{n-k,m-k})$。

可以发现（建议配合表理解），当 $n$ 和 $m$ 之中有一个比较小的时候，$f_{n,m}=[\text{n,m 奇偶性不同}]$，这个小的界限在 $[1,k]$。然后再大一点，就出现了全是 $1$ 的区域，再大又是 $0$ 和 $1$ 相间排布，但此时 $f_{n,m}=[\text{n,m 奇偶性相同}]$ 也就是 $\lnot f_{n-k-1,m-k-1}$，然后再出现一个全是 $1$ 的区域。这四者构成一个循环节，长度为 $2k+2$。

这样分布的原因是比较显然的，一开始只能向一个方向移动一步，后来出现了一个额外的决策点，本着能走到 $0$ 就走 $0$ 的方针，这一行或列都是 $1$，然后下一行和列失去了一个单向移动的决策方案，于是恰好和之前的那一部分相反。以此类推。

讲一个棋盘转一下不会有任何变化，所以交换 $n$ 和 $m$ 不会有任何影响。

----
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,k,n,m;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&T,&k);
	while(T--){
		scanf("%d%d",&n,&m);
		if(k==1){
			if((n&1)&(m&1)==1)printf("-\n");
			else printf("+\n");
			continue;
		}
		if(n>m)swap(n,m);
		int del=n-(n-1)%(2*k+2)-1;
		n-=del;m-=del;
		if(n<=k){
			if((n&1)!=(m&1))printf("+\n");
			else printf("-\n");
			continue;
		}
		if(n==k+1||n==2*k+2){
			printf("+\n");
			continue;
		}
		if((n&1)==(m&1))printf("+\n");
		else printf("-\n");
	}
	return 0;
}
```


---

