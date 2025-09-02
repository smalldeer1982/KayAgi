# [ABC331E] Set Meal

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc331/tasks/abc331_e

AtCoder 食堂では主菜と副菜からなる定食が販売されています。  
 主菜は $ N $ 種類あり、順に主菜 $ 1 $, 主菜 $ 2 $, $ \dots $, 主菜 $ N $ と呼びます。主菜 $ i $ の価格は $ a_i $ 円です。  
 副菜は $ M $ 種類あり、順に副菜 $ 1 $, 副菜 $ 2 $, $ \dots $, 副菜 $ M $ と呼びます。副菜 $ i $ の価格は $ b_i $ 円です。

定食は主菜と副菜を $ 1 $ 種類ずつ選んで構成されます。定食の価格は選んだ主菜の価格と副菜の価格の和です。   
 ただし、$ L $ 個の相異なる組 $ (c_1,\ d_1),\ \dots,\ (c_L,\ d_L) $ について、主菜 $ c_i $ と副菜 $ d_i $ からなる定食は食べ合わせが悪いため提供されていません。  
 つまり、提供されている定食は $ NM\ -\ L $ 種類あることになります。(提供されている定食が少なくとも $ 1 $ 種類存在することが制約によって保証されています。)

提供されている定食のうち、最も価格の高い定食の価格を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 10^5 $
- $ 0\ \leq\ L\ \leq\ \min(10^5,\ N\ M\ -\ 1) $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ 10^9 $
- $ 1\ \leq\ c_i\ \leq\ N $
- $ 1\ \leq\ d_j\ \leq\ M $
- $ i\ \neq\ j $ ならば $ (c_i,\ d_i)\ \neq\ (c_j,\ d_j) $
- 入力される値は全て整数
 
### Sample Explanation 1

提供されている定食、及びその価格は次の $ 3 $ 種類です。 - 主菜 $ 1 $ と副菜 $ 1 $ からなる定食。価格は $ 2\ +\ 10\ =\ 12 $ 円である。 - 主菜 $ 1 $ と副菜 $ 3 $ からなる定食。価格は $ 2\ +\ 20\ =\ 22 $ 円である。 - 主菜 $ 2 $ と副菜 $ 2 $ からなる定食。価格は $ 1\ +\ 30\ =\ 31 $ 円である。 この中で最も高い定食は $ 3 $ 番目の定食です。よって $ 31 $ を出力してください。

## 样例 #1

### 输入

```
2 3 3
2 1
10 30 20
1 2
2 1
2 3```

### 输出

```
31```

## 样例 #2

### 输入

```
2 1 0
1000000000 1
1000000000```

### 输出

```
2000000000```

## 样例 #3

### 输入

```
10 10 10
47718 21994 74148 76721 98917 73766 29598 59035 69293 29127
7017 46004 16086 62644 74928 57404 32168 45794 19493 71590
1 3
2 6
4 5
5 4
5 5
5 6
5 7
5 8
5 10
7 3```

### 输出

```
149076```

# 题解

## 作者：xu222ux (赞：4)

# [Set Meal](https://atcoder.jp/contests/abc331/tasks/abc331_e)

## 思路

~~本题很简单。~~

首先主菜和副菜的价格要从大到小排序。

然后枚举所有主菜的价格，对于每个主菜，枚举副菜，找第一个可以搭配的组合，然后打擂台。

不明白就看这段代码。
```cpp
//数组a是主菜，b是副菜
int tmp=0;//注意初始化
for(int i=1;i<=n;i++){//枚举主菜
	for(int j=1;j<=m;j++){副菜
		if(!mp[{a[i].id,b[j].id}]){//判断是否可以搭配
			tmp=max(tmp,a[i].x+b[j].x);//打擂台不多说了
			break;//注意要break,不然超时
		}
	}
}
cout<<tmp;//输出结果
```

最后计算时间复杂度：$O(n+l)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct node{
	int id,x;
}a[100005],b[100005];
map<pair<int,int>,bool>mp;
bool cmp(node b1,node b2){return b1.x>b2.x;}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)cin>>a[i].x,a[i].id=i;
	for(int i=1;i<=m;i++)cin>>b[i].x,b[i].id=i;
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+m,cmp);
	for(int i=1;i<=k;i++){
		int x,y;cin>>x>>y;
		mp[{x,y}]=true;
	}
	int tmp=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!mp[{a[i].id,b[j].id}]){
				tmp=max(tmp,a[i].x+b[j].x);
				break;
			}
		}
	}
	cout<<tmp;
	return 0;
}
```

---

## 作者：wmrqwq (赞：3)

# 题目链接：

[[ABC331E] Set Meal](https://www.luogu.com.cn/problem/AT_abc331_e)

# 题意简述：

有长度分别为 $n,m$ 的两个序列 $a,b$，你需要选择 $a$ 序列中的一个数和 $b$ 序列中的一个数使得这两个数的比其余的两个数的组合都大，但是有 $q$ 组约束给出 $u,v$ 表示你不能同时选择 $a_u$ 和 $b_v$ 这两个数。

# 解题思路：

我们可以考虑对于每个 $b_i$ 选择哪个 $a_i$ 时值最大，那么我们可以将 $a$ 序列从小到大排序，那么开始时显然所有 $b_i$ 选择的数字均为 $a_n$，然后对于每次约束我们直接开个 `map` 维护一下即可。

# 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,l[100010],wz[100010],u,v,ans;
struct node{
	long long x,id,maxn;
	map<int,int>mp;
}a[100010],b[100010];
bool cmp(node x,node y){
	return x.x<y.x;
}
#define lowbit(x) x&-x
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i].x,a[i].id=i;
	for(int i=1;i<=m;i++)	
		cin>>b[i].x,b[i].id=i,b[i].maxn=n;
	sort(a+1,a+1+n,cmp);
//	sort(b+1,b+1+m,cmp);
	for(int j=1;j<=n;j++)
	//	if(a[j].id==u)
			wz[a[j].id]=j;
	for(int i=1;i<=k;i++)
	{
		cin>>u>>v;
	//	long long wz;
		/*for(int j=1;j<=n;j++)
			if(a[j].id==u)
				wz=j;*/
		b[v].mp[wz[u]]=1;
		while(b[v].mp[b[v].maxn])
			b[v].maxn--;
	}
	for(int i=1;i<=m;i++)
	{
		ans=max(ans,b[i].x+a[b[i].maxn].x);
//		cout<<b[i].maxn<<endl;
	}
	cout<<ans;
	QwQ;
}
```

---

## 作者：haokee (赞：1)

## 题目大意

有 $N$ 个主菜，第 $i$ 个主菜需要 $a_i$ 元；$M$ 个配菜，第 $i$ 个配菜 $b_i$ 元。但是有 $L$ 对主菜和配菜是不能配在一起的。一对菜的价值定义为主菜加上配菜价钱的和。问你最贵的一对菜需要多少元。

## 思路

我们先考虑一个暴力算法：首先枚举 $N$ 个主菜，然后枚举 $M$ 个配菜，最后遍历 $L$ 个配对，判断一下是否可以购买，然后记录最大值。这种算法的时间复杂度是 $\mathcal O(NML)$ 的，而 $1\le N,M,L\le 10^5$，使用这种算法会直接吃席。

我们可以来尝试优化一下，既然要求的是最大值，那么一个主菜必须配对可以买的的最大价值的配菜。那么我们可以直接对 $b$ 数组排序，然后从后往前遍历一遍，在来判断是否可以购买，如果可以就记录最大值，然后 break。这种做法虽然是三重循环，但是时间复杂度是 $\mathcal O(L^2)$ 的，因为第一二层循环只会枚举 $L$ 次，枚举完就必定可以找到可以配对的。

现在我们要加快判断是否能够购买的速度。可以使用一个集合，然后第三重循环就可以直接省掉——变成一个判断是否在集合内出现过的问题。这种算法的时间复杂度是 $\mathcal O(L\log_2\min(M,L))$ 的，因为一个集合内的元素最多有 $L$ 个，但是其实同样不能超过 $M$ 个，因此这题就过掉了。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int n, m, l, ans;

int main() {
  cin >> n >> m >> l;
  vector<int> a(n + 1);                  // 主菜
  vector<pair<int, int>> b(m + 1);       // 配菜
  vector<set<int>> s(n + 1, set<int>()); // 不能配对的菜
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i].first, b[i].second = i;  // 输入并打上编号
  }
  sort(b.begin(), b.end(), [](const auto &a, const auto &b) {  // 排序
    return a.first < b.first;                                  // 按价格排序
  });
  for (int i = 1, x, y; i <= l; i++) {
    cin >> x >> y;
    s[x].insert(y);  // 买了主菜 x 不能买 y
  }
  for (int i = 1; i <= n; i++) {             // 枚举主菜
    for (int j = m; j >= 1; j--) {           // 枚举配菜
      if (!s[i].count(b[j].second)) {        // 如果可以购买
        ans = max(ans, a[i] + b[j].first);   // 记录最大值
        break;                               // 灵魂剪枝
      }
    }
  }
  cout << ans << '\n';  // 输出最优答案
  return 0;
}
```

---

## 作者：heyx0201 (赞：1)

# ABC331E Set Meal 题解
## Description
> 给定 $N$ 个主菜和 $M$ 个配菜，有 $L$ 个套餐不能配在一起，求套餐最大价格。

## Solution
这题有一个奇怪的做法：利用题目的特点做。

具体怎么做呢？就是用 `map` 标记不能匹配的菜，对 $b$ 数组从大到小排序（注意 $b$ 数组要记录编号），然后枚举每个 $1 \le i \le N$，也就是枚举 $a$ 数组，再枚举每个 $1 \le j \le M$，也就是枚举 $b$ 数组，如果找到第一个没有被标记过的 $j$，那么退出，更新答案。

为什么能过呢？因为这个算法均摊时间复杂度为 $O(N+L)$！

大概结构：

- 枚举 $i$：
  - 枚举 $j$：
    - 如果没有被标记过，退出；
    - 否则，继续。
  - 更新答案。

## Accept Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, m, l;
pair<int, int> a[MAXN], b[MAXN];
map<int, bool> vis[MAXN];

int main() {
  cin >> n >> m >> l;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i].first;
    b[i].second = i;
  }
  sort(b + 1, b + m + 1, [](const pair<int, int> &i, const pair<int, int> &j) {
    return i.first > j.first;
  });
  for (int i = 1, x, y; i <= l; i++) {
    cin >> x >> y;
    vis[x][y] = 1;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int j = 1;
    for (; j <= m && vis[i][b[j].second]; j++) {
    }
    ans = max(ans, a[i].first + b[j].first);
  }
  cout << ans;
  return 0;
}

```

---

## 作者：ZnPdCo (赞：1)

要使得 $a_i+b_i$ 尽量大，那就要使得 $a_i$ 和 $b_i$ 尽量大。贪心处理，从大到小枚举 $a_i$ 和 $b_i$。如果 $a_i$ 和 $b_i$ 不匹配就跳过。因为最多有 $l$ 条规则，所以最多会跳 $l$ 次，不超时。

可以使用 `set` 判断是否匹配。

```c++
#include <bits/stdc++.h>
#define ll long long
#define N 100010
#define debug() printf("debug");
#define newll(x) ll x = 0
#define newarr(x) ll x[N] = {0}
#define newvis(x) bool x[N] = {0}
#define outt printf
#define inn scanf
using namespace std;
ll n, m, l, Case=1, ans;
struct node {
	ll pos, val;
} a[N], b[N];
ll aa[N], bb[N];
set<ll> s[N];
void solve();
int main() {
	while(Case--) solve();
}
bool cmp(node x, node y) {
	return x.val > y.val;
}
void solve() {
	inn("%lld %lld %lld", &n, &m, &l);
	for(ll i = 1; i <= n; i++) {
		inn("%lld", &a[i].val);
		a[i].pos=i;
	}
	sort(a+1, a+1+n, cmp);
	for(ll i = 1; i <= n; i++) {
		aa[a[i].pos] = i;
	}
	
	for(ll i = 1; i <= m; i++) {
		inn("%lld", &b[i].val);
		b[i].pos=i;
	}
	sort(b+1, b+1+m, cmp);
	for(ll i = 1; i <= m; i++) {
		bb[b[i].pos] = i;
	}
	for(ll i = 1; i <= l; i++) {
		ll c, d;
		inn("%lld %lld", &c, &d);
		c = aa[c];
		d = bb[d];
		s[c].insert(d);
	}
	for(ll i = 1; i <= n; i++) {
		for(ll j = 1; j <= m; j++) {
			if(s[i].find(j) == s[i].end()) {
				ans = max(ans, a[i].val + b[j].val);
				break;
			}
		}
	}
	outt("%lld", ans);
}
```



---

## 作者：xz001 (赞：0)

- 首先我们可以记录下来每种主菜**不能**和哪些配菜搭配，这个可以用 ```vector <int> t[N];```。
- 然后我们将其排序，我们会发现此时每种主菜可以搭配的配菜的每相邻两项 $(t_{i,j-1},t_{i,j})$ 区间内的元素都是可取的，我们扫描每一个主菜，从这些区间里找最值即可，这个可以用 ```ST``` 表，由于还有 $[1,t_{i,0})$ 和 $(t_{i,t_i.size()-1},m]$ 这两段区间内的元素是可取的，我们在 ```vector``` 里插入 $0$ 和 $m+1$ 即可省去特判。
- 时间复杂度 $O(l\log_2l+m\log_2m)$，代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>
#define int long long

using namespace std;

int st[200005][25], n, m, l, a[200005], b[200005], c[200005], d[200005], ans;

vector <int> t[200005];

int query (int l, int r) {
	int s = log2(r - l + 1);
	return max(st[l][s], st[r - (1 << s) + 1][s]);
}

signed main() {
    scanf("%lld%lld%lld", &n, &m, &l);
    for (int i = 1; i <= n; ++ i) scanf("%lld", a + i);
    for (int i = 1; i <= m; ++ i) scanf("%lld", b + i), st[i][0] = b[i];
    for (int i = 1; i <= n; ++ i) t[i].push_back(0);  //插入 0
    for (int i = 1; i <= l; ++ i) {
    	scanf("%lld%lld", c + i, d + i);
    	t[c[i]].push_back(d[i]); //存储不能搭配的配菜
	}
	for (int i = 1; i <= n; ++ i) t[i].push_back(m + 1), sort(t[i].begin(), t[i].end());  //插入 m + 1
	for (int j = 1; j <= 20; ++ j)  // ST 表
	    for (int i = 1; i + (1 << j) - 1 <= m; ++ i)
	        st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j < (int)t[i].size(); ++ j) {
			int l = t[i][j - 1], r = t[i][j];
			if (l == r - 1) continue;
			ans = max(ans, a[i] + query (l + 1, r - 1));
		}
	}
	printf("%lld", ans);
    return 0;
}


```

---

## 作者：yhx0322 (赞：0)

## Desciption
有 $n$ 种主菜和 $m$ 种副菜。现在有 $l$ 对不是好的配对。求出最大的配对方案。

## Solution
将两个数列从大到小排序，则答案点对一定存在于 $(1 \sim 400, 1 \sim m)$ 和 $(1 \sim n, 1 \sim 400)$ 之中。

可以反证上述结论：最大的，不存在与上述区间的点对为 $(401,401)$，比其更大的至少有 $400^2 = 1.6 \times 10^5$ 个点对，然而最多只会排斥掉 $10 ^ 5$ 个点对，故结论区间必定包含答案。
 
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
const int inf = 2e18, N = 1e6 + 10;
map<int, map<int, int>> mp;
int n, m, l;

struct node {
    int x, id;

    bool operator<(const node &c) const {
        return x > c.x;
    }
} a[N], b[N];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> l;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x;
        a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= m; i++) {
        cin >> b[i].x;
        b[i].id = i;
    }
    sort(b + 1, b + m + 1);
    while (l--) {
        int x, y;
        cin >> x >> y;
        mp[x][y] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[a[i].id][b[j].id] == 0) {
                ans = max(ans, a[i].x + b[j].x);
                break;
            }
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：naroanah (赞：0)

对于每个 $a_i$，显然与最大的且可以匹配的 $b_i$ 匹配，所产生的贡献最大，最后所求的即为所有贡献的最大值。注意到 $L \le 10^5$，可以将 $b$ 排序后直接暴力倒序扫描，找到最大的可以和当前 $a_i$ 匹配的 $b_i$，即可求出当前 $a_i$ 的答案。

时间复杂度 $O(n \log{m})$。
```cpp
#include<bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define req(i, r, l) for(int i = (r); i >= (l); i--)
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define fi first
#define se second
#define all(x) begin(x), end(x)
using namespace std;
constexpr int N = 1e5 + 10, inf = 0x3f3f3f3f, INF = 0x7f7f7f7f; constexpr double eps = 1e-9;
int n, m, L;
int a[N];
pii b[N];
bool vis[N];
vector<int> g[N];
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m >> L;
    rep(i, 1, n) cin >> a[i]; rep(i, 1, m) {cin >> b[i].fi; b[i].se = i;};
    sort(b + 1, b + m + 1);
    rep(i, 1, L) {
        int u, v; cin >> u >> v; g[u].emplace_back(v);
    }
    int ans = -1;
    rep(i, 1, n) {
        for(auto it : g[i]) vis[it] = 1;
        req(j, m, 1) if(!vis[b[j].se]) {ans = max(ans, a[i] + b[j].fi);  break;}
        for(auto it : g[i]) vis[it] = 0;
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Leeb (赞：0)

### 题意简述

有 $n$ 种主菜，每种价格为 $a_i$，有 $m$ 种配菜，每种价格为 $b_i$。套餐由一道主菜和一道配菜组成，价格为所选主菜和所选配菜的价格之和。存在 $l$ 组不同的不存在的套餐组合 $(c_i,d_i)$。求提供的最贵套餐的价格。
### 解题思路

枚举每一道主菜，每次将对于这道主菜而言不可行的配菜删掉，然后统计答案，再将删掉的小菜加回去。

- 使用 multiset 实现。
### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <set>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define N 100005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
// #define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define pii pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, m, l, ans, a[N], b[N];
multiset<int> st;
vector<int> G[N];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline int max(int a, int b) {
    return a > b ? a : b;
}
inline void init() {
    n = in(), m = in(), l = in();
    for (int i = 1; i <= n; ++i) a[i] = in();
    for (int i = 1; i <= m; ++i) 
        b[i] = in(), st.insert(b[i]);
    for (int i = 1; i <= l; ++i) {
        int c = in(), d = in();
        G[c].push_back(d);
    }
}
inline void work() {
    for (int i = 1; i <= n; ++i) {
        for (auto x : G[i]) 
            st.erase(st.find(b[x]));
        if (!st.empty()) 
            ans = max(ans, a[i] + *st.rbegin());
        for (auto x : G[i]) st.insert(b[x]);
    }
    out(ans, endl);
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```

---

## 作者：_smart_stupid_ (赞：0)

# [题目](https://www.luogu.com.cn/problem/AT_abc331_e)

## 思路：

这道题可以用无脑的方法做，就是类似暴力。

## 方法：

先将一对套餐用整数的方式表示出来，设主菜为 $i$，配菜为 $j$，那么这对套餐可以用 $i \times 100010 + j$ 的形式表示为一个数，因为 $i,j \leq 100000$，所以所有套餐都可以用不重复的整数表示出来。

用一个 map 数组 $mp$ 存储每个套餐合不合适，每输入一个不合适的套餐，就将套餐用上述方式表示为一个数，设它为 $x$，那么就让 $mp_x$ 为 $1$，表示该配餐不可行。

然后将配餐与他的原下标绑定，这里我用了结构体，然后将配餐按价格从大到小排序。

**最重点的一部分：**

枚举主餐 $i$，对于每个 $i$，都遍历配餐数组，用上面的 $mp$ 数组判断：这个套餐是否可行。如果这个套餐可行，就更新答案，然后跳出这个 $i$ 的枚举，去看下一个 $i$，因为前面将配餐数组排了序，所以这里可以保证第一个可行的配餐就是该主餐价格最大的方案。

因为有 $L$ 个不可行的配餐，所以枚举时最多会枚举 $L$ 个不可行的套餐和 $N$ 个可行的套餐，时间复杂度 $O(N + L)$，可以通过此题。

## AC Code：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<list>
#include<set>
#include<map>
using namespace std;
int n, m;
int l;
int a[100100];
struct node{
	int id, val;
}b[100100];
map<long long, bool> mp;
bool cmp(node a, node b) {
	return a.val > b.val;
}
int ans = 0;
const int x = 100010;
int main(){
	scanf("%d%d%d", &n, &m, &l);
	for (int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; i ++) {
		scanf("%d", &b[i].val);
		b[i].id = i;
	}
	for (int i = 1; i <= l; i ++) {
		int tmp1, tmp2;
		scanf("%d%d", &tmp1, &tmp2);
		long long tmp = tmp1*x + tmp2;
		mp[tmp] = 1;
	}
	sort(b + 1, b + 1 + n, cmp);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			if(mp[i * x + b[j].id] == 0) {
				ans = max(ans, a[i] + b[j].val);
				break;
			}
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

