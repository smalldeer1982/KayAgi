# [USACO13FEB] Perimeter S

## 题目描述

农夫约翰已经在他的一片田地中间放置了n（1<=n<=50000）个干草堆。我们可以认为这片田地是由1000000*1000000 个小方格组成的矩阵，每个干草堆占据一个小方格（当然，没有两堆干草占据同一个格子）

FJ 注意到他的干草堆组成了一个大的连通块，这就意味着从任何一个草堆走起，可以通过相邻草堆走若干步到达其他任意的草堆。这个连通块的内部可能包含若干个“洞”——被干草堆完全包围的空白格子。

请帮助FJ计算整个连通块的周长。计算周长时请不要考虑“洞”。

## 样例 #1

### 输入

```
8 
10005 200003 
10005 200004 
10008 200004 
10005 200005 
10006 200003 
10007 200003 
10007 200004 
10006 200005 
```

### 输出

```
14 
```

# 题解

## 作者：Limit (赞：8)

USACO的题目,感觉还是挺神奇的.
- ## 前置芝士
1.[DFS](https://baike.baidu.com/item/%E6%B7%B1%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2/5224976)([BFS](https://baike.baidu.com/item/%E5%AE%BD%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2?fromtitle=BFS&fromid=542084))遍历:用来搜索(因为DFS好写,本文以DFS为准~~还不是因为作者懒~~)
2.[STL](https://baike.baidu.com/item/STL/70103?fr=aladdin)中的set(map)的基本用法:数据很大,不能直接存.
- ## 具体做法
因为不能把草堆围起来造成的周长记录起来所以不能再草堆中搜索,需要再这个草堆外面绕着搜索这样就不会将内部的周长记录下来了.

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200108145506126.jpg)

如这样一张图它的周长是(红色部分):

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200108150155960.jpg)

于是需要找到一个在最外边的点,可以发现最上方的那个点的就十分合适,搜索的位置(蓝色部分)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200108151552321.jpg)

从最上方开始搜,如果搜到了草就answer++,return.
但是这样搜的时候如果一直往外跑就会直接炸掉,所以必须不能有这种情况,可以发现对于每一个蓝色位置的八个方向的一格处至少有一个草堆,于是如果没有草堆就直接退出.
- ## 代码
```cpp
#include<bits/stdc++.h>
#define rap(i,first,last) for(int i=first;i<=last;++i)
using namespace std;
const int move_x[9]={233,0,0,1,-1,1,1,-1,-1};
const int move_y[9]={233,1,-1,0,0,1,-1,1,-1};
set<pair<int,int> >_map;//用来记录这张图
set<pair<int,int> >visit;//用来判断这个位置有没有走过
int N,fx=-1,fy,answer=0;
bool OutSide(int x,int y)//判断八个方向上有没有草堆
{
	rap(i,1,8)
	if(_map.count(make_pair(x+move_x[i],y+move_y[i])))return 0;//有就返回0
	return 1;//没有返回1
}
void DFS(int x,int y)//DFS
{
	if(_map.count(make_pair(x,y)))//如果这个位置是草堆就answer++,return
	{
		answer++;
		return;
	}
	if(visit.count(make_pair(x,y)))return;//走过了就不能在走了
	visit.insert(make_pair(x,y));//记录这个位置走过
	if(OutSide(x,y))return;//如果八个方向上没有草堆则return
	rap(i,1,4)//向四个方向搜索
	DFS(x+move_x[i],y+move_y[i]);
}
int main()
{
	scanf("%d",&N);
	int x,y;
	rap(i,1,N)
	{
		scanf("%d%d",&x,&y);
		_map.insert(make_pair(x,y));//地图中这个位置有草堆
		if(x>fx)
		{
			fx=x;
			fy=y;
		}
	}
	DFS(fx+1,fy);//最上方那个点上方的那个点开始搜索
	printf("%d",answer);//输出answer
	return 0;
}
```

---

## 作者：刘辰雨 (赞：4)

感觉是很标准的**正难则反**的思想，有一点点妙（考场上想了半个小时吧）

# Sulution of P3072(Pirth)

### 简述题意 / General describe:

题目给定一些点并组成连通块，特别地，连通块不一定“实心”。求连通块周长（不考虑空洞部分）

### 心路历程 / General ideas:

1. 对于一般的深搜和广搜而言，显然是很难判断空洞部分的，如果每遍历到一个空的点就搜索一遍来判断，在时间复杂度上肯定很劣。

2. 当时在考场上，有点迷茫，忽然想到了往格子里“倒水”的办法：如果用水淹没整个连通块，水接触到的部分肯定是可以纳入周长统计的（水显然不会灌到空腔里）。

3. 顺着这个思路，就可以想到用程序“模拟水”，而像水一样漫溢四处的，肯定是**广搜**无疑。

4. 想到这个地方，基本上就确定了**正难则反**的方针了。更明确一点说，既然连通块中有空洞，不好遍历；那么连通块周围的“空间”肯定是没有空洞的，可以很好地遍历咯。

## 初版代码 / Initial version code：

经过上面的思考，基本上就能写出初版代码了，也是我的考场代码。

毕竟要模拟水，肯定从右上角开始“往下倒”，所以初版代码是遍历了整个包含连通块的**矩形**：在时间复杂度上依然比较劣，很容易被卡，所以考场上只拿到了九十分。

[90分初版代码评测记录](https://www.luogu.com.cn/record/103487317)

### 初版代码：

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

int fx[4] = {0,1,0,-1};
int fy[4] = {1,0,-1,0};
int N;
map<pair<int,int>, int> vist;
map<pair<int,int>, int> grass;
int x,y;
int maxx,maxy;
int minx = 1e6, miny = 1e6;
long long Answer;

void BFS()//广搜——核心代码
{
	queue<pair<int,int> > Q;
	while(!Q.empty()) Q.pop();
	Q.push({maxx, maxy}); 
	while(!Q.empty()) {
		int X = Q.front().first;
		int Y = Q.front().second;
		Q.pop();
		
		if(X < minx || X > maxx || Y < miny || Y > maxy || vist[{X,Y}] != 0 || grass[{X,Y}] != 0)
			continue;
		vist[{X,Y}] = 1;
		for(int i = 0 ; i< 4 ; i++) {
			x = X+fx[i];
			y = Y+fy[i];
			if(grass[{x,y}] != 0) {
				Answer++;
			}
			if(x < minx || x > maxx || y < miny || y > maxy || vist[{x,y}] != 0 || grass[{x,y}] != 0) {
				continue;
			} else {
				Q.push({x,y});
			}
		}
	}
}

int main()
{
 	freopen("girth.in","r",stdin);
 	freopen("girth.out","w",stdout); 
	scanf("%d", &N);
	for(int i = 1 ; i<= N ; i++) {
		scanf("%d%d", &x, &y);
		grass[{x,y}] = 1;
		maxx = max(maxx,x);
		maxy = max(maxy,y);
		minx = min(minx,x);
		miny = min(miny,y);
     		//确定包含整个连通块的最小矩形的右上角(maxx,maxy)和左下角(minx,miny)
	}
	minx--;
	miny--;
	maxx++;
	maxy++;
    	//连通块可能充满整个矩形，这样就倒不进水了，于是把矩形扩大一下，防止这种情况。
	BFS();
	printf("%d\n", Answer);
 	fclose(stdin);
 	fclose(stdout);
	return 0;
}
```

## 优化代码 / Optimized code：

刚刚提到初版代码是不优的，这是为什么呢？参见下图：

![hack演示](https://cdn.luogu.com.cn/upload/image_hosting/ikzsq4o2.png)

加粗部分是我将遍历的矩形；绿色部分是连通块；黄色部分是对答案有贡献的块。

显而易见地，白色的部分都是冗余的遍历，因为他们对答案起不到任何效果，是“废水”，如果出类似的“条状”样例，初版代码就极容易被卡退化成暴力。所以我们对初版代码进行修改，不再遍历矩形，而是直接**贴着连通块的边**开始遍历。

[优化代码AC记录](https://www.luogu.com.cn/record/103487209)

### 优化代码：

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

int fx[4] = {0,1,0,-1};
int fy[4] = {1,0,-1,0};
int pdx[8] = {-1,0,1,1, 1, 0,-1,-1};
int pdy[8] = { 1,1,1,0,-1,-1,-1, 0};
int N;
int Startx, Starty;
map<pair<int,int>, int> vist;
map<pair<int,int>, int> grass;
int x,y;
int maxx,maxy;
int minx = 1e6, miny = 1e6;
long long Answer;

bool DisNice(int x, int y) {//判断该点是否“贴着”连通块
	for(int i = 0 ; i < 8 ; i++) {
		int gx = x+pdx[i];
		int gy = y+pdy[i];
		if(grass[{gx,gy}] != 0)
			return false;
	}
	return true;
}

void BFS()//广搜——核心代码
{
	queue<pair<int,int> > Q;
	while(!Q.empty()) Q.pop();
	Q.push({Startx+1, Starty}); 
	while(!Q.empty()) {
		int X = Q.front().first;
		int Y = Q.front().second;
		Q.pop();
		
		if( vist[{X,Y}] != 0 || grass[{X,Y}] != 0)
			continue;
		vist[{X,Y}] = 1;
		for(int i = 0 ; i< 4 ; i++) {
			x = X+fx[i];
			y = Y+fy[i];
			if(grass[{x,y}] != 0) {
				Answer++;
			}
			if( vist[{x,y}] != 0 || grass[{x,y}] != 0 || DisNice(x,y)) {
				continue;
			} else {
				Q.push({x,y});
			}
		}
	}
}

int main()
{
	freopen("girth.in","r",stdin);
	freopen("girth.out","w",stdout); 
	scanf("%d", &N);
	for(int i = 1 ; i<= N ; i++) {
		scanf("%d%d", &x, &y);
		grass[{x,y}] = 1;
		if(Startx < x) {
			Startx = x;
			Starty = y;
		}
	}
	BFS();
	printf("%d\n", Answer);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

以上代码吸氧即可AC。

感谢观看，希望有所帮助。


---

## 作者：_qingshu_ (赞：3)

# 题意分析：

给定一个 $10^{6} \cdot 10^{6}$ 的矩阵，你有 $n$ 个点是被覆盖的，所有被覆盖的点构成一个大的连通块，求整个连通块的周长（不计算内部）。

# 思路解析：

首先考虑把图缩成一个除了最外圈其余行列至少有一个被覆盖的点的最小图。

考虑把这个图从左上角开始染色，将左上角未被覆盖的点开始搜索，每搜索一个点记录这个点为 ```2```，被覆盖的点为 ```1``` ，连通块内部点和一开始没有被改变的 ```2``` 为```0```。

在每一次改变一个 ```0``` 成为 ```2``` 后尝试向四个方向扫一遍，如果为 ```1``` 就让 $ans$ 数组自增 1.如果为 ```0``` 就考虑向那个方向扩展。

然后你就可以得到一份~~快乐~~的 90 分代码。

![](https://cdn.luogu.com.cn/upload/image_hosting/rwpaep8l.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

# 考虑优化：

我们在搜整个图的时候会有大量无法对答案产生贡献的无用点导致 $mp[x][y]$ 更新了大量的 ```2```，没有产生应有的减小空间的效果，所以说考虑什么样的点是有用的。

我们可以试着沿着连通块的边进行寻找，也就是 $3 \cdot 3$ 范围内有 ```1``` 的块才考虑扩展。

如果还是从左上角开始找的话，不一定可以直接接触到连通块，所以我们要在第1行跑一边确认一个与联通块接触的点开始。

# 代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<long long,long long>mp[1000000];
long long n;
long long xma,xmi=INT_MAX,yma,ymi=INT_MAX;
long long ans=0;
long long chex[]={ 0,0,1,-1, 1, 1,-1, -1};
long long chey[]={-1,1,0, 0, 1,-1, 1, -1};
bool check(long long x,long long y){//如果是贴着连通块的 
	for(long long i=0;i<8;i++){
		long long nowx=x+chex[i],nowy=y+chey[i];
		if(nowx>=xmi-1&&nowx<=xma+1&&nowy>=ymi-1&&nowy<=yma+1){
			if(mp[nowx][nowy]==1){
				return true;
			}
		}
	}
	return false;
}
void dfs(long long x,long long y){
	mp[x][y]=2;//标记为2 
	//四个方向尝试记录答案与扩展 
	if(mp[x+1][y]==1)ans++;
	else if(mp[x+1][y]==0&&x<=xma&&check(x+1,y))dfs(x+1,y);
	
	if(mp[x-1][y]==1)ans++;
	else if(mp[x-1][y]==0&&x>=xmi&&check(x-1,y))dfs(x-1,y);
		
	if(mp[x][y+1]==1){ans++;
	else if(mp[x][y+1]==0&&y<=yma&&check(x,y+1))dfs(x,y+1);
		
	if(mp[x][y-1]==1){ans++;
	else if(mp[x][y-1]==0&&y>=ymi&&check(x,y-1))dfs(x,y-1);
}
int main(){
	cin>>n;
	long long x,y;
	for(long long i=1;i<=n;i++){
		scanf("%lld%lld",&x,&y);
		x++;y++;
		mp[x][y]=1;//标记为1 
		xma=max(xma,x);
		xmi=min(xmi,x);
		yma=max(yma,y);
		ymi=min(ymi,y);//缩略图 
	}
	for(long long i=ymi-1;i<=yma+1;i++){//寻找一个与连通块直接接触的点 
		if(mp[xmi][i]==1){
			y=i-1;
			break;
		}
	}
	dfs(xmi,y);//开始搜索 
	cout<<ans;
} 
```
23.12.3：修改了中文与数字时间缺少空格。

---

## 作者：dzysc (赞：3)

说下思路吧，这是一道DFS的题目，简单来说我们的目标是绕着边框搜索一圈，并且

记下周长。

至于如何做到这一点呢，我们为了防止我们dfs的时候走进谷堆里面的洞

可以考虑判断一个点是否孤立（is函数）也就是是否4面8方都是空地,经过这一简单

处理之后我们可以很轻松的完成dfs

顺便科普一下防止大家伙看不懂set

set里面包含了一个pair，存放点的坐标，然后我变量名字起的都挺规范的，就不解

释了，主要说下count，可以找到这个pair的值，并且返回，也就是说用set来高效判

断周围情况。

ps：USACO说这个解法已经fast enough，但是洛谷机器实在太（辣）强（鸡）,所以

如何ac你们懂的
```cpp
#include <cstdio>
#include <iostream>
#include <set>
using namespace std;

set<pair<int,int> >blocks,visited;
int pr;

bool is(int x,int y)
{
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)	 
			if(blocks.count(make_pair(x+i,y+j))==1)return false;
	return true;
}

void dfs(int x,int y)
{
	if(blocks.count(make_pair(x,y))!=0)
	{
		pr++;
		return;
	}
	if(visited.count(make_pair(x,y))!=0)return;
	visited.insert(make_pair(x,y));
	if(is(x,y)==true)return;
	dfs(x+1,y);
	dfs(x-1,y);
	dfs(x,y+1);
	dfs(x,y-1);
}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a,b;
		cin>>a>>b;
		blocks.insert(make_pair(a,b));
	}
	pair<int,int>st=*blocks.begin();
	int stx,sty;
	stx=st.first-1;
	sty=st.second-1;
	dfs(stx,sty);
	cout<<pr<<endl;
	return 0;
}
```

---

## 作者：Dream_poetry (赞：1)

### 思路：
很“氢气”的 DFS。

假设我们枚举稻草，那么显然我们会写的很艰难，并且难以考虑洞的情况。

所以我们考虑枚举整个图形的外圈。

对于一个位置，如果它靠着至少一个稻草，则它必然可以贡献入答案，

所以我们就找一个位置，枚举它的九宫格，如果没有找到稻草或这个位置已经被访问过，则跳出，否则继续走。

如果走到了一个稻草，则计入答案。

否则继续执行上述操作，直到跑完了 DFS。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;

map<pair<int,int>,int>vis;

int sx=-1;
int sy=-1;

int dx[10]={0,0,0,1,-1,1,1,-1,-1};
int dy[10]={0,1,-1,0,0,1,-1,-1,1};
int ans;



inline void dfs(int sx,int sy){
	if (vis[make_pair(sx,sy)]==2){
		ans++;
		return;
	}
	int flag=0;
	if (vis[make_pair(sx,sy)]) return;
	vis[make_pair(sx,sy)]=1;
	for (int i=1;i<=8;i++){
		int x=sx+dx[i];
		int y=sy+dy[i];
		if (vis[make_pair(x,y)]==2){
			flag=1;
			break;
		}
	}
	if (flag){
		for (int i=1;i<=4;i++){
			int x=sx+dx[i];
			int y=sy+dy[i];
			dfs(x,y);
		}
	}
}

signed main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		vis[make_pair(x,y)]=2;
		if (x>sx){
			sx=x;
			sy=y;
		}
	}
	dfs(sx+1,sy);
	cout<<ans;
	
	return 0;
}
```

---

## 作者：哈士奇憨憨 (赞：1)

## 题意
平面网格中有一个四连通的连通块，连通块中间可能有洞，求连通块的外围周长。
## 思路
由于坐标范围比较大，无法对网格进行遍历，所以只能采用别的方法来判断边界。

不妨考虑用模拟的方式沿着边界顺时针移动一圈，并统计出周长。

首先要确定起点，可以找到连通块中优先最靠左其次最靠下的格子，那么该格子的左边就可以作为起点。然后开始模拟移动，初始时面朝上。
对于当前位置，首先应该判断是否需要调整方向：先判断右边是否为空，如果为空则应当右转；再判断前方是否不为空，不为空则应该左转，并累加边界长度，注意如果走到凹槽可能连续两次左转。然后就可以向前移动一步，移动后如果右边不为空，则累加周长。回到起点时移动结束。
为了能够快速判断某个坐标是否为空，应当将连通块都加入到集合中维护，可以使用 STL 的 `set`。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;
const Pii kD[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // 上右下左
set<Pii> a;
Pii s = {1e9, 1e9}, p;
int n, d, ans;
Pii operator+(const Pii &x, const Pii &y) { return {x.first + y.first, x.second + y.second}; }  // 向量加法
void W() {
  p = s = s + kD[3];  // 左下角格子的左边作为初始位置
  do {
    if (!a.count(p + kD[(d + 1) % 4])) {  // 右方没有障碍
      d = (d + 1) % 4;                    // 右拐
    }
    for (; a.count(p + kD[d]); d = (d + 3) % 4) {  // 前方障碍则左拐
      ans++;                                       // 累加前方的边长
    }
    p = p + kD[d];                        // 向前移动一步
    ans += a.count(p + kD[(d + 1) % 4]);  // 右方如果有障碍则累加边长
  } while (p != s);                       // 回到起点时结束
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p.first >> p.second;
    a.insert(p);    // 将位置加入集合
    s = min(s, p);  // 计算最靠左的位置
  }
  W();
  cout << ans;
  return 0;
}
```

---

## 作者：Milthm (赞：0)

~~我的代码貌似相对来说很短。~~

首先你这个空白连通块是很难处理的，因为这个网格有 $10^6$ 的大小。

那不好处理怎么办？那就不处理了。我们干脆想一想外面的部分怎么算。

容易想到里面的空白连通块和外面是不通着的，所以我们可以像水流一样广搜，就可以求出外面的周长。

但是这种做法肯定能被卡到超时，原因是有大量的无意义搜索。

所以我们优化一下，直接沿着大连通块的边缘走，这样多余的部分就不会被搜索到了。

写代码的时候有一些小技巧，比如把两个方向数组合在一起，以及写函数判断等。可以减少一定的代码长度。

### AC code

```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
using namespace std;
int n,sx,sy,ans,w[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};
map<pi,bool>m,vis;
queue<pi>q;
bool qwq(int x,int y){
	for(int i=0;i<8;++i){
		int px=x+w[i][0],py=y+w[i][1];
		if(m.count({px,py}))return 1;
	}
	return 0;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		int x,y;cin>>x>>y;m[{x,y}]=1;
		if(x>sx)sx=x,sy=y;
	}
	q.push({sx+1,sy});
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;q.pop();
		if(vis.count({x,y}))continue;vis[{x,y}]=1;
		for(int i=0;i<4;++i){
			int px=x+w[i][0],py=y+w[i][1];
			if(m.count({px,py}))++ans;	
			else if(qwq(px,py)&&!vis.count({px,py}))q.push({px,py});
		}
	}
	cout<<ans;
	return 0;
}

```


---

