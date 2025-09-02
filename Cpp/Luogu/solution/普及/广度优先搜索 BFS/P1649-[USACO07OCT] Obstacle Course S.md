# [USACO07OCT] Obstacle Course S

## 题目描述

Consider an N x N (1 <= N <= 100) square field composed of 1

by 1 tiles. Some of these tiles are impassible by cows and are marked with an 'x' in this 5 by 5 field that is challenging to navigate:

```cpp
. . B x . 
. x x A . 
. . . x . 
. x . . . 
. . x . . 
```
Bessie finds herself in one such field at location A and wants to move to location B in order to lick the salt block there.  Slow, lumbering creatures like cows do not like to turn and, of course, may only move parallel to the edges of the square field. For a given field, determine the minimum number of ninety degree turns in any path from A to B. The path may begin and end with Bessie facing in any direction. Bessie knows she can get to the salt lick.



## 说明/提示

只可以上下左右四个方向行走，并且不能走出这些格子之外。开始和结束时的方向可以任意。

### 数据范围及约定

对于全部数据，保证 $2\le N\le 100$。


## 样例 #1

### 输入

```
3
. x A
. . .
B x .```

### 输出

```
2```

# 题解

## 作者：Lidy (赞：59)

```cpp
/*
此题数据范围是n<=100,本来正解是bfs或者最短路径spfa
我先想用暴搜试一下看能拿多少分
没想到居然能AC，但是我后来调了一下，发现这是一个有点巧的事情
如果你把方向数组的顺序改一下，也许就只能拿90，不管怎么说，我还是侥幸过了
思路还是很好理解。
下面上代码 ： 
*/ 
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,x0,y0,xn,yn,ans=0x7fffffff/2,bj;char l;
int a[105][105];
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
//右 下 左  上 
void Read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	    {
	    	cin>>l;//读入字符的时候因为题目说了有空格，所以用cin而没用scanf 
	    	if(l=='A')x0=i,y0=j,a[i][j]=-1;//标记不能重复走 
	    	if(l=='B')xn=i,yn=j,a[i][j]=0;
	    	if(l=='x')a[i][j]=-1;
    	}
} 
void dfs(int x,int y,int t,int k)
//x坐标+y坐标+t为上次的方向+k为当前转角次数 
{
	if(k>=ans)return ;
	//剪枝！！！ ：不管你搜到没有，因为本题是求的最少次数，所以如果发现当前的k都大于ans，那么直接return 
	if(x==xn&&y==yn){ans=min(ans,k);bj=1;return ;}//取ans最小并标记找到 
	for(int i=0;i<4;i++)
	{
		int nx=dx[i]+x;int ny=dy[i]+y;//四个方向的走后点的新坐标 
		if(nx<=0||nx>n||ny<=0||ny>n)continue;//判界 
		if(!a[nx][ny])//不走回路 
		{
			a[nx][ny]=-1;//标记不能走 
		    int f=0;
			if(i!=t)f=1;if(t==-1)f=0;//f判断方向，如果当前方向i与上一次的方向t不同，说明要转向，记f=1 
	    	dfs(nx,ny,i,k+f);
	    	//下一个位置的坐标+方向+次数累加 
	    	a[nx][ny]=0;//回溯 
		}
	}
}
int main()
{
    Read();
    dfs(x0,y0,-1,0);//下面是暴力dfs 
    if(bj)printf("%d",ans);
    else printf("-1");
    return 0;
} 
```

---

## 作者：「QQ红包」 (赞：44)

题解by：redbag

其实就是暴力，一个格子一个格子的搜，每次只扩展一个（因为不一定需要走到底）

然后扩展之后入队，

注意：每个点不止入队一次，因为可能之后找到了更优的方案（毕竟是拐弯次数啊）

然后具体见代码

```cpp
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
int read(){
    char s;
    int k=0,base=1;
    while((s=getchar())!='-'&&s!=EOF&&!(s>='0'&&s<='9'));
    if(s==EOF)exit(0);
    if(s=='-')base=-1,s=getchar();
    while(s>='0'&&s<='9')
    {
        k=(k<<1)+(k<<3)+(s-'0');
        s=getchar();
    }
    return k*base;
}
void write(int x)
{
    if(x<0){putchar('-');write(-x);}
    else{if(x/10)write(x/10);putchar(x%10+'0');}
}
int n;
int sx,sy,tx,ty;
int a[110][110];
int d[110][110];
struct node
{
    int x,y;
    int d;
    int f;
};
int ans;
int fx[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
queue<node> q;
int main()
{
    n=read();
    char ch;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {//只有1的地方可以走
            ch=getchar();
            while (ch!='A'&&ch!='B'&&ch!='.'&&ch!='x') ch=getchar();
            //神奇读入，只要不是自己要的就丢掉 
            if (ch=='A') a[i][j]=1,sx=i,sy=j; else
            if (ch=='B') a[i][j]=1,tx=i,ty=j; else
            if (ch=='.') a[i][j]=1;//标记，s：起点，t：终点 
        }
    }
    node aa;//起点入队 
    aa.x=sx;aa.y=sy;aa.d=0;aa.f=-1;
    memset(d,1,sizeof(d));
    a[aa.x][aa.y]=233;//和'x'分开，因为一个点可能反复入队
    //（第一次找到的不一定是最优解，亲测30分） 
    d[aa.x][aa.y]=0;//打标记 
    q.push(aa);
    ans=23333333;
    while (!q.empty())
    {
        node u;
        u=q.front();
        q.pop();
        if (u.d>ans) continue;//搜索剪枝，如果转弯次数大于ans就不用搜了 
        for (int i=0;i<=3;i++)
        {//四个方向一个一个的去扫 
            node v;
            v.x=u.x+fx[i][0];
            v.y=u.y+fx[i][1];
            v.f=i;
            if (u.f==-1||u.f==v.f) v.d=u.d; else v.d=u.d+1;
//v.f存的是这一步走的方向，如果上一步没走或者和这一步方向一样，那么拐弯次数不变 
            if (v.x<1||v.y<0||v.x>n||v.y>n) continue;//越界 
            if ((a[v.x][v.y]!=1&&v.d>d[v.x][v.y])||a[v.x][v.y]==0) continue;
            //如果扫过并且这次并不是更优，或者是x（走不了），就不搜了 
            a[v.x][v.y]=233;//标记 
            d[v.x][v.y]=v.d;//记录 
            if (v.x==tx&&v.y==ty)//到终点了，更新ans，不用入队 
            {
                ans=min(ans,v.d);
                continue;
            }
            q.push(v);
        }
    }
    if (ans!=23333333) printf("%d\n",ans); else//输出 
    printf("-1");
    return 0;
}

```

---

## 作者：白烛葵 (赞：37)

这题一看上去裸的宽搜

但这题因为要记录拐弯的次数，而不是最短路。。。

# 误区 路短不代表拐弯少

所以不能用常规宽搜QWQ~~太麻烦了，要回溯，多次搜，搜出所有路~~

这时我们需要对宽搜进行一下特殊的加强~~处理~~

让它只搜一次就出答案

我们可以利用

# 洪水填充~~机房某大佬取的名~~
的方法对一个点的4个方向进行搜索

这样就不用多次搜了

至于洪水填充是啥，我具体讲一下

这个方法是对宽搜进行优化，但某些情况反而会有有拖累

~~不过应该没人卡这种蒟蒻优化~~

实现这个方法，你只要在进行搜索跑点时在多加一个for循环

来模拟当前这条路能跑多远，向前延伸多远，像水一样向直线拓展

即让坐标点的变量乘上一个常数，让该点4条直线上延展

下面上代码QWQ
```
#include<cstdio>
#include<iostream>
using namespace std;
struct pd{int x,y;}hrb[20050];//队列，存状态
int lxy[101][101],n,m,i,j,k,r=1,l,x,y,emm[101][101];
//lxy起bool的作用，emm记录拐弯次数
int xy[4]={1,-1,0,0},yx[4]={0,0,-1,1}；//坐标变量
char tu[101][101];//原图
int main()
{
    //freopen("ddos.in","r",stdin);
    //freopen("ddos.out","w",stdout);
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    for(k=1;k<=n;k++)
    {
        cin>>tu[i][k];
        if(tu[i][k]=='A')hrb[l].x=i,hrb[l].y=k,lxy[i][k]=1;
        if(tu[i][k]=='B')x=i,y=k;
        if(tu[i][k]=='x')lxy[i][k]=1;
        //对图进行处理
    }
    while(l<r)//开搜
    {
        for(i=0;i<4;i++)//枚举坐标变量，进行4方移动
        for(k=1;;k++)//用于洪水填充的数组
        {
            int xx=hrb[l].x+k*xy[i],yy=hrb[l].y+k*yx[i];
            //枚举一个常数k，与坐标变量相乘
            if(lxy[xx][yy]==1)break;
            if(xx<=0||xx>n||yy<=0||yy>n)break;
            //碰边或走过了，停止填充
            lxy[xx][yy]=1;//打标记
            emm[xx][yy]=emm[hrb[l].x][hrb[l].y]+1;
            //停了，说明该转弯了，于是当前点的次数为原坐标的加1
            //该处不用取min，是因为洪水填充记得是拐弯次数，到目标点，拐弯次数自然是最少的
            hrb[r].x=xx;
            hrb[r].y=yy;
            r++;//进行队列
        }
        l++;
    }
    if(emm[x][y]!=0)
    printf("%d",emm[x][y]-1);//终点不为0，就说明到过这，输出答案减去1，因为开始方向不定QWQ~~理解一下~~
    else
    printf("-1");//说明到不了
    return 0;
}
```
搜索其实是优雅的暴力QWQ

面对不同题目，要用各种骚操作

比如，这题常规宽搜要搜几次才能出答案，试出所有路才能出答案

加了洪水填充，就只有一次，搜完，是不是很快，是不是很神奇

# 所以，这不点赞，关注，~~投食，素质三连~~，一波

---

## 作者：GNAQ (赞：36)

#目前最快的BFS算法


先来说一下思路吧，鄙人不才，表达能力有很大欠缺，如果理解有误，那完全是我的错。

这道题可以用一个特殊的BFS来求解。**每次把队首元素四个方向上的点扩展到队尾，用桶来记录转弯次数。**


##1.初始状态

A（起点）的转弯次数为-1。

##2.产生结点的规则

现在，起点位于队首。

从队首的点向四周逐“层”扩展，每一“层”扩展到的新点入队列，这些新点显然不需要转弯就可以达到（起点任意方向），所以他们的转弯次数记录为0 **（也就是起点+1，你的疑问马上就会得到解答）**

 ![](https://cdn.luogu.com.cn/upload/pic/5320.png) 

这就是产生新结点的策略。

##3.记录每个点的转弯次数

扩展到的新点的转弯次数=队首点的转弯次数+1。（由于BFS的特点，新点未被访问过才可以被加入队尾）

**下面是证明。**

如果扩展到的新点是不转90°（直走）就可以到的，那该点**一定**被扩展了队首点的点（队首点的父结点，不知道这么说对不对）访问过，此时该点不会被当作新点处理。同理，转弯180°的点也**一定**被扩展了队首点的点访问过。

所以，扩展到的新点**一定**是转弯90°（左或右）才能走到的。

此时，到新点的转弯次数=队首点的转弯次数+1。

证明完毕。


```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;

int n;//地图大小 
int timex[200][200]={0};//转弯次数记录 
int cachex,cachey,sx,sy,ex,ey;//起点，终点坐标和队首坐标缓存 
int wayx[4]={-1,0,1,0},wayy[4]={0,1,0,-1};//方向表 
queue<int>quex,quey;
char mapx[200][200]={0};//地图 
bool teller[4]={true};//扩展层数判断 

void showTimex()//输出到地图各点的转弯次数 
{
    cout<<endl<<"Showing Timex Mitrix"<<endl<<endl;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++) printf("%3d",timex[i][j]);
        printf("\n");
    }
    printf("\n");
    return;
}

int main()
{
    memset(timex,-1,sizeof(timex));
    scanf("%d",&n);
    getchar();//吸收回车 
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) 
    {
        cin>>mapx[i][j];
        if (mapx[i][j]=='A'){sx=i;sy=j;}//记录起点 
        if (mapx[i][j]=='B'){ex=i;ey=j;mapx[i][j]='.';}//记录终点并且让终点可以入队 
    }
    //cout<<sx<<" "<<sy<<" "<<ex<<" "<<ey<<" "<<endl; /*去掉注释可以看起点终点的位置*/ 
    quex.push(sx); quey.push(sy); 
    while (quex.size()>0)
    {
        memset(teller,true,sizeof(teller));//初始化 扩展层数判断变量 
        cachex=quex.front(); cachey=quey.front();//缓存存入 
        if (cachex==ex && cachey==ey)//如果到了终点，输出（这个题不存在起点=终点的情况，因为分别用AB表示 
        {
            cout<<timex[ex][ey]<<endl;
            return 0;
        }
        for (int j=0;j<=3;j++)//四个方向 
        {
            for (int i=1;i<=n;i++)/*开一层*/ if (teller[j]==true) /*如果该方向上 前面一层没遇到障碍*/ 
            {
                //cout<<"Direction= "<<j<<" Now Position At: "<<cachex+wayx[j]*i<<" "<<cachey+wayy[j]*i<<endl; /*去掉注释看方向、现在扩展到的位置坐标 */ 
                if (cachex+wayx[j]*i>=0 && cachex+wayx[j]*i<n && cachey+wayy[j]*i>=0 && cachey+wayy[j]*i<n)//越界判断 
                {
                    if (mapx[cachex+wayx[j]*i][cachey+wayy[j]*i]=='.' && timex[cachex+wayx[j]*i][cachey+wayy[j]*i]==-1) //未被访问且不是障碍 
                    {
                        timex[cachex+wayx[j]*i][cachey+wayy[j]*i]=timex[cachex][cachey]+1;//计算转弯次数 
                        quex.push(cachex+wayx[j]*i); quey.push(cachey+wayy[j]*i);//入队列 
                    }
                    else if (mapx[cachex+wayx[j]*i][cachey+wayy[j]*i]=='x') teller[j]=false;//此方向该层存在障碍，结束此方向的扩展 
                }
                else teller[j]=false;//越界，结束扩展 
            }
        }
        //showTimex(); /*去掉注释可以看每一次扩展完之后的转弯次数表*/ 
        quex.pop(); quey.pop();//队首元素出队 
    }
    cout<<-1<<endl;//搜完全图，没搜到 
    return 0;
}
```
##请不要抄袭代码


---

## 作者：yjxyjx (赞：19)

今天有人来给我们讲课。。（~~透露一点：WC银牌…不能被看到。。23333（逃~~


好了不扯了。。


------------（low到不行的分割线。。）


这题是今天讲课的例题。。一开始用深搜做。。但只有30分，代码如下：



```cpp




#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::string;

const int MAXN = 100 + 10;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

string s[MAXN];
int N, matrix[MAXN][MAXN] = {0}, ans = -1, endX, endY, startX, startY;


/*startX， startY：起始点的坐标；endX, endY：同start；matrix：转换成数字后的矩阵（这样处理方便些。~~（不过也没方便多少。。~~*/

bool check(int x, int y) {
    if ((x < 0) || (x >= N) || (y < 0) || (y >= N)) {
        return false;
    }
    if (matrix[x][y] < 0) {
        return false;
    }
    return true;
}

void dfs(int x, int y, int now, int lastWay) {
/*
(x,y)是当前的点的坐标；now是到达当前点的转弯次数；lastWay是走到这个点时的方向。。
*/

    if ((x == endX) && (y == endY)) {
    
    
/*
这里不能用matrix[x][y] == 2（虽然一开始转换数组时把终点标为了2），因为后面继续搜索时，有一句"matrix[tmpx][tmpy] = -1"，这句会使得你走到终点再判断时，终点却被标记为了-1。*/
        (ans == -1) ? ans = now : ans = std::min(now,ans);
    } else {
        
        for (int i = 0; i < 4; ++i) {
        
        //四个方向进行扩展。。
            int tmpx = x + dx[i], tmpy = y + dy[i];
            
            //扩展出的点的新坐标。。
            if (check(tmpx, tmpy) == true) {
            
            //没有越界且扩展的新点可以走。。
                if (lastWay != i) {//上一个方向和当前方向不相同
                    matrix[tmpx][tmpy] = -1;
                    dfs(tmpx, tmpy, now + 1, i);
                    //新坐标，转弯次数+1， 新方向。。
                    matrix[tmpx][tmpy] = 1;
                } else {
                    matrix[tmpx][tmpy] = -1;
                    dfs(tmpx, tmpy, now, i);
                    //方向和转弯次数都不变。
                    matrix[tmpx][tmpy] = 1;
                }
            }
        }
    }
}

string OutSpace(string s) {
    int len = s.size();
    string ans = "";
    for (int i = 0; i < len; ++i) {
        if (s[i] != ' ') {
            ans += s[i];
        }
    }
    return ans;
}

void Init() {
    cin >> N;
    getchar();
    
/*
这句是别人帮我debug时发现的。。在输入N之后，会有一个回车符。。导致下面读入时，先读入了回车符，而不是图。。
*/
//    N++;这两句没什么用。辛苦您俩了。。233333333
//    std::cerr << N;
    int x = 1, y = 1;
    for (int i = 0; i < N; i++) {
        getline(cin, s[i]);
        s[i] = OutSpace(s[i]);//去掉空格。。
    }
    
    for (int i = 0; i < N; ++i) {/*一开始想变为1——n范围的。。但是比较麻烦。。所以0——n-1.。*/
        for (int j = 0; j < s[i].size(); ++j) {
            
            switch (s[i][j]) {

                case '.': {//可以走的点，标记为1
                    matrix[i][j] = 1;
                    break;
                }
                case 'A': {
                    matrix[i][j] = 1;
                    startX = i; startY = j;/*主要是这里，要记住起点的坐标，下面dfs要用到。*/
                    break;
                }
                case 'B': {
                    matrix[i][j] = 2; 
                    endX = i; endY = j;
/*
既然不能用matrix[i][j] == 2 作为dfs终止条件了，所以要记住坐标。
*/                 
                    break;
                }
                case 'x': {
                    matrix[i][j] = -1;//不可扩展的点。
                    break;
                }
            }

        }
    }
}

void Work() {
    for (int i = 0; i < 4; ++i) {
        dfs(startX, startY, 0, i);//从起点出发，4个方向进行扩展。
    }
}

void Print() {
    cout << ans;
}

int main() {
    Init();
    Work();
    Print();
    return 0;
}



```

（这里吐槽一句：为什么vscode上的中文到这里就乱码了。。上面的注释是我重新打的。。


但是。。既然身为广搜讲课例题。。。那能用dfs就能A呢2333.。

好吧其实学长给出了这样一种数据：

（打空格太累不打了）

xx........……

xxA.......……

xxxxxx....

xxxxxx.xxx

B......xxx

在这种数据中，明显只用转2次弯（可以自己稍微手画一下）但dfs会全部遍历一遍，广搜则保证了每个点只会入队1次，时间复杂度为O（点的数量），

明显要好得多，所以，还不用广搜，更待何时？？？



先放出广搜大招：~~虽然基本上是抄的~~


```cpp






#include<bits/stdc++.h>

using namespace std;

const int INF = 2333333;//每天笑一笑，十年少23333333333
const int MAXN = 200 + 10;
const int maxWay = 4;//最大的方向个数。。直译一下就好。。
const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, -1, 1, 0};

struct Point {
    int x, y;
    int lastWay;
};

queue < Point > q;
Point start, end;//起点和终点
char maze[MAXN][MAXN];//maze：迷宫，
int N, step[MAXN][MAXN];

bool check(int x, int y) {
    if ((x < 0) || (x >= N) || (y < 0) || (y >= N) || (maze[x][y] == 'x')) {
        return false;
    }//越界||这个点不能走 return false；
    return true;
}

void Init() {
    cin >> N;
    getchar();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> maze[i][j];
            //cin自动忽略空的字符
            if (maze[i][j] == 'A') {
            //找到起点和终点
                start.x = i; start.y = j;
            }
            if (maze[i][j] == 'B') {
                end.x = i; end.y = j;
            }
            step[i][j] = INF;
    //从起点到点[i][j]的转弯次数设置为INF（无限大）
        }
    }
    step[start.x][start.y] = 0;//起点到起点转0次弯。
}

void Work() {
    q.push(start);
    while (!q.empty()) {
        Point u = q.front();
        q.pop();
        if ((u.x == end.x) && (u.y == end.y)) break;//如果坐标到了终点坐标，根据广搜“先到的必定最优”原则，可立即结束搜索。
        Point V;
        for (int i = 0; i < maxWay; ++i) {//四个方向
            V.x = u.x + dx[i]; V.y = u.y + dy[i];
            while (check(V.x, V.y) == true) {
            
            
/*
学长说，一般的广搜是逐渐扩散开来的，但是这样的话，队列里的顺序就没办法保证是由转弯次数少到转弯次数多的，所以用一个while，一次把所有能走的点全部扩展掉。
*/
            if (step[V.x][V.y]>step[u.x][u.y] + 1) {
                    step[V.x][V.y]=step[u.x][u.y] + 1;
                    //更新到达此点的转弯次数。。
                    q.push(V);
                }
                V.x += dx[i]; V.y += dy[i];//顺着此方向继续走，进行下一次加入队列。
            }
        }
    }
}

void Print() {
    (step[end.x][end.y] == INF) ? cout << -1 : cout << step[end.x][end.y] - 1;//学长说，在step数组里，就算是通过起点直接走过去的点，都被算成了“转1次弯”，因为在上面的广搜中，while循环把一种扩展点都扩展了，（可以打出来看一下），为了方便，直接-1；
}

void debug2()
{
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++)
            cout<<step[i][j]<<" ";
        cout<<endl;
    }
}

int main() {
    Init();
    Work();
    Print();
//    debug2();
    return 0;
}


```




说实话，这题真的有一些坑（~~所以我写了一天~~），但是，只要做出来了，我认为便值得。


~~颓啊~~


---

## 作者：ykuouzf (赞：10)

面对如潮的BFS写法，对深搜狂热的我还是决然用了DFS；

深搜里应放入四个变量，分别表示：

当前位置（两个变量）；当前转弯次数；当前方向；

裸上DFS当然不能，不然一个100×100蓝天白云就gg了；

所以必须还加入一点优化：

### 记忆化搜索是关键！

简单说就是用一个数组存下当前位置的最小步数，如果比当前步数小，那就用新的步数更新，如果已大于当前步数，那就直接退出搜索。

转换语句就是：
if(q[x][y]<=sum) return ;
q[x][y]=sum;

好了，这样代码就很好写了。简单码一下，80分

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l1,l2,s1,s2,q[101][101];
char a[1000][1000]; 
int ax[5]={0,-1,0,1,0},ay[5]={0,0,-1,0,1};
bool flag=1,vis[1000][1000]={0};
void dfs(int x,int y,int sum,int p)
{
    //cout<<x<<" "<<y<<" "<<sum<<" "<<p<<endl;
    if(q[x][y]<sum) return ;
    q[x][y]=sum;
    if(x==s1&&y==s2) return ;
    for(int i=1;i<=4;i++)
    {
        int ux=x+ax[i],uy=y+ay[i];
        if(ux<1||uy<1||ux>n||uy>n) continue;
        if(a[ux][uy]=='x') continue;
        if(!vis[ux][uy])
        {
            vis[ux][uy]=1;
            if(p==i%2||p==2) dfs(ux,uy,sum,i%2);
            else dfs(ux,uy,sum+1,i%2);
            vis[ux][uy]=0;
        }
    }
}
int main()
{
    memset(q,0x3f3f3f3f,sizeof(q));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j];
            if(a[i][j]=='A')
            {
                l1=i;
                l2=j;
            }
            if(a[i][j]=='B')
            {
                s1=i;
                s2=j;
            }
        }   
    vis[l1][l2]=1;
    dfs(l1,l2,0,2);
    if(q[s1][s2]==0x3f3f3f3f) cout<<-1;
    else cout<<q[s1][s2];
    return 0;
}
```
那么问题出在哪儿呢？

假设有一个5×5的表格：

|  |  |  |  |  |
| :----------: | :----------: | :----------: | :----------: | :----------: |
|  |  | 方向1 |  |  |
|  | 方向2 | 当前位置 | 方向4 |  |
|  |  | 方向3 |  |  |
|  |  |  |  |  |

我们观察可以发现方向1和方向3为同方向；方向2和方向4为同方向。而1和3都不能被2整除，2和4都能被2整除。那么我们就发现了一个新方法——

#### 通过判断是否能被2整除来判断方向

记忆化数组就可以改为q[3][x][y]:q[1][x][y]表示方向1和方向3；q[2][x][y]表示方向2和方向4。

那么时间可以少用一半喽！

AC代码献上：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l1,l2,s1,s2,q[3][101][101];
char a[1000][1000]; 
int ax[5]={0,-1,0,1,0},ay[5]={0,0,-1,0,1};
bool flag=1,vis[1000][1000]={0};
void dfs(int x,int y,int sum,int p)
{
    //cout<<x<<" "<<y<<" "<<sum<<" "<<p<<endl;
    if(q[p][x][y]<=sum) return ;
    q[p][x][y]=sum;
    if(x==s1&&y==s2) return ;
    for(int i=1;i<=4;i++)
    {
        int ux=x+ax[i],uy=y+ay[i];
        if(ux<1||uy<1||ux>n||uy>n) continue;
        if(a[ux][uy]=='x') continue;
        if(!vis[ux][uy])
        {
            vis[ux][uy]=1;
            if(p==i%2||p==2) dfs(ux,uy,sum,i%2);
            else dfs(ux,uy,sum+1,i%2);
            vis[ux][uy]=0;
        }
    }
}
int main()
{
    memset(q,0x3f3f3f3f,sizeof(q));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j];
            if(a[i][j]=='A')
            {
                l1=i;
                l2=j;
            }
            if(a[i][j]=='B')
            {
                s1=i;
                s2=j;
            }
        }   
    vis[l1][l2]=1;
    dfs(l1,l2,0,2);
    if(q[1][s1][s2]==0x3f3f3f3f&&q[0][s1][s2]==0x3f3f3f3f) cout<<-1;
    else cout<<min(q[1][s1][s2],q[0][s1][s2]);
    return 0;
}
```
祝大家早日AC！！

---

## 作者：s_ShotღMaki (赞：10)

看一眼觉得是一道bfs裸题，本来想秒掉来着

but

## 我肝了一晚上？？？

跟普通的bfs不太一样呢，需要全扩展掉，

不多说，看代码吧！

（正在改进码风）

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

inline int read ()
{
    int f = 1, x = 0;
	char ch;
    do {ch = getchar (); if (ch== '-') f = -1;} while (ch < '0' || ch > '9');
    do {x = x * 10 + ch - '0'; ch = getchar ();} while (ch >= '0' && ch <= '9');
    return f * x;
}

struct node
{
	int x, y;
} ;

queue <node> q;

int n;
int fx[4] = {1, -1, 0, 0};
int fy[4] = {0, 0, 1, -1};
bool map[101][101];
int s[101][101];
int qx, qy, zx, zy;

void GET_in ()
{   
    char pg;
	for (int i = 0; i < n; i ++)
	 for (int j = 0; j < n; j ++)
	 {
	 	cin >> pg;
	 	if (pg == 'x') map[i][j] = true;
	 	if (pg == 'A') qx = i, qy = j;
	 	if (pg == 'B') zx = i, zy = j;
	 }
}

bool check(int x, int y)
{
    if ((x >= 0) && (x < n) && (y >= 0) && (y < n) && (!map[x][y]))
    return true;
    return false;
}

void bfs ()
{
	memset (s, 0x3f, sizeof (s));
	s[qx][qy] = 0;
	node start;
	start.x = qx, start.y = qy;
	q.push (start);
	while (!q.empty ())
	{
		node now = q.front (); q.pop ();
		if ((now.x == zx) && (now.y == zy)) return ;
		node now2;
		for (int i = 0; i < 4; i ++)
		{
			now2.x = now.x + fx[i], now2.y = now.y + fy[i];
			while (check (now2.x, now2.y))
			{
				if (s[now2.x][now2.y] > s[now.x][now.y] + 1)
				{
					s[now2.x][now2.y] = s[now.x][now.y] + 1;
		            q.push (now2);
				}
				now2.x += fx[i], now2.y += fy[i];
			}
		}
	}
}

int main ()
{
	n = read ();
	GET_in ();
	bfs ();
	if (s[zx][zy] == 1061109567) printf ("-1"); //关于0x3f
	else printf ("%d", s[zx][zy] - 1);
	return 0;
}
```


---

## 作者：巨型方块 (赞：9)

这道题目没有那么难，没有那么烦；

其实就是一个裸的bfs；

然后比较的东西就是转弯的次数，这样大力bfs就没事了；

没什么可以讲的了，写spfa的真的没必要了；



```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const int N=1e2+5;
bool vi[N][N],g[N][N];
int xxx[4]={0,1,0,-1};
int yyy[4]={1,0,-1,0};
int X[N*N],Y[N*N],V[N*N],l,r;
int n,m,A[2],B[2];
char c;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            cin>>c;
            if(c=='x')g[i][j]=1;
            if(c=='A')A[0]=i,A[1]=j;
            if(c=='B')B[0]=i,B[1]=j;
        }
    for(int i=1;i<=n;i++)g[0][i]=g[n+1][i]=g[i][0]=g[i][n+1]=1;
    X[1]=A[0];Y[1]=A[1];V[1]=-1;
    l=0;r=1;
    while(r>l){
        int xx=X[++l],yy=Y[l],v=V[l];
        if(xx==B[0]&&yy==B[1]){printf("%d",max(0,v));return 0;}
        for(int i=0;i<4;i++){
            int x=xx+xxx[i];
            int y=yy+yyy[i];
            while(!g[x][y]){
                if(!vi[x][y]){
                    vi[x][y]=1;
                    X[++r]=x;
                    Y[r]=y;
                    V[r]=v+1;
                }
                x+=xxx[i];
                y+=yyy[i];
            }
        }
    }printf("-1");
}

```

---

## 作者：杨先达 (赞：6)

# **拆点+最短路**
一看题目就想到分层图啥的，于是乎就愉快地拆点跑Dijkstra过了...

然后打开题解看一眼，竟然莫得这样写的，那就贡献出洛谷第一篇处女题解吧（~~轻喷，轻hack~~）

跟一般的最短路不一样，题目要求的是90转弯次数最少的，不是路径最短的

如下图中显然最短路是往上走的那条，但是转弯的次数比往右边走来得多。

![图例1](https://cdn.luogu.com.cn/upload/image_hosting/0vrzkt8j.png)

所以我们需要重新构图，将一个点拆成四个点，分别表示到达这个位置的时候上、下、左、右四种状态。

在建边的时候，对于两个相邻的点，其中同方向的点（转弯角度为0°/180°）连一条权值为0的边，而垂直方向的点（转弯角度为90°）连一条权值为1的边。

最后建立超级源点连接S的四个状态点，T的四个状态点连接到超级汇点，跑最短路即可。

##  _**Code**_ 
```cpp
#include<iostream>
#include<algorithm>
#include<set>
#include<queue>
#include<deque>
#include<vector>
#include<map>
#include<stack>
#include<cstdio>
#include<cstring>
#include<climits>
#include<cmath>
#include<iomanip>
#define int long long
#define double long double
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 400+10;  // 因为要拆成四个点，所以四倍

struct qNode {
	int v;
	int c;
	qNode(int _v = 0, int _c = 0) : v(_v), c(_c) {}
	bool operator < (const qNode &r)const {
		return c > r.c;
	}
};

struct Edge {
	int v;
	int cost;
	Edge(int _v = 0, int _cost = 0) : v(_v), cost(_cost) {}
};

int n;
char g[MAXN][MAXN];  // 注意是MAXN*MAXN
vector<Edge>E[MAXN*MAXN];
bool vis[MAXN*MAXN];
int dist[MAXN*MAXN];

inline int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}

void Dijkstra(int n, int start) { //点的编号从1开始
	memset(vis, false, sizeof(vis));
	memset(dist, 0x3f, sizeof(dist));
	priority_queue<qNode>que;

	while (!que.empty()) {
		que.pop();
	}
	dist[start] = 0;
	que.push(qNode(start, 0));
	qNode tmp;

	while (!que.empty()) {
		tmp = que.top();
		que.pop();
		int u = tmp.v;
		if (vis[u]) {
			continue;
		}
		vis[u] = true;
		for (int i = 0; i < E[u].size(); i++) {
			int v = E[tmp.v][i].v;
			int cost = E[u][i].cost;
			if (!vis[v] && dist[v] > dist[u] + cost) {
				dist[v] = dist[u] +cost;
				que.push(qNode(v, dist[v]));
			}
		}
	}
}

void addEdge(int u, int v, int w) {
	E[u].push_back(Edge(v, w));
}

signed main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> g[i][j];
		}
	}
	int st, ed;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(g[i][j] == '.' || g[i][j] == 'A' || g[i][j] == 'B') {
				int now = (i-1)*n+j;
				// 1~n*n 上 n*n+1~2*n*n 下 2*n*n+1~3*n*n 左 3*n*n+1~4*n*n 右
				if(i-1 >= 1 && (g[i-1][j] == '.' || g[i-1][j] == 'A' || g[i-1][j] == 'B')) {
					addEdge(now+n*n, n*n+(i-2)*n+j, 0);
					addEdge(now, n*n+(i-2)*n+j, 0);
					addEdge(now+2*n*n, n*n+(i-2)*n+j, 1);
					addEdge(now+3*n*n, n*n+(i-2)*n+j, 1);
				}
				if(i+1 <= n && (g[i+1][j] == '.' || g[i+1][j] == 'A' || g[i+1][j] == 'B')) {
					addEdge(now, i*n+j, 0);
					addEdge(now+n*n, i*n+j, 0);
					addEdge(now+2*n*n, i*n+j, 1);
					addEdge(now+3*n*n, i*n+j, 1);
				}
				if(j-1 >= 1 && (g[i][j-1] == '.' || g[i][j-1] == 'A' || g[i][j-1] == 'B')){
					addEdge(now+3*n*n, 3*n*n+(i-1)*n+j-1, 0);
					addEdge(now+2*n*n, 3*n*n+(i-1)*n+j-1, 0);
					addEdge(now+n*n, 3*n*n+(i-1)*n+j-1, 1);
					addEdge(now, 3*n*n+(i-1)*n+j-1, 1);
				}
				if(j+1 <= n && (g[i][j+1] == '.' || g[i][j+1] == 'A' || g[i][j+1] == 'B')){
					addEdge(now+2*n*n, 2*n*n+(i-1)*n+j+1, 0);
					addEdge(now+3*n*n, 2*n*n+(i-1)*n+j+1, 0);
					addEdge(now+n*n, 2*n*n+(i-1)*n+j+1, 1);
					addEdge(now, 2*n*n+(i-1)*n+j+1, 1);
				}
				if(g[i][j] == 'A') st = (i-1)*n+j;
				else if(g[i][j] == 'B') ed = (i-1)*n+j;
			}
		}
	}
	for(int i = 0; i < 4; i++) addEdge(0, st+i*n*n, 0);
	for(int i = 0; i < 4; i++) addEdge(ed+i*n*n, 4*n*n+1, 0);
	Dijkstra(4*n*n+1, 0);
	cout << (dist[4*n*n+1]>=INF?-1:dist[4*n*n+1]) << endl;
	return 0;
}

```

【感谢观看】

---

## 作者：さょなち (赞：6)

**spfa**
~~这道题标签是spfa，那就用spfa做吧~~
这道题很明显是一个最短路的思想，但问题是怎么spfa。
首先，这道题很明显不能用一般的bfs，因为求的不是最少步数而是最少转弯次数，每个点的值都不同，且无法确定，那只能用spfa。
spfa的时候还要考察方向，因为每个方向来的转弯次数有可能不同。
所以数组要加多一维来记录方向。
~~好了，不说废话了，上代码~~
```
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;

const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
const int INF=99999999;

int n,head,tail,sx,sy,ex,ey,c,ans=INF;

struct point{
    int x,y,dt;
}a;

int dis[105][105][5],vis[105][105][5];//加一维记录方向
int map[105][105];
queue<point>que;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++){
      	char ch;
      	cin>>ch;
        if(ch=='A') sx=i,sy=j;
        if(ch=='B') ex=i,ey=j;
        if(ch=='x') map[i][j]=1;
       }
    }//这道题有坑，读入的时候是有空格的。。。
    
    
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        for(int k=0;k<4;k++)
          dis[i][j][k]=INF;
    
    
    for(int i=0;i<4;i++){
        int xx=sx+dx[i],yy=sy+dy[i];
        if(xx<=0||yy<=0||xx>n||yy>n||map[xx][yy])continue;
        vis[xx][yy][i]=1;
        a.x=xx,a.y=yy,a.dt=i;
        que.push(a);
        dis[xx][yy][i]=0;
    }//从起点向四个方向拓展
    
    
    while(!que.empty()){//spfa
        point t=que.front();que.pop();
        int tx=t.x,ty=t.y;
        for(int i=0;i<4;i++){
            int xx=tx+dx[i],yy=ty+dy[i];
            
            if(xx<=0||yy<=0||xx>n||yy>n||map[xx][yy])continue;//越界
            
            if(t.dt==i) c=0;else c=1;//同方向转弯次数就为0，反之为1
            if(dis[xx][yy][i]>dis[tx][ty][t.dt]+c){
                dis[xx][yy][i]=dis[tx][ty][t.dt]+c;
                if(!vis[xx][yy][i]){
                    a.x=xx,a.y=yy,a.dt=i;
                    que.push(a);
                    vis[xx][yy][i]=1;
                }
            }
        }
        vis[tx][ty][t.dt]=0;
    }
    
    for(int i=0;i<4;i++)
      ans=min(ans,dis[ex][ey][i]);//看看四个方向的答案
    
    if(ans==INF)cout<<"-1\n";//到不了就-1
    else cout<<ans<<endl;
    
    return 0;
}
```
~~~~ 

---

## 作者：夏色祭 (赞：3)

**来一发P党的题解，造福P党的朋友们**

本题的思路是BFS。 （不知道为什么标签会是dp）

先用ff[i,j]记录从A点出发最少转弯次数（一开始赋初值为maxlongint，因为是求最少）

然后去BFS，起点为A的坐标，每次向四个方向拓展，入队的条件是到当前点的次数比ff数组里当前记录的最优解还要更优

不多bb上代码：

```cpp
const
  x:array[1..4]of longint=(1,0,0,-1);
  y:array[1..4]of longint=(0,1,-1,0);//四个方向
var
  ff:array[0..101,0..101]of longint;
  f,f1,f2,f3:array[0..100000]of longint;
  a:array[0..101,0..101]of char;
  n,i,j,k,a1,a2,b1,b2,h,t,l,r:longint;
  c:char;
begin
  readln(n);
  for i:=1 to n do 
    begin
      for j:=1 to n do  
        begin
          read(a[i,j],c);//用c把多余空格读掉
          if a[i,j]='A' then begin a1:=i;a2:=j; end;
          if a[i,j]='B' then begin b1:=i;b2:=j; end;//记录A和B的坐标
        end;
      readln;
    end;
  for i:=1 to n do 
    for j:=1 to n do 
      ff[i,j]:=maxlongint;//赋初值
  h:=0;
  t:=1; 
  f[1]:=0;
  f1[1]:=a1;
  f2[1]:=a2;
  f3[1]:=0;//f数组记录方向,f1和f2数组记录坐标
  while h<=t do 
    begin
      inc(h);
      for i:=1 to 4 do 
        begin
          l:=f1[h]+x[i];
          r:=f2[h]+y[i];
          if (l<1)or(r<1)or(l>n)or(r>n)or(a[l,r]='x') then continue;//所要去的点不能越界
          if (h=1)or(f[h]=i) then k:=f3[h] else k:=f3[h]+1;//判断从(f1[h],f2[h])到当前点要不要转弯，并把转弯数记录下来
          if ff[l,r]>k then //到当前点的次数比ff数组里当前记录的最优解还要更优
            begin
              inc(t);
              f[t]:=i;
              f1[t]:=l;
              f2[t]:=r;
              f3[t]:=k;
              ff[l,r]:=k; 
            end;//入队
        end;
    end;//BFS
  if ff[b1,b2]=maxlongint then write(-1) else write(ff[b1,b2]);//如果到不了则输出-1（题目里没说）
end.
```

---

## 作者：Apro1066 (赞：2)

这题，其实和**P2937**还是很像的，基本是一模一样的代码。

和P2937一样，也是典型的01最短路问题，比较好的方法是用bfs。我看题解里没多少用dfs的，这里用的dfs求，主要也是想练习爆搜（雾）。

首先考虑dfs，如果要换方向就把答案$+1$，反正只要换方向了肯定需要一个+1。到达B的时候更新答案，取最小值即可。

每次搜的时候按照之前的方向搜，然后再尝试其他方向搜。这样能尽快找到最优解。

但是仍然会TLE。考虑使用记忆化搜索。令$dp[x][y][direct]$为表示到点$(x,y)$并且前一次转弯位$direct$时最小转弯次数。

```cpp
#include <stdio.h>
#include <iostream>
#include <memory.h>
using namespace std;
int tox[5]={0,1,0,-1,0},toy[5]={0,0,1,0,-1};
int n,m,s(9999999),cnt,dp[501][501][5];
char a[501][501];
bool vis[501][501];
void dfs(int x,int y,int direct,int times)//x,y坐标，direct方向，times转弯次数 
{
	if(direct!=-1 && dp[x][y][direct]<=times) return;
	if(direct!=-1) dp[x][y][direct]=times;//记录最优解 
	if(a[x][y]=='B')//到达终点 
	{
		s=min(s,times);
		return;
	}
	register int i,j,x1,y1;
	if(direct!=-1)//先同方向搜索 
	{
		x1=x+tox[direct];
		y1=y+toy[direct];
		if(x1>=1 && x1<=n && y1>=1 && y1<=n && vis[x1][y1]==0 && a[x1][y1]!='x')
		{
			vis[x1][y1]=1;
			dfs(x1,y1,direct,times);//肯定方向相同，不用拐弯 
			vis[x1][y1]=0;
		}
	}
	for(i=1;i<=4;i++)//枚举方向 
	{
		if(i!=direct)
		{
			x1=x+tox[i];
			y1=y+toy[i];
			if(x1>=1 && x1<=n && y1>=1 && y1<=n && vis[x1][y1]==0 && a[x1][y1]!='x')
			{
				vis[x1][y1]=1;
				if(direct!=-1)//换一个方向就要加转个弯 
					dfs(x1,y1,i,times+1);
				else//如果等于-1的话，还是意味着同方向。这个特判主要针对于一开始怎么走 
					dfs(x1,y1,i,times);
				vis[x1][y1]=0;
			}
		}
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(a[i][j]=='A')//起点 
			{
				memset(dp,999999,sizeof(dp));
				vis[i][j]=1;
				dfs(i,j,-1,0);//由于一开始不好确定方向所以direct先为-1 
				if(s==9999999)
					cout<<-1<<endl;
				else
					cout<<s<<endl;
				return 0; 
			}
		}
	}
	return 0;
}
```


---

## 作者：Janet_One (赞：2)

## 这题是BFS~~吧~~

这题主要是要记录移动方向的变化，从而得出转弯的次数。很显然，如果某一次扩展的方向与这次扩展之前的扩展方向不一致的话，转向次数就是上一节点的转弯次数+1了。

但是，如何判断是否一致呢？我们可以很容易的想到，在扩展的节点中新增一个状态$f$表示方向,每次比较这个方向就行了。不过如果用一个数字来表示方向会有点麻烦，因为一般节点扩展时我们是用$dx[]$和$dy[]$两个方向数组来控制移动的，若要把$dx[]$和$dy[]$转换成$1、2、3、4$的这类数字的话着实~~不优雅~~麻烦,于是我们可以把方向表示成和$dx[]$和$dy[]$一样的形式(也就是{-1,0},{1,0},{0,-1},{0,1})，这样就可以快速判断了

还有，这样做会使某个点多次被访问到（最多4次，分别为这个点的上，下，左，右的相邻点访问而来），所以在更新这个点之前要判断当前是否比此次更新要好

code:
```cpp
#include<iostream>
#include<queue>
#include<cstring>
#define debug for(int i(1);i<=n;++i){for(int j(1);j<=n;++j){cout<<vis[i][j]<<" ";}cout<<endl;}
using namespace std;
const int N(110);
struct node
{
    int x,y,turn,fx,fy;
};
int n,sx,sy,ex,ey,vis[N][N],ans(1<<30);
char a[N][N],dx[]={-1,1,0,0},dy[]={0,0,-1,1};
void bfs(int wayx,int wayy)
{
    queue<node>que;
    que.push((node){sx,sy,0,wayx,wayy});
    vis[sx][sy]=0;//初始化
    while(que.size())
    {
        node now(que.front());
        que.pop();
        if(now.turn>=ans)
            continue;//如果当前的次数都已经大于等于已知答案了，那么也就没有必要再搜索下去了
        for(int i(0);i<4;++i)
        {
            int fx(now.x+dx[i]),fy(now.y+dy[i]);
            if(fx<1 || fx>n || fy<1 || fy>n || a[fx][fy]=='x')
                continue;
            if(vis[fx][fy])//如果这个点已经被访问过了，就比较这次访问和之前那一次访问谁的转弯次数更少
            {
                int pd(now.turn);
                if(dx[i]!=now.fx || dy[i]!=now.fy)//不是同个方向次数就要+1
                    ++pd;
                if(pd<vis[fx][fy])//选择更好的解
                    vis[fx][fy]=pd,
                    que.push((node){fx,fy,pd,dx[i],dy[i]});
            }
            else//如果没有访问过这个点就直接更新它
            {
                int pd(now.turn);
                if(dx[i]!=now.fx || dy[i]!=now.fy)
                    ++pd;
                vis[fx][fy]=pd;
                que.push((node){fx,fy,pd,dx[i],dy[i]});
            }
        }
    }
    if(vis[ex][ey])//当终点被到达过时才来更新ans
        ans=ans<vis[ex][ey]?ans:vis[ex][ey];
    return ;
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;
    for(register int i(1);i<=n;++i)
    {
        for(register int j(1);j<=n;++j)
        {
            cin>>a[i][j];
            if(a[i][j]=='A')//记录开始点
                sx=i,sy=j;
            else if(a[i][j]=='B')//记录结束点
                ex=i,ey=j;
        }
    }
    for(int i(0);i<4;++i)
        memset(vis,0,sizeof(vis)),
        bfs(dx[i],dy[i]);//由于开始时的方向是任意的，所以需要四个方向都试一遍
    if(ans==1<<30)
        cout<<-1<<endl;
    else
        cout<<ans<<endl;//最终的答案
    return 0;
}

```

---

## 作者：hht2005 (赞：2)

### 发一个不一样的题解
#### 算法:
标签是spfa或DP，有的人用spfa，有的人用bfs，有的人用dfs，可我用的居然是用双端队列优化的Dijkstra。

#### 思路：
这一题可以看成一个最短路。对于某个点，它有四种状态，面对前、后、左、右，所以我们可以把一个点分成四个点。

由于我们要求的不是最要需要多少步，而是最要需要拐多少弯，所以边权有两种，0(不拐弯)和1(拐弯)。此时，用普通的bfs就不行了，可以改成spfa。(平均时间复杂度：k·n^2,k为小常数，最坏可达n^2)。

用spfa算法会使一个点被扩张多次，使效率降低。但最短路还有另一个更高效的Dijkstra算法。朴素的Dijkstra算法是点数的平方，一般可以加堆优化。但堆优化会增加一个log，在这一题会得不偿失(平均时间复杂度：n^2·logn^2，logn^2为堆的时间)。

不过，这一题的边权不是为零就是一，并不要用堆，用双端队列就行。在普通bfs队列里，按层扩张，层数只有两层，正在扩张层和扩张层的下一层，而且正在扩张层在队列中全部在下一层的前面。如果改成双端队列，边权为零说明新扩张的结点和扩张它的结点在同一层，从队头入队；否则，从队尾入队。这样，当一个点第一次被取出时，它离起点的距离就它离起点的最短路(平均时间复杂度：n^2)。

### code:
双端队列Dijkstra:
```cpp
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
const int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};//四个方向
char a[110][110];//原地图
int v[110][110][4];//拆点后的单源最短路
bool b[110][110][4];//记录是否被取出
struct node{
	int x,y,f;
};
deque<node>q;//STL中的双端队列
int main()
{
	memset(v,0x3f,sizeof(v));//最短路初值为inf
	int n,sx,sy,tx,ty;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='A')//起点
			{
				sx=i;
				sy=j;
			}
			else if(a[i][j]=='B')//终点
			{
				a[i][j]='.';
				tx=i;
				ty=j;
			}
		}
	for(int k=0;k<4;k++)//将起点入队
		q.push_back((node){sx,sy,k}),v[sx][sy][k]=0;
	while(!q.empty())\\dijkstra
	{
		node x=q.front();
		q.pop_front();
		if(x.x==tx&&x.y==ty)//终点被取出，得到答案
		{
			printf("%d\n",v[x.x][x.y][x.f]);
			return 0;
		}
		if(b[x.x][x.y][x.f])continue;//被取出过，continue
		b[x.x][x.y][x.f]=1;
		for(int i=0;i<4;i++)//枚举四个方向
		{
			int x1=x.x+dx[i],y1=x.y+dy[i];
			if(a[x1][y1]=='.'/*越界即为空字符*/&&v[x.x][x.y][x.f]+(x.f!=i)<v[x1][y1][i])
			{
				v[x1][y1][i]=v[x.x][x.y][x.f]+(i!=x.f);
				if(i==x.f)q.push_front((node){x1,y1,i});//边权为零,从队头入队。
				else q.push_back((node){x1,y1,i});//否则，从队尾入队
			}
		}
	}
	puts("-1");//终点从未被取出，判断无解
}
```

---

## 作者：Von_Blücher (赞：2)

看到楼上题解代码较为复杂，没有给出分析很透彻的思路，于是想了很久，得到一个时间复杂度较高但是简单一些的代码。

首先BFS的性质——最短。此题不能用一般BFS的原因在于，离A点路径最短的点并非拐弯最少的点。由此想到，可以以转弯次数作为推广搜索下一层的条件。而我们能够根据BFS性质得知，若某个点转弯次数为i，则它一定能够通过某个转弯次数为i-1的点扩展而来。

所以，我们只需要以A点为根，先扩展出所有到A点转弯仅为1的点，将它们放入队列。再从这些转弯次数为1的结点出发，再次扩展，得到次数为2的结点，以此类推，直到寻找到B点。

实现过程中，我没有用两个队列，这样会遇到一个问题：可能由于扩展顺序先后的不同，某些结点无法被及时扩展。为了解决这个问题，只好在取出每个扩展结点时，向这个结点上、下、左、右四个方向找，若扩展的结点已访问则跳过继续，直到搜索到第一个禁位为止。于是这使得每个结点扩展时需要花费近似O(N)的时间（PS：尽管可能远小于它）（PS 2：其实楼上的那个找法也是要花时间的，只不过少一点罢了233）（PS 3：我不用记录方向，且只用一个队列，等于时间换空间+代码复杂度），所以时间复杂度约为O(N^3)（PS：不过除非极端数据否则根本到不了N^3）

贴代码……很丑陋还请包涵

、、、



    
        

  
  
    
      
        
        
        
  


    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAX=105,INF=1<<29,dx[]={-1,1,0,0},dy[]={0,0,-1,1}; 
int N,Bx,By,Ex,Ey;
bool F[MAX][MAX],Vis[MAX][MAX];
struct Node
{
  int x,y,turn;
}Q[MAX*MAX*MAX];
void Input()
{
    char c;
    scanf("%d\n",&N);
    for(int i=1;i<=N;i++){
      for(int j=1;j<=N;j++){
        cin>>c;
        if(c=='A'){
          Bx=i;
          By=j;
      }
      if(c=='B'){
        Ex=i;
        Ey=j;
      }
      if(c!='x')F[i][j]=true;
    }
  }
}
bool BFS()
{
  int Head=0,Tail=1;
  Node top;
  Q[1].x=Bx;
  Q[1].y=By;
  Q[1].turn=-1;
  Vis[Bx][By]=true;
  do{
    Head++;
    top=Q[Head];
    Vis[top.x][top.y]=true;
    for(int i=0;i<4;i++){
      int tx=top.x+dx[i],ty=top.y+dy[i];
      while(tx>=1&&tx<=N&&ty>=1&&ty<=N&&F[tx][ty]){
        if(Vis[tx][ty]){
          tx+=dx[i];
          ty+=dy[i];
          continue;
        }
        if(tx==Ex&&ty==Ey){
          printf("%d\n",top.turn+1);
          return true;
        }
        Vis[tx][ty]=true;
        Tail++;
        Q[Tail].x=tx;
        Q[Tail].y=ty;
        Q[Tail].turn=top.turn+1;
        tx+=dx[i];
        ty+=dy[i];
      }
    }
  }while(Head<Tail);
  return false;
}
int main()
{
    Input();
    if(!BFS())printf("-1\n");
    return 0;
}
、、、
```

---

## 作者：浮尘ii (赞：2)

①BFS
利用两个队列。Q1记录只转弯可到的点，Q2记录Q1转弯后再在方向上扩展所有可到的点。如果Q1里的点无法扩展了，就说明无法到达了。

（注意输入格式里面 **每个字符后有一个空格**，被坑了很多次）

关键代码：

```cpp
const int        Dx[] = {1, 0, -1, 0}, Dy[] = {0, 1, 0, -1};
struct NodeTp {
    int    cx, cy, cd, cstep;
} ;
struct QueueTp {
    NodeTp    Q[MaxN * MaxN << 2];
    int        Head, Tail;

    inline bool notempty()
     { return Head != Tail; }
    inline void clear()
     { Head = Tail = 0; }
    inline void push(const NodeTp& arg)
     { Q[Tail++] = arg; }
    inline NodeTp& pop()
     { return Q[Head++]; }
} Q1, Q2;
```

```cpp
    for(int i = 0; i < 4; i++)
        Vis[Ax][Ay][i] = true, Q1.push((NodeTp) {Ax, Ay, i, 0});
    while(flag) {
        flag = false;
        Q2.clear();
            while(i > 0 && j > 0 && i <= N && j <= N && Map[i][j] != 'x' && !Vis[i][j][now.cd]) {
                if(Map[i][j] == 'B') {
                    cout << now.cstep << endl;
                    return 0;
                }
                Vis[i][j][now.cd] = true, flag = true;
                Q2.push((NodeTp) {i, j, now.cd, now.cstep});
                i += Dx[now.cd], j += Dy[now.cd];
            }
        }
        Q1.clear();
        while(Q2.notempty()) {
            NodeTp    &now = Q2.pop();
            if(!Vis[now.cx][now.cy][(now.cd + 1) % 4])
                Vis[now.cx][now.cy][(now.cd + 1) % 4] = true, Q1.push((NodeTp) {now.cx, now.cy, (now.cd + 1) % 4, now.cstep + 1});
            if(!Vis[now.cx][now.cy][(now.cd + 3) % 4])
                Vis[now.cx][now.cy][(now.cd + 3) % 4] = true, Q1.push((NodeTp) {now.cx, now.cy, (now.cd + 3) % 4, now.cstep + 1});
        }
    }
```
②最短路

把一个点扩成4个点，表示一个点的4个不同方向。加边：同一个点不同方向间边权为1(90度)，一个点一个方向可达的点（邻接点即可）间边权为0。

然后可以使用最短路算法求得答案。

（思路来源于其他人，我还没写，就不贴代码了）


---

## 作者：Remarkableboy (赞：1)

# 蒟蒻的Dijkstra
刚刚看了dalao们的洪水填充，蒟蒻的我瑟瑟发抖(tql+orz).....普通bfs在跑图时搜点记录的是最短路径（扩展层数），本题要求输出最小转弯次数，我们可以模仿dijkstra+堆优化将转弯数保存在小根堆中然后跑dijkstra，
由于堆顶始终最小，所以在bfs跑到时就能得出我们的答案
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[109][109];
int book[109][109];
int flag=99999;
int nx[4]= {1,0,-1,0};
int ny[4]= {0,-1,0,1};
int s1,s2;
int e1,e2;
struct node
{
    int px=0;
    int py=0;
    int x=0;
    int y=0;
    int w=0;
    friend bool operator < (node a,node b)//小根堆
    {
        return a.w>b.w;
    }
};
int w;
priority_queue<node> q;
int m,n;
void bfs()//dijkstra
{
    node fir;
    fir.x=s1;
    fir.y=s2;
    q.push(fir);
    book[s1][s2]=1;
    while(!q.empty())
    {
        node now=q.top();
        q.pop();
        book[now.x][now.y]=1;
        if(now.x==e1&&now.y==e2)
        {
            //if(now.w<=flag)
            {
            flag=now.w;
            break;
            //return;
            }
        }
        for(int i=0; i<4; i++)
        {
            int tx=now.x+nx[i];
            int ty=now.y+ny[i];
            if(tx<1||tx>m||ty<1||ty>m)
                continue;
            if(a[tx][ty]=='x')
                continue;
            if(book[tx][ty]==1)
                continue;
            if((tx-now.x)*(now.x-now.px)+(ty-now.y)*(now.y-now.py)==0)
            {
                node next;
                next.x=tx;
                next.y=ty;
                next.px=now.x;
                next.py=now.y;
                next.w=now.w+1;
                q.push(next);
          
            }
            else
            {
                node next;
                next.x=tx;
                next.y=ty;
                next.px=now.x;
                next.py=now.y;
                next.w=now.w;
                q.push(next);
                
            }
        }
    }
}
int main()
{
    cin>>m;
    memset(a,-1,sizeof(a));
    int x,y;
    int z;
    for(int i=1; i<=m; i++)
        for(int j=1; j<=m; j++)
        {
            char c;
            cin>>c;
            if(c=='A')
            {
                s1=i;
                s2=j;
            }
            if(c=='B')
            {
                e1=i;
                e2=j;
            }
            a[i][j]=c;
        }
    bfs();
    if(flag==99999)
        cout<<-1;
    else
        cout<<flag;
    return 0;
}
```


---

## 作者：qr的小迷妹 (赞：1)

### 最少
确认过眼神，就是宽搜啦。
宽搜需要存队列，然而这么~~懒~~的我。。看到了
#### “N (1 <= N <= 100)”
那么，可以不存队列，直接搜（咳，这是一篇偷懒的题解）
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[101][101];
int xxx,yyy,ii,k,xx,yy,i,x,y,j,n,a[101][101];
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int main()
{
    cin>>n;
    for (i=1;i<=n;i++)
     for (j=1;j<=n;j++)
     {
      cin>>s[i][j];
      if (s[i][j]=='A')a[i][j]=0,x=i,y=j;else a[i][j]=10001;
      if (s[i][j]=='B')xx=i,yy=j;
     }
    for (i=1;i<=4;i++)
    {
        xxx=x;yyy=y;
        while ((s[x+dx[i]][y+dy[i]]=='.'||s[x+dx[i]][y+dy[i]]=='B')&&a[x+dx[i]][y+dy[i]]==10001)
          x+=dx[i],y+=dy[i],a[x][y]=0;
        x=xxx;y=yyy;
    }
    if (a[xx][yy]!=10001)
    {
        cout<<a[xx][yy];
        return 0;
    }
    for (k=0;k<=10000;k++)
    for (i=1;i<=n;i++)
     for (j=1;j<=n;j++)
     {
     	if (a[i][j]==k)
     	{
     		x=i;y=j;
     		for (ii=1;ii<=4;ii++)
     		{
     			xxx=x;yyy=y;
     		while ((s[x+dx[ii]][y+dy[ii]]=='.'||s[x+dx[ii]][y+dy[ii]]=='B')
             &&a[x+dx[ii]][y+dy[ii]]>=k+1)
            x+=dx[ii],y+=dy[ii],a[x][y]=k+1;
            x=xxx;y=yyy;
            }
            if (a[xx][yy]!=10001)
            {
               cout<<a[xx][yy];return 0;
            }  
        }
     }
    cout<<-1;
}
```


---

