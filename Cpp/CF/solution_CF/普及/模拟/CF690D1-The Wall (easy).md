# The Wall (easy)

## 题目描述

### 题意翻译

给定一个长为 $C$ $（1≤C≤100）$ ，宽为 $R$ $(1≤R≤100)$ 的矩形。其中$‘.’$ 表示该区域为空，而 $‘B’$ 表示该区域为实。

现在求有多少个区域为实。

## 样例 #1

### 输入

```
3 7
.......
.......
.BB.B..
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 5
..B..
..B..
B.B.B
BBB.B
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 6
..B...
B.B.BB
BBB.BB
BBBBBB
```

### 输出

```
1
```

## 样例 #4

### 输入

```
1 1
B
```

### 输出

```
1
```

## 样例 #5

### 输入

```
10 7
.......
.......
.......
.......
.......
.......
.......
.......
...B...
B.BB.B.
```

### 输出

```
3
```

## 样例 #6

### 输入

```
8 8
........
........
........
........
.B......
.B.....B
.B.....B
.BB...BB
```

### 输出

```
2
```

# 题解

## 作者：EdenSky (赞：5)

# [CF690D1 The Wall(easy)](https://www.luogu.com.cn/problem/CF690D1)
- [更好的阅读体验](https://www.cnblogs.com/wanguan/p/17008864.html)

## 正文

很显然啊，这是在考一个叫连通块的东东，于是~~蒟蒻的~~我马上想到了连通块必备：并查集。

如果一个块四边连通了其它的块，那么合并这两个块。

当然，并查集要用二维的：

```cpp
typedef pair<int,int> pii;
pii f[1005][1005];
void init(){//初始化并查集
	for(int i=1;i<=n;i++)	for(int j=1;j<=m;j++)
		f[i][j]={i,j};
}
pii fd(pii a){//查找根
	if(f[a.fi][a.sc]==a)	return a;
	return f[a.fi][a.sc]=fd(f[a.fi][a.sc]);
}
void unio(pii a,pii b){//合并a和b所在的集合
	f[a.fi][a.sc]=fd(b);
}
```

最后就是查重，这里我用了手打的哈希表 `set`。

遍历并查集数组，将每个子节点的根节点放入 `set`，去重，最后看 `set` 的元素数就可以。

```cpp
struct set{
	int s[1000005];
	void insert(pii a){
		s[a.fi*105+a.sc]++;
	}
	int size(){
		int ret=0;
		for(int &i:s)
			if(i)	ret++;
		return ret;
	}
};
```

最后综合：

```cpp
#include<iostream>
#include<bits/stl_pair.h>
#define fi first
#define sc second
using namespace std;
typedef pair<int,int> pii;
pii f[1005][1005];
int n,m;
char a[1005][1005];
struct set{
	int s[1000005];
	void insert(pii a){
		s[a.fi*105+a.sc]++;
	}
	int size(){
		int ret=0;
		for(int &i:s)
			if(i)	ret++;
		return ret;
	}
};
set s;
void init(){
	for(int i=1;i<=n;i++)	for(int j=1;j<=m;j++)
		f[i][j]={i,j};
}
pii fd(pii a){
	if(f[a.fi][a.sc]==a)	return a;
	return f[a.fi][a.sc]=fd(f[a.fi][a.sc]);
}
void unio(pii a,pii b){
	f[a.fi][a.sc]=fd(b);
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n>>m;
	init();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='.')	continue;
			if(a[i-1][j]=='B')	unio({i-1,j},{i,j});
			if(a[i+1][j]=='B')	unio({i+1,j},{i,j});
			if(a[i][j-1]=='B')	unio({i,j-1},{i,j});
			if(a[i][j+1]=='B')	unio({i,j+1},{i,j});
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='B')	s.insert(fd({i,j}));
	cout<<s.size();
}
```

[完结！！](https://www.luogu.com.cn/record/98117184)

---

## 作者：RE_Prince (赞：2)

# CF690D1 The Wall (easy) 

[link](https://www.luogu.com.cn/problem/CF690D1)


一道求连通块板子题。

## Sol


相信大家深搜的板子都会写吧，那我这里就讲如何求连通块了。


我们考虑每枚举到一个 `B` 字符时都往四面搜索，知道一面搜不到联通块了，程序自动返回。为了防止爆栈，要加一个 $vis_{i,j}$ 来表示这里走没走过。


那上面是求连通块，那怎么求数量呢？


我们不只是调用这个函数一遍，因为 $vis$ 数组是全局的，因此我们在外层再枚举一个 $i,j$ 来表示现在枚举到以哪个格子为起点向四面扩散的联通块了。当然，那个格子必须是 `B` 并没有访问到过。这时，连通块数量 $+1$。


这里有个大坑点：四个方向，不是八个，否则会在 $76$ 个点上 WA。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101][101],x,y,i,j,k,n,m,l=0,p;
//这里我把vis和存储是否是'B'的数组混在一起了，能过，节省空间
void dfs(int x,int y)
{
	a[x][y]=0;
	if(a[x+1][y]) dfs(x+1,y);
	if(a[x-1][y]) dfs(x-1,y);
	if(a[x][y+1]) dfs(x,y+1);
	if(a[x][y-1]) dfs(x,y-1);
//	if(a[x-1][y-1]) dfs(x-1,y-1);
//	if(a[x+1][y-1]) dfs(x+1,y-1);
//	if(a[x-1][y+1]) dfs(x-1,y+1);
//	if(a[x+1][y+1]) dfs(x+1,y+1);
}
char f[1001][1001];
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			cin>>f[i][j];
			if(f[i][j]=='B') a[i][j]=1;
			else a[i][j]=0;
		}
	}	
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i][j]) dfs(i,j),l++;//搜到了，连通块++
	cout<<l;
	return 0;
}
```

---

## 作者：Super_dark (赞：2)

## 思路
这是一道求连通块的板子题。

当我们找到一个找到一个“B”时，往 __四面搜索__ ，如果找不到了自动返回。
为防止一个联通块被反复计算，我们每走一个B就把它改成“.”，就不会再走一遍了！

所以，我们在外层枚举 $i$，$j$ 来表示现在枚举到哪个格子，当枚举到的格子是“B”时，说明这是一个没走过的连通块的一部分。这时，连通块数量 $+1$，并用深搜找完这个联通块，标记为“.”。

#### 注意：是“四面搜索”，不是“八面搜索”。
## 代码实现
```
#include<bits/stdc++.h>
using namespace std;
int n,m,dx[4]= {1,-1,0,0},dy[4]= {0,0,1,-1},l;
char a[105][105];
void dfs(int x,int y) {
	a[x][y]='.';
	int i,tx,ty;
	for(i=0;i<4;i++) {
		tx=x+dx[i];
		ty=y+dy[i];
		if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&a[tx][ty]=='B') {
			a[tx][ty]='.';
			dfs(tx,ty);                      
		}
	}
}
int main(){
	int i,j;
	cin >>n>>m;
	for (int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin >>a[i][j];
	for(i=1;i<=n; i++)
		for(j=1;j<=m; j++)
			if(a[i][j]=='B') {
				dfs(i,j);
                l++;
			}
	cout <<l;
}
```


---

## 作者：Archy_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF690D1)

## 题目简述：

输入 $1$ 个长 $m$ 宽 $n$ 的矩形。其中点表示该区域为空，而 $B$ 表示该区域为实。

求有多少个区域为**实**。

## 思路：

由于实区域有可以联通，题目数据范围较小，我们可以考虑**搜索**算法。

定义一个布尔类型的二维数组，读入时如果此处为 $B$，**把此处改为真**。

再遍历这个二维数组，若此处为真，开始搜索。**先把此处改为假**，再**判断上下左右**处是否也是真，若真，接着搜。

搜完后这处实的区域就**都变成了假**，此时 $ans$ 加 $1$。

## code：
```cpp
#include<iostream>
#define r register
using namespace std;
int m,n,ans;
char a[105][105];
bool b[105][105];
void dfs(int y,int x){
	b[y][x]=false;//把此处改false，不然会死循环
	if(b[y+1][x])dfs(y+1,x);//上
	if(b[y-1][x])dfs(y-1,x);//下
	if(b[y][x+1])dfs(y,x+1);//右
	if(b[y][x-1])dfs(y,x-1);//左
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(r int i=1;i<=n;i++)
		for(r int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='B')b[i][j]=true;//此处是B
		}
	for(r int i=1;i<=n;i++)
		for(r int j=1;j<=m;j++)
			if(b[i][j]){//此处是真，也就是B
				dfs(i,j);//开始搜索
				ans++;	//记录答案
			}
	cout<<ans<<"\n";//记得换行
	return 0;
}
```

---

## 作者：xxxr_2024 (赞：1)

# 题目大意即分析
本题就是让你求一个矩阵中联通块的个数，可以用并查集，但看看数据范围 $1\le R,C \le 100$，完全可以用深搜水过去。
# 思路分析
先 $O(nm)$ 遍历每个点，如果它没被走过（标记过），那么就从这个点开始深搜。
**注意，这道题不用回溯！！** 一但 dfs 停了,就说明这个联通块都走完了，无路可走自然停止的。所以在主函数中每找见一个没有遍历过的就是一个新的联通块，所以 $ans$ 加一。

细节请参考代码注释。
# 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    const int N = 105;
    int c, r;//长、宽 
	int ans; // ans统计联通块个数，全局默认为0
    char mp[N][N]; // 地图数组，存矩阵
    // 方向数组（上下左右）
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    void dfs(int x, int y) // 深搜函数
    {
        // 因为这道题是统计联通块个数，所以不用回溯，不用终止条件，标记之后走不了了就自动停止，停止后一个联通块就被标记完了
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (mp[xx][yy] == 'B' && 1 <= xx && xx <= c && 1 <= yy && yy <= r) // 判断此处走到的点是否合法
            {
                mp[xx][yy] = '.'; // 标记走过
                dfs(xx, yy);      // 从这个点继续走
            }
        }
    }
    int work() // 主函数
    {
        cin >> c >> r;
        for (int i = 1; i <= c; i++)
        {
            for (int j = 1; j <= r; j++)
            {
                cin >> mp[i][j];
            }
        }
        for (int i = 1; i <= c; i++)
        {
            for (int j = 1; j <= r; j++)
            {
                if (mp[i][j] == 'B')
                {
                    ans++;          // 联通块个数加一
                    mp[i][j] = '.'; // 将当前点标记
                    dfs(i, j);      // 从当前点深搜查找
                }
            }
        }
        cout << ans << endl;
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```


---

## 作者：togeth1 (赞：1)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF690D1)

### [题意解析]
给你一个包含“空”和“实”的 $C \times R$ 矩阵，其中“实”的方块是可以连通的，多个相连的“实”方块可以变成一个大的“实”方块，求有多少个“实”的区域。
+ “实”方块的字母是 $B$。
+ “空”方块的表示方式是一个点。

### [思路分析]
稍微看一眼就能知道，这是一道**深搜**的板子题。但是对于一个位置 $i,j$，能跟它连通的方块位置只有**上下左右**，所以我们的深搜的方向也只有四个方向。之后写个板子就好了，把每个元素 $\verb!dfs!$ 一下，统计答案就好了。

### [贴上代码]

```cpp
#include<bits/stdc++.h>
using namespace std;
const int ii[]={1,-1,0,0};
const int jj[]={0,0,1,-1};
/*四个方向*/
int c,r,ans;
char a[110][110];
void dfs(int x,int y) {
	a[x][y] = '*';
	/*这是一个实方块，先标记它被连通了。*/
	for(int i=0; i<4; i++) {
		/*四个方向*/
		int xx= x + ii[i], yy= y + jj[i];
		/*当前的 x,y 坐标*/
		if(xx >= 1 && xx <= c && yy >= 1 && yy <= r && a[xx][yy] == 'B'){
			/*如果这个坐标没有超过左右的边界，且这个位置的数是一个实方块*/
			a[xx][yy] = '*';
			/*这是一个实方块，先标记它被连通了。*/
			dfs(xx,yy);    
			/*以这个位置继续搜索*/                  
		}
	}
}
int main(){
	cin>>c>>r;
	for (int i=1; i<=c; i++)
        for(int j=1; j<=r; j++)
            cin>>a[i][j];
	for(int i=1; i<=c; i++)
		for(int j=1; j<=r; j++)
			if(a[i][j] == 'B'){
				/*把每个矩阵元素都搜索一次，找能跟它连通的方块*/
				dfs(i,j);
                ans++;
                /*统计答案*/
			}
	cout<<ans;
	return 0;
}
```


---

## 作者：loser_seele (赞：1)

一道简单的深搜题目，统计由 B 格子组成的连通块数量。

不难想到枚举每个方向之后用并查集的思想，如果属于同类格子则合并两个格子，最后统计 B 的连通块数量即可。

可以预先把格子编号，然后对格子的编号进行合并即可。

时间复杂度 $ \mathcal{O}(n^2) $，可以通过。

因为懒得写并查集，用了 LCT 实现动态维护两点连通性。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e5+10;
const int mod=1e18;
int n,q,m,u[maxn],v[maxn],fightu[maxn],fightv[maxn],c;
int cnt=0;
int mapp[1010][1010];
int dx[9]={0,0,0,1,-1,1,1,-1,-1},dy[9]={0,1,-1,0,0,1,-1,1,-1};//所有方向坐标变化量
char op;
inline char myread()
{
op='a';
while(op!='B'&&op!='.')
op=getchar();
return op;
}//读入字符
struct Splay
{
	int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn],ans[maxn];
	void clear(int x)
	{
		ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=ans[x]=0;
		mul[x]=1;
	}
	int getch(int x)
	{
		return (ch[fa[x]][1]==x);
	}
	int isroot(int x)
	{
		clear(0);
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	void maintain(int x)
	{
		clear(0);
		siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]])%mod;
		sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]])%mod;
        ans[x]=(ans[ch[x][0]]^val[x]^ans[ch[x][1]])%mod;
	}
	void pushdown(int x)
	{
		clear(0);
		if(rev[x])
		{
			if(ch[x][0])
			rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
			if(ch[x][1])
			rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
			rev[x]=0;
		}
	}
	void update(int x)
	{
		if(!isroot(x))
		update(fa[x]);
		pushdown(x);
	}
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
		fa[x]=z;
		if(!isroot(y))
		ch[z][chy]=x;
		ch[y][chx]=ch[x][chx^1];
		fa[ch[x][chx^1]]=y;
		ch[x][chx^1]=y;
		fa[y]=x;
		maintain(y);
		maintain(x);
		maintain(z);
	}
	void splay(int x)
	{
		update(x);
		for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
		if(!isroot(f))
		rotate(getch(x)==getch(f)?f:x);
	}
	void access(int x)
	{
		for(int f=0;x;f=x,x=fa[x])
		splay(x),ch[x][1]=f,maintain(x);
	}
	void makeroot(int x)
	{
		access(x);
		splay(x);
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
	int find(int x)
	{
		access(x);
		splay(x);
		while(ch[x][0])
		x=ch[x][0];
		splay(x);
		return x;
	}
    inline void link(int x, int p)
    {
    makeroot(x);
    splay(x);
    fa[x] = p;
    }
    void split(int x, int y) 
    {
        makeroot(x);
        access(y);
        splay(y);
        return ;
    }
    inline void cut(int x, int y) 
    {
        split(x, y);
        if (ch[y][0] != x || ch[x][1]) 
        return ;
        ch[y][0] = fa[x] = 0;
        maintain(y);
        return ;
    }
    inline void merge(int x,int y)
    {
    if (find(x) != find(y)) 
    link(x,y);
    }//并查集核心
}st;//LCT板子
inline int encode(int x,int y)
{
return (x-1)*m+y;
}//编号格子
inline bool inrange(int k,int l,int r)
{
return l<=k&&k<=r;
}//判断出界
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
signed main()
{
	cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
    for(int j=1;j<=m;j++)
    {
    op=myread(),mapp[i][j]=op=='B'?1:0;
    //cout<<mapp[i][j]<<' ';
    }
    //cout<<endl;
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    for(int k=1;k<=4;k++)//枚举所有方向
    {
    int x=i+dx[k],y=j+dy[k];
    if(inrange(x,1,n)&&inrange(y,1,m)&&mapp[x][y]==mapp[i][j]&&mapp[x][y])
    st.merge(encode(i,j),encode(x,y));//合并
    }
    map<int,int>vis;
    int ans=0;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    if(mapp[i][j])
    {
    if(!vis[st.find(encode(i,j))])
    ans++;
    vis[st.find(encode(i,j))]=1;//累计答案
    //cout<<encode(i,j)<<' '<<st.find(encode(i,j))<<'\n';
    }
    cout<<ans;
}
```


---

## 作者：zwy__ (赞：0)

### 题目大意
现在给出一个 $C$ 行 $R$ 行的二维矩阵。这个矩阵由字符 $\verb!.!$ 与字符 $\verb!B!$ 组成，定义一个“区域”为：由上下左右相邻的 $\verb!B!$ 组成，现在要你求出有多少个这样的区域。
### 题目思路
看一看数据范围：$1 \le C,R \le 100$，直接放心大胆的深搜，重复以下步骤操作即可。
1. 定义两个数组，一个用来存储地图，一个用来进行标记。
2. 对于每一个未被查找过的 $\verb!B!$，从这个 $\verb!B!$ 开始查找，直到找完这个区域的所有 $\verb!B!$ 为止，并对每个查找到的 $\verb!B!$ 用数组进行标记，避免反复查找。
3. 找完这个区域以后，累加器进行统计。

### 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum;
char ch[105][105];//存储地图数组 
int f[105][105];//标记数组 
void dfs(int x,int y)//寻找“区域”部分 
{
	f[x][y]=1;
	if(ch[x-1][y]=='B'&&f[x-1][y]==0)dfs(x-1,y);
	if(ch[x+1][y]=='B'&&f[x+1][y]==0)dfs(x+1,y);
	if(ch[x][y-1]=='B'&&f[x][y-1]==0)dfs(x,y-1);
	if(ch[x][y+1]=='B'&&f[x][y+1]==0)dfs(x,y+1);
}
int main()
{
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cin>>ch[i][j];
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			//每找到一个新的'b'，则进行查找，累加器++。 
			if(ch[i][j]=='B'&&f[i][j]==0)
			{
				sum++;
				dfs(i,j);
			}
		}
	}
	cout<<sum;
	return 0;
} 
```


---

## 作者：CrazyWisdom (赞：0)

### 前言
题目传送门：[The Wall (easy)](https://www.luogu.com.cn/problem/CF690D1)

### 思路

题目要求求有多少个连通块。

我们在某一个连通块中选取任意一个代表，都可以由它搜索到同一个连通块内的元素。

利用这一特性，我们可以采取以下方法：

遍历一遍二维数组，每当找到一个实区域，就从它开始搜索；显见，连通块内的所有元素都将被搜索到。

删除这个连通块，并把连通块数量加上一。具体删除方法是在遍历到连通块内的元素时将其赋值为空区域。这种方法可以避免重复遍历到同一连通块中的元素。

重复上列操作，直到数组遍历结束，显见所有的连通块都会被记录且删除。

输出记录的连通块数量。

因为数据范围很小，所以深搜的办法是可行的。

看代码。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int C, R, MAP[105][105], nxt[4][2]={{1,0},{-1,0},{0,1},{0,-1}}, sum=0;
void dfs(int x, int y) {
	if(x<1 || x>C || y<1 || y>R || MAP[x][y]==0) {
		return;
	}
	MAP[x][y]=0;//删除连通块内的实区域元素
	for(int i=0;i<4;i++) {
		dfs(x+nxt[i][0],y+nxt[i][1]);//搜索连通块内的其他元素
	}
}
int main () {
	cin>>C>>R;
	for(int i=1;i<=C;i++) {
		for(int j=1;j<=R;j++) {
			char x;
			cin>>x;
			if(x=='.') {//个人癖好，把字符处理转为数字处理
				MAP[i][j]=0;
			} else {
				MAP[i][j]=1;
			}
		}
	}
	for(int i=1;i<=C;i++) {
		for(int j=1;j<=R;j++) {
			if(MAP[i][j]==1) {//检测到实区域
				sum++;//增加连通块数量
			}
			dfs(i, j);//从代表为起点搜索兼删除当下连通块
		}
	}
	cout<<sum;
	return 0;
}
```

### 后记
简单看了看题解区里的其他大佬，都打的二维并查集。

我太蒻了，看了数据范围就随手写了个深搜，竟然过了。

补充一句：感觉这个普通并查集也能做，思路大概就是先对每个元素一维编号然后 combine。这个思路纯口胡，不保证过。

最后：有问题欢迎指出。

谢谢收看。


---

## 作者：WaterSky (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/CF690D1)

这一道题是搜索题目，一开始开个循环判断每一个区域的空实，如果是实区块，就进入 $dfs$ 函数。

## $dfs$ 函数
- 将自己变为虚。
- 往自己的四周寻找合法的区块，再判断是否为自己的里的实区块。
- 如果是，那么就再次进入 $dfs$ 函数，重新进行。

## $AC$ 程序：
```
#include<bits/stdc++.h>
using namespace std;
char a[105][105];
long long n,m,ans;
long long dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
void dfs(long long x,long long y) //定义搜索函数。 
{
	long long X,Y;
	a[x][y]='.';//将找到的这一个区域由实变为空，代表已经找到过了，不用再继续找下去了。
	for(int i=0;i<4;i++) 
	{
		X=x+dx[i],Y=y+dy[i]; //往自己的四个方向寻找。
		if(X>=1 && X<=n && Y>=1 && Y<=m && a[X][Y]=='B') //如果寻找的方向同时满足：不超过范围和实两个条件，就符合搜索条件，那么继续往那一个方向搜索。
			dfs(X,Y);       
	}
	return;
}
int main(){
	cin>>n>>m;//输入。
	for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];//输入。
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='B') 
				dfs(i,j),ans++;//逐个寻找每一个未被删除的连通块，答案增加。
	cout<<ans;//输出。
	return 0;
}
```

---

## 作者：LBYYSM_123 (赞：0)

### 前言  
看到大佬用一个叫并查集的东东，本蒟蒻瑟瑟发抖，只好掏出自己的**深度优先搜索** 。 
### 思路
每遇到一个 `B` 字符，就将该字符变为 `.` ，便搜周围与其相连通的 `B`  字符。
为了防止搜索重复，就将每一个搜过的点变为 `.` 。最后进行统计，每搜到一个块，数量就加一。   
**注意**：题目要求为四面搜索，而不是八面搜索。
### Code:
```cpp
#include<bits/stdc++.h>
#define x2 ( x + dx[i] )
#define y2 ( y + dy[i] )
using namespace std;
int n,m,ans;char a[101][101]; 
const int dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};
void dfs(int x,int y){
	a[x][y]='.';
	for(int i=1;i<=4;i++)
		if(x2>=1&&x2<=n&&y2>=1&&y2<=m&&a[x2][y2]=='B') 
			a[x2][y2]='.',dfs(x2,y2);              
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='B')
				dfs(i,j),ans++;
	cout<<ans;		
	return 0;
}
```

---

## 作者：Guizy (赞：0)

- ### **题目大意**
这题就是给你一个矩阵（用 `.` 和 `B`）组成，现在让你判断，`B` 字符一共组成了多少个连通块。

- ### **思路**
很显然，对于这种求连通块的东西，我们可以用 BFS 算法实现。具体我们要循环找到每一个 `B`，判断它是否有被找过（用一个二维数组实现），如果没有找过，就把和它相邻的 `B` 全部标记，然后答案加上 $1$。

- ### **实现**

具体请看代码:

```cpp
#include<bits/stdc++.h>
using namespace std;

char a[101][101];
int vis[101][101],ans;
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,1,-1};

struct node {
	int x,y;
};

void bfs(int sx,int sy){
	
	queue<node>q;//STL队列
	q.push({sx,sy});
	while(!q.empty()){
		node temp=q.front(); q.pop();
		for(int i=1;i<=4;i++){
			int xx=temp.x+dx[i],yy=temp.y+dy[i];
			if(a[xx][yy]=='B'&&vis[xx][yy]==0){//如果是B，并且没有被搜过，就推进队列以便继续搜索
				vis[xx][yy]=1; 
				q.push({xx,yy});
			}
		}
	}
	return ;
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!vis[i][j]&&a[i][j]=='B'){
				vis[i][j]=1;
				bfs(i,j);//搜索
				ans++;
			}
		}
	}
	
	printf("%d\n",ans);
	
}
```

---

## 作者：mgcjade (赞：0)

# [The Wall (easy)](https://www.luogu.com.cn/problem/CF690D1)

 一道十分明显的 dfs。
 
 可以用一个数组储存此处是是否可以连通,然后进行标记，每一个点都看一次，时间复杂度 $\mathcal{O(nm)}$。
 
 废话不多说，直接上代码:
```cpp

#include <bits/stdc++.h>
using namespace std;
int n,m,s;
bool b[1005][1005];
void f(int x,int y)		//搜索连通块
{
	if(b[x][y+1]&&y<m)
	{
		b[x][y+1]=0;
		f(x,y+1);
	}
	if(b[x+1][y]&&x<n)
	{
		b[x+1][y]=0;
		f(x+1,y);
	}
	if(b[x][y-1]&&y>1)
	{
		b[x][y-1]=0;
		f(x,y-1);
	}
	if(b[x-1][y]&&x>1)
	{
		b[x-1][y]=0;
		f(x-1,y);
	}
}
char ch[1005];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch);
		for(int j=0;j<m;j++)
			b[i][j+1]=(ch[j]=='.'?0:1);	//判断是否为实
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(b[i][j])	//若没有被搜索过且此处为实，进行搜索
			{
				s++;
				f(i,j);
			}
	printf("%d",s);
	return 0;
}

```


[AC](https://vjudge.net/status#un=mgcjadae&OJId=CodeForces&probNum=690D1&res=0&orderBy=run_id&language=)

---

