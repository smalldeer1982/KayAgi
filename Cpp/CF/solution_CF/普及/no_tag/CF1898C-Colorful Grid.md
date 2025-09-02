# Colorful Grid

## 题目描述

Elena has a grid formed by $ n $ horizontal lines and $ m $ vertical lines. The horizontal lines are numbered by integers from $ 1 $ to $ n $ from top to bottom. The vertical lines are numbered by integers from $ 1 $ to $ m $ from left to right. For each $ x $ and $ y $ ( $ 1 \leq x \leq n $ , $ 1 \leq y \leq m $ ), the notation $ (x, y) $ denotes the point at the intersection of the $ x $ -th horizontal line and $ y $ -th vertical line.

Two points $ (x_1,y_1) $ and $ (x_2,y_2) $ are adjacent if and only if $ |x_1-x_2| + |y_1-y_2| = 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1898C/6c3cb21cf557af9dcb463c1e32ea40590620a065.png) The grid formed by $ n=4 $ horizontal lines and $ m=5 $ vertical lines.Elena calls a sequence of points $ p_1, p_2, \ldots, p_g $ of length $ g $ a walk if and only if all the following conditions hold:

- The first point $ p_1 $ in this sequence is $ (1, 1) $ .
- The last point $ p_g $ in this sequence is $ (n, m) $ .
- For each $ 1 \le i < g $ , the points $ p_i $ and $ p_{i+1} $ are adjacent.

Note that the walk may contain the same point more than once. In particular, it may contain point $ (1, 1) $ or $ (n, m) $ multiple times.

There are $ n(m-1)+(n-1)m $ segments connecting the adjacent points in Elena's grid. Elena wants to color each of these segments in blue or red color so that there exists a walk $ p_1, p_2, \ldots, p_{k+1} $ of length $ k+1 $ such that

- out of $ k $ segments connecting two consecutive points in this walk, no two consecutive segments have the same color (in other words, for each $ 1 \le i < k $ , the color of the segment between points $ p_i $ and $ p_{i+1} $ differs from the color of the segment between points $ p_{i+1} $ and $ p_{i+2} $ ).

Please find any such coloring or report that there is no such coloring.

## 说明/提示

In the first test case, one of the correct answers is shown in the picture below. The color-alternating walk of length $ 12 $ is highlighted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1898C/b1be0887b26038ecce64f350278435c139e51a92.png)In the second and the third test cases, it can be shown that there is no coloring satisfying the condition from the statement.

## 样例 #1

### 输入

```
5
4 5 11
3 3 2
3 4 1000000000
3 3 12588
4 4 8```

### 输出

```
YES
R R B B
R R R R
B B B R
R R B B
R B B R B
R B B B B
B B R R R
NO
NO
YES
R B
B B
B R
B B R
R B B
YES
B B R
R B R
B R R
R R B
B R R B
B B B B
B R R R```

# 题解

## 作者：_qingshu_ (赞：4)

# 题意:

给定一个 $n \times m$ 的网格，给出一种染色方案（仅存在两种颜色红色或者蓝色）使得存在一条长度为 $k$  的从 $(1,1)$ 到 $(n,m)$ 的路线满足该路线上相邻的边颜色均不相同。

# 思路：

### 首先考虑什么情况下是不可能有这么一条路径的。

- 第一种是需求路线长度无法支撑存在一条合法路线。

```
   ((n-1)+(m-1)>k)
```

- 第二种易证得如果想要在最短路径上加长路线只能构建一个环或者 ```U``` 形，这两者对应的增加贡献值明显的为 ```4``` 与 ```2```。如果我们需要增添的长度是奇数的话我们是无论如何都无法构成一条合法路线的。

```
   (k-(n-1)-(m-1))%2==1
```

### 在考虑存不存在一种通法使得构建出来的图一定满足要求。

首先我们在最边缘构建一条最短路线，构建方式就是简单的红蓝交替（在下文中，既定该路线是以红色开始）。

可以回到题面，得知 $3 \le n,m \le 16$。既然至少一定有个 $3 \times 3$ 大小的网格，我们可以考虑在第一行第二个小正方形上操作。（因为既然定义了开始为红色，要么会出现出发第一个为蓝色，要么会出现蓝色与蓝色相接），可以神奇的发现，将第二个小格子构成一个环后它是可以当作一个 ```U``` 字形使用的，那么我们就可以在这个地方绕圈来满足所有的合法需求。

为了方便代码构建，可以将除开最短路线的所有横线定义为蓝色，所有纵线定义为红色。

# code:

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
int t;
int n,m,k;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		if(n+m-2>k||(k-n-m+2)%2!=0){
			cout<<"NO"<<endl;
			continue;
		}
		else cout<<"YES"<<endl;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=(m-1);j++)
				if(i==1)
					if(j%2==1)cout<<"R ";
					else cout<<"B ";	
				else cout<<"B ";
			cout<<endl;
		}
		for(int i=1;i<=(n-1);i++){
			for(int j=1;j<=m;j++)
				if(j==m)
					if((m-1)%2==0)
						if(i%2==1)cout<<"R ";
						else cout<<"B ";
					else
						if(i%2==1)cout<<"B ";
						else cout<<"R ";
				else cout<<"R ";
			cout<<endl;
		}
	}
} 
```

update：

23.12.19：修改了有序列表使用有误（改为无序）。

---

## 作者：hytallenxu (赞：1)

## 题目大意
给定一个 $n\times m$ 的网格，给出一种染色方案（仅存在两种颜色红色或者蓝色）使得存在一条长度为 $k$ 的从 $(1,1)$ 到 $(n,m)$ 的路线满足该路线上相邻的边颜色均不相同。

## 思路

首先考虑无解的情况。

1. $ k<(m+n-2) $

从 $(1,1)$ 到 $(n,m)$ 的最短路径是 $(n-1)+(m-1)$。假如  $k$ 小于这个最短路径，则必定无解。

2. $ k-(m+n-2) \bmod 2=1$ （等价于 $ k-m-n \bmod 2=1$）

假如要在最短路径上进行绕路的话，多行走的距离必定是一个偶数（稍后会讲）。假如不是偶数，则无解。

让我们考虑有解的情况。


![](https://cdn.luogu.com.cn/upload/image_hosting/1l53ne1h.png)

在此图中，最短路径为 $(4-1)+(4-1)=6$。而假如 $(k-6) \bmod 2=0$ 的话，就有解。

下面的代码采用了以下的编程方式：

1. 先构造出一条由 $(1,1)$ 到 $(n,1)$ 的路径，然后再构造 $(n,1)$ 到 $(n,m)$ 的路径。

2. 在第一个小格子处，设置红蓝循环，并以 $(1,3)$ 为起点再做一次步骤 $1$（即构造最短路径）。

3. 剩余没用到的格子随便什么颜色都行。

4. ```arr[a][b][c][d]``` 表示由 $(a,b)$ 到 $(c,d)$ （保证是相邻格子）的填色。

## Code
```cpp
#include <iostream>
using namespace std;
int t;

inline int work(){
	int n,m,k;
	cin>>n>>m>>k;
	char arr[n+10][m+10][n+10][m+10]; 
	if(n+m-2>k or (k-n-m)&1) return cout<<"NO\n",0;
	else cout<<"YES\n";
	char begin='R';int i=1,j=1;
	while(i<=n-1){arr[i][j][i+1][j]=begin;if(begin=='R')begin='B';else begin='R';i++;}
	while(j<=m-1){arr[i][j][i][j+1]=begin;if(begin=='R')begin='B';else begin='R';j++;}
	arr[2][1][2][2]='B',arr[1][2][2][2]='R',arr[1][2][1][3]='B',i=1,j=3,begin='R';
	while(i<=n-1){arr[i][j][i+1][j]=begin;if(begin=='R')begin='B';else begin='R';i++;}
	while(j<=m-1){arr[i][j][i][j+1]=begin;if(begin=='R')begin='B';else begin='R';j++;}
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			if(arr[i][j][i][j+1]=='B' or arr[i][j][i][j+1]=='R') cout<<arr[i][j][i][j+1]<<" ";
			else{
				cout<<"B ";
			}
		}
		cout<<"\n";
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			if(arr[i][j][i+1][j]=='B' or arr[i][j][i+1][j]=='R') cout<<arr[i][j][i+1][j]<<" ";
			else{
				cout<<"B ";
			}
		}
		cout<<"\n";
	}
	return 0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>t;
	while(t--) work();
	return 0;
}
```



---

## 作者：UncleSam_Died (赞：1)

### 题目大意
已知有一个 $n$ 行 $m$ 列的网格图，如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1898C/6c3cb21cf557af9dcb463c1e32ea40590620a065.png)

现在规定一条可行路为一个点集 $p_1,p_2,\dots,p_k$，其中，$p_1$ 为点 $(1,1)$，$p_k$ 为点 $(n,m)$，相邻的两个点 $p_i$ 和 $p_{i+1}$ 之间的距离为 $1$，我们规定两个点之间的距离为 $|x_1-x_2|+|y_1+y_2|$。你需要对所有的边染成 `R` 或 `B` 这两种颜色，使得存在一条长度为 $k+1$ 的可行路（点集的大小为 $k+1$）满足路径上任意相邻的两条边的颜色不同，一个点（包括 $(1,1)$ 和 $(n,m)$）可以经过多次，如果不存在一种合法方案，输出 `NO`，否则输出 `YES`，并输出解决方案。

### 解题思路
很简单的一道模拟题，容易发现，最短路径的边长度之和为 $n+m-2$，那么相对于最短路而言，一条长度为 $k+1$ 的可行路的边长之和多了 $res=k-(n+m-2)$。很显然，任意一条路径不可能短于最短路，若 $res<0$ 直接输出 `NO` 即可。读者自己模拟以下就可以发现，不存在 $res$ 为奇数的情况，那么若 $res$ 为奇数，直接输出 `NO`，剩余情况易证均存在一个合法的方案。

我们发现，如果走一格的上半部分，那么会多出 $2$ 的长度，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/y8l8lvbt.png)

同样，如果绕一圈，那么会多出 $4$ 的长度，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7q2l88o3.png)

那么，我们可以考虑，如果 $res\bmod 4=0$，那么直接在终点处走 $\frac{res}{4}$ 圈即可，否则的话，那么我们先从上方走最后一格，增加 $2$ 的长度，然后走 $\frac{res-2}{4}$ 圈即可。

### 注意事项
注意题目中要求的输出格式以及走的顺序。

### AC 代码
码风较丑，不喜勿喷。
```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 20
int n,m,k;
char map1[N][N];
char map2[N][N];
inline void work(){
	scanf("%d%d%d",&n,&m,&k);
	int mint=n-1+m-1;
	if(k<mint){
		puts("No");
		return;
	}
	if((k-mint)&1){
		puts("No");
		return;
	}puts("Yes");
	int res=k-mint;
	for(register int i=1;i<=n;++i)
	for(register int j=1;j<=m;++j)
		map1[i][j]=map2[i][j]='R';
	int col=0;
	if(res%4==0){
		for(register int i=1;i<n;++i){
			col=col^1;
			if(col==1) 
				map2[i][1]='R';
			else map2[i][1]='B';
		}
		for(register int j=1;j<m;++j){
			col=col^1;
			if(col==1)
				map1[n][j]='R';
			else map1[n][j]='B';
		}
		col=col^1;
		if(col==1)
			map2[n-1][m]='R';
		else map2[n-1][m]='B';
		col=col^1;
		if(col==1)
			map1[n-1][m-1]='R';
		else map1[n-1][m-1]='B';
		col=col^1;
		if(col==1)
			map2[n-1][m-1]='R';
		else map2[n-1][m-1]='B';
	}else{
		for(register int i=1;i<n;++i){
			col=col^1;
			if(col==1) 
				map2[i][1]='R';
			else map2[i][1]='B';
		}
		for(register int j=1;j<m-1;++j){
			col=col^1;
			if(col==1)
				map1[n][j]='R';
			else map1[n][j]='B';
		}
		col=col^1;
		if(col==1)
			map2[n-1][m-1]='R';
		else map2[n-1][m-1]='B';
		col=col^1;
		if(col==1)
			map1[n-1][m-1]='R';
		else map1[n-1][m-1]='B';
		col=col^1;
		if(col==1)
			map2[n-1][m]='R';
		else map2[n-1][m]='B';
		col=col^1;
		if(col==1)
			map1[n][m-1]='R';
		else map1[n][m-1]='B';
	}
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<m;++j){
			if(j!=1) putchar(' ');
			putchar(map1[i][j]);
		}putchar('\n');
	}
	for(register int i=1;i<n;++i){
		for(register int j=1;j<=m;++j){
			if(j!=1) putchar(' ');
			putchar(map2[i][j]);
		}putchar('\n');
	}
}signed main(){
	srand(114514);
	srand(rand());
	srand(time(0));
	int T;scanf("%d",&T);
	while(T--) work();
	return 0;
}
```


---

## 作者：Msents (赞：1)

## 题意：

给你一个方格，你要在上面染上蓝色和红色，然后从左上角出发，恰好走 $k$ 步，最后到达右下角，求任意一种染色方案即可，或报告没有这样的方案。

## 思路：

乍一看是个毒瘤题，但思路没歪还是挺简单的。

考虑先走最短路，也就是每次向下或向右走，这需要走 $n+m-2$ 步。

如果 $k$ 比它小肯定是走不了的。

将 $k$ 和 $n+m-2$ 作差，相当于计算多走的路。

现在想怎么多走，有两种方法：
- 走个圈，也就是一个矩形，能多走四步。
- 在原来路径的基础上走出去一步，然后按原来路径的方向走一步，最后再往回走一步，能多走两步，相当于走个 `U` 字。

上面两种方法核心思想是抵消影响，两者配合能多走偶数步，如果我们走奇数步，那多走的一步就没法抵消，也就是走不了。

最后我们要构造一个方案，这里简单粗暴，先全填一个颜色，填好路径，在起点整一个环，在终点整一个 `U` 字就行了。

赛时代码：

```cpp20
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MaxN=16;
int n,m,k;
char a1[MaxN+1][MaxN+1],a2[MaxN+1][MaxN+1];
/*
1
4 5 9
*/
void Solve(){
	cin>>n>>m>>k;
	if(k<n+m-2){
		cout<<"NO\n";
		return;
	}else{
		if((k-(n+m-2))%4==0){
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m-1;j++)
					a1[i][j]='B';
			for(int i=1;i<=n-1;i++)
				for(int j=1;j<=m;j++)
					a2[i][j]='B';
			bool now=false;
			for(int j=1;j<=m-1;j++){
				a1[1][j]=(now?'R':'B');
				now^=1;
			}
			for(int i=1;i<=n-1;i++){
				a2[i][m]=(now?'R':'B');
				now^=1;
			}
			a1[2][1]='B';
			a2[1][1]='R';
			a2[1][2]='R';
		}else if((k-(n+m-2))%4==2){
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m-1;j++)
					a1[i][j]='B';
			for(int i=1;i<=n-1;i++)
				for(int j=1;j<=m;j++)
					a2[i][j]='B';
			bool now=false;
			for(int j=1;j<=m-1;j++){
				a1[1][j]=(now?'R':'B');
				now^=1;
			}
			for(int i=1;i<=n-1;i++){
				a2[i][m]=(now?'R':'B');
				now^=1;
			}
			a1[2][1]='B';
			a2[1][1]='R';
			a2[1][2]='R';
			
			a2[n-1][m-1]=a2[n-2][m];
			a1[n-1][m-1]=(a2[n-1][m-1]=='R'?'B':'R');
			a1[n][m-1]=(a2[n-1][m-1]=='R'?'B':'R');
		}else{
			cout<<"NO\n";
			return;
		}
		cout<<"YES\n";
		for(int i=1;i<=n;i++,cout<<'\n')
			for(int j=1;j<=m-1;j++)
				cout<<a1[i][j]<<' ';
		for(int i=1;i<=n-1;i++,cout<<'\n')
			for(int j=1;j<=m;j++)
				cout<<a2[i][j]<<' ';
	}
}
#undef int
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--)
		Solve();
	return 0;
}
```

---

## 作者：Scean_Tong (赞：0)

# 题解

## 思路

根据题目的要求，我们需要找到一个长为 $k+1$ 的路径，并且路径上任意相邻的两段边的颜色不同。

观察题目给出的网格，我们可以发现以下规律：

1. 如果 $m$ 是偶数，那么每一行的边的颜色都可以设定为红-蓝-红-蓝-... 这样的交替形式。
2. 如果 $m$ 是奇数，那么每一行的边的颜色都可以设定为红-蓝-红-蓝-... 的交替形式，并且最后一列的边的颜色为红色。

基于以上规律，我们可以将网格的每一行的边的颜色按照规律设定，然后再根据每一列的边的颜色是否要交替，来确定最后一行的边的颜色。

## 实现

对于每个测试用例，我们按照以下步骤进行处理：

1. 读取输入测试用例的 $n$、$m$ 和 $k$。
2. 根据 $n$ 和 $m$ 的奇偶性来确定每一行的边的颜色。对于偶数行，使用红-蓝-红-蓝的交替形式；对于奇数行，使用红-蓝-红-蓝的交替形式，并将最后一列的边的颜色设为红色。
3. 分两种情况来确定最后一行的边的颜色：
   - 如果 $m$ 是偶数，那么最后一行的边的颜色也可以使用红-蓝-红-蓝-... 的交替形式。
   - 如果 $m$ 是奇数，那么最后一行的边的颜色需要与倒数第二行的边的颜色不同，并且需要保证路径长度为 $k+1$。
4. 输出结果。

## 复杂度分析

- 时间复杂度：$O(n \times m)$，对于每个测试用例，需要遍历网格的每个边。
- 空间复杂度：$O(n \times m)$，需要存储网格的每个边的颜色。
## 总结

本题通过观察题目给出的网格的特点，找到了每一行边的颜色可以遵循的规律，并仔细处理最后一行的边的颜色。这样就能够满足路径长度和边的颜色交替的要求。实现起来比较简单，时间复杂度和空间复杂度也较小。
以上是本题的思路，代码就不贴了

---

## 作者：xuyiyang (赞：0)

### Solution
首先，从 $(1,1)$ 走到 $(n,m)$ 的最少步数是 $n+m-2$，所以如果 $k \lt n + m - 2$，一定无解。由于 $k \le 10 ^ 9$，所以一定是有重复走一条边的情况。先走好 $n+m-2$ 条边。有两种情况可以增加边数。
- 走一个方格的四条边，形成环，能增加四条边。
- 面对一条边，比如是横的，可以把它改为走竖的，横的，再走竖的，能增加两条边。即 $(x,y) \to (x,y+1)$ 可以拆成 $(x,y) \to (x-1,y),(x-1,y) \to (x-1,y+1),(x-1,y+1) \to (x,y)$。

令 $\Delta = k - (n+m-2)$。由于只能增加 $2$ 或 $4$ 条边，所以当 $\Delta$ 是奇数时，一定无解。$\\$
否则：
1. 如果 $\Delta \bmod 4 = 0$，为了方便，在起点或终点造个环即可。
2. 如果 $\Delta \bmod 4 = 2$，在起点造个环，然后在终点前造个增加两条边的方案即可。

然后这道题就做完了，代码很好写。

---

