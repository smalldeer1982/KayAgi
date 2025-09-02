# Obsession with Robots

## 题目描述

The whole world got obsessed with robots,and to keep pace with the progress, great Berland's programmer Draude decided to build his own robot. He was working hard at the robot. He taught it to walk the shortest path from one point to another, to record all its movements, but like in many Draude's programs, there was a bug — the robot didn't always walk the shortest path. Fortunately, the robot recorded its own movements correctly. Now Draude wants to find out when his robot functions wrong. Heh, if Draude only remembered the map of the field, where he tested the robot, he would easily say if the robot walked in the right direction or not. But the field map was lost never to be found, that's why he asks you to find out if there exist at least one map, where the path recorded by the robot is the shortest.

The map is an infinite checkered field, where each square is either empty, or contains an obstruction. It is also known that the robot never tries to run into the obstruction. By the recorded robot's movements find out if there exist at least one such map, that it is possible to choose for the robot a starting square (the starting square should be empty) such that when the robot moves from this square its movements coincide with the recorded ones (the robot doesn't run into anything, moving along empty squares only), and the path from the starting square to the end one is the shortest.

In one movement the robot can move into the square (providing there are no obstrutions in this square) that has common sides with the square the robot is currently in.

## 样例 #1

### 输入

```
LLUUUR
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
RRUULLDD
```

### 输出

```
BUG
```

# 题解

## 作者：封禁用户 (赞：14)

### 前言

吐槽一下这个翻译，什么也没说清楚。。。

题目就是说呢，有一张地图然后呢有一个机器人，他在某个地方，然后他要到达某个地方，给出了他的行进方向，问你他从某个点到某个点的是不是最短路径，L 表示 往左走，R 表示 往右走，U 表示往上走，D 表示往下走，如果是最短路径输出 `OK` 不是输出 `BUG`。

### 分析

这个问题和从哪个点开始没有太大的关系，我们唯一要考虑的就是负数的情况，那么防止负数我们可以把 $x$ 和 $y$ 设成 $101$ 这样就可以防止有负数的情况。

然后再会过来看这个问题，首先我们肯定一点，就是说**如果他走过了这个点然后再回头走这个点肯定不是最优的**。

那么我们继续思考，另外的情况。

也就是，如果**他走到的这个点除他走过来的那个点以外，其它的三个点如果有一个被走过了就证明不是最短路径**，~~就好比是你吃饱了撑的，走过一个附近的点然后旁边是最终的目的地，你还绕一圈走到这个点~~。

所以我们可以总结出来两点判断是否是最短路径。

1. 如果他走过了这个点然后再回头走这个点肯定不是最优的。

2. 他走到的这个点除他走过来的那个点以外，其它的三个点如果有一个被走过了就证明不是最短路径。

然后我们就可以利用这 $2$ 点来做这道题目。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
//头文件不多讲。
using namespace std;
const int INF=205;
int data[INF][INF],x,y,fx[]={0,0,-1,1},fy[]={1,-1,0,0};
string s1;
// data 为标记数组，标记是否走过了这个点，是就是 1 ，不是就是 0，作者比较喜欢用 int 数组。
//x y 为最开始的点。
//fx 和 fy 为方向数组。
//s1 表示 命令的读入。
inline bool check(int x_,int y_)//check 函数返回 true 表示不是最优的，false 就代表是最优的，这里千万千万不要用 x1 和 y1 否则会 CE 的，虽然作者也不知道为什么，总之就是尽量不要用 x1 和 y1。
{
        if (data[x_][y_]) return true;//如果走过了，那么就代表不是最优的。
        int tot=0;//否则我们利用一个 tot 来标记它周围有多少个格子被走过了。
        for (int i=0; i<4; i++)
        {
                int dx=fx[i]+x;
                int dy=fy[i]+y;//dx dy 表示 四个方向。
                if (data[dx][dy]) tot++;//如果走过了，那么就 +1。
        }
        return tot>1;//除走过来的那个格子以外，其它如果有，那么就返回 true。
}
signed main()
{
        x=y=101;//最开始设成 101 这样就不怕负数了，毕竟从哪个点开始都可以。
        cin>>s1;//读入命令串。
        int len=s1.size();//测量长度。
        for (int i=0; i<len; i++) {
                data[x][y]=1;//标记是否走过。
                if (s1[i]=='L') {
                        y--;//往左走那么 y-1。
                        if (check(x,y)) {//判断一下是否是最优的。
                                printf("BUG\n");
                                return 0;//不是那么就输出 BUG 并且 结束。
                        }
                }
                if (s1[i]=='R') {
                        y++;//往右走那么 y+1。
                        if (check(x,y)) {//判断一下是否是最优的。
                                printf("BUG\n");
                                return 0;//不是那么就输出 BUG 并且 结束。
                        }
                }
                if (s1[i]=='D') {
                        x++;//往下走那么 x+1
                        if (check(x,y)) {//判断一下是否是最优的。
                                printf("BUG\n");
                                return 0;//不是那么就输出 BUG 并且 结束。
                        }
                }
                if (s1[i]=='U') {
                        x--;//往上走那么 x-1
                        if (check(x,y)) {//判断一下是否是最优的。
                                printf("BUG\n");
                                return 0;//不是那么就输出 BUG 并且 结束。
                        }
                }
        }
        printf("OK\n");//如果全都是最优的那么就输出 OK ，代表是最短路径。
        return 0;
}

```

### 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

谢谢观赏！

---

## 作者：Loner_Knowledge (赞：8)


---

题意是判断从起点到终点的路径是否为最短路径。

明显的，如果该路径为如果某路径是迷宫的最短路径，那么满足以下条件：

经过的位置最多只出现一次（这是BFS求最短路的原理）

走到某个位置时，这个位置只能由刚经过的位置到达（如果这个位置旁边的某位置早已经到达过，那么那个位置走到这个位置最终的路径肯定会更短）

然后检查走过的路径是否满足以上条件即可即可

```cpp
#include<cstdio>
const int Const[2][4]={{-1,0,1,0},{0,1,0,-1}};
const char *str="URDL";
bool mark[204][204];		//标记位置是否到达过
char s[102];
int Use(char c) {
	for(int i=0;i<4;++i)
		if(c==str[i])
			return i;
	return -1;
}
bool Check(int x,int y) {		//检查是否不是最短路的函数（不是最短路返回1）
	if(mark[x][y])
		return 1;			//如果该位置已经走到过则不是最短路
	int cnt=0;				//记录该位置周围已经经过的点的数量
	for(int i,j,k=0;k<4;++k) {
		i=x+Const[0][k];
		j=y+Const[1][k];
		if(mark[i][j])
			++cnt;
	}
	return cnt>1;			//如果点的数量大于1,，则不是最短路
}
bool Solve(int x,int y) {
	mark[x][y]=1;
	for(int i=0,t;s[i];++i) {		//一步一步检查
		t=Use(s[i]);
		x+=Const[0][t];
		y+=Const[1][t];
		if(Check(x,y))
			return 0;
		mark[x][y]=1;
	}
	return 1;
}
int main() {
	scanf("%s",s);
	printf("%s",Solve(101,101)? "OK":"BUG");
	return 0;
}
```

---


---

## 作者：cyrxdzj (赞：4)

### 一、思路

**需要注意，这里的机器人并不是在走没有东西的地图，它是在走有障碍的地图，所以它可能会被迫往回走。**

机器人可以往回走，有些是为了躲避障碍，有些就是吃饱了撑着。

如何判断一个机器人的往回走是否有效？

分两种情况。

1. 同一个格子，机器人走了 $2$ 次。

   如图。
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/sxu99cix.png)
   
   显然，与其按照这个路线走，不如走 $1\Rightarrow2\Rightarrow6$ 的路线。
   
2. 走到某一个格子，此时对于四周的格子，除了刚刚走过来的格子以外，其它三个格子已经有 $1$ 个走过了。

   如图。
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/x8htl2zy.png)
   
   显然，与其按照这个路线走，不如走 $1\Rightarrow4$ 的路线。
   
由此，我们可以模拟每一步走法，并进行判断。

### 二、完整代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=205;
int graph[MAXN][MAXN];//记录一个格子是否走过。
char input[MAXN];
int x=MAXN/2,y=MAXN/2;//将初始x与y都赋值为地图中央。
int main()
{
	scanf("%s",&input);
	graph[x][y]=1;
	for(int i=0;i<strlen(input);i++)
	{
		char move=input[i];
		if(move=='U')//移动，修改坐标。
		{
			x--;
		}
		else if(move=='D')
		{
			x++;
		}
		else if(move=='L')
		{
			y--;
		}
		else if(move=='R')
		{
			y++;
		}
		if(graph[x][y])//对应情况1。
		{
			printf("BUG\n");
			return 0;
		}
		if(graph[x-1][y]+graph[x+1][y]+graph[x][y-1]+graph[x][y+1]>1)//对应情况2。
		{
			printf("BUG\n");
			return 0;
		}
		graph[x][y]=1;//标记已走过。
	}
	printf("OK\n");
	return 0;
}

```

### 三、后记

记录：<https://www.luogu.com.cn/record/51614002>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：qzhwmjb (赞：4)

### 思路
---
此题让我们判断有没有多走路。但是只给了路程方向。所以我们只需要建一个二维数组，根据当前行进指令变动 $x$ 和 $y$ 的值，同时判断四周是否只有一条路径就好了。  
注意：如果输出 $BUG$ 了就要结束，不然就可能有两个输出。
### 全代码
---
```cpp
#include<Bits/stdc++.h>//防伪标记
using namespace std;
string s;
int g[202][202];
int i,j,k;
int main(){
	cin>>s;
	int x=101,y=101,lenth=s.size();
	for(i=0;i<202;i++){
		for(j=0;j<202;j++){
			g[i][j]=0;
		}
	}//初始化。
	for(i=0;i<lenth;i++){
		g[x][y]=1;
        if(s[i]=='L'){
        	x--;//左走，x坐标减1
		}else if(s[i]=='R'){
        	x++;//右走，x坐标加1
		}else if(s[i]=='U'){
        	y++;//下走，y坐标减1
		}else if(s[i]=='D'){
        	y--;//上走，y坐标加1
		} //对应x,y,值变动。
        if(g[x][y]+g[x-1][y]+g[x][y-1]+g[x+1][y]+g[x][y+1]>1){
        	cout<<"BUG"<<endl;
        	return 0;
        }//四周出现两条及以上路径就不是最短路径,并结束。
	}
	cout<<"OK"<<endl;//是最短路径。
	return 0;
}
```


---

## 作者：sunzz3183 (赞：2)

# CF8B Obsession with Robots

## 题意

题目的意思是说一个机器人在一个图里走（**没走过的格子相当于没有，不能走**），它可以走到任意与他相邻的格子，问他走过的路径是不是最短路径（也就不走没有的格子的情况下有没有更优的走法）

$L$ 表示往左走， $R$ 表示往右走， $U$ 表示往上走， $D$ 表示往下走，如果是最短路径输出 $OK$ 不是输出 $BUG$。

## 思路

一条最短路要满足以下几个条件：

1. 不能走重复的格子。

2. 除了上一个格子，它周围的格子不能被走过（因为它周围的格子既然被走过，那么当前格子一定可以从它周围的格子总过来，并且路程更短）。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
bool book[400][400];	//book用来记录此格子有没有被走过
bool ok=0;	//ok是用来记录是否满足
string s;
int nex[4][2]={{-1,0},	//路径
				{0,-1},
				{0,1},
				{1,0},};
void dfs(int x,int y,int lx,int ly,int temp){//lx和ly用来记录上一个格子
	if(book[x][y]){	//条件1：重复走
		ok=1;
		return;
	}
	for(int i=0;i<4;i++){	//条件2：周围有格子被走过
		int tx=x+nex[i][0],ty=y+nex[i][1];
		if(tx==lx&&ty==ly)	//去除上一个格子
			continue;
		if(book[tx][ty]){
			ok=1;
			return;
		}
	}
	book[x][y]=1;	//标记
	if(s[temp]=='U')	//往下走
		dfs(x-1,y,x,y,temp+1);
	if(s[temp]=='D')	//往左走
		dfs(x+1,y,x,y,temp+1);
	if(s[temp]=='L')	//往左走
		dfs(x,y-1,x,y,temp+1);
	if(s[temp]=='R')	//往右走
		dfs(x,y+1,x,y,temp+1);
	return;
}
int main(){
	cin>>s;
	dfs(200,200,200,200,0);//一定要从（200，200）开始走，否则会数组越界
	if(ok)	//判断
		cout<<"BUG";
	else
		cout<<"OK";
	return 0;
}
```


---

## 作者：liaokq (赞：2)

一开始是练习广搜时搜到的题，但其实并不是广搜，但出于习惯还是做了QAQ

——————————————————————————

问从起点到终点的路径是否为最短路径。

判断是不是最优的方法：

**1、如果走的位置是刚才走过的，就一定不是最优**

**2、对于一个走到的位置，除过过来的方向，如果其他方向曾经走过，就一定不是最优**

其余情况均为最优

——————————————————————

用一个数组模拟即可

代码有点丑，明白就可以了：

```cpp
#include<bits/stdc++.h>
using namespace std;

bool a[205][205];//定义一个bool类型数组
string f;
int i,x=101,y=101;//初始时必须把起点放在中心
int main()
{
	a[x][y]=1;//起点
	cin>>f;
	for(i=0;i<f.size();i++)
	{
		if(f[i]=='U'){x--;if(a[x][y]==1||a[x-1][y]==1||a[x][y-1]==1||a[x][y+1]==1){cout<<"BUG"<<endl;return 0;}}//向上走
		else if(f[i]=='D'){x++;if(a[x][y]==1||a[x+1][y]==1||a[x][y-1]==1||a[x][y+1]==1){cout<<"BUG"<<endl;return 0;}}//向下走
		else if(f[i]=='L'){y--;if(a[x][y]==1||a[x-1][y]==1||a[x][y-1]==1||a[x+1][y]==1){cout<<"BUG"<<endl;return 0;}}//向左走
		else if(f[i]=='R'){y++;if(a[x][y]==1||a[x-1][y]==1||a[x+1][y]==1||a[x][y+1]==1){cout<<"BUG"<<endl;return 0;}}//向右走
		a[x][y]=1;//把这个点标记一下
	}
	cout<<"OK"<<endl;//如果还顺利的进行到现在，就肯定是最优了
	return 0;
}
```


---

## 作者：Level_Down (赞：1)

感觉这题的中文翻译稍微有些歧义，建议看英文版题面或看[这里](https://www.luogu.com.cn/discuss/show/283529)。

总之就是要判断题中所给出的路径有没有可能是最短路径。

我们可以从BFS的原理出发，可以发现只要满足两个条件这条路径就有可能是最短路径：

（1）路不重复走；

（2）不绕路。

反过来说如果发现违反了这两个条件那么这条路径一定不是最短的。

那么如何判定便成了首要问题。

对于第一个条件，很简单，只要开一个数组记录路径，每走到新的一格时判断这格以前有没有走过即可。

对于第二个条件，我们可以发现有一种情况是肯定绕了路的，如图中：

```
A B C
D E F
G H I
```

从 E → F，一次即可，但偏要走 E → B → C → F。

从BFS原理上来分析，可以走到 F 的地方有 C、E、I，但由于我们最先到过 E，所以从 E 过来绝对最快，但在第二条路径中是由 C 过来的，所以不是最短。

要实现这个判定也很简单，只需要在每次到达一个新格子后看它周围（即上下左右四个格子）是不是只有它来得时候的那个格子是被走过的，不是的话则必定有更短路径。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int ct[505][505],sx = 200,sy = 200,sum;
//sx，sy是初始位置，怎么设都行，但最好设的中间一点如（200,200），防溢出。 
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
string s;
int main()
{
	cin >> s;
	ct[sx][sy] = 1;//记录位置，下同。 
	for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == 'L') sy--;
			if (s[i] == 'R') sy++;
			if (s[i] == 'U') sx--;
			if (s[i] == 'D') sx++;//移动。 
			if (ct[sx][sy]) return printf("BUG"),0;//条件一。 
			sum = 0;
			for (int j = 0; j < 4; j++)
				{
					if (ct[sx + dx[j]][sy + dy[j]]) sum++;
				}
			if (sum != 1) return printf("BUG"),0;//条件二。 
			ct[sx][sy] = 1;//别忘了记录。	
		}
	printf("OK");	
	return 0;
}
```

若题解有错欢迎在评论区反应哦！

---

## 作者：simonG (赞：1)

### 前言
本题大意为：  
地图是一个无限的方格区域，每个方格要么是空的，要么包含一个障碍物。众所周知，机器人从不试图碰到障碍物。通过记录机器人的运动，找出是否至少存在一个这样的地图，可以为机器人选择一个起始方格（起始方格应该是空的），这样当机器人从这个方格移动时，它的运动与记录的运动一致（机器人不会碰到任何东西，只沿着空的方格移动），从起点到终点的路径最短。

### 详解
>* 1，即为最短路，先来科普一个知识。假设在一个空图（$n \times m$）内，最短路一定为$n+m$。但是，题目并非空图，就无法使用递推思想。
>* 2，这题无法用递推思想，所以我们可以用类搜索的方法做。定义横纵坐标，走过即标记。
>* 3，行走的过程中，如果遇到标记过的地方，**或是其他地方可以走过来**，就结束程序，输出。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200][200]={0};
int x=100,y=100;
string work(string str){
    a[x][y]=1;
    for(int i=0;i<str.size();i++){
        if(str[i]=='U'){
            x--;
            if(a[x][y]||a[x-1][y]||a[x][y-1]||a[x][y+1])return "BUG";
            a[x][y]=1;
        }
        if(str[i]=='D'){
            x++;
            if(a[x][y]||a[x+1][y]||a[x][y-1]||a[x][y+1])return "BUG";
            a[x][y]=1;
        }
        if(str[i]=='L'){
            y--;
            if(a[x][y]||a[x][y-1]||a[x-1][y]||a[x+1][y])return "BUG";
            a[x][y]=1;
        }
        if(str[i]=='R'){
            y++;
            if(a[x][y]||a[x][y+1]||a[x-1][y]||a[x+1][y])return "BUG";
            a[x][y]=1;
        }
    }
    return "OK";
}
int main(){
    string str;
    cin>>str;
    cout<<work(str);
    return 0;
}
```
### 后记
其实这道题还可以用最短路做，即分析他的行走路线，判断出障碍物的位置，再求解。只提供思路。

---

## 作者：Aw顿顿 (赞：1)

简单的讲一下思路：

一开始我以为是一张空图让我走，所以写了个程序就交上去了样例都没测：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool U,D,L,R;
string s;
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='U')U=1;
		if(s[i]=='D')D=1;
		if(s[i]=='L')L=1;
		if(s[i]=='R')R=1;
		if((U&&D)||(L&&R)){
			puts("BUG");
			return 0;
		}
	}puts("OK");
}
```

然后发现不对，去看了下英文题面，发现是一个类似于迷宫的一道题目，然而并不给出迷宫（也就是说可能有一些格子不能走所以会出现往回绕的情况），所以必须要按照广搜的思路来。

题意大概是这样：给出一条路径，假设这条路径在一个皇帝的新迷宫上走路，请问这个路径是否**可能**是最短路径？如果可能，输出 `OK`，否则输出 `BUG`。

“最短的”一条路必然满足这几个条件：

- 没有任何一个格子重复经过。
- 任何一个格子周围除了上一个格子，不能有任何一个格子走过。

第一句话容易理解，第二句话呢？事实上，如果存在一个格子，上一步是从左边走过来的，而上面有一个格子也被走过，那么从上面的格子走一定能到达这个格子，并且**一定在现在之前**，所以会更快。

那么满足了这两个条件，就可以确定这条路径是否最短了。

代码容易实现，且实现方法多样，此处不给出，感谢理解。

---

## 作者：胡金梁 (赞：0)

先讲一下翻译问题：最重要的部分都没翻译。就比如说我，就天真的以为是两个点（没障碍）之间的最短距离，只能用两个动作。但是题目说可能有障碍，我们又不知道障碍的位置。所以我们需要找出输出 ```BUG``` 的情况。

第一种就是你又走了一遍你走过的位置，一个点走两次肯定不是最短路了，直接输出 ```BUG``` 。

第二种比较难想，我是看了大佬的题解才悟出来的。就是你到的这个位置周围有两个及以上个点是到过的，那么肯定不是最短路，因为你放着一步就能到达的位置不走，偏要拐个大弯子从另一个地方走，也不是最短路。

接着我们说定义位置问题。因为题目说了字符串长度小于等于一百，所以考虑最坏的情况，我们把地图直接开到 $200^2$ ，初始位置就在最中间。上下左右怎么走都不会出地图。
```cpp
#include<iostream>
using namespace std;
bool mp[205][205];
bool cheak(int x,int y)
{
    if(mp[x][y])
    {
        return 1;
    }
    int dx[4]={0,0,1,-1};
    int dy[4]={1,-1,0,0},sum=0;
    for(int i=0;i<4;i++)
    {
        if(mp[x+dx[i]][y+dy[i]])
        {
            sum++;
        }
    }
    return sum>1;
}
signed main()
{
	char a,x=100,y=100;
    while(cin>>a)
    {
        mp[x][y]=1;
        if(a=='U')
        {
            x--;
            if(cheak(x,y))
            {
                cout<<"BUG"<<endl;
                return 0;
            }
        }
        if(a=='D')
        {
            x++;
            if(cheak(x,y))
            {
                cout<<"BUG"<<endl;
                return 0;
            }
        }
        if(a=='L')
        {
            y--;
            if(cheak(x,y))
            {
                cout<<"BUG"<<endl;
                return 0;
            }
        }
        if(a=='R')
        {
            y++;
            if(cheak(x,y))
            {
                cout<<"BUG"<<endl;
                return 0;
            }
        }
    }
    cout<<"OK"<<endl;
}
```


---

