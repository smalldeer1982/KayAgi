# 小A和uim之大逃离 II

## 题目背景

话说上回……还是参见 <https://www.luogu.com.cn/problem/P1373> 吧

小 a 和 uim 再次来到雨林中探险。突然一阵南风吹来，一片乌云从南部天边急涌过来，还伴着一道道闪电，一阵阵雷声。刹那间，狂风大作，乌云布满了天空，紧接着豆大的雨点从天空中打落下来，只见前方出现了一个牛头马面的怪物，低沉着声音说：“呵呵，既然你们来到这，两个都别活了！”。小 a 和他的小伙伴再次惊呆了！


## 题目描述

瞬间，地面上出现了一个 $H$ 行 $W$ 列的巨幅矩阵，矩阵的每个格子上要么是空地 `.` 或者障碍 `#`。

他们起点在 $(1,1)$，要逃往 $(H,W)$ 的出口。他们可以一次向上下左右移动一格，这个算一步操作。不过他们还保留着上次冒险时收集的魔液，一口气喝掉后可以瞬移到相对自己位置的 $(D,R)$ 向量；也就是说，原来的位置是 $(x,y)$，然后新的位置是 $(x+D,y+R)$，这个也算一步操作，不过他们仅能至多进行一次这种操作（当然可以不喝魔液）。

这个地方是个是非之地。所以他们希望知道最小能有几步操作可以离开这个鬼地方。不过他们可能逃不出这个鬼地方，遇到这种情况，只能等死，别无他法。


## 说明/提示

样例解释 $1$

$(1,1) \to (1,2)\to (1,3)\to$ 喝魔液 $\to (3,4)\to (3,5)\to (3,6)$。

样例解释 $2$

因为只有一瓶魔液所以他们没办法逃出来。

样例解释 $3$

$D$ 和 $R$ 还可以是 $0$或者负数。

数据范围与约定

$40\%$ 的测试数据 $2\leq H,W\leq 5$。

$70\%$ 的测试数据 $2\leq H,W\leq 100$。

$100\%$ 的测试数据 $2\leq H,W\leq 1000,|D|<H,|R|<W$。

## 样例 #1

### 输入

```
3 6 2 1
...#..
..##..
..#...```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 7 2 1
..#..#.
.##.##.
.#..#..```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 6 -2 0
.#....
.#.#..
.####.
.#..#.
.##.#.
....#.```

### 输出

```
21```

# 题解

## 作者：x_faraway_x (赞：19)

一道简单的裸BFS啊~（貌似比I要简单？好吧I我还没做）

如果没有药水这个限制就是裸的BFS走迷宫，当然处理药水也很简单。

原先走迷宫需要用一个数组step[x][y]来记录到(x,y)的最少步数，这里只需要再添加一维就可以了。

我们用step[x][y][0]表示走到(x,y)且没有喝药的最少步数，用step[x][y][1]表示走到(x,y)且已经喝药的最小步数。

因为根据题目要求，总共只能喝一次药，所以简单处理一下即可。

具体过程如下：

遍历到一个点（简称遍历点），枚举上下左右的点（简称到达点），如果到达点可行，先把到达点按走迷宫的方式处理了，然后看遍历点状态是否吃药，如果未吃药则再处理到达点吃药可转移的点，当然要注意第三维的变化。

由于过程已经叙述过了故程序就不再注释。建议先根据上述思路自己写写代码哦！

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1005;
int h,w,d,r,st[N][N][2];
char s[N][N];
struct Point
{
    int x,y,u;
};
queue<Point> Q;
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
bool check(int x, int y)
{
    return x>=1&&y>=1&&x<=h&&y<=w&&s[x][y]=='.';
}
int main()
{
    scanf("%d%d%d%d",&h,&w,&d,&r);
    for(int i=1;i<=h;i++)
        scanf("%s",s[i]+1);
    memset(st,-1,sizeof(st));
    st[1][1][0]=0;
    Q.push((Point){1,1,0});
    while(!Q.empty()&&st[h][w][0]==-1&&st[h][w][1]==-1)
    {
        Point f=Q.front();
        Q.pop();
        for(int i=0;i<4;i++)
        {
            int x=dx[i]+f.x,y=dy[i]+f.y;
            if(check(x,y)&&st[x][y][f.u]==-1)
            {
                Q.push((Point){x,y,f.u});
                st[x][y][f.u]=st[f.x][f.y][f.u]+1;
                if(f.u==0&&check(x+d,y+r)&&st[x+d][y+r][1]==-1)
                {
                    Q.push((Point){x+d,y+r,1});
                    st[x+d][y+r][1]=st[x][y][0]+1;
                }
            }
        }
    }
    if(st[h][w][0]==-1&&st[h][w][1]==-1) puts("-1");
    else 
    printf("%d",min(st[h][w][0]==-1?1<<30:st[h][w][0],
                    st[h][w][1]==-1?1<<30:st[h][w][1])); //奇葩的写法，不建议效仿QWQ
}
```
PS当时比赛没时间写题啊 要写作业QAQ


---

## 作者：zpf_13516358919 (赞：14)

```cpp
//阅读题目后，首先明确药的作用
//不喝药就能走到终点，药的作用就是缩短距离
//如果不喝药到不了终点，那么要就必须用来穿墙
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
#include<map>
#include<queue>
#include<set>
#define LL long long
int dx[]={0,0,1,0,-1};
int dy[]={0,1,0,-1,0};
bool ma[1010][1010],past0[1010][1010],past1[1010][1010];
int n,m,sx,sy;
char s;
using namespace std;
struct node
{
    int x,y,step,f;
}q[1000010],cur,nxt;
void bfs1()//搜索出不用喝药能到达的地方 
{
    q[0].x=1;q[0].y=1;
    past0[1][1]=1;
    int head=0,tail=1;
    while(head<tail)
    {
        cur=q[head++];
        for(int i=1;i<=4;i++)
        {
            nxt.x=cur.x+dx[i];
            nxt.y=cur.y+dy[i];
            if(nxt.x>=1&&nxt.x<=n&&nxt.y>=1&&nxt.y<=m&&!ma[nxt.x][nxt.y]&&!past0[nxt.x][nxt.y])
            {
                past0[nxt.x][nxt.y]=1;
                q[tail++]=nxt;
            }
        }
    }
}
void bfs()
{
    memset(q,0,sizeof(q));
    q[0].x=1;q[0].y=1;q[0].step=0;q[0].f=0;
    past1[1][1]=1;
    int head=0,tail=1;
    while(head<tail)
    {
        cur=q[head++];
        if(cur.x==n&&cur.y==m)
        {
            cout<<cur.step;
            return;
        }
        for(int i=0;i<=4;i++)
        {
            nxt.f=cur.f;
            if(i==0)
            {
                if(!nxt.f)//没喝过药
                {
                    nxt.x=cur.x+dx[0];
                    nxt.y=cur.y+dy[0];
                    if(!past0[n][m])//不喝药不能走到终点
                    {
                        if(past0[nxt.x][nxt.y])
                                       //喝药之后,再走到不喝药能走到的地方,喝药就没有意义
                    continue;//略过这种情况
                    }
                }
                else continue;
            }
            else
            {
                nxt.x=cur.x+dx[i];
                nxt.y=cur.y+dy[i];
            }
            if(nxt.x>=1&&nxt.x<=n&&nxt.y>=1&&nxt.y<=m&&!ma[nxt.x][nxt.y]&&!past1[nxt.x][nxt.y])
            {
                if(i==0)nxt.f=1;//本次喝药,标记为使用
                past1[nxt.x][nxt.y]=1;//标记为走过
                nxt.step=cur.step+1;//步数+1
                q[tail++]=nxt;
            }
        }
    }
    cout<<-1;
}
int main()
{
    cin>>n>>m>>sx>>sy;
    for(int i=1;i<=n;i++)
    for(int j=0;j<=m;j++)
    {
        scanf("%c",&s);
        if(s=='.')ma[i][j]=0;
        else ma[i][j]=1;
    }
    dx[0]=sx;dy[0]=sy;
    bfs1();
    bfs();
    return 0;
}

```

---

## 作者：amstar (赞：8)

数据范围题目中是<=1000，开1010第二点会re，直接开2010，AC

代码并不难，就是判重就好，vis前两维记录坐标，第三维记录是否用过药水，然后bfs即可，注意判重。

注意如果一个点用过了药水，则他所有可以扩展的点的状态都是喝过的，就是flag=1，不能再用药水了，不用再搜。

这个点没用过的话，它扩展的点的既有不用的（上下左右），也有用药水的，都要入队。




    
```cpp
#include<cstdio>
#include<queue>
#include<iostream>
using namespace std;
const int MAXN = 2010;
struct node{
    int x,y,step;
    int flag;
}cur,nxt;
int dx[6] = {0,0,1,-1};
int dy[6] = {1,-1,0,0};
char mp[MAXN][MAXN];
bool v[MAXN][MAXN][2];
int n,m,ax,ay,f;
queue<node>q;
void bfs()
{
    cur.flag = 0;cur.step = 0;
    cur.x = 1;cur.y = 1;
    q.push(cur);
    v[1][1][0] = true;
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        if (cur.flag == 1) f = 1;
        else f = 0;
        for (int i=0; i<4; ++i)
        {
            int xx = dx[i]+cur.x;
            int yy = dy[i]+cur.y;
            if (xx>0&&xx<=n&&yy>0&&yy<=m&&mp[xx][yy]!='#'&&!v[xx][yy][f])    //是否出界 
            {
                if (xx==n&&yy==m)
                {
                    printf("%d",cur.step+1);
                    return ;
                }
                v[xx][yy][f] = true;
                nxt.flag = f;nxt.step = cur.step+1;
                nxt.x = xx;nxt.y = yy;
                q.push(nxt);
            }
        }
        int xx = cur.x+dx[4], yy = cur.y+dy[4];
        if (f==0&&!v[xx][yy][1]&&xx>0&&xx<=n&&yy>0&&yy<=m&&mp[xx][yy]!='#')
        {
            if (xx==n&&yy==m)
            {
                printf("%d",cur.step+1);
                return ;
            }
            v[xx][yy][1] = true;
            nxt.flag = 1;nxt.step = cur.step+1;
            nxt.x = xx;nxt.y = yy;
            q.push(nxt);
        }
    }
    printf("-1");    
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&dx[4],&dy[4]);
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=m; ++j)
            cin>>mp[i][j];
    bfs();
    return 0;
}
```

---

## 作者：hs_wfz_orz (赞：4)

 题解 P3818 【小A和uim之大逃离 II】
 不要往下翻了 这是你的选择
 回归正题，这显然是一道bfs~~裸题~~，可是蒟蒻打了3天
我的解法可能和其他dalao不一样，不要例外。只有~~120行~~（满分吖吖啊）

 首先明确一点：：if嗑药那么能到（n，m）就加速，否则穿墙
------------------------------不怎华丽的分割线----------------------------

我们需要3个bfs（bfs，bfs1，bfs2）分别记录（1,1）可以扩展的点，加速，穿墙。

 1.第一个bfs就是一个bfs板子，遇到墙就退回并用vis1记录，步数用num1记录

 记录后我们再分情况讨论如果vis1[n][m]==1那么就加速，否则穿墙

 2.加速，从（n,m）扩展，用ans记录最小值，且ans的初值为num1[n][m]（不加速的最大值）可是为什么不是0x7fffffff%……* -----假如嗑药值为-1，-1，那么嗑药比不嗑药还慢，ans就不更新了，同时，不能输出-1，因为决定由一个解
 3.同理，就是有几个细节，ans的初值为0x7fffffff，如果ans的值没有改变，就输出-1

 可是问题来了，怎么更新ans的值
 为了解决这个问题，定义vis2和num2，嗑药时先判断能不能到（1,1）扩展的点，若果能更新
 那么vis2,num2有什么用呢？？？qwq先来看更新式
ans=min(ans,num1[h.x-s1][h.y-s2]+1+num2[h.x][h.y]);(h.x,h.y为现在的点，+1是嗑药也要消耗步数）
 再来解释一下这个式子，因为我们是从（n，m）开始扩展的所以要-s1，-s2.又因为这个式子是在vis1[h.x-s1][h.y-s2](1,1扩展的点）建立的，那么一定存在num1的值，num1[h.x-s1][h.y-s2]嗑药后的点的步数（1,1开始的），和到嗑药的这个点的步数（n,m开始的）+1
 上代码
```
#include<iostream>//第一次写码风---wfz' 
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
struct node{
	int x;
	int y;
};
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};
int n,m,s1,s2;
int g[1010][1010],vis1[1010][1010],vis2[1010][1010],num1[1010][1010],num2[1010][1010];
bool torf;
void bfs()
{
	queue<node> q;
	node h,o;
	vis1[1][1]=1;
	h.x=1;
	h.y=1;
	q.push(h);
	while(!q.empty()){
		h=q.front();
		q.pop();
		for(int i=1;i<=4;i++){
			int u=h.x+dx[i];
			int v=h.y+dy[i];
			if(u<1||u>n||v<1||v>m||vis1[u][v]==1||g[u][v]==1) continue;
			vis1[u][v]=1;
			o.x=u;
			o.y=v;
			num1[u][v]=num1[h.x][h.y]+1;
			q.push(o);
		}
	}	
}
void bfs1(){
	queue<node> q;
	node h,o;
	vis2[n][m]=1;
	h.x=n;
	h.y=m;
	int ans=num1[n][m];
	q.push(h);
	while(!q.empty()){
		h=q.front();
		q.pop(); 
		if(h.x-s1>=1&&h.x-s1<=n&&h.y-s2>=1&&h.y-s2<=m&&vis1[h.x-s1][h.y-s2]==1){
			ans=min(ans,num1[h.x-s1][h.y-s2]+1+num2[h.x][h.y]);
			//cout<<h.x<<" "<<h.y<<endl;
		} 
		for(int i=1;i<=4;i++){
		int u=h.x+dx[i];
		int v=h.y+dy[i];
		if(u<1||u>n||v<1||v>m||vis2[u][v]==1||g[u][v]==1) continue;
		    vis2[u][v]=1;
			o.x=u;
			o.y=v;
			num2[u][v]=num2[h.x][h.y]+1;
			q.push(o);
	}
}
cout<<ans;
}
void bfs2(){
	queue<node> q;
	node h,o;
	vis2[n][m]=1;
	h.x=n;
	h.y=m;
	int ans=0x7fffffff; 
	q.push(h);
	while(!q.empty()){
		h=q.front();
		q.pop();
		if(h.x-s1>=1&&h.x-s1<=n&&h.y-s2>=1&&h.y-s2<=m&&vis1[h.x-s1][h.y-s2]==1)
		{
			ans=min(ans,num1[h.x-s1][h.y-s2]+1+num2[h.x][h.y]);
		}
		for(int i=1;i<=4;i++){
		int u=h.x+dx[i];
		int v=h.y+dy[i];
		if(u<1||u>n||v<1||v>m||vis2[u][v]==1||g[u][v]==1) continue;
		    vis2[u][v]=1;
			o.x=u;
			o.y=v;
			num2[u][v]=num2[h.x][h.y]+1;
			q.push(o);
	}
}
if(ans!=0x7fffffff){
	cout<<ans;
	return ;
}
cout<<-1;
}
int main()
{
	cin>>n>>m>>s1>>s2;
    //if(s1>=n||s2>=m) torf=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			if(c=='#') g[i][j]=1;
		}
	}
	if(g[n][m]==1){
		cout<<-1;
		return 0;
	}
	bfs();
	if(vis1[n][m]==1) bfs1();
	else bfs2();
	//cout<<num1[n][m];
}
```


---

## 作者：中二病 (赞：3)

~~这么水的广搜模板题，看一眼直接秒掉~~

首先广搜是没跑了

然后一局只能用药一次，开一个bo队列记录有没有用过

再开一个num队列记录步数

再开两个队列记录位置

然后还有一个问题，点的遍历。用过药遍历这个点和没用过药遍历这个点状态是不一样的，所以开一个bo1记录没用过药遍历,bo2记录用过药遍历

然后广搜

上代码

```
#include<iostream>
#include<queue>
using namespace std;
int p[4]={1,0,-1,0},q[4]={0,1,0,-1};
char map[1010][1010];
int h,w,d,r;
int x,y,z,n;
bool bo1[1010][1010],bo2[1010][1010];
queue <int> qx;
queue <int> qy;
queue <int> num;
queue <bool> bo;
int main()
{
	cin>>h>>w>>d>>r;
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		{
			cin>>map[i][j];
		}
	}
	qx.push(1);
	qy.push(1);
	num.push(0);
	bo.push(1);
	bo1[1][1]=1;
	while(!qx.empty())
	{
		x=qx.front();qx.pop();
		y=qy.front();qy.pop();
		z=num.front();num.pop();
		n=bo.front();bo.pop();
		if(x==h&&y==w)
		{
			cout<<z;
			return 0;
		}
		for(int i=0;i<=3;i++)
		{
			if(x+p[i]>0&&y+q[i]>0&&map[x+p[i]][y+q[i]]=='.')
			{
				if(bo1[x+p[i]][y+q[i]])continue;
				if(!n&&bo2[x+p[i]][y+q[i]])continue;
				qx.push(x+p[i]);qy.push(y+q[i]);
				num.push(z+1);bo.push(n);
				if(n)bo1[x+p[i]][y+q[i]]=1;
				else bo2[x+p[i]][y+q[i]]=1;
			}
		}
		if(n&&map[x+d][y+r]=='.'&&!bo1[x+d][y+r]&&!bo2[x+d][y+r])
		{
			qx.push(x+d);qy.push(y+r);
			num.push(z+1);bo.push(0);
			bo2[x+d][y+r]=1;
		}
	}
	cout<<"-1";
	return 0;
}
```


---

## 作者：gyf12138 (赞：3)

###这道题是一道bfs的问题

应该很容易看出这个是需要遍历全图的

个人习惯广搜，深搜其实也可以

这里要说一个我一直第二个点re然后90分的问题

##数组要开1010，千万不要开成1001，嗯，就是这样，下面都有注释详解，若诸位dalao有何问题，欢迎请教

        
        
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int N = 1010;
int h, w, d, r;
bool graph[N][N];
int q[N*N*2][3];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int dis[2][N][N];        //0表示没嗑药，1表示嗑药 
void input()
{
    char c;
    scanf("%d%d%d%d", &h, &w, &d, &r);
    for(int i = 1; i <= h; i++)
        for(int j = 1; j <= w; j++)
        {
            cin>>c;
            if(c == '.')
                graph[i][j] = 1;
            else
                graph[i][j] = 0;
        }    
    memset(dis, -1, sizeof(dis));     //走不了输出-1，为了方便直接定义 
}
void bfs()
{
    int head = 0, tail = 1;
    q[0][0] = 0;        //用k代表没嗑药的状态 
    q[0][1] = 1;        //用x代表横坐标 
    q[0][2] = 1;        //用y代表纵坐标 
    dis[0][1][1] = 0;    //初始距离为0 
    while(head < tail)
    {
        int k = q[head][0], x = q[head][1], y = q[head][2], z = dis[k][x][y];
        for(int i = 0; i < 4; i++)
        {
            int xx = x + dx[i], yy = y + dy[i]; //bfs全图 
            //cout<<xx<<" "<<yy<<endl;
            if(dis[k][xx][yy] == -1 && xx >= 1 && xx <= h && yy >= 1 && yy <= w && graph[xx][yy])
            {                                    //表示这个点能走的时候往下继续搜索
                dis[k][xx][yy] = z + 1;
                q[tail][0] = k;
                q[tail][1] = xx;
                q[tail][2] = yy;
                tail++;
            }
        }
        if(k == 0)    //若是走不了，该嗑药了 
        {
            int xx = x + d, yy = y + r;
            if(dis[k][xx][yy] == -1 && xx >= 1 && xx <=h && yy >= 1 && yy <= w && graph[xx][yy])    //能走 
            {
                dis[1][xx][yy] = z + 1;
                q[tail][0] = 1;            //磕过药标记成1 
                q[tail][1] = xx;
                q[tail][2] = yy;
                tail++;
            }
        }
        head++; //做完一次头指针往后移，准备让下一个点入队 
    }    
    int ans1 = dis[0][h][w], ans2 = dis[1][h][w]; //因为bfs遍历特性一般第一个出来的就是最优解
    if(ans1 == -1)            //没嗑药出不来就看嗑药的 
        printf("%d\n", ans2);
    else if(ans2 == -1)        //若是嗑药还出不来就没办法了 
        printf("%d\n", ans1);
    else
        printf("%d\n", min(ans1, ans2));    //能出来的就看哪个小咯,半天输出不来气死了。。 
}
int main()
{
    input();
    bfs();
    return 0;
}
```

---

## 作者：AuCloud (赞：2)

~~为啥你们要判断是否穿墙呢……~~


看了好多题解和我的解法都不一样emmm

我的想法很简单

从起点进行一次bfs（设为a数组）

同时从终点也进行一次bfs（设为b数组）

则在(x, y)点喝药的最短路可表示为$a[x][y]+b[x+d][y+r]+1$

之后暴力枚举嗑药点就好

至于穿不穿墙什么的就不需要判断了

时间复杂度$O(n^2)$，完全能过
```cpp
#include <bits/stdc++.h>
#define X x + movx[i]
#define Y y + movy[i]
using namespace std;
bool mapp[2001][2001];
int movx[4] = {1, 0, -1, 0};
int movy[4] = {0, 1, 0, -1};
int n, m;
int a[2001][2001], b[2001][2001];
bool used[2001][2001];
struct hehe{
    int x, y;
};
void bfs1()
{
    queue < hehe >q;
    hehe now;
    now.x = now.y = 1;
    memset(a, 0x3f, sizeof a);
    a[1][1] = 0;
    q.push(now);
    while(q.size())
    {
        now = q.front();
        q.pop();
        int x = now.x, y = now.y;
        used[x][y] = 0;
        for(int i = 0; i < 4; i++)
        {
            if(mapp[X][Y] && a[x][y] + 1 < a[X][Y])
            {
                a[X][Y] = a[x][y] + 1;
                if(!used[X][Y])
                {
                    hehe neww;
                    neww.x = X, neww.y = Y;
                    q.push(neww);
                    used[X][Y] = 1;
                }
            }
        }
    }
}
void bfs2()
{
    queue < hehe >q;
    hehe now;
    now.x = n;
    now.y = m;
    memset(b, 0x3f, sizeof b);
    memset(used, 0, sizeof used);
    b[n][m] = 0;
    q.push(now);
    while(q.size())
    {
        now = q.front();
        q.pop();
        int x = now.x, y = now.y;
        used[x][y] = 0;
        for(int i = 0; i < 4; i++)
        {
            if(mapp[X][Y] && b[x][y] + 1 < b[X][Y])
            {
                b[X][Y] = b[x][y] + 1;
                if(!used[X][Y])
                {
                    hehe neww;
                    neww.x = X, neww.y = Y;
                    q.push(neww);
                    used[X][Y] = 1;
                }
            }
        }
    }
}
int main()
{
    int e, r;
    cin >> n >> m >> e >> r;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            char ch;
            cin >> ch;
            mapp[i][j] = (ch == '.');
        }
    }
    bfs1();
    bfs2();
    int ans = a[n][m];
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(a[i][j] <= 1000000 && i + e >= 0 && j + r >= 0 && b[i + e][j + r] <= 1000000 && mapp[i + e][j + r])
                ans = min(ans, a[i][j] + b[i + e][j + r] + 1);
        }
    }
    if(ans > 1000000 || !mapp[n][m]) cout << -1;
    else cout << ans;
    return 0;
}
```
后记：

说一下这题的几个坑点

- D和R可能是负数，所以嗑药的时候一定要特判当前点磕完药后的坐标是否小于零

- 出口可能是墙！！！

- 注意数组不能大也不能小

upd:更正了一处公式错误（手残）

---

## 作者：ylsoi (赞：2)

这一题用dfs必定会超时，大概是40分吧（当然是没有剪枝，我也不会剪枝），所以就知可以用bfs，但是一个非常关键的问题就是要记录有没有嗑药，磕了药就不可以再嗑药了，所以我们在队列的结构体中在设置有没有磕过药，如果这个结点磕过药了，那么它以后拓展的每一个结点也都是磕过药的，当然同一个坐标可能存在嗑药和没嗑药两种情况，都是可以入队的，就比如说第三个样例中的（4，3）；当然把结点送入队列之后，我们还要去重，这个时候就不可以单独地记录这个坐标有没有来过了，因为存在一种情况就是如果瞬移到了某个点之后，实际上，走到这个点之后再瞬移才是正解。所以要用一个三维的数组来记录某点某状态的情况。附上代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath> 
using namespace std;
int h,w,d,r,p;
char a[1005][1005];
bool s[1005][1005][2];
int xx[10]={0,1,0,-1,0};
int yy[10]={0,0,-1,0,1};
int mins=2147483647;
struct tt
{
    int x;
    int y;
    int step;
    bool flag;
}t[1005*1005*2];
void bfs()
{
    int head=0,tail=1;
    t[1].x=1;t[1].y=1;
    s[1][1][0]=1;//第一个点要初始化
    while(head<tail)
    {
        head++;
        for(int i=1;i<=5;i++)
        {
            if(i==5&&t[head].flag==1)//如果父亲结点都是磕过药的，那么就可以不用再走了；
            continue;
            int x1=t[head].x+xx[i],y1=t[head].y+yy[i];
            if(x1>=1&&x1<=h&&y1>=1&&y1<=w&&a[x1][y1]!='#')
            {
                if(t[head].flag==1&&s[x1][y1][1]==1)continue;//之前嗑药来过，现在又嗑药来，所以就不行
                if(t[head].flag==0&&s[x1][y1][0]==1&&i!=5)continue;//之前走路过来的，现在又走过来，当然也不行
                tail++;
                t[tail].x=x1;
                t[tail].y=y1;
                if(t[head].flag==1||i==5)
                {
                    t[tail].flag=1;
                    s[x1][y1][1]=1;
                }
                else s[x1][y1][0]=1;
                t[tail].step=t[head].step+1;
                if(x1==h&&y1==w)
                {
                    p=tail;
                    head=tail;
                    break;
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d%d%d",&h,&w,&d,&r);
    getchar();
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        scanf("%c",&a[i][j]);
        getchar();
    }
    xx[5]=d;yy[5]=r;//这是第五种移动的方式
    bfs();
    for(int i=1;i<=p;i++)
    {
        if(t[i].x==h&&t[i].y==w)//如果搜不到的话那就直接输出-1了
        {
            printf("%d",t[i].step);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
```

---

## 作者：zjp_shadow (赞：2)

看到这题。。很容易知道就是搜索。。

但最近最短路做的有点多  我想想能不能建一个图 然后跑一边spfa来算起点到终点的最短路

之后思考了下如何建图 最难的就是普通的上下左右移动 和 只能嗑一次药如何进行区分

我觉得 可以将只能走一次的边权（或者说是标记）设为1  别的为0

最后 将dis 普通的一维数组 扩展成二维的  第二个维度 也是 0 和 1 区分  0代表到这个点 不进行嗑药 所走的最短路 1就是嗑药的 （好像和大部分的bfs标记差不多）

上程序:

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<queue>
#include<iostream>
#define For(i, l, r) for(int i = (l); i <= (int)(r); ++i)
#define Fordown(i, r, l) for(int i = (r); i >= (int)(l); --i)
#define Set(a, v) memset(a, v, sizeof(a))
using namespace std;

inline int read(){
  int x = 0, fh = 1; char ch;
  for(; !isdigit(ch); ch = getchar()) if (ch == '-') fh = -1;
  for(; isdigit(ch); ch = getchar()) x = (x<<1) + (x<<3) + (ch^'0');
  return x * fh;
}

inline bool read_char() {
   char ch = getchar();
   for(; ch != '.' && ch != '#'; ch = getchar());
   return ch == '.' ? 1 : 0;
}  //打的一个读取图的东西。。

const int N = 1010, M = 1010*1010*(4+1), inf = 0x3f3f3f3f;
int dis[N*N][2], fx[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
bool MAP[N][N], inq[N*N];
bool val[M];
int to[M], Next[M], Head[M], e = 0;
int h, w, fl1, fl2;
inline void add_edge (int u, int v, bool pass) {
    to[++e] = v;
    Next[e] = Head[u];
    val[e] = pass; //如果这条边需要嗑药 则标记一下 
    Head[u] = e;
} //用链式前向星存边 减少空间消耗 

inline int bh (int x, int y) {return (x-1) * w + y; } //对二维矩阵的每个点进行编号 

int spfa () {
    Set(dis, inf);
    queue<int> Q;
    Q.push(1); dis[1][0] = dis[1][1] = 0; //spfa初始化 
    while (!Q.empty()) {
        int now = Q.front(); Q.pop(); inq[now] = 0;
        for (int i = Head[now]; i; i = Next[i]) {
         int v = to[i];               
         if (!val[i]) {  //不嗑药的情况 
             if (dis[v][1] > dis[now][1] + 1) { //当前起始点嗑药的距离+1 比到达点嗑药距离要短 
                 dis[v][1] = dis[now][1] + 1; //更新 
                 if (!inq[v]) {inq[v] = 1; Q.push(v);}
             } 
             if (dis[v][0] > dis[now][0] + 1) {  //同上不嗑药的情况 
                 dis[v][0] = dis[now][0] + 1;
                 if (!inq[v]) {inq[v] = 1; Q.push(v);}
             }
        }
        else {
            if (dis[v][1] > dis[now][0] + 1) { //当前起始点不嗑药的距离+1 比到达点嗑药距离要短 
                dis[v][1] = dis[now][0] + 1;
                if (!inq[v]) {inq[v] = 1; Q.push(v);}
                }
             }
        }
    }
    int t = bh(h, w), ans = min(dis[t][1], dis[t][0]); //取出到终点的最短路 
    return ans == inf ? -1 : ans; //到不了为-1 到得了为嗑药和不嗑药较小的那个 
}

int main(){
    h = read(); w = read(); fl1 = read(); fl2 = read(); //fl = flash 闪现（滑稽） 
    For (i, 1, h) 
     For (j, 1, w) 
      MAP[i][j] = read_char();
    
    For (i, 1, h)
     For (j, 1, w) 
      if (MAP[i][j]) { //当前位置合法 
        For (k, 0, 3) {
            int x1 = i + fx[k][0], y1 = j + fx[k][1];
            if (MAP[x1][y1]) {
                int u = bh(i, j), v = bh(x1, y1); //取出起始点和终点的编号 
                add_edge(u, v, false); //加入此边，标记为假 
            }
        }
        int x2 = i + fl1, y2 = j + fl2; //嗑药后的坐标 
        if (x2 <= 0 || y2 <= 0 || x2 > h || y2 > w) continue; //位置不合法 
        if (MAP[x2][y2]) {
            int u = bh(i, j), v = bh(x2, y2);
            add_edge(u, v, true); //嗑药标记为真 
        }
      }
          
    printf ("%d\n", spfa ());
}
```
ps:这种思路 其实本身和各位大佬的bfs差不多。。。 只是强行用了图论写。。  时间效率略慢一些


---

## 作者：attack (赞：1)

其实这题大可不必建边跑最短路什么的。

我们可以用一个vis[i][j][0/1]数组来记录状态。

0表示是通过走路的方式到达的这个点，

1表示通过魔法的方式走的到这个点。

还有一个很坑的地方就是vis开小了会RE第2个点，开大了会RE第7个点，

莫名其妙

                
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#define lli long long int 
using namespace std;
void read(int &n)
{
    char c='+';int x=0;bool flag=0;
    while(c<'0'||c>'9')
    {c=getchar();if(c=='-')flag=1;}
    while(c>='0'&&c<='9')
    {x=x*10+(c-48);c=getchar();}
    flag==1?n=-x:n=x;
}
int n,m;
int mox,moy;
int map[2501][2501];
bool vis[2501][2101][3];
int xx[5]={-1,+1,0,0};
int yy[5]={0,0,-1,+1};
struct node
{
    int x,y,step;
    bool flag;// 是否喝了药水、 
}now,nxt;
void  BFS()
{
    queue<node>q;
    vis[1][1][0]=1;
    //vis[bgx][bgy][1]=1;
    now.x=1;
    now.y=1;
    now.flag=0;
    now.step=0;
    q.push(now);
    bool end=0;
    while(q.size()!=0)
    {
        node p=q.front();
        q.pop();
        if(p.x<0||p.y<0||p.x>n||p.y>m)
            continue;
        for(int i=0;i<4;i++)
        {
            int wx=xx[i]+p.x;
            int wy=yy[i]+p.y;
            if(map[wx][wy]==1&&wx>0&&wy>0&&wx<=n&&wy<=m)
            {
                if(vis[wx][wy][p.flag]==0)
                {
                vis[wx][wy][p.flag]=1;
                node w;
                w.x=wx;
                w.y=wy;
                w.step=p.step+1;
                w.flag=p.flag;
                if(wx==n&&wy==m)
                {
                    printf("%d",w.step);
                    return ;
                }
                q.push(w);    
                }
            }
        }
        if(p.flag==0)
        {
            int wx=p.x+mox;
            int wy=p.y+moy;    
            if(map[wx][wy]==1&&wx>0&&wy>0&&wx<=n&&wy<=m)
            {
                if(vis[wx][wy][1]==0)
                {
                    vis[wx][wy][1]=1;
                    node w;
                    w.x=wx;
                    w.y=wy;
                    w.step=p.step+1;
                    w.flag=1;
                    if(wx==n&&wy==m)
                    {
                        printf("%d",w.step);
                        return ;
                    }
                    q.push(w);    
                }
            }
        }
    }
        printf("-1");
}
int main()
{
    //ios::sync_with_stdio(false);
    cin>>n>>m>>mox>>moy;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            char p;
            cin>>p;
            if(p=='.') map[i][j]=1;// 可以通过
            else 
            if(p=='#') map[i][j]=2;// 不能通过    
        }
    }
    BFS();
    return 0;
}
```

---

## 作者：totorato (赞：1)

其实也可以这样想。

先BFS两遍，分别保存每个点到起点的距离，和到终点的距离（这里的距离指步数），然后再for(i=1 to n)for(j=1 to m) 一下，查找每个点经过跳跃再到终点的距离。于是只不过有3的常数而已，想起来和实现起来都很方便

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

#define MX 2001

using namespace std;

int mp[MX][MX],n,m,v1,v2,d1[MX][MX],d2[MX][MX];
int nvec[5][3]={{0,0,0},{0,0,1},{0,1,0},{0,0,-1},{0,-1,0}};
typedef struct poit{int x,y;}point;
point q[MX*MX];
char vis[MX][MX];
point make_point(int x,int y){point p;p.x=x,p.y=y;return p;}

void sch(point frm,int (*dis)[MX])
{
    int h=1,t=1;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)dis[i][j]=-1,vis[i][j]=0;
    q[h]=frm;
    vis[frm.x][frm.y]=1;
    dis[frm.x][frm.y]=0;
    point now,nxt;
    while(h>=t)
    {
        now=q[t++];
        for(int i=1;i<=4;i++)
        {
            nxt.x=now.x+nvec[i][1];
            nxt.y=now.y+nvec[i][2];
            if(nxt.x>n||nxt.y>m||nxt.x<1||nxt.y<1||mp[nxt.x][nxt.y]==1||vis[nxt.x][nxt.y]==1)continue;
            q[++h]=nxt;
            vis[nxt.x][nxt.y]=1;
            dis[nxt.x][nxt.y]=dis[now.x][now.y]+1;
        }
    }
}

int main()
{
    char ch='6';
    scanf("%d%d%d%d",&n,&m,&v1,&v2);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            ch=getchar();
            while(ch!='#'&&ch!='.')ch=getchar();
            if(ch=='#')mp[i][j]=1;
            else mp[i][j]=0;
        }
    }
    if(mp[1][1]||mp[n][m]){cout<<"-1"<<endl;return 0;}
    sch(make_point(1,1),d1);
    sch(make_point(n,m),d2);
    int mdis=99999999;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(i+v1<=n&&j+v2<=m&&i+v1>=1&&j+v2>=1)
                if(d1[i][j]!=-1&&d2[i+v1][j+v2]!=-1)
                    mdis=min(mdis,d1[i][j]+d2[i+v1][j+v2]+1);
    if(d1[n][m]!=-1)mdis=min(mdis,d1[n][m]);
    if(mdis<99999999)cout<<mdis<<endl;
    else cout<<"-1"<<endl;
    return 0;
}
```

---

## 作者：1124828077ccj (赞：1)

这题其实不难，仔细想想可以发现一些事情。。。

设d[i][j][k]为从1,1走到i,j的最短路径的长度，k表示是否喝过药水

然后每次分别转移，跑一遍BFS就解决了

看代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<queue>
using namespace std;
int n,m,d,r,ans[1002][1002][2];
char s[1002][1002];
queue<int>q1,q2,q3;
int main()
{
    scanf("%d%d%d%d",&n,&m,&d,&r);
    for (int i=1;i<=n;i++)
    scanf("%s",s[i]+1);
    memset(ans,-1,sizeof(ans));
    ans[1][1][0]=0;q1.push(1);q2.push(1);q3.push(0);
    while(!q1.empty())
    {
        int u1=q1.front(),u2=q2.front(),u3=q3.front();
        q1.pop();q2.pop();q3.pop();
        if (u1==n && u2==m){printf("%d\n",ans[u1][u2][u3]);return 0;}
        if (u1+1<=n && ans[u1+1][u2][u3]==-1 && s[u1+1][u2]!='#')//向下
        {
            ans[u1+1][u2][u3]=ans[u1][u2][u3]+1;
            q1.push(u1+1);q2.push(u2);q3.push(u3);
        }
        if (u1-1>0 && ans[u1-1][u2][u3]==-1 && s[u1-1][u2]!='#')//向上
        {
            ans[u1-1][u2][u3]=ans[u1][u2][u3]+1;
            q1.push(u1-1);q2.push(u2);q3.push(u3);
        }
        if (u2+1<=m && ans[u1][u2+1][u3]==-1 && s[u1][u2+1]!='#')向右
        {
            ans[u1][u2+1][u3]=ans[u1][u2][u3]+1;
            q1.push(u1);q2.push(u2+1);q3.push(u3);
        }
        if (u2-1>0 && ans[u1][u2-1][u3]==-1 && s[u1][u2-1]!='#')//向左
        {
            ans[u1][u2-1][u3]=ans[u1][u2][u3]+1;
            q1.push(u1);q2.push(u2-1);q3.push(u3);
        }
        if (!u3 && u1+d>0 && u1+d<=n && u2+r<=m && u2+r>0 && ans[u1+d][u2+r][1]==-1 && s[u1+d][u2+r]!='#')//喝药水
        {
            ans[u1+d][u2+r][1]=ans[u1][u2][u3]+1;
            q1.push(u1+d);q2.push(u2+r);q3.push(1);
        }
    }
    puts("-1");//无方案
    return 0;
}
```

---

## 作者：a1_1 (赞：1)

### P3818 【小A和uim之大逃离 II】
又一道~~水~~的搜索题，裸的bfs。关键在于要用三维数组。记a[i][j][1]为到第i行第j行不用魔药的最少步数，记a[i][j][0]为到第i行第j行用魔药的最少步数。上码:
```cpp
#include<bits/stdc++.h>
#define flag(e,f,g) (e>0&&e<=h&&f>0&&f<=w&&a[e][f][g]=='.')
using namespace std;
struct run{int x,y,dep,magic;};//先定一个结构体
queue<run>q;
int h,w,d,r,b[5]={0,-1,1,0,0},c[5]={0,0,0,-1,1};//b、c控制方向
char a[1010][1010][2];//用于标记状态
void bfs(run z)
{
	int i;
	run l;
	q.push(z);
	while (q.size())
	{
		l=q.front();
		q.pop();
		if (l.x==h&&l.y==w)//到达终点
		{
			cout<<l.dep<<endl;//输出步数
			exit(0);
		}
		for (i=1;i<=4;i++)
		{
			if (flag(l.x+b[i],l.y+c[i],l.magic))//不用魔药
			{
				a[l.x+b[i]][l.y+c[i]][l.magic]='#';//标记
				q.push({l.x+b[i],l.y+c[i],l.dep+1,l.magic});//将新状态加入队尾
			}
		}
		if (flag(l.x+d,l.y+r,0)&&l.magic==1)//用魔药
		{
			a[l.x+d][l.y+r][0]='#';//同上
			q.push({l.x+d,l.y+r,l.dep+1,0});//同上			
		}
	}
	cout<<-1<<endl;//逃不了
}
int main()//巨短主函数，只负责输入和调用bfs
{
	int i,j;
	cin>>h>>w>>d>>r;
	for (i=1;i<=h;i++)
		for (j=1;j<=w;j++)
			cin>>a[i][j][0],a[i][j][1]=a[i][j][0];
	a[1][1][0]=a[1][1][1]='#';//标记起始位置
	bfs({1,1,0,1});
	return 0;
}
```


---

## 作者：Limit (赞：1)

这题目其实是一道典型的bfs解迷宫问题，唯一的难度在于可以使用魔法，而且只能使用一次。因此我们需要多建立一张表存使用魔法后的情况。
代码：
```pascal
const z:array[1..4,1..2]of -1..1=((1,0),(-1,0),(0,1),(0,-1));//四个方向
var i,j,k:longint;
    m,n:longint;
    h,t:longint;          //第二张表为0，原表为1
    a:array[0..1001,0..1001,0..1]of boolean;
    x,y,u,p:array[0..2000001]of longint;
    d,r:longint;
    ch:char;
begin
  readln(m,n,d,r);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='.' then
      begin
        a[i,j,0]:=true;
        a[i,j,1]:=true;
      end
      else
      begin
        a[i,j,0]:=false;
        a[i,j,1]:=false;
      end;
    end;
    readln;
  end;
  p[1]:=1;
  x[1]:=1;
  y[1]:=1;
  u[1]:=0;
  h:=1;
  t:=1;
  repeat
    if (x[t]=m) and (y[t]=n) then//到终点时，输出
    begin
      write(u[t]);
      exit;
    end;
    for i:=1 to 4 do//正常搜索，模板
    if a[x[t]+z[i,1],y[t]+z[i,2],p[t]] then
    begin
      a[x[t]+z[i,1],y[t]+z[i,2],p[t]]:=false;
      inc(h);
      p[h]:=p[t];//保留之前是否使用魔法
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      u[h]:=u[t]+1;
    end;
    if p[t]=1 then//之前没有使用过魔法
    begin
      if (x[t]+d>0) and (y[t]+r>0) and (x[t]+d<=m) and (y[t]+r<=n) then//因为使用魔法可能会超过边界，所以要特判一下
      if a[x[t]+d,y[t]+r,0] then//处理方法与正常相同
      begin
        inc(h);
        a[x[t]+d,y[t]+r,0]:=false;
        x[h]:=x[t]+d;
        y[h]:=y[t]+r;
        u[h]:=u[t]+1;
        p[h]:=0;//记录为用过魔法
      end;
    end;
    inc(t);
  until t>h;
  write(-1);//无解
end.
```


---

## 作者：maomao9173 (赞：1)

#### 作为一个蒟蒻，之前看这道题目，第一感觉是：这不是DP吗？然后顺手推了几个样例都过不了的方程出来。。。后来想一下才发现因为DP是扫的方式来计算的，所以扫到某一行的时候那里可能还没更新，就会导致一些gg的事情发生。。。

#### 这个题正解是BFS，前面dalao们都说的很清楚了，我就只把我之前过程中没搞懂的在这里贴一下，(如果发出来了)请配合其他dalao们的BFS代码食用。。

#### 因为我太弱了所以想要把这些（可能很常识的）东西记一下，求轻喷。。

### Q1:为什么不能用DP？
### A1:值会出现更新不到的情况，没法转移。
### Q2:为什么BFS过程中不需要加min来更新步数最小值？
### A2:因为BFS本来就是按层遍历，只要搜到一定就是最小值，所以不需要更新。
### Q3:为啥要通过判断有没有值来确定是否搜完？
### A3:同Q2，只要有值就一定是最小值，这时候就可以停止搜索了。


---

## 作者：saipubw (赞：0)

首先给你们讲下坑点：起点和终点是可以有障碍物的……

所以队列初始化的时候也要记得判断下有没有障碍物……

这道题我的思路和其他题解都不一样。

我们假设喝药之前的点为A，喝药之后的点为B

那么A必然要和起点联通，B必然要和终点联通。

于是我们可以想象两张图，一张是起点的联通块，一张是终点的联通块。

对第一张图我们用bfs求一下起点出发能到达的每个点的最短距离dis[i][j]

对第二张图我们再用bfs求一下终点出发能到达的每个点的最短距离dis2[i][j]

我们先考虑不喝药的情况,终点坐标是（H，W），由于不喝药，就是直接从起点到终点，那么可得：ans=dis[H][W]

然后再考虑喝药：

喝药就是在这两张图之间连一条边（~~空间跳跃~~），那么我们只要枚举图上所有合法的点：
```cpp
                ans=min(dis[i][j]+dis2[i+d][j+r]+1);
```
还看不懂？再翻译一下：答案就是：

**最小的（起点到喝药位置的距离+喝药后跳到的位置到终点的距离+喝药费用）**

这道题就被转换为了一个简单的隐式图的bfs求最短路。不用说了吧？

细节看代码吧

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
#define maxn 1005
#define INF 0x3f
#define INFF 0x3f3f3f3f
using namespace std;
int h, w, d, r;
char map[maxn][maxn];
int dis[maxn][maxn],dis2[maxn][maxn];
queue<pair<int,int>> que;
bool legal(int x, int y);
void fake_spfa(int x,int y,int dis[][maxn]);
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int main(void)
{
    int ans=INFF,i,j;
    memset(dis, INF, sizeof(dis));
    scanf("%d%d%d%d", &h, &w, &d, &r);
    for(i = 1; i <= h; i++)
        scanf("%s", (char *)map[i]+1);
    fake_spfa(1, 1,dis);
    ans = dis[h][w];
    memset(dis2, INF, sizeof(dis2));
    fake_spfa(h, w, dis2);
    for(i = 1; i <= h; i++)
        for(j = 1; j <= w; j++)
            if (dis[i][j]!=INFF&&legal(i+d,j+r)&&dis2[i+d][j+r]!=INFF)
                ans = min(ans, dis[i][j] + dis2[i + d][j + r] + 1);
    if (ans==INFF)
        ans = -1;
    printf("%d", ans);
    return 0;
}
void fake_spfa(int x,int y,int dis[][maxn])
{
    int nx, ny,i;
    if (map[x][y]!='#')
    {
        dis[x][y] = 0;
        que.push(make_pair(x, y));
    }
    while (que.size())
    {
        x=que.front().first,y=que.front().second;
        que.pop();
        for(i = 0; i < 4; i++)
        {
            nx = x + dir[i][0], ny = y + dir[i][1];
            if (legal(nx,ny)&&map[nx][ny]!='#'&&dis[nx][ny]==INFF)
            {
                dis[nx][ny] = dis[x][y] + 1;
                que.push(make_pair(nx, ny));
            }
        }
    }
    return;
}
inline bool legal(int x,int y)
{
    return (x >= 1 && y >= 1 && x <= h && y <= w);
}
```

---

## 作者：Starlight237 (赞：0)

核心算法：**BFS**

PS：这里用的是手写队列，不然在我们老师的毒瘤OJ上会被卡成TLE。

用一个结构体Node来保存状态，xy表示坐标，fly表示还能用魔法的次数（由题意应初始化为1），N则是达到该状态的最小步数。

这里vis数组用来判重，防止走过多余的状态。

flag保存是否能到达终点。

每次枚举四个方向，将能走到的点入队；如果能够使用魔液，则将使用了魔液的情况入队。并不需要像一些程序一样开三个队列qwq。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
char mp[1001][1001];
static int vis[1001][1001][2],m,n,flag,val,d,r;
struct Node{
    int x,y,fly,N;
    Node(){}//这里采用了构造函数的写法。
    Node(int xx,int yy,int dd,int nn):x(xx),y(yy),fly(dd),N(nn){}
};
inline bool okay(int x,int y,int fly){//判断该状态是否合理
	return x>=0&&x<m&&y>=0&&y<n&&mp[x][y]=='.'&&vis[x][y][fly]==0;
}
Node q[2000010];
int main(){
    scanf("%d%d%d%d",&m,&n,&d,&r);
    for(reg int i=0;i<m;++i)
        scanf("%s",mp+i);
    int head=0,tail=0;
    q[tail++]=Node(0,0,1,0);
    vis[0][0][d]=1;
    while(head<tail){
        Node p=q[head++];
        if(p.x==m-1&&p.y==n-1){
            flag=1,val=p.N;//达到目标状态
            break;
        }
        for(reg int i=0;i<4;++i)//不使用魔液的情况
            if(okay(p.x+dx[i],p.y+dy[i],p.fly))
                q[tail++]=Node(p.x+dx[i],p.y+dy[i],p.fly,p.N+1),
                vis[p.x+dx[i]][p.y+dy[i]][p.fly]=1;//新状态入队
        if(okay(p.x+d,p.y+r,p.fly-1)&&p.fly==1)//若还能使用魔液，则考虑使用魔液的情况
                q[tail++]=Node(p.x+d,p.y+r,p.fly-1,p.N+1),
                vis[p.x+d][p.y+r][p.fly-1]=1;//新状态入队
    }
    if(flag)printf("%d",val);//若能到达终点输出最小步数
    else printf("-1");
    return 0;
}
```
最后附上一道类似的题目：[飞越原野](https://www.cppentry.com/bencandy.php?fid=49&id=101487)

我的代码（大家可以看到和这题是惊人的相似）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
char mp[101][101];
static int vis[101][101][101],m,n,flag,val,d;
struct Node{
    int x,y,fly,N;
    Node(){}
    Node(int xx,int yy,int dd,int nn):x(xx),y(yy),fly(dd),N(nn){}
};
inline bool okay(int x,int y,int fly){
    return x>=0&&x<m&&y>=0&&y<n&&mp[x][y]=='P'&&vis[x][y][fly]==0;
}
Node q[1000010];
int main(){
    scanf("%d%d%d",&m,&n,&d);
    for(reg int i=0;i<m;++i)
        scanf("%s",mp+i);
    int head=0,tail=0;
    q[tail++]=Node(0,0,d,0);
    vis[0][0][d]=1;
    while(head<tail){
        Node p=q[head++];
        if(p.x==m-1&&p.y==n-1){
            flag=1,val=p.N;
            break;
        }
        for(reg int i=0;i<4;++i)
            if(okay(p.x+dx[i],p.y+dy[i],p.fly))
                q[tail++]=Node(p.x+dx[i],p.y+dy[i],p.fly,p.N+1),
                vis[p.x+dx[i]][p.y+dy[i]][p.fly]=1;
        for(reg int i=0;i<4;++i)
            for(reg int j=2;j<=p.fly;++j)
                if(okay(p.x+dx[i]*j,p.y+dy[i]*j,p.fly-j))
                    q[tail++]=Node(p.x+dx[i]*j,p.y+dy[i]*j,p.fly-j,p.N+1),
                    vis[p.x+dx[i]*j][p.y+dy[i]*j][p.fly-j]=1;
    }
    if(flag)printf("%d",val);
    else printf("impossible");
    return 0;
}
```

---

## 作者：御坂御坂 (赞：0)

来一发Pas题解


本题 **纯BFS**


唯一有一点 ~~神奇的地方~~ 就是


> 嗑药！

至于如何解决嗑药后的路径与嗑药前冲突


开两个数组**分别记录**就行啦

```cpp
type node=
    record
        x,y,step:longint;
        f:boolean;//到达这个节点时是否磕过药
    end;
var q:array[1..10000000] of node;
    a,b:array[-2000..2000,-2000..2000] of boolean;//记住一定要从负数开启！！！
    dx,dy:array[1..5] of longint;
    ch:char;
    i,j,n,m,h,w,l,r,x,y,nx,ny,s:longint;
begin
    readln(n,m,h,w);
    //第五个方向就是嗑药！
    dx[1]:=1;dx[2]:=0;dx[3]:=-1;dx[4]:=0;dx[5]:=h;
    dy[1]:=0;dy[2]:=1;dy[3]:=0;dy[4]:=-1;dy[5]:=w;
    //读入
    for i:=1 to n do 
    begin
        for j:=1 to m do 
        begin    
            read(ch);
            if ch='#' then a[i][j]:=false else a[i][j]:=true;
        end;
        readln;
    end;
    l:=0;r:=1;
    q[1].x:=1;q[1].y:=1;q[1].step:=0;
    a[1][1]:=false;
    b:=a;//双数组判重
    while l<=r do
    begin
        inc(l);x:=q[l].x;y:=q[l].y;s:=q[l].step;//初始化
        if (x=n)and(y=m) then
        begin
            writeln(s);break;
        end;
        for i:=1 to 5 do 
        begin
            if (i=5)and(q[l].f) then break;//药只有一瓶，嗑完了就没了
            nx:=x+dx[i];ny:=y+dy[i];
            //如果没嗑药就用没嗑药的判重，如果嗑药了就用嗑药后的判重
            if ((a[nx][ny])and(not(q[l].f)))or((b[nx][ny])and(q[l].f)) then 
            begin
                if (q[l].f)or(i=5) then b[nx][ny]:=false
                else begin
                    //防止嗑药后进入到之前的地方
                    a[nx][ny]:=false;
                    b[nx][ny]:=false;
                end;
                inc(r);q[r].x:=nx;q[r].y:=ny;q[r].step:=s+1;q[r].f:=q[l].f;
                if i=5 then q[r].f:=true;//磕过药了。。
            end;
        end;
    end;
    if (x<>n)and(y<>m) then writeln(-1);//没找到就滚
    
end.
```

---

