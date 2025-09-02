# [ABC313Ex] Group Photo

## 题目描述

### 题面描述：

存在 $2 \times n + 1$ 个人需排队照相， 分为两排。

第一排的人高度分别为：$a_1, a_2, a_3, ... , a_n$。

第二排的人高度分别为：$b_1, b_2, b_3, ... , b_n, b_{n+1}$。

你可以自行决定这些人的排列顺序， 使其符合如下条件 ：

- $b_1 > a_1$
- $b_{n + 1} > a_n$
- $b_{i} > \min(a_i, a_{i - 1}) \text{ }( 2 \le i \le n)$

请问存在合法的第一排排列方案有多少？

## 样例 #1

### 输入

```
3
1 12 6
4 3 10 9```

### 输出

```
2```

## 样例 #2

### 输入

```
1
5
1 10```

### 输出

```
0```

## 样例 #3

### 输入

```
10
189330739 910286918 802329211 923078537 492686568 404539679 822804784 303238506 650287940 1
125660016 430302156 982631932 773361868 161735902 731963982 317063340 880895728 1000000000 707723857 450968417```

### 输出

```
3542400```

# 题解

## 作者：EuphoricStar (赞：7)

考虑若重排好了 $a$，如何判断可不可行。显然只用把 $b$ 排序，把 $\min(a_{i - 1}, a_i)$ 也排序（定义 $a_0 = a_{n + 1} = +\infty$），按顺序逐个判断是否大于即可。

这启示我们将 $\min(a_{i - 1}, a_i)$ 排序考虑。考虑从大到小加入 $a_i$，那么加入一个 $a_i$，和它相邻的 $\min(a_{i - 1}, a_i)$ 一定是 $a_i$。每个时刻已经加入的 $a_i$ 形成了若干个连续段，考虑连续段 dp：

设 $f_{i, j}$ 为考虑了 $a$ 中前 $i$ 大的数，当前形成了 $j$ 个连续段。那么有 $i - j$ 对相邻的数。

初值为 $f_{2, 2} = 1$，表示一开始加入了 $a_0$ 和 $a_{n + 1}$。

有转移：

- $a_i$ 新开一个段，这个段可以在两段之间的空隙中：$f_{i, j + 1} \gets f_{i - 1, j} \times (j - 1)$；
- 把 $a_i$ 接入一个段的开头或末尾，需要满足 $a_i < b_{i - j}$，此时有：$f_{i, j} \gets f_{i - 1, j} \times (2j - 2)$；
- 把 $a_i$ 塞进两个相邻段的空隙中，然后合并这两个段，需要满足 $a_i < b_{i - j + 1}$，此时有：$f_{i, j - 1} \gets f_{i - 1, j} \times (j - 1)$。

答案为 $f_{n + 2, 1}$。

时间复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/abc313/submissions/45771012)

---

## 作者：liyujia (赞：7)

蒟蒻第一篇题解，写得不好/有误请见谅。

[原题传送门](https://atcoder.jp/contests/abc313/tasks/abc313_h)
[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc313_h)

### 题意

有 $2n+1$ 个人要拍照，其中 $n$ 个人在第一排，身高为 $a_1,a_2,...,a_n$，$n+1$ 个人在第二排，身高为 $b_1,b_2,...,b_{n+1}$。

定义一种方案是好的当且仅当以下条件成立：

* $b_1>a_1$。
* $b_i>a_i$ 或 $b_i>a_{i-1}$，其中 $2\le i\le n$。
* $b_{n+1}>a_n$。

求有多少将 $a$ 重排的方案，使得可以将 $b$ 重排后得到一组好的方案。

* $n\le5000$。
* $a_i,b_i\leq10^9$，且任意 $a,b$ 元素不相等。

### 解法

挺神的 dp 题，但官方题解有些地方讲得不好（可能是我太菜了），我来做点补充，同时也参考了一下。

首先，转换一下条件。

令 $c$ 为一个长度为 $n+1$ 的序列，满足：

$$c_i=\begin{cases}a_1,i=1\\
\min\{a_{i-1},a_i\} ,2\leq i\leq n\\
a_n,i=n+1
\end{cases}$$

显然当且仅当把 $b$ 重排后满足任意 $c_i<b_i$ 的方案是好的，这又等价于 $b,c$ 升序排列后满足 $c_i<b_i$。若有 $c_i>b_i$，则满足大于 $c_i$ 的 $b_i$ 只有 $n+1-i$ 个，而 $c_i$ 有 $n+2-i$ 个，显然无论如何排列都不成立。以下默认 $c$ 已经升序排列。

对于一个 $a_i$，它作为 $c_i$ 当且仅当它比 $a_{i-1}$ 更小，也就是比 $a_{i-1}$ 更早加入。$c_{i+1}$ 同理。

所以，考虑从小到大找到 $a$ 中元素的位置。

设 $dp_{i,j}$ 是填完前 $i$ 个元素，共有 $j$ 个**连续段**的方案数。记录 $j$ 这一维是为了方便看出更新的 $c_k$ 是否满足要求。

填 $a_{i+1}$ 时，有以下三种情况：

* $a_{i+1}$ 在一个连续段的左或右侧，$dp_{i+1,j}\leftarrow  dp_{i+1,j}+dp_{i,j}\times 2\times j$。
* $a_{i+1}$ 将两个连续段连接起来，$dp_{i+1,j-1}\leftarrow dp_{i+1,j-1}+dp_{i,j}\times (j-1)$。
* $a_{i+1}$ 新建一个连续段，$dp_{i+1,j+1}\leftarrow dp_{i+1,j+1}+dp_{i,j}\times (j+1)$。因为后面的操作会唯一确定 $a_i$ 的位置，所以实际上只用分插到哪两个连续段的中间或者开头、结尾，有 $j+1$ 种方案。

然后再考虑限制，在 $a_{i+1}$ 被填前面已经有 $i+j$ 个被确定的 $c$ 中的元素。先将 $b$ 升序排序，同样分三种情况：

* $a_{i+1}$ 在一个连续段的左或右侧，此时新确定了 $c_{i+j+1}=a_{i+1}$，要比 $b_{i+j+1}$ 小，即 $a_{i+1}<b_{i+j+1}$。

* $a_{i+1}$ 将两个连续段连接起来，此时没有新确定的元素，就是没有限制。

* $a_{i+1}$ 新建一个连续段，此时 $c_{i+j+1}=c_{i+j+2}=a_{i+1}$ 要分别小于 $b_{i+j+1},b_{i+j+2}$。注意到 $b_{i+j+1}<b_{i+j+2}$，所以限制相当于 $a_{i+1}<b_{i+j+1}$。可以和第一种情况整合。

答案就是 $dp_{n,1}$，初值自然是 $dp_{0,0}=1$。

时空复杂度 $O(n^2)$。

顺便说一句，建议评紫。

### 代码
其实还挺短的。代码中 $p$ 表示连通块的变化量。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int n, dp[5005][5005], a[5005], b[5005];
signed main(){
    cin >> n;
    for(int i = 1; i <= n; i++)
    	cin >> a[i];
    for(int i = 1; i <= n + 1; i++)
    	cin >> b[i]; 
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 2);
    dp[0][0] = 1;
    for(int i = 0; i < n; i++)
    	for(int j = 0; j <= i; j++)
			for(int p = -1; p <= 1; p++){
				if(p + j <= 0 || p + j + i > n + 1) continue;
				if(p >= 0 && b[i + 1 + j] < a[i + 1]) continue;
				int l;
				if(p == -1) l = j - 1;
				else if(p == 0) l = 2 * j;
				else l = j + 1;
				(dp[i + 1][j + p] += dp[i][j] * l) %= mod;
			}
    cout << dp[n][1];
    return 0;
}
```

---

## 作者：drowsylve (赞：2)

一道 wygzgyw 老师上课讲的题。

注意到确定下第一排的顺序后，第二排的最优策略即从小到大插空放，在确定第一排的过程中判断即可。

考虑按 $a$ 从小到大的顺序，依次加入到排列中。当前的排列会形如若干个连续段（链）。如果我们考虑到第 $i$ 个点，它们构成了 $j$ 个连续段，显然每个连续段贡献的可以插的空是确定的，当前共有 $i+j+1$ 个空应当插入了 $b$。

令 $f_{i,j}$ 表示加入了前 $i$ 小的 $a$，构成了 $j$ 个连续段时的合法方案数。

每次转移加入一个新的 $a_{i}$，讨论是将两条连续段合并在一起，还是将某个连续段增长 $1$，还是成为一条的连续段。

合并连续段时，由于两个连续段的左右两端能插入的空位都在此前被考虑过了，而当前的 $a_i$ 又大于之前的 $a$，一定不会使得某个合法的方案变得不合法。所以直接合并，每两个相邻连续段之间都可以选择。有 $f_{i,j} \times (j-1) \to f_{i+1,j-1} $。

选择加入某个连续段的一端，则需要满足接下来选的 $a$ 必须小于当前最小的 $b$，因为此时只有最靠边的这一个 $a$ 会对 $b$ 有限制。每一段都有左右两个端点可以选择，有 $f_{i,j} \times j \times 2 \to f_{i+1,j}$。

新建一个连续段，则当前 $a$ 同样需要满足对 $b$ 的限制。由于 $b$ 同样升序排列，所以只要满足下一个 $b$，再下一个 $b$ 也一定满足。有 $f_{i,j} \times (j+1) \to f_{i+1,j+1}$。

最后答案应全部合为一段，显然为 $f_{n,1}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005;
const int mod=998244353;
int n,a[N],b[N];
int f[N][N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n+1;i++) cin>>b[i];
	sort(a+1,a+1+n);
	sort(b+1,b+1+n+1);
	f[0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=i;j++){
			if(!f[i][j]) continue;
			f[i+1][j-1]=(f[i+1][j-1]+f[i][j]*(j-1)%mod)%mod;
			if(a[i+1]>=b[i+j+1]) continue; 
			f[i+1][j]=(f[i+1][j]+f[i][j]*(2*j)%mod)%mod;
			f[i+1][j+1]=(f[i+1][j+1]+f[i][j]*(j+1)%mod)%mod;
		}
	}
	cout<<f[n][1];
	return 0;
}

```

---

## 作者：cqbzlzm (赞：1)

### Description

令 $a_0,a_{n+1}$ 为无穷大，求有多少种 $a$ 数组的排列方式，使得存在一种 $b$ 数组的排列方式，且 $b_i>\min(a_{i-1},a_i)$。

**数据规模：**$n\leq5000$。

### Solution

我们先考虑暴力该怎么做。显然，我们先将 $b$ 数组从小到大排序，然后我们枚举 $a$ 数组的所有排列，令 $c_i=\min(a_{i-1},a_i)$，将 $c$ 数组从小到大排序后，看能不能一一对应 $b$ 数组。

然后再看正解。我们注意到 $c$ 取决于 $a$，而且 $c$ 最终是要排序的。那么我们能不能考虑先将 $a$ 排序，然后我们把 $a$ 一个一个放进去。这样我们在放 $a$ 的过程中会产生新的相邻的 $a$，所以就会产生新的 $c$。又因为我们加入 $a$ 的顺序是按照从小到大加入的，所以 $c$ 一定会取决于先加进去的 $a$，那么 $c$ 也是从小到大确定的。

假设我们现在加入了 $a$ 的从小到大前 $i$ 个数，构成了 $j$ 个连通块。（之所以要 $j$，是因为后加的 $a$ 一定大于以前所有加进去的 $a$，所以块之间的相对位置不重要，我们只需要考虑新加的 $a$ 是否于先前加入的相邻）。

所以我们设 $dp_{i,j}$ 表示上述情况的添加 $a$ 的方案数。考虑三种情况：

- 新加的 $a$ 只与原来的一段相邻：$dp_{i+1,j}\leftarrow dp_{i,j}\times 2j$。这个操作会更新一个 $c$，又因为在 $dp_{i,j}$ 的状态下已经确定了 $i+j$ 个 $c$，所以我们要求 $a_{i+1}<b_{i+j+1}$。

- 新加的 $a$ 将原来两端不相连的连接起来：$dp_{i+1,j-1}\leftarrow dp_{i,j}\times(j-1)$。这个操作不会改变 $c$，所以没有限制。

- 新加的独成一段：$dp_{i+1,j+1}\leftarrow dp_{i,j}\times(j+1)$。这个操作会添加两个 $c$，所以要求 $a_{i+1}<b_{i+j+1}$ 且 $a_{i+1}<b_{i+j+2}$，综合一下，得到 $a_{i+1}<b_{i+j+1}$。

**Q：**为什么添加 $a$ 的时候不考虑新加的数到底放在那里？

**A：**因为它的位置会一步一步被确定下来，最终答案 $dp_{n,1}$ 会将放的位置定死。
 
### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int read() {
    int x = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
    return f ? -x : x;
}
const int MAXN = 5000, mod = 998244353;
int n, ans;
int a[MAXN + 5], b[MAXN + 5];
int dp[MAXN + 5][MAXN + 5];
signed main() {
    n = read();
    for (int i = 1; i <= n; i ++) a[i] = read();
    for (int i = 1; i <= n + 1; i ++) b[i] = read();
    sort(b + 1, b + 1 + n + 1);
    sort(a + 1, a + 1 + n);
    dp[0][0] = 1;
    for (int i = 0; i <= n; i ++) {
        for (int j = 0; j <= i; j ++) {
            if (b[i + j + 1] > a[i + 1]) {
                (dp[i + 1][j] += dp[i][j] * j * 2  ) %= mod;
                (dp[i + 1][j + 1] += dp[i][j] * (j + 1)  ) %= mod;
            }
            (dp[i + 1][j - 1] += dp[i][j] * (j - 1)   ) %= mod;
            
        }
    }
    printf("%lld", dp[n][1]);
    return 0;
}
```



---

## 作者：james1BadCreeper (赞：1)

序列可以重排列，直接按照顺序递推便不太能做。但是要钦定一个顺序，发现按值的大小很适合。如果你做过 [P5999](https://www.luogu.com.cn/problem/P5999)，那便不难想到插入法。

设 $f_{i,j}$ 代表填前 $i$ 个元素，有 $j$ 个段满足原题条件的方案数，考虑 $a_{i+1}$ 填到哪里（此时 $b$ 应该填 $b_{i+j+1}$）：

- 将其放到一个连续段的左侧或者右侧，$f_{i+1,j}\stackrel{+}{\leftarrow}f_{i,j}\times 2\times j$，需要满足 $b_{i+j+1}>a_i$ 才能满足条件；
- 合并两个连续段，$f_{i+1,j-1}\stackrel{+}{\leftarrow}f_{i,j}\times (j-1)$，没有任何条件就可以转移；
- 新增一个连续段，$f_{i+1,j+1}\stackrel{+}{\leftarrow}f_{i,j}\times (j+1)$，需要满足 $\min\{b_{i+j+1},b_{i+j+2}\}>a_i$。


$a,b$ 均从小到大排序即可转移。


```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 998244353; 
inline void add(int &x, int t) { x += t; x -= x >= P ? P : 0; }

int n; 
int a[5005], b[5005]; 
int f[5005][5005]; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n; 
    for (int i = 1; i <= n; ++i) cin >> a[i]; 
    for (int i = 1; i <= n + 1; ++i) cin >> b[i]; 
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 2); 
    f[0][0] = 1; 
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j) {
            if (j) add(f[i + 1][j - 1], f[i][j] * (j - 1ll) % P); 
            if (b[i + j + 1] > a[i + 1]) {
                add(f[i + 1][j], 2ll * f[i][j] * j % P); 
                add(f[i + 1][j + 1], f[i][j] * (j + 1ll) % P); 
            }
        }
    cout << f[n][1] << "\n"; 
    return 0; 
}
```

---

## 作者：苏联小渣 (赞：0)

考虑给定 $a$，如何判定是否存在 $b$。容易得到 $n+1$ 个下界，考虑把下界从大到小排序，设为 $c_i(c_1 \ge c_2 \ge ... \ge c_{n+1})$，那么对于每一个 $c_i$，都需要满足 $b$ 中比 $c_i$ 大的数的个数 $\ge i$，不然 $i$ 这个位置就没法填数了。这个转化在很多计数题里面都有。

由于下界是由较小的 $a_i$ 决定的，于是考虑把 $a_i$ 从大到小排序，然后找到一个刻画填数过程的方式来 dp。填到 $a_i$ 的时候，假设当前已经填入序列的有 $k$ 个相邻数对，那么就是说有 $k$ 个 $b_i$ 要大于 $a_i$，$k$ 的上界就是 $b$ 中比 $a_i$ 大的数的个数，这个可以预处理出来，不妨设为 $d_i$。我们不妨把当前已经填入的连续段看作一个连通块，那么一条边就可以表示一个相邻数对，也就是说当前的边数要 $\le d_i$。为了方便我们在序列的最左和最后端加入两个 $+\infty$，初始时有两个点。我们考虑把 $a_i$ 加入到序列中有哪几种方式：

- 新建一个连通块；

- 连在一个连通块的左端或右端（含有 $+\infty$ 的连通块只能接一端）；

- 合并两个连通块。

根据连通块个数=点数-边数，我们知道了点数和边数就能知道连通块个数。于是可以考虑 dp，设 $f_{i,j}$ 表示从大到小填到第 $i$ 个数的时候，当前有 $j$ 条边（也就是相邻相等数对）的方案数。有 $j \le d_i$，令 $s=-j$ 表示连通块个数，根据上面三种方式有转移：

- 第一种：$f_{i,j} \gets f_{i-1,j} \times (s-2)$，因为可以插在任意两个相邻连通块中间；

- 第二种：$f_{i,j} \gets f_{i-1,j-1} \times (2s-2)$，表示连接在左端或右端，但要除去最左最右；

- 第三种：$f_{i,j} \gets f_{i-1,j-2} \times s$，因为原先的连通块个数为 $s+1$。

初始加入两个点表示 $+\infty$，则 $f_{2,0}=1$，最后 $f_{n+2,n+1}$ 就是答案。时间复杂度 $O(n^2)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, m, a[5010], b[5010], c[5010], f[5010][5010];
const int mo = 998244353;
void Add(int &x, int y){
	x = ((x + y >= mo) ? (x + y - mo) : (x + y));
}
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
	}
	for (int i=1; i<=n+1; i++){
		scanf ("%d", &b[i]);
	}
	sort (b+1, b+n+2);
	a[n+1] = a[m=n+2] = 1e9;
	sort (a+1, a+m+1, greater<int>());
	for (int i=3; i<=m; i++){
		c[i] = upper_bound(b+1, b+n+2, a[i]) - b;
		c[i] = n + 2 - c[i];
	}
	f[2][0] = 1;
	for (int i=3; i<=m; i++){
		for (int j=0; j<=c[i]; j++){
			int tot = i - j;//连通块个数 
			Add(f[i][j], 1LL*f[i-1][j]*(tot-2)%mo);//新建连通块 
			if (j) Add(f[i][j], 1LL*f[i-1][j-1]*(tot*2-2)%mo);//连在左右端 
			if (j >= 2) Add(f[i][j], 1LL*f[i-1][j-2]*tot%mo);//连接两个 
		}
	}
	printf ("%d\n", f[m][n+1]);
	return 0;
}
```

---

## 作者：SnowTrace (赞：0)

简单题。

假如我们已经确定了 $a_i$ 的顺序，那么显然我们 $b_i$ 可以贪心的放进去，也就是把最大的 $b_i$ 放到 $min(a_i,a_{i-1})$ 最大的位置，以此类推。我们其实并不在乎 $a_i$ 具体是怎么排的，而是关系 $min(a_i,a_{i-1})$ 中有哪些数

我们考虑根据这个简单的性质设计 $dp$。

套路地，考虑连续段 $dp$，我们从大往小插入并且维护插入过程中已经形成的连续段。那么本质上，我们是通过这种方式来确定每次的 $a_i$ 究竟产生了几个贡献，并且继续转移，我们把 $min(a_i,a_{i-1})$ 的数从大到小的确定，从而合法性也很好判断。

$dp_{i,j}$ 表示目前插完了 $a_1$ 到 $a_i$ 的所有元素，在序列中组成了 $j$ 个连续段。转移考虑三种：

$a_i$ 自己新开一段，$a_i$ 跟在某一段的最左边或者最右边，$a_i$ 把两个相邻的段拼起来。转移需要考虑能否成立，也就是考虑当前放进去的 $a_i$ 和目前考虑到的 $b_k$ 的大小关系，$k$ 的值容易计算。

注意到两边不大好处理，最终放在最左边和最右边的数都会额外产生一个贡献，那我们不妨一开始就设段数为 2 然后再做 dp。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int n;
int a[5005],b[5005];
int dp[5005][5005];
signed main(){
	cin >> n;
	for(int i = 1;i<=n;i++)cin >> a[i];
	for(int i = 1;i<=n+1;i++)cin >> b[i];
	dp[0][2] = 1;
	/*假设左右是两个特别大的数*/
	sort(a+1,a+1+n);sort(b+1,b+2+n);
	reverse(a+1,a+1+n);reverse(b+1,b+2+n);
	for(int i = 0;i<n;i++){
		for(int j = 2;j<=n+2;j++){
			int now = i+2-j+1;
			if(now<1 or now>n+1)continue;
			//往空隙里插一个
			dp[i+1][j+1] = (dp[i+1][j+1]+dp[i][j]*(j-1))%mod;
			//在边缘新增一个
			if(a[i+1]<b[now])dp[i+1][j] = (dp[i+1][j]+dp[i][j]*(2*j-2))%mod;
			if(now!=n+1 and a[i+1]<b[now] and a[i+1]<b[now+1]){
				dp[i+1][j-1] = (dp[i+1][j-1]+dp[i][j]*(j-1))%mod;
			}
		}
	}cout << dp[n][1] << endl;
	return 0;
}

```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc313_h)

**题目大意**

> 给定 $a_1\sim a_n,b_1\sim b_{n+1}$，重排 $a,b$ 使得 $b_i> \min(a_i,a_{i-1})$，求有多少可能的 $\{a_i\}$。
>
> 数据范围：$n\le 5000$。

**思路分析**

设 $c_i=\min(a_i,a_{i-1})$。

相当于从大到小排列 $c_i,b_i$ 使得对应位 $b>c$。

从大到小插入 $a_i$，每次插入时考虑左右邻居有几个被钦定，那么产生新的 $c$ 就是 $a_i$。

$f_{i,j}$ 表示插入了最大的 $i$ 个，其中有 $j$ 对邻居被锁定变成 $c$，降序排列 $b_i$ 即可 check。

降序排列 $b_i$，那么转移就是 $f_{i+1,j+k}=f_{i,j}(i+1-j)[b_{j+k}>a_j](1+[k=1])$。

其中 $k$ 表示新增多少 $c$，$k=1$ 可以选择哪边变成 $c$。

时间复杂度：$\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5005,MOD=998244353;
int a[MAXN],b[MAXN],n;
ll f[MAXN],g[MAXN]; //cnt of break
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n+1;++i) scanf("%d",&b[i]);
	sort(a+1,a+n+1,greater<int>());
	sort(b+1,b+n+2,greater<int>());
	f[0]=1;
	for(int i=1;i<=n;++i) {
		memset(g,0,sizeof(g));
		for(int j=0;j<i;++j) if(f[j]) {
			ll t=f[j]*(i-j);
			g[j]=(g[j]+t)%MOD;
			if(b[j+1]>a[i]) g[j+1]=(g[j+1]+2*t)%MOD;
			if(b[j+2]>a[i]) g[j+2]=(g[j+2]+t)%MOD;
		}
		memcpy(f,g,sizeof(f));
	}
	printf("%lld\n",f[n+1]);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑从大到小插入 $a_i$ 判断合法性。

考虑连续段 dp，设计 $dp_{i,j}$ 表示目前看到第 $i$ 小的 $a_i$，所有 $a_i$ 形成 $j$ 个连续段，目前存在符合要求的 $b$ 的方案数。

不难发现显然会将 $(n-i+1)-j$ 个最大的 $b_i$ 先塞进去。

考虑对于每个 $a_i$，求出他能要的最小的 $b_i$ 是第几小的。通过这个，容易算出 $j$ 这一维的条件（形如 $j\geq x$，具体留给读者自行推导，可见代码）。只要转移到的 $j$ 符合要求，就可以按经典连续段 dp 的系数转移了。

出于方便，可以最初在左右两边加上一个很大的 $a_i$，即起始位置是 $dp_{n+1,2}=1$。

总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&(-i))
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
const int mod=998244353;
int dp[5005][5005];
signed main(){
	int n; cin>>n;
	int a[n+1],b[n+2],p[n+1];
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n+1;i++) cin>>b[i];
	sort(a+1,a+n+1); sort(b+1,b+n+2);
	for(int i=n;i>=1;i--) p[i]=n-(lower_bound(b+1,b+n+2,a[i])-b)+2;
	dp[n+1][2]=1;
	for(int i=n;i>=1;i--){
		//(n-i+1)+(2-j)<=p[i]
		//j>=n-i-p[i]+3 
		int minlim=n-i-p[i]+3;
		for(int j=1;j<=n;j++){
			if(j+1>=minlim) (dp[i][j+1]+=dp[i+1][j]*(j-1))%=mod;
			if(j>=minlim) (dp[i][j]+=dp[i+1][j]*2*(j-1))%=mod;
			if(j-1>=minlim) (dp[i][j-1]+=dp[i+1][j]*(j-1))%=mod;
		}
	}
	cout<<dp[1][1];
	return 0;
}
```

---

