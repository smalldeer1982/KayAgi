# [CERC2013] Rubik's Rectangle

## 题目描述

一种旨在征服游戏市场的新型益智游戏是魔方与十五数码的融合。棋盘是一个 $H \times W$ 的框架，上面印有从 $1$ 到 $H \cdot W$ 的所有数字。

![](/upload/images2/rubik1.png)

唯一允许的移动类型是翻转其中一行或一列。翻转会逆转该行（或列）元素的顺序。下面第三行被翻转：

![](/upload/images2/rubik2.png)

给定一个以某种任意顺序编号的棋盘。确定一系列翻转操作，使棋盘达到整齐排序的位置，如果可能的话。

![](/upload/images2/rubik3.png)

## 说明/提示

时间限制：6 秒，内存限制：128 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4

3 3
1 2 3
4 5 6
9 8 7

4 2
1 2 3 4
5 6 7 8

4 4
1 2 15 4
8 7 11 5
12 6 10 9
13 14 3 16

3 4
1 2 4
3 5 6
7 8 9
10 11 12
```

### 输出

```
POSSIBLE 1 R3
POSSIBLE 0
POSSIBLE 3 R3 C3 R2
IMPOSSIBLE
```

# 题解

## 作者：ix35 (赞：5)

显然一个格子上的数只能到达横向和竖向翻转后对称的 $4$ 个格子。

考虑这样一个“等价类”中的 $4$ 个数 $a,b,c,d$，如何能在不影响其他格子的数的情况下进行它们之间的置换。

简单考虑发现，我们可以以顺时针或逆时针方向旋转其中任意三个格子，具体做法是形如 $\texttt{URU'R'}$，这有点类似三阶魔方中的顶面三棱换。

于是我们可以算出这些可能的置换作用于 $\begin{bmatrix} a\quad b\\ c\quad d\end{bmatrix}$ 上的置换群，例如 $\begin{bmatrix} b\quad a\\ c\quad d\end{bmatrix}$ 这样是无法生成的，而 $\begin{bmatrix} b\quad a\\ d\quad c\end{bmatrix}$ 是可以生成的。

事实上我们只需先将 $a$ 换到左上角，然后看看剩下的三个是不是逆时针排列为 $b,c,d$ 的即可。

那么本题的做法如下：

- 先将四个角还原，此时可以随便操作，只要四个角对上就可以了；

- 再将四条边还原，但此时不能动角块，例如还原上下边时保证进行行翻转偶数次，而左右边时保证进行列翻转偶数次；

- 再将中间还原，只能按照上面所说的几种置换复合来实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=110;
int t,n,m,cnt,a[MAXN][MAXN],md[MAXN*MAXN*10][2];
int hs (int x,int y) {return (x-1)*m+y;}
void trip (int x,int y,int t) {
	if (t==1) {
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=x;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=x;
		swap(a[x][y],a[x][m-y+1]);
		swap(a[x][y],a[n-x+1][y]);
	} else if (t==2) {
		cnt++;
		md[cnt][0]=1,md[cnt][1]=x;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=m-y+1;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=x;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=m-y+1;
		swap(a[x][y],a[n-x+1][m-y+1]);
		swap(a[x][m-y+1],a[n-x+1][m-y+1]);
	} else if (t==3) {
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		swap(a[x][y],a[n-x+1][y]);
		swap(a[n-x+1][y],a[n-x+1][m-y+1]);
	} else {
		cnt++;
		md[cnt][0]=2,md[cnt][1]=m-y+1;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		cnt++;
		md[cnt][0]=2,md[cnt][1]=m-y+1;
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		swap(a[x][m-y+1],a[n-x+1][m-y+1]);
		swap(a[x][m-y+1],a[n-x+1][y]);
	}
	return;
}
int solve (int x,int y,int t) {
	int uu=a[x][y],vv=a[x][m-y+1],xx=a[n-x+1][y],yy=a[n-x+1][m-y+1];
	int tmp1[5],tmp2[5];
	tmp1[1]=uu,tmp1[2]=vv,tmp1[3]=xx,tmp1[4]=yy;
	tmp2[1]=hs(x,y),tmp2[2]=hs(x,m-y+1),tmp2[3]=hs(n-x+1,y),tmp2[4]=hs(n-x+1,m-y+1);
	sort(tmp1+1,tmp1+5);
	sort(tmp2+1,tmp2+5);
	for (int i=1;i<=4;i++) {if (tmp1[i]!=tmp2[i]) {return 0;}}
	int u=(uu>vv)+(uu>xx)+(uu>yy)+1,v=(vv>uu)+(vv>xx)+(vv>yy)+1;
	int xxx=(xx>uu)+(xx>vv)+(xx>yy)+1,yyy=(yy>uu)+(yy>vv)+(yy>xx)+1;
	if (v==1) {
		trip(x,y,2),trip(x,y,2);
	} else if (xxx==1) {
		trip(x,y,1);
	} else if (yyy==1) {
		trip(x,y,2);
	}
	uu=a[x][y],vv=a[x][m-y+1],xx=a[n-x+1][y],yy=a[n-x+1][m-y+1];
	u=(uu>vv)+(uu>xx)+(uu>yy)+1,v=(vv>uu)+(vv>xx)+(vv>yy)+1;
	xxx=(xx>uu)+(xx>vv)+(xx>yy)+1,yyy=(yy>uu)+(yy>vv)+(yy>xx)+1;
	if (xxx==2) {
		trip(x,y,4);
	} else if (yyy==2) {
		trip(x,y,4),trip(x,y,4);
	}
	uu=a[x][y],vv=a[x][m-y+1],xx=a[n-x+1][y],yy=a[n-x+1][m-y+1];
	u=(uu>vv)+(uu>xx)+(uu>yy)+1,v=(vv>uu)+(vv>xx)+(vv>yy)+1;
	xxx=(xx>uu)+(xx>vv)+(xx>yy)+1,yyy=(yy>uu)+(yy>vv)+(yy>xx)+1;
	if (xxx==3) {return 1;}
	if (t==0) {return 0;}
	if (t==1) {
		cnt++;
		md[cnt][0]=1,md[cnt][1]=n-x+1;
		for (int i=1;i<=m/2;i++) {swap(a[n-x+1][i],a[n-x+1][m-i+1]);}
	} else {
		cnt++;
		md[cnt][0]=2,md[cnt][1]=y;
		for (int i=1;i<=n/2;i++) {swap(a[i][y],a[n-i+1][y]);}
		trip(x,y,3);
	}
	return 1;
}
void print () {
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}
int main () {
	scanf("%d",&t);
	for (int ii=1;ii<=t;ii++) {
		scanf("%d%d",&n,&m); 
		swap(n,m);
		cnt=0;
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=m;j++) {
				scanf("%d",&a[i][j]);
			}
		}
		int flg=0;
		if (n!=1&&m!=1) {
			
		for (int i=1;i<=n/2;i++) {
			if (!solve(i,1,1)) {flg=1;break;}
		}
		for (int j=2;j<=m/2;j++) {
			if (!solve(1,j,2)) {flg=1;break;}
		}
		
		}
		//print();
		for (int i=2;i<=n/2;i++) {
			if (flg) {break;}
			for (int j=2;j<=m/2;j++) {
				if (!solve(i,j,0)) {
					flg=1;
					break;
				}
			}
		}
		//print();
		if (n%2==1) {
			int flg2=1,rw=(n+1)/2;
			for (int i=1;i<=m;i++) {
				if (a[rw][i]!=hs(rw,i)) {flg2=0;break;}
			}
			if (!flg2) {
				flg2=1;
				for (int i=1;i<=m;i++) {
					if (a[rw][i]!=hs(rw,m-i+1)) {flg2=0,flg=1;break;}
				}
				if (flg2) {
					cnt++;
					md[cnt][0]=1,md[cnt][1]=rw;
					for (int i=1;i<=m/2;i++) {swap(a[rw][i],a[rw][m-i+1]);}
				}
			}
		}
		if (m%2==1) {
			int flg2=1,col=(m+1)/2;
			for (int i=1;i<=n;i++) {
				if (a[i][col]!=hs(i,col)) {flg2=0;break;}
			}
			if (!flg2) {
				flg2=1;
				for (int i=1;i<=n;i++) {
					if (a[i][col]!=hs(n-i+1,col)) {flg2=0,flg=1;break;}
				}
				if (flg2) {
					cnt++;
					md[cnt][0]=2,md[cnt][1]=col;
					for (int i=1;i<=n/2;i++) {swap(a[i][col],a[n-i+1][col]);}
				}
			}
		}
		if (flg) {
			printf("IMPOSSIBLE\n");
		} else {
			printf("POSSIBLE %d",cnt);
			for (int i=1;i<=cnt;i++) {
				if (md[i][0]==1) {printf(" R%d",md[i][1]);}
				else {printf(" C%d",md[i][1]);}
			}
			printf("\n");
		}
	}
	return 0;
}
```


---

