# [JOI Open 2022] 跷跷板 / Seesaw

## 题目背景

**译自 [JOI Open 2022](https://contests.ioi-jp.org/open-2022/index.html) T1. [シーソー](http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2022/seesaw/2022-open-seesaw-statement.pdf) / [Seesaw](http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2022/seesaw/2022-open-seesaw-statement-en.pdf)。**

## 题目描述

一根长度为 ${10}^9$ 的直杆从左到右水平放置。你可以忽略这根杆的重量。共有 $N$ 个砝码挂在这根杆上，每个砝码的质量为一单位。这 $N$ 个砝码的位置两两不同。第 $i$（$1 \le i \le N$）个砝码的位置为 $A_i$。即，第 $i$ 个砝码到直杆最左端的距离为 $A_i$。

最开始，我们有一个宽度为 $w$ 的箱子。我们可以把这根杆子放在箱子上，支撑起杆从 $l$ 到 $r$（$0 \le l < r \le {10}^9$）的部分（包括两端），即，从杆上位置为 $l$ 到杆上位置为 $r$ 的区间。这里需要满足 $r = l + w$。之后我们不可以改变 $l$ 和 $r$ 的值。

接下来，我们去掉挂在杆上最左端或最右端的砝码。我们需要重复这个操作 $N - 1$ 次。在这个过程中，包括初始状态和最终状态，挂在杆上的所有砝码重心都需要保持在 $l$ 到 $r$ 之间（包括两端）。如果杆上挂有 $m$ 个砝码，位置分别为 $b_1, b_2, \ldots, b_m$，那么重心位置为 $\frac{b_1 + b_2 + \cdots + b_m}{m}$。

给定 $N$ 和这 $N$ 个砝码的位置 $A_1, A_2, \ldots, A_N$，写一个程序计算箱子的最小可能宽度 $w$。

## 说明/提示

**【样例解释 \#1】**

可让箱子的宽度为 $\frac{5}{6}$。我们令 $l = \frac{3}{2}, r = \frac{7}{3}$。进行如下操作：

- 最初，重心位置为 $\frac{7}{3}$。
- 第一次操作，我们去掉最右端的砝码（位置为 $4$ 的砝码）。重心位置变为 $\frac{3}{2}$。
- 第二次操作，我们去掉最左端的砝码（位置为 $1$ 的砝码）。重心位置变为 $2$。

在这个过程中，重心始终保持在 $l$ 到 $r$ 范围中。

因为箱子的宽度不会小于 $\frac{5}{6}$，因此输出 $\frac{5}{6}$ 的小数形式。

这组样例满足所有子任务的限制。

----

**【样例解释 \#2】**

这组样例满足所有子任务的限制。

----

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（1 分）：$N \le 20$。
- 子任务 2（33 分）：$N \le 100$。
- 子任务 3（33 分）：$N \le 2000$。
- 子任务 4（33 分）：无特殊限制。

对于所有数据，满足 $2 \le N \le 2 \times 10^5$，$0 \le A_1 < A_2 < \cdots < A_N \le {10}^9$。

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
0.8333333333
```

## 样例 #2

### 输入

```
6
1 2 5 6 8 9
```

### 输出

```
1.166666667
```

# 题解

## 作者：qbf！ (赞：9)

首先有 $mid=\dfrac{\sum_{i=1}^na_i}n$ 必定被包含。

对于每个 $i$，我们找到操作 $i$ 次后重心位置 $\le mid$ 且最大的区间，设其重心为 $L_i$，以及重心位置 $\ge mid$ 且最小的区间，设其重心为 $R_i$。

我们大胆猜测题目相当于对每个 $i$ 选择 $c_i=L_i$ 或 $c_i=R_i$，然后最小化序列 $c$ 的极差，证明如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/b5qm4ieu.png)

假设 $L_i$ 对应的区间为 $[l,r-1]$，$R_i$ 对应的区间为 $[l+1,r]$，那么容易发现 $[l+1,r-1]$ 必定是 $L_{i+1}$ 或 $R_{i+1}$，假设它是 $L_{i+1}$：

- 假设我们选择了 $c_i=L_i$ 且 $c_{i+1}=L_{i+1}$，那么我们显然可以从 $[l,r-1]$ 走到 $[l+1,r-1]$。
- 假设我们选择了 $c_i=L_i$ 且 $c_{i+1}=R_{i+1}$，那么由于 $L_i<L_{i+1}$，故我们显然可以把 $c_{i+1}$ 调整成 $L_{i+1}$ 而不会使答案更劣。
- 假设我们选择了 $c_i=R_i$ 且 $c_{i+1}=R_{i+1}$，则我们显然可以从 $[l+1,r]$ 走到 $[l+2,r]$。
- 假设我们选择了 $c_i=R_i$ 且 $c_{i+1}=L_{i+1}$，则我们显然可以从 $[l+1,r]$ 走到 $[l+1,r-1]$。

$R_{i+1}$ 的情况是同理的。

因此我们只需将所有 $[L_i,R_i]$ 排序，然后从小到大枚举 $c$ 序列的最小值，维护 $c$ 序列的最大值即可，时间复杂度 $\mathcal O(n\log n)$。

---

## 作者：Union_of_Britain (赞：1)

$O\left(n^2 \log n\right)$（存疑）爆了。

设初始重心为 $P$，对于一个答案 $[l, r]$，设 $L_1=P-l$,则 $r$ 大致是关于 $L_1$ 增加而减小的，但是答案 $L_1+r-P$ 却被发现不具有凸性或单峰等性质。

但是一个 $L_1$ 代表 $r^{\prime}<r$ 均（可以被认为）合法。这意味着，$\left\{L_1, r\right\}$ 应该成阶梯状。根据 Quickhull 的思想，只需要把阶梯处的凹位置全都遍历一边就可以了。这可以通过二分找下一个 $r$ 不同的位置来实现。设有 $K$ 个凹点，那么时间复杂度是 $O(n K \log n)$。随机数据下，$n=2 \times 10^5$ 大概 $K=70$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double 
const int maxn=2e5+5;
int n;
db a[maxn],P,s[maxn],ans=0;
inline db Calc(db L1){
	int l=1,r=n;
	db mx=P;
	while(r-l>0){
		while(r-l+1>1&&(s[r-1]-s[l-1])>(P-L1)*(r-l))--r;
		if(r-l+1==1)break;
		l++;
		mx=max(mx,(s[r]-s[l-1])/(r-l+1));
	}
	return mx-P;
}
priority_queue<pair<db,db> > Q;
signed main(){
	// freopen("balance.in","r",stdin);
	// freopen("balance.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],P+=a[i],s[i]=s[i-1]+a[i];
	if(n==2){
		printf("%.10lf\n",(a[2]-a[1])/2.0);
		return 0;
	}
	P/=n;
	db cur=0,curc=Calc(0),ans=curc;
	int cnt=0;
	while(1){
		++cnt;
		db L=cur,R=1e9,res=-1,cres;
		while(Q.size()&&(fabs(curc-Q.top().second)<1e-6||(-Q.top().first)<=cur))Q.pop();
		if(Q.size())R=-Q.top().first;
		while(R-L>max(L,1.0)*1e-9){
			db mid=(L+R)/2.0,r=Calc(mid);
			if(R-L>1e-3)Q.push({-mid,r});
			if(fabs(r-curc)>1e-6)res=mid,R=mid,cres=r;
			else L=mid;
		}
		if(res!=-1)ans=min(ans,cres+res),cur=res,curc=cres;
		else break;
	}
	// cout<<cnt<<endl;
	printf("%.10lf\n",ans);
	return 0;
}```

---

## 作者：zzy0618 (赞：0)

考虑删砝码的过程，若无论删 $[l,r]$ 哪边都不行，一定是 $[l,r-1]$ 和 $[l+1,r]$ 重心不在区间上。

故有解的充要条件为对于每一个 $i\in [1,n]$，都存在一个长度为 $i$ 的区间，其重心在答案区间上。必要性是显然的，充分性的话如果 $i,i-1$ 两个长度都有合法的区间，$i-1$ 的区间中必有长度为 $i$ 的子区间，因为如果不是将其移动到 $i$ 子区间内必然更居中于答案区间。

一种暴力的方法是将所有长度的区间抠出来，枚举重心最小值，记录重心最大值，然后就有 $O(n^2\log n)$ 的做法。


设 $[1,n]$ 区间的重心为 $mid$，无论是猜测还是观察都能想到我们会选重心更接近 $mid$ 的区间。而这里的接近是 $\le mid$ 中最大的以及 $\ge mid$ 中最小的。

证明大概是这样，如图红色为重心，假设我们向右选了第三条远离重心的我们如过回头向左，那么白白使右端点 $\max$ 增加，如果继续向右那就答案左端点不变，右端点还在增加。不如直接选第四条重心靠近 $mid$ 的区间。

![](https://cdn.luogu.com.cn/upload/image_hosting/xi91xpe7.png)

这样有用的区间被控在了 $O(n)$ 范围内。复杂度 $O(n\log n)$。

笔者实现较为简单粗暴，直接 $n$ 个队列和一个优先队列，实际会有较大常数。

```cpp
#include <bits/stdc++.h>
#define dbz double
#define pii pair<int, int>
using namespace std;
const int N = 2e5 + 3;
int n;
dbz a[N], s[N], mx, ans = 1e18;
int L[N], R[N];
queue<dbz> q[N];
priority_queue<pair<dbz, int>> Q;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], s[i] = s[i - 1] + a[i];
    dbz mid = 1.0 * s[n] / n;
    L[n] = 1, R[n] = n;
    q[n].push(mid);
    Q.push(make_pair(-mid, n));
    mx = max(mx, mid);
    for (int i = n - 1; i >= 1; --i) {
        R[i] = n;
        for (int l = L[i + 1], r = l + i - 1; r <= R[i + 1]; ++l, ++r) {
            q[i].push(1.0 * (s[r] - s[l - 1]) / i);
            if (1.0 * (s[r] - s[l - 1]) / i <= mid)
                L[i] = max(L[i], l);
            else
                R[i] = min(R[i], r);
        }
        Q.push(make_pair(-q[i].front(), i));
        mx = max(mx, q[i].front());
    }
    while (1) {
        int u = Q.top().second;
        ans = min(ans, mx + Q.top().first);
        q[u].pop(), Q.pop();
        if (q[u].empty())
            break;
        mx = max(mx, q[u].front());
        Q.push(make_pair(-q[u].front(), u));
    }
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}
```

---

