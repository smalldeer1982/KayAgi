# [CEOI 2019] Building Skyscrapers

## 题目描述

在 2D 平面上，有 $n$ 个计划建摩天楼的格子，第 $i$ 座计划建的摩天楼的格子位于 $(r_i,c_i)$。

您可以选择任意一种建摩天楼的顺序，但是要满足如下设定：

- 设建摩天楼的顺序为 $s$。
- 对于任意 $2\le i\le n$，都要保证，第 $s_i$ 座至少和前面任意一座摩天楼有公共边或公共角。
- 对于任意 $1\le i\le n$，都要保证，从第 $s_i$ 座计划建摩天楼的格子到 2D 平面的边界，有路径相连（从一个格子只能走到与其有公共边的格子），且路径上除第 $s_i$ 座摩天楼无其他摩天楼。

同时会输入一个 $t$，表示输出的类别：

- 若 $t=1$，您需要构造任意一种建造的顺序。
- 若 $t=2$，您需要构造 $(s_n, s_{n - 1}, \dots, s_1)$ 字典序最大的建造顺序。

## 说明/提示

#### 样例解释

#### 样例 1 解释

这是三个摩天楼连成一行，自然有如下几种解：

- $1,2,3$
- $2,1,3$
- $2,3,1$
- $3,2,1$

因为 $t=2$，所以输出第一种。

#### 样例 2 解释

和样例 1 的区别只是三个摩天楼连成一条对角线，与样例 1 的解一致，又因为 $t=1$，随便输出一组即可。

#### 样例 3 解释

两个摩天楼无相交部分，自然无法建立。
#### 数据范围
对于 $100\%$ 的数据，保证 $1\le n\le 1.5\times 10^5$，$1\le t\le 2$，$\lvert r_i \rvert,\lvert c_i \rvert\le 10^9$。

详细子任务限制及分值如下表：

| 子任务编号 | 限制 | 分值 |
| :-: |:-:|:-:|
| 1 | $t=1$ 且 $n\le 10$ | $8$ | 
| 2 | $t=1$ 且 $n\le 200$ | $14$ | 
| 3 | $t=1$ 且 $n\le 2\times 10^3$ | $12$ | 
| 4 | $t=2$ 且 $n\le 2\times 10^3$ | $17$ | 
| 5 | $t=1$ | $20$ | 
| 6 | $t=2$，$n\le 7\times 10^4$ 且 $\lvert r_i \rvert,\lvert c_i \rvert\le 900$ | $10$ | 
| 7 | $t=2$ | $19$ | 
#### 说明
本题译自 [Central-European Olympiad in Informatics 2019](https://ceoi.sk/) [Day 1](https://ceoi.sk/tasks/) [T1 Building Skyscrapers](https://ceoi.sk/static/statements/skyscrapers-ENG.pdf)。

## 样例 #1

### 输入

```
3
2
0 0
0 1
0 2```

### 输出

```
YES
1
2
3
```

## 样例 #2

### 输入

```
3
1
0 0
1 1
2 2```

### 输出

```
YES
2
3
1```

## 样例 #3

### 输入

```
2
1
0 0
0 2
```

### 输出

```
NO```

# 题解

## 作者：Cute__yhb (赞：1)

## 前言

社贡掉没了，来写篇题解。

这题是山东三轮省集某天模拟赛搬的题。

## 思路

注意到 $t=2$ 时的字典序限制是从 $n$ 到 $1$ 的，这启发我们倒着想，将建楼转化成拆楼。

一开始，所有楼都是建好的，每一次操作，我们要找到当前能拆的楼中编号最大的，把它拆掉。

对于一座楼，如果能被拆，一定满足以下条件。

- 对于所有楼按八连通建边的图中，它不是割点。

- 它能到达无穷远。

对于第一条限制来说，显然，如果该图不是联通图，一定不合法，否则一定存在方案满足条件。

先来解决第二条限制。

直接建图空间肯定会炸，考虑把一部分点表示出来。

对于一座楼，如果它四联通的空地里有到达无穷远的，那它也能到达无穷远。

考虑到下一个限制是八连通，所以，先把每个楼八联通的空地存下来，判断时只判断四联通的那些点，这样，点的个数就是 $O(n)$ 量级的了。

可以先找到一个能到达无穷远的空地，比如横坐标最小的，然后找出该点所在的空地的连通块，则该块都能到达无穷远。

在拆楼的过程中，每个空地最多一次改变是否能到达无穷远的状态，所以这一部分直接暴力搜索这个楼四周的空地即可。时间复杂度 $O(n)$。

这样，就有了一种 $O(n^2)$ 的暴力：每次都把图建出来，用 Tarjan 找出割点。

现在来解决第二条限制。

因为是网格图，所以割点只会有以下几种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/3dm3se0p.png)

图中，$1$ 是楼，$0$ 是空地，$x$ 是判断是否是割点的楼。

如果图中的 $0$ 属于同一连通块，此时拆掉 $x$ 的话，上下的 $1$ 就不连通了，所以这时 $x$ 是割点。

将此图翻转同理。

![](https://cdn.luogu.com.cn/upload/image_hosting/i8zn6f0y.png)

如果图中的 $0$ 属于同一连通块时，同理，$x$ 是割点。

初始化时顺便处理每个空地所处的连通块即可。

当拆楼时，所影响到只有被拆掉的楼四周的空地连通块周围的楼的状态。

因为改变是否是割点的只有被删的楼八连通的楼，所以时间复杂度同样是 $O(n)$。

找编号最大的楼可以用 set，维护每个点的状态可以用 map。复杂度多带一个 log。

## 代码

不知道是不是实现的问题，我感觉这题稍微有点卡常。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define F(i,l,r) for(int i=l;i<=r;i++)
#define UF(i,r,l) for(int i=r;i>=l;i--)
#define p_q priority_queue
#define pb push_back
#define mk(a,b) make_pair(a,b)
#define pii pair<int,int> 
#define ve vector
#define endl '\n'
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define lowbit(x) (x&(-x))
// #pragma GCC optimize("O3")
int dx[]={0,1,0,-1,0,1,1,-1,-1};
int dy[]={0,0,1,0,-1,1,-1,1,-1};
int n,T;
struct node{
	int x,y;
}a[150005],b[1919811];
map<pii,int> f,vis;
int cnt=0,_=0;
void dfs(int x,int y){
	if(!vis.count(mk(x,y))||!vis[mk(x,y)]) return ;
	_++;
	vis[mk(x,y)]=0;
	for(int i=1;i<=8;i++){
		int xx=x+dx[i];
		int yy=y+dy[i];
		dfs(xx,yy);
	}
}
set<int>s;
inline bool check(int x,int y);
bool chk(int x,int y);
inline void full(int x,int y,int col,int F){
	if(!f.count(mk(x,y))){
		return ;
	}
	if(f[mk(x,y)]==col||f[mk(x,y)]==1) return ;
	f[mk(x,y)]=col;
//	full(x+1,y,col,F);
//	full(x-1,y,col,F);
//	full(x,y+1,col,F);
//	full(x,y-1,col,F);
	for(register int i=1;i<=4;i++){
		int xx=x+dx[i];
		int yy=y+dy[i];
		full(xx,yy,col,F);		
	}
	if(!F) return ;
	for(register int i=1;i<=4;i++){
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(vis.count(mk(xx,yy))&&vis[mk(xx,yy)]!=0){
			if(chk(xx,yy)){
				s.insert(vis[mk(xx,yy)]);
			}else{
				if(s.find(vis[mk(xx,yy)])!=s.end()){
					s.erase(s.find(vis[mk(xx,yy)]));
				}
			}
		}
	}
}
int ans[150005],live[150005];
int tot=0,root;
int F[9];
inline bool check(int x,int y){
	F[1]=f[mk(x-1,y-1)];
	F[2]=f[mk(x-1,y)];
	F[3]=f[mk(x-1,y+1)];
	F[4]=f[mk(x,y-1)];
	F[5]=f[mk(x,y+1)];
	F[6]=f[mk(x+1,y-1)];
	F[7]=f[mk(x+1,y)];
	F[8]=f[mk(x+1,y+1)];
	if((F[1]==1||F[2]==1||F[3]==1)&&(F[6]==1||F[7]==1||F[8]==1)&&F[4]==F[5]&&F[5]<0) return 0;
	if(F[2]<0&&F[7]==F[2]&&(F[1]==1||F[4]==1||F[6]==1)&&(F[3]==1||F[5]==1||F[8]==1)) return 0;
	if(F[2]==F[4]&&F[4]<0&&F[1]==1&&(F[6]==1||F[7]==1||F[8]==1||F[5]==1||F[3]==1)) return 0;
	if(F[7]==F[5]&&F[5]<0&&F[8]==1&&(F[1]==1||F[4]==1||F[6]==1||F[3]==1||F[2]==1)) return 0;
	if(F[3]==1&&(F[1]==1||F[4]==1||F[6]==1||F[7]==1||F[8]==1)&&F[2]==F[5]&&F[5]<0) return 0;
	if(F[6]==1&&(F[3]==1||F[5]==1||F[8]==1||F[2]==1||F[1]==1)&&F[7]==F[4]&&F[4]<0) return 0;
	return 1&&(F[2]==-1||F[4]==-1||F[5]==-1||F[7]==-1);
}
bool chk(int x,int y){
	return check(x,y);
}
int main(){
//	freopen("c.in","r",stdin);
//	freopen("c.out","w",stdout);
	cin>>n>>T;
	for(register int i=1;i<=n;i++){
		live[i]=1;
		scanf("%d%d",&a[i].x,&a[i].y);
		vis[mk(a[i].x,a[i].y)]=1;
		f[mk(a[i].x,a[i].y)]=1;
		for(int j=1;j<=8;j++){
			int xx=a[i].x+dx[j];
			int yy=a[i].y+dy[j];
			if(!f.count(mk(xx,yy))){
				cnt++;
				b[cnt].x=xx;
				b[cnt].y=yy;
				f[mk(xx,yy)]=0;
			}
		}
	}
	dfs(a[1].x,a[1].y);
	if(_!=n){
		cout<<"NO";
		return 0;
	}
	cout<<"YES\n";
	_=1;
	for(register int i=2;i<=cnt;i++){
		if(b[i].x<b[_].x) _=i;
	}
	full(b[_].x,b[_].y,-1,0);
	_=-1;
	for(register int i=1;i<=cnt;i++) {
		if(f[mk(b[i].x,b[i].y)]==0){
			_--;
			full(b[i].x,b[i].y,_,0);
		}
	}
	for(register int i=1;i<=n;i++){
		vis[mk(a[i].x,a[i].y)]=i;
		if(chk(a[i].x,a[i].y)){
			s.insert(i);
		}
	}
	for(_=n;_;_--){
		set<int>::iterator __=s.end();
		__--;
		ans[_]=*__;
		vis[mk(a[*__].x,a[*__].y)]=0;
		f[mk(a[*__].x,a[*__].y)]=0;
		full(a[*__].x,a[*__].y,-1,1);
		int x=a[*__].x,y=a[*__].y;
		for(register int i=1;i<=8;i++){
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(vis.count(mk(xx,yy))&&vis[mk(xx,yy)]!=0){
				if(chk(xx,yy)){
					s.insert(vis[mk(xx,yy)]);
				}else{
					if(s.find(vis[mk(xx,yy)])!=s.end()){
						s.erase(s.find(vis[mk(xx,yy)]));
					}
				}
			}
		}
		s.erase(__);
	}
	for(register int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：AC_love (赞：1)

打开题解区发现唯一一篇题解出自我校功勋学长，写了 10k 看得我眼花缭乱的，这里给出一个更简洁的代码实现。

注意到要求字典序最大是从 $n$ 到 $1$ 的字典序最大，这与我们常规的对字典序的要求不太一样，是一个提示，暗示我们应该反过来做。

把建造变成拆除，考虑拆除顺序的字典序最大即可。

显然存在方案的充要条件是所有大楼均连通，那么在拆除过程中，一旦发现图不连通，则无解，说明刚才拆错了。

那么一栋大楼能够被删除当且仅当：

- 它能到达无穷远处。
- 它不是割点。

考虑这个东西该怎么判。

先判断前者。我们不妨把整张网格图建出来，有尚未被拆除的大楼的点标记为黑点，反之为白点。最外层的白点是可以到达无穷远处的，与可以到达无穷远处的白点四连通的点是可以到达无穷远处的。

可以用并查集来合并，不过其实没必要。因为我们注意到每次将一个黑点变成白点的时候一定只会将至多一个白色连通块合并到能到达无穷远处的连通块上，而不会对其他白色连通块产生影响，每个点的合并次数都是 $O(1)$ 的，所以可以直接暴力合并。

可是这个平面是 $10^9 \times 10^9$ 的，真把图建出来时空都要炸了。不过发现黑点个数只有 $n$ 个，我们可以只添加所有黑点以及黑点周围的 $8$ 个点，这样点数就是 $O(n)$ 级别的了。

然后考虑后者如何判断。无向图动态删点维护连通性，这东西做不了一点。不过好在这道题比较特殊，是在一个网格图上，那么只需要判一下周围八个点的状态即可。

一个点是割点有且只有两种情况：

```
A*B
A#B
A*B

A*B
*#B
BBB
```

其中 `#` 代表这个点，`*` 代表一个白点，`A` 和 `B` 对应两个不同的区域。

如果两个 `*` 在同一个连通块里，且 `A` 区域和 `B` 区域都至少有一个黑点，那么这个 `#` 是割点。

实际上情况有六种，第一种情况旋转后总共有两种情况，第二种情况旋转后总共有四种情况。我们可以预处理把这六种情况都记录下来，这样在代码实现的其他地方会更加简洁。

注意到每次只有删除的点的周围的八个点的状态可能会变，这确保了我们的操作数是 $O(n)$ 的，可以直接暴力大模拟来解决。

代码实现上的细节可以参考我的代码，写了不到 5k，应该还是比较简洁的。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 114;
const int dx[9] = {0, 1, -1, 0, 0, 1, 1, -1, -1};
const int dy[9] = {0, 0, 0, 1, -1, 1, -1, 1, -1};

struct node
{
    pair <int, int> pos[2];
    vector <pair <int, int> > a;
    vector <pair <int, int> > b;
};
node c[7];

void init()
// 预处理出所有可能成为割点的六种情况
{
    c[1].pos[0] = {1, 0};
    c[1].pos[1] = {0, 1};
    c[1].a.push_back({1, 1});
    c[1].b.push_back({-1, 1});
    c[1].b.push_back({-1, 0});
    c[1].b.push_back({-1, -1});
    c[1].b.push_back({0, -1});
    c[1].b.push_back({1, -1});

    c[2].pos[0] = {1, 0};
    c[2].pos[1] = {0, -1};
    c[2].a.push_back({1, -1});
    c[2].b.push_back({1, 1});
    c[2].b.push_back({0, 1});
    c[2].b.push_back({-1, 1});
    c[2].b.push_back({-1, 0});
    c[2].b.push_back({-1, -1});

    c[3].pos[0] = {-1, 0};
    c[3].pos[1] = {0, 1};
    c[3].a.push_back({-1, 1});
    c[3].b.push_back({1, 1});
    c[3].b.push_back({1, 0});
    c[3].b.push_back({1, -1});
    c[3].b.push_back({0, -1});
    c[3].b.push_back({-1, -1});

    c[4].pos[0] = {-1, 0};
    c[4].pos[1] = {0, -1};
    c[4].a.push_back({-1, -1});
    c[4].b.push_back({-1, 1});
    c[4].b.push_back({0, 1});
    c[4].b.push_back({1, 1});
    c[4].b.push_back({1, 0});
    c[4].b.push_back({1, -1});

    c[5].pos[0] = {1, 0};
    c[5].pos[1] = {-1, 0};
    c[5].a.push_back({1, 1});
    c[5].a.push_back({0, 1});
    c[5].a.push_back({-1, 1});
    c[5].b.push_back({1, -1});
    c[5].b.push_back({0, -1});
    c[5].b.push_back({-1, -1});

    c[6].pos[0] = {0, 1};
    c[6].pos[1] = {0, -1};
    c[6].a.push_back({1, 1});
    c[6].a.push_back({1, 0});
    c[6].a.push_back({1, -1});
    c[6].b.push_back({-1, 1});
    c[6].b.push_back({-1, 0});
    c[6].b.push_back({-1, -1});
}

map <pair <int, int>, int> p, id;
int n, t, cnt;
pair <int, int> pt[N];
bool vis[N];

int tot = 0;

// 首先判断是否有解
void dfs(pair <int, int> x)
{
    if(p[x] == 0 || vis[p[x]])
        return;
    vis[p[x]] = 1;
    tot ++;
    for(int i = 1; i <= 8; i = i + 1)
        dfs({x.first + dx[i], x.second + dy[i]});
}

set <int> s;

int rg;

vector <pair <int, int> > vv;

// 判断一个白点属于哪个白色联通块
void search(pair <int, int> x)
{
    if(p.find(x) == p.end())
        return;
    if(p[x] > 0 || p[x] == rg)
        return;
    vv.push_back(x);
    p[x] = rg;
    for(int i = 1; i <= 4; i = i + 1)
        search({x.first + dx[i], x.second + dy[i]});
}

// 判断一个黑点是否是割点
bool ok(pair <int, int> x, int id)
{
    pair <int, int> r1 = {x.first + c[id].pos[0].first, x.second + c[id].pos[0].second};
    pair <int, int> r2 = {x.first + c[id].pos[1].first, x.second + c[id].pos[1].second};
    int pr1 = p[r1], pr2 = p[r2];
    if(pr1 != pr2 || pr1 > 0)
        return 0;
    bool a = 0;
    for(auto i : c[id].a)
    {
        pair <int, int> rr = {x.first + i.first, x.second + i.second};
        a |= (p[rr] > 0);
    }
    if(a == 0)
        return 0;
    bool b = 0;
    for(auto i : c[id].b)
    {
        pair <int, int> rr = {x.first + i.first, x.second + i.second};
        b |= (p[rr] > 0);
    }
    return b;
}

// 判断一个黑点是否可以被拆除
bool check(int x)
{
    pair <int, int> r = pt[x];
    bool f = 0;
    for(int i = 1; i <= 4; i = i + 1)
        if(p[{r.first + dx[i], r.second + dy[i]}] == -1)
        {
            f = 1;
            break;
        }
    if(f == 0)
        return 0;
    for(int i = 1; i <= 6; i = i + 1)
        if(ok(r, i))
            return 0;
    return 1;
}

vector <int> ans;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> t;
    init();
    for(int i = 1, x, y; i <= n; i = i + 1)
    {
        cin >> x >> y;
        p[{x, y}] = i;
        pt[i] = {x, y};
        for(int k = 1; k <= 8; k = k + 1)
            if(p.find({x + dx[k], y + dy[k]}) == p.end())
                p[{x + dx[k], y + dy[k]}] = 0;
    }
    dfs(pt[1]);
    if(tot < n)
    {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for(auto &i : p)
        if(i.second == 0)
        {
            rg --;
            search(i.first);
        }
    for(int i = 1; i <= n; i = i + 1)
    {
        if(check(i))
            s.insert(i);
    }
    rg = -1;
    while(ans.size() < n)
    {
        vv.clear();
        set <int> :: iterator it = s.end();
        it --;
        int res = *it;
        s.erase(it);
        ans.push_back(res);
        pair <int, int> ndd = pt[res];
        p[ndd] = 0;
        search(ndd);
        for(auto nd : vv)
        {
            for(int i = 1; i <= 8; i = i + 1)
            {
                pair <int, int> rr = {nd.first + dx[i], nd.second + dy[i]};
                int ret = p[rr];
                if(ret > 0)
                {
                    bool f = check(ret);
                    if(f)
                        s.insert(ret);
                    else
                    {
                        if(s.find(ret) != s.end())
                            s.erase(s.find(ret));
                    }
                }
            }
        }
    }
    while(ans.size())
    {
        cout << ans.back() << "\n";
        ans.pop_back();
    }
    return 0;
}
```

---

## 作者：james1BadCreeper (赞：1)

我们显然要去删大楼（字典序是倒着比的也提示了这一点），考虑当前子问题有解的充要条件：当前大楼八连通。

一个点能被删掉的充要条件是：

- 它能够到达无穷远处；
- 它不是八连通图的割点。

考虑将非大楼点称为白点，那么能到达无穷远的白点的大楼满足条件一，这个很好维护。

条件二说明我们只能删圆方树的叶子，但是这样发现我们需要维护动态图的圆方树，基本上是死了。但这是网格图，性质很好，出现问题只有类似以下两种情况（`B` 表示楼，`X` 表示是割点，`W` 表示白点）：

```
B W B
W X B
B B B

B B B
W X W
B B B
```

其中 `W` 要在同一个连通块内，每次更新即可。但是我一开始写了各种奇怪的东西，一个简单题被我断断续续写了两天，只能说我是笨蛋。欢迎大家来欣赏我的大粪代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1.5e5 + 5; 
const int D[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}}; 
const int V = 2e9; 

int n, TGFD; 
struct Point {
    int x, y; 
} a[N]; 

struct pair_hash {
    long long operator()(const pair<int, int> &p) const {
        return 1ll * p.first * V + p.second;
    }
};
unordered_map<pair<int, int>, int, pair_hash> id; 
vector<int> E[N]; 

int dfn[N], low[N], num, node, st[N], tot, cnt[N * 2], cut[N]; 
// vector<int> G[N * 2]; 
bool s2[N]; 
inline void tarjan(int x) {
    dfn[x] = low[x] = ++num; st[++tot] = x; 
    function<void(int, int)> addedge = [] (int x, int y) {
        ++cnt[x]; ++cnt[y]; 
        // G[x].emplace_back(y); 
        // G[y].emplace_back(x); 
    }; 
    for (int y : E[x]) 
        if (!dfn[y]) {
            tarjan(y); low[x] = min(low[x], low[y]); 
            if (dfn[x] <= low[y]) {
                int z; addedge(x, ++node); 
                do addedge(z = st[tot--], node); while (z != y); 
            }
        } else low[x] = min(low[x], dfn[y]); 
}

unordered_set<pair<int, int>, pair_hash> whiteqwq; 
unordered_map<pair<int, int>, int, pair_hash> white; 
set<int> ans; 
vector<pair<int, int>> todo; 

inline void dfs(pair<int, int> now) {
    if (whiteqwq.find(now) != whiteqwq.end()) return; 
    whiteqwq.emplace(now); todo.emplace_back(now); white[now] = 1; 
    for (int k = 0; k < 4; ++k) {
        int x = now.first + D[k][0], y = now.second + D[k][1]; 
        if (id.find({x, y}) != id.end()) {
            int val = id[{x, y}]; 
            s2[val] = 1; 
            if (!cut[val]) ans.insert(val); 
        }
    }
    for (int i = 0; i < 4; ++i) {
        pair<int, int> to = make_pair(now.first + D[i][0], now.second + D[i][1]); 
        if (white.find(to) != white.end()) dfs(to); 
    }
}
void dfs2(int x, int y, int val) {
    white[{x, y}] = val; 
    for (int k = 0; k < 4; ++k) {
        int _x = x + D[k][0], _y = y + D[k][1]; 
        if (white.find({_x, _y}) != white.end() && white[{_x, _y}] == 0) dfs2(_x, _y, val); 
    }
}

inline int ck(int i) {
    auto [x, y] = a[i]; 
    int ans = 0; 
    for (int i = 0; i < 8; ++i) {
        int xx = x + D[i][0], yy = y + D[i][1]; 
        if (id.find({xx, yy}) != id.end()) ++ans; 
    }
    return ans; 
}
inline void upd(int x, int k) {
    cut[x] = k; 
    if (k == 1) ans.erase(x); 
    else if (s2[x]) ans.insert(x); 
}

#ifdef BEF
void work(int x, int y) {
    // cerr << x << " " << y << "\n"; 
    for (int i = 4; i < 8; ++i) {
        int _x = x + D[i][0], _y = y + D[i][1]; 
        if (white.find({_x, _y}) == white.end() || white[{_x, _y}] != white[{x, y}]) continue; 
        int i1 = id.find({x + D[i][0], y}) == id.end() ? 0 : id[{x + D[i][0], y}], 
            i2 = id.find({x, y + D[i][1]}) == id.end() ? 0 : id[{x, y + D[i][1]}]; 
        if (!i1 || !i2) {
            if (i1) mp[i1] |= 0; 
            if (i2) mp[i2] |= 0; 
        } else {
            if (i1) {
                mp[i1] |= (ck(i1) >= 2); 
                // if (i1 == 8 && (ck(i1) >= 2)) {
                    // cerr << i1 << " " << i2 << " ???\n"; 
                    // cerr << _x << " " << _y << "\n"; 
                    // for (auto [pos, val] : white)   
                        // cerr << pos.first << " " << pos.second << " " << val << "\n"; 
                    // exit(-1); 
                // }
            }
            if (i2) {
                mp[i2] |= (ck(i2) >= 2); 
                // if (i2 == 8 && (ck(i2) >= 2)) {
                    // cerr << i1 << " " << i2 << " ???\n"; 
                    // cerr << _x << " " << _y << "\n"; 
                    // for (auto [pos, val] : white)   
                        // cerr << pos.first << " " << pos.second << " " << val << "\n"; 
                    // exit(-1); 
                // }
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        int _x = x + D[i][0] * 2, _y = y + D[i][1] * 2; 
        if (white.find({_x, _y}) == white.end() || white[{_x, _y}] != white[{x, y}]) continue; 
        _x = x + D[i][0], _y = y + D[i][1]; 
        if (id.find({_x, _y}) != id.end()) {
            if (D[i][0] == 0) { // 它是竖着的
                bool is = 1; 
                for (int dx : {-1, 1}) {
                    bool flg = 0; 
                    for (int dy : {-1, 0, 1})
                        if (id.find({_x + dx, _y + dy}) != id.end()) { flg = 1; break; }
                    if (!flg) { is = 0; break; }
                }
                mp[id[{_x, _y}]] |= is; 
                // upd(id[{_x, _y}], is); 
            } else {
                bool is = 1; 
                for (int dy : {-1, 1}) {
                    bool flg = 0; 
                    for (int dx : {-1, 0, 1})
                        if (id.find({_x + dx, _y + dy}) != id.end()) { flg = 1; break; }
                    if (!flg) { is = 0; break; }
                }
                mp[id[{_x, _y}]] |= is; 
                // upd(id[{_x, _y}], is); 
            }
        }
    }
}
#endif

bool whiteequal(int x, int y, int _x, int _y) {
    if (white.find({x, y}) == white.end()) return 0; 
    if (white.find({_x, _y}) == white.end()) return 0; 
    return white[{x, y}] == white[{_x, _y}]; 
}
bool check(int p) { // 检查 p 是否为割点
    if (ck(p) >= 2) {
        for (int i = 0; i < 8; ++i) {
            int x = a[p].x + D[i][0], y = a[p].y + D[i][1]; 
            if (id.find({x, y}) != id.end()) {
                int j = id[{x, y}]; 
                if (whiteequal(a[p].x + D[i][0], a[p].y, a[p].x, a[p].y + D[i][1])) return 1; 
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (!whiteequal(a[p].x + D[i][0], a[p].y + D[i][1], a[p].x - D[i][0], a[p].y - D[i][1])) continue; 
        if (D[i][0] == 0) {
            bool is = 1; 
            for (int dx : {-1, 1}) {
                bool flg = 0; 
                for (int dy : {-1, 0, 1})
                    if (id.find({a[p].x + dx, a[p].y + dy}) != id.end()) { flg = 1; break; }
                if (!flg) { is = 0; break; }
            }
            if (is) return 1; 
        } else {
            bool is = 1; 
            for (int dy : {-1, 1}) {
                bool flg = 0; 
                for (int dx : {-1, 0, 1})
                    if (id.find({a[p].x + dx, a[p].y + dy}) != id.end()) { flg = 1; break; }
                if (!flg) { is = 0; break; }
            }
            if (is) return 1; 
        }
    }
    return 0; 
}

int main(void) {
    // freopen("1.err", "w", stderr); 
    ios::sync_with_stdio(0); 
    cin >> n >> TGFD; 
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y; 
        id[{a[i].x, a[i].y}] = i; 
    }
    if (n == 1) return cout << "YES\n1\n", 0; 
    for (int i = 1; i <= n; ++i)
        for (int k = 0; k < 8; ++k) {
            int x = a[i].x + D[k][0], y = a[i].y + D[k][1]; 
            if (id.find({x, y}) != id.end()) {
                int j = id[{x, y}]; 
                E[i].emplace_back(j); E[j].emplace_back(i); 
            }
        }
    node = n; tarjan(1); 
    for (int i = 1; i <= n; ++i) if (!dfn[i]) return cout << "NO\n", 0; 

    for (int i = 1; i <= n; ++i) if (cnt[i] != 1) cut[i] = 1; 

    pair<int, int> xxx = {-2e9, -2e9}; 
    for (int i = 1; i <= n; ++i)
        for (int k = 0; k < 8; ++k) {
            int x = a[i].x + D[k][0], y = a[i].y + D[k][1]; 
            if (id.find({x, y}) == id.end()) white[{x, y}] = 0, xxx = max(xxx, make_pair(x, y)); 
        }
    dfs(xxx); 
    int tot = 1; 
    for (int i = 1; i <= n; ++i)
        for (int k = 0; k < 8; ++k) {
            int x = a[i].x + D[k][0], y = a[i].y + D[k][1]; 
            if (white.find({x, y}) != white.end() && white[{x, y}] == 0) dfs2(x, y, ++tot); 
        }

    // cerr << "1622 is " << cut[1622] << "\n";  
    // for (int dy = -3; dy <= 3; ++dy, cerr << "\n")
        // for (int dx = -3; dx <= 3; ++dx) {
            // int x = a[1622].x + dx, y = dy + a[1622].y; 
            // if (id.find({x, y}) != id.end()) cerr << id[{x, y}] << " "; 
            // else if (whiteqwq.find({x, y}) != whiteqwq.end()) cerr << "W  "; 
            // else cerr << "-1 "; 
        // }

    vector<int> Ans; 
    for (int op = 1; op <= n; ++op) {
        assert(ans.size()); 
        int u = *ans.rbegin(); Ans.push_back(u); ans.erase(prev(ans.end())); 

#ifdef DEBUG
        cerr << "del " << u << "\n"; 
        if (u == 1622) exit(-1);
#endif

        id.erase(make_pair(a[u].x, a[u].y)); white[{a[u].x, a[u].y}] = 1; 

        // cerr << u << "\n"; 
        todo.clear(); dfs(make_pair(a[u].x, a[u].y)); 
        for (auto [x, y] : todo) {
            for (int i = 0; i < 8; ++i) {
                int _x = x + D[i][0], _y = y + D[i][1]; 
                if (id.find({_x, _y}) != id.end()) 
                    upd(id[{_x, _y}], check(id[{_x, _y}])); 
            }
        }

#ifdef DEBUG
        cerr << "1622 is " << cut[1622] << "\n";  
        for (int dy = -3; dy <= 3; ++dy, cerr << "\n")
            for (int dx = -3; dx <= 3; ++dx) {
                int x = a[1622].x + dx, y = dy + a[1622].y; 
                if (id.find({x, y}) != id.end()) cerr << id[{x, y}] << " "; 
                else if (white.find({x, y}) != white.end()) cerr << "W" << white[{x, y}] << " "; 
                else cerr << "-1 "; 
            }
#endif
#ifdef BEF
        mp.clear(); 
#endif

        // cerr << x << " " << y << "\n"; 
        // for (int i = 1; i <= n; ++i)
            // if (cut[i]) cerr << "CUT IS " << a[i].x << " " << a[i].y << "\n"; 
        // cerr << u << " " << cnt[u] << "\n"; 
        
        // cerr << "-----------\n"; 
    }
#ifdef DEBUG
    return 0; 
#endif
    reverse(Ans.begin(), Ans.end()); 
    cout << "YES\n"; 
    for (int i : Ans) cout << i << "\n"; 
    return 0; 
}

/*
-1  -1   W   232  -1   -1  228
-1  -1   W   W    332  862 1578
W   -1   W   W    1589 -1  -1
W   W    W   1622 -1   194 -1
107 1449 W   334  439  -1  817
849 -1   122 834  -1   -1  -1
-1  -1   -1  -1   -1   -1  207
*/

/*
W1  -1   -1   -1   -1   -1   -1 
W1  W1   W1   W1   W1   W1   -1 
694 701  1074 W1   526  W1   W1 
335 W187 W187 1622 W1   W1   643 
618 672  W187 W187 1378 1586 W1 
W1  W1   541  1213 W1   W1   W1 
W1  W1   W1   279  W1   W1   22 
*/
```

---

## 作者：takanashi_mifuru (赞：0)

首先是判断无解，容易发现连通就有解，否则就无解。

考虑平方暴力，这题第二问启发我们从后往前拆楼，于是我们考虑找到最大的能拆的楼拆掉。

一栋楼能被拆除当且仅当把他拆除后大楼仍连通同时他与边界相连，显然把这样的楼拆掉不会影响后续的判断结果所以我们贪心选择标号最大的可行节点，这样就可以做到平方。

当然可能会有点数过多的情况，考虑我们把每一行以及相邻的行预留出来，再把每一列以及相邻的列预留出来，这样表格的大小就是 $O(n^2)$ 的了。

于是这样能通过 51 分。

考虑这个问题中有两个东西卡着他让他不能够取到我想要的东西，一个是点数，另一个则是判断割点。

先考虑判断割点，网格图的割点考虑形式如下图，如果图中红叉为割点，那么两个白点作为空白点显然必须连通把这两坨包起来。

![](https://pic1.imgdb.cn/item/6862383458cb8da5c87f3b86.png)

还有一种形式是把他横过来，也是类似的。

显然在这个模式下我只在乎八连通的点以及他们之间的连通性，所以点数的问题也解决了，我们获得了一个更为优美的 $O(n^2)$ 做法。

考虑如何优化，这个东西看上去删掉一个点会影响很多个点的连通性，但实际一个点从非割点变成割点可能有若干种可能，但从割点变成非割点只有八连通的点才能做到。

所以一个点从割点变为非割点最多进行 $O(n)$ 次，反过来从非割点变为割点最多也只会进行 $O(n)$ 次，我们需要维护支持插入删除求最大值的数据结构，写个可删堆即可。

有个小细节就是，如果一个点被删除后与边界连通，那么需要以他为起点把没搜过的连通空点搜一遍，并将这些点的邻接非空点加入可删堆，原因显然。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,type;
int dx[8]={1,0,0,-1,1,-1,1,-1};
int dy[8]={0,1,-1,0,1,-1,-1,1};
struct node{
   int x,y;
}A[1500005];
bool vis[1500005];
pair<int,int> G[1500005];
int tot,pos;
int N,M;
int id(int i,int j){
   return (i-1)*M+j;
}
int need;

map<int,int> mp[500005];
int ljb[1500005][8];
//
class UFS{
   public:
   int father[1500005];
   void init(int n){
      for(int i=1;i<=n;i++)father[i]=i;
      return;
   }
   int find(int x){
      return father[x]==x?x:father[x]=find(father[x]);
   }
   void unionn(int x,int y){return father[find(x)]=find(y),void();}
}S;

void init(){
   vector<int> D;
   for(int i=1;i<=n;i++){
      D.push_back(A[i].x-1);
      D.push_back(A[i].x);
      D.push_back(A[i].x+1);
   }
   sort(D.begin(),D.end());
   vector<int> E;
   for(int i=0;i<D.size();i++){
      if(!i)E.push_back(D[i]);
      else if(D[i] xor D[i-1])E.push_back(D[i]);
   }
   D=E;
   for(int i=1;i<=n;i++){
      int lt=-1,rt=D.size();
      while(lt+1<rt){
         int mid=lt+rt>>1;
         if(D[mid]<=A[i].x)lt=mid;
         else rt=mid;
      }
      A[i].x=lt;
   }
   N=D.size()-1;
   D.clear(),E.clear();
   for(int i=1;i<=n;i++){
      D.push_back(A[i].y-1);
      D.push_back(A[i].y);
      D.push_back(A[i].y+1);
   }
   sort(D.begin(),D.end());
   for(int i=0;i<D.size();i++){
      if(!i)E.push_back(D[i]);
      else if(D[i] xor D[i-1])E.push_back(D[i]);
   }
   // exit(0);
   D=E;
   for(int i=1;i<=n;i++){
      int lt=-1,rt=D.size();
      while(lt+1<rt){
         int mid=lt+rt>>1;
         if(D[mid]<=A[i].y)lt=mid;
         else rt=mid;
      }
      A[i].y=lt;
   }
   M=E.size()-1;
   N+=2,M+=2;
   for(int i=1;i<=n;i++){
      A[i].x++,A[i].y++;
   }
   for(int i=1;i<=n;i++){
      mp[A[i].x][A[i].y]=i;
   }
   for(int i=1;i<=n;i++){
      for(int k=0;k<8;k++){
         if(mp[A[i].x+dx[k]][A[i].y+dy[k]]){
            continue;
         }
         G[++tot]=make_pair(A[i].x+dx[k],A[i].y+dy[k]);
      }
   }
   sort(G+1,G+1+tot);
   pos=n;
   for(int i=1;i<=tot;i++){
      if(G[i]!=G[i-1]){
         A[++pos]=node{G[i].first,G[i].second};
      }
   }
   for(int i=1;i<=pos;i++)mp[A[i].x][A[i].y]=i;
   need=pos;
   for(int i=1;i<=pos;i++){
      for(int k=0;k<8;k++){
         ljb[i][k]=mp[A[i].x+dx[k]][A[i].y+dy[k]];
      }
   }
   S.init(pos);
   for(int i=1;i<=n;i++){
      for(int k=0;k<8;k++){
         int v=ljb[i][k];
         if(!v||v>n)continue;
         S.unionn(i,v);
      }
   }
   for(int i=n+1;i<=pos;i++){
      for(int k=0;k<4;k++){
         int v=ljb[i][k];
         if(!v||v<=n)continue;
         S.unionn(i,v);
      }
   }
   cerr<<N<<' '<<M<<'\n';
   return;
}

vector<int> L[6],R[6],qeta[6];

bool check(int cur){
   for(int i=0;i<6;i++){
      bool flg=false;
      for(int v:L[i]){
         if(vis[ljb[cur][v]])flg=true;
      }
      if(!flg)continue;
      flg=false;
      for(int v:R[i]){
         if(vis[ljb[cur][v]])flg=true;
      }
      if(!flg)continue;
      flg=false;
      for(int v:qeta[i]){
         if(vis[ljb[cur][v]])flg=true;
      }
      if(flg)continue;
      if(S.find(ljb[cur][qeta[i][0]])==S.find(ljb[cur][qeta[i][1]])){
         return true;
      }
   }
   for(int i=0;i<4;i++){
      int v=ljb[cur][i];
      if(!v)continue;
      if(S.find(v)==S.find(need)){
         return false;
      }
   }
   return true;
}

class ddd{
   public:
   priority_queue<int> A,D;
   void push(int x){return A.push(x),void();}
   void del(int x){return D.push(x),void();}
   int top(){while(D.size()&&A.top()==D.top())A.pop(),D.pop();return A.top();}
   int size(){return A.size()-D.size();}
}Q;
bool in[150005];

bool tag[1500005];

void getin(int cur){
   tag[cur]=true;
   for(int i=0;i<4;i++){
      if(!ljb[cur][i])continue;
      if(vis[ljb[cur][i]]){
         if(!in[ljb[cur][i]]){
            Q.push(ljb[cur][i]);
            in[ljb[cur][i]]=true;
         }
         continue;
      }
      if(tag[ljb[cur][i]])continue;
      getin(ljb[cur][i]);
   }
   return;
}

int main(){
   // freopen("building.in","r",stdin);
   // freopen("building.out","w",stdout);
   L[0]={7},R[0]={5,2,6,0,4},qeta[0]={1,3};
   L[1]={5},R[1]={6,0,4,1,7},qeta[1]={2,3};
   L[2]={6},R[2]={5,3,7,1,4},qeta[2]={2,0};
   L[3]={4},R[3]={6,2,5,3,7},qeta[3]={0,1};
   L[4]={5,3,7},R[4]={6,0,4},qeta[4]={1,2};
   L[5]={5,2,6},R[5]={7,1,4},qeta[5]={0,3};
   scanf("%d%d",&n,&type);
   for(int i=1;i<=n;i++){
      scanf("%d%d",&A[i].x,&A[i].y);
   }
   init();
   int chk=0;
   for(int i=1;i<=n;i++){
      if(S.find(i)==i){
         chk++;
      }
   }
   if(chk>1){
      puts("NO");
      return 0;
   }
   for(int i=1;i<=n;i++)S.father[i]=i;
   for(int i=1;i<=n;i++)vis[i]=true;
   int tim=n;
   vector<int> ans;
   for(int i=1;i<=n;i++)Q.push(i),in[i]=true;
   while(tim--){
      while(Q.size()){
         int tmp=Q.top();
         Q.del(tmp);
         in[tmp]=false;
         if(check(tmp))continue;
         if(!vis[tmp])continue;
         vis[tmp]=false;
         for(int j=0;j<4;j++){//
            if(!vis[ljb[tmp][j]])S.unionn(tmp,ljb[tmp][j]);
         }
         if(S.find(need)==S.find(tmp)){
            getin(tmp);
         }
         ans.push_back(tmp);
         for(int j=0;j<8;j++){
            if(vis[ljb[tmp][j]]){
               if(!in[ljb[tmp][j]]){
                  Q.push(ljb[tmp][j]);
                  in[ljb[tmp][j]]=true;
               }
            }
         }
         break;
      }
   }
   puts("YES");
   for(int i=ans.size()-1;i>=0;i--){
      printf("%d\n",ans[i]);
   }
   return 0;
}
```

---

