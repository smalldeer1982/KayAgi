# [USACO08MAR] Cow Travelling S

## 题目描述

奶牛们在被划分成 $N$ 行 $M$ 列（$2 \leq N,M \leq 100$）的草地上游走， 试图找到整块草地中最美味的牧草。

Farmer John 在某个时刻看见贝茜在位置 $(R_1, C_1)$，恰好 $T$（$0 \lt T \leq 15$）秒后，FJ 又在位置 $(R_2, C_2)$ 与贝茜撞了正着。FJ 并不知道在这 $T$ 秒内贝茜是否曾经到过 $(R_2, C_2)$，他能确定的只是，现在贝茜在那里。

设 $S$ 为奶牛在 $T$ 秒内从 $(R_1, C_1)$ 走到 $(R_2, C_2)$ 所能选择的路径总数，FJ 希望有一个程序来帮他计算这个值。每一秒内，奶牛会水平或垂直地移动 $1$ 单位距离（奶牛总是在移动，不会在某秒内停在它上一秒所在的点）。草地上的某些地方有树，自然，奶牛不能走到树所在的位置，也不会走出草地。

现在你拿到了一张整块草地的地形图，其中 `.` 表示平坦的草地，`*` 表示挡路的树。你的任务是计算出，一头在 $T$ 秒内从 $(R_1, C_1)$ 移动到 $(R_2, C_2)$ 的奶牛可能经过的路径有哪些。

## 说明/提示

奶牛在 $6$ 秒内从 $(1,3)$ 走到 $(1,5)$ 的方法只有一种，绕过她面前的树。

## 样例 #1

### 输入

```
4 5 6
...*.
...*.
.....
.....
1 3 1 5```

### 输出

```
1
```

# 题解

## 作者：JRzyh (赞：133)

从基础开始讲解记忆化搜索。

$\texttt{Part~-1~前置知识}$

深度优先搜索（dfs）。

$\texttt{Part~0~开始之前}$

拿到 P1535 这题的第一反应就应该是搜索。

这题爆搜思路很好想。

首先从出发点开始搜，

向上下左右四个方向搜索。

那么就只要到达目的地 `ans++`。

```cpp
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
int n,m,t,r1,c1,r2,c2,ans;
bitset<108>b[108];
void dfs(int x,int y,int time)
{
	if(time>t)return ;
	if(time==t)
	{
		if(x==r2&&y==c2)
		{
			ans++;
			return ;
		}
		else return ;
	}
	for(int i=0;i<4;i++)
	{
		if(b[x+dx[i]][y+dy[i]]||x+dx[i]<1||x+dx[i]>n||y+dy[i]<1||y+dy[i]>m)continue;
		dfs(x+dx[i],y+dy[i],time+1);
	}
}
int main()
{
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=0;j<m;j++)
		{
			if(s[j]=='*')b[i][j+1]=1;
		}
	}
	cin>>r1>>c1>>r2>>c2;
	dfs(r1,c1,0);
	cout<<ans<<endl;
 	return 0;
}
```
但肯定是过不了的，现在开始记忆化。

$\texttt{Part~1~记忆化是啥}$

记忆化搜索，就是把已经搜到的状态开个数组记录下来，再次搜的时候直接返回。

举个例子：dfs 求斐波那契数列。

众所周知：

$$F_n = \left\{\begin{aligned} 1 \space (n \le 2) \\ F_{n-1}+F_{n-2} \space (n\ge 3) \end{aligned}\right.$$

所以很好写：

```cpp
int f(int n)
{
   if(n<=2)return 1;
   else return f(n-1)+f(n-2);
}
```
现在调用 `f(5)` 看看搜索树是怎样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/7g6cqd1k.png)

发现了什么：

![](https://cdn.luogu.com.cn/upload/image_hosting/7wtnwqov.png)

相同函数有多次重复调用，这个计算花的时间就是浪费的。

可以怎么办呢？

记忆化呀。

开一个数组 `re[]={0}` 记录下来搜过的状态。

```cpp
int f(int n)
{
   if(re[n]!=0)return re[n];
   if(n<=2)return re[n]=1;//等价于 re[n]=1;return re[n]; 下同。
   else return re[n]=f(n-1)+f(n-2);
}
```

这样搜索树就会好多了：

![](https://cdn.luogu.com.cn/upload/image_hosting/19hqa4d4.png)

$\texttt{Part~2~记忆化咋写}$

把上面的 dfs 扒下来：

```cpp
void dfs(int x,int y,int time)
{
	if(time>t)return ;
	if(time==t)
	{
		if(x==r2&&y==c2)
		{
			ans++;
			return ;
		}
		else return ;
	}
	for(int i=0;i<4;i++)
	{
		if(b[x+dx[i]][y+dy[i]]||x+dx[i]<1||x+dx[i]>n||y+dy[i]<1||y+dy[i]>m)continue;
		dfs(x+dx[i],y+dy[i],time+1);
	}
}
```
注意到 `dfs` 是 `void` 类型的，借助全局变量统计答案。把它改成另一种写法：`int` 型，用返回值返回答案。

```cpp

int dfs(int x,int y,int time)
{
	if(time>t)return 0;
	if(time==t)
	{
		if(x==r2&&y==c2)return 1;
		else return 0;
	}
	int ans=0;
	for(int i=0;i<4;i++)
	{
		if(b[x+dx[i]][y+dy[i]]||x+dx[i]<1||x+dx[i]>n||y+dy[i]<1||y+dy[i]>m)continue;
		ans+=dfs(x+dx[i],y+dy[i],time+1);
	}
	return ans;
}
```

然后定义一个记忆化数组 `re[x][y][t]`，初始值都为 $-1$。


表示 `dfs(x,y,t)` 的值，也就是花了 $t$ 秒走到 $(x,y)$ 的方案数。

搜的时候加入发现搜过就直接返回。

```cpp
if(re[x][y][time]!=-1)return re[x][y][time];
```
然后再每个 dfs 算出答案的时候记录即可。

code:

```cpp
int dfs(int x,int y,int time)
{
	if(re[x][y][time]!=-1)return re[x][y][time];
	if(abs(x-r2)+abs(y-c2)>t-time)return re[x][y][time]=0;
	if(time>t)return re[x][y][time]=0;
	if(time==t)
	{
		if(x==r2&&y==c2)return re[x][y][time]=1;
		else return re[x][y][time]=0;
	}
	int ans=0;
	for(int i=0;i<4;i++)
	{
		if(b[x+dx[i]][y+dy[i]]||x+dx[i]<1||x+dx[i]>n||y+dy[i]<1||y+dy[i]>m)continue;
		ans+=dfs(x+dx[i],y+dy[i],time+1);
	}
	return re[x][y][time]=ans;
}
```
别走，还没结束。~~还没点赞呢~~。

$\texttt{Part~3~复杂度分析}$

dfs 复杂度 $=$ 节点个数 $\times$ 一次递归复杂度。

一次递归复杂度是 $O(1)$。

因为每个 `re[x][y][t]` 至多计算一次，所以节点个数是 $O(nmt)$。

复杂度 $O(nmt)$。

但假如不记忆化，

一次递归复杂度还是 $O(1)$。

但因为没有记忆化，节点个是深为 $t$ 的满 $4$ 叉树 $=\dfrac{(4^t-1)}{3}$ 也就是 $O(4^t)$ 。

记忆化还是很有用的。

$\texttt{Part~4~code}$



```cpp
////////////////////////
///////////////////////
//////////////////////
/////////////////////
/////Author/////////
//////zyh//////////
//////////////////
/////////////////
////////////////
///////////////
//////////////
/////////////
////////////
#include<bits/stdc++.h>
#define EL putchar('\n')
#define SP putchar(' ')
using namespace std;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
int n,m,t,r1,c1,r2,c2;
bitset<108>b[108];
int re[108][108][20];
int dfs(int x,int y,int time)
{
	if(re[x][y][time]!=-1)return re[x][y][time];
	if(abs(x-r2)+abs(y-c2)>t-time)return re[x][y][time]=0;
	if(time>t)return re[x][y][time]=0;
	if(time==t)
	{
		if(x==r2&&y==c2)return re[x][y][time]=1;
		else return re[x][y][time]=0;
	}
	int ans=0;
	for(int i=0;i<4;i++)
	{
		if(b[x+dx[i]][y+dy[i]]||x+dx[i]<1||x+dx[i]>n||y+dy[i]<1||y+dy[i]>m)continue;
		ans+=dfs(x+dx[i],y+dy[i],time+1);
	}
	return re[x][y][time]=ans;
}
int main()
{
	cin>>n>>m>>t;
	memset(re,-1,sizeof(re));
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=0;j<m;j++)
		{
			if(s[j]=='*')b[i][j+1]=1;
		}
	}
	cin>>r1>>c1>>r2>>c2;
	cout<<dfs(r1,c1,0)<<endl;
 	return 0;
}

```

$\texttt{Part~5~一些后话}$

其实记忆化和 dp 是有亿点点像的。




求赞![qq_emoji: qq](https://xn--9zr.tk/qq) 。


---

## 作者：communist (赞：35)

## 搜索
不知道为什么没有人写bfs

觉得挺像是标准个bfs的
### 状态
### 因为要统计次数，不能简单地跳过一个被经过的点
### 这样的话，状态量会爆炸
### 采用记忆化
#### 设$dp[i][j][k]$表示在第$k$分钟到达点$(i,j)$的方案数
#### 以地点+时间作为状态
#### 避免同一状态被反复拓展
#### 这样，状态量将减少至最多$100*100*15$
### 转移
### ~~这就比较显然了~~
#### 对于将被拓展的状态，在计数时加上当前状态的方案数
#### 如果这个状态曾被拓展，就不要别的操作了
#### 否则，将这一状态入队，预备拓展其他状态
代码是这样的：
```
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct node{
    int x,y,s;	//x、y表示坐标，s表示时间
};
queue<node>q;
int n,m,t,r1,c1,r2,c2,dp[110][110][20];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};	//移动
string s[110];
int main()
{
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++)
        cin>>s[i];
    cin>>r1>>c1>>r2>>c2;
    dp[r1][c1][0]=1;	//初始方案数为1
    q.push(node{r1,c1,0});
    while(!q.empty())
    {
        node u=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            node th;
            th.x=u.x+dx[i];
            th.y=u.y+dy[i];
            th.s=u.s+1;
            if(dp[th.x][th.y][th.s])
            {
                dp[th.x][th.y][th.s]+=dp[u.x][u.y][u.s];
                continue;	//当前状态曾被拓展
            }
            if(th.x<1||th.x>n||th.y<1||th.y>m||s[th.x][th.y-1]=='*'||th.s>t)
                continue;	//越界或不能走或超时，跳过
            dp[th.x][th.y][th.s]+=dp[u.x][u.y][u.s];	//计数
            q.push(th);
        }
    }
    cout<<dp[r2][c2][t]<<endl;
    return 0;
}
```

---

## 作者：天南地北 (赞：18)

## 正解：动态规划
#### 这道题是可以用搜索的方式AC
#### 但动态规划的方法更~~难打~~好打，也好理解。
## 那怎么动态规划呢
#### 在$1$秒内，对于第$i$行第$j$列的到达方案数为上下左右的和。
#### 我们这里可以用$-1$表示树。
#### 但是，如果周围有树，只能加没有树的一边。
#### 例如(我们这里用a数组表示)：
```
0 0  0 0 0 0 0
0 0 -1 0 0 0 0
0 0  0 0 0 0 0
0 0  0 0 0 0 0 
```
#### 那么，对于$i=3$,$j=4$的时候，只能增加左，下，右的方案数
#### 注意，整个过程用两个数组操作，$b$数组为这一秒后的方案数，注意，每次计算都要先清$0$。最后在赋值到$a$数组。
## 这是代码：
```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>//头文件
using namespace std;
const int maxn=100+10;
int n,m,t;
int a[maxn][maxn],b[maxn][maxn];
char ch;
int x,y,mbx,mby;
void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
void print(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}
int main()
{
    read(n),read(m),read(t);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
        	cin>>ch;
        	if(ch=='*')a[i][j]=b[i][j]=-1;//这是树的情况
        }
    cin>>x>>y>>mbx>>mby;
    a[x][y]=b[x][y]=1;//初始化
    for(int k=1;k<=t;k++)
    {
    	for(int i=1;i<=n;i++)
    	    for(int j=1;j<=m;j++)
    	       if(a[i][j]!=-1)
    	       {
    	       	b[i][j]=0;
    	       	if(a[i-1][j]!=-1)b[i][j]+=a[i-1][j];
    	       	if(a[i+1][j]!=-1)b[i][j]+=a[i+1][j];
    	        if(a[i][j-1]!=-1)b[i][j]+=a[i][j-1];
    	        if(a[i][j+1]!=-1)b[i][j]+=a[i][j+1];
			   }//判断树的情况，不是树才能加
		for(int i=1;i<=n;i++)
    	    for(int j=1;j<=m;j++)
    	        a[i][j]=b[i][j];//最后的赋值
    }
    cout<<a[mbx][mby];
    return 0;
}
```
ps：这篇题解一定要过啊

---

## 作者：ta3b (赞：10)

这题可以做成相当简单的dp。

f[i,j,k]=时间为i，坐标为j，k的方案数。（f[i,j,k]当然不能为障碍物）

**对于f[i,j,k]=**

**f[i-1,j-1,k]+f[i-1,j+1,k]+f[i-1,j,k-1]+f[i-1,j,k+1]。**

**（上一秒的上下左右相加）**
```pascal
var
        map:array [1..100,1..100] of longint;
        f:array [0..15,1..100,1..100] of longint;
        n,m,t,x1,x2,y1,y2,i,j,k:longint;
        ch:char;
begin
        fillchar(f,sizeof(f),0);
        readln(n,m,t);
        for i:=1 to n do
        begin
                for j:=1 to m do
                begin
                        read(ch);
                        if ch='*' then map[i,j]:=1;
                end;
                readln;
        end;
        readln(x1,y1,x2,y2);
        f[0,x1,y1]:=1;//初值
        for i:=1 to t do
                for j:=1 to n do
                        for k:=1 to m do
                                if map[j,k]<>1 then
                                begin
                                        f[i,j,k]:=f[i-1,j-11,k]+f[i-1,j+1,k]+f[i-1,j,k-1]+f[i-1,j,k+1];//动态方程
                                end;
        
        writeln(f[t,x2,y2]);//答案
end.

```

---

## 作者：月下萤火 (赞：9)

## 记忆化搜索  
对于萌新来说，个人还是觉得记忆化搜索的思路比较好理解，相当于其他方法比较“朴实"  
搜索的题目一般可以先写个朴素的写法，即暴力查找，然后再进行修改，相当于有一个过渡的过程。  


------------
其实就是一个深度优先搜索的过程，从起点到终点，只不过加了一个时间的限制，具体的不再赘述，我的代码应该还算写的比较朴实的，所以很容易看懂吧！  

------------

20分朴素写法:  
```c
#include<iostream>
#include<cstring>

using namespace std;

const int N=110;

char g[N][N];
int n,m,t;
int r1,c1,r2,c2;
int ans=0;

int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};

void dfs(int x,int y,int t){//对四个方向进行搜索,统计合法时间内的方案 
	if(t<0)	return;
	if(x==r2&&y==c2){
		ans++;
		return;
	}
	int mx,my;
	for(int i=0;i<4;i++){
		mx=x+dx[i];
		my=y+dy[i];
		if(mx>=0&&mx<n&&my>=0&&my<m&&g[mx][my]!='*')	dfs(mx,my,t-1);
	}
}

int main(){
	cin>>n>>m>>t;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>g[i][j];
	cin>>r1>>c1>>r2>>c2;
	r2--;c2--;//注意匹配下标 
	dfs(r1-1,c1-1,t);
	cout<<ans;
}
```
------------
100分-记忆化搜索  
考虑加入记忆化数组，其实就是省去重复的计算，详细见代码

------------

```c
#include<iostream>
#include<cstring>

using namespace std;

const int N=110;

char g[N][N];
int n,m,t;
int r1,c1,r2,c2;
int f[N][N][N];//f[x][y][t]表示以(x,y)为起点,在时间为t时可以到达终点的路线数 

int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};

int dfs(int x,int y,int t){
	if(f[x][y][t]!=-1)	return f[x][y][t];
	if(t==0){//注意关注t的在f数组中的意义 
		if(x==r2&&y==c2)	return f[x][y][t]=1;
		return f[x][y][t]=0;
	}
	int mx,my;
	int tmp=0;
	for(int i=0;i<4;i++){
		mx=x+dx[i];
		my=y+dy[i];
		if(mx>=0&&mx<n&&my>=0&&my<m&&g[mx][my]!='*')	tmp+=dfs(mx,my,t-1);
	}
	return f[x][y][t]=tmp;
}

int main(){
	cin>>n>>m>>t;
	memset(f,-1,sizeof f);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>g[i][j];
	cin>>r1>>c1>>r2>>c2;
	r2--;c2--;
	cout<<dfs(r1-1,c1-1,t);
}
```


------------

对比两个代码可以知道，其实差别并不大，但朴素写法肯定是最好写的，在朴素代码的基础上构思记忆化的方法则容易得多



---

## 作者：湖里的杭 (赞：7)

# 优化是循序渐进的

即将联(tui)赛(yi)的蒟蒻来水一篇题解

看到此题的第一眼就想到了：
## 大暴力（MLE    40)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,sx,sy,ex,ey,ans=0;
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};
char s[109][109];
struct node
{
	int x,y,step;
}u,v;queue<node>q;
void bfs()
{
	q.push(node{sx,sy,0});
	while(!q.empty())
	{
		u=q.front();q.pop();
		for(register int i=1;i<=4;i++)
		{
			v.x=u.x+dx[i];v.y=u.y+dy[i];v.step=u.step+1;
			if(v.x<1 || v.x>n || v.y<1 || v.y>m) continue;
			if(s[v.x][v.y]=='*') continue;
			if(v.step>t) continue;
			if(v.step==t && !(v.x==ex && v.y==ey)) continue;
			if(v.step==t && v.x==ex && v.y==ey)
			{
				ans++;
				continue;
			}
			q.push(v);
		}
	}
}
int main()
{
	cin>>n>>m>>t;
	for(register int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	cin>>sx>>sy>>ex>>ey;
	bfs();
	cout<<ans<<endl;
	return 0;
}
```

之后，我们发现，**对于一个状态而言，如果他到终点的距离大于他剩下的时间，那么它应被舍去**


于是就有：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,sx,sy,ex,ey,ans=0;
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};
char s[109][109];
struct node
{
    int x,y,step;
}u,v;queue<node>q;
void bfs()
{
    q.push(node{sx,sy,0});
    while(!q.empty())
    {
        u=q.front();q.pop();
        //printf("%d %d %d",u.x,u.y,u.step);system("pause");
        for(register int i=1;i<=4;i++)
        {
            v.x=u.x+dx[i];v.y=u.y+dy[i];v.step=u.step+1;
            if(v.x<1 || v.x>n || v.y<1 || v.y>m) continue;
            if(s[v.x][v.y]=='*') continue;
            if(abs(v.x-ex)+abs(v.y-ey)>t-v.step) continue;
            //这一步尚待优化，abs所求不一定正确
            //(但优化后还是过不了QwQ)
            if(v.step==t && v.x==ex && v.y==ey)
            {
                ans++;
                continue;
            }
            q.push(v);
        }
    }
}
int main()
{
    cin>>n>>m>>t;
    for(register int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    cin>>sx>>sy>>ex>>ey;
    bfs();
    cout<<ans<<endl;
    return 0;
}
```

## MLE   90

### 还是不够优！

------------
~~这里有个小优化，大佬不想看可略去~~

因为有 墙 的存在，所以abs所求的值比实际要小，可以预处理一遍bfs求出终点到各点的实际距离，这样可以减去更多的枝。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,sx,sy,ex,ey,ans=0,dis[109][109];
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};
char s[109][109];
struct node
{
    int x,y,step;
}u,v;queue<node>q;
void pre_bfs()//对距离进行预处理
{
    q.push(node{ex,ey,0});
    memset(dis,-1,sizeof(dis));dis[ex][ey]=0;
    while(!q.empty())
    {
        u=q.front();q.pop();
        for(register int i=1;i<=4;i++)
        {
            v.x=u.x+dx[i];v.y=u.y+dy[i];v.step=u.step+1;
            if(v.x<1 || v.x>n || v.y<1 || v.y>m) continue;
            if(dis[v.x][v.y]!=-1) continue;
            q.push(v);
            dis[v.x][v.y]=v.step;
        }
    }
}
void bfs()
{
    while(!q.empty()) q.pop();
    q.push(node{sx,sy,0});
    while(!q.empty())
    {
        u=q.front();q.pop();
        for(register int i=1;i<=4;i++)
        {
            v.x=u.x+dx[i];v.y=u.y+dy[i];v.step=u.step+1;
            if(v.x<1 || v.x>n || v.y<1 || v.y>m) continue;
            if(s[v.x][v.y]=='*') continue;
            if(dis[v.x][v.y]>t-v.step) continue;
            if(v.step==t && v.x==ex && v.y==ey)
            {
                ans++;
                continue;
            }
            q.push(v);
        }
    }
}
int main()
{
    cin>>n>>m>>t;
    for(register int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    cin>>sx>>sy>>ex>>ey;
    pre_bfs();
    bfs();
    cout<<ans<<endl;
    return 0;
}
```

~~但还是没过~~



------------

我们会发现，MLE的本质原因在于**重复的状态**过多导致队列过大，而重复的状态本身并没有意义，我们用f[i][j][k]表示走到（i,j）这个点，时间为t的情况数（有点类似于记搜）。这样便达到了去重的目的。


#### AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,sx,sy,ex,ey,ans=0,dis[109][109],f[109][109][20];
//							记录距离		记忆化
int dx[5]={0,1,-1,0,0};//方向数组
int dy[5]={0,0,0,1,-1};
char s[109][109];
struct node
{
    int x,y,step;
}u,v;queue<node>q;
void pre_bfs()//预处理，其实在这里直接用abs也没有关系
{
    q.push(node{ex,ey,0});
    memset(dis,-1,sizeof(dis));dis[ex][ey]=0;
    while(!q.empty())
    {
        u=q.front();q.pop();
        for(register int i=1;i<=4;i++)
        {
            v.x=u.x+dx[i];v.y=u.y+dy[i];v.step=u.step+1;
            if(v.x<1 || v.x>n || v.y<1 || v.y>m) continue;
            if(dis[v.x][v.y]!=-1) continue;
            q.push(v);
            dis[v.x][v.y]=v.step;
        }
    }
}
void bfs()
{
    while(!q.empty()) q.pop();
    q.push(node{sx,sy,0});
    memset(f,0,sizeof(f));f[sx][sy][0]=1;
    while(!q.empty())
    {
        u=q.front();q.pop();
        for(register int i=1;i<=4;i++)
        {
            v.x=u.x+dx[i];v.y=u.y+dy[i];v.step=u.step+1;
            if(v.x<1 || v.x>n || v.y<1 || v.y>m) continue;
            if(s[v.x][v.y]=='*') continue;
            if(dis[v.x][v.y]>t-v.step) continue;//剪枝
            f[v.x][v.y][v.step]+=f[u.x][u.y][u.step];//计算结果数
            if(f[v.x][v.y][v.step]-f[u.x][u.y][u.step]>0) continue;
            //去重
            q.push(v);
        }
    }
}
int main()
{
    cin>>n>>m>>t;
    for(register int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    cin>>sx>>sy>>ex>>ey;
    pre_bfs();
    bfs();
    cout<<f[ex][ey][t]<<endl;//输出答案
    return 0;
}
```

# 再优化
## DP

### 记忆化是一定可以转为DP的。

~~这里当做附加题，请同学们自行完成~~


完，求过

---

## 作者：_ztyqwq (赞：5)

这个题考试的时候直接打dfs，[原地爆炸](https://www.luogu.org/record/show?rid=7145020)。

考完才想到正解——

# dp

用dp[i][j][k]表示用k秒走到(i,j)处的方案总数，状态转移方程：

dp[i][j][k]=dp[i][j-1][k-1]+dp[i][j+1][k-1]+dp[i-1][j][k-1]+dp[i+1][j][k-1];

边界为dp[r1][c1][0]=1;

## 注意要先枚举k再枚举i和j。

## 还有一个坑点：题目说是在T秒**内**，实际上就是**刚好**T秒。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool g[101][101];
unsigned long long dp[102][102][16];
int main()
{
	int n,m,t,r1,c1,r2,c2;
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=1;j<=m;j++)
			g[i][j]=(s[j-1]=='.');
	}
	cin>>r1>>c1>>r2>>c2;
	dp[r1][c1][0]=1;
	for(int i=1;i<=t;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=m;k++)
				if(!g[j][k])
					dp[j][k][i]=0;
				else
					dp[j][k][i]=dp[j][k-1][i-1]+dp[j][k+1][i-1]+dp[j-1][k][i-1]+dp[j+1][k][i-1];
	cout<<dp[r2][c2][t]<<endl;
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：2)

暴搜+剪枝

剪枝：

//1：如果当前位置到达终点的最短距离加上已经走过的时间大于 $T$ ，那么直接return

实现方法就是先跑一遍bfs，算出 $mindis_{x,y}$ 即 $(R_2,C_2)$ 到每个 $(x,y)$ 的最短距离

//2：如果当前走了 $T-1$ 秒了，那么可以直接判断当前位置的 $mindis$ 是不是 1，如果是就答案+1，否则就不加。没有必要走到 $T$ 秒的时候再判断。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int dir[4][2]={1,0,0,1,-1,0,0,-1};
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int Ex,Ey;
int n,m,t,ans;
char G[150][150];
int mindis[150][150],nomore[150][150];
inline void bfs(int Sx,int Sy)
{
	memset(mindis,0x3f,sizeof mindis);
	mindis[Sx][Sy]=0;
	queue<pair<int,int> > Q;
	Q.push(make_pair(Sx,Sy));
	while(!Q.empty())
	{
		reg pair<int,int> now=Q.front();Q.pop();
		for(int i=0;i<4;++i)
		{
			reg int nx=now.first+dir[i][0];
			reg int ny=now.second+dir[i][1];
			if(G[nx][ny]=='*'||mindis[nx][ny]!=0x3f3f3f3f)
				continue;
			mindis[nx][ny]=mindis[now.first][now.second]+1;
			Q.push(make_pair(nx,ny));
		}
	}
	return;
}
inline void dfs(int x,int y,int step)
{
	if(step==t-1)
	{
		if(mindis[x][y]==1)
			++ans;
		return;
	}
	for(int i=0;i<4;++i)
	{
		reg int nx=x+dir[i][0];
		reg int ny=y+dir[i][1];
		if(step+mindis[nx][ny]+1>t)
			continue;
		dfs(nx,ny,step+1);
	}
	return;
}
signed main(void)
{
	int Sx,Sy;
	cin>>n>>m>>t;
	for(int i=1;i<=n;++i)
		cin>>(G[i]+1);
	for(int i=0;i<=n+1;++i)
		G[i][0]=G[i][m+1]='*';
	for(int i=0;i<=m+1;++i)
		G[0][i]=G[n+1][i]='*';
	cin>>Sx>>Sy>>Ex>>Ey;
	bfs(Ex,Ey);
	dfs(Sx,Sy,0);
	cout<<ans<<endl;
	return 0;
}
```





---

## 作者：源氏可以吃吗 (赞：2)

### 题目大意
计算在限定步数内，所有可以达到的坐标点。
### 解法
BFS无敌，~~还不是老师让我们全用BFS和暴力模拟解题目~~。
### 难点
不能简单地用哈希判重，容易超时。
### 解题思路
建一个bool数组判定当前位置是否在队列中以此来进行判重。
### 直接放代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Point
{
	int x, y, step, num;
};//定义结构体
Point q[4000010], s, t;//队列尽量开大一些，避免爆栈
int f = 1, e = 0;
int n, m, lmt;
char g[110][110];
int detx[4]={1,-1,0,0};
int dety[4]={0,0,-1,1};//移动方向
int ans = 0;
bool inq[101][101];//记录是否在队列中
int pot[101][101];
int main()
{
	memset(inq, 0, sizeof(inq));//这是个好习惯
	cin >> n >> m >> lmt;
	for (int i = 0; i < n; i++)
		scanf ("%s", g[i]);
	cin >> s.x >> s.y >> t.x >> t.y;
	s.x--,s.y--,t.x--,t.y--;
	s.step = 0, s.num = 1;
	inq[s.x][s.y] = 1;
	pot[s.x][s.y] = 1;
	q[++e] = s;//初始化ing...
	while ( f <= e )
	{
		Point u = q[f++];
		inq[u.x][u.y] = 0;
		for (int i = 0; i < 4; i++)
		{
			Point v;
			v.x = u.x + detx[i];
			v.y = u.y + dety[i];
			v.step = u.step + 1;
			v.num = u.num;
			if (v.x < 0 || v.x >= n || v.y < 0 || v.y >= m) continue;//是否越界
			if (g[v.x][v.y] == '*') continue;//是否撞树
			if (v.x == t.x && v.y == t.y && v.step == lmt)
			{
				ans = ans + v.num;
			}//如果符合条件，答案加1
			if (v.step >= lmt)
				continue;//判定步数
			if (inq[v.x][v.y] == 0)
			{
				q[++e] = v;
				inq[v.x][v.y] = 1;
				pot[v.x][v.y] = e;
			}//如果此点不在队列中
			else 
			{
				q[pot[v.x][v.y]].num += v.num;
			}//如果此点已经做过了，将两个点的方法数量合并
		}
	}
	cout << ans << endl;
	return 0;
}

```


---

## 作者：炽凤羽招 (赞：1)

首先我们会发现一件事：

某点在t秒时能到达的方法等于上一秒能到达其周围四个方向方法的和。

如果用ways[x][y]数组表示在t秒内能达到的方法数，那么可以得到：

ways[x][y] = ways[x - 1][y] + ways[x + 1][y] + ways[x][y - 1] + ways[x][y + 1]。

举个栗子吧，一个5 * 5没有障碍的地图，奶牛在中间，我们暴力下

0 0 0 0 0

0 0 1 0 0

0 1 0 1 0

0 0 1 0 0

0 0 0 0 0

这是第一秒的情况。

0 0 1 0 0

0 2 0 2 0

1 0 4 0 1

0 2 0 2 0

0 0 1 0 0

这是第二秒，可能还有些人没看出什么，我们再来第三秒

0 3 0 3 0

3 0 9 0 3

0 9 0 9 0

3 0 9 0 3

0 3 0 3 0

总结一下！！！

如果我们能在第t秒时有方法到达这一个点，那么在t + 1秒时就一点没有方法到达这一个点。

那么我们可以推导出：如果在该秒内能到达这个点的方法大于零，那么它周围的四个点在该秒内无法到达。（不信可以自己手推）

那么由此我们可以得到，若要知晓某一个时间内某一地点的方法数，只要知道上一秒他四周的方法数，再只要知晓上上秒内的……这就是一个递归的过程。

但是我们在代码中要实现的是递推，从一开始建立一个初始化的地图，然后将第一个点推入队列，推出它周围四个点的方式数，并将这四个点推入队列，再一个个扫描这四个点，将这四个点周围的点推入……

接下来是代码实现。

首先我们考虑利用队列进行宽搜

建立一个结构体

    struct node
    {
	    int x;//表示横坐标    
    	int y;//表示纵坐标
    	int s;//若s为0,则可以走 
    	int step;//表示这是第几秒
        int ways;//表示到达这个点时的方法	
    }p[105][105];

有人可能看得比较迷，没关系我们慢慢来。

要进行推导，首先要初始化（输入就省略不讲了，详见代码）。


    for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			cin>>c;
			if(c == '.') p[i][j].s = 0;//可以走
			if(c == '*') p[i][j].s = 1;//不能走
			p[i][j].x = i;//横坐标
			p[i][j].y = j;//纵坐标
			p[i][j].step = -1;//初始化
			p[i][j].ways = 0;//没有记录
		}
	}
    p[r1][c1].step = 0;
	if(r1 + 1 <= n and p[r1 + 1][c1].s == 0)
	{
		p[r1 + 1][c1].ways = 1;
		
	}
	if(r1 - 1 > 0 and p[r1 - 1][c1].s == 0)
	{
		p[r1 - 1][c1].ways = 1;
	}
	if(c1 - 1 > 0 and p[r1][c1 - 1].s == 0)
	{
		p[r1][c1 - 1].ways = 1; 
	}
	if(c1 + 1 <= m and p[r1][c1 + 1].s == 0)
	{
		p[r1][c1 + 1].ways = 1;
	}
    
作图的话就是

0 1 0

1 0 1

0 1 0

我们可以发现一件事，在这里我是直接记录了1，而没有将时间加一，为什么呢？很简单。

首先我们建立一个队列，并推入第一个元素

    queue<node>kk;
    kk.push(p[r1][c1]);
    
当进行宽搜时，我们会发现第一个操作的元素它的原本赋值是0，所以向四周增加时不会做出任何改变。

接下来进行宽搜（我的代码很长，不想看就直接跳到下面的讲解）

    while(!kk.empty())
	{
		node tmp = kk.front();
		kk.pop();
		if(tmp.step >= t)break;
	//	cout<<tmp.x<<" "<<tmp.y<<endl;
		if(tmp.x - 1 > 0 and p[tmp.x - 1][tmp.y].s == 0)
		{
			ways[tmp.x - 1][tmp.y] += ways[tmp.x][tmp.y];
		}
		if(tmp.x + 1 <= n and p[tmp.x + 1][tmp.y].s == 0)
		{
			ways[tmp.x + 1][tmp.y] += ways[tmp.x][tmp.y];
			
		}
		if(tmp.y - 1 >= 0 and p[tmp.x][tmp.y - 1].s == 0)
		{
			ways[tmp.x][tmp.y - 1] += ways[tmp.x][tmp.y];
		}
		if(tmp.y + 1 <= m and p[tmp.x][tmp.y + 1].s == 0)
		{
			ways[tmp.x][tmp.y + 1] += ways[tmp.x][tmp.y];
		}
		if(inq[tmp.x - 1][tmp.y] == false and tmp.x - 1 > 0 and p[tmp.x - 1][tmp.y].s == 0)
		{
			p[tmp.x - 1][tmp.y].step = tmp.step + 1;
			kk.push(p[tmp.x - 1][tmp.y]);
			inq[tmp.x - 1][tmp.y] = true;
		}
		if(inq[tmp.x + 1][tmp.y] == false and tmp.x + 1 <= n and p[tmp.x + 1][tmp.y].s == 0)
		{
			p[tmp.x + 1][tmp.y].step = tmp.step + 1;
			kk.push(p[tmp.x + 1][tmp.y]);
			inq[tmp.x + 1][tmp.y] = true;
		}
		if(inq[tmp.x][tmp.y - 1] == false and tmp.y - 1 > 0 and p[tmp.x][tmp.y - 1].s == 0)
		{
			p[tmp.x][tmp.y - 1].step = tmp.step + 1;
			kk.push(p[tmp.x][tmp.y - 1]);
			inq[tmp.x][tmp.y - 1] = true;
		}
		if(inq[tmp.x][tmp.y + 1] == false and tmp.y + 1 <= m and p[tmp.x][tmp.y + 1].s == 0)
		{
			p[tmp.x][tmp.y + 1].step = tmp.step + 1;
			kk.push(p[tmp.x][tmp.y + 1]);
			inq[tmp.x][tmp.y + 1] = true;
		}
		ways[tmp.x][tmp.y] = 0;
		inq[tmp.x][tmp.y] = false;
		/*
		for(int i = 1;i <= n;i++)
     	{
	    	for(int j = 1;j <= m;j++)
	    	{
	    		cout<<ways[i][j]<<" ";
	    	}
	    	cout<<endl;
    	}
    	cout<<endl;*/
	}
 首先，取出队首，推出（这些基本操作就不讲了）……
 
 我们可以看到每一秒钟中所用需要操作的地方
 
 有人会发现一些奇怪的事情：
 
 1、有一个inq数组不知道干什么用
 
 2、原本在结构体里的ways数组外放了。
 
 如果直接暴力会发现某一个点会被重复推入队列，加大了空间量，容易报错且得不偿失。
 
 所以我们建立一个数组，如果这个点在队列里面，我们就不推入。
 
 但是，即使不推入队列，该有的操作还是要有的，就是要先让它的值加到周围，再进行推入队列的判断，最后清零并清除inq数组的标记。
 
 至于ways数组为什么要外放，因为如果这个数组在结构体里面，那么我们很难对其进行修改（因为推入队列后队列中的ways是固定的，哪怕后面再做出修改也不会影响到队列中的值，就会出错，不信自己去尝试）
 
 当然，如果你足够dalao，用手写队列的话，标记下位置，ways就不用外放了（不会的就当做没看到）
 
 最后就是这个很迷的step了。
 
 我们会神奇地发现每一秒中要操作的点在队列中都是聚在一起的，所以利用推入时 p[tmp.x - 1][tmp.y].step = tmp.step + 1 的写法，就可以控制了。
 
正因为这样，当遇到step和上一个推出的队首的step不同时，说明你已经做完了上一秒的操作，开始了下一秒。

留意一点，因为我们初始化的时候将step初始化为-1，所以判断时是用 step >= t 而不是 step > t。

这样就差不多了。

下附AC代码

    #include<iostream>
    #include<queue>
    #include<cmath>
    #include<cstring>
    #include<algorithm>
    using namespace std;
    int n, m, t;
    char c;
    int r1, c1, r2, c2; 
    bool inq[105][105];
    int ways[105][105];//表示有几种走法 

    struct node
    {
	int x;
	int y;
	int s;//若s为0,则可以走 
	int step;//表示这是第几秒
	
    }p[105][105];

    queue<node>kk;
	
    void bfs()
    {
	while(!kk.empty())
	{
		node tmp = kk.front();
		kk.pop();
		inq[tmp.x][tmp.y] = false;
		if(tmp.step >= t)break;
	//	cout<<tmp.x<<" "<<tmp.y<<endl;
		if(tmp.x - 1 > 0 and p[tmp.x - 1][tmp.y].s == 0)
		{
			ways[tmp.x - 1][tmp.y] += ways[tmp.x][tmp.y];
		}
		if(tmp.x + 1 <= n and p[tmp.x + 1][tmp.y].s == 0)
		{
			ways[tmp.x + 1][tmp.y] += ways[tmp.x][tmp.y];
			
		}
		if(tmp.y - 1 >= 0 and p[tmp.x][tmp.y - 1].s == 0)
		{
			ways[tmp.x][tmp.y - 1] += ways[tmp.x][tmp.y];
		}
		if(tmp.y + 1 <= m and p[tmp.x][tmp.y + 1].s == 0)
		{
			ways[tmp.x][tmp.y + 1] += ways[tmp.x][tmp.y];
		}
		if(inq[tmp.x - 1][tmp.y] == false and tmp.x - 1 > 0 and p[tmp.x - 1][tmp.y].s == 0)
		{
			p[tmp.x - 1][tmp.y].step = tmp.step + 1;
			kk.push(p[tmp.x - 1][tmp.y]);
			inq[tmp.x - 1][tmp.y] = true;
		}
		if(inq[tmp.x + 1][tmp.y] == false and tmp.x + 1 <= n and p[tmp.x + 1][tmp.y].s == 0)
		{
			p[tmp.x + 1][tmp.y].step = tmp.step + 1;
			kk.push(p[tmp.x + 1][tmp.y]);
			inq[tmp.x + 1][tmp.y] = true;
		}
		if(inq[tmp.x][tmp.y - 1] == false and tmp.y - 1 > 0 and p[tmp.x][tmp.y - 1].s == 0)
		{
			p[tmp.x][tmp.y - 1].step = tmp.step + 1;
			kk.push(p[tmp.x][tmp.y - 1]);
			inq[tmp.x][tmp.y - 1] = true;
		}
		if(inq[tmp.x][tmp.y + 1] == false and tmp.y + 1 <= m and p[tmp.x][tmp.y + 1].s == 0)
		{
			p[tmp.x][tmp.y + 1].step = tmp.step + 1;
			kk.push(p[tmp.x][tmp.y + 1]);
			inq[tmp.x][tmp.y + 1] = true;
		}
		ways[tmp.x][tmp.y] = 0;
		inq[tmp.x][tmp.y] = false;
		/*
		for(int i = 1;i <= n;i++)
     	{
	    	for(int j = 1;j <= m;j++)
	    	{
	    		cout<<ways[i][j]<<" ";
	    	}
	    	cout<<endl;
    	}
    	cout<<endl;*/
	}
}

    int main()
    {
	cin>>n>>m>>t;
	memset(inq, false, sizeof(inq));
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			cin>>c;
			if(c == '.') p[i][j].s = 0;
			if(c == '*') p[i][j].s = 1;
			p[i][j].x = i;
			p[i][j].y = j;
			p[i][j].step = -1;
			ways[i][j] = 0;
		}
	}
	cin>>r1>>c1>>r2>>c2;
	/*
	if(t == 0) cout<<0;
	if(t == 1)
	{
		if(abs(r1 - r2) + abs(c1 - c2) == 1) cout<<1;
		else cout<<0;
	}*/
	p[r1][c1].step = 0;
	if(r1 + 1 <= n and p[r1 + 1][c1].s == 0)
	{
		ways[r1 + 1][c1] = 1;
		
	}
	if(r1 - 1 > 0 and p[r1 - 1][c1].s == 0)
	{
		ways[r1 - 1][c1] = 1;
	}
	if(c1 - 1 > 0 and p[r1][c1 - 1].s == 0)
	{
		ways[r1][c1 - 1] = 1; 
	}
	if(c1 + 1 <= m and p[r1][c1 + 1].s == 0)
	{
		ways[r1][c1 + 1] = 1;
	}
	kk.push(p[r1][c1]);
	inq[r1][c1] = true;
	bfs();
	
	cout<<ways[r2][c2];
	return ~~（0-0）;//很皮的操作，两个取反，括号内零减零
} 
 
 
 

---

## 作者：mot1ve (赞：0)

给自己看的。典型BFS。在BFS中，为了防止重复拓展，需要避免把重复的状态压入队列。这道题的状态是由坐标+时间构成的而不是简单的坐标。所以需要三维。此题又要求我们求出方案数，所以遇到重复状态时直接

$f[xx][yy][step+1]+=f[x][y][step]$ 。

有dp那味了。如果不要求方案数的话 $f[xx][yy][step+1]==1$ 的话直接continue。
```
#include<bits/stdc++.h>
using namespace std;
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int n,m,t,sx,sy,fx,fy;
char a[110][110];
int f[110][110][20];//在k时间到达i,j的方案数。坐标+时间作为状态防止重复拓展。 
struct node{
	int x,y,step;
};
queue<node> q;
void bfs(int sx,int sy)
{
    q.push((node){sx,sy,0});
    f[sx][sy][0]=1;
	while(q.size())
	{
		node u=q.front();
		q.pop();
		int x=u.x;
		int y=u.y;
		int step=u.step;
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx<1||yy<1||xx>n||yy>m||a[xx][yy]=='*'||step+1>t)
			continue;
			if(f[xx][yy][step+1])//避免重复拓展
			{
				f[xx][yy][step+1]+=f[x][y][step];
				continue;
			} 
			f[xx][yy][step+1]+=f[x][y][step];
			q.push((node){xx,yy,step+1});
		}
	}	
}
int main()
{
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	cin>>sx>>sy>>fx>>fy;
	bfs(sx,sy);
	cout<<f[fx][fy][t];
	return 0;
}
```

---

## 作者：Sshenyyyu (赞：0)

# 游荡的奶牛
这题呢，可以用记忆化搜索，作为一个不会DP的同学，只能这样做啦，用F[i][j][t]表示在坐标(i,j)上用t秒的路径总数。
贴代码。。。
```
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <iostream>
using namespace std;

const int Maxn=101;

int n,m,t;
char a[Maxn][Maxn];
int ans;
int r,c,r1,c1,f[Maxn][Maxn][Maxn];
int dx[]={1,-1,0,0};
int dy[]={0,0,-1,1};

int dfs_1(int R,int C,int T)//DFS求解
{
	if(f[R][C][T]!=-1) return f[R][C][T];//记忆化，如果当前的状态有解，就返回
	if(T>t) return 0;//如果用的时间大于题目给定的时间，肯定无解，返回0
	if(R==r1&&C==c1&&T==t) return 1;//在满足时间一定的情况下走到了，返回1
	int tmp=0;
	for(int i=0; i<4; i++) {
		int x=dx[i]+R;
		int y=dy[i]+C;
		if(x>=1&&y>=1&&x<=n&&y<=m&&a[x][y]!='*')
			tmp+=dfs_1(x,y,T+1);//标准记忆化
	}
	f[R][C][T]=tmp;
	return f[R][C][T];
}

int main()
{
	memset(f,-1,sizeof(f));
	cin>>n>>m>>t;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cin>>a[i][j];
	cin>>r>>c>>r1>>c1;
	memset(f,-1,sizeof(f));
	cout<<dfs_1(r,c,0)<<endl;//调用函数
	return 0;
}

```

---

## 作者：Patrickpwq (赞：0)

一上来直接二话不说一个dfs 50分到手

然后就开始yy正解了 说实话我一开始还真没想到过河卒这道题（一个月之前才做过）

如果大家没有做过的话 可以去先做一下过河卒（LuoguP1002）



我们开始YY 要求终点的方案数 那就是相当于求终点的上下左右的方案数之和（不用加一）

这样一步一步推下去 我们只要知道每个点的方案数 就可以求出终点的方案数

所以相当于 从一个点开始 它上下左右的点都要加上这个点的方案数

那么 就有dp的初始条件————dp[0][r1][c1]=1

于是我们建立数组 DP[T][N][M] 代表第i秒从起点到当前j,k的路径方案总数

ok了 可以看代码了


```cpp
/*
...*. 
...*. 
..... 
.....
*/
#include<bits/stdc++.h>
using namespace std;
char Map[105][105];
int dirx[5]={0,0,0,-1,1};//上下左右 
int diry[5]={0,1,-1,0,0};
int n,m,t;
int r1,c1,r2,c2;

int dp[20][105][105];

int main()
{
//	freopen("sheep.in","r",stdin); 
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>Map[i][j];
		}
	}
	cin>>r1>>c1>>r2>>c2;
	dp[0][r1][c1]=1;
	for(int i=1;i<=t;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=m;k++)
			{
				for(int p=1;p<=4;p++)
				{
					int newx=j+dirx[p];
					int newy=k+diry[p];
					if(newx<1||newx>n||newy<1||newy>m||Map[newx][newy]=='*')	continue;
					dp[i][j][k]+=dp[i-1][newx][newy];
				}
			}
		}
	}
	cout<<dp[t][r2][c2];
	return 0;
}
```

---

## 作者：Dream_It_Possible (赞：0)

~~我觉得DP都是相通的~~

这题其实就是1002过河卒的超级加强版。

首先搜索四个方向，***判断是否有障碍***，如果没有，就用一种类似和数组的东西累加上一步的值，然后就可以过了。

代码：

```cpp
    #include<cstdio>
    #include<iostream>
    #include<cstring>
    #include<cmath>
    #include<algorithm>
    using namespace std;
    char a[105][105];
    long long xx[5]={0,1,-1,0,0},yy[5]={0,0,0,1,-1};//四个方向
    long long f[105][105][105];//貌似int会WA
    int main()
    {
        long long n,m,time,i,j,k;//貌似int会WA
        cin>>n>>m>>time;
        for (i=1;i<=n;i++)
        {
            for (j=1;j<=m;j++)
            {
                cin>>a[i][j];
            }
        }
        long long s1,s2,e1,e2;
        cin>>s1>>s2>>e1>>e2;//貌似int会WA
        f[s1][s2][0]=1;//初始化
        for (i=1;i<=time;i++)
        {
            for (j=1;j<=n;j++)
            {
                int l;
                for (k=1;k<=m;k++)
                {
                    for (l=1;l<=4;l++)
                    {
                        long long xxx=xx[l]+j;
                        long long yyy=yy[l]+k;
                        if (xxx>=1&&yyy>=1&&xxx<=n&&yyy<=m&&a[xxx][yyy]!='*')//是否有障碍
                        {
                            f[j][k][i]+=f[xxx][yyy][i-1];//累加上一步
                        }
                    }
                }
            }
        }
        cout<<f[e1][e2][time];
        return 0;
}
```

---

## 作者：Dispwnl (赞：0)

终于过了。。。

这题可以用搜索做

但是是记忆化搜索+一点小剪枝

f[i][j][k]表示第k时间到达(i,j)的方案数

推出:f[x][y][k]+=f[x+mv1[i]][y+mv2[i]][k+1]

其中mv1,mv2枚举方向

优化:

1.if(f[x)[y][tot]) return;没啥可说的

2.if(tot>t) return;也好理解

3.if(abs(r2-x)+abs(c2-y)>t-tot) return;

从(x,y)到(r2,c2)不考虑障碍物的情况下最短路肯定是abs(r2-x)+abs(c2-y)(即曼哈顿距离，是叫这个名吗？)

如果剩余时间小于这个数

肯定到不了(r2,c2)

舍掉
看记忆化搜索，多短

```cpp
# include<iostream>
# include<cstdio>
# include<cstring>
# include<cstdlib>
using namespace std;
int n,m,t,r1,c1,r2,c2,ans;
int mv1[4]={1,-1,0,0};
int mv2[4]={0,0,1,-1};
long long f[101][101][21];
char a[101][101];
inline void dfs(int x,int y,int tot)
{
    if(f[x][y][tot]) return;
    if(abs(r2-x)+abs(c2-y)>t-tot) return;
    if(tot>t) return;
    if(x==r2&&y==c2&&tot==t)
    {
        f[x][y][tot]=1;
        return;
    }
    for(int i=0;i<=3;i++)
      {
          int xx=x+mv1[i],yy=y+mv2[i];
          if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]=='*')
        continue;
          dfs(xx,yy,tot+1);
          f[x][y][tot]+=f[xx][yy][tot+1];
      }
}
int main()
{
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++)
        cin>>a[i][j];
    cin>>r1>>c1>>r2>>c2;
    dfs(r1,c1,0);
    cout<<f[r1][c1][0];
    return 0;
}
```

---

## 作者：wuzhoupei (赞：0)

这题虽然简单，但是题解有点少，我来一个递推；

这道题就是一个简单的宽搜；

但是实现的方式不再用队列而已；

不然会很难操作；

所以就变成了递推；

我们令f[i][j][k]代表在(i,j)这个点用k步到达的方式；

这样我想到一道过河卒的题；

那道题也是一个递推；

不过那道题是二维，没有步数限制；

即当前点可以由上下左右四个点中合法的点经过一步走过来；

所以我们可以直接暴力递推就好了；

先判断合不合法；

合法就加过来，否则就换下一个点继续判断；

最后输出目标点目标步数的方式就好了；

至于搜索，我没有写，我觉得那样子不是很有趣；

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define II int
#define C char
#define R register
#define I 105
using namespace std;


II f[I][I][20];
II bx[4]={1,-1,0,0};
II by[4]={0,0,1,-1};

C map[I][I];

II n,m,t,sx,sy,tx,ty;


int main()
{
//    freopen("1.in","r",stdin);
    
    scanf("%d%d%d",&n,&m,&t);
    for(R II i=1;i<=n;i++)
    {
        for(R II j=1;j<=m;j++)
        {
            cin>>map[i][j];
        }
    } 
    scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
    
    f[sx][sy][0]=1;
    for(R II i=1;i<=t;i++)
    {
        for(R II j=1;j<=n;j++)
        {
            for(R II k=1;k<=m;k++)
            {
                if(map[j][k]!='*') for(R II l=0;l<=3;l++)
                {
                    R II x=j+bx[l];
                    R II y=k+by[l];
                    if(x&&y&&x<=n&&y<=m&&map[x][y]!='*') {
                        // 合法，加步数; 
                        f[j][k][i]+=f[x][y][i-1];
                    }
                }
            }
        }
    }
    
    printf("%d\n",f[tx][ty][t]);
    exit(0);
}
```

---

