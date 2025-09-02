# 自宅からの脱出

## 题目描述

一张地图用一些字符串来描述。地图上的位置代表对应的平面坐标。

上端表示北方。西北角为坐标 $(1,1)$，东南角为坐标 $(M,N)$。坐标 $(x,y)$ 表示第 $y$ 行的第 $x$ 个字符。

- `.` 空地
- `C` 笔记本电脑
- `S` 出发地
- `G` 门

你可以在 $1$ 个单位时间内从当前位置，移动到 $(x+1,y),(x,y+1),(x-1,y),(x,y-1)$ 中的任意一个。

特别的，还有一些不能移动到的要求：

- 不能移动到墙壁（`#`）所在的地方。

- 移动到计算机所在地之后立刻拿上电脑，不用考虑此动作所花的时间。

- 到达家的门口时，如果此时没有拿上笔记本电脑，那么什么也不会发生。

请求出拿上电脑并到达门口的所花的最短时间。

![](https://cdn.luogu.org/upload/pic/23163.png)

## 说明/提示

对于 $100\%$ 的数据，$5\le n\le 500$，$5\le m\le 500$。

保证数据中墙壁围成了一个封闭图形。 

保证每行的首字符与末字符都为 `#`。

翻译 by @[159号程序员](https://www.luogu.com.cn/user/334586)

# 题解

## 作者：zoobidubi (赞：6)

这题的主要思路是

## 广搜

- 我们知道，这个人在家中走，有两个必经之路，一个是笔记本电脑位置，一个是门，这两段路都要使得路程最短。

- 我拿到这题第一思路是，在广搜时弄一个标记，记下这段走的路程中有没有覆盖这两个必经之点，并且先覆盖的是电脑，有的话输出最短步数即可

- 可是打完后才发现这种做法白白浪费掉好多空间，而且代码实现也不是很容易，可读性也会很差

怎么办呢？
get正解：

- ### 既然两个点都是要走过的，

### 1. 设这个第一个必经之点为另外一个广搜入口，
### 2. 算两遍广搜出来的最短距离之和，不就是总路程的最短距离之和吗

这是本题的突破口，理解了这个地方，剩下的地方都套模板了

还有个坑点
### 搜第二遍时q数组一定一定要清0！！！

代码中有具体注释

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[2000101][5], n, m, sxx, syy, cxx, cyy, gxx, gyy;
//手打队列时，队列一定要开到2*N*N,我保险起见N开大一倍，队列也要跟着变大
int dx[5] = {0, 1, 0, -1, 0}, dy[5] = {0, 0, 1, 0, -1};
char a[1010][1011];//字符类型的a，定bool类型也可以，但是那几个字母都是真，只有#为假
bool f[1001][1010];//用来判断有没有走过的
string s;
int ans;
int bfs(int fx, int fy, int tx, int ty)
{
    memset(q, 0, sizeof(q));
    memset(f, 0, sizeof(f));//q数组一定要初始化0！！！
    q[1][1] = fx, q[1][2] = fy;//起点入队
    int fl = 0, re = 1;//头尾指针初始化
    while (fl <= re)//也可以把fl++打在后面，不挂等号
    {
        fl ++;//队头扩展一个
        if (q[fl][1] == tx && q[fl][2] == ty)
            return q[fl][3];
   //如果这个位置到达了目标点，就返回到这个点需要的步数
   //ps：一定要把这句话打在外面，不能打在下面的if里面，不然会死循环无输出（我也不知道为啥QwQ）         
        for (int i = 1; i <= 4; i ++)
        {
            int cx = q[fl][1] + dx[i];
            int cy = q[fl][2] + dy[i];
            if (a[cx][cy] != '#' && !f[cx][cy]&&cx >= 1&&cx <= n && cy >= 1 &&cy <= m)//如果这个位置不是墙，并且没有超界，还没有走过
            {
                re ++;
                q[re][1] = cx;
                q[re][2] = cy;//尾指针扩展一个
                f[cx][cy] = 1;//设成走过
                q[re][3] = q[fl][3] + 1;
                //新扩展到这个点的步数
                //等于上个点到这里的步数加一
            }
        }
    }
    return 0;//如果while循环都结束了，还没有到达目标点，就返回0
    //这里不用考虑返回-1，因为如果走到的话，步数不可能为0，所以不会冲突
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
    {
        cin >> s;
        for (int j = 0 ; j < s.size(); j ++)
        {
            if (s[j] == 'S') sxx = i, syy = j + 1, a[i][j+1] = s[j];
            else if (s[j] == '.') a[i][j+1] = s[j];
            else if (s[j] == '#') a[i][j+1] = s[j];
            else if (s[j] == 'C') cxx = i, cyy = j + 1, a[i][j+1] = s[j];
            else if (s[j] == 'G') gxx = i, gyy = j + 1, a[i][j+1] = s[j];
        }//把三个特殊点的位置记录下来，把图存下来
    }
    int z1 = bfs(sxx, syy, cxx, cyy), z2 = bfs(cxx, cyy, gxx, gyy);//z1是房间到笔记本的位置，z2是笔记本到门的位置
    if (z1 == 0 || z2 == 0)//如果这些有一个无法到达的话
    {
    	cout << -1  <<endl;//就输出-1
      //ps:AT的题目一定要换行！！！
    	return 0;//直接结束
    }
    cout << z1+z2<<endl;//否则输出最短距离和，换行
return 0;
}

```



---

## 作者：朦胧细雨 (赞：4)

此题为非常标准的广搜~~因为出现了地图~~；

这里展示的是**结构体加队列**。~~因为懒所以用结构体了~~
***
由题目可以得知，主角必须要先拿到电脑才能逃离(~~不拿电脑就无法生存~~)。

所以我们可以**先以电脑为终点，再以门为终点**进行**两次广搜**。
***
不多说了，上代码，为了增强可读性，这里不展示头文件，我尽量使用英文变量名(~~英语太菜了~~)。
```cpp
#define ll long long
using namespace std;
ll n,m;
int sx,sy;//起点坐标（start） 
int mx,my;//中点（电脑）坐标（middle） 
int fx,fy;//终点（门口）坐标（finish） 

int kx[4]={-1,1,0,0};
int ky[4]={0,0,-1,1};

char home[510][510];//家里的地图 
bool flag,vis[510][510];
//vis->visit访问标记，flag标记拿过了电脑 

struct ppx{
	int x,y,time_;
}step,t;//step用来记录(坐标，时间)，而t作为辅助记录step。

queue<ppx> q;

int main()
{
//	freopen("AT168.txt","r",stdin);
//调试骚操作，这样就可以不用每次都输入了
	scanf("%lld%lld",&n,&m); 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>home[i][j];
			if(home[i][j]=='S')//找起点 
			{
				sx=i;sy=j;
			}
			if(home[i][j]=='C')//找电脑 
			{
				mx=i;my=j;
			}
			if(home[i][j]=='G')//找门 
			{
				fx=i;fy=j;
			}
		}
	}
	step.x=sx;step.y=sy;step.time_=0;
	vis[sx][sy]=1;//这里起点一定要标记 
	q.push(step);
	while(!q.empty())
	{
		step=q.front();
		q.pop();
		if(step.x==mx&&step.y==my)
		{
			flag=1;//拿到电脑;
			break;
		}
		for(int i=0;i<4;i++)
		{
			int tx=step.x+kx[i];
			int ty=step.y+ky[i];
			if(tx>0&&tx<=n&&ty>0&&ty<=m&&home[tx][ty]!='#'&&vis[tx][ty]==0)
			{
				t.x=tx;t.y=ty;t.time_=step.time_+1;
				vis[tx][ty]=1;
				q.push(t);
			}
		}
	}
	if(flag==0)
	{
		printf("-1\n");
		return 0;
	}
	while(!q.empty())
	{
		q.pop();
	}
	step.x=mx;step.y=my;
	memset(vis,0,sizeof(vis));
	//一定要初始化，不能拿了电脑断了后路（bushi） 
	vis[mx][my]=1;
	//重新标记 
	q.push(step);
	while(!q.empty())
	{
		step=q.front();
		q.pop();
		if(step.x==fx&&step.y==fy)
		{
			printf("%d\n",step.time_);
			return 0;
		}
		for(int i=0;i<4;i++)
		{
			int tx=step.x+kx[i];
			int ty=step.y+ky[i];
			if(tx>0&&tx<=n&&ty>0&&ty<=m&&home[tx][ty]!='#'&&vis[tx][ty]==0)
			{
				t.x=tx;t.y=ty;t.time_=step.time_+1;
				vis[tx][ty]=1;
				q.push(t);
			}
		}
	}
	printf("-1\n");
	return 0;
}


```
***
[AT168 自宅からの脱出（原址）](https://atcoder.jp/contests/wupc2012/tasks/wupc2012_3)\
[这里有一道进阶版的题](http://noi.openjudge.cn/ch0205/7221/)
***

---

## 作者：名字好难取144 (赞：3)

一看题目，马上想到迷宫问题。


迷宫问题？那不是标标准准的广搜题吗？


这篇文章是我自己写的，我觉得对于**广搜与迷宫问题**讲的还算可以吧
[看文章戳这里！](https://blog.csdn.net/qq_54173335/article/details/118420862?spm=1001.2014.3001.5501)

下面说一下要注意的地方

- 怎么搜索？
  
  很简单，读入地图的时候记录一下房间，笔记本，家门得到位置，按照房间——笔记本，笔记本——门口的顺序搜索即可。（一看就知道要搜索两遍了）
  
- 关于记录路径的数组与队列的清零问题
 
   如果在第一次搜索结束后忘记把**队列**的元素弹出，忘记初始化**路径数组**，我赌一根棒棒糖，绝对会收获**WA**。
   
- 判断是否能拿走电脑并离开家

   我们只需要开一个bool类型的flag来判断是否能完成任务，如果**能**，将flag变成**1**,如果不能，就不改变。（具体如何实现可以看代码）
   
   
## 小优化   

题目说四周都是墙壁，我们只需要搜索$1<x<n$,$1<y<m$大小的地方就可以了

# 代码

~~千万别复制粘贴。。。~~


```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;

struct node{
	int x,y,sum;
};

int cx[4]={0,0,1,-1};
int cy[4]={1,-1,0,0};
char a[1001][1001];
bool vis[1001][1001];

queue<node> q;

int n,m;
int x1,x2,x3,y1,y2,y3,ans;
bool flag;

void bfs(int sx,int sy,int ex,int ey){
	node t;
	t.x=sx;t.y=sy;t.sum=0;
	vis[t.x][t.y]=1;
	q.push(t);
	while(!q.empty()){
		t=q.front();
		q.pop();
		if(t.x==ex&&t.y==ey){
			ans+=t.sum;
			flag=1;
			return ;
		}
		for(int i=0;i<4;++i){
			int tx=t.x+cx[i];
			int ty=t.y+cy[i];
			if(tx>=2&&tx<n&&ty>=2&&ty<m&&a[tx][ty]!='#'&&vis[tx][ty]==0){
				node tt;
				tt.x=tx; tt.y=ty; tt.sum=t.sum+1;
				vis[tx][ty]=1;
				q.push(tt);
			}
		}
	}
}


int main()
{
	freopen("q.in","r",stdin);  //防抄袭
	freopen("q.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>a[i][j];
			if(a[i][j]=='S'){
				x1=i;y1=j;
				a[i][j]='.';
			}
			else if(a[i][j]=='C'){
				x2=i;y2=j;
				a[i][j]='.';
			}
			else if(a[i][j]=='G'){
				x3=i;y3=j;
				a[i][j]='.';
			}
		}
	}
	bfs(x1,y1,x2,y2);
	if(flag==0) {
		cout<<-1<<endl;
		return 0;
	}
	
	flag=0;
	
	memset(vis,0,sizeof(vis)); //clear 清空队列与标记数组 
	while(!q.empty()) q.pop();
	
	bfs(x2,y2,x3,y3);
	
	if(flag==0) {
		cout<<-1<<endl;
		return 0;
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：Max_s_xaM (赞：2)

# AT168 【自宅からの脱出】

其他题解都要两次 bfs，但其实只一次 bfs 即可。

显然，**电脑到起点**的最短距离就相当于**起点到电脑**的最短距离。
于是，**起点 -> 电脑 -> 门**就被转化为**电脑 -> 起点 + 电脑 -> 门**。
我们可以以电脑的位置为原点，用一次 bfs 算出**电脑到起点的最短距离**和**电脑到门的最短距离**，两个相加即为答案。

### Code

```cpp
#include <iostream>
#include <queue>
using namespace std;

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int n, m, xs, ys, xc, yc, xg, yg;
char map[510][510];
int dis[510][510];
bool vis[510][510];
queue <pair<int, int> > q;
void bfs()
{
	q.push(make_pair(xc, yc));
	vis[xc][yc] = 1;
	while (!q.empty())
	{
		int x = q.front().first, y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int xx = x + dx[i], yy = y + dy[i];
			if (xx < 1 || xx > n || yy < 1 || yy > m || map[xx][yy] == '#' || vis[xx][yy]) continue;
			dis[xx][yy] = dis[x][y] + 1;
			q.push(make_pair(xx, yy));
			vis[xx][yy] = 1;
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
	{
		cin >> map[i][j];
		if (map[i][j] == 'S') xs = i, ys = j;
		if (map[i][j] == 'C') xc = i, yc = j;
		if (map[i][j] == 'G') xg = i, yg = j;
	}
	bfs();
    // 如果有一个距离为零，则不存在路径
	if (dis[xs][ys] && dis[xg][yg])
	cout << dis[xs][ys] + dis[xg][yg] << endl;
	else cout << -1 << endl;
	return 0;
}

```


---

## 作者：Quan_200605 (赞：1)

看到题解都是数组模拟BFS，没人用STL的

那我就来写一写STL吧

[题目传送门](https://www.luogu.com.cn/problem/AT168)

### sol
题目意思都很清晰吧，分为两个部分：

①从我的房间到电脑

②从电脑到我家的门

求最短距离，很明显用两遍BFS即可，“#”表示障碍（即不能走），“S”表示我的房间，“C”电脑位置，“G”表示我家的门。首先就把S，C，G的位置循环搜出来

然后呢，跑两遍BFS，第一次起点为S，终点为C，第二次起点为C，终点为G。**注意：在第二次开始搜的时候数组一定要清空**

### code
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
typedef long long ll;
using namespace std;
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
inline int rd(){
	int res=0,sign=1;char ch;
	while((ch=getchar())<'0'||ch>'9')if(ch=='-')sign=-1;res=res*10+ch-48;
	while((ch=getchar())>='0'&&ch<='9')res=res*10+ch-48;
	return res*sign;
}
const int maxn=510;
int n,m;//边长 
int dx[5]={0,0,1,-1};
int dy[5]={1,-1,0,0};//方向数组，表示下一步的四个方向 
char mapp[maxn][maxn];//存储我家 
int ans[maxn][maxn];//记录步数 
bool flag[maxn][maxn];//标记是否走过 
int sx,sy,cpx,cpy,ex,ey;//sx、sy表示S（我的房间），cpx、cpy表示C（电脑），ex、ey表示G（我家的门） 
queue<int>q1,q2;//定义队列 
queue<int>qq1,qq2;//因为STL队列不能清空（只有双端队列才能清空），所以定义两个 
void init(){//读入 
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) 
	 for(int j=1;j<=m;j++){
	 	cin>>mapp[i][j];
	 	if(mapp[i][j]=='S') sx=i,sy=j;
	 	if(mapp[i][j]=='C') cpx=i,cpy=j;
	 	if(mapp[i][j]=='G') ex=i,ey=j;//把S、C、G坐标搜出来 
 	} 
} 
int sum=0;
bool used=false,t=false;
void BFS1(){//第一遍BFS，从S到C 
	memset(flag,0,sizeof(flag));
	memset(ans,0,sizeof(ans));
	used=false;
	q1.push(sx),q2.push(sy);
	flag[sx][sy]=1;
	while(!q1.empty()){
		int x=q1.front(),y=q2.front();
		q1.pop(),q2.pop();
		if(x==cpx&&y==cpy){
			sum+=ans[x][y];
			used=1;//如果能到达目的地，标记起来 
		}
		for(int i=0;i<4;i++){
			int xx1=x+dx[i];
			int yy1=y+dy[i];
			if(xx1>=1&&xx1<=n&&yy1>=1&&yy1<=m&&mapp[xx1][yy1]!='#'&&!flag[xx1][yy1]){
				flag[xx1][yy1]=1;
				ans[xx1][yy1]=ans[x][y]+1;
				q1.push(xx1),q2.push(yy1);
			}
		}
		if(used)break;
	}
	if(!used)//如果不能到 ，输出-1 
	 puts("-1"),t=1;
}
void BFS2(){//第二遍BFS，从C到G 
	memset(flag,0,sizeof(flag));
	memset(ans,0,sizeof(ans));
	used=false;
	qq1.push(cpx),qq2.push(cpy);
	flag[cpx][cpy]=1;
	while(!qq1.empty()){
		int x=qq1.front(),y=qq2.front();
		qq1.pop(),qq2.pop();
		if(x==ex&&y==ey){
			sum+=ans[x][y];
			used=1;//同上 
		}
		for(int i=0;i<4;i++){
			int xx1=x+dx[i];
			int yy1=y+dy[i];
			if(xx1>=1&&xx1<=n&&yy1>=1&&yy1<=m&&mapp[xx1][yy1]!='#'&&!flag[xx1][yy1]){
				flag[xx1][yy1]=1;
				ans[xx1][yy1]=ans[x][y]+1;
				qq1.push(xx1),qq2.push(yy1);
			}
		}
		if(used)break;
	}
	if(!used)
	 puts("-1"),t=1;//同上 
}
int main(){
	init();
	BFS1();
	if(t)return 0;//如果不能到就退出程序 
	t=false;
	BFS2();
	if(t)return 0;//同上 
	cout<<sum<<endl;//完美输出 
	return 0;
}

```
总得来说，题目还是比较简单的，就是板子题，细节很多，很容易写错

完结撒花
### [我的博客传送门](https://www.luogu.com.cn/blog/qzw200605/)

---

## 作者：Raw_Aya9285 (赞：1)

**算法：BFS**

这道题的搜索我们可以分成两部分：

1. **从卧室来到电脑**
2. **从电脑来到大门**

所以我们要做的，就是进行两次搜索。

一般的深搜大家都会，但这里我把一些东西放在了函数里方便调用。首先我们把从卧室找到电脑的部分写出来吧：

```cpp
struct node{
    int x;
    int y;
    int step;
}que[250001];  //深搜用结构体
int n,m,sx,sy,fx,fy,p,q;  //sx和sy是起点即卧室，fx和fy是终点即电脑
int tail,head,flag;  //头尾，以及标记
int bk[501][501],w[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
char mup[501][501];  //三个数组分别是：标记是否有走过，走的四个方向，地图
void bfs(){
    tail=1,head=1,flag=0;
    que[tail].x=x;
    que[tail].y=y;
    que[tail].step=1;
    tail++;  //常规初始化
    while(head<tail){
        for(int i=0;i<4;i++){  //遍历四个方向
            p=que[head].x+w[i][0];
            q=que[head].y+w[i][1];
            if(p<1||p>n||q<1||q>m)  continue;  //如果搜出图了不再搜索
            if(mup[p][q]!='#'&&bk[p][q]==0){  //如果不是墙壁且没有走过就可以走
                bk[p][q]=1;
                que[tail].x=p;
                que[tail].y=q;
                que[tail].step=que[head].step+1;
                tail++;  //一些简单的设置
            }
            if(p==fx&&q==fy){  //如果搜到了就退出吧
                flag=1;  //标记一下
                break;
            }
        }
        if(flag==1){
            break;
        }
        head++;
    }
    if(flag==0){  //如果无论如何都不能走到就输出-1
        cout<<-1<<endl;
    }
    return;
}
```

这一部分我们就打完了。下面我们要处理从电脑到家门的搜索。

其实两个搜索都一样，但起点和终点不一样，所以我们在函数里定义起点和终点变量，到时候再直接从外部调用：

```void bfs(int x,int y,int fx,int fy)```

然后就一切大吉啦，代码如下：

```cpp
struct node{
    int x;
    int y;
    int step;
}que[250001];  //同上
int n,m,sx,sy,mx,my,ex,ey,p,q;  //分别是卧室、电脑和大门的坐标，其他同上
int tail,head,flag;
int bk[501][501],w[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
char mup[501][501];  //同上
void bfs(int x,int y,int fx,int fy){  //这样方便调用
    tail=1,head=1,flag=0;
    que[tail].x=x;
    que[tail].y=y;
    que[tail].step=1;
    tail++;
    while(head<tail){
        for(int i=0;i<4;i++){
            p=que[head].x+w[i][0];
            q=que[head].y+w[i][1];
            if(p<1||p>n||q<1||q>m)  continue;
            if(mup[p][q]!='#'&&bk[p][q]==0){
                bk[p][q]=1;
                que[tail].x=p;
                que[tail].y=q;
                que[tail].step=que[head].step+1;
                tail++;
            }
            if(p==fx&&q==fy){
                flag=1;
                break;
            }
        }
        if(flag==1){
            break;
        }
        head++;
    }
    if(flag==0){
        cout<<-1<<endl;
    }
    return;  //一直到这里都和上一个代码一样，不多做解释
}
int main(){
    int ans=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mup[i][j];
            if(mup[i][j]=='S'){
            	sx=i;sy=j;
            }else if(mup[i][j]=='C'){
                mx=i;my=j;
            }else if(mup[i][j]=='G'){
                ex=i;ey=j;
            }  //循环输入，顺便分别记录三个重要位置的坐标
        }
    }
    bfs(sx,sy,mx,my);  //第一次搜索
    if(flag==0)  return 0;  //如果已经失败了，就return 0，因为函数里面已经输出-1了
    ans+=que[tail-1].step-1;  //统计第一次的步数
    bfs(mx,my,ex,ey);  //第二次搜索
    if(flag==0)  return 0;
    ans+=que[tail-1].step-1;  //同第一次
    cout<<ans<<endl;  //输出
    return 0;
}
```

然后你就会愉快地...... ~~AC~~ 爆零！！

为什么呢？不是明明两次搜索都写的很好吗？

那是因为......

**BK数组没有初始化！QwQ**

淦一下初始化，愉快搞定AC！

（为了防止抄袭我就不贴完整代码啦）

---

## 作者：wssdl (赞：0)

**双倍经验： [P5195](https://www.luogu.com.cn/problem/P5195)**

## 题目大意

给你一个 $n\times m$ 的矩阵，你要从初始位置 S ，走到目标位置 G ，而且走到 G 时，必须拿到电脑，换句话说，必须经过点 C ，每次走可以往上下左右走，每走一步花费 $1$ 的时间，不能走到 # ，问拿上电脑并到达门口的所花的最短时间，如果不能完成，输出 $-1$ 。

## 解题思路

- 这是一道不错的 **广搜题** ，建议管理员大大们加个 **广搜** 的标签。

- 由于数据范围，深搜估计会超时，而且题目询问最短时间，于是果断 **广搜** ~~貌似上面讲了~~ 。

- 我们知道要从起点走到终点，所以我们可以把起点与终点的位置标出来，然后打个广搜模板，其中，我们为了不重复走，我们可以用个布尔数组，开成二维，第一维表示行，第二维表示列，值为 $1$ 为走过，值为 $0$ 为没有走过，但是题目有一个很恶心的地方：走到目标点是必须带上电脑，否则没用，在普通 BFS 中，是一定不能往回走的，但这题可以，可以看看第二个样例，那可怎么办呢？因为和回走有关系，所以我们可以在布尔数组上动手脚，我们再往后加一维，开到 $2$ ，不用担心暴空间的问题，这一维 $1$ 表示拿了电脑后走没走， $0$ 表示没拿电脑时走没走，这样问题就解决了，无解时，由于我们写了函数，那如果有答案并输出后函数肯定会结束，没结束的话不就是无解吗，我们在最后输出即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 10;
int n, m;
int sx, sy;
int fx, fy;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
char a[N][N];
bool vis[N][N][2];  //改变数组
struct Node {
  int x, y, s;
  bool b;
};
int bfs(int x, int y, int s, int b) {
  queue<Node> q;
  Node cur = {x, y, s, b};
  q.push(cur);
  vis[x][y][b] = 1;
  while (!q.empty()) {
    Node cur = q.front();
    q.pop();
    if (cur.x == fx && cur.y == fy && cur.b) {  //必须拿到电脑
      return cur.s;
    }
    if (a[cur.x][cur.y] == 'C') {  //是电脑赶紧拿
      cur.b = 1;
    }
    for (int i = 0; i <= 3; i++) {  //四个方向
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && a[nx][ny] != '#' && !vis[nx][ny][cur.b]) {  //判断是否可以走
        vis[nx][ny][cur.b] = 1;
        Node ne = {nx, ny, cur.s + 1, cur.b};
        q.push(ne);
      }
    }
  }
  return -1;  //无解
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == 'S') {  //起点与终点
        sx = i;
        sy = j;
      }
      if (a[i][j] == 'G') {
        fx = i;
        fy = j;
      }
    }
  }
  cout << bfs(sx, sy, 0, 0) << endl;
  return 0;
}
```

求通过，~~其实更恶心的地方是要输出换行……~~

---

## 作者：1lgorithm (赞：0)

### 这个题可以说是一道裸的广搜了！

这道题让我们搜两遍，所以我们可以用函数实现（实际上是我懒）

在函数里实现就要注意一点：数组要归零！！

但是如果我们把vis数组和队列定义在函数里面，就不用操心了。

代码：

```cpp
#include<iostream>
#include<queue>
using namespace std;
int a[501][501],n,m,sx1,sx2,sy1,sy2,ex1,ex2,ey1,ey2;
char c;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int bfs(int sx,int sy,int ex,int ey){	
	int ans[501][501]={0},vis[501][501]={0};
	queue <int> quex,quey;
	vis[sx][sy]=1;
	quex.push(sx),quey.push(sy);
	while(quex.size()){
		int x=quex.front(),y=quey.front();
		quex.pop(),quey.pop();
		if(x==ex&&y==ey){
			return ans[x][y];
		}
		for(int i=0;i<4;i++){
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<=0||yy<=0||xx>=n||yy>=m) continue;
			if(vis[xx][yy]==0&&a[xx][yy]==0){
				ans[xx][yy]=ans[x][y]+1;
				vis[xx][yy]=1;
				quex.push(xx);
				quey.push(yy);
			}
		}
	}
	return -1;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='#') a[i][j]=1;
			if(c=='S') sx1=i,sy1=j;
			if(c=='C') sx2=i,sy2=j,ex1=i,ey1=j;
			if(c=='G') ex2=i,ey2=j;
		}
	}
	int length1=bfs(sx1,sy1,ex1,ey1),length2=bfs(sx2,sy2,ex2,ey2);
	if(length1==-1||length2==-1){
		cout<<"-1"<<endl;
	}
	else{
		cout<<length1+length2<<endl;
	}
}
```




---

## 作者：AveMarina (赞：0)

## BFS求两次最短距离
### 考虑下如何使所走路径最短
如果走到电脑的距离最短且走到终点的距离最短那么这不就是满足题意的最短距离吗？

但是一次广搜能保证我们得到的距离最短吗？答案是不能。

考虑下数学里的两点间最短距离的定义：__两点之间直线距离最短__。而这个题目要我们求的却是 __起点->电脑->终点__ 的最短距离，也就是说我们要求 __三个点的最短距离。__所以一次BFS是无法得到最短距离的。__~~如果三个点正好在一条线上是可以的~~

所以我们可以考虑 __令起点->电脑距离最短，电脑->终点距离最短__，这两个距离之和就是总的最短距离了。

另外要注意清空访问标记数组，不然很可能在第二次BFS时出现“不能从电脑走到门的情况”
```cpp
#include <iostream>
#include <cstring>
using namespace std;

// 两次BFS，一次求从起点到电脑的距离，一次求电脑到终点的距离... 

const int N = 510;
struct Pos {
	int x, y, step;
	Pos(int x, int y, int step) : x(x), y(y), step(step) {};
	Pos() {};
};
char graph[N][N];
int n, m;
int sx, sy, ex, ey, cx, cy;
Pos que[N * N];
int mv[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool visited[N][N];
int bfs(int bsx, int bsy, int bex, int bey) {
	memset(visited, 0, sizeof visited);
	int qtop = 0, qback = 0;
	que[qtop] = Pos(bsx, bsy, 0);
	while (qtop <= qback) {
		Pos now = que[qtop++];
		if (now.x == bex && now.y == bey) return now.step;
		for (int i = 0; i < 4; i++) {
			int nx = now.x + mv[i][0], ny = now.y + mv[i][1];
			if (nx > n || ny < 1 || ny > m || ny < 1) continue;
			// 考虑到地图会被用两次，这里就开了个visited标记访问 
			if (visited[nx][ny] || graph[nx][ny] == '#') continue;
			visited[nx][ny] = true;
			que[++qback] = Pos(nx, ny, now.step + 1);
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> graph[i][j];
			if (graph[i][j] == 'S') sx = i, sy = j;
			if (graph[i][j] == 'C') cx = i, cy = j;
			if (graph[i][j] == 'G') ex = i, ey = j;
		}
	} 
	// 为了提升效率所以这两个bfs分开调用 
	int r1 = bfs(sx, sy, cx, cy);
	if (r1 == -1) {
		cout << -1 << endl;
		return 0;
	}
	int r2 = bfs(cx, cy, ex, ey);
	if (r2 == -1) {
		cout << -1 << endl;
		return 0;
	}
	cout << r1 + r2 << endl;
	return 0;
}
```

---

## 作者：Perseis (赞：0)

经典的**bfs**模版

唯一不同的大概就是需要两次bfs

一次是从我的房间到笔记本电脑

第二次是从笔记本电脑到房门

话不多说上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char ma[600][600];
int n,m,f[600][600],b,c,d,e,ans,dx[4] = {1,0,-1,0},dy[4]={0,1,0,-1},fa,fd,g;
inline bool okk(int x,int y)
{
    if(x>=1&&x<n+1&&y>=1&&y<m+1) return true;
    else return false;
}
struct node
{
    int x,y,step;
}a[1000000];
int bfs(int c,int d,int e,int b)
{
    f[c][d] = 1;
    int fr = 0,tail = 1;
    a[1].step = 0;
    a[1].x = c;
    a[1].y = d;
    while(fr<=tail)//手写队列
    {
        node k = a[++fr];
        if(k.x == e && k.y == b) return k.step;
        for(register int i = 0;i<4;i++)
        {
            int nx = k.x+dx[i];
            int ny = k.y+dy[i];
            if(okk(nx,ny)&&ma[nx][ny]!='#'&&!f[nx][ny])
            {
                tail++;
                a[tail].x = nx;
                a[tail].y = ny;
                a[tail].step = k.step+1;
                f[nx][ny] = 1;
            }
        }
    }
    return 0;//走不到的情况
}
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i =1;i<=n;i++) for(register int j = 1;j<=m;j++)
    {
        cin>>ma[i][j];
        if(ma[i][j] == 'S')//记录我的房间位置
        {
            b = i;
            c = j;
        }
        if(ma[i][j] == 'C')//记录笔记本位置
        {
            d = i;
            e = j;
        }
        if(ma[i][j] == 'G')//记录房门位置
        {
            fd = i;
            g = j;
        }
    }
    int t = bfs(b,c,d,e);
    if(t) ans += t;//从我的房间到笔记本
    else//走不到
    {
        cout<<"-1"<<endl;
        return 0;
    }
    memset(f,0,sizeof(f));//清零走过的标记
    t = bfs(d,e,fd,g);
    if(t) ans += t;//从笔记本到房门
    else//走不到
    {
        cout<<"-1"<<endl;
        return 0;
    }
    cout<<ans<<endl;//结果
    return 0;
}

```

---

