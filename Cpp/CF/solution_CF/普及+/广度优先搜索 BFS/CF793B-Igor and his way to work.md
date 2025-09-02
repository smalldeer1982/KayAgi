# Igor and his way to work

## 题目描述

伴随着闹钟的铃声，财政分析家 Igor 匆忙起来赶去工作。他吃完早餐后就坐到了他的车上。不幸的，当他打开他的 GPS 导航时，发现在他所居住的小镇 Bankopolis 中的一些道路，由于道路施工而关闭。更不幸的是，车的方向盘有点问题，所以在他去他的银行办公室的途中，**最多只能转两次弯**。

小镇 Bankopolis 可以看做是一个 $n$ 行 $m$ 列的网格图，Igor 需要找到一条从家到银行的道路，这条道路转弯次数最多为 $2$ 次，且不能经过正在维修的道路，或者你可以告诉他不能到达，他应该在家工作。**转弯**定义为 Igor 的车改变一次方向。Igor 的车只能向**上，下，左，右**四个方向行驶。在最开始的时候，Igor 的车可以选择任何方向。因为 Igor 仍然在睡觉，所以请你帮帮他。

## 样例 #1

### 输入

```
5 5
..S..
****.
T....
****.
.....
```

### 输出

```
YES```

## 样例 #2

### 输入

```
5 5
S....
****.
.....
.****
..T..
```

### 输出

```
NO```

# 题解

## 作者：I_will_AKIOI (赞：2)

广搜简单题。

题目说改变方向算一次转弯，那么我们在广搜的时候记录一下上次走路的方向，再记录上当前走到的点坐标 $(x,y)$，已经转弯的次数 $s$。接着对每个点记录至少要转弯几次到达这个点，如果到这个点的转弯次数比最少次数还多，那么就不搜索，否则更新最少转弯次数。

```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
struct Data{int x,y,s,last;}w;
int n,m,vis[N][N];
int fx[4]={1,0,-1,0},fy[4]={0,1,0,-1};
char c[N][N];
queue<Data>q;
int BFS()
{
  w.s=0;
  w.last=-1;
  q.push(w);
  while(!q.empty())
  {
    w=q.front();
    int x=w.x,y=w.y,s=w.s,last=w.last;
    if(c[x][y]=='T') return 1;
    for(int i=0;i<4;i++)
    {
      int nx=x+fx[i],ny=y+fy[i],ns=s;
      if(last!=-1&&last!=i) ns++;//和上次不同，转弯
      if(nx<1||nx>n||ny<1||ny>m||ns>2||vis[nx][ny]<ns||c[nx][ny]=='*') continue;//不符合要求的点
      vis[nx][ny]=ns;//更新最少转弯次数
      q.push(Data{nx,ny,ns,i});
    }
    q.pop();
  }
  return 0;
}
int main()
{
  ios::sync_with_stdio(0);
  memset(vis,63,sizeof(vis));
  cin>>n>>m;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      cin>>c[i][j];
      if(c[i][j]=='S') w.x=i,w.y=j;//起点
    }
  }
  if(BFS()) cout<<"YES";
  else cout<<"NO";
  return 0;
}
```

---

## 作者：Dimly_dust (赞：2)

算法类型：$Dfs ~\&~ Bfs$

思路：

**题目意思为求能否在不转2个弯以上的情况下从S到T。**

- 那么首先从$S$开始上下左右遍历得出在不转第一个弯之前能到达的所有位子。

- 分别由这些位置为起点遍历四周，循环两次，可得出转两次弯所能到达所有位置，只需判断其中是否包括$T$可以了。

bfs算法（怕dfs超时就没用）

```cpp
#include<bits/stdc++.h>
using namespace std;
char f[1009][1009];
int d[1009][1009];
int m,n;
int fuck(int x,int y,int shuju)/*遍历矩阵*/
{
	int i=x+1;
	int j=y;
	while(i<m&&d[i][j]==-1&&f[i][j]!='*')//搜索下方
	{
		d[i++][j]=shuju;
	}
	i=x-1;
	j=y;
	while(i>=0&&d[i][j]==-1&&f[i][j]!='*')//搜索上方
	{
		d[i--][j]=shuju;
	}
	i=x;
	j=y+1;
	while(j<n&&d[i][j]==-1&&f[i][j]!='*')//搜索右方
	{
		d[i][j++]=shuju;
	}
	i=x;
	j=y-1;
	while(j>=0&&d[i][j]==-1&&f[i][j]!='*')//搜索左方
	{
		d[i][j--]=shuju;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>m>>n;
	memset(d, -1,sizeof(d));//初始化数组
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			cin>>f[i][j];
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			if(f[i][j]=='S')
			{
				d[i][j]=0;
				fuck(i,j,0);
			}
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			if(d[i][j]==0)
			{
				fuck(i,j,1);
			}
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			if(d[i][j]==1)
			{
				fuck(i,j,2);
			}
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			if(f[i][j]=='T')
			{
				cout<<(d[i][j]==-1?"NO":"YES");
                /*
                三目运算符,可拓展为：
                if(d[i][j]==-1)cout<<"NO";
                else cout<<"YES";
				 */
			}
	return 0;
}
```



---

## 作者：xiaozeyu (赞：1)

[题目链接 CF793B Igor and his way to work](https://www.luogu.com.cn/problem/CF793B)

深搜加记忆化。

一道图论题，有很多其他类似的题，那就用其他题目中的方法做做看。

先给出相似的题目。而且是双倍经验。

[相似题 P2937 [USACO09JAN]Laserphones S](https://www.luogu.com.cn/problem/P2937)

[SP3861 MLASERP - Laser Phones](https://www.luogu.com.cn/problem/SP3861)

相似题的题解 [题解 SP3861 MLASERP - Laser Pho](https://www.luogu.com.cn/blog/xiaozeyu/solution-sp3861)

都是同一类的计算转弯次数的题目，但范围有所不同，可以借此多练几遍，希望有帮助。

回到这道题目的具体要求。

我们要求出能否在两次转弯以内从出发点达到目的地。

这本质上和其他题目里拿对角线的镜子将光线转一个直角是没有区别的。

本题的数据范围大，但答案却很小。

对于这种特殊情况，我们可以考虑直接从出发点进行两次染色，看能不能达到另一个点。

但如果想要拓展到更多次转弯，就需要用到这里的记忆化优化深搜的方法。

我们可以用深搜的方法。

每次转弯的时候将次数加上一。

优化一下，优先不转弯，先直走，这样快一点。

加上记忆化就可以过了，记忆化中包含四个方向。

在我们找到其中一个端点时就可以开始搜了，在搜之前把这个点当做墙壁，这样防止回来或是在原地转圈浪费力气。

方向直接先用数组存。后面不用讨论。

记得再搜的时候超出就直接返回，这样就不会超时，用时也是很少的。

代码如下。

---


```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int read()
{
    char c=getchar();int x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
const int maxn=1010;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int f[maxn][maxn][4];
int n,m,ans=0x3f3f3f3f;
char a[maxn][maxn];
bool vis[maxn][maxn];
void dfs(int i,int j,int c,int d)
{
	if(c>=3) return ;
    if(d!=-1&&f[i][j][d]<=c) return ;
    if(d!=-1) f[i][j][d]=c;
    if(a[i][j]=='T') 
    {
        ans=min(ans,c);
        return ;
    }
    int x,y;
    if(d!=-1)
    {
        x=i+dx[d];y=j+dy[d];
        if(x<=n&&x>=1&&y<=m&&y>=1&&!vis[x][y]&&a[x][y]!='*')
        {
            vis[x][y]=1;
            dfs(x,y,c,d);
            vis[x][y]=0;
        }
    }
    For(k,0,3)
    {
        if(k==d) continue;
        x=i+dx[k];y=j+dy[k];
        if(x<=n&&x>=1&&y<=m&&y>=1)
        {
            if(vis[x][y]||a[x][y]=='*') continue;
            vis[x][y]=1;
            dfs(x,y,c+(d!=-1),k);;
            vis[x][y]=0;
        }
    }
}
int main()
{
    memset(f,0x3f,sizeof f);
    scanf("%d%d",&n,&m);
    For(i,1,n) scanf("%s",a[i]+1);
    //For(i,1,n) printf("%s\n",a[i]+1);
    For(i,1,n)
        For(j,1,m)
        {
            if(a[i][j]!='S') continue;
            vis[i][j]=1;
            a[i][j]='*';
            dfs(i,j,0,-1);
            if(ans<=2) puts("YES");
            else puts("NO");
            //printf("%d\n",ans);
            return 0;
        }
}
```

感谢管理员的审核。


---

## 作者：_lxy_ (赞：1)

### 题意
有一个 $n\times m$ 的矩阵，有 $4$ 种道路，`.` 是可行的道路, `*` 是不可行的道路， `S` 是起点， `T` 是终点，且只能转 $2$ 次弯，问是否能从起点走到终点。
### 分析
在 bfs 的时候记录一下当前转弯的次数，如果下一步走的方向和上一步走的方向不同，就加上这次转弯的次数。
### 代码
```cpp
#include <bits/stdc++.h>
#define elif else if
using namespace std;
const int MAXN=1e3+7;
char a[MAXN][MAXN];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int vis[1005][1005][4][2];
int n,m;
struct node
{
    int x,y,z,turns;
};
bool bfs(node u)
{
    queue<node>q;
    for(register int i=0;i<4;i++) //4个方向
    {
        node v=u;
        v.x+=dx[i];
        v.y+=dy[i];
        if(v.x>=1&&v.x<=n&&v.y>=1&&v.y<=m&&a[v.x][v.y]!='*') //能走
        {                                   
            v.z=i;
            v.turns=2;
            vis[v.x][v.y][i][2]=1;
            q.push(v);
        }
    }
    while(!q.empty())
    {
        node u=q.front();
        q.pop();
        if(a[u.x][u.y]=='T') return true; //走到终点了
        for(register int i=0;i<4;i++)
        {
            node v=u;
            v.x+=dx[i];
            v.y+=dy[i];
            if(v.x>=1&&v.x<=n&&v.y>=1&&v.y<=m&&a[v.x][v.y]!='*') //下一步能走
            {
                if(v.z==i) //方向不变
                {
                    if(!vis[v.x][v.y][i][v.turns]) //之前没有相同方向走过
                    {
                        q.push(v);
                        vis[v.x][v.y][i][v.turns]=true;
                    }
                }
                elif(v.turns>0)
                {
                    if(!vis[v.x][v.y][i][v.turns-1])
                    {
                        v.turns--;
                        v.z=i;  
                        vis[v.x][v.y][i][v.turns]=true;
                        q.push(v);
                    }
                }
            }
        }
 
    }
    return 0;
}
int main()
{
    cin>>n>>m;
    node start;
    for(register int i=1;i<=n;i++)
    {
        for(register int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            if(a[i][j]=='S') //记录起点
            {
                start.x=i;
                start.y=j;
            }
        }
    }
    if(bfs(start)) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}
```


---

## 作者：槑小杨 (赞：1)

朴素方法。

开数组判断转了几次，还剩几次。

与上一次行动不同就视为转弯。

```
#include<bits/stdc++.h>
using namespace std;
char s[1005][1005];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int used[1005][1005][4][2];
int n,m;
struct node
{
    int x,y,d,sum;
};
int  bfs(node zuobiao)
{
    queue<node>q;
    for(int i=0;i<4;i++)
    {
        node v=zuobiao;
        v.x+=dx[i];
        v.y+=dy[i];
        if(v.x>=1&&v.x<=n&&v.y>=1&&v.y<=m&&s[v.x][v.y]!='*')     
        {                                   
            v.d=i;
            v.sum=2;
            used[v.x][v.y][i][2]=1;
            q.push(v);
        }
    }
    while(!q.empty())
    {
       node u=q.front();
        q.pop();
        if(s[u.x][u.y]=='T')
            return 1;
        for(int i=0;i<4;i++)
        {
            node v=u;
            v.x+=dx[i];
            v.y+=dy[i];
            if(v.x>=1&&v.x<=n&&v.y>=1&&v.y<=m&&s[v.x][v.y]!='*')
            {
                if(v.d==i) 
                {
                    if(used[v.x][v.y][i][v.sum]==0){
                    q.push(v);
                    used[v.x][v.y][i][v.sum]=1;
                    }
                }
                else if(v.sum>0)
                {
                    if(!used[v.x][v.y][i][v.sum-1])
                    {
                        v.sum--;
                        v.d=i;  
                        used[v.x][v.y][i][v.sum]=1;
                       q.push(v);
                    }
                }
            }
 
        }
 
    }
    return 0;
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(used,0,sizeof(used));
    node zuobiao;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",&s[i][1]);
        for(int j=1;j<=m;j++)
        {
            if(s[i][j]=='S')
            {
                zuobiao.x=i;
                zuobiao.y=j;
            }
        }
    }
       if(bfs(zuobiao)) printf("YES\n");
        else printf("NO\n");
    return 0;
}
```

---

## 作者：Tomle (赞：0)

# CF793B 题解

## 题意简化

从 `S` 出发，可以走 `.`，终点为 `T`，最多转弯两次，能否到达。

## 思路

搜索。

dfs + 记忆化打寄了，于是尝试 bfs。

bfs 比较好理解，尝试能否到达终点。bfs 记录 4 个信息：横纵坐标，方向，转弯次数。

## 算法流程

- 读入，可以用 scanf 读入 char 数组。
- 找起点，记录坐标。
- bfs 检查是否能到达终点。代码中的的 bfs 函数是 bool 类型的。
	- 首先把所有方向全部入队，此时转弯次数为 $0$。
    - 循环中：
    	- 如果到达终点（字符为 `T`），函数结束（`return true;`）。
        - 否则像四个方向拓展，如果拓展方向与原方向不一样，转弯次数加一。
        - 检查边界、是否是障碍物、转弯次数是否大于 $2$。
        - 标记。
    - 如果循环结束，说明不能到达（无解），`return false;`。

## 时间复杂度分析

$4$ 个方向，可能转弯 $0 \sim 2$ 次，每个点最多入队 $4 \times 3 = 12$ 次。共有 $m \times n$ 个点，进队次数最多 $12mn$ 次，所以复杂度为 $O(mn)$。

## 细节

- 边界。
- 横纵坐标不要写反。
- 判重数组也要开四维，记录坐标、方向、转弯次数。因为不同的方向和转弯次数可能会有不同结果。

code:
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node {
	int x, y, d, t;
	// 横纵坐标，方向，转弯次数。
};

int n, m;
char a[1005][1005];
bool tt[1005][1005][4][5];
// 判重。
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int dd[4] = {3, 1, 2, 0};
// 向四个方向拓展的相对坐标和方向。

bool bfs(int sx, int sy) {
	queue <node> q;
	q.push({sx, sy, 0, 0});
	q.push({sx, sy, 1, 0});
	q.push({sx, sy, 2, 0});
	q.push({sx, sy, 3, 0});
	for (int i = 0; i < 4; i++) tt[sx][sy][i][0] = 0;
	// 全部入队并标记
	while (q.size()) {
		int x = q.front().x, y = q.front().y, d = q.front().d, t = q.front().t;
		if (a[y][x] == 'T') return true;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int X = x + dx[i], Y = y + dy[i], T;
			if (dd[i] == d) T = t;
			else T = t + 1;
			if (X == 0 || X > m || Y == 0 || Y > n || T > 2 || tt[X][Y][dd[i]][T] || a[Y][X] == '*') continue;
			tt[X][Y][dd[i]][T] = true;
			q.push({X, Y, dd[i], T});
		}
	}
	return false;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", a[i] + 1);
	}
	int sx, sy;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == 'S'){
				sy = i, sx = j;
			}
		}
	}
	if (bfs(sx, sy)) {
		cout << "YES";
	} else {
		cout << "NO";
	}
	return 0;
}
```

---

## 作者：Creative_sad_yosgic (赞：0)

## CF793Bの题解
### 题意
一眼 BFS **求能否到达终点**题。

在模板的基础上，我们的题额外为我们增加了**只能转两次弯**的要求，所以我~~首先打了一个暴力~~，在第 $9$ 个点T了。

显然，这题需要记忆化，所以我 **~~又写了~~** 一个代码，结果更惨，直接 WA 了。

### 因为本弱者不怎么会写记忆化，所以我们可以搞一个投机取巧的思路：

首先从起点开始搜索，搜到起点上下左右能到的所有点，标记。再搜索标记过的点，继续标记，因为**转弯两次**所以两次这样的操作即可，记得记忆化（~~还得写~~。

### 代码
```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")//外网优化 
#include<bits/stdc++.h>
using namespace std;
char a[1111][1111];int vis[1111][1111];
int nx,ny,tox,toy,flag1,flag2;//记录起点，终点，优化标记 
int n,m;
struct node{
	int x,y;
};
queue<node> q;
int dx[]={0,1,-1,0,0};
int dy[]={0,0,0,1,-1};//上下左右 
int bfs(int x,int y,int p)
{
	node now,next;//标准BFS 
	now.x=x;
	now.y=y;
	q.push(now);
	for(int i=1;i<=4;i++)
	{
		next.x=now.x+dx[i];
		next.y=now.y+dy[i];
	    while(next.x>=1&&next.x<=n&&next.y>=1&&next.y<=m&&vis[next.x][next.y]==-1&&a[next.x][next.y]!='*')
		{//在不越界且未走过的情况下 
			vis[next.x][next.y]=p;//标记走过 
			q.push(next);
			next.x+=dx[i];
			next.y+=dy[i];//不断朝同一方向移动 
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); //优化 
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	   for(int j=1;j<=m;j++)
		   cin>>a[i][j];
	for(int i=1;i<=n;i++)
	   for(int j=1;j<=m;j++)
		   vis[i][j]=-1;//初始化标记数组 
	for(int i=1;i<=n;i++)
    {
		if(flag2) break;
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]=='S') nx=i,ny=j,flag1=1;//找到起点就标记 
			if(a[i][j]=='T')
			{
				tox=i,toy=j;
				if(flag1) {flag2=1;break;}//如果同时找到终点就退出循环 
			}
		}
	}//带优化的找起点终点 
	bfs(nx,ny,0);//不转弯 
	for(int i=1;i<=n;i++) 
	   for(int j=1;j<=m;j++)
	     if(vis[i][j]==0) bfs(i,j,1);//第一次转弯 
	for(int i=1;i<=n;i++) 
	   for(int j=1;j<=m;j++)
	     if(vis[i][j]==1) bfs(i,j,2);//第二次转弯 
	int ans=vis[tox][toy];
	if(ans!=-1) cout<<"YES";//如果终点被标记过就YES 
	else cout<<"NO";//否则NO 
	return 0;
}
```
**~~所以为什么我试图双队列优化时会W啊~~**





---

## 作者：hihihi198 (赞：0)

怎么其他的题解都是用搜索？

那么我来写一篇直接在地图上进行标记的解法吧！

思路：既然我们要知道 S 是否只要通过两次转弯就可以到达 T，那么一定存在两个转弯点，其中一个点不用转弯就能到 S，另一个点不用转弯就能到 T，且这两个点不用转弯就可以相互到达。

具体地，我们可以先分别标记出 S 和 T 不用拐弯就能到达的点。在标记过程中特判不用拐弯和拐弯一次就能到达的情况。

遍历每一条横线和竖线。每一条线都能被障碍物（即`*`）分成几段。

如果在一段中同时存在 S 不用拐弯就能到的点和 T 不用拐弯就能到达的点，那么就有解（因为这一段与它们显然构成了两个拐弯点），否则无解。

时间复杂度：$ O(nm) $。


```cpp
#include<cctype>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld eps=1e-8;
inline int read(){
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    return f?-x:x;
}
const int N=1050;
int n,m,xs,ys,xt,yt;
char gps[N][N];//记录地图
bool flag;
int main(){
	n=read();m=read();flag=false;
	for(register int i=1;i<=n;i++){
		scanf("%s",gps[i]+1);
	}
	for(register int i=1;i<=n;i++){//找到S和T的坐标
		for(register int j=1;j<=m;j++){
			if(gps[i][j]=='S')xs=i,ys=j;
			if(gps[i][j]=='T')xt=i,yt=j;
		}
	}
	for(register int i=xs;i>=1;i--){//将S向四个方向扩展
		if(gps[i][ys]=='*')break;
		gps[i][ys]='S';
	}
	for(register int i=xs;i<=n;i++){
		if(gps[i][ys]=='*')break;
		gps[i][ys]='S';
	}
	for(register int i=ys;i>=1;i--){
		if(gps[xs][i]=='*')break;
		gps[xs][i]='S';
	}
	for(register int i=ys;i<=m;i++){
		if(gps[xs][i]=='*')break;
		gps[xs][i]='S';
	}
	for(register int i=xt;i>=1;i--){//将T向四个方向扩展顺便特判
		if(gps[i][yt]=='*')break;
		if(gps[i][yt]=='S')flag=true;
		gps[i][yt]='T';
	}
	for(register int i=xt;i<=n;i++){
		if(gps[i][yt]=='*')break;
		if(gps[i][yt]=='S')flag=true;
		gps[i][yt]='T';
	}
	for(register int i=yt;i>=1;i--){
		if(gps[xt][i]=='*')break;
		if(gps[xt][i]=='S')flag=true;
		gps[xt][i]='T';
	}
	for(register int i=yt;i<=m;i++){
		if(gps[xt][i]=='*')break;
		if(gps[xt][i]=='S')flag=true;
		gps[xt][i]='T';
	}
	if(flag){
		printf("YES");
		return 0;
	}
	for(register int i=1;i<=n;i++){
		char ever='*';//记录每一段内是否有能到达的点
		for(register int j=1;j<=m;j++){
			if((gps[i][j]=='S'&&ever=='T')||(gps[i][j]=='T'&&ever=='S')){
				flag=true;
				break;
			}
			if(gps[i][j]!='.')ever=gps[i][j];
		}
		if(flag)break;
	}
	if(flag){
		printf("YES");
		return 0;
	}
	for(register int j=1;j<=m;j++){
		char ever='.';
		for(register int i=1;i<=n;i++){
			if((gps[i][j]=='S'&&ever=='T')||(gps[i][j]=='T'&&ever=='S')){
				flag=true;
				break;
			}
			if(gps[i][j]!='.')ever=gps[i][j];
		}
		if(flag)break;
	}
	printf(flag?"YES":"NO");
	return 0;
}

```

---

