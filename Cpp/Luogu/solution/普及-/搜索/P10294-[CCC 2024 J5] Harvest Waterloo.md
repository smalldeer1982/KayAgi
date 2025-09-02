# [CCC 2024 J5] Harvest Waterloo

## 题目描述

有一款新出现的广受欢迎的收割模拟游戏叫做 Harvest Waterloo。游戏在一块矩形南瓜地上进行，南瓜地里有成捆的干草和不同大小的南瓜。游戏开始时，一个农民在其中一个南瓜的位置上。

农民通过在整片土地上向左、向右、向上或向下移动来收割南瓜。农民不能斜着移动，不能穿过干草，也不能离开田地。

你的工作是确定农民收获的南瓜的总价值。其中一个小南瓜值 $1$ 美元，一个中等大小的南瓜值 $5$ 美元，而一个大南瓜值 $10$ 美元。

## 说明/提示

**【样例 1 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/sppn2crp.png)

农民在第 $5$ 行第 $1$ 列开始可以收割 $6$ 个南瓜。可以收割到 $2$ 个小南瓜，$1$ 个中等大小的南瓜和 $3$ 个大南瓜。收割的南瓜的总价值是 $2 \times 1 + 1 \times 5 + 3 \times 10 = 37$。

**【样例 2 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/dni4nwdv.png)

农民在第 $2$ 行第 $4$ 列开始可以收割 $19$ 个南瓜。可以收割到 $8$ 个小南瓜，$6$ 个中等大小的南瓜和 $5$ 个大南瓜。收割的南瓜的总价值是 $8 \times 1 + 6 \times 5 + 5 \times 10 = 88$。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1\leq R,C\leq 10^5$，$1\leq R\times C\leq 10^5$。

下面的表格显示了 $15$ 分的分配方案：

| 分值 | 描述 | 范围 |
| :-: | :- | :-: |
| $1$ | 南瓜地很小并且不存在干草。 | $R \times C \leq 100$ |
| $4$ | 南瓜地很小并且干草把南瓜地分割为一些矩形区域。 | $R \times C \leq 100$ |
| $5$ | 南瓜地很小并且干草可以在任意位置。 | $R \times C \leq 100$ |
| $5$ | 南瓜地可能很大并且干草可以在任意位置。 | $R \times C \leq 10^5$ |

## 样例 #1

### 输入

```
6
6
**LMLS
S*LMMS
S*SMSM
******
LLM*MS
SSL*SS
5
1
```

### 输出

```
37
```

## 样例 #2

### 输入

```
6
6
**LMLS
S*LMMS
S*SMSM
***SLL
LLM*MS
SSL*SS
2
4
```

### 输出

```
88
```

# 题解

## 作者：superballll (赞：12)

# 题目分析

初读题时感觉太简单，看完数据范围发现自己太年轻，又感受到了被 **MLE** 支配的压迫感！行和列的数据范围为 $1\leq R\times C\leq 10^5$ 那也就是说当 $R=1$ 或者 $C=1$ 时，另外一条边都会达到最大值 $10^5$，那如果我们按这个数去开一个二维数组的话，就肯定喜提**爆零**了！那怎么办呢？

在**标准模板库**中有一个好东西，他不需要预先分配内存，这样不管 $R$ 和 $C$ 的值是多少，我们都不用担心 **MLE** 了！这就是动态数组 ```vector```！整个对输入数据的处理过程，会让自己有一种在构建邻接表的错觉，但是在使用中，几乎是与二维数组一模一样！要是非说有什么不同，可能就是下标必须得从 $0$ 开始吧，但是万幸的是：**题目中的南瓜地下标就是从 $0$ 开始的**！

定义两个动态数组，一个是 $p$ 表示这片南瓜地，类型为字符型；另一个是 $vis$ 表示有没有来过，类型为布尔型。定义的程序如下：
```
vector<char>p[100005];
vector<bool>vis[100005];
```
然后就是根据输入去构造这两个动态数组，其中要注意第一行的字符我们要给 $p[0][j]$ 因此 ```for``` 循环要从 $0$ 开始。此外，还需要定义一个字符型变量用于临时记录输入的字符，然后填入动态数组 $p$ 中，同时由于初始状态下的南瓜地都没有去过，因此 $vis$ 中就无脑放 $0$ 就可以了！构造过程的程序如下：
```
for(int i=0;i<r;i++)
	for(int j=0;j<c;j++){
		cin>>m;
		p[i].push_back(m);
		vis[i].push_back(0);
	}
```
下面就开始模拟摘南瓜的过程了，其实使用深搜和广搜都是可以的，我个人选择的是深搜。在开始搜索的过程中，要去看一下题目中给的起点是否合理，因为可能有一个大大的坑：就是给定的起点处会不会是稻草！但是好在题目中说了，**游戏开始时，一个农民在其中一个南瓜的位置上**，那也就是意味着不用对起点进行判定了，直接搜就可以了！

# 代码
```
#include<bits/stdc++.h>
using namespace std;

int r,c,sx,sy,ans=0;
char m;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1}; 
vector<char>p[100005];
vector<bool>vis[100005];

void dfs(int x,int y)
{
	if(p[x][y]=='S') ans+=1;
	else if(p[x][y]=='M') ans+=5;
	else if(p[x][y]=='L') ans+=10;
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<0||xx>=r||yy<0||yy>=c) continue; //出范围了
		if(p[xx][yy]=='*') continue; //干草走不了
		if(vis[xx][yy]==1) continue; //摘过了
		vis[xx][yy]=1;
		dfs(xx,yy);
	}
}

int main()
{
	cin>>r>>c;
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
		{
			cin>>m;
			p[i].push_back(m);
			vis[i].push_back(0);
		}
	cin>>sx>>sy;
	vis[sx][sy]=1;
	dfs(sx,sy);
	cout<<ans;
	return 0;
} 
```

---

## 作者：xiaoshumiao (赞：5)

简要题意：给定 $a,b$，求 $(a,b)$ 所在的连通块（把干草看成障碍）里的南瓜值多少钱。

我们用 BFS 搜出连通块内的所有南瓜，然后按题意计算价值即可。
```cpp
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int R=1e5+10,dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
vector<char>e[R]; vector<bool>vis[R];
int main() {
  int r,c; scanf("%d %d",&r,&c);
  for(int i=0;i<r;i++) {
  	char ch;
  	for(int j=0;j<c;j++) {
  	  scanf(" %c",&ch);
  	  e[i].push_back(ch),vis[i].push_back(false);
	}
  }
  int a,b; scanf("%d %d",&a,&b);
  int sum=0; queue<pair<int,int> >q;
  q.push(make_pair(a,b)),vis[a][b]=true;
  while(!q.empty()) {
  	pair<int,int>p=q.front(); q.pop();
  	int x=p.first,y=p.second;
  	//printf("%d %d ",x,y);
  	if(e[x][y]=='S') sum++;
  	if(e[x][y]=='M') sum+=5;
  	if(e[x][y]=='L') sum+=10;
  	for(int i=0;i<4;i++) {
  	  int xx=x+dx[i],yy=y+dy[i];
  	  if(xx>=0&&xx<r&&yy>=0&&yy<c&&e[xx][yy]!='*'&&!vis[xx][yy])
		q.push(make_pair(xx,yy)),vis[xx][yy]=true;
	}
  }
  printf("%d",sum);
  return 0;
}
```

---

## 作者：gavinliu266 (赞：2)

题解区已经有 BFS 的了，所以这是一篇带权并查集的题解。
# 思路
## 带权并查集
前置知识：并查集。

并查集模版题：[P3367](https://www.luogu.com.cn/problem/P3367)。

带权并查集，即边上带有特殊权值的并查集。
```cpp
int find(int xx) {
    if(xx != fa[xx]) return fa[xx] = find(fa[xx]);
    return xx;
}
void unionn(int ta, int tb) {
    fa[ta] = tb;
    cc[tb] += cc[ta];  // 多出来的部分，对权值进行操作，注意方向，不能写反
    cc[ta] = 0;
    return;
}
```
可以发现，它只比普通的并查集多了对权值的运算。

## 具体做法
可以把每个边权设置为每个点的价值。

每次通过一个点去修改旁边的两个点，如果两个点都不是干草，那么合并，此时权值累加到一起，最终可以自动将图分成几个联通块，每个块都有一个祖先，最后输出所求位置的祖先的权值，即是答案。

## 注意
本题不能直接开二维数组，会 MLE，所以可以考虑转化为一位数组，再进行操作。

# 代码实现
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int r, c, x, y;
char s[100005];
int a[100005], fa[100005], cc[100005];
int find(int xx) {
    if(xx != fa[xx]) return fa[xx] = find(fa[xx]);
    return xx;
}
void unionn(int ta, int tb) {
    fa[ta] = tb;
    cc[tb] += cc[ta];
    cc[ta] = 0;
    return;
}  // 带权并查集的操作
int main() {
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; ++i) {
        scanf("%s", s); // 读如字符串可以避免单个字符读入的一些问题
        for(int j = 0; j < c; ++j)
            a[i * c + j] = (s[j] == 'L' ? 10 : (s[j] == 'M' ? 5 : (s[j] == 'S' ? 1 : 0)));
    }
    for(int i = 0; i < r * c; ++i)
        fa[i] = i, cc[i] = a[i];
    scanf("%d%d", &x, &y);
    for(int i = 0; i < r * c; ++i) {
        if(!a[i]) continue;  // 这个判断很重要，只有两个都是南瓜才可以采集
        if(i % c != c - 1 && a[i + 1]) {
            int ta = find(i), tb = find(i + 1);
            if(ta != tb) unionn(ta, tb);
        }
        if(i < r * c - c && a[i + c]) {  // 边界条件
            int ta = find(i), tb = find(i + c);
            if(ta != tb) unionn(ta, tb);
        }
      // 向右与向下合并，因为向上和向左已经被合并过了
    }
    printf("%d\n", cc[find(x * c + y)]);
}
```

---

## 作者：a1111a (赞：2)

# 思路
用深度优先搜索搜一下能到达的格子即可，但由于行和列小于等于 $10^5$，所以只能用字符串数组存。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,ans,xx[]={0,0,1,-1},yy[]={1,-1,0,0};
string s[100005],v[100005];
void dfs(int x,int y){
	v[x][y]='1';
	if(s[x][y]=='S')
		ans++;
	else if(s[x][y]=='M')
		ans+=5;
	else
		ans+=10;
	for(int i=0;i<4;i++)
		if(x+xx[i]>=0&&x+xx[i]<n&&y+yy[i]>=0&&y+yy[i]<m&&v[x+xx[i]][y+yy[i]]=='0'&&s[x+xx[i]][y+yy[i]]!='*')
			dfs(x+xx[i],y+yy[i]);
	return;
}
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>s[i];
	cin>>a>>b;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			v[i]+='0';
	dfs(a,b);
	cout<<ans;
	return 0;
}
```

---

## 作者：Wy_x (赞：2)

[P10294 [CCC 2024 J5] Harvest Waterloo](https://www.luogu.com.cn/problem/P10294)

[My Blog](https://www.luogu.com.cn/article/0qgnga4l)


------------

### Solotion:

由题可知，所求的是农夫所在的一个南瓜组成的连通块，不妨使用广度优先搜索（BFS）解决。

具体方法是：当队列非空时，进行循环，每次取出队首，并尝试从该点向上下左右进行扩展，若可以扩展，则更新记录数组，累加总价值，将拓展到的点推入队列；反之，不进行操作。

记忆数组的作用是防止一个点重复被访问。

**注意**：在遍历开始时，应先判断起点，若是干草块，不操作；否则，统计总价值，将起点推入队列，更新记忆数组，开始广搜。

------------
### Code:


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int fx[4]={0,0,1,-1};
const int fy[4]={1,-1,0,0};

int r,c;
char a[5005][5005];
int z[200];
bool vis[5005][5005];
int ans;

signed main()
{
	z['S']=1;
	z['M']=5;
	z['L']=10;
	cin>>r>>c;
	for(int i=1;i<=r;i++)
	for(int j=1;j<=c;j++)
		cin>>a[i][j];
	
	int x,y;
	cin>>x>>y;
	x++;
	y++;
	//输入是以 (0,0) 为左上角，改为 (1,1)
	//横纵坐标加一
	
	queue<pair<int,int>> q;
	if(a[x][y]!='*')//起始地有南瓜
	{
		q.push(make_pair(x,y));
		//推入队列，开始遍历
		vis[x][y]=1;
		ans+=z[a[x][y]];
	}
	
	while(q.size())//BFS
	{
		int x=q.front().first;
		int y=q.front().second;
		q.pop();
		//取出队首，坐标 (x,y)
		for(int i=0;i<4;i++)
		{//(x,y) 向上下左右四个方向扩展
			int xx=x+fx[i];
			int yy=y+fy[i];
			
			if(xx<1||yy<1||xx>r||yy>c) continue;//越界
			if(a[xx][yy]=='*') continue;//不能走
			if(vis[xx][yy]) continue;//走到过
			
			vis[xx][yy]=1;//记录到过
			ans+=z[a[xx][yy]];//价值累加
			q.push(make_pair(xx,yy));
			//将该点推入队列
		}
	}
	cout<<ans;
	
	return 0;
}
```

---

## 作者：Genshin_ZFYX (赞：2)

一道简单的搜索题，我们把农夫所在位置的 dfs 遍历一遍，把所能到达的南瓜的价值加起来，输出即可。

注：本题左上角为 $(0,0)$，所以我们遍历时起点为 $(sx+1,sy+1)$。
```
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define I return
#define love 0
#define FIRESTARS ;
int n,m,sum,sx,sy;
int a[1005][1005],vis[1005][1005];
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
void dfs(int x,int y)
{
	sum+=a[x][y];
	vis[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int xx=dx[i]+x,yy=dy[i]+y;
		if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&a[xx][yy]&&!vis[xx][yy])
		dfs(xx,yy);
	}
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
    	char c;cin>>c;
    	if(c=='S')a[i][j]=1;
    	else if(c=='M')a[i][j]=5;
    	else if(c=='L')a[i][j]=10;
	}
	cin>>sx>>sy;
	dfs(sx+1,sy+1);
	cout<<sum;
	I love FIRESTARS
}

```

---

## 作者：LG086 (赞：1)

### 分析

简单 BFS 题。

输入 $R \times C$ 的土地，每输入一个字符 $ch$ 就判断是否是南瓜，再对当前位置进行赋值。  
小南瓜处设为 $1$，中等南瓜处设为 $5$，大南瓜处设为 $10$，干草处不管，默认为 $0$。  
因为 $1 \le C,R \le 10^5$，所以无法直接开大数组。  
那就在输入后设置数组大小。  
接着就是 BFS 求 $ans$，最后输出即可。

------------
### 代码

```cpp
#include<bits/stdc++.h>
#define LG086 signed
#define int long long
using namespace std;
int R,C,sx,sy,ans,dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
struct LuoGu{int x,y;};
queue<LuoGu> q;
LG086 main(){
    cin>>R>>C;
    bool used[R+10][C+10]={false};int mp[R+10][C+10];
    memset(mp,0,sizeof(mp));memset(used,false,sizeof(used));
    for(int i = 1;i <= R;i ++)
    for(int j = 1;j <= C;j ++){
        char ch;cin>>ch;
        if(ch=='*')continue;
        mp[i][j]=(ch=='S'?1:(ch=='M'?5:10));
    }
    cin>>sx>>sy;sx+=1,sy+=1;ans+=mp[sx][sy];
    LuoGu st;st.x=sx;st.y=sy;used[sx][sy]=1;q.push(st);
	while(!q.empty()){
		LuoGu nw=q.front();
		for(int i=0;i<4;i++){
			LuoGu nxt=nw;nxt.x+=dx[i],nxt.y+=dy[i];
			if(mp[nxt.x][nxt.y]==0||used[nxt.x][nxt.y]==1)
			continue;
			used[nxt.x][nxt.y]=1,q.push(nxt);
			ans+=mp[nxt.x][nxt.y];
		}q.pop();
	}cout<<ans;
}
```

---

## 作者：_Jocularly_ (赞：0)

给出地图，问角色所在的连通块内能获得的最大价值，因为角色能够向各个方向走，所以问题转化为求角色所在连通块内价值和为多少，我们直接广搜，在输入时直接把字符换成对应的价值，一边搜索一边统计答案即可。题目要求的行数和列数太大，肯定不能直接开二维数组，这里换成动态数组，注意别忘了加上起点的价值。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
int n,m;
int sx,sy;
vector<int> a[100005];
vector<int> vis[100005];
int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};
int ans;
void bfs(){
	queue<PII> q;
	q.push({sx,sy});
	vis[sx][sy] = 1;
	ans += a[sx][sy];
	while(!q.empty()){
		PII now=q.front();
		q.pop();
		int x=now.first,y=now.second;
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<0||ny<0||nx>=n||ny>=m) continue;
			if(a[nx][ny] == -1) continue;
			if(vis[nx][ny]) continue;
			vis[nx][ny] = 1;
			ans += a[nx][ny];
			q.push({nx,ny}); 
		}
	} 
}
int main(){
	cin >> n >> m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			char c;
			cin >> c;
			if(c == 'S') a[i].push_back(1);
			else if(c == 'M') a[i].push_back(5);
			else if(c == 'L') a[i].push_back(10);
			else a[i].push_back(-1);
			vis[i].push_back(0);//初始化 
		}
	}
	cin >> sx >> sy;
	bfs();
	cout << ans;
	return 0;
}

```

---

## 作者：Hy13_xsm (赞：0)

## 题目分析

有一块 $a$ 行 $b$ 列的南瓜地，里面有大、中、小三种大小的南瓜，以及干草堆。大型用 `L` 表示，中型用 `M` 表示，小型用 `S` 表示，干草堆用 `*` 表示。有一个人收南瓜，只能向上、下、左、右移动，且不能穿过干草堆。大型的价值 $10$ 美元，中型的价值
$5$ 美元，小型的价值 $1$ 美元。问这个人最多能收集到多少价值的南瓜。

## 题目解决

这很明显是在二维图上面的 DFS。我们从起点开始，逐个按方向深搜，递归不继续的条件是到达边界或者目标点上是干草块。然后输出搜到南瓜的总价值。

需要注意的是，这里南瓜地是从坐标 $(0,0)$ 开始的，一些喜欢从 $(1,1)$ 开始的同学需要改改，不然很可能一开始站在干草块上，会 WA。

然后就没有任何疑点可言了。没有学习过 DFS 的同学可以从其他题解中汲取技巧和感悟。那么到这里整个问题就解决了。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,s1,s2,cnt;
char c[2005][2005];
bool vis[2005][2005];
int dx[]={0,0,0,1,-1},dy[]={0,1,-1,0,0};//个人习惯，喜欢从第一位开始存 
void dfs(int x,int y)
{
	vis[x][y]=1;//标记一下，防止递归陷入死循环 
	if(c[x][y]=='S')cnt+=1;
	if(c[x][y]=='M')cnt+=5;
	if(c[x][y]=='L')cnt+=10;
	for(int i=1;i<=4;i++)
	{
		int tx=x+dx[i],ty=y+dy[i];
		if(c[tx][ty]!='*'&&!vis[tx][ty]&&tx>=0&&tx<a&&ty>=0&&ty<b)
		dfs(tx,ty);
	}//因为不用搜多遍，所以不要回溯，否则造成不必要的麻烦 
}
int main()
{
	cin>>a>>b;
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++)
		cin>>c[i][j];
	}//注意从零开始 
	cin>>s1>>s2;
	dfs(s1,s2);
	cout<<cnt;
	return 0;
}
```

---

## 作者：A_grasser (赞：0)

## 题意简化

给定一个矩阵，求所处坐标联通块中加和值。

## 需要注意的地方

1. 注意矩阵长宽大小用普通二维数组开不了。

## 解法分析

看着矩阵长宽我就想了一天，最后看了另一篇大佬的题解才想起有个 STL 叫 `vector`。

之后的内容很简单，就只要 bfs 一遍，把里面的值都加起来就行，具体看代码。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
struct point{int x,y;};//点对坐标 
int r,c,a,b,ans;
vector<char>g[10007];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
vector<bool>used[10007];//标记使用 
queue<point>q;
int main(){
	cin>>r>>c;
	char x;
	for(int i=0;i<r;i++){//存地图 
  		for(int j=0;j<c;j++){
			cin>>x;
  			g[i].push_back(x);
			used[i].push_back(0);
		}
	}
	cin>>a>>b;
	q.push((point){a,b});
	used[a][b]=1;
	while(q.empty()==0){//宽搜模版 
  		point u=q.front();
		q.pop();
  		if(g[u.x][u.y]=='S') ans++;
  		if(g[u.x][u.y]=='M') ans+=5;
  		if(g[u.x][u.y]=='L') ans+=10;
  		for(int i=0;i<4;i++){
  			int x=u.x+dx[i],y=u.y+dy[i];
  			if((0<=x && x<r) && (0<=y && y<c) && g[x][y]!='*' && used[x][y]==0){//判断条件 
  				q.push((point){x,y});
				used[x][y]=1;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Z3k7223 (赞：0)

## Problem

给定一个 $n \times m$ 的矩阵，其中 `*` 为障碍物，其余每个位置对应的字符有不同的权值。给定一个起点，求从起点能到达的所有位置的权值之和。

## Solution

一道很简单的搜索模板题，根据题意搜索即可。

值得注意的是题目规定 $n,m \le 10^5$ 且 $n \times m \le 10^5$，直接开一个二维的 $10^5$ 数组肯定不可行，因此我们可以使用 STL 里面的一个神器———— `vector` 来帮助我们动态扩展数组。

余下的就不多说了，直接上代码，注意一些细节。

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int>vis[N];
vector<char>a[N];

int walk[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
int n, m;
typedef pair<int, int> pii;

int val(char ch) {
	if (ch == 'S')
		return 1;
	if (ch == 'M')
		return 5;
	if (ch == 'L')
		return 10;
	return 114514;//无论如何也不可能到这里，索性瞎填一个值
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
        a[i].push_back('*');
		vis[i].push_back(0);//个人习惯下标从1开始，先单独把每行的下标0占了
		for (int j = 1; j <= m; j++) {
			char tmp;
			cin >> tmp;
			a[i].push_back(tmp);
			vis[i].push_back(0);
		}
		a[i].push_back('*');
		vis[i].push_back(0);
	}
	pii st;
	cin >> st.first >> st.second;//题目给的下标从0开始，转换一下
	st.first++, st.second++;
	int ans = 0;
	queue<pii>q;
	q.push(st);
	vis[st.first][st.second] = 1;
	while (!q.empty()) {//快乐的广搜模板
		pii tmp = q.front();
		q.pop();
		ans += val(a[tmp.first][tmp.second]);
		for (int i = 0; i < 4; i++) {
			int nxtx = tmp.first + walk[i][0], nxty = tmp.second + walk[i][1];
			if ((nxtx >= 1 && nxtx <= n && nxty >= 1 && nxty <= m) && (a[nxtx][nxty] != '*' && vis[nxtx][nxty] == 0)) {
				vis[nxtx][nxty] = 1;
				pii nxt;
				nxt.first = nxtx;
				nxt.second = nxty;
				q.push(nxt);
			}
		}
	}
	cout << ans << endl;
	return 0;//完结撒花
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10294)
## 解题思路
宽度优先搜索模板题。

先输入 $n,m$，南瓜地 $a$，农民位置 $x,y$，把当前位置的南瓜先摘掉，再宽搜，四个位置都去搜一遍，堵住了或者查找过了就不要搜，否则摘掉当前南瓜，加上它的价值，并记录已经查找过了，防止重复搜，节省时间。

这不用我多说的吧？
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string a[100010];
queue<pair<int,int> >q;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i];
	int x,y,sum;
	cin>>x>>y;
	switch(a[x][y])
	{
		case 'S':sum=1;break;
		case 'M':sum=5;break;
		case 'L':sum=10;break;
	}
	a[x][y]='*';
	q.push(make_pair(x,y));
	while(!q.empty())
	{
		for(int i=0;i<4;i++)
		{
			int xx=q.front().first+dx[i];
			int yy=q.front().second+dy[i];
			if(xx<n&&yy<m&&xx>=0&&yy>=0&&a[xx][yy]!='*')
			{
				switch(a[xx][yy])
				{
					case 'S':sum++;break;
					case 'M':sum+=5;break;
					case 'L':sum+=10;break;
				}
				a[xx][yy]='*';
				q.push(make_pair(xx,yy));
			}
		}
		q.pop();
	}
	cout<<sum;
	return 0;
}

```

---

