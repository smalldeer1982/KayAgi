# Remembering Strings

## 题目描述

You have multiset of $ n $ strings of the same length, consisting of lowercase English letters. We will say that those strings are easy to remember if for each string there is some position $ i $ and some letter $ c $ of the English alphabet, such that this string is the only string in the multiset that has letter $ c $ in position $ i $ .

For example, a multiset of strings {"abc", "aba", "adc", "ada"} are not easy to remember. And multiset {"abc", "ada", "ssa"} is easy to remember because:

- the first string is the only string that has character $ c $ in position $ 3 $ ;
- the second string is the only string that has character $ d $ in position $ 2 $ ;
- the third string is the only string that has character $ s $ in position $ 2 $ .

You want to change your multiset a little so that it is easy to remember. For $ a_{ij} $ coins, you can change character in the $ j $ -th position of the $ i $ -th string into any other lowercase letter of the English alphabet. Find what is the minimum sum you should pay in order to make the multiset of strings easy to remember.

## 样例 #1

### 输入

```
4 5
abcde
abcde
abcde
abcde
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 3
abc
aba
adc
ada
10 10 10
10 1 10
10 10 10
10 1 10
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 3
abc
ada
ssa
1 1 1
1 1 1
1 1 1
```

### 输出

```
0
```

# 题解

## 作者：YLWang (赞：9)

状压简单题。

首先看到数据范围$n \leqslant 20$, 就可以往状压的方面考虑了。

先想暴力状压。定义$dp[st]$表示当前状态为$st$时，答案的最小值。其中，$st$的第$i$位为$1$表示第$i$个串已经满足，反之则表示还没有满足。

那么将一个串变为合法的，无非就两种情况：

- 改变当前这个串的某一个位置，使这个位置独一无二
- 改变其他与这个串这个位置相同的所有串的这个位置，这个位置从而也就独一无二了。

定义$qwq[i][j]$表示所有第$j$个字符与第$i$个串第$j$个字符相同的串，使用状态压缩的形式表示; $b[i][j]$表示将他们全部变成不同的价值。注意，因为要把这些都变得不一样，所以可以不将这个串设为不操作，而是将这些串中价值最大的设为不操作。

那么状态转移方程就比较显然了，可以看代码。

Q：如果一个串一开始就是好理解的，那这个转移方程为什么正确呢？

A：这个时候，第二条转移方程会覆盖第一条转移方程。

此方法代码：
```
#include<bits/stdc++.h>
#define ll long long
#define reaD() read()
#define pb push_back
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(register int i = (k); i >= (j); i--)
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
#define MAXN 22
string s[MAXN]; 
int a[MAXN][MAXN], n, m, qwq[MAXN][MAXN], b[MAXN][MAXN];
int dp[1<<MAXN];
signed main()
{
	n = read(), m = read();
	For(i, 0, n-1) cin >> s[i];
	For(i, 0, n-1) For(j, 0, m-1)
		a[i][j] = read();
	For(i, 0, n-1) {
		For(j, 0, m-1) {
			int sum = 0, val = -(1 << 30);
			For(k, 0, n-1) {
				if(s[k][j] == s[i][j]) {
					sum += a[k][j], ckmax(val, a[k][j]);
					qwq[i][j] |= (1 << k);
				}
			}
			b[i][j] = sum - val;
		}
	}
	memset (dp, 127/2, sizeof (dp)); 
	dp[0] = 0;
	For(i, 0, (1<<n)-1) {
		For(j, 0, n-1) {
			if (!(i & (1 << j))) {
				For(k, 0, m-1) {
					ckmin(dp[i | (1 << j)], dp[i] + a[j][k]);
					ckmin(dp[i | qwq[j][k]], dp[i] + b[j][k]);
				}
			}
		}
	}
			
	printf ("%d\n", dp[(1<<n) - 1]);
    return 0;
}
```

但是这样虽然可以卡过去，但显然复杂度$O(2^nnm)$是有问题的。

下面优化其至$O(2^nm)$

其实，这个算法本质上是可以看做在一个$DAG$上面$DP$。

我们在上面的两个转移方程，实际上就是在$DAG$中的两个顶点连一条边。

最终求的就是起点和终点的最短路。

那么有没有简化建边的方法呢？

答案是：有的。

我们有一个结论，就是说，只要一个点随便连出去一个$0$所有边，对结果就没有影响。

因为无论走哪条路径，最终都会到达全$1$的状态。

所以说，就算中间的DP值是不对的，最终的DP值也是对的，因为路径一定走过了最优状态。

比如说，我们有最优路径$000 -> 110 -> 111$

那么我们用如下的方法，一定有$000 -> 001 -> 111$, 等价于最优路径。

这个技巧非常的常用，希望大家可以学习一下。

```
#include<bits/stdc++.h>
#define ll long long
#define reaD() read()
#define pb push_back
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(register int i = (k); i >= (j); i--)
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
#define MAXN 22
string s[MAXN]; 
int a[MAXN][MAXN], n, m, qwq[MAXN][MAXN], b[MAXN][MAXN];
int dp[1<<MAXN];
signed main()
{
	n = read(), m = read();
	For(i, 0, n-1) cin >> s[i];
	For(i, 0, n-1) For(j, 0, m-1)
		a[i][j] = read();
	For(i, 0, n-1) {
		For(j, 0, m-1) {
			int sum = 0, val = -(1 << 30);
			For(k, 0, n-1) {
				if(s[k][j] == s[i][j]) {
					sum += a[k][j], ckmax(val, a[k][j]);
					qwq[i][j] |= (1 << k);
				}
			}
			b[i][j] = sum - val;
		}
	}
	memset (dp, 127/2, sizeof (dp)); 
	dp[0] = 0;
	For(i, 0, (1<<n)-2) {
		int j;
		for(j = 0; j < n; j++)
			if (!(i & (1 << j))) {
				break;
			}
		For(k, 0, m-1) {
			ckmin(dp[i | (1 << j)], dp[i] + a[j][k]);
			ckmin(dp[i | qwq[j][k]], dp[i] + b[j][k]);
		}
	}
			
	printf ("%d\n", dp[(1<<n) - 1]);
    return 0;
}
```

---

## 作者：81179332_ (赞：4)

状压 dp，设 $dp_i$ 表示将集合 $i$ 中的串都变为合法的最小代价

对于一个不合法的串，位置 $j$，有两种转移：

1. 改变这个串的位置 $j$，使它独一无二（一共只有 $20$ 个串，但是有 $26$ 个字母，所以一定可以做到）

2. 改变所有位置 $j$ 与当前串位置 $j$ 相同的串，使得它们全都独一无二（保留代价最大的那个串不变一定是最优的）

预处理与第 $i$ 个串的第 $j$ 个位置相同的串的集合 $se_{i,j}$，以及改变它们的代价 $v_{i,j}$

这样做的复杂度是 $O(nm\cdot2^n)$

发现转移顺序不影响答案，所以我们转移时可以随便选择一个不合法的串（即当前状态为 $0$） 的串转移，采用刷表法

```cpp
//timeues:10min
const int N = 30;
int n,m,a[N][N];char s[N][N];
int se[N][N],v[N][N];
int dp[1 << 20];
int main()
{
	n = read(),m = read();
	for(int i = 0;i < n;i++) scanf("%s",s[i]);
	for(int i = 0;i < n;i++) for(int j = 0;j < m;j++) a[i][j] = read();
	for(int i = 0;i < n;i++) for(int j = 0;j < m;j++)
	{
		int res = 0,maxx = -1;
		for(int k = 0;k < n;k++) if(s[k][j] == s[i][j])
			se[i][j] |= (1 << k),res += a[k][j],maxx = max(maxx,a[k][j]);
		v[i][j] = res - maxx;
	}memset(dp,63,sizeof(dp));
	int S = (1 << n) - 1;
	dp[0] = 0;
	for(int i = 0;i < S;i++)
	{
		int k = 0;while(i & (1 << k)) k++;
		for(int j = 0;j < m;j++)
		{
			dp[i | (1 << k)] = min(dp[i | (1 << k)],dp[i] + a[k][j]);
			dp[i | se[k][j]] = min(dp[i | se[k][j]],dp[i] + v[k][j]);
		}
	}fprint(dp[S]);
	return 0;
}
```

---

## 作者：LCat90 (赞：1)

显然为了方便，可以先假设一些单词已经与众不同了，直接考虑剩下的单词如何修改。

修改的先后是没有影响的，所以可以随便找一个没有修改的位置 $k$，然后修改。有两种方案：

+ 选择一个位置的字符修改，使之和其它位置不同。

由于修改最多只有 $20$ 个元素，且小写字母有 $26$ 个，故改一个字符一定是满足的。

+ 选择一个位置 $j$，然后使得这个位置上所有与 $s_{i,j}$ 相同的位置都不同。

而这种方案的答案就是减去最大值的和。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 50, M = 2e6 + 5;
int n, m, a[N][N], dp[M], b[N][N], f[N][N]; 
char c[N][N];
signed main() {
	while(cin >> n >> m) {
		memset(dp, 0x3f, sizeof dp);
		memset(b, 0, sizeof b);
		memset(f, 0, sizeof f);
		for(int i = 1;i <= n; ++i) scanf("%s", c[i] + 1);
		for(int i = 1;i <= n; ++i) 
			for(int j = 1;j <= m; ++j) cin >> a[i][j];
		for(int i = 1;i <= n; ++i) 
			for(int j = 1;j <= m; ++j) {
				int maxn = 0;
				for(int k = 1;k <= n; ++k) 
					if(c[k][j] == c[i][j])
						f[i][j] |= (1 << (k - 1)), b[i][j] += a[k][j], maxn = max(maxn, a[k][j]);
				b[i][j] -= maxn;
			}
		dp[0] = 0;
		for(int i = 0;i < (1 << n) - 1; ++i) {
			int k = 0; while(i & (1 << k)) k++;
			++k;
			for(int j = 1;j <= m; ++j) {
				dp[i | (1 << (k - 1))] = min(dp[i | (1 << (k - 1))], dp[i] + a[k][j]);
				dp[i | f[k][j]] = min(dp[i | f[k][j]], dp[i] + b[k][j]);
			}
		}
		cout << dp[(1 << n) - 1] << "\n";
	}
	return 0;
}
```

---

## 作者：Meteor_ (赞：1)

# CF543C Remembering Strings 题解

## 题意

~~我觉得现在这个题面翻译写的不像人话，估计过不了过久就会被换掉~~

给你 $n$ 个长度为 $m$ 的字符串。如果一个字符串某一位上的字符，是其他 $n - 1$ 个字符串的这一位上没有的，那么称这个字符串是好的。你可以改变其中一些字符，但也有代价。你希望用最小的代价让这 $n$ 个字符串变成好的。

$1 \le n, m \le 20$。

## 分析

数据范围 $1 \le n, m \le 20$，其实很明显是状压，压什么也比较好想。毕竟压 $m$ 没什么实际意义，可能性不大，就只能压 $n$。再看一眼范围，不像是给 $O(nm \cdot 2^n)$ 的，倒像是给 $O(n \cdot 2^n)$ 或 $O(m \cdot 2^n)$ 的。于是我们可以进一步去想了。

## 题解

$dp_i$ 表示状态为 $i$ 时的最小代价。二进制下 $i$ 的第 $j$ 位为 $1$ 表示第 $j$ 个字符串已经满足条件。

我们考虑怎么去转移。

对于一个还没有满足条件的字符串，我们有两种选择：

1. 改变它的某一位，使其变得独一无二（因为 $m \le 20 < 26$，所以一定能做到）；

2. 让其他与这个串的某一位的相同的串的这一位都变得独一无二。

所以转移就有两种。

我们不能转移时再去找有多少字符串与它这一位相同，所以我们需要预处理出来。

设 $s_{i, j}$ 表示与字符串 $i$ 的第 $j$ 位相同的串，也把它压成状态，$w_{i, j}$ 表示把与字符串 $i$ 的第 $j$ 位相同的串都变得独一无二需要的代价。

这两个东西很好求。但是在求 $w$ 时需要注意一下，我们不需要把所有字符串的那一位都变掉，可以保留一个代价最大的不改。

感觉这样就很好转移了。

写一下转移，假设 $i$ 在二进制下的第 $pos$ 位为 $0$，当前枚举到了字符串的第 $j$ 位：

- $dp_{i | 2^{pos}} = min(dp_{i | 2^{pos}}, dp_i + a_{pos, j})$；

- $dp_{i | s_{pos, j}} = min(dp_{i | s_{pos, j}}, dp_i + w_{pos, j})$。

但是我们发现，这样是 $O(nm \cdot 2^n)$ 的，会寄，所以考虑怎么优化一下。

我们注意到，这个转移是与顺序无关的，所以只需要找到一位为 $0$ 即可转移（换句话说，我们只需要找到一个 $pos$），不需要对于所有为 $0$ 的位置都去转移。因为我们只要最后的状态——所有字符串都独一无二即可，不需要在过程中保证什么。而你稍微思考一下可以发现，即便我们只转移一位 $0$，每一个状态也都会被覆盖到。于是，我们就有了时间复杂度 $O(m \cdot 2^n)$ 的算法。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define M 21

using namespace std;

int n, m, a[M][M], s[M][M], w[M][M], dp[1 << M], bin[M + 1];
string str[M];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    bin[1] = 1;
    for(int i = 2; i <= M; ++ i)
        bin[i] = bin[i - 1] << 1;
    for(int i = 1; i <= n; ++ i)
        cin >> str[i], str[i] = '#' + str[i];
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j)
            cin >> a[i][j];
    for(int i = 1; i <= n; ++ i) {
        for(int j = 1; j <= m; ++ j) {
            int maxn = 0;
            for(int k = 1; k <= n; ++ k) {
                if(str[i][j] == str[k][j]) {
                    s[i][j] += bin[k];
                    w[i][j] += a[k][j];
                    maxn = max(maxn, a[k][j]);
                }
            }
            w[i][j] -= maxn;
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for(int i = 0; i < bin[n + 1] - 1; ++ i) {
        int pos = 1;
        while(bin[pos] & i)
            ++ pos;
        for(int j = 1; j <= m; ++ j) {
            dp[i | bin[pos]] = min(dp[i | bin[pos]], dp[i] + a[pos][j]);
            dp[i | s[pos][j]] = min(dp[i | s[pos][j]], dp[i] + w[pos][j]);
        }
    }
    cout << dp[bin[n + 1] - 1];
}
```

---

## 作者：Forever1507 (赞：0)

## CF543C

简要题意：给定 $n$ 个长度为 $m$ 的字符串以及矩阵 $A$，其中 $A_{i,j}$ 表示将第 $i$ 个字符串的第 $j$ 个字符修改为任意其他字母的代价，求最小代价使得每一个字符串在修改后都至少有一位在所有字符串的这一位中是唯一的。

注意到将一个字符串的某一位修改为唯一只有两种途径：把自己这一位改掉，或者把与自己相同的位置全部改掉。

对于第二种方法，因为我把和自己相同的也全部改掉了，所以等于把某一位上相同的位置全部变成合法的，又考虑到 $n,m$ 很小，所以考虑用状压维护。一个状态 $st$ 的第 $i$ 位为 $1$ 表示这个字符串当前已经唯一了。

对上述两种方法分别考虑转移：

- 对于第一种，假设枚举到第 $i$ 个串，找到 $A_{i,j}$ 最小的位置 $j$，直接将 `st` 转移到  `st|(1<<i)` 即可。这显然是平凡的，不再赘述。
- 对于第二种，枚举第 $i$ 个串的第 $j$ 位，预处理 $s_{i,j}$ 表示第 $j$ 位与 $i$ 相同的字符串的状态，$val_{i,j}$ 表示第 $j$ 位与 $i$ 相同且不含 $i$ 的 $A_{k,j}$ 之和。因为所有 $s_{i,j}$ 相同的状态中一定会覆盖到所有可能不含的位置所以一定是对的。然后有转移 $f_i=\max(f_i,f_{i|s_{i,j}}+val_{i,j})$。一个串允许被改多次所以不需要判重。

时间复杂度为 $O(2^nnm)$，因为时限开到了 $2$ 且状压常数不大，所以可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char c[25][25];
int f[1<<20],a[25][25],val[25][25],st[25][25];
int mini[25];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>c[i][j];
        }
    }
    memset(mini,0x3f,sizeof(mini));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            mini[i]=min(mini[i],a[i][j]);
            for(int k=1;k<=n;++k){
                if(c[i][j]==c[k][j]){
                    if(i!=k)val[i][j]+=a[k][j];
                    st[i][j]|=(1<<k-1);
                }
            }
        }
    }
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=0;i<(1<<n);++i){
        for(int j=1;j<=n;++j){
            if(!(i>>j-1&1)){
                f[i|(1<<j-1)]=min(f[i|(1<<j-1)],f[i]+mini[j]);
                for(int k=1;k<=m;++k){
                    f[i|st[j][k]]=min(f[i|st[j][k]],f[i]+val[j][k]);
                }
            }
        }
    }
    cout<<f[(1<<n)-1];
    return 0;
}
```

---

## 作者：cqbzlzm (赞：0)

### *Description*

**题目大意：**有 $n$ 个长度都为 $m$ 的单词，仅由小写英文字母组成。 你可以支付 $c_{i,j}$ 的代价，将第 $i$ 个单词的第 $j$ 个字母修改成任意一个小写英文字母。求将所有单词都改成至少有一位**与众不同**所需的最小代价。当单词某一位置的字母与其他单词这一位的字母都不同时，我们认为单词的这一位是**与众不同**的。

**数据范围：** $1\leq n,m\leq 20,1\leq c_{i,j} \leq 10^6$。

### *Solution*

一眼的状压DP题目。$dp_{sta}$，若 $sta$ 的第 $i$ 位是 $1$，则表示使得所有第 $i$ 个字符串已经**与众不同**的最小代价。

考虑如何把一个字符串变得与众不同：

- 使自己在某一位变得与其他的字符串都不相同
- 使在这一位所有和我相同的都变得和我不同，顺带地，还可以把他们分别变得不同

所以我们枚举 $sta$，然后枚举每个第 $i$ 位为 $0$ 的字符串（先枚举 $i$），然后按上面的方式进行操作，刷表法。

但是上面的做法要 `TLE`，但是我们发现当前一步对任意未满足条件的字符串来说是一样的，所以我们只需要找第一个不满足条件的就可以了（或者说选的顺序不影响答案）。



### *Code*

```cpp
for (int i = 1; i <= n; i ++) scanf("%s", s[i] + 1);
for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++) scanf("%d", &a[i][j]);
for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)  {
        int mx = 0;
        for (int k = 1; k <= n; k ++)
            if (s[i][j] == s[k][j]) {
                mx = max(mx, a[k][j]);
                xt[i][j] += (1 << (k - 1));
                cost[i][j] += a[k][j];
            }
        cost[i][j] -= mx;
    }
memset(dp, 0x3f3f3f3f, sizeof(dp));
dp[0] = 0;
for (int j = 0; j < (1ll << n); j ++) {
    int k = 0;
    while (j >> k & 1) k ++;
    for (int i = 1; i <= m; i ++) {
        dp[j | (1ll << k)] = min(dp[j | (1ll << k)], dp[j] + a[k + 1][i]);
        dp[j | xt[k + 1][i]] = min(dp[j | xt[k + 1][i]], dp[j] + cost[k + 1][i]);
    }
}
printf("%lld\n", dp[(1ll << n) - 1ll]);
```

---

## 作者：Unnamed114514 (赞：0)

首先可以想到，因为 $m\le 20$，所以一次修改一定可以使一个串变得与众不同。

我们把让一个串分成变得与众不同的方法分成如下两种：

1. 更改一个串位置的字符，使这个串变得与众不同。

2. 更改一个位置上所有与串当前位置相同的字符，同样地，这些字符串都会变得与众不同。

因此我们可以定义 $f_{now,s}$ 表示第 $now$ 列与众不同状态为 $s$ 的最小花费。

对于第一种情况，我们就找到一个当前未选取的串，更改 $now$ 位即可。

那么对于第二种情况，我们就会发现对于所有的字符，我们所对应的修改状态是不同的，所以我们可以直接存下每个字符在当前位的修改状态。

首先，贪心地，若 $s$ 在一次操作之后还是 $s$，那么我们的花费白白地消耗了，又因为 $s$ 不会变小，所以我们的 dp 不会出现循环的情况。

时间复杂度 $O(n|s|2^n)$，其中 $|s|$ 为小写字符集的大小，即 $26$。

然后会发现这样会 TLE on #6，但是我们代码的复杂度是正确的，于是考虑常数优化。

然后我们就可以发现的是：对于第一种操作，所有的字符串都是独立的，然后可以修改改行任意字符。所以我们在搜索完成后即 $now=m+1$ 后，对所有没有变成与众不同的位置对它的任意位置进行修改即可。因为要最小，所以花费就是 $\min\limits_{j=1}^m c_{i,j}$。

虽然时间复杂度 $O(|s|n2^n)$，但是常数优化了很多，只跑了 46ms，还拿了最优解。

---

## 作者：世末OIer (赞：0)

> 用二进制串表示字符串是否好记，1表示好记，0表示不好记，dp值表示到当前状态的最少代价，每一次转移只考虑最低的为0的一位，两种可能:一种是把它变出去，另一种是在跟它相同（包括自己）的里边只保留最大的，把其它的都换走，这样可以转移到下一个状态了，对每一个状态不断地更新到最小值，最后全1的状态的值就是答案了

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[25][25],N,M,dp[1<<22],l,n,m,t,h,i,j,b,c;
string s[25];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>N>>M;
	for(i=0;i<N;++i) cin>>s[i];
	for(i=0;i<N;++i) for(j=0;j<M;++j) cin>>a[i][j];
	memset(dp,63,sizeof(dp));
	dp[0]=0;
	for(m=0;m<(1<<N);++m){
		for(b=0;b<N;++b) if(!(m&(1<<b))){              //找到第一个还不是好记的
			l=b;
			break;
		}
		for(c=0;c<M;++c){
			dp[m+(1<<l)]=min(dp[m+(1<<l)],dp[m]+a[l][c]),n=m,t=0,h=0;   //初始赋值
			for(i=0;i<N;++i) if(s[i][c]==s[l][c]) n|=(1<<i),t+=a[i][c],h=max(h,a[i][c]);  //去减去数的最大值就是取最后的最小值
			dp[n]=min(dp[n],dp[m]+t-h);          //赋值
		}
	}
	cout<<dp[(1<<N)-1]<<endl;
	return 0;
}
```

---

