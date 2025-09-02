# Gojou and Matrix Game

## 题目描述

Marin feels exhausted after a long day of cosplay, so Gojou invites her to play a game!

Marin and Gojou take turns to place one of their tokens on an $ n \times n $ grid with Marin starting first. There are some restrictions and allowances on where to place tokens:

- Apart from the first move, the token placed by a player must be more than Manhattan distance $ k $ away from the previous token placed on the matrix. In other words, if a player places a token at $ (x_1, y_1) $ , then the token placed by the other player in the next move must be in a cell $ (x_2, y_2) $ satisfying $ |x_2 - x_1| + |y_2 - y_1| > k $ .
- Apart from the previous restriction, a token can be placed anywhere on the matrix, including cells where tokens were previously placed by any player.

Whenever a player places a token on cell $ (x, y) $ , that player gets $ v_{x,\ y} $ points. All values of $ v $ on the grid are distinct. You still get points from a cell even if tokens were already placed onto the cell. The game finishes when each player makes $ 10^{100} $ moves.

Marin and Gojou will play $ n^2 $ games. For each cell of the grid, there will be exactly one game where Marin places a token on that cell on her first move. Please answer for each game, if Marin and Gojou play optimally (after Marin's first move), who will have more points at the end? Or will the game end in a draw (both players have the same points at the end)?

## 样例 #1

### 输入

```
3 1
1 2 4
6 8 3
9 5 7```

### 输出

```
GGG
MGG
MGG```

# 题解

## 作者：sgweo8ys (赞：6)

[CF1658 其他题目题解 ](https://www.cnblogs.com/sgweo8yspace/p/16073716.html)

### 题目描述

有一个 $n \times n$ 的矩阵 $v$，其中 $v_{i, j} < n^2$ 且互不相等。

G 和 M 两人轮流取数，每个数可以被取多次，但取的位置与上一个人取的位置的曼哈顿距离不能小于等于 $k$。

M 先取，对于每个 $(i, j)$ 输出如果 M 第一步取 $v_{i,j}$，在选了好多好多步之后会是谁赢。

$n \le 2000$


### 分析

很有意思的一道题 ...

显然，一个人选了数之后，下一个人不会选比他更小的（否则第一个人可以继续选那个数）。


所以我们可以强制让每个人只选比上一个人选的数更大的数。


这样就有一个很好的性质：**不能行动者输** 。


也就是说，这是个公平组合游戏。


考虑算出 [sg 函数](https://oi-wiki.org/math/game-theory/impartial-game/#sg)。


这里我们不需要准确知道 sg 值是多少，我们只需要知道他是不是 $0$ 就行。


显然我们要按照每个点上的数字从大到小对点排序，然后依次考虑每个点的 sg 值。


假设现在考虑到了第 $i$ 个点。


那它的后继状态就是 $1$ 到 $i-1$ 中与 $i$ 的曼哈顿距离大于 $k$ 的点。


如果这些点有一个 sg 为 $0$，那第 $i$ 个点就不是 $0$。


否则它就是 $0$。


那如何考虑曼哈顿距离呢？


如图：


![](https://cdn.luogu.com.cn/upload/image_hosting/k0k2uvw9.png)


对于红色的点，与他曼哈顿距离小于等于 $k$ 的点在红色框内，红色框是一个小正方形，且每条边与矩阵的边夹角都为 $45$ 度。

大于 $k$ 的自然就是蓝色阴影部分。

由于我们要判断大于 $k$ 的区域内有没有 $0$，这显然是个可重复贡献问题，于是我们把蓝色阴影拆成四个三角形。

如图（上一张图的痕迹擦不干净了）：



![](https://cdn.luogu.com.cn/upload/image_hosting/vnp3gmcz.png)


也就是红色框四条边延长线与矩阵边界所围成的三角形。

对于一个三角形，考虑这样分析：


![](https://cdn.luogu.com.cn/upload/image_hosting/7tr0hn5d.png)


一个如图的三角形内没有 $0$ 等价于它的它的斜边的右上方的斜边（包括它自己）没有 $0$。

维护一个最右上的出现 $0$ 的斜边即可。

其他三个三角形类似。

复杂度 $O(n^2)$ （如果使用基数排序的话）。

### 代码

注：未使用基数排序，复杂度为 $O(n^2 \log n)$。

还要注意一下，sg 为 $0$ 说明面对这种情况的人无法行动，也就是创造这种情况的人赢了，所以这里 sg 为 $0$ 是说 M 选了一个数使得 G 需要面对一个 sg 为 $0$ 的情况，也就是 M 赢了。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int inf = 0x3f3f3f3f;

struct node{
    int x, y, v;
    bool operator <(const node a)const{
        return v > a.v;
    }
}a[N * N];

int n, k, m, pro[4];
char ans[N][N];

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

int main()
{
    n = read(), k = read(), m = n * n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            a[(i - 1) * n + j] = (node){i, j, read()};
    sort(a + 1, a + m + 1);

    pro[0] = pro[2] = inf, pro[1] = pro[3] = -inf;
    for(int i = 1; i <= m; i++){
        int x = a[i].x, y = a[i].y, res = 1;
        if(x - k - 1 + y >= pro[0]) res = 0;
        else if(x + k + 1 - y <= pro[1]) res = 0;
        else if(x - k - 1 - y >= pro[2]) res = 0;
        else if(x + k + 1 + y <= pro[3]) res = 0;

        if(res) ans[x][y] = 'M';// res = 1 说明 sg 是 0 ，赢的就是 M
        else ans[x][y] = 'G';

        if(res){
            pro[0] = min(pro[0], x + y), pro[1] = max(pro[1], x - y);
            pro[2] = min(pro[2], x - y), pro[3] = max(pro[3], x + y);
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++) putchar(ans[i][j]);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：Zack_zhu (赞：2)

其他大佬们都写得曼哈顿距离转切比雪夫距离，但如果不会这玩意（其实这玩意也很简单）的话这里可以给出一种几乎不用动脑的做法。(本质相同）
## 题目分析
不妨先考虑最大的数，发现 M 先手选这个数时一定能赢，只需要在 G 选其他的地方时选回来就行。  
同时我们考虑一个数，如果我后手选了比它小的数，先手一定可以选回这个数，这样一定不优。  
然后我们再看样例：
```
1 2 4
6 8 3
9 5 7
```
这里的 $7$ 是后手必胜的，原因是 M 先手选 $7$ 后 G 可以选 $9$，而 $9$ 是先手必胜的。  
同时这里的 $6$ 是先手必胜的，原因之前提到过只能选比他大的，而且 $8$ 和 $9$ 由于距离问题没有办法选择，它的后手能选到的 $7$ 是后手必胜，故它本身是先手必胜。  
以此类推，我们发现这个游戏的规则是：  
- 如果有比当前数大且距离大于 $k$ 的数，且这个点是先手必胜（答案为 M）的情况时，这个点就是后手必胜的（答案为 G），否则就是先手必胜的。（答案为 M）  

规则清楚了，我们发现比当前数大的限制可以搞个桶倒着来解决，现在唯一的限制就是这个距离大于 $k$。  
设当前点为 $(x_0,y_0)$，距离可以表示为：  
$\vert x - x_0\vert$ + $\vert y - y_0\vert$  
我们考虑拆开绝对值，发现只有 $4$ 种情况，如下：  
$x - x_0 + y - y_0$  
$x - x_0 + y_0 - y$  
$x_0 - x + y - y_0$  
$x_0 - x + y_0 - y$  
然后巧妙的是这个 $4$ 种情况的最大值是我们要求的答案，因为原来的式子是绝对值相加，这里如果有东西是负的那么肯定更小取不到。  
而其中的与 $x$，$y$ 相关的部分可以每次确定是先手必胜后 $O(1)$ 求最大值，于是整体复杂度就是 $O(n^2)$。  
当然，如果你了解曼哈顿距离转切比雪夫距离的话会发现这其实就是拆了绝对值的切比雪夫距离。（个人认为拆绝对值会更加直观）  
[code](https://codeforces.com/contest/1658/submission/227994738)

---

## 作者：shinkuu (赞：1)

简单题。只要清楚博弈策略就没啥问题了。

考虑怎么决策是优的。发现如果从一个大的 $a_{x_1,y_1}$ 走到更小的 $a_{x_2,y_2}$，下一步对方可以直接走回来 $(x_1,y_1)$，这样肯定是不优的。所以得到结论：**除非无路可走，否则不会走到比自己小的数**。

考虑从一个位置会走到哪个比自己大的数。一步走到尽可能大的数显然是可能不优的，发现这相当于变成一个有向图游戏，考虑没有出边的点为必败态，然后转移出 SG 函数值（其实不用详细值，只用知道 $0/1$ 即可）然后判断。

转移时，可以考虑能转移过来的点都是 $x+y$ 和 $x-y$ 的一段前缀或后缀。所以维护为必败态的位置的上述两个值的 $\max$ 和 $\min$ 即可。

但是作者没有想到，于是写了个 BIT，其实也是好写的。

code：

```cpp
int n,m,a[N][N],px[M],py[M];bool ans[M];
struct BIT{
	int tr[N<<1],n;
	#define lb(x) (x&(-x))
	il void upd(int x,int y){while(x<=n)tr[x]+=y,x+=lb(x);}
	il int qry(int x){int ret=0;while(x)ret+=tr[x],x-=lb(x);return ret;}
}T[2];
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)rep(j,1,n){
		scanf("%d",&a[i][j]);
		px[a[i][j]]=i,py[a[i][j]]=j;
	}
	int k=n*n;
	rep(i,0,1)T[i].n=n*2;
	drep(i,k,1){
		int x=px[i],y=py[i];
		ans[i]|=T[0].qry(max(x+y-m-1,0))+T[0].qry(n*2)-T[0].qry(min(x+y+m,n*2));
		ans[i]|=T[1].qry(max(x-y-m+n-1,0))+T[1].qry(n*2)-T[1].qry(min(x-y+m+n,n*2));
		T[0].upd(x+y,ans[i]^1),T[1].upd(x-y+n,ans[i]^1);
	}
	rep(i,1,n){
		rep(j,1,n)pc(ans[a[i][j]]?'G':'M');
		puts("");
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：RyexAwl (赞：1)

> key Observation：如果 Marin 先手下在 $(a,b)$，Gojou 紧接着下来下在了 $(c,d)$，且 $V_{(c,d)}<V_{(a,b)}$，那么 Gojou 必输。

因为 $(c,d)$ 与 $(a,b)$ 的曼哈顿距离 $>k$，所以接下来 Marin 一定还可以下在 $(a,b)$，除非存在一个时刻 Gojou 下在了比 Marin 大的位置，而如果这样的话先下在这个位置一定更优。

Gojou 下完之后 Marin 也同理。

因此考虑改写游戏规则：

* 除第一步外选定的落子位置与上一次的落子位置的曼哈顿距离 $>k$。

* 除第一步外选定的落子位置上的权值必须严格大于前一次落子位置的权值。

* 将棋盘中所有位置看成点，向所有后继状态连有向边，因为后继状态的权值严格大于当前状态的权值，所有其一定是有向边，因此本问题可以看成有向图游戏：对于有向图中每个点，求初始棋子放在该点时是否先手必胜，如果先手必胜则 Gojou 赢，否则 Marin 赢。

令 $f(i,j)$ 表示如果初始棋子放在 $(i,j)$，是否先手必胜。

为了计算出 $f(i,j)$，我们需要知道 $(i,j)$ 的所有后继状态中是否有必败状态，如果存在一个必败态则 $(i,j)$ 是必胜态，否则 $(i,j)$ 是必败态。

对于曼哈顿距离，可以将其转化为切比雪夫距离：

$$
|i-i'|+|j-j'|>k\Leftrightarrow \max(|(i+j)-(i'+j')|,|(i-j)-(i'-j')|)>k
$$

将所有位置按权值降序排序，维护当前所有必败态的 $(i+j),(i-j)$ 的 $\max$ 与 $\min$ 即可。

复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

const int N = 2005;

int f[N][N],a[N][N];

int n,k;

std::pair<int,int> mp[N * N];

char ans[N][N];

template <class T> void fr(T &a, bool f = 0, char ch = getchar()) {
    for (a = 0; ch < '0' || ch > '9'; ch = getchar()) ch == '-' ? f = 1 : 0;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) a = a * 10 + (ch - '0');
    a = f ? -a : a;
}
template <class T, class... Y> void fr(T &t, Y &... a) { fr(t), fr(a...); }
int fr() { int a; return fr(a), a; }

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    fr(n,k);
    rep(i,1,n) rep(j,1,n) fr(a[i][j]);
    rep(i,1,n) rep(j,1,n) mp[a[i][j]] = {i,j};
    int maxplus = 0xcfcfcfcf,minplus = 0x3f3f3f3f,maxde = 0xcfcfcfcf,minde = 0x3f3f3f3f;
    per(i,n*n,1) {
        auto cur = mp[i];
        int x = cur.fi + cur.se,y = cur.fi - cur.se;
        if (std::max(std::max(maxplus - x,x - minplus),std::max(maxde - y,y - minde)) > k) {
            f[cur.fi][cur.se] = 1; 
        } else {
            maxplus = std::max(maxplus,x),minplus = std::min(minplus,x);
            maxde = std::max(maxde,y),minde = std::min(minde,y); 
        }
    }
    rep(i,1,n) {
        rep(j,1,n) if (f[i][j]) ans[i][j] = 'G'; else ans[i][j] = 'M';
    }
    rep(i,1,n) {
        rep(j,1,n) putchar(ans[i][j]);
        puts("");
    }
}

}signed main(){wxy::main(); return 0;}
```


---

## 作者：JS_TZ_ZHR (赞：1)

## 题意：

给定一个矩阵。矩阵中的每一个数都不同。现在有两个玩家在玩游戏。第一轮中，第一个玩家决定棋子放哪里，接着他们轮流移动棋子。每次移动（包括第一轮的放置）后做出这个决定的玩家获得和矩阵中这个位置的数一样大的分数。分数大的最终胜利。每次移动到的格子和原来的格子曼哈顿距离大于 $k$。问对于每个格子，第一个玩家放在这里能不能获得胜利。游戏进行 $10^{100}$ 轮。

## 题解：

一个重要的性质：两个格子可以互相到达。

显然放在数最大的格子可以让第一个玩家胜利，因为无论第二个玩家怎么做他移回来就行。

接下来对于每个格子，如果玩家一放上面之后，玩家二可以把这个棋子移到最大的数上，那么玩家二可以通过复制如上策略胜利。但玩家一放在数字最大的无法到达最大的数的格子上时，由于无论玩家二如何操作，要么到一个更小的格子，要么到一个可以到达最大的数的格子上的地方。前者玩家一移回去，后者玩家一到最大的数的格子上，这个策略可以让他必胜。

以此类推，一个格子如果可以移动到先手必胜的格子上，那么这个格子先手必败，反之先手必胜。所以从最大的数开始这样考虑即可。

注意到题目中的是曼哈顿距离，所以保留上下左右四个角的点维护来保证时间复杂度。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#define N 4000005
using namespace std;
int n,k,a[2005][2005],x,y,p1[N],p2[N],cnt,tot;
char ans[2005][2005];
struct node{
	int x,y;
}p[N];
bool cmp(node u,node v){
	return a[u.x][u.y]>a[v.x][v.y];
}
void upd(){
	node tmp[5];
	for(int i=1;i<=4;i++)tmp[i].x=p1[1],tmp[i].y=p2[1];
	for(int i=2;i<=tot;i++){
		if(p1[i]+p2[i]>tmp[1].x+tmp[1].y)tmp[1].x=p1[i],tmp[1].y=p2[i];
		if(p1[i]-p2[i]>tmp[2].x-tmp[2].y)tmp[2].x=p1[i],tmp[2].y=p2[i];
		if(-p1[i]+p2[i]>-tmp[3].x+tmp[3].y)tmp[3].x=p1[i],tmp[3].y=p2[i];
		if(-p1[i]-p2[i]>-tmp[4].x-tmp[4].y)tmp[4].x=p1[i],tmp[4].y=p2[i];
	}
	tot=4;
	for(int i=1;i<=4;i++){
		p1[i]=tmp[i].x;
		p2[i]=tmp[i].y;
	}
}
signed main() {
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
			if(a[i][j]==n*n)x=i,y=j; 
			ans[i][j]='G';
		}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(abs(x-i)+abs(y-j)<=k){
				p[++cnt].x=i,p[cnt].y=j;
			}
		}
	}
	sort(p+1,p+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		bool flag=1;
		for(register int j=1;j<=tot;j++){
			if(abs(p1[j]-p[i].x)+abs(p2[j]-p[i].y)>k){
				flag=0;
				break;
			}
		}
		if(flag){
			p1[++tot]=p[i].x;
			p2[tot]=p[i].y;
			ans[p1[tot]][p2[tot]]='M';
			upd();
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			putchar(ans[i][j]);
		}
		putchar('\n');
	}
}

```


---

## 作者：xfrvq (赞：0)

显然的观察：最大值点先手必败。原因是以最大值为起点，先手怎么走后手都重新取回最大值。对应的，最大值点能一步走到的点先手必胜。

现在考虑把问题放到点集上，我们先将最大值处标记为先手必败，最大值一步能走到的点标记为先手必胜。然后把这些点删掉，得到规模更小子问题。

但这样做会漏掉一些转移：晚删掉的点是否可能转移到早删掉的点呢？考虑早删掉的点一定是当时的最大值，或当时最大值能一步走到的点。

+ 如果是前者：那么这个晚删掉的点应该是最大值一步能走到的点，不可能比最大值晚删掉。因此这种情况不存在。
+ 如果是后者：这个点一定是先手必胜，到这个点转移不优，可以略去。

注意到这个点集一定是：到一个点距离 $\le k$ 的点，即一定是一个菱形。考虑曼哈顿距离转切比雪夫距离，就变成了矩形。从大往小枚举最大值并维护点集，如果该值在当前点集内，就用来更新当前点集。

最终代码十分简单。

```cpp
const int N = 2e3 + 5;

int n,k,t,b[N * N],c[N * N],ans[N * 2][N * 2];

int main(){
	n = read(),k = read();
	for(int i = 0;i < n;++i)
		for(int j = 0,x;j < n;++j) x = read(),b[x] = i + j,c[x] = i - j + n - 1;
	int u = 0,d = n * 2 - 1,l = 0,r = n * 2 - 1;
	for(int i = n * n;i;--i) if(u <= b[i] && b[i] <= d && l <= c[i] && c[i] <= r){
		ans[b[i]][c[i]] = 1;
		u = max(u,b[i] - k),d = min(d,b[i] + k),l = max(l,c[i] - k),r = min(r,c[i] + k);
	}
	for(int i = 0;i < n;++i,puts(""))
		for(int j = 0;j < n;++j) putchar(ans[i + j][i - j + n - 1] == 1 ? 'M' : 'G');
	return 0;
}
```

---

## 作者：MiniLong (赞：0)

考虑第一次走，如果能走到 $n^2$，那么必定走。因为第二次必定会走到距离 $n^2$ $k$ 距离以外的点，下次还能走回来。所以距离 $n^2$ 这个点大于 $k$ 的点都是先手胜利。考虑在这个范围内的，显然每个人都不可能走出去这个范围，不然下次另一个人就能走到 $n^2$ 了。这就是一个子问题，还是看到这个范围内除了 $n^2$ 以外的最大值……那么最后剩下的这个范围就是先手必败的了（因为到这里必定走出这个范围，然后后手就会走到上一层的最大值）。注意到这是一个切比雪夫距离，将原来为 $(x,y)$ 的点转化为 $(x+y,x-y)$，那么原距离为 $k$ 的就是这里 $(x-k,y-k,x+k,y+k)$ 这个矩阵。从大到小枚举坐标，每次碰到一个在上次合并之后的矩阵中的点，将 $(x_i-k,y_i-k,x_i+k,y_i+k)$ 和上次那个矩阵求交作为新的矩阵。**最后的矩阵**里的点就是必败的了。复杂度 $\Theta(n^2)$。

~~好好想想为什么自己一开始在写 bit~~

---

## 作者：Qiaoqia (赞：0)

> 第一次独立做出 *2500 纪念。

一个显然的情况是如果 M 取到最大值，那肯定是他赢了，因为 G 必须取和他曼哈顿距离 $k$ 以外的，所以他一直取这个最大的就行了。

同样，如果 M 第一次取的位置和最大值所在位置曼哈顿距离大于 $k$，那么 G 直接取最大值 M 无论如何也不可能赢。  
那么考虑 M 取了和最大值曼哈顿距离在 $k$ 以内的情况，此时 G 如果不同样取和最大值在曼哈顿距离在 $k$ 以内的点，那么 M 就直接取最大值，无论 G 暂时捡了怎么样的便宜，都会被 $10^{100}$ 次的漫长时光给击败，所以 G 不能取和最大值相距 $k$ 以上的。同样如果之后某一步 M 取到外面去了，G 取到最大的也一定会获得胜利，所以 M 不会取距离最大值曼哈顿距离超过 $k$ 的点。

那么就不用考虑距离最大值曼哈顿距离 $k$ 以上的点了，可以把那些点从网格中删除变成一张新的网格。  
这时可以惊喜地发现，问题变成了一个和原问题形式相同，规模更小的问题，那么只要找到一个递归的边界就可以解决问题了。  
注意 G 的取值还有一个限制，即和 M 的曼哈顿距离必须大于 $k$，如果某一个时刻剩余的网格大小不足以给 G 这样一个选项，M 必然获得胜利。

那么就有了一个做法：对于 M 的每个开局，都这样模拟网格不断缩小的过程。  
但是这样时间复杂度太高了。可以发现对于一个范围内的所有点，棋盘缩小的过程是一样的，所以可以转换一下求答案的顺序，将所有数排序，从大到小如果点已经被删除，则标记为 G 赢，否则缩小网格。  
维护棋盘的删除可以将曼哈顿距离转换成切比雪夫距离，这样剩余网格就变成了方形，可以很方便地维护。

提交记录：[#153099044](https://codeforces.com/contest/1658/submission/153099044)。

---

