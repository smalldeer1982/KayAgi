# Project Manager

## 题目描述

B公司有 $ n $ 名员工，编号从 $ 1 $ 到 $ n $ 。每个员工每周都有工作日和休息日。给定每个员工的工作日列表。工作日分为正常工作日和假日。在正常工作日，只有那些在当天工作日列表中的员工才工作。

在假日中，没有人工作。给定一组假日列表。第一天从星期一开始，编号为 1 。公司收到了 $ k $ 个项目的投标，需要完成这些项目。这些项目按照优先级从高到低编号为从 1 到 $ k $ 。每个项目由多个部分组成，第 $ i $ 部分必须由第 $ a_i $ 名员工完成。各个部分必须按顺序完成（即只有在第 $ i $ 部分完成后，才能开始完成第 $ i+1 $ 部分）。每个部分需要相应的员工花费一天的时间来完成。项目可以同时进行。

然而，每个员工在一天内只能完成一个项目的一部分。如果他们有多个项目可以选择完成一部分，他们总是优先选择优先级最高（索引最小）的项目。对于每个项目，输出该项目完成的天数。

## 样例 #1

### 输入

```
3 5 4
2 Saturday Sunday
2 Tuesday Thursday
4 Monday Wednesday Friday Saturday
4 7 13 14 15
5 1 1 3 3 2
3 2 3 2
5 3 3 3 1 1
8 3 3 3 3 3 3 3 3```

### 输出

```
25 9 27 27```

# 题解

## 作者：CaoXian (赞：2)

先来考虑这样一件事：对于第一个项目，某个人完成了他目前应该完成的部分，那么下一个人只要一有空就会去接手这个项目。

这一点是因为题目限定了**同一个人如果在一个时刻有多种选择**的话，他会选择**优先级最高**的项目去做。

明白了这一点的话整道题大概的思路就出来了。下面记得区分一下**项目**与**部分**。

现在我们不仅仅局限于第一个项目，我们可以把它依次拓展到第 $i$ 个项目的情况。

具体地，我们从第一个项目开始，每完成一个部分的时候都记录一下当前日期，一个项目的所有部分都解决了过后当前时间即为答案。开一个新的项目的时候当前时间设为 $0$。

我们依次遍历这个项目的所有部分，每次都检查这个部分的负责人，找到他**晚于当前时间的最早空闲时间**（这里的**空闲时间**是指，那一天他会参加工作，但是目前还没有被安排工作），那么这个负责人将会在这个时间去接手这一部分，并且将这个人的这段**空闲时间**设为**已占用状态**（意思是说他这段时间不能再安排别的任务了），同时要更新一下当前时间。

为什么这样做是对的？首先**晚于当前时间**这一点是显而易见的，如果不是选择**晚于当前时间的最早空闲时间**而是安排到了后面，那么这段空闲时间无论是没安排工作的或是安排给了后面的项目，肯定都不符合要求。因为我们是从第一个项目开始的，也就是说优先级是从大到小的。

现在的难点转化到了快速求出**晚于当前时间的最早空闲时间**。

不难发现人与人之间没有关系，所以对于每一个人单独考虑。

如果不考虑假期的情况，那么我们可以把这个人的一周七天时间压缩到**只有工作日的时间**（就是没有休息日的情况）。

然后可以对这个工人**自己的时间**和**正常时间**建立一个映射关系，要找到**晚于当前时间的最早空闲时间**就只需要：先找到**当前时间**对应到了这个人**自己的时间**的哪一天，然后往后推一天，在回到**正常时间**就好了。

并且因为这个东西具有周期性，所以求起来挺方便的。

接着加入假期的限制，如果某一天假期不在一个人的工作日里那么肯定不用考虑。虽然剩下的假期和“已经安排了工作的工作日”本质上相同，但是它们不是一个量级的（前者对于每一个人都是 $m$，后者是所有人的总和为 $k$），不能用同样的方法处理。

先讨论“已经安排了工作”的情况。

如果某个工作日是不空闲的（不能被安排工作的），但是我们却找到了这个工作日。我们显然是希望找到在这个工作日后面的空闲工作日的，所以我们希望**在找到一个非空闲工作日的时候可以跳过这一天**。

这个操作很像并查集，但是空间肯定开不下。仔细思考一下会发现我们有很多未被更改过的结点，这些结点都是没用的，如何过滤掉？或者说，在没有更改这个结点的父亲的时候，不用申请这个结点的空间。很明显可以用 `map` 或者 `unordered_map` 代替数组。

所以某个人在某天被安排了工作过后，把他那一天的父亲指向下一天就好了。

接着是假期，我们可以不用把它当作“不能被安排工作的工作日”，而是把它看成“休息日”。具体地，我们在建立某个工人自己的时间和正常时间的映射关系时，将这些假期排除在外就好。

题目限制了“所有部分的总数量不超过 $2 \times 10^{5}$”，两只 $\log$ 都可以过，所以哪里不方便直接计算的话直接换成二分就行，具体可以看代码实现，复杂度是 $\mathcal{O}(k \log m \log V)$ 的，在“找到**当前时间**对应到了这个人**自己的时间**的哪一天”的部分用了一个二分，在“回到**正常时间**”的部分又套了一个二分。（因为检查的时候调用了前面的函数。）

代码还是挺短的：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, k, p, a, now, h[200005];
vector<int> md[8];
string str;
unordered_map<string, int> mp;
struct worker {
	int t, day[7];
	unordered_map<int, int> father;
	int findset(int x) {
		if(!father.count(x)) return x;
		return father[x] = findset(father[x]);
	}
	void init() {//读入
		cin >> t;
		for(int i = 0; i < t; ++i) {
			cin >> str;
			day[i] = mp[str];
		}
	}
	int idx(int d) {//找到当前时间对应到了这个人自己的时间的哪一天
		if(d < day[0]) return 0;
		int ret = ((d + 6) / 7 - 1) * t, w = ((d + 6) / 7 - 1) * 7, pos = -1;
		for(int i = 0; i < t; ++i) {
			if(day[i] <= (d % 7 ? d % 7 : 7)) ++ret, pos = i;
		}
		if(~pos) w += day[pos];
		for(int i = 0; i < t; ++i) {
			ret -= upper_bound(md[day[i]].begin(), md[day[i]].end(), w) - md[day[i]].begin();//排除假期，原本就是休息日的就不要再排除了
		}
		return ret;
	}
	int get(int d) {
		int l = 1, r = 1000000000, mid, ret = 1;
		while(l <= r) mid = (l + r) >> 1, (idx(mid) >= d) ? (ret = mid, r = mid - 1) : (l = mid + 1);//这里直接计算很麻烦，直接无脑二分
		return ret;
	}
	int find(int bg) {
		int c = findset(idx(bg) + 1);
		father[c] = c + 1;//这一天被安排了工作，更改父亲结点
		return get(c);
	}
} w[200005];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	mp["Monday"] = 1;
	mp["Tuesday"] = 2;
	mp["Wednesday"] = 3;
	mp["Thursday"] = 4;
	mp["Friday"] = 5;
	mp["Saturday"] = 6;
	mp["Sunday"] = 7;
	cin >> n >> m >> k;
	for(int i = 1; i <= n; ++i) w[i].init();
	for(int i = 1; i <= m; ++i) {
		cin >> h[i];
		md[h[i] % 7 ? h[i] % 7 : 7].push_back(h[i]);
	}
	while(k--) {
		cin >> p;
		now = 0;
		while(p--) {
			cin >> a;
			now = w[a].find(now);
		}
		cout << now << " ";
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

设 $N = \sum p$。

考虑到每个没有节假日的周必然存在至少一个项目被完成，所以答案不超过 $M = 7(N + m)$。对于 $h_i > M$ 的节假日，一律无用。

因为一个人会选择编号较小的项目推进，所以按编号从小到大依次模拟每个项目的进度。设当前处理到项目的第 $i$ 部分，在第 $cur$ 天处理了第 $i - 1$ 部分。求出第 $a_i$ 个人在第 $cur + 1$ 天起，第一个工作且没有处理编号更小的项目的日期。

星期一到星期日相互独立，因此考虑对一星期的七天，如果 $a_i$ 在这天工作，分别求后继，再取最小值。这样，在第 $h_i$ 天的假期相当于从 $h_i$ 跳到了 $h_i + 7$。类似的，一个被占用处理编号更小的项目的日期 $p$ 相当于从 $p$ 跳到了 $p + 7$。对于前者，直接预处理出 $suc_i$ 表示从 $i$ 开始的对应类型的第一天工作日。对于后者，用 `map` 维护并查集即可。注意这里并查集是一条链，所以执行 `find` 的总次数为总点数的线性，而每新增一个点，都意味着找到一个工作且未被占用的后继，所以总点数为 $\mathcal{O}(N)$ 级别。

时间复杂度 $\mathcal{O}(m + N\log N)$。不压行且两空格缩进的代码竟然获得了 CF 最短解（2022.12.16）？跑得也非常快，前提是开了 `ios::sync_with_stdio(0)`。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
constexpr int M = 3e6 + 5;
const string week[8] = {
  "",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  "Sunday"
};

int n, m, k, w[N][8], suc[M];
map<int, int> mp[N];
int f(int id, int z) {
  z = suc[z];
  auto it = mp[id].find(z);
  if(it == mp[id].end() || it->second == z) return z;
  return it->second = f(id, it->second);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> m >> k;
  for(int i = 1; i < M; i++) suc[i] = i;
  for(int i = 1; i <= n; i++) {
    int cnt;
    cin >> cnt;
    string day;
    while(cnt--) {
      cin >> day;
      for(int j = 1; j <= 7; j++) {
        if(day == week[j]) w[i][j] = 1;
      }
    }
  }
  for(int i = 1; i <= m; i++) {
    int h;
    cin >> h;
    if(h < M) suc[h] = h + 7;
  }
  for(int i = M - 8; i; i--) suc[i] = suc[suc[i]];

  for(int _ = 1; _ <= k; _++) {
    int p, a, cur = 0;
    cin >> p;
    while(p--) {
      cin >> a;
      int nxt = M;
      for(int i = 1; i <= 7; i++) {
        if(w[a][(cur + i - 1) % 7 + 1]) nxt = min(nxt, f(a, cur + i));
        if(nxt == cur + i) break;
      }
      mp[a][nxt] = nxt + 7, cur = nxt;
    }
    cout << cur << " ";
  }
  cout << "\n";
  return 0;
}
/*
g++ L.cpp -o L -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：do_while_true (赞：2)

写了两个小时写吐了，你告诉我这玩意 2400？

如果不管假期的话，那么每一周必然会有一个项目跟进一次进度。那么答案就是线性的。即使有假期的存在也没关系，每个假期顶多就只会拖延一周的时间。

所以只需要暴力模拟每一天有哪些人工作了，完成了哪些项目的一个进度就可以了。

我的方法是对每个星期几维护一个 set，表示在这一天可能会工作的人，然后对每个人再开一个堆，存储这个人任务计划中的项目。

一个人可能在好几个星期几中工作，但是对于一个项目他只会工作一次，所以要搞个类似懒惰删除的东西，在一个人的任务计划里面找项目的时候需要判一下这个项目目前需不需要这个人来做。

然后就代码写得比较长......好像有更简单的写法。

[Code](https://codeforces.com/contest/1765/submission/182911321) . 

---

## 作者：wenqizhi1125 (赞：1)

提供一种不使用并查集的做法。

考虑朴素的模拟过程：枚举天数，记录各个项目当前需要的工人，枚举工人寻找他做的项目或者枚举项目找做它的工人，复杂度瓶颈在于这个匹配过程中多次失配。

如果枚举工人时，他今天一定工作该多好。

记录各个项目当前需要的工人，若第 $x$ 个项目需要第 $i$ 个工人，将 $x$ 插入小根堆 $work_i$。

维护 $7$ 个 `set` 表示在当前各个项目的进度下，如果今天是星期一二三四五六七时，今天一定要工作的工人集合。

只要 $work_i$ 不为空，第 $i$ 个工人会在一周中他的工作日的 `set` 中出现。

所需要的修改只有删除/加入某个项目修改 $work_i$；根据 $work_i$ 是否为空判断要不要在 $set$ 中删去/加入 $i$。

复杂度为单 $\log$ 但是 $7$ 倍常数。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

ll read()
{
    ll x = 0; bool f = false; char c = getchar();
    while(c < '0' || c > '9') f |= (c == '-'), c = getchar();
    while(c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c & 15), c = getchar();
    return f ? -x : x;
}

const int N = 2e5 + 5;
int n, m, K;
int vis[8][N];
int h[N];
queue<int> q[N];
int ddl[N];

priority_queue< int, vector<int>, greater<int> > work[N]; // 每个人要做的项目
set<int> s[8]; // 某天需要出勤的人

void solve()
{
    n = read(), m = read(), K = read();
    for(int i = 1; i <= n; ++i)
    {
        int t = read();
        while(t--)
        {
            string s;
            cin >> s;
            if(s == "Monday") vis[1][i] = 1;
            else if(s == "Tuesday") vis[2][i] = 1;
            else if(s == "Wednesday") vis[3][i] = 1;
            else if(s == "Thursday") vis[4][i] = 1;
            else if(s == "Friday") vis[5][i] = 1;
            else if(s == "Saturday") vis[6][i] = 1;
            else if(s == "Sunday") vis[7][i] = 1;
        }
    }
    for(int i = 1; i <= m; ++i) h[i] = read();
    for(int i = 1; i <= K; ++i)
    {
        int p = read();
        while(p--)
        {
            int x = read();
            q[i].emplace(x);
        }
        int x = q[i].front();
        work[x].emplace(i);
        for(int j = 1; j <= 7; ++j) if(vis[j][x]) s[j].insert(x);
    }
    int cnt = 0;
    for(int i = 1; cnt < K; ++i)
    {
        if(h[lower_bound(h + 1, h + m + 1, i) - h] == i) continue;
        int t = (i - 1) % 7 + 1;
        vector<int> t1, t2;
        for(auto x : s[t]) t1.emplace_back(x);
        for(auto x : t1)
        {
            assert(!work[x].empty());
            int y = work[x].top();
            work[x].pop();
            q[y].pop();
            if(!q[y].empty()) t2.emplace_back(y);
            else ddl[y] = i, ++cnt;
            if(work[x].empty()) for(int j = 1; j <= 7; ++j) if(vis[j][x]) s[j].erase(x);
        }
        for(auto y : t2)
        {
            int x = q[y].front();
            for(int j = 1; j <= 7; ++j) if(vis[j][x]) s[j].insert(x);
            work[x].emplace(y);
        }
    }
    for(int i = 1; i <= K; ++i) printf("%d ", ddl[i]);
}

int main()
{
    int T = 1;
    while(T--) solve();
    return 0;
}
```

---

