# [USACO14JAN] Cross Country Skiing S

## 题目描述

冬季 Moolympics 的越野滑雪赛道由一个 $M \times N$ 的高程网格描述（$1 \leq M, N \leq 500$），每个高程在 $0$ 到 $1,000,000,000$ 之间。网格中的某些单元被指定为赛道的航点。Moolympics 的组织者希望为整个赛道分配一个难度等级 $D$，以便奶牛可以通过从一个单元滑到相邻单元（绝对高程差最多为 $D$）的方式，从任何一个航点到达另一个航点。如果一个单元的正北、正南、正东或正西方向上有另一个单元，则这两个单元是相邻的。赛道的难度等级是 $D$ 的最小值，使得所有航点都可以通过这种方式相互到达。

## 说明/提示

如果 $D = 21$，三个航点可以相互到达。如果 $D < 21$，则右上角的航点无法从其他两个航点到达。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 5
20 21 18 99 5
19 22 20 16 26
18 17 40 60 80
1 0 0 0 1
0 0 0 0 0
0 0 0 0 1```

### 输出

```
21```

# 题解

## 作者：EDqwq (赞：16)

一道水题

***

### 思路：

看了一下数据范围，直接二分+dfs可过

二分从0到11亿左右，亲测从1开始挂掉

dfs时不要回溯，直接标记，最后用check函数判断，如果这个点是关键点，且它没有被访问过，返回$false$。如果所有的都访问过，返回$true$。

***
### 注意事项：

1. 二分记录答案当check函数返回$true$时更新为mid，不要记录为l或r。不但是这道题，二分都要这么做。

1. 判断难度值是大于等于而不是大于。

***

时间复杂度为$O(nm)$，绝不可能炸掉。

### 代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

struct node{
	int x;
	int y;
}e[50010];

int n,m;
int maps[1010][1010];
int ans;
int l,r,mid;
int cnt;
int sx,sy;
int fx[4][2] = {1,0,-1,0,0,1,0,-1};
bool bk[1010][1010];
bool bkk[1010][1010];

void dfs(int x,int y){
	//cout<<"x = "<<x<<" y = "<<y<<endl;
	for(int i = 0;i <= 3;i ++){
		int xx = x + fx[i][0];
		int yy = y + fx[i][1];
		//cout<<"xx = "<<xx<<" yy = "<<yy<<endl;
		if(xx >= 1 && yy >= 1 && xx <= n && yy <= m && !bk[xx][yy]){
			if(abs(maps[xx][yy] - maps[x][y]) <= mid){
				bk[xx][yy] = true;
				dfs(xx,yy);
			}
		}
	}
}

bool check(){
	memset(bk,false,sizeof(bk));
	bk[sx][sy] = true;
	dfs(sx,sy);
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			if(bkk[i][j]){
				if(!bk[i][j])return false;
			}
		}
	}
	return true;
}

signed main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			maps[i][j] = read();
		}
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			int xx;
			xx = read();
			if(xx == 1){
				bkk[i][j] = true;
				sx = i;
				sy = j;
			}
		}
	}
	l = 0,r = 2100000000;
	while(l <= r){
		mid = (l + r) / 2;
		if(check())r = mid - 1,ans = mid;
		else l = mid + 1;
	}
	cout<<ans;
	return 0;
}
```
实话说，感觉没有绿题难度。

以此纪念考场上的一道水题

---

## 作者：DQYdqy (赞：6)

看了看大佬们的题解都是二分加bfs，然鹅可以写并查集。。。

对于每一个点可以向它右边的点和下面的点连边，权值就为两个点的高度差

然后再把所有的边按边权从小到大排序，并查集加点

最后判断当前集合是否涵盖所有的航点，如果是，就输出最后一条边的边权，否则就继续加点

## **Code**:
```cpp
#include<bits/stdc++.h>
#define N 500001
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int n,m,t,cnt,tt;ll ans;
int fa[N],ct[501][501];
int mp[501][501],sz[N],u[N];
struct dqy{ll v;int x,y;}w[N];
inline bool cmp(dqy a,dqy b){return a.v<b.v;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline pii getpos(int num){
	int x=num/m+(num%m!=0);
	int y=num-(x-1)*m;
	return make_pair(x,y);
}
int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			mp[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ct[i][j]=read(),tt+=ct[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(j!=m){
				w[++cnt].x=(i-1)*m+j;
				w[cnt].y=w[cnt].x+1;
				w[cnt].v=abs(mp[i][j]-mp[i][j+1]);
			}
			if(i!=n){
				w[++cnt].x=(i-1)*m+j;
				w[cnt].y=w[cnt].x+m;
				w[cnt].v=abs(mp[i][j]-mp[i+1][j]);
			}
		}
	sort(w+1,w+cnt+1,cmp);
	for(int i=1;i<=n*m;i++) fa[i]=i;
	for(int i=1;i<=n*m;i++){
		sz[i]=1;pii now=getpos(i);
		u[i]=ct[now.first][now.second];
	}
	for(int i=1;i<=cnt;i++){
		int x=w[i].x,y=w[i].y;
		int f1=find(x),f2=find(y);
		if(f1==f2) continue;
		sz[f1]+=sz[f2];
		u[f1]+=u[f2];fa[f2]=f1;
		if(u[f1]==tt){
			ans=w[i].v;
			break;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：iorit (赞：4)

[原题](https://www.luogu.com.cn/problem/P4955)

[翻译，~~从学校OJ偷来的~~](https://www.luogu.com.cn/paste/9iqf9z8w)

乍一看，要求最小的难度值D，于是考虑二分答案 + bfs/dfs。

如果一个关键格$(x,y)$能够到达关键格$(xi,yi)$和$(xj , yj)$

那么$(xi,yi)$也能通过$(x,y)$到达$(xj,yj)$，反之亦然。

所以只要验证：

$(x,y)$是否能够到达所有其他关键格即可。

### 代码

时间复杂度$O(NMlog\;a[i][j])$

```cpp
// 此处应有头文件 
using namespace std;
const int N = 5e2 + 10;
int n,m;
int a[N][N]; // 存地图 
bool vis[N][N]; // 是否访问过 
int fsum = 0; // 关键格数量 
bool f[N][N]; // 是否为关键格 
struct node
{
	int x,y;
};
int dx[] = {0 , 0 , -1 , 1};
int dy[] = {-1 , 1 , 0 , 0}; // 移动 
int sx,sy; // 存其中一个关键格的位置 
bool bfs(int k)
{
	memset( vis , false , sizeof(vis) );
	queue<node> q; 
	q.push( (node){sx , sy} );
	vis[sx][sy] = true;
	int sum = 0; // 已经访问到多少个关键格 
	while( !q.empty() )
	{
		node t = q.front();
		q.pop();
		if( f[t.x][t.y] )
			++sum;
		if(sum >= fsum)
			return true;
		for(int i = 0;i < 4;i++)
		{
			int xx = t.x + dx[i];
			int yy = t.y + dy[i];
			if( xx > 0 && yy > 0 && xx <= n && yy <= m && !vis[xx][yy] )
			{
				if( abs( a[t.x][t.y] - a[xx][yy] ) <= k )
				{
					q.push( (node){xx , yy} );
					vis[xx][yy] = true;
				}
			}
		}
	}
	return false;
}
bool check(int k)
{
	if( !bfs(k) )
		return false;
	return true;
}
int main()
{
	int l = 0;
	int r = 0;
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
		{
			cin >> a[i][j];
			r = max(a[i][j] , r); // 取全地图的最高点作为右界限 
		}	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
		{
			cin >> f[i][j];
			if( f[i][j] )
			{
				++fsum;
				sx = i,sy = j; // 存其中一个关键格的位置 
			}
		}
	while(l < r) // 二分答案 
	{
		int mid = l + r >> 1; // 右移一位 = /2 
		if( check(mid) )
			r = mid;
		else
			l = mid + 1;
	}
	cout << l << endl;
    return 0;
}
```


---

## 作者：ustze (赞：3)

这题还是比较简单的吧。。10min写完，难度大概是绿题  
题意是你要选定一个d值，使得在高度差最大为d时给定的点互相可达  
显然可以二分d，然后bfs判断即可（注意，互相可达其实只用一个点能到达其他点即可,这点想必都能理解）  
复杂度$O(nmlog_2w)$  
代码如下，很丑，常数也很大：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int a[N][N],b[N][N];
int vis[N][N];
int x,y;int n,m;
int nx[]={0,0,1,-1};
int ny[]={1,-1,0,0};
queue<pair<int,int> > q;
inline bool check(int mid){
    memset(vis,0,sizeof(vis));
    vis[x][y]=1;
    q.push(make_pair(x,y));
    while(!q.empty()){
        pair<int,int> p=q.front();q.pop();
        int px=p.first,py=p.second;
        for(int i=0;i<4;i++){
            int tx=px+nx[i],ty=py+ny[i];
            if(tx<1||ty<1||tx>n||ty>m) continue;
            if(!vis[tx][ty]&&abs(a[tx][ty]-a[px][py])<=mid){
                vis[tx][ty]=1;
                q.push(make_pair(tx,ty));
            }
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(b[i][j]&&!vis[i][j]) return 0;
    return 1;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            scanf("%d",&b[i][j]);
            if(b[i][j]) x=i,y=j;
        }
    int l=0,r=1e9+1,mid,ans;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：xy_xw_for_2024 (赞：2)

楼下已经讲得可以了，本蒟蒻再来完善一下

这道题是我们编程社考试第四次的第四题，自认为比较水

其实吧，这道题是我当时唯一AC的一道题（心酸）

也正是因为这道题，我留在了编程社

题目大意：

有一个M * N（2<=n,m<=500）的滑雪场，每个点都有一个高度，如果相邻两个点的高度差小于安全高度d就可以互相抵达，在滑雪场上有一些重要的点，请问d最小是多少时可以使每个重要的点都可以互相抵达

标准答案：二分+BFS

看到这道题，当时瞬间想到的是另一道题：城市距离

两道题的数据范围都是500*500，而城市距离用两个BFS都能过，这个二分+BFS肯定也能过

∵log(maxh)=9

（P.S.二分的范围是0~maxh）

所以我们就可以打出正解代码了：：
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
inline void read(int &x) {
    x=0;int f=1;char s=getchar();
    while(s<'0'||s>'9') {
        if(s=='-')
            f=-1;
        s=getchar();
    }
    while(s>='0'&&s<='9') {
        x=x*10+s-48;
        s=getchar();
    }
    x=x*f;
}
inline void pr(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9)
        pr(x/10);
    putchar(x%10+48);
}//快读快输不解释
struct node {
    int x,y,num;//分别表示坐标和高度
}a[505][505];
int flag[505][505],i,n,j,k,m,maxh,zy,xx,yy,X[5]={0,-1,0,1,0},Y[5]={0,0,1,0,-1};
bool ma[505][505];
inline int abs(int x) {//去绝对值
    if(x<0)return -x;return x;
}
inline bool check(int sum) {//检查可不可以相互到达，相当于BFS
    memset(ma,0,sizeof(ma));//记得每次用完都要清空
    int ls=0;//这里的ls是用来剪枝的，只要搜到了所有重要的点就可以结束了
    queue<node>q;
    node t,t1;
    q.push(a[xx][yy]);//xx，yy表示的是最后一个输入的重要点的坐标，其实不需要最后一个
                      //但一定要从重要点开始
    ma[xx][yy]=1;
    while(!q.empty()) {
        t=q.front();
        q.pop();
        for(int o=1;o<5;o++) {
            t1=t;
            t1.x+=X[o];
            t1.y+=Y[o];
            t1.num=a[t1.x][t1.y].num;
            if(!ma[t1.x][t1.y]&&abs(a[t1.x][t1.y].num-a[t.x][t.y].num)<=sum) {
                q.push(t1);
                ma[t1.x][t1.y]=1;
                if(flag[t1.x][t1.y]==1)//重要的点
                    ls++;
            }
        }
        if(ls==zy-1)//最开始的重要点没算
            return 1;
    }
    return 0;
}
inline int ef(int l,int r) {
    if(l==r)
        return l;
    int mid;
    while(l<r) {
        mid=(l+r)/2;
        bool f=check(mid);//节省时间用的
        if(f&&!check(mid-1))//高度再少一个就不行了
            break;//就是正确答案
        else if(f)//不然可以再小
            r=mid;
        else//还要增大
            l=mid;
    }
    return mid;
}
int main() {
    /*freopen("skiing.in","r",stdin);
    freopen("skiing.out","w",stdout);*/
    read(n),read(m);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            read(a[i][j].num),maxh=max(maxh,a[i][j].num);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++) {
            read(flag[i][j]),a[i][j].x=i,a[i][j].y=j;
            if(flag[i][j]) {
                zy++;
                xx=i;
                yy=j;
            }
        }
    for(i=1;i<=n;i++)
        a[i][0].num=a[i][m+1].num=2147483647;
    for(i=1;i<=m;i++)
        a[0][i].num=a[n+1][i].num=2147483647;
    pr(ef(0,maxh));
}
```
[我的CSDN博客链接](https://blog.csdn.net/qq_43890190/article/details/85260435#comments)

---

## 作者：hulean (赞：2)

### 二分+DFS

看到这么多大佬写了并查集，BFS的，还没有人写DFS版的，那么肯定是要来水水积分的啦~~毕竟这可是道伪紫题呢~~!

做法楼上楼下也讲得很清楚了吧，详见代码的注释
```cpp
#include<bits/stdc++.h>
using namespace std;
bool taofen_boys[510][510];//你可以理解为tf[][]
//是否需要走到 (不要打我
int Map[510][510];
//存每个点的高度
bool vis[510][510];//是否访问到
int n,m;
int sx,sy;
//起点
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int mid;
vector<pair<int,int> >flag;
//用于存需要走到的点
inline int read()
{
    int tot=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        tot=tot*10+c-'0';
        c=getchar();
    }
    return tot;
}
inline void DFS(int x,int y)
{
	//cout<<x<<" "<<y<<endl;
	for(int i=1;i<=4;i++)//四个方向枚举
	{
		int a=x+dx[i],b=y+dy[i];
		//cout<<a<<" "<<b<<endl;
		if(a<1||b<1||a>n||b>m||vis[a][b])continue;
		if(abs(Map[a][b]-Map[x][y])>mid)continue;//是否满足要求
		vis[a][b]=1;
		DFS(a,b);
     //这里不用回溯
	}
}
inline bool check()
{
	memset(vis,0,sizeof(vis));
	vis[sx][sy]=1;
	DFS(sx,sy);
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)cout<<vis[i][j]<<" ";
		cout<<endl;
	}*/
	for(int i=0;i<flag.size();i++)
	{
		int tx=flag[i].first,ty=flag[i].second;
		if(!vis[tx][ty])return 0;
        //判断是否走过
	}
	return 1;
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)Map[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			taofen_boys[i][j]=read();
			if(taofen_boys[i][j])
			{
				sx=i,sy=j;//起点随便记录一个就行了
				flag.push_back(make_pair(i,j));
			}
		}
	/*mid=5000000;
	check();*/
	int l=0,r=1000000000,ans=0;
	while(l<=r)//二分答案
	{
		mid=l+r>>1;
		//cout<<l<<" "<<r<<" "<<mid<<" "<<ans<<" "<<check()<<endl;
		if(check())r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans<<endl;
   	return 0;
}
```

---

## 作者：Moeebius (赞：1)

## 题意简述
给你一个数字矩阵，让你求出要到达这个**矩阵**中的某几个点，行进过程中任意两数之差**最大值的最小值**
## 题目分析
根据“最大值的最小值”，可以得出使用**二分**。（答案具有单调性）
### PART 1: 主函数
使用二分板子：

```cpp
long long low=0, high=1000000000;//二分效率很高，不妨把low和high都设为极值（注意要开long long）
int ans;
while(low<=high)
{
	long long mid=(low+high)/2;
	if(check(mid))
	{
		high=mid-1;
		ans=mid;
	}
	else low=mid+1;
}
cout<<ans;
```
### PART 2: check 函数实现
接下来就是 check 函数的问题。

分析一下题面：
- 有矩阵
- 有规则（上下左右）
- 还有能走不能走
- 没有明确的起点、终点

这就是一个典型的染色问题 BFS 啊！

所以 check 函数可以用 BFS 实现，需要参数 $x$ ，代表两点之间海拔差的最大值。

由此可得伪代码：
```
check(x):
	while(没走完):
		x->下一个点,y->下一个点;
		if(越界) continue;
		if(走过) continue;
		if(海拔差>=x) continue;
		if(是关键点) 记录;
		标记走过;
		进队;
```
#### c++实现
##### 要用的东西
定义一个结构体：
```cpp
struct point{
	int x,y;//横纵坐标
};
```
手写队列和规则：
```cpp
point q[1000001],s;
int front,tail;
int dx[]={1,-1,0,0}, dy[]={0,0,1,-1};
```
判重数组：
```cpp
bool used[1000][1000];
```

##### 初始化
```cpp
memset(used,0,sizeof(used));
front=tail=1;
s.x=sx,s.y=sy;
used[s.x][s.y]=1;
q[1]=s;
```
##### 搜索部分
```cpp
while(front<=tail)
{
	point u=q[front++];//取队头
	point v;
	for(int i=0; i<4; i++)
	{
		v.x=u.x+dx[i],v.y=u.y+dy[i];//根据规则找能走的点
		if(v.x<1||v.x>n||v.y<1||v.y>m) continue;//越界
		if(used[v.x][v.y]) continue;//走过了
		if(abs(g[v.x][v.y]-g[u.x][u.y])>x) continue;//海拔差（“难度值”）太大，不走
			
		used[v.x][v.y]=1;//记录已经走过了
		if(imp[v.x][v.y]) c--;//如果是重要点，要走的个数减一
		q[++tail]=v;//入队
	}
}
return c==0;//返回有没有走完
```
加上输入输出即可 AC 。

---

## 作者：_caiji_ (赞：1)

这道题其实没有绿这么难，只需要二分+搜索就行了。
1. 读入。注意尽量不要用 `scanf` 读入 `bool`，这好像是 UB，可以用一个变量 $x$ 存输入的数，然后直接类型转换。
1. 二分。套模版就行了，等一下我们再写 $\operatorname{check}()$ 函数。
1. 搜索。直接 dfs 爆搜，注意我们只需要标记这个点能不能到，不用回溯。
1. $\operatorname{check}()$。我们先清空数组，然后随便挑一个点开始暴搜（实测 $\operatorname{dfs}(1,1)$ 能过）。然后两重 for 循环暴力检查，如果发现一个关键点没被标记，说明这个解不合法，`return 0`。如果到最后还没有 `return 0`，说明这个解合法，`return 1`。

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
const int dx[]={0,-1,0,0,1},//四方向打表
          dy[]={0,0,-1,1,0};
int n,m,a[510][510];
bool vis[510][510],key[510][510];//vis标记，key关键点
int abs(int a){//把一些常用函数封一下
    return a<0?-a:a;
}
bool checkpoint(int x,int y){
    return 1<=x&&x<=n&&1<=y&&y<=m;
}
void dfs(int x,int y,int nowans){//搜索
    for(int i=1;i<=4;i++){
        int tmpx=x+dx[i],tmpy=y+dy[i];
        if(checkpoint(tmpx,tmpy)&&!vis[tmpx][tmpy]&&\
           abs(a[x][y]-a[tmpx][tmpy])<=nowans){//这里\可以使上下两行无缝衔接，可以用这个减少一行的长度
            vis[tmpx][tmpy]=1;
            dfs(tmpx,tmpy,nowans);
          	//不用回溯
        }
    }
}
bool check(int nowans){//暴力check
    memset(vis,0,sizeof vis);
    vis[1][1]=1;//注意标记起点
    dfs(1,1,nowans);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(key[i][j]&&!vis[i][j]) return 0;
    return 1;
}
int binary(){//套模版
    int l=0,r=1e9+10;
    while(l<=r){
        int mid=l+r>>1;//1e9+1e9=2e9不爆int
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    return r+1;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1,x;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&x),key[i][j]=x;//防UB
    printf("%d",binary());
    return 0;
}
```

---

## 作者：Jsxts_ (赞：1)

# 题解 Cross Country Skiing S

[原题链接](https://www.luogu.com.cn/problem/P4955)

**题意**：给定一个 $n * m$ 的矩阵，每一个点代表它的高度，两点之间的难度值为两点高度的差的绝对值。一条路径的难度值是指该路径上相邻两格子的难度值的最大值现在给出若干个关键格子，求所有这些关键格子相互可达的最小的难度值。

**题解**：因为对每个关键点求最小值会超时，所以我们可以二分最小难度值，每一次用 check 函数时，就以 mid 为一个难度值的限定，每条路径的难度值不可以超过 mid （最小难度值），再进行 [DFS](https://blog.csdn.net/qq_41759198/article/details/81501764?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160169259219724836734464%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=160169259219724836734464&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v3~pc_rank_v2-2-81501764.first_rank_ecpm_v3_pc_rank_v2&utm_term=DFS&spm=1018.2118.3001.4187) 。这样，如果最后深搜时遍历到了每一个关键点，说明可以达成条件，继续二分。

这里给出二分求**整数**最小/最大值的模板：

最小值：
```cpp
while (l < r) {
	int mid = (l + r) / 2;
	if (check(mid)) r = mid;
	else l = mid + 1;
}
//最后l就是答案，check自己写 
```

最大值：

```cpp
while (l < r) {
	int mid = (l + r + 1) / 2;
	if (check(mid)) l = mid;
	else r = mid - 1;
}
//最后l就是答案，check自己写
```


# _Code:_

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,vis[510][510];
int a[1010][1010];
int op[510][510],ans,s;
int dx[] = {0,0,-1,1};//方向数组
int dy[] = {-1,1,0,0};

void dfs(int x,int y,int mid) {
	ans += op[x][y];//累计，如果是关键点就加了一 
	for (int i = 0;i < 4;i ++ ) {
		int nx = x + dx[i];//深搜板子 
		int ny = y + dy[i];
		if (nx < 1 || ny < 1 || nx > n || ny > m){
			continue;//边界 
		}
		if (vis[nx][ny]) continue;
		if (abs(a[x][y] - a[nx][ny]) <= mid) {
			//（重要！）mid的限制条件 
			vis[nx][ny] = 1;
			dfs(nx,ny,mid);//继续递归 
		}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= n;i ++ ) {
		for (int j = 1;j <= m;j ++ ) {
			scanf("%d",&a[i][j]);
		}
	}
	int sx,sy;
	for (int i = 1;i <= n;i ++ ) {
		for (int j = 1;j <= m;j ++ ) {
			scanf("%d",&op[i][j]);
			if (op[i][j]) {
				//从任何一个关键点出发都行
				sx = i;//记录起点 
				sy = j;
			}
			s += op[i][j];//统计有多少个关键点 
		}
	}
	int l = 0,r = 1000000000;//题目要求找最小值 
	while (l < r) {
		memset(vis,0,sizeof vis);
		int mid = (l + r) / 2;
		ans = 0;
		vis[sx][sy] = 1;
		dfs(sx,sy,mid);
		if (ans == s) r = mid;
		//把所有关键点便利过了，就是check成功 
		else l = mid + 1;
	}
	printf("%d",l);//答案 
	return 0;
}
```

# END

---

## 作者：亦闻楚歌起 (赞：0)

很明显，这个题和图论有关

能从一个格子滑到另一个格子

不就是从一个点走到另一个点嘛

然后我翻了一下

**~~竟然没有用最短路做的题解~~**

~~然后我就来了~~

首先我们可以认为这个是一个单源最短路

只要随便从一个重要点出发，找到到其他重要点的难度最大值，就是答案

为什么可以用单源最短路呢？

首先从一个重要点出发，这个重要点就已经走过了

走第二个重要点，更新答案

当我们要找第三个重要点的时候，我们并不知道怎么从第二个重要点走到第三个重要点

但是我们可以无花费回到第一个重要点
**因为路径相同，计算最大值为难度**

所以回到第一个重要点不需要花费，然后就可以找到第一个重要点到第三个重要点的最短路，更新答案

如此类推

为什么不找第二个点到第三个点的路径呢？

我们知道第一个点到第三个点的最短路径
和第二个点
的关系只有两种

1. 第一个点到第三个点的最短路径上包含第二个点
2. 第一个点到第三个点的最短路径上不包含第二个点

对于情况1，既然包含第二个点，而且题目定义的距离是路径最大值，那么根据
$$
\displaystyle \max(\max_{x\leq i \leq y}\{a_i\},\max_{y \leq j \leq z}\{a_j\}) = \max_{x \leq i \leq z}\{a_i\}
$$

所以1到3的最短路径就是

1到2的最短路径

2到3的最短路径

取最大值

如果从2出发，虽然有可能到3的路径小于1到3的路径

但是始终我们还要从2到1

最终的答案还是要有

1到2的最短路径

2到3的最短路径

取最大值

对于情况2

可以证明从2到3的最短路径必定经过1

用反证法证明

	由题知1到3的最短路径不经过2
        如果2到3的最短路径不经过1
        即从2到3不经过1上的所有路径
        都比
        从2经过1到3上的所有路径
        短
        
        即从2到3不经过1上的所有路径
        都比
        从2到1的所有路径和从1到3上的所有路径
        短
        
        那么1到3的最短路径就应该是从1出发经过2再到3
        于题设不符
        故2到3的最短路径必定经过1
        
综上所述，出发点的选择和中途是否返回出发点对于答案没有影响

~~说了这么多终于能进入正题了~~

我们既然知道了这题是最短路**变式**

那么就要考虑用什么算法

平均每个点大约都会有4条出边，4条入边相连

（边挺多的）

引用一句话：

dwj：spfa明明是O(nm)的，说spfa是O(nk)的都是在放p

既然spfa不能用，没有负边权

我们可以考虑一下伟大的dijkstra+小根堆

（我也不知道不加堆优化会发生什么）

这道题和普通最短路的不同就在于要把普通最短路的
$$
dis_u + edge_{u, v} < dis_v
$$
改成
$$
\max(dis_u, edge_{u, v}) < dis_v
$$
其他都不变，照常跑dijkstra就好了

小小的优化：哈希

我们一般习惯了最短路是一个点

现在他是二维怎么办？

哈希帮你解决

只需要定义点$(x, y)$的编号为$x*n+y$即可

代码：
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
template <typename T>
inline T max(T a, T b)
{
    return a > b ? a : b;
}
template <typename T>
inline void read(T &x)
{
    x = 0;
    char ch = getchar();
    while(ch > '9' or ch < '0') ch = getchar();
    while(ch >= '0' and ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
}
template <typename T>
inline T read()
{
    T x = 0;
    char ch = getchar();
    while(ch > '9' or ch < '0') ch = getchar();
    while(ch >= '0' and ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
template <typename T>
inline void write(T x)
{
    if(x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
int n, m, dep[250001], dis[250001], vis[250001], tot, head[250001], imp[250001];
inline int hash(int a, int b) // 聪明的哈希 
{
    return a * n + b;
}
inline std::pair<int, int> hsah(int k) // 通过哈希值求原来的坐标（虽然好像没咋用） 
{
    return std::make_pair(k / n, k % n);
}
struct Edge //链式前向星存图 
{
    int u, v, w;
}edge[250001 << 3];
inline void add(int a, int b, int c) // 加边，因为每个点都向外扩张4条边，所以加有向边 
{
    edge[++tot] = (Edge){head[a], b, c};
    head[a] = tot;
}
inline void dij(int);
int main()
{
    read(m); read(n);
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            read(dep[hash(i, j)]);
        }
    }
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
        	// 如果这个点的上/下/左/右没有节点，就不能加边，否则会发生玄学错误 
            if(i != 0) add(hash(i, j), hash(i - 1, j), abs(dep[hash(i, j)] - dep[hash(i - 1, j)]));
            if(j != 0) add(hash(i, j), hash(i, j - 1), abs(dep[hash(i, j)] - dep[hash(i, j - 1)]));
            if(i != m - 1) add(hash(i, j), hash(i + 1, j), abs(dep[hash(i, j)] - dep[hash(i + 1, j)]));
            if(i != n - 1) add(hash(i, j), hash(i, j + 1), abs(dep[hash(i, j)] - dep[hash(i, j + 1)]));
        }
    }
    tot = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(read<int>()) imp[++tot] = hash(i, j); // 标记重要点 
        }
    }
    dij(imp[1]); // 跑dijkstra 
    register int ans = 0;
    for(int i = 1; i <= tot; i++) ans = max(ans, dis[imp[i]]); // 更新答案 
    write(ans);
    putchar(10);
    return 0;
}
inline void dij(int k)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            dis[hash(i, j)] = 2147483647;
            vis[hash(i, j)] = 0;
        }
    }
    dis[k] = 0;
    // 小根堆 
    std::priority_queue < std::pair <int, int>, std::vector< std::pair <int, int> >, std::greater< std::pair <int, int> > > Hp;
    Hp.push(std::make_pair(0, k)); 
    while(not Hp.empty())
    {
        register int i = Hp.top().second;
        Hp.pop();
        if(vis[i]) continue;
        vis[i] = true;
        for(int j = head[i]; j; j = edge[j].u)
        {
            const int ds = max(dis[i], edge[j].w);
            // 如果有难度值更小的路线 
            if(dis[edge[j].v] >= ds)
            {
                dis[edge[j].v] = ds;
                if(not vis[edge[j].v]) Hp.push(std::make_pair(dis[edge[j].v], edge[j].v));
            }
        }
    }
}
```

---

