# Tetris revisited

## 题目描述

给定一个 $n \times m$ 的游戏盘，盘内有一些格子已被填充，要求用一些图形将剩余空格填满。

可用图形都以2~5个单元格组成，包含了将2~5个单元格共边连接的所有情况，填充时可以旋转和翻转。

## 样例 #1

### 输入

```
2 3
...
#.#
```

### 输出

```
000
#0#
```

## 样例 #2

### 输入

```
3 3
.#.
...
..#
```

### 输出

```
5#1
511
55#
```

## 样例 #3

### 输入

```
3 3
...
.##
.#.
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
1 2
##
```

### 输出

```
##
```

# 题解

## 作者：EnofTaiPeople (赞：2)

看在没人写题解，我就来写一篇。

题目给定了一个 $n\times m$ 个格子的矩形，有些格子已经填满，要求将剩余的划分成大小为 $2\sim5$ 的四连通块，并染上 $0\sim9$ 的 颜色，相邻不同颜色的格子看作不同块。

不妨设格子的度数为其四周未染色（填满了视作染了色）格子个数。

如果初始情况存在度数为零的格子，显然无解，否则，选取一个没染色的格子。

考虑如果这个格子的四周是否有度数为一的格子，如果有，将其与所有度数为一的相邻格子染上相同的颜色，容易发现剩下的连通块大小仍为偶数。

如果没有，随便取一个相邻格子，将这两个格子与该相邻格子相邻且度数为一的格子染上相同颜色。

注意要计算出与相邻连通块均不相同的颜色，枚举即可，时空复杂度 $O(n+m)$：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
char s[N][N];
int n,m,g[N][N],h[N][N];
int X[N],Y[N],tp,up;
void adg(int x,int y,int p){
	g[x-1][y]+=p,g[x][y-1]+=p;
	g[x+1][y]+=p,g[x][y+1]+=p;
}
void adn(int x,int y,int p){
	s[x][y]=p+48;
	h[x-1][y]|=1<<p;
	h[x][y-1]|=1<<p;
	h[x+1][y]|=1<<p;
	h[x][y+1]|=1<<p;
}
void adt(int x,int y){
	X[++tp]=x,Y[tp]=y;
	up|=h[x][y];
}
int ckg(int x,int y){
	return (s[x][y]=='.'&&g[x][y]==1);
}
int main(){
	scanf("%d%d",&n,&m);
	int i,j,x,y,p;
	for(i=1;i<=n;++i){
		scanf("%s",s[i]+1);
		for(j=1;j<=m;++j)
			if(s[i][j]=='.')adg(i,j,1);
	}
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			if(s[i][j]=='.'&&!g[i][j]){
				puts("-1");return 0;
			}
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			if(s[i][j]=='.'){
				tp=up=0,adt(i,j);
				if(ckg(i+1,j))adt(i+1,j);
				if(ckg(i,j+1))adt(i,j+1);
				if(tp==1){
					if(s[i+1][j]=='.'){
						adt(i+1,j);
						if(ckg(i+2,j))adt(i+2,j);
						if(ckg(i+1,j-1))adt(i+1,j-1);
						if(ckg(i+1,j+1))adt(i+1,j+1);
					}else if(s[i][j+1]=='.'){
						adt(i,j+1);
						if(ckg(i,j+2))adt(i,j+2);
						if(ckg(i+1,j+1))adt(i+1,j+1);
					}
				}
				for(x=0;(up>>x)&1;++x);
				for(p=1;p<=tp;++p)adg(X[p],Y[p],-1),adn(X[p],Y[p],x);
			}
	for(i=1;i<=n;++i){
		s[i][m+1]='\n';
		fwrite(s[i]+1,1,m+1,stdout);
	}
	return 0;
}
```

---

