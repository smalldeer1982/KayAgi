# [JOI 2019 Final] 硬币收藏 / Coin Collecting

## 题目背景

JOI 2019 Final T4

由于数据点较多，本题只评测其中的部分数据。

## 题目描述

JOI 先生的收藏室里有一张巨大的桌子，上面有许多稀有的硬币。为了清理桌子，他要重新摆放硬币。

桌面可视为 $(2\times 10^9+1)\times (2\times 10^9+1)$ 的网格。JOI 先生有 $2N$ 枚硬币。初始时，第 $i$ 枚 $(1\le i\le 2N)$ 硬币被放在坐标为 $(X_i,Y_i)$ 的格子里。JOI 先生的目标是在每个满足 $1\le x \le N,1\le y\le 2$ 的格子 $(x,y)$ 上恰好放一枚硬币。为了不损坏硬币，他能做的唯一一个操作是钦定一枚硬币然后将其移动到相邻的一个格子中（我们说两个格子相邻，当且仅当这两个格子有公共边）。在移动硬币的过程中，允许两个硬币处在同一个格子中。JOI 先生希望通过尽量少的操作次数完成目标。

现在给出硬币的数量和初始时所在的位置，编写一个程序，计算完成 JOI 先生目标所需的最少操作次数。

## 说明/提示

样例解释 $1$:  

一种合法的移动方案是：  

第一枚硬币：$(0,0)\rightarrow(1,0)\rightarrow(1,1)\rightarrow(1,2)$  

第二枚硬币：$(0,4)\rightarrow(1,4)\rightarrow(1,3)\rightarrow(2,3)\rightarrow(3,3)\rightarrow(3,2)$  

第三枚硬币：$(4,0)\rightarrow(4,1)\rightarrow(3,1)$  

第四枚硬币：不动  

第五枚硬币：$(2,5)\rightarrow(2,4)\rightarrow(2,3)\rightarrow(2,2)$ 
 
第六枚硬币：$(-1,1)\rightarrow(0,1)\rightarrow(1,1)$  

可以证明 JOI 先生不能用少于 $15$ 次移动完成目标。

对于 $8\%$ 的数据，$N\le 10$。

对于 $37\%$ 的数据，$N\le 1000$。

对于 $100\%$ 的数据，$N\le 10^5,-10^9\le X_i,Y_i\le 10^9$。

## 样例 #1

### 输入

```
3
0 0
0 4
4 0
2 1
2 5
-1 1```

### 输出

```
15```

## 样例 #2

### 输入

```
4
2 1
2 1
2 1
3 1
3 1
3 1
3 1
3 1```

### 输出

```
9```

## 样例 #3

### 输入

```
5
1000000000 1000000000
-1000000000 1000000000
-1000000000 -1000000000
1000000000 -1000000000
-1 -5
-2 2
2 8
4 7
-2 5
7 3```

### 输出

```
8000000029```

# 题解

## 作者：览遍千秋 (赞：10)

第18回日本情報オリンピック 本選 コイン集め 解説

[更好的阅读体验](https://www.cnblogs.com/liubainian/p/14002210.html)

## 问题描述

JOI 先生的收藏室里有一张巨大的桌子，上面有许多稀有的硬币。为了清理桌子，他要重新摆放硬币。

桌面可视为 $(2\times 10^9+1) \times (2\times 10^9+1)$ 的网格。网格上往下数第 $i$ 行（$-10^9 \le i \le 10^9$），左往右数第 $j$ 列（$-10^9 \le j \le 10^9$）的格子坐标记为 $(i, j)$ 。

JOI 先生有 $2N$ 枚硬币。初始时，第 $i$ 枚 $(1 \le i \le 2N)$ 硬币被放在坐标为 $(X_i, Y_i)$ 的格子里。JOI 先生的目标是在每个满足 $1 \le x \le N, 1 \le y \le 2$ 的格子 $(x,y)$ 上恰好放一枚硬币。为了不损坏硬币，他能做的唯一一个操作是钦定一枚硬币然后将其移动到相邻的一个格子中（我们说两个格子相邻，当且仅当这两个格子有公共边）。在移动硬币的过程中，允许两个硬币处在同一个格子中。JOI 先生希望通过尽量少的操作次数完成目标。

现在给出硬币的数量和初始时所在的位置，编写一个程序，计算完成 JOI 先生目标所需的最少操作次数。

## 题解

贪心，结论类似于 [JSOI2018]列队 / 均分纸牌。

注意到最后所有的 $2 \times N$ 个棋子都需要移动到左下角 $[1,1]$，右上角 $[2,N]$ 的矩形中，且每个棋子最终需要占据单独的一个格子，则问题可转化为为每个棋子分配一个格子。

所以 Subtask1 的 $8$ 分，可以通过暴力枚举每一个棋子对应的格子获得。

下面考虑如何分配格子。

如果想要将这些棋子，分配到这连在一起的一个矩形中，那么这些棋子首先需要移动到这个矩形中，显然对于棋子 $i(X_i,Y_i)$，将其移动到最近的矩形格 $(X_i',Y_i')$ 中最优。

移动顺序显然不影响答案，所以行列分开考虑，分别有以下几种情况：

$$X_i'=
\begin{cases}
X_i & X_i\in[1,n]\\
1 & X_i \in (-\infty,1)\\
n & X_i \in (n,+\infty)
\end{cases}
$$
$$Y_i'=
\begin{cases}
1 & Y_i \in (-\infty,1]\\
2 & Y_i \in [2,+\infty)
\end{cases}
$$

将棋子 $i$ 从 $(X_i,Y_i)$ 移动到 $(X_i',Y_i')$ 的代价为 $|X_i-X_i'| + |Y_i-Y_i'|$

上述移动方法之所以正确，是因为在移动过程中，每个格子可以同时堆放多个棋子。

但是可能存在多个不同的 $a_1,a_2,\cdots,a_k$，使得 
$\begin{cases}
X_{a_1}' = X_{a_2}' = X_{\cdots}' = X_{a_k}'\\
Y_{a_1}' = Y_{a_2}' = Y_{\cdots}' = Y_{a_k}'
\end{cases}
$

假设 $f(x,y)$ 代表满足 
$
\begin{cases}
x = X_i\\
y = Y_i
\end{cases}(i \in[1,2 \times N])
$ 的 $i$ 的数量。

至此，问题转化为调整矩形里每一个格子的棋子数量。

容易得到贪心算法，从 $1$ 到 $N$ 扫描所有 $f(i,1),f(i,2)$

显然，$[i,1],[i,2]$ 位置上需要移走的棋子数量分别为 $g(i,1)=f(i,1)-1,g(i,2)=f(i,2)-1$（如果为负，则为移来的数量）

分几类讨论：

- $g(i,1)=g(i,2)=0$

无答案贡献。

- $g(i,1)>0,g(i,2)<0$

令 $p=\min\{g(i,1),-g(i,2)\}$，代表从 $[i,1]$ 挪 $p$ 个棋子到 $[i,2]$。

此后，需要把 $g(i,1)-p$ 个棋子挪到 $g(i+1,1)$，把 $g(i,2)+p$ 个棋子挪到 $g(i+1,2)$

第 $i$ 列对答案的贡献为 $p + g(i,1) +g(i,2)$

- $g(i,1)<0,g(i,2)>0$

同上类。

- $g(i,1) \times g(i,2) > 0$

同上类，只是不需要计算 $p$，直接向右移动即可。

---

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define pb push_back

template < typename Tp >
inline void rd(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

template < typename Tp >
inline void bird(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 2 + ch - '0', ch = getchar();
	x *= fh;
}

template < typename Tp >
inline void smax(Tp &x, Tp y) {
	if(x < y) x = y;
}

const int maxn = 200000 + 7;

int n;
int num[2][maxn];

long long ans;

//#define tester

signed mian(void) {
	#ifdef tester
		freopen("coin.in", "r", stdin);
		freopen("coin.out", "w", stdout);
	#endif
	rd(n);
	for(int i = 1, x, y; i <= n * 2; i++) {
		rd(x); rd(y);
		int sx, sy;
		if(x >= n) sx = n;
		else if(x <= 1) sx = 1;
		else sx = x;
		if(y > 1) sy = 2;
		else sy = 1;
		if(sx > x) ans += sx - x;
		else ans += x - sx;
		if(sy > y) ans += sy - y;
		else ans += y - sy;
		--sy;
		num[sy][sx]++;
	}
	for(int i = 1; i <= n; i++) {
		num[0][i]--, num[1][i]--;
		int RIP = 0;
		if(num[0][i] > 0 && num[1][i] < 0) RIP = min(num[0][i], -num[1][i]);
		else if(num[0][i] < 0 && num[1][i] > 0) RIP = min(-num[0][i], num[1][i]);
		ans += RIP;
		if(num[0][i] > 0 && num[1][i] < 0) num[0][i] -= RIP, num[1][i] += RIP;
		else if(num[0][i] < 0 && num[1][i] > 0) num[0][i] += RIP, num[1][i] -= RIP;
		num[0][i + 1] += num[0][i], num[1][i + 1] += num[1][i];
		if(num[0][i] > 0) ans += num[0][i];
		else ans += -num[0][i];
		if(num[1][i] > 0) ans += num[1][i];
		else ans += -num[1][i];
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：随情英 (赞：10)

贪心

首先把棋子都移到里指定位置最近的部分，分六个区域，四个边角，两个中列。计算总的移动距离。
然后，按列考虑先上下移动，再从左右增补。类似均分纸牌。

```cpp
/*
 * @Autor: suiqingying
 * @Date: 2020-11-17 19:40:49
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-11-18 08:20:30
 */

#include <ctime>
#include <queue>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = x * 10 + c - '0', c = getchar();
    }
    return x * f;
}
const int maxn = 1e5 + 10;
struct Point
{
    long long x, y;
    Point(const long long &_x = 0, const long long &_y = 0)
    {
        x = _x, y = _y;
    }
};
long long d(const Point &A, const Point &B)
{
    return abs(A.x - B.x) + abs(A.y - B.y);
}
int n, cnt[maxn][3];
long long ans;
void pre_work()
{
    n = read();
    for (int i = 1; i <= n << 1; ++i)
    {
        int x = read(), y = read();
        if (x <= 1 && y <= 1)
        {
            cnt[1][1]++;
            ans += d(Point(x, y), Point(1, 1));
        }
        else if (x <= 1 && y >= 2)
        {
            cnt[1][2]++;
            ans += d(Point(x, y), Point(1, 2));
        }
        else if (x >= n && y <= 1)
        {
            cnt[n][1]++;
            ans += d(Point(x, y), Point(n, 1));
        }
        else if (x >= n && y >= 2)
        {
            cnt[n][2]++;
            ans += d(Point(x, y), Point(n, 2));
        }
        else if (y >= 2)
        {
            cnt[x][2]++;
            ans += d(Point(x, y), Point(x, 2));
        }
        else
        {
            cnt[x][1]++;
            ans += d(Point(x, y), Point(x, 1));
        }
    }
}
int main()
{
    pre_work();
    for (int i = 1, c1 = 0, c2 = 0; i <= n; ++i)
    {
        c1 += cnt[i][1] - 1, c2 += cnt[i][2] - 1;
        while (c1 < 0 && c2 > 0)
        {
            ++c1, --c2, ++ans;
        }
        while (c1 > 0 && c2 < 0)
        {
            --c1, ++c2, ++ans;
        }
        if (i < n)
        {
            ans += abs(c1) + abs(c2);
        }
    }
    printf("%lld\n", ans);
    return 0;
}



---

## 作者：彭天宇 (赞：8)

真就没想到这题是[均分纸牌](https://www.luogu.com.cn/problem/P1031)的变式啊。

这是一个大贪心，没有什么玄学的地方。

首先将平面上所有点转移到$2\times n$区域的边缘，这样能保证下面的操作更优。（十分显然）

然后考虑怎样内部调节硬币的数量：

如果这个位置上下两个$(a[i][1],a[i][2])$能够内部调节就调节一下，这样每平衡一个硬币只要移动一步，而且防止到最后又一行没有满，另一行溢出。

如果多余就向后面转移一步，缺少就向后面索要，两种虽然方法不同但计算起来是一样的。

想明白了代码就其短无比。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,a[N][3];
long long ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=2*n;i++){
		int x=read(),y=read();
		if(x<1){
			ans+=1-x;
			x=1;
		}
		if(x>n){
			ans+=x-n;
			x=n;
		}
		if(y>2){
			ans+=y-2;
			y=2;
		}
		if(y<1){
			ans+=1-y;
			y=1;
		}
		a[x][y]++;
	}
	int up=0,down=0;
	for(int i=1;i<=n;i++){
		up+=a[i][1]-1;
		down+=a[i][2]-1;
		while(up>0&&down<0){
			up--;
			down++;
			ans++;
		}
		while(down>0&&up<0){
			up++;
			down--;
			ans++;
		}
		ans+=abs(up)+abs(down);
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：Happy_Dream (赞：2)

既然没有题解，就给大家写一下吧。

对于$Subtask 1$，我们可以纯爆搜去做，复杂度较玄学，可以拿到8分的高分。

对于$Subtask 2$，可以纯暴力去做，复杂度较玄学，可以拿到45分的高分。

而对于满分，我们可以将硬币先移动到离他最近的格子，这是会有一些地方有很多，而一些地方却没有，我们可以扫描一下每一列，可以类似的理解为一个贪心，如果有空的地方，就移过来一些，否则将这列多余的硬币全部拿走。复杂度也比较玄学差不多$O(N)$的，可以通过此题。

MY CODE：
```
#include <bits/stdc++.h>
using namespace std;
int b[1000005][3];
int main()
{
	int n;
	cin>>n;
	long long ans=0;
	for(int x,y,i=1;i<=2*n;i++)
	{
		cin>>x>>y;
		if(x<1)
		{
			ans+=1-x;
			x=1;
		}
		if(x>n)
		{
			ans+=x-n;
			x=n;
		}
		if(y<1)
		{
			ans+=1-y;
			y=1;
		}
		if(y>2)
		{
			ans+=y-2;
			y=2;
		}
                //往近的地方放
		b[x][y]++;//将有硬币的地方加一下（类似于一个桶）
	}
	for(int i=1,x=0,y=0;i<=n;i++) 
	{
                x+=b[i][1]-1;
		y+=b[i][2]-1;
                while(x<0&&y>0)
                {
        	        x++;
        	        y--;
        	        ans++;
	        }
                while(x>0&&y<0)
                {
        	        x--;
        	        y++;
        	        ans++;
	        }
                //按照上过程模拟即可
                if(i<n)
                ans+=abs(x)+abs(y);//计算答案
        }
        cout<<ans;
	return 0;
}
```
同步发布与本人nowcoder blog

here:

https://blog.nowcoder.net/yisu1

---

## 作者：FutaRimeWoawaSete (赞：1)

一刚开始想加写的很复杂，其实并没有那么恶心。

感觉还是很困难的贪心。

考虑一个很显然的东西就是大坐标轴背景其实是虚假的，直接走到最近的范围内的点上然后做进一步的子问题显然是最优的。

可以考虑最后匹配过程上的形成形式，发现若任意点到其匹配的目标点，由于是曼哈顿距离，先走到范围内最近点再走到目标点是不劣的。

考虑一维问题怎么做，一个贪心是根据空的位置和多余位置的棋子按顺序一一匹配，考虑函数化的表达，滚前缀和，每次维护有多少个棋子必定要向左右移动将贡献平摊到每个 $i \rightarrow i+ 1$ 或 $i + 1 \rightarrow i$ 的间隙上。

回归二维，不考虑两行的跨越传递棋子，我们发现问题变成：

- 给定两个变量 $L,R$ 初始为 $0$，一个 $2 \times n$ 的矩阵上每次令 $L \leftarrow L + c_{i,1},R \leftarrow R + c_{i,2}$，最后贡献是 $\sum |L_i| + |R_i|$。

考虑跨越传递棋子。将其放在转化问题时就是消耗 $1$ 的代价，使得 $L \leftarrow L + 1,R \leftarrow R - 1$ 或 $R \leftarrow R + 1,L \leftarrow L - 1$。

不妨大胆猜测一个结论：每次若 $L,R$ 一正一负时互相递补调整，最后求和就是最优策略。

考虑任意的 $c_{x,y} \in [-1,2n]$，我们发现每次递补调整时大多数情况都会让当前的 $|L| + |R|$ 减少 $2 - 1 = 1$，只有当 $L,R$ 为 $-1,+1$ 且下次的 $c$ 为 $1,-1$ 才会造成当前的操作不劣。

并且我们发现由于保证 $\sum = 2n$，且 $L,R$ 在最后的值代表了有 $n + x$ 个棋子这样的含义，操作的目标导向为“尽量使两者值都为 $0$”，最后一定能保证 $L = 0,R = 0$，即分配两行棋子平均的定义。

我们可以发现该种操作的所有可能导致的后效性都是不劣的，并且所有的后续影响都是最优的，故可以默认为后效性其实是不存在的，这样最优子结构也可以被提出来，贪心的正确性也可以得到证明。我不知道这个表达是否准确，也许是自己的理解。

时间复杂度 $O(n)$。

```cpp
/*
考虑对于极大坐标轴是假的，显然移动到最近的范围区域后重新分配是对的。
如果是一维的话很简单，显然必须对应填是最小的。
考虑加了一行，咋做
离线下来成一维序列，考虑 dp，设 dp_{i,l,r} 当走到 i 时表示上面前 l 个下面前 r 个的最小花费
然后咋搞，感觉就不平凡了。
先来看一下转移式
dp_{i,l,r} = min(dp_{i - 1,l - 1,r} + opt + dis(i,l) , dp_{i - 1,l,r - 1} + opt + dis(i,r))  
首先，一个点上有的就不动了。 
可以发现重叠的路径之间是可以 swap 的。
然后就有一个很显然的贪心了？ 
*/
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int Len = 1e5 + 5;
int n,m;
int sm[2],ct[Len][2];
#define ll long long
inline int Iabs(int x){if(x < 0) x = -x;return x;}
ll as = 0;
int sum[Len];
signed main()
{
	scanf("%lld",&n);
	for(int i = 1 ; i <= (n << 1) ; i ++)
	{
		int x,y;scanf("%lld %lld",&x,&y);
		if(x <= 0) as += Iabs(x - 1) , x = 1;
		if(x > n) as += Iabs(x - n) , x = n;
		if(y <= 0) as += Iabs(y - 1) , y = 1;
		if(y > 2) as += Iabs(y - 2) , y = 2;
		ct[x][y] ++;
		//printf("!%d %d\n",x,y);
		sm[y] ++;
	}
	//printf("%lld\n",as);
	int opt = 1;
	int L = 0 , R = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		L += ct[i][1] - 1 , R += ct[i][2] - 1;
		while(L > 0 && R < 0) L -- , R ++ , as ++;
		while(L < 0 && R > 0) R -- , L ++ , as ++;
		//printf("%d %d\n",L,R);
		as += Iabs(L) + Iabs(R);
	}
	printf("%lld\n",as);
	return 0;
}
```

---

## 作者：Luogu_916767 (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/P6117)

### 题目大意
求将桌子上的硬币排列成一个矩阵的最小移动次数。

### 思路分析
所有硬币必须最终位于矩阵内。对于初始在矩阵外的硬币，先移动到距离最近的矩阵内位置，记录这部分必要移动的次数。

矩阵内可能存在硬币过剩或空缺，需进一步调整：

1. 分别统计每行的硬币数量。
2. 优先进行同列调整：若一列多，另一列少则从多的行移动到少的行。
3. 直接移动，比跨行列移动更优。

这里有一个技巧，若某位置需要一个硬币，而此前已经没有多余的硬币，则可以将空格数纪录，应为将空格移走和从别的格子移过来一枚硬币是等价的。

### 警示后人

一定要开 `long long` 血泪的教训啊！
      
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
//十年OI一场空，不开longlong见祖宗。

using namespace std;

int n;
int a[100005][5];
int x,y;

signed main(){
    cin>>n;
    int ans = 0;
    for(int i = 1; i <= 2*n; i ++ ){
        cin>>x>>y;
        if(x <= 1){
            ans += 1-x;
            if(y >= 2){
                ans += y-2;
                a[1][2] ++ ;
            }else{
                ans += 1-y;
                a[1][1] ++ ;
            }
        }else if(x > 1 && x < n){
            if(y >= 2){
                ans += y-2;
                a[x][2] ++ ;
            }else{ 
                ans += 1-y;
                a[x][1] ++ ;
            }
        }else{
            ans += x-n;
            if(y >= 2){
                ans += y-2;
                a[n][2] ++ ;
            }else{
                ans += 1-y;
                a[n][1] ++ ;
            }
        }
    }
//    x = y = 0;防抄袭
	for(int i = 1; i <= n; i ++ ){
		x += a[i][1] - 1;
		y += a[i][2] - 1;
		while(x > 0 && y < 0){
			x -- ;
			y ++ ;
			ans ++ ;
		}
		while(y > 0 && x < 0){
			x ++ ;
			y -- ;
			ans ++ ;
		}
		ans += abs(x) + abs(y);
	}
    cout<<ans;
}
```

当然，直接抄是不会对的啊。

---

## 作者：時空 (赞：0)

[Link](https://www.luogu.com.cn/problem/P6117)

神秘题。

首先考虑把所有硬币都移到目标矩阵里。由于允许两个硬币处在同一个格子中，所以所有硬币可以一起考虑移动。\
那么现在我们得到了两行 $n$ 列的矩阵，每一个位置上可能有若干个硬币。\
考虑只有一行怎么做。这就是均分纸牌了。一个很好的套路可惜我不会。\
考虑原题。在只有一行的过程中，对于每一列我们有 $x$ 表示当前这一位，需要往后转移的硬币的数量。若 $x > 0$ 表示需要往后放，否则需要从后面拿。当前列对答案的贡献即为 $x$。 \
那么对于有两行的情况，区别在于我们此时有 $x_1,x_2$，且当前的贡献为 $\lvert x_1 \lvert + \lvert x_2 \rvert$。考虑让 $\vert x_1 \rvert$，$\lvert x_2 \rvert$ 尽量小。注意到 $1,2$ 行的硬币可以相互转化，即可以做到 $x_1 \leftarrow x_1 - 1,x_2 \leftarrow x_2 + 1$ 或 $x_1 \leftarrow x_1 + 1,x_2 \leftarrow x_2 - 1$。那么每次若 $x_1,x_2$ 正负性不同，转化即可。

```cpp
#include <bits/stdc++.h>

#define FstIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair <ll, ll>
#define pb push_back
#define mem(a, v) memset(a, v, sizeof a)

using namespace std; 

using ll = long long; 
using ull = unsigned long long;
using ld = long double;

const ll N = 5e5 + 2, M = 2e3 + 5;
const ll inf = 1e18, mod = 1e9 + 7;
const ld eps = 1e-6;

ll n, t;
ll f[N][3];
ll find(ll x)
{
	if (x >= 1 && x <= n) return x;
	if (x < 1) return 1;
	return n;
}
ll find2(ll y)
{
	return (y >= 2) ? 2 : 1; 
}

signed main()
{
	FstIO;	
	
	cin >> n;
	
	for (ll i = 1; i <= (n << 1); ++ i )
	{
		ll x, y; cin >> x >> y;
		
		ll p = find(x), q = find2(y);
		++ f[p][q];
		t += abs(p - x) + abs(q - y);	
	}
	ll up = 0, down = 0;
	for (ll i = 1; i <= n; ++ i )
	{
		up += f[i][1] - 1, down += f[i][2] - 1;
		while (up > 0 && down < 0) 
			-- up, ++ down, ++ t;
		while (up < 0 && down > 0)
			++ up, -- down, ++ t;
		t += abs(up) + abs(down);
	}
	cout << t << '\n';
	
	return 0;
	
	cout.flush();
}
```

---

## 作者：Anonymely (赞：0)

可以看成给每个硬币分配一个位置，然后每个硬币走到位置上的最小路径和。

先让每个硬币走进 $2 \times n$ 的连通块内，容易找到每个硬币所对应的连通块的进入点，具体地，行列独立开来，分类讨论一下与 $1,n$ 的大小关系即可。

找到了后问题变成了 $2 \times n$ 的网络中每个格子有 $w(i,j)$ 枚棋子，移动至每个格子仅有一枚棋子的最小代价。

实际上就是个有二维的均分纸牌问题，不同的是可以上下交换，而能上下交换一定是更优的，根据符号讨论即可。

复杂度 $O(n)$。


```cpp
	int n;
	cin >> n;
	vector < array <int, 2> > f(n);
	i64 sum = 0;
	for (int i = 1, x, y; i <= 2 * n; i++) {
		cin >> x >> y;
		x--, y--;
		int sx, sy;
		if (x < 0) sx = 0;
		else if (x >= n) sx = n - 1;
		else sx = x;
		if (y <= 0) sy = 0;
		else sy = 1;
		sum += abs(sx - x) + abs(sy - y);
		f[sx][sy]++;
	}
	for (int i = 0; i < n; i++) {
		f[i][0]--, f[i][1]--;
		int d = 0;
		if (f[i][0] > 0 && f[i][1] < 0) d = min(f[i][0], -f[i][1]);
		else if (f[i][0] < 0 && f[i][1] > 0) d = min(-f[i][0], f[i][1]);
		sum += d;
		if (f[i][0] > 0 && f[i][1] < 0) f[i][0] -= d, f[i][1] += d;
		else if (f[i][0] < 0 && f[i][1] > 0) f[i][0] += d, f[i][1] -= d;
		if (i != n - 1) f[i + 1][0] += f[i][0], f[i + 1][1] += f[i][1];
		sum += abs(f[i][0]) + abs(f[i][1]);
	}
	cout << sum << '\n';
```

---

## 作者：masonpop (赞：0)

~~JOI 特技大贪心。~~

首先每个点在回家的路上，一定会经过矩形的边缘。因此，可以先让每个点走最短路到达矩形边界的某个位置（在矩形内则不动）。显然这样不影响答案。

接着就是这样的问题：一个 $n\times 2$ 矩形，每个格子内有 $a_i$ 个点，问至少移动多少次，使得每个格子内恰有一个点。可以发现，这就是经典的均分物品问题的加强版。

很容易想到类似做法。设 $b_i=a_i-1$ 表示需要移走多少个点。然后每一行考虑，如果两边的 $b$ 异号，显然先两边中和一下，剩下的直接往下丢即可。

复杂度 $O(n)$。[代码](https://www.luogu.com.cn/paste/q257ft2x)。

---

## 作者：Zero_s (赞：0)

本题只需要用到贪心就可以了，没有什么坑点。
## 先考虑策略：
显然，将平面上所有点转移到 $2\times n$ 区域的边缘，这样能保证下面的操作更优。（~~是个人都能看得出来，这里就不解释了。~~）
## 解决调节数量：
1. 如果这个位置上下两个 $(f[i][1],f[i][2])$ 能调节就调节一下，这样每平衡一个硬币只要移动一步。另一个优点是能防止到最后又一行没有满，也能防止另一行溢出。

2. 前面多就甩锅到后边去，前面少的话就从后方抢，两种虽然方法不同但计算起来是一样的。
## AC代码在这里：
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,f[100050][3],x,y,l,r,i;
long long ans;
inline int read()//快读优化，其实并不需要。
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-') f=-1;//记得输入可能是负数。
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);//位运算优化。
		ch=getchar();
	}
	return x*f;//记得要相乘哟！~~
}
int main()
{
	N=read();
	for(i=1;i<=2*N;i++)//先循环输入然后初次处理。
	{
		x=read();
		y=read();
			//输入数据
		if(x<1) ans+=1-x,x=1;
		if(x>N) ans+=x-N,x=N;
		if(y>2) ans+=y-2,y=2;
		if(y<1) ans+=1-y,y=1;
		f[x][y]++;
	}
	for(i=1;i<=N;i++)//第二次计算ans。
	{
		l+=f[i][1]-1;
		r+=f[i][2]-1;
		while(l>0&&r<0) l--,r++,ans++;
		while(l<0&&r>0) l++,r--,ans++;
			//这里一定要记得ans++，我就因为没有ans++错了一次。
		ans+=abs(l)+abs(r);//l和r可能是负数，所以要取abs。
	}
	printf("%lld\n",ans);//输出答案。
	return 0;//记得return 0哟！
}
```
这道题其实就是贪心啦，只要按照刚刚说的策略做就可以了。

---

## 作者：qwq自动机 (赞：0)

Solution for  [P6117 JOI 2019 Final 收集硬币](https://www.luogu.com.cn/problem/P6117)

一个奇怪的贪心……

首先我们可以很容易想到可以先把所有的硬币全部移到那个 $2\times N$ 的矩形里面。具体的移动方法如图：

![看来图片挂了 qnq](//hassium.gitee.io/res/imgs/20211117-1.jpg)

代码写起来大概是这样：

```cpp
// 原来硬币在 (x, y)，要移动到 (xpos, ypos)
if (x < 1)
    xpos = 1;
else if (x > n)
    xpos = n;
else
    xpos = x;
if (y < 1)
    ypos = 1;
else if (y > 2)
    ypos = 2;
else
    ypos = y;
```

然后我们开一个桶记录下 $2\times N$ 的区域内每个点在移动后有多少个硬币。

现在的问题已经转化为 $2\times N$ 的格子里每个格子有一些硬币，要把这些硬币“铺平铺均匀”在整个矩形里面，最少要几步。

现在该怎么做？

~~注意到这个东西有点像 [Generals](//generals.io)……然后通过人类智慧就~~可以得出一个贪心结论：先在当前列的两个格子当中把硬币“匀开“，然后再向后推进。

具体来说就是从 $1$ 到 $N$ 枚举 $i$，对于第 $i$ 列的两个格子 $(i,1)$ 和 $(i, 2)$，先内部把缺少 / 多余的硬币消化掉，然后留下最少的那几个硬币往下一个列的对应格子累加，同时正确累加步数即可。

代码如下，稍微压了压行，有注释。

```cpp
#include <iostream>
#include <cmath>
const int MAXN = 1e5 + 10;
int cnt[MAXN][3], n;
int main()
{
    long long ans = 0;
    std::cin >> n;
    for (int i = 1, x, y, xpos, ypos; i <= n << 1; i++) // 注意这里是 2n 个硬币
    {
        std::cin >> x >> y;
        // 计算目标位置
        if (x < 1) xpos = 1;
        else if (x > n) xpos = n;
        else xpos = x;
        if (y < 1) ypos = 1;
        else if (y > 2) ypos = 2;
        else ypos = y;
        cnt[xpos][ypos]++; // 累加桶
        ans += abs(xpos - x) + abs(ypos - y); // 累加刚开始的步数
    }
    int up = 0, down = 0; // 上 / 下行剩余多少硬币要挪走（负的就是要挪过来）
    for (int i = 1; i <= n; i++) // 从左到右扫描列
    {
        up += cnt[i][1] - 1; // 累加当前列的硬币，注意每一列都要留下一个
        down += cnt[i][2] - 1;
        if (up > 0 && down < 0) // 如果上面可以给下面补
        {
            int moved = std::min(-down, up); // 能够补上的硬币
            up -= moved; // 上面的减掉补的
            down += moved; // 下面的加上不得
            ans += moved; // 更新答案
        }
        else if (up < 0 && down > 0) // 同理下面补上面
        {
            int moved = std::min(down, -up);
            up += moved;
            doen -= moved;
            ans += moved;
        }
        ans += abs(up) + abs(down); // 补剩的移到下一列去，累加答案
    }
    std::cout << ans << std::endl;
    return 0;
}
```



---

