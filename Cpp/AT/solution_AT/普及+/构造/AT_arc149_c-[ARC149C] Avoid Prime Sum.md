# [ARC149C] Avoid Prime Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc149/tasks/arc149_c

正整数 $ N $ が与えられます．

$ N $ 行 $ N $ 列からなるマス目の各マスに $ N^2 $ 以下の正整数を $ 1 $ つずつ書き込んで，以下の条件がすべて成り立つようにしてください．

- 上下左右の $ 4 $ 方向いずれかに隣接する $ 2 $ マスに書き込まれた正整数の和は，どれも素数ではない．
- $ N^2 $ 以下の正整数はすべてどれかのマスに $ 1 $ 度ずつ書き込まれている．

なお本問題の制約のもと，このような書き込み方が必ず存在することが証明できます．

## 说明/提示

### 制約

- $ 3\leq\ N\leq\ 1000 $

### Sample Explanation 1

このマス目には $ 1 $ 以上 $ 16 $ 以下の正整数がすべて $ 1 $ 度ずつ書き込まれています．また隣接する $ 2 $ マスに書き込まれた正整数の和には $ 15+11=26 $, $ 11+16=27 $, $ 15+13=28 $ などがありますが，これらはすべて素数ではありません．

## 样例 #1

### 输入

```
4```

### 输出

```
15 11 16 12
13 3 6 9
14 7 8 1
4 2 10 5```

# 题解

## 作者：APJifengc (赞：4)

首先可以想到，假如我们把奇数放一半，偶数放一半，这样就只用考虑边界地方了。

![](https://img.atcoder.jp/arc149/386dd470603f65be4fbb8dcf45db8cad.png)

所有题解都提到了这一点。接下来，我们需要构造一种方案。

构造？狗都不构造。考虑合数本来就很多，我们直接每次随机一个奇数一个偶数，如果加起来不是质数就直接填。这样做只有 $n=3$ 的时候跑不出来，手动构造一下就行。

最慢的点跑了 500ms，轻松通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
int n;
bool vis[2 * MAXN * MAXN];
bool isprime[2 * MAXN * MAXN];
bool check(int x) {
    for (int i = 2, d = sqrt(x); i <= d; i++) if (x % i == 0) 
        return false;
    return true;
}
int ans[MAXN][MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n * n; i++)
        isprime[i] = check(i);
    mt19937 Rand(time(0) ^ clock());
    if (n % 2 == 0) {
        for (int i = 1; i <= n; i++) {
            int a = Rand() % (n * n) + 1, b = Rand() % (n * n) + 1;
            while (a % 2 == 0 || b % 2 == 1 || vis[a] || vis[b] || isprime[a + b]) {
                a = Rand() % (n * n) + 1, b = Rand() % (n * n) + 1;
            }
            vis[a] = vis[b] = 1;
            ans[n / 2][i] = a, ans[n / 2 + 1][i] = b;
        }
        int now = 1;
        for (int i = 1; i < n / 2; i++) {
            for (int j = 1; j <= n; j++) if (!ans[i][j]) {
                while (vis[now]) now += 2;
                ans[i][j] = now;
                now += 2;
            }
        }
        now = 2;
        for (int i = n / 2 + 2; i <= n; i++) {
            for (int j = 1; j <= n; j++) if (!ans[i][j]) {
                while (vis[now]) now += 2;
                ans[i][j] = now;
                now += 2;
            }
        }
    } else {
        if (n == 3) {
            printf("5 3 1\n9 7 8\n6 2 4\n");
            return 0;
        }
        int mid = (n + 1) / 2;
        for (int i = 1; i <= n; i++) {
            int a = Rand() % (n * n) + 1, b = Rand() % (n * n) + 1;
            while (a % 2 == 0 || b % 2 == 1 || vis[a] || vis[b] || isprime[a + b] || (i == mid + 1 && isprime[ans[mid][mid] + b])) {
                a = Rand() % (n * n) + 1, b = Rand() % (n * n) + 1;
            }
            vis[a] = vis[b] = 1;
            if (i <= n / 2 + 1) {
                ans[mid][i] = a, ans[mid + 1][i] = b;
            } else {
                ans[mid - 1][i] = a, ans[mid][i] = b;
            }
        }
        int now = 1;
        for (int i = 1; i < mid; i++) {
            for (int j = 1; j <= n; j++) if (!ans[i][j]) {
                while (vis[now]) now += 2;
                ans[i][j] = now;
                now += 2;
            }
        }
        for (int i = 1; i <= mid; i++) if (!ans[mid][i]) {
            while (vis[now]) now += 2;
            ans[mid][i] = now;
            now += 2;
        }
        now = 2;
        for (int i = mid + 1; i <= n; i++) if (!ans[mid][i]) {
            while (vis[now]) now += 2;
            ans[mid][i] = now;
            now += 2;
        }
        for (int i = mid + 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) if (!ans[i][j]) {
                while (vis[now]) now += 2;
                ans[i][j] = now;
                now += 2;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Jasonshan10 (赞：1)

## 题意

- 构造 $1$ 种方案，用 $1∼n^2$ 这 $n^2$ 个数填充一个 $n\times n$ 的方格。

- 满足任意两个相邻的数的和不为质数。

## 思路

- 首先有一个很显然的思路，就是**奇数放上面**，**偶数放下面**，这样我们只需要判断中间情况即可。

- 接着，我们发现，只要在中间的奇数和偶数都是 $3$ 的倍数，就能满足中间的两个数之和也是 $3$ 的倍数，构造完毕。

- 如果 $n$ 为偶数，那么中间填充方式如图所示（以 $n=6$ 为例）

![](https://cdn.luogu.com.cn/upload/image_hosting/lrxikjqo.png)

- 如果 $n$ 为奇数，那么中间填充方式如图所示（以 $n=7$ 为例）

![](https://cdn.luogu.com.cn/upload/image_hosting/0jepyz6x.png)

- 这里注意，这种方法只适用于 $n>5$ 的情况，若 $n\le 5$，则需要特殊判断。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=1e3+5;
int a[MAXN][MAXN];
set<int> s1;
int main(){
	int n;
	scanf("%d",&n);
	if (n==3){
		printf("5 3 1\n");
		printf("9 7 8\n");
		printf("6 2 4\n");
	}
	else if (n==4){
		printf("15 11 16 12\n");
		printf("13 3 6 9\n");
		printf("14 7 8 1\n");
		printf("4 2 10 5\n");
	}
	else if (n==5){
		printf("7 9 11 13 15\n");
		printf("17 19 25 5 21\n");
		printf("23 3 1 20 4\n");
		printf("2 22 24 6 8\n");
		printf("10 12 14 16 18\n");	
	}
	else{
		if (n%2==0){
			int now=3;
			for(int i=1;i<=n;++i){
				a[n/2][i]=now;
				s1.insert(now);
				now=now+6;
			}
			now=1;
			for(int i=1;i<n/2;++i){
				for(int j=1;j<=n;++j){
					while (s1.count(now)!=0){
						now=now+2;
					}
					a[i][j]=now;
					now=now+2;
				}
			}
			now=6;
			for(int i=1;i<=n;++i){
				a[n/2+1][i]=now;
				s1.insert(now);
				now=now+6;
			}
			now=2;
			for(int i=n/2+2;i<=n;++i){
				for(int j=1;j<=n;++j){
					while (s1.count(now)!=0){
						now=now+2;
					}
					a[i][j]=now;
					now=now+2;
				}
			}
			for(int i=1;i<=n;++i){
				for(int j=1;j<=n;++j){
					printf("%d ",a[i][j]);
				}
				printf("\n");
			}	
		}
		else{
			int now=3;
			for(int i=n/2+2;i<=n;++i){
				a[n/2][i]=now;
				s1.insert(now);
				now=now+6;
			}
			for(int i=1;i<=n/2+1;++i){
				a[n/2+1][i]=now;
				s1.insert(now);
				now=now+6;
				
			}
			now=1;
			for(int i=1;i<=n/2-1;++i){
				for(int j=1;j<=n;++j){
					while (s1.count(now)!=0){
						now=now+2;
					}
					a[i][j]=now;
					now=now+2;
				}
			}
			for(int i=1;i<=n/2+1;++i){
				while (s1.count(now)!=0){
					now=now+2;
				}
				a[n/2][i]=now;
				now=now+2;
			}
			now=6;
			for(int i=n/2+2;i<=n;++i){
				a[n/2+1][i]=now;
				s1.insert(now);
				now=now+6;
				
			}
			for(int i=1;i<=n/2+1;++i){
				a[n/2+2][i]=now;
				s1.insert(now);
				now=now+6;
				
			}
			now=2;
			for(int i=n/2+2;i<=n;++i){
				while (s1.count(now)!=0){
					now=now+2;
				}
				a[n/2+2][i]=now;
				now=now+2;
			}
			for(int i=n/2+3;i<=n;++i){
				for(int j=1;j<=n;++j){
					while (s1.count(now)!=0){
						now=now+2;
					}
					a[i][j]=now;
					now=now+2;
				}
			}
			for(int i=1;i<=n;++i){
				for(int j=1;j<=n;++j){
					printf("%d ",a[i][j]);
				}
				printf("\n");
			}
		}
	}
	return 0;
}

```

---

## 作者：Priestess_SLG (赞：0)

考虑对 $n$ 的奇偶性分类讨论答案。

**I. $n$ 是偶数**

此时把上面的 $\frac n2$ 行构造奇数，下面的 $\frac n2$ 行构造偶数。可以证明此时上 $\frac n2$ 行和下 $\frac n2$ 行各自内部相邻两个数的和一定不为质数（都是不为 $2$ 的偶数）。因此只需要考虑第 $\frac n2$ 行和第 $\frac n2+1$ 行之间上下相邻两个格子之间的关系。容易想到构造让她们之间的和都为 $3$ 的倍数，那么直接把所有 $3$ 的倍数的数拿出来分奇偶放入两个数组中，先填写这两行，然后用剩下的元素填写剩下的 $n-2$ 行即可。

特殊的，$n$ 很小的时候该构造显然不对，需要单独 DFS 搜索出答案。

**II. $n$ 是奇数**

也是类似的。特殊的地方在于此时边界线分为三段，由左下 - 右上排列。也是类似的方法构造 $3$ 的倍数即可。

代码，比较复杂，但是除了奇数情况的边界条件以外没有什么容易出错的点。

```cpp
#pragma GCC optimize(3, "Ofast", "inline") 
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
const int N = 2000010;
int n;
int pr[N], isp[N], idx, vis[N];
int mp[2010][2010];
void sieve() {
    for (int i = 2; i < N; ++i) {
        if (!isp[i]) pr[++idx] = i;
        for (int j = 1; j <= idx && i * pr[j] < N; ++j) {
            isp[i * pr[j]] = 1;
            if (i % pr[j] == 0) break;
        }
    }
}
int ok = 0;
int Visit[N];
void dfs(int x, int y) {
    if (ok) return;
    if (x == n + 1) {
        ok = 1;
        return;
    }
    for (int i = 1; i <= n * n; ++i)
        if (!Visit[i]) {
            Visit[i] = 1;
            mp[x][y] = i;
            int wrong = 0;
            if (x != 1) {
                int now = mp[x][y] + mp[x - 1][y];
                if (!isp[now]) wrong = 1;
            }
            if (y != 1) {
                int now = mp[x][y] + mp[x][y - 1];
                if (!isp[now]) wrong = 1;
            }
            if (!wrong) {
                int nx = x, ny = y + 1;
                if (ny > n) ny -= n, ++nx;
                dfs(nx, ny);
                if (ok) return;
            }
            Visit[i] = 0;
        }
}
int solve() {
    cin >> n;
    vector<int> div3[2];
    for (int i = 3; i <= n * n; i += 3)
        div3[i & 1].emplace_back(i);
    if (n % 2 == 0) {
        if (min(div3[0].size(), div3[1].size()) >= n) {
            for (int i = 1; i <= n; ++i) {
                int key = div3[0].back();
                div3[0].pop_back();
                vis[key] = 1;
                mp[n / 2][i] = key;
            }
            for (int i = 1; i <= n; ++i) {
                int key = div3[1].back();
                div3[1].pop_back();
                vis[key] = 1;
                mp[n / 2 + 1][i] = key;
            }
            vector<int> v;
            int now = 2, fail = 0;
            for (int i = 1; i <= n / 2 - 1; ++i)
                for (int j = 1; j <= n; ++j) {
                    while (vis[now]) now += 2;
                    if (now > n * n) {
                        fail = 1;
                        break;
                    }
                    mp[i][j] = now;
                    now += 2;
                }
            now = 1;
            for (int i = n / 2 + 2; i <= n; ++i)
                for (int j = 1; j <= n; ++j) {
                    while (vis[now]) now += 2;
                    if (now > n * n) {
                        fail = 1;
                        break;
                    }
                    mp[i][j] = now;
                    now += 2;
                }
            if (fail) {
                dfs(1, 1);
                for (int i = 1; i <= n; ++i, cout << '\n')
                    for (int j = 1; j <= n; ++j)
                        cout << mp[i][j] << ' ';
            } else {
                for (int i = 1; i <= n; ++i, cout << '\n')
                    for (int j = 1; j <= n; ++j)
                        cout << mp[i][j] << ' ';
            }
        } else {
            dfs(1, 1); assert(ok);
            for (int i = 1; i <= n; ++i, cout << '\n')
                for (int j = 1; j <= n; ++j)
                    cout << mp[i][j] << ' ';
        }
    } else {
        if (min(div3[0].size(), div3[1].size()) >= n) {
            int x = n / 2 + 1, y = 1, now = (x - 1) * n + 1;
            while (now < n * n / 2 + 1)
                ++now, ++y;
            assert(y <= n);
            for (int i = 1; i < y; ++i) {
                mp[n / 2 + 1][i] = div3[0].back();
                vis[div3[0].back()] = 1;
                div3[0].pop_back();
                mp[n / 2 + 2][i] = div3[1].back();
                vis[div3[1].back()] = 1;
                div3[1].pop_back();
            }
            for (int i = y; i <= n; ++i) {
                mp[n / 2][i] = div3[0].back();
                vis[div3[0].back()] = 1;
                div3[0].pop_back();
                mp[n / 2 + 1][i] = div3[1].back();
                vis[div3[1].back()] = 1;
                div3[1].pop_back();
            }
            { int now = 2, fail = 0;
            for (int i = 1; i < n / 2; ++i)
                for (int j = 1; j <= n; ++j) {
                    while (vis[now]) now += 2;
                    mp[i][j] = now;
                    if (now > n * n) {
                        fail = 1;
                        break;
                    }
                    now += 2;
                }
            for (int i = 1; i < y; ++i) {
                while (vis[now]) now += 2;
                mp[n / 2][i] = now;
                if (now > n * n) {
                    fail = 1;
                    break;
                }
                now += 2;
            }
            now = 1;
            for (int i = n / 2 + 3; i <= n; ++i)
                for (int j = 1; j <= n; ++j) {
                    while (vis[now]) now += 2;
                    mp[i][j] = now;
                    if (now > n * n) {
                        fail = 1;
                        break;
                    }
                    now += 2;
                }
            for (int i = y; i <= n; ++i) {
                while (vis[now]) now += 2;
                mp[n / 2 + 2][i] = now;
                if (now > n * n) {
                    fail = 1;
                    break;
                }
                now += 2;
            }
            if (fail) {
                dfs(1, 1);
                for (int i = 1; i <= n; ++i, cout << '\n')
                    for (int j = 1; j <= n; ++j)
                        cout << mp[i][j] << ' ';
            } else {
                for (int i = 1; i <= n; ++i, cout << '\n')
                    for (int j = 1; j <= n; ++j)
                        cout << mp[i][j] << ' ';
            } }
        } else {
            dfs(1, 1);
            for (int i = 1; i <= n; ++i, cout << '\n')
                for (int j = 1; j <= n; ++j)
                    cout << mp[i][j] << ' ';
        }
    }
    return 0;
}
signed main() {
    srand(time(0));
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    sieve();
    return solve();
}
```

---

## 作者：GJX_Algorithm (赞：0)

# AT_arc149_c题解
## 题目描述
1. 构造一个 $n \times n$ 的二维矩阵，要求用 $1 \sim n^2$ 填充这个矩阵。
2. 满足矩阵中任意两个相邻的数的和不为质数。

## 解题思路
1. 我们知道质数有一个特性：偶数中除了 $2$ 之外都不是质数。
2. 注意到偶数只有偶数与偶数相加或者奇数与奇数相加才能得到，于是我们就能构造出这样的矩阵：
![](https://cdn.luogu.com.cn/upload/image_hosting/j0apocf5.png)
3. 接下来我们只需要考虑奇数与偶数的边界，因为合数一定是某个数（不为 $1$ 和 $0$）的倍数，所以我们可以都填上 $x$ 的倍数，这样它们相加一定也是 $x$ 的倍数。
4. 然后又冒出来一个问题：万一 $x$ 的倍数不够放边界怎么办？由于 $x$ 越小，$x$ 的倍数越多，所以取最小的 $3$，就能得出不等式：$\lfloor n^2 \div 3 \rfloor \ge 4 \times n$，解得：$n \ge 6$ 时，边界够放。
5. $3 \le n < 6$ 时打表就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, a[N][N], e_multiple[N * N], o_multiple[N * N], cnt1, cnt2, flag[N][N];
bool vis[N * N];
void get_multiple()
{
    int now = 0;
    while (now <= n * n)
    {
        now += 3;
        if (now % 2 == 0) e_multiple[++cnt1] = now;
        else o_multiple[++cnt2] = now;
    }
    return ;
}
void Printf()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    return ;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    if (n == 3) cout << "3 5 1\n9 7 8\n6 2 4";
    else if (n == 4) cout << "15 11 16 12\n13 3 6 9\n14 7 8 1\n4 2 10 5";
    else if (n == 5) cout << "1 5 7 11 13\n17 19 23 21 25\n3 9 15 24 10\n6 12 18 2 4\n8 14 16 20 22";
    else if (n % 2 == 0)
    {
        get_multiple();
        int sum = 1;
        for (int j = 1; j <= n; j++)
        {
            a[n / 2][j] = o_multiple[sum];
            a[n / 2 + 1][j] = e_multiple[sum];
            vis[o_multiple[sum]] = vis[e_multiple[sum]] = 1;
            sum++;
        }
        int o_now = 1, e_now = 2;
        for (int i = 1; i < n / 2; i++)
            for (int j = 1; j <= n; j++)
            {
                while (vis[o_now] == 1) o_now += 2;
                a[i][j] = o_now;
                o_now += 2;
            }
        for (int i = n / 2 + 2; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                while (vis[e_now] == 1) e_now += 2;
                a[i][j] = e_now;
                e_now += 2;
            }
        Printf();
    }
    else
    {
        get_multiple();
        int sum = 1;
        for (int j = 1; j <= n / 2 + 1; j++)
        {
            a[n / 2 + 1][j] = o_multiple[sum];
            a[n / 2 + 2][j] = e_multiple[sum];
            vis[o_multiple[sum]] = vis[e_multiple[sum]] = 1;
            flag[n / 2 + 1][j] = flag[n / 2 + 2][j] = 1;
            sum++;
        }
        for (int j = n / 2 + 2; j <= n; j++)
        {
            a[n / 2][j] = o_multiple[sum];
            a[n / 2 + 1][j] = e_multiple[sum];
            vis[o_multiple[sum]] = vis[e_multiple[sum]] = 1;
            flag[n / 2][j] = flag[n / 2 + 1][j] = 1;
            sum++;
        }
        int o_now = 1, e_now = 2;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                if (flag[i][j] == 1) continue;
                if (i <= n / 2)
                {
                    while (vis[o_now] == 1) o_now += 2;
                    a[i][j] = o_now;
                    o_now += 2;
                }
                if (i >= n / 2 + 2)
                {
                    while (vis[e_now] == 1) e_now += 2;
                    a[i][j] = e_now;
                    e_now += 2;
                }
            }
        Printf();
    }
    return 0;
}

```

---

## 作者：lzqy_ (赞：0)

不一样的构造方法。

首先还是奇偶分开放，只考虑中间奇偶相邻的部分，并让奇数和偶数配对。

设 $2n^2$ 内有 $k$ 个质数，那么对于边界线上的一个奇数 $x$，会有 $w(w\le k)$ 个偶数 $y$ 不能和它匹配。而显然 $(\sum w)n<n^2$，所以肯定能找到一种配对方式。

用bitset维护即可，时间复杂度 $O(\frac{n^3}{w})$。

实现的时候就维护一个判断质数的bitset $p$ 和判断是否使用当前偶数的bitset $b$，每次把 $p$ 右移再翻转后，与上 $b$ 然后随便取元素即可。

注意 $n$ 为奇数时，拐角处要与上两个 $p$。

还有就是 $n=3$ 要特判。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=1010;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
bool vis[maxn*maxn<<1];
int Prime[maxn*maxn<<1],cnt;
void Oula(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i]) Prime[++cnt]=i;
		for(int j=1,x;j<=cnt&&(x=Prime[j]*i)<=n;j++){
			vis[x]=1;
			if(i%Prime[j]==0) break;
		}
	}
}
bitset<maxn*maxn*2>b,p;
int n,m,a[maxn][maxn];
il int Sum1(int x){return x*2-1;}
il int Sum2(int x){int y=b._Find_first();b[y]=0;return y;}
int main(){
	n=read(),m=n*n;
	if(n==3){
		printf("2 7 9\n");
		printf("4 8 6\n");
		printf("5 1 3\n");
		return 0;
	}
	Oula(m<<1);
	int c1=0,c2=0;
	for(int i=2;i<=m+m;i+=2) b[i]=1;
	for(int i=1;i<=cnt;i++) p[Prime[i]]=1;
	if(n%2==0){ 
		for(int i=1,x;i<=n;i++){
			a[n/2][i]=x=Sum1(++c1);
			a[n/2+1][i]=(b&((p>>x)).flip())._Find_first();
			b[a[n/2+1][i]]=0;
		}
	}
	if(n%2==1){
//		p[1000000000ll]=1;
		for(int i=1,x;i<=n/2+1;i++){
			a[n/2+1][i]=x=Sum1(++c1);
			a[n/2+2][i]=(b&((p>>x).flip()))._Find_first(); 
			b[a[n/2+2][i]]=0;
		}
		a[n/2][n/2+2]=Sum1(++c1);
		a[n/2+1][n/2+2]=(b&((p>>a[n/2][n/2+2]).flip())&((p>>a[n/2+1][n/2+1]).flip()))._Find_first();
		b[a[n/2+1][n/2+2]]=0;
		for(int i=n/2+3,x;i<=n;i++){
			a[n/2][i]=x=Sum1(++c1);
			a[n/2+1][i]=(b&((p>>x).flip()))._Find_first();
			b[a[n/2+1][i]]=0;
		}
	} 
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)
			if(a[i][j]) printf("%d ",a[i][j]);
			else{
				if((i-1)*n+j<=(m+1)/2) printf("%d ",Sum1(++c1));
				else printf("%d ",Sum2(++c2));
			}
	return 0;
} 
```

~~感觉这道题被我做难了好多~~

~~ARC C放这种无脑题也是离谱~~

---

## 作者：NobodyThere (赞：0)

这题构造方式有很多。

## Solution

### Step 1.

题目对任意相邻两数均有要求，一共有 $\mathcal O(n^2)$ 组点对，处理起来太麻烦，需要简化。

既然要求相邻两数和为合数，而任意两数和大于 $2$，那么在所有和中，所有偶数都是合数。将奇数与奇数凑在一起，偶数与偶数凑在一起，那我们就只用考虑奇数与偶数之间的关系了。

上半部分塞奇数，下半部分塞偶数，就会形成一个边界，如图：

![](https://img.atcoder.jp/arc149/386dd470603f65be4fbb8dcf45db8cad.png)

$\uparrow\text{(from Atcoder)}\uparrow$

我们就只需要考虑上面红色箭头所指的位置了。需要保证这些数对的和为奇合数。

接下来就有各种各样的构造方式了。

### Step 2.

赛时想到一种奇怪的构造方法。

众所周知，由于 $n\geq3$，当 $n$ 为奇数时，$n^2$ 为合数；当 $n$ 为偶数时，$n^2-1$ 为合数。

可以把这个数作为数对的和。

下面进行分类讨论。

#### I. $n\text{ is even}.$

容易构造数对 $\{(1,n^2-2),(2,n^2-3),\cdots,(n,n^2-n-1)\}$。显然满足 $n<n^2-n-1(n\geq4)$。依次填进边界的上下两排即可。注意奇数都要填上面，偶数都要填下面。

#### II. $n\text{ is odd}.$

容易构造数对 $\{(1,n^2-1),(2,n^2-2),\cdots,(n,n^2-n)\}$。显然满足 $n<n^2-n(n\geq3)$。

注意图中的拐角处。这意味着我们需要额外构造出一组数对，使得和为合数，并且数对的两数需要在前面的数对中出现。

注意到当 $n\geq5$ 时，$n^2-4$ 也为合数，所以我们可以组出 $(1,n^2-5)$。显然 $1$ 和 $n^2-5$ 都在前面的数对出现过了。而且 $n^2-5$ 为偶数。

需要特判 $n=3$ 的情况。

## Code

```cpp
#include <cstdio>
int n, a[1007][1007], vis[1000007], s, t;
void oper(int x, int i, int j) {
	int y = s - x; vis[x] = vis[y] = 1;
	if(x & 1) a[i][j] = x, a[i + 1][j] = y;
	else a[i][j] = y, a[i + 1][j] = x;
}
int main() {
	scanf("%d", &n);
	if(n == 3) { // 特判
		puts("5 9 1");
		puts("3 7 8");
		puts("6 2 4");
		return 0;
	}
	if(~n & 1) { // 偶数的情况
		s = n * n - 1;
		for(int i = 1; i <= n; i++) // 填边界
			oper(i, n >> 1, i);
		t = 1;
		for(int i = 1; i < n >> 1; i++) { // 填其它的数
			for(int j = 1; j <= n; j++) {
				while(vis[t]) t += 2;
				a[i][j] = t, t += 2;
			}
		}
		t = 2;
		for(int i = (n >> 1) + 2; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				while(vis[t]) t += 2;
				a[i][j] = t, t += 2;
			}
		}
	} else { // 奇数的情况
		s = n * n;
		oper(1, (n >> 1) + 1, (n >> 1) + 1); // 将 1 和 n^2-5 及对应的数对填入
		oper(5, n >> 1, (n >> 1) + 2);
		t = 1;
		for(int i = 1; i < (n >> 1) + 1; i++) { // 填入边界上其它的数
			while(vis[t]) ++t;
			oper(t, (n >> 1) + 1, i);
		}
		for(int i = (n >> 1) + 3; i <= n; i++) {
			while(vis[t]) ++t;
			oper(t, n >> 1, i);
		}
		t = 1;
		for(int i = 1; i < n >> 1; i++) { // 填边界以外的数
			for(int j = 1; j <= n; j++) {
				while(vis[t]) t += 2;
				a[i][j] = t, t += 2;
			}
		}
		for(int j = 1; j <= (n >> 1) + 1; j++) {
			while(vis[t]) t += 2;
			a[n >> 1][j] = t, t += 2;
		}
		t = 2;
		for(int j = (n >> 1) + 2; j <= n; j++) {
			while(vis[t]) t += 2;
			a[(n >> 1) + 2][j] = t, t += 2;
		}
		for(int i = (n >> 1) + 3; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				while(vis[t]) t += 2;
				a[i][j] = t, t += 2;
			}
		}
	}
	for(int i = 1; i <= n; i++, puts(""))
		for(int j = 1; j <= n; j++)
			printf("%d ", a[i][j]);
	return 0;
}
```

---

## 作者：xiaoPanda (赞：0)

## C - Avoid Prime Sum

### Problem

构造一个 $n\times n$ 的矩阵使得任意相邻两个数和不为质数（上下相邻和左右相邻），且使用 $1$ 到 $n\times n$ 的每一个数。

### Solution

容易发现一个奇数加奇数，偶数加偶数一定不是质数，那么我们可以把矩阵分成上下两个部分，上面的部分都填奇数，下面的部分都填偶数，不考虑中间一行，肯定符合要求。

那么中间怎么办呢，可以考虑使得中间上下两个数是 $3$ 的倍数，对于 $n$ 是偶数的情况，只要中间上方一行填 $3,9,...$ ，下方一行填 $6,12,...$ 就能满足要求，如图左下图：

![https://cdn.luogu.com.cn/upload/image_hosting/kyo69fem.png?x-oss-process=image/resize,m_lfit,h_170,w_225](https://cdn.luogu.com.cn/upload/image_hosting/kyo69fem.png?x-oss-process=image/resize,m_lfit,h_550,w_1000)

upd：图片来自 Atcoder 官方题解。

 $n$ 为奇数是也同理，只是要注意一下拐点的地方，如右上图。

还有就是对于 $n=3,4,5$ 时没有那么多 $3$ 的倍数，特判一下即可。

---

## 作者：lnwhl (赞：0)

## Description
构造一种方案，用 $1\sim n^2$ 填充一个 $n\times n$ 的方格，使任意两个相邻的数的和不为质数。
## Solution
小清新构造。

让相邻两个的和不为质数，最简单的方法就是让和为偶数，容易知道 奇数+奇数=偶数，偶数+偶数=偶数，所以可以想到把奇数排在上面，偶数排在下面，尽可能减少奇数与偶数的接触。

下面，我们分类讨论 $n$ 为奇数和偶数的情况。
### $n$ 为偶数
奇数都排在上面 $n/2$ 行，偶数排在下面 $n/2$ 行。但是，还有一个问题，第 $n/2$ 行的数和第 $n/2+1$ 行的数的和是奇数，可能会出现质数。
考虑如何构造，不难发现如果 $n/2+1$ 行的数是 $n/2$ 行的数的倍数，他们的和一定是合数，所以可以构造 $n/2+1$ 行的数等于 $n/2$ 行的数的二倍。剩下的数瞎填就好了。

|   |   |   |   |   |   |
| ------------ | ------------ | ------------ | ------------ | ------------ | ------------ |
|   |   |   |   |   |   |
| 3  |  5 | 7  | 9  | 11  | 13  |
|  6 |  10 | 14  | 18  | 22  | 26  |
|   |   |   |   |   |   |
|   |   |   |   |   |   |

### $n$ 为奇数
还像偶数一样，把奇数排在上面，偶数排在下面。
但是有一个问题（如下图，$5\times5$ 的格），$(3,4)$ 的偶数同时与 $(3,3),(2,4)$ 两个奇数相邻，$(3,3)$ 的奇数也同时与两个偶数相邻，我们构造 $3,6,9,12$ 就可以了。

|   |   |   |   |   |
| ------------ | ------------ | ------------ | ------------ | ------------ |
|   |   |   |  $\color{red}{9}$ |   |
|   |   |  $\color{red}{3}$ | $\color{blue}{6}$ |   |
|   |   |  $\color{blue}{12}$ |   |   |
|   |   |   |   |   |

剩下的位置继续构造 $2$ 倍关系就可以了。

|   |   |   |   |   |
| ------------ | ------------ | ------------ | ------------ | ------------ |
|   |   |   |  9 | 11  |
|  5 |  7 |  3 | 6 | 22  |
|  10 |  14 | 12  |   |   |
|   |   |   |   |   |

### Corner Case
当然，$n=3$ 和 $n=4$ 的情况需要特殊构造，具体构造方案见代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1005;
int n,a[N][N],used[N*N];
signed main()
{
	cin>>n;
	if(n==3){cout<<"5 9 1\n3 7 8\n6 2 4";return 0;}
	if(n==4){cout<<"9 11 13 15\n1 3 5 7\n8 6 10 14\n2 4 12 16";return 0;}
	if(n%2==0)
	{
		for(int i=1;i<=n;++i)
		{
			a[n/2][i]=i+i+1;
			a[n/2+1][i]=a[n/2][i]*2;
			used[i+i+1]=1;used[4*i+2]=1;
		}
		int now=1;
		for(int i=1;i<=n/2-1;++i)
			for(int j=1;j<=n;++j)
			{
				while(used[now])now+=2;
				a[i][j]=now;now+=2;
			}
		now=2;
		for(int i=n/2+2;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				while(used[now])now+=2;
				a[i][j]=now;now+=2;
			}
	}
	else
	{
		a[n/2+1][n/2+1]=3;used[3]=1;
		a[n/2+1][n/2+2]=6;used[6]=1;
		a[n/2][n/2+2]=9;used[9]=1;
		a[n/2+2][n/2+1]=12;used[12]=1;
		int now=5;
		for(int i=1;i<=n/2;++i)
		{
			while(used[now])now+=2;
			a[n/2+1][i]=now;a[n/2+2][i]=now*2;
			used[now]=1;used[now*2]=1;now+=2;
		}
		for(int i=n/2+3;i<=n;++i)
		{
			while(used[now])now+=2;
			a[n/2][i]=now;a[n/2+1][i]=now*2;
			used[now]=1;used[now*2]=1;now+=2;
		}
		now=1;
		for(int i=1;i<=n/2;++i)
			for(int j=1;j<=n;++j)
			{
				if(a[i][j])continue;
				while(used[now])now+=2;
				a[i][j]=now;now+=2;
			}
		now=2;
		for(int i=n/2+2;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				if(a[i][j])continue;
				while(used[now])now+=2;
				a[i][j]=now;now+=2;
			}
	}
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			cout<<a[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
```



---

