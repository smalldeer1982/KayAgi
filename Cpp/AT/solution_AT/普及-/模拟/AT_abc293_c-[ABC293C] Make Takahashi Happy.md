# [ABC293C] Make Takahashi Happy

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc293/tasks/abc293_c

$ H $ 行 $ W $ 列のマス目があります。 $ 1\ \leq\ i\ \leq\ H $ かつ $ 1\ \leq\ j\ \leq\ W $ を満たす $ 2 $ つの整数 $ i,\ j $ について、 上から $ i $ 行目、左から $ j $ 列目のマス（以下、$ (i,\ j) $ と表す）には、整数 $ A_{i,\ j} $ が書かれています。

いま、高橋君は $ (1,\ 1) $ にいます。 これから高橋君は「いまいるマスから右または下に隣接するマスに移動する」ことを繰り返して、$ (H,\ W) $ まで移動します。 ただし、その過程でマス目の外部に移動することは出来ません。

その結果、高橋君が通ったマス（始点 $ (1,\ 1) $ と終点 $ (H,\ W) $ を含む）に書かれた整数がすべて異なるとき、高橋君は嬉しくなります。 高橋君の移動経路として考えられるもののうち、高橋君が嬉しくなるものの個数を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 10 $
- $ 1\ \leq\ A_{i,\ j}\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

高橋君の移動経路として考えられるものは下記の $ 6 $ 通りです。 - $ (1,\ 1)\ \rightarrow\ (1,\ 2)\ \rightarrow\ (1,\ 3)\ \rightarrow\ (2,\ 3)\ \rightarrow\ (3,\ 3) $：通ったマスに書かれた整数は $ 3,\ 2,\ 2,\ 3,\ 4 $ であり、高橋君は嬉しく\*\*なりません\*\*。 - $ (1,\ 1)\ \rightarrow\ (1,\ 2)\ \rightarrow\ (2,\ 2)\ \rightarrow\ (2,\ 3)\ \rightarrow\ (3,\ 3) $：通ったマスに書かれた整数は $ 3,\ 2,\ 1,\ 3,\ 4 $ であり、高橋君は嬉しく\*\*なりません\*\*。 - $ (1,\ 1)\ \rightarrow\ (1,\ 2)\ \rightarrow\ (2,\ 2)\ \rightarrow\ (3,\ 2)\ \rightarrow\ (3,\ 3) $：通ったマスに書かれた整数は $ 3,\ 2,\ 1,\ 5,\ 4 $ であり、高橋君は嬉しく\*\*なります\*\*。 - $ (1,\ 1)\ \rightarrow\ (2,\ 1)\ \rightarrow\ (2,\ 2)\ \rightarrow\ (2,\ 3)\ \rightarrow\ (3,\ 3) $：通ったマスに書かれた整数は $ 3,\ 2,\ 1,\ 3,\ 4 $ であり、高橋君は嬉しく\*\*なりません\*\*。 - $ (1,\ 1)\ \rightarrow\ (2,\ 1)\ \rightarrow\ (2,\ 2)\ \rightarrow\ (3,\ 2)\ \rightarrow\ (3,\ 3) $：通ったマスに書かれた整数は $ 3,\ 2,\ 1,\ 5,\ 4 $ であり、高橋君は嬉しく\*\*なります\*\*。 - $ (1,\ 1)\ \rightarrow\ (2,\ 1)\ \rightarrow\ (3,\ 1)\ \rightarrow\ (3,\ 2)\ \rightarrow\ (3,\ 3) $：通ったマスに書かれた整数は $ 3,\ 2,\ 1,\ 5,\ 4 $ であり、高橋君は嬉しく\*\*なります\*\*。 よって、高橋君が嬉しくなる移動経路は、上で $ 3,\ 5,\ 6 $ 番目に述べた $ 3 $ 個です。

### Sample Explanation 2

この例では、高橋君は考えられるどの経路を通っても嬉しくなります。

## 样例 #1

### 输入

```
3 3
3 2 2
2 1 3
1 5 4```

### 输出

```
3```

## 样例 #2

### 输入

```
10 10
1 2 3 4 5 6 7 8 9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
31 32 33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48 49 50
51 52 53 54 55 56 57 58 59 60
61 62 63 64 65 66 67 68 69 70
71 72 73 74 75 76 77 78 79 80
81 82 83 84 85 86 87 88 89 90
91 92 93 94 95 96 97 98 99 100```

### 输出

```
48620```

# 题解

## 作者：zajasi (赞：5)

## 题意
给你一个 $n$ 行 $m$ 列的矩阵。你需要从 $(1,1)$ 走到 $(n,m)$，每次可以往下或右走。问有多少种走法，满足走过的所有数字不相等？
## 解题思路 1
我们观察到 $n \le 10$ 且 $m \le 10$，也就是可以大胆 dfs。最后，维护 set 观察加入一波以后的总数量跟走过的总步数相不相等，相等答案加 $1$。
## AC 代码 1
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
int n,m;
int a[11][11];
int vis[11][11];
int p[101];
int dx[]={1,0};
int dy[]={0,1};
int z;
bool check(int dep){
    set<int> s;
    for(int i=1;i<=dep;i++){
        s.insert(p[i]);
//       cout<<p[i]<<" ";
    }//cout<<"\n";
    if(s.size()==dep)return true;
    return false;
}
void dfs(int dep,int x,int y){
    if(x==n&&y==m){
        p[dep]=a[x][y];
        if(check(dep))z++;
        return;
    }
    vis[x][y]=1;
    p[dep]=a[x][y];
    for(int i=0;i<2;i++){
        int tx=x+dx[i];
        int ty=y+dy[i];
        if(tx>0&&tx<=n&&ty>0&&ty<=m&&vis[tx][ty]==0)dfs(dep+1,tx,ty);
    }
    vis[x][y]=0;
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    dfs(1,1,1);
    cout<<z;
    return 0;
}

```
## 解题思路 2
好像用枚举子集也能过。但因为代码感觉并没有 dfs 好理解，就不细讲了。时间复杂度 $\Theta(2^{20})$。
## AC 代码 2
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[20][20];
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    int ans=0;
    for(int k=0;k<(1<<n+m-2)+1;k++){
        int x=1,y=1;
        bool f=1;
        set<int> s;
        s.insert(a[1][1]);
        for(int i=0;i<n+m-2;i++){
            if((k>>i)&1)x++;
            else y++;
            if(x>n||y>m){
                f=0;
                break;
            }
            s.insert(a[x][y]);
        }
        if(f&&s.size()==n+m-1)ans++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Jerry_heng (赞：4)

看到题解区里空空如也，就来写一篇。

（一）

题意：

给你一个$H \times W$ 的网格，每一格上有对应的数字。从 $(1,1)$ 开始走，到 $(H,W)$ 结束。每一步只能向下或向右。

求路径数使走到的格子上的数互不相同。

（二）

其实就是简单的深搜，优化都不用。$a_{i,j} \le 10^9$，直接用桶记录。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,n,m,a[11][11];
bool b[1000000001];
void ss(int x,int y){
	if(x==n&&y==m){//到了
		ans++;
		return;
	}
	if(x<n&&!b[a[x+1][y]]){//向下
		b[a[x+1][y]]=1;
		ss(x+1,y);
		b[a[x+1][y]]=0;//回溯
	}
	if(y<m&&!b[a[x][y+1]]){//向右
		b[a[x][y+1]]=1;
		ss(x,y+1);
		b[a[x][y+1]]=0;//回溯
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	b[a[1][1]]=1;
	ss(1,1);
	cout<<ans;
	return 0;
}
```


---

## 作者：I_am_kunzi (赞：4)

# AT_abc293_c 题解

### 闪现
[洛谷 abc293c](https://www.luogu.com.cn/problem/AT_abc293_c) | [AtCoder abc293c](https://atcoder.jp/contests/abc293/tasks/abc293_c)

### 题目大意

给你一个 $ H $ 行 $ W $ 列的方阵，高桥要从这个方阵的 $ (1 , 1) $ 走到 $ (H , W) $ ，如果他在这个过程中经过的所有数字都不相同，那么他就会开心；如果他经过的数字中有相同的，他就会不开心。输出高桥所有走法中，可以使他开心的走法的数量。

### 题目分析

因为是要找到使高桥开心的所有的路径，我便想到了 for 循环，但是又一想，发现 for 循环的话既慢又不好控制层数，因此我想到了递归。

### 思路拆分 and 代码实现

+ 输入
+ 递归 and 判断函数
+ 输出

输入和输出部分在此处不再多说，让我们直接进入下面的递归和判断部分。

递归部分需要一个数组 $ qk $ 存高桥经过的数，还需要判断：如果他没有到第 $ H $ 行，那么就递归到下一行；如果他没有到地 $ W $ 列，那么就递归到下一列... ...直到他走到了第 $ H $ 行 $ W $ 列，然后就运行判断的函数，用一个数组 $ fuzhi $ 来复制一份 $ qk $ 中的数，排序后再看相邻的两个数有没有重复，有则不记录这一条路径，否则就记录。

#### 为什么不能对原来的 $ qk $ 数组排序？

因为这个数组是存储高桥经过的数，如果对它排序，这个数组的顺序就会被打乱，体现不出高桥经过数的顺序，为了方便理解，让我们以一个样例加深理解：

以 AtCoder 原题中的样例 $ 1 $ 为例：

```
3 3
3 2 2
2 1 3
1 5 4

```

高桥先以 $ (1 , 1) , (2 , 1) , (3 , 1) , (3 , 2 ) , (3 , 3) $ 的路径移动，此时 $ qk $ 数组中存储的是 $ 3 , 2 , 2 , 3 , 4 $ 排序后是 $ 2 , 2 , 3 , 3 , 4 $ ，下一步递归时，高桥的路径变成了 $ (1 , 1) , (2 , 1) , (2 , 2) , (3 , 2 ) , (3 , 3) $ ， 数组中应该是$ 3 , 2 , 1 , 3 , 4 $ ，而因为经过了一次排序，现在变成了 $ 2 , 2 , 1 , 3 , 4 $ ，已经和原来的不一样了。

综上，不能对原来的 $ qk $ 数组排序。

由以上的分析，代码如下：

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
using namespace std;
int qk[25] , fuzhi[25];
int sz[15][15];
int h , w;
int ans;
//qk，fuzhi：含义如题解中
//sz：存储方阵	h，w：存储行和列 
//ans：存储答案数量 
bool right(int cnt) //判断函数 
{
	for(int i = 1 ; i <= cnt ; i++)
	{
		fuzhi[i] = qk[i]; //复制 
	}
	sort(fuzhi + 1 , fuzhi + cnt + 1); //排序 
	for(int i = 1 ; i <= cnt - 1 ; i++)
	{
		if(fuzhi[i] == fuzhi[i + 1]) //有重复 
		{
			return 0;  //答案增加 0 个  
		}
	}
	return 1; //答案增加 1 个 
}
void dfs(int a , int b , int c)
//a，b：存现在高桥的行和列
//c：存储高桥这条路径现在在走第几个数 
{
	qk[c] = sz[a][b]; //存储高桥经过的数 
	if(a == h && b == w) //到终点 
	{
		ans += right(c); //判断并累加 
		return ; //返回上一层递归 
	}
	if(a != h)
	{
		dfs(a + 1 , b , c + 1); //到下一行 
	}
	if(b != w)
	{
		dfs(a , b + 1 , c + 1); //到下一列 
	}
}
int main()
{
	cin >> h >> w;
	for(int i = 1 ; i <= h ; i++)
	{
		for(int j = 1 ; j <= w ; j++)
		{
			cin >> sz[i][j];
		}
	}
	dfs(1 , 1 , 1); //递归 
	cout << ans << endl;
    return 0;
}

```

还有无注释版：

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
using namespace std;
int qk[25] , fuzhi[25];
int sz[15][15];
int h , w;
int ans;
bool right(int cnt)
{
	for(int i = 1 ; i <= cnt ; i++)
	{
		fuzhi[i] = qk[i];
	}
	sort(fuzhi + 1 , fuzhi + cnt + 1);
	for(int i = 1 ; i <= cnt - 1 ; i++)
	{
		if(fuzhi[i] == fuzhi[i + 1])
		{
			return 0;
		}
	}
	return 1;
}
void dfs(int a , int b , int c)
{
	qk[c] = sz[a][b];
	if(a == h && b == w)
	{
		ans += right(c);
		return ;
	}
	if(a != h)
	{
		dfs(a + 1 , b , c + 1);
	}
	if(b != w)
	{
		dfs(a , b + 1 , c + 1);
	}
}
int main()
{
	cin >> h >> w;
	for(int i = 1 ; i <= h ; i++)
	{
		for(int j = 1 ; j <= w ; j++)
		{
			cin >> sz[i][j];
		}
	}
	dfs(1 , 1 , 1);
	cout << ans << endl;
    return 0;
}

```

最后，附上 AC 的截图：
![abc293c_ac](https://cdn.luogu.com.cn/upload/image_hosting/bj4dfe93.png)

---

## 作者：rui_er (赞：2)

样例二已经告诉我们路径数最多为 $48620=\binom{18}{9}$（九步向右走、九步向下走，任意排列）。这个路径数是非常少的，考虑暴力。

首先将所有数离散化，然后可以塞到一个大小为 $10^2$ 的 bitset 中，在搜索过程中利用 bitset 判断经过的数是否重复即可。

```cpp
// Problem: C - Make Takahashi Happy
// Contest: AtCoder - AtCoder Beginner Contest 293
// URL: https://atcoder.jp/contests/abc293/tasks/abc293_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
	uniform_int_distribution<int> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 10;

int n, m, a[N][N], buc[N*N], tot, ans;
bitset<N*N> qwq;

void dfs(int x, int y, bitset<N*N>& now) {
	if(x == n - 1 && y == m - 1) {++ans; return;}
	if(x < n - 1 && !now.test(a[x+1][y])) {
		now.set(a[x+1][y]);
		dfs(x+1, y, now);
		now.reset(a[x+1][y]);
	}
	if(y < m - 1 && !now.test(a[x][y+1])) {
		now.set(a[x][y+1]);
		dfs(x, y+1, now);
		now.reset(a[x][y+1]);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 0, n-1) {
		rep(j, 0, m-1) {
			scanf("%d", &a[i][j]);
			buc[tot++] = a[i][j];
		}
	}
	sort(buc, buc+tot);
	tot = unique(buc, buc+tot) - buc;
	rep(i, 0, n-1) rep(j, 0, m-1) a[i][j] = lower_bound(buc, buc+tot, a[i][j]) - buc;
	qwq.set(a[0][0]);
	dfs(0, 0, qwq);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：incra (赞：2)

### 题意
给定一个 $n\times m$ 的方格，每一个格子上都有一个数字 $A_{i,j}$。

一条从 $(1,1)$ 到 $(n,m)$ 的路径能让 Takahashi 开心当且仅当这条路径上没有重复的数且没有往上或往左移动。

求有几条路径能让 Takahashi 开心。

$n,m\le10$。

### 题解
由于 $n$很小，考虑暴搜所有方案。

我们用一个 $set$ 来保存路径上遇到的所有数，这里我们用到了 $set$ 的特性：可以自动去重。所以当从 $(1,1)$ 走到 $(n,m)$ 遇到的数的个数是 $n+m-1$。所以判断到 $(n,m)$ 时 $set$ 里数的个数是否为 $n+m-1$ 来判断这条路径有没有重复的数。

当然，从 $1,1$ 走到 $(i,j)$ 时，数的个数不是 $i+j-1$ 时，可以提前退出，算作一个剪枝吧，当然不加也能过。

### 代码
```cpp
#include <iostream>
#include <set>
using namespace std;
const int N = 20;
int n,m;
int a[N][N];
int ans = 0;
void dfs (int x,int y,set <int> vis) {
	vis.insert (a[x][y]);
	if (x == n && y == m) {
		ans += vis.size () == n + m - 1;
		return ;
	}
	if (x + 1 <= n) dfs (x + 1,y,vis);
	if (y + 1 <= m) dfs (x,y + 1,vis);
}
int main () {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) cin >> a[i][j];
	}
	dfs (1,1,{});
	cout << ans << endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 思路
我们使用搜索。从 $(1,1)$ 开始，每次判断一下下一个点的值是否已经被记录过了。若没有，就继续搜索，并将这个点的值记录一下即可。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[100][100];
int k[1000];
int idx;
int ans;
bool check(int x,int y)//判断a[x][y]的值是否已经存在
{
	for(int i=1;i<=idx;i++) if(k[i]==a[x][y]) return 0;
	return 1;
}
void dfs(int x,int y)
{
	if(x==n&&y==m) ans++;//走到目标点了
	else
	{
		if(check(x,y+1)&&x<=n&&y+1<=m) k[++idx]=a[x][y+1],dfs(x,y+1),idx--;//向右走
		if(check(x+1,y)&&x+1<=n&&y<=m) k[++idx]=a[x+1][y],dfs(x+1,y),idx--;//向下走
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	k[++idx]=a[1][1];//第一个点是一定会有的
	dfs(1,1);
	cout<<ans;
	return 0;
}
```


---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

给一个 $H \times W$ 的网格每个点有一个数字，求从 $(1,1)$ 走到 $(H,W)$ 最短路径数，使得走到的数字互不相同。

### 题目分析

首先看到求最短路径数可以用动规思维的标数法，但是注意“走到的数字互不相同”，很明显用标数法无法实现。

仔细观察数据范围 $2 \le H,W \le 10$，可以发现网格并不大，考虑用 $\operatorname{dfs}$，记录哪些数字已经经过了，如果当前点已经经过了就说明这条路径不通，最后统计所有到 $(H,W)$ 的路径数。

总的时间效率是 $\le O(48620)$ 的（当网格最大为 $10 \times 10$ 时，路径数最大为 $48620$）。
### code
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 1e9 + 5;
int n, m, ans, a[20][20];
bool cnt[N];
void dfs(int x, int y)
{
	if(y > m || x > n)
		return ;
    if(x == n && y == m)
	{
        ans++;
        return;
    }
    if(!cnt[a[x + 1][y]])
	{
        cnt[a[x + 1][y]] = true;
        dfs(x + 1, y);
        cnt[a[x + 1][y]] = false;
    }
    if(!cnt[a[x][y + 1]])
	{
        cnt[a[x][y + 1]] = true;
        dfs(x,y + 1);
        cnt[a[x][y + 1]] = false;
    }
    return ; 
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            scanf("%d", &a[i][j]);
    cnt[a[1][1]] = true;
    dfs(1, 1);
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

闲的没事打了两篇代码。

## 思路

用 `map` 记录每一个走过的数字，走到每一个新的格子就判定一下，那个格子里的数字有没有出现在总路程里，如果没有，记录该格子的数字并进行下一步的深搜，当横坐标 $= H$ 且纵坐标 $= W$ 时，答案 $+1$ 即可，别忘了判定横纵坐标在不在边界和回溯到原位置。

## 代码

~~两篇代码也就是一篇先提前标记下一个要搜索的，一个是到达是标记的。~~

```cpp
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
#define int long long
map<int, int> MAP;
int a[101][101], h, w, cnt = 0;
void dfs(int x, int y){
	if(x == h && y == w){//到达右下角
		cnt++;
		return ;
	}
	if(x != h){//如果横坐标没有碰到边界
		if(MAP[a[x + 1][y]] == 0){//如果之前并没走到与下一个相同的数字
			MAP[a[x + 1][y]] = 0;//标记
			dfs(x + 1, y);//继续深搜
			MAP[a[x + 1][y]] = 0;//回溯
		}
	}
	if(y != w){//如果纵坐标没有碰到边界
		if(MAP[a[x][y + 1]] == 0){//如果之前并没走到与下一个相同的数字
			MAP[a[x][y + 1]] = 1;
			dfs(x, y + 1);
			MAP[a[x][y + 1]] = 0;
		}
	}
	return ;
}
signed main(){
	scanf("%lld%lld",&h,&w);
	for(int i = 1; i <= h; i++) for(int j = 1; j <= w; j++) scanf("%lld",&a[i][j]);
	MAP[a[1][1]] = 1;//初始化
	dfs(1, 1);
	printf("%lld\n", cnt);
	return 0;
}
```

```cpp
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
#define int long long
map<int, int> MAP;
int a[101][101], h, w, cnt = 0;
void dfs(int x, int y){
	if(MAP[a[x][y]]) return ;//如果这个格子上的数之前走到过
	if(x == h && y == w){
		cnt++;
		return ;
	}
	MAP[a[x][y]]++;
	if(x != h){
		dfs(x + 1, y);
	}
	if(y != w){
		dfs(x, y + 1);
	}
	MAP[a[x][y]]--;
	return ;
}
signed main(){
	scanf("%lld%lld",&h,&w);
	for(int i = 1; i <= h; i++) for(int j = 1; j <= w; j++) scanf("%lld",&a[i][j]);
	dfs(1, 1);
	printf("%lld\n", cnt);
	return 0;
}
```

---

## 作者：Escapism (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc293_c)

# 题意

给出一个 $H \times W$ 的矩阵。矩阵的每一格上有一个数。现在要从 $(1,1)$ 走到 $(H,W)$，只能向下面的格子或右边的格子走，问有几种行走方案可以使走到的格子上没有重复的数字。

# 思路

数据范围很小，只有 $H,W \le 10$。所以可以考虑爆搜枚举每一种方案。

从 $(1,1)$ 开始枚举，先枚举到右边的路线，再枚举到下边的所有路线。对所有到达的格子都以此类推。用一个 ``map`` 记录数字的出现次数。如果达到的格子的数字已经出现过，就说明之后的所有路线都是无效的，因而可以直接停止向下枚举。

如果到达了第 $H$ 行或者第 $W$ 列，就只有向右或向下的一种情况。

看上去非常暴力，但实际上最大的枚举次数大约只有 $2^{20}$ 次，而且有 ``map`` 的剪枝和最后一行或最后一列的限制，所以实际次数会更小。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
 
int cnt,n,m;
int a[15][15];
map<int,int> MP;
void dfs(int x,int y){
  	if (MP[a[x][y]] != 0) return; //出现重复数字，剪枝
  	//cout<<x<<" "<<y<<endl;
 	if (x == n && y == m){ //到达终点
		cnt++;
		return;
	}
	MP[a[x][y]]++; //记录数字
	if (x != n) dfs(x + 1,y); //向右枚举
	if (y != m) dfs(x,y + 1);//向下枚举
	MP[a[x][y]]--;//将这一格的数字删除
	return;
}
int main(){
  	cin>>n>>m;
	for (int i = 1;i <= n;i++){
      	for (int j = 1;j <= m;j++){
          	cin>>a[i][j];
        }
    }
  	dfs(1,1);
	cout<<cnt<<endl;
}
```


---

## 作者：atomic_int (赞：0)

## 题意：
有一个 $H \times W$ 的网格，从 $(1,1)$ 开始走，可以向下或向右走（不能越界），走到 $(H, W)$ 结束，要求走过的数不能有重复。

## 分析：
$H,W$ 很小，考虑搜索，对于每种方法，记录走过的数，判断是否有重复。

## 代码：
```cpp
#include <bits/stdc++.h>
#include <vector>
#define int long long
#define ld long double
#define ri register int
#define inf64 0x7f7f7f7f
#define endl '\n'
#define SeeFloat(x) fixed << setprecision(x)
using namespace std;
int H, W, ans;
vector<vector<int>> mp(20, vector<int>(20));
vector<vector<bool>> vis(20, vector<bool>(20));
const int dx[2] = {0, 1}, dy[2] = {1, 0};
vector<int> a;
inline void dfs(int x, int y) {
	if (x == H && y == W) {
		map<int, int> m;
		for (auto v : a) {
			if (m[v] >= 1) {
				return ;
			}
			m[v] ++;
		}
		ans ++;
		return ;
	}
	for (int i = 0; i < 2; i ++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx <= H && nx >= 1 && ny <= W && ny >= 1 && !vis[nx][ny]) {
			vis[nx][ny] = true;
			a.push_back(mp[nx][ny]);
			dfs(nx, ny);
			vis[nx][ny] = false;
			a.pop_back();
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> H >> W;
	for (int i = 1; i <= H; i ++) {
		for (int j = 1; j <= W; j ++) {
			cin >> mp[i][j];
		}
	}
	vis[1][1] = true;
	a.push_back(mp[1][1]);
	dfs(1, 1);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[$\color{orangered}\text{题目传送门}$](https://www.luogu.com.cn/problem/AT_abc293_c)

## 题意
给出一个 $H\times W$ 的数字矩阵，高桥最初在 $(1,1)$，每次可以向下或向右走，但不能走出地图。问有几条路线可以使他走到 $(H,W)$ 而所走过的数字不重复。

## 分析
dfs 轻松解决。

由于数字最大为 $10^9$，所以用 `map` 开一个桶用来标记这个数字是否走过。
```cpp
map<int,bool>f;
```
左上角的数是一定要走的，标记为 $1$。
```cpp
f[a[1][1]]=1;
```

开两个方向数组，表示向下和向右走。
```cpp
int dx[2]={1,0},dy[2]={0,1};
```

dfs。
```cpp
void dfs(int x,int y)//x,y表示当前坐标
{
	if(x==h&&y==w)//如果走到了(h,w)
	{
		ans++;//答案加1
		return;//返回上一个点
	}
	for(int i=0;i<2;i++)//枚举两个方向
	{
		int xx=x+dx[i],yy=y+dy[i];//xx和yy表示该走的下一个点的坐标
		if(xx<=h&&yy<=w)//如果在地图范围内
		{
			if(!f[a[xx][yy]])//如果下一个点的数字没有被走过
			{
				f[a[xx][yy]]=1;//下一个点的数字标记为走过
				dfs(xx,yy);//走到下一个点
				f[a[xx][yy]]=0;//回溯
				//因为不走这条路了，所以这个点的数字要标记为0
			}
		}
	}
}
```

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w;
long long a[15][15];
map<int,bool>f;
long long ans=0;
int dx[2]={1,0},dy[2]={0,1};
void dfs(int x,int y)
{
	if(x==h&&y==w)
	{
		ans++;
		return;
	}
	for(int i=0;i<2;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<=h&&yy<=w)
		{
			if(!f[a[xx][yy]])
			{
				f[a[xx][yy]]=1;
				dfs(xx,yy);
				f[a[xx][yy]]=0;
			}
		}
	}
}
int main()
{
	cin>>h>>w;
	for(int i=1;i<=h;i++)
	{
		for(int j=1;j<=w;j++)
		cin>>a[i][j];
	}
	f[a[1][1]]=1;
	dfs(1,1);
	cout<<ans;
    return 0;
}
```

---

## 作者：Symbolize (赞：0)

# 思路
因为不允许走与已经走过的任意一个点值相同的点，所以说我们考虑搜索。

使用深搜还是广搜呢？但让使用深搜，广搜最大的问题就是无法回溯，当找到一条路径后，需要清除这条路径走过的点，所以要用广搜就只能记录下每次走的路径进行多次广搜。因为数据范围很小，所以这是可以过的，但是从并不推荐。

深搜的核心在于递归，每次只能向下边或者右边走，所以判断下边的点能否通过，能则递归下面的点；同理，判断右边的点是否能通过，能则递归下面的点。

如何判断？使用一个标记数组就可以了。

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e3+10;
using namespace std;
int n,m,a[N][N],ans;
map<int,bool> mp;//实际上用数组就行
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
void dfs(int x,int y)
{
	if(x==n&&y==m)//找到了，累计答案
	{
		++ans;
		return;
	}
	if(!mp[a[x][y+1]]&&x<=n&&y<m)
	{
		mp[a[x][y+1]]=1;
		dfs(x,y+1);
		mp[a[x][y+1]]=0;//回溯
	}
	if(!mp[a[x+1][y]]&&x<n&&y<=m)
	{
		mp[a[x+1][y]]=1;
		dfs(x+1,y);
		mp[a[x+1][y]]=0;//回溯
	}
	return;
}
signed main()
{
	n=read();
	m=read();
	rep1(i,1,n) rep1(j,1,m) a[i][j]=read();
	mp[a[1][1]]=1;//第一个点一定会走到
	dfs(1,1);//搜索
	cout<<ans<<endl;//输出0
	return 0;//收场
}
```

---

