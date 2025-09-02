# [IOI 1994] The Buses

## 题目描述

一个人在 12:00 到达一个公交车站。他在 12:00 到 12:59 期间一直待在那里。这个公交车站被多条公交线路使用。这个人记录了公交车到达的时间。给出了公交车到达的时间。

- 同一条路线的公交车在整个小时内从 12:00 到 12:59 以固定的时间间隔到达。
- 时间以整分钟给出，从 0 到 59。
- 每条公交线路至少停靠 2 次。
- 测试示例中的公交线路数量将 $\leq 17$。
- 不同路线的公交车可能同时到达。
- 几条公交线路的首次到达时间和/或时间间隔可能相同。如果两条公交线路的起始时间和间隔相同，则它们是不同的，并且都需要呈现。

找出满足输入数据的必须停靠在公交车站的公交线路数量最少的时间表。对于每条公交线路，输出起始时间和间隔。

## 样例 #1

### 输入

```
17
0 3 5 13 13 15 21 26 27 29 37 39 39 45 51 52 53```

### 输出

```
3```

# 题解

## 作者：Stars_Traveller (赞：5)

# 题解：P10489 [IOI1994] The Buses
## 分析
$n$ 最大为 $300$，直接爆搜会超时，而题面中说公交路线小于或等于 $17$，尝试迭代加深搜索。提前处理出必须停靠在公交车站的公交线路，使公交路线的每一辆到达的公交车的到达时间都记录了。写一个 check 函数检查第 $i$ 个公交路线的每一辆到达的公交车的到达时间是否都记录了（是否都在输入中给出）。将公交路线按公交车数量从多到少排序，贪心选择公交路线。最后维护一个数组 $s_i$ 表示第 $i$ 个时间点出现的车的数量。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int cnt, dep, n, s[114514];
struct node
{
	int x, d, num;
}route[114514];
bool cmp(node x, node y)
{
    return x.num>y.num;
}
bool check(int x, int d)
{
	for(int i=x;i<60;i+=d)if(!s[i])return 0;
	return 1;
}
bool dfs(int cur, int k, int sum)
{
	if(cur==dep)
	{
		return sum==n;
	}
	if(sum+(dep-cur)*route[k].num<n)return 0;
	for(int i=k;i<=cnt;i++)
	{
		if(check(route[i].x,route[i].d))
		{
			for(int j=route[i].x;j<60;j+=route[i].d)
			{
				s[j]--;
			}
			if(dfs(cur+1,i,sum+route[i].num))
			{
				return 1;
			}
			for(int j=route[i].x;j<60;j+=route[i].d)
			{
				s[j]++;
			}
		}
	}
	return 0;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		s[x]++;
	}
	for(int i=0;i<60;i++)
	{
		for(int d=i+1;i+d<60;d++)
		{
			if(check(i,d))
			{
				cnt++;
				route[cnt].x=i,route[cnt].d=d,route[cnt].num=(59-i)/d+1;
			}
		}
	}
	sort(route+1,route+1+cnt,cmp);
	dep=0;
	while(!dfs(0,1,0))
	{
		dep++;
	}
	cout<<dep;
}

---

## 作者：Im_Klee (赞：3)

### 前言
帮帮可莉吧！让可莉通过审核吧！
### 题意
给定 $n$ 个数，求最少的等差数列个数，恰好覆盖 $n$ 个数各一次。

至少 $2$ 项，数值在 $0$ 到 $59$ 之间。

允许有重复的等差数列。

$X$ 等差数列必须按规律在 $[0,59]$ 之间出现。

### 分析：

1. 考虑到 `DFS` 超时，而答案在 $17$ 以内，尝试 `IDDFS`。
2. 预处理可能的等差数列，使得等差数列的每一项都在输入中出现。
3. 维护 `check` 函数检查第 $i$ 个等差数列的每一项是否都有出现，设找到 $cnt$ 条。
4. 将等差数列按项数从多到少排序，贪心选取，从而使得需要的公交路线最少。
5. 维护 $cnt_i$ 表示时间点 $i$ 出现的车的数量。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std。
const int maxn = 305。
int cnt, dep, n, s[65]。

struct node
{
	int x, d, num。
	bool operator < (const node &a) const
	{
		return num > a.num。
	}
}route[3600]。

	
bool check(int x, int d)
{
	for(int i = x。 i < 60。 i += d)
		if(s[i] == 0)
			return false。
	return true。
}

bool dfs(int cur, int k, int sum) //cur 层次，k线路， sum已经覆盖的车的数量 
{
	if(cur == dep)
		return sum == n。
	if(sum + (dep-cur) * route[k].num < n) //可行性剪枝 
		return false。
	for(int i = k。 i <= cnt。 i++)
	{
		if(check(route[i].x, route[i].d) == true)
		{
			for(int j = route[i].x。 j < 60。 j += route[i].d)
				s[j]--。
			if(dfs(cur+1, i, sum + route[i].num) == true) //第i条路线还可以选!! 
				return true。
			for(int j = route[i].x。 j < 60。 j += route[i].d) //回溯 
				s[j]++。
		}
	}
	return false。
}

int main()
{
	cin >> n。 //n车 
	for(int i = 1。 i <= n。 i++)
	{
		int x。
		cin >> x。 //时间 
		s[x]++。 //计数器 
	}
	for(int i = 0。 i < 60。 i++) //首项 
	{
		for(int d = i + 1。 i + d < 60。 d++) //公差 
		{
			if(check(i, d) == true) //找到可行的线路 
			{
				cnt++。
				route[cnt].x = i。 //首项 
				route[cnt].d = d。 //公差 
				route[cnt].num = (59-i) / d + 1。 //覆盖的公交车数量 
			}
		}
	}
	sort(route + 1, route + cnt + 1)。 //按照覆盖的公交车数量从大到小排序 
	dep = 0。
	while(dfs(0, 1, 0) == false) //当前的深度，选择线路编号， 覆盖的总公交 
		dep++。
	cout << dep。
	return 0。
}
//注意这组数据 0  4  4  8 8 12 12 …… 

```

---

## 作者：NTT__int128 (赞：2)

# P10489 [IOI1994] The Buses题解
## 题意
给定 $n$ 个数，求最少的等差数列个数，恰好覆盖 $n$ 个数各一次，至少两项，数值为 $[0,59]$，允许有重复的等差数列。等差数列必须两端不可以再拓展。

## 分析：
1. 考虑到 DFS 会超时，而答案在 $17$ 以内，尝试 IDDFS；
2. 预处理可能的等差数列，使得等差数列的每一项都在谁中出现；
3. 维护 check 函数检查第 $i$ 的等差数列的每一项是否都有出现；
4. 将等差数列按箱数从多到少排序，贪心选取，从而使得需要的公交路线最少；
5. 开一个桶维护每种时间的数量；

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e2+5;
struct sequence{
	int s,d,c;
	bool operator<(const sequence&_)const{
		return c>_.c;
	}
}a[100005];
int n,x[N],s[65],cnt,dep;
bool check(int st,int d){
	while(st<60){
		if(!s[st])return 0;
		st+=d;
	}
	return 1;
}
bool dfs(int c,int k,int p){
	if(c==dep)return p==n;
	if(p+a[k].c*(dep-c)<n)return 0;
	for(int i=k;i<=cnt;i++)
		if(check(a[i].s,a[i].d)){
			for(int j=a[i].s;j<60;j+=a[i].d)s[j]--;
			if(dfs(c+1,i,p+a[i].c))return 1;
			for(int j=a[i].s;j<60;j+=a[i].d)s[j]++;
		}
	return 0;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x[i],s[x[i]]++;
	for(int i=0;i<60;i++)
		for(int d=i+1;i+d<60;d++)
			if(check(i,d)){
				cnt++;
				a[cnt].s=i,a[cnt].d=d,a[cnt].c=(59-i)/d+1;
			}
	sort(a+1,a+cnt+1);
	dep=1;
	while(!dfs(0,1,0))dep++;
	cout<<dep;
	return 0;
}
```

---

## 作者：Weekoder (赞：2)

### 思路

这道题不是很好想，如果硬要做的话，就只能暴搜了。可是暴搜显然会超时，该怎么优化呢？

注意到题目中有一个很特别的条件：测试示例中的公交线路数量将 $$\leq 17$$。也就是说，我们如果以公交线路的数量作为搜索树的层数，那么这个问题就变成了一个标准的 IDDFS！

我们可以将每条能覆盖所有范围内时间点的路线存储起来，并根据覆盖时间点的数量降序排序。于是在 DFS 中，我们只需要枚举要选择的线路就可以了，并在 DFS 完毕后回溯。

这里依然可以加入一个可行性剪枝：如果当前已经覆盖的结点数量加上贪心能覆盖的最多结点数量还是不能覆盖全部，就直接返回假，也就是没有找到答案，提高程序的运行效率。可行性剪枝是 IDDFS 中非常常用且实用的一种剪枝方法。

最后，完整代码如下：


```cpp
#include <bits/stdc++.h>

#define debug(x) (cout << #x << " " << x << "\n")

using namespace std;

using ll = long long;

const int N = 1505;

struct node {
	int x, d, num;
} q[N];

int n, s[N], lim, cnt;

bool check(int x, int d) {
	for (int i = x; i < 60; i += d) if (!s[i]) {
		return 0;
	}
	return 1;
}

bool dfs(int cur, int k, int sum) {
    if (cur == lim) return sum == n;
    if (sum + q[k].num * (lim - cur) < n) return 0;
    for (int i = k; i <= cnt; i++) if (check(q[i].x, q[i].d)) {
        for (int j = q[i].x; j < 60; j += q[i].d) s[j] --;
        if (dfs(cur + 1, i, sum + q[i].num)) return 1;
        for (int j = q[i].x; j < 60; j += q[i].d) s[j] ++;
    }
    return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1, x; i <= n; i++) cin >> x, s[x] ++;
	lim = 0;
	for (int i = 0; i < 60; i++) {
		for (int j = i + 1; i + j < 60; j++) if (check(i, j)) {
			cnt ++;
			q[cnt] = {i, j, (59 - i) / j + 1};
		}
	}
	sort(q + 1, q + 1 + cnt, [&](const node &x, const node &y) {
		return x.num > y.num;	
	});
	while (!dfs(0, 1, 0)) lim ++;
    cout << lim;
	return 0;
}
```

---

## 作者：endswitch (赞：2)

## 题意简化

给定 $n$ 个数，求最少的等差序列个数，恰好覆盖 $n$ 个数各一次。

每个等差数列至少 $2$ 项，数值在 $[0,59]$ 之间，允许有重复的等差数列。

等差数列必须为**最简**等差数列。

* **最简**等差数列：满足以当前公差、首项、末项为等差数列时，不会再有另一个等差数列满足其包含该等差数列。

## 分析

显然会有一个 naive 的爆搜，会超时。但题目满足答案（即搜索树的深度）小于等于 $17$，考虑 IDDFS。

预处理可能的等差数列使得等差数列的每一项都在输入中出现。

这个实现是很简单的。首先枚举首项为 $i$，公差为 $j$ 的最简等差数列（即满足 $j > i,i + j \le 59$），再维护 `check` 函数检查等差数列的每一项是否都在给定的 $n$ 个数中出现。显而易见的，维护一个桶 $t_i$ 表示时间点 $i$ 出现的车的数量即可。

此时便可以 IDDFS 了。

但你会发现这样仍然会超时。我们发现有些状态根本不可能走到，但按上述思路写的程序会义无反顾的搜下去。

于是考虑可行性剪枝。按照套路，我们如果按最优策略对当前状态进行预测。若不行，便放弃该状态。

在此题中，我们的最优策略一定是优先选等差数列中项数多的，所使用的等差数列数一定是最小的。

因此想到贪心地将等差数列按照项数从大到小排序，这样可以保证所需要的公交路线数量最小。

我们在搜索中维护 $pos,sum$ 两个变量分别表示当前搜到的等差数列编号和在 $n$ 个数中已经选过的数的数量。

当 $sum + len_{pos} \times (dep - cur) < n$（$len_{pos}$ 为第 $pos$ 个等差数列的项数，$dep$ 为当前规划的搜索的深度，$cur$ 为当前搜索的深度。该式子的含义即为在当前状态以最优策略搜索之后是否能满足条件。由于等差数列可以重复选，$len_{pos}$ 一定是当前状态可选的项数最大的等差数列，所以该策略一定为最优策略）时，将该状态剪枝即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 305;
int n, x, cnt, dep, t[N];
struct Node {
	int s, d, len;
	Node(int ss = 0, int dd = 0, int llen = 0) {
		s = ss, d = dd, len = llen;
	}
} a[N * N];

inline bool check(int s, int d) {
	for(int i = s ; i <= 59 ; i += d)
		if(! t[i]) return false;
	
	return true;
}

inline bool cmp(Node a, Node b) {
	return a.len > b.len;
}

inline bool dfs(int x, int pos, int sum) {
	if(x == dep) return sum == n;
	
	if(sum + a[pos].len * (dep - x) < n) return false;
	
	for(int i = pos ; i <= cnt ; ++ i) {
		if(! check(a[i].s, a[i].d)) continue;
		
		for(int j = a[i].s ; j <= 59 ; j += a[i].d)
			-- t[j];
		
		if(dfs(x + 1, i, sum + a[i].len)) return true;
		
		for(int j = a[i].s ; j <= 59 ; j += a[i].d)
			++ t[j];
	}
	
	return false;
}

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> x;
		
		++ t[x];
	}
	
	for(int i = 0 ; i <= 59 ; ++ i)
		for(int j = i + 1 ; i + j <= 59 ; ++ j)
			if(check(i, j)) {
				int res = 0;
				
				for(int k = i ; k <= 59 ; k += j)
					++ res;
				
				a[++ cnt] = Node(i, j, res);
			}
//			a[++ cnt] = Node(i, j, (59 - i) / j + 1);
	
	sort(a + 1, a + 1 + cnt, cmp);
	
	while(! dfs(0, 1, 0)) ++ dep;
	
	cout << dep;
	
	return 0;
}
```

---

## 作者：liuli688 (赞：1)

思路和其他神犇们不太一样。
### 思路
显而易见第一步先枚举可能的公交线路。设 $i$ 为每条公交的发车时间，$j$ 为间隔时间，则应该对于 $\forall i \in [0,30),\forall j \in [i + 1,60 - i)$ 进行检查路线是否合法的操作。

Q：为什么是 $\forall i \in [0,30)$ 而不是 $\forall i \in [0,60)$？

A：因为题目里说“**每条公交线路至少停靠 $2$ 次**”，对于发车时间大于等于 $30$ 的公交车，其间隔时间必然大于 $30$（不然此次到达之前还会先到一次），所以该路线只会被这条路线上的公交车停靠一次。这个优化可以节省大量时间。

Q：怎么检查路线合不合法？

A：在输入时记录每个时间公交到来的次数，接下来设 $i = \texttt{发车时间}$，若 $stop_i = 0$ 则不合法（$stop_i$ 表示时刻 $i$ 公交到来的次数）,否则 $i \gets i + \texttt{间隔时间}$。

其实本质是模拟：计算车到来的时间，再看看对应的数组中有没有这辆车。

```
bool check(int st, int interval) {//st 发车时间，interval 间隔时间
        for (reg int i = st; i < N; i += interval)//模拟
            if (stop[i] == 0)
                return false;
        return true;
    }
```

------------

算出所有可能的路线后，很多神犇都是直接打 ID-DFS（迭代加深 DFS）：因为并不知道有几条线路，那就从 $1$ 开始试，刚好是 ID-DFS 的板子，何乐而不为？但是如果有毒瘤数据（比如说刚好 $17$ 条路线），容易被卡。所以我反其道而行之，用 DFS 算出所有可能的方案，再打擂台找答案的最小值。

Q：DFS 状态是什么？怎么转移？

A：实际上只要两个状态 $dep$（表示目前线路数）和 $c$（目前枚举到哪条线路）。

进行 DFS 时，对于 $\forall i \in [c,\texttt{方案总数}]$，枚举 $\texttt{线路}_i$，检查合不合法，如合法则将这条线路标记，并进行扩展 $dfs(dep + 1,i)$。记得 DFS 完随手清除标记。

另外我们还可以加一个剪枝：如果目前线路数加上将来最少所需的线路数大于等于已搜到的答案，那么直接回溯即可。

最后加上小优化：按公交车在车站停靠的次数降序排序，可以加速。

```
//bus 是线路，st 同上，interval 同上，cnt 是公交车在车站停靠的次数，stop 同上
#define reg register

void set(int st, int interval) {
    for (reg int i = st; i < N; i += interval) {
        --stop[i];
        --n;
    }
}
void reset(int st, int interval) {
    for (reg int i = st; i < N; i += interval) {
        ++stop[i];
        ++n;
    }
}

void dfs(int dep, int c) {
    if (n <= 0) {//全部公交车到达的时间被分配完，打擂台找答案最小值
        ans = std::min(ans, dep);
        return ;
    }
    for (reg int i = c; i < tot; ++i) {
        if (dep + n / bus[i].cnt >= ans)//剪枝（Q：为什么 dep + n / bus[i].cnt 是将来最少所需的线路数？A：因为已经降序排序了）
            return ;
        if (check(bus[i].st, bus[i].interval)) {//检查合不合法
            set(bus[i].st, bus[i].interval);//标记线路
            dfs(dep + 1, i);
            reset(bus[i].st, bus[i].interval);//取消标记
        }
    }
}
```
### 代码
```
//P10489 [IOI1994] The Buses
#include <bits/stdc++.h>

#define reg register

constexpr int N = 60;
int n, ans = 18, tot = 0;

namespace Route {
    int stop[N];
    class Bus {
    public:
        int st, interval, cnt;
    } bus[1001];
    bool check(int st, int interval) {
        for (reg int i = st; i < N; i += interval)
            if (stop[i] == 0)
                return false;
        return true;
    }
    void set(int st, int interval) {
        for (reg int i = st; i < N; i += interval) {
            --stop[i];
            --n;
        }
    }
    void reset(int st, int interval) {
        for (reg int i = st; i < N; i += interval) {
            ++stop[i];
            ++n;
        }
    }
}

using Route::stop;
using Route::Bus;
using Route::bus;

void dfs(int dep, int c) {
    if (n <= 0) {
        ans = std::min(ans, dep);
        return ;
    }
    for (reg int i = c; i < tot; ++i) {
        if (dep + n / bus[i].cnt >= ans)
            return ;
        if (Route::check(bus[i].st, bus[i].interval)) {
            Route::set(bus[i].st, bus[i].interval);
            dfs(dep + 1, i);
            Route::reset(bus[i].st, bus[i].interval);
        }
    }
}

signed main() {
    scanf("%d", &n);
    for (reg int i = 0, tmp; i < n; ++i) {
        scanf("%d", &tmp);
        ++stop[tmp];
    }
    for (reg int i = 0; i < (N >> 1); ++i)
        for (reg int j = i + 1; j < N - i; ++j)
            if (Route::check(i, j)) {
                Bus tmp;
                tmp.st = i;
                tmp.interval = j;
                tmp.cnt = (N - 1 - i) / j + 1;
                bus[tot++] = tmp;
            }
    std::sort(bus, bus + tot, [](Bus x, Bus y) {
        return x.cnt > y.cnt;
    });
    dfs(0, 0);
    printf("%d", ans);
    return 0;
}
```

---

## 作者：niuzh (赞：1)

### 思路

首先预处理出所有可能的线路。枚举起点 $i$ 和枚举公差 $j$，使 $j \geq i+1，i+j<60$。

然后问题就变成了最少从线路中选出多少条，才可以包含所有公交车。

由于线路很多，但并不知道要取几条，所以可以考虑迭代加深搜索。

但这样还会超时，所以还可以再加上一些剪枝，会剪掉不少情况。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=60+10,M=3600+10;
int n,idx,ans,h[N];
struct node
{
	int x,d,nums;
	bool operator<(const node &t)const
	{
		return nums>t.nums;
	}
}r[M];
bool check(int x,int d)
{
	for (int i=x; i<60; i+=d)
	{
		if (!h[i])
		{
			return false;
		}
	}
	return true;
}
bool dfs(int cnt,int now,int sum)
{
	if (cnt==ans)//剪枝
	{
		return sum==n;
	}
	if (sum+(ans-cnt)*r[now].nums<n)
	{
		return false;
	}
	for (int i=now; i<=idx; i++)
	{
		int x=r[i].x,d=r[i].d,nums=r[i].nums;
		if (check(x,d))
		{
			for (int j=x; j<60; j+=d)
			{
				h[j]--;
			}
			if (dfs(cnt+1,i,sum+nums))
			{
				return true;
			}
			for (int j=x; j<60; j+=d)
			{
				h[j]++;
			}
		}
	}
	return false;
}
int main()
{
	cin>>n;
	for (int i=1,x; i<=n; i++)
	{
		cin>>x;
		h[x]++;
	}
	for (int i=0; i<60; i++)
	{
		for (int j=i+1; i+j<60; j++)
		{
			if (check(i,j))
			{
				r[++idx]=node{i,j,(59-i)/j+1};
			}
		}
	}
	sort(r+1, r+idx+1);
	ans=0;
	while (!dfs(0,1,0))//迭代加深搜索
	{
		ans++;
		if (ans>17)
		{
			cout<<"Unkown Problems!";
			return 0;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：__zyq_666_kpzc__ (赞：0)

### 思路分析
- 深搜必定超时，而答案很小，考虑迭代加深搜索。

- 预处理可能的等差数列，使得等差数列的每一项都在输入中出现。

- 维护一个函数检查第 $i$ 个等差数列的每一项是否都有出现，设找到 $cnt$ 条。

- 将等差数列按项数从多到少排序，再贪心选取，从而使得需要的公交路线最少。

- 维护 $cnt_i$ 表示时间点 $i$ 出现的车数量。

~~代码就不用我多说了吧。~~

---

