# [AGC007A] Shik and Stone

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc007/tasks/agc007_a

縦 $ H $ 行、横 $ W $ 列のマス目に区切られた盤面があります。 はじめ、駒が左上隅のマスに置かれていました。 シックはこの駒を $ 1 $ マスずつ上下左右に動かし、右下隅のマスに移動させました。 このとき、駒が同じマスを複数回通った可能性もあります（左上隅や右下隅のマスも含む）。

縦横に並んだ文字 $ a_{ij} $ ($ 1\ \leq\ i\ \leq\ H $, $ 1\ \leq\ j\ \leq\ W $) が与えられます。 $ a_{ij} $ が `#` のとき、駒が移動する過程で $ i $ 行 $ j $ 列目のマスを一度以上通ったことを表します（左上隅や右下隅のマスは必ず通ったものとして扱います）。 $ a_{ij} $ が `.` のとき、駒が $ i $ 行 $ j $ 列目のマスを一度も通らなかったことを表します。 移動する過程で、駒が常に右または下に動いていた可能性があるか判定してください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 8 $
- $ a_{i,j} $ は `#` または `.` である。
- 問題文および $ a $ で与えられる情報と整合するような駒の動き方が存在する。

### Sample Explanation 1

右、下、右、下、右、下、右と駒が動くと、通るマスが与えられた情報と合致します。

## 样例 #1

### 输入

```
4 5
##...
.##..
..##.
...##```

### 输出

```
Possible```

## 样例 #2

### 输入

```
5 3
###
..#
###
#..
###```

### 输出

```
Impossible```

## 样例 #3

### 输入

```
4 5
##...
.###.
.###.
...##```

### 输出

```
Impossible```

# 题解

## 作者：Yu_343 (赞：8)

我A掉此题之后翻了翻别人的题解．

我的天！搜索是什么神仙算法！

接下来是我的算法：

一只马**从左上角只向下或只向右走到右下角**，等价于**从第 $i$ 行到第 $i+1$ 行可能存在仅一种移动方式 且 从第 $j$ 列到第 $j+1$ 列可能存在仅一种移动方式**，即**移动了 $(h-1)+(w-1)$ 即 $h+w-2$ 次**．

反映到输入数据上，就是 **`#` 的个数等于 $h+w-1$**．

但是如果是这么一组数据怎么办？

```
4 5
#####
....#
...##
.....
```

它也符合 `#` 的个数等于 $h+w-1$，这种情况岂不是只有大法师能解决？~~（这句话好像不太对？dalao勿喷~~

别着急，题目中有这么一句话：

> 問題文および $a$ で与えられる情報と整合するような駒の動き方が存在する。

~~其实我也不大清楚什么意思，大概~~就是说输入数据保证合法，即一定是从左上角移动到右下角．

所以用我的想法可以快速水过此题！时间仅需 `9ms`！

```cpp
/*
https://www.luogu.org/problem/AT2168
Author: Yu-343
*/

#include <cstdio>

int main (void) {
	int h, w;
	scanf ("%d %d", &h, &w);
    int cnt = 0;
	for (int i = 1; i <= h; ++i) {
		getchar ();
		for (int j = 1; j <= w; ++j) {
			char ch = getchar ();
			if (ch == '#') ++cnt;
		}
	}
	puts ((cnt == h + w - 1) ? "Possible" : "Impossible");
	return 0;
}
```

其实这个想法极其简单~~但是好像dalao不屑去用！？~~，以上的很多都是无关紧要的废话，还请dalao多多包涵．

另外我翻了翻提交记录，发现[有和我一个方法的dalao代码](https://www.luogu.org/record/11433868)（只用了 `1ms`，绝对的最优解），
可能还不止一个相似算法代码，我在此只是说明并不是我第一个想出了这个算法．

谢谢大家！

~~蒟蒻的第一篇题解qwq，管理员审核第二遍辛苦了．~~

---

## 作者：zjyqwq (赞：3)

### AT2168 [AGC007A] Shik and Stone题解
pascal。


------------
#### 解题思路
第一眼：这不就爆搜？

突然发现，一个点可以走无数遍，我谔谔，爆搜的想法顿时消失。

根据数学思路推断，路径长度为 $H+W-1$ 。证明：

|# | # | . |
| :----------: | :----------: | :----------: |
| . |#  |  .|
| . |#  | # |
这是一个随便举的例子。很显然，他可以到达。

现在，我们把他变一下：

| #| . | . |
| :----------: | :----------: | :----------: |
| #| . | . |
| #|# |# |

井号个数不变，但是我们可以算一下，表中有一整列是满的，有一整行是满的，但是有一个井号重复了。所以路径长度为 $H+W-1$ 。

但是，我们马上可以举出一个反例：

| .|  #| . |
| :----------: | :----------: | :----------: |
| # |#  |#  |
|  .|  #| . |

通过整理，我们也可以得出结果：


| #| . | . |
| :----------: | :----------: | :----------: |
| #| . | . |
| #|# |# |

但是，这个表显然不能到达。

这种情况，又让我想起了爆搜……

可是爆搜做不了……

~~这什么毒瘤题我不做了！！！~~

我只好打开了题解。发现大佬 @Yu_343 的题解：

说输入数据保证合法，即一定是从左上角移动到右下角。

这就可以求出井号的数量，如果不等于 $H+W-1$ ，则输出 $Impossible$ ,否则输出 $Possible$ 。


------------
#### 代码
```pascal
var
n,m,i,j,s:longint;
x:char;//定义
 begin
  readln(n,m);//输入
  for i:=1 to n do
   begin
    for j:=1 to m do
     begin
      read(x);
      if x='#'then inc(s);//累加#号的数量
     end;
    readln;//注意！！！输入要换行
   end;
  if s=n+m-1 then writeln('Possible')
  else writeln('Impossible');//输出
 end.
```

---

## 作者：wimg6_ (赞：0)

## AT2168 题解

**算法一**

$2$ 秒钟，且 $2\leq H,W\leq 8$。

暴力推都能推过。

四联通问题，且马只能向右走或者向下走。

对于深度优先搜索算法而言，从 $(1,1)$ 开始搜，如果能走到头就返回。

对于广度优先搜索，也是从 $(1,1)$ 开始搜，注意只把对于当前点右边和下边的两个点加入队列即可，这一个细节不要弄混，否则会出错。

**算法二**

更快的算法？

从 $(1,1)$ 走到 $(H,W)$，对于行来说需要走 $H-1$ 格，对于列来说要走 $W-1$ 格，即总共要走 $H-1+W-1$ 格，注意起点被算了两次，所以要加上 $1$，总共走 $H+W-1$ 格。

即：若当前地图上 `#` 数量为 $H-W+1$，则输出 `Possible`，否则输出 `Impossible`。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int h,w,s;
int main()
{
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
		{
			char c;
			cin>>c;
			if(c=='#') s++;
		}
	if(s==h+w-1) return !printf("Possible\n");
	else return !printf("Impossible\n");
}
```


---

## 作者：Daniel_yao (赞：0)

## 题目大意
有一个纵 $H$ 行，横 $W$ 列的格子状棋盘。开始时，棋盘左上角的格子有一个马（不是象棋意义的马）。Shik 将会操纵它上下左右移动，从而到达右下角的格子。此时，马能够经过同一个格子多次（含左上角和右下角的格子）。

给出 $H$ 行字符串，如果第 $i$ 行第 $j$ 列的字符为 ' # ' ，则表示马在移动过程中至少通过了此格一次（左上角和右下角的格子一定会通过至少一次）。当 $a_{i,j}$
  为 ' . ' 时，表示马在移动过程中并没有经过此格。

请判断：马是否可能每次移动都向下或向右。

### 解题思路
 通过推样例，不难发现，‘ # ’的个数为 $H + W - 1$ 。意思就是说，矩阵合法移动顺序为：右，下，右，下，右，下，右. . . 依次往下推。最后就会发现，矩阵非无终点和起点。一定是 **严格** 从左上角移动到右下角。
 
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int H, W, num;
string s;
int main(){
	cin >> H >> W;
	int cnt = H + W - 1;
	int num = H * W;
	for(int i = 1;i <= H;i++){	
		cin >> s;
		for(int j = 0;j <= s.size();j++){
			if(s[j] == '.'){
				num--;
			}
		}
	}
	if(num == cnt){
		cout << "Possible"; 
	}
	else{
		cout << "Impossible";
	}
	while(1);//杜绝抄袭 
	return 0;
}
```
注：部分思路可能与大佬 Yu_343 的思路有些相似，但大部分还是我自己想出来的。这里，先给大家声明一下，有任何疑问，可以来私信我哟！！

---

## 作者：零殇 (赞：0)

#### 题意

有一匹马在$1,1$的位置，只能向下或向右走，问能否到底右下角且经过所以$'#'$字格。

#### 思路

首先，我们把$'#'$的个数记录下来，便于后面判断。

```
for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)
		{
			cin>>ch[i][j];
			if(ch[i][j]=='#')
				sum++;//记录
		}
```

然后搜索（$dfs$和$bfs$都行啦），判断是否可以通过只向下和向右到达右下角。

我们可以得到两种情况。

#### 第一种：无法到达

如果压根就无法到达，那么其他什么都没有意义了，直接$Impossible$。

因为可以经过搜索判断，就不说明了。

#### 第二种：能到达，但无法经过全部$'#'$

由于要经过所有路而不能回头，所以可以得到路径必定唯一。因此，我们可以记录到达终点后所经过的$'#'$个数，在和我们之前的$sum$比较。如果不相等，那么就说明无法全部经过，反之，则改图满足我们的要求。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int H,W;
char ch[10][10];
int x[5]={0,0,1};
int y[5]={0,1,0};
int k[10][10],ans[10][10],sum;
void bfs()
{
	int head=0,tail=1,h[3][1000];
	h[1][1]=1;
	h[2][1]=1;
	ans[1][1]=1;
	while(head<tail)
	{
		head++;
		k[h[1][head]][h[2][head]]=1;
		for(int i=1;i<=2;i++)
		{
			tail++;
			h[1][tail]=h[1][head]+x[i];
			h[2][tail]=h[2][head]+y[i]; 
			if(k[h[1][tail]][h[2][tail]]==1||ch[h[1][tail]][h[2][tail]]=='.'||h[1][tail]>H||h[2][tail]>W)
				tail--;
			else
			{
				ans[h[1][tail]][h[2][tail]]=ans[h[1][head]][h[2][head]]+1;
				k[h[1][tail]][h[2][tail]]=1;
			}
		}
		if(h[1][head]==H&&h[2][head]==W)
		{
			if(ans[h[1][head]][h[2][head]]==sum)
			{
				cout<<"Possible"<<endl;
				return;
			}
		}
	}
	cout<<"Impossible"<<endl;
}
int main()
{
	scanf("%d%d",&H,&W);
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)
		{
			cin>>ch[i][j];
			if(ch[i][j]=='#')
				sum++;
		}
	bfs();
	return 0;
}
```

完结撒花~

---

## 作者：智子·起源 (赞：0)

## bfs详细题解

### 1、思路：

这道题，显然是用搜索方便些。

只要我们把合法的路线搜出来，再看一下还有没有没有走过的“#”就可以了。

每一次搜索，我们存在两种走路方法：向右走 or 向左走。

啊，这么简单的二项搜！！qwq

于是我就开始噼里啪啦敲代码了。。。


第一次，我敲出来的代码是这样的：

```cpp
#include<iostream>
using namespace std;
int n,m,dx[2]={0,1},dy[2]={1,0};char a[9][9];
struct data{int x,y;}que[1000];
void bfs()
{
  int h=0,t=1,xx,yy;
  que[0].x=que[0].y=1,a[1][1]='.';
  while(h!=t)
  {
    for(int i=0;i<2;i++)
    {
      xx=que[h].x+dx[i];
      yy=que[h].y+dy[i];
      if(xx<1||yy<1||xx>n||yy>m||a[xx][yy]=='.')continue;
      que[t].x=xx,que[t].y=yy,t++,a[xx][yy]='.';
    }
    h++;
  }
}
int main()
{
  cin>>n>>m;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
      cin>>a[i][j];
  bfs();
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
      if(a[i][j]=='#'){cout<<"Impossible"<<endl;return 0;}
  cout<<"Possible"<<endl;
  return 0;
}

```
### 2、易错点

但是，我错了第三个样例。

怎么回事？

我们结合一下样例：

4 5

| # | # | . | . | . |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| . | # | # | # | . |
| . | # | # | # | . |
| . | . | . | # | # |

这时候，我们发现有两种走法是可行的：

1、

| → | ┓ | . | . | . |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| . | ┗ | → | ┓ | . |
| . | # | # | ↓ | . |
| . | . | . | ┗ | ⊙ |

2、

| → | ┓ | . | . | . |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| . | ↓ | # | # | . |
| . | ┗ |→ | ┓ | . |
| . | . | . | ┗ | ⊙ |

而我这样的写法把两条路同时搜出来了QAQ

但是如果一条路直接走到终点，必定不能走完另一条路，故“Impossible”。

### 那我们就要改一下搜索的结构了。

### 不是二项搜，而是 **“选择式单项搜”。** （我自创的=。=）

### 在搜索过程中我们只要找到一个可走方案，就直接走，而抛弃另一种方案。这样才能真正模拟出马走的路线。

那有人会问：那如果当前路线走不通，而另一条路线可以但你抛弃它导致结果有误怎么办？

我的回答是：没有这种结果。因为如果有两条分歧，一条达不到终点，那么就肯定输出“Impossible”。因为这也是马要走的路，而马如果走了，就不能后退，绝对不能符合要求。

那该怎么该程序呢？TAT

很简单，加个“break；”就可以啦！

大家看一下AC代码：

```cpp
#include<iostream>
using namespace std;
int n,m,dx[2]={0,1},dy[2]={1,0};char a[9][9];
struct data{int x,y;}que[1000];
void bfs()
{
  int h=0,t=1,xx,yy;
  que[0].x=que[0].y=1,a[1][1]='.';
  while(h!=t)
  {
    for(int i=0;i<2;i++)
    {
      xx=que[h].x+dx[i];
      yy=que[h].y+dy[i];
      if(xx<1||yy<1||xx>n||yy>m||a[xx][yy]=='.')continue;
      que[t].x=xx,que[t].y=yy,t++,a[xx][yy]='.';
      break;//新加的break，也就是说，如果有一种满足情况就立刻退出。
    }
    h++;
  }
}
int main()
{
  cin>>n>>m;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
      cin>>a[i][j];
  bfs();
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
      if(a[i][j]=='#'){cout<<"Impossible"<<endl;return 0;}
  cout<<"Possible"<<endl;
  return 0;
}

```

### 完结撒花。（~▽~）

虽然方法有可能重复，但写法和思路解释是目前最优的。为了能让更多人更好的理解学会解答本题，更好的学会灵活运用bfs，请管理员过一下，谢谢！^_^

---

## 作者：lzxhdxx (赞：0)

# AT2168 bfs
看到之前有大佬写了dfs、模拟题解，甚至有巨佬写了数学题解，就是没人写bfs题解，所以我就来写一写bfs题解吧！

### 题意：
输入一张n*m的图，判断是否能从左上角走到右下角（必须经过所有'#'）

### 做法：
看到题目，我一下就想到了搜索，我们只要从左上角开始搜索，如果能到左下角而且经过了所有的'#'就可以了！

但是，如果直接这样写，一定会WA，因为直接搜索扩展出去的不止一条路径，相当于走了回头路，但是题目中说“**马是否可能每次移动都向下或向右**”，所以我们不应该考虑向左/向上走，而向下走时走回头路就成了向上走，不行；向右走时走回头路同理，也不行。

所以我们就可以得到搜索策略：搜到某个点后如果得到两个可以扩展的点（即不止一条路径）就直接返回，输出不可能。如果一直搜完了，返回后就检查一下是否有没有走过的点，都走过就输出可能

Code：
```cpp
#include <iostream>
#include <queue>

using namespace std;

int n, m, dx[5] = { 0,1,0 }, dy[5] = { 0,0,1 };
char c[10][10];
bool vis[10][10] = { false };//vis记录有没有走过，根据前面分析的不能走回头路的特性可知每个点至多走一次

void bfs()//广搜
{
	queue<pair<int, int> >Q;//存点的队列
	Q.push(make_pair(1, 1));//压入起点
	vis[1][1] = true, c[1][1] = '.';//把起点标记为走过，修改为'.'便于最后检查是否有没走过的'#'
	while (!Q.empty())//循环直到队列空
	{
		int nowx = Q.front().first, nowy = Q.front().second, tmp = 0;//取出队头，tmp用于记录扩展了几条路径
		for (int i = 1; i <= 2; i++)
		{
			int newx = nowx + dx[i], newy = nowy + dy[i];//扩展点
			if (newx >= 1 && newy >= 1 && newx <= n && newy <= m && !vis[newx][newy]/* && c[newx][newy] == '#'*/)//如果符合条件就尝试一下
			{
				tmp++;//路径+1
				Q.push(make_pair(newx, newy));//压入新点
				vis[newx][newy] = true, c[newx][newy] = '.';//标记为走过，修改为'.'
			}
			if (tmp == 2) return;//如果拓展出了两条路径就直接返回
		}
		Q.pop();//弹队列
	}
}

int main()
{
	ios::sync_with_stdio(false);//加快cin,cout
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)//输入
			cin >> c[i][j];
	bfs();//广搜
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)//检查是否有没走过的'#'
			if (c[i][j] == '#')
				return cout << "Impossible" << endl, 0;//如果有没走过的点直接输出不可能，然后return 0;
	cout << "Possible" << endl;//不是不可能就是可能
	return 0;
}
```
悄悄告诉你们，我把代码里的一处小地方注释掉了，大家看懂~~再抄~~自己打一边哟

新版bfs题解，求管理大大给过

---

## 作者：七夜 (赞：0)

看到另一位大佬用的搜索，身为蒟蒻的我，只能水过此题

首先根据题意得知，只能向下或者向右，也就是说不能向左或者向上

那么如果一个点既有向右的也有向下的，那么无论如何也只能到达一个点，没错吧

还有就是，如果一个点上面和左面都没有，那么就无法到达（0,0除外)所以只需要判断上面或者左面有#，然后下面和右面保证只有一个就行了

~~于是就产生了本蒟蒻的代码（附带注释）~~

```
#include<bits/stdc++.h>//偷懒专用库 
#define MAXN 99999
#define INF 101//两个宏定义 
using namespace std;
inline int read(){
 char c=getchar();int x=0,f=1;
 while(c>'9'||c<'0'){if(c!='-')f=-1;c=getchar();}
 while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
 return x*f;
}//快读，想学习的可以借鉴 
char s[INF][INF];//用来存字符 
int n,m,tot,pop;//n代表行，m代表列，tot和pop用来判断 
int main()
{
    n=read();
    m=read();//读入行和列 
    for(int i=1;i<=n;++i)
     for(int j=1;j<=m;++j)
      cin>>s[i][j];//读入字符 
    s[0][1]=s[1][0]='#';//很关键，如果不写，输出结果全部都是Impossible 
    for(int i=1;i<=n;++i)
     for(int j=1;j<=m;++j)
      {
      	tot=0;
      	pop=0;//初始化 
      	if(s[i][j]=='#')
      	 {
      	 	if(s[i][j+1]=='#')
      	 	 tot++;
      	 	if(s[i+1][j]=='#')
      	 	 tot++;//判断下面和右面有一个还是两个，按照题意，两个位置只能存在一个 
      	 	if(s[i-1][j]!='#')
      	 	 pop++;
      	 	if(s[i][j-1]!='#')
      	 	 pop++;//这个是判断上面或者左边有没有，也就是确定有没有方法能到达 
         }
        if(tot==2||pop==2)
         {
         	cout<<"Impossible\n";
         	return 0;//只要不满足其中一种，就输出不可能，然后直接结束 
         }
      }
    cout<<"Possible\n";//否则输出可能 
    return 0;//别忘了打return 0 
}
```


---

## 作者：N0othing (赞：0)

这道题本蒟蒻使用的是搜索。各位dalao如果有更好的做法可以回复我。

这道题的思路是用深搜，在函数里传两个参数，表示当前点的坐标。然后看看能否向右或下走。于是，代码就写出来了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10][10],m,n,flag;//a数组表示能不能选
char kk[10];//这个数组用来输入
void dfs(int x,int y){
    if(x==m-1&&y==n-1){//如果能走到最后一格
        flag=1;//标记
        return;//返回
    }
    if(flag==1)return;//加快，优化
    if(a[x+1][y])dfs(x+1,y);//向下走
    if(a[x][y+1])dfs(x,y+1);//向右走
    if(!a[x][y+1]&&!a[x+1][y])return;
    //如果既不能向右又不能向下，就返回
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=0;i<=m;++i){
        gets(kk);//输入
        for(int j=0;j<n;++j)
        if(kk[j]=='#')a[i-1][j]=1;
        //如果是#，就说明可以从这里走
    }
    if(a[0][0])dfs(0,0);//开始深搜
    if(flag)cout<<"Possible"<<endl;
    else cout<<"Impossible"<<endl;
    return 0;
} 
```
提交以后，发现你就华丽丽的WA了。为什么呢？
## 因为必须通过所有的#格才可以。
所以，代码应该是这样的：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10][10],m,n,flag;//a数组表示能不能选
char kk[10];//这个数组用来输入
void dfs(int x,int y){
    if(x==m-1&&y==n-1){//如果能走到最后一格
        for(int i=0;i<m;++i)for(int j=0;j<n;++j){
            if(a[i][j])return;//如果有个没走过
        }
        flag=1;//标记
        return;//返回
    }
    if(flag==1)return;//加快，优化
    if(a[x+1][y]){//如果可以向下走
        a[x+1][y]=0;//表示走过
        dfs(x+1,y);
        a[x+1][y]=1;//回溯
    }
    if(a[x][y+1]){//同上（懒）
        a[x][y+1]=0;
        dfs(x,y+1);
        a[x][y+1]=1;
    }
    if(!a[x][y+1]&&!a[x+1][y])return;
    //如果既不能向右又不能向下，就返回
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=0;i<=m;++i){
        gets(kk);//输入
        for(int j=0;j<n;++j)
        if(kk[j]=='#')a[i-1][j]=1;
        //如果是#，就说明可以从这里走
    }
    if(a[0][0]){
        a[0][0]=0;//肯定要走，先打上标记
        dfs(0,0);
    }
    if(flag)cout<<"Possible"<<endl;
    else cout<<"Impossible"<<endl;
    return 0;
} 
```
这就是最终代码。打代码不容易，望管理员通过~

---

## 作者：Texas_the_Omertosa (赞：0)

[题目传送门](https://www.bilibili.com/video/BV1Wp4y1H7A4/?spm_id_from=333.788.recommend_more_video.1)

### 0x01 思路

第一眼看到这题以为搜索一遍过，没想到样例总过不去，才发现题目里有这样一句话：Shik 将会操纵它上下左右移动。我天，**它不是走日，而是走四联通！**

又改了一下发现样例 3 总过不去，又看到：马是否可能每次移动都向下或向右。

这点我不会用搜索，也就是说，并不是要你判断能不能走到右下角，而是判断是否有可能**只向下或向右遍历完所有井号。**

但是我想这样就好办了，因为只向下或向右相当于走了两条邻边（即这个矩形的相邻的一条长和一条宽，平移过去即可），相当于 $h+w$，但是由于两线有交点，所以会重复算一点，即 $h+w-1$。于是我们得出这样一条结论：

当井号个数为 $h+w-1$ 时，马存在只像下或向右的可能性。

### 0x02 AC Code
```cpp
#include<bits/stdc++.h>
#define int QWQ
#define QWQ QwQ
#define QwQ QWq
#define QWq qWQ
#define qWQ qWq
#define qWq Qwq
#define Qwq qwQ
#define qwQ qwq
#define qwq long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,sum=0;
	char c;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c;
			if(c=='#')
			{
				sum++;//计算井号的数量
			}
		}
	}
	if(sum==n+m-1)
	{
		cout<<"Possible\n";//符合，有可能
	}
	else
	{
		cout<<"Impossible\n";//否则不可能
	}
	return 0;
}
```

完结~

---

## 作者：cjZYZtcl (赞：0)

## 第一眼看这题，以为是DFS
然后就交了一个代码上去，结果第一个点就TLE。。。
## 后来又想了想，觉得不对。
我分析了题目以后，得出了只往下和往右能到达右下角的几个条件：
- 一个点不会重复走多次
- 路径长度一定是矩阵行长加列长减一

### 为什么一个点不会重复走多次？
因为多次走过一个点必然会形成一个环，而这个环必然会包含两种相反的行走方向，所以只向右和向下不会一个点重复走多次。
### 为什么路径长度一定是矩阵行长加列长减一？
很明显，最简单的只向右和向下走的路径就是沿左边界和下边界或沿上边界和右边界走，而可以证明，其他走法路径长度一定和这两种相同。

所以，我们只需要判断一下这两个条件就好啦！

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, sum = 0;
char a[10][10];
char ch;
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	n = read(), m = read();
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ch = getchar();
			while(ch != '.' && ch != '#'){
				ch = getchar();
			}
			a[i][j] = ch;
			if(a[i][j] == '#') sum++;
		}
	}
	if(sum == n + m - 1) puts("Possible");
	else puts("Impossible");
}
```


---

