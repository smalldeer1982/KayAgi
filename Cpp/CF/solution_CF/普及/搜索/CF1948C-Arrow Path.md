# Arrow Path

## 题目描述

有一个 $2$ 行 $n$ 列的网格，每个格子上有一个向左或向右的箭头（即 `<` 或 `>`）。

现在你从 $(1, 1)$ 开始移动，并遵循以下的移动方式：

- 首先，选择一个移动方向走 $1$ 格，可以是上、下、左、右任意方向，但你需要保证不会走出网格；
- 走完一步后，如果当前所在格为 `<`，则向左走 $1$ 格，否则向右走 $1$​ 格。注意，你也需要保证这一步不会走出网格。

请回答你能否到达 $(2, n)$。

## 说明/提示

对于 $100 \%$ 的数据，保证 $1 \leq t \leq 10^4, 2 \leq n \leq 2 \times 10^5$。

**保证 $n$ 是偶数，没有箭头指向网格外，$n$ 的总和不超过 $2 \times 10^5$。**

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
4
4
&gt;&gt;&lt;&lt;
&gt;&gt;&gt;&lt;
2
&gt;&lt;
&gt;&lt;
4
&gt;&gt;&gt;&lt;
&gt;&gt;&lt;&lt;
6
&gt;&gt;&lt;&lt;&gt;&lt;
&gt;&lt;&gt;&gt;&gt;&lt;```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：kczw (赞：17)

# 题意
给定大小 $2\times n$ 的图，图由 `<` 及 `>` 两种箭头组成。

你从 $(1,1)$ 开始，每次可以按以下方式操作：
- 在不出图前提下往上下左右任意方向移动一步。
- 移动后据当前位置箭头指向再次移动。

保证箭头不会指向图外。

问能否抵达 $(2,n)$。
# 思路
分析以下两种情况：
```
/ > /      / < /
```
起、终点符号无意义，用 `/` 代替。

- 第一种情况，你移动一步，然后据箭头方向继续向前。
- 第二种情况，你移动一步，然后据箭头方向回到原点。

所以判断能否到达 $(2,n)$ 的关键就是判断是上下两条线路否有同时出现的第二种情况。

上文浅提了所谓的**起、终点无意义**，可能需要解释一下，先申明，起、终点并非 $(1,1),(2,n)$，而是对于**每次移动**的起点和终点。

你从某个点开始移动，于是此位置的箭头并不会起到作用，而移动后据其位置的箭头再次移动到终点，此时终点上箭头也并无作用。

根据以上规律，可知图中 `#` 的位置的箭头都是无意义的，此处用于 `/` 代替 `<` 及 `>`。
```
# / # / # / #
/ # / # / # /
```
很好理解，每次你移动的曼哈段距离都是偶数，那么对于曼哈段距离为偶数的点，必然是你的某个起点或终点又或者你根本无法到达的点，于是有如上图。

所以我们只要判断在有意义的点集中是否有连续的 `<` 即可（图示如下）。
```
# / # < #    # < # / #
/ # < # /    / # < # / 
```
如若有，则不可抵达 $(2,n)$，否则可以。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n;
char s[2][N];
main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%s%s",&n,s[0]+1,s[1]+1);
		bool flag=0;
		for(int i=2;i<=n;i+=2){
			if(s[0][i]=='<'&&(s[1][i-1]=='<'||(i+1<n&&s[1][i+1]=='<'))){
				flag=1;
				break;
			}
		}
		flag?puts("No"):puts("Yes");
	}
}
```

---

## 作者：littlebug (赞：7)

## Description

给定一个 $2\times n$ 的网格 $p$，$p_{i,j}$ 的值为 `>` 或 `<`，分别表示向右和向左。

你最开始位于 $(1,1)$，你可以进行如下操作任意次：

1. 第一步，你需要向左、向右、向下或向上移动一格（但不能离开网格）；
2. 第二步，你需要**立即**沿着当前格子中的箭头的方向移动一格。

求你是否可以到达 $(2,n)$。

## Solution

看到网格图，并且是求**是否**能到达，可以想到，从初始位置 $(1,1)$ 开始搜索，依次搜索直到到达点 $(2,n)$ 或确定无解。

具体地，开一个 `vis` 数组，表示哪个点访问过。在搜索过程中，只搜没有搜过的点，如果到达点 $(2,n)$ 就立即退出，否则如果能搜到的点都搜过了，搜索也会自动退出。

还有一点，就是不能直接搜索点 $(1,1)$，而是搜索点 $(1,2)$ 和点 $(2,1)$，因为在 `dfs` 函数中，先进行的是上一次移动的第 $2$ 步，如果从 $(1,1)$ 开始则会多移动一步，不过如果你将一次移动的两步放在一起进行，就没有这个问题了。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#define il inline
using namespace std;
const int MAXN=2e5+5;
int n;
bitset <MAXN> p[2+5]; //>:1 <:0 
bitset <MAXN> vis[2+5];
bool ok;
il void dfs(int x,int y)
{
	if(p[x][y]) //进行第2步移动 
		++y;
	else
		--y;
	if(x==2 && y==n) //到达终点则立即退出 
	{
		ok=1; //标记到达终点
		return;
	}
	if(x<1 || x>2 || y<1 || y>n) //判断是否越界  
		return;
	if(vis[x][y]) //判断是否访问过 
		return;
	vis[x][y]=1; //标记访问过 
	//向上下左右四个方向搜索 
	dfs(x+1,y);
	if(ok) return; //如果到达终点则立即退出 
	dfs(x-1,y);
	if(ok) return;
	dfs(x,y+1);
	if(ok) return;
	dfs(x,y-1);
	return;
}
il void solve()
{
	cin>>n;
	char c;
	for(int i=1;i<=2;++i)
	{
		p[i]&=0;
		vis[i]&=0; //多测要清空！ 
		for(int j=1;j<=n;++j)
		{
			cin>>c;
			p[i][j]=(c=='>');
		}
	}
	ok=0;
	dfs(1,2); //直接搜索点(1,2)和点(2,1) 
	dfs(2,1);
	if(ok)
		puts("YES");
	else
		puts("NO");
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：hmzclimc (赞：3)

## 思路
搜索。

部分思路来自于一位大佬的[代码](https://codeforces.com/contest/1948/submission/251528546)（已经征得同意），在这里表示感谢。

只需要按照题目所给的要求进行 dfs 就行。每次到达一个点就把它标记为访问过（可以到达）。最终判断一下终点是否访问过就好。

详情请看代码：
## 主要代码
```cpp
const int maxn=200005;
int n;string s[3];
bool vis[3][maxn];
void dfs(int x,int y){
    if(s[x][y]=='<'){ // 根据地图移动
        y--;
    }else{
        y++;
    }
    if(!(1<=x&&x<=2&&1<=y&&y<=n)){// 超出坐标限制就返回
        return ;
    }
    if(vis[x][y]){ //访问过的话就可以返回了
        return ;
    }
    vis[x][y]=1; // 标记为访问过
    dfs(3-x,y);// 注意到 3-1 = 2 , 3-2 = 1 ,这样可以简单的实现行之间的移动
    if(y+1<=n){ // 可以向右走
        dfs(x,y+1);
    }
    if(y-1>=1){ // 可以向左走
        dfs(x,y-1);
    }
}
void solve(){
    memset(vis,0,sizeof(vis));// 清空 vis 数组
    n=read();
    cin>>s[1]>>s[2];// 读入
    s[2]=" "+s[2],s[1]=" "+s[1];
    dfs(1,2),dfs(2,1); // 从一开始可以到达的两个坐标出发 dfs
    print(((vis[2][n])?("YES"):("NO")),'\n'); // 输出
}
```

感谢阅读，有问题请指出，谢谢。

---

## 作者：Super_Builder (赞：1)

简单的广搜变形题。

## 思路

如果不会广搜，请自行学习。

这题就是在普通的广搜基础上，加上了一个箭头。

简单讲下搜索过程。  
由于可以朝**任何方向**走，所以先从**当前点开始搜索**，向四面拓展新节点，并判掉越界情况。  
拓展出来点之后，根据箭头方向，向左或右移动。移动后判断**是否搜到过**，搜到则无需重复搜。  
然后将拓展出来的点加入队列，继续搜索。  
最后判断**是否搜到过** $(2,n)$ 点就可以了。

注意，题目保证了，箭头不会指向网格外，所以在根据箭头移动时，不需要判断越界。

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
bool vis[3][200005];
char c[3][200005];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
void bfs(){
	memset(vis,0,sizeof vis);
	queue<pair<int,int> >q;
	q.push({1,1});
	vis[1][1]=1;
	while(q.size()){
		auto ft=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int nx=ft.first+dx[i],ny=ft.second+dy[i];
			if(nx<1||nx>2||ny<1||ny>n)continue;
			if(c[nx][ny]=='<')ny--;
			else ny++;
			if(vis[nx][ny])continue;
			vis[nx][ny]=1;
			q.push({nx,ny});
		}
	}
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=2;i++){
			for(int j=1;j<=n;j++){
				cin>>c[i][j];
			}
		}
		bfs();
		if(vis[2][n])puts("Yes");
		else puts("No");
	} 
	return 0;
}
```

## AC CODE

---

## 作者：Drind (赞：1)

### 题目解析

我们预处理每个格子向四个方向走完一步会到哪儿，然后做一遍 bfs 处理起点和终点的连通性即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int inf=0x3f3f3f3f;

int a[3][N];

struct node{
	int to,nxt;
}edge[N*8]; int head[N*2],cnt;
void add(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

int vis[N*2];
bool bfs(int s,int t){
	queue<int>q;
	q.push(s); vis[s]=1;
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to; if(vis[v]) continue;
			vis[v]=1; q.push(v);
			if(v==t) return true;
		}
	}
	return false;
}

inline void fake_main(){
	int n; cin>>n;
	memset(head,0,(2*n+3)*sizeof head[0]);
	memset(vis,0,(2*n+3)*sizeof vis[0]); cnt=0;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=n;j++){
			char ch; cin>>ch;
			if(ch=='>') a[i][j]=1;
			else a[i][j]=0;
		}
	}
	for(int i=1;i<=2;i++){
		for(int j=1;j<=n;j++){
			for(int r=0;r<4;r++){
				int tx=i+dx[r];
				int ty=j+dy[r];
				if(tx>2||tx<1||ty>n||ty<1) continue;
				if(a[tx][ty]==1) ty++;
				else ty--;
				add((i-1)*n+j,(tx-1)*n+ty);
			}
		}
	}
	if(bfs(1,n*2)) cout<<"YES\n";
	else cout<<"NO\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：xxxxxxxb (赞：0)

题目大意：

有两行 $n$ 列的方格，一开始位于 $(1,1)$ 处，每次操作可以先向任意方向走一步，然后再按走一步之后的格子上的方向再走一步。问能否到达 $(2,n)$。

相当于变形的全一最短路，用广搜。每次走两步，把经过的格子和最后到达的格子打上标记，把最后到达的格子再入队就行。最后判断 $(2,n)$ 有没有标记。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int read() {
    int res = 0, f = 1;
    char c = getchar();
    while(!isdigit(c)) {
        if(c == '-') f = -1;
        c = getchar();
    }
    while(isdigit(c)) {
        res = (res << 1) + (res << 3) + (c ^ 48);
        c = getchar();
    }
    return res * f;
}

int t;
int n;
char str[3][(int)2e5 + 7];
int dx[4] = {1,-1,0,0}, dy[4] = {0, 0, 1, -1};
void sol() {
    n = read();
    scanf("%s", str[1] + 1);
    scanf("%s", str[2] + 1);
    bitset<(int)2e5 + 7> vis[3];
    queue<pair<int, int>> q;
    q.push({1,1});
    vis[1][1] = 1;
    while(!q.empty()) {
        pair<int, int> u = q.front();
        q.pop();
        int x = u.first, y = u.second;
        for(int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx <= 0 || ny <= 0 || nx > 2 || ny > n) {
                continue;
            }
            if(vis[nx][ny]) {
                continue;
            }
            vis[nx][ny] = 1;
            if(str[nx][ny] == '<') {
                ny--;
            } else {
                ny++;
            }
            if(vis[nx][ny]) {
                continue;
            }
            vis[nx][ny] = 1;
            q.push({nx, ny});
            if(vis[2][n]) {
                printf("YES\n");
                return;
            }
        }
    }
    printf("NO\n");
}
int main() {
    t = read();
    while(t--) {
        sol();
    }
}
```

---

## 作者：GenesisCrystal (赞：0)

~~大暴力~~

## Soulution

这道题需要一个带剪枝的暴力搜索。

令 $f_{i,j,k}$ 表示在第 $i$ 列，第 $j$ 行，如果 $k$ 为 $0$ 那么当前为 `<`，如果 $k$ 为 $1$ 那么当前为 `>`，如果 $k$ 为 $2$ 那么当前为为随意走。

如果搜到的状态搜到过了，就不用再搜一遍了。

然后按题目说的模拟就行了。

## Code
```cpp
/// @author WUYIXUAN_
// Problem: C. Arrow Path
// Contest: Codeforces - Educational Codeforces Round 163 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1948/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms

// python
// rp = 0
// while TURE:
//     rp = rp + 1
#include <cstring>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1, kD[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool f[kMaxN][2][3], cn;
int t, n;
char c[kMaxN][2];

void Dfs(int x, int y, bool st, char p) {
	if (f[x][y][(st == 1 ? 2 : (p == '<' ? 0 : 1))]) {
		return;
	}
	f[x][y][(st == 1 ? 2 : (p == '<' ? 0 : 1))] = 1;
	if (x == n && y == 1) {
		cn = 1;
	}
	if (cn) {
		return;
	}
	if (st) {
		for (int i = 0; i < 4; i++) {
			int nx = x + kD[i][0], ny = y + kD[i][1];
			if (ny < 0 || ny > 1 || nx < 1 || nx > n) {
				continue;
			}
			Dfs(nx, ny, 0, c[nx][ny]);
		}
	} else {
		Dfs(x + (p == '<' ? -1 : 1), y, 1, c[x + (p == '<' ? -1 : 1)][y]);
	}
}

int main() {
	for (cin >> t; t; t--) {
		memset(f, 0, sizeof(f));
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> c[i][0];
		}
		for (int i = 1; i <= n; i++) {
			cin >> c[i][1];
		}
		Dfs(1, 0, 1, c[1][0]);
		cout << (cn ? "YES\n" : "NO\n");
		cn = 0;
  }
	return 0;
}
```

---

