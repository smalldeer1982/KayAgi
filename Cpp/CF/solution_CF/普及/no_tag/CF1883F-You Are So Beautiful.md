# You Are So Beautiful

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ . Calculate the number of subarrays of this array $ 1 \leq l \leq r \leq n $ , such that:

- The array $ b = [a_l, a_{l+1}, \ldots, a_r] $ occurs in the array $ a $ as a subsequence exactly once. In other words, there is exactly one way to select a set of indices $ 1 \leq i_1 < i_2 < \ldots < i_{r - l + 1} \leq n $ , such that $ b_j = a_{i_j} $ for all $ 1 \leq j \leq r - l + 1 $ .

## 说明/提示

In the first test case, there is exactly one subarray $ (1, 1) $ that suits us.

In the second test case, there is exactly one subarray $ (1, 2) $ that suits us. Subarrays $ (1, 1) $ and $ (2, 2) $ do not suit us, as the subsequence $ [1] $ occurs twice in the array.

In the third test case, all subarrays except $ (1, 1) $ and $ (3, 3) $ are suitable.

## 样例 #1

### 输入

```
6
1
1
2
1 1
3
1 2 1
4
2 3 2 1
5
4 5 4 5 4
10
1 7 7 2 3 4 3 2 1 100```

### 输出

```
1
1
4
7
4
28```

# 题解

## 作者：One_JuRuo (赞：7)

## 思路

最开始都错题了，以为是不能通过另一种子串的选择方法得到这个子串就算做独特字串，实际上，是需要不能通过选择子序列的方式得到这个子串才满足条件，导致赛时没做出来（悲）。

实际上，如果一个子串满足条件，那么一个必要条件就是子串左侧没有与该子串左端一样的数字并且子串右侧也没有与该子串右端一样的数字。

可以发现，这个条件也是子串符合题意得充分条件。

如果满足这个条件，那么左侧一定没有第二种选法可以获得这个子串的前缀，同理右侧也无法获得这个子串的后缀，所以一定没有第二种选法可以获得这个字串。

所以，我们可以根据这个充要条件去找答案。

那么首先一个字串的左端点的数字必须第一次出现，右端点则必须最后一次出现，很容易地，我们想到可以预处理某点右侧最后一次出现的数字的个数，这个可以 $O(n)$ 预处理。

那么再 $O(n)$ 正序扫一遍，当一个数字第一次出现时，直接将答案加上这个位置右侧最后一次出现的数字的个数，注意的是这个位置也要考虑，因为如果这个位置既是第一次出现，也是最后一次出现，那么只选这个数字的长度为 $1$ 的子串也符合条件。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,a[100005],ans,r[100005];
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n),ans=0,r[n+1]=0;
		for(long long i=1;i<=n;++i) scanf("%lld",&a[i]);
		map<long long,long long>m;
		for(long long i=n;i>=1;--i) if(!m.count(a[i])) r[i]=r[i+1]+1,m[a[i]]=1;else r[i]=r[i+1];
		map<long long,long long>m1;
		for(long long i=1;i<=n;++i) if(!m1.count(a[i])) ans+=r[i],m1[a[i]]=1;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：FFTotoro (赞：5)

考虑什么样的元素才可以成为区间的左 / 右端点。以左端点为例：当且仅当在它左边没有与它相等的元素，它才可能成为左端点。证明考虑充分性和必要性，一方面如果它左边有与它相等的元素，那么将“子序列”的端点移到左边那个元素，子序列的所有元素的值也不会变；另一方面，因为判断的是整个连续的子段，假设一个非端点元素移动了，那么它与端点元素的相对位置就会改变，而又已知左端点的左边不可能有与它相等的元素（右端点同理），所以它一移动这个序列必然会改变。

预处理出所有备选的左端点和右端点（使用 STL `map`；[别用 `unordered_map`](https://codeforces.com/blog/entry/62393)，昨晚房间里面有个人用这个被叉了），装进两个数组，然后枚举左端点，用 `lower_bound` 来匹配可用的右端点，统计方案总和即可。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin>>t;
  while(t--){
    int n,c=0; cin>>n;
    vector<int> a(n),l,r;
    for(auto &i:a)cin>>i;
    map<int,bool> m,m2;
    for(int i=0;i<n;i++)
      if(!m[a[i]])m[a[i]]=true,l.emplace_back(i);
    for(int i=n-1;~i;i--)
      if(!m2[a[i]])m2[a[i]]=true,r.emplace_back(i);
    // 即第一次出现的，左端点的从左往右扫，右端点从右往左扫
    reverse(r.begin(),r.end());
    for(int i:l)c+=r.size()-(lower_bound(r.begin(),r.end(),i)-r.begin());
    // 统计答案
    cout<<c<<'\n';
  }
  return 0;
}
```

---

## 作者：Iniaugoty (赞：2)

我是赛时第七个通过本题的，手速还是有些慢了。

>给定一个长 $n$ 的序列 $a$。对于区间 $[l, r]$，如果 $a$ 没有其它子序列（不一定连续）和这个区间完全相同，则这个区间合法。求出合法区间数量。

这个题长得就很分治。

设 $[l, r]$ 是当前区间，$[l, mid]$ 和 $[mid + 1, r]$ 是这个区间分下去的左右两个区间。

先递归计算左右端点都在 $[l, mid]$，和左右端点都在 $[mid + 1, r]$ 的数量，然后考虑左端点在 $[l, mid]$，右端点在 $[mid + 1, r]$ 的区间数量。不难想到，如果一个区间非法，意味着区间左端点的左边有一个和左端点相同的数，或者右端点的右边有一个和右端点相同的数；否则一定没有另一个子序列和这个区间相同。这样就好办了，求出 $[l, mid]$ 有多少个数是第一个出现的这个数，$[mid + 1, r]$ 有多少个数是最后一次出现的这个数，乘法原理一乘就出来了。

```cpp
// fst[i]/lst[i] 表示第一次/最后一次出现数字 i 的位置
// 值域比较大，注意离散化，不过你要写平衡树维护我也拦不了你 [doge]
LL Solve(int l, int r) {
	if (l == r) return fst[a[l]] == lst[a[l]];
	int mid = l + r >> 1;
	LL res = Solve(l, mid) + Solve(mid + 1, r);
	int cntl = 0, cntr = 0;
	F(i, l, mid) if (fst[a[i]] == i) ++cntl;
	F(i, mid + 1, r) if (lst[a[i]] == i) ++cntr;
	res += (LL) cntl * cntr;
	return res;
}
```

以上是赛时做法。

你愉快的搞完了分治并获得了 Pretest Pass，然后你会发现你已经会了合法区间的 $\mathcal O (1)$ 判定了，而且这个判定只与左端点或右端点有关，这个分治就显得很鸡肋。于是一个 $\mathcal O (n)$ 的做法呼之欲出：枚举每一个可以作为合法区间左端点的位置（某个数字第一次出现），求出这个位置右边可以作为合法区间右端点的位置数量（某个数字最后一次出现），后者可以用一个后缀和维护。不过复杂度瓶颈是离散化，所以仍然是 $\mathcal O (n \log n)$ 的。

```cpp
// s 是后缀和
F(i, 1, k) fst[i] = lst[i] = s[i] = 0;
F(i, 1, n) if (!fst[a[i]]) fst[a[i]] = i;
dF(i, n, 1) if (!lst[a[i]]) lst[a[i]] = i;
dF(i, n, 1) s[i] = s[i + 1] + (lst[a[i]] == i);
LL ans = 0;
F(i, 1, n) if (fst[a[i]] == i) ans += s[i];
```

---

## 作者：AK_400 (赞：1)

令 $fst_i,lst_i$ 分别表示第一个和最后一个 $i$ 的位置，则子段 $[l,r]$ 合法的充要条件为 $fst_{a_l}=l\wedge lst_{a_r}=r$。

声明：$[l,r]$ 表示子段 $a_l,a_{l+1},\cdots,a_r$，$s_1+s_2$ 表示将两个子段拼接。

- 必要性证明：假设 $fst_{a_l}\ne l$ 时存在合法子段，设其为 $[l,r]$，那么显然，$fst_{a_l}+[l+1,r]=[l,r]$，即 $[l,r]$ 不合法。$lst_{a_r}\ne r$ 时同理。

- 充分性证明：因为 $fst_{a_l}=l$，所以不存在 $i<l$ 使得 $a_i=a_l$。于是与 $[l,r]$ 相等的子序列的起点 $l'\ge l$，同理其终点 $r'\le r$。因为其元素个数和 $[l,r]$ 相等，于是 $r-l\le r'-l'$，所以 $l=l',r=r'$。

有了这个转化，我们可以把 $a$ 离散化，算出 $fst,lst$，然后处理出每个合法左端点对应的合法右端点个数即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[100005],b[100005],lst[100005],fst[100005];
void slv(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    sort(b+1,b+1+n);
    int mn=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+1+mn,a[i])-b;
    for(int i=1;i<=n;i++)lst[a[i]]=i;
    for(int i=n;i>=1;i--)fst[a[i]]=i;
    sort(lst+1,lst+1+mn);
    int now=1;
    int ans=0;
    for(int i=1;i<=n;i++){
        while(lst[now]<i)now++;//now 以前的都在i以前
        if(fst[a[i]]!=i)continue;//i不合法
        ans+=mn-now+1;
    }
    cout<<ans<<endl;
}
signed main(){
    int T;
    cin>>T;
    while(T--)
    slv();
    return 0;
}
```

---

## 作者：Gapple (赞：0)

注意到如下结论：区间 $[l, r]$ 满足题目条件当且仅当 $a_l$ 第一次出现，且 $a_r$ 最后一次出现。

> 证明：充分性显然，下面证明必要性。
>
> 若区间 $[l, r]$ 不满足上述条件，则我们可以找到在 $a_l$ 左边与其相同的数与 $[l + 1, r]$ 拼起来，或找到在 $a_r$ 右边与其相同的数与 $[l, r - 1]$ 拼起来。
>
> 故该区间不满足题目条件。

所以对于下标 $i$，我们维护 $f_i, l_i$ 分别记录 $a_i$ 是否是第一个与最后一个出现的。若 $a_i$ 是第一个出现的，则 $f_i = 1$；否则 $f_i = 0$。$l_i$ 同理。

设 $S_i = \sum \limits_{j = i}^n l_j$，则答案为

$$
\sum_{i = 1}^n f_i \cdot S_i
$$

```cpp
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using i64 = long long;

void solve_test()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    vector<bool> fst(n), lst(n);
    map<int, bool> vis;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];

        if (!vis[arr[i]])
            vis[arr[i]] = fst[i] = true;
    }

    decltype(vis)().swap(vis);

    for (int i = n - 1; i >= 0; --i) {
        if (!vis[arr[i]])
            vis[arr[i]] = lst[i] = true;
    }

    vector<int> suff(n, lst[n - 1]);

    for (int i = n - 2; i >= 0; --i)
        suff[i] = suff[i + 1] + (int)lst[i];

    i64 ans = 0;

    for (int i = 0; i < n; ++i)
        ans += (i64)fst[i] * suff[i];

    cout << ans << '\n';
}

int main()
{
    int t;
    cin >> t;

    while (t-- > 0)
        solve_test();

    return 0;
}
```

---

## 作者：LucasXu80 (赞：0)

本题解提供一份不使用 STL 的代码。

解题思路其他题解已经证明，这里再解释一下：

从前往后扫一遍数组，预处理出第一次出现的数字所在位置，再从后往前进行同样的操作。

再从前往后计算第一次出现数字个数的前缀和。

对于从后往前第一次出现的数字所在位数，将答案直接加上这一位置刚刚计算过的前缀和值即可。

该算法的正确性在于，一个子串满足条件的充要条件是：子串左侧没有与该子串左端一样的数字，并且子串右侧没有与该子串右端一样的数字。

用样例模拟一下该过程：

| $i$ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $a_i$ |$1$|$7$|$7$|$2$|$3$|$4$|$3$|$2$|$1$|$100$|
| $unvisitedpre_i$ | $1$ | $1$ | $0$ | $1$ | $1$ | $1$ | $0$ | $0$ | $0$ | $1$ |
| $pre_i$（前缀和） | $1$ | $2$ | $2$ | $3$ | $4$ | $5$ | $5$ | $5$ | $5$ | $6$ |
| $unvisitedback_i$ | $0$ | $0$ | $1$ | $0$ | $0$ | $1$ | $1$ | $1$ | $1$ | $1$ |
| 对 $ans$ 的贡献 | $0$ | $0$ | $2$ | $0$ | $0$ | $5$ | $5$ | $5$ |  $5$| $6$ |

故答案为 $2+5+5+5+5+6=28$。

注意到 $1 \leq a_i \leq 10^9$，不能用一个大小为 $10^9$ 的 $vis$ 数组记录每个数字是否出现过，因此需要离散化。

考虑将数组从小到大排序并去重，将数字从小到大依次编号为 $1,2,...$，这样最多有 $10^5$ 个编号，构建数字与编号之间的映射，从编号可以直接推回数字。

欲从数字推到其编号，可以二分记录编号对应数字的数组，复杂度 $O(\log(cnt))$，其中 $cnt$ 为不同的数字个数。

总复杂度 $O(n\log n)$。

代码及注释：

```cpp
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
int t,n,cnt,a[100001],b[100001],idx[100001],pre[100001];
bool vis[100001],unvisited_pre[100001],unvisited_back[100001];
int find(int x)
{
    int l=1,r=cnt,mid;
    while (l<=r)
    {
        mid=(l+r)/2;
        if (idx[mid]==x) return mid;
        if (idx[mid]<x) l=mid+1;
        if (idx[mid]>x) r=mid-1;
    }
}
int main()
{
    cin>>t;
    while (t--)
    {
        cnt=0;
        memset(vis,0,sizeof(vis));
        memset(unvisited_pre,0,sizeof(unvisited_pre));
        memset(unvisited_back,0,sizeof(unvisited_back));
        // 多测记得清空
        cin>>n;
        for (int i=1; i<=n; i++)
        {
            cin>>a[i];
            b[i]=a[i]; // 不能改变原 a[] 数组的顺序，故新开 b[] 数组进行排序
        }
        sort(b+1,b+n+1);
        for (int i=1; i<=n; i++)
        {
            if (b[i]!=b[i-1])
            {
                cnt++;
                idx[cnt]=b[i]; // 为数字 b[i] 赋予编号 idx
            }
        }
        for (int i=1; i<=n; i++)
        {
            if (!vis[find(a[i])])
            {
                vis[find(a[i])]=1;
                unvisited_pre[i]=1;
            }
        }
        memset(vis,0,sizeof(vis)); // 从后往前扫的时候重复利用 vis 数组，再次清零
        for (int i=n; i>=1; i--)
        {
            if (!vis[find(a[i])])
            {
                vis[find(a[i])]=1;
                unvisited_back[i]=1;
            }
        }
        for (int i=1; i<=n; i++) pre[i]=pre[i-1]+unvisited_pre[i];
        long long ans=0;
        for (int i=n; i>=1; i--)
        {
            if (unvisited_back[i]) ans+=pre[i];
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```


---

## 作者：FireRain (赞：0)

# 思路

发现如果一个区间 $[l,r]$ 满足对于所有的 $i \in [1,l)$ 都有 $a_i \neq a_l$，对于所有的 $i \in (r,n]$ 都有 $a_i \neq a_r$，那么区间 $[l,r]$ 一定合法。

那么定义 $stl_i = 0/1$ 表示对于所有的 $j \in [1,i)$ 不满足/满足 $a_j \neq a_i$；$str_i = 0/1$ 同理。

枚举一个 $i$ 当做区间的右端点。那么这个 $i$ 对于答案的贡献为：

$$
(\sum_{i = 1}^{i}{stl_i}) \times str_i
$$

这个可以直接用前缀和维护。

**注意：不要使用 `unordered_map`，会被卡。**

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 1e5 + 10;
int T,n;
int arr[N];
bool stl[N],str[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void solve(){
	int ans = 0,cnt = 0;
	map<int,bool> visl,visr;
	n = read();
	for (re int i = 1;i <= n;i++){
		stl[i] = str[i] = false;
		arr[i] = read();
	}
	for (re int i = 1;i <= n;i++){
		if (!visl.count(arr[i])) stl[i] = true;
		visl[arr[i]] = true;
	}
	for (re int i = n;i;i--){
		if (!visr.count(arr[i])) str[i] = true;
		visr[arr[i]] = true;
	}
	for (re int i = 1;i <= n;i++){
		cnt += stl[i];
		ans += str[i] * cnt;
	}
	printf("%lld\n",ans);
}

signed main(){
	T = read();
	while (T--) solve();
	return 0;
}
```

---

## 作者：Miracle_1024 (赞：0)

## 思路：
对于一段区间 $[l,r]$ 而言，合不合法，取决于 $[1,l−1]$ 不存在 $a_l$，并且 $[r+1,n]$ 不存在 $a_r$，也就是区间前面不能存在和左端点值一样的点，区间后面不能存在和右端点值一样的点。

然后统计合法区间数。假设，我们当前点 $i$ 为区间的左端点，那么从 $[i,n]$ 这个区间，求有多少个点是可以作为右端点的。

可以用后缀和实现。设 $r_i$ 表示从 $[r,n]$ 的可以作为右端点的个数，假如说当前节点 $i$，从后往前是第一次出现的，那么 $r_i = r_{i-1}+1$，否则 $r_i = r_{i-1}$。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll t,n,a[N],sum[N],ans;
int main(){
	cin>>t;
	while(t--){
		ans=0;
		map<ll,bool>mp1,mp2;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		sum[n+1]=0;
		for(int i=n;i;i--){
			sum[i]=sum[i+1]+(!mp2[a[i]]);
			mp2[a[i]]=1;
		}
		for(int i=1; i<=n; i++){
			if(!mp1[a[i]])ans+=sum[i];
			mp1[a[i]]=1;
		}
		cout<<ans<<endl;
	}
}


```

---

