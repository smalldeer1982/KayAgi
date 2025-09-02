# Too Easy Problems

## 题目描述

你正在准备一场关于调度理论的考试。

这场考试会持续正好 $T$ 毫秒，由 $n$ 道题目组成。

你可以用 $t_i$ 毫秒解决第 $i$ 个问题，或者忽略它并不消耗时间。你也不需要用来在做完一道题之后休息的时间。

不幸的是，你的老师认为一些题目对你来说太简单了。因此，他对于每道题 $i$ 规定了一个整数 $a_i$，表示题目 $i$ 只在你总共解决了不超过 $a_i$ 个问题（包括问题 $i$ ）的情况下为你的最终成绩加上一分。

正式地，假设你在考试中解决了问题 $p_1,p_2,\cdots,p_k$。那么，你的最终成绩 $s$ 会等于在 $1$ 到 $k$ 之间的满足 $k\le a_{p_j}$ 的 $j$ 的个数。

你已经意识到这场考试真正的第一道题目已经放在了你面前。因此，你想要选择一组题目来解决，从而最大化你的最终成绩。不要忘记这场考试有时间限制，而你必须有足够的时间来解决所有你选择的题目。如果存在多个最优解，任意输出一组即可。

## 说明/提示

$1\le n\le 2\times10^5$

$1\le T\le10^9$

$0\le k\le n$

## 样例 #1

### 输入

```
5 300
3 100
4 150
4 80
2 90
2 300
```

### 输出

```
2
3
3 1 4
```

## 样例 #2

### 输入

```
2 100
1 787
2 788
```

### 输出

```
0
0

```

## 样例 #3

### 输入

```
2 100
2 42
2 58
```

### 输出

```
2
2
1 2
```

# 题解

## 作者：Sol1 (赞：2)

Greedy!

我们可以显然发现，如果我们想要获得$k$分，那么其实我们只需要做$k$道题就可以了。因为如果我们做了$k+1$道题，然后我们只获得了$k$分，那么就一定会有一道题满足$a_i \leq k$，那么我们直接将这道题扔掉，只会让时间更少，而不会让答案变少。**换句话说，我们如果能做$k+1$题并获得$k$分，那么我们做$k$题也一定能获得$k$分。**

那么怎么贪心呢？显然，如果我们要在时限内做出$k$题，显然我们要从耗时小的开始做。注意，如果此题满足$a_i<k$，那么就可以直接扔掉它。

具体来说，我们可以二分枚举$k$，然后用一个函数来判断是否可以做$k$题并获得$k$分。

时间复杂度：排序$\Theta(N \log N)$，二分$\Theta(\log N)$，验证二分值$\Theta(N)$，总时间复杂度$\Theta(N \log N)$。

CODE:

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//用一个结构体来存储问题，方便排序以及输出
struct Problem {
	int a, t, idx;
	bool operator < (const Problem& p) const {
		return t < p.t;
	}
};
int n, t;
Problem p[200005];

void Read() {
	scanf("%d%d", &n, &t);
	for (int i = 1;i <= n;i++) {
		scanf("%d%d", &p[i].a, &p[i].t);
		p[i].idx = i;
	}
}
//检验二分出的答案是否可行
bool Chk(int x) {
	int tmp = t, scr = 0;//tmp为当前剩下的时间，scr为当前已经达到的分数
	for (int i = 1;i <= n;i++) {
		if (tmp < p[i].t) {
			break;
		}
		if (p[i].a < x) {
			continue;
		}
		scr++;
		tmp -= p[i].t;
	}
	return scr >= x;
}
//输出答案
void GetAns(int x) {
	int tmp = t, s = 0;
	for (int i = 1;i <= n;i++) {
		if (tmp < p[i].t) {
			break;
		}
		if (p[i].a < x) {
			continue;
		}
		printf("%d ", p[i].idx);
		tmp -= p[i].t;
		s++;
		if (s == x) {
			break;
		}
	}
}
//二分
void Solve() {
	int l = 0, r = n + 1;
	while (l < r - 1) {
		int mid = l + r >> 1;
		if (Chk(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	printf("%d\n%d\n", l, l);
	GetAns(l);
}

int main() {
	Read();
	sort(p + 1, p + n + 1);
	Solve();
	return 0;
}
```

---

## 作者：Tzs_yousa (赞：1)

## 贪心策略
第一要素：看到时间有限的问题首先就会想到排序，直接把时间按从小到大排序即可。

第二要素：获得 $k$ 分，就需要做 $k$ 道题，因为一道题对应一分，要么不给分要么给一分，所以如果要得到 $k$ 分就不必再多做一道题。

## 二分答案
二分答案，通过大眼观察法，我们可以发现这是个单调的，所以就可以二分一个答案，这样就可以在对数级别的时间里将答案得出。

## AC code
```cpp
//这里使用了一个 $pair$ 来存题号。
#include <bits/stdc++.h>
#define int long long
const int MAXN = 200001;
using namespace std;
int a[MAXN], t[MAXN], n, T, tmp[MAXN];
pair<int, int> ans[MAXN];
bool check(int mid) 
{
	int cnt = 0;
	for (int i = 1; i <= n; i++) if (a[i] >= mid) tmp[++cnt] = t[i];
	sort(tmp + 1, tmp + 1 + cnt);
	if (mid > cnt) return 0;
	int sum = 0;
	for (int i = 1; i <= mid; i++)  sum += tmp[i];
	if(sum <= T) return true;
	return false;
}
signed main() 
{
	scanf("%lld%lld", &n, &T);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &t[i]);
	int l = 0, r = n;
	int mid = (l + r) / 2;
	while (r > l) 
	{
		if (check(mid)) l = mid;
		else r = mid - 1;
		mid = (l + r + 1) / 2;
	}
	printf("%lld\n%lld\n", mid, mid);
	int cnt = 0;
	for (int i = 1; i <= n; i++) 
		if (a[i] >= mid) ans[++cnt] = make_pair(t[i], i);
	sort(ans + 1, ans + 1 + cnt);
	for (int i = 1; i <= mid; i++) 
		printf("%lld ", ans[i].second);
	printf("\n");
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：0)

\* 1800，不知道为什么二分，不知道为什么蓝。

显然没贡献的不选。

用大根堆维护前 $k$ 大，每次插入的时候只需要和堆顶比较就行了。

从大到小钦定选 $i$ 个，把新增的（即 $a=i$）插入，然后如果大小超了就弹出。

每个插入一次删除一次，显然是 $O(n\log n)$ 的。

---

## 作者：JimmyLee (赞：0)

# 题意

> 给定一场考试，考试会持续 $T$ 毫秒，由 $n$ 道题目组成，你可以用 $t_i$ 毫秒解决第 $i$ 个问题，每个问题给定一个整数 $a_i$。
>
>要求你选出一个试题集合 $S$，若该集合大小为 $k$，它应满足 $T\geq\sum_{i\in S}\limits t_i$，你需要最大化 $\sum_{i\in S}\limits [a_i\geq k]$。

# 分析

显然所做的题数就应该是得分，因为不得分的题没有做的必要。

容易发现做的题越多，耗时也越多，同时能够提供分数的题越少，显然有单调性。

考虑二分答案。

我们在钦定了答案 $k$ 后，只需要将所有的能产生贡献的题目（即 $a_i\geq k$ 的题目）按时长从小到大排序，然后贪心选取。

时间复杂度 $O(n\log n)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 200005

struct test
{
    int a, t, id;
    test(int A, int T, int I): a(A), t(T), id(I) {}
};

vector<test> con, tmp, ans;

bool chk(int k, int T)
{
    tmp.clear();
    for(auto [a, t, i]:con)
        if(a>=k) tmp.emplace_back(a, t, i);
    sort(tmp.begin(), tmp.end(), [](test &a, test &b){return a.t<b.t;});
    int cnt=0;
    for(auto [a, t, i]:tmp)
    {
        if(T<t) break;
        cnt++, T-=t;
    }
    return cnt>=k;
}

int main()
{
    int n, T;
    cin>>n>>T;
    for(int i=1, a, t;i<=n;i++)
        cin>>a>>t, con.emplace_back(a, t, i);
    int l=0, r=3e5;
    while(l+1<r)
    {
        int mid=(l+r)>>1;
        if(chk(mid, T)) l=mid, ans=tmp;
        else r=mid; 
    }
    cout<<l<<'\n'<<l<<'\n';
    for(int i=0;i<l;i++)
        cout<<ans[i].id<<' ';
}
```

---

## 作者：Loser_Syx (赞：0)

考虑构造出的合法方案，当 $a_i < s$ 时，这个答案不作任何贡献，而且还会增加耗时（因为 $a_i \geq 1$），故可以去掉选项。  
所以有结论：可以构造出 $k=s$ 的一个答案其中每个都满足 $a_i \geq s$。

因为 $a_i \geq 1$，所以不会存在减去用时的情况，故对于每个 $s$，贪心选择满足 $a_i \geq s$ 中 $t_i$ 最小的 $s$ 个数。  
然后由于 $s$ 越小可供选择的越多，故满足单调性，可以二分答案。 

```cpp
struct node {
	int first, second, id;
	bool operator < (const node &a) const {
		return first < a.first;
	}
} a[1010101];
void solve() {
	int n = read(), t = read();
	for (int i = 1; i <= n; ++i) {
		read(a[i].second, a[i].first);
		a[i].id = i;
	}
	sort(a + 1, a + 1 + n);
	auto check = [&](int x) -> bool {
		int cnt = 0, tim = t;
		for (int i = 1; i <= n; ++i) {
			if (a[i].second >= x) {
				if (a[i].first <= tim) {
					tim -= a[i].first;
					++cnt;
				} else break;
			}
		}
		return cnt >= x;
	};
	int l = 0, r = 1e9;
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid;
	}
	write(r - 1, '\n');
	write(r - 1, '\n');
	int cnt = 0, tim = t;
	for (int i = 1; i <= n; ++i) {
		if (a[i].second >= r-1) {
			if (a[i].first <= tim) {
				tim -= a[i].first;
				++cnt;
				write(a[i].id, ' ');
				if (cnt == r-1) break;
			}
		}
	}
}
```

---

## 作者：Black_Porridge (赞：0)

~~这个翻译是什么情况啊/fad~~ 现在好了

## 题目大意：

给定 $n$ 个问题和总时间限制 $T$ ，每道题目需要时间 $t_i$ 来解决，同时有一限制 $a_i$ ，只有当解决的问题数 $k\leq a_i$ 时回答该问题才有效，求在时限 $T$ 内能解决的最大有效问题数。

## 解题思路：

我们考虑贪心。因为题目的价值是相同的，所以为了在时限内解决问题，我们要从花费时间最少的开始计算（即先排序）。如果 $a_i < k$ 则直接丢掉不做计算。这里给出具体实现的两种方法。

- 二分答案

	二分枚举答案 $k$ ，按照前面提到的思路在  ```check``` 函数中计算此时的得分。再比较得分是否大于等于 $k$ 即可。
    
    时间复杂度 $O(n\log n)$
    
    code：
    ```
  #include <iostream>
  #include <queue>
  #include <algorithm>
  using namespace std;
  const int N = 2e5 + 10;

  int n, t, ans;
  int id[N], a[N], tt[N];

  bool cmp(int x, int y) {
      return tt[x] < tt[y];
  }

  bool check(int x) {
      int now = t, hav = 0;
      for(int i = 1; i <= n && now >= tt[id[i]]; i++) {
          if(a[id[i]] < x)
              continue;
          hav++;
          now -= tt[id[i]];
      }
      if(hav >= x)
          return 1;
      return 0;
  }

  int main() {
      cin >> n >> t;
      for(int i = 1; i <= n; i++)
          cin >> a[i] >> tt[i], id[i] = i;
      sort(id + 1, id + n + 1, cmp);
      int l = 0, r = N;
      while(l <= r) {
          int mid = (l + r) >> 1;
          if(check(mid))
              ans = mid, l = mid + 1;
          else
              r = mid - 1;
      }
      cout << ans << "\n" << ans << "\n";
      int now = t, hav = 0;
      for(int i = 1; i <= n && now >= tt[id[i]]; i++) {
          if(a[id[i]] < ans)
              continue;
          cout << id[i] << " ";
          hav++;
          now -= tt[id[i]];
          if(hav >= s)//注意这里一定要保证输出的个数和答案大小相同
              break;
      }
      return 0;
  }


- 优先队列

	从 $n$ 枚举到 $0$ ，维护优先队列。对于枚举的第 $i$ 道题目，当队列大小为 $i$ 且花费时间 $<T$ 时题目对答案产生贡献。
   
    时间复杂度 $O(n\log n)$



---

