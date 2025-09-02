# 「XSOI-R1」区间操作 (opt)

## 题目背景

小 A 喜欢区间操作问题。

## 题目描述

小 A 给你了一个长度为 $n$ 的序列 $a$，并给你了 $q$ 组询问。

对于每组询问，小 A 会给你两个正整数 $l,r$，你需要求出 $(a_l) \oplus (a_l+a_{l+1}) \oplus (a_l+a_{l+1}+a_{l+2}) \oplus \dots \oplus (a_l + a_{l+1} + a_{l+2} + \dots + a_r)$ 的值。

其中 $\oplus$ 表示异或运算。

## 说明/提示

**【样例解释 #1】**

$1 \oplus (1 + 1) \oplus (1 + 1 + 4) \oplus (1 + 1 + 4 + 5) \oplus (1 + 1 + 4 + 5 + 1) \oplus (1 + 1 + 4 + 5 + 1 + 4) = 18$。

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 0（13 pts）：保证 $n,q \le 10^2$。

- Subtask 1（28 pts）：保证 $n,q \le 10^4$。

- Subtask 2（19 pts）：保证 $a_i \le 10^4$。

- Subtask 3（7 pts）：保证 $n \le 10^2$。

- Subtask 4（17 pts）：保证 $a_i$ 均为 $2$ 的非负整数次幂。

- Subtask 5（16 pts）：无特殊限制。

对于所有测试数据，$1 \le l \le r \le n \le 10^4$，$1 \le q \le 10^6$，$0 \le a_i \le 10^{10}$。

upd（2024.7.3）：添加一组 hack 数据，减少一组数据。

## 样例 #1

### 输入

```
6 1
1 1 4 5 1 4
1 6```

### 输出

```
18```

## 样例 #2

### 输入

```
7 10
1 9 1 9 8 1 0
1 2
1 3
1 4
1 5
1 6
1 7
2 6
3 5
4 7
2 7```

### 输出

```
11
0
20
8
21
8
23
25
24
11```

# 题解

## 作者：wmrqwq (赞：17)

# 题目链接

[Link](https://www.luogu.com.cn/problem/P10401)

# 解题思路

## 算法一：

暴力模拟，时间复杂度 $O(n^2q)$，可以获得 $13$ 分。

事实上常数不大的话可以获得 $20$ 分。

## 算法二：

发现异或和可以用前缀和维护，时间复杂度 $O(nq)$，可以获得 $48$ 分。

## 算法三：

我们发现可以暴力预处理每个区间的值，时间复杂度 $O(n^2)$，空间复杂度 $O(n^2)$，显然会 MLE。

于是我们只需要将每次询问离线，然后再预处理时判断是否询问到了这个区间即可，如果询问到了就将答案储存下来。

这样做时间复杂度 $O(n^2)$，空间复杂度 $O(q)$，可以获得 $100$ 分。

# 参考代码

```
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
ll t;
ll n,q,l,r,K;
ll a[100010],sum[100010],ans[1000010];
struct node{
	ll l,r,id;
}Q[1000010];
bool cmp(node x,node y){
	if(x.l==y.l)
		return x.r<y.r;
	return x.l<y.l;
}
void solve()
{
	cin>>n>>q;
	forl(i,1,n)
		cin>>a[i],sum[i]=sum[i-1]+a[i];
	forl(i,1,q)
		cin>>Q[i].l>>Q[i].r,Q[i].id=i;
	sort(Q+1,Q+1+q,cmp);
	K=1;
	forl(i,1,n)
	{
		if(i!=Q[K].l)
			continue;
		ll Sum=0;
		forl(j,i,n)
		{
			Sum^=(sum[j]-sum[i-1]);
			while(Q[K].r==j && Q[K].l==i)
				ans[Q[K].id]=Sum,K++;
			if(Q[K].l!=i)
				break;
			if(K==q+1)	
			{
				forl(i,1,q)
					cout<<ans[i]<<endl;
				return ;
			}
		}
	}
	if(K!=q+1)
		return ;
	forl(i,1,q)
		cout<<ans[i]<<endl;
}
int main()
{
	IOS;
	t=1;
//	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：cqbzlhy (赞：12)

此题题面虽然看起来又是求和又是异或，比较唬人，但是仔细推敲起来，都是比较简单的纸老虎。

首先看到每个异或之间的算式，题目要求求得 $a_l, a_l+a_{l+1}, a_l+a_{l+1}+a_{l+2}, \dots, a_l+a_{l+1}+\dots+a_r$ 这样的一系列数字的和。那么为了快速的求到这一系列的求和答案，很容易想到第一个需要使用的方法：前缀和。通过前缀和，就可以在 $O(1)$ 的时间复杂度得到每一个区间和的答案。

在解决了区间求和的问题之后，下一个问题就变为了如何求解这些区间和的异或答案了。此时，我们发现，虽然题目的查询次数 $q$ 比较大，但是，总共的数字个数 $n$ 只有 $10000$ 个，因此，直接使用 $O(n^2)$ 的时间复杂度来暴力求解这个问题在理论上是可行的。这样，我们就可以先使用一个数组 $ans[i][j]$ 表示区间 $i$ 到 $j$ 直接的异或答案等于多少，采用打表的方式，找到任意的 $i$ 到 $j$ 之间满足题目要求的答案为多少，最后，在 $q$ 次查询当中，每一次询问直接 $O(1)$ 的给出答案，就可以完成这个问题。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,q;
long long a[10005],b[10005],ans[10005][10005];

int main(){
	cin >> n >> q;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		b[i]=b[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(i == j){
				ans[i][j]=a[i];
			}
			else{
				ans[i][j]=ans[i][j-1]^(b[j]-b[i-1]);
			}
		}
	}
	while(q--){
		long long l,r;
		cin >> l >> r;
		cout << ans[l][r] << endl;
	}
	return 0;
}
```

可是，按照当前思路完成题目以后，发现最终只得到了 $20$ 分，评测机返回结果 MLE。通过对代码的推敲，发现问题出在这个 $ans$ 的数组上，因为题目只有 $128MB$ 的空间，没办法容纳当前数组的大小。因为实际上，对我们答案有用的个数最多也只有 $10^6$ 这么多个，之前打表的过程中有很多空间都被我们用来存储了许多不需要的答案。在这里，就需要想个办法，只保留最终需要的答案，把不需要的答案舍弃。

这里我想到的办法就是，将整个计算过程转换为离线过程。然后，将所有需要查询的数据按照左端点从小到大排序，左端点一样时按照右端点从小到大排序，这样，就可以保证在 $O(n)$ 的情况下，将所有左端点相同的区间的答案全部进行暴力计算。最终同样在 $O(n^2)$ 的情况下得到所有需要求解的答案。因为这里只保留了需要查询的答案，就大大减少了所需要的空间大小，就不会出现 MLE 的情况了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	long long l,r;
	long long ans;
	long long id;
}qq[1000005];

long long n,q;
long long a[10005],b[10005],ans[10005][10005];

bool cmp1(node x,node y){
	if(x.l!=y.l)
		return x.l<y.l;
	else
		return x.r<y.r;
}

bool cmp2(node x,node y){
	return x.id<y.id;
}

int main(){
	cin >> n >> q;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		b[i]=b[i-1]+a[i];
	}
	for(int i=1;i<=q;i++){
		cin >> qq[i].l >> qq[i].r;
		qq[i].id=i;
	}
	sort(qq+1,qq+1+q,cmp1);
	long long haha=0,up=0;
	for(int i=1;i<=q;i++){
		if(i==1 || qq[i].l != qq[i-1].l){
			haha=a[qq[i].l];
			up=qq[i].l;
		}
		for(int j=up+1;j<=qq[i].r;j++){
			haha^=(b[j]-b[qq[i].l-1]);
		}
		qq[i].ans=haha;
		up=qq[i].r;
	}
	sort(qq+1,qq+1+q,cmp2);
	for(int i=1;i<=q;i++){
		cout << qq[i].ans << endl;
	}
	return 0;
}
```

此时，我们在这样处理完所有内容以后，就得到了一个空间符合要求，时间上也符合要求的代码，但是，这段代码交上去以后只得到了 $93$ 分，题目 TLE 了一个点。

后续通过排查，感觉时间上应该是没有问题的，可能是由于题目数据量太大，在没有关闭同步的情况下，使用输入输出流耗费的时间较多导致。最后，将上述代码中所有的 `cin` , `cout` 改为 `scanf` , `printf` 就可以了。

---

## 作者：xyx404 (赞：6)

## 思路：
使用前缀和，考虑到输入的询问范围可能会有 $l$ 相同，所以先用一个结构体把输入的 $l$ 和 $r$ 和输入的顺序存起来，然后进行排序哪个左端点更小，如果同时左端点相同，那么比较哪个右端点更小。

在 $l$ 相等时，我们可以直接按照上一个的答案往下搜这样重复的部分就不用重复计算历遍了。

为什么可以直接按照上一个的答案往下搜，因为我们在一开始排过序，只要这个结构体排完序后在前一个结构体后面，并且 $l$ 相同，那么后面的结构体的 $r$ 一定大于等于前面的结构体的 $r$，所以可以直接按照上一个的答案往下搜。

当 $l$ 不相等时，就正常地直接历遍，然后存答案就可以了。

## 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define LL long long
ull tamp;
const int MAXN=10001;
const int MAXQ=1000001;
ull n,q;
ull sum[MAXN];
ull a[100010];
struct node{
	ull l,r,id,ans;// 存左、右端点和输入顺序和答案 
}wt[MAXQ];
bool cmp_id(node x,node y){// 通过输入顺序还原后再输出 
	return x.id<y.id;
}
bool cmp_lr(node x,node y){// 排序哪个先开始如果同时开始那么比较哪个先结束 
	if(x.l==y.l)return x.r<y.r;// 如果左端点也就是 l 相同那么比较右端点 
	return x.l<y.l;// 如果 l 不相同比较那个的 l 更前面 
}
void find(){
	ull su;
	for(ull i=1;i<=q;i++){//q 个问题 
		if(wt[i].l!=wt[i-1].l){// 上一个结构体的 l 和这个结构体的 l 不相同 
			su=a[wt[i].l];//su 赋值为 a[wt[i].l]
			for(int j=wt[i].l+1;j<=wt[i].r;j++){// 从 wt[i].l+1 历遍到 wt[i].r 的答案 
				su^=(sum[j]-sum[wt[i].l-1]);
			}
			wt[i].ans=su;// 答案赋值 
		}
		else{
			if(wt[i].l==wt[i-1].l&&wt[i].r==wt[i-1].r){// 如果和上一个结构体的 l 和 r 相同说明答案也相同 
				wt[i].ans=su;// 直接赋值 
			}
			else{
				for(ull j=wt[i-1].r+1;j<=wt[i].r;j++){// 因为 l 相同且后面的结构体的 r 一定大于等于前面的结构体的 r 所以直接从前面的结构体的 r 的后面开始历遍 
					su^=(sum[j]-sum[wt[i].l-1]);
				}
				wt[i].ans=su;// 答案赋值 
			}
		}
		
	}
}
int main(){
	cin>>n>>q;
	for(ull i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];// 计算前缀和 
	}
	for(ull i=1;i<=q;i++)cin>>wt[i].l>>wt[i].r,wt[i].id=i;// 输入问题的 l 和 r 并标记输入顺序 
	sort(wt+1,wt+1+q,cmp_lr);// 按 l 和 r 排序
	find();
	sort(wt+1,wt+1+q,cmp_id);// 按输入顺序排序
	for(ull i=1;i<=q;i++)cout<<wt[i].ans<<"\n";// 输出答案 
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：5)

一道坑题，注意区间有重复。

我们先把所有 $(l,r)$ 数对从大到小排序，然后对于每个 $i$，都算出 $a_i,(a_i) \oplus (a_i+a_{i+1}),\ldots,(a_i) \oplus (a_i+a_{i+1}) \oplus (a_i+a_{i+1}+a_{i+2}+\ldots+a_n)$。当发现目前计算的区间正好在询问里出现，那么把答案加入输出的队列即可。

总的来说就是暴力计算，时间复杂度 $O(n^2+q)$，可以通过此题。

代码如下：
```cpp
ll pre[10006];
vector <tuple <ll, ll, ll>> question;
ll ans[1000006];
int main() {
	int n, q;
	read(n); read(q);
	int x = 0;
	rep(i, 1, n, 1) {
		ll k; read(k);
		pre[i] = pre[i - 1] + k;
	}
	int d = q;
	while (q--) {
		int l, r; 
		read(l), read(r);
		question.emplace_back(l, r, d - q);
	}
	sort(question.begin(), question.end(),
	[&](tuple <int, int, int> a, tuple <int, int, int> b) {
		int l1 = get<0>(a), l2 = get<0>(b);
		int r1 = get<1>(a), r2 = get<1>(b);
		return make_pair(l1, r1) > make_pair(l2, r2);
	});
	for (int i = 1; i <= n; i++) {
		if (question.empty()) break;
		ll a = 0;
		for (int j = i; j <= n; j++) {
			if (question.empty()) break;
			a ^= (pre[j] - pre[i - 1]);
			while (get<0>(question.back()) == i &&
			get<1>(question.back()) == j) {
				ans[get<2>(question.back())] = a;
				question.pop_back();
			}
		}
	}
	for (int i = 1; i <= d; i++) {
		write(ans[i]), putchar('\n');
	}
}
```

---

## 作者：Y_zhao111 (赞：3)

### Description
题目传送门：[P10401 「XSOI-R1」区间操作](https://www.luogu.com.cn/problem/P10401)。

让你求 $(a_l) \oplus (a_l+a_{l+1}) \oplus (a_l+a_{l+1}+a_{l+2}) \oplus \dots \oplus (a_l + a_{l+1} + a_{l+2} + \dots + a_r)$。

### Analysis
赛时第一眼瞪眼法，暴力 + 前缀和，不难编出代码。
 ```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll a[10005] , sum[10005];

int main()
{
	ll n , q;
	cin >> n >> q;
	
	for(ll i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	
	while(q --)
	{
		ll l , r;
		cin >> l >> r;
		
		ll ans = 0;
		for(ll i = l ; i <= r ; i ++)
		{
			ans ^= sum[i] - sum[l - 1];
		}
		
		cout << ans << endl;
	}
	return 0;
}
```
结果喜提 $\color{orange}48 \color{b}\operatorname{pts}$，于是乎——优化。

#### 正解
看了一下数据范围，$q$ 还蛮大的，到了 $10^6$。注意到 $n$ 较小，才到 $10^4$，所以考虑前缀和加优化。

前缀和：设 $sum_i=a_1+a_2+\dots+a_i$，化简一下就是 $\sum_{j=1}^{i}a_i$。

但注意到，$q$ 很大，这样的情况下空间复杂度为 $\mathcal{O}(n^2)$，在线操作 $^{[1]}$ 肯定会挂，显然会 $\colorbox{#052242}{\color{white}{\texttt{MLE}}}$，于是考虑离线操作 $^{[2]}$。

#### 离线操作与在线操作
+ 离线操作：读入所有的操作数据，然后一次性处理。
+ 在线操作：每读入一个操作数据，就进行一次操作。

怕新人不知道这个专有名词，介绍一下。

离线代码：
```cpp
for(int i = 1 ; i <= T ; i ++)
{
	ll l , r;
	cin >> l >> r;
	
	p[l].push_back(r);
	q[l].push_back(i);
}
```
输出也一样。

正解快的要死，连优化、快读快写都不用，最坏的情况下时间复杂度 $\mathcal{O}(n^2)$ 刚好卡过，非极限的情况下复杂度为 $\mathcal{O}(nq)$，随便跑跑都不是问题。

注意 $a_i$ 达到了 $10^{10}$，要开 long long。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll a[10005] , ans[10005] , sum[1000005]; //sum 为 ans

vector<ll> p[10005] , q[100005]; //做成定长

int main()
{
	ll n , T; //q有了，换成T
	cin >> n >> T;
	
	for(int i = 1 ; i <= n ; i ++)
	{
		ll x;
		cin >> x;
		
		a[i] = a[i - 1] + x; //前缀和操作
	}
	
	for(int i = 1 ; i <= T ; i ++)
	{
		ll l , r;
		cin >> l >> r;
		
		p[l].push_back(r);//离线操作
		q[l].push_back(i);//离线操作
	}
	
	for(int i = 1 ; i <= n ; i ++)
	{
		ans[i - 1] = 0;
		
		for(int j = i ; j <= n ; j ++)
		{
			ans[j] = ans[j-1] ^ (a[j] - a[i - 1]); //状态转移方程
		}
		
		for(int j = 0 ; j < p[i].size() ; j ++)
		{
			sum[q[i][j]] = ans[p[i][j]];
		}
	}
	
	//将答案存在数组中，统一输出，不搞在线操作
	for(int i = 1 ; i <= T ; i ++)
	{
		cout << sum[i] << endl;		
	}
	return 0;
}
```

---

## 作者：__Green_tick__ (赞：3)

### 题目链接
[P10401 「XSOI-R1」区间操作](https://www.luogu.com.cn/problem/P10401)

### 题目分析
这题我第一遍写了个 $48$ 分的暴力，见下。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q;
long long a[10010];
int main(){
	cin>>n>>q;
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(long long i=1;i<=q;i++){
		long long l,r,k=0,ans=0;
		scanf("%lld%lld",&l,&r);
		for(long long i=l;i<=r;i++){
			k=k+a[i];
			ans=ans^k;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
就是用 $ans$ 记答案，$k$ 当做一个前缀和，不知道前缀和的大佬看下面：

例如现有 `1 3 4 2 6` 这个五个数的数组，而我现在要在两重循环里得到加和，但一旦时间复杂度高于 $O(n^3)$ 就会超时，怎么办。

前缀和就是解决这个问题的，它将另一个数组 $s$ 中的 $s_i$ 定义为 $a_1+a_2+a_3+...+a_{i-1}+a_i$，而用时只需用 $O(1)$ 的时间复杂度。

但是，即使加了前缀和也会超时三个点，没法 AC。

但突然发现对于所有测试数据，$1 \le l \le r \le n \le 10^4$，$1 \le q \le 10^6$，$0 \le a_i \le 10^{10}$，于是就可以用离线做法了。

代码见下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N = 10005;
long long a[N], ans[N], sum[1000005];
vector<long long>p[N], q[N];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long n, T, l, r, x;
	cin >> n >> T;
	for (long long i = 1; i <= n; i++) {
		cin >> x;
		a[i] = a[i - 1] + x;
	}
	for (long long i = 1; i <= T; i++) {
		cin >> l >> r;
		p[l].push_back(r);
		q[l].push_back(i);
	}
	for (long long i = 1; i <= n; i++) {
		ans[i - 1] = 0;
		for (long long j = i; j <= n; j++) {
			ans[j] = ans[j - 1] ^ (a[j] - a[i - 1]);
		}
		for (long long j = 0; j < p[i].size(); j++) {
			sum[q[i][j]] = ans[p[i][j]];
		}
	}
	for (long long i = 1; i <= T; i++)
		cout << sum[i] << '\n';
	return 0;
}
```

---

## 作者：Laisira (赞：3)

## 也许貌似大概可以用低配的莫队
### 题面
字面意思，给一个序列，$q$ 次查询，要求的是：

 $(a_l) \oplus (a_l+a_{l+1}) \oplus (a_l+a_{l+1}+a_{l+2}) \oplus \dots \oplus (a_l + a_{l+1} + a_{l+2} + \dots + a_r)$ 

### 思路
$q$ 有点大，其他都很小，似乎可以用一个低配版的莫队。因为 $q$ 比 $n$ 大，所以非极限的 $O(nq)$ 随便跑，极限数据必定有一些重复，将询问按 $l$ 和 $r$ 排序，$l$ 相同时只移动右指针，然后就过了，快读都不需要（似乎跟莫队差远了）。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int pre[10005];
struct Member {
    int l,r,id;
} e[1000005];
bool cmp(Member it,Member is) {
    if(it.l!=is.l)return it.l<is.l;
    return it.r<is.r;
}
int answer[1000005];
signed main()
{
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>pre[i],pre[i]+=pre[i-1];
    for(int i=1;i<=q;i++)
    {
        int l,r;
        cin>>l>>r;
        e[i]={l,r,i};
    }
    sort(e+1,e+1+q,cmp);
    int last=0,now,ans;
    for(int i=1;i<=q;i++)
    {
        if(e[i].l!=last) {
            ans=0;
            last=e[i].l;
            now=e[i].r;
            for(int j=e[i].l;j<=e[i].r;j++)
                ans^=pre[j]-pre[e[i].l-1];
        } else {
            for(int j=now+1;j<=e[i].r;j++)
                ans^=pre[j]-pre[e[i].l-1];
            now=e[i].r;
        } answer[e[i].id]=ans;
    }
    for(int i=1;i<=q;i++)
        cout<<answer[i]<<"\n";
    return 0;
}
```

---

## 作者：xuan_never (赞：2)

老师测试给的题。

刚开始，我忘记了异或可以前缀和，只打出了一个 $O(nq)$ 的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, q, l, r;
ll a[100005], ans;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> a[i], a[i] += a[i - 1];
	while (q--) {
		cin >> l >> r;
		ans = 0;
		for (int i = l; i <= r; ++i)
			ans ^= a[i] - a[l - 1];
		cout << ans << '\n';
	}
	return 0;
}
```
结果就是：48 pts。

正片开始。

## 思路
一个显然的思路是，$O(n^2)$ 预处理出一个表，然后 $O(1)$ 询问，然而**空间**不允许。

考虑到离线处理，因为只有 $l$ 对结果序列有影响，所以按 $l$ 排序询问，对于每个不同的 $l$ 再进行前缀和，再按询问顺序输出，最终复杂度 $O(n^2+q\log q)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<pair<int, int>, int> pip;
#define fi first
#define se second
int n, q;
ll a[100005], an[100005], ans[1000006];
pip l[1000006];
bool cmp(pip x, pip y) {
	return x.fi.fi < y.fi.fi;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> a[i], a[i] += a[i - 1];
	for (int i = 0; i < q; ++i)
		cin >> l[i].fi.fi >> l[i].fi.se,
		l[i].se = i;
	sort(l, l + q, cmp);
	for (int j = l[0].fi.fi; j <= n; ++j)
		an[j] = an[j - 1] ^ a[j] - a[l[0].fi.fi - 1];
	ans[l[0].se] = an[l[0].fi.se];
	for (int i = 1; i < q; ++i) {
		if (l[i].fi.fi != l[i - 1].fi.fi) {
			memset(an, 0, sizeof an);
			for (int j = l[i].fi.fi; j <= n; ++j)
				an[j] = an[j - 1] ^ a[j] - a[l[i].fi.fi - 1];
		} ans[l[i].se] = an[l[i].fi.se];
	} for (int i = 0; i < q; ++i)
		cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：Brilliant11001 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P10401)

### 题目大意：

给定一个长度为 $n$ 的序列，有 $q$ 次询问，每次询问一个区间 $[l,r]$，需要输出该区间内每个前缀的和的异或和。

很容易想到用前缀和维护序列 $a$，异或和暴力处理，但这样的时间复杂度是 $O(nq)$ 的，只能通过测试点 $0,1,3$。

又考虑到这是个静态区间问题，想到莫队。

思考了一会儿发现左端点不好维护，但右端点可以 $O(1)$ 维护，于是借用了莫队的思想（其实就是普通的双指针），将询问按左端点为第一关键字，右端点按第二关键字升序排序。

左端点与上一个询问相同时，只需右移右端点就行了。

左端点与上一个询问不同时，暴力计算。

这样的最坏时间复杂度是 $O(n^2)$，~~可以水过此题~~。

总之，莫队的思想还是很重要的。

$\texttt{Code:}$

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10010, M = 1000010;

int n, m;
long long s[N];

struct node{
	int id, l ,r;
}q[M];
long long ans[M];

bool cmp(node x, node y) {
	if(x.l == y.l) return x.r < y.r;
	return x.l < y.l;
}

void add(int x, int l, long long &res) {
	res ^= (s[x] - s[l - 1]);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &s[i]);
		s[i] += s[i - 1];
	}
	int id, l, r;
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &l, &r);
		q[i] = {i, l, r};
	} 
	sort(q + 1, q + m + 1, cmp);
	long long res;
	for(int i, k = 1; k <= m; k++) {
		id = q[k].id, l = q[k].l, r = q[k].r;
		if(k == 1 || l != q[k - 1].l) {
			res = 0;
			for(int j = l; j <= r; j++) 
				res ^= (s[j] - s[l - 1]);
			i = q[k].r;
		}
		else while(i < r) add(++i, q[k - 1].l, res); //幼年的莫队 
		ans[id] = res;
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：HasNoName (赞：2)

### 思路

先用前缀和，设 $s_i=a_1+a_2+\dotsi+a_i$。

$l$ 到 $r$ 的答案为 $(s_l-s_{l-1})\oplus(s_{l+1}-s_{l-1})\oplus(s_{l+2}-s_{l-1})\oplus\dotsi\oplus(s_r-s_{l-1})$。

在考虑离线就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10005;
ll a[N],ans[N],sum[1000005];//用sum存答案
vector<int>p[N],q[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n,T,l,r,x;
	cin>>n>>T;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		a[i]=a[i-1]+x;//前缀和
	}
	for(int i=1;i<=T;i++)
	{
		cin>>l>>r;
		p[l].push_back(r);//离线
		q[l].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		ans[i-1]=0;
		for(int j=i;j<=n;j++)
		{
			ans[j]=ans[j-1]^(a[j]-a[i-1]);//转移
		}
		for(int j=0;j<p[i].size();j++)
		{
			sum[q[i][j]]=ans[p[i][j]];
		}
	}
	for(int i=1;i<=T;i++)
		cout<<sum[i]<<'\n';
	return 0;
}
```

---

## 作者：zjh114514 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P10401)

## 思路

记 $f(l, r) = \bigoplus _ {i = l} ^ r \sum _ {j = l} ^ i a _ j$，即询问 $[l, r]$ 时要输出的值。

注意到 $n \le 10 ^ 4$，容易得到以下代码。

``` cpp
for (int i = 1; i <= n; i++) {
    f[i][i] = a[i];
    for (int j = i + 1; j <= n; j++)
        f[i][j] = f[i][j - 1] ^ sum[j] - sum[i - 1] // sum 为前缀和
}

for (int i = 0; i < q; i++) ...
// O(1) 回答询问
```

但显然这样空间会爆。

考虑将询问离线，再暴力求答案，这样就不需要 $f$ 数组记录了。

时间复杂度 $O(n ^ 2)$，空间复杂度 $O(q)$。
## 代码

``` cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long; // 不要忘了 long long 哦

int n, q;
LL a[10001];
struct Range { int l, r, info; } qry[1000000];
LL ans[1000000];

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < q; i++) cin >> qry[i].l >> qry[i].r, qry[i].info = i;
    sort(qry, qry + q, [] (Range a, Range b) { return a.l != b.l ? a.l < b.l : a.r < b.r; });
    // 左端点靠左的放前面，左端点相同时右端点靠左的放前面
    // 排序保证暴力计算时能逐个回答询问
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        long long sum = 0, tmp = 0; // 记录当前区间和和 f
        for (int j = i; j <= n; j++) {
            sum += a[j];
            tmp ^= sum;
            while (i == qry[cur].l && j == qry[cur].r) // 不要用 if，可能有区间重合
                ans[qry[cur++].info] = tmp; // 把答案按正确的顺序放好再输出
        } 
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
```

---

## 作者：2022_37_yzyUUU (赞：1)

# P10401 题解

## [题面](https://www.luogu.com.cn/problem/P10401)

### 思路

因为当 $l≤t≤r$ 时，从 $l$ 到 $r$ 的答案等于 $l$ 到 $t$ 的答案异或 $t$ 到 $r$ 的答案。

所以我们可以把数据离线处理，使用结构体排序，主要关键字为左端点，次要关键字为右端点，升序排序。

然后如果左端点一样的，就不用再从新算一遍了，只需在在上一个的基础上异或即可，这样会快很多。

### Code

```
#include<bits/stdc++.h>
using namespace std;
long long n,ans[1000006],q,a[10004];//记得开longlong
struct ask666{
	long long id,l,r;
}p[10000006];
bool cmp(ask666 x,ask666 y){
	if(x.l!=y.l)return x.l<y.l;
	return x.r<y.r;
}
long long ask1(int l,int r){
	long long t=0;
	for(int i=l;i<=r;i++){
		t^=(a[i]-a[l-1]);
	}return t;
}
long long ask2(int o,int l,int r){
	long long t=0;
	for(int i=l;i<=r;i++){
		t^=(a[i]-a[o-1]);
	}return t;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]+=a[i-1];
	}
	for(int i=1;i<=q;i++){
		cin>>p[i].l>>p[i].r;
		p[i].id=i;
	}
	sort(p+1,p+q+1,cmp);
	for(int i=1;i<=q;i++){
		if(i!=1&&p[i].l==p[i-1].l)
			ans[p[i].id]=ans[p[i-1].id]^ask2(p[i].l,p[i-1].r+1,p[i].r);
		else 
			ans[p[i].id]=ask1(p[i].l,p[i].r);
	}
	for(int i=1;i<=q;i++)
		cout<<ans[i]<<"\n";
}
```

## End

---

## 作者：封禁用户 (赞：0)

我们可以用 $sum_i$ 表示 $\sum_{j=1}^i a_i$，那么问题转化成 $\bigoplus_{i=l}^l (sum_{i}-sum_{l-1})$。

注意到上面那个玩意儿不会再优化了，又看到 $n\le 10^4$ 考虑离线下来搞。

我们可以枚举左端点 $i$ 后再枚举从左至右枚举右端点 $j$，在计算一个区间 $[i,j]$ 的答案时，由于已知 $[i,j-1]$ 的答案，可以直接递推到 $[i,j]$，那么这样就是 $O(n^2)$ 的。

可是这样内存也是 $O(n^2)$ 的，考虑优化。

我们注意到很多区间都是“没用”的，所以我们可以开个 `map<pair<int,int>,int>` 来记录一个区间是否“有用”，只把“有用”的则记下来。

那么这样空间复杂度是 $O(q)$ 的，可以通过。

---

## 作者：forever516 (赞：0)

## 题意
这题题意已经很明显了，就是用离线的方法。
## 解法
先暴力预处理，接着我们在每次询问离线，然后再预处理时判断是否询问到了这个区间即可，如果询问到了就将答案储存下来。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e4+5,M=1e7+5;
ll s[N], ans[N], cnt[M],n, T, l, r, x,i,j;
vector<ll>p[N], q[N];
int main() {
	cin >> n >> T;
	for (i = 1; i <= n; i++) {
		cin >> x;
		s[i] = s[i - 1] + x;//前缀和处理 
	}
	for (i = 1; i <= T; i++) {
		cin >> l >> r;
		p[l].push_back(r);
		q[l].push_back(i);
	}
	for (i = 1; i <= n; i++) {
		ans[i - 1] = 0;
		for (j = i; j <= n; j++)ans[j] = ans[j - 1] ^ (s[j] - s[i - 1]);//询问离线，判区间 
		for (j = 0; j < p[i].size(); j++)cnt[q[i][j]] = ans[p[i][j]];
	}
	for (i = 1; i <= T; i++)cout << cnt[i] << "\n";//输出即可 
	return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

## 一道不水的题~~
看到题目的第一眼，就能想到，要用**前缀和**优化。
于是，我写出来了 $48$ 分的代码，如下：
```cpp
#include <iostream>
using namespace std;
long long n, q, l, r, ans, a[10001], s[10001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for (long long i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    while (q--)
    {
        cin >> l >> r;
        ans = 0;
        for (long long i = l; i <= r; i++)
            ans ^= s[i] - s[l - 1];
        cout << ans << '\n';
    }
    return 0;
}
```
接着尝试优化，发现可以排序，按照每个 $l$ 相等的分一个区间，相同区间内再按照 $r$ 的大小排序。存一个 $num$ 变量作为相同区间的初始值 $l$，每次就可以使 $num$ 变量值每次通过前缀和更新，把前缀和数组称为 $s$，此区间左端点为 $l$，式子为：$num \gets  num \operatorname{xor} (s_j - s_{l - 1})$ 最后存好答案**并按照原来顺序复原**即可。 

代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
long long n, q, beg, num, a[10001], s[10001];
struct node
{
    long long l, r, ans, id;
}x[1000001];//答案与数据的左右端点结构体
bool cmp1(node a, node b)//变换排序
{
    if (a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}
bool cmp2(node a, node b)//还原排序
{
    return a.id < b.id;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for (long long i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    for (long long i = 1; i <= q; i++)
    {
        cin >> x[i].l >> x[i].r;
        x[i].id = i;
    }
    sort(x + 1, x + q + 1, cmp1);
    for (long long i = 1; i <= q; i++)
    {
        if (i == 1 || x[i].l != x[i - 1].l)
        {
			num = a[x[i].l];
			beg = x[i].l;
		}
		for (long long j = beg + 1; j <= x[i].r; j++)
			num ^= (s[j] - s[x[i].l - 1]);//更新求值
		x[i].ans = num;
        beg = x[i].r;
    }
    sort(x + 1, x + q + 1, cmp2);
    for (long long i = 1; i <= q; i++) cout << x[i].ans << '\n';
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

我们注意到 $n$ 的范围有点小，所以考虑 $O(n^2+q)$ 的时间复杂度。

首先，我们可以预处理出所有区间的答案，用前缀和优化可以 $O(n^2)$ 搞定。

可是这样空间会超，所以我们考虑离线下来再搞。

我们可以离线后标记一下所有会产生答案的区间，记录就只用记录所有标记过的区间就行了。

时间 $O(n^2+q)$，空间 $O(q)$。

---

