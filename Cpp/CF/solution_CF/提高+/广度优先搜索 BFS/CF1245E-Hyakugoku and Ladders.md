# Hyakugoku and Ladders

## 题目描述

Hyakugoku has just retired from being the resident deity of the South Black Snail Temple in order to pursue her dream of becoming a cartoonist. She spent six months in that temple just playing "Cat's Cradle" so now she wants to try a different game — "Snakes and Ladders". Unfortunately, she already killed all the snakes, so there are only ladders left now.

The game is played on a $ 10 \times 10 $ board as follows:

- At the beginning of the game, the player is at the bottom left square.
- The objective of the game is for the player to reach the Goal (the top left square) by following the path and climbing vertical ladders. Once the player reaches the Goal, the game ends.
- The path is as follows: if a square is not the end of its row, it leads to the square next to it along the direction of its row; if a square is the end of its row, it leads to the square above it. The direction of a row is determined as follows: the direction of the bottom row is to the right; the direction of any other row is opposite the direction of the row below it. See Notes section for visualization of path.
- During each turn, the player rolls a standard six-sided dice. Suppose that the number shown on the dice is $ r $ . If the Goal is less than $ r $ squares away on the path, the player doesn't move (but the turn is performed). Otherwise, the player advances exactly $ r $ squares along the path and then stops. If the player stops on a square with the bottom of a ladder, the player chooses whether or not to climb up that ladder. If she chooses not to climb, then she stays in that square for the beginning of the next turn.
- Some squares have a ladder in them. Ladders are only placed vertically — each one leads to the same square of some of the upper rows. In order for the player to climb up a ladder, after rolling the dice, she must stop at the square containing the bottom of the ladder. After using the ladder, the player will end up in the square containing the top of the ladder. She cannot leave the ladder in the middle of climbing. And if the square containing the top of the ladder also contains the bottom of another ladder, she is not allowed to use that second ladder.
- The numbers on the faces of the dice are 1, 2, 3, 4, 5, and 6, with each number having the same probability of being shown.

Please note that:

- it is possible for ladders to overlap, but the player cannot switch to the other ladder while in the middle of climbing the first one;
- it is possible for ladders to go straight to the top row, but not any higher;
- it is possible for two ladders to lead to the same tile;
- it is possible for a ladder to lead to a tile that also has a ladder, but the player will not be able to use that second ladder if she uses the first one;
- the player can only climb up ladders, not climb down.

Hyakugoku wants to finish the game as soon as possible. Thus, on each turn she chooses whether to climb the ladder or not optimally. Help her to determine the minimum expected number of turns the game will take.

## 说明/提示

A visualization of the path and the board from example 2 is as follows: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1245E/43b532b250e8898c1ca20662157f9e4153d49da7.png)

The tile with an 'S' is the starting tile and the tile with an 'E' is the Goal.

For the first example, there are no ladders.

For the second example, the board looks like the one in the right part of the image (the ladders have been colored for clarity).

It is possible for ladders to overlap, as is the case with the red and yellow ladders and green and blue ladders. It is also possible for ladders to go straight to the top, as is the case with the black and blue ladders. However, it is not possible for ladders to go any higher (outside of the board). It is also possible that two ladders lead to the same tile, as is the case with the red and yellow ladders. Also, notice that the red and yellow ladders lead to the tile with the orange ladder. So if the player chooses to climb either of the red and yellow ladders, they will not be able to climb the orange ladder. Finally, notice that the green ladder passes through the starting tile of the blue ladder. The player cannot transfer from the green ladder to the blue ladder while in the middle of climbing the green ladder.

## 样例 #1

### 输入

```
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

### 输出

```
33.0476190476
```

## 样例 #2

### 输入

```
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 3 0 0 0 4 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 4 0 0 0
0 0 3 0 0 0 0 0 0 0
0 0 4 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 9
```

### 输出

```
20.2591405923
```

## 样例 #3

### 输入

```
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 6 6 6 6 6 6 0 0 0
1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

### 输出

```
15.9047592939
```

# 题解

## 作者：yuzhechuan (赞：2)

放个dp版的题解

---

### 题解：

方便起见，先将二维转成一维，终点为100,起点为1

设f[i]表示格子i到终点的期望步数，nxt[i]表示用梯子会到达的格子

初始f[100]=0

先考虑不能一步到的格子（93～1），转移为$f[i]=1+\frac{\sum_{j=1}^{6} \min(f[i+j],f[nxt[i+j]])}{6}$

（解释：+1表示要在上一种基础上多扔一次，除以6表示从每个上一种转移的概率都是$\frac{1}{6}$，min()表示可以靠老老实实走转移，也可以靠梯子转移）

再考虑能一步到的格子（99～94）

手算
$$f[99]=\frac{5(f[99]+1)}{6}+\frac{f[100]+1}{6}$$
（解释：$\frac{5}{6}$概率留原地,$\frac{1}{6}$概率到终点）

打开

$$\frac{f[99]}{6}=1$$

得到

$$f[99]=6$$

其他同理，可以得出99~94号格子都期望6步到达终点

最后答案就是f[1]

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

const int N=15;
int id[N][N],nxt[105],cnt;
double f[105];

signed main(){
	for(int i=10;i>=1;i--)
		if(i&1)
			for(int j=10;j>=1;j--) id[i][j]=++cnt;
		else
			for(int j=1;j<=10;j++) id[i][j]=++cnt; //id[i][j]表示从上到下第i行，从左到右第j列转成一维后的序号
	for(int i=1,x;i<=10;i++)
		for(int j=1;j<=10;j++)
			nxt[id[i][j]]=id[i-read(x)][j]; //nxt[i]表示第i格子会到哪，有梯子则指向梯子终点，否则指向自己
	for(int i=99;i>=94;i--) f[i]=6; //手算得出
	for(int i=93;i>=1;i--){
		for(int j=1;j<=6;j++)
			f[i]+=fmin(f[i+j],f[nxt[i+j]]); //转移
		f[i]=f[i]/6.0+1; //除以概率，加上代价
	}
	printf("%.10lf",f[1]);
}
```

---

## 作者：梧桐灯 (赞：1)

stO @[Binary_Search_Tree](https://www.luogu.org/space/show?uid=40985) Orz

这道题上来首先想到期望DP，然后发现对于一个格子只可能有两种情况：要么走梯子，要么走到下一个格子。

显然，首先预处理nx数组表示这个点**不走梯子**经过的下一个点是什么。然后开始记搜，对于一个点判断两种情况，然后特判终点与无法掷满1~6（即距离终点只剩1~5步）的情况算期望即可

代码：

```
#pragma GCC optimize(2)
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define MP make_pair
using namespace std;
 
typedef double D;
const int N = 13, n = 10;
int a[N][N];
pair <int, int> nx[N][N];
D f[N][N];
 
D dfs (const int x, const int y) {
	if (x == 1 && y == 1) return 0;
	if (f[x][y] >= 0) return f[x][y];
	f[x][y] = 0;
	register int sx = x, sy = y;
	int k = 0;
	for (register int What = 1; What <= 6; ++What) {
		if (sx == 1 && sy == 1) {
			k = 7 - What;
			break;
		} //判断特殊情况
		int p = nx[sx][sy].first, q = nx[sx][sy].second;
		sx = p, sy = q;
		if (a[sx][sy]) f[x][y] += min (dfs (sx - a[sx][sy], sy), dfs (sx, sy)); //肯定选期望步数少的
		else f[x][y] += dfs (sx, sy);
	}
	return f[x][y] = (f[x][y] + 6) / (6.0 - k); //计算期望
}
 
int main () {
	int i, j;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			f[i][j] = -100;
			scanf ("%d", &a[i][j]);
			if (i & 1) {
				if (j == 1)
					nx[i][j] = MP (i - 1, j);
				else
					nx[i][j] = MP (i, j - 1);
			}
			else {
				if (j == 10)
					nx[i][j] = MP (i - 1, j);
				else
					nx[i][j] = MP (i, j + 1);
			}
		}
	} //预处理nx数组
	printf ("%.10lf\n", dfs (10, 1));
	return 0;
}
```

---

