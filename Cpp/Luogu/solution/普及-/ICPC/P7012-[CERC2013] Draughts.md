# [CERC2013] Draughts

## 题目描述

国际跳棋（或称跳棋）是一种由两个对手在 $10 \times 10$ 的棋盘上进行的游戏。棋盘上的方块是黑色或白色的，就像经典的国际象棋棋盘一样。玩家一方控制黑棋，另一方控制白棋。棋子只能占据黑色的格子。棋手们交替走棋，各自移动自己的一个棋子。

最有趣的走法是吃掉：如果一个对角线相邻的格子里有对手的棋子，可以通过跳过它到紧挨着它的未被占领的格子来吃掉（并从游戏中删除被吃掉的这个棋子）。允许在一步棋中用一个棋子连续吃掉几个棋子。通过向前或向后的跳跃来吃子也是合法的。

你会得到一个棋子的位置。现在轮到白方了。计算他在下一步棋中能吃掉的最大可能的黑棋数量。

## 样例 #1

### 输入

```
2

.#.#.#.#.#
#.#.#.#.#.
.#.#.B.#.#
#.#.#.#.#.
.#.#.B.#.#
#.#.W.#.#.
.#.#.#.#.#
#.#.#.B.#.
.#.#.#.#.#
#.#.#.#.#.

.#.#.#.#.#
#.#.#.#.#.
.#.#.B.#.#
#.B.#.B.#.
.#.#.B.#.#
#.B.W.#.#.
.#.B.B.#.#
#.#.#.#.#.
.#.B.B.#.#
#.#.#.#.#.
```

### 输出

```
2
4
```

# 题解

## 作者：David_yang (赞：26)

[传送门](https://www.luogu.com.cn/problem/P7012)

第六篇题解，如有不妥请~~忽视~~指出。

## 题目大意：

给定一个国际跳棋棋盘，你现在是白方，该你走棋，求你最多可以吃多少颗棋子。

## 算法：

搜索。

## 解析：

这道题大体思路应该好想，但有一些小细节需要注意。

先几句话把大体思路讲一下。很容易想到，它可能会有多颗白棋，那么每一颗棋子都要搜一遍，看一下最多能吃多少颗棋子，最终再看吃的最多的那颗棋子吃了多少颗。

然后就是一些小细节：

1. 搜索时注意每一步都要还原，而且不是只还原 $1$ 个，码量有点多（有点抽象，看下面的代码）。

2. 多组数据，**不清零见祖宗！！！**

3. 我栽在这一个点上。清零就够了，不要给习惯性地他设成负的多少，因为题目中说：如果没有合法的棋步（例如，棋盘上没有白棋），只需输出 $0$。没搜到时，由于最大值初始化为 $0$，所以输出时直接输出就行了。

好了，该说的也说完了，那我放代码了。放代码之前，祝大家新年快乐（尽管春节已经过了几天了……）！

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,mmax,dx[]={-2,-2,2,2},dy[]={-2,2,2,-2};		//祝大家新的一年里龙（long）腾虎跃！
char a[15][15];
void dfs(long long x,long long y,long long cnt)
{
	if((a[x-1][y-1]!='B' || a[x-2][y-2]!='#') && (a[x-1][y+1]!='B' || a[x-2][y+2]!='#') && (a[x+1][y-1]!='B' || a[x+2][y-2]!='#') && (a[x+1][y+1]!='B' || a[x+2][y+2]!='#'))	//判断条件，有点长，但还好理解
	{
		mmax=max(mmax,cnt);
		return; 
	}
	for(int i=0;i<4;i++)
	{
		long long nx=x+dx[i],ny=y+dy[i];
		if(nx>0 && nx<11 && ny>0 && ny<11 && a[nx][ny]!='B' && a[nx][ny]!='W')
		{
			if(i==0 && a[x-1][y-1]=='B')
			{
				a[x-1][y-1]='#';
				a[x][y]='#';
				a[nx][ny]='W';
				dfs(nx,ny,cnt+1);
				a[x-1][y-1]='B';
				a[x][y]='W';
				a[nx][ny]='#';			//要还原 3 个格子，所以这里的代码比较长
			}
			if(i==1 && a[x-1][y+1]=='B')
			{
				a[x-1][y+1]='#';
				a[x][y]='#';
				a[nx][ny]='W';
				dfs(nx,ny,cnt+1);
				a[x-1][y+1]='B';
				a[x][y]='W';
				a[nx][ny]='#';
			}
			if(i==2 && a[x+1][y+1]=='B')
			{
				a[x+1][y+1]='#';
				a[x][y]='#';
				a[nx][ny]='W';
				dfs(nx,ny,cnt+1);
				a[x+1][y+1]='B';
				a[x][y]='W';
				a[nx][ny]='#';
			}
			if(i==3 && a[x+1][y-1]=='B')
			{
				a[x+1][y-1]='#';
				a[x][y]='#';
				a[nx][ny]='W';
				dfs(nx,ny,cnt+1);
				a[x+1][y-1]='B';
				a[x][y]='W';
				a[nx][ny]='#';
			}
		}
	}
}
int main()
{
	scanf("%lld",&n);
	while(n--)
	{
		for(int i=1;i<11;i++)
		{
			for(int j=1;j<11;j++)
			{
				cin>>a[i][j];
			}
		}
		for(int i=1;i<11;i++)
		{
			for(int j=1;j<11;j++)
			{
				if(a[i][j]=='W')
				{
					dfs(i,j,0);
				}
			}
		}
		printf("%lld\n",mmax);
		mmax=0;						//要清零，而且设为0就够了
	}
	return 0;
}
```

注：代码已 AC 过，请放心食用。

最后，浏览过看过也要赞过！

---

## 作者：Genshin_ZFYX (赞：11)

# P7012题解

[原题传送门](https://www.luogu.com.cn/problem/P7012)

发现楼上没有一个写 bfs 滴，于是——

又发现 bfs 难写得很，写了三天连样例都没过（真的很疑惑为什么题目标签里边有 bfs 但没有 dfs）

打了三天，总算不再坚持了，老老实实的写 dfs 吧～

### 话不多说，进入正题——

思路：dfs + 回溯（~~只是有一点坑~~）。遇见一枚白棋就开始搜索，标记黑棋有没有被吃。

AC 代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define I return
#define love 0
#define FIRESTARS ;
int a[1145][1145],vis[1145][1145],n,m,maxn;
int dx[]={1,-1,1,-1},dy[]={1,-1,-1,1},ddx[]={2,-2,2,-2},ddy[]={2,-2,-2,2}; //方向数组，自己理解 
void dfs(int x,int y,int sum) //xy 为起始坐标，返回值为最多能吃多少棋子
{
	maxn=max(sum,maxn);
	for(int i=0;i<4;i++)
		{
			int nx=x+dx[i],ny=y+dy[i],xx=ddx[i]+x,yy=ddy[i]+y;
			if(xx>=1&&yy>=1&&xx<=n&&yy<=m&&!a[xx][yy]&&a[nx][ny]==2&&!vis[nx][ny])
			{
				vis[nx][ny]=1; //这里我们标记黑棋有没有被吃 
				dfs(xx,yy,sum+1);
				vis[nx][ny]=0; //此题要回溯
			}
		}
}
signed main()
{
	int t;cin>>t;
	n=m=10; //行和列，这样子用更习惯 
	while(t--)
	{
		maxn=0; //千万别忘了初始化！
    	for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    	{
    		char c;cin>>c;
    		if(c=='#')a[i][j]=0;
    		if(c=='.')a[i][j]=1;
    		if(c=='B')a[i][j]=2;
    		if(c=='W')a[i][j]=3;
    	 } //输入完毕，正片开始 
    	 for(int i=1;i<=n;i++)
    	 for(int j=1;j<=m;j++)
    	 	if(a[i][j]==3) //找到了一枚白棋
			 {
                a[i][j]=0; //先把它赋值为 0
                //memset(vis,0,sizeof(vis)); 这里不要初始化 vis！初始化多了会 TLE
    		 	dfs(i,j,0);//开始搜索
                a[i][j]=3; //再把它赋值回去
            }
    	cout<<maxn<<endl; //输出
	}
	I love FIRESTARS //我爱火星！ 
}

```

火星提醒您：

`搜索大法好，深广要慎选`

`选择不规范，爆零两行泪`

![](https://cdn.luogu.com.cn/upload/image_hosting/th824pw0.png)

---

## 作者：_Epsilon_ (赞：3)

## 思路
国跳玩法不多说了，其实这一道题就像你在下棋的时候算打击的思路一样，把一个走法走到底，看一看收益怎么样。最后找出最优解。

根据上列想法，**深搜**秒了！
## 实现
找到每一个白棋，再去看它旁边有没有黑棋，最后看其后面有没有阻挡。

搜到底时，和当前最大值比较即可。
## Code
```cpp
#include <bits/stdc++.h> 
using namespace std;
int n,m,ans; 
char a[105][105];
bool pdx(int x)
{
    return x-2>=1;
}
bool pdxx(int x)
{
    return x+2<=10;
}
bool pdy(int y)
{
    return y-2>=1;
}
bool pdyy(int y)
{
    return y+2<=10;
}
void dfs(int x,int y,int k){
	ans=max(k,ans);
	if(pdx(x)&&pdy(y)&&a[x-1][y-1]=='B'&&a[x-2][y-2]!='B'&&a[x-2][y-2]!='W')
	{
	    a[x-1][y-1]='.';
	    dfs(x-2,y-2,k+1);
	    a[x-1][y-1]='B';
	}
	if(pdxx(x)&&pdyy(y)&&a[x+1][y+1]=='B'&&a[x+2][y+2]!='B'&&a[x+2][y+2]!='W')
	{
	    a[x+1][y+1]='.';
	    dfs(x+2,y+2,k+1);
	    a[x+1][y+1]='B';
	}
	if(pdx(x)&&pdyy(y)&&a[x-1][y+1]=='B'&&a[x-2][y+2]!='B'&&a[x-2][y+2]!='W')
	{
	    a[x-1][y+1]='.';
	    dfs(x-2,y+2,k+1);
	    a[x-1][y+1]='B';
	}
	if(pdxx(x)&&pdy(y)&&a[x+1][y-1]=='B'&&a[x+2][y-2]!='B'&&a[x+2][y-2]!='W')
	{
	    a[x+1][y-1]='.';
	    dfs(x+2,y-2,k+1);
	    a[x+1][y-1]='B';
	}
	return;
}
int main(){
	cin>>n;
	while(n--)
	{
	    ans=0;
		for(int i=1;i<=10;i++)
		{
			for(int j=1;j<=10;j++)
			{
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=10;i++)
		{
		    for(int j=1;j<=10;j++)
		    {
		        if(a[i][j]=='W')
		        {
		            a[i][j]='#';
		            dfs(i,j,0);
		            a[i][j]='W'; 
		        }
		    }
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
## 致谢
- 感谢重庆棋院以及重庆两江国际跳棋协会。
- 感谢洛谷平台。
- 感谢我的国际跳棋老师——张*教练。

---

## 作者：Tjaweiof (赞：2)

# P7012 题解
[题目传送门](https://www.luogu.com.cn/problem/P7012)

因为数据范围较小，选择 dfs。只需要几个特判即可：

1. 有可能会有多个 W，所以需要输出答案最大的。如：
```
.#.#.#.#.#
#.#.#.#.#.
.#.#.#.#.#
#.#.#.#.#.
.#.#.#.#.#
#.#.W.#.#.
.#.#.#.#.#
#.#.#.#.#.
.#.#.#.B.#
#.#.#.#.W.
```

2. 跳到的格子不能是 `B` 或 `W`。如：
```
.W.#.#.#.#
#.B.#.#.#.
.#.W.#.#.#
#.#.#.#.#.
.#.#.#.#.#
#.#.#.#.#.
.#.#.#.#.#
#.#.#.#.#.
.#.#.#.#.#
#.#.#.#.#.
```
这个点非常坑，我调几天，提交记录甚至被我刷了 3 页，最后还是某个巨佬帮我调出来的。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long nextstep[4][2] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
const long long nextstep2[4][2] = {{-2, -2}, {2, -2}, {-2, 2}, {2, 2}};
long long n;
char a[11][11];
long long dfs(long long x, long long y, long long step){
	long long maxn = 0;
	for (long long k = 0; k < 4; k++){
		if (x + nextstep2[k][0] < 1 || x + nextstep2[k][0] > 10 || y + nextstep2[k][1] < 1 || y + nextstep2[k][1] > 10){
			continue;
		}
		if (a[x + nextstep[k][0]][y + nextstep[k][1]] == 'B' && a[x + nextstep2[k][0]][y + nextstep2[k][1]] == '#'){
			a[x + nextstep[k][0]][y + nextstep[k][1]] = '#';
			maxn = max(maxn, dfs(x + nextstep2[k][0], y + nextstep2[k][1], step + 1) + 1);
			a[x + nextstep[k][0]][y + nextstep[k][1]] = 'B';
		}
	}
	return maxn;
}
int main(){
	scanf("%lld", &n);
	while (n--){
		bool flag = true;
		long long ans = 0;
		for (long long i = 1; i <= 10; i++){
			for (long long j = 1; j <= 10; j++){
				scanf(" %c", &a[i][j]);
			}
		}
		for (long long i = 1; i <= 10; i++){
			for (long long j = 1; j <= 10; j++){
				if (a[i][j] == 'W'){
					a[i][j] = '#';
					ans = max(dfs(i, j, 0), ans);
					a[i][j] = 'W'; // 这句代码就是我调了3页记录的
					flag = false;
				}
			}
		}
		if (!flag){
		    printf("%lld\n", ans);
		} else {
		    printf("0\n");
		}
	}
	return 0;
}

```
**此代码时间复杂度 $O(n^2)$，空间复杂度 $O(n)$，完美过关！**

---

## 作者：Alystkia (赞：1)

> [P7012 [CERC2013] Draughts](/problem/P7012)。

考虑到数据最大为 $10$，可以直接考虑爆搜。

字符 # 和 . 表示空的黑色和白色方块，W 表示有浅色棋子的方块，B 表示有深色棋子的方块。

+ 注意每次搜完的时候要将数组还原，举个栗子：
```cpp
if(_x >= 1 && _x <= n && _y >= 1 && _y <= n && mp[_x][_y] == 0 && mp[xx][yy] == 2)
{
	mp[xx][yy] = 0;
	dfs(_x , _y , step + 1);
	mp[xx][yy] = 2; //还原。
}
```
```cpp
if(mp[i][j] == 1)
{
	mp[i][j] = 0;
	dfs(i , j , 0);
	mp[i][j] = 1; //还原
}
```

+ 增量数组：
```cpp
const long long dx[] = {0,1,1,-1,-1};
const long long dy[] = {0,1,-1,1,-1};
```
注意，有两个增量，这里简化成一个，搭配下：
```cpp
long long xx = dx[i] + x , yy = dy[i] + y;
long long _x = dx[i] * 2 + x , _y = dy[i] * 2 + y;
```
注意 $\times2$。

+ 考虑有多组测试数据，记得复原。
+ 每次找到每一个浅色棋子，去看它旁边有没有深色棋子。
+ 没有就输出 `0`。

具体见代码。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

long long ans = 0;
long long mp[15][15];
const long long n = 10;

const long long dx[] = {0,1,1,-1,-1};
const long long dy[] = {0,1,-1,1,-1};

void dfs(long long x , long long y , long long step)
{
	ans = max(step , ans);
	
	for(long long i = 1 ; i <= 4 ; i ++)
	{
		long long xx = dx[i] + x , yy = dy[i] + y;
		long long _x = dx[i] * 2 + x , _y = dy[i] * 2 + y;
		
		if(_x >= 1 && _x <= n && _y >= 1 && _y <= n && mp[_x][_y] == 0 && mp[xx][yy] == 2)
		{
			mp[xx][yy] = 0;
			dfs(_x , _y , step + 1);
			mp[xx][yy] = 2;
		}
	}
}

int main()
{
	long long T;
	cin >> T;
	
	while(T --)
	{
		memset(mp , 0 , sizeof(mp));		
		ans = 0;
		
		for(long long i = 1 ; i <= n ; i ++)
		{
			for(long long j = 1 ; j <= n ; j ++)
			{
				char c;
				cin >> c;
				
				if(c == 'W')
					mp[i][j] = 1;
				
				else if(c == 'B')
					mp[i][j] = 2;
				
				else
					mp[i][j] = 0;
			}
		}
		
		for(long long i = 1 ; i <= n ; i ++)
		{
			for(long long j = 1 ; j <= n ; j ++)
			{
				if(mp[i][j] == 1)
				{
					mp[i][j] = 0;
					dfs(i , j , 0);
					mp[i][j] = 1;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：_iridescent (赞：1)

### 题目大意

给你一个国际象棋棋盘，上面摆放着一些棋子。你现在操控着一颗白棋，每次你可以往四个对角线的其中一个方向跳两步，如果你现在的位置和跳之前的位置中间夹了一颗黑棋，你就可以吃掉它，每回合可以一直行动直到你无法吃掉任何一颗棋子。要求你输出白棋最多能吃掉几个黑棋。（有可能有多个白棋，输出最大的）
移动方式可以看看下面（简陋的）草图：

![棋子移动示意图](https://cdn.luogu.com.cn/upload/image_hosting/ekhrf4x3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

### 思路

直接深搜就可以了。

因为这个矩阵字母间没有间距，所以我们可以把它转换成数字来处理，只要枚举到一个地方是白棋，就从它开始搜一遍，记录能吃几个再取最大值就行了。

与其它不同的是，在深搜函数中，我们要把敌人的坐标和要跳的坐标都表示出来，然后再依题意处理。其中还有一些细节，就打在下面代码的注释里了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int T,n,m,ans;
int mp[15][15];
int dx[4]={-1,1,1,-1},dy[4]={1,1,-1,-1};// 偏离量，注意是四个对角线方向的 
bool check(int x,int y){// 判断坐标是否合法 
	return x>=1&&x<=10&&y>=1&&y<=10;// 意思就是满足前面的条件就返回true
}
void dfs(int x,int y,int step){
	ans=max(ans,step);
	for(int i=0;i<4;i++){
		int mx=x+dx[i]*2,my=y+dy[i]*2;// 白棋的新坐标 
		int ex=x+dx[i],ey=y+dy[i];// 黑棋坐标 
		if(mp[mx][my]==0&&mp[ex][ey]==-1&&check(mx,my)){// 我们只需判断新坐标是否合法即可，因为黑棋坐标永远在新坐标内 
			mp[ex][ey]=0;
			dfs(mx,my,step+1);
			mp[ex][ey]=-1;
		}
	}
}
signed main(){
	cin>>T;
	while(T--){
		ans=0;// 多测数据要清空！！！ 
		for(int i=1;i<=10;i++){
			string s;
			cin>>s;
			for(int j=0;j<10;j++){
				if(s[j]=='.'||s[j]=='#')mp[i][j+1]=0;// 注意string是从0开始的 
				else if(s[j]=='B')mp[i][j+1]=-1;
				else mp[i][j+1]=1; 
			}
		}
		for(int i=1;i<=10;i++){
			for(int j=1;j<=10;j++){
				if(mp[i][j]==1){
					mp[i][j]=0;// 注意腾出自己的位置，避免阻碍后面的搜索 
					dfs(i,j,0);
					mp[i][j]=1;// 因为只求吃掉棋子数量最大的那个棋，所以现在棋子得放回原位 
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：back_find (赞：1)

## 题目简述
你有一些棋子，如果在**对角线**相邻的格子里有对手的棋子，可以通过跳过它到紧挨着它的未被占领的格子，并**删除对手的棋子**，移动任意一个棋子，最多能吃几个对面的棋子。如果大家有点懵，请看下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ydyujecv.png)

红的是你的棋子，黑的是对手的棋子，绿的是可以跳到的位置。

## 思路
看数据范围很小，使用 DFS 遍历能走的方法，找出能吃掉最多棋子的即可。

## 代码
```cpp
#include<iostream>
using namespace std;
int t,qp[15][15],ans=0,mx[10]={1,1,-1,-1},my[10]={1,-1,1,-1};
char inp;
void dfs(int x,int y,int dep){
	ans=max(ans,dep);
	for(int i=0;i<4;i++){
		if(x+mx[i]*2>=1&&x+mx[i]*2<=10
		&&y+my[i]*2>=1&&y+my[i]*2<=10
		&&qp[x+mx[i]][y+my[i]]==2&&qp[x+2*mx[i]][y+2*my[i]]==0){
			qp[x+mx[i]][y+my[i]]=0;//要去掉棋子
			dfs(x+2*mx[i],y+2*my[i],dep+1);
			qp[x+mx[i]][y+my[i]]=2;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		ans=0;//初始化！！！
		for(int i=1;i<=10;i++){
			for(int j=1;j<=10;j++){
				cin>>inp;
				if(inp=='W')qp[i][j]=1;
				else if(inp=='B')qp[i][j]=2;
				else qp[i][j]=0;
			}
		}
		for(int i=1;i<=10;i++){
			for(int j=1;j<=10;j++){
				if(qp[i][j]==1){
					qp[i][j]=0;//不要自己挡住自己
					dfs(i,j,0);
					qp[i][j]=1;
				}
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：Y_zhao111 (赞：0)

### Description
题目传送门：[P7012 [CERC2013] Draughts](/problem/P7012)。

简单回溯题目，你操作白棋，判断白棋最多能吃几个敌方的棋。

### Analysis
考虑 $n\le10$，直接爆搜（回溯）。

分类讨论：
+ 字符 $\tt\#$ 和 $\tt.$ 表示空的黑色和白色方块，$\tt W$ 表示有浅色棋子的方块，$\tt B$ 表示有深色棋子的方块。

+ 增量数组：
	```cpp
	const int dx[4] = {-2,-2,2,2};
	const int dy[4] = {-2,2,2,-2};
	```	
+ **多组测试数据记得复原**。

+ 记得**回溯**。

+ 找到每一个浅色棋子，去看它旁边有没有深色棋子。

+ 记得找最大值，没有白棋输出 $-1$。

时间复杂度 $\mathcal{O}(n^2)$。

---

## 作者：sillation (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7012)



------------
### 关于这道题
因为此题的的数据很小，可以直接用 dfs 来做。

题目讲得很清楚，坑点挺多的。
#### 怎么移动白棋子
先输入整个棋盘，注意棋盘大小是 $10 \times 10$。输入完成遍历一遍，遇到白棋子进行搜索。

只要这枚白棋子任意一个斜对角是黑棋子并且黑棋子的斜对角上没有棋子，白棋子就可以移动到黑棋子的斜对角。

方向数组：
```cpp
dx[]={0,1,1,-1,-1},dy[]={0,1,-1,1,-1}；
```
坐标：
```cpp
int ux=dx[i]+x,uy=dy[i]+y,sx=dx[i]*2+x,sy=dy[i]*2+y;
```
#### 关于坑点
- $ans$ 一定要清零。
- 在遇到白棋子后，记得把白棋子的位置上变为没有棋子在经行搜索，搜索完毕记得恢复。
- 此题需要回溯。
#### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,t,dx[]={0,1,1,-1,-1},dy[]={0,1,-1,1,-1},v[20][20],s[20][20];
char c; 
void dfs(int x,int y,int k){
	ans=max(k,ans);
	for(int i=1;i<=4;i++){
		int ux=dx[i]+x,uy=dy[i]+y,sx=dx[i]*2+x,sy=dy[i]*2+y;
		if(sx>=1&&sx<=10&&sy>=1&&sy<=10&&s[sx][sy]==0&&s[ux][uy]==2){
			s[ux][uy]=0;
			dfs(sx,sy,k+1);
			s[ux][uy]=2;
		}
	}
}
int main(){
	cin>>t;
	while(t--){
		ans=0;
		for(int i=1;i<=10;i++){
			for(int j=1;j<=10;j++){
				cin>>c;
				if(c=='W') s[i][j]=1;
				else if(c=='B') s[i][j]=2;
				else s[i][j]=0;

			}
		} 
		for(int i=1;i<=10;i++){
			for(int j=1;j<=10;j++){
				if(s[i][j]==1){
					s[i][j]=0;
					dfs(i,j,0);
					s[i][j]=1;
				}
			}
		} 
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Flaw_Owl (赞：0)

# P7012 [CERC2013] Draughts 题解

原题链接：[P7012 [CERC2013] Draughts](https://www.luogu.com.cn/problem/P7012)

## 题目分析

这道题显然是一道经典的**搜索**问题，可以考虑用深搜（DFS）或者广搜（BFS）解决。在这道题中，鉴于地图较小（$10 \times 10$），并且存在地图改变的情况（棋子的移动和棋子被吃掉），使用**深搜 + 回溯**的方式是更优解。

这道题几乎没有什么难点，重点关注以下几个方面即可：

- 这道题棋子的坐标既有判断的部分（对角线上有没有黑色棋子），又有移动的部分（跳过棋子），要注意坐标的数值变化，容易出错
- 进行更深层的 DFS 之前要记得改变地图，有三个方面：原位置置空、被吃掉的棋子置空、移动后的位置置白；结束之后也要记得改变地图。并在 DFS 结束之后进行答案的维护。
- 这道题没有必要公式地使用 `vis` 数组防止重复，题目并没有提到。
- 注意进行深搜的判断条件
  1. 不能出界
  2. 四个角落有黑色棋子
  3. 移动到的位置不能有其他棋子

只要遍历整个地图，遇到白色棋子就进行一次深搜，维护最后的答案即可。

## AC 代码

```cpp
#include <iostream>
#include <cctype>

using namespace std;

// 快读
int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 15;
const int dirX[4] = {-1, -1, 1, 1};
const int dirY[4] = {1, -1, 1, -1};

int T;
int ans;

char mp[maxN][maxN];

// 判断是否出界
bool inBounds(int x, int y)
{
    return x >= 1 && y >= 1 && x <= 10 && y <= 10;
}

// 深搜
void dfs(int x, int y, int cnt)
{
    for (int i = 0; i < 4; i++)
    {
        // check 是判断黑色棋子是否存在，new 是如果可以吃掉的话，白色棋子移动到的位置
        int checkX = x + dirX[i];
        int checkY = y + dirY[i];
        int newX = x + dirX[i] * 2;
        int newY = y + dirY[i] * 2;
        if (mp[checkX][checkY] == 'B' && mp[newX][newY] == '#' && inBounds(newX, newY) && inBounds(checkX, checkY))
        {
            mp[x][y] = '#';
            mp[checkX][checkY] = '#';
            mp[newX][newY] = 'W';
            dfs(newX, newY, cnt + 1);
            mp[x][y] = 'W';
            mp[checkX][checkY] = 'B';
            mp[newX][newY] = '#';
        }
    }
    ans = max(cnt, ans);
}

int main()
{
    T = read();
    while (T--)
    {
        ans = 0;
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
                cin >> mp[i][j];
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
                if (mp[i][j] == 'W')
                    dfs(i, j, 0);
        printf("%d\n", ans);
    }
}
```

---

## 作者：fangminding (赞：0)

这题规定一个跳棋规则，判断最多能吃几个敌方子。

数据很小，棋盘大小确定，直接考虑进行深度优先搜索，用一个数组记录这个位置的子是否被吃，还有一个变量记录得到的最大答案。

AC 代码：

```
#include <bits/stdc++.h>
using namespace std;
char A[130][130];
int used[130][130];
int maax[130][130];
int nx[38]={-2,-2,2,2};
int ny[38]={2,-2,2,-2};
int x2[38]={-1,-1,1,1};
int y2[38]={1,-1,1,-1};
int ans;

struct node{int x,y,c;};

int dfs(node kkk)
{
	ans=max(ans,kkk.c);
	for(int i = 0;i <4;i++)
			if(kkk.x+nx[i]<=10&&kkk.x+nx[i]>=1&&kkk.y+ny[i]<=10&&kkk.y+ny[i]>=1)
				if(!used[kkk.x+x2[i]][kkk.y+y2[i]])
					if(A[kkk.x+nx[i]][kkk.y+ny[i]]=='#'||A[kkk.x+nx[i]][kkk.y+ny[i]]=='.')
						if(A[kkk.x+x2[i]][kkk.y+y2[i]]=='B')
						{
							node ppp;
							ppp.x=kkk.x+nx[i];
							ppp.y=kkk.y+ny[i];
							ppp.c=kkk.c+1;
							used[kkk.x+x2[i]][kkk.y+y2[i]]=1;
							dfs(ppp);
							used[kkk.x+x2[i]][kkk.y+y2[i]]=0;
							ans=max(ans,kkk.c+1);
						}
}

int main()
{
	int T;
	cin>>T;
	for(int asdf = 1;asdf <=T;asdf++)
	{
		for(int i = 1;i <=10;i++)
			for(int j = 1;j <=10;j++)
				cin>>A[i][j];
		ans=0;
		for(int i = 1;i <=10;i++)
			for(int j = 1;j <=10;j++)
				if(A[i][j]=='W')
				{
					A[i][j]='#';
					node asd;
					asd.x=i,asd.y=j,asd.c=0;
					memset(maax,0,sizeof(maax));
					memset(used,0,sizeof(used));
					dfs(asd);
					A[i][j]='W';
				}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：danb123 (赞：0)

## 题目大意

非常明白的一道题目，相信各位玩过的也知道，就是白棋可以杀掉它左上方、右上方、左下方、右下方的棋子，并移动到它对应的位置。本题给出了棋盘的布局，求白棋走一步最多杀掉多少枚黑棋。

## 题目分析

首先确定一定是深搜，遍历一遍棋盘，找到了白棋就开始深搜。从四个方向搜索，搜索条件要满足：

1. 不会出边界。
1. 它的左上方、右上方、左下方、右下方有一颗黑棋。
1. 它吃掉对方棋子后的位置不能有棋子。


深搜部分代码如下：
```cpp
void dfs(int x,int y,int cnt){
	maxn=max(cnt,maxn);//记录最大值 
	if(x-2>=1&&y-2>=1&&a[x-1][y-1]=='B'&&a[x-2][y-2]!='B'&&a[x-2][y-2]!='W') a[x-1][y-1]='.',dfs(x-2,y-2,cnt+1),a[x-1][y-1]='B';
	if(x+2<=10&&y+2<=10&&a[x+1][y+1]=='B'&&a[x+2][y+2]!='B'&&a[x+2][y+2]!='W') a[x+1][y+1]='.',dfs(x+2,y+2,cnt+1),a[x+1][y+1]='B';
	if(x-2>=1&&y+2<=10&&a[x-1][y+1]=='B'&&a[x-2][y+2]!='B'&&a[x-2][y+2]!='W') a[x-1][y+1]='.',dfs(x-2,y+2,cnt+1),a[x-1][y+1]='B';
	if(x+2<=10&&y-2>=1&&a[x+1][y-1]=='B'&&a[x+2][y-2]!='B'&&a[x+2][y-2]!='W') a[x+1][y-1]='.',dfs(x+2,y-2,cnt+1),a[x+1][y-1]='B';
}
```
以下为完整代码，时间复杂度极低。
```cpp
#include <bits/stdc++.h>//万能头 
using namespace std;
int n,m,maxn; 
char a[1001][1001];
void dfs(int x,int y,int cnt){
	maxn=max(cnt,maxn);//记录最大值 
	if(x-2>=1&&y-2>=1&&a[x-1][y-1]=='B'&&a[x-2][y-2]!='B'&&a[x-2][y-2]!='W') a[x-1][y-1]='.',dfs(x-2,y-2,cnt+1),a[x-1][y-1]='B';
	if(x+2<=10&&y+2<=10&&a[x+1][y+1]=='B'&&a[x+2][y+2]!='B'&&a[x+2][y+2]!='W') a[x+1][y+1]='.',dfs(x+2,y+2,cnt+1),a[x+1][y+1]='B';
	if(x-2>=1&&y+2<=10&&a[x-1][y+1]=='B'&&a[x-2][y+2]!='B'&&a[x-2][y+2]!='W') a[x-1][y+1]='.',dfs(x-2,y+2,cnt+1),a[x-1][y+1]='B';
	if(x+2<=10&&y-2>=1&&a[x+1][y-1]=='B'&&a[x+2][y-2]!='B'&&a[x+2][y-2]!='W') a[x+1][y-1]='.',dfs(x+2,y-2,cnt+1),a[x+1][y-1]='B';
}
int main(){
	cin>>n;
	while(n--){
		for(int i=1;i<=10;i++)
			for(int j=1;j<=10;j++)
				cin>>a[i][j];//输入 
		maxn=0;//初始化 
		for(int i=1;i<=10;i++)
			for(int j=1;j<=10;j++)
				if(a[i][j]=='W')//检测到白棋 
					a[i][j]='#',dfs(i,j,0),a[i][j]='W';//标记 
		cout<<maxn<<endl;
	}
}
```


---

## 作者：abensyl (赞：0)

原题：[P7012 [CERC2013] Draughts](https://www.luogu.com.cn/problem/P7012)。

~~在 CF 的 gym 里做题，发现洛谷这题也有就来水个题解。~~

## 思路 

首先明确题意和题目中的操作，大致就是说这样的要求：

- 你操作白棋；  
- 棋子只能往对角线方向移动；  
- 棋子可以向一个方向移动，当且仅当在这个方向上跨过一个黑棋，并且跨过之后的那个格子没有棋子；
- 被跨过的棋子会被吃掉；  
- 如果一个棋子移动过后可以移动，那么你可以继续，换言之，你可以连续对相同的棋子进行若干次合法的上述移动操作。

由于数据范围很小，可以注意到规定的棋盘大小是 $10\times 10$ 的，所以考虑直接暴力搜索。

对于每一个白棋都发起一次深度优先搜索，向左上、左下、右上、右下四个方向每一个方向进行依次枚举，只要可以移动，就进行移动吃子尝试，然后进行递归，枚举所有情况，取吃子数量的最大值。

注意：搜索的时候要注意回溯，保护原来的数据。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int jp[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
int col[13][13],res;
bool legal(int x,int y) {
	if(x<1||y<1) return false;
	if(x>10||y>10) return false;
	if(col[x][y]) return false;
	return true;
}
void dfs(int x,int y,int now) {
//	cout<<"dfs: "<<x<<' '<<y<<' '<<now<<'\n';
	res=max(res,now);
	for(auto c:jp) {
		int nxtx=x+c[0]*2,nxty=y+c[1]*2;
		if(!legal(nxtx,nxty)) continue;
		if(col[x+c[0]][y+c[1]]!=2) continue;
		col[x+c[0]][y+c[1]]=0;
		dfs(nxtx,nxty,now+1);
		col[x+c[0]][y+c[1]]=2;
	}
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		res=0;
		for(int i=1;i<=10;++i) {
			for(int j=1;j<=10;++j) {
				char ch=getchar();
				if(ch=='.'||ch=='#') col[i][j]=0;
				else if(ch=='B') col[i][j]=2;
				else if(ch=='W') col[i][j]=1;
				else --j;
			}
		}
		for(int i=1;i<=10;++i) {
			for(int j=1;j<=10;++j) {
				if(col[i][j]==1) {
					col[i][j]=0;
					dfs(i,j,0);
					col[i][j]=1;
				}
			}
		} cout<<res<<'\n';
	}
	return 0;
}
```

[代码和 AC 记录](https://codeforces.com/gym/100299/submission/235699590)。

---

