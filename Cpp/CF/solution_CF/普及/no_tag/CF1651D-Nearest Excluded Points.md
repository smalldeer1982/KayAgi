# Nearest Excluded Points

## 题目描述

You are given $ n $ distinct points on a plane. The coordinates of the $ i $ -th point are $ (x_i, y_i) $ .

For each point $ i $ , find the nearest (in terms of Manhattan distance) point with integer coordinates that is not among the given $ n $ points. If there are multiple such points — you can choose any of them.

The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ .

## 样例 #1

### 输入

```
6
2 2
1 2
2 1
3 2
2 3
5 5```

### 输出

```
1 1
1 1
2 0
3 1
2 4
5 4```

## 样例 #2

### 输入

```
8
4 4
2 4
2 2
2 3
1 4
4 2
1 3
3 3```

### 输出

```
4 3
2 5
2 1
2 5
1 5
4 1
1 2
3 2```

# 题解

## 作者：XL4453 (赞：7)

### $\text{Difficulty : 1900}$
---
### 解题思路：

经典赛后过题。

可以发现，所有可能的结果都是某一个已知的点周边的点。

所以直接将所有在已知点周围的空点记录下来，直接 $\text{BFS}$，遇到未被更新且已知点就加入队列，否则一概不加入。

空间不够可以用 $\text{map}$，来存储。

总复杂度 $O(n)$。

---
### 代码：
```cpp
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
int n,x[200005],y[200005],dx[5]={0,0,-1,1},dy[5]={1,-1,0,0},nx,ny;
map <pair<int,int> ,int> f;
map <pair<int,int> ,pair<int,int> > ans;
queue <pair<int,int> > q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
		f[make_pair(x[i],y[i])]=-1;
	}
	for(int i=1;i<=n;i++){
		for(int l=0;l<=3;l++)
		if(f[make_pair(x[i]+dx[l],y[i]+dy[l])]!=-1)
		q.push(make_pair(x[i]+dx[l],y[i]+dy[l])),
		ans[make_pair(x[i]+dx[l],y[i]+dy[l])]=make_pair(x[i]+dx[l],y[i]+dy[l]);
	}
	while(!q.empty()){
		nx=q.front().first;
		ny=q.front().second;
		for(int i=0;i<=3;i++){
			if(f[make_pair(nx+dx[i],ny+dy[i])]==-1){
				f[make_pair(nx+dx[i],ny+dy[i])]=1;
				ans[make_pair(nx+dx[i],ny+dy[i])]=ans[make_pair(nx,ny)];
				q.push(make_pair(nx+dx[i],ny+dy[i]));
			}
		}
		q.pop();
	}
	for(int i=1;i<=n;i++){
		printf("%d %d\n",ans[make_pair(x[i],y[i])].first,ans[make_pair(x[i],y[i])].second);
	}
	return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：4)

比较简单的喵喵题。

## 题目简述

- 有 $n$ 个整点被染上了红色。
- 对于每一个点，输出一个非红色的整点使其曼哈顿距离最小。
- $n\leq2\times 10^5$

## 解题思路

考虑 BFS。

一开始先让所有边缘上的点入队。

在 BFS 的过程中一个点 $A$ 转移到另一个点 $B$ 的过程中，$A$ 选择的非红色点，$B$ 肯定也能选这个非红色点。

至于存图可以用 map 套 map。

## 参考代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
using namespace std;
#define ll long long
const int MAXN=2e5+5;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int n;
int x[MAXN],y[MAXN];
int sx[MAXN],sy[MAXN];
bool vis[MAXN];
map<int,map<int,int> > M;
queue<int> q;
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		M[x[i]][y[i]]=i;
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<4;j++)
			if(!M[x[i]+dx[j]][y[i]+dy[j]]){
				sx[i]=x[i]+dx[j];
				sy[i]=y[i]+dy[j];
				vis[i]=true;
				q.push(i);
			}
	while(!q.empty()){
		int p=q.front();
		q.pop();
		for(int i=0;i<4;i++)
			if(M[x[p]+dx[i]][y[p]+dy[i]]){
				int k=M[x[p]+dx[i]][y[p]+dy[i]];
				if(!vis[k]){
					sx[k]=sx[p];
					sy[k]=sy[p];
					vis[k]=true;
					q.push(k);
				}
			}
	}
	for(int i=1;i<=n;i++)
		cout<<sx[i]<<" "<<sy[i]<<endl;
	return;
}
int main(){
		solve();
} 
```


---

## 作者：songge888 (赞：2)

### 题意

给定 $n$ 个点 $(x,y)$，求每个点周围距离与这个点的哈夫曼距离最小的点（不包括这 $n$ 个点）。

### 思路

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/l5g4tpyz.png)

对于每个询问中的点，可以分成两种情况：

- 周围有不是询问中的点

以点 $E$ 为例，在它的周围有 $(1,3)$，$(2,4)$，$(3,3)$，将点 $E$ 的答案设为其中的一个点即可，即：
若一个点周围有不是询问中的点，这个点的答案为它周围其中一个不是询问中的点。

- 周围都是询问中的点

以点 $A$ 为例，它周围无非询问的点，于是向外搜索，搜到一个点（例如点 $E$ ），搜出来的点如果已经有答案了，则原本的点的答案就是搜出来的点的答案，即：
若一个点周围都是询问中的点，这个点的答案为它周围其中一个的点的答案。

知道了思路，接下来想想可以怎么做，对于这 $n$ 个点，可以先考虑第一种情况，开一个 `vis` 数组，如果这个点周围有空白的点，直接在这个点上打上标记，再把这个点丢进一个队列中。
接下来考虑第二种情况，遍历队列中的每一个点，如果队列中的点周围有要询问的点并且那个点没有被标记，则那个点的答案就是当前队列里这个点的答案，更新完答案后打上标记，将刚刚标记的点丢进队列中，然后一直循环这个操作，用 **BFS** 就可以了。

注意数据范围 $n \le 2 \times 10^5$，所以存图时要用 `map`。

时间复杂度：$O(n\log n)$

### Code

```c++
#include<bits/stdc++.h>
#define bug cout<<"!!!!!!!!_bug_!!!!!!!!!"<<'\n';
#define int long long
using namespace std;
struct node{
	int x,y;
}a[200010],ans[200010];
map<pair<int,int>,int> mp;
queue<int> q;
int n;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int vis[200010];
void bfs(){
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int xx=a[now].x+dx[i];
			int yy=a[now].y+dy[i];
			if(mp[{xx,yy}]&&!vis[mp[{xx,yy}]]){
				ans[mp[{xx,yy}]]=ans[now];
				vis[mp[{xx,yy}]]++;
				q.push(mp[{xx,yy}]);
			}
		}
	}
    return ;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		mp[{a[i].x,a[i].y}]=i;
	}
	for(int i=1;i<=n;i++){//第一种情况
		for(int j=0;j<4;j++){
			int xx=a[i].x+dx[j],yy=a[i].y+dy[j];
			if(!mp[{xx,yy}]){
				ans[i]={xx,yy};
				vis[i]++;
				q.push(i);
				break;
			}
		} 
	}
	bfs();//第二种情况
	for(int i=1;i<=n;i++){
		cout<<ans[i].x<<' '<<ans[i].y<<'\n';
	}
	return 0;
}

```

[提交记录](https://codeforces.com/contest/1651/submission/292470852)

---

## 作者：Graph_Theory (赞：2)

### 0.题意
给出 $n$ 个染色点，求离这 $n$ 个点最近的非染色点的坐标。

### 1.思路和代码
#### 1.1 枚举曼哈顿距离为 $1$ 的四周
一个点最小的曼哈顿距离一定是这个点的上下左右（即为 $1$）此时我们先寻找这 $n$ 个点四周是否存在非染色点。

如果存在，那么我们就将其设为答案，并加入队列。

这里加入队列的意义在于排除其他没有用的非染色点，毕竟那些不存在曼哈顿距离为 $1$ 的非染色点的染色点，他们一定和围住他四周的存在曼哈顿距离为 $1$ 的点共用一个非染色点。

此时，枚举这些共用的非染色点就可以推出这些四周都有染色点的染色点的最短曼哈顿距离的非染色点。

如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/gmd45eu1.png)

代码：
```cpp
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=4;j++)//枚举4个方向
	{
		int nx=x[i]+dx[j],ny=y[i]+dy[j];//新坐标
		if(!mp[nx][ny]) //这里是第一次访问,且只访问一次，所以不需要判断是否访问过
		{               
			ans[i].x=nx;
			ans[i].y=ny;//记录答案
			vis[i]=true;//已有答案
			q.push(i);
			break;
		}
	}
}
```
#### 1.2 对于那些四周都有染色点的染色点，通过枚举队列中的非染色点得出结果

因为求最短距离，所以这里使用 BFS 搜索

代码：
```cpp
while(!q.empty())
{
	int id=q.front();
	q.pop();
	for(int i=1;i<=4;i++)
	{
		int xx=x[id]+dx[i];//计算新坐标
		int yy=y[id]+dy[i];
		if(mp[xx][yy]>0)
		{
			int num=mp[xx][yy];//mp中存了涂色点是否存在，也存了涂色点的编号
			if(vis[num]==false)//如果这是个染色点且还没有答案
			{
				ans[num].x=ans[id].x;
				ans[num].y=ans[id].y;//记录答案;
				vis[num]=true;
				q.push(num);//加入队列
			}
		}
	}
}

```


---

## 作者：Genius_Star (赞：2)

### 题意：

平面上有 $n$ 个点，请你找出距离每个点曼哈顿距离最近的且不是这 $n$ 个点的点。

### 思路：

对于两个点 $(x_1,y_1),(x_2,y_2)$ 的曼哈顿距离为 $|x_1-x_2|+|y_1-y_2|$。

也就是说，对于一个点，与其曼哈顿距离最近的点是这个点的四邻域，即上下左右。

画一下图，我们可以发现，一个点的答案肯定在一个点周边的点，所以我们可以先在每个点的四邻域寻找满足条件的点，如果有满足条件的点，就记录下来。

然后从这 $n$ 个点中找到了满足条件的点进行 BFS，当遇到这 $n$ 个点中的某个点时，离他最近的点就是离走到它的点的最近的点。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n;
vector<pair<ll,ll>> a; 
map<pair<ll,ll>,bool> f;
map<pair<ll,ll>,pair<ll,ll>> ans;
queue<pair<ll,ll>> q;
ll dx[]={0,0,-1,1};
ll dy[]={-1,1,0,0};
void BFS(){
	while(!q.empty()){
		auto t=q.front();
		ll x=t.first,y=t.second;
		q.pop();
		for(int i=0;i<4;i++){
			ll zx=x+dx[i],zy=y+dy[i];
			if(!f[{zx,zy}]||ans.count({zx,zy}))
			  continue;
			ans[{zx,zy}]=ans[{x,y}];
			q.push({zx,zy});
		}
	}
}
int main(){
	n=read();
	for(int x,y,zx,zy,i=1;i<=n;i++){
		x=read(),y=read();
		a.push_back({x,y});
		f[{x,y}]=1;
	}
	for(auto i:a){
		ll x=i.first,y=i.second;
		for(int j=0;j<4;j++){
			ll zx=x+dx[j],zy=y+dy[j];
			if(f[{zx,zy}])
			  continue;
			ans[{x,y}]={zx,zy};
			q.push({x,y});
			break;
		}
	}
	BFS();
    for (auto i:a){
        auto t=ans[i];
        write(t.first);
        putchar(' ');
        write(t.second);
        putchar('\n');
    }
	return 0;
}
```


---

## 作者：huayucaiji (赞：1)

## 解题思路

我们定义一个点的“距离”为它和其对应答案的**曼哈顿距离**

我们可以非常轻松的知道哪些点的距离是 $1$。我们以这些点作为起点 BFS。

如果一个点 $x$ 距离为 $1$，它的四周有一个点 $y$ 距离大于 $1$ 的话，那么 $y$ 的距离就为 $2$。这是显然的，只要 $y$ 匹配这个与 $x$ 曼哈顿距离为 $1$ 的点即可。

所以同理，如果一个点 $x$ 距离为 $k$，它的四周有一个点 $y$ 距离大于 $k$ 的话，那么 $y$ 的距离就为 $k+1$。

也就是说我们可以快乐地 BFS 了。

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
char read_char() {
	char ch=getchar();
	while(!isalpha(ch)) {
		ch=getchar();
	}
	return ch;
}

const int MAXN=2e5+10;
const int dx[]={0,-1,0,1};
const int dy[]={1,0,-1,0};

int n;
bool vis[MAXN];
queue<int> q;
struct point {
	int x,y;
}p[MAXN],ans[MAXN];
long long node(int x,int y) {
	return 1ll*x*MAXN+y;
}
map<long long,int> mp;

void bfs() {
	while(!q.empty()) {
		int i=q.front();
		q.pop();
		for(int k=0;k<4;k++) {
			int nx=p[i].x+dx[k];
			int ny=p[i].y+dy[k];
			
			int idx=mp[node(nx,ny)];
			if(!idx) {
				mp.erase(node(nx,ny));
			}
			else if(!vis[idx]) {
				ans[idx]=ans[i];
				vis[idx]=1;
				q.push(idx);
			} 
		}
	}
}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		p[i].x=read();
		p[i].y=read();
		mp[node(p[i].x,p[i].y)]=i;
	}
	
	for(int i=1;i<=n;i++) {
		for(int k=0;k<4;k++) {
			int nx=p[i].x+dx[k];
			int ny=p[i].y+dy[k];
			
			if(mp[node(nx,ny)]==0) {
				mp.erase(node(nx,ny));
				ans[i].x=nx;ans[i].y=ny;
				vis[i]=1; 
				q.push(i);
			} 
		}
	}
	bfs();
	
	for(int i=1;i<=n;i++) {
		printf("%d %d\n",ans[i].x,ans[i].y);
	}
	return 0;
}

```



---

