# The BOSS Can Count Pairs

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

Your task is to count the number of pairs of integers $ (i,j) $ such that $ 1 \leq i < j \leq n $ and $ a_i \cdot a_j = b_i+b_j $ .

## 说明/提示

In the first sample, there are $ 2 $ good pairs:

- $ (1,2) $ ,
- $ (1,3) $ .

In the second sample, there are $ 7 $ good pairs:

- $ (1,2) $ ,
- $ (1,5) $ ,
- $ (2,8) $ ,
- $ (3,4) $ ,
- $ (4,7) $ ,
- $ (5,6) $ ,
- $ (5,7) $ .

## 样例 #1

### 输入

```
3
3
2 3 2
3 3 1
8
4 2 8 2 1 2 7 5
3 5 8 8 1 1 6 5
8
4 4 8 8 8 8 8 8
8 8 8 8 8 8 8 8```

### 输出

```
2
7
1```

# 题解

## 作者：Xy_top (赞：11)

一道简单题，这个弱弱不知道为什么考场上没想到分块，写了个类似启发式合并的做法？

这道题的突破口其实很好找，我们发现 $b_i+b_j$ 的最大值也就是 $2n$ 了，$a_i\times a_j$ 如果想要被统计入答案，不能超过 $2\times n$。

如果两数相乘等于 $x$，那么两个数中一定有一个小于等于 $\sqrt{x}$，这个结论显然成立。所以挑小的 $a_i$ 枚举值就行了。

首先遍历所有 $a$，如果它等于当前枚举的值 $k$，把 $b_i$ 弄到桶里去。

接着就要统计答案了，别忘记统计相同 $a$ 的答案啊。

如果当前的 $a_i$ 等于枚举的值 $k$，发现 $k \times k - b_i$ 就是需要的 $b_j$ 的值，我们不是预处理了一个桶了吗？于是这种情况就结束了。

再来看不同的 $a$ 相乘贡献的答案。

我们用变量 $i$ 依次遍历 $a$，如果它的值比 $k$ 大，才会被 $k$ 相乘并统计答案。（因为我们枚举较小的 $a$ 统计答案）

枚举另一个 $a$ 的同时，我们也就知道对应的 $b$ 值了吧，所以我们现在已知的是：$a_j$ 的值，$a_i$，$b_i$。

虽然不知道 $a_j$ 所对应的 $b_j$，但是可以反推出 $b_j$ 的值等于 $a_i \times k-b_i$。

然而，并不是所有等于这个值的都要被记录答案，$b$ 所对应的 $a$ 值必须是当前枚举的 $k$，之前预处理的桶不就派上用场了吗？

如果不压行，这个大概就是极限代码了吧：

```cpp
#include <cmath>
#include <iostream>
using namespace std;
int n, t;
int a[200005], b[200005];
int bin[200005];
signed main() {
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		for (int i = 1; i <= n; i ++) cin >> b[i];
		int c = sqrt (n * 2);
		long long res = 0;
		for (int j = 1; j <= c + 1; j ++) {
			for (int i = 1; i <= n; i ++) bin[i] = 0;
			for (int i = 1; i <= n; i ++) if (a[i] == j) {
				if (j * j - b[i] > 0 && j * j - b[i] <= n) res += bin[j * j - b[i] ];
				bin[b[i] ] ++;
			}
			for (int i = 1; i <= n; i ++) if (a[i] > j && a[i] * j - b[i] >= 1 && a[i] * j - b[i] <= n)
				res += bin[a[i] * j - b[i] ];
		}
		cout << res << "\n";
	}
	return 0;
}
```


---

## 作者：Reunite (赞：2)

## 一
---
- 看到这种有序对统计的题，首先观察数据范围。注意到 $a_i$ 与 $b_i$ 的值域都是 $n$。不妨设 $a_i\ge a_j$，有 $a_j^2 \leq a_i \cdot a_j \leq 2 \cdot n$，也即 $a_j \leq \sqrt{2\cdot n}$。这是一个很好的性质。

- 看到根号，我们直接考虑分块思想的算法。考虑转化问题，我们枚举并钦定 $a_j$ 的值，这样的复杂度是 $O(\sqrt{n})$ 的，完全可以接受，现在我们还能接受一次 $O(n)$ 复杂度的扫描，那么我们怎么根据枚举的 $a_j$ 来快速算出以 $a_j$ 为较小值的答案呢？

- 直接把整个数组从 $1$ 到 $n$ 枚举一遍，记此时枚举到了 $i$ 位置。这时候，我们已知了 $a_i,a_j,b_i$，可以直接算出 $b_j$ 应该的值，只需快速知道这样的 $j$ 有多少个即可。注意要跳过 $a_i \leq  a_j$ 的点，这样才不会重复。

## 二
---
算法流程：

- 开一个桶，大小为 $n\sqrt{2\cdot n}$。表示 $a_j$ 的值为 $x$，$b_j$ 的值为 $y$ 的 $(x,y)$ 个数。

- 枚举每一个 $j$，扫描整个数组，计算出此时 $b_j$ 应有的值，然后把答案加上桶中 $j,b_j$ 的个数即可。

- 总时间复杂度为 $O(n \sqrt{n})$，空间复杂度为 $O(n \sqrt{n})$。
实现的时候要注意下标越界等问题，不然会挂（赛时惨痛的经历）。还有一点要注意一下，对于 $a_i=a_j$ 的情况要特殊处理一下，一定要注意不重不漏。

## 三
---
- code：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;

int t,n;
int a[200005];
int b[200005];
int mp[635][200005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int main(){
	in(t);
	while(t--){
		in(n);
		int bl=(int)sqrt(2*n)+1;
		for(int i=0;i<=bl;i++)
			for(int j=0;j<=n;j++) mp[i][j]=0;
		for(int i=1;i<=n;i++) in(a[i]);
		for(int i=1;i<=n;i++) in(b[i]);
		for(int i=1;i<=n;i++)
			if(a[i]<=bl) mp[a[i]][b[i]]++;
		ll ans=0;
		for(int j=1;j<=bl;j++){
			for(int i=1;i<=n;i++){
				if(a[i]<=j) continue;
				int d=a[i]*j-b[i];
				if(d>0&&d<=n) ans+=mp[j][d];
			}
			if(j%2==0){
				for(int i=1;i<j*j/2;i++)
					if(i<=n&&j*j-i<=n) 
						ans+=1ll*mp[j][i]*mp[j][j*j-i];
				if(j*j/2<=n){
					int x=mp[j][j*j/2];
					ans+=1ll*x*(x-1)/2;
				}
			}
			else{
				for(int i=1;i<=j*j/2;i++)
					if(i<=n&&j*j-i<=n) 
						ans+=1ll*mp[j][i]*mp[j][j*j-i];
			}
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
```


---

## 作者：伊地知虹夏 (赞：2)

考虑 $b_i + b_j \in [2,2n]$，所以肯定有一个数小于等于 $\sqrt{2n}$，考虑枚举它。

设当前枚举到的是 $k$。枚举下标 $i$ 满足 $a_i > j$，那么 $b_j = a_i \times k - b_i$，用桶统计。

在将 $a_i = k$ 的数放进桶内时，先加上满足 $b_j = k^2 - b_i$ 的 $j$ 的贡献即可。

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int n,a[N],b[N],c[N];
void Calc(){
	cin >> n;
	for(int i = 1;i <= n;i ++)
		cin >> a[i];
	for(int i = 1;i <= n;i ++)
		cin >> b[i];
	ll ans = 0;
	int T = sqrt(2*n);
	for(int i = 1;i <= T;i ++){
		fill(c+1,c+1+n,0);
		for(int j = 1;j <= n;j ++) if(a[j] == i){
			int B = i * i - b[j];
			if(B >= 1 && B <= n) ans += c[B];
			c[b[j]] ++;
		}
		for(int j = 1;j <= n;j ++){
			int B = a[j] * i - b[j];
			if(B >= 1 && B <= n && a[j] > i) 
				ans += c[B];
		}
	}
	cout << ans << '\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin >> t;
	while(t --) Calc();
}
```

---

## 作者：苏联小渣 (赞：2)

考虑题目给的式子的性质，首先若 $xy=c$，则 $\min(x,y) \le \sqrt{c}$。

那么有 $\min(a_i,a_j) \le \sqrt{b_i+b_j} \le \sqrt{2n}$。

也就是说，我们可以把枚举 $i,j$ 两个下标，变成一个枚举下标、一个枚举值。

那么我们记 $f_{i,j}$ 表示**当前**满足 $b_x=i,a_x=j$ 的 $x$ 的个数。

首先从前往后扫，对于每个下标 $x$，我们枚举 $j \in [1,\sqrt{2n}]$，令 $a_y=j$，可以倒推出 $b_y=a_x \cdot a_y-b_x$，将 $f_{b_y,a_y}$ 计入答案。注意判掉不合法。

然后，对于所有满足 $a_x \le \sqrt{2n}$ 的 $x$，将 $f_{b_x,a_x} \gets f_{b_x,a_x}+1$。这样，就处理了 $a_i \le \sqrt{2n}$，$a_j \le \sqrt{2n}$ 和 $a_i \le \sqrt{2n}$，$a_j > \sqrt{2n}$ 的情况。

还有一种 $a_i>\sqrt{2n}$，$a_j \le \sqrt{2n}$ 的情况，从后往前扫就行了。

时空复杂度均为 $O(n \sqrt{n})$，事实上是 $O(n\sqrt{2n})$。有一种压空间的方法，是外层枚举 $a_x \in [1,\sqrt{2n}]$，这样空间是线性的。不过我根号空间也卡着线过了。

---

## 作者：WaterSun (赞：1)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]CF1830B%20The%20BOSS%20Can%20Count%20Pairs)

# 思路

观察到 $a_i,b_i \leq n$，又要求 $a_i \times a_j = b_i + b_j$ 的数量，那么显然有 $a_i \times a_j = b_i + b_j \leq 2n$。

并且显然有 $a_i$ 和 $a_j$ 其中一个一定小于 $\sqrt{2n}$。不妨枚举 $i$ 和 $a_j$ 的值 $x$，那么 $b_j$ 可以被表示为 $a_i \times x - b_i$。

于是我们可以直接开一个桶记录满足 $a_j = x$ 的 $b_j$。其次为了避免计算重复，应当对 $a,b$ 整体进行排序。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register
#define int long long

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10;
int n,vis[N];
pii arr[N];

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
    int ans = 0;
    n = read();
    for (re int i = 1;i <= n;i++) arr[i].fst = read();
    for (re int i = 1;i <= n;i++) arr[i].snd = read();
    sort(arr + 1,arr + n + 1);
    for (re int x = 1;x * x <= 2 * n;x++){
        vector<int> del;
        for (re int i = 1;i <= n;i++){
            int y = x * arr[i].fst - arr[i].snd;
            if (1 <= y && y <= n) ans += vis[y];
            if (arr[i].fst == x){
                del.push_back(arr[i].snd);
                vis[arr[i].snd]++;
            }
        }
        for (int p:del) vis[p]--;
    }
    printf("%lld\n",ans);
}

signed main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Zimo_666 (赞：0)

## D. The BOSS Can Count Pairs

我们考虑类似 $a_i\times a_j$ 的大小样子。

先排序。

显然 $a_i \times a_j = b_i \times b_j \le 2n$。

那么我们可以考虑枚举 $i$，枚举 $x$ 作为 $a_j$ ，然后顺便把贡献加进数组内方便统计。

即统计：小于当前下标 $i$（避免重复统计）的数据中，对应的合法的个数有多少。

复杂度 $O(n \sqrt{2n})$。

[Code](https://codeforces.com/contest/1831/submission/224291752)

---

## 作者：Jeefy (赞：0)

每组数据给你一个 $n$ 和两个序列 $a,b$。

求有多少个数对 $(i,j)$ 满足 $1 \le i < j \le n$ 且 $a_i \times a_j = b_i + b_j$

对于每一个 $i$ 看作用 $a_i \times x - b_i = y$ 这条线来切所有的点。

注意到当 $a_i$ 很大的时候的简单的，我们只需要用一个桶记录一下 $(x, y)$ 的个数即可，然后可以 $O(\frac n {a_i})$ 求出。

此时设一个阈值 $B$，当 $a_i \gt B$ 的时候认为是很大的，所以上面的复杂度可以看作 $O(\frac n B)$。

问题在于当 $a_i$ 很小的时候，注意到其实可以 $O(B)$ 预处理出 $\forall k \in [1, B]$ $k \times a_i - b_i$ 的值。

这样就可以 $O(1)$ 查询了。

两者稍微平衡一下，令 $B = \sqrt {2n}$ 于是可以 $O(n \sqrt {n})$ 解决本题。

代码链接： <https://codeforces.com/contest/1830/submission/222008847>

---

## 作者：hfjh (赞：0)

# CF1830B The BOSS Can Count Pairs
## 题意

每组数据给你一个 $n$ 和两个序列 $a,b$。

求有多少个数对 $(i,j)$ 满足 $1 \le i < j \le n$ 且 $a_i \times a_j = b_i + b_j$。

## 题解

考虑 $a_i\times a_j = b_i + b_j$，那么 $a_i \times a_j \le 2n \to \min(a_i, a_j) \le \sqrt {2n}$。
 
枚举 $x$ 表示两个 $a$ 中小的那个，从 $1 \to \sqrt {2n}$。

把所有满足 $a_i = x$ 的 $b_i$ 放在桶里，然后在桶里找 $a_i \times x - b_i$ 个数。

复杂度 $O(n\sqrt n)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10; 
int t, n, w;
int a[N], b[N], cnt[N]; 
long long ans = 0;
void input(){
	cin>> n;
	for(int i = 1; i <= n; ++i) cin>> a[i];
	for(int i = 1; i <= n; ++i) cin>> b[i];
	w = sqrt(2 * n);
}
bool ch(int x){
	return (x >= 1) && (x <= n);
}
void op(){
	for(int x = 1; x <= w; ++x){
		for(int i = 1; i <= n; ++i) cnt[i] = 0;
		for(int i = 1; i <= n; ++i){
			if(a[i] == x){
				if(ch(x * x - b[i]))ans += cnt[x * x - b[i]];
				++cnt[b[i]];
			}
		}
		for(int i = 1; i <= n; ++i){
			if(a[i] > x){
				if(ch(x * a[i] - b[i])){
					ans += cnt[x * a[i] - b[i]];
				}
			}
		}
	}
}
void qk(){
	
	ans = 0;
}
int main(){
	cin>>t;
	while(t--){
		input();
		op();
		cout<<ans<<'\n';
		qk();
	}
} 
```

---

## 作者：chroneZ (赞：0)

首先发现任意合法的 $(i, j)$ 都应满足 $a_i \times a_j \leq 2n$，显然 $\min(a_i, a_j) \leq \sqrt{2n}$。这启发我们从值域入手。

考虑枚举 $(i, j)$ 中的位置 $j$，与此同时枚举 $x \in [1, \sqrt{2n}]$ 表示只考虑值为 $x$ 的 $a_i$，此时的 $b_i$ 可以由 $b_i = xa_j - b_j$ 得到。令 $y = xa_j - b_j$，并记 $c_{x,y}$ 表示满足 $a_i = x, b_i = y$ 的 $i$ 的数量，则对于每个位置 $j$，它的贡献为 $\sum\limits_{x \leq \sqrt{2n}} c_{x, y}$。

当然，这样遗漏了 $i < j, a_i > \sqrt{2n}$ 的合法二元组的贡献了，可以对这部分贡献专门倒着统计一遍即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve() {
	int n; cin >> n;
	vector<int> a(n), b(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i++)
		cin >> b[i];

	int L = sqrt(2 * n);
	vector<vector<int>> c(L + 1, vector<int>(n + 1, 0));
	i64 ans = 0;
	for(int i = 0; i < n; i++) {
		for(int x = 1; x <= L; x++) {
			int y = a[i] * x - b[i];
			if(y <= 0) continue;
			if(y > n) break;
			ans += c[x][y];
		}
		if(a[i] <= L) {
			c[a[i]][b[i]]++;
		}
	}
	for(int i = 0; i < n; i++) if(a[i] <= L) c[a[i]][b[i]]--;
	for(int i = n - 1; i >= 0; i--) { 
		if(a[i] > L) {
			for(int x = 1; x <= L; x++) {
				int y = a[i] * x - b[i];
				if(y <= 0) continue;
				if(y > n) break;
				ans += c[x][y];
			}
		} else {
			c[a[i]][b[i]]++;
		}
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	int T; cin >> T;
	while(T--) {
		solve();
	}
}
```

---

## 作者：happybob (赞：0)

容易发现 $a_i \times a_j = b_i + b_j$ 时，由于保证了 $1 \leq a_i, b_i \leq n$，所以 $a_i \times a_j \leq 2n$，故 $\min\{a_i,a_j\} \leq \sqrt{2n}$。

考虑枚举每一对 $(i,j)$ 中小于等于 $\sqrt{2n}$ 的那个数。如果 $a_i$ 和 $a_j$ 都小于等于 $\sqrt{2n}$，会算两次，我们在后面重新减掉这部分贡献。现在不妨考虑枚举了 $i$ 且 $a_i \leq \sqrt{2n}$，此时 $a_i,b_i$ 为定值，考虑 $a_i\times a_j = b_i + b_j$，转为 $a_i \times a_j - b_i = b_j$。由于我们钦定了这里 $a_i \leq \sqrt{2n}$，所以可以预先做一次处理求出每种 $a_i$ 时有多少 $j$ 满足 $a_i \times a_j - x = b_j$。这部分复杂度是 $O(n\sqrt{n})$ 的。这样枚举 $i$ 后可以 $O(1)$ 查询。

后面只需要减去 $a_i,a_j$ 同时不超过 $\sqrt{2n}$ 的即可，也是容易通过上面的信息计算的，总复杂度 $O(n\sqrt{n})$。

---

