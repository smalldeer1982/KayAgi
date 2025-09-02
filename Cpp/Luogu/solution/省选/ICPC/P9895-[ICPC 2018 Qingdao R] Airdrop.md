# [ICPC 2018 Qingdao R] Airdrop

## 题目描述

PUBG 是一款多人在线大逃杀视频游戏。在游戏中，最多一百名玩家跳伞到一个岛上，搜寻武器和装备以击杀其他玩家，同时避免自己被击杀。空投是游戏中的一个关键元素，因为空投通常携带强大的武器或大量补给，帮助玩家生存。

考虑游戏的战场是一个二维平面。一个空投刚刚降落在点 $(x_0, y_0)$（$x_0$ 和 $y_0$ 都是整数），战场上的所有 $n$ 名玩家，其中 $(x_i, y_i)$（$x_i$ 和 $y_i$ 都是整数）表示第 $i$ 名玩家的初始位置，开始以以下模式向空投移动：

- 如果一个活着的玩家在这个时间单位开始时的位置不等于 $(x_0, y_0)$，他将开始他的下一步移动。
- + 假设他当前在点 $(x, y)$。对于他的下一步移动，他将考虑四个点 $(x, y - 1)$、$(x, y + 1)$、$(x - 1, y)$ 和 $(x + 1, y)$。
- + 他将选择其中一个到空投 $(x_0, y_0)$ 的曼哈顿距离最小的点作为他下一步的目的地。回忆一下，两点 $(x_a, y_a)$ 和 $(x_b, y_b)$ 之间的曼哈顿距离定义为 $|x_a - x_b| + |y_a - y_b|$。
- + 如果两个或更多点到空投的曼哈顿距离相同，他将使用以下优先级规则来打破平局：$(x, y - 1)$ 优先级最高，$(x, y + 1)$ 优先级第二，$(x - 1, y)$ 优先级第三，$(x + 1, y)$ 优先级最低。
- + 在这个时间单位结束时，他到达他的目的地。
- 如果一个活着的玩家在这个时间单位开始时的位置等于 $(x_0, y_0)$，他将继续用空投中的补给填满他的背包，并停留在 $(x_0, y_0)$。

但战斗很激烈，几乎不可能所有玩家都安全到达空投。如果两个或更多玩家在点 $(x', y')$ 相遇，且 $(x', y')$ 不是 $(x_0, y_0)$，他们将互相搏斗并全部阵亡，没有人存活。

BaoBao 是该游戏的忠实粉丝，对成功到达空投位置的玩家数量感兴趣，但他不知道 $x_0$ 的值。给定 $y_0$ 的值和每个玩家的初始位置，请帮助 BaoBao 计算对于所有 $x_0 \in \mathbb{Z}$（$\mathbb{Z}$ 是所有整数的集合，注意 $x_0$ 可以是正数、零或负数），成功到达空投位置的玩家数量的最小值和最大值。

## 说明/提示

我们现在解释第一个样例测试用例。

为了得到 $p_\text{min} = 1$ 的答案，应该考虑 $x_0 = 3$。下表显示了当 $x_0 = 3$ 时每个玩家在每个时间单位结束时的位置。

为了得到 $p_\text{max} = 3$ 的答案，应该考虑 $x_0 = 2$。下表显示了当 $x_0 = 2$ 时每个玩家在每个时间单位结束时的位置。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
3 2
1 2
2 1
3 5
3 3
2 1
2 5
4 3
2 3
1 3
4 3```

### 输出

```
1 3
0 3
2 2```

# 题解

## 作者：immortal_immortals (赞：2)

## 思路
1. 将所有点按 $x$ 坐标从小到大排序，分别算出空投左边的点和右边的点到空投的曼哈顿距离(相对的)。
1. 从左往右扫一遍 $x$ 值，每扫到一个 $x$ 值，将所有相同 $x$ 值的点的曼哈顿距离加上，若之前没有在此距离上存活的点，则此点存活。否则此距离上的点全部完蛋。同时记录每个 $x$ 值有多少存活的点。
1. 再从右往左扫一遍。
1. 再扫一遍 $x$ 值，取左边存活的点 $+$ 右边存活的点 $+$ 横坐标为 $x$ 的点的最大值作为答案。

时间复杂度 $O(t \times n)$。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
struct aa
{
    int x,y;
    bool operator<(aa b)
	{
		return x<b.x;
	}
}a[100005];
int t,n,yy,mi,im,ans1,ans2,mh[2][100005],f[200010],js[3][100005];
int main()
{
    t=read();
    for(int ll=1;ll<=t;ll++)
	{
        memset(js,0,sizeof js);
        cin>>n>>yy;
        for(int i=1;i<=n;i++)
		{
			a[i].x=read();
			a[i].y=read();
			a[i].x++;
		}
        sort(a+1,a+1+n);
		mi=a[1].x;
		im=a[n].x;
        for(int i=1;i<=n;i++)
		{
            mh[0][i]=abs(yy-a[i].y)-a[i].x+100000;
            mh[1][i]=abs(yy-a[i].y)+a[i].x;
        }
        memset(f,0,sizeof(f));
        for(int i=mi,j=1,k;i<=im;i++)
		{
            js[0][i]=js[0][i-1];
            k=j;
            for(;j<=n&&a[j].x==i;j++)
			{
                if(f[mh[0][j]]==0)
				{
					f[mh[0][j]]=1;
					js[0][i]++;
				}
                else if(f[mh[0][j]]==1)
				{
					f[mh[0][j]]=-1;
					js[0][i]--;
				}
            }
            j=k;
            for(;j<=n&&a[j].x==i;j++)
			{
				if(f[mh[0][j]]==-1)
				{
					f[mh[0][j]]=0;
				}
			}
        }
        memset(f,0,sizeof(f));
        for(int i=im,j=n,k;i>=mi;i--)
		{
            js[1][i]=js[1][i+1];
            k=j;
            for(;j>=1&&a[j].x==i;j--) 
			{
                if(f[mh[1][j]]==0)
				{
					f[mh[1][j]]=1;
					js[1][i]++;
				}
                else if(f[mh[1][j]]==1)
				{
					f[mh[1][j]]=-1;
					js[1][i]--;
				}
            }
            j=k;
            for(;j>=1&&a[j].x==i;j--)
			{
				if(f[mh[1][j]]==-1)
				{
					f[mh[1][j]]=0;
				}
			}
        }
        for(int i=1;i<=n;i++)
		{
			js[2][a[i].x]++;
		}
		ans1=-99999999,ans2=99999999;
        for(int i=mi-1;i<=im+1;i++)
		{
            ans1=max(ans1,js[0][i-1]+js[1][i+1]+js[2][i]);
            ans2=min(ans2,js[0][i-1]+js[1][i+1]+js[2][i]);
        }
        printf("%d %d\n",ans2,ans1);
    }
    return 0;
}
```


---

## 作者：Alex_Wei (赞：1)

### K. [P9895 [ICPC2018 Qingdao R] Airdrop](https://www.luogu.com.cn/problem/P9895)

先考虑 $(x_0, y_0)$ 确定时怎么计算答案。

因为所有人都是优先沿 $y$ 轴移动，不走到 $y = y_0$ 不横向移动，所以相撞只会发生在 $y = y_0$ 这条水平线上。

将点根据 $x_i$ 和 $x_0$ 的大小关系分成三类：

- 若 $x_i = x_0$，那么他不会和任何人撞到，因为他一走到 $y = y_0$ 就安全了。
- 若 $x_i < x_0$，那么他只有可能和 $x_j < x_0$ 且与 $(x_0, y_0)$ 曼哈顿距离相同的 $(x_j, y_j)$ 撞起来。
- 若 $x_i > x_0$，同理。

现在固定曼哈顿距离相同且 $x_i < x_0$，由于这些人最终都要走到 $(x_0 - 1, y_0)$，所以最多只有一个人活下来。如果一定只是两个人相撞，则答案就是人数的奇偶性。但有可能出现三个人相撞在 $(x' < x_0, y_0)$，三个人分别从该点的上下两侧和左侧走进来的情况。按 $x$ 从小到大的顺序扫描，维护标记表示是否有人从左边走过来。

- 如果当前 $x$ 没有人，则标记不变。
- 如果当前 $x$ 有一个人，则标记改变。
- 如果当前 $x$ 有两个人，则标记清空。

扫描到 $x_0$ 时如果标记为 $1$ 则产生贡献，否则产生贡献。

现在会算 $(x_0, y_0)$ 的答案，考虑对所有 $x_0$ 求答案。

$x_0$ 从小往大扫，算 $x_i < x_0$ 的贡献。然后 $x_0$ 从大往小扫，算 $x_i > x_0$ 的贡献。两种情况对称，只研究第一种情况。

$x_0$ 从小扫到大的过程中，发现 $x_0$ 的方向和固定某个曼哈顿距离时 $x$ 扫动的方向是一致的。也就是说，$x_0$ 向右移动 $1$，只需考虑所有 $x_i = x_0$ 的点对标记的影响，而不需要重新计算答案。

还有一个问题，就是本题多测，不能对每组数据都从 $0$ 扫到 $10 ^ 5$。只有 $x_i$ 和 $x_i\pm 1$ 作为 $x_0$ 是重要的，其它 $x_0$ 都可以向左或向右移动直到它们等于 $x_i\pm 1$，而不改变答案。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;
using LL = __int128_t;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int add(int x, int y) {
  return x += y, x >= mod && (x -= mod), x;
}

struct FastMod {
  ull b, m;
  FastMod(ull b = 1) : b(b), m(ull((LL(1) << 64) / b)) {}
  ull reduce(ull a) {
    ull q = ull((LL(m) * a) >> 64);
    ull r = a - q * b; // can be proven that 0 <= r < 2 * b
    return r >= b ? r - b : r;
  }
} R;

// ---------- templates above ----------

constexpr int N = 3e5 + 5;
constexpr int V = 1e5 + 1;

int n, y;
int cnt, d[N], res[N];
struct point {
  int x, y;
  bool operator < (const point &z) const {
    return x != z.x ? x < z.x : abs(y - ::y) < abs(z.y - ::y);
  }
} c[N];

int cur, pt, buc[N], tp[N], vis[N], num, ap[N];
void init() {
  for(int i = 1; i <= num; i++) {
    buc[ap[i]] = vis[ap[i]] = tp[ap[i]] = 0;
  }
  cur = pt = num = 0;
}
int calc(int x) {
  while(pt < n && c[pt + 1].x < x) {
    int pos = V;
    if(c[++pt].y >= y) pos += c[pt].x - (c[pt].y - y);
    else pos += c[pt].x + (c[pt].y - y);
    if(!vis[pos]) ap[++num] = pos, vis[pos] = 1;
    if(pt < n && c[pt].x == c[pt + 1].x && c[pt].y + c[pt + 1].y == 2 * y) {
      if(tp[pos]) {
        buc[pos] ? cur-- : cur++;
        buc[pos] ^= 1;
      }
      tp[pos] = 1;
    }
    else tp[pos] ^= 1;
    buc[pos] ? cur-- : cur++;
    buc[pos] ^= 1;
  }
  return cur;
}

void solve() {
  cin >> n >> y, cnt = 0;
  map<int, int> mp;
  for(int i = 1; i <= n; i++) {
    cin >> c[i].x >> c[i].y;
    mp[c[i].x]++;
    d[++cnt] = c[i].x - 1;
    d[++cnt] = c[i].x;
    d[++cnt] = c[i].x + 1;
  }
  sort(d + 1, d + cnt + 1);
  cnt = unique(d + 1, d + cnt + 1) - d - 1;
  sort(c + 1, c + n + 1);
  init();
  for(int i = 1; i <= cnt; i++) {
    auto it = mp.find(d[i]);
    if(it != mp.end()) res[i] = it->second;
    else res[i] = 0;
    res[i] += calc(d[i]);
  }
  init();
  for(int i = 1; i <= n; i++) c[i].x = V - c[i].x;
  for(int i = 1; i <= cnt; i++) d[i] = V - d[i];
  reverse(c + 1, c + n + 1);
  reverse(d + 1, d + cnt + 1);
  reverse(res + 1, res + cnt + 1);
  init();
  for(int i = 1; i <= cnt; i++) res[i] += calc(d[i]);
  int mn = n, mx = 0;
  for(int i = 1; i <= cnt; i++) {
    mn = min(mn, res[i]);
    mx = max(mx, res[i]);
  }
  cout << mn << " " << mx << "\n";
}

bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T = 1;
  cin >> T;
  while(T--) solve();
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

