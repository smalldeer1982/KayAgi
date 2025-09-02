# [ABC395F] Smooth Occlusion

## 题目描述

高桥君共有 $2N$ 颗牙齿，其中 $N$ 颗是上牙，剩余的 $N$ 颗是下牙。

左数第 $i$ 颗（$1 \leq i \leq N$）上牙的长度为 $U_i$，左数第 $i$ 颗（$1 \leq i \leq N$）下牙的长度为 $D_i$。

当高桥君的牙齿满足以下两个条件时，称为「良好咬合」：
1. 存在一个整数 $H$，使得对于所有 $1 \leq i \leq N$，有 $U_i + D_i = H$。
2. 对于所有 $1 \leq i < N$，有 $|U_i - U_{i+1}| \leq X$。

高桥君可以执行以下操作任意次：
- 支付 $1$ 日元使用磨牙工具，选择一个长度为正的牙齿，将其长度减少 $1$。

除上述操作外，无法通过其他方式改变牙齿长度。请计算高桥君达成良好咬合所需支付的最小金额。

## 说明/提示

### 约束条件
- $2 \leq N \leq 2 \times 10^5$
- $1 \leq U_i \leq 10^9$（$1 \leq i \leq N$）
- $1 \leq D_i \leq 10^9$（$1 \leq i \leq N$）
- $1 \leq X \leq 10^9$
- 输入均为整数

### 样例解释 1
初始牙齿长度示意图（图片链接略）。通过以下调整可达成良好咬合（调整后示意图略），总成本为 $15$ 日元。无法以 $14$ 日元或更少达成，因此输出 `15`。

### 样例解释 2
存在牙齿初始状态已满足良好咬合的情况。

### 样例解释 3
答案可能超过 32 位整数范围，需注意处理大数。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4 3
3 1
4 1
5 9
2 6```

### 输出

```
15```

## 样例 #2

### 输入

```
4 1000000000
3 3
3 3
3 3
3 3```

### 输出

```
0```

## 样例 #3

### 输入

```
4 1
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000
1 1```

### 输出

```
5999999994```

## 样例 #4

### 输入

```
15 128
748 169
586 329
972 529
432 519
408 587
138 249
656 114
632 299
984 755
404 772
155 506
832 854
353 465
387 374
567 385```

### 输出

```
9460```

# 题解

## 作者：cwd2023 (赞：35)

## AT_abc395_f [ABC395F] Smooth Occlusion 题解
### by cwd2023


---

### 思路：
其实本题有多种做法，例如二分，差分约束等，这里介绍一种十分简洁的~~且只有十行代码的~~ $O(n)$ 做法。

首先，我们想让磨掉的牙最少，就等于保留尽可能多的牙,所以设 $h$ 表示可保留牙的最大值，设 $sum$ 为所有牙齿的长度和。

先考虑题目中的第二个条件，我们可以设 $miu$ 为上牙可保留的最大值。那么，由于磨牙只能减少长度，所以当新输入的上牙长度小于 $miu+x$ 时，我们就可以更新 $miu$ 使其更小，否则不更新。

那么，为了保证题目中的第一个条件，我们再设 $mid$ 表示下牙可保留的最大值，且 $mid$ 和 $miu$ 必须同步更新，这样保证了它们的和相等。

最后，记得将 $h$ 和 $miu$ 以及 $mid$ 赋上初始值。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,u,d,sum,h=2e18,miu=1e18,mid=1e18,x;
int main() {
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>x;
	for(ll i=1;i<=n;i++){
		cin>>u>>d;
		sum+=(u+d);
		miu=min(miu+x,u);
		mid=min(mid+x,d);
		h=min(h,miu+mid);
	}
	cout<<sum-n*h<<"\n";
	return 0;
}
```
最后，希望本篇题解对你有所帮助，感谢观看。

**望管理员通过！**

---

## 作者：Moya_Rao (赞：13)

# 题目大意

给定两个长度为 $n$ 的序列 $a$ 和 $b$，以及一个标准值 $k$。

如果说这两个序列 $a$ 和 $b$ 匹配，当且仅当：
- 所有 $a_i + b_i$ 均相等。
- $a_i \ge 0$ 并且 $b_i \ge 0$。
- 对于每个 $1 \le i < n$，都有 $|a_i-a_{i+1}| \le k$。

现在你可以执行若干次操作（可以一次都不执行）：  
在序列 $a$ 或序列 $b$ 中任选一个大于 $0$ 的数值，将其的数值减去 $1$。

请问至少要执行多少次操作，才能使 $a$ 和 $b$ 匹配？请求出这个最少执行次数。

$2 \le n \le 2 \times 10^5$，$1 \le a_i,b_i,k \le 10^9$。

更加详细的题面请看[原题](https://atcoder.jp/contests/abc395/tasks/abc395_f)。

# 思路

考虑到选择 $a_i + b_i$ 最小的那一组的总和作为最终的标定物，使每组 $a_i + b_i$ 都变成这个值。

这个想法是好的，但是有可能不满足“对于每个 $1 \le i < n$，都有 $|a_i-a_{i+1}| \le k$”这个条件。怎么办？很简单，我们可以一开始就处理一下，使得最初的序列 $a$ 就已经满足这个条件了。那么之后去做减法的时候，总有一种办法可以保持相对差值相等的，是吧？

那么现在的问题就是如何在一开始的时候经过处理，使得最初的序列 $a$ 满足条件呢？很简单，我们写一个循环，遍历相邻的两个值 $a_i$ 和 $a_{i+1}$，然后看看它们俩的差值是否大于 $k$，如果是的，那么就调整一下，使得差值变成 $k$。

不过——真的只要处理序列 $a$ 吗？当然不是的，$b$ 数组也要处理。为什么啊？明明条件里只有序列 $a$ 啊！让我告诉你吧，因为还有一个和相等的条件呀，所以说其实上，$b$ 数组也是满足的，对吧？所以一开始，也需要处理 $b$ 数组，使得它也满足情况。

搞完这个处理，我们就可以安安心心的求出 $a_i + b_i$ 的最小值 $sum$，然后分别用 $a_i + b_i$ 减去 $sum$，算出的值累加到 $ans$ 里边就可以啦。

注意了，$ans$ 要开 `long long` 哟，不然会 WA 的！

# 代码
你们爱看的代码来咯！  
这代码非常短，而且极其简洁，你们可以配合着思路来看。  
最后留下一个[提交记录](https://atcoder.jp/contests/abc395/submissions/63320784)，告诉你们，我的代码是可以放心看的哟！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
long long n,k,a[N],b[N],sum,ans;
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
    for(int i=1;i<n;i++){
        if(a[i]-a[i+1]>k)
            ans+=a[i]-a[i+1]-k,a[i]=a[i+1]+k;
        if(a[i+1]-a[i]>k)
            ans+=a[i+1]-a[i]-k,a[i+1]=a[i]+k;
        if(b[i]-b[i+1]>k)
            ans+=b[i]-b[i+1]-k,b[i]=b[i+1]+k;
        if(b[i+1]-b[i]>k)
            ans+=b[i+1]-b[i]-k,b[i+1]=b[i]+k;
    }
    sum=0x3f3f3f3f3f3f3f3f;
    for(int i=1;i<=n;i++)sum=min(sum,a[i]+b[i]);
    for(int i=1;i<=n;i++)ans+=a[i]+b[i]-sum;
    cout<<ans;
    return 0;
}
```

如果本篇题解对你有帮助，请你留下一个小小的赞，万分感谢！

---

## 作者：Lovely_yhb (赞：11)

### 题意

有两个长度为 $n$ 的序列 $u_i$ 和 $d_i$，每次操作可以把一个正数减一，问最少经过次操作使得：

1. 存在 $H$ 使所有 $u_i+d_i=H$。
2. 序列中相邻两个数的差小于等于 $x$。

### 思路

这道题可以二分答案去做。

只需要确定 $H$，答案就是所有数字的总和减去 $H\times n$。

二分答案 $H$，下界是 $0$，上界是 $\min(u_i+d_i)$。

设 $U_i,D_i$ 分别表示操作完后的 $u_i$ 和 $d_i$。因为 $U_i+D_i=H$，所以只要一个确定了，另一个也确定，那我们就只考虑 $U_i$。

因为每次操作只能减少，所以有 $U_i\le u_i,D_i\le d_i$。

对于 $D_i=H-U_i\le d_i$ 推出 $U_i\ge H-d_i$。

又因为每个数都要大于等于 $0$ 且小于等于 $H$。所以 $U_i$ 的范围是区间 $[\max(0,H-d_i),\min(u_i,H)]$。

对每个 $U_i$，记录它的取值区间左端点 $L$ 和右端点 $R$。

第 $i$ 个数的取值区间必须是两个约束的交集：
1. 自身的区间 $[\max(0,H-d_i),\min(u_i,H)]$。
2. 能够和前一个数的差不超过 $x$，即必须落在区间 $[L_{i-1}-x,R_{i-1}+x]$ 内。

因此，对每个 $i$，$L_i=\max(0,H-d_i,L_{i-1}-x),R_i=\min(H,u_i,R_{i-1}+x)$。

如果对于某个 $i$，$L_i>R_i$，说明不合法。check 函数就是这样写的。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,x,u[N],d[N];
bool check(int H) {
	int L=max(0ll,H-d[1]),R=min(u[1],H);
	if(L>R) return 0;
	for(int i=2;i<=n;i++){
		int curL=max(0ll,H-d[i]),curR=min(u[i],H);
		curL=max(curL,L-x),curR=min(curR,R+x);
		if(curL>curR) return 0;
		L=curL,R=curR;
	}
	return 1;
}
signed main() {
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>x;
	int sum=0;
	for(int i=1; i<=n; i++) cin>>u[i]>>d[i];
	for(int i=1; i<=n; i++) sum+=u[i]+d[i];
	int maxn=1145141919810ll;
	for(int i=1; i<=n; i++) maxn=min(maxn,u[i]+d[i]);
	int l=0,r=maxn,anss=0;
	while(l<=r) {
		int mid=(l+r)/2;
		if(check(mid)) anss=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<sum-n*anss;
	return 0;
}
```

---

## 作者：gesong (赞：11)

题目传送门：[[ABC395F] Smooth Occlusion](https://www.luogu.com.cn/problem/AT_abc395_f)。
# 思路

本题解的 $a,b$ 数组表示题目中的 $U,D$ 数组，$d$ 变量为题目中的 $X$ 变量。

我们如果知道 $H$ 的值，我们就可以快速求出答案。

根据贪心，我们希望在合法情况下 $H$ 要尽量的大，我们考虑使用二分做法求出这个 $H$。

考虑如何判断一个 $H$ 是否是合法的，将 $i-1$ 的上牙齿合法区间设为 $[l,r]$，首先我们的区间可以扩展成 $[l-d,r+d]$，我们考虑这个牙齿的限制，首先我们最大值一定为 $a_i$ 因为我们不能再让它变长，同理我们的最小值为 $H-b_i$，因为我们的 $b_i$ 已经取到了最大的，因此区间即为 $[\max(l-d,H-b_i),\min(r+d,a_i)]$。

这时只要我们有一个区间不合法（左端点比右端点大）就不合法，否则合法，二分之后输出即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],b[N],n,d;
inline int max(int a,int b,int c){
	return max(max(a,b),c);
}
inline int min(int a,int b,int c){
	return min(min(a,b),c);
}
inline bool check(int mid){
	int l=0,r=1e18;
	for (int i=1;i<=n;i++){
		l=max(mid-b[i],l-d);
		r=min(r+d,a[i]);
		if (l>r) return 0;
	}
	return 1;
}
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	n=read(),d=read();
	int r=1e18;
	for (int i=1;i<=n;i++) a[i]=read(),b[i]=read(),r=min(r,a[i]+b[i]);
	int l=1,ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if (check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	int sum=0;
	for (int i=1;i<=n;i++) sum+=a[i]+b[i]-ans;
	cout <<sum;
    return 0;
}
// AtCoder Beginner Contest 395 & 联合省选 2025 RP++
// AtCoder Beginner Contest 395 & 联合省选 2025 RP++
// AtCoder Beginner Contest 395 & 联合省选 2025 RP++
// AtCoder Beginner Contest 395 & 联合省选 2025 RP++
// AtCoder Beginner Contest 395 & 联合省选 2025 RP++
```

---

## 作者：Laisira (赞：7)

说句闲话，这题没 B 题难。

显然 $H$ 存在最大值，以及合法情况具有单调性。最大值是 $\min_{i=1}^{n}D_i+U_i$，考虑二分 $H$，并维护一个牙齿的可能区间。具体点就是对于每个 $U_i$ 处理出他可能的值，这个值一定是个区间，所以后面的 $U_{i+1}$ 也被确定了一个自己的和关于 $U_i$ 的区间，这两个区间要取并，维护这个区间向后面做判断和转移就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define bit(x) (x&-x)
#define rep(l,r,i) for(int i=l;i<=r;i++)
#define per(l,r,i) for(int i=l;i>=r;i--)
using namespace std;
#define int long long 
int N;
int X;
vector<int> U, D;
vector<int> sum_UD;
bool is_feasible(int H) {
    int curr_low = max(H - D[0], 0LL);
    int curr_high = min(U[0], H);
    if (curr_low > curr_high) return false;
    rep(1,N-1,i) {
        int a = max(H-D[i], 0LL);
        int b = min(U[i],H);
        int new_low = max(a,curr_low-X);
        int new_high = min(b,curr_high+X);
        if (new_low > new_high) return false;
        curr_low = new_low;
        curr_high = new_high;
    }
    return true;
}
signed main() {
    cin>>N>>X;
    U.resize(N);
    D.resize(N);
    sum_UD.resize(N);
    int H_max = LONG_LONG_MAX;
    rep(0,N-1,i) {
        cin>>U[i]>>D[i];
        sum_UD[i] = U[i] + D[i];
        if (sum_UD[i] < H_max)
            H_max = sum_UD[i];
    }
    int left = 0, right = H_max;
    int best_H = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (is_feasible(mid)) {
            best_H = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    int total_sum = 0;
    for (int s:sum_UD) {
        total_sum += s;
    }
    int cost = total_sum - best_H * N;
    cout<<cost;
    return 0;
}
```

---

## 作者：fish_love_cat (赞：6)

巨嘴高桥 /jk

---

先把第一条性质做了，依题意得操作只减不加，那么我们可以不动较小值，把大的数磨下来就行了。

可是这样子直接做贪心应该是 $O(n^2)$ 的，因为两边都要跑一遍判断。

考虑优化。

首先如果 $U_i<U_{i+1}-x$，直接磨后者磨到合法为止显然优秀，此时对 $U_{i+1}$ 动态进行修改。时间 $O(1)$。

如果 $U_{i+1}<U_{i}-x$，我们不断往前找不操作前面只磨当前还能够合法的点，对其进行修改。

注意到改了当前点以后后面的点大多也需要同时进行修改，然而遍历时间复杂度依然会写成 $O(n^2)$，所以选择利用差分来维护修改。

同时又注意到直接往前找数一样会写成 $O(n^2)$，所以选择利用链表直接跳，综合 $O(n)$。

那么就可以找到一个操作次数最少可以做出来的合法 $U$ 序列了。

---

接下来处理第二个限制。

我们把当前牙齿对长度和算出来，然后全部磨到一致就行了。

这里的 $U$ 取的是上文处理后的 $U$。

---

其实有一个问题，就是如何保证处理后的 $U$ 放过来处理第二个性质时也是最优解呢？

观察发现，由于 $U_i$ 有额外限制，所以处理第二个性质时会优先照顾 $D_i$，然后 $D_i$ 被磨没了才去磨 $U_i$。

而当 $U_i$ 需要被磨时，必然保证存在一个数字 $j$ 使得 $U_j$ 也要被磨且 $U_j>U_{j\pm1}+D_{j\pm1}$。

同时我们又知道 $U_j-U_{j\pm1}\le x$，所以将 $U_j$ 磨下来并不违反限制一。

以此类推，所以合并起来磨并不违反限制。

那么取处理后的最优 $U$ 显然更为不错。

---

南山破机房打不开 AT，所以代码就不放了。

实现非常轻松大家应该都不会写挂吧。

~~发现差分写挂赛后 7min 过 F 逆向上分是谁我不说 /cf~~

---

## 作者：Dtw_ (赞：4)

## 题意
给你 $2n$ 个数，$a_1,a_2,\cdots,a_n$ 以及 $b_1,b_2,\cdots,b_n$。

你要找到一个数 $h$，使得所有的 $a_i+b_i=h$ 且 $\left | a_i - a_{i - 1}\right | \leq x$。

你可以使任意的 $a_i$ 或 $b_i$ 减少 $1$，代价为 $1$。求满足要求的最小代价。
## Solution
考虑我们最终的答案应该是 $\sum_{i=1}^n a_i + b_i - h$ 那么 $h$ 越大越好，在考虑 $h$ 具有单调性，即如果 $h$ 符合要求，那么对于 $h'<h$ 肯定也符合要求。

所以我们就可以二分 $h$，然后考虑如何 check。

现在问题变为 $l_i\leq a_i\leq r_i$ 且  $\left | a_i - a_{i - 1}\right | \leq x$，看是否有合法的 $a$ 序列。

那么我们直接维护 $a_i$ 能取到的范围，然后拓展即可。

如果取不到某个 $a_i$ 就说明这个 $h$ 不行。
## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 2e5 + 10, inf = 0x3f3f3f3f;

int n, a[N], b[N], x;
ll l[N], r[N];

bool check(ll k)
{
    for (int i = 1; i <= n; i++) { ll mx = (a[i] + b[i] - k); l[i] = max(0ll, a[i] - mx), r[i] = k - max(0ll, b[i] - mx); }
    for (int i = 2; i <= n; i++) { l[i] = max(l[i], l[i - 1] - x), r[i] = min(r[i], r[i - 1] + x); if (l[i] > r[i]) return false; }
    return true;
}

int main()
{
    fst
    cin >> n >> x;
    ll l = 0, r = 2e9, res = -1;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i], r = min(1ll * (a[i] + b[i]), r);
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (check(mid)) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) ans += a[i] + b[i] - res;
    cout << ans;
    return 0;
}
```

---

## 作者：xyx404 (赞：3)

## 翻译：
高桥君有 $2 \times N$ 个牙齿，$N$ 个上排的牙齿和 $N$ 个下排的牙齿。

> 注：以下为了方便“上牙”指的是上排的牙齿，“下牙”指的是下排的牙齿。

第 $i$ 个上牙的长度为 $U_i$，第 $i$ 个下牙的长度为 $D_i$。

有个操作，需要花费一元，选择一个长度大于 $0$ 的牙齿，将其长度减少 $1$。

求使牙齿“咬合良好”的最小总费用。

牙齿“咬合良好”需要满足以下两个条件：
1. 存在一个整数 $H$，使得对于所有 $1 \le i \le N$，满足 $U_i + D_i$ 等于 $H$。
2. 对于所有 $1 \le i <  N$，满足 $\left  |U_i - U_{i+1}  \right | \le X$。


## 思路：

二分搜索。

二分寻找符合条件的最大的 $H$。

找到后计算最小费用就行了，设总费用为 $ans$，则 
$$ans=\sum_{i=1}^{N}(U_i+D_i-H)$$

### 二分查找部分：
#### 为什么可以二分 $H$ 和二分范围：
我们可以发现如果某一个 $H$ 是可行的，因为我们可以使用操作去减少牙齿的长度，所以所有比 $H$ 小的值也可能是可行的，所以我们可以发现 $H$ 是满足单调性的。

$H$ 的左边界是 $0$，因为所有牙齿的长度都为 $0$ 时一定是满足条件的；$H$ 的右边界是所有 $U_i+D_i$ 的最小值，因为需要满足 $U_i + D_i$ 等于 $H$，而我们的操作只能减少长度，不能增加长度。

#### 查询是否符合条件：
定义两个数组 $a$ 和 $b$，$a_i$ 是第 $i$ 个上牙的最小可能长度，$b_i$ 是第 $i$ 个上牙的最大可能长度。

因为必须满足 $U_i + D_i$ 等于 $H$，所以我们可以得出 $U_i$ 必须满足 $U_i=H-D_i$，由于长度至少要是 $0$，所以 $a_i=\max(0,H-D_i)$。

因为第 $i$ 个上牙的长度只有 $U_i$，而在第 $i$ 个下牙为 $0$ 时，要满足条件长度应该等于 $H$，所以 $b_i=\min(U_i,H)$。

先判断第一个上牙的范围是否合法，也就是左端点需要小于等于右端点，因为不可能会出现最大值小于最小值。

接着循环除了第一个牙齿外的其它牙齿，检查相邻上牙的差值是否满足条件。

如果所有上牙都满足条件，返回真，否则返回假。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
LL T=1,n,m,x;
LL u[int(2*1e5+10)],d[int(2*1e5+10)];
LL al[int(2*1e5+10)],bl[int(2*1e5+10)];
vector<LL>sum_ud;
bool check(LL mid){
	for(int i=0;i<n;i++){
		al[i]=max(0ll,mid-d[i]);
		bl[i]=min(u[i],mid);
	}
	LL cl=al[0],cr=bl[0];
	if(cl>cr)return 0;
	for(int i=1;i<n;i++){
		LL pl=cl,pr=cr;
		LL nl=max(al[i],pl-x),nr=min(bl[i],pr+x);
		if(nl>nr)return 0;
		cl=nl;
		cr=nr;
	}
	return 1;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	while(T--){
		cin>>n>>x;
		sum_ud.resize(n);
		for(int i=0;i<n;i++){
			cin>>u[i]>>d[i];
			sum_ud[i]=u[i]+d[i];
		}
		LL hm=*min_element(sum_ud.begin(),sum_ud.end());
		int l=0,r=hm,anss=0;
		while(l<=r){
			LL mid=l+(r-l)/2;
			if(check(mid)){
				anss=mid;l=mid+1;
			}
			else r=mid-1;
		}
		LL ans=0;
		for(int i=0;i<n;i++){
			ans+=sum_ud[i]-anss;
		}
		cout<<ans;
	}
	return 0;
}

```

---

## 作者：joe_zxq (赞：2)

涨知识了！原来高桥有 $4 \times 10^5$ 颗牙诶！原来他的牙长这样！

![](https://img.atcoder.jp/abc395/eeb6b57fa9d9b6577f264baba37644c5.png)

考虑从前往后和从后往前分别跑一次，每次遇到长度大于上一个牙齿长度加上 $X$ 的牙，就把它磨为上一个牙齿长度加上 $X$。最后设刚开始牙齿长度和为 $s$，磨完后最短上下牙长度和为 $m$，则答案为 $s-m \times N$。

这应该是此题的最简单解法吧。时间复杂度：$O(N)$。

```cpp
ll tc = 1, n, m, sum, mn = 1e18;

struct teeth {
	ll u, v;
} a[200025];

void init() {
	;
}

void solve() {
	init();
	n = read(), m = read();
	for (ll i = 1; i <= n; i++) {
		ll u = read(), v = read();
		a[i] = {u, v};
		sum += u + v;
	}
	for (ll i = 2; i <= n; i++) {
		updmin(a[i].u, a[i - 1].u + m);
	}
	for (ll i = n - 1; i >= 1; i--) {
		updmin(a[i].u, a[i + 1].u + m);
	}
	for (ll i = 1; i <= n; i++) {
		updmin(mn, a[i].u + a[i].v);
	}
	write(sum - mn * n);
}
```

---

## 作者：Union_Find (赞：2)

首先注意到，第二个限制和 $H$ 无关，所以我们可以从第二个限制入手。

注意到绝对值比较难搞，所以我们可以从小到大考虑，那么就是 $U_v - U_u \le x$，其中 $v = u - 1$ 或 $v = u + 1$。那么这就是差分约束了。当然，其实并不需要真的建图，直接向两边走即可。

而最后的答案很明显取决于 $H$，即 $ans = sumh - n \times H$。所以我们只要让 $H$ 最小即可。显而易见，$H$ 的最小值就是差分约束之后最小的和。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), x = rd(), h1[N], h2[N], dis[N], vis[N], sum, ans = 1e18;
priority_queue <pair<ll, ll> > q; 
int main(){
	for (int i = 1; i <= n; i++) h1[i] = rd(), h2[i] = rd(), sum += h1[i] + h2[i];
	for (int i = 1; i <= n; i++) q.push({-h1[i], i}), vis[i] = 0, dis[i] = h1[i];
	while (q.size()){
		ll u = q.top().second;q.pop();
		if (vis[u]) continue;vis[u] = 1;
		if (u > 1 && dis[u - 1] > dis[u] + x) dis[u - 1] = dis[u] + x, q.push({-dis[u - 1], u - 1});
		if (u < n && dis[u + 1] > dis[u] + x) dis[u + 1] = dis[u] + x, q.push({-dis[u + 1], u + 1}); 
	}for (int i = 1; i <= n; i++) ans = min(ans, dis[i] + h2[i]);
	printf ("%lld\n", sum - n * ans);
	return 0;
}

```

---

## 作者：chenhanzheapple (赞：2)

# 思路

将问题转化为：保留尽可能多的牙齿。

因此二分每个位置上的牙齿长度即可。

因为牙齿长度只能减少，因此单调性是显然的。

如何写 `check` 呢？考虑贪心，由于牙齿长度只能减少，对于左右相邻的牙齿，若长度差距大于 $X$，则只能减少长度大的那颗牙。

然后这题就做完了。

# 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,xx,sum,minn = LONG_LONG_MAX;
int u[200005],d[200005],a[200005],b[200005];
bool check(int x){
    for(int i=1;i<n;i++){
        if(u[i]-u[i+1]>xx){
            u[i] = u[i+1]+xx;
        }
        else if(u[i+1]-u[i]>xx){
            u[i+1] = u[i]+xx;
        }
    }
    for(int i=1;i<n;i++){
        if(d[i]-d[i+1]>xx){
            d[i] = d[i+1]+xx;
        }
        else if(d[i+1]-d[i]>xx){
            d[i+1] = d[i]+xx;
        }
    }
    for(int i=1;i<=n;i++){
        if(u[i]+d[i]<x){
            for(int j=1;j<=n;j++){
                u[j] = a[j],d[j] = b[j];
            }
            return 0;
        }
    }
    for(int j=1;j<=n;j++){
        u[j] = a[j],d[j] = b[j];
    }
    return 1;
}
signed main(){
    cin >> n >> xx;
    for(int i=1;i<=n;i++){
        cin >> u[i] >> d[i];
        sum+=u[i]+d[i];
        a[i] = u[i],b[i] = d[i];
        minn = min(minn,u[i]+d[i]);
    }
    int l = 0,r = minn,ans = -1;
    while(l<=r){
        int mid = (l+r)/2;
        if(check(mid)){
            l = mid+1;
            ans = mid;
        }
        else{
            r = mid-1;
        }
    }
    cout << sum-ans*n;
    return 0;
}

```

# 后记

最水的一集。

---

## 作者：ANDER_ (赞：2)

#### 考察：二分。
### 题意

给定上下牙齿各 $N$ 颗，需满足：

- 存在公共高度 $H$ 使得 $\forall i(U'_i + D'_i = H)$。

- 相邻上牙满足 $|U'_i - U'_{i+1}| \leq X$。

定义调整成本为 $\displaystyle\sum_{i=1}^N (U_i - U'_i) + (D_i - D'_i)$。

找到满足条件的 $\{U'_i\}$ 和 $\{D'_i\}$，使总成本最小。输出这个总成本。

### 数据范围

-   $2 \leq N \leq 2 \times 10^5$
-   $1 \leq U _ i \leq 10^9 \ (1 \leq i \leq N)$
-   $1 \leq D _ i \leq 10^9 \ (1 \leq i \leq N)$
-   $1 \leq X \leq 10^9$
-   所有输入值均为整数。
### 思路

是一个比较显然的二分，但是实现起来有很多细节。由第一个条件可得，有：
$$
U'_i = H - D'_i \geq 0 \\
D'_i = H - U'_i \geq 0 \\
\Rightarrow \max(H - D_i, 0) \leq U'_i \leq \min(U_i, H)
$$
我们可以用 $[L_i,R_i]$ 来表示这个开区间。二分时取上下界：
   $$
   H_{min} = 0 \\
   H_{max} = \min_{1 \leq i \leq N}(U_i + D_i)
   $$
维护动态区间 $[low, high]$，递推检查：
   $$
   low_{i+1} = \max(L_{i+1}, low_i - X) \\
   high_{i+1} = \min(R_{i+1}, high_i + X) \\
   $$
当存在 $low_{i} > high_i$ 时，当前 $H$ 不可行。

总答案即为：
   $$
    \displaystyle\sum_{i=1}^N (U_i + D_i) - N \times H
   $$

于是我们在 $\Theta(N \log_2(U_{\max} + D_{\max}))$ 的时间复杂度，解决了这道题，[代码](https://atcoder.jp/contests/abc395/submissions/63306118)。

---

## 作者：xiaoshumiao (赞：2)

第一次场切 F 捏。

显然 $H$ 越大越好，因此考虑二分答案 $H$。

因为相邻两个上牙的绝对差是有限制的，所以考虑算每个上牙的范围 $[L_i,R_i]$。

则：

$$L_i=\max(0,H-D_i,L_{i-1}-x)$$

$$R_i=\min(U_i,H,R_{i-1}+x)$$

为什么呢？

- 下限：首先上牙长度不能变成负数，其次下牙也不能长高，然后又也不能和上一个相差超过 $X$，三个扔一起求个 $\max$。

- 上限：首先上牙长度不能变大，其次下牙不能变成负数，然后又也不能和上一个相差超过 $X$，三个扔一起求个 $\min$。

具体代码实现见下：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, x;
pair<int, int> a[N];
bool check(int h)
{
    int ll = 0, lr = 9e18;
    for (int i = 1; i <= n; i++)
    {
        int l = max({0ll, h - a[i].second, ll - x}), r = min({a[i].first, h, lr + x});
        if (l > r)
            return false;
        ll = l, lr = r;
    }
    return true;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int l = 0, r = 9e18, ans, sum = 0;
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> a[i].first >> a[i].second, r = min(r, a[i].first + a[i].second);
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    for (int i = 1; i <= n; i++)
        sum += a[i].first + a[i].second - ans;
    cout << sum;
    return 0;
}
```

---

## 作者：cheng2010 (赞：1)

## 思路

首先，先化简一下问题：知道 $h$ 该怎么做？

首先，下排牙齿长度的取值我们便知道了，是 $[h-U_i,D_i]$，设上一个牙齿范围为 $[l,r]$ 显然只要 $[h-U_i,D_i] \bigcup [l-x,r+x] \notin \empty$ 即可满足条件，再让 $l,r$ 变为目前两个区间的交即可。

现在回到此问题，发现 $h$ 似乎是单调的，考虑简单证明一下。

若 $h_1<h_2$ 且 $h_2$ 成立，那么便可把 $h_2$ 时的方案数每一个都减去 $h_2-h_1$ 此时 $h_1$ 成立，证毕。

二分 $h$ 即可。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int const N=1e6+7;
int n,x;
int a[N],b[N];
int sum;
inline bool check(int h)
{
	if(a[1]+b[1]<h) return 0;
	int l=h-b[1]-x;
	int r=a[1]+x;
	for(int i=2;i<=n;i++)
	{
		if(a[i]+b[i]<h) return 0;
		int L=h-b[i];
		int R=a[i];
		l=max(l,L);
		r=min(r,R);
		if(l>r) return 0;
		l=l-x;
		r=r+x;
	}
	return 1;
}
signed main()
{
	scanf("%lld %lld",&n,&x);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld %lld",&a[i],&b[i]);
		sum+=a[i]+b[i];
	}
	int l=0;
	int r=2e9;
	int ans=0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid))
		{
			l=mid+1;
			ans=mid;
		}
		else
		{
			r=mid-1; 
		}
	}
	cout<<sum-ans*n;
}
```

---

## 作者：2huk (赞：1)

如果最终让上下牙之和都是 $H$，那么答案显然是 $\sum (u_i+d_i-H)$。于是发现 $H$ 越大越好。

我们令最终下面的牙的大小是 $w_i$。显然 $w$ 需要满足以下三个条件：

- $w_i \le u_i$
- $|w_i - w_{i - 1}| \le X$
- $\min_{i=1}^n(w_i + d_i)$ 最大。显然这个最小值就是 $H$。

于是二分 $H$。那么 $w_i$ 需要满足 $H - d_i \le w_i \le u_i$。令 $l_i = H - d_i,r_i = u_i$。

那么二分 check 合法的条件等价于存在 $w$ 使得 $l_i \le w_i \le r_i$ 且 $|w_i - w_{i-1}| \le X$。

显然有一个 $\mathcal O(nV)$ 的 DP。$f(i, j)$ 表示考虑前 $i$ 项且 $w_i=j$ 是否可行。那么 $f(i-1,j) \to f(i, k)$，其中 $k \in [\max(l_i,j-X), \min(r_i, j+X)]$。然后 $f(1, i) = 1$ 对于所有 $i$ 都成立。

直接做是不可能的。但注意到 $f(i, 1\dots V)$ 数组中为真的位置**一定是连续的**，所以可以只维护 $L, R$ 表示 $f(i,L) = f(i,L+1) = \dots = f(i, R) = 1$ 且 $f(i, L-1) = f(i,R+ 1)=0$。于是 check 就能做到线性了。

  为啥是连续的？注意到 $[l_1,r_1] + [l_2,r_2]=  [l_1+l_2,r_1+r_2]$，归纳一下即可。[**而且显然 $[l_1,r_1] + [l_2,r_2]=  [l_1+l_2,r_1+r_2]$ 这个 trick 今天（2025/3/1）一天用了两遍。**](https://www.luogu.com.cn/problem/P11830)

```cpp
// Problem: F - Smooth Occlusion
// Contest: AtCoder - AtCoder Beginner Contest 395
// URL: https://atcoder.jp/contests/abc395/tasks/abc395_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10;

int n, X;
int u[N], d[N], x[N];
int l[N], r[N];

bool chk(int H) {
	for (int i = 1; i <= n; ++ i ) {
		l[i] = max(0ll, H - d[i]);
		r[i] = u[i];
		if (l[i] > r[i]) return false;
	}
	
	int L = l[1], R = r[1];
	for (int i = 2; i <= n; ++ i ) {
		L = max(l[i], L - X);
		R = min(r[i], R + X);
		if (L > R) return false;
	}
	
	return true;
}

signed main() {
	cin >> n >> X;
	
	int lo = 0, hi = 2e9;
	for (int i = 1; i <= n; ++ i ) {
		cin >> u[i] >> d[i];
		hi = min(hi, u[i] + d[i]);
	}
	
	int res = 0;
	while (lo <= hi) {
		int mid = lo + hi >> 1;
		if (chk(mid)) res = mid, lo = mid + 1;
		else hi = mid - 1;
	}
	
	int sum = accumulate(u + 1, u + n + 1, 0ll);
	sum += accumulate(d + 1, d + n + 1, 0ll);
	cout << sum - n * res;
	
	return 0;
}
```

---

## 作者：2023lpx (赞：1)

# AT_abc395_f [ABC395F] Smooth Occlusion

## 思路

显然，既然 $X$ 是个常数，那么我们就先让 $u$ 满足 $|u_i-u_{i+1}| \le X$。

显然这个我们可以 $O(n)$ 搞定。

至于 $u_i+d_i=H$ 这个条件，我们做如下考虑：

1. 既然牙齿只能磨短，不能补长，那么显然 $H \le \min(u_i+d_i)$。
  
2. 显然，$H$ 越小，$\sum_{i=1}^{n} u_i+d_i-H$ 就越大。
  

所以，我们可以得出结论：当 $H=\min(u_i+d_i)$ 时，答案最小。

扫几遍数组就好了。

时间复杂度 $O(n)$。 

## code

[Submission #63278289 - AtCoder Beginner Contest 395](https://atcoder.jp/contests/abc395/submissions/63278289)

---

## 作者：SY_nzwmb83 (赞：1)

题意：给出数列 $u$ 和 $d$，每次操作仅能给任意一个数减 $1$。最终希望 $u_i+d_i$ 为定值，且 $u$ 中相邻两数差的绝对值小于 $x$。求最小操作次数。

设 $u_i+d_i$ 为 $h$。若 $h$ 确定了，那么操作次数显然确定。同时若 $h$ 可以满足要求，那么 $h-1$ 也可以。考虑二分 $h$，对 $u_i$ 求出其长度应在的区间，若有区间端点不合法，证明该 $h$ 不行。

判断函数：

```cpp
bool check(int h)
{
	for(int i=1;i<=n;i++)
	{
		a[i]=max(0ll,h-d[i]);
		b[i]=min(h,u[i]);
	}
	for(int i=2;i<=n;i++)
	{
		a[i]=max(a[i],a[i-1]-x);
		b[i]=min(b[i],b[i-1]+x);
		if(a[i]>b[i])return 0;
	}
	return 1;
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

给定两个数组 $u_i, d_i$，每次操作选择一个 $i$，将 $u_i$ 或 $v_i$ 减一，使得：

-   $\forall 1 \le i \le n, u_i + d_i = h$，这里 $h$ 可以是任何一个数。
-   $\forall 1\le i < n, |u_i-u_{i+1}|\le x$，这里 $x$ 是给定的一个数。

求最小操作次数。

## 思路

可以发现，对于一个合法的 $h$，操作次数为 $\sum\limits_{i=1}^n u_i + \sum\limits_{i=1}^n d_i - h \cdot n$，且合法的 $h$ 是一段连续的区间。

所以考虑二分 $h$。

发现题目要求 $|u_i - u_{i + 1}| \le x$，考虑使用差分约束，跑 dijkstra 即可。

最后看 $u_i + d_i$ 是否 $\ge h$。

## 代码

```cpp
ll n, k, u[200005], d[200005], vis[200005], t[200005];

bool ck(ll h) {
    priority_queue <pair <ll, ll> > q;
    for(ll i = 1; i <= n; i++) vis[i] = 0, t[i] = u[i];
    for(ll i = 1; i <= n; i++) q.push({-u[i], i});
    while(q.size()) {
        ll x = q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        if(x < n && t[x + 1] - t[x] > k) t[x + 1] = t[x] + k, q.push({-t[x + 1], x + 1});
        if(x > 1 && t[x - 1] - t[x] > k) t[x - 1] = t[x] + k, q.push({-t[x - 1], x - 1});
    }
    for(ll i = 1; i <= n; i++) if(t[i] + d[i] < h) return 0;
    return 1;
}
signed main() {
    n = rd(), k = rd();
    for(ll i = 1; i <= n; i++) u[i] = rd(), d[i] = rd();
    ll l = 0, r = 2e9, ans = 0;
    while(l < r) {
        ll mid = (l + r + 1) >> 1;
        if(ck(mid)) l = mid;
        else r = mid - 1;
    }
    for(ll i = 1; i <= n; i++) ans += u[i] + d[i] - l;
    cout << ans;
    return 0;
}
/*

*/
```

---

## 作者：piantouqu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc395_f)

## 思路

显然 $H$ 越大时，消耗越小。那么很容易想到去找最小的 $U_i+D_i$。但是有 $\lvert U_i-U_{i+1} \rvert \leq X$ 这个条件在，我们应该先对上牙进行“平整” 处理，使得上牙满足 $\lvert U_i-U_{i+1} \rvert \leq X$。最后用总和减去“平整” 后的最小上下和即可得到答案。

## 证明

为什么“平整” 后去取答案是对的呢？

因为下牙没有限制，所以我们先去处理下牙。如果处理了下牙还需要处理，再去处理上牙。如果此时 $\lvert U_i-U_{i+1} \rvert > X$，那么说明 $U_{i+1}$ 也是要被处理成与 $U_i$ 差不多的状态（$U_{i+1}$ 显然大于 $U_i$），那么便不在需要“平整” 操作。

[code](https://atcoder.jp/contests/abc395/submissions/63333097)

---

## 作者：_7thRC_CB_CRP_ (赞：0)

首先无论你如何据牙齿，最后的答案都是 $(\sum_{i-1}^n U_i+D_i)-nH$。

所以说我们只需要找到一最大的 $H$ 满足据牙齿的条件。

显然对于一个 $H$ 可以锯掉那么所有 $H'<H$ 都可以锯掉。那么我们可以根据该性质二分，找到最大的一个 $H$。

那现在只需要考虑为 $H$ 的情况下，是否可以锯掉牙齿。同时，条件仅要求了上牙的情况，那么我们可以指考虑上牙。

那么既然知道 $H$。不难发现，第 $1$ 颗上牙的可锯成 $[l_1,r_1]=[\max(0,h-D_1),\min(h,U_1)]$；第 $i,2\le i$ 颗上牙可以锯成 $[l_i,r_i]=[\max(0,h-D_i),\min(h,U_i)]\land[l_{i-1}-x,r_{i-1}+x]$。

而如果任何一颗上牙的取值为空集，那么则无法锯掉，否则可以。

即可完成此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, x;
ll u[200001], d[200001];
bool check(ll h) {
	ll l =0, r =3000000000;
	for (int i = 1; i <= n; i++) {
		l = max(max(h - d[i], 0ll), l - x);
		r = min(min(u[i], h), r + x);//计算取值范围
		if(l>r)
			return 0;//判定是否可行
	}
	return 1;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>x;
	ll sum=0;
	for(int i=1;i<=n;i++)
		cin>>u[i]>>d[i],sum+=u[i]+d[i];//计算总长度
	ll l=0,r=3000000000;
	while(l<r) {
		ll mid=(l+r)/2;
		if(check(mid+1)) l=mid+1;
		else r=mid;
	}//二分
	cout<<sum-n*l;//输出答案
}
```

---

## 作者：light_searcher (赞：0)

首先假设最后所有高度之和都是 $H$，那么答案则为 $ \sum\limits _{i=1}^n U_i+D_i-H$，也就是 $H$ 越大越好，而且 $H$ 是否可行又是具有单调性的，于是考虑二分 $H$。判断就比较简单了，把每个 $U_i$ 最终的取值范围求出来即可，如果不存在合法的取值范围，说明当前的 $H$ 是不可行的，时间复杂度 $\mathcal O(n \log V)$，$V$ 是值域。

Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,u[N],d[N],X,a[N],sum;
bool check(int x){
	int l=0,r=1e18;
	for(int i=1;i<=n;i++){
		l=max({0ll,l-X,x-d[i]});
		r=min(u[i],r+X);
		if(l>r) return 0;
	}
	return 1;
}
signed main(){
	scanf("%lld%lld",&n,&X);
	int l=0,r=1e18,mid=0,ans=0;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&u[i],&d[i]);
		sum+=u[i]+d[i];
		r=min(r,u[i]+d[i]);
	}
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)){
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
	}
	printf("%lld",sum-n*ans);
	return 0;
}

---

## 作者：small_lemon_qwq (赞：0)

首先可以发现答案只与 $H$ 有关，并且 $H$ 满足单调性，可以考虑二分 $H$ 的最大值。

确定了上牙与下牙的总高度后，我们就可以确定每颗上牙最少和最大的磨牙次数，将最大次数和牙齿高度减去最小次数就可以去掉最小次数的限制了。

接下来，不难发现，最短的牙齿是一定不会使用磨牙次数的，而且左右的牙齿不满足要求还需要强行让他们的高度变为最小值 $+X$，可以把所有牙齿丢进优先队列或 `set` 中维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,X,a[200005],b[200005],c[200005],d[200005],vis[200005],minn=LLONG_MAX,sum=0;
priority_queue<pair<int,int>,deque<pair<int,int>>,greater<pair<int,int>>>st;
bool checker(int H){
	memset(vis,0,sizeof(vis));
	while(st.size())st.pop();
	for(int i=1;i<=n;i++){
		int mn=max(a[i]-H,0ll);
		int mx=min(a[i],a[i]+b[i]-H);
		mx-=mn;
		c[i]=a[i]-mn;
		d[i]=mx;
		st.push({c[i],i});
	}
	while(st.size()){
		auto p=st.top();
		st.pop();
		if(vis[p.second])continue;
		vis[p.second]=1;
		if(p.second!=1){
			if(c[p.second-1]-c[p.second]>X){
				d[p.second-1]-=c[p.second-1]-c[p.second]-X;
				if(d[p.second-1]<0)return 0;
				c[p.second-1]=c[p.second]+X;
				st.push({c[p.second-1],p.second-1});
			}
		}
		if(p.second!=n){
			if(c[p.second+1]-c[p.second]>X){
				d[p.second+1]-=c[p.second+1]-c[p.second]-X;
				if(d[p.second+1]<0)return 0;
				c[p.second+1]=c[p.second]+X;
				st.push({c[p.second+1],p.second+1});
			}
		}
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>X;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		minn=min(minn,a[i]+b[i]);
		sum+=a[i]+b[i];
	}
	int L=0,R=minn;
	while(L<=R){
		int mid=(L+R)>>1;
		if(checker(mid)){
			L=mid+1;
		}else{
			R=mid-1;
		}
	}
	cout<<sum-(L-1)*n;
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

二分答案。设答案 $H$ 为最终上下牙齿高度和。显然答案下界为 $0$，上界为 $\min \{U_i+D_i\}$。考虑如何判断 $H$ 成立。只要维护一个 $U'_i$ 的区间，并判断区间是否合法即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int N,U[202503],D[202503],X,L,R=2e9+7,sum;
bool chk(int H){
	int hi,lo;
	for(int i=1;i<=N;i++){
		if(i!=1){
			lo=max(max(0ll,H-D[i]),lo-X);
			hi=min(U[i],hi+X);
		}else{
			lo=max(0ll,H-D[i]);
			hi=U[i];
		}if(lo>hi)return 0;
	}
	return 1;
}
signed main(){
	cin>>N>>X;
	for(int i=1;i<=N;i++)cin>>U[i]>>D[i],R=min(R,U[i]+D[i]),sum+=(U[i]+D[i]);
	int ans=0,mid;
	while(L<=R){
		mid=L+R>>1;
		if(chk(mid))ans=mid,L=mid+1;
		else R=mid-1;
	}cout<<sum-N*ans;
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

简单题，但是为什么我 $86$ 分钟才过啊。

## Solution AT_abc395_f

### Idea

以下记 $a$ 为 $U$，记 $b$ 为 $D$。

最基本的思路：我们让 $a_i$ 尽量大，这样磨掉的牙齿数就尽量小。

根据贪心，我们不难想到让 $a_i+b_i$ 的最小值为 $H$，所以我们接下来的任务就是：修正 $a_i$，满足第二个条件。

我们不难想到一个策略：我们遍历整个序列，如果 $a_i-a_{i-1}>x$ 就令 $a_i=a_{i-1}+x$，如果 $a_{i-1}=a_i+x$ 就令 $a_{i-1}=a_i+x$。

但是这样的转移是有后效性的。例如以下数据：

```
10 3
13 15
16 27
19 31
22 15
25 18
28 26
31 17
21 19
13 16
18 17
```

遍历完成之后，数组会变成这样：

```
10 3
13 15
16 27
19 31
22 15
25 18
28 26
24 17
16 19
13 16
16 17
```

可以发现它并不符合要求。

虽然我们从 $1$ 开始有后效性，但是如果我们从每个位置都开始遍历一遍呢？不难发现如果 $a_i$ 要磨掉一块，一定是因为一个 $a_j$ 导致的（$j\in[1,n]$），所以这样做是可行的。但是这样复杂度不可接受。

我们发现，如果从 $j$ 开始遍历，记录 $d_i$ 为 $a_i$ 在以 $j$ 遍历基础上的最终值，可以发现：

- 如果 $i<j$，则 $a_i=\min(a_{i+1}+x,a_i)$。
- 如果 $i=j$，则 $a_i=a_j$。
- 如果 $i>j$，则 $a_i=\min(a_{i-1}+x,a_i)$。

那么我们可以把上面的式子展开，得到：

- 如果 $i<j$，则 $a_i=\min(a_{i+1}+x,a_i)=\min(\min(a_{i+2}+x,a_{i+1})+x,a_i)=\cdots=\min\{a_k+(k-i)\times x\}$，其中 $k\in[i,j]$。
- 如果 $i=j$，则 $a_i=a_j$。
- 如果 $i>j$，则 $a_i=\min(a_{i-1}+x,a_i)=\min(\min(a_{i-2}+x,a_{i-1})+x+a_i)=\cdots=\min\{a_k+(i-k)\times x\}$，其中 $k\in[j,i]$。

记 $c_i$ 为 $a_i$ 最终值，可以发现 $c_i=\min\{a_j+x\times |j-i|\}$，其中 $j\in[1,n]$。

那么这个怎么解决呢？我们发现如果我们只考虑往右遍历，记 $e_{j,i}$ 为从 $j$ 开始往右遍历之后到第 $i$ 个位置 $a_i$ 应该被修正为多少。那么显然有：对 $\forall i\in[j,n]$，有 $e_{1,i}\le e_{j,i}$。原因显然：从 $j$ 开始遍历的数，从 $1$ 开始都取得到。

反方向依然同理。

正方向遍历时所以我们可以记录一个变量 $minn$ 来记录 $\min\{a_k+(i-k)\times x\}$（其中 $k\in[1,i]$），遍历到 $i$ 时需要更新 $minn=\min(minn+x,a_i)$。事实上我在代码里是先在上一次循环的结尾为 $minn$ 加 $x$，不过都一样了。

反方向遍历依然同理。

所以我们这道题就做完了，时间复杂度 $\operatorname{O}(n)$。

### Code

```
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
#define ll long long
ll a[N], b[N],c[N], x, ans,anss=0, r = 0x3f3f3f3f3f3f3f3f;
int n;
int main()
{
    scanf("%d%lld", &n, &x);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a[i], &b[i]);
    }
    ll minn=0x3f3f3f3f3f3f3f3f;
    minn=0x3f3f3f3f3f3f3f3f;
    for(int i=1;i<=n;i++){
        minn=min(minn,a[i]);
        c[i]=minn;
        minn+=x;
    }
    minn=0x3f3f3f3f3f3f3f3f;
    for(int i=n;i>=1;i--){
        minn=min(minn,a[i]);
        c[i]=min(c[i],minn);
        minn+=x;
    }
    for(int i=1;i<=n;i++){
        anss=anss+(a[i]-c[i]);
    }
    for(int i=1;i<=n;i++){
        r=min(r,c[i]+b[i]);
    }
    for(int i=1;i<=n;i++){
        anss=anss+(c[i]+b[i]-r);
    }
    printf("%lld",anss);
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

一个很直观的做法。

首先我们可以二分 $H$，考虑 check。根据题意，若 $U_i$ 位于范围 $[l,r]$，那么 $U_{i+1}$ 必定位于范围 $[l-X,r+X]$，但是 $U$ 是不能被增加的，也不能减少超过 $U_{i+1}+D_{i+1}-H$ 所以其实是范围 $[l-X,r+X]\cap [U_{i+1}-(U_{i+1}+D_{i+1}-H),U_{i+1}]$，所以如果某个牙齿的范围为 $\varnothing$，那么这个 $H$ 就不成立，所以可以做到 $O(n)$ check，总复杂度 $O(n\log V)$，$V$ 为值域的 $2$ 倍。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int n,x,a[N],b[N];
int check(int h)
{
	int nowl=1,nowr=a[1];
	for(int i=2;i<=n;i++)
	{
		nowl=max({a[i]-(a[i]+b[i]-h),nowl-x,1ll});
		nowr=min(a[i],nowr+x);
		if(nowl>nowr) return 0;
	}
	return 1;
}
signed main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	int mn=2e9;
	for(int i=1;i<=n;i++) mn=min(mn,a[i]+b[i]);
	int l=1,r=mn,mid,res;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid)) res=mid,l=mid+1;
		else r=mid-1;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans+=a[i]+b[i];
	cout<<ans-n*res;
}

---

## 作者：liugh_ (赞：0)

一个很极限的做法。

首先可以二分高度和，显然答案为最大的 $H$ 满足能操作使得 $U$ 合法。贪心地，我们希望尽量多的操作都在 $D$ 上因为其没有限制，设 $U_i$ 的最终取值为 $u_i$，注意到对于一个 $H$，有
$$
\left\{\begin{aligned}
u_i&\le \min(U_i,H) \\
u_i&\le u_{i+1}+X \\
u_i&\le u_{i-1}+X
\end{aligned}\right.
$$
容易发现这是一个要求变量尽量大的差分约束，且边权非负，上 dijkstra，总时间 $\Theta(n\log^2 n)$，常数较大，需要快读和一些常数优化。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<cassert>
#include<numeric>
#include<array>
#include<bitset>
#include<set>
constexpr static void tomin(auto&x,auto&&y){if(y<x)x=y;}
constexpr static void tomax(auto&x,auto&&y){if(y>x)x=y;}
constexpr static void fin(auto&x){signed c=0,f=0;do if(c==45)f=1;while(c=getchar(),c<48||c>57);x=0;do x=(x<<1)+(x<<3)+(c^48);while(c=getchar(),c>=48&&c<=57);if(f)x=-x;}
constexpr static void fot(auto x){signed d[40],l=-1;if(x<0)x=-x,putchar(45);do d[++l]=(x%10)^48;while(x/=10);do putchar(d[l]);while(~--l);putchar(32);}
using namespace std;
#define long        long long
#define pb          push_back
#define ve          vector
#define fi          first
#define se          second
#define pii         pair<int,int>
#define all(x)      (x).begin(),(x).end()
#ifndef BUG
#define bug(x)      ({})
#define bua(a,l,r)  ({})
#else
#define bug(x)      ({cout<<":"<<__LINE__<<": ";x;cout<<endl;({});})
#define bua(a,l,r)  ({cout<<#a": ";for(signed i##END=(l),j##END=(r);i##END<=j##END;i##END++)cout<<a[i##END]<<' ';cout<<endl;({});})
#endif
#ifdef  FIO
auto FI=freopen("1.in","r",stdin);
auto FO=freopen("1.out","w",stdout);
#endif

#define int long
constexpr long inf=1ll<<60,maxn=2e5+10;

int n,X;
int A[maxn],B[maxn];

struct _eg{int pre,v,w;}eg[maxn*3];int ei=1,eh[maxn];
void ea(auto u,auto v,auto w){eg[++ei]={eh[u],v,w};eh[u]=ei;}

int dis[maxn];
bitset<maxn> vis;
int cal(int sum){
    fill(dis,&dis[n]+1,inf);
    vis.reset();
    for(int e=eh[0];e;e=eg[e].pre){
        auto& [_,v,w]=eg[e];
        w=min(A[v],sum);
    }
    priority_queue<pii> q;
    dis[0]=0;
    q.push({0,0});
    while(q.size()){
        int u=q.top().se;
        q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int e=eh[u];e;e=eg[e].pre){
            auto [_,v,w]=eg[e];
            if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                q.push({-dis[v],v});
            }
        }
    }
    int res=0;
    for(int i=1;i<=n;i++){
        res+=A[i]-dis[i];
        if(B[i]-(sum-dis[i])<0)return -1;
        res+=B[i]-(sum-dis[i]);
    }
    return res;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // signed cse=1;cin>>cse>>ws;while(cse--)
[](){
    fin(n),fin(X);
    for(int i=1;i<=n;i++)fin(A[i]),fin(B[i]);
    for(int i=1;i+1<=n;i++){
        ea(i+1,i,X);
        ea(i,i+1,X);
    }
    for(int i=1;i<=n;i++){
        ea(0,i,A[i]);
    }
    int l=0,r=2e9,ans=-1;
    for(int i=1;i<=n;i++)tomin(r,A[i]+B[i]);
    while(l<=r){
        int mid=(l+r)>>1;
        int t=cal(mid);
        if(~t)ans=t,l=mid+1;else r=mid-1;
    }
    fot(ans);
}();
}
```

---

## 作者：xiaoyin2011 (赞：0)

## AT_abc395_f [ABC395F] 丝滑贴合 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc395_f)

### 题目大意

有 $N \times 2$ 颗牙，$N$ 颗上牙，$N$ 颗下牙，它们一一对应。第 $i$ 颗上牙长为 $U_i$，下牙长为 $D_i$。现在有如下定义：

> - 如果对于所有的牙（$1 \le i \le N$），都有 $U_i + D_i = H$（$H$ 有一个固定的值）。
> 
> - 如果对于所有的牙之间（$1 \le i \le N - 1$），都有 $| U_{i + 1} - U_{i} | \le X$（$X$ 是输入的常量）。
> 
> - 如果对于所有的牙之间（$1 \le i \le N - 1$），都有 $| D_{i + 1} - D_{i} | \le X$。
> 
> 满足以上条件，则称牙丝滑地贴合了。

现在有磨牙器可以使用，每次仅能将一颗牙齿的长度减少 $1$（注意不能增加，可以多次减少，直至 $0$）。每次使用磨牙器花费 $1$，问达到丝滑贴合的最少花费。

### 思路

首先，把所有牙齿降低到 $0$ 必然满足丝滑贴合的条件，所以本题一定有解。

---

接下来，场上我想到了两条路径，其中一条是正解。分割线之内内容是另一个想法，可以跳过。

一种思路是先根据绝对差值不超过 $X$，牙不能增长，利用贪心将上牙的最长长度一一求出，然后设为能达到的最长长度，并且让下牙在 $O(N)$ 之内适配它。

想法固然好，但是实现的时候会发现两个问题：

- 隔一个的牙齿的最大值也会受到自己影响，体现在第三个样例，此时必须全部遍历，复杂度突破 $O(N ^ 2)$。

- 绝对值会产生下界，有时会突破下界。

于是果断放弃。继续观察特征。

---

看到数据范围高达 $10^9$，同时最终牙齿贴合高度 $H_{ans}$ 越小越容易成功，但答案越不优秀。这满足二分的特征，考虑二分。

显然这里我们需要二分 $H$。二分需要我们找一下上下界限 $H_l$ 和 $H_r$。其中 $H_l = 0$ 毋庸置疑，这里 $H_r$ 可以直接设置成 $2 \times 10^9$，当时我并没有想到，而是对于每对牙计算了 $U_i + D_i$，并求最小值。

这样，我们可以知道闭区间 $[H_l, H_r]$，并且每次求得 $H_{mid}$，那么，如何验证 $H_{mid}$ 可不可以闭合呢？

对于 $1 \le i \le N$，如果 $U_i + D_i < H$，那必然不行，返回 $0$。接下来考虑第 $i$ 格的索求空间和需求空间。假设 $i$ 处下牙剩余的空间是 $L_i$，上牙需要空间 $R_i$，当 $L_i \le R_i$ 即可通过磨牙器解决。反之，则返回 $0$。下牙剩余的空间和上牙空间也不是一定的，下牙剩余空间一定不低于原长下牙剩余，因为要考虑上一颗下牙的长度拉住它，上牙同理。直到最后也没有出现问题，返回 $1$。

将上述过程做成 `check` 函数，当返回 $1$ 时，则把 $H_l$ 拉到 $H_{mid} + 1$，$H_{ans} = H_{mid}$，反之，$H_r = H_{mid} - 1$。

这样最后只会得到 $H$，但是我们只要预处理所有牙的长度和，再知道目标长度和是 $H_{ans} \times N$，答案就出来了。

### 实现

注意到原长也会限制 $L$ 和 $R$，因此 $U_i + D_i$ 不行，也会 $L > R$，因此略去。这里只需要存储上一个的 $L$ 和 $R$ 以及当前 $L$ 和 $R$ 即可。`bool check(ll H);` 的实现如下：

```cpp
bool check(ll H)
{
	ll pl, pr, tl, tr;
	for (int i = 1; i <= N; i++)
	{
		tl = max(0ll, H - D[i]), tr = min(U[i], H);
		if (i != 1) tl = max(tl, pl - X), tr = min(tr, pr + X);
		if (tl > tr) return 0;
		pl = tl, pr = tr;
	}
	return 1;
}
```

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, X, U[200005], D[200005], sum = 0;
bool check(ll H)
{
	ll pl, pr, tl, tr;
	for (int i = 1; i <= N; i++)
	{
		tl = max(0ll, H - D[i]), tr = min(U[i], H);
		if (i != 1) tl = max(tl, pl - X), tr = min(tr, pr + X);
		if (tl > tr) return 0;
		pl = tl, pr = tr;
	}
	return 1;
}
int main()
{
    scanf("%lld%lld", &N, &X);
    for (int i = 1; i <= N; i++)
	{
        scanf("%lld%lld", &U[i], &D[i]);
        sum += (U[i] + D[i]);
    }
	ll l = 0, r = 2e9, mid, ans = 0;
    while (l <= r)
	{
        mid = l + (r - l) / 2;
        if (check(mid))
		{
            ans = mid;
            l = mid + 1;
        }
		else
		{
            r = mid - 1;
        }
    }
	printf("%lld\n", sum - ans * N);
    return 0;
}
```

---

