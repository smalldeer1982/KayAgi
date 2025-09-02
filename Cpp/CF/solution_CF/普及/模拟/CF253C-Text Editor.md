# Text Editor

## 题目描述

Vasya is pressing the keys on the keyboard reluctantly, squeezing out his ideas on the classical epos depicted in Homer's Odysseus... How can he explain to his literature teacher that he isn't going to become a writer? In fact, he is going to become a programmer. So, he would take great pleasure in writing a program, but none — in writing a composition.

As Vasya was fishing for a sentence in the dark pond of his imagination, he suddenly wondered: what is the least number of times he should push a key to shift the cursor from one position to another one?

Let's describe his question more formally: to type a text, Vasya is using the text editor. He has already written $ n $ lines, the $ i $ -th line contains $ a_{i} $ characters (including spaces). If some line contains $ k $ characters, then this line overall contains $ (k+1) $ positions where the cursor can stand: before some character or after all characters (at the end of the line). Thus, the cursor's position is determined by a pair of integers $ (r,c) $ , where $ r $ is the number of the line and $ c $ is the cursor's position in the line (the positions are indexed starting from one from the beginning of the line).

Vasya doesn't use the mouse to move the cursor. He uses keys "Up", "Down", "Right" and "Left". When he pushes each of these keys, the cursor shifts in the needed direction. Let's assume that before the corresponding key is pressed, the cursor was located in the position $ (r,c) $ , then Vasya pushed key:

- "Up": if the cursor was located in the first line ( $ r=1 $ ), then it does not move. Otherwise, it moves to the previous line (with number $ r-1 $ ), to the same position. At that, if the previous line was short, that is, the cursor couldn't occupy position $ c $ there, the cursor moves to the last position of the line with number $ r-1 $ ;
- "Down": if the cursor was located in the last line ( $ r=n $ ), then it does not move. Otherwise, it moves to the next line (with number $ r+1 $ ), to the same position. At that, if the next line was short, that is, the cursor couldn't occupy position $ c $ there, the cursor moves to the last position of the line with number $ r+1 $ ;
- "Right": if the cursor can move to the right in this line ( $ c&lt;a_{r}+1 $ ), then it moves to the right (to position $ c+1 $ ). Otherwise, it is located at the end of the line and doesn't move anywhere when Vasya presses the "Right" key;
- "Left": if the cursor can move to the left in this line ( $ c&gt;1 $ ), then it moves to the left (to position $ c-1 $ ). Otherwise, it is located at the beginning of the line and doesn't move anywhere when Vasya presses the "Left" key.

You've got the number of lines in the text file and the number of characters, written in each line of this file. Find the least number of times Vasya should push the keys, described above, to shift the cursor from position $ (r_{1},c_{1}) $ to position $ (r_{2},c_{2}) $ .

## 说明/提示

In the first sample the editor contains four lines. Let's represent the cursor's possible positions in the line as numbers. Letter $ s $ represents the cursor's initial position, letter $ t $ represents the last one. Then all possible positions of the cursor in the text editor are described by the following table.

123

12

123s567

1t345

One of the possible answers in the given sample is: "Left", "Down", "Left".

## 样例 #1

### 输入

```
4
2 1 6 4
3 4 4 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
10 5 6 4
1 11 4 2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3
10 1 10
1 10 1 1
```

### 输出

```
3
```

# 题解

## 作者：tongziyu (赞：4)

## Solution
看到这道题，正常人想到的都是 BFS。

不过我不是正常人。

以下是我想到的奇怪算法（似乎跑的比 BFS 快的多？）

从第 $r1$ 行开始走， 依次先走到第 $1$ 行 到第 $n$ 行中的每一行，再到第 $r2$ 行。

这样在竖直方向上的总花费就是 $|i - r1|  + |i - r2|$。

走完这段后，光标所在的列 $c$ 就是所经过的这些行的字符数 $a[i]$，$+1$ 后与 $c1$ 取 $min$ 的值。

这样最后在水平方向上移动的花费就是 $|c - c2|$。

枚举 $1$ ~ $n$ 中的每个数，作为先走到的那一行，将每一次的答案算出取 $min$ 即可。

时间复杂度 $O(n^2)$。

------------


## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];
int n, r1, c1, r2, c2;
inline int read()
{
	register int r = 0, c= getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') r = (r << 3) + (r << 1) + (c ^ 48), c = getchar();
	return r;
} 
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	r1 = read(), c1 = read(), r2 = read(), c2 = read();
	int tmp, ans = 1e5 + 1e2 + 10;
	for (int i = 1; i <= n; ++i) 
	{
		tmp = abs(i - r1) + abs(i - r2);
		int c = c1;
		for (int j = min(r1, min(i, r2)); j <= max(i, max(r1, r2)); ++j) c = min(c, a[j] + 1);
		tmp += abs(c2 - c);  
		ans = min(ans, tmp);
	 } 
	return printf("%d", ans), 0;
}
```

------------
本程序可以优化到 $O(n)$ 的时间复杂度，方法请读者自行探索。

---

## 作者：_Gabriel_ (赞：1)

### 思路

注意本题需要文件读写。

即求光标从位置 $(r1,c1)$ 移动到 $(r2,c2)$ 的最短距离。

解题方法很好想，从初始位置 $(r1,c1)$ 开始 BFS，假设光标当前位置为 $(x,y)$，则他能移动到 $(x-1,y),(x,y-1),(x+1,y),(x,y+1)$ 四个位置，但有一种特殊情况：

```
1 2
3 4 5
6
```

假如光标在编号为 $5$ 的位置上，如果向上移动，则会移动到 $2$，如果向下移动，则会移动到 $6$。

所以要判断当向上或向下移动到的列 $y$ 是否大于当前所在行的字符个数，若大于，则光标位置要改变成当前所在行的行末。

其他地方跟普通的 BFS 没有区别。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll mod = 998244353;
const int N = 1e2 + 10;
struct node {
	int x, y;
};
int a[N], vis[N][100010];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n, sx, sy, ex, ey;
queue<node> q;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i]++;
	}
	cin >> sx >> sy >> ex >> ey;
	if (sx == sy && ex == ey) {
		cout << 0;
		return 0;
	}
	q.push({sx, sy});
	while (!q.empty()) {
		node tmp = q.front();
		q.pop();
		int x = tmp.x, y = tmp.y;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= a[x] && !vis[nx][ny]) {
				ny = min(ny, a[nx]);
                vis[nx][ny] = vis[x][y] + 1;
                q.push({nx, ny});                
			}
		}
	}
	cout << vis[ex][ey];
    return 0;
}
```

[提交记录](https://codeforces.com/problemset/submission/253/287474542)

---

## 作者：ATION001 (赞：1)

## 题目描述
一个文本编辑器，已经写了 $n$ 行，每行有 $a_i$ 个字符。

我们用键盘的上下左右键来控制光标，这个文本编辑器的光标移动方式跟我们平常使用的编辑器（比如洛谷专栏文章编辑器）的光标移动方式相同。

现在光标在位置 $r1,c1$，求移动到位置 $r2,c2$ 最少需要按几次键盘。

**请注意此题需要使用文件读写。**
## 思路
当我们看到“最少距离”这几个字时，就可以想到这是最短路了。

此题跟模板 BFS 没本质上的区别，只是移动方式不同而已。

只需要在转移时加一个特判这题就解决了！！！
```cpp
for(int i=0;i<4;i++){
    int fx=xyx[i][0]+x,fy=xyx[i][1]+y;
    if(fx&&fy&&fx<=n&&fy<=a[x]){// 题目前四个限制就是让我们不要越界
      if(fy>a[fx]){// 就是在这里加一个特判，超出的下一行的边界就移动到下一行的末尾
        fy=a[fx];
      }
      if(!b[fx][fy]){// 正常的 BFS
        b[fx][fy]=b[x][y]+1;
        q.push({fx,fy});  
      }  
    }
}
```
**温馨提示：不加文件读写见祖宗。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],dx,dy,ex,ey,b[110][100010],xyx[10][10]={{0,-1},{0,1},{-1,0},{1,0}};
queue<pair<int,int>>q;
int main(){
    freopen("input.txt", "r", stdin);// 特别注意加文件读写！！！
	freopen("output.txt", "w", stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i],a[i]++;
	}
	cin>>dx>>dy>>ex>>ey;
	if(dx==ex&&dy==ey){
		cout<<0;
		return 0;
	}
	q.push({dx,dy});
	while(q.size()){
		auto x=q.front().first,y=q.front().second;
		q.pop();
		for(int i=0;i<4;i++){
			int fx=xyx[i][0]+x,fy=xyx[i][1]+y;
			if(fx&&fy&&fx<=n&&fy<=a[x]){
				if(fy>a[fx]){
					fy=a[fx];
				}
				if(!b[fx][fy]){
					b[fx][fy]=b[x][y]+1;
					q.push({fx,fy}); 
				}
			}
		}
	}
	cout<<b[ex][ey];
	return 0;    
}
```

---

## 作者：songzhixin (赞：1)

## 题目大意
给你一个文本，共有 $n$ 行，第 $i$ 行有 $a_i + 1$ 个空格。每次可以向上、下、左、右四个方向移动。如果上或下的空格不够，就跳到最后一个。求从 $ ( r1,c1 ) $ 到 $( r2,c2 ) $ 的最短少次数。

## 解题思路
因为求最少次数，所以很容易想到 BFS。那么想向那些方向搜呢？

根据题目，如果当先坐标为 $(x,y)$ 应该有：

$$ \begin{cases} (x,y-1) & (y > 1) \\ (x,y+1) & (y \le a_x) \\ (x-1,y) & (x>1 且  a_{x-1}+1 \ge y) \\ (x+1,y) & (x<n且 a_{x+1}+1 \ge y) \\ (x-1,a_{x-1}+1) & (x>1 且a_{x-1}+1<y) \\ (x+1,a_{x+1} +1) & ( x<n 且 a_{x+1}+1 < y) \end{cases} $$

这样搜索即可，时间复杂度 $O(n \times \max(a_i))$，最大为 $10^7$，可以过。

## 解题代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=105;
const long long M=1e5+5;
long long a[N],n;
bool v[N][M];
long long b[N][M];
long long ax,ay,bx,by;
struct node{
	long long x,y,s;
};
queue<node> q;
void add(long long fx,long long fy,long long fs){
	node t;
	t.s=fs;
	t.x=fx;
	t.y=fy;
	q.push(t);
}
int main(){
	freopen("input.txt","r",stdin);//一定要记得freopen 
	freopen("output.txt","w",stdout);
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	scanf("%lld%lld%lld%lld",&ax,&ay,&bx,&by);//输入起始坐标与目标坐标 
	add(ax,ay,0);
	v[ax][ay]=true;
	while(!q.empty()){
		node aa=q.front();
		q.pop();
		b[aa.x][aa.y]=aa.s;
		if(aa.x==bx&&aa.y==by){
			printf("%lld\n",aa.s);
			return 0;
		}
		if(aa.y>1&&v[aa.x][aa.y-1]==false){//向左 
			v[aa.x][aa.y-1]=true;
			add(aa.x,aa.y-1,aa.s+1);
		}
		if(aa.y<a[aa.x]+1&&v[aa.x][aa.y+1]==false){//向右
			v[aa.x][aa.y+1]=true;
			add(aa.x,aa.y+1,aa.s+1);
		}
		if(aa.x>1&&a[aa.x-1]+1>=aa.y&&v[aa.x-1][aa.y]==false){//向上并且不会超出 
			v[aa.x-1][aa.y]=true;
			add(aa.x-1,aa.y,aa.s+1);
		}
		if(aa.x<n&&a[aa.x+1]+1>=aa.y&&v[aa.x+1][aa.y]==false){//向下并且不会超出 
			v[aa.x+1][aa.y]=true;
			add(aa.x+1,aa.y,aa.s+1);
		}
		if(aa.x>1&&a[aa.x-1]+1<aa.y&&v[aa.x-1][a[aa.x-1]+1]==false){//向上并且会超出
			v[aa.x-1][a[aa.x-1]+1]=true;
			add(aa.x-1,a[aa.x-1]+1,aa.s+1);
		}
		if(aa.x<n&&a[aa.x+1]+1<aa.y&&v[aa.x+1][a[aa.x+1]+1]==false){//向下并且不会超出 
			v[aa.x+1][a[aa.x+1]+1]=true;
			add(aa.x+1,a[aa.x+1]+1,aa.s+1);
		}
	}
	return 0;
}
```

## 易错提示
1、一定要开 freopen。

2、有 $a_i$ 个文本，就有 $a_i+1$ 个间隔。

3、要打标记，避免重复计算。

---

## 作者：封禁用户 (赞：1)

这是一道水题，只需要按题目的要求去bfs即可，注意要读清楚题目， _每次换行如果下一行不够则到下一行最后一个的后面一个！！_ 

记得关注我的博客：https://www.luogu.org/blog/Noi2017/

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105,M=100005;
int a[N],dis[N][M];
queue<pair<pair<int,int>,int>>q;
int main()
{
#ifdef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	int n,r1,c1,r2,c2,kx,ky,kdis,sum=0,cnt;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
	memset(dis,0x3f3f3f3f,sizeof(dis));
	dis[r1][c1]=0;
	q.push(make_pair(make_pair(r1,c1),0));
	while(!q.empty())
	{
		pair<pair<int,int>,int>k=q.front();
		q.pop();
		kx=k.first.first;
		ky=k.first.second;
		kdis=k.second;
		if(kx==r2&&ky==c2)
		{
			printf("%d\n",kdis);
			break;
		}
		if(ky>=2&&kdis+1<dis[kx][ky-1])
		{
			dis[kx][ky-1]=kdis+1;
			q.push(make_pair(make_pair(kx,ky-1),kdis+1));
		}
		if(ky<a[kx]&&kdis+1<dis[kx][ky+1])
		{
			dis[kx][ky+1]=kdis+1;
			q.push(make_pair(make_pair(kx,ky+1),kdis+1));
		}
		if(kx!=n&&kdis+1<dis[kx+1][min(ky,a[kx+1]+1)])
		{
			dis[kx+1][min(ky,a[kx+1]+1)]=kdis+1;
			q.push(make_pair(make_pair(kx+1,min(ky,a[kx+1]+1)),kdis+1));
		}
		if(kx!=1&&kdis+1<dis[kx-1][min(ky,a[kx-1]+1)])
		{
			dis[kx-1][min(ky,a[kx-1]+1)]=kdis+1;
			q.push(make_pair(make_pair(kx-1,min(ky,a[kx-1]+1)),kdis+1));
		}
	}
	return 0;
}

```

---

## 作者：mnlbnkk (赞：0)

# 题目意思
你有一个普通的文本编辑器，唯一不同的是，当你在行首向左，他不会跳到上一行的行末，行尾向右同理，每一行都有一个字符长度，求从一个位置到另一个位置的最少步数。
# 做法
很明显的 BFS，但是某位奇葩的管理既然觉得有人不会 BFS，我替真正不会的人感到无语。
所以这里被迫讲一下搜索的过程，尝试分布理解。
- 1.从队里面找到队头，如果是第一次，那必然取出起点，距离最小，不然因为每一次的步的长度为 $1$，队里面也会是单调的。
- 2.查看这个点是否被走过，因为队列是单调的，所以目前的点如果已经被走过了，那必然不优。
- 3.上下左右走，如果没有走不动，那就加入队尾，这样的话队列仍然是单调的。

最后第一个到达终点的队列元素就是答案。
当然，最后要注意一下：输入的 $a_i$ 需要增加 $1$，原因更简单，因为题面里面说了，要注意有 $a_i+1$ 个点位。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define P pair<ll,ll>
#define Pp pair<ll,P>
#define fi first
#define se second
using namespace std;
const ll N=1e2+9,M=1e5+9;
ll n,a[N],r1,c1,r2,c2,ans;bool vis[N][M];
ll gx[9]={0,0,-1,1},gy[9]={1,-1,0,0};
inline void bfs()
{
    queue<Pp>que;
    que.push({0,{r1,c1}});
    while(!que.empty())
    {
        ll step=que.front().fi+1;
        P tmp=que.front().se;que.pop();
        // cout<<tmp.fi<<' '<<tmp.se<<' '<<step-1<<endl;
        if(tmp.fi==r2 && tmp.se==c2){ans=step-1;break;}
        if(vis[tmp.fi][tmp.se])continue;
        vis[tmp.fi][tmp.se]=1;
        for(int i=0;i<4;i++)
        {
            ll nx=tmp.fi+gx[i],ny=tmp.se+gy[i];
            if(nx<1 || nx>n)continue;
            ny=min(ny,a[nx]);
            que.push({step,{nx,ny}});
        }
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],a[i]++;
    cin>>r1>>c1>>r2>>c2;
    bfs();cout<<ans;
    return 0;
}
```

---

## 作者：XCDRF_ (赞：0)

# CF253C Text Editor 题解

[原题传送门](https://codeforces.com/problemset/problem/253/C)

[更好的阅读体验](https://www.luogu.com.cn/article/f9jgiteg)

## 解题思路

这题的思路其实非常简单，与普通的 BFS 只有一个地方有区别。就是需要特判一下移动到上一行或下一行时列数是否超过下一行的列数限制。若超过，则移动到行末。

因为若每一行有 $k$ 个字符，则光标有 $k+1$ 个位置可以停留。所以在输入的时候，要把每一行的列数加 $1$。

## 注意事项

1. 记得开文件输入输出。
2. 本题很容易 MLE，数组不要开太大。

## 参考代码

```cpp
#include<iostream>
#include<queue>
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=1e2+5,M=1e5+5;
const int dx[]={0,1,-1,0,0};
const int dy[]={0,0,0,1,-1};
queue<pii> q;
int n,r1,c1,r2,c2;
int a[N],dis[N][M];
bool vis[N][M];
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]++;
	}
	cin>>r1>>c1>>r2>>c2;
	q.push(mp(r1,c1));
	vis[r1][c1]=1;
	while(!q.empty()){
		pii t=q.front();
		q.pop();
		for(int i=1;i<=4;i++){
			int xx=t.fi+dx[i],yy=t.se+dy[i];
			if(vis[xx][yy]||xx<1||xx>n||yy<1||yy>a[t.fi]) continue;
			yy=min(yy,a[xx]);
			dis[xx][yy]=dis[t.fi][t.se]+1;
			vis[xx][yy]=1;
			q.push(mp(xx,yy));
		}
	}
	cout<<dis[r2][c2];
	return 0;
}
```

[AC 记录](https://codeforces.com/contest/253/submission/292474395)

感谢管理大大审核，求通过 QwQ。

---

## 作者：lzj666_luogu (赞：0)

## 说明提示

翻译坑人！这道题在 CF 上是要文件操作的，见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/rthg97ae.png)

## 做法

见到这道题我们可以发现可以用题目中给出的条件建一张图，而这道题中所有边的边权均为 $1$，因此可以使用 BFS。

BFS 广度优先搜索是使用队列（queue，先进先出）来实现，整个过程也可以看做一个倒立的树形：

1. 把根节点放到队列的末尾。
2. 每次从队列的头部取出一个元素，查看这个元素所有的下一级元素，把它们放到队列的末尾 (不需要排序，因为默认每次增加权重相同)。并把这个元素记为它下一级元素的前驱。
3. 找到所要找的元素时结束程序。
4. 如果遍历整个树还没有找到，结束程序。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[100 + 5], bx, by, ex, ey;
bool vis[100 + 5][100000 + 5];
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	queue<tuple<int, int, int>>q;
	cin >> bx >> by >> ex >> ey;
	q.emplace(bx, by, 0);
	while (!q.empty()) {
		tuple<int, int, int>now = q.front(); q.pop();
		int x = get<0>(now), y = get<1>(now), d = get<2>(now);
		if (vis[x][y]) continue;
		vis[x][y] = 1;
		if (x == ex && y == ey) {
			cout << d << endl;
			return 0;
		}
		if (y > 1) q.emplace(x, y - 1, d + 1);
		if (y <= a[x]) q.emplace(x, y + 1, d + 1);
		if (x > 1 && a[x - 1] + 1 >= y) q.emplace(x - 1, y, d + 1);
		if (x < n && a[x + 1] + 1 >= y) q.emplace(x + 1, y, d + 1);
		if (x > 1 && a[x - 1] + 1 < y) q.emplace(x - 1, a[x - 1] + 1, d + 1);
		if (x < n && a[x + 1] + 1 < y) q.emplace(x + 1, a[x + 1] + 1, d + 1);
	}
}
```

[AC 记录](https://codeforces.com/contest/253/submission/278239292)

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路
	这道题是一道宽搜，甚至不用连边。。。只需要从起点开始到处搜，判断边界，记录答案即可，不用任何优化可过。这里说一下上下的操作：当前光标要向上或向下时，如果目标行的总列数都没有当前列数大，那么就移到目标行的最后一列，这里将当前列数和目标行列数取小值即可。但是为什么要文件读写。。。
    
- ### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],x,y,xx,yy,dis[105][100005];
struct Queue{
	int hd=0,tl=0,a[1000005][2];
	bool empty(){return hd==tl;}
	int front(){return a[hd+1][0];}
	int front1(){return a[hd+1][1];}
	void pop(){hd++,hd=(hd==1000000?0:hd);}
	void push(int x,int y){a[++tl][0]=x,a[tl][1]=y,tl=(tl==1000000?0:tl);}
}q;
int main()
{
	freopen("input.txt","r",stdin); 
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]),a[i]++;
		for(int j=1;j<=a[i];j++) dis[i][j]=1e9;
	}
	scanf("%d%d%d%d",&x,&y,&xx,&yy);
	q.push(x,y);
	dis[x][y]=0;
	int x2,y2,y3;
	while(!q.empty())
	{
		x2=q.front();
		y2=q.front1();
		q.pop();
		if(y2!=a[x2])
		{
			if(dis[x2][y2+1]>dis[x2][y2]+1)
			{
				
				dis[x2][y2+1]=dis[x2][y2]+1;
				q.push(x2,y2+1);
			}
		}
		if(y2>1)
		{
		
			if(dis[x2][y2-1]>dis[x2][y2]+1)
			{
				dis[x2][y2-1]=dis[x2][y2]+1;
				q.push(x2,y2-1);
			}
		}
		if(x2>1)
		{
		
			y3=min(y2,a[x2-1]);
			if(dis[x2-1][y3]>dis[x2][y2]+1)
			{
				dis[x2-1][y3]=dis[x2][y2]+1;
				q.push(x2-1,y3);
			}
		}
		if(x2!=n)
		{
				
			y3=min(y2,a[x2+1]);
			if(dis[x2+1][y3]>dis[x2][y2]+1)
			{
				dis[x2+1][y3]=dis[x2][y2]+1;
				q.push(x2+1,y3);
			}
		}
	}
	printf("%d",dis[xx][yy]);
}

---

## 作者：nyC20 (赞：0)

# 思路
宽搜板子，看似简单实则很坑，坑点如下：

1. 记忆化，不然死循环加超时。

2. 不要用贪心思想只往终点方向搜，比如下图这个例子，很显然黄色路线的步数比绿色路线的次数少的多。

![](https://cdn.luogu.com.cn/upload/image_hosting/li984lpd.png)

3. 要加上文件读写，即 freopen 函数。

这样写最坏时间复杂度为 $O(n \times \max(a_i))$，不会超时。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long r1, c1, r2, c2, n, a[103], ans=1e8;
long long vis[103][100010];

struct node{
	long long x, y, step;
};
queue<node>q;

void bfs(){
	q.push({r1,c1,0});
	while(q.size()){
		node u=q.front();
		q.pop();
		
		if(u.x==r2&&u.y==c2){
			printf("%lld",u.step);
			return;
		}
		
		vis[u.x][u.y]=u.step;
		
		if(u.y>=2&&u.step+1<vis[u.x][u.y-1]){
			vis[u.x][u.y-1]=u.step+1;
			q.push({u.x,u.y-1,u.step+1});
		}
		if(u.y<a[u.x]&&u.step+1<vis[u.x][u.y+1]){
			vis[u.x][u.y+1]=u.step+1;
			q.push({u.x,u.y+1,u.step+1});
		}
		if(u.x!=n&&u.step+1<vis[u.x+1][min(u.y,a[u.x+1]+1)]){
			vis[u.x+1][min(u.y,a[u.x+1]+1)]=u.step+1;
			q.push({u.x+1,min(u.y,a[u.x+1]+1),u.step+1});
		}
		if(u.x!=1&&u.step+1<vis[u.x-1][min(u.y,a[u.x-1]+1)]){
			vis[u.x-1][min(u.y,a[u.x-1]+1)]=u.step+1;
			q.push({u.x-1,min(u.y,a[u.x-1]+1),u.step+1});
		}
	}
}

int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	scanf("%lld%lld%lld%lld",&r1,&c1,&r2,&c2);
	memset(vis,0x3f3f3f3f,sizeof vis);
	vis[r1][c1]=0;
	bfs();
	return 0;
}
```

---

## 作者：Paris_Bentley (赞：0)

加文件读写，加文件读写，加文件读写！！！

找了好久好久错误，最后实在没办法看各位大佬的提交记录，发现这个题目要文件读写，一直没找到错误原因。

题目是一个相对基础的 BFS 题目变形，需要注意的位置一共两点。

首先，每行如果有 $a_i$ 个字符，那么每行的合法位置就是 $a_i+1$ 个。

其次，如果上移或者下移到第 $a_i$ 行，而 $a_i$ 行的位置数不足，要让当前的位置坐标更新到 $a_i+1$。

具体描述见代码。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,a[105];
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0}; 
int r1,r2,c1,c2;
bool vis[105][100005];
struct Node
{
	int x,y,k;
};
queue<Node> q;//bfs核心部分——队列 
int main()
{
	freopen("input.txt","r",stdin);//记得文件读写，没有必错 
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
	q.push((Node){r1,c1,0});//起点入队 
	vis[r1][c1]=true;
	while (q.size()>0)
	{
		int nowx,nowy,nowk;
		nowx=q.front().x;
		nowy=q.front().y;
		nowk=q.front().k;
		if (nowx==r2&&nowy==c2)//找到终点，结束 
		{
			printf("%d\n",nowk);
			break;
		}
		q.pop();
		for (int i=0;i<4;i++)
		{
			int nx,ny;
			nx=nowx+dx[i];
			ny=nowy+dy[i];
			if (ny>a[nx]+1)//特殊处理，如果目标行的位置不足，跳到行末 
				ny=a[nx]+1;
			if (nx>=1&&nx<=n&&ny>=1&&ny<=a[nx]+1&&vis[nx][ny]==false)
			{
				q.push((Node){nx,ny,nowk+1});
				vis[nx][ny]=true;
			}
		}
	}
	return 0;
}
```


---

## 作者：CommandSR (赞：0)

## 题意简述

控制光标求出从一点移动到另外一点最小距离，光标上下左右移动，在边界时存在一些特殊情况。

---

## 基本思路

显然，这是一道地图和和常规矩阵地图有一定区别的 BFS。

传统 BFS 算法这里不进行过多讲解
，主要讲一讲这道题和传统矩阵上 BFS 的区别。

#### 每一行的长度不同

非常好处理，题目已经给出了每一行的长度，我们用 $a_i$ 表示第 $i$ 行的长度。在 BFS 时判定当前列数是否超过 $a_i$ 即可。

注意，题目给出的数值是当前行的**字符数量**，而非**列数**，真正的光标可以到达的位置可以是任意一个字符的两侧，故我们将输入的每一个 $a_i$ 加一。

#### 鼠标位置比上下行末位置大的处理

题目中有这样几句话：

> 如果鼠标的位置比上一行的行末位置大，如果按上的话，移到上一行的行末。

> 如果鼠标的位置比下一行的行末位置大，如果按下的话，移到下一行的行末。

我们只需要在每次改变行数时，判定当前位置是否大于当前行末位置即可，若当前位置大于当前行末位置，移到当前行末位置。

---

## AC Code

其余细节见注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[110];
int sx, sy, tx, ty;
bool vis[110][100010];
struct node
{
	int x, y, step ;
};
queue <node> q;
int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};
void bfs()
{
	// 常规BFS模板
	q.push((node){sx, sy, 0});
	vis[sx][sy] = 1;
	while (!q.empty())
	{
		node u = q.front(), v;
		q.pop();
		if (u.x == tx && u.y == ty)
		{
			// 走到终点一定是最佳答案，输出，结束。
			cout << u.step << '\n';
			return ;
		}
		for (int i = 0; i < 4; i++)
		{
			v.x = u.x + dx[i];
			v.y = u.y + dy[i];
			// 移出边界没有意义。
			if (v.x < 1) v.x = 1;
			if (v.x > n) v.x = n;
			if (v.y < 1) v.y = 1;
			// 若当前位置大于当前行末位置，移到当前行末位置。
			if (a[v.x] < v.y) v.y = a[v.x];
			if (vis[v.x][v.y]) continue ;
			vis[v.x][v.y] = 1;
			q.push((node){v.x, v.y, u.step + 1});
		}
	}
}
int main() 
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i] ++;
		// 光标可以到达的位置可以是任意一个字符的两侧，故列数+1
	}
	cin >> sx >> sy >> tx >> ty;
	bfs();
	return 0;
}
```

拒绝抄袭！

---

