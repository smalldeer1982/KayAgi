# To Become Max

## 题目描述

You are given an array of integers $ a $ of length $ n $ .

In one operation you:

- Choose an index $ i $ such that $ 1 \le i \le n - 1 $ and $ a_i \le a_{i + 1} $ .
- Increase $ a_i $ by $ 1 $ .

Find the maximum possible value of $ \max(a_1, a_2, \ldots a_n) $ that you can get after performing this operation at most $ k $ times.

## 说明/提示

In the first test case, one possible optimal sequence of operations is: $[\textcolor{red}{1}, 3, 3] \rightarrow [2, \textcolor{red}{3}, 3] \rightarrow [\textcolor{red}{2}, 4, 3] \rightarrow [\textcolor{red}{3}, 4, 3] \rightarrow [4, 4, 3]$.

In the second test case, one possible optimal sequence of operations is: $[1, \textcolor{red}{3}, 4, 5, 1] \rightarrow [1, \textcolor{red}{4}, 4, 5, 1] \rightarrow [1, 5, \textcolor{red}{4}, 5, 1] \rightarrow [1, 5, \textcolor{red}{5}, 5, 1] \rightarrow [1, \textcolor{red}{5}, 6, 5, 1] \rightarrow [1, \textcolor{red}{6}, 6, 5, 1] \rightarrow [1, 7, 6, 5, 1]$.

## 样例 #1

### 输入

```
6
3 4
1 3 3
5 6
1 3 4 5 1
4 13
1 1 3 179
5 3
4 3 2 2 2
5 6
6 5 4 1 5
2 17
3 5```

### 输出

```
4
7
179
5
7
6```

# 题解

## 作者：MaxBlazeResFire (赞：7)

来一发二分答案的题解吧。

考虑如何 check。注意到数据范围允许平方级别的复杂度，故我们枚举第一维表示 **钦定位置 $a_l$ 成为最值**，第二维枚举 $r$ 表示检查 **是否能只改变 $[l,r]$ 之间的数使 $a_l$ 成为最值。**

换句话说，对于一个 $r$，我们需要知道 **恰好** 只需改变 $[l,r]$ 达到目标的条件。设目前二分的答案为 $x$，该条件就是 $\displaystyle\forall i\in[l,r],(x-i+l)>a_i$ 并且 $\displaystyle\sum_{i=l}^r(x-i+l)-a_i\leq k$。

若不满足第一个条件，那么需要操作的右端点位于 $r$ 之前，就不满足 **恰好** 的条件了。也就是说若存在一个位置 $i$ 使得 $(x-i+l)\leq a_i$，那么自然在位置 $r$ 之前就可以得出答案，此时直接退出即可。

复杂度 $O(n^2\log V)$.

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005

int n,k,a[MAXN],b[MAXN],Ans = 0;

inline bool chk( int x ){
	int tmp = k;
	for( int i = 1 ; i <= n ; i ++ ){
		tmp = k;
		for( int j = i ; j <= n ; j ++ ){
			if( a[j] < x - ( j - i ) ){
				if( tmp < ( x - j + i - a[j] ) ) break;
				tmp -= ( x - j + i - a[j] );
			}
			else return 1;
		}
	}
	return 0;
}

inline void solve(){
	scanf("%lld%lld",&n,&k);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]);
	int l = 0,r = 1e9,Ans = 0;
	while( l <= r ){
		int mid = ( l + r ) >> 1;
		if( chk( mid ) ) Ans = mid,l = mid + 1;
		else r = mid - 1;
	}
	printf("%lld\n",Ans);
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：7)

提供一种 $O(n^2)$ 的贪心做法。

$n$ 只有 $1000$，想的暴力一点，枚举最终成为答案的数 $a_i$。一开始肯定要利用 $a_{i+1}$ 让 $a_i$ 变得尽可能大，这样的代价是最小的。当 $a_i>a_{i+1}$ 时怎么办？利用 $a_{i+2}$ 让 $a_{i+1}$ 变大。

如果操作次数足够多，那么最终的序列肯定是形如 $x,x-1,\cdots,a_n+1,a_n$ 的。也就是说，依次枚举 $j\in[i+1,n]$，当 $a_j\ge a_{j-1}$ 时，至多就可以让 $a_i$ 变大 $a_j-a_{j-1}+1$，此时更新答案即可。如果不满足，$a_j$ 在后续的更新过程中肯定要变成 $a_{j-1}-1$，否则无法使 $a_i$ 变得更大，提前更新 $a_j$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

int n; i64 k; 
int a[1005], b[1005]; 

void solve(void) {
    cin >> n >> k; 
    for (int i = 1; i <= n; ++i) cin >> a[i]; 
    int ans = a[n]; 
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= n; ++j) b[j] = a[j]; 
        i64 t = k; 
        
        for (int j = i + 1; j <= n && t > 0; ++j) {
            if (b[j] < b[j - 1]) {
                t -= b[j - 1] - 1 - b[j]; 
                b[j] = b[j - 1] - 1; 
            } else {
                i64 ad = min(1ll * (b[j] - b[j - 1] + 1) * (j - i), t); 
                t -= ad; b[i] += ad / (j - i); 
            }
            ans = max(ans, b[i]); 
        }
    }
    cout << ans << "\n"; 
}

int main(void) {
    ios::sync_with_stdio(false);
    int T; cin >> T; 
    while (T--) solve(); 
    return 0;
}
```

---

## 作者：信息向阳花木 (赞：6)

赛时贪心半天没想出来，用二分过掉了。

我们可以二分 $k$ 次操作后 $a$ 的最大值 $mid$。

二分主要是 `check` 函数怎么写。

模拟一下样例，或许可以找到规律。如果 $a_i = x$，则 $a_{i - 1}$ 最多可以加到 $x + 1$。相反，如果想让 $a_i$ 的值变为 $x$，那么 $a_{i + 1} \ge x - 1$。由于 $n$ 非常小，所以我们可以 $O(n^2)$ 枚举。具体地，我们可以枚举 $i$，计算让 $a_i$ 变为 $mid$ 的最小步数。对于每个 $i$，我们可以利用上面的性质往后枚举，算出 $a_{i + 1}, a_{i+2},...,a_{n-1}$ 的最小值，再计算步数。由于 $a_n$ 的值是不可以改动的，所以枚举时有些边界问题需要注意。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1010;

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

int t, n, k, maxx;
int a[N];

bool check(long long mid)
{	
	for (int i = 1; i < n; i ++ )
	{
		long long cnt = 0, t = mid;
		for (int j = i; j < n; j ++ )
		{
			if(j == n - 1 && t - (long long)a[j] > 1ll * max(0, a[j + 1] - a[j] + 1)) //a[n-1] 需要加的步数不得大于 a[n-1] 最多能加的步数 
			{
				cnt = 1e18;
				break;
			}
			if(t <= 1ll * a[j]) break;
			cnt += (t - 1ll * a[j]);
			t --;
		}
		if(cnt <= 1ll * k) return 1;
	}
	return 0;
}

int main()
{
	in(t);
	while (t -- )
	{
		in(n); in(k);
		for (int i = 1; i <= n; i ++ ) in(a[i]);
		
		maxx = 0;
		for (int i = 1; i <= n; i ++ ) maxx = max(maxx, a[i]);
		
		long long l = (long long)maxx + 1ll, r = 1e18, mid;
		while (l <= r)
		{
			mid = l + r >> 1ll;
			if(check(mid)) l = mid + 1ll;
			else r = mid - 1ll;
		}
		printf("%lld\n", l - 1ll);
	}
	return 0;
}
```
~~赛时代码加了点注释，码风混乱，大佬轻喷~~

---

## 作者：qwq___qaq (赞：3)

警钟长鸣：

- 发现暴力可过交暴力也应该先看一下时间复杂度对不对。

- 都有能保证正确性的暴力了打出了能过的算法也应该先对拍一下。

***

这里给出一种**很不光彩**的思路。

时限 2s,CF 神机，$n=1000$，于是可以考虑 $O(n^3)$。

考虑一下哪些情况会对最大值产生影响：

- 首先考虑到对于一个区间 $[l,r]$，在 $r$ 不变化并且不限制操作次数的情况下，最大值显然是 $r+(r-l)$，因为 $r-1$ 最大是 $r+1$，$r-2$ 最大是 $r+2$，以此类推。

- 现在考虑 $r$ 变化的情况：假设 $r\gets r+1$，那么显然左边的都会 $+1$，但是此时若左边的没有 $+1$，但是此时左边的仍然是最大值，所以对最大值无影响，设剩余操作次数为 $k'$，那么显然最大值最多只能增加 $\lfloor\dfrac{k}{r-l+1}\rfloor$

此时枚举区间 $[l,r]$，但是呢，有一种可能，那就是如果 $a_r$ 不变，中间会有一个 $a_k$ 阻止增长。

那么此时我们可以遍历 $[l,r]$，然后就能得到 $a_r$ 至少要增长的值 $\Delta$，然后再遍历一次得到按照第一种情况增加的方案数 $s$。然后再考虑第二种情况的方案数，就是 $\lfloor\dfrac{k-s}{r-l+1}\rfloor$，注意到 $a_r$ 不能超过 $a_{r+1}+1$，所以要和 $a_{r+1}+1-(a_r+\Delta)$。

注意 $[l,r]$ 不可取的情况的判断：

- 方案 $1$ 之后操作次数已经大于 $k$，注意 $s$ 每次增长时都需要判断一次，或者开 ll。

- 方案 $1$ 预处理的时候要注意一下 $a_r$ 能否增加这么多。

哦对了 $a_n$ 不能增长所以 $a_{n+1}$ 直接赋 $0$ 即可。

- 后记：关于 $O(n^2)$

其实呢固定 $r$，然后倒序枚举 $l$，就可以递推了，好像这样 $s$ 一超出就 `break` 还可以减少一个实现细节。

---

## 作者：ax_by_c (赞：2)

一眼二分。

因为不会超时，考虑用 $O(n^2)$ 的时间来判断是否可行。

我们先枚举 $i$，然后判断能否让 $a_i$ 变为 $mid$。

如果 $mid \le a_i$，那么显然是可行的。

否则则说明要让 $a_i$ 变大。

我们先不考虑选数的限制，那么需要加上 $mid - a_i$。

现在有了选数的限制，所以我们最多只能加到 $a_{i+1}+1$。

如果还要往上加就只能把 $a_{i+1}$ 增加。

所以可以这样来判断：

统计所需要加的最小次数，设 $nd_i$ 表示第 $i$ 位所需要加到的数（$nd$ 单调递减），然后用指针 $j$ 向后统计最小要加的次数。

这题的样例很阴间，坑点也很多：

1.如果满足 $nd_j \le a_j $，则说明已经不需要加了，直接退出。

2.最后一次修改的位置不能是 $n$。

3.如果最后一次修改的位置是 $n-1$，则修改后的值不能超过 $a_n+1$。

4.对于每个 $i$ 的统计都是相互独立的，所以每次统计前要先复制一遍。

---

## 作者：jiangchen1234 (赞：2)

### 题意
$t$ 组数据。

每一组数据中有 $n,k$ 和一个数组 $a$。

有 $k$ 次操作，每次操作可以使 $a_{i} + 1$，$i$ 满足 $1 \le i \le n$ 且  $a_{i} \le a_{i + 1}$。
### 思路
我们可以用二分答案来做。

因为结果最大是 $2 \times 10^8$，最小值是 $a_{max}$，对结果进行二分。

来看一下 $check$ 咋写。

先枚举最大值的位置，若这个位置的值操作后能达到 $mid$ 的话，那么 $a_{i - 1}$ 的值至少为 $mid - 1$，之后的值也可以递推出来。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define rg register
#define IOS ios::sync_with_stdio(false);cin.tie(0); cout.tie(0)
using namespace std;
int t,n,k,a[1005];
bool check(int x) {
	for(rg int i(1); i <= n; ++i) {
		int pos = k,flag = 0;
		pos -= x - a[i];
		if(pos < 0){
			continue;
		}
		for(rg int j(i + 1); j <= n; ++j) {
			if(a[j] < x + i - j){
				pos -= x - j + i - a[j];
				if(pos < 0) break;
			}
			else{
				flag = 1;
			}
		}
		if(flag) return 1;
	}
	return 0;
}
signed main() {
	IOS;
	cin>>t;
	while(t--) {
		int maxx = 0,ans = 0;
		cin>>n>>k;
		for(rg int i(1); i <= n; ++i) {
			cin>>a[i];
			maxx = max(maxx,a[i]);
		}
		int l = maxx,r = 2e8;
		ans = maxx;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(check(mid)) {
				ans = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1856C)

这题二分，但这位蒟蒻被家长赶去睡觉了，没调完代码。

这题二分枚举的是最大值，也就是答案。二分时二分数组 $a$ 中最大的数加 $1$ 到 $10^9$ 的这个区间，$ans$ 的初值先设成 $a$ 中最大的数。

接下来就是套模板，二分的过程就不讲了，主要讲二分中的 `check`。

这个 `check` 判断的是 $mid$ 是否能在数组 $a$ 进行一系列操作后由某个元素达成。

先是第一重循环枚举 $mid$ 是由数组 $a$ 中的元素 $a_i$ 达成，枚举到 $n-1$。接下来枚举找到一个下标 $la$ 表示 $a_i$ 若想变成 $mid$ 只需要让 $a_i$ 到 $a_{la-1}$ 这个区间的所有数去进行操作就行了，这样子可以保证操作数最小。

最后用一个循环计算从 $a_i$ 到 $a_{la-1}$ 中所有的数变为能符合 $a_i$ 为 $mid$ 所花费的最小操作数。这里可以去用样例模拟一下思路，这里我直接给出每次的最小操作数的公式：$\text{max}(0,mid+i-j-a_j)$，但最好别抄，自己模拟一下样例就行了。这个公式的具体意思就是每个 $a_j$ 所需要变成的数是从 $a_i$ 变成的 $mid$ 递减 $1$ 下来的。为什么是递减 $1$，因为当 $a_i=a_{i+1}$ 时，操作完后 $a_i=a_{i+1}+1$，才有可能更新最大值，所以从 $a_i$ 到 $a_{la-1}$ 是递减的，这样也能保证操作数最小。

查找 $la$ 时的判断用的也是刚才那个公式，这里我就不给了，直接看代码就行。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[1010],maxx=-1;
inline bool check(int mid)
{
	for(register int i=1;i<=n-1;i++)
	{
		int la=-1;
		long long s=0;
		for(register int j=i+1;j<=n;j++)
			if(a[j]>=mid+i-j){la=j;break;}
		if(la==-1) continue;
		for(register int j=i;j<=la-1;j++)
		{
			s+=max(0,mid+i-j-a[j]);
			if(s>k) break;
		}
		if(s<=k) return 1;
	}
	return 0;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int l,r=1e9,ans;
		scanf("%d%d",&n,&k);
		for(register int i=1;i<=n;i++) scanf("%d",&a[i]),maxx=max(maxx,a[i]);
		ans=maxx,l=maxx+1;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",ans),maxx=-1;
	}
	return 0;
}
```

---

## 作者：gan1234 (赞：1)

## 题意
有 $k$ 次操作，每次操作可以选择一个满足 $1\le i<n$ 和 $a_i\le a_{i+1}$ 的 $a_i$，使 $a_i$ 加一。询问 $k$ 次操作后 $\max(a_1,a_2,...a_n)$ 最大为多少。

## 分析
最大化，最小化某个值，一般可以考虑二分答案。我们发现，要想把 $a_i$ 加到 $x$，必须满足 $a_{i+1}\ge x-1$。我们分情况解决。

- $a_{i+1}\ge x-1$ 不用管，可以直接操作 $a_i$。
- $a_{i+1}<x-1$ 需要先把 $a_{i+1}$ 加到 $x-1$。

因此判断能不能把 $a_i$ 加到 $x$，可以从 $a_i$ 开始往后枚举，是第二种情况，就减去相应的操作次数，继续检查下一个。如果操作次数不够，说明不能把 $a_i$ 加到 $x$，直接退出循环。如果遇到第一种情况，说明操作数足够把 $a_i$ 加到 $x$。

二分答案 $x$，枚举所有数判断能不能把 $a_i$ 加到 $x$，二分复杂度 $O(\log \max(a_i)+k)$ 约等于 $O(\log k)$，枚举判断复杂度 $O(n^2)$，总复杂度 $O(n^2\log k)$。

最后注意 $ans=\max(ans,\max(a_i))$。

## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
int a[10005];
int check(int x){
    for(int i=1;n>i;i++){
        int p=k;p-=x-a[i];
        if(p<0)continue;
        for(int j=i+1;n>=j;j++){
            if(a[j]>=x-(j-i))return 1;
            else if(j==n)break;
            else if(p>=x-(j-i)-a[j])p=p-(x-(j-i)-a[j]);
            else break;
        }
    }
    return 0;
}
void solve(){
    cin>>n>>k;
    int ans=0;
    for(int i=1;n>=i;i++)cin>>a[i];
    for(int i=1;n>=i;i++)ans=max(ans,a[i]);
    int l=1,r=k+ans;
    while(r>l){
        int mid=(l+r)/2;
        if(check(mid))l=mid+1;
        else r=mid;
    }
    while(check(l))l++;
    while(!check(l))l--;
    cout<<max(l,ans)<<endl;
}
signed main(){
    int _T;
    cin>>_T;
    while(_T--){
        solve();
    }
    return 0;
}
~~~

---

## 作者：abensyl (赞：0)

原题：[CF1856C To Become Max](https://www.luogu.com.cn/problem/CF1856C)。

一道关于二分的好题。

## 思路

简要题意：对于一个数组中的元素 $a_i$，如果 $a_i\leq a_{i+1}$，那么可以选择将 $a_i$ 加一，也可以不加。

那么，我们一个数如果想增加，它就必须小于或者等于它后一个元素，换句话说，增加过 $1$ 之后，他顶多比他后一个元素大 $1$，所以，对于任意一个数字 $a_i$，将其变为 $a_i+b$（$b$ 为一个常数）需要花费的代价都是可以计算出来的，容易想到二分。

二分时，对于每一个 $a_i$，检验它能变成的最大的元素即可，最终的答案就是对于 $a$ 序列的所有元素可以变成的最大值中的最大值。

注意：最后一个元素没有后一个元素，所以它的值不能发生变化！

## 代码

```cpp
int a[2005];
int n,k;
int check(int id,int nm) {
	int zc=0;
	for(int i=id,j=nm;i<=n;++i,--j) {
		if(a[i]>=j) break;
		if(i==n) return 1e9;
		zc+=j-a[i];
	}
	return zc;
}
void solve() {
	// do something
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	int res=0;
	for(int i=1;i<=n;++i) {
		//cout<<i<<": ";
		int l=a[i],r=a[i]+k;
		while(l<=r) {
			int mid=l+r>>1;
			//cout<<mid<<' '<<check(i,mid)<<'\n';
			if(check(i,mid)<=k) l=mid+1;
			else r=mid-1;
		} res=max(res,r);
		//cout<<r<<' '<<check(i,r)<<'\n';
	} cout<<max(res,a[n])<<'\n';
	return;
}
```

[我的代码 + AC记录。](https://codeforces.com/problemset/submission/1856/217293314)

---

## 作者：shipeiqian (赞：0)

# CF1856C 题解

## 题意

有 $n$ 个整数和 $k$ 次操作，每次操作可以选择一个 $i$ 使得 $a_i\leq a_{i+1} (1\leq i<n)$，然后让 $a_i=a_i+1$。求最后可能的最大值。

## 思路

根据条件可知，$\max(a_i)=a_{i+1}+1$，所以想要最大化某个数字，就要先把后面的数字全部最大化。

## 做法

可以二分最终的最大值，然后遍历每个数，求出将这个数字化为最大值的操作数是多少，然后比较是否有某个位置可以用至多 $k$ 次操作成为此最大值即可。

## Code

```cpp
#include <bits/stdc++.h>
#define de "debug"
using namespace std;
typedef long long ll;
ll n,k,a[1005];
bool check(ll x){
    for(int i=1;i<=n;i++){
        ll need=0,now=x;//now是当前位置需要的值
        for(int j=i;j<=n;j++){
            if(now<=a[j])break;//如果当前值已经足够，就直接退出判断
            if(j+1>n){//如果到了最后一个，还没完，就说明不可行
                need+=k+1;//让这个值大于k即可
                break;
            }
            need+=now-a[j];
            now=max(0ll,now-1);//修改需要的值
        }
        if(need<=k)return true;//只要当前位置可以就行
    }
    return false;
}
void solve(){
    cin >>n >>k;
    ll minn=1e18,maxx=0;
    for(ll i=1;i<=n;i++)cin >>a[i],minn=min(minn,a[i]),maxx=max(maxx,a[i]);
    ll l=minn,r=maxx+k,mid;//下界也可以是maxx
    while(l+1<r){
        mid=(l+r)/2;
        if(check(mid))l=mid;
        else r=mid;
    }
    if(check(r))cout <<r <<"\n";
    else cout <<l <<"\n";
}
int main(){
    ll T=1;
    cin >>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：Drind (赞：0)

听说大家都是二分答案？这里给一种不是二分答案的解法。

首先我们枚举要让哪个数作为最大值，然后我们要让最大值之后的数变成 $n,n-1,n-2,\dots$ 我们才能每次遇到一个新的数的时候就能让我们的最大值变大。

拿样例举个栗子：
```
5 6 
1 3 4 5 1
```
假设第二个数是最大值，那么我们往前找。找到的第一个数是 4，现在我们可以把 3 变成 5，我们继续往下找，找到了 5，那么我们就可以把前面两个数都加二，序列变成 $1,7,6,5,1$，这时正好用完所有的次数，答案为 7。

如果遇到的数字比他的预期小怎么办？我同样拿样例举个栗子：
```
5 6
6 5 4 1 5
```
假设第一个数是最大值，那么我们往前找。找到的第一个数是 5，那这个数没法再给我们的最大值加了，我们继续找，找到了 4，同样的也没法加了，我们继续找，找到了 1。那这回不对了，因为这个数至少是 3 我们才能满足后一个数比前一个数大 1 的规律，那么我们把他补全成 3。我们找到的下一个数是 5，我们可以把前面四个数都加上 3，但是我们没有那么多次数了，所以前面每个数加上 1。最终序列变成 $7,6,5,4,5$，答案为 7。

按方法模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int a[N];
void fake_main(){
	int n,k,ans=0,tot=0; cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		ans=a[i];
		int tmp=k,num=1;//tmp代表还剩下的次数，num代表现在加一次需要加几个数
		for(int j=i+1;j<=n;j++){
			if(a[j]+j-i>ans){//a[j]+j-i是如果以最大值开头，这个数结尾的下降序列里最大值的值，大于ans代表可以加，小于ans代表需要补全
				int kt=tmp/num;
				if(kt>=a[j]+j-i-ans){//判断现在的次数还能不能加完
					tmp-=(a[j]+j-i-ans)*num;
					ans=a[j]+j-i;
					num++;
				}else{
					ans+=kt;
					break;
				}
			}else if(a[j]+j-i<=ans){//补全
				tmp-=ans-a[j]-j+i;
				num++;
				if(tmp<0) break;
			}
		}
		tot=max(tot,ans);
	}
	cout<<tot<<endl;
}

int main(){
	int t;
	cin>>t;
	while(t--) fake_main();
}
```

---

