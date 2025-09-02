# Colorado Potato Beetle

## 题目描述

Old MacDonald has a farm and a large potato field, $ (10^{10}+1)×(10^{10}+1) $ square meters in size. The field is divided into square garden beds, each bed takes up one square meter.

Old McDonald knows that the Colorado potato beetle is about to invade his farm and can destroy the entire harvest. To fight the insects, Old McDonald wants to spray some beds with insecticides.

So Old McDonald went to the field, stood at the center of the central field bed and sprayed this bed with insecticides. Now he's going to make a series of movements and spray a few more beds. During each movement Old McDonald moves left, right, up or down the field some integer number of meters. As Old McDonald moves, he sprays all the beds he steps on. In other words, the beds that have any intersection at all with Old McDonald's trajectory, are sprayed with insecticides.

When Old McDonald finished spraying, he wrote out all his movements on a piece of paper. Now he wants to know how many beds won't be infected after the invasion of the Colorado beetles.

It is known that the invasion of the Colorado beetles goes as follows. First some bed on the field border gets infected. Than any bed that hasn't been infected, hasn't been sprayed with insecticides and has a common side with an infected bed, gets infected as well. Help Old McDonald and determine the number of beds that won't be infected by the Colorado potato beetle.

## 样例 #1

### 输入

```
5
R 8
U 9
L 9
D 8
L 2
```

### 输出

```
101```

## 样例 #2

### 输入

```
7
R 10
D 2
L 7
U 9
D 2
R 3
D 10
```

### 输出

```
52```

# 题解

## 作者：字如其人 (赞：4)

离散化 + BFS （DFS）就可以解决这道题。 

题目大意是给你一条路线，路线上的方格不能走到，问最后能到那些方格。

很明显的搜索，但是土地的长宽太大，直接搜肯定会 TLE 。

观察题目，发现 $n$ 只有 1e3 ,想到把图离散化。具体的做法是把每条路线的终点（转折点）的行列记下来，然后对其进行离散化。

这些行列把图分割成最多 $(n+1)*(n+1)$ 个小方块。这时对于搜索的过程来说，这些小分块都被当成一个点处理，只需在统计答案时加上原来的面积即可。

具体要处理的细节看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Maxn=3005;
int ax[Maxn],ay[Maxn],nx,ny,n,px[Maxn],py[Maxn],vis[Maxn][Maxn],ans;//数组 ax 中 ax[0] 存的是数组大小 
inline int find_x(int x){return lower_bound(ax+1,ax+ax[0]+1,x)-ax;}
inline int find_y(int x){return lower_bound(ay+1,ay+ay[0]+1,x)-ay;} //离散化后的数组具有单调性，使用二分找到值 x 对应的原始编号 
void dfs(int x,int y){
	if(vis[x][y]||x<1||x>ax[0]+1||y<1||y>ay[0]+1)return; //如果越界或者在之前的路线中或者已经更新了就返回 
	vis[x][y]=2;dfs(x-1,y),dfs(x,y-1),dfs(x+1,y),dfs(x,y+1); //四个方向 
}
signed main(){
	scanf("%lld",&n);
	// 插入 x 的时候把 x-1 ，x ，x+1 都插进去 
	ax[++ax[0]]=-1,ax[++ax[0]]=0,ax[++ax[0]]=1;
	ay[++ay[0]]=-1,ay[++ay[0]]=0,ay[++ay[0]]=1;//插入起点 （0,0） 
	for(int i=1;i<=n;i++){
		char op[5];int x;
		scanf("%s",op);scanf("%lld",&x);
		if(op[0]=='R')ny+=x;
		if(op[0]=='U')nx+=x;
		if(op[0]=='L')ny-=x;
		if(op[0]=='D')nx-=x;
		px[i]=nx,py[i]=ny;
		ax[++ax[0]]=nx-1,ax[++ax[0]]=nx,ax[++ax[0]]=nx+1;
		ay[++ay[0]]=ny-1,ay[++ay[0]]=ny,ay[++ay[0]]=ny+1;
	}
	sort(ax+1,ax+ax[0]+1);sort(ay+1,ay+ay[0]+1); 
	ax[0]=unique(ax+1,ax+ax[0]+1)-(ax+1);ay[0]=unique(ay+1,ay+ay[0]+1)-(ay+1);//利用STL unique 离散化 ，返回的是新的大小 
	for(int i=1;i<=n;i++){
		int p1=find_x(px[i-1]),q1=find_y(py[i-1]),p2=find_x(px[i]),q2=find_y(py[i]);
		if(p1==p2) for(int j=min(q1,q2);j<=max(q1,q2);j++)vis[p1][j]=1;
		if(q1==q2) for(int j=min(p1,p2);j<=max(p1,p2);j++)vis[j][q1]=1; //标记走过的点 (在 dfs 中不走） 
	}
	dfs(1,1);
	for(int i=1;i<=ax[0];i++){
		for(int j=1;j<=ay[0];j++)
			if(vis[i][j]!=2)ans+=(ax[i]-ax[i-1])*(ay[j]-ay[j-1]);
	}// 最后统计答案直接暴力枚举，O（n^2） 
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：frankchenfu (赞：4)

因为这片土地的大小是$10^{10}+1$的，输入数据最大只有$10^3\times 10^6 = 10^9$，所以我们可以把这个土地看做是无限大的。

然后题目要求的是线段围成的封闭路径，所以我们可以考虑直接搜索。可是，范围高达$10^{20}$，不能搜索。因为题目中只有$10^3$条线段，所以我们可以考虑将其离散化。这样，我们就可以很愉快的在$2000\times 2000$的范围内进行`BFS`染色了，并且空间也可以接受。我们从$(0,0)$（这个是取不到的点）开始染色，没有被染色的部分就是封闭的。

在实现上，我们可以在最外面加上四条“边框”，这样就可以搜索了。代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int MAXN=2010;
const ll INF=1ll<<47;
const ll way[4][2]={{0,1},{0,-1},{1,0},{-1,0}};  

struct rect{
    ll p1,q1,p2,q2;
}rec[MAXN];

int n,tot=0;
int vis[MAXN][MAXN];
int lst[2],now[2];
map<ll,int>xpos,ypos;
vector<ll>x,y;
queue<pair<ll,ll> >q;

inline int max(int x,int y){
    return x>y?x:y;
}
inline int min(int x,int y){
    return x<y?x:y;
}

void adde(int ord){
    char opt[3];int val;
    scanf("%s%d",opt,&val);
    switch(opt[0]){
        case 'U':{
            now[0]=lst[0]-val;
            now[1]=lst[1];
            break;
        }
        case 'D':{
            now[0]=lst[0]+val;
            now[1]=lst[1];
            break;
        }
        case 'L':{
            now[0]=lst[0];
            now[1]=lst[1]-val;
            break;
        }
        case 'R':{
            now[0]=lst[0];
            now[1]=lst[1]+val;
            break;
        }
        default:{
            puts("Error");
            return;
        }
    }
    x.push_back(min(lst[0],now[0]));x.push_back(max(lst[0],now[0])+1);
    y.push_back(min(lst[1],now[1]));y.push_back(max(lst[1],now[1])+1);
    rec[ord]=(rect){min(lst[0],now[0]),min(lst[1],now[1]),max(lst[0],now[0])+1,max(lst[1],now[1])+1};
    lst[0]=now[0];lst[1]=now[1];
}

int match(vector<ll>v,ll num){  
    return find(v.begin(),v.end(),num)-v.begin();  
}  

int main(){
    x.push_back(-INF);x.push_back(INF);
    y.push_back(-INF);y.push_back(INF);
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        adde(i);
    sort(x.begin(),x.end());sort(y.begin(),y.end());
    x.resize(unique(x.begin(),x.end())-x.begin());
    y.resize(unique(y.begin(),y.end())-y.begin());
    
    for(int i=0;i<n;i++){  
        lst[0]=match(x,rec[i].p1);now[0]=match(x,rec[i].p2)-1;  
        lst[1]=match(y,rec[i].q1);now[1]=match(y,rec[i].q2)-1;  
        for(int j=lst[0];j<=now[0];j++)  
            for(int k=lst[1];k<=now[1];k++)  
                vis[j][k]=1;  
    }  
    q.push(make_pair(0,0));vis[0][0]=2;
    while(!q.empty()){
    	pair<ll,ll>u,v;
    	u=q.front();q.pop();
    	for(int i=0;i<4;i++){
    		v=u;
			v.first+=way[i][0];v.second+=way[i][1];
			if(v.first>=0&&v.first<x.size()&&v.second>=0&&v.second<y.size()&&vis[v.first][v.second]==0){  
                vis[v.first][v.second]=2;  
                q.push(v);  
            }
		}
	}
	ll ans=0;  
    for(int i=0;i<x.size()-1;i++)  
        for(int j=0;j<y.size()-1;j++)  
            if(vis[i][j]!=2)  
                ans+=(x[i+1]-x[i])*(ll)(y[j+1]-y[j]);  
    printf("%lld\n",ans);  
    return 0;
} 
```

---

## 作者：crashed (赞：3)

# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于$OIer$无论是向上向下，向左向右，距离都是$5\times 10^9$，而$OIer$最多走$\max\{X\}\times N$，也就是$10^9$步，所以$OIer$绝对走不出他的田地。也就是说，田地完全可以被认作是无穷大的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于很难对原问题直接求解，所以我们考虑求会被甲虫入侵的田地，然后再用总田地数量减去会被入侵的田地。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;但是，被入侵的田地也很难求得。不过，假如我们对原图的坐标进行离散化，那么点的数量就会变成$O(N^2)$级别的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这个时候再用$BFS$求出会被会被入侵的面积，从走过的长宽围成的长方形面积中减去这个面积就是答案。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于点的离散，我把每个线段的起点和终点都会加入离散结果。然后，同一坐标轴上非紧靠的相邻两点中间都会有一段空缺，这段空缺也会被加入到离散后的结果后。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果不加入这段空缺，那么就有可能会出现原来两点不相邻，但是在离散化之后就相邻了的情况。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;文字描述比较难懂。待会看代码。 
# 代码
```cpp
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 1005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s < '0' || '9' < s ){ if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ x = -x, putchar( '-' ); }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct node
{
	long long pos;
	int indx, type;
	node(){}
	node( const long long Pos, const int Indx, const int t )
	{
		pos = Pos, indx = Indx;
		type = t;
	}
	bool operator < ( const node & other ) const
	{
		return pos < other.pos;
	}
}XPoints[2 * MAXN], YPoints[2 * MAXN];

struct seg
{
	int sx, sy, ex, ey;
	seg(){}
	seg( const int Sx, const int Sy, const int Ex, const int Ey )
	{
		sx = Sx, sy = Sy, ex = Ex, ey = Ey;
	}
}segment[MAXN];

struct BFSNode
{
	int x, y;
	BFSNode(){}
	BFSNode( const int X, const int Y )
	{
		x = X, y = Y;
	}
};

queue<BFSNode> q;

int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
int lenX[3 * MAXN], lenY[3 * MAXN];
int N;
bool mp[3 * MAXN][3 * MAXN];

int main()
{
	char op[5];
	long long x = 0, y = 0;
	long long minY = 0, maxY = 0, minX = 0, maxX = 0;
	long long mov;
	int cnt1 = 0, cnt2 = 0;
	read( N );
	for( int i = 1 ; i <= N ; i ++ )
	{
		scanf( "%s", op );
		read( mov );
		switch( op[0] )
		{
			case 'L':
			{
				XPoints[++ cnt1] = node( x, i, 1 );
				YPoints[++ cnt2] = node( y, i, 2 );
				x -= mov;
				XPoints[++ cnt1] = node( x, i, 3 );
				YPoints[++ cnt2] = node( y, i, 4 );
				break;
			}
			case 'R':
			{
				XPoints[++ cnt1] = node( x, i, 1 );
				YPoints[++ cnt2] = node( y, i, 2 );
				x += mov;
				XPoints[++ cnt1] = node( x, i, 3 );
				YPoints[++ cnt2] = node( y, i, 4 );
				break;
			}
			case 'U':
			{
				XPoints[++ cnt1] = node( x, i, 1 );
				YPoints[++ cnt2] = node( y, i, 2 );
				y -= mov;
				XPoints[++ cnt1] = node( x, i, 3 );
				YPoints[++ cnt2] = node( y, i, 4 );
				break;
			}
			case 'D':
			{
				XPoints[++ cnt1] = node( x, i, 1 );
				YPoints[++ cnt2] = node( y, i, 2 );
				y += mov;
				XPoints[++ cnt1] = node( x, i, 3 );
				YPoints[++ cnt2] = node( y, i, 4 );
				break;
				break;
			}
		}
		minX = MIN( x, minX );
		maxX = MAX( x, maxX );
		minY = MIN( y, minY );
		maxY = MAX( y, maxY );
	}
	if( ! N )
	{
		write( 1 ), putchar( '\n' );
		return 0;
	}
	sort( XPoints + 1, XPoints + 1 + cnt1 );
	sort( YPoints + 1, YPoints + 1 + cnt2 );
	int cntX = 0;
	XPoints[0].pos = -2147483648ll;
	YPoints[0].pos = -2147483648ll;
	for( int i = 1 ; i <= cnt1 ; i ++ )
	{
		if( XPoints[i].pos ^ XPoints[i - 1].pos )
		{
			cntX ++;
			lenX[cntX] = XPoints[i].pos - ( i - 1 ? XPoints[i - 1].pos : XPoints[i].pos - 1 ) - 1;
			if( ! lenX[cntX] ) cntX --;
			cntX ++;
			lenX[cntX] = 1;
		}
		switch( XPoints[i].type )
		{
			case 1:
			{
				segment[XPoints[i].indx].sx = cntX;
				break;
			}
			case 3:
			{
				segment[XPoints[i].indx].ex = cntX;
				break;
			}
		}
	}
	int cntY = 0;
	for( int i = 1 ; i <= cnt1 ; i ++ )
	{
		if( YPoints[i].pos ^ YPoints[i - 1].pos )
		{
			cntY ++;
			lenY[cntY] = YPoints[i].pos - ( i - 1 ? YPoints[i - 1].pos : YPoints[i].pos - 1 ) - 1;
			if( ! lenY[cntY] ) cntY --;
			cntY ++;
			lenY[cntY] = 1;
		}
		switch( YPoints[i].type )
		{
			case 2:
			{
				segment[YPoints[i].indx].sy = cntY;
				break;
			}
			case 4:
			{
				segment[YPoints[i].indx].ey = cntY;
				break;
			}
		}
	}
	for( int i = 1 ; i <= N ; i ++ )
	{
		if( segment[i].sx == segment[i].ex )
		{
			for( int j = MIN( segment[i].sy, segment[i].ey ) ; j <= MAX( segment[i].sy, segment[i].ey ) ; j ++ )
			{
				mp[j][segment[i].ex] = true;
			}
		}
		else
		{
			for( int j = MIN( segment[i].sx, segment[i].ex ) ; j <= MAX( segment[i].sx, segment[i].ex ) ; j ++ )
			{
				mp[segment[i].ey][j] = true;
			}
		}
	}
	for( int i = 1 ; i <= cntX ; i ++ )
	{
		if( ! mp[1][i] )
		{
			q.push( BFSNode( 1, i ) );
			mp[1][i] = true;
		}
		if( ! mp[cntY][i] )
		{
			q.push( BFSNode( cntY, i ) );
			mp[cntY][i] = true;
		}
	}
	for( int i = 1 ; i <= cntY ; i ++ )
	{
		if( ! mp[i][1] )
		{
			q.push( BFSNode( i, 1 ) );
			mp[i][1] = true;
		}
		if( ! mp[i][cntX] )
		{
			q.push( BFSNode( i, cntX ) );
			mp[i][cntX] = true;
		}
	}
	BFSNode h;
	LL tot = 0;
	int tx, ty;
	while( ! q.empty() )
	{
		h = q.front();
		q.pop();
		tot += 1ll * lenY[h.x] * lenX[h.y];
		for( int i = 0 ; i < 4 ; i ++ )
		{
			tx = h.x + dir[i][0], ty = h.y + dir[i][1];
			if( 1 <= tx && tx <= cntY && 1 <= ty && ty <= cntX && ! mp[tx][ty] )
			{
				mp[tx][ty] = true;
				q.push( BFSNode( tx, ty ) );
			}
		}
	}
	write( 1ll * ( maxX - minX + 1 ) * ( maxY - minY + 1 ) - tot ), putchar( '\n' );
	return 0;
}
```

---

