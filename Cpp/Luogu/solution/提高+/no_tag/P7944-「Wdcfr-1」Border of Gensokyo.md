# 「Wdcfr-1」Border of Gensokyo

## 题目描述

**这是一个交互式问题。**

Ran 正在帮助 Yukari 维护幻想乡的边界。

幻想乡的边界是一个 $n \times m$ 的矩阵，其中 $n$ 和 $m$ 都是偶数。不幸的是，由于 Moriya 神社的迁入，矩阵中现在有 4 个薄弱点。

为了简化维护工作，Ran 已经找到了从 $(1,1)$ 到 $(n,m)$ 的一条路径，只能向下或向右走。路径将四个薄弱点分隔开，使得每一侧恰好有两个薄弱点。她将在输入中告诉你这条路径。

现在你需要帮助 Ran 维护边界。你可以使用操作 `? x y` 来询问点 $(x,y)$ 是否是薄弱点。在查询之后，Ran 会将该点标记为蓝色。

如果在一次查询后，你刚刚找到了第 $k$ 个薄弱点，并且 $k$ 是偶数，你需要构造一条从第 $(k-1)$ 个薄弱点到第 $k$ 个薄弱点的简单路径。你构造的路径必须经过且仅经过所有标记为蓝色的点。Ran 然后将这些点在边界上加固并重新着色为红色。

Ran 不想做重复的工作，所以你只能用 `?` 查询白色的点。

现在 Ran 希望你能找到所有的“薄弱点”并完成所有的构造。

### 交互协议

首先从标准输入读取两个整数 $n$ 和 $m$。

然后从标准输入读取几个点（包括起点和终点），每行一个，表示从 $(1,1)$ 到 $(n,m)$ 的一条简单路径。

然后你可以进行**无限**次查询。将你的查询以 `? x y` 的格式打印到标准输出。然后你将从标准输入接收一个整数 $p$。如果 $p=1$，表示你询问的点确实是薄弱点；如果 $p=0$，表示它不是薄弱点。

记得刷新你的输出，你可以在 C++ 中使用 `fflush(stdout);`。请参考你的编程语言的文档。

在第 $k$ 次（$k$ 是偶数）接收到结果 $p=1$ 时，请按顺序输出几个点（包括两个薄弱点），每行一个，以 $-1,-1$ 结束，以表示从第 $(k-1)$ 个到第 $k$ 个薄弱点的简单路径。

在找到第四个薄弱点并完成构造后，你需要立即退出程序。

## 说明/提示

### 解释

示例中的矩阵如下：

```plain
..XX
X...
....
X...
```

其中 `X` 表示一个“薄弱点”。

### 约束

$4 \le n,m \le 100$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 4
1 1
1 2
2 2
3 2
3 3
3 4
4 4

0

1

0

0

1







1

1
```

### 输出

```








? 2 2

? 2 1

? 3 1

? 3 2

? 4 1

2 1
2 2
3 2
3 1
4 1
-1 -1
? 1 4

? 1 3

1 4
1 3
-1 -1
```

# 题解

## 作者：Tiffake (赞：2)

## 题意
简单来说，就是让你构造一种用一笔画铺满左右两个区域的方案，数据范围较小。

## 思路
乍看之下似乎有点难，因为很难保证询问的路径不会互相重复。可以考虑一种类似于“贪吃蛇”的套路——不断地走 `S` 型弯路，直到首尾相接，如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/ryp6ttbh.png)

对于横向拓展，每次向前两格一定没问题，因为这样正好可以向下之后再回来，竖向拓展同理。  
但是判断要不要继续沿当前方向拓展是一个难点。可以考虑判断如果继续拓展，会不会走到对面区域。如果会，那就向下拓展；否则，尽可能地向对面拓展。  
代码实现如下：
```cpp
inline bool chk(int x,int y){
	return !a[x][y-1]||a[x][y];//判断是否走到对面去了
}
//先构造地图，方便后续操作
x=1,y=1;while(a[x][y]&&a[x+1][y])x+=2;//开始点一定不能在路径上
for(sx=x,sy=y;x<=n;x++,y--){
	mp[x-1][y++]='d';
	if(x==sx&&chk(x,y))mp[x][y-1]='r',y++;
	while(y<m&&x&1&&chk(x,y)&&chk(x,y+1))
		mp[x][y-1]=mp[x][y]='r',y+=2;//能走就走，记得一次走两步
}
```
这样，我们就可以得到左边区域紧贴路径的走法了。  
然后，把左区域的剩下区域填满就行了。由于我们之前每次都拓展了两格，因此直接走 `S` 型弯路就行了，代码如下：
```cpp
for(x--,y--;y>=1;y--){
	mp[x--][y+1]='l';
	while(!mp[x][y])mp[x+1][y]='u',x--;//向上走
	x++,mp[x][y]='l',y--;
	while(x<=n&&!mp[x][y]){//向下走
		if(!mp[x-1][y])mp[x-1][y]='d';
		x++;
	}
	x--;
}
mp[tx=sx+1][ty=sy]='u';//记得特判最后一格
```
右边的地图构造方式也和左边差不多，不再过多赘述。

但是这样跑一遍只能找出一个点，还需要再反着跑一遍才能找到另一个点，因此考虑建反图：
```cpp
inline void go(int&x,int&y,char c){
	switch(c){
		case 'u':x--;break;
		case 'd':x++;break;
		case 'l':y--;break;
		case 'r':y++;break;
	}
}
inline char rgo(char x){//取反某个方向
	switch(x){
		case 'u':return 'd';
		case 'd':return 'u';
		case 'l':return 'r';
		case 'r':return 'l';
	}
	return 0;
}
inline void Getrevmap(){
	x=sx,y=sy;
	for(int lx=x,ly=y;lx!=tx||ly!=ty;lx=x,ly=y)
		go(x,y,mp[x][y]),rmp[x][y]=rgo(mp[lx][ly]);
	//先走一步，再把当前位置的方向改为走到的位置的反方向
	go(x,y,mp[x][y]),rmp[x][y]=rgo(mp[tx][ty]);//要特判最后一格
}
```
最后按照造好的地图模拟查询即可，给出 `main` 函数的代码：
```cpp
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n+m;i++)cin>>x>>y,a[x][y]=1;
	Getlmap(),v.push_back({sx,sy}),r.push_back({sx+1,sy});
	for(x=sx,y=sy;!ask(x,y);v.push_back({x,y}))go(x,y,mp[x][y]);
	Getrevmap();
	for(x=sx+1,y=sy;!ask(x,y);r.push_back({x,y}))go(x,y,rmp[x][y]);
	reverse(r.begin(),r.end());
	while(v.size())cout<<v.back().fst<<' '<<v.back().snd<<'\n',v.pop_back();
	while(r.size())cout<<r.back().fst<<' '<<r.back().snd<<'\n',r.pop_back();
	cout<<"-1 -1"<<endl;
	memset(mp,0,sizeof mp),memset(rmp,0,sizeof rmp);//记得清空地图
	Getrmap(),v.push_back({sx,sy}),r.push_back({sx-1,sy});
	for(x=sx,y=sy;!ask(x,y);v.push_back({x,y}))go(x,y,mp[x][y]);
	Getrevmap();
	for(x=sx-1,y=sy;!ask(x,y);r.push_back({x,y}))go(x,y,rmp[x][y]);
	reverse(r.begin(),r.end());
	while(v.size())cout<<v.back().fst<<' '<<v.back().snd<<'\n',v.pop_back();
	while(r.size())cout<<r.back().fst<<' '<<r.back().snd<<'\n',r.pop_back();
	cout<<"-1 -1"<<endl;
	return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：2)

这道题貌似还没有题解啊，交一发吧！

注意到题目中已经给出了路径，将其分为两部分，考虑构造一个简单环，穿过每一个部分里的所有点，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/edlndz5x.png)

橙色的为环，红色的是路径。

于是我们考虑构造“锯齿形”，注意到齿的长度应该为偶数，把图建出来后双向搜索即可。

代码：

```cpp
//By: Luogu@⚡炭治郎⚡(a.k.a. Kamado_Tanjiro)(LuoguID:308854)
#include <bits/stdc++.h>
#define rep(i,x,y,z) for(int i=(x);i<=(y);i+=(z))

using namespace std;

const int INF=(sizeof(int)==4?0x3f3f3f3f:0x3f3f3f3f3f3f3f3f);
const int MOD=998244353;
const long double EPS=1e-7;
const int MAXN=110;

vector<pair<int,int>> Path;
vector<int> PathInLine[MAXN];
int AskSeqHelp[MAXN];
bool QwQ[MAXN][MAXN];
map<pair<int,int>,pair<pair<int,int>,pair<int,int>>> Graph;
pair<int,int> WeaknessPoint0,WeaknessPoint1;

void Run0(pair<int,int> t,int FirstNotEq0)
{
	cout<<"? "<<t.first<<" "<<t.second<<endl;
	cout<<flush;

	int q;

	cin>>q;
	fflush(stdin);

	cout<<flush;

	if(q)
	{
		WeaknessPoint0=t;

		return ;
	}

	Run0(Graph[t].first,FirstNotEq0);
}

void Run1(pair<int,int> t,int FirstNotEq0)
{
	cout<<"? "<<t.first<<" "<<t.second<<endl;
	cout<<flush;

	int q;

	cin>>q;
	fflush(stdin);

	cout<<flush;

	if(q)
	{
		WeaknessPoint1=t;

		return ;
	}

	Run1(Graph[t].second,FirstNotEq0);
}

void Output0(pair<int,int> t,pair<int,int> e)
{
	cout<<t.first<<" "<<t.second<<endl;
	cout<<flush;

	if(t==WeaknessPoint1)
	{
		return ;
	}

	Output0(Graph[t].second,e);
}

signed main()
{
	int n,m;

	cin>>n>>m;
	fflush(stdin);

	int x,y;

	while(cin>>x>>y)
	{
		Path.push_back({x,y});

		if(x==n && y==m)
			break ;
	}

	int lx=1;

	for(auto i:Path)
	{
		if(lx!=i.first)
		{
			if(lx%2==0)
			{
				AskSeqHelp[lx]=AskSeqHelp[lx-1];
			}
			if(lx%2==1)
			{
				if(PathInLine[lx][PathInLine[lx].size()-1]%2)
					AskSeqHelp[lx]=PathInLine[lx][PathInLine[lx].size()-1]-1;
				else
					AskSeqHelp[lx]=PathInLine[lx][PathInLine[lx].size()-1];
			}

			lx++;
		}

		PathInLine[lx].push_back(i.second);
	}

	AskSeqHelp[n]=AskSeqHelp[n-1];

	/*
	for(int i=1;i<=n;i++)
		cout<<AskSeqHelp[i]<<endl;
	*/

	int FirstNotEq0=INF;

	for(int i=1;i<=n;i++)
	{
		if(AskSeqHelp[i]==0)
			continue ;

		FirstNotEq0=min(FirstNotEq0,i);

		if(i%2)
		{
			for(int j=2;j<AskSeqHelp[i];j++)
			{
				Graph[make_pair(i,j)].second=make_pair(i,j+1);
				Graph[make_pair(i,j+1)].first=make_pair(i,j);
			}

			Graph[make_pair(i,AskSeqHelp[i])].second=make_pair(i+1,AskSeqHelp[i]);
			Graph[make_pair(i+1,AskSeqHelp[i])].first=make_pair(i,AskSeqHelp[i]);
		}
		else
		{
			for(int j=AskSeqHelp[i];j>2;j--)
			{
				Graph[make_pair(i,j)].second=make_pair(i,j-1);
				Graph[make_pair(i,j-1)].first=make_pair(i,j);
			}

			Graph[make_pair(i,2)].second=make_pair(i+1,2);
			Graph[make_pair(i+1,2)].first=make_pair(i,2);
		}
	}

	Graph[make_pair(FirstNotEq0,2)].first=make_pair(FirstNotEq0,1);
	Graph[make_pair(FirstNotEq0,1)].second=make_pair(FirstNotEq0,2);

	for(int i=FirstNotEq0;i<n;i++)
	{
		Graph[make_pair(i,1)].first=make_pair(i+1,1);
		Graph[make_pair(i+1,1)].second=make_pair(i,1);
	}

	Graph[make_pair(n,1)].second=make_pair(n-1,1);
	Graph[make_pair(n,1)].first=make_pair(n,2);
	Graph[make_pair(n,2)].second=make_pair(n,1);

	Run0(make_pair(FirstNotEq0,1),FirstNotEq0);
	Run1(make_pair(FirstNotEq0,2),FirstNotEq0);
	Output0(WeaknessPoint0,WeaknessPoint1);

	cout<<"-1 -1"<<endl<<flush;

	Graph.clear();

	int LastNotEq0=-INF;

	for(int i=1;i<=n;i++)
	{
		if(AskSeqHelp[i]==m)
			continue ;

		LastNotEq0=max(LastNotEq0,i);

		if(i%2==0)
		{
			for(int j=AskSeqHelp[i]+1;j<m-1;j++)
			{
				Graph[make_pair(i,j)].second=make_pair(i,j+1);
				Graph[make_pair(i,j+1)].first=make_pair(i,j);
			}

			Graph[make_pair(i,m-1)].second=make_pair(i+1,m-1);
			Graph[make_pair(i+1,m-1)].first=make_pair(i,m-1);
		}
		else
		{
			for(int j=m-1;j>AskSeqHelp[i]+1;j--)
			{
				Graph[make_pair(i,j)].second=make_pair(i,j-1);
				Graph[make_pair(i,j-1)].first=make_pair(i,j);
			}

			Graph[make_pair(i,AskSeqHelp[i]+1)].second=make_pair(i+1,AskSeqHelp[i]+1);
			Graph[make_pair(i+1,AskSeqHelp[i]+1)].first=make_pair(i,AskSeqHelp[i]+1);
		}
	}

	Graph[make_pair(1,m-1)].first=make_pair(1,m);
	Graph[make_pair(1,m)].second=make_pair(1,m-1);

	for(int i=1;i<LastNotEq0;i++)
	{
		Graph[make_pair(i,m)].first=make_pair(i+1,m);
		Graph[make_pair(i+1,m)].second=make_pair(i,m);
	}

	Graph[make_pair(LastNotEq0,m)].second=make_pair(LastNotEq0-1,m);
	Graph[make_pair(LastNotEq0,m-1)].second=make_pair(LastNotEq0,m);
	Graph[make_pair(LastNotEq0,m)].first=make_pair(LastNotEq0,m-1);

	Run0(make_pair(1,m),FirstNotEq0);
	Run1(make_pair(1,m-1),FirstNotEq0);
	Output0(WeaknessPoint0,WeaknessPoint1);

	cout<<"-1 -1"<<endl;
	cout<<flush;

	return 0;
}
```

---

