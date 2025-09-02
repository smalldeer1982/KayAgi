# Bubble Sort Graph

## 题目描述

Iahub recently has learned Bubble Sort, an algorithm that is used to sort a permutation with $ n $ elements $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ in ascending order. He is bored of this so simple algorithm, so he invents his own graph. The graph (let's call it $ G $ ) initially has $ n $ vertices and 0 edges. During Bubble Sort execution, edges appear as described in the following algorithm (pseudocode).

`<br></br>procedure bubbleSortGraph()<br></br>    build a graph G with n vertices and 0 edges<br></br>    repeat<br></br>        swapped = false<br></br>        for i = 1 to n - 1 inclusive do:<br></br>            if a[i] > a[i + 1] then<br></br>                add an undirected edge in G between a[i] and a[i + 1]<br></br>                swap( a[i], a[i + 1] )<br></br>                swapped = true<br></br>            end if<br></br>        end for<br></br>    until not swapped <br></br>    /* repeat the algorithm as long as swapped value is true. */ <br></br>end procedure<br></br>`For a graph, an independent set is a set of vertices in a graph, no two of which are adjacent (so there are no edges between vertices of an independent set). A maximum independent set is an independent set which has maximum cardinality. Given the permutation, find the size of the maximum independent set of graph $ G $ , if we use such permutation as the premutation $ a $ in procedure bubbleSortGraph.

## 说明/提示

Consider the first example. Bubble sort swaps elements 3 and 1. We add edge (1, 3). Permutation is now \[1, 3, 2\]. Then bubble sort swaps elements 3 and 2. We add edge (2, 3). Permutation is now sorted. We have a graph with 3 vertices and 2 edges (1, 3) and (2, 3). Its maximal independent set is \[1, 2\].

## 样例 #1

### 输入

```
3
3 1 2
```

### 输出

```
2
```

# 题解

## 作者：_edge_ (赞：3)

首先说一句，题目翻译有误，实际上正确的翻译应该是对于这个序列的逆序对都相互连一条边。

我们都知道，目前人类所开发出来的算法，还暂时没有能够解决 $10^5$ 范围的最小独立集，同时这道题目，就是连边都很困难。

我们考虑去研究这道题目的本质，实际上可以这样考虑，考虑仅仅是前面的点连到后面的点，相当于是什么？

相当于这个点选了之后，后面被确定的点都不能被选中，再进一步利用这个逆序对的性质，就是说当前这个点被选中，那么后面小于等于它的点都不能选中。

实质上就是求最长上升子序列。

没人写树状数组的我就来补一发，直接在树状数组上进行单点修改，以及前缀最大值即可。

时间复杂度 $O(n \log n)$。

如有问题，还请指出。

```cpp
#include <iostream>
#include <cstdio>
#define lowbit(x) x&-x
using namespace std;
const int INF=2e5+5;
int n,a[INF],tree[INF],f[INF];
void add(int x,int y) {
	for (int i=x;i<=1e5;i+=lowbit(i))
		tree[i]=max(tree[i],y);
	return ;
}
int query(int x) {
	int sum=0;
	for (int i=x;i>=1;i-=lowbit(i))
		sum=max(sum,tree[i]);
	return sum;
}
signed main()
{
	scanf("%d",&n);int ans=0,sum=0;
	for (int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) {
		f[i]=1;int kk=query(a[i]-1);
		f[i]=max(f[i],kk+1);
		add(a[i],f[i]);
		ans=max(ans,f[i]);
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：wxzzzz (赞：3)

### 题意

求最长连续逆序对。（最长上升子序列）

### 思路

贪心。

贪心策略：对于一个上升子序列，其结尾元素越小，越利于在后面接其他的元素，使最长上升子序列可能变得更长，因此，贪心策略就是使每个上升子序列的结尾元素最小。

设 $f_i$ 表示长度为 $i$ 的最长上升子序列的末尾元素的最小值，对于每个 $a_i$，找到已有的 $f$ 中第一个大于等于 $a_i$ 的元素，显然 $f$ 满足单调性，因此可以二分。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, l, r, mid, ans, a[1000005], f[1000005];
int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        l = 0, r = ans;

        while (l < r) {
            mid = (l + r + 1) / 2;

            if (f[mid] < a[i])
                l = mid;
            else
                r = mid - 1;
        }

        ans = max(ans, r + 1);
        f[r + 1] = a[i];
    }

    cout << ans;
    return 0;
}
```

---

## 作者：AKPC (赞：2)

### 思路
对于本题，如果选中前面的点，就不能选后面小于等于的点。所以这不就是最长上升子序列（[LIS](/problem/AT_chokudai_S001_h)）吗！！！

当然这里 $n\leq 10^5$，不可以用 $\text O(n^2)$ 的动态规划，考虑 $\text O(n\log n)$ 复杂度，即贪心+二分查找。
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100001],f[100001],ans=1,l,r,mid;
signed main(){
	cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i];
	f[1]=a[1];
	for (int i=2;i<=n;++i){
		l=1,r=ans,mid;
		while (l<=r){
			mid=(l+r)>>1;
			a[i]<=f[mid]?r=mid-1:l=mid+1;
		}
		f[l]=a[i];
		if (l>ans) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Altwilio (赞：2)

$1.$ 题意

对于给定的序列，每个逆序对连接一条无向边，求得到的图的最大独立集。

$2.$ 思路

对于本题相当于，如果选中前面的点，就不能选后面小于等于的点，于是演变成了 $O(nlogn)$ 求最长上升子序列。

$3.$ 代码实现

其中 $logn$ 的复杂度来自二分。

长度相同的上升子序列只需要保存结尾最小的那个，而长度递增时，结尾数字的大小也是递增的。最长上升子序列就是找出比他大的第一个数。前面的数都比他小，所以他和这个数的长度相同。然后由于他比较然后小，更新找到的那个值。

```cpp
#include<map>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

template<class T> inline void read(T &x){
    x = 0; register char c = getchar(); register bool f = 0;
    while(!isdigit(c)) f ^= c == '-', c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if(f) x = -x;
}

template<class T> inline void print(T x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar('0' + x % 10);
}

int n, cnt, l, r, a[100010], x, mid;

int main(){
    read(n);
    a[0] = -1e9;
    for(int i = 0; i < n; i ++){
        read(x);
        if(x > a[cnt]) a[++ cnt] = x;
        else{
            l = 1, r = cnt;
            while(l <= r){
                mid = l + r >> 1;
                if(x > a[mid]) l = mid + 1;
                else r = mid - 1;
            }
            a[l] = x;
        }
    }
    print(cnt);
    return 0;
}
```


---

## 作者：coding_goat (赞：1)

$1500$ 的 dp。正难则反，将逆序对连起来求最大独立集，就相当于找没有逆序对的数列的最长长度，所以就是 LIS。考虑到 $1 \le n \le 10^5 $，所以用 $n \log n$ 的方法。设 $f_i$ 表示当 LIS 长度为 $i$ 的时候，序列末尾的最小值为多少。显而易见的，$f$ 单调递增，所以可以二分查找最小值，对于每个 $a_i$ 查找 $f$ 中有无一个最小元素使得 $f_i\ge a_i$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mem(a,b) memset((a),(b),sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
using namespace std;
inline int read()
{
	int xx=0;int f=1;
    char c = getchar();
    while(c<'0'||c>'9')
	{
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9')
	{
        xx = (xx<<1)+(xx<<3)+(c^48);
        c = getchar();
    }
    return xx*f;
}
#define maxn 100050

int n,a[maxn];
int f[maxn],ans=1;

signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	mem(f,0x7f);
	f[0]=0,f[1]=a[1];
	for(int i=2;i<=n;i++)
	{
		int l=0,r=ans;
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			if(f[mid]<a[i]) l=mid;
			else r=mid-1;
		}
		//cout<<r<<' '<<f[r]<<' '<<a[i]<<'\n';
		ans=max(ans,r+1);
		f[r+1]=a[i];
	}
	cout<<ans;
	return 0;
}



```

---

## 作者：DennyQi (赞：1)

题目可以理解为给出一个长度为$n$的序列，每个逆序对连一条无向边，求得到的无向图（可能不连通）的最大独立集。

做法：根据定义，对于没有连边的两个点，他们一定不是逆序的，因此是递增的（题目保证没有相同的值）。最大独立集转化为了最长上升子序列。

题目卡$O(n^2)$，所以要做一下$O(n \log n)$的LIS。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100010;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,x,l,d[N],L,R,mid,p;
int main(){
	freopen("file.in","r",stdin);
	n = read();
	for(int i = 1; i <= n; ++i){
		x = read();
		L = 1, R = l;
		p = 0;
		while(L <= R){
			mid = (L+R) >> 1;
			if(d[mid] > x){
				R = mid-1;
			}else{
				L = mid+1;
				p = mid;
			}
		}
		if(p+1 > l) ++l, d[l] = x;
		else d[p+1] = min(d[p+1],x);
	}
	printf("%d\n",l);
	return 0;
}
```

---

## 作者：_121017_ (赞：1)

这道题第一眼看上去，全是英文表示看不懂，一看样例解释：一个集合 $[3,1,2]$ 中选取了 $[1,2]$ 两个元素，我们不难猜到这是道 $LIS$ 的模板题，不懂 $LIS$ 的 [出门右转](https://blog.csdn.net/ltrbless/article/details/81318935)

看一眼数据范围： $1<n<10^5$，$n^2$ 算法肯定是过不了的，我们得追求 $nlog_2n$ 的算法那么怎么办呢？我们维护一个 $f$ 数组，$cnt$ 表示数组里的元素个数（从 $1$ 开始）。当读取到的数比 $f$ 数组最后一个大时，直接把这个元素放到后面，否则找到第一个比它大的元素替换掉。

这么看来是不是有点像单调队列？但裸的单调队列复杂度依然是 $n^2$，想要通过这道题，我们必须借助 $STL$ 库里的 $lower\_bound$ 函数。 

使用方法： $lower\_bound(a+1,a+1+n,x)$ 表示在 $a[1]$ 到 $a[n]$ 这段区间内找到第一个比 $x$ 大的数的地址，我们只要在后面减去 $a$ 就可以了。


# code：
```cpp
#include<bits/stdc++.h>
#define ri register int
#define N 100005
using namespace std;
int n,a[N],f[N],cnt;
int main(){
	cin>>n;
	for(ri i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>f[cnt]) f[++cnt]=a[i];
		else{
			int p=upper_bound(f+1,f+1+cnt,a[i])-f;
			f[p]=a[i];
		}
	}
	cout<<cnt;
	return 0;
}
```


---

## 作者：ZLCT (赞：0)

# CF340D Bubble Sort Graph
## 题目翻译
给定一个排列，现在根据如下规则建图：每队逆序对之间连边。求此图最大独立集。
## solution
这个题就是顶着最大独立集的帽子招摇撞骗。\
我们考虑最终选择的点集需要满足什么条件。\
那根据最大独立集的定义，所有点之间都不存在连边，那换到题目里就转化成了没有逆序对。\
诶？是不是答案就出来了。\
我们问题现在是求原排列的一个最长子序列使得没有逆序对，这不就是最长上生子序列 LIS 吗？\
为了以防万一我们再来检查一遍，首先必要性刚才已经说了，那只要是最长上升子序列就没有逆序对吗？\
这个也是显而易见的，由于最长上升子序列满足 $a_i<a_{i+1}$，根据不等式的传递性，我们可以推出 $a_1<a_2<a_3<…<a_{m-1}<a_m$，这其中肯定不存在逆序对。\
下面我们就要考虑最后一件事了，如何求 LIS，正常的 dp 方法肯定是复杂度不够的，那我们考虑另外两种方法：
- 暴力数据结构法。我们 dp 时相当于没次都要在前 $i-1$ 个中找到一个满足 $a_j<a_i$ 的 $f_j$ 的最大值。但是我们由于是顺序加入的，所以时间维就可以忽略了，就变成了在 $[1,a_i-1]$ 中找到一个 $f_j$ 的最大值，这就可以线段树或树状数组去维护了。
- 二分法。这是一个基于贪心思想的方法，我们回顾 dp 法，我们考虑如果选择 $i$，那么因为无论前面有多少的数，它对后面的影响都是 $a_i$，所以我们肯定是要选择最长的可放位置。那我们换一种角度考虑，对于一个长度为 $l$ 的上升子序列，它为了使后面的数满足条件的机会更大，一定希望它的结尾最小。所以我们记录 $f_i$ 表示长度为 $i$ 的上升子序列结尾最小是几，那么根据 dp 法的思路，我们当前的 $a_i$ 一定是会放在能放的最长位置，所以我们可以二分出第一个 $>a_i$ 的位置，并把它换成 $a_i$，如果比最长的位置都要大就单独开一个位置。\
但是这为什么一定满足单调呢？因为每次我们找到的位置 $k$ 都满足 $\forall w<k,f_w<f_k$ 并且 $f_k>a_i,\forall w>k,f_w>f_k$，又是根据不等式的传递性，整个序列依旧是一个单调的。
## 数据结构法 by `flydutchman`
```cpp
#include<bits/stdc++.h>

using namespace std;
#define For(i,l,r) for (int i = l; i <= r; ++i)

int n, A[222222], tree[222222], f[222222];
void ins(int x, int val) {
	for (int z = x; z <= 200000; z += z & -z) tree[z] = max(tree[z], val);
}

int ask(int r) {
	int res = 0;
	for (int z = r; z; z -= z & -z) res = max(res, tree[z]);
	return res;
}

int main() {
	cin >> n;
	For(i,1,n) scanf("%d", &A[i]);
	int ans = 0;
	For(i,1,n) {
		f[i] = ask(A[i] - 1) + 1;
		ins(A[i], f[i]);
		ans = max(ans, f[i]);
	}
	cout << ans << endl;
	return 0;
}
```
## 二分法 by me
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+666;
int n,a[N],f[N],ans;
signed main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;++i){
        int st=lower_bound(f+1,f+1+n,a[i])-f;
        f[st]=a[i];
        ans=max(ans,st);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑最大独立集中的所有 $i,j(i<j)$，那么都有 $a_i < a_j$，否则就有逆序对就不独立了。

那么求最大独立集其实就是求最长上升子序列，然后因为 $n \le 10^5$，所以用贪心或树状数组做即可（我使用的是树状数组）。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;
ll c[100010], a[100010];

void modify(int x, ll d) {
	for (; x <= n; x += (x & (-x))) c[x] = max(c[x], d);
}

ll query(int x) {
	ll ans = 0;
	for (; x; x -= (x & (-x))) ans = max(c[x], ans);
	return ans;
}

int main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);

	for (int i = 1; i <= n; ++i) {
		modify(a[i], query(a[i]) + 1);
	}

	printf("%lld\n", query(n));

	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

简单题。很显然题目就是求 $a$ 数组的 `LIS`（最长上升子序列）的长度。因为 $n\le 10^5$ 且 $a_i\le 10^5$，所以考虑用值域线段树优化 `LIS` 的转移。时间复杂度为 $O(n\log n)$。

---

## 作者：Natsume_Rin (赞：0)

其实这一题就是求最长上升序列的问题。

来分析一下：

**对于每一个数构成独立集，大小肯定是要大于等于它后面大于它的数的**。

所以，就只要求这个序列中的最长上升序列就可以了。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
int n, cnt, l, r, a[100001], x, mid;
int main() {
	scanf("%d",&n);
	a[0]=-2147483647;
	for(RI i=0; i<n; i++) {
		scanf("%d",&x);
		if(x>a[cnt]) a[++cnt]=x;
		else {
			l=1, r=cnt;
			while(l<=r) {
				mid=(l+r)>>1;
				if(x>a[mid]) l=mid+1;
				else r=mid-1;
			}
			a[l]=x;
		}
	}
	cout<<cnt<<endl;
	return 0;
}
```

---

