# Cleaning Robot

## 题目描述

Consider a hallway, which can be represented as the matrix with $ 2 $ rows and $ n $ columns. Let's denote the cell on the intersection of the $ i $ -th row and the $ j $ -th column as $ (i, j) $ . The distance between the cells $ (i_1, j_1) $ and $ (i_2, j_2) $ is $ |i_1 - i_2| + |j_1 - j_2| $ .

There is a cleaning robot in the cell $ (1, 1) $ . Some cells of the hallway are clean, other cells are dirty (the cell with the robot is clean). You want to clean the hallway, so you are going to launch the robot to do this.

After the robot is launched, it works as follows. While at least one cell is dirty, the robot chooses the closest (to its current cell) cell among those which are dirty, moves there and cleans it (so the cell is no longer dirty). After cleaning a cell, the robot again finds the closest dirty cell to its current cell, and so on. This process repeats until the whole hallway is clean.

However, there is a critical bug in the robot's program. If at some moment, there are multiple closest (to the robot's current position) dirty cells, the robot malfunctions.

You want to clean the hallway in such a way that the robot doesn't malfunction. Before launching the robot, you can clean some (possibly zero) of the dirty cells yourself. However, you don't want to do too much dirty work yourself while you have this nice, smart (yet buggy) robot to do this. Note that you cannot make a clean cell dirty.

Calculate the maximum possible number of cells you can leave dirty before launching the robot, so that it doesn't malfunction.

## 说明/提示

In the first example, you can clean the cell $ (1, 2) $ , so the path of the robot is $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) $ .

In the second example, you can leave the hallway as it is, so the path of the robot is $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) $ .

In the third example, you can clean the cell $ (1, 2) $ , so the path of the robot is $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 3) \rightarrow (2, 4) \rightarrow (1, 4) $ .

In the fourth example, the hallway is already clean. Maybe you have launched the robot earlier?

## 样例 #1

### 输入

```
2
01
11```

### 输出

```
2```

## 样例 #2

### 输入

```
2
01
01```

### 输出

```
2```

## 样例 #3

### 输入

```
4
0101
1011```

### 输出

```
4```

## 样例 #4

### 输入

```
4
0000
0000```

### 输出

```
0```

## 样例 #5

### 输入

```
5
00011
10101```

### 输出

```
4```

## 样例 #6

### 输入

```
6
011111
111111```

### 输出

```
8```

## 样例 #7

### 输入

```
10
0101001010
1010100110```

### 输出

```
6```

# 题解

## 作者：MSqwq (赞：11)

好题但无人写题解（？）  
本题芝士点：分类讨论思想和简单线性 DP  

题意：  
现有 $2 \times n$ 的地面，两点之间的距离采用曼哈顿距离计算距离。现在一些地方有垃圾需要清理，扫地机器人从左上角 $(1,1)$ 开始，它将检索最近的垃圾，选择最近的道路到达此处并清理。但是，如果有多个同样近的垃圾，机器人就报废了。问至少要预先清理多少垃圾，才能使得机器人在清扫剩余垃圾的过程中不会报废。  

题解：  
开这题的时候感觉很原，感觉可以推广到 $n \times m$ 。。。  
对于本题，考虑 DP 处理，设 $f_{x,y}$ 表示从第 $x$ 行第 $y$ 列开始（不计前 $ y-1$ 列的垃圾），最少需要预先清理的垃圾数量。  其中 $r\in\{0,1\}$ ， $c\in [0,n) $ ，不难可以发现一共有四种情况： 

如果第 $x\oplus1$ 行第 $y$ 列没有垃圾   
该列的清扫无需移动机器人的位置，则有 $f_{x,y} = f_{x,y+1}$ 。

如果第 $x\oplus1$ 行第 $y$ 列有垃圾分两大类讨论   

首先是若第 $x$ 行第 $y+1$ 列没有垃圾  
可以预先清理第 $x\oplus1$ 行第 $y$ 列，则无需移动，当然也可以让机器人来清理（这会移动横坐标），所以有 $f_{x,y}=\min(1+f_{x, y+1}, f_{x\oplus1,y+1}) $   

其次若第 $x$ 行第 $y+1$ 列有垃圾，则还需分两小类讨论  
第一如果第 $x\oplus1$ 行第 $y+1$ 列有垃圾，可以预先清理一个垃圾，最终位置在第 $x\oplus1$ 行 $y+1$ 列。也可以预先清理两个垃圾，最终位置在第 $x$ 行 $y+1$ 列,没有必要全部预先清理。所以有 $f_{x,y}=\min(f_{x\oplus1, y+2}+1, f_{x,y+2} + 2)$   
第一如果第 $x\oplus1$ 行第 $y+1$ 列没有垃圾，可以预先清理一个垃圾，最终位置可以在 $x\oplus1$ 行，也可以在 $x$ 行。所以有 $f_{x,y}=\min(f_{x\oplus1, y+2} + 1, f_{x,y+2} + 1)$  

为了防止读者和笨笨的 ms 一样被这题的分类讨论搅浑了脑子， 笨笨的 ms 画了图帮助大家理解  

![](https://3wt.img.zlkj.icu/2022/11-11/3b14a731726f496783c5c57bc891aa7b3wcn351256.jpeg)   

最后代码如下（仅供参考喵）：  
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<functional>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=2e5+10;
int f[N][2];
int main()
{
	int n=read();
	string a[2];
	cin>>a[0]>>a[1];
	a[0]="0"+a[0],a[1]="0"+a[1];
	int sum=0;
	for(int i=1;i<=n;i++)sum+=(a[0][i]=='1')+(a[1][i]=='1');
	for(int j=n-1;j>=0;j--)
	{
		for(int i=0;i<=1;i++)
		{
			if(a[i^1][j]=='0')f[i][j]=f[i][j+1];
			else if(a[i][j+1]=='0')f[i][j]=min(f[i^1][j+1],f[i][j+1]+1);
			else if(a[i^1][j+1]=='0')f[i][j]=min(f[i^1][j+2]+1,f[i][j+2]+1);
			else f[i][j]=min(f[i][j+2]+2,f[i^1][j+2]+1);
		}
	}
	printf("%d\n",sum-f[0][0]);
	return 0;
}
```


---

## 作者：Alex_Wei (赞：7)

首先，因为只有两列且机器人只会向最近的格子移动，所以机器人一定不会向左移动。

对于前 $i$ 列，我们只关心机器人在清扫完毕后的行，设为 $j$。转移到第 $i + 1$ 列时，如果两行都没有或只有第 $j$ 行有，则保持 $j$ 不变。否则机器人要么走到 $(i, j \oplus 1)$，要么先走到 $(i, j)$ 再走到 $(i, j\oplus 1)$，这两种情况均要求 $(i + 1, j)$ 为空，否则机器人会爆炸，我们在 DP 时记录下一列的每一行（实际上只关心第 $j\oplus 1$ 行）是否必须为空即可。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1739/submission/184449349)。

---

## 作者：灵茶山艾府 (赞：5)

目前已有题解（包括官方题解）都写得很麻烦，我来提供一个简单的思路和简洁的写法。

不失一般性，假设机器人在第一行（上面那行）。

**情况一**：无论机器人下方是否有污渍，都可以让机器人向右走。

- 如果机器人下方没有污渍，那么机器人只能向右走。（或者说只需考虑向右走）
- 如果机器人下方有污渍，那么我们擦掉污渍，机器人就只能向右走了。

**情况二**：如果机器人下方有污渍，可以让机器人向下走。

- 如果机器人右边没有污渍，那么机器人只能向下走。
- 如果机器人右边有污渍，那么我们擦掉污渍，机器人就只能向下走了。
- 机器人向下走后，下一步一定向右走，并且（因为我们擦掉了污渍）**下下一步也是向右走**。这个性质很有用，我们无需额外用一个参数记录「擦掉了右边的污渍」。

下面计算我们自己最少要擦掉多少污渍。

定义 $f_{j,i}$ 表示机器人在 $i$ 行 $j$ 列时，我们自己最少要擦掉多少污渍。（下标从 $0$ 开始）

- 情况一：$f_{j,i} = f_{j+1,i} + a_{i\oplus 1, j}$。
- 情况二：如果 $a_{i\oplus 1, j}=1$，那么有 $f_{j,i} = f_{j+2,i\oplus 1} + a_{i, j+1}$。

两种情况取最小值，就是 $f_{j,i}$。

初始值：$f_{n-1,i} = f_{n,i} = 0$。

答案：$\texttt{1}$ 的总个数减去 $f_{0,0}$，因为一开始在 $(0,0)$。

AC 代码（Golang）：

```go
package main
import("bufio";."fmt";"os";."strings")

func main() {
	var n int
	a := [2]string{}
	Fscan(bufio.NewReader(os.Stdin), &n, &a[0], &a[1])
	f := make([][2]int, n+1)
	for j := n - 2; j >= 0; j-- {
		for i := range 2 {
			f[j][i] = f[j+1][i] + int(a[i^1][j]&1)
			if a[i^1][j] == '1' {
				f[j][i] = min(f[j][i], f[j+2][i^1]+int(a[i][j+1]&1))
			}
		}
	}
	Print(Count(a[0], "1") + Count(a[1], "1") - f[0][0])
}
```

时间复杂度：$\mathcal{O}(n)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：hegm (赞：3)

### [Cleaning Robot](https://www.luogu.com.cn/problem/CF1739E)

考虑 $dp$ 状态

$dp_{i,0/1}$ 表示我清理完**后** $i$ 列，最后状态在 第一行/第二行。

发现我们到某一行有两种情况，并且对当前这一行有影响的只有后面的两列。

考虑分情况讨论。

假设我们在 $(i,j)$。

1. 如果 $(i,j\oplus1)$ 没有。

那么我可以直接去下一行不受影响。

$dp_{i,j}=dp_{i+1,j}$

![z5bZef.png](https://s1.ax1x.com/2022/12/14/z5bZef.png)

2. 如果 $i,j\oplus 1$ 有但是第 $i+1$ 列都没有。

两种选择，将另一行上的手动清理掉，或者不清理，让机器人自己转移到另一行。

$dp_{i,j}=\min({{\color{blue}dp_{i+1,j\oplus1}},{\color{Purple}dp_{i+1,j}+1}})$

（对应同颜色路径）

![z5bmTS.png](https://s1.ax1x.com/2022/12/14/z5bmTS.png)

3. 如果 $i,j\oplus 1$ 和 $i+1,j\oplus 1$ 有，但 $i+1,j$ 没有。

和 $\text{2}$ 相同，因为 $(i+1,j\oplus1)$ 是否有不会对我的 $\text{2}$ 抉择造成任何影响，所以不用考虑。

4. 如果 $i,j\oplus 1$ 和 $i+1,j$ 有，但 $i+1,j\oplus1$ 没有。

此时出现了矛盾点，必须清除其中的一个。

$dp_{i,j}=\min{({\color{Gold}dp_{i+1,j\oplus1}+1},{\color{blue}{dp_{i+2,j}+1}})}$

![z5OTn1.png](https://s1.ax1x.com/2022/12/14/z5OTn1.png)

5. 如果这三处地方都有。

![pAXH5dJ.png](https://s21.ax1x.com/2024/12/23/pAXH5dJ.png)

这时我们有三条路线，两种情况。

如果我不想换行，就说明我要把另外两个都手动删掉。 

否则我可以选择从上面绕，还是从下面绕

但是不难发现，橙色的路线存在问题，就是如果在问号所在地有一处垃圾，那就说明 $(i+1,j)$ 是不能走的，也就是说我们无法预测这里的状态，但是不用担心，我们观察紫色的路线，发现他和橙色的终点一样，也就是说两种路线造成的影响以及花费其实是相同的，因此我们完全不用在意橙色路线，无脑选择紫色即可。

同时我们依然存在情况二的蓝色路径。

$dp_{i,j}=\min{({\color{purple}dp_{i+2,j\oplus1}+1},{\color{blue}{dp_{i+2,j}+2}})}$

综上转移即可。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,mp[N][3],f[N][3],sum;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)mp[i][0]=getchar()-'0';
	getchar();
	for(int i=1;i<=n;i++)mp[i][1]=getchar()-'0';
	for(int i=1;i<=n;i++)sum+=mp[i][0]+mp[i][1];
	for(int i=n-1;i>=0;i--)
	{
		for(int j=0;j<2;j++)
		{
			if(mp[i][j^1]==0)f[i][j]=f[i+1][j];
			else
			{
				if(mp[i+1][j]==0)f[i][j]=min(f[i+1][j^1],f[i+1][j]+1);
				else if(mp[i+1][j^1]==0)f[i][j]=min(f[i+2][j],f[i+2][j^1])+1;
				else f[i][j]=min(f[i+2][j]+2,f[i+2][j^1]+1);
			}
		}
	}
	cout<<sum-f[1][0]<<"\n";
	return 0;
}

```

---

## 作者：fanypcd (赞：3)

CF 上好像有很多在 $2 \times n$ 的图上玩出花的恶心 dp。。。

懒得分类，于是暴力设状态 $f_{0/1,i,0/1,0/1}$ 表示机器人走到第 $i$ 列上/下位置，且第 $i+1$ 列是否手动清理状态为 $0/1,0/1$ 的最小的手动清理次数。

然后枚举上一个位置（上、下），当前位置清理状态，当前位置（上、下），下一个位置清理状态，暴力判断能否转移即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while(!isdigit(ch))
		f |= ch == '-', ch = getchar();
	while(isdigit(ch))
		x = x * 10 + ch - 48, ch = getchar();
	x = f ? -x : x; return;
}
#define inf 0x3f3f3f3f
#define ll long long
#define fir first
#define sec second
#define N 200005
int n;
char s[2][N];
int f[2][N][2][2];
inline bool chk(int p, int w, int s0, int s1, int t0, int t1) {
	if(p == 0) {
		if(w == 0) {
			return !s1;
		}
		else {
			return s1 && !(s1 && t0);
		}
	}
	else {
		if(w == 0) {
			return s0 && !(s0 && t1);
		}
		else {
			return !s0;
		}
	}
	return 0;
}
inline void upd(int &x, int y) {
	x = min(x, y); return;
}
inline void trs(int i) {
	for(int p0 = 0; p0 < 2; p0++) {
		for(int p1 = 0; p1 < 2; p1++) {
			int s0 = p0 ? 0 : s[0][i] == '1';
			int s1 = p1 ? 0 : s[1][i] == '1';
			for(int n0 = 0; n0 < 2; n0++) {
				for(int n1 = 0; n1 < 2; n1++) {
					int t0 = n0 ? 0 : s[0][i + 1] == '1';
					int t1 = n1 ? 0 : s[1][i + 1] == '1';
					if(chk(0, 0, s0, s1, t0, t1))
						upd(f[0][i][n0][n1], f[0][i - 1][p0][p1] + n0 + n1);
					if(chk(0, 1, s0, s1, t0, t1))
						upd(f[1][i][n0][n1], f[0][i - 1][p0][p1] + n0 + n1);
					if(chk(1, 0, s0, s1, t0, t1))
						upd(f[0][i][n0][n1], f[1][i - 1][p0][p1] + n0 + n1);
					if(chk(1, 1, s0, s1, t0, t1))
						upd(f[1][i][n0][n1], f[1][i - 1][p0][p1] + n0 + n1);
				}
			}
		}
	}
	return;
}
signed main() {
	read(n);
	scanf("%s %s", s[0] + 1, s[1] + 1);
	memset(f, 0x3f, sizeof(f));
	f[0][0][0][0] = 0;
	f[0][0][0][1] = 1;
	f[0][0][1][0] = 1;
	f[0][0][1][1] = 2;
	
	f[1][0][0][0] = inf;
	f[1][0][0][1] = inf;
	f[1][0][1][0] = inf;
	f[1][0][1][1] = inf;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		cnt += (s[0][i] == '1') + (s[1][i] == '1');
		trs(i);
	}
	printf("%d", cnt - min(f[0][n][0][0], f[1][n][0][0]));
	return 0;
}
```

---

## 作者：Felix72 (赞：3)

首先我们要知道，两个脏格子同时成为选择，仅在他们横竖坐标都相差一才可能出现，这个很好证明。

知道了这个性质，我们发现对决策有影响的只有机器人所在的列和后一列的脏格子。那么它前面的呢？由于这个矩阵长只有二，所以它前面的列肯定被打扫完了，不用考虑。

所以我们只需要记录有影响的几个数据，记搜或动规即可。此处使用记搜实现。

需要注意的是，如果当前列没有脏格子了，那么往后一列走就行，因为无论下一个脏格子在哪，这肯定是最短路。但不要随意走到另一行，因为这不一定是最短路，对答案有影响。

```
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int n, a[N][3], f[N][3][3][3][3], cnt, b[N][3], tot;
bool vis[N][3][3][3][3];
inline int dfs(int now, int pos, int cur, int nxt1, int nxt2)
{
	if(vis[now][pos][cur][nxt1][nxt2])
	{
		return f[now][pos][cur][nxt1][nxt2];
	}
	if(now == cnt) return 0;
	int ans = 0x3f3f3f3f;
	if(pos == 1)
	{
		if(cur == 1)
		{
			if(nxt1 == 1)
			{
				ans = min(ans, 1 + dfs(now + 1, 1, nxt2, b[now + 2][1], b[now + 2][2]));
				ans = min(ans, 1 + dfs(now, 2, 0, 0, nxt2));
			}
			else
			{
				ans = min(ans, dfs(now, 2, 0, nxt1, nxt2));
				ans = min(ans, 1 + dfs(now + 1, 1, nxt2, b[now + 2][1], b[now + 2][2]));
			}
		}
		else
		{
			ans = min(ans, dfs(now + 1, 1, nxt2, b[now + 2][1], b[now + 2][2]));
		}
	}
	else
	{
		if(cur == 1)
		{
			if(nxt2 == 1)
			{
				ans = min(ans, 1 + dfs(now + 1, 2, nxt1, b[now + 2][1], b[now + 2][2]));
				ans = min(ans, 1 + dfs(now, 1, 0, nxt1, 0));
			}
			else
			{
				ans = min(ans, dfs(now, 1, 0, nxt1, nxt2));
				ans = min(ans, 1 + dfs(now + 1, 2, nxt1, b[now + 2][1], b[now + 2][2]));
			}
		}
		else
		{
			ans = min(ans, dfs(now + 1, 2, nxt1, b[now + 2][1], b[now + 2][2]));
		}
	}
	vis[now][pos][cur][nxt1][nxt2] = true;
	f[now][pos][cur][nxt1][nxt2] = ans;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n; cnt = n;
	for(int i = 1; i <= 2; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			char c; cin >> c;
			b[j][i] = c - '0';
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		tot += b[i][1] + b[i][2];
	}
	memset(f, 0x3f, sizeof(f));
	cout << tot - dfs(1, 1, b[1][2], b[2][1], b[2][2]) << '\n';
	return 0;
}
```

---

## 作者：Mashu77 (赞：0)

题意：考虑一个走廊，它可以表示为 $2$ 行 $n$ 列的矩阵。让我们将第 $i$ 行和第 $j$ 列相交处的单元格表示为 $(i,j)$。

机器人启动后，其工作方式如下。当至少有一个单元脏时，

机器人在脏单元中选择最接近（当前单元）的单元，移动到那里并清洗。

我们的任务是清洗某些脏单元，使得机器人在脏单元中选择最接近（当前单元）的单元，答案都唯一。

请给出最后机器人清洗脏单元最大数量。

题解：
考虑 DP。

$f[i][j]$ 为 $i$ 列之后的清洗脏单元数量。

$f[i][1]$ 二行向右一格。

$f[i][2]$ 二行向右上两格。

$f[i][3]$ 一行向右下两格。

$f[i][0]$ 一行向右一格。

```cpp
#include "stdafx.h"
#include <iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<set>
#include< map>
 #include<vector>
using namespace std;
typedef long long ll;

int  n;
int a[3][200005],f[200005][4],pre[200005][4];

int main(){

 	 FILE *fi;
	freopen_s(&fi,"CF1739Ein.txt","r",stdin);

	ios::sync_with_stdio(false);

		cin >> n;
		for(int i = 1;i <= 2;i ++){
			for(int j = 1;j <= n;j ++){
				char ch;
				cin >> ch; a[i][j] = ch - '0';
			}
		}
		int ans = 0;
		for(int i = 0;i < 4;i ++) f[1][i] = pre[1][i] = f[0][i] = pre[0][i] = -0x3f ;
		f[1][0] = pre[1][0] = 0;

		if(a[2][1]) f[1][3] = pre[1][3] = ans = 1;
		//0101
		//1011
			for(int j = 0;j < 4;j ++)
				cout<<", \t j="<<j<<",  f[1][j]="<<f[1][j];
			cout<<endl;

		for(int i = 2;i <= n;i ++){
			for(int j = 0;j < 4;j ++)
				cout<<", \t    pre[i - 1][j]="<<pre[i - 1][j];
			cout<<endl;
		//  f[i][1]二行向右一格
		// f[i][2]二行向右上两格
		// f[i][3]一行向右下两格
		// f[i][0]一行向右一格
			for(int j = 0;j < 4;j ++) f[i][j] = -0x3f ;
			if(a[1][i]){
				f[i][0] = max(f[i][0],pre[i - 1][0] + 1);	//一行继续向右
				f[i][0] = max(f[i][0],pre[i - 1][2] + 1);	//二行向右上后再向右
				// 二行向右后右上
				f[i][2] = max(f[i][2],pre[i - 1][1] + a[1][i] + a[2][i]);
				// 一行右下后跳行右上,
				// 机器人在脏单元中选择最接近（当前单元）的单元，答案都唯一。右下后邻行右上不允许
				f[i][2] = max(f[i][2],pre[i - 2][3] + a[1][i] + a[2][i]);
			}
			if(a[2][i]){
				f[i][1] = max(f[i][1],pre[i - 1][1] + 1);	//二行继续向右
				f[i][1] = max(f[i][1],pre[i - 1][3] + 1);	//一行向右下后再向右
				// 一行向右后右下
				f[i][3] = max(f[i][3],pre[i - 1][0] + a[1][i] + a[2][i]);
				// 二行右上后跳行右下
				f[i][3] = max(f[i][3],pre[i - 2][2] + a[1][i] + a[2][i]);
			}
			for(int j = 0;j < 4;j ++){
				pre[i][j] = max(pre[i - 1][j],f[i][j]);
				ans = max(ans,f[i][j]);

				cout<<", \t j="<<j<<",  f[i][j]="<<f[i][j];
			}
			cout<<endl;
		}
		cout << ans << '\n';

	return 0;
}

---

