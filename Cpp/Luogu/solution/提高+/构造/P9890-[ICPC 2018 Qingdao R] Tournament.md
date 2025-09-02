# [ICPC 2018 Qingdao R] Tournament

## 题目描述

DreamGrid，Gridland 的国王，正在举办一场骑士锦标赛。有 $n$ 名骑士，编号从 1 到 $n$，参加这次锦标赛。锦标赛的规则如下：

- 锦标赛由 $k$ 轮组成。每一轮由若干场决斗组成。每场决斗恰好在两名骑士之间进行。
- 每名骑士在每一轮中必须参加一场决斗。
- 对于每对骑士，在所有 $k$ 轮中最多只能有一场决斗。
- 设 $1 \le i, j \le k$，$i 
e j$，且 $1 \le a, b, c, d \le n$，$a, b, c, d$ 是四个不同的整数。如果
  - 骑士 $a$ 在第 $i$ 轮对战骑士 $b$，并且
  - 骑士 $c$ 在第 $i$ 轮对战骑士 $d$，并且
  - 骑士 $a$ 在第 $j$ 轮对战骑士 $c$，
- 那么骑士 $b$ 必须在第 $j$ 轮对战骑士 $d$。

作为 DreamGrid 的将军，你需要编写一个程序来安排所有 $k$ 轮中的所有决斗，以便结果安排满足上述规则。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
3 1
4 3```

### 输出

```
Impossible
2 1 4 3
3 4 1 2
4 3 2 1```

# 题解

## 作者：Alex_Wei (赞：2)

### [P9890 [ICPC2018 Qingdao R] Tournament](https://www.luogu.com.cn/problem/P9890)

构造好题。

因为任意一组构造在 $k$ 变小时依然适用，所以我们需要对每个 $n$ 找到有解的 $k$ 的最大值。

正向构造：

- 第一步：两两配对。因为编号可以任意排列，所以 $2k - 1$ 和 $2k$ 匹配是字典序最小的。如果不是 $2$ 的倍数，则办不到。
- 第二步：若 $1$ 和 $2k - 1$ 配对，则 $2$ 和 $2k$ 配对；反之若 $1$ 和 $2k$ 配对，则 $2$ 和 $2k - 1$ 配对。这相当于将 $2k - 1$ 和 $2k$ 看成一组，两组之间配对，总共可以贡献两轮。如果不是 $4$ 的倍数，则办不到。
- 以此类推，第 $i$ 步会将第 $i - 1$ 步的大小为 $2 ^ {i - 1}$ 的结构两两匹配，形成大小为 $2 ^ i$ 的结构并贡献 $2 ^ {i - 1}$ 轮，要求 $2 ^ i\mid n$。

综上，设 $p$ 为最大的能整除 $n$ 的 $2$ 的幂，即 $n$ 在二进制下最低位的 $1$，则 $k_{\max} = 1 + \cdots + 2 ^ {p - 1} = 2 ^ p - 1$​。注意上述推导只是感性理解，不构成严谨证明。可以尝试通过 “题述限制要求小结构合并时必须成对，得到大结构的大小为 $2$ 的幂” 的思路进行证明，具体细节留给读者思考。

反向构造：设 $f(a, b) = i$ 表示 $a$ 和 $b$ 在第 $i$ 轮决斗，则题述要求等价于：若 $f(a, b) = f(c, d) = i$ 且 $f(a, c) = j$，则 $f(b, d) = j$。根据 $f$ 的该种性质，容易想到一个合理的二元运算符：异或。令 $f(a, b) = (a - 1)\oplus (b - 1)$，则 $a$ 在第 $i$ 轮的对手为 $((a - 1) \oplus i) + 1$。这给出了 $i < 2 ^ p$ 时的构造：当 $i = 2 ^ p$ 时，$((n - 1)\oplus 2 ^ p) + 1 = ((n - 1) + p) + 1 = n + p$，不合法。

容易证明这样构造得到的是字典序最小解。

时间复杂度 $\mathcal{O}(n\cdot \min(n, k))$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;
using LL = __int128_t;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;

// ---------- templates above ----------

int n, k;
void solve(int T) {
  cin >> n >> k;
  if(k >= (n & -n)) cout << "Impossible\n";
  else {
    for(int i = 1; i <= k; i++) {
      for(int a = 1; a <= n; a++) {
        cout << ((a - 1) ^ i) + 1 << " ";
      }
      cout << "\n";
    }
  }
}

bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T = 1;
  cin >> T;
  while(T--) solve(T);
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：aleph_ (赞：1)

# P9890 题解

### 思路

我们把骑士按 $2$ 的幂次分组（分治），构造出循环赛日程表，然后开始找规律。

以下是大小为 $8$ 时的循环赛日程表：

```
2 1 4 3 6 5 8 7 
3 4 1 2 7 8 5 6 
4 3 2 1 8 7 6 5 
5 6 7 8 1 2 3 4 
6 5 8 7 2 1 4 3 
7 8 5 6 3 4 1 2 
8 7 6 5 4 3 2 1 
```

这里我删去了原表中的第一行，即 ```1 2 3 4 5 6 7 8```，因为自己不能和自己比赛。

对于每一个 $n$，它的最大比赛次数就是前 $n$ 列第一次出现大于 $n$ 的数的前一行。比如 $n=6$，那么 $k$ 最大为 $1$，因为第二行中出现了 $7$ 和 $8$。

我们列出最大比赛次数的表格：

| $n$ | 最大比赛次数 | $\operatorname{lowbit}(n)$ |
| :----------: | :----------: | :----------: |
| 1 | 0 | 1 |
| 2 | 1 | 2 |
| 3 | 0 | 1 |
| 4 | 3 | 4 |
| 5 | 0 | 1 |
| 6 | 1 | 2 |
| 7 | 0 | 1 |
| 8 | 7 | 8 |

可以观察到，最大比赛次数即 $\operatorname{lowbit(n)}-1$！

然后这个题就做完了。

### 补充

$\operatorname{lowbit(n)}$ 是取 $n$ 的二进制最低位，再减 $1$ 就是把二进制最右端连续的 $0$ 全部转化成 $1$，正好对应了 $2$ 的幂次分组的幂次和。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2005][2005];
void init(int n){
    if(n>=1024) return;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i+n][j+n]=a[i][j];
            a[i][j+n]=a[i+n][j]=a[i][j]+n;
        }
    }
    init(n*2);
}
int T,n,k;
int lowbit(int n){
    return n&-n;
}
int main(){
    a[1][1]=1;
    init(1);
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k>lowbit(n)-1){
            cout<<"Impossible"<<endl;
            continue;
        }
        for(int i=2;i<=k+1;i++){
            for(int j=1;j<=n;j++){
                cout<<a[i][j];
                if(j!=n) cout<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
```

---

## 作者：zheng_zx (赞：1)

## P9890 [ICPC2018 Qingdao R] Tournament

[题目传送门](https://www.luogu.com.cn/problem/P9890)

### 分析

---

一道找规律的~~水~~题。这道题我们可以用分治法打出循环赛日程表，然后找出规律，发现最多可进行 $\operatorname{lowbit}(n)-1$ 场比赛，再依次输出即可。

- 不知道 $\operatorname{lowbit}$ [函数](https://blog.csdn.net/czyzx/article/details/120875152)是啥的看这。

### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1030][1030], n, k, T;
int main() {
    for(int k = 1; k < 1024; k <<= 1)
        for(int i = 0; i < k; ++i)
            for(int j = 0; j < k; ++j)
                a[i + k][j] = a[i][j + k] = a[i][j] + k, a[i + k][j + k] = a[i][j];
    cin >> T;  
    while(T--){
        cin >> n >> k;
        if(k >= (n &- n))
            puts("Impossible");
        else {
            for(int i = 1; i <= k; ++i)
                for(int j = 0; j < n; ++j)
                    printf("%d%c", a[i][j]+1, " \n" [j == n - 1]);
        }
    }
    return 0;
}
```


---

## 作者：xueruhao (赞：0)

# P9890 [ICPC2018 Qingdao R] Tournament

[题目传送门](https://www.luogu.com.cn/problem/P9890)

[更好的阅读体验](https://www.cnblogs.com/xueruhao/p/18490020)

一道找规律的思维题。

## 前置知识 $\operatorname{lowbit}$

$\operatorname{lowbit}$ 用于获取一个二进制数中最右边的 $1$ 所代表的值。可以通过对一个数取反后加 $1$，再与原数进行按位与操作来实现。

```cpp
int lowbit(int x) {
    return x & -x;
}
```

例如：对于二进制数 $(11010)_2$（十进制 $26$），其 $\operatorname{lowbit}$ 为 $(10)_2$（十进制 $2$），即 $\operatorname{lowbit}(26) = 2$。

## Solve
其实题意说得已经非常清楚了，我们可以将骑士分成二幂次组，构造打出循环赛日程表，通过找规律不难发现最多进行 $\operatorname{lowbit}(n)-1$ 场比赛，最后依次输出即可。

And 至于为什么最多进行 $\operatorname{lowbit}(n)-1$ 场比赛，我想到了一段不严格的文字证明：在比赛中，每场比赛都会消除掉一个骑士，所以在给定人数为 $n$ 时，总的比赛次数就是将骑士数缩减为 $1$ 的过程。最多的比赛发生在每轮都尽可能减少最少人数的情况下，即每次比赛中淘汰 $\operatorname{lowbit}(n)$ 个骑士。因此，总的比赛次数为 $\operatorname{lowbit}(n) - 1$。

## Code

```cpp
#include <bits/stdc++.h>
#define N 2005

int A[N][N];
int T,n,k;

int lowbit(int x) {
	return x & -x;
}

int main() {
	A[1][1]=1;
	for(int k = 1; k < 1024; k *= 2) {
		for(int i = 1; i <= k; i++) {
			for(int j = 1; j <= k; j++) {
				A[i + k][j + k] = A[i][j];
				A[i][j + k]=A[i + k][j] = A[i][j] + k;
			}
		}
	}
	std::cin>>T;
	while(T--) {
		std::cin>>n>>k;
		if(k > lowbit(n) - 1) {
			std::cout<<"Impossible";
			puts("");
			continue;
		}
		for(int i = 2; i <= k + 1; i++) {
			for(int j = 1; j <= n; j++) {
				std::cout<<A[i][j]<<" ";
			}
			puts("");
		}
	}
	return 0;
}
```

over~

---

## 作者：immortal_immortals (赞：0)

## 题意：
$n$ 个骑士进行 $m$ 轮对决，每轮每个骑士都要有对手。且只能打一次。若 $a$ 与 $b$ 打，$c$ 与 $d$ 打， $a$ 与 $c$ 打，则 $b$ 必须和 $d$ 打。

## 思路：
将骑士分成二幂次组，然后在组内循环，`int lowbit(int x)` 取的是二进制最低位 $1$ 的位置，减一则最右端连续的 $0$ 转化成 $1$，正好对应二幂次分组的幂次和。
## 代码：
```
#include<bits/stdc++.h>
#define LL long long
#define INF INT64_MAX
#define MOD 998244353
#define ls rt << 1
#define rs rt << 1 | 1
using namespace std;
typedef pair<int,int>pa;
const int N = 1005;
#define lowbit(x) x&(-x)
int a[N][N];
char s[N];
int n, m, k, tt;
void solve(int len)
{
    for(int l = 1;l+2*len-1 <= n;l += 2*len)
	{
        for(int r = 1;r+2*len-1 <= n; r += 2*len)
		{
            for(int i = l;i <= l+len-1;i++)
			{
                for(int j = r;j <= r+len-1;j++)
				{
                    a[i+len][j+len] = a[i][j];
                }
            }
        }
    }
    for(int l = 1;l+2*len-1 <= n;l += 2*len)
	{
        for(int r = 2*len;r <= n;r += 2*len)
		{
            for(int i = l;i+len <= n;i++)
			{
                for(int j = r;j >= r-len+1;j--)
				{
                    //printf("i = %d %d %d\n", i, j, len);
                    a[i+len][j-len] = a[i][j];
                }
            }
        }
    }
}
int main()
{
    scanf("%d", &tt);
    while(tt--)
	{
        scanf("%d%d", &n, &k);
        if(n%2 || k > lowbit(n)-1) printf("Impossible\n");
        else
		{
            for(int j = 1;j <= n;j+=2)
			{
                a[1][j] = j;
                a[1][j+1] = j+1;
                a[2][j] = j+1;
                a[2][j+1] = j;
            }
            for(int i = 2;i <= n;i*=2)
			{
                if(n%i) break;
                solve(i);
            }
            for(int i = 2;i <= k+1;i++)
			{
                for(int j = 1;j <= n;j++)
				{
                    printf("%d", a[i][j]);
                    if(j!=n) printf(" ");
                }
                printf("\n");
            }
        }
    }
    return 0;
}
```

---

