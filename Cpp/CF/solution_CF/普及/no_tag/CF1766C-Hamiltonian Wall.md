# Hamiltonian Wall

## 题目描述

Sir Monocarp Hamilton is planning to paint his wall. The wall can be represented as a grid, consisting of $ 2 $ rows and $ m $ columns. Initially, the wall is completely white.

Monocarp wants to paint a black picture on the wall. In particular, he wants cell $ (i, j) $ (the $ j $ -th cell in the $ i $ -th row) to be colored black, if $ c_{i, j} = $ 'B', and to be left white, if $ c_{i, j} = $ 'W'. Additionally, he wants each column to have at least one black cell, so, for each $ j $ , the following constraint is satisfied: $ c_{1, j} $ , $ c_{2, j} $ or both of them will be equal to 'B'.

In order for the picture to turn out smooth, Monocarp wants to place down a paint brush in some cell $ (x_1, y_1) $ and move it along the path $ (x_1, y_1), (x_2, y_2), \dots, (x_k, y_k) $ so that:

- for each $ i $ , $ (x_i, y_i) $ and $ (x_{i+1}, y_{i+1}) $ share a common side;
- all black cells appear in the path exactly once;
- white cells don't appear in the path.

Determine if Monocarp can paint the wall.

## 说明/提示

In the first testcase, Monocarp can follow a path $ (2, 1) $ , $ (2, 2) $ , $ (1, 2) $ , $ (1, 3) $ with his brush. All black cells appear in the path exactly once, no white cells appear in the path.

In the second testcase, Monocarp can follow a path $ (1, 1) $ , $ (2, 1) $ .

In the third testcase:

- the path $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (1, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ doesn't suffice because a pair of cells $ (1, 3) $ and $ (2, 4) $ doesn't share a common side;
- the path $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (1, 3) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ doesn't suffice because cell $ (2, 3) $ is visited twice;
- the path $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ doesn't suffice because a black cell $ (1, 3) $ doesn't appear in the path;
- the path $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (2, 5) $ , $ (1, 5) $ , $ (1, 4) $ , $ (1, 3) $ doesn't suffice because a white cell $ (1, 4) $ appears in the path.

## 样例 #1

### 输入

```
6
3
WBB
BBW
1
B
B
5
BWBWB
BBBBB
2
BW
WB
5
BBBBW
BWBBB
6
BWBBWB
BBBBBB```

### 输出

```
YES
YES
NO
NO
NO
YES```

# 题解

## 作者：_dijkstra_ (赞：11)

并不算难。

## 思路

迷宫只有两列，所以很容易想到暴力模拟。

![](https://cdn.luogu.com.cn/upload/image_hosting/sner0ftt.png)

按照这样的规则，如果走完了最后一列，那么就成功了。

按照这样的规则，只需要分别尝试第一列的两个格子为出发点，只要有一个路径是成功的，就是 $\texttt{YES}$ 了。

## 代码

```cpp
int n;
string s[2];
bool chk0()
{
	bool now = 0;
	if (s[1][0] == 'B') now = 1;
	for (int i = 1; i < n; i++)
	{
		if (s[now][i] == 'W') return false;
		if (s[!now][i] == 'B') now = !now;
	}
	return true;
}
bool chk1()
{
	bool now = 1;
	if (s[0][0] == 'B') now = 0;
	for (int i = 1; i < n; i++)
	{
		if (s[now][i] == 'W') return false;
		if (s[!now][i] == 'B') now = !now;
	}
	return true;
}
bool solve()
{
	cin >> n >> s[0] >> s[1];
	if (s[0][0] == 'B') {if (chk0()) return true;}
	if (s[1][0] == 'B') {if (chk1()) return true;}
	return false;
}
```

---

## 作者：tZEROちゃん (赞：2)

设 $dp_{i,\ j}$ 表示从起点到第 $i$ 行，第 $j$ 列经过 $\tt B$ 数量的最大值。

只要存在一个 $dp_{i,\ j} = b$，其中 $b$ 是 $\tt B$ 的总数量，那就是 `YES`。

考虑转移，如果这个位置是 $\tt W$，那就无法转移，$dp_{i,\ j} = 0$。

在不是 $\tt W$ 的情况下，如果当前位置和上一列的同一行都是 $\tt B$，那就可以转移，$dp_{i,\ j} = dp_{i,\ j - 1} + 1$。如果这一列的两个都是 $\tt B$，那还可以通过上下转移得到，$dp_{i,\ j} = \max\{dp_{i,\ j}, dp_{3-i,\ j}\}$。

代码略。

---

## 作者：Patients (赞：2)

### [CF1766C Hamiltonian Wall](https://www.luogu.com.cn/problem/CF1766C)

------------

虽然是DP板题，但是本蒟蒻实在不想写DP，于是提供一个~~无脑~~的算法。

可以讲```B```都连起来，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/tga0dqoo.png)

很显然，它就变成了一个一笔画问题。

所以判断奇数点的个数即可。

然后，就连上面的样例都过不了了。

Why?

![](https://cdn.luogu.com.cn/upload/image_hosting/hku4xz0v.png)

很明显有 $ 4 $ 个奇数点啊。

但是这不代表思路有问题，需要改进一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/fwbq9qax.png)

对比这两张图片，可以发现，如果两个 $ 3 $ 连在一起，那么一定可以绕一圈，少走一条边。

然后就只有样例 $ 4 $ 过不了了。

肉眼可见，这不是不连通吗。

然后就完了。

### Code：

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 200005
int T;
int m;
int vis[3][maxn];
int p[3][maxn];
int a[3][maxn];
struct node{
    int x,y;
};
void bfs(int x,int y)
{
    queue<node> q;
    q.push((node){x,y});
    while(!q.empty())
    {
        node u=q.front();
        q.pop();
        if(u.x==1)
        {
            if(vis[1][u.y-1] && !p[1][u.y-1]) {p[1][u.y-1]=1;q.push((node){1,u.y-1});}
            if(vis[1][u.y+1] && !p[1][u.y+1]) {p[1][u.y+1]=1;q.push((node){1,u.y+1});}
            if(vis[2][u.y] && !p[2][u.y]) {p[2][u.y]=1;q.push((node){2,u.y});}
        }
        else 
        {
            if(vis[2][u.y-1] && !p[2][u.y-1]) {p[2][u.y-1]=1;q.push((node){2,u.y-1});}
            if(vis[2][u.y+1] && !p[2][u.y+1]) {p[2][u.y+1]=1;q.push((node){2,u.y+1});}
            if(vis[1][u.y] && !p[1][u.y]) {p[1][u.y]=1;q.push((node){1,u.y});}
        }
    }
}
void Solve()
{
    for(int i=1;i<=m;i++)
    {
        vis[1][i]=vis[2][i]=0;
        a[1][i]=a[2][i]=0;
        p[1][i]=p[2][i]=0;
    }
    // memset(vis,0,sizeof vis);
    // memset(a,0,sizeof a);
    // memset(p,0,sizeof p);
    int sum=0;
    cin>>m;
    char c;
    for(int i=1;i<=m;i++)
    {
        cin>>c;
        if(c=='B') vis[1][i]=1;
    }
    for(int i=1;i<=m;i++)
    {
        cin>>c;
        if(c=='B') vis[2][i]=1;
    }
    int num=0;
    for(int i=1;i<=m;i++) if(!p[1][i] && vis[1][i]) {num++;bfs(1,i);}
    for(int i=1;i<=m;i++) if(!p[2][i] && vis[2][i]) {num++;bfs(2,i);}
    if(num>1)
    {
        cout<<"NO\n";
        return ;
    }
    for(int j=1;j<=m;j++)
    {
        if(!vis[1][j]) continue ;
        a[1][j]=vis[1][j-1]+vis[1][j+1]+vis[2][j];
    }
    for(int j=1;j<=m;j++)
    {
        if(!vis[2][j]) continue ;
        a[2][j]=vis[2][j-1]+vis[2][j+1]+vis[1][j];
    }
    for(int j=1;j<=m;j++)
    {
        if(a[1][j]==3)
            if(a[1][j-1]==3) a[1][j]--,a[1][j-1]--;
            else if(a[1][j+1]==3) a[1][j]--,a[1][j+1]--;
            else if(a[2][j]==3) a[1][j]--,a[2][j]--;
    }
    for(int j=1;j<=m;j++)
    {
        if(a[2][j]==3)
            if(a[2][j-1]==3) a[2][j]--,a[2][j-1]--;
            else if(a[2][j+1]==3) a[2][j]--,a[2][j+1]--;
            else if(a[1][j]==3) a[2][j]--,a[1][j]--;
    }
    for(int j=1;j<=m;j++)
        if(a[1][j]%2==1) sum++;
    for(int j=1;j<=m;j++)
        if(a[2][j]%2==1) sum++;
    if(sum==0 || sum==2) cout<<"YES\n";
    else cout<<"NO\n";
}
signed main()
{
#ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>T;
    while(T--) Solve();
	return 0;
}
```

ps：不要用memset！

---

## 作者：wawatime1 (赞：1)

### 题目分析
本题可以使用动态规划来解决，关键思路是用 $ dp_{ij} $ 表示到第 $ j $ 列第 $ i $ 行时，能够覆盖的连续的 $ B $ 的最大数量。

- 初始化时，如果第一列的某一行是 $B$，则该行对应的 $dp$ 值为 $1$。

- 状态转移时，如果当前列的某一行是 $B$ 且上一列同一行也是 $B$，则可以从左边转移过来，$dp$ 值加 $1$。

- 如果当前列两行都是 $B$，则可以上下走，更新 $dp$ 值为当前值和另一行 $dp$ 值加 $1$ 的较大值。
最后判断是否存在某一行的 $dp$ 值等于总的 $B$ 的数量，如果是，则输出 YES，否则输出 NO。

---

## 作者：Ryouko_miku (赞：1)

**题意**：给你一面 $2$ 行 $m$ 列白墙，给你一把粉刷和黑色油漆，问你能不能一笔画成样例所给的那面墙。

------------

###  解题思路：
解题方法很简单，因为题目确保了两行中必有一行为黑色，那我只需要分别以 $(1,1)$ 和 $(2,1)$ 为起点，进行两次 **dfs** 检查是否能一笔画成即可，只要有其中一次能够一笔画成，则输出 YES，否则输出 NO。

因为只有两行，所以这个时间复杂度是足够的。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
const int INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0xc0c0c0c0c0c0c0c0;
const int N = 2e5 + 5;
char m[5][N], vis[5][N];
int n;

bool dfs(int x, int y, int cnt) 
{
	vis[x][y] = 1;
	bool tag = false;
	if (!cnt) {
		return true; //若所有黑色格子已涂完，则返回true
	}
	if (x + 1 <= 2 && m[x + 1][y] == 'B' && !vis[x + 1][y]) {
		tag = dfs(x + 1, y, cnt - 1);
	}
	else if (x - 1 >= 1 && m[x - 1][y] == 'B' && !vis[x - 1][y]) {
		tag = dfs(x - 1, y, cnt - 1);
	}
	else if (y + 1 <= n && m[x][y + 1] == 'B' && !vis[x][y + 1]) {
		tag = dfs(x, y + 1, cnt - 1);
	}
	else if (y - 1 >= 1 && m[x][y - 1] == 'B' && !vis[x][y - 1]) {
		tag = dfs(x, y - 1, cnt - 1);
	}
	return tag; //否则返回false
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		int cnt = 0;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> m[i][j];
				vis[i][j] = 0;
				if (m[i][j] == 'B') {
					cnt++; //统计黑色的个数
				}
			}
		}
		bool tag = false;
		if (m[1][1] == 'B') {
			tag = dfs(1, 1, cnt - 1); //若(1,1)为黑色，则先以(1,1)作为起点，跑一次dfs
		}
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= n; j++) {
				vis[i][j] = 0; //恢复第一次dfs改变过的vis数组
			}
		}
		if (!tag && m[2][1] == 'B') { //若第一次dfs，就能证明一笔能画成，则无需第二次dfs
			tag = dfs(2, 1, cnt - 1); //若(2,1)为黑色，再以(2,1)作为起点，再跑一次dfs
		}
		if (tag) { //两次dfs中，只要有一次能够一笔画成，则符合题意，输出YES
			cout << "YES\n";
		}
		else {    //否则，输出NO
			cout << "NO\n";
		}
	}
	cout << '\n';
	return 0;
}
```

---

