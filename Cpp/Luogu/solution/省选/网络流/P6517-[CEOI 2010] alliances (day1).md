# [CEOI 2010] alliances (day1)

## 题目描述

在一个幻想世界里，有块矩形岛屿。这座岛屿被划分成了 $R$ 行 $C$ 列的方格。

有些方格无人居住，而有些方格被以下某一种生物占据：精灵，人类，矮人或者霍比特人。占据同一格子的生物在这一格子组成了一个村庄。

为了防止恶魔的袭击，他们需要结成联盟。定义**每个村庄相邻四个方向（上下左右）的村庄**为这个村庄的邻居。

每种生物分别要满足以下条件：

- 精灵：只需要与一个邻居结盟；
- 人类：需要与两个邻居结盟，且这两个邻居不能在上下或者左右方向；
- 矮人：需要与三个邻居结盟；
- 霍比特：需要与四个邻居结盟（即所有邻居）。

你的任务是确定岛上的所有村庄是否都能与相应数量的邻居结盟（即可能会出现一些邻居并没有结盟）。如果能，则输出联盟的结构。否则输出 `Impossible!`。

**注意：结盟的关系是双向的。**

## 说明/提示

#### 数据规模与约定

- 对于 $55\%$ 的数据，保证 $\min(r,c)\le 10$；
- 对于另 $15\%$ 的数据，保证 $r\times c\le 20$；
- 对于另 $10\%$ 的数据，保证地图中只有无人区和人类；
- 对于 $100\%$ 的数据，保证 $1\le r,c\le 70$。

#### 说明

**题目译自 [CEOI 2010](http://ceoi2010.ics.upjs.sk/Contest/Tasks) day 1 *[T1 alliances](https://people.ksp.sk/~misof/ceoi2010/all-eng.pdf)***。

翻译版权为题目提供者 @[ShineEternal](https://www.luogu.com.cn/user/45475) 所有，未经许可禁止转载。



## 样例 #1

### 输入

```
3 4
2 3 2 0
3 4 3 0
2 3 3 1```

### 输出

```
............
.OXXOXXO....
.X..X..X....
.X..X..X....
.OXXOXXO....
.X..X..X....
.X..X..X....
.OXXOXXOXXO.
............```

## 样例 #2

### 输入

```
1 2
2 1```

### 输出

```
Impossible!```

# 题解

## 作者：MarchKid_Joe (赞：7)

# [P6517 [CEOI2010 day1] alliances](https://www.luogu.com.cn/problem/P6517)

## 算法

- 网络流黑白染色

## 题目

一共给出了 $4$ 种限制。

第 $1$ 种结点：与四连通的 $1$ 个邻居 Union。

第 $2$ 种结点：与四连通的 $2$ 个邻居 Union。

第 $3$ 种结点：与四连通的 $3$ 个邻居 Union。

第 $4$ 种结点：与四连通的 $4$ 个邻居 Union。

但是第 $2$ 种结点还有一个**坑**：就是不能同时与**上下**或**左右** Union。

最后输出一种可行方案。

## 思路

看到这种**配对**的问题，自然要考虑**网络流黑白染色**思想了。

规定：对于二元组 $(i,j)$，若 $i+j$ 为**奇数**，则为**黑点**；否则，为**白点**。而且：**黑点**只向**白点**连边，但是**白点**不向**黑点**连边。

### 有无解

判断是否有解只需要判断：**黑点的权值和是否等于结盟数（也就是最大流）**。

### 建图

#### 初始化

源点 $s$ 向所有**黑点**连边，权值为输入的数据。

所有**白点**向汇点 $t$ 连边，权值为输入的数据。

#### 联盟关系

分为两部分：

先考虑不包括第 $2$ 种结点的情况（~~非人类点~~）：

首先，判断黑白点，若是白点，跳过；否则：黑点向白点连边，权值为 $1$。

再考虑包括第 $2$ 种结点的情况：

发现人类比较特殊，含有两条限制：不能同时与**上下**或**左右** Union。

那我们只需要把人类拆为 $3$ 个点：第一个为初始点 $x$，第二个为管理上下方向的结点 $x_1$，第三个为管理左右的结点 $x_2$。

对于初始点，仍然限流为 $2$。

对于其他两个结点：

若此节点为**黑点**：

从初结点分别向 $x_1$ 和 $x_2$ 连接一条权值为 $1$ 的边。然后 $x_1$ 向这个结点的**上下**结点连边，权值为 $1$；$x_2$ 向这个结点的**左右**结点连边，权值为 $1$。

若此节点为**白点**：

从 $x_1$ 和 $x_2$ 分别向初结点连接一条权值为 $1$ 的边。然后这个结点的**上下**结点向 $x_1$ 连边，权值为 $1$；这个结点的**左右**结点向 $x_2$ 连边，权值为 $1$。

发现**黑白点**就是反着建图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zhiw1nl0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/ib7mpgvb.png)

#### 建图总结

源点 $s$ 向黑点连边。

白点向汇点 $t$ 连边。

黑点向白点连边。

把第 $2$ 种结点——人类拆了。

### 最大流

网络流模板。

### 统计答案

**正边没有流**或者**反边有流**则证明这条边连接的两个结点 Union。

## 提醒

注意普通点 $1,3,4$ 向人类点 $2$ 连边时**不是向初始点** $x$ 连边，而**是**向另外两个**管辖方向的点**连边。（我吃亏了）

网络流**反边**流量为 $0$。（我又吃亏了）

答案的图的大小是原图的 $3$ 倍。（我又双吃亏了）

最好将 $(1,1)$ 结点设为黑点，这样就不用特判只有一个点的情况了（不特判 $98$ 分）。因为如果 $(1,1)$ 是白点，**黑点贡献**（联盟数量）为 $0$，最大流也是 $0$，就判断为有解了，显然错误。（我又双叒吃亏了）

编号方式：

$n$ 行 $m$ 列：

对于二元组 $(i,j)$，编号为 $i\times(m-1)+j$。

对于第 $k$ 个人类的管辖方向的点，编号为 $n\times m+2\times k-x\qquad x\in[0,1]$。

统计答案时要**原图结点的坐标**，开个**桶**，下标为二元组对应的编号，内容存相应的二元组就行了。

~~这是我的编号方式。（这次没吃亏）~~

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define judge ((i + dx[k] >= 1 && j + dy[k] >= 1 && i + dx[k] <= n && j + dy[k] <= m) && (a[i + dx[k]][j + dy[k]]))
//judge 判断是否越界，是否为无人区。
const int inf = 1 << 30;
const int N = 70 + 5;
const int M = 3 * N * N;
const int s = M - 1;//原点
const int t = M - 2;//汇点
namespace IO
{
    struct type//二元组，其实就是pair<int,int>
    {
        int x, y;
        friend bool operator<(const type &A, const type &B){return A.x != B.x ? A.x < B.x : A.y < B.y;}
        type(int x = 0, int y = 0) : x(x), y(y){}
    };
    template <typename Type> void read(Type &n)
    {
        Type w=1;char x=getchar();n=0;
        while(x<'0'||x>'9'){if(x=='-')w=-1;x=getchar();}
        while(x>='0'&&x<='9'){n=(n<<1)+(n<<3)+(x^48);x=getchar();}
        n*=w;
    }
    template <typename Type,typename...Etc> void read(Type &n,Etc &...etcs)
    {
        read(n);read(etcs...);
    }
    template <typename Type> void write(Type x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) write(x/10);
        putchar(x%10+'0');
    }
}
using namespace IO;
namespace network//网络流模板，此部分不解释
{
    struct edge
    {
        int u;
        int v;
        int w;
        int nxt;
        edge(int u = 0, int v = 0, int w = 0, int nxt = 0) : u(u), v(v), w(w), nxt(nxt){}
    };
    edge e[M << 4];
    int head[M];
    int dep[M];
    int cur[M];
    int ecnt = 1;
    void add(int u, int v, int w)
    {
        e[++ecnt] = edge(u, v, w, head[u]); head[u] = ecnt;
        e[++ecnt] = edge(v, u, 0, head[v]); head[v] = ecnt;
    }
    bool bfs()
    {
        queue<int> q;
        memcpy(cur, head, sizeof(cur));
        memset(dep, 0, sizeof(dep));
        dep[s] = 1;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i; i = e[i].nxt)
            {
                int v = e[i].v;
                if (e[i].w && !dep[v])
                {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        return dep[t];
    }
    int dfs(int u, int flow)
    {
        if (u == t)
            return flow;
        int i, rest = flow;
        for (i = cur[u]; i; i = e[i].nxt)
        {
            int v = e[i].v;
            if (e[i].w && dep[v] == dep[u] + 1)
            {
                int k = dfs(v, min(e[i].w, rest));
                rest -= k;
                e[i].w -= k;
                e[i ^ 1].w += k;
                if (!rest)
                    break;
            }
        }
        cur[u] = i;
        return flow - rest;
    }
    int maxflow()
    {
        int ans = 0;
        while (bfs())
            ans += dfs(s, inf);
        return ans;
    }
}
using namespace network;
int n, m, sum;
int a[N][N], b[N * 3][N * 3];//原图和答案图，记得开 3 倍
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
//下，上，右，左
int personcnt;
//人的个数
map<type, type> person;
//人拆出来的两个管辖方向的点
map<type, bool> Union;
//判断两个点是否联合。
type point[M];
//桶存相应的点的坐标
bool black(type p)//判断是否为黑点
{
    return !((p.x + p.y) & 1);
}
int get_num(type p)//得到二元组的编号
{
    return (p.x - 1) * m + p.y;
}
void get_edge()//建边
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            read(a[i][j]);
            type now = type(i, j);
            sum += a[i][j] * black(now);
            if (black(now))//s->黑点
                add(s, get_num(now), a[i][j]);
            else//白点->t
                add(get_num(now), t, a[i][j]);
            point[get_num(now)] = now;
            if (a[i][j] == 2)
            {
                ++personcnt;//人类+1
                person[now] = type(n * m + 2 * personcnt - 1, n * m + 2 * personcnt);//拆点
                point[person[now].x] = now;
                point[person[now].y] = now;
                if (black(now))//黑点->x1,x2
                {
                    add(get_num(now), person[now].x, 1);
                    add(get_num(now), person[now].y, 1);
                }
                else//x1,x2->白点
                {
                    add(person[now].x, get_num(now), 1);
                    add(person[now].y, get_num(now), 1);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            type u = type(i, j);
            if (!black(u) || a[i][j] == 0)
                continue;//白点，无人区不连边
            for (int k = 0; k < 4; k++)
            {
                type v = type(i + dx[k], j + dy[k]);
                if (judge)
                {
                    if (a[i + dx[k]][j + dy[k]] == 2)//连向的点是人类
                    {
                        if (a[i][j] == 2)//当前点是人类
                        {
                            if (k < 2)//上下
                                add(person[u].x, person[v].x, 1);
                            else//左右
                                add(person[u].y, person[v].y, 1);
                        }
                        else//当前点是普通点
                        {
                            if (k < 2)
                                add(get_num(u), person[v].x, 1);
                            else
                                add(get_num(u), person[v].y, 1);
                        }
                    }
                    else//连向的点是普通点
                    {
                        if (a[i][j] == 2)
                        {
                            if (k < 2)
                                add(person[u].x, get_num(v), 1);
                            else
                                add(person[u].y, get_num(v), 1);
                        }
                        else
                            add(get_num(u), get_num(v), 1);
                    }
                }
            }
        }
    }
}
void get_map()
{
    for (int i = 1; i <= n * 3; i++)
        for (int j = 1; j <= m * 3; j++)
            b[i][j] = '.';//初始化全部没人
    for (int i = 2; i <= ecnt; i += 2)//Union
    {
        if (e[i].u != s && e[i].v != t && !e[i].w)
        {
            int u = get_num(point[e[i].u]);
            int v = get_num(point[e[i].v]);
            Union[type(u, v)] = true;
            Union[type(v, u)] = true;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j])//若当前不是无人区
            {
                int xl = 3 * (i - 1) + 1, xr = 3 * i;
                int yl = 3 * (j - 1) + 1, yr = 3 * j;
                int xmid = (xl + xr) >> 1, ymid = (yl + yr) >> 1;
                b[xmid][ymid] = 'O';
                for (int k = 0; k < 4; k++)
                    if (judge && Union.count(type(get_num(type(i, j)), get_num(type(i + dx[k], j + dy[k])))))//判断四个方向是否 Union
                        b[xmid + dx[k]][ymid + dy[k]] = 'X';
            }
        }
    }
}
signed main()
{
    int total = 0;
    read(n, m);
    get_edge();//建边
    if (sum != maxflow())//判断
    {
        printf("Impossible!");
        return 0;
    }
    get_map();//答案
    for (int i = 1; i <= n * 3; i++)//print
    {
        for (int j = 1; j <= m * 3; j++)
        {
            putchar(b[i][j]);
        }
        putchar('\n');
    }
    return 0;//never give up.
}
```
## 后言

感谢 @[Ptilopsis_w](https://www.luogu.com.cn/user/239167) DaLao 对本人错误思想的指出及正确思想的提供。

感谢管理员大大抽出时间审核。

---

## 作者：CaoXian (赞：4)

最大流。

---

首先，不考虑人类结盟的特殊要求，这道题如何解决？

因为结盟关系只能在相邻两个村庄之间产生，所以把村庄看作结点，结盟关系看作边，那么这将会是一张二分图。

所以可以先将地图黑白染色，将黑点看作源点，白点看作汇点，能够产生结盟关系的结点之间连一条容量为 $1$ 的边，跑一遍最大流即可得到答案。

（注意：在建源点汇点的时候要考虑这个点需要的结盟数量，这一点在多源汇转单源汇的时候就可以处理。）

接着考虑人类的特殊要求：

人类需要恰好两个结盟关系，并且不能同时上下结盟或同时左右结盟。这个要求等价于：**在上下结盟关系中选择一个，在左右结盟关系中选择一个**。

所以，可以对人类的结点拆点，分别拆为：**人类的上下结盟关系**和**人类的左右结盟关系**，这两个是新的源点（或汇点），并且其容量为 $1$。在连边的时候只连其对应到的结点即可。

剩下的部分和上面说的一样。

这道题的输出也比较麻烦冗长，但是如果理解了建模方式那么也不是难事了。

建模代码（`val` 表示这个村庄需要的结点数量，`id` 是拆点过后的点的编号，`px` 和 `py` 是每个编号对应的位置）：

```cpp
void add(int fx, int fy, int tx, int ty) {
	int f = id[fx][fy][0], t = id[tx][ty][0];
	if(val[fx][fy] == 2) {
		if(fx == tx) f = id[fx][fy][1];
		else f = id[fx][fy][2];
	}
	if(val[tx][ty] == 2) {
		if(fx == tx) t = id[tx][ty][1];
		else t = id[tx][ty][2];
	}
	add_edge(f, t, 1);
}
//下面是 main 函数里面的部分
for(int i = 1; i <= r; ++i) {
	for(int j = 1; j <= c; ++j) {
		cin >> val[i][j];
		sum += val[i][j];
		if(val[i][j]) {
			id[i][j][0] = ++cnt;
			px[id[i][j][0]] = i, py[id[i][j][0]] = j;
			if(val[i][j] == 2) {
				id[i][j][1] = ++cnt, id[i][j][2] = ++cnt;
				px[id[i][j][1]] = px[id[i][j][2]] = i;
				py[id[i][j][1]] = py[id[i][j][2]] = j;
			}
		}
	}
}
if(sum & 1) {
	cout << "Impossible!";
	return 0;
}
for(int i = 1; i <= r; ++i) {
	for(int j = 1; j <= c; ++j) {
		if(val[i][j]) {
			if((i + j) & 1) {
				add_edge(s, id[i][j][0], val[i][j]);
				if(val[i][j] == 2) {
					add_edge(id[i][j][0], id[i][j][1], 1);
					add_edge(id[i][j][0], id[i][j][2], 1);
				}
				for(int k = 0; k < 4; ++k) {
					x = i + dx[k], y = j + dy[k];
					if(x >= 1 && x <= r && y >= 1 && y <= c && val[x][y]) {
						add(i, j, x, y);
					}
				}
			}
			else {
				add_edge(id[i][j][0], t, val[i][j]);
				if(val[i][j] == 2) {
					add_edge(id[i][j][1], id[i][j][0], 1);
					add_edge(id[i][j][2], id[i][j][0], 1);
				}
			}
		}
	}
}
```

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using flow_type = ll;
constexpr int inf = 1 << 30;
int St, Ed;
struct edge {
	int to;
	flow_type c;
	int pos;
	edge(int To = 0, flow_type C = 0, int Pos = 0): to(To), c(C), pos(Pos) {}
};
vector<edge> g[15005];
void add_edge(int from, int to, flow_type c, bool directed = true) {
	// cerr << "from " << from << " to " << to << " with " << c << '\n';
	if(!c) return;
	g[from].push_back(edge(to, c));
	g[to].push_back(edge(from, directed ? 0 : c));
	g[from].back().pos = g[to].size() - 1;
	g[to].back().pos = g[from].size() - 1;
}
namespace Dinic {
	int dep[15005], cur[15005];
	queue<int> q;
	bool bfs(int s, int t) {
		fill(dep + St, dep + 1 + Ed, 0);
		dep[s] = 1;
		q.push(s);
		int now;
		while(!q.empty()) {
			now = q.front();
			q.pop();
			for(const auto& i : g[now]) {
				if(!dep[i.to] && i.c) {
					dep[i.to] = dep[now] + 1;
					q.push(i.to);
				}
			}
		}
		return dep[t];
	}
	flow_type dfs(int now, flow_type flw, const int& t) {
		if(now == t) return flw;
		flow_type rest = flw, f;
		const int len = (int)g[now].size();
		while(cur[now] < len) {
			auto& i = g[now][cur[now]];
			if(dep[i.to] == dep[now] + 1 && i.c) {
				f = dfs(i.to, min(i.c, rest), t);
				if(!f) dep[i.to] = 0;
				i.c -= f;
				g[i.to][i.pos].c += f;
				rest -= f;
				if(!rest) break;
			}
			++cur[now];
		}
		return flw - rest;
	}
	flow_type Dinic(int s, int t) {
		flow_type flow = 0;
		while(bfs(s, t)) {
			fill(cur + St, cur + 1 + Ed, 0);
			flow += dfs(s, inf, t);
		}
		return flow;
	}
}
constexpr int dx[] = {-1, 0, 1, 0};
constexpr int dy[] = {0, -1, 0, 1};
int r, c, s, t, cnt, sum, x, y, px[15005], py[15005], val[75][75], id[75][75][3];
char put[220][220];
vector<edge> v;
void add(int fx, int fy, int tx, int ty) {
	int f = id[fx][fy][0], t = id[tx][ty][0];
	if(val[fx][fy] == 2) {
		if(fx == tx) f = id[fx][fy][1];
		else f = id[fx][fy][2];
	}
	if(val[tx][ty] == 2) {
		if(fx == tx) t = id[tx][ty][1];
		else t = id[tx][ty][2];
	}
	add_edge(f, t, 1);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> r >> c;
	s = ++cnt, t = ++cnt;
	for(int i = 1; i <= r; ++i) {
		for(int j = 1; j <= c; ++j) {
			cin >> val[i][j];
			sum += val[i][j];
			if(val[i][j]) {
				id[i][j][0] = ++cnt;
				px[id[i][j][0]] = i, py[id[i][j][0]] = j;
				if(val[i][j] == 2) {
					id[i][j][1] = ++cnt, id[i][j][2] = ++cnt;
					px[id[i][j][1]] = px[id[i][j][2]] = i;
					py[id[i][j][1]] = py[id[i][j][2]] = j;
				}
			}
		}
	}
	if(sum & 1) {
		cout << "Impossible!";
		return 0;
	}
	for(int i = 1; i <= r; ++i) {
		for(int j = 1; j <= c; ++j) {
			if(val[i][j]) {
				if((i + j) & 1) {
					add_edge(s, id[i][j][0], val[i][j]);
					if(val[i][j] == 2) {
						add_edge(id[i][j][0], id[i][j][1], 1);
						add_edge(id[i][j][0], id[i][j][2], 1);
					}
					for(int k = 0; k < 4; ++k) {
						x = i + dx[k], y = j + dy[k];
						if(x >= 1 && x <= r && y >= 1 && y <= c && val[x][y]) {
							add(i, j, x, y);
						}
					}
				}
				else {
					add_edge(id[i][j][0], t, val[i][j]);
					if(val[i][j] == 2) {
						add_edge(id[i][j][1], id[i][j][0], 1);
						add_edge(id[i][j][2], id[i][j][0], 1);
					}
				}
			}
		}
	}
	St = 1, Ed = cnt;
	if(Dinic::Dinic(s, t) != (sum >> 1)) {
		cout << "Impossible!";
		return 0;
	}
	else {
		memset(put, '.', sizeof(put));
		for(int i = 1; i <= r; ++i) {
			for(int j = 1; j <= c; ++j) {
				if(val[i][j]) {
					put[(i - 1) * 3 + 2][(j - 1) * 3 + 2] = 'O';
					if((i + j) & 1) {
						v.clear();
						if(val[i][j] == 2) {
							for(const auto& k : g[id[i][j][1]]) v.push_back(k);
							for(const auto& k : g[id[i][j][2]]) v.push_back(k);
						}
						else for(const auto& k : g[id[i][j][0]]) v.push_back(k);
						for(const auto& k : v) {
							if(!k.c) {
								x = px[k.to], y = py[k.to];
								if(x == i + 1) put[(i - 1) * 3 + 3][(j - 1) * 3 + 2] = put[(x - 1) * 3 + 1][(y - 1) * 3 + 2] = 'X';
								if(x == i - 1) put[(i - 1) * 3 + 1][(j - 1) * 3 + 2] = put[(x - 1) * 3 + 3][(y - 1) * 3 + 2] = 'X';
								if(y == j + 1) put[(i - 1) * 3 + 2][(j - 1) * 3 + 3] = put[(x - 1) * 3 + 2][(y - 1) * 3 + 1] = 'X';
								if(y == j - 1) put[(i - 1) * 3 + 2][(j - 1) * 3 + 1] = put[(x - 1) * 3 + 2][(y - 1) * 3 + 3] = 'X';
							}
						}
					}
				}
			}
		}
		for(int i = 1; i <= r * 3; ++i) {
			for(int j = 1; j <= c * 3; ++j) {
				cout << put[i][j];
			}
			cout << '\n';
		}
	}
	return 0;
}
```

---

## 作者：kemingyu (赞：4)

### 思路
考虑拆点：$elves$ 就是一个单点，$human$ 拆成两个点一个向上下连边，一个向左右连边，$drawves$ 拆成五个点，中间一个向周围四个连边，$hobbits$ 就是四个点。
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 25005
using namespace std;
int m,n,tot,cnt,fst[N],pnt[N],nxt[N],a[75][75],p[75][75][4],pre[N],blg[N];
bool bo[N],mp[215][215];
void add(int x,int y,bool z)
{
	if(!z)
	{
		swap(x,y);
	}
	pnt[++tot]=y;
	nxt[tot]=fst[x];
	fst[x]=tot;
}
bool dfs(int x)
{
	int i,y;
	for(i=fst[x];i;i=nxt[i])
	{
		y=pnt[i];
		if(bo[y])
		{
			bo[y]=0;
			if(!pre[y]||dfs(pre[y]))
			{
				pre[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
void work(int x,int y)
{
	if(!x||!y)
	{
		return;
	}
	if(x>y)
	{
		swap(x,y);
	}
	int v=(x-1)%n+1,u=(x-v)/n+1;
	u=u*3-1;
	v=v*3-1;
	if(x+n==y) 
	{
		mp[u+1][v]=mp[u+2][v]=1; 
	}
	else
	{
		mp[u][v+1]=mp[u][v+2]=1;
	}
}
int main()
{
	scanf("%d%d",&m,&n);
	int i,j,k;
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
		{
			scanf("%d",&a[i][j]);
			if(!a[i][j])
			{
				continue;
			}
			if(a[i][j]==1)
			{
				p[i][j][0]=p[i][j][1]=p[i][j][2]=p[i][j][3]=++cnt;
			}
			else
			{
				if(a[i][j]==2)
				{
					p[i][j][0]=p[i][j][1]=++cnt;
					p[i][j][2]=p[i][j][3]=++cnt;
				} 
				else
				{
					for(k=0;k<4;k++)
					{
						p[i][j][k]=++cnt;
					}
					if(a[i][j]==3)
					{
						cnt++;
						for(k=0;k<4;k++)
						{
							add(p[i][j][k],cnt,i+j&1);
						}
					}						
				}
			}
		}
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			for(k=0;k<4;k++) blg[p[i][j][k]]=(i-1)*n+j;
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++) 
		{
			if(a[i][j])
			{
				if(a[i+1][j]) add(p[i][j][1],p[i+1][j][0],i+j&1);
				if(a[i][j+1]) add(p[i][j][3],p[i][j+1][2],i+j&1);
			}		
		}
	int ans=0;
	for(i=1;i<=cnt;i++)
	{
		memset(bo,1,sizeof(bo));
		if(dfs(i)) ans++;
	}
	if((ans<<1)<cnt)
	{
		puts("Impossible!");
		return 0;
	}
	for(i=1;i<=cnt;i++)
		if(pre[i]) work(blg[pre[i]],blg[i]);
	for(i=1;i<=3*m;puts(""),i++)
		for(j=1; j<=3*n;j++)
			if(i%3==2&&j%3==2&&a[i/3+1][j/3+1]) putchar('O');
			else putchar(mp[i][j]?'X':'.');
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：2)

# 一道简单的网络~~瘤~~流
[Maybe更好的阅读体验](https://chen-jia-liang.gitee.io/blog/2020/07/07/%E9%A2%98%E8%A7%A3-P6517-%E3%80%90-CEOI2010-day1-alliances%E3%80%91/)~~$\LaTeX$炸了请刷新一下~~

看到$\color{white}\colorbox{red}{\texttt{最大流}}$的标签，我们就要想着去构造合适的模型。

首先我们根据$x+y$的奇偶性把所有的坐标分成两类，打上不同的记号，整幅图就变成了这样：

![棋盘](https://cdn.luogu.com.cn/upload/image_hosting/993pqtgp.png)

~~这真的不是棋盘~~

我们看到，题目中
> 定义**每个村庄相邻四个方向（上下左右）的村庄**为这个村庄的邻居。

也就是说，同色的块之间是没有任何关系的，他们不可能是邻居。

此时若忽略```
且这两个邻居不能在上下或者左右方向```，此题就是一道简单的最大匹配问题。我们只需要
1. 将**源点$S$** 连到黑色块，流量为此块的结盟数，表示此块最多结盟的数量；
1. 将黑色块连到相邻的白色块，流量为$1$，表示他们之间最多结盟一次；
1. 将白色块连到**汇点$T$** ，流量为此块的结盟数，表示此块最多结盟的数量；
1. 若最大流量=黑块的结盟数总和，则有解，并将$\texttt{dinic}$之后流量为0的点记录下来表示结盟，否则无解

所以我们现在的问题变为如何处理使其无法在上下或者左右方向，~~根据做题的套路~~，我们知道，可以把人类拆成两个点~~好残忍~~，分别表示其左右和上下，源点分别与它们连一条流量为$1$的边，表示左右/上下都只能有$1$个，完美解决了人类的限制

## 代码
思路有了其实挺简单的，只是细节有点多
```cpp
//#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
	char get(char &c){
		c=getc();
		while(!isalpha(c))
			c=getc();
		return c;
	}
	void deal(){
		char c=getc();
		while(isalpha(c))
			c=getc();
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
const int maxn=70*70*5,maxe=1000010*2;
struct Graph{
	struct node{
		int v,w,nxt;
	}e[maxe<<1];
	int head[maxn],cur[maxn],tot;
	int dis[maxn];
	int s,t;
	void init(int _s,int _t){s=_s,t=_t;tot=1;memset(head,0,sizeof head);}
	Graph(int _s=0,int _t=0){init(_s,_t);}
	void add(int u,int v,int w){
		//printf("%d %d %d\n",u,v,w);
		e[++tot]=(node){v,w,head[u]},head[u]=tot;
		e[++tot]=(node){u,0,head[v]},head[v]=tot;
	}
	#define v e[i].v
	inline bool bfs(){
		queue<int>q;
		memset(dis,0,sizeof dis);
		memcpy(cur,head,sizeof head);
		dis[s]=1;q.push(s);
		while(q.size()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt)
				if(!dis[v]&&e[i].w){
					dis[v]=dis[u]+1,q.push(v);
					if(v==t)return true;
				}
		}
		return  false;
	}
	int dfs(int u,int flow){
		if(u==t)return flow;
		int rest=flow;
		for(int i=cur[u];i&&rest;i=e[i].nxt){
			if(dis[v]==dis[u]+1&&e[i].w){
				int tmp=dfs(v,min(rest,e[i].w));
				rest-=tmp,e[i].w-=tmp,e[i^1].w+=tmp;
			}
			cur[u]=i;
		}
		if(rest==0)dis[u]=-1;
		return flow-rest;
	}
	#undef v
	int dinic(){
		int ans=0;
		while(bfs())
			while(int sth=dfs(s,2e9))
				ans+=sth;
		return ans;
	}
}G; 
int r,c;
int a[80][80];
bool f[80][80];//标记出入
vector<int>v[80][80];
bool t[80][80][4];
int x[64000],y[64000];
int tot=0;
char ch[900][900];
vector<int> newn(int X,int Y,int len){
	vector<int>c;
	for(int i=1;i<=len;i++)
		c.push_back(++tot),x[tot]=X,y[tot]=Y;
	return c;
} 
#define LR  0
#define UD  1
signed main(){
	//freopen("1.in","r",stdin);
	in::read(r,c);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			in::read(a[i][j]);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			f[i][j]=(i+j)&1^1;
	//S连向f[i][j]为1
	//f[i][j]为1连向f[i][j]为0
	//f[i][j]为0连向T
	int sum=0;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			if(f[i][j])sum+=a[i][j];
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++){
			if(a[i][j]==2)v[i][j]=newn(i,j,2);
			else if(a[i][j])v[i][j]=newn(i,j,1);
		}
	G.init(0,++tot);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)if(a[i][j]){
			if(f[i][j]){
				if(a[i][j]==2)G.add(G.s,v[i][j][0],1),G.add(G.s,v[i][j][1],1);
				else G.add(G.s,v[i][j][0],a[i][j]);
			}
			else{
				if(a[i][j]==2)G.add(v[i][j][0],G.t,1),G.add(v[i][j][1],G.t,1);
				else G.add(v[i][j][0],G.t,a[i][j]);
			}
		}
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			if(f[i][j]&&a[i][j]){//有村庄并且为1 
				if(a[i][j]==2){
					if(a[i][j-1]){
						if(a[i][j-1]==2)G.add(v[i][j][LR],v[i][j-1][LR],1);
						else G.add(v[i][j][LR],v[i][j-1][0],1);
					}
					if(a[i][j+1]){
						if(a[i][j+1]==2)G.add(v[i][j][LR],v[i][j+1][LR],1);
						else G.add(v[i][j][LR],v[i][j+1][0],1);
					}
					if(a[i-1][j]){
						if(a[i-1][j]==2)G.add(v[i][j][UD],v[i-1][j][UD],1);
						else G.add(v[i][j][UD],v[i-1][j][0],1);
					}
					if(a[i+1][j]){
						if(a[i+1][j]==2)G.add(v[i][j][UD],v[i+1][j][UD],1);
						else G.add(v[i][j][UD],v[i+1][j][0],1);
					}
					
				}
				else{
					if(a[i][j-1]){
						if(a[i][j-1]==2)G.add(v[i][j][0],v[i][j-1][LR],1);
						else G.add(v[i][j][0],v[i][j-1][0],1);
					}
					if(a[i][j+1]){
						if(a[i][j+1]==2)G.add(v[i][j][0],v[i][j+1][LR],1);
						else G.add(v[i][j][0],v[i][j+1][0],1);
					}
					if(a[i-1][j]){
						if(a[i-1][j]==2)G.add(v[i][j][0],v[i-1][j][UD],1);
						else G.add(v[i][j][0],v[i-1][j][0],1);
					}
					if(a[i+1][j]){
						if(a[i+1][j]==2)G.add(v[i][j][0],v[i+1][j][UD],1);
						else G.add(v[i][j][0],v[i+1][j][0],1);
					}
					
				}
			} 
	if(G.dinic()!=sum)printf("Impossible!");
	else{
		#define UP 0
		#define DO 1
		#define LE 2
		#define RI 3
		for(int i=1;i<=r;i++)
			for(int j=1;j<=c;j++){
				vector<pair<int,int> >ttt;
				if(f[i][j]&&a[i][j]){
					//printf("%d %d\n",i,j);
					if(a[i][j]==2){
						for(int w=G.head[v[i][j][0]];w;w=G.e[w].nxt)
							if(G.e[w].w==0&&G.e[w].v!=G.s&&G.e[w].v!=G.t)
								ttt.push_back(make_pair(x[G.e[w].v],y[G.e[w].v]));
						for(int w=G.head[v[i][j][1]];w;w=G.e[w].nxt)
							if(G.e[w].w==0&&G.e[w].v!=G.s&&G.e[w].v!=G.t)
								ttt.push_back(make_pair(x[G.e[w].v],y[G.e[w].v]));
						
					}
					else{
						for(int w=G.head[v[i][j][0]];w;w=G.e[w].nxt)
							if(G.e[w].w==0&&G.e[w].v!=G.s&&G.e[w].v!=G.t)
								ttt.push_back(make_pair(x[G.e[w].v],y[G.e[w].v]));
						
					}
					for(vector<pair<int,int> >::iterator it=ttt.begin();it!=ttt.end();it++){
						int X=(*it).first,Y=(*it).second;
						//printf("   %d %d\n",X,Y);
						if(X==i-1){
							t[i][j][LE]=1;
							t[X][Y][RI]=1;
						}
						if(X==i+1){
							t[i][j][RI]=1;
							t[X][Y][LE]=1;
						}
						if(Y==j-1){
							t[i][j][UP]=1;
							t[X][Y][DO]=1;
						}
						if(Y==j+1){
							t[i][j][DO]=1;
							t[X][Y][UP]=1;
						}
					}
				}
			}
			
			for(int i=1;i<=3*r;i++)
				for(int j=1;j<=3*c;j++)
					ch[i][j]='.';
			for(int i=1;i<=r;i++)
				for(int j=1;j<=c;j++)
					if(a[i][j]){
						int X=3*(i-1)+2,Y=3*(j-1)+2;
						ch[X][Y]='O';
						if(t[i][j][UP])ch[X][Y-1]='X';
						if(t[i][j][DO])ch[X][Y+1]='X';
						if(t[i][j][LE])ch[X-1][Y]='X';
						if(t[i][j][RI])ch[X+1][Y]='X';
						
					}
			for(int i=1;i<=3*r;i++){
				for(int j=1;j<=3*c;j++)
					out::putc(ch[i][j]);
				out::putc('\n');
			}
	}
	out::flush();
	return 0;
}
```

---

## 作者：一扶苏一 (赞：2)

## 【最大流】【P6517】 [CEOI2010 day1] alliances

### Analysis

首先考虑如果没有人类的“两个结盟不能同时处在上下或左右方向”应该怎么做：

如果以邻居关系连边，那么建出的图显然是一个二分图。邻居之间左部点向右部点连一条流量为 $1$ 的边，源点分别向左部点连以该点所需要的结盟数为流量的边，右部点向汇点同理连边，跑最大流即可求出每个节点是否能达到结盟数要求。check 图上左右部点之间的边是否在参量网络上有流量即可输出方案。

考虑加入了人类的限制：

注意到人类的两个结盟一定是两个方向各一个，也即横向有一个结盟，纵向有一个结盟。因此将人类拆成两个点，一个点表示横向结盟，一个点表示纵向结盟即可。

### Code

实现的时候不要忘记因为人类会被拆成两个点，所以总点数应该大约是 $r \times c \times 2$，不要把乘二落下。

```cpp
namespace Fusu {

const int maxt = 75;
const int maxn = 100050;
const int INF = 0x3f3f3f3f;

void Init();
void Solve();

void Main() {
  Init();
  Solve();
}

int r, c, n, s, t, aa, bb;

int a[maxt][maxt], id[maxt][maxt];
std::pair<int, int> pos[maxn];

struct Edge {
  int v, f;
  Edge *nxt, *bk;
};
Edge *hd[maxn];
inline void cont(const int u, const int v, const int w) {
  auto x = new Edge({v, w, hd[u], nullptr}), y = new Edge({u, 0, hd[v], nullptr});
  hd[u] = y->bk = x;
  hd[v] = x->bk = y;
}

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

void Init() {
  qr(r); qr(c);
  s = 2 * r * c + 1; t = s + 1;
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      qr(a[i][j]);
      if (a[i][j] == 0) continue;
      pos[id[i][j] = ++n] = std::make_pair(i, j);
      bool isleft = (i & 1) == (j & 1);
      for (int k = 0, p, q; k < 2; ++k) {
        if ((a[i][j] == 2) && (k == 1)) {
          pos[++n] = std::make_pair(i, j);
        }
        if ((p = (i + dx[k])) && (q = j + dy[k]) && a[p][q]) {
          int o = id[p][q];
          if ((k == 1) && (a[p][q] == 2)) ++o;
          if (isleft) {
            cont(n, o, 1);
          } else {
            cont(o, n, 1);
          }
        }
      }
      if (a[i][j] != 2) {
        if (isleft) {
          cont(s, n, a[i][j]);
          aa += a[i][j];
        } else {
          cont(n, t, a[i][j]);
          bb += a[i][j];
        }
      } else {
        if (isleft) {
          cont(s, n, 1);
          cont(s, n - 1, 1);
          aa += 2;
        } else {
          cont(n, t, 1);
          cont(n - 1, t, 1);
          bb += 2;
        }
      }
    }
  }
}

std::queue<int> Q;
int dist[maxn];
Edge *tmp[maxn];
bool bfs() {
  Q.push(s);
  memset(dist, -1, sizeof dist);
  dist[s] = 0;
  for (int u, d, v; !Q.empty(); Q.pop()) {
    d = dist[u = Q.front()] + 1;
    for (auto e = tmp[u] = hd[u]; e; e = e->nxt) if ((e->f > 0) && (dist[v = e->v] == -1)) {
      dist[v] = d;
      Q.push(v);
    }
  }
  return dist[t] != -1;
}

int dfs(const int u, int f) {
  if (u == t) return f;
  int ret = 0;
  int v, d = dist[u] + 1, k;
  for (auto &e = tmp[u]; e; e = e->nxt) if ((dist[v = e->v] == d) && (e->f > 0)) {
    k = dfs(v, std::min(e->f, f));
    ret += k;
    e->f -= k;
    e->bk->f += k;
    if ((f -= k) == 0) break;
  }
  return ret;
}

bool lnk[maxt][maxt][maxt][maxt];
char opt[maxt][maxt][3][3];
void Solve() {
  if (aa != bb) {
    puts("Impossible!");
    return;
  }
  int ans = 0;
  while (bfs()) ans += dfs(s, INF);
  if (ans != aa) {
    puts("Impossible!");
    return;
  }
  for (auto e = hd[s]; e; e = e->nxt) {
    int u = e->v, x = pos[u].first, y = pos[u].second;
    for (auto ee = hd[u]; ee; ee = ee->nxt) if (ee->f == 0) {
      int p = pos[ee->v].first, q = pos[ee->v].second;
      lnk[x][y][p][q] = lnk[p][q][x][y] = true;
    }
  }
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      for (int k = 0; k < 3; ++k) {
        for (int h = 0; h < 3; ++h) {
          opt[i][j][k][h] = '.';
        }
      }
      if (a[i][j]) opt[i][j][1][1] = 'O';
      for (int k = 0, x, y; k < 4; ++k) {
        x = i + dx[k]; y = j + dy[k];
        if ((x == 0) || (y == 0) || (x > r) || (y > c)) continue;
        if (lnk[i][j][x][y]) {
          opt[i][j][1 + dx[k]][1 + dy[k]] = 'X';
        }
      }
    }
  }
  for (int i = 1; i <= r; ++i) {
    for (int k = 0; k < 3; ++k) {
      for (int j = 1; j <= c; ++j) {
        for (int h = 0; h < 3; ++h) {
          putchar(opt[i][j][k][h]);
        }
      }
      putchar('\n');
    }
  }
}

} // namespace Fusu
```





---

## 作者：AIskeleton (赞：1)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16333922.html)

网络流，但是大模拟。

> [P6517 [CEOI2010 day1] alliances](https://www.luogu.com.cn/problem/P6517)

> 题面有点长，不放了。

首先，题目给出的是一个**方格图**，而且连边是在**相邻四个方向（上下左右）**之间。

所以可以对方格图进行**黑白染色**，这样相同颜色的点之间就不会连边。

先考虑没有人类连边的限制，则直接跑二分图多重匹配即可。

建图方法（其中的点都不是空地）：
- 源点向每个黑点连边，容量为当前黑点需要连边数。
- 每个黑点向周围四个点连容量为 1 的边。
- 每个白点向汇点连边，容量为当前白点所需连边数。

可以想到，人类的连边方法一定是一横一竖。

所以只要把每个表示人类的点拆成两个点，一个点只横向连边，另一个点只竖向连边即可。拆成的点的连边**容量要减半**。

如果满流说明有解。
输出方案就遍历所有边查看匹配情况。

思路不算特别恶心，但具体实现细节很多，码量也比较大。
```cpp
#include <bits/stdc++.h>
using namespace std;
int rd(){
	int v=1,w=0;char c=getchar();while(c<'0'||c>'9'){if(c=='-')v=-1;c=getchar();}
	while(c>='0'&&c<='9')w=(w<<1)+(w<<3)+(c&15),c=getchar();return w*v;
}void wr(int x){if(x<0)putchar('-'),x=-x;if(x>9)wr(x/10);putchar(x%10+'0');}
const int N=2003,INF=2e9;
int n,m,st,ed,tot,ans,sum;
int a[N][N],f[N][N],bh[N][N][2];
char out[N][N];

int fir[N<<6],cnt=1;
struct E{int v,w,nt;}e[N*10000];
void I(int u,int v,int w){
	e[++cnt]=(E){v,w,fir[u]};fir[u]=cnt;
	e[++cnt]=(E){u,0,fir[v]};fir[v]=cnt;
}void init(){memset(e,0,sizeof(e));cnt=1;memset(fir,0,sizeof(fir));}

int cur[N*1000],d[N*1000];queue <int>q;
bool bfs(){
	memset(d,0,sizeof(d));
	for(int i=0;i<=ed;i++)	cur[i]=fir[i];
	q.push(st);d[st]=1;
	while(q.size()){
		int u=q.front(),V;q.pop();
		for(int i=fir[u];i;i=e[i].nt)
			if(e[i].w&&!d[V=e[i].v])
				q.push(V),d[V]=d[u]+1;
	}return d[ed];
}int dfs(int u,int fl){
	if(u==ed)return fl;int f,V,s=0;
	for(int i=cur[u];i;i=e[i].nt){
		cur[u]=i;
		if(e[i].w&&d[V=e[i].v]==d[u]+1){
			f=dfs(V,min(fl,e[i].w));
			e[i].w-=f;e[i^1].w+=f;
			s+=f;fl-=f;if(!fl)break;
		}
	}if(!s)d[u]=0;return s;
}int dinic(){int ans=0;while(bfs())ans+=dfs(st,INF);return ans;}

int main(){
	n=rd(),m=rd();st=n*m*2+99,ed=n*m*2+100;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=rd();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]=(i+j)&1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j])
				bh[i][j][0]=++tot;
			if(a[i][j]==2)
				bh[i][j][1]=++tot;
		}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(!a[i][j])continue;
			if(f[i][j]){
				if(a[i][j]==2)
					I(bh[i][j][0],ed,1),I(bh[i][j][1],ed,1);
				else
					I(bh[i][j][0],ed,a[i][j]);
			}else{
				sum+=a[i][j];
				if(a[i][j]==2)
					I(st,bh[i][j][0],1),I(st,bh[i][j][1],1);
				else
					I(st,bh[i][j][0],a[i][j]);
				if(a[i][j]==2){
					if(a[i+1][j])
						I(bh[i][j][0],bh[i+1][j][0],1);
					if(a[i-1][j])
						I(bh[i][j][0],bh[i-1][j][0],1);
					if(a[i][j+1])
						if(a[i][j+1]==2)
							I(bh[i][j][1],bh[i][j+1][1],1);
						else
							I(bh[i][j][1],bh[i][j+1][0],1);
					if(a[i][j-1])
						if(a[i][j-1]==2)
							I(bh[i][j][1],bh[i][j-1][1],1);
						else
							I(bh[i][j][1],bh[i][j-1][0],1);
				}else{
					if(a[i+1][j])
						I(bh[i][j][0],bh[i+1][j][0],1);
					if(a[i-1][j])
						I(bh[i][j][0],bh[i-1][j][0],1);
					if(a[i][j+1])
						if(a[i][j+1]==2)
							I(bh[i][j][0],bh[i][j+1][1],1);
						else
							I(bh[i][j][0],bh[i][j+1][0],1);
					if(a[i][j-1])
						if(a[i][j-1]==2)
							I(bh[i][j][0],bh[i][j-1][1],1);
						else
							I(bh[i][j][0],bh[i][j-1][0],1);
				}
			}
		}
	if(dinic()<sum){
		puts("Impossible!");
		return 0;
	}
	for(int i=1;i<=n*3;i++)
		for(int j=1;j<=m*3;j++)
			out[i][j]='.';
	for(int i=1,x=2;i<=n;i++,x+=3){
		for(int j=1,y=2;j<=m;j++,y+=3){
			if(a[i][j])out[x][y]='O';
			else continue;
			if(f[i][j])continue;
			if(a[i][j]==2){
				for(int k=fir[bh[i][j][0]];k;k=e[k].nt){
					if((e[k].v==bh[i+1][j][1]||e[k].v==bh[i+1][j][0])&&!e[k].w)
						out[x+1][y]='X',out[x+2][y]='X';
					if((e[k].v==bh[i-1][j][1]||e[k].v==bh[i-1][j][0])&&!e[k].w)
						out[x-1][y]='X',out[x-2][y]='X';
				}for(int k=fir[bh[i][j][1]];k;k=e[k].nt){
					if((e[k].v==bh[i][j+1][1]||e[k].v==bh[i][j+1][0])&&!e[k].w)
						out[x][y+1]='X',out[x][y+2]='X';
					if((e[k].v==bh[i][j-1][1]||e[k].v==bh[i][j-1][0])&&!e[k].w)
						out[x][y-1]='X',out[x][y-2]='X';
				}
			}else{
				for(int k=fir[bh[i][j][0]];k;k=e[k].nt){
					if((e[k].v==bh[i+1][j][1]||e[k].v==bh[i+1][j][0])&&!e[k].w)
						out[x+1][y]='X',out[x+2][y]='X';
					if((e[k].v==bh[i-1][j][1]||e[k].v==bh[i-1][j][0])&&!e[k].w)
						out[x-1][y]='X',out[x-2][y]='X';
					if((e[k].v==bh[i][j+1][1]||e[k].v==bh[i][j+1][0])&&!e[k].w)
						out[x][y+1]='X',out[x][y+2]='X';
					if((e[k].v==bh[i][j-1][1]||e[k].v==bh[i][j-1][0])&&!e[k].w)
						out[x][y-1]='X',out[x][y-2]='X';
				}
			}
		}
	}for(int i=1;i<=n*3;i++){
		for(int j=1;j<=m*3;j++)
			putchar(out[i][j]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：gyyyyx (赞：0)

看到网格图，首先想到二分图。

将网格黑白染色，则白点只能和黑点结盟。

假设人类没有其它限制，也就是人类可以和任意两个邻居结盟。

如果我们让白点向相邻的黑点连边，可以发现精灵需要匹配一个黑点，人类需要匹配两个白点……

容易想到二分图最大匹配。

建源汇点 $S,T$，让 $S$ 向白点连边，容量为白点的类型（精灵为 $1$，人类为 $2$……），让黑点向 $T$ 连边，容量同理，同时相邻白点黑点间连容量为 $1$ 的边。

则跑一遍最大流，若能跑到满流则输出方案，否则无解。

现在加上“与人类结盟的两个邻居不能在同时在上下或者左右方向”这个限制（~~人类的 b 事怎么这么多~~）。

观察人类能结盟的四种方式，可以发现必须在上下选一个方向结盟，在左右选一个方向结盟。

那我们可以考虑拆点，将代表人类的点拆成两个，一个代表上下方向，一个代表左右方向。

则只需要让 $S$ 向这两个点连容量为 $1$ 的边，或让这两点向 $T$ 连容量为 $1$ 的边。

这段说起来比较容易但写起来没这么简单。

还有输出方案就是找到连接非源汇点的、满流的边，那么这两个点就是相互结盟的。

点数最大的情况是全图人类，为 $4rc$ 个，边数同理，为 $16rc$ 条。

二分图最大匹配是 $O(N\sqrt{M})$，放到这里就是 $O(rc\sqrt{rc})$，常数略大，但跑起来还是很快的。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 9805
#define M 80005
using namespace std;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
int r,c,type[75][75],sum1,sum2;
int tot,id[75][75],nx[N],ny[N];
int s,t;
struct Edge{
	int nxt,to,flw;
	Edge(int a=0,int b=0,int c=0)
	:nxt(a),to(b),flw(c){}
} e[M];
int head[N],cnt(1);
inline void AddEdge(int u,int v,int f){
	e[++cnt]=Edge(head[u],v,f);head[u]=cnt;
	e[++cnt]=Edge(head[v],u,0);head[v]=cnt;
}
inline void Build(int u,int vx,int vy,bool flg){
	if(!type[vx][vy]) return;
	if(type[vx][vy]^2) AddEdge(u,id[vx][vy],1);
	else AddEdge(u,id[vx][vy]+flg,1);
}
int dis[N],vis[N],cur[N];
queue <int> q;
inline bool BFS(){
	for(int i(s);i<=t;++i) dis[i]=INF;
	dis[s]=0;q.push(s);
	while(!q.empty()){
		int u(q.front());q.pop();
		for(int i(head[u]);i;i=e[i].nxt){
			if(!e[i].flw) continue;
			int v(e[i].to);
			if(dis[v]==INF) dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t]<INF;
}
int DFS(int u,int limit){
	if(u==t||!limit) return limit;
	vis[u]=1;int f(0);
	for(int i(cur[u]);i&&limit;i=e[i].nxt){
		cur[u]=i;
		if(!e[i].flw) continue;
		int v(e[i].to);
		if(!vis[v]&&dis[v]==dis[u]+1){
			int tmp(DFS(v,min(limit,e[i].flw)));
			e[i].flw-=tmp;e[i^1].flw+=tmp;
			limit-=tmp;f+=tmp;
		}
	}
	if(f) vis[u]=0;
	return f;
}
inline int Dinic(){
	int ans(0),res;
	while(BFS()){
		for(int i(s);i<=t;++i) vis[i]=0,cur[i]=head[i];
		while((res=DFS(s,INF))>0) ans+=res;
	}
	return ans;
}
bool fr[75][75][3][3];
char ans[215][215];
inline void Solve(int u){
	for(int i(head[u]);i;i=e[i].nxt){
		if(e[i].flw) continue;
		int v(e[i].to),dx(nx[v]-nx[u]),dy(ny[v]-ny[u]);
		fr[nx[u]][ny[u]][1+dx][1+dy]=1;
		fr[nx[v]][ny[v]][1-dx][1-dy]=1;
	}
}
int main(){
	scanf("%d%d",&r,&c);
	for(int i(1);i<=r;++i)
		for(int j(1);j<=c;++j){
			scanf("%d",&type[i][j]);
			id[i][j]=++tot;nx[tot]=i;ny[tot]=j;
			if(type[i][j]==2) nx[++tot]=i,ny[tot]=j;
		}
	s=0;t=tot+1;
	for(int i(1);i<=r;++i){
		tot=i&1;
		for(int j(1);j<=c;++j,tot^=1){
			if(!type[i][j]) continue;
			if(tot&1){
				sum1+=type[i][j];
				if(type[i][j]^2){
					AddEdge(s,id[i][j],type[i][j]);
					for(int k(0);k<4;++k) Build(id[i][j],i+dx[k],j+dy[k],k>1);
				}
				else{
					AddEdge(s,id[i][j],1);
					for(int k(0);k<2;++k) Build(id[i][j],i+dx[k],j+dy[k],0);
					AddEdge(s,id[i][j]+1,1);
					for(int k(2);k<4;++k) Build(id[i][j]+1,i+dx[k],j+dy[k],1);
				}
			}
			else{
				sum2+=type[i][j];
				if(type[i][j]^2) AddEdge(id[i][j],t,type[i][j]);
				else{
					AddEdge(id[i][j],t,1);
					AddEdge(id[i][j]+1,t,1);
				}
			}
		}
	}
	if(sum1^sum2) puts("Impossible!");
	else{
		if(Dinic()^sum1) puts("Impossible!");
		else{
			for(int i(1);i<=r;++i){
				tot=i&1;
				for(int j(1);j<=c;++j,tot^=1)
					if(type[i][j]&&(tot&1)){
						Solve(id[i][j]);
						if(type[i][j]==2) Solve(id[i][j]+1);
					}
			}
			for(int i(1);i<=r;++i)
				for(int j(1);j<=c;++j){
					ans[i*3-2][j*3-2]='.';
					ans[i*3-2][j*3-1]=(fr[i][j][0][1]?'X':'.');
					ans[i*3-2][j*3]='.';
					ans[i*3-1][j*3-2]=(fr[i][j][1][0]?'X':'.');
					ans[i*3-1][j*3-1]=(type[i][j]?'O':'.');
					ans[i*3-1][j*3]=(fr[i][j][1][2]?'X':'.');
					ans[i*3][j*3-2]='.';
					ans[i*3][j*3-1]=(fr[i][j][2][1]?'X':'.');
					ans[i*3][j*3]='.';
				}
			for(int i(1);i<=r*3;++i) printf("%s\n",ans[i]+1);
		}
	}
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

网络流模板题。容易看出，结盟关系是在相邻两个格子之间的，所以可以黑白二染色。

如果人没有那个奇怪的限制，很容易想到把黑格子放在左边，白格子放在右边，分别向源汇点连容量为 $a_{i,j}$ 的边，跑最大流之后看看所有与源汇点相连的边是否满流。

考虑一个人必定是上下找一个盟友，左右找一个盟友。于是把一个人拆成两个点，分别表示掌管上下盟友~~的神~~和掌管左右盟友。

输出的时候判断黑白格子间哪些边是满流的即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=70+5,MAXV=MAXN*MAXN*2,MAXE=MAXV*20,dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};
int n,m,s,t,tot=1,tmp,al,a[MAXN][MAXN],id[MAXN][MAXN],hd[MAXV],cur[MAXV],dis[MAXV];
struct Edge {int to,nxt,w;}edge[MAXE];
void add_edge(int u,int v,int w) {
	edge[++tot]={v,hd[u],w},hd[u]=tot;
	edge[++tot]={u,hd[v],0},hd[v]=tot;
	return ;	
}
int bfs(void) {
	memset(dis,-1,sizeof(dis));
	queue<int> q; dis[s]=0,q.push(s);
	while(!q.empty()) {
		int u=q.front(); q.pop();
		cur[u]=hd[u];
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,w=edge[i].w;
			if(!w||dis[to]!=-1) continue ;
			dis[to]=dis[u]+1,q.push(to);
		}
	}
	return dis[t]!=-1;
}
int dinic(int u,int mx) {
	if(u==t) return mx;
	int res=0;
	for(int i=cur[u];i;i=edge[i].nxt) {
		cur[u]=i;
		int to=edge[i].to,w=edge[i].w;
		if(!w||dis[to]!=dis[u]+1) continue ;
		int tmp=dinic(to,min(mx,w));
		if(tmp) {
			mx-=tmp,res+=tmp,edge[i].w-=tmp,edge[i^1].w+=tmp;
			if(mx==0) break ;
		} else dis[to]=-1;
	}
	return res;
}
vector<int> ans[3];
void add(int id,int x,int y,int z) {
	ans[id].push_back(x),ans[id].push_back(y),ans[id].push_back(z);
	return ;	
}
int G[MAXN*MAXN][MAXN*MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) ffor(j,1,m) cin>>a[i][j],al+=a[i][j],id[i][j]=(i-1)*m+j;
	t=n*m*2+1;
	ffor(i,1,n) ffor(j,1,m) {
		if(!a[i][j]) continue ;
		if(a[i][j]==2) {
			if((i+j)&1) add_edge(s,id[i][j],1),add_edge(s,id[i][j]+n*m,1);
			else add_edge(id[i][j],t,1),add_edge(id[i][j]+n*m,t,1);
		}
		else {
			if((i+j)&1) add_edge(s,id[i][j],a[i][j]);
			else add_edge(id[i][j],t,a[i][j]);	
		}
		if((i+j)&1) {
			ffor(dir,1,4) {
				int x=i+dx[dir],y=j+dy[dir];
				if(x<1||y<1||x>n||y>m) continue ;
				if(dir<=2) add_edge(id[i][j],id[x][y],1);
				else {
					add_edge(n*m+id[i][j],n*m+id[x][y],1);
					if(a[x][y]!=2&&a[i][j]!=2) add_edge(id[i][j],id[x][y],1);
					if(a[i][j]!=2) add_edge(id[i][j],id[x][y]+n*m,1);
					if(a[x][y]!=2) add_edge(n*m+id[i][j],id[x][y],1);
				}
			}
		}
	}
	int mzx=0;
	while(bfs()) while(tmp=dinic(s,1000000)) mzx+=tmp;
	if(al!=mzx*2) cout<<"Impossible!";
	else {
		ffor(i,1,n) ffor(j,1,m) {
			if((i+j)&1) {
				int u=id[i][j];
				for(int i=hd[u];i;i=edge[i].nxt) {
					int to=edge[i].to,w=edge[i].w;
					if(!w&&to!=s) {
						int v=to;
						if(v>n*m) v-=n*m;
						G[u][v]=G[v][u]=1;
					}
				}
				for(int i=hd[u+n*m];i;i=edge[i].nxt) {
					int to=edge[i].to,w=edge[i].w;
					if(!w&&to!=s) {
						int v=to;
						if(v>n*m) v-=n*m;
						G[u][v]=G[v][u]=1;
					}
				}
			}
		}
		ffor(i,1,n) {
			ans[0].clear(),ans[1].clear(),ans[2].clear();
			ffor(j,1,m) {
				if(!a[i][j]) add(0,0,0,0),add(1,0,0,0),add(2,0,0,0);	
				else add(0,0,G[id[i][j]][id[i-1][j]],0),add(1,G[id[i][j]][id[i][j-1]],2,G[id[i][j]][id[i][j+1]]),add(2,0,G[id[i][j]][id[i+1][j]],0);
			}
			for(auto v:ans[0]) {
				if(v==0) cout<<'.';
				if(v==2) cout<<'O';
				if(v==1) cout<<'X';	
			}
			cout<<'\n';
			for(auto v:ans[1]) {
				if(v==0) cout<<'.';
				if(v==2) cout<<'O';
				if(v==1) cout<<'X';	
			}
			cout<<'\n';
			for(auto v:ans[2]) {
				if(v==0) cout<<'.';
				if(v==2) cout<<'O';
				if(v==1) cout<<'X';	
			}
			cout<<'\n';
		}
	}
	return 0;
}
```

---

