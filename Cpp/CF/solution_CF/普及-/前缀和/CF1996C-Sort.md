# Sort

## 题目描述

You are given two strings $ a $ and $ b $ of length $ n $ . Then, you are (forced against your will) to answer $ q $ queries.

For each query, you are given a range bounded by $ l $ and $ r $ . In one operation, you can choose an integer $ i $ ( $ l \leq i \leq r $ ) and set $ a_i = x $ where $ x $ is any character you desire. Output the minimum number of operations you must perform such that $ \texttt{sorted(a[l..r])} = \texttt{sorted(b[l..r])} $ . The operations you perform on one query does not affect other queries.

For an arbitrary string $ c $ , $ \texttt{sorted(c[l..r])} $ denotes the substring consisting of characters $ c_l, c_{l+1}, ... , c_r $ sorted in lexicographical order.

## 说明/提示

For the first query, $ \texttt{sorted(a[1..5])} = $ abcde and $ \texttt{sorted(b[1..5])} = $ abcde, so no operations are necessary.

For the second query, you need to set $ a_1 =  $ e. Then, $ \texttt{sorted(a[1..4])} = \texttt{sorted(b[1..4])} =  $ bcde.

## 样例 #1

### 输入

```
3
5 3
abcde
edcba
1 5
1 4
3 3
4 2
zzde
azbe
1 3
1 4
6 3
uwuwuw
wuwuwu
2 4
1 3
1 6```

### 输出

```
0
1
0
2
2
1
1
0```

# 题解

## 作者：PineappleSummer (赞：3)

[CF1996C Sort](https://codeforces.com/problemset/problem/1996/C)

简单前缀和。

设 $cnt1_{i,j}$ 为字符串 $a$ 种前 $i$ 个字符里 $j$ 字符的数量，$cnt2_{i,j}$ 为字符串 $b$ 种前 $i$ 个字符里 $j$ 字符的数量。最初可以把 $cnt1$ 与 $cnt2$ 预处理出来。

要使得区间内每个字符的数目相等，需要先统计差异的个数。

对于每次询问，依次枚举每个字符，设 $x$ 为 $cnt1_{r,j}-cnt1_{l-1,j}$，$y$ 为 $cnt2_{r,j}-cnt2_{l-1,j}$，使 $ans$ 累加上 $\left|x-y\right|$。最后答案即为 $\dfrac{ans}{2}$。

时间复杂度 $\mathcal O(26n)$。

有个同学说他写的莫队，$\mathcal O(n\sqrt{n})$ 的复杂度，很牛，卡不掉。
```cpp
void solve () {
	scanf ("%lld %lld", &n, &q);
	scanf ("%s", a + 1);
	scanf ("%s", b + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 26; j++)
			cnt1[i][j] = cnt1[i - 1][j] + (a[i] == 'a' + j - 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 26; j++)
			cnt2[i][j] = cnt2[i - 1][j] + (b[i] == 'a' + j - 1);
	while (q--) {
		int l, r, res = 0;
		scanf ("%lld %lld", &l, &r);
		for (int i = 1; i <= 26; i++) {
			int x = cnt1[r][i] - cnt1[l - 1][i];
			int y = cnt2[r][i] - cnt2[l - 1][i];
			if (x > y) res += x - y; // 统计答案
		}
		printf ("%lld\n", res);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 26; j++)
			cnt1[i][j] = cnt2[i][j] = 0;
}
```

---

## 作者：Manki23333333 (赞：1)

#### 题解

显然的一个结论，就是 $a$ 排序并且 $b$ 排序相等的充要条件是 $a$ 所有字符的出现次数等于 $b$ 所有字符的出现次数。

#### 结论的证明

如果$a$ 排序并且 $b$ 排序并不相等，不妨设 $a$ 的字典序大于 $b$，此时结论成立。

如果$a$ 所有字符的出现次数不等于 $b$ 所有字符的出现次数，那么肯定会有一个字符出现的次数大于另一个，此时结论也成立。

#### 解法详述

设 $fa_{i, j}$ 为对于 $a$ 的 $[1, i]$ 区间，$j$ 字符出现的次数（类似于前缀和），对于 $b$ 构造一个同样的 $fb$。询问时枚举 $j$。

#### 代码

```
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e5 + 5;
 
int a [N], b [N], fa [N] [35], fb [N] [35], n, q;
char x;
 
void init_sum () {
	for (int i = 1 ; i <= n ; i ++) {
		for (int j = 0 ; j < 26 ; j ++) {
			fa [i] [j] = fa [i - 1] [j] + (a [i] == j);
			fb [i] [j] = fb [i - 1] [j] + (b [i] == j);
		}
	}
}
 
int main () {
//	freopen ("temp.out", "w", stdout);
	
	int T;
	
	cin >> T;
	
	while (T --) {
		cin >> n >> q;
		
		for (int i = 1 ; i <= n ; i ++) {
			cin >> x;
			a [i] = x - 'a';
		}
		
		for (int i = 1 ; i <= n ; i ++) {
			cin >> x;
			b [i] = x - 'a';
		}
		
		init_sum ();
		
		while (q --) {
			int l, r;
			cin >> l >> r;
			
			int ans = 0;
			for (int j = 0 ; j < 26 ; j ++) {
				ans += abs ((fa [r] [j] - fa [l - 1] [j]) - (fb [r] [j] - fb [l - 1] [j]));
			}
			
			cout << ans / 2 << endl; // 这个写法要除以二，因为答案会贡献两次
		}
	}
	return 0;
}
```

---

## 作者：PigNotFound (赞：0)

看到这道题，奇奇怪怪的询问，可以离线，很容易想到莫队（虽然正解是前缀和）。
首先，每个询问等价于这样的形式:

定义 $cnt1_i$ 表示在 $a_{[l\cdots r]}$ 中 $i$ 字符出现的次数，$cnt2_i$ 表示在 $b_{[l\cdots r]}$ 中 $i$ 字符出现的次数。求出 $\frac{\sum_{i=A}^{Z}{\lvert cnt1_i-cnt2_i \rvert}}{2}$。

所以，用莫队维护 $cnt1$ 和 $cnt2$，时间复杂度 $O(n \sqrt{n})$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Pig = 2e5 + 10;
int belong[Pig];
struct query{
    int l, r, id;
    bool operator<(query a) {
        if (belong[l] == belong[a.l])
            return (belong[a.l] & 1) ? r > a.r : a.r > r;
        return belong[l] < belong[a.l];
    }
};
int cnt1[30], cnt2[30], ans[Pig];
string a, b;
void add(int n) {
    cnt1[a[n - 1] - 'a']++;
    cnt2[b[n - 1] - 'a']++;
}
void del(int n) {
    cnt1[a[n - 1] - 'a']--;
    cnt2[b[n - 1] - 'a']--;
}
void process(vector<query> q) {
    sort(q.begin(), q.end());
    int l = 1, r = 0;
    memset(cnt1, 0, sizeof(cnt1));
    memset(cnt2, 0, sizeof(cnt2));
    for (auto v : q) {
        while (l < v.l) del(l++);
        while (r < v.r) add(++r);
        while (l > v.l) add(--l);
        while (r > v.r) del(r--);
        int cur = 0;
        for (int i = 0; i < 26; i++)
            cur += abs(cnt1[i] - cnt2[i]);
        ans[v.id] = (cur >> 1);
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    vector<int> nums;
    for (int n, q; t; t--) {
        cin >> n >> q;
        cin >> a >> b;
        int len = sqrt(n), cur = 1;
        for (int i = 1; i <= n; i++) {
            if (i == cur * len)
                cur++;
            belong[i] = cur;
        }
        vector<query> qu;
        for (int l, r, i = 0; i < q; i++) {
            cin >> l >> r;
            qu.push_back({l, r, i});
        }
        process(qu);
        for (int i = 0; i < q; i++)
            cout << ans[i] << '\n';
    }
    return 0;
}
```

---

## 作者：GoldenCreeper (赞：0)

如果 $\mathrm{sort}(a[l..r])=\mathrm{sort}(b[l..r])$， 那么说明 $a[l..r]$ 中每个字母的个数和  $b[l..r]$ 相等，所以想让 $\mathrm{sort}(a[l..r])=\mathrm{sort}(b[l..r])$ 的操作数，也就是每个字母在 $a[l..r]$ 与 $b[l..r]$ 中的差的和。

使用前缀和来快速的求 $a[l..r]$ 与 $b[l..r]$ 中每个字母的个数，时间复杂度 $\Theta(n)$，[AClink](https://codeforces.com/contest/1996/submission/272783866)。

---

## 作者：Heldivis (赞：0)

## CF1996C

由于询问的两个字符串经过排序，所以每次询问的答案只与这两个区间内各个字符的数量有关，可以使用前缀和优化计算。

考虑两个字符串，尝试让第二个字符串变为第一个，每个相差的字符都需要一次变化，则需要各个字符的差量的绝对值之和个字符发生变化。又因为每次操作可以让一个数量较多的字符变为一个数量较少的字符，可以改变两个字符，还要把差量和除以 $2$ 才是最终答案。

代码：

```cpp
int ToInt(char c) { return c - 'a'; }

void Main() {
  n = read(), q = read();
  scanf("%s", a + 1);
  scanf("%s", b + 1);
  for (int i = 1; i <= n; i++) a[i] = ToInt(a[i]), b[i] = ToInt(b[i]);
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < 26; j++) {
      sa[i][j] = sa[i - 1][j] + (a[i] == j);
      sb[i][j] = sb[i - 1][j] + (b[i] == j);
    }
  while (q--) {
    int l = read() - 1, r = read(), sum = 0;
    for (int i = 0; i < 26; i++)
      sum += abs((sa[r][i] - sa[l][i]) - (sb[r][i] - sb[l][i]));
    printf("%d\n", sum / 2);
  }
}
```

---

## 作者：B612Dusk (赞：0)

# CF1996C Sort

题目大意就是给我两个字符串 $a,b$ ，每次查询一段区间，问我至少修改多少个字符 $a$ 可以使 $a,b$ 序列在该区间 $l \rightarrow r$ 区间内按照字典序 $sort$ 一遍后相同

看到这道题我们第一反应是前缀和，这当然是正解，~~但是这样太难想我们考虑一个直观的~~，看到这道题我们容易想到 HH的项链 那道题，这个题可以说是他的弱化版。我们考虑所谓的 $sort$ 本质就是 $26$ 种字母个数都相同，那么我们可以考虑使用**莫队**，然后每达到一个询问查询一次当前的 $26$ 个字母个数分别相差多少，但是记住我们一次修改会减少 $2$ 个不同的字母，比如对于第 $i$ 位，$a_i=a$，$b_i=z$ ，那么在 $cnt_a$ 和 $cnt_z$ 同时贡献 $1$，但是我们只需要修改一次，所以答案需要除以2。

最后时间复杂度 $O(n\sqrt{n} \times 26)$ 但是加上常数优化并且很难卡满所以稳稳过掉

## Code
```c++
#include <bits/stdc++.h>
#define int long long
 
const int N = 3e5 + 10;
 
using namespace std;
 
inline int read()
{
	int t;
	cin >> t;
	return t;
}
 
int T, n, Q, len, ans[N];
int cnta[30], cntb[30], area[N];
char a[N], b[N];
 
struct quest{
	int l, r, id;
}que[N];
 
bool cmp(quest a, quest b)
{
	if(area[a.l] ^ area[b.l])	
		return a.l < b.l;
	else if(area[a.l] & 1)	return a.r < b.r;
	else	return a.r > b.r;
}
 
inline void add(int x)
{
	++ cnta[a[x] - 'a'];
	++ cntb[b[x] - 'a'];
}
 
inline void del(int x)
{
	-- cnta[a[x] - 'a'];
	-- cntb[b[x] - 'a'];
}
 
inline int ask()
{
	int ans = 0;
	for(int i = 0;i < 26;i = -~i)
		ans += abs(cnta[i] - cntb[i]);
	return ans;
}
 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
 
	T = read();
	while(T --)
	{
		n = read() , Q = read();
		len = sqrt(n);
		
		for(int i = 1;i <= n;i = -~i)	cin >> a[i];
		for(int i = 1;i <= n;i = -~i)	cin >> b[i];
		for(int i = 1;i <= n;i = -~i)	area[i] = (i - 1) / len + 1;
		
		for(int i = 1;i <= Q;i = -~i)
			que[i].l = read(), que[i].r = read(), que[i].id = i;
		
		sort(que + 1, que + Q + 1, cmp);
		
		int l = que[1].l, r = que[1].r;
		for(int i = l;i <= r;i = -~i)	add(i);
		ans[que[1].id] = ask();
		
		for(int i = 2;i <= Q;i = -~i)
		{
			while(l < que[i].l)		del(l ++);
			while(l > que[i].l)		add(-- l);
			while(r < que[i].r)		add(++ r);
			while(r > que[i].r)		del(r --);
			ans[que[i].id] = ask();
		}
		
		for(int i = 1;i <= Q;i = -~i)
			cout << ans[i] / 2 << endl;
			
		for(int i = 0;i < 26;i = -~i)
			cnta[i] = cntb[i] = 0;
	} // 注意清空，多测
 
	return 0;
}
```

---

## 作者：TPJX (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1996C)
### 思路
本题目要求将字符串 $a$ 的某个子串通过最少的修改次数变为字符串 $b$ 的相应子串的排序结果相同。关键在于利用前缀和数组技巧和字符频率统计来快速计算区间内字符出现次数的差异，进而推算出最少的修改次数。

首先，为了快速回答多个查询，需要预处理两个字符串中每个字符出现的次数。使用一个三维数组 `freq[2][MAXN][26]`，其中 `freq[0]` 用于字符串 $a$，`freq[1]` 用于字符串 $b$。这个数组的每一维表示到当前位置为止，每个字母（$a$ 到 $z$）的出现次数。

对于每一个查询，需要确定在子串 $l$ 到 $r$ 范围内，两个字符串中每个字符的出现次数。利用前缀和的性质，可以 $O(1)$ 时间内得到任意区间的字符频率。即对于字符 $i$，$a$ 中的数量为 `freq[0][r][i] - freq[0][l-1][i]`，$b$ 中的数量为 `freq[1][r][i] - freq[1][l-1][i]`。

计算完两个字符串在查询区间内各个字符的数量后，接下来计算将 $\texttt{a[l..r]}$ 变为 $\texttt{b[l..r]}$ 所需的最小修改次数。每一个字符的差的绝对值累加起来，除以 $2$ 即得到答案。这是因为每一次操作可以修正两个不匹配的字符。（一个字符的增加和一个字符的减少）

时间复杂度方面，预处理字符频率是 $O(n)$ 的，对于每个查询，我们通过已经计算好的频率数组可以在 $O(1)$ 时间内得到任意区间的字符频率。因此，对于每个查询的复杂度为 $O(26)$，即 $O(1)$。因此，整体复杂度主要由预处理的 $O(n)$ 和所有查询的 $O(q)$ 决定，每个测试用例为 $O(n + q)$。

### C++ 代码

```cpp
#include <iostream>
using namespace std;

const int MAXN = 200010;
int freq[2][MAXN][26]; 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, q; string a, b;
        cin >> n >> q >> a >> b;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 26; ++j) {
                freq[0][i][j] = freq[0][i - 1][j];
                freq[1][i][j] = freq[1][i - 1][j];
            }
            freq[0][i][a[i - 1] - 'a']++;
            freq[1][i][b[i - 1] - 'a']++;
        }
        while (q--) {
            int l, r;
            cin >> l >> r;
            int ops = 0;
            for (int i = 0; i < 26; ++i) {
                int cnta = freq[0][r][i] - freq[0][l - 1][i];
                int cntb = freq[1][r][i] - freq[1][l - 1][i];
                ops += abs(cnta - cntb);
            }
            cout << ops / 2 << endl;
        }
    }
    return 0;
}
```

---

