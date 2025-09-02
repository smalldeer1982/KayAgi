# Colorful Constructive

## 题目描述

You have $ n $ colored cubes, the $ i $ -th cube has color $ a_i $ .

You need to distribute all the cubes on shelves. There are a total of $ m $ shelves, the $ i $ -th shelf can hold $ s_i $ cubes. Also, $ s_1 + s_2 + \ldots + s_m = n $ .

Suppose on a shelf of size $ k $ there are cubes of colors $ c_1, c_2, \ldots, c_k $ , in this order. Then we define the colorfulness of the shelf as the minimum distance between two different cubes of the same color on the shelf. If all the cubes on the shelf have different colors, then the colorfulness is considered to be equal to the size of the shelf, that is, the number $ k $ .

More formally, the colorfulness of $ c_1, c_2, \ldots, c_k $ is defined as follows:

- If all the colors $ c_1, c_2, \ldots, c_k $ are different, the colorfulness is considered to be $ k $ .
- Otherwise, the colorfulness is considered to be the smallest integer $ x \geq 1 $ such that there exists an index $ i $ $ (1 \le i \le k - x) $ such that $ c_i = c_{i+x} $ .

For each shelf, you are given the minimum required colorfulness, that is, you are given numbers $ d_1, d_2, \ldots, d_m $ , which mean that shelf $ i $ must have a colorfulness $ \geq d_i $ for all $ i $ .

Distribute the available cubes among the shelves to ensure the required colorfulness, or report that it is impossible.

## 样例 #1

### 输入

```
6
10 3
1 1 1 1 2 2 2 3 3 4
6 2 2
4 1 1
8 2
7 7 7 7 8 8 8 8
4 4
2 2
5 1
5 4 3 2 1
5
3
7 3
1 2 2 2 2 3 4
1 2 4
1 2 4
12 7
6 6 6 6 6 6 6 6 6 7 8 9
2 2 2 2 2 1 1
1 2 2 2 1 1 1
20 2
11 20 15 6 8 18 12 16 8 20 10 12 3 12 20 11 15 8 17 17
8 12
3 5```

### 输出

```
1 3 4 2 1 3 
1 1 
2 2 
8 7 8 7 
8 7 8 7 
2 4 5 3 1 
-1
6 6 
7 6 
8 6 
9 6 
6 6 
6 
6 
12 17 20 15 8 20 16 11 
15 20 17 12 10 8 3 18 12 11 8 6```

# 题解

## 作者：蒟蒻君HJT (赞：5)

这场给我干傻了，1B 1C 写了一百年根本没时间看 1D，结果 1D 是纯 sbt（可以放 1B）。

考虑对于一个大小为 $s$ 的架子，其限制为 $k$，什么情况下能满足要求。不难发现，必要条件是从左往右分成长为 $k$ 的若干段和长为 $s\bmod k$ 的余下一段（如果 $s\bmod k\neq 0$ 的话）中段内部不能有相同颜色，这是非常显然的。但是仔细想想会发现这也是充分条件。

Proof：

不妨把余下那段移到最左边。这段随便放。然后从第 $2$ 段开始的第 $i$ 段，把其中出现过的数字按在第 $i-1$ 段中的出现位置（没出现过就是看作 $-1$）从小到大排序，再放到第 $i$ 段中。这样一来对于所有同时出现在第 $i-1$ 段和第 $i$ 段中的数字 $x$，其在第一段的出现位置一定比第二段更靠前，也就是他们的距离 $\geq k$。

那么就可以放心地拆架子了。将所有拆出来的段从长到短排序，对于长为 $l$ 的段，若当前可选的不同的 $a_i$ 少于 $l$ 种，则答案不存在；否则取出当前出现次数最多的 $l$ 种 $a_i$，扔到段里就行。这是经典的贪心策略。可以用 ```std::priority_queue``` 维护贪心过程。

时间复杂度线性对数。

[for reference only.](https://codeforces.com/contest/1893/submission/231920145)

---

## 作者：World_Creater (赞：4)

考虑每个架子 $i$ 的限制：要求相同元素距离不小于 $k$，我们将这个限制大力转换为：我们每次塞数字直接一次性塞 $k$ 个**不同**元素进去，然后必然存在一种重排这个架子的方式使得这个架子合法，如果塞不进去说明无解。

显然上面这个过程是充要的，考虑每一个架子中 $[1,k],[k+1,2k]$ 等这些位置必然全不相同。

考虑贪心，使用一个优先队列，每次弹出当前限制最大的架子。考虑给这个架子分配哪 $k$ 个数，显然分配当前出现次数最多的 $k$ 个是最优的。

分配完数字后的重排过程也是简单的，这里不多赘述。

然后这个题就做完了，感觉完全没有 Div1 D 和 \*2600 的难度。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200005],b[200005],c[200005],vis[200005],id[200005];
map<int,int> mp[200005];
struct node{
	int id,lim,cnt;
	bool operator <(const node &b) const
	{
		return min(lim,cnt)<min(b.lim,b.cnt);
	}
};
void output(int x)
{
	priority_queue<pair<int,int> > q;
	for(auto i:mp[x]) q.emplace(i.second,i.first)/*,cerr<<x<<" "<<i.first<<" "<<i.second<<"\n"*/;
	vector<pair<int,int> > f(b[x]+5);
	for(int i=1;i<=b[x];i++)
	{
		if(f[i].first!=0) q.emplace(f[i]);
		auto j=q.top();
		q.pop();
		cout<<j.second<<" ";
		j.first--;
		if(j.first!=0&&i+c[x]<=b[x]) f[i+c[x]]=j; 
	}
	cout<<"\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			vis[a[i]]++;
		}
		for(int i=1;i<=m;i++)
		{
			cin>>b[i];
		}
		for(int i=1;i<=m;i++)
		{
			cin>>c[i];
			// cerr<<"lim:"<<c[i]<<"\n";
		}
		set<pair<int,int> > s;
		for(int i=1;i<=n;i++)
		{
			if(vis[i]) s.insert({vis[i],i});
		}
		priority_queue<node> q;
		for(int i=1;i<=m;i++)
		{
			q.push({i,c[i],b[i]});
		}
		bool f=1;
		while(!q.empty())
		{
			auto [x,y,z]=q.top();//找出限制最大的架子
			q.pop();
			if(min(y,z)>s.size())
			{
				f=0;
				break ;
			}
			vector<pair<int,int> > _;
			for(int i=1;i<=min(y,z);i++)
			{
				auto it=prev(s.end());//优先把出现次数最多的分配给他
				auto t=*it;
				t.first--;
				_.emplace_back(t);
				mp[x][t.second]++;
				s.erase(it);
			}
			z-=min(y,z);
			if(z) q.push({x,y,z});
			for(auto i:_)
			{
				if(i.first) s.insert(i);
			}
		}
		if(!f) cout<<"-1\n";
		else
		{
			for(int i=1;i<=m;i++)
			{
				output(i);	
			}
		}
		for(int i=1;i<=m;i++)
		{
			mp[i].clear();
		}
		for(int i=1;i<=n;i++)
		{
			vis[i]=0;
		}
	}
}
```

---

## 作者：Alex_Wei (赞：3)

### [CF1893D Colorful Constructive](https://www.luogu.com.cn/problem/CF1893D)

诈骗题，没想到这么简单。

方块之间无序且颜色之间相互等价，于是我们只关心每个颜色的出现次数 $occ_i$ 形成的可重集 $S$。

将 $S$ 从大到小排序后看成数列，基本的想法是：$|S|$ 不变的情况下，$S$ 的字典序越小越有可能有解。证明即考虑若 $S_i > S_{i + 1}$ 且有解，则令 $S_i$ 减去 $1$，$S_{i + 1}$ 加上 $1$ 之后依然有解。

因此可以直接贪心：按任意顺序枚举架子，依次往上放入 $s$ 个方块，每次选择出现次数最多的符合限制的方块。于是，每一步都能取到 $S$ 的最小字典序（当 $|S|$ 开始减小，说明 $S$ 里面所有数均为 $1$，此时一定有解）。

正确性可以类似调整证明。

使用优先队列，每次取出 $occ$ 的最大值。若已经放了 $i\geq d$ 个，则将第 $i - d + 1$ 个方块的颜色加回优先队列。不要忘记处理完一个架子后，末尾还有 $d - 1$ 个颜色需要加入优先队列。

时间复杂度 $\mathcal{O}((n + m)\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rnd(1064);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 998244353;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

// ---------- templates above ----------

constexpr int N = 2e5 + 5;

int n, m, occ[N], s[N], d[N];
vector<int> ans[N];
void mian() {
  cin >> n >> m;
  memset(occ, 0, n + 2 << 2);
  for(int i = 1, a; i <= n; i++) cin >> a, occ[a]++;
  for(int i = 1; i <= m; i++) cin >> s[i];
  for(int i = 1; i <= m; i++) cin >> d[i];
  priority_queue<pii> q;
  for(int i = 1; i <= n; i++) if(occ[i]) q.push({occ[i], i});
  for(int i = 1; i <= m; i++) {
    ans[i].clear();
    for(int j = 0; j < s[i] + d[i] - 1; j++) {
      if(j < s[i]) {
        if(q.empty()) {
          cout << "-1\n";
          return;
        }
        pii t = q.top(); q.pop();
        ans[i].push_back(t.second);
      }
      if(j >= d[i] - 1) {
        int id = ans[i][j - d[i] + 1];
        if(--occ[id]) q.push({occ[id], id});
      }
    }
  }
  for(int i = 1; i <= m; i++) {
    for(int it : ans[i]) cout << it << " ";
    cout << "\n";
  }
}


bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while(T--) mian();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：HHH6666666666 (赞：2)

补一下官方题解中提到的两个贪心做法的正确性证明。

## 做法简述

- 方法 $1$：假设一个书架属性为 $(s, d)$，其中 $s$ 为书架容量，$d$ 为书架彩色值，则将该书架分为 $\lfloor \frac{s}{d} \rfloor$ 个容量为 $d$ 的块和一个 $s \bmod d$ 的块。若所有块内所装元素不相同则必然存在一种将其放回原书架的方式。将所有书架拆分后，**以任意顺序遍历所有颜色**，每次贪心地将该颜色的所有方块（假设有 $k$ 个）放入 **剩余容量前 $k$ 大的块** 内（若剩余块不足 $k$ 个则无解）。

- 方法 $2$：按照方法 1 将书架拆分后，**以任意顺序遍历所有块**，假设该块容量为 $l$，则将 **剩余个数前 $l$ 多的颜色** 各放一个在该块内（若剩余颜色个数不足 $l$ 则无解）。

## 正确性证明

先证明方法 $1$ 的正确性。

考虑证明结论：若存在任意合法方案，则必然可以通过方法 $1$ 构造出一种。

假设存在一种合法方案使颜色 $x$ 在构造过程中根据方法 $1$ 所述应放入一个剩余容量为 $A$ 的块 $a$，然而实际放入了一个剩余容量为 $B$ 的块 $b$（$A > B$）。若方案本质不同，则 $a$ 的这 $A$ 单位容量中最终不存在颜色 $x$。那么 $a$ 的这 $A$ 单位容量中必然存在至少一种 $b$ 的对应 $B$ 单位容量中不存在的颜色（注意由于以一定顺序枚举颜色，前面选的颜色对当前序列无影响，所以这里拿出两块中这 $A, B$ 点容量单独分析），将这种颜色与 $b$ 中的颜色 $x$ 交换，两个块仍满足其中均无重复颜色。则此时必然存在一个将 $x$ 放入 $a$ 的合法方案。结论得证。

现在证明方法 $2$。

每个块中颜色互不相同，说明一个颜色应放入不同的块内。在建立颜色与块的匹配时，不难发现二者实际上是对称的。

暴力地说，假如块的容量集合为 $S_1$，颜色的个数集合为 $S_2$，这种情况的合法性与块容量集合为 $S_2$，颜色个数集合为 $S_1$ 的情况的合法性完全相同。

于是方法 $2$ 与方法 $1$ 是对称的，自然正确。

---

## 作者：_Diu_ (赞：2)

赛时没调出来赛后 5min 过。来分享一下神秘做法。

## 题目大意

有 $n$ 个球，每个球有颜色。有 $m$ 个货架，第 $i$ 个货架只能放 $s_i$ 个球。保证 $\sum s_i=n$。

第 $i$ 个货架放的球排成一排，需要满足任意一对颜色相同的球的距离 $\ge d_i$。两个球的距离定义为下标之差。

判断是否存在解，若存在则构造方案。

$\sum n,m\le2e5$。

## 解法

不知道为什么一眼网络流。可能这就是脑电波对接失败给我带来的自信！

设 $c_i$ 表示颜色为 $i$ 的球的数量，用 $(0,i)$ 表示。左侧建立 $n$ 个点表示每种颜色，右侧建立 $2m$ 个点，每两个点表示一个货架，分别用 $(1,j,0),(1,j,1)$ 表示。

建模如下：

源点 $S$ 连向点 $(0,i)$，流量为 $c_i$。

点 $(1,j,0)$ 连向汇点 $T$，流量为 $s_i$。

点 $(0,i)$ 连向点 $(1,j,0)$，流量为 $\lfloor\frac{s_j}{d_j}\rfloor$。

点 $(0,i)$ 连向点 $(1,j,1)$，流量为 $1$。

点 $(1,j,1)$ 连向点 $(1,j,0)$，流量为 $s_j\bmod d_j$。

核心观察是对于每个货架，要求最多有 $s_j\bmod d_j$ 种颜色的球出现 $\lfloor\frac{s_j}{d_j}\rfloor+1$ 次，其他每种颜色最多出现 $\lfloor\frac{s_j}{d_j}\rfloor$ 次。因此就有了上述建模。

容易发现判合法即为判断上述网络流模型能否满流，直接 Hall 定理判断：对于左侧若干流量，判断右边能够流出的流量总和能否够用。

检查合法性考虑找到最紧的限制，枚举 $k$，找到左侧 $c_i$ 最大的 $k$ 个点，右侧的流量即为 $\sum min(d_j,k)\times \lfloor\frac {s_j}{d_j}\rfloor+\min(s_j\bmod d_j,k)$。可以 $O(n)$ 判断。

但是本题要求构造方案。边数 $O(nm)$ 流不动哇。我们想办法每次花较少的时间确定 $1$ 单位的流量，保证 Hall 定理成立，不退流即可。

先枚举右侧所有流经 $(1,j,1)$ 的点，贪心选择 $c_i$ 最大的若干个点。然后再依次枚举右边所有其他边，同样贪心选择 $c_i$ 最大的点一个一个连，如果一种颜色连超过 $\lfloor \frac{s_i}{d_i}\rfloor$ 次就不连了。使用堆简单维护即可。

同一个货架内部分配也是类似，一种颜色用过之后在 $d_i$ 次后重新加入备选队列，同样贪心选择剩下最多的颜色，同样使用堆维护即可。

复杂度 $O(n\log n)$

最后发现建模并没有什么卵用。最开始的时候贪心想法是把同种颜色尽量一起连，没过，不知道这样是错的还是写的有问题，只能说明自己菜吧！

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int T;
int n,m;
int c[N],id[N],t[N],d[N],s[N];
bool cmp(int a,int b){
	return c[a]>c[b];
}
vector<int> g;
int vs[N],ts[N];
vector<pair<int,int> > vc[N],rs;
void solve(int i){
	priority_queue<pair<int,int> > q; 
	for(int p:g){
//		printf("Node:%d %d\n",p,vs[p]);
		q.push(make_pair(vs[p],p));
	}
	for(int j=1;j<=t[i];j++)vc[j].clear();
	for(int j=1;j<=t[i];j++){
		for(pair<int,int> p:vc[j])q.push(p);
		pair<int,int> p=q.top();q.pop();
		printf("%d ",p.second);
		--vs[p.second];
		if(vs[p.second])vc[j+d[i]].push_back(make_pair(vs[p.second],p.second));
	}
	puts("");
}
signed main(){
	scanf("%d",&T);
	for(;T--;){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)c[i]=0;
		for(int x,i=1;i<=n;i++)scanf("%d",&x),c[x]++;
		for(int i=1;i<=m;i++)scanf("%d",&t[i]);
		for(int i=1;i<=m;i++)scanf("%d",&d[i]);
		for(int i=1;i<=n;i++)s[i]=0;
		s[1]=m;
		for(int i=1;i<=m;i++)s[1]+=t[i]/d[i],s[d[i]+1]-=t[i]/d[i],s[t[i]%d[i]+1]--;
		for(int i=2;i<=n;i++)s[i]+=s[i-1];
		for(int i=1;i<=n;i++)id[i]=i;sort(id+1,id+n+1,cmp);
		int val=0,flg=0;
		for(int i=1;i<=n&&!flg;i++){
			val-=c[id[i]],val+=s[i];
			if(val<0)flg=1;
		}
		if(flg){puts("-1");continue;}
		priority_queue<pair<int,int> > q;
		for(int i=1;i<=n;i++)if(c[i])q.push({c[i],i});
		for(int i=1;i<=m;i++){
			for(int j=0;j<t[i]%d[i];j++){
				pair<int,int> p=q.top();q.pop();
				g.push_back(p.second),++vs[p.second];p.first--;
				if(p.first)rs.push_back(p);
			}
			for(pair<int,int> p:rs)q.push(p);rs.clear();
			int sum=t[i]/d[i]*d[i];
			for(;sum;){
				pair<int,int> p=q.top();q.pop();
				if(!vs[p.second])g.push_back(p.second);
				vs[p.second]++,ts[p.second]++,sum--,p.first--;
				if(p.first){
					if(ts[p.second]!=t[i]/d[i])q.push(p);
					else rs.push_back(p);
				}
			}
			for(pair<int,int> p:rs)q.push(p);rs.clear();
//			while(!q.empty()){
//				pair<int,int> p=q.top();q.pop();
//				printf("%d %d\n",p.first,p.second);
//				rs.push_back(p);
//			}
//			for(pair<int,int> p:rs)q.push(p);rs.clear();
//			return 0;
			solve(i);
			for(int x:g)ts[x]=0;
			g.clear();
		}
	}
}
```

---

## 作者：chengning0909 (赞：1)

# [CF1893D](https://codeforces.com/problemset/problem/1893/D)

我们依次考虑每一个货架。

对于每一个货架 $i$，我们依次考虑每一个位置应该放什么颜色的立方体。

对于第 $j$ 个位置，能在这里放的颜色一定不能在 $(j - d_i, j - 1]$ 出现。

然后显然的策略是我们会选择可以选择的颜色中出现次数最多的，这样可以尽可能让同一种颜色的数量变少。

这里用一个优先队列维护出现次数和颜色即可。

```cpp
#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int N = 2e5 + 10;

int T, n, m, cnt[N], s[N], d[N];
vector<int> col[N];

void Solve() {
    cin >> n >> m;
    fill(cnt + 1, cnt + n + 1, 0);
    for (int i = 1, x; i <= n; i++) cin >> x, cnt[x]++;
    for (int i = 1; i <= m; i++) cin >> s[i];
    for (int i = 1; i <= m; i++) cin >> d[i];
    priority_queue<pii> pq;
    for (int i = 1; i <= n; i++) if (cnt[i]) pq.push({cnt[i], i});
    for (int i = 1; i <= m; i++) {
        col[i].clear(), col[i].resize(s[i] + 1);
        for (int j = 1; j <= s[i]; j++) {
            if (j > d[i] && cnt[col[i][j - d[i]]]) {
                if (cnt[col[i][j - d[i]]]) pq.push({cnt[col[i][j - d[i]]], col[i][j - d[i]]});
            }
            if (pq.empty()) {
                cout << "-1\n";
                return ;
            }
            while (1) {
                auto [ct, u] = pq.top(); pq.pop();
                if (ct == cnt[u]) {
                    cnt[u]--, col[i][j] = u;
                    break;
                }
            }
        }
        for (int j = s[i] - d[i] + 1; j <= s[i]; j++) {
            if (cnt[col[i][j]]) pq.push({cnt[col[i][j]], col[i][j]});
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= s[i]; j++) cout << col[i][j] << ' ';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> T;
    while (T--) Solve();
    return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

不妨把 $s_i$ 的空间按 $d_i$ 的长度分块，对于每个块单独处理。

显而易见的是，对于每个块，其中元素一定需要不同，不然就会存在相同的两个数的间隔不足 $d_i$。

那为什么会出现不合法情况呢？因为我们同一种元素个数太多了而其他元素稀缺而不得填入。

故为了避免上述情况，我们对于每个块贪心选择个数最多的那几种，这样可以保留个数少的元素。

维护最多可以用堆，但是不妨考虑一下为什么块与块交界处是对的。我们以 $(cnt_i,i)$ 为二元组进行堆里存储，假设在前面块里面我们取了前 $k$ 个，那么由于堆的性质，我们在后面块内取的也可以是这 $k$ 个，并且也可能有新元素的加入而使得几个数顺次向后移。

代码复杂度 $O(n \log n)$。

[code](https://codeforces.com/contest/1893/submission/296014519)。

---

## 作者：Hoks (赞：0)

## 前言
duel 到的题，好像感性理解的话不是很难。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
首先一眼就能看出来的是，给你的方块顺序是没用的，直接扔进一个桶里记录下每种颜色有多少块即可。

接着题目要求对于第 $i$ 个架子，色彩值要大于 $d_i$，那么显然也是假的，我们直接给色彩值堆成 $d_i$ 就可以不管了。

接着考虑怎么样放颜色块才最优。

考虑，对于数量很多的颜色块，因为色彩值限制，一个架子上最多放上去的同色块数量是 $\lceil\frac{k_i}{d_i}\rceil$，而数量多的同色块数量显然可能大于这个值，所以他们必然要放到很多架子上去。

那么感性的想，他们数量多，肯定优先把他们放上去好。

因为最后杂色块随便放，都可以保证色彩值大于 $d_i$，我们需要保证的只是同色块的距离要至少为 $d_i$。

那么尽可能的削减同色块的数量就变成了目标，所以对于一个架子，我们考虑把数量最多的 $d_i$ 种颜色扔上去，如果这些颜色的块的数量不够了就随便放，因为杂色仍然满足条件。
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,m,s[N],k[N],a[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='e'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='*'||c=='/'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read(),m=read();for(int i=1;i<=n;i++) a[i]=0;
    for(int i=1;i<=m;i++) e[i].clear();
    for(int i=1;i<=n;i++) a[read()]++;priority_queue<pair<int,int>>q,p;
    for(int i=1;i<=m;i++) s[i]=read();for(int i=1;i<=m;i++) k[i]=read();
    for(int i=1;i<=n;i++) if(a[i]) q.push({a[i],i});
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=s[i]/k[i];j++)
        {
            for(int l=1;l<=k[i];l++)
            {
                if(q.empty()) return put("-1\n");
                e[i].emplace_back(q.top().second);
                if(q.top().first!=1) p.push({q.top().first-1,q.top().second});
                q.pop();
            }while(!p.empty()) q.push(p.top()),p.pop();
        }
        for(int l=1;l<=s[i]%k[i];l++)
        {
            if(q.empty()) return put("-1\n");
            e[i].emplace_back(q.top().second);
            if(q.top().first!=1) p.push({q.top().first-1,q.top().second});
            q.pop();
        }while(!p.empty()) q.push(p.top()),p.pop();
    }
    for(int i=1;i<=m;i++){for(auto x:e[i]) print(x),put(' ');put('\n');}
}
signed main()
{
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Retired_lvmao (赞：0)

#### 题解

首先考虑对于给定的一个架子，假如球的颜色集合确定，应该如何安排顺序。

观察到出现无解的原因，是某些元素出现了太多次，因此，我们的策略必然要尽可能让出现次数最大的数出现次数变小。

我们不难想到一个贪心策略：每次从集合中挑出**可行的**出现次数最多的数，放在架子上。这个可以简单的使用堆进行维护。

考虑原问题，我们发现我们的策略是同样优秀的，按照同样的方式贪心即可。

用堆维护的时间复杂度 $O(n\log n)$，但实际上由于每个数的出现次数是 $O(n)$ 的，使用桶维护可能可以做到线性。

#### 代码

```
#include<bits/stdc++.h>
using namespace std;
set<pair<int,int>> s;
int n,m,a[200010],sz[200010],d[200010],cnt[200010];
vector<int> ans[200010];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		s.clear();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			cnt[i]=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),cnt[a[i]]++;
		for(int i=1;i<=n;i++)
			if(cnt[i])
				s.insert(make_pair(cnt[i],i));
		for(int i=1;i<=m;i++)
			scanf("%d",&sz[i]),ans[i].clear();
		for(int i=1;i<=m;i++)
			scanf("%d",&d[i]);
		int ok=1;
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=sz[i];j++) 
			{
				if(j>d[i]&&cnt[ans[i][j-d[i]-1]])
					s.insert(make_pair(cnt[ans[i][j-d[i]-1]],ans[i][j-d[i]-1]));
				if(s.size()==0)
				{
					ok=0;
					break;
				}
				auto it=--s.end();
				ans[i].push_back((*it).second);
				cnt[(*it).second]--;
				s.erase(it); 
			}
			for(int x:ans[i])
				if(cnt[x])
					s.insert(make_pair(cnt[x],x));
			if(ok==0)
				break;
		}
		if(!ok)
		{
			puts("-1");
			continue;
		}
		for(int i=1;i<=m;i++)
		{
			for(int x:ans[i])
				printf("%d ",x);
			puts("");
		}
	}
}
```

---

## 作者：Gmt丶FFF (赞：0)

萌新因故没打现场，打的 vp，感觉比 C 简单…

可以想到，我们其实本质是在同一个货架上尽量使不同的数更多，所以数量多的数字我们应该尽可能使其更少，那么对于一个货架，我们考虑优先放数字最多的数字，然后对于第 $i$ 时间放进去的数字，等待 $i+d$ 时间后才能重新再次放入这个数字。

可以想到这个操作可以用优先队列维护，我们每次取出剩余次数最多的那个数加入书架，并移除队列，再等待 $d$ 时刻后再重新将这个数字入队即可。

时间复杂度：$O(n\log n)$。

以下是 vp 时的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int N=2e5+5;
struct node
{
	int x,y;
};
priority_queue<node>q;
bool operator <(node x,node y)
{
	return x.y<y.y;
}
struct node2
{
	int name,s,d;
}p[N];
inline bool cmp(node2 x,node2 y)
{
	if(x.d==y.d)return x.s>y.s;
	return x.d>y.d;
}
int n,m,t[N];
vector<int>a[N];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)t[i]=0;
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			t[x]++;
		}
		for(int i=1;i<=n;i++)if(t[i])q.push({i,t[i]});
		for(int i=1;i<=m;i++)scanf("%d",&p[i].s),p[i].name=i;
		for(int i=1;i<=m;i++)scanf("%d",&p[i].d);
//		sort(p+1,p+1+m,cmp);
		bool flag=1;
		for(int i=1;i<=m;i++)
		{
			a[i].clear();
			a[i].reserve(p[i].s+1);
			a[i].push_back(0);
			for(int j=1;j<=p[i].s;j++)
			{
				if(j>p[i].d)if(t[a[i][j-p[i].d]])q.push({a[i][j-p[i].d],t[a[i][j-p[i].d]]});
				if(q.empty())
				{
					flag=0;
					break;
				}			
				int x=q.top().x;
//				cout<<q.size()<<" ?\n"; 
				q.pop();
				t[x]--;
				a[i].push_back(x);
//				cout<<i<<" "<<j<<" "<<x<<" "<<t[x]<<" ??\n";
			}
			if(!flag)break;
			for(int j=p[i].s-p[i].d+1;j<=p[i].s;j++)if(t[a[i][j]])q.push({a[i][j],t[a[i][j]]});
		}
		if(!flag)
		{
			puts("-1");
			continue;
		}
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=p[i].s;j++)printf("%d ",a[i][j]);
			printf("\n");
		}
//		cout<<"????\n";
//		cout<<q.size()<<" asdfasfhg"<<endl;
	}
	return 0;
}
/*
1
7 3
1 2 2 2 2 3 4
1 2 4
1 2 4
*/
```


---

## 作者：Galex (赞：0)

先考虑所有 $s_i=d_i$，即要求每行的数互不相同怎么做。显然有贪心策略：逐行考虑，每一行填在剩余的数中出现次数最多的 $s_i$ 个颜色。

然后考虑 $s_i>d_i$，发现其实差不多，仍然逐行逐个考虑。假设考虑到第 $i$ 行第 $j$ 个，则 $ans_{i,j}$ 为在剩余的颜色中出现次数最多，且在 $ans_{i,j-d_i+1}$ 到 $ans_{i,j-1}$ 中没出现过的颜色。感性理解一下这样应该是最优的。

那么考虑如何维护 $ans_{i,j}$。考虑用线段树维护每种颜色的出现次数，我们可以在求出 $ans_{i,k}$ 时在线段树上给 $ans_{i,k}$ 这种颜色打个标记，表示这种颜色目前不可用了。然后在求 $ans_{i,k+d_i}$ 时把 $ans_{i,j}$ 的标记取消。这样 $ans_{i,j}$ 就是目前线段树上没有打标记的出现次数最多的颜色，容易维护。

具体实现可以在线段树上每个叶子维护一个 $val$，每个点维护一个 $mx$。打标记就相当于把对应叶子的 $mx$ 设成 $0$，取消标记就相当于把对应叶子的 $mx$ 设成 $val$。查询时查询根的 $mx$ 就行。时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n, m;
int a[200005], s[200005], d[200005];
int cnt[200005];
vector<int> back[200005], ans[200005];

struct SGT {
	#define ls (p << 1)
	#define rs (p << 1 | 1)
	#define mid ((l + r) >> 1)
	int val[800005], mx[800005], mxp[800005];
	void maintain(int p) {
		mx[p] = max(mx[ls], mx[rs]);
		mxp[p] = mx[ls] > mx[rs] ? mxp[ls] : mxp[rs];
	}
	void build(int l, int r, int p) {
		if (l == r) {
			mx[p] = val[p] = cnt[l], mxp[p] = l;
			return ;
		}
		build(l, mid, ls), build(mid + 1, r, rs);
		maintain(p);
	}
	void mdf(int l, int r, int p, int x, int v) {
		if (l == r) {
			val[p] += v, mx[p] += v;
			return ;
		}
		x <= mid ? mdf(l, mid, ls, x, v) : mdf(mid + 1, r, rs, x, v);
		maintain(p);
	}
	void mdf2(int l, int r, int p, int x, int op) {
		if (l == r) {
			mx[p] = op ? val[p] : 0;
			return ;
		}
		x <= mid ? mdf2(l, mid, ls, x, op) : mdf2(mid + 1, r, rs, x, op);
		maintain(p);
	}
	int qry() {
		return !mx[1] ? -1 : mxp[1];
	}
} t;

void work() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		cnt[i] = 0;
	for (int i = 1; i <= n; i++)
		a[i] = read(), cnt[a[i]]++;
	for (int i = 1; i <= m; i++)
		s[i] = read();
	for (int i = 1; i <= m; i++)
		d[i] = read();
	t.build(1, n, 1);
	for (int i = 1; i <= m; i++) {
		ans[i].clear();
		for (int j = 1; j <= s[i] + 1; j++)
			back[j].clear();
		for (int j = 1; j <= s[i]; j++) {
			for (int k : back[j])
				t.mdf2(1, n, 1, k, 1);
			int p = t.qry();
			if (p == -1) {
				printf("-1\n");
				return ;
			}
			ans[i].push_back(p);
			t.mdf(1, n, 1, p, -1), t.mdf2(1, n, 1, p, 0);
			back[min(s[i] + 1, j + d[i])].push_back(p);
		}
		for (int k : back[s[i] + 1])
			t.mdf2(1, n, 1, k, 1);
	}
	for (int i = 1; i <= m; i++, putchar('\n'))
		for (int j : ans[i])
			printf("%lld ", j);
}

signed main() {
	int T = read();
	while (T--)
		work();
	return 0;
}
```

---

