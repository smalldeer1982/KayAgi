# 题目信息

# Binary String Copying

## 题目描述

You are given a string $ s $ consisting of $ n $ characters 0 and/or 1.

You make $ m $ copies of this string, let the $ i $ -th copy be the string $ t_i $ . Then you perform exactly one operation on each of the copies: for the $ i $ -th copy, you sort its substring $ [l_i; r_i] $ (the substring from the $ l_i $ -th character to the $ r_i $ -th character, both endpoints inclusive). Note that each operation affects only one copy, and each copy is affected by only one operation.

Your task is to calculate the number of different strings among $ t_1, t_2, \ldots, t_m $ . Note that the initial string $ s $ should be counted only if at least one of the copies stays the same after the operation.

## 说明/提示

Consider the first example. Copies below are given in order of the input operations. Underlined substrings are substrings that are sorted:

1. 101100 $ \rightarrow $ 011100;
2. 101100 $ \rightarrow $ 011100;
3. 101100 $ \rightarrow $ 101100;
4. 101100 $ \rightarrow $ 101100;
5. 101100 $ \rightarrow $ 000111.

There are three different strings among $ t_1, t_2, t_3, t_4, t_5 $ : 000111, 011100 and 101100.

Consider the second example:

1. 100111 $ \rightarrow $ 100111;
2. 100111 $ \rightarrow $ 001111;
3. 100111 $ \rightarrow $ 001111;
4. 100111 $ \rightarrow $ 010111.

There are three different strings among $ t_1, t_2, t_3, t_4 $ : 001111, 010111 and 100111.

## 样例 #1

### 输入

```
3
6 5
101100
1 2
1 3
2 4
5 5
1 6
6 4
100111
2 2
1 4
1 3
1 2
1 1
0
1 1```

### 输出

```
3
3
1```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由 $n$ 个字符组成的字符串 $s$，字符仅包含 0 和/或 1。

你生成了 $m$ 个该字符串的副本，记第 $i$ 个副本为字符串 $t_i$。然后对每个副本执行一次操作：对第 $i$ 个副本，你将其子串 $[l_i, r_i]$（从第 $l_i$ 个字符到第 $r_i$ 个字符，包含端点）进行排序。注意，每个操作只影响一个副本，且每个副本只被一个操作影响。

你的任务是计算 $t_1, t_2, \ldots, t_m$ 中不同字符串的数量。注意，如果至少有一个副本在操作后保持不变，则初始字符串 $s$ 也应被计入。

#### 说明/提示

考虑第一个例子。副本按输入操作的顺序给出。下划线的子串是被排序的子串：

1. 101100 → 011100;
2. 101100 → 011100;
3. 101100 → 101100;
4. 101100 → 101100;
5. 101100 → 000111.

在 $t_1, t_2, t_3, t_4, t_5$ 中有三个不同的字符串：000111, 011100 和 101100。

考虑第二个例子：

1. 100111 → 100111;
2. 100111 → 001111;
3. 100111 → 001111;
4. 100111 → 010111.

在 $t_1, t_2, t_3, t_4$ 中有三个不同的字符串：001111, 010111 和 100111.

#### 样例 #1

##### 输入

```
3
6 5
101100
1 2
1 3
2 4
5 5
1 6
6 4
100111
2 2
1 4
1 3
1 2
1 1
0
1 1
```

##### 输出

```
3
3
1
```

### 算法分类

字符串、排序、哈希

### 题解分析与结论

该题的核心问题是如何高效地统计在对字符串进行多次子串排序后，得到的不同字符串的数量。由于每次操作只影响一个副本，且每个副本只被一个操作影响，因此需要找到一种方法来判断哪些操作会导致相同的字符串结果。

大多数题解都采用了以下思路：

1. **区间优化**：通过预处理每个位置左边第一个 0 和右边第一个 1 的位置，将原始区间 $[l_i, r_i]$ 优化为实际需要排序的区间 $[nxt_l, pre_r]$。这样可以避免对已经有序的部分进行不必要的排序。
  
2. **哈希去重**：使用哈希表或 `unordered_map` 来记录不同的区间，从而统计不同字符串的数量。

3. **特殊情况处理**：当优化后的区间无效（如 $nxt_l > pre_r$）时，说明该操作不会改变字符串，直接将其视为无效操作。

### 所选题解

#### 题解 1：zfx_VeXl6 (赞：19)

- **星级**：★★★★★
- **关键亮点**：
  - 通过预处理每个位置左边第一个 0 和右边第一个 1 的位置，优化了区间排序的范围。
  - 使用 `unordered_map` 记录不同的区间，避免了重复计算。
  - 代码简洁，逻辑清晰，易于理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=2e5+2;
int t,n,m,nxt[N],pre[N],ans;
char s[N];
LL hsh(int x,int y){return 1LL*(n+1)*x+y;}
unordered_map<LL,int>vis;
int main()
{
    cin>>t;
    while(t--)
    {
        vis.clear();
        ans=0;
        cin>>n>>m;
        nxt[n+1]=n+1;
        scanf("%s",s+1);
        for(int i=1;i<=n;i++)
            if(s[i]=='1')
                pre[i]=pre[i-1];
            else
                pre[i]=i;
        for(int i=n;i;i--)
            if(s[i]=='0')
                nxt[i]=nxt[i+1];
            else
                nxt[i]=i;
        for(int i=1;i<=m;i++)
        {
            int l,r;
            cin>>l>>r;
            l=nxt[l];
            r=pre[r];
            if(l>r)
                l=r=0;
            if(!vis[hsh(l,r)])
            {
                ans++;
                vis[hsh(l,r)]=1;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

#### 题解 2：liuhl_weifang (赞：11)

- **星级**：★★★★
- **关键亮点**：
  - 通过预处理每个位置左边第一个 0 和右边第一个 1 的位置，优化了区间排序的范围。
  - 使用 `map` 记录不同的区间，避免了重复计算。
  - 代码结构清晰，易于理解。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
char s[200010];
int l[200010];//左边第一个 0 的位置
int r[200010];//右边第一个 1 的位置
map<pair<int,int>,bool> p;

void solve()
{
	p.clear();
	cin >> n >> m >> s+1;
	int pos = 0;
	for (int i=1;i<=n;i++) 
	{
		if(s[i]=='0') pos = i;
		l[i] = pos;
	}
	pos = n+1;
	for (int i=n;i>=1;i--)
	{
		if(s[i]=='1') pos = i;
		r[i] = pos;
	}
	int ans = 0;
	for (int i=1;i<=m;i++)
	{
		int a,b;
		cin >> a >> b;
		a = r[a];//过滤掉左边的 0，相当于跳到右边的 1 
		b = l[b];//过滤掉右边的 1，相当于跳到左边的 0
		if(a>b) a = 1,b = 1;//这种情况属于排序排了个寂寞 
		if(p[make_pair(a,b)]==false)
		{
			p[make_pair(a,b)] = true;
			ans++;
		}
	}
	cout << ans << "\n";
	return;
} 
 
signed main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

#### 题解 3：escapist404 (赞：8)

- **星级**：★★★★
- **关键亮点**：
  - 使用字符串哈希来计算排序后的字符串的哈希值，避免了直接生成字符串的开销。
  - 通过前缀和和哈希值的组合，高效地计算了排序后的字符串的哈希值。
  - 代码结构清晰，逻辑严谨。

```cpp
#include <bits/stdc++.h>

using i64 = unsigned long long;

std::vector<i64> base;

std::mt19937_64 rnd(time(0));

void get_hash(int n) {
	base.assign(n, 0);
	for (i64& i : base) i = rnd();
}

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::string s;
	std::cin >> s;

    get_hash(n);

	std::vector<i64> pre(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] + (s[i - 1] == '1' ? base[i - 1] : 0);
	}

	std::vector<int> num(n + 1, 0);
	std::vector<i64> fill(n + 1, 0);

	for (int i = 1; i <= n; ++i) {
		num[i] = num[i - 1] + (s[i - 1] == '1' ? 1 : 0);
		fill[i] = fill[i - 1] + base[i - 1];
	}

	std::vector<std::pair<int, int>> q(m);
	for (int i = 0; i < m; ++i) {
		std::cin >> q[i].first >> q[i].second;
        --q[i].first;
	}

    i64 hash = pre[n];

	std::set<i64> set;
	for (auto i : q) {
        i64 old = hash - pre[i.second] + pre[i.first];
        i64 ocr = num[i.second] - num[i.first];
        i64 cur = fill[i.second] - fill[i.second - ocr];
        set.insert(old + cur);
	}

	std::cout << set.size() << '\n';
}

int main() {
	int tt;
	std::cin >> tt;
	while (tt--) {
		solve();
	}
	return 0;
}
```

### 最优关键思路与技巧

1. **区间优化**：通过预处理每个位置左边第一个 0 和右边第一个 1 的位置，将原始区间 $[l_i, r_i]$ 优化为实际需要排序的区间 $[nxt_l, pre_r]$，从而减少不必要的排序操作。

2. **哈希去重**：使用哈希表或 `unordered_map` 来记录不同的区间，从而高效地统计不同字符串的数量。

3. **特殊情况处理**：当优化后的区间无效时，直接将其视为无效操作，避免不必要的计算。

### 可拓展之处

该题的思路可以拓展到其他需要对字符串进行多次操作并统计不同结果的问题。例如，可以对字符串进行其他类型的操作（如反转、替换等），并使用类似的方法来优化和去重。

### 推荐题目

1. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
2. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
3. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)

---
处理用时：79.20秒