# array-value

## 题目描述

You have an array of non-negative integers $ a_1, a_2, \ldots, a_n $ .

The value of a sub-array of length $ \ge 2 $ , $ a[l, r] = [a_l, a_{l+1}, \ldots, a_r] $ is the minimum value of $ a_i \oplus a_j $ such that $ l \le i < j \le r $ , where $ \oplus $ is the xor (exclusive-or) operator.

You have to find the $ k $ -th smallest value over all sub-arrays of length $ \ge 2 $ .

## 说明/提示

In the first testcase, we have subarrays with their smallest exclusive-or pair as:

 $ [1,2]: 3 $

 $ [2,3]: 1 $

 $ [3,4]: 7 $

 $ [4,5]: 1 $

 $ [1,2,3]: 1 $

 $ [2,3,4]: 1 $

 $ [3,4,5]: 1 $

 $ [1,2,3,4]: 1 $

 $ [2,3,4,5]: 1 $

 $ [1,2,3,4,5]: 1 $

The sorted order would be: $ 1, 1, 1, 1, 1, 1, 1, 1, 3, 7 $ . Therefore, the second smallest element would be $ 1 $ .

## 样例 #1

### 输入

```
4
5 2
1 2 3 4 5
2 1
4 3
4 6
1 2 4 8
5 9
1 2 3 4 5```

### 输出

```
1
7
12
3```

# 题解

## 作者：KingPowers (赞：14)

这种唐题能放在 F？场上过两百纯属是位置问题，如果放在 D 题我感觉能过 1000 个。

类似的题目其实有一大车，异或粽子、CF241B、ABC252Ex、~~魔法手杖~~等都是同一类型的题目。

对于这种异或求第 $k$ 小的问题我们一般先二分答案再用 trie 维护，假设二分答案为 $mid$，那我们就需要检查有多少个子段的价值小于等于 $mid$。

考虑枚举右端点 $r$，求出来有多少个左端点 $l$ 满足 $[l,r]$ 的价值小于等于 $mid$。不难观察到一个性质：只需要找到最靠右的 $l<r$ 满足 $a_l\oplus a_r\le mid$ 即可，因为 $l$ 再往左移动时一定会包含这个最靠右的一对，因此更靠左的 $l$ 一定也合法。

具体维护方式很简单也很套路，在往 trie 里插入时维护一个子树内的最大下标，然后把 $a_i$ 和 $mid$ 拉到 trie 上二分，从高到低枚举每一位，设当前枚举到第 $x$ 位：

- 如果 $mid$ 第 $x$ 位为 $1$，那么当前与 $a_i$ 第 $x$ 位同一方向的子树内一定都是合法的，向相反的子树走即可。

- 如果 $mid$ 第 $x$ 位位 $0$，只能向同一方向的子树走，否则这一位会大于 $mid$。

走的过程中即可求出最靠右的合法位置。

当然我们对每个 $a_i$ 求出的最靠右位置是强行要求和 $a_i$ 异或的，和之前求出的所有位置取个 $\max$ 就可以得到实际最靠右的左端点。

对于每个 $a_i$ 把最靠右的合法下标求和就得到了有多少子段价值不超过 $mid$，因此本题解决，注意二分的左边界要设为 $0$ 即可。

时间复杂度 $O(n\log^2 V)$，$V$ 是值域。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define deb(x) cerr << #x"=" << x << '\n';
using namespace std;
const int N = 5e5 + 5;
int n, k, tot = 1, a[N], ch[N * 15][2], mx[N * 15];
void add(int x, int pos){
	int now = 1;
	Rof(i, 29, 0){
		int p = (x >> i) & 1;
		if(!ch[now][p]) ch[now][p] = ++tot;
		now = ch[now][p];
		mx[now] = max(mx[now], pos);
	}
}
int query(int x, int mid){
	int now = 1, pos = 0;
	Rof(i, 29, 0){
		int p1 = (x >> i) & 1, p2 = (mid >> i) & 1;
		if(p2) pos = max(pos, mx[ch[now][p1]]), now = ch[now][p1 ^ 1];
		else now = ch[now][p1];
	}
	pos = max(pos, mx[now]);
	return pos;
}
int check(int mid){
	int sum = 0, pos = 0;
	For(i, 1, n){
		pos = max(pos, query(a[i], mid));
		add(a[i], i); sum += pos;
	}
	For(i, 0, tot) mx[i] = ch[i][0] = ch[i][1] = 0;
	tot = 1;
	return sum;
}
void Solve(){
	cin >> n >> k;
	For(i, 1, n) cin >> a[i];
	int l = 0, r = (1 << 30) - 1, ans = 0;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid) >= k) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	cout << ans << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：lfxxx (赞：6)

考虑二分答案 $mid$。

接着我们计算多少个区间的答案小于等于 $mid$。

考虑对于 $r$ 来说，随着 $l$ 的递减，区间的价值在递减，也就是说存在一个分界点 $t_r$ 满足对于任意 $l \in [1,t]$ 都有区间 $[l,r]$ 的贡献小于等于 $mid$，由于区间内可能包含子区间，所以我们只设计状态 $dp_{r}$ 表示对于任意 $l \in [1,dp_r]$ 都有区间 $[l,r]$ 内以 $r$ 为右端点的子区间最小价值小于等于 $mid$，不难发现 $dp_r$ 就是最大的满足 $a_{j} \oplus a_i \leq mid$ 的 $j$，且有 $t_r = \max(t_{r-1},dp_r)$，考虑从前往后扫描线的过程中用一个 01trie 维护每个二进制前缀最大的（最靠后的）存在位置，查询时根据异或上的数 $a_i$ 在 01trie 上查询满足 $a_j \oplus a_i \leq mid$ 中最大的（最靠后的）存在位置即可。

时间复杂度 $O(n \log^2 V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5*40+114;
int dp[maxn];
int ls[maxn],rs[maxn],tot;
int n,a[maxn],rt;
int f[maxn];
long long k;
void ins(int v,int tm){
    int u=rt;
    dp[u]=max(dp[u],tm);
    for(int i=30;i>=0;i--){
        if((1<<i)&v){
            if(rs[u]==0) rs[u]=++tot;
            u=rs[u];
        }else{
            if(ls[u]==0) ls[u]=++tot;
            u=ls[u];
        }
        dp[u]=max(dp[u],tm);
    }
}
int ask(int v,int s){
    int u=rt;
    int res=0;
    for(int i=30;i>=0;i--){
        if((1<<i)&s){
            //01 反转
            if((1<<i)&v){
                res=max(res,dp[rs[u]]);
                u=ls[u];
            }else{
                u=rs[u];
            }
        }else{
            if((1<<i)&v){
                res=max(res,dp[ls[u]]);
                u=rs[u];
            }else{
                u=ls[u];
            }
        }
    }
    res=max(res,dp[u]);
    return res;
}
bool check(int mid){
    rt=++tot;
    long long sum=0;
    for(int i=1;i<=n;i++){
        f[i]=ask(mid,a[i]);
        ins(a[i],i);
    }
    for(int i=1;i<=n;i++) f[i]=max(f[i],f[i-1]),sum+=f[i];
    for(int i=0;i<=tot;i++) ls[i]=rs[i]=dp[i]=0;
    tot=0;
    return sum>=k;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        long long l=-1,r=2e9+114;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(check(mid)==true) r=mid;
            else l=mid;
        }
        cout<<r<<"\n";
    }
    return 0;
}
```

---

## 作者：subcrip (赞：5)

看到这种求第 $k$ 小的问题，首先想到了二分答案。

设当前想要检查 $x$ 是不是第 $k$ 小的值，我们统计有多少个子数组的值不超过 $k$。枚举子数组的右端点 $r$，设第一次满足 $[l,r]$ 的值不超过 $k$ 的左端点为 $l$。

一共就两种情况：要么这个子数组的最小值是 $a_j\oplus a_r$，要么它是由之前的某个数对异或得到。对于第一种情况，只需找到最近的左端点 $j<r$ 使得 $a_j\oplus a_r\leqslant k$。对于第二种情况，我们已经在 $r-1$ 时考虑过了，记 $r-1$ 时的答案为 $l'$。

所以得到 $l=\max(j,l')$。问题只剩下如何求出 $j$。可以维护一棵 01-Trie，在枚举 $r$ 的过程中向其中插入 $r$ 左边的元素，然后用类似查询最大异或值的方法求解。

时间复杂度 $O(n\log^2U)$，其中 $U$ 是值域大小。

Code:

```cpp
void solve() {
    read(int, n);
    read(ll, k);
    readvec(int, a, n);

    auto work = [&] (int target) -> ll {
        vector<pair<array<int, 2>, int>> trie(1);

        auto trie_insert = [&] (int x, int pos) {
            int curr = 0;
            for (int i = 30; ~i; --i) {
                int bit = (x >> i) & 1;
                if (not trie[curr].first[bit]) {
                    trie[curr].first[bit] = trie.size();
                    trie.emplace_back();
                }
                curr = trie[curr].first[bit];
                chmax(trie[curr].second, pos);
            }
        };

        auto trie_query = [&] (int x) {
            int curr = 0;
            int res = 0;
            for (int i = 30; ~i; --i) {
                int bit = (x >> i) & 1;
                if (((target >> i) & 1) == 1) {
                    if (bit == 1) {
                        chmax(res, trie[trie[curr].first[1]].second);
                        curr = trie[curr].first[0];
                    } else {
                        chmax(res, trie[trie[curr].first[0]].second);
                        curr = trie[curr].first[1];
                    }
                } else {
                    if (bit == 1) {
                        curr = trie[curr].first[1];
                    } else {
                        curr = trie[curr].first[0];
                    }
                }
                if (curr == 0) break;
            }
            return max(res, trie[curr].second);
        };

        ll cnt = 0;
        trie_insert(a[0], 1);
        int prev = 0;
        for (int i = 1; i < n; ++i) {
            chmax(prev, trie_query(a[i]));
            cnt += prev;
            trie_insert(a[i], i + 1);
        }

        return cnt;
    };

    int l = 0, r = INT_MAX;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (work(mid) < k) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    cout << l << '\n';
}
```

---

## 作者：Diaоsi (赞：3)

[Array Value](https://codeforces.com/contest/1983/problem/F)

怎么大家写的都是 $\mathcal{O}(n\log^2V)$，我觉得有必要发一下 $\mathcal{O}(n\log n\log V)$ 的做法。

首先区间异或最小值等价于将区间排序，然后取相邻两个数的异或值中的最小值。

简单证明一下这个结论，将排完序的序列按照最高位 $1$ 分类，于是整个序列就被分成若干个连续段。此时任意一个元素一定是与相同段内的元素异或会更优，否则最高位不会被消去。

在同一段内由于最高位相同，可以去掉最高位然后再递归进行上述过程，正确性显然。$\ \Box$

考虑二分答案，每次检查有多少个区间的异或最小值比当前值 $x$ 小。可以使用双指针 $l,r$，枚举区间的右端点，发现当左端点右移时区间异或最小值一定是单调递增的，移动到第一个区间异或最小值大于 $x$ 的位置即可。产生的贡献是 $l-1$。

于是问题变成了怎么动态维护区间异或最小值，可以开两个 ```std::multiset```，第一个 ```std::multiset``` 用于维护排序后的区间，在插入元素时把当前元素与前驱后继产生的异或贡献插入第二个 ```std::multiset``` 中，删除同理。

每次检查的时间复杂度是 $\mathcal{O}(n\log n)$ 的，故总时间复杂度为 $\mathcal{O}(n\log n\log V)$。

贴一下关键部分的代码（把快读和头文件去掉了）：

```cpp
int T,n,a[N];
ll k;
multiset<int> s1,s2;
ll check(int x){
	s1.clear();s2.clear();
	ll res=0;
	for(int i=1,j=1;i<=n;i++){
		auto it1=s1.lower_bound(a[i]);
		if(it1!=s1.end()&&it1!=s1.begin()){
			auto it2=it1;it2--;
			s2.erase(s2.find(*it1^*it2));
		}
		if(it1!=s1.end())s2.insert(*it1^a[i]);
		if(it1!=s1.begin()){
			auto it2=it1;it2--;
			s2.insert(*it2^a[i]);
		}
		s1.insert(a[i]);
		while(s2.size()&&*s2.begin()<=x){
			it1=s1.lower_bound(a[j]);
			auto pre=it1,nxt=it1;pre--,nxt++;
			if(nxt!=s1.end())s2.erase(s2.find(*nxt^a[j]));
			if(it1!=s1.begin())s2.erase(s2.find(*pre^a[j]));
			if(nxt!=s1.end()&&it1!=s1.begin())
				s2.insert(*nxt^*pre);
			s1.erase(it1);
			++j;
		}
		res+=j-1;
	}
	return res;
}
void solve(){
	qio>>n>>k;
	for(int i=1;i<=n;i++)qio>>a[i];
	int l=0,r=1073741824,res=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)>=k)r=(res=mid)-1;
		else l=mid+1;
	}
	qio<<res<<'\n';
}
int main(){
	qio>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：__little__Cabbage__ (赞：2)

最不喜欢 ds 姐姐啦！

第一次交~~不~~可爱数据结构的题解，感觉比其他题解好写多了。

但是数据结构题总是调半天调不出来 QwQ。

## Solution

一眼二分答案，考虑如何 check。

考虑如何统计答案 $\le k$ 的区间个数，复杂度要求 $O(n)$ 或者再加一只 $\log$。可以枚举 $r$，对于每个 $r$ 找到一个最大的 $l$ 满足以 $1 \sim l$ 为左端点的区间答案都 $\le k$，这是显然成立的，因为如果 $a_l \oplus a_r \le k$，那么 $l$ 左边的一定可以取 $l,r$ 这一对数。

于是问题就转化成了在 $[1,r]$ 内找到一个最大的 $l$ 满足 $a_l \oplus a_r \le k$，这个可以 01trie 解决，具体地，从高位向低位枚举，如果当前位置（指二进制位）$mid$ 的值为 $1$，那么这一位就可以与 $a_r$ 不同，如果为 $0$ 则必须相同了，贪心正确性显然。循环时依次把 $r$ 塞到 01trie 里。当然这是固定 $a_l$ 必须与 $a_r$ 异或的情况，所以再跟以前的结果取个 $\max$ 就可以了。

注意因为 01trie 要用到二进制位，所以二分的上界必须取 `INT_MAX`。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define int long long
#define il inline
using namespace std;

const int MAXN=1e5+5,MAXlg=30; //29.897353
int n,k,a[MAXN];

class __01trie
{
public:
	struct node{int ch[2],mx;} v[MAXN*MAXlg];
	int tot=1;
	
	il void clear() {for(int i=0;i<=tot;++i) v[i]=(node){{0,0},0}; tot=1;}
	
	il void update(int x,int ind)
	{
		int pos=1; bool now;
		for(int i=MAXlg-1;i>=0;--i)
		{
			now=(x&(1<<i));
			if(!v[pos].ch[now]) v[pos].ch[now]=++tot;
			pos=v[pos].ch[now];
			v[pos].mx=max(v[pos].mx,ind);
		}
	}
	
	il int query(int x,int mid)
	{
		int pos=1,ans=0; bool now;
		for(int i=MAXlg-1;i>=0;--i)
		{
			now=(x&(1<<i));
			if(mid&(1<<i)) ans=max(ans,v[v[pos].ch[now]].mx),pos=v[pos].ch[!now];
			else pos=v[pos].ch[now];
			if(!pos) break;
		}
		return max(ans,v[pos].mx);
	}
} tr;

il bool check(int x)
{
	tr.clear();
	
	int mx=0,res=0;
	tr.update(a[1],1);
	for(int r=2;r<=n;++r)
	{
		mx=max(mx,tr.query(a[r],x)),res+=mx;
		tr.update(a[r],r);
	}
	
	return res>=k;
}

il void solve()
{
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	
	int l=0,r=2147483647,mid=-1;
	while(l<r)
	{
		mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	
	cout<<r<<'\n';
}

signed main()
{
	ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
	int T; cin>>T; while(T--) solve();
	return 0;
}
```

---

## 作者：Alex_Wei (赞：2)

### [CF1983F array-value](https://www.luogu.com.cn/problem/CF1983F)

二分答案，求有多少子区间的权值不大于 $mid$。

根据权值的计算方式，若一个区间包含另一个区间，则前者的权值不大于后者的权值。固定右端点 $r$，随着左端点 $l$ 的位置增加，区间的权值不降。因此，存在临界位置 $p$ 使得 $p$ 及其左侧的位置作为左端点时，区间的权值不大于 $mid$，$p$ 右侧的位置作为左端点时，区间的权值大于 $mid$。

设 $p_i$ 表示当 $i$ 为右端点时的临界点，即 $p_i$ 最大且 $[p_i, i]$ 的权值不大于 $mid$，若不存在则认为 $p_i = 0$。只需求出所有 $p_i$。

设 $q_i$ 表示 $i$ 左侧最右边的位置使得 $a_{q_i}\oplus a_i \leq mid$，若不存在则认为 $q_i = 0$，则 $p_i = \max(p_{i - 1}, q_i)$。直接求 $q_i$ 需要二分和可持久化字典树，无法接受。

当 $q_i$ 能够更新 $p_i$ 时，一定存在 $p_i \lt pos \lt i$ 使得 $a_{pos} \oplus a_i \leq mid$。维护下标在 $[p_i + 1, i - 1]$ 的所有数构成的 01-Trie，即可快速判断左端点是否需要向右移动。

设 $V$ 为值域大小，算法的时间复杂度为 $\mathcal{O}(n\log ^ 2 V)$，空间复杂度为 $\mathcal{O}(n\log V)$。[代码](https://codeforces.com/contest/1983/submission/270565219)。

*本题解将同步发表于清华大学学生算法协会微信公众号「酒井算协」。

---

## 作者：yingkeqian9217 (赞：1)

这里提供一种比较好写的时间复杂度 $O(n\log V)$ 的做法。

套路地，对于求第 $k$ 小问题，通过二分答案转化成求 $< x$ 的方案数问题。直接做并不好做，考虑扫描线，记录每个点为右端点时的最优左端点，于是只需要考虑单个数的匹配。

注意到 $a_i \oplus a_j <x$ 的左侧异或和并不好做，转而对右侧进行拆分，对于其二进制的第 $k$ 位的 1，将贡献拆成“要求异或和的 $k$ 位之前与 $x$ 相同，第 $k$ 位为 0，其余无要求”。

0 的限制是平凡的，只需要这几位都取相同即可；对于 1 的限制，注意到这一位的取 0 或 1 均无关，所以等价于无限制。此时我们只要对于拆成的每个贡献计算只保留元素对应 0 位的二进制值即可，此时问题等价于求等值前驱，容易维护。此时时间复杂度 $O(n\log^2 V)$。

考虑在二进制问题中二分答案的另一种表现形式，拆位贪心。当我们从高到低逐位考虑时，每次只会加入 1 条限制，直接在匹配数组上取最大值即可，单次只需要扫一次数组。

用哈希表实现前驱，时间复杂度 $O(n\log V)$。

```cpp
#include<bits/stdc++.h>
#define maxn 510005
#define int long long
using namespace std;

int n,k,a[maxn],pre[maxn];
unordered_map<int,int>mp;
int check(int x){
	mp.clear();
	int res=0,maxx=0;
	for(int i=1;i<=n;i++){
		int cur=a[i]&x;
		maxx=max(maxx,pre[i]);
		if(mp.count(cur)) maxx=max(maxx,mp[cur]);
		mp[cur]=i;
		res+=maxx;
		if(res>=k) return 0;
	}
	return 1;
}
void update(int x){
	mp.clear();
	for(int i=1;i<=n;i++){
		int cur=a[i]&x;
		pre[i]=max(pre[i],pre[i-1]);
		if(mp.count(cur)) pre[i]=max(pre[i],mp[cur]);
		mp[cur]=i;
	}
}
void solve(){
	int x=0;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),pre[i]=0;
	for(int i=30;i>=0;i--){
		if(check(~(x|((1<<i)-1)))) update(~(x|((1<<i)-1))),x|=(1<<i);
	}
	printf("%lld\n",x);
}
signed main(){
	signed T=1;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：TTpandaS (赞：1)

可以发现区间内两数异或最小值就是将区间排序后相邻两数异或最小值。

先二分答案，然后对于每个 $r$，都找到第一个 $l$ 满足 $[l,r]$ 答案小于等于 $mid$，也就是第一个 $l$ 满足 $[l,r]$ 内 $a_r$ 的前驱和后继与 $a_r$ 的异或值小于等于 $mid$。我赛时用的二分加主席树，时间复杂度 $ O(n \log^3 n)$，还打挂了没调出来。实际上可以直接使用双指针和 set 寻找前驱后继。$r$ 增加时第一个 $l$ 肯定也是单调不减的，所以使用双指针。找前驱后继就先在 set 里 `lower_bound` 出 $a_r$ 在 set 中的位置，加一和减一后就是前驱和后继。时间复杂度 $ O(n \log^2 n)$。

check 部分：

```cpp
  int check(int mid){
      multiset<int> t;
      int l=0,res=0;
      for(int i=1;i<=n;i++){
          t.insert(a[i]);
          while(l<i){
              if(l){
                  t.erase(t.find(a[l]));
              }
              auto x=t.lower_bound(a[i]);
              bool flag=0;
              if(x!=t.end()){
                  ++x;
                  if(x!=t.end()){
                      if(((*x)^a[i])<=mid){
                          flag=1;
                      }					
                  }
                  --x;
              }
              if(x!=t.begin()){
                  --x;
                  if(((*x)^a[i])<=mid){
                      flag=1;
                  }
                  ++x;
              }
              if(flag){
                  l++;
              }
              else{
                  if(l){
                      t.insert(a[l]);
                  }
                  break;
              }
          }
          res+=l;
      }	
      return res;
  }
```

---

## 作者：Priestess_SLG (赞：0)

喜提最劣解，来补一下题解。考虑一个关键性质：

对于任意三个正整数 $x,y,z$，若满足 $x\le y\le z$，则必然有 $\min(x\oplus y,y\oplus z)\le x\oplus z$（类似的题目是 AT_abc308_g）。证明可以按位考虑。

然后显然的先二分答案是 $x$，那么只需要 check 是否有至少 $k$ 个位置，使得权值 $\le x$。然后发现在固定右端点，移动左端点时，权值具有单调性（单调不递增）。于是考虑记录一下对于每一个右端点，最右边的使得权值 $\le x$ 的位置 $f_i$。然后又能够发现 $f_i$ 单调不递减，于是考虑双指针维护 $f_i$ 的值。具体的，类似于 AT_abc308_g 的做法，开两个 `multiset`（或者平衡树）来维护当前区域内所有的 $a$ 的值和所有相邻两个 $a$ 值异或的值，然后加入当前的右端点，并更新两个 `multiset` 的值。此时若维护相邻异或值的 `multiset` 内的最小值已经小于或等于 $k$ 了，那么就移动左端点，并每一次在两个 `multiset` 中删除当前左端点更新答案，直到 `multiset` 内的最小值再次 $>k$ 为止。此时二分有一只值域的 $\log$，`multiset` 或者平衡树有一只巨大的 $\log$，合起来就是巨大常数的 $O(n\log n\log W)$，但是可以卡着时限通过。

[代码](https://codeforces.com/contest/1983/submission/301210359)，感觉不如指针移动错了调了 $1.5$ 小时。

---

## 作者：forest114514 (赞：0)

VP 结束后一分钟就调过了，还用了一种大炮打蚊子的办法，唐完了……

还是讲一讲这种大炮打蚊子的办法吧，毕竟跑得挺快即使在 `#define int long long` 这个常数炸弹的加持下最慢点也只跑了 $1.01s$。

首先考虑如何求一个区间的最小异或值 $\min\limits_{l\leq i<j\leq r} a_{i}\oplus a_{j}$，这是经典的支配对能做的题，一个关键的结论是排序后越靠近的两个数异或和越小，所以我们可以尝试求出支配点对：首先枚举二进制下 LCS 的长度，LCS 相等的若干数按照下标排序后相邻两个就是一对关键对，通过分析不难发现至多有 $O(n\log V)$ 个关键对，就能扫描线求区间的最小异或值。

求出关键点对后再看这道题怎么做，不难发现可以二分 $mid$ 求有多少区间的最小异或值 $\leq mid$，考虑所有异或和 $\leq mid$ 的关键点对 $(l,r)$，不难所有满足 $L\leq l,R\geq r$ 的区间 $[L,R]$ 都是最小异或值 $\leq mid$ 的区间。所有的点对的限制构成了一个平面上矩形面积并的东西，但注意到这些矩形都是一个前后缀的矩形，可以不用任何数据结构直接求后缀 $\max$ 就行了。

单次 check 的复杂度就是 $O(n\log V)$，一共的时间复杂度就是 $O(n\log^2 V)$。

代码：

```cpp
//蒟蒻一枚 rp++
//即得易见平凡，仿照上例显然。留作习题答案略，读者自证不难
//反之亦然同理，推论自然成立，略去过程Q.E.D.，由上可知证毕
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define repp(i,a,b) for(int i=(a);i<(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define tep(i,x) for(int i=head[x];~i;i=ne[i])
#define ls(x) x<<1
#define rs(x) x<<1|1
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e16
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef double db;
namespace IO{
	template<typename T> inline void read(T &x){
		bool f=1;x=0;char ch=gc();
		while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
		while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
		x=f?x:-x;
	}
	template<typename T> inline void write(T x){
		if(x<0) putchar('-'),x=-x;
	   	if(x>9) write(x/10);
	   	putchar(char('0'+x%10));
	}
	template <typename T,typename ...Args> inline
	void read(T &x,Args &...args){read(x);read(args...);}
	template<typename T> inline void write(T x,char c){write(x),putchar(c);}
}
using namespace IO;
//bool _ST;
#define int LL
const int N=1e5+100,M=N*32;
struct NODE{
	int l,r,v;
}d[M];
int a[N],p[N];
int n,tot,mn[N];
LL k;
LL check(LL mid){
	LL res=0;
	rep(i,1,n) mn[i]=INF;
	rep(i,1,tot) if(d[i].v<=mid) mn[d[i].l]=min(mn[d[i].l],d[i].r);
	int minn=inf;
	per(i,n,1){
		minn=min(minn,mn[i]);
		if(minn<=n) res+=n-minn+1;	
	}
	return res;
}
void solve(){
	read(n,k);tot=0;
	rep(i,1,n) read(a[i]),p[i]=i;
	rep(i,0,30){
		sort(p+1,p+1+n,[&](int x,int y){
			if((a[x]>>i)==(a[y]>>i)) return x<y;
			return (a[x]>>i)<(a[y]>>i);
		});
		rep(j,2,n) if((a[p[j]]>>i)==(a[p[j-1]]>>i)) d[++tot]=(NODE){p[j-1],p[j],a[p[j]]^a[p[j-1]]};
	}
	rep(i,1,tot) if(d[i].l>d[i].r) swap(d[i].l,d[i].r);
	LL l=0,r=INF;
	while(l<r){
		LL mid=l+r>>1;
		if(check(mid)>=k) r=mid;
		else l=mid+1;
	}
	write(l,'\n');
}
//bool _ED;
signed main(){
	//fprintf(stderr,"%.20lf MB\n",(&_ST-&_ED)/1048576.0);
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T;read(T);
	while(T--) solve(); 
	//fprintf(stderr,"%.4lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
//谨记:
//十年OI一场空，不开longlong见祖宗
//数据千万条，清空第一条。多测不清空，爆零两行泪。清空不规范，TLE总相伴。
//快读要加类型名

```

---

## 作者：gan1234 (赞：0)

考虑二分答案，这样问题就转化为了：有多少子区间的权值小于等于 $x$。由于一个子区间的权值是 $\min_{l\le j<k\le r}(a_j\oplus a_k)$，因此考虑扫描线，枚举右端点。

由于随着左端点的向左移，区间的权值一定不升，所以我们每次只需要维护最大的左端点使得区间权值小于等于 $x$。

这个东西应该能用 01 Trie 维护，每个节点维护子树内最大的左端点，询问就类似查询异或最大值。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define ll long long
using namespace std;
int n;
ll k;
int a[MAXN];

int cnt=1;
int ch[MAXN*31][2],v[MAXN*31];
void insert(int k,int pos){
	int x=1;
	for(int i=30;i>=0;i--){
		v[x]=max(v[x],pos);
		int t=(k>>i)&1;
		if(!ch[x][t])ch[x][t]=++cnt,v[cnt]=0;
		x=ch[x][t];
	}
	v[x]=max(v[x],pos);
}
void erase(int x,int k,int pos,int l){
	if(l<0){
		if(v[x]==pos)v[x]=0;
		return ;
	}
	int t=(k>>l)&1;
	if(!ch[x][t])return ;
	erase(ch[x][t],k,pos,l-1);
	v[x]=max(v[ch[x][0]],v[ch[x][1]]);
}

int query(int k,int lim){
	int res=0;
	int x=1,s=0;
	for(int i=30;i>=0;i--){
		int t=(k>>i)&1;
		if(t){
			if((s^(1<<i))<=lim){
				res=max(res,v[ch[x][1]]);
				x=ch[x][0];
				s^=(1<<i);
			}else{
				x=ch[x][1];
			}
		}else{
			if((s^(1<<i))<=lim){
				res=max(res,v[ch[x][0]]);
				x=ch[x][1];
				s^=(1<<i);
			}else{
				x=ch[x][0];
			}
		}
	}
	res=max(res,v[x]);
	return res;
}

ll check(int x){
	for(int i=1;cnt>=i;i++)v[i]=0;
	for(int i=1;cnt>=i;i++)ch[i][0]=ch[i][1]=0;
	int l=0;cnt=1;
	ll res=0;
	for(int i=1;n>=i;i++){
		int t=query(a[i],x);
		while(l<t){
			erase(1,a[l],l,30);
			l++;
		}
		res+=l;
		insert(a[i],i);
	}
	while(l<n)erase(1,a[l],l,30),l++;
	return res;
}
void work(){
	cin>>n>>k;
	for(int i=1;n>=i;i++)cin>>a[i];
	ll l=0,r=2e9;
	while(r>l){
		ll mid=(l+r)/2;
		if(check(mid)<k)l=mid+1;
		else r=mid;
	}
	cout<<l<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	int _T;
	cin>>_T;
	while(_T--)work();
	return 0;
}
```

---

## 作者：幸存者 (赞：0)

一个不用二分的赛时（没调完）做法，由于我不知道二分怎么做，所以我也不知道这两个做法是不是本质相同的。

考虑从高到低每一位答案为 $0/1$，可以直接把所有数这一位后面的二进制都去掉，也就是整体右移。

假设现在正在考虑 $2^i$ 这一位，更高位答案构成的数为 $p$（不补 $0$），那么我们只需要计算出异或最小值为 $2p$ 的区间个数，与当前的 $k$ 比较即可。（若小于 $k$，就让 $k$ 减去这个值，并且这一位答案为 $1$，否则答案为 $0$）

对于这个问题，容易想到双指针的做法，为了求出每个 $l$ 开始的所有区间，我们可以用两个指针 $r_1,r_2$，分别代表第一个异或最小值为 $2p$ 的区间为 $[l,r_1]$，最后一个异或最小值为 $2p$ 的区间为 $[l,r_2]$。

将数分别放到两个 Trie 里，动态维护异或值为 $2p$ 的二元组的个数。第一个即 $[l,r_1]$ 异或值为 $2p$ 的有序对个数大于 $0$，第二个即 $[l,r_2+1]$ 可以取到更小的异或值。

综上，我们完成了这道题，时间复杂度为 $O(n\log^2n)$。

## $\text{AC Code}$

```cpp
// superyijin AK IOI
// wangsiyuanZP AK IOI
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[100010];
int now[2], t[2][3000010][2], siz[2][3000010];
void insert(int o, int k, int z)
{
	int x = 0;
	for (int i = 29; i >= 0; i--)
	{
		int y = (k >> i) & 1;
		if (!t[o][x][y]) t[o][x][y] = ++now[o];
		x = t[o][x][y];
		siz[o][x] += z;
	}
}
int ans;
int query(int o, int k)
{
	int x = 0;
	for (int i = 29; i >= 0; i--)
	{
		int y = (k >> i) & 1;
		if (siz[o][t[o][x][y]])
		{
			if ((ans >> i) & 1) return -1; // 存在异或值更小的情况
			else x = t[o][x][y];
		}
		else
		{
			if ((ans >> i) & 1) x = t[o][x][y ^ 1];
			else return 0; // 异或值较大，不计入个数
		}
	}
	return siz[o][x];
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;
		for (int i = 1; i <= n; i++) cin >> a[i];
		ans = 0;
		for (int i = 29; i >= 0; i--)
		{
			for (int o = 0; o < 2; o++) for (int j = 0; j <= now[o]; j++) t[o][j][0] = t[o][j][1] = siz[o][j] = 0;
			now[0] = now[1] = 0;
			ans *= 2;
			int r1 = 0, r2 = 0, cnt1 = 0, cnt2 = 0, s = 0;
			for (int l = 1; l <= n; l++)
			{
				if (l > 1)
				{
					insert(0, a[l - 1] >> i, -1);
					insert(1, a[l - 1] >> i, -1);
					cnt1 -= max(0ll, query(0, a[l - 1] >> i));
					cnt2 -= max(0ll, query(1, a[l - 1] >> i));
				}
				while (r2 < n && query(1, a[r2 + 1] >> i) >= 0)
				{
					cnt2 += query(1, a[r2 + 1] >> i);
					insert(1, a[++r2] >> i, 1);
				}
				while (r1 < r2 && cnt1 <= 0)
				{
					cnt1 += query(0, a[r1 + 1] >> i);
					insert(0, a[++r1] >> i, 1);
				}
				if (cnt1 > 0) s += r2 - r1 + 1;
			}
			if (s < k)
			{
				k -= s;
				ans++;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
// superyijin AK IOI
// wangsiyuanZP AK IOI
```

---

