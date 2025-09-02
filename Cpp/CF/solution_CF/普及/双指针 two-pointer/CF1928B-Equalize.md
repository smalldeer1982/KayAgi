# Equalize

## 题目描述

Vasya 有两个爱好——给数组加上排列和寻找出现次数最多的元素。最近，他发现了一个数组 $a$，并决定找出在给数组 $a$ 加上某个排列后，数组中相同数字出现次数的最大值。

更正式地说，Vasya 必须选择恰好一个长度为 $n$ 的排列 $p_1, p_2, p_3, \ldots, p_n$，然后按照规则 $a_i := a_i + p_i$ 修改数组 $a$ 的元素。之后，Vasya 统计数组 $a$ 中每个数字出现的次数，并取这些值的最大值。你需要求出他能获得的最大值。

$^{\dagger}$ 长度为 $n$ 的排列是由 $n$ 个 $1$ 到 $n$ 的不同整数组成的数组，顺序任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中有 $4$）。

## 说明/提示

在第一个测试用例中，最优选择是 $p = [2, 1]$。操作后，数组 $a$ 变为 $[3, 3]$，此时数字 $3$ 出现了两次，所以答案是 $2$。

在第二个测试用例中，其中一种最优方案是 $p = [2, 3, 1, 4]$。操作后，数组 $a$ 变为 $[9, 4, 5, 5]$。由于数字 $5$ 出现了两次，所以答案是 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
2
1 2
4
7 1 4 1
3
103 102 104
5
1 101 1 100 1
5
1 10 100 1000 1
2
3 1
3
1000000000 999999997 999999999```

### 输出

```
2
2
3
2
1
1
2```

# 题解

## 作者：Kdlyh (赞：12)

# 分析

通过读题，可以得出两个结论：

- $a$​ 数组中一组相同的数中只有一个能对答案造成贡献。
  - 因为排列中每个数不同，相同的数加不同的数不可能得出相同的数。

- 一段去重后的数列要贡献答案长度，当且仅当该数列的**最大值与最小值之差**小于等于 $n - 1$。
  - 因为一段数列内只要没有重复数字，同时**最大值与最小值之差**小于等于 $n - 1$，肯定能通过加上 $1\sim n$​ 的排列而相等。

# 实现

- 针对第一个性质，对数组排序后去重：

  ```cpp
  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());
  ```

- 针对第二个性质：

  - 排序数组（去重时已做到）。

  - 在最多 $ O(n\log n)$ 的时间复杂度下维护一段**最大值与最小值之差**小于等于 $n - 1$​ 的序列。

    - 双指针维护

      ```cpp
      for (int i = 0, j = 0; i < a.size(); i++) {
      	while(j < a.size() && a[i] + n - 1 >= a[j]) j++;//如果满足性质二，后方指针后移
      	ans = std::max<int>(ans, j - i);
      }
      ```

    - 二分查找

      ```cpp
      for (int i = 0; i < a.size(); i++) {
      	i64 sum = std::upper_bound(a.begin(), a.end(), a[i] + n - 1) - a.begin() - i;//直接找以当前这个元素为最小值的符合性质二的最大的最大值的位置，再与当前位置做差求出序列长度
      	ans = std::max(ans, sum);
      }
      ```

# 代码

- 双指针实现

  ```cpp
  void solve() {
      int n;
      std::cin >> n;
      std::vector<i64> a(n);
      for (auto& i : a) std::cin >> i;
      std::sort(a.begin(), a.end());
      a.erase(std::unique(a.begin(), a.end()), a.end());
      i64 ans = 0;
      for (int i = 0, j = 0; i < a.size(); i++) {
  		while(j < a.size() && a[i] + n - 1 >= a[j]) j++;
  		ans = std::max<int>(ans, j - i);
  	}
      std::cout << ans << '\n';
  }
  ```

- 二分查找实现

  ```cpp
  void solve() {
      int n;
      std::cin >> n;
      std::vector<i64> a(n);
      for (auto& i : a) std::cin >> i;
      std::sort(a.begin(), a.end());
      a.erase(std::unique(a.begin(), a.end()), a.end());
      i64 ans = 0;
      for (int i = 0; i < a.size(); i++) {
          i64 sum = std::upper_bound(a.begin(), a.end(), a[i] + n - 1) - a.begin() - i;
          ans = std::max(ans, sum);
      }
      std::cout << ans << '\n';
  }
  ```

  



---

## 作者：2huk (赞：5)

> 给定一个长度为  $n$ 的序列 $a$。请你构造一个 $1 \sim n$ 的排列 $p$，并使得新序列 $b = \{a_i + p_i\}$ 中相同的元素数量最多。输出最多的相同元素数量。
>
> 多测。$t \le 2 \times 10^4$，$\sum n \le 2 \times 10^5$，$1 \le a_i \le 10^9$。

首先题目可以理解成，从 $a$ 中选择一些数，使得将这些数加上 $1 \sim n$ 中一些**不重复**的数字之后，所有元素相同。求最多选数数量。

思考一下选出的数有什么性质：

- 不会选择**重复**的数字。如果有重复的数字，由于排列中的数字是不重复的，所以相加后这些原本相同的数字一定会变得不同。所以可以直接将 $a$ 去重。
- 选择的数字在**排序**后的数组是连续的。可以感性理解一下，如果 $a_1 < a_2 < a_3 < a_4$，那么如果我们可以选择 $a_1, a_3, a_4$，就意味着也存在一种方法选择 $a_2, a_3, a_4$。反过来却不一定。

所以这启发我们可以先将 $a$ 升序排序并去重，然后从中选择一个区间 $[l, r]$，并将 $[l, r]$ 内的数字全部选上，那么答案即为所有合法区间的最大长度。问题在于如何判断 $[l, r]$ 是否合法。

由于此时 $a_r$ 是严格最大值，所以为了让剩下的数能与 $a_r$ 相等，我们肯定是希望让 $a_r$ 加上 $1 \sim n$ 中最小的数，也就是 $1$。然后判断一下剩下的 $a_i(l \le i < r)$ 能否通过加某个 $2 \sim n$ 的数使得它能与 $a_r$ 相等，也就是判断 $a_r + 1 - a_i$ 是否在 $2 \sim n$ 之内。

如何判断呢？不难发现只要 $a_l$ 满足这个条件，剩下的所有元素就都能满足了。因为 $a_l$ 是最小的。所以我们需要判断是否 $a_r + 1 - a_l \le n$。

```cpp
int solve() {
	int n = read();
	vector<int> a(n);
	
	for (int &t : a) t = read();
	
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	
	int m = a.size(), res = 0;
	for (int l = 0; l < m; ++ l )
		for (int r = l; r < m; ++ r )
			if (a[r] + 1 - a[l] <= n)
				res = max(res, r - l + 1);
	return res;
}
```

这样是 $\mathcal O(n^2)$ 的。

不难发现在选择满足 $a_r + 1 - a_l \le n$ 的区间 $[l, r]$ 时，随着 $r$ 的增加，$l$ 一定不减。所以双指针即可。

```cpp
int solve() {
	int n = read();
	vector<int> a(n);
	
	for (int &t : a) t = read();
	
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	
	int m = a.size(), res = 0;
	for (int r = 0, l = 0; r < m; ++ r ) {
		while (l <= r && a[r] + 1 - a[l] > n) {
			++ l;
		}
		if (l <= r && a[r] + 1 - a[l] <= n) res = max(res, r - l + 1);
		
	}
	
	return res;
}
```

---

## 作者：无名之雾 (赞：3)

# Equalize 题解

~~就这题我因为 `sort(a+1,a+n+1)` 打成了 `sort(a+n,a+n+1)` 挂了 $5$ 发。~~

## 题意

每次操作，给定你一个长度为 $n$ 的序列 $a$。你需要找到一个由 $1$ 到 $n$ 组成的无须数列 $p$ 每次通过操作 $a_i+p_i$ 使得 $a_i$ 中相同的数字最多。

## The first method

### 思路

这题的本质说白了就是找出给定数组经过添加一个排列后，最大重复元素的个数。再看一眼数据范围 $1\le t \le 2\times10^4$，$1\le n \le 2\times10^5$。想到运用双指针进行操作，最劣时间复杂度 $O(\sum n\log n\times t)$。~~相信 CF 的机子一定可以跑过去的（大不了指令集）。~~

### 实现

考虑维护两个指针 $l$ 和 $r$，初始时均指向新数组的第一个位置。
遍历新数组的每个元素 $a_r$。如果 $a_l+n-1<a_r$，说明 $l$ 到 $r$ 之间的区间无法通过添加排列使得元素相等，将 $l$ 右移一位。
更新答案，表示当前长度的区间内的最大重复元素个数。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
signed main(){
    int t=read();
    while(t--){
        int n=read(),ans=0;
        for(int i=1;i<=n;i++)a[i]=read();
        sort(a+1,a+n+1);
        int q=unique(a+1,a+n+1)-a-1;
        //排序数组并去除重复元素
        for(int l=1,r=1;r<=q;r++){
            while(a[l]+n-1<a[r])l++;
            // 找到l指针移动的位置
            ans=max(ans,r-l+1);
            // 更新答案
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

## The second method

### 思路

本题同样可以通过二分的方法来找到最大重复元素的个数，时间复杂度同样为 $O(n \log n\times t)$。可以接受。

### 实现

使用两个指针 $i$ 和 $j$ 遍历 $v$ 向量，其中 $i$ 是当前区间的起始位置，$j$ 是不小于 $v_i+n-1$ 的位置。通过二分查找，可以找到 $v_i+n-1$ 在 $v$ 向量中的位置，然后计算 $j$ 的值。每次更新 $j-i+1$ 的最大值，并将结果保存在变量 $ans$ 中。


### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int arr[200005];
int main(){
    int t;
    cin>>t;
    while(t--){
    int N;
    cin>>N;  
    for(int i=0;i<N;i++)cin>>arr[i];
     sort(arr,arr+N);
     vector<int>v;
     int size=0;
     for(int i=0;i<N;i++){
         if(size==0||v[size-1]!=arr[i]) {
             v.push_back(arr[i]);
             size++;
         }
     }
     int ans=0;
     for(int i=0;i<size;i++){
         int ind=upper_bound(v.begin(),v.end(),v[i]+N-1)-v.begin();
         ans=max(ans,ind-i);
     }
     cout<<ans<<endl;
   }
}
```

---

## 作者：susenyang (赞：3)

题意大概是：给定一个长为 $n$ 的数组，和一个 $1 \sim n$ 的排列对应相加，最大化相等的数的数量。

首先可以对数组排序（因为我们并不关心数组和排列每个数的顺序）。又因为排列中每个数都是不同的，所以原数组中相同的数不能对答案产生更多的贡献，考虑对原数组去重。

对于去重后的数组，可以发现，要最大化相等的数的数量，一定是选择连续的一段进行操作。这一段可以转化为相同的数的条件就是，最大的减去最小的小于等于 $n-1$。

所以问题转化为，在一个递增且不重的序列中，找最长的子序列，使得最大减最小小于等于 $n-1$。我赛时的做法是二分答案：二分子序列的长度，检查是否存在合法的子序列。

[赛时代码：](https://codeforces.com/contest/1928/submission/245809916)

```cpp
#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 10;

int a[N];
std::vector<int> b;
std::map<int, int> vis;

void solve()
{
    int n;
    std::cin >> n;
    b.clear(), vis.clear();
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
    }
    std::sort(a + 1, a + n + 1);
    b.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        if (!vis[a[i]])
        {
            b.push_back(a[i]);
            vis[a[i]] = 1;
        }
    }
    int m = b.size() - 1;
    int l = 0, r = 1e9;
    int ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        bool isok = 0;
        for (int i = 1; i + mid - 1 <= m; i++)
        {
            if (b[i + mid - 1] - b[i] <= n - 1)
            {
                isok = 1;
            }
        }
        if (isok)
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    std::cout << ans << std::endl;
}

signed main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int _;
    std::cin >> _;
    while (_--)
        solve();
    return 0;
}
```


---

## 作者：信息向阳花木 (赞：3)

求一个长度为 $n$ 的数列给它加上一个任意长度的排列，最多有多少元素相同。

首先，加上排列的长度不能超过 $n$。如果几个数加完排列后一样，那么它们两两之间的差的绝对值不能超过 $n$。接下来就很好做了。由于排列中每个数只出现一次，所以我们将原序列排序，去重。如果要以 $a_i$ 为首加上一个排列（$a_i$ 加 $1$），那么相同元素个数就是 $[a_i, a_i+ n - 1]$ 区间内数的个数。因为只要在这个区间范围内的数，两两差的绝对值都小于等于 $n$，都可以加到相同的值。这个直接用二分求一下可以了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

int t, n, m;
int a[N];

int main()
{
    scanf("%d", &t);
    while (t -- )
    {
        scanf("%d", &n); m = n;
        int res = 0;
        for (int i = 1; i <= n; i ++ )
            scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        n = unique(a + 1, a + n + 1) - a - 1;
        for (int i = 1; i <= n; i ++ )
        {
            if(a[n] <= a[i] + m - 1)
                res = max(res, n - i + 1);
            else
            {
                int p = upper_bound(a + 1, a + n + 1, a[i] + m - 1) - a;
                res = max(res, p - i);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
```

---

## 作者：SXqwq (赞：2)

首先，容易得出**一组重复的数最多对答案造成一个贡献**。因此重复的数据我们只需要保留一个即可。

其次，对于去重后的数组 $a$。如果一个区间是合法的，当且仅当区间最大值减最小值小于 $n$ 时。

解释：

设区间最大值为 $x$，最小值为 $y$。将最大值更改为 $x+1$，则 $y$ 最多加 $n$ 就合法。我们保证 $a$ 中每个数各不相同。所以区间内的每个数都可以使用 $1-n$ 的排列解决问题。

反证，当 $x-y = n$ 时，同样将 $x+1$。此时 $y$ 最多需要加 $n+1$。不能用 $1-n$ 的排列解决问题。至于 $x-y > n$ 时同理。

至于找区间内的最大最小值，将数组 $a$ 去重排序即可。$a_l,a_r$ 即为最大最小值。

双指针维护即可。

### Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e9;
const int MAXN = 1000010;
int T;
int n,cnt;    
int a[MAXN];
int b[MAXN];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int cnt = 0;
    for(int i=1;i<=n;i++)
    {
        if(a[i] == a[i-1]) continue;
        b[++cnt] = a[i];
    }
    int l = 1,r = 1,ansl,ansr,maxn = 1;
    while(r <= cnt)
    {
        while(b[r] - b[l] >= n && l <= r) l ++;
        if(r - l+1 > maxn)
        {
            maxn = r-l+1;
        }
        r ++;
    }
    cout<<maxn<<endl;
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--)
    {
        solve();
    }
}
```

---

## 作者：No_Rest (赞：2)

## 思路

不难发现，如果想要某些数在改变之后相等，那么他们之中的最大数减去最小数应该 $< n$。

所以这道题就很简单了，将原数组排序之后就可以按自己的方法做了。注意如果数原来就相等，改变之后不可能相等，所以还需要对原数组去重。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 2e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll t = read(), n, a[maxn], b[maxn], lst, tot, p, ans;
void solve(){
	n = read(), lst = tot = 0, p = ans = 1;
	for(ll i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);//排序
	for(ll i = 1; i <= n; ++i)
		if(lst != a[i]) lst = a[i], b[++tot] = a[i];//去重
	for(ll i = 2; i <= tot; ++i){
		while(b[i] - b[p] >= n) p++;
		ans = max(ans, i - p + 1);//更新答案
	}
	printf("%lld\n", ans);
}
int main(){	
	for(; t; --t) solve(); 
    return 0;
}
```

---

## 作者：huangruiheng0217 (赞：2)

水题，但是调了好久。

### 题目描述

给定一个数组 $a$。

求一个 $1-n$ 的排列 $p$，使数组 $a$ 与 $p$ 叠加后得到的新数组中，众数出现的次数最大。

输出这个最大值。

### 思路

注意到重复的数在与 $p$ 数组叠加之后，数值一定不同（因为 $p$ 是一个排列，其中的元素互不相同）。因此我们需要先对 $a$ 数组去重。

去重后，任意一个子集均可以通过构造 $p$ 数组使得叠加后值全部相等，当且仅当极差小于 $n$。

证明：若极差大于或等于 $n$，最大值和最小值永远无法相等。

若极差小于 $n$，将所有数和子集中最小的数作差，得到若干个互不相同且大小在 $[0,k)$ 之间的整数 $b_1,b_2,...,b_k$。其中 $k$ 是该子集的元素个数。

对于这一部分数据，构造的 $p$ 数组为 $n-b_1,n-b_2,...,n-b_k$，显然是 $1-n$ 的一个排列的一部分。

证毕。

注意排序并去重后的数组具有如下性质：连续区间一定比非连续区间更优。

证明：设当前最优方案为 $[l_1,r_1] \cup [l_2,r_2] \cup ... \cup [l_k,r_k]$，显然区间 $[l_k,r_k]$ 更优。证毕。

所以考虑将数组排序，检查其中的连续区间是否符合要求即可（双指针）。

### 代码

太丑了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int b[200005];
void solve(){
    int n,ans=1;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    int cur=1;
    b[cur]=a[1];
    for(int i=2;i<=n;i++){
        if(a[i]!=b[cur])
            b[++cur]=a[i];
    }
    for(int i=1;i<=cur;i++){
        int j=i+ans;
        if(j>cur)break;
        while(b[j]-b[i]<n){
            if(j>cur)break;
            ans=max(ans,j-i+1);
            j++;
        }
    }
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}
```

---

## 作者：UniGravity (赞：1)

## Solution CF1928B Equalize
洛谷[传送门](https://www.luogu.com.cn/problem/CF1928B)

~~事实上这题一开始没想出来，做完了 C 才回来做。~~

### 题意
有一个给定的长度为 $n$ 的数列 $a$，现在加上一个排列 $b$，即 $c_i=a_i+b_i$。

现在求对于所有可能的 $b$，$c$ 中**出现最多的数的出现次数**的最大值。

### 做法
首先发现一个显然的规律，即对于 $c$ 中出现最多的数（若 $c_i$ 是这个数，则称 $i$ 为**选中下标**），这个数的组成一定如下图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/xs197vdf.png)

那么想到对 $a$ 做排序，然后可以发现，选中下标在排序后的 $a$ 中一定是连续的。

就有一个 $O(n^2)$ 的做法，即枚举开头 $l$ 结尾 $r$，然后判断 $a_r-a_l$ 是否小于排列长度 $n$，因为中间的数值在头尾中间，排列都可以覆盖。

然后发现可以双指针，因为当 $l$ 增大时 $r$ 一定不减。

同时要对 $a$ 去重，因为 $b$ 中的数各不相等。

那么就做完了，时间复杂度 $O(n\log n)$，因为要做排序。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;
int a[200005], b[200005];
int ans;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + n + 1);
		int m = 1;
		b[1] = a[1];
		for (int i = 2; i <= n; i++) {
			if (a[i] != a[i - 1]) b[++m] = a[i];
		}
		ans = 0;
		for (int s = 1, t = 1; s <= m; s++) {
			while (t < m && b[t + 1] - b[s] < n) t++;
//			printf("[%d %d]\n", s, t);
			ans = max(ans, t - s + 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：_Delete_ (赞：1)

## 思路

为了使相等的元素尽可能多，我们则会使一个原序列中的较小数加上一个较大数，使原序列中的较大数加上一个较小数，使其两数相等。

事实上，只有一组数中没有相等的数，且最大数和最小数之差小于序列长度，这组数才能相等。因此，我们将原序列排序，双指针查找一个区间，区间内最大数小于最小数加区间长度，寻找最长区间即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 
ll a[200005];
ll inf=2147483647;

//function 
void solve(){
	ll q;
	cin>>q;
	for(ll i=1;i<=q+3;i++)a[i]=inf;
	for(ll i=1;i<=q;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+q);
	ll ans=1;
	ll i=1,j=1,cf=0;
   //cf用于去重
	while(i<=q&&j<=q){
		while(a[i]+q>a[j]){
			j++;
			if(a[j]==a[j-1])cf++;
		}
		ans=max(ans,j-i-cf);
//		cout<<i<<' '<<j<<endl;
		if(a[i]==a[i+1])cf--;
		i++;
	}
	cout<<ans<<endl;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	
	return 0;
}


```


---

## 作者：快斗游鹿 (赞：1)

注意到两个相等的数一定不可能被改成一样的，因为一个排列中的数互不相同，所以可以先对整个数列进行去重。

然后有一个结论：只要一个数列中数的极差小于 $n$，其中的数就一定可以被改成相同的。为什么？可以将最大的数改为 $x+1$，那么最小的数最多也只需要增加 $n$ 就可以满足条件，而又保证了数列中的数互不相同，故一定可以用一个 $1$ 到 $n$ 的排列使其满足条件。

排序后用双指针扫一遍即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T,n,a[N],ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	//freopen("std.in","r",stdin);
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+1+n);
		int m=unique(a+1,a+1+n)-a-1;
		int l=1,r=1;
		ans=0;
		while(l<=m){
			while(r<=m&&a[r]-a[l]<n)r++;
			ans=max(ans,r-l);
			l++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
 
```


---

## 作者：Cure_Wing (赞：1)

[CF1928B Equalize](https://www.luogu.com.cn/problem/CF1928B)

### 思路

我们看到，对于序列中的每一个数，它加上数组成的的是一个长度为 $n$ 的排列，所以对于一个数 $x$，如果我们想让它与 $x+k$ 相等，那么只需要让 $x$ 加 $k+1$，再让 $x+k$ 加 $1$ 即可。进而我们可以想到，对于一个数 $x$，我们可以让 $x+1\sim x+n-1$ 与它相等，因为我们只需要让 $x$ 加 $n$，然后依次加上 $n-1,n-2,\cdots,1$ 即可。而相同的数是不会二次相等的，所以我们一开始可以去重。看到我们询问的数满足单调的区间，所以一开始我们可以对原序列排序。这样我们从小到大枚举 $x$。如果二分查找 $x+n-1$，时间复杂度 $O(\sum(n\log n))$。而很容易想到，二分查找的右端点随 $x$ 单调不降，于是我们多维护一个指针 $p$，表示搜索到的答案，让它随着 $x$ 的更新而移动即可。时间复杂度优化到 $O(\sum n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=200005;
int t,n,a[N],ans;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<ans<<'\n'){
		cin>>n;ans=0;
		for(int i=1;i<=n;++i) cin>>a[i];
		std::sort(a+1,a+n+1);
		int m=std::unique(a+1,a+n+1)-a-1;
		int j=1;//这里的 j 就是指针 p
		for(int i=1;i<=m;++i){
			j=std::max(i,j);
			for(;j<m&&a[j+1]-a[i]<n;++j);
			ans=std::max(ans,j-i+1);
		}
	}
	return 0;
}
```

---

## 作者：apiad (赞：0)

由于排列是不可以重复的，所以显然重复的数想要加到一个定值（若是出现最多，肯定尽量一样，也就是定值）只有一个数可以加到。于是，不妨排序去重一下。

很贪心的策略，因为你要让一些数加到一个定值，然后尽可能出现多，显然，这在排序去重之后，代表，你得选一个尽可能长的子段，最后一个数减最前面的数 $\le n-1$。

这样，我们可以枚举子段的开头，然后二分即可，时间复杂度 $O(n\log n)$。

[code](https://codeforces.com/contest/1928/submission/245845763)。

---

## 作者：int_R (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1928B)

排列中的每个数不相等，所以序列中相等的数操作完后一定不相等。

所以先排序，去重，只要两个数相差小于 $n$ 就可以给它们分配一个数使它们最后相等。

问题转化成取出一段最长的区间使得极差小于 $n$，双指针即可。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10;
int T,n,k,a[MAXN],ans;
inline void work()
{
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+1+n);k=unique(a+1,a+1+n)-a-1;
    for(int l=1,r=1;l<=k;++l)
    {
        while(r<=k&&a[l]+n>a[r]) ++r;
        ans=max(ans,r-l);
    }
    cout<<ans<<'\n';ans=0;
}
int main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>T;while(T--) work();
    return 0;
}
```

---

## 作者：__Octhyccc__ (赞：0)

不错的一道思维题，建议评黄。

注：下文的 $a_i$ 和 $a_j$ 均在 $i≠j$ 时。

题意简述：给定长度为 $n$ 的一个排列 $p$（顺序任意），再给定 $n$ 个数，令其为数组 $a$，让每个 $a_i=a_i+p_i$，求在操作后最多有多少个数相等，多组数据。

首先，由于 $p$ 是一个 $1\sim n$ 的排列，所以对于操作前任意情况的 $a_i=a_j$，它们操作后一定不能相等。

这就告诉了我们第 $1$ 步：对数组 $a$ 去重（这个可以用 map 实现）。

再考虑一下如果操作后 $a_i=a_j$，那么操作前 $|a_i-a_j|$ 的最大值一定不超过 $n-1$。因为数组 $a$ 中的每个数都要加上排列 $p$ 中的一个数，又因为 $1\le p_i\le n$。

令操作前 $a_i=a_i+n$，$a_j=a_j+1$，然后 $a_i=a_j$。得方程：

$$a_i+n=a_j+1$$

$$n-1=a_j-a_i$$

由于我们取了极差，所以结论成立。将 $a_i,a_j$ 颠倒过来同理。方程中的 $a_i,a_j$ 均视为**操作前**。

那么有了这个结论，我们的第 $2$ 步确定：对数组 $a$ 从小到大排序。

然后就找一个区间，令 $l,r$ 为左右端点（区间含 $l,r$），满足以下要求：

在满足 $a_r-a_l\le n-1$ 的情况下使该区间涵盖的元素数最大。

当然，我们都想到了可以 $O(n^2)$ 解决该部分（就是暴力枚举），这里提供一种单组数据时间复杂度最坏为 $O(2n)$ 的方法：

初始时 $l=0,r=1$。若 $a_r-a_l>n-1$，告诉我们 $l$ 小了，令 $l=l+1$，若 $a_r-a_l\le n-1$，这就证明可以，我们可以开一个 $v$ 数组，储存 $r-l+1$（也就是元素个数）的值，让 $r=r+1$，继续寻找，直到 $r\ge n-1$ 为止。

现在，$v$ 数组中的最大值就是答案。

加上排序的话我的代码单组数据是 $O(n\log n)$ 的，不过排序可以使用桶排序（就是开一个 map），降低到 $O(2n)$，不过我不愿意改了。

代码（赛时）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a;
vector<int>v,s;
map<int,bool>m;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",&a);
			if(!m[a]){
				v.push_back(a);
				m[a]=1;
			}
		}
		sort(v.begin(),v.end());
		int l=0,r=0;
		while(r<=v.size()-1){
			if(v[r]-v[l]<=n-1){
				r++;
				s.push_back(r-l);
			}
			else{
				s.push_back(r-l);
				l++;
			}
		}
		sort(s.begin(),s.end());
		printf("%d\n",s[s.size()-1]);
		m.clear();v.clear();s.clear();
	}
	return 0;
}

```

---

## 作者：wangyishan (赞：0)

# CF1928B Equalize 题解

## 题意

给定一个长度为 $n$ 数列 $a$，你要在这个序列上加上一个长度为 $n$ 的排列，求最终 $a$ 数组内出现最多的数的次数。

$n\leq 2\times 10^5$。



## 题解

首先我们发现原数组 $a$ 中相同元素只能被计算一次。证明：数组内每个数都要加上一个排列中的一个数，而排列中的数互不相同。

现在我们只需要考虑原来的 $a$ 数组元素互不相同时该怎么做。

对于原数组 $a$ 内的一段区间 $[l,r]$，易得只要 $a_r-a_l\leq n-1 $ 时，这段区间一定可以变成一个相同的数。证明很显然。

这就转化成了一个经典的滑动窗口、双指针问题了。首先对数组排序并去重，然后维护两个指针 $l,r$，只要 $a_r-a_l\leq n-1 $ 就 $r:=r+1$，否则更新答案，并且 $l:=l+1$。

时间复杂度为排序的 $\mathcal O(n\log n)$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define ll long long 
#define YESS {cout<<"YES"<<endl;return;}
#define NOOO {cout<<"NO"<<endl;return;}

int n;
int a[200050];
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    int m=unique(a+1,a+n+1)-a-1;
   // cout<<"m="<<m<<endl;
    int l=1,r=1;
    int ans=1;
    for(int l=1;l<=m;l++){
        while(r<=m&&a[r]-a[l]<n)r++;
        ans=max(ans,r-l);
      //  cout<<l<<" "<<r<<" "<<endl;
    }
    cout<<ans<<endl;
}

signed main(){
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}
```





---

## 作者：Mortidesperatslav (赞：0)

因为加上一个排列，所以对于一个数 $a_i$，所有在 $[a_i+1,a_i+n-1]$ 范围内的数都可以和 $a_i$ 相等。因为 $a_i+n-1+1=a_i+n,a_i+1+(n-1)=a_i+n$，其余数同理。

那么我们排完序后，对于每个 $a_i$，二分查找最后一个小于等于 $a_i+n-1$ 的数，然后取 $\max$ 就能求出答案了。

但是有一个坑点，因为可能出现 $a_i$ 相等的情况，我们先去重，但是注意 $a_i+n-1$ 的 $n$ 是去重前元素的个数。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[200005],n;
int fnd(int k){//二分查找
	int l=1,r=n,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
	//	cerr<<mid<<"\n";
		if(a[mid]<=k)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n);
		int tpn=n;//去重前的 n
		n=unique(a+1,a+1+n)-a-1;
		for(int i=1;i<=n;i++){
	//		cerr<<a[i]<<" ";
			ans=max(ans,fnd(a[i]+tpn-1)-i+1);//求答案最大值
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：eb0ycn (赞：0)

传送门：[CF1928B](https://www.luogu.com.cn/problem/CF1928B)。

## 题意

给你一个数组 $a$，$a$ 的长度为 $n$，你要给 $a$ 中的每个元素加上 $1 \sim n$ 中的一个值，且这些值不能重复。问最后 $a$ 数组最多有多少个元素相等。

## 思路

既然加的值不能重复，那我们肯定贪心地让原来较小的元素加上较大的值。由于数组元素的顺序对答案没有影响，所以我们先排序。因为加的值不能相同，所以原来相同的元素最后一定会变成不同。即原来相同的值中，最多只有一个会对结果产生贡献。所以我们对数组进行去重。

去重以后，数组就变成了单调上升的。考虑对于其中的一个区间 $[l,r]$，要满足什么条件才能让操作后里面的元素都相等？显然 $a_r-a_l \leq n-1$。而两端在操作后可以相等，那中间一定也可以。所以问题就转化成了：给你一个上升的数组，求最长的区间 $[l,r]$，使 $a_r-a_l \leq n-1$。用尺取法就行了。

时间复杂度：排序 $O(n \log n)$，尺取 $O(n)$。

## 极其简短的代码

```cpp
//场上代码
#include <bits/stdc++.h>
using namespace std;
int t,n,a[200001],cnt,l,r,ans;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n),l=r=ans=1;
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		sort(a+1,a+n+1),cnt=unique(a+1,a+n+1)-a-1;
		for(;r<=cnt;++r){
			while(a[r]-a[l]>=n&&l<r)++l;
			ans=max(ans,r-l+1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

