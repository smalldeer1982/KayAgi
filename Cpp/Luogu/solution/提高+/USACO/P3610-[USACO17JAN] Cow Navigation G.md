# [USACO17JAN] Cow Navigation G

## 题目描述

Bessie 又一次被困在了 Farmer John 的谷仓的错误一侧，由于她的视力很差，她需要你的帮助来穿过谷仓。

谷仓由一个 $N \times N$ 的方格网格描述（$2 \leq N \leq 20$），其中一些格子是空的，另一些则包含无法通过的干草堆。Bessie 从左下角（格子 1,1）开始，想要移动到右上角（格子 $N,N$）。你可以通过告诉她一系列指令来引导她，每条指令可以是“前进”、“向左转 90 度”或“向右转 90 度”。你需要给出最短的指令序列，以引导她到达目的地。如果你指示 Bessie 移动到网格外（即撞到谷仓墙壁）或进入干草堆，她将不会移动，并跳过你序列中的下一条指令。

不幸的是，Bessie 不知道她最初是面朝上（朝向格子 1,2）还是面朝右（朝向格子 2,1）。你需要给出一个最短的指令序列，无论她最初面朝哪个方向，都能引导她到达目标。一旦她到达目标，她将忽略后续的指令。

## 样例 #1

### 输入

```
3
EHE
EEE
EEE```

### 输出

```
9```

# 题解

## 作者：曹老师 (赞：5)

**知识点：六维BFS**

就一个bfs但是调了好几个小时（临界条件好麻烦

（虽然代码中有注释 但我还是想讲~~(tu)~~讲~~(cao)~~

**因为有两头牛而且N值比较小 我们可以用六维数组模拟出每一个牛的朝向和位置**

f[x1][y1][x2][t2][d1][d2]含义如上

还要注意临界条件：**边界和障碍要判断 判断牛是否应该回到来时的点**

**然后就是进栈 更新什么的**

这里我用了传址& ~~也可以直接Ctrl+C Ctrl+V来省事（不是复制My Code~~

接下来**判断左转右转** 特判一下方向：以免出负号RE

因为我们不知道最后的牛的脸朝哪儿 **于是枚举方向即可求出答案**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=21;
int n,map[L][L],f[L][L][L][L][5][5],ans=INF,dx[]={0,-1,0,1,0},dy[]={0,0,1,0,-1};
bool vis[L][L][L][L][5][5];
struct node{
	int x1,x2,y1,y2,d1,d2;
    node (int x1,int y1,int x2,int y2,int d1,int d2):x1(x1),y1(y1),x2(x2),y2(y2),d1(d1),d2(d2) {}
    node () {}
};
int ex(char ch)
{
	if(ch=='E')
		return 1;
	return 0;
}
bool judge(int x,int y)
{
	return (x>=1)&&(x<=n)&&(y>=1)&&(y<=n);
}
void bfs()
{
	queue<node>q;
	q.push(node(n,1,n,1,1,2));
	while(!q.empty())
	{
		node head=q.front();
		q.pop();
		int nx1,nx2,ny1,ny2;		//直走 
		nx1=head.x1+dx[head.d1];
		ny1=head.y1+dy[head.d1];
		nx2=head.x2+dx[head.d2];
		ny2=head.y2+dy[head.d2];
		int cnt=f[head.x1][head.y1][head.x2][head.y2][head.d1][head.d2];
		if(!judge(nx1,ny1)||(!map[nx1][ny1]))//牛一不能直走 再回来 
			nx1=head.x1,ny1=head.y1;
		if(!judge(nx2,ny2)||(!map[nx2][ny2]))//牛二不能直走 再回来 
			nx2=head.x2,ny2=head.y2;
		if(head.x1==1&&head.y1==n)//牛一走到边界 不能移动 
			nx1=1,ny1=n;
        if (head.x2==1&&head.y2==n)//牛二走到边界 不能移动 
			nx2=1,ny2=n;
		int &p=f[nx1][ny1][nx2][ny2][head.d1][head.d2];
		if(p>cnt+1)//进栈 更新 
		{
			p=cnt+1;
			if(!vis[nx1][ny1][nx2][ny2][head.d1][head.d2])
			{
				vis[nx1][ny1][nx2][ny2][head.d1][head.d2]=1;
				q.push(node(nx1,ny1,nx2,ny2,head.d1,head.d2));
			}
		} 
		int d1,d2;
		d1=head.d1-1,d2=head.d2-1;		//左转 
		if(!d1) d1=4; if(!d2) d2=4;
		int &u=f[head.x1][head.y1][head.x2][head.y2][d1][d2];
		if(u>cnt+1)//进栈 更新 
		{
			u=cnt+1;
			if(!vis[head.x1][head.y1][head.x2][head.y2][d1][d2])
			{
				vis[head.x1][head.y1][head.x2][head.y2][d1][d2]=1;
				q.push(node(head.x1,head.y1,head.x2,head.y2,d1,d2));
			}
		}
        d1=head.d1+1,d2=head.d2+1;		//右转 
		if(d1==5) d1=1;if(d2==5) d2=1;
		int &r=f[head.x1][head.y1][head.x2][head.y2][d1][d2];
		if(r>cnt+1)//进栈 更新 
		{
			r=cnt+1;
			if(!vis[head.x1][head.y1][head.x2][head.y2][d1][d2])
			{
				vis[head.x1][head.y1][head.x2][head.y2][d1][d2]=1;
				q.push(node(head.x1,head.y1,head.x2,head.y2,d1,d2));
			}	
		}
	}
}
int main()
{
	memset(f,0x3f,sizeof(f));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			char c;
			cin>>c;
			map[i][j]=ex(c);
		}
	f[n][1][n][1][1][2]=0;
	bfs();
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			ans=min(ans,f[1][n][1][n][i][j]);//枚举最后的朝向 
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Lastwhisper1212 (赞：3)

这道题可以用结构体+bfs做
结构体有7个参数{x1, y1, d1, x2, y2, d2, step}

x1, y1, d1 用来跟踪第一头牛的位置 (x1, y1), 和它的方向 d1

x2, y2, d2 用来跟踪第一头牛的位置 (x2, y2), 和它的方向 d2

其中d1和d2从N->E->S->W 以0-3 表示，0表示上，3表示右

这样对于任何一头牛我们输入指令的时候左转就变成 (d + 3) % 4 , 右转就是 (d + 1) % 4

step是在bfs中跟踪步数的变量

**具体代码每次bfs循环推进3个新的，未访问过的地点（包括方向）进队列**

```cpp

int dirr[] = {-1, 0, 1, 0}, dirc[] = {0, 1, 0, -1}; //变向数组

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n && map[x][y];
}

//左转
que.push(location(loc.x1, loc.y1, (loc.d1 + 3) % 4, loc.x2, loc.y2, (loc.d2 + 3) % 4, loc.step + 1));

//右转
que.push(location(loc.x1, loc.y1, (loc.d1 + 1) % 4, loc.x2, loc.y2, (loc.d2 + 1) % 4, loc.step + 1));
```
```cpp
//直走
int x1, x2, y1, y2;
x1 = loc.x1 + dirr[loc.d1];
x2 = loc.x2 + dirr[loc.d2];
y1 = loc.y1 + dirc[loc.d1];
y2 = loc.y2 + dirc[loc.d2];

if (!check(x1, y1) || (loc.x1 == 0 && loc.y1 == n - 1)) {
	x1 = loc.x1;
	y1 = loc.y1;
}
if (!check(x2, y2) || (loc.x2 == 0 && loc.y2 == n - 1)) {
	x2 = loc.x2;
	y2 = loc.y2;
}
que.push(location(x1, y1, loc.d1, x2, y2, loc.d2, loc.step + 1));
```
直走：新建4个变量x1, y1, x2, y2, 作为这两头牛下一步的坐标（方向不变）。用变向数组就能枚举出下一步以当前方向的下一个位置。然后我们check这些坐标，要是出界，碰到障碍，或者已走到终点，就返回原来的位置。最终push进去这个location，然后step++。

完整代码：
```cpp
#include <cstring>
#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;

int n, dirr[] = {-1, 0, 1, 0}, dirc[] = {0, 1, 0, -1};
bool map[20][20], vis[20][20][4][20][20][4];

struct location {
int x1, y1, d1, x2, y2, d2, step;
location(int _x1, int _y1, int _d1, int _x2, int _y2, int _d2, int _step) {
		x1 = _x1;
		y1 = _y1;
		d1 = _d1;
		x2 = _x2;
		y2 = _y2;
		d2 = _d2;
		step = _step;
	}
};

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n && map[x][y];
}

void bfs() {
	queue<location> que;
	que.push(location(n - 1, 0, 0, n - 1, 0, 1, 0));

	while (!que.empty()) {
		location loc = que.front();
		if (!vis[loc.x1][loc.y1][loc.d1][loc.x2][loc.y2][loc.d2]) {
			vis[loc.x1][loc.y1][loc.d1][loc.x2][loc.y2][loc.d2] = true;

			if (loc.x1 == 0 && loc.y1 == n - 1 && loc.x2 == 0 && loc.y2 == n - 1) {
				cout << loc.step;
				break;
			}
            
			//left
			que.push(location(loc.x1, loc.y1, (loc.d1 + 3) % 4, loc.x2, loc.y2, (loc.d2 + 3) % 4, loc.step + 1));

			//right
			que.push(location(loc.x1, loc.y1, (loc.d1 + 1) % 4, loc.x2, loc.y2, (loc.d2 + 1) % 4, loc.step + 1));

			//forward
			int x1, x2, y1, y2;
			x1 = loc.x1 + dirr[loc.d1];
			x2 = loc.x2 + dirr[loc.d2];
			y1 = loc.y1 + dirc[loc.d1];
			y2 = loc.y2 + dirc[loc.d2];

			if (!check(x1, y1) || (loc.x1 == 0 && loc.y1 == n - 1)) {
				x1 = loc.x1;
				y1 = loc.y1;
			}
			if (!check(x2, y2) || (loc.x2 == 0 && loc.y2 == n - 1)) {
				x2 = loc.x2;
				y2 = loc.y2;
			}
			que.push(location(x1, y1, loc.d1, x2, y2, loc.d2, loc.step + 1));
		}
		que.pop();
	}
}

int main() {
	cin >> n;
	char temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> temp;
			if (temp == 'E')
				map[i][j] = 1;
		}
	}
	//start: [n-1][0]
	//end: [0][n-1]
	//N->E->S->W : 0, 1, 2, 3
	bfs();
}
```



---

## 作者：yummy (赞：2)

首先我们如果单单口胡，很容易想到一个 $O(dn^4)$ 的 BFS（其中 $d$ 表示牛的朝向数，本题为 $4$）。

写的时候我们观察到这是 USACO 题，放心使用 STL，对于一个结构体我们开朝右走的奶牛坐标、朝上走的奶牛坐标、朝右走的奶牛方向。

然后我们思考怎么判重。我们发现，如果开五维数组，可能会碰到下面的问题：
- 发现结构体又要一个一个解绑，代码量上升。
- 这道题问题不大，如果是其他题，可能产生大量浪费，空间受不了。

因此我们采用 `unordered_map/set` 就可以很好地解决。

很多同学（包括我）之前都没有用过这玩意存自定义结构体，因为显然 STL 并不会为这种东西提供 `hash_policy`。因此这里简单地教一下。

首先，你需要**重载 `==`**，因为这是 `unordered`，所以你并不需要重载小于号。

然后，你需要手写哈希函数。这个哈希和我们平时的哈希不同，由于哈希表大小是 STL 决定的，你并不需要求余，直接返回一个 `size_t` 就行了。

总而言之，你需要写下面这种东西：
```cpp
struct node{int x1,y1,x2,y2,dir;};
bool operator == (node x,node y){return x.x1==y.x1 and x.x2==y.x2 and x.y1==y.y1 and x.y2==y.y2 and x.dir==y.dir;}//定义相等
struct my_hash//定义哈希
{
	size_t operator () (node x)const//这句话其实可以直接背（
	{
		return (((x.x1*20+x.y1)*20+x.x2)*20+x.y2)*4+x.dir;
	}
};
unordered_map<node,int,my_hash> dis;//在最后一个参数的位置写上你的哈希
```

其他地方就大同小异了。下面放出参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define x1 eoifgjfkwdf
#define y1 poeirtwepfjdkl
const int dry[]={1,0,-1,0};
const int drx[]={0,-1,0,1};
const int duy[]={0,-1,0,1};
const int dux[]={-1,0,1,0};
int n;
char mp[22][22];
struct node{int x1,y1,x2,y2,dir;};
bool operator == (node x,node y){return x.x1==y.x1 and x.x2==y.x2 and x.y1==y.y1 and x.y2==y.y2 and x.dir==y.dir;}
struct my_hash
{
	size_t operator () (node x)const
	{
		return (((x.x1*20+x.y1)*20+x.x2)*20+x.y2)*4+x.dir;
	}
};
unordered_map<node,int,my_hash> dis;
queue<node> q;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	q.push({n,1,n,1,0});
	dis[{n,1,n,1,0}]=0;
	while(q.size())
	{
		node qf=q.front();int qd=dis[qf];q.pop();
		node rht={qf.x1,qf.y1,qf.x2,qf.y2,(qf.dir+1)%4};
		if(dis.count(rht)==0)
			q.push(rht),dis[rht]=qd+1;
		node lft={qf.x1,qf.y1,qf.x2,qf.y2,(qf.dir+3)%4};
		if(dis.count(lft)==0)
			q.push(lft),dis[lft]=qd+1;
		if(not(qf.x1==1 and qf.y1==n) and mp[qf.x1+drx[qf.dir]][qf.y1+dry[qf.dir]] == 'E')
			qf.x1+=drx[qf.dir],qf.y1+=dry[qf.dir];
		if(not(qf.x2==1 and qf.y2==n) and mp[qf.x2+dux[qf.dir]][qf.y2+duy[qf.dir]] == 'E')
			qf.x2+=dux[qf.dir],qf.y2+=duy[qf.dir];
		if(dis.count(qf)==0)
			q.push(qf),dis[qf]=qd+1;
	}
	int ans=0x3f3f3f3f;
	if(dis.count({1,n,1,n,0}))ans=min(ans,dis[{1,n,1,n,0}]);
	if(dis.count({1,n,1,n,1}))ans=min(ans,dis[{1,n,1,n,1}]);
	if(dis.count({1,n,1,n,2}))ans=min(ans,dis[{1,n,1,n,2}]);
	if(dis.count({1,n,1,n,3}))ans=min(ans,dis[{1,n,1,n,3}]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Rachel_in (赞：2)

看题解都是6维BFS做的，$f[x1][y1][x2][y2][dir1][dir2]$，表示原先朝上的走到$(x1,y1)$,方向为dir1，原先朝左的走到$(x2,y2)$,方向为dir2的最小步数，然后跑bfs就可以了。**但其实还是可以空间优化的，我们可以把它降到5维，**也就是只存一个dir就可以了,因为不管转几次，原先朝上的方向肯定是原先朝左的方向向右，故我们只需记录一个dir就行了。bfs的代码题解里的各位dalao都已经解释的很清楚了，不再赘述了QwQ

---

## 作者：nihanchu (赞：2)

这道题我看了半天别人的题解，为了很久以后我还能看懂，所以写题解来记录一下。


此题为usaco20171月月赛金组


这道题是一道动归加上spfa，用dis[x1][y1][x2][y2][d1][d2]来表示两条路分别在x1,y1,面向d1,和在x2,y2,面向d2,从起点出发要到这个状态所需的最短指令。


spfa中，分三种情况来讨论三种做法，最后的得到结果。


具体的解释和意思在代码注释里。


复制代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n,m[100][100],dis[30][30][30][30][5][5]; 
bool c[30][30][30][30][5][5];
int nowx1,nowx2,nowy1,nowy2;
int h[]={0,-1,0,1,0},l[]={0,0,1,0,-1};
int sum1,ans,sum2,td1,td2;
char a[100][100];
struct gather{
    int x1,y1,x2,y2,d1,d2;
    gather (int x1,int y1,int x2,int y2,int d1,int d2):
        x1(x1),y1(y1),x2(x2),y2(y2),d1(d1),d2(d2){}
    gather () {}
};
//上面这段定义，是我无耻地抄了一个博客，因为我完全不知道该怎么把那六个元素定义起来....也是看了那个人的博客后才指导方法的。。。
```
我们就姑且算作是定义了一个包含六个元素的集合吧。。。
```cpp
queue<gather>q;//定义一个队列
bool check(int x,int y)
{
    if ((x<1)||(x>n)||(y<1)||(y>n)) return false;
    else return true;
```
}//检查目前的这个坐标有没有越界
```cpp
void spfa()
{
  q.push(gather(n,1,n,1,1,2));//把第一个集合放进去，也就是贝西的起始位置
  c[n][1][n][1][1][2]=true;//这个集合已经出队列了
  while (!q.empty())//如果集合不为空
  {
      gather p=q.front();//拿出队首的集合
      q.pop();//删队首集合
       //1.第一种方案，按当前方向继续向前走
      nowx1=p.x1+h[p.d1]; nowy1=p.y1+l[p.d1];
      nowx2=p.x2+h[p.d2]; nowy2=p.y2+l[p.d2];
       //以上是两条路在继续按当前方向走后，会到达的点
      if ((check(nowx1,nowy1)==false)||(m[nowx1][nowy1]==false)){
        nowx1=p.x1; nowy1=p.y1;
    }
    if ((check(nowx2,nowy2)==false)||(m[nowx2][nowy2]==false)){
        nowx2=p.x2; nowy2=p.y2;
    } 
       //以上两个if语句表示如果继续向前走一步，到达的点如果超出图的范围，或者是那个店存在石头，都是不能走的，应停留在原来的位置。
    if ((p.x1==1)&&(p.y1==n)){nowx1=1;nowy1=n;}
    if ((p.x2==1)&&(p.y2==n)){nowx2=1;nowy2=n;}
    //这个点表示如果其中任意一条路原本已经到了终点，就不用再走了，停在原来位置。
      sum1=dis[nowx1][nowy1][nowx2][nowy2][p.d1][p.d2];
     //目前为止向前走需要的最短指令
      sum2=dis[p.x1][p.y1][p.x2][p.y2][p.d1][p.d2];
  //走到原来位置需要的最短指令
      if (sum1>sum2+1)//更新最短指令
      { 
        dis[nowx1][nowy1][nowx2][nowy2][p.d1][p.d2]=sum2+1;
        if (c[nowx1][nowy1][nowx2][nowy2][p.d1][p.d2]==false)
        q.push(gather(nowx1,nowy1,nowx2,nowy2,p.d1,p.d2));
          //如果不在队列内，就放进去
        c[nowx1][nowy1][nowx2][nowy2][p.d1][p.d2]=true;
    }
    //2.向右转90度
    td1=p.d1+1; td2=p.d2+1; 
    if (td1>4) td1=1; if (td2>4) td2=1;
       //更新所指向的方向
    sum1=dis[p.x1][p.y1][p.x2][p.y2][td1][td2];
    if (sum1>sum2+1)//更新最短指令
      { 
        dis[p.x1][p.y1][p.x2][p.y2][td1][td2]=sum2+1;
        if (c[p.x1][p.y1][p.x2][p.y2][td1][td2]==false)
        q.push(gather(p.x1,p.y1,p.x2,p.y2,td1,td2));
        c[p.x1][p.y1][p.x2][p.y2][td1][td2]=true;
    }
    //3.向左转90度
    td1=p.d1-1; td2=p.d2-1; 
    if (td1<1) td1=4; if (td2<1) td2=4;
    sum1=dis[p.x1][p.y1][p.x2][p.y2][td1][td2];
    if (sum1>sum2+1)
      { 
        dis[p.x1][p.y1][p.x2][p.y2][td1][td2]=sum2+1;
        if (c[p.x1][p.y1][p.x2][p.y2][td1][td2]==false)
        q.push(gather(p.x1,p.y1,p.x2,p.y2,td1,td2));
        c[p.x1][p.y1][p.x2][p.y2][td1][td2]=true;
    }
    c[p.x1][p.y1][p.x2][p.y2][p.d1][p.d2]=false;
       //出队列
  }
}
int main()
{
  scanf("%d",&n);
  a[1][1]=getchar();
  for (int i=1;i<=n;i++)
   for (int j=1;j<=n+1;j++)
   {
     a[i][j]=getchar();
     if (a[i][j]=='E') m[i][j]=true;
     else if (a[i][j]=='H') m[i][j]=false;
   }
//我们用dis[x1][y1][x2][y2][d1][d2]来表示两条路分别在x1,y1,面向d1,
```
和在x2,y2,面向d2,从起点出发要到这个状态所需的最短指令。
```cpp
  for (int i=1;i<=n;i++)
   for (int j=1;j<=n;j++)
    for (int i1=1;i1<=n;i1++)
     for (int j1=1;j1<=n;j1++)
      for (int u=1;u<=4;u++)
       for (int d=1;d<=4;d++)
       dis[i][j][i1][j1][u][d]=2147483647/2;//初始化
   dis[n][1][n][1][1][2]=0;
   ans=2147483647/2;
   spfa();
   for (int i=1;i<=4;i++)
    for (int j=1;j<=4;j++)
    ans=min(ans,dis[1][n][1][n][i][j]);     
   cout<<ans<<endl;
}
```

---

## 作者：s7a9 (赞：1)

写了一份~~自认为是比较清真的~~代码

思路很简单 就是6维bfs

以(n,1,0,n,1,1)为起点，(1,n,i,1,n,j)(0<=i,j<=3)中距离最小的为终点 三种状态转移

其中要注意几点,已在代码中标出

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 25
const int px[4]={-1,0,1,0},py[4]={0,1,0,-1};//0上1右2下3左
bool blk[N][N],mrk[N][N][4][N][N][4];
int n,dst[N][N][4][N][N][4],head,tail=1;
struct P{
	int x,y,d;
	bool IsnInBound(){return x<1||x>n||y<1||y>n||blk[x][y];}
};
struct S{
	P p1,p2;
	int& get(){return dst[p1.x][p1.y][p1.d][p2.x][p2.y][p2.d];}//返回引用 方便很多233
	bool IsMrked(){return mrk[p1.x][p1.y][p1.d][p2.x][p2.y][p2.d];}
	void Mark(){mrk[p1.x][p1.y][p1.d][p2.x][p2.y][p2.d]=true;}
};
void move(P& d,P f,int w){
	d=f;
	if(w==0){//前进
		if(d.x==1&&d.y==n)return;//这里坑了我很久...如果已经到了终点就不会再移动...调了我几个小时
		d.x+=px[d.d],d.y+=py[d.d];
		if(d.IsnInBound())d=f;
	}else if(w==1){//顺时针90
		d.d++;
		if(d.d==4)d.d=0;
	}else if(w==2){//逆时针90
		d.d--;
		if(d.d==-1)d.d=3;
	}
}
S q[N*N*N*N*16];
int main(){
	memset(dst,0x7f,sizeof(dst));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
    	getchar();
		for(int j=1;j<=n;j++){
			blk[i][j]='H'==getchar();
		}
	}
	q[0].p1.x=q[0].p2.x=n,q[0].p1.y=q[0].p2.y=q[0].p2.d=1;
	q[0].get()=0;
	S p,nx;
	while(head<tail){
		p=q[head++],nx;
//		if(p.p1.x==1&&p.p2.x==1&&p.p1.y==n&&p.p2.y==n)break;第一次遍历到其实就可停下
		int w=p.get();
		for(int i=0;i<3;i++){
			move(nx.p1,p.p1,i),move(nx.p2,p.p2,i);
			int &nd=nx.get();
			if(nd>w+1){
				nd=w+1;
				if(!nx.IsMrked())q[tail++]=nx,nx.Mark();//其实可以不用判断是否已经走过 因为转移状态花费为1 先遍历到的肯定距离最小
			}
		}
	}
	int ans=0x7f7f7f7f;
	for(int i=0;i<4;i++)for(int j=0;j<4;j++)ans=std::min(ans,dst[1][n][i][1][n][j]);
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：kuikuidadi (赞：1)

# 题意
一共有两头牛，一个 $n\times n$ 的矩阵，两头牛的初始位置都是 $(n,1)$，不知道是面朝 $(n-1,1)$ 还是 $(n,2)$，题目给定图，$E$ 可以走，$H$ 有障碍物。一共有三种指令，向左转，向右转，向前走，两头牛是同时接受信息，并同步执行命令，但是因为初始的方向不同，走过的路径也不同。但当牛面朝矩阵边界，或者面朝内容为 $H$ 的位置时可以发出向前走的命令，但是牛不执行。（总不能让牛钻进草堆里吧）。问题就是，最少要下达多少命令才可以让同时在 $(1,n)$ 的位置。（都在 $(1,n)$ 时面向无所谓。）其中，转向并走一步算是两条命令。
# 思路
其实就是一个六维 BFS。

每头牛的位置 $(x,y)$ 方向 $(z)$ 三个量，两头牛，所以就是六维的数组。

在就是 BFS 一下就可以了。

---

## 作者：Limit (赞：1)

这题算是[P1126 机器人搬重物](https://www.luogu.org/problemnew/show/P1126)的升级版QAQ，就是把他当成两只牛来算就好了
```
const z:array[1..4,1..2]of -1..1=((-1,0),(0,1),(1,0),(0,-1));
var i,j,k:longint;
    n:longint;
    bo:array[0..21,0..21,0..21,0..21,1..4,1..4]of boolean;
    //6维数组，为第一只牛的坐标、方向，第二只牛的坐标、方向
    no:array[0..21,0..21]of boolean;
    x1,y1,x2,y2,u,fx1,fx2:array[0..10000000]of longint;
    _x1,_y1,_x2,_y2,_fx1,_fx2:longint;
    ch:char;
    h,t:longint;
    x1i,y1i,x2i,y2i:longint;
procedure add(x1,y1,x2,y2:longint);//当前这一格是可以走的
var i,j:longint;
begin
  for i:=1 to 4 do
  for j:=1 to 4 do
  bo[x1,y1,x2,y2,i,j]:=true;
end;
function left(fx:longint):longint;//左转
begin
  if fx=1 then exit(4) else exit(fx-1);
end;
function right(fx:longint):longint;//右转
begin
  if fx=4 then exit(1) else exit(fx+1);
end;
procedure go(fx:longint;var x,y:longint);//判断可不可以走...
begin
  if (x=1) and (y=n) then exit;//到了终点就不可以走了
  if no[x+z[fx,1],y+z[fx,2]] then//移动
  begin
    x:=x+z[fx,1];
    y:=y+z[fx,2];
  end;
end;
begin
  readln(n);
  for i:=1 to n do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='E' then
      no[i,j]:=true;
    end;
  readln;
  end;
  //判断用的数组初始化
  for x1i:=1 to n do
  for y1i:=1 to n do
  for x2i:=1 to n do
  for y2i:=1 to n do
  if no[x1i,y1i] and no[x2i,y2i] then
  add(x1i,y1i,x2i,y2i);
  //队列初始化
  h:=1;
  t:=1;
  x1[1]:=n;
  y1[1]:=1;
  x2[1]:=n;
  y2[1]:=1;
  u[1]:=0;
  fx1[1]:=1;
  fx2[1]:=2;
  bo[x1[1],y1[1],x2[1],y2[1],fx1[1],fx2[1]]:=false;
  repeat
    if (x1[t]=1) and (x2[t]=1) and (y1[t]=n) and (y2[t]=n) then//两只牛都到终点了
    begin
      write(u[t]);
      exit;
    end;
    for i:=1 to 3 do
    begin
      if i=1 then
      begin
        //记录下来比较方便
        _x1:=x1[t];
        _y1:=y1[t];
        _x2:=x2[t];
        _y2:=y2[t];
        go(fx1[t],_x1,_y1);
        go(fx2[t],_x2,_y2);
        if(bo[_x1,_y1,_x2,_y2,fx1[t],fx2[t]])then//判断向前走可不可以
        begin//入队列
          inc(h);
          x1[h]:=_x1;
          y1[h]:=_y1;
          x2[h]:=_x2;
          y2[h]:=_y2;
          fx1[h]:=fx1[t];
          fx2[h]:=fx2[t];
          bo[_x1,_y1,_x2,_y2,fx1[t],fx2[t]]:=false;
          u[h]:=u[t]+1;
        end;
      end;
      if i=2 then
      if(bo[x1[t],y1[t],x2[t],y2[t],left(fx1[t]),left(fx2[t])])then//左转
      //转弯不会到地图外面和草上，不用特判
      begin
        inc(h);
        fx1[h]:=left(fx1[t]);
        fx2[h]:=left(fx2[t]);
        x1[h]:=x1[t];
        y1[h]:=y1[t];
        x2[h]:=x2[t];
        y2[h]:=y2[t];
        bo[x1[h],y1[h],x2[h],y2[h],fx1[h],fx2[h]]:=false;
        u[h]:=u[t]+1;
      end;
      if i=2 then
      if(bo[x1[t],y1[t],x2[t],y2[t],right(fx1[t]),right(fx2[t])])then//右转QAQ
      begin
        inc(h);
        fx1[h]:=right(fx1[t]);
        fx2[h]:=right(fx2[t]);
        x1[h]:=x1[t];
        y1[h]:=y1[t];
        x2[h]:=x2[t];
        y2[h]:=y2[t];
        bo[x1[h],y1[h],x2[h],y2[h],fx1[h],fx2[h]]:=false;
        u[h]:=u[t]+1;
      end;
    end;
    inc(t);
  until t>h;
end.
```
就是写起来累点，思路还是很清楚的QAQWQ


---

## 作者：Loser_Syx (赞：0)

就是一个简单广搜。  
考虑要求两种朝向都能走出，那么我们可以看成存在两头奶牛不同朝向。  
于是可以定义状态 $(a,b,c,d,e,f)$，为奶牛 A 在 $(a,b)$ 处面向 $e$ 方向，奶牛 B 在 $(c,d)$ 处面向 $f$ 方向，然后对于每个指令走一下，判一下合法就行，注意不合法是不移动。  
具体 bfs 一遍即可，复杂度很安全。

```cpp
// dir = 0(up), dir = 1(right), dir = 2(down), dir = 3(left)
struct node {
	int x, y, dir;
	void right() {
		dir = (dir + 1) % 4;
	}
	void left() {
		dir = (dir + 4 - 1) % 4;
	}
};
struct cow {
	node a, b;
	int step;
};
char mp[101][101];
bool vis[21][21][21][21][4][4];
int n;
int dir[4][2] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};
bool finished(node x) {
	if (x.x == 1 && x.y == n) return 1;
	return 0;
}
bool in(int x) {
	return x >= 1 && x <= n;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) cin >> mp[i][j];
	queue<cow> q;
	q.push({{n, 1, 0}, {n, 1, 1}, 0});
	while (!q.empty()) {
		cow f = q.front();
		q.pop();
		if (finished(f.a) && finished(f.b)) {
			cout << f.step << '\n';
			break;
		}
		cow _ = f;
		_.a.left(), _.b.left();
		_.step += 1;
		if (!vis[_.a.x][_.a.y][_.b.x][_.b.y][_.a.dir][_.b.dir]) {
			vis[_.a.x][_.a.y][_.b.x][_.b.y][_.a.dir][_.b.dir] = 1;
			q.push(_);
		}
		_ = f;
		_.a.right(), _.b.right();
		_.step += 1;
		if (!vis[_.a.x][_.a.y][_.b.x][_.b.y][_.a.dir][_.b.dir]) {
			vis[_.a.x][_.a.y][_.b.x][_.b.y][_.a.dir][_.b.dir] = 1;
			q.push(_);
		}
		_ = f;
		if (!finished(_.a)) _.a.x += dir[_.a.dir][0], _.a.y += dir[_.a.dir][1];
		if (!(in(_.a.x) && in(_.a.y) && mp[_.a.x][_.a.y] != 'H')) _.a = f.a;
		if (!finished(_.b)) _.b.x += dir[_.b.dir][0], _.b.y += dir[_.b.dir][1];
		if (!(in(_.b.x) && in(_.b.y) && mp[_.b.x][_.b.y] != 'H')) _.b = f.b;
		_.step += 1;
		if (!vis[_.a.x][_.a.y][_.b.x][_.b.y][_.a.dir][_.b.dir]) {
			vis[_.a.x][_.a.y][_.b.x][_.b.y][_.a.dir][_.b.dir] = 1;
			q.push(_);
		}
	}
	return 0;
}
```

---

