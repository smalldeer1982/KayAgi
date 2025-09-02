# SEARCH

## 题目描述

年轻的拉尔夫开玩笑地从一个小镇上偷走了一辆车，但他没想到的是那辆车属于警察局，并且车上装有用于发射车子移动路线的装置。

那个装置太旧了，以至于只能发射关于那辆车的移动路线的方向信息。

编写程序，通过使用一张小镇的地图帮助警察局找到那辆车。程序必须能表示出该车最终所有可能的位置。

小镇的地图是矩形的，上面的符号用来标明哪儿可以行车哪儿不行。$\verb!.!$ 表示小镇上那块地方是可以行车的，而符号 $\verb!X!$ 表示此处不能行车。拉尔夫所开小车的初始位置用字符的 $\verb!*!$ 表示，且汽车能从初始位置通过。

汽车能向四个方向移动：向北（向上），向南（向下），向西（向左），向东（向右）。

拉尔夫所开小车的行动路线是通过一组给定的方向来描述的。在每个给定的方向，拉尔夫驾驶小车通过小镇上一个或更多的可行车地点。


## 样例 #1

### 输入

```
4 5
.....
.X...
...*X
X.X..
3
NORTH
WEST
SOUTH```

### 输出

```
.....
*X*..
*.*.X
X.X..
```

# 题解

## 作者：stone_juice石汁 (赞：230)

## 标签明示要用$dfs$或$bfs$。题解中也有单独用$dfs$或$bfs$做的。

## 我发现我更过分。

**我两个都用了XD**

------------
**为什么发新题解？**

**1、方法不同：**因为我发现我不仅只是用了两种搜索实现简便运作，**我还是第一个开两个队列，用存点和缓存机制$A$了这道题的人**

**2、详细易懂：**我自认为我的题解算是比较详细了，希望能帮到那些没看懂其他题解的OIer

当然，如果我写的不好，轻喷QWQ。如果能看得过去，也希望对大家有帮助

## 那么说一下我的做法：$bfs$处理 + $dfs$扩展 + 队列存点与缓存 + 判重剪枝 * 1

等等！先别被我标题劝退！实际上技术含量很低。

~~说得好像很高级，其实就是胡搞乱搞出来的~~

我觉得我写的算详细了。如果你有耐心读完，估计也就会做了（吧？？？）

**这道题坑点倒是蛮多的，请让我一一道来**

- ## 先说思路吧：

	1、**开两个队列，一个用于存点，一个用于缓存**（以下简称为$q$队列与$t$队列），至于这两个队列有什么不一样...往下看
    
   2、先读入整张图（必须的）。开二维$char$数组，就按输入老老实实存就行了。**读到 $* $ 的时候，把当前的坐标直接$push$进$q$队列。理所应当地，在传进队列后，这个 $* $ 就没用了，因为之后车可能不会开回，并且我们把起始点给记住了。所以把 $* $ 直接换成$ .$（空位） 。**
   
   3、接下来就是一个$bfs$的过程。**取光 $q$ 队列里的全部坐标，每个坐标都进行一次方向扩展。方向扩展由 $dfs$ 完成。** 由于方向是固定的，通过输入给出，所以这个 $dfs$时间复杂度一点也不高。（其实你可以写一个循环代替$dfs$，但要开多变量，麻烦。所以说这是一个很不标准的$dfs$ XD）。
   
	4、上面提到过$bfs$负责把存储的坐标扔给$dfs$，$dfs$**往规定方向扩展。每跑到一个符合规则的点就把这个点坐标扔给 $t$ 队列。** 直到遇到 **$X$** 或者 **边界**（我搞这个东西的时候把边界忘了于是$RE$过 XD）。
    
   5、**最后在处理扩展完 $q$ 队列中的所有坐标后，把缓存在 $t$ 队列里的坐标全被扔进 $q$ 队列。**
   
   6、**每次操作一遍更换方向，就重复一遍3，4，5的过程。**
   
   7、最后，处理完成的答案坐标（即车可能开到的位置的坐标）全部存在 $q$队列中。弹出所有坐标，把那个位置的符号改为 $* $。输出整张图。
   
   8、卖萌装傻庆祝$AC$
   
   **所有步骤均在代码中有批注，易于各位OIer们寻找！**
   
- ## Q & A 及坑点

  - 1、
  
  	Q：**为什么要开两个队列，一个队列实现处理和录入不行吗？**
  
  	A：当然不行。因为在$q$队列扔出数据处理后，是会引入新坐标的。**毕竟队列里的坐标只能一个一个处理，不可能一下子扔完。而边扔出边引入则会引起数据混乱或无限循环。** 毕竟$q$队列要扔出所有的坐标啊...刚引入的坐标是不能扔出去的，要留在下一轮处理。所以这才有了缓冲队列$t$。
  
  - 2、
  
  	Q：**怎么实现通过输入字符串让$dfs$有针对性地扩展（只往规定方向扩展）？**
  
  	A：我的做法是这样的：
  
  	输入的不是字符串吗？然而我更喜欢用$N S W E$表示方向，怎么办？
  
  	好说！：取每个字符串的第一个字符就可以了。
  
  	Q：**那怎么把字符判断转化为扩展限制？**
  
  	A：我定义了两个数组：
  
  	dx[4] = ｛0, 0, -1, 1｝
  
  	dy[4] = ｛-1, 1, 0, 0｝
  
  	这种数组应该是司空见惯了。稍微想一下，就能想到$N S W E$ 分别对应$2，3，0，1$（下标值）。
  
  	定义一个$int$变量$pd$，判断一下，扔到$dfs$里去就可以了。
  
  - 3、**Q：这种做法不会爆时间吗？**
  
  	A：不会
  
  	**那是不可能滴**（滑稽），你不剪枝，只能跑$30$分。而且还会爆空间，贼恐怖。
  
  	但是我们可以剪枝。
  
  	观察$dfs$的过程，再来看下面这张图：
    
  	 ![](http://zhzxoj-tuchuang-1256463233.cos.ap-hongkong.myqcloud.com/2019/08/04/5d46d9d87b4fc.png)
   
  	星号表示待处理坐标，规定方向向北。
   	
 	假设我们现在处理了黄色区块的坐标，浅蓝色区域全部都会被录入。
    
  	那么再次处理上面两个坐标就没有意义了。实际上，当数据很大的时候，这样重复处理浪费了不少时间和空间。
    
  	所以，我们直接申明一个$vis$数组（$bool$型），已经看过的点就不再去管他了。
    
  	于是我们就有了一个$100$分的$AC$代码！
    
- ## 上代码！

	```cpp
	#include<bits/stdc++.h>
	#define mian main
	#define QWQ puts("QWQ");
	#define inf 0x3f3f3f3f
	#define maxn 55
	using namespace std;
	//第一步：开队列及相关变量数组 
	int n, m, w;//n，m：长宽，w：方向变化数 
	char _map[maxn][maxn];
	int pd;//pd用来记录方向以便在dfs发挥定向作用 
	int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};//如上文所讲 
	bool vis[maxn][maxn];//去重判断用 
	string d;//用来录入方向 
	queue <int> q;//存储队列 
	queue <int> t;//缓存队列 

	void dfs(int x, int y, int p)//第四步：深搜来跑单向路径，把跑过的坐标记录进缓冲队列t 
	{
		int tx = x + dx[p], ty = y + dy[p];
		if(_map[tx][ty] == 'X' || tx > n || tx <= 0 || ty > m || ty <= 0) return;//遇到障碍或边界就不跑了
		if(vis[tx][ty]) return;//很重要的剪枝：之前处理过也不跑了，因为都是同向，跑下去也一样，能省去大量时间。 
		vis[tx][ty] = true; //打上标记 
		t.push(tx); t.push(ty);
		dfs(tx, ty, p);
	}

	void bfs(string dir)
	{
		while(!q.empty())//第三步：查找q中所有坐标并进行 移动 记录 缓存 操作 
		{
			int tx = q.front();
			q.pop();
			int ty = q.front();
			q.pop();
			if(dir[0] == 'N') pd = 2;
			else if(dir[0] == 'S') pd = 3;
			else if(dir[0] == 'W') pd = 0;
			else if(dir[0] == 'E') pd = 1;//判断一下方向。 
			dfs(tx, ty, pd);
		}
		memset(vis, false, sizeof(vis));//记得每次清空vis数组 
		while(!t.empty())//将缓冲队列t中的缓存坐标转移到q中 
		{
			q.push(t.front());
			t.pop();
			q.push(t.front());
			t.pop();
		}
	}

	int main()
	{
		cin >> n >> m;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
			{
				cin >> _map[i][j];//第二步：录入整张图 
				if(_map[i][j] == '*')//扫到起始点 
				{
					q.push(i); 
					q.push(j);
					_map[i][j] = '.';//因为已经记录进q队列，没有再留的必要，打回原形。 
				} 
			}
		cin >> w;
		for(int i = 1; i <= w; i ++)//第6步：每次读入都重复过程 
		{
			cin >> d;
			bfs(d);
		}
		
		while(!q.empty())//第7步：直接取出q中所有坐标，改符号为*并输出图 
		{
			int tx = q.front();
			q.pop();
			int ty = q.front();
			q.pop();
			_map[tx][ty] = '*';
		} 
		for(int i = 1; i <= n; i ++)
		{
			for(int j = 1; j <= m; j ++) cout << _map[i][j];
			cout << endl;
		}
	
		return 0;//第8步：QWQ 
	}
	```
## 希望我的这篇题解对大家有帮助！

~~码子不易，各位大佬是不是应该....~~

---

## 作者：dingcx (赞：107)

~~```dfs``` 它不香吗~~

## 思路

其实这道题的思路还是比较简单的，就**做 N 次 ```dfs```**，把每次最后到达的点记录下来就好了。

然而用 ```dfs``` 往往就要考虑时间问题，这道题直接搜的时间复杂度是 $(R+C)^N$，显然会**超时**。（~~复杂度我也不确定，反正绝对会超~~）

所以重点在于**如何优化**。

## 记忆化搜索

容易想到用**记忆化搜索**来优化。

对于每一个操作，如果执行完这个操作到达的点与之前另一个执行完这个操作到达的点相同，那么不管前面的走法有多大不同，现在开始这两个方案就是**完全一样**的。

由此，我们可以定义一个 ```bool``` 数组 ```vis[dep][x][y]``` 表示在执行完第 ```dep``` 个操作后是否到过点 ```(x,y)```。这就是记忆化搜索。

但可能有人认为（~~比如我~~）：这也没有减掉多少种可能啊，怎么就不会超时呢？

但事实上，要执行 N 次，每次少一点，最后会少很多。算一下时间复杂度可能更加明白：每次最多只有 $R\times C$，总共 N 次，所以复杂度就是 $N\times R\times C$，显然不超时。

## 细节

时间满足了，现在再说一下细节部分。

1. 注意一些读入的细节（例如换行）。

2. ```'*'```也是能走的。

3. 记录方向的数组的值和操作数组一定要对应。（不太好描述，可以看后面的代码）

4. ```dfs```中往后遍历时走不通了直接 ```break```，因为后面也走不了。

## 代码

你们喜欢的代码在这里~

代码中 ```n``` 代表 R；```m``` 代表 C；```k``` 代表 N；深度 ```dep``` 是 ```k```最浅，```0``` 最深（这样子好写）。

```cpp
#include<cstdio>
using namespace std;
const int MAXN=1010;
bool _map[55][55],vis[MAXN][55][55];//是否能走，有没有到过
int to[MAXN],pos[4][2]={1,0,0,1,-1,0,0,-1};//方向数组，操作数组
int read(){//快读
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
void dfs(int dep,int x,int y){//深搜，dep是深度
	if(vis[dep][x][y]) return;//来过就返回
	vis[dep][x][y]=1;//记录
	if(dep==0) return;//这里可以直接返回，因为上一行已经记录了
	while(_map[x+=pos[to[dep]][0]][y+=pos[to[dep]][1]]) dfs(dep-1,x,y);//移动+往下遍历，细节3+细节4，这里压行有点狠
}
int main(){//主函数
	int n=read(),m=read(),sx,sy;//sx和sy是初始位置
	char c,s[10];
	for(int i=1;i<=n;i++){//读入图
		scanf("\n");//细节1
		for(int j=1;j<=m;j++){
			c=getchar();
			if(c=='.') _map[i][j]=1;//记录
			if(c=='*') _map[i][j]=1,sx=i,sy=j;//记录，细节2
		}
	}
	int k=read();
	for(int i=k;i>0;i--){//dep是反的，这里也要反
		scanf("\n%s",s);//细节1
		if(s[0]=='S') to[i]=0;//细节3，想清楚哪边是加哪边是减
		if(s[0]=='E') to[i]=1;
		if(s[0]=='N') to[i]=2;
		if(s[0]=='W') to[i]=3;
	}
	dfs(k,sx,sy);//开始深搜
	for(int i=1;i<=n;i++){//输出
		for(int j=1;j<=m;j++) printf("%c",vis[0][i][j]?'*':(_map[i][j]?'.':'X'));//这里压行也有点狠
		printf("\n");
	}
	return 0;//华丽结束
}
```
我还是把不压行的代码放一下吧，防止有人不习惯压行……

第一个
```cpp
while(1){
	x+=pos[to[dep]][0],y+=pos[to[dep]][1];//改变位置
    if(!_map[x][y]) break;//判断退出
    dfs(dep-1,x,y);//往下遍历
}
```
第二个
```cpp
if(vis[0][i][j]) printf("*");//最终可以到达
else if(_map[i][j]) printf(".");//可以到达
else printf("X");//不可以到达
```

看我写了这么多，总得点个赞在走呀~

---

## 作者：丿王者之路 (赞：30)

大概看了一下其它题解，跟我的方法有点不一样，那我就来水发一道。

这是一道纯搜索题，只要弄清题意，还是很好写出来的；

首先我先来讲一下我的思路：

首先，我在读入图的时候，先预处理一下，将起点记录在ans[][]数组中，可行与不可行记录在map[][]数组中（存在map[][]纯属习惯，也比叫好判断一点，当然也可以不这样写）；

然后，读入方向，每读入一个，就search（）一遍；

最后，在输出，如果ans[][]为1，则表示有可能的位置，就输出‘ \* ',否则就按原图输出（当然要特判一下这个点是否是起点，如果是起点，但不是最后的有可能出现的点，就输出’ . '）;

ps:ans[][]是用来记录没走一步可能出现的位置;

如果还有疑问可以参考代码，进行理解；


```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int r,c,n,map[60][60],ans[60][60];
char st[60][60],str[1000];
bool vis[60][60];
//vis数组是用来记录，当次search（）中ans[][]为1点，是上次serch()得来的ans[][]，
//还是由上次search()得来的ans[][]由这次search()移动得来的; 
int dx[5]={0,-1,0,1,0},dy[5]={0,0,1,0,-1};
//方向，我是左上角为原点，向下为x的正方向，想又为y的正方向； 
void search(int direct)
{
    memset(vis,0,sizeof(vis));//新的一 轮，就要重新开始 
    for(int i=1;i<=r;i++)
    for(int j=1;j<=c;j++)
    {
        if(ans[i][j] && !vis[i][j])
        {
            int ddx=i+dx[direct],ddy=j+dy[direct];
            ans[i][j]=0;//它一移动原来的位置就不在有可能在有； 
            while(map[ddx][ddy])//将其能到的点全标记； 
            {
                ans[ddx][ddy]=1;
                vis[ddx][ddy]=true;
                ddx=ddx+dx[direct];ddy=ddy+dy[direct];
            }
        }
    }
}
int main()
{
    scanf("%d %d",&r,&c);
    for(int i=1;i<=r;i++)
    {
        scanf("%s",st[i]+1);
        for(int j=1;j<=c;j++)
        {
            if(st[i][j]=='*') map[i][j]=1,ans[i][j]=1;
            //最开始的位置，就是还没移动时的可能的位置； 
            else if(st[i][j]=='.') map[i][j]=1;
            else map[i][j]=0;
        }
    }
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        if(str[0]=='N') search(1);//向上 
        if(str[0]=='E') search(2);//向右 
        if(str[0]=='S') search(3);//向下 
        if(str[0]=='W') search(4);//向左 
    }
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            if(ans[i][j]) printf("*");
            else 
            {
                if(st[i][j]=='*') printf(".");
                else printf("%c",st[i][j]);
            }
        }
        printf("\n");
    }
}
```

---

## 作者：lzxhdxx (赞：23)

## 疑似本题最短dfs（无压行加上两行大括号和一行定义共8行）
### 一直WA的同学千万不要错过本题解末尾的坑点整理
#### 题意简述：
输入一幅图并输入N个命令，从“*”点开始向命令所指的方向（以下简称命令方向）探索，输出所有可能的重点

先贴代码：（代码看起来很长，但是如果把注释删掉只有45行，1.06KB）
```cpp
#include <iostream>
using namespace std;
int dx[5] = { 0,-1,1,0,0 }, dy[5] = { 0,0,0,-1,1 };// dx, dy用来控制车的上下左右移动
int n, m, k;//n,m地图的长宽，k命令的个数
int dir[1000010], x, y;//dir是每条命令所指的方向；x,y是车初始位置
bool s[110][110][2010] = { false };//剪枝用的三维数组，第三个2010一定要开够！我因为这个WA了将近十次！
char ma[110][110];//地图
void dfs(int stp, int xx, int yy, bool flag)//stp当前到达的步数；xx,yy当前到达的坐标；flag是当前可不可以尝试下一步
/*PS:当前命令执行过了，就有两种选择：一是继续执行当前命令，二是尝试下一步,但是你如果当前命令还没有执行过，就只能执行当前命令
坑点：当前命令需要且必须要执行
flag就是记录当前命令是否执行过的bool变量*/
{
	if (xx<1 || yy<1 || xx>n || yy>m || stp > k || s[xx][yy][stp] || ma[xx][yy] == 'X') return;
	//xx<1||yy<1||xx>n||yy>m 判断是否越界，越界就return;
	//stp>k 看看当前的步数有没有走超（比如一共3步，你现在已经到了第4步），如果走超就return;
	/*s[xx][yy][stp] 看看当前坐标处有没有来过
	注意：这里是s[xx][yy][stp]而不是s[xx][yy][dir[stp]]
	WA例分析：
	3 3
	*..
	.X.
	...
	5
	EAST SOUTH WEST NORTH EAST
	这时你需要两次以“EAST”方向经过（1,1）和（1,2），所以不能用方向剪枝，要用当前步数
	*/
	//ma[xx][yy]=='X' 你总不能从障碍物上开过去吧
	if (stp == k) ma[xx][yy] = '*';
	/*如果现在的步数已经等于要求的步数，就把当前坐标标记为“*”
	注意：
	这里不能直接return;
	WA例分析：
	3 2
	*.
	X.
	X.
	2
	EAST SOUTH
	如果你在这里直接return,那么你在(1,2)就会直接结束dfs,(2,2)和(3,2)就都不会被标记为“*”
	*/
	dfs(stp, xx + dx[dir[stp]], yy + dy[dir[stp]], true);//如果当前命令方向可以继续走，就继续探索
	if (flag) dfs(stp + 1, xx + dx[dir[stp + 1]], yy + dy[dir[stp + 1]], true);
	//如果当前命令方向已经走过了，即flag==true，就可以尝试下一个命令方向
	s[xx][yy][stp] = true;
	//剪枝方法：s[当前x坐标][当前y坐标][当前步数]=true，一定注意是当前步数而不是当前方向，原因参见代码17行WA例
}
int main()
{
	cin >> n >> m;//输入长宽
	for (int i = 1; i <= n; i++)//输入地图
		for (int j = 1; j <= m; j++)
		{
			cin >> ma[i][j];
			if (ma[i][j] == '*')//输入时存储初始点x，y坐标，并把初始点设置为'.'
				//必须设置成'.'的原因：初始点是“*”，结束点也是“*”，初始点就会影响结果
				//但是初始点必须在dfs前设置为'.'，因为车有可能停在原始区域（如行走了一个环形）
				x = i, y = j, ma[i][j] = '.';
		}
	cin >> k;//命令数
	for (int i = 1; i <= k; i++)
	{
		string str;
		cin >> str;
		switch (str[0])//比较首字符，重复比较用switch更方便
		{
			case 'N':dir[i] = 1; break;
			case 'S':dir[i] = 2; break;
			case 'W':dir[i] = 3; break;
			default: dir[i] = 4;
		}
	}
	dfs(1, x, y, false);//开始探索
	for (int i = 1; i <= n; i++)//输出地图
	{
		for (int j = 1; j <= m; j++)
			cout << ma[i][j];
		cout << endl;
	}
	return 0;
}
```


## 坑点和建议：（本人WA的经历，自认为非常全面，一直WA的同学不要错过）

1.这个代码如果不剪枝会有太多重复搜索，所以**必须剪枝**，剪枝要**用步数剪枝而不能用方向**，WA例及分析请看代码17行（不剪枝只能AC#1,3,5，剩下全部TLE，30分）（如果剪枝用了方向只能AC#1,3，20分，没错，还不如不剪枝）

2.**每个步骤需要且必须要执行**，这个是dfs函数中flag的作用（这个没写会WA#3，90分）

3.**每个步骤一定要重复尝试直到不能再继续**，不然会漏非常多可能的终点

4.**数组不能越界**，不然访问错误会卡机，0分

5.剪枝用的**s数组一定要开够**！我刚开始开的是s[110][110][110]，会WA#2,10，80分

6.**初始点在dfs前需要改成“.”**，不然会影响输出，参见main函数第8行（不然只能AC#2,3,10）

7.输入输出千万**不能用getchar()和putchar()**，这个我试过，输出全部正确也0分

8.**搜到可能的终点时不能直接return**，WA例及分析在代码30行

9.此题存储方向**用switch判断**很方便，但是看到之前的大佬没有用的，在这里提醒一句，switch里千万**别忘了写break**，（没写0分）

10.这里有一个小建议：**用dx，dy来控制小车的转弯**，这样就可以有效避免很多判断，我用这种方法成功把我的dfs函数长度减少到8行，还让代码比较优美可读

希望我的题解能够帮助到你

感谢管理大大审核！感谢大家耐心阅读！

---

## 作者：wangxingqi (赞：22)

        
    
```cpp
# include <iostream>
# include <memory.h>
# include <cstring>
using namespace std;
string dir;
char map[55][55]; //地图 
int r, c, n;
bool mem[55][55]; //记录那些位置有可能有车 
void mark(int i, int j, int dir_i, int dir_j){     //i,j表地址 dir_i、dir_j表移动方向 求可能情况 
    map[i][j] = '.';
    i += dir_i;
    j += dir_j;
    while (i <= r && j <= c && i > 0 && j > 0){
        if (map[i][j] == 'X')
            return;
        mem[i][j] = true;
        i += dir_i;
        j += dir_j;
    }
}
int main(){
    ios::sync_with_stdio(false);    //输入 
    cin >> r >> c;
    for (int i = 1 ; i <= r ; ++ i)
        for (int j = 1 ; j <= c ; ++ j)
            cin >> map[i][j];
    cin >> n;
    for (int i = 1, dir_i, dir_j ; i <= n ; ++ i){
        cin >> dir;
        dir_i = dir_j = 0;
        if (dir == "NORTH")        //判断方向 
            dir_i = -1;
        if (dir == "SOUTH")
            dir_i = 1;
        if (dir == "EAST")
            dir_j = 1;
        if (dir == "WEST")
            dir_j = -1;
        memset(mem, 0, sizeof(mem));    //清零，防止上一时刻的结果影响本次计算 
        for (int j = 1 ; j <= r ; ++ j)
            for (int k = 1 ; k <= c ; ++ k)
                if (map[j][k] == '*')
                    mark(j, k, dir_i, dir_j);
        for (int j = 1 ; j <= r ; ++ j)    //把所有可能录入地图 
            for (int k = 1 ; k <= c ; ++ k)
                if (mem[j][k])
                    map[j][k] = '*';
    }
    for (int i = 1 ; i <= r ; ++ i){    //输出 
        for (int j = 1 ; j <= c ; ++ j)
            cout << map[i][j];
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Blue_wonders (赞：18)

# 广度优先搜索AC
#### 详细易懂的代码
bfs易错点注意！！！
拿不到满分可能是数组开小了
题目数据很可能是WEST,EAST,WEST,EAST;所以数组一定开大，或者是标记点是否是刚刚存过的
我没记录数组开10w错8个点~~
```
//这道题不提供数据下载，所以自己写了几个输入输出可以试试
输入1：
5 4
.*X.
....
....
..X.
....
2
SOUTH
WEST
输出1：
..X.
*...
*...
*.X.
*...

输入2：
5 20
.............X.XXXXX
....XX..XXXXX...*..X
....XXXX.XXX.X......
....................
...................X
7
SOUTH
WEST
EAST
WEST
NORTH
EAST
SOUTH
输出2：
.............X.XXXXX
.***XX**XXXXX......X
.***XXXX.XXX.X.****.
.***...........*****
.******************X
```
队列广搜很简单，一层一层找就ok
最后把找到的答案标记起来，最后输出
具体看代码
### 我是将一层方向的所有点都找出来，然后再进行下一层的搜索
```cpp
//https://www.luogu.org/problemnew/show/P1189
//bfs
#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
using namespace std;
struct point{//结构体进行队列的保存，不用开多个队列
	int x,y,dep;//分别保存横坐标，纵坐标，和层数
};
int kx[5]={0,-1,1,0,0};
int ky[5]={0,0,0,-1,1};//对x，y坐标的加减用x=x+k[i]表示，代替四个if的判断
int n,m,l,startx,starty;
int a[51][51];//记录地形，是否可以过
int b[51][51]; //记录一个周期中哪些被记下来过，避免一个点在队列中出现多次
int c[1001];
void bfs(int sx,int sy){
	int head=0,tail=1;
	point h[1000001];//创建队列	
	h[0].x=sx;
	h[0].y=sy;
	h[0].dep=1;
	while(head<tail){
		point p=h[head++];
		int x=p.x,y=p.y,step=p.dep;
		if(step>l)a[x][y]=2;//判断是否是最后结果
		while(1>0){//一直循环，直到break打破
			int x0=x+kx[c[step]],y0=y+ky[c[step]];
			if(x0>0&&x0<=n&&y0>0&&y0<=m&&step<=l&&a[x0][y0]!=0&&b[x0][y0]!=step+1){//首先x0，y0在地图中，然后可以通行，最后判断这个点是否是这个周期中求过的点
				h[tail]={x0,y0,step+1};//符合条件，进入队列
				tail++;
				b[x0][y0]=step+1;//把这个点附上周期的数值，避免在同周期中重复计算
				x=x0;y=y0;//保存这个点，以便下一次计算
			}
			else break;//如果下一个点不满足，就退出循环
		}
	}
}
int main(){map<string,int>g;//用map函数映射方向，用数值表示便于以后for循环判断方向
	g["NORTH"]=1;g["SOUTH"]=2;g["WEST"]=3;g["EAST"]=4;//定义北==1,南==2,西==3,东==4
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){//1能走，0不能走 
			char k;
			cin>>k;
			if(k=='.')a[i][j]=1;
			if(k=='X')a[i][j]=0;
			if(k=='*'){//标记起点横纵坐标，起点可以走，所以变成'.'
				startx=i;
				starty=j;
				a[i][j]=1; 
			}
		}
	}
	cin>>l;
	for(int i=1;i<=l;i++){
		string s;//输入字符串
		cin>>s;
		c[i]=g[s];//用map映射用数字表示字符串
	}
	bfs(startx,starty);//广度优先搜索答案
	for(int i=1;i<=n;i++){//输出改变过并标记答案的地图
		for(int j=1;j<=m;j++){
			if(a[i][j]==1)cout<<'.';
			if(a[i][j]==0)cout<<'X';
			if(a[i][j]==2)cout<<'*';
		}
		cout<<endl;//每输入一行就换行
	}
	return 0;//结束程序
}
```

---

## 作者：ChthollyTree (赞：15)

递归版深搜，记得要剪枝去重。

见下面的注释。

（记得出发点的\*搜索前要去掉）

、、、



     


    


        
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXR 60
#define MAXN 1005 
const int nx[4] = {1,0,-1,0};
const int ny[4] = {0,1,0,-1};
char a[MAXR][MAXR];//地图 
int b[MAXR][MAXR][MAXN];//一个点是否在某时走过 
int r,c,n;
char d[MAXN][10]; 
int sx,sy;
inline void rd()//输入 
{
    scanf("%d%d",&r,&c);
    for(int i = 1; i <= r; i ++)
        scanf("%s",a[i]+1);
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%s",d[i]);
     }
     for(int i = 1; i <= r; i ++)//寻找出发点 
         for(int j = 1; j <= c; j ++)
        {
            if(a[i][j] == '*')
            {
                sx = i;
                sy = j;
                break;
            }
         } 
    a[sx][sy] = '.';
}
bool zj(int x,int y)//是否越界 
{
    return x<=r&&y<=c&&x>0&&y>0;
}
int hua(char x) 
{
    if(x == 'N')//上 
        return 2;
    if(x == 'S')//下 
        return 0;
    if(x == 'E')//左 
        return 1;
    if(x == 'W')//右 
        return 3;
}
void dfs(int x,int y,int s)//深搜（x，y为x行y列，记录仪的第s个方向） 
{
    if(b[x][y][s])//去重，没有这个30分  
        return;
    b[x][y][s] = 1;//标记
    if(s == n + 1)
    {
        a[x][y] = '*';
        return;
    }
    else
    {
        int ex = x,ey = y,p;
        p = hua(d[s][0]);
        ex += nx[p];
        ey += ny[p];
        while(zj(ex,ey)&&a[ex][ey] != 'X')
        {
            dfs(ex,ey,s+1);
            ex += nx[p];
            ey += ny[p];
        }
    }
}
int main()
{
    rd();
    dfs(sx,sy,1);
    for(int i = 1; i <= r; i ++)//输出答案 
        printf("%s\n",a[i]+1);
    return 0;
 } 
、、、
```

---

## 作者：夏色祭 (赞：14)

#一道练剪枝的好题

每次往第k个方向一直走，直到碰到障碍或是出了边界，每走一步都算这个方向走过了，然后就调用过程，去走下个一方向。

然而这样只有30分，所以我们还需要剪枝。

f[i,j,k]表示第k次到了(i,j)有没有尝试过，如果有，直接exit掉。

献上没有66666a代码丑陋的代码：

```cpp
const
  x:array[1..4]of longint=(-1,1,0,0);
  y:array[1..4]of longint=(0,0,-1,1);//四个方向
var
  a:array[0..51,0..51]of char;
  b:array[0..51,0..51]of boolean;
  f:array[0..51,0..51,1..1000]of boolean;
  s:array[0..1001]of longint;
  n,m,k,i,j,p,q:longint;
  s1:ansistring;
function zz(s1:ansistring):longint;
begin
  if s1='NORTH' then exit(1);//上
  if s1='SOUTH' then exit(2);//下
  if s1='WEST' then exit(3);//左
  if s1='EAST' then exit(4);//右
end;
procedure try(kk,l,r:longint);
var
  i,j:longint;
  begin
    if f[l,r,kk] then exit;//剪枝
    f[l,r,kk]:=true;
    if kk>k then 
      begin
        b[l,r]:=true;
        exit;
      end;//边界
    i:=l+x[s[kk]];
    j:=r+y[s[kk]];
    while (a[i,j]<>'X') do //直到碰上障碍，因为边界被围上了一圈障碍
      begin
        try(kk+1,i,j);//每走一步，都尝试去走下个一方向
        inc(i,x[s[kk]]);
        inc(j,y[s[kk]]);
      end;
  end;//dfs
begin
  readln(n,m);
  for i:=1 to n do 
    begin
      for j:=1 to m do 
        begin
          read(a[i,j]);
          if a[i,j]='*' then 
            begin 
              p:=i;
              q:=j;
            end;
        end;
      readln;
    end;
  for i:=0 to n+1 do 
    begin
      a[i,0]:='X';
      a[i,m+1]:='X';
    end;
  for i:=0 to m+1 do 
    begin
      a[0,i]:='X';
      a[n+1,i]:='X';
    end;//给地图的周围一圈围上障碍
  readln(k);
  for i:=1 to k do 
    begin
      readln(s1);
      s[i]:=zz(s1);
    end;//把字符串表示的方向转换成数字
  try(1,p,q);
  for i:=1 to n do 
    begin
      for j:=1 to m do 
        if b[i,j] then write('*')
          else if a[i,j]='*' then write('.')
            else write(a[i,j]);
      writeln;
    end;//输出
end.

```

---

## 作者：子谦。 (赞：12)

## 超简单的递推（没错，我就是喜欢用各种各样不同的方法来花式A题（主要是我觉得搜索复杂度可能过不了，又不想算了））

题意很简单，相信大家都看明白了，但是有一个地方要注意一下，就是每次走，至少走一格，不能不走，通过样例应该也能发现这个要求，直接上代码吧（代码并不能AC，甚至样例也过不了，但是只要用样例调一下，很容易就可以看出来哪个地方的处理被我删掉了（悄悄告诉你：很短的一个赋值））

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc getchar
#define maxn 55
#define maxm 1005
using namespace std;

inline ll read(){
	ll a=0;int f=0;char p=gc();
	while(!isdigit(p)){f|=p=='-';p=gc();}
	while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
	return f?-a:a;
}

int r,c,n,a[maxn][maxn][maxm];//r，c和n是什么意思想必不用介绍，a[i][j][k]表示还剩k步是否可以到达第i行第j列，1表示可以，0表示不可以
char s[maxn][maxn];
inline void solve_n(){
	for(int i=1;i<=c;++i)  //向北移动时列与列之间互不影响，其他方向以此类推
		for(int j=r;j;--j){  //因为是往上走，所以我们把从下往上扫（从上往下也可以，但是会慢一些）
			if(!a[j][i][n+1])continue;  //如果上一步能走到这里，那么就从这里出发，否则不管
			while(s[j-1][i]=='.')  //一直走到不是路为止
				a[--j][i][n]=1;
		}
}
inline void solve_s(){  //与向北走类似，只是改一下方向
	for(int i=1;i<=c;++i)
		for(int j=1;j<=r;++j){
			if(!a[j][i][n+1])continue;
			while(s[j+1][i]=='.')
				a[++j][i][n]=1;
		}
}
inline void solve_w(){
	for(int i=1;i<=r;++i)
		for(int j=c;j;--j){
			if(!a[i][j][n+1])continue;
			while(s[i][j-1]=='.')
				a[i][--j][n]=1;
		}
}
inline void solve_e(){
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j){
			if(!a[i][j][n+1])continue;
			while(s[i][j+1]=='.')
				a[i][++j][n]=1;
		}
}	

int main(){
	r=read();c=read();
	for(int i=1;i<=r;++i)
		scanf("%s",s[i]+1);
	n=read();char zz[10];
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j){
			if(s[i][j]!='*')continue;
			a[i][j][n]=1;break;
		}
	while(n--){
		scanf("%s",zz+1);
		switch(zz[1]){
			case 'N':solve_n();break;
			case 'S':solve_s();break;
			case 'W':solve_w();break;
			case 'E':solve_e();break;
		}
		/*for(int i=1;i<=r;++i,puts(""))
			for(int j=1;j<=c;++j)
				printf("%d ",a[i][j][n]);*/
	}
	for(int i=1;i<=r;++i,puts(""))
		for(int j=1;j<=c;++j)
			putchar(a[i][j][0]?'*':s[i][j]);  //输出时判定如果最后一步可以走到就输出*，否则输出原来的字符（别忘了处理一个特殊点哦）
	return 0;
}
```

是不是很好理解呢，欢迎在评论区提出你的疑问，我看到了会回复的

---

## 作者：小穹 (赞：8)

# 本人用的模拟来做这题的：
### ~~其实没什么优化,只是把连续相同的方向省掉了（根本不用优化都能AC）~~

边输入边执行，每次在上一个方向可以到达的地方继续扩展，

用一个pd来记录每次走到的点，

最后在覆盖到记录坐标的数组dx,dy里面，供下一次扩展。

最后一方向走出来的点就是 答案 即汽车最终可能出现的位置

具体详细看代码（内有注释）

```cpp
#include<bits/stdc++.h>
#define fs(i,a,b) for(int i=a;i<=b;i++) //新定义 前后两个效果一样
using namespace std;
int dy[100001],dx[100001]; //记录每次可到达地方的坐标 
int n,m,k,r=1; 
char hxt[51][51]; //地图 
bool pd[51][51]; //用来判断每一次方向能走到的地方 
void rj(int xf,int yf)
{
    fs(i,1,n) fs(j,1,m) pd[i][j]=0; //初始化该方向而到达的地方 
	fs(i,1,r) while(hxt[xf+dx[i]][yf+dy[i]]=='.' ) dx[i]=xf+dx[i],dy[i]=yf+dy[i],pd[dx[i]][dy[i]]=1; //每一个点的扩展,pd来记录可到达的点 
	//把上一个方向能走到的点以现在方向扩展 
	r=0;//下一次可扩展点总数清零
	fs(i,1,n) fs(j,1,m) if(pd[i][j]) r++,dx[r]=i,dy[r]=j; //更新下一次搜索的点 
}
int main()
{
	scanf("%d%d",&n,&m);
	fs(i,1,n) fs(j,1,m)
	{
		cin>>hxt[i][j];
		if(hxt[i][j]=='*') dx[r]=i,dy[r]=j,hxt[i][j]='.'; //记录出发点 
	}
	cin>>k;
	string a,b;
	fs(i,1,k)
	{
		cin>>a; 
		if(a==b) continue; //如果该方向与上一个方向相同则不扩展 
		else
		{
			switch(a[0])			
			{
				case 'N':rj(-1,0);break; //向地图上方运动 即 X-- 
				case 'S':rj(1,0);break;  //向地图下方运动 即 X++ 
				case 'E':rj(0,1);break;  //向地图右方运动 即 Y++ 
				case 'W':rj(0,-1);break;  //向地图左方运动 即 Y-- 
			}
		}
		b=a; //用来与下一次方向比较 
	}
	fs(i,1,r) hxt[dx[i]][dy[i]]='*'; //最后可到达的点 即最后一个方向可以到达的点 
	fs(i,1,n)
	{
		fs(j,1,m) cout<<hxt[i][j]; //输出 
		printf("\n");
	}
}
```


---

## 作者：远航之曲 (赞：7)

来水一篇题解


用的迭代加深。。。和楼下不一样

直接上代码。。没啥好说的，基础题

    
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int map[60][60],turn[1010];
bool vis[60][60][1010];
int n,r,c,b1,b2;
char ch,ch1[10],a[60][60];
int d[5][2]={{0,0},{-1,0},{1,0},{0,-1},{0,1}};
void init()
{
    cin>>r>>c;  
    for (int i=1;i<=r;i++)  
        for (int j=1;j<=c;j++)  
        {  
            cin>>a[i][j];  
            if (a[i][j]=='.') 
                map[i][j]=1;  
            if (a[i][j]=='X') 
                map[i][j]=0;  
            if (a[i][j]=='*')   
            {  
                a[i][j] = '.';  
                map[i][j] = 1;  
                b1 = i;  
                b2 = j;  
            }  
        }  
    cin>>n;  
    for (int i=1;i<=n;i++)  
    {  
        char dir[5];  
        cin>>dir;
        int m=i;  
        if (dir[0]=='N') turn[m] = 1;                
        if (dir[0]=='S') turn[m] = 2;  
        if (dir[0]=='W') turn[m] = 3;  
        if (dir[0]=='E') turn[m] = 4;  
    }
}
void dfs(int x,int y,int t)
{
    if (vis[x][y][t]) return;
    vis[x][y][t]=true;
    if (t>n)
    {
        a[x][y]='*';
        return;
    }
    x+=d[turn[t]][0];y+=d[turn[t]][1];
    while (x>=1 && x<=r && y>=1 && y<=c && map[x][y])
    {
        dfs(x,y,t+1);
        x+=d[turn[t]][0];y+=d[turn[t]][1];
    }
}
void outit()
{
    for (int i=1;i<=r;i++)
    {
        for (int j=1;j<=c;j++)
            printf("%c",a[i][j]);
        printf("\n");
    }
}
main()
{
    init();
    dfs(b1,b2,1);
    outit();    
}
```

---

## 作者：ddddk (赞：4)

这里讲下我自己的思路：

一道深搜题，就是求从出发点按照一些指定方向走后的可能到达的地点，要注意的是可以走无数步，直到撞墙，并且不用标记

要注意的是要记忆化优化，判断之前有没有走过这个点，不然只有30分（~~不要问我是怎么知道的~~）

这里我与其他人的存放方向的位置不一样，我是用way[n][1]表示第n次向上还是向下；way[n][2]表示第n次向左还是向右

然后下面贴代码(个人习惯模块化)
```
#include <bits/stdc++.h>
using namespace std;
int r,t,sx,sy,way[1006][3],n;//way储存走的方向
char ans[56][56];
bool m[56][56],vis[56][56][1006];
//m表示是否为墙 vis标记是否走过
void init(){//答案数组标记初始化
    for(int i=0;i<56;i++)
        for(int j=0;j<56;j++)
            ans[i][j]='.';
}
void output(){//输出答案数组
    for(int i=1;i<=r;i++){
        for(int j=1;j<=t;j++)
        	cout<<ans[i][j];
        cout<<'\n';
    }
}
void input(){
    cin>>r>>t;
    for(int i=1;i<=r;i++)
        for(int j=1;j<=t;j++){
            char temp;
        	cin>>temp;
        //	if((temp!='.')&&(temp!='*'))
        //		ans[i][j]=='X'; //之前测试出的一个神奇的bug，测试请注释掉下面判断是否为'X'，欢迎dalao指导
        	if(temp=='.')//如果是.
        		m[i][j]=true;//标记可以走
        	if(temp=='*'){//如果是*
        		m[i][j]=true;//标记可以走
        		sx=i;
        		sy=j;//保存起点位置
            }
            if(!m[i][j])//不可以走就是X
                ans[i][j]='X';
        }
    cin>>n;
    for(int i=1;i<=n;i++){
        string temp;
        cin>>temp;
        switch(temp[0]){//判断方向
            case 'N':
                way[i][1]=-1;
                break;
            case 'S':
                way[i][1]=1;
                break;
            case 'W':
                way[i][2]=-1;
                break;
            case 'E':
                way[i][2]=1;
                break;
        }
    }
}
void dfs(int x,int y,int step){
    if(vis[x][y][step])//记忆化
        return ;//如果访问过直接跳过
    else
        vis[x][y][step]=1;//不然就标记
    
    if(step==n+1){//如果走完了就标记
        ans[x][y]='*';
    	return ;
    }
    //神奇的for 循环
    //i表示向前第几步，way表示前进的方向
    for(int i=1;m[x+way[step][1]*i][y+way[step][2]*i];i++)
    	dfs(x+way[step][1]*i,y+way[step][2]*i,step+1);
    //搜索不用标记
}
int main()//简短的主程序
{
    init();//初始化
    input();//输入
    dfs(sx,sy,1);//搜索
    output();//输出
    return 0;
}
```

---

## 作者：_H1kar1 (赞：3)

本来以为是个大模拟，没想到自己被卡了好久...题解大佬都讲了剪枝，我自愧不如，但是个人认为本题除了剪枝这道题也有很多需要注意的细节，这篇题解我会一步一步讲自己的犯错经历，希望对你们有所帮助qwq

首先浏览一遍题意，感觉十分可做，大体思路是用dfs模拟每一次开车经历

ps:为了排版和方便阅读，只用向南作为例子，下同

pss：这篇题解不涉及剪枝内容

```cpp
//v[x][y]用来记录车车的位置～
void dfs(int x,int y,int p){
	//位于x，y，正在处理第p条命令
    if(p>k)	return ;
    string heading=ord[p];
	if(heading=="SOUTH"){
		int fx=n-x;//对于点x,y，最多向下走n-x格
		for(int i=1;i<=fx;++i){
			int nx=x+i;//拓展出的点是nx,y
			if(a[nx][y]=='X')//如果碰到墙，说明往后走不了了
				return;
			v[x][y]=false;
			v[nx][y]=true;//车子从x,y开到了nx,y
			dfs(nx,y,p+1);//处理下一条命令
		}
	}
    ...//三个方向
}

//a[][]是地图
int main(){
	...
    
    //输出答案
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(!v[i][j]){
				if(a[i][j]=='*')
					putchar('.');
				else 	putchar(a[i][j]);
			}
			else	putchar('*');
		}
		puts("");
	}
	return 0;
}

```
然后发现WA飞了hhhh（**不考虑剪枝**）

仔细研究样例发现，对于每个命令，不可以不做（当然），也就是说，**如果车在点x,y且准备向下走，而下方紧挨着墙，则说明这种情况不存在**

我们愉快的加个特判w
```cpp
if(heading=="SOUTH"){
	int fx=n-x;
	for(int i=1;i<=fx;++i){
		int nx=x+i;
		if(a[nx][y]=='X'){
			if(i==1)//走一步就是墙，说明车不可能在x,y
            	v[x][y]=false;
			return;
        }
			v[x][y]=false;
			v[nx][y]=true;
			dfs(nx,y,p+1);
		}
	}
}
```
过了样例，~~感觉自己真的很不错~~，提交试试

...然后又WA飞了qwq

只能下大样例...下下来也没什么思路，左思右想觉得自己很对啊，于是手玩了几个数据

```
5 5
X....
..X.X
.*..X
..X.X	
XXX.X
5
NORTH
EAST
SOUTH
WEST
NORTH

```
显然答案是
```
X*...
**X.X
....X
..X.X
XXX.X
```
而上面的代码跑出来了
```
X....
**X.X
....X
..X.X
XXX.X
```
嗯？

经过调试发现了上面代码的本质错误...
>**在一次搜索中，车开到了点x,y并将其赋值为true，但是在回溯后模拟其他情况时候，又将其改为了false**

orz我笨死了...

也就是这里的问题
```cpp
v[x][y]=false;
v[nx][y]=true;//车子从x,y开到了nx,y,但是如果我们之前的搜索证明了x,y本身可以抵达，回溯回来时候我们又把车开走了...
dfs(nx,y,p+1);//处理下一条命令

```
### 经过几分钟思考发现了一个结论：
**当且仅当执行完所有命令后，车的位置才是有效的，其他时刻都是中间量**

~~这不是显而易见吗~~

于是愉快的多加一个二维数组吧
```cpp
if(heading=="SOUTH"){
	int fx=n-x;
	for(int i=1;i<=fx;++i){
		int nx=x+i;
		if(a[nx][y]=='X'){
			if(i==1)
				v[x][y]=false;
			return;
		}
		v[x][y]=false;
		v[nx][y]=true;
		if(p==k)
			fin[nx][y]=true;//只有在此时才是真正的可以到达
		dfs(nx,y,t+1);
	}
}
```
输出时候要按照fin的指导输出...

测了一下，终于A了滚粗...

然后回头看看代码，好像发现v数组没用上啊，~~开始的时候思路实在是错的彻底~~

精简一下代码
```cpp
if(heading=="SOUTH"){
	int fx=n-x;
	for(int i=1;i<=fx;++i){
		int nx=x+i;
		if(a[nx][y]=='X')	return;
		if(p==k)			fin[nx][y]=true;
		dfs(nx,y,t+1);
	}
}
```
~~原来这么简单啊~~

总结一下，遇到题先看清题意，手玩下样例，打代码之前先模拟orzz

[由于版面问题，这里贴出完整的代码吧](https://www.luogu.org/paste/e6qmp8a0)



---

## 作者：巫妖王 (赞：3)

**每次往第k个方向一直走，直到碰到障碍或是出了边界，每走一步都算这个方向走过了，然后就调用过程，去走下个一方向。**

**然而这样只有30分，所以我们还需要剪枝。**

**f数组表示有没有尝试过，如果有，直接exit掉。**

代码如下
```cpp
#include<iostream>
using namespace std;
bool f[1005][55][55];
char c[55][55];
string s[1005];
int n,m,k,x,y,p,nh,nl,h,l;
int hh(string ss)
{
	if(ss=="NORTH") return 1;
	else if(ss=="SOUTH") return -1;
	else return 0;//竖直方向的判断； 
}
int ll(string ss)
{
	if(ss=="WEST") return 1;
	else if(ss=="EAST") return -1;
	else return 0;//水平方向的判断； 
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>c[i][j];
			if(c[i][j]=='*') f[0][i][j]=true;
		}
	cin>>k;
	for(int i=1;i<=k;i++) cin>>s[i];//读入； 
	for(int i=1;i<=k;i++)
	{
		x=hh(s[i]);
		y=ll(s[i]);
		if(x==0) p=m;
		if(y==0) p=n;
		for(int j=1;j<=n;j++)
		{
			for(int u=1;u<=m;u++)
			{
				if(c[j][u]!='X')
				{
					h=j;
					l=u;
					for(int o=1;o<=p;o++)
					{
						nh=h+o*x;
						nl=l+o*y;
						if((nh<1)||(nl<1)||(nh>n)||(nl>m)) break;
						if(c[nh][nl]=='X') break;
						if(f[i-1][nh][nl]) 
							f[i][h][l]=true;//搜索与剪枝； 
					}
				}	
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(f[k][i][j]) cout<<"*";
			else if(c[i][j]=='X') cout<<"X";
			else cout<<".";
		}
		cout<<endl;//输出 
	}
	return 0;
}
```
**Pascal代码如下**
```pascal
var n,m,i,j,k,x,y,u,o,h,l,nh,nl,p:longint;
    f:array[0..1005,0..105,0..105] of boolean;
    c:array[0..105,0..105] of char;
    s:array[0..1005] of string;
function hh(st:string):longint;
begin
  if st='NORTH' then exit(1) else
  if st='SOUTH' then exit(-1) else exit(0);//竖直方向的判断；
end;
function ll(st:string):longint;
begin
  if st='WEST' then exit(1) else
  if st='EAST' then exit(-1) else exit(0);//水平方向的判断；
end;
begin
  readln(n,m);
  for i:=1 to n do
  begin
    for j:=1 to m do
    begin
      read(c[i,j]);
      if (c[i,j]='*') then f[0,i,j]:=true;
    end;
    readln;
  end;
  readln(k);//读入； 
  for i:=1 to k do
    readln(s[i]);
  for i:=1 to k do
  begin
    x:=hh(s[i]);
    y:=ll(s[i]);
    if (x=0) then p:=m;
    if (y=0) then p:=n;
    for j:=1 to n do
      for u:=1 to m do
        if c[j,u]<>'X' then
        begin
          h:=j;
          l:=u;
          for o:=1 to p do
          begin
            nh:=h+o*x;
            nl:=l+o*y;
            if (nh<1) or (nl<1) or (nh>n) or (nl>m) then break;
            if (c[nh,nl]='X') then break;
            if (f[i-1,nh,nl]) then f[i,h,l]:=true;//搜索与剪枝；
          end;
        end;
  end;
  for i:=1 to n do
  begin
    for j:=1 to m do
      if f[k,i,j] then write('*') else
      if c[i,j]='X' then write('X') else write('.');
    writeln;//输出 
  end;
end.
```

---

## 作者：quanjun (赞：2)

题目链接：[https://www.luogu.com.cn/problem/P1189](https://www.luogu.com.cn/problem/P1189)  

题目大意：  
给你一个 $n \times m$ 的矩阵，其中有一些格子可以走，一些各自不能走，然后有一个点是起点。  
你走了 $q$ 次，每次走的方向（上下左右四个方向）是知道的，但是不知道的是你每次走了多少格（至少 $1$ 格），问最终你可能处在的位置。  
（注意我这里开的变量名和原题描述的变量名不一样，不过不影响理解）  

解题思路：  
这道题目是其实是一道模拟题。  
洛谷上面给的算法标签是“迭代加深”，但是其实这里只涉及“迭代”而没有“加深”。  
迭代加深——以我的理解——应该是：  
- 先定一个小目标，搜索的深度不超过 $1$ 层，看看能不能搜到答案；
- 如果不行，再把搜索的最大深度设为 $2$ ，看看能不能找到；
- 如果不行，再把搜索的最大深度设为 $3$ ，看看能不能找到；
- ……
- 直到设定目标为某一个深度 $D$ ，并且此时我能够找到答案则退出。

但是其实我们这里没有接触到搜索，而只是将问题分解成了 $q$ 步。  

所以我可以开一个二维数组 $a[i][j]$ 表示 $(i,j)$ 这个格子可以作为第 $a[i][j]$ 步的起点。  

很显然，一开始我可以这么设：  
- 起点对应的 $a[i][j]$ 为 $1$，
- 不能走的点对应的 $a[i][j]$ 为 $-1$，
- 剩下的点（非起点的能走的点）对应的 $a[i][j]$ 为 $0$

然后我们模拟每一步，我们从 $1$ 到 $q$ 来枚举第 $id$ 步，  
假设当前在第 $id$ 步，  
我们再枚举每一个点 $(i,j)$ ，如果 $a[i][j]$ 恰好等于 $id$ ，说明可以以 $(i,j)$ 为起点向对应的方向走。  
比如第 $id$ 步的指令是“NORTH”，那么是往北走，
则我们可以循环将 $a[i-1][j],a[i-2][j], ...$ 置为 $id+1$,知道渠道不能走的点或者超出地图边界。  

最后，我们可以通过判断 $a[i][j]$ 来还原出这个地图：  
- 如果 $a[i][j]==id+1$，则该点对应‘*’；
- 如果 $a[i][j]==-1$，则该点对应‘X’；
- 其他情况下，该点对应‘.’。

实现代码如下：  
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
int n, m, q, a[maxn][maxn]; // n,m表示行和列，q表示方向的数量
char maze[maxn][maxn], ch[11];
bool in_map(int x, int y) { // 判断(x,y)是否在地图中
    return x>=0 && x<n && y>=0 && y<m;
}
void go_north(int x, int y, int id) {   // 往北走并标记
    while (in_map(x, y) && maze[x][y] != 'X') {
        a[x][y] = id+1;
        x --;
    }
}
void go_south(int x, int y, int id) {   // 往南走并标记
    while (in_map(x, y) && maze[x][y] != 'X') {
        a[x][y] = id+1;
        x ++;
    }
}
void go_west(int x, int y, int id) {   // 往西走并标记
    while (in_map(x, y) && maze[x][y] != 'X') {
        a[x][y] = id+1;
        y --;
    }
}
void go_east(int x, int y, int id) {   // 往东走并标记
    while (in_map(x, y) && maze[x][y] != 'X') {
        a[x][y] = id+1;
        y ++;
    }
}
void handle(int id, char ch[]) {    // 第id步判断是什么指令然后往相应的方向走
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (a[i][j] == id) {
                if (ch[0] == 'N') go_north(i-1, j, id);
                else if (ch[0] == 'S') go_south(i+1, j, id);
                else if (ch[0] == 'W') go_west(i, j-1, id);
                else go_east(i, j+1, id);
            }
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i ++) cin >> maze[i];
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (maze[i][j] == 'X') a[i][j] = -1;
            else if (maze[i][j] == '*') a[i][j] = 1;
        }
    }
    cin >> q;
    for (int id = 1; id <= q; id ++) {
        cin >> ch;
        handle(id, ch);
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (maze[i][j] == 'X') putchar('X');
            else if (a[i][j] == q+1) putchar('*');
            else putchar('.');
        }
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：虚无教主 (赞：2)

# 无需深搜，直接模拟（精简版）
##### 优点：省时省空间
#### 先附上代码

```cpp
#include<cstdio>

char d[105][105];	//记录地图的char数组
int dt[105][105];	//坑点
int cnt=100;	//此法坑点1，下文解释
int n,m;

inline void src(int _,int __)	//下划线做变量名（萌新习惯就好）
{
    cnt++;	//
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) 
        {
            if(dt[i][j]==cnt-1)
            {
                int a=i,b=j;
                while(dt[a+_][b+__]!=0&&dt[a+_][b+__]!='X')
                    a+=_,b+=__,dt[a][b]=cnt;	//记录此次移动留下的足迹
            }
        }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",d[i]+1);	//正常输入

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) if(d[i][j]=='*') dt[i][j]=100;else dt[i][j]=d[i][j];	//此方重要预处理，坑点
    int T;scanf("%d",&T);
    while(T--)
    {
        char p[7];scanf("%s",p);
        if(p[0]=='N') src(-1,0);	//直接将方向加到函数形参上
        if(p[0]=='S') src(1,0);
        if(p[0]=='W') src(0,-1);
        if(p[0]=='E') src(0,1);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(dt[i][j]==cnt) d[i][j]='*';
            else if(dt[i][j]!='X') d[i][j]='.';		//因为懒，所以复杂化了一步，但是仔细看理解后可以直接与输出合并
    for(int i=1;i<=n;i++)
        printf("%s\n",d[i]+1);
    //n=int('X'); vscode玩家用于快速索引ascll码
}
```

#### 坑点（个人来说，也是比赛时可能忽略的）：char数据范围不足1000，在转移到int数组前直接search会导致cnt==‘X’……（你懂得，地图就没了），所以……对吧。
###### 核心思路就是模拟（与其他``模拟``题解大同小异），因为没有其他那么冗杂，所以自认为可以被借鉴一下。


---

## 作者：MorsLin (赞：2)

*先反省一波：我以后再也不用getchar()+scanf了(日常爆零)*

- 算是比较裸的搜索吧，在下用的算是DFS(严格说来应该是枚举)+在线处理吧，就是一边输入方向一边处理，用ans数组表示输入这一次方向后汽车可能在的位置，每次输入方向后将不能继续前进的ans删去，将可以前进的ans更新到新的位置
```cpp
void dfs(int x,int y,int dir,int l)
{
	if(map[x+fx[dir]][y+fy[dir]]) //如果不能继续前进，那么这个ans一定是错的，将它删去 
	{
		ans[x][y]=0;
		return ;
	}
	for(int i=1;;i++) //知道我为什么说它是枚举了吧 qwq 
	{
		int xx=x+fx[dir]*i,yy=y+fy[dir]*i;
		if(xx<1||xx>n||yy<1||yy>m||map[xx][yy]) //不断前进，并将这条路全置为ans(因为都符合条件) 
		  break;
		ans[xx][yy]=l+1; //防止重复查找，即防止刚置为ans后没有进行下一重循环，直接在这层循环再搜一次 
	}
	return ;
}
```

- 上面的dfs函数可以去掉不能继续前进的答案，加入新的答案，那么旧的答案该怎么办呢？ 我们可以在循环到ans后直接将它删去，因为对我们来说它已经没用了。接下来直接上代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
bool map[51][51]; //判断有没有障碍物
int ans[51][51];  //存答案
char mmp[51][51]; //存地图，不要在意变量名
int n,m,k;  
int fx[5]={0,0,0,1,-1}; //存方向，顺序是E、W、S、N
int fy[5]={0,1,-1,0,0};
void dfs(int x,int y,int dir,int l)
{
	if(map[x+fx[dir]][y+fy[dir]]) //如果不能继续前进，那么这个ans一定是错的，将它删去 
	{
		ans[x][y]=0;
		return ;
	}
	for(int i=1;;i++) //知道我为什么说它是枚举了吧 qwq 
	{
		int xx=x+fx[dir]*i,yy=y+fy[dir]*i;
		if(xx<1||xx>n||yy<1||yy>m||map[xx][yy]) //不断前进，并将这条路全置为ans(因为都符合条件) 
		  break;
		ans[xx][yy]=l+1; //防止重复查找，即刚置为ans后没有进行下一重循环，直接在这层循环再搜一次 
	}
	return ;
}
int main()
{
    输入+预处理地图
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
		    cin>>mmp[i][j];
		  	if(mmp[i][j]=='X')  map[i][j]=1;
		  	if(mmp[i][j]=='*')  ans[i][j]=1;
		}
	}  
	//在线查找
	scanf("%d",&k);
	for(int o=1;o<=k;o++)
	{
		char a[10]; scanf("%s",a);
		if(a[0]=='E')
		{
			for(int i=1;i<=n;i++) 
			  for(int j=1;j<=m;j++)
			  {
			  	if(ans[i][j]==o)
			  	{
			  		ans[i][j]=0; //将旧的答案删去，下同
			  		dfs(i,j,1,o); //用当层的答案去寻找新的答案
			  	}
			  }
		}
		if(a[0]=='W')
		{
			for(int i=1;i<=n;i++)
			  for(int j=1;j<=m;j++)
			  {
			  	if(ans[i][j]==o)
			  	{
			  		ans[i][j]=0;
			  		dfs(i,j,2,o);
			  	}
			  }
		}
		if(a[0]=='S')
		{
			for(int i=1;i<=n;i++)
			  for(int j=1;j<=m;j++)
			  {
			  	if(ans[i][j]==o)
			  	{
			  		ans[i][j]=0;
			  		dfs(i,j,3,o);
			  	}
			  }
		}
		if(a[0]=='N')
		{
			for(int i=1;i<=n;i++)
			  for(int j=1;j<=m;j++)
			  {
			  	if(ans[i][j]==o)
			  	{
			  		ans[i][j]=0;
			  		dfs(i,j,4,o);
			  	}
			  }
		}
	}
	//输出
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!ans[i][j]&&mmp[i][j]=='*'){cout<<'.'; continue;}
			if(!ans[i][j])
			  cout<<mmp[i][j];
			else
			  cout<<'*';
		}
		cout<<endl;
	}  
	
	
	return 0;
}
```

- 广告时间

在下的[洛谷博客](https://www.luogu.org/blog/34188/)和[博客园](http://www.cnblogs.com/wxl-Ezio/)

---

## 作者：Wider (赞：2)

#大模拟不必搜索

```cpp
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

char map[55][55];
string d;
int ans[55][55],x,y,r,c,n;

void work(int a){
    int yy,xx;
    if(d=="NORTH")
    {
        xx=x-1;
        while(xx>0 && map[xx][y]!='X' && ans[xx][y]<a)
        {
            ans[xx][y]=a;
            xx--;
        }
    }
    else if(d=="SOUTH")
    {
        xx=x+1;
        while(xx<=r && map[xx][y]!='X' && ans[xx][y]<a)
        {
            ans[xx][y]=a;
            xx++;
        }
    }
    else if(d=="WEST")
    {
        yy=y-1;
        while(yy>0 && map[x][yy]!='X' && ans[x][yy]<a)
        {
            ans[x][yy]=a;
            yy--;
        }
    }
    else if(d=="EAST")
    {
        yy=y+1;
        while(yy<=c && map[x][yy]!='X' && ans[x][yy]<a)
        {
            ans[x][yy]=a;
            yy++;
        }
    }
}//模拟

int main(){
    cin>>r>>c;
    for(int i=1;i<=r;i++)
    for(int j=1;j<=c;j++)
    {
        cin>>map[i][j];
        if(map[i][j]=='*')
        {
            x=i;
            y=j;
        }
    }
    cin>>n;
    memset(ans,-1,sizeof(ans));
    ans[x][y]=0;
    for(int k=1;k<=n;k++)
    {
        cin>>d;
        for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
        if(ans[i][j]==k-1)
        {
            x=i; y=j;//找到上一次的位置
            work(k);//模拟这一次可能到达的点
        }
    }
    for(int i=1;i<=r;i++){
    for(int j=1;j<=c;j++)
        if(ans[i][j]==n) cout<<'*';
        else if(map[i][j]=='X') cout<<'X';
        else cout<<'.';
        cout<<endl;
    }
    return 0;
}
```
**模拟的话最坏情况下时间O(n\*r\*c\*max(r,c))=O(1000\*50\*50\*50)=O(1.25\*10^8)，但实际上不可能出现这种情况时间远远小于O(10^8)，不会TLE**


**空间O(50\*50)**

 ![](https://cdn.luogu.com.cn/upload/pic/3204.png) 



---

## 作者：封禁用户 (赞：1)

## P1189
很明显，这是一道可以用DFS解决的题目，但是时间复杂度~~SPFA~~了，所以需要进行剪枝
#### 剪枝方法
这个数据不是太过分~~再过分点我也剪不了了~~需要开一个记录访问的数组，确定是否访问过

注意，这里的记录需要再记录坐标的同时记录step数，不同step到达一个点最后的解答树是不同的

#### 读入部分
###### 方法
读入时有个小技巧，不用对比单词，读入字符串以后只用对比首字母就可以了，毕竟都不同（N，S，W，E），判断可以单独开一个函数
###### 代码实现
```
int rd()
{
	char k[10];
	scanf("%s",k);//方向读入
	if(k[0]=='N')
	{
		return 0;
	}
	if(k[0]=='S')
	{
		return 1;
	}
	if(k[0]=='W')
	{
		return 2;
	}
	if(k[0]=='E')
	{
		return 3;
	}
}
/*
上:0
下:1
左:2
右:3 
*/
void input()
{
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%s",ma[i]+1);
	}
	scanf("%d",&num);
	for(i=1;i<=num;i++)
	{
		di[i]=rd();//存入行动数组
	}
	for(i=1;i<=n;i++)//寻找开始位置，并且初始为'.'
	{
		for(j=1;j<=m;j++)
		{
			if(ma[i][j]=='*')
			{
				sta=i;
				stb=j;
				ma[i][j]='.';
				return;
			}
		}
	}
}
```
#### dfs实现部分
###### 思路
同时向下传递坐标与step，若访问过，直接return。没访问过则打标记然后dfs。4个方向分开讨论。使用while寻找可以去的点，细节见代码~~语文不好，见谅~~
###### 代码实现
```
void dfs(int x,int y,int step)
{
	//printf("[%d][%d]\n",x,y);
	if(vi[x][y][step]==1)//剪枝，真的就这么点，30->AC
	{
		return;
	}else
	{
		vi[x][y][step]=1;
	}
	if(step==num+1)//如果到了终点，则将'*'打印
	{
		ma[x][y]='*';
		return;
	}
	int i;
	if(di[step]==0 && x>1 && ma[x-1][y]!='X')//确定能走，不知道有没有卡误解的点,要用不等于，因为有些可以走的点被车子位子'*'覆盖了
	{
		i=1;
		while(x-i>=1 && ma[x-i][y]!='X')//把所有能走的点都循环一遍
		{
			dfs(x-i,y,step+1);//向下循环，step一定别用++，不然后面有BUG
			i++;
		}
	}else if(di[step]==1 && x<n && ma[x+1][y]!='X')
	{
		i=1;
		while(x+i<=n && ma[x+i][y]!='X')
		{
			dfs(x+i,y,step+1);
			i++;
		}
	}else if(di[step]==2 && y>1 && ma[x][y-1]!='X')
	{
		i=1;
		while(y-i>=1 && ma[x][y-i]!='X')
		{
			dfs(x,y-i,step+1);
			i++;
		}
	}else if(di[step]==3 && y<m && ma[x][y+1]!='X')
	{
		i=1;
		while(y+i<=m && ma[x][y+i]!='X')
		{
			dfs(x,y+i,step+1);
			i++;
		}
	}
	return;
}
```
注意这个剪枝，是带有步数的，否则wonderful-ansder
#### 完全代码
```
#include "cstdio"
using namespace std;
const int N=1e3+7;
const int M=57;
int di[N];//记录移动
char ma[M][M];//记录图
bool vi[M][M][2007];//我不知道步数该开多大，随便开的，我太菜了
int n,m,num;
int sta,stb;
int rd()
{
	char k[10];
	scanf("%s",k);
	if(k[0]=='N')
	{
		return 0;
	}
	if(k[0]=='S')
	{
		return 1;
	}
	if(k[0]=='W')
	{
		return 2;
	}
	if(k[0]=='E')
	{
		return 3;
	}
}
/*
上:0
下:1
左:2
右:3 
*/
void input()
{
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%s",ma[i]+1);
	}
	scanf("%d",&num);
	for(i=1;i<=num;i++)
	{
		di[i]=rd();
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(ma[i][j]=='*')
			{
				sta=i;
				stb=j;
				ma[i][j]='.';
				return;
			}
		}
	}
}
void dfs(int x,int y,int step)
{
	//printf("[%d][%d]\n",x,y);
	if(vi[x][y][step]==1)
	{
		return;
	}else
	{
		vi[x][y][step]=1;
	}
	if(step==num+1)
	{
		ma[x][y]='*';
		return;
	}
	int i;
	if(di[step]==0 && x>1 && ma[x-1][y]!='X')
	{
		i=1;
		while(x-i>=1 && ma[x-i][y]!='X')
		{
			dfs(x-i,y,step+1);
			i++;
		}
	}else if(di[step]==1 && x<n && ma[x+1][y]!='X')
	{
		i=1;
		while(x+i<=n && ma[x+i][y]!='X')
		{
			dfs(x+i,y,step+1);
			i++;
		}
	}else if(di[step]==2 && y>1 && ma[x][y-1]!='X')
	{
		i=1;
		while(y-i>=1 && ma[x][y-i]!='X')
		{
			dfs(x,y-i,step+1);
			i++;
		}
	}else if(di[step]==3 && y<m && ma[x][y+1]!='X')
	{
		i=1;
		while(y+i<=m && ma[x][y+i]!='X')
		{
			dfs(x,y+i,step+1);
			i++;
		}
	}
	return;
}
int main()
{
	int i,j;
	input();
	dfs(sta,stb,1);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			printf("%c",ma[i][j]);//输出别随手加空格，不然会自闭的
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：CCCPKeay (赞：1)

BFS话这题还挺难的.(对于我这个蒟蒻来说)

我看好多dalao都是用DFS来写的我来一个BFS.大佬就看个乐吧.

## 思路:

由题意得知有N个方向,且小车的行动状态必须满足这N个方向才能在图中停下.那么BFS的思路就是我们用一个队列将满足这一个方向所有可以移动的点存储起来,但我们可以发现,当进行下一个方向更新时会把上一个方向覆盖,因此不能走完所有情况,那么我们需要另一个队列来存储当前所更新的点在由这个队列继续更新.

如果还有不懂的可以看代码注释应该还算详细吧.

#### 所以总结我们需要两个队列来存储所有可行的点.

~~献上冗长的BFS~~
## 代码:

```cpp
#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
const int N=60;
char Map[N][N];
bool vis[N][N][1000+100];
int n,m,op,flag,startx,starty;
struct Node//结构体不解释 
{
    int x,y;
};
queue<struct Node> keay;//此题核心:queue<struct Node>keay这个队列可以看作为中转站将que这个队列每次更新的数值存储起来 
queue<struct Node> que;//再由keay队列push回que再次更新从而达到遍历全图的目的 
void update()//update就是我们进行存储的操作 
{
    while(!keay.empty())
    {
        que.push(keay.front());//push回que队列 
        keay.pop();
    }
}
void bfs(int dir,int t)//bfs进行遍历 
{
    struct Node now;
    if(flag==0)//这个地方可以写在主函数(我这样写麻烦了些)flag 
    {          //为了防止每次从keay队列弹回que队列时多加入初始点所以我们用flag标记一下 
        now.x=startx;now.y=starty;
        que.push(now);
        flag++;
    }
    while(!que.empty())
    {
        now=que.front();//将que队列的每次更新的数值赋值给now来达到遍历下一个点 
        que.pop();//弹出队列 
        if(vis[now.x][now.y][t]) continue;//这个地方是坑点 (luogu竟然卡我这份代码)
        vis[now.x][now.y][t]=true;//这个地方是个优化,按照我们的遍历思路可能会出现重复走同一条路因此我们只用走一次(luogu数据坑点如果不这样写就会TLE) 
        for(int i=1;;i++)//因为题目没有明确小车的路线所以我们找出所有可以走的路因此无限循环直到不能走为止 
        {
            if(dir==1)//当方向为1的情况 
            {
                int xx=now.x-i;//因为向上走所以减i 
                int yy=now.y;//当然yy不会变 
                if(xx<1) break;//当超出边界不满足break 
                if(Map[xx][yy]=='X') break;//由题目得'X'不能走也break 
                if(t==op)//这里t计数当t==op时说明小车满足停车的条件 
                Map[xx][yy]='*';//那么将此点赋值为可停车的'*' 
                struct Node next;
                next.x=xx;next.y=yy;//进入下一个状态 
                keay.push(next);
            }
            if(dir==2)//接下来四个方向都和dir==1是一样的意思这里不做解释 
            {
                int xx=now.x;
                int yy=now.y-i;
                if(yy<1) break;
                if(Map[xx][yy]=='X') break;
                if(t==op) 
                Map[xx][yy]='*';
                struct Node next;
                next.x=xx;next.y=yy;
                keay.push(next);
            }
            if(dir==3)//...........
            {
                int xx=now.x;
                int yy=now.y+i;
                if(yy>m) break;
                if(Map[xx][yy]=='X') break;
                if(t==op)
                Map[xx][yy]='*';
                struct Node next;
                next.x=xx;next.y=yy;
                keay.push(next);
            }
            if(dir==4)//...........
            {
                int xx=now.x+i;
                int yy=now.y;
                if(xx>n) break;
                if(Map[xx][yy]=='X') break;
                if(t==op)
                Map[xx][yy]='*';
                struct Node next;
                next.x=xx;next.y=yy;
                keay.push(next);
            }
        }
    }
    return;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>Map[i][j];
            if(Map[i][j]=='*')
            {
                startx=i;//出发点坐标 
                starty=j;
                Map[i][j]='.';//因为出发点不能停车所以赋值为'.' 
            }
        }
    }
    cin>>op;//操作方向个数 
    for(int i=1;i<=op;i++) 
    {
        string s;
        int direct;
        cin>>s;
        if(s=="NORTH") direct=1;//打标记 
        if(s=="WEST") direct=2;//direct==1:NORTH,direct==2:WEST,direct==3:EAST,direct==4:SOUTH.
        if(s=="EAST") direct=3;
        if(s=="SOUTH") direct=4;
        bfs(direct,i);//bfs direct方向与操作的次数与
        if(i<op)//可有可无的优化 
        update();
    }
    for(int i=1;i<=n;i++)//输出 
    {
        for(int j=1;j<=m;j++)
        {
            cout<<Map[i][j];
        }
        cout<<endl;
    }
    return 0;
}
```
希望能对你们有所帮助
~~dalao就当看个热闹~~

---

## 作者：fetaler (赞：1)

嗯，一道比较水的省选，但这是我的第一个题解（A+B problem我交题解时锁了233），好了不多说了上代码。
这个题用来练dfs剪枝很不错（当然你玩模拟优先队列迭代BFS甚至一个FOR+MAIN()我也不管，反正我都会，而且听说这题有大佬用DP和图论做？），不剪30分（排除WA,RE,CE等情况）
```cpp
//没加注释的不用看了，是楼主调试的心血
#include<iostream>
#include<string.h>
using namespace std;
int lon,hig智能防抄;
char street[55][55];//[行][列] 
bool judge[55][55][1005];//怕溢出，剪枝
int n智能防抄;
string rule智能防抄;

short chance[1005];

void dfs(int hang,int lie,int num)//深搜函数
{
//	cout<<hang<<" "<<lie<<" "<<num<<" "<<chance[num]<<endl;
//	getchar();
	if(judge[hang][lie][num]==1) return;
	else judge[hang][lie][智能防抄num]=1;//剪枝
	if(num==n)
	{
		street[hang][lie]='*';//搜到末尾
		return;
	}
	if(chance[num]==0)//楼主英语不好，请把WHANG当做W-行，WLIE同理
	{
		for(int whang=hang;;)
		{
			whang--;
			if(street[whang][lie]=='X') 
			{
//				cout<<whang<<endl;
				break;
			}
			dfs(whang,lie,num+1);
		}
	}
	else if(chance[num]==1)
	{
		for(int whang=hang;智能防抄;)
		{
			whang++;
			if(street[whang][lie]=='X') 
			{
//				cout<<whang<<endl;
				break;
			}
			dfs(whang,lie,num+1);
		}
	}
	else if(chance[num]==2)
	{
		for(int wlie=lie;智能防抄;)
		{
			wlie--;
			if(street[hang][wlie]=='X')
			{
//				cout<<wlie<<endl;
				break;
			}
			dfs(hang,wlie,num+1);
		}
	}
	else
	{
		for(int wlie=lie;智能防抄;)
		{
			wlie++;
			if(street[hang][wlie]=='X')
			{
//				cout<<wlie<<endl;
				break;
			}
			dfs(hang,wlie,num+1);
		}
	}

}

int main(智能防抄)
{
	int q1,q2;
	memset(street,0,sizeof(street)智能防抄);//清数组
	memset(chance,0,sizeof(chance智能防抄));
	memset(judge,0,sizeof(judge)智能防抄);
	cin>>hig>>lon;
	for(int wa=1;wa<=hig;wa++)
	{
		for(int wb=1;wb<=lon;wb++)
		{
			cin>>street[wa][wb];
//			cout<<"("<<wa<<","<<wb<<")";
			if (street[wa][wb]=='*')
			{
				q1=wa;
				q2=wb;
				street[wa][wb]='.';//这里不懂请读题
//				cout<<q1<<" "<<q2<<endl;
			}
		}
//		cout<<wa<<" ";
	}
//	cout<<endl;
	for(int wa=0;wa<=lon+1;wa++)//预防措施（反正又不输出233）
	{
		street[0][wa]='X智能防抄';
		street[hig+1][wa]='智能防抄X';
	}
	for(int wb=0;wb<=hig+1;wb++)
	{
		street[wb][0]='X';
		street[wb][lon智能防抄+1]='X';
	}
	cin>>n;
	for(int wa=0;wa<n;wa++)
	{
		cin>>rule;
		if(rule[0]=='N智能防抄')chance[wa]=0;//北=0
		else if(rule[0]=='智能防抄S')chance[wa]=1;//南=1
		else if(rule[0]=='W智能防抄')chance[wa]=2;//西=2
		else if(rule[0]=='智能防抄E')chance[wa]=3;//东=3
//		cout<<chance[wa]<<endl智能防抄;
	}
	dfs(q1,q2,0);
	for(int wa=1;wa<=hig;wa++)
	{
		for(int wb=1;wb<=lon;wb++)
		{
			cout<<street[w智能防抄a][wb智能防抄];//输出
		}
		cout<<en智能防抄dl;
	}
}
最后再说一句，可能代码比较水，但是稳定高效。还有，请勿抄袭。
抄我代码必定编译错误233.
（模拟优先队列迭代BFS FOR+MAIN()可以关了）还有，这种题如果过不了的话先去试试剪枝八皇后（你要做猪国杀或PVZ我也不拦你）。

---

## 作者：OIer991215 (赞：1)

转换一下思维，

开两组队列，每一组存x、y坐标。

把第一条指令走到的点放入第一个队列；

把第二条指令走到的点放入第二个队列；

把第三条指令走到的点放入第一个队列；

把第四条指令走到的点放入第二个队列；

...........................................................

两个队列相互push，最后一条指令里走到的点就是答案


————————————————————————————————————————


在同一条指令里，一个点可能被多次访问，如何优化？

开一个col数组对每个点染色，染色的标号为当前的指令

两个队列相互push的时候，把新更新的点染上色，可以避免一个点被push两次


——————————————————————————————————————————


最后更新最后答案，那些点的col为指令数（这些点是最后一次被便利到）的点即为最后的中点

下面是整齐划一的代码：

————————————————————————————————————————





```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
queue <int> qx,qy,px,py;
int n,m,in,cnt,colo;
int mx,my,qqx,qqy;
char s[55][55];
char inf[1010][55];
int col[55][55];
bool flag[55][55];
bool check(int x,int y,int color)
{
    if(x>=1&&x<=n&&y>=1&&y<=m&&col[x][y]!=color&&s[x][y]!='X')
        return 1;
    return 0;
}
void work()
{
    while(cnt<=in)
    {
        cnt++,colo++;
        while(!qx.empty()&&cnt<=in)
        {
            int x=qx.front(),y=qy.front();
            qx.pop(),qy.pop();
            if(inf[cnt][1]=='W')    mx=0,my=-1;
            if(inf[cnt][1]=='E')    mx=0,my=1;
            if(inf[cnt][1]=='N')    mx=-1,my=0;
            if(inf[cnt][1]=='S')    mx=1,my=0;
            while( check(x+mx,y+my,colo) )
                x+=mx,y+=my,px.push(x),py.push(y),col[x][y]=colo;
        }
        cnt++,colo++;
        while(!px.empty()&&cnt<=in)
        {
            int x=px.front(),y=py.front();
            px.pop(),py.pop();
            if(inf[cnt][1]=='W')    mx=0,my=-1;
            if(inf[cnt][1]=='E')    mx=0,my=1;
            if(inf[cnt][1]=='N')    mx=-1,my=0;
            if(inf[cnt][1]=='S')    mx=1,my=0;
            while( check(x+mx,y+my,colo) )
                x+=mx,y+=my,qx.push(x),qy.push(y),col[x][y]=colo;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1; i<=n; i++)
        for(register int j=1; j<=m; j++)
        {
            cin>>s[i][j];
            if(s[i][j]=='*')
                qqx=i,qqy=j;
        }
    qx.push(qqx);
    qy.push(qqy);
    scanf("%d",&in);
    for(register int i=1; i<=in; i++)
        scanf("%s",inf[i]+1);
    work();
    for(register int i=1; i<=n; i++)
        for(register int j=1; j<=m; j++)
            if(col[i][j]==in)
                flag[i][j]=1;
    s[qqx][qqy]='.';
    for(register int i=1; i<=n; i++)
    {
        for(register int j=1; j<=m; j++)
            if(flag[i][j])
                printf("*");
            else
                printf("%c",s[i][j]);
        printf("\n");
    }
    return 0;
}
```
——————————————————————————

---

## 作者：tututu (赞：1)

来篇pascal的题解。

模拟大水题啊，一个数组保存当前可能位置，每次读入一个方向就在所有的可能位置中逐个枚举，向该方向移动，直到边界或者障碍，将路径上的所有位置标记为下一个状态的可能位置。

```cpp
var
  n,m,i,j,k,x,y,e:longint;
  a,b:array['A'..'Z'] of longint;
  f,f1:array[-1..102,-1..102] of boolean;
  s:array[-1..102] of string;
  t:char;
begin
  readln(n,m);
  for i:=1 to n do
    begin
      readln(s[i]);
      if pos('*',s[i])>0 then f[i,pos('*',s[i])]:=true;//f保存当前可能位置
    end;
  readln(e);
  a['N']:=-1;//为了方便处理，直接用数组存了，省得列四种情况。
  a['S']:=1;
  b['W']:=-1;
  b['E']:=1;
  for i:=1 to e do
    begin
      readln(t);//读入首字母就行了，压压内存。
      fillchar(f1,sizeof(f1),false);//临时储存
      for j:=1 to n do for k:=1 to m do if f[j,k] then//枚举当前的可能位置
        begin
          x:=j+a[t];//横坐标
          y:=k+b[t];//纵
          while (s[x,y]<>'X') and (x>=1) and (x<=n) and (y>=1) and (y<=m) do begin f1[x,y]:=true; x:=x+a[t]; y:=y+b[t]; end;//一路上全部记为true
        end;
      f:=f1;//迭代
    end;
  for i:=1 to n do
    begin
      for j:=1 to m do if s[i,j]='X' then write('X') else if f[i,j] then write('*') else write('.');//输出不多说。
      writeln;
    end;
end.
```

---

## 作者：依依 (赞：1)

解：对于答案来说，贡献就是到达那个点是第几次转向

然后进行BFS，但是会出现很多重复状态

然后我们就需要进行剪枝，

当到达一个点的状态有重复时，我们就不在对这个状态进行更新

详看代码。

[OK](http://www.cnblogs.com/adelalove/p/8876253.html)

---

## 作者：虚无教主 (赞：0)

# 无需深搜，直接广搜（及其复杂）
### 我看也没有广搜题解，所以再发一篇广搜
#### 广搜比较容易看懂，直接上代码
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>

using std::queue;		//一开始，我想，一步一步走，我写个模拟，然后想模拟好像很慢，队列优化一下，结果……变成广搜了

struct slu{int x,y;};

char dt[105][105];
int d[105][105];
int cnt;

queue<slu>q;	//结构体类型的队列

inline void bfs(int _,int __)
{
    cnt--;
    queue<slu>qt=q;
    while(!qt.empty())
    {
        slu o=q.front();q.pop(),qt.pop();
        while(d[o.x+_][o.y+__]!=0&&d[o.x+_][o.y+__]!='X') 
        {
            o.x+=_,o.y+=__;
            if(d[o.x][o.y]!=cnt) q.push({o.x,o.y}),d[o.x][o.y]=cnt; 
        }
    }
}

int main()
{
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",dt[i]+1);

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(dt[i][j]=='*') {q.push({i,j});break;}
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) if(dt[i][j]=='*') d[i][j]=100;else d[i][j]=dt[i][j];

    int T;scanf("%d",&T);
    while(T--)
    {
        char p[7];scanf("%s",p);
        if(p[0]=='N') bfs(-1,0);
        if(p[0]=='S') bfs(1,0);
        if(p[0]=='W') bfs(0,-1);
        if(p[0]=='E') bfs(0,1);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(d[i][j]==cnt) dt[i][j]='*';
            else if(d[i][j]!='X') dt[i][j]='.';
    for(int i=1;i<=n;i++)
        printf("%s\n",dt[i]+1);
}
```
想要更~~丰富~~快的模拟，移步[无需深搜，直接模拟（精简版）](https://www.luogu.org/blog/jiaozhu/solution-p1189)。

---

## 作者：wanyaxin (赞：0)

##  这道题，我想了好久~~还抄了一遍题解~~，最后，终于AC了
### 来讲一下我的思路吧：
1. 看到题目我首先想到了搜索（废话），但是应该深搜还是广搜呢？如果深搜，要依次搜索每一种情况，可能会炸，所以，还是广搜吧。
2. 如何广搜？首先，依次找每一个方向，把这个方向上可以走的所有位置都标记一下，记为方向i，（例如，第三个方向可到达的所有点都记为3）.搜索完后，标记为n的点就是'*'.
3. 但是这样会超时！所以要剪枝，当一个点的标记已经等于当前点的时候，原来的直接不要了，这样就不会超时。
### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[60][60];
int step[60][60];
char ha[4]={'N','s','W','E'};
int hx[4]={-1,1, 0,0};
int hy[4]={ 0,0,-1,1};
queue<int>qx;
queue<int>qy;
int mian()
{
	int r,c,n;
	int i,j;
	cin>>r>>c;
	for(i=1;i<=r;i++)
	{
		char s[60];
		scanf("%s",s+1);
		for(j=1;j<=c;j++)
		{
			if(s[j]=='*')
			{
				qx.push(i);
				qy.push(j);
				step[i][j]=0;
				a[i][j]='.';
			}
			else
			{
				a[i][j]=s[j];
			}
		}
	}
	cin>>n;
	for(i=1;i<=n;i++)
	{
		char s2[10];
		scanf("%s",s2);
		for(j=0;j<4;j++)
		{
			if(s2[0]==ha[j])
			{
				queue<int>qxx,qyy;
				while(!qx.empty())
				{
					int fx=qx.front();
					int fy=qy.front();
					qx.pop();
					qy.pop();
					if(step[fx][fy]==i)
					{
						continue;
					}
					int tx=fx;
					int ty=fy;
					while(1)
					{
						tx+=hx[j];
						ty+=hy[j];
						if(tx<1||ty<1||tx>r||ty>c||a[tx][ty]=='X')
						{
							break;
						}
						if(step[tx][ty]==i)
						{
							break;
						} 
						step[tx][ty]=i;
						qxx.push(tx);
						qyy.push(ty);
					}
				}
				while(!qxx.empty())
				{
					int t1=qxx.front(),t2=qyy.front();
					qx.push(t1);
					qy.push(t2);
					qxx.pop();
					qyy.pop();
				}
			}
		}
	}
	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			if(step[i][j]==n)
			{
				printf("*");
			}
			else
			{
				printf("%c",a[i][j]);
			}
		}
		printf("\n");
	}
}
```

---

## 作者：yjxyjx (赞：0)

这道题不知道什么时候出现在我的任务计划中的qwq，这两天看着任务计划一堆题很不爽~~虽然我不是太会~~，然后开始一题一题地写

***

这道题主要是**模拟**，

大致思路就是：每次先把方向输入进来，来一个方向就从**所有起点**开始，把从这个起点能扩展到的所有点都标记为"*"

如果又输入一个方向呢？

那么就把上一次的结果入队作为新起点，同时把这些点置为"*"

思路差不多是这样，下面是代码：

```cpp
#include<iostream>
#include<deque>
#include<string>

const int MaxR = 50 + 10;
const int MaxC = 50 + 10;
const int dx[] = {0, 0, 1, 0, -1};
const int dy[] = {0, 1, 0, -1, 0};

struct Node {
    int x, y, nowWay;//nowWay表示：现在的方向的编号是多少
};

std::deque< Node > Q;
char ans[MaxR][MaxC];
int R, C, num = 0;


inline void debug1() {
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            std::cerr << ans[i][j];
        }
        std::cerr << "\n";
    }
}

inline bool check(Node &_node) {
    return (_node.x < 1) || (_node.x > R) || (_node.y < 1) || (_node.y > C) || (ans[_node.x][_node.y] == 'X');
}

inline void Init() {
    Q.empty();
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            if (ans[i][j] == '*') {
                Q.push_back((Node) {i, j, 0});
                ans[i][j] = '.';
            }
        }
    }
}//这里一开始用的是队列中的元素，结果比较难写，也比较难维护，果断放弃

inline void Go(int way, int now) {
    
    do {
        Node start = Q.front(); Q.pop_front();
        Node next = start;
        next.x += dx[way]; next.y += dy[way];
        while (!check(next)) {
            ans[next.x][next.y] = '*';
            next.x += dx[way]; next.y += dy[way];
        }
    } while (!Q.empty());
    
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> R >> C;
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            std::cin >> ans[i][j];            
        }
    }
    // debug1();
    int N;
    std::cin >> N;
    for (int i = 1; i <= N; ++i) {
        std::string S;
        std::cin >> S;
        int way;
        if (S == "EAST") way = 1;
        if (S == "SOUTH") way = 2;
        if (S == "WEST") way = 3;
        if (S == "NORTH") way = 4;
        Init();//将所有起点入队作为新起点，同时把这些点置为"*"
        Go(way, i);//扩展现在所有能扩展的点/*debug1(); std::cerr << "------\n\n";*/
    }
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            std::cout << ans[i][j];
        }
        std::cout << "\n";
    }
    return 0;
}
```

---

## 作者：高冷 (赞：0)

我觉得这题只有普及难度。。。。

按照题目要求模拟就行了。

。。。但感觉需要迭代加深的思想











```cpp
#include <algorithm> //STL通用算法
#include <cmath> //定义数学函数
#include <cstdio> //定义输入/输出函数
#include <iostream> //数据流输入/输出
#include <cstring> //字符串处理
#include <string> //字符串类
#include <ctime> //定义关于时间的函数
#define itn int
#define fro for
#define ll long long
/*#include <bitset> //STL位集容器
#include <cstype> //字符处理
#include <cerrno> //定义错误码
#include <complex> //复数类
#include <clocale> //定义本地化函数
#include <cstdlib> //定义杂项函数及内存分配函数
#include <deque> //STL双端队列容器
#include <exception> //异常处理类
#include <fstream> //文件输入/输出
#include <functional> //STL定义运算函数(代替运算符)
#include <limits> //定义各种数据类型最值常量
#include <list> //STL线性列表容器
#include <map> //STL映射容器
#include <iomanip> //参数化输入/输出
#include <ios> //基本输入/输出支持
#include <iosfwd> //输入/输出系统使用的前置声明
#include <istream> //基本输入流
#include <ostream> //基本输出流
#include <queue> //STL队列容器
#include <set> //STL集合容器
#include <sstream> //基于字符串的流
#include <stack> //STL堆栈容器
#include <stdexcept> //标准异常类
#include <streambuf> //底层输入/输出支持
#include <utility> //STL通用模板类
#include <vector> //STL动态数组容器
#include <cwchar.h>//宽字符处理及输入/输出
#include <cwctype.h> //宽字符分类*/
using namespace std;
int ans;
int max(int x,int y){
    return x>y?x:y;
}
int min(int x,int y){
    return x<y?x:y;
}
int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
void write(int x){
    int buf[50];
    if (x<0) putchar('-'),x=-x;
    buf[0]=0;
    while (x) buf[++buf[0]]=x%10,x/=10;
    if (!buf[0]) buf[0]=1,buf[1]=0;
    while (buf[0]) putchar('0'+buf[buf[0]--]);
}
int a[64][64];
int main(){
    string s;
    int n=read(),m=read();
    for (int i=1;i<=n;i++)
    {
        cin>>s;
        for (int j=0;j<m;j++)
        {
            if (s[j]=='X') a[i][j+1]=-1;
            if (s[j]=='*') a[i][j+1]=1;
            if (s[j]=='.') a[i][j+1]=0;
        }
    }
    int T=read();
    for (int k=2;k<=T+1;k++)
    {
        cin>>s;
        if (s=="NORTH")
        {
            for (int j=1;j<=m;j++)
                for (int i=n-1;i>=1;i--)//要从反方向开始改
                    if (a[i][j]!=-1)
                    {
                        if (a[i+1][j]==k-1||a[i+1][j]==k) a[i][j]=k;
                    }
                    //else break;
        }
        if (s=="SOUTH")
        {
            for (int j=1;j<=m;j++)
                for (int i=2;i<=n;i++)
                    if (a[i][j]!=-1)
                    {
                        if (a[i-1][j]==k-1||a[i-1][j]==k) a[i][j]=k;
                    }
                    //else break;
        }
        if (s=="WEST")
        {
            for (int i=1;i<=n;i++)
                for (int j=m-1;j>=1;j--)
                    if (a[i][j]!=-1)
                    {
                        if (a[i][j+1]==k-1||a[i][j+1]==k) a[i][j]=k;
                    }
                    //else break;
        }
        if (s=="EAST")
        {
            for (int i=1;i<=n;i++)
                for (int j=2;j<=m;j++)
                    if (a[i][j]!=-1)
                    {
                        if (a[i][j-1]==k-1||a[i][j-1]==k) a[i][j]=k;
                    }
                    //else break;
        }
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            if (a[i][j]==-1) printf("X");
            else
            if (a[i][j]==T+1) printf("*");
            else
            printf(".");
        }
        printf("\n");
    }
    return 0;
}

```

---

## 作者：hahalidaxin2 (赞：0)

添加一个BFS的题解：较dfs略慢。

以 x,y,d 为状态，xy为坐标，d为当前的走向。宽搜状态即可 。


```cpp

#include<iostream>
#include<queue>
using namespace std;

const int maxn = 50+5;
const char* dirs= "NESW";
struct Node{
    int x,y,d;
};
int G[maxn][maxn];
int vis[maxn][maxn][1010];
int ans[maxn][maxn];
int op[1010];
int R,C,n,sx,sy;

inline bool inside(int x,int y) {
    return x>=0 && x<R && y>=0 && y<C && !G[x][y];
}
void bfs() {
    queue<Node> q;
    q.push((Node){sx,sy,0});
    while(!q.empty()) 
    {
        Node u=q.front(); q.pop();
        int x=u.x,y=u.y,d=u.d,opt=op[d];
        if(d==n) { ans[x][y]=1; continue; }
        int dx=0,dy=0;
        if(opt==0)dx=-1; if(opt==1)dy=1; if(opt==2)dx=1; if(opt==3)dy=-1;
        x+=dx; y+=dy;
        while(inside(x,y)) {
            if(!vis[x][y][d+1]) {
                vis[x][y][d+1]=1;
                q.push((Node){x,y,d+1});
            }
            x+=dx; y+=dy;
        }
    }
}

void print_ans() {
    for(int i=0;i<R;i++)
    {
      for(int j=0;j<C;j++)
        if(G[i][j]==1) cout<<'X';
        else 
          if(ans[i][j]) cout<<'*';
        else 
          cout<<'.';
      cout<<"\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin>>R>>C;
    char c;
    for(int i=0;i<R;i++)
      for(int j=0;j<C;j++)
      {
            cin>>c;
            if(c=='*') sx=i,sy=j;
            else 
              if(c=='X') G[i][j]=1;
      }
    cin>>n;
    string s;
    for(int i=0;i<n;i++) {
        cin>>s;
        op[i]=strchr(dirs,s[0])-dirs;
    }
    
    bfs();
    print_ans();
    
    return 0;
}

```

---

