# Playing with Superglue

## 题目描述

Two players play a game. The game is played on a rectangular board with $ n×m $ squares. At the beginning of the game two different squares of the board have two chips. The first player's goal is to shift the chips to the same square. The second player aims to stop the first one with a tube of superglue.

We'll describe the rules of the game in more detail.

The players move in turns. The first player begins.

With every move the first player chooses one of his unglued chips, and shifts it one square to the left, to the right, up or down. It is not allowed to move a chip beyond the board edge. At the beginning of a turn some squares of the board may be covered with a glue. The first player can move the chip to such square, in this case the chip gets tightly glued and cannot move any longer.

At each move the second player selects one of the free squares (which do not contain a chip or a glue) and covers it with superglue. The glue dries long and squares covered with it remain sticky up to the end of the game.

If, after some move of the first player both chips are in the same square, then the first player wins. If the first player cannot make a move (both of his chips are glued), then the second player wins. Note that the situation where the second player cannot make a move is impossible — he can always spread the glue on the square from which the first player has just moved the chip.

We will further clarify the case where both chips are glued and are in the same square. In this case the first player wins as the game ends as soon as both chips are in the same square, and the condition of the loss (the inability to move) does not arise.

You know the board sizes and the positions of the two chips on it. At the beginning of the game all board squares are glue-free. Find out who wins if the players play optimally.

## 样例 #1

### 输入

```
1 6 1 2 1 6
```

### 输出

```
First```

## 样例 #2

### 输入

```
6 5 4 3 2 1
```

### 输出

```
First```

## 样例 #3

### 输入

```
10 10 1 1 10 10
```

### 输出

```
Second```

# 题解

## 作者：hongshixiaobai (赞：1)

# CF176C Playing with Superglue 题解
[传送门](https://www.luogu.com.cn/problem/CF176C)
## 思路
手模一下，发现如果两步之后两颗棋子的 $x$ 或 $y$ 坐标之差中大的那个 $\max(d_x,d_y)>2$，那么玩家 B 就可以通过如下方式获胜：

![](https://cdn.luogu.com.cn/upload/image_hosting/7p5sqwl4.png)

（叉是胶水，圆是棋子）

知道了这一点之后容易发现，最后的结论就是：如果 $x$ 距离之差 $d_x$ 与 $y$ 距离之差 $d_y$ 中大的那个 $\max(d_x,d_y)>4$ 或 $\max(d_x,d_y) = 4$ 且  $\min(d_x,d_y) = 3$ 就输出 `second` 否则输出 `first`

注：代码最好不要用 `x1` `x2` `y1` `y2` 作为变量名，因为你谷过不了但 CF 和 CCF 能过~~推荐用 `x[2]` `y[2]`~~。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int c,k,x[2],y[2],d[2];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin>>c>>k>>x[0]>>y[0]>>x[1]>>y[1];
	d[0] = abs(x[0]-x[1]);
	d[1] = abs(y[0]-y[1]);
	if(d[0]<d[1])swap(d[0],d[1]);
	if((d[0] == 4&&d[1] == 3)||d[0]>4)cout<<"second";
	else cout<<"first";
}  
```

---

## 作者：Lijunzhuo (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF176C)  
这道题我们可以用模拟的方式来找规律。  
我们可以得到——  
若棋子曼哈顿距离分别为 $d1$ 和 $d2$ ，如果   
```latex
d1>=3&&d2>=4||(d1>4||d2>4)
```

那么输出“ $\texttt{Second}$ ”，否则输出“ $\texttt{First}$ ”。  

为什么呢？  
可以这样理解，先手和后手的目标是使两点重合。如果横向或纵向的距离差不足   $3$，则两点有可能在下一步就重合了，此时先手无法继续操作，后手获胜。  

如果横向和纵向的距离差至少为 $3$，并且至少有一方的距离差超过 $4$，那么显然先手可以进行一些特定的操作，例如在距离较短的那个方向上来回移动，或者向中心点移动，从而使得后手无论如何都无法阻止两点的重合，这样先手就获得了胜利。  

当横向和纵向的距离差都大于 $4$ 时，先手更容易控制两点的相对位置，这可以看作是一个更加优势的局面。即使后手想要阻止两点的重合，先手也有足够的操作空间来反击，最终取得胜利。  

因此，需要满足上述条件才能让先手获胜。如果不满足这些条件，后手有可能利用先手某些操作的局限性，最终获得胜利。

知道了规律，我们就能轻松地做对这道题了，时间复杂度为 $O(1)$。  
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x1,x2,y1,y2,d1,d2;
int main()
{
	scanf("%d%d%d%d%d%d",&n,&m,&x1,&y1,&x2,&y2);
	d1=abs(x1-x2);
	d2=abs(y1-y2);
	if(d2<d1) swap(d1,d2);
	if(d1>=3&&d2>=4||(d1>4||d2>4))
		printf("Second\n");
	else printf("First\n");
	return 0;
}
/*
if(d1>=3&&d2>=4||(d1>4||d2>4))
	printf("Second\n");
else printf("First\n");
可以改成：
printf("%s\n",d1>=3&&d2>=4||(d1>4||d2>4)?"Second":"First");
*/
```

---

## 作者：MsgNotFound (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF176C)

# 思路分析
首先，将两枚棋子的曼哈顿距离设为 $dis_1$ 和 $dis_2$，首先判断 $dis_1$ 是否大于 $dis_2$，如果是的话，使用 `swap(dis1,dis2);` 语句来进行交换值。经过模拟后，可以得出：如果

$(dis_1\ge3∧dis_2\ge4)∨(dis_1>4)∨(dis_2>4)$


这个条件成立，则输出 $\texttt{Second}$，反之则输出 $\texttt{Frist}$。

明白了这一点，我们就可以直接写出代码了，时间复杂度是 $O(1)$。

话不多说，上代码：

```cpp
#include<cmath>// 需要用到abs函数
#include<iostream>
using namespace std;
int n,m,x1,x2,y1,y2;
void check(int dis1,int dis2){
	if(dis1>dis2)swap(dis1,dis2);
	if(dis1>=3&&dis2>=4||(dis1>4||dis2>4))cout<<"Second";
	else cout<<"First";
}// dis1和dis2是曼哈顿距离，这个函数实现上述功能
int main(){
    int n,m,x1,y1,x2,y2;// 变量定义
    cin>>n>>m>>x1>>y1>>x2>>y2;
    int d1=abs(x1-x2),d2=abs(y1-y2);
    check(d1,d2);
    return 0;
}
```
**养成良好习惯，不要抄袭哦！**

---

## 作者：__CrossBow_EXE__ (赞：0)

一道简单的模拟题。首先记录下点 $x$ 和点 $y$ 的曼哈顿距离，再通过它们的曼哈顿距离进行判断即可。
```cpp
/*
题目：CF176C
时间复杂度：O(1)（或许是？） 
15 行极简代码，已AC，请放心食用。 
*/
#include<bits/stdc++.h>
using namespace std;
void judge(int dis1,int dis2){
	//判断及输出 
	if(dis1>dis2) swap(dis1,dis2);
	if(dis1>=3&&dis2>=4||(dis1>4||dis2>4)) cout<<"Second";
	else cout<<"First";
}
int main(){
    int n,m,x1,y1,x2,y2;
    cin>>n>>m>>x1>>y1>>x2>>y2;
    int dis1_=abs(x1-x2),dis2_=abs(y1-y2);//这里我是想让变量名与函数中的参数名不相同，实际作用不大。 
    judge(dis1_,dis2_);
    return 0;
}
```

---

## 作者：frankchenfu (赞：0)

正解：手动模拟，找出规律。至于证明，本人不会，网络上也没有中文博客的可靠资料。

设两个棋子时间曼哈顿距离为`dist1`和`dist2`，那么请注意`dis1==3&&dis2==4`的情况时后手，其余容易模拟得出。

```cpp
#include<cstdio>
#include<cstring>

unsigned int abs(int x){
	return x<0?-x:x;
}
void swap(int &x,int &y){
	int t=x;x=y;y=t;
}

int main(){
    int n,m;scanf("%d%d",&n,&m);
    int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    int dis1=abs(x1-x2);
    int dis2=abs(y1-y2);
    if(dis1>dis2)
		swap(dis1,dis2);
	if(dis1>=3&&dis2>=4||(dis1>4||dis2>4))
		puts("Second");
	else
		puts("First");
    return 0;
}
```

---

