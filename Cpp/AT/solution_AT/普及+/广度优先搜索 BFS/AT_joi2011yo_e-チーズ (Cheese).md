# チーズ (Cheese)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2011yo/tasks/joi2011yo_e

今年も JOI 町のチーズ工場がチーズの生産を始め，ねずみが巣から顔を出した．JOI 町は東西南北に区画整理されていて，各区画は巣，チーズ工場，障害物，空き地のいずれかである．ねずみは巣から出発して全てのチーズ工場を訪れチーズを $ 1 $ 個ずつ食べる．

この町には，$ N $ 個のチーズ工場があり，どの工場も $ １ $ 種類のチーズだけを生産している．チーズの硬さは工場によって異なっており，硬さ $ 1 $ から $ N $ までのチーズを生産するチーズ工場がちょうど $ 1 $ つずつある．

ねずみの最初の体力は $ 1 $ であり，チーズを $ 1 $ 個食べるごとに体力が $ 1 $ 増える．ただし，ねずみは自分の体力よりも硬いチーズを食べることはできない．

ねずみは，東西南北に隣り合う区画に $ 1 $ 分で移動することができるが，障害物の区画には入ることができない．チーズ工場をチーズを食べずに通り過ぎることもできる．すべてのチーズを食べ終えるまでにかかる最短時間を求めるプログラムを書け．ただし，ねずみがチーズを食べるのにかかる時間は無視できる．

- - - - - -

## 说明/提示

### Sample Explanation 1

\- - - - - -

### Sample Explanation 2

\- - - - - -

## 样例 #1

### 输入

```
3 3 1
S..
...
..1```

### 输出

```
4```

## 样例 #2

### 输入

```
4 5 2
.X..1
....X
.XX.S
.2.X.```

### 输出

```
12```

## 样例 #3

### 输入

```
10 10 9
.X...X.S.X
6..5X..X1X
...XXXX..X
X..9X...X.
8.X2X..X3X
...XX.X4..
XX....7X..
X..X..XX..
X...X.XX..
..X.......```

### 输出

```
91```

# 题解

## 作者：Blue_wonders (赞：2)

### 交完翻译我来交一发题解(多次bfs搜索)
## **这个题最后输出带换行，不带全错**
#### 做题思路
1. 存地图(X用-1代替，* 用0代替，S直接记录并标记0，数字还是数字)
2. 循环bfs（从上一个工厂到下一个工厂走的步数）
3. 每次总步数加上每个部分的步数
4. 输出总步数(记得换行记得换行记得换行)
#### AC代码(附注释)
[AC详情](https://www.luogu.org/recordnew/show/17051724)
```cpp
#include<bits/stdc++.h>
using namespace std;
struct point{//结构体队列 
    int x,y,dep;
} h[1000001];
int kx[5]={0,0,0,1,-1};//判断四个方向用数组存起来比较简单 
int ky[5]={0,1,-1,0,0};
int a[1001][1001];//存地图 
int vis[1001][1001]; //标记是否走过 
int n,m,l,ax,ay,s=0;
void bfs(int c,int u,int o){//bfs搜索部分 
    int tail=1,head=0;//队列 
    h[0]=(point){u,o,0};
    while(head<=tail){//保证队列不空 
        vis[u][o]=1;//标记已经走过 
        int x=h[head].x,y=h[head].y,step=h[head].dep;
        head++;//x，y，dep，表示横纵坐标以及搜索步数 
        if(a[x][y]==c){//如果发现这个点就是要找的工厂 
            ax=x;//标记上新的位置，下次循环从这里开始走 
            ay=y;
            s=s+step;//总步数是每一部分的和，所以加上这一部分走的步数 
            return;//结束bfs 
        }
        for(int i=1;i<=4;i++){//如果不是终点那么就继续沿四个方向走 
            int x0=x+kx[i];//新的点的横纵坐标 
            int y0=y+ky[i];
            if(x0>0&&x0<=n&&y0>0&&y0<=m&&a[x0][y0]!=-1&&vis[x0][y0]==0){
    			//如果新点的横坐标以及纵坐标在地图范围里并且这个点没走过以及不是障碍，那么加入队列 
                vis[x0][y0]=1;//标记走过 
                h[tail]=(point){x0,y0,step+1};
                tail++;//加入队列 
            }
        }
    }
}
int main(){
    cin>>n>>m>>l;//输入 
    char d;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>d;//字符串输入 
            if(d=='S'){//记录下起点的位置 
                ax=i;
                ay=j;
            }
            if(d=='X')a[i][j]=-1;//不能过在数组a上标记-1 
            if(d=='.')a[i][j]=0;//能走标记0 
            if(d>='1'&&d<='9')a[i][j]=d-48;//如果是工厂就标记生产的硬度 
        }
    }
    for(int i=1;i<=l;i++){//从1开始循环bfs找工厂
        memset(vis,0,sizeof(vis));//记着vis数组要每次清零 
        bfs(i,ax,ay);//第一个点表示找的工厂，ax，ay是出发的坐标 
    }
    cout<<s<<endl;//输出总步数，记得换行 
    return 0;
}
```
感谢大家能看我的题解!~

---

## 作者：细数繁星 (赞：0)

## 提示

**可爱 Atcoder，输出要换行，换行，换行！！！重要的事情说三遍！！！**

[我的惨痛经历。](https://www.luogu.com.cn/record/list?pid=AT_joi2011yo_e&user=824363&page=1)

## 思路

每个工厂的奶酪只能吃一次，且不能吃大于自己体力值的奶酪，而且每次吃完奶酪，体力值加一。所以能得到结论：**必须按顺序吃奶酪，才能取得最优解。**

注意：每一次吃完奶酪，直接从奶酪的位置开走，所以起点要更新。`bfs` 中队首最先到达目的地，不用取最小值。最重要的：因为是多次 `bfs`，所以：`vis` 数组每次要 `memset`！

## 代码


```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void solve() {
	
}

int n, m, k, arr[1005][1005], ans = 0, starti, startj;
bool vis[1005][1005];

struct node {
  int x, y, step;
};

void bfs(int end) {
  memset(vis, 0, sizeof vis);
  queue<node> q;
  q.push({starti, startj, 0});
  vis[starti][startj] = true;
  while (q.size()) {
    node now = q.front();
    q.pop();
    if (arr[now.x][now.y] == end) {
      ans += now.step;
      starti = now.x;
      startj = now.y;
      return;
    }
    int dxy[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    repq(i, 0, 4) {
      int dx = now.x + dxy[i][0], dy = now.y + dxy[i][1];
      if (dx < 1 || dx > n || dy < 1 || dy > m || vis[dx][dy] || arr[dx][dy] < 0) continue;
      vis[dx][dy] = true;
      q.push({dx, dy, now.step + 1});
    }
  }
}

main() {
//	int t; cin >> t; while (t--) solve();
  cin >> n >> m >> k;
  rep(i, 1, n) {
    rep(j, 1, m) {
      char x;
      cin >> x;
      if (x == 'X') {
        arr[i][j] = -1;
      }
      if (x == 'S') {
        starti = i; startj = j;
      }
      if (isdigit(x))  {
        arr[i][j] = x - '0';
      }
    }
  }
  rep(i, 1, k) {
    bfs(i);
  }
  cout << ans << endl;
}

```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

遇到水题，吃定水题！

观察数据范围，一个 $10^3\times10^3$ 的矩阵，但是边权为 $1$，且最多求 $9$ 次，直接跑 $n$ 遍复杂度 $O(wh)$ 的广搜。总复杂度 $O(nwh)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int x, y, v;
	node(int xi = 0, int yi = 0, int vi = 0) :
		x(xi), y(yi), v(vi) {};
}tmp;
int n, m, k, ans; char mp[1005][1005]; bool vis[1005][1005];
constexpr int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };
inline int cnt(const int& v) {
	int sx, sy, ex, ey; sx = sy = ex = ey = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; vis[i][j] = (mp[i][j] == 'X'), j++)
			if (mp[i][j] == v + '0') sx = i, sy = j;
			else if (mp[i][j] == v + '1') ex = i, ey = j;
	queue<node>q; q.push(node(sx, sy, 0));
	while (q.size()) {
		tmp = q.front(), q.pop();
		if (vis[tmp.x][tmp.y])continue; vis[tmp.x][tmp.y] = 1;
		if (tmp.x == ex && tmp.y == ey) return tmp.v;
		for (int i = 0; i ^ 4; ++i)
			if (!vis[tmp.x + dx[i]][tmp.y + dy[i]])
				q.push(node(tmp.x + dx[i], tmp.y + dy[i], tmp.v + 1));
	}
	return 0;
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m >> k; memset(vis, 1, sizeof vis);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> mp[i][j], mp[i][j] = (mp[i][j] ^ 'S' ? mp[i][j] : '0');
	for (int i = 0; i ^ k; ++i) ans += cnt(i);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：0)

### 坑点

要输出空行。

### 题目大意
给定一个地图，其中 ```X``` 处无法走，求出从 ```S``` 处按 ```S```,```1```,```2``` 到 ```N``` 的顺序走，所需求的最短距离。

### 题解
我们知道，在地图上求从一个点到另外一个点的距离可以用 bfs 实现，用数组记录走过与否，保证走过的路不重复，就可以在 $O(WH)$ 的时间内求出最短距离。

而本题就是在一个地图上有多个起点和终点，对于每一组起点和终点，我们分别进行 bfs 即可，时间复杂度 $O(NWH)$，足以通过本题。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
char mapp[1010][1010];
int vis[1010][1010];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int h,w,n;
struct Node
{
    int x, y;
    int dis;
}id[114];//记录点坐标和走到该点的距离
queue<Node> que;
int bfs(int sx, int sy, int ex, int ey)
{
    while (!que.empty())
        que.pop();
    memset(vis, 0, sizeof(vis));
    que.push((Node){sx, sy, 0});
    while (!que.empty())
    {
        Node now = que.front();
        int x=now.x,y=now.y,dis=now.dis; 
        que.pop();
        if(x==ex&&y==ey)return dis;//找到点
        for(int k=0;k<4;k++)//扩展点，往上下左右四个方向找
        {
            if(x+dx[k]<=h&&x+dx[k]>=1&&y+dy[k]<=w&&y+dy[k]>=1&&mapp[x+dx[k]][y+dy[k]]!='X'&&!vis[x+dx[k]][y+dy[k]])//符合条件
            {
                vis[x+dx[k]][y+dy[k]]=1;
                que.push((Node){x+dx[k],y+dy[k],dis+1});
            }
        }
    }
    return 114514;
}
int main()
{
    cin>>h>>w>>n;
    for(int i=1;i<=h;i++)
    for(int j=1;j<=w;j++)
    {
        cin>>mapp[i][j];
        if(mapp[i][j]=='S')id[0].x=i,id[0].y=j;
        if(mapp[i][j]>='0'&&mapp[i][j]<='9')id[mapp[i][j]-'0'].x=i,id[mapp[i][j]-'0'].y=j;
    }
    int ans=0;
    for(int i=1;i<=n;i++)//分别bfs
    {
        int x=bfs(id[i-1].x,id[i-1].y,id[i].x,id[i].y);
        //cout<<x<<endl;
        ans+=x;
    }
    cout<<ans<<endl;
}
```

---

## 作者：wssdl (赞：0)

## 解题思路

这是一道不错的 **bfs** 题目，但没标签，建议管理员大大审核时能把 **广搜** 的标签写上去。

看完题目，我们发现题目中有一个重要的线索，就是老鼠一开始精力为 $1$ ，每吃一个奶酪后精力就会加一，每次只能吃奶酪硬度小于等于精力的奶酪，这就在拼命地暗示我们必须按奶酪硬度的从小到大来吃，不然奶酪即吃不了，还浪费了时间。

大概流程：

- 我们把矩阵中数字的下标和值存到一个结构体中，起始点值设为 $0$ 。

- 按值进行从小到大的排序，把值相邻的两个点跑 bfs 求最短时间。

- 所有的最短时间加起来即为答案。

~~仁慈的~~我给大家看看样例：

```cpp
3 3 1
S..
...
..1
4

4 5 2
.X..1
....X
.XX.S
.2.X.
12

10 10 9
.X...X.S.X
6..5X..X1X
...XXXX..X
X..9X...X.
8.X2X..X3X
...XX.X4..
XX....7X..
X..X..XX..
X...X.XX..
..X.......
91
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, m, k;
int cnt, sum;
int dx[4] = {0, 1, 0, -1};  //四个方向
int dy[4] = {1, 0, -1, 0};
char a[N][N];
bool vis[N][N];
struct F {
  int w;
  int x, y;
} f[N];
struct Node {
  int x, y, s;
};
bool cmp(F A, F B) {  //按值排序
  return A.w < B.w;
}
int bfs(int x, int y, int s, int fx, int fy) {  //一个普普通通的广搜
  queue<Node> q;
  Node cur = {x, y, s};
  q.push(cur);
  memset(vis, 0, sizeof(vis));
  vis[x][y] = 1;  //记得标记起点
  while (!q.empty()) {
    Node cur = q.front();
    q.pop();
    if (cur.x == fx && cur.y == fy) {  //到达终点
      return cur.s;
    }
    for (int i = 0; i <= 3; i++) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && a[nx][ny] != 'X') {  //判断可不可以走
        vis[nx][ny] = 1;
        Node ne = {nx, ny, cur.s + 1};
        q.push(ne);
      }
    }
  }
}
int main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      if (a[i][j] == 'S') {  //起点特殊处理
        cnt++;
        f[cnt].w = 0;
        f[cnt].x = i, f[cnt].y = j;
      }
      if (a[i][j] >= '1' && a[i][j] <= '9') {  //存储数字的值与下标
        cnt++;
        f[cnt].w = a[i][j] - '0';
        f[cnt].x = i, f[cnt].y = j;
      }
    }
  }
  sort(f + 1, f + cnt + 1, cmp);
  for (int i = 1; i < cnt; i++) {
    sum += bfs(f[i].x, f[i].y, 0, f[i + 1].x, f[i + 1].y);  //累加相邻的最小时间
  }
  cout << sum;
  return 0;
}
```


内有巨坑，请勿复制！

---

## 作者：Aisaka_Taiga (赞：0)

## 基本思路

本题题目已经表达了要按工厂编号顺序吃奶酪，所以就是一个搜好几遍的广搜题，用数组来存放地图和有没有走过，步数存在结构体里~~一开始我没用结构体，用二维数组存步数，一直 TLE 两个点~~，用一个变量存下每一次广搜得到的步数，输出就好了。

对于工厂的位置，只要用数字表示就好了，把障碍赋成 $-1$，最后用循环来找每一个工厂，存一下上一次的广搜完的位置，用不到 sort。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct sb{ 
    int x,y,dep;//x，y，dep，表示横纵坐标以及搜索步数
}h[1000001];
int dx[4]={0,0,1,-1}; 
int dy[4]={1,-1,0,0};
int a[1001][1001];//存地图 
int vis[1001][1001];//标记是否走过 
int n,m,l,ax,ay,s=0;
void bfs(int w,int u,int v)
{ 
    queue<sb>q;//队列 
    q.push((sb){u,v,0});
    while(!q.empty())
	{
        vis[u][v]=1;//标记已经走过 
        sb qwq=q.front();q.pop();
        int x=qwq.x,y=qwq.y,step=qwq.dep;
        if(a[x][y]==w)//如果发现这个点就是要找的工厂 
		{
            ax=x;//标记上新的位置，下次循环从这里开始走 
            ay=y;
            s=s+step;//总步数是每一部分的和，所以加上这一部分走的步数 
            return ; 
        }
        for(int i=0;i<=3;i++)//如果不是终点那么就继续沿四个方向走
		{ 
            int x0=x+dx[i];//新的点的横纵坐标 
            int y0=y+dy[i];
            if(x0<=0||x0>n||y0<=0||y0>m||a[x0][y0]==-1||vis[x0][y0])continue;//判断是否出界 
            vis[x0][y0]=1;//标记走过 
            q.push((sb){x0,y0,step+1});
        }
    }
}
int main()
{
    cin>>n>>m>>l;
    char d;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
		{
            cin>>d;
            if(d=='S') ax=i,ay=j;//记录下起点的位置
            if(d=='X')a[i][j]=-1;//不能过在数组a上标记-1 
            if(d>='1'&&d<='9')a[i][j]=d-48;//如果是工厂就标记生产的硬度 
        }
    for(int i=1;i<=l;i++)
	{
        memset(vis,0,sizeof(vis));//vis数组要每次清零 
        bfs(i,ax,ay);//第一个点表示找的工厂，ax，ay是出发的坐标 
    }
    cout<<s<<endl;
    return 0;
}

```


---

