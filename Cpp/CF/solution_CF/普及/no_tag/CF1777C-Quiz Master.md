# Quiz Master

## 题目描述

A school has to decide on its team for an international quiz. There are $ n $ students in the school. We can describe the students using an array $ a $ where $ a_i $ is the smartness of the $ i $ -th ( $ 1 \le i \le n $ ) student.

There are $ m $ topics $ 1, 2, 3, \ldots, m $ from which the quiz questions will be formed. The $ i $ -th student is considered proficient in a topic $ T $ if $ (a_i \bmod T) = 0 $ . Otherwise, he is a rookie in that topic.

We say that a team of students is collectively proficient in all the topics if for every topic there is a member of the team proficient in this topic.

Find a team that is collectively proficient in all the topics such that the maximum difference between the smartness of any two students in that team is minimized. Output this difference.

## 说明/提示

In the first test case, we have participants with smartnesses $ 3 $ and $ 7 $ , and $ m = 4 $ . Thus, there is no student with smartness divisible by $ 2 $ . Since $ 2 \leq m $ , there is no way to choose a team.

In the second test case, we can select the participant with smartness $ 2 $ to be the only one on the team. This way the team will be collectively proficient in both topics $ 1 $ and $ 2 $ .

In the third test case, consider the team with participants of smartnesses $ 4, 5, 6, 7 $ . This way the team will be collectively proficient in all topics $ 1, 2, \ldots, 7 $ .

## 样例 #1

### 输入

```
3
2 4
3 7
4 2
3 7 2 9
5 7
6 4 3 5 7```

### 输出

```
-1
0
3```

# 题解

## 作者：yemuzhe (赞：7)

### 简化题意

- 给你 $n$ 个数，第 $i$ 个数是 $a _ i$。
- 你要从中选出若干个数，使得这些数的因子中包含 $1 \sim m$。
- 若可以选出这些数，则输出这些数极差（最大值减最小值）的最小值；否则输出 $-1$。
- 本题有 $t$ 组输入数据。$1 \le t \le 10 ^ 4, 1 \le n, m \le 10 ^ 5, 1 \le a _ i \le 10 ^ 5, \sum n \le 10 ^ 5, \sum m \le 10 ^ 5$

### 解题思路

首先可以将这些数从小到大排好序。容易发现，我们选的这些数一定是连续的（或者说不连续的一定不比连续的更优）。

既然这些数是连续的，可以看作一个区间。我们可以枚举区间的左端点 $l$，再来计算右端点 $r$。

观察到对于 $l ^ \prime > l$，$r ^ \prime$ 也一定 $\ge r$。根据这个性质，我们可以采取双指针算法求解。

首先可以预处理 $1 \sim m$ 的因子。预处理时可以不用 $\text O (m \sqrt m)$ 枚举所有数的因数，而是 $\text O (n \log n)$ 枚举每个因数的倍数，具体见代码。

我们可以用一个数组 $vis$ 来记录某个因子在这些数中出现的次数，$vis _ i$ 表示因子 $i$ 出现了几次；再用一个变量 $cnt$ 记录 $1 \sim m$ 中不同因子的个数。

首先在 $r < n$ 且 $cnt < m$ 的情况下不断增加右端点 $r$，$cnt < m$ 意味着 $1 \sim m$ 的因子还没有全部被包含。在增加右端点 $r$ 的时候，我们把 $a _ r$ 加入了这些数中，就要遍历 $a _ r$ 的所有因数，让这些因数的出现次数加 $1$。

具体地，对于某个因数 $t$，若 $t \le m$，我们让 $vis _ t$ 加 $1$，并在此之前，若 $vis _ t = 0$，则说明因子 $t$ 之前没有而现在有，将 $cnt$ 加 $1$。

更新完右端点 $r$ 后，若 $cnt = m$，则说明 $1 \sim m$ 已经都被包含了，更新答案，令 $ans = \min \{ans, a _ r - a _ l\}$。

然后为左端点 $l$ 增加 $1$ 做调整，我们遍历 $a _ l$ 的所有因数，让这些因数的出现次数减 $1$。

具体地，对于某个因数 $t$，若 $t \le m$，我们让 $vis _ t$ 减 $1$，并在此之后，若 $vis _ t = 0$，则说明因子 $t$ 之前有而现在没有，将 $cnt$ 减 $1$。

最后若答案被更新过，直接输出答案即可；否则输出 $-1$。

### AC Code

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#define maxm 100000
#define N 100005
using namespace std;

int T, n, m, t, cnt, ans, a[N], vis[N];
vector <int> v[N]; // 数组 v[i] 存的是 i 的所有因数

int main ()
{
    scanf ("%d", &T);
    for (int i = 1; i <= maxm; i ++) // 枚举因数，时间复杂度 O (n + n/2 + n/3 + ... + n/n) ≈ O (n ln n)
    {
        for (int j = i; j <= maxm; j += i) // 遍历这个因数的倍数
        {
            v[j].push_back (i); // 预处理因数
        }
    }
    while (T --)
    {
        scanf ("%d%d", &n, &m), ans = maxm;
        for (int i = 1; i <= n; i ++)
        {
            scanf ("%d", &a[i]);
        }
        sort (a + 1, a + n + 1); // 先排序
        for (int l = 1, r = 0; l <= n; l ++) // 双指针算法
        {
            while (r < n && cnt < m) // 调整右端点 r
            {
                r ++;
                for (int i = 0; i < v[a[r]].size (); i ++) // 遍历 a[r] 的所有因数
                {
                    t = v[a[r]][i];
                    cnt += t <= m && !(vis[t] ++);
                    // 这个语句其实是个缩写，相当于下面语句：
                    // if (t <= m) // 如果因子 t 在 1~m 范围内
                    // {
                    //     if (!vis[t]) // 如果之前没有因子 t 而现在有了
                    //     {
                    //         cnt ++; // 不同的因子个数加 1
                    //     }
                    //     vis[t] ++; // 多了一个因子 t
                    // }
                }
            }
            if (cnt == m) // 如果不同的因子个数等于 m，即 1~m 全部有了
            {
                ans = min (ans, a[r] - a[l]); // 更新答案 ans，用极差 a[r] - a[l] 和 ans 取 min
            }
            for (int i = 0; i < v[a[l]].size (); i ++) // 遍历 a[l] 的所有因数
            {
                t = v[a[l]][i];
                cnt -= t <= m && !(-- vis[t]);
                // 这个语句其实是个缩写，相当于下面语句：
                // if (t <= m) // 如果因子 t 在 1~m 范围内
                // {
                //     vis[t] --; // 少了一个因子 t
                //     if (!vis[t]) // 如果之前有因子 t 而现在没有了
                //     {
                //         cnt --; // 不同的因子个数减 1
                //     }
                // }
            }
        }
        printf ("%d\n", ans < maxm ? ans : -1); // 输出答案（如果 ans < m 即又被更新过则输出 ans，否则输出 -1）
    }
    return 0;
}
```

---

## 作者：Chthologist7507 (赞：4)

### 题意简述

多组询问，一个长为 $n$ 的数列 $a$ 和一个数 $m$，求在数列 $a$ 中删掉几个数，使得从 $1$ 到 $m$ 的所有数组成的集合是数列 $a$ 中所有数的因数组成的集合的子集，求删数后数列 $a$ 的极差。

### 题目分析

预处理 $a_i$ 的因数，然后二分查找极差，对于 check 函数，双指针扫一下，在扫的过程中，把在区间范围内的因数扔到一个桶里，当从 $1$ 到 $m$ 的所有数组成的集合是桶里所有数的集合的子集的时候说明满足要求。

时间复杂度大约是 $O(n\log n)$，但是会有一个比较大的常数，请注意对于桶的清空是否常数过大。

[code](https://codeforces.com/contest/1777/submission/190286283)

---

## 作者：ExplodingKonjac (赞：3)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1777C)**

## 题目分析

把序列排序、去重。然后我们可以看做选出序列的连续一段。因为影响答案的只有 $|\max-\min|$，中间的都加上不影响答案还会更优。

然后就可以进行经典的双指针操作：不断扩展右端点 $r$，然后在满足条件的情况下不断缩小左端点 $l$，同时更新答案。

我们只需要记录一个桶，加入/删除数的时候可以枚举这个数所有因数，动态维护桶中非空的位置个数，如果 $=m$ 就是合法了。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

constexpr int MAXM=1e5,INF=1e9;
int T,n,m,a[100005],bk[100005];
vector<int> d[100005];
int tot;
inline void add(int i,int x=0)
{
	tot-=!!bk[i];
	bk[i]+=x;
	tot+=!!bk[i];
}
int main()
{
	qin>>T;
	for(int i=1;i<=MAXM;i++)
		for(int j=i;j<=MAXM;j+=i)
			d[j].push_back(i);
	while(T--)
	{
		qin>>n>>m;
		for(int i=1;i<=n;i++) qin>>a[i];
		sort(a+1,a+n+1),n=unique(a+1,a+n+1)-a-1;
		int ans=INF;tot=0;
		for(int i=1;i<=m;i++) bk[i]=0;
		for(int i=1,j=1;i<=n;i++)
		{
			for(auto &j: d[a[i]])
				if(j<=m) add(j,1);
			while(j<=i && tot==m)
			{
				ans=min(ans,a[i]-a[j]);
				for(auto &k: d[a[j]])
					if(k<=m) add(k,-1);
				j++;
			}
		}
		qout.writeln(ans==INF?-1:ans);
	}
	return 0;
}
```


---

## 作者：happybob (赞：1)

考虑对 $a$ 序列从小到大排序。

可以发现，一定存在一种最优方案，使得选出的数在 $a$ 排序后的序列中是一段连续区间，且极差最小。因为如果存在一种最优方案选取的不是连续区间，那么将这些数最左端和最右端内全部选取，仍然符合题意，极差不变，但是选择的数是连续区间。

因此将 $a$ 排序后，考虑双指针，因此我们只需要维护一段连续区间是否符合题意。考虑用 $c_i$ 表示 $i$ 作为因子出现在当前区间 $a_l, a_{l+1},\cdots, a_r$ 内的次数。$r$ 指针右移时，$a_r$ 的所有因子的出现次数增加 $1$，$l$ 右移，即 $a_l$ 所有因子出现次数减少 $1$，维护是否 $1 \sim m$ 每个数出现次数 $\geq 1$ 即可，可以 `set` 维护。

$10^5$ 内最多的数的因子个数为 $128$，复杂度可以得到保证。

```cpp
#pragma GCC optimize("-Ofast")
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
using namespace std;

#define ll long long

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t, a[N];
bool del[N];
vector<int> G[N];
set<int> st;
int cnt[N];

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			G[i].clear();
		}
		st.clear();
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++)
		{
			int x = a[i];
			for (long long j = 1; j * j <= x; j++)
			{
				if (1LL * x % j == 0)
				{
					G[i].emplace_back((int)j);
					if (1LL * x / j != j) G[i].emplace_back((int)(1LL * x / j));
				}
			}
		}
		for (int i = 1; i <= m; i++) st.insert(i), cnt[i] = 0;
		int l = 1, r = 0, ans = 1e9;
		bool nowcheck = 0;
		while (l <= n && r <= n)
		{
			if (!nowcheck)
			{
				r++;
				if (r > n) break;
				for (int j : G[r])
				{
					if (j <= m)
					{
						cnt[j]++;
						if (cnt[j] == 1)
						{
							st.erase(j);
						}
					}
				}
				if (st.size() == 0)
				{
					ans = min(ans, a[r] - a[l]);
					nowcheck = 1;
				}
			}
			else
			{
				if (l > n) break;
				for (int j : G[l])
				{
					if (j <= m)
					{
						cnt[j]--;
						if (cnt[j] == 0)
						{
							st.insert(j);
						}
					}
				}
				if (st.size() == 0)
				{
					ans = min(ans, a[r] - a[l + 1]);
					//nowcheck = 1;
				}
				else
				{
					nowcheck = 0;
				}
				l++;
			}
		}
		printf("%d\n", (ans == (int)1e9 ? -1 : ans));
	}
	return 0;
}
```


---

## 作者：sixrc (赞：1)

经典套路题。

先对序列排序。极差最小一般情况先考虑双指针（论据可以见 [P1712 [NOI2016] 区间](https://www.luogu.com.cn/problem/P1712)、[P7514 [省选联考 2021 A/B 卷] 卡牌游戏](https://www.luogu.com.cn/problem/P7514)），具体来说就是固定左端点 $l$，找到最小的 $r$ 满足区间 $[l,r]$ 满足条件。

这个题显然可以这么做。首先固定左端点 $l$。$[l,r]$ 满足题意的充要条件就是 $\forall i \in [1,m], \exists j \in [l,r]$ 满足 $i|a_j$。所以我们拿个桶，$p_i$ 记录 $i$ 的出现次数。用变量 $s$ 记录当前桶中有多少个在 $[1,m]$ 中且不同的数。则 $[l,r]$ 合法的充要条件就转化成了 $s=m$。以右指针 $r$ 的移动为例，对于 $a_r$ 的每个 $[1,m]$ 中的因数 $t$：

- $p_t=0$：则 $s \gets s+1,p_t \gets p_t+1$。

- $p_t>0$：则 $p_t \gets p_t+1$。

左端点移动也类似，只不过从增加变成了删去。

注意把 $r$ 到达 $n$ 但 $s<m$ 的情况判掉。时间复杂度 $O(n \sqrt{a_i})$，1e5 2s 绰绰有余。

---

## 作者：Coffee_zzz (赞：0)

乱搞题。

### 分析

只需要看最大值和最小值，可以把选择的部分看成一条从最小值到最大值的线段，因为中间部分不影响答案所以可以全部取出。

考虑尺取法。记录当前线段每个数的因子出现了多少次，在 $l+1$ 时去掉 $l$ 的所有因子即可。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;
int a[100005],vis[100005];
signed main(){
	int t,n,m,l,r,i,cnt,ans;
	cin>>t;
	for(int temp=0;temp<t;temp++){
		memset(vis,0,sizeof vis);
		cin>>n>>m;
		for(i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);
		ans=1e9,cnt=0,r=0;
		for(l=1;l<=n;l++){
			if(cnt>=m) ans=min(ans,a[r]-a[l]);
			else{
				for(r=r+1;r<=n;r++){
					for(i=1;i*i<=a[r];i++){
						if(a[r]%i==0){
							if(i<=m) if(!vis[i]++) cnt++;
							if(a[r]/i<=m&&i*i!=a[r]) if(!vis[a[r]/i]++) cnt++;
						}
					}
					if(cnt>=m) {ans=min(ans,a[r]-a[l]);break;}
				}
				if(r==n+1) break;
			}
			for(i=1;i*i<=a[l];i++){
				if(a[l]%i==0){
					if(i<=m) if(!--vis[i]) cnt--;
					if(a[l]/i<=m&&i*i!=a[l]) if(!--vis[a[l]/i]) cnt--;
				}
			}
		}
		if(ans==1e9) cout<<"-1\n";
		else cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：eason1021 (赞：0)

# 题目简述
给定一个长度为 $n$ 的正整数序列 $a$，以及一个正整数 $m$。在序列 $a$ 中选出一个长度为子序列（**不是子段**） $b$ ，$\forall i \in [1, m] ,\exists b_j, b_j$ 能整除 $i$。

求所有满足条件的序列 $b$ 的极差（最大值于最小值的差）的最小值；若无满足条件序列 $b$ ，输出 $-1$ 。

## 思路
考虑先排序。

将序列排序之后，如果区间 $a[l, r]$ 满足条件，则 $a[l, r + 1]$ 一定不优；如果区间 $a[l, r]$ 不满足条件，则 $a[l + 1, r]$ 一定不满足条件。

所以可以考虑双指针，每次将右端点向右移一位。考虑删去左端点，若可以整除的数没有减少，则删去左端点。

## 代码
```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
const int N = 1E5 + 5;
int t, n, m; 
int a[N];
int b[N];
int main()
{
	cin >> t;
	while (t--) {
		memset(b, 0, sizeof(b));
		cin >> n >> m;
		for (int i = 1; i <= n ;i++) cin >> a[i];
		sort (a + 1, a + n + 1);
		int l = 1, ans = 0x3F3F3F3F, now = 0;
		for (int r = 1; r <= n; r++) {
			for (int i = 1; i * i <= a[r]; i++) {
				if (a[r] % i == 0) {
					if (!b[i] && i <= m) now++;
					if (i * i != a[r] && !b[a[r] / i] && a[r] / i <= m) now++;
					b[i]++;
					if (i * i != a[r]) b[a[r] / i]++;
				}
			}
			while (l < r) {
				bool ok = 1;
				for (int i = 1; i * i <= a[l]; i++) {
					if (a[l] % i == 0) {
						if (b[i] == 1 && i <= m || b[a[l] / i] == 1 && a[l] / i <= m ) {
							ok = 0;
							break;
						}
					}
				}
				if (!ok) break;
				for (int i = 1; i * i <= a[l]; i++) {
					if (a[l] % i == 0) {
						b[i]--;
						if (i * i != a[l]) b[a[l] / i]--; 
					}
				}
				l++;
			}
			if (now == m) ans = min(a[r] - a[l], ans);
		}
		if (ans == 0x3F3F3F3F) cout << -1;
		else cout << ans;
		cout << '\n';
	}
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1777C 题解



## 思路分析

显然先按 $a_i$ 排序，枚举选择的学生中权值最小的一个，记为 $a_l$，显然此时我们应该选取最小的 $r$ 使得 $a_l\sim a_r$ 中的学生可以组队，并用 $a_r-a_l$ 更新答案。

注意到随着 $l$ 从 $1$ 向 $n$ 递增，$r$ 肯定是单调不降的，因此维护一下双指针的移动，每次移动暴力枚举约数修改即可。

时间复杂度 $\Theta(n\sqrt m)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+1,INF=1e9;
int n,m,a[MAXN],cnt[MAXN],tot=0;
vector <int> factors[MAXN]; 
inline void del(int x) {
	for(int d:factors[x]) {
		if(d>m) break;
		--cnt[d];
		if(!cnt[d]) ++tot;
	}
}
inline void add(int x) {
	for(int d:factors[x]) {
		if(d>m) break;
		if(!cnt[d]) --tot;
		++cnt[d];
	}
}
inline void solve() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) cnt[i]=0;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	tot=m;
	int ans=INF;
	for(int l=1,r=0;l<=n;++l) {
		while(r<n&&tot!=0) add(a[++r]);
		if(tot>0) break;
		ans=min(ans,a[r]-a[l]);
		del(a[l]); 
	}
	printf("%d\n",(ans==INF)?-1:ans);
}
signed main() {
	for(int i=1;i<MAXN;++i) {
		for(int j=i;j<MAXN;j+=i) {
			factors[j].push_back(i);
		}
	}
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

赛时卡了一个半小时的题，寄之。

首先把数组排序，这显然不影响答案。

然后发现选取的数一定要在原数组内编号连续最优，这并不难理解，因为确定最大值和最小值后，选取所有中间的数一定不会更劣。

观察到答案具有单调性，所以可以二分或者双指针实现。这里用双指针写法。当然二分也是可以通过的。

对于每个 $ l $ 不断暴力扩展右端点 $ r $ 直到区间合法，如果 $ r $ 挪动到最右端仍不合法则停止流程，否则将当前答案与 $ a_r-a_l $ 取较小值。

因为每次操作 $ l,r $ 都是单调递增的，于是总移动指针次数为 $ \mathcal{O}(n) $。然后对于挪动指针这个操作，首先要求出单个数的所有因子，这步是 $ \mathcal{O}(\sqrt{a_i}) $ 的。但是如果每次暴力判断区间是否合法显然是过不去的，考虑类似莫队记录区间颜色数的思想，分两种情况讨论：区间扩大和区间缩小。以下忽略所有大于 $ m $ 的因子，因为对答案显然没有贡献。

考虑维护一个 $ now $ 表示当前区间内不同因子个数。

区间扩大分两种情况讨论：对于当前因子 $ x $ 如果出现次数为 $ 0 $，则 $ now \leftarrow now+1 $ 表示区间出现了一种新因子，然后出现次数加 $ 1 $。

区间缩小同样分为两种情况讨论：如果出现次数为 $ 1 $ 说明更新后这个因子不再出现在这个区间，于是 $ now \leftarrow now-1 $ 表示这个因子不再出现在这个区间，然后出现次数减 $ 1 $。

于是判断当前区间是否合法只需要判断 $ now=m $ 是否为真即可。

于是总时间复杂度 $ \mathcal{O}(n\sqrt{\max a_i}) $，可以通过。为了方便，以下代码中将区间扩大和区间缩小实现在一个函数内。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read() 
{
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') 
    {
		if (ch=='-') 
        f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') 
    {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n) 
{
	int f[2000020],tmp[2000020];
	for (int i=1;i<=n;i++)
	f[i]=i;
	do 
    {
		for (int i=n+1;i<=2*n;i++)
		f[i]=f[2*n-i+1];
		for (int i=1;i<=2*n;i++)
		tmp[i]=f[i];
		for (int i=1;i<=2*n;i++)
		for (int j=i+1;j<=2*n;j++)
		if(tmp[i]>tmp[j])//add something here.
		ans++;
	}
	while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
const int mod=1e9+7;
int n,m,now=0;
int cnt[2000020];
vector<int> ok(int n) 
{
	vector<int>d;
	if(n==1) 
    {
		d.push_back(1);
		return d;
	}
	d.push_back(1),d.push_back(n);
	for (int i=2;i<sqrt(n);i++)
	if(n%i==0)
	d.push_back(i),d.push_back(n/i);
	int rt=sqrt(n);
	if(rt*rt==n)
	d.push_back(rt);
	return d;
}
bool check() 
{
	return now==m;
}
void add(int r,int op) 
{
	if(op==1) 
    {
		vector<int>d=ok(a[r]);
		for (auto x:d)
		if(x>m)
		continue; 
        else if(!cnt[x])
		cnt[x]++,now++; 
        else
		cnt[x]++;
	} 
    else 
    {
		vector<int>d=ok(a[r]);
		for (auto x:d)
		if(x>m)
		continue; 
        else if(cnt[x]==1)
		cnt[x]=0,now--; 
        else
		cnt[x]--;
	}
}
void test(int a,int b) 
{
	cout<<a<<' '<<b<<'\n';
}
signed main() 
{
	int T;
	cin>>T;
	while(T--) 
    {
		cin>>n>>m;
		for (int i=1;i<=m;i++)
		    cnt[i]=0;
		now=0;
		for (int i=1;i<=n;i++)
		    cin>>a[i];
		sort(a+1,a+n+1);
		int l=1,r=0,ans=2e9;
		now=0;
		while(l<=n) 
        {
			if(l>n)
				break;
			while(r<=n&&!check())
				r++,add(r,1);
			if(r>n)
				break;
			//test(l,r);
			if(check())
				ans=min(ans,a[r]-a[l]);
			add(l,-1);
			l++;
		}
		if(ans>1e9)
		    cout<<-1<<'\n'; 
        else
		    cout<<ans<<'\n';
	}
}
```



---

