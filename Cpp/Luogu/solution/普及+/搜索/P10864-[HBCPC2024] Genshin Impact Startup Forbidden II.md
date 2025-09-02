# [HBCPC2024] Genshin Impact Startup Forbidden II

## 题目描述

### 弹窗内容

LeavingZ：你被禁止玩《原神》。



蓝边铅球因LeavingZ的禁止而无法玩《原神》，所以她转向了围棋。

围棋游戏由两名玩家进行，一方使用黑子，另一方使用白子。两名玩家轮流下子，黑子先行。围棋棋盘由$19\times 19$的交叉点组成，我们用$(x,y)$表示第$x$行第$y$列的交叉点。棋子放置在交叉点上。左上角为$(1,1)$，右下角为$(19,19)$。

如果$|x_1-x_2| + |y_1-y_2| = 1$，那么交叉点$(x_1,y_1)$和$(x_2,y_2)$是相邻的。相邻的交叉点上放置相同颜色的棋子属于同一组棋子。一个棋子的“气”数等于该棋子所在交叉点的相邻交叉点上没有棋子的个数。一组棋子的“气”数等于该组棋子中所有棋子的“气”数之和。一组棋子如果“气”数为零，则被视为“死棋”并且必须从棋盘上移除。

注意，在黑子落子后，优先移除任何死掉的白子，然后重新计算黑子的“气”数。这是因为可能出现这样的情况：黑子落子后，黑白两方的棋子都没有“气”，但移除死掉的白子会增加黑子的“气”。白子落子的处理方式类似。在白子落子后，优先移除任何死掉的黑子，然后重新计算白子的“气”数。

现在有一局围棋，从空棋盘开始，总共进行了$m$步。给定每步棋子的放置位置，请输出每步棋子落子后，分别有多少颗黑子和白子被移除。显然，黑子在奇数步落子，白子在偶数步落子。保证棋子放置在空的交叉点上。注意，棋子可以放置在$\textbf{任意}$当前没有棋子的交叉点上，无论是否违反了现实中的[围棋规则](https://zhuanlan.zhihu.com/p/440794632)$^{(1)}$。

注释：
- (2):译者补充

## 样例 #1

### 输入

```
8
2 1
1 1
1 2
2 2
1 1
1 3
2 3
3 1```

### 输出

```
0 0
0 0
0 1
0 0
0 0
0 0
0 0
3 0```

# 题解

## 作者：jianhe (赞：5)

### 题意：
两个人下围棋，保证每次下在空位上，求每步棋后，被吃掉的黑子与白子数量。
### 思路：
众所周知，围棋棋盘大小是 $19 \times 19$ 的，因此我们可以采取比较暴力的方式：在每步棋后，暴力搜索整个棋盘，寻找没有气的棋子，并统计答案。

为保证复杂度，我们用 $vis$ 数组标记一个位置是否被遍历过。

有许多要注意的细节：
1. 要先提对方的棋子，再提自己的。
2. $vis$ 数组每次都要清空。
3. 不要忘记写 `continue`。
4. 可以用 `-1` 表示没有棋子。
5. 记得删除被吃掉的棋子（标记为 $-1$）。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define fi first
#define se second
ll m,x,y,black,white,qi[20][20];
ll dx[]={-1,0,0,1};
ll dy[]={0,-1,1,0};
queue<pair<ll,ll> > q;
vector<pair<ll,ll> > e;
bool vis[20][20];
bool ok(ll x,ll y){return 1<=x&&x<=19&&1<=y&&y<=19;}
void bfs(ll x,ll y,bool col){
	q.push({x,y});e.clear();
	bool flag=0;
	while(!q.empty()){//检查这块棋是否有气
		auto tmp=q.front();q.pop();
		ll xx=tmp.fi,yy=tmp.se;
		if(!flag) e.push_back({xx,yy});
		for(int k=0;k<4;k++){
			ll px=xx+dx[k],py=yy+dy[k];
			if(!ok(px,py)||qi[px][py]==!col) continue;
			if(qi[px][py]==-1){flag=1;continue;}//记得写 continue!
			if(vis[px][py]) continue;
			vis[px][py]=1,q.push({px,py});
		}
	}
	if(flag) return;
	if(col) black+=e.size();
	else white+=e.size();
	for(auto pp:e) qi[pp.fi][pp.se]=-1;
}
void solve(bool col){
	black=white=0;
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++) vis[i][j]=0;
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++)
			if(!vis[i][j]&&qi[i][j]==!col) vis[i][j]=1,bfs(i,j,!col);//先删对方的，再删自己的
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++)
			if(!vis[i][j]&&qi[i][j]==col) vis[i][j]=1,bfs(i,j,col);
	cout<<black<<" "<<white<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++) qi[i][j]=-1;
    //-1 表示没有棋，1 表示黑棋，0 表示白棋
	cin>>m;
	for(int i=1;i<=m;i++)
		cin>>x>>y,qi[x][y]=(i&1),solve(i&1);
	return 0;
}
```

---

## 作者：Bill_luogu (赞：3)

## 本题思路：  
本题是一个大模拟，我们每一次输入都把整个棋盘都搜一遍，计算每个黑棋和白棋联通块的气，如果没气了，那就把联通块里的棋子都移除，并统计黑棋和白棋被移除的数量。  
代码如下：
```cpp
#include<bits/stdc++.h>
#include<queue>
using namespace std;
typedef pair<int,int> point;
int map1[30][30],t,x2,y2,ans1,ans2,x3[1010],y3[1010],cnt;
const int dx[]={0, 0,-1,1};
const int dy[]={1,-1, 0,0};
bool vis[30][30],flag=0;
queue<point> q;
void bfs(int x,int y,int c)//搜索每一个联通块
{
	while(!q.empty())q.pop();
	cnt=0;
	flag=0;
	q.push((point){x,y});
	while(!q.empty())
	{
		point now=q.front();
		q.pop();
		if(flag==0)
		x3[++cnt]=now.first,y3[cnt]=now.second;//记录位置，等一下好删除
		for(int i=0;i<4;i++)
		{
			int xx=now.first+dx[i];
			int yy=now.second+dy[i];
			if(map1[xx][yy]==-1&&xx>=1&&xx<=19&&yy>=1&&yy<=19)//判断是否有气
			{
				flag=1;
				continue;
			}
			if(map1[xx][yy]==c&&vis[xx][yy]==0&&xx>=1&&xx<=19&&yy>=1&&yy<=19)
			{
				point tool1;
				tool1.first=xx;
				tool1.second=yy;
				q.push(tool1);
				vis[xx][yy]=1;
			}
		}
	}
	if(flag)return;
	for(int i=1;i<=cnt;i++)
		map1[x3[i]][y3[i]]=-1;//移除没气的棋子
  //统计
	if(c==1)
	ans1+=cnt;
	if(c==0)
	ans2+=cnt;
	return;
}
int main()
{
	cin>>t;
  //我们定义map1[i][j]=-1为没棋子，map1[i][j]=1为这个地方是黑棋，map1[i][j]=0为这个地方是白棋棋
	for(int i=1;i<=19;i++)
		for(int j=1;j<=19;j++)
			map1[i][j]=-1;//标记为没棋子
	for(int k=1;k<=t;k++)
	{
		cin>>x2>>y2;
		ans1=0,ans2=0;
		map1[x2][y2]=k%2;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=19;i++)
		{
			for(int j=1;j<=19;j++)
			{
				if(map1[i][j]==!(k%2)&&!vis[i][j])
				{
					flag=0;
					vis[i][j]=1;
					bfs(i,j,!(k%2));//搜联通块
				}
			}
		}
		for(int i=1;i<=19;i++)
		{
			for(int j=1;j<=19;j++)
			{
				if(map1[i][j]==(k%2)&&!vis[i][j])
				{
					flag=0;
					vis[i][j]=1;
					bfs(i,j,(k%2));//搜联通块
				}
			}
		}
		cout<<ans1<<' '<<ans2<<endl;
	}
	return 0;
}
```

---

## 作者：xzy090626 (赞：2)

问题本身很简单，每次询问由于棋盘边长（$n=19$）很小，直接 BFS 就可以了。在向当前棋子四连通的位置扩展时顺便记录有没有气，再用一个数组记录连通块的所有棋子位置，如果没有气了就删掉，同时记录 `vis` 数组以保证复杂度（显然某个位置删掉之后不可能再属于任何一个连通块，没有删也是一样。所以至多只能被访问一次）。有一个关键点是题目中说了要先删对手的再删自己的，不然就错了。

单次 BFS 复杂度 $O(n^2)$，总复杂度是 $O(n^2m)$。在 4s 的情况下比较容易。但其实也不容易，至少我赛时的代码一开始使用 `std::queue` 被卡爆了，后来改成了快读快写和手写队列才卡过，不知道是不是人傻常数大。

贴一个[赛时代码](https://www.luogu.com.cn/paste/7yiurcj7)。有点丑，慎入。

---
其实有更简单的做法。可以使用并查集维护连通块，像 BFS 一样类似地维护气，由于所有时间中棋盘上出现过的棋子个数只有 $m$ 个（因为每次询问只添加一个棋子），所以均摊一下删除操作也是 $O(m)$ 的。使用路径压缩 + 启发式合并的并查集，复杂度可以做到 $O(m)$。

---

## 作者：charlieqi (赞：1)

一道~很水~的绿题。
# 分析
我们知道：围棋棋盘是 $19\times 19$ 的，那么我们可以采取一个比较暴力的方式去枚举所有没有气的棋子并统计答案。为了降低时间复杂度，我们可以使用 $vis$ 数组记录每个点是否被遍历过（记忆化的思想）。

思路是比较简单的，但是，我们要注意一些小细节：

1. $vis$ 数组多测要清空。
2. 用 $-1$ 表示没有子。
3. `continue` 很重要！很重要！！很重要！！！

# 放代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define pr pair<int,int>
#define fi first
#define se second
const int N=20;
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
using namespace std;
int m,bla,whi,pl[N][N];
bool vis[N][N];
queue<pr>q;
vector<pr>v;
int read(){
	int x=0,y=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')y=-1;c=getchar();};
	while(isdigit(c)){x=x*10+c-48;c=getchar();};
	return x*y;
}
bool check(int x,int y){\\越界判断
	return x>=1&&y>=1&&x<N&&y<N;
}
void bfs(int x,int y,int c){\\暴力搜索+记忆化
	q.push({x,y});
	v.clear();
	bool f=0;
	while(q.size()){//套版子
		auto t=q.front();
		q.pop();
		int tx=t.fi,ty=t.se;
		if(!f)v.push_back({tx,ty});
		for(int i=0;i<4;i++){
			int x0=tx+dx[i],y0=ty+dy[i];
			if(!check(x0,y0)||pl[x0][y0]==!c)continue;
			if(pl[x0][y0]==-1){
				f=1;
				continue;
			}	
			if(vis[x0][y0])continue;
			vis[x0][y0]=1;
			q.push({x0,y0});
		}
	}
	if(f)return;
	if(c)bla+=v.size();
	else whi+=v.size();
	for(auto t:v)pl[t.fi][t.se]=-1;//删去的子
}
void solve(bool c){
	bla=whi=0;
	for(int i=1;i<N;i++){
		for(int j=1;j<N;j++)vis[i][j]=0;
	}
    //自己和对手分别遍历
	for(int i=1;i<N;i++){
		for(int j=1;j<N;j++){
			if(!vis[i][j]&&pl[i][j]==!c){
				vis[i][j]=1;
				bfs(i,j,!c);
			}
		}
	}
	for(int i=1;i<N;i++){
		for(int j=1;j<N;j++){
			if(!vis[i][j]&&pl[i][j]==c){
				vis[i][j]=1;
				bfs(i,j,c);
			}
		}
	}
	cout<<bla<<' '<<whi<<'\n';//答案
}
signed main(){
	m=read();
	for(int i=1;i<N;i++){
		for(int j=1;j<N;j++)pl[i][j]=-1;
	} 
	for(int i=1,x,y;i<=m;i++){
		x=read();
		y=read();
		pl[x][y]=i&1;
		solve(i&1);
	}
	return 0;
}
```
# 知识点
1. `BFS`
# `BFS` 好题推荐
1. [THIS](https://www.luogu.com.cn/training/533940#problems)

---

## 作者：是青白呀 (赞：1)

开两个并查集分别维护黑子和白子的连通块及其气数，放子时先计算当前位置的气数，然后和四个方向可合并的连通块作合并，然后判断四个方向的敌方连通块是否死掉，最后判断自己和四个方向的我方连通块是否死掉。对于死掉的连通块，直接 dfs 遍历每个死掉的棋子，取走的时候记得加上四周敌方的气数。由于每个棋子只会死一次，所以 dfs 是均摊的。复杂度为 $O(\alpha(m))$。不带棋盘大小的常数。

```cpp
int T,n=19*19;
int getid(int x,int y){
    return (x-1)*19+y;
}
struct bcj{
    int fa[N],val[N];
    void init(){
        rep(i,1,n)
            fa[i]=i,val[i]=0;
    }
    int find(int x){
        if(fa[x]==x)return x;
        return fa[x]=find(fa[x]);
    }
    void merge(int x,int y){
        x=find(x),y=find(y);
        if(x==y)return;
        fa[x]=y,val[y]+=val[x];
    }
    void clr(int x){
        fa[x]=x,val[x]=0;
    }
    void modify(int x,int v){
        x=find(x),val[x]+=v;
    }
    int query(int x){
        x=find(x);
        return val[x];
    }
}B[2];
bool vis[2][20][20];
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0},num[2],ynum[2];
void delp(int x,int y,int op){
    B[op].clr(getid(x,y)),num[op]--;
    vis[op][x][y]=0;
    rep(i,0,3){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx<1||tx>19||ty<1||ty>19)continue;
        if(!vis[op^1][tx][ty])continue;
        B[op^1].modify(getid(tx,ty),1);
    }
}
void dfsc(int p,int op){
    int x=(p-1)/19+1,y=p-19*(x-1);
    delp(x,y,op);
    rep(i,0,3){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx<1||tx>19||ty<1||ty>19)continue;
        if(!vis[op][tx][ty])continue;
        dfsc(getid(tx,ty),op);
    }
}
void addp(int x,int y,int op){
    int nst=getid(x,y);
    vis[op][x][y]=1;
    rep(i,0,3){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx<1||tx>19||ty<1||ty>19)continue;
        if(vis[op][tx][ty]||vis[op^1][tx][ty])continue;
        B[op].modify(nst,1);
    }
    rep(i,0,3){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx<1||tx>19||ty<1||ty>19)continue;
        if(!vis[op][tx][ty])continue;
        int nid=getid(tx,ty);
        B[op].merge(nst,nid);
    }
    rep(i,0,3){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx<1||tx>19||ty<1||ty>19)continue;
        if(!vis[op^1][tx][ty])continue;
        int nid=getid(tx,ty);
        B[op^1].modify(nid,-1);
        if(!B[op^1].query(nid))dfsc(nid,op^1);
    }
    if(!B[op].query(nst)){
        dfsc(nst,op);
        return;
    }
    rep(i,0,3){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx<1||tx>19||ty<1||ty>19)continue;
        if(!vis[op][tx][ty])continue;
        int nid=getid(tx,ty);
        B[op].modify(nid,-1);
        if(!B[op].query(nid))dfsc(nid,op);
    }
}
int m;
void solve(){
    read(m);
    B[0].init(),B[1].init();
    int op=0;
    while(m--){
        int x,y;
        read(x),read(y);
        num[op]++;
        rep(i,0,1)
            ynum[i]=num[i];
        addp(x,y,op);
        printf("%d %d\n",ynum[0]-num[0],ynum[1]-num[1]);
        op^=1;
    }
}
```

---

## 作者：Little_duck_GGG (赞：0)

### 题目意思。
在一个十九乘十九的棋盘内下棋，模拟出每一步之后，有多少个白棋，黑棋被吃掉了。
###  题目思路。
首先我们要明确一个点，那就是，如果当前这组棋子被吃掉了，那么当前这组棋子的气必为零。也就是**说这组棋子会被对手的棋子围住**。我们现在的目标就是在每步之后，搜索出棋盘中能被吃掉的棋子。

但枚举棋盘棋子是否被吃掉的顺序是什么呢？

题目中说了，如果当前这步是白棋下的，则**优先吃黑棋**，所以说，我们优先吃对方的棋子，再来吃自己的棋子。

想完以上几点，其实搜索的代码已经显而易见了。但数据范围较大，所以我们还需要一个数组去标记当前位置是否被查询过。

最后注意一点，我们可以**违反围棋的规则**，只要当前的格子没有棋子，我们都可以下。那么就会有一下情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/kr6fjdm8.png)
在围棋的规则中，红色格点是不能下的，但在此题中，因为会**优先吃掉对方棋子**，所以此行为是可被允许的。
### 最后给出代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,x,y,a[25][25],wh,bl,sum,v[25][25];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
struct node
{
	int xx,yy;
}pro[100050];
void bfs(int sx,int sy,int l)//查找被吃掉的棋子，l表示当前找的是白棋还是黑棋 
{
	queue<node> q;
	node st;
	st.xx=sx;
	st.yy=sy;
	q.push(st);	
	int ff=0;
	sum=0;
	while(!q.empty())
	{
		node t=q.front();
		q.pop();
		if(ff==0) pro[++sum]=t; //标记被吃掉的棋子位置 
		for(int i=0;i<4;i++)
		{
			int txx,tyy;//广搜模板 
			txx=t.xx+dx[i];
			tyy=t.yy+dy[i];
			if(txx<1||tyy<1||txx>19||tyy>19) continue;
			if(a[txx][tyy]==0) //此处如果发现有气，既是有非棋子的地方，则此组棋子不可被吃掉，标记 
			{
				ff=1;
				continue;
			}
			if(a[txx][tyy]!=l) continue;
			if(v[txx][tyy]==1) continue;
			v[txx][tyy]=1;
			node temp;
			temp.xx=txx;
			temp.yy=tyy;
			q.push(temp);
		}	
	}
	if(ff==1) return;//不可被吃掉就返回 
	if(l==2) wh+=sum;// 统计 
	else bl+=sum;
	for(int i=1;i<=sum;i++) a[pro[i].xx][pro[i].yy]=0;//被吃掉的地方就没有棋子了  	
	for(int i=1;i<=sum;i++) pro[i].xx=pro[i].yy=0;
}
void fun(int op)
{
	memset(v,0,sizeof(v));
	for(int i=1;i<=19;i++)//先吃对手的棋子 
	{
		for(int j=1;j<=19;j++)
		{
			if(v[i][j]==0&&a[i][j]!=op&&a[i][j]!=0)
			{
				v[i][j]=1;//标记位置 
				bfs(i,j,a[i][j]);
			} 
		}
	}
	for(int i=1;i<=19;i++)//吃自己的棋子 
	{
		for(int j=1;j<=19;j++)
		{
			if(a[i][j]==op&&v[i][j]==0)
			{	
				v[i][j]=1;
				bfs(i,j,op);
			} 
		}
	}
}
int main(){
    cin>>m;
    for(int i=1;i<=m;i++)
    {
    	cin>>x>>y;
    	wh=bl=0;
		a[x][y]=(i%2)+1;//奇数是黑棋，偶数是白棋	
		fun((i%2)+1);
    	cout<<wh<<" "<<bl<<endl;
	}
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 题目大意

模拟围棋的落子过程，然后根据围棋的气来计算每一步落子后被提子的个数。

当然强调了，每一步的落子没有限制，也就有可能某个棋子刚落下去后会直接被提掉。

### 思路

直接在落子后暴力搜索计算出相邻的棋子所在块的气，最后在计算落子位置所在块的气。

具体来说，对于从 $(x,y)$ 开始搜索的棋子，每到达一个未被访问到的同色棋子的块，就加入到集合中；每到达一个未被访问到的空位，就把该连通块的气的数目加一。

由于时限为 5s，并且棋盘的大小是 $19×19$ 的，所以复杂度为 $O(n)$，可以通过此题。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define init(x) memset (x,-1,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
vector <pair <int,int> > v;
int t,outa,outb,cnt;
int a[25][25],vis[25][25],sx[] = {0,0,1,-1},sy[] = {1,-1,0,0}; 
void search (int x,int y,int col);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();init (a);
	for (int i = 1;i <= t;++i)
	{
		int x = read (),y = read (),ty = (i & 1) ? 0 : 1;//ty = 1 为白棋
		a[x][y] = ty;outa = outb = 0;
//先处理对手的气的情况，提完子后再处理自己的气
		for (int i = 0;i < 4;++i)//处理这个棋子的相邻位置
		{
			int xx = x + sx[i],yy = y + sy[i];
			cnt = 0;v.clear ();
			if (1 <= xx && xx <= 19 && 1 <= yy && yy <= 19)
			{
				if (a[xx][yy] == (ty ^ 1) && !vis[xx][yy]) search (xx,yy,ty ^ 1);
				if (!cnt)//没有气会被提子
				{
					if (ty == 0) outb += v.size ();
					else outa += v.size ();//提子的数目即为 v 的大小
					for (auto p : v) a[p.first][p.second] = -1;//清空这些位置
				}
			}
		}
		cnt = 0;v.clear ();
		search (x,y,ty);
		if (!cnt)
		{
			if (ty == 0) outa += v.size ();
			else outb += v.size ();
			for (auto p : v) a[p.first][p.second] = -1;
		}
		for (int i = 1;i <= 19;++i)
			for (int j = 1;j <= 19;++j) vis[i][j] = 0;
		printf ("%d %d\n",outa,outb);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void search (int x,int y,int col)
{
	vis[x][y] = 1;v.push_back ({x,y});//标记
	for (int i = 0;i < 4;++i)
	{
		int xx = x + sx[i],yy = y + sy[i];
		if (1 <= xx && xx <= 19 && 1 <= yy && yy <= 19)
		{
			if (a[xx][yy] == -1) ++cnt;//空位
			if (a[xx][yy] == col && !vis[xx][yy]) search (xx,yy,col);
		}
	}
}

```

---

## 作者：sgtqwq (赞：0)

模拟题，题面需要注意的细节较多。

#### 题目描述

给一盘围棋，奇数步执黑偶数步执白，下完一手以后**先计算刚刚下完哪一方的对方的气，再计算自己一方的气，棋子可以下在任意空点上**。
#### 做法
注意到棋盘很小，所以考虑大力 bfs，每次 bfs 都搜一个连通块，如果块里面有一个点有气则整个连通块都有气，如果发现某个连通块没有气就直接把它清掉，注意到我们要先搜对方的连通块，再搜自己的，时间复杂度 $O(n^2m)$，时限宽松，可以通过。

代码很丑，就不放了。

---

## 作者：Cyx20110930 (赞：0)

# 题意简述

在一局围棋中，给你黑方与白方每一步的落子，问你每一步黑白双方有几个子被吃？

# Sol

很简单啊，我们可以每一步落子之后，对这个棋子周围的五个位置（包括自己的位置）的联通块处理即可。

# Code

```
#include <bits/stdc++.h>
using namespace std;
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int board[30][30],ans[10],n=19;
bool used[30][30];
void bfs(int x,int y){
	int col=board[x][y];
	queue<pair<int,int>> que;
	vector<pair<int,int>> v;
	que.push(make_pair(x,y));
	used[x][y]=true;
	bool ok=false;
	while(!que.empty()){
		auto [x,y]=que.front();
		que.pop();
		v.push_back(make_pair(x,y));
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<1 || nx>n || ny<1 || ny>n)
				continue;
			if(board[nx][ny]==-1)
				ok=true;
			if(board[nx][ny]!=col || used[nx][ny])
				continue;
			que.push(make_pair(nx,ny));
			used[nx][ny]=true;
		}
	}
	if(!ok){
		for(auto &[x,y]:v){
			board[x][y]=-1;
			ans[col]++;
		}
	}
	return;
}
void solve(int col,vector<pair<int,int>> &v){
	memset(used,0,sizeof(used));
	for(auto &[x,y]:v){
		if(x<1 || x>n || y<1 || y>n)
			continue;
		if(used[x][y])
			continue;
		if(board[x][y]!=col)
			continue;
		bfs(x,y);
	}
	for(auto &[x,y]:v){
		if(x<1 || x>n || y<1 || y>n)
			continue;
		if(used[x][y])
			continue;
		if(board[x][y]!=1^col)
			continue;
		bfs(x,y);
	}
	return;
}
int main(){
	memset(board,-1,sizeof(board));
	int m;
	cin>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		int col=i%2;
		board[x][y]=col;
		ans[1]=ans[0]=0;
		vector<pair<int,int>> v;
		for(int i=0;i<4;i++)
			v.push_back(make_pair(x+dx[i],y+dy[i]));
		v.push_back(make_pair(x,y));
		solve(col^1,v);
		cout<<ans[1]<<' '<<ans[0]<<endl;
	}
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有一个 $19\times 19$ 的围棋棋盘，两个人正在下简化版的围棋，一人执黑子，一人执白子，轮流落子，执黑子的人先行。每个人落子只能落到没有棋子的位置上。

定义一个棋子的气，为其四连通内的空位数量。定义两个棋子是相连的，为其中任意一个棋子位于另一个棋子的四联通范围内。定义一个棋子所在的棋子组，表示一个极大的同色棋子集合，满足对于集合中的任意一个棋子，都至少有一个相连的棋子在集合中。定义一个棋子组的气，为其中所有棋子的气总和。

当一方落子后，先检查对方的每一个棋子所在的棋子组，若该棋子组的气为 $0$，则将棋子组中的所有棋子全部提掉（移出棋盘）。然后以同样的规则，检查己方的每一个棋子所在的棋子组。

这两个人打算一共进行 $m$ 着（累计落下 $m$ 枚棋子），你需要输出每次落子后，被提的黑棋数和白棋数。

$1\leq m\leq 5\times10^5$

## 思路

感觉我做完题目会已经会下围棋了……

这是一道模拟题。

我们对于每一着，枚举棋盘上的每一个对方棋子，DFS 计算一下所在棋子组的气（就是 DFS 连通块），并且记录一下棋子组的棋子，如果气为 $0$ 就全部移除，然后枚举己方棋子，也完成上述步骤即可。

注意需要保证每一着内每一个棋子只会被搜索一次，要不然复杂度不对。

时间复杂度 $O(n^2m)$，其中 $n=19$。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

enum ChessState{
    NONE, BLACK, WHITE
};

ChessState table[25][25];
int gas;
bool vis[25][25];

int calc_gas(int x, int y){// 一个位置的棋子的气
    auto _ = [&](int x, int y){
        if(x < 1 || x > 19 || y < 1 || y > 19) return 0;// 注意出界的位置不参与到气的计算中
        return (int)(table[x][y] == NONE); 
    };
    return _(x + 1, y) + _(x - 1, y) + _(x, y + 1) + _(x, y - 1);
}

vector<pair<int,int> > group;

void dfs(int x, int y, ChessState color){
    vis[x][y] = true;
    group.push_back({x, y});// 将这个棋子加入棋子组
    gas += calc_gas(x, y);// 累加气的总和
    for(auto [i, j] : {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)}){// 枚举相连的位置
        int fx = x + i, fy = y + j;
        if(fx < 1 || fx > 19 || fy < 1 || fy > 19) continue;
        if(table[fx][fy] != color) continue;
        if(vis[fx][fy]) continue;
        dfs(fx, fy, color);
    }
}

ChessState enemy(ChessState color){
    return color == BLACK ? WHITE : BLACK;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n; cin >> n;
    ChessState now = BLACK;
    while(n--){
        int x, y;
        cin >> x >> y;
        table[x][y] = now;// 落子
        // cerr << "ROUND OF " << now << '\n';
        int he = 0, me = 0;
        for(int i=1;i<=19;i++){// 枚举对方的棋子
            for(int j=1;j<=19;j++){
                if(vis[i][j]) continue;// 保证每个棋子只会被搜索一次
                if(table[i][j] == enemy(now)){
                    group.clear();
                    gas = 0;
                    dfs(i, j, enemy(now));
                    // cerr << "ENEMY " << i << ' ' << j << ' ' << gas << '\n';
                    if(!gas){// 气为0，需要提子
                        for(auto [x, y] : group){
                            table[x][y] = NONE;
                            he++;
                        }
                    }
                }
            }
        }
        for(int i=1;i<=19;i++){// 枚举己方的棋子
            for(int j=1;j<=19;j++){
                if(vis[i][j]) continue;
                if(table[i][j] == now){
                    group.clear();
                    gas = 0;
                    dfs(i, j, now);
                    // cerr << "ME " << i << ' ' << j << ' ' << gas << '\n';
                    if(!gas){
                        for(auto [x, y] : group){
                            table[x][y] = NONE;
                            me++;
                        }
                    }
                }
            }
        }
        if(now == BLACK) cout << me << ' ' << he << '\n';// 注意输出时黑在前，白在后
        else cout << he << ' ' << me << '\n';
        now = enemy(now);// 切换到下一个玩家
        memset(vis, 0, sizeof(vis));// 清空标记数组
    }
    return 0;
}

// Written by xiezheyuan

```

---

## 作者：SUNCHAOYI (赞：0)

**【题目大意】**

模拟围棋的落子过程，然后根据围棋的气来计算每一步落子后被提子的个数。

当然强调了，每一步的落子没有限制，也就有可能**某个棋子刚落下去后会直接被提掉**。

**【思路】**

直接在落子后暴力搜索计算出相邻的棋子所在块的气，最后在计算落子位置所在块的气。

具体来说，对于从 $(x,y)$ 开始搜索的棋子，每到达一个未被访问到的同色棋子的块，就加入到集合中；每到达一个未被访问到的空位，就把该连通块的气的数目加一。

由于时限为 $4s$，并且棋盘的大小是 $19 \times 19$ 的，所以复杂度为 $O(m)$，可以通过此题。

**【代码】**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define init(x) memset (x,-1,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
vector <pair <int,int> > v;
int t,outa,outb,cnt;
int a[25][25],vis[25][25],sx[] = {0,0,1,-1},sy[] = {1,-1,0,0}; 
void search (int x,int y,int col);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();init (a);
	for (int i = 1;i <= t;++i)
	{
		int x = read (),y = read (),ty = (i & 1) ? 0 : 1;//ty = 1 为白棋
		a[x][y] = ty;outa = outb = 0;
//先处理对手的气的情况，提完子后再处理自己的气
		for (int i = 0;i < 4;++i)//处理这个棋子的相邻位置
		{
			int xx = x + sx[i],yy = y + sy[i];
			cnt = 0;v.clear ();
			if (1 <= xx && xx <= 19 && 1 <= yy && yy <= 19)
			{
				if (a[xx][yy] == (ty ^ 1) && !vis[xx][yy]) search (xx,yy,ty ^ 1);
				if (!cnt)//没有气会被提子
				{
					if (ty == 0) outb += v.size ();
					else outa += v.size ();//提子的数目即为 v 的大小
					for (auto p : v) a[p.first][p.second] = -1;//清空这些位置
				}
			}
		}
		cnt = 0;v.clear ();
		search (x,y,ty);
		if (!cnt)
		{
			if (ty == 0) outa += v.size ();
			else outb += v.size ();
			for (auto p : v) a[p.first][p.second] = -1;
		}
		for (int i = 1;i <= 19;++i)
			for (int j = 1;j <= 19;++j) vis[i][j] = 0;
		printf ("%d %d\n",outa,outb);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void search (int x,int y,int col)
{
	vis[x][y] = 1;v.push_back ({x,y});//标记
	for (int i = 0;i < 4;++i)
	{
		int xx = x + sx[i],yy = y + sy[i];
		if (1 <= xx && xx <= 19 && 1 <= yy && yy <= 19)
		{
			if (a[xx][yy] == -1) ++cnt;//空位
			if (a[xx][yy] == col && !vis[xx][yy]) search (xx,yy,col);
		}
	}
}
```

---

## 作者：luogu_gza (赞：0)

问题等价于维护一个围棋棋盘，问你每次黑子白子被提了多少。

不难 bfs 每个与下棋点四连通的点，每次 bfs 处理出连通块对应的气的数量，如果为零就删掉这个连通块。

细节是：要先删对手的再删自己的，否则就搞笑了。

细节是：为了优化，删了的连通块及时删掉，否则可能被删多次，那就很唐。

细节是：我们不需要判断出具体的气，我们只需要判断气是否大于零。那么只需要判断与该连通块相邻的点是否有任意一个是空位即可。

[code](https://www.luogu.com.cn/record/171976700)。

想要代码可以来找我。

---

## 作者：wanghonghui123 (赞：0)

#### 题目大意：

- 给定围棋规则，若四周被其他颜色的包围将被包围区域换对方棋子，判断在给定下棋步数过程中双方被吃掉的棋子个数。

### 思路：

这题我们可以使用 BFS 来解决，也就是**广度优先搜索算法**。
1. 我们可以用上述方法来识别棋子的颜色。
  
2. 四联通 $dx$ 和 $dy$ 的初始为：
   ```cpp
    int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
   ```
3. 这是一道模拟题，因此我们需要充分想象 BFS 的搜索方式。
   
4. 找到周围同颜色的棋子并且判断是否完全被包围，是则对该区域的颜色翻转并记录个数。找颜色不同的棋子同样执行 BFS 并可能翻转颜色。

5. 我们可以用递归的方式检查并移除所有新产生的无气棋子。

6. 在每次移动后，统计并记录被吃掉的黑白棋子的数量。

7. 我们需要初始化一个 $19 \times 19$ 的棋盘。

#### 注意：
- 是要先吃对手的，再吃自己的。

#### 时间复杂度
- 时间复杂度为 $\mathcal{O(n)}$。

---

