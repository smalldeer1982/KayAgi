# Serval and Kaitenzushi Buffet

## 题目描述

Serval 发现了一家回转寿司自助餐厅。回转寿司意味着餐厅内有一条传送带，将寿司盘依次传送到顾客 Serval 面前。

在这家餐厅中，每盘寿司恰好包含 $k$ 块寿司，第 $i$ 盘寿司的美味值为 $d_i$。Serval 将在这家餐厅用餐 $n$ 分钟，且在这 $n$ 分钟内必须吃完他从传送带上拿取的所有寿司块。

设未食用的已拿取寿司块计数器为 $r$。初始时 $r = 0$。在第 $i$ 分钟（$1 \leq i \leq n$），只有第 $i$ 盘寿司会被传送到 Serval 面前，他可以执行以下三种操作之一：
- 从传送带上拿取第 $i$ 盘寿司（其美味值为 $d_i$），此时 $r$ 增加 $k$；
- 食用之前从传送带上拿取的 1 块未食用寿司，此时 $r$ 减少 $1$（注意仅当 $r > 0$ 时可执行此操作）；
- 或不做任何操作，此时 $r$ 保持不变。

注意在 $n$ 分钟结束后，$r$ 的值必须为 $0$。

Serval 希望最大化他拿取的所有寿司盘的美味值之和。请帮助他计算这个最大值！

## 说明/提示

第一个测试案例中，可以证明 Serval 最多能吃完一盘寿司。由于第二盘寿司的美味值 $6$ 是所有盘中最大的，他会在第二分钟拿取该盘，并在接下来的 $2$ 分钟内吃完它。

| 分钟 | 1 | 2 | 3 | 4 | 5 |
|------|---|---|---|---|---|
| 操作 | — | 拿取 | 食用 | 食用 | — |
| 操作后 $r$ | 0 | 2 | 1 | 0 | 0 |
| 累计美味值 | 0 | 6 | 6 | 6 | 6 |

第二个测试案例中，可以证明最优策略是拿取第一、第三和第六盘寿司。这些盘的美味值之和为 $3 + 4 + 9 = 16$。

| 分钟 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|------|---|---|---|---|---|---|---|
| 操作 | 拿取 | 食用 | 拿取 | 食用 | — | 拿取 | 食用 |
| 操作后 $r$ | 1 | 0 | 1 | 0 | 0 | 1 | 0 |
| 累计美味值 | 3 | 3 | 7 | 7 | 7 | 16 | 16 |

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
5 2
3 6 4 1 2
7 1
3 1 4 1 5 9 2
4 3
4 3 2 1
6 2
1 3 5 2 4 6
6 1
1000000000 1 1000000000 1 1000000000 1```

### 输出

```
6
16
4
6
3000000000```

# 题解

## 作者：ZMQ_Ink6556 (赞：6)

## 题解：CF2085D Serval and Kaitenzushi Buffet

### 题意简述

Serval 刚刚找到了一家 Kaitenzushi 自助餐厅。
Kaitenzushi 的意思是餐厅里有一条传送带，将寿司盘送到顾客 Serval 面前。

在这家餐厅，每个盘子里正好有 $k$ 块寿司，第 $i$ 个盘子有一个美味值 $d_i$。

Serval 将在这家餐厅吃 $n$ 分钟，在 $n$ 分钟内，他必须吃完他从腰带上拿来的所有寿司。

将未吃掉的寿司片的数量表示为 $r$。
最初，$r = 0$。在第 $i$ 分钟 $(1 \le i \le n)$，只有第 $i$ 盘寿司会送到 Serval 面前。

他可以执行以下操作之一：

- 从传送带上拿出第 $i$ 盘寿司（其美味是 $d_i$），$r$ 将增加 $k$。
- 吃掉他之前从腰带上拿走的一块未吃的寿司，$r$ 将减少 $1$。请注意，只有在 $r > 0$ 时才能这么做。
- 或者，什么都不做，$r$ 将保持不变。

请注意，在 $n$ 分钟后，$r$ 的值必须为 $0$。

Serval 想把他吃的所有盘子的美味总和最大化。帮他找出来！

### 解题思路

容易发现在 $n - k$、$n - 2k$、$n - 3k \cdots$ 时获取寿司是一种合法的方案（不一定最优）。

考虑**贪心**，将一个合法寿司换成一个更早的寿司也一定合法，但换成更晚的不一定合法。

可以观察到，在 $n - k$、$n - 2k$、$n - 3k \cdots$ 时获取寿司是一种边界方案，也就是说，若**将这些寿司标记为合法，那么将一个合法寿司换成一个更早的寿司也一定合法，但换成更晚的一定不合法**。

此时从左到右贪心，每遇到标记点从前面取出一个美味度最大的寿司即可通过。

单次取最大值操作可以通过优先队列 $O(\log n)$ 实现。

复杂度：$O((n + k) \log n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int t;
long long k , n , d[200005] , dp[200005] , ans;
bool vis[200005];
priority_queue<long long> q;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		for(int i = 1 ; i <= n * 2 ; i++)
		{
			dp[i] = -1000000000000000018ll;
		}
		dp[n + 1] = 0;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> d[i];
			vis[i] = 0;
		}
		for(int i = n ; i >= 1 ; i--)
		{
			if(dp[i + k + 1] == 0)
			{
				dp[i] = 0;
				vis[i] = 1;
			}
		}
		ans = 0;
		while(q.size())
		{
			q.pop();
		}
		for(int i = 1 ; i <= n ; i++)
		{
			q.push(d[i]);
			if(vis[i])
			{
				ans += q.top();
				q.pop();
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：zhaohongdi114514 (赞：2)

## 贪心

看到最优性，不是贪心就是 DP，但 DP 显然需要二维状态，故不可行，于是考虑贪心。

正着贪也不好做，考虑倒过来做，于是题目变成：

有一计数器 $r$，每到一个点可以消耗 $k$ 将答案加上这个点的值，否则计数器加一。

那么这就很显然的可以用反悔贪心来做，使用一个小根堆记录当前所有被取的值，每当当前点可取就直接取，否则判断堆顶的值是否比当前值更劣，取二者中较优值。

Code:
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,k;
int a[N];
priority_queue<int,vector<int>,greater<int>> h;
signed main(){
	int T;
	for (cin>>T;T--;){
		cin>>n>>k;
		for (int i=1;i<=n;i++)
			cin>>a[i];
		int cnt=0;
		for (int i=n;i>=1;i--){
			if (cnt>=k){
				cnt-=k;
				h.push(a[i]);	
			}
			else{
				if (h.size() && a[i]>h.top()){
					h.pop();
					h.push(a[i]);
				}
				cnt++;
			}
		}
		int ans=0;
		while (h.size()){
			ans+=h.top();
			h.pop();
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：zac2010 (赞：1)

### Part1：思路
这题虽然简单，但是反应的思维方式比较有意义。

首先，去刻画什么情况下一盘寿司能被选择——显然是后面至少有 $k$ 分钟空着没事做。

这里的关键在于**后面**，但是后面的情况如何正着做是不知道的。换句话说，前面数的选择与否只与后面的情况有关，所以我们从后往前考虑。

遇到这种选择物品题，我们往往第一反应都会是贪心。从后往前扫的时候，假若现在是第 $n-k$ 分钟，那么后面恰好有 $k$ 分钟空余，我们将选择当前这盘寿司。

但是这里显然不满足最优子结构。考虑刻画非最优的情况。具体的，对于第 $1\sim n-k-1$ 中任意一盘没选中的寿司，假若选择它会带来更大美味值，那么我们都可以使用后面的寿司替换第 $n-k$ 盘。

更加广泛的，对于任意 $j<i$，我们都可以使用第 $j$ 盘寿司替换第 $i$ 盘。这时候就得到了一个反悔贪心，对于其正确性此时再稍作归纳便可得知。

### Part2：代码

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for (int i = (a); i <= (b); ++i)
#define FR(i, a, b) for (int i = (a); i >= (b); --i)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define Sz(v) ((int)(v).size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int N = 2e5 + 10;
int n, k, d[N];
multiset<int> s1;
void Solve() {
    scanf("%d %d", &n, &k);
    FL(i, 1, n) {
        scanf("%d", &d[i]);
    }
    s1.clear();
    ll ans = 0;
    FR(i, n, 1) {
        int lim = (n - i + 1) / (k + 1);
        if (Sz(s1) < lim) {
            ans += d[i];
            s1.emplace(d[i]);
        } else {
            if (!s1.empty() && *s1.begin() < d[i]) {
                ans -= *s1.begin();
                s1.erase(s1.begin());
                ans += d[i];
                s1.emplace(d[i]);
            }
        }
    }
    printf("%lld\n", ans);
}
int main() {
    int T = 1;
    scanf("%d", &T);
    for (; T--; Solve());
    return 0;
}
```

---

## 作者：GY程袁浩 (赞：0)

首先是这样的，我们如果对于一个问题最多能取 $m$ 盘寿司，那么最优方案也一定取了 $m$ 盘寿司。

我们反证法，如果最优方案取了少于 $m$ 盘寿司，我们找到最左边没有选的寿司，选上一定合法，并且一定会使答案增加，矛盾。

然后我们再来看看这 $m$ 盘寿司如何选，$m$ 具体是多少。

从右往左看，能放就放绝对最优，因此 $m=\lfloor \frac{n}{k+1}\rfloor$。

我们不合法当且仅当右边的空不够，这就意味着如果我们在一个合法方案中将一个所吃的寿司位置向左移动整个方案仍然合法。

而我们所有寿司都最左边的方案就是从右往左每隔 $k$ 个空选一个。

然后有我们刚刚的合法结论，所以对于从右往左每 $k$ 个，它左边的寿司，如果没有选过，都可以选。

现在就变成了，我有 $S_{1},\dots,S_{m}$ 个可重集合并且有 $S_{i} \in S_{i+1}(1\le i<m)$。希望你从每个集合中选出一个数使得总和最大。因为有 $S_{i} \in S_{i+1}(1\le i<m)$，所以我们优先从 $S_{1}$ 开始选最大值，如果前面已经选过就选次大值，还选过就选次次大值，以此类推。考虑如果我们改变优先级，那么由于范围更小的集合用作次大值，使得答案不会更优。

```cpp
// Problem: D. Serval and Kaitenzushi Buffet
// Contest: Codeforces - Codeforces Round 1011 (Div. 2)
// URL: https://codeforces.com/contest/2085/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define upp(a, x, y) for (int a = x; a <= y; a++)
#define dww(a, x, y) for (int a = x; a >= y; a--)
#define pb(x) push_back(x)
#define endl '\n'
#define x first
#define y second
#define PII pair<int, int>
using namespace std;
int qmi(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
const int N = 1e6 + 10;
int a[N];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n, k;
        cin >> n >> k;
        priority_queue<int> qq;
        int ans = 0;
        upp(i, 1, n) {
            int x;
            cin >> x;
            qq.push(x);
            if ((n - i + 1) % (k + 1) == 0) {
                ans += qq.top();
                qq.pop();
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：MrPython (赞：0)

把问题**倒过来做**，就变成了：

初始时有 $0$ 点 hp，每轮会恢复一点 hp。同时每轮使用一次技能，消耗 $k+1$ 点 hp 来获得当前轮所对应的快乐值。你最多可以获得多少快乐值？

然后就是经典反悔贪心板子。每轮尝试使用技能，若 hp 不够就撤销掉所有用过的技能快乐值最少的那次。

```cpp
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <ranges>
#include <utility>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    ui k;
    size_t n;
    fin >> n >> k;
    vector<ui> d(n);
    for (ui& i : d) fin >> i;
    priority_queue<ui, vector<ui>, greater<>> q;
    int hp = 0;
    uli sum = 0;
    for (auto i : d | ranges::views::reverse) {
      hp += 1;
      q.emplace(i);
      sum += i;
      hp -= k + 1;
      while (hp < 0) {
        sum -= q.top();
        q.pop();
        hp += k + 1;
      }
    }
    fout << sum << '\n';
  }
  return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[CF2085D](https://www.luogu.com.cn/problem/CF2085D)

## Solution

考虑能拿多少盘寿司、什么时候能拿第 $i$ 盘寿司。

贪心的想，我们每次一定是吃掉还没吃掉的且美味值最高的那盘寿司。

因为每次拿一盘寿司会有 $k$ 的罚时，所以吃掉的第 $i$ 盘寿司必须在 $n - i \times (k + 1) + 1$ 之前吃掉。

这样每次能吃寿司的时刻我们吃掉当前拿到的没吃掉的美味值最大的那盘寿司，也就是说需要一个单调的数据结构来维护，选择用大根堆或者 set 维护，复杂度就是 $O(n\log n)$。

## Code

[Submission](https://codeforces.com/contest/2085/submission/312134375)

---

