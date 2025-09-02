# Reclamation

## 题目描述

### 题意简述

给定一个大小为 $r \times c$ 的二维环形网格图，每一行的第 $1$ 格和第 $c$ 格同样相邻。  
现在按照给定的顺序将 $n$ 个格子变成障碍物。一个格子可以变成障碍的条件为该格子变成障碍后仍然存在一条从第 $1$ 行到第 $r$ 行的路径。如果一个格子不可以变成障碍，就跳过该操作并且继续处理接下来的格子。路径为四相邻规则。
您需要求出最多可以有多少个格子变成障碍物。

## 样例 #1

### 输入

```
3 4 9
2 2
3 2
2 3
3 4
3 1
1 3
2 1
1 1
1 4
```

### 输出

```
6
```

# 题解

## 作者：Social_Zhao (赞：7)

## 题意

就是说，给了一个空心的圆柱，把上面的方格往下抠。但是不能把圆柱抠断了，求能够成功抠掉的方格数。

## 做法

由于这里是个圆柱，首尾相接的，所以我们需要断环为链（复制一份）

其次，可以发现，如果出现了“抠断”的情况，说明出现了一个环，也就是说从$(i,j)$这个点和$(i,j + c)$这个点之间打通了。

要维护这样的连通性，我们可以用并查集。

详细过程

### 1 判断一个点可不可以删除

我们现在知道要判断的目标点$(x,y)$和断环为链后的对应点$(x,y+c)$。

现在我们需要检查这两个点**八连通且已删除**的相邻点中有没有在同一集合中的。如果存在，那么说明如果抠掉这个点，圆柱就断了。

### 2 删除一个点

同样，我们只需要将$(x,y)$、$(x,y+c)$与他们**八连通且已删除**的相连点合并到同一集合即可。

### 3 注意的细节

- 如果$x$越界了，则``continue``，但如果$y$越界了，就将$y$“传送”到另一边（因为圆柱上下不相连而左右相连）
- 这种方法有一个漏洞，就是当$c=1$时，我们的程序总是会判断可以删除（但实际上时不可以的），所以要再加一个特判。

这样就可以过了

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int get() {
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

const int N = 2e7 + 5;
int r, c, n, f[N], ans = 0;
const int dx[] = {1, 0, -1, 0, 1, 1, -1, -1};
const int dy[] = {0, 1, 0, -1, 1, -1, 1, -1}; //八个方向
bool delt[3005][6005];

inline int id(int x, int y) { //降维打击
	return (x - 1) * c * 2 + y;
}

inline bool ok(int &x, int &y) { //判断越界和已删除
	if(y == 0) y = c * 2;
	else if(y == c * 2 + 1) y = 1;
	return (x > 0 && x <= r && delt[x][y]);
}

inline int find(int x) { //并查集路劲压缩
	return x == f[x]? x : f[x] = find(f[x]);
}

inline bool chk(int x, int y) { //检查能否删除这个点
	int x1 = x, y1 = y + c;
	for(register int i = 0; i < 8; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if(!ok(nx, ny)) continue;
		for(register int j = 0; j < 8; j++) {
			int nx1 = x1 + dx[j], ny1 = y1 + dy[j];
			if(!ok(nx1, ny1)) continue;
			if(find(id(nx, ny)) == find(id(nx1, ny1))) { return 0; }
		}
	}
	return 1;
}

inline void merge(int a, int b) { //并查集的合并操作
	int x = find(a), y = find(b);
	f[x] = y;
}

inline void del(int x, int y) { //删除某个点
	int x1 = x, y1 = y + c;
	for(register int i = 0; i < 8; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if(ok(nx, ny)) merge(id(x, y), id(nx, ny));
		int nx1 = x1 + dx[i], ny1 = y1 + dy[i];
		if(ok(nx1, ny1)) merge(id(x1, y1), id(nx1, ny1));
	}
	delt[x][y] = 1;
	delt[x1][y1] = 1;
}

int main() {
	r = get(), c = get(), n = get();
	if(c == 1) { // 特判
		printf("0");
		return 0;
	}
	for(register int i = 1; i <= r; i++)
		for(register int j = 1; j <= c * 2; j++)
			f[id(i, j)] = id(i, j);
	while(n--) {
		int x = get(), y = get();
		if(chk(x, y)) del(x, y), ans++;
	}
	printf("%d\n", ans);
	return 0;
}
```

如有问题 & Bug，欢迎在评论区反馈

---

## 作者：youdu666 (赞：6)

# CF325D Reclamation题解
## 1、题意简化
给你一张四相邻网格图，左右边界互通。给你 $n$ 个障碍物，每次按顺序添加一个，如果该障碍物加入后，上下边界不再连通，则不加入该障碍物，问最后一共加入了多少障碍物。
## 2、基本思路
#### 2.1、破环成链
由于是左右连通的，我们可以把每一行看成一个环，也就可以想到要破环成链，复制一遍原图。注意增加障碍物时要左右同时添加。
#### 2.2、判断上下边界是否连通
简单的情况随便搞搞就能过，所以这边我们选用一种相对复杂的不连通情况：

![Reclamation1.png](https://cdn.luogu.com.cn/upload/image_hosting/agm9pxxj.png)

由于 $n$ 的范围有 $3\times10^5$，所以对于每一个障碍物是否能加入，最多只能是一个根号的判断时间，因为每一次只会添加一个障碍物，所以我们考虑以障碍物来判断是否连通。

观察上图我们可以发现，这个不合法的网格图中有一些障碍物八相邻连通围了整个圆柱一圈，所有的不合法方案都有这个特性，因为只要一圈就可以将圆柱“截断”，使得上下边界不连通。

判断是否能使上下边界连通时，由于左右图中的障碍物是相同的，则可以通过判断左右图中添加的新障碍物是否连通来判断新障碍物加入后网格图上下边界是否连通，以此判断是否要加入该障碍物。
#### 2.3、并查集判障碍物连通性
并查集可以快速查询两个点是否连通，所以本问题可以使用并查集来解决。在具体实现方面，可以让两个障碍物周围的八个网格进行配对，并将其合并至同一个并查集内。

对于并查集中集合或祖先的名字，可以想到给每个网格一个不重复的数值，来在并查集中代表这个网格。假设有一个点 $(x,y)$ 我们可以用 $(x-1)\times m+y$ 来表示一个网格的数值。
## 3、代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=3005;
inline int read()
{
    int x=0,y=1;
    char c=getchar();
    while(c>'9'||c<'0')
    {
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}
bool a[N][N<<1];
int n,m,k;
int f[N*(N<<1)];
int dx[8]={-1,0,1,1,1,0,-1,-1};
int dy[8]={1,1,1,0,-1,-1,-1,0};
int fd(int x)
{
    return f[x]==x?x:f[x]=fd(f[x]);
}
int dot(int x,int y)//计算点对所代表的数值，由1~n*(m<<1)组成，恰好不重复布满整张图
{
    return (x-1)*(m<<1)+y;
}
bool dd(int xx,int yy)
{
    for(int i=0;i<=7;i++)//双重七方向，类似于搜索，寻找恰好配对组
    for(int j=0;j<=7;j++)
    {
        int xa=xx+dx[i],ya=yy+dy[i];
        int xb=xx+dx[j],yb=yy+dy[j]+m;
        if(ya>m<<1)//因为左右打通，所以当越界时直接跳到一边，下同
        	ya=1;
        if(ya<1)
        	ya=m<<1;
        if(yb>m<<1)
        	yb=1;
        if(yb<1)
        	yb=m<<1;
        if(xa<=0||xa>n||ya<=0||ya>(m<<1)) continue;//超空间（要先判断）
        if(xb<=0||xb>n||yb<=0||yb>(m<<1)) continue;
        if(!a[xa][ya]||!a[xb][yb]) continue;//目标处没有点，搜个der
        int x=fd(dot(xa,ya)),y=fd(dot(xb,yb));//找两个目标点的最早祖先以判断是否连通
        if(x==y)//恰好配对，直接返回发现连通
        return false;
    }
    return true;
}
int ans;
int main()
{
    //freopen("Reclamation.in","r",stdin);
    n=read(),m=read(),k=read();
    if(m==1||k==0)
    {
    	printf("0\n");
    	return 0;
	}
    for(int u=1;u<=n;u++)
        for(int j=1;j<=m<<1;j++)
            f[dot(u,j)]=dot(u,j);//预处理father，为并查集做准备
    for(int i=1;i<=k;i++)
    {
        int xx=read(),yy=read();
        if(!dd(xx,yy)) continue;//判断该点左区间部分和右区间部分周围（八点）是否有连通
        /*
        证明：当周围八点有联通时无法放入该点
            周围八点有连通时，因为输入的目标点左区间部分和右区
            间部分之间相隔长度为m，则根据左右的扩展，在该点加
            入后会导致全图上下部分被分割，不合题意。
        */
        a[xx][yy]=a[xx][yy+m]=true;//根据题目要求，能放就放
        int da=dot(xx,yy),db=dot(xx,yy+m);//提前算好要更新点的坐标所代表的数值
        for(int i=0;i<=7;i++)//8个方向搜索
        {
            int xa=xx+dx[i],ya=yy+dy[i];
            int xb=xx+dx[i],yb=yy+dy[i]+m;
	        if(ya>m<<1)
	        	ya=1;
	        if(ya<1)
	        	ya=m<<1;
	        if(yb>m<<1)
	        	yb=1;
	        if(yb<1)
	        	yb=m<<1;
            if(xa>0&&ya>0&&ya<=(m<<1)&&xa<=n)//超范围
            if(a[xa][ya])//目标处有点对
            {
                int dc=dot(xa,ya);
                f[fd(dc)]=fd(da);//并查集，将目标点对的最早祖先改为更新点的最早祖先
                /*
                证明：反过来放父亲不行
                    反过来放父亲会导致更新点的父亲被重复更改，覆盖先前同样由目标点更新出来的父亲
                */
            }
            if(xb>0&&yb>0&&xb<=n&&yb<=(m<<1))
            if(a[xb][yb])
            {
                int dd=dot(xb,yb);
                f[fd(dd)]=fd(db);
            }
        }
        ans++;
    }
    printf("%d\n",ans);
}
```
## 4、hack数据
这里提供一组```hack```数据：[hack数据](https://www.luogu.com.cn/paste/c9dvepue)

这个数据```hack```掉了我曾经的代码，如果你的代码也被```hack```掉了，那么你的代码没有考虑多次穿过同一条边界再穿回来连通的数据。

## 5、闲话
讲真的这道题有点水，不像黑题，~~不然我也不会做~~。

另外，如果题解有什么缺陷可以评论提出。

---

## 作者：ethan0328 (赞：1)

## 思路

首先，因为是圆柱，所以要破环成链，即将其复制一遍。

然后，考虑如果没有从 $1$ 到 $r$ 的路径，就相当于有一条八连通的由已删除节点构成的路径连接 $1$ 和 $c$ 的路径。

所以每加入一个要删除的点，枚举两个与它八连通的点 $(x1,y1)$ 和 $(x2,y2)$，若 $(x1,y1)$ 与 $(x2,y2+c)$ 连通，则说明加入新结点后连接 $1$ 到 $c$，所以新节点不合法。

最后，考虑用并查集判结点是否连通。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+10;
int n,m,k,ans,fa[N*N*2];
bool b[N][N*2];
int walk[8][2]={{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};
int num(int x,int y)
{
	return (x-1)*m*2+y;
}
bool ok(int x,int y)
{
	if(y==m*2+1)
	{
		y=1;
	}
	if(y==0)
	{
		y=m*2;
	}
	if(x<=0||x>n)
	{
		return 0;
	}
	if(!b[x][y])
	{
		return 0;;
	}
	return 1;
}
int find(int x)
{
	if(fa[x]==x)
	{
		return x;
	}
	fa[x]=find(fa[x]);
	return fa[x];
}
bool check(int x,int y)
{
	int x1,y1,x2,y2;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			x1=x+walk[i][0];
			y1=y+walk[i][1];
			x2=x+walk[j][0];
			y2=y+walk[j][1]+m;
			if(!ok(x1,y1)||!ok(x2,y2))
			{
				continue;
			}
			if(find(num(x1,y1))==find(num(x2,y2)))
			{
				return 0;
			}
		}
	}
	return 1;
}
void del(int x,int y)
{
	int x1,y1;
	for(int i=0;i<8;i++)
	{
		x1=x+walk[i][0];
		y1=y+walk[i][1];
		if(!ok(x1,y1))
		{
			continue;
		}
		int s1=find(num(x,y)),s2=find(num(x1,y1));
		fa[s1]=s2;
		y1=y1+m;
		if(!ok(x1,y1))
		{
			continue;
		}
		s1=find(num(x,y+m));
		s2=find(num(x1,y1));
		fa[s1]=s2;
	}
	b[x][y]=1;
	b[x][y+m]=1;
}
int main()
{
	int x,y;
	cin>>n>>m>>k;
	for(int i=1;i<=n*m*2;i++)
	{
		fa[i]=i;
	}
	for(int i=1;i<=k;i++)
	{
		cin>>x>>y;
		if(check(x,y))
		{
			ans++;
			del(x,y);
		}
	}
	cout<<ans;
}
```


---

