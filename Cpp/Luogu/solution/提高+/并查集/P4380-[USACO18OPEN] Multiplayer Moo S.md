# [USACO18OPEN] Multiplayer Moo S

## 题目描述

奶牛们提出了一款创新性的新游戏，令人惊讶的是她们给这款游戏取了个最没创意的名字：“Moo”。  
Moo 游戏在一个由 $N \times N$ 个正方形格子组成的棋盘上进行。一头奶牛可以通过大叫一声“哞！”然后把她的数字编号写在这个格子里来占有这个格子。

在游戏结束时，每个格子中都包含一个数。此时，如果一头奶牛创建了一个由连通的格子组成的领域，且该领域的大小不小于其他所有领域，那么这头奶牛就获胜。一个“领域”被定义为一些具有相同数字编号的格子，其中每个格子都直接与另一个同一领域中的格子通过上、下、左或右相邻（对角线不计）。

由于以单牛形式进行游戏有点无聊，奶牛们也对双牛组队进行游戏感兴趣。同一队的两头奶牛可以创建一个领域，但现在领域中的格子可以属于队伍中的任一头奶牛。

给定游戏棋盘的最终状态，请帮助奶牛们计算：  
1. 任何单头奶牛占有的最大领域包含的格子数量。  
2. 任何两头奶牛组成的队伍占有的最大领域包含的格子数量。  

注意，两头奶牛占有的领域必须同时包含队伍中两头奶牛的编号，不能仅仅包含一头。

## 说明/提示

在这个例子中，单头奶牛占有的最大领域是由五个 $9$ 组成的。如果编号为 $1$ 和 $9$ 的奶牛组队，她们可以形成一个大小为 $10$ 的领域。

供题：Brian Dean

## 样例 #1

### 输入

```
4
2 3 9 3
4 9 9 1
9 9 1 7
2 1 1 9```

### 输出

```
5
10
```

# 题解

## 作者：xiwang (赞：12)

~~千亿的STL,千亿的迭代器~~  
第一问好写，每个格子跑floodfill就好了  
起初写了个暴力版的，就是直接枚举可能的号码组合然后用第一问结果统计  
然后就爆炸了  
然后我找到了官方（？）题解，然后那代码在我的破电脑上编译不了  
然后我只好对每一组号码组合建一张图  
那么怎么搞映射呢？map  
重复边怎么去重？用map<int,set<int> >存图  
  怎么不MLE呢？靠神奇的STL  
  怎么不TLE呢？O2  
  所以我们把第一问处理出的每一个联通块缩成一个点，之后针对每一组可能的号码组合（原图中相邻的不同号码）建一张图，map搞搞映射，之后每一张新图暴力统计答案就好了  
  丑陋的代码:  
  ```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=256;
typedef pair<int,int> pii;
#define X first
#define Y second
int n,a[N][N],id[N][N],arid,clk;
struct gph{
	map<int,set<int> > g;
	map<int,int> nsz,rid,rsz;
};
map<int,gph> g1;
map<pii,gph> g2;

int dfs(gph &g,int nid,int rid){
	if(g.rid.count(nid)>0)return 0;
	g.rid[nid]=rid;
	int x=g.nsz[nid];
	for(set<int>::iterator i=g.g[nid].begin();i!=g.g[nid].end();i++){
		x+=dfs(g,*i,rid);
	}
	g.rsz[rid]=x;
	return x;
}
int fuck(gph &g){
	int re=0;
	for(map<int,set<int> >::iterator i=g.g.begin();i!=g.g.end();i++)re=max(re,dfs(g,(*i).X,++arid));
	return re;
}
void add(gph &g,int st,int ed){
	g.g[st].insert(ed);
	g.g[ed].insert(st);
	g.nsz[st]=g.nsz[ed]=1;
}
void addg2(int x1,int y1,int x2,int y2){
	int c1=a[x1][y1],c2=a[x2][y2],id1=id[x1][y1],id2=id[x2][y2];
	if(c1>c2)swap(c1,c2),swap(id1,id2);
	int r1=g1[c1].rid[id1],r2=g1[c2].rid[id2];
	pii p=pii(c1,c2);
	add(g2[p],r1,r2);
	g2[p].nsz[r1]=g1[c1].rsz[r1];                                                              
	g2[p].nsz[r2]=g1[c2].rsz[r2];  
}
int main(){
	//printf("Dioptic manifold clear.\n");
	scanf("%d",&n);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]),id[i][j]=++clk;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		add(g1[a[i][j]],id[i][j],id[i][j]);
		if(i<n&&a[i+1][j]==a[i][j])add(g1[a[i][j]],id[i][j],id[i+1][j]);
		if(j<n&&a[i][j+1]==a[i][j])add(g1[a[i][j]],id[i][j],id[i][j+1]);;
	}
	int ass1=0;
	for(map<int,gph>::iterator i=g1.begin();i!=g1.end();i++){
		ass1=max(ass1,fuck((*i).Y));
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		if(i<n&&a[i+1][j]!=a[i][j])addg2(i,j,i+1,j);
		if(j<n&&a[i][j+1]!=a[i][j])addg2(i,j,i,j+1);
	}
	int ass2=0;
	for(map<pii,gph>::iterator i=g2.begin();i!=g2.end();i++){
		ass2=max(ass2,fuck((*i).Y));
	}
	printf("%d\n%d",ass1,ass2);
	return 0;
}
```

---

## 作者：狸狸养的敏敏 (赞：10)

~~自古FJ屁事多，他的奶牛屁事也多~~


给各位带来一个好玩意儿

C++ STL库的

# **unordered_map**!!!

(需包含头文件<unordered_map>)

~~没错bits都没法用~~

另外，这是C++11里的玩意儿，如果不支持C++11的孩子还是看看楼上的吧


介绍一下哈。

unordered_map，是无序映射，（离散化的好玩意儿），他和map不同的是，map底层使用红黑平衡树实现，而unordered_map是使用hash（哈希）实现，也就是说，使用unordered_map建立映射的复杂度是……

# $O(1)!!!$

本题可以采用宽搜求解，运用Flood-Fill算法求解两问，思路如下：

第一问比较简单，枚举每一点并进行flood-fill，并且更新最大值，代码如下
```cpp
int bfs1(int x,int y) {
	int ans(0);
	queue<node>que;
	node t,s;
	t=(node) {
		x,y
	};
	mark[x][y]=1;
	que.push(t);
	while(!que.empty()) {
		t=que.front();
		que.pop();
		ans++;
		for(int i=0; i<4; i++) {
			s.x=t.x+mv[i][0];
			s.y=t.y+mv[i][1];
			if(s.x>=1&&s.x<=n&&s.y>=1&&s.y<=n&&!mark[s.x][s.y]&&mp[s.x][s.y]==mp[t.x][t.y]) {//mp[s.x][s.y]==mp[t.x][t.y]是保证下一个点和这个点是同一个数字
				mark[s.x][s.y]=1;
				que.push(s);
			}
		}
	}
	return ans;
}
```

那么第二问怎么解决呢？我们这样子考虑：

#### 对于任意一个点，我们考虑他能否与四周进行组队~~（开黑）~~，若是可以的话，将他与四周的点进行组队并连接，若四周的点均不是本身（即符合）

>两头奶牛占有的领域必须要同时包含队伍中两头奶牛的编号，不能仅仅包含一头。

#### 这个条件，那么进行Flood-Fill，并且记为数字X与数字Y已经结为一队。那么怎么记录呢？

# $unordered_{}map!!!$

注意，在判断是否允许将此点加入队列时，要判断的不仅仅是$$mp[s.x][s.y]==mp[t.x][t.y]$$

还有$$mp[s.x][s.y]$$是否与他的队友相同(**打的是友军!)

代码如下
```
int bfs2(int x,int y,int x1,int y1) {
	memset(mark,0,sizeof(mark));
	//printf("%d %d %d %d\n",x,y,x1,y1);
	int ans(0);
	int used1=mp[x][y],used2=mp[x1][y1];//used1表示自己的数字编号
    //used2表示队友的数字编号
	queue<node>que;
	node t,s;
	t=(node) {
		x,y
	};
	mark[x][y]=1;
	que.push(t);
	while(!que.empty()) {
		t=que.front();
		que.pop();
		//printf("%d %d\n",t.x,t.y);
		ans++;
		for(int i=0; i<4; i++) {
			s.x=t.x+mv[i][0];
			s.y=t.y+mv[i][1];
			if(s.x>=1&&s.x<=n&&s.y>=1&&s.y<=n&&!mark[s.x][s.y]&&(mp[s.x][s.y]==used1||mp[s.x][s.y]==used2)) {//有了上面的注释，问题就不大了
				mark[s.x][s.y]=1;
				que.push(s);
			}
		}
	}
	return ans;
}
```

完全代码
```
#include<bits/stdc++.h>
#include<unordered_map>
#define FILE(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout)
using namespace std;
int n,ans1,ans2;
int mv[4][2]= {{1,0},{-1,0},{0,1},{0,-1}};
int mp[333][333];
bool mark[333][333];
unordered_map<int,unordered_map<int,bool> >mmp;
struct node {
	int x;
	int y;
};
int bfs1(int x,int y) {
	int ans(0);
	queue<node>que;
	node t,s;
	t=(node) {
		x,y
	};
	mark[x][y]=1;
	que.push(t);
	while(!que.empty()) {
		t=que.front();
		que.pop();
		ans++;
		for(int i=0; i<4; i++) {
			s.x=t.x+mv[i][0];
			s.y=t.y+mv[i][1];
			if(s.x>=1&&s.x<=n&&s.y>=1&&s.y<=n&&!mark[s.x][s.y]&&mp[s.x][s.y]==mp[t.x][t.y]) {
				mark[s.x][s.y]=1;
				que.push(s);
			}
		}
	}
	return ans;
}
int bfs2(int x,int y,int x1,int y1) {
	memset(mark,0,sizeof(mark));
	//printf("%d %d %d %d\n",x,y,x1,y1);
	int ans(0);
	int used1=mp[x][y],used2=mp[x1][y1];
	queue<node>que;
	node t,s;
	t=(node) {
		x,y
	};
	mark[x][y]=1;
	que.push(t);
	while(!que.empty()) {
		t=que.front();
		que.pop();
		//printf("%d %d\n",t.x,t.y);
		ans++;
		for(int i=0; i<4; i++) {
			s.x=t.x+mv[i][0];
			s.y=t.y+mv[i][1];
			if(s.x>=1&&s.x<=n&&s.y>=1&&s.y<=n&&!mark[s.x][s.y]&&(mp[s.x][s.y]==used1||mp[s.x][s.y]==used2)) {
				mark[s.x][s.y]=1;
				que.push(s);
			}
		}
	}
	return ans;
}
int main() {
	//FILE("multimoo");
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			scanf("%d",mp[i]+j);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(!mark[i][j])
				ans1=max(ans1,bfs1(i,j));//第一问的Flood-fill问题都不大吧
	printf("%d\n",ans1);
	memset(mark,0,sizeof(mark));
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			for(int k=0; k<4; k++) {
				int frx=i+mv[k][0];
				int fry=j+mv[k][1];//判断周围四个点能否与当前点结成队友(组队开黑)(划掉)
				if(frx>=1&&frx<=n&&fry>=1&&fry<=n&&mp[i][j]!=mp[frx][fry]&&!mmp[mp[i][j]][mp[frx][fry]])//mp[i][j]!=mp[frx][fry]即判断mp[i][j]是否与自己组队（我 和 我 自 己 组 队）
					ans2=max(ans2,bfs2(i,j,frx,fry)),mmp[mp[i][j]][mp[frx][fry]]=mmp[mp[frx][fry]][mp[i][j]]=1;//mmp记录当前点与周围是否组过队
			}
	printf("%d\n",ans2);//华丽丽的输出
	return 0;
}
```

# The End. Thanks for your watching

---

## 作者：Aoki_灏 (赞：9)

# 关于HACK

之前我也是像第二篇题解一样的做法，但是发现这样是错的。

`(!mmp[mp[i][j]][mp[frx][fry]])`


这一句话的判断又明显的问题，如果之前已经在左上角配过了两种颜色，

但同样的颜色配对在右下角的联通块大于左上角，但因为左上角已经搜过了，此时右下角不会搜到。

例如这个数据

```
5
5 3 5 7 9
3 3 3 2 1 
8 9 10 11 12
5 5 5 5 5
3 3 3 3 3
```
正确答案是10,错解6。

或这个
```
5
1 1 9 8 8   
1 2 7 6 1
5 4 3 2 2
11 10 9 2 1
1 2 1 2 1
```
正确答案是10,错解4。

更多数据请看讨论

不加这个优化又会TLE，我又不想换算法，那怎么办呢

于是在此提供一种比较难叉掉的随机算法

~~（欢迎大家来叉掉）~~

# 题解

首先大家都知道这题是个暴力搜索，第一问很简单，直接对于每个点暴力dfs

关键是第二问，我们如何找到两种颜色来bfs

## - 1.我会枚举

既然已经说了前面一种优化是错的

所以我们就直接暴力枚举不考虑颜色。。

于是可以获得TLE一个点的好成绩

代码如下

```
#include <bits/stdc++.h>

using namespace std;
const int N=300;
const int M=1e6+10;
int mp[N][N],ans2,n,m,ans,col[M],tmp,ans1;
bool vis[N][N],flag[N][N];
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};
map<int,bool>match[M];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void dfs(int x,int y)
{
    vis[x][y]=1;
    tmp++;
    for(int i=0;i<4;i++)
    {
        int tx=x+dx[i];
        int ty=y+dy[i];
        if(!tx||!ty||tx>n||ty>n||vis[tx][ty])continue;
        if(mp[tx][ty]==mp[x][y])dfs(tx,ty);
    }
}
struct point
{
    int x,y;
};
void bfs(int stx,int sty,int sttx,int stty)//直接暴力bfs
{
    tmp=1;
    memset(flag,0,sizeof(flag));//其实这里还可以优化
    queue<point>q;
    q.push((point){stx,sty});
    flag[stx][sty]=1;
    while(!q.empty())
    {
         int x=q.front().x,y=q.front().y;
         q.pop();
         for(int i=0;i<4;i++)
         {
             int tx=x+dx[i];
             int ty=y+dy[i];
             if(!tx||!ty||tx>n||ty>n||flag[tx][ty])continue;
             if(mp[tx][ty]!=mp[stx][sty]&&mp[tx][ty]!=mp[sttx][stty])continue;
             tmp++;
             flag[tx][ty]=1;
             q.push((point){tx,ty});
         }

    }
    ans2=max(ans2,tmp);
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        mp[i][j]=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        if(!vis[i][j])tmp=0,dfs(i,j),col[mp[i][j]]=max(col[mp[i][j]],tmp),ans1=max(ans1,col[mp[i][j]]);
    printf("%d\n",ans1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
    {
         for(int k=0;k<4;k++)
         {
             int tx=i+dx[k];
             int ty=j+dy[k];
             if(!tx||!ty||tx>n||ty>n||mp[tx][ty]==mp[i][j])continue;
             bfs(i,j,tx,ty);//每次暴力找周边的点进行bfs
         }
     }
     printf("%d",ans2);
    return 0;
}
```

## - 2.我会随机化

基于之前的枚举，我们加入随机化操作。

### 1.我会rand_shuffle

之前是从头枚举到尾，这一次我们用rand_shuffle随机一个排列，按这个顺序进行bfs

我们惊奇的发现，成功A掉了这题，包括hack的数据！！！

当然我们还要加入卡时间操作

第一种随机化操作，正确性还是比较高的
```
    pair<int,int>rak[N*N];
    int cnt=0;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
      rak[++cnt]=make_pair(i,j);
      random_shuffle(rak+1,rak+1+cnt);
      int t=1;
     while (t <= cnt && t <= n * n && (double)clock() / CLOCKS_PER_SEC < 0.9) 
     {
     	  int i=rak[t].first,j=rak[t].second;
     	 for(int k=0;k<4;k++)
         {
             int tx=i+dx[k];
             int ty=j+dy[k];
             if(!tx||!ty||tx>n||ty>n||mp[tx][ty]==mp[i][j])continue;
             bfs(i,j,tx,ty);
         }
     	t++;
     }
```

### 2.我还会直接暴力rand()
 
我们不用rand_shuffle一个顺序，直接每次rand两个点，

虽然有rand到两个相同点的机率，但是这样被叉掉 的机率很高

还是rand_shuffle更优秀

```
   srand(unsigned(time(NULL)));
    for(int s=1;s<=60000;s++)
    {
        if( (double)clock() / CLOCKS_PER_SEC >= 0.9)break;
        int i=rand()%n+1,j=rand()%n+1;
         for(int k=0;k<4;k++)
         {
             int tx=i+dx[k];
             int ty=j+dy[k];
             if(!tx||!ty||tx>n||ty>n||mp[tx][ty]==mp[i][j])continue;
             bfs(i,j,tx,ty);
         }
    }
    
```

## - 3.我还会时间戳优化

我们发现在每次bfs的过程中其实没必要每次都memset一下，

把`flag`变成`int`类型，增加一个时间变量`TIM_CNT`

```
void bfs(int stx,int sty,int sttx,int stty)
{
    tmp=1;
    TIM_CNT++;//时间戳优化
    queue<point>q;
    q.push((point){stx,sty});
    flag[stx][sty]=TIM_CNT;
    while(!q.empty())
    {
         int x=q.front().x,y=q.front().y;
         q.pop();
         for(int i=0;i<4;i++)
         {
             int tx=x+dx[i];
             int ty=y+dy[i];
             if(!tx||!ty||tx>n||ty>n||flag[tx][ty]==TIM_CNT)continue;
             if(mp[tx][ty]!=mp[stx][sty]&&mp[tx][ty]!=mp[sttx][stty])continue;
             tmp++;
             flag[tx][ty]=TIM_CNT;//把flag赋值为当前时间
             q.push((point){tx,ty});
         }

    }
    ans2=max(ans2,tmp);
}
```
我们会发现这样就又快了接近1000ms，是真的非常有用

至此，我们发现随机化真的难卡掉，可以说除了慢了一些真的非常优秀。



---

## 作者：Mandy (赞：7)


题目来源 : [luogu4380](https://www.luogu.org/problem/P4380)

同步于我的 blog： [my blog](https://www.cnblogs.com/Mandy-H-Y/p/11529663.html)

# 分析

## Part 1 写在前面

看到题解里好多大佬用STL，蒟蒻瑟瑟发抖，打了两遍BFS，~~过了~~。

这道题本身是刷并查集时刷到的，然而发现自己用并查集想不到第二问该怎么做……

（不过luogu题解里有大佬是用的并查集）

果断放弃了并查集的思路重新思考后，发现这道题到是用BFS染色可以做。


## Part 2 BFS ？

第一问倒是好想，标记连通块，统计连通块的大小，最后输出最大值就好。

```cpp

void bfs1(int sx,int sy){
    ++tot;//连通块的编号 
    color[tot] = a[sx][sy];//记下连通块的颜色 
    queue<Node>q;
    q.push((Node){sx,sy});
    vis[sx][sy] = tot;//标记起点 
    while(!q.empty()){
        Node u = q.front();
        q.pop();
        cnt[tot]++;//记连通块的数量 
        for(int i = 0;i < 4; ++ i){
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];
            
            if(nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
            if(!vis[nx][ny] && a[nx][ny] == a[sx][sy]){
                q.push((Node){nx,ny});
                vis[nx][ny] = tot;//保证只进一次队 
                continue;
            } 
            
            if(vis[nx][ny] && vis[nx][ny] < tot){
                eadd(tot,vis[nx][ny]); 
                eadd(vis[nx][ny],tot); //连双向边 
            }
        }
    }
    ans = max(ans,cnt[tot]);
}

```


第一问主模块：


```cpp
//-----------------第一问 
    for(int i = 1;i <= n; ++ i)
        for(int j = 1;j <= n; ++ j){
            if(!vis[i][j]) bfs1(i,j);
        }
    put(ans);puts("");


```


关键是第二问。



看题：

>同一队的两头奶牛像之前一样可以创建一个领域，但是现在领域中的格子可以属于队伍中的任一头奶牛。

>两头奶牛占有的领域必须要同时包含队伍中两头奶牛的编号，不能仅仅包含一头。


也就是**只包含两个颜色的最大连通块**

我们可以思考：

**最后得到的答案连通块，一定是由某个单色连通块和另一个相连的不同颜色的连通块扩展所得。**


这样，

**我们就可以在第一问寻找连通块的时候，为每个连通块编号，将这个连通块跟与之相邻的联通块之间加一条无向边，这样可以保证每一条边的两端颜色都是不同的。**


**在第二问时，按顺序遍历每一个联通快，并将其跟与它相连的连通块组成组合，一起扩展，求出最大的组合连通块即可**

```cpp
void bfs2(int s1,int s2){
    queue<int>q;
    num++;//num是方案的编号 （双色连通块的编号） 
    int tmp = 0;
    q.push(s2);
    q.push(s1);
    used[s1] = num;
    used[s2] = num; //不在同一方案中走环 
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        tmp += cnt[u];
        for(int i = first[u];i;i = edge[i].nt){
            int v = edge[i].v;
            if(used[v] == num) continue;
            if(color[v]!=color[s1] && color[v]!=color[s2]) continue;
            used[v] = num;
            q.push(v);
        } 
    }
    ans = max(ans,tmp);
}
```



直接将这样的代码交上去，超时，不过有90分

但是我们有优化:

## Part 3 优化

### 优化 1 遍历边优化

还记得我再将第二问的时候特别强调了一句话：

>这样可以保证每一条边的两端颜色都是不同的

题目中的第二问要求：**包含且仅包含两头牛**

所以，一条边（u，v），确定了包含u,v的方案，

（注意不是包含u,v的颜色的方案，因为有可能有与u,v颜色相同的方案，只是和u，v不连通。这就是另一个方案了）

而u，v颜色不同

所以 **一条边就代表一个方案**

这样，我们在遍历到有标记的边时，可以直接跳过，因为已经遍历过这种方案了

这样可以保证每条边只遍历一次

```cpp
if(usededge[j]) continue;
usededge[j] = 1;usededge[j^1] = 1;
//标记边和反向边
```


但是其实有些地方还是不必要遍历的，因为连通块是一个图，有环，在便历时因为标记点、不走环的原因，不一定把连通块中所有的边都遍历了，所以不一定都标记完，下一次可能还会走到这些没标记的边，不过还没想好怎么优化，只有用标记点稍微优化一下。

### 优化 2 遍历点优化

跟边优化其实有一点重合，没有边优化强大，但我还是要说。~~蚊子肉也是肉~~

因为我们是按顺序来的，**遍历完一个点后，就是把这个点的所有方案都遍历完了。**

所以遇到比自己小的点，一定是已经遍历过的，那么这个方案也被遍历过了，就可以直接跳过

```cpp

if(v<u) continue;


```


### 优化 3 答案优化

如果答案大于了面积的一半，就可以直接输出了

```cpp
if(ans>n*n/2) break;
```

  
至此，就可以过掉这道题啦

# 代码

```cpp
/*************************
User：Mandy.H.Y
Language:c++
Problem:luogu 4380
*************************/
#include<bits/stdc++.h>

using namespace std;

const int maxn = 62505;

int q,n,cnt[maxn],size = 1,first[maxn];
//size = 1,便于找到反向边 
int color[maxn],num;
int a[255][255];
int vis[255][255];
int used[maxn];
bool usededge[maxn<<2];

int ans = 0,tot;
int dx[5] = {0,0,1,-1};
int dy[5] = {1,-1,0,0};

struct Edge{
    int v,nt;
}edge[maxn << 2];
struct Node{
    int x,y;
};
template<class T>inline void read(T&x){
    x = 0;char ch = getchar();bool flag = 0;
    while(!isdigit(ch)) flag |= ch == '-',ch = getchar();
    while(isdigit(ch)) x = (x << 1) + (x <<3) + (ch ^ 48),ch = getchar();
    if(flag) x = -x;
} 

template<class T>void putch(const T x){
    if(x > 9) putch(x / 10);
    putchar(x % 10 | 48); 
} 

template<class T>void put(const T x){
    if(x < 0) putchar('-'),putch(-x);
    else putch(x);
}

void file(){
    freopen("4380.in","r",stdin);
//    freopen("4380.out","w",stdout);
}

void readdata(){
    read(n);
    for(int i = 1;i <= n; ++ i)
        for(int j = 1;j <= n; ++ j)
            read(a[i][j]);
}

void eadd(int u,int v){
    edge[++size].v = v;
    edge[size].nt = first[u];
    first[u] = size;
}

void bfs1(int sx,int sy){
    ++tot;//连通块的编号 
    color[tot] = a[sx][sy];//记下连通块的颜色 
    queue<Node>q;
    q.push((Node){sx,sy});
    vis[sx][sy] = tot;//标记起点 
    while(!q.empty()){
        Node u = q.front();
        q.pop();
        cnt[tot]++;//记连通块的数量 
        for(int i = 0;i < 4; ++ i){
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];
            
            if(nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
            if(!vis[nx][ny] && a[nx][ny] == a[sx][sy]){
                q.push((Node){nx,ny});
                vis[nx][ny] = tot;//保证只进一次队 
                continue;
            } 
            
            if(vis[nx][ny] && vis[nx][ny] < tot){
                eadd(tot,vis[nx][ny]); 
                eadd(vis[nx][ny],tot); //连双向边 
            }
        }
    }
    ans = max(ans,cnt[tot]);
}

void bfs2(int s1,int s2){
    queue<int>q;
    num++;//num是方案的编号 （双色连通块的编号） 
    int tmp = 0;
    q.push(s2);
    q.push(s1);
    used[s1] = num;
    used[s2] = num; //不在同一方案中走环 
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        tmp += cnt[u];
        for(int i = first[u];i;i = edge[i].nt){
            int v = edge[i].v;
            if(used[v] == num || v < s1) continue;//优化2 
            if(color[v]!=color[s1] && color[v]!=color[s2]) continue;
            if(usededge[i]) return;//优化1 
            //这里直接return，因为是一个方案都遍历过
            //这里也要加上这个剪枝， 因为有可能是上一次双色连通块判断点的时候就返回了，就没有标记边
            //主程序里边没剪完 
            usededge[i] = 1;usededge[i^1] = 1;//标记边与反向边 
            used[v] = num;
            q.push(v);
        } 
    }
    ans = max(ans,tmp);
}

void work(){
//-----------------第一问 
    for(int i = 1;i <= n; ++ i)
        for(int j = 1;j <= n; ++ j){
            if(!vis[i][j]) bfs1(i,j);
        }
    put(ans);puts("");
//-----------------第二问 
    ans = 0;
    int maxans = (n*n)>>1;
    for(int i = 1;i <= tot; ++ i){//按序遍历单色连通块 
        for(int j = first[i];j;j = edge[j].nt){
            int v = edge[j].v;
            if(v <= i) continue;//优化2 
            if(color[v] == color[i]) continue;
            if(usededge[j]) continue;
            //这里先剪一部分边，前面遍历过的双色连通块里的边不一定都标记完了 
            usededge[j] = 1;usededge[j^1] = 1;//优化1 
            bfs2(i,v);
            if(ans > maxans) break; //优化3 
        }
    }
    put(ans);
} 

int main(){
//    file();
    readdata();
    work();
    return 0;
}

```


---

## 作者：Shunpower (赞：5)

## 思路

第一问可以直接在给的地图上 Flood-Fill，可以 BFS 也可以并查集找连通块，时间复杂度差不多。

第二问比较难。首先可以想到的是暴力，对于一个连通块找与它相连的另一个连通块，然后试图把这两个连通块组合，每次去计算一下。

但时间复杂度非常高，所以考虑时间复杂度低的做法。接下来介绍这种做法。

### 1.1 第一步

既然要给连通块找与它相连的连通块，不妨把连通块看成一个点，然后对于它相连的连通块建无向边，这样就可以较快地知道它周围的连通块。由这些连通块得到的图上每个点存在点权，点权即为对应连通块的大小。

这一步可以放在解决第一问的时候顺便做。

注意要给每个连通块重新编号，否则对于两块属于同一人但分开的连通块，你的程序会认为是同一个连通块。

### 1.2 第二步

对于相邻的连通块建无向边后，你便可以在得到的图里，针对每一个连通块与它相邻的连通块做 BFS 算第二问的答案，可惜还是太慢了，所以考虑更改 BFS 的方式。

容易发现一种卡掉这种做法的输入：

```
250
1 2 1 2 1 2 ...
2 1 2 1 2 1 ...
1 2 1 2 1 2 ...
...
```

在这种输入里，每一个点 BFS 都会一直扩展到整个棋盘，因此我们的算法就被卡成了 $O(N^4)$，所以考虑更好的方法。

容易想到在这道题里，多次走重复的边没有任何意义，因此开一个 $\texttt{map}$ 存边是否走过。

在避免走重复边的同时也要记录是否走了重复点。注意在这里 BFS 的时候，每次 BFS 前要清掉标记点的数组，而不要清掉标记边的数组。

在 BFS 内要写检查是否走到了重复边的代码，如果检查到了那么这次 BFS 没有意义，直接退出 BFS。

在每次 BFS 中，如果不能够再扩展且不是无意义的 BFS，则把 BFS 中遇到的连通块的大小求和最后和答案取 $\max$。

## 代码

前半部分将详细解释各部分代码的打法，后面一小部分会讲如何卡常通过 #9，#10，hack。

### 2.1 解决第一问

使用一个 $\texttt{queue}$ 进行 BFS 找连通块，注意这里我们算出来的东西不只是连通块（务必仔细看它们的作用，第二问将非常依赖它们）：

- $tnt$ 是编号，来一个新的连通块给一个新的编号。最终的编号是互不相同的。
- $cnt$ 用于存储该位置所在连通块的编号。
- $is$ 用于存储该编号下的连通块的实际值。
- $num$ 用于存储该编号表示的连通块大小。


```
for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
		if(!vis[i][j]){
			int sum=0;
			vis[i][j]=1;
			q.push(mp(i,j));//初始化
			while(!q.empty()){
				sum++;
				int x=q.front().first;
				int y=q.front().second;
				cnt[x][y]=tnt;//告诉这个点所在连通块的编号
				q.pop();//记得 pop
				for(int p=0;p<4;p++){
					int yh=x+dx[p],hx=y+dy[p];
					if(yh>n||hx>n||yh<1||hx<1||vis[yh][hx]||a[yh][hx]!=a[x][y]){
						continue;
					}
					vis[yh][hx]=1; 
					q.push(mp(yh,hx));//记得 push
				}
			}
			num[tnt]=sum;//处理编号为 tnt 的连通块的大小
			is[tnt]=a[i][j];//处理编号为 tnt 的连通块的实际值
			tnt++;
			ans=max(ans,sum);
		}
	}
}
cout<<ans<<endl;
```

### 2.2 相邻连通块建边

从这里开始，对连通块的操作都在它们的编号上进行，而不会对棋盘进行操作。

$n^2$ 枚举任意两点，先检查它们是否在同一连通块内且在棋盘范围内（使用刚刚算出来的 $cnt$ 检查），再用 $\texttt{map}$ 检查分别所在的连通块是否已经建边（防止建重边提升效率）。

如果通过了所有检查，将这两个连通块间连边并标记它们已经连边。

```
for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
		for(int p=0;p<4;p++){
			int yh=i+dx[p],hx=j+dy[p];
			if(yh>n||hx>n||yh<1||hx<1||cnt[yh][hx]==cnt[i][j]){
				continue;
			}
			if(mup.count(mp(cnt[i][j],cnt[yh][hx]))){
				continue;
			}
			vp[cnt[i][j]].push_back(cnt[yh][hx]);
			vp[cnt[yh][hx]].push_back(cnt[i][j]);
			mup[mp(cnt[i][j],cnt[yh][hx])]=mup[mp(cnt[yh][hx],cnt[i][j])]=1;
		}
	}
}
```

连完边之后，连通块就变成了点，相邻的连通块建了边，原题就变成了图论。

### 2.3 对于每个点枚举每个与它相邻的点

这一步比较复杂，因此再做拆分讲解。

在这一段里面，点和连通块的意思是一样的。

#### 2.3.1 BFS 之前的准备

用一个 $\texttt{map}$（此处的 $muup$） 去标记走过的边。还要使用一个数组（此处的 $muuup$）去标记走过的点。BFS 开始之前要初始化。

使用 `q1=queue<int>()` 可以高效率地清空队列。


```
for(int i=1;i<tnt;i++){
	for(int j=0;j<vp[i].size();j++){
		int tql=vp[i][j];//取出相邻点
		if(muup.count(mp(i,tql))){//若这两点间的边曾经走过，直接判定这次 BFS 没有意义。
			continue;
		}
        memset(muuup,0,sizeof(muuup));//把清空放在判定之后可以减少很多无意义的清空，正是因此，我在这里卡常卡了很久
		int sum=num[i]+num[tql];//sum 初始值为两个连通块的大小和，后面我们扩展的时候不会计算初始的两个连通块
		muuup[tql]=muuup[i]=true;//标记初始的两个连通块已经被走过。
		muup[mp(i,tql)]=muup[mp(tql,i)]=true;//标记这两个连通块之间的边走过
		q1=queue<int>();
		q1.push(i);
		q1.push(tql);
        //在这里接 2.3.2 的程序
	}
}
```

#### 2.3.2 BFS 的扩展

使用一个 $\texttt{bool}$ 型变量（这里的 $f$）标记这次 BFS 是否无意义。如果被标记了那么接下来的 BFS 内容都不能继续。最终退出取相邻点的循环后，程序会直接回到选两个相邻连通块的循环。

在 BFS 的过程中，每次扩展与我们之前选的连通块有相同颜色的点进行扩展（如之前选的颜色为 $3,1$ 的两个连通块，那么扩展过程中我们只能走颜色为 $3,1$ 的点）。

```
while(!q1.empty()){
	int x=q1.front();
	q1.pop();
	for(int k=0;k<vp[x].size();k++){
		int tqll=vp[x][k];
		if(f||muuup[tqll]||(is[tqll]!=is[i]&&is[tqll]!=is[tql])){//这里筛除了被走过的点和颜色不行的点，这里说明了 is 数组的作用
			continue;
		}
		if(muup[mp(x,tqll)]){//走到了曾经走过的边，标记这次 BFS 无意义。
			f=true;
		}
		if(!f){
			muuup[tqll]=1;//标记这个点已经走过
			muup[mp(x,tqll)]=muup[mp(tqll,x)]=1;//标记这条边已经走过
			q1.push(tqll);//扩展这个新点
			sum+=num[tqll];//sum 要加上这个连通块的大小。
		}
	}
	if(f){
			break;//退出 BFS 的过程
	}
} 
if(!f){//只有在 BFS 有效时才将 sum 和目前的答案比较
	ans2=max(ans2,sum);
}
```

最后把这份代码[交上去](https://www.luogu.com.cn/record/59234622)，你会发现无论是原题记录还是测试讨论区 hack 的[记录](https://www.luogu.com.cn/record/59236711)，最慢都跑了 $900ms$ 以上。因此你可以进行一些常数优化避免因为电脑配置的不同超时。

### 2.4 简单的剪枝

容易发现这道题里面，若算出的答案达到了棋盘大小的一半那么这个答案将会是最终答案，不必继续 BFS。因此可以将这个代码：

```
if(!f){
	ans2=max(ans2,sum);
}
```

变成

```
if(!f){
	if(sum>=sq){
		cout<<sum<<endl;
		return 0;
	}
	ans2=max(ans2,sum);
}
```

注意这里要在前面加上一句`sq=(n*n)>>1`。

于是[原题的记录](https://www.luogu.com.cn/record/59237377)中测试点 9 跑到了 $500ms$，测试点 10 也空出了 $50ms$。

[hack 的记录](https://www.luogu.com.cn/record/59237526)也跑到了 $500ms$。

## AC CODE

代码已经分段给出。

[AC 记录](https://www.luogu.com.cn/record/59237377)

---

## 作者：tribool4_in (赞：3)

### 前言：
此题解非正解（~~我是不会承认我不会正解的~~），只能写个暴力啦，况且暴力不开 $O2$ 似乎也能过（只能怪数据太弱）

##  第一问

似乎没啥好说的，$Dfs$ 或 $Bfs$ 并运用 Flood-Fill 算法（话说我原来还不知道这个连通块算法有这个名字）求连通块即可 ~~板子大法好~~。

上代码：

```cpp
int bfs1(int x, int y) {
	int ans(0);
	queue<node> que;
	node t, s;
	t = (node){x, y};
	mark[x][y] = 1;
	que.push(t);
	while (!que.empty()) {
		t = que.front();
		que.pop();
		ans++;
		for (int i = 0; i < 4; i++) {
			s.x = t.x + dxy[i][0];
			s.y = t.y + dxy[i][1];
			if (s.x >= 1 && s.x <= n && s.y >= 1 && s.y <= n && !mark[s.x][s.y] && mp[s.x][s.y] == mp[t.x][t.y]) {
				mark[s.x][s.y] = 1;
				que.push(s);
			}
		}
	}
	return ans;
}
```

##  第二问

上暴力！

**对于每两个相邻的点，判断它们能否组队，如果可以则计算组队后的最大领域即可。**

但是，要是搜重复了呢？要知道这是必然发生的。咋办呢？

MAP 大法好！！！

**定义 ``map<int, map<int, bool> > vis;`` ，而 ``vis[a][b]`` 表示这两点是否已经试组队过，再在暴力时判断一下即可。**

上代码~~菜~~：

```cpp
int bfs2(int x, int y, int x1, int y1) {
	memset(mark, 0, sizeof(mark));
	int ans(0);
	int used1 = mp[x][y], used2 = mp[x1][y1];
	queue<node> que;
	node t, s;
	t = (node){x, y};
	mark[x][y] = 1;
	que.push(t);
	while (!que.empty()) {
		t = que.front();
		que.pop();
		ans++;
		for (int i = 0; i < 4; i++) {
			s.x = t.x + dxy[i][0];
			s.y = t.y + dxy[i][1];
			if (s.x >= 1 && s.x <= n && s.y >= 1 && s.y <= n && !mark[s.x][s.y] && (mp[s.x][s.y] == used1 || mp[s.x][s.y] == used2)) {
				mark[s.x][s.y] = 1;
				que.push(s);
			}
		}
	}
	return ans;
}
```

主程序部分：

```cpp
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= n; j++) {
		for (int k = 0; k < 4; k++) { // 每两个相邻的点 
			int frx = i + dxy[k][0];
			int fry = j + dxy[k][1];
			if (frx >= 1 && frx <= n && fry >= 1 && fry <= n && mp[i][j] != mp[frx][fry] && !vis[mp[i][j]][mp[frx][fry]]) {
				ans2 = max(ans2, bfs2(i, j, frx, fry)), vis[mp[i][j]][mp[frx][fry]] = vis[mp[frx][fry]][mp[i][j]] = 1;
			}
		}
	}
}
```

最终代码:

```cpp
#include <bits/stdc++.h>
const int N = 3e2 + 5;
using namespace std;
inline int read() {
	int s=0, w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int n, ans1, ans2;
int dxy[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int mp[N][N];
bool mark[N][N];
map<int, map<int, bool> > vis;
struct node {
	int x;
	int y;
};
int bfs1(int x, int y) {
	int ans(0);
	queue<node> que;
	node t, s;
	t = (node){x, y};
	mark[x][y] = 1;
	que.push(t);
	while (!que.empty()) {
		t = que.front();
		que.pop();
		ans++;
		for (int i = 0; i < 4; i++) {
			s.x = t.x + dxy[i][0];
			s.y = t.y + dxy[i][1];
			if (s.x >= 1 && s.x <= n && s.y >= 1 && s.y <= n && !mark[s.x][s.y] && mp[s.x][s.y] == mp[t.x][t.y]) {
				mark[s.x][s.y] = 1;
				que.push(s);
			}
		}
	}
	return ans;
}
int bfs2(int x, int y, int x1, int y1) {
	memset(mark, 0, sizeof(mark));
	int ans(0);
	int used1 = mp[x][y], used2 = mp[x1][y1];
	queue<node> que;
	node t, s;
	t = (node){x, y};
	mark[x][y] = 1;
	que.push(t);
	while (!que.empty()) {
		t = que.front();
		que.pop();
		ans++;
		for (int i = 0; i < 4; i++) {
			s.x = t.x + dxy[i][0];
			s.y = t.y + dxy[i][1];
			if (s.x >= 1 && s.x <= n && s.y >= 1 && s.y <= n && !mark[s.x][s.y] && (mp[s.x][s.y] == used1 || mp[s.x][s.y] == used2)) {
				mark[s.x][s.y] = 1;
				que.push(s);
			}
		}
	}
	return ans;
}
int main() {
	// freopen("multimoo.in", "r", stdin);
	// freopen("multimoo.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			mp[i][j] = read();
	for (int i = 1; i <= n; i++) // 第一问 
		for (int j = 1; j <= n; j++)
			if (!mark[i][j])
				ans1 = max(ans1, bfs1(i, j)); // 枚举每个点求连通块 
	printf("%d\n", ans1);
	
	memset(mark, 0, sizeof(mark));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < 4; k++) { // 每两个相邻的点 
				int frx = i + dxy[k][0];
				int fry = j + dxy[k][1];
				if (frx >= 1 && frx <= n && fry >= 1 && fry <= n && mp[i][j] != mp[frx][fry] && !vis[mp[i][j]][mp[frx][fry]]) {
					ans2 = max(ans2, bfs2(i, j, frx, fry)), vis[mp[i][j]][mp[frx][fry]] = vis[mp[frx][fry]][mp[i][j]] = 1;
				}
			}
		}
	}
	printf("%d\n", ans2);
	return 0;
}
```


---

## 作者：曹老师 (赞：2)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco18open-mulmoo.html)

**这是洛谷目前(2018年8月21日16:38:14)跑的最快的并查集做法的代码，被搜索和剪枝虐惨了啊！**

对于第一问，还是很好求的，可以搜索求，可以并查集求，但还是建议并查集求，因为我们第二问要用到，**第一问就是把两个相同颜色(以下及代码中都用的颜色来表示)合并，然后求一个最大的带权并查集就好**，我是按执合并的。

第二问，我们把第一问中求出来的每个并查集的代表元给找出来，放到一个动态数组中，接下来就是加边，为了防止多加边，只加右面和下面的边就好，如果说颜色不相同，就加一条边，**所谓加边，其实就是存下这条边的起点，终点，还有颜色。**然后按照颜色排一下序，这样就会先连颜色比较小的连的边，排序也正是为了后面的$while$循环，然后保存一下此时每个并查集的大小，**每次连完两个有相同颜色的联通块，就回溯一下，再把保存下来的并查集大小放回去，保持刚建完图的状态**。

## Code ##

**注释掉的部分为未优化前，~~懒~~就不删掉了**
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

const int L = 255 , L2 = 62505;
struct Seg {
	int from , to , color1 , color2;
};
Seg seg[2*L2];
int n , map[L][L] , ans1 , ans2 , tot = 0;
int fa[L2] , size[L2] , num[L2];
vector<int>v[1000005];

template <typename T> inline void read(T &x) {
    int c = getchar();
    bool f = false;
    for (x = 0; !isdigit(c); c = getchar()) {
        if (c == '-') {
            f = true;
        }
    }
    for (; isdigit(c); c = getchar()) {
        x = x * 10 + c - '0';
    }
    if (f) {
        x = -x;
    }
}

void put(int x)  
{  
    int num = 0; char c[15];
    while(x) c[++num] = (x%10)+48, x /= 10;
    while(num) putchar(c[num--]);
    putchar('\n'); 
}

int mymx(int x , int y) {
	return x>y?x:y;
}

void myswp(int &x , int &y) {
	int t = x;
	x = y;
	y = t;
}

bool cmp(Seg a , Seg b) {
	if(a.color1 == b.color1)
		return a.color2 < b.color2;
	return a.color1 < b.color1;
}

void init() {
	for(int i=1; i<=n*n; i++) {
		fa[i] = i;
		size[i] = 1;
	}
}

int find(int x) {
	if(fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}

void merge(int x , int y) {
	int t1 = find(x) , t2 = find(y);
	if(t1 == t2)
		return ; 
	if(size[t2] > size[t1]) 
		myswp(t1 , t2);
	fa[t2] = t1;
	size[t1] += size[t2];
}

void add(int num1 , int num2 , int x , int y , int p) {
	if(p == 1) {
		tot++;
		seg[tot].from = find(num1);
		seg[tot].to = find(num2);
		seg[tot].color1 = min(map[x][y] , map[x+1][y]);
		seg[tot].color2 = mymx(map[x][y] , map[x+1][y]);		
	} else {
		tot++;
		seg[tot].from = find(num1);
		seg[tot].to = find(num2);
		seg[tot].color1 = min(map[x][y] , map[x][y+1]);
		seg[tot].color2 = mymx(map[x][y] , map[x][y+1]);			
	}
}

void Reback(int x) {
	for(int i=0; i<v[x].size(); i++) {
		int u = v[x][i];
		fa[u] = u;
		size[u] = num[u];
	}
}

int main() {
	read(n);
	//scanf("%d",&n);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			read(map[i][j]);
		//	scanf("%d",&map[i][j]);
	init();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) {
			if(i != n && map[i][j] == map[i+1][j])
				merge((i-1)*n+j , i*n+j);
			if(j != n && map[i][j+1] == map[i][j])
				merge((i-1)*n+j , (i-1)*n+j+1);
			ans1 = mymx(ans1 , size[find((i-1)*n+j)]);
		}
	//cout<<ans1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) {
			int x = (i-1)*n+j;
			if(find(x) == x)
				v[map[i][j]].push_back(x);
		}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) {
			if(i != n && map[i][j] != map[i+1][j]) 
				add((i-1)*n+j , i*n+j , i , j , 1);
			if(j != n && map[i][j] != map[i][j+1])
				add((i-1)*n+j , (i-1)*n+j+1 , i , j , 2);
		}
	sort(seg+1 , seg+tot+1 , cmp);
	for(int i=1; i<=n*n; i++)
		num[i] = size[i];
	for(int i=1; i<=tot;) {
		int color1 = seg[i].color1 , color2 = seg[i].color2;
		while(seg[i].color1 == color1 && seg[i].color2 == color2) {
			merge(seg[i].from , seg[i].to);
			ans2 = mymx(ans2 , size[find(seg[i].from)]);
			i++;
		}
		Reback(color1);
		Reback(color2);
	}
	put(ans1);put(ans2); 
//	printf("%d\n%d",ans1,ans2);
	return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P4380

---

## 作者：Hooch (赞：0)

### 题目大意

第一问：求最大的联通块的大小。

第二问：求含有两种数值的联通块的最大大小。

### 题目思路

第一问很明显就是送的，上 floodfill 的板子就可以解决。

第二问由于是求含有两种颜色的，所以要从一个位置往上下左右找一种不同数值的位置，再用这两个位置的不同的颜色进行 bfs。

显然，一个位置枚举是 $O(n^2)$ 的，而进行 floodfill 就又是 $O(n^2)$ 的，总的是 $O(n^4)$，不可过，必须剪枝。

- 剪枝 1：

可以只枚举下方和右方的位置，优化到 $\frac{1}{2}$。

2.69s -> 1.73s

但还是过不了。

- 剪枝 2：

把搜到的每一个位置以及和它组合的数值用 map 判重，如果之前考虑过就 ```return 0```。

1.73s -> 884ms

然后就愉悦地 AC 了。

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i(j); i <= n; ++i)
#define rep2(i, j, n) for (int i(j); i >= n; --i)
using namespace std;
const int N = 255;
int n, a[N][N], sz[N][N], mx[4] = {0, 0, -1, 1}, my[4] = {1, -1, 0, 0}; bool vis[N][N], lst[N][N], final[N][N][4];
map <int, bool> v[N][N];
struct node {int x, y; node(int sx, int sy) {x = sx, y = sy;}} ;
inline int read(int &x) {
	x = 0; char ch = getchar(); int f = 1;
	while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();}
	while (isdigit(ch)) {x = (x << 1) + (x << 3) + (ch & 15); ch = getchar();}
	x *= f; return 0;
}
inline int bfs(int i, int j) { // 第一问找联通块 
	queue <node> q; q.push(node(i, j)); lst[i][j] = 1; int cnt = 0;
	while (!q.empty()) {
		node t = q.front(); q.pop(); ++cnt;
		rep1(i, 0, 3) {
			int nx = mx[i] + t.x, ny = t.y + my[i];
			if (nx && ny && nx <= n && ny <= n)
				if (!lst[nx][ny] && !vis[nx][ny] && a[t.x][t.y] == a[nx][ny]) {
					lst[nx][ny] = vis[nx][ny] = 1;
					q.push(node(nx, ny));
				}
		}
	}
	q.push(node(i, j));
	while (!q.empty()) {
		node t = q.front(); q.pop(); sz[t.x][t.y] = cnt;
		rep1(i, 0, 3) {
			int nx = t.x + mx[i], ny = t.y + my[i];
			if (nx && ny && nx <= n && ny <= n)
				if (lst[nx][ny]) {
					lst[nx][ny] = 0;
					q.push(node(nx, ny));
				}
		}
	} return 0;
}
inline int bfs2(int x, int y, int cl) {
	queue <node> q; q.push(node(x, y)); memset(vis, 0, sizeof vis); vis[x][y] = 1; int ans = 0;
	if (v[x][y].count(cl)) return 0; v[x][y][cl] = 1; // 判重，剪枝 2 
	while (!q.empty()) {
		node t = q.front(); q.pop(); ++ans; v[t.x][t.y][cl] = 1; // 记录 
		rep1(i, 0, 3) {
			int nx = t.x + mx[i], ny = my[i] + t.y;
			if (nx && ny && nx <= n && ny <= n) {
				if ((a[nx][ny] == cl || a[nx][ny] == a[x][y]) && !vis[nx][ny] && !final[t.x][t.y][i]) {
					vis[nx][ny] = 1;
					q.push(node(nx, ny));
				}
			}
		}
	}
	return ans;
}
signed main(void) {
//	freopen("multimoo.in", "r", stdin);
//	freopen("multimoo.out", "w", stdout);
	read(n); 
	int ans1 = 0, ans2 = 0;
	rep1(i, 1, n) rep1(j, 1, n) read(a[i][j]);
	rep1(i, 1, n) rep1(j, 1, n) 
		if (!vis[i][j]) bfs(i, j), ans1 = max(ans1, sz[i][j]);
	rep1(i, 1, n) rep1(j, 1, n)
		rep1(k, 0, 3) {
			k = (k & 1 ? 0 : 3); /*<- 剪枝 1*/ int nx = i + mx[k], ny = j + my[k];
			if (nx && ny && nx <= n && ny <= n) 
				if (a[nx][ny] ^ a[i][j]) ans2 = max(ans2, bfs2(i, j, a[nx][ny]));
		}
	printf("%d\n%d\n", ans1, ans2);
}
```



---

