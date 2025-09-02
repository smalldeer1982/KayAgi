# [USACO12MAR] Tractor S

## 题目描述

经过一天漫长的工作，农场主 John 完全忘记了他的拖拉机还在场地中央。他的奶牛们总喜欢和他搞些恶作剧，它们在场地的不同位置丢下 $n$ 堆干草。这样 John 就必须先移走一些干草堆才能将拖拉机开走。

拖拉机和干草堆都可以看作是二维平面上的点，它们的坐标都是整数，没有哪堆干草的坐标和拖拉机的初始坐标一致。John 驾驶拖拉机只能沿着坐标轴的方向移动若干单位长度，比如说，他可以先朝北移动 $2$ 个单位长度，再向东移动 $3$ 个单位长度等等。拖拉机不能移动到干草堆所占据的点。

请你帮助 John 计算一下，最少要移动多少堆干草才能将拖拉机开回坐标原点。

## 说明/提示

对于 $100\%$ 的数据，保证 $1 \leq n \leq 5 \times 10^4$，$1 \leq x_i, y_i \leq 10^3$。

## 样例 #1

### 输入

```
7 6 3 
6 2 
5 2 
4 3 
2 1 
7 3 
5 4 
6 4 ```

### 输出

```
1 ```

# 题解

## 作者：一只书虫仔 (赞：13)

[P1849 [USACO12MAR]Tractor S](https://www.luogu.com.cn/problem/P1849)

### 题外话

这是课上的考试题，教练给了我们思路和代码让我们自己研究，那我就开始研究啦！

---

### 方法简述

01 bfs，与正常广搜及其相近。

---

### 前置芝士

queue，deque

---

### 具体方法

首先是方向移动，用两个初始化数组 $\text{stx}$ 和 $\text{sty}$ 即可。  
然后是 01 bfs，用到 deque，从最开始的初始边向后走。  
如果可以 push 到队首，就一直 push 到队首，反之 push 到队尾。   


---

### Code

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXM = 1000 + 5;
const int stx[4] = {0, 1, 0, -1};
const int sty[4] = {1, 0, -1, 0};

struct Node {
	int x, y;
} s;

int n, step[MAXM][MAXM];
bool map[MAXM][MAXM];
deque<Node> q;

int main () {
	scanf("%d%d%d", &n, &s.x, &s.y);
	for (int i = 1, x, y; i <= n; i++) {
		scanf("%d%d", &x, &y);
		map[x][y] = true;
	}

	memset(step, -1, sizeof(step));
	step[s.x][s.y] = 0;
	q.push_back(s);
	while (!q.empty()) {
		Node cur = q.front();
		q.pop_front();
		for (int k = 0; k < 4; k++) {
			Node nxt;
			nxt.x = cur.x + stx[k], nxt.y = cur.y + sty[k];
			if (nxt.x < 0 || nxt.x >= MAXM) continue;
			if (nxt.y < 0 || nxt.y >= MAXM) continue;
			if (step[nxt.x][nxt.y] != -1) continue;
			if (map[nxt.x][nxt.y]) {
				step[nxt.x][nxt.y] = step[cur.x][cur.y] + 1;
				q.push_back(nxt);
			}
			else {
				step[nxt.x][nxt.y] = step[cur.x][cur.y];
				q.push_front(nxt);
			}
		}
	}

	printf("%d\n", step[0][0]);
	return 0;
}
``` 

p.s. 这是我们教练给的程序 ~~我猜他看到这个会骂我~~

---

### 总结与延伸

这题其实最好用的是最短路算法，这就是个最短路算法模板。  
那 01 bfs 用于什么地方比较合适呢？  
用于能转化为边权 $0 \text { or }1$ 的最短路问题。  
所以，在 tg 组中算一个比较实用的技巧。

好的，就到这里！

---

### 参考资料

- 教练给的思路和代码
- [01 bfs 学习笔记](https://blog.csdn.net/R_O_J/article/details/52772421?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase)
- [01 bfs 学习记录](https://blog.csdn.net/shiveringkonnyaku/article/details/82839223)

---

## 作者：_Atyou (赞：11)

### 双端队列BFS

就是一般BFS的变形，走四个方向，遇到草堆的就压到队尾，没有遇到草堆的就压到队头。

这样，我们就保证了任意时刻广搜队列中的节点所对应的答案仍具有单调性。

因此每个点只需要访问一次，算法的复杂度是O（1000^2）

#### 细节方面：

由于草堆的坐标范围在（1，1000），且在草堆范围外都是可走的，但其实这样的话范围（-∞，-1）与0都是等价的，1001与（1002，＋∞）也是，我们在草堆范围外加一圈就可以。所以0和1001也是可走的，数组开大点不然越界

具体双端队列的一些操作其实和普通队列差不多，多写一个front或back

代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <deque>
using namespace std;

namespace atyou {

inline int read() {
    register int num=0, f=1;
    register char c;
    while (!isdigit(c=getchar())) if (c == '-') f=-1;
    while (isdigit(c))
          num=(num<<3)+(num<<1)+(c&15), c=getchar();
    return num*f;
}

inline void write(register int x) {
    if (x < 0) putchar('-'), write(~x+1);
    else {
        if (x > 9) write(x/10);
        putchar(x%10+'0');
    }
}

const int N = 500000 + 5, M = 1000 + 5, dx[]={1, -1, 0, 0}, dy[]={0, 0, -1, 1};

int n, sx, sy, a[M][M], f[M][M], v[M][M]; //a记录是否有草堆， f记录答案， v记录是否访问 
deque<pair<int, int> > q; //双端队列 

int main() {
    memset(f, 0x3f, sizeof(f)); // 初始化 
    n=read(); sx=read(); sy=read();
    for (register int i=1; i<=n; i++) {
        int x=read(), y=read();
        a[x][y]=1; //放草堆 
    }
    q.push_back(make_pair(sx, sy)); //起点压入 
    f[sx][sy]=0; v[sx][sy]=1; 
    while (q.size()) {
        int x=q.front().first, y=q.front().second; q.pop_front();
        if (x == 0 && y == 0) { //到了坐标原点 
            write(f[x][y]);  
            return 0;
        }
        for (register int i=0; i<4; i++) {
            int x0=x+dx[i], y0=y+dy[i];
            if (x0 < 0 || x0 > 1001 || y0 < 0 || y0 > 1001) continue; //超出范围 
            if (v[x0][y0]) continue; 
            v[x0][y0]=1;
            f[x0][y0]=f[x][y]+a[x0][y0]; //更新答案 
            //整段代码的重点来了 
            if (a[x0][y0]) q.push_back(make_pair(x0, y0)); //有草堆压到队尾 
            else q.push_front(make_pair(x0, y0)); //没草堆压到队首，优先更新其他点  
        }
    }
    return 0;
}

}

int main() {
    atyou::main();
    return 0;
}

```


---

## 作者：soy_un_perro (赞：9)

解法：优先队列广搜。建立以移动的干草数为第一关键字的小根堆，借助贪心，当取出堆顶的坐标为(0,0)，即为最优解。

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
priority_queue <pair<int,pair<int,int> > > q; //优先队列的第一关键字是移动的干草数，第二关键字是(x,y)坐标，实现小根堆（运用相反数）
int n,sx,sy,x,y,step;
int m[1100][1100],v[1100][1100];
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
int bfs()
{
	q.push(make_pair(0,make_pair(-sx,-sy)));
	v[sx][sy]=1;
	while(!q.empty())
	{
		x=-q.top().second.first;
		y=-q.top().second.second;
		step=-q.top().first;
		q.pop();
		if (x==0 && y==0)
			return step;
		for(int i=0;i<4;i++)
		{
			if (x+dx[i]>=0 && x+dx[i]<=1050 
			&& y+dy[i]>=0 && y+dy[i]<=1050 
			&& !v[x+dx[i]][y+dy[i]])
			{
				if (m[x+dx[i]][y+dy[i]])
					q.push(make_pair(-step-1,make_pair(-x-dx[i],-y-dy[i])));
				else
					q.push(make_pair(-step,make_pair(-x-dx[i],-y-dy[i])));
				v[x+dx[i]][y+dy[i]]=1;
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&sx,&sy);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		m[x][y]=1;
	}
	printf("%d",bfs());
	return 0;
}
```

---

## 作者：Chevalier (赞：7)

本蒟蒻的第一篇题解！

思路很简单：从出发点进行广搜，将本次广搜接触到的所有干草堆搬走，再进行广搜，以此类推，直到第i次广搜遍历到原点为止，答案即为i-1。证明也很显然，在此不再赘述。

复杂度的话是最坏O(n^3)  （应该吧）


献上我拙陋的代码：
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
int n,mx,my,bx,by,mp[1010][1010],v[1010][1010],ans;
int xd[5]={0,0,0,1,-1};
int yd[5]={0,1,-1,0,0};
queue<pair<int,int> > q;

bool bfs(){
    memset(v,0,sizeof v);
    q.push(make_pair(bx,by));
    while(q.size()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        if(x==0&&y==0)return 1;
        for(int i=1;i<=4;i++){
            int dx=x+xd[i];
            int dy=y+yd[i];
            if(v[dx][dy]||dx<0||dy<0||dx>mx||dy>my)continue;
            if(mp[dx][dy]){
                mp[dx][dy]=0;
                v[dx][dy]=1;
                continue;
            }
            q.push(make_pair(dx,dy));
            v[dx][dy]=1;
        }
    }
    return 0;
}

int main(){
    scanf("%d%d%d",&n,&bx,&by);
    mx=bx,my=by;
    for(int i=1;i<=n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        mx=max(mx,x);
        my=max(my,y);
        mp[x][y]=1;
    }
    mx++,my++;
    while(!bfs())
        ans++;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：maple_tzc (赞：7)



这题目还蛮简单，记住，用spfa的时候，数组一定要开大一些，不然，SPFA会傻逼逼的把你所有的点都走一遍，然后你就莫名数组越界，

判断一下就SPFA就好了


```cpp
#include<bits/stdc++.h>
using namespace std;
int z[4]={0,0,1,-1},c[4]={1,-1,0,0};
int n,x,y,x1,y2,mapp[1010][1010],q1[1001000],q2[1001000],d[1010][1010];
bool v[1011][1011];
void inti() {
    cin>>n>>x>>y;
    for (int i=1; i<=n; i++)
        cin>>x1>>y2,mapp[x1][y2]=1;
}
void spfa(int x,int y) {
    memset(d,127,sizeof(d));
    v[x][y]=1;
    d[x][y]=mapp[x][y];
    q1[0]=x;
    q2[0]=y;
    int head=0,tail=1;
    while (head!=tail) {
        int nx=q1[head],ny=q2[head];
        head=(head+1)%100000;
        for(int i=0; i<4; i++) {
            int sx=nx+c[i],sy=ny+z[i];
            if(sx>=0 && sx<=1001 && sy>=0 && sy<=1001 && d[sx][sy]>d[nx][ny]+mapp[sx][sy]){
                d[sx][sy]=d[nx][ny]+mapp[sx][sy];
                if (!v[sx][sy]) {
                    v[sx][sy]=1;
                    tail=(1+tail)%100000;
                    q1[tail]=sx;
                    q2[tail]=sy;
                }
            }
        }        
        v[nx][ny]=0;
    }
}
void work() {
    spfa(x,y);
    cout<<d[0][0];
}
int main() {
    inti();
    work();
    return 0;
}
```

---

## 作者：SzTC (赞：5)

~~萌新刚学OI~~ 萌新很菜，不会很多专业的术语，因此本题解看起来会对和我一样的萌新友好一点。（大佬请自动略过）

题目大意：由 $(x0,y0)$ 点至原点 $(0,0)$ 至少需要经过多少干草堆。  
说到 **至少** ，又是 **在地图中** ，我们想到可以用bfs来求解。  
但是对于像我一样的蒟蒻来说，用单个一般的bfs很难实现，于是想了（好吧我承认是经过了教练的点拨）两种方法进行求解（均以bfs为思路）：

## 解法一：一个bfs不行，那我们就来多个
共进行多次bfs搜索，每一次搜索都将所有能够到达的地点进行标记，直到没有点可以再走了（即周围全都被干草堆围起来了）注意：干草堆也需要标记。   
而后的搜索可以直接走过这些标记过的干草堆。  
当原点也被标记掉以后，停止搜索。  
最后的答案就是 搜索的总次数 ${ -1 }$ 。  
 参考代码： 
```cpp
#include<bits/stdc++.h>  //万能头文件（偷懒） 
using namespace std;
inline int read()//快读（读入优化） 
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int n;
int k;
int xx,yy;
int nn,mm;
int mv[4][2]={{1,0},{-1,0},{0,1},{0,-1}};  //移动数组 
int mark[1111][1111];
int cnt;  //搜索次数统计（即答案） 
struct node{ 
	int x,y;
};
void bfs()
{
	queue<node>que;//STL大法好 
	node head;
	head.x=xx;
	head.y=yy;
	mark[xx][yy]=k;
	que.push(head);
	while(!que.empty())//开始bfs 
	{
		int x=que.front().x;
		int y=que.front().y;
		que.pop();
		for(int i=0;i<4;i++)
		{
			int tx=x+mv[i][0];
			int ty=y+mv[i][1];
			if(tx>=0 && tx<=nn && ty>=0 && ty<=mm)
			{
				if(mark[tx][ty]<=cnt)//如果这个点为0（不是干草堆）或者小于等于cnt（是以前搜索过的干草堆）那么将其加入队列 
				{
					node t;
					t.x=tx;
					t.y=ty;
					que.push(t);
				}
				mark[tx][ty]=cnt+1;//将点标记 
			}
		}
	}
}
int main()
{
	n=read();
	xx=read();
	yy=read();
	for(int i=1;i<=n;i++)
	{
		int a,b;
		a=read();
		b=read();
		mark[a][b]=INT_MAX;//干草堆的初始标记设为无穷大 
		nn=max(nn,a);
		mm=max(mm,b);
	}
	nn++;mm++;//地图的边界为干草堆坐标最大的点再+1（因为可以走到干草堆的后一格） 
	bfs();   //第一次搜索 
	while(mark[0][0]==0)//如果原点未被标记，则继续搜索 
	{
		cnt++;
		bfs();
	}
	cout<<cnt;
	return 0;
}
```
此解法的时间复杂度较高，但更易理解


------------
## 解法二：双端队列优化bfs
像一般的bfs一样搜索，只不过遇到有干草堆的就往队列后面加，否则就正常地加到队列的前面。  
原理：保证了在队列前面的点需要经过的干草堆始终小于或等于在队列后面的点，因此搜索到原点的时候也可以保证此时经过的干草堆是最少的。  
参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int n;
int xx,yy;
int nn,mm;
int mv[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int mapp[1111][1111];
int mark[1111][1111];
int cnt;
struct node{
	int x,y,step;
};
void bfs()
{
	deque<node>que;//双端队列，STL大法好！！ 
	node head;
	head.x=0;
	head.y=0;
	mark[0][0]=1;//总觉得从原点开始搜会快一点 
	head.step=0;
	que.push_back(head);//与一般的队列没什么区别，主要就是push与pop的时候需要加上front（从队头）或者back（从队尾） 
	while(!que.empty())
	{
		int x=que.front().x;
		int y=que.front().y;
		int s=que.front().step;
		que.pop_front();
		if(x==xx && y==yy)//搜索到目标点，此时的答案必定是最优答案（上面已经解释过了） 
		{
			cout<<s;
			return ;
		}
		for(int i=0;i<4;i++)
		{
			int tx=x+mv[i][0];
			int ty=y+mv[i][1];
			if(tx>=0 && tx<=nn && ty>=0 && ty<=mm && !mark[tx][ty])
			{
				mark[tx][ty]=1;
				node t;
				t.x=tx;
				t.y=ty;
				t.step=s;
				if(!mapp[tx][ty])
				{
					que.push_front(t);//没遇到干草堆，队头加入 
				}
				else
				{
					t.step=s+1;
					que.push_back(t);//遇到了干草堆，从队尾加入 
				}
			}
		}
	}
}
int main()
{
	n=read();
	xx=read();
	yy=read();
	for(int i=1;i<=n;i++)
	{
		int a,b;
		a=read();
		b=read();
		mapp[a][b]=1;
		nn=max(nn,a);
		mm=max(mm,b);
	}
	nn++;mm++;//同上 
	bfs();//只需要搜索一次 
	return 0;
}
```

（小建议：善用c++的STL库，真的非常方便）  
最后，欢迎大家在评论区提出意见！

---

## 作者：Tony2 (赞：5)

### 我这道题的做法非常奇葩，仅供参考

一看到图论标签，我就想到要把每个点向四周连边，但发现数据不容许。。。于是我就想到将一个连通块看作一个点，然后进行dijkstra，求出最短路。

做法：

1. 将数据处理成地图，求出连通块并标号（这里我用dfs爆栈了。。。我用了bfs）。
2. 对于拖拉机所在的联通块进行bfs，假设当前为pos，另一个为pos2，就让pos的**连通块编号**向pos2的**连通块编号**连边，权值为pos2干草块数量（此处要分两种情况，具体见代码）。
3. 求拖拉机到（0，0）的最短路，输出。

### 再次声明：不建议大家使用这种方法，太复杂了

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 400005, M = 1010;
int n, tot=0;
int X, Y, dis[N], a[M+10][M+10], num[M+10][M+10];
pair<int, int> q2[10000005];
int head=1, tail=0;//queue炸了，手写
bool vis[M+10][M+10], f[N];
int dx[5] = {0, 1, 0, -1}, dy[5] = {-1, 0, 1, 0};
vector<pair<int, int> > e[N], p[N];
queue<pair<int, int> > q;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
int dijkstra(){
	memset(f, 0, sizeof(f));
	memset(dis, 0x3f, sizeof(dis));
	dis[num[X][Y]] = 0;
	pq.push({0, num[X][Y]});
	while (!pq.empty()){
		int u = pq.top().second;
		pq.pop();
		if (f[u]) continue;
		f[u] = 1;
		for (int i = 0; i < e[u].size(); i++){
			int v = e[u][i].first, w = e[u][i].second;
			if (dis[v] > dis[u]+w){
				dis[v] = dis[u]+w;
				pq.push({dis[v], v});
			}
		}
	}
	return dis[num[0][0]];
}
void push(pair<int, int> pii){
	tail++;
	tail %= 10000000;
	q2[tail] = pii;
}
void bfs(int x){
	for (int i = 0; i < p[x].size(); i++) push(p[x][i]), vis[p[x][i].first][p[x][i].second] = 1;
	while (head <= tail){
		pair<int, int> pos = q2[head];
//		cout << pos.first << ' ' << pos.second << endl;
		head++, head %= 10000000;
		for (int i = 0; i < 4; i++){
			int xx = pos.first+dx[i], yy = pos.second+dy[i];
			if (xx >= 0 && yy >= 0 && xx <= M && yy <= M && !vis[xx][yy]){
				push({xx, yy});
				vis[xx][yy] = 1;
				if (num[xx][yy] == 0){//如果有干草块（在前面bfs处理的时候标号为1
					num[xx][yy] = ++tot;
					e[num[pos.first][pos.second]].push_back({tot, a[xx][yy]});//连边
				}else{
					for (int j = 0; j < p[num[xx][yy]].size(); j++){
						int _x = p[num[xx][yy]][j].first, _y = p[num[xx][yy]][j].second;
						if (!vis[_x][_y]){
							push({_x, _y});//将连通块所有的点加入queue
							vis[_x][_y] = 1;
						}
					}
					e[num[pos.first][pos.second]].push_back({num[xx][yy], 0});//连边
				}
			}
		}
	}
}
void bfs2(int x, int y){//洪水操作
	while (!q.empty()) q.pop();
	q.push({x, y});
	while (!q.empty()){
		pair<int, int> pos = q.front();
		q.pop();
		for (int i = 0; i < 4; i++){
			int xx = pos.first+dx[i], yy = pos.second+dy[i];
			if (xx >= 0 && yy >= 0 && xx <= M && yy <= M && !num[xx][yy] && a[xx][yy] == 0){
				num[xx][yy] = tot;
				q.push({xx, yy});
			}
		}
	}
}
int main(){
	std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	freopen("test_file/in.txt", "r", stdin);
//	freopen("test_file/out.out", "w", stdout);
	memset(vis, 0, sizeof(vis));
	memset(num, 0, sizeof(num));
	memset(a, 0, sizeof(a));
	cin >> n >> X >> Y;
	for (int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;
		a[x][y]++;
	}
	for (int i = 0; i <= M; i++)
		for (int j = 0; j <= M; j++) if (!num[i][j] && a[i][j] == 0){
			tot++;
			num[i][j] = tot;
			bfs2(i, j);
		}
	for (int i = 0; i <= M; i++)
		for (int j = 0; j <= M; j++) if (num[i][j])
			p[num[i][j]].push_back({i, j});
	bfs(num[X][Y]);
	cout << dijkstra() << endl;
	return 0; 
}
```

### 最后求管理员大大通过QWQ！！！

---

## 作者：Lance1ot (赞：2)

首先这道题我们可以搜索 ~~废话~~

大部分跑的是spfa或者是类似的BFS。如果到这个点的花费比之前更少，就入队搜索。

可是，如果这么样的话。一个点至少会被入队一次。

那怎么优化呢？

## 我们先抛开这个题

我们先想BFS的本质。

BFS的大体思路就是按照状态转移的次数进行有层次的便利。

直到遍历到所有状态或目标状态。

这到题呢？  状态就是移开的干草数

可是如果这么定义状态的话。虽然搜到目标状态就是最优解，但是现在的难题就是状态的转移。

因为每个状态的都不是相连的。

而我们一般写bfs都是将四个或八个方向的相邻的点扩展出来。

如果这么写的话，就默认了距离就是状态。

我们就可以写一个dfs函数辅助状态转移。

## 对，没有错。就是dfs

dfs是具有连续性的。

比如说dfs版spfa就是比bfs的spfa判负环快，因为就是具有连续性。

所以，BFS+DFS扩展状态就可以了。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
struct node
{
    int x;
    int y;
};
queue<node> q;
int map[1010][1010];
int vis[1010][1010];
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
int n,bx,by;
bool flag;
node ha;
int read()
{
    int w=0;
    char in=getchar();
    while(in<'0'||in>'9')
        in=getchar();
    while(in>='0'&&in<='9')
    {
        w=(w<<1)+(w<<3)+in-'0';
        in=getchar();
    }
    return w;
}
bool check(int x,int y)
{
    if(x<0||y<0||x>1001||y>1001)
        return false;
    return true;
}
void dfs(int x,int y,int step)
{
    if(vis[x][y]&&vis[x][y]<step)
        return ;
    vis[x][y]=step;
    for(int i=0;i<=3;i++)
    {
        if(flag)
            return ;
        if(check(x+dx[i],y+dy[i])&&(vis[x+dx[i]][y+dy[i]]>step+1||!vis[x+dx[i]][y+dy[i]]))
        {
            if(x+dx[i]==0&&y+dy[i]==0)//终点 
            {
                flag=true;
                vis[0][0]=step;
                if(map[0][0])
                    vis[0][0]+=1;
                return ;
            }
            if(map[x+dx[i]][y+dy[i]])//如果遇到了一个有干草的块，就是找到了下一个状态. 
            {
                vis[x+dx[i]][y+dy[i]]=step+1;
                ha.x=x+dx[i];
                ha.y=y+dy[i];
                q.push(ha);
                continue;
            }
            dfs(x+dx[i],y+dy[i],step);
        }
    }
}
int main()
{
    n=read();
    bx=read();
    by=read();
    int a,b;
    for(int i=1;i<=n;i++)
    {
        a=read();b=read();
        map[a][b]=true;
    }
    node pass;
    /*pass.x=bx;
    pass.y=by;
    q.push(pass);
    vis[bx][by]=1;*/
    dfs(bx,by,1);
    while(!flag)
    {
        pass=q.front();
        /*if(pass.x==0&&pass.y==0)
            break;*/
        q.pop();
        dfs(pass.x,pass.y,vis[pass.x][pass.y]);//很简单BFS 
    }
    printf("%d",vis[0][0]-1);
    return 0;
}
/*
2 1 1
0 1
1 0 
*/
*/
```

---

## 作者：abandentsky (赞：0)

题意：就是从给顶点到（0,0）点最少突破几个圈。
思路：直接优先队列就ok了，输入中给的定如果到了就加一，其他点就是父节点的权值，这样不断的跑广搜就好了。
注意，这里面小于1和大于1000的位置也是可以走的，题目中给的干草堆的位置是在[1,1000]之间的，我们可以考虑在这个外面的，那么我们直接用0来替代负无穷到1,1001来替代1000带正无穷就好了。
```c
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define MAXN 1005
#define maxnode 1000005
#define sigma_size 26
#define md 12345678
#define INF 0x3f3f3f3f
#define pii pair<int,int>
using namespace std;

bool vis[MAXN][MAXN],pos[MAXN][MAXN];
struct node
{
    int x,y,pp;
    node(int x=0,int y=0,int pp=0):x(x),y(y),pp(pp){};
    bool operator < (const node &rah) const
    {
        return pp>rah.pp;
    }
};
int dic_x[4]={0,0,-1,1};
int dic_y[4]={-1,1,0,0};
int n,xs,ys;

int solve()
{
    priority_queue<node> Q;
    vis[xs][ys]=true;
    Q.push({xs,ys,0});
    while(!Q.empty())
    {
        node X=Q.top();
        Q.pop();
        if(X.x==0&&X.y==0)
            return X.pp;
        for(int i=0;i<4;i++)
        {
            int xx=X.x+dic_x[i];
            int yy=X.y+dic_y[i];
            if(xx<0||xx>1004||yy<0||yy>1004)
                continue;
            if(vis[xx][yy])
                continue;
            vis[xx][yy]=true;
            if(pos[xx][yy])
            {
                Q.push({xx,yy,X.pp+1});
            }
            else
            {
                Q.push({xx,yy,X.pp});
            }
        }
    }
    return -1;
}

int main()
{
    scanf("%d %d %d",&n,&xs,&ys);
    int xx,yy;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&xx,&yy);
        pos[xx][yy]=true;
    }
    printf("%d\n",solve());
    return 0;
}

```


---

## 作者：Seanq (赞：0)

**luogu P1849 [USACO12MAR]拖拉机Tractor**      
感谢Chevalier提供的好思路     
我在Chevalier思路的基础上做了改进     
其实就是问至少要穿过几个环     
如图：     
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190125200954115.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzg3MjM3MA==,size_16,color_FFFFFF,t_70)

帅气~     
所以......         
影响的可能性只有围绕起点的草堆环数      
所以思路出啦！    
每次从原点BFS一遍，碰到边缘就停下、删除、记录，直到回到原点      
但是......     
这算法好慢啊！     
实测1662ms     
还不如其他的！     
但是，我们可以优化它。    
如图：     
![不好意思，放错图了](https://img-blog.csdnimg.cn/20190125201252626.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzg3MjM3MA==,size_16,color_FFFFFF,t_70)
不好意思，放错图了    
应该是：      


![在这里插入图片描述](https://img-blog.csdnimg.cn/20190125201349212.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzg3MjM3MA==,size_16,color_FFFFFF,t_70)
咦，这不还是刚刚那张图吗？   
那就直说：   
每次从上次搜到的边界再搜     
这样每个点最多搜到一次   
时间复杂度O(X^2)     
非常优秀   
实测250ms    
std:   

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define frep(i,a,b) for(int i=a;i>=b;i--)
#define MAXN 1005
#define M 50005
#define N 1005000
#define NN 8005000
int n;
struct pos{
 int x,y;
}st,s[M];
bool used[MAXN][MAXN]={0};
bool ue[MAXN][MAXN]={0};
int ans=0;
int h=1,t=0;
pos q[NN];
int sum=0; 
pos mark[NN];//上一次搜到的 
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
bool bfs(){
 h=1,t=0;
 rep(i,1,sum){
  q[++t]=mark[i];
 } 
 sum=0;
 while(h<=t){
  pos u=q[h];
  h++;
  rep(i,0,3){
   pos v=u;
   v.x+=dx[i];
   v.y+=dy[i];
   if(v.x<0||v.y<0||v.x>1002||v.y>1002) continue;
   if(ue[v.x][v.y]) continue;
   ue[v.x][v.y]=1;
   if(v.x==0&&v.y==0){
    printf("%d\n",ans);
    exit(0);
   }
   if(used[v.x][v.y]){
    sum++;
    mark[sum]=v;
    continue;
   }
   t++;
   q[t]=v;
  }
 }
 rep(i,1,sum){
  used[mark[i].x][mark[i].y]=0;
 }
 return 1;
}
int main(){
 scanf("%d",&n);
 scanf("%d%d",&st.x,&st.y);
 st.x++;
 st.y++;
 rep(i,1,n){
  scanf("%d%d",&s[i].x,&s[i].y);
  s[i].x++;
  s[i].y++;
  used[s[i].x][s[i].y]=1;
 }
 sum++;
 mark[sum]=st;
 while(bfs()){//只要还有圈 
  ans++; 
 }
 return 0;
} 
```



---

## 作者：luaddict (赞：0)

很简单的广搜，只需对到（x，y）的需要移开的干草数进行更新就行了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int xx,yx,n,m,f[1005][1005],x,y,s[1005][1005],t[50001][2],u[5]={0,1,0,-1,0},ans=9999999;
void bfs()
{
    int head=0,tail=1;
    t[0][0]=x;
    t[0][1]=y;
    f[x][y]=0;
    while(head!=tail)
    {
        for(int i=1;i<=4;i++)
        {
            int a=t[head][0]+u[i],b=t[head][1]+u[i-1];
            if(a>=1&&a<=xx&&b>=1&&b<=yx)
            {
                if(s[a][b]==1)
                {
                    if(f[a][b]>f[t[head][0]][t[head][1]]+1)
                    {
                        f[a][b]=f[t[head][0]][t[head][1]]+1;
                        t[tail][0]=a;
                        t[tail][1]=b;
                        tail=(tail+1)%50000;
                        if(a==1||b==1)
                        ans=min(ans,f[a][b]);
                    }
                }
                else
                {
                    if(f[a][b]>f[t[head][0]][t[head][1]])
                    {
                        f[a][b]=f[t[head][0]][t[head][1]];
                        t[tail][0]=a;
                        t[tail][1]=b;
                        tail=(tail+1)%50000;
                        if(a==1||b==1)
                        ans=min(ans,f[a][b]);
                    }
                }
            }
        }
        head=(head+1)%50000;
    }
    return;
}
int main()
{
    int i,j;
    cin>>n>>x>>y;
    for(i=1;i<=n;i++)
    {
        int x2,y2;
        scanf("%d%d",&x2,&y2);
        s[x2][y2]=1;
        xx=max(xx,x2);
        yx=max(yx,y2);
    }
    xx++;
    yx++;
    memset(f,127/3,sizeof(f));
    bfs();
    cout<<ans<<endl;
    return 0;
}
```

---

