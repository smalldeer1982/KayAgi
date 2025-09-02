# New Year and Buggy Bot

## 题目描述

Bob programmed a robot to navigate through a 2d maze.

The maze has some obstacles. Empty cells are denoted by the character '.', where obstacles are denoted by '\#'.

There is a single robot in the maze. Its start position is denoted with the character 'S'. This position has no obstacle in it. There is also a single exit in the maze. Its position is denoted with the character 'E'. This position has no obstacle in it.

The robot can only move up, left, right, or down.

When Bob programmed the robot, he wrote down a string of digits consisting of the digits 0 to 3, inclusive. He intended for each digit to correspond to a distinct direction, and the robot would follow the directions in order to reach the exit. Unfortunately, he forgot to actually assign the directions to digits.

The robot will choose some random mapping of digits to distinct directions. The robot will map distinct digits to distinct directions. The robot will then follow the instructions according to the given string in order and chosen mapping. If an instruction would lead the robot to go off the edge of the maze or hit an obstacle, the robot will crash and break down. If the robot reaches the exit at any point, then the robot will stop following any further instructions.

Bob is having trouble debugging his robot, so he would like to determine the number of mappings of digits to directions that would lead the robot to the exit.

## 说明/提示

For the first sample, the only valid mapping is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908B/4c40549367cb1d718a2322ebe6b5a9600149483b.png), where $ D $ is down, $ L $ is left, $ U $ is up, $ R $ is right.

## 样例 #1

### 输入

```
5 6
.....#
S....#
.#....
.#....
...E..
333300012
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 6
......
......
..SE..
......
......
......
01232123212302123021
```

### 输出

```
14
```

## 样例 #3

### 输入

```
5 3
...
.S.
###
.E.
...
3
```

### 输出

```
0
```

# 题解

## 作者：LYR_ (赞：2)

#### 这题不难，用dfs枚举上下左右与0，1，2，3就可以搞定。
~~自认为这个方法比较简单~~

Code(C++):
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=60;
const int S=110;
int dx[5]={0 , -1 ,  1 ,  0}; //行
int dy[5]={1 ,  0 ,  0 , -1}; //列
//      {右，上 ，下 ，左}
int s[S],t[5];
char a[N][N];
int n,m;
int sx,sy,ex,ey;//开始与结束的坐标
int main() {
	int ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cin>>a[i][j];
			if(a[i][j]=='S') {
				sx=i;sy=j;
			}
			else if(a[i][j]=='E') {//这里可以删去，后面if(x==ex && y==ex) 改为 if(a[x][y]=='E')
				ex=i;ey=j;
			} 
		}
	}
	string st;
	cin>>st;
	int l=st.size();
	for(int i=1;i<=l;i++) s[i]=st[i-1]-'0';//将st换为数组
	for(int i=0;i<4;i++) t[i]=i;
	int x,y;
	do {
		x=sx;y=sy;//这边别忘了
		for(int i=1;i<=l;i++) {
			if(x>n || y>m || x<1 || y<1) break; 
			x+=dx[t[s[i]]];
			y+=dy[t[s[i]]];
			if(x==ex && y==ey) {
				ans++;
				break ;
			}
			if(a[x][y]=='#') break;//撞墙
		}
	}while(next_permutation(t,t+4));//全排列函数
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：RagnaLP (赞：1)

这是一道新奇的图论题，不是特别难，重点是列举所有对照情况，只需要疯狂循环循环循环，每种情况都走一遍看能不能到就可以了。中间一定要将输入的数转换成对应方向的变化。

PS：**注意审题！！！**这个机器人只要到了终点**就不会管后面**的步骤了！！！很坑


```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int step[105]={0},t=0,n,m;//step记录操作,t为操作个数 
int ex,ey,sx,sy,ans=0;//终点坐标，起点坐标 
char map[55][55]={0};//记地图 
int change[4][2]={{-1,0},{1,0},{0,-1},{0,1}};//变化的方向：UP,DOWN,LEFT,RIGHT 
void Init(){
	scanf("%d%d",&n,&m);
	char c=getchar();
	for(int i=0;i<n;i++){//列 
		while(c!='.'&&c!='#'&&c!='S'&&c!='E')c=getchar();//getchar要排除\n的情况 
		for(int j=0;j<m;j++){//行 
			map[i][j]=c;
			//记录起点和终点 
			if(c=='S')
				sx=i,sy=j;
			else if(c=='E')
				ex=i,ey=j; 
			c=getchar();//下一个 
		}
	}
	//读步骤 
	while(c>'3'||c<'0') c=getchar();
	while(c>='0'&&c<='3'){
		step[t]=c-'0';//字符转int 
		c=getchar();
		t++; 
	}
}

void walk(int x,int y,int z,int w){//0,1,2,3分别对应的方向 
	int r=sx,c=sy,a[4]={x,y,z,w};//a为输入的步的实际方向 
	for(int i=0;i<t;i++){
		r=r+change[a[step[i]]][0];//a[step[i]]表示对应的方向 
		c=c+change[a[step[i]]][1];
		if(r<0||c<0||r>=n||c>=m||map[r][c]=='#')//超出边界或者是有阻挡就return 
			return;
		if(r==ex&&c==ey){//遇到终点 
			ans++;
			return;
		}
	}
	return;
}
void solve(){
	//i,j,k,l为‘0’，‘1’，‘2’，‘3’代表的方向
	//i,j,k,l的值：0表示UP，1表示DOWN，2表示LEFT，3表示RIGHT 
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(i==j) continue; 
			for(int k=0;k<4;k++){
				if(k==j||k==i) continue;
				for(int l=0;l<4;l++){
					if(i==l||k==l||j==l) continue;//保证i,j,k,l不相等 
					walk(i,j,k,l);
				}
			}
		}
	} 
}
int main(){
	Init();
	solve();
	printf("%d",ans);
	return 0;
}
```

---

## 作者：WaterSky (赞：0)

# [ CF908B New Year and Buggy Bot。](https://www.luogu.com.cn/problem/CF908B)

中秋快乐！

## 思路。
深度遍历搜索。

搜索四个数字每一个数字的所有可能性，然后再跑一遍，看看能不能**经过**终点，如果能够**经过**终点就说明是一种方法，答案增加，如果路径上撞墙或者出界那么就说明这个方法不可行，直接退出。

细一点讲，用一个二维数组记录每一个方向横纵所要加的值，然后再开两个数组分别记录是否有这个方向以及这个数字确定的方向，如果没有确定方向则为 $-1$。

```
#include<bits/stdc++.h>
using namespace std;
long long n,m,X1,Y1,ans;
long long walk[15][2]={{0,1},{0,-1},{1,0},{-1,0}};
long long A[105];
char a[1005][1005];
string s;
bool bj[1005];
void dfs(long long x)//深度遍历搜索。
{
	if(x==4)
	{
		long long X2=X1,Y2=Y1;
		for(int i=0;i<s.size();i++)
		{
			X2+=walk[A[s[i]-'0']][0],Y2+=walk[A[s[i]-'0']][1];//加上方向的对应横纵数值。
			if(a[X2][Y2]=='#' || X2<1 || X2>n || Y2<1 || Y2>m) return;//判断是否不可行。
			if(a[X2][Y2]=='E') {ans++;return;}//如果经过那么答案增加。
		}
	}
	else
		for(int j=0;j<4;j++)
			if(bj[j]==0)//如果这个方向没有被选过。
				bj[j]=1,A[x]=j,dfs(x+1),A[x]=-1,bj[j]=0;//遍历，之后记得清空。
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			{
				cin>>a[i][j];
				if(a[i][j]=='S') X1=i,Y1=j;//找到起点值。
			}
	cin>>s;
	for(int i=0;i<4;i++) A[i]=-1;//将所有设为-1。
	dfs(0);//开始搜索。
	cout<<ans;//输出答案。
	return 0;
}
```

---

## 作者：A_grass_block (赞：0)

### 题目：
这道题目其实就是一个搜索，题目不难，枚举出上下左右，就好了，可以说是一道广搜。

广搜：判断出有几条出路。

深搜：判断有没有出路。

这里可以使用全排列函数，代码中已标注。

### 代码：
```
#include<bits/stdc++.h>
using namespace std;

int dx[5]={0,-1,1,0};//各个方向
int dy[5]={1,0,0,-1};
int s[110],t[5];
char a[65][65];      //表
int main() 
{
	
	int n,m;
	int sum=0;        //计数器
	int sx,sy,ex,ey;  //开始、结束的坐标
	cin>>n>>m;
	for(int i=1;i<=n;i++) 
	{
		for(int j=1;j<=m;j++) 
		{
			cin>>a[i][j];//输入表
			if(a[i][j]=='S') 
			{
				sx=i;
				sy=j;
			}
			else if(a[i][j]=='E') 
			{
				ex=i;
				ey=j;
			} 
		}
	}
	string st;
	cin>>st;
	int l=st.size();
	for(int i=1;i<=l;i++) 
	{
		s[i]=st[i-1]-'0';//将st换为数组
	}
	for(int i=0;i<4;i++) 
	{
		t[i]=i;
	}
	int x,y;
	do //是 do whlie   不是 while
	{
		x=sx;//进行重置
		y=sy;
		for(int i=1;i<=l;i++) 
		{
			if(x>n||y>m||x<1||y<1) //判断是否越界
			{
				break;
			}
			x+=dx[t[s[i]]];
			y+=dy[t[s[i]]];
			if(x==ex&&y==ey) 
			{
				sum++;
				break;
			}
			if(a[x][y]=='#')//边界(墙)
			{
				break;
			} 
		}
	}while(next_permutation(t,t+4)); //全排列函数
	cout<<sum<<endl;
	
	return 0;
}
```

---

## 作者：Helium_Ship (赞：0)

先把起点的位置记录下来，用一个数组枚举每个数字代表的方向（这里我们可以运用到STL库中生成全排列的函数），最后利用广度优先搜索判断是否方案可行即可。

这里有一个坑点：每个操作并不一定需要用完。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sx,sy,sum,t[5];
int fx[5]={1,-1,0,0};
int fy[5]={0,0,1,-1};
char c[61][61];
string str;
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			cin>>c[i][j];
			if (c[i][j]=='S')
				sx=i,sy=j;
		}
	cin>>str;
	for (int i=0;i<=3;i++)
		t[i]=i;
	do
	{
		bool flag=0;
		int nx=sx,ny=sy;
		for (int i=0;i<str.size();i++)
		{
			nx=nx+fx[t[str[i]-'0']];
			ny=ny+fy[t[str[i]-'0']];
			if (nx>=1&&nx<=n&&ny>=1&&ny<=m)
			{
				if (c[nx][ny]=='E')
				{
					flag=1;
					break;
				}
				if (c[nx][ny]=='#')
					break;
			}
			else break;
		}
		sum+=flag;
			
	}while(next_permutation(t,t+4));//此处为全排列生成函数
	cout<<sum;
	return 0;
}
```


---

## 作者：codeLJH114514 (赞：0)

[Problem](https://www.luogu.com.cn/problem/CF908B)

# Problem

给定一个 $N \times M$ 的字符矩阵，每一个字符 $\in \{\texttt{S},\texttt{E},\texttt{\#},\texttt{.}\}$，其中 $\texttt{S}$ 表示起点，$\texttt{E}$ 表示终点，$\texttt{\#}$ 表示障碍物。

机器人会按照一段给定的操作序列进行移动，操作序列的每种数都对应一个方向（一共 $4$ 种，`0123`）。你需要回答，这些数字代表那些方向能让机器人从起点走到终点，输出个数。

数据范围：$2 \le N,M \le 50$，$1 \le S \le 100$，$S$ 表示操作序列长度。

# Analysis

直接暴力枚举每一种数对应的方向即可，模拟判断是否合法。

一共只会判断 $4 \times 3 \times 2 = 24$ 次，每次的时间复杂度为 $\mathcal{O}(S)$，总时间复杂度为 $\mathcal{O}(N \times M + S)$。

枚举可以用 `STL:<algorithm>` 的 `std::next_permutation` 函数。

# Code

```cpp
#include <iostream>
#include <algorithm>
#define maxn 64
int N, M;
std::string S;
char a[maxn][maxn];
int act[4], Answer;
int Sx, Sy, Ex, Ey;
struct Direction {
    int dx, dy;
} d[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int CheckAnswer();
int main() {
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) {
            std::cin >> a[i][j];
            if (a[i][j] == 'S')
                Sx = i, Sy = j;
            if (a[i][j] == 'E')
                Ex = i, Ey = j;
        }
    std::cin >> S;
    act[0] = 0, act[1] = 1, act[2] = 2, act[3] = 3;
    do {
        Answer += CheckAnswer();
    } while (std::next_permutation(act, act + 4));
    std::cout << Answer << "\n";
    return 0;
}
int CheckAnswer() {
    int x = Sx, y = Sy;
    for (int i = 0; i < S.size(); i++) {
        x += d[act[S[i] - '0']].dx,
        y += d[act[S[i] - '0']].dy;
        if (not (1 <= x and x <= N and 1 <= y and y <= M))
            return 0;
        if (a[x][y] == '#')
            return 0;
        if (x == Ex and y == Ey)
            return 1;
    }
    return 0;
}
```

---

## 作者：kster__ (赞：0)

~~啊这道题真的一言难尽，开始提交编译失败了好几次，又看不太懂提示信息，最后灵光一闪，把next数组名字改掉才成功了~~

言归正传，这题不是特别难，把所有可能的情况用四个for循环嵌套枚举出来，再把每条路走一遍就可以了

```cpp
#include <bits/stdc++.h>
using namespace std;

char mp[100][100];		//用来存储地图信息，包括障碍和起点终点 
string dir;		//用来保存给机器人的指令 
int ne[4][2]={ {0,1}, {0,-1}, {1,0}, {-1,0} };		//上下左右对应的x、y需要加上的值 
int sx,sy,ssx,ssy,tx,ty,n,m;
long long res=0;	//可走路径的总数 

int main()
{
	cin>>n>>m;		//输入地图大小 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>mp[i][j];		//输入地图 
			if(mp[i][j] == 'S')		//用sx，sy存储起点数据 
			{
				sx=i;
				sy=j;
			}
		}
		getchar();
	}
	
	cin>>dir;		//输入指令 

	for(int a=0;a<4;a++)		//用abcd分别代替一个方向的指令 
	{
		for(int b=0;b<4;b++)
		{
			if(b==a) continue;
			for(int c=0;c<4;c++)
			{
				if(c==a || c==b) continue;
				for(int d=0;d<4;d++)
				{	
					if(d==a || d==b || d==c) continue;		//三个if语句使abcd代替的方向不重复 
					
					ssx=sx;
					ssy=sy;		//初始化，每进行一组新数据的测试都要存储一次新的起点数值 
					
					for(int i=0;i<dir.length();i++)		//一步一步的跟着指令走 
					{
						if(dir[i] == '0')		//每个数字指令都指定一个字母来代替，便于枚举所有的可能方向 
						{
							tx=ssx+ne[a][0];
							ty=ssy+ne[a][1];		//用tx，ty临时存储下一步到达的坐标 
						}
						
						if(dir[i] == '1')
						{
							tx=ssx+ne[b][0];
							ty=ssy+ne[b][1];
						}
						
						if(dir[i] == '2')
						{
							tx=ssx+ne[c][0];
							ty=ssy+ne[c][1];
						}
						
						if(dir[i] == '3')
						{
							tx=ssx+ne[d][0];
							ty=ssy+ne[d][1];
						}
						
						if(mp[tx][ty]=='E')		//如果下一步就是终点，总路径数加一，直接跳出循环，不用管剩余的指令是否还未进行 
						{
							res++;
							break;
						}
						
						if(tx<0 || ty<0 || tx>=n || ty>=m || mp[tx][ty]=='#') break;	
						//如果下一步超出了地图范围或者撞上了障碍物说明这种方向的搭配行不通了，都不能再继续走下去，跳出循环，进行新组合的判断 
						
						ssx=tx;		 
						ssy=ty;
						continue;	//如果没有被上面的判定拦下，说明下一步既可以继续走也尚未到达终点，更新ssx，ssy的值，进行下一步指令 
					} 
				}
			}
		}
	}
	
	cout<<res<<endl;		//输出总路径数 
	
	return 0;
} 
```


---

