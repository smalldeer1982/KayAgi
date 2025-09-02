# Grid Game 2

## 题目描述

You are playing "Grid Game 2" with your friend. There is a grid with $ 10^9 $ rows (numbered from $ 1 $ to $ 10^9 $ ) and $ 10^9 $ columns (numbered from $ 1 $ to $ 10^9 $ ). The cell at row $ r $ and column $ c $ is denoted as $ (r, c) $ .

Each cell can have a colour of either black or white. Initially, there are exactly $ N $ black cells (numbered from $ 1 $ to $ N $ ). Black cell $ i $ is located at $ (R_i, C_i) $ . The rest of the cells are white.

You and your friend will alternately take turn playing on this grid, and you are playing in the first turn. In one turn, a player will choose a black cell $ (r, c) $ , then toggle cells $ (r - x, c - y) $ for all $ 0 \leq x, y < \min(r, c) $ . If a cell is toggled, then the cell becomes black if it was a white cell, and the cell becomes white if it was a black cell.

For example, the following illustration shows how the grid changes after a player chooses a black cell $ (5, 4) $ in their turn.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/e2fd54c73d9615e1033b8dd1a01d70086e6fa600.png)A player who is unable to play on their turn, i.e. no remaining black cells, loses the game, and the opposing player wins the game. If you and your friend are playing optimally, determine who will win the game.

## 说明/提示

Explanation for the sample input/output #1

You can start your move by choosing $ (2, 4) $ , whose effect was demonstrated in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/2b04f438065762fd04c672bc2aeca49fdf0ed64a.png)The remaining black cells are $ (1, 3) $ and $ (1, 4) $ , each of which will only toggle itself when chosen. Whichever your friend chooses on the next move, the you can choose the remaining black cell.

Explanation for the sample input/output #2

You have only one cell to choose, and will toggle cells $ (1, 1) $ , $ (1, 2) $ , $ (2, 1) $ , and $ (2, 2) $ . Your friend and you will alternately choose the remaining black cells with your friend choosing the last black cell.

## 样例 #1

### 输入

```
2
2 3
2 4```

### 输出

```
FIRST```

## 样例 #2

### 输入

```
1
2 2```

### 输出

```
SECOND```

## 样例 #3

### 输入

```
13
1 1
1 4
1 5
2 1
2 4
2 5
4 1
4 2
4 4
5 1
5 2
5 4
5 5```

### 输出

```
SECOND```

# 题解

## 作者：EnofTaiPeople (赞：6)

首先观察博弈过程的规律。

如果你对 $(x,y)$ 操作，$\min\{x,y\}=1$，那么只会影响到自己（一个点），考虑设 $f_{x,y}$ 表示对 $(x,y)$ 操作影响到的点的次数的**奇偶性**，此时 $f_{x,y}=1$。

对于更一般的情况，一个点的 $f$ 值为所有后继影响到的点的权值加上当次操作，即 $f_{x,y}=\oplus_{i=0}^{\min\{x,y\}}\oplus_{j=0}^{\min\{x,y\}}[ij\ne0]f_{x-i,y-j}\oplus1$。

这个东西看着很有规律的样子，不过打一个表发现并没有什么规律。

考虑直接把规律推出来，因为 $f_{x,y}=f_{y,x}$，不妨设 $x\le y$，对于点 $(x,y)$，有 $\oplus_{i=0}^{x}\oplus_{j=0}^{x}f_{x-i,y-j}=1$，设 $g_{x,y}=\oplus_{i=1}^{x}\oplus_{j=1}^{y}f_{x,y}$，则有 $g_{x,y}=g_{x,y-x}\oplus1$。

这样我们可以很轻易地得出 $g_{x,y}$ 存在类似 $\gcd$ 的递推关系，$O(\log V)$ 直接递归计算即可。

有了 $g$ 可以直接差分出 $f$，而答案只与 $\oplus_{i=1}^nf_{x_i,y_i}$ 有关。

```cpp
int T,n,ans;
void sol(int x,int y){
    while(x&&y){
        if(x>y)swap(x,y);
        y%=(x+x);
        if(y>=x)ans^=1,y-=x;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z,v;
    for(cin>>T;T--;){
        cin>>x>>y;
        sol(x,y),sol(x-1,y-1);
        sol(x-1,y),sol(x,y-1);
    }
    puts(ans?"FIRST":"SECOND");
    return 0;
}
```

---

## 作者：Mars_Dingdang (赞：1)

每日一题。

博弈论题，考虑求 SG 函数。不妨设 $i\le j$，则位置 $(i,j)$ 有黑点的后继状态是位置 $\{(x,y)|1\le x\le i,1\le y\le j\}$ 除去 $(i,j)$ 本身之外均为黑，因此 $\text{SG}(i,j)=\text{mex}\{\bigoplus_{x,y} \text{SG}(x,y)\}$。边界为 $\text{SG}(1,i)=1$。

显然可以通过归纳证明，任意的 $\text{SG}(i,j)\in\{0,1\}$，则有 $\text{SG}(i,j)=\left(\displaystyle\bigoplus_{x,y} \text{SG}(x,y)\right)\oplus 1$。考虑如何快速求出 $\text{SG}(i,j)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/bqfug410.png)

我们发现，求 $\text{SG}(i,j)$ 相当于求一个区域的异或和，自然地想到记录二维前缀和 $S(i,j)=\displaystyle \sum_{x=1}^i \sum_{y=1}^j \text{SG}(x,y)$，则有 
$$\text{SG}(i,j)=\left(\displaystyle\bigoplus_{x,y} \text{SG}(x,y)\right)\oplus 1=S(i,j)\oplus \text{SG}(i,j)\oplus S(i,j-i)\oplus 1$$

两边同时异或 $\text{SG}(i,j)$ 可得 $S(i,j)=S(i,j-i)\oplus 1$。

这个式子对于值域 $10^9$ 显然应该辗转相除，根据 $\lfloor\dfrac j i\rfloor$ 奇偶性决定是否再异或 $1$。

其边界条件在于 $i|j$ 的情况。注意到每个 $i\times i$ 的正方形的异或和：记黑色区域异或和为 $x$，$\text{SG}(i,j)=y$，则 $y=x\oplus 1$，即 $x\oplus y=1$，也就是说每个 $i\times i$ 的区域的异或和一定为 $1$。那么 $i|j$ 的情况也可以根据 $\dfrac j i$ 的奇偶性判断即可。

综上，当 $i|j$ 时 $S(i,j)=\dfrac j i\bmod 2$，否则 $S(i,j)=S(i,j\bmod i)\oplus (\lfloor\dfrac j i\rfloor\bmod 2)$。知道了二维前缀和可以很快地求出 $\text{SG}(i,j)$，将整个局面的 SG 值异或起来就得到整个游戏的 SG 值。

[代码](https://www.luogu.com.cn/record/144356218)。

闲话：这道题你可能也想找规律，毕竟很多 SG 函数都可以找规律找到。但你很快会发现 $\text{SG}(1,i)=1$，$\text{SG}(2,i)$ 的周期是 $2$，$\text{SG}(3,i)$ 的周期是 $6$，$\text{SG}(4,i)$ 的最小正周期是 $12$。也就是说，$\text{SG}(x,i)$ 的周期是 $\text{lcm}(1,2,\cdots,x)$ 填满的（显然 $\text{lcm}$ 一定是周期），显然无法解决 $10^9$ 规模的问题。因此要多多推式子，别只想着找规律，毕竟前缀和处理一下就做完了。

---

## 作者：封禁用户 (赞：1)

独立想出来的紫色思维题！

本题第一篇题解

每个格子选中后，若在纯白网格上仅有 $(i,j)$ 黑的情况下需要奇数次（包括选中 $(i,j)$）选中，则令 $f(i,j)=1$，否则 $f(i,j)=0$。

如 $f(1,k)=1,f(2,1)=1,f(2,2)=0,f(3,3)=1$ 等等（比如 $f(2,2)$，需要选中 $(2,2),(2,1),(1,2),(1,1)$ 为 $4$ 次，故 $f(2,2)=0$）。

一格从黑色改变为白色可以认为是需要两次选中该黑格，更多次同理，因为只考虑奇偶性，两次选中就是没选，递归可以证明 $f(i,j)$ 唯一确定（也就是奇偶性固定）。

对于任意的 $(i,j)$，$f(i,j)$ 就相当于选中 $(i,j)$ 会选中的矩形中除了 $(i,j)$ 外所有点的 $f$ 值的异或再取反（因为选中 $(i,j)$ 并取反也算一步，导致奇偶性改变，而这会导致出现矩形内所有的其他格子变黑，所以异或上那些格子）。

假设 $g=\min(i,j)$，则 $f(i,j) \oplus 1=\mathop\oplus\limits_{u=i-g+1}^i\mathop\oplus\limits_{v=j-g+1}^j [u \ne i\ or\ v \ne j]f(u,v)$，也就是 $1=\mathop\oplus\limits_{u=i-g+1}^i\mathop\oplus\limits_{v=j-g+1}^j f(u,v)$。

令 $S(i,j)$ 为前缀异或和，假设 $i<j$，则根据 $S$ 的定义和上面的式子，可知 $S(i,j)=S(i,j-g) \oplus 1$，观察这个式子，很像辗转相除，于是得到 $S(i,j)=S(i,j \mod i) \oplus [2 \nmid \lfloor \frac{j}{i} \rfloor]$。

终止条件为 $i \mid j$，此时就是 $\frac ji$ 个边长为 $i$ 的正方形依次排列，每个正方形有 $1$ 的贡献（依然是那个式子），所以此时 $S(i,j)=[2 \nmid \frac ji]$。

辗转相除即可。

[AC 记录](https://www.luogu.com.cn/record/139593368) 代码写的很烂，将就一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x,y,k;
inline int d(int i,int j){return !(j%i)?(j/i)&1:((j/i)&1)^d(j%i,i);}
inline int e(int i,int j){return !i||!j?0:i<j?d(i,j):d(j,i);}
int main(){
	cin>>t;
	for(int i=0;i<t;++i) cin>>x>>y,k^=e(x,y)^e(x-1,y)^e(x,y-1)^e(x-1,y-1);
	cout<<(k?"FIRST":"SECOND");
	return 0;
}
```

---

