# Yet Another Division Into Teams

## 题目描述

你的大学里面有 $n$ 个学生，第 $i$ 个学生的水平为 $a_i$。作为一名教练，你想把他们分成若干个队伍已准备即将到来的 ICPC 决赛。

每一支队伍至少要有三名学生，并且每一位学生恰好属于一支队伍。定义一支队伍的极差为所有这支队伍的学生中水平最高的与最低的的水平之差。形式化的说，如果一支队伍中有 $k$ 个学生，水平分别为 $a_{i_1},a_{i_2},\cdots,a_{i_n}$，那么这支队伍的极差为 $\max\limits_{j=1}^{k}a_{i_j}-\min\limits_{j=1}^{k}a_{i_j}$。

总共的极差为所有队伍的极差之和。

你需要找到一种最优的分组方案使得总共的极差最小。

## 样例 #1

### 输入

```
5
1 1 3 4 2
```

### 输出

```
3 1
1 1 1 1 1 
```

## 样例 #2

### 输入

```
6
1 5 12 13 2 15
```

### 输出

```
7 2
2 2 1 1 2 1 
```

## 样例 #3

### 输入

```
10
1 2 5 129 185 581 1041 1909 1580 8150
```

### 输出

```
7486 3
3 3 3 2 2 2 2 1 1 1 
```

# 题解

## 作者：lgswdn_SA (赞：4)

显然这是一个 $dp$。为了最小化极差我们进行排序。

$f(i)$ 表示前 $i$ 个人的分组的最小极差和。

$$
f(i)=\min f(j)+\operatorname{diversity}(j+1,i)
$$

可以用 $O(n^2)$ 完成。

这玩意儿又和 $i$ 有关不能单调队列，决策也没有单调性。

由于一般来说分组不会特别大所以我们可以对 $k$ 做一个优化，所以我们的 $k$ 可以不用在 $[1,i-4]$ 中枚举而是选择一个长度 $l$ 使最大分组大小为 $l$。我们可以在不 TLE 的情况下取得 $l$ 最大值。

以上皆为没有正确性证明的优化。

---

到底 $l$ 开到多少合适呢？经过尝试，$l=5$ 是最小的能保证正确性的 $l$。稍微证明一下。如果 $l=6$，我们看如下分析。

设这 $6$ 个人分别为 $x_1\ge x_2\ge ...\ge x_6$，如果 $6$ 个人分组那么答案为 $x_6-x_1$，如果前 $3$ 个分一组后 $3$ 个分一组那么答案为 $x_6-x_4+x_3-x_1\le x_6-x_1$，所以不会更差。

所以我们转移方程变成了这个。

$$
f(i)=\min_{j\in [i-6,i-4]} f(j)+\operatorname{diversity}(j+1,i)
$$

记录下决策即可。

```cpp
#include<bits/stdc++.h> 
#define int long long
#define rep(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
const int N=200009;

int n,f[N],p[N],cnt,ans[N];

struct node{int id,val;}a[N];
bool cmp(const node&a,const node&b) {
	return a.val<b.val;
}

signed main() {
	scanf("%lld",&n);
	rep(i,1,n) scanf("%lld",&a[i].val), a[i].id=i;
	sort(a+1,a+n+1,cmp);
	rep(i,1,n) {
		f[i]=0x3f3f3f3f;
		rep(j,max(0ll,i-5),i-3)
			if(f[j]+a[i].val-a[j+1].val<f[i])
				f[i]=f[j]+a[i].val-a[j+1].val,p[i]=j;
	}
	int x=n;
	while(x) {
		++cnt;
		rep(i,p[x]+1,x) ans[a[i].id]=cnt;
		x=p[x];
	}
	printf("%lld %lld\n",f[n],cnt);
	rep(i,1,n) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：81179332_ (赞：2)

完全没有想到啊。。

我们至多将 $6$ 个人分为一组，因为如果我们将 $6$ 个人分为一组，我们可以将 $6$ 个人排序后，取前 $3$ 个一组，后 $3$ 个一组，可以证明，答案不会变差

事实上，分的组越多越好，只是因为本题限制了每组至少 $3$ 个人，所以 $4$、$5$ 的分组由于无法拆分也可能是最优的

设 $f_i$ 表示前 $i$ 个人的最小答案，$f_i$ 可以从 $f_j(j\in[i-5,i-3])$ 转移得到，记录一下转移位置来输出方案

```cpp
//timeuse:15min
const int N = 200010;
struct data { ll v;int id; }a[N];
int n,ans[N];
ll f[N];int pos[N];
int main()
{
	n = read();for(int i = 1;i <= n;i++) a[i].v = read(),a[i].id = i;
	sort(a + 1,a + 1 + n,[&](data u,data v) { return u.v < v.v; });
	memset(f,63,sizeof(f)),f[0] = 0;
	for(int i = 3;i <= n;i++)
		for(int j = 3;j <= 5 && i - j >= 0;j++)
			if(i - j >= 0 && f[i] > f[i - j] + a[i].v - a[i - j + 1].v)
				f[i] = f[i - j] + a[i].v - a[i - j + 1].v,pos[i] = i - j;
	int now = n,cnt = 0;
	while(now)
	{
		cnt++;
		for(int i = now;i > pos[now];i--) ans[a[i].id] = cnt;
		now = pos[now];
	}pprint(f[n]),fprint(cnt);
	for(int i = 1;i <= n;i++) pprint(ans[i]);
}
```

---

## 作者：lx_zjk (赞：1)

题目大意 将$n$个人分组 最小化每组的极差

首先有一个引理 一个组别人数不超过5

证明如下

假设有$a b c d e f6$个数字 

不妨设设 $a < b < c < d < e < f$ 

假设分成这一个组 
$$ans1 = (f - a)$$ 

那么我们考虑继续将其分组 $(a < b < c) (d < e < f)$ 
$$ans2 = f - d + c - a = (f - a) + (c - d);$$

因为$(c < d)$ 所以 $ans2 < ans1$ 

所以可以证明 只能分成 (3 - 5)个人一组 

证明完毕 $！$

我们有一个略含贪心的$dp$ 设$f[i]$ 表示$(0 -> (i - 1))$都已经分完的最小极差和

那么对于$i$ 我们有如下的三种策略
```cpp
f[0] = 0; 
chkmin (f[i + 5], f[i] + a[i + 4] - a[i]);
chkmin (f[i + 4], f[i] + a[i + 3] - a[i]);
chkmin (f[i + 3], f[i] + a[i + 2] - a[i]);
```

然后就做完了！
# code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <queue>

using namespace std;

template <typename T> void chkmax(T &x, T y) {x = x > y ? x : y;}
template <typename T> void chkmin(T &x, T y) {x = x > y ? y : x;}

typedef long long ll;

const int INF = 2139062143;

#define DEBUG(x) std::cerr << #x << " = " << x << std::endl

inline ll read() {
    ll f = 1, x = 0; char ch;
    do {ch = getchar(); if (ch == '-') f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0'; ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
}

#define int ll

const int MAX_N = 2e5 + 25;

int n, f[MAX_N], pos[MAX_N], group[MAX_N];

struct Node {
	int pos, val;
	bool operator < (const Node &rhs) const {
		return val < rhs.val;
	}
} a[MAX_N];

signed main() {
	n = read ();
	a[n].val = a[n + 1].val = a[n + 2].val = a[n + 3].val = INF;
	for (int i = 0; i < n; i ++ ) a[i].val = read (), a[i].pos = i;
	sort (a, a + n);
	memset (f, 127, sizeof (f));
	f[0] = 0;
	for (int i = 0; i < n; i ++ ) {
		if (f[i + 5] > f[i] + a[i + 4].val - a[i].val) {
			pos[i + 5] = i;
			f[i + 5] = f[i] + a[i + 4].val - a[i].val;
		}
		if (f[i + 4] > f[i] + a[i + 3].val - a[i].val) {
			pos[i + 4] = i;
			f[i + 4] = f[i] + a[i + 3].val - a[i].val;			
		}
		if (f[i + 3] > f[i] + a[i + 2].val - a[i].val) {
			pos[i + 3] = i;
			f[i + 3] = f[i] + a[i + 2].val - a[i].val;
		}
	}
	int cur = n, cnt = 1;
	while (cur) {
		for (int i = cur - 1; i >= pos[cur]; i -- ) group[a[i].pos] = cnt;
		cnt ++ ;
		cur = pos[cur];
	}
	printf ("%I64d %I64d\n", f[n], cnt - 1);
	for (int i = 0; i < n; i ++ ) printf ("%I64d ", group[i]);
	return 0;
}
```

---

## 作者：Exscallop64_ (赞：0)

# CodeForces 1256E

### 题目简述

有 $n$ 个学生，每个学生有一个能力值 $a_i$，你需要将 $n$ 个学生分成若干组，使各个组的“差异”总和最小，求其最小值、对应的分的组数、每个学生所属队伍的编号。

+ 一个组的差异值定义为：若该组有 $k$ 个人，依次为 $i_1,i_2 \dots i_k$，则该组的差异值为：

$$
\max_{j=1}^{k} a_{i_j} - \min_{j=1}^{n} a_{i_j}
$$

### 思路

提供一种比较冷门的思考方式。

考虑序列型 DP：

我们有一种贪心思路，显然让每组内的 $a_{i_1},a_{i_2} \dots a_{i_k}$ 相邻两个越接近越好，因此可以先从小到大排序。

状态：$dp_i$ 表示前 $i$ 个人产生的差异值最小值。

初始状态：$dp_i = a_i - a_1(3 \le i \le 5)$

转移：$dp_i = \min(dp_i, dp_j + a_i - a_{j+1})(6 \le i \le n, 3 \le j \le i - 3)$

显然 $O(n^2)$ 超时，我们不妨将 $a_i$ 提出来，把转移式改为如下转移式：

$$
dp_i = (\min_{j=3}^{i-3} dp_j - a_{j+1}) + a_i
$$

注意到 $\min_{j=3}^{i-3}$ 显然是一个前缀结构（注意 $j=1/2$ 时是无效状态），可以用前缀最小值 $mn_i$ 表示 $dp_j - a_{j+1} (3 \le j \le i)$ 最小时对应的下标 $j$，以此优化 DP。

因此，转移式变为：

$$
dp_i = dp_{mn_{i-3}} + a_i - a_{mn_{i-3}+1}
$$

所以，DP 可以优化为在 $O(n)$ 时间复杂度内求出答案。

### 复杂度分析

+ 时间复杂度：DP 动态规划 $O(n)$，排序 $O(n \log n)$，总时间复杂度 $O(n \log n)$。

+ 空间复杂度：$O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 3e5 + 5;
const ll INF = 1e18;

int n, team[N];
ll dp[N], mn[N];

struct Node{
  int x, id;
  bool operator < (const Node &i) const{
    return x < i.x;//按能力值排序
  }
}a[N];

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cin.tie(0);
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i].x;
    a[i].id = i;
  }
  sort(a + 1, a + 1 + n);
  for(int i = 3; i <= 5; i++){//初始状态
    dp[i] = a[i].x - a[1].x;
    mn[i] = mn[i - 1];
    if(dp[mn[i - 1]] - a[mn[i - 1] + 1].x > dp[i] - a[i + 1].x){
      mn[i] = i;
    }
  }
  for(int i = 6; i <= n; i++){
    dp[i] = dp[mn[i - 3]] + a[i].x - a[mn[i - 3] + 1].x;
    mn[i] = mn[i - 1];
    if(dp[mn[i - 1]] - a[mn[i - 1] + 1].x > dp[i] - a[i + 1].x){//更新mn[i]
      mn[i] = i;
    }
  }
  cout << dp[n] << " ";//输出
  int cnt = 0;
  for(int i = n; i; i = mn[i - 3]){
    cnt++;
  }
  cout << cnt << "\n";
  for(int i = n, j = 1; i; i = mn[i - 3], j++){
    for(int k = mn[i - 3] + 1; k <= i; k++){
      team[a[k].id] = j;
    }
  }
  for(int i = 1; i <= n; i++){
    cout << team[i] << " ";
  }
  return 0;
}
``````

---

## 作者：lsr1409111459 (赞：0)

#### 1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1256E)）

##### 1.1 题目大意

你是一名ICPC教练，现在有 $n$ 名学生要参赛，每人有一个能力值。

ICPC是要分队的，每队不少于 $3$ 人，每人属于一队且仅属于一队。每队的极差为队伍中能力值最高的人的能力值与能力值最低的人的能力值的差。现在要你找出一种分队方法，使得所有队伍的极差和最小。

##### 1.2 输入格式

第一行一个整数 $n(3\leq n \leq 2·10^5)$ ，表示学生的数量。

第二行为 $n$ 个整数 $a_1,a_2,...,a_n(1 \leq a_i \leq 10^9)$ ，其中    $a_i$ 表示第 $i$ 名学生的能力值。

##### 1.3 输出格式

共两行。

第一行两个整数 $res$ 和 $k$ ，分别表示所得的极差最小和和队伍数量。

第二行为 $n$ 个整数 $t_1,t_2,...,t_n(1\leq t_i \leq k)$ ，其中 $t_i$ 表示第 $i$ 名学生属于的队伍编号。

如果有多组答案，输出一组即可。不一定要最小化队伍的数量。

共 $q$ 行。

每行一个长度为 $n$ 的二进制串，为最多 $k$ 次操作后字典序最小的二进制串。

#### 2 解题思路

本题是一道 $DP$ 题。首先将整个序列从小到大排序。

我们设 $dp[i]$ 表示前 $i$ 个位置所能达到的极差的最小值。

状态转移方程为 $dp[i]=min(dp[i],dp[j]+a[j]-a[i])(4 \leq j \leq i-3)$ 。

这样复杂度为 $O(n^2)$ ，毫无疑问会 $TLE$ 。

因此我们考虑一条特性：每个队伍的人数只能为 $3,4,5$ 。

假设我们队伍的人数为 $6$ ，那么一定可以拆分为两个人数为 $3$ 的队伍，使得总极差值不变或变小。

因为 $a[6]-a[1] \geq a[6]-a[4]+a[3]-a[1]$ 。

所以我们在状态转移时， $j$ 的枚举范围就可以大幅减小： $i-5 \leq j \leq i-3$ 。

这样复杂度仅为 $O(n)$ ，复杂度大大降低了。（当然还有排序的复杂度，所以其实是 $O(nlogn)$ ）

#### 3 解题代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n;
struct node
{
    int i,x,start,ans;
}a[200010];
long long dp[200010];
bool cmp(node x,node y){return x.x<y.x;}
bool cmp2(node x,node y){return x.i<y.i;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].x);
        a[i].i=i;
        dp[i]=INT_MAX;//dp初始化一个很大的值，因为我们要找最小值
    }
    sort(a+1,a+1+n,cmp);
    for(int i=3;i<=5;i++)//预处理前5个dp值，其中dp[1],dp[2]无答案
    {
        dp[i]=a[i].x-a[1].x;
        a[i].start=1;
    }
    for(int i=6;i<=n;i++)
    {
        for(int j=i-5;j<=i-3;j++)
        {
            if(dp[i]>dp[j]+a[i].x-a[j+1].x)
            {
                dp[i]=dp[j]+a[i].x-a[j+1].x;
                a[i].start=j+1;//a[i].start记录当前元素所属组的起始元素位置
            }
        }
    }
    int cnt=0;
    for(int i=n;i>=1;i--)//按记录的start值进行答案赋值
    {
        cnt++;
        for(int j=a[i].start;j<=i;j++)
            a[j].ans=cnt;
        i=a[i].start;
    }
    sort(a+1,a+1+n,cmp2);
    printf("%d %d\n",dp[n],cnt);
    for(int i=1;i<=n;i++)printf("%d ",a[i].ans);
    printf("\n");
    return 0;
}
```

#### 4 解题心得

考场上没有解出来的 $DP$ 题，或者说看到题就没有意识到是 $DP$ 题，或者是意识到是 $DP$ 题但是没有构造转移方程的思维。总而言之， $DP$ 这个大专题是该练了。校队寒假集训今天讲了 $DP$ ，等给题之后做一做。 $DP$ 的大块复习诸如数位 $DP$ ，状压 $DP$ ，树形 $DP$ 等也该着手进行了。

---

## 作者：HDWR (赞：0)

## 解题报告
首先显然是按从小到大顺序选最优。于是先排个序。

设 `f[i]` 表示前 $i$ 个学生组队完的最小极差和。

转移需要从 $1$ 开始枚举上一组是在哪截止的，取最小的那一个记录方案。

于是直接套一个前缀最小值优化。

## 代码实现

写的有亿点点长。主要还是输出方案不熟练。

```cpp
const int MAXN = 2e5 + 10;

struct T { lli val, id; } ts[MAXN];

bool cmp1(T x, T y) { return x.val < y.val; }
bool cmp2(T x, T y) { return x.id < y.id; }

int n; lli aa[MAXN];
lli dp[MAXN], prefdp[MAXN];
int last[MAXN], last_pref[MAXN];
// last[i] 记录的是 f[i] 从哪转移过来
// last_pref[i] 记录的是 prefdp[i] 在 dp 数组中的下标

void getDetail() {
    /* DEBUG */ 

    int r = n;
    int now = n;
    std::vector<std::pair<int, int> > ans;
    while (now) {
        now = last[now];
        ans.push_back({now + 1, r});
        r = now;
    }
    std::reverse(ALL(ans)); int teams = 0;
    for (auto v : ans) {
        ++teams;
        for (int i = v.first; i <= v.second; ++i) ts[i].val = teams;
    } cout << ' ' << teams << endl;
    std::sort(ts + 1, ts + 1 + n, cmp2);
    for (int i = 1; i <= n; ++i) cout << ts[i].val << ' ';
    cout << endl;
}

int main() {
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    
    for (int i = 1; i <= n; ++i) { cin >> ts[i].val; ts[i].id = i; }
    std::sort(ts + 1, ts + 1 + n, cmp1);
    for (int i = 1; i <= n; ++i) {
        aa[i] = ts[i].val;
    }

    memset(dp, 0x3f, sizeof dp); memset(prefdp, 0x3f, sizeof prefdp);
    dp[3] = aa[3] - aa[1]; prefdp[3] = dp[3] - aa[4]; 
    last[3] = 0; last_pref[3] = 3;
    for (int i = 4; i <= n; ++i) {
        // dp[i] = std::min(dp[i - 1] - aa[i - 1], prefdp[i - 3]) + aa[i];
        // prefdp[i] = std::min(prefdp[i - 1], dp[i] - aa[i + 1]);
        
        if (dp[i - 1] - aa[i - 1] < prefdp[i - 3]) {
            dp[i] = dp[i - 1] - aa[i - 1];
            last[i] = last[i - 1];
        } else {
            dp[i] = prefdp[i - 3];
            last[i] = last_pref[i - 3];
        } dp[i] += aa[i];
        if (prefdp[i - 1] < dp[i] - aa[i + 1]) {
            prefdp[i] = prefdp[i - 1];
            last_pref[i] = last_pref[i - 1];
        } else {
            prefdp[i] = dp[i] - aa[i + 1];
            last_pref[i] = i;
        }
    } cout << dp[n];
    getDetail();
    return 0;
}
```

---

## 作者：zhlzt (赞：0)

### 题解

这里是正解，但是我们要以一个乱搞的开头引入正解。

我们充分发扬人类智慧，可以猜出这样的结论：最优解中一支队伍的人数必定不超过 $m$，$m$ 是一个较小的常数。


将 $a$ 升序排序，贪心地取连续的一段组成一支队伍。这样有一个显然的 dp，即设 $dp_i$ 表示前 $i$ 个人组队后最小的极差之和。

我们要求出 $m$ 的最小值，首先考虑到一个队伍最少有 $3$ 人，所以若有 $4$ 或 $5$ 个人只能分成一组，故 $m\ge 5$。

而若存在一支由 $6$ 人组成的队伍，不妨设他们的水平分别为 $b_1,b_2,b_3,b_4,b_5,b_6$，其中 $b_1\le b_2\le b_3\le b_4 \le b_5\le b_6$，则有：

$$b_3-b_1+b_6-b_4\le b_6-b_1$$

所以将其拆分成 $2$ 个 $3$ 人队伍必定不劣，对于由大于 $6$ 人组成的队伍同理，故 $m\le 5$。

综上所述，$m=5$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
pair<ll,int>a[maxn];
ll dp[maxn]; 
int pre[maxn],ans[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].first;
	for(int i=1;i<=n;i++) a[i].second=i;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		dp[i]=5e15;
		for(int j=max(0,i-5);j<=i-3;j++){
			ll val=a[i].first-a[j+1].first;
			if(dp[j]+val<dp[i]){
				dp[i]=dp[j]+val,pre[i]=j;
			}
		}
	}
	int id=1;
	for(int i=n;i>0;id++){
		for(int j=i;j>pre[i];j--){
			ans[a[j].second]=id;
		}
		i=pre[i];
	}
	cout<<dp[n]<<' '<<--id<<'\n';
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
} 
```

---

