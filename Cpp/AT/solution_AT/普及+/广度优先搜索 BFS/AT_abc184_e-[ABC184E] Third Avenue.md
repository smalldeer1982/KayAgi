# [ABC184E] Third Avenue

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc184/tasks/abc184_e

縦 $ H $ マス、横 $ W $ マスの $ 2 $ 次元グリッドで表された街があります。  
 上から $ i $ 行目、左から $ j $ 列目のマスの情報が文字 $ a_{i,j} $ により与えられます。 $ a_{i,j} $ は `S` , `G` , `.` , `#` , `a` ~ `z` のいずれかです。  
`#` は入ることができないマスを、`a` ~ `z` はテレポーターのあるマスを表します。

高橋くんははじめ `S` のマスにおり、 $ 1 $ 秒ごとに以下のいずれかの移動を行います。

- 現在いるマスと上下左右に隣り合う、`#` でないマスに移動する。
- 今いるマスと同じ文字が書かれているマスを $ 1 $ つ選び、そこにテレポートする。この移動は現在いるマスが `a` ~ `z` のいずれかであるとき使える。

高橋くんが `S` のマスから `G` のマスに移動するのに必要な最短の時間を求めてください。  
 ただし、どうしても `G` のマスにたどり着けない場合は、代わりに `-1` を出力してください。

## 说明/提示

### 制約

- $ 1\ \le\ H,\ W\ \le\ 2000 $
- $ a_{i,j} $ は `S` , `G` , `.` , `#` , 英小文字のいずれか
- `S` のマスと `G` のマスはちょうど $ 1 $ つ存在する

### Sample Explanation 1

上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ で表すこととします。 はじめ、高橋くんは $ (1,\ 1) $ にいます。 例えば、以下のような手順で $ 4 $ 秒で $ (2,\ 5) $ に移動することができます。 - $ (1,\ 1) $ から $ (2,\ 1) $ に移動する - $ (2,\ 1) $ と同じ `a` のマスである $ (2,\ 3) $ にテレポートする - $ (2,\ 3) $ から $ (2,\ 4) $ に移動する - $ (2,\ 4) $ から $ (2,\ 5) $ に移動する

## 样例 #1

### 输入

```
2 5
S.b.b
a.a.G```

### 输出

```
4```

## 样例 #2

### 输入

```
11 11
S##...#c...
...#d.#.#..
..........#
.#....#...#
#.....bc...
#.##......#
.......c..#
..#........
a..........
d..#...a...
.#........G```

### 输出

```
14```

## 样例 #3

### 输入

```
11 11
.#.#.e#a...
.b..##..#..
#....#.#..#
.#dd..#..#.
....#...#e.
c#.#a....#.
.....#..#.e
.#....#b.#.
.#...#..#..
......#c#G.
#..S...#...```

### 输出

```
-1```

# 题解

## 作者：KobeBeanBryantCox (赞：6)

# AT_abc184_e [ABC184E] Third Avenue 题解

------------

[题目传送门](https://www.luogu.com.cn/problem/AT_abc184_e)

~~此题大水题，评级过高~~

------------

## 题意

给出 $h\times w$ 的迷宫，其中有若干个相对应传送门，要求输出从起点到终点的最短路径，如不能到达则输出 `-1`。

------------

## 分析

先看数据范围：$1\leq h,w\leq 2000$，我们大概需要一个 $O(hw)$ 的算法。

一看这个题就是个迷宫问题，只不过加了一个传送门。

想不到好的方法那就尝试搜索吧。根据以往的经验，迷宫问题 DFS 应该会比 BFS 慢一些，所以我们直接尝试写 BFS。

开始思考如何 BFS。首先是**上下左右四个方向全部入队**，这是迷宫问题的基本策略。

然后我们考虑，如果当前点是传送门，那我们可以选择上下左右，也可以传送。这样的话，我们只需要**把所有传送门的位置记下来，找到对应的传送门，将它们全部入队**就行了。

------------

定义结构体 $node$ 和坐标偏移量数组 $d$，方便以后使用。

```cpp
struct node
{
	int x,y,step;
};
int d[5]={1,0,-1,0,1}; // 这里的 d 数组这样定义是个小技巧，读者自行理解
```
定义 `char a[2010][2010];` 用来存输入数据。

定义 `vector<node>csm[300];` 用来记录传送门位置，注意相同字母的传送门可能不止 $2$ 个！所以必须用数组存起来，这里采用动态数组 vector 节省代码量。

（这里其实定义 $150$ 就够了，是因为按照传送门名字存位置，名字为一个字符，字符个数不会超过 $128$ 个。）

定义 `bool vis[2010][2010];` 表示 BFS 过程中这个点有没有被访问过。

因个人习惯，将 $h,w$ 定义为 $n,m$，不喜勿喷。

其余详见代码。

- ### 主函数：

```cpp
int main()
{
	scanf("%d%d",&n,&m),getchar(); // 读掉行尾换行 
	for(int i=1;i<=n;getchar(),i++) // 读掉行尾换行 
		for(int j=1;j<=m;j++)
		{
			a[i][j]=getchar();
			if(a[i][j]=='S')x=i,y=j; // 起点，记下坐标 
			else if(a[i][j]!='G'&&a[i][j]!='.'&&a[i][j]!='#')csm[a[i][j]].push_back({i,j,0}); // 传送门 
		}
	printf("%d",bfs()); // 执行 BFS 
	return 0;
}
```

- ### bfs 函数：

```cpp
int bfs()
{
	queue<node>q;
	vis[x][y]=true,q.push({x,y,0}); // 起点入队 
	while(!q.empty())
	{
		node t=q.front();
		q.pop();
		char c=a[t.x][t.y]; 
		if(c=='G')return t.step; // 走到终点，返回步数 
		for(int i=0;i<4;i++) // 四个方向 
		{
			int xx=t.x+d[i],yy=t.y+d[i+1]; // 这里对应上面的小技巧，自行理解 
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&!vis[xx][yy]&&a[xx][yy]!='#')vis[xx][yy]=true,q.push({xx,yy,t.step+1});
			// 如果没越界，没被访问过，并且不是墙，那么入队 
		}
		if(c!='.'&&c!='#'&&c!='S'&&c!='G') // 如果是传送门 
			for(int i=0;i<csm[c].size();i++) // 对应的传送门全部入队 
			{
				int xx=csm[c][i].x,yy=csm[c][i].y;
				if(!vis[xx][yy])vis[xx][yy]=true,q.push({xx,yy,t.step+1}); // 未被访问过才入队 
			}
	}
	return -1; // 队列空了还未到终点，输出 -1 
}
```

~~可以愉快地交代码啦！~~

------------

**慢！！！**

分析一下时间复杂度，最坏情况下全是传送门，那么这个代码的时间复杂度是 $O(h^{2}w^{2})$，远超预期，思考如何优化。

假设我们已经走过一次名字为 `a` 的传送门，第二次进入名字为 `a` 的传送门时候，可以传送到的位置与第一次相同，而且步数多了好多，那我们还不如第一次就传送。

所以，我们不难得出一个结论：**同一个名字的传送门只走一次**。这样一来，每个点最多走一次，时间复杂度为 $O(hw)$，就能通过本题啦！

于是我们定义 `map<char,bool>f;`，$f[\ 'a'\ ]$ 表示名字为 `a` 的传送门是否走过。

对于修改原来的 BFS 代码，只需要修改传送门那一部分。

- ### 修改的 bfs 函数的部分：

```cpp
if(c!='.'&&c!='#'&&c!='S'&&c!='G'&&!f[c]) // 如果是传送门，并且这个名字的传送门没走过 
{
	f[c]=true; // 现在走过了 
	for(int i=0;i<csm[c].size();i++) // 对应的传送门全部入队 
	{
		int xx=csm[c][i].x,yy=csm[c][i].y;
		if(!vis[xx][yy])vis[xx][yy]=true,q.push({xx,yy,t.step+1}); // 未被访问过才入队 
	}
}
```

## AC代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
struct node
{
	int x,y,step;
};
vector<node>csm[300];
char a[2010][2010];
int n,m,x,y,d[5]={1,0,-1,0,1}; // 这里的 d 数组这样定义是个小技巧，读者自行理解
bool vis[2010][2010];
map<char,bool>f;
int bfs()
{
	queue<node>q;
	vis[x][y]=true,q.push({x,y,0}); // 起点入队 
	while(!q.empty())
	{
		node t=q.front();
		q.pop();
		char c=a[t.x][t.y]; 
		if(c=='G')return t.step; // 走到终点，返回步数 
		for(int i=0;i<4;i++) // 四个方向 
		{
			int xx=t.x+d[i],yy=t.y+d[i+1]; // 这里对应上面的小技巧，自行理解 
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&!vis[xx][yy]&&a[xx][yy]!='#')vis[xx][yy]=true,q.push({xx,yy,t.step+1});
			// 如果没越界，没被访问过，并且不是墙，那么入队 
		}
		if(c!='.'&&c!='#'&&c!='S'&&c!='G'&&!f[c]) // 如果是传送门，并且这个名字的传送门没走过 
		{
			f[c]=true; // 现在走过了 
			for(int i=0;i<csm[c].size();i++) // 对应的传送门全部入队 
			{
				int xx=csm[c][i].x,yy=csm[c][i].y;
				if(!vis[xx][yy])vis[xx][yy]=true,q.push({xx,yy,t.step+1}); // 未被访问过才入队 
			}
		}
	}
	return -1; // 队列空了还未到终点，输出 -1 
}
int main()
{
	scanf("%d%d",&n,&m),getchar(); // 读掉行尾换行 
	for(int i=1;i<=n;getchar(),i++) // 读掉行尾换行 
		for(int j=1;j<=m;j++)
		{
			a[i][j]=getchar();
			if(a[i][j]=='S')x=i,y=j; // 起点，记下坐标 
			else if(a[i][j]!='G'&&a[i][j]!='.'&&a[i][j]!='#')csm[a[i][j]].push_back({i,j,0}); // 传送门 
		}
	printf("%d",bfs()); // 执行 BFS 
	return 0;
}
```

至此，本题迎刃而解。

------------

后记 1：版权所有@[KobeBeanBryantCox](https://www.luogu.com.cn/user/865625)，请勿抄袭代码。

后记 2：写代码的习惯一定要好，代码不要乱七八糟，优秀的码风是很醉人的~

~~还有，能不能不要脸地要个赞呀QwQ~~

---

## 作者：fish_love_cat (赞：2)

~~BFS 大淼题， AT 日常难度偏高。~~

**思路：**

迷宫问题的传送门版本，与正常的迷宫问题不同的地方在于，多出了若干个传送门，这也就意味着走法不再单单是上下左右那么简单，如果走到了传送门上，就要把与之对应的传送门全部入队，然后记录传送门的名字，永不再用，以此节约时间。

为了记录传送门，不能像传统 BFS 那样只开一个 ```bool``` 数组记录能不能走就算完事，还要把读入的地图用 ```char``` 数组保存下来，如果遇到传送门，还需要遍历一遍地图，找到所有对应传送门。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sx,sy,ex,ey;
char c[2005][2005];
bool f[2005][2005];
struct wz{
    int x,y,ans;
};
int gx[4]={0,0,1,-1};
int gy[4]={1,-1,0,0};
map<char,bool> mapp;
int bfs(){
    queue<wz> q;
    wz a;
    a.x=sx;
    a.y=sy;
    a.ans=0;
    q.push(a);
    while(!q.empty()){
        a=q.front();
        q.pop();
        if(a.x==ex&&a.y==ey) return a.ans;
        for(int i=0;i<4;i++){
            wz xin;
            xin.x=gx[i]+a.x;
            xin.y=gy[i]+a.y;
            xin.ans=a.ans+1;
            if(f[xin.x][xin.y]) q.push(xin),f[xin.x][xin.y]=false;
        }
        if(c[a.x][a.y]!='.'){
            char cs=c[a.x][a.y];
            if(mapp[cs]) continue;
            mapp[cs]=true;
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(c[i][j]==cs){
                        wz xin;
                        xin.x=i;
                        xin.y=j;
                        xin.ans=a.ans+1;
                        q.push(xin);
                        f[i][j]=false;
                    }
                }
            }
        }
    }
    return -1;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c[i][j];
            if(c[i][j]!='#') f[i][j]=true;
            if(c[i][j]=='S') sx=i,sy=j;
            if(c[i][j]=='G') ex=i,ey=j;
        }
    }
    cout<<bfs();
	return 0;
}
```

---

## 作者：HadrianZhang (赞：1)

# 思路

本题是迷宫问题的变种，增加了一个传送门的条件。

思路也很简单：
- 不是传送门：正常往四个方向试着走。
- 是传送门：遍历所有与之相同的字母的位置，逐一判断能不能走。字母的位置可以预先存在 vector 里。

但是，这种朴素的想法的最坏时间复杂度为 $O(h^2w^2)$，即地图上全为传送门的情况。

优化：每个字母的传送门最多遍历一遍，之后再遇到这个字母时，它的相关传送门就都被访问过了，可以记录每个字母是否被访问过的情况。时间复杂度降为 $O(hw)$，可以通过本题。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,bx,by,dir[][2]={{0,1},{0,-1},{1,0},{-1,0}};
bool vis[2005][2005],vis2[205];
string a[2005];
struct node
{
	int x,y,step;
};
vector<node>v[205];
int bfs()
{
	queue<node>q;
	q.push({bx,by,0});
	vis[bx][by]=1;
	while(q.size())
	{
		node f=q.front();
		q.pop();
		char now=a[f.x][f.y];
		if(now=='G') return f.step;
		for(int i=0;i<4;i++)
		{
			int tx=f.x+dir[i][0],ty=f.y+dir[i][1];
			if(tx>=0&&tx<n&&ty>=0&&ty<m&&!vis[tx][ty]&&a[tx][ty]!='#')
			{
				vis[tx][ty]=1;
				q.push({tx,ty,f.step+1});
			}
		}
		if(islower(now)&&!vis2[now])
		{
			vis2[now]=1;
			for(int i=0;i<v[now].size();i++)
			{
				int x=v[now][i].x,y=v[now][i].y;
				if(!vis[x][y])
				{
					vis[x][y]=1;
					q.push({x,y,f.step+1});
				}
			}
		}
	}
	return -1;
}
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		for(int j=0;j<m;j++)
		{
			if(a[i][j]=='S') bx=i,by=j;
			if(islower(a[i][j])) v[a[i][j]].push_back({i,j,0});
		}
	}
	cout<<bfs();
	return 0;
}
```

---

## 作者：syzxzqy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc184_e)  
搜索的模板题。  
用 bfs 实现，主要思想就是用队列记录需要遍历的每一个坐标，依次遍历，从队头取出坐标，如果它的上下左右能够通行并且步数比原先记录的要少，就更新步数，加入队列中（传送门同理），做完后弹出这个队列。  
先对整个图预处理，找出起点、终点、各个传送门，起点、终点用变量保存，传送门可能有多个，方便起见用 vector 保存。
```cpp
cin>>n>>m;
for(int i=1;i<=n;++i)
	cin>>a[i]+1;
for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
		if(a[i][j]=='S') x=(no){i,j};//记录起点 
		else{
			if(a[i][j]=='G') y=(no){i,j};//记录终点 
			else if('a'<=a[i][j]&&a[i][j]<='z') v[a[i][j]].push_back((no){i,j});//传送门可能有多个，例如样例2 
			f[i][j]=2e9;//将步数都赋值为最大 
		}
```
然后开始宽搜，从队头取出坐标，枚举上下左右和传送到达的地方，在队尾保存，修改步数。
```cpp
f[x.x][x.y]=0;
q.push(x);//记录开头 
while(!q.empty()){
	u=q.front();q.pop();//取出队头坐标 
	if(u.x==y.x&&u.y==y.y){//如果是终点，输出步数 
		cout<<f[u.x][u.y];return 0;
	}
	bu=f[u.x][u.y]+1;
	for(int i=0;i<4;++i){
		v2=(no){u.x+e[i][0],u.y+e[i][1]};//走一步的坐标 
		if(v2.x<1||v2.y<1||v2.x>n||v2.y>m) continue;//越界 
		if(a[v2.x][v2.y]=='#') continue;//无法走 
		if(f[v2.x][v2.y]<=bu) continue;//步数没小于之前记录的 
		q.push(v2);f[v2.x][v2.y]=bu;//加入队列，更新 
	}
	ch=a[u.x][u.y];//当前坐标的符号 
	if('a'<=ch&&ch<='z'){//判断是否为传送门 
		for(int i=0;i<v[ch].size();++i){
			v2=v[ch][i];//走一步的坐标 
			if(v2.x==u.x&&v2.y==u.y) continue;//还是原点 
			if(f[v2.x][v2.y]<=bu) continue;
			q.push(v2);f[v2.x][v2.y]=bu;
		}
	}
}
cout<<-1;//走不通 
```
时间复杂度看似是：$O(nm)$，实际上如果除了起点和终点都是传送门，最差情况下时间复杂度为：$O(n^2m^2)$，这时候就需要加优化。  
可以发现每种传送门只需要用一次，再用就没有最优了，因此可以做完就删除。
### 完整代码  
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std; 
const int N=1e6+10,M=2e3+10,e[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int n,m,bu,f[M][M];
char a[M][M],ch;
struct no{
	int x,y;
}x,y,u,v2;
vector<no> v[M];
queue<no> q;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i]+1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i][j]=='S') x=(no){i,j};//记录起点 
			else{
				if(a[i][j]=='G') y=(no){i,j};//记录终点 
				else if('a'<=a[i][j]&&a[i][j]<='z') v[a[i][j]].push_back((no){i,j});//传送门可能有多个，例如样例2 
				f[i][j]=2e9;//将步数都赋值为最大 
			}
	f[x.x][x.y]=0;
	q.push(x);//记录开头 
	while(!q.empty()){
		u=q.front();q.pop();//取出队头坐标 
		if(u.x==y.x&&u.y==y.y){//如果是终点，输出步数 
			cout<<f[u.x][u.y];return 0;
		}
		bu=f[u.x][u.y]+1;
		for(int i=0;i<4;++i){
			v2=(no){u.x+e[i][0],u.y+e[i][1]};//走一步的坐标 
			if(v2.x<1||v2.y<1||v2.x>n||v2.y>m) continue;//越界 
			if(a[v2.x][v2.y]=='#') continue;//无法走 
			if(f[v2.x][v2.y]<=bu) continue;//步数没小于之前记录的 
			q.push(v2);f[v2.x][v2.y]=bu;//加入队列，更新 
		}
		ch=a[u.x][u.y];//当前坐标的符号 
		if('a'<=ch&&ch<='z'){//判断是否为传送门 
			for(int i=0;i<v[ch].size();++i){
				v2=v[ch][i];//走一步的坐标 
				if(v2.x==u.x&&v2.y==u.y) continue;//还是原点 
				if(f[v2.x][v2.y]<=bu) continue;
				q.push(v2);f[v2.x][v2.y]=bu;
			}
			v[ch].clear();//删除传送门 
		}
	}
	cout<<-1;//走不通 
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [ABC184E] Third Avenue

## 题面翻译

给出一张地图，起点 `S` 终点 `G`，`#` 表示墙体。

地图上有若干个传送门，用小写字母表示。

每一秒，您可以移动到相邻位置，或是通过您当前所处的传送门移动到对应的任一传送门。

问您需要的最短时间，若是无法到达输出 `-1`。

## 思路

省流：带传送门的走迷宫大水题

既然只是走迷宫，那我们就从 bfs 最基础的部分开始写。

**基础 bfs 代码**

```C++

void bfs() {
	d[fromx][fromy] = 0;//把起点push进队列
	q.push((node){fromx, fromy});
  
	while (q.size()) {
		node u = q.front();
		q.pop();
		
		if(c[u.x][u.y]=='G'){//走到终点
			cout << d[u.x][u.y] << endl;//输出距离
			return ;
		}
      
        //...
		
		for (int k = 0; k < 4; k++) {
			int xx = u.x + dx[k], yy = u.y + dy[k];//增量数组计算出邻接坐标
          
			if (xx < 1 || xx > n || yy < 1 || yy > m )continue;//判掉不合法的
			if(c[xx][yy]=='#')continue;//判掉不能走的
			if (d[u.x][u.y] + 1<d[xx][yy]){//如果原来的答案更好就不要push进队列了
				q.push((node){xx,yy});
				d[xx][yy] = min(d[xx][yy],d[u.x][u.y] + 1);
			}
		}
	}
	
	cout<<-1<<endl;//走完都没有达到终点,输出-1,即无法达到

}

```


本题还有传送门部分，代码如下。注意，本题传送门相关的费用是：走到传送门算一步，传送算一步。还要注意一点就是，我们走到传送门，可以选择不传送的。

**传送门**

```C++
    //...
    if(c[u.x][u.y]>='a'&&c[u.x][u.y]<='z'){
			int id=c[u.x][u.y]-'a';
			for(int i=0;i<e[id].size();i++){
				node v=e[id][i];
				if(v.x==u.x&&v.y==u.y)continue;//如果是自己则continue
				if (d[u.x][u.y] + 1<d[v.x][v.y]){
					q.push((node){v.x,v.y});
					d[v.x][v.y] = min(d[u.x][u.y] + 1,d[v.x][v.y]);
				}
			}
		}
```


还有非常重要的一点——相同字母的传送门可能不止 $2$ 个！所以要用 vector 存储。



**输入**

我们要一边输入一边记录传送门位置，还可以顺便记录起点的位置。

```C++
for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> c[i][j];
			if (c[i][j] == 'S')fromx = i, fromy = j;
			if(c[i][j]>='a'&&c[i][j]<='z'){//传送门
				e[c[i][j]-'a'].push_back((node){i,j});
			}
		}
```



其他就没有什么了，不多说了，直接上代码。

——

稍等！

本题如果仅仅是普通的走迷宫 + 传送门，那就会 TLE，因为如果地图上都是传送门的话，那么时间复杂度会达到惊人的 $O(h^2w^2)$。我们考虑到当我们第一次访问到传送门 $c$ 时，那么从 $c$ 传送到另外一个 $c$，路径长度一定会更优。但是如果后面再访问到传送门 $c$ 时（这里指的是字母相同的不同传送门），那么传送后的路径不一定更短。

所以我们总结出：每种传送门最多只使用一次。

所以我们标记每一种传送门的使用次数，如果 $≥1$ 则不进行传送。

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;

struct node{
	int x,y;
};
queue <node>q;

vector <node>e[27];
char c[N][N];
int n, m, ans, d[N][N], vis[N][N],cnt[27];
int fromx, fromy, ansx, ansy;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};


void bfs() {
	d[fromx][fromy] = 0;
	vis[fromx][fromy] = 1;
	q.push((node){fromx, fromy});
	while (q.size()) {
		node u = q.front();
		q.pop();
		
		if(c[u.x][u.y]=='G'){
			cout << d[u.x][u.y] << endl;
			return ;
		}
		
		
		if(c[u.x][u.y]>='a'&&c[u.x][u.y]<='z'){
			int id=c[u.x][u.y]-'a';
			if(cnt[id]==0){
				cnt[id]++;
				for(int i=0;i<e[id].size();i++){
					node v=e[id][i];
					if(v.x==u.x&&v.y==u.y)continue;
					if (d[u.x][u.y] + 1<d[v.x][v.y]){
						q.push((node){v.x,v.y});
						d[v.x][v.y] = min(d[u.x][u.y] + 1,d[v.x][v.y]);
					}
				}
			}
			
		}

		for (int k = 0; k < 4; k++) {
			int xx = u.x + dx[k], yy = u.y + dy[k];
          
			if (xx < 1 || xx > n || yy < 1 || yy > m )continue;
			if(c[xx][yy]=='#')continue;
			if (d[u.x][u.y] + 1<d[xx][yy]){
				q.push((node){xx,yy});
				d[xx][yy] = min(d[xx][yy],d[u.x][u.y] + 1);
			}
		}
	}
	
	cout<<-1<<endl;

}

int main() {
	cin >> n >> m;
	memset(d,0x3f,sizeof d);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> c[i][j];
			if (c[i][j] == 'S')fromx = i, fromy = j;
			if(c[i][j]>='a'&&c[i][j]<='z'){
				e[c[i][j]-'a'].push_back((node){i,j});
			}
		}
	bfs();	
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= m; j++) {
//			cout<<d[i][j]<<' ';
//			}
//			cout<<endl;
//		}
	
	return 0;
}
```






---

