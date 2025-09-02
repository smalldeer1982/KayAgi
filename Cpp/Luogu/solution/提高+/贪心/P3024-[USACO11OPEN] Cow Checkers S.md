# [USACO11OPEN] Cow Checkers S

## 题目描述

One day, Bessie decides to challenge Farmer John to a game of 'Cow Checkers'. The game is played on an M\*N (1 <= M <= 1,000,000; 1 <= N <= 1,000,000) checkerboard that initially contains a single checker piece on the checkboard square coordinates (X, Y) (0 <= X < M; 0 <= Y < N). The bottom leftmost square of the checkerboard has

coordinates (0, 0), and the top rightmost square has coordinates (M-1, N-1). Bessie always moves first, and then the two players alternate turns.  Each turn comprises one of three types of moves:

1) Move the checker piece to any square on the same row to the left of its current position.

2) Move the checker piece to any square on the same column below its current position.

3) Move the checker piece to any spot k squares below and k squares to the left of the current square (where k is any positive integer such that this new spot is still on the checkerboard).

The first player unable to make a move (i.e., because the checker is at (0, 0)) loses. Given that Bessie always goes first, determine who will win the game if both play optimally.

Play and report the winner for T games (1 <= T <= 1,000) reading in a new X,Y starting value for each new game.

有一天，Bessie准备玩一个叫做奶牛跳棋的游戏，来挑战Farmer John。


这个游戏的棋盘大小为 M\*N (1 <= M <= 1,000,000; 1 <= N <= 1,000,000) 。最初棋盘上只有一个棋子在（x,y），棋盘的左下角坐标是（0,0），右上角的坐标是（M-1，N-1）。


每次游戏Bessie都是第一个开始，之后两个人轮流。


每次下棋的时候都有三种走法：


1.向左走任意步


2.向下走任意步


3.向左走k步然后向下走k步（k可随便取值，只要不走出棋盘）


首先走到（0,0）的人为胜利者。


游戏共有T次，每次都会给出一个新的坐标（x,y），请输出每一轮赢家的名字。


## 说明/提示

Farmer John and Bessie are playing one game on a 3\*3 checkerboard with the checker piece initially at (1, 1) (i.e. at the center of the board).


Bessie initially can only move the checker piece to either (1, 0) or (0, 1), or (0, 0). Bessie can immediately win by moving the piece to (0, 0).


起点在（1,1），一开始有三种选择（1,0）,（0,1），（0,0）只要Bessie在开始时将棋子移到（1,0）或（0,1），就必胜无疑。


感谢@ 2014nhc  提供的翻译


## 样例 #1

### 输入

```
3 3 
1 
1 1 
```

### 输出

```
Bessie 
```

# 题解

## 作者：Water_Cows (赞：24)

吐槽一句，题解里面写的都是啥啊。。。**威佐夫博弈**对于我们这些蒟蒻来说，太难了![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)。

***

$\texttt{UPDATE 2021.2.13}$ 代码添加注释，修改一些 $\LaTeX$。
$\texttt{UPDATE 2021.3.6}$ 修改一些细节。

### Part 1 找规律

在模拟赛上看到这种题，第一眼看到的就应该想到找规律。

我们首先把胜负的图画出来。注：红色表示 Farmer John 胜，蓝色表示 Bessie 胜。

[![yDckoq.png](https://s3.ax1x.com/2021/02/12/yDckoq.png)](https://imgchr.com/i/yDckoq)

感觉太少了，没关系，再来！

[![yDcZWT.png](https://s3.ax1x.com/2021/02/12/yDcZWT.png)](https://imgchr.com/i/yDcZWT)

~~感觉我的手要断了。~~

有兴趣的读者可以继续画下去，~~反正我是不画了~~。

我们把每个点的坐标写出来：

$$(0, 0), (1, 2), (2, 1), (3, 5), (4, 7), (5, 3), (6, 10), (7, 4), (8, 13), (10, 6), (13, 8)$$

我们发现，哦不，没有发现，这~~毛~~玩样有什么（~~毛个~~）规律啊？

但是有一点我们可以发现，就是红色的东西是关于 $y=x$ 这条直线对称的（说给初一及以下的同学听，就是关于正方形对角线对称的）。

好，那我们重新写一遍出来：

$$(0, 0), (1, 2), (3, 5), (4, 7), (6, 10), (8, 13)$$

还是没什么规律啊？把一个点横纵坐标做个差看看？

$$0, 1, 2, 3, 4, 5$$

！！！发现了吧，**等差数列**！！！

### Part 2 得出规律

所以可以得出规律：从 $1$ 至 $n$（横坐标的值）每次加上 $k$（$k$ 每次加 $1$），得到的值，为纵坐标的值，这个坐标则 Bessie 一定输的点。

### Part 3 发现一个 Bug

还有一个问题：怎么确定横坐标的值，毕竟横坐标并不是从 $1$ 到 $n$ 按顺序的。

考虑在同一行内，至多会有一个红格子 $B$。原因：

- 当这个格子 $A$ 在红格子 $B$ 左边时，一定可以找到从这个格子一步走到另一个红格子 $C$ 的方法，那么 Bessie 从先手变成了后手，而红格子意味着后者会赢，所以这个格子 $A$ 是先手赢。
- 当这个格子 $A$ 在红格子 $B$ 的右边时，一定可以先向左走走到红格子 $B$，那么 Bessie 从先手变成了后手，而红格子意味着后者会赢，所以这个格子 $A$ 是先手赢。

既然我们发现的这个规律，由于 $N$ 和 $M$ 在 $1$ ~ $1000000$ 之间，可以开一个一维数组，下标表示横坐标的值，数组值记录的值为对应的纵坐标的值。之后就执行以下操作：

- 当 $f_i$ 还没有对应纵坐标的值的时候，根据规律计算出 $f_i$ 的值，同时把 $f_{f_i}=i$。因为两个点是关于 $y=x$ 对称的。
- 当 $f_i$ 有对应纵坐标的值的时候，直接跳过，因为这一行已经有红色的点了。

然后就可以 $\mathcal{O(1)}$ 查询了。每次有一个起始坐标 $(x, y)$，则判断 $x$ 对应的纵坐标是否为 $y$，如果是，则 Bessie 输，否则则赢。

### Part 4 代码

```cpp
#include <iostream>
using namespace std;

const int N = 1e6 + 7;

int f[(N<<1)+1], t;
// 记得数组开两倍
// 后面 +1 就是一个习惯，毕竟数组的大小开奇数好像会快一点

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
   // 平时写题可以用用，可以增加 cin 和 cout 速度，但是不能用 scanf 和 printf 了
   // 千万注意考试别用，RE 抱蛋两行泪

	for(int k=0, i=1; i<=(int)1e6; i++)
		if(!f[i]) f[i] = i + (++k), f[f[i]] = i;
		
	cin >> t >> t >> t;
   // 读 3 个 t 就是因为 n 和 m 没用，节省变量，反正会覆盖的
	for(int i=1; i<=t; i++) {
		int x, y;
		cin >> x >> y;
		if(f[x] == y) cout << "Farmer John\n";
		else cout << "Bessie\n";
	}
}
```

泥们是不是要~~感谢~~一下我这个良心题解，没有泥们看不懂的东西，要公式去别的题解看就好了，~~求赞![/kel](https://cdn.luogu.com.cn/upload/pic/62226.png)~~。

---

## 作者：xiwang (赞：4)

发现把一个点(x,y)当成一堆石子有x个，另一堆有y个,发现3种操作分别对应从第1堆拿任意个石子，从第2堆拿任意个石子,从2堆中同时拿任意个石子...于是这就是个威佐夫博弈。

Betty定理：

记k=floor((b-a)\*((1.0+sqrt(5.0))/2.0))]；

若k==x，则先手必败，否则先手必胜。

code：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m;
const char ass[2][32]={"Farmer John","Bessie"};
int sb(int a,int b){
    if(a>b)swap(a,b);
    int k=floor((b-a)*((1.0+sqrt(5.0))/2.0));
    return k!=a?1:0;
}
int main(){
    scanf("%d%d",&m,&n);
    int t;
    scanf("%d",&t);
    while(t--){
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%s\n",ass[sb(a,b)]);
    }
    return 0;
}
```

---

## 作者：ycy1124 (赞：4)

### 题意
有一个 $n \times m$ 现在 Bessie 与 Farmer John 在这上面轮流移动。游戏共有 $t$ 局，每局都由 Bessie 先手。初始时棋子在点 $(x,y)$ 上，每次可以将其向下移动任意格，向左移动任意格，或者同时向下与向左移动 $k$ 格。谁先移动到 $(0,0)$ 谁就胜利，要求输出每局的赢家。
### 思路
很容易想到博弈论。我们发现，点 $(0,0)$ 是 Bessie 的必败点，因为先手无法行动。那么对应的，如果点的 $x=0$，$y=0$ 或者 $x=y$ 都是必胜点，因为他们可以直接走到必败点，对方就输了。此时我们考虑接下来先手必败的点，此时由于 $x=0,y=0$ 的点都不行，那么下一个一定是 $x=1$ 或者 $y=1$ 且 $x=y\pm1$ 的点。不难发现两个点分别为 $(1,2)$ 和 $(2,1)$。到这里又可以发现一个性质，这些点都是对称的，即 $(x,y)$ 与 $(y,x)$ 的胜负性一样。接下来同理，所有 $x=y\pm 1$ 的点或者同行同列有必败点的点都是必胜点。找到第 $k$ 对必败点是 $x=y\pm (k-1)$ 并且 $x$ 最小且同行没有必败点的点。到这里，代码就很好写了。
### 实现方法
用一个 $vis_i$ 表示这一行有没有必败点，$w_i$ 表示这一行必败点的 $y$ 坐标，$js$ 累加表示第几组必败点了。枚举 $i$ 从 $1$ 到 $n$，每次如果这一行没有必败点就 将 $vis_{i}$ 与 $vis_{i+js}$ 标记并将 $w_i=i+js$ 与 $w_{i+js}=i$。每次询问 $\mathcal{O}( 1 )$ 判断即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int w[1000005];
bool vis[1000005];
signed main(){
    int n,m,t;
    cin>>n>>m>>t;
    int js=0;
    for(int i=0;i<=max(n,m);i++){
        if(!vis[i]){
            w[i]=i+js;
            if(i+js<=n)
                w[i+js]=i;
            vis[i]=1;
            if(i+js<=n)
                vis[i+js]=1;
            ++js;
        }
    }
    while(t--){
        int x,y;
        cin>>x>>y;
        if(y!=w[x]){
            cout<<"Bessie"<<'\n';
        }
        else{
            cout<<"Farmer John"<<'\n';
        }
    }
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/195510831)

---

## 作者：_Rainlzy (赞：2)

[前置芝士：博弈论](https://oi-wiki.org/math/game-theory/)

其实这道题只不过是一道[威佐夫博弈题](https://baike.baidu.com/item/%E5%A8%81%E4%BD%90%E5%A4%AB%E5%8D%9A%E5%BC%88/19858256)。

我们只要把横轴看成一堆石子，竖轴也看成一堆石子。三种操作分别是从第 $1$ 堆中拿若干个石子，从第 $2$ 堆中拿若干个石子，同时从第 $1$ 堆和第 $2$ 堆中拿若干个石子。

简化版就是两堆石子 $(a,b)$，第一种操作变为 $(a+x,b)$，第二种变为 $(a,b+x)$，第三种变为 $(a+x,b+x)$。

经过通项公式可得出结论，当 $\frac{\sqrt5+1}{2} \times (b-a) = a$ 时，就是先手必败的情景。反之不等于 $a$ 时就是先手必胜。

```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int main(){
    int n=read(),m=read();
    int T=read();
    for(int i=1;i<=T;i++){
        int x=read(),y=read();
        if(x>y)
            swap(x,y);
        double ans=(sqrt(5.0)+1)*0.5*(y-x);
        if(x==(int)ans)
            cout<<"Farmer John\n";
        else
            cout<<"Bessie\n";
    }
    return 0;
}
```

如果你把先手必败场面所有的 $a$ 排序后，你会发现所有 $a$ 中都没有重复的。

---

## 作者：yaoyuchen2021 (赞：1)

# 前言
本蒟蒻太菜了，不会威佐夫博弈也不会理性证明打表的正确性，但是看了一圈发现打表的题解都一点没解释为啥对，所以写一篇感性证明，供大家踩踏 ~~（~~。

# 题目大意
有一个 $n \times m$ 的棋盘，Bessie 与 Farmer John （以下简称 B 和 F ）轮流按一些规则移动一枚棋子，走到 $(0,0)$ 的人胜利，对于每个给定的棋子，输出赢家。

规则：每次只能向左，向下，或沿正方形对角线向左下移动。

# 解题思路
看看数据范围，$n \le 10^6$，比较大，再结合题目背景，容易想到这是一道博弈论。看了一下其他题解，果然是一个叫什么威佐夫博弈的东西。但是本蒟蒻不会那么高深的东西，而众所周知一些博弈论是可以找规律过的，于是，我就踏上了我的打表之路。

#### 打表小技巧：

1. 从左下开始画。
2. 点 $(0,0)$ F 赢。
3. 能一步到达 F 赢的点的位置 B 赢。（可以想象为在原步骤中加了这么一步，原来的第一步变成了第二步，那么原来 F 走的最后一步就变成 B 走的了）
4. 如果则么走都**无法**再一部内到达 F 赢得点，F 赢。（同理可得）

经过一小时的打表，我~什么也没看出来~发现：

1. 两者的输赢关系关于直线 $y=x$ 对称。
2. 每行，每列，每条向左下的的斜线有且仅有一个 F 赢的点。
3. 取其中一边 F 赢的点，按横坐标排序，纵坐标与横坐标的差依次加一。

下面分别给出证明：

1. 很好理解，把棋盘延 $y=x$ 翻转即可。
2. 设一个 F 点坐标为 $(x,y)$，则 $(x,y+k),(x+k,y),(x+k,y+k)$ 都能在一步内到达 $(x,y)$，参考打表小技巧 $3$，故最多有一个这样的点。在每行内，不断向右拓展，肯定有一个点满足小技巧 $3$ 的条件，故至少有一个点，每列同理。
3. 设一个点坐标为 $(x,y)$，根据第二条，$(x+k,y+k)$ 上不会含其他点，但每一行至少有一个这样的点，所以格子会至少向右移一格（这里举的是在斜线右下方的例子），然后我们发现如果相邻实际上只要向右移一格就满足条件了（应为是从左到右画的），所以如果这个相邻的格子出现在一边，那么他的位置因该行为 $(x+k+1,y+k)$，表现出来就是纵坐标与横坐标的差一次加一。

# AC Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
int T,x,y,f[2000005];
signed main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>x>>y>>T;
	for(int i=1,j=0;i<=1e6;i++)//预处理
	{
		if(f[i])continue;
		j++;f[i]=i+j;f[i+j]=i;//同时处理两侧，j表示横纵坐标差
	}
	while(T--)//O(1)处理询问
	{
		cin>>x>>y;
		if(f[x]==y)cout<<"Farmer John\n";
		else cout<<"Bessie\n";
	}
	return 0;
}
```

---

## 作者：corner_xiejunqi (赞：1)

### 题目分析：
由题意可将在棋盘中的坐标 $(x,y)$，看作一堆有 $x$ 个石子的石堆，和一堆有 $y$ 个石子的石堆。
#### 1.向左走任意步：
可以看作将第一堆石子拿出任意个石子。
#### 2.向下走任意步：
可以看作将第二堆石子拿走任意个石子。
#### 3.向左走 $k$ 步然后向下走 $k$ 步（ $k$ 可随便取值，只要不走出棋盘）。
可以看作第一二堆同时拿走任意个石子。
#### 所以这就是经典的个威佐夫博弈。
更据 Betty 定理：经过通项公式可得出结论，当 $\frac{\sqrt{5}+1}{2}\times(y-x)=x(x\le y)$ 时，先手必败，也就是 Bessie 必败，反之则 Farmer John 必败。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,t;
signed main(){
	// step 1、读题、声明变量
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	// step 2、输入
	cin>>n>>m>>t;
	// step 3、处理
	while(t--){
        int x,y;
		cin>>x>>y;
		if(x>y) swap(x,y);//维护x比y小 
		double res=(sqrt(5.0)+1.0)*0.5*(y-x);//0.618黄金分割比,Betty定理 
		if((int)res==x) cout<<"Farmer John\n";//Farmer John必胜 
		else cout<<"Bessie\n";//Bessie必胜，Bessie为先手 
	}
	// step 4、输出
	return 0;
}
```

---

## 作者：_Haoomff_ (赞：1)

本篇题解将介绍两种方法。

前置知识：[威佐夫博弈](https://baike.baidu.com/item/%E5%A8%81%E4%BD%90%E5%A4%AB%E5%8D%9A%E5%BC%88/19858256?fr=ge_ala)。
### 第一种
把横轴看做一堆石子，把竖轴也看做一堆石子。两堆石子，我们分别用 $a$ 和 $b$ 表示，那么就是 $(a,b)$。现在，对于三种操作，就转化成了：
1. $(a+k,b)$；
2. $(a,b+k)$；
3. $(a+k,b+k)$。

通过前置知识，可得：当 $\frac{\sqrt{5}+1}{2}\times(b-a)=a$ 时，先手必败；否则先手必胜。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
inline void swap(int &a,int &b){
	int t=a;
	a=b;b=t;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>t;
	for(int x,y;t--;){
		double res;
		cin>>x>>y;
		if(x>y)swap(x,y);
		res=(sqrt(5.0)+1.0)*0.5*(y-x);//除以2相当于乘0.5 
		if((int)res==x)cout<<"Farmer John\n";
		else cout<<"Bessie\n";
	}
	return 0;
}
```
这种方法成功地抢到了[最优解](https://www.luogu.com.cn/record/list?pid=P3024&orderBy=1&status=&page=1)。
### 第二种
在赛场上遇到这种题目，如果没有头绪，那么可以画画图、找找规律。

威佐夫博弈是颇为复杂的。我们用 $(a_k,b_k)(a_k\le b_k,k=0,1,2,…,n)$ 表示两堆物品的数量并称其为局势，如果甲面对 $(0,0)$，那么甲已经输了，这种局势我们称为奇异局势。（摘自百度百科，稍作改动）

百度百科还非常贴心地给出了几组奇异局势：$(0,0),(1,2),(3,5),(4,7),(6,10),(8,13),(9,15),(11,18),(12,20)$。

可以发现，前后作差分别为：$0,1,2,3,4,5,6,7,8$。没错，就是等差数列！

代码就不放了，可以去[这篇](https://www.luogu.com.cn/blog/yufan/solution-p3024)看看。

---

## 作者：yz0414 (赞：1)

思路和前一位大佬是一样的。

若trunc(abs(y-x)*(sqrt(5)+1)/2)=x

则先手必败，否则先手必胜。

为P党服务一下，附上代码：

```pascal
var n,m,t,x,y,i:longint; tmp:real;
begin
   readln(n,m);
   readln(t);
   for i:=1 to t do
     begin
        readln(x,y);
        if trunc(abs(y-x)*(sqrt(5)+1)/2)=x
         then writeln('Farmer John')
          else writeln('Bessie');
     end;
end.
```


---

