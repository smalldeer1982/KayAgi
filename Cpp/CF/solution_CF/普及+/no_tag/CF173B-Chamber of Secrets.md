# Chamber of Secrets

## 题目描述

**“密室再次被打开了。”**——这个消息传遍了霍格沃茨，而一些学生因为看到蛇怪而被石化。虽然邓布利多被迫离开了学校，但哈利正尝试进入密室。而这对伏地魔可不是什么好消息。他不希望任何人进入密室。因为他正在吸取金妮的灵魂。

密室是一个$n×m$的矩形网格，其中一些单元格有柱子。光线（蛇怪的凝视）可以穿过柱子而不改变方向。但是通过一些魔咒，我们可以让柱子在接收光线时反射所有光线向四个方向射去。如下图所示。

左边光线穿过没有施魔法的柱子，右边光线穿过施魔法的柱子，效果如图。蛇怪在密室的右下角，向左边凝视。据传说，直接看见蛇怪的眼睛就会马上死亡，而看到通过柱子的反射光线就会被石化。我们知道，密室的入口在左上角，而进入的人必须注视他所要移动的方向。图片就是第一个样例。

给定密室的大小，和普通柱子的位置，伏地魔想要让你对最少的柱子施法，**使所有人不能进入密室**；或者表示不能完成保护密室的任务。

## 说明/提示

图片为样例解释，将两根柱子都施魔法才可以阻止哈利进入密室。

## 样例 #1

### 输入

```
3 3
.#.
...
.#.
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
##.
...
.#.
.#.
```

### 输出

```
2
```

# 题解

## 作者：jzcrq (赞：16)

## CF173B 非BFS题解
目前本题题解均为BFS题解，所以这里给出不同的解法
***
 题目链接：
 
 [CF173B Chamber of Secrets —— 洛谷](https://www.luogu.com.cn/problem/CF173B)

 [CF173B Chamber of Secrets —— Codeforces](http://codeforces.com/problemset/problem/173/B)
***
观前提示：本文中的行指水平方向的横行，列指竖直方向的纵列。
***
### 题意分析：
题目的描述虽形象，易于理解，但是不易于程序的实现，考虑对题目进行简化。

- 未施法的柱子等于空格子。

- 因为光线可以在任何格子上沿着原来的方向传播，所以施法柱子的实际作用为改变光线方向。

- 光线从左上角或右下角来对结果没有影响。（可以理解为光路可逆）

**所以我们可以将题目转变成：**

**一束光线从左上角水平射出，遇到施法柱子就转弯（水平转竖直，竖直转水平），要求光线向右下角水平射出。**
***
### 定义：
- $line$ ：行。

- $row$ ：列。

- $length$ ：长度。

- $step$ ：施法柱子的个数，也可以把它认为光线行走的“步数”，因为本题中光线行走的代价就是经过施法柱子的个数。

- $step_{max}$ ：$n,m$ 一定时，满足伏地魔要求下施法柱子最多的个数。

- $f_{max}$ ：$n,m$ 一定时，满足伏地魔要求下施法柱子最多的情况。（即问题可解情况下，最优策略的最坏情况。）（可以结合 $step_{max}$ 部分的图例理解。）

- $f_{fail}$ ：不可解的情况。

因为前文中提到，光线从左上角或右下角来对结果没有影响，所以本文会将左上角作为起点，右下角作为终点，方便理解。
***
### 初步思路：

不难发现，首末行没有柱子的情况，一定是 $f_{fail}$ 。而首末行有柱子的情况下，如果能到达末行的柱子，意味着能到达终点，如果能到达首行的柱子，意味着能到达起点。

换句话说，起点被转移到了首行的柱子上，终点被转移到了末行的柱子上。

而当起点与终点在同行或同列时，意味着该图可解。

那我们是不是可以一直这样转移下去呢？

于是我们有了下面的思路：

思路 1. 起点与终点可以转化为首行与末行的柱子，进而转化为他们所在列的柱子，再转化成其所在行的柱子......起点和终点相遇就说明可以到达终点。

思路 2. 只转化起点，如果转化后的起点在末行，则可以到达终点，否则继续转化。

在可解的情况下通过 $step$ 次的转化就能找到一组在同一行或列的起点与终点。

而如果在 $step_{max}$ 次转化后依然不存在这样的一组起点与终点，就说明该情况不可解。
***
思路 1 与 2 本质上是一致的，只不过一个是两点互找，一个是起点找终点，同样的道理，终点找起点也是可行的。所以后面的部分以细节较复杂的思路1为例，另外两种基本同理。

举个可解的栗子：

![](https://cdn.luogu.com.cn/upload/image_hosting/zn0npwgp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们用 " 1 " 表示柱子，能够转化为下面的矩形：

![](https://cdn.luogu.com.cn/upload/image_hosting/lbwkxacg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们在每行每列加一个表头记录该行列是否出现转移后的起点、终点，上面的矩形就能通过如下步骤逐步求解：

- $step_1$ ：

![](https://cdn.luogu.com.cn/upload/image_hosting/snczrxlz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- $step_2$ ：

![](https://cdn.luogu.com.cn/upload/image_hosting/33930wx6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- $step_3$ ：

![](https://cdn.luogu.com.cn/upload/image_hosting/w04zsmw6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- $step_4$ ：

![](https://cdn.luogu.com.cn/upload/image_hosting/07quqven.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- $step_5$ ：

![](https://cdn.luogu.com.cn/upload/image_hosting/g134cplo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- $step_6$ ：

![](https://cdn.luogu.com.cn/upload/image_hosting/xlctk9f6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以上面的栗子的 $step=6$ 。

每次的转换相当于“走一步”，每次转换如果同时涉及多根柱子，说明这些柱子不会在最短可解路径中同时存在，如果同一步内有多个行列出现起点与终点相遇，说明该情况存在多个最短可解路径。

弄明白了可解的栗子，不可解的问题就只剩下 $step_{max}$ 了。
***
### 如何求 $step_{max}$

因为 $step_{max}=step_{f_{max}}$ ，所以我们可以从 $f_{max}$ 入手。

由题意可知：

每个施法柱子的作用是将光线转向，因为光线进入的方向和到达终点的方向相同（水平方向），所以施法柱子的个数应当是偶数个，并且为了策略最优，每行每列最多只有两个柱子，分别完成将光线引入该（行/列），将光线导出该（行/列）的任务。

**所以 $f_{max}$ 具有性质：首行与末行以外的每行每列，要么同时存在两个施法柱子，要么不存在施法柱子，首行末行各存在一个施法柱子。**

这种条件下的 $f_{max}$ 可以存在多个，但因为每根施法柱子都会使其所在行列能容纳的施法柱子-1。所以每个 $f_{max}$ 的施法柱子的个数是一样的，我们只需要构造一些熟悉，形象的 $f_{max}$ 探究即可。

如：

1. 转圈圈型：（即前文的例子）

![](https://cdn.luogu.com.cn/upload/image_hosting/wnb4fj79.png)

2. 下楼梯型：

![](https://cdn.luogu.com.cn/upload/image_hosting/ep809f70.png)

聪明的你想必会发现，这两种 $f_{max}$ 都空出了一列，但都无法再插入一个施法柱子。
***
空出的为什么是一列而不是一行呢？

假如你可以捏住图片的左上角和右下角，然后对其翻转，空出的一列就变成了一行。

以下楼梯型为例，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/sk1y2l3q.png)

翻转的地方可能语言表述不够周到，可以参照两张图右下角水印的变化理解。

在进行该翻转操作的同时，我们把左上角的第一个箭头从竖直向下转成了水平向右。

而因为题目中光线刚开始沿水平方向射入，所以第一次经过施法柱子后的方向应该是竖直方向，所以该翻转不能进行。

为什么会空出这一列呢？

注意观察，上面两幅图都是迷宫为 $4*4$ 时的情况，如果你将空出的一列切开，变成 $3*4$ 的迷宫，这样每行每列就都有施法柱子了。

所以空出一列是现象， $f_{max}$ 的 $length_{line}$ 和 $length_{row}$ 不相等才是本质。

不难发现：每次经过施法柱子后都会涉及新的行或列，但不能步入已满的行列。

因为相邻两步的行或列有且仅有一者相同，所以相邻两步一定会把一行或一列走满。

又因为每次经过施法柱子方向改变，我们按照这些性质试着写一些可能的行走方案：

1. 转圈圈型：

$step_1$ 1 1

$step_2$ 1 3

$step_3$ 3 3

$step_4$ 3 2

$step_5$ 2 2

$step_6$ 2 4

第二步走满了列1，第三步走满了行3，第四步走满了列3......

2. 下楼梯型：

$step_1$ 1 1

$step_2$ 1 2

$step_3$ 2 2

$step_4$ 2 3

$step_5$ 3 3

$step_6$ 3 4

可以发现：第一步之后的每一步都在轮流把一列和一行走满。

又因为到达末行时就代表到达终点（光线到达末行的施法柱子就可以直接水平射入右下角），所以最后一步会把一列走满。

所以， $f_{max}$ 走满的行比列少1。

但别忘了，首行和末行各有一个施法柱子，所以有施法柱子的行比列多1。

我们把空行或空列剪掉，就会得到：

$$length_{line}=length_{row}-1$$
(走过的行就是列的长度，走过的列就是行的长度。)

同时可以根据上面的结论计算出 $step_{max}$ ：
$$step=2\cdot (length_{line}-1)+2=2\cdot length_{row}$$

所以对于一个给定的迷宫，我们需要将无法填充的空行空列剪掉。
$$∴step_{max}=2\cdot \min(m,n-1)$$
这样就求出了我们的 $step_{max}$ ，并且可以发现，形状越是狭长的迷宫，其空行空列比例会越高，空行空列不会同时出现，这也是符合我们直觉的。
***
### 代码实现
假如给你一组很小的 $n$ 与 $m$ ，你或许会非常快乐地打出下面的代码。

```cpp
read();//这里指输入而非快读。
	step++;
	for (int i=1;i<=n;i++)
		if (row[i]==1)//如果该行或列曾被标记但未被访问过，则进行访问。
		{
			for (int j=1;j<=m;j++)
				if (maze[j][i])
				{
					if (line[j]==2||
                    line[j]==-2||
                    row[i]==2||
                    row[i]==-2)//判断起点与终点是否相遇。
					{
						printf("%d",step);
						return 0;
					}
					line[j]=1;
				}
			row[i]=-1;//避免重复访问同一行或同一列。
		}
	step++;
	for (int i=1;i<=n;i++)
		if (row[i]==2)
		{
			for (int j=1;j<=m;j++)
				if (maze[j][i])
				{
					if (line[j]==1||
                    line[j]==-1||
                    row[i]==1||
                    row[i]==-1)
					{
						printf("%d",step);
						return 0;
					}
					line[j]=2;
				}
			row[i]=-2;
		}
	step++;
	for (int i=1;i<=m;i++)
		if (line[i]==1)
		{
			for (int j=1;j<=n;j++)
				if (maze[i][j])
				{
					if (row[j]==2||
                    row[j]==-2||
                    line[i]==2||
                    line[i]==-2)
					{
						printf("%d",step);
						return 0;
					}
					row[j]=1;
				}
			line[i]=-1;
		}
	step++;
	for (int i=1;i<=m;i++)
		if (line[i]==2)
		{
			for (int j=1;j<=n;j++)
				if (maze[i][j])
				{
					if (row[j]==1||
                    row[j]==-1||
                    line[i]==1||
                    line[i]==-1)
					{
						printf("%d",step);
						return 0;
					}
					row[j]=2;
				}
			line[i]=-2;
		}
	printf("%d",step);
   ......
```
但是 $(2<=N,M<=1000)$ ，所以我们需要从上面的代码中整理规律实现。

不难看出， $line/row$ 与前/后两组循环有关(也可以认为将两组循环看成一轮，与当前轮的奇偶有关)；$1/2$ 与当前循环次数的奇偶有关。

解释：

因为 $line/row$ 代表（水平/竖直）先确定可能需要转移的行/列；

$1/2$ 代表本次循环转移的时起点/终点。
***
看看上面这段代码，每组循环的 $step$ 都逐次增长，

所以上面的两种关联，我们可以用 $step\bmod2$ 和 $\dfrac{step}{2}\bmod2$ 表示。

当值为 1 为奇，为 2 为偶。

***
**But**

如果你就这样轻易地提交了代码，你可能会在 #74 或 #101 得到TLE的好成绩。

细想一下，我们解决了 $step_{max}$ ，考虑极限数据， $step_{max}$ 可以达到 1998 ，所以当我们需要判断这样规模的不可解情况时，浪费了很多时间。

我们试着举出一些 $f_{fail}$ 的例子，它们无一不是路线在中间中断。

显然，一条成功的路径不会存在断点，所以当存在一步操作没有新增转化点时，这种情况就是 $f_{fail}$ ，可以直接输出 " - 1 " 结束。

断点可能靠近中间，也可能靠近两端。

当断点在中间时，思路 1 需要走的步数最多，思路 2 需要走其一半的步数；

当断点在两端时，思路 2 需要走的步数最多或最少，思路 1 需要走的步数较少。

这是思路 1 和思路 2 在不同断点位置下效率上的区别，但是两者的最优和最坏情况，走的步数都是相同的。
***
**放代码环节：**

代码中用到了三目运算符，所以在这里也给没有了解过三目运算符的同学粗略解释一下，避免看不懂代码。

三目运算符形式如下：

```cpp
条件 ? a : b
```
意为：如果满足条件（条件式返回值非 0 ），则返回a,否则返回b。

三目运算符的优先级不高，为了保险，勤打括号。

题解解法：

```cpp
#include<cstdio>
int n,m;
char input;
bool maze[1010][1010],solve,point[1010];
short line[1010],row[1010],step;
bool read()
{
	scanf("%d%d",&n,&m);
	step_max=2*min(m,n-1);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf(" %c",&input);
			if (input=='#')
			{
				maze[j][i]=1;
				if (i==1)
					row[1]=1;
				if (i==n)
				{
					row[n]=2;
					if (maze[j][1])
						return 1;
				}
				if (!solve)
				{
					if (point[j])
						solve=1;
					else
						point[j]=1;
				}
			}
		}
	return 0;
}
int main()
{
//	freopen("text.txt","r",stdin);
//	freopen("out_mine.txt","w",stdout);
	if (read())
	{
		printf("2");
		return 0;
	}//首末行同一列都存在柱子。
	if (!solve||!(row[1]&&row[n]))
	{
		printf("-1");
		return 0;
	}//没有一列存在2个及以上的柱子，光线无法向下传播；首末行某行没有柱子，光线无法转弯。
	for (step=1;;step++)
	{
		bool ju=step/2&1,add=0;
		for (int i=1;i<=(ju?n:m);i++)
			if ((ju?row[i]:line[i])==((step&1)?1:2)) 
			{
				for (int j=1;j<=(ju?m:n);j++)
					if (maze[(ju?j:i)][(ju?i:j)])
					{
						if (row[(ju?i:j)]==((step&1)?2:1)||
                        row[(ju?i:j)]==((step&1)?-2:-1)||
                        line[(ju?j:i)]==((step&1)?2:1)||
                        line[(ju?j:i)]==((step&1)?-2:-1))
                        /*
                        这些三目运算符就是根据上文的代码压缩的部分，可以对照阅读理解。
                        */
						{
							printf("%d",step-1);
							return 0;
						}
						if (ju) line[j]=(step&1)?1:2;
						else row[j]=(step&1)?1:2;
						maze[(ju?j:i)][(ju?i:j)]=0;
						add=1;
                        /*
                        重复对line和row标记没有意义。
                        */
					}
				if (ju)
					row[i]=((step&1)?-1:-2);
				else
					line[i]=((step&1)?-1:-2);
                    /*
                    已经走过的行与列上的每一个都已打过tag，不用重复访问。
                    */
			}
		if (!add&&step!=1)
		{
			printf("-1");
			return 0;
		}
	}
	printf("-1");
//	fclose(stdin);
//	fclose(stdout);
	return 0;
} 
```


0-1BFS：

```cpp
#include<deque>
#include<cstdio>
struct Node{
	int x,y,step;
	bool way;//1水平,0竖直。
} start,in,now;
int n,m;
char input;
bool maze[1010][1010];
short meet[1010][1010];
std::deque<Node> q;
int bfs()
{
	start.x=start.y=start.way=1,start.step=0;
	q.push_back(start);
	while (!q.empty())
	{
		now=q.front(),in=now;
		q.pop_front();
		if (now.x==m+1&&now.y==n)
			return now.step;
		if (now.x<=0||now.x>m||now.y<=0||now.y>n||
        now.way==meet[now.x][now.y]-1||
        (meet[now.x][now.y]==3))
			continue;
		if (now.way!=meet[now.x][now.y]&&meet[now.x][now.y])
			meet[now.x][now.y]=3;
		else
			meet[now.x][now.y]=now.way+1;
		in.x=now.x+(now.way?1:0);
		in.y=now.y+(now.way?0:1);
		q.push_front(in);
		in.x=now.x+(now.way?-1:0);
		in.y=now.y+(now.way?0:-1);
		q.push_front(in);
		if (maze[now.x][now.y])
		{
			in.way=!now.way,in.step=now.step+1;
			in.x=now.x+(now.way?0:1);
			in.y=now.y+(now.way?1:0);
			q.push_back(in);
			in.x=now.x+(now.way?0:-1);
			in.y=now.y+(now.way?-1:0);
			q.push_back(in);
		}
	}
	return -1;
}
int main()
{
//	freopen("text.txt","r",stdin);
//	freopen("out_solu.txt","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)	
		{
			scanf(" %c",&input);
			if (input=='#')
				maze[j][i]=1;
		}
	printf("%d",bfs());
//	fclose(stdin);
//	fclose(stdout);
	return 0;
} 
```
对拍是一种校对自己程序正误的方法，即利用程序将自己的程序与朴素做法（暴力）或AC代码比较答案，确定自己程序的正确性，以及利用 clock() 函数预估程序能通过的数据范围。

顺手附上调题解代码时的 random 和 script ，方便大家对拍调错。

random：
```cpp
#include<bits/stdc++.h>
char c[2]={'.','#'};
int main()
{
//	freopen("text.txt","w",stdout);
	int n=1000,m=1000;
	srand(time(NULL));//设下随机数种子，因为时间不停向前，以此作为种子，随机数也会不停变化。
	printf("%d %d\n",n,m);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			int out=rand()%250;
			if (out)
				printf("%c",c[0]);
			else
				printf("%c",c[1]);
		}
		printf("\n");
	}
//	fclose(stdout);
	return 0;
}
```
script：
```cpp
#include<bits/stdc++.h>
int main()
{
	for (int T=1;T;T++)
	{
		system("random.exe");//运行数据生成器。
		double st=clock();
		system("mine.exe");//用自己的代码运行数据。
		double ed1=clock();
		system("solution.exe");//用正确性有保证的代码运行数据。
		double ed2=clock();
		if (system("fc out_solu.txt out_mine.txt"))//比较两份代码的输出文件，如果不同立刻结束对拍，就能保留下hack数据。
		{
			printf("Wrong Answer");
			return 0;
		}
		else
		{
			if (ed1-st>=2000)
			{
				printf("Time limit exceeded,测试点#%d:\nmine用时:%.0lfms\nsolution用时:%.0lfms\n",T,ed1-st,ed2-ed1);
				return 0;
			}//利用clock()函数特判TLE的情况。
			else 
				printf("Accepted,测试点#%d:\nmine用时:%.0lfms\nsolution用时:%.0lfms\n",T,ed1-st,ed2-ed1);
		}
	}
}
```
本文的做法和BFS的做法，区别主要在于一者从线出发，一者从点出发。

面对一个问题时，往往可以考虑不同的出发角度，寻找自己熟悉的，或是复杂度更优的解法。

于是，你就切了这道蓝题！

---

## 作者：Elegy_of_Green_Kite (赞：9)

[原题链接](https://www.luogu.com.cn/problem/CF173B)

这道题算法(BFS)难度不大，思维难度较高，是一道比较好的思维题。

当一根柱子被施了魔法，一条光线经过的时候实际效果是该行该列都会有光线。这即是说，一根柱子是否施了魔法影响的是该行该列是否有光线。

基于这一点，我们可以看作一根柱子连接了两个点——它处于的行和列，对这个柱子施魔法相当于花代价 $1$ 连通了该行和该列。

剩下来的就很好想了，将 $1$ 到 $n$ 行编号 $1 \sim n$，将 $1$ 到 $n$ 列编号 $n+1 \sim 2*n$，从 $1$ 到 $n$ 跑一遍 BFS。

代码如下
```cpp
#include<iostream>
#include<stdio.h>
using namespace std;
const int N=1e3+5,inf=0x7fffffff;
int n,m,q[N<<1],d[N<<1],mark[N<<1];
int tot,head[N<<1],Next[N*N<<2],vet[N*N<<2];
char g[N][N];
void add(int a,int b)
{
    Next[++tot]=head[a];
	vet[tot]=b;
    head[a]=tot;//邻接表存边 
}
void bfs()
{
    for(int i=1;i<=n+m;i++)  d[i]=inf;//初始化为最大值
    int le=0,ri=0;
    d[1]=0,q[++ri]=1,mark[1]=1;
    while(le<ri)//BFS
	{
        int x=q[++le];
        for(int i=head[x];i;i=Next[i])
		{
            int y=vet[i];
            if(mark[y]) continue;
            d[y]=d[x]+1;
            q[++ri]=y; mark[y]=1;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
	{
        scanf("%s",g[i]+1);//直接读入一整行字符串再处理
        for(int j=1;j<=m;j++)
            if(g[i][j]=='#')  add(i,j+n),add(j+n,i);
    }
    bfs();
    if(d[n]==inf)  printf("-1");
    else  printf("%d",d[n]);
return 0;
}
```


---

## 作者：封禁用户 (赞：4)

我们把每一行和每一列当成一个顶点，对于每个#，把他所在的行和列连一条无向边，然后从第一行到第n行跑一次bfs求最短路即可。

记得关注我的博客哦：https://www.luogu.org/blog/Noi2017/

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int dis[N*2];
char mp[N][N];
vector<int>e[N*2];
queue<int>q;
int main()
{
	int n,m,flag=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(mp[i][j]=='#')
			{
				e[i].push_back(n+j);
				e[n+j].push_back(i);
			}
		}
	}
	memset(dis,0x3f3f3f3f,sizeof(dis));
	dis[1]=0;
	q.push(1);
	while(!q.empty())
	{
		int k=q.front();
		q.pop();
		if(k==n)
		{
			printf("%d\n",dis[n]);
			flag=1;
			break;
		}
		for(int i=0;i<e[k].size();i++)
		{
			if(dis[e[k][i]]>dis[k]+1)
			{
				dis[e[k][i]]=dis[k]+1;
				q.push(e[k][i]);
			}
		}
	}
	if(!flag)
		printf("-1\n");
	return 0;
}

```

---

## 作者：闫飞天jyh (赞：3)

#  _Solution_    
  
一个 ***n * m***  的图，现在有一束激光从左上角往右边射出，每遇到 ***'#'*** ，你可以选择光线往四个方向射出，或者什么都不做，问最少需要多少个 ***'#'*** 往四个方向射出才能使光线在第 ***n*** 行往右边射出。   

一道双端队列BFS裸题 

看其他神仙用的都是最短路，这里使用一种不同的方法 ***0-1BFS*** ， 这样可以减少思考过程。

###  _做法_ 
一个方向射出不需要花费（0），而往四个方向射出需要花费（1），然后直接来就可以了。

直接贴代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

#define INF (1 << 29)

int n, m;
char grid[1001][1001];
int dist[1001][1001][4];
int fx[] = {1, -1, 0, 0};
int fy[] = {0, 0, 1, -1};

deque<int> q;

void add_front(int x, int y, int dir, int d)
{
	if (d < dist[x][y][dir])
	{
		dist[x][y][dir] = d;
		q.push_front(dir);
		q.push_front(y);
		q.push_front(x); 
	}
}

void add_back(int x, int y, int dir, int d)
{
	if (d < dist[x][y][dir])
	{
		dist[x][y][dir] = d;
		q.push_back(x);
		q.push_back(y);
		q.push_back(dir); 
	}
}//双端队列

int main()
{
	cin >> n >> m;
	for(int i = 0; i < n; i++)	cin >> grid[i];
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			for(int k = 0; k < 4; k++) dist[i][j][k] = INF;
		
	add_front(n - 1, m - 1, 3, 0);
	
	while(!q.empty())
	{
		int x = q[0], y = q[1], dir = q[2];
		q.pop_front();
		q.pop_front();
		q.pop_front();
		int d = dist[x][y][dir];
		int nx = x + fx[dir], ny = y + fy[dir];		
       if (nx >= 0 && nx < n && ny >= 0 && ny < m) add_front(nx, ny, dir, d);
       if (grid[x][y] == '#')
      for (int i = 0; i < 4; i++)
        if (i != dir) add_back(x, y, i, d + 1);
  }
  
  if (dist[0][0][3] == INF)
  
    cout << -1 << endl;
    
  else
    cout << dist[0][0][3] << endl;
    
  return 0;
}

```


---

## 作者：szhqwq (赞：3)

## $\tt{Solution}$

考虑使用 `deque` 进行 0-1 bfs。

存入 $4$ 个值，分别为当前从 $(1,1)$ 走到 $(x,y)$ 且面朝方向为 $c$ 的最少次数，$x$ 坐标，$y$ 坐标，当前面朝的方向 $c$。

每走到一个 `#`，都会有以下两种情况：

1. 无视，继续按当前面朝方向前行，次数不变，并加入队头；

2. 转换方向，次数加一，加入队尾。

**注意：第一种情况仅在不越界的情况下进行。**

[Link](https://codeforces.com/contest/173/submission/224014341)

---

## 作者：lutaoquan2012 (赞：2)

## [Chamber of Secrets](https://www.luogu.com.cn/problem/CF173B)

### 前置知识：图上 01bfs
 
## 思路

### PART $1$

这道题给出我们的是一个图。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF173B/ba6e758f7280b60525185b5ab7cbc35edd6aeb84.png)

这个图呢，它必须要有点和边，所以我们就可以看一看点和边是怎么去创造的。

#### 点：
点其实可以被我们作为每一个柱子的每一个方向，也就是每一个方向都有一个点。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kyewp3zo.png)

这样点就建完了，可是边呢？
其实每一个主子都会有一条边。

也就是从前面的任意一个光源引发出来的一条光线传到了我现在所在的这个柱子里，然后穿过，那么那个光源道我现在的柱子就是一条边

举个例子，从上图中，光源右下角怪物发射出来的一条光线，射向了最后一行的柱子，显然也就是 $:$ 怪兽的眼睛到点 $8$。这就是一条边

为了方便后面的计算，每一个点是可以怎么样来储存的呢？看到数据范围的时候很开心呀。$N,M\le1000$，显然我们就想到了以前的邻接表。其实就是换一下，每次记录现在的柱子是第几行第几列的就行了。在存一个他是哪一个方向就行了。


接着，显而易见，我们的这个图应该是有边权的，可是边权是什么呢？

如果是这个柱子要使用魔法才能传送到另一个点，比如我要从点 $5$ 传送到点 $1$ 的话，那么我就是需要边权为 $1$，因为它需要把 $2,3$ 这个点给是魔法。如果不是的话，那么边权就是 $0$。

### PART $2$

现在我们就有了一个最短路问题，当然，我一开始像的办法就是 djikstra 算法，一看数据心里凉了一截。这数据，过不了呀……

### PART $3$

我再一看，边权是 $0$ 和 $1$ 这不就是显然的 01bfs。~~真香~~。但是这个有一个问题，如果是定义一个普通的队列的话，有些时候会导致两个魔法 $1$ 的结合起来比 $0$ 更好。所以我们可以用一个双端队列，利用它可以插队的性质，把 $0$ 放前面，$1$ 放后面。

## 代码

```cpp
//
// Created by 55062 on 2023/12/7.
//
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node{
    ll x,y,d;//位值，方向
};
ll n,m,dis[1100][1100][4];
ll dx[5]={0,0,1,-1},dy[5]={1,-1,0,0};//方向数组
char a[1100][1100];
void bfs(){
    memset(dis,0x3f,sizeof(dis));
    deque<node> q;
    q.push_back({n,m,1});//先是往左边看，所以是1
    dis[n][m][1]=0;
    while(!q.empty()){
        ll x=q.front().x,y=q.front().y,d=q.front().d;
        q.pop_front();//一定是删掉前面的
        for(ll xx=dx[d]+x,yy=dy[d]+y;xx>=1&&xx<=n&&yy>=1&&yy<=m;xx+=dx[d],yy+=dy[d]){//其实相当于一个while循环
            if(a[xx][yy]=='#'){
                if(dis[xx][yy][d]>dis[x][y][d]){
                    dis[xx][yy][d]=dis[x][y][d];//更新
                    q.push_front({xx,yy,d});//进队,因为是0,就是刚才的一条直线直接传过去,没有代价,所以方向不变
                }break;//节省时间，因为后面即使有，也可以从这个更新的柱子访问到
            }
        }if(a[x][y]=='#'){//判断使用魔法
            for(int i=0;i<4;i++){
                if(i!=d&&dis[x][y][i]>dis[x][y][d]+1){//判断
                    dis[x][y][i]=dis[x][y][d]+1;
                    q.push_back({x,y,i});//因为是用了魔法，所以代价是1
                }

            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) cin>>a[i][j];
    bfs();
    ll ans=0x3f3f3f3f;
    for(int i=1;i<=m;i++) ans=min(ans,dis[1][i][1]);//有一种可能性是如果这个第一行有许多柱子的话,那么取最小值
    if(ans>=0x3f3f3f3f) cout<<-1;
    else cout<<ans;
    return 0;
}
```

---

## 作者：Peiyuan (赞：2)

## [题](https://www.luogu.com.cn/problem/CF173B)意

有一个 $n\times m$ 的矩阵，每个格子上用 `#` 代表柱子，`.` 代表空地。矩阵的右下角有一只 ~~柯爱的~~ 蛇怪，向左看并发出光线，被蛇怪看到的人就会变成石头。其中，柱子可以被施魔法，施了魔法的柱子就会把射过来的光反射到它的四个方向。求：把光线从右到左找到左上角的格子最少需要施几次魔法，误解输出 `-1`。

## 思路

把每个柱子看成上下左右四个点。同方向且在同一直线上的每两个点连一条边权为 $0$ 的边（因为光这么走是免费的，不用施魔法）。如果方向不同且在同一个柱子上，就要连一条边权为 $1$ 的有向边（因为要施魔法，花费 $1$ 代价，相当于改变方向就要施魔法）。建图见下图，以样例一为例子，红色边是免费的，蓝色边要施魔法。

![图呢？](https://cdn.luogu.com.cn/upload/image_hosting/0a15v1en.png)

图建好了，现在对这个图求最短路，也就是最终的答案。现在你肯定会想到 `dijkstra` 或 `SPFA` 算法，但是……这些太慢了，因为这个图有一个特点，就是每个点的边权要么是 $1$ 要么是 $0$，所以我们可以采用 `01BFS` 的方法，$\Theta(n)$ 复杂度求解。

其实……为了节省空间，可以干脆不建图，直接 `BFS`。具体看

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,d; //d是方向 
};
int dx[]={0,0,1,-1},dy[]={1,-1,0,0}; //四个方向，迷宫问题的老套路了.... 
int dis[1005][1005][4],n,m; //dis记录点i,j的四个方向的最短路长度 
char a[1005][1005]; //存迷宫 
void bfs(){
	memset(dis,0x3f,sizeof(dis));
	deque<node> q; //定义双端队列 
	q.push_back({n,m,1});
	dis[n][m][1]=0; //处理起点（蛇怪） 
	while(q.size()){
		int x=q.front().x,y=q.front().y,d=q.front().d;
		q.pop_front(); //取出队头
		int nx=x+dx[d],ny=y+dy[d];
		while(nx>0&&nx<=n&&ny>0&&ny<=m){ //不越界的情况下查找柱子
			if(a[nx][ny]=='#'){
				if(dis[nx][ny][d]>dis[x][y][d]){ //松弛，处理免费的边 
					dis[nx][ny][d]=dis[x][y][d];
					q.push_front({nx,ny,d});
				}
				break; //已经找到柱子了，蹦出去 
			}
			nx+=dx[d],ny+=dy[d];
		}
		if(a[x][y]=='#'){
			for(int k=0; k<4; k++){
				if(k!=d/*转弯*/&&dis[x][y][k]>dis[x][y][d]+1){ //松弛，处理收费的边 
					dis[x][y][k]=dis[x][y][d]+1;
					q.push_back({x,y,k});
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%s",(a[i]+1)); //从1开始读入 
	}
	bfs();
	int ans=0x3f3f3f3f;
	for(int i=1; i<=m; i++){
		ans=min(ans,dis[1][i][1]); //第一行所有向右看的点的距离取最大值，因为站在这些点上都能看到光 
	}
	if(ans==0x3f3f3f3f) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```

---

## 作者：emo_male_god (赞：2)

## 题外话
楼下好几人的题解与 [oi-wiki] 上同题的题解一样（**没有恶意，勿喷**）。不说啥回事，只是发现他们的代码部分有问题，包括题目翻译，虽然不影响结果，但是我还是想纠正一下。纠正请看本文最后。

----------
### 题目大意：
光线从密室的左下角 （n,m） 的位置往左边射出来，要求我们最少对几个柱子施法才能把光线射到密室门口且光线的方向为左 （1,1）。

这里我用了双向队列优化 BFS，比一般的队列应该要快上不少。[提交记录](https://www.luogu.com.cn/record/111155159)

### 解题思路：
用广搜从 n,m 开始遍历每个点，如果当前点是个空格，就依照当前方向把下一个状态 `push` 进队列里面。如果当前点是个柱子 （#） ，那么我们就讨论其他三个方向的光线，并分别 `push` 进队列。

## 定义：
$n\;m$：密室的大小

$check$：记忆化用的数组

$dx$ 数组和 $dy$ 数组：增量数组

$c$ 数组：密室

$q$：双端队列

$x\;y$：从队列中取出的坐标

$dir$：方向（数字 1、2、3、4 分别对应上下左右四个方向）
## 部分代码
**push 部分代码（如果你用了结构体，就请忽略这部分代码）**：
```cpp
//如果你用了结构体，就请忽略这个函数
void add_front(int x, int y, int dir, int cnt)
{
	//direction翻译为方向的意思
	if (cnt < check[x][y][dir])//如果当前插入的状态比之前的状态更优的话就插入，不然就拜拜
	{
		check[x][y][dir] = cnt;//更新记录数组
		//这里可以用结构图代替push三个数，这样做只是因为我在OI-wiki上看到一种骚操作（见主函数的while循环）
		q.push_front(dir);//虽然没用结构体，但是要保持提出的数据顺序得一致，我这里用的是「x坐标，y坐标，方向」的顺序
		q.push_front(y);
		q.push_front(x);
	}
}
//如果你用了结构体，就请忽略这个函数
void add_back(int x, int y, int dir, int cnt)
{
	//direction翻译为方向的意思
	if (cnt < check[x][y][dir])
	{
		check[x][y][dir] = cnt;
		//因为这里是从尾部插入的，要保持从头部取出的数的顺序一致，所以要改下push的顺序
		q.push_back(x);
		q.push_back(y);
		q.push_back(dir);
	}
}
```
**BFS部分：**
```cpp
	while (!q.empty())
	{
		int x = q[0], y = q[1], dir = q[2];//骚操作（如果会，请忽略这句话，反正我当初不会）
		q.pop_front(), q.pop_front(), q.pop_front();
		int cnt = check[x][y][dir];
		int _x = x + dx[dir], _y = y + dy[dir];
		if (_x >= 1 && _x <= n && _y >= 1 && _y <= m)//当坐标加上增量数组后依然在范围内，
		{
			add_front(_x, _y, dir, cnt);//往队列头部push当前方向
		}
		if (c[x][y] == '#')//如果当前位置有#号，讨论其他三个方向
		{
			for (int i = 1; i <= 4; i ++ )
			{
				if (i != dir) add_back(x, y, i, cnt + 1);
			}
		}
	}
```
## 最后的温馨提示：
$check$ 数组记得初始化

$q$ 队列记得先 `push` 进最初位置

输出时记得特判!



## 纠正：
题意纠正：起点是在右下，终点是左上（虽然不影响结果）

代码纠正：终点光线的方向应该向左，起点光线方向应该还是向左

[oi-wiki]:https://oi-wiki.org/graph/bfs/#%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97-bfs

---

## 作者：dctc1494 (赞：1)

题目传送门

[洛谷 Chamber of Secrets](https://www.luogu.com.cn/problem/CF173B)

### 题目理解

我们需要找到最少的柱子数量，使得从入口到密室的路径上，光线（或蛇怪的视线）能够被反射，从而阻止哈利波特进入密室。

### 初步想法

当一根柱子被施了魔法，一条光线经过的时候实际效果是该行该列都会有光线。这即是说，一根柱子是否施了魔法影响的是该行该列是否有光线。

使用 `BFS`。

### 算法思路

1. **构建图**：首先，我们将网格转换为图，其中每个单元格是一个顶点，如果两个单元格相邻（上下或左右），则它们之间有一条边。

2. **特殊顶点处理**：对于每个柱子 `#`，我们将其视为两个顶点，一个在网格的上方，一个在下方，它们之间有一条边。这样，光线在遇到柱子时可以选择反射。

3. **广度优先搜索（`BFS`）**：从入口点（左上角）开始，使用 `BFS` 搜索到出口点（右下角）。在搜索过程中，记录每个顶点的最短路径长度。

4. **判断与输出**：如果出口点的最短路径长度为无穷大（即没有可达路径），输出 $-1$；否则，输出该路径长度。

### AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;
const int M = 2e6 + 5;
const int INF = 0x3f3f3f3f;

struct Edge {
    int nxt, to;
} E[M];

int n, m, q[N], d[N];
int tot, head[N];
char g[N][N];
bool vis[N];

void add(int x, int y) {
    E[++tot] = {head[x], y};
    head[x] = tot;
}

void bfs() {
    for (int i = 1; i <= n + m; ++i) {
        d[i] = INF;
    }
    int l = 0, r = 0;
    d[1] = 0;
    q[++r] = 1;
    vis[1] = true;
    while (l < r) {
        int x = q[++l];
        for (int i = head[x]; i; i = E[i].nxt) {
            int y = E[i].to;
            if (vis[y])
                continue;
            d[y] = d[x] + 1;
            q[++r] = y;
            vis[y] = true;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> g[i][j];
            if (g[i][j] == '#') {
                add(i, j + n);
                add(j + n, i);
            }
        }
    }
    bfs();
    if (d[n] == INF) {
        cout << -1 << endl;
    } else {
        cout << d[n] << endl;
    }

    return 0;
}
```

---

## 作者：ATION001 (赞：1)

## 题目描述
有一道激光从坐标 $n,m$ 出发，经过地图上的`#`时，如果没经过处理，按原方向前进，否则转弯。

现在把地图给你，求激光最少需要转向多少次才能到达坐标 $1,0$。
## 思路
~~这题一看就是暴力搜图。~~

一提到搜图，很多童鞋都会想到 bfs 或 dfs。没错，这里介绍一下 bfs 的写法。不过跟裸的 bfs 不一样，这里是 01bfs，不会的童鞋[点这里](https://blog.csdn.net/Mr_dimple/article/details/116864052)，本题解不详细讲解。

学会了 01bfs 这题就可以写出来啦！没转向贡献为 $0$，转向贡献为 $1$，把贡献为 $0$ 的放前面，贡献为 $1$ 的放后面。

最后就是代码啦。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int first,second,third;
};
int n,m,vis[2010][2010][4],dis[1010][1010][4],xyx[5][5]={{-1,0},{1,0},{0,-1},{0,1}};
char a[1010][1010];
deque<node>q;
void bfs(int rx,int ry){
	vis[rx][ry][2]=1;
	q.push_front({rx,ry,2});
	while(q.size()){
		auto p=q.front();
		q.pop_front();
		for(int i=0;i<4;i++){
			int dx=p.first+xyx[i][0],dy=p.second+xyx[i][1],o=p.third;
			if((a[dx][dy]!='a'||dx==1&&dy==0)&&vis[dx][dy][i]!=1&&i==o){
				vis[dx][dy][i]=1,dis[dx][dy][i]=dis[p.first][p.second][o];
				if(dy){
					q.push_front({dx,dy,i});
				}
			}else if((a[dx][dy]!='a'||dx==1&&dy==0)&&vis[dx][dy][i]==-1&&a[p.first][p.second]=='#'){
				vis[dx][dy][i]=2,dis[dx][dy][i]=dis[p.first][p.second][o]+1;
				if(dy){
					q.push_back({dx,dy,i});
				}
			}
		}
	}
} 
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	fill(a[0],a[1005],'a'),fill(vis[0][0],vis[2005][2005],-1);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	bfs(n,m+1);
	cout<<(!dis[1][0][2]?-1:dis[1][0][2]);
	return 0;
} 
```
求过。

---

## 作者：2huk (赞：1)

- 给定一张 $n\times m$ 的包含 `#` 和 `.` 的图，现有一束激光从左上角往右边射出。

  每次遇到 `#`，你可以选择光线改变为上下左右四个方向之一，也可以不改变。

  求至少需要改变几次方向，可以使激光从第 $n$ 行向右射出。

- $n, m \le 10^3$。

显然总共有 $4nm$ 种状态，即在每个位置有 $4$ 种当前面对的方向。

发现转移是类似于图上的边，且边权仅有 $0$ 和 $1$。所以 01bfs 即可。

```cpp
#include <bits/stdc++.h>

const int N = 1010, M = 10000100;

int n, m;
char g[N][N];

struct Node {
	int a, b, dx, dy;
	bool operator <(const Node &h) const {
		if (a == h.a) {
			if (b == h.b) {
				if (dx == h.dx) return dy < h.dy;
				return dx < h.dx;
			}
			return b < h.b;
		}
		return a < h.a;
	}
};

std::deque<Node> q;
int dis[N][N][3][3];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i ) scanf("%s", g[i] + 1);
	
	memset(dis, 0x3f, sizeof dis);
	
	q.push_back({1, 1, 0, 1});
	dis[1][1][1][2] = 0;
	
	const std::vector<int> tx({1, 0, -1, 0}), ty({0, -1, 0, 1});
	
	while (!q.empty()) {
		int x = q.front().a, y = q.front().b, dx = q.front().dx, dy = q.front().dy;
		q.pop_front();
		if (g[x][y] == '#') {
			for (int i = 0; i < 4; ++ i ) {
				if (dis[x][y][tx[i] + 1][ty[i] + 1] > 1e9) {
					dis[x][y][tx[i] + 1][ty[i] + 1] = dis[x][y][dx + 1][dy + 1] + 1;
					q.push_back({x, y, tx[i], ty[i]});
				}
			}
		}
		if (x + dx >= 1 && x + dx <= n && y + dy >= 1 && y + dy <= m && dis[x + dx][y + dy][dx + 1][dy + 1] > 1e9) {
			dis[x + dx][y + dy][dx + 1][dy + 1] = dis[x][y][dx + 1][dy + 1];
			q.push_front({x + dx, y + dy, dx, dy});
		}
	}
	
	printf("%d\n", dis[n][m][1][2] < 1e9 ? dis[n][m][1][2] : -1);
	
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：1)

# 先说几句

图论，最短路。有点隐蔽。

# 解题思路

如果 $(i, j)$ 上有个柱子，我们可以说成：

**横边 $i$ 可以转换成纵边 $j$。边权是 $1$。**

纵边 $j$ 可以在边表的下标为 $2000+j$。

这样建成图后，结果就是 $0$ 到 $m-1$ 的最短路。

注意输入时要忽略换行。

# 奉上代码

千万不要抄，小心棕名！

```cpp
// 173B Chamber of Secrets
#include <bits/stdc++.h>
#define var long long
#define SIZE 200010
#define inf INT_MAX
#define to (a[w][k])
using namespace std;

struct Edge
{
	int v, w;
};
int dis[100010];

struct cmp		
{
    bool operator() (int a, int b)
    {
        return dis[a]>dis[b]; 
    }
}; 

void Dijkstra(vector<Edge> a[], int n, int sv)
{
	bool vis[n+5];
	fill(vis, vis+   n+5, 0);
	fill(dis, dis+100010, inf);
	
	dis[sv]=0;
	
	priority_queue<int, vector<int>, cmp> Q;
	Q.push(sv);
	while(!Q.empty())
	{
		int w=Q.top(); Q.pop();
		if(vis[w]) continue;
		vis[w]=1;
		
		for(int k=0; k<a[w].size(); k++)
		{
			if(!vis[to.v] && dis[w]+to.w<dis[to.v])
			{
				dis[to.v]=dis[w]+to.w;
				Q.push(to.v);
			}
		}
	}
}

int main()
{
	int k=0;
	int m, n; cin>>m>>n;
	vector<Edge> a[2000+n+5];
	cin.get();
	for(int i=0; i<m; i++)	
	{
		for(int j=0; j<n; j++)
		{
			char c=getchar();
			if(c=='#')
			{
				a[i].push_back({2000+j, 1});
				a[2000+j].push_back({i, 1});
			}				
		}
		cin.get();
	}
		
	Dijkstra(a, 2000+n+5, 0);
	if(dis[m-1]==inf)
		cout<<-1;
	else
		cout<<dis[m-1];

    return 0;
}

```

---

## 作者：mot1ve (赞：1)

算法很简单，就是BFS，建图很有意思。
```
//由于一个柱子影响的是一行和一列，把每一行和每一列看成一个点，依次标号
//有柱子的地方，从他的所在行的标号向所在列的标号连一条边权为1的边
//边权全是1，BFS最短路从第n行走到第1行 
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
int n,m,idx;
struct node{
	int nxt,to;
}edge[5000010];
int head[1000010],dis[1000010];
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
void bfs()//不需要vis，dis判断就行 
{
	memset(dis,INF,sizeof(dis));
	queue<int> q;
	q.push(1);
	dis[1]=0;
	while(q.size())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=edge[i].nxt)
		{
			int y=edge[i].to;
			if(dis[x]+1<dis[y])
			{
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			char ch;
			scanf(" %c",&ch);
			if(ch=='#')
			{
				add(i,n+j);
				add(n+j,i);
			}
		}
	}
	bfs();
	if(dis[n]==INF)
	cout<<"-1";
	else cout<<dis[n];
	return 0;
}
```

---

## 作者：Liuhy2996 (赞：0)

### 思路
记忆化搜索。  
$dp_{i,j,k}$ 表示第 $i$ 行第 $j$ 列要形成方向 $k$ 的光线最少的施法次数。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,dp[1005][1005][4],dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
char c[1005][1005];
bool vis[1005][1005][4];
bool chk(int x,int y,int d){
	return (x>0&&y>0&&x<=n&&y<=m&&!vis[x][y][d]);
}
inline int dfs(int x,int y,int d){
	if(vis[x][y][d]) return dp[x][y][d];
	vis[x][y][d]=1;
	if(chk(x-dx[d],y-dy[d],d)) dp[x][y][d]=min(dp[x][y][d],dfs(x-dx[d],y-dy[d],d));
	if(c[x][y]=='#'){
		int mn=1e7;
		for(int i=0;i<4;++i)
			if(i!=d){
				if(chk(x-dx[i],y-dy[i],i)) dp[x][y][i]=min(dp[x][y][i],dfs(x-dx[i],y-dy[i],i));
				mn=min(mn,dp[x][y][i]+1);
			}
		for(int i=0;i<4;++i) dp[x][y][i]=min(dp[x][y][i],mn);
	}
	return dp[x][y][d];
}
int main(){
	memset(dp,0x3f,sizeof dp);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) cin>>c[i][j];
	for(int i=1;i<=m;++i) dp[n][i][1]=0;
	int ans=dfs(1,1,1);
	if(ans<1e7) cout<<ans;
	else cout<<-1;
	return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# 题目分析

## 题意

~~题干很丑陋~~

于是自己转换了一下问题：

可以考虑成倒着跑，从 $(1, 1)$ 出发，方向向右，抵达 $(n, m+1)$。

每次遇到 `#` 可以以 $1$ 的代价更换方向。其余情况均只能以原方向前进。

求最小代价。

## 分析

考虑分层图最短路。

- 每一层只能沿一个方向移动，边权为 $0$。

- 在 `#` 处向别的层连边，边权为 $1$，表示切换方向代价为 $1$。

貌似一般的最短路算法被卡了。

我们容易发现该图中边权为 $0$ 或 $1$，考虑使用一些奇怪的技巧。

使用 [01 BFS](https://oi-wiki.org/graph/bfs/#%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97-bfs)。顺带省去了建边的步骤。

时间复杂度 $O(n)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1003

int dis[maxn][maxn][4];
string mp[maxn];

struct st
{
    int x, y, d;
    st(int X, int Y, int D):x(X), y(Y), d(D) {}
};

deque<st> q;
int dx[]={1, -1, 0, 0};
int dy[]={0, 0, 1, -1};
#define chk(i, j) ((i)&&(j)&&(i<=n)&&(j<=m))
#define mp(i, j) mp[i][j-1]

/*
   ^  
   1
<3   2>
   0
   v 
*/

void bfs(int n, int m)
{
    memset(dis, 0x3f, sizeof dis);
    q.emplace_back(1, 1, 2);
    dis[1][1][2]=0;
    while(!q.empty())
    {
        auto [x, y, p]=q.front();
        q.pop_front();
        if(!(dis[x+dx[p]][y+dy[p]][p]<=dis[x][y][p]||!chk(x+dx[p], y+dy[p])))
        {
            dis[x+dx[p]][y+dy[p]][p]=dis[x][y][p];
            q.emplace_front(x+dx[p], y+dy[p], p);
        }
        if(mp(x, y)=='#')
            for(int i=0;i<=3;i++)
            {
                if(i==p) continue;
                if(dis[x+dx[i]][y+dy[i]][i]<=dis[x][y][p]+1||!chk(x+dx[i], y+dy[i])) continue;
                dis[x+dx[i]][y+dy[i]][i]=dis[x][y][p]+1;
                q.emplace_back(x+dx[i], y+dy[i], i);
            }
    }
}

int main()
{
    int n, m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>mp[i];
    bfs(n, m+1);
    cout<<(dis[n][m+1][2]==0x3f3f3f3f?-1:dis[n][m+1][2]);
}
```

---

## 作者：BugGod (赞：0)

相信在座的诸位应该有不少都是被 OI-wiki 忽悠来的。考虑 01-bfs，显然，我们可以不耗费代价，让光线按照现在的方向前进，也可以耗费 $1$ 的代价，让光线向四个方向中的任意一个射出（在某个地方施法），那么就变成了 01-bfs 裸题。

注意光线是从右下角射出，方向为左，最后方向也为左。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
int n,m,ans,dist[1010][1010][4],dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};//dist存储当前的距离
char mapp[1010][1010];
struct node
{
    int x,y,d;//x,y是坐标，d是方向
};
deque<node>q;
void ftadd(int x,int y,int d,int step)//x,y是坐标，d是当前方向，step是当前代价
{
    if(step<dist[x][y][d])//剪枝，如果步数已经大了，就没必要再跑了
    {
        q.push_front((node){x,y,d});
        dist[x][y][d]=step;
    }
}
void bkadd(int x,int y,int d,int step)
{
    if(step<dist[x][y][d])//剪枝，同上
    {
        q.push_back((node){x,y,d});
        dist[x][y][d]=step;
    }
}
void bfs()
{
    ftadd(n,m,1,0);//这里之所以方向是1，是因为在起点时朝向左边
    while(q.size())
    {
        node k=q[0];
        q.pop_front();
        int d=k.d,xx=k.x+dx[d],yy=k.y+dy[d],dis=dist[k.x][k.y][d];
        if(xx>=1&&xx<=n&&yy>=1&&yy<=n)ftadd(xx,yy,d,dis);//可以直走不拐弯
        if(mapp[k.x][k.y]=='#')//施法
        {
            for(int l=0;l<4;l++)
            {
                if(l!=d)bkadd(k.x,k.y,l,dis+1);//剪枝，如果方向和现在的方向一样，那还不如不施法
            }
        }
    }
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)for(int k=0;k<4;k++)dist[i][j][k]=2e9;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>mapp[i][j];
        }
    }
    bfs();
    if(dist[1][1][1]==2e9)cout<<-1;//到达终点时一定是向左的，所以是dist[1][1][1]
    else cout<<dist[1][1][1];
    return 0;
}
```

---

## 作者：fuwei123 (赞：0)

本题可以用 bfs 求最短路的方式解决。

假设你是那道光。当前你站在第 $1$ 行，往右边走。当你遇到一个柱子时，就改变方向，观察到一个柱子会**改变**你行或列的状态中的**一种**，即一个柱子会使得你能到达另外一个方向。而最终你的目标就是走到第 $n$ 行。实际上从第一行不管是往右边还是往下边，都是一样的。

所以，我们可以把行坐标设为 $1$ 到 $n$，列坐标设为 $n+1$ 到 $2\times n$。当读到一个位于 ${i,j}$ 的柱子时，就把 $i$ 和 $j+n+1$ 连无向边。最终的答案就是从 $1$ 到 $n$ 的最短路。

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int>G[2005];
int dis[2005];
void bfs(int s){
	queue<int>q;
	q.push(s);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(auto v : G[u]){
			if(dis[v] > dis[u] + 1){
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
}
int n, m;
int main(){
	ios::sync_with_stdio(0);
	cin >> n >> m;
	memset(dis, 0x3f, sizeof dis);
	for(int i = 1;i <= n;i++){
		string s;
		cin >> s;
		for(int j = 0;j < s.length();j++){
			if(s[j] == '#'){
				G[i].push_back(j + n + 1);
				G[j + n + 1].push_back(i);
			}
		}
	}
	dis[1] = 0;
	bfs(1);
	if(dis[n] == 1061109567)cout << -1;
	else cout << dis[n];
	return 0;
}
```

---

