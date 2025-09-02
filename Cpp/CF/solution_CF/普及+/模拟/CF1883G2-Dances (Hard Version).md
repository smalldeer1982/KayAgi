# Dances (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ m \leq 10^9 $ .

You are given two arrays of integers $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ . Before applying any operations, you can reorder the elements of each array as you wish. Then, in one operation, you will perform both of the following actions, if the arrays are not empty:

- Choose any element from array $ a $ and remove it (all remaining elements are shifted to a new array $ a $ ),
- Choose any element from array $ b $ and remove it (all remaining elements are shifted to a new array $ b $ ).

Let $ k $ be the final size of both arrays. You need to find the minimum number of operations required to satisfy $ a_i < b_i $ for all $ 1 \leq i \leq k $ .

This problem was too easy, so the problem author decided to make it more challenging. You are also given a positive integer $ m $ . Now, you need to find the sum of answers to the problem for $ m $ pairs of arrays $ (c[i], b) $ , where $ 1 \leq i \leq m $ . Array $ c[i] $ is obtained from $ a $ as follows:

- $ c[i]_1 = i $ ,
- $ c[i]_j = a_j $ , for $ 2 \leq j \leq n $ .

## 说明/提示

In the first test case:

- For the pair of arrays $ ([1, 1], [3, 2]) $ , the answer is $ 0 $ . No operations or reordering of elements are needed.
- For the pair of arrays $ ([2, 1], [3, 2]) $ , the answer is $ 0 $ . The elements of the first array can be rearranged to obtain $ [1, 2) $ . No operations are needed.
- For the pair of arrays $ ([3, 1], [3, 2]) $ , the answer is $ 1 $ . The element $ 3 $ can be removed from the first array and the element $ 2 $ can be removed from the second array.
- For the pair of arrays $ ([4, 1], [3, 2]) $ , the answer is $ 1 $ . The element $ 4 $ can be removed from the first array and the element $ 3 $ can be removed from the second array.

## 样例 #1

### 输入

```
4
2 4
1
3 2
4 7
5 1 5
3 8 3 3
8 4
4 3 3 2 2 1 1
1 1 1 1 3 3 3 3
9 1
9 2 8 3 7 4 6 5
1 2 3 2 1 4 5 6 5```

### 输出

```
2
12
16
4```

# 题解

## 作者：FFTotoro (赞：10)

## 前言

该题解中 D2 做法基于 D1 的做法。

## 解法

### Easy Version

先考虑如果数组最终大小 $k$ 确定怎么判断答案是否合法：有一个显然的贪心，把 $a$ 数组中最大的 $n-k$ 个移除，把 $b$ 中最小的 $n-k$ 个移除，排序后进行比较所有 $a_i$ 与 $b_i$ 的大小关系即可。

再观察到 $k$ 具有单调性，直接二分即可。

### Hard Version

一开始想到一个巨大麻烦的分段讨论 $a_1$ 值的做法，但是因为巨难调放弃了。

再考虑每次只修改第一个数有什么性质：直觉告诉我们对答案的影响不大，猜测其不超过 $1$。事实上这是正确的，感性理解一下，即修改一个数后，不管修改为多少，$a$ 数组中一些元素排名变动不超过 $1$，这时如果 $a$ 数组因为这个事没法像原来一样与 $b$ 形成合法的序列，那么 $a$ 与 $b$ 各再删一个即可。

设 $a_1=1$ 的时候答案为 $x$，则在 $a_1$ 大于某个临界点 $y$ 时答案为 $x+1$。显然这个 $y$ 也可以二分，于是二分套二分判断中点 $a_1=m$ 时的答案是否等于 $l$ 即可，内部套的那个二分就是 D1 做法。答案为 $xy+(x+1)(m-y)$。时间复杂度 $O(n\log n\log m)$。

放代码（Hard Version）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,m; cin>>n>>m;
    vector<int> a(n),b(n),c(n);
    a[0]=1; for(int i=1;i<n;i++)cin>>a[i];
    for(auto &i:b)cin>>i;
    c=a,sort(a.begin(),a.end()); // 记得备份
    sort(b.begin(),b.end());
    auto pd=[&](int x){
      vector<int> p,q;
      for(int i=0;i<x;i++)
        p.emplace_back(a[i]);
      for(int i=n-x;i<n;i++)
        q.emplace_back(b[i]);
      for(int i=0;i<x;i++)
        if(p[i]>=q[i])return false;
      return true;
    }; // 内部二分
    auto f=[&](int x){
      a=c,a[0]=x;
      sort(a.begin(),a.end());
      int l=0,r=n;
      while(l<r){
        int m=l+r+1>>1;
        if(pd(m))l=m;
        else r=m-1;
      }
      return l;
    }; // 求当 a[1]=x 时的最大数组大小
       // 真正答案要用 n 减去它
    int l=f(1),l2=1,r2=m;
    while(l2<r2){
      int m2=l2+r2+1>>1;
      if(f(m2)==l)l2=m2;
      else r2=m2-1;
    } // 内部二分
    cout<<l2*(n-l)+(m-l2)*(n-l+1)<<'\n'; // 计算答案
  }
  return 0;
}
```

---

## 作者：Aleph_Drawer (赞：5)

分享 $O(n \log n)$ 的算法，瓶颈是排序，主体部分时间复杂度 $O(n)$。

而且又快又好写，不到 `800 bytes`。

首先考虑 $m = 1$ 怎么做，此时 $a,b$ 是确定的，不妨先排个序。

我们此时如果进行操作，显然是删去 $b$ 中最小的，$a$ 中最大的。

不妨一个个考虑 $a_i$ 会对应哪一个 $b_j$，如果 $a_i$ 找不到可以匹配的，需要删除，就假设匹配到 $n + 1$。这种显然可以使用双指针解决，答案即为 $\max(i - j)$。

现在考虑怎么做 $m > 1$ 的情况。

首先，发现 $a$ 的变化只会有一个数，不妨先将 $a_1$ 设为无穷大，然后按照上面的流程跑出答案 $cnt$。

此时，我们的匹配大概是长这样的：
$$
\begin{matrix}
	a_1 & a_2 & a_3 & \cdots & a_{n - 1} & a_{n} \\
	b_1 & b_3 & b_4 & \cdots & b_{n + 1} & b_{n + 1}
\end{matrix}
$$
实际情况大概就是这样，我们发现，形如 $b_2$ 之类的并没有被用上，不妨设它们组成的集合为 $S$。

此时答案就是（不妨考虑 $\max \{x | x \in S\} \geq m$，小于的情况取个 $\min$ 即可）$(cnt - 1)(\max \{x | x \in S\} - 1) + cnt(m - \max \{x | x \in S\} + 1)$。

其中 $\max \{x | x \in S\}$ 即为 $x$ 中最大值。

为什么这样做是对的？考虑 $0 \leq i < \max \{x | x \in S\}$ 的情况，此时 $i$ 可以与 $\max \{x | x \in S\}$ 匹配，由于我们原先存在一个无限大的点，所以此时的答案即为 $\max \{x | x \in S\} - 1$；而对于 $i \geq \max \{x | x \in S\}$ 的情况，由于 $i$ 已经不能和任何一个点匹配了，此时就跟存在一个无限大的点跟 $n + 1$ 匹配答案是一样的，为 $cnt$。

代码比较简短。

```c++
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 105;
int t, n, m, a[N], b[N];

int main() {
	scanf("%d", &t);
	for(; t; --t) {
		scanf("%d%d", &n, &m);
		a[1] = 0x3f3f3f3f;
		for(int i = 2; i <= n; i++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		stable_sort(a + 1, a + n + 1);
		stable_sort(b + 1, b + n + 1);
		int p = 1;
		bool ept = 0;
		long long cnt = 0, maxs = 0;
		for(int i = 1; i <= n; i++) {
			while(p <= n && a[i] >= b[p]) p++, ept = 1;
			cnt = max(cnt, (long long)p - i);
			if(ept)
				maxs = max(maxs, (long long)b[p - 1]);
			ept = 0;
			if(p > n) break;
			p++;
		}
		a[0] = 0;
		printf("%lld\n", (cnt - 1) * (min(1ll * m, maxs - 1)) + (cnt) * (m - min(1ll * m, maxs - 1)));
	}
	return 0;
}
```



---

## 作者：_sunkuangzheng_ (赞：4)

这题没切，太可惜了。

首先你要会 D1。

$\textbf{Key point}$：修改数组 $a$ 一个位置的值，答案最多只会变劣 $1$。

$\textbf{Proof}$：考虑可以重排数组让答案不变；如果不能，可以直接将该元素移除，剩余移动一位，一定满足要求。

然后显然的是，随着 $a_1$ 增大，答案不降。

那么二分转折点即可。时间复杂度 $\mathcal O(n \log n \log m)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 22.10.2023 19:28:03
**/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int t,n,m,a[N],b[N],c[N];
bool check(int x){
    for(int i = 1;i <= n - x;i ++)
        if(a[i] >= b[i+x]) return 0;
    return 1;
}int f(int x){
    for(int i = 2;i <= n;i ++) a[i] = c[i];
    a[1] = x;
    sort(a+1,a+n+1),sort(b+1,b+n+1);
    int l = 0,r = n,ans = -1;
    while(l <= r){
        int mid = (l + r) / 2;
        if(check(mid)) r = mid - 1,ans = mid; else l = mid + 1; 
    }return ans;
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> n >> m,a[1] = 1;
        for(int i = 2;i <= n;i ++) cin >> c[i];
        for(int i = 1;i <= n;i ++) cin >> b[i];
        int k = f(1),l = 1,r = m;
        while(l <= r){
            int mid = (l + r) / 2;
            if(f(mid) > k) r = mid - 1; else l = mid + 1;
        }int sb = r;
        cout << k * m + m - sb << "\n"; 
    }
}
```

---

## 作者：RainWetPeopleStart (赞：0)

## D1 题解

VP 时没读到可以事先移动位置，因此没秒掉 D1。

此时 $a_1=1$。

贪心一下，将 $a$ 排序，然后对每个 $a_i$ 找最小的没被选的 $b_i>a_i$，这个过程可以对 $b$ 排序+双指针解决。

## D2 题解

D2 被 long long 控了。

先尝试把这个贪心变得更易于推广。

先将 $b$ 排序。

记 $t_i$ 表示最小的，满足 $b_j>a_i$ 的 $j$。

此时，可以把 $a_i$ 挂在 $t_i$ 上。

这个时候，用大根堆维护 $t_i$，然后从右往左扫一遍 $b$，并贪心的取堆中的数即可。

具体流程是这样的：

1.遍历到位置 $i$。

2.取出堆顶元素 $v$。

3.若 $v>i$，重复 2 直到 $v\le i$。

4.若最后堆非空且 $v\le i$，则说明这个位置可以出现在最终的 $b$ 中，直接算即可。

此时指定 $a_1$ 相当于把 $t_{a_1}$ 扔堆里再问答案。

发现如果做上述第 4 步时出现 $v=i$ 的情况，则意味着若添加一个 $\ge v$ 的元素会丢掉 $v$ 的贡献。

枚举 $t_{a_1}$ 依照上述过程算即可。

## D1 代码


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
int a[N],b[N];
void slv(){
    int n,m;cin>>n>>m;
    a[1]=1;for(int i=2;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    int it=1;
    int ans=0;
    sort(a+1,a+n+1);sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        while(it<=n&&b[it]<=a[i]) it++;
        if(it<=n) ans++,it++;
    }cout<<n-ans<<endl;
}
int main(){
    int t;cin>>t;while(t--) slv();
    return 0;
}
```

## D2 代码


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
int a[N],b[N];
int tg[N],suc[N];
priority_queue<int> q;
void slv(){
    int n,m;cin>>n>>m;
    for(int i=1;i<n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    int it=1;while(!q.empty()) q.pop();
    long long ans=0;
    sort(a+1,a+n);sort(b+1,b+n+1);
    for(int i=1;i<n;i++){
        while(it<=n&&b[it]<=a[i]) it++;
        if(it<=n) q.push(it)/*,cout<<it<<' '*/;
    }int k=0;
    for(int i=n;i>=1;i--){
        tg[i]=0;
        while(!q.empty()){
            if(q.top()>i) q.pop();
            else break;
        }
        if(!q.empty()){if(q.top()==i) tg[i]=1;q.pop();k++;}
    }int fl=1;b[0]=1;
    for(int i=1;i<=n;i++){
        if(tg[i]==1) fl=0;
        if(b[i-1]>m) continue;
        if(fl) ans+=1ll*(min(b[i],m+1)-b[i-1])*(n-k-1);
        else ans+=1ll*(min(b[i],m+1)-b[i-1])*(n-k);
    }if(b[n]<=m) ans+=1ll*(n-k)*(m+1-b[n]);
    cout<<ans<<endl;
}
int main(){
    int t;cin>>t;while(t--) slv();
    return 0;
}
```

---

## 作者：AC_love (赞：0)

考虑对于任意一个数，我们都尽量找比它大的最小的数去匹配。可以证明这样的贪心策略一定是最优的。

具体做法是先把 $a, b$ 数组都排好序，然后用双指针去扫两个数组。

扫完之后，可能会出现以下两种情况：

1. $a$ 中元素都能找到匹配，$b$ 中剩下一个元素。
2. $a$ 中元素不全能找到匹配，$b$ 中剩下大于一个元素。

如果是前者的话，我们直接找到 $b$ 中剩下的元素是几即可，不难发现 $m$ 小于这个元素时 $k = 0$，而 $m$ 大于这个元素时 $k = 1$，就做完了。

如果是后者的话，我们就找到 $b$ 中剩下的元素的最大值即可，然后步骤同上。

[code](https://codeforces.com/contest/1887/submission/250568685)

---

## 作者：FireRain (赞：0)

# 思路

首先发现 $a_1$ 的变化最多会对每一次的答案与 $a_1 = 1$ 的答案产生 $1$ 的变化，并且一旦产生此变化后，接下来的所有情况会产生 $1$ 的变化。

所以考虑，二分出这个位置，然后问题就转化为了 Easy Version，拍完序后跑个双指针即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 1e5 + 10;
int T,n,m,k;
int arr[N],brr[N],t[N];

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

inline int f(int x){
	int ans = 0;
	arr[1] = x;
	for (re int i = 2;i <= n;i++) arr[i] = t[i];
	sort(arr + 1,arr + n + 1);
	for (re int i = 1,j = 1;i <= n - ans && j <= n;i++){
		while (arr[i] >= brr[j] && j <= n){
			j++;
			ans++;
		}
		j++;
	}
	return ans;
}

inline bool check(int x){
	return (f(x) <= k);
}

inline void solve(){
	n = read();
	m = read();
	for (re int i = 2;i <= n;i++) t[i] = read();
	for (re int i = 1;i <= n;i++) brr[i] = read();
	sort(brr + 1,brr + n + 1);
	k = f(1);
	int l = 1,r = m;
	while (l < r){
		int mid = l + r + 1 >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%lld\n",k * m - l + m);
}

signed main(){
	T = read();
	while (T--) solve();
	return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

大体上的思路应该和简单版本一致，建议先看本人关于简单版本的[题解](https://www.luogu.com.cn/blog/AuroraWind/cf1883g1-dances-easy-version)。

与简单版本不同的是，困难版本的 $m$ 可以不为 $1$，而是取遍 $[1,m]$ 中的整数，所以答案的总值会变大很多倍。

如果直接枚举 $m$ 次，时间复杂度将会达到 $O(mn\log n)$ 显然过不了，就算优化排序的复杂度，也是 $O(mn)$，还是过不了。

所以需要思考如何优化。

可以发现，无论第一个值取几，很多之前匹配成功的还是能匹配，所以我们考虑先不管 $a_1$，把剩下的先匹配了。

因为这里 $a$ 要少一个，所以我换了个思路，改成了用 $b$ 匹配 $a$，但实际上是一样的，只是我感觉这样写代码要方便一些。

那么，现在来讨论，如果 $a_1$ 小于没被匹配的最大的 $b$ 的话，就可以再匹配一个，也就是操作数少一个。

如果 $a_1$ 大于等于没被匹配的最大的 $b$ 的话，操作数就会多一个。

假设不算 $a_1$ 匹配的个数是 $i$，没被匹配的最大的 $b$ 是 $b_k$ 的话，答案就应该是 $(n-i-1)\times m+\max(0,m-b_k+1)$。（取 $\max$ 是因为可能 $m$ 很小，$b_k$ 很大，就会导致后面是负的）

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,m,a[100005],b[100005],ans,maxn;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m),ans=0;
		for(long long i=1;i<n;++i) scanf("%lld",&a[i]);
		for(long long i=1;i<=n;++i) scanf("%lld",&b[i]);
		sort(a+1,a+n),sort(b+1,b+n+1);
		long long j=1,flag=0;maxn=0;
		for(long long i=1;i<n;++i)
		{
			while(j<n&&a[i]>=b[j]) maxn=max(maxn,b[j]),++j;
			if(j==n)
			{
				flag=1;
				if(a[i]<b[j]) ans=m*(n-i-1)+max(0ll,m-maxn+1);
				else ans=m*(n-i)+max(0ll,m-max(maxn,b[j])+1);
				break;
			}
			++j;
		}
		if(!flag) ans=max(0ll,m-b[n]+1);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：樱雪喵 (赞：0)

日常给大家提供乐子。

首先考虑 A1（在这里应当是 G1）的做法，把 $a,b$ 序列都从小到大排序，$a$ 贪心删大的，$b$ 贪心删小的，二分答案并 $O(n)$ $\text{check}$。

## Solution 1

现在的限制变成了 $m\le 10^9$，肯定不能一个一个求答案。但是发现我们只关心这个 $a_1$ 和 $a,b$ 中其余的每个元素的大小关系。也就是说我们只要枚举 $4\times 10^5$ 种大小关系，对他们分别求解就可以得到所有答案了。

原来对一个给定序列求答案的时间复杂度是 $O(n\log n)$，考虑优化这个过程。

同样二分删掉的数量 $mid$，设 $a_1=x$，$a$ 序列排序时不包含 $a_1$。  
那么把 $x$ 插进 $a$ 的对应位置，需要判断的区间可以分成 $3$ 段：$a$ 序列中在 $x$ 前的部分，$x$ 的位置，$a$ 序列中在 $x$ 后的部分。

已经有两个 $\log$ 了，需要 $O(1)$ 地判断 $[a_l,a_r]$ 与 $[b_L,b_R]$ 对应起来是否合法。

设 $lst_i$ 表示第一个比 $b_i$ 小的位置与当前位置的差值。换句话说，取最大的 $j$ 使 $a_j<b_i$，令 $lst_i= j-i$。那么 $[a_l,a_r]$ 与 $[b_L,b_R]$ 合法的判断条件就是 $L-l\le \min\{lst_L,\dots,lst_R\}$
。使用 ST 表维护。

时间复杂度 $O(n \log^2 n)$。  
我也不知道我怎么 5min 想到这个做法调了 1h 的，所以写出来给大家看看乐子。

## Solution 2

发现答案只有两种，要不然原来的就合法，如果加了一个数不合法就把加的那个删掉，答案增加 $1$。于是就做完了。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
    long long xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9') 
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
#define int long long
const int N=2e5+5;
int T,n,m;
int a[N],b[N],d[N],L[N],tot;
int st[20][N];
il bool check(int l,int r,int L,int R)
{
    if(l>r) return 1;
    int len=__lg(R-L+1);
    int mn=min(st[len][L],st[len][R-(1<<len)+1]);
    if(mn<l-L) return 0;
    return 1;
}
il bool Check(int mid,int x)
{
    int pos=lower_bound(a+1,a+n,x)-a;
    if(pos>n-mid&&mid) return check(1,n-mid,mid+1,n);
    bool flag1=check(1,pos-1,mid+1,mid+pos-1);
    bool flag2=x<b[mid+pos];
    bool flag3=check(pos,n-mid-1,mid+pos+1,n);
    return flag1&&flag2&&flag3;
}
il int Solve(int x)
{
    int l=0,r=n;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(Check(mid,x)) r=mid;
        else l=mid+1;
    }
    return l;
}
void solve()
{
    tot=1;
    n=read(),m=read(); d[1]=m; d[++tot]=1;
    for(int i=1;i<n;i++) a[i]=read(),d[++tot]=a[i];
    for(int i=1;i<=n;i++) b[i]=read(),d[++tot]=b[i];
    sort(a+1,a+n),sort(b+1,b+n+1),sort(d+1,d+tot+1);
    for(int i=1;i<=n;i++)
    {
        L[i]=lower_bound(a+1,a+n,b[i])-a-1-i;
        // cerr<<"L[i] "<<i<<" "<<L[i]<<endl;
        st[0][i]=L[i];
    }
    for(int i=1;i<=__lg(n);i++) 
        for(int j=1;j<=n-(1<<i)+1;j++) st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
    int ans=0; 
    for(int i=1;i<=tot;i++)
    {
        if(d[i]!=d[i-1]) ans+=Solve(d[i]);
        if(d[i]==m) break;
        if(i!=tot&&d[i+1]-d[i]>1) ans+=(d[i+1]-d[i]-1)*Solve(d[i]+1);
    }
    printf("%lld\n",ans);
}
signed main()
{
    int T=read();
    while(T--) solve();
}
```

---

