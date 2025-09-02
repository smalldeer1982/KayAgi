# Line Game

## 题目描述

你在玩一个音游。

这个音游可以抽象为一个长度为 $m+1$ 的线段。

这个音游有 $n+m$ 秒，在前 $n$ 秒中，第 $i$ 秒会在 $1$ 处出现一个集合，这个集合可以用一个可重无序集 $S_i$ 来表示，大小为 $a_i$，每秒末尾这个集合的位置会增加 $1$。

因为你不会玩，所以你有一个可爱的 bot，它在第 $0$ 秒位于 $1$，之后每一秒你都需要选择一个值域区间 $[l,r]$，若这个 bot 所处位置有一个非空的集合 $Q$，那么 bot 会消去 $Q$ 中值域位于 $[l,r]$ 的数，该操作代价为 $r-l+1$。除此之外，这个 bot 在每秒的末尾可以选择将自己的位置 $+1$。

若有非空的集合到达 $m+1$ 处，那么你就失败了。请问在不失败的情况下你最少需要花费多少代价？

## 说明/提示

设 $[1,k]$ 为集合中元素的值域。

**本题采用捆绑测试。**

- Subtask#1（$10\text{pts}$）：$m=1$；
- Subtask#2（$20\text{pts}$）：$n=1$；
- Subtask#3（$15\text{pts}$）：$k=100$；
- Subtask#4（$15\text{pts}$）：$m\le 100$；
- Subtask#5（$20\text{pts}$）：$m\le 10^5$；
- Subtask#6（$20\text{pts}$）：无特殊限制。


对于 $100\%$ 的数据，$1\le n\le 100$，$1\le m\le 10^9$，$1\le a_i\le 5\times 10^4$，除 Subtusk#3 外 $k=10^9$。

## 样例 #1

### 输入

```
1 2
4 1 2 6 7```

### 输出

```
4```

# 题解

## 作者：chenly8128 (赞：3)

最难的是看懂题目。

本质上就是给出 $n$ 条线段，并给出第 $i$ 条线段上的 $a_i$ 个**关键点**，允许删除总计最多 $m-1$ 条不含关键点的子线段，问剩下的线段含有的点（不仅包括关键点）的总数是多少。

理解到这一步，直接使用整体减空白思想和贪心大法。

1. 首先，计算不删除任何子线段情况下，点的总数。
2. 接着，计算把每条线段中任意的相邻的两个关键点之间子线段删去，能够减少的点的个数。并存入一个数组 $a$。
3. 然后，$a$ 从大到小排序。
4. 最后，从总点数中减掉 $a$ 中大于 $0$ 的至多前 $m-1$ 项。

然后就好了，复杂度 $O(an\log_2{an})$，瓶颈在于排序。

### CODE


```cpp

// Author: chenly8128
// Created: 2025-01-30 15:58:36

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(void) {
	int res = 0;bool flag = true;char c = getchar();
	while (c < '0' || c > '9') {flag ^= (c == '-');c = getchar();}
	while (c >= '0' && c <= '9') {res = (res << 3) + (res << 1) + (c ^ 48);c = getchar();}
	return flag ? res : -res;
}
vector <int> res;
vector <int> v;
int n,m,a;
ll sum = 0;
int main (void) {
	n = read();m = read();
	for (int i = 1;i <= n;i++) {
		a = read();
		v.clear();
		for (int i = 1;i <= a;i++) v.push_back(read());
		sort (v.begin(),v.end());
		for (int i = 1;i < a;i++)
			res.push_back(v[i]-v[i-1]-1);
		sum += v[a-1]-v[0]+1;
	}
	sort (res.begin(),res.end(),greater<int>());
	for (int i = 0;i < res.size();i++) {
		if (i >= m-1 || res[i] <= 0) break;
		sum -= res[i];
	}
	printf ("%lld\n",sum);
	return 0;
}
```

---

## 作者：xuyifei0302 (赞：1)

读完题，我们发现，若一个集合只用一个区间，那么每个集合都是最大减去最小加一，然后求和。

然后就发现一个集合是可以使用多个区间。我们就必须要把每个集合里的每种数都设定一个代价。

多个区间就是排完序之后，区间之间的交界处之间的数都不提供代价。所以我们排完序相邻两种数算差并减一，就是在这里分界可以减免的代价。

所以我们将这些减免的大小进行排序，选择前 $m - 1$ 大的进行减免即可。

下面是代码环节：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, a[50005], sum, cnt, b[5000005];
bool cmp(int x, int y) {
	return x > y;
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		int len;
		cin >> len;
		for (int j = 1; j <= len; j ++) {
			cin >> a[j];
		}
		sort(a + 1, a + 1 + len);
		sum += a[len] - a[1] + 1;
		for (int j = 2; j <= len; j ++) {
			if (a[j - 1] != a[j]) {
				b[++cnt] = a[j] - a[j - 1] - 1;
			}
		}
	}
	sort(b + 1, b + 1 + cnt, cmp);
	for (int i = 1; i <= min(cnt, m - 1); i ++) {
		sum -= b[i];
	}
	cout << sum;
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

首先可以发现，如果你把一个集合放走了，让它跑到了 bot 后面，bot 就永远追不上了，所以不能这么做。

所以 bot 必须一直跟着最前面的集合，直到将它清空然后再停下来等待后面的集合，然后再跟着它走……

但是，如果你一次操作就把某个集合秒没了，就不用移动位置，可以待在原地。这说明，每个集合有一次免费的攻击机会。

而一次就清空的方案可能不优，因为集合的值域中间有一些空隙，本来不需要覆盖到。如果增加一个空隙，值域的分段数就会增加 $1$，也就是说 bot 就得再跟着那个集合走一步，但是最终代价会减少空隙的长度。

bot 走到 $m$ 就必须把集合消灭，所以最多从 $1$ 开始往后走 $m-1$ 步，所以恰好可以随便选择 $m-1$ 个空隙，贪心从最大的空隙开始选取即可。

设 $N$ 为 $\sum\limits_{i=1}^na_i$，则代码时间复杂度为 $O(N\log N)$，瓶颈在于排序。

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,m,b[50010],a[5000010],cur;
int ans;
bool cmp(const int &x,const int &y){
    return x>y;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int k;
        cin>>k;
        int minn=1e9,maxn=0;
        for(int j=1;j<=k;j++)cin>>b[j];
        sort(b+1,b+k+1);
        ans+=b[k]-b[1]+1;
        for(int j=1;j<=k;j++)
            if(j>1)a[++cur]=b[j]-b[j-1]-1;
    }
    sort(a+1,a+cur+1,cmp);
    for(int i=1;i<=min(m-1,cur);i++)
        if(a[i]>0)ans-=a[i];
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Vincent615 (赞：0)

# P11639 Line Game 题解

[题目传送门](https://www.luogu.com.cn/problem/P11639)

## 分析题目

有 $n$ 条线段，给定第 $i$ 条线段上的 $a_i$ 个点，可以删除最多 $m - 1$ 条线段，求剩余线段上的所有点数的总和。

$m < 10^9$ 让我放弃暴力，想一想贪心大法。

## 贪心

先排序！

如果一个集合只包含一个区间的话，那么这个集合的答案就是集合中最大的元素减去集合中最小的元素加 $1$ ，求和。

如果一个集合包含多个区间的话，所以所有区间的交界处的点对答案不提供任何代价。将每个相邻位置作差减 $1$ ，~~别问我为啥减一~~。这些就是可以消掉的代价，存储在另一个数组 $b$ 中。

最后，从大到小给 $b$ 排序。选前 $\min(b\text{数组中实际存储的元素个数}, m - 1)$ 个抵消。

## 上代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,sum,cnt;
int a[50005],b[5000005];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int len;
		cin >> len;
		for(int j=1;j<=len;j++){
			cin>>a[j];
		}
		
		sort(a+1,a+1+len);
		sum+=a[len]-a[1]+1;
		for(int j=2;j<=len;j++){
			if(a[j-1]!=a[j]){
				b[++cnt]=a[j]-a[j-1]-1;
			}
		}
	}
	
	sort(b+1,b+1+cnt,greater<int>());
	for(int i=1;i<=min(cnt,m-1);i++){
		sum-=b[i];
	}
	cout<<sum;
	return 0;
}

```

## AC 记录

[AC](https://www.luogu.com.cn/record/202601864)

---

## 作者：_O_v_O_ (赞：0)

出题人题解。

先将所有可重无序集去重排序，很显然不影响答案。

我们注意到 bot 往后移一格那么肯定是在当前格子内的集合没被消完的情况。

那么每向后移一格就相当于将这个集合拆成了两个集合来消掉，一次在移动前消，一次在移动后消。

也就是说，问题被转换成了给定 $m$ 个集合，你可以把 $m$ 个集合拆成最多 $n+m$ 个，使得所有被拆集合的极差和最小。

很显然拆一个集合 $S$ 拆一次后的最小代价为 $(\max_{i\in S}i-\min_{i\in S}i)-\max_{i=1}^{|S|-1}(S_{i+1}-S_i)$，即从 $\max_{i=1}^{|S|-1}(S_{i+1}-S_i)$ 的 $i$ 处拆。

那么就很显然了，我们按照上述方法类比至所有集合即可。

---

## 作者：DecemberFox (赞：0)

# P11639 Line Game 题解

## 题目分析

简单来说，本题要求使用若干个值域区间覆盖 $n$ 个集合中的所有数，并且被多个区间覆盖的集合额外使用的区间（即覆盖该集合的区间数减一）的总数不超过 $m$。

此外，所有区间需要花费其长度的代价。求在满足情况下最少需要的代价。

## 解法分析

不难发现，如果一个集合中的所有数需要被若干个区间覆盖，那么区间需要避开集合中值域空缺的地方。

例如在集合 $\{1,2,6,7\}$ 中可以使用两个区间（$[1,2]$ 和 $[6,7]$，代价为 $4$）覆盖，这比使用一个区间更优（$[1,7]$，代价为 $7$）。

但是额外使用的区间不能过多，因此需要尽可能地将含有较多值域空缺的区间分割为较小的区间。

因此利用贪心的思想，将每个集合中所有值域空缺的长度记录下来，按照由长到短排序，分割区间。

具体实现中，可以先假设所有集合均被一个大区间覆盖，然后通过值域空缺的长度分割区间。容易发现，减少的代价可以通过值域空缺的长度直接计算。

需要注意的是，集合中的元素是可以重复的，且重复元素对区间的划分没有影响，因此可以将其去除。

```cpp
#include<algorithm>
#include<iostream>
#include<vector>
#include<cstdio>
#include<queue>
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	typedef __int128 lll;
	typedef unsigned __int128 ulll;
	const int const1=5e4+10;
	int a,s[const1];
	std::priority_queue<int,std::vector<int>,std::less<int> > q;
	bool cmp(int x,int y)
	{
		return x>y;
	}
	void solve()
	{
		int i,j,n,m;
		ll ans(0);
		read(n,m);
		--m;
		for(i=1;i<=n;++i)
		{
			read(a);
			for(j=1;j<=a;++j) read(s[j]);
			std::sort(s+1,s+a+1);
			for(j=1;j<a;++j) q.push(std::max(0,s[j+1]-s[j]-1));
			ans+=s[a]-s[1]+1;
		}
		for(i=1;i<=m&&!q.empty();++i)
		{
			ans-=q.top();
			q.pop();
		}
		write(ans);
	}
}
int main()
{
	SOLVE::solve();
	return 0;
}
```

---

## 作者：LittleAcbg (赞：0)

验题人题解。

模拟一下样例可以发现，每次消除之后，如果这个集合还没消完，就跟着它去下一个位置，到下一个位置时就可以多一次消除该集合的机会。如果这个集合消除完了，就在原地等下一个集合。

bot 最多可以多消除 $m-1$ 次，因为 $m$ 次就到 $m+1$ 位置而输了。

我们考虑贪心，有 $m-1$ 次额外消除的机会，每次可以将某个消除区间分成两个区间进行消除，可以节省两个相邻元素之间的所有数，节省的代价是 $a_{i+1}-a_i-1$。

接着将所有节省的代价从大到小排序处理即可，我使用的是 `priority_queue` 大根堆处理。

本题还有一个坑点，就是 $S$ 是**可重无序集**：

- 可重：注意可能有 $a_{i+1}=a_i$ 导致 $a_{i+1}-a_i-1=-1$，导致增加代价的情况。
- 无序：输入的集合需要排序。

具体处理见代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e4+9;
int n,m,k,a[N];
ll ans;
priority_queue<int> q; // 大根堆
int main()
{
    scanf("%d%d", &n, &m);
    while (n--)
    {
        scanf("%d", &k);
        for (int i = 1; i <= k; ++i) scanf("%d", &a[i]);
        sort(a + 1, a + k + 1); // 无序集处理
        ans += a[k] - a[1] + 1; // 整体消除代价
        for (int i = 1; i < k; ++i)
            q.push(a[i + 1] - a[i] - 1); // 节省的代价
    }
    while (--m) // 循环 m-1 次
    {
        if (q.empty()) break;
        if (q.top() <= 0) break; // 可重集处理
        ans -= q.top();
        q.pop();
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P11639 题解

## 思路

仔细阅读题目不难发现，对于 $n$ 个集合，你最多能进行 $n+m-1$ 次操作，并且同一个集合的操作次数不超过 $m$。

先假设刚好执行 $n$ 次操作，那么这 $n$ 次操作一一对应 $n$ 个集合，每一个操作将对应集合完全覆盖。

将一个集合其中一个操作拆分成两个，操作次数 $+1$，本集合的操作次数 $+1$，代价也相应地会减少。

一共可以进行 $m-1$ 次分裂，每一次分裂都要使代价尽可能多地减少。

对于一个集合 $S_i$ 中的每一个元素 $s_1, s_2, \cdots, s_{a_i}$，对于每一个 $i$，在满足 $1 \le i \le a_i-1$ 的条件下，记 $v_i = s_{i+1}-s_i-1$，则 $v_i$ 表示若 $s_i$ 与 $s_{i+1}$ 在相同一次操作内被覆盖，则从它们中间将操作切开，可以减掉多少贡献。

将这些 $v$ 进行降序排序，然后依次枚举每一个 $v$，若 $v$ 所属原集合的分裂次数（分裂次数即操作次数减一）未达到 $m-1$ 且总分裂次数未达到 $m-1$，则可以操作，否则跳过找下一个。

注意特判 $s_i = s_{i+1}$ 的情况，这里的贡献 $v_i = s_{i+1}-s_i-1$ 在计算时会得到 $-1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
};

using namespace IO;

const int N=105;
const int M=50005;

int n,m;
int a[N];
int s[N][M];
vector<pii> vec;
int tot;
int cnt[N];
i64 ans;

bool cmp(const pii& a,const pii& b) {
    return a.first>b.first;
}

int main() {
    read(n),read(m);
    _rep(i,1,n) {
        read(a[i]);
        _rep(j,1,a[i]) read(s[i][j]);
        sort(s[i]+1,s[i]+1+a[i]);
        ans+=s[i][a[i]]-s[i][1]+1;
        _rep(j,1,a[i]-1) vec.emplace_back(pii{s[i][j+1]-s[i][j]-1,i});
    }
    sort(vec.begin(),vec.end(),cmp);
    _iter(it,vec) {
        int dec=it->first,idx=it->second;
        if (dec<0) break;
        if (cnt[idx]+1<m) cnt[idx]++,tot++,ans-=dec;
        if (tot==m-1) break;
    }
    write(ans);
    return 0;
}
```

---

## 作者：DrAlfred (赞：0)

摘要：双指针，贪心

[传送门：https://www.luogu.com.cn/problem/P11639](https://www.luogu.com.cn/problem/P11639)

## 题意

有一个下落式音游，谱面是一个长度为 $m+1$ 的线段。音游有 $n+m$ 秒，在前 $n$ 秒中，第 $i$ 秒会在高度 $1$ 处出现一个集合，这个集合可以用一个可重无序集 $S_i$ 来表示，大小为 $a_i$，每秒末尾这个集合的高度会增加 $1$。

手指一开始在高度 $1$，每次可以 `flip` 消除手指在的高度的集合的一段值域。代价为值域的长度。然后可以选择将手指的高度加 $1$。若有非空的集合到达 $m+1$ 处就失败了。求在不失败的情况下最少需要花费多少代价？

## 分析思路

如果 $m$ 无限大，最优的策略显然就是手指一直跟着目前没有被消除的集合，消除它其中一段值域的连续段（因为如果“放走”了一个非空的集合，就永远追不上了）。这时候答案就是所以 $S_i$ 的每个值域连续段的长度之和。

而有了 $m$ 的限制，也就意味着我们可能需要用更少的步数完成所有消除。考虑答案会多出来的部分。具体来说，如果有两个值域连续段 $[l_1, r_1], [l_2, r_2]$，其中 $l_2 - r_1 > 1$，我们可以选择花费两个单位高度，分别消除两段，代价是 $(r_1 - l_1 + 1) + (r_2 - l_2 + 1)$；我们也可以只花费一个单位高度，代价是 $r_2 - l_1 + 1$，相比上一种答案增加了 $l_2 - r_1 - 1$。其实就是多花了 $(r_1, l_2)$ 的代价。我们把这些值域之间的空隙叫做 `gap`。

那么，贪心策略就很显然了，花费一个 `gap` 就能挣回一个单位的高度，那么显然挑最小的 `gap` 补上就行。如果有 $g$ 个 `gap`，那么有 $g + n$ 个值域连续段，要将高度限制在 $n + m - 1$ 内，就要删除 $g - m + 1$ 个 `gap`。通过排序和双指针处理值域连续段，贪心即可。时间复杂度 $O(\sum a_i \log a_i)$，可以通过。

其实本题蕴涵了反悔贪心的思想，读者可以自行思考。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, x, S[50010];
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    long long ans = 0;
    std::vector<int> G; // 存储所有 gap
    optimizeIO(), cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        for (int j = 1; j <= x; j++) {
            cin >> S[j];
        }
        sort(S + 1, S + 1 + x);
        for (int l = 1, r = 1; l <= x; l = r) { // 双指针处理值域连续段
            while (r <= x && S[r] - S[l] <= 1) r++;
            if (l != 1) G.push_back(S[l] - S[l - 1] - 1);
            ans += S[r - 1] - S[l] + 1; // 加上逃不掉的答案
        }
    }
    sort(G.begin(), G.end());
    for (int i = 0; i <= (int)G.size() - m; i++) {
        ans += G[i]; // 加上额外要补的答案
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：K_yuxiang_rose (赞：0)

写的时候感觉这个做法是假的，但还是过了。

先考虑 $m$ 较大的情况。对于每个集合，将里面的数一个一个消掉（多个重复数字一起消，代价不变），这样能保证最小代价，同时因为 $m$ 较大，我们拥有充足的时间去单个消除。排序去重加特判能得到 65pts。

本题最大的难点就是 $m$ 较小的情况，也就是第四个和第五个捆绑点。如果时间不够，要考虑合并相邻的数字一起消。贪心策略，两数之间的自然数越少，需要增加的代价就越小，因此要选择相邻的数合并。

先求出单个消除需要的时间和最小代价，再存合并相邻的数需要的代价，把这些代价排个序，每次取代价最小的合并直到需要的时间等于 $m+n-1$ 为止。

为什么不是 $m+n$？因为这个线段从 $1$ 开始，到 $m+1$ 结束，因此每个集合待在线段上的时间只有 $m-1$ 秒。

---

## 作者：sbno333 (赞：0)

最开始没看懂题，所以这里给题意简述。

给定 $n$ 个由若干整数组成的集合，对于每个集合，你都要选择若干区间使得集合所有数都被包含在这些区间的并，代价为区间并的大小，所有集合你总共可以选取 $n+m-1$ 个区间，求最小代价。

当 $m=1$ 时，每个集合都是最大减去最小加一，求和，这启示我们要排序。

考虑一个集合可以用多个区间该怎么办。

发现每个集合中的每种数都必须要用一个代价来弄。

考虑我们要让选中的多余数尽量少。

发现多个区间就是排完序之后区间与区间交界处之间的数都不提供代价。

所以我们排完序相邻两种数算差并减一得到在这里分界可以减免的代价。

发现可以把每个集合的每一个这样的大小丢到一起，排序，选出前 $m-1$ 大的和减免即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int dx[5000009];
int a[1000009];
int inn;
signed main(){
	cin>>n>>m;
	m--;
	int ans;
	ans=0;
	while(n--){
		int nn;
		cin>>nn;
		for(int i=1;i<=nn;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+nn);
		ans+=a[nn]-a[1]+1;
		for(int i=2;i<=nn;i++){
			if(a[i]!=a[i-1])
			dx[++inn]=a[i]-a[i-1]-1;
		}
	}
	sort(dx+1,dx+1+inn);
	m=min(m,inn);
	for(int i=inn;i>=inn-m+1;i--){
		ans-=dx[i];
	}
	cout<<ans;
	return 0;
}
```

---

