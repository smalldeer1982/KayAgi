# Kevin and Competition Memories

## 题目描述

Kevin 曾经进入过 Rio 的记忆。在那段记忆中，曾举办过一系列的比赛。Kevin 还记得所有参赛者和比赛的问题，但具体的比赛轮次、问题分布和排名已经模糊不清。

有 $m$ 个比赛问题，第 $i$ 个问题的难度为 $b_i$。每场比赛选择 $k$ 个问题，因此总共会有 $\lfloor \frac{m}{k} \rfloor$ 场比赛。这意味着你可以任意组合选择这些比赛问题，并挑出总共 $\lfloor \frac{m}{k} \rfloor \cdot k$ 个问题参赛，每个问题最多只能被选一次，剩余 $m \bmod k$ 个问题将未被使用。例如，如果 $m = 17$ 且 $k = 3$，你将组织 $5$ 场比赛，每场 $3$ 个问题，会剩下 $2$ 个问题没有用上。

比赛有 $n$ 位参赛者，其中 Kevin 是第 1 位。第 $i$ 位参赛者的评分是 $a_i$。在比赛中，每个参赛者能解决难度不超过其评分的问题，具体来说，第 $i$ 位参赛者能解决第 $j$ 个问题，当且仅当 $a_i \geq b_j$。在每场比赛中，Kevin 的排名定义为那些比他解掉更多题目的参赛者数量加一。

对于每个 $k = 1, 2, \ldots, m$，Kevin 想知道在所有 $\lfloor \frac{m}{k} \rfloor$ 场比赛中的排名之和的最小可能值。也就是说，对于某个 $k$，你需要优化问题的选择和分配，使得 Kevin 的排名之和最小化。

不同的 $k$ 值代表的比赛是相互独立的。换言之，你可以对每个不同的 $k$ 值分别规划问题分配。

## 说明/提示

考虑第一个测试数据：

- 当 $k=1$ 时，每场比赛只包含一个问题，分配方式是唯一的。例如，在包含难度为 $4$ 的第三个问题的比赛中，除了第 2 位参赛者外，所有人都能解决。因为没有人比 Kevin 解出更多的问题，他在这场比赛中排名第 1。同理，在所有 $4$ 场比赛中，Kevin 的排名分别是 $1, 3, 1, 2$，总和为 $7$。

- 当 $k=2$ 时，最佳选择是将第 1 和第 3 个问题组成一场比赛，第 2 和第 4 个问题组成另一场。在前一场比赛中，4 名选手分别解决 $2, 1, 2, 2$ 个问题，Kevin 排名第 1；在后一场比赛中，选手分别解决 $0, 0, 2, 1$ 个问题，因有 2 位选手多解题，Kevin 排名第 $3$。所以总和是 $1 + 3 = 4$。这是最优解。

- 当 $k=3$ 时，可以选择第 1、3、4 个问题组成一场比赛，Kevin 的排名是 2，为最优。

- 当 $k=4$ 时，只有一场比赛，分配方式唯一，Kevin 的排名是 3。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
4 4
4 3 7 5
2 5 4 6
5 5
5 0 4 8 6
1 3 9 2 7
6 7
1 1 4 5 1 4
1 9 1 9 8 1 0
7 6
1 9 1 9 8 1 0
1 1 4 5 1 4```

### 输出

```
7 4 2 3
6 2 1 1 2
7 3 2 1 1 1 1
15 9 5 4 4 4```

# 题解

## 作者：ZnPdCo (赞：4)

注意到比自己弱的选手没用，全部杀。

注意到把比自己弱的选手杀完之后，题目分三类，我会的，我不会的但别人会的，我不会的别人也不会的。

第三类题目没有用，第一类题目也没用，全部删。

那么剩下的题目中，一道题目对排名的贡献就是会的人的个数加一。

那么一套题目对排名的贡献就是这套题目内所有题目的贡献的最大值。

答案就是所有套题的贡献的和。

一道题目对排名的贡献 $c_i$ 是好算的，可以二分计算她。

然后贪心的想，直接把 $c_i$ 从小到大排序，那么就是第 $1$ 到 $k$ 题组一套，$k+1$ 到 $2k$ 题组一套，以此类推。然后计算 $k$ 的答案就是 $c_k+c_{2k}+c_{3k}+\cdots$。

$O(n\log n)$（视 $n$ 和 $m$ 同阶）。

```cpp
#include <bits/stdc++.h>
#define N 300010
#define int long long
using namespace std;
int T, n, m, a[N], b[N];
signed main() {
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) cin >> a[i];
        for(int i = 1; i <= m; i++) cin >> b[i];
        if(n != 1)
            sort(a + 2, a + n + 1, greater<int>()), n = lower_bound(a + 2, a + n + 1, a[1], greater<int>()) - a - 1;
        sort(a + 2, a + n + 1, greater<int>());
        for(int i = 1; i <= m; i++) b[i] = b[i] <= a[1] ? 0 : upper_bound(a + 2, a + n + 1, b[i], greater<int>()) - a - 2;
        sort(b + 1, b + m + 1);
        for(int k = 1; k <= m || (cout << endl, 0); k++)
            for(int i = k, ans = m / k; i <= m || (cout << ans << " ", 0); i += k)
                ans += b[i];
    }
}
```

这题就是第二类题目。

---

## 作者：postpone (赞：2)

先从 $k=1$ 入手，也就是把每一题的排名算出来。具体地，设 $c_i$ 为第 $i$ 道题这个人的排名。

然后来看 $k>1$，即能选题组起来的情况。比如说我把某两道题 $i, j$ 组合起来，可以发现组合之后 $c'=\max(c_i, c_j)$，这场的排名是这些题的排名的最大值。

要让 $\sum c'$ 最小，贪心地想，就是要尽量把小的组在一起，可以发现，就是将 $c$ 升序之后取前 $\lfloor \frac mk \rfloor$ 个子串。

关于这个结论的证明，可以想想一个升序的序列，交换两个来自不同块的元素。只有取块中的最大，才会影响结果，但分类讨论一下能发现，无论拿哪个，结果都一定不会优。

因此先二分预处理 $c$ 数组，随后如上所述模拟结果即可。

```cpp
void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    const int me = a[0];

    ranges::sort(a);
    vector<int> c(m);

    for (int i = 0; i < m; i++) {
        if (b[i] <= me) {
            c[i] = 1;
        } else {
            c[i] = a.end() - (lower_bound(a.begin(), a.end(), b[i])) + 1;
        }
    }
    ranges::sort(c);
    RMQ<int, greater<int>> rmq(c); // ST 表
    
    for (int i = 1; i <= m; i++) {
        ll ans{};
        for (int j = 0; j + i <= m; j += i) {
            ans += rmq(j, j + i);
        }
        cout << ans << " \n"[i == m];
    }
}
```

---

## 作者：OIer_Hhy (赞：0)

把所有题目都分两类.

- Kevin 会做的。
- Kevin 不会做的。

考虑贪心。

将题目分成两类后排序：

- 对于 Kevin 会做的题，按从易到难排序。
- 对于 Kevin 不会做的题，按从难到易排序（尽量让别人也不会做）。

接着处理查询。

我们先将第 $2$ 至 $n$ 位选手按等级分升序排序，方便待会二分。

接着，我们枚举每一个 $k \in [1,m]$，对于每一个 $k$ 枚举 $b_{kq(q \in N+,kq \le m)}$，分为两种情况：

- Kevin 会做：直接第一。
- Kevin 不会做：二分查找出会做这道题的人的个数。

代码如下：（I love wxq forever!）


```cpp
#include<bits/stdc++.h>
#define int long long
#define I_love_wxq_4ever true
using namespace std;
const int N=3e5+10;
int n,m,a[N],b[N];
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(b+1,b+m+1);
	int pos=upper_bound(b+1,b+m+1,a[1])-b;
	sort(b+pos,b+m+1,greater<int>());
	sort(a+2,a+n+1);
	#ifndef I_love_wxq_4ever
	for(int i=1;i<=n;i++) cout<<a[i]<<' ';
	cout<<"\n";
	for(int i=1;i<=m;i++) cout<<b[i]<<' ';
	cout<<"\n";
	#endif
	
	for(int i=1;i<=m;i++){
		int res=0;
		for(int j=1;j<=m/i;j++){
			if(a[1]>=b[j*i]){
				res++;
				continue;
			}
			int pos=lower_bound(a+2,a+n+1,b[j*i])-a;
			res+=n-pos+2;
		}
		cout<<res<<" ";
	}
	cout<<'\n';
}
signed main(){
	#ifdef I_love_wxq_4ever
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	#endif
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}

```

---

## 作者：wfc284 (赞：0)

提供一种非常 naive 且暴力的思路。   
小于等于 Kevin 的选手没有任何贡献，扣掉。  
我们发现，我们如果按轮次一个个填充这一堆比赛，实际上是可以确定一个（可能的）最优填充次序的。  
先填 Kevin 会做的。这些题目**不影响排名**。  
再按 $b_i$ **从大到小**依次填充。这样是最优的，因为 $b_i$ 越小，贡献越大，肯定是按顺序填充的，要么从大到小，要么从小到大。显然降序更优。（感性理解）  
做完了。

Q：不会 T 吗？  
A：我们填充时，只关心一场比赛中，除 Kevin 会做的比赛外，**最简单的题目**。于是 ST 表维护即可。而对于一个 $k$，只有 $\lfloor \frac{m}{k} \rfloor$ 场比赛。所以比赛总场数是 $\sum_{k=1}^{m}\lfloor \frac{m}{k} \rfloor = O(m\log m)$ 的。带上 ST 表，总时间复杂度 $O(m \log^{2} m)$。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 3e5+2;
	
	int n, m, x, tmp[N], *a, b[N];
	vector<int> c;
	
	int f[N][20], LOG2[N];	//ST表
	int query(int l, int r) {
		if(l > r) return inf;
		int k = LOG2[r - l + 1];
		return min(f[l][k], f[r - (1 << k) + 1][k]);
	}
	
	void main() {
		cin >> n >> m;
		for(int i = 1; i <= n; ++i) scanf("%d", &tmp[i]);
		x = tmp[1], a = tmp + 1;
		for(int i = 1; i <= m; ++i) scanf("%d", &b[i]);
		
		sort(a+1, a+n);
		a = upper_bound(a+1, a+n, x) - 1;
		n -= a - tmp;
		sort(b+1, b+m+1);
		
		c.clear();
		c.push_back(0);
		int easy = 0;
		for(int i = 1; i <= m; ++i)
			if(b[i] <= x) c.push_back(b[i]), ++easy;
			else break;
		for(int i = m; i >= 1; --i)
			if(b[i] > x) c.push_back(b[i]);
			else break;
		//按c数组的顺序依次填充比赛
		
		for(int i = 2; i <= m; ++i) LOG2[i] = LOG2[i >> 1] + 1;
		for(int i = 1; i <= m; ++i) f[i][0] = c[i];
		for(int k = 1; k <= 19; ++k)
			for(int i = 1; i + (1 << k) - 1 <= m; ++i)
				f[i][k] = min(f[i][k-1], f[i + (1 << k-1)][k-1]);
		
		for(int k = 1; k <= m; ++k) {
			int p = 1;
			long long ans = 0;
			for(int r = 1; r <= m / k; ++r) {
				int v = query(max(p, easy+1), p+k-1);
				int rank = n - (lower_bound(a+1, a+n+1, v) - a) + 2;
				ans += rank;
				p += k;
			}
			printf("%lld ", ans);
		}
		puts("");
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：_lmh_ (赞：0)

考虑一场比赛，假设其题目难度从小到大为 $d_1\sim d_k$。

如果 $a_i<a_j$，那么 $i$ 能做出的题目 $j$ 一定也能做出。也就是说，$i$ 排名比 $j$ 靠后当且仅当存在一个 $a_i<d_x\le a_j$。

现在考虑 $a_1$ 的排名。如果 $d_k\le a_1$ 显然它肯定并列第一，否则设第一个 $\ge a_1$ 的 $d$ 是 $d_x$。

显然 $\le a_1$ 的 $a_i$ 无意义，而只有 $a_1<d_x\le a_i$ 的人排名比他高。（否则，$d_{x-1}\le a_1<a_i<d_x$，两个人做出的题目一样多）

也就是说，对于每个 $a_1$ 做不出的题目，计算它的排名 $p_i$ 为能做出这道题的人数 $+1$（否则 $p_i=1$），可以证明最终 $a_1$ 的排名为 $p_i$ 的最大值。

对 $p$ 排序，显然选择 $p_{xk}(1\le xk\le m,x\in \Z)$ 最优，构造方案显然。

直接做需要 $n\sum_{i=1}^n\frac{1}{i}$ 次运算，是 $O(n\log n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=300007;
ll T,n,m,a[N],b[N],ans[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for (int i=1;i<=n;++i) cin>>a[i];
		for (int i=1;i<=m;++i){cin>>b[i];ans[i]=(a[1]>=b[i]);}
		sort(a+1,a+1+n);
		for (int i=1;i<=m;++i) if (!ans[i]) ans[i]=n-(lower_bound(a+1,a+1+n,b[i])-a)+2;
		sort(ans+1,ans+1+m);
		for (int i=1;i<=m;++i) for (int j=i+i;j<=m;j+=i) ans[i]+=ans[j];
		for (int i=1;i<=m;++i) cout<<ans[i]<<' ';cout<<'\n';
	}
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF2048D)

## statement

$n$ 名选手，$m$ 道题目，第 $i$ 名选手的能力值为 $a_i$，第 $j$ 道题目的难度为 $b_j$，对于第 $i$ 个选手，Ta 可以解决 $a_i \geq b_j$ 的题目，第 $1$ 个选手是 Kevin，Ta 的排名是 $1$ 加上比他解决更多问题的参赛者的数量，对于 $\forall k \in [1,m]$，所有 $\lfloor{\frac{n}{k}}\rfloor$ 场中每场 $k$ 道题目，求出最小化的 Kevin 在每场比赛中的 rank 之和。

## Solution

对于一道难度大于 $\max\{a_i\}$ 的题目，所有人都做不了，不会对 Kevin 的排名产生影响；对于一道 $a_1 < b_j \leq a_i$ 的题目，记能做出该题的人数为 $t$，则它会使 Kevin 的排名下降 $t$；对于一道 $b_j \leq a_1$，并不会产生影响，综上所述，我们只需要对 $a$ 排序后每次找到 $a$ 中第一个大于等于 $b_i$ 的位置 $ptr$，此时 Kevin 的排名为 $n - ptr + 1$，每次枚举 $k$，统计 $tk \leq m(t \in \mathbb{N_{+}})$ 位置的 rank 之和。

## code

[代码 click here](https://codeforces.com/contest/2048/submission/297379235)

---

