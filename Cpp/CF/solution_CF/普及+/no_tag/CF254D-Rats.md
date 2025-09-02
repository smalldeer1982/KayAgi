# Rats

## 题目描述

Rats have bred to hundreds and hundreds in the basement of the store, owned by Vasily Petrovich. Vasily Petrovich may have not noticed their presence, but they got into the habit of sneaking into the warehouse and stealing food from there. Vasily Petrovich cannot put up with it anymore, he has to destroy the rats in the basement. Since mousetraps are outdated and do not help, and rat poison can poison inattentive people as well as rats, he chose a radical way: to blow up two grenades in the basement (he does not have more).

In this problem, we will present the shop basement as a rectangular table of $ n×m $ cells. Some of the cells are occupied by walls, and the rest of them are empty. Vasily has been watching the rats and he found out that at a certain time they go to sleep, and all the time they sleep in the same places. He wants to blow up a grenade when this convenient time comes. On the plan of his basement, he marked cells with sleeping rats in them. Naturally, these cells are not occupied by walls.

Grenades can only blow up in a cell that is not occupied by a wall. The blast wave from a grenade distributes as follows. We assume that the grenade blast occurs at time 0. During this initial time only the cell where the grenade blew up gets 'clear'. If at time $ t $ some cell is clear, then at time $ t+1 $ those side-neighbouring cells which are not occupied by the walls get clear too (some of them could have been cleared before). The blast wave distributes for exactly $ d $ seconds, then it dies immediately.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF254D/b144e2334a4b3ed6e085b2980cabe248fcd67fba.png)An example of a distributing blast wave: Picture 1 shows the situation before the blast, and the following pictures show "clear" cells by time 0,1,2,3 and 4. Thus, the blast wave on the picture distributes for $ d=4 $ seconds.Vasily Petrovich wonders, whether he can choose two cells to blast the grenades so as to clear all cells with sleeping rats. Write the program that finds it out.

## 样例 #1

### 输入

```
4 4 1
XXXX
XR.X
X.RX
XXXX
```

### 输出

```
2 2 2 3
```

## 样例 #2

### 输入

```
9 14 5
XXXXXXXXXXXXXX
X....R...R...X
X..R.........X
X....RXR..R..X
X..R...X.....X
XR.R...X.....X
X....XXR.....X
X....R..R.R..X
XXXXXXXXXXXXXX
```

### 输出

```
2 3 6 9
```

## 样例 #3

### 输入

```
7 7 1
XXXXXXX
X.R.R.X
X.....X
X..X..X
X..R..X
X....RX
XXXXXXX
```

### 输出

```
-1
```

# 题解

## 作者：Rushroom (赞：5)

超级恶心人的 BFS 题目。

~~话说为什么 CF 的题还要用 freopen 啊~~

[传送门](https://www.luogu.com.cn/problem/CF254D)

## 假的思路

直接枚举两个炸弹的位置，然后对这两个位置，分别进行 BFS，求出能炸到哪些点，如果覆盖了所有老鼠就输出这个方案。

发现复杂度是 $O(n^4 d^2)$ 的，TLE 了。

## 真的思路

我们发现，真正有用的位置其实没有多少个。

首先，我们随便选一个老鼠，因为它一定要被炸到，所以 BFS 一遍，求出所有能炸到它的位置，那么第一个炸弹一定在这些位置之中，数量是 $O(d^2)$ 的。

我们就可以愉快地枚举第一个炸弹的位置了。然后我们在第一个炸弹的位置 BFS，求出它能炸到哪些位置。

但是，会有一些老鼠是第一个炸弹炸不到的。我们再用类似的方法，找到一个这样的老鼠，再 BFS 哪些位置能炸到它，再枚举第二个炸弹的位置，最后判断是不是能炸到所有老鼠即可。

数一数，发现一共有 **4 个 BFS**。

~~恶心死了~~

还有一些细节，比如老鼠的数量小于 2，可以放炸弹的位置数小于 2 等，考虑一下就行了。

因为如果老鼠的数量大于 $8d^2$，就可以直接判断无解了，所以复杂度是 $O(d^6)$ 的。

## Code

```cpp
 /*
  * @Description: I want to be the weakest vegetable in the world!
  * @Author: CGBoy
  * @Date: 2022-01-27 21:00:58
  */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;i++)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T, case_;
int n, m, d, emp = 0;
char c[1010][1010];
vector<pair<int, int> >r;
pair<pair<int, int>, int>tmp;
bool vis[1010][1010], vis2[1010][1010], vis3[1010][1010], vis4[1010][1010];
void solve() {
    scanf("%d%d%d", &n, &m, &d);
    rep(i, n) {
        scanf("%s", c[i]);
        rep(j, m) {
            if (c[i][j] == 'R')r.pb(mp(i, j)), emp++;
            if (c[i][j] == '.')emp++;
        }
    }
    if (r.size() > 8 * d * d || emp < 2) {
        printf("-1");
        return;
    }
    if (r.size() == 0) {
        emp = 0;
        rep(i, n) {
            rep(j, m) {
                if (c[i][j] != 'X') {
                    printf("%d %d ", i + 1, j + 1);
                    emp++;
                    if (emp == 2)return;
                }
            }
        }
    }
    if (r.size() == 1) {
        printf("%d %d ", r[0].fi + 1, r[0].se + 1);
        rep(i, n) {
            rep(j, m) {
                if (c[i][j] != 'X') {
                    if (i != r[0].fi || j != r[0].se) {
                        printf("%d %d ", i + 1, j + 1);
                        return;
                    }
                }
            }
        }
    }
    queue<pair<pair<int, int>, int > >q;
    q.push(mp(mp(r[0].fi, r[0].se), 0));
    while (!q.empty()) {
        tmp = q.front();
        q.pop();
        if (tmp.se > d || c[tmp.fi.fi][tmp.fi.se] == 'X' || vis[tmp.fi.fi][tmp.fi.se])continue;
        vis[tmp.fi.fi][tmp.fi.se] = 1;
        q.push(mp(mp(tmp.fi.fi - 1, tmp.fi.se), tmp.se + 1));
        q.push(mp(mp(tmp.fi.fi + 1, tmp.fi.se), tmp.se + 1));
        q.push(mp(mp(tmp.fi.fi, tmp.fi.se - 1), tmp.se + 1));
        q.push(mp(mp(tmp.fi.fi, tmp.fi.se + 1), tmp.se + 1));
    }
    rep(i, n) {
        rep(j, m) {
            // first bomb
            if (!vis[i][j])continue;
            init(vis2, 0);
            queue<pair<pair<int, int>, int > >q2;
            q2.push(mp(mp(i, j), 0));
            while (!q2.empty()) {
                tmp = q2.front();
                q2.pop();
                if (tmp.se > d || c[tmp.fi.fi][tmp.fi.se] == 'X' || vis2[tmp.fi.fi][tmp.fi.se])continue;
                vis2[tmp.fi.fi][tmp.fi.se] = 1;
                q2.push(mp(mp(tmp.fi.fi - 1, tmp.fi.se), tmp.se + 1));
                q2.push(mp(mp(tmp.fi.fi + 1, tmp.fi.se), tmp.se + 1));
                q2.push(mp(mp(tmp.fi.fi, tmp.fi.se - 1), tmp.se + 1));
                q2.push(mp(mp(tmp.fi.fi, tmp.fi.se + 1), tmp.se + 1));
            }
            bool s = 1;
            rep(k, r.size()) {
                if (!vis2[r[k].fi][r[k].se]) {
                    s = 0;
                    init(vis3, 0);
                    queue<pair<pair<int, int>, int > >q3;
                    q3.push(mp(mp(r[k].fi, r[k].se), 0));
                    while (!q3.empty()) {
                        tmp = q3.front();
                        q3.pop();
                        if (tmp.se > d || c[tmp.fi.fi][tmp.fi.se] == 'X' || vis3[tmp.fi.fi][tmp.fi.se])continue;
                        vis3[tmp.fi.fi][tmp.fi.se] = 1;
                        q3.push(mp(mp(tmp.fi.fi - 1, tmp.fi.se), tmp.se + 1));
                        q3.push(mp(mp(tmp.fi.fi + 1, tmp.fi.se), tmp.se + 1));
                        q3.push(mp(mp(tmp.fi.fi, tmp.fi.se - 1), tmp.se + 1));
                        q3.push(mp(mp(tmp.fi.fi, tmp.fi.se + 1), tmp.se + 1));
                    }
                    break;
                }
            }
            if (s) {
                printf("%d %d ", i + 1, j + 1);
                rep(ii, n) {
                    rep(jj, m) {
                        if (ii != i || jj != j) {
                            if (c[ii][jj] != 'X') {
                                printf("%d %d ", ii + 1, jj + 1);
                                return;
                            }
                        }
                    }
                }
            }
            rep(ii, n) {
                rep(jj, m) {
                    // second bomb
                    if ((i == ii && j == jj) || !vis3[ii][jj])continue;
                    init(vis4, 0);
                    queue<pair<pair<int, int>, int > >q4;
                    q4.push(mp(mp(ii, jj), 0));
                    while (!q4.empty()) {
                        tmp = q4.front();
                        q4.pop();
                        if (tmp.se > d || c[tmp.fi.fi][tmp.fi.se] == 'X' || vis4[tmp.fi.fi][tmp.fi.se])continue;
                        vis4[tmp.fi.fi][tmp.fi.se] = 1;
                        q4.push(mp(mp(tmp.fi.fi - 1, tmp.fi.se), tmp.se + 1));
                        q4.push(mp(mp(tmp.fi.fi + 1, tmp.fi.se), tmp.se + 1));
                        q4.push(mp(mp(tmp.fi.fi, tmp.fi.se - 1), tmp.se + 1));
                        q4.push(mp(mp(tmp.fi.fi, tmp.fi.se + 1), tmp.se + 1));
                    }
                    bool suc = 1;
                    rep(k, r.size()) {
                        if (vis2[r[k].fi][r[k].se] == 0 && vis4[r[k].fi][r[k].se] == 0) {
                            suc = 0;
                        }
                    }
                    if (suc) {
                        printf("%d %d %d %d", i + 1, j + 1, ii + 1, jj + 1);
                        return;
                    }
                }
            }
        }
    }
    printf("-1");
}
int main() {
    T = 1;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    for (case_ = 1;case_ <= T;case_++)solve();
    return 0;
}
```

~~不喝，不喝是吧，不喝，我就炸死你！~~

---

## 作者：AquariusZhao (赞：4)

我感觉本蒟蒻的代码结构比较清晰，所以打算来一发题解～

## 注意事项

这题要用文件输入输出！！！

输入：

```cpp
freopen("input.txt", "r", stdin);
```

输出：

```cpp
freopen("output.txt", "w", stdout);
```

## 题意

[传送门](https://www.luogu.com.cn/problem/CF254D)

给定一张 $ n \times m $ 网格图，其中有空格字（、墙和老鼠。你的任务是用你手中的两枚手榴弹来炸死所有老鼠，并给出它们的坐标。若无解则输出 `-1` 。

每枚手榴弹的伤害会在安放后的 $ d $ 秒内四处蔓延。具体地，每秒可以向上下左右的非墙体格子扩散一格。

数据保证至少有两个位置可以安放手榴弹，且至少有一只老鼠。

$ 4 \le n,m \le 1000,1 \le d \le 8 $

## 思路

本题的难点在于有两枚手榴弹，不能直接用一般的方法进行搜索。

观察数据范围，发现 $ n $ 到了 $1000$ ，但是 $ d $ 很小，所以可以考虑进行若干次以 $ d $ 为单位的搜索。

## 

不难发现，有的手榴弹是没用的。换句话说，第一枚手榴弹至少要炸到一只老鼠。

想到这里，我们不妨选定第一只老鼠，搜索出第一枚手榴弹要安放的范围。

以 $ d=3 $ 的情况为例：（蓝色是边框）

![](https://cdn.luogu.com.cn/upload/image_hosting/8p76c1l3.png)

可以看出，其中橙色区域为第一枚手榴弹要炸到左边的老鼠的安放区域。这样就锁定了第一枚手榴弹的枚举范围。

然后就可以类似地查找第二只还没有被炸到的老鼠。接着再找出第二枚手榴弹的橙色区域、枚举第二枚手榴弹的位置（注意：不要重复记录第一枚手榴弹炸过的老鼠）。

但如果第二枚手榴弹无法炸死剩余老鼠，就要将第一枚手榴弹换一个位置（还在它的橙色区域内）。

最后，如果发现第一枚手榴弹在橙色区域内均没有可以安放的位置，说明必然没有能炸死所有老鼠的方案（因为没有能同时炸死第一只老鼠和其他老鼠的方案）。

时间复杂度 $ O(d^6) $，可以通过。

另外，可以加一条特判：若老鼠数量 $ >4d^2+4d+2 $ ，则显然没有可行的方案。

## 代码

如果对时间复杂度有疑问可以看看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int N = 1005;
int n, m, d, pos[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // 预处理出移动的方位
char s[N][N];         // 地图
vector<pii> mice;     // 老鼠坐标
bool vis[5][N][N];    // vis[k][i][j]表示bfs_k遍历过的位置
struct node
{
    int x, y, p;
};
pii a, b;             // 两枚手榴弹的坐标

int bfs4(int X, int Y)     // 记录第二枚手榴弹炸到的老鼠数
{
    int res = 0;
    queue<node> q;
    memset(vis[4], 0, sizeof(vis[4]));
    q.push({X, Y, 0});
    vis[4][X][Y] = true;
    while (!q.empty())
    {
        node cur = q.front();
        q.pop();
        if (!vis[2][cur.x][cur.y])           // 第一枚手榴弹没有炸到
            res += s[cur.x][cur.y] == 'R';   // 计数
        if (cur.p >= d)
            continue;
        for (int i = 0; i < 4; i++)
        {
            int tx = cur.x + pos[i][0], ty = cur.y + pos[i][1];
            if (1 < tx && tx < n && 1 < ty && ty < m && !vis[4][tx][ty] && s[tx][ty] != 'X')
            {
                q.push({tx, ty, cur.p + 1});
                vis[4][tx][ty] = true;
            }
        }
    }
    return res;
}

int bfs3(int X, int Y)     // 枚举第二枚手榴弹的位置，返回第二枚手榴弹可以炸到的最大老鼠数量
{
    int mx = 0;
    queue<node> q;
    memset(vis[3], 0, sizeof(vis[3]));
    q.push({X, Y, 0});
    vis[3][X][Y] = true;
    while (!q.empty())
    {
        node cur = q.front();
        q.pop();
        int t = bfs4(cur.x, cur.y);
        if (t > mx) // 更新第二枚手榴弹的最优位置
        {
            mx = t;
            b = {cur.x, cur.y};
        }
        if (cur.p >= d)
            continue;
        for (int i = 0; i < 4; i++)
        {
            int tx = cur.x + pos[i][0], ty = cur.y + pos[i][1];
            if (1 < tx && tx < n && 1 < ty && ty < m && !vis[3][tx][ty] && s[tx][ty] != 'X')
            {
                q.push({tx, ty, cur.p + 1});
                vis[3][tx][ty] = true;
            }
        }
    }
    return mx;
}

int bfs2(int X, int Y)     // 记录第一枚手榴弹炸到的老鼠数
{
    a = {X, Y};     // 第一枚手榴弹的位置
    int res = 0;    // 第一枚手榴弹炸到的老鼠数
    queue<node> q;
    memset(vis[2], 0, sizeof(vis[2]));
    q.push({X, Y, 0});
    vis[2][X][Y] = true;
    while (!q.empty())
    {
        node cur = q.front();
        q.pop();
        res += s[cur.x][cur.y] == 'R'; // 记数
        if (cur.p >= d)
            continue;
        for (int i = 0; i < 4; i++)
        {
            int tx = cur.x + pos[i][0], ty = cur.y + pos[i][1];
            if (1 < tx && tx < n && 1 < ty && ty < m && !vis[2][tx][ty] && s[tx][ty] != 'X')
            {
                q.push({tx, ty, cur.p + 1});
                vis[2][tx][ty] = true;
            }
        }
    }
    for (auto &&i : mice)   // 查找没有被炸到的老鼠
        if (!vis[2][i.first][i.second])
            return res + bfs3(i.first, i.second);
    if (b.first == 0)       // 第一枚手榴弹就已经炸死所有老鼠了
        for (int i = 2; i < n; i++)
            for (int j = 2; j < m; j++)
                if (s[i][j] != 'X')
                    b = {i, j};
    return mice.size();
}

bool bfs1(int X, int Y)     // 枚举第一枚手榴弹的位置
{
    queue<node> q;
    q.push({X, Y, 0});
    vis[1][X][Y] = true;
    while (!q.empty())
    {
        node cur = q.front();
        q.pop();
        if (bfs2(cur.x, cur.y) == mice.size())  // 判断两枚手榴弹是否能够炸死所有老鼠
            return true;
        if (cur.p >= d)
            continue;
        for (int i = 0; i < 4; i++)
        {
            int tx = cur.x + pos[i][0], ty = cur.y + pos[i][1];
            if (1 < tx && tx < n && 1 < ty && ty < m && !vis[1][tx][ty] && s[tx][ty] != 'X')
            {
                q.push({tx, ty, cur.p + 1});
                vis[1][tx][ty] = true;
            }
        }
    }
    return false;   // 不存在方案
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m >> d;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= m; j++)
            if (s[i][j] == 'R')
                mice.push_back({i, j}); // vector记录老鼠坐标
    }
    if (mice.size() <= 4 * d * d + 4 * d + 2 && bfs1(mice[0].first, mice[0].second))
        printf("%d %d %d %d\n", a.first, a.second, b.first, b.second);
    else
        puts("-1");
    return 0;
}
```

---

## 作者：jun头吉吉 (赞：3)

## 题意
一个 $n\times m$的网格图中，有一些格子是墙，其余格子中，有一些格子中有老鼠.

现在需要放置两颗手榴弹，每颗手榴弹初始在格子$(r_i,c_i)$ 上，在 $1\sim d$ 秒内，每过 $1$ 秒其伤害范围会从现有的每个伤害范围的格子向外扩展一格并炸死哪一格的老鼠。

你需要给出能够杀死所有老鼠的两个手榴弹的放置坐标$(r_1,c_1)$ 和 $(r_2,c_2)$ ，如果无解，则输出 $-1$
## 题解
 考虑如果老鼠的数量大于 $290$ 那么一定不能全部炸死。只需要考虑老鼠的数量 $\le 290$。先计算出每个位置能炸到的老鼠存在 $\rm bitset$ 里，如果炸不到就不用管了。那么显然最多就 $145\times 290$ 个这样的点。于是先枚举能炸到第一个老鼠的点，第一个炸弹只能在这些位置，再去枚举第二个位置，把两个位置能炸到的老鼠取交集，也就是 $\rm bitset$ 的或。

复杂度主要是后面的 $\mathcal{O}(\frac{290\times145\times290\times290}w)$。

不要忘记特判只有一个点就可以全部炸到的情况。
## 瑇码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10,M=150;
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
int n,m,d;char mp[N][N];
int id[N][N],cnt,xx[2*M*M],yy[2*M*M];
bitset<2*M>flag[2*M*M];bool vis[N][N];
void add(int x,int y,int id){
	int&a=::id[x][y];
	if(!a)a=++cnt,xx[a]=x,yy[a]=y;
	flag[a].set(id,1);
}
#define In(a,b) (1<=(a)&&(a)<=n&&1<=(b)&&(b)<=m)
void bfs(int x,int y,int id){
	queue<tuple<int,int,int>>q;q.push({x,y,0});
	while(q.size()){
		auto [x,y,dp]=q.front();q.pop();
		add(x,y,id);if(dp==d)continue;++dp;
		for(int i=0;i<4;i++)if(In(x+dx[i],y+dy[i])&&mp[x+dx[i]][y+dy[i]]!='X')
			q.push({x+dx[i],y+dy[i],dp});
	}
}
signed main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	
	int rats=0;
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1;i<=n;i++){
		scanf("%s",mp[i]+1);
		for(int j=1;j<=m;j++)
			rats+=mp[i][j]=='R';
	}
	if(rats>290)return puts("-1"),0;
	rats=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]=='R')bfs(i,j,++rats);
	for(int i=1;i<=cnt;i++)
		if(flag[i].count()==rats){
			for(int x=1;x<=n;x++)
				for(int y=1;y<=m;y++)
					if((x!=xx[i]||y!=yy[i])&&mp[x][y]!='X')
						return printf("%d %d %d %d\n",xx[i],yy[i],x,y),0;
			return puts("-1"),0;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]=='R'){
				queue<tuple<int,int,int>>q;q.push({i,j,0});
				while(q.size()){
					auto [x,y,dp]=q.front();q.pop();
					vis[x][y]=1;
					for(int k=1;k<=cnt;k++)
						if((flag[id[x][y]]|flag[k]).count()==rats)
							return printf("%d %d %d %d\n",x,y,xx[k],yy[k]),0;
					if(dp==d)continue;++dp;
					for(int i=0;i<4;i++)if(In(x+dx[i],y+dy[i])&&mp[x+dx[i]][y+dy[i]]!='X'&&!vis[x+dx[i]][y+dy[i]])
						q.push({x+dx[i],y+dy[i],dp});
				}
				return puts("-1"),0;
			}
}
```

---

## 作者：沉石鱼惊旋 (赞：1)

# 前言

凭什么有人觉得这题难写来着，多分析一点就很好写了/fendou

# 题目翻译

$n\times m$ 的网格，有若干个老鼠 $\tt R$。墙是 $\tt X$。普通地面是 $\tt .$。选择两个位置投放炸弹，炸弹每个时刻往四联通扩张一次。炸弹不可以越过墙。炸弹投放时间为 $0$，$d$ 秒之后炸弹就会停止扩张。问选择哪两个位置各投放一个炸弹才能让所有老鼠都被炸到。无解输出 `-1`。

要求构造的答案炸弹初始不在墙上，不可以两个炸弹初始在同一个位置。

$1\leq n,m\leq 1000$，$1\leq d\leq 8$。

# 题目思路

$d$ 很小，从这里考虑。发现一个炸弹有效范围大概是 $\mathcal O(d^2)$ 的，无遮挡的情况下曼哈顿距离小于等于 $d$ 的是可炸的。

枚举第一只老鼠周围曼哈顿距离不超过 $d$ 的格子，作为第一个炸弹的候选点。找到另一只老鼠，与第一只老鼠曼哈顿距离最大，再把它周围曼哈顿距离不超过 $d$ 的格子作为第二个炸弹的候选点。枚举所有候选点组合，搜索一遍记录炸掉的老鼠个数。

复杂度 $\mathcal O(d^6)$。极其好写。写一个 BFS 调用两次即可。

这个做法看起来有点不靠谱。~~但是他过了~~。尝试构造 hack。大概 hack 思路是有一个老鼠和第一只的距离很近，但是被封住了导致没法在规定时间炸到。曼哈顿最远的反而能被炸到。

感性理解一下，这种形式的 hack，这只老鼠本身就会成为第一个炸弹的候选点之一，肯定是会被炸到的。第一只老鼠和最远的老鼠，又可以通过枚举第二个炸弹的位置被同时炸到。不管怎样这样的做法肯定是对的。

另外我一开始用 `std::map` 存访问位置多带了 $\log$ 被卡常了。搜索的时候标记套路性地打成颜色标记即可。

# 完整代码

[CF submission 301081506](https://codeforces.com/contest/254/submission/301081506)

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
char mp[1020][1020];
vector<array<int, 2>> vec;
vector<array<int, 2>> v1;
vector<array<int, 2>> v2;
set<array<int, 2>> s;
int vis[1020][1020];
int cnt;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
bool in(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
int col;
void bfs(int x, int y)
{
    col++;
    queue<array<int, 3>> q;
    q.push({x, y, 0});
    while (!q.empty())
    {
        auto [x, y, d] = q.front();
        q.pop();
        if (vis[x][y] == col)
            continue;
        vis[x][y] = col;
        if (mp[x][y] == 'R')
            s.insert({x, y});
        if (d == k)
            continue;
        for (int i = 0; i < 4; i++)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (in(tx, ty) && mp[tx][ty] != 'X')
                q.push({tx, ty, d + 1});
        }
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cin >> mp[i][j];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] == 'R')
                vec.push_back({i, j});
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] != 'X' && abs(i - vec[0][0]) + abs(j - vec[0][1]) <= k)
                v1.push_back({i, j});
        }
    }
    int p = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (abs(vec[p][0] - vec[0][0]) + abs(vec[p][1] - vec[0][1]) <
            abs(vec[i][0] - vec[0][0]) + abs(vec[i][1] - vec[0][1]))
            p = i;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] != 'X' && abs(i - vec[p][0]) + abs(j - vec[p][1]) <= k)
                v2.push_back({i, j});
        }
    }
    for (auto [ax, ay] : v1)
    {
        for (auto [bx, by] : v2)
        {
            if (ax == bx && ay == by)
                continue;
            s.clear();
            bfs(ax, ay);
            bfs(bx, by);
            if (s.size() == vec.size())
                return cout << ax << ' ' << ay << ' ' << bx << ' ' << by << '\n', 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
```

---

## 作者：Reaepita (赞：1)

我们首先可以知道，$d$ 的范围比较小，当老鼠过多时就炸不完了，所

以当老鼠个数大于 $290$ 时直接输出 $-1$ 

我们对每只老鼠所在的位置进行 $bfs$ 向外扩展 $d$ 格，对于搜到

的每个点进行编号，并且记录这个点能炸到哪些老鼠

处理完过后直接枚举，输出答案

如下

`va[num][k]` 数组用于记录 $num$ 号点能否炸到第 $k$ 只老鼠

`vx[num] vy[num]` 分别用于记录 $num$ 号点的坐标

`reach[x][y]` 表示点 $(x,y)$ 有没有进行重新编号  

注意这道题必须要加文件输入输出，如下
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int max_rats=290;
const int maxn=1000+10;
struct node
{
	int x,y,d;
	node(int xx=0,int yy=0,int dd=0){
		x=xx,y=yy,d=dd;
	};
};
vector<node>rats;
int n,m,d,cnt_rats=0,size=0;
int map[maxn][maxn];
char s[maxn][maxn];
int reach[maxn][maxn];
int vx[max_rats*max_rats],vy[max_rats*max_rats];
bool va[max_rats*max_rats][max_rats];
bool vis[maxn][maxn];
const int dx[4]={0,1,-1,0},dy[4]={1,0,0,-1};
void put_set(int x,int y,int type)//(x,y)能炸到type号老鼠
{
	if(!reach[x][y])//未编过号
	{
		va[++size][type]=1;
		vx[size]=x;
		vy[size]=y;
		return ;
	}
	for(int i=1;i<=size;i++)
	if(vx[i]==x&&vy[i]==y){
		va[i][type]=1;
		break;
	}
}
void bfs(int type,node st)//对每只老鼠进行处理
{
	memset(vis,0,sizeof(vis));
	queue<node>q;
	q.push(st);
	vis[st.x][st.y]=1;
	while(!q.empty())
	{
		node u=q.front();
		q.pop();
		put_set(u.x,u.y,type);
		reach[u.x][u.y]=1;
		if(u.d==d)continue;
		for(int i=0;i<4;i++)
		{
			int x=u.x+dx[i],y=u.y+dy[i];
			if(x<1||x>n||y<1||y>m||vis[x][y]||map[x][y])continue;
			vis[x][y]=1;
			q.push(node(x,y,u.d+1));
		}
	}	
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ans1,ans2,find_ans=0;
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++)
		if(s[i][j]=='R')cnt_rats++;
	}
	if(cnt_rats>max_rats){printf("-1\n");return 0;}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		map[i][j]=0;
		if(s[i][j]=='X')map[i][j]=1;
		if(s[i][j]=='R')rats.push_back(node(i,j,0));
	}
	for(int i=0;i<cnt_rats;i++)
	bfs(i,rats[i]);
	if(size==1)//只有一个点能炸到老鼠
	{
		for(int i=0;i<cnt_rats;i++)
		if(va[1][i]==0)
		{
			printf("-1\n");
			return 0;
		}
		printf("%d %d ",vx[1],vy[1]);
		for(int i=1;i<=n;i++)//寻找一个与之前点不同的点
		for(int j=1;j<=m;j++)
		{
			if(map[i][j]||(i==vx[1]&&j==vy[1]))continue;
			printf("%d %d\n",i,j);
			return 0;
		}
	}
	for(int i=1;i<size;i++)
	{
		
		for(int j=i+1;j<=size;j++)//枚举能炸到老鼠的两个不同的点
		{
			find_ans=1;
			for(int k=0;k<cnt_rats;k++)
			if(va[i][k]==0&&va[j][k]==0)//有一只老鼠不能炸到
			{
				find_ans=0;
				break;
			}
			if(find_ans){
				ans1=i;
				ans2=j;
				break;
			}
		}	
		if(find_ans)break;
	}
	if(find_ans)printf("%d %d %d %d\n",vx[ans1],vy[ans1],vx[ans2],vy[ans2]);
	else printf("-1\n");
}
```

---

