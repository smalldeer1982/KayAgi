# [USACO5.2] 蜗牛的旅行Snail Trails

## 题目描述

萨丽·斯内尔（Sally Snail，蜗牛）喜欢在 $N\times N$ 的棋盘上闲逛（$1<n \le 120$）。

她总是从棋盘的左上角出发。棋盘上有空的格子（用 $\verb!.!$ 来表示）和 $B$ 个路障（用 $\verb!#!$ 来表示）。

下面是这种表示法的示例棋盘：

$$
\boxed{\quad\begin{aligned}
\verb!   A  B  C  D  E  F  G  H! \\
\verb!1  S  .  .  .  .  .  #  .! \\
\verb!2  .  .  .  .  #  .  .  .! \\
\verb!3  .  .  .  .  .  .  .  .! \\
\verb!4  .  .  .  .  .  .  .  .! \\
\verb!5  .  .  .  .  .  #  .  .! \\
\verb!6  #  .  .  .  .  .  .  .! \\
\verb!7  .  .  .  .  .  .  .  .! \\
\verb!8  .  .  .  .  .  .  .  .! \\
\end{aligned}\quad}$$

萨丽总是垂直（向上或者向下）或水平（向左或者向右）地走。她可以从出发地（总是记作 $\tt A1$）向下或者向右走。一旦萨丽选定了一个方向，她就会一直走下去。如果她遇到棋盘边缘或者路障，她就停下来，并且转过 $90$ 度。她不可能离开棋盘，或者走进路障当中。并且，萨丽从不跨过她已经经过的格子。当她再也不能走的时候，她就停止散步。

这里是上面的棋盘上的一次散步路线图示：

$$
\boxed{\quad\begin{aligned}
\verb!   A  B  C  D  E  F  G  H! \\
\verb!1  S--------------+  #  .! \\
\verb!2  .  .  .  .  #  |  .  .! \\
\verb!3  .  .  .  .  .  |  .  .! \\
\verb!4  .  .  .  .  .  +-----+! \\
\verb!5  .  .  .  .  .  #  .  |! \\
\verb!6  #  .  .  .  .  .  .  |! \\
\verb!7  +-----------------+  |! \\
\verb!8  +--------------------+! \\
\end{aligned}\quad}$$
 
萨丽向右走，再向下，向右，向下，然后向左，再向上，最后向右走。这时她遇到了一个她已经走过的格子，她就停下来了。但是，如果她在 $\tt F5$ 格遇到路障后选择另外一条路——向我们看来是左边的方向转弯，情况就不一样了。

你的任务是计算并输出，如果萨丽聪明地选择她的路线的话，她所能够经过的最多格子数。


## 说明/提示

$$
\boxed{\quad\begin{aligned}
\verb!   A  B  C  D  E  F  G  H! \\
\verb!1  S  .  .  .  .  .  #  .! \\
\verb!2  |  .  .  .  #  .  .  .! \\
\verb!3  |  .  .  .  +--------+! \\
\verb!4  |  .  .  .  |  .  .  |! \\
\verb!5  +-----------+  #  .  |! \\
\verb!6  #  .  .  .  .  .  .  |! \\
\verb!7  +------------------  |! \\
\verb!8  +--------------------+! \\
\end{aligned}\quad}$$

题目翻译来自NOCOW。

USACO Training Section 5.2

[本题疑似有误，不保证存在可以通过任意符合要求的输入数据的程序](https://www.luogu.com.cn/discuss/1072919)。如果您认为您的做法可以通过任意符合要求的输入数据，欢迎联系管理员。

## 样例 #1

### 输入

```
8 4
E2
A6
G1
F5```

### 输出

```
33```

# 题解

## 作者：子谦。 (赞：42)


明显这是一道搜索题，其他题解写的有点复杂，我有更简便的写法

既然题目说走到不能再走，那我们就干脆一点，一条路走到黑，不到南墙不回头，一下把要走的路都走完，不但效率高，也好写，关键是大大节省了系统栈

一口气走很多点的关键在于如何记录一个点是否便利过呢？退出后又如何删除标记呢？

或许正是这两个问题使一些想到这种解法的人退缩了，但解决这种问题并不难。我们照常可以用一个二维数组记录一个点是否走过，再用一个栈来记录走过的点，退出时，将栈顶依次弹出就好

也许有人会说don't talk,show me your code.

当然是带着代码来的了，口胡可不是我的风格

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc getchar
#define maxn 125
#define maxm 15000
using namespace std;

inline ll read(){
	ll a=0;int f=0;char p=gc();
	while(!isdigit(p)){f|=p=='-';p=gc();}
	while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
	return f?-a:a;
}

struct ahaha{
	int x,y;
}s[maxm];   //用一个栈来记录已便利的点的坐标  此处建议使用手写栈，而不是STL的栈
int n,m,ans,a[maxn][maxn];    //ans记录最多能走多少点，a数组表示当前点的状态，1为障碍或边界，0为未访问的点，1是已访问的点
const int xx[4]={1,0,-1,0},yy[4]={0,1,0,-1};
void dfs(int x,int y,int sum){    //x,y表示拐点坐标，sum表示走到当前点已走过的点数（包括当前点）
	int s1=sum;  //s1记录栈大小
	for(int i=0;i<4;++i){
		int xy=x+xx[i],yx=y+yy[i];
		while(!a[xy][yx]){  //若节点可访问，则不断访问直到不能访问
			s[++s1]=(ahaha){xy,yx};a[xy][yx]=2;
			xy+=xx[i],yx+=yy[i];
		}xy-=xx[i],yx-=yy[i];  //最后一个节点不可访问要往回走一个
		if(xy==x&&yx==y)continue;   //如果在原地没动要返回，避免死循环
		ans=max(ans,s1);  //ans利用栈大小赋值
		if(a[xy+xx[i]][yx+yy[i]]!=2)dfs(xy,yx,s1);   //如果下一个点不是已访问的点则继续前进
		while(s1>sum){    //撤销标记，弹出栈顶
			a[s[s1].x][s[s1].y]=0;
			--s1;
		}
	}
}

char c[5];
int main(){
	n=read();m=read();
	while(m--){
		scanf("%s",c+1);int l=strlen(c+1),sum=0;
		for(int i=2;i<=l;++i)
			sum=(sum<<3)+(sum<<1)+(c[i]-48);
		a[c[1]-'A'+1][sum]=1;
	}
	for(int i=1;i<=n;++i)
		a[0][i]=a[n+1][i]=a[i][0]=a[i][n+1]=1;
	a[1][1]=2;s[1]=(ahaha){1,1};   //记得把(1,1)放入栈中，如果不放，答案记得+1
	dfs(1,1,1);    //(1,1)如果不放就是dfs(1,1,0)
	printf("%d\n",ans);
	return 0;
}
```

怎么样是不是简洁又美观呢？喜欢的话，点个赞吧

谢谢您的观看

---

## 作者：ZUTTER_ (赞：18)

###（如果管理员大大给过的话，或许是还会比楼下再短6行的解法，接替最美(￣▽￣)~\*）


以为dfs会超时，但是数据范围比较可爱


##质朴dfs+cin is alright


**处理边界条件**把能走的坐标设为1，有障碍的设为0，走过的设为2，防止出现超出边界的情况。


只能转90度处理

```cpp
int f[4]={0,1,0,-1},g[4]={1,0,-1,0};
```
**搜索方向**，0-4分别代表右下左上 所以只要旋转前后的**方向之和**为奇数，旋转度数就是90度


具体看程序注释↓↓↓

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int v,i,m,n,j,k,a[125][125];
int f[4]={0,1,0,-1},g[4]={1,0,-1,0};//搜索方向
char c;
void search(int x,int y,int t,int bs){//t存方向 
    if(bs>k) k=bs;//bs表示当前走过的格子数，k存放最大格子数 
    if(a[x+f[t]][y+g[t]]==1) {//如果可以继续向前走 
        a[x][y]=2;//当前坐标设为走过 
        search(x+f[t],y+g[t],t,bs+1);//方向不变，格数加一 
        a[x][y]=1;//回溯 
    }
    else if(a[x+f[t]][y+g[t]]==0)//前方为障碍时 
        for(int i=0;i<4;i++)
            if((a[x+f[i]][y+g[i]]==1)&&((i+t)%2!=0)){ 
                a[x][y]=2;  
                search(x+f[i],y+g[i],i,bs+1);
                a[x][y]=1;
            } 
}
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++){
        cin>>c>>v;
        a[c-'A'+1][v]=1;//先把障碍存为1 
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++){
            if(a[i][j]==1) a[i][j]=0;
            else a[i][j]=1;//1和0替换，障碍和边界设为0 ，可走格设为1 
        }
    search(1,1,0,1);//搜索方向：向右 
    search(1,1,1,1);//搜索方向：向下 
    printf("%d",k);
}
```
第一次发题解呐，希望能过φ(>ω<\*)


---

## 作者：panyf (赞：4)

dfs题

要分几种情况考虑：

1.前方的格子未走且无障碍，往前走1步

2.前方的格子有障碍，若左侧或右侧未走且无障碍，走左侧或右侧

3.前方的格子已走，则退出搜索

详细注释代码（仅21行，目前最短代码，30msAC）
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[129][129],n,b,d,m,p[4]={1,0,-1,0},q[4]={0,1,0,-1};//t数组存储格子的状态，0为可走，1为有障碍，2为已走；p数组存储x坐标方向，q数组存储y坐标方向
char c;
void dfs(int x,int y,int s,int f){//s为当前已走格子数，f为方向
	t[x][y]=2,m=max(m,s++);//标记当前格子为已走，更新答案
	int u=x+p[f],v=y+q[f];//u为下一步x坐标，v为下一步y坐标
	if(t[u][v]==0)dfs(u,v,s,f),t[u][v]=0;//前方可走则继续搜索，不要忘记将t数组置为0
	if(t[u][v]==1){//有障碍
		f=(f+1)%4,u=x+p[f],v=y+q[f];//分别搜索两侧
		if(t[u][v]==0)dfs(u,v,s,f),t[u][v]=0;
		f=(f+2)%4,u=x+p[f],v=y+q[f];
		if(t[u][v]==0)dfs(u,v,s,f),t[u][v]=0;
	}
}
int main(){
	cin>>n>>b;
	for(int i=n+1;i>=0;i--)t[i][0]=t[0][i]=t[n+1][i]=t[i][n+1]=1;//先标记边界为有障碍，搜索过程中即无需判断边界
	for(int i=0;i<b;i++)cin>>c>>d,t[c-64][d]=1;//标记障碍
	dfs(1,1,1,0),dfs(1,1,1,1),cout<<m;//搜索向下和向右两个方向，输出
}
```


---

## 作者：steven张 (赞：4)

一口气第二发题解，比较生硬的套用了计算几何的知识，调了两个小时，总算是过了。

这种line结构体标记之前的路径然后递归的写法，是今天自己做题的时候想出来的，感觉还不错，我的p1153题解有同款写法

具体细节注释里都有，我用的是两个vector（c,r）存的行和列的障碍物坐标，这样写的写法有什么好处呢？如果n特别大1e5到1e6左右，这种写法不需要一格一格去跳，而是一下到位，因为他的障碍物比较少，可以采用这种离散化的思想。

（代码量仅做练习，不建议考试时候写）

        
```cpp
#include<cstdio>
#include<vector>
##include<algorithm>
using namespace std;
const int maxn=125;
const int maxnode=1e3;
int mx=0,n,m,cnt=-1,tmp1;//cnt记录从起点到终点走了多少线段
char ch;
vector<int> c[maxn],r[maxn];
struct point
{
    int x,y;
    point(int x=0,int y=0):x(x),y(y){}
}a[maxnode];
typedef point vec;
struct line//单开一个表示走过的线段的结构体 
{
    point p1,p2;
    line(point p1=point(0,0),point p2=point(0,0)):p1(p1),p2(p2){}
}tmp[maxnode];
vec operator-(point a,point b){return vec(a.x-b.x,a.y-b.y);}
bool operator==(vec a,vec b){return a.x==b.x&&a.y==b.y;}
int cross(vec a,vec b){return a.x*b.y-a.y*b.x;}//叉积
int dot(vec a,vec b){return a.x*b.x+a.y*b.y;}//点积
bool onseg(point p,point a1,point a2){return cross(a1-p,a2-p)==0&&dot(a1-p,a2-p)<0;}//判断p点在a1a2线段上
bool segproperintersection(point a1,point a2,point b1,point b2)
{
    int c1=cross(a2-a1,b1-a1),c2=cross(a2-a1,b2-a1),c3=cross(b2-b1,a1-b1),c4=cross(b2-b1,a2-b1);
    return c1*c2<0&&c3*c4<0;
}
//计算几何常用工具 
bool judge(point a1,point a2,point b1,point b2)//与之前相交处理 
{
    if(segproperintersection(a1,a2,b1,b2)||onseg(a2,b1,b2)||onseg(b1,a1,a2)||onseg(b2,a1,a2)||a2==b1||a2==b2)//这里不太好想。。总之都写上，也是因为这里调了好长时间。。
        return 1;
    else return 0;
}
void dfs(int tc,int tr ,int dir,int dis)//分别是行，列，方向，1234代表右下左上，走的方格数 
{
    mx=max(mx,dis);//根据这个写法，需要直接更新 
    if(dir==1)//同理 
    {
        int k=0,tmp1=1e9;//从c【tc】的vector里面去找第一个遇到的障碍 
        while(c[tc][k]<tr)
            k++;
        if(c[tc][k]-tr<=1)
            return ;
        int d=c[tc][k]-tr-1;
        tmp[++cnt]=line(point(tc,tr),point(tc,tr+d));
        bool flag=0;//flag和下面的judge判断是否和之前的线段有一条重复 
        for(int i=0;i<cnt;i++)
        { 
            if(judge(tmp[cnt].p1,tmp[cnt].p2,tmp[i].p1,tmp[i].p2))
                flag=1,tmp1=min(tmp1,tmp[i].p1.y);
        }
        if(!flag)//不重复就往下搜 
        {
            dfs(tc,tr+d,4,dis+d);
            dfs(tc,tr+d,2,dis+d);
        }
        cnt--;
        if(flag)//一旦重复就只能回溯 
        {
            d=tmp1-tr-1;
            mx=max(mx,d+dis);//同时在这里更新mx 
            return ;
        }
    }
    else if(dir==2)//同理 
    {
        int k=0,tmp1=1e9;
        while(r[tr][k]<tc)
            k++;
        if(r[tr][k]-tc<=1)
            return ;
        int d=r[tr][k]-tc-1;
        tmp[++cnt]=line(point(tc,tr),point(tc+d,tr));
        bool flag=0;
        for(int i=0;i<cnt;i++)
        {
            if(judge(tmp[cnt].p1,tmp[cnt].p2,tmp[i].p1,tmp[i].p2))
                flag=1,tmp1=min(tmp1,tmp[i].p1.x);
        }
        if(!flag)
        {
            dfs(tc+d,tr,1,dis+d);
            dfs(tc+d,tr,3,dis+d);
        }
        cnt--;
        if(flag)
        {
            d=tmp1-tc-1;
            mx=max(mx,dis+d);
            return;
        }
    }
    else if(dir==3)//同理 
    {
        int k=c[tc].size()-1,tmp1=0;//这里找第一个障碍的时候，要注意从反方向找，下面同理 
        while(c[tc][k]>tr)
            k--;
        if(tr-c[tc][k]<=1)
            return ;
        int d=tr-c[tc][k]-1;
        tmp[++cnt]=line(point(tc,tr),point(tc,tr-d));
        bool flag=0;
        for(int i=0;i<cnt;i++)
        {
            if(judge(tmp[cnt].p1,tmp[cnt].p2,tmp[i].p1,tmp[i].p2))
            {
                flag=1,tmp1=max(tmp1,tmp[i].p1.y);
            } 
        }
        if(!flag)
        {
            dfs(tc,tr-d,4,dis+d);
            dfs(tc,tr-d,2,dis+d);
        }
        cnt--;
        if(flag)
        {
            d=tr-tmp1-1;
            mx=max(mx,dis+d);
            return ;
        }
    }
    if(dir==4)//同理 
    {
        int k=r[tr].size()-1,tmp1=0;
        while(r[tr][k]>tc)
            k--;
        if(tc-r[tr][k]<=1)
            return ;
        int d=tc-r[tr][k]-1;
        tmp[++cnt]=line(point(tc,tr),point(tc-d,tr));
        bool flag=0,ok=0;
        for(int i=0;i<cnt;i++)
        {
            if(judge(tmp[cnt].p1,tmp[cnt].p2,tmp[i].p1,tmp[i].p2))
            {
                flag=1,tmp1=max(tmp1,tmp[i].p1.x);    
            }
        }
        if(!flag)
        {
            dfs(tc-d,tr,1,dis+d);
            dfs(tc-d,tr,3,dis+d);
        }
        cnt--;
        if(flag)
        {
            d=tc-tmp1-1;
            mx=max(mx,d+dis);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        c[i].push_back(0),r[i].push_back(0); //处理边界的障碍 
    for(int i=1,t;i<=m;i++)
    {
        scanf(" %c%d",&ch,&t);//注意冒号里的空格，scanf大法好 
        ch-='A'-1;
        c[t].push_back(ch);
        r[ch].push_back(t);
    }
    for(int i=1;i<=n;i++)
        c[i].push_back(n+1),r[i].push_back(n+1);//处理边界的障碍 
    tmp[++cnt]=line(point(1,1),point(1,1));//初始位置来一条长度线段
    dfs(1,1,1,1);
    dfs(1,1,2,1);//两个方向去搜索 
    printf("%d\n",mx);
}
```

---

## 作者：罗旅洲 (赞：3)


**代码长度目测比楼下都短 目前最美。。。**


绝对要注意：读入可以不用cin，我scanf一遍过


比196453250cn更短，更快，更强


```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
using namespace std;
bool map[123][123];
int n,m,ans=0,d[4][2]={{1,0},{-1,0},{0,1},{0,-1}},tx,ty; // 转向的数组
char s[10],vis[123][123];                        // d[i][p] i=0 左， =1 右， =2 下， =3 上
void dfs(int x,int y,int dir,int num){    //x,y表示当前坐标，dir为当前方向，num表示经过点数
    if(vis[x][y]) {                // 是否经过
        ans=max(ans,num-1);      //num-1因为这个点算了两次
        return ;
    }
    vis[x][y]=1;
    tx=x+d[dir][0]; ty=y+d[dir][1];
    if(map[tx][ty])
        For(i,0,3){                //考虑转向
            if(i==dir) continue;        
            tx=x+d[i][0];
            ty=y+d[i][1];
            if(!map[tx][ty])
                   dfs(tx,ty,i,num+1);
            }
    else dfs(tx,ty,dir,num+1);    //不用转向
    vis[x][y]=0;                //记得回溯
}
int main(){
    int l,k;
    scanf("%d%d",&n,&m);
    For(i,1,m){
        scanf("%s",s);
        l=strlen(s); k=0;
        For(i,1,l-1) k=(k<<3)+(k<<1)+(s[i]^48);        //存图
        map[s[0]-64][k]=1;
    }
    For(i,1,n) map[i][0]=map[0][i]=map[n+1][i]=map[i][n+1]=1;    //处理边界
    dfs(1,1,0,1);  dfs(1,1,2,1);    //出发要不向左，要不向下
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：zhz小蒟蒻 (赞：3)

### ~~一发过样例、题目，真开森!~~
咳咳，进入正题  
其实这题并没有想象中的复杂，就是一个智障的大爆搜，我感觉我都没有加上什么优化，然后就 $AC$ 了。  
![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1564149298100&di=01f7f0cd039525f80a3b84201caf6b16&imgtype=0&src=http%3A%2F%2Fimg.wxcha.com%2Ffile%2F201703%2F17%2Fe8b8bcb139.jpeg)  
我用的有点像是记忆化搜索，然而事实上可以不这么用。  
每次搜索路径时，我们就一条道走到黑，不撞南墙不回头，然后在遇到障碍或边界时，枚举其余的方向，再碰到自己走过的路径便停下来，开始回溯   
$Code:$
```
#include <iostream>
#include <cstdio>
using namespace std;
bool book[121][121];
int n,b,ans=0;
int a[121][121],f[121][121][5][2]; 
int t1[5]={0,0,1,0,-1};
int t2[5]={0,1,0,-1,0};
int dfs(int x,int y,int move); 
bool check(int x,int y);
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);	 
	scanf("%d %d",&n,&b);
	for(int i=1;i<=b;++i)
	{
		char ch;int num;
		cin>>ch>>num;
		a[num][ch-'A'+1]=1; //在地图上标记出障碍
	} 
	printf("%d",max(dfs(1,1,1),dfs(1,1,2))); //注意，从起点出发的时候，有两条路可以走，右边和下边
	return 0;
} 
bool check(int x,int y)  //判断函数，判断现在是否遇到了障碍、边界或者自己走过的路
{
	if(x>n || x<1 || y>n || y<1 || a[x][y] || book[x][y]) return true;
	return false; 
}
int dfs(int x,int y,int move) //x是横坐标,y是纵坐标,move是移动的方向:1表示右,2表示下,3表示左,4表示上
{
	int d=1;  //记录每个方向的最大值
	book[x][y]=true; //标记这个点已经来过
	int tx=x+t1[move],ty=y+t2[move]; //判断目前移动的方向
	if(!book[tx][ty]) //如果没来过这个点，才能进行下面的判断
	{
		if(check(tx,ty))  //检测是否合法
		{
			for(int i=1;i<=4;++i)//如果不合法，那么选择一条可以走的路
			{
				tx=x+t1[i]; ty=y+t2[i];
				if(!check(tx,ty)) //下一个点也必须合法
					d=max(d,dfs(tx,ty,i)+1); 
			}
		}
		else //如果合法，那么就继续往下走
			d=dfs(tx,ty,move)+1; //统计走过的个数时注意加上自己本身这个节点
	}
	book[x][y]=false; //无路可走后，把这个点的标记删掉
	return d; //返回在x,y能走的最大节点数
}
```

---

## 作者：chihik (赞：2)

这道题是一道典型的搜索题，我们用$dfs(x,y,step,s)$表示蜗牛在$(x,y)$这个点，走了$step$步，当前的方向（起点的$s=0$，特殊处理一下）。

当蜗牛确定一个方向后，我们就不断让它前进，同时记录它走过的格子，直到它遇到障碍，出界或者到达已走过的点停止。

如果蜗牛遇到障碍，我们就枚举每个方向，因为前方有障碍，后方已经走过，所以蜗牛只会向左或向右转，不需要特殊处理。

代码中$goto$的作用是找到后面的单词，使之跳过一些语句，感觉作用比$break$,$continue$强，可以减少一些判断。

最后是代码：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 120;
char x;
int n,m,y,Ans;
char Map[ MAXN + 5 ][ MAXN + 5 ];
bool vis[ MAXN + 5 ][ MAXN + 5 ];

int tx[ 5 ] = { 0 , 1 , -1 , 0 , 0 };
int ty[ 5 ] = { 0 , 0 , 0 , 1 , -1 };
void dfs( int x , int y , int step , int s ) {
	Ans = max( Ans , step );
	if( s ) {
		int fx = x + tx[ s ] , fy = y + ty[ s ];
		if( fx == 0 || fy == 0 || fx == n + 1 || fy == n + 1 || Map[ fx ][ fy ] == '#' )
			goto there;
		if( vis[ fx ][ fy ] )
			return;
		vis[ fx ][ fy ] = 1;
		dfs( fx , fy , step + 1 , s );
		vis[ fx ][ fy ] = 0;
		return;
	}
	there:;
	for( int i = 1 ; i <= 4 ; i ++ ) {
		int fx = x + tx[ i ] , fy = y + ty[ i ];
		if( fx == 0 || fy == 0 || fx == n + 1 || fy == n + 1 || Map[ fx ][ fy ] == '#' || vis[ fx ][ fy ] )
			continue;
		vis[ fx ][ fy ] = 1;
		dfs( fx , fy , step + 1 , i );
		vis[ fx ][ fy ] = 0;
	}
}

int main( ) {
	scanf("%d %d",&n,&m);
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= n ; j ++ )
			Map[ i ][ j ] = '.';
	for( int i = 1 ; i <= m ; i ++ ) {
		cin >> x;
		scanf("%d",&y);
		Map[ y ][ x - 'A' + 1 ] = '#';
	}
	/*for( int i = 1 ; i <= n ; i ++ ) {
		for( int j = 1 ; j <= n ; j ++ )
			printf("%c",Map[ i ][ j ]);
		printf("\n");
	}*/
	vis[ 1 ][ 1 ] = 1;
	dfs( 1 , 1 , 1 , 0 );
	printf("%d",Ans);
	return 0;
}
```


---

## 作者：Exber (赞：1)

## 题意
- ### 给你一个 $n*n$ 的棋盘，棋盘上有一些障碍。
- ### 一直很笨的蜗牛会沿着某个方向一直走，撞到墙它可以左拐或者右拐，遇到自己已经走过的格子它就停下来不走了。
- ### 现在这只蜗牛从 (1,1) 的位置出发，请问它最多能走多少格。

## 做法
这道题其实相当于一个 dfs 的模板。

可是，为什么 dfs **不会超时**？

障碍数可是达到了 200 的，时间复杂度不是会达到 $O(2^{200})$ 吗？

原因很简单，因为每一个格子**只能走一遍**，所以时间复杂度并没有那么高，只有 $O(n^2)$。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n,m,mp[125][125],dx[]{0,0,1,-1},dy[]{1,-1,0,0};
bool vis[125][125];

inline bool can(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=n&&mp[x][y]==0&&!vis[x][y];
}

int count(int x,int y,int f)
{
	int nx=x+dx[f],ny=y+dy[f]; // 下一步的位置 
	if(vis[nx][ny]) // 走过了，不用走了 
	{
		return 1;
	}
	int ans=0;
	if(!can(nx,ny)) // 撞墙了 
	{
		for(int i=0;i<4;i++) // 枚举转弯方向 
		{
			int nnx=x+dx[i],nny=y+dy[i]; // 转弯后的位置 
			if(can(nnx,nny)) // 能走就一定是往左或者往右 
			{
				vis[nnx][nny]=true; // 标记 
				ans=max(ans,count(nnx,nny,i)); // 往新方向走 
				vis[nnx][nny]=false; // 取消标记 
			}
		}
	}
	else
	{
		vis[nx][ny]=true; // 标记 
		ans=count(nx,ny,f); // 一直往这个方向走下去 
		vis[nx][ny]=false; // 取消标记 
	}
	return ans+1; // 记得加上当前格 
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		char x;
		int y;
		scanf(" %c%d",&x,&y); // 注意一下输入格式
		mp[x-'A'+1][y]=1;
	}
	vis[1][1]=true; // 起点走过了 
	printf("%d\n",max(count(1,1,0),count(1,1,2))); // 往左和往下 
	return 0;
}
```


---

## 作者：_OJF_ (赞：0)

这道题的题意翻译的很准确，不再赘述，直接开始说明

每次遇到障碍时它可以转，否则不可以转，所以此时就可以得到在前方可以走时，直接往前走

如果遇到障碍就可以分两种情况，将两种情况分别判断可不可行，然后进行dfs

输入也非常简单，只要把边界看作障碍即可

ps：标记已走过的时候千万要和障碍区分开！不能直接当做障碍！这样遇到自己路线就能转弯然后使结果错误（我调了多久来着？）

dfs函数：

$dfs(x, y, d, step)$为在$(x,y)$，方向为$d$，已走$step$步的情况

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, b, a, m[125][125], flag[125][125], ans, dx[5] = {0, 0, 1, 0, -1}, dy[5] = {0, 1, 0, -1, 0};
char c;
void dfs(int x, int y, int d, int step){
	if(!m[x][y] || flag[x][y])
		return;
	ans = max(ans, step);
    if(m[x + dx[d]][y + dy[d]] != 0){
        flag[x][y] = 1;
        dfs(x + dx[d], y + dy[d], d, step + 1);
        flag[x][y] = 0;
    } else {
        for(int i = 1;i <= 4;i++){
        	if(m[x + dx[i]][y + dy[i]] == 1 && (i + d) % 2){ 
               flag[x][y] = 1;  
               dfs(x + dx[i], y + dy[i], i, step + 1);
               flag[x][y] = 0;
            } 
        }
    }
}
int main(){
	cin>>n>>b;
	for(int i = 1;i <= b;i++){
		cin>>c>>a;
		m[c - 'A' + 1][a] = 1;
	}
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            m[i][j] = 1 - m[i][j];
	dfs(1, 1, 1, 1);
	dfs(1, 1, 2, 1);
	cout<<ans;
	return 0;
}
```


---

## 作者：Celebrate (赞：0)

这一道题暴力即可，大约几万次的样子，不用怕超时

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[210][210];
int ans;
const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};//搜索方向
void dfs(int x,int y,int t,int k)
{
    if(k>ans) ans=k;//取最大值 
    if(a[x+dx[t]][y+dy[t]]==1) //如果正方向可以走 
	{
        a[x][y]=2;
        dfs(x+dx[t],y+dy[t],t,k+1); //往下走 
        a[x][y]=1;
    }
    else if(a[x+dx[t]][y+dy[t]]==0)//如果前面不可以走 
    {
        for(int i=0;i<4;i++)//换一个方向走 
    	{
            if(a[x+dx[i]][y+dy[i]]==1 && (i+t)%2!=0)
			{
                a[x][y]=2;  
                dfs(x+dx[i],y+dy[i],i,k+1);
                a[x][y]=1;
            } 
        }
    }
}
int main()
{
	int i,j,v;
	char c;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++)
	{
        cin>>c>>v;//输入 
        a[c-'A'+1][v]=1;//先把障碍存为1 
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
		{
            if(a[i][j]==1) a[i][j]=0;
            else a[i][j]=1;//1和0替换，障碍和边界设为0 ，可走格设为1 
        }
    }
    dfs(1,1,0,1);//搜索方向：向右 
    dfs(1,1,1,1);//搜索方向：向下 
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Checkmate (赞：0)

这题我用了一个很神奇（奇葩）的方法，就是在某个位置若方向满足条件(会撞上)就标记为1（方便在深搜时转弯）；

我们用一个map[x][y][dire]的三维数组储存：在坐标为（x,y）的地方若此时方向为dire且map[x][y][dire]=1就需要转弯；

当然首先要将字符转化为数字；

方向用数字表示：1->向下，2->向右，3->向上，4->向左；

例如：有路障（E,2）;

所以我们让：

```cpp
map[E-‘A’+1][2+1][3]=1;
map[E-'A'+1][2-1][1]=1;
map[E-'A'+1-1][2][2]=1;
map[E-'A'+1+1][2][4]=1;
```
边界同理；



```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
const int maxn=1500;
using namespace std;
bool vis[maxn][maxn];
int n,ans,k,dire;
int a[maxn][maxn];
int dir[5][2]={{0,0},{0,1},{1,0},{0,-1},{-1,0}};// 1->向下，2->向右，3->向上，4->向左； 
int map[maxn][maxn][5];//在哪个位置朝哪个方向； 
bool flag;
void dfs(int x,int y,int step)
{
    if(x>n || y>n || x<=0 || y<=0){return;}//超出边界回溯 
    if(a[x][y]){return;}//遇到障碍回溯 
    if(vis[x][y] && step>ans){ans=step;return;}//遇到走过的路，更新答案； 
    if(vis[x][y])return;
//    cout<<x<<" "<<y<<endl;
    vis[x][y]=1;
//    system("pause");
    if(dire==1)dfs(x,y+1,step+1);
    else if(dire==2)dfs(x+1,y,step+1);
    else if(dire==3)dfs(x,y-1,step+1);
    else if(dire==4)dfs(x-1,y,step+1);
    if(map[x][y][dire])
    {
        int l=dire;//l 用于记录dire原来的值方便回溯； 
        for(int i=1;i<=4;i++)
        {
            dire=i;
            dfs(x+dir[i][0],y+dir[i][1],step+1);
            dire=0;
        }
        dire=l;//回溯，防止对之前的状态有影响； 
    }
    vis[x][y]=0;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++)
    {
        char s;
        int x;
        cin>>s;
        scanf("%d",&x);
        a[s-'A'+1][x]=1;//路障的位置；
        map[s-'A'+1][x+1][3]=1;//路障旁边的四个格子分别做上标记表示在此位置在此方向需要转弯； 
        map[s-'A'+1][x-1][1]=1;
        map[s-'A'][x][2]=1;
        map[s-'A'+2][x][4]=1;
    }
    for(int i=1;i<=n;i++)
    {
        map[i][1][3]=1;//更新边界； 
        map[i][n][1]=1;
        map[1][i][4]=1;
        map[n][i][2]=1;
    }
    dire=1;//先向下搜 ； 
    dfs(1,1,0);
    dire=2;//再向右搜； 
    dfs(1,1,0);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Drinkwater (赞：0)

这道题没什么特别难的地方，主要是一些细节，处理好细节特别重要，我们每次走到一个点，然后就枚举4个方向看能不能走，能走就一直走到底，然后搜索加上回溯就可以了，最主要的一点，记得输入要用cin，我就是因为这个被卡了一下午。









```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define REP(i,a,b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++i)
inline int read()
{
    char c = getchar();register int fg = 1, sum = 0;
    while(c < '0' || c > '9')
    {
        if(c == '-')fg = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
    {
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return fg * sum;
}
int n,m;
char s[20];
int vis[150][150],ans;
void print()
{
    REP(i,1,n)
    {
        REP(j,1,n)
            cout<<vis[i][j]<<" ";
        cout<<endl;
    }
}
void dfs(int x,int y,int sum)
{
    ans = max(ans,sum);
    if(x - 1 > 0 && !vis[x-1][y])//上
    {
        int flag = 0,cnt = 0;
        int tmp = x - 1;
        while(tmp > 0)//能走就走到底
        {
            if(vis[tmp][y] == 1){flag = 1;break;}//遇到以前退出
            if(vis[tmp][y] == 2)break;//遇到障碍退出
            vis[tmp][y] = 1,tmp--,cnt++;
        }tmp++;
        ans = max(ans,sum+cnt);
        if(!flag)dfs(tmp,y,sum+cnt);
        while(tmp < x)vis[tmp][y] = 0,tmp++;//回溯
    }
    if(x + 1 <= n && !vis[x+1][y])//下
    {
        int flag = 0,cnt = 0;
        int tmp = x+1;
        while(tmp <= n)
        {
            if(vis[tmp][y] == 1){flag = 1;break;}
            if(vis[tmp][y] == 2)break;
            vis[tmp][y] = 1,tmp++,cnt++;
        }tmp--;
        ans = max(ans,sum + cnt);
        if(!flag)dfs(tmp,y,sum+cnt);
        while(x < tmp)vis[tmp][y] = 0,tmp--;
    }
    if(y - 1 > 0 && !vis[x][y-1])//左
    {
        int flag = 0,cnt = 0;
        int tmp = y - 1;
        while(tmp > 0)
        {
            if(vis[x][tmp] == 1){flag = 1;break;}
            if(vis[x][tmp] == 2)break;
            vis[x][tmp] = 1,tmp--,cnt++;
        }tmp++;
        ans = max(ans,sum + cnt);
        if(!flag)dfs(x,tmp,sum+cnt);
        while(tmp < y)vis[x][tmp] = 0,tmp++;
    }
    if(y + 1 <= n && !vis[x][y+1])//右
    {
        int flag = 0,cnt = 0;
        int tmp = y + 1;
        while(tmp <= n)
        {
            if(vis[x][tmp] == 1){flag = 1;break;}
            if(vis[x][tmp] == 2)break;
            vis[x][tmp] = 1,tmp++,cnt++;
        }tmp--;
        ans = max(ans,sum + cnt);
        if(!flag)dfs(x,tmp,sum+cnt);
        while(y < tmp)vis[x][tmp] = 0,tmp--;
    }
}
int main()
{
//    freopen("input.in","r",stdin);
//    freopen("output.out","w",stdout);
    scanf("%d%d",&n,&m);    
    char c;
    int x;
    REP(i,1,m)
    {
        cin>>c>>x;
        vis[c-'A'+1][x] = 2;
    }
    vis[1][1] = 1;
    dfs(1,1,1);//搜索，从1,1开始，步数为1
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：Jason_Yvan (赞：0)

一开始以为dfs会爆，最后发现数据很小，然后爆搜就可以过。

不过被输入坑了，好像要用cin读入，读入优化和scanf都会错

所以大家还是老老实实的用cin读入吧


不需要剪枝，模拟每一种走法

**走到自己以前走过的地方就整个散步就停止了**

重要代码处有说明！

C++代码：

/*************************************************************************

    > Author: wzw-cnyali
    > Created Time: 2017/4/13 19:53:51
************************************************************************/















```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define EREP(i, a) for(register int i = (be[a]); i != -1; i = nxt[i])
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template <class T>
T read(T sum = 0, T fg = 0)
{
    char c = getchar();
    while(c < '0' || c > '9') { fg |= c == '-'; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return fg ? -sum : sum;
}
const int inf = 0x3f3f3f3f;
const int Size = 200;
const int maxn = 100000;
const int maxm = 100000;
int n;
int ans;
bool map[Size][Size];
bool vis[Size][Size];
bool judge(int x, int y)//判断是否出界
{
    if(x < 1 || y < 1 || x > n || y > n) return 0;
    return 1;
}
//0是up， 1是down， 2是right， 3是left
void dfs(int x, int y, int sum, int direct)
{
    chkmax(ans, sum);
    if(direct == 0)
    {
        if(vis[x - 1][y]) return;
        if(judge(x - 1, y) && !map[x - 1][y])//笔直走
        {
            vis[x - 1][y] = 1;
            dfs(x - 1, y, sum + 1, 0);
            vis[x - 1][y] = 0;
            return;
        }
        else//转向
        {
            if(judge(x, y + 1) && !map[x][y + 1] && !vis[x][y + 1])
            {
                vis[x][y + 1] = 1;
                dfs(x, y + 1, sum + 1, 2);
                vis[x][y + 1] = 0;
            }
            if(judge(x, y - 1) && !map[x][y - 1] && !vis[x][y - 1])
            {
                vis[x][y - 1] = 1;
                dfs(x, y - 1, sum + 1, 3);
                vis[x][y - 1] = 0;
            }
        }
    }
    else if(direct == 1)
    {
        if(vis[x + 1][y]) return;
        if(judge(x + 1, y) && !map[x + 1][y])//笔直走
        {
            vis[x + 1][y] = 1;
            dfs(x + 1, y, sum + 1, 1);
            vis[x + 1][y] = 0;
            return;
        }
        else//转向
        {
            if(judge(x, y + 1) && !map[x][y + 1] && !vis[x][y + 1])
            {
                vis[x][y + 1] = 1;
                dfs(x, y + 1, sum + 1, 2);
                vis[x][y + 1] = 0;
            }
            if(judge(x, y - 1) && !map[x][y - 1] && !vis[x][y - 1])
            {
                vis[x][y - 1] = 1;
                dfs(x, y - 1, sum + 1, 3);
                vis[x][y - 1] = 0;
            }
        }
    }
    else if(direct == 2)
    {
        if(vis[x][y + 1]) return;
        if(judge(x, y + 1) && !map[x][y + 1])//笔直走
        {
            vis[x][y + 1] = 1;
            dfs(x, y + 1, sum + 1, 2);
            vis[x][y + 1] = 0;
            return;
        }
        else//转向
        {
            if(judge(x + 1, y) && !map[x + 1][y] && !vis[x + 1][y])
            {
                vis[x + 1][y] = 1;
                dfs(x + 1, y, sum + 1, 1);
                vis[x + 1][y] = 0;
            }
            if(judge(x - 1, y) && !map[x - 1][y] && !vis[x - 1][y])
            {
                vis[x - 1][y] = 1;
                dfs(x - 1, y, sum + 1, 0);
                vis[x - 1][y] = 0;
            }
        }
    }
    else if(direct == 3)
    {
        if(vis[x][y - 1]) return;
        if(judge(x, y - 1) && !map[x][y - 1])//笔直走
        {
            vis[x][y - 1] = 1;
            dfs(x, y - 1, sum + 1, 3);
            vis[x][y - 1] = 0;
            return;
        }
        else//转向
        {
            if(judge(x + 1, y) && !map[x + 1][y] && !vis[x + 1][y])
            {
                vis[x + 1][y] = 1;
                dfs(x + 1, y, sum + 1, 1);
                vis[x + 1][y] = 0;
            }
            if(judge(x - 1, y) && !map[x - 1][y] && !vis[x - 1][y])
            {
                vis[x - 1][y] = 1;
                dfs(x - 1, y, sum + 1, 0);
                vis[x - 1][y] = 0;
            }
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    int m;
    scanf("%d%d", &n, &m);
    REP(i, 1, m)
    {
        char c; int x;
        cin>>c>>x;
        map[x][c - 'A' + 1] = 1;
    }
    vis[1][1] = 1;
    REP(i, 1, 2)
    {    
        dfs(1, 1, 1, i);//起点有两种走法
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Till_Gloam (赞：0)

###代码长度目测比楼下短 目前最美。。。

绝对要注意：读入用cin  读入用cin   读入用cin(重要的事情说三遍） ， 我因为这个WA了好几遍

其实逻辑和楼下的差不多， 看注释吧






```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
int n, b, ans;
int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};//四个方向
bool map[150][150], walk[150][150];//map记障碍， walk记是否走过
char c;
void dfs(int x, int y, int step, int D){
    walk[x][y] = 1;                     //标记走过
    int i, x1 = x + d[D][0], y1 = y + d[D][1];       //向前走到（x1, y1）
    if(!map[x1][y1] && x1 && y1 && x1 <= n && y1 <= n && !walk[x1][y1]){
        dfs(x1, y1, step + 1, D);              //能直走就走
    }else{
        if(walk[x1][y1]){
            if(step > ans) ans = step;        //走过就停
        }else{
            bool flag = 0;
            for(i = 0; i < 4; ++i){
                if(i == D) continue;
                int X = x + d[i][0], Y = y + d[i][1];
                if(!map[X][Y] && X && Y && X <= n && Y <= n && !walk[X][Y]){
                    flag = 1;
                    dfs(X, Y, step + 1, i);             //能转就转
                }
            }
            if(!flag && step > ans) ans = step;              //不能转就停
        }
    }
    walk[x][y] = 0;                       //回溯
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("Usa.in", "r", stdin);
    freopen("Usa.out","w",stdout);
#endif
    int i;
    scanf("%d%d", &n, &b);
    for(i = 1; i <= b; ++i){
        int a, b;
        cin>>c>>b;                      //读入用cin
        a = c - 'A' + 1;
        map[a][b] = 1;
    }
    dfs(1, 1, 1, 0);         //当前在（1， 1）， 走了1步， 方向向上（0） -》 这样就能一开始自动枚举所有方向， 不需打两遍dfs
    printf("%d", ans);                    //嗯， AC
    return 0;
}
```

---

## 作者：never_see (赞：0)

**###代码长度是楼下的一半 目前最短。**

**思路很简单，**

一个方向可以走的话就一直走，

遇到有障碍的地方就开始选方向(不用考虑是否能拐弯，因为直走方向不行，倒退的方向已经标记过)，

遇到走过的地方就返回上一级，

差不对就这样了。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int map[201][201];int tot=1;int n,b,y;char x;
int mx[]={1,0,-1,0};int my[]={0,-1,0,1};bool bo[201][201];int MAX=0;//map表示地图上的障碍，bo表示是否走过
bool check(int x,int y){return (x>=1&&x<=n&&y>=1&&y<=n&&!map[x][y]&&!bo[x][y]);}//判断目前到的这一点是否可行
void dfs(int x,int y,int dir)//dir为上一次方向
{
    int xx=x+mx[dir];
    int yy=y+my[dir];
    if(bo[xx][yy])//如果碰到了走过的地方
    {
        if(MAX<tot)
            MAX=tot;
        return ;
    }
    if(map[xx][yy]||xx<1||yy<1||xx>n||yy>n)//如果碰到了障碍
    {
        for(int i=0;i<=3;i++)
        {
            xx=x+mx[i];
            yy=y+my[i];
            if(check(xx,yy))
            {
                tot++;
                bo[xx][yy]=1;
                dfs(xx,yy,i);
                bo[xx][yy]=0;
                tot--;
            }
        }
        if(tot>MAX)MAX=tot;//时刻为MAX更新
        return ;
    }
    tot++;//直走
    bo[xx][yy]=1;
    if(tot>MAX)MAX = tot;
    dfs(xx,yy,dir);
    bo[xx][yy]=0;
    tot--;
}
int main()
{
    scanf("%d%d",&n,&b);
    for(int i=1;i<=b;i++)
    {
        cin>>x>>y;//scanf似乎有毒
        map[y][x-'A'+1]=1;
    }
    bo[1][1]=1;
    dfs(1,1,0);//开始的第一次方向有两种
    dfs(1,1,3);
    printf("%d",MAX);
    return 0;
}
```

---

## 作者：JOHNKRAM (赞：0)

乍一看，N≤120，肯定不能用搜索。其实，由于必须走到头才能转弯，所以真正有效的状态数并不多。

直接搜索即可，不过细节处理有点麻烦。


---

## 作者：funky_monkey (赞：0)

```cpp
/* 
LGOJ P1560 [USACO5.2]蜗牛的旅行Snail Trails
时空限制：1s 128MB 
这道题的数据范围比较小，只有120，可以用dfs的暴力算法。
但是，这道题有一些注意点：
1、首先是输入，输入时用scanf时要这样写： scanf("\n%c%d",&temp1,&temp2); 否则读入的第一个字符为换行符。 
2、其次，这道题的横纵坐标与我们习惯性所使用的不同，要注意。
3、搜索时遇到障碍物转向或停止，这时，一定要注意回溯到上一个转向点。
4、数组不要满打满算，开大一点。
*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN=120+10;
char m[MAXN][MAXN];// '#'为边界或障碍 'X'为已走过的点 '.'为可以走的点 
int tempm,n,step=1,ans=1;
int dx[4]={1,0,0,-1};//方向 
int dy[4]={0,-1,1,0};
void dfs(int x,int y,int dire)
{
	//这个dfs函数的主要思想：先按照方向往前走，每一步判断下一步是否可以走。若不可以，就转向。 
	int X0=x,Y0=y;
	if(m[X0+dx[dire]][Y0+dy[dire]]!='.')
	{ ans=max(step,ans); return; }//如果转向后往前走还是障碍，说明走进了死胡同，停止搜索。 
	do
	{
		X0+=dx[dire]; Y0+=dy[dire]; 
		m[X0][Y0]='X'; 
		step++;
	}while(m[X0+dx[dire]][Y0+dy[dire]]=='.');//没有障碍物，始终往固定方向走。 
	ans=max(step,ans);
	if(m[X0+dx[dire]][Y0+dy[dire]]!='X')//碰到障碍物，转向搜索。 
	{
		dfs(X0,Y0,0);
		dfs(X0,Y0,1);
		dfs(X0,Y0,2);
		dfs(X0,Y0,3);
	}
	while(!(X0==x&&Y0==y))//回溯到上一转向点。 
	{
		step--;
		m[X0][Y0]='.'; 
		X0-=dx[dire]; Y0-=dy[dire];
	}
	return;
}
int main()
{
	scanf("%d%d",&n,&tempm);
	for(int i=0;i<=101;i++)
		for(int j=0;j<=101;j++)
			m[i][j]='#';
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			m[i][j]='.';
	for(int i=1;i<=tempm;i++)
	{
		char temp1;
		int temp2;
		scanf("\n%c%d",&temp1,&temp2);//读入这里注意一下
		m[temp2][temp1-'A'+1]='#';
	}
	m[1][1]='X';
	dfs(1,1,0);//向右、下搜索 
	dfs(1,1,2);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Myrcella (赞：0)

这道题第一反应就是深搜dfs辣。。。

~~感觉大概是一道假蓝题~~

但是本人调了一个下午！！（当然其中是包括了我打游戏看QQ眺望远方思考人生的时间的……

原因就是一个我至今都不知道怎么回事的玄学错误

输入！！！输入！！！

窝一开始是这么写的
```cpp
scanf("%d%d",&n,&b);
for (int i=0; i<b; i++) {
    string s;
    cin>>s;
    int x=s[1]-'1',y=s[0]-'A';
    g[x][y]=true;
}
```
然后很快写完 测完样例 想着这道题肯定能一遍A掉 然后就可以偷偷van一会儿辣。。信心满满的交了结果41分！！41分！！我写的时候明明思路很清晰啊。。不会有问题的啊。。。

然后苦逼的我对着题解里面的程序查了快一个下午总是有一些奇奇怪怪的问题。。。然后在一次长时间的思考人生后，我开始怀疑输入。我把输入改成了AC程序的输入 然后就过了 过了！！

窝真的不知道原来的写法有啥问题 求大佬解答。。（update：那啥我好想知道怎么回事了 如果n≥10的话那样读入数字就有问题了233 看来不是玄学错误只是太菜了qwq

然后贴上我的程序辣 代码虽然很丑但不算很长啊OvO
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
//聪明的你们一定会发现，这里是按顺时针排列的。
//于是+1或-1则是旋转90°后的方向

int n,b;
bool g[130][130];//记录障碍
int ans=0;//记录答案
bool vis[130][130];//dfs时记录格子是否已被当前路径经过

bool inrange(int x,int y) {//判断有没有到图外面去
    return x>=0&&x<n&&y>=0&&y<n;
}

void dfs(int i,int j,int dir,int cur,bool can){
//can标记是否已经改变过方向。
//因为方向只能改变一次。要不然就死循环辣
    if (vis[i+dx[dir]][j+dy[dir]]) {//不能走啦！
        ans=max(ans,cur);
        return;
    }
    if (g[i+dx[dir]][j+dy[dir]]==true||!inrange(i+dx[dir],j+dy[dir])) {
        if (can==false){//方向已被改变就不能再改啦
            ans=max(ans,cur);
            return;
        }
        dfs(i,j,(dir+3)%4,cur,false);
        //can=false 不可以再次改变方向 
        //该步只执行方向改变的操作 因此坐标和计数器均不变
        dfs(i,j,(dir+1)%4,cur,false);
    }
    else {
        vis[i][j]=true;
        dfs(i+dx[dir],j+dy[dir],dir,cur+1,true);
        vis[i][j]=false;//勿忘回溯！！
    }
}

int main() {
    scanf("%d%d",&n,&b);
    char c;
    int v;
    for (int i=0; i<b; i++) {//坑死人的输入。。
        cin>>c>>v;
        g[c-'A'][v-1]=1;
    }
    dfs(0,0,1,1,true);//从起点出发可以向下和向右走
    dfs(0,0,0,1,true);
    cout<<ans<<endl;
}
```

---

