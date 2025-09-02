# [USACO23OPEN] Pareidolia G

## 题目描述

### 题目背景

Pareidolia 是一种现象，指的是人们倾向于在并不真正存在的地方看到熟悉的图案——例如在云中看到一张脸。可以想象，由于农夫 John 经常与奶牛接触，他常常在日常物品中看到与奶牛相关的图案。例如，如果他看到字符串 "bqessiyexbesszieb"，农夫 John 的眼睛会忽略其中的一些字母，而他看到的只是 "bessiexbessieb"——一个包含两个连续子串等于 "bessie" 的字符串。


给定一个长度不超过 $2 \cdot 10^5$ 的字符串，且仅由字符 a-z 组成，其中每个字符都有一个相关的删除成本。计算通过删除零个或多个字符后，能够形成的等于 "bessie" 的连续子串的最大数量，以及为了实现这一目标所需删除字符的最小总成本。

## 说明/提示

对于第一个样例，通过删除位置 4 的 's'，我们可以使整个字符串变为 "bessie"。位置 4 的字符成本为 $4$，因此我们的答案是成本 $4$ 得到 $1$ 个 "bessie"，这是我们可以做到的最佳结果。

对于第二个样例，通过删除位置 5-7 的 "con"，我们可以使字符串变为 "bebessiete"，其中包含中间的 "bessie"。位置 5-7 的字符成本为 $5 + 7 + 9 = 21$，因此我们的答案是成本 $21$ 得到 $1$ 个 "bessie"，这是我们可以做到的最佳结果。

对于第三个样例，通过删除位置 4-10 的 "giraffe"，我们可以使字符串变为 "bessiebessibessie"，其中包含开头和结尾的 "bessie"。"giraffe" 有 7 个字符，且所有字符的成本均为 $1$，因此我们的答案是成本 $7$ 得到 $2$ 个 "bessie"，这是我们可以做到的最佳结果。此样例满足第二个子任务的约束条件。

- 输入 4-5：$N \le 2000$。
- 输入 6-8：所有成本均为 $1$。
- 输入 9-17：没有额外限制。

## 样例 #1

### 输入

```
besssie
1 1 5 4 6 1 1
```

### 输出

```
1
4
```

## 样例 #2

### 输入

```
bebesconsiete
6 5 2 3 6 5 7 9 8 1 4 5 1
```

### 输出

```
1
21
```

## 样例 #3

### 输入

```
besgiraffesiebessibessie
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出

```
2
7
```

# 题解

## 作者：lnwhl (赞：7)

设字符串的长度为 $n$。

dp，$f[i][j][k]$ 表示 $s[1\dots i]$ 通过删去若干字符，能够凑出 $j$ 个完整的 `bessie`，最后一个（不完整的） `bessie` 已经凑齐了前 $k$ 位的最小删除代价和。答案即为最大的 $j$ 和对应的 $f[n][j][0]$。

考虑如何转移：
1. 删除 $s[i]$，$f[i][j][k]=f[i-1][j][k]+c[i]$。
2. 如果 $s[i]$ 等于 `bessie` 中的第 $k$ 个字母，那么 $f[i][j][k]=f[i-1][j][k-1]$，不需要转移代价。

如上两种转移取最优即可。

但是我们还需要考虑 $k=0$ 的 Corner Case：
1. 对于第一个转移，因为出现了 `bessie` 中的前 $0$ 个字母并非真实存在，所以并不需要删除字母来维护这个条件（字母就放在那里即可），$f[i][j][0]$ 可以由 $f[i-1][j][0]$ 直接转移而来，无需转移代价。
2. 对于第二个转移，$f[i][j][0]$ 可以直接由 $f[i][j-1][6]$ 转移而来，也无需转移代价。

这样我们就得到了一个 $\mathcal O(n^2)$ 的解法，可以通过 $n\le 2000$ 的 Subtask。考虑优化。

考虑把 $j$ 踢出状态，$f[i][k]$ 表示 $s[1\dots i]$ 通过删去若干字符，最后一个（不完整的） `bessie` 已经凑齐了前 $k$ 位的**最大完整 `bessie` 数以及对应的最小删除代价**。

我们把 最大完整 `bessie` 数 以及 对应的最小删除代价 的二元组称为一个最优方案。注意因为我们要求的是保证 `bessie` 数最大的情况下的最小删除代价，所以我们要优先考虑最大化 `bessie` 数，最小删除代价也是在保证最大的 `bessie` 数前提下的。

所以可以得出和上面类似的转移方程：
1. 当 $s[i]$ 等于 `bessie` 中的第 $k$ 个字母时，$f[i][k]=\operatorname{best\ option}(f[i-1][k]+(0,c[i]),f[i-1][k-1])$。
2. 否则，$f[i][k]=f[i-1][k]+(0,c[i])$。
3. 当 $k=0$ 时，$f[i][k]=\operatorname{best\ option}(f[i-1][0],f[i][6]+(1,0))$。

这样状态就变成 $\mathcal O(n)$ 级别的了，总的复杂度 $\mathcal O(n)$。

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define il inline
using namespace std;
const int N=2e5+5;
int n,c[N];pii f[N][10];
string s,b=" bessie";
il pii best_option(pii x,pii y)
{
	if(x.first<y.first)return y;
	if(x.first==y.first)
	{
		if(x.second<=y.second)return x;
		return y;
	}
	return x;
}
il pii add(pii x,pii y){return {x.first+y.first,x.second+y.second};}
signed main()
{
	cin>>s;n=s.size();s=' '+s;
	for(int i=1;i<=n;++i)cin>>c[i];
	for(int i=0;i<=n;++i)for(int k=0;k<=6;++k)f[i][k]={-1,1e9};
	f[0][0]={0,0};
	for(int i=1;i<=n;++i)
	{
		for(int k=1;k<=6;++k)
		{
			if(s[i]==b[k])f[i][k]=best_option(add(f[i-1][k],{0,c[i]}),f[i-1][k-1]);
			else f[i][k]=add(f[i-1][k],{0,c[i]});
		}	
		f[i][0]=best_option(f[i-1][0],add(f[i][6],{1,0}));
	}
	cout<<f[n][0].first<<endl<<f[n][0].second;
	return 0;
}
```

---

## 作者：CYZZ (赞：7)

# [P9190](https://www.luogu.com.cn/problem/P9190)
模拟赛的题，sto [缪凌锴_Mathew](https://www.luogu.com.cn/user/372409) 巨佬。
## 思路
如果只看第一问的话，可以用贪心做，但是无法解决第二问。

于是我们改用 dp。设 $dp_{i,j}$ 表示前 $i$ 个字符，最后一个 `bessie` 已经匹配了 $j$ 位时，最大的已经匹配的 `bessie` 数量。

考虑第二问，你发现只要把 dp 值存两维就行了，第一维存匹配个数，第二维存代价。（因为题目要求匹配个数优先）

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
int n,a[N];
pair<int,int>dp[N][10],ans;
string s,b="?bessie";
pair<int,int> add(pair<int,int> x,pair<int,int> y)
{
    return {x.first+y.first,x.second+y.second};
}
pair<int,int> Max(pair<int,int> x,pair<int,int> y)
{
    if(x.first==y.first)
    {
        if(x.second<y.second)
            return x;
        return y;
    }
    if(x.first>y.first)
        return x;
    return y;
}
int main()
{
    cin >> s;
    n=s.size();
    s=" "+s;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<6;j++)
        {
            dp[i][j]={-100,100};
        }
    }
    dp[0][0]={0,0};
    for(int i=1;i<=n;i++)
    {
        dp[i][0]=dp[i-1][0];
        if(s[i]==b[6])
            dp[i][0]=Max(dp[i][0],add(dp[i-1][5],{1,0}));
        for(int j=1;j<=5;j++)
        {
            dp[i][j]=add(dp[i-1][j],{0,a[i]});
            if(s[i]==b[j])
                dp[i][j]=Max(dp[i][j],dp[i-1][j-1]);
        }
    }
    for(int i=0;i<=5;i++)
    {
        ans=Max(ans,dp[n][i]);
    }
    printf("%d\n%d",ans.first,ans.second);
}
```

---

## 作者：JLGxy (赞：6)

首先做一次 dp，设 $dp_{i,j}$ 表示字符串的第 $i$ 个字符，匹配到了 `bessie` 中的第 $j$ 个字符，最多有多少完整的 `bessie`。转移是显然的（设 `t="bessie"`）：

$$dp_{i,j}=max(dp_{i-1,j},dp_{i-1,j-1}[s_i=t_j])$$
$$dp_{i,0}=dp_{i,6}+1\quad(s_i=\text{'e'})$$

然后再做一次 dp 求出最小代价，设 $c_{i,j}$ 表示字符串的第 $i$ 个字符，匹配到了 `bessie` 中的第 $j$ 个字符，前面匹配了 $dp_{i,j}$ 个完整的 `bessie` 的最小代价。考虑 $c$ 如何转移：

$$c_{i,j}=\max\limits_{dp_{k,j-1}=dp_{i,j}}\{c_{k,j-1}+sum_{i-1}-sum_k\}$$

这样暴力做转移总复杂度是 $\mathcal O(n^2)$ 的，考虑令 $t_{i,j}=c_{i,j}-sum_i+sum_n$，则可以得到

$$c_{i,j}=\max\limits_{dp_{k,j-1}=dp_{i,j}}\{t_{k,j-1}+sum_{i-1}-sum_n\}$$

把大括号中与 $k$ 无关的都移到外面：

$$c_{i,j}=\max\limits_{dp_{k,j-1}=dp_{i,j}}\{t_{k,j-1}\}+sum_{i-1}-sum_n$$

转移的时候记一下 $\max$ 即可 $\mathcal O(1)$ 得到上式的第一项。总复杂度 $\mathcal O(n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;
const int maxn = 300005;
char s[maxn];
int c[maxn][8], t[maxn][8], p[8][maxn], d[maxn], dp[maxn][8], sum[maxn], ans[maxn];
string bes = " bessie";
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        sum[i] = sum[i - 1] + d[i];
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        memcpy(dp[i], dp[i - 1], sizeof(int) * 8);
        if (s[i] == 'b') {
            dp[i][1] = dp[i][0];
        } else if (s[i] == 'e') {
            dp[i][2] = dp[i][1];
            dp[i][6] = dp[i][5];
            dp[i][0] = dp[i][6] + 1;
        } else if (s[i] == 's') {
            dp[i][4] = dp[i][3];
            dp[i][3] = dp[i][2];
        } else if (s[i] == 'i') {
            dp[i][5] = dp[i][4];
        }
    }
    cout << dp[n][6] << endl;
    memset(p, 0x3f, sizeof(p));
    memset(t, 0x3f, sizeof(t));
    memset(c, 0x3f, sizeof(c));
    memset(ans, 0x3f, sizeof(ans));
    t[0][0] = sum[n];
    p[0][1] = sum[n];
    ans[0] = 0;
    for (int i = 1; i <= n; i++) {
        p[0][1] = sum[n] - sum[i - 1];
        for (int x = 6; x >= 1; x--) {
            if (bes[x] == s[i]) {
                if (x == 1) {
                    c[i][x] = ans[dp[i][x] - 1];
                } else
                    c[i][x] = p[x - 1][dp[i][x]] - sum[n] + sum[i - 1];
                t[i][x] = c[i][x] + sum[n] - sum[i];
                p[x][dp[i][x]] = min(p[x][dp[i][x]], t[i][x]);
                if (x == 6) {
                    ans[dp[i][x]] = min(ans[dp[i][x]], c[i][x]);
                }
            }
        }
    }
    cout << ans[dp[n][6]];
    return 0;
}
```

---

## 作者：Keroshi (赞：5)

先把问题转换为留下的字符 `bessie` 串最多且留下字符的价值和最大。

考虑 dp，但是这里先要最大化 `bessie` 串，再最大化价值和，考虑经典 trick，搞一个超大数 $V$ 使得 $V > \sum c$，然后每加入一个 `bessie` 中的字符就价值加上一个 $V$，即可 dp 时第一关键字为 `bessie` 串数量，第二关键字为价值。

考虑 $f_{u,i}$ 为 $1$ 到 $u$ 的串中，`bessie` 串填到了第 $i$ 个字符，的最大价值。

注意到 `bessie` 串中不可以插字符，但是两个串之间可以，设 `bessis` 串为 $t$，所以转移方程为：

$f_{u,i+1}=\max(f_{u-1,i+1}, [s_u=t_i](f_{u-1,i}+c_u+V))$

$f_{u,0}=\max(f_{u-1,0}+c_u, [s_u=t_5](f_{u-1,5}+c_u+V))$

转移可以直接把数组滚动掉。

时间复杂度 $O(n)$。

```cpp
const int N = 2e5 + 5;
const int V = 1e9;
const ll LNF = 1e18 + 128;
int n; ll a[N], sum;
ll f[6], g[6];
string s, t = "bessie";
void solve() {
	cin >> s; n = SZ(s); s = ' ' + s;
	FOR(i, 1, n) cin >> a[i], sum += a[i];
	REP(i, 6) f[i] = - LNF; f[0] = 0;
	FOR(i, 1, n) {
		REP(j, 6) g[j] = f[j];
		REP(j, 6) if(s[i] == t[j]) chmax(g[(j + 1) % 6], f[j] + a[i] + V);
		chmax(g[0], f[0] + a[i]);
		REP(j, 6) f[j] = g[j];
	}
	cout << f[0] / V / 6 << endl;
	cout << sum - f[0] % V << endl;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给出一个字符串 $S$，你需要进行若干次下面的操作来得到 $S$ 的一个子序列 $T$：

- 花费 $c_i$ 的代价，删去 $S_i$。注意 $c_i$ 中的 $i$ 不会随着 $S$ 的长度而改变对应关系。

你需要输出：

- `bessie` 在 $T$ 中至多出现（occurrence）多少次。
- 在最大化出现次数的前提下，最小化花费的代价。输出这个最小代价。

$1\leq |S|\leq 2\times 10^5$

## 思路

唉，弱小的 xzy。

首先有一个比较显然的 dp，设 $f(i,j,k)$ 表示当前考虑到 $S$ 的前缀 $[1,i]$，已经出现了 $\lfloor\frac{j}{6}\rfloor$ 次完整的模式串 `bessie`，当前匹配到模式串的第 $k$ 位的最小代价（之所以这样设计，是因为我考虑进位（一个完整的模式串结束）的时候简单点）。

转移方程比较好推，大意就是考虑 $S_i$ 是否记入 $T$ 内（记模式串为 $P$）。

- 对于 $k=0$，如果 $6\mid j$，则可以考虑转移，$f(i,j,0)\leftarrow f(i-1,j,t)$，其中 $t\in [0, 6]$。
- 对于 $k=1$，如果 $S_i=P_1, j\equiv 1\pmod{6}$，则可以考虑转移 $f(i,j,1)\leftarrow f(i-1,j-1,t)$。
- 对于 $k\geq 2$，如果 $S_i=P_k$，则可以考虑转移 $f(i,j,k)\leftarrow f(i-1,j-1,k-1)$。
- 无论什么情况，都可以将 $S_i$ 删除，也就是 $f(i,j,k)\leftarrow f(i-1,j,k)+c_i$。

时间复杂度 $O(|P|^2 n^2)$，精细的实现可以做到 $O(|P|n^2)$，均无法通过本题。

考虑优化，你发现我们的转移其实和 $j$ 关系不大，而我们要求最大化这个 $j$，所以可以不将 $j$ 记到状态中，而是改为另一维转移中。

具体来说，设 $f(i,k,0)$，表示当前考虑到 $S$ 的前缀 $[1,i]$，匹配到模式串第 $k$ 位的最大 $j$，$f(i,k,1)$ 为 $j$ 最大的前提下的最小代价。

转移的话和初代版本类似，不过选取转移的第一关键字不是 $f(i,k,1)$ 而是 $f(i,k,0)$，因为我们需要最大化 $j$ 为第一前提。

时间复杂度 $O(|P|n)$ 可以通过本题。

最后统计答案的时候注意，我们应该以 $\lfloor\frac{f(i,k,0)}{6}\rfloor$ 为第一个关键字，而不是 $f(i,k,0)$。

## 代码

转移要有耐心，且需要注意细节。

```cpp
// Problem: P9190 [USACO23OPEN] Pareidolia G

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, f[N][9][2], w[N];
string s, t = " bessie";

int jzy(int x){
    return (x / 6) * 6;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> s; n = s.size(); s = " " + s;
    for(int i=1;i<=n;i++) cin >> w[i];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=6;j++){
            f[i][j][0] = INT_MIN;
            f[i][j][1] = INT_MAX;
        }
    }
    f[0][0][0] = 0; f[0][0][1] = 0;
    for(int i=1;i<=n;i++){
        for(int j=2;j<=6;j++){
            // f[i][j] <- f[i - 1][j], f[i - 1][j - 1]
            f[i][j][0] = f[i - 1][j][0];
            f[i][j][1] = f[i - 1][j][1] + w[i];
            if(f[i][j][0] < (f[i - 1][j - 1][0] + 1) && s[i] == t[j]){
                f[i][j][0] = f[i - 1][j - 1][0] + 1;
                f[i][j][1] = f[i - 1][j - 1][1];
            }
            else if(f[i][j][0] == (f[i - 1][j - 1][0] + 1) && s[i] == t[j]){
                f[i][j][1] = min(f[i][j][1], f[i - 1][j - 1][1]);
            }
        }
        f[i][0][0] = jzy(f[i - 1][0][0]);
        f[i][0][1] = f[i - 1][0][1];
        for(int j=1;j<=6;j++){
            if(f[i][0][0] < jzy(f[i - 1][j][0])){
                f[i][0][0] = jzy(f[i - 1][j][0]);
                f[i][0][1] = f[i - 1][j][1];
            }
            else if(f[i][0][0] == jzy(f[i - 1][j][0])){
                f[i][0][1] = min(f[i][0][1], f[i - 1][j][1]);
            }
        }
        f[i][1][0] = f[i - 1][1][0];
        f[i][1][1] = f[i - 1][1][1] + w[i];
        if(s[i] == t[1]){
            for(int j=0;j<=6;j++){
                if(f[i][1][0] < jzy(f[i - 1][j][0])){
                    f[i][1][0] = jzy(f[i - 1][j][0]) + 1;
                    f[i][1][1] = f[i - 1][j][1];
                }
                else if(f[i][1][0] == (jzy(f[i - 1][j][0]) + 1)){
                    f[i][1][1] = min(f[i][1][1], f[i - 1][j][1]);
                }
            }
        }
    }
    int ans1 = 0, ans2 = INT_MAX;
    for(int j=0;j<=6;j++){
        if((ans1 / 6) < (f[n][j][0] / 6)){
            ans1 = f[n][j][0];
            ans2 = f[n][j][1];
        }
        else if((ans1 / 6) == (f[n][j][0] / 6)){
            ans2 = min(ans2, f[n][j][1]);
        }
    }
    cout << (ans1 / 6) << '\n' << ans2 << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：云浅知处 (赞：1)

我们发现 `bessie` 这个单词是没有 border 的。也就是说最终可以把字符串分段，每段划分出一个 `bessie`。

首先考虑怎么算最多的 `bessie` 数量，发现可以贪心：每次贪心找一个最短的后缀使其包含 `bessie`，以这个后缀作为决策点。这样我们就可以递推出每个前缀的最多 `bessie` 数量 $f_i$。只需要判断某个区间内是否有 `bessie` 子序列，以及权值最大的 `bessie` 子序列。维护子序列自动机之类的东西贪心跳第一个 `e,i,s,s,e,b` 就行了。

考虑怎么算最小代价，发现相当于每次选一个 $f_j+1=f_i$ 的 $j$，转移到 $g_j+w(j+1,i)$。此时相当于要把 $f$ 划分成若干连续段，在两个相邻连续段中做转移。对于两个连续段 $[a,b],[b+1,c]$，我们要让 $g[a\cdots b]$ 转移到 $g[b+1\cdots c]$。

把贡献 $w(i,j)$ 拆开，发现有三种情况：选出的 `bessie` 全都在 $[b+1,j]$ 内，全都在 $[i,b]$ 内，或者在两段之间。前两种容易计算，第三种可以枚举分段点之后 $O(1)$ 计算。

记 $L=\texttt{bessie}$。具体来说，我们对 $[a,b]$ 中的每个 $i$ 算出 $c_1(i,l,r)$ 表示从 $[i,b]$ 中选出 $L[l\cdots r]$，并删掉某些字符使得 $L[l\cdots r]$ 连续且紧贴右端点的最小代价。转移时只需要讨论是否有 $s[i]=L[l]$ 即可。再算出 $c_2(i,l)$ 表示从 $[i,b]$ 中选出 $L[l\cdots 6]$，并删掉某些字符使得 $L[l\cdots 6]$ 连续但不必紧贴右端点的最小代价。在右边也做一遍类似的 DP 即可。

复杂度大概是 $O(n|\Sigma|+n|L|^2)$，其中 $|L|=|\texttt{bessie}|=6$。

感觉这个做法比较丑，如果有更优美的做法戳我一下谢谢喵。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=1e9+7;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=2e5+5;
const int D=30;
char s[N];
int n,cost[N],f[N],g[N],pre[N][D],pos[D],cur[N];

//bessie
char t[6]={'b','e','s','s','i','e'};
int calc(int p){
	for(int i=5;i>=0&&p>=0;i--)p=pre[p][t[i]-'a']-1;
	return p;
}

int cl1[N][7][7],cl2[N][7],cr1[N][7][7],cr2[N][7],mv[7];
const int INF=1e9;

void solve(int l,int mid,int r){
	
	for(int i=0;i<=6;i++)for(int j=0;j<=6;j++)cl1[mid+1][i][j]=INF;
	cl2[mid+1][6]=0;for(int i=0;i<6;i++)cl2[mid+1][i]=INF;
	for(int i=mid;i>=l;i--){
		for(int j=0;j<6;j++){
			cl2[i][j]=cl2[i+1][j];
			if(j!=0)cl2[i][j]+=cost[i];
			if(s[i]==t[j])cl2[i][j]=min(cl2[i][j],cl2[i+1][j+1]);
		}
		cl2[i][6]=cl2[i+1][6];
	}
	for(int k=1;k<=6;k++){//cl1[i][j][k] ：从 [i...mid] 中选一个子串 L[j...k-1] 
		cl1[mid+1][k][k]=0;
		for(int i=mid;i>=l;i--){
			for(int j=0;j<k;j++){
				cl1[i][j][k]=cl1[i+1][j][k];
				if(j!=0)cl1[i][j][k]+=cost[i];
				if(s[i]==t[j])cl1[i][j][k]=min(cl1[i][j][k],cl1[i+1][j+1][k]);
			}
			cl1[i][k][k]=cl1[i+1][k][k]+cost[i];
		}
	}
	
	for(int i=0;i<=6;i++)for(int j=0;j<=6;j++)cr1[mid][i][j]=INF;
	cr2[mid][0]=0;for(int i=1;i<=6;i++)cr2[mid][i]=INF;
	for(int i=mid+1;i<=r;i++){
		for(int j=1;j<=6;j++){
			cr2[i][j]=cr2[i-1][j];
			if(j!=6)cr2[i][j]+=cost[i];
			if(s[i]==t[j-1])cr2[i][j]=min(cr2[i][j],cr2[i-1][j-1]);
		}
		cr2[i][0]=cr2[i-1][0];
	}
	for(int j=0;j<6;j++){
		cr1[mid][j][j]=0;
		for(int i=mid+1;i<=r;i++){
			for(int k=j+1;k<=6;k++){
				cr1[i][j][k]=cr1[i-1][j][k];
				if(k!=6)cr1[i][j][k]+=cost[i];
				if(s[i]==t[k-1])cr1[i][j][k]=min(cr1[i][j][k],cr1[i-1][j][k-1]);
			}
			cr1[i][j][j]=cr1[i-1][j][j]+cost[i];
		}
	}
	
	for(int j=0;j<=6;j++)mv[j]=INF;
	for(int i=l;i<=mid;i++){
		for(int j=1;j<=5;j++)mv[j]=min(mv[j],g[i]+cl1[i][0][j]);
		mv[6]=min(mv[6],g[i]+cl2[i+1][0]),mv[0]=min(mv[0],g[i]);
	}
	for(int i=mid+1;i<=r;i++){
		g[i]=mv[0]+cr2[i][6];g[i]=min(g[i],mv[6]);
		for(int j=1;j<=5;j++)g[i]=min(g[i],mv[j]+cr1[i][j][6]);
	}
}

int L[N],R[N];

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	cin>>(s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)cost[i]=read();
	
	for(int i=1;i<=n;i++){
		pos[s[i]-'a']=i;
		for(int j=0;j<26;j++)pre[i][j]=pos[j];
	}
	
	for(int i=1;i<=n;i++)if(calc(i)>=0)f[i]=f[calc(i)]+1;
	cout<<f[n]<<endl;
	
	memset(L,63,sizeof(L));
	for(int i=1;i<=n;i++)L[f[i]]=min(L[f[i]],i),R[f[i]]=i;
	for(int i=0;i<f[n];i++)solve(L[i],R[i],R[i+1]);
	cout<<g[n]<<endl;

	return 0;
}
```

---

## 作者：__Ginka__ (赞：0)

### 总思路

1. 目标合并：通过引入 $V$，将最大数量和最小删除成本统一为单一优化目标。
2. 动态规划：$f_{j}$ 表示匹配到 `bessie` 的第 $j$ 个字符时的最大价值。
3. 转移：第一种就是匹配成功时更新下一个状态，并累加价值，第二种允许保留字符但不推进匹配（仅对状态 $0$）。

#### 状态定义

如果用 $k$ 表示已完成的 `bessie` 数量，用 $t$ 表示保留的字符总成本，那么价值就是：$V \times k+t$。

其中 $V$ 足够大（$V > \sum c_i$），所以确保数量优先。

#### 状态转移

1. 匹配成功（当前字符与 `bessie` 的第 $j$ 位相同）：$f_{j+1} = \max\left(f_{j+1},\ f_{j} + c_i + V\right)$

用于保留当前字符，推进匹配进度，累加成本并增加计数权重 $V$。

2. 保留但不匹配（边界）：$f_{0} = \max\left(f_{0},\ f_{0} + c_i\right)$

3. 完成一个 `bessie` 后的循环：

当 $j=5$（匹配到最后一个字符 `e`）时，下一个状态为 $0$，此时若再次匹配到 `b`，就是说开到了新的一串 `bessie`。

#### 最后计算

最大数量：总价值中 $V$ 的总贡献次数为 $\frac{f_{0}}{V}$，每个 `bessie` 需要 $6$ 次 $V$，所以数量为：$\left\lfloor \frac{f_{0}}{6V} \right\rfloor$

最小删除成本：总保留成本为 $\text{sum} = \sum c_i$，实际保留成本为 $f_{0} \bmod V$，所以删除成本 $g$ 为：$\text{sum} - (f_{0} \bmod V)$

思路较粗糙，建议搭配代码理解。
代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200007],sum;
string s,t="bessie";
long long f[6],g[6];//f[j]表示匹配到t的第j个字符时的最大价值（数量*V + 保留成本）
int n;
const long long V=1e9;
const long long LNF=1e18; 
int main()
{
    cin>>s;
    n=s.size();
    s=' '+s;//调整下标从1开始
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];
    }
    for(int j=0;j<6;j++)
    {
        f[j]=-LNF;
    }
    f[0]=0;//未匹配任何字符，价值为0
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<6;j++)
        {
            g[j]=f[j];
        }

        //保留当前字符的情况
        for(int j=0;j<6;j++)
        {
            if(s[i]==t[j])//当前字符匹配t的第j个字符
            {
                int nj=(j+1)%6;//转移到下一个状态
                long long tmp=f[j]+a[i]+V;//累加保留成本和大常数V
                if(tmp>g[nj])//更新目标状态
                {
                    g[nj]=tmp;
                }
            }
        }
        //保留当前字符但不参与匹配的情况
        long long tmp=f[0]+a[i];//仅累加保留成本
        if(tmp>g[0])
        {
            g[0]=tmp;
        }
        //将临时数组g的值更新回f数组
        for(int j=0;j<6;j++)
        {
            f[j]=g[j];
        }
    }
    //计算最大bessie数量：
    long long k=f[0]/V/6; 
    //计算删除的最小成本
    long long c=sum - f[0]%V; 
    cout<<k<<endl;
    cout<<c<<endl;
    return 0;
}
```

---

## 作者：g1ove (赞：0)

注意到 `bessie` 没有 $\text{border}$。

不难设计一个暴力的 dp，设状态 $f_{i,j,k}$ 表示到了第 $i$ 个字符，匹配到了第 $j$ 位，一共出现了 $k$ 个 `bessie` 的最小代价。由于题目要求 `bessie` 个数最大，所以只有 $j$ 达到最大值的时候状态是有用的。这样我们的状态数就变成 $O(n)$ 的了，再用滚动数组压掉一维。

正难则反，定义新状态 $f_{i}$ 表示匹配到字符串第 $i$ 位时，取了的位的最大代价和。再定义一个 $g_i$ 表示匹配到第 $i$ 位时 `bessie` 最大的个数。

我们需要同时转移 $f,g$，具体而言，当 $g_{i-1}>g_i$ 时，需要强制从 $f_{i-1}$ 转移过来，其他情况贪心转移即可。

最后就是匹配完 `bessie` 时可以取一些无关的字符，可以每次贪心的夺取一些数。

将 `bessie` 的长度看为常数，则时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define ll long long
using namespace std;
int n;
char s[N];
int w[N]; 
char M[]="bessie";
int cnt,sum,used;
int f[8],g[8];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	memset(g,-1,sizeof g);
	g[5]=0;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&w[i]);sum+=w[i];
		if(s[i]==M[5])
			if(g[4]==g[5]) f[5]=f[4],g[5]=g[4]+1;
			else f[5]=max(f[5],f[4]);
		for(int j=4;j+1;j--)
		{
			if(M[j]^s[i]) continue;
			int lst=(j+5)%6;
			if(g[lst]>g[j]) f[j]=f[lst]+w[i],g[j]=g[lst];
			else f[j]=max(f[j],f[lst]+w[i]);
		}
		f[5]+=w[i];
	}
	printf("%d\n%d",g[5],sum-f[5]);
	return 0;
}
```

---

