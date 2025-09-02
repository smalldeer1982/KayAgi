# Special Grid

## 题目描述

You are given an $ n×m $ grid, some of its nodes are black, the others are white. Moreover, it's not an ordinary grid — each unit square of the grid has painted diagonals.

The figure below is an example of such grid of size $ 3×5 $ . Four nodes of this grid are black, the other $ 11 $ nodes are white.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435D/2a129804a620070f064ad9f06e8026399abd5ad7.png)Your task is to count the number of such triangles on the given grid that:

- the corners match the white nodes, and the area is positive;
- all sides go along the grid lines (horizontal, vertical or diagonal);
- no side contains black nodes.

## 说明/提示

The figure below shows red and blue triangles. They are the examples of the required triangles in the first sample. One of the invalid triangles is painted green. It is invalid because not all sides go along the grid lines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435D/f9604961f586e4f0664ffd8ad99709dfacd15973.png)

## 样例 #1

### 输入

```
3 5
10000
10010
00001
```

### 输出

```
20
```

## 样例 #2

### 输入

```
2 2
00
00
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2 2
11
11
```

### 输出

```
0
```

# 题解

## 作者：YanYou (赞：0)

# Solution

本题显然有一个DP的思想。

这里直接上状态：$f[i][j][k]$ 表示点 $(i,j)$ 向方向 $k$ 符合要求的最长延伸长度。

显然可以在 $O(n^3)$ 的时间内求出，不会 $TLE$ 。

接下来枚举直角顶点 $(i,j)$ ，对于每个方向，用已经求出的 $f$ 数组判断斜边上是否有黑点，累加答案即可。

具体见代码。




# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=405;
const int dx[8]={0,-1,-1,-1,0,1,1,1};
const int dy[8]={-1,-1,0,1,1,1,0,-1};
int n,m,a[N][N],f[N][N][8],ans;
char ch;

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			cin>>ch;
			a[i][j]=ch-'0';
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=0;k<4;++k)
			{
				int x=i,y=j;
				while(x>0&&x<=n&&y>0&&y<=m&&a[x][y]==0)x+=dx[k],y+=dy[k];
				f[i][j][k]=(i-x!=0?i-x:j-y);
			}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)if(a[i][j]==0)
			for(int k=0;k<8;++k)
			{
				int l=(k+2)%8,w=(k+3)%4;
				for(int t=1;t<min(n,m);++t)
				{
					int xp=i+t*dx[k],yp=j+t*dy[k],xq=i+t*dx[l],yq=j+t*dy[l];
					if(xp<=0||xp>n||yp<=0||yp>m||xq<=0||xq>n||yq<=0||yq>m)break;
					if(a[xp][yp]==1||a[xq][yq]==1)break;
					if(k>=1&&k<=4)
					{
						if((dx[w]==0||f[xq][yq][w]>(xp-xq)/dx[w])&&(dy[w]==0||f[xq][yq][w]>(yp-yq)/dy[w]))
							ans++;
					}else
					{
						if((dx[w]==0||f[xp][yp][w]>(xq-xp)/dx[w])&&(dy[w]==0||f[xp][yp][w]>(yq-yp)/dy[w]))
							ans++;
					}
				}
			}
	cout<<ans<<"\n";
	return 0;
}
```


---

