# [JOIGST 2025] 雪球 2 / Snowball 2

## 题目描述

Aoi 在雪地里玩耍。在 Aoi 面前，有 $N$ 个雪球从左到右排成一列，编号为 $1$ 到 $N$。第 $i$ 个雪球初始时的大小为 $A_i$。

Aoi 希望她能造出一个大雪球。为此，Aoi 决定重复以下操作，直到雪球的数量变为 $1$ 或无法进行操作：

- 选择相邻的两个雪球，假设左侧的雪球大小为 $l$，右侧的雪球大小为 $r$，则需要满足 $0\le l-r\le 1$；
- 将选定的两个雪球合并成一个大小为 $l+r$ 的雪球；
- 换句话说，如果操作前有 $k$ 个雪球，从左到右大小分别为 $s_1,s_2,\ldots,s_k$，则可以选择一个 $t(1\le t\le k-1)$ 满足 $0\le s_t-s_{t+1}\le 1$ 进行操作，操作后的 $k-1$ 个雪球从左到右大小分别为 $s_1,s_2,\ldots,s_{t-1},s_t+s_{t+1},s_{t+2},\ldots,s_k$。

判断 Aoi 是否能通过操作将所有雪球合并成一个大雪球。

## 说明/提示

#### 【样例解释 #1】

Aoi 可以通过执行以下操作合成一个大雪球：

- 选择从左到右第 $4$ 和第 $5$ 个雪球，操作后雪球大小变为 $1,1,1,2$；
- 选择从左到右第 $1$ 和第 $2$ 个雪球，操作后雪球大小变为 $2,1,2$；
- 选择从左到右第 $1$ 和第 $2$ 个雪球，操作后雪球大小变为 $3,2$；
- 选择从左到右第 $1$ 和第 $2$ 个雪球，操作后雪球大小变为 $5$。

该样例满足所有子任务的限制。

#### 【样例解释 #2】

Aoi 无法通过执行操作合成一个大雪球。

该样例满足所有子任务的限制。

#### 【样例解释 #3】

该样例满足子任务 $2,3,4,5$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $3,4,5$ 的限制。

#### 【数据范围】

- $2\le N\le 5\times 10^5$；
- $1\le A_i\le 10^{12}(1\le i\le N)$。

#### 【子任务】

1. （$15$ 分）$A_1=A_2=\cdots=A_N$；
2. （$18$ 分）$N\le 8$；
3. （$18$ 分）$N\le 200$；
4. （$19$ 分）$N\le 5000$；
5. （$30$ 分）无附加限制。

## 样例 #1

### 输入

```
5
1 1 1 1 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
2 2 2```

### 输出

```
No```

## 样例 #3

### 输入

```
8
5 4 3 2 1 2 3 4```

### 输出

```
No```

## 样例 #4

### 输入

```
16
3 2 1 6 2 1 3 2 1 3 12 6 1 1 1 2```

### 输出

```
Yes```

# 题解

## 作者：Shuhang_JOKER1 (赞：4)

~~妥妥的分治题。~~

### 题目描述：

Aoi 面前有 $N$ 个雪球从左到右排成一列，每个雪球有一个大小。她希望将这些雪球最终合并成一个大雪球。

合并规则是：

每次可以选择两个相邻的雪球，左边的大小为 $l$，右边的大小为 $r$，要求满足 $0 ≤ l - r ≤ 1$，然后将它们合并成一个大小为 $l + r$ 的新雪球。

这个操作可以重复进行，直到只剩一个雪球或者无法继续操作。问是否可能通过一系列操作将所有雪球合并成一个。

### 题目分析：

仔细读题，不难发现只有当左边的雪球不小于右边，并且差值不超过 $1$ 时才能合并。所以合并过程对顺序和数值大小非常敏感。

我们考虑贪心。从左到右或从右到左不断合并，可能会因为局部最优选择而破坏全局合并的可能性。

分析一下样例，可以发现，比如三个大小为 $2$ 的雪球无法合并，因为无论怎么合并都会导致差值超过 $1$。

而五个大小为 $1$ 的雪球可以成功合并，说明初始值的大小和合并顺序都至关重要。

观察发现，最终的合并过程可以看作是一棵二叉树，每次合并对应一个内部节点。

整个序列被分成左右两部分，分别合并成一个雪球，然后再合并这两个结果。这马上就能想到分治。

要能最终合并，必须存在一个分割点，使得左半部分和右半部分都能独立合并成功，并且它们的总和满足合并条件。

### 题目解答：

基于刚刚的观察，我们可以考虑采用分治加二分搜索的策略。

定义一个函数 $merge(l, r)$ 表示区间 $[l, r]$ 是否可以合并成一个雪球。

关键优化在于，我们利用合并条件推导出左半部分的总和必须接近整个区间总和的一半。

具体来说，设总和为 $total$，左半部分和为 $s1$，右半部分和为 $s2$，必须满足 $s1 ≥ s2$ 且 $s1 - s2 ≤ 1$。通过推导可得 $s1$ 必须等于 $(total + 1) ÷ 2$。

因此，我们可以用前缀和数组快速计算区间和，并通过二分查找找到满足左半部分和等于 $(total + 1) ÷ 2$ 的 $mid$ 位置。

然后递归检查左右两部分是否都能成功合并。

我们可以使用 map 记忆化已经计算过的区间结果。

在函数内部，先检查边界和记忆化缓存。设 $mid$ 表示中间位置，然后计算目标左半部分和，用二分查找可能的 $mid$ 位置，并检查 $mid$ 附近几个位置是否满足条件。

如果能找到一个可行的分割点，返回 true，否则返回 false 就行了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[500005], pre[500005]; // a数组存储输入的雪球大小，pre为前缀和数组
map<pair<int, int>, bool> mp;     // 记忆化搜索的缓存，避免重复计算相同区间
// 函数：判断区间 [l, r] 是否可以合并成一个雪球
bool merge(int l, int r) {
    // 如果区间只有一个元素，直接返回 true
    if (l == r) 
        return true;
    // 创建当前区间的键值对，用于记忆化
    pair<int, int> key = {l, r};
    // 如果该区间已经计算过，直接返回缓存结果
    if (mp.find(key) != mp.end()) 
        return mp[key];
    // 计算区间 [l, r] 的总和
    long long total = pre[r] - pre[l-1];
    // 根据合并条件推导：左半部分的和 s1 必须满足 s1 >= s2 且 s1 - s2 <= 1
    // 其中 s2 = total - s1，解得 s1 的理论值
    long long s1_low = (total + 1) / 2;  
    long long s1_high = (total + 1) / 2; 
    // 目标左半部分的和
    long long t_sum = s1_low;
    // 对应的目标前缀和值
    long long t_pre = pre[l-1] + t_sum;
    // 二分查找：在 [l, r-1] 范围内寻找 pre[mid] == t_pre 的位置
    int L = l, R = r - 1;
    int mid = -1;
    while (L <= R) {
        int mid_idx = (L + R) / 2;
        if (pre[mid_idx] == t_pre) {
            mid = mid_idx;  // 找到目标位置
            break;
        } 
        else if (pre[mid_idx] < t_pre) {
            L = mid_idx + 1;  // 在右半部分继续查找
        } 
        else {
            R = mid_idx - 1;  // 在左半部分继续查找
        }
    }
    // 如果找到了一个可能的分割点 mid
    if (mid != -1) {
        int mid_s = mid;
        // 递归检查左右两部分是否都能合并成功
        if (merge(l, mid_s) && merge(mid_s + 1, r)) 
            return mp[key] = true;  // 如果可以，缓存并返回 true
    }
    // 为了防止浮点或整数边界问题，尝试 mid 附近的位置（-1, 0, +1）
    for (int i = -1; i <= 1; i++) {
        int mid_s = mid + i;
        // 检查 mid_s 是否在有效范围内
        if (mid_s < l || mid_s >= r) 
            continue;
        // 计算左右两部分的实际和
        long long s1 = pre[mid_s] - pre[l-1];
        long long s2 = pre[r] - pre[mid_s];
        // 检查是否满足合并条件：左 >= 右 且 差值 <= 1
        if (s1 >= s2 && s1 - s2 <= 1) 
            // 递归检查两部分是否可合并
            if (merge(l, mid_s) && merge(mid_s + 1, r)) 
                return mp[key] = true;  // 成功则缓存并返回
    }
    // 所有尝试都失败，缓存并返回 false
    return mp[key] = false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    // 读入雪球大小，并计算前缀和
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }
    // 调用 merge 函数判断整个区间 [1, n] 是否可合并
    if (merge(1, n)) 
        cout << "Yes\n";
    else 
        cout << "No\n";
        
    return 0;
}
```

---

## 作者：Mindulle (赞：3)

考点：
- 分治思想（递归）
- 前缀和
- 二分查找


对于区间 $[l, r]$，要能合并成一个大雪球，必须存在一个分割点 $p$，使得：

- 左半部分 $[l, p]$ 的和 $≥$ 右半部分 $[p+1, r]$ 的和。
- 左半部分的和与右半部分的和相减 $≤ 1$。
- 左右两部分自身都能合并成功。

此时，本题方法就非常明显了，我们每次将区间折半进行判断，若最后剩下 $1$ 个数，则已经成立，剩下 $2$ 个数判断一下就好了，可以用递归法解决。

至于求和部分，前缀和预处理即可。折半可以使用二分查找解决。

Code：

```cpp
bool check(int l,int r){
    if(l==r) return 1;
    if(l+1==r) return a[l]-a[r]>=0 and a[l]-a[r]<=1;
    int mid=(sum[r]+sum[l-1]+1)>>1;
    int pos=lower_bound(sum+1,sum+n+1,mid)-sum;
    if(sum[pos]!=mid) return 0;
    return check(l,pos) and check(pos+1,r);
}
```

警示后人：

- 看清楚数据范围哦！

---

## 作者：LotleTos (赞：2)

一个大雪球只能有两个相邻的雪球合成，那么一个大雪球只能由原来小雪球序列的连续区间合成而来。

于是对于每个区间，枚举断点，判断左右两半能否合成出大雪球或者本身就是一个雪球（即区间长度为 $1$），如果有一个断点合法，那么这个区间就能合成出大雪球。

这样递归这个雪球序列，即可得出答案。

要开 `long long` ！
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[500010];
long long sum[500010];
bool f(int l,int r){
	if(l==r){
		return 1;
	}
	for(int i=l;i<r;i++){
		if(sum[i]-sum[l-1]-sum[r]+sum[i]>=0&&sum[i]-sum[l-1]-sum[r]+sum[i]<=1){
			if(f(l,i)&&f(i+1,r)){
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=a[i]+sum[i-1];
	}
	if(f(1,n)){
		cout<<"Yes";
	}
	else{
		cout<<"No";
	}
}
```

---

## 作者：IntoTheDusk (赞：2)

::::info[题面]
给定 $n$ 个数 $a_{1 \dots n}$，你可以执行 $n-1$ 操作，每次操作选择一个正整数 $i$ 且 $0 \le a_i-a_{i+1} \le 1$ 并把 $a_i,a_{i+1}$ 合并为 $a_i+a_{i+1}$。试判断能否把序列 $a$ 操作到只剩一个数。

$2 \le n \le 5 \times 10^5,1 \le a_i \le 10^{12},\rm{1.0s,1024MiB}$。
::::

设 $f(l,r,s)$ 表示能否通过若干次操作将 $[l,r]$ 合并为一个大小为 $s$ 的数。可以证明，答案为 $f(1,n,\sum\limits_{i=1}^{n}a_i)$。

注意到这么一个事实：如果若干个数可以被一步合并为 $S$，则最后一次操作之前这些数一定只剩两个，且左边的数必然为 $\lceil\frac{S}{2}\rceil$，右边的数必然为 $\lfloor\frac{n}{2}\rfloor$。据此，我们得出了一个结论：若 $\exists l \le p < r,\sum\limits_{i=l}^{p}a_i=\lceil\frac{S}{2}\rceil$，则 $f(l,r,s)=f(l,p,\lceil\frac{S}{2}\rceil) \land f(p+1,r,\lfloor\frac{n}{2}\rfloor)$。否则，$f(l,r,s)=0$。

据此，我们直接分治即可。对于 $p$，考虑到序列的所有数均是正数，我们可以在求出前缀和后直接二分或者开桶记录。时间复杂度 $O\left(n\log n\right)$。

[评测记录](https://www.luogu.com.cn/record/231590319)

::::success[一份C++实现]
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n,a[N],sum[N];
map<int,int>pos;
bool solve(int l,int r,int s){
	if(l==r&&a[l]==s) return true;
	int rs=s/2;int ls=s-rs;
	int p=pos[ls+sum[l-1]];
	if(p==0) return false;
	if(p>=r) return false;
	return solve(l,p,ls)&&solve(p+1,r,rs);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++) pos[sum[i]]=i;
	bool ans=solve(1,n,sum[n]);
	if(ans) cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```
::::

---

## 作者：Indestructible (赞：1)

## 题意

形式化题面：对于 $n$ 个正整数 $A_1\sim A_n$，第 $i$ 次操作可选择一个 $t$，满足 $1\leq t\leq n-i$ 且 $0\leq A_t-A_{t+1}\leq 1$，使 $A_t\gets A_t+A_{t+1}$，并将 $A_{t+1}$ 之后的所有数前移一位。判断这 $n$ 个数是否可以合并为 $1$ 个。

感性理解：$n$ 个正整数，每次取相邻两个，若相等或前项比后项大 $1$，则可以相加合并。判断这 $n$ 个数是否可以合并为 $1$ 个。

## 做法

### ?? 分

全部输出 $\texttt{Yes}$ 或 $\texttt{No}$，也可以随机输出。

### 100 分

~~因为想部分分时直接想出了正解，就不写部分分做法了。~~

尝试逆推。

将所有数合成为 $1$ 个的上一步的两个数必然相等或前数比后数大 $1$，否则直接无解。而当相等时，所有数的总和是偶数，大 $1$ 时是奇数。

于是我们将整个数列分成了两个区间。然后对这两个区间同样求解。区间长度为 $2$ 时直接判断。

于是做法就出来了。

用一个前缀和数组记录和，对区间 $[1,n]$ 递归判断是否存在上述有解情况。查找和值用 `lower_bound` 即可。

最好情况下的时间复杂度为 $O(n\log n)$，$\log$ 是 `lower_bound` 的复杂度。忽略数据范围，最差情况下为 $O(n^2\log n)$，但要取得最差情况，$A_1$ 将达到 $2^n$，显然不可能。事实上，代码在本题的 309 个测试点跑得飞快。

综上，时间复杂度为 $O(n\log n)$。

## 代码

不开 `long long` 见祖宗。

```cpp line-numbers
#include <bits/stdc++.h>
#define fr(i, x, y) for (int i = (x); i <= (y); i ++)
#define int long long
using namespace std;

const int N = 5e5 + 6;
int n, a[N], s[N];

bool f(int l, int r){
	if (r == l) return 1;
	if (r - l == 1) return a[l] >= a[r] && a[l] - a[r] <= 1; 
	// 以上特判，以下核心代码 
	int mid = (s[r] + s[l - 1] + 1) >> 1; // 奇数加 1 以取得和的中间值 
	int p = lower_bound(s + 1, s + n + 1, mid) - s; // 中间值所在的下标 
	if (s[p] != mid) return 0; // 中间值不存在于前缀和数组中返回 0 
	return f(l, p) && f(p + 1, r);  // 中间值存在，递归查询 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	fr(i, 1, n) cin >> a[i], s[i] = s[i - 1] + a[i];
	cout << (f(1, n) ? "Yes" : "No");
	return 0; // 好习惯祝 CSP2025 RP++ 
}
```

[AC 记录](https://www.luogu.com.cn/record/231956703)

---

## 作者：tuxiaolai (赞：1)

~~原来还有这么水的分治。~~  
首先，我们可以考虑合并的最后一步，显然，一定是整个序列的左边一部分合并后的结果和右边一部分合并。也就是说我们只要找到符合要求的这个中间点，并像这样判断左右两边是否都可行即可。不难想到[分治思想](https://oi-wiki.org//basic/divide-and-conquer/#%E5%88%86%E6%B2%BB)。  
对于一个区间 $[l,r]$，若 $l=r$，则一定可行；否则我们要找到一个点 $mid$，使得 $0 \le \sum_{i=l}^{mid} a_i - \sum_{i=mid+1}^{r} a_i \le 1$。由于 $1\le a_i$，易证 $\sum_{i=l}^{mid} a_i=\lceil \frac{\sum_{i=l}^{r} a_i }{2} \rceil$，因此，只要前缀和加二分即可找出 $mid$。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[500010],sum[500010];
bool hhh(long long l,long long r){   //想不出叫啥名了
    if(l==r){
        return 1;
    }
    long long res=(sum[r]-sum[l-1]+1)/2;
    long long ll=l,rr=r;
    long long mmid=0;
    while(ll<=rr){
        long long mid=ll+(rr-ll)/2;
        if(sum[mid]-sum[l-1]<res){
            ll=mid+1;
        }else if(sum[mid]-sum[l-1]>res){
            rr=mid-1;
        }else{
            mmid=mid;
            break;
        }
    }
    if(mmid==0){
        return 0;
    }
    return hhh(l,mmid) && hhh(mmid+1,r);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    if(hhh(1,n)){
        cout<<"Yes\n";
    }else{
        cout<<"No\n";
    }
    return 0;
}
```
完结撒花！

---

## 作者：__szh_DNCB__ (赞：0)

蒟蒻的第 $12$ 篇题解。

这个黄题质量还有点高。由于序列长最大是 $5 \times 10^5$，直接模拟（预计时间复杂度在 $O(n^2)$）显然会超时。看到题目标签有二分和分治，所以我想到了采用二分和递归解决。

大致的思想就是把整个序列拆成左右两个子序列，使得左侧子序列大于等于右侧子序列的和，且两个子序列的差不超过 $1$。反复做这样的操作就可以把整个子序列拆分成 $n$ 个长度为 $1$ 的子序列啦。

又因为题目标签有“前缀和”，我们考虑用前缀和数组 $pre$ 维护前缀和，其中 $pre_i$ 表示序列前 $i$ 个元素的和。这样我们的时间复杂度是 $O(n \log n)$，可以通过本题。

**温馨提示：十年 OI 一场空，不开 `long long` 见祖宗喵。**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010;
int a[N],pre[N];
bool solve(int l,int r,int targ){
	if (l == r)return true;
    if (pre[r]-pre[l-1] != targ)return false;
    int m = (targ+1) / 2;
    int targp = pre[l-1] + m;
    int *bpt = pre+l,*ept = pre+r;
    int *f = lower_bound(bpt,ept,targp);
    if (f != ept && *f == targp)return (solve(l,f-pre,m)&&solve(f-pre+1,r,targ-m));
    return false;
}
signed main(){
	int n;
    cin >> n;
    for (int i=0;i<n;i++)cin>> a[i];
    pre[0] = 0;
    for (int i=1;i<=n;i++){
        pre[i] = pre[i-1]+a[i-1];
    }
    if (solve(1,n,pre[n]))puts("Yes");
	else puts("No");
    return 0;
}
```

---

