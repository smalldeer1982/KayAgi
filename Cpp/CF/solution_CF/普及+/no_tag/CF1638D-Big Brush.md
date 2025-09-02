# Big Brush

## 题目描述

You found a painting on a canvas of size $ n \times m $ . The canvas can be represented as a grid with $ n $ rows and $ m $ columns. Each cell has some color. Cell $ (i, j) $ has color $ c_{i,j} $ .

Near the painting you also found a brush in the shape of a $ 2 \times 2 $ square, so the canvas was surely painted in the following way: initially, no cell was painted. Then, the following painting operation has been performed some number of times:

- Choose two integers $ i $ and $ j $ ( $ 1 \le i < n $ , $ 1 \le j < m $ ) and some color $ k $ ( $ 1 \le k \le nm $ ).
- Paint cells $ (i, j) $ , $ (i + 1, j) $ , $ (i, j + 1) $ , $ (i + 1, j + 1) $ in color $ k $ .

All cells must be painted at least once. A cell can be painted multiple times. In this case, its final color will be the last one.

Find any sequence of at most $ nm $ operations that could have led to the painting you found or state that it's impossible.

## 说明/提示

In the first test case, the solution is not unique. Here's one of them:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638D/a19f3f2204a2363bab52391bc42a7f1ff29f94cb.png)In the second test case, there is no way one could obtain the given painting, thus the answer is $ -1 $ .

## 样例 #1

### 输入

```
4 4
5 5 3 3
1 1 5 3
2 2 5 4
2 2 4 4```

### 输出

```
6
1 3 3
3 3 4
2 2 5
1 1 5
2 1 1
3 1 2```

## 样例 #2

### 输入

```
3 4
1 1 1 1
2 2 3 1
2 2 1 1```

### 输出

```
-1```

# 题解

## 作者：wumingwei (赞：12)

题目: [Big Brush](https://www.luogu.com.cn/problem/CF1638D)
# 思路
题目看了遍，$2≤n,m≤1000$，所以采用顺序深搜或者暴力枚举是不可取的。

所以便采用倒序进行 BFS。

我们会发现，每次更改后，只会影响到周围 $8$ 个的结果，及左上，上，右上，左，右，左下，下，右下。
# 代码
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1003;
int a[N][N],f[8][2]={{1,0},{0,1},{1,1},{0,-1},{-1,0},{-1,-1},{1,-1},{-1,1}};//方向 
int n,m,book[N][N]; 
int s;
struct S//x,y为坐标 z为颜色 
{
	int x,y,z;
}w;//临时存储 
queue<S> q;
vector<S> v;//存储答案 
void change(int x,int y)
{
	a[x][y]=a[x+1][y]=a[x][y+1]=a[x+1][y+1]=-1;//-1为无色 
}
bool check(int x,int y)//判断是否可以染色 
{
	if(x>=1&&x<n&&y>=1&&y<m)//是否在范围内 
	{
		s=-1;
		for(int i=x;i<=x+1;i++)
		{
			for(int j=y;j<=y+1;j++)
			{
				if(a[i][j]!=-1&&s==-1)
				s=a[i][j];
				else
				if(a[i][j]!=-1&&a[i][j]!=s)return 0;
			}
		}
		return 1;
	}
	return 0;
}
bool finish()//是否成功 
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]!=-1)return 0;
		}
	}
	return 1;
}
int main()
{
	std::ios::sync_with_stdio(false);//看不见我 
	std::ios::sync_with_stdio(false);//看不见我 
	cin.tie(0);//看不见我 
	cout.tie(0);//看不见我 
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<n;i++)//初始判断,就是一开始可以染色的 
	{
		for(int j=1;j<m;j++)
		{
			if(check(i,j)&&!book[i][j])
			{
				book[i][j]=1;
				change(i,j);
				w.x=i;
				w.y=j;
				w.z=s;
				q.push(w);
				v.push_back(w);
			}
		}
	}
	while(!q.empty())//dddd
	{
		S now=q.front();
		q.pop();
		for(int i=0;i<8;i++)//枚举8个方向 
		{
			int nx=now.x+f[i][0];
			int ny=now.y+f[i][1];
			if(check(nx,ny)&&s!=-1&&!book[nx][ny])//s=-1就是4个皆空,无需染色,已经染色的也不需要 
			{
				book[nx][ny]=1;
				change(nx,ny);//改变 
				w.x=nx;
				w.y=ny;
				w.z=s;
				q.push(w);
				v.push_back(w);
			}
		}
	}
	if(!finish())//如果未完成 
	{
		cout<<-1;
		return 0;
	}
	int len=v.size();
	cout<<len<<endl;
	for(int i=len-1;i>=0;i--)//输出 
	{
		cout<<v[i].x<<' '<<v[i].y<<' '<<v[i].z<<endl;
	}
	return 0;
}
```

---

## 作者：enucai (赞：7)

## Preface

考场上这题没想出来，确实是想歪了，噗，掉大分 /kk。

## Analysis

正向构造比较难想，不妨反向思考。

最后一笔一定会将一个 $2\times 2$ 的块涂成一样的颜色，因此每次找一个 $2\times 2$ 且 $4$ 个格子中 未被处理的所有格子 **颜色相同** 的块染色即可。若一个格子已经被染色，则将它的值设为 $0$，即表示已经处理该格子。

最后将答案序列反转输出即可。具体细节间代码。

## Code

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1638/submission/146465726)

```cpp
int n,m,a[1010][1010];
struct node{int x,y,val;};
vector<node> ans;
void paint(int x,int y){
	if(x==0||x==n||y==0||y==m) return;//越界判断
	int val[]={a[x][y],a[x+1][y],a[x][y+1],a[x+1][y+1]};
	sort(val,val+4);
	if(val[3]==0) return;//格子全部被处理则返回
	bool flag=true;
	For(i,0,2) if(val[i]!=0&&val[i]!=val[3]) flag=false;
	if(!flag) return;//有未被处理的格子颜色不相等，不能处理改2*2块
	ans.pb((node){x,y,val[3]});//对这个2*2的块进行染色
	For(i,x,x+1) For(j,y,y+1) a[i][j]=0;//标记处理
	For(i,x-1,x+1) For(j,y-1,y+1) paint(i,j);//周围8个块都可能可以染色
}
signed main(){
	read(n,m);
	For(i,1,n) For(j,1,m) read(a[i][j]);
	For(i,1,n-1) For(j,1,m-1) paint(i,j);
	reverse(ans.begin(),ans.end());//反转答案序列
	For(i,1,n) For(j,1,m) if(a[i][j]!=0){write(-1,'\n');return 0;}//判断无解
	write(ans.size(),'\n');
	for(auto p:ans) write(p.x,' ',p.y,' ',p.val,'\n');
}
```

---

## 作者：Milmon (赞：5)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF1638D) & [Problem](//www.luogu.com.cn/problem/CF1638D)

## 题目大意
给定一个大小为 $n\times m$ 的画板，初始画板上没有任何颜色，每次可以选择一个 $2\times 2$ 的相邻田字格进行颜色填充。给定画板的最终形态，判断是否可以绘制出这样的形态，如果可以，给出任意一种可行的绘制方案。

## 解题思路
采取倒推的解题策略，先找出最后一步填充的田字格。  
把所有可选田字格扫描一遍，找出颜色相同的田字格，并将其设为答案序列的最后几步。  
接着把已加入答案序列的田字格替换成特殊标记。  
每当确定一个田字格加入答案序列时，判断它周围的田字格，是否也是全为一种颜色的，他周围的田字格最多只有 $9$ 种，找到可行的，就加入答案序列。  
最后，判断画板上是否全是特殊标记，如果还有普通颜色，那么即为无法达到。  
时间复杂度 $\Theta(nm)$。

## AC 代码
```
#include <bits/stdc++.h>
using namespace std;
int n,m,a[1001][1001];
struct Answer{
	int x,y,col;
}ans[1000001];//答案序列
int anslen;
bool p[1001][1001];//标记
inline void work(int x,int y){
	if(x<1||x>n-1||y<1||y>m-1||p[x][y])return;
	bool flag=true; int col=-1;
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++){
			if(a[x+i][y+j]==-1)continue;
			if(col==-1)col=a[x+i][y+j];
			flag&=a[x+i][y+j]==col;
		}
	if(col==-1)return;
	if(flag)ans[++anslen]={x,y,col},p[x][y]=true;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)work(i,j);//判断是否是2*2的同色田字格，是的话加入答案
	for(int i=1;i<=anslen;i++){
		for(int j=0;j<=1;j++)
			for(int jj=0;jj<=1;jj++)
				a[ans[i].x+j][ans[i].y+jj]=-1;//标记
		for(int j=-1;j<=1;j++)
			for(int jj=-1;jj<=1;jj++)
				work(ans[i].x+j,ans[i].y+jj);
	}
	bool flag=true;
	for(int i=1;i<=n&&flag;i++)
		for(int j=1;j<=m&&flag;j++)
			flag=a[i][j]==-1;
	if(!flag)printf("-1\n");//还有没绘制的田字格
	else{
		printf("%d\n",anslen);
		for(int i=anslen;i>=1;i--)
			printf("%d %d %d\n",ans[i].x,ans[i].y,ans[i].col);
	}
	return 0;
} 
```

---

## 作者：jianhe (赞：4)

与 [CF37E Trial for Chief](https://www.luogu.com.cn/problem/CF37E) 类似的思路，将染色的过程倒过来做，那么问题就变成了：选择一个 $2\times 2$  的矩形，满足矩形内元素的颜色相同，将其染为任意颜色，求最终染为全白色的方案。

小技巧：我们可以用 `-1` 来表示 **任意颜色**，特判即可。

那么这道题就变得简单了。跑个 `bfs` 即可，记得最后要倒着输出~

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1010;
ll n,m,d,a[N][N],ans;
ll dx[]={-1,-1,-1,0,0,1,1,1};
ll dy[]={-1,0,1,-1,1,-1,0,1};
bool vis[N][N];
struct P{ll x,y,c;};
struct Q{ll x,y;};
queue<Q> q;
vector<P> e;
bool check(ll x,ll y){
	if(x<1||x>=n||y<1||y>=m) return 0;
	d=-1;
	for(int i=x;i<=x+1;i++)
		for(int j=y;j<=y+1;j++)
			if(a[i][j]!=-1)
				if(d==-1) d=a[i][j];
				else if(a[i][j]!=d) return 0;
	return 1;
}
bool ok(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!=-1) return 0;
	return 1;
}
void xg(ll x,ll y){a[x][y]=a[x+1][y]=a[x][y+1]=a[x+1][y+1]=-1;}
void bfs(){
	while(!q.empty()){
		Q t=q.front();q.pop();
		ll x=t.x,y=t.y;
		for(int i=0;i<8;i++){
			ll px=x+dx[i],py=y+dy[i];
			if(check(px,py)&&d!=-1&&!vis[px][py]){
				vis[px][py]=1;xg(px,py);
				q.push({px,py});e.push_back({px,py,d});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>a[i][j];
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
			if(check(i,j)){
				vis[i][j]=1;xg(i,j);
				q.push({i,j});e.push_back({i,j,d});
			}
	bfs();
	if(!ok()) cout<<"-1";
	else{
		cout<<e.size()<<"\n";
		reverse(e.begin(),e.end());
		for(auto t:e) cout<<t.x<<" "<<t.y<<" "<<t.c<<"\n";
	} 	
	return 0;
}

```

---

## 作者：Eason_AC (赞：3)

## Content
小 A 有一个 $n\times m$ 的网格图。设第 $i$ 行第 $j$ 列的格子为 $(i,j)$，颜色为 $c_{i,j}$。初始时所有格子均未涂色。小 A 告诉你他将对此网格图进行若干次如下操作：

- 选定一个格子 $(x,y)$ 和一个颜色 $C$，需要保证 $1\leqslant x\leqslant n$，$1\leqslant y\leqslant m$，$1\leqslant C\leqslant nm$。
- 将 $(x,y)$，$(x+1,y)$，$(x,y+1)$，$(x+1,y+1)$ 这四个格子均涂上颜色 $C$。如果某个格子之前已被涂色，那么原来的颜色将会被覆盖。换句话说，将 $c_{x,y}$，$c_{x,y+1}$，$c_{x+1,y}$，$c_{x+1,y+1}$ 的值替换为 $C$。

不久之后，小 A 把涂好了的网格图拿给你看，这个网格图上的所有格子都涂上了一种颜色。请你构造出一个最多包含 $nm$ 次操作的方案。输出格式如下：

如果存在最多 $nm$ 次操作的方案，首先先输出一行一个整数 $k$ 表示操作次数，接下来 $k$ 行每行三个整数，分别表示第 $i$ 次操作选定的格子的横坐标、纵坐标和选定的颜色。如果不存在，输出一行 `-1`。

**数据范围：$2\leqslant n,m\leqslant 1000$，$1\leqslant c_{i,j}\leqslant nm$。**
## Solution
这题考场上想到了思路，但是由于写的过于复杂而写挂了，结束前也没调出来，再加上赛时 ABC 切的太慢从而导致这一场狂掉分 /kk

首先，如果正着考虑的话会发现根本没办法下手，那么正难则反，我们来考虑倒过来怎么做。

很容易发现，最后一次涂色之后，一定会有颜色相同 $2\times 2$ 的一块，换句话说，一定存在一个格子 $(x,y)$，使得 $c_{x,y}=c_{x,y+1}=c_{x+1,y}=c_{x+1,y+1}$。我们不妨就从这里下手，倒过去推，把整个网格图变成初始状态，即所有格子都未涂色的状态，每次推之前记录一下整个操作序列，整个推完后，操作序列也就出来了。

感觉这个想法非常的有道理，继续往下想。然后我们发现无解的状态也就呼之欲出了：**在把能倒推过去的全部倒推完以后，格子上还有格子的颜色没被擦除**。我们只需要在倒推完以后，扫一遍这个网格图进行判断即可。

接下来的关键就是如何把颜色按照次序擦除。我们不妨考虑用最朴素的 DFS，即从某个满足 $c_{x,y}=c_{x+1,y}=c_{x,y+1}=c_{x+1,y+1}$ 的 $(x,y)$ 下手。然后发现在擦除这四个格子的颜色之后，只会影响与 $(x,y)$ 八联通的所有格子。然后考虑左上角为这些八联通的格子的 $2\times 2$ 的一块的当前涂色情况，如果所有格子都已经被擦除了，那么就不用考虑这个格子了，直接跳过。否则，再看是否仅有部分格子未涂色，而剩余涂了色的格子颜色又相同即可，将其还原成相同颜色的 $2\times 2$ 的格子之后再继续往下搜索，一直搜到所有格子的颜色都被擦除了，搜索也就结束了。

这种搜索的最坏情况是对所有满足 $1\leqslant i<n$，$1\leqslant j<m$ 的格子 $(i,j)$ 都进行了一次操作，总操作次数也不过 $(n-1)(m-1)=nm-n-m-1<nm$，因此可以说明我们搜索的正确性。

注意，由于我们是倒推到初始状态的，而我们想得到的操作序列是要从初始状态正推过去，所以，我们应当倒着把整个操作序列输出一遍。
## Code
```cpp
namespace Solution {
    const int N = 1007;
    const int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
    const int dy[] = {0, 0, 1, -1, 1, -1, -1, 1};
    int n;
    int m;
    int col[N][N];
    struct qry {
		int x;
		int y;
		int c;
	};
	vector<qry> res;
	
	int get_col(int x, int y) {
		if(!col[x][y]
		&& !col[x][y + 1]
		&& !col[x + 1][y]
		&& !col[x + 1][y + 1])
			return 0;
		int ans;
		if(col[x][y])
			ans = col[x][y];
		else if(col[x][y + 1])
			ans = col[x][y + 1];
		else if(col[x + 1][y])
			ans = col[x + 1][y];
		else if(col[x + 1][y + 1])
			ans = col[x + 1][y + 1];
		if((col[x][y] && ans != col[x][y])
		|| (col[x + 1][y] && ans != col[x + 1][y])
		|| (col[x][y + 1] && ans != col[x][y + 1])
		|| (col[x + 1][y + 1] && ans != col[x + 1][y + 1]))
			return 0;
		return ans;
	}
	void dfs(int x, int y) {
		int c = get_col(x, y);
		if(!c)
			return;
		res.push_back((qry){x, y, c});
		col[x][y] =
		col[x][y + 1] = 
		col[x + 1][y] = 
		col[x + 1][y + 1] = 0;
		for(int i = 0; i <= 7; ++i) {
			if(x + dx[i] < 1 || x + dx[i] >= n || y + dy[i] < 1 || y + dy[i] >= m)
				continue;
			dfs(x + dx[i], y + dy[i]);
		}
	}

	void Main() {
        read(n, m);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                read(col[i][j]);
        for(int i = 1; i < n; ++i)
        	for(int j = 1; j < m; ++j)
        		if(col[i][j] == col[i][j + 1]
				&& col[i][j] == col[i + 1][j]
				&& col[i][j] == col[i + 1][j + 1])
					dfs(i, j);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				if(col[i][j]) {
					puts("-1");
					return;
				}
		write(res.size());
		puts("");
		reverse(res.begin(), res.end());
		for(auto i : res)
			printf("%d %d %d\n", i.x, i.y, i.c);
		return;
	}
}
```

---

## 作者：yaoyuchen2021 (赞：2)

# 题目大意
给定一个大小为 $n\times m$ 的画板，初始画板上没有任何颜色，每次可以选择一个 $2\times 2$ 的小正方形进行颜色填充。给定画板的最终形态，判断是否可以在 $nm$ 步内绘制出这样的形态，如果可以，给出**任意一种**可行的绘制方案，否则输出 $-1$ 。

# 解题思路
考虑 **倒推** 最后画上的一笔肯定是给出画板上的一个大小为 $2\times 2$ 的颜色相同的小正方形。将它找出来后，存入答案，再做好特殊标记。接下来再继续寻找，要找的是 **只含有一种颜色（必须含有） 和特殊标记的 $2\times 2$ 的小正方形** ，可以这样一直重复下去，直到这种小正方形找不出来。最后再检查一遍画板，如果还有格子有颜色，则无法涂成给定的样式。

另外治理有一个坑点：题目要求输出的是：

> 如果可以，给出**任意一种**可行的绘制方案。

而不是：

> 如果可以，给出**步数最少的一种**可行的绘制方案。

所以只需要找到可行方案，不需要保证自己的方案和样例中的步数一样。

注：步数比样例多是因为有时样例中给出的方案涂的是方框一，而我们的代码会先搜到方框二。

![哎呀，图片加载失败了呢](https://cdn.luogu.com.cn/upload/image_hosting/oq53f4eb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005][1005],k,sum;//sum表示打上特殊标记的格子数
struct xxx
{
    int x;
    int y;
    int color;
}ans[1000005];
void p(int x,int y)
{
    if(!x||!y||x==n||y==m)return ;
    //31~35行参考了其它题解的做法。
    int v[]={a[x][y],a[x][y+1],a[x+1][y],a[x+1][y+1]};
    sort(v,v+4);
    if(!v[3])return ;//没有颜色，不用再刷一次，这样可以保证步数小于nm
    for(int i=0;i<=2;i++)if(v[i]&&v[i]!=v[3])return ;//颜色相同
    ans[++k].x=x;ans[k].y=y;ans[k].color=v[3];
    //38~41行为打特殊标记，这里我用0作为特殊标记
    if(a[x][y])a[x][y]=0,sum++;
    if(a[x][y+1])a[x][y+1]=0,sum++;
    if(a[x+1][y])a[x+1][y]=0,sum++;
    if(a[x+1][y+1])a[x+1][y+1]=0,sum++;
    p(x-1,y-1);p(x-1,y);p(x-1,y+1);p(x,y-1);
    p(x,y+1);p(x+1,y-1);p(x+1,y);p(x+1,y+1);
    return ;
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
    for(int i=1;i<n;i++)for(int j=1;j<m;j++)p(i,j);
    if(sum!=m*n)
    {
        cout<<"-1";
        return 0;
    }
    cout<<k<<"\n";
    for(int i=k;i;i--)cout<<ans[i].x<<" "<<ans[i].y<<" "<<ans[i].color<<"\n";
    return 0;
}
```


---

## 作者：LinkyChristian (赞：1)

考场上想出来了，可惜被抓去睡觉了。

首先如果我们要正着构造的话不太好构造，这时候我们观察到一个特点：在最后一步操作后一定会留下一个 $2 \times 2$ 的同色方格，这就引导我们往构造题的常见套路——反向构造来想。

考虑将一个 $2 \times 2$ 方块染成同色的反操作：将一个 $2 \times 2$ 的同色方块替换成任意颜色。将无色方块看成可以变作任意颜色的方块，操作变为将 $2 \times 2$ 的同色方块变为无色，之后由于无色方块可以变作任何颜色，因此如果有一个残缺的 $2 \times 2$ 同色方块但其所缺少的部分是无色方块，那我们就可以直接将无色方块看做这种颜色，直接将其消掉。

考虑消掉一个 $2 \times 2$ 方块后影响的最多是以其为中心的 $4 \times 4$ 方块，其左上角最多在原本左上角的八连通块位置，因此往原本左上角的八连通块搜索即可，代码简单，可以自行写出。

掉大分.jpg

---

## 作者：imljw (赞：0)

根据题目，我们发现，最后一次涂色不可能被覆盖，所以有解的肯定有一个 $2 \times 2$ 的颜色一样的方块，其次，因为每次都是 $2 \times 2$ 的方块，所以不管怎么涂，每行，每列最后一个被覆盖的 $1 \times 2$ 或 $2 \times 1$ 的位置都不会被覆盖，所以有解的每行都有至少一个 $1 \times 2$ 的一样颜色的，每列都有至少一个 $2 \times 1$ 的一样颜色的，判断一下即可。

仅供参考，请勿抄袭。
```cpp
#include<bits/stdc++.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
namespace IN {
	const int MANPUT = 1000000;
#define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MANPUT),p1==p2)?EOF:*p1++)
	char buf[MANPUT],*p1,*p2;
	template<typename T>inline void read(T &x) {
		static std::streambuf *inbuf=cin.rdbuf();
		x=0;
		register int f=0,flag=false;
		register char ch=getc();
		while(!isdigit(ch)) {
			if (ch=='-') f=1;
			ch=getc();
		}
		if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
		while(isdigit(ch)) {
			x=x*10+ch-48;
			ch=getc();
		}
		x=f?-x:x;
	}
	template<typename T,typename ...Args>inline void read(T& a,Args& ...args) {
		read(a);
		read(args...);
	}
#undef getc
}
using namespace IN;
int T,n,m,a;
int s[205][205];
int main(){
	read(T);
	while(T--){
		read(n,m);
		memset(s,0,sizeof(s));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)read(s[i][j]);
		}
		for(int i=1;i<=n;i++){
			a=0;
			for(int j=1;j<=m;j++){
				if(s[i][j]==s[i][j+1]){
					a=1;
					break;
				}
			}
			if(!a){
				puts("No");
				break;
			}
		}
		if(!a)continue;
		for(int j=1;j<=m;j++){
			a=0;
			for(int i=1;i<=n;i++){
				if(s[i][j]==s[i+1][j]){
					a=1;
					break;
				}
			}
			if(!a){
				puts("No");
				break;
			}
		}
		if(!a)continue;
		a=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(s[i][j]==s[i-1][j]&&s[i][j]==s[i-1][j-1]&&s[i][j]==s[i][j-1]){
					a=1;
				}
			}
		}
		if(!a)puts("No");
		else puts("Yes");
		a=0;
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1638D 题解



## 思路分析

考虑从结果入手，每次选择一个 $2\times2$ 的同色方格清空，最后倒序操作即可。

由于每个位置只会被最后一个操作覆盖，那么倒序操作时已经被操作的格子可以重复操作。

因此每次选择一个合法的同色方格清空一定没有后效性，注意到每个格子至多被清空一次，所以操作次数一定在 $n\times m$ 以内。

不过如果暴力找操作位置是 $\Theta(nm)$ 的，重复 $n\times m$ 次会超时。

注意到清空一个方格后，只有可能影响与其相交的 $9$ 个方格，使得这些方格可以被操作，因此做一遍 BFS 即可。

如果 BFS 结束后还有位置没被清空则输出无解。

时间复杂度 $\Theta(nm)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1001;
const int dx[]={-1,-1,-1,0,0,1,1,1};
const int dy[]={-1,0,1,-1,1,-1,0,1};
struct node {
	int x,y,c;
};
int a[MAXN][MAXN];
inline bool valid(int x,int y) {
	int col=max(max(a[x][y],a[x+1][y+1]),max(a[x][y+1],a[x+1][y]));
	if(!col) return false;
	return (a[x][y]==col||a[x][y]==0)&&(a[x+1][y+1]==col||a[x+1][y+1]==0)&&
		   (a[x+1][y]==col||a[x+1][y]==0)&&(a[x][y+1]==col||a[x][y+1]==0);
}
inline int color(int x,int y) {
	return max(max(a[x][y],a[x+1][y+1]),max(a[x][y+1],a[x+1][y]));
}
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector <node> op; queue <node> q;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<n;++i) {
		for(int j=1;j<m;++j) {
			if(valid(i,j)) q.push((node){i,j,0});
		}
	}
	while(!q.empty()) {
		int x=q.front().x,y=q.front().y; q.pop();
		if(color(x,y)==0) continue;
		op.push_back((node){x,y,color(x,y)});
		a[x][y]=a[x+1][y]=a[x][y+1]=a[x+1][y+1]=0;
		for(int k=0;k<8;++k) {
			int tx=x+dx[k],ty=y+dy[k];
			if(tx<1||ty<1||tx>=n||ty>=m) continue;
			if(valid(tx,ty)) q.push((node){tx,ty,0});
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(a[i][j]!=0) {
				puts("-1");
				return 0;
			}
		}
	}
	printf("%d\n",(int)op.size());
	reverse(op.begin(),op.end());
	for(auto u:op) printf("%d %d %d\n",u.x,u.y,u.c);
	return 0;
}
```



---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$
---
### 解题思路：

正难则反，考虑倒推。

任意一个四个整块的位置都可以作为最后一画，先将这些位置入队，然后暴力 $\text{BFS}$ 向四周拓展就行了。

总复杂度 $O(mn)$。

---
注意不要把 $n$ 和 $m$ 写反。

---
### 代码：
```cpp
#include<cstdio>
#include<queue>
using namespace std;
int n,m,a[1005][1005],ax[1005*1005],cnt,nx,ny;
int x,ay[1005*1005],ac[1005*1005];
queue <int> qx,qy;
int _check(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
	int flag=0;
	if(a[x1][y1]!=0)flag=a[x1][y1];
	if(a[x2][y2]!=0){
		if(flag!=0&&flag!=a[x2][y2])return 0;
		flag=a[x2][y2];
	}
	if(a[x3][y3]!=0){
		if(flag!=0&&flag!=a[x3][y3])return 0;
		flag=a[x3][y3];
	}
	if(a[x4][y4]!=0){
		if(flag!=0&&flag!=a[x4][y4])return 0;
		flag=a[x4][y4];
	}
	return flag;
}
int check(int x,int y){
	if(x+1>n||y+1>m||x<=0||y<=0)return 0;
	return _check(x,y,x+1,y,x,y+1,x+1,y+1);
}
void clear(int x,int y){
	a[x][y]=0;
	a[x+1][y+1]=0;
	a[x+1][y]=0;
	a[x][y+1]=0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	scanf("%d",&a[i][j]);
	for(int i=1;i<n;i++)
	for(int j=1;j<m;j++)
	if(x=check(i,j)){
		qx.push(i);qy.push(j);
		cnt++;ax[cnt]=i;ay[cnt]=j;ac[cnt]=x;
		clear(i,j);
	}
	while(!qx.empty()){
		nx=qx.front();
		ny=qy.front();
		qx.pop();qy.pop();
		for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
		if(x=check(nx+i,ny+j)){
			qx.push(nx+i);qy.push(ny+j);
			cnt++;ax[cnt]=nx+i;ay[cnt]=ny+j;ac[cnt]=x;
			clear(nx+i,ny+j);
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(a[i][j]!=0){
		printf("-1\n");
		return 0;
	}
	printf("%d\n",cnt);
	for(int i=cnt;i>=1;i--)
	printf("%d %d %d\n",ax[i],ay[i],ac[i]);
	return 0;
}
```


---

## 作者：PrincessQi (赞：0)

考虑倒推。

设当前可能没有颜色的区块的颜色为 $-1$。

若当前的图含有一个只由 $-1$ 和某一种颜色的 $2\times 2$ 矩形，则将这个矩形的颜色全部设为 $-1$，并统计增加的 $-1$ 个数。

若 $-1$ 的个数等于图的大小（即 $n\times m$），则有解。解可以在 dfs 时顺便求出。

否则，输出无解即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
stack<int>s,ss,sss;
int n,m,qaq,qwq[1005][1005],mp[1005][1005],dx[4]={0,0,1,1},dy[4]={0,1,0,1},ddx[8]={-1,-1,-1,0,0,1,1,1},ddy[8]={-1,0,1,-1,1,-1,0,1};
void dfs(int x,int y){
	s.push(x);
	ss.push(y);
	qwq[x][y]=1;
	int col=-1;
	for(int j=0;j<4;j++)
		if(mp[x+dx[j]][y+dy[j]]!=-1)
			col=mp[x+dx[j]][y+dy[j]],mp[x+dx[j]][y+dy[j]]=-1,qaq++;
	sss.push(col);
	mp[x][y]=mp[x+1][y]=mp[x][y+1]=mp[x+1][y+1]=-1;
	for(int i=0;i<8;i++)
		if(x+ddx[i]>=1&&x+ddx[i]<n&&y+ddy[i]>=1&&y+ddy[i]<m&&qwq[x+ddx[i]][y+ddy[i]]==0){
			int ans=-1;
			for(int j=0;j<4;j++)
				if(mp[x+ddx[i]+dx[j]][y+ddy[i]+dy[j]]!=-1){
					if(ans!=-1&&ans!=mp[x+ddx[i]+dx[j]][y+ddy[i]+dy[j]]){
						ans=-2;
						break;
					}
					if(ans==-1)ans=mp[x+ddx[i]+dx[j]][y+ddy[i]+dy[j]];
				}
			if(ans>=0)dfs(x+ddx[i],y+ddy[i]);
		}
	if(qaq==n*m){
		printf("%d\n",s.size());
		while(!s.empty()){
			printf("%d %d %d\n",s.top(),ss.top(),sss.top());
			s.pop();
			ss.pop();
			sss.pop();
		}
		exit(0);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&mp[i][j]);
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
			if(mp[i][j]==mp[i][j+1]&&mp[i][j]==mp[i+1][j]&&mp[i][j]==mp[i+1][j+1]&&mp[i][j]!=-1)
				dfs(i,j);
	puts("-1");
	return 0;
} 
```

---

## 作者：Hywel (赞：0)

#### 思路
逆向思维。

找出最后一个填充的 $2*2$ 的方格，然后撤销染色操作，再以这个方格为起点继续扩展，直到把整个图扩展到没有染色为止。如果无法继续扩展，则输出 $-1$。

#### 细节
1. 开始时找出的方格及开始后扩展的方格用队列全部储存，逐一处理。
2. 扩展时记录操作用栈记录，最后倒序输出即可。
3. 扩展时分两种情况，三缺一和两个连着，样例 $1$ 中最后一步撤销后即为两个连着的情况，这个需要分情况讨论一下。

#### Code
个人感觉我的代码相比其他题解来说还是比较清晰的，更加便于理解，~~就是考场没调出来。~~

```cpp
#include <bits/stdc++.h>
#define ll long long
#define forever return
using namespace std;

namespace IO
{
	template < typename T > inline void write( T x )
	{
	    if(x < 0)
	        putchar('-') , x = - x;
	    if(x == 0)
	    {
	        putchar('0') ;
	        return ;
	    }
	    if(x > 9)
	        write(x / 10) ;
	    putchar(x % 10 + '0') ;
	    return ;
	}
	template < typename T > inline void read( T &x )
	{
	    x = 0 ; int w = 1 ; char ch = getchar() ;
	    while( !isdigit( ch ) ) { if(ch == '-') w = -1 ; ch = getchar() ; }
	    while( isdigit( ch ) ) x = (x << 1) + (x << 3) + (ch ^ 48) , ch = getchar() ;
	    x *= w;
	}
}

#define writeln(x) write(x) , putchar('\n')
#define writesp(x) write(x) , putchar(' ')
using namespace IO ;

//#define writeln(x) write(x),pc('\n')
//#define writesp(x) write(x),pc(' ')
//using namespace FastIO ;

/* ------------------------------------------------------------------------------------------------------------------------ */
int n , m ;
int a[2020][2020] ;
struct node
{
	int x , y ;
	int c ;
} ;
queue < pair < int , int > > q ;
stack < node > op ; 
signed main()
{
	read( n ) , read( m ) ;
	for( int i = 1 ; i <= n ; ++ i )
		for( int j = 1 ; j <= m ; ++ j )
			read( a[i][j] ) ;
	for( int i = 1 ; i <= n ; ++ i )
	{
		for( int j = 1 ; j <= m ; ++ j )
		{
			if( a[i][j] == a[i][j + 1] && a[i + 1][j] == a[i][j] && a[i + 1][j + 1] == a[i][j])
				q.push(make_pair(i,j));
		}
	}
	while( q.size() ) 
	{
		pair<int,int> fr = q.front() ;
		a[fr.first][fr.second]=0;
		a[fr.first+1][fr.second+1]=0;
		a[fr.first+1][fr.second]=0;
		a[fr.first][fr.second+1]=0;
		//俩连着的
		if(fr.first!=1&&a[fr.first-1][fr.second]==a[fr.first-1][fr.second+1])
		{
			q.push(make_pair(fr.first-1,fr.second));
			op.push(node{fr.first-1 ,  fr.second , a[fr.first-1][fr.second] } ) ;	
		} //正上
		if(fr.first!=n-1&&a[fr.first+2][fr.second]==a[fr.first+2][fr.second+1])
		{
			q.push(make_pair(fr.first+2,fr.second));
			op.push(node{fr.first+2 ,  fr.second , a[fr.first+2][fr.second] } ) ;
		} //正下 
		if(fr.second!=1&&a[fr.first][fr.second-1]==a[fr.first+1][fr.second-1])
		{
			q.push(make_pair(fr.first,fr.second-1));
			op.push(node{fr.first ,  fr.second-1 , a[fr.first][fr.second-1] } ) ;
		} //正左 
		if(fr.second!=n-1&&a[fr.first][fr.second+2]==a[fr.first+1][fr.second+2])
		{
			q.push(make_pair(fr.first,fr.second+2));
			op.push(node{fr.first ,  fr.second+2 , a[fr.first][fr.second+2] } ) ;
		} //正左 
		//三缺一
		if(fr.first!=1&&fr.second!=n&&a[fr.first-1][fr.second+1]==a[fr.first-1][fr.second+2]&&a[fr.first-1][fr.second+2]==a[fr.first][fr.second+2])
		{
			q.push(make_pair(fr.first-1,fr.second+1));
			op.push(node{fr.first-1 ,  fr.second+1 , a[fr.first-1][fr.second+1] } ) ;
		 }//右上
		if(fr.first!=1&&fr.second!=1&&a[fr.first-1][fr.second]==a[fr.first-1][fr.second-1]&&a[fr.first-1][fr.second-1]==a[fr.first][fr.second-1])
		{
			q.push(make_pair(fr.first-1,fr.second+1));
			op.push(node{fr.first-1 ,  fr.second-1 , a[fr.first-1][fr.second-1] } ) ;
		 } //左上
		  if(fr.first!=1&&fr.second!=n&&a[fr.first+1][fr.second+2]==a[fr.first+2][fr.second+1]&&a[fr.first+2][fr.second+2]==a[fr.first+1][fr.second+2])
		{
			q.push(make_pair(fr.first+1,fr.second+1));
			op.push(node{fr.first+1 ,  fr.second+1 , a[fr.first+1][fr.second+1] } ) ;
		 }//右下 
		 if(fr.first!=1&&fr.second!=n&&a[fr.first+1][fr.second-1]==a[fr.first+2][fr.second-1]&&a[fr.first+2][fr.second]==a[fr.first+2][fr.second-1])
		{
			q.push(make_pair(fr.first+1,fr.second+1));
			op.push(node{fr.first+1 ,  fr.second-1 , a[fr.first+1][fr.second-1] } ) ;
		 }//左下 
		q.pop() ;
	}
	while(op.size())
	{
		node fr = op.top();
		cout<<fr.x<<" "<<fr.y<<" " <<fr.c<< " " << endl;
		op.pop();
	}
	forever 0 ;
}


```

---

