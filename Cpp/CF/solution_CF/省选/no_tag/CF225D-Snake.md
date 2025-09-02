# Snake

## 题目描述

Let us remind you the rules of a very popular game called "Snake" (or sometimes "Boa", "Python" or "Worm").

The game field is represented by an $ n×m $ rectangular table. Some squares of the field are considered impassable (walls), all other squares of the fields are passable.

You control a snake, the snake consists of segments. Each segment takes up exactly one passable square of the field, but any passable square contains at most one segment. All segments are indexed by integers from $ 1 $ to $ k $ , where $ k $ is the snake's length. The $ 1 $ -th segment is the head and the $ k $ -th segment is the tail. For any $ i $ ( $ 1<=i&lt;k $ ), segments with indexes $ i $ and $ i+1 $ are located in the adjacent squares of the field, that is, these squares share a common side.

One of the passable field squares contains an apple. The snake's aim is to reach the apple and eat it (that is, to position its head in the square with the apple).

The snake moves throughout the game. During one move the snake can move its head to an adjacent field square. All other segments follow the head. That is, each segment number $ i $ $ (1&lt;i<=k) $ moves to the square that has just had segment number $ i-1 $ . Consider that all segments including the head move simultaneously (see the second test sample). If the snake's head moves to an unpassable square or to the square, occupied by its other segment, the snake dies. That's why we will consider such moves unvalid.

Your task is to determine the minimum number of valid moves that the snake needs to reach the apple.

## 样例 #1

### 输入

```
4 5
##...
..1#@
432#.
...#.
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 4
#78#
.612
.543
..@.
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3 2
3@
2#
1#
```

### 输出

```
-1
```

# 题解

## 作者：flyfree (赞：13)

看到地图和最少几步，首先想到bfs。

这题的难点，应该是状态的表示。我的思路是记录蛇头也就是1的位置，后边蛇的身子每一节用一个0-3之间的整数表示，分别代表当前这一节在上一节的上、下、左、右。

如果把这一串数看作10进制，那么最大有8位，显然开不了数组，没法去重。所以会想到把它看作一个4进制数，这样最大只有65535，就能顺利的开数组，而且刚好可以借助位运算完成一些操作。

一些细节：

1、每次取出队首都要更新当前蛇的状态，注意蛇尾可以看作空地。

2、我个人不习惯用STL的队列，就粗略计算了一下f数组的大小，也就是最多有多少种情况，大概就是15* 15* 4* 3^7。为什么是3^7*4而不是65535呢，可以想一下，如果前一节确定下来，那么当前这一节其实只有3种选择而非4种，这样可以大大节省空间。

当然，事实上可以开的更小，还有一些不合法的情况。但是由于本蒟蒻实在水平有限，就只能压到这了。

上代码~（绝对原创）

```
#include <cstdio>
using namespace std;
struct node
{int x,y,body,step;}f[1968301];
bool vi[16][16][65536];
int m,n,stx,sty,ans=-1,dis,q=1;
int mx[4]={-1,1,0,0},my[4]={0,0,-1,1};
char a[16][16];
void read(int p)
{	char x=' ';
	while(x=='\n'||x=='\r'||x==' ')
	x=getchar();
	for(int i=1;i<=n;i++)
	{	a[p][i]=x;
		if(x=='1')
		{	f[1].x=p;f[1].y=i;}//记录蛇头位置
		if(x>='1'&&x<='9'&&x-'0'>dis)
		dis=x-'0';//记录蛇的长度
		x=getchar();
	}
}
void build()//节数从小到大压缩，可以类比十进制
{	int lastx=f[1].x,lasty=f[1].y,x,y;
	for(int i=2;i<=dis;i++)
	{	for(int j=0;j<4;j++)
		{	x=lastx+mx[j];
			y=lasty+my[j];
			if(a[x][y]=='0'+i)
			{	f[1].body*=4;
				f[1].body+=j;
				lastx=x;lasty=y;
				break;
			}
		}
	}
}
void update(int num)//每次都要更新蛇的状态，更新前写清除之前的
{	int x=f[num].x,y=f[num].y,p=f[num].body,z=q;
	int xx;
	for(int i=1;i<=m;i++)
	for(int j=1;j<=n;j++)
	if(a[i][j]>='1'&&a[i][j]<='9')
	a[i][j]='.';
	for(int i=1;i<=dis;i++)
	{	a[x][y]='0'+i;
		if(p&&z)
		xx=p/z;
		else xx=0;
		x+=mx[xx];y+=my[xx];
		if(p&&z)
		p=p%z;
		if(z)
		z/=4;
	}
}
void output()//调试用的，并没有什么用。每次输出一下整张地图，非常直观
{	for(int i=1;i<=m;i++)
	{	for(int j=1;j<=n;j++)
		printf("%c",a[i][j]);
		printf("\n");
	}
	printf("\n");
}
void bfs()
{	int l=1,r=2,x,y,z;
	build();
	vi[f[1].x][f[1].y][f[1].body]=true;
	while(l<r)
	{	update(l);
//		output();
		for(int i=0;i<4;i++)
		{	x=f[l].x+mx[i];
			y=f[l].y+my[i];
			if(x<1||x>m||y<1||y>n) continue;
			if(a[x][y]=='#') continue;
			if(a[x][y]>='1'&&a[x][y]<'0'+dis)
			continue; 
			if(a[x][y]=='@')
			{	ans=f[l].step+1;return;}
			z=f[l].body/4;
			z+=(i^1)*q;//如果蛇头向上走，2号就在1号的下面
        //依此类推，方向都是反着的，所以要异或一下
			if(vi[x][y][z]) continue;
			vi[x][y][z]=true;
			f[r].x=x;f[r].y=y;
			f[r].step=f[l].step+1;
			f[r].body=z;
			r++;
		}
		l++;
	}
}
int main()
{	scanf("%d %d",&m,&n);
	for(int i=1;i<=m;i++)
	read(i);
	for(int i=2;i<dis;i++)
	q*=4;
   //q的作用可以类比十进制理解一下，由于我的状态压缩是序号从小到大，而每次更新的都是最小的2号，所以需要乘一下q
	bfs();
	printf("%d",ans);
	return 0;
}
```

这样就可以A了，但是感觉这个代码跑得有点慢，于是瞄了一下rk1的代码，比着做了一些优化，大体思路不变，时间就从4.09m变成了2.15m，空间不变（%%%dalao)

优化：

1、初始状态的build函数改为递归形式，状态由原来的序号从小到大变成了从大到小。好处是后续修改第2节的值的时候可以全部依靠位运算，避免了*q；更新的update也可以简洁很多，完全依靠位运算

2、更新蛇的状态的时候，事实上每个点上是蛇的第几节并不重要，重要的是有没有蛇，所以之前完全还原蛇身是不必要的，只要开一个bool数组记录是否有就行了。这样判断起来会更加简单。

代码2.0

```
#include <cstdio>
using namespace std;
struct node
{int x,y,body,step;}f[1968301];
bool vi[16][16][65536],use[16][16];
int m,n,stx,sty,ans=-1,dis,q;
int mx[4]={-1,1,0,0},my[4]={0,0,-1,1};
char a[16][16];
void read(int p)
{	char x=' ';
	while(x=='\n'||x=='\r'||x==' ')
	x=getchar();
	for(int i=1;i<=n;i++)
	{	a[p][i]=x;
		if(x=='1')
		{	f[1].x=p;f[1].y=i;}
		if(x>='1'&&x<='9'&&x-'0'>dis)
		dis=x-'0';
		x=getchar();
	}
}
int build(int lx,int ly,char p)
{	int x,y;
	for(int i=0;i<4;i++)
	{	x=lx+mx[i];y=ly+my[i];
		if(x<1||x>m||y<1||y>n) continue;
		if(a[x][y]==p)
		return (build(x,y,p+1)<<2)|i;
	}
	return 0;
}
void update(int num,bool v)
{	int x=f[num].x,y=f[num].y,z=f[num].body,p;
	for(int i=1;i<dis;i++)
	{	use[x][y]=v;
		p=z&3;z>>=2;
		x+=mx[p];y+=my[p];
	}
}
void output()
{	for(int i=1;i<=m;i++)
	{	for(int j=1;j<=n;j++)
		printf("%d",use[i][j]);
		printf("\n");
	}
	printf("\n");
}
void bfs()
{	int l=1,r=2,x,y,z;
	f[1].body=build(f[1].x,f[1].y,'2');
	vi[f[1].x][f[1].y][f[1].body]=true;
	while(l<r)
	{	update(l,1);//更新蛇的状态
//		output();
		for(int i=0;i<4;i++)
		{	x=f[l].x+mx[i];
			y=f[l].y+my[i];
			if(x<1||x>m||y<1||y>n) continue;
			if(a[x][y]=='#') continue;
			if(use[x][y]) continue; //新的update带来的便利
			if(a[x][y]=='@')
			{	ans=f[l].step+1;return;}
			z=f[l].body<<2;
			z&=q;//左移后事实上蛇尾的状态已经没用了，需要用q去除
			z|=i^1;
			if(vi[x][y][z]) continue;
			vi[x][y][z]=true;
			f[r].x=x;f[r].y=y;
			f[r].step=f[l].step+1;
			f[r].body=z;
			r++;
		}
		update(l,0);l++;//还原蛇的状态
	}
}
int main()
{	scanf("%d %d",&m,&n);
	for(int i=1;i<=m;i++)
	read(i);
	q=(1<<(2*dis-2))-1;//为了去除多余的状态
	bfs();
	printf("%d",ans);
	return 0;
}
```

完结撒花~

---

## 作者：SnowTrace (赞：4)

看到本题数据范围，发现非常非常小。

于是第一个想法就是在队列里套字符串，进行宽搜。

具体是这样的：

一个数组储存蛇的头到尾的所有元素，循环先写出最初状态的数组，让初始状态进队，然后用 map 记录这种数组的情况是否已经出现过，如果出现过就不再延申进队。

然后题中写明蛇不能走到自己的身体上

（注意尾巴处是可以走过的，因为在头走过去的时候尾巴也动了）

那我们就可以将蛇的身体部分全部变为障碍，最后再恢复成原来的样子。

（指 while 循环中的一次循环干一遍这个事情）

（这样写的话还需要注意一开始的地图中的蛇需要去掉全部变成点）

其它情况，就按正常的宽搜模板写就可以了。

（四大要素： 队列，判边界，判是否访问过，判是否是终点坐标）

值得注意的一个小点： 准备将元素入队的时候，要将原来储存蛇的位置修改一下，删掉最后一位，然后在第一位插入目前的坐标。

这边还有一个问题，如果写 int 类型的数组，内存可能会炸。

看到数据范围 $15*15 = 225$

于是我们用 unsigned char 类型可以直接存。

最后 codeforces 2200 的题就被水完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
// 本程序还写了一个二维压一维的数组进行节省空间
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
//宽搜方向
char a[100][100];
//地图
int n,m;
vector<unsigned char>snake;
//存初始的蛇的所有点的位置（按顺序1到最后）
map<vector<unsigned char>,bool>mp;
void find_snake(int sx,int sy){//一开始的找蛇
	snake.push_back(sx*16+sy);
	char now = '1';
	int nx = sx,ny = sy;
	while(1){
		bool ok =0;
		if(now == '9')break;
		for(int i =0;i<4;i++){
			int x1 = nx+dx[i],y1 = ny+dy[i];
			if(a[x1][y1] == now+1){
				a[x1][y1] = '.';
				now+=1;
				nx = x1,ny = y1;
				ok = 1;
				snake.push_back(x1*16+y1);
				break;
			}
		}if(!ok)break;
	}
}
queue<pair<vector<unsigned char>,int> >q;
inline bool check(int x2,int y2){
	if(x2<1 or x2>n or y2<1 or y2>m or a[x2][y2] == '#')return false;
	return true;
}
int bfs(){
	q.push(make_pair(snake,(int)0));
	mp[snake] = true;
	while(!q.empty()){
		vector<unsigned char>e = q.front().first;
		if(a[(int)e[0]/16][(int)e[0]%16] == '@'){
			return q.front().second;
        //看是否访问到答案
		}
		vector<unsigned char>ee = e;
		for(int i = 1;i<e.size()-1;i++){
			a[(int)e[i]/16][(int)e[i]%16] = '#';	
        //将蛇的身体部分设置为无法访问区
        //其中循环的开始点和结束点不包含蛇头和蛇尾
		}for(int i =0;i<4;i++){
			int x1 = (int)e[0]/16+dx[i],y1 = (int)e[0]%16+dy[i];
			ee = e;
			ee.pop_back();
			ee.insert(ee.begin(),x1*16+y1);
			if(check(x1,y1) and !mp[ee]){
				mp[ee] = true;
				q.push(make_pair(ee,q.front().second+1));	
			}
		}
		for(int i = 1;i<e.size()-1;i++){
			a[(int)e[i]/16][(int)e[i]%16] = '.';
		}
	q.pop();}
	return -1;
}//宽搜
int main(){
	cin >> n >> m;
	int sx,sy;
	for(int i =1;i<=n;i++){
		for(int j =1;j<=m;j++){
			cin >> a[i][j];
			if(a[i][j] == '1'){
				sx = i,sy = j;
			}
		}
	}find_snake(sx,sy);
	cout << bfs() << endl;
	return 0;
}//紫题做完了！！！
```






---

## 作者：I_will_AKIOI (赞：1)

今日兔群每日任务，我竟然不看题解切出紫！

求最少步数很容易想到是 BFS。

首先先预处理出蛇身的位置，我们遍历数组，是数字就记录下来坐标，最后对数组排序，坐标对应的数字小的在前。

接下来 BFS。对每个节点开两个数组，记录蛇身体的坐标，然后暴力扩展答案。如果你不判重，就会获得 [MLE](https://codeforces.com/contest/225/submission/256593556)。

所以接下来我们用 map 判重，但是由于扩展节点和 map 的常数过大，会获得 [TLE](https://codeforces.com/contest/225/submission/256600412)。

接下来开始优化。首先我们发现要在开两个数组记录坐标，一个 `int` 记录一个 $\le15$ 的数，未免有些浪费。所以我们先压位，把二维变一维，用一个 `int` 表示坐标。**将左上角标为 $0$**，对于点 $(x,y)$，则压位后坐标为 $z=x\times m+y$。压位后怎么还原为原来的 $(x,y)$？很简单，$x=\displaystyle\left\lfloor\frac{z}{m}\right\rfloor,y=z\bmod m$。

虽然常数小了一半，但是还是过不去。这时候我们可以使用哈希，用 bitset 存，效率大大提升，就可以 AC 了。同时你还可以开一下 O3，由于数据较小，可以把 `int` 变成 `short`，进一步提升效率。

```
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
struct Data
{
  vector<short>v;
  short s;
}w;
short n,m,fx[4]={0,1,0,-1},fy[4]={1,0,-1,0};
char c[15][15];
queue<Data>q;
bitset<100000007>vis;
bool cmp(short x,short y){return c[x/m][x%m]<c[y/m][y%m];}
bool check(vector<short>&v,short x,short y)//判断蛇身是否重叠
{
  for(int i=0;i<v.size()-1;i++) if(v[i]/m==x&&v[i]%m==y) return 1;
  return 0;
}
int Hash(vector<short>&v)//哈希
{
	int res=0;
	for(int i=0;i<v.size();i++) res=((long long)res*13331+v[i])%100000007;
	return res;
}
short bfs()
{
  q.push(w);
  vis[Hash(w.v)]=1;
  while(!q.empty())
  {
    w=q.front();
    if(c[w.v[0]/m][w.v[0]%m]=='@') return w.s;
    for(int i=0;i<4;i++)
    {
      short nx=w.v[0]/m+fx[i],ny=w.v[0]%m+fy[i];
      if(nx<0||nx>=n||ny<0||ny>=m||c[nx][ny]=='#') continue;
      if(check(w.v,nx,ny)) continue;
      vector<short>v;
      v.push_back(nx*m+ny);
      for(int j=0;j<w.v.size()-1;j++) v.push_back(w.v[j]);
      int now=Hash(v);
      if(vis[now]==0) vis[now]=1,q.push(Data{v,w.s+1});
    }
    q.pop();
  }
  return -1;
}
int main()
{
  ios::sync_with_stdio(0);
  cin>>n>>m;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      cin>>c[i][j];
      if(c[i][j]>='1'&&c[i][j]<='9') w.v.push_back(i*m+j);//把是数字的坐标加入
    }
  }
  sort(w.v.begin(),w.v.end(),cmp);//把蛇身排序
  cout<<bfs();
  return 0;
}
```

---

## 作者：Y2y7m (赞：1)

感觉这题的状态压缩很有意思。

看到又是字符图迷宫，于是想到他的经典做法：广搜。

但是题目中要求“蛇”的身体不能重叠，所以，我们需要将这个“蛇”压缩进状态中，且 ```vis``` 数组中也需要有“蛇”的状态。

如果我们直接暴力压缩，将“蛇”的每一节都存进状态中，状态数过多，空间炸飞。

考虑到“蛇”是连续的，所以我们不需要存下这条“蛇”每个点的位置，只需要记下它的形状即可，也就是记下这条蛇第 $i+1$ 节在第 $i$ 节的哪个方向即可（只有上下左右四种情况）。

让我们算一下空间：极限情况下是 $4^{8}\times 15\times 15$ 个 ```bool```，正好开的下，如果想优化空间的话应该可以优化到 $3^8\times 15\times 15$，但是没必要，这样也不好写。

具体实现方面的细节可以看看代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxmsk=(1<<16)+10;
int n,m,len;
char s[20][20];
int dx[4]={1,0,0,-1};
int dy[4]={0,1,-1,0};
bool inbound(int x,int y)
{
	return x&&y&&(x<=n)&&(y<=m);
}
int sx,sy,ex,ey;
struct node
{
	int x,y;
	int msk,step;
};
bool vis[20][20][maxmsk],used[20][20];
int tx[10],ty[10],tmp[10];
void getall(int msk,int sx,int sy,int d)
{
	int tot=0,rst=len-1;
	while(rst--)
	{
		tmp[++tot]=msk%4;
		msk>>=2;
	}
	for(int i=tot;i>=2;i--)
	{
		int nx=sx+dx[tmp[i]],ny=sy+dy[tmp[i]];
		used[nx][ny]=d;
		sx=nx,sy=ny;
	}
}
int bfs(int st)
{
	vis[sx][sy][st]=1;
	queue<node> q;
	q.push({sx,sy,st,0});
	while(!q.empty())
	{
		node t=q.front();
		q.pop();
		getall(t.msk,t.x,t.y,1);
		for(int i=0;i<4;i++)
		{
			int nx=t.x+dx[i],ny=t.y+dy[i],nmsk=(t.msk>>2)+((3-i)<<(2*(len-2)));
			if(!inbound(nx,ny)||vis[nx][ny][nmsk]||used[nx][ny]||s[nx][ny]=='#') continue;
			vis[nx][ny][nmsk]=1;
			if(nx==ex&&ny==ey) return t.step+1;
			q.push({nx,ny,nmsk,t.step+1});
		}
		getall(t.msk,t.x,t.y,0);
	}
	return -1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i]+1;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(s[i][j]=='@') ex=i,ey=j;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='1')
			{
				int posx=i,posy=j,now=1;
				sx=i,sy=j;
				int msk=0;
				while(1)
				{
					now++;
					bool flag=0;
					for(int k=0;k<4;k++)
					{
						int nx=posx+dx[k],ny=posy+dy[k];
						if(!inbound(nx,ny)||s[nx][ny]!=now+'0') continue;
						msk=(msk<<2)+k;
						flag=1;
						posx=nx,posy=ny;
						break;
					}
					if(!flag) break;
				}
				len=now-1;
				cout<<bfs(msk)<<endl;
				return 0;
			}
		}
	}
	return 0;
}

```


---

## 作者：SkyRainWind (赞：1)

本场比赛 A~E 的题解可以查看[我的blog](https://www.cnblogs.com/SkyRainWind/p/17062489.html)。

D

考虑蛇的一次移动如何表示，例如：

```
34.
21.
```

考虑先把蛇的每一个位置都 +1，然后去掉最末尾的一个。这一步相当于身体的移动。

```
4..
32.
```

再考虑头该如何移动：

```
41. 4..
32. 321
```

两种都是可以的。

（注意这样还能省去判断头和尾刚好差一格也是能移动的情况。）

然后就是普通的 bfs，但是还需要判断当前位置是否访问过，有两种方法：

- 对整个地图 hash。自然溢出[可能会被卡](https://codeforces.com/contest/225/submission/189733666)，普通hash可能[常数过大](https://codeforces.com/contest/225/submission/189736788)（最大点需要 4.4s,TLE）
- 对蛇 hash（就是记一下 $1..9$ 的位置然后hash），最大点只需要约 $2s$。

```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define pii pair<int,int>

using namespace std;

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;

const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 17;
const int p = 998244353, p2 = 990804011;

int n,m;
char s[maxn][maxn];
struct state{
	char st[maxn][maxn];
	int cnt;
	
	ull gethash(){
		ull hs = 0;
		ull hs2 = 0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				hs = hs*p + st[i][j],
				hs2 = (hs2*p2 + st[i][j]);
		return hs*127+hs2;
	}
	
	state(){cnt=0;}
}hajime;

int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
unordered_map<ull,int>vis;
queue<state>Q;
int ans = -1, len = 0;

int ind(int x,int y){return (x-1)*n+y;}
int in(int x,int y){return x>=1 && x<=n && y>=1 && y<=m;} 
ull hsh(int *pp){
	ull now=0;
	for(int i=1;i<=len;i++)now=now*p+pp[i];
	return now;
}

void move(state now){
	int tmp[12];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(now.st[i][j] >= '1' && now.st[i][j] <= '9'){
				now.st[i][j] ++;
				if(now.st[i][j] < len + '1')tmp[now.st[i][j] - '0'] = ind(i, j);
			}
	int bx, by;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(now.st[i][j] == '2')
				bx = i, by = j;
			if(now.st[i][j] == len + '1')
				now.st[i][j] = '.';
		}
	
	now.cnt ++;
	for(int i=0;i<4;i++){
		int fx = bx + dx[i], fy = by + dy[i];
		if(!in(fx, fy))continue;
		if(now.st[fx][fy] == '@'){
			ans = now.cnt;
			return ;
		}else if(now.st[fx][fy] == '.'){
			tmp[1] = ind(fx, fy);
			now.st[fx][fy] = '1';
			ull nowhs = hsh(tmp);
			if(!vis.count(nowhs)){
				vis[nowhs] = 1;
//				vis.insert(nowhs);
				Q.push(now);
			}
			now.st[fx][fy] = '.';
		}
	}
}

signed main(){
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++)scanf("%s",hajime.st[i] + 1);
	
	int tmp[12];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(hajime.st[i][j] >= '1' && hajime.st[i][j] <= '9')
				len = max(len, hajime.st[i][j] - '0'),
				tmp[hajime.st[i][j] - '0'] = ind(i, j);
	hajime.cnt = 0;
	vis[hsh(tmp)] = 1;
//	vis.insert(hajime.gethash());
	Q.push(hajime);
	
	while(!Q.empty()){
		state now = Q.front(); Q.pop();
		
		move(now);
		if(~ans)break;
	}
	cout<<ans;

	return 0;
}
```

---

## 作者：Imerance1018 (赞：0)

提供一个不用哈希和位运算的做法。（其实上本质是相同的，但我觉得这个做法更好理解和查错）

### Description

[here](https://codeforces.com/problemset/problem/225/D)

### Solution

发现 $n$ 和 $m$ 很小，可以直接 bfs，但难点在如何存储蛇。

可以先存储蛇头坐标，然后对以后的每一段记录此段在上一段的什么方位。那么状态数为 $15 \times 15 \times 4^8$，不超过 $2 \times 10^7$。

接下来在 bfs 的时候先把状态转化成二维的地图，再将蛇头往接下来的三个方向分别走即可。
~~有巨佬用位运算做，但我不会。~~

注意蛇头下一步可以走到当前蛇尾所在的位置。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=20;
int n,m;
string mapp[N];
struct node
{
	int pos,x,y,val;
};//存状态，pos 表示蛇的身体，x 和 y 描述蛇头位置，val 为答案
queue<node>q;
bool vis[N][N][65536];
int st,stx,sty,len=1;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
string now[N];
int dfs(int x,int y)//生成 pos
{
	int res=0;
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>m)continue;
		if(now[xx][yy]==now[x][y]+1)
			res=dfs(xx,yy)*4+i;
	}
	return res;
}

void solve(int pos,int x,int y,int num)//画蛇
{
	if(num>len)return;
	now[x][y]=num+'0';
	int xx=x+dx[pos%4],yy=y+dy[pos%4];
	pos/=4;
	solve(pos,xx,yy,num+1);
}
void paint(int pos,int x,int y)//将状态转化成地图
{
	for(int i=1;i<=n;i++)now[i]="*";
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(mapp[i][j]=='#'||mapp[i][j]=='@')now[i]+=mapp[i][j];
			else now[i]+='.';
		}
	}
	solve(pos,x,y,1);
}

int getpos(int x,int y,int num)//找蛇尾位置
{
	if(num==len)return x*30+y;// pair 的替代品，因为 x,y 不大 
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(now[xx][yy]==now[x][y]+1)return getpos(xx,yy,num+1);
	}	
}

int bfs()
{
	while(!q.empty())
	{
		int pos=q.front().pos,x=q.front().x,y=q.front().y,z=q.front().val;
		q.pop();
		
		if(vis[x][y][pos])continue;
		vis[x][y][pos]=1;
		if(mapp[x][y]=='@')return z;
		
		paint(pos,x,y);

		int lst=getpos(x,y,1);
		int lstx=lst/30,lsty=lst%30;
		now[lstx][lsty]='.';//为移动蛇做准备
		
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<1||yy<1||xx>n||yy>m)continue;
			if(now[xx][yy]!='.'&&now[xx][yy]!='@')continue;
			now[xx][yy]='0';
  //由于 dfs 函数只会考虑蛇身编号的相对大小关系，所以这就相当于把蛇往前移了一格，蛇尾在循环外面就已去除
			//cout<<xx<<" "<<yy<<" "<<endl;
			q.push((node){dfs(xx,yy),xx,yy,z+1});
			
			now[xx][yy]='.';//别忘了还原
		}
	}
	return -1;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>mapp[i];
		mapp[i]='*'+mapp[i];
		for(int j=1;j<=m;j++)
			if(mapp[i][j]>='1'&&mapp[i][j]<='9')
				len=max<int>(len,mapp[i][j]-'0');
		now[i]=mapp[i];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mapp[i][j]=='1')
			{
				stx=i,sty=j;
				st=dfs(i,j);
				break; 
			}
	q.push((node){st,stx,sty,0}); 
	cout<<bfs();
	return 0;
}
``````

---

