# 最长的滑雪路径 Longest Run on a Snowboard

## 题目描述

$ben$喜欢滑雪。（以下简叙）在一个$R*C(R,C\leq100)$的整数矩阵上找一条高度严格递减的最长路。起点任意，但每次只能沿着上下左右$4$个方向之一走一格，并且不能走出矩阵外。如图所示，最长路是按照高度$25,24,23,...,2,1$这样走，长度为$25$。矩阵中的数均为$0$~$100$.

## 样例 #1

### 输入

```
2
Feldberg 10 5
56 14 51 58 88
26 94 24 39 41
24 16 8 51 51
76 72 77 43 10
38 50 59 84 81
5 23 37 71 77
96 10 93 53 82
94 15 96 69 9
74 0 62 38 96
37 54 55 82 38
Spiral 5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9```

### 输出

```
Feldberg: 7
Spiral: 25```

# 题解

## 作者：Gorenstein (赞：4)

本题的正解是记忆化搜索（但是有些写法我看不懂），我来发一个更加简单的写法。

#### 2020.10.18 upd：修正了一个锅，并修改了一些表述和排版

------------


首先先考虑暴搜的方法。

1. 定义 $ans$ 记录每一轮答案，$answer$ 记录最终答案；
2. 枚举每个点开始搜索，如果这个点珂以往下，那么令``ans++``；
3. 回溯的时候令``ans--``；
4. 如果四个方向都没有路了，令 $answer=\max(answer,ans)$。

但是这样会非常暴力。因此考虑优化。

------------


重新定义$ans$，**使用 $ans_{i,j}$ 表示到达位置 $(i,j)$ 的时候的最优解**。那么如果从当前位置能向四个方向走，那么令 

$$
ans_{i+dir1_k,j+dir2_k}=\max(ans_{i+dir1_k,j+dir2_k},ans_{i,j}+1)\quad(k=1,2,3,4)
$$

因此这个问题转化为了类似于求解二维的最长下降子序列的问题。

使用 $ans_{i,j}$ 记录之后，我们发现其实当从一个位置像四个方向搜索的时候，**如果当前位置的最优解$+1$小于等于要搜索的下一个位置的值，就没必要搜索了，执行最优性剪枝**。

有了这个优化，就可以AC此题了。（在滑雪那题里记搜和这个都写过，此方法稍微慢一些）

------------


总体过程如下：
1. 初始化$ans$数组为全1
2. 枚举所有位置，假设现在的位置为$(i,j)$，开始搜索：
   - 向四个方向搜索，如果$ans_{i+dir1_k,j+dir2_k}<ans_{i,j}+1$，则向那个方向搜索并更新那个方向的$ans$；
   - 其他有2种情况：一种是那个方向无法向下滑；另一种是向那个方向划没有比原先的路径更优。这两种情况都不用搜索，剪枝。
3. 搜索完成之后，令最终答案为
   $$
   \max\limits_{1\leq i\leq n,1\leq j\leq m}(ans_{i,j})
   $$
   
然后就好了。

有动态规划思想。

```cpp
int r,c,a[105][105],ans[105][105],i,j,maxn,n;
int dir1[5]={0,-1,1,0,0},dir2[5]={0,0,0,1,-1};
//表示当前搜索到了第x行第j列 
void search(int x,int y)
{
	for(int i=1;i<=4;i++)
		//第一个条件判断能否往下滑，第二个判断为剪枝 
		if(a[x+dir1[i]][y+dir2[i]]<a[x][y]&&ans[x][y]+1>ans[x+dir1[i]][y+dir2[i]])
		{
	        ans[x+dir1[i]][y+dir2[i]]=ans[x][y]+1;
	        search(x+dir1[i],y+dir2[i]);
	    }    
}
int main()
{
	cin>>n;
	while(n--)
	{
		char nam[105];
	    for(i=0;i<105;i++)
	        for(j=0;j<105;j++)
	            ans[i][j]=0,a[i][j]=99999;
	            //初始化ans和a数组 
	    maxn=0;
	    cin>>nam;
    	cin>>r>>c;
	    for(i=1;i<=r;i++)
	        for(j=1;j<=c;j++)
			{
	            cin>>a[i][j];
	            ans[i][j]=1;
	        }
	    for(i=1;i<=r;i++)
	        for(j=1;j<=c;j++)
	            search(i,j);
	            //所有起点都搜索一遍 
	    for(i=1;i<=r;i++)
	        for(j=1;j<=c;j++)
	            if(maxn<ans[i][j])
					maxn=ans[i][j];
					//所有终点都判断一遍 
	    cout<<nam<<": "<<maxn<<endl;
	}
    return 0;
}
```

---

## 作者：lzxhdxx (赞：3)

# UVA10285 最长的滑雪路径

这个题目让人一眼看上去……经典的线性dp啊，但是不知道为什么前面全部的四篇题解都写得是记忆化搜索，那我就补一篇新的dp题解吧

### 题意
给定N组数据，每组数据是一个R*C的地图的高度,要找到一条最长的高度严格递减的路径，求这条路径的长度

### 思路
我们先将所有的数据记录在一个一维数组中，然后进行降序排序，从第一个到最后一个点分别进行处理，记录到当前点为止的最长长度，最后遍历记录长度的数组，找到最大值输出即可

状态转移方程：cnt[i]=max(cnt[i],cnt[j]+1)，其他具体做法请看注释

Code:
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#define ri register int

using namespace std;

struct snowboard 
{ 
	int h, x, y; 
	bool operator>(const snowboard a)const//重载大于号排序用
	{
		return h > a.h;
	}
}h[10010];
int T, r, c, cnt[10010], ans = 0, dx[5] = { 0,-1,1,0,0 }, dy[5] = { 0,0,0,-1,1 };
char name[1010];

void Init()
{
	memset(cnt, 0, sizeof(cnt));//数组记得清零
	scanf("%s%d%d", &name, &r, &c);//依次输入名字和长宽
	for (ri i = 1; i <= r; i++)
		for (ri j = 1; j <= c; j++)//输入
			scanf("%d", &h[(i - 1) * c + j].h), h[(i - 1) * c + j].x = i, h[(i - 1) * c + j].y = j;
            //(i-1)*c+j就是当前输入的是第几个数据
	sort(h + 1, h + r * c + 1, greater<snowboard>());//greater是functional里带的函数，用来降序排序
}

bool check(int i1, int i2)
{
	if (h[i1].h < h[i2].h)//后一个要比前一个高
		for (ri i = 1; i <= 4; i++)
			if (h[i1].x + dx[i] == h[i2].x && h[i1].y + dy[i] == h[i2].y)//判断是否相邻
				return true;//相邻返回true
	return false;//不是true就是false
}

void dp()
{
	for (ri i = 1; i <= r * c; i++)//当前点
	{
		cnt[i] = 1;//每个点都是一个长度，刚开始我用memset，结果成了一个很奇怪的数，就只好在这里初始化了
		for (ri j = 1; j < i; j++)//这个点之前的点，即比他高的点
			if (check(i, j))//如果符合条件
				cnt[i] = max(cnt[i], cnt[j] + 1);//取最大值
	}
}

int Find_Answer()
{
	int mmax = 0;//答案
	for (ri i = 1; i <= r * c; i++)
		mmax = max(mmax, cnt[i]);//找到最大长度
	return mmax;//返回最大长度
}

int main()
{
	scanf("%d", &T);
	while (T--)//T组数据
	{
		Init();//输入
		dp();//开始dp
		printf("%s: %d\n", name, Find_Answer());//输出
	}
	return 0;
}
```
特别特别感谢@万万没想到 给我指出了好多错误，刚开始我用cin&快读输入结果蜜汁WA，改用scanf就好了

补一篇新题解，求管理大大给过

---

## 作者：Im_airman (赞：1)

#### 题目
 $N$ 组数据，给出第 $i$ 个人的姓名，矩阵的长 $R$ ,宽 $C$ ,以及滑雪场的 ~~等高线地形图~~ 各个点的高度。求最远可以滑多远。

#### 思路
1. 输入数据。
2. 记忆化搜索（核心）：依次从**每个节点**向下找，取最大值。
3. 输出结果。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110][110],v[110][110],ma[110][110],sum,ans,aans;
int r,c;//矩阵边框
string n;//名字
int dx[4]={0,0,-1,1};//X轴
int dy[4]={-1,1,0,0};//Y轴
int dfs(int x,int y){
	if(ma[x][y]!=0){//如果已经找过了，直接输出
		return ma[x][y];
	}
	else{
		for(int i=0;i<4;i++){//四个方向
			int xx=x+dx[i],yy=y+dy[i];//前进后的坐标
			if(v[xx][yy]==1 || xx<1 || yy<1 || xx>r ||	yy>c || a[x][y]<=a[xx][yy])	continue;//越界或向高处前进就不走
				dfs(xx,yy);//往下找
				ma[x][y]=max(ma[x][y],ma[xx][yy]+1);//存贮搜索结果
			}
		return 	ma[x][y];//返回
	}
	
}
int main(){
	int num;cin>>num;//数据点
	while(num--){
		aans=0,ans=0;
		memset(v,0,sizeof v);
		memset(ma,0,sizeof ma);//不同数据点，要初始化
		
		
		cin>>n>>r>>c;
		for(int i=1;i<=r;i++){
			for(int j=1;j<=c;j++){
				cin>>a[i][j];	
			}
		}//输入
		for(int i=1;i<=r;i++){
			for(int j=1;j<=c;j++){
				ans=dfs(i,j);//从每个节点开始找
				aans=max(aans,ans);//找最大值
			}
		}
		cout<<n<<": "<<aans+1<<endl;//输出
		
	}
	return 0;

}

---

## 作者：璀璨丶凋零 (赞：1)

题意：给出N * N的矩阵，要求找到一条路  径，路径上的值是递减的，求这样的路径的最长长度。

思路：记忆化搜索。因为要求最长的路径那么就需要将所有的这样的路径找出，但是直接dfs会超时的。对于同一个位置，从这个点出发的最长路径长度是固定的。所以在找的时候就要将这个位置的最长路径算出来并且保存下来。一开始还担心会走回头路就是一直兜圈子。但是后面发现能往右走就不可能在从右边的那个位置走回去，因为路径上的值是要求递减的。

    f[i,j] 代表从x，y这个位置开能够走的最长的路径长度。

一道非常经典的记忆化搜索题

上代码

```pascal
const e:array[1..4,1..2] of longint=((-1,0),(1,0),(0,-1),(0,1));//定义一个指标数组分别为上下左右
var a,f:array[1..100,1..100] of longint;
s:string;
max,i,j,k,n,m,t,l:longint;
function sc(x,y:longint):longint;
var i,x1,y1,s:longint;
begin
 if f[x,y]<>0 then exit(f[x,y]);  //记忆化搜索，如果搜过了就直接exit
 s:=1;  //s的初始值要为1，如果高度一样则只有一条跑道
 for i:=1 to 4 do
  begin
   x1:=x+e[i,1];y1:=y+e[i,2];
   if (x1>=1)and(x1<=n)and(y1>=1)and(y1<=m)and(a[x1,y1]<a[x,y]) then  //判断边界条件，而且只能往低的地方滑
     if sc(x1,y1)+1>s then s:=sc(x1,y1)+1;  //往下搜索，找最优解
  end;
 f[x,y]:=s;
 exit(s);
end;
begin
 readln(t);
 for l:=1 to t do
  begin
   max:=0;
   fillchar(f,sizeof(f),0);     
   readln(s);  //c++可以直接用%s法读入
   k:=pos(' ',s);  //开始了坑爹的字符串处理，作为P党的忧伤
   write(copy(s,1,k-1),': ');
   delete(s,1,k);
   k:=pos(' ',s);
   val(copy(s,1,k-1),n);
   delete(s,1,k);
   val(copy(s,1,length(s)),m);
   for i:=1 to n do
    begin
     for j:=1 to m do read(a[i,j]);
     readln;
    end;
    for i:=1 to n do
     for j:=1 to m do
      if f[i,j]=0 then
       begin
        if sc(i,j)>max then max:=sc(i,j);  //记录最优解
        f[i,j]:=sc(i,j);
       end;
    writeln(max);
  end;
end.
```

---

## 作者：Dreamweaver (赞：1)

# 分析
记忆化搜索裸题，P1434的双倍经验。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define maxn 110
#define Orz cout<<"stO %王队% Orz"<<'\n';
int t,n,m,a[maxn][maxn],ans;
string b;
int f[maxn][maxn];
int dfs(int x,int y)
{
	if(f[x][y]!=-1)	return f[x][y];//如果已经搜过了，就直接返回结果
	f[x][y]=1;
	if(x>1&&a[x][y]>a[x-1][y])	f[x][y]=max(f[x][y],dfs(x-1,y)+1);	
	if(x<n&&a[x][y]>a[x+1][y])	f[x][y]=max(f[x][y],dfs(x+1,y)+1);
	if(y>1&&a[x][y]>a[x][y-1])	f[x][y]=max(f[x][y],dfs(x,y-1)+1);
	if(y<m&&a[x][y]>a[x][y+1])	f[x][y]=max(f[x][y],dfs(x,y+1)+1);	//向四面搜索，同时记录结果
	return f[x][y];	
}
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if(ch=='-')f=-1; ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0'; ch=getchar();}
    return x*f;
}
int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
//	printf("%dM\n",(sizeof(dp) >> 20));
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof a);
		memset(f,-1,sizeof f);
		ans=0;//不要忘记初始化 
        cin>>b>>n>>m;
		for(re int i=1;i<=n;++i)
			for(re int j=1;j<=m;++j)
				a[i][j]=read();
		for(re int i=1;i<=n;++i)
			for(re int j=1;j<=m;++j)
				ans=max(ans,dfs(i,j));//每个位置都要搜一遍，想一想，为什么？
		cout<<b<<": "<<ans<<'\n';
	}
	return 0;
}

```


---

## 作者：WanderingTrader (赞：1)

这题就是一个DAG上的记忆化搜索，模板题。  
### 题目分析
这里给大家讲解2个方法，记忆化搜索和dp。  
大家可能会想：这两个不是同一个东西吗？  
还是有区别的，记忆化搜索的基础是递归，dp则是递推，两种算法求解答案的顺序恰好相反。
1. 记忆化搜索  
遍历每个节点，按DFS向外搜索，不过每次记录一下答案，这样总复杂度降到$O(NRC)$，可以说是相当高效了。  
2. dp  
动态规划做法其实就是反着记忆化搜索。与之不同的是，由于递推查找的是数组(而不是记忆化搜索的$F$函数)，为确保所需数据都已计算完毕，递推时需要按高度从小到大计算。  
我们令$dx[4]=\left\{0,0,1,-1\right\},dy[4]=\left\{1,-1,0,0\right\}$，那么易得转移方程：  
$dp_{i,j}=\begin{cases}dp_{i,j}\quad\quad\quad\qquad\qquad\qquad(h_{i,j}<h_{i+dx[k],j+dy[k]})\\\max(dp_{i,j},dp_{i+dx[k],j+dy[k]})(h_{i,j}>h_{i+dx[k],j+dy[k]})\end{cases}$.  
这里$h_{i,j}$表示$(i,j)$的高度。  
公式有点复杂，但是扔给计算机就很简单了。  
由此可见，dp的复杂度也是$O(NRC)$

### 代码1——记忆化搜索
初始化&三要素——大F函数，小f数组，vis数组
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int m[N][N],f[N][N],r,c;
const int dx[5] = {0,1,-1},dy[5] = {0,0,0,1,-1},ans;
bool vis[N][N];
int F(int x,int y)
{
}
int main(){
	int t;
	string s;
	scanf("%d",&t);
	while(t --)
	{
		cin >> s;
		scanf("%d%d",&r,&c);
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++)
				scanf("%d",&m[i][j]);
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++)
			{
				f[i][j] = vis[i][j] = 0;
			}
		ans = -1;
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++)
				ans = max(F(i,j),ans);
		cout << s;
		printf(": %d\n",ans);
	} 
	return 0;
}
```
那么F函数怎么写呢？easy：  
如果已经搜索过，那么直接返回小f数组的答案，否则标记已搜索：
```cpp
if(vis[x][y]) return f[x][y];
vis[x][y] = 1;
```
然后遍历上下左右四个方向，修改答案：
```cpp
for(int i = 1;i <= 4;i ++)
	if(m[x][y] < m[x + dx[i]][y + dy[i]])
		f[x][y] = max(f[x][y],F(x + dx[i],y + dy[i]));	
```
最后把答案加一(算上自己)并返回：
```cpp
return ++ f[x][y];
```
结束了。  
这里有同学可能会有疑问了，这里(指$x+dx[i],y+dy[i]$)下标不会越界吗？  
试想，第一次越界肯定是$0$或$R+1$或$C+1$，这时数组的下标依然存在(这就是把数组开大的好处)，访问到的$m[x][y]$一定是$0$，不比原本的大，因此不会继续递归大F函数，到此为止了，没有越界情况。  

全部代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int m[N][N],f[N][N],r,c,dx[5] = {0,1,-1},dy[5] = {0,0,0,1,-1},ans;
bool vis[N][N];
int F(int x,int y)
{
	if(vis[x][y]) return f[x][y];
	vis[x][y] = 1;
	for(int i = 1;i <= 4;i ++)
		if(m[x][y] < m[x + dx[i]][y + dy[i]])
			f[x][y] = max(f[x][y],F(x + dx[i],y + dy[i]));	
	return ++ f[x][y];
}
int main(){
	int t;
	string s;
	scanf("%d",&t);
	while(t --)
	{
		cin >> s;
		scanf("%d%d",&r,&c);
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++)
				scanf("%d",&m[i][j]);
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++)
			{
				f[i][j] = vis[i][j] = 0;
			}
		ans = -1;
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++)
				ans = max(F(i,j),ans);
		cout << s;
		printf(": %d\n",ans);
	} 
	return 0;
}
```
### 代码2——动态规划
初始化：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int m[N][N],dp[N][N];
const int dx[4] = {1,-1,0,0},dy[4] = {0,0,1,-1};
struct node{
	int x,y;
	bool operator < (const node& a) const
	{
		return m[x][y] > m[a.x][a.y];
	}
};
priority_queue <node> pq;
int main(){
	int t,r,c,n,ans = 0,x,y;
	node k;
	string name;
	cin >> t;
	while(t --)
	{
		n = 1;
		ans = 0;
		cin >> name;
		scanf("%d%d",&r,&c);
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++,n ++)
			{
				scanf("%d",&m[i][j]);
				pq.push((node){i,j});
			}
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++)
				dp[i][j] = 0;
		cout << name;
		printf(": %d\n",ans);
	}
	return 0;
}
```
为了避免用sort(试试就知道，麻烦)，我们用一个优先队列存放坐标，排序的方式非常“奇怪”：和$x,y$没关系，比较的是$m[x][y]$的值，大家可以思考一下这样做的用意。  

输入处理和初始化完成后，我们按$m[x][y]$从小到大的顺序依次操作：
```cpp
while(!pq.empty())
{
	k = pq.top();
	pq.pop();
	x = k.x,y = k.y;
}
```
然后的步骤和记忆化搜索一样，不再赘述：
```cpp
for(int i = 0;i < 4;i ++)
{
if(m[x][y] > m[x + dx[i]][y + dy[i]]) 
	dp[x][y] = max(dp[x][y],dp[x + dx[i]][y + dy[i]]);
}
ans = max(++ dp[x][y],ans);
```
全部代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int m[N][N],dp[N][N];
const int dx[4] = {1,-1,0,0},dy[4] = {0,0,1,-1};
struct node{
	int x,y;
	bool operator < (const node& a) const
	{
		return m[x][y] > m[a.x][a.y];
	}
};
priority_queue <node> pq;
int main(){
	int t,r,c,n,ans = 0,x,y;
	node k;
	string name;
	cin >> t;
	while(t --)
	{
		n = 1;
		ans = 0;
		cin >> name;
		scanf("%d%d",&r,&c);
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++,n ++)
			{
				scanf("%d",&m[i][j]);
				pq.push((node){i,j});
			}
		for(int i = 1;i <= r;i ++)
			for(int j = 1;j <= c;j ++)
				dp[i][j] = 0;
		while(!pq.empty())
		{
			k = pq.top();
			pq.pop();
			x = k.x,y = k.y;
			for(int i = 0;i < 4;i ++)
			{
				if(m[x][y] > m[x + dx[i]][y + dy[i]]) 
					dp[x][y] = max(dp[x][y],dp[x + dx[i]][y + dy[i]]);
			}
			ans = max(++ dp[x][y],ans);
		}
		cout << name;
		printf(": %d\n",ans);
	}
	return 0;
}
```
### 反思与总结
最长雪道问题是DAG上的经典问题，不管是记忆化搜索还是dp，原理都是一样的：化整为零，逐个击破。大家可以好好体会一下。  

$\mathrm{The\ End.}$

---

## 作者：TLMPEX (赞：0)

这道题是个纯记忆化搜索，思路楼上的大佬们都说过了，这里就不说了。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int n,m,k[110][110],f[110][110];
int a[4]={-1,0,0,1},b[4]={0,-1,1,0};//漂移量
int dfs(int x,int y){//记忆化搜索
	if(f[x][y])return f[x][y];//如果访问过了直接返回
	f[x][y]=1;
	for(int i=0;i<4;i++){
		int nx=x+a[i],ny=y+b[i];
		if(nx<=n&&ny<=m&&nx>=1&&ny>=1&&k[nx][ny]<k[x][y])//符合条件取最大值
			f[x][y]=max(f[x][y],dfs(nx,ny)+1);
	}
	return f[x][y];
}
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(f,0,sizeof(f));//初始化
		string name;
		int i,j,z=0;
		cin>>name>>n>>m;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				cin>>k[i][j];
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				z=max(z,dfs(i,j));//取最大值
		cout<<name<<": "<<z<<endl;
	}
}
```


---

## 作者：_caiji_ (赞：0)

此题正解是记忆化搜索，我们先考虑暴力 dfs。

显然，我们可以在 $\operatorname{dfs}$ 中传 $3$ 个参数：$x,y,cnt$，分别表示当前的位置和滑雪路径的长度。每次更新答案，并往另外 $4$ 个点继续搜。
```cpp
void dfs(int x,int y,int cnt){
	ans=Max(ans,cnt);
	for(int i=1;i<=4;i++){
		int tmpx=x+dx[i],tmpy=y+dy[i];
		if(tmpx<1||n<tmpx||tmpy<1||m<tmpy) continue;
		if(a[tmpx][tmpy]>=a[x][y]) continue;
      	//我们可以不标记走过的点，因为你不可能滑下来又滑上去
		dfs(tmpx,tmpy,cnt+1);
	}
}
```
这种方法是正确的，但时间复杂度达到了 $O(4^{nm})$，会 TLE，考虑优化。

不难发现，从一个点出发的最长滑雪路径的长度是一定的，搜过一次，下次再搜，会浪费很多时间。我们可以把这个最长滑雪路径的长度用一个数组 $f$ 存起来，使用 $f_{x,y}$ 表示 $(x,y)$ 从这个点出发的最长滑雪路径，如果搜过了，$f_{x,y}$ 会有一个值，这时候就不用继续搜索下去了，直接返回 $f_{x,y}$。

为了方便，我们可以让 $f$ 数组初始化为 $-1$，判断 $f_{x,y}$ 有没有值时可以写成`if(~f[x][y])`，这样能避免"从这个点出发的最长滑雪路径的长度为 $0$ 而继续搜"的情况。

这就是记忆化搜索的思想，经过记忆化，时间复杂度从 $O(4^{nm})$ 优化成了 $O(nm)$。

下面是代码：
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
template<class T>
T Max(T _,T __){return _<__?__:_;}
template<class T>
T Min(T _,T __){return _>__?__:_;}
const int dx[5]={0,-1,0,0,1},
		  dy[5]={0,0,-1,1,0};//四个方向打表
int n,m,a[110][110],ans;
int f[110][110];
int dfs(int x,int y,int cnt){//注意记忆化的 dfs 有返回值
	if(~f[x][y]) return f[x][y];//记忆化
	int maxcnt=0;//记录最长滑雪路径的长度
	for(int i=1;i<=4;i++){
		int tmpx=x+dx[i],tmpy=y+dy[i];
		if(tmpx<1||n<tmpx||tmpy<1||m<tmpy) continue;
		if(a[tmpx][tmpy]>=a[x][y]) continue;
		maxcnt=Max(maxcnt,dfs(tmpx,tmpy,cnt+1)+1);
     	//最长滑雪路径包括这个点本身，要 +1
	}
	return f[x][y]=maxcnt;//赋值语句有返回值
}
int mian(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ans=Max(ans,dfs(i,j,1));
  	//注意，最长滑雪路径不一定从最高的点开始，要每个点搜一次
	return 0;
}
char ipt[100010];
int main(int T){//其实可以偷 main 的参数的
	for(scanf("%d",&T)/*偷过来用*/;T--;puts("")){
		memset(a,0,sizeof a);
		memset(f,-1,sizeof f);//以上为多测日常操作
      	scanf("%s",ipt);
		mian();
		printf("%s: %d",ipt,ans+1);//因为一些玄学问题 ans 要 +1
	}
	return 0;
}
```


另外，此题与[P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)是双倍经验。

---

## 作者：zzx42121 (赞：0)

一个有点奇怪的方法

##### 题意：
在矩阵里找一条高度严格递减的最长路

##### 思路：
还是dfs，不过提前算出了每个点每个方向是否能走

代码如下（码风有点丑，见谅）

```cpp
//代码里注释掉的地方是记忆化的部分，不加似乎也能 AC,p1434我也用的这个方法，但不加注释掉的部分就会t一个点 
//大概和其他方法不一样的就是提前用结构体记录每个点每个方向是否能走 
#include<iostream> 
#include<cstring>
using namespace std; 
struct hhh//四个方向是否能走 
{
	bool l,r,u,d;
	int z;
}a[105][105];
string name;
//int memo[105][105]; 
int maxx=0;
int n,m;
int memo2=0;
void dfs(int len,int i,int j)
{
	if(i>n||j>m)
		return;
//	if(memo[i][j]>0)
//	{
//		if(len+memo[i][j]>memo2)
//			memo2=len+memo[i][j]-1;
//		return;
//	}
	if(len>memo2)
		memo2=len;//更新最长路径 
	if(a[i][j].d==true)//==true代表能走 
		dfs(len+1,i+1,j);
	if(a[i][j].u==true)
		dfs(len+1,i-1,j);
	if(a[i][j].l==true)
		dfs(len+1,i,j-1);
	if(a[i][j].r==true)
		dfs(len+1,i,j+1);
}
int main()
{
	int c;
	cin>>c;
	for(int i=0;i<c;i++)
	{
		cin>>name;
		cin>>n>>m;
		maxx=0;
		memo2=0;
		memset(a,0,sizeof(a));//记得初始化  
//		memset(memo,0,sizeof(memo))
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			cin>>a[i][j].z; 
//下面这个循环是用来提前记录每个点是否能走。 
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=m;j++)
			{
				if(i>1)
					if(a[i][j].z>a[i-1][j].z) 
						a[i][j].u=1;
				if(j>1)
					if(a[i][j].z>a[i][j-1].z)
						a[i][j].l=1;
				if(i<n)
					if(a[i][j].z>a[i+1][j].z)
						a[i][j].d=1;
				if(j<m)
					if(a[i][j].z>a[i][j+1].z)
						a[i][j].r=1;
			} 
//每个点的最长路径 
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				memo2=0;
				dfs(1,i,j);
//				memo[i][j]=memo2;
				if(memo2>maxx)
					maxx=memo2;
			}
		cout<<name<<":"<<" ";//注意坑人的输出格式 
		cout<<maxx<<endl; 
	}
	return 0;
}
```

---

## 作者：Unordered_OIer (赞：0)

# UVA10285 题解
~~这是一道模板题~~真的很模板orz
## 题目大意
找一条高度严格递减的最长路。
## 解答
看看数据范围：
$R,C<=\color{red}{100}$  
$100$也太小了，所以我们可以**枚举起点，$\text{dfs}$计算路径长度，打擂台求解**

时间复杂度肯定够。

由于$\text{dfs}$的代码dalao们都写了，所以我这里写记忆化搜索版。
```cpp
ll F(ll i,ll j){
  if(ok[i][j])return f[i][j];
  ok[i][j]=1;f[i][j]=1;
  for(ll k=0;k<4;k++){
    ll nx=i+dx[k],ny=j+dy[k];
    if(nx>=1&&nx<=r&&ny>=1&&ny<=c&&h[nx][ny]<h[i][j])
      f[i][j]=max(f[i][j],F(nx,ny)+1);
  }
  return f[i][j];
}
```

---

## 作者：JustNo (赞：0)

一道搜索题。

------------

思路：

每个点都一条以自己为起点的最长路径。
所以，我们搜索时，只要取以周围点为起点的最长路径+1，即可。	而且每个点都只需要搜索一遍，因为一个点只有一条最长路径	

------------
```cpp
#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
int a[105][105];
int dis[105][105];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int r,c;
int DFS(int x,int y)//对以(x,y)为起点开始搜索最长路径 
{
	if (dis[x][y])		//这个点之前被搜过，已经知道了这点的最长路径，剪枝。 
		return dis[x][y];
	for (int i=0;i<4;i++)
	{
		int u=x+dx[i],v=y+dy[i];
		if (u<1||u>r||v<1||v>c)
			continue;
		if (a[u][v]<a[x][y])
		{
			dis[x][y]=max(dis[x][y],DFS(u,v)+1);//当前点所能走的最长路径 
		}
	}
	return dis[x][y];//返回点的最长路径 
}
int main()
{
	int t;
	string name;
	scanf ("%d",&t);
	while (t--)
	{
		cin>>name;
		scanf ("%d%d",&r,&c);
		for (int i=1;i<=r;i++)
		{
			for (int j=1;j<=c;j++)
			{
				scanf ("%d",&a[i][j]);
				dis[i][j]=0;
			}
			
		}
		int m=0;
		for (int i=1;i<=r;i++)
		{
			for (int j=1;j<=c;j++)
			{
				m=max(m,DFS(i,j));//以每个点为起点都搜索一遍 ，取最大值。 
			} 
		}
		cout<<name<<": "<<m+1<<endl;
	}
	return 0;
}
```

---

