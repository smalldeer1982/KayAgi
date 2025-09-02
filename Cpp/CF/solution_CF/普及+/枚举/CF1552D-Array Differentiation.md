# Array Differentiation

## 题目描述

You are given a sequence of $ n $ integers $ a_1, \, a_2, \, \dots, \, a_n $ .

Does there exist a sequence of $ n $ integers $ b_1, \, b_2, \, \dots, \, b_n $ such that the following property holds?

- For each $ 1 \le i \le n $ , there exist two (not necessarily distinct) indices $ j $ and $ k $ ( $ 1 \le j, \, k \le n $ ) such that $ a_i = b_j - b_k $ .

## 说明/提示

In the first test case, the sequence $ b = [-9, \, 2, \, 1, \, 3, \, -2] $ satisfies the property. Indeed, the following holds:

- $ a_1 = 4 = 2 - (-2) = b_2 - b_5 $ ;
- $ a_2 = -7 = -9 - (-2) = b_1 - b_5 $ ;
- $ a_3 = -1 = 1 - 2 = b_3 - b_2 $ ;
- $ a_4 = 5 = 3 - (-2) = b_4 - b_5 $ ;
- $ a_5 = 10 = 1 - (-9) = b_3 - b_1 $ .

In the second test case, it is sufficient to choose $ b = [0] $ , since $ a_1 = 0 = 0 - 0 = b_1 - b_1 $ .

In the third test case, it is possible to show that no sequence $ b $ of length $ 3 $ satisfies the property.

## 样例 #1

### 输入

```
5
5
4 -7 -1 5 10
1
0
3
1 10 100
4
-3 2 10 2
9
25 -171 250 174 152 242 100 -205 -258```

### 输出

```
YES
YES
NO
YES
YES```

# 题解

## 作者：SSerxhs (赞：15)

如果 $a$ 长度为 $n-1$ 那就很好做了，构造 $b_{i+1}=b_i+a_i$ 即可。

在这种情况下，如果有某一段区间 $[l,r]$ 满足 $\sum\limits_{i=l}^ra_i=a_n$，那么$b_r-b_{l-1}=a_n$。如果视为 $b_{l-1}-b_r=-a_n$，可以注意到这其实就是一个总边权为 $0$ 的环。

考虑最终序列 $b_n$，若 $b_x-b_y=a_i$ 则从连边 $x\xrightarrow{a_i} y$，那么不考虑方向，$n$ 个点 $n$ 条边的图上一定有环。同时，只要存在这样的一个环，就说明构造出了答案。

考虑将部分环边重定向，即 $x\xrightarrow{a_i} y$ 改为  $y\xrightarrow{-a_i} x$，必定可以改造为考虑方向的环。换句话说，存在一个子集使得部分元素变为相反数后总和为 $0$。搜索即可。

```cpp
	read(T);
	while (T--)
	{
		read(n);m=1<<n;
		read(a-1,n);
		sort(a,a+n);
		for (i=0;i<n;i++) if (a[i]==0) break;
		if (i<n) {puts("YES");continue;}
		for (i=0;i+1<n;i++) if (a[i]==a[i+1]) break;
		if (i+1<n) {puts("YES");continue;}q=0;
		dfs(0,0,0);
		sort(b,b+q);
		if (*lower_bound(b,b+q,0)==0) puts("YES"); else puts("NO");
	}
    ```

---

## 作者：灵茶山艾府 (赞：14)

由于 $a_i$ 可以由 $b$ 的任意两元素相减表示，不妨将 $a$ 中的部分元素取反，记新数组为 $a'$。

设 $b_1=0$，将 $b$ 视作 $a'$ 的前 $n-1$ 个元素的前缀和。

若 $a'$ 的前 $n-1$ 个元素中存在一个子数组 $a'[l\cdots r]$，其区间和等于 $a'_n$，由于 $b$ 是前缀和，所以 $a'_n$ 也能用 $b$ 的两个元素相减表示。

写成等式就是 $a'_l+...+a'_r=a'_n$

移项得 $a'_l+...+a'_r-a'_n=0$

实际上，由于 $a'$ 的元素既可以随意取反，也可以随意调换顺序，我们相当于是在 $a'$ 中寻找一个子集，其元素和为 $0$。

因此得出结论：需要在 $a$ 中找到一个子集，该子集的部分元素取反后，能够使该子集元素和为 $0$。若能找到这样的子集则输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

进一步地，我们只需要判断 $a$ 中是否存在两个子集，其子集和相等就行了。

简单地证明一下：

设这两个子集为 $A$ 和 $B$，若有 $\sum A=\sum B$，移项得 $\sum A-\sum B=0$。

注意，若 $A$ 和 $B$ 有相同的元素，会在上式中消去。消去后的剩余部分就是 $a$ 的一个子集，其中部分元素取反，且该子集和为 $0$，这正是我们需要寻找的。

AC 代码：(Golang)

```go
package main
import ."fmt"

func main() {
	var T, n int
	for Scan(&T); T > 0; T-- {
		Scan(&n)
		a := make([]int, n)
		for i := range a {
			Scan(&a[i])
		}
		set := map[int]bool{}
		for i := 0; i < 1<<n; i++ {
			sum := 0
			for j, v := range a {
				sum += i >> j & 1 * v
			}
			set[sum] = true
		}
		if len(set) < 1<<n { // 至少有两个子集和相同
			Println("YES")
		} else {
			Println("NO")
		}
	}
}
```

---

## 作者：_ZML_ (赞：4)

# CF1552D题解
## 思路 
首先，$a_i$ 的正负不重要，如果 $a_i=b_j-b_k$，那么就有 $-a_i=b_k-b_j$，读入时将 $a_i$ 全部转化为正数。

若满足 $a_i+a_j+\ldots+a_k$，那么就可以构造出 $b$ 序列，否则不行。

从左到右遍历一遍 $a$ 序列，动态规划推出所有可以组成的和，并判断是否满足上式，时间复杂度 $O(T\times n\times \max(a_i))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T,n,dp[N],a[20];

void solve(){
	for(int i=0;i<N;i++) dp[i]=0;
	cin>>n; dp[0]=1; bool flag=false;
	for(int i=0;i<n;i++){ cin>>a[i]; a[i]=a[i]<0?-a[i]:a[i]; }
	for(int i=0;i<n;i++)
		for(int j=N-1-a[i];j>=0;j--)
			if(dp[j]){
				if(dp[j+a[i]]==1) flag=true;
				else dp[j+a[i]]=1;
			}
	cout<<(flag?"YES\n":"NO\n");
}
-
signed main(){
	ios::sync_with_stdio(false);
	for(cin>>T;T;T--) solve();
}

```

现在抛出一个不难验证的结论：若   $a_i\;\mathcal{op}\;a_j\;\mathcal{op}\ldots\;a_k\;\mathcal{op} \;a_l=0$ （$op$ 为 $+$ 或 $-$ ）
那么就可以构造出序列 $b$，否则不能。
那么对于 $a$ 序列中的所有数，有三种情况：

1. $a_i$ 不在上面式子中。
2. $a_i$ 在上式中，$op$为 $+$。
3. $a_i$ 在上式中，$op$ 为 $-$。

共 $3^n-1$ 种状态（因为不能全部不在上式中，所以减去 $1$ 种情况）。

遍历 $1$ 次这种状态，若有一种情况符合上式，那么就输出 ``yes``，时间复杂度 $O(n\times3^n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[20];

void solve(){
	cin>>n; int k=pow(3,n);
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=1;i<k;i++){
		int sum=0,tk=i;
		for(int j=0;j<n;j++){
			int s=tk%3; tk/=3;
			if(s==2) s=-1;
			sum+=s*a[j];
		}
		if(sum==0) return (void)(cout<<"YES\n");
	}
	cout<<"NO\n";
}

signed main(){
	ios::sync_with_stdio(false);
	for(cin>>T;T;T--) solve();
}
```


---

## 作者：123zbk (赞：3)

因为 $a_i=b_j-b_k=-(b_k-b_j)$，所以 $a$ 数组的正负可以随意变动。我们直接将 $a_i$ 全部变为正数。

首先考虑如果 $a$ 数组是 $n-1$ 个数，那么直接构造 $b_{i+1}=a_i+b_i$ 即可。所以 $b$ 数组相当于一个前缀和。

在这种情况下，如果存在区间 $[l,r]$，满足 $\sum\limits_{i=l}^ra_i=a_n$，那么 $a_n=b_r-b_{l-1}$，就可以构造出来。

所以本题就是询问在数组 $a$ 中是否存在一个数，使它是其他任意几个数的和。

直接 dp，推出所有可以组成的和。每次循环 $i$ 和值域 $j$，如果当前 $a_i$ 已经被合成，或者 $a_i$ 加上一个合法的值域 $j$ 也被合成过，那么就一定能构造出 $b$ 数组。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int T,n,a[101],sum,dp[maxn],ok;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ok=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			a[i]=abs(a[i]);
		}
		memset(dp,0,sizeof(dp));
		dp[0]=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=maxn-a[i]-1;j>=0;j--)
			{
				if(dp[j])
				{
					if(dp[j+a[i]])
					{
						ok=1;
						break;
					}
					dp[j+a[i]]=1;
				}
			}
		}
		puts(ok==1?"YES":"NO");
	}
	return 0;
} 
```

---

## 作者：AMlhd (赞：1)

### 思路

题目要求构造一个序列 $b_1,b_2,\dots,b_n$，使得对于每个 $a_i$ 都存在两个 $b$ 的元素满足

$$
a_i=b_j-b_k
$$

一个关键观察是：\
若存在一组 $\delta_i\in\{-1,0,1\}$（不全为零），使得

$$
\sum_{i=1}^{n}\delta_i\cdot a_i=0
$$

成立，则可以构造出合适的 $b$ 序列。实际上，对于每个下标 $p$，我们考察是否存在一组 $\delta_i\in\{-1,0,1\}$（对于 $i\neq p$），使得

$$
\sum_{i\neq p}\delta_i\cdot a_i=a_p
$$

若存在这样的组合，则答案为 `YES`。由于 $n\le10$，暴力枚举每个下标 $p$ 对应的所有可能组合是可行的。

### 代码

```cpp
#include <bits/stdc++.h>

#define N 110

using namespace std;

int T;
int n;
int a[N];
int sta[N];
bool flag;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

inline void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

inline void writeln(int x) {
    write(x);
    putchar('\n');
}

inline void dfs(int now, int x, int p) {
    if(now >= n + 1) {
        int sum = 0;
        for(int i = 1; i <= n; ++i) {
            if(i != p)
                sum += a[i] * sta[i];
        }
        if(sum == x) {
            flag = 1;
        }
        return;
    }
    for(int i = -1; i <= 1; ++i) {
        sta[now] = i;
        dfs(now + 1, x, p);
    }
}

inline bool find(int x, int p) {
    flag = 0;
    dfs(1, x, p);
    return flag;
}

inline void solve() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        a[i] = read();
    }
    for(int i = 1; i <= n; ++i) {
        if(find(a[i], i)) {
            puts("YES");
            return;
        }
    }
    puts("NO");
}

int main() {

    T = read();
    while(T--) {
        solve();
    }

    return 0;
}
```

由于 $n \le 10$ 较小，暴力搜索的复杂度 $O(n \times 3 ^ n)$ 完全可接受。

---

## 作者：Crosser (赞：1)

看起来很难仔细想想其实很容易感性理解的题。

我们考虑一个图论模型，如果 $b_j-b_k=a_i$，那么连 $(j,k)$ 为一条无向边。如果图中出现了一个长度为 $n$ 的链 $x_1 \leftrightarrow x_2 \leftrightarrow \dots \leftrightarrow x_n$，我们一定可以确定 $x_1$ 和 $x_n$ 之间的关系。换句话来说，在这张图中，已经无法人为的添加任何一条边，否则都有可能会与现有条件产生冲突。

然而现在题目就是构造基环树，考虑加入一条边不会冲突当且仅当它所在的环没有产生冲突，其它的条件都不会产生冲突。返回定义看什么时候产生环，即：$b_{x_1}-b_{x_2}\in a,b_{x_2}-b_{x_3}\in a,\dots,b_{x_k}-b_{x_1}\in a$。

因为 $b_{x_1}-b_{x_2}+b_{x_2}-b_{x_3}+\dots+b_{x_k}-b_{x_1}=0$，所以题目转化为：对 $a$ 的每个元素任意取正负，是否存在一个 $a$ 的子集和为 $0$。

那么这个问题相当于 $a$ 所有元素取绝对值后是否存在两个和一样的子集，枚举子集即可。复杂度 $\mathcal O(T2^nn)$ 不会炸。

```cpp
int solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int s = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x = abs(x);
        a[i] = x;
    }
    int tmp = 0;
    map<int, int> mp;
    for(int i = 0; i < (1 << n); i++) {
        for(int w = 0; w < n; w++) {
            if((i >> w) & 1) s += a[w];
        }
        if(mp[s]) return puts("YES");
        mp[s] = 1;
        s = 0;
    }
    puts("NO");
    return 0;
}
```

---

## 作者：AirQwQ (赞：1)

由于 $a_i$ 由 $b_i$ 中任意两元素相减表示，可以将 $a$ 中部分元素取反，记为 $a'$。

设 $b_1=0,b_i=b_{i-1}+a'_{i-1},i \ge 2$

这样可以表示 $a_1,a_{n-1}$。

一种暴力的想法是枚举 $a'$ 的取反状态,并判断能否用 $b$ 凑出 $a_n$。

这样做是 $O(n^22^n)$，显然可以通过此题。

---

## 作者：RockyYue (赞：0)

### 题意

给定序列 $a_{1\dots n}$，问是否可以构造出序列 $b_{1\dots n}$ 使得对于所有 $a_i$ 都存在 $b$ 中两数（可以相等）之差为其 $a_i$。

其中 $n\le 10,|a_i|\le 10^5$。

### 题解

首先若 $a$ 长度为 $n-1$ 是易于构造的，对于 $i>1$，$b_1-b_i=a_{i-1}$ 即可。

但 $a$ 的长度为 $n$，就需要额外表示出一个数，可以联想到建图构造环。

这里假设 $b$ 的构造存在。若 $a_i=b_j-b_k$，从点 $j$ 向点 $k$ 连边（对于每个 $i$，连且仅连一条边）。

这个图中若存在环，则可以表示出多出的一个 $a$。这里的环不用要求边的方向，重边自环亦为合法。

若将这些边统一定向，可得环中所有 $a$ 之和为 $0$。但是统一定向的代价就是需要用部分 $a$ 取反后的结果才能构造出这个环。

那么如果 $a$ 中一个子集中部分取反后和为 $0$，可以构造；否则不行，枚举此子集与其中取反的部分再进行验证，复杂度为 $O(4^n\times n)$。

若不存在该构造，即 $b$ 关系不存在环，则 $n$ 个点至多 $n-1$ 条边，即至多表示 $a$ 中 $n-1$ 个数，无解。

---

