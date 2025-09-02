# Grid Game 2

## 题目描述

你和你的朋友正在玩“Grid Game 2”。有一个 $10^9$ 行（编号从 $1$ 到 $10^9$）和 $10^9$ 列（编号从 $1$ 到 $10^9$）的网格。第 $r$ 行第 $c$ 列的格子记作 $(r, c)$。

每个格子可以是黑色或白色。初始时，恰好有 $N$ 个黑色格子（编号从 $1$ 到 $N$）。第 $i$ 个黑色格子位于 $(R_i, C_i)$。其余格子都是白色。

你和你的朋友轮流在这个网格上进行操作，你先手。在每一回合，玩家需要选择一个黑色格子 $(r, c)$，然后对所有满足 $0 \leq x, y < \min(r, c)$ 的格子 $(r - x, c - y)$ 进行翻转操作。如果一个格子被翻转，那么如果它原本是白色就变成黑色，原本是黑色就变成白色。

例如，下图展示了玩家在自己的回合选择黑色格子 $(5, 4)$ 后，网格的变化情况。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/e2fd54c73d9615e1033b8dd1a01d70086efa600.png)

如果某位玩家在自己的回合无法选择黑色格子（即没有剩余的黑色格子），则该玩家输掉游戏，对方获胜。如果你和你的朋友都采取最优策略，判断谁将赢得游戏。

## 说明/提示

样例输入输出 #1 说明

你可以先选择 $(2, 4)$，其效果如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906G/2b04f438065762fd04c672bc2aeca49fdf0ed64a.png)

剩下的黑色格子是 $(1, 3)$ 和 $(1, 4)$，每次选择时只会翻转自身。无论你的朋友下一步选择哪一个，你都可以选择剩下的黑色格子。

样例输入输出 #2 说明

你只有一个格子可选，将会翻转 $(1, 1)$、$(1, 2)$、$(2, 1)$ 和 $(2, 2)$。你和你的朋友轮流选择剩下的黑色格子，你的朋友会选择最后一个黑色格子。

由 ChatGPT 4.1 翻译

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

## 作者：SudoXue (赞：0)

[更好的阅读体验](https://www.cnblogs.com/xueruhao/p/18974593)

把每个初始黑格 $(r,c)$ 视作独立子局 $G_{r,c}$。因一次操作只影响以 $(r,c)$ 为右下角的左上实心矩形，任何两子局要么互不相交，要么一包含一，从而整体就是若干子局的离散和；胜负取决于所有子局的 SG 值按异或求和是否为零。可证明 $G_{r,c}$ 的 SG 值只可能取 $0$ 或 $1$，且有公式：

$$g(r,c)=E(r,c)\oplus E(r-1,c)\oplus E(r,c-1)\oplus E(r-1,c-1)$$

其中 $E(a,b)$ 为在辗转相除求 $\gcd(a,b)$ 过程中，把每步整除商的奇偶性做异或得到的结果。循环中维护 $v\mathrel{\,\hat=\,}(a/b)\&1$，随后令 $(a,b)\leftarrow(b,a\bmod b)$ 即可，单次计算复杂度 $O(\log\max(a,b))$。读入全部黑格不断异或 $g(r,c)$，最终异或和非零则先手赢，否则后手赢。

时间复杂度 $O(N\log V)$，其中值域为 $V = 10^9$。

[link](https://codeforces.com/contest/1906/submission/328169208)

拓展：[CF494E Sharti](https://codeforces.com/contest/494/problem/E)

---

