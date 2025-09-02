# [ABC261F] Sorting Color Balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc261/tasks/abc261_f

$ N $ 個の球が左右一列に並んでいます。 左から $ i $ 番目の球の色は色 $ C_i $ であり、整数 $ X_i $ が書かれています。

高橋君の目標は球を左から右に見た時に書かれている数が非減少になるように球を並べ替えることです。 言い換えれば、高橋君の目標は、任意の $ 1\leq\ i\leq\ N-1 $ について、左から $ i+1 $ 番目の球に書かれている数 が左から $ i $ 番目に書かれている数以上であるようにすることです。

高橋君は目標を達成するために、次の操作を好きなだけ（ $ 0 $ 回でも良い ）繰り返すことができます。

> $ 1\leq\ i\leq\ N-1 $ をみたす整数 $ i $ を選ぶ。  
>  左から $ i $ 番目の球と $ i+1 $ 番目の球の色が異なっているならば、コストを $ 1 $ 支払う。 （色が等しいならばコストを支払う必要は無い。）  
>  左から $ i $ 番目の球と $ i+1 $ 番目の球を入れ替える。

高橋君が目標を達成するために支払う必要のあるコストの最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\times\ 10^5 $
- $ 1\leq\ C_i\leq\ N $
- $ 1\leq\ X_i\leq\ N $
- 入力は全て整数

### Sample Explanation 1

球の情報を $ (色,\ 整数) $ で表すとします。 最初の状態は $ (1,3) $, $ (5,2) $, $ (2,1) $, $ (2,2) $, $ (1,1) $ です。 例えば、高橋君は次のように操作を行うことができます。 - 左から $ 1 $ 番目の球 (色 $ 1 $) と $ 2 $ 番目の球 (色 $ 5 $) を入れ替える。 球は左から $ (5,2) $, $ (1,3) $, $ (2,1) $, $ (2,2) $, $ (1,1) $ となる。 - 左から $ 2 $ 番目の球 (色 $ 1 $) と $ 3 $ 番目の球 (色 $ 2 $) を入れ替える。 球は左から $ (5,2) $, $ (2,1) $, $ (1,3) $, $ (2,2) $, $ (1,1) $ となる。 - 左から $ 3 $ 番目の球 (色 $ 1 $) と $ 4 $ 番目の球 (色 $ 2 $) を入れ替える。 球は左から $ (5,2) $, $ (2,1) $, $ (2,2) $, $ (1,3) $, $ (1,1) $ となる。 - 左から $ 4 $ 番目の球 (色 $ 1 $) と $ 5 $ 番目の球 (色 $ 1 $) を入れ替える。 球は左から $ (5,2) $, $ (2,1) $, $ (2,2) $, $ (1,1) $, $ (1,3) $ となる。 - 左から $ 3 $ 番目の球 (色 $ 2 $) と $ 4 $ 番目の球 (色 $ 1 $) を入れ替える。 球は左から $ (5,2) $, $ (2,1) $, $ (1,1) $, $ (2,2) $, $ (1,3) $ となる。 - 左から $ 1 $ 番目の球 (色 $ 5 $) と $ 2 $ 番目の球 (色 $ 2 $) を入れ替える。 球は左から $ (2,1) $, $ (5,2) $, $ (1,1) $, $ (2,2) $, $ (1,3) $ となる。 - 左から $ 2 $ 番目の球 (色 $ 5 $) と $ 3 $ 番目の球 (色 $ 1 $) を入れ替える。 球は左から $ (2,1) $, $ (1,1) $, $ (5,2) $, $ (2,2) $, $ (1,3) $ となる。 最後の操作の後で球に書かれている数は左から順に $ 1,1,2,2,3 $ となっているため、高橋君は目的を達成しています。 $ 1,2,3,5,6,7 $ 回目の操作にコストが $ 1 $ ずつかかるため、 このとき合計でコストは $ 6 $ かかり、このときが最小となります。 $ 4 $ 回目の操作では、入れ替えた球の色がともに色 $ 1 $ であるためコストがかからないことに注意してください。

### Sample Explanation 2

すべての球の色は同じであるため、球の入れ替えにコストがかかることはありません。

### Sample Explanation 3

高橋君は一度も操作を行わずとも、目的を達成できています。

## 样例 #1

### 输入

```
5
1 5 2 2 1
3 2 1 2 1```

### 输出

```
6```

## 样例 #2

### 输入

```
3
1 1 1
3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3
3 1 2
1 1 2```

### 输出

```
0```

# 题解

## 作者：CQ_Bab (赞：3)

# 前言
本题中大多数人都是用的逆序对，这里提供一种不需要逆序对的方法。
# 思路
我们可以发现，我们可以从 $a\sim Max$ 去移动没一个数，这里的 $Max$ 是指 $x$ 的最大值，然后我们可以通过排序得出对于 $x$ 为 $i$ 的应该出现在 $l\sim r$ 这个区间，那么我们通过手玩可以发现我们对于每一个 $i$ 可以将第一个 $x$ 移到 $l$ 将第 $2$ 个移动到 $l+1$ 的位置，然后以此类推。

那么我们，就可以得出一个公式就是对于一个 $i$ 的贡献为 $wei_i+small_i-now-same_i$ 这里我们的 $wei_i$ 为第 $i$ 个数在原数组中出现的位置，$small_i$ 为原数组中在 $i$ 之后且 $x$ 小于 $i$ 的 $x$ 的数量，然后 $now$ 为当前的目标点，最后 $same_i$ 为在 $i$ 之前且 $c$ 等于 $i$ 的 $c$ 并且 $x$ 大于 $i$ 的 $x$ 的数量。

这样做为什么是对的呢？因为我们是从小到大来移动的 $x$ 所以我们对于所有 $x$ 小于 $i$ 的 $x$ 且在其后面的都会经过 $i$ 那么每经过一次就会把 $i$ 往后移动一个位置，然后我们将 $x$ 小于 $i.x$ 的移动完之后 $i$ 的位置就是 $wei_i+small_i$。

然后通过左右区间可以算出需要的步数（这里先忽略 $c$）然后我们对于能抵消的必须是在 $i$ 前面且 $c$ 要和其相等的还有 $x$ 要大于 $i.x$ 的，那么我们可以用两个树状数组，一个求解 $small_i$ 一个求解 $same_i$ 即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n;
const int N=3e5+10;
struct node {
	int c,x,id;
} s[N];
bool cmp(node a,node b) {
	if(a.x!=b.x) return a.x<b.x;
	return a.id>b.id;
}
vector<int>v[N];
vector<pair<int,int>>ve[N];
int cnt[N];
int small[N];
int shao[N];
int now[N],shor[N];
int res;
struct Node {
	int l,r;
} a[N];
int tr[N];
int lowbit(int x) {
	return x&(- x);
}
void add(int x,int k) {
	for(; x<=n; x+=lowbit(x)) tr[x]+=k;
}
int Ans(int x) {
	int res=false;
	for(; x; x-=lowbit(x)) {
		res+=tr[x];
	}
	return res;
}
set<int>se;
fire main() {
	in(n);
	rep(i,1,n) in(s[i].c),s[i].id=i;
	rep(i,1,n) in(s[i].x),cnt[s[i].x]++,se.insert(s[i].c);
	rep(i,1,n) v[s[i].x].push_back(i);
	rep(i,1,n) ve[s[i].c].push_back({s[i].x,i});
	rep1(i,n,1) {
		small[i]=Ans(s[i].x-1);
		add(s[i].x,1);
	}
	rep(i,1,n) tr[i]=0;
//	add(2,1);
//	add(2,-1);
//	rep(i,1,n) cout<<tr[i]<<" ";
	for(auto i:se) {
		for(pair<int,int> x:ve[i]) {
			shao[x.second]=Ans(x.first);
			add(x.first,1);
		}
//		cout<<endl;
		for(pair<int,int> x:ve[i]) add(x.first,-1);
//		cout<<endl;
	}
	rep(i,1,n) {
		shor[i]=now[s[i].c]-shao[i];
		now[s[i].c]++;
	}
	sort(s+1,s+1+n,cmp);
	rep(i,1,n) {
		if(!a[s[i].x].l) a[s[i].x].l=i;
		a[s[i].x].r=i;
	}
	rep(i,1,n) {
		if(!cnt[i]) continue;
		int now=a[i].l;
		for(auto x:v[i]) {
			res+=((x+small[x])-now)-shor[x];
			now++;
		}
	}
	print(res);
	return false;
}
```

---

## 作者：ZBH_123 (赞：2)

## 思路：归并排序求逆序对
在做本题之前，我们需要明白：本题去掉颜色限制后就是求逆序对。那么，我们要做的就是在统计逆序对的基础之上加上颜色限制。不加颜色限制时，那些交换代价为 $0$ 的逆序对也被算作为代价为 $1$。所以，本题的最终代价就等于逆序对数量减去颜色相同的逆序对数量。~~因为个人习惯问题~~，我们用 $a$ 来代替题目中的 $x$，用 $b$ 来代替题目中的 $c$。求逆序对可以用归并排序或者是树状数组，我这里选择使用归并排序。归并排序的示范代码如下：
```cpp
void msort(int l,int r){
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(a[i]<=a[j]){
			tmp[k++]=a[i++];
		}
		else{
			ans+=mid-i+1;
			tmp[k++]=a[j++];
		}
	}
	while(i<=mid){
		tmp[k++]=a[i++];
	}
	while(j<=r){
		tmp[k++]=a[j++];		
	}
	for(int i=l;i<=r;i++){
		a[i]=tmp[i];
	}
}
```
所以，我们需要在求逆序对的时候减去与 $a_j$ 颜色相同的元素数量。但是如果从 $i$ 到 $mid$ 枚举的话，时间复杂度会很高。考虑预处理 $l \sim mid$ 中与 $a_j$ 颜色相同的元素个数，记作 $cnt_{b_j}$。每次合并时，如果 $a_i \le a_j$，那么 $cnt_{b_i}$ 就应该减一，这时 $cnt_{b_j}$ 就指的是 $i+1 \sim mid$ 中与 $a_j$ 颜色相同的元素的个数了。如果 $a_i \gt a_j$，那么新产生的代价就是 $mid-i+1-cnt_{b_j}$。所以，我们能写出如下代码片段：
```cpp
void msort(int l,int r){
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r);
	for(int i=l;i<=r;i++){
		cnt[b[i]]=0;
	}
	for(int i=l;i<=mid;i++){
		cnt[b[i]]++;
	}
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(a[i]<=a[j]){
			cnt[b[i]]--;
			tmp[k++]=i++;
		}
		else{
			ans+=mid-i+1-cnt[b[j]];
			tmp[k++]=j++;
		}
	}
	while(i<=mid){
		tmp[k++]=i++;
	}
	while(j<=r){
		tmp[k++]=j++;		
	}
	for(int i=l;i<=r;i++){
		temp1[i]=b[i],temp2[i]=a[i];
	}
	for(int i=l;i<=r;i++){
		a[i]=temp2[tmp[i]],b[i]=temp1[tmp[i]];
	}
}
```
**AC code：**
```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define ll long long
const int maxn=3e5;
int n,a[maxn+5],b[maxn+5],cnt[maxn+5],tmp[maxn+5],temp1[maxn+5],temp2[maxn+5];
ll ans;
void msort(int l,int r){
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r);
	for(int i=l;i<=r;i++){
		cnt[b[i]]=0;
	}
	for(int i=l;i<=mid;i++){
		cnt[b[i]]++;
	}
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(a[i]<=a[j]){
			cnt[b[i]]--;
			tmp[k++]=i++;
		}
		else{
			ans+=mid-i+1-cnt[b[j]];
			tmp[k++]=j++;
		}
	}
	while(i<=mid){
		tmp[k++]=i++;
	}
	while(j<=r){
		tmp[k++]=j++;		
	}
	for(int i=l;i<=r;i++){
		temp1[i]=b[i],temp2[i]=a[i];
	}
	for(int i=l;i<=r;i++){
		a[i]=temp2[tmp[i]],b[i]=temp1[tmp[i]];
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	msort(1,n);
	cout<<ans;
	return 0;
}
```

---

## 作者：xs_siqi (赞：1)

看了一眼题解感觉前面的人很多东西都没有说清楚。至少我自己做这道题的时候是卡在了为什么最小值必定就是统计逆序对上，但是这件事根本没被提到。

首先对于没有颜色的情况，最小步数显然是逆序对个数（代价均为 $1$ 情况下）。因为要把序列造成递增，就必须满足逆序对为 $0$ 的条件。

每次交换两个数的前提下，能且仅能改变一对相邻的关系是否是逆序对。直接交换这两个数即可。可以证明没有更小的方案，因为比较大小关系是单向的，而一次只换两个元素的相对位置，两个元素相对于其他元素的位置相对不变。

根据贪心，我们每次把满足逆序对关系的相邻元素交换即可。

综上，我们得出了，当序列交换代价都为 $1$ 时答案就是逆序对。

接下来证明当序列交换代价为 $0$ 或 $1$ 时答案是逆序对数量减去代价为 $0$ 的逆序对数。

根据上面的推论，在这里最多的疑问便是，我能不能通过两次或多次 $0$ 代价的逆序对操作，去替换， $1$ 代价的逆序对操作？至少我在想这题时就是在想这个问题。

可以证明不是的。因为要做到上述操作，就必须通过多次操作改变两个数的相对位置，而不改变这两个元素相对整个串的相对位置。

这显然不能通过间接操作达成。为什么呢？以两个为例，如果要交换三个（或四个）串时，就必然会产生至少三个串的相对位置被改变，不符合上述要求。

综上我们证明了答案就是逆序对数减去颜色相同的逆序对数。

这里我采用了权值线段树来解决逆序对问题。用动态数组存颜色为第一下标，在相同颜色中的相对从左到右的排行为第二下标进行多次求逆序对操作。

```cpp
#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
#define pb push_back
#define L ls,l,mid
#define R rs,mid+1,r
#define int long long
using namespace std;
const int maxn=1e6+2e5+5;
int ans,n,tr[maxn],co[maxn],a[maxn];
vector<int> p[maxn];
void C(int rt,int l,int r,int p,int k){
	tr[rt]+=k;
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(p<=mid)C(L,p,k);
	else C(R,p,k);}
int Q(int rt,int l,int r,int p){
	if(l>=p)return tr[rt];
	int mid=(l+r)>>1;
	if(p<=mid)return Q(L,p)+Q(R,p);
	else return Q(R,p);}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&co[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		p[co[i]].pb(a[i]);
		ans+=Q(1,1,n,a[i]+1),C(1,1,n,a[i],1);}
	for(int i=1;i<=n;i++)
		C(1,1,n,a[i],-1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<p[i].size();j++)
			ans-=Q(1,1,n,p[i][j]+1),C(1,1,n,p[i][j],1);
		for(int j=0;j<p[i].size();j++)
			C(1,1,n,p[i][j],-1);}
	printf("%lld\n",ans);
	return 0;}
```


---

## 作者：Gaode_Sean (赞：1)

~~这题简单来说就是一个逆序对大模拟~~。

题目大意：给定 $n$ 个球，每个球有颜色 $c_i$ 和 权值 $x_i$，现在要按权值单调不减的顺序排好。选择一个球 $i\ (1 \leq i \leq n-1)$，交换第 $i$ 和第 $i+1$ 个球。当 $c_i=c_{i+1}$，这一步的代价为 $0$，否则这一步的代价为 $1$。

如果不考虑颜色的话，很显然这道题的答案就是 $x$ 序列中的逆序对个数，时间复杂度是 $O(n \log n)$。

增加了颜色限制后，我们不难发现，在原来的逆序对中，同一种颜色的逆序对个数代价总和为 $0$。因此可以先计算出 $x$ 序列中的逆序对个数，记为原来的答案。接着再枚举颜色的种类，计算同种颜色之间的逆序对个数，并从答案中减去。

整个算法的时间复杂度经过计算可以得出必定不超过 $O(n \log n)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
typedef long long ll;
ll ans;
struct node
{
	int c,v;
}a[N];
int n,b[N],mp[N],c[N];
vector<int> vec[N];
int ask(int x)
{
	int cnt=0;
	for(;x;x-=x&-x) cnt+=c[x];
	return cnt;
}
void add(int x){for(;x<=n;x+=x&-x) c[x]++;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].c);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].v);
	    vec[a[i].c].push_back(a[i].v);
	}
	for(int i=n;i>=1;i--){ans+=(ll)(ask(a[i].v-1));add(a[i].v);}
	for(int i=1;i<=n;i++)
	{
		if(vec[i].empty()) continue;
		for(int j=0;j<vec[i].size();j++) b[j+1]=vec[i][j];
		sort(b+1,b+1+vec[i].size());
		int m=unique(b+1,b+1+vec[i].size())-(b+1);
		for(int j=1;j<=m;j++) mp[b[j]]=j,c[j]=0;
		for(int j=vec[i].size()-1;j>=0;j--){ans-=(ll)(ask(mp[vec[i][j]]-1));add(mp[vec[i][j]]);}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：SkyLines (赞：0)

## 题目大意：

给定 $n$ 个球，第 $i$ 个球有 $C_i$ 和 $X_i$。可以选择一个正整数 $i$，其中 $1 \le i \le n-1$，若 $C_i=C_{i+1}$，交换 $i$ 和 $i+1$ 两个球不花费代价，否则花费 $1$ 的代价，求按这个序列的 $X$ 从小到大排序所花费的最小代价。

## 思路：

没有颜色的话，显然就是求逆序对个数，可以用时间复杂度为 $O(n\log{n})$ 的归并排序实现，代码如下。

例题：[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500005], s[500005];
long long sum = 0;
void merge(int l1, int r1, int l2, int r2)
{
	int index = l1, ls = l1;
	while(l1 <= r1 && l2 <= r2)
	{
		if(a[l1] <= a[l2]) s[index++] = a[l1++];
		else sum += r1 - l1 + 1, s[index++] = a[l2++];
	}
	while(l1 <= r1) s[index++] = a[l1++];
	while(l2 <= r2) s[index++] = a[l2++];
	while(ls < index) a[ls] = s[ls], ls++;
}
void merge_sort(int l, int r)
{
	if(l >= r) return ;
	int mid = (l + r) / 2;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	merge(l, mid, mid + 1, r);
}
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	merge_sort(0, n - 1);
	printf("%lld", sum);
	return 0;
}
```

然后考虑颜色，发现用原来总的逆序对数量减去每种颜色的逆序对数量就是答案了，求同颜色的逆序对可以用 $n$ 个 vector 统计每个颜色的 $C$。时间复杂度不会超过 $O(n\log{n})$，因为求原来的逆序对时间复杂度为 $O(n\log{n})$，求同颜色的逆序对时间复杂度不会超过 $O(n\log{n})$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, sum, c[300005], s[300005];
vector<int> mp[300005];
int a[300005];
int tmp;
void merge(int l1, int r1, int l2, int r2)
{
	int index = l1, ls = l1;
	while(l1 <= r1 && l2 <= r2)
	{
		if(a[l1] <= a[l2]) s[index++] = a[l1++];
		else sum += tmp * (r1 - l1 + 1), s[index++] = a[l2++];
	}
	while(l1 <= r1) s[index++] = a[l1++];
	while(l2 <= r2) s[index++] = a[l2++];
	while(ls < index) a[ls] = s[ls], ls++;
}
void merge_sort(int l, int r)
{
	if(l >= r) return ;
	int mid = (l + r) >> 1;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	merge(l, mid, mid + 1, r);
}
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &c[i]);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		mp[c[i]].push_back(a[i]);
	}
	tmp = 1;
	merge_sort(1, n);
	for(int i = 1; i <= n; i++)
	{
		if(!mp[i].size()) continue;
		tmp = -1;
		for(int j = 0; j < mp[i].size(); j++) a[j + 1] = mp[i][j];
		merge_sort(1, mp[i].size());
	}
	printf("%lld", sum);
	return 0;
}
```

---

## 作者：Glacial_Shine (赞：0)

# 题目大意

有 $n$ 个球，每个球的颜色是 $c_i$，球上的数字为 $x_i$，我们想要重排这些球使得这些球上的数字从左到右不下降。

我们可以重复以下操作无数次：

- 选择一个整数 $i(1 \leq i < n)$，交换第 $i$ 个和第 $i + 1$ 个球，如果这两个球颜色相等，则不花钱，如果这两个球颜色不等，则花一块钱。

求所需要的最小花费。

# 思路

我们知道在不考虑颜色的情况下所需要的最小交换次数就是逆序对的个数。

我们可以用归并求逆序对，在这时多记录以下前面每个颜色有多少个球，在算的时候就可以直接减去相同颜色的球的逆序对数量。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, sum[300005];
LL ans;
struct node {
    int color, number;
} a[300005], b[300005];
void guibin(int l, int r) {
    if (l == r)
        return ;
    int mid = (l + r) / 2;
    guibin(l, mid), guibin(mid + 1, r);
    int i = l, j = mid + 1;
    for (int ii = l; ii <= r; ii++)
        sum[a[ii].color] = 0, b[ii] = a[ii];
    for (int ii = l; ii <= mid; ii++)
        sum[a[ii].color]++;
    int k = i;
    while (i <= mid || j <= r) {
        if (i > mid)
            a[k] = b[j], j++;
        else if (j > r)
            a[k] = b[i], i++;
        else {
            if (b[i].number <= b[j].number)
                a[k] = b[i], sum[b[i].color]--, i++;
            else
                ans = ans + mid - i + 1 - sum[b[j].color], a[k] = b[j], j++;
        }
        k++;
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].color);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].number);
    guibin(1, n);
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

## 题意
给定 $N$ 个形如 $(C_i,X_i)$ 的**二元组**，要求交换若干次**相邻项**，使得二元组中的 $x_i$ **单调不降**。设**调换的**是第 $k$ 项及第 $k+1$ 项，$k\in N^*$ 且 $1\leqslant k<n$，则操作代价如下：

1. $C_k=C_{k+1}$：$0$ 消耗
2. $C_k\ne C_{k+1}$：$1$ 消耗

## 思路
首先，若我们**不考虑** $C_i$ 对**答案**的影响，即**默认**每次操作**均为 $1$ 消耗**，则根据经验，答案即为**在 $\{X_i\}$ 序列中的逆序对数**。

现在，由于只有**相同的** $C_i$ 才会对答案**产生影响**（使答案**更小**），所以我们将二元组**按 $C_i$ 的值分组**抽离出来，单独考虑。

此时，我们就可以**不用纠结**诸如“用**多次** $0$ 消耗的调换操作可否**等效于一次** $1$ 消耗”的问题，**只需要**考虑**同组**之间需要调换几次位置，即**可节约的步数**，也即对于 $\{X_i\}$ 的**逆序对**。用之前统计的答案**减去**即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define maxn 300000
using namespace std;
vector<int> col[maxn + 5];
typedef long long ll;
struct node {int ls, rs, size, pri, cnt, value;}tree[maxn + 5];
int n, rt, idx, c[maxn + 5], a[maxn + 5], cc[maxn + 5];
ll ans;
/*========权值树状数组========*/
int lowbit(int x) {return x & -x;}
void add(int x)
{
	while(x <= n) cc[x]++, x += lowbit(x);
}
int query(int x)
{
	int ret = 0;
	while(x) ret += cc[x], x -= lowbit(x);
	return ret;
}
/*======fhq-treap======*/
#define p(k) tree[k].pri
#define c(k) tree[k].cnt
#define s(k) tree[k].size
#define l(k) tree[k].ls
#define r(k) tree[k].rs
#define v(k) tree[k].value
void update(int k) {s(k) = s(l(k)) + s(r(k)) + c(k);}
void newnode(int &k, int value)
{
	k = ++idx;
	p(k) = rand();
	c(k) = s(k) = 1;
	v(k) = value;
	l(k) = r(k) = 0;
}
void split(int k, int value, int &l, int &r)
{
	if(!k)
	{
		l = r = 0;
		return;
	}
	if(v(k) <= value) l = k, split(r(k), value, r(k), r);
	else r = k, split(l(k), value, l, l(k));
	update(k);
}
int merge(int l, int r)
{
	if(!l || !r) return l + r;
	int ret;
	if(p(l) < p(r)) ret = l, r(l) = merge(r(l), r);
	else ret = r, l(r) = merge(l, l(r));
	update(ret);
	return ret;
}
void insert(int value)
{
	int l, mid, r;
	split(rt, value, l, r), split(l, value - 1, l, mid);
	if(!mid) newnode(mid, value);
	else s(mid)++, c(mid)++;
	rt = merge(merge(l, mid), r);
}
int find(int value)
{
	int l, r, ret;
	split(rt, value, l, r);
	ret = s(r);
	merge(l, r);
	return ret;
}
/*================*/
int main()
{
	srand(time(0));
	srand(rand());
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		add(a[i]);
		ans += i - query(a[i]);//求逆序对，初步统计答案
		col[c[i]].push_back(a[i]);//单独考虑各个 $C_i$
	}
	for(int i = 1; i <= n; i++)
	{
		rt = idx = 0;
		for(int j : col[i])
		{
			ans -= find(j);//减去能节约的步数（其实也是逆序对）
			insert(j);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```
[$\text{\color{green}{AC}}$](https://www.luogu.com.cn/record/128292894)

---
## 后记
**赛时**一开始一点思路也没有，后来才想到了以**两种逆序对**的方式来求解。

**但是**，第一次**逆序对**我都想到了用**树状数组**，可第二次**逆序对**，我却写了~~又臭又长~~的**平衡树**，~~简直疯了~~，多了这么多行代码……

---

## 作者：WaterSun (赞：0)

# 思路

典题。发现如果没有 $c$ 的限制，答案将是序列中逆序对的数量。

但是加上 $c$ 的限制后，不难发现在原本的逆序对中，如果有 $c$ 属性相同的两个逆序对，那么这个逆序对将不会对答案产生贡献。

于是考虑在原答案的基础上减去 $c$ 属性相同的逆序对。

用一个 `vector<int> v[N]` 存储每一种 $c$ 的小球。然后对每一个 `v[i]` 求一次逆序对数量，并从原答案中减去即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 3e5 + 10;
int n,ans;
vector<int> a;
vector<int> v[N];

struct point{
	int x;
	int c;
}arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

struct BIT{
	int tr[N];
	
	inline int lowbit(int x){
		return x & -x;
	}
	
	inline void modify(int x,int k){
		for (re int i = x;i <= n;i += lowbit(i)) tr[i] += k;
	}
	
	inline int query(int x){
		int res = 0;
		for (re int i = x;i;i -= lowbit(i)) res += tr[i];
		return res;
	}
}tree;

inline int solve(vector<int> a){
	int res = 0;
	int n = a.size();
	for (re int i = n - 1;~i;i--){
		res += tree.query(a[i] - 1);
		tree.modify(a[i],1);
	}
	for (re int i = n - 1;~i;i--) tree.modify(a[i],-1);
	return res;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) arr[i].c = read();
	for (re int i = 1;i <= n;i++){
		arr[i].x = read();
		a.push_back(arr[i].x);
		v[arr[i].c].push_back(arr[i].x);
	}
	ans = solve(a);
	for (re int i = 1;i <= n;i++){
		if (v[i].empty()) continue;
		ans -= solve(v[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

没脑子题。

对于一个位置 $i$，把它移动到它之前的 $x_i=x_j$ 中 $j$ 位置最大值 $+1$ 一定是最优的。同时，先将小的 $x_i$ 排好再排大的也是最优策略。

结合上面两个，将位置 $i$ 的值移动到某个最优位置的代价就是 $(i-1)-(\sum\limits_{j=1}^{x_i} cnt_j+\sum\limits_{j=1}^{i-1}(c_i=c_j)-\sum\limits_{j=1}^{i-1}(c_i=c_j \land x_j \le x_i))$，其中 $cnt_j=\sum\limits_{k=1}^{i-1}(x_k=j)$，即 $j$ 在 $i$ 之前出现的数量。后面的式子用树状数组和前缀和维护就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=3e5+10;
int n,c[N],x[N];
int b[N],idx;
int cnt[N],sum[N];
map<int,int> tr[N];
int tr2[N];

il void add(int k,int x,int y){while(x<=n) tr[k][x]+=y,x+=x&(-x);}
il void add2(int x,int y){while(x<=n) tr2[x]+=y,x+=x&(-x);}
il int query(int k,int x){int ans=0;while(x) ans+=tr[k][x],x-=x&(-x);return ans;}
il int query2(int x){int ans=0;while(x) ans+=tr2[x],x-=x&(-x);return ans;}

il void solve(){
	int ans=0;
	cin>>n;
	for(re int i=1;i<=n;++i) cin>>c[i];
	for(re int i=1;i<=n;++i) cin>>x[i];
	for(re int i=1;i<=n;++i)
		ans+=(i-1)-(query2(x[i])+sum[c[i]]-query(c[i],x[i])),
		++sum[c[i]],add(c[i],x[i],1),add2(x[i],1);
	cout<<ans;
}

signed main(){
	solve();
	return 0;
}
```


---

