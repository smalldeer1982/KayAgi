# [POI 2012] LIC-Bidding

## 题目背景

**本题为交互题**。

**本题 checker 中含有正解, 故不下发**。

## 题目描述

A 和 B 两个人在玩一个游戏，这个游戏是他们轮流操作一对整数 $(x,y)$。

初始时 $(x,y)=(1,0)$，可以进行三种操作：

1. 将 $(x,y)$ 变成 $(1,x+y)$。
2. 将 $(x,y)$ 变成 $(2x,y)$。
3. 将 $(x,y)$ 变成 $(3x,y)$。

给定正整数 $n$。在 $x+y\ge n$ 时就不能进行后两种操作。如果某个人操作后 $y\ge n$，他就输掉了。

保证给出的 $n$ 为先手必胜的，你需要提供一种先手必胜的方案。例如 $n = 3$ 时，先手选择操作 3，后手只能选择操作 1 然后输，所以 $n = 3$ 时先手必胜。

**交互题**，你需要实现一个函数 ``extern "C" int _opt(int n, int x, int y)``，该函数的返回值是一个值为 $1$，$2$ 或 $3$ 的整数，表示现在数对是 $(x, y)$，参数是 $n$ 且轮到你操作时，你会选择的操作。

## 说明/提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq n\leq 30000$。

### 说明

样例交互库见附件。与选手程序在本地一起编译后可以通过标准输入来模拟 spj 与选手程序进行交互。  
当交互库输出 `-2 -2` 并退出时，说明选手程序正确。

# 题解

## 作者：Werner_Yin (赞：11)

这是一道博弈论DP 的交互题。

# 暴力

我们可以设状态为

$f[i][j]$

表示当 x 为 $i$ 时，y 为 $j$ 时的走法，当

$f[i][j] = 0$时为必输。

于是：

$f[i][j] =$ 

- 0 ($i + j >= n $)

- 1 $(f [1][i+j] = 0)$

- 2 $(f[i*2][j] = 0)$

- 3 $(f[i*3][j] = 0)$



但是,这肯定$MLE$了。

# 优化

   注意到，$x$ 可以表示为 $2^i*3^j$ ,于是我们可以这样表示状态：

$f[i][j][k]$ :

当 $y = i,x = 2^j*3^k$ 时 的方案。

预处理一下$2$，$3$ 的幂就行。

改造一下方程即可。

# 代码

蒟蒻第一次写非IO的交互题，长见识了。

```cpp
int f[30010][16][11] = {0},k = 0;
int p2[16],p3[11];
extern "C" {
	extern int _opt(int n, int x, int y) {
		if(k == 0){
		    p2[0] = 1,p3[0] = 1;
		   for(int i = 1;i <= 15;i++) p2[i] = p2[i-1]*2;
            for(int i = 1;i <= 10;i++) p3[i] = p3[i-1]*3;
	   		for(int i = n;i >= 0;i--){
	    		for(int j = 15;j >= 0;j--){
	    			for(int k = 10;k >= 0;k--){
	    				if(p2[j] * p3[k] + i >= n) f[i][j][k] = 0;
	    				else{
	    					if(!f[i][j + 1][k]) f[i][j][k] = 2;
	    					if(!f[i][j][k+1]) f[i][j][k] = 3;
	    					if(!f[ i+p2[j]*p3[k] ][0][0]) f[i][j][k] = 1;
	    				}
	    			}
	    		}
	    	}
            k = 1;
        }
		int xx2 = 0,xx3 = 0;
		while(x%2 == 0 && x > 0){x /= 2;xx2++;}
		while(x%3 == 0 && x > 0){x /= 3;xx3++;}
        return f[y][xx2][xx3];
	}
}
```



---

## 作者：ttq012 (赞：3)

upd：已经通过题解更新代码。

博弈论动态规划题。

容易想到令 $f[i][j]$ 为 $x = i$，$y = j$ 时的最优方案。

但是 $N\le 3\times 10^4$，会超时超空。

但是注意操作 $2$ 和操作 $3$，容易发现，$x$ 只可能转移到 $2\times x$ 和 $3\times x$。

那么记录一个状态 $f[i][j][k]$，代表 $x = 2^i\times 3^j$，$y = k$ 的时的最优方案。

经过计算，$k\le 3\times 10^4$，$i\le 16$，$j\le 10$ 的状态即可。时间复杂度为 $O(i\times j\times k)\approx 5\times 10^6$，可以通过这个题。

注意是交互题。

```cpp
int f[30010][25][21];
int _2[25], _3[21];
extern "C" int _opt(int n, int x, int y)
{
  for (int i = 0; i <= 16; i ++)
    _2[i] = 1 << i;
  _3[0] = 1;
  for (int i = 1; i <= 11; i ++)
    _3[i] = _3[i - 1] * 3;
  for (int i = n; ~i; i --)
    for (int j = 16; ~j; j --)
      for (int k = 11; ~k; k --)
        if (_2[j] * _3[k] + i >= n)
          f[i][j][k] = 0;
        else
        {
          if (!f[i][j + 1][k])
            f[i][j][k] = 2;
          else if (!f[i][j][k + 1])
            f[i][j][k] = 3;
          else if (!f[i + _2[j] * _3[k]][0][0])
            f[i][j][k] = 1;
          else
            f[i][j][k] = 0;
        }
  int __2 = 0, __3 = 0;
  for (; x && x % 2 == 0; x >>= 1, __2 ++)
    ;
  for (; x && x % 3 == 0; x /= 3, __3 ++)
    ;
  return f[y][__2][__3];
}
```

---

## 作者：Alex_Wei (赞：3)

> [P6612 [POI2012]LIC-Bidding](https://www.luogu.com.cn/problem/P6612)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

注意到 $x$ 只有可能是 $2^a3^b$ 的形式，因此 $x$ 的数量级为 $\log ^ 2 n$。

将 $x$ 离散化，直接暴力 DP 每个 $(x,y)$ 是必胜还是必败态，注意转移时枚举变量的顺序，时间复杂度线性对数。

```cpp
const int N = 3e4 + 5;
int I, cnt, f[N >> 8][N], buc[N], rev[N];
void Init(int n) {
	for(int i = 1; i < n; i++) {
		int t = i;
		while(!(t & 1)) t >>= 1;
		while(!(t % 3)) t /= 3;
		if(t == 1) rev[cnt] = i, buc[i] = cnt++;
	}
	for(int y = n - 1; ~y; y--)
		for(int p = cnt - 1; ~p; p--) {
			int x = rev[p];
			if(x + y >= n) continue;
			if(1 + x + y >= n || x * 2 + y >= n || x * 3 + y >= n) f[p][y] = 1; // f[i][j] = 1 表示 (i, j) 是必胜态
			else if(!f[buc[1]][x + y] || !f[buc[x << 1]][y] || !f[buc[x * 3]][y]) f[p][y] = 1;
		}
		
}
extern "C" int _opt(int n, int x, int y) {
	if(!I) Init(n), I = 1;
	if(1 + x + y >= n || !f[buc[1]][x + y]) return 1; // 找到一个必败态给后手
	if(x * 2 + y >= n || !f[buc[x << 1]][y]) return 2;
	if(x * 3 + y >= n || !f[buc[x * 3]][y]) return 3;
}
```

有啥不懂的可以私信问（大雾）。

---

## 作者：N1K_J (赞：1)

幽默交互题，难度一大半在找是哪被这个 byd 交互库判成 Hack 了。

考虑一个显然的 dp：记 $dp_{x,y}$ 表示当前最优解。

$$dp_{x,y}=\begin{cases}0 & x+y \ge n\\1 & dp_{1,x+y}=0\\2 & dp_{2x,y}=0 \\3 & dp_{3x,y}\end{cases}$$

复杂度 $O(n^2)$，过不了一点。

但是注意到 $x$ 可以表示为形如 $x = 2^a \cdot 3^b,a \le 15,b \le 10$。

这样一来用 $2,3$ 的幂次来替换掉 $x$，复杂度降为 $O(n\log^2n)$。

注意一些小细节避免被判成 hack 交互库。

```cpp
#include<bits/stdc++.h>
int dp[30010][20][20];
int pw2[20],pw3[20];
bool tag = 0;
extern "C" int _opt(int n, int x, int y){
	if(!tag){
		tag = 1;
		pw2[0] = 1;for(int i = 1; i <= 18; i++) pw2[i] = pw2[i-1]*2;
		pw3[0] = 1;for(int i = 1; i <= 12; i++) pw3[i] = pw3[i-1]*3;
		for(int k = n; k >= 0; k--){
			for(int i = 15; i >= 0; i--) for(int j = 10; j >= 0; j--){
				if(pw2[i]*pw3[j]+k>=n) dp[k][i][j] = 0;
				else {
					if(dp[k][i+1][j]==0) dp[k][i][j] = 2;
					if(dp[k][i][j+1]==0) dp[k][i][j] = 3;
					if(dp[k+pw2[i]*pw3[j]][0][0]==0) dp[k][i][j] = 1;
				}
			}
		}
	}
	if(x+y>=n) return 1;
	int s = 0,t = 0;
	while(x%pw2[s+1]==0) s++;
	while(x%pw3[t+1]==0) t++;
	return dp[y][s][t];
}
```

---

## 作者：allen2010 (赞：0)

可以考虑设 $dp_{x,y}$ 表示在该 $x$ 和 $y$ 的情况下我们应该采取的操作，为 0 表示该状态已经输了或必输。每次转移到必输态（即让交互库输）。即：

- 当前已经输了就为 0。
- 如果 $dp_{1,x+y}$ 为 0 就为 1。
- 如果 $dp_{2x,y}$ 为 0 就为 2。
- 如果 $dp_{3x,y}$ 为 0 就为 3。

后三种状态显然没有先后顺序，有多个满足时任选一个。

但是，从数据范围来看，既 MLE 又 TLE 了。~~敏锐地~~观察到三种操作导致 $x$ 的变化，每次操作只会乘 2 或乘 3 或改为 1，可以发现这样 $x$ 只可能有质因数 2 和 3，可以把状态拆成 $dp_{i,j,y}$ 表示 $x=2^i \times 3^j$ 时的状态，并预处理 2 和 3 的幂，这样就不会超时了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[20][20][60007];
int a[20],b[20];
extern "C" int _opt(int n, int x, int y)
{
    if(a[0]!=1)
    {
        a[0]=b[0]=1;
        for(int i=1;i<=15;i++) a[i]=a[i-1]*2;
        for(int i=1;i<=10;i++) b[i]=b[i-1]*3;
        for(int i=n;i>=0;i--)
        {
            for(int j=15;j>=0;j--)
            {
                for(int k=10;k>=0;k--)
                {
                    if(a[j]*b[k]+i>=n) dp[j][k][i]=0;
                    else{
                        if(dp[0][0][i+a[j]*b[k]]) dp[j][k][i]=1;
                        if(dp[j+1][k][i]) dp[j][k][i]=2;
                        if(dp[j][k+1][i]) dp[j][k][i]=3;
                    }
                }
            }
        }
    }
    if(x+y>=n) return 1;
    int r=0,s=0;
    while(x%2==0) r++,x/=2;
    while(x%3==0) s++,x/=3;
    return dp[r][s][y];
}
```
注意事项：

1. 预处理时**不要把枚举幂次的范围开大了**。
2. 谨慎编写代码，小心返回非法操作。
3. 如果你 RE 了，看看提示，**也有可能是你的数组超界了**。
4. 样例交互库也挺有用的。

---

## 作者：EllinY (赞：0)

# 思路
博弈题目，可以使用递归，如果本轮先手做完某个操作后，可以使下一轮的操作人必败，则此轮做这个操作可以使先手必胜。相应地，如果本轮无论做哪种操作都无法使下一轮的人必败（即下一轮的人有策略必胜），则当前状态必败。所以可以用 `int _opt(int n,int x,int y)` 作为这个递归函数，如果有必胜策略返回操作编号，如果没有返回 $-1$。终止状态就是 $x+y\ge n$，此时只能做完操作 $1$ 之后输掉游戏，返回 $-1$。$\\$ 但是这样会把同一个状态多次走到并且一直递归到底，超时。所以考虑使用 $rec_{i,j}$ 记录 $x=i,y=j$ 时的`_opt`返回值，可是 $30000\times30000$ 太大。观察一下操作，$x$ 要么变成 $1$，要么 $\times2$ 或 $\times3$，所以 $x$ 一定是这种形式：$2^i·3^j$（$x$ 的初始值是 $1$，任何一个状态的 $x$ 都是从 $1$ 乘上来的）。所以可以用 $rec_{i,j,k}(0\le i<15,0\le j<10,0\le k\le 30000)$ 表示 $x=2^i·3^j,y=k$ 的 `_opt` 返回值。
# 代码
关于这道交互题：
1. 如果用了 `pair` 这类东西，要写一下万能头。
2. 评测机不会给你一个初始的 $x,y$ 使得 $x+y\ge n$（在讨论区看到的，我试过了，加上这个判断没有改变结果）。
3. 内存超限或是其他错导致的 `RE`，会判成 `You tried to hack`。
```cpp
#include<bits/stdc++.h>
using namespace std;
short rec[15][10][30005];
int cnt;
pair<int,int> change(int x){//把 x 转化为 i,j 的形式
	pair<int,int> p=make_pair(0,0);
	while(x%2==0){
		x/=2;
		p.first++;
	}
	while(x%3==0){
		x/=3;
		p.second++;
	}
	return p;
}
extern "C" int _opt(int n,int x,int y){
	pair<int,int> p=change(x);
	if(x+y>=n) return -1;
	if(rec[p.first][p.second][y])
		return rec[p.first][p.second][y];
	int flag1=_opt(n,1,x+y),flag2=_opt(n,2*x,y),flag3=_opt(n,3*x,y);
	if(flag1==-1) rec[p.first][p.second][y]=1;
	else if(flag2==-1) rec[p.first][p.second][y]=2;
	else if(flag3==-1) rec[p.first][p.second][y]=3;
	else rec[p.first][p.second][y]=-1;
	return rec[p.first][p.second][y];
}
```

---

## 作者：maruize (赞：0)

我第一道交互题。

### 直接dp

$f_{x,y}$表示面对$(x,y)$时是否能赢。

$g_{x,y}$表示面对$(x,y)$时如果能赢的走法。

$f_{x,y}$

- $x+y\ge n$ := _lose_
- _else_ := $ !f_{1,x+y} | !f_{2\times x,y} |!f_{3\times x,y}$

$g$跟着$f$一起转移。

开不下？

---

$ \ $
$ \ $
$ \ $
$ \ $
$ \ $
$ \ $


直接map。

别忘了记忆化搜索。  ~~好没有技术含量~~

---

**$\color{blue}{code}:$**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
map<int,bool>f[70050];
map<int,int>g[70005];//要多开些，要不RE。
int n;
bool dp(int x,int y){
	if(f[x].count(y))return f[x][y];
	//if(y>=n)return f[x][y]=1;
	if(x+y>=n)return f[x][y]=0;
	if(!dp(1,x+y))return g[x][y]=1,f[x][y]=1;
	if(!dp(2*x,y))return g[x][y]=2,f[x][y]=1;
	if(!dp(3*x,y))return g[x][y]=3,f[x][y]=1;
	return f[x][y]=0;
}
bool uninited=1;
void init(int _n){
	n=_n;
	dp(1,0);
//	if(f[1][0]==0)while(1);
	uninited=0;
}
extern"C" int _opt(int _n,int x,int y){
	if(uninited)init(_n);
	/*
	if(g[x][y]==-1)while(1);
	int o=g[x][y];
	if((x+y>=n&&o>1)||(o>0&&o<4));
	else while(1);
	*/
	return g[x][y];
}
```

---

