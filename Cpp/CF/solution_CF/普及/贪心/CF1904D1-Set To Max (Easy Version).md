# Set To Max (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions of this problem are the constraints on $ n $ and the time limit. You can make hacks only if all versions of the problem are solved.

You are given two arrays $ a $ and $ b $ of length $ n $ .

You can perform the following operation some (possibly zero) times:

1. choose $ l $ and $ r $ such that $ 1 \leq l \leq r \leq n $ .
2. let $ x=\max(a_l,a_{l+1},\ldots,a_r) $ .
3. for all $ l \leq i \leq r $ , set $ a_i := x $ .

Determine if you can make array $ a $ equal to array $ b $ .

## 说明/提示

In the first test case, we can achieve array $ b $ by applying a single operation: $ (l,r)=(2,3) $ .

In the second test case, it can be shown we cannot achieve array $ b $ in any amount of operations.

In the third test case, we can achieve array $ b $ by applying two operations: $ (l,r)=(2,5) $ . followed by $ (l,r)=(1,3) $ .

In the fourth and fifth test cases, it can be shown we cannot achieve array $ b $ in any amount of operations.

## 样例 #1

### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2```

### 输出

```
YES
NO
YES
NO
NO```

# 题解

## 作者：CuteChat (赞：7)

本题解仅供像我一样的蒟蒻阅读，大佬们可以去困难版。

对于简单的简单版而言，$N$ 是 $10^{3}$ 量级的，这说明我们可以使用 $O(N^2)$ 的暴力乱搞。

怎么乱搞呢，首先有一个性质，如果有一个 $i$，使得 $a_i > b_i$，那么这种局面一定无解，因为 $a_i$ 肯定是越修改越大的，不可能变小，毕竟想要修改 $i$ 这个位置这个修改区间必然经过 $i$，从而影响到最大值。

接下来就是 $a_i < b_i$ 的情况，如果 $a_i < b_i$，我们可以从 $i$ 出发，分别向左向右拓展，记现在拓展到了 $j$，如果找到一个等于 $b_i$ 的 $a_j$ 我们就尝试用这个区间修改。

来举一个例子：

$A=4,3,{\color{red}2},5,3$

$B=4,3,3,3,5$

在这里，被标红的 $2$ 想要成为 $3$，我们就以这个位置出发，向左向右拓展，显然 $j$ 可以取 $2$，即对 $[2,3]$ 的区间进行修改。

为什么 $j$ 不能取 $5$ 呢？因为中间有一个比他们都大的 $5$！这样修改就不是我们想要的结果。

那么，我们在拓展的时候，要满足那些条件才能使得我们能修改成想要的结果呢？

第一条 $a_j > b_i$ 有了，还有没有其他的条件呢，显然有，如果 $b_i > b_j$ 的情况下，这个修改就是错误的，如何理解？

就是，我们修改这一个区间之后，$a_i$ 就变成了 $b_i$，同样的，拓展到了 $j$ 也会使得 $a_j = b_i$，这样就满足了无解的性质（因为 $a_j > b_j$，等量代换）。

所以拓展的时候检查就可以了。

不过又有一个问题，就是我们修改之后，$a$ 会被修改，会不会存在一种情况，使得原本某个位置是能找到解的，但是其他地方修改过后，这个地方就找不到解了，也就是说，操作之间可能会互相影响。

不过，我们可以按照每一个修改区间的最大值排序，从小到大修改，这样就不会影响答案了。

在实际的编写中，其实我们不需要考虑这种情况，因为只要我们不修改，就一定不会影响答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, a[200003], b[200003];

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	for (int i = 1; i <= n; ++i) {
		if (a[i] > b[i]) { // 如果要修改他，必然会经过他，必然会影响最大值。 
			return puts("NO"), void(); 
		} else if (a[i] < b[i]) {
			// 向右拓展找到一个
			bool ok = 0;
			for (int r = i + 1; r <= n; ++r) {
				if (a[r] == b[i]) { // 找到了
					ok = 1;
					break;
				}
				if (a[r] > b[i] || b[i] > b[r]) break; // 条件不满足，方案不能满足题意
			}
			if (ok) continue;
			// 向左拓展找到一个
			ok = 0;
			for (int l = i; l >= 1; --l) {
				if (a[l] == b[i]) { // 找到了
					ok = 1;
					break;
				}
				if (a[l] > b[i] || b[i] > b[l]) break; // 条件不满足，方案不能满足题意
			}
			if (ok) continue;
			return puts("NO"), void(); // 如果两种方案就不行，说明无解
		}
	}
	puts("YES"); // 每一个位置都能满足条件
}

int main() {
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}
```

---

## 作者：kczw (赞：5)

# 题意简述
共 $t$ 组数据，对于每组数据给定两个长 $n$ 数列 $a,b$。对于 $a_i$，如果与相邻的数比它小，那么这个数可以被赋值为 $a_i$。问最后能否将 $a$ 修改成 $b$。
# 思路
题意给出的修改方式其实可以理解为一种大数向相邻小数的扩散。

所以看能否将 $a$ 修改成为 $b$，其实就是判断两个点：
- 对于 $a_i=b_i$ 时，能否保证不受扩散影响。
- 对于 $a_i\ne b_i$ 时能否在 $a$ 中找到一个 $a_j=b_i$，将自己的值扩散到 $a_i$，同时保证扩散后其他像 $a_i,b_i$ 这样不等的组合，还能经过修改相等。

最后，我们只需要用 set 存储对于每个 $a_i$ 在满足以上条件所能被扩散到的所有可能的值。
# 实现
```cpp
#include<iostream>
#include<set>
using namespace std;
int t,n,last,k,a[1005],b[1005];
int main(){
	scanf("%d",&t);
	while(t--){
		k=1;
		set<pair<int,int> > co;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)scanf("%d",&b[i]);
		for(int i=1;i<=n;i++){
			for(int j=i-1;j>=1&&a[j]<a[i]&&a[i]<=b[j];j--)co.insert({j,a[i]});
			for(int j=i+1;j<=n&&a[j]<a[i]&&a[i]<=b[j];j++)co.insert({j,a[i]});
		}for(int i=1;i<=n;i++)
			if(a[i]!=b[i])
				if(!co.count({i,b[i]})){k=0;break;}
		printf(k?"YES\n":"NO\n");
	}return 0;
}
```

---

## 作者：yshpdyt (赞：2)

## 题意
两个序列，支持一个操作将第一个序列某段区间赋值为该区间最大值，求能否将第一序列变成第二个序列
## Sol
考虑什么情况无解。

每次操作为赋值区间最大值，操作不会使得 $a_i$ 变小，所以对于 $a_i > b_i$ 的情况存在一定无解，如果有操作导致了这种情景，那这种操作就是不合法的。

除此之外，使 $a_i$ 增大为 $b_i$ 的操作一定是以 $i$ 为一个端点，向左向右找可以更新的最近位置。这里的优先条件先是可以更新，其次是最近。为什么是越近越好？对比挑选同侧一个近的位置 $j_1$ 和一个远的位置 $j_2$，$[j_2,i]$ 一定会包含 $[j_1,i]$，或者 $[i,j_2]$ 一定会包含 $[i,j_1]$，这说明挑选远的位置会多进行一些无意义的赋值，从而可能使结果出现问题（具体出现啥问题继续看）

那么我们的思路就很明显了，对于每一个 $i$，向左向右找值等于 $b_i$ 的地方，接着考虑什么样的情况找不到。

如果没有等于 $b_i$ 的值，那么是无解的。

如果在找到一个等于 $b_i$ 的位置前，找到一个 $j$，使得 $a_j>b_i$，那么无法找到，因为这样会使 $a_i$ 更新成 $a_j>b_i$ 从而无解。

如果在找到一个等于 $b_i$ 的位置前，找到一个 $j$，使得 $b_j<b_i$，那么即使找到要找的位置，也会使 $a_j$ 赋值为 $b_i$，从而使 $a_j>b_j$ 无解。

总结一下，以下情况无解，以向左查找为例（默认 $\exists \ i$）：

1. $\forall j\ ,a_j \neq b_i$
2. $\forall a_j=b_i \ ,\max^i_{k=j}a_k>b_i$ 
3. $\forall a_j=b_i \ ,\min^i_{k=j}b_k>b_i$ 

直接做是 $O(n^2)$ 的，显然过不去，考虑优化。

注意到对于一个位置 $i$，可以更新一段包含 $i$ 的连续区间，分开左右，以向右更新为例。

我们考虑维护 $i$ 位置可以更新的最远距离为到 $j$，如果不考虑第三条限制，需要满足 
$$\max^{j}_{k=i}a_i \le b_k , a_i>b_{j+1} $$ 
或 
$$\max^{j}_{k=i}a_k \le a_i , a_i<a_{j+1}$$

考虑找到这个 $j$ ，将 $[i,j]$ 的可被更新的值候选队列加上 $a_i$，由于最后要取最近的位置进行更新，所以这个候选队列实际上只有两个值（左边可更新的最近元素和右边可更新的最近元素）。
这些操作可以通过维护一个单调队列来实现，第一关键字为 $a_i$ ，第二关键字为 $i$，每到一个新的位置 $i$，将队首大于 $b_i$ 或者 小于 $a_i$ 的元素弹出。在队列中查找最优的符合题意的位置加入到候选队列，这里的单调队列为了方便找位置使用 `set` 实现。

向左同理，即正着找一遍，反着找一遍，获得向左向右的最优解。

接着考虑候选队列是否符合题意，维护一个直接求解  $b_i$ 区间最小值的数据结构。
如果候选队列为空，无解。
如果候选队列的所有值（两个），设为 $j$ ， $\min^i_{k=j}b_k<b_i$，不符合第三条限制，两个都不满足，说明无解。

这样这道题就完成了，复杂度 $O(nlogn)$ 。

总结一下，通过维护单调队列求每个元素的候选解，判断候选解是否符合条件，存在任意元素无解，说明整个无解。

说起来可能比较绕，细节见代码。
## Code

```
#include<bits/stdc++.h>
#define ll int
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
set<pair<ll,ll>> q;
ll fl1[N],fl2[N];
ll n,a[N],b[N];
namespace tr{
    #define mid ((l+r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    ll mx[N*5],lzy[N*5];
    void build(ll p,ll l,ll r){
        if(l==r){
            mx[p]=b[l];
            return ;
        }
        build(ls,l,mid);
        build(rs,mid+1,r);
        mx[p]=min(mx[ls],mx[rs]);
    }
    ll qr(ll p,ll l,ll r,ll le,ll ri){
        if(le<=l&&ri>=r)return mx[p];
        ll ans=inf;
        if(le<=mid)ans=min(ans,qr(ls,l,mid,le,ri));
        if(ri>mid)ans=min(ans,qr(rs,mid+1,r,le,ri));
        return ans;
    }
}
void sol(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        cin>>b[i];
        if(a[i]>b[i]){
            //ai比bi大，无法通过操作减小ai的值，故无解
            cout<<"NO\n";
            return ;
        }
    }
    tr::build(1,1,n);
    // 维护区间最小值的数据结构
    q.clear();
    for(int i=1;i<=n;i++){
        //从左到右维护单调递减的set，存储当前位置可以被那些值更新，以及这些值的位置
        while(!q.empty()&&((*q.begin()).fi<a[i]||(*q.begin()).fi>b[i]))q.erase(q.begin());
        //将 <ai 的值删除，这些值无法更新当前位置及其右边
        //将 >bi 的值删除，使用这些值会使当前位置无法变成bi
        if(b[i]>=a[i])q.insert({a[i],i});//加入当前元素
        auto t=q.lower_bound({b[i]+1,0});//优先查找距离自己最近的bi值的位置
        //这里由于是从左边加的，里面的元素下标小于i，应该查找值为bi且位置最靠右的
        t--;//减一就是如上所说
        if((*t).fi==b[i])fl1[i]=(*t).se;//查找到的元素可以使ai更新乘bi
        else fl1[i]=0;
        // fl1表示i左边可以使ai更新为bi的元素位置
    }
    q.clear();
    for(int i=n;i>=1;i--){
        while(!q.empty()&&((*q.begin()).fi<a[i]||(*q.begin()).fi>b[i]))q.erase(q.begin());
        if(b[i]>=a[i])q.insert({a[i],i});
        auto t=q.upper_bound({b[i],0});
        //这里由于是从右边加的，里面的元素下标大于i，应该查找值为bi且位置最靠左的
        if((*t).fi==b[i])fl2[i]=(*t).se;
        else fl2[i]=0;
        // fl2表示i右边可以使ai更新为bi的元素位置
    }
    for(int i=1;i<=n;i++){
        if(!fl1[i]&&!fl2[i]){//如果不存在可以更新为bi的位置，说明无解
            cout<<"NO\n";
            return ;
        }
        ll p1=1,p2=1;
        
        if(fl1[i]&&fl1[i]<i&&tr::qr(1,1,n,fl1[i]+1,i)<b[i])p1=0;
        // 如果左边存在位置fl1，且fl1~i中的b数组有比bi小的，这样会使某个aj>bj从而无解
        if(fl2[i]&&i<fl2[i]&&tr::qr(1,1,n,i,fl2[i]-1)<b[i])p2=0;
        // 如果右边存在位置fl2，且i~fl2中的b数组有比bi小的，这样会使某个aj>bj从而无解
        if(p1&&fl1[i])continue;
        if(p2&&fl2[i])continue;
        cout<<"NO\n";
        return ;
    }
    cout<<"YES\n";
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```


---

## 作者：ddw1 (赞：1)

## 题意

给定长度为 $n$ 的两个数组 $a,b$。每次操作你可以选择 $a$ 的一个区间 $[l,r]$，将这段区间内的所有数赋值为 $a[l,r]$ 内的最大值。

请你确定是否可以是的数组 $a$ 和数组 $b$ 相同。

## 思路

首先我们要枚举 $a,b$ 中的每一位，然后对于第 $i$ 位分类来看：

1. $a_i=b_i\\$这时候已经匹配好，直接跳过，不需要进行任何操作。
2. $a_i>b_i\\$由于修改后的 $a_i$ 一定是 $\ge$ 初始的 $a_i$ 的，而你又不能改变 $b$ 数组，所以这种情况直接输出 `NO` 就结束了。
3. $a_i<b_i\\$这种情况就需要我们去进行操作了。我们可以从第 $i$ 位开始，向两边拓展，如果找到一位 $a_j=b_i$ 那么就说明这一位可以替换，可以继续操作。但是要注意，这里有两种情况是要直接输出 `NO` 的：
   + $a_j>b_i$。因为 $a_i$ 会替换为区间内最大的一个，但是如果遇到比 $b_j$ 大的数，那不管在拓展到哪一位，最小也会替换为这个数，这样就不可能得到 $b_i$ 了。
   + $b_i>b_j$。这种情况下，如果把 $a_i$ 成功更改 $b_i$，但因为在所找到的 $j$ 与 $i$ 之间有一个更小的，那它也被替换后会被影响，所以要输出 `NO`。

按照以上思路遍历就可以了，如果遍历完都没输出 `NO`，那就输出 `YES` 即可。

## Code

``` cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 5;

int a[N], b[N];

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i <= n; i++) cin >> b[i];
		bool f = true;
		for(int i = 1; i <= n; i++)
		{
			if(a[i] == b[i]) continue;
			if(a[i] > b[i])
			{
				cout << "NO" << endl;
				f = false;
				break;
			}
			bool g = false;
			for(int j = i-1; j >= 1; j--)
			{
				if(a[j] == b[i])
				{
					g = true;
					break;
				}
				if(a[j] > b[i] || b[i] > b[j]) break;
			}
			for(int j = i+1; j <= n; j++)
			{
				if(a[j] == b[i])
				{
					g = true;
					break;
				}
				if(a[j] > b[i] || b[i] > b[j]) break;
			}
			if(!g)
			{
				cout << "NO" << endl;
				f = false;
				break;
			}
		}
		if(f) cout << "YES" << endl;
	}
	return 0;
}
```

---

## 作者：ENJOY_AK (赞：1)

## 思路：

由于数据范围不大，所以可以直接暴力做。

遍历 $ \texttt a$、$ \texttt b$ 数组，若出现 $ \text a_i > b_i$，直接输出 NO，不可能修改数更小，否则的话就向该元素两边分别遍历，直到找到符合条件的 $ \texttt a$ 元素。

这里需要注意一个点，当出现遍历 $\texttt a$ 元素大于所需 $\texttt b$ 元素或遍历 $\texttt b$ 元素小于所需 $\texttt b$ 元素时结束查找，因为会造成 $ \text a_i > b_i$ 的情况。

## 代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}

ll n,a[N],b[N],t;
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= n; i ++) cin >> b[i];
 
    for (int i = 1; i <= n; i ++) {
        if (a[i] == b[i]) continue;
        if (a[i] > b[i]) {
            cout << "NO" << endl;
            return;
        }
        int l = i, r = i;
        for (int j = i - 1; j >= 1; j --) {
            if (a[j] > b[i] || b[j] < b[i]) {
                break;
            }
            if (a[j] == b[i]) {
                l = j;
                break;
            }
        }
        for (int j = i + 1; j <= n; j ++) {
            if (a[j] > b[i] || b[j] < b[i]) {
                break;
            }
            if (a[j] == b[i]) {
                r = j;
                break;
            }
        }
        if (a[l] != b[i] && a[r] != b[i]) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}
int main(){
	cin >> t;
	while(t--){
		solve();
	}
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1904D1)

## 思路
循环每一个元素 $a_{i}$，判断其是否能够在**不影响别的元素的更改**的情况下改为 $b_{i}$，可以分为以下三类：
* 当 $a_{i} > b_{j}$ 时：由于每次操作是将 $a[l, r]$ 全部改为 $max(a_{l}, a_{l + 1}, a_{l + 2}, a_{l + 1}, ..., a_{r - 1}, a_{r})$，即所有元素都只会增加，也就是说每个元素都不可能更小了，所以此种情况说明无通过若干次操作使得两个数列相同，直接输出 NO 即可。
* 当 $a_{i} = b_{j}$ 时：无需修改。
* 当 $a_{i} < b_{j}$ 时：需要进行修改，向左右各自按以下规则寻找：
  * 当 $b_{j} < b_{i}$ 时，如果选中的区间包含 $j$ 会导致改变后 $j$ 无解（第一种情况）。
  * 当 $a_{j} > b_{i}$ 时，如果选中的区间包含 $j$ 最大值至少为 $a_{j}$，修改完后又会回到第一种情况。
  * 当 $a_{j} = b_{i}$ 且中途寻找到的都没有违反上两条时，则 $a_{i}$ 可以在不影响其他元素的情况下变为 $b_{i}$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAX(x, y) ((x >= y) ?(x) :(y))
#define MIN(x, y) ((x <= y) ?(x) :(y))
#define FOR(st, ed, i, stp, flag) for (int i = st; i <= ed && flag; i += stp)
#define FORR(st, ed, i, stp, flag) for (int i = ed; i >= st && flag; i -= stp)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double dou;
typedef pair<int, int> pii;

const int maxn = 1e3 + 10;

int t, n;
int a[maxn], b[maxn];

bool yes;
int l, r;

int main () {
	scanf("%i", &t);
	while (t--) {
		yes = true;
		
		scanf("%i", &n);
		FOR (1, n, i, 1, true) {
			scanf("%i", &a[i]);
		}
		FOR (1, n, i, 1, true) {
			scanf("%i", &b[i]);
		}
		
		FOR (1, n, i, 1, true) {
			if (a[i] == b[i]) {
				continue;
			}else if (a[i] < b[i]) {
				l = i;
				r = i;
				
				FORR (1, (i - 1), j, 1, a[j] <= b[i] && b[j] >= b[i]) {
					if (a[j] == b[i]) {
						l = j;
						break;
					}
				}
				FOR ((i + 1), n, j, 1, a[j] <= b[i] && b[j] >= b[i]) {
					if (a[j] == b[i]) {
						r = j;
						break;
					}
				}
				
				if (l == i && r == i) {
					printf("NO\n");
					yes = false;
					break;
				}
			}else if (a[i] > b[i]) {
				printf("NO\n");
				yes = false;
				break;
			}
		}
		
		if (yes) {
			printf("YES\n");
		}
	}
	return 0;
}

```

---

## 作者：Genius_Star (赞：0)

### 思路：

注意到每次都是赋值为较大值，故 $a_i$ 的变化一定是单调不降的；故若 $a_i > b_i$ 肯定无解。

若 $a_i \ne b_i$，要使得 $a_i = b_i$，首先要找到一个 $j$ 使得 $a_j = b_i$，可以选择 $[i, j]$ 这个区间。

那么若 $[i, j]$ 合法当且仅当：

- 在 $(i, j)$ 中不存在一个 $k$ 使得 $a_k > a_j$，因为此时 $[i, j]$ 中的最大值就不一定是 $a_j$ 了。

- 同时对于任意的 $k \in (i, j)$ 都需要满足 $b_k > b_i$，因为将 $a_k \gets b_i$ 后若 $a_k > b_k$ 是无解的。

总结一下无解：

- 若不存在 $j$，无解。

- 若 $\max\limits_{k = i}^j a_k > a_j$，无解。

- 若 $\min\limits_{k = i}^j b_k < a_j$，无解。

直接找左边和右边的第一个满足 $a_j = b_i$ 的 $k$ 判断即可；可以使用 ST 表维护最大最小值。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10, M = 19; 
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int T, n;
int a[N], b[N], lst[N];
int F[2][M][N];
bool f[N];
inline int askmax(int l, int r){
	int k = log2(r - l + 1);
	return max(F[0][k][l], F[0][k][r - (1 << k) + 1]);
}
inline int askmin(int l, int r){
	int k = log2(r - l + 1);
	return min(F[1][k][l], F[1][k][r - (1 << k) + 1]);
}
inline void solve(){
	n = read();
	for(int i = 1; i <= n; ++i)
	  F[0][0][i] = a[i] = read();
	for(int i = 1; i <= n; ++i)
	  F[1][0][i] = b[i] = read();
	for(int j = 1; j < M; ++j){
		for(int i = 1; i <= n && i + (1 << j) - 1 <= n; ++i){
			F[0][j][i] = max(F[0][j - 1][i], F[0][j - 1][i + (1 << (j - 1))]);
			F[1][j][i] = min(F[1][j - 1][i], F[1][j - 1][i + (1 << (j - 1))]);
		}
	}
	for(int i = 1; i <= n; ++i){
		if(a[i] == b[i])
		  f[i] = 1;
		else
		  f[i] = 0;
	}
	for(int i = 1; i <= n; ++i)
	  lst[i] = 0;
	for(int i = 1; i <= n; ++i){
		if(f[i] || !lst[b[i]]){
			lst[a[i]] = i;
			continue;
		}
		int j = lst[b[i]];
		if(askmax(j, i) > a[j]){
			lst[a[i]] = i;
			continue;
		}
		if(askmin(j, i) < a[j]){
			lst[a[i]] = i;
			continue;
		}
		f[i] = 1;
		lst[a[i]] = i;
	}
	for(int i = 1; i <= n; ++i)
	  lst[i] = 0;
	for(int i = n; i >= 1; --i){
		if(f[i] || !lst[b[i]]){
			lst[a[i]] = i;
			continue;
		}
		int j = lst[b[i]];
		if(askmax(i, j) > a[j]){
			lst[a[i]] = i;
			continue;
		}
		if(askmin(i, j) < a[j]){
			lst[a[i]] = i;
			continue;
		}
		f[i] = 1;
		lst[a[i]] = i;
	}
	for(int i = 1; i <= n; ++i){
		if(!f[i]){
			puts("NO");
			return ;
		}
	}
	puts("YES");
}
bool End;
int main(){
	T = read();
	while(T--)
	  solve();
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
我们给定两个长度均为 $n$ 的数组 $a$ 和 $b$，我们可以进行的操作是，从 $a$ 中选一段区间 $(l,r)$，将这段区间内的 $a_i$ 全部改成这段区间的最大值，问最后能否使 $a$ 变成 $b$。
## 分析
我们想这个操作只能让小数变成大数，那么对与 $a_i>b_i$ 的情况一定不行，其余情况我们继续分析，对于 $a_i<b_i$ 我们肯定要从 $a$ 的两侧找到一个等于 $b_i$ 的 $a_j$ 且 $a_j$ 一定要为 $i$ 到 $j$ 的最大值，才可以让 $a_i$ 变为 $a_j$，更重要的是，我们这样改一个区间，会不会让 $i$ 到 $j$ 里面出现 $a_i>b_i$。

综上，我们左右两边查找距离最近且值与 $b_i$ 值相同的点，只要找到的元素与 $a_i$ 之间不存在更大的元素，且这段区间内的 $b_j$ 均大于等于 $b_i$，那么就可以完成修改，两边有一边满足即可。
## 代码 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pi acos(-1)
#define xx first
#define yy second
#define endl "\n"
#define lowbit(x) x & (-x)
#define int long long
#define ull unsigned long long
#define pb push_back
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
#define LF(x) fixed << setprecision(x)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define Yshanqian ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
const int N = 1e6 + 10, M = 1010, inf = 0x3f3f3f3f, mod = 1e9 + 7, P = 13331;
const double eps = 1e-8;
void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++)cin >> a[i];
    for (int i = 1; i <= n; i++)cin >> b[i];
    auto check = [&](int x) -> bool{
        if (a[x] == b[x])return 1;
        if (a[x] > b[x]) return 0;
        int l = x, r = x;
        bool f1 = 0, f2 = 0;
        for (int i = x - 1; i >= 1; i--){
            if (a[i] > b[x] || b[i] < b[x]){f1 = 1;break;}
            if (a[i] == b[x]){l = i;break;}
        }
        for (int i = x + 1; i <= n; i++){
            if (a[i] > b[x] || b[i] < b[x]){f2 = 1;break;}
            if (a[i] == b[x]){r = i;break;}
        }
        if (r == x)f2 = 1;
        if (l == x)f1 = 1;
        if (f1 && f2)return 0;
        return 1;
    };
    for (int i = 1; i <= n; i++){
        if (!check(i)){cout << "NO" << endl;return;}
    }
    cout << "YES" << endl;
}
signed main(){
    Yshanqian;
    int T;
    T = 1;
    cin >> T;
    for (int cases = 1; cases <= T; ++cases) solve();
    return 0;
}
```

---

## 作者：sordio (赞：0)

# CF1904D1的题解
根据此题的数据范围可知，此题算法的时间复杂度应为 $O(n^2)$。

可以考虑枚举每一个 $a_i$ 能否变化为 $b_i$，如果每一个点都能成功变化，那么整体数列就可以变化。

但有一个问题，比如说 $A:[3,2,1,1,1] ~~~ B:[3,3,3,2,2]$ 这个样例中，如果我先将 $A_2$ 的 $2$ 转化为 $3$，那后面的 $A_4$ 和 $A_5$ 将无法转化为 $2$，即操作之间互相有影响。因为转化操作是转化为最大值，所以可以从小到大转化（即 $B_i$ 从小到大），这样操作之间就不会有影响。实际写代码时不需要考虑这一点，因为代码中不需要真的操作，只需要判断可行性即可。

那如何判断是否可以转化呢？首先，假设我们现在要将 $a_i$ 转化为 $b_i$，而我们找到的数字为 $a_j=b_i$（$j>i$）。由于变化操作是只增不减的，所以当 $a_i>b_i$ 时一定是无解的。同理，由于变化是区间的，所以在 $[b_i,b_j]$ 中只要有任意一个 $b_k<b_i$，那么这次变化是不合理的，因为 $a_k = b_i > b_k$，将无法变化成 $b_k$。

然后从 $a_i$ 出发分别向左右寻找，直到 $a_j=b_i$，但如果 $a_i$ 和 $a_j$ 之间由任意一个数 $a_k>b_i$，则无法变化。

综上所述，只需要考虑以上几个条件，就可以 AC 此题。

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int T,n,ans;
int a[N],b[N];

bool left(int x){ //向左搜
	for(int i=x;i>=1;i--){
		if(a[i]>b[x]||b[x]>b[i]) return 0; //判断是否存在 a[k]>b[i] 或 b[k]<b[i]
		if(a[i]==b[x]) return 1; //找到了！ 
	}
	return 0; //没找到
}

bool right(int x){ //同上，向右搜 
	for(int i=x;i<=n;i++){
		if(a[i]>b[x]||b[x]>b[i]) return 0;
		if(a[i]==b[x]) return 1;
	}
	return 0;
}

bool solve(){
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]) continue; //判断是否不用变化 
		if(a[i]>b[i]) return 0; //判断是否存在a[i]>b[i] 
		if(!left(i)&&!right(i)) return 0; //向左向右搜索 
	}
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
		}
		if(solve()) puts("YES");
		else puts("NO");
	}
	return 0;
}

---

