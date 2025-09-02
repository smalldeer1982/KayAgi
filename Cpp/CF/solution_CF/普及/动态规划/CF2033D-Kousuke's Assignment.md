# Kousuke's Assignment

## 题目描述

After a trip with Sakurako, Kousuke was very scared because he forgot about his programming assignment. In this assignment, the teacher gave him an array $ a $ of $ n $ integers and asked him to calculate the number of non-overlapping segments of the array $ a $ , such that each segment is considered beautiful.

A segment $ [l,r] $ is considered beautiful if $ a_l + a_{l+1} + \dots + a_{r-1} + a_r=0 $ .

For a fixed array $ a $ , your task is to compute the maximum number of non-overlapping beautiful segments.

## 样例 #1

### 输入

```
3
5
2 1 -3 2 1
7
12 -4 4 43 -3 -5 8
6
0 -4 0 3 0 1```

### 输出

```
1
2
3```

# 题解

## 作者：chenxi2009 (赞：6)

# 思路
考虑前缀和思想，令 $s_0=0,s_i=\sum_{j=1}^{i}a_j$，则子段 $[l,r]$ 是“美丽的”当且仅当 $s_r-s_{l-1}=0$，即 $s_{l-1}=s_r$。

贪心一下当从左往右扫当前扫到的位置可以作为“美丽的”子段的最右端时一定将它作为一个子段，这样对后面产生子段的影响一定最小。

所以每一次要检查当前的前缀和是否出现过，出现过则分割出一个美丽子段。需要特判 $0$。`set` 维护即可，复杂度 $O(\sum n\log n)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[100001],ans;
long long sum;
set<long long>s;
int main(){
	scanf("%d",&T);
	while(T --){
		ans = 0,sum = 0,s.clear(),s.insert(0);//多测清空 
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++){
			scanf("%d",&a[i]);
			sum += a[i];
			if(s.count(sum)){
				sum = 0,ans ++,s.clear(),s.insert(0);//找到了一个子段，前缀和、set 均清空 
			}
			else{
				s.insert(sum);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

设 $dp_i$ 表示前 $i$ 个数最多能分成多少段。首先可直接不管这个数，转移为 $dp_i\gets dp_{i-1}$。从 $i$ 开始往前找到第一个位置使得这一段的和为 $0$（记为 $j$），那么有转移：$dp_i\gets dp_{j-1}+1$。如何找 $j$？对 $a$ 作前缀和，记为 $s$，那么满足 $s_i=s_{j-1}$，于是打个桶记录 $s$ 中元素的最后出现位置进行调用即可。由于 $s$ 的值域范围较大，可使用 `std::map` 或者 `std::unordered_map` 实现桶的功能。

# Code

```cpp
#include<bits/stdc++.h>
std::map<long long,int>mp;
int dp[100005];
int T,n;
long long s;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		mp.clear();
		mp[0]=0;s=0;
		for(int i=1,x;i<=n;++i){
			scanf("%d",&x);s+=x;
			dp[i]=dp[i-1];
			if(mp.count(s))
				dp[i]=std::max(dp[i],dp[mp[s]]+1);
			mp[s]=i;
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
```

---

## 作者：Sakura_Emilia (赞：1)

# Solution

基本思路：**前缀和** + **DP**。

由于题目要求某一连续子段为 0，想到前缀和。也就是需要从前往后统计，有多少个至多重叠两端点的子段，使得所有的子段中的各个元素均不相等。

DP 数组表示对于前 n 个元素，不重叠的美丽线段的最大数目。

使用 `map` 加 `priority_queue` 作为桶，来记录当前所有的数字的下标。`priority_queue` 用来动态维护对于某一已经出现过的数字，其最右端那个位置的下标。当更新到一个已经出现过的数字的时候，我们只需要更新该数字历史最右端的位置即可。

# Tips

在 Codeforces 平台上一定不要使用 `unordered_map`，全部使用 `map` 来替换，Codeforces 平台上的 `unordered_map` 会退化效率极低。这道题好多人都是用的 `unordered_map` 被 Hack 惨了。

# Code

```cpp
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;
const int N = 1e6 + 8;

int T, n, k;
int dp[N], a[N];
map<int, priority_queue<int>> mp;

inline void solve() {
    mp.clear();
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> k;
        a[i] = a[i - 1] + k;
    }

    dp[0] = 0;
    mp[0].push(0);
    for(int i = 1; i <= n; i++){
        dp[i] = 0;
        if(!mp[a[i]].empty()){
            int tt = mp[a[i]].top();
            dp[i] = max(dp[i], dp[tt] + 1);
        }
        mp[a[i]].push(i);
        dp[i] = max(dp[i], dp[i-1]);
    }

    cout << dp[n] << endl;
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

前缀和优化 DP。

设 $dp_i$ 为前 $i$ 个数最多有多少个**不重叠**的美丽子段，$sum_i$ 为 $1 \sim i$ 的前缀和。

如果区间 $[l,r]$ 要组成一个美丽子段，那么必有 $sum_r - sum_{l - 1} = 0$。

下面分类讨论，如果第 $i$ 个数不作为某个美丽字段的末尾，则 $dp_i = dp_{i - 1}$，如果第 $i$ 个数作为某个美丽字段的末尾，则 $dp_i = dp_w + 1$，其中 $w$ 表示上一个前缀和是 $sum_i$ 的数的位置，这样才能组成一个美丽子段。

综上，转移方程就是 $dp_i = \max(dp_{i - 1},dp_w + 1)$。

直接枚举的话复杂度是 $O(n^2)$，用 map 记录上一个前缀和是 $sum_i$ 的数的位置即可，复杂度 $O(n\log n)$。

代码：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 10;
int t,n,ans;
int a[N],sum[N],dp[N];
map <int,int> mp;
void solve(){
	mp.clear();
	cin >> n;
	for (int i = 1 ; i <= n ; i++){
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
		dp[i] = 0;
	}
	mp[0] = 0;
	for (int i = 1 ; i <= n ; i++){
		dp[i] = dp[i - 1];
		if (mp.count(sum[i]) > 0)
		    dp[i] = max(dp[i],dp[mp[sum[i]]] + 1);
		mp[sum[i]] = i;
	}
	cout << dp[n] << endl;
}
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> t;
	while (t--) solve();
	return 0;
}
```

多测不清空，赛场两行泪。

---

## 作者：K_J_M (赞：0)

# Kousuke's Assignment

## 题目描述

给出一个长度为 $n$ 的数列 $a_i$，要求计算数组中**不重叠**的子段数量，使得每个子段是美丽的。

一个子段 $[l,r]$ 被认为是美丽的，当且仅当 $a_l+a_{l+1}+\dots+a_r=0$。

你的任务是计算最多有多少个不重叠的美丽子段。
# Solution
简单优化 dp。设 $pre_i$ 为 $a_i$ 的前缀和数组，$dp_i$ 表示前 $i$ 个最多的不重叠的美丽子段。那么转移为 
$$dp_i=\max \begin{cases} \max(dp_{i-1},[pre_i=0])\\ dp_j+1& pre_i-pre_j=0 \end{cases}$$
时间复杂度为 $\mathcal O(n^2)$，考虑优化。发现条件 $pre_i-pre_j=0$ 可以转化为 $pre_i=pre_j$，然后又发现 $dp_i$ 数组是单调递增的，所以我们可以从最近的一个满足条件的 $j$ 转移过来。记 $last_i$ 表示上一个前缀和是 $i$ 的位置，那么转移可以写为 $dp_i=\max(dp_i,dp_{last_{pre_i}}+1)$，这是 $\mathcal O(1)$ 转移，值得注意的是，我们转移时需要考虑 $last$ 有没有值。时间复杂度 $\mathcal O(n\log n)$。\
[Ac Code](https://www.luogu.com.cn/paste/802y5khw)

---

## 作者：2022linzhiyi (赞：0)

动态规划。设 $f_i$ 表示只考虑前 $i$ 个数的最大答案。

首先，如果第 $i$ 个数不做为美丽子段的末尾，则有 $f_i = f_{i-1}$。

然后，考虑第 $i$ 个数做为美丽子段的末尾的情况。显然，$f$ 数组是单调不降的，所以只需要找出以 $i$ 结尾的最短的美丽子段，将前面的 $f$ 值加上即为当前最大答案。可以先记录前缀和 $sum$ 数组，则这个区间的左端点的左边一个点 $p$ 只需满足 $sum_p=sum_i$ 即可。于是可以用 map 进行离散化，然后用 $pos_i$ 表示 $sum$ 离散化后结果为 $i$ 的最右边的位置，于是 $f_i=f_{pos_{mp_{sum_i}}}+1$，$mp$ 为离散化数组。

最后两种情况的最大值就是 $f_i$ 的结果。

答案即为 $f_n$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,a[N],pos[N],f[N];
map<long long,int> mp;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f=-1;
		ch=getchar();
	}
	while (isdigit(ch)) {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int main() {
	int T=read();
	while (T --) {
		n=read();
		for (int i=1;i<=n;i++) a[i]=read();
		long long sum=0;
		int cnt=1,ans=0;
		mp[1]=0;
		pos[1]=0;
		for (int i=1;i<=n;i++) {
			f[i]=f[i-1];
			sum += a[i];
			if (pos[mp[sum]] > 0 || sum == 0) f[i]=max(f[i],f[pos[mp[sum]]]+1);
			if (!mp[sum]) mp[sum]=++cnt;
			ans=max(ans,f[i]);
			pos[mp[sum]]=i;
		}
		cout << ans << endl;
		memset(f,0,sizeof f);
		mp.clear();
		memset(pos,0,sizeof pos);
	}
	return 0;
}
```

---

## 作者：A_Bit_Cold (赞：0)

一个较简单的题，挺典的思路，采用贪心策略。

发现到，对于一个 beautiful 区间，其右端点 $r$ 越小越好，留给后面的 beautiful 区间。

然后对于区间 $\sum_{i=l}^r a_i=0$ 必有 $\sum_{i=1}^r a_i$ 在之前出现过。用 map 映射 $\sum_{i=1}^r a_i$ 的值即可。

对于每次出现过的值，只需将答案加一，并将 map 重置即可。

注意 $0$ 的出现是要开始就设成 $1$ 的。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,cnt;
long long a[N];
map <long long,int> v;
int main() {
	scanf("%d",&t);
	while(t--) {
		v.clear();
	    scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		v[0]=1; long long s=0ll; cnt=0;
		for(int i=1;i<=n;i++) {
			s+=a[i];
			if(v[s]) cnt++,v.clear(),s=0ll,v[0]=1;
			v[s]=1;
		}
		printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：篮网总冠军 (赞：0)

个人感觉 D 是 C,D,E 中最简单的，但是晚上因为太困睡觉了，就没写 E。这题应该只算个橙。

一道简单的贪心。

我们知道，因为要找更多的满足条件的串，我们必须让上一个串的结尾更往前，才能找到更多的串。

那怎么找串呢？

我们假设 $[l,r]$ 这个区间内有一段数 $[l_1,r]$ 的和为 $0$，那么一定满足 $\sum_{i=l}^{r}a_i = \sum_{i=l}^{l_1-1} a_i$。

那就好做了，只要记录当前值是否出现即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

long long a[100005];
map<long long,bool>mp;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		int cnt=0;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		long long s=0;
		mp[s]=1;
		for(int i=1;i<=n;i++){
			s+=a[i];
			if (mp[s]){
				mp.clear();
				cnt++;
				s=0;
				mp[s]=1;
			}
			else{
				mp[s]=1;
			}
		}
		cout<<cnt<<endl;
		mp.clear();
	}
	return 0;
}
```

最后，祝所有 Oier CSP rp++。

---

## 作者：JOKER_chu (赞：0)

## 题意

从长度为 $n$ 的序列中选出尽可能多的不相交子段，选出的每个子段满足字段和为 $0$。

## 解法

前缀和与 `map` 可以很好的通过，我们先处理出 $sum_i = \sum_{j = 1}^{j \leq i} a_j$。然后对于每个 $sum_i$ 将他放进 `map` 里，枚举一个 $1 \leq i \leq n$ 的 $i$，然后找到上一个数值为 $sum_i$ 的 $sum_j = sum_i$，这时显然 $sum_i - sum_j = 0$，将这个段放进一个向量里，最后做一遍线段覆盖即可。

## 代码

```cpp
#include <bits/stdc++.h>

#include <bits/extc++.h>

#define int long long

using namespace std;

using namespace __gnu_cxx;

using namespace __gnu_pbds;

struct Seg {
  int l, r;
  bool operator < ( const Seg &i ) const {
    return r < i.r;
  }
};

const int N = 2e5 + 5;

int n, a[N];

void solve() {
  cin >> n;
  for (int i = 1; i <= n; cin >> a[i++]) {
  }
  map<int, int> v;
  vector<Seg> s;
  int fix = 0;
  v[0] = 0;
  for (int i = 1; i <= n; ++i) {
    fix += a[i];
    if (v.find(fix) != v.end()) {
      s.push_back({v[fix], i});
    }
    v[fix] = i;
  }
  int ans = 0, res = 0;
  sort (s.begin(), s.end());
  for (auto i : s) {
    if (i.l >= res) {
      ans++;
      res = i.r;
    }
  }
  cout << ans << '\n';
}

signed main() {
  ios :: sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

