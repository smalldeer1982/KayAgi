# Not Splitting

## 题目描述

There is a $ k \times k $ grid, where $ k $ is even. The square in row $ r $ and column $ c $ is denoted by $ (r,c) $ . Two squares $ (r_1, c_1) $ and $ (r_2, c_2) $ are considered adjacent if $ \lvert r_1 - r_2 \rvert + \lvert c_1 - c_2 \rvert = 1 $ .

An array of adjacent pairs of squares is called strong if it is possible to cut the grid along grid lines into two connected, [congruent](https://en.wikipedia.org/wiki/Congruence_(geometry)) pieces so that each pair is part of the same piece. Two pieces are congruent if one can be matched with the other by translation, rotation, and reflection, or a combination of these.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627F/7a1cba5ad185443613d7aa270876dfc93648efec.png) The picture above represents the first test case. Arrows indicate pairs of squares, and the thick black line represents the cut. You are given an array $ a $ of $ n $ pairs of adjacent squares. Find the size of the largest strong subsequence of $ a $ . An array $ p $ is a subsequence of an array $ q $ if $ p $ can be obtained from $ q $ by deletion of several (possibly, zero or all) elements.

## 说明/提示

In the first test case, the array $ a $ is not good, but if we take the subsequence $ [a_1, a_2, a_3, a_4, a_5, a_6, a_8] $ , then the square can be split as shown in the statement.

In the second test case, we can take the subsequence consisting of the last four elements of $ a $ and cut the square with a horizontal line through its center.

## 样例 #1

### 输入

```
3
8 4
1 2 1 3
2 2 2 3
3 2 3 3
4 2 4 3
1 4 2 4
2 1 3 1
2 2 3 2
4 1 4 2
7 2
1 1 1 2
2 1 2 2
1 1 1 2
1 1 2 1
1 2 2 2
1 1 2 1
1 2 2 2
1 6
3 3 3 4```

### 输出

```
7
4
1```

# 题解

## 作者：Cry_For_theMoon (赞：4)

记左下角点为 $(0,0)$，右上角点为 $(k,k)$。

重要性质：切出来的两个图形一定关于中心 $(\frac{k}{2},\frac{k}{2})$ 中心对称。

证明不难，只要考虑中心点连到某条边上，形成的部分截线，容易发现可以直接确定剩下部分截线就是关于中心点中心对称确定的。

问题可以转化为被截线横穿的 $1\times 2$ square 最少。

由于截线的中心对称性质，只需要找中点到边的一条路径，使得这条路径上劈开的 square 最少。

显然可以对 $(k+1)^2$ 个格点之间连边求解 $(\frac{k}{2},\frac{k}{2})$ 为起点的最短路。

注意到截线的中心对称要求，所以一条边的边权是 它劈开的 square 数量加上它关于中心点对称的边劈开的 square 数量。

时间复杂度 $O(n^2\log n^2)$，出成 $500$ 感觉小了，骗我去想了 $n^3$ 做法。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10,MAXK=600,INF=1e9;
const int px[4]={-1,0,1,0},py[4]={0,1,0,-1};
int t,n,k;
int cnt[MAXK][MAXK][4];
int vis[MAXK*MAXK],dis[MAXK*MAXK];
vector<pi>e[MAXK*MAXK];
struct Node{
    int u,dis;
    bool operator<(const Node& n2)const{return dis>n2.dis;}
};
priority_queue<Node>q;
int H(int i,int j){return i*(k+1)+(j+1);}
int D(int x,int y,int d){
    int dx=k/2-x,dy=k/2-y;
    x+=2*dx;y+=2*dy;
    if(d==0)d=2;
    else if(d==1)d=3;
    else if(d==2)d=0;
    else if(d==3)d=1;
    return cnt[x][y][d];
}
int valid(int x,int y){return x>=0 && x<=k && y>=0 && y<=k;}
void solve(){
    scanf("%d%d",&n,&k);
    rep(x,0,k)rep(y,0,k)rep(z,0,3)cnt[x][y][z]=0;
    rep(i,1,n){
        int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if(x1==x2){
            if(y1>y2)swap(y1,y2);
            cnt[x1][y1][0]++;
            cnt[x1-1][y1][2]++;
        }else{
            if(x1>x2)swap(x1,x2);
            cnt[x1][y1-1][1]++;
            cnt[x1][y1][3]++;
        }
    }
    int s=H(k/2,k/2),end=H(k,k)+1;
    rep(i,0,end)e[i].clear(),vis[i]=0,dis[i]=INF;
    rep(i,0,k)rep(j,0,k){
        if(i==0 || j==0 || i==k || j==k){
            e[H(i,j)].pb(mp(end,0));
        }else{
            rep(d,0,3){
                int x=i+px[d],y=j+py[d];
                if(!valid(x,y))continue;
                e[H(i,j)].push_back(mp(H(x,y),cnt[i][j][d]+D(i,j,d)));
            }
        }
    }
    dis[s]=0;q.push(((Node){s,0}));
    while(q.size()){
        Node tmp=q.top();q.pop();
        if(vis[tmp.u])continue;
        vis[tmp.u]=1;
        for(auto p:e[tmp.u]){
            if(dis[p.fr]>dis[tmp.u]+p.se){
                dis[p.fr]=dis[tmp.u]+p.se;
                q.push(((Node){p.fr,dis[p.fr]}));
            }
        }
    }
    printf("%d\n",n-dis[end]);
}
int main(){
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}

```

---

## 作者：2021hych (赞：1)

# 简要/形式化题意
给定一个 $k \times k$ 的网格（$k$ 为偶数），网格上有若干张 $1 \times 2$ 的多米诺骨牌。选取若干条格边组成一条连续的线，将网格分成两个全等的部分。问最少需要拿走几张骨牌，才能使每张骨牌所占的两个格子均属于其中一个部分。
# 题解
看似无从下手，但可以发现如果从整个格子最中间的格点（注意，是格点），向相对的两边引两条关于该格点中心对称的两条线，就能将网格分成两个全等的部分。当然这个方法是充分且必要的，感性理解一下，本人不咋会证明这个抽象的东西。

总而言之，对与 $(i,j)$ 右下角的格点，若在分割线上，则其相对于最中间格点的中心对称点，$(k-i,k-j)$ 右下角的格点也必然在分割线上。

回到原问题，最少需要拿走几张骨牌，本质上就是在问，最少会穿过几张骨牌。从图的角度看待，$(k+1)^2$ 个格点，建立一个网格图，对于一张骨牌 $(r_1,c_1)$，$(r_2,c_2)$（它所占的两个格子）。若 $r_1=r_2$，则 $(r_1-1,c_1)$ 右下角的格点与 $(r_1,c_1)$ 右下角的格点之间的边权加 $1$。若 $c_1=c_2$，则 $(r_1,c_1-1)$ 右下角的格点与 $(r_1,c_1)$ 右下角的格点之间的边权加 $1$。

至此，原问题被转化为，求一条经过中心格点且贯穿网格图（即 $(\dfrac{k}{2},\dfrac{k}{2})$ 右下角的格点）的最短路径，并且该路径满足最开始提到的那个结论。我们可以以中心格点为原点，利用 $\text{Dijkstra}$ 算法同时向两边求最短路即可。时间复杂度为 $O(k^2 \log k^2)$。

为了方便实现，$(i,j)$ 右下角的格点哈希成 $i \times (k+1)+j+1$ 存储。本质上把网格图的格边去掉，剩下的按序编号，简化建图。
# AC code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510;
const int M=1e6+10;
int t,k,n,r1,c1,r2,c2; 
int vis[M],d[M];
map<pair<int,int>,int>Map;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) {
		priority_queue<pair<int,int> >q;
		cin>>n>>k;
		for(int i=1;i<=(k+1)*(k+1);i++) d[i]=1e18;
		for(int i=1;i<=(k+1)*(k+1);i++) vis[i]=0;
		Map.clear();
		for(int i=1;i<=n;i++) {
			cin>>r1>>c1>>r2>>c2;
			if(r1>r2) swap(r1,r2);
			if(c1>c2) swap(c1,c2);
			if(r1==r2) {
				Map[make_pair((r1-1)*(k+1)+c2,r1*(k+1)+c2)]++;
				Map[make_pair(r1*(k+1)+c2,(r1-1)*(k+1)+c2)]++;
			}
			if(c1==c2) {
				Map[make_pair(r1*(k+1)+c1,r1*(k+1)+c1+1)]++;
				Map[make_pair(r1*(k+1)+c1+1,r1*(k+1)+c1)]++;
			}
		}
		d[k*k/2+k+1]=0;
		q.push(make_pair(0,k*k/2+k+1));
		while(!q.empty()) {
			int x=q.top().second;
			q.pop();
			if(vis[x]) continue;
			vis[x]=1;
			vis[k*k+2*k+2-x]=1;
			if(x<=k+1||x>k*(k+1)||x%(k+1)==1||x%(k+1)==0) {
				cout<<n-d[x]<<endl;
				break;
			}
			int y,z;
			y=x-1,z=Map[make_pair(x,y)]+Map[make_pair(k*k+2*k+2-x,k*k+2*k+2-y)];
			if(d[y]>d[x]+z) {
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));
			}
			y=x+1,z=Map[make_pair(x,y)]+Map[make_pair(k*k+2*k+2-x,k*k+2*k+2-y)];
			if(d[y]>d[x]+z) {
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));
			}
			y=x+k+1,z=Map[make_pair(x,y)]+Map[make_pair(k*k+2*k+2-x,k*k+2*k+2-y)];
			if(d[y]>d[x]+z) {
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));
			}
			y=x-k-1,z=Map[make_pair(x,y)]+Map[make_pair(k*k+2*k+2-x,k*k+2*k+2-y)];
			if(d[y]>d[x]+z) {
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));
			}
		}
	}
	return 0;
}

```

---

## 作者：Tyyyyyy (赞：1)

# CF1627F

### 题意简述
定义一个元素是由方格图中相邻方格组成的二元组。

称一个由若干元素组成的数组是**强**的，当且仅当存在一种方案，可以沿方格纸上的格线将方格纸分为两个**全等的**部分，使得数组中的每一个元素中包含的两个方格都处于同一部分。

给定一个 $k\times k$ 的方格纸和 $n$ 个元素，请求出至少需要删除多少个元素，才能使得剩余的元素组成的数组是**强**的。

$1\leq n\leq 10^5,2\leq k\leq 500,2\mid k$。

### 题目分析
对于一个合法的分割方案，需要删除的元素即为被分割线划为两半的元素。因此，我们可以考虑建立一个最短路模型。

将方格作为点，格线作为边。对于给定的元素，它们之间的格线边权为 $1$，其它边权为 $0$。则我们将 $(\frac{k}{2},\frac{k}{2})$ 作为起点，任意边界作为终点求解最短路，一定可以找到正确的答案。

需要注意的是，因为全等可以旋转，因此经过一个点 $(x,y)$ 时，应当视作 $(k-x,k-y)$ 也被经过。时间复杂度为 $O(k^2\log k)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mktp make_tuple
using namespace std;
int t,n,k;
bool vis[510][510];
map<tuple<int,int,int,int>,int>mp;
struct node
{
	int x,y,w;
	bool operator < (node b) const
	{
		return w>b.w;
	}
};
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		for(int i=1,r1,c1,r2,c2;i<=n;i++)
		{
			scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
			if(r1>r2)swap(r1,r2);
			if(c1>c2)swap(c1,c2);
			if(r1==r2)mp[mktp(r1-1,c1,r1,c1)]++,mp[mktp(r1,c1,r1-1,c1)]++;
			else mp[mktp(r1,c1-1,r1,c1)]++,mp[mktp(r1,c1,r1,c1-1)]++;
		}
		priority_queue<node>q;
		q.push((node){k/2,k/2,0});
		while(!q.empty())
		{
			node u=q.top();q.pop();
			if(vis[u.x][u.y])continue;
			vis[u.x][u.y]=1,vis[k-u.x][k-u.y]=1;
			if(!u.x||u.x==k||!u.y||u.y==k)
			{
				printf("%d\n",n-u.w);
				break;
			}
			for(int i=0;i<4;i++)
			{
				node v=(node){u.x+dx[i],u.y+dy[i],0};
				if(vis[v.x][v.y])continue;
				v.w=u.w+mp[mktp(u.x,u.y,v.x,v.y)]+mp[mktp(k-u.x,k-u.y,k-v.x,k-v.y)];
				q.push(v);
			}
		}
		for(int i=0;i<=k;i++)
			for(int j=0;j<=k;j++)vis[i][j]=0;
		mp.clear();
	}
	return 0;
}
```

---

## 作者：lkjlkjlkj2012 (赞：0)

### 前备知识
做这题首先要明白一个结论：将正方形分成全等两部分的路径，一定经过正方形中点；被正方形中点分开的两条路径中心对称。
### 思路
其实题面就是让你求没有被分割线分开的相邻格子对的最大个数，也就是被分开的格子对的最小个数。我们可以考虑在格点之间连边，边权为这一条边会分开的格子对数，由于路径关于中心对称，所以中心对称后分开的格子对数也要统计进边权。比如图中绿色的边就是由于会分开格子对增加了边权，淡蓝色的边则是因为中心对称后会分开格子对。最后跑个 dijkstra 即可。
![](https://cdn.luogu.com.cn/upload/image_hosting/yywujjmz.png)
### 代码

```cpp
// Problem: CF1627F Not Splitting
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1627F
// Memory Limit: 500 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
int t, n, k, dis[505][505], d[505][505][4], dx[4] = {-1, 0, 1, 0},
                                            dy[4] = {0, 1, 0, -1};
/*     ^0
       |
 3<- (x,y) ->1
       |
       v2
*/
bool vis[505][505];
struct Point {
  int x, y, w;
};
struct cmp {
  bool operator()(Point x, Point y) { return x.w > y.w; }
};
inline void mark(int x1, int y1, int x2, int y2) {
  if (x1 > x2) swap(x1, x2);
  if (y1 > y2) swap(y1, y2);
  if (x1 == x2) {
    d[x1 - 1][y1][2]++;
    d[x1][y1][0]++;
    d[k - x1][k - y1][2]++;
    d[k - x1 + 1][k - y1][0]++;
  } else {
    d[x1][y1 - 1][1]++;
    d[x1][y1][3]++;
    d[k - x1][k - y1][1]++;
    d[k - x1][k - y1 + 1][3]++;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    memset(dis, 0x3f, sizeof(dis));
    memset(d, 0, sizeof(d));
    memset(vis, 0, sizeof(vis));
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      mark(x1, y1, x2, y2);
    }
    // for (int i = 0; i <= k; i++)
    // for (int j = 0; j <= k; j++)
    // cout << i << " " << j << " " << d[i][j][0] << " " << d[i][j][1] << " "
    // << d[i][j][2] << " " << d[i][j][3] << endl;
    priority_queue<Point, vector<Point>, cmp> q;
    q.push((Point){k / 2, k / 2, 0});
    dis[k / 2][k / 2] = 0;
    while (!q.empty()) {
      Point now = q.top();
      q.pop();
      if (now.x == 0 || now.x == k || now.y == 0 || now.y == k) {
        cout << n - now.w << endl;
        break;
      }
      if (vis[now.x][now.y]) continue;
      vis[now.x][now.y] = vis[k - now.x][k - now.y] = true;
      for (int i = 0; i < 4; i++) {
        int nx = now.x + dx[i];
        int ny = now.y + dy[i];
        int w = now.w + d[now.x][now.y][i];
        if (w < dis[nx][ny]) {
          dis[nx][ny] = w;
          q.push((Point){nx, ny, w});
        }
      }
    }
  }
}
```

---

