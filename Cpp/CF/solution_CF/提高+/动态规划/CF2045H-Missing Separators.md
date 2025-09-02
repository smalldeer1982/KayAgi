# Missing Separators

## 题目描述

你有一个字典，其中的单词均已按照字母顺序排好，并且每个单词都是独特的，由大写英文字母构成。

现在你想打印这个字典，但不幸的是，打印系统出现了故障，所有单词都相连在一起打印，没有任何间隔符。因此，你得到一个字符串 $S$，它是字典中所有单词按顺序连接构成的。

你的任务是从字符串 $S$ 中将原来的字典单词分离出来。注意，分离出来的单词也必须是唯一的，并且按字母顺序排列。你需要尽可能多地复原字典中的单词数量。如果存在多个分离方案能够达到单词数量的最大值，你可以选择任意一种方案。

## 样例 #1

### 输入

```
ABACUS```

### 输出

```
4
A
BA
C
US```

## 样例 #2

### 输入

```
AAAAAA```

### 输出

```
3
A
AA
AAA```

## 样例 #3

### 输入

```
EDCBA```

### 输出

```
1
EDCBA```

# 题解

## 作者：FiraCode (赞：3)

考虑说直接贪心不太能做，所以考虑 DP。

考虑说我们选后缀比前缀容易，所以我们倒着 DP。

考虑说我们如果设 $f_{i,j}$ 表示分了后 $i$ 个 $j$ 段是否可行，我们发现 $i,j$ 从 $f_{k,j - 1}$ 转移，但我们需要枚举 $i,j,k$ 还有 $k$ 最后一段的长度，感觉不太好优化。

考虑到原来的 DP 主要关心最后一段多长，所以我们考虑设 $f_{i, j}$ 表示 $[i, n]$ 这段后缀，最后一段为 $[i,j]$ 最长的段数是多少。

然后我们枚举 $i, j$，然后考虑用 SA 求出来 $[i, n]$ 和 $[j + 1, n]$ 的最长公共前缀设为 $s$，那么就看如果 $[i,i + \min(lcp, j - i + 1)]$ 这段是否小于 $[j + 1, j + 1 + \min(lcp, j - i + 1)]$，如果是的话，那么 $f_{i,j}$ 就是 $\max_{k=j + 1 + \min(lcp, j - i + 1)} ^ {n} f_{j + 1, k}$，然后发现是后缀 $\max$，于是再开一个数组维护即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 10010;

int n, m, p;
char s[5010];
pair<int, int> f[5010][5010];
pair<int, int> g[5010][5010];
int st[16][N], log_2[N];
int sa[N], rk[N], ork[N], id[N], cnt[N];

int queryM(int l, int r) {
	int L = log_2[r - l + 1];
	return min(st[L][l], st[L][r - (1 << L) + 1]);
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);

	m = 255;
	for (int i = 1; i <= n; ++i) cnt[rk[i] = s[i]]++;
	for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

	for (int w = 1; ; w <<= 1, m = p) {
		int cc = 0;
		for (int i = n - w + 1; i <= n; ++i) id[++cc] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > w) id[++cc] = sa[i] - w;

		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; ++i) cnt[rk[i]]++;
		for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];

		memcpy(ork, rk, sizeof(ork));
		p = 0;
		for (int i = 1; i <= n; ++i)
			if (ork[sa[i]] == ork[sa[i - 1]] && ork[sa[i] + w] == ork[sa[i - 1] + w])
				rk[sa[i]] = p;
			else
				rk[sa[i]] = ++p;

		if (p == n) break;
	}
	
	for (int i = 1, k = 1; i <= n; ++i) {
		if (!rk[i]) continue;
		if (k) --k;
		// cout << sa[rk[i] - 1] << ' ' << i << ' ' << rk[i] << ' ' << sa[rk[i]] << ' ' << sa[rk[i] - 1] << ' ' << sa[i] << endl;
		while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;

		st[0][rk[i]] = k;
	}

	for (int i = 1; i <= 15; ++i)
		for (int j = 1; j <= n; ++j)
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
	log_2[1] = 0;
	for (int i = 2; i <= n; ++i) log_2[i] = log_2[i >> 1] + 1;

	for (int i = n; i >= 1; --i) {
		for (int j = i; j <= n; ++j) {
			if (j == n) {
				f[i][j] = {1, n + 1};
				break;
			}

			int l = rk[i], r = rk[j + 1];
			if (l > r) swap(l, r);
			int lcp = min(queryM(l + 1, r), j - i + 1);

			if (lcp == n - j) continue;

			if (lcp >= j - i + 1) {
				if (g[j + 1][j + j - i + 2].first + 1 > f[i][j].first)
					f[i][j] = {g[j + 1][j + j - i + 2].first + 1, g[j + 1][j + j - i + 2].second};
			} else {
				if (s[i + lcp] < s[j + lcp + 1]) {
					if (g[j + 1][j + lcp + 1].first + 1 > f[i][j].first)
						f[i][j] = {g[j + 1][j + lcp + 1].first + 1, g[j + 1][j + lcp + 1].second};
				}
			}

			// cout << i << ' ' << j << ' ' << lcp << ' ' << f[i][j].first << "----" << ' ' << j + lcp + 1 << ' ' << g[j + 1][j + lcp + 1].first << endl;
		}

		for (int j = n; j >= i; --j) {
			g[i][j] = max(g[i][j + 1], {f[i][j].first, j});
		}
	}

	int ans = 0, id = 0;
	for (int i = 1; i <= n; ++i) {
		if (f[1][i].first > ans) {
			ans = f[1][i].first;
			id = i;
		}
	}

	printf("%d\n", ans);
	int l = 1;
	while (id <= n) {
		for (int i = l; i <= id; ++i) putchar(s[i]);
		putchar('\n');
		int tid = id;
		id = f[l][id].second;
		l = tid + 1;
	}

	return 0;
}
```

---

## 作者：KaruAWA (赞：1)

本篇题解主要是想补充说明一下为什么要从后往前考虑，毕竟作者一开始在从前往后的状态设计中卡了很久。

首先我们需要明确，贪心地能分割就分割是不行的，随便构造一个 `AZBC` 就卡掉了。因此，运用了这个结论的动态规划都不行。那么如果我们从前往后考虑，可行的 dp 状态只剩下 $dp_{i,j}$ 表示前 $i$ 个分了 $j$ 组且末尾字符串字典序最小的末尾字符串开头的位置，以及 $dp_{i,j}$ 表示 $[1,j]$ 的前缀已经分割好，并且末尾字符串为 $[i,j]$ 的最大分割次数（作者只想到这两种转移方程了/kk，如果有其他可做方程欢迎补充）。

先考虑前者，由于在想要 $i$ 成为新字符串开头的情况下，在转移的时候并不需要强制让 $a_i >a_{dp_{i-1,j-1}}$，而是可以等于，之后再不断添加字符串使得以 $i$ 开头的字符串比前一个字符串字典序大。也就是说只要满足第 $j -1$ 个字符串比第 $j-2$ 个字符串字典序大，并且 $a_i \ge a_{dp_{i-1, j-1}}$ 时都是可以转移使得 $i$ 为第 $j$ 个字符串开头的。但是这样又假掉了，第一个样例 `ABACUS` 就会 hack 我们，我们在前缀为 $3$ 时会贪心地分割为 `AB A`，这会使得后面的 `C` 不得不接在第二个字符串后面。因此这种转移是不行的。

再考虑后者，若 $dp_{i,j}$ 要从 $dp_{k , i -1}$ 转移过来，需要满足 $[k,i-1]$ 这一段的字典序比 $[i,j]$ 这一段的字典序小，看起来很对啊，但是这样是 $O(n^3)$ 的，并且由于字典序是从前往后比较的，能转移过来的 $k$ 也是非连续的，因此很难优化了。

因此，考虑到第二种做法是因为字典序的性质导致 $k$ 非连续而不优的，我们就考虑从后往前转移，即 $dp_{i,j}$ 表示已经分割好了 $[i,n]$ 这一段后缀，并且 $[i,j]$ 为第一个字符串的最大分割数量。这样做的好处是满足 $dp_{i,j}$ 可以从 $dp_{j+1,k}$ 转移过来的 $k$ 是一段连续的后续，因为仅仅只在末尾添加字符只会使得字典序不降，因此只要我们找到第一个满足条件的 $k$，维护一个后缀最大值即可。

如何找到第一个满足条件的 $k$？我们不难发现可能满足条件的 $k$ 一定是 $[i,n]$ 和 $[j+1, n]$ 这两段后缀的最长公共前缀 $+1$ 的位置，并且要满足它在以 $i$ 为开头的后缀中的字典序比在以 $j+1$ 为开头的后缀中的字典序小。后缀和 lcp？这我熟，直接 SA 即可。但是考虑到本题的数据范围以及后面动态规划的时间复杂度瓶颈，$O(n^2)$ 的转移 lcp 也完全能过，但 $O(n^2\log n)$ 的二分哈希好像就会被卡了。

在转移时还有一些细节，比如第一个满足条件的 $k$ 超出了 $[i,j]$ 这一段字符串，那我们只需要满足 $[j+1, k]$ 的长度严格大于 $[i,j]$ 的长度即可。

代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 1;
int n, a[N];
int lcp[N][N];
int dp[N][N], f[N][N];
int maxi[N][N], p[N][N];

void print(int x, int y) {
    if(x >= n + 1 || y >= n + 1)
        return;
    for(int i = x; i <= y; ++i) {
        char c = a[i] + 'A' - 1;
        cout << c;
    }
    cout << "\n";
    print(y + 1, f[x][y]);
}

int main() {
    ios::sync_with_stdio(false);
    string s;
    cin >> s;
    n = s.size();
    for(int i = 1; i <= n; ++i) {
        a[i] = s[i - 1] - 'A' + 1;
        lcp[i][i] = 1;
    }
    for(int i = n; i >= 1; --i) {
        for(int j = i + 1; j <= n; ++j) {
            if(a[i] == a[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;
        }
    }
    for(int i = 1; i <= n; ++i) {
        dp[i][n] = maxi[i][n] = 1;
        p[i][n] = n;
        f[i][n] = n + 1;
        for(int j = n; j >= i; --j) {
            maxi[i][j] = 1;
            p[i][n] = n;
        }
    }

    for(int i = n - 1; i >= 1; --i) {
        for(int j = n; j >= i; --j) {
            int tmp = lcp[i][j + 1] + 1;
            if((i + tmp - 1 <= j && j + tmp <= n && a[i + tmp - 1] < a[j + tmp])) {
                dp[i][j] = maxi[j + 1][j + tmp] + 1;
                f[i][j] = p[j + 1][j + tmp];
            }
            else if(i + tmp - 1 > j && 2 * j - i + 2 <= n) {
                dp[i][j] = maxi[j + 1][2 * j - i + 2] + 1;
                f[i][j] = p[j + 1][2 * j - i + 2];
            }

            if(dp[i][j] > maxi[i][j + 1]) {
                maxi[i][j] = dp[i][j];
                p[i][j] = j;
            }
            else {
                maxi[i][j] = maxi[i][j + 1];
                p[i][j] = p[i][j + 1];
            }
        }
    }
    int ansi = 0, y = 0;
    for(int i = 1; i <= n; ++i) {
        if(dp[1][i] > ansi) {
            ansi = dp[1][i];
            y = i;
        }
    }
    cout << ansi << "\n";
    print(1, y);
    return 0;
}
~~~

---

## 作者：lfxxx (赞：0)

不妨从后往前考虑，设计状态 $dp_{i,j}$ 表示 $S[i,n]$ 满足最后一段划分为 $[i,j]$ 的前提下最多能划分为多少段。

那么 $dp_{i,j}$ 能从 $dp_{j+1,k}$ 转移过来当且仅当 $S[i,j] > S[j+1,k]$。

注意到转移到过程中你必须枚举 $i,j$，于是转移过程中唯一可以优化的一步就是枚举 $k$。

在枚举 $k$ 的过程中，你发现 $S[j+1,k]$ 在不断变大，因此满足 $S[i,j] > S[j+1,k]$ 的 $k$ 是一段后缀，具体而言可以通过求解 $S[i,n]$ 与 $S[j+1,n]$ 的最长公共前缀求出，这一步可以 $O(n^2)$ 暴力做，dp 的过程用后缀 max 优化一下也做到了 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e3+114;
pair<int,pair<int,int> > dp[maxn][maxn];
pair<int,pair<int,int> > suf[maxn][maxn];
string S;
char s[maxn];
int lcp[maxn][maxn];
int n;
pair<int,pair<int,int> > upd(pair<int,pair<int,int> > x){
    x.first++;
    return x;
}
pair<int,pair<int,int> > chan(pair<int,pair<int,int> > x,pair<int,int> now){
    x.second=now;
    return x;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>S;
    n=S.size();
    for(int i=1;i<=n;i++) s[i]=S[i-1];
    for(int i=n;i>=1;i--){
        for(int j=n;j>=1;j--) lcp[i][j]=(s[i]==s[j])*(lcp[i+1][j+1]+1);
    }
    for(int i=n;i>=1;i--){
        suf[i][n+1]=dp[i][n+1]=make_pair(0,make_pair(n+1,n+1));
        for(int j=n;j>=i+1;j--){
            dp[i][j]=make_pair(0,make_pair(n+1,n+1));
            if(lcp[i][j]>=j-i&&j+j-i+1<=n+1) dp[i][j]=max(dp[i][j],upd(suf[j][j+j-i+1]));
            else if(s[i+lcp[i][j]]<s[j+lcp[i][j]]&&j+lcp[i][j]+1<=n+1) dp[i][j]=max(dp[i][j],upd(suf[j][j+lcp[i][j]+1]));
            //cout<<i<<' '<<j<<' '<<suf[j][j+lcp[i][j]+1].first<<' '<<dp[i][j].first<<'\n';
            suf[i][j]=max(suf[i][j+1],chan(dp[i][j],make_pair(i,j)));
            //cout<<i<<' '<<j<<' '<<suf[i][j].first<<'\n';
        }
    }
    cout<<suf[1][2].first+1<<'\n';
    if(suf[1][2].first+1==1){
        cout<<S<<'\n';
        return 0;
    }
    pair<int,int> u=suf[1][2].second;
    int lst=0;
    while(u.first<=n){
        for(int i=u.first;i<u.second;i++) cout<<s[i];
        cout<<'\n';
        lst=u.second;
        u=dp[u.first][u.second].second;
    }
    for(int i=lst;i<=n;i++) cout<<s[i];
    return 0;
}
```

---

