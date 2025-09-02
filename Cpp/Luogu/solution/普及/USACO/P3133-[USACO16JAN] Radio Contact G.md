# [USACO16JAN] Radio Contact G

## 题目描述

FJ 失去了他最喜欢的牛铃，而 Bessie 已经同意帮助他找到它！他们用不同的路径搜索农场，通过无线电保持联系。

不幸的是，无线电中的电池电量不足，所以他们设法尽可能保持两者位置的距离最小，以节省电量。

FJ 从位置$(f_x,f_y)$ 开始，并计划遵循由 $N$ 步组成的路径.Bessie 从位置 $(b_x,b_y)$ 开始，并遵循由 $M$ 步组成的路径。每个步骤都是 `N`（北），`E`（东），`S`（南），或`W`（西）。其中，东方向为 $x$ 轴正方向，北方向为 $y$ 轴正方向。两个路径可以经过相同的点。

在每个时间段，FJ 可以不移动，也可以沿着他的道路前进一步。无论哪个方向恰好在下一个（假设他还没有到达他的路径的最后位置）。Bessie 可以做出类似的选择。

在每个时间点（不包括从初始位置开始的第一步），他们的无线电消耗的能量等于它们之间距离的平方。

请帮助 FJ 和 Bessie 计划行动策略，使双方达到各自终点时，最大限度地减少消耗的能量总量。输出所消耗的最小的能量。

## 样例 #1

### 输入

```
2 7
3 0
5 0
NN
NWWWWWN```

### 输出

```
28```

# 题解

## 作者：卷王 (赞：17)

## 题目大意

[点这里](https://www.luogu.com.cn/paste/y6futzd9) 感觉这题的题目描述得改改了。

## 思路

一遇到走路求最大值的问题我们首先会想到 dp。显然，这题不例外。让我们来探讨一下吧。


------------

### STEP1. 定义 dp 数组

我总结出橙黄的 dp 基本上都是问啥设啥。

这题也不例外。我们可以设 $dp_{i,j}$ 表示 FJ 走到路径的第 $i$ 个点，Bessie 走到路径的第 $j$ 个点时候最少消耗的能量。

好，就是这样。请读者们别急，让我们继续。

------------
### STEP2. 设计状态转移

橙黄题的状态转移基本上都是很基础、很简单的。

这题仍然不例外。

我们来 **分情况讨论** (为了简便这里把 FJ 看成 F，把奶牛看成 B)：

* F走，B不走，即 $dp_{i - 1, j}$。
* F走，B走，即 $dp_{i - 1, j - 1}$。
* F不走，B走，即 $dp_{i, j - 1}$。
* F不走，B也不走，这种情况由于不走还不如走，所以去掉。 

题目说要取最小的能量值，所以取 $\min$。

状态转移方程：$dp_{i, j} = \min(dp_{i - 1, j - 1}, dp_{i - 1, j}, dp_{i, j - 1}) + $ $\text{从 i 到 j 消耗的能量}$。 

有人问，这个从 $i$ 到 $j$ 消耗的能量怎么求？别急，看下面 qwq。 

我们开个结构体，设 $fx_i$ 表示 FJ 在他的路径上的第 $i$ 个步骤在 x 轴上的哪个位置，$fy_i$ 表示表示 FJ 在他的路径上的第 $i$ 个步骤在 y 轴上的哪个位置。$bx_i$ 与 $by_i$ 同理，只是把 FJ 换成 Bessie。在读入的时候根据字符依次判断即可。 

有了这两个数组，那么就可以快速求出在某一时刻两人的距离，也就知道了从 $i$ 到 $j$ 消耗的能量。

解决，下一部分！


------------

### STEP3. 初始化

有人说，这个简单！不就是这个赋一下值，然后那个再改一下吗？

但是这个蒟蒻并不这么认为 qwq。

你如果想写好初始化，那么就必需深深地领会 dp 数组的意思和 dp 的本质，所以要扎实一点，现在没学好，后面就会很难理解了！ 

好，言归正传，我们讲题——

严格意义上，我们要先令 $dp[0][0] = 0$，但是由于 dp 数组本身就默认为 $0$，所以可以不写。

再回顾一下，我们的 $dp_{i,j}$ 表示 FJ 走到路径的第 $i$ 个点，Bessie 走到路径的第 $j$ 个点时候最少消耗的能量。

那么我们就必需初始 FJ 一直没动，或者 Bessie 一直没动消耗的能量。

怎么做？很简单，请自行思考。实在不行看代码吧。 

AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
int fx, fy, bx, by;
int dp[1007][1007];
//dp[i][j] 表示 FJ 走到路径的第 i 个点，Bessie 走到路径的第 j 个点时候最少消耗的能量 
struct node {
	int x, y;
}f[1007], b[1007]; //开两个数组记录路径 
inline int dis(int u, int v) { //计算两点需要消耗的能量 
	return pow(f[u].x - b[v].x, 2) + pow(f[u].y - b[v].y, 2);
}
int main() {
	cin >> n >> m >> fx >> fy >> bx >> by; //读入 
	f[0] = (node){fx, fy}; b[0] = (node){bx, by};
	for(int i = 1; i <= n; i++) { //FJ
		char c; cin >> c; //初始化，依次判断 
		if(c == 'N') f[i] = (node){f[i - 1].x, f[i - 1].y + 1}; //北，往右 
		if(c == 'E') f[i] = (node){f[i - 1].x + 1, f[i - 1].y}; //东，往下 
		if(c == 'S') f[i] = (node){f[i - 1].x, f[i - 1].y - 1}; //南，往左 
		if(c == 'W') f[i] = (node){f[i - 1].x - 1, f[i - 1].y}; //西，往上 
	}
	for(int i = 1; i <= m; i++) { //Bessie
		char c; cin >> c; //初始化，依次判断 
		if(c == 'N') b[i] = (node){b[i - 1].x, b[i - 1].y + 1}; //北，往右 
		if(c == 'E') b[i] = (node){b[i - 1].x + 1, b[i - 1].y}; //东，往下 
		if(c == 'S') b[i] = (node){b[i - 1].x, b[i - 1].y - 1}; //南，往左 
		if(c == 'W') b[i] = (node){b[i - 1].x - 1, b[i - 1].y}; //西，往上 
	}
	for(int i = 1; i <= n; i++) //dpの初始化 
		dp[i][0] = dp[i - 1][0] + dis(i, 0);
	for(int i = 1; i <= m; i++) //同理 
		dp[0][i] = dp[0][i - 1] + dis(0, i);
	for(int i = 1; i <= n; i++) //很简单的 dp 
		for(int j = 1; j <= m; j++)
			dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + dis(i, j);
	cout << dp[n][m];
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：9)

#### Description

> 小 F 和小 B 在一个平面上走，小 F 的初始位置是 $(f_x,f_y)$，小 B 的初始位置是 $(b_x,b_y)$，他们的路径分别是 $S_f,S_b$，每个时间点他们可以选择原地不动或者按照他们的路径走一步，每个时间点产生的代价为他们的欧几里得距离的平方，求他们到达路径终点最少需要多少代价。

#### Solution

这是一个思维难度 $=1$ 代码难度 $=5$ 的题目。。。

二维 dp，定义 $dp[i][j]$ 为这个时间点小 F 走了 $i$ 步小 B 走了 $j$ 步产生的最小代价，不难得知可以从三种情况转移过来：

- 小 F 走一步，小 B 原地不动。
- 小 F 原地不动，小 B 走一步。
- 小 F 和小 B 都走一步。

转移方程即为：

$$dp[i][j]=\min\{dp[i-1][j],dp[i][j-1],dp[i-1][j-1]\}+dis$$

注意初始化 $dp[i][j]$ 时 $i=0,j=0$ 需要分别特判并初始化。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int dp[1005][1005];

char f[1005];
char b[1005];

int F[1005][1005];
int B[1005][1005];

int dis (int x1, int y1, int x2, int y2) {return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);}

int main () {
	int n, m;
	scanf("%d%d", &n, &m);
	int fx, fy, bx, by;
	scanf("%d%d%d%d", &fx, &fy, &bx, &by);
	scanf("%s%s", f, b);
	F[0][1] = fx;
	F[0][2] = fy;
	for (int i = 1; i <= n; i++) 
		switch (f[i - 1]) {
			case 'N': {
				F[i][1] = F[i - 1][1];
				F[i][2] = F[i - 1][2] + 1; 
				break;
			}
			case 'E': {
				F[i][1] = F[i - 1][1] + 1;
				F[i][2] = F[i - 1][2];
				break;
			} 
			case 'S': {
				F[i][1] = F[i - 1][1];
				F[i][2] = F[i - 1][2] - 1;
				break;
			}
			case 'W': {
				F[i][1] = F[i - 1][1] - 1;
				F[i][2] = F[i - 1][2];
				break;
			}
		}
	B[0][1] = bx;
	B[0][2] = by;
	for (int i = 1; i <= m; i++) 
		switch (b[i - 1]) {
			case 'N': {
				B[i][1] = B[i - 1][1];
				B[i][2] = B[i - 1][2] + 1; 
				break;
			}
			case 'E': {
				B[i][1] = B[i - 1][1] + 1;
				B[i][2] = B[i - 1][2];
				break;
			} 
			case 'S': {
				B[i][1] = B[i - 1][1];
				B[i][2] = B[i - 1][2] - 1;
				break;
			}
			case 'W': {
				B[i][1] = B[i - 1][1] - 1;
				B[i][2] = B[i - 1][2];
				break;
			}
		}
	for (int i = 1; i <= n; i++)
		dp[i][0] = dp[i - 1][0] + dis(bx, by, F[i][1], F[i][2]);
	for (int i = 1; i <= m; i++)
		dp[0][i] = dp[0][i - 1] + dis(fx, fy, B[i][1], B[i][2]);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
			dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + dis(F[i][1], F[i][2], B[j][1], B[j][2]);
	printf("%d", dp[n][m]);
	return 0;
}
```

---

## 作者：wyxdrqc (赞：9)

~~调了进一个小时~~ ，**我真是太弱了**


------------
作为自己第一道~~靠自己能力~~AC的DP（虽然是一道黄题，但我已经很满足了）


------------
废话少说，这道题的状态还是~~比较好设计的~~（毕竟像我这种蒟蒻都能想到）

f[i][j]表示当第一个人走了i步，第2个人走了j时的最小花费

那么 f[i][j]=min(f[i-1][j],f[i-1][j-1],f[i][j-1])+当前花费

这个状态转移方程还是比较好想的，关键在于边界问题的处理
以及求当前花费上


------------
```c
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1005;
int f[N][N];
int m,n;
char farmer[N],bessie[N];//储存方向数组
int dx[105];
int dy[105];
int fx,fy,bx,by;
int fto[N][3];
int bto[N][3];//fto[i][0]表示第一个人走i步所到达的点的X坐标，bto[i][0]同理
inline int sum(int x,int y){
	return (fto[x][1]-bto[y][1])*(fto[x][1]-bto[y][1])+
	(fto[x][2]-bto[y][2])*(fto[x][2]-bto[y][2]);
    //计算，当第一个人走X步，第二个人走y步时的花费
}
inline int min(int x,int y,int z){
	if(x>y)
	x=y;
	if(x>z)
	x=z;
	return x;	
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d%d%d",&fto[0][1],&fto[0][2],&bto[0][1],&bto[0][2]);
	scanf("%s",farmer+1);
	scanf("%s",bessie+1);
	dy[(int)'N']=1;
	dy[(int)'S']=-1;
	dx[(int)'W']=-1;
	dx[(int)'E']=1;//标记坐标数组（此处懒了一下）
	for(int i=1;i<=n;i++){
		int k1=int(farmer[i]);
		fto[i][1]=fto[i-1][1]+dx[k1];
		fto[i][2]=fto[i-1][2]+dy[k1];//将fto[i][0]与fto[i][1]递推出来
        //这样我们就可以直接用了，每一步都只是上一步又走了一步而已
	}
	for(int i=1;i<=m;i++){
		int k2=int(bessie[i]);
		bto[i][1]=bto[i-1][1]+dx[k2];
		bto[i][2]=bto[i-1][2]+dy[k2];//此处同上
	}
	for(int i=1;i<=n;i++)
	f[i][0]=sum(i,0)+f[i-1][0];
	for(int i=1;i<=m;i++)   
	f[0][i]=sum(0,i)+f[0][i-1];//一定要注意处理边界！！！（在这里卡了半天）
    //因为不但需要计算出当前花费，还要将当前花费与之前的花费和相加
    //否则就只计算出了当前这一步的花费,那么DP就无意义了
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f[i][j]=min(f[i-1][j],f[i-1][j-1],f[i][j-1])+sum(i,j);	
		}//所以，将边界处理好后，DP还是挺简单的
	}
	printf("%d",f[n][m]);
	return 0;	
}
```

---

## 作者：_louhc (赞：4)

> ~~众所周知，DP是一个好东西，所以这题用DP。~~

[原题](https://www.luogu.org/problemnew/show/P3133)

这是样例的示意图  
![样例](https://img-blog.csdn.net/20180814150653860?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xvdWhhbmNoZW5n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)  

这道题有十分明显的阶段性，而且数据也不大，所以用DP即可。
我们用一个二维数组```f[i][j]```表示当Farmer John到第i步，Bessie到第j步时所需花费的最小能量。
转移方程容易推得：
```cpp
f[i][j] = min( f[i][j - 1], f[i - 1][j], f[i - 1][j - 1] ) + dist;
```
其中dist表示FJ在第i步，Bessie在j步时他们距离的平方```( tx1 - tx2 ) * ( tx1 - tx2 ) + ( ty1 - ty2 ) * ( ty1 - ty2 )```

这里要注意初始化:
```
f[i][0] = f[i - 1][0] + dist;
f[0][i] = f[i - 1][0] + dist;
f[0][0] = 0;//因为从初始位置开始的第一步不需要能量
```

这里我用一个move函数移动坐标(用了引用变量方便一点)

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 1005
#define LL long long

int N, M;
LL f[MAXN][MAXN];//开long long防止上溢
int fx, fy, bx, by, la, lb;
char a[MAXN], b[MAXN];//移动方向

void move( int &x, int &y, char d ){ //移动坐标
	switch( d ){
		case 'N': y++; break;
		case 'S': y--; break;
		case 'W': x--; break;
		case 'E': x++; break;
	}
}

LL dist( int x1, int y1, int x2, int y2 ){ //花费能量
	return ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 );
}
	
int main(){
	scanf( "%d%d", &N, &M );
	scanf( "%d%d%d%d", &fx, &fy, &bx, &by );
	scanf( "%s%s", a + 1, b + 1 );
	la = strlen( a + 1 ); lb = strlen( b + 1 );
	int tx1(fx), ty1(fy), tx2(bx), ty2(by);//FJ、Bessie的坐标
	for ( int i = 1; i <= la; ++i ){ // 初始化f[i][0](i != 0)
		move( tx1, ty1, a[i] );
		f[i][0] = f[i - 1][0] + dist( tx1, ty1, bx, by );
	}
	for ( int i = 1; i <= lb; ++i ){ //初始化f[0][i](i != 0)
		move( tx2, ty2, b[i] );
		f[0][i] = f[0][i - 1] + dist( fx, fy, tx2, ty2 );
	}
	tx1 = fx; ty1 = fy;
	for ( int i = 1; i <= la; ++i ){
		tx2 = bx; ty2 = by;
		move( tx1, ty1, a[i] );
		for ( int j = 1; j <= lb; ++j ){
			move( tx2, ty2, b[j] );
			f[i][j] = min( f[i - 1][j], f[i][j - 1] ); // 上述转移方程
			f[i][j] = min( f[i][j], f[i - 1][j - 1] );
			f[i][j] += dist( tx1, ty1, tx2, ty2 );
		}
	}
	printf( "%lld", f[la][lb] );
	return 0;
}
```
#__~~所以: DP是个好东西~~__

---

## 作者：_ajthreac_ (赞：3)

### 0.Description
给出两个人的移动方向序列，每个时间点可以移动也可以不移动，问所有时间点两人欧几里得距离平方的最小值。 
### 1.Solution
观察题面可以发现它满足 $dp$ 的性质，我们可以考虑 $dp$ 来做。      
首先考虑状态如何设计：我们发现知道两个人分别走到第几步就可以计算出总的价值，不妨先设出来 $f_{i,j}$ 表示两人分别走到第 $i$ 步、第 $j$ 步的最小答案。            
有了状态，转移就很好办了，我们只需讨论这个时间点谁走即可（注意：两个人不可能都不走）： $f_{i,j}=\min\{f_{i-1,j},f_{i,j-1},f_{i-1,j-1}\}+w$ ，其中 $w$ 为当前位置时两人距离的平方。                
最后初始化也很简单：分别计算其中一个人不走时另一个人的答案。
### 2.Code
[开头代码](https://www.cnblogs.com/juruoajh/p/12632444.html)
```cpp
#define N 1010
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};
int n,m,fx,fy,bx,by,f[N][N];
char fj[N],bs[N];
inline int Dir(char s){//移动的方向
	switch(s){
		case 'N':return 0;
		case 'E':return 1;
		case 'S':return 2;
		case 'W':return 3;
	}
	return 0;
}
inline int Dist(int x1,int y1,int x2,int y2){
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int main(){
	Read(n),Read(m);
	Read(fx),Read(fy),Read(bx),Read(by);
	scanf("%s%s",fj+1,bs+1);
	int x=fx,y=fy;
	for(rg int i=1;i<=n;i++){//只有FJ移动
		x+=dx[Dir(fj[i])],y+=dy[Dir(fj[i])];
		f[i][0]=f[i-1][0]+Dist(x,y,bx,by);
	}
	x=bx,y=by;
	for(rg int i=1;i<=m;i++){//只有Bessie移动
		x+=dx[Dir(bs[i])],y+=dy[Dir(bs[i])];
		f[0][i]=f[0][i-1]+Dist(fx,fy,x,y);
	}
	int fx1=fx,fy1=fy;//fx1,fy1,bx1,by1都是临时存储变量
	for(rg int i=1;i<=n;i++){
		fx1+=dx[Dir(fj[i])],fy1+=dy[Dir(fj[i])];
		int bx1=bx,by1=by;
		for(rg int j=1;j<=m;j++){
			bx1+=dx[Dir(bs[j])],by1+=dy[Dir(bs[j])];
			f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+Dist(fx1,fy1,bx1,by1);
		} 
	}
	cout<<f[n][m]<<endl;
	return 0;
}
```

---

## 作者：云雷心柠檬听 (赞：2)

### 题意简述
给定两个点（即 FJ 和 Bessie）和两条路径，让这两个点沿着路径移动，求每移动一次的能量总和。

### 思维路径
典型的动态规划题，我们设计状态，设 $f_{i,j}$ 表示 FJ 走到第 $i$ 个点，Bessie 走到第 $j$ 个点最少的能量总和。

因为他们两个都可以在某一个时间点选择走或者不走，$f_{i,j}$ 可以由 $f_{i-1,j-1}$ 或 $f_{i-1,j}$ 或 $f_{i,j-1}$ 走到，因此得到如下的转移方程式。
$$
f_{i,j}=min(f_{i-1,j-1},f_{i-1,j},f_{i,j-1})+dst_{i,j}
$$

### 具体实现
首先我们存下路径上每一步到达的点，注意题目中的注意事项：东方向为正 X 方向，北方向为正 Y 方向。

因此，以 FJ 路径的存储方式为例，得到以下代码。

```cpp
if(s[i]=='N') posf[i+1]=(node){posf[i].x,posf[i].y+1};
if(s[i]=='E') posf[i+1]=(node){posf[i].x+1,posf[i].y};
if(s[i]=='S') posf[i+1]=(node){posf[i].x,posf[i].y-1};
if(s[i]=='W') posf[i+1]=(node){posf[i].x-1,posf[i].y};
```

接着我们要写计算两点间距离的代码。

它们间距离的平方就等于它们横坐标之差的平方和纵坐标之差的平方的和。

代码实现如下。

```cpp
ll dst(ll u,ll v){
	return (posf[u].x-posb[v].x)*(posf[u].x-posb[v].x)+(posf[u].y-posb[v].y)*(posf[u].y-posb[v].y);
}
```


最后我们要写正式的 dp ，在预处理中要处理 $i=0$ 和 $j=0$ 的情况。

注意 $i=j=0$ 时能量和为 $0$ 而不是两个起点之间的距离。

得到预处理的代码。

```
f[0][0]=0;
for(ll i=1;i<=n;i++){
	f[i][0]=dst(i,0)+f[i-1][0];
}
for(ll i=1;i<=m;i++){
	f[0][i]=dst(0,i)+f[0][i-1];
}
```

### AC 代码

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1009;
ll n,m;
struct node{
	ll x,y;
} posf[N],posb[N];
ll f[N][N];

void input(){
	cin>>n>>m;
	cin>>posf[0].x>>posf[0].y>>posb[0].x>>posb[0].y;
	string s;
	cin>>s;
	for(ll i=0;i<s.size();i++){
		if(s[i]=='N') posf[i+1]=(node){posf[i].x,posf[i].y+1};
		if(s[i]=='E') posf[i+1]=(node){posf[i].x+1,posf[i].y};
		if(s[i]=='S') posf[i+1]=(node){posf[i].x,posf[i].y-1};
		if(s[i]=='W') posf[i+1]=(node){posf[i].x-1,posf[i].y};
	}
	cin>>s;
	for(ll i=0;i<s.size();i++){
		if(s[i]=='N') posb[i+1]=(node){posb[i].x,posb[i].y+1};
		if(s[i]=='E') posb[i+1]=(node){posb[i].x+1,posb[i].y};
		if(s[i]=='S') posb[i+1]=(node){posb[i].x,posb[i].y-1};
		if(s[i]=='W') posb[i+1]=(node){posb[i].x-1,posb[i].y};
//		cout<<posb[i+1].x<<" "<<posb[i+1].y<<endl;
	}
}

ll dst(ll u,ll v){
	return (posf[u].x-posb[v].x)*(posf[u].x-posb[v].x)+(posf[u].y-posb[v].y)*(posf[u].y-posb[v].y);
}

void solve(){
	f[0][0]=0;
	for(ll i=1;i<=n;i++){
		f[i][0]=dst(i,0)+f[i-1][0];
	}
	for(ll i=1;i<=m;i++){
		f[0][i]=dst(0,i)+f[0][i-1];
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+dst(i,j);
//			cout<<f[i][j]<<" ";
		}
//		cout<<endl;
	}
	cout<<f[n][m];
}

int main(){
	input();
	solve();
	return 0;
}
```


---

## 作者：逝星DS (赞：2)

P3133 【[USACO16JAN]无线电联系Radio Contact】

FJ失去了他最喜欢的牛铃，而Bessie已经同意帮助他找到它！他们用不同的路径搜索农场，通过无线电保持联系。不幸的是，无线电中的电池电量不足，所以他们设法尽可能保持两者位置的距离最小，以节省电量。

FJ从位置（fx，fy）开始，并计划遵循由N步骤组成的路径，每个步骤都是“N”（北），“E”（东），“S”（南），或“W”（西）。Bessie从位置（bx，by）开始，并遵循由M步骤组成的类似路径。两个路径可以经过相同的点。在每个时间段，FJ可以保持在他现在的位置，或沿着他的道路前进一步，无论哪个方向恰好在下一个（假设他还没有到达他的路径的最后位置）。Bessie可以做出类似的选择。在每个时间步（不包括从初始位置开始的第一步），他们的无线电消耗的能量等于它们之间距离的平方。

请帮助FJ和Bessie计划行动策略，最大限度地减少消耗的能量总量。总量包括最终步骤，这时两者首先到达各自路径上的最终位置。

输入输出格式

输入格式：
第一行输入N和M（1≤N，M≤1000）。

第二行输入整数fx和fy，第三行输入bx和by（0≤fx，fy，bx，≤1000）。下一行包含一个长度为N的字符串描述FJ的路径，最后一行包含一个字符串的长度M描述Bessie的路径。

数据满足（0≤x，y≤1000）。注意，东方向为正X方向，北方向为正Y方向。

输出格式：
输出一个整数，表示最小能量。

输入输出样例

输入样例#1： 
2 7
3 0
5 0
NN
NWWWWWN
输出样例#1： 
28

一个很好的四维dp；
设f[i][j][k][[l]，两人分别走了i、j步，k、l为两人走或不走的状态；
附上代码：（详细注释）

```cpp
#include <iostream>
#include <cstring>
#define maxN 1010
using namespace std;
int N,M;
int x1[maxN],y1[maxN],x2[maxN],y2[maxN];  //先将走到每一步的坐标算出并记录； 
char A[maxN],B[maxN];  //两人走的路径； 
int f[maxN][maxN][3][3];  //如上所示； 
void pre();  //预处理； 
void comp(int i,int j);
int main()  {
	cin>>N>>M;
	cin>>x1[0]>>y1[0]>>x2[0]>>y2[0];  //起点； 
	cin>>A>>B;
	memset(f,0x7f,sizeof(f));  //初始化； 
	pre();  //预处理，计算每步坐标； 
	for(int i=0;i<=N;i++)  {  //i、j从0开始！！！！ 
		for(int j=0;j<=M;j++)  {
			if(!i && !j)  {  //初始化，； 
				f[i][j][0][1]=0;
				f[i][j][1][1]=0;
				f[i][j][1][0]=0;  //默认为0； 
				continue;
			}
			comp(i,j);  //dp; 
		}
	}
	cout<<min(f[N][M][1][1],min(f[N][M][1][0],f[N][M][0][1]));
	return 0;
}
void comp(int i,int j)  {  //dp;
	if(i!=0 && j!=0)  //别忘判断！！！！ 
	    f[i][j][1][1]=min(f[i-1][j-1][1][1],min(f[i-1][j-1][1][0],f[i-1][j-1][0][1]));
	f[i][j][1][1]+=(x1[i]-x2[j])*(x1[i]-x2[j])+(y1[i]-y2[j])*(y1[i]-y2[j]);
	if(i!=0)  //别忘判断！！！！
	    f[i][j][1][0]=min(f[i-1][j][1][1],min(f[i-1][j][1][0],f[i-1][j][0][1]));
	f[i][j][1][0]+=(x1[i]-x2[j])*(x1[i]-x2[j])+(y1[i]-y2[j])*(y1[i]-y2[j]);
	if(j!=0)  //别忘判断！！！！
	    f[i][j][0][1]=min(f[i][j-1][1][1],min(f[i][j-1][1][0],f[i][j-1][0][1]));
	f[i][j][0][1]+=(x1[i]-x2[j])*(x1[i]-x2[j])+(y1[i]-y2[j])*(y1[i]-y2[j]);
}
void pre()  {
	for(int i=0;i<N;i++)  {
		if(A[i]=='N')  {
			x1[i+1]=x1[i];
			y1[i+1]=y1[i]+1;
		}
		else if(A[i]=='E')  {
			x1[i+1]=x1[i]+1;
			y1[i+1]=y1[i];
		}
		else if(A[i]=='S')  {
			x1[i+1]=x1[i];
			y1[i+1]=y1[i]-1;
		}
		else  {
			x1[i+1]=x1[i]-1;
			y1[i+1]=y1[i];
		}
	}
	for(int i=0;i<M;i++)  {
		if(B[i]=='N')  {
			x2[i+1]=x2[i];
			y2[i+1]=y2[i]+1;
		}
		else if(B[i]=='E')  {
			x2[i+1]=x2[i]+1;
			y2[i+1]=y2[i];
		}
		else if(B[i]=='S')  {
			x2[i+1]=x2[i];
			y2[i+1]=y2[i]-1;
		}
		else  {
			x2[i+1]=x2[i]-1;
			y2[i+1]=y2[i];
		}
	}
}  
```

---

## 作者：QcpyWcpyQ (赞：1)

- 考虑动态规划，令$dp_{i,j}$为Farmer John到第i步，Bessie到第j步时所需花费的最小能量。

- 转移方程则为：

$$dp_{i,j}=\min\{dp_{i-1,j},dp_{i,j-1},dp_{i-1,j-1}\}+\text{dis}(i,j)$$

其中$\min$中的三项分别表示Farmer John走一步，Bessie走一步和他们都走一步。$\text{dis}(i,j)$表示能量。

- 注意初始化边界和每次走到的点。


------------

- code:

```cpp
#include<bits/stdc++.h>
using namespace std; 

inline int read(){
	int s=0,f=1;char ch=getchar();
	while(ch<'0' or ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' and ch<='9'){s=(s<<1)+(s<<3)+(ch^48);ch=getchar();}
	return f*s;
}

inline void write(long long num){
	if(num<0)putchar('-'),num=-num;
	if(num>9)write(num/10);
	putchar(num%10+48);
}

const int N=1e3+5;
struct Fj{int x,y;}fj[N]; 
struct Bs{int x,y;}bs[N];

int n,m,fx,fy,bx,by;
long long dp[N][N];

char c;

inline long long dis(int i,int j){
	return (fj[i+1].x-bs[j+1].x)*(fj[i+1].x-bs[j+1].x)+
		   (fj[i+1].y-bs[j+1].y)*(fj[i+1].y-bs[j+1].y);
}

int main(){
	n=read(),m=read();
	fx=read(),fy=read();
	bx=read(),by=read();
	fj[1].x=fx,fj[1].y=fy;
	bs[1].x=bx,bs[1].y=by;
	for(int i=1;i<=n;++i){
		cin>>c;
		if(c=='N')fj[i+1].x=fj[i].x,fj[i+1].y=fj[i].y+1;
		if(c=='S')fj[i+1].x=fj[i].x,fj[i+1].y=fj[i].y-1;
		if(c=='W')fj[i+1].x=fj[i].x-1,fj[i+1].y=fj[i].y;
		if(c=='E')fj[i+1].x=fj[i].x+1,fj[i+1].y=fj[i].y;
	}
	for(int i=1;i<=m;++i){
		cin>>c;
		if(c=='N')bs[i+1].x=bs[i].x,bs[i+1].y=bs[i].y+1;
		if(c=='S')bs[i+1].x=bs[i].x,bs[i+1].y=bs[i].y-1;
		if(c=='W')bs[i+1].x=bs[i].x-1,bs[i+1].y=bs[i].y;
		if(c=='E')bs[i+1].x=bs[i].x+1,bs[i+1].y=bs[i].y;
	}
	for(int i=1;i<=n;++i)
		dp[i][0]=dis(i,0)+dp[i-1][0];
	for(int i=1;i<=m;++i)   
		dp[0][i]=dis(0,i)+dp[0][i-1];	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			dp[i][j]=min(dp[i][j-1],min(dp[i-1][j],dp[i-1][j-1]))+dis(i,j);
	write(dp[n][m]);
	return 0;
}
```


---

## 作者：0xFF (赞：1)

#### 题目大意


------------
给出两个人的初始位置和移动的顺序，每一个时刻两个人可以选择留在原地或者按照给定的移动顺序移动一步，每一时刻的代价是两人欧几里得距离的平方，求最小的代价和。

#### 思路分析


------------
考虑动态规划求解。

$f(i,j)$ 表示第一个人走 $i$ 步且第二个人走 $j$ 的最小代价和。

由于每次的状态只有第一个人走第二个人不走、第一个人不走第二个人走和两人都走这三种状态，所以转移方程即为

$$
f(i,j) = \min\left \{ f(i-1,j) \ \ f(i,j-1) \ \ f(i-1,j-1) \right \} + dis(i,j) 
$$

由于路线是固定的所以只需预处理出 $dis(i,j)$ 即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int INF = 5e7 + 7;
const int mod = 1e9 + 7;
const int N = 500 + 10;
int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int f[N][N];
int dis[N][N];
int calc(int a_1,int b_1,int a_2,int b_2){
	return (a_2 - a_1) * (a_2 - a_1) + (b_2 - b_1) * (b_2 - b_1);
}
char str1[N],str2[N];
int Fx[N],Fy[N];
int Dx[N],Dy[N];
signed main(){
	int n = read() , m = read();
	int fx = read() , fy = read();
	int dx = read() , dy = read();
	dis[0][0] = calc(fx,fy,dx,dy);
	scanf("%s",str1+1);
	scanf("%s",str2+1);
	Fx[0] = fx,Fy[0] = fy,Dx[0] = dx,Dy[0] = dy;
	for(int i=1;i<=n;i++){
		if(str1[i] == 'N'){
			Fx[i] = Fx[i-1];
			Fy[i] = Fy[i-1] + 1;
		}
		if(str1[i] == 'E'){
			Fx[i] = Fx[i-1] + 1;
			Fy[i] = Fy[i-1];
		}
		if(str1[i] == 'S'){
			Fx[i] = Fx[i-1];
			Fy[i] = Fy[i-1] - 1;
		}
		if(str1[i] == 'W'){
			Fx[i] = Fx[i-1]-1;
			Fy[i] = Fy[i-1];
		}
	}
	for(int i=1;i<=m;i++){
		if(str2[i] == 'N'){
			Dx[i] = Dx[i-1];
			Dy[i] = Dy[i-1] + 1;
		}
		if(str2[i] == 'E'){
			Dx[i] = Dx[i-1] + 1;
			Dy[i] = Dy[i-1];
		}
		if(str2[i] == 'S'){
			Dx[i] = Dx[i-1];
			Dy[i] = Dy[i-1] - 1;
		}
		if(str2[i] == 'W'){
			Dx[i] = Dx[i-1]-1;
			Dy[i] = Dy[i-1];
		}	
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			dis[i][j] = calc(Fx[i],Fy[i],Dx[j],Dy[j]);
		}
	}
	for(int i=1;i<=n;i++){
		f[i][0] = f[i-1][0] + dis[i][0];
	}
	for(int i=1;i<=m;i++){
		f[0][i] = f[0][i-1] + dis[0][i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f[i][j] = min(f[i-1][j],min(f[i][j-1],f[i-1][j-1])) + dis[i][j];
		}
	}
	printf("%lld\n",f[n][m]);
	return 0;
}
```


---

## 作者：Hexarhy (赞：0)

### Preface

递推基础题，这里主要是为了写题解攒咕值，顺便修题面，原来的没有 $\LaTeX$ 。

### Description

**希望管理员替换题面。**[题面剪贴板地址。](https://www.luogu.com.cn/paste/r99pceu1)

题意简述：给出长度分别为 $n,m$ 的两条路径和相应起点。两者每一步可以移动或不移动。每一步都会消耗能量，其值为两者的欧几里得距离的平方。输出所消耗的最小能量。

### Solution

非常套路的递推题。

设 $F_{i,j}$ 为一方走了 $i$ 步，另一方走了 $j$ 步的消耗的最小能量。则有：

$$F_{i,j}=\min\{F_{i-1,j},F_{i,j-1}.F_{i-1,j-1}\}+v$$

其中 $v$ 为当前所消耗的能量。

$\min$ 里的三者分别表示为：前者走后者不走，前者不走后者走，两者不走的三种情况。

初始化边界就是当 $i,j$ 分别为 $0$ 时所消耗的能量。当然 $F_{0,0}=0$。

接下来就模拟走路径，改变坐标即可。

答案就是双方走完路径的时候，即 $F_{n,m}$。

时间复杂度 $\Theta(nm)$。

### Notice

1. 考虑到距离有平方，最好开`long long`。（没试过会不会炸）

1. 注意边界和别把 $n,m$ 弄反了。

1. 如果下标从 $1$ 开始，枚举时要注意先移动，再计算。

1. 字符数组输入的时候，下标从 $1$ 开始。

### Code

本代码需要 C++11。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
const int MAXN=1005;
int n,m,fx,fy,bx,by;
ll f[MAXN][MAXN];
char fj[MAXN],bes[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>m>>fx>>fy>>bx>>by;
    for(int i=1;i<=n;i++)	cin>>fj[i];
    for(int i=1;i<=m;i++)	cin>>bes[i];
    auto dis=[=](const int x1,const int y1,const int x2,const int y2)
	{
		return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	};
    auto move=[=](int& x,int& y,const char dir)
    {
	    switch(dir)
		{
			case 'N':y++;return;
			case 'S':y--;return;
			case 'E':x++;return;
			case 'W':x--;return;
		} 
	};
	int x=fx,y=fy;
    for(int i=1;i<=n;i++)
    {
    	move(x,y,fj[i]);
    	f[i][0]=f[i-1][0]+dis(x,y,bx,by);
	}
	x=bx,y=by;
	for(int i=1;i<=m;i++)
	{
		move(x,y,bes[i]);
		f[0][i]=f[0][i-1]+dis(fx,fy,x,y);
	}
	for(int i=1,ux=fx,uy=fy;i<=n;i++)
	{
		move(ux,uy,fj[i]);
		for(int j=1,vx=bx,vy=by;j<=m;j++)
		 {
		 	move(vx,vy,bes[j]);
		 	f[i][j]=min(f[i-1][j],min(f[i][j-1],f[i-1][j-1]))+dis(ux,uy,vx,vy);
		 }
	}
	cout<<f[n][m]<<endl;
	return 0;
}
```

---

## 作者：沧澜 (赞：0)

f[i][j]表示，第1个人走了i步，第2个人走了j步，此时所消耗的最小的能量之和。

状态转移方程就可以很轻易的表示出来：f[i][j]=min(f[i-1][j],min(f[i][j-1],f[i-1][j-1]))。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,fx,fy,bx,by;
char s1[1001],s2[1001];
int f[1001][1001],dis[1001][1001];
int h1[1001],h2[1001],z1[1001],z2[1001];
void pre(){
    h1[0]=fx;z1[0]=fy;h2[0]=bx;z2[0]=by;
    for(int i=1;i<=n;i++){
        if(s1[i-1]=='W')    h1[i]=h1[i-1]-1,z1[i]=z1[i-1];
        if(s1[i-1]=='N')    h1[i]=h1[i-1],z1[i]=z1[i-1]+1;
        if(s1[i-1]=='S')    h1[i]=h1[i-1],z1[i]=z1[i-1]-1;
        if(s1[i-1]=='E')    h1[i]=h1[i-1]+1,z1[i]=z1[i-1];
    }
    for(int i=1;i<=m;i++){
        if(s2[i-1]=='W')    h2[i]=h2[i-1]-1,z2[i]=z2[i-1];
        if(s2[i-1]=='N')    h2[i]=h2[i-1],z2[i]=z2[i-1]+1;
        if(s2[i-1]=='S')    h2[i]=h2[i-1],z2[i]=z2[i-1]-1;
        if(s2[i-1]=='E')    h2[i]=h2[i-1]+1,z2[i]=z2[i-1];
    }    
}
int main(){
    scanf("%d%d",&n,&m);
    scanf("%d%d",&fx,&fy);
    scanf("%d%d",&bx,&by);
    scanf("%s",s1);
    scanf("%s",s2);
    pre();
    memset(f,0x7f,sizeof(f));
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            dis[i][j]=(h1[i]-h2[j])*(h1[i]-h2[j])+(z1[i]-z2[j])*(z1[i]-z2[j]);
    f[0][0]=0;
    for(int i=1;i<=m;i++)    f[0][i]=f[0][i-1]+dis[0][i];
    for(int i=1;i<=n;i++)    f[i][0]=f[i-1][0]+dis[i][0];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            f[i][j]=min(f[i-1][j],min(f[i-1][j-1],f[i][j-1]))+dis[i][j];
    cout<<f[n][m];
}
```

---

