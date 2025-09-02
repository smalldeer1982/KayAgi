# Jamie and Binary Sequence (changed after round)

## 题目描述

Jamie is preparing a Codeforces round. He has got an idea for a problem, but does not know how to solve it. Help him write a solution to the following problem:

Find $ k $ integers such that the sum of two to the power of each number equals to the number $ n $ and the largest integer in the answer is as small as possible. As there may be multiple answers, you are asked to output the lexicographically largest one.

To be more clear, consider all integer sequence with length $ k $ $ (a_{1},a_{2},...,a_{k}) $ with ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/804a330680fa0a689680c55396d7d651c977b163.png). Give a value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/3a6d52e5a86468620a5b59c3452f1e46ca1a5ee4.png) to each sequence. Among all sequence(s) that have the minimum $ y $ value, output the one that is the lexicographically largest.

For definitions of powers and lexicographical order see notes.


## 说明/提示

Sample 1:

 $ 2^{3}+2^{3}+2^{2}+2^{1}+2^{0}=8+8+4+2+1=23 $

Answers like $ (3,3,2,0,1) $ or $ (0,1,2,3,3) $ are not lexicographically largest.

Answers like $ (4,1,1,1,0) $ do not have the minimum $ y $ value.

Sample 2:

It can be shown there does not exist a sequence with length 2.

Sample 3:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/32c976228a27c0f708bbb18d0f890775f96c4e59.png)

Powers of 2:

If $ x>0 $ , then $ 2^{x}=2·2·2·...·2 $ ( $ x $ times).

If $ x=0 $ , then $ 2^{x}=1 $ .

If $ x<0 $ , then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/6fdb1f744a78ad201a27505654584044743d34f7.png).

Lexicographical order:

Given two different sequences of the same length, $ (a_{1},a_{2},...\ ,a_{k}) $ and $ (b_{1},b_{2},...\ ,b_{k}) $ , the first one is smaller than the second one for the lexicographical order, if and only if $ a_{i}<b_{i} $ , for the first $ i $ where $ a_{i} $ and $ b_{i} $ differ.

## 样例 #1

### 输入

```
23 5
```

### 输出

```
Yes
3 3 2 1 0 
```

## 样例 #2

### 输入

```
13 2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
1 2
```

### 输出

```
Yes
-1 -1 
```

# 题解

## 作者：CarroT1212 (赞：3)

2023-10-20 upd：更换了写法。

------------

### 题意

给定整数 $n,k$，现在你需要尝试构造一个长度为 $k$ 的序列 $a$，使得 $n=\sum\limits_{i=1}^n 2^{a_i}$，$a$ 中元素可以重复，要求在 $\max\{a_1,a_2,\cdots,a_k\}$ 尽可能小的条件下，$a$ 的字典序尽可能大。如果存在这样的序列，输出 `Yes` 和序列 $a$，否则输出 `No`。

数据范围：$1 \le n \le 10^{18}$，$1 \le k \le 10^5$，保证最终答案中的数范围为 $[-10^{18},10^{18}]$。

------------

### 解法分析

发现 $\max\{a_1,a_2,\cdots,a_k\}$ 的范围也就在 $[-60,60]$ 的样子，考虑枚举它。设 $\max\{a_1,a_2,\cdots,a_k\}=y$，则我们需要求出最小的满足条件的 $y$。

首先，如果没有 $y$ 的限制，要把 $n$ 直接分解成幂的和并且让幂的个数最少，就是直接把它为 $1$ 的二进制位拆出来。

但如果加上了这个限制，所有 $a_i>y$ 的 $2^{a_i}$ 都超限了，这时可以把超限的 $2^{a_i}$ 拆成若干个合法的 $2^y$ 的和，具体地，每个 $a_i>y$ 的 $2^{a_i}$ 都可以拆为 $2^{a_i-y}$ 个 $2^y$。因为我们把每一个 $a_i$ 都变得尽量大，这么做 $a$ 的长度一定是最小的，而且将 $a_i$ 降序排序后它的字典序也一定是最大的。

那么判断一个 $y$ 合法的条件就是，如果按上面的方法把所有超限的 $a_i$ 都拆掉，$a$ 的长度不大于 $k$。否则如果按最优方法拆都塞不进 $k$ 就显然是不合法的。还可以二分加速一下，不过必要不大。

但是求出了最小的 $y$ 之后还有一个问题：$a$ 要是太短了怎么办？

这时可以压榨 $a$ 的最后一个元素，设其为 $a_{z}$，则显然可以把它变为两个 $a_{z}-1$。每次这么做可以使它的长度增加 $1$，反复执行直到 $a$ 的长度等于 $k$。因为只动最后一个元素，这样同时还保证了 $a$ 的字典序是最大的。

最后有几个细节：$y$ 可以是负的，否则你会在 #12 去世；拆 $2^{a_i}$ 的时候 $2^{a_i-y}$ 可能巨大，记得特判，否则你会在 #15 去世。

------------

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vo void()
using namespace std;
const ll N=1e5+7;
ll n,k;
vector<ll> nn;
int main() {
	scanf("%lld%lld",&n,&k);
	for (ll i=61;~i;i--) if (n>>i&1) nn.pb(i);
	for (ll i=-61;i<=61;i++) {
		vector<ll> ans;
		ll flg=0;
		for (ll j:nn) {
			if (j>i) {
				if (j-i>61||1ll<<j-i>k) { flg=1; break; }
				for (ll l=1;l<=1ll<<j-i;l++) ans.pb(i);
			}
			else ans.pb(j);
			if (ans.size()>k) { flg=1; break; }
		}
		if (flg) continue;
		while (ans.size()<k) {
			ll x=ans.back();
			ans.pop_back(),ans.pb(x-1),ans.pb(x-1);
		}
		printf("Yes\n");
		for (ll i:ans) printf("%lld ",i);
		return 0;
	}
	printf("No");
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：2)

CPS 前发题解据说能攒 rp。那就祝各位 rp++。

把 $x$ 分成多个二的幂的和，至少需要 其二进制下出现 $1$ 的次数 个数。这个应该是显然的，可以参考倍增时从大到小枚举确定最高位，应该是一个道理。

所以无解的情况就能判掉了。

$2^a=2^{a-1}+2^{a-1}$。也就是说对于答案的一个 $a$，我们可以把它拆成两个 $a-1$。

题目要求最大值最小我们每次就拆最大的数，直到个数满足要求。

过不了。原因是每次拆最大的数无法满足字典序最大的要求。因为如果你这一次拆完以后最大值不可能再改变那么你可以一直拆最小的数使得前面的数尽量大。

所以记录最大的数最小会被拆成什么，然后重新做一遍拆数的操作，发现拆完之后最大值和原来得到的最后的最大值相等就转去拆最小的数。

码风不好评。

```cpp
#include <bits/stdc++.h>
#define lint __int128
#define int long long
#define Il inline
#define Rg register
#define Ri Rg int
#define pb push_back
#define vec vector
#define fi first
#define se second
#define IT ::iterator
#define pque priority_queue

using namespace std;
//typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
const int N=1e5;
const db eps=1e-9,pi=acos(-1.0);

int n,K,bn=0,b[105],c=0;
pque<int>pq;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>K;for(Ri x=n;x;x>>=1ll){b[++bn]=x&1ll;if(b[bn])c++,pq.push(bn-1);}
	if(c>K){cout<<"No";return 0;}cout<<"Yes\n";
	for(;c<K;c++){int fq=pq.top();pq.pop();pq.push(fq-1),pq.push(fq-1);}//第一次处理最后得到的最大值
	int mx=pq.top();while(!pq.empty())pq.pop();c=0;
	for(Ri i=1;i<=bn;i++)if(b[i])c++,pq.push(i-1);//重新拆一遍
	for(;c<K&&pq.top()!=mx;c++){int fq=pq.top();pq.pop();pq.push(fq-1),pq.push(fq-1);}
	while((int)pq.size()>1){cout<<pq.top()<<' ';pq.pop();}int t=pq.top();
	if(c==K){cout<<t<<'\n';return 0;}//特判不需要拆最小数的情况
    t--;for(;c<K-1;c++,t--)cout<<t<<' ';cout<<t<<' '<<t;
	return 0;
}
```

---

## 作者：xunzhen (赞：2)

这道题思路很简单，但不过细节真的多~~调了我一个多小时~~。首先特判一下这个数二进制位为1的位数是否大于$k$如大于，就直接输出`NO`。然后把这个数二进制分解，把最大的位尽量的往下压，然后再挑**一个**最低的位往下压压到满足题意为止，具体解释看代码(在代码里的变量$s$就是$k$)。

~~代码丑到突破天际~~

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long LL;
LL c[100111];
int main(){
#ifndef ONLINE_JUDGE
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
#endif
	LL n,s;
	cin>>n>>s;
	LL i=0,k=n,sum=0;
	while (k){
		c[i++]=k&1LL;	//二进制分解
		sum+=(k&1LL);
		k>>=1LL;
	}
	if (sum>s){
		printf("No\n");
		return 0;	//特判
	}
	LL p=0;
	for (i=65;i>=-65;i--){
		if (i<0) i+=100100;	//因为数组下标非负，所以特殊处理一下
		if (c[i]){
			p=i;
			if (sum+c[i]<=s){
				int nt=i-1;
				if (nt<0) nt+=100100;
				c[nt]+=2*c[i];	//一个变两个
				sum+=c[i];
				c[i]=0;
			}else break;	//压不了了就退掉
		}
		if (i>100) i-=100100;
	}
	for (i=65;i>=-65;i--){
		if (i<0) i+=100100;
		if (c[i]) p=i;
		if (i>100) i-=100100;
	}
	i=p;	//挑位数最低的
	while (sum<s){	//压到个数为k为止
		c[i]--;
		i--;
		if (i<0) i+=100100;
		c[i]+=2;
		sum++;
	}
	printf("Yes\n");
	//巧妙输出
	for (i=65;i>=-100000;i--){
		if (i<0) i+=100100;
		if (c[i])
			for (int j=1;j<=c[i];j++)
				printf("%I64d ",i>100?(i-100100):i);	//CF上要用I64d
		if (i>=100) i-=100100;
	}
	puts("");
	return 0;
}
```

---

## 作者：Kyl_in_2024 (赞：1)

**题目大意**

构造一个长度为 $k$ 的序列 $a$，使得正整数 $n = \sum \limits_{i=1}^n 2^{a_i}$（$n$ 是定值）。要求序列 $a$ 当中最大值尽可能小，并且字典序尽可能大。

**思路**

一开始的思路就是用优先队列存储，每次把最大的数拆成两个，然后直到队列里有 $k$ 个数为止。时间上没有任何问题，但是很快就死在了第五个测试点。

什么原因呢？因为题面还有一个字典序。一开始没看出来，后来[这个大佬](https://www.luogu.com.cn/user/676520)给我讲了 $10^{-114514}$ 秒我就恍然大悟了：因为每次选择最大的两个去拆，如果已经满足了 $\max\{a_1,a_2,\cdots,a_k\}$ 是最小的，那么去拆最大的数反而会导致字典序更小。

所以我们可以先算出 $\max\{a_1,a_2,\cdots,a_k\}$ 最小是多少，然后重新再计算一遍，如果最大的数已经是这个值了就退出。最后我们就一直选择最小的那个来拆成两个。

剩下更多细节都在代码注释里。

**代码**

```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
signed main(){
	priority_queue<int> a,b;
	int n,k;
	cin>>n>>k;
	for(int i=62;i>=0;i--){
		if(n&(1ll<<i)) a.push(i);
	}
	b=a;//备份（
	int tk=k-a.size();
	if(tk<0){//如果不能完成
		cout<<"No";
		return 0;
	}
	cout<<"Yes\n";
	for(int i=1;i<=tk;i++){
		int t=a.top();
		a.pop();
		t--;//拆成两个
		a.push(t);
		a.push(t);
	}
	int tmp=a.top();//最大值最小是多少
	while(b.top()>tmp){//如果超过就退出
		int t=b.top();
		b.pop();
		t--;
		b.push(t);
		b.push(t);
	}
	while(b.size()>1){
		cout<<b.top()<<" ";
		b.pop();
		k--;
	}//此时的b.top()是最小值
	for(int i=1;i<k;i++){
		cout<<b.top()-i<<" ";//这里可以想象成拆x，x是最小的，变成x-1,x-1。然后是x-1,x-2,x-2、x-1,x-2,x-3,x-3……总之除了最后两个是相等的剩下全是等差数列。
	} 
	cout<<b.top()-k+1;//输出相等的那个
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

首先我们考虑如果需要用最少的数表示 $n$ 的话需要 $\operatorname{popcount}$ 个（即 $n$ 的二进制表示下的 $1$ 的个数），如果 $k$ 比这个还小，那么输出 `No`。

我们知道，可以通过将序列中某个 $x$ 拆为 $2$ 个 $x-1$ 增加序列中数的个数，那么不难发现 $a$ 中最大值减小将导致 $a$ 中数增加，所以可以二分或者枚举在 $a$ 的大小不超过 $k$ 的最小的 $a$ 中最大值 $mx$。

我们先把 $a$ 弄成 $n$ 的二进制表示下的每一个是 $1$ 的位置，然后把超过 $mx$ 的全部换为若干个 $mx$（换法就是把将序列中某个 $x$ 拆为 $2$ 个 $x-1$），如果还需要增加序列中数的个数，那么就每次暴力地把序列中的最小值再拆为两个数，重复直到 $a$ 中有 $k$ 个数为止。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
set<int> st;
signed main()
{
	int n,k;
	cin>>n>>k;
	if(k<__builtin_popcountll(n))
	{
		cout<<"No";
		return 0;
	}
	cout<<"Yes\n";
	for(int i=60;~i;i--) if(n>>i&1) st.insert(i);
	int mx;
	for(int i=-60;;i++)
	{
		int cnt=0;
		for(auto j:st)
		{
			if(j>i)
			{
				if(j-i>60) goto E;
				cnt+=(1ll<<(j-i));
				if(cnt>k) goto E;
			}
			else cnt++;
		}
		if(cnt<=k)
		{
			mx=i;
			break;
		}
		E:;
	}
	vector<int> ans(1e5+10);
	int now=0;
	for(auto i:st)
	{
		if(i>mx) for(int t=1;t<=1ll<<(i-mx);t++) ans[++now]=mx;
		else ans[++now]=i;
	}
	sort(ans.begin()+1,ans.begin()+now+1,greater<int>());
	while(now<k)
	{
		ans[now]=ans[now+1]=ans[now]-1;
		now++;
	}
	for(int i=1;i<=now;i++) cout<<ans[i]<<' ';
}

---

## 作者：wangyibo201026 (赞：0)

## solution

考前攒 RP 写的题解。

看一眼考虑二分，但实则并不需要考虑二分？

考虑我们用一个堆来存储每个答案，存一个 pair，表示指数和指数出现次数，初始时就是二进制拆分后的结果。

然后我们要让最大值最小，所以如果假设目前最大的指数 $x$，能够全部变为 $x - 1$，我们就全部变，否则就退出（因为最大值不能变了，我们现在的目标是使字典序最大）。

好，我们已经完成了第一步，目前这个序列既是最大值最小也是字典序最大的了，但是可能个数不够 $k$，此时我们拿出最小的一个指数，疯狂的拆分，拆分直至 $k$ 个才停止（这是因为字典序定义，第一个不同的大小，所以尽量不要动前面的）。

然后你写了一下，发现过了。

## code

code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 1e5 + 5;

int n, k, cnt;
priority_queue < pii > q, ans;
priority_queue < pii, vector < pii >, greater < pii > > q2;

void Solve () {
	cin >> n >> k;
	for ( int i = 0; i <= 60; i ++ ) {
		if ( ( n >> i ) & 1 ) {
			q.push ( { i, 1 } );
			cnt ++;
		}
	}
	if ( cnt > k ) {
		cout << "No";
		return ;
	}
	while ( !q.empty () ) {
		pii x = q.top ();
		q.pop ();
		if ( cnt + x.second <= k ) {
			cnt += x.second;
			x.second *= 2;
			x.first --;
			if ( !q.empty () && q.top ().first == x.first ) {
				x.second += q.top ().second;
				q.pop ();
				q.push ( x );
			}
			else {
				q.push ( x );
			}
		}
		else {
			q.push ( x );
			break;
		}
	}
	if ( cnt == k ) {
		cout << "Yes\n";
		while ( !q.empty () ) {
			for ( int i = 1; i <= q.top ().second; i ++ ) {
				cout << q.top ().first << " ";
			}
			q.pop ();
		}
		return ;
	}
	while ( !q.empty () ) {
		q2.push ( q.top () );
		q.pop ();
	}
	pii tmp = q2.top ();
	q2.pop ();
	tmp.second --;
	if ( tmp.second ) {
		q2.push ( tmp );
	}
	for ( int i = 1; i <= k - cnt; i ++ ) {
		tmp.first --;
		q2.push ( { tmp.first, 1 } );
	}
	q2.push ( { tmp.first, 1 } );
	while ( !q2.empty () ) {
		q.push ( q2.top () );
		q2.pop ();
	}
	cout << "Yes\n";
	while ( !q.empty () ) {
		for ( int i = 1; i <= q.top ().second; i ++ ) {
			cout << q.top ().first << " ";
		}
		q.pop ();
	}
}

signed main () {
#ifdef judge
	freopen ( "Code.in", "r", stdin );
	freopen ( "Code.out", "w", stdout );
	freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# 题意

> 把一个数分解成**恰好** $k$ 个 $2^{a_i}$ 次方的和，可以重复，要求保证最大的 $a_i$ 要尽可能的小时，$a$ 的字典序尽可能大，输出序列 $a$。

# 分析

首先我们借助二进制拆出一个满足 $n=\sum 2^{a_i}$ 序列 $a$，满足 $a$ 的长度最小。

若此时 $a$ 的长度大于 $k$，显然无解。

因为 $2^m=2^{m-1}+2^{m-1}$，我们每次取出序列中最大的元素 $a_i$，然后向序列中加入两个 $a_i-1$ 直到序列的长度等于 $k$。

因为我们每次拆出的元素均为序列中的最大值，显然能保证此时 $\max a_i$ 是最小的。

模拟上述过程，然后得到 WA on #5。

---

当 $k=5$，而某一步得到的 $a=\{4, 4, 2, 1\}$ 这种情况就能 hack 掉这种做法。

因为此时拆掉最大元素 $4$ 得到的序列 $a=\{4,3,3,2,1\}$ 的字典序小于拆掉最小元素 $1$ 得到的序列 $a=\{4, 4, 2, 0, 0\}$。

发现如果当前的 $\max a_i$ 等于答案中的 $\max a_i$ 时，拆掉最小元素的方案会使字典序大于拆掉最小元素的方案。

使用 `set` 模拟即可。

[AC 记录](https://codeforces.com/contest/916/submission/278191925)

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

multiset<int, greater<int>> s, s0;

int main()
{
    int64_t n, k;
    cin>>n>>k;
    for(int i=0;i<63;i++) 
        if(n&(1ll<<i)) s.emplace(i);  
    if(s.size()>k) return cout<<"No", 0;
    cout<<"Yes\n";
    s0=s;
    while(s.size()<k)
    {
        int p=*s.begin();
        s.erase(s.begin());
        s.emplace(p-1);
        s.emplace(p-1);
    }
    int mx=*s.begin();
    while(s0.size()<k)
    {
        int p=*s0.begin();
        if(p==mx) break;
        s0.erase(s0.begin());
        s0.emplace(p-1);
        s0.emplace(p-1);
    }
    while(s0.size()<k)
    {
        int p=*s0.rbegin();
        s0.erase(prev(s0.end()));
        s0.emplace(p-1);
        s0.emplace(p-1);
    }
    for(auto i:s0) cout<<i<<' ';
}
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
首先确定最大 $a_i$ 的最小值。可以把 $n$ 的二进制指数塞入优先队列，每次把最大的指数弹出，拆成两个，再塞回优先队列，直到队列里有 $k$ 个数为止，此时队首就是最大 $a_i$ 的最小值。

接着让字典序最大。将优先队列清空，把 $n$ 的二进制指数再次塞入优先队列，分裂最大值，直到队首等于之前求的最大 $a_i$ 的最小值，此时分裂最小值。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<int>q,ans;
long long n,k,t;
int main(){
	cin>>n>>k;
	for(int i=0;i<=60;++i)
		if((n>>i)&1) q.push(i);
	t=k-q.size();
	if(t<0){
		puts("No");
		return 0;
	}
	ans=q;
	while(t--) q.push(q.top()-1),q.push(q.top()-1),q.pop();
	while(ans.size()<q.size()&&ans.top()>q.top()) ans.push(ans.top()-1),ans.push(ans.top()-1),ans.pop();
	puts("Yes");
	t=q.size()-ans.size();
	while(ans.size()>1) cout<<ans.top()<<' ',ans.pop();
	for(int i=1;i<=t;++i) cout<<ans.top()-i<<' ';
	cout<<ans.top()-t;
	return 0;
}
```

---

## 作者：PDAST (赞：0)

## 题意
把一个数分解成 $k$ 个 $2^{i}$ 的数的和，求在序列中最大值最小的情况下字典序最大的序列。例如把 $2$ 分解成 $3$ 个数，分别是 $2^{-1}$、$2^{-1}$、$2^{0}$。
## 思路
思路其实挺简单的，先转化二进制，把那一位是一的位置加入队列，建立一个优先队列，排序方法是大到小，对最大的取出分解，即删去最大的，加上两个该数减一，挨个分解求出序列最大值，再输出前长度减一位的数，把最后一个数分解到长度符合要求即可。
## 代码
~~~
#include<bits/stdc++.h>
#define int long long
using namespace std;
int kth[101];
signed main(){
	kth[0]=1;
	for(int i=1;i<=62;i++){
		kth[i]=kth[i-1]<<1;
	}
	int k,n,m=0;
	cin>>n>>k;
	priority_queue<int>q,ans;
	while(n){
		if(n&1){
			q.push(m);
		}
		n>>=1;
		m++;
	}
	if(q.size()>k){
		cout<<"No";
		return 0;
	}
	ans=q; 
	while(q.size()<k){
		int tmp=q.top();
		q.pop();
		q.push(tmp-1);
		q.push(tmp-1);
	}
	cout<<"Yes\n";
	while(ans.size()<q.size()&&ans.top()>q.top()){
		int tmp=ans.top();
		ans.pop();
		ans.push(tmp-1);
		ans.push(tmp-1);
	}
	int t=k-ans.size();
	while(ans.size()>1){
		cout<<ans.top()<<" ";
		ans.pop();
	}
	for(int i=1;i<=t;i++){
		cout<<ans.top()-i<<" ";
	}
	cout<<ans.top()-t;
}
~~~cpp

---

## 作者：YFF1 (赞：0)

# 题解
## 解法分析：
一道二进制的构造题，为了使这个序列符合题目里的要求，我们可以用优先队列来做。具体做法是：在不知道最大值是什么时，不断将最大值拆成两个次大值之和，以此来获得最顶端的最小值。注意在优先队列最顶端的元素已经取得最小值时，使用剩下的拆分机会，不断将最后一个元素拆分。
按照这样的做法即可取得序列的字典序最大值。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
signed main () {
	cin>>n>>k;
	priority_queue<int,vector<int>>q,q2; 
	for(int i=log2(n);i>=0;i--){
		if((n>>i)&1)q.push(i);
	}//加入优先队列中
	int l=q.size();
	if(l>k){
		cout<<"No";
		return 0;
	}//直接判断不能分出来的
	cout<<"Yes"<<endl;
	q2=q; 
	while(q.size()<k){
		int x=q.top();
		x--;
		q.pop();
		q.push(x);
		q.push(x);//通过优先队列1号来求顶端可以取得的最大值
	}
	while(q2.size()<q.size()&&q2.top()>q.top()){
		int x=q2.top();
		x--;
		q2.pop();
		q2.push(x);
		q2.push(x);//通过优先队列2号来求在顶端已经取得最大值的情况时最小值
	}
	int k2=q.size()-q2.size();
	while(q2.size()>1){
		cout<<q2.top()<<" ";
		q2.pop();
	}
	for(int i=1;i<=k2;i++)cout<<q2.top()-i<<" ";
	cout<<q2.top()-k2;//取字典序最大值
	return 0;
}
```

---

## 作者：Peaky (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF916B)。
### 思路
题目要求 $y$ 尽量小的前提下 $a_1 ,a_2,...,a_i$ 的字典序尽量小。  
首先我么容易想到把 $n$ 的二进制先求出来，再把所有的 $1$ 所对应的位数放进优先队列中，再一次将最大值 $a_1$ **拆成两个相同的数** $a_1 -1$ 再放回队列中，多次操作，直至队列的元素个数为 $k$ 为止。  
如果直接这么写只保证的 $y$ 最小而没保证字典序最小，所以我们要采取其他的方法。
### 正解
首先按照刚才的思路找到最小的 $y$，接着，再依次输出队列里的元素直到**只剩下一个元素为止**。此时输出的个数距离 $k$ 可能还差一些，考虑到每次拆分两个数会导致新的数比原来的数少 $1$，所以我们不难发现，剩下要输出的数是个**递减的等差数列且公差为** $1$。所以我们只需要求出有多少项即可。到了这一步，就已经没有什么问题了。
### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
long long n,k,l=1;
int i,j,tl;
priority_queue<int> q,a;
int main(){
	cin>>n>>k;
	for(int i=60;i>=0;i--) {if(n>>i&1) q.push(i);}
	if(k<q.size()) return puts("No"),0;
	a=q;
	while(q.size()<k) {q.push(q.top()-1);q.push(q.top()-1);q.pop();}
	while(a.size()<q.size()&&a.top()>q.top()) {a.push(a.top()-1);a.push(a.top()-1);a.pop();}
	puts("Yes");
	int t=q.size()-a.size();
	while(a.size()>1) cout<<a.top()<<" ",a.pop();
	for(int i=1;i<=t;i++) cout<<a.top()-i<<" ";
	cout<<a.top()-t;
	return 0;
}
```

---

