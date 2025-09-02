# Dasha and Chess

## 题目描述

这是一道交互题。

Dasha 和 NN 喜欢下象棋。在对弈时他们觉得普通象棋不够有趣，于是发明了下面这个游戏。

在一个 $999 \times 999$ 的棋盘上，有 $666$ 个黑车和 $1$ 个白王。当白王移动到与任意黑车同行或同列的位置时（即被将军），白王获胜。

双方轮流行动，白方先行。NN 操控白王，每次可以将王移动到相邻的格子（包括对角线），即如果王在 $(x,y)$，可以移动到 $(nx,ny)$，只要满足 $\max(|nx-x|,|ny-y|)=1$ 且 $1 \leq nx,ny \leq 999$。王不能移动到已有黑车的格子，但可以与黑车同行或同列。

Dasha 不按常规象棋规则移动车，而是每次选择任意一个黑车移动到棋盘上未被占据的任意位置（可以保持原位）。但她不能将车移动到与王同行或同列的位置。

双方各进行 $2000$ 回合后，若白王未被将军，则黑方获胜。

NN 不想输，但觉得这个任务太难，于是请你编写一个程序来操控白王，确保总能获胜。注意 Dasha 能看到你的王的位置并据此调整策略。

## 说明/提示

样例经过精简。第一个测试用例中所有黑车的初始位置详见 <https://pastebin.com/qQCTXgKP>。不保证黑车会如样例中那样移动。

## 样例 #1

### 输入

```
999 999
1 1
1 2
2 1
2 2
1 3
2 3
&lt;...&gt;
26 13
26 14
26 15
26 16

1 700 800

2 1 2

&lt;...&gt;

-1 -1 -1
```

### 输出

```










999 998

999 997

&lt;...&gt;

999 26
```

# 题解

## 作者：_sys (赞：8)

题意：

***本题为交互题。***

***你有一个$999*999$的棋盘，其中有$666$个小兵和一个国王，小兵和国王的位置都不重复。***

***你需要操控国王，每次可向相邻的八个位置走去，但不能走出边界，不能走在已经有小兵的位置。***

***对方操控$666$个小兵。每次你操作完后，对方可以选择一个小兵并让他瞬移至场上某一个空位置，并告诉你移动的信息。具体来说，你将获得$k,a,b$，表示第$k$个小兵移动到了$(a,b)$处。***

***你获胜的条件是某一次对方操纵完毕时，有小兵与国王在同一列或同一行。***

***你最多有$2000$次操作机会，你也可以选择不走，每一次，你需要输出国王当前所在的位置。***

***当你获胜时，对方将输出"$-1 -1 -1$"，这时你应该结束你的程序，不输出任何东西。***

那么我们考虑，对于国王，他获胜当且仅当他走到的位置所在的行列中存在至少$2$个小兵。

我们可以首先让国王走到$(500,500)$，此时棋盘被划分为$4$个区域，即：

![King(500,500)](https://cdn.luogu.com.cn/upload/pic/48597.png)

我们考虑小兵数量最多的三块，他们的和肯定大于等于$\lceil \frac{3}{4}*666\rceil=500$，然而国王从$(500,500)$走到某个边角只需要$499$次，我们可以发现：

![King go to (1,1)](https://cdn.luogu.com.cn/upload/pic/48598.png)

拿$(1,1)$举例，我们发现从$(500,500)$走到$(1,1)$能够覆盖$\frac{3}{4}$的棋盘，如果这$\frac{3}{4}$的棋盘中有大于$499$个小兵，那么对方就是无法在国王到达之前把所有的小兵挪走的，而根据上文，我们可以找到$\frac{3}{4}$的棋盘包含至少$500$个小兵。本题解决。

注意要判断下面的情况

![special](https://cdn.luogu.com.cn/upload/pic/48920.png)

此时橙色为King所在位置。

如果King要往右上方走，在$(x+1,y+1)$处有小兵。

- 如果某个绿色部分有一个小兵，那么直接获胜
- 否则，直接朝一个方向走去，对方肯定会挪动蓝色区域的小兵。这样，我们还能多争取到一步。

这样走下来，最坏的情况也最多也就会多增加一步(如果有许多$x$或者$y$满足$(x+1,y+1)有小兵$，那就是第一种情况)，我们仍可接受。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int x=999,y=999,k=666;
bool vis[1005][1005];
int cnt[5];
struct point
{
	int x,y;
}king,rook[k+5];
void move(int dx,int dy)
{
	king.x+=dx,king.y+=dy;
	if(vis[king.x][king.y]) king.x-=dx;
	printf("%d %d\n",king.x,king.y);
	fflush(stdout);
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	if(a==-1&&b==-1&&c==-1) exit(0);
	vis[rook[a].x][rook[a].y]=false;
	rook[a].x=b,rook[a].y=c;
	vis[rook[a].x][rook[a].y]=true;
}
int main()
{
	scanf("%d%d",&king.x,&king.y);
	for(int i=1;i<=k;i++)
		scanf("%d%d",&rook[i].x,&rook[i].y),vis[rook[i].x][rook[i].y]=true;
	while(king.x>500) move(-1,0);
	while(king.x<500) move(1,0);
	while(king.y>500) move(0,-1);
	while(king.y<500) move(0,1);
	for(int i=1;i<=k;i++)
		cnt[(rook[i].x<500)*2+(rook[i].y<500)]++;
	int mini=0x3f3f3f3f,pnt;
	for(int i=0;i<=3;i++)
		if(mini>cnt[i]) mini=cnt[i],pnt=i;
	while(1) move(pnt/2?1:-1,pnt%2?1:-1);
	return 0;
}
```

---

## 作者：Dispwnl (赞：3)

#### [博客](https://a-failure.github.io/2019/01/14/CF1100X-Codeforces-Round-532-(Div.-2)/)

#### 题解

如果白王移动到$(500,500)$的话，会把棋盘分为$4$块

最劣情况下，任意$3$块棋盘的和的最大值为$166+167+167=500$

这样移动白王向最大值的方向移动，相当于横纵坐标都扫一遍，最劣情况下也会有至少一行/列黑车的数量$>=2$，所以这样存在必胜策略

#### 代码

```c++
# include<bits/stdc++.h>
using namespace std;
const int MAX=1e3+5;
struct p{
	int x,y;
}s[MAX];
int X,Y;
bool use[MAX][MAX];
void ask(int _x,int _y)
{
	int k,x,y;
	if(use[X+_x][Y+_y]) _y=0;
	printf("%d %d\n",X+=_x,Y+=_y);
	fflush(stdout);
	scanf("%d%d%d",&k,&x,&y);
	if(k==-1) exit(0);
	if(!k) exit(0);
	use[s[k].x][s[k].y]=0,use[s[k].x=x][s[k].y=y]=1;
}
int main()
{
	scanf("%d%d",&X,&Y);
	for(int i=1;i<=666;++i)
	  scanf("%d%d",&s[i].x,&s[i].y),use[s[i].x][s[i].y]=1;
	while(X<500) ask(1,0);
	while(X>500) ask(-1,0);
	while(Y<500) ask(0,1);
	while(Y>500) ask(0,-1);
	int cnt1=0,cnt2=0,cnt3=0,cnt4=0;
	for(int i=1;i<=999;++i)
	  for(int j=1;j<=999;++j)
	    if(use[i][j])
		{
			if(i<500||j<500) ++cnt1;
			if(i<500||j>500) ++cnt2;
			if(i>500||j<500) ++cnt3;
			if(i>500||j>500) ++cnt4;
		}
	if(cnt1>=500) while(1) ask(-1,-1);
	if(cnt2>=500) while(1) ask(-1,1);
	if(cnt3>=500) while(1) ask(1,-1);
	if(cnt4>=500) while(1) ask(1,1);
	return 0;
}
```



---

