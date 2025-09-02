# [USACO10OCT] Lake Counting S

## 题目描述

Due to recent rains, water has pooled in various places in Farmer John's field, which is represented by a rectangle of N x M (1 <= N <= 100; 1 <= M <= 100) squares. Each square contains either water ('W') or dry land ('.'). Farmer John would like to figure out how many ponds have formed in his field. A pond is a connected set of squares with water in them, where a square is considered adjacent to all eight of its neighbors. Given a diagram of Farmer John's field, determine how many ponds he has.






## 说明/提示

OUTPUT DETAILS: There are three ponds: one in the upper left, one in the lower left, and one along the right side.


## 样例 #1

### 输入

```
10 12
W........WW.
.WWW.....WWW
....WW...WW.
.........WW.
.........W..
..W......W..
.W.W.....WW.
W.W.W.....W.
.W.W......W.
..W.......W.
```

### 输出

```
3
```

# 题解

## 作者：Fractures (赞：229)

# 这篇题解是这道题的DFS和BFS解法的介绍

### 这道题主要有两种解法，深搜和广搜。很多人只会拿DFS写，那我来写写这两种解题方法，再分析一下深搜和广搜的优缺点

## 首先，看看DFS
#### 其实DFS就是一口气往一个方向搜索，然后遇到障碍之后再改一个方向搜索
#### 优点：好写，不易出错，浅显易懂
#### 缺点：往一个方向查找耗时，当寻找最优解时没有剪枝会卡时间

核心代码：
```cpp
void dfs(int x,int y){
    a[x][y]='.';//标记为已走
    int dx,dy;
    for(int i=-1;i<=1;i++){//搜索周围的地方
        for(int j=-1;j<=1;j++){
            dx=x+i;
            dy=y+j;
            if(dx>=0&&dx<=n&&dy>=0&&dy<m&&a[dx][dy]=='W'){//如果没有超过边界且为'W'的话就往那个点继续深入搜索
                dfs(dx,dy);
            }
        }
    }
    return;//在void中return为返回上一值，表示如果不能继续深搜就返回上面的点继续搜索
} 
```

所以，有了这组代码整个代码就写出来了

```cpp
#include<cstdio>
using namespace std;
char a[101][101];
int ans;
int n,m;
void dfs(int x,int y){
    a[x][y]='.';
    int dx,dy;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            dx=x+i;
            dy=y+j;
            if(dx>=0&&dx<=n&&dy>=0&&dy<m&&a[dx][dy]=='W'){
                dfs(dx,dy);
            }
        }
    }
    return;
} 
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++){
    	scanf("%s",a[i]);//避免换行带来问题这里直接读入字符串
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='W'){//如果是W的话就直接开始遍历
                dfs(i,j);
                ans++;//水潭加一处
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```

##### 显然 ，dfs的好处就是好打、方便

## 那么，再过来看看BFS
#### BFS就是维护一个队列，以一个点往四周搜索，如果符合条件的话就把它放进队列里
#### 优点：同级优先搜索，在求最优解的时候可以避免许多无用的搜索，提高效率、可以避免递归
#### 缺点：不好写，易出问题，用stl写队列很慢

### 当我们用stl写队列时的BFS核心代码
```cpp
void bfs(int x,int y){
    s[x][y]='.';
    int dx,dy;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            dx=x+i;
            dy=y+j;
            if(dx>=0&&dx<n&&dy>=0&&dy<m&&s[dx][dy]=='W'){
                hori.push(dx);//把行放入队列
                para.push(dy);//把列放入队列
            }//注意，其实可以用一个队列维护，但是用两个队列更好写，更直观
        }
    }
}
```

那么，整体代码就稍微有点差别

```cpp
#include<cstdio>
#include<queue>
using namespace std;
queue<int>hori;//行的队列
queue<int>para;//列的队列
int n,m;
int ans;
char s[101][101];
inline int read(){//读入优化，可以加快数字的输入
    char p=0;int r=0,o=0;
    for(;p<'0'||p>'9';o|=p=='-',p=getchar());
    for(;p>='0'&&p<='9';r=(r<<1)+(r<<3)+(p^48),p=getchar());
    return o?(~r)+1:r;
}
inline void bfs(int x,int y){//不用递归时可以加inline，提高1ms的运行速度
    s[x][y]='.';
    int dx,dy;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            dx=x+i;
            dy=y+j;
            if(dx>=0&&dx<n&&dy>=0&&dy<m&&s[dx][dy]=='W'){
                hori.push(dx);
                para.push(dy);
            }
        }
    }
}
int main(){
    n=read();m=read();//看不懂的话可以把这一行改成cin或scanf
    for(int i=0;i<n;i++){
        scanf("%s",s[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i][j]=='W'){
                hori.push(i);
                para.push(j);
                while(!hori.empty()){//如果队列不为空
                    bfs(hori.front(),para.front());//广搜队列前面的元素
                    hori.pop();para.pop();//弹出元素
                }
                ans++;
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```
#### 值得一提的是，加上快读等优化以后已经做到stl队列能运行时间的极致了，然而提交就算开O2优化还是会有两个测试点被T
#### 这就需要我们手写队列了以及各种优化了，但是这个代码适合bfs的初学者理解

---

## 作者：高铁1号 (赞：106)

# 一道DFS判断连通块的题目。

### 代码附上：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int fxx[9]={0,-1,-1,-1,0,0,1,1,1};//x方向
int fxy[9]={0,-1,0,1,-1,1,-1,0,1};//y方向
int n,m,ans;
char a[105][105];
void dfs(int x,int y)
{
    int r,c;
    a[x][y]='.';
    for (int i=1;i<=8;i++)
    {
        r=x+fxx[i];
        c=y+fxy[i];
        if (r<1||r>n||c<1||c>m||a[r][c]=='.')//判断是否出界
            continue;
        a[r][c]='.';
        dfs(r,c);
    }
}
int main()
{
    scanf("%d %d\n",&n,&m);
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
            cin>>a[i][j];
    }
    ans=0;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            if (a[i][j]=='W')
            {
                ans++;
                dfs(i,j);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
### 第一次写题解，如有不足，请各位dalao指出，谢谢！


---

## 作者：子谦。 (赞：41)

# 非搜索方法！！
这道题我们用**暴~~颓~~推$+$并查集**做

读完题我们也许会有一个大胆的想法：这道题真的要用搜索？？这跟DFS有什么联系？？

我们发现，所有的水坑都是连在一起的，八个方向相连。那么，这非常有利于我们直接暴推写并查集，我们从左往右自上而下地推，因为与八个方向相连，所以我们只需要判定四个方向是否为一个水坑，要求这四个方向所在直线互不重合
## 下放代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=105;
int n,m,f[10005],ans;//f是并查集数组（并为一维），ans是水坑个数
char p[maxn][maxn];
int fa(int x){//简单的寻找祖先，又名找爸爸
    if(f[x]==x)return x;
    return fa(f[x]);
}
void hebing(int x,int y){//合并祖先
    int fx=fa(x),fy=fa(y);
    if(fx==x){
        f[x]=fy;
        return;
    }
    f[fy]=fx;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        getchar();//读掉换行符
        for(int j=1;j<=m;++j){
            scanf("%c",&p[i][j]);
            f[(i-1)*m+j]=(i-1)*m+j;
        }
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            if(p[i][j]=='W'){//如果本身有积水
                int pp=(i-1)*m+j;
                if(p[i][j+1]=='W')hebing(pp,pp+1);//正右方向
                if(p[i+1][j-1]=='W')hebing(pp,pp+m-1);//左下方向
                if(p[i+1][j]=='W')hebing(pp,pp+m);//正下方
                if(p[i+1][j+1]=='W')hebing(pp,pp+m+1);//右下方向
            }
        }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(p[i][j]=='W')//如果本身有积水且祖先为自己本身，则视为一个新的水坑
            	ans+=(f[(i-1)*m+j]==(i-1)*m+j);
    printf("%d",ans);
    return 0;
}
```
## 不喜勿喷
# 请勿抄袭
### 谢谢观看

---

## 作者：s5_gan (赞：32)

# DFS大法好
####  作为一名 ~~不会用bfs~~ dfs大佬
### 做题思路是很简单的：
#### 只要每搜索完一滩水就标记，就可以避免重复搜索了。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int p[8][2]={{0,1},{1,0},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};//上,下,左,右,左前,左后,右前,右后
int n,m,ans=0;
char a[105][105];
bool bo[105][105];//标记地图
int dfs(int x,int y)//主角
{
	bo[x][y]=1;//每次搜索这个单元格都定义为被搜过
	for(int i=0;i<8;i++){//const不用说,八个方向都搜一边
		if(a[x+p[i][0]][y+p[i][1]]=='W' && bo[x+p[i][0]][y+p[i][1]]==0){//如果搜索到相连的水
			dfs(x+p[i][0],y+p[i][1]);//进入另一个水单元格
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		cin>>a[i][j];//输入不说
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		if(a[i][j]=='W' && bo[i][j]==0){
        	//寻找一个有水的单元格(前提没被搜过)
			dfs(i,j);//开始搜索
			ans++;//每次标记完一滩水加一
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：liujiayuan (赞：27)

看到楼上大佬说bfs会T，我这个用bfs板子不开O2不用快读一遍过的蒟蒻瑟瑟发抖

在我的印象中bfs不是用空间换时间吗？哪里会好慢？而且对于C党们的~~NB~~STL一直好评如潮啊

#### 言归正传

看到本题bfs竟然不是主流做法的 ~~练习时长两年半的BFS练习生~~ 我，就来了一份bfs代码，这种求连通块个数的题目也是屡见不鲜了，基本可以当板子打

#### 上代码，注释在其中
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,flag[105][105]={0},ans=0,cnt=1;
char ma[105][105];
int dx[8]={0,1,0,-1,1,1,-1,-1};
int dy[8]={1,0,-1,0,1,-1,1,-1};
//dx，dy，存下八个方向
struct node
{
	int x,y;   //这里的结构体只需要存坐标就好了，步数什么的无所谓
};
inline void bfs(int a,int b)   //bfs板子
{
	queue <node> q;   //开一个node类型的队列，存点
	node o;
	o.x=a;o.y=b;
	q.push(o);   //把起始点存入队列
	flag[a][b]=cnt;  
//这里flag赋为cnt我解释一下，此处赋为1也没问题，
//但这么做是为了方便可能出现的查询操作，那样的话直接查询flag数组就好了
	while(!q.empty())
	{
		o=q.front();   //取出队头，作为基准点向周围发散
		q.pop();   //弹出队头
		for(int i=0;i<8;i++)   //枚举八个方向
		{
			int nx=o.x+dx[i];
			int ny=o.y+dy[i];
			if(nx<0||ny<0||nx>=n||ny>=m||flag[nx][ny]!=0||ma[nx][ny]!='W')
			{
				continue;
			}   
            //判断越界，非水坑，以及重复
			flag[nx][ny]=cnt;   //标记
			node next;
			next.x=nx;next.y=ny;
			q.push(next);   //存入队列
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>ma[i];
	}   //懒人输入
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(ma[i][j]=='W'&&flag[i][j]==0)
			{
				bfs(i,j);
				ans++;
				cnt++;
			}
            //找到未被标记的水坑，就进行bfs覆盖式标记，并ans++
            //这个cnt的作用之前也解释过了，cnt++进行下一块标记
		}
	}
	cout<<ans<<endl;  //输出结果
	return 0;   //完美结束
}
```


---

## 作者：loceaner (赞：26)

### 没错，我又找到了一个可以暴搜的题目，因为又是判断连通块
似乎并没有什么技术含量的暴搜，有时候，就可以A掉一个题！！

8个if，让你的人生更加美好！！

## 思路：

因为所有的水坑都是连在一起的，所以我们可以for循环找到某一个水坑的某一个元素，将ans加1，然后将其周围的水全部变成陆地（及将这个水坑删除）,然后这样一步一步搜下来就可以找出水坑数啦！

接下来我们就看代码吧！

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<deque>
using namespace std;

int n,m;
char a[101][101];
bool f[101][101]= {false};

int baosou(int x,int y) {//将访问的这个水坑删除
	if(a[x][y+1]=='W') {
		a[x][y+1]='.';
		baosou(x,y+1);
	}
	if(a[x][y-1]=='W'){
		a[x][y-1]='.';
		baosou(x,y-1);
	}
	if(a[x+1][y]=='W') {
		a[x+1][y]='.';
		baosou(x+1,y);
	}
	if(a[x-1][y]=='W') {
		a[x-1][y]='.';
		baosou(x-1,y);
	}
	if(a[x+1][y+1]=='W') {
		a[x+1][y+1]='.';
		baosou(x+1,y+1);
	}
	if(a[x+1][y-1]=='W') {
		a[x+1][y-1]='.';
		baosou(x+1,y-1);
	}
	if(a[x-1][y+1]=='W') {
		a[x-1][y+1]='.';
		baosou(x-1,y+1);
	}
	if(a[x-1][y-1]=='W') {
		a[x-1][y-1]='.';
		baosou(x-1,y-1);
	}
}

int main() {
	scanf("%d%d",&n,&m);
	if(m==0)return 0;
	int ans=0;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin>>a[i][j];
            //听我的，永远不要用scanf输入字符
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(a[i][j]=='W') {
				a[i][j]='.';
				ans++;//找到之后将这个点变成旱地并将ans加1
				baosou(i,j);//开始暴搜
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：扬皓2006 (赞：17)

这是一道经典的dfs求联通块的题目

代码如下:
```
#include<bits/stdc++.h>//万能头
using namespace std;
int n,m,coun=0;
char ma[101][101];//地图数组
int b[101][101];
int dx[8]={0,0,1,-1,1,-1,1,-1};//此处千万要注意，是8个方向
int dy[8]={1,-1,0,0,-1,1,1,-1};
void dfs(int x,int y)//好戏即将开始
{
	ma[x][y]=0;//把搜索过的标记
	for(int i=0;i<=7;i++)
	{
		if(ma[x+dx[i]][y+dy[i]]==1)//如果是水坑
		{
			dfs(x+dx[i],y+dy[i]);//继续搜索旁边的
		}
	}
}
int main()
{
	cin>>m>>n;//输入
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>ma[i][j];
			if(ma[i][j]=='W')
			ma[i][j]=1;
			else
			ma[i][j]=0;//改成数字便于搜索
		}
	 } 
	 for(int i=1;i<=m;i++)
	 {
	 	for(int j=1;j<=n;j++)
	 	{
	 		if(ma[i][j]==1)
	 		{
	 			coun++;//水坑计数
	 			dfs(i,j);
			 }
		 }
	 }
	 cout<<coun;//输出
	 return 0;
}
这里还有两个普通的深搜模板
深度优先搜索算法框架1
int Search(int k)
　{
　for (i=1;i<=算符种数;i++)
　　if (满足条件)
　　   {
　　　　保存结果
　　　　if (到目的地) 输出解;
　　　           else Search(k+1);
　　　　恢复：保存结果之前的状态{回溯一步}
　 　  }
　}
 深度优先搜索算法框架2
int Search(int k)
　{
　  if  (到目的地) 输出解;
　　　else
　　　　for (i=1;i<=算符种数;i++)
　　　　　if  (满足条件) 
　　　　　　　{
　　　　　　　　保存结果;
　　　                  Search(k+1)
                             恢复：保存结果之前的状态{回溯一步}
　　　　　　　}
　}
 希望各位都能顺利学会DFS，也希望管理大大能通过此篇题解！

---

## 作者：Sn_Eddy (赞：17)

# 一个很简单的连通块问题
//到我博客里看一看吧[]https://www.luogu.org/blog/zxl/

首先给各位看官们普及一下，用到dfs的一般都是求全部解和连通块问题。搜索算法的可变性非常大（比如下面这个程序就是搜索，只是长得不太像而已）
看代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char zyj[1001][1010];//这个数组用来存储水塘和陆地
int i,j,m,n,sum=0;
void sdm(int a,int b)//你可以吧sdm理解为dfs
{
    if (zyj[a][b]=='W')//如果是水塘，就把它变成陆地，并且搜索四周的水塘，这样就可以把一片水塘找出
    {
    	zyj[a][b]='.';//变成陆地
        sdm(a-1,b-1);
        sdm(a-1,b);
        sdm(a-1,b+1);
        sdm(a,b-1);
        sdm(a,b+1);
        sdm(a+1,b-1);
        sdm(a+1,b);
        sdm(a+1,b+1);//这八行是递推
    }
}
int main()
{
    
    cin>>m>>n; 
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            cin>>zyj[i][j];//输入
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
        {
            if(zyj[i][j]=='W')//如果有水塘，计数器+1，并且将这个水塘从我们的搜索过程中排除
            {
                sdm(i,j);
                sum++;
            }
        }
        cout<<sum;//多么简单，对吗？
}
```

---

## 作者：Strong_Jelly (赞：8)

**这道题虽然用dfs，bfs等可以过，但对于一些初学者来说并不是很容易，于是就有了这篇~~奇葩~~题解。虽然代码很长，复杂度很高，但很好理解**

首先声明一下，这种思路是由这道题产生的：[流感传染](http://ybt.ssoier.cn:8088/problem_show.php?pid=1191)，
这种思想和广度优先搜索一样，可代码却完全不同

把思路阐述一下

**我们可以定义一个“首领”w数组，w[0][i][j]表示x坐标是i，y坐标是j的“W”的首领的x坐标；w[1][i][j]表示x坐标是i，y坐标是j的“W”的首领的y坐标。这里首领是什么意思呢？是当你枚举到一个“W”是，就可以把它定义为这个湖的首领，及自己的首领是自己，这样当枚举到其他和这个湖相连的“W”时就可以把它的首领定义为这个湖的首领，就不会把这个“W”算到其它的湖里去了。**

1.枚举所有点

2.找到一个“W”后，标记此湖已经找过了，并存下坐标，把湖的数量 + 1

3.while循环直到没有找到其他和第2步上面枚举的首领相连的“W”。至于怎么while循环呢，看下面的代码

```cpp
while(true)//循环直到没有可连的"W" 
{
	bool ff = false;//定义一个ff，判断是否找到了任何一个可以连的"W" 
	for(int ii = 1; ii <= m; ii++)
	{
		for(int jj = 1; jj <= n; jj++)
		{
			if(w[0][ii][jj] == i && w[1][ii][jj] == j)//如果一个"W"的首领是上面枚举到的首领，就可以判断有没有和这个"W"相连的"W"了 
			{
				for(int k = 0; k < 8; k++)//八个方向 
				{
					if(q[ii + u[0][k]][jj + u[1][k]] == 'W' && !f[ii + u[0][k]][jj + u[1][k]])//如果是个"W"，且没有被连过 
					{
						f[ii + u[0][k]][jj + u[1][k]] = true;//改为连过了 
						w[0][ii + u[0][k]][jj + u[1][k]] = i;//把首领定义为上面枚举到的首领 
						w[1][ii + u[0][k]][jj + u[1][k]] = j;
						ff = true;//标记为这次循环连过"W"了(表示还有可连的"W")
					}
				}
			}
		}
	}
	if(!ff)//如果没有"W"可连了 
	{
		break;//退出 
	}
}
```


完整的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int u[2][8] = {{1, -1, 1, -1, 0, 0, 1, -1}, {1, -1, -1, 1, 1, -1, 0, 0}};//八个方向(按顺序)--->：↘，↖，↙，↗，→，←，↓，↑  
int n, m, k, w[2][111][111], ans;
char q[111][111];
bool f[111][111];
int main()
{
	scanf("%d %d", &m, &n);
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			cin >> q[i][j];//输入 
		}
	}
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(q[i][j] == 'W' && !f[i][j])//如果发现了一个湖，且没有被连过 
			{
				f[i][j] = true;//改为连过了 
				w[0][i][j] = i;//自己是首领 
				w[1][i][j] = j;
				ans++;//湖的数量 + 1 
				while(true)//循环直到没有可连的"W" 
				{
					bool ff = false;//定义一个ff，判断是否找到了任何一个可以连的"W" 
					for(int ii = 1; ii <= m; ii++)
					{
						for(int jj = 1; jj <= n; jj++)
						{
							if(w[0][ii][jj] == i && w[1][ii][jj] == j)//如果一个"W"的首领是上面枚举到的首领，就可以判断有没有和这个"W"相连的"W"了 
							{
								for(int k = 0; k < 8; k++)//八个方向 
								{
									if(q[ii + u[0][k]][jj + u[1][k]] == 'W' && !f[ii + u[0][k]][jj + u[1][k]])//如果是个"W"，且没有被连过 
									{
										f[ii + u[0][k]][jj + u[1][k]] = true;//改为连过了 
										w[0][ii + u[0][k]][jj + u[1][k]] = i;//把首领定义为上面枚举到的首领 
										w[1][ii + u[0][k]][jj + u[1][k]] = j;
										ff = true;//标记为这次循环连过"W"了(表示还有可连的"W")
									}
								}
							}
						}
					}
					if(!ff)//如果没有"W"可连了 
					{
						break;//退出 
					}
				}
			}
		}
	}
	printf("%d", ans);//输出 
	return 0;
} 
```

PS：迷宫问题也可以这么做

---

## 作者：二哥啃菜包 (赞：4)

这题乍一看是道求联通块的模板题，那么联通块各位大佬都有各种神奇的办法维护但是
### 我们不讲联通块，我们讲强连通分量！！！（不连边的tarjan呦）

观察题面，嗯不错这是道网格题的图，那么我们考虑用二维tarjan求强连通 分量，

我就不讲tarjan了，这是一个套模板的题，我们在【模板】缩点 的代码上加一维，具体其他和模板一样，套个代码观察观察：

```
#include<cstdio>
#include<iostream>
using namespace std;
int n,m,top=0,col=0,x=0,ans=0;//ans 没蛋用；
//直接输出col（强连通分量个数）即可
const int N=105;
struct node{
    int x,y;
}stack[N*N];
int low[N][N],dfn[N][N];//tarjan标配
char map[N][N];
int co[N][N];//co记改点属于哪个强连通分量
int dx[]={-1,-1,-1,0,0,1,1,1},dy[]={-1,0,1,-1,1,-1,0,1};
void tarjan(int ux,int uy){ 
    if(map[ux][uy]=='.')return;//防止对.进行tarjan
    dfn[ux][uy]=low[ux][uy]=++x;
    top++;
    stack[top].x=ux;
    stack[top].y=uy;
    for(int i=0;i<8;++i){
        int vx=ux+dx[i];int vy=uy+dy[i];
        if(vx<1 || vx>n || vy<1 || vy>m)continue;//防止超边界
        if(map[vx][vy]=='.')continue;
        if(!dfn[vx][vy]){
            tarjan(vx,vy);
            low[ux][uy]=min(low[ux][uy],low[vx][vy]);
        } 
        else if(!co[vx][vy])
            low[ux][uy]=min(low[ux][uy],dfn[vx][vy]);
    }
    if(dfn[ux][uy]==low[ux][uy]){
        co[ux][uy]=++col;
        map[ux][uy]='.';
        while(stack[top].x!=ux || stack[top].y!=uy){
            co[stack[top].x][stack[top].y]=col;
            map[stack[top].x][stack[top].y]='.';
            top--;
        }
        top--;
    }
}
int main(){
    std::ios::sync_with_stdio(false);//关闭同步
    cin>>n>>m;
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j){
        cin>>map[i][j];
    }
    
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)
    if(!dfn[i][j])tarjan(i,j);
    ans=col;
    cout<<ans<<endl;
}
```

啊这是一篇多么贴近劳动人民生活的题解，求管理员放我去救济众位在tarjan中奔腾的孩子们吧

---

## 作者：hfcxb (赞：4)

来一个Python的程序
```python
import sys
sys.setrecursionlimit(10000 + 13)  #限制递归层数，否则有一个点RE

m,n = map(int, input().split())
field=[list(input()) for i in range(m)]

dx = [-1, -1, -1, 0, 0, 1, 1, 1]
dy = [-1, 0, 1, -1, 1, -1, 0, 1]
v = [[0] * n for i in range(m)]

def dfs(x,y):
    v[x][y] = 1
    for k in range(len(dx)):
        tx = x + dx[k]
        ty = y + dy[k]
        if tx < 0 or tx >= m or ty < 0 or ty >= n:
            continue
        if field[tx][ty] == '.' or v[tx][ty] == 1:
            continue
        dfs(tx,ty)


ans = 0
for i in range(m) :
    for j in range(n) :
        if v[i][j] == 0 and field[i][j] == 'W':
            dfs(i,j)
            ans = ans + 1

print(ans)

```

---

## 作者：花千树 (赞：4)

## DFS经典题（染色，又叫求联通块），跟许多题有类似的地方

### 染色，它的名字告诉我们，是一个从一张白纸（初始状态），一步步染成需要的结果

#### DFS，全程为深度优先搜索，也叫深搜，DFS，曾在NOIP中出现多次，是每个OIER必学的算法


#### 其他DFS经典题：八皇后，全排列问题，约瑟夫环等

##### 回到本题，本题思路：先顺着查找一遍，找到水坑把它设为旱地，然后DFS深搜，深搜过程中，搜过就设成旱地，每搜一次加方向，继续搜。

**上代码：**

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
char s[105][105];
int n,m,ans,f[8][2]={{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};//方向增量数组
int dfs(int x,int y){//深搜过程
    if(!(x<0||y<0||x>=n||y>=m)){
        if(s[x][y]=='W'){
            s[x][y]='.';//设为旱地（染色）
             for(int i=0;i<=7;i++){
                dfs(x+f[i][0],y+f[i][1]);//7个方向继续搜
        }
        return 1;
    }
    }
}
int main(){
    cin>>n>>m;//读入
    for(int i=0;i<n;i++)cin>>s[i];//读入
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)if(s[i][j]=='W')ans+=dfs(i,j);//判断可以搜，就搜
    }
    cout<<ans<<endl;//输出
    return 0;
}
```

---

## 作者：Eason_AC (赞：3)

深搜即可，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

char a[200][200];
int dx[8]={-1,-1,-1,0,0,1,1,1},dy[8]={-1,0,1,-1,1,-1,0,1};
int ans,n,m;
void dfs(int x,int y) {
    a[x][y]='.';
    for(int i=0; i<8; ++i) {
        int xx=x+dx[i];
        int yy=y+dy[i];
        if((xx>=0)&&(xx<n)&&(yy>=0)&&(yy<m)&&(a[xx][yy]=='W'))
            dfs(xx,yy);
    }
}
int main() {
    cin>>n>>m;
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
            cin>>a[i][j];
    for(int i=0; i<n; ++i)  
        for(int j=0; j<m; ++j)  
            if(a[i][j]=='W') {
                dfs(i,j);
                ans++;
            }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：加载错误 (赞：3)

# 算法：DFS联通块
## 思路：找到水洼（1），标记（0），计数
---------
1.题中要求$N,M$均不超过$100$，所以只用定义$100*100$的数组$lake$就行。另外，lake数组只需要两种状态，即“$W$”,“$.$”，因此，用$bool$就行。

```cpp
const int X = 110;//抛一点，因为数组下标从0开始
bool lake[X][X];
int n,m;
```

2.一个水洼连着8个方向，如果把当前水洼的坐标看作$W(0,0)$,那么其他四个方向就是$W_1(-1,-1),W_2(-1,1),W_3(1,-1),W_4(1,1),W_5(0,-1),W_6(0,1),W_7(-1,0),W_8(1,0)$

就是横坐标分别加$0,0,1,-1,1,-1,1,-1$,纵坐标分别加$1,-1,0,0,1,1,-1,-1$

```cpp
int gox[] = {0,0,0,1,-1,1,-1,1,-1},
    goy[] = {0,1,-1,0,0,1,1,-1,-1};
```

### 好了，开始初始化吧

```cpp
void init(){
    string st;
    cin>>n>>m;
    for(int i = 1;i <= n;i++){
        cin>>st;
        for(int j = 0;j < m;j++){
            if(st[j] == 'W'){
                lake[i][j + 1] = true;//是水洼就标记true
            }
            else{
                lake[i][j + 1] = false;//
            }
        }
    }
}
```
如果图是这样：
```
W.W
.WW
..W
```
那么lake数组里面就是这样
```
101
011
001
```

# OK，现在开始从开头扫描，找到水洼就从那里开始DFS，让周围的水洼变为false。
```cpp
for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(lake[i][j] == t){
                dfs(i,j);
                s++;//计数
            }
        }
    }
```
DFS函数
```cpp
void dfs(int x,int y){
    lake[x][y] = false;//把符合的坐标赋为false
    for(int i = 1;i <= 8;i++){
        int xx = x + gox[i],
            yy = y + goy[i];//xx，yy枚举新坐标
        if(!check(xx,yy)){//在这个位置，如果新的坐标不符合，那么就continue。
            continue;
        }
        dfs(xx,yy);
    }
}
```
check函数
```cpp
bool check(int x,int y){
    if(x > n||y > m){//超出边界，返回false
        return false;
    }
    if(x < 1||y < 1){
        return false;//超出边界，返回false
    }
    if(lake[x][y] == false){//不是水洼，返回false
        return false;
    }
    return true;
}
```

把全部水洼赋为false后，这一整块水洼就不存在了
就开始下一块。。。。。

### 完整代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int X = 101;
int n,m;
bool lake[X][X];
int gox[] = {0,0,0,1,-1,1,-1,1,-1},
    goy[] = {0,1,-1,0,0,1,1,-1,-1};

void init(){
    string st;
    cin>>n>>m;
    for(int i = 1;i <= n;i++){
        cin>>st;
        for(int j = 0;j < m;j++){
            if(st[j] == 'W'){
                lake[i][j + 1] = true;
            }
            else{
                lake[i][j + 1] = false;
            }
        }
    }
}

bool check(int x,int y){
    if(x > n||y > m){
        return false;
    }
    if(x < 1||y < 1){
        return false;
    }
    if(lake[x][y] == false){
        return false;
    }
    return true;
}

void dfs(int x,int y){
    lake[x][y] = false;
    for(int i = 1;i <= 8;i++){
        int xx = x + gox[i],
            yy = y + goy[i];
        if(!check(xx,yy)){
            continue;
        }
        dfs(xx,yy);
    }
}

int main(){
    int s = 0;
    init();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(lake[i][j] == true){
                dfs(i,j);
                s++;
            }
        }
    }
    cout<<s<<endl;
    return 0;
}
```

PS:如果大家有什么不懂的，就[私信我](https://www.luogu.org/space/show?uid=35971)

---

## 作者：大学士_USACO (赞：3)

**提示**

1.标程运用广度优先搜索bfs，通常采用队列存储方式；

2.注意：题解中搜索过的标记套路是这样的：如果寻找的新坐标xx和yy在有效范围内，且标记为“未查找过”，“未查找过”指的是水洼"W"，搜索完毕标记为"."，方便重复搜索；

3.数组q下标第二个：1->横轴所在位置，2->纵轴所在位置。

**标程**

```cpp
/*
	Name:USA Computing Olympiad
	Copyright:USACO_Official / luogu
	Author:Jason Mills
	Date: 05/10/18 15:30
	Description:bfs_Lake Counting
*/
#include <iostream>
using namespace std;
char a[101][101];
int q[10001][3];//q[]中的下标1表示横轴所在位置，下标2表示纵轴所在位置 
int n,m,ans=0;
int fx[]={1,1,1,0,0,-1,-1,-1};//定义8个坐标的位置 
int fy[]={-1,0,1,-1,1,-1,0,1};
void bfs(int,int);//广度优先搜索 
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='W') bfs(i,j);//如果遇到水洼，就开始搜索 
	cout<<ans<<endl;
	return 0;
}
void bfs(int x,int y)//x->横轴所处的位置，y->纵轴所处的位置 
{
	int head=0,tail=1;//head->队列头，tail->队列尾 
	int xx,yy;//xx->搜索到的横轴新坐标，yy->搜索到的纵轴新坐标 
	ans++;
	q[1][1]=x;//初始化队首 
	q[1][2]=y;
	a[x][y]='.';//队首水洼标记为“已查找过” 
	do
	{
		head++;//删除队首 
		for(int i=0;i<8;i++)//8个方向开始搜索 
		{
			xx=q[head][1]+fx[i];//寻找x的新坐标xx 
			yy=q[head][2]+fy[i];//寻找y的新坐标yy
			if(xx>=1 && xx<=n && yy>=1 && yy<=m && a[xx][yy]=='W')
			//如果寻找的新坐标xx和yy在有效范围内，且标记为“未查找过” 
			{
				a[xx][yy]='.';// 标记为“已查找过”
				tail++;//入队，队尾+1 
				q[tail][1]=xx;// 入队横坐标 
				q[tail][2]=yy;//入队纵坐标 
			}
		}
	}while(head<tail);
}
```

---

## 作者：Frank_Pu (赞：3)

**这道题可以用bfs解决

写得比较简单，仅供参考**

**注意数组的大小，大了就MLE，小了就RE**

**上代码：**


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
    char tmp=getchar();
    int result = tmp == '-' ? 0 : tmp - '0' , f = tmp == '-' ? -1 : 1 ;
    while(true){
        tmp=getchar();
        if(tmp>='0'&&tmp<='9') result=result*10+tmp-'0';
        else return result*f;
    }
}
int cz[120][120];
int n,m;
int num=0;
int dx[8]={-1,-1,0,1,1,1,0,-1},
    dy[8]={0,1,1,1,0,-1,-1,-1};
void bfs(int p,int q){
    int head=0,tail=1;
    num++;
    int d[1000][3];
    d[1][1]=p,d[1][2]=q;
    do{
        head++;
        for(int i = 0 ;i < 8;++i ){
            int x=dx[i]+d[head][1],y=dy[i]+d[head][2];
            if(x>=0&&x<n&&y>=0&&y<m&&cz[x][y]){
                tail++;
                d[tail][1]=x;
                d[tail][2]=y;
                cz[x][y]=0;
            }
        }
    }while(head<tail);
}
void doit(void);
int main(){
    doit();
}
void doit(void){
    int i,j;
    char s[101],ch;
    cin>>n>>m;
    scanf("\n");
    for(int i=0;i<n;++i) for(int j=0;j<m;++j) cz[i][j]=true;
    for(int i=0;i<n;++i){
        gets(s);
        for(int j=0;j<m;++j){
            if(s[j]=='.'){
                cz[i][j]=false;
            }
        }
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(cz[i][j])  bfs(i,j);
        }
    }
    cout<<num;
}
```

---

## 作者：焚魂 (赞：2)

这时蒟蒻橙名之后第一次发题解，如有不足，大佬勿喷，假以告知，定会改正。
好了，话回正题，这道题标准的搜索，我的方法
# 很暴力
\(^o^)/，下面是我的搜索代码（dfs）：
```
void dfs(int x,int y)
{
	if(x<1||x>n||y<1||y>m)
	return;
	if(map[x+1][y]!='.')
	{
		map[x+1][y]='.';
		dfs(x+1,y);
	}
	if(map[x-1][y]!='.')
	{
		map[x-1][y]='.';
		dfs(x-1,y);
	}
	if(map[x][y+1]!='.')
	{
		map[x][y+1]='.';
		dfs(x,y+1);
	}
	if(map[x][y-1]!='.')
	{
		map[x][y-1]='.';
		dfs(x,y-1);
	}
	if(map[x+1][y+1]!='.')
	{
		map[x+1][y+1]='.';
		dfs(x+1,y+1);
	}
	if(map[x-1][y+1]!='.')
	{
		map[x-1][y+1]='.';
		dfs(x-1,y+1);
	}
	if(map[x+1][y-1]!='.')
	{
		map[x+1][y-1]='.';
		dfs(x+1,y-1);
	}
	if(map[x-1][y-1]!='.')
	{
		map[x-1][y-1]='.';
		dfs(x-1,y-1);
	}
}
```
怎么样，够暴力吧，从八个方向搜索，直到把连着的水坑都变成'.'了就结束，然后一个双重循环，一个一个判断，凡是判断到是水坑，ans++;之后就用这个函数把周围的都变成'.'，再接着判断就好啦，下面是本题的coding:
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
void dfs(int x,int y);
char map[10010][10010];
bool b[10010][10010];
int ans;
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout); 
	cin>>n>>m;
	char s;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		cin>>map[i][j];
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		if(map[i][j]!='.')
		{
			map[i][j]='.';
			ans++;
			dfs(i,j);//把周围的水坑都变成'.'
		}
	}
	cout<<ans;
	return 0;
}
void dfs(int x,int y)
{
	if(x<1||x>n||y<1||y>m)
	return;
	if(map[x+1][y]!='.')
	{
		map[x+1][y]='.';
		dfs(x+1,y);
	}
	if(map[x-1][y]!='.')
	{
		map[x-1][y]='.';
		dfs(x-1,y);
	}
	if(map[x][y+1]!='.')
	{
		map[x][y+1]='.';
		dfs(x,y+1);
	}
	if(map[x][y-1]!='.')
	{
		map[x][y-1]='.';
		dfs(x,y-1);
	}
	if(map[x+1][y+1]!='.')
	{
		map[x+1][y+1]='.';
		dfs(x+1,y+1);
	}
	if(map[x-1][y+1]!='.')
	{
		map[x-1][y+1]='.';
		dfs(x-1,y+1);
	}
	if(map[x+1][y-1]!='.')
	{
		map[x+1][y-1]='.';
		dfs(x+1,y-1);
	}
	if(map[x-1][y-1]!='.')
	{
		map[x-1][y-1]='.';
		dfs(x-1,y-1);
	}
}
```
就我个人认为，我的代码还是很好理解的。

---

## 作者：霍士弘 (赞：2)

# 一道$DFS$求八连块的题目
>  一个网格与其周围的八个网格相连，而一组相连的网格视为一个水坑。约翰想弄清楚他的田地已经形成了多少水坑。给出约翰田地的示意图，确定当中有多少水坑。  

这就是八连块的题目，所以我们求八连块的个数即可，我们用深度优先搜索，简单易懂。  
先上代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string mp[105];//存放地图
int dx[8] = {-1,1,0,0,-1,1,1,-1};//8个方向，用于扩展节点，上 下 左 右 右上 右下 左下 左上
int dy[8] = {0,0,-1,1,1,1,-1,-1};
bool isin(int x,int y)
{
	return 0 <= x && 0 <= y && x < n && y < m;//判断是否走出了地图
}
void dfs(int x,int y)//dfs
{
	mp[x][y] = '.';//走过的标记为土地
	for(int i = 0;i < 8;i++)//往8个方向走
	{
		int tx = x + dx[i];//走相邻的节点
		int ty = y + dy[i];
		if(isin(tx,ty) && !vis[tx][ty] && mp[tx][ty] == 'W')//符合条件
		{
			dfs(tx,ty);//搜索相邻节点
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i = 0;i < n;i++)
	{
		cin>>mp[i];
	}
	int cnt = 0;
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < m;j++)
		{
			if(mp[i][j] == 'W')//找到一个水坑的开始
			{
				dfs(i,j);//将这个水坑全部夷为平地
				cnt++;//计数器++
			}
		}
	}
	cout<<cnt;//输出答案
	return 0;
}
```
用$DFS$求八连块的主要思想就是：找到一个水坑（意味着一个大水坑的开始），将他与她连接的水坑夷为平地（避免同一个大水坑重复计数），然后计数器加加，找下一个水坑，就可以了。  
~~蒟蒻第一次写题解，有问题请提出~~

---

## 作者：codeboyzzb (赞：2)

## 这是一道典型的 ~~骨胳清奇~~ DFS深度优先搜索(连通域)题目
思路:

+ 先找到一个为$‘W’$的字符,然后再把这个字符替换成  $·(点)$ ,  然后再从当前字符遍历八方，最后
```cpp
if(这个字符是W)
    返回1;
else
    返回0;
```
![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1558965220&di=f3c8999392850adc397efe311d86c468&imgtype=jpg&er=1&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20181122%2F1883ccd3b9bf418482dbf10365a40457.jpeg)
### 既然思路已经给了,那就上代码 ~~扒~~ 吧
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 105
char data[MAXN][MAXN] = {0};
int m,n,ans = 0;
int DFS(int,int);
int main()
{
	cin>>m>>n;
	for(int y = 1; y <= m; ++y)
		for(int x = 1; x <= n; ++x)
			cin>>data[y][x];
	for(int y = 1; y <= m; ++y)
		for(int x = 1; x <= n; ++x)
			if(1 == DFS(x,y))
				ans++;
	printf("%d\n",ans);
	return 0;
}
int DFS(int x,int y)
{
	if('W' == data[y][x])
	{
		data[y][x] = '.';
		DFS(x-1,y-1);
		DFS(x,y-1);
		DFS(x+1,y-1);
		DFS(x-1,y);
		DFS(x+1,y);
		DFS(x-1,y+1);
		DFS(x,y+1);
		DFS(x+1,y+1); 
		return 1;
	}
	return 0;
}
```
# (代码好长啊啊啊)
![](https://ss2.bdstatic.com/70cFvnSh_Q1YnxGkpoWK1HF6hhy/it/u=2804687714,205299780&fm=26&gp=0.jpg)
# 哒哒哒,优化完毕!
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 105
char data[MAXN][MAXN] = {0};
int m,n,ans = 0;
int dx[]={-1,0,1,-1,1,-1,0,1},dy[]={-1,-1,-1,0,0,1,1,1};
int DFS(int,int);
int main()
{
	cin>>m>>n;
	for(int y = 1; y <= m; ++y)
		for(int x = 1; x <= n; ++x)
			cin>>data[y][x];
	for(int y = 1; y <= m; ++y)
		for(int x = 1; x <= n; ++x)
			if(1 == DFS(x,y))
				ans++;
	printf("%d\n",ans);
	return 0;
}
int DFS(int x,int y)
{
	if('W' == data[y][x])
	{
		data[y][x] = '.';
		for(int i = 0; i < 8; i++)
			DFS(x+dx[i],y+dy[i]);
		return 1;
	}
	return 0;
}
```
#### 用一个循环就行了
* * *
为了让大家看到递归的全过程,小编上一个代码,注意,前方高能!

![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1558370982332&di=6f4fd6d4aec881cab9898db4e02cc7a4&imgtype=0&src=http%3A%2F%2Fs7.sinaimg.cn%2Fmw690%2F006SRo6ezy7d7HkhHXEb6%26690)

```cpp
#include <iostream>
#include <cstdio>
#include <windows.h>
using namespace std;
#define MAXN 105
char data[MAXN][MAXN] = {0};
int m,n,ans = 0;
int dx[]={-1,0,1,-1,1,-1,0,1},dy[]={-1,-1,-1,0,0,1,1,1};
int DFS(int,int);
void print(int,int);
int main()
{
	cin>>m>>n;
	for(int y = 1; y <= m; ++y)
		for(int x = 1; x <= n; ++x)
			cin>>data[y][x];
	for(int y = 1; y <= m; ++y)
		for(int x = 1; x <= n; ++x)
			if(1 == DFS(x,y))
				ans++;
	printf("%d\n",ans);
	return 0;
}
int DFS(int x,int y)
{
	if('W' == data[y][x])
	{
		data[y][x] = '.';
		print(m,n);
		for(int i = 0; i < 8; i++)
			DFS(x+dx[i],y+dy[i]);
		return 1;
	}
	return 0;
}
void print(int x,int y)
{
	Sleep(500);
	system("cls");
	for(int i = 1; i <= x; i++)
	{
		for(int j = 1; j <= y; j++)
			cout<<data[i][j];
		cout<<endl;	
	}
	return;
}
```
# 好了,这道题就到这里,下道题见!
![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1558371467309&di=13e5fb7b8796f816aae5087e061d8df2&imgtype=0&src=http%3A%2F%2Fimg.gifhome.com%2Fgif%2Fs%2F20181102%2Ff0ae84ea1935e8a22655025a4804a5d2.jpg%3Fx-oss-process%3Dimage%2Fresize%2Cw_174)

---

## 作者：CCCPKeay (赞：2)

我看许多dalao都是用DFS写的,那我就来一个BFS.

此题不难,就是一个联通块计数的模板题.

## 思路:

因为要记录由'W'组成的联通块的数量,因此我们可以声明一个bool型数组vis先遍

历全图找到'W'就将vis赋值为true,再跑一遍BFS将和这个'W'相连的联通块全赋值

为false,那么我们下次寻找下一个联通块的时候就不会找这个联通块了,因此我们就

完成了计数.

### 步骤:

1.vis将字母'W'赋值为true.

2.跑一边BFS将与这个'W'相连的联通块标记.

3.计数.

~~献上冗长丑陋的代码~~

如果还有不懂的见代码.

## 代码:

```cpp
#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
const int N=100;
int n,m,startx,starty,keay;
char Map[N][N];
bool vis[N][N],judge[N][N];//vis判断,judge判断是否重复BFS基本操作
int dirx[8]={0,1,-1,0,1,-1,1,-1};
int diry[8]={1,0,0,-1,1,1,-1,-1};
struct Node 
{
	int x,y;
};
void bfs()
{
	vis[startx][starty]=false;
	judge[startx][starty]=true;
	queue<struct Node> que;
	struct Node now;
	now.x=startx;now.y=starty;
	que.push(now);
	while(!que.empty())
	{
		now=que.front();
		que.pop();
		for(int i=0;i<8;i++)
		{
			int xx=now.x+dirx[i];
			int yy=now.y+diry[i];
			if(xx<1||xx>n||yy<1||yy>m) continue;
			if(judge[xx][yy]) continue;
			if(Map[xx][yy]=='.') continue;
			judge[xx][yy]=true;
			vis[xx][yy]=false;//本题的核心BFS的同时将与'W'相连的联通块赋值为false,那么下次我们BFS的时候这个联通块就是false就不会对这个联通块进行BFS.
			struct Node next;
			next.x=xx;next.y=yy;
			que.push(next);
		}
	}
	return;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)//遍历全图
	{
		for(int j=1;j<=m;j++)
		{
			cin>>Map[i][j];
			if(Map[i][j]=='W')//如果找到'W'就将vis赋值为true.
			vis[i][j]=true;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(vis[i][j])
			{
				startx=i;starty=j;//BFS
				bfs();
				keay++;//计数
			}
		}
	}
	cout<<keay;
	return 0;
}
```

---

## 作者：Dr_殇 (赞：2)

#一道简单的DFS，话说你不要问我DFS是什么。

#题目分析

这道题目很多人一开始可能看不懂，其实就是搜上，下，左，右，左上，右上，左下，右下分别有没有水，如果有水，就继续搜，直到不能搜为止。

其实这题和[圣诞夜的极光](https://www.luogu.org/problemnew/show/1454)差不多，做出这题后，做圣诞夜的极光就很简单了。

##代码如下：





```cpp
//--新阶梯工作室防伪水印-- 
//--By新阶梯工作室 闪现--
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备
#define in freopen (".in","r",stdin)
#define out freopen (".out","w",stdout)
#define INF 2147483647
#define UNINF -2147483648ll
#define ch char
#define bo bool
#define ui unsigned int
#define ll long long//闪现为了少打几个字符，弄了好多好多宏定义
using namespace std;
int n,m,ans,dx[9]={0,1,0,-1,0,1,1,-1,-1},dy[9]={0,0,1,0,-1,1,-1,1,-1};//dx和dy是方向数组
ch map[105][105];
inline void dfs(int x,int y);
inline void work();
int main(){
    //in;out;
    work();
    return 0;
}
inline void dfs(int x,int y){
    map[x][y]='.';//将它变为不是水，要不然会搜好多遍
    bo ok=1;
    for (int i=1;i<=8;i++){
        if (x+dx[i]>=1&&x+dx[i]<=n&&y+dy[i]>=1&&y+dy[i]<=m&&map[x+dx[i]][y+dy[i]]=='W'){dfs(x+dx[i],y+dy[i]);ok=0;}//以防越界，未越界就搜，越界就不搜
    }
    if (ok)return;//如果啥也没搜到就返回，提高运行速度
}
inline void work(){
    scanf ("%d %d\n",&n,&m);
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            scanf ("%c",&map[i][j]);
        }
        scanf ("\n");
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (map[i][j]=='W'){dfs(i,j);ans++;}//如果是个水，那么就搜索一遍，然后就是一个水坑
        }
    }
    printf ("%d\n",ans);//最后输出
}

```

---

## 作者：Deny_小田 (赞：2)

求八连块……

这是怎么了，连续n个月uke，不过到最后好歹是好了，感谢@w的辛勤劳动~


附代码：



```cpp
//用 DFS 求连通块 
#include <cstdio>
#define Size 105
char Graph[Size][Size];
int m,n,Visited[Size][Size] = {0},cnt = 0;
void DFS(int x,int y,int id){
    if(x < 0||x >= m||y < 0||y >= n) return ;        //判断是否越界
    if(Visited[x][y] > 0||Graph[x][y] != 'W') return ;    //如果已经访问过或者不是 '@' 的格子
    Visited[x][y] = id;        //访问标记 
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++) if(i != 0||j != 0) DFS(x+i,y+j,id);     // i ≠0或者 j ≠0 DFS 
```
/\*
针对上一条 if 语句情况的枚举：

1：i ≠0，j ≠0：DFS

2：i = 0，j ≠0：DFS

3：i ≠0，j = 0：DFS

4：i = 0，j = 0：Not DFS（即中心）

所以是从周围的八个情况枚举。 （也可以用坐标常量数组，以及 if 判断）

                另一种表示方法： if(!(i == 0&&j == 0)) DFS(x+i,y+j,id);  if(!!i||!!j) DFS(x+i,y+j,id);
//如果非（i = 0并且 j = 0） DFS          //如果 非非i 或者 非非j（或 i 或者 j） DFS

\*/

    
```cpp
    } 
}
int main(){ 
    scanf("%d %d",&m,&n);
    for(int i = 0; i < m; i++) scanf("%s",Graph[i]);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++) if(Visited[i][j] == 0&&Graph[i][j] == 'W') DFS(i,j,++cnt);
    }
    printf("%d\n",cnt);
    return 0;
}
```

---

## 作者：Leaved_ (赞：2)

思路:BFS判断联通块，加入队列后把此点变为 ' . '

~~手写队列~~

[二倍经验](https://www.luogu.org/problem/P1451) P1451
```cpp
#include <bits/stdc++.h>

using namespace std;

int go[10001][10001]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,1},{1,-1},{-1,-1}};
//因为题目要求8联通，所以要枚举8个方向
//为啥数组开这么大？
//第一次交RE了...
char ma[100001][1001];
int n,m,ans;
pair <int,int> q[100001];

void input() {
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			ma[i][j]='.';
		}
	}
}

void bfs(int x,int y) {
	int head=1,tail=1;
	ma[x][y]='.';
	q[head].first=x;
	q[head].second=y;
	while(head<=tail) {
		int x2=q[head].first;
		int y2=q[head].second;
		head++;
		for (int i=0;i<8;i++) {//8联通
				int x1=x2+go[i][0];
				int y1=y2+go[i][1];
				if (ma[x1][y1]=='.'||x1<1||x1>n||y1<1||y1>m) continue;
				ma[x1][y1]='.';//标记，避免重复操作
				tail++;
				q[tail].first=x1;
				q[tail].second=y1;//入队
		}
	}
}

int main() {
	cin>>n>>m;
	input();
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			char a;cin>>a;
			ma[i][j]=a;
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(ma[i][j]!='.') {//如果是水洼
				ans++;
				bfs(i,j);//搜索与它相连的所有水洼，标记
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}


```


---

## 作者：ShineEternal (赞：2)

我来发一篇**b**fs的题解

```
#include<cstdio>
using namespace std;
int aa[9]={0,-1,0,1,1,1,0,-1,-1};//八个方向
int n,m;
char a[111][111]; 
char s[111][111]; 
int h[10011][3];
int sum=0;
int bb[9]={0,1,1,1,0,-1,-1,-1,0};//八个方向
int pd(int x,int y)
{
	sum++;
	h[1][1]=x;
	h[1][2]=y;
	a[x][y]='.';
	int head=0,tail=1;//因为广搜，所以有头指针，尾指针
	do
	{
		head++;
		for(int i=1;i<=8;i++)
		{
		int xx=h[head][1]+aa[i];
		int yy=h[head][2]+bb[i];
			if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy]=='W')//前四个是判断不越界，最后一个是判断走到的还是水洼
			{
				a[xx][yy]='.';//心满意足的消掉一个
				tail++;
				h[tail][1]=xx;
				h[tail][2]=yy;//更新队列
			} 
		}
	}while(head<tail);
	return 0;
}
int main()
{
	scanf("%d%d\n",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%s",s[i]);//字符串输入更便捷
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]='.';
			if(s[i][j-1]=='W')
			a[i][j]='W';
		}//我这么写有点麻烦，仅仅是个人爱好
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='W')
			{
			pd(i,j);
			}//主题思路就是遇到一个，计数，然后搜索，把和他连起来的全消掉
		}
	}
	printf("%d",sum);
	return 0;
}
```

本题解主要是为bfs党准备

---

## 作者：lili_flyingcutter (赞：2)

#这题广搜深搜都行

```cpp
#include<iostream>
using namespace std;
char map[101][101];
int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};//定义方向变量（八个）
int n,m,num;
int dfs(int i,int j){if(i<0||j<0||i>=n||j>=m);
    else if(map[i][j]=='W'){map[i][j]='.';//搜过就清零
         for(int z=0;z<=7;z++){
            dfs(i+dir[z][0],j+dir[z][1]);//每搜一次就加上方向
         }return 1;
    }
}
int main()
{
    int i,j;
    cin>>n>>m;
        num=0;
        for(i=0;i<n;++i)
            cin>>map[i];
        for(i=0;i<n;++i)
           for(j=0;j<m;++j)
               if(map[i][j]=='W')
                   num+=dfs(i,j);//是水就搜
        cout<<num<<endl;//输出
    return 0;
}
```

---

## 作者：liumuxin (赞：1)

我来写一个详细一点的bfs题解，这一道题的题目意思就是要统计一个n*m的地图中，水坑的数量

一个水坑就是一个联通块，这里联通块的意思就是一个可以通过在水中8个方向扩展，到达的地方。

这里我用的是bfs，所以用一个队列，每次扩展出的节点就加入队列的末尾，每次从队头取出一个节点来扩展

bfs的好处是在求最短步数等答案中第一次搜到的就是答案，但是比较耗空间，在这种矩形的图中跑的比dfs快

dfs的好处可以求出所有的方案，但是容易tle，适用于每一层的可能性较少的问题中

这道题中，我们枚举每一个是水坑的点，如果它没有被访问过，答案+1，从他开始访问其他点，这样就能保证所有水坑都遍历过，而且不会重复计算答案

```cpp
#include<algorithm>
#include<iostream>
#include<queue>
#define pii pair<int,int> //pair 用来储存一个点的坐标
using namespace std;
int dir[8][2]={{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};//这里很多人可能认为很玄学，其实不太难懂
//dir是方向数组，0~7分别表示往八个方向走，比如{1,0}就是x坐标+1，y坐标不懂，对应着向右移动一个单位
//这么写在后面的扩展中只用一个for循环就可以代替8倍的代码
int n,m;
pii a;
int vis[120][120];//记录每一个点是否被访问过
int map[120][120];
int color[120][120];
void bfs(pii s,int c){//c表示这是第几次计算联通块
	queue<pii> q;
	q.push(s);
	vis[s.first][s.second]=1;
	color[s.first][s.second]=c;//记录color，但是不必要
	while(!q.empty()){
		s=q.front();
		q.pop();
		int x=s.first,y=s.second;//这个表示现在的坐标
		for(int i=0;i<=7;i++){
			int tx=x+dir[i][0],ty=y+dir[i][1];//通过dir数组枚举八个扩展的方向，并加入队列
			if(!vis[tx][ty]&&map[tx][ty]==1){
				vis[tx][ty]=1;//记录访问过这个点
				color[tx][ty]=c;
				pii next=make_pair(tx,ty);
				q.push(next);//加入队列
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char x;
			cin>>x;
			if(x=='W'){
				map[i][j]=1;//标记水坑
			}
		}
	}
	int tot=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(map[i][j]==1&&!vis[i][j]){//每次找到一个没有被访问过的水坑，开始扩展，答案就是总共扩展的次数
				tot++;//扩展次数++
				pii start=make_pair(i,j);
				bfs(start,tot);	//开始扩展
			}
		}
	}
	cout<<tot<<endl;//输出扩展次数
}
```

---

## 作者：Ofnoname (赞：1)

# 本蒟蒻的第二篇题解
看见那么多大佬用深搜，本人使用广搜做本体
坑点如下

1.可以向八个方向，而不是四个方向，所以不能照抄P1451

2.输入时要么用cin,要么用scanf(" %c")，绝不能用scanf("%c")，否则读入会有问题。

C++代码：
```
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int MAX=100;
const int dx[]={1,1,1,-1,-1,-1,0,0};
const int dy[]={1,0,-1,1,0,-1,1,-1};
//dx,dy用于保存方向。 
int N,M,dat[MAX][MAX],f[MAX][MAX],ans;
//dat是输入数据，f保存搜索情况,ans保存答案 
queue <int> qx,qy;
//分别保存x,y坐标 

void BFS(int x, int y)
//广搜函数，在main里被调用 
{
	qx.push(x);
	qy.push(y); //进队 
	f[x][y]=0;//标记 
	while (!qx.empty())
	{
		int i=qx.front();
		int j=qy.front();
		qx.pop();
		qy.pop();
		//以上取出队首，删掉队首 
		for (int d=0; d<8; d++)
		{
			int Ti=i+dx[d];
			int Tj=j+dy[d];
			if (dat[Ti][Tj] && f[Ti][Tj] && 0<=Ti && 0<=Tj && Ti<N && Tj<M)
			//在N*M之内且有水，未被标记 
			{
				f[Ti][Tj]=0;//标记 
				qx.push(Ti);//进队 
				qy.push(Tj);
			}
		}
	}
	//队列已空，不需再清空 
	return;
}

int main()
{
	scanf("%d%d",&N,&M);
	memset(f,1,sizeof(f));
	//初始化f为1 
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<M; j++)
		{
			char c=0;
			scanf(" %c",&c);
			//猥琐的输入，也可使用cin>>c; 
			dat[i][j]=(c=='W')?1:0;//转为数字存储 
		}
	}
	for (int i=0; i<N; i++)
		for (int j=0; j<M; j++)
			if (dat[i][j] && f[i][j])
			//这里为1，且未被标记 
			{
				ans++;
				BFS(i,j);
			}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：北极鹅 (赞：1)

这个题用dfs就能过。简单粗暴又容易调。但一定要注意m和n的意义，否则样例都有可能过不了（除非数据是m == n）。

···cpp






```cpp
#include <cstdio>
#include <cstring>
using namespace std;
char s[103][103];////用于保存图
int lake[103][103];////用于记录湖的数量
int m,n;
void dfs(int x,int y,int cnt) {
    register int dx, dy;
    lake[x][y] = cnt;////打标记
    for(dx = -1;dx < 2;++dx)
        for(dy = -1;dy < 2;++dy)
            if((dx || dy)/*先判断是不是自己，以防无限递归*/ && (x + dx > -1) && (x + dx < n) && /*x下标没有越界*/
            (y + dy > -1) && (y + dy < m) && /*y下标没有越界*/
            (s[x + dx][y + dy] == 'W') && (lake[x + dx][y + dy] == 0))////是水而且没有访问过
                dfs(x + dx,y + dy,cnt);////访问这个点
}
int main() {
    register int i,j;
    int c = 0;
    scanf("%d %d",&n,&m);
    for(i = 0;i < n;++i)
        scanf("%s",s[i]);
    memset(lake,0,sizeof(lake));////清零
    for(i = 0;i < n;++i)
        for(j = 0;j < m;++j)
            if(s[i][j] == 'W' && lake[i][j] == 0) dfs(i,j,++c);////没访问过且是水地，记录个数自加
    printf("%d\n",c);////输出记录个数
    return 0;
}
```
```cpp

---

## 作者：饮溪 (赞：1)

**题意：给出一张图，求全为'W'的联通块的数量。**

简化题意之后，思路就清晰了。

显而易见，此题使用搜索。~~其实我并不知道自己写的是宽搜还是深搜。~~

详细解释见代码注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n;
char map1[103][103];
int dx[9]={0,0,0,1,-1,1,1,-1,-1}; //方向数组，用于搜索
int dy[9]={0,1,-1,0,0,1,-1,1,-1};
int ans;
void Floodfill(int x,int y)//这个过程的工作是与第一个小水坑联通的所有水坑都置为0，即标记为已走过
{
    map1[x][y]='0';//走过的水坑标记为0
    for (int i=1;i<=8;i++)//遍历8个方向，注意是八个方向！
    {
        int new_x=x+dx[i],new_y=y+dy[i];
        if (map1[new_x][new_y]=='1')//没有判断是否出界，是因为map1数组是全局变量初始化全部是0
            Floodfill(new_x,new_y);//如果是水坑，就继续走下一步
    }
}
int main()
{
    cin>>m>>n;//输入行、列
    for (int i=1;i<=m;i++)
    {
        for (int j=1;j<=n;j++)
        {
            cin>>map1[i][j];
            if (map1[i][j]=='.') map1[i][j]='0';//将水坑存为1，旱地存为0，方便之后处理
                else map1[i][j]='1';
        }
    }
    for (int i=1;i<=m;i++)
    {
        for (int j=1;j<=n;j++)
        {
            if (map1[i][j]=='1')//判断是不是水坑
            {
                ans++;//发现一个水坑就计数
                Floodfill(i,j);//寻找周围相连的水坑，标记为已经走过（即用旱地表示），这样下一次循环就不会再走重复的地方
            }
        }
    }
    cout<<ans;//输出结果
    return 0;
}
By Sure.
```

---

## 作者：Dream_It_Possible (赞：1)

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath> 
#include<cstring>
using namespace std;
int a[200][200],n,m,ans,i,j;
char b;
void f(int x,int y)
{
    if (!a[x][y])
    return;
    a[x][y]=0;//符0，表示搜过，不在搜了。
    f(x-1,y);//向下。
    f(x+1,y);//向上。
    f(x,y-1);//向左。
    f(x,y+1);//向右。
    f(x-1,y-1);//向左上。
    f(x-1,y+1);//向右上。
    f(x+1,y-1);//向左下。
    f(x+1,y+1);//向右下。
        //共8个方向。
}
int main()
{
    cin>>n>>m;
    for (i=1;i<=n;i++)
    for (j=1;j<=m;j++)
    {
        cin>>b;
        if (b=='W')
        a[i][j]=1;//是水，转为1，方便后面计算
        else
        a[i][j]=0;//不是水，转为0，方便后面计算
    }
    for (i=1;i<=n;i++)
    for (j=1;j<=m;j++)
    {
        if (a[i][j])
        {
            ans++;//找到一个
            f(i,j);//以这一点去搜。
        }
    }
    cout<<ans;
    return 0;
}
//建议做完这题可以去看看P1451.
```

---

## 作者：Umaru (赞：1)

刚学dfs  本蒟蒻在这里卡了很久 基本思想很简单 就是写一个dfs然后把一个已经找到的水池计算出来（也就是一个八连块）

最后统计dfs的使用次数就ok了

代码如下


```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn=102;
int n,m,total=0;
bool field1[maxn][maxn]={false};//把每一个格子先弄成未访问方便后面加快dfs的速度
char field2[maxn][maxn];
void dfs(int x,int y){
    if(field1[x][y])return;
    else field1[x][y]=true;
    for(int dx=-1;dx<=1;dx++){       //周围的8个格子
        for(int dy=-1;dy<=1;dy++){
            int nx=dx+x,ny=dy+y;
            if(field2[nx][ny]=='.'||!nx||!ny||nx>n||ny>m)//dfs核心s
                continue;
            else dfs(nx,ny);
        }
    }
}
void solve(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(field1[i][j]||field2[i][j]=='.')
                continue;
            else {
                dfs(i,j);
                total++;
            }
        }
    }
    cout<<total;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%s",field2[i]+1);
    }
    solve();
    return 0;
}

```

---

## 作者：walker (赞：1)

本题为图的连通块问题。

比较简单的方法可以用dfs，我们可以从任意一个水坑的地方开始搜索，每到达一个水坑位置就把它变为旱地，直到与它八连通的所有水坑位置都变为旱地。

再重复上面的过程，直到所有格子都变为旱地为止。

（详见代码）

···cpp

```cpp
#include<cstdio>
using namespace std;
const int MAXN=125;
int step[9][2]={-1,-1,-1,0,-1,1,0,-1,0,0,0,1,1,-1,1,0,1,1};
//用来表示移动的数组 
int n,m,ans;
bool g[MAXN][MAXN];
void dfs(int x,int y)
{
    g[x][y]=0;//访问过的点改为旱地，避免被再次访问 
    int tx,ty;//表示从当前点可到达的点 
    for(int i=0;i<9;i++)//尝试各个方向
    {
        //以原点为基础进行拓展 
        tx=x+step[i][0];ty=y+step[i][1];
        //判断当前点是否越界或是旱地 
        if(g[tx][ty]&&tx>=0&&tx<n&&ty>=0&&ty<m) 
          dfs(tx,ty);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    char tmp[MAXN];
    for(int i=0;i<n;i++)
    {
        scanf("%s",tmp);
        for(int j=0;j<m;j++)
          if(tmp[j]=='W')
            g[i][j]=1;
    }
    //由于数据间没有空格，利用字符串进行读入，再转换为bool数组 
    for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
        if(g[i][j]) {dfs(i,j);ans++;}
    //找到一个水坑位置，进行dfs搜索，当无联通时，搜索完成，答案加一 
    printf("%d\n",ans);
    return 0;
}
···
```

---

## 作者：poemciman (赞：1)


****深搜，发现一个没有标记过的小水坑的，就调用tryfill，这样一次调用（主程序内）就标记完了它所在的整片大水坑（湖）。代码如下。


{
In this program,

1 means earth

0 means marked water

-1 means unmarked water


    
    
    
    
    
            
    
```cpp
}
var
    a:array[0..101,0..101] of longint; //0,-1 or 1
    n,m:longint;
procedure tryfill(i,j:longint); //Try filling the surroundings of a[i,j]
begin
    if ((i < 1) or (i > n)) or ((j < 1) or (j > m)) then
        exit;
    if a[i,j] <> -1 then// marked water (0),or earth(1)
        exit;
    // Not exited till here has only one possibillity:It's unmarked water(0).Then mark it after eight DIAOYONGs.
    a[i, j] :=0;
    tryfill(i-1,j-1);
    tryfill(i-1,j);
    tryfill(i-1,j+1);
    tryfill(i,j-1);
    tryfill(i,j+1);
    tryfill(i+1,j-1);
    tryfill(i+1,j);
    tryfill(i+1,j+1);
    //So that:Only need to tryfill(i,j),anywhere same-pond with a[i,j] will be marked
end;
var
    i,j:longint;
    c:char;
    ans:longint;
begin
    readln(n,m);
    for i:=1 to n do
    begin
        for j:=1 to m do
        begin
            read(c);
            if c = 'W' then
            begin
                a[i,j]:=-1;
            end;
            if c = '.' then
            begin
                a[i,j]:=1;
            end;
        end;
        readln;
    end;
    ans:=0;        
    for i:=1 to n do
        for j:=1 to m do
        begin
            if a[i,j] = -1 then
            begin
                tryfill(i,j);
                inc(ans);
            end;
        end;
    write(ans);
end.

```

---

## 作者：Z__X (赞：1)

### **~~为数不多的P党~~...**
#### 这道题就是一道dfs，二重循环，每次从有水处（‘W’）开始搜，将搜过的地方赋值为旱地（‘.’），考虑一下边界和有木有搜过，依次往八个方向（i,j-1;i,j+1;i+1,j;i-1,j）搜就可以了（具体看代码注释）。
$ QAQ $

#### 代码如下：
```
var
  n,m,i,j,ans,s:longint;
  a:array[0..101,0..101] of char;  //字符数组
procedure dfs(x,y:longint);  //神奇的dfs
begin
  if (x<1) or (x>n) or (y<1) or (y>m) then exit;  //判断边界的时间到了
  if a[x,y]='.' then exit;  //当前这个点有木有被扫到过
  a[x,y]:='.';  //赋值为旱地
  inc(s);   //累加当前水坑的面积
  dfs(x+1,y);  //向下进军！
  dfs(x-1,y);  //向上突击！
  dfs(x,y+1);  //向右袭击！
  dfs(x,y-1);  //向左进攻！
  dfs(x-1,y-1);  //这个...左上！
  dfs(x-1,y+1);  //额...右上！
  dfs(x+1,y-1);  //左下...
  dfs(x+1,y+1);  //右下！
end;
begin
  readln(n,m);  //行...列
  for i:=1 to n do  //输入，不说了
   begin
     for j:=1 to m do read(a[i,j]);
	 readln;
   end;
  ans:=0;  //初始化
  for i:=1 to n do
   for j:=1 to m do
    if a[i,j]='W' then  //如果当前点有水，那么...
	 begin
	   s:=0;  //清零
	   dfs(i,j);  //开启dfs之旅
	   if s<>0 then inc(ans);  //若找到水坑，答案加一
	 end;
  write(ans);  //输出
end.  //AC！
```

---

## 作者：LevenKoko (赞：1)

//搜索那一段复制粘贴，结果一个符号忘改，找了好久哪里错了。。（不过符号不改也有40分，amazing！）

```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
using namespace std;
int f[105][105],n,m,p=0,s=0; //f其实没用，本来相当flag用。。
char a[105][105];//存地图

void dfs(int i,int j)//ij是坐标
{
    a[i][j]='.';//如果这里是湖，把它置为旱地，免得后来又扫一遍
    p=0;//当然可以把p忽略，因为它其实自动会退出的
    if(i+1<=n&&a[i+1][j]=='W') dfs(i+1,j),p++;//这一大段功能就是在八个方向找有没有湖，注意越界！
    if(j+1<=m&&a[i][j+1]=='W') dfs(i,j+1),p++;
    if(i-1>=1&&a[i-1][j]=='W') dfs(i-1,j),p++;
    if(j-1>=1&&a[i][j-1]=='W') dfs(i,j-1),p++;
    if(i+1<=n&&j+1<=m&&a[i+1][j+1]=='W') dfs(i+1,j+1),p++;
    if(i+1<=n&&j-1>=1&&a[i+1][j-1]=='W') dfs(i+1,j-1),p++;
    if(i-1>=1&&j-1>=1&&a[i-1][j-1]=='W') dfs(i-1,j-1),p++;
    if(i-1>=1&&j+1>=1&&a[i-1][j+1]=='W') dfs(i-1,j+1),p++;//就是这里的符号
    if(p<1) return;//可忽略
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        cin>>a[i][j];//输入地图
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            p=0;
            if(a[i][j]=='W')//如果没被扫到过就开始搜索；
            dfs(i,j),s++;//搜索完后加一个湖数量;
        } 
    cout<<s;
    return 0;
}
```

---

## 作者：Caicz (赞：0)

### 这是一道判断周围8个格子是否连通后计数的题
### 可以用BFS和队列来做

#### 先循环查找未被标记的水，若找到，ans++
#### 若找到，以该位置为起点，进行BFS，并将能通过位移数组到达的点全部标记
#### **代码如下：**

```c
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;
int m,n,ans=0,s;
struct node
{
	int x,y,d;
}start;
int dx[8]={1,-1,0,0,1,-1,-1,1};
int dy[8]={0,0,1,-1,1,-1,1,-1};
bool visit[1005][1005];
char map[1005][1005];

void bfs(int i,int j)
{
	queue<node> q;//重置队列
	start.x=i,start.y=j;//输入起点
	start.d=1;
	q.push(start);
	visit[start.x][start.y]=1;
	while(!q.empty())//若队列为空，停止循环
	{
		node a=q.front();
		s=a.d;
		q.pop();
		int x=a.x,y=a.y;
		for(int i=0;i<8;i++)
		{
			node b;
			b.x=x+dx[i];
			b.y=y+dy[i];
			b.d=a.d+1;
			if(b.x<0||b.y<0||b.x>=n||b.y>=m||visit[b.x][b.y]||map[b.x][b.y]=='.')continue;//若不满足条件，继续循环
			visit[b.x][b.y]=1;
			q.push(b);
		}
	}
}

int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		scanf("\n");
		for(int j=0;j<m;j++)
			cin>>map[i][j];
	}
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
		if(!visit[i][j]&&map[i][j]!='.')//循环查找未被标记的水
		{
			bfs(i,j);
			ans++;
		}
	cout<<ans;
	return 0;
}
```


---

## 作者：zhangke1 (赞：0)

BFS广度优先搜索

这一题我们要用广搜解。

1.读入。

2.一个一个点搜，找到水洼"W"进入BFS，把自己和与其相连的水洼变成干地"."，水洼数加一。

3.输出水洼数量。

长话短说，上代码!

```cpp
#include<iostream>
  
#include<queue>//c++队列头文件
  
using namespace std;
  
struct data{
  
	int x,y;
  
};//自定义结构体
  
queue<data> q;//定义一个队列q，是前面定义的结构体
  
int n,m;
  
char map[200][200];
  
const int dx[8]={0,1,0,-1,1,1,-1,-1};//八个方向的x坐标
  
const int dy[8]={1,0,-1,0,1,-1,1,-1};//八个方向的y坐标
  
void bfs(int xx,int yy)//进入广搜
  
{
  
	data d,k;
  
	d.x=xx;
  
	d.y=yy;
  
	q.push(d);
  
	while(!q.empty())
  
	{
  
		k=q.front();
  
		q.pop();
  
		map[k.x][k.y]='.';//搜过的变成干地，以防重复
  
		for(int i=0;i<8;++i)向8个方向扩展节点                                    
		{                     
			d.x=k.x+dx[i];                     
			d.y=k.y+dy[i];
			if(d.x>0&&d.y>0&&d.x<=n&&d.y<=m&&map[d.x][d.y]=='W')
			  {
			  	q.push(d);
			  	map[d.x][d.y]='?';
			  }
		}
	} 
}
int main() 
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)      
	  for(int j=1;j<=m;++j)
	    cin>>map[i][j];//输入
	int ans=0;
	for(int i=1;i<=n;++i)      
	  for(int j=1;j<=m;++j)
	    if(map[i][j]=='W') 
	      {
	      	ans++;
	      	bfs(i,j);
	      }//统计
	cout<<ans;//输出
	return 0;
}
```

  
请记住，BFS是一圈一圈搜，DFS是一次搜到底！
  
如有不当，请指教……


---

## 作者：SasukeUchiha (赞：0)

日期 20180904

~~由题面中'水'字符的出现频率可知，此题为水题(然而是普及-，非入门难度)~~**滑稽**~~

'**W**'代表水，与其一周**8**个方格相连，而相连在一起的**一片**'W'称之为**一个**"湖"。

由于前几天在看并查集，楼主一开始就认为这是并查集的题目了，(~~感兴趣的~~达瓦里氏可以尝试下),然而DFS深搜染色貌似方便的多。

于是，以下是代码了 （   已AC： [测评情况](https://www.luogu.org/record/show?rid=10444798)  ）

————————————————分割线———————————————————
```cpp
#include<cstdio>      //头文件
#define len 10002     //定义常量,表示数组长度
bool s[len][len];     //bool型占空间少，且满足染色需要

void fin(int x,int y) //染Shen色Sou函数 “抽水”
{
    if(s[x][y]==true) //有水的地方
    {
        s[x][y]=false;//水变旱地
        fin(x-1,y);
        fin(x,y-1);
        fin(x+1,y);
        fin(x,y+1);
        fin(x+1,y+1);
        fin(x+1,y-1);
        fin(x-1,y-1);
        fin(x-1,y+1); //八方向染色，遇到连通水域就和谐掉
    }
    else
    return ;          //到边界(旱地)结束
}

int main()
{
    int m,n;
    long int k=0;
    scanf("%d%d",&m,&n);      //读入长宽
    char o;
    scanf("%c",&o);           //过滤换行符'\n'
    
    for(int i=1;i<=m;i++)
    for(int j=1;j<=n+1;j++)
    {
        scanf("%c",&o);       //每一个方格的数据
        if(j==n+1)
        break;                //过滤换行符'\n'
        
        if(o=='.')            //是旱地
        s[i][j]=false;
        else                  //是水
        s[i][j]=true;
    }
    
    for(int i=1;i<=m;i++)
    for(int j=1;j<=n;j++)
    {
        if(s[i][j]==true)     //是水
        k++;                  //湖+1
        fin(i,j);             //“抽水”
    }
    
    printf("%ld",k);          //输出湖数
    return 0;
    
}

```
Emmmm，其实我是从 **P1451 求细胞数量** 过来的，只是那个题线上评测莫名鬼畜(~~与本地测试结果不同~~)，所以莫名~~**没**~~通过。。。

快捷地址：[P1451](https://www.luogu.org/problemnew/show/P1451)

WA：[测评情况](https://www.luogu.org/recordnew/show/10445880)

---

## 作者：xukuan (赞：0)

算法：深度优先搜索

先输入

###这是字符串输入，所以注意换行！（要点会在程序里标注）

再穷举每一个W的位置，找到后执行下列操作：

1.删除与W的联通块（dfs，8个方向）

2.计数器+1

最后输出计数器


有一个优化可以考虑（未尝试）：不穷举左上，上，右上三个方向，因为我的代码是先从上到下，从左到右枚举的，理论上是可以的


```cpp
#include<bits/stdc++.h>
using namespace std;

const int lx[9]={0,-1,-1,-1, 0,0, 1,1,1},
          ly[9]={0,-1, 0, 1,-1,1,-1,0,1};
//穷举八个方向注意c++的数组的下界是0

string s;
int n,m,ans/*计数器*/;
char a[110][110];

void dfs(int x,int y)//dfs
{
    a[x][y]='.';//将这个格子赋成'.'
    for(int i=1; i<=8; i++)//穷举8个方向
    {
        int xx=x+lx[i];//x轴
        int yy=y+ly[i];//y轴
        if(a[xx][yy]=='W')/*这个格子是水坑*/ dfs(xx,yy);//递归
    }
}

int main()
{
    scanf("%d %d\n",&n,&m);//输入，要有换行，不然会在第一行的行末少一个字符，60分就是这里
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
          a[i][j]=getchar();//输入
        getline(cin,s);//处理掉后面的换行符，因为样例行尾有空格，所以用字符串操作，稳妥起见
    }
    
    for(int i=1; i<=n; i++)//穷举x轴
      for(int j=1; j<=m; j++)//穷举y轴
        if(a[i][j]=='W')//这是水坑
        {
            dfs(i,j);//调用深搜
            ans++;//计数器+1
        } 
    printf("%d",ans);//输出
}
```

---

## 作者：lipee (赞：0)

这道题其实和白皮书里的细胞很像，就是把四个方向该成了八个。

```cpp
const
  d:array[1..8,1..2]of longint=((1,0),(0,1),(-1,0),(0,-1),(1,1),(-1,-1),(1,-1),(-1,1));//定义方向常量
var
  a:array[1..100,1..100]of char;
  n,m,i,j,ans:longint;
procedure find(x,y:longint);
var
  i:longint;
begin
  a[x,y]:='.';//标记走过的点
  for i:=1 to 8 do
    if (x+d[i,1]>0)and(x+d[i,1]<=n)and(y+d[i,2]>0)and(y+d[i,2]<=m)and(a[x+d[i,1],y+d[i,2]]='W'）//与当前点相连的点是水潭
      then find(x+d[i,1],y+d[i,2]);//进行下一步搜索
end;
begin
  readln(n,m);
  for i:=1 to n do
    begin
      for j:=1 to m do
        read(a[i,j]);
      readln;//注意这里要换行
    end;
  for i:=1 to n do
    for j:=1 to m do
      if a[i,j]='W' then begin find(i,j); inc(ans); end;//枚举没有走过的水潭
  write(ans);
end.

```

---

## 作者：zy小可爱ღ (赞：0)

个人感觉这题还是很简单的，就是一个完全不加工的找联通块个数

个人解题思路是先读入，然后循环一遍，遇到水就dfs，并把这个w所在的联通块“删除”，并在答案上加一

最后输出答案

具体注释看程序：：：





```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,ans;
bool a[105][105];//我用布尔数组，反正就两种情况
void dfs(int x,int y){//dfs
    a[x][y]=false;//删除连通块
    if(x+1<=n&&a[x+1][y])dfs(x+1,y);//如果下面是水（。。。），往下搜
    if(y+1<=m&&a[x][y+1])dfs(x,y+1);//如果左边是水，往左搜，注意y是与m比较，千万不要把m，n弄混
    if(x-1>=1&&a[x-1][y])dfs(x-1,y);//往上搜
    if(y-1>=1&&a[x][y-1])dfs(x,y-1);//往右搜
    if(x+1<=n&&y+1<=m&&a[x+1][y+1])dfs(x+1,y+1);//往左上搜
    if(x+1<=n&&y-1>=1&&a[x+1][y-1])dfs(x+1,y-1);//往右上搜
    if(x-1>=1&&y+1<=m&&a[x-1][y+1])dfs(x-1,y+1);//往左下搜
    if(x-1>=1&&y-1>=1&&a[x-1][y-1])dfs(x-1,y-1);//往右下搜
}
void sc(){//这是我个人调试时用的程序，看被删除的连通块是哪一个，有兴趣的同学可以看看~~~
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j])cout<<"w";
            else cout<<".";
        }
        cout<<endl;
    }
}
int main(){//主函数
    cin>>n>>m;//读入
    for(int i=1;i<=n;i++){
            string x;//定义字符串，字符串虽然是单独的一个变量，但可以直接用下标访问
            cin>>x;//读入连续一段char型的字符串，比较方便
        for(int j=1;j<=m;j++){
            if(x[j-1]=='.')a[i][j]=false;//注意，x是从下标为0的地方开始读的，如果不是水块，就赋值否
            else a[i][j]=true;//否则为是
        }
    }
    for(int i=1;i<=n;i++){//模拟
        for(int j=1;j<=m;j++){
            if(a[i][j]){//如果是水
                //cout<<i<<' '<<j<<endl;个人调试所用
                dfs(i,j);//删除连通块
                //sc();个人调试所用
                ans++;//答案数加一
            }
        }
    }
    cout<<ans<<endl;//输出答案
    return 0;
```
}//完美结束
最后，祝大家天天开心，编程顺利（。。。）


---

