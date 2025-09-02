# Balanced String

## 题目描述

You are given a binary string $ s $ (a binary string is a string consisting of characters 0 and/or 1).

Let's call a binary string balanced if the number of subsequences 01 (the number of indices $ i $ and $ j $ such that $ 1 \le i < j \le n $ , $ s_i=0 $ and $ s_j=1 $ ) equals to the number of subsequences 10 (the number of indices $ k $ and $ l $ such that $ 1 \le k < l \le n $ , $ s_k=1 $ and $ s_l=0 $ ) in it.

For example, the string 1000110 is balanced, because both the number of subsequences 01 and the number of subsequences 10 are equal to $ 6 $ . On the other hand, 11010 is not balanced, because the number of subsequences 01 is $ 1 $ , but the number of subsequences 10 is $ 5 $ .

You can perform the following operation any number of times: choose two characters in $ s $ and swap them. Your task is to calculate the minimum number of operations to make the string $ s $ balanced.

## 说明/提示

In the first example, the string is already balanced, the number of both 01 and 10 is equal to $ 1 $ .

In the second example, the string is already balanced, the number of both 01 and 10 is equal to $ 6 $ .

In the third example, one of the possible answers is the following one: 11010 $ \rightarrow $ 01110. After that, the number of both 01 and 10 is equal to $ 3 $ .

In the fourth example, one of the possible answers is the following one: 11001100 $ \rightarrow $ 11001010 $ \rightarrow $ 11000011. After that, the number of both 01 and 10 is equal to $ 8 $ .

## 样例 #1

### 输入

```
101```

### 输出

```
0```

## 样例 #2

### 输入

```
1000110```

### 输出

```
0```

## 样例 #3

### 输入

```
11010```

### 输出

```
1```

## 样例 #4

### 输入

```
11001100```

### 输出

```
2```

# 题解

## 作者：EuphoricStar (赞：14)

首先考虑一个子问题，给两个只含有 $0$ 和 $1$ 的字符串 $s, t$，求至少要使用多少次交换 $t$ 的任意两个字符的操作，使得 $s$ 与 $t$ 相等，或报告无解。

显然无解情况就是两个串 $0$ 或 $1$ 的出现次数不同。接下来我们排除相等的位置，设还剩 $k$ 个 $s_i = \texttt{0}, t_i = \texttt{1}$ 的位置和 $k$ 个 $s_i = \texttt{1}, t_i = \texttt{0}$ 的位置，每次选择一对 $(0, 1)$ 交换，答案就是 $k$。

回到原题，发现 $n \le 100$，那不就直接把题面中乱七八糟的条件塞进 dp 状态吗。设 $f_{i, j, k}$ 为 $t$ 中填完 $[1, i]$，填了 $j$ 个 $0$，当前 $\texttt{01}$ 子序列个数减去 $\texttt{10}$ 子序列个数 $= k$，$t$ 与 $s$ 不相等的位置个数的最小值。转移就枚举第 $i$ 个位置填 $0$ 还是 $1$，如果填 $1$，那么 $k$ 加上 $[1, i - 1]$ 中 $0$ 的个数，否则 $k$ 减去 $[1, i - 1]$ 中 $1$ 的个数。

时间复杂度 $O(n^4)$。

[code](https://codeforces.com/contest/1860/submission/219458338)

---

## 作者：TernaryTree (赞：8)

简单 dp 啊。$n\le 100$ 考虑直接 dp。

对于一个 $1$，它可以与前面所有 $0$ 组成 $01$，与后面所有所有 $0$ 组成 $10$。其贡献为后面 $0$ 个数减去前面 $0$ 个数。

如果是合法的那么所有 $1$ 的贡献总和是 $0$。

设 $f_{i,j,k}$ 表示 $1\sim i$ 里面有 $j$ 个 $1$，总贡献为 $k$ 的方案中与 $s_{1\sim i}$ 最小的不同个数。则有

$$f_{i,j,k}=\min(f_{i-1,j,k},f_{i-1,j-1,k-cnt_0+2(i-j)})$$

第一维显然可以滚动数组滚掉。

注意到贡献 $k$ 是 $\Theta(n^2)$ 的，并且有可能有负数，在处理的时候数组下标加上 $n^2$ 即可。

然后最小的不同个数怎么转换成操作次数呢，每次可以交换一对与答案序列相应位置不同的 $0,1$，一次交换即可消去两个相同位置不同的数，所以答案是 $\dfrac{f_{n,cnt_1,0}}2$。

时间复杂度 $\Theta(n^4)$，空间复杂度 $\Theta(n^3)$。

[Code](https://www.luogu.com.cn/paste/hvsvjxpz)

---

## 作者：Deamer (赞：7)

赛时没想出来 D dp 解法，写了个贪心赛后被 hack 了，无缘 CM ，现在发现 D 也不算难，写一篇题解反省一下。

我们注意到 $n≤100$ ，所以赛时猜到了正解的时间复杂度为 $O(n^4)$。

先考虑如何判断当前状态是否可行，我们考虑对于每一个 $1$，我们设它的贡献为它前面 $0$ 的个数减去它后面 $0$ 的个数，显然当前状态可行当且仅当所有 $1$ 的贡献之和为 $0$。

先来定义一些东西，$s$ 为原数组，$cnt0$ 为 $s$ 中 $0$ 的个数，$cnt1$ 为 $s$ 中 $1$ 的个数。

我们设 $f_{i,j,k}$ 表示前 $i$ 个数里面填完了 $j$ 个 $1$，贡献之和为 $k$ 的与 $s$ 前 $i$ 个数最小的不同个数。

考虑如何转移 $f_{i,j,k}=\min(f_{i-1,j,k}+[s_i=1],f_{i-1,j-1,k+2(i-j)-cnt0}+[s_i=0])$。

我们发现 $k$ 会出现负数的情况且 $k≤\frac{n \times n}{2}$，所以我们把 $k$ 在作为下标时都加上 $\frac{n \times n}{2}$ 即可。

因为最优解中的一次交换会导致一个位置上的 $1$ 变为 $0$，一个位置上的 $0$ 变为 $1$，所以答案为 $\frac{f_{n,cnt1,0}}{2}$。

由于 $f_i$ 转移时只依赖于 $f_{i-1}$，所以可以用滚动数组来优化空间复杂度。

时间复杂度为 $O(n^4)$，空间复杂度为 $n^3$。

~~readers : Talking is cheap , show me the code !!!~~

##  _Code_ 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e2+10;
const int INF=0x7f7f7f7f;
int n,m;
char s[N];
int a[N];
int f[N][N*N];

int main(){
	scanf("%s",s+1);
	n=strlen(s+1); m=n*n/2;
	int cnt=0;
	for(int i=1;i<=n;i++){
		a[i]=s[i]-'0';
		cnt+=!a[i];
	}
	memset(f,INF,sizeof(f));
	f[0][m]=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j>=0;j--){
			for(int k=-m;k<=m;k++){
				f[j][k+m]=f[j][k+m]+a[i];
				if(j) f[j][k+m]=min(f[j][k+m],f[j-1][k+m+2*(i-j)-cnt]+(!a[i]));
			}
		}
	}
	if(f[n-cnt][m]==INF) printf("-1\n");
	else printf("%d\n",f[n-cnt][m]/2);
	return 0;
}
```

[完结撒花！！！](https://www.luogu.com.cn/record/121826375)

Update : 2023.8.21 改了一些笔误。

---

## 作者：Autisia (赞：6)

在 Codeforces 上看到了这题的 $\mathcal{O}(n ^ 4 / \omega)$ 做法，和大家分享一下。

[原版 Solution 链接](https://codeforces.com/blog/entry/119504?#comment-1060285)

记 $d$ 为原字符串 $s$ 中 $01$ 和 $10$ 的个数差。

观察题目可以得到以下性质：

+ 不可能交换两个 $0$ 或两个 $1$，不可能在同一个位置上进行两次操作。

+ 当交换位置 $(p, q)$ 上的 $0$ 和 $1$ 时，$d$ 会增加或减少 $(p - q) \times 2$。

现在我们需要选出两个长度都为 $l$ 的 $s$ 的序列 $a$（选择交换的 $0$ 的下标）和 $b$（选择交换的 $1$ 的下标），在满足 $\sum_{i=1}^{k}{b_i - a_i} = d / 2$ 的条件下希望 $l$ 最小。

考虑对下标 DP，设 $f_{0 / 1,i , j, k} = 0 / 1$ 表示目前转移到 $0$ 或 $1$ 的第 $i$ 个位置，已经选择的下标之和为 $j$，选了 $k$ 个数是否可行。转移为：

```cpp
f[s][i + 1][j + i][k + 1] |= f[s][i][j][k]
f[s][i + 1][j][k] |= f[s][i][j][k]
```

最后求出最小的 $l$ 满足存在 $x$ 使 $f_{0, n, x, l} =1$ 且
$f_{1, n, x + d, l} = 1$。

这个 DP 是 $\mathcal{O}(n ^ 4)$ 的，注意到 $f$ 数组的取值为 $0$ 或 $1$，可以使用 bitset 将第三维压掉。设 bitset 数组 $g_{0/1, i, k}$ 为目前转移到 $0$ 或 $1$ 的第 $i$ 个位置，选了 $k$ 个数的下标之和的状态。转移为：

```cpp
g[s][i + 1][k + 1] |= g[s][i][k] << i
g[s][i + 1][k] |= g[s][i][k]
```

最后利用倒序枚举 $k$ 滚动第二位得转移方程为：

```cpp
g[s][k + 1] |= g[s][k] << i
```

复杂度为 $\mathcal{O}(n ^ 4/w)$。附上代码：

```cpp
#include <iostream>
#include <bitset>
#include <string.h>
#define gc getchar 
#define pc putchar
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <class Typ> Typ &read(Typ &x) {
    char ch = gc(), sgn = 0; 
    for(; !isdigit(ch); ch = gc()) sgn |= ch == '-';
    for(x = 0; isdigit(ch); ch=gc()) x = x * 10 + (ch ^ 48);
    return sgn && (x = -x), x;
}
template <class Typ> void write(Typ x) {
    if(x < 0) pc('-'), x = -x;
    if(x > 9) write(x / 10);
    pc(x % 10 ^ 48);
}
const int N = 110;
bitset<N * N / 2> pack[2][N];
char s[N];
int n, diff; 
int main() {
    scanf("%s", s + 1), n = strlen(s + 1);
    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= n; j++) {
            if(s[i] == '0' && s[j] == '1') diff++;
            if(s[i] == '1' && s[j] == '0') diff--;
        }
    diff >>= 1;
    pack[0][0][0] = 1, pack[1][0][0] = 1;
    for(int i = 1; i <= n; i++) for(int j = i - 1; j >= 0; j--)
        pack[s[i] - '0'][j + 1] |= pack[s[i] - '0'][j] << i;
    for(int i = 0; i <= n; i++) 
        for(int j = 0; j <= n * (n-1) >> 1; j++) if(j + diff >= 0) 
            if(pack[0][i][j] && pack[1][i][j + diff]) { 
                write(i), pc('\n');
                return 0;
            }
    return 0;
}
```



---

## 作者：masonpop (赞：3)

赛时想偏了。

前期考虑的是交换 01 产生的影响，然后发现如果交换 $i,j$ 影响是 $j-i$，并由此设计了一个背包然后假掉了。之后发现完全没必要。

考虑暴力计算 01 和 10 对的个数。首先，对于每个 $a_i=1$ 的位置 $i$，它前面有 $i-1$ 个位置可能和它产生 01 对。但是这样多算了所有 11 组合，需要减掉。10 组合同理。

交换不改变元素个数。设开始 $1$ 的个数是 $t$。那么有 $\sum\limits_{a_i=1}(i-1)-\frac{t(t-1)}{2}=\sum\limits_{a_i=0}(i-1)-\frac{(n-t)(n-t-1)}{2}$。

化简一下，即为 $2\sum\limits_{a_i=1}i=\frac{t(t+1)}{2}-\frac{(n-t)(n-t+1)}{2}+\frac{n(n+1)}{2}$。

可得 $\sum\limits_{a_i=1}i=\frac{(n+1)t}{2}$。

这个式子显然可以 dp。设 $f_{i,j,k}$ 表示考虑到前 $i$ 个位置，填了 $j$ 个 $1$，且填的 $1$ 的下标和为 $k$ 时最少有多少个位置填了 $1$ 但原数列中是 $0$。（注意到，这个值即为最小需要交换数）

由于 $k$ 是 $n^2$ 级别的，因此 dp 过程是 $O(n^4)$ 的。由于空间消耗较大因此压掉第一维即可。[代码](https://codeforces.com/contest/1860/submission/219382149)

---

## 作者：eastcloud (赞：2)

赛时脑抽，以为做法假了（恼）。

看到数据范围 $n\le 100$，一般来说是个多状态的 dp，考虑直接把题目中给的条件直接塞到转移式里。

假设目前已经处理到了第 $i$ 位，我们需要的信息就是已经填完的某种数的个数和目前已经存在的某种数对的个数，以此设计转移，这里提供一种比较简洁的做法（来自 jiangly 佬的赛时做法）：

设计 $f_{i,j,k}$ 表示目前已经处理到了第 $i$ 位，已经填完了 $j$ 个 1，01 和 11 数对共有 $k$ 个，转移式即为 $f_{i,j,k} + [s_i=0] \rightarrow f_{i+1,j+1,k+i}$，倒序枚举可以优化掉第一维，答案状态是显然的。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector> 
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
int f[110][5100];
int main(){
	string s;cin>>s;
	int len=s.length(),cnt=0;
	for(int i=0;i<len;i++)cnt+=(s[i]=='1');
	int need=len*(len-1)/2+cnt*(cnt-1)/2-(len-cnt)*(len-cnt-1)/2;need/=2;
	for(int i=0;i<len;i++)for(int j=0;j<=need;j++)f[i][j]=inf;
	f[0][0]=0;
	for(int i=0;i<len;i++){
		for(int j=cnt-1;j>=0;j--){
			for(int k=0;k<=need-i;k++){
				f[j+1][k+i]=min(f[j+1][k+i],f[j][k]+(s[i]=='0'));
			}
		}
	}
	cout<<f[cnt][need];
}
```


---

## 作者：yuanruiqi (赞：1)

## 题意

给定一个 01 串，求最少的交换次数使得串内的 10 子序列和 01 子序列数量相同。

## 分析

不难发现一次必要的交换一定选择了两个字符不同的位置，那样就相当于将串中的一个 1 变成 0，一个 0 变成 1 了。不妨先考虑另一个问题，最小化翻转的数量。~~笔者赛时看错了题意，理解成这样，于是猛烈下分。~~

将一个 1 翻转成 0 后，对 10 子序列的贡献是前面 1 的数量与后面 0 的数量之差。对 01 的贡献是后面 1 与前面 0 的差。为了方便计算，我们只需要考虑 10 和 01 子序列数量差即可。记该位置为 $i$，字符串长度为 $n$，作差可得贡献为 $(i - 1) - (n - i) = 2i - n - 1$ 。同理将 0 翻转成 1 的贡献为 $(n-i)-(i-1)=n-2i+1$。既然每个位置最多只会被翻转一次，那么 01 背包就可以完成。

本题可不可以直接转化为上面的问题呢？答案是不可以。因为我们需要保证被翻转的 0 的数量等于被翻转的 1 的数量。而只进行一个 01 背包是无法保证的。这时我们观察到数据范围极小，$n \leq 100$，于是可以考虑再记录一维状态。具体的，$f_{i,j,k}$ 表示考虑到第 $i$ 位，已经被翻转的 1 的数量与被翻转的 0 的数量的差为 $j$，当前 10 子序列的数量与 01 子序列数量的差为 $k$。$i$ 和 $j$ 都是 $O(n)$ 级别的，$k$ 是 $O(n^2)$ 级别的，每次转移只需要 $O(1)$，那么我们就能以 $O(n^4)$ 的复杂度完成本题。实现上需要注意的是 $j$ 和 $k$ 可能取到负数。

## 代码

[代码](https://codeforces.com/contest/1860/submission/219393939)

---

## 作者：Xy_top (赞：0)

简单的 dpt，VP 时做了 ABC 然后就到要去上课的点了，就没做这题。

思考一下状态是什么样子的，首先必定有一个 $i$ 是当前考虑到字符串的第 $i$ 位，其次如果要统计 ``01`` 和 ``10`` 的方案数，还要记录一下 $1$ 和 $0$ 的数量，然而只需要记录一个就行了，可以反推出另一个。

至此，状态已达 $n^2$，还可以再加，如果再加那么只有可能是当前字符串中 ``01`` 的个数减去 ``10`` 的个数了，但是值存什么呢？显然存当前考虑出来的字符串与原字符串最少有几个位置不同。

转移也很显然：观察 $f_{i,j,k}$ 能变成哪些。

当前填 $1$，$i$ 前面 $0$ 的个数为 $i-j$，所以新产生了 $i-j$ 对 ``01``，于是转移成 $f_{i+1,j+1,k+i-j}$，需不需要加一看 $s$ 这一位。

当前填 $0$，$i$ 前面有 $j$ 个 $1$，新产生了 $j$ 对 ``10``，转移成 $f_{i+1,j,k-j}$。

答案也很简单，如果最后的字符串有 $c$ 个位置与给定字符串不同，那么需要 $\frac{c}{2}$ 次交换，$c$ 显然是偶数。

另外，$k$ 有可能小于 $0$，所以将它加上 $n^2$ 后再处理即可。

简单的 dpt，状态设计就是把所有东西往上硬塞，代码也很好写：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define int long long
using namespace std;
char s[105];
int cnt0, cnt1;
int f[2][101][20001];//填到第 i 位，j 个 1，贡献总和为 k 
signed main () {
	memset (f, 0x3f, sizeof f);
	scanf ("%s", s + 1);
	int len = strlen (s + 1);
	f[0][0][len * len] = 0;
	For (i, 1, len) { 
		if (s[i] == '1') ++ cnt1;
		else ++ cnt0;
	}
	For (i, 0, len - 1) {
		int x = (i & 1) ^ 1;
		For (j, 0, 100) For (k, 0, 20000) f[x][j][k] = 200;
		For (j, 0, min (i, cnt1) ) {
			For (k, 0, 2 * len * len) {
				if (f[i & 1][j][k] > 100) continue;
				//填 1
				if (s[i + 1] == '1') f[x][j + 1][k + i - j] = min (f[x][j + 1][k + i - j], f[i & 1][j][k]);//1 0 的贡献是 + 1，0 1 的贡献是 -1
				else f[x][j + 1][k + i - j] = min (f[x][j + 1][k + i - j], f[i & 1][j][k] + 1);
				//填 0
				if (s[i + 1] == '1') f[x][j][k - j] = min (f[x][j][k - j], f[i & 1][j][k] + 1);
				else f[x][j][k - j] = min (f[x][j][k - j], f[i & 1][j][k]);
			}
		}
	}
	cout << f[len & 1][cnt1][len * len] / 2;
	return 0;
}
```


---

