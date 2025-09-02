# [ABC231F] Jealous Two

## 题目描述

&emsp;滑头君要给他的两个好基友 A、B 每人送一个礼物。\
&emsp;滑头君有 **$ N $ 种**礼物，对于每种礼物，两个好基友都有不同的喜爱值。\
&emsp;两个好基友非常嫉妒。对于任意一个人来说，如果对方收到的礼物对自己的喜爱值比自己的礼物对自己的喜爱值更高，换句话说就是如果有人更喜欢对方的礼物的话，两个人就会打架。\
&emsp;滑头君不想失去他的朋友，于是请你求出共有几种可能的送礼方案。  
**请注意，可以给两个人送同样的礼物。**

## 样例 #1

### 输入

```
3
50 100 150
1 3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3
123456789 123456 123
987 987654 987654321```

### 输出

```
6```

## 样例 #3

### 输入

```
10
3 1 4 1 5 9 2 6 5 3
2 7 1 8 2 8 1 8 2 8```

### 输出

```
37```

# 题解

## 作者：Claire0918 (赞：1)

不妨设两人一个选了第 $i$ 个礼物，一个选了第 $j$ 个礼物。先考虑 $i \neq j$ 的情况。

由题得到 $a_i \geq a_j, b_i \leq b_j$，交换得 $a_i \leq a_j, b_i \geq b_j$。

设 $c_i = (a_i, b_i)$，将 $\{c_i\}$ 按照 $a_i$ 为第一关键字升序排序，$b_i$ 为第一关键字降序排序之后求满足 $i < j, b_i \geq b_j$ 的 $(i, j)$ 数量即可。

注意到当存在 $i \neq j$ 使得 $c_i = c_j$ 时，两人可以分别选两个，有两种情况，但在上文中只计算了一种（因为我们钦定 $i < j$），所以如果有 $k$ 个 $c_i$ 相等，结果要加上 ${k \choose 2} = \frac{k(k - 1)}{2}$。

再考虑两人选相同礼物的情况，显然有 $n$ 种。

在实现时，我们可以先算出任选 $1 < i \leq j < n$ 的 $(i, j)$ 共有 $\frac{n(n + 1)}{2}$ 种，再减去 $\{c_i\}$ 中的 $i < j, a_i < a_j$ 的 $(i, j)$ 数量，再对于任意 $k$ 个相等的 $c_i$ 加上 $\frac{k(k - 1)}{2}$ 即可。

时间复杂度 $\mathcal{O}(n \log n)$，瓶颈在于快速求出顺序对。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10;

long long n, res = 0;
pair<int, int> buf[maxn];
int a[maxn], temp[maxn];

inline void mergesort(int l, int r){
    if (l >= r){
        return;
    }
    const int mid = l + r >> 1;
    mergesort(l, mid);
    mergesort(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r){
        if (a[i] <= a[j]){
            temp[k++] = a[i++];
            res += j - mid - 1;
        }else{
            temp[k++] = a[j++];
        }
    }
    while (i <= mid){
        temp[k++] = a[i++];
        res += r - mid;
    }
    while (j <= r){
        temp[k++] = a[j++];
    }
    for (int i = l; i <= r; i++){
        a[i] = temp[i];
    }
}

int main(){
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &buf[i].first);
    }
    for (int i = 1; i <= n; i++){
        scanf("%d", &buf[i].second);
    }
    sort(buf + 1, buf + n + 1, [](pair<int, int> x, pair<int, int> y){return x.first > y.first || x.first == y.first && x.second < y.second;});
    for (int i = 1; i <= n; i++){
        a[i] = buf[i].second;
    }
    mergesort(1, n);
    pair<int, int> prev = make_pair(-1, -1);
    long long connect = 0;
    for (int i = 1; i <= n; i++){
        if (buf[i] == prev){
            connect++;
        }else{
            prev = buf[i];
            res -= connect * (connect - 1) >> 1;
            connect = 1;
        }
    }
    res -= connect * (connect - 1) >> 1;
    printf("%lld", (n * (n + 1) >> 1) - res);

return 0;
}
```

---

## 作者：yzyjh (赞：1)

把问题抽象一下就是 "有多少对 $(i, j)$ 是 $A_i\geq A_j$和$B_i\leq B_j$ ？"

我们可以假设 $1\leq A_i,B_i\leq N$ 。为简单起见，我们首先假设没有        $(i,j)$ 满足 $(A_i,B_i)=(A_j,B_j)$。

对于这一部分，我们可以考虑用线段树或者树状数组求逆序对来解决。

即使存在  $(i,j)$  这样的  $(A_i,B_i)=(A_j,B_j)$，也可以通过对它们进行适当分组而得到类似的解法。

因此，该问题总共只用了 $O(N\log N)$ 时间就解决了。


---

## 作者：allenchoi (赞：1)

### 题意：  
有长度为 $n$ 的两个数列 $a,b$ 求不满足 $a_i < a_j$ 和 $b_i > b_j$ 的 $(i,j)$ 数量，其中 $1 \le i,j \le n$ 。  
### 科技
数学（容斥原理），树状数组 / 线段树   
### 思路：  
我们可以先统计处满足条件（ $a_i < a_j$ 或 $b_i > b_j$ ）的数量，再用 $n ^ 2$ 减去。  
根据容斥原理，满足条件的数量为满足 $a_i < a_j$ 的数量加上满足 $b_i > b_j$ 的数量减去 $a_i < a_j$ 且 $b_i > b_j$ 的数量。  
前面两项排序一下就可以求出来，但最后一项怎么求呢？  
很简单，把 $a_i,b_i$ 打包成一个结构体按 $a$ 升序排序，每次处理 $a$ 相等的一段区间(设为 $[i,p]$ )，答案加上 $\sum_{j = i}^{p}\sum_{k=1}^{i-1}[b_k>b_j]$ 。   
容易想到把 $b$ 离散化后用树状数组或线段树统计。  
### 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n,m,p1[N],p2[N],s[N];
long long c1,c2,c3;
struct gift{int a,b;} g[N];
bool cmp(gift x,gift y){return x.a < y.a;}
int lowbit(int x){return x & (-x);}
void update(int x,int v){for(int i = x;i <= m;i += lowbit(i)) s[i] += v;}
int query(int x)
{
	int ret = 0;
	for(int i = x;i;i -= lowbit(i)) ret += s[i];
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&g[i].a);
		p1[i] = g[i].a;
	}
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&g[i].b);
		p2[i] = g[i].b;
	}
	sort(p1 + 1,p1 + n + 1);
	for(int i = 1;i <= n;i++) c1 += lower_bound(p1 + 1,p1 + i + 1,p1[i]) - p1 - 1;
	sort(p2 + 1,p2 + n + 1);
	for(int i = 1;i <= n;i++) c2 += lower_bound(p2 + 1,p2 + i + 1,p2[i]) - p2 - 1;
	p2[0] = -114514;
	for(int i = 1;i <= n;i++) if(p2[i] != p2[i - 1]) p2[++m] = p2[i];
	sort(g + 1,g + n + 1,cmp);
	for(int i = 1,j;i <= n;i++)
	{
		for(j = i;j <= n && g[j].a == g[i].a;j++)
		{
			g[j].b = lower_bound(p2 + 1,p2 + m + 1,g[j].b) - p2;
			c3 += query(m) - query(g[j].b);
		}
		for(j = i;j <= n && g[j].a == g[i].a;j++) update(g[j].b,1);
		i = j - 1;
	}
	printf("%lld\n",1LL * n * n - c1 - c2 + c3);
	return 0;
}
```

---

## 作者：Fire_Shadow_Dream (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc231_f)

# 题意

（已经过转化，因为这样会更好理解）

给定两个长度为 $n$ 序列 $a,b$，求满足 $a_i\ge a_j$ 且 $b_i\le b_j$ 的数对 $(i,j)$ 个数。

  # 思路

稍微转变一下要求：$a_i\ge a_j,b_i\le b_j$。

如果将 $b_i,b_j$ 转换成下标来看，这个问题就可以转换成求逆序对对数的问题。

将序列 $a$ 与 $b$ 分别对应联结起来，并按照 $b$ 升序排序，那么对于序列 $b$ 此时就满足对于 $i,j\in [1,n]$，有 $b_i\le b_j$，满足第二个条件。

此时会出现一种特殊情况：若有数对 $(i,j)$ 满足 $a_i=a_j,b_i=b_j$，那么此时方案 $(i,j)$ 或 $(j,i)$ 都是可行的，但在求逆序对中只会算一种方案，因此我们将 $a_i$ 与 $b_i$ 都相同的合并在一组中，那么就可以保证求逆序对时没有完全重复的数据了。计算逆序对个数时只需多乘上组中数据个数即可。

在排序时也要注意一个细节，就是当 $b$ 相等时要让前面的 $a$ 尽量大。因为在原序列中只需要满足 $a_i\ge a_j,b_i\le b_j$ 即可，与 $i,j$ 的大小无关，因此原序列中当 $b$ 相等时，只需要用较大的 $a$ 搭配较小的 $a$ 就可以构造出一种方案。在排序序列中，为了使大 $a$ 搭配小 $a$ 能够组成一种方案，我们要将大 $a$ 放在前面，让小 $a$ 放在后面，由此组成一组逆序对，贡献一种方案。

对于同一组，由于无论 $i,j$ 是多少，不难得都能够满足要求，记组内元素个数为 $S$，因此同一组中贡献的方案数为 $S^2$。

将同组中的贡献与不同组的逆序对贡献求和，即为答案。

求逆序对可用归并排序或离散+树状数组，这里用的是归并排序，在此不多介绍，结合代码注释使用效果更佳。

# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define hxq using
#define is namespace
#define yyds std;
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define int long long 
hxq is yyds
const int N=2e5+10;
int n,nw;
ll ans;
struct Data{
	int a,b;
}d[N];
bool cmp(Data a,Data b){
	return a.b<b.b||a.b==b.b&&a.a>b.a;
}
struct h{
	int p,s;
}sum[N],L[N],R[N];
int jp[N];
void merge(int l,int mid,int r){
	jp[l-1]=0;
	for(int i=l;i<=mid;i++) L[i]=sum[i],jp[i]=jp[i-1]+sum[i].s;//前缀和数组辅助 
	for(int i=mid+1;i<=r;i++) R[i]=sum[i];
	int i=l,j=mid+1,tot=0;
	L[mid+1].p=R[r+1].p=INT_MAX;
	while(tot<r-l+1){
		tot++;
		if(L[i].p>=R[j].p) sum[l+tot-1]=R[j],ans+=(jp[mid]-jp[i-1])*R[j].s,j++;//计算逆序对 
		else sum[l+tot-1]=L[i],i++;
	}
}
void solve(int l,int r){
	if(l==r) return ;
	int mid=l+r>>1;
	ll res=0;
	solve(l,mid),solve(mid+1,r);
	merge(l,mid,r);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>d[i].a;
	for(int i=1;i<=n;i++) cin>>d[i].b;
	sort(d+1,d+n+1,cmp); //按b升序排序，注意当b相等时要使a大的尽量在前面这样才能使逆序对个数与原序列的方案数一样 
	d[0].a=-1;
	int t=1;
	for(int i=2;i<=n+1;i++){//合并 
		if(d[i].a!=d[i-1].a||d[i].b!=d[i-1].b) sum[++nw].s=t,sum[nw].p=d[i-1].a,t=1;
		else t++;	
	}
	solve(1,nw);//归并求逆序对 
	for(int i=1;i<=nw;i++){//求同族贡献 
		ans+=sum[i].s*sum[i].s;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

一个比较清新的做法。

题意可以转化为求 $(i, j)$ 满足 $a_i \ge a_j, b_i \le b_j$ 的对数。

考虑直接按 $a$ 从大到小排序，然后你依照类似树状数组求逆序对的思想，从前往后扫一遍，直接维护当前 $b_j$ 有多少个 $b_i$ 小于等于它。

但是你发现这个东西过不去，原来是有 $a$ 相同的情况。考虑排序时 $a$ 相同就按 $b$ 从大到小排序，然后最后对于出现次数为 $x$ 的 $a$，答案加上 $\binom x 2$，含义是随便选一对都是在之前没有计算过的，一开始的做法只能算 $i \le j$ 的方案，这样做就补上了 $j < i$ 的情况。

离散化后树状数组就可以简单维护这个东西。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;
int n; struct Node { int a, b; } x[N];
int a[N], b[N];
vector <int> col[N]; int cnt[N];

namespace FenwichTree {
	int c[N];
	int qwq(int x) { return x & (-x); }
	void update(int x) { for (; x <= n; x += qwq(x)) c[x]++; }
	int query(int x) { int a = 0; for (; x; x -= qwq(x)) a += c[x]; return a; }
} using namespace FenwichTree;

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> x[i].a, a[i] = x[i].a;
	for (int i = 1; i <= n; i++) cin >> x[i].b, b[i] = x[i].b;
	sort(x + 1, x + n + 1, [](Node x, Node y) { return x.a != y.a ? x.a > y.a : x.b > y.b; });
	sort(a + 1, a + n + 1); int lena = unique(a + 1, a + n + 1) - (a + 1);
	sort(b + 1, b + n + 1); int lenb = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; i++) x[i].a = lower_bound(a + 1, a + lena + 1, x[i].a) - a, x[i].b = lower_bound(b + 1, b + lenb + 1, x[i].b) - b;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		update(x[i].b);
		ans += query(x[i].b);
	} 
	for (int i = 1; i <= n; i++) col[x[i].a].push_back(x[i].b);
	for (int i = 1, siz; siz = col[i].size(), i <= n; i++) ans += siz * (siz - 1) / 2;
	cout << ans;
	return 0;
}
```

---

## 作者：Fimlty (赞：0)

# 题意
有长度为 $n$ 的数列 $A$ 和 $B$ ，求满足 $A_i \leq A_j$ 且 $B_i \geq B_j$ 的 $(i,j)$ 数量，其中 $1\leq i,j\leq n$ 。

实际上本题并**不需要**容斥原理，~~尽管代码好写一点~~而 @allenchoi 的题解中，计算第三项的方法完全适用于直接求解答案，只不过需要补充一些细节。

## 排序
因为合法的一对 $(i,j)$ 要保证 $B_i \geq B_j$ ，那我们不妨将 $B$ 升序排序，对于每一个 $i$ 寻找对应的 $j$ 。这样做可以天然满足**第二个条件**。
## 树状数组
我们把 $A$ **离散化**后就可使用树状数组。
```cpp
for (int i = 1; i <= N; i++)		
		if (P[i].A == P[i - 1].A)
			P[i].NA = M;
		else P[i].NA = ++M;
```

统计答案时，找出**已插入**树状数组的所有满足 $A_j \geq A_i$ 的 $A_j$ 记录答案。(但是不包含自己以及“同类”，为什么呢？)

```cpp
for (int i = 1; i <= N; i++) {
		if (P[i].NA != P[i - 1].NA || P[i].B != P[i - 1].B)ans += lst * lst, lst = 1;
		else lst++;
		ans += query(M) - query(P[i].NA - 1);
		if (P[i].NA != P[i + 1].NA || P[i].B != P[i + 1].B)
			for(int j = 1; j <= lst; j++)
				add(P[i].NA);//为什么要等同类都统计完再插入？想一想。
	}
	ans += lst * lst;
```
我们称两个相同的礼物为**同类**。

你会发现 $lst$ 这个变量很奇怪，其实他就是来解决 $A_i$ 与同类难以直接统计进答案的问题。那我们~~就不统计~~，先假装没有同类，但是用 $lst$ 记录自己和同类的总数，显然在一共有 $lst$ 个相同的 $(A_i,B_i)$ 的情况下，对答案有 $lst^2$ 的贡献。
## 代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int N, M = 1, t[200005]={0};//离散化记得M初值为1,否则RE
long long ans, lst;
void add(int x) {
	if (x == 0)return;
	for (; x <= M; x += x & -x)t[x]++;
}
int query(int x) {
	if (x < 0)return 0;
	int res = 0;
	for (; x; x -= x & -x)res += t[x];
	return res;
}
struct node {
	int A, B, NA;
}P[200005]={0};
bool cmp1(node x, node y) {
	return (x.A < y.A);
}
bool cmp2(node x, node y) {
	return (x.B == y.B ? x.A > y.A: x.B < y.B);
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++)cin >> P[i].A;
	for (int i = 1; i <= N; i++)cin >> P[i].B;
	sort(P + 1, P + N + 1, cmp1);
	for (int i = 1; i <= N; i++)		
		if (P[i].A == P[i - 1].A)
			P[i].NA = M;
		else P[i].NA = ++M;
	sort(P + 1, P + N + 1, cmp2);
	for (int i = 1; i <= N; i++) {
		if (P[i].NA != P[i - 1].NA || P[i].B != P[i - 1].B)ans += lst * lst, lst = 1;
		else lst++;
		ans += query(M) - query(P[i].NA - 1);
		if (P[i].NA != P[i + 1].NA || P[i].B != P[i + 1].B)
			for(int j = 1; j <= lst; j++)
				add(P[i].NA);
	}
	ans += lst * lst;
	cout << ans;
	return 0;
}
```



---

## 作者：FL_sleake (赞：0)

目前题解区只有两篇题解，而且我都看得云里雾里的，是我理解能力不足。不过自己做出来的之后好像大概看懂了那两篇题解。

### 题意简述

给定两个长度为 $n$ 的数组 $a_1,a_2,\cdots,a_n$，$b_1,b_2,\cdots,b_n$。求出对于所有的 $1 \leq i,j \leq n$，有多少组有序的 $(i,j)$ 满足 $a_i \leq a_j$ 且 $b_i \geq b_j$。$i$ 可以等于 $j$。

### 解题思路

我们先假设所有 $a_i$ 互不相同。有两个条件需要同时满足：$a_i \leq a_j$，$b_i \geq b_j$。考虑将 $a_i,b_i$ 打包成一个结构体 $c_i$，然后以 $a_i$ 为关键字排序。这样操作之后，我们从 $1$ 扫到 $n$，如果当前是第 $j$ 个，那么 $a_j$ 一定是前 $j$ 个中最大的。为了满足 $a_i \leq a_j$ 这个条件，我们只能从前 $j$ 个数中统计答案。

具体而言，我们要统计有多少个 $1 \leq i \leq j$，满足 $b_i \geq b_j$。做个转换，$b_i \geq b_j$ 的数量等于 $j$ 减去 $b_i < b_j$ 的数量。所以其实我们只需要维护前 $j$ 个数中有多少个数比 $b_j$ 小，树状数组板子就可以解决。注意 $0 \leq b_i \leq 10^9$，所以要对 $b$ 数组进行一个离散化。

然后再来考虑 $a_i$ 有重复的情况。如果将 $a,b$ 打包成一个结构体并排序之后，出现下面的情况：

```cpp
1 2 3 3 4 5//以a为关键字排序
5 3 4 4 2 1
```

按照上面所说的，$j=3$ 时答案只能在前面 $3$ 个数中产生。而实际上 $(3,4)$ 是一种应该被统计的答案。于是我们发现，答案的统计区间应该从 $1$ 到最靠右的且满足 $a_r=a_j$ 的 $r$。所以我们每次更新到 $r$，然后再统一查询答案即可。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) (x&(-x))
int n,ans=0,num[200010];
struct node{
	int a,b;
	bool operator<(const node &B)const{
		return a<B.a;
		//以 a 为关键字排序 
	}
}x[200010];
int lsh[200010],Max=0;
void update(int x){
	for(int i=x;i<=Max;i+=lowbit(i)) num[i]++;
}
int query(int x){
	int cnt=0;
	for(int i=x;i>=1;i-=lowbit(i)) cnt+=num[i];
	return cnt;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i].a;
	for(int i=1;i<=n;i++) cin>>x[i].b,lsh[i]=x[i].b; 
	sort(x+1,x+n+1);
	sort(lsh+1,lsh+n+1);
	for(int i=1;i<=n;i++) x[i].b=lower_bound(lsh+1,lsh+n+1,x[i].b)-lsh,Max=max(Max,x[i].b);
	//离散化处理 
	for(int i=1;i<=n;i++){
		int lst=i;
		while(x[i].a==x[lst].a) update(x[i].b),i++;
		//从i处理到当前能统计答案的最右边的点 
		i--;
		//抵消for循环中的i++ 
		for(int j=lst;j<=i;j++) ans+=(i-query(x[j].b-1));
		//全部更新完了再统计答案 
	}
	cout<<ans<<endl;
	return 0;
}
```

---

