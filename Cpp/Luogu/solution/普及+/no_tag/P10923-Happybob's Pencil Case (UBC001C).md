# Happybob's Pencil Case (UBC001C)

## 题目背景

注：本题无 typo。

## 题目描述

假设教室是一个 $n \times n$ 的 `01` 矩阵，`0` 表示空，`1` 表示有课桌（障碍）。

现在 Cuazyoxi 拿着 Happybob's Pencil Case 在 $(x_1, y_1)$ 处，Happybob 在 $(x_2, y_2)$ 处。

我们定义一次移动为往当前格子的上下左右一格移动。形式化地，假设当前一人（Cuazyoxi 或 Happybob）在 $(x, y)$ 处，如果 $(x + 1, y), (x, y + 1), (x - 1, y), (x, y - 1)$ 当中的某一个存在且不是障碍，则他可以移动到那一格。

每秒，Cuazyoxi 先移动一次或不动，然后 Happybob 移动一次或两次或者不动，每次移动后他们都知道对方的位置。

双方都很聪明。Cuazyoxi 想要让 Happybob 抓到他的时间尽量久，而 Happybob 想要尽早抓到 Cuazyoxi。

问：Cuazyoxi 还能躲避 Happybob 多少秒（Happybob 至少要多少秒后才能和 Cuazyoxi 达到同一个格子）？


## 说明/提示

**样例说明**

对于样例 $1$，Cuazyoxi 的最优策略显然是呆在原地不动，$2$ 秒后 Happybob 可以抓到他。

对于样例 $2$，无论如何 Happybob 都抓不到 Cuazyoxi。

**数据范围**

$2\le n\le 10$ 且 $1 \le x_1, x_2, y_1, y_2 \le n$。保证 $(x_1,y_1),(x_2,y_2)$ 上的数字是 `0` 且 $x_1\ne x_2$ 或 $y_1\ne y_2$。保证输入的 $n$ 个字符串长度都是 $n$ 且只含字符 `0` 与 `1`（可能只含 `1` 或只含 `0`）。

## 样例 #1

### 输入

```
3
1 1 3 3
011
011
000```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 1 3 3
011
111
110```

### 输出

```
inf```

# 题解

## 作者：Crazyouth (赞：4)

### Sol. by "Cuazyoxi"

考虑两种搜索策略。

#### 广搜

由于 cy（Cuazyoxi）需要尽量远离 hb（Happybob），所以每次 cy 一定会往远离 hb 的方向走，hb 同理。也就是说，易证最终两人路线一定满足 cy 远离 hb，hb 靠近 cy，但是正向搜索这样会 WA on #1，为什么呢？如果说 cy 远离 hb 就进入队列，那么 cy 遇到死胡同代码就挂了，因此需要枚举 cy 落点，再据此将每个 hb 能达到最小距离的点枚举下去。

但是这个代码会 WA on #5，原因是 hb 往离 cy 近的方向走不一定最优，因为 cy 可以和 hb 绕圈，这时候 hb 去堵截 cy 是最优的，怎么解决这种问题呢？见下。

#### 深搜

记搜，$ans_{i,j,k,l}$ 表示把 cy 在 $(i,j)$，hb 在 $(k,l)$ 最多多少步抓到 cy，转移的时候枚举 cy 落点，据此搜索 hb 往哪个方向最快抓，再判断 cy 这一步是否明智。

但是这个代码会 WA on #2，原因是判断是否访问过的时候 $vis$ 数组妨碍了 hb 的走位，导致出现错误答案，如何避免？见下。

#### Mix it up!

如果在深搜的时候不记录 vis，而是搜索 hb 所有离 cy 近的路线，那不就过了？正确的。时空峰值：$8$ ms，$564$ KB。

### Std.
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[20];
int dist[20][20],dy[5]={0,1,0,-1,0},dx[5]={-1,0,1,0,0},vis[20][20];
int vis2[20][20],ans[20][20][20][20];
int x[3],y[3],n,m;
void getdist(int nx,int ny)
{
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	dist[i][j]=1e9,vis2[i][j]=0;
	vis2[nx][ny]=1;
	dist[nx][ny]=0;
	queue<pair<int,int>> pos;
	queue<int> step;
	pos.push({nx,ny});
	step.push(0);
	while(pos.size())
	{
		int x=pos.front().first,y=pos.front().second,stp=step.front();
		pos.pop();
		step.pop();
		dist[x][y]=stp;
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(xx>n||xx<1||yy>n||yy<1||vis2[xx][yy]||s[xx][yy]=='1') continue;
			vis2[xx][yy]=1;
			pos.push({xx,yy});
			step.push(stp+1);
		}
	}
}
int dfs(int xc,int yc,int xh,int yh)
{
	if(xc==xh&&yc==yh) return 0;
	if(ans[xc][yc][xh][yh]) return ans[xc][yc][xh][yh];
	int mintime=1e9,maxtime=0;
	for(int ii=0;ii<5;ii++)
	{
		int xxc=xc+dx[ii],yyc=yc+dy[ii];
		if(xxc<1||xxc>n||yyc<1||yyc>n||s[xxc][yyc]=='1') continue;
		getdist(xxc,yyc);
		mintime=1e9;
		vis[xxc][yyc]=1;
		int xxh,yyh,fxh,fyh,mindist=1e9,xxh2,yyh2,fxh2,fyh2,mindist3=1e9;
		for(int i=0;i<=4;i++)
		{
			xxh=dx[i]+xh;yyh=dy[i]+yh;
			if(xxh>n||xxh<1||yyh>n||yyh<1||s[xxh][yyh]=='1') continue;
			fxh=xxh;
			fyh=yyh;
			for(int j=0;j<=4;j++)
			{
				xxh2=dx[j]+fxh;yyh2=dy[j]+fyh;
				if(xxh2>n||xxh2<1||yyh2>n||yyh2<1||s[xxh2][yyh2]=='1') continue;
				if(dist[xxh2][yyh2]<=mindist)
				{
					mindist=dist[xxh2][yyh2];
					fxh2=xxh2;
					fyh2=yyh2;
				}
			}
		}
		int nxh2,nyh2;
		for(int i=0;i<=4;i++)
		{
			nxh2=xh+dx[i],nyh2=yh+dy[i];
			if(nxh2>n||nxh2<1||nyh2>n||nyh2<1||s[nxh2][nyh2]=='1') continue;
			for(int j=0;j<=4;j++)
			{
				int nxh3=nxh2,nyh3=nyh2;
				nxh3+=dx[j],nyh3+=dy[j];
				if(nxh3>n||nxh3<1||nyh3>n||nyh3<1||s[nxh3][nyh3]=='1') continue;
				if(dist[nxh3][nyh3]==mindist)
				{
					mintime=min(mintime,dfs(xxc,yyc,nxh3,nyh3)+1);
				}
			}
		}
		if(mintime==1e9) mintime=0;
		maxtime=max(maxtime,mintime);
	}
	ans[xc][yc][xh][yh]=maxtime;
	return maxtime;
}
int main()
{
	cin>>n;
	cin>>x[1]>>y[1]>>x[2]>>y[2];
	for(int i=1;i<=n;i++)
	cin>>s[i],s[i]=' '+s[i];
	getdist(x[1],y[1]);
	if(dist[x[2]][y[2]]==1e9)
	{
		cout<<"inf";
		return 0;
	}
	cout<<dfs(x[1],y[1],x[2],y[2]);
	return 0;
}

---

