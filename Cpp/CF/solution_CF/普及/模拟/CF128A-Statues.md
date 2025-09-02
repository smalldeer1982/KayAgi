# Statues

## 题目描述

In this task Anna and Maria play a game with a very unpleasant rival. Anna and Maria are in the opposite squares of a chessboard ( $ 8×8 $ ): Anna is in the upper right corner, and Maria is in the lower left one. Apart from them, the board has several statues. Each statue occupies exactly one square. A square that contains a statue cannot have anything or anyone — neither any other statues, nor Anna, nor Maria.

Anna is present on the board as a figurant (she stands still and never moves), and Maria has been actively involved in the game. Her goal is — to come to Anna's square. Maria and statues move in turn, Maria moves first. During one move Maria can go to any adjacent on the side or diagonal cell in which there is no statue, or she can stay in the cell where she is. The statues during their move must go one square down simultaneously, and those statues that were in the bottom row fall from the board and are no longer appeared.

At that moment, when one of the statues is in the cell in which the Maria is, the statues are declared winners. At the moment when Maria comes into the cell where Anna has been waiting, Maria is declared the winner.

Obviously, nothing depends on the statues, so it all depends on Maria. Determine who will win, if Maria does not make a strategic error.

## 样例 #1

### 输入

```
.......A
........
........
........
........
........
........
M.......
```

### 输出

```
WIN
```

## 样例 #2

### 输入

```
.......A
........
........
........
........
........
SS......
M.......
```

### 输出

```
LOSE
```

## 样例 #3

### 输入

```
.......A
........
........
........
........
.S......
S.......
MS......
```

### 输出

```
LOSE
```

# 题解

## 作者：JiaY19 (赞：4)

#### 题目大意

天空上会掉下几块石雕（Statues），我们需要将主人公（M）移到（A），并且不被砸到。

#### 思路分析

由于他的步数是无限的。

所以我们可以发现，只要在石雕砸到地上之前，我们可以~~运用蛇皮走位~~躲过石雕，就可以在最后，直接走到A。

至于如何去走的话，我们可以分析一下。

1. 我们不能去撞石头（应该都懂）

2. 我们不能去等石头砸下来，即不能去石头的下面。

所以只需要判这两个地方就可以了

#### 代码实现

由于数据范围较小，我们考虑直接用DFS解决这道题。

其余细节，见代码。

#### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[10][10];
int dx[10] = {0 , 1 , 1 , 1 , -1 , -1 , -1 , 0 , 0 , 0};
int dy[10] = {0 , -1 , 0 , 1 , 1 , 0 , -1 , 1 , 0 , -1};
//九个方向

int read()
{
    int s = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

int dfs(int s , int x , int y)                        //DFS
{
	if(s == 0) return 1;
	//如果石雕都没了，就能直接去A了 
	for(int i = 1;i <= 9;i++)
	{
		int vx = x + dx[i];
		int vy = y + dy[i];
		if(vx > 8 || vx <= 0 || vy > 8 || vy <= 0) continue;
		//边界判断 
		if(f[vx - 8 + s - 1][vy] || f[vx - 8 + s][vy]) continue;
		//判断此时去的地方有没有石雕和去了之后这个地方有没有石雕 
		if(dfs(s - 1 , vx , vy)) return 1;
		//直接去就好了 
	}
	return 0;
}

int main()
{
	int bg1 , bg2;
	for(int i = 1;i <= 8;i++)
	{
		for(int j = 1;j <= 8;j++)
		{
			char a; cin >> a; 
			if(a == 'S') f[i][j] = 1;
			if(a == 'M') bg1 = i , bg2 = j;
		} 
	}
	if(dfs(8 , bg1 , bg2)) cout << "WIN";
	else cout << "LOSE";
	return 0;
}
```

完结撒花。


---

## 作者：yzh_Error404 (赞：2)

这道题一看就是一道搜索题 ~~不要问我为什么~~。

首先，我们可以知道，这个人要从地图的左下角走到右上角，地图上有一些障碍物，人每走一步障碍物就会下落一层。

因为地图只有 $8$ 行，就算是最上面的障碍物也只需要 $8$ 次走动即可掉到最下面，于是我们只需要判断人能否活着走过 $8$ 步即可。

在搜索的时候记录步数 $step$ ，所以将要掉到人走到的格子上的障碍物的初始坐标即为 $(nx-step,ny)$ ，因为走过之后障碍物还要落下来一格，下一个掉到这里的障碍物的初始坐标为 $(nx-step-1,ny)$ ，判断这两个格子上是否有障碍物即可（我原来是模拟障碍物掉落，根本写不出 ~~可能是我太菜了~~）

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int fx[15]={0,-1,1,0,0,1,1,-1,-1,0};
int fy[15]={0,0,0,-1,1,1,-1,1,-1,0};
int ma[10][10];//存图，2为障碍物，0为空地（在写的时候脑抽的没写1）
inline void dfs(int step,int x,int y)
{
	if(step==8)//如果活着走了八步，就一定可以走到终点
	{
		puts("WIN");
		exit(0);
	}
	for(register int i=1;i<=9;i++)
	{
		int nx=x+fx[i],ny=y+fy[i];
		if(nx<1||nx>8||ny<1||ny>8||ma[nx-step-1][ny]==2||ma[nx-step][ny]==2)continue;//如果走出地图 / 走到的位置上有障碍物 / 走到的位置的上面一格有障碍物就是不合法的
		dfs(step+1,nx,ny);
	}
}
int main()
{
	for(register int i=1;i<=8;i++)
		for(register int j=1;j<=8;j++)
		{
			char ch;
			cin>>ch;
			if(ch=='S')ma[i][j]=2;
			else ma[i][j]=0;
		}
	dfs(0,8,1);
	puts("LOSE");
	return 0;
}
```

---

## 作者：Ba_creeper (赞：1)

## 题解 CF128A 【Statues】

#### 题目大意

从左下角走到右上角，走的过程中有障碍物。但每走一步时障碍物就会下落一层，问是否能到右上角。

#### 题目分析

这道题主要运用深度优先搜索。由于每走一步障碍物都会下落，所以只需走8次，障碍物都会掉出地图。所以，问题就被转化成了：判断走8次会不会死亡即可。

存图过程中，我们可以将 'S' 标记为 1，之后进行 dfs 即可。细节见代码。

#### 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int f[9][9],sx,sy;
int dx[9]= {1,1,1,-1,-1,-1,0,0,0}; //九个方向
int dy[9]= {1,-1,0,1,0,-1,1,-1,0};

int dfs(int sx,int sy,int s)
{
	if(s==0) return 1; //s=0时，即已经移动了8步，返回，输出WIN
	for(int i=0; i<9; ++i)
	{
		int nx=dx[i]+sx;
		int ny=dy[i]+sy;
		if(nx>8 || ny>8 || nx<1 || ny<1) continue; //判断边界
		if(f[nx-8+s-1][ny] || f[nx-8+s][ny]) continue; //判断障碍物下落后 和 障碍物下落前 能不能生存
		if(dfs(nx,ny,s-1)) return 1; //如果最终存活，返回1
	}
	return 0;//否则返回0
}
int main()
{
	char ch;
	for(int i=1; i<=8; ++i)
		for(int j=1; j<=8; ++j)
		{
			cin>>ch;//输入字符
			if(ch=='S') f[i][j]=1;//将字符转变成图
			else f[i][j]=0;
			if(ch=='M') sx=i,sy=j; //判断起点的位置
		}
	if(dfs(sx,sy,8)) puts("WIN");
	else puts("LOSE");
	return 0;
}

```



---

## 作者：TLMPEX (赞：0)

~~这道题其实很水。~~

思路：如果主角能走8步不死，就说明主角赢了。走每步只要判断能不能走下一个，不能走就输了，能走就到那一格。主要思路见代码。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int k[10][10];
int a[9]={-1,-1,-1,0,0,0,1,1,1};
int b[9]={-1,0,1,-1,0,1,-1,0,1};//方向数组
int dfs(int x,int y,int s){//x和y为当前位置坐标s为以走步数。
	if(s==8)return 1;//如果走到8步了，就返回1，说明主角赢了
	for(int i=0;i<9;i++){
		int fx=x+a[i],fy=y+b[i];
		if(fx>8||fy>8||fx<1||fy<1
		||k[fx-s-1][fy]||k[fx-s][fy])//如果下一步不符合条件，则跳过。
			continue;
		if(dfs(fx,fy,s+1))return 1;//如果往下一步走最终能走到终点，就返回1，说明主角赢了
	}
	return 0;//如果走不到，就输了，返回0
}
int main(){
	int i,j;
	char r;
	for(i=1;i<=8;i++)
		for(j=1;j<=8;j++){
			cin>>r;
			if(r=='.'||r=='M'||r=='A')k[i][j]=0;//初始化
			if(r=='S')k[i][j]=1;//初始化
		}
	if(dfs(8,1,0))cout<<"WIN";
	else cout<<"LOSE";
}
```


---

## 作者：Legendre_Gauss (赞：0)

题目大意：

主角开局位于M处，他如果能够走到A处就是WIN，否则就是Lose。

主角先走一步之后， 所有的S下落一层，M不能走S，而且每轮有9种走法：向周围八个地方移动，以及原地不动。

显然考虑爆搜

因为只有8X8的格子，所以最多8步之后，所有S都掉出棋盘了，那么我们只需要需要让M跑八步还不挂就行了         

然后是每次S往下掉一格，也就是地图会变化，那只要在爆搜时考虑这种情况就可以啊

```
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
 
const int dx[9]={-1,-1,-1,0,0,0,1,1,1},
	      dy[9]={-1,0,1,-1,0,1,-1,0,1};

char mp[15][15];

bool dfs(int x,int y,int step)
{
    if(step>8) return 1;
    for(int i=0;i<=8;i++)
    {
        register int kx=x+dx[i],ky=y+dy[i];
        if(kx<0||kx>7||ky<0||ky>7) continue;
        if(kx>=(step+1)&&mp[kx-(step+1)][ky]=='S') continue;
        if(kx>=step&&mp[kx-step][ky]=='S') continue;
        if(dfs(kx,ky,step+1)) return 1;
    }
    return 0;
}

void work()
{
	for(int i = 0;i < 8;i ++)
        for(int j = 0;j < 8;j ++)
        	cin>>mp[i][j];
    if(dfs(7,0,0)) cout<<"WIN"<<endl;
    else cout<<"LOSE"<<endl;
    return;
}

int main()
{
	work();
    return 0;
}
```

---

