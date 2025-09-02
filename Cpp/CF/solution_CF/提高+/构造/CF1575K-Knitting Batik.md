# Knitting Batik

## 题目描述

Mr. Chanek wants to knit a batik, a traditional cloth from Indonesia. The cloth forms a grid $ a $ with size $ n \times m $ . There are $ k $ colors, and each cell in the grid can be one of the $ k $ colors.

Define a sub-rectangle as an ordered pair of two cells $ ((x_1, y_1), (x_2, y_2)) $ , denoting the top-left cell and bottom-right cell (inclusively) of a sub-rectangle in $ a $ . Two sub-rectangles $ ((x_1, y_1), (x_2, y_2)) $ and $ ((x_3, y_3), (x_4, y_4)) $ have the same pattern if and only if the following holds:

- they have the same width ( $ x_2 - x_1 = x_4 - x_3 $ );
- they have the same height ( $ y_2 - y_1 = y_4 - y_3 $ );
- for every pair $ (i, j) $ where $ 0 \leq i \leq x_2 - x_1 $ and $ 0 \leq j \leq y_2 - y_1 $ , the color of cells $ (x_1 + i, y_1 + j) $ and $ (x_3 + i, y_3 + j) $ are equal.

Count the number of possible batik color combinations, such that the subrectangles $ ((a_x, a_y),(a_x + r - 1, a_y + c - 1)) $ and $ ((b_x, b_y),(b_x + r - 1, b_y + c - 1)) $ have the same pattern.

Output the answer modulo $ 10^9 + 7 $ .

## 说明/提示

The following are all $ 32 $ possible color combinations in the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575K/d3c6708d78b5f06c195ccdb514326aae6d396561.png)

## 样例 #1

### 输入

```
3 3 2 2 2
1 1 2 2```

### 输出

```
32```

## 样例 #2

### 输入

```
4 5 170845 2 2
1 4 3 1```

### 输出

```
756680455```

# 题解

## 作者：misaka_sama (赞：3)

简单分讨，根本不到蓝吧，最多黄。

首先如果两个子矩形完全重合，那任何情况一定满足限制，输出 $k^{nm}$（有 $nm$ 个格子，每个格子都可以填 $k$ 种颜色，且互不干扰）。

否则我们考虑第二个矩形，手玩一下你会发现，第二个矩形中的每个格子都受一个形如 $a_{x1,y1}=a_{x2,y2}$ 的限制（如果两个矩形有交集就可能有多个位置必须相等）。反正无论如何，有 $nm-rc$ 个格子是自由的，而有 $rc$ 个是受限制的。所以答案是 $k^{nm-rc}$。

[code](https://codeforces.com/contest/1575/submission/299970593)

---

## 作者：skyskyCCC (赞：2)

## 前言。
思维题，用到分析与分类讨论。

结果被第二个样例卡了半小时的我，不仅要长叹一声：如果输出负数，请检查一下数据范围，然后看下您把数据类型开够了没有。
## 分析。
首先分析一个情况：两个矩形重叠，即 $a_x=b_x$ 并且 $a_y=b_y$ 时，很明显整个矩形可以任意涂色，分析样例一然后画画图，不难得到答案就是 $k^{nm}$ 的答案。严格证明可以用乘法原理。

否则两个矩形不重叠。
- 如果两个矩形完全不重叠，很明显如果我们确定了矩形 $A$ 的填充部分，则一定能相应地对应到矩形 $B$ 所以只要考虑其中一个矩形即可。答案为 $k^{nm-rc}$ 的结果。
- 如果两个矩形部分重叠，考虑填充未重叠部分，则如果填充了一部分非重叠部分，则另一个矩形的重叠部分就可以确定一部分，然后根据已知推未知，一定能找到一种方案填充重叠部分，此时相应地能找到另一个矩形的颜色。明显答案就是 $k^{nm-rc}$ 的结果。

一句话概括：除了第二个矩形之外的地方都可以随便取，并且此时第二个矩形有且仅有一种染色方案。那么在网格中只有 $nm-rc$ 的若干不相交部分是不被影响的。

什么意思哪？我们可以借助一张图理解：
![](https://cdn.luogu.com.cn/upload/image_hosting/xlsoscv2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

暂且忽略掉大矩形中没有截到的一部分。这种情况里 $4$ 个点是一定需要相同颜色的，我们去找有多少个点和当前点颜色相同即可。但是我们只需要考虑第一个矩阵不重叠的部分，因为第二个矩阵的部分一定会和第一个矩阵不重叠的部分一一对应。

为了防止超时，可以采用快速幂计算。

时间复杂度为 $O(\log nm)$ 足以通过本题。

代码如下，仅供参考：
```
#include<iostream>
#define ll long long
using namespace std;
const ll mod=1e9+7;
ll n,m,k,r,c,ax,ay,bx,by;
ll ksm(ll a,ll b){
	int res=1;
	while(b){
		if(b&1){
			res=res*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main(){
    cin>>n>>m>>k>>r>>c;
    cin>>ax>>ay>>bx>>by;
    if(ax==bx&&ay==by){
        cout<<ksm(k,n*m)%mod<<"\n";
    }
    else{
        cout<<ksm(k,n*m-r*c)%mod<<"\n";
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：songhongyi (赞：1)

题意：给定一个 $n\times m$ 的矩形，每个方格染 $k$ 种颜色中的一个，问有多少种方法使得两个给定的大小相同的子矩形内图案相同（定义为对应行列相同）

解法：注意到如果两个矩形完全重叠，则答案显然为 $k^{nm}$，否则考虑去掉一个矩形，剩下的内容一定可以唯一的确定整个图案，因而答案为 $k^{nm-rc}$，快速幂处理即可，复杂度 $O(\log nm)$

```cpp
//
// Problem: K. Knitting Batik
// Contest: Codeforces - COMPFEST 13 - Finals Online Mirror (Unrated, ICPC
// Rules, Teams Preferred) URL: https://codeforces.com/problemset/problem/1575/K
// Memory Limit: 512 MB
// Time Limit: 2000 ms

#include <iostream>
using namespace std;
long long int pmod = 1e9 + 7;
long long int qpow( long long int a, long long int b )
{
    // cerr << a << "  " << b << endl;
    if ( b == 0 )
    {
        return 1;
    }
    if ( b == 1 )
    {
        return a;
    }
    long long int t = qpow( a, b / 2 ) % pmod;
    if ( b & 1 )
    {
        return ( t * t ) % pmod * a;
    }
    else
    {
        return t * t;
    }
}
int main()
{
    long long int n, m, k, r, c;
    cin >> n >> m >> k >> r >> c;
    int ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    if ( ax == bx && ay == by )
    {
        cout << qpow( k, n * m ) % pmod << endl;
    }
    else
    {
        cout << qpow( k, n * m - r * c ) % pmod << endl;
    }
}
```

---

## 作者：bingo888 (赞：0)

#### 题目回顾：  
在 $n\times m$ 的矩形中给每个格子任意涂上 $k$ 中颜色，同时给出两个大小相同的子矩形位置，求有多少种涂色方案使两个子矩形涂色完全相同。  

#### 题解：  
在已有的题解中，思路已经很清晰了，这里稍加补充：  

对于完全重叠的两个子矩形：整个大矩形可以任意涂色，由乘法原理可得答案为 $k^{nm}$。  

对于完全不重叠的两个子矩形：填涂任意一个子矩形将确定另一个，所以任意填涂的方格数将减少一个子矩形的方格数，答案即为 $k^{nm-rc}$。  

对于部分重叠的两个子矩形，任意填涂其中一个的未重叠部分，一定可以确定一部分重叠部分的颜色，再根据已经确定的颜色可以继续填涂重叠部分，一定可以将重叠部分填满，于是同时也便确定了另一个子矩形的颜色，答案即为空白部分加上其中一个子矩形的未重叠部分，即大矩形方格数减去一个子矩形方格数，答案仍然为 $k^{nm-rc}$。  

由于代码只有快速幂板子，并且已经有题解给出了，所以本人便不贴代码了。  
细节注意：由于 $n,m$ 较大，可以用欧拉定理（指数取模）优化代码（本质上用处不大，最多快一倍）。  

优化后时间复杂度为 $\mathcal{O}(\log mod)$。  

~~本人觉得这是自己做过最水的蓝题（逃。~~  

---

