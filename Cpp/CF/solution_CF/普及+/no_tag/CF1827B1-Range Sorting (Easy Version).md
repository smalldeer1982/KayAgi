# Range Sorting (Easy Version)

## 题目描述

The only difference between this problem and the hard version is the constraints on $ t $ and $ n $ .

You are given an array $ a $ , consisting of $ n $ distinct integers $ a_1, a_2, \ldots, a_n $ .

Define the beauty of an array $ p_1, p_2, \ldots p_k $ as the minimum amount of time needed to sort this array using an arbitrary number of range-sort operations. In each range-sort operation, you will do the following:

- Choose two integers $ l $ and $ r $ ( $ 1 \le l < r \le k $ ).
- Sort the subarray $ p_l, p_{l + 1}, \ldots, p_r $ in $ r - l $ seconds.

Please calculate the sum of beauty over all subarrays of array $ a $ .

A subarray of an array is defined as a sequence of consecutive elements of the array.

## 说明/提示

In the first test case:

- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [4] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [6, 4] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 1 = 1 $ .In the second test case:

- The subarray $ [3] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [10] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [6] $ is already sorted, so its beauty is $ 0 $ .
- The subarray $ [3, 10] $ is already sorted, so its beauty is $ 0 $ .
- You can sort the subarray $ [10, 6] $ in one operation by choosing $ l = 1 $ and $ r = 2 $ . Its beauty is equal to $ 2 - 1 = 1 $ .
- You can sort the subarray $ [3, 10, 6] $ in one operation by choosing $ l = 2 $ and $ r = 3 $ . Its beauty is equal to $ 3 - 2 = 1 $ .

 The sum of beauty over all subarrays of the given array is equal to $ 0 + 0 + 0 + 0 + 1 + 1 = 2 $ .

## 样例 #1

### 输入

```
5
2
6 4
3
3 10 6
4
4 8 7 2
5
9 8 2 4 6
12
2 6 13 3 15 5 10 8 16 9 11 18```

### 输出

```
1
2
8
16
232```

# 题解

## 作者：_sunkuangzheng_ (赞：7)

是官方题解做法捏。

感觉评绿是不是有点低的说 :) 

**【题目大意】**

长度为 $n(1 \le n \le 5 \times 10^3)$ 的数组 $a$，将一个子段 $[l,r]$ 排序的代价是 $r-l$，一个数组的代价定义为将这个数组排好序所需的最小代价，求数组 $a$ 所有子数组的代价之和。

**【题目分析】**

一些表达：$\max([l,r])$ 和 $\min([l,r])$ 表示区间 $[l,r]$ 的最值。

首先证明一些性质。

- 性质 $1$：为了达到最优，每次选择的一定是不交区间。

证明：如果选择了区间 $[l_1,r_1]$ 和 $[l_2,r_2]$，其中 $r_1 > l_2$，那么直接选择区间 $[\min(l_1,l_2),\max(r_1,r_2)]$ 显然更优。

- 性质 $2$：独立的处理每个不交子区间不劣于处理整个大区间。

具体的，如果有两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$，其中 $l_2 = r_1+1$，若满足 $\max([l_1,r_1]) < \min([l_2,r_2])$，那么分开排序两个区间。

证明：整体排序花费为 $r_2 -l_1$，而分开排序花费为 $r_1-l_1+r_2-(r_1+1)=r_2-l_1-1$。

我们能根据上面的信息得到结论：区间 $[l,r]$ 的代价为 $r-l - x$，其中 $x$ 为满足 $\max([l,x]) < \min([x+1,r])$ 的下标 $x$ 数量。因为根据上面的结论，如果满足上式的 $x$ 存在，则分开处理会让答案 $-1$。

然后我们考虑如何用这些性质解题。直接枚举区间可能会使复杂度升到 $\mathcal O(n^3)$。我们枚举每个 $i$，钦定 $a_i$ 为区间的最小值，则需要找到极大的 $a_i$ 可以当最小值的范围。这也等价于，找到两个位置 $x,y$ 使得 $a_x < a_i$ 并且 $a_y < a_i$，让 $y-x$ 尽可能大。然后我们需要满足 $\max([l,x]) < \min([x+1,r])$，即找到一个 $z(z < x)$ 满足 $a_z > a_i$，并且 $x-z$ 尽可能大。最终满足条件的合法 $l,r$ 取值范围为 $z < l \le x,i \le r < y$，即对答案有 $(x-z)(y-i)$ 的贡献。

我们一开始先加上所有区间长度，然后枚举 $i$ 的过程中寻找 $x,y,z$，每一次寻找 $x,y,z$ 时间复杂度是 $\mathcal O(n)$，总时间复杂度是 $\mathcal O(n^2)$。当然，这个算法可以优化至 $\mathcal O(n \log n)$ 甚至 $\mathcal O(n)$，详见 B2 题解捏。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[5005],ans,l,r,k;
int main(){
    for(cin >> t;t -- && cin >> n;cout << ans << "\n",ans = 0){
        for(int i = 1;i <= n;i ++) cin >> a[i],ans += (i - 1) * (n - i + 1);
        for(int i = 1;k = l = r = i,i <= n;ans -= (r - i) * (k - l),i ++){
            while(k > 0 && a[k] >= a[i]) k --;l = k;
            while(l > 0 && a[l] <= a[i]) l --;
            while(r <= n && a[r] >= a[i]) r ++;
        }
    }
}
```







---

## 作者：lalaouye (赞：4)

首先，很容易想到最多的代价怎么求，这个时候我们发现，在一段区间内，把要排序的区间切得越碎越好，比如说在 $[2,1,4,3]$ 中，我们在 $1$ 后面断一下，然后分开排序，代价会减一。那么我们的目的就是让每段切得越碎越好。


暴力枚举区间肯定是不可取的，那怎么办？转换一下思路，枚举每一个断的位置，看一下有多少个区间可以被它所断。什么时候不可断？ 在 $[4,1,3,2]$ 中，我们不能在 $1$ 后面断，因为 $4$ 是要到第 $4$ 个位置的，然而 $[1,5,3,6,7,9]$ 是可以在 $3$ 后面断的，我们可以得出结论，如果区间可以在 $r$ 位置后所断，那么必有

$\max\limits_{1<x<r}(a_x) < \min\limits_{r+1<x<n}(a_x)$

另外，容易想到断完之后相当于分开处理，断的时候不会影响到别的能断地方。所以现在我们枚举每个位置 $r$，它能断的区间总数 $cnt_r$，最大代价总和为 $sum$，那么答案就是 $sum-\sum cnt_i$，因为断一下代价就减一。

那么考虑如何统计，首先题目中说数字两两各不相同，那么我们将这个数组变成排列，把每个位置的数变成初始数在数组中的排名。在枚举位置的时候，先往后枚举求最小值，然后每次都让 $s_{minn}+1$，意思是后半段最小值为 $minn$ 的区间又多了一个，然后往前依次枚举，求最大值，让 $sum-\sum_{i=maxn+1}^n s_i$，意思是最大值为 $maxn$ 时，能让该位置所断的区间数为后段区间中最小值大于 $maxn$ 的总数，其中求和再提前用前缀和处理，具体可看代码，变量名可能与上面的讲解不相同。

```cpp
signed main ()
{
	int T = rd ();
	while (T --)
	{
		n = rd ();
		for (int i = 1; i <= n; i ++)
			a[i].x = rd (), a[i].id = i;
		sort (a + 1, a + n + 1, cmp);
		for (int i = 1; i <= n; i ++)
			p[a[i].id] = i;
		int res = 0;
		for (int i = 1; i < n; i ++) res += i * (n - i);//最大代价
		for (int i = 1; i < n; i ++)
		{
			memset (sum, 0, sizeof sum);
			int minn = 1e9;
			for (int j = i + 1; j <= n; j ++)
			{
				minn = min (minn, p[j]);
				sum[minn] ++;
			}//现在的sum[i]表示最小值为i的后段区间个数
			for (int j = n; j >= 1; j --)
			{
				sum[j] += sum[j + 1];
			}//现在的sum[i]表示最小值大于等于i的后段区间个数
			int maxn = 0;
			for (int j = i; j >= 1; j --)
			{
				maxn = max (maxn, p[j]);
				res -= sum[maxn + 1];//让最大代价直接减去就行
			}
		}
		printf ("%lld", res);
		puts("");
	}
}
```


---

## 作者：System32 (赞：3)

提供一种类似单调栈的做法。

对于一个单独的数字，我们可以认为它是一个长度为 $1$，代价为 $0$ 的区间。然后问题就变成了把一个序列分成多个区间，使得排序每个区间后序列有序，求区间个数的最大值。

假设当前已经有了一个 $[l,r]$ 的子串，最优解为 $[l,d_1] \ldots [d_{k-1}+1,r]$，总计 $k$ 个区间。要推到 $[l,r+1]$，先新建一个区间 $[r+1,r+1]$，然后考虑合并。

对于两个区间 $[a,b],[b+1,c]$，当且仅当 $[a,b]$ 中的最大值大于 $[b+1,c]$ 中的最小值时才有必要合并。

枚举 $l$ 之后，很明显可以用单调栈来维护，并且代价只会在合并时增加 $1$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int a[5010];

signed main() {
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			stack<pair<int, int>> s;
			int v = 0;
			for (int j = i; j <= n; j++) {
				pair<int, int> temp = {a[j], a[j]};
				while (!s.empty() && s.top().second > temp.first) {
					temp.first = min(temp.first, s.top().first);
					temp.second = max(temp.second, s.top().second);
					s.pop();
					v++;
				}
				s.push(temp);
				ans += v;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：苏联小渣 (赞：3)

提供一个只能过 Easy Version 的方法。

考虑一下 $r-l$ 怎样最小：很明显，对于一个区间 $[L,R]$，其分成所有段的 $r-l$ 之和（在这里，单独的一个数也算作一段，虽然其 $r-l=0$），就是 $R-L+1-S_{L,R}$，其中 $S_{L,R}$ 表示操作的次数。

显然我们需要让操作次数尽量多，而且显然所有操作区间肯定不交。考虑一个序列 $a$，记其从小到大排序后的序列为 $b$。那么对 $a$ 序列的 $[l,r]$ 操作，当且仅当对 $a[l,r]$ 排序后的 $a'[l,r]=b[l,r]$。那么就有一个贪心：记上一次操作的右端点为 $[l,r]$，当前遍历到 $i$，如果 $a[r+1,i]$ 排序后和 $b[r+1,i]$ 相等，那么代价加上 $i-r-1,r \gets i$。根据上面的推导，这样肯定是最优的。

举个例子：$a=[1,3,2]$，$b=[1,2,3]$。首先，$a[1,1]=b[1,1]$，那么对它操作，代价加 $0$；下一次，$a[2,3]$ 排序后和 $b[2,3]$ 相等，那对 $a[2,3]$ 进行操作，代价为 $1$。

~~这个时候我就想到了一个用哈希判断同构的 $O(n^3)$ 解法，当时很好奇这题怎么 $O(n^2)$~~。显然需要做到 $O(n^2)$，我们需要考虑插入一个数对答案会有什么影响。

考虑一些性质。设两个操作区间为 $[l_1,r_1],[r_1+1,r_2]$，那么显然有：

$$\max_{i=l_1}^{r_1}a_i \le \max_{i=r_{1}+1}^{r_2}a_i,\max_{i=l_1}^{r_1}a_i \le \min_{i=r_{1}+1}^{r_2}a_i,$$

不然它们肯定无法在值域上连成一段。那么到了这里，思路就清晰了：对于一个序列，$a_i$ 可以作为一段的开头，当且仅当 $a_i \ge \max_{j=1}^{i-1} a_j$。

同时，如果当前数 $a_j$ 小于上一段的最大值，那么我们就暴力往回跳，看跳到哪一段满足 $a_j$ 大于等于前一段的最大值，然后把中间跳的这些段合并起来就好了，这个答案贡献是容易统计的。同时，左端点固定，往回跳的次数是 $O(n)$ 的，总时间复杂度就是 $O(n^2)$。不过这么想似乎很难上数据结构做到更优的复杂度。

举个例子，对于 $a=[1,3,2,4]$，考虑在末尾插入 $1$。

对于原序列 $a$，其操作区间分别是 $[1],[3,2],[4]$。插入 $1$ 之后：

- $1<3$，也就是小于上一段的最大值，合并 $[3,2,4]$；

- $1 \ge 1$，也就是大于等于上一段最大值，符合条件。此时操作区间更换为 $[1],[3,2,4,1]$。答案也是容易维护的。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, m, ans, a[5010], l[5010], mx[5010];
long long tot;
int main(){
	scanf ("%d", &t);
	while (t --){
		tot = 0;
		scanf ("%d", &n);
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
		}
		for (int i=1; i<=n; i++){
			ans = m = 0;
			for (int j=i; j<=n; j++){
				if (a[j] >= mx[m]){
					l[++m] = j, mx[m] = a[j];
				}
				else if (a[j] < mx[m-1]){
					int pos = m-1;
					ans -= j - l[m];
					ans ++;
					while (a[j] < mx[pos]){
						ans -= l[pos+1] - l[pos] - 1;
						pos --;
					}
					pos ++;
					ans += j - l[pos];
					mx[pos] = mx[m], m = pos;
				}
				else{
					ans ++;
					mx[m] = max(mx[m], a[j]);
				}
				tot += ans;
			}
		}
		printf ("%lld\n", tot);
	}
	return 0;
}
```

---

## 作者：Engulf (赞：1)

这是可通过 Hard Version 的做法。

首先，在最优情况下，排序操作的区间不重叠。[证明](https://www.luogu.com.cn/paste/gi32sfm4)。

考虑容斥，每次都直接对整个区间排序，此时答案为 $\sum\limits_{i = 1}^{n - 1}\sum\limits_{j = i + 1}^{n}(j - i) = \sum\limits_{i = 1}^{n - 1} i(n - i)$。

想想对于一个区间 $[l, r]$，如何减少代价。如果存在一个位置 $i$，把整个区间断开变成 $[l, i)$ 和 $[i, r]$，分别排序，代价为 $r-i+i-1-l = r - l - 1$，这使得代价减小 $1$。

这样做的前提是左边的最大值大于右边的最小值（注意题目条件提到元素两两不同），即 $\max\limits_{k=l}^{i - 1}a_k < \min\limits_{k = i}^{r}a_k$。

[如果你有点困惑，在想：“为什么只考虑减少 $1$ 的情况，如果是这样 $[\color{red}2\color{black}, \color{Red}1\color{black}, 3, 4, \color{red}6\color{black}, \color{red}5\color{blac}]$”，对 $[1, 6]$ 排序的代价明明减少了 $2$”这种事情的话。](https://www.luogu.com.cn/paste/94mhuizf)

这样，问题变为求对于每一个 $(l, r)$，满足那个要求的 $i$ 的个数。这个是复杂的，考虑转换一下求法，考虑每个 $i$ 的贡献。

钦定 $a_i$ 是区间最小值，设：
- $x$ 是 $i$ 右边第一个使得 $a_x<a_i$ 的 $x$。
- $y$ 是 $i$ 左边第一个使得 $a_y < a_i$ 的 $y$。
- $z$ 是 $y$ 左边第一个使得 $a_z > a_{\color{red}i\color{black}}$ 的 $z$。

把下标写出来大概是这个模样：

$$[\cdots, z, \color{red}\cdots\color{black}, y, \color{green}\cdots\color{black}, i, \color{blue}\cdots\color{black}, x, \cdots]$$

- 红色部分的数，均 $<a_i$
- 绿色部分的数，均 $>a_i$
- 蓝色部分的数，均 $>a_i$

那么对于这个 $i$ 而言合法的 $l \in (z, y]$，合法的 $r \in [i, x)$。$r$ 的范围保证了 $a_i$ 是右边部分最小值，$l$ 则保证了左边部分再大，也都是 $<a_i$ 的，至此满足了要求。满足条件的区间数为 $(x - i)(y-z)$，从初始的答案中减去即可。

求出 $x,y,z$ 是经典问题，使用 ST 表和二分即可解决。代码实现起来非常舒适。时间复杂度 $O(n\log^2n)$。

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
        vector<int> a(n);
        vector<vector<int>> mn(n, vector<int>(__lg(n) + 1));
        vector<vector<int>> mx(n, vector<int>(__lg(n) + 1));
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mn[i][0] = mx[i][0] = a[i];
        }

        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                mn[i][j] = min(mn[i][j - 1], mn[i + (1 << j - 1)][j - 1]);
                mx[i][j] = max(mx[i][j - 1], mx[i + (1 << j - 1)][j - 1]);
            }

        auto queryMax = [=](int l, int r) {
            int k = __lg(r - l + 1);
            return max(mx[l][k], mx[r - (1 << k) + 1][k]);
        };
        auto queryMin = [=](int l, int r) {
            int k = __lg(r - l + 1);
            return min(mn[l][k], mn[r - (1 << k) + 1][k]);
        };

        ll ans = 0;
        for (int i = 1; i < n; i++) ans += 1ll * i * (n - i);

        auto rless = [=](int pos, int val) {
            int l = pos + 1, r = n - 1, res = n;
            while (l <= r) {
                int mid = l + r >> 1;
                if (queryMin(pos + 1, mid) < val) res = mid, r = mid - 1;
                else l = mid + 1;
            }
            return res;
        };
        auto lless = [=](int pos, int val) {
            int l = 0, r = pos - 1, res = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (queryMin(mid, pos - 1) < val) res = mid, l = mid + 1;
                else r = mid - 1;
            }
            return res;
        };
        auto lgreater = [=](int pos, int val) {
            int l = 0, r = pos - 1, res = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (queryMax(mid, pos - 1) > val) res = mid, l = mid + 1;
                else r = mid - 1;
            }
            return res;
        };

        for (int i = 0; i < n; i++) {
            int x = rless(i, a[i]), y = lless(i, a[i]);
            int z = lgreater(y, a[i]);
            // debug("i: %d, (%d, %d] and [%d, %d)\n", i, z, y, i, x);
            ans -= 1ll * (x - i) * (y - z);
        }

        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

提供一个让我无法想到 Hard Version 的做法。

猜想应该是容斥，总共答案是 $\sum\limits_{i=1}^n(i-1)(n-i+1)$，而看到 $r-l$ 让我想到了间隔，所以，我采用了找间隔计算贡献的方法。

对于 $L\sim R$ 的区间，考虑 $i\sim i+1(L\le i<R)$ 的间隔，需要满足 $\forall i\in[L,i],j\in[i+1,r],a_i<a_j$（这里的中括号可能不规范，因为可能相等）。于是，我们得到了一个枚举间隔、左端点、右端点的 $O(n^3)$ 做法。

发现枚举 $(i,i+1)$ 之间的间隔，枚举左端点 $L$，在左端点 $L$ 减小的时候，需要满足条件，那么 $R$ 肯定是不增的。但是为什么不能先找到一个 $L=i$ 的时候的 $R$，然后类似双指针一样的从右往左枚举呢？理由是，如果 $R$ 向左移动之后，导致最小值没了，那么，下一个最小值是什么，这个无法直接得知。

思考到这里，发现这个问题其实是很好解决的，可以先处理出 $i+1\sim j$ 的最小值 $mm_j$，这样就可以快速知道右侧的的 $\min$ 了。

由此，复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5, inf = 1e18;
int T, n, a[N], ans, L[N], q[N], t, R[N], aa[N], maxn, mm[N];
signed main(){
    scanf("%lld", &T);
    while(T--){
        scanf("%lld", &n);
        for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
        ans = 0ll;
        for(int i = 2; i <= n; i++){
            ans += (i - 1) * (n - i + 1);
        }
        for(int i = 1; i < n; i++){
            int k = i + 1;
            mm[i] = inf;
            while(k <= n && a[k] > a[i]){
                mm[k] = min(mm[k - 1], a[k]);
                k++;
            }
            k--;
            maxn = a[i];
            for(int j = i; j; j--){
                if(a[j] > maxn) maxn = a[j];
                while(k >= i + 1 && mm[k] < maxn) k--;
                ans -= k - i;
                //printf("%lld %lld %lld\n", i, j, k);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
/*
1
5
9 8 2 4 6
*/
```

但是本蒟蒻不会扩展到 $n\le 3\cdot10^5$ 的情况了，如果大佬有扩展的方法，可以评论/私信。

---

