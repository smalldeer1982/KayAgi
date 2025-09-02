# Distance Learning Courses in MAC

## 题目描述

The New Year has arrived in the Master's Assistance Center, which means it's time to introduce a new feature!

Now students are given distance learning courses, with a total of $ n $ courses available. For the $ i $ -th distance learning course, a student can receive a grade ranging from $ x_i $ to $ y_i $ .

However, not all courses may be available to each student. Specifically, the $ j $ -th student is only given courses with numbers from $ l_j $ to $ r_j $ , meaning the distance learning courses with numbers $ l_j, l_j + 1, \ldots, r_j $ .

The creators of the distance learning courses have decided to determine the final grade in a special way. Let the $ j $ -th student receive grades $ c_{l_j}, c_{l_j + 1}, \ldots, c_{r_j} $ for their distance learning courses. Then their final grade will be equal to $ c_{l_j} $ $ | $ $ c_{l_j + 1} $ $ | $ $ \ldots $ $ | $ $ c_{r_j} $ , where $ | $ denotes the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) operation.

Since the chatbot for solving distance learning courses is broken, the students have asked for your help. For each of the $ q $ students, tell them the maximum final grade they can achieve.

## 说明/提示

In the first test case:

1. The maximum grade for the first student is $ 1 $ : 
  - On the first distance learning course, he will receive a grade of $ 1 $ .
  
   Therefore, the final grade is $ 1 $ .
2. The maximum grade for the second student is $ 5 $ : 
  - On the first distance learning course, he will receive a grade of $ 1 $ .
  - On the second distance learning course, he will receive a grade of $ 4 $ .
  
   Therefore, the final grade is $ 1 $ $ | $ $ 4 $ $ = $ $ 5 $ .
3. The maximum grade for the third student is $ 4 $ : 
  - On the second distance learning course, he will receive a grade of $ 4 $ .
  
   Therefore, the final grade is $ 4 $ .

In the second test case:

1. The maximum grade for the first student is $ 15 $ : 
  - On the first distance learning course, he will receive a grade of $ 7 $ .
  - On the second distance learning course, he will receive a grade of $ 4 $ .
  - On the third distance learning course, he will receive a grade of $ 8 $ .
  
   Therefore, the final grade is $ 7 $ $ | $ $ 4 $ $ | $ $ 8 $ $ = $ $ 15 $ .
2. The maximum grade for the second student is $ 11 $ : 
  - On the third distance learning course, he will receive a grade of $ 9 $ .
  - On the fourth distance learning course, he will receive a grade of $ 2 $ .
  
   Therefore, the final grade is $ 9 $ $ | $ $ 2 $ $ = $ $ 11 $ .

## 样例 #1

### 输入

```
3
2
0 1
3 4
3
1 1
1 2
2 2
4
1 7
1 7
3 10
2 2
5
1 3
3 4
2 3
1 4
1 2
6
1 2
2 2
0 1
1 1
3 3
0 0
4
3 4
5 5
2 5
1 2```

### 输出

```
1 5 4 
15 11 15 15 7 
1 3 3 3```

# 题解

## 作者：sunkuangzheng (赞：13)

$\textbf{CF1935E *2500}$

> - 给定序列 $\{x_n\},\{y_n\}$，共有 $q$ 组询问，第 $i$ 组询问给出 $l,r$，你需要构造序列 $a$ 满足 $a_i \in [x_i,y_i]$，求 $\max \operatorname{OR}_{i=l}^r a_i$。
> - $1\le n,q \le 2 \cdot 10^5,0 \le x_i \le y_i < 2^{30}$。

### 提示 $1$

考虑对于一对 $(x_i,y_i)$，如果 $y_i$ 的第 $k$ 位是 $1$ 则答案第 $k$ 位一定是 $1$，思考为什么。

### 提示 $2$

如果所有 $(x_i,y_i)$ 的最高位不同该怎么做？

### 题解

首先我们对于每一对 $(x_i,y_i)$，去除它们二进制下最长公共前缀并直接算入答案 $ans$，此时一定满足 $x_i < y_i$ 且最高位不同。考虑对于某一位 $j$，考虑区间内有多少 $y_i$ 满足 $y_i$ 的第 $j$ 位是 $1$，加上 $ans$ 的第 $j$ 位是否是 $1$ 后假设有 $c$ 个：

- $c \ge 2$：因为我们已经保证 $x_i < y_i$，所以一定可以一个位置令 $a_i = 2^j$，一个位置令 $a_i = 2^j-1$，或起来后 $j$ 及更低的二进制位都已经是 $1$，不需要再往下考虑。
- $c = 1$：此时我们一定填 $1$，这一位对答案产生贡献。
- $c = 0$：这一位没有意义。

你也可以通过以上流程发现，在去除最长公共前缀后 $x_i$ 就已经没有意义，因为当 $c \ge 2$ 时我们直接得到答案，$c=  1$ 时只关心能否在某一位填 $1$，而这个与 $x_i$ 无关。

可以前缀和统计出现次数，ST 表维护区间或，时间复杂度 $\mathcal O((n+q) \log nV)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 06.03.2024 07:28:11
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,q,x,y,l,r;
void los(){
    cin >> n;
    vector<vector<int>> ct(36,vector<int>(n + 1)),st(25,vector<int>(n + 1));
    for(int i = 1;i <= n;i ++){
        cin >> x >> y;
        for(int j = 30;j >= 0;j --)
            if(((x >> j) & 1) == ((y >> j) & 1)) st[0][i] |= (((x >> j) & 1) << j);
            else{
                for(int k = j;k >= 0;k --) if((y >> k) & 1) ct[k][i] ++;
                break;
            }
        for(int j = 30;j >= 0;j --) ct[j][i] += ct[j][i-1];
    }for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
        st[j][i] = st[j-1][i] | st[j-1][i + (1 << j-1)];
    auto qry = [&](int l,int r){
        int k = __lg(r - l + 1);
        return st[k][l] | st[k][r-(1<<k)+1];
    };
    cin >> q;
    while(q --){
        cin >> l >> r;
        int ans = qry(l,r),w;
        for(int i = 30;i >= 0;i --)
            if(w = ct[i][r] - ct[i][l-1] + ((ans >> i) & 1),w >= 2) ans |= (1 << i + 1) - 1;
            else if(w) ans |= (1 << i); 
        cout << ans << " ";
    }cout << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：Alex_Wei (赞：10)

### [CF1935E Distance Learning Courses in MAC](https://www.luogu.com.cn/problem/CF1935E)

所有区间不一定全部选 $y$，因为对于每一位，只要区间内存在一个数该位为 $1$ 就能产生贡献，其它的 $1$ 都浪费了。

对于区间 $[x, y]$，设最终选定的数 $x\leq c\leq y$。考虑 $c$ 和 $y$ 在二进制下最高的不同位 $k$，则 $c$ 的第 $k$ 位为 $0$，$y$ 的第 $k$ 位为 $1$，此时一定贪心地让 $c$ 的第 $0\sim k - 1$ 位为 $1$，这样不仅能够最大程度地满足 $x\leq c$ 的限制，也能让 $c$ 的每一位都取到最大贡献。

于是，设 $x$ 和 $y$ 在二进制下最高的不同位为 $k$，则可以让 $y$ 的第 $k'$ 位的 $1$ 变成 $0$，第 $0\sim k' - 1$ 位全部变成 $1$，要求 $k'\leq k$ 且 $y$ 的第 $k'$ 位确实为 $1$。

设 $f(k, l, r)$ 表示第 $k$ 位 $y_{l\sim r}$ 的 $1$ 的个数，$g(k, l, r)$ 表示第 $k$ 位 $y_{l\sim r}$ 可以变为 $0$ 的 $1$ 的个数，即 $y_i\ (l\leq i\leq r)$ 产生贡献当且仅当 $y_i$ 的第 $k$ 位为 $1$ 且 $k$ 不高于 $x_i$ 和 $y_i$ 在二进制下最高的不同位。$f, g$ 均可预处理前缀和 $\mathcal{O}(1)$ 计算。

对于每次询问，考虑从高到低按位贪心。对于当前位：

- 若 $f(l, r) = 0$，则无法产生贡献。
- 若 $f(l, r) = 1$，则就算唯一的 $1$ 可以变成所有低位的 $1$，这样做也不优。令其直接产生贡献。
- 若 $f(l, r) > 1$：
  - 若 $g(l, r) > 0$，则令其中一个 $1$ 变成所有低位的 $1$，此时所有不高于当前位的位均产生贡献，贪心过程结束。
  - 若 $g(l, r) = 0$，则只能直接产生贡献。

时间复杂度 $\mathcal{O}((n + q)\log V)$。[代码](https://codeforces.com/contest/1935/submission/250203455)。

---

## 作者：鼓豆帝王 (赞：7)

题目链接：[CF1935E Distance Learning Courses in MAC](https://www.luogu.com.cn/problem/CF1935E)

## 解法说明

乍看一眼没有思路，所以尝试从题目条件的特殊性入手。注意到每个区间是 $[l,r]$ 中**连续**的数，这个“连续”的性质让我感觉可能存在着某些结论。

接着尝试按位处理，先看到 $l$ 和 $r$ 的最高位，下面记 $l$ 的最高位为第 $h_l$ 位，$r$ 的最高位为第 $h_r$ 位（从第 $0$ 位开始），分两种情况讨论：

1. 若 $h_l\neq h_r$，则一定满足 $l\le 2^{h_r}-1\le r$，也就是说 $[l,r]$ 中存在一个数，其二进制表示的第 $0\sim h_r-1$ 位均为 $1$，其余各位均为 $0$。  
2. 若 $h_l= h_r$，则不论选 $[l,r]$ 中的哪个数，其二进制表示的第 $h_r$ 位一定是 $1$。

进一步地，我们可以研究多个区间的结论。对于编号为 $[L,R]$ 中的区间，记：

- $H=\max \limits_{i=L}^{R} h_{r_i}$（也就是所有区间中的最高位）。  
- $l_i,r_i$ 的第 $H$ 位均为 $1$ 的区间数量为 $c_{eq}$。  
- $l_i$ 的第 $H$ 位为 $0$，$r_i$ 的第 $H$ 位为 $1$ 的区间数量为 $c_{neq}$。

分三种情况讨论：

1. 若 $c_{eq}\neq 0$ 且 $c_{neq}=0$，那么答案的第 $H$ 位一定是 $1$。  
2. 若 $c_{eq}=0$ 且 $c_{neq}=1$，那么答案的第 $H$ 位一定是 $1$。  
3. 否则，答案的第 $0\sim H$ 位均为 $1$，其余各位均为 $0$。

根据上面的结论，您是否感觉可以从高到低逐位处理，最后整个程序的流程如下：

1. 若第 $i$ 个区间的 $h_l\neq h_r$，则将 $l_i$ 置为 $0$。（如果你对此步感到疑惑，可以结合第 $4,5$ 步理解）
2. 从高到低遍历每一个二进制位，用前缀和预处理每一位的 $c_{eq}, c_{neq}$。  
3. 若第 $i$ 位的 $c_{eq}\neq 0$ 且 $c_{neq}=0$，那么答案的第 $i$ 位一定是 $1$，即将答案加上 $2^i$，继续处理 $i-1$ 位。  
4. 若第 $i$ 位的 $c_{eq}=0$ 且 $c_{neq}=1$，那么答案的第 $i$ 位一定是 $1$，即将答案加上 $2^i$，继续处理 $i-1$ 位。 
5. 否则，答案的第 $0\sim i$ 位均为 $1$，即将答案加上 $2^{i+1}-1$，直接跳出循环。

该算法的时间复杂度为 $O((n+q)\log V)$，空间复杂度为 $O(n\log V)$。

## AC 代码

```cpp
#include <iostream>
#include <stdio.h>
#define ll long long
using namespace std;

const ll maxN = 2e5 + 10;
const ll maxB = 40;

struct numstr {
	ll l, r;
} nums[maxN];

ll t, n, q;
ll sum1[maxN][maxB], sum2[maxN][maxB];

ll highbit(ll x) {
	while (x ^ (x & -x)) x ^= x & -x;
	return x;
}

int main(void) {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%lld%lld", &nums[i].l, &nums[i].r);
			if (highbit(nums[i].l) != highbit(nums[i].r)) {
				nums[i].l = 0;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 30; j++) {
				sum1[i][j] = sum1[i - 1][j], sum2[i][j] = sum2[i - 1][j];
				if (((nums[i].l >> j) & 1) && ((nums[i].r >> j) & 1)) {
					sum1[i][j]++;
				}
				if (!((nums[i].l >> j) & 1) && ((nums[i].r >> j) & 1)) {
					sum2[i][j]++;
				}
			}
		}
		
		scanf("%lld", &q);
		ll l, r, ans;
		for (int i = 1; i <= q; i++) {
			scanf("%lld%lld", &l, &r);
			ans = 0;
			for (int j = 29; j >= 0; j--) {
				ll temp1 = sum1[r][j] - sum1[l - 1][j];
				ll temp2 = sum2[r][j] - sum2[l - 1][j];
				if (!temp1 && !temp2) continue;
				else if (temp1 && !temp2) {
					ans += (1 << j);
				}
				else if (!temp1 && temp2 == 1) {
					ans += (1 << j);
				}
				else {
					ans += (1 << (j + 1)) - 1;
					break;
				}
			}
			printf("%lld ", ans);
		}
		putchar('\n');
		
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 30; j++) {
				sum1[i][j] = sum2[i][j] = 0;
			}
		}
	}
}
```

---

## 作者：Engulf (赞：3)

对于区间 $[x_i, y_i]$，设选择的数是 $w$ 因为 $x_i \le w \le y_i$，所以不妨去掉 $x_i$ 和 $y_i$ 最高位相同的部分，这些是肯定能取到的，如：

$$x:\color{red}1101\color{black}01101(429_{(10)})$$
$$y:\color{red}1101\color{black}10111(439_{(10)})$$

红色部分一定出现于答案，第 $i$ 个区间的红色部分记为 $a_i$。

去掉这些后，所有的 $x_i < y_i$（当然有可能存在 $x_i = y_i = 0$，但这不影响答案），现在从高位到低位贪心，一开始先将答案赋值为 $a_l | a_{l + 1} | \cdots | a_r$，当前处理到第 $j$ 位，设在 $i \in [l, r]$ 中，$y_i$ 第 $j$ 位是 $1$ 的数有 $c$ 个，分类讨论：
- $c \ge 2$，也就是存在至少两个区间是下面这种情况（下面的最高位就当作是第 $j$ 位）
   - $[011001, 101101]$
   - $[001010, 100110]$
- 由于现在 $x$ 第 $j$ 位一定小于 $y$ 的第 $j$ 位，想到这两个区间一个取 $2^j$，一个取 $2^j - 1$，这两个数都是一定在范围内的，那么 $0$ 到 $j$ 位都变为 $1$，即答案或上 $2^{j + 1} - 1$，既然低位全是 $1$，停止计算。
- $c = 1$，只有一个区间是上面那种区间的情况，设当前答案第 $j$ 位是 $v$：
  - $v = 0$，为了答案最大，答案或上 $2^j$，继续计算。
  - $v = 1$，类似 $c \ge 2$ 的情况，这个区间取 $2^j - 1$ 即可，答案或上 $2^{j} - 1$，低位全变为 $1$，可停止计算。因为答案第 $j$ 位已经是 $1$，或上 $2^j - 1$ 等价于或上 $2^{j + 1} - 1$，所以实现的时候，$c$ 也加上答案第 $j$ 为是否为 $1$，可减少讨论。
- $c = 0$，这一位恒为 $0$，不产生贡献。

综上，我们需要维护区间或和区间和，使用 ST 表和前缀和维护即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;

        vector<vector<int>> sum(n + 5, vector<int>(35));

        vector<vector<int>> st(n + 5, vector<int>(__lg(n) + 5));

        for (int i = 1, x, y; i <= n; i++) {
            cin >> x >> y;
            for (int j = 29; ~j; j--) {
                if ((x >> j & 1) == (y >> j & 1))
                    st[i][0] |= (x >> j & 1) << j;
                else {
                    for (; ~j; j--)
                        if (y >> j & 1)
                            sum[i][j]++;
                    break;
                }
            }
            for (int j = 29; ~j; j--)
                sum[i][j] += sum[i - 1][j];
        }

        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[i][j] = st[i][j - 1] | st[i + (1 << j - 1)][j - 1];

        auto query = [=](int l, int r) {
            int k = __lg(r - l + 1);
            return st[l][k] | st[r - (1 << k) + 1][k];
        };

        int q;
        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            int ans = query(l, r);
            for (int j = 29; ~j; j--) {
                int c = sum[r][j] - sum[l - 1][j] + (ans >> j & 1);
                if (c >= 2) {ans |= (1 << j + 1) - 1; break;}
                else if (c == 1) ans |= 1 << j;
            }
            cout << ans << " ";
        }
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：fast_photon (赞：3)

## CF1935E  
### 1. 题意  
给定一个限制序列 $\{(x_n,y_n)\}$，表示 $x_i\le a_i\le y_i$。  
$q$ 组询问 $l,r$，问 $[l,r]$ 中的所有数都满足限制时，它们的按位或最大是多少。询问之间互相独立。  
$1\le n,q\le 2\times 10^5,1\le l_i\le r_i\le n,0\le x_i\le y_i<2^{32}$。  

### 2. 分析  
由于问位运算最大值，所以可以从高位往低位贪心。  
第 $i$ 位可以为 $1$，当且仅当有至少一个数在第 $i$ 位可以为 $1$。  
如果有数必须在这一位为 $1$，则直接用这个数，避免带来不必要的限制。  
否则会对一个数产生一个更严格的下界。  

+ 如果这一位特别宽松，还额外有一个可以是 $0$ 也可以是 $1$ 的数，就可以直接把后面的位都解决。因为是连续变化，所以可以有 $1000\dots \operatorname{or} {0111\dots}=1111\dots$。
+ 如果这一位不太宽松，且我们用掉了一个可 $0$ 可 $1$ 的，那么这个数从上界的下一个 $1$ 位开始重新变得可 $0$ 可 $1$。  
+ 如果这一位不太宽松，且我们用掉了一个一定为 $1$ 的数，不会产生额外影响。  
+ 如果这一位非常严格，不能达成 $1$，直接继续贪下一位。  

对于数的判定，若某一位上，某个数的上下界不同，则从这一位开始这个数可 $0$ 可 $1$。否则按照上下界判断是否一定为 $1$。  

至此，我们可以总结如下贪心策略：  
1. 从高开始枚举每一位。  
2. 看这一位在给定区间内有多少个可 $0$ 可 $1$ 的数（称为第一贡献），和多少个必须为 $1$ 的数（称为第二贡献）。第二贡献有 $\ge 1$ 个产生 $1$ 的贡献，第一贡献按个数产生贡献。  
3. 总贡献 $\ge 2$ 时，把后面的位和这一位全置 $1$，结束贪心过程。  
4. 总贡献 $=0$ 时，不管这一位，继续贪心。  
5. 总贡献 $=1$ 时，这一位置成 $1$，若有第一贡献，将 $[下一位，进行第一贡献的数^{*}后面所有位中的最高位]$ 区间的第一贡献减少 $1$。  

\*：对于每一个数和每一位，找到这之前这一位第一个可 $0$ 可 $1$ 的数。只需要找一个，因为有两个就会结束贪心。。

### 3. 代码  
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<algorithm>
#define maxn 400005
#define int long long

using namespace std;

int n, q, l, r, cnt[maxn][32], lst[maxn][32], x[maxn], y[maxn], l2[maxn];

inline int l2c(int x) {
	return (x >> 16) ? l2[x >> 16] + 16 : l2[x];
}

void work() {
	cin >> n;
	for(int i = 0; i <= n + 2; i++) {
		x[i] = y[i] = 0;
		for(int j = 0; j <= 30; j++) {
			cnt[i][j] = lst[i][j] = 0; //多测清空！！！
		}
	}
	for(int i = 1; i <= n; i++) {
		cin >> l >> r;
		x[i] = l, y[i] = r;
		for(int j = 29; j >= 0; j--) {
			if(i == 1) lst[i][j] = 0;
			lst[i + 1][j] = lst[i][j];
			if((l >> j) != (r >> j)) cnt[i][j] = cnt[i - 1][j] + 1048576; //判定贡献类别，偷懒压数了，cnt的后20位为第二贡献，前面的位为第一贡献。这么写要开 long long。
			else if((l >> j) & 1) cnt[i][j] = cnt[i - 1][j] + 1; //产生第二贡献
			else cnt[i][j] = cnt[i - 1][j]; //没有贡献，也要做前缀和转移！！
			if(((l >> j) ^ (r >> j)) == 1) lst[i + 1][j] = i; //维护 * 的内容。
		}
	}
	cin >> q;
	while(q--) {
		cin >> l >> r;
		int bs = 0, xum = 0;
		int q0[32] = {0}; //每一位总贡献
		for(int i = 29; i >= 0; i--) {
			int sum = cnt[r][i] - cnt[l - 1][i];
			int ctn = 0;
			for(int p = lst[r + 1][i]; p >= l; p = lst[p][i]) {
				q0[i]++;
				for(int t = y[p] & ((1 << i) - 1); t; t &= ((1 << l2c(t)) - 1)) { //每次取下一个 1 位。
					q0[l2c(t)]++; //l2c 为自己写的取最高位函数。在每个 1 位产生贡献。若没被使用，则必然有其他数被使用，二次贡献，结束。若被使用，则一定是继续找下一个 1
				}
				ctn++;
				if(ctn > 1) break; //同一位超过两次贡献，直接结束
			}
			int s1 = sum & 1048575; //提取第二贡献
			if(s1) s1 = 1; // 若有，无论多少个都是 1 贡献
			q0[i] += s1;
		}
		for(int i = 29; i >= 0; i--) {
			if(q0[i] >= 2) { // 二次贡献全变 1
				xum |= (1 << (i + 1)) - 1;
			}
			else if(q0[i] >= 1) xum |= (1 << i); //一次贡献单位变 1
		}
		cout << xum << ' ';
	}
	cout << '\n';
}

signed main() {
	l2[0] = -1;
	for(int i = 1; i <= 200000; i++) l2[i] = l2[i >> 1] + 1;
	ios::sync_with_stdio(false); cin.tie(0);
	int _; cin >> _; while(_--) work();
} 
```

---

## 作者：eb0ycn (赞：1)

一拍桌子，两眼放光，直接 ST 表维护 $y$ 的或和，输出！

然后你就假了。

某个反面教材，我不说是谁。

## 思路

定义**舍弃**为把一个数 $y$ 的某一位 $p$ 从 $1$ 改为 $0$，且 $p$ 位以下全变为 $1$。

假设每个位置选了 $q$，那么要么 $q=y$，要么 $q$ 是 $y$ **舍弃**一位得到的数。

我们不知道舍弃哪个位置，所以很难不预处理哪些位置可以被舍弃。显然地，$y_i$ 的这一位必须是 $1$，且舍弃后**不小于** $x_i$。

设 $f_{i,j}$ 表示前 $j$ 个数第 $i$ 位一共有多少个 $1$，$g_{i,j}$ 表示前 $j$ 个数中可以在第 $i$ 位舍弃的数量。不难发现这两个东西都可以差分。

每次询问时，肯定要从高位开始贪心。只有 $f_{i,r}-f_{i,l-1}>1$，且 $g_{i,r}-g_{i,l-1}>0$ 时，才考虑舍弃第 $i$ 位，牺牲“有余力”的 $1$，这样答案的第 $i$ 位及以下就全是 $1$ 了。

## 代码


```cpp
#include<cstdio>
int T,n,x[200001],y[200001],f[30][200001],g[30][200001],q,l,r,ans;
int read(){
	int x=0;
	char c=getchar();
	while(c<48||c>57)c=getchar();
	while(c>47&&c<58)x=x*10+c-48,c=getchar();
	return x;
}
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;++i)x[i]=read(),y[i]=read();
		for(int i=0;i<30;++i){
			for(int j=1;j<=n;++j){
				f[i][j]=f[i][j-1]+(y[j]>>i&1),g[i][j]=g[i][j-1];
				if(y[j]>>i&1&&(y[j]^1<<i|((1<<i)-1))>=x[j])++g[i][j];
			}
		}
		q=read();
		while(q--){
			l=read(),r=read(),ans=0;
			for(int i=29;~i;--i){
				if(f[i][r]-f[i][l-1])ans|=1<<i;
				if(f[i][r]-f[i][l-1]>1&&g[i][r]-g[i][l-1]){ans|=(1<<i)-1;break;}
			}
			printf("%d ",ans);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：mkx2023275 (赞：0)

题意很明确，让我们求按位或的最大值。像这种求位运算极值的题目，一般考虑从高位到低位贪心。

观察发现，某些区间的某些位为定值，如 $x = (1010110101)_2, y = (1010011010)_2$，两数有共同前缀 $1010$，所以在这个区间中的数的前缀一定为 $1010$。我们可以把所有区间中这样 $x$ 和 $y$ 的公共前缀提取出来，先将其加到答案里面。每次查询时相当于求一个区间重的数的按位或，可以使用 ST 表。

为什么要这么做呢？可以发现，在这么做之后，每个数第一位的取值是自由的，可以取一些特殊值，如 $(1000\cdots000)_2$，$(0111\cdots111)$，这对我们后面的贪心有帮助。

接下来我们进行按位的贪心，假设我们现在贪心到第 $j$ 位，设 $y$ 的第 $j$ 位为 $1$ 的数有 $cnt$ 个。由于答案进行过初始化（公共前缀按位或），每一位可能需要 $1$（初始答案中这一位为 $0$），也可能不需要（初始答案中这一位未 $1$），我们对这两种情况分类讨论。

 - 这一位不需要 $1$
   - $cnt \ge 1$，此时可以将其中一个数 $j$ 之后的几位（不包括 $j$）全部设为 $1$（即 $2 ^ j - 1$）。此时 $j$ 后面的位全部为 $1$，结束贪心。
   - $cnt = 0$，直接继续。
 - 这一位需要 $1$
   - $cnt \ge 2$，此时可以将一个数的第 $j$ 位设为 $1$（$2 ^ j$），两一个数 $j$ 往后的位设为 $1$（$2 ^ j - 1$）。此时 $j$ 后面的位全部为 $1$，结束贪心。
   - $cnt = 1$，我们将这个数的第 $j$ 位设为 $1$，继续贪心。
   - $cnt = 0$，这一位答案只能为 $0$，直接继续。

这一过程中需要求一个区间中某一位为 $1$ 的数的个数，对每一位记录前缀和即可。

总结一下，我们首先确定了贪心的大方向，然后对固定位进行计算，再对每一位贪心，按照当前位为 $1$ 的数的个数和当前为是否需要 $1$ 进行分类讨论。

[代码](https://codeforces.com/contest/2106/submission/323600494)。

---

## 作者：LYY_yyyy (赞：0)

首先观察到若 $l_i,r_i$ 二进制下最高位相同，那这一位一定选最高位，故可以直接删去最高位，询问时直接计入答案。这可以用 ST 表维护区间或实现。

接下来只要考虑最高位不同的情况。按位从大到小考虑。我们发现，对于某一位 $i$，若存在两对 $l,r$ 的最高位为 $i$，或者区间或中第 $i$ 位为 1 且存在至少一对 $l,r$ 的最高位为 $i$，那么我们可以一对取 $2^i$，另一对取 $2^i-1$，这样接下来的位就不用考虑了，直接结束。若不存在一对 $l,r$ 满足最高位为 $i$，则直接跳过这一位。所以我们只要考虑只存在一对 $l,r$ 满足最高位为 $i$ 的情况。此时肯定要选第 $i$ 位，那么考虑范围变为 $[2^i,r]$。此时 $2^i$ 与 $r$ 最高位相同，直接删去最高位，区间变为 $[0,r-2^i]$，按照上述规则递归下去。由于将一位置为 1 才会继续递归（若原本为 1，那么满足第一种情况，可以直接退出），所以时间复杂度 $O((n+q)\log nV)$。

代码:

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define pb emplace_back
using namespace std;
int T,n;
struct node
{
	int l,r,id;
	friend bool operator < (const node &a,const node &b)
	{
		return a.l<b.l;
	}
}q[200010];
int l[200010],r[200010],ans[200010];
int st[200010][21];
vector<int> op[31];
vector<int>::iterator p[31];
int nw,f;
void calc(int ro)
{
	if(!ro) return;
	int hi=__lg(ro);
	if((p[hi]!=op[hi].end()&&*p[hi]<=f)||(nw>>hi)&1) return nw|=(1<<(hi+1))-1,void();
	return nw|=(1<<hi),calc(ro-(1<<hi));
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=0;i<30;i++) op[i].clear();
		for(int i=1;i<=n;i++) cin>>l[i]>>r[i];
		for(int i=1;i<=n;i++)
		{
			int s=0,rp;
			while(l[i]&&r[i]&&__lg(l[i])==__lg(r[i])) rp=1<<__lg(l[i]),l[i]-=rp,r[i]-=rp,s|=rp;
			st[i][0]=s;
			if(r[i]) op[__lg(r[i])].pb(i);
		}
		for(int j=1;j<=__lg(n);j++)
		{
			for(int i=1;i+(1<<j)-1<=n;i++)
			{
				st[i][j]=st[i][j-1]|st[i+(1<<(j-1))][j-1];
			}
		}
		int Q;cin>>Q;
		for(int i=1;i<=Q;i++) cin>>q[i].l>>q[i].r,q[i].id=i;
		sort(q+1,q+Q+1);
		for(int i=0;i<30;i++) p[i]=op[i].begin();
		for(int i=1;i<=Q;i++)
		{
			for(int j=0;j<30;j++) while(p[j]!=op[j].end()&&*p[j]<q[i].l) p[j]++;
			int len=__lg(q[i].r-q[i].l+1);
			nw=st[q[i].l][len]|st[q[i].r-(1<<len)+1][len];
			f=q[i].r;
			for(int j=29;j>=0;j--)
			{
				if(p[j]!=op[j].end()&&*p[j]<=f)
				{
					auto rp=p[j];
					rp++;
					if((rp!=op[j].end()&&*rp<=f)||(nw>>j)&1)
					{
						nw|=(1<<(j+1))-1;
						break;
					}
					else
					{
						nw|=(1<<j);
						calc(r[*p[j]]-(1<<j));
					}
				}
			}
			ans[q[i].id]=nw;
		}
		for(int i=1;i<=Q;i++) cout<<ans[i]<<' ';
		cout<<"\n";
	} 
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

注意到，我们其实可以对某一个 $r_i$ 进行一个“牺牲”操作，即把某一位的 $1$ 变成 $0$ 并把比该位低的位全部变成 $1$。这种操作当且仅当 $l_i$ 的那一位是 $0$，或者前面某一位已经满足 $r_i$ 的那一位是 $1$ 且 $l_i$ 那一位是 $0$。

如果对于某一位 $k$，仅存在一个数可以“牺牲”第 $k$ 位，那么“牺牲”显然不优。因此第 $k$ 位的“牺牲”操作会进行，当且仅当存在两个数的第 $k$ 位是 $1$ 且存在一个数可以“牺牲”第 $k$ 位。

由于“牺牲”某一位并不影响比它高的位，那么比最大的“牺牲”的位要高的位不会受影响，因此对每一位前缀和，全部按位或到答案上即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200010;
int sum[32][N],x[N],y[N],cm[32][N],sum2[32][N];
vector<int> cmt[32];
void solve()
{
	int n;
	cin>>n;
	for(int i=0;i<=30;i++)
	for(int j=1;j<=n;j++)
	cm[i][j]=0;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)
	{
		int flag=0;
		for(int j=30;~j;j--)
		{
			if((1ll<<j)>y[i]) continue;
			flag|=((y[i]>>j&1)>(x[i]>>j&1));
			if(flag&&(y[i]>>j&1)) cm[j][i]=1;
		}
	}
	for(int i=30;~i;i--)
	{
		for(int j=1;j<=n;j++)
		{
			sum[i][j]=sum[i][j-1]+cm[i][j];
			sum2[i][j]=sum2[i][j-1]+(y[j]>>i&1);
		}
	}
	int q;
	cin>>q;
	while(q--)
	{
		int l,r,cmmx=-1;
		cin>>l>>r;
		for(int i=30;~i;i--) if(sum[i][r]-sum[i][l-1]>0&&sum2[i][r]-sum2[i][l-1]>1)
		{
			cmmx=i;
			break;
		}
		int res=0;
		for(int i=0;i<=cmmx;i++) res+=(1ll<<i);
		for(int i=30;i>cmmx;i--) res+=(sum2[i][r]-sum2[i][l-1]>0)*(1ll<<i);
		cout<<res<<' ';
	}
	cout<<'\n';
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
}

---

## 作者：cosf (赞：0)

可以发现，假设在 $2^j$ 位以上，$l_i = r_i$，那么，这些数是一定会被加在结果里面。我们先把 $l_i, r_i$ 相同的高位去掉，使得存在一个 $j$，满足 $l_i \lt 2^j \le r_i$。

对于每一个询问，我们先把一定存在的位算出来，设为 $s$。

我们接下来考虑一个和 $c_{j, x\dots y}$，表示 $r_x$ 到 $r_y$ 中 $2^j$ 位为 $1$ 的个数。那么，我们从高位往下枚举：

- 如果 $c_{j, x\dots y} \gt 1$，那么，我们可以选出一个数，让它 $\gets 2^j$，再选出一个数让它 $\gets 2^j - 1$，这样后面的位全部为 $1$，不可能更大了。
- 如果 $c_{j, x\dots y} = 1$ 且 $s$ 在这一位上为 $1$，则和第一种情况类似。
- 如果 $c_{j, x\dots y} = 1$ 且 $s$ 在这一位上为 $0$，我们让 $s \gets s | 2^j$ 即可。
- 否则什么都不做。

最后的 $s$ 即答案。

由贪心的性质可以分析出该做法的正确性。

时间复杂度 $O(n\log n + q(\log n + \log V))$，其中 $V$ 为值域。

```cpp
#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 200005
#define MAXL 31
#define gh(x, y) ((x) >> (y))
#define gb(x, y) (gh(x, y) & 1)

int n;

int a[MAXN], l[MAXN], r[MAXN];

int t[MAXN << 2];

void pushup(int p)
{
    t[p] = t[p << 1] | t[p << 1 | 1];
}

void build(int p, int l, int r)
{
    if (l == r)
    {
        t[p] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

int query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
    {
        return t[p];
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if (mid >= ql)
    {
        res |= query(p << 1, l, mid, ql, qr);
    }
    if (mid < qr)
    {
        res |= query(p << 1 | 1, mid + 1, r, ql, qr);
    }
    return res;
}

int c[MAXL][MAXN];

void clear()
{
    for (int j = 0; j < MAXL; j++)
    {
        for (int i = 0; i <= n; i++)
        {
            c[j][i] = 0;
        }
    }
}

void solve()
{
    cin >> n;
    clear();
    for (int i = 1; i <= n; i++)
    {
        cin >> l[i] >> r[i];
        if (l[i] == r[i])
        {
            a[i] = l[i];
            continue;
        }
        int j;
        for (j = MAXL - 1; ~j; j--)
        {
            if (gb(l[i], j) != gb(r[i], j))
            {
                a[i] = gh(l[i], j + 1) << (j + 1);
                break;
            }
        }
        for (; ~j; j--)
        {
            if (gb(r[i], j))
            {
                c[j][i]++;
            }
        }
    }
    for (int j = 0; j < MAXL; j++)
    {
        for (int i = 2; i <= n; i++)
        {
            c[j][i] += c[j][i - 1];
        }
    }
    build(1, 1, n);
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        int s = query(1, 1, n, l, r);
        for (int j = MAXL - 1; ~j; j--)
        {
            if (c[j][r] - c[j][l - 1] > 1)
            {
                s |= (1 << (j + 1)) - 1;
                break;
            }
            else if (c[j][r] - c[j][l - 1] == 1 && gb(s, j))
            {
                s |= (1 << j) - 1;
                break;
            }
            else if (c[j][r] - c[j][l - 1] == 1)
            {
                s |= (1 << j);
            }
        }
        cout << s << ' ';
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        clear();
        solve();
    }
    return 0;
}

```

---

## 作者：guihuagaoxiang (赞：0)

~~这是我的第一篇题解，描述不清楚，多多见谅~~

对于一组 $x_i$ 和 $y_i$，我们从高到低，看二进制中第一个不同位置，把 $y_i$ 分为前缀 $p_i$ 和后缀 $s_i$。 

贪心选最大就行。

看下面代码就清楚了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int N=2e5+9;
const int mod=1e9+7;
int n;
vector<array<int, 30> > s(N + 1);
vector<array<int, 30> > p(N + 1);
int num[30];
void solv(){
	cin>>n;
 	for(int i = 1; i <= n; i++){
            int x, y;
            cin >> x >> y;
            s[i] = s[i - 1];
            p[i] = p[i - 1];
            if(x==y){
            	for(int j = 0; j < 30; j++){
	                p[i][j] += (y >> j & 1);
	            }
	            continue;
			}
            int pos = __lg(x ^ y);
            int val = y & ((1 << pos + 1) - 1);
            y-=val;
            for(int j = 0; j < 30; j++){
                s[i][j] += (val >> j & 1);
                p[i][j] += (y >> j & 1);
            }
    }
    int q;
    cin >> q;
    while(q--){
        int l, r;
        int ans=0;
        cin >> l >> r;
        for(int i = 29; i >= 0; i--){
        	int num=p[r][i]-p[l-1][i];
        	if(num)num=1;
            int cnt = s[r][i] - s[l - 1][i] + num;
            if (cnt > 1){
                ans |= (1 << i + 1) - 1;
                break;
            }
            else if (cnt == 1){
                ans |= 1 << i;
            }
        }
        cout << ans << ' ';
    }
    cout << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0); 
	cout.tie(0);
	int tst=1;
	cin>>tst;
	while(tst--){
		solv();
	}
}

```

---

