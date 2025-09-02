# Zero-Sum Prefixes

## 题目描述

The score of an array $ v_1,v_2,\ldots,v_n $ is defined as the number of indices $ i $ ( $ 1 \le i \le n $ ) such that $ v_1+v_2+\ldots+v_i = 0 $ .

You are given an array $ a_1,a_2,\ldots,a_n $ of length $ n $ . You can perform the following operation multiple times:

- select an index $ i $ ( $ 1 \le i \le n $ ) such that $ a_i=0 $ ;
- then replace $ a_i $ by an arbitrary integer.

What is the maximum possible score of $ a $ that can be obtained by performing a sequence of such operations?

## 说明/提示

In the first test case, it is optimal to change the value of $ a_2 $ to $ -2 $ in one operation.

The resulting array $ a $ will be $ [2,-2,1,-1,0] $ , with a score of $ 3 $ :

- $ a_1+a_2=2-2=0 $ ;
- $ a_1+a_2+a_3+a_4=2-2+1-1=0 $ ;
- $ a_1+a_2+a_3+a_4+a_5=2-2+1-1+0=0 $ .

In the second test case, it is optimal to change the value of $ a_3 $ to $ -2\,000\,000\,000 $ , giving us an array with a score of $ 1 $ .

In the third test case, it is not necessary to perform any operations.

## 样例 #1

### 输入

```
5
5
2 0 1 -1 0
3
1000000000 1000000000 0
4
0 0 0 0
8
3 0 2 -10 10 -30 30 0
9
1 0 0 1 -1 0 1 0 -1```

### 输出

```
3
1
4
4
5```

# 题解

## 作者：Hovery (赞：9)

## Problem

[Zero-Sum Prefixes
](https://www.luogu.com.cn/problem/CF1748C)

## Sol

挺有趣的一道题。

设 $b_i = \sum_{j=1}^{i}{a_j}$。

题目就是要求改变后的 $b$ 数组中的 $0$ 尽可能多。

结论：一个 $0$ 能影响的位置在 $[zero_{now}, zero_{now+1})$ 中。也就是像下面红色的一段。

![](https://cdn.luogu.com.cn/upload/image_hosting/33qy5ydh.png)

证明：若我们使一个 $0$ 的位置加上 $x$，那么下一个 $0$ 的位置可以减去一个 $x$ 再加上一个 $y$，就相当于加上 $y-x$。所以一个 $0$ 能影响的范围就这么点。

一个很贪心的想法，我们想让上图红色段的 $b_i = 0$ 尽可能多，那就考虑这一段 $b_i$ 的众数即可，因为一定有方案让这些众数变为 $0$。

## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int> 
#define pb push_back
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define int long long
using namespace std;

const int mod = 998244353;

void solve()
{
	int n, ans = 0;
	cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		b[i] = a[i];
		b[i] += b[i - 1];
	}
	int i = 1;
	while (a[i] && i <= n) i++;
	for (int _ = 1;_ < i;_++)
	if (!b[_])
	ans++;
	for (;i <= n;)
	{
		int j = i + 1, Max = 1;
		map<int, int> mp;
		while (a[j] && j <= n) j++;
		for (int k = i ;k < j;k++)
		{
			mp[b[k]]++;
			Max = max(Max, mp[b[k]]);
		}
		i = j;
		ans += Max;
	}
	cout << ans << '\n';
}

signed main()
{
	IOS;
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：SpringFullGarden (赞：2)

## 题意

一个长度为 $n$ 的序列 $a$，可以将其中的每个 $0$ 分别改成任意整数。求最多有多少个数的前缀和为 $0$。

## 思路

可以发现，当一个 $0$ 被改变时，会对它及它后面的数的前缀和产生影响，第一个 $0$ 前的数的前缀和无法改变。

贪心的想法，为了使前缀和为 $0$ 的数尽可能多，就需要把它后面出现次数最多的前缀和改变为 $0$。显然的，一个数的前缀和可以被这个数之前所有的 $0$ 改变，所以只需要考虑在下一个 $0$ 出现前的数的前缀和的次数。特别的，最后一个 $0$ 需要考虑后面所有数的前缀和。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ui unsigned
#define ull unsigned long long
using namespace std;

ll rd() {
	char ch = getchar(); ll x = 0, f = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}

map <ll, ll> b;
ll a[200005], d[200005], s[200005];

int main() {
//	freopen("zero.in", "r", stdin);
//	freopen("zero.out", "w", stdout);
	for(ll _ = rd(); _--;) {
		ll n = rd(), ans = 0, top = 0;
		s[1] = n + 1; 
		for(ll i = 1; i <= n; i++) {
			a[i] = rd(), d[i] = d[i - 1] + a[i];
			if(!a[i]) s[++top] = i;
		}
		for(ll i = 1; i < s[1]; i++) 
			if(!d[i]) ans++;
		s[top + 1] = n + 1;
		for(ll i = 1; i <= top; i++) {
			b.clear();
			ll mx = -1e18;
			for(ll j = s[i]; j < s[i + 1]; j++) 
				++b[d[j]], mx = max(mx, b[d[j]]);
			ans += mx;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Leasier (赞：2)

Update on 2022.11.14：感谢 @[Duawieh](https://www.luogu.com.cn/user/445135)。

不会贪心，于是考虑 dp。

设 $dp_i$ 表示钦定以某个位置 $i$ 结尾的某个连续段和为 $0$ 时前面一共最多有多少个前缀和为 $0$。

现在考虑钦定当前和为 $0$ 的连续段的开头，分为以下两种情况：

- 前面某个 $[j, i]$ 之间有 $0$

则我们可以通过改变任意一个 $0$ 获得一个新的和为 $0$ 的连续段，此时我们令 $dp_i \leftarrow \max(dp_i, dp_j + 1)$。

- 前面某个 $[j, i]$ 的区间和本来就是 $0$

则它本来就是一个和为 $0$ 的连续段，此时我们令 $dp_i \leftarrow \max(dp_i, dp_j + 1)$。

用前缀 $\max$ 和一个 map 维护上述转移即可。答案为 $\max(\displaystyle\max_{i = 1}^n dp_i, 0)$。

时间复杂度为 $O(\sum n \log n)$。

代码：
```cpp
#include <iostream>
#include <map>

using namespace std;

typedef long long ll;

int a[200007], lst[200007], max_val[200007], dp[200007];
ll sum[200007];
map<ll, int> mp;

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n, ans = 0;
		cin >> n;
		mp.clear();
		for (int j = 1; j <= n; j++){
			cin >> a[j];
			sum[j] = sum[j - 1] + a[j];
		}
		for (int j = 1, k = 0; j <= n; j++){
			if (a[j] == 0) k = j;
			lst[j] = k;
		}
		mp[0] = 0;
		for (int j = 1; j <= n; j++){
			dp[j] = 0x80000000;
			if (lst[j] > 0) dp[j] = max_val[lst[j] - 1];
			if (mp.count(sum[j])) dp[j] = max(dp[j], mp[sum[j]]);
			dp[j]++;
			max_val[j] = max(max_val[j - 1], dp[j]);
			ans = max(ans, dp[j]);
			if (!mp.count(sum[j])){
				mp[sum[j]] = dp[j];
			} else {
				mp[sum[j]] = max(mp[sum[j]], dp[j]);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Nuclear_Fish_cyq (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1748C)

[CF 原题传送门](https://codeforces.com/problemset/problem/1748/C)

[提交记录](https://www.luogu.com.cn/record/127614012)

## 题意简述

有一个长度为 $n$ 的序列 $a$，你可以把 $a$ 中的任意 $0$ 改为任意整数，设 $S_i=\sum_{k=0}^ia_i$，求 $S$ 里面最多能有多少个 $0$。

## 做法

不难发现如果我们把 $a$ 中的任意一个 $0$ 修改成其他数的话，会改变它后面的所有 $S_i$。看起来我们只能 $O(n^2)$ 暴力枚举，但是其实不需要。我们发现，修改一个 $0$ 所产生的影响可以通过后面的修改来消除，换句话说，一个 $0$ 真正能影响的只有从它（包含）到下一个 $0$（不包含） 这个区间上的所有 $S_i$。那么，我们可以直接求每一个 $0$（包含）到下一个 $0$（如果有，不包含）的区间里出现次数最大的数的出现次数，那么这个问题就解决了。由于所有这些区间的长度和不超过 $n$，这个做法是 $O(n)$（实际上这个时间复杂度并不是我代码的时间复杂度，等下讲）的。

但是还有一个小问题没有处理：$-10^9\leq a_i\leq-10^9$，怎么求出现次数最大的数的出现次数？map 大法好。但是由于 map 是 $O(\log n)$ 的，所以实际上整个代码的时间复杂度是 $O(n\log n)$ 的。

然后就是一些小细节了。如果你一直 WA#2 的话，可以看眼下面这组 hack 数据：

```
1
3
2 -2 0
```

正确代码会输出 `2`，而错误的一般会输出 `1`。为什么呢？因为有的时候即使你无法专门对于序列的 $0$ 出现前的一段进行操作，序列的那一段对应的 $S$ 也可能可以自然出现 $0$。对于这件事，解决方案就是特判。由于我是对序列进行倒序遍历来算次数最大的数的出现次数的，所以只需要在答案输出的时候额外加上就可以了。

最后还有两个小细节：首先，这道题是多组测试点，数据要清空干净。其次，这道题的前缀和数组可能会爆 $2^{31}-1$。

上代码。码风可能比较奇怪，请不要在意。

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t, n, a[200000], s[200000], ans, maxn, summ;
map<ll, ll> cnt;
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	for(int kk = 0; kk < t; kk++){
		cin >> n;
		ans = 0;
		cnt.clear();
		maxn = 0;
		for(int i = 0; i < n; i++){
			cin >> a[i];
			s[i] = (i == 0 ? 0 : s[i - 1]) + a[i];//求前缀和
		}
		for(int i = n - 1; i >= 0; i--){
			cnt[s[i]]++;
			maxn = max(maxn, cnt[s[i]]);//更新当前区间同一个数出现次数最大值
			if(a[i] == 0){//当前区间结束
				ans += maxn;
				maxn = 0;
				cnt.clear();
			}
		}
		cout << ans + cnt[0] << endl;//一定要特判！
	}
	return 0;
}

```

---

## 作者：yingkeqian9217 (赞：1)

把序列依照 $0$ 的位置分段考虑，不妨将第 $i$ 个 $0$ 的位置设为 $z_i$：

1. $id\in[1,z_1)$，因为不可能修改，所以直接记录前缀和为 $0$ 的个数即可。

2. $id\in[z_i,z_{i+1})$，（$i\ge1$），可以修改，由且仅由 $a_{z_i}$ 修改的值决定前缀和。

在实际操作时，我们可以多建一个虚位 $a_{n+1}=0$ 来避免最后一个区间漏算。 

而如何修改，才能使为零的最多呢？

不难发现，在一个区间内的前缀之间差不变，也就是说，每一种数值的相对数量是不变的，所以 $0$ 取到最多，就是找到所谓的“众数”。

我们可以用 ```map``` 来维护前缀值，区间如果是第一种情况同样可以解决，特判即可。

## Code:

~~~cpp
#include <bits/stdc++.h>
#define maxn 2900001
#define int long long//不开long long见祖宗
using namespace std;
int T, n, id, ans, a[maxn], s[maxn];
map<int, int>mp;
signed main() {
    scanf("%lld", &T); //scanf注意lld

    while (T--) {
        id = ans = 0; //id记录上一次0的位置
        mp.clear();//注意清空
        scanf("%lld", &n);
        a[n + 1] = 0;

        for (int i = 1; i <= n + 1; i++) {
            if (i <= n)
                scanf("%lld", &a[i]); //读入时记得判断

            if (!a[i]) {
                if (!id) { //特判第一种情况
                    s[i - 1] = 0;
                    ans += mp[0];
                    mp.clear();
                    id = i;
                    goto csq;//goto比较方便,分开写也可以
                }

                int maxx = 0;

                while (id < i) {
                    maxx = max(maxx, mp[s[id]]); //统计前缀和的map
                    id++;//位置加到当前点
                }

                ans += maxx; //累加
                s[i - 1] = 0;
                mp.clear();
            }

            csq:s[i] = s[i - 1] + a[i];
            mp[s[i]]++;//维护前缀和map
        }

        printf("%lld\n", ans);
    }

    return 0;
}
~~~

---

## 作者：WaterSun (赞：1)

UPD 23.10.3 更新的对思路的描述，以及代码。

# 思路

对于每一个 $a_i = 0$，如果我们将它变为 $x$，都可以直接将 $i \sim n$ 位置上的前缀和加 $x$。

设 $a_j$ 是 $a_i$ 后第一个 $0$，那么，在 $j$ 时同样有上述规律。

所以，我们只需在 $i$ 时考虑，$i \sim (j - 1)$ 的贡献。 

因为我们想尽可能的使 $s_x = 0$ 的数量更多，所以我们就要让 $a_i$ 修改为在 $i \sim (j - 1)$ 中 $s_k$ 出现次数最多的元素的相反数。

特别的，如果 $i$ 后没有任意一个位置 $j$ 为 $0$，那么，考虑 $i \sim n$ 即可。（直接加一个 $n + 1$ 的哨兵即可）

因为 $i$ 的修改对 $1 \sim (i - 1)$ 的前缀和无关，所以只需枚举 $i \sim (j - 1)$ 的位置，保证了更新的位置总和是 $\Theta(n)$，然后还需要用一个 `map` 维护前缀和的出现次数。

综上，时间复杂度为 $\Theta(n \log n)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define ll long long

using namespace std;

const int N = 2e5 + 10;
int T,n;
int arr[N];
ll s[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	T = read();
	while (T--){
		int ans = 0,len = 0;
		vector<int> v;
		n = read();
		for (re int i = 1;i <= n;i++) arr[i] = s[i] = 0;
		for (re int i = 1;i <= n;i++){
			arr[i] = read();
			s[i] = s[i - 1] + arr[i];
			if (!arr[i]){
				len++;
				v.push_back(i);
			}
		}
		v.push_back(n + 1);
		for (re int i = 1;i < v.front();i++){
			if (!s[i]) ans++;
		}
		for (re int x = 0;x < len;x++){
			unordered_map<ll,int> vis;
			int Max = 0;
			for (re int i = v[x];i < v[x + 1];i++){
				vis[s[i]]++;
				Max = max(Max,vis[s[i]]);
			}
			ans += Max;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：VinstaG173 (赞：1)

贪心。记 $s_k=a_1+\dots+a_k$。

设 $a_i,a_j$ 是两个相邻的 $0$（我们认为 $a_{n+1}=0$，这样数列中最后一个 $0$ 与 $a_{n+1}$ 相邻），那么 $s_i,s_{i+1},\dots,s_{j-1}$ 之间的差值不会改变，因此最终 $s_i,s_{i+1},\dots,s_{j-1}$ 中取到 $0$ 的原来的值必然相等。而且可以通过更改 $a_i$ 来使得 $s_i$ 取到任意值，因此对任意满足 $i\le t_1<t_2<\dots<t_p<j$ 且 $s_{t_1}=s_{t_2}=\dots=s_{t_p}$ 的数组 $t_1,t_2,\dots,t_p$，均可以适当地取 $a_i$ 使得修改后 $s_{t_1}=s_{t_2}=\dots=s_{t_p}=0$。故得到贪心策略：让 $s_i,s_{i+1},\dots,s_{j-1}$ 中出现次数最多的相等值变成 $0$。用 `map` 存储其中存在的值及出现次数即可做到 $O(n\log n)$。

最后还要加上第一个 $0$ 之前满足 $s_i=0$ 的 $i$ 的个数。但是也许没有人会和我一样傻到因此吃两发罚时。~~还有一发罚时是因为把数组开成了 1e5~~

Code:
```cpp
int n;ll a[200003];
int zr[200003],cnt;
map<ll,int>tms;
int mxn,res;
inline void solve(){rd(n);cnt=res=0;
	for(rg int i=1;i<=n;++i){
		if(!rd(a[i])){
			zr[++cnt]=i;
		}a[i]+=a[i-1];
	}zr[++cnt]=n+1;
	for(rg int i=1;i<zr[1];++i){
		if(a[i]==0)++res;
	}for(rg int i=1;i<cnt;++i){
		tms.clear();mxn=0;
		map<ll,int>::iterator it;
		for(rg int j=zr[i];j<zr[i+1];++j){
			if(!tms.count(a[j]))tms[a[j]]=1;
			else ++tms[a[j]];
		}for(it=tms.begin();it!=tms.end();++it){
			if(it->second>mxn)mxn=it->second;
		}res+=mxn;
	}printf("%d\n",res);
}
```

---

## 作者：Duawieh (赞：1)

**广告：推一手[博客](https://www.luogu.com.cn/blog/Duawieh/#)先~**

---

首先考虑，将所有满足 $a_i=0$ 的 $i$ 提出来，构成序列 $B$，设 $B$ 的长度为 $k$。不难得到如下事实：

- 对于 $\forall i\in B$，其在序列 $a$ 中可影响的范围仅限于 $[i,n]$
- 对于 $\forall i\in B$，由于我们可以对 $a_i$ 随意进行赋值，所以 $a_i$ 之前的序列所产生的任何影响都能够在 $a_i$ 之后被消除

于是我们高兴地发现，对于$\forall i\in[2,k-1]$，$a$ 的子区间 $a_{[B_i,\ B_{i+1}]}$ 的答案，总是由 $a_{B_i}$ 决定而不受 $a_{B_{i-1}}$ 或 $a_{B_{i+1}}$ 的影响。那么单独处理每个这样的子区间并将答案相加即可。注意单独处理子区间 $a_{[1,\ B_1]}$ 和 $a_{[B_k,\ n]}$。

接下来考虑如何求出每个子区间的贡献。令 $S_n=\sum_{i=1}^na_i$，不难发现，当我们把一个特定位置 $a_x$ 修改为 $a_x+y$ 时，所有的 $S_i,i\in[x,n]$ 都会变为 $S_i+y\ $。  
对于一个区间 $[l,r]$，满足 $a_l=0 \ \cap\ a_i\neq0,i\in(l,r]$，钦定 $K=S_x$, $S_x$ 为 $S_{[l,r]}$ 中重复出现次数最多的元素，那么该区间的最大贡献即为 $K$ 在 $S_{[l,r]}$ 中重复出现的次数，因为我们可以令 $a_l=-K$ 来将它们全部归零。

所以先预处理一个前缀和数组 $S$，然后直接统计各个区间内出现次数最多的 $S_i$ 各出现了多少次，求和即可。

---

一个玄学坑：不知道为什么`map`可以通过，但`multiset`会超时。

```cpp
#include<bits/stdc++.h>
using  namespace std;
//Zero-Sum Prefixes

const int maxn = (int)2e5 + 8;
long long s[maxn];
int a[maxn];
int T, n;

int main() {
    scanf("%d", &T);
    while (T--) {
        int ans = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
        for (int i = 1; i <= n; i++) {
            if (a[i] == 0) {
                map<long long, int> _m;
                _m.insert(make_pair(s[i], 1));
                int max_cnt = 1;
                int j = i + 1;
                for (; j <= n && a[j]; j++) 
                    max_cnt = max(max_cnt, ++_m[s[j]]);
                ans += max_cnt;
                i = j - 1;
                continue;
            }
            if (s[i] == 0) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：highkj (赞：0)

# 思路
我们可以发现一个 $0$ 会对其之后到下一个 $0$ 的前缀和进行限制，那么我们就可以将这个数组来分段处理我们可以先将第一个 $0$ 之前的答案类加上，然后我们对于第 $i$ 个 $0$ 到第 $i+1$ 个 $0$ 之间的前缀和统计出一个出现次数最多的，那么我们便可以得到这么多次数个前缀和为 $0$ 及将答案加上次数个，然后再对于每一个区间都做这样的操作即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define fi first
#define se second
#define lcm(x,y) x*y/__gcd(x,y)
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int t;
int n,a[200100],s[200100];
map<int,int>mp;
int Max[200100];
int v;
fire main() {
	in(t);
	w(t) {
		in(n);
		v=n+1;
		rep(i,1,n) in(a[i]),s[i]=s[i-1]+a[i];
		rep(i,1,n) {
			if(a[i]==false) {
				v=i;
				break;
			}
		}
		int res=false;
		rep(i,1,v-1) if(!s[i]) res++;
		rep(i,1,n) Max[i]=false;
		mp.clear();
		rep(i,v,n) {
			if(a[i]==false) {
				res+=Max[i-1];
				mp.clear();
				Max[i-1]=false;
			}
			mp[s[i]]++;
			Max[i]=max(Max[i-1],mp[s[i]]);
		}
		print(res+Max[n]);
		end;
	}
	return false;
}

```

---

## 作者：Hedgehog_210508 (赞：0)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1748C)

**思路**：显然，两个零之间，前缀和的相对大小不变，即前面的操作不影响这一段任意两个前缀和的差。而对于一个 $0$，它只涉及到到下一个 $0$ 为止的数（后面一段可以通过 $0$ 再变回来），为了使 $0$ 尽可能多，那么就可以记录这一段前缀和相同最多的有几个，将他们变成 $0$。使用一个 map 记录解决即可。

**代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		ll n,a[200009],p[200009],m=0,k[200009],ans=0;
		p[0]=0;
		cin>>n;
		for(ll i=1;i<=n;i++){
			k[i]=0;
			cin>>a[i];
			p[i]=p[i-1]+a[i];
			if(a[i]==0) k[++m]=i;
		}
		k[m+1]=n+1;
		for(ll i=1;i<k[1];i++) if(p[i]==0) ans++;
		map<ll,ll> s;
		map<ll,ll>::iterator it;
		for(ll i=1;i<=m;i++){
			ll tmp=0;
			s.clear();
			for(ll j=k[i];j<k[i+1];j++){
				s[p[j]]++;
			}
			for(it=s.begin();it!=s.end();it++) tmp=max(tmp,it->second);
			ans+=tmp;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1600}$
---
### 解题思路：

首先考虑只有一个 $0$ 的情况，容易发现在这种情况下，在这个 $0$ 的前面的所有位置都无法被影响，而将 $0$ 更改为 $x$ 会导致后面的所有的位置的前缀和都加上 $x$。那么此时的做法一定就是统计出包括可以被更改的 $0$ 在内的后面的所有位置的前缀和，然后在其中选出一个出现次数最多的前缀和 $u$，并将 $0$ 更改成 $-u$。

拓展到一般情况，容易发现对于一个 $0$ 的更改虽然会影响得到后面的所有位置的前缀和，但是对于下一个 $0$ 而言，前面位置造成的影响不会影响后面的变化量，所以一定可以通过后面的更改抵消前面位置的影响。

由此就从后往前依次考虑每一个 $0$，统计当前位置（包括）到下一个 $0$（不包括）之间的前缀和，选出其中出现次数的一个加入答案即可。


---
### 代码：
```cpp
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
#define int long long
int T,n,a[200005],sum[200005],ans,cnt;
map<int,int>mp;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			sum[i]=sum[i-1]+a[i];
		}
		mp.clear();cnt=0;ans=0;
		for(int i=n;i>=1;i--){
			mp[sum[i]]++;
			cnt=max(cnt,mp[sum[i]]);
			if(a[i]==0){
				ans+=cnt;
				cnt=0;
				mp.clear();
			}
		}
		ans+=mp[0];
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Dry_ice (赞：0)

[更好的阅读体验](https://www.cnblogs.com/dry-ice/p/cf1748c.html)

题链：[cf](https://codeforces.com/contest/1748/problem/C) [luogu](https://www.luogu.com.cn/problem/CF1748C)

> 有意思的统计题。

## Description
给你一个长度为 $n$ 的整数序列 $A$，你可以将其中的 $0$ 替换为任意的 $x(x\in\mathbb{Z})$。

问经**替换后**最多有多少个 $i$ 满足 $\sum^{i}_{j=1}a_j=0$。

## Analysis
考虑每一个 $0$ 可以控制到下一个 $0$ 之间的前缀和 $=0$ 数。这点容易想到，于是发现**分段**处理。

对每两个 $0$ 之间的位置求前缀和众数（可以使用 ```Hash``` 或 ```std:: map```），设众数为 $x$，则前面的 $0$ 可以替换为 $-x$ 以得最优解。

注意：第一个 $0$ 前的原始为 $0$ 的前缀和不要漏统。

## Code
```cpp
#include <stdio.h>
#include <map>
#define int long long
const int N = (int)2e5 + 5;
int n, a[N], s[N];
inline void Solve() {
	scanf("%lld", &n); s[0] = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	int ans = 0, st;
	for (st = 1; st <= n && a[st]; ++st)
		if (!s[st]) ++ans;
	for (int i = st, j; i <= n; i = j) {
		std:: map<int, int> cnt; int now = 1;
		for (j = i + 1; j <= n && a[j]; ++j);
		for (int k = i; k < j; ++k) {
			++cnt[s[k]];
			if (cnt[s[k]] > now) now = cnt[s[k]];
		}
		ans += now;
	}
	printf("%lld\n", ans);
}
signed main(void) {
	int T; for (scanf("%lld", &T); T--; ) Solve();
	return 0;
}
```


## Postscript

至今不知道为什么写成 ```unordered_map``` 会超时，

但写成 ```map``` 肯定能过。

~~不说再见~~

---

## 作者：Rosent (赞：0)

[题目Link](https://www.luogu.com.cn/problem/CF1748C)

注意到数据范围 $1\le n \le 2\times10^5$，容易想到使用贪心法求解。

题目要求求 $a_{1}+a_{2}+⋯+a_{k}=0$ 的个数，容易想到使用前缀和 `s[i]=s[i-1]+a[i]` 维护序列和。

设第 $i$ 个 $0$ 出现的位置为 $x_{i}$。

观察数据，可以将序列分为两部分：

1. 在 $x_{1}$ 之前，无论如何皆无法改变序列的和，此部分符合题目要求的个数即为 $\sum_{i=1}^{x-1} [s_{i}=0]$。

2. 在 $x_{i}$ 与 $x_{i+1}$ 之间，每个数字 $0$ 都可以使其本身与下一个 $0$ 之间的数字加（减）上一个数字。

我们成功将问题转化为如何在 $s_{i}$ 和 $s_{j}$ 之间将修改最大化。

不难看出，由于一个 $0$ 仅可以修改一次，当修改的是 $s_{i}$ 与 $s_{j}$ 之间的众数时，修改最大化，可用贪心解决。可用 `map<int,int>` 维护众数。

温馨提示：多测千万条，清空第一条。

另附完整代码。
```cpp
#include <bits/stdc++.h>
#define int long long//不开ll见祖宗
using namespace std;
const int N=200010;
int a[N],s[N];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,cnt=0;
		cin>>n;
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			s[i]=a[i]+s[i-1];
		}
		for(int i=1;i<=n;i++)
		{
			if(a[i]==0) break;
			if(s[i]==0) cnt++;
		 } 
		for(int i=1;i<=n;i++)
		{	
			if(a[i]==0)
			{
				map <int,int> m;
				int maxx=-1,j;
				for(j=i;a[j]!=0||j==i;j++)
				{
					m[s[j]]++;
					maxx=max(maxx,m[s[j]]);
				}
				i=j-1;
				cnt+=maxx;
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
 } 
 ```
 

---

