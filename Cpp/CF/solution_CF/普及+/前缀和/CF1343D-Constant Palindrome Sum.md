# Constant Palindrome Sum

## 题目描述

You are given an array $ a $ consisting of $ n $ integers (it is guaranteed that $ n $ is even, i.e. divisible by $ 2 $ ). All $ a_i $ does not exceed some integer $ k $ .

Your task is to replace the minimum number of elements (replacement is the following operation: choose some index $ i $ from $ 1 $ to $ n $ and replace $ a_i $ with some integer in range $ [1; k] $ ) to satisfy the following conditions:

- after all replacements, all $ a_i $ are positive integers not greater than $ k $ ;
- for all $ i $ from $ 1 $ to $ \frac{n}{2} $ the following equation is true: $ a_i + a_{n - i + 1} = x $ , where $ x $ should be the same for all $ \frac{n}{2} $ pairs of elements.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
4 2
1 2 1 2
4 3
1 2 2 1
8 7
6 1 1 7 6 3 4 6
6 6
5 2 6 1 3 4```

### 输出

```
0
1
4
2```

# 题解

## 作者：Andrewzdm (赞：14)

[也许更好的阅读体验](https://blog.csdn.net/Andrewzdm/article/details/105682808)

# [CF1343D Constant Palindrome Sum](https://www.luogu.com.cn/problem/CF1343D)

打比赛的时候这道题没想出来，等到想出来的时候比赛结束了……$qwq$

下面进入正题：（前一部分我会复盘我的思路过程供大家参考，当然这是一个**蒟蒻的思考过程**， 大家完全可以跳过）

* * * *

首先拿到题目，先想了下能否贪心，发现找不到贪心策略。毫无头绪，我开始尝试寻找突破口。这时我发现题目有一点比较奇怪：题目给了 $k$ 的范围还保证 $\sum k \leq 2 \times 10^5$。这就在暗示我们复杂度正常情况下应该含有 $k$（大部分题目还是没有废话的）。

接下来我观察到因为所有的数（初始的和替换的）都在 $[1,k]$ 内，所以每一对数的和一定在 $[2,2k]$ 内。

那么我们不妨考虑枚举题目中要求的等式
$$a_i + a_{n-i-1} = x$$
中的 $x(2 \le x \le 2k)$，算出每一对数需要替换多少个数，最后在所有的结果中取 $\min$，时间复杂度为 $O(nk)$。

但是这样会 $\texttt{TLE}$，为了不超时，基于枚举 $x$ 的算法思想，时间复杂度要么 $O(k \log n)$ 要么 $O(k+n)$。

首先我想出了一个解法，然而很遗憾是错的。这个想法是这样的（不想看的可以跳过）：  
把每一对数的总和进行排序，然后把所有的总和分成 $sum<x,sum=x,sum>x$ 三个部分。当 $2 \le x \le k$ 时，除了 $sum=x$ 的一部分，剩下的两部分都要进行一次替换。还没开始想 $k < x \le 2k$ 的情况，我就发现我错了：
> 比方说给定的 $a$ 是 $1,2,2,3$，求出总和排序后是 $4,4$。当 $x=2$ 时，我们会计算出替换次数为 $2$。可是 $2,2$ 这一对数要想总和为 $2$ 必须替换两次。所以替换次数应该为 $3$。

好吧，只能换思路了。

接下来是正解：
----

我们先前的算法之所以是 $O(nk)$，是因为我们在枚举 $x$ 的过程中才计算每一对数需要替换多少个。为了优化，我们需要想办法进行**预处理**，算出对于每一个 $x$，有多少对数可以一个都不替换，有多少可以只替换其中一个，有多少必须两个都要替换。

不妨考虑各个击破：
### 一个都不替换
这个很简单，我们开一个数组 $equ$，其中 $equ_i$ 表示当 $x=i$ 时有多少对数可以一个都不替换。 因为不用替换的条件就是一对数的和 $sum=x$，那么我们只要算出每一对数的和 $sum$，并且 `equ[sum]++` 就可以了。
### 只需要替换其中一个
首先，对于一对数 $a_i,a_{n-i+1}$，在只替换其中一个数的情况下，它们的和只能在 $[\min(a_i,a_{n-i+1})+1, \max(a_i,a_{n-i+1})+k]$ 中。我们稍微变通一下，求出有多少对数**至多**需要替换一个，那么**只**需要替换一个的数目就很好求了，为至多需要替换一个的数目减去一个都不需要替换的数目。

那么如何求出有多少对数至多需要替换一个？这个问题就变成了：对于 $x$，求出有多少个区间 $[\min(a_i,a_{n-i+1})+1, \max(a_i,a_{n-i+1})+k]$ $(1 \le i \le \dfrac{n}{2})$ 覆盖了 $x$。

这一问题可以这样解决（而且对于类似的“求每一个数有多少个区间覆盖了此数”的问题都可以这样做）：  
开一个数组 $cover$，$cover_i$ 表示有多少个区间覆盖了数 $i$。首先枚举区间，设区间的左右端点分别为 $l,r$，然后我们进行操作 `cover[l]++` 和 `cover[r+1]--`，枚举完后再用计算前缀和的方式进行如下操作： `cover[i] += cover[i-1]`。然后我们就求完了。

下面解释下算法的原理：其实我们 `cover[l]++` 和 `cover[i] += cover[i-1]` 的两个操作等效于对于所有的 $i \in [l,rbound]$ 进行 `cover[i]++`。类似的，我们也进行了 `cover[i]--`$(i \in [r+1, rbound])$。前一个操作计算了有多少个区间的左端点小于等于 $x$，而后一个操作计算了有多少个区间的右端点小于 $x$。一加一减就是覆盖了 $x$ 的区间数目。

如果还是难以理解，可以尝试自己举个栗子模拟一下，这里就不赘述了。
### 两个都需要替换
因为我们求出了 $cover$，这一问题相当简单。一句话搞定：
$$num_i = \dfrac{n}{2} - cover_i$$

不要忘了我们的 $cover_i$ 表示有多少对**至多**需要替换一个数。

所以我们对于每个 $x$，最少替换步数 $ans_x$ 就可以这样计算：
$$ans_x = cover_x - equ_x + num_x \times 2$$

最终时间复杂度 $O(k+n)$。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int equ[2 * maxn], cover[2 * maxn], a[maxn];

signed main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int n, k;
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++)
			scanf("%d", a + i);
      //注意值域最大为2k，初始化到2k+4比较保险。
		fill(equ, equ + 2 * k + 5, 0);
		fill(cover, cover + 2 * k + 5, 0);
		for(int i = 1; i <= n / 2; i++)
			equ[a[i] + a[n - i + 1]]++;
		for(int i = 1; i <= n / 2; i++)
		{
			cover[min(a[i], a[n - i + 1]) + 1]++;
			cover[max(a[i], a[n - i + 1]) + k + 1]--;//注意加上k之后还要加上1
		}
		for(int i = 3; i <= 2 * k; i++)//值域最小为2，所以从3开始做前缀和就可以了
			cover[i] += cover[i - 1];
		int ans = INT_MAX;
		for(int x = 2; x <= 2 * k; x++)
			ans = min(ans, cover[x] - equ[x] + (n / 2 - cover[x]) * 2);//这里就没有再开一个数组num了
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：andyli (赞：9)

题意：  

给出一个包含 $n$ 个整数的数组 $a$ ，保证 $1\leq a_i \leq k$，修改其中的几个数为 $[1,k]$ 的整数，使得 $\forall i\in \left[1,\frac{n}{2}\right], a_i+a_{n-i+1}$ 为同一个数。最小化修改的次数，并输出。  

$2\leq n\leq 2\times 10^5, 1\leq k\leq 10^5$。  

分析：  

枚举最终修改完成后的 $x=a_i+a_{n-i+1}$，易知每对 $(a_i, a_{n-i+1})$ 至多修改 $2$ 次，若 $c_i (1\leq i\leq \frac{n}{2})$ 表示数对 $(a_i, a_{n-i+1})$ 最少需改 $j$ 次才能使 $a_i+a_{n-i+1}=x$，则答案为 $\sum\limits_{i=1}^{\frac{n}{2}}c_i$。
  
- 当 $a_i+a_{n-i+1}=x$ 时，$c_i=0$ 
- 否则，当 $\min\{a_i, a_{n-i+1}\} + 1\leq x\leq \max\{a_i, a_{n-i+1}\} + k$ 时 $c_i=1$
- 否则，$c_i=2$

对于每组 $(a_i, a_{n-i+1})$，用差分或数据结构将区间 $[\min\{a_i, a_{n-i+1}\} + 1,\max\{a_i, a_{n-i+1}\} + k]$ 的所有数加 $1$ ，将 $a_i+a_{n-i+1}$ 减 $1$ ，在枚举时直接统计即可。  

时间复杂度 $\mathcal O(n)$ 。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
constexpr int maxn = 200005, INF = -1u / 2;

int A[maxn], cnt0[maxn << 1], cnt1[maxn << 1];
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n, k;
        io.read(n, k);
        for (int i = 1; i <= (k << 1); i++)
            cnt0[i] = cnt1[i] = 0;
        for (int i = 1; i <= n; i++)
            io.read(A[i]);
        for (int i = 1; i <= n / 2; i++) {
            cnt0[A[i] + A[n - i + 1]]++;
            // 差分
            cnt1[min(A[i], A[n - i + 1]) + 1]++;
            cnt1[max(A[i], A[n - i + 1]) + k + 1]--;
            cnt1[A[i] + A[n - i + 1]]--;
            cnt1[A[i] + A[n - i + 1] + 1]++;
        }
        int ans = INF;
        for (int i = 2; i <= (k << 1); i++)
            cnt1[i] += cnt1[i - 1], chkmin(ans, cnt1[i] + (n / 2 - cnt1[i] - cnt0[i]) * 2); // cnt1 -- 一次, n/2-cnt1-cnt0 -- 两次
        writeln(ans);
    }
    return 0;
}
```

---

## 作者：do_while_true (赞：2)

设一个 $b$ 序列， $b_i$ 表示 $x=i$ 时需要的修改次数。我们把 $a_i$ 和 $a_{n-i+1}$ 分成一组。则每一组对 $b$ 数组会有一个影响。我们通过给 $b$ 进行差分，来达到  $\mathcal{O}(1)$ 修改，最后 $\mathcal{O}(n)$ 取一遍 $min$ 即可。

具体怎样差分可以手玩一下，如果推不出来再看代码。

### [$\mathcal{Code}$](https://codeforces.ml/contest/1343/submission/77568679)

---

## 作者：F_Mu (赞：2)

**题意**

多组样例

给一个长度为$n$（$n$一定为偶数）的数组$a[]$，给一个正整数$k$，保证数组内元素为小于等于$k$的正整数，你可以每次将数组的一个元素变为小于等于$k$的正整数，问最少多少次操作后，数组能满足对于任意$i$，有$a[i]+a[n-i+1]=x$，$x$为任意值，即所有$a[i]+a[n-i+1]$相等

**分析**

枚举$x$然后判定肯定是不现实的，考虑分析$a[i]+a[n-i+1]$的性质，此处设$j=n-i+1$

+ 两个数字都不改变，得到的和为$a[i]+a[j]$
+ 改变一个数字，可以得到的和为$[\min(a[i],a[j])+1,\max(a[i],a[j])+k]$区间中的任意一个数（将较大数变为$1$得到最小和，将较小数变为$k$得到最大和）
+ 改变两个数字，可以得到的和为$[2,2*k]$区间中的任意一个数

综上，对于($i,j)$，对于$[2,\min(a[i],a[j])]$的贡献为$2$，对于$[\min(a[i],a[j])+1,a[i]+a[j]-1]$的贡献为$1$，对于$a[i]+a[j]$的贡献为$0$，对于$[a[i]+a[j]+1,\max(a[i],a[j])+k]$的贡献为$1$，对于$[\max(a[i],a[j])+k+1,2*k]$的贡献为$2$

遍历每一组数字，我们可以得到这对数字对$[2,2*k]$区间内的$x$的贡献，然后取操作数最小的$x$的操作数即可

由于是区间贡献，采取前缀和数组或者树状数组皆可，这里采取前缀和数组

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
//#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
const int maxn = (ll) 4e5 + 5;
const int mod = (ll) 1e9 + 7;
const int inf = 0x3f3f3f3f;
int T = 1;
int n, a[maxn], k;
int sum[maxn];

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= 2 * k; ++i)
        sum[i] = 0;
    for (int i = 1; i <= n / 2; ++i) {
        int now = a[i] + a[n - i + 1];
        int maxx = max(a[i], a[n - i + 1]) + k + 1;
        sum[2] += 2;
        --sum[min(a[i], a[n - i + 1]) + 1];
        --sum[now];
        ++sum[now + 1];
        ++sum[maxx];
    }
    int ans = inf;
    for (int i = 2; i <= 2 * k; ++i)
        sum[i] = sum[i - 1] + sum[i], ans = min(ans, sum[i]);
    cout << ans << '\n';
}

signed main() {
    start;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```



---

## 作者：KellyFrog (赞：1)

只会打暴力的我瑟瑟发抖，第一次CF，记录下吧。

D题，大意：给出一个序列$a$和$k$，每次可以修改序列中的一个数为$[1,\frac{k}{2}]$中的一个数，求修改几次可以使得所有$a_i+a_{n-i+1}$相等。

都说了是第一次CF，所以就不太可能搞出什么东西，只可能打暴力。于是我们可以得到一个非常简单的$O(nk)$的暴力。

```cpp
#include <iostream>
 
using namespace std;
 
const int MAXN = 2e5 + 5;
 
int a[MAXN], sum[MAXN << 1];
 
int main() {
	int t, n, k;
	cin >> t;
	while(t--) {
		int ans = 2147483647;
		cin >> n >> k;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		
		for(int i = 0; i <= (k << 1); i++) {
			int res = 0;
			for(int j = 1; j <= (n >> 1); j++) {
				if(max(a[j], a[n - j + 1]) + k < i) {
					res += 2;
					
				} else if(min(a[j], a[n - j + 1]) >= i) {
					res += 2;
				} else if(a[j] + a[n - j + 1] != i) {
					res++;
				}
			}
			ans = min(ans, res);
		}
	}
	return 0;
}
```

然后这显然是过不了的，~~但我还是卡了半天常，万一呢？~~

于是我们考虑优化这个算法。

程序中的最后一个`else-if`是统计有多少个$a_j+a_{n-j+1}\neq i$的，显然可以预处理掉。

前面的两个枚举我们发现只要找到符合条件的数量且不关心他们在哪里，所以我们分别排序`max(a[i],a[n-i+1])+k)`和`min(a[i],a[n-i+1])`之后二分就行了。

总复杂度$O(n\log n+k\log n)$

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 2e5 + 5;

int a[MAXN], sum[MAXN << 1];

int cnt[MAXN];
int t, n, k;

int mini[MAXN], maxi[MAXN]; 

int main() {
	cin >> t;
	while(t--) {
		int ans = 2147483647;
		cin >> n >> k;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		
		memset(mini, 0, sizeof mini);
		memset(maxi, 0, sizeof maxi);
		memset(cnt, 0, sizeof cnt);
		
		for(int i = 1; i <= (n >> 1); i++) {
			cnt[a[i] + a[n - i + 1]]++;
			mini[i] = min(a[i], a[n - i + 1]);
			maxi[i] = max(a[i], a[n - i + 1]) + k;
		}
		
		sort(mini + 1, mini + 1 + (n >> 1), greater<int>());
		sort(maxi + 1, maxi + 1 + (n >> 1));
		
		
		for(int i = 0; i <= (k << 1); i++) {
			int cur = (n >> 1) - cnt[i]; //先处理成有多少个a[j]+a[n - j + 1] != i
			int left = 1, right = (n >> 1);
			int res = 0;
			while(left <= right) {
				int mid = (left + right) >> 1;
				if(mini[mid] >= i) {
					res = mid;
					left = mid + 1;
				} else {
					right = mid - 1;
				}
			}
			cur += res;
			
			res = 0;
			left = 1, right = (n >> 1);
			while(left <= right) {
				int mid = (left + right) >> 1;
				if(maxi[mid] < i) {
					res = mid;
					left = mid + 1;
				} else {
					right = mid - 1;
				}
			}
			cur += res;
			
			ans = min(ans, cur);
		}
		cout << ans << endl;
	}
	return 0;
}
```

~~其实本来是可以用STL一行搞定的，但不知道为什么我一写`lower_bound`和`upper_bound`就锅所以只能手写二分了。~~

---

## 作者：aCssen (赞：0)

唐氏人的唐氏做法。。。
### Solution

考虑枚举一个 $m \in[2,2k]$，表示 $a_i+a_{n-i+1}=m$，计算每一对 $a_i+a_{n-i+1}$ 的代价，显然，这个代价不超过 $2$。

令 $j=n-i+1$。

+ 若 $a_i+a_j=m$，无需处理。

+ 若 $a_i+a_j<m$，我们想用一次操作解决，那么 $m-a_i-a_j \le k-\min(a_i,a_j)$，也就是 $a_i+a_j-\min(a_i,a_j) \ge m-k $。含义就是选取小的一个最多加到 $k$，如果 $m$ 与 $a_i+a_j$ 的差不超过这个增加量就可以一次操作，否则就需要两次。

+ 若 $a_i+a_j>m$，我们可以类似的得到只需花费一次的条件是 $a_i+a_j>m,a_i+a_j-\max(a_i,a_j) \le m-1$，这个减一是因为不能取到 $0$。

这里我们有两个限制条件，考虑使用**平衡树**维护 $m$ 两边的数，小于 $m$ 的维护 $a_i+a_j-\min(a_i,a_j)$，每次查询树的大小和 $\ge m-k$ 的数的数量。大于 $m$ 的维护 $a_i+a_j-\max(a_i,a_j)$，每次查询 $\le m-1$ 的数量，算出答案即可。

每次 $m$ 变化时只需在左树删掉 $a_i+a_j=m$ 的对，右树加上 $a_i+a_j=m$ 的对即可，注意更新的顺序。

对于和为定值，我们可以用值域个 vector 维护。

注意清空，时间复杂度 $\mathcal{O}(\sum n \log n)$，没有任何优势。

### Code
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int maxn=2e5+5;
int a[maxn];
vector<int>L[maxn<<1],R[maxn<<1];
struct node{
	struct Node{int ls,rs,key,dat,siz;}t[maxn<<1];
	int root,tot,seed=19260817;
	int rnd(){int ret=seed;seed=(seed*7+13)%1000000007;return ret;}
	int Random(int N=998244353){return 1ll*rnd()*rnd()%N+1;}
	int New(int key){t[++tot]=(Node){0,0,key,Random(),1};return tot;}
	void pushup(int p){t[p].siz=t[t[p].ls].siz+t[t[p].rs].siz+1;}
	void split(int x,int key,int &p,int &q){
		if(!x) return p=q=0,void();
		if(t[x].key<=key) p=x,split(t[x].rs,key,t[x].rs,q);
		else q=x,split(t[x].ls,key,p,t[x].ls);
		pushup(x);
	}
	int merge(int x,int y){
		if(!x||!y) return x|y;
		if(t[x].dat<t[y].dat)
			return t[x].rs=merge(t[x].rs,y),pushup(x),x;
		return t[y].ls=merge(x,t[y].ls),pushup(y),y;
	}
	int Get(int key,bool is){
		int x,y,ans;
		split(root,key-is,x,y);
		if(is) ans=t[y].siz;
		else ans=t[x].siz;
		root=merge(x,y);
		return ans;
	}
	void insert(int key){
		int x,y;split(root,key-1,x,y);
		root=merge(x,merge(New(key),y));
	}
	void remove(int key){
		int x,y,z;
		split(root,key-1,x,z);split(z,key,y,z);
		y=merge(t[y].ls,t[y].rs);
		root=merge(x,merge(y,z));
	}
}A,B;
void solve(){
	int n=read(),k=read(),ans=2e9;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=2;i<=2*k;i++) L[i].clear(),R[i].clear();
	for(int i=1,j=n;i<j;i++,j--){
		L[a[i]+a[j]].push_back(a[i]+a[j]-min(a[i],a[j]));
		R[a[i]+a[j]].push_back(a[i]+a[j]-max(a[i],a[j]));
	}
	for(int i=2;i<=2*k;i++) for(int x:R[i]) B.insert(x);
	for(int i=2;i<=2*k;i++){
		for(int x:R[i]) B.remove(x);
		int N1=A.Get(i-k,1),N2=A.t[A.root].siz-N1;
		int N3=B.Get(i-1,0),N4=B.t[B.root].siz-N3;
		ans=min(ans,N1+N3+2*(N2+N4));
		for(int x:L[i]) A.insert(x); 
	}
	for(int i=2;i<=2*k;i++) for(int x:L[i]) A.remove(x);
	Write(ans);
}
int main(){
	int t=read();
	while(t--) solve();
	return 0;
}
```

---

