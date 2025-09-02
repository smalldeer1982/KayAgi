# [AGC033A] Darker and Darker

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc033/tasks/agc033_a

縦 $ H $ 行、横 $ W $ 列の白黒に塗られたマス目が与えられます。 マス目の状態は $ A_{11} $ から $ A_{HW} $ の $ HW $ 個の文字で表されており、 上から $ i $ 行目、左から $ j $ 列目にあるマスが黒色のとき $ A_{ij} $ は `#`、 上から $ i $ 行目、左から $ j $ 列目にあるマスが白色のとき $ A_{ij} $ は `.` となっています。

すべてのマスが黒色になるまで、以下の操作を繰り返し行います。

- 辺を共有して隣接するマスの中に、黒色のマスが一つ以上存在するような白色のマスすべてが黒色になる。

何回の操作を行うことになるか求めてください。 ただし、最初に与えられるマス目には少なくとも $ 1 $ つ黒色のマスが存在します。

## 说明/提示

### 制約

- $ 1\ ≦\ H,W\ ≦\ 1000 $
- $ A_{ij} $ は `#` または `.`
- 与えられるマス目には少なくとも $ 1 $ つ黒色のマスが存在する。

### Sample Explanation 1

操作を一回行うとマス目の四隅以外が黒色になり、もう一度操作を行うとすべてのマス目が黒色になります。

## 样例 #1

### 输入

```
3 3
...
.#.
...```

### 输出

```
2```

## 样例 #2

### 输入

```
6 6
..#..#
......
#..#..
......
.#....
....#.```

### 输出

```
3```

# 题解

## 作者：Fijian_Bus (赞：6)

题目大意：给你一个 $n$∗$m$ 的方格，由黑色与白色组成，黑每次可以呈十字型向外扩散，问最少需要扩散几次，使得整个方格全部都是黑。

这是一个搜索问题，容易想到广搜，用广搜妙在哪里？

样例：（黑代表#，白代表.）

```
. # .
. . .
. . #
```

看一下 $(3,2)$ 这个位置，如果用 $(1,2)$ 位置的黑去更新需要两步，但是如果用 $(3,3)$ 则需要一步，所以我们所求的最小的最大值有很可能会因为更新判断错误而出错。

而如果用广搜，我们首先将黑色的两个位置放入队列，然后进行广搜，广搜的条件即为判断这个点是否已被更新，我们可以开标记数组 $vis$ 判断是否为白色，如果是，就将其赋值为黑色，并放入队列。这样搜索的时间复杂度也会有所优化。

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define mod 1e9+7
typedef long long ll;
const ll INF=1e9+5;
long long n,m;
char mp[1005][1005];
int ans = -INF;
int dx[5]={1,-1,0,0};
int dy[5]={0,0,-1,1};

struct node {
    int x,y,step;
};

queue<node> q;

bool judge(int x,int y) // 判断格子合法性
{
    if(x<1 || x>n || y<1 || y>m)
        return false;
    return true;
}

void BFS() //（广搜模板）
{
    while(!q.empty()) {
    // 队列操作不多说
        node pre=q.front();
        q.pop();
        ans = max(ans,pre.step);
        for(int i=0; i<4; i++) {
            int mx = dx[i]+pre.x;
            int my = dy[i]+pre.y;
            if(judge(mx,my) && mp[mx][my]=='.') {
                mp[mx][my]='#';
                q.push(node{mx,my,pre.step+1});
            }
        }
    }
}

int main()
{
    scanf("%lld %lld", &n, &m);
    for(int i=1; i<=n; i++)
        scanf("%s", mp[i]+1);
    for(int i=1; i<=n; i++) {
        for(int k=1;k<=m;k++)
            if(mp[i][k]=='#') { //#黑.白
               node s = node{i,k,0};
               q.push(s);
            }
    }
    BFS();
    printf("%d\n", ans);
    return 0;
}
```

审核大大，求过~

---

## 作者：fish_love_cat (赞：3)

广搜板子题。

从题面中可以知道，这一题的出发点不止一个，我们需要把所有的初始黑点全部入队，然后把每一个队首四周的白点全部入队并染黑即可。

如果当前点的四周有黑点，那么可以肯定，这个时候无论是替代原来染哪个黑点，结果一定更劣。所以对于原来已经染过色的点就不要去动了。

最后输出所需操作最多的点的操作次数即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[1005][1005];
bool f[1005][1005];
struct wz{
    int x,y,ans;
};
int gx[]={0,0,1,-1};
int gy[]={1,-1,0,0};
queue<wz> q;
int bfs(){
    int maxx=-1;//统计次数
    while(!q.empty()){
        wz v=q.front();q.pop();
        maxx=max(maxx,v.ans);//取较大的
        for(int i=0;i<4;i++){
            wz xin;
            xin.x=v.x+gx[i];
            xin.y=v.y+gy[i];
            xin.ans=v.ans+1;
            if(f[xin.x][xin.y]) q.push(xin),f[xin.x][xin.y]=false;//白-->黑
        }
    }
    return maxx;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            f[i][j]=true;//白点标志
            if(c=='#'){
                f[i][j]=false;//黑点标志
                wz xin;
                xin.x=i,xin.y=j,xin.ans=0;
                q.push(xin);//黑点就压入
            }
        }
    }
    cout<<bfs();
    return 0;
}
```

[Accepted.](https://www.luogu.com.cn/record/109611369)

---

## 作者：Bpds1110 (赞：2)

[**原题传送门**](https://www.luogu.com.cn/problem/AT_agc033_a)
## 题面：
给出一个 $n\times m$ 的矩阵，只包含 `.` 和 `#`，每一次每一个 `#` 可以把四个方向的 `.` 变成 `#`，求出至少多少次可以使所有的 `.` 都变为 `#`。
## Solution:
我们可以用宽搜，${vis_{i_j}}$ 表示坐标为 $i,j$ 的点是否被访问过，${a_{i_j}}$ 表示当前这个点存放的字符。思路如下。

- 首先，把每个是 `#` 的位置 $i$ 和 $j$ 入队，并且 $vis_{i,j}=1$。
- 其次，从每个是 `#` 的位置（已保存在队列中）开始宽搜。我们设每个起点的坐标为 $fx,fy$。
- 接着，每次枚举从起点所到的四个方向，我们设所到的坐标为 $sx,sy$。判断这四个坐标是否满足条件。如果**下标没有越界**并且**当前的点没有被访问过**（$vis_{i_j}$ 为 $0$），就入队，并且更新当前位置变成 `#` 的最小次数。
- 重复以上步骤，直到队列为空。
- 注意：不用判断从 ${a_{fx_fy}}$ 到 ${a_{sx_sy}}$ 的次数比原本到 ${a_{sx_sy}}$ 的次数多，因为当这个坐标第一次入队时已经把 ${vis_{i_j}}$ 变为 $1$ 了。
## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1001;
int n, m, dis[N][N];
char a[N][N];
bool vis[N][N];
const int e[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1}; 
//二维数组定义四个方向 
struct node{
	int x;
	int y;
};//x坐标与y坐标 
int main()
{
	queue < node > q;//定义队列 
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			cin >> a[i][j];
			if(a[i][j] == '#')//如果为#就入队 
			{
				q.push({i, j});
				vis[i][j] = 1;//设为已经访问过 
			}
		}
	int ans = 0;//用来存放最少次数 
	while(! q.empty())
	{
		int fx = q.front().x;
		int fy = q.front().y;
		ans = ans > dis[fx][fy] ? ans : dis[fx][fy];
		//ans求出把所有点变为#的最小值，所以求最大 
		q.pop(); 
		for(int i = 0 ; i< 4; i ++)//枚举四个方向 
		{
			int sx = fx + e[i][0];
			int sy = fy + e[i][1];
			if(sx < 1 || sx > n || sy < 1 || sy > m) continue ;
			//不能越界 
			if(vis[sx][sy]) continue ;
			//如果已经访问过就不用在做了，最先访问到的一定是最小值 
			dis[sx][sy] = dis[fx][fy] + 1;//更新最小次数 
			vis[sx][sy] = 1;//设为访问过了 
			q.push({sx, sy});//入队 
		}
	}
	cout << ans;
}

```


---

## 作者：Otomachi_Una_ (赞：2)

因为最多 $1000\times1000$ 个格子，于是直接 BFS 即可。

对于已经黑了的格子先入队，染成黑色的格子向四周扫一遍，把四周格子也入队，直到队列为空。

# Code

```cpp
#include<iostream>
#include<queue>
using namespace std;
#define ll long long
const int MAXN=1e3+5;
int h,w;
int ans=0;
char a[MAXN][MAXN];
bool go[MAXN][MAXN];
struct node{
	int x,y,t;
}s;
queue<node> Q;
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int main(){
	cin>>h>>w;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++){
			cin>>a[i][j];
			if(a[i][j]=='#')
				Q.push(node{i,j,0});
		}
	while(!Q.empty()){
		s=Q.front();
		Q.pop();
		if(s.x<=0||s.y<=0||s.x>h||s.y>w)
			continue;
		if(go[s.x][s.y])
			continue;
		go[s.x][s.y]=true;
		ans=s.t;
		for(int i=0;i<4;i++)
			Q.push(node{s.x+dx[i],s.y+dy[i],s.t+1});
	}
	cout<<ans;
}
```


---

## 作者：火车司机 (赞：2)

## 简要分析

最多 $1000 \times 1000$ 个格子，因此暴力模拟染色的复杂度是正确的

类似拓扑排序，从每个黑色格子向四周染色，染过的格子再继续入队

最后暴力扫一遍所需步数最大的格子就行了

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 1005
using namespace std;
int n, m, ans, a[N][N], fx[4] = {0, 0, 1, -1}, fy[4] = {1, -1, 0, 0};
char s[N];
struct point
{
	int x, y, p;
} t;
queue<point> q;
inline int mxx(int a, int b)
{
	return a > b ? a : b;
}
signed main()
{
	scanf("%lld%lld", &n, &m);
	for (ri i = 1; i <= n; ++i)
	{
		scanf("%s", s + 1);
		for (ri j = 1; j <= m; ++j)
			if (s[j] == '#')
				a[i][j] = 1, q.push((point){i, j, a[i][j]});
	}
	while (!q.empty())
	{
		t = q.front(), q.pop();
		for (ri i = 0, x, y; i < 4; ++i)
		{
			x = t.x + fx[i], y = t.y + fy[i];
			if (x < 1 || y < 1 || x > n || y > m || a[x][y])
				continue;
			a[x][y] = t.p + 1, q.push((point){x, y, a[x][y]});
		}
	}
	for (ri i = 1; i <= n; ++i)
		for (ri j = 1; j <= m; ++j)
			ans = mxx(ans, a[i][j]);
	printf("%lld", ans - 1);
	return 0;
}
```


---

## 作者：Texas_the_Omertosa (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT4924)

### 0x00 所需知识

1. 广度优先搜索（宽度优先搜索）

1. 队列（这里使用 STL queue 队列）

### 0x01 思路

在输入时让已经是黑格的格子入队，在搜索时弹出队首元素，让其上下左右四个格子中是白格的入队，直到全部为黑格（即队列为空）。

队列中的每一个元素需要存下三个变量：

1. 它的 $x$ 坐标

1. 它的 $y$ 坐标

1. 它是第几步变黑的

每次弹出元素时更新答案步数即可。

### 0x02 AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct point
{
  int x;
  int y;
  int step;
};
queue<point> q;
int h,k,ans=-1;
char a[1005][1005];
bool f[1005][1005];
int fx[5]={0,0,0,1,-1};
int fy[5]={0,1,-1,0,0};
inline void bfs()
{
  while(!q.empty())
    {
      point ch=q.front();
      q.pop();
      ans=max(ans,ch.step);//更新
      for(int i=1;i<=4;i++)
        {
          int xx=ch.x+fx[i];
          int yy=ch.y+fy[i];
          if(xx<1||yy<1||xx>h||yy>k||a[xx][yy]=='#')continue;//越界或是黑格不入队
          a[xx][yy]='#';//变为黑格
          q.push(point{xx,yy,ch.step+1});//入队
        }
    }
}
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin>>h>>k;
  for(int i=1;i<=h;i++)
    {
      for(int j=1;j<=k;j++)
        {
          cin>>a[i][j];
          if(a[i][j]=='#')
            {
              q.push(point{i,j,0});//黑格入队
            }
        }
    }
  bfs();
  cout<<ans<<'\n';
  return 0;
}

```

求求点个赞吧，蟹蟹了！！！

---

## 作者：kaceqwq (赞：1)

# 题目大意：
在一个 $N \times M$ 且只含有 . 和 # 的字符矩阵中，其中 # 代表黑，. 代表白。点击任意一个位置，该位置以及其上，左，下，右四个相邻的位置上的数字都会变化（黑变成白，白变成黑），问：最少需要多少次点击可以把一个给定的字符矩阵全部变成黑 ( 翻译貌似错了？ )

# 分析：
根据题意，我们很容易可以得出三个性质。

1.每个位置至多只会被点击一次，因为点两次和不点击是一样的，不会影响结果。

2.若固定了第一行（不能再改变第一行），则满足题意的点击方案至多只有 $1$ 种。其原因是：当第 $i$ 行的这一位变成 #。从上到下按行使用归纳法可得上述结论，

3.点击的先后顺序不会影响最终结果。

于是，我们不妨先考虑第一行如何点击。在枚举第一行的点击方法后，就可以认为第一行“固定不动”，再考虑第 $2$ 至 $n$ 行如何点击。而按照上述性质 $2$，此时第 $2$ 至 $n$ 行的点击方案也是确定的——从第一行开始递推，当第 $i$ 行某一位为 . 时，点击第 $i+1$ 行该位置上的字符。若到达第 $n$ 行不全为 $#$，说明这种点击方式不合法。在所有合法的点击方式中取点击次数最少的就是答案。 


---

## 作者：yangmingshuo114514 (赞：1)

## 题意

已知有一个 $ H \times W $ 的黑白网格。给定这个网格的初始状态，每一秒与白格子相邻的黑格子都会蔓延到相邻的白格子里，染黑白格子。求几秒钟后网格全染黑。

## 思路

这题很容易想到 BFS。

定义一个变量存当前被染黑的格子数，每次入队就 $ + 1 $，当变量的值达到 $ H \times W $ 时就输出当前时间。定义一个数组存当前这些格子是否被染黑。

然后我们进行以下操作：

1. 先让最初就染黑的格子入队。

2. 让与队首相邻的白格子入队，标记为黑。

3. 队首出队。

## 代码

```cpp
#include<cstdio>
const int M=1e6+5;
int h,w,ql,qr,qx[M],qy[M],qt[M],mx[]={0,1,0,-1},my[]={1,0,-1,0};//用数组模拟队列，ql为队首，qr为队尾，qx、qy、qt数组存储队列数组
char ch[1005][1005];
bool vis[1005][1005];//存这些格子是否被染黑的数组
int main(){
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++){
			do ch[i][j]=getchar(); while(ch[i][j]!='.'&&ch[i][j]!='#');
			if(ch[i][j]=='#') qx[++qr]=i,qy[qr]=j,vis[i][j]=1;//最初被染黑的格子入队
		}
	while(1){
		++ql;//队首出队
		for(int i=0;i<4;i++){
			if(qr==h*w) return printf("%d",qt[qr])&0;//如果队尾为h*w，输出当前时间
			int nx=qx[ql]+mx[i],ny=qy[ql]+my[i];//与队首相邻的格子坐标
			if(nx>=1&&nx<=h&&ny>=1&&ny<=w&&!vis[nx][ny]) vis[nx][ny]=1,qx[++qr]=nx,qy[qr]=ny,qt[qr]=qt[ql]+1;//如果没超出地图且没被染黑就入队
		}
	}
}

---

## 作者：Chicken_Rrog (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_agc033_a#submit)

图不是太大，直接宽搜就可以过。

## 题意
给出一个矩阵，由黑色与白色组成，黑每次可以呈十字型向外扩散，问最少需要扩散几次，使得整个方格全部都是黑。( 题目好像写错了，写成全白了 ) 。

## 思路

在输入时如果是黑色就看做起点，直接放入队列里。然后就可以进行广搜了，每次更新到所在点的最少操作数就好了，直接看代码吧。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
queue<pair<int,int> > q;
char a[1005][1005];
int ds[1005][1005];
bool vs[1005][1005];
int fx[4]={0,0,1,-1};
int fy[4]={1,-1,0,0};
void bfs(){
    while(q.size()){
        int nx=q.front().first;
        int ny=q.front().second;
        q.pop();
        ans=max(ds[nx][ny],ans);//每次更新最少的操作。
        for(int i=0;i<4;i++){//枚举四个方向。
            int mx=nx+fx[i];
            int my=ny+fy[i];
            if(!vs[mx][my]&&mx>=1&&mx<=n&&my>=1&&my<=m&&a[mx][my]!='#'){//没有访问过就访问。
                vs[mx][my]=1;//标记为访问过。
                q.push(make_pair(mx,my));//将新访问的点放进队列。
                ds[mx][my]=ds[nx][ny]+1;//更新最小操作数。
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf(" %c",&a[i][j]);
            if(a[i][j]=='#') q.push(make_pair(i,j)),
            vs[i][j]=1,ds[i][j]=0;//如果是黑色就放进队列，标记为已经走过。
        }
    }
    bfs();
    printf("%d\n",ans);
    return 0;
}
```



---

