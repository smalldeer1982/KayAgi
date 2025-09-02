# Good Colorings

## 题目描述

Alice suggested Bob to play a game. Bob didn't like this idea, but he couldn't refuse Alice, so he asked you to write a program that would play instead of him.

The game starts with Alice taking out a grid sheet of size $ n \times n $ , the cells of which are initially not colored. After that she colors some $ 2n $ cells with colors $ 1,2,\ldots, 2n $ , respectively, and informs Bob about these cells.

In one move, Bob can point to a cell that has not been colored yet and ask Alice to color that cell. Alice colors that cell with one of the $ 2n $ colors of her choice, informing Bob of the chosen color. Bob can make no more than $ 10 $ moves, after which he needs to find a good set of four cells.

A set of four cells is considered good if the following conditions are met:

- All the cells in the set are colored;
- No two cells in the set are colored with the same color;
- The centers of the cells form a rectangle with sides parallel to the grid lines.

## 说明/提示

In the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1887E/a2b20109a1b2b0f0b055e4119ab98ab31956ba17.png)In the second test case, cells with coordinates $ (1, 1), (1, 2), (2, 1), (2, 2) $ are initially colored by Alice in different colors.

## 样例 #1

### 输入

```
2
3
1 2
1 3
2 1
2 3
3 1
3 2

1

OK
3
1 1
1 2
1 3
2 1
2 2
2 3

OK```

### 输出

```
? 1 1

! 1 2 1 3








! 1 2 1 2```

# 题解

## 作者：樱雪喵 (赞：10)

## Description

Alice 和你玩游戏。有一个 $n\times n$ 的网格，初始时没有颜色。Alice 在游戏开始前依次给其中 $2n$ 个格子分别涂上了第 $1\sim 2n$ 种颜色，并告诉你每个颜色的位置。

接下来的每次操作，你可以选择一个未涂色的格子，由 Alice 在 $2n$ 种颜色中选择一个涂在该格子上，并告诉你该颜色。

如果在某次操作后方格图上存在四个不同颜色的点，且它们的位置形成一个平行于边线的矩形，则输出它们以获得胜利。

你至多进行 $10$ 次操作，请构造一个获胜方案。交互库自适应，也就是说 Alice 的决策与你的选择有关。

$T\le200,n\le 1000$。

## Solution

我们把网格图的行列分别看作点，把格子 $(x,y)$ 涂成颜色 $c$，看作行 $x$ 向列 $y$ 连一条边权为 $c$ 的边。  
那么这是一个左右各有 $n$ 个点的二分图，我们要找的合法矩形就是长度为 $4$ 且边权互不相同的环。

由于共有 $2n$ 个点，已经连了 $2n$ 条不相同的边，则已经连的边一定至少形成一个长度为偶数的环。考虑通过这个环构造答案。

设环上的点分别为 $a_1,a_2,\dots,a_{2k}$。每次我们考虑把这个环连一条边对半拆开：

![](https://cdn.luogu.com.cn/upload/image_hosting/llhiv9kr.png)

因为整个环上边的颜色都不相同，所以不论新连的边是什么颜色，左右两个环都至少有一个满足环上边的颜色互不相同。选择满足该条件的一侧，重复上述操作，最终一定会得到一个大小为 $4$ 的环。

由于每次令环长变为原来的一半，至多操作 $O(\log 2n)-2$ 次。

```cpp
const int N=2005;
int T,n,f[N][N];
vector<int> e[N],a,b;
stack<int> q;
int in[N],flag,vis[N];
void dfs(int u,int lst)
{
    // cerr<<u<<" "<<lst<<" "<<q.size()<<endl;
    if(flag) return;
    vis[u]=1,in[u]=1,q.push(u);
    for(auto v:e[u]) if(v^lst)
    {
        if(flag) return;
        if(in[v])
        {
            // cerr<<"v "<<v<<" "<<u<<" "<<q.size()<<endl;
            assert(q.size());
            while(q.top()!=v) a.push_back(q.top()),q.pop();
            a.push_back(v),flag=1;return;
        }
        dfs(v,u);
    }
    in[u]=0;if(!q.empty()) q.pop();
}
il void clear()
{
    // cerr<<"qwq"<<n<<endl;
    a.clear(); flag=0;
    // cerr<<"?"<<" "<<q.size()<<endl;
    while(!q.empty()) q.pop();
    // cerr<<"?"<<endl;
    for(int i=1;i<=(n<<1);i++) 
    {
        // cerr<<i<<endl;
        vis[i]=0,in[i]=0;
        for(auto v:e[i]) f[i][v]=0;
        e[i].clear();
    }
}
il int ask(int x,int y)
{
    if(x>y) swap(x,y);
    cout<<"? "<<x<<" "<<y-n<<endl;
    return read();
}
il void solve()
{
    n=read();
    for(int i=1;i<=(n<<1);i++)
    {
        int u=read(),v=read();
        e[u].push_back(v+n),e[v+n].push_back(u),f[u][v+n]=f[v+n][u]=i;
    }
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,0);
    while(a.size()>4)
    {
        int sz=a.size()-1,mid=sz/4;
        assert(sz&1); int x=a[sz-mid],y=a[mid];
        int col=ask(x,y),fg=1;
        f[x][y]=f[y][x]=col,e[x].push_back(y),e[y].push_back(x);
        for(int i=mid;i<sz-mid;i++) if(f[a[i]][a[i+1]]==col) fg=0;
        b.clear();
        if(fg) for(int i=mid;i<=sz-mid;i++) b.push_back(a[i]);
        else {for(int i=0;i<=mid;i++) b.push_back(a[i]);for(int i=sz-mid;i<=sz;i++) b.push_back(a[i]);}
        swap(a,b);
    }
    assert(a.size()==4);
    sort(a.begin(),a.end());
    cout<<"! "<<a[0]<<" "<<a[1]<<" "<<a[2]-n<<" "<<a[3]-n<<endl;
    string s;cin>>s;
    if(s=="ERROR") exit(0);
}
int main()
{
    T=read();
    while(T--) solve(),clear();
    return 0;
}
```

---

## 作者：zzzYheng (赞：7)

#### 题意：

现在有一个 $n \times n$ 的网格，初始有 $2n$ 个点有颜色，分别为 $1\sim 2n$，其他点都没有颜色。

每次你可以指定一个没有颜色的点，你的对手会选择一个 $1\sim 2n$ 中的颜色填上去。

当出现四个点 $(x_1,y_1),(x_1,y_2),(x_2,y_1),(x_2,y_2)$ 四个点颜色互不相同时，你就获胜了。

你现在要在 $10$ 次操作之内获胜。

数据范围：$n \le 1000$。

#### 思路：

首先是一个经典的网格图转二分图。

假设左部为行，右部为列，格子就是边，格子的颜色就是边的颜色（未染色的格子不存在边）。

那么有一组满足条件的四个颜色互不相同的点就等价于二分图上有一个边颜色互不相同的四元环。

考虑初始条件，网格中有 $2n$ 个颜色互不相同的格子，也就是二分图上有 $2n$ 条颜色互不相同的边。

那这个二分图上就一定会出现一个环，并且边颜色互不相同。

考虑用这个环来构造边颜色互不相同的四元环。

首先我们明确一点，二分图没有奇环，所以四元环就是这个图上可能存在的最小环。

最多能执行的操作次数是 $10$ 次，我们猜测这表示 $\log_{2} n$，所以考虑一个 $\Theta(\log n)$ 次操作的必胜策略，即每次将环长减半。

容易想到的操作方式是直接在这个环中间连一条边，将环分成两半，如下图所示：

![](https://pic.imgdb.cn/item/6572c71bc458853aeff4a0a8.jpg)

（图中黑点表示左部点，白点表示右部点，我们只能在黑点和白点间连边）

这样把环分成两半是可行的吗？显然是可行的。

因为这个环上每条边颜色互不相同，所以环的两半中至少有一半不存在与新边颜色相同的边（有相同的就取另一边），我们也就得到了一个长度减半的边颜色互不相同的环。

那么 $\Theta(\log n)$ 次操作后，我们就能得到一个长度为 $4$ （长度最小）的边颜色互不相同的环。

经实际检测，可以在 $10$ 次操作内完成构造，可以通过。

#### 总结
这道题首先是一个经典的网格图转二分图，转化为获取边颜色互不相同四元环。

然后观察到初始一定存在环，考虑用那个环构造。

最后观察到操作次数 $10$ 次以内可能是 $\log_2 n$ 的构造方式，考虑每次将环折半，然后做法就出来了。

---

## 作者：CarroT1212 (赞：2)

+ 关键词：构造，二分图。

长方形啊，一个 trick 就是转成二分图，左部点是 $x$ 轴，右部点是 $y$ 轴，那么端点 $(x,y)$ 就转化成了二分图上连接对应 $x,y$ 的的一条边，四个端点构成长方形仅当它们对应的边在图上构成了一个四元环。

那么现在题目的要求就是初始左右部点个数都为 $n$，且有 $2n$ 条颜色不同的边，然后你要往里加边直到出现四边颜色不同的四元环，同时对面怎么给新加的边随机染色。这怎么保证有解呢？

VP 的时候一路推到了这，甚至把样例的初始图都画出来了，然后死于没发现里面有个环……

显然最开始肯定能找到一个环，只是可能不是四元，那么利用好环上边颜色各不相同的性质一直做下去即可。具体地，每次将这个环对半劈，那么两半新出的环中肯定至少有一个是各边颜色不同的，再用这个砍出来的合法新环继续做直到变成四元环。操作次数为 $O(\log n)$ 左右，带小常数，可以卡进 $10$ 次。

```cpp
int n,a[N],b[N],vis[N];
vector<pii > e[N];
vector<int> vet,edg;
int dfs(int p,int f) {
	vis[p]=1;
	for (pii i:e[p]) if (i.second!=f) {
		if (!vis[i.first]) {
			int tmp=dfs(i.first,i.second);
			if (tmp) {
				if (tmp<=n*2) vet.pb(p),edg.pb(i.second);
				if (tmp==p) tmp=n*2+1;
				return tmp;
			}
		}
		else if (vis[i.first]==1) {
			return vet.pb(p),edg.pb(i.second),i.first;
		}
	}
	vis[p]=2;
	return 0;
}
void mian() {
	scanf("%d",&n);
	vet.clear(),edg.clear(),memset(vis,0,sizeof(vis));
	for (int i=1;i<=n*2;i++) e[i].clear();
	for (int i=1;i<=n*2;i++)
		scanf("%d%d",&a[i],&b[i]),e[a[i]].pb({b[i]+n,i}),e[b[i]+n].pb({a[i],i});
	for (int i=1;i<=n*2;i++) if (!vis[i]) {
		dfs(i,0);
		if (vet.size()) {
			reverse(vet.begin(),vet.end()),reverse(edg.begin(),edg.end());
			while (vet.size()>4) {
				int h1=vet.size()/2+1>>1,h2=vet.size()-h1+1,x,flg=1;
				vector<int> nw,wn;
				h1--,h2--;
				if (vet[h1]>n) cout<<"? "<<vet[h2]<<" "<<vet[h1]-n<<endl;
				else cout<<"? "<<vet[h1]<<" "<<vet[h2]-n<<endl;
				scanf("%d",&x);
				for (int i=h1;i<h2&&flg;i++) if (edg[i]==x) {
					for (int j=0;j<h1;j++) nw.pb(vet[j]),wn.pb(edg[j]);
					nw.pb(vet[h1]),wn.pb(x);
					for (int j=h2;j<vet.size();j++) nw.pb(vet[j]),wn.pb(edg[j]);
					flg=0;
				}
				if (flg) {
					for (int j=h1;j<h2;j++) nw.pb(vet[j]),wn.pb(edg[j]);
					nw.pb(vet[h2]),wn.pb(x);
				}
				vet=nw,edg=wn;
			}
			sort(vet.begin(),vet.end());
			cout<<"! "<<vet[0]<<" "<<vet[1]<<" "<<vet[2]-n<<" "<<vet[3]-n<<endl;
			string str; cin>>str;
			assert(str=="OK");
			return;
		}
	}
	assert(1);
}
```

---

## 作者：rui_er (赞：2)

萌萌交互题。

对网格图进行二分图建模，左部 $n$ 个点表示每一行，右部 $n$ 个点表示每一列。若格子 $(i,j)$ 被染成 $c$ 色，就连接 $(L_i,R_j,c)$ 的边。

由抽屉原理易证，在初始局面中至少有一个各边颜色均不同的偶环。获胜条件相当于存在一个各边颜色均不同的四元环。

讨论环长是否为四的倍数。若不为四的倍数，则询问任意一对正对面的点对应的格子；若为四的倍数，错开一位即可。（如图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/u0szc09s.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/uoz4rkum.png)

这样，我们就可以将大环划分为两个大小约为一半的小环。显然，无论询问的边被染成什么颜色，两个小环之中至少有一个不包含这种颜色。在第一个图中为左半部分，在第二个图中为右半部分。

至此，我们可以由一个各边颜色均不同的偶环，经过一次询问，得到一个规模减半的各边颜色依然不同的偶环。重复询问直到环长为四，最大询问次数不超过 $10$。

需要注意的一点是，在每组数据结束后，需要读入一行字符串 `OK`。

```cpp
// Problem: Good Colorings
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1887E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 2e3 + 5;

int T, n, col[N][N], vis[N];
vector<int> e[N], cyc;
stack<int> stk;

bool dfs(int u, int f) {
    vis[u] = 1;
    stk.push(u);
    for(int v : e[u]) {
        if(v == f || vis[v] == 2) continue;
        if(vis[v] == 1) {
            if(v <= n) cyc.push_back(v);
            while(stk.top() != v) {
                cyc.push_back(stk.top());
                stk.pop();
            }
            if(v > n) cyc.push_back(v);
            return true;
        }
        if(dfs(v, u)) return true;
    }
    vis[u] = 2;
    stk.pop();
    return false;
}

void solve() {
    cin >> n;
    rep(i, 1, 2 * n) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(n + v);
        e[n + v].push_back(u);
        col[u][n + v] = i;
        col[n + v][u] = i;
    }
    rep(i, 1, 2 * n) if(vis[i] == 0) if(dfs(i, 0)) break;
    while(cyc.size() > 4) {
        int sz = cyc.size();
        int uid = 0, vid = sz % 4 == 0 ? sz / 2 + 1 : sz / 2;
        int u = cyc[uid], v = cyc[vid], c;
        cout << "? " << u << " " << v - n << endl << flush;
        cin >> c;
        col[u][v] = col[v][u] = c;
        bool flag = true;
        rep(i, uid, vid - 1) if(col[cyc[i]][cyc[i + 1]] == c) flag = false;
        vector<int> tmp;
        if(flag) {
            rep(i, uid, vid) tmp.push_back(cyc[i]);
        }
        else {
            tmp.push_back(cyc[uid]);
            per(i, cyc.size() - 1, vid) tmp.push_back(cyc[i]);
        }
        swap(cyc, tmp);
    }
    cout << "! " << cyc[0] << " " << cyc[2] << " " << cyc[1] - n << " " << cyc[3] - n << endl << flush;
    string result;
    cin >> result;
    assert(result == "OK");
}

void clear() {
    rep(i, 1, 2 * n) {
        rep(j, 1, 2 * n) col[i][j] = 0;
        vis[i] = 0;
        e[i].clear();
    }
    cyc.clear();
    while(!stk.empty()) stk.pop();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(cin >> T; T; --T) {
        solve();
        clear();
    }
    return 0;
}
```

---

## 作者：chlchl (赞：1)

第一次写交互题就调了 2h……

~~但是不得不说挺好玩的。~~

## Solution
首先~~根据老师的提示~~有一个观察发现：$10$ 约等于 $\log 2n$，所以考虑：
- 在这个图中，什么是 $O(n)$ 级别的。
- 有什么操作可以使某个东西每次折半。

很容易想到行、列都是 $O(n)$ 级别的，所以考虑将行、列抽象成图上的节点，编号分别为 $1\sim n$、$n+1\sim 2n$，那么对于初始涂了 $r$ 号颜色的节点 $(x,y)$，连一条 $x\leftrightarrow y+n$ 的双向边，边的颜色为 $r$。

显然地，发现这是个 $2n$ 点、$2n$ 边的二分图（行行、列列不可能有直接连边），显然存在且仅存在一个环。

这个时候，涂上一个颜色相当于连一条边。结合最开始的性质 $2$，我们考虑把这个环从中间“劈开”。

![](https://cdn.luogu.com.cn/upload/image_hosting/kcpkyi38.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

就像这条红色边一样。然后会发现，无论红色边是什么颜色，总有一侧的环与它的颜色都不相同。只要选择这个环继续做相同的操作即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/xond09ah.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样环的大小每次是会折半的，只需要做 $\log 2n-2$ 次即可变成一个 $4$ 元环。

而这个 $4$ 元环就恰恰代表了一个四个顶点都不同色的长方形。

实现起来细节还是超多的……WA 了好多发，出错的点都标在注释里了。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2000 + 10;
int T, n, vis[N];
int g[N][N];
int tp, sta[N];
char okokok[N];
vector<int> path;

bool find_path(int u, int fa){
	if(vis[u] == 1){//注意此时栈内的点并非都在环内！！！！！！ 
		path.clear();
		if(u <= n)
			path.push_back(u);//保证第一个一定是行数 
		while(sta[tp] != u)
			path.push_back(sta[tp--]);
		if(u > n)
			path.push_back(u);
		return 1;
	}
	vis[u] = 1;
	sta[++tp] = u;
	for(int v=1;v<=n*2;v++){
		if(v == fa || !g[u][v] || vis[v] == 2)
			continue;
		if(find_path(v, u))
			return 1;
	}
	tp--;
	vis[u] = 2;
	return 0;
}

void solve(){
	memset(g, 0, sizeof(g));
	memset(vis, 0, sizeof(vis));
	memset(sta, 0, sizeof(sta));
	tp = 0; 
	scanf("%d", &n);
	for(int i=1,x,y;i<=2*n;i++){
		scanf("%d%d", &x, &y);
		g[x][y + n] = g[y + n][x] = i;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i] && find_path(i, i))
			break;
	while(path.size() > 4){
		int color, sz = path.size();
		int s = 0, t = (sz % 4 ? sz / 2 : sz / 2 + 1);//环的大小是4的倍数的时候会取到两行，要移动一位 
		int u = path[s], v = path[t], flag = 1;
		printf("? %d %d\n", u, v - n);
		fflush(stdout);
		scanf("%d", &color);
		g[u][v] = g[v][u] = color;//注意这里的 u,v 已经是对应行、列的编号，不用 -n、+n 啦！！！！！！ 
		vector<int> now;
		for(int i=s;i<t;i++){
			if(g[path[i]][path[i + 1]] == color){
				flag = 0;
				break;
			}
		}
		if(flag){
			for(int i=s;i<=t;i++)
				now.push_back(path[i]);
		}else{
			now.push_back(path[s]);
			for(int i=path.size()-1;i>=t;i--)
				now.push_back(path[i]);
		}
		swap(path, now);
	}
	sort(path.begin(), path.end());
	printf("! %d %d %d %d\n", path[0], path[1], path[2] - n, path[3] - n);
	fflush(stdout);
	scanf("%s", okokok);
	return ;
}

int main(){
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：WoXitao (赞：0)

## 题意：

Alice 和你玩游戏，有一个 $n\times n$ 的网格，最开始 Alice 会在其中 $2n$ 个格子涂上从 $1\sim 2n$ 不一样的颜色，接着你可以选择一个未涂有颜色的格子让 Alice 在 $2n$ 个颜色里选择一个颜色并涂上并返回她涂的颜色，你最多进行 $10$ 次操作并且构造出存在四个方格拥有不同颜色且在一个平行于网格边的矩形上。

## 解答：

将在 $(x,y)$ 涂上颜色 $c$ 可以看作在点 $x$ 和 $y$ 中间连了一条权值为 $c$ 的边，那么就变成了一个 $2n$ 节点的二分图，现在我们的操作就是在 $x,y$ 之间连一条权值未知的边，目标变成了构造出一个循环长度为4且边权不一样的环。

由于存在了 $2n$ 个点，连了 $2n$ 条边，因为二分图没有奇环，所以会出现一个偶数环，我们可以在其中间划一条边，并且端点不是同一颜色，将这个环的大小从 $l$ 分成大小约是 $\frac{l}{2}+1$ 的两个小环。

因为对于这个环上的边颜色互不一样，所以划了一条边之后至少会有一个小环上的边颜色互不一样。一直划下去就会出现目标情况。

---

## 作者：Otomachi_Una_ (赞：0)

**【题意简述】**

一个 $n\times n$ 的格子，初始由 $2n$ 个不同的各自被染了不同的颜色。你有 $10$ 次机会，每次指定一个没染色的格子，交互库会给这个格子染上 $1\sim 2n$ 中的颜色之一，要求你要找到一个四角异色长方形。

$n\leq 1000$。

**【解题思路】**

转为二分图，一个格子 $(i,j)$ 有色 $x$，就给左边 $i$ 和右边 $j$ 连上颜色为 $x$ 的边。

由于我们初始有 $2n$ 条边，所以我们一定能找到一个环。这个环有个性质就是边的颜色两两不同。

注意到我们最终只需要找一个大小为 $4$ 的边两两不同的环，于是我们每次尽可能通过依次询问加边就能得到大小约一半的更小的异色环。

我们只需要 $\mathcal O(\log n)$ 次询问就能做到这一点。

**【参考代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN=1005;
int n,col[MAXN][MAXN];bool vis[MAXN<<1];
vector<int> edg[MAXN<<1];
deque<int> q;
int ask(int x,int y){
	if(x>n) swap(x,y);
	y-=n;
	if(col[x][y]) return col[x][y];
	cout<<"? "<<x<<' '<<y<<endl;
	cin>>col[x][y];
	return col[x][y];
}
bool dfs(int u,int fa){
	vis[u]=true;q.push_back(u);
	for(int v:edg[u]){
		if(!vis[v]){
			if(dfs(v,u)) return true;
		}else if(v!=fa){
			while(q.front()!=v) q.pop_front();
			return true;
		}
	}
	q.pop_back();
	return false;
}
void solve(vector<int> cyc){
	if(cyc.size()==4){
		cout<<"! "<<cyc[0]<<' '<<cyc[2]<<' '<<cyc[1]-n<<' '<<cyc[3]-n<<endl;
		string s;cin>>s;
		return;
	}
	int l=1,r=cyc.size()-1;
	while(l+2<=r-2) l+=2,r-=2;
	int x=ask(cyc[0],cyc[l]);
	vector<int> nxt;bool flag=true;
	for(int i=0;i<l;i++) if(ask(cyc[i],cyc[i+1])==x){
		flag=false;
		break;
	}
	if(flag){
		for(int i=0;i<=l;i++) nxt.push_back(cyc[i]);
	}else{
		nxt.push_back(cyc[0]);
		for(int i=l;i<(int)cyc.size();i++) nxt.push_back(cyc[i]);
	}
	solve(nxt);
}
void solve(){
	memset(col,0,sizeof(col));memset(vis,0,sizeof(vis));
	cin>>n;
	for(int i=1;i<=2*n;i++) edg[i].clear();
	for(int i=1;i<=2*n;i++){
		int x,y;cin>>x>>y;
		col[x][y]=i;
		edg[x].push_back(y+n);
		edg[y+n].push_back(x);
	}
	vector<int> cyc;
	for(int i=1;i<=n;i++) if(!vis[i]){
		if(dfs(i,0)) break;
	}
	if(q.front()>n){
		q.push_back(q.front());
		q.pop_front();
	}
	while(!q.empty()) cyc.push_back(q.front()),q.pop_front();
	solve(cyc);
	return;
}
int main(){
	int _;cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：Prophesy_One (赞：0)

将网格图转为二分图，即对于行列分别建点，连 $2n$ 条边。

考虑极端情况下第 $2n$ 条边一定会在二分图中构成一个环，且二分图中没有奇环，所以图内一定存在偶环。

我们所求的矩阵又是一个四元环，于是我们考虑通过这个偶环来构造答案。

因为限制的操作次数极少，大概是 $\log n$ 级别的，考虑二分，每次在偶环中央连上一条边，将偶环切割成两个偶环，在这两个新的偶环中一定有一个是各边都不相同的（显然，因为原环本身就各边都不相同），再选择这个环继续递归即可。

这样递归下去，可以在 $\log n$ 次操作内得到所求的四元环。

调了很久，死因是要寻找的偶环不等于你当前栈内存的遍历序列。。。。

```cpp
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
const int N=2e3+5;
struct edge
{
	int next,to;
}e[N<<1];
bool vis[N],bz;
map<int,int> mp[N];
int n,cnt,top,topp,in[N],st[N],sta[N];
int read()
{
	int res,f=1;
	char ch;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')
	f=-1;
	res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
	res=(res<<1)+(res<<3)+(ch^48);
	return res*f;
}
void add(int x,int y)
{
	e[++cnt].next=in[x];
	e[cnt].to=y;
	in[x]=cnt;
}
void dfs(int u,int fa)
{
	if(bz)
	return;
	int i;
	int v;
	vis[u]=1;sta[++topp]=u;
	for(i=in[u];i;i=e[i].next)
	{
		if(bz)
		return;
		v=e[i].to;
		if(v==fa)
		continue;
		if(vis[v])
		{
			while(sta[topp]!=v)
			st[++top]=sta[topp--];
			st[++top]=v;
			bz=1;
			return;
		}
		dfs(v,u);
	}
	vis[u]=0;
	if(topp)
	topp--;
}
int gsk(int x,int y)
{
	if(x>y)
	swap(x,y);
	printf("? %d %d\n",x,y-n);
	fflush(stdout);
	return mp[x][y]=mp[y][x]=read();
}
void solve()
{
	int i,x,y,l,r,mid,a[7];
	n=read();
	for(i=1;i<=n*2;i++)
	{
		in[i]=0;vis[i]=0;
		mp[i].clear();
	}
	cnt=top=topp=0;
	for(i=1;i<=n*2;i++)
	{
		x=read();y=read()+n;
		add(x,y);add(y,x);
		mp[x][y]=mp[y][x]=i;
	}
	for(i=1,bz=0;i<=n*2&&!bz;i++)
	dfs(i,0);
	l=1;r=top/2;
//	printf("%d\n",top);
	while(l+1<r)
	{
		mid=(l+r)>>1;
//		printf("%d %d\n",mid,top-mid+1);
		x=gsk(st[mid],st[top-mid+1]);
		for(i=l;i<=mid-1;i++)
		if(mp[st[i]][st[i+1]]==x||
		mp[st[top-i]][st[top-i+1]]==x)
		break;
		if(i!=mid||mp[st[l]][st[top-l+1]]==x)
		l=mid;
		else
		r=mid;
	}
//	printf("%d %d ",l,r);
	a[1]=st[l];a[2]=st[r];a[3]=st[top-l+1];a[4]=st[top-r+1];
	sort(a+1,a+5);a[3]-=n;a[4]-=n;
	printf("! %d %d %d %d\n",a[1],a[2],a[3],a[4]);
	fflush(stdout);
	char ssr[7];
	scanf("%s",ssr);
	if(ssr[0]=='E')
	exit(0);
}
int main()
{
//	freopen("data.out","r",stdin);
	int T=read();
	while(T--)
	solve();
	return 0;
}
```

---

## 作者：Mars_Dingdang (赞：0)

每日一题，这一道比较套路了。

### 题目描述

Alice 和你玩游戏。有一个 $n\times n$ 的网格，初始时没有颜色。Alice 在游戏开始前依次给其中 $2n$ 个格子分别涂上了第 $1\sim 2n$ 种颜色，并告诉你每个颜色的位置。

接下来的每次操作，你可以选择一个未涂色的格子，由 Alice 在 $2n$ 种颜色中选择一个涂在该格子上，并告诉你该颜色。

如果在某次操作后方格图上存在四个不同颜色的点，且它们的位置形成一个平行于边线的矩形，则输出它们以获得胜利。

你至多进行 $10$ 次操作，请构造一个获胜方案。交互库自适应，也就是说 Alice 的决策与你的选择有关。

$T\le200,n\le 1000$。

### 思路
我们先来看 [CF1140F](https://www.luogu.com.cn/problem/CF1140F) 这道题。

在那题中，我们将行和列分别拆开，然后一个位于 $(x,y)$ 的点相当于 $x$ 行向 $y$ 列连边。

本题中我们同样套路地将网格图拆成 $n$ 个代表行的点和 $n$ 个代表列的点，一个位于 $(x,y)$ 的点表示 $x$ 向 $y$ 连边。

观察到一共有 $2n$ 个点，这样就很好理解为什么一开始给了 $2n$ 个有颜色的点，这意味着拆点得到的二分图恰好有 $2n$ 条不重复的边，这构成了一个基环森林，并且由于是二分图且没有重边，所有环的大小均为不小于 $4$ 的偶数。

考虑大小为 $4$ 的环的意义，这表明四个构成矩形的位置都有颜色，并且如果这个环一开始就存在，说明颜色互不相同。可想而知，我们的加点操作就是在一个环中间连边，而最终我们想得到的一定也是四元环。

注意到一个环中间连边会得到两个环，而由于交互库显然会选择一个合适的颜色使得较小的环不满足四种颜色互不相同，因此能利用的一定是较大的环。此时再结合 $10$ 次的操作限制和 $n=1024$，我们很容易想到应该每次从环中间一分为二，这样需要 $O(\log n)$ 次操作即可。

有一个小小的地方需要注意。当环的大小为 $4$ 的倍数时，从中间连边得到两个奇环，如下左图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/3oqq1ipf.png)

按照上方右图的办法错开一位即可。

[代码](https://codeforces.com/contest/1887/submission/243551217)。

---

