# 题目信息

# Alice's Adventures in Cutting Cake

## 题目描述

爱丽丝参加了疯帽子的茶话会！有一块长长的蛋糕，由 $n$ 个部分组成，每个部分的美味度值为 $a_1, a_2, \ldots, a_n$ 。茶话会上共有 $m$ 个生物，但不包括爱丽丝。

爱丽丝将把蛋糕切成 $m + 1$ 块。正式地说，她将把蛋糕分成 $m + 1$ 个子串，每个子串由一定数量的相邻部分组成。一块蛋糕的美味度是其各部分美味度的总和。之后，她会将这些 $m + 1$ 块蛋糕分给 $m$ 个生物和她自己（她的那块蛋糕可以是空的）。但是，只有当每个 $m$ 个生物的蛋糕美味度达到或超过 $v$ 时，它们才会感到高兴。

Alice 想要确保每个生物都快乐。受此条件限制，她还想最大化自己的那块食物的美味程度。你能帮助 Alice 找到她的那块食物可以达到的最大美味程度吗？如果没有办法确保每个生物都快乐，则输出 $-1$ 。

## 样例 #1

### 输入

```
7
6 2 1
1 1 10 1 1 10
6 2 2
1 1 10 1 1 10
6 2 3
1 1 10 1 1 10
6 2 10
1 1 10 1 1 10
6 2 11
1 1 10 1 1 10
6 2 12
1 1 10 1 1 10
6 2 12
1 1 1 1 10 10```

### 输出

```
22
12
2
2
2
0
-1```

# AI分析结果

### 题目内容重写
# 爱丽丝的切蛋糕冒险

## 题目描述

爱丽丝参加了疯帽子的茶话会！有一块长长的蛋糕，由 $n$ 个部分组成，每个部分的美味度值为 $a_1, a_2, \ldots, a_n$ 。茶话会上共有 $m$ 个生物，但不包括爱丽丝。

爱丽丝将把蛋糕切成 $m + 1$ 块。正式地说，她将把蛋糕分成 $m + 1$ 个子串，每个子串由一定数量的相邻部分组成。一块蛋糕的美味度是其各部分美味度的总和。之后，她会将这些 $m + 1$ 块蛋糕分给 $m$ 个生物和她自己（她的那块蛋糕可以是空的）。但是，只有当每个 $m$ 个生物的蛋糕美味度达到或超过 $v$ 时，它们才会感到高兴。

Alice 想要确保每个生物都快乐。受此条件限制，她还想最大化自己的那块食物的美味程度。你能帮助 Alice 找到她的那块食物可以达到的最大美味程度吗？如果没有办法确保每个生物都快乐，则输出 $-1$ 。

## 样例 #1

### 输入

```
7
6 2 1
1 1 10 1 1 10
6 2 2
1 1 10 1 1 10
6 2 3
1 1 10 1 1 10
6 2 10
1 1 10 1 1 10
6 2 11
1 1 10 1 1 10
6 2 12
1 1 10 1 1 10
6 2 12
1 1 1 1 10 10```

### 输出

```
22
12
2
2
2
0
-1```

### 综合分析与结论

这道题的核心在于如何在确保 $m$ 个生物都能获得美味度至少为 $v$ 的蛋糕的前提下，最大化爱丽丝自己获得的蛋糕的美味度。题解中主要采用了双指针和前缀和的技巧，通过预处理前缀和后缀信息，快速判断某个区间是否满足条件，并通过双指针优化查找过程。

### 所选高星题解

#### 题解1：作者：chenxi2009 (赞：9)
- **星级**：5星
- **关键亮点**：使用双指针优化查找过程，时间复杂度为 $O(n)$，代码清晰且高效。
- **个人心得**：作者提到刚复习双指针就写一篇双指针题解，说明双指针在实际应用中的重要性。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,v,a[200001],b[200001],r,l,c[200001],mxb[200001],mxa[200002];
long long s[200001],ans;
int main(){
	scanf("%d",&T);
	while(T --){
		r = 0,ans = -1;
		scanf("%d%d%d",&n,&m,&v);
		for(int i = 1;i <= n;i ++){
			scanf("%d",&a[i]);
			s[i] = s[i - 1] + a[i];//前缀和 
		}
		for(l = 1;l <= n;l ++){
			while(r <= n && s[r] - s[l - 1] < v)r ++;
			b[l] = r;//双指针：[l,r] 是以 l 为左端的最短的能满足一个小动物的区间，r=n+1 为满足不了 
		}
		l = n + 1;
		for(r = n;r;r --){
			while(l && s[r] - s[l - 1] < v)l --;
			c[r] = l;//双指针：[l,r] 是以 r 为右端的最短的能满足一个小动物的区间，l=0 为满足不了 
		}
		for(int i = 1;i <= n;i ++)mxb[i] = c[i] ? mxb[c[i] - 1] + 1 : 0;//[1,i] 可以满足的小动物数量 
		mxa[n + 1] = 0;//防越界 
		for(int i = n;i;i --)mxa[i] = b[i] <= n ? mxa[b[i] + 1] + 1 : 0;//[i,n] 可以满足的小动物数量 
		r = 0;
		for(l = 1;l <= n;l ++){
			while(r < n && mxb[l - 1] + mxa[r + 2] >= m)r ++;//双指针：[l,r] 是以 l 为左端的 Alice 可取的最长区间 
			if(mxb[l - 1] + mxa[r + 1] >= m)ans = max(ans,s[r] - s[l - 1]);//可能查到无效区间，所以需要判定 
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

#### 题解2：作者：_299817_ (赞：6)
- **星级**：4星
- **关键亮点**：使用二分查找优化右端点的查找过程，思路清晰，代码结构良好。
- **个人心得**：作者提到逆天场，鉴定为 B >>>> C，说明题目难度较高，需要仔细思考。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<list>
#include<cstdint>
using namespace std;
#define rep(i, l, r) for(i32 i = (i32)(l); i <= (i32)(r); i++)
#define per(i, l, r) for(i32 i = (i32)(l); i >= (i32)(r); i--)
#define FILEIO(INNAME, OUTNAME) freopen(INNAME".in", "r", stdin), freopen(OUTNAME".out", "w", stdout)
#define sort stable_sort
#ifdef QwQ_ATM
    #define Debug(x) cout << "---------- #Debug " << x << " ----------" << endl
    #define DDebug(s, x) cout << s << x
    #define Output(x) cout << x
#else
    #define Debug(x) 1
    #define DDebug(s, x) 1
    #define Output(x) 1
    #define endl '\n'
    #include<bits/stdc++.h>
#endif
#define int long long
typedef pair<int, int> pii;
using i32 = int32_t;
using i64 = int64_t;

const int MAXN = 200010;

int T, n, m, v;
int a[MAXN];
int sum[MAXN];
int pre[MAXN], lst[MAXN];

i32 main(){
    #ifdef QwQ_ATM
        FILEIO("input", "output");
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n >> m >> v;
        rep(i, 1, n) cin >> a[i];
        rep(i, 1, n + 1) sum[i] = sum[i - 1] + a[i]; // 前缀和
        int now = 0; // 预处理数组的所有前缀和后缀中最多能分成多少个区间和大于等于 V 的区间，分别是 pre 和 lst
        rep(i, 1, n){
            now += a[i];
            if(now >= v) pre[i] = pre[i - 1] + 1, now = 0;
            else pre[i] = pre[i - 1];
        }
        now = 0;
        per(i, n, 1){
            now += a[i];
            if(now >= v) lst[i] = lst[i + 1] + 1, now = 0;
            else lst[i] = lst[i + 1];
        }
        if(pre[n] < m){ // 判断无解的情况，也就是整个序列根本不能分成 m 个区间和大于等于 V 的区间
            cout << -1 << endl;
            continue;
        }
        int ans = -1;
        rep(i, 1, n){
            int need = m - pre[i - 1]; // 计算出我们现在还需要多少个区间和大于等于 V 的区间
            int u = upper_bound(lst + i, lst + n + 2, need, greater<int>()) - lst - 1; // 二分右端点
            if(lst[u] < need) continue; // 这个左端点不满足条件
            ans = max(ans, sum[u - 1] - sum[i - 1]); // 用前缀和更新答案
        }
        cout << ans << endl; // 输出
        rep(i, 1, n) pre[i] = lst[i] = 0; // 多测记得清空
    }
    return 0;
}
```

#### 题解3：作者：panxz2009 (赞：2)
- **星级**：4星
- **关键亮点**：使用双指针和前缀和，代码简洁，思路清晰，适合初学者理解。
- **个人心得**：作者提到全机房 VP 碰到的，说明题目在实际比赛中具有一定的挑战性。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 10, inf = 1e18;
int n, m, v, f[maxn], g[maxn], a[maxn], s[maxn], ans;
void solve() {
	scanf("%lld%lld%lld", &n, &m, &v);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	f[0] = 0;
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += a[i];
		f[i] = f[i - 1];
		if(sum >= v) {
			f[i]++;
			sum = 0;
		}
	}
	g[n + 1] = 0, sum = 0;
	for(int i = n; i >= 1; i--) {
		sum += a[i];
		g[i] = g[i + 1];
		if(sum >= v) {
			g[i]++;
			sum = 0;
		}
	}
	if(f[n] < m) {
		puts("-1");
		return;
	}
	ans = 0;
	for(int l = 0, r = 0; l <= n; l++) {
		while(r <= n && f[l] + g[r + 1] >= m) r++;
		ans = max(ans, s[r - 1] - s[l]);
	}
	printf("%lld\n", ans);
}
signed main() {
	int T;
	scanf("%lld", &T);
	while(T--) solve();
	return 0;
}
```

### 最优关键思路与技巧
1. **双指针优化**：通过双指针快速找到满足条件的区间，时间复杂度为 $O(n)$。
2. **前缀和预处理**：通过前缀和快速计算任意区间的美味度和，方便后续判断。
3. **二分查找**：在确定右端点时，使用二分查找进一步优化查找过程。

### 可拓展之处
- **类似问题**：可以扩展到其他需要满足多个条件的最优化问题，如资源分配、任务调度等。
- **算法套路**：双指针和前缀和的组合在解决区间问题时非常常见，可以举一反三应用到其他题目中。

### 推荐题目
1. [P1147 连续子序列的最大和](https://www.luogu.com.cn/problem/P1147)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：86.58秒