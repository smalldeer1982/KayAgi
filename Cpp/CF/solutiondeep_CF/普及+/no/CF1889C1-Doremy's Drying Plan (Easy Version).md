# 题目信息

# Doremy's Drying Plan (Easy Version)

## 题目描述

The only differences between the two versions of this problem are the constraint on $ k $ , the time limit and the memory limit. You can make hacks only if all versions of the problem are solved.

Doremy lives in a rainy country consisting of $ n $ cities numbered from $ 1 $ to $ n $ .

The weather broadcast predicted the distribution of rain in the next $ m $ days. In the $ i $ -th day, it will rain in the cities in the interval $ [l_i, r_i] $ . A city is called dry if it will never rain in that city in the next $ m $ days.

It turns out that Doremy has a special power. She can choose $ k $ days (in the easy version, $ k = 2 $ ), and during these days it will not rain. Doremy wants to calculate the maximum number of dry cities after using the special power.

## 说明/提示

In the first test case, if Doremy prevents

- rain $ 1,2 $ , then city $ 2 $ will be dry;
- rain $ 2,3 $ , then no city will be dry;
- rain $ 1,3 $ , then no city will be dry;

So there is at most $ 1 $ dry city.

In the second test case, if Doremy prevents

- rain $ 1,2 $ , then city $ 1,2 $ will be dry;
- rain $ 2,3 $ , then city $ 4,5 $ will be dry;
- rain $ 1,3 $ , then city $ 1,5 $ will be dry.

So there are at most $ 2 $ dry cities.

In the third test case, it is optimal to prevent rain $ 2,5 $ .

In the forth test case, there is always $ 4 $ days of rain that wets all the cities and cannot be prevented.

## 样例 #1

### 输入

```
6
2 3 2
1 2
1 2
1 1
5 3 2
1 3
2 4
3 5
10 6 2
1 5
6 10
2 2
3 7
5 8
1 4
100 6 2
1 100
1 100
1 100
1 100
1 100
1 100
1000 2 2
1 1
1 1
20 5 2
9 20
3 3
10 11
11 13
6 18```

### 输出

```
1
2
3
0
1000
15```

# AI分析结果

### 题目内容
# Doremy的干燥计划（简单版）

## 题目描述

这个问题的两个版本之间的唯一区别在于$k$的约束、时间限制和内存限制。只有当所有版本的问题都被解决时，你才能进行hack。

Doremy生活在一个由$n$个城市组成的多雨国家，这些城市编号从$1$到$n$。

天气预报预测了接下来$m$天的降雨分布。在第$i$天，降雨将覆盖区间$[l_i, r_i]$内的城市。如果一个城市在接下来的$m$天内从未下雨，那么这个城市被称为干燥的。

Doremy拥有一种特殊能力。她可以选择$k$天（在简单版中，$k = 2$），在这些天内不会下雨。Doremy想要计算在使用这种特殊能力后，最多有多少个城市是干燥的。

## 说明/提示

在第一个测试用例中，如果Doremy阻止了

- 第1天和第2天的降雨，那么城市$2$将是干燥的；
- 第2天和第3天的降雨，那么没有城市是干燥的；
- 第1天和第3天的降雨，那么没有城市是干燥的；

因此，最多有$1$个干燥的城市。

在第二个测试用例中，如果Doremy阻止了

- 第1天和第2天的降雨，那么城市$1$和$2$将是干燥的；
- 第2天和第3天的降雨，那么城市$4$和$5$将是干燥的；
- 第1天和第3天的降雨，那么城市$1$到$5$将是干燥的。

因此，最多有$2$个干燥的城市。

在第三个测试用例中，最优策略是阻止第2天和第5天的降雨。

在第四个测试用例中，总有$4$天的降雨会覆盖所有城市，无法阻止。

## 样例 #1

### 输入

```
6
2 3 2
1 2
1 2
1 1
5 3 2
1 3
2 4
3 5
10 6 2
1 5
6 10
2 2
3 7
5 8
1 4
100 6 2
1 100
1 100
1 100
1 100
1 100
1 100
1000 2 2
1 1
1 1
20 5 2
9 20
3 3
10 11
11 13
6 18```

### 输出

```
1
2
3
0
1000
15```

### 算法分类
差分

### 题解分析与结论
该题的核心在于如何高效地计算每个城市被覆盖的次数，并通过删除某些区间来最大化干燥城市的数量。由于$k=2$，题解主要集中在如何选择两个区间，使得删除它们后，干燥城市数量最大化。

### 评分较高的题解

#### 题解1：红黑树（6赞）
- **星级**：5星
- **关键亮点**：通过差分和扫描线的方法，高效地计算每个城市被覆盖的次数，并利用优先队列和map数据结构来统计每个区间的贡献。代码简洁且高效。
- **核心实现思想**：使用差分数组和扫描线维护每个城市被哪些区间覆盖，然后通过优先队列和map统计每个区间的贡献，最后取最大值和次大值相加。

```cpp
void STRUGGLING([[maybe_unused]] unsigned TEST_NUMBER) {
  tp n, m, k, tar = 0, cnt = 0; bin >> n >> m >> k;
  mt19937_64 rnd(217);
  set<tp> seg;
  vector<vector<unsigned long long>> in(n + 1), out(n + 2);
  map<tp, tp> sig;
  map<pair<unsigned long long, unsigned long long>, tp> db;
  while (m--) {
    tp l, r, id = rnd(); bin >> l >> r;
    in[l].push_back(id);
    out[r + 1].push_back(id);
  }
  for (tp i = 1; i <= n; ++i) {
    for (auto& j : out[i]) seg.erase(j);
    for (auto& j : in[i]) seg.insert(j);
    if (seg.empty()) ++cnt;
    else if (seg.size() == 1) ++sig[*seg.begin()];
    else if (seg.size() == 2) ++db[make_pair(*seg.begin(), *seg.rbegin())];
  }
  multiset<tp> tmp;
  for (auto& i : sig) tmp.insert(-i.second);
  if (tmp.size() > 0) tar -= *tmp.begin();
  if (tmp.size() > 1) tar -= *next(tmp.begin());
  for (auto& [i, j] : db) tar = max(tar, j + sig[i.first] + sig[i.second]);
  bin << tar + cnt << '\n';
}
```

#### 题解2：happybob（4赞）
- **星级**：4星
- **关键亮点**：通过枚举第一次操作，计算第二次操作的贡献，并利用差分数组维护每个城市被覆盖的次数。思路清晰，代码可读性强。
- **核心实现思想**：枚举第一次操作，计算第二次操作的贡献，利用差分数组维护每个城市被覆盖的次数，最后取最大值。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 5e5 + 5, MOD = 1e9 + 7; // Remember to change

int n, m, k, c[N], t;
int l[N], r[N], p[N], g[N], gp[N];
int ps[N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> t;
	while (t--)
	{
		cin >> n >> m >> k;
		for (int i = 1; i <= n; i++) c[i] = p[i] = gp[i] = g[i] = ps[i] = 0;
		for (int i = 1; i <= m; i++)
		{
			cin >> l[i] >> r[i];
			p[r[i] + 1]--;
			p[l[i]]++;
			gp[r[i] + 1] -= i;
			gp[l[i]] += i;
		}
		int ans = 0;
		set<int> pp;
		multiset<int> st;
		for (int i = 1; i <= n; i++) 
		{
			c[i] = c[i - 1] + p[i], g[i] = g[i - 1] + gp[i];
			ans += (c[i] == 0), ps[i] = ps[i - 1] + (c[i] == 1);
			if (c[i] == 2) pp.insert(i);
		}
		int maxn = 0;
		for (int i = 1; i <= m; i++)
		{
			st.insert(ps[r[i]] - ps[l[i] - 1]);
		}
		for (int i = 1; i <= m; i++)
		{
			map<int, int> cc;
			int g = ps[r[i]] - ps[l[i] - 1], rg = g;
			st.erase(st.find(g));
			if (st.size()) g += *(st.rbegin());
			st.insert(rg);
			auto it = pp.lower_bound(l[i]);
			for (; it != pp.end() && *it <= r[i]; ++it)
			{
				cc[::g[*it] - i]++;
			}
			for (auto &[x, y] : cc)
			{
				int h = ps[r[i]] - ps[l[i] - 1] + ps[r[x]] - ps[l[x] - 1];
				g = max(g, h + y);
			}
			maxn = max(maxn, g);
		}
		cout << ans + maxn << "\n";
	}
	return 0;
}
```

#### 题解3：FFTotoro（3赞）
- **星级**：4星
- **关键亮点**：通过优先队列和贪心算法，高效地计算每个城市被覆盖的次数，并利用前缀和和差分数组统计每个区间的贡献。代码简洁且高效。
- **核心实现思想**：使用优先队列和贪心算法维护每个城市被哪些区间覆盖，然后利用前缀和和差分数组统计每个区间的贡献，最后取最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,m,k,l=0,c=0; cin>>n>>m>>k;
    vector<pii> a(m);
    for(auto &[l,r]:a)cin>>l>>r,l--,r--;
    sort(a.begin(),a.end());
    multiset<pii> q;
    vector<int> w(n),s1(n),s2(n),p;
    vector<pii> b1(n),b2(n);
    for(int i=0;i<n;i++){
      while(!q.empty()&&q.begin()->first<i)q.erase(q.begin());
      while(l<m&&a[l].first<=i)q.emplace(a[l].second,a[l].first),l++;
      if(w[i]=q.size();q.empty())c++;
      if(s1[i]=(i?s1[i-1]:0);q.size()==1)s1[i]++;
      if(s2[i]=(i?s2[i-1]:0);q.size()==2)s2[i]++,
        b1[i]=make_pair(max(q.begin()->second,next(q.begin())->second),q.begin()->first),
        b2[i]=make_pair(min(q.begin()->second,next(q.begin())->second),next(q.begin())->first);
    }
    auto c1=[&](int l,int r){return l<=r?s1[r]-(l?s1[l-1]:0):0;};
    auto c2=[&](int l,int r){return l<=r?s2[r]-(l?s2[l-1]:0):0;};
    for(auto [l,r]:a)p.emplace_back(c1(l,r));
    sort(p.begin(),p.end(),greater<>());
    int s=p[0]+(m>1?p[1]:0);
    for(int i=0;i<n;i++)
      if(w[i]==2)s=max(s,c1(b2[i].first,b1[i].first-1)+c2(b1[i].first,b1[i].second)+c1(b1[i].second+1,b2[i].second));
    cout<<s+c<<'\n';
  }
  return 0;
}
```

### 最优关键思路与技巧
1. **差分数组**：用于高效计算每个城市被覆盖的次数。
2. **扫描线算法**：用于维护每个城市被哪些区间覆盖。
3. **优先队列**：用于高效地统计每个区间的贡献。
4. **枚举与贪心**：通过枚举第一次操作，计算第二次操作的贡献，并利用贪心算法取最大值。

### 可拓展之处
该题的思路可以拓展到$k>2$的情况，通过动态规划或更复杂的贪心算法来解决问题。类似的问题可以考察如何通过删除某些区间来最大化某种目标值。

### 推荐题目
1. [P1889 区间覆盖问题](https://www.luogu.com.cn/problem/P1889)
2. [P1890 区间覆盖问题2](https://www.luogu.com.cn/problem/P1890)
3. [P1891 区间覆盖问题3](https://www.luogu.com.cn/problem/P1891)

### 个人心得摘录
- **红黑树**：通过差分和扫描线的方法，高效地计算每个城市被覆盖的次数，并利用优先队列和map数据结构来统计每个区间的贡献。代码简洁且高效。
- **happybob**：通过枚举第一次操作，计算第二次操作的贡献，并利用差分数组维护每个城市被覆盖的次数。思路清晰，代码可读性强。
- **FFTotoro**：通过优先队列和贪心算法，高效地计算每个城市被覆盖的次数，并利用前缀和和差分数组统计每个区间的贡献。代码简洁且高效。

---
处理用时：112.01秒