# Phillip and Trains

## 题目描述

The mobile application store has a new game called "Subway Roller".

The protagonist of the game Philip is located in one end of the tunnel and wants to get out of the other one. The tunnel is a rectangular field consisting of three rows and $ n $ columns. At the beginning of the game the hero is in some cell of the leftmost column. Some number of trains rides towards the hero. Each train consists of two or more neighbouring cells in some row of the field.

All trains are moving from right to left at a speed of two cells per second, and the hero runs from left to right at the speed of one cell per second. For simplicity, the game is implemented so that the hero and the trains move in turns. First, the hero moves one cell to the right, then one square up or down, or stays idle. Then all the trains move twice simultaneously one cell to the left. Thus, in one move, Philip definitely makes a move to the right and can move up or down. If at any point, Philip is in the same cell with a train, he loses. If the train reaches the left column, it continues to move as before, leaving the tunnel.

Your task is to answer the question whether there is a sequence of movements of Philip, such that he would be able to get to the rightmost column.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF585B/309f950d64c5a7d55f4952aae670b86363abc76b.png)

## 说明/提示

In the first set of the input of the first sample Philip must first go forward and go down to the third row of the field, then go only forward, then go forward and climb to the second row, go forward again and go up to the first row. After that way no train blocks Philip's path, so he can go straight to the end of the tunnel.

Note that in this problem the challenges are restricted to tests that contain only one testset.

## 样例 #1

### 输入

```
2
16 4
...AAAAA........
s.BBB......CCCCC
........DDDDD...
16 4
...AAAAA........
s.BBB....CCCCC..
.......DDDDD....
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
2
10 4
s.ZZ......
.....AAABB
.YYYYYY...
10 4
s.ZZ......
....AAAABB
.YYYYYY...
```

### 输出

```
YES
NO
```

# 题解

## 作者：lraM41 (赞：5)

一道挺水的搜索题。



------------
## 思路：DFS。

如果按题意的火车移动会很麻烦，~~根据相对论~~我们可以将火车向左移动步改为这个人向右移动，加上之前的向前走一步就是向右走三步。
### 方法:每次在上下以及本行进行搜索，不需要加什么剪枝，再拿一个数组进行标记，如果前方有火车则不能走了，达到终点进行标记。每次枚举不越界的上本下行，判断该行的前面三格是否有火车，若前面三格都没有火车就从这行继续搜索。



------------

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f,n,k,t,i,j,a[4][105],fx,vis[4][105];
char b;
void dfs(int x,int y)
{
   if(y>=n){//达到终点
      f=1;
      return;
   }
   if(vis[x][y]||f)return;//已走过或已经到了。
   vis[x][y]=1;//打标记。
   if(a[x][y+1])return;//如果前面有火车，结束。
   for(int i=x-1;i<=x+1;i++)//三行。
   {
      if(i<1||i>3)continue;//越界了。
      if(!a[i][y+1]&&!a[i][y+2]&&!a[i][y+3])dfs(i,y+3);//前面没火车。
   }
}
int main()
{
   cin>>t;
   while(t--)
   {
      f=0;
      memset(a,0,sizeof a);
      memset(vis,0,sizeof vis);//初始化。
      cin>>n>>i;
      for(i=1;i<=3;i++)
         for(j=1;j<=n;j++)
         {
            cin>>b;//输入。
            if(b!='.'){
               if(b=='s')fx=i;//起始位置。
               else a[i][j]=1;
            }
            else a[i][j]=0;
            vis[i][j]=0; //有点多余，请不要在意。
         }
      dfs(fx,1);//搜索。
      if(f)puts("YES");//输出。
      else puts("NO");
   }
	return 0;//完结撒花！
}
```


---

## 作者：installb (赞：4)

## 首先可以看出这是一道搜索题（我用了bfs）

首先我们可以把所有火车往左 视为人物往右 因为所有的火车都是同一速度同时动的

这样就可以视为一回合内人物先往右走一格 再换行或不动 再往前走一格 然后再往前走一格 往前走的两格要**分开判断**
```cpp
s.A.
..B.
..C.
```
如果遇到这种直接+1不换行+2就错了

如果人物走到第n列且当前位置不是障碍物 或到达>n的列 就直接**清空队列退出搜索**

此外 不难发现k其实是废的 只要把所有大写字母所在格全部设置为障碍物就可以了

具体搜索过程见代码

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct node {
	int lin; //lin记录人物在第几列
	int col; //col记录人物在第几行
} aa,bb; //不要在意变量名...
queue <node> q;
int t,n,k;
char c;
int mp[1005][5] = {0};
int vis[1005][5] = {0}; 
int dirx[3] = {-1,0,1}; //从上走，不动，往上走 
int sx,sy,tx,ty,flag;
int main() {
	cin >> t;
	while(t --) {
		memset(mp,0,sizeof(mp));
		memset(vis,0,sizeof(vis));
		flag = 0; //flag用来存是否能达到终点 多组数据记得把该清零的都清零 
		scanf("%d %d",&n,&k);
		for(int i = 1; i <= 3; i ++) {
			for(int j = 1; j <= n; j ++) {
				cin >> c;
				if(c == 's') {
					sx = j;
					sy = i; // 起始位置 
				}
				if(c >= 'A' && c <= 'Z') {
					mp[j][i] = 1; //标记火车 
				}
			}
		}
		aa.lin = sx;
		aa.col = sy;
		q.push(aa);
		while(!q.empty()) {
			aa = q.front();
			if(aa.lin >= n) { //当前所在行在最右边或更靠右即退出 
				flag = 1;
				while(!q.empty()) q.pop(); //一定要把队列清空再退出！ 
				break;
			}
			if(mp[aa.lin + 1][aa.col] == 1 || mp[aa.lin][aa.col] == 1) {
				q.pop();
				continue;
			} //如果前方一格是障碍物就不需要再判断下面的了 因为是先前走一格再上下走（换行） 
			for(int i = 0; i < 3; i ++) {
				tx = aa.lin + 1;
				ty = aa.col + dirx[i]; //换行
				if(ty < 1 || ty > 3) continue;
				if(mp[tx][ty] == 1) continue;
				tx = aa.lin + 2; //往前走一格 
				if(mp[tx][ty] == 1) continue; 
				tx = aa.lin + 3; //往前走两格 这里还是要判 会遇到火车只有一格长 
				if(mp[tx][ty] == 1) continue;  
				if(vis[tx][ty] == 1) continue; //虽然每一步都要判断障碍物但是vis只有走到底才判断和标记 
				vis[tx][ty] = 1;
				bb.lin = tx;
				bb.col = ty;
				q.push(bb); //只要碰到障碍物就continue 一路上都没障碍就入队 
			}
			q.pop();
		}
		if(flag == 1) printf("YES\n");
		if(flag == 0) printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Prurite (赞：2)

## 思路
容易想到通过搜索（事实上深搜，广搜都行）来判断从起点出发是否能到达终点，如果搜索的过程中遍历到了第 $n+1$ 列就可以，否则不能。

这题有几个小技巧和需要注意的地方：
1. 根据运动与静止的相对性，火车向左走两格可以看做人向右走两格，这样可以有效降低代码复杂度
2. 注意剪枝（用 vis 数组标记访问过的点，如果访问过就不再访问；只要找到一条合法路径就直接 return ），否则会 TLE 。

具体实现可以看代码。

## 代码
```cpp
#include <cstdio>
using std::scanf;
using std::printf;
// 使用命名空间防止重名冲突，不了解的同学可以直接使用 using namespace std;

const int MAXL=100+10;
int len;
bool can_arrive;
// 记录是否能到达
bool map[5][MAXL];
// 记录地图，1表示可以走，0表示不能走
bool vis[5][MAXL];
// 记录是否被访问过，1表示访问过了

inline void reset( );
inline void dfs ( int nowx, int nowy );

int main( )
{
	int T;
	scanf( "%d", &T );
	while ( T-- )
	{
		reset( ); // 重置数组
		int train;
		scanf( "%d %d", &len, &train );
		int sx, sy;
		for ( int i=1; i<=3; i++ )
		{
			char line[MAXL];
			scanf( "%s", line );
			for ( int j=0; j<len; j++ )
				if ( line[j]>='A' && line[j]<='Z' )	
					map[i][j]=0;
				else if ( line[j]=='s' )
					sx=i, sy=j;
		} //读入
		dfs( sx, sy );
		printf( "%s\n", can_arrive?"YES":"NO" ); // 使用三目表达式压长度(?)
	}
	return 0;
}
		


inline void reset( )
{
	for ( register int i=0; i<MAXL; i++ )
	{
		map[1][i]=map[2][i]=map[3][i]=1;
		map[0][i]=map[4][i]=0;
		vis[1][i]=vis[2][i]=vis[3][i]=0;
		vis[0][i]=vis[4][i]=1;
	}
// 初始化的时候将边界也设置为不能走，防止搜索的时候越界；
// 我采用的是先假设全部都可以走，读到障碍的时候再设置为不能走
	can_arrive=0;
	return;
}

inline void dfs( int nowx, int nowy )
{
	if ( nowy>=len ) //走到了隧道尽头 
		can_arrive=1;
	if ( can_arrive ) // 已经有合法路径 
		return;
	if ( map[nowx][nowy]==0 ) // 走到了不能走的格子 
		return;
	if ( vis[nowx][nowy] ) // 当前格子被访问过 
		return;
	vis[nowx][nowy]=1; // 记录访问 
	for ( int i=-1; i<=1; i++ )
		if ( map[nowx][nowy+1] && map[nowx+i][nowy+1] 
		&& map[nowx+i][nowy+2] && map[nowx+i][nowy+3] )
		// 判断路径上是否都是空格子，是再继续搜索 
			dfs( nowx+i, nowy+3 );
	return;
}
```

[提交记录 用时: 511ms / 内存: 3248KB](https://www.luogu.org/record/show?rid=6784349)

## 广告：加入代码公开计划 互助共建和谐洛谷
~~逃~~

---

## 作者：Jinzixun (赞：1)

根据物体的相对运动，所以可以将火车视为不动，玩家走三格。

这里我使用了反向递推的方法，和别的题解有所不同，速度挺快。

代码很好理解。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int t, n, k, beg;//beg 表示起点
bool dp[4][N];
string s[4];
int main(){
	scanf("%d", &t);
	while(t--){
		memset(dp, 0, sizeof(dp));//多测清空
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= 3; i++){
			cin >> s[i];
    		s[i] = ' ' + s[i];
			if(s[i][1] == 's'){
                beg = i;
                s[i][1] = '.';
            }
		}
		while(n % 3 != 1){
			n++;
			for(int i = 1; i <= 3; i++)	s[i][n] = '.';
		}//这样最后才能刚好循环到1
        dp[1][n] = dp[2][n] = dp[3][n] = true;//初始条件
		for(int j = n - 3; j >= 1; j -= 3){
			for(int i = 1; i <= 3; i++){
				if(s[i][j] != '.')	continue;
				for(int d = -1; d <= 1; d++){//d枚举移动方向
					if(i + d >= 1 && i + d <= 3){
						if(s[i][j + 1] == '.' && s[i + d][j + 1] == '.' && s[i + d][j + 2] == '.' && s[i + d][j + 3] == '.'){//判断这一轮有没有火车
							dp[i][j] |= dp[i + d][j + 3];
						}
					}
				}
			}
		}
		printf(dp[beg][1] ? "YES\n" : "NO\n");
	}
	return 0;
}
```

---

## 作者：RiceFruit (赞：1)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF585B)

给你一个 $3\times n$ （ $3$ 行 $n$ 列）的二维字符数组，其中 $\texttt{s}$ 表示你的初始位置，$\texttt{A}$~ $\texttt{Z}$ 表示列车。

对于每回合，你要先往右一格，再选择往上、不动、或者往下走一格（不能超出格子）。然后每辆列车都会往左走两格，若超出边界则会消失一些。若在任何时候列车撞到了你，那么就会结束游戏。如果存在一种方案使得你可以到达终点（即最后一列），则输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

## 思路
我们考虑使用 `dfs`。

但是每此移动后都改变车的位置，那么很容易 $\texttt{TLE}$ （~~本蒟蒻~~我第一次的做法)。

这时我们换一种思路：

每次车移动两格时，你是不动的，这可以转换为：车不动，你往前移动两回合。且移动的两回合中都不能碰到车。这样一来，不仅可以省去移动车的时间，代码也变得更简单了。

这样，问题就转换成了：每回合，你先往右移动两格，再选择往上、不动、或者往下走一格（不能超出格子），然后往前移动两格，且任意时刻都不能碰到车。

这样一来，代码就会变得非常简单。

## CODE

```
#include<bits/stdc++.h>
using namespace std;
const int N=170,mod=1e9+7;
int T;
bool b[4][N];
int n,m;
bool as;
char s[N];
bool vis[4][N];
void dfs(int u,int x){//u表示当前走到第u列，x表示当前为第x行 
	if(u>=n){
		as=1;//标记成功标记 
		return;
	}
	if(vis[x][u]||as)return;//如果已经走过了或者当前已经成功，就返回 
	vis[x][u]=1;//标记为已经走过 
	if(b[x][u+1])return;
	for(int i=x-1;i<=x+1;i++){
		if(i<1||i>3)continue;//超出格子，跳过 
		if(!b[i][u+1]&&!b[i][u+2]&&!b[i][u+3]){//如果都没有车 
			dfs(u+3,i);//继续dfs 
		}
	}
	return;
}
void solve(){
	as=0;
	cin>>n>>m; 
	memset(b,0,sizeof(b));
	memset(vis,0,sizeof(vis));
	int dq;
	for(int i=1;i<=3;i++){
		scanf("%s",s);
		if(s[0]=='s')dq=i;
		for(int j=0;j<n;j++){
			if(s[j]>='A'&&s[j]<='Z')b[i][j+1]=1;
		}
	}
	dfs(1,dq);
	if(as){
		cout<<"YES\n";
	}
	else{
		cout<<"NO\n";
	}
	return;
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```


---

## 作者：星空记逸 (赞：1)

### [$CF585B$ $Phillip$ $and$ $Trains$](https://www.luogu.com.cn/problem/CF585B)

~~一道难度低于蓝题的搜索题。~~

**题目**：游戏人物向右一步，选择向上或者向下一步或者停在原地。然后所有火车同时向左开两格。在任何时候火车撞到游戏人物，游戏人物也死了。火车会一直向左开，直到完全消失。

物理学告诉我们，可以将火车相对人向左运动看作**人相对火车向右运动**。

所以题目转为：火车不动，每次人向右一步，选择换行或者不换行，再向右走两步。

可以发现有以下三种情况：（在第一行和第三行可能因为碰壁而无法换行）

![](https://cdn.luogu.com.cn/upload/image_hosting/tfhyry94.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/s4lwduwd.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/m4jhz0kh.png)

接下来只用$BFS$，或$DFS$即可搜索得出结果。

(在搜索时需要用数组记录是否搜过不然可能$TLE$)

$DFS$代码：
```cpp
#include<bits/stdc++.h>
#define N 105
#define reg register
using namespace std;
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
int t,n,k,x1,pd;
int ma[5][N],pd1[5][N];
string s;
void solve(int x,int y){ //dfs
	if(y>=n||pd==1){ //已经搜到合法解
		pd=1;
		return;
	}
	pd1[x][y]=1;
	for(reg int i=-1;i<=1;i++){ //三种情况
		int nx=x+i;
		if(pd1[nx][y+3]==0&&ma[x][y+1]==0&&ma[nx][y+1]==0&&ma[nx][y+2]==0&&ma[nx][y+3]==0&&nx>=1&&nx<=3)//判断是否可以移动
			solve(nx,y+3);
	}
}
int main(){
	t=read();
	for(reg int z=1;z<=t;z++){
		n=read(),k=read();
		memset(ma,0,sizeof(ma));
		memset(pd1,0,sizeof(pd1));
		pd=0;
		for(reg int i=1;i<=3;i++){ 
			cin>>s;
			for(reg int j=0;j<s.size();j++){
				if(s[j]=='s')x1=i,pd1[i][1]=1;//起点
				else if(s[j]>='A'&&s[j]<='Z') ma[i][j+1]=1;//火车
			}
		}
		solve(x1,1);
		if(pd==1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Janat_ (赞：1)

呃DFS
Pascal代码

```pascal
var xx,yy,num,n1,i,j,n,m:longint;
    a:array[0..4,0..105]of char;
    bo:array[0..4,0..105]of boolean;
function canon(x:longint):boolean;
begin
  if (x>=1)and(x<=3) then exit(true);
   exit(false);
end;

function search(x,y:longint):boolean;
var bool:boolean;
begin
  bo[x,y]:=true;
  bool:=false;
  if (y+1<=n)and(not(a[x,y+1]='.'))  then exit(false);
  if canon(x-1) then
  begin
  if y+1>n then exit(true)
           else if (a[x-1,y+1]='.')and(y+2>n) then exit(true)
                                              else
                            if (a[x-1,y+1]='.')and(a[x-1,y+2]='.')and(y+3>n) then exit(true);
                   if (a[x-1,y+3]='.')and(a[x-1,y+1]='.')and(a[x-1,y+2]='.') then
                            if not bo[x-1,y+3] then bool:=search(x-1,y+3);
                            if bool then exit(true);
                          end;
          bool:=false;
          if canon(x+1) then begin
                             if y+1>n then exit(true)
                            else
                            if (a[x+1,y+1]='.')and(y+2>n) then exit(true)
                            else
                            if (a[x+1,y+1]='.')and(a[x+1,y+2]='.')and(y+3>n) then exit(true);

                   if (a[x+1,y+3]='.')and(a[x+1,y+1]='.')and(a[x+1,y+2]='.') then
                            if not bo[x+1,y+3] then bool:=search(x+1,y+3);
                            if bool then exit(true);
                          end;
          bool:=false;
                          begin
                             if y+1>n then exit(true)
                            else
                            if (a[x,y+1]='.')and(y+2>n) then exit(true)
                            else
                            if (a[x,y+1]='.')and(a[x,y+2]='.')and(y+3>n) then exit(true);
                   if (a[x,y+3]='.')and(a[x,y+1]='.')and(a[x,y+2]='.') then
                            if not bo[x,y+3] then bool:=search(x,y+3);
                            if bool then exit(true);
                          end;
          exit(false);
        end;


begin
  readln(num);
  for n1:=1 to num do
  begin
      readln(n,m); fillchar(bo,sizeof(bo),0);
      for i:=1 to 3 do
      begin
        for j:=1 to n do
        begin
          read(a[i,j]);
          if a[i,j]='s' then begin xx:=i; yy:=j; end;
        end;
        readln;
      end;
      if search(xx,yy) then writeln('YES')
                      else writeln('NO');
  end;
end.

```

---

## 作者：dyc2022 (赞：0)

此题解为[绿色健康食品](https://www.luogu.com.cn/record/98761597)，请放心食用。

***

这是一道搜索题，总体还是挺淼的，只是细节稍微多。

***

## 简要题意

在一个地图上有一个人，还有一些火车，每个回合内，人往右移动 $1$ 格，然后所有火车往左移动 $2$ 格。请问这个人能不能从第 $1$ 列的指定位置移动到最后一列？

## 心路历程

首先，题目告诉我们火车的列数，这个东西是没用的。~~我总不可能把那些火车一列一列地移动吧！~~

其次，题目还说用连续地相同字母来表示同一辆火车，这也是没用的。因为我们不需要知道具体哪个格子属于哪一辆火车，只需要把火车当做移动的障碍物处理即可。

但是，对于每次操作，都要把火车（障碍物）往左移动 $1$ 个格子，不仅操作不方便，还会付出一些本来没有必要的复杂度。

可是，我们又会想到，如果我们不方便把火车左移，那我们为什么不能把人右移呢？

![如果你看到了这行字，那么说明图炸了。](https://cdn.luogu.com.cn/upload/image_hosting/uj3fzmph.png)

如上图，这就是人**本身**在一个单位时间内的移动方式。为避免歧义，从这里开始，我将用 $(x_0 , y_0)$ 表示**第 $i$ 行、第 $j$ 列的格子**。那么假设不会越界，这个人就可能走到 $(x_0,y_0 + 1)$、$(x_0 + 1,y_0 + 1)$、$(x_0 - 1,y_0 + 1)$。如果我们要走到 $(x_0 + 1,y_0 + 1)$ 或 $(x_0 - 1,y_0 + 1)$， 那么就要满足 $(x_0,y_0 + 1)$ 的格子和我们的目标格子都可以通过。如果我们要走到 $(x_0,y_0 + 1)$，那么只要判断目标格子是不是火车（障碍物）。

人走完，火车就要开始移动了。

![](https://cdn.luogu.com.cn/upload/image_hosting/o3p7tphc.png)

上方的绿色箭头表示火车实际的移动方向，但是我们可以用人的移动抵消火车的移动。黑色空心箭头表示人要多移动的距离。

定义上图中的黑色线条箭头和黑色空心箭头连成的折线是单位时间中的一次移动，那么问题就被我们简化成求是否能通过若干次移动，到达最右边的列，且路径上的格子不和火车重合？

用搜索（我用的是 dfs）就可以完成。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int feide;//废的
int a[5][128];
int t;
int sx,sy;
int flag=0;
int f[5][128];
void dfs(int x,int y)
{
	if(flag)return;
	if(y>=n)
	{
		flag=1;
		return;
	}
	f[x][y]=1;
	for(int i=x-1;i<=x+1;i++)
	{
		if(f[i][y+3]==0&&a[x][y+1]==0&&a[i][y+1]==0&&a[i][y+2]==0&&a[i][y+3]==0&&i>=1&&i<=3)
			dfs(i,y+3);
	}
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>feide;
		memset(f,0,sizeof(f));
		memset(a,0,sizeof(a));
		for(int i=1;i<=3;i++)
			for(int j=1;j<=n;j++)
			{
				char tmppp;
				cin>>tmppp;
				if(tmppp=='s')sx=i,sy=j;
				a[i][j]=0;
				if(tmppp!='.'&&tmppp!='s')a[i][j]=1;
			}
		flag=0;
		dfs(sx,sy);
		string o=flag?"YES\n":"NO\n";
		cout<<o;
	}
    return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

对于同一时间，火车的状态是一样的，那么同一时间同一位置的状态是一样的，所以可以用记搜。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[105][5],n,k,T;
char s[105][5];
inline void work(){
	for(int i=1;i<=3;++i){
		for(int j=1;j<n;++j)
			s[j][i]=s[j+1][i];
		s[n][i]='.';
	}
}
int dfs(int x,int y){
	if(s[x][y]!='.')
		return 0;
	if(x==n)
		return 1;
	if(s[x+1][y]!='.')
		return 0; 
	if(~dp[x][y])
		return dp[x][y];
	char c[105][5];
	for(int i=1;i<=3;++i)
		for(int j=1;j<=n;++j)
			c[j][i]=s[j][i];
	bool flg1=1,flg2=1,flg3=1;
	if(y==1||s[x+1][y-1]!='.')
		flg1=0;
	if(s[x+1][y]!='.')
		flg2=0;
	if(y==3||s[x+1][y+1]!='.')
		flg3=0;
	work(),work();
	bool flg=0;
	if(flg1)
		flg|=dfs(x+1,y-1);
	if(flg2)
		flg|=dfs(x+1,y);
	if(flg3)
		flg|=dfs(x+1,y+1);
	for(int i=1;i<=3;++i)
		for(int j=1;j<=n;++j)
			s[j][i]=c[j][i];
	return dp[x][y]=flg;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		int p;
		for(int i=1;i<=3;++i)
			for(int j=1;j<=n;++j){
				cin>>s[j][i];
				if(s[j][i]=='s')
					p=i,s[j][i]='.';
			}
		memset(dp,-1,sizeof(dp));
		if(dfs(1,p))
			puts("YES");
		else
			puts("NO");			
	}
	return 0;
}
```

---

## 作者：Supor__Shoep (赞：0)

这是一道深搜的好题。

首先对于这种人和火车都能移动的情况，我们可以通过一次走多个格子的方式模拟出两个物体一起移动的状态。接着深搜此时人的 $x$ 和 $y$ 坐标，一直搜索直到人到达最右边。

大概框架找到了，我们就进行详细剖析。对于搜索，我们要注意有三种情况：一种是简简单单的向前移动，考虑到两个物体一起运动，那么 $y$ 的坐标就要移动 $3$ 格，当然为了保证安全到达终点，我们需要判断在接下来的移动当中会不会撞到火车。注意一个点在恢复当前节点时，记录已访问节点的数组要提前一个格子，因为对于这种情况，火车和人都是一起运动的。第二种是向左移动，这种情况只有在最右边两条路才可以运用，所以我们进行一个判断，接着同上，判断是否安全。第三种想必大家已经想到了，就是向右移动，这个就不做解释了。

最后是终止条件，如果到达了最右处就是可行的，同时为了避免超时，我们用一个变量判断是否找到了一种解法，如果找到了就不再进行其它节点的下一步访问。

还有一个点比较重要，由于是多组数据，初始化是不可缺少的，我相信一定会有人忘了讲记录地图的数组初始化，这样的话有可能逻辑混乱，于是我们就初始化为一个点，即全部可以行走，到了输入的时候再把其它的东西加进来。

代码如下：
```
void dfs(int x,int y)
{
    if(y>n||flag)
    {
        flag=1;
        return;
    }
    if(check(x,y+1)&&check(x,y+2)&&check(x,y+3)&&!vis[x][y+3])
    {
        vis[x][y+3]=1;
        dfs(x,y+3);
        vis[x][y+2]=0;
    }
    if(x<=2&&check(x,y+1)&&check(x+1,y+1)&&check(x+1,y+2)&&check(x+1,y+3)&&!vis[x+1][y+3])
    {
        vis[x+1][y+3]=1;
        dfs(x+1,y+3);
        vis[x+1][y+3]=0;
    }
    if(x>=2&&check(x,y+1)&&check(x-1,y+1)&&check(x-1,y+2)&&check(x-1,y+3)&&!vis[x-1][y+3])
    {
        vis[x-1][y+3]=1;
        dfs(x-1,y+3);
        vis[x-1][y+3]=0;
    }
}
```

---

## 作者：happybob (赞：0)

# 题意：

给定一个 $3$ 行 $n$ 列的地图，地图中有一些火车。每列火车都是一个在任意一行且至少长两个格的一些连续方格。同一列火车用相同字母表示，空地表示为 `.`。现在有一个起点，字符表示为 `s`，每次 `s` 先向右走一格，然后可以选择向上向下或不变位置。之后每一列火车会向左行驶两格。问有没有方法使得从起点开始不被火车撞死到达任意一行最后一列。

# 解法：

这题用搜索解决。因为问题是连通性而非最小步数等问题，广搜深搜均可解决。但是特别要注意的地方是存储火车以及火车向左行驶两步的模拟。

我们考虑用一个结构体存储一列火车的信息，那么我们需要存储的是这列火车所在的行，火车最左端与最右端所在的列，总共 $3$ 个信息。我是这样写的：

```cpp
struct Node
{
	int l, r, x; // 左端点所在的列、右端点所在的列、火车所在的行
	Node(int a, int b, int c): l(a), r(b), x(c){} // 构造函数
	Node()
	{
		l = r = x = 0;
	} // 构造函数
};
```

处理字符串时我们可以用 `vector` 存储每列火车，用 `unordered_map` 记录每列火车是否以及存储，因为题面说相同的火车字符相同。

剩下的问题在于火车行驶的模拟，这里有一个细节，例如以下例子：

```cpp
1
6 1
s...AA
....BB
....CC
```
那么其中一种方案的下一步是：

```cpp
..AA..
.sBB..
..CC..
```
紧接着是：

```cpp
AA....
BBs...
CC....
```

但是很明显最后这个状态无法实现，因为在 `s` 转移时会被火车撞到。但是如果直接模拟那么转移后其实是合法的，但是转移过程不合法。所以一定要对转移过程特判。

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>
#include <utility>
#include <unordered_map>
#include <vector>
using namespace std;

const int N = 105;
string s[N];
int t, n, k;
bool f[N][N];

struct Node
{
	int l, r, x;
	Node(int a, int b, int c): l(a), r(b), x(c){}
	Node()
	{
		l = r = x = 0;
	}
};

vector<Node> train; // 保存火车
unordered_map<char, bool> mp;

inline bool check(int x, int y)
{
	for (int i = 0; i < train.size(); i++)
	{
		if (train[i].x == x && train[i].l <= y && train[i].r >= y)
		{
			return true;
		}
	}
	return false;
}

inline bool work_next(int x, int y)
{
	for (int i = 0; i < train.size(); i++)
	{
		if (train[i].x == x && train[i].l <= y && train[i].r >= y) return true;
		if (train[i].x == x && train[i].l - 2 <= y && train[i].r >= y) return true;
	}
	for (int i = 0; i < train.size(); i++)
	{
		train[i].l -= 2;
		train[i].r -= 2;
	}
	return false;
}

inline void work_pre()
{
	for (int i = 0; i < train.size(); i++)
	{
		train[i].l += 2;
		train[i].r += 2;
	}
}

inline bool dfs(int x, int y)
{
	if (x < 1 || x > 3 || y < 0 || y >= n || f[x][y] || check(x, y)) return false;
	f[x][y] = true;
	if (y == n - 1)
	{
		//cout << x << " " << y << endl;
		puts("YES");
		return true;
	}
	y++;
	if (check(x, y)) return false;
	if (!work_next(x, y))
	{
		if (dfs(x, y)) return true;
		work_pre();
	}
	if (!work_next(x - 1, y))
	{
		if (dfs(x - 1, y)) return true;
		work_pre();
	}
	if (!work_next(x + 1, y))
	{
		if (dfs(x + 1, y)) return true;
		work_pre();
	}
	return false;
}


int main()
{
	scanf("%d", &t);
	while (t--)
	{
		memset(f, false, sizeof(f));
		scanf("%d %d", &n, &k);
		train.clear();
		mp.clear();
		int sx = 0, sy = 0;
		for (int i = 1; i <= 3; i++)
		{
			cin >> s[i];
		}
		for (register int i = 1; i <= 3; i++)
		{
			for (register int j = 0; j < n; j++)
			{
				if (s[i][j] == 's')
				{
					sx = i;
					sy = j;
				}
				else
				{
					if (s[i][j] == '.' || mp.count(s[i][j])) continue;
					mp[s[i][j]] = true;
					Node p;
					p.x = i;
					p.l = j;
					p.r = j;
					for (register int k = j + 1; k < n; k++)
					{
						if (s[i][k] != s[i][j])
						{
							p.r = k - 1;
							break;
						}
					}
					train.push_back(p);
				}
			}
		}
		if (!dfs(sx, sy))
		{
			puts("NO");
		}
	}
	return 0;
}
```



---

## 作者：Macesuted (赞：0)

[题面](https://www.luogu.com.cn/problem/CF585B)
## 题意
一个跑酷游戏，每一回合玩家先向前跑一步，然后允许向上一格、向下一格和不动，然后火车前进两步。如果撞到火车则游戏失败，如果玩家成功跑到了地图的最右边，则游戏胜利。现在告诉你场上的情况，问你玩家是否可以成功。

## 分析
首先很容易想到使用bfs，因为在这里有拐弯这一个操作，这一处会使得可能的方案数不止一种，为了遍历所有可能的方案我们使用bfs。

然后我们发现火车向左移两步和玩家再向右移两步相同，所以我们让火车不移动，毕竟玩家移动比火车移动要简单很多。玩家在此时额外向前跑两步而不是火车移动。则整个回合内玩家操作如下：

1. 前进一步
2. 向上一步，向下一步，或不动
3. 前进两步

期间任何一步操作中若玩家移动路径上的方块上有火车，则此方案不合法。

详情见代码。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> node;

int train[3][105];
bool visit[3][105];
int n, k;
queue<node> que;

bool bfs(int tx, int ty) {
    memset(visit, 0, sizeof(visit));
    while (!que.empty())
        que.pop();
    que.push((node){tx, ty});  //起点
    while (!que.empty()) {
        node cac = que.front();
        que.pop();
        int &x = cac.first, &y = cac.second;
        if (visit[x][y])
            continue;
        visit[x][y] = true;
        if (y >= n - 1)  //跑出地图，即成功
            return true;
        if (train[x][++y])  //1.前进一格
            continue;
        if (y == n - 1)  //跑出地图，即成功
            return true;
        for (int i = -1; i < 2; i++) {  //2.尝试转向
            int tx = x + i;
            if (tx < 0 || tx > 2)
                continue;
            if (train[tx][y] || train[tx][y + 1] || train[tx][y + 2])
                continue;  //3.前进两格
            que.push((node){tx, y + 2});
        }
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(train, 0, sizeof(train));
        scanf("%d%d", &n, &k);
        int start_x = 1, start_y = 0;  //起始位置
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                char c = getchar();
                while (c == ' ' || c == '\n' || c == '\r')
                    c = getchar();
                train[i][j] = c != '.';
                if (c == 's')
                    start_x = i, start_y = j;
            }
        }
        if (bfs(start_x, start_y))
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
```

---

## 作者：裘小小 (赞：0)

#### 正解：
## ~~深搜~~
科学老师表示运动是相对的，所以可以把火车向右两格看做人向左走两格，即一回合游戏人物向右一步(如果此时撞到火车就死了)。接着，可以选择向上或者向下一步或者停在原地（不能碰到火车），再向右2格。然后 
### ~~深搜~~
```pascal
var
  xx,yy,num,n1,i,j,n,m:longint;
  a:array[0..4,0..105]of char;
  vis:array[0..4,0..105]of boolean;
function ok(x:longint):boolean;
begin
  if (x>=1)and(x<=3) then
                       exit(true)
                     else
                       exit(false);

end;
function check(x,y:longint):boolean;
var
  t1:boolean;
begin
  vis[x,y]:=true;
  t1:=false;
  if (y+1<=n)and(not(a[x,y+1]='.')) then
    exit(false);
  if ok(x-1) then
    begin
      if y+1>n then
        exit(true)
      else
        if (a[x-1,y+1]='.')and(y+2>n) then
          exit(true)
        else
          if (a[x-1,y+1]='.')and(a[x-1,y+2]='.')and(y+3>n) then
            exit(true);
      if (a[x-1,y+3]='.')and(a[x-1,y+1]='.')and(a[x-1,y+2]='.') then
        if not vis[x-1,y+3] then
          t1:=check(x-1,y+3);
      if t1 then exit(true);
    end;
  t1:=false;
  if ok(x+1) then
    begin
      if y+1>n then
        exit(true)
      else
      if (a[x+1,y+1]='.')and(y+2>n) then
        exit(true)
      else
      if (a[x+1,y+1]='.')and(a[x+1,y+2]='.')and(y+3>n) then
        exit(true);
      if (a[x+1,y+3]='.')and(a[x+1,y+1]='.')and(a[x+1,y+2]='.') then
        if not vis[x+1,y+3] then
          t1:=check(x+1,y+3);
      if t1 then
      exit(true);
    end;
    t1:=false;
    begin
      if y+1>n then
        exit(true)
      else
        if (a[x,y+1]='.')and(y+2>n) then
          exit(true)
        else
          if (a[x,y+1]='.')and(a[x,y+2]='.')and(y+3>n) then
            exit(true);
       if (a[x,y+3]='.')and(a[x,y+1]='.')and(a[x,y+2]='.') then
         if not vis[x,y+3] then
           t1:=check(x,y+3);
       if t1 then
         exit(true);
    end;
  exit(false);
end;
procedure I_Can_;
begin
  readln(num);
end;
procedure AK_NOI;
begin
  for n1:=1 to num do
    begin
      readln(n,m);
      fillchar(vis,sizeof(vis),0);
      for i:=1 to 3 do
        begin
          for j:=1 to n do
            begin
              read(a[i,j]);
              if a[i,j]='s' then
                              begin
                                xx:=i;
                                yy:=j;
                              end;
            end;
          readln;
        end;
      if check(xx,yy) then
                        writeln('YES')
                      else
                        writeln('NO');
    end;
end;
begin
  I_Can_;AK_NOI;//蜜汁代码QAQ
end.



```

---

