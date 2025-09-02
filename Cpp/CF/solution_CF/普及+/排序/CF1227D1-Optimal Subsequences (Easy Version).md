# Optimal Subsequences (Easy Version)

## 题目描述

This is the easier version of the problem. In this version $ 1 \le n, m \le 100 $ . You can hack this problem only if you solve and lock both problems.

You are given a sequence of integers $ a=[a_1,a_2,\dots,a_n] $ of length $ n $ . Its subsequence is obtained by removing zero or more elements from the sequence $ a $ (they do not necessarily go consecutively). For example, for the sequence $ a=[11,20,11,33,11,20,11] $ :

- $ [11,20,11,33,11,20,11] $ , $ [11,20,11,33,11,20] $ , $ [11,11,11,11] $ , $ [20] $ , $ [33,20] $ are subsequences (these are just some of the long list);
- $ [40] $ , $ [33,33] $ , $ [33,20,20] $ , $ [20,20,11,11] $ are not subsequences.

Suppose that an additional non-negative integer $ k $ ( $ 1 \le k \le n $ ) is given, then the subsequence is called optimal if:

- it has a length of $ k $ and the sum of its elements is the maximum possible among all subsequences of length $ k $ ;
- and among all subsequences of length $ k $ that satisfy the previous item, it is lexicographically minimal.

Recall that the sequence $ b=[b_1, b_2, \dots, b_k] $ is lexicographically smaller than the sequence $ c=[c_1, c_2, \dots, c_k] $ if the first element (from the left) in which they differ less in the sequence $ b $ than in $ c $ . Formally: there exists $ t $ ( $ 1 \le t \le k $ ) such that $ b_1=c_1 $ , $ b_2=c_2 $ , ..., $ b_{t-1}=c_{t-1} $ and at the same time $ b_t<c_t $ . For example:

- $ [10, 20, 20] $ lexicographically less than $ [10, 21, 1] $ ,
- $ [7, 99, 99] $ is lexicographically less than $ [10, 21, 1] $ ,
- $ [10, 21, 0] $ is lexicographically less than $ [10, 21, 1] $ .

You are given a sequence of $ a=[a_1,a_2,\dots,a_n] $ and $ m $ requests, each consisting of two numbers $ k_j $ and $ pos_j $ ( $ 1 \le k \le n $ , $ 1 \le pos_j \le k_j $ ). For each query, print the value that is in the index $ pos_j $ of the optimal subsequence of the given sequence $ a $ for $ k=k_j $ .

For example, if $ n=4 $ , $ a=[10,20,30,20] $ , $ k_j=2 $ , then the optimal subsequence is $ [20,30] $ — it is the minimum lexicographically among all subsequences of length $ 2 $ with the maximum total sum of items. Thus, the answer to the request $ k_j=2 $ , $ pos_j=1 $ is the number $ 20 $ , and the answer to the request $ k_j=2 $ , $ pos_j=2 $ is the number $ 30 $ .

## 说明/提示

In the first example, for $ a=[10,20,10] $ the optimal subsequences are:

- for $ k=1 $ : $ [20] $ ,
- for $ k=2 $ : $ [10,20] $ ,
- for $ k=3 $ : $ [10,20,10] $ .

## 样例 #1

### 输入

```
3
10 20 10
6
1 1
2 1
2 2
3 1
3 2
3 3
```

### 输出

```
20
10
20
10
20
10
```

## 样例 #2

### 输入

```
7
1 2 1 3 1 2 1
9
2 1
2 2
3 1
3 2
3 3
1 1
7 1
7 7
7 4
```

### 输出

```
2
3
2
3
2
3
1
1
3
```

# 题解

## 作者：HoshizoraZ (赞：5)

发现简单版本的 $n,m$ 都很小，因此我们可以考虑暴力做法。

不难想出一个贪心策略：将序列 $a$ **从大到小**排序，取前 $k$ 个数，那么选出的这 $k$ 个数组成的子序列一定**和最大**。证明过于简单这里就不写了。

不过这题的 $a$ 序列中可能存在值相同的元素，如何解决它们在原序列的分布问题十分关键。

一般地，设**从大到小**排序后的第 $k$ 个元素为 $x$。

那么原序列中所有**大于** $x$ 的元素**都一定**会被取到，所有**小于** $x$ 的元素**都不会**被取到。

而原序列中**等于** $x$ 的元素，是子序列中值最小的元素，可能**只取到一部分**。

这么一说，序列中不确定的元素只剩下**等于** $x$ 的元素了。

而题目说了第二关键字是**字典序**，所以 $x$ 作为子序列中最小的数，在子序列中的位置应该越前越好。

因此可以设计策略如下：

- 对于值大于原序列第 $k$ 大的元素，直接收入子序列；
- 对于值等于原序列第 $k$ 大的元素，优先挑靠前位置的，直到选满 $k$ 个数为止。

代码如下（$n,m \le 100$，随便怎么写都可以，这里为了简单就搞了个 `std::map`）：

```cpp
#include <bits/stdc++.h>
#define INF 1e9
#define eps 1e-6
typedef long long ll;
using namespace std;

map <int, int> M;
int n, m, a[110], b[110], seq[110], ss;
bool bb[110];

int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1);
	scanf("%d", &m);
	for(int i = 1, k, pos; i <= m; i++){
		scanf("%d%d", &k, &pos);
		for(int j = n; j >= n - k + 1; j--)		// 挑前 k 大
			M[b[j]]++;
		ss = 0;
		for(int j = 1; j <= n; j++)		// 放到原序列找
			if(M[a[j]] > 0)
				M[a[j]]--, seq[++ss] = a[j];
		printf("%d\n", seq[pos]);
	}

	return 0;
}
```

---

## 作者：Rex01 (赞：2)

## [CF1127D1 题目传送门](https://www.luogu.com.cn/problem/CF1227D1)

## 题目大意
给定长度为 $n$ 的整数序列 $a$，请你通过从序列中删除零个或多个元素得到最优子序列。给定非负整数 $k$，定义最优子序列为同时满足以下条件的子序列：

- 长度为 $k$，且元素的和是所有长度为 $k$ 的子序列中最大；
- 满足上述条件的所有长度为 $k$ 的子序列中，其字典序最小。

总共有 $m$ 个查询，每个查询给出两个数 $k$ 和 $p$，输出给定序列 $a$ 的最优子序列中索引为 $p$ 的值。

## 解决思路
注意到数据范围 $1 \leq n, m \leq 100$，直接想到了**暴力**。要使元素的和是所有长度为 $k$ 的子序列中最大的，就需要将数组从大到小排序，注意这里在代码中要写成 `sort(a + 1, a + n + 1)`，排完序后的前 $k$ 项为答案子序列的元素。接着把这些元素按初始序列顺序排序，其中的第 $p$ 项就是答案。

## 代码展示
```cpp
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int N = 110;
int n, a[N], m;
int b[N], d[N];
map <int, int> c;
//注意用map否则会超时

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);//减少输入速度
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		b[i] = a[i];//b数组是a数组的替代品
	}
	sort(a + 1, a + n + 1);
	cin >> m;
	for(int i = 1; i <= m; i++)
	{
		int k, p, sum = 0;
		cin >> k >> p;
		for(int j = n; j >= n - k + 1; j--) c[a[j]]++;
		for(int j = 1; j <= n; j++)
			if(c[b[j]] > 0)
			{
				c[b[j]]--;
				d[++sum] = b[j];
			}
		cout << d[p] << endl;
	}
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：2)

见招拆招。

看第一个约束：元素和最大的子序列。  
那一定是前 $k$ 大的元素构成的。  
但是由于元素可能相同，子序列不唯一。

自然看到了第二个约束：下标的字典序最小。  
我们记第 $k$ 大元素为 $c$。  
那么 $>c$ 的所有数，都是固定的。  
只需考虑 $=c$ 的所有数。  
那自然就是，将 $=c$ 的数下标小的先取。

复杂度 $\mathcal{O(m n\log n)}$。

细节看代码。

```cpp
const int N=2e5+3;
int n,m;
struct wt{int x,y;}a[N],b[N];
void Solve()
{
	rd(n);
	for(re int i=1;i<=n;++i) rd(a[i].x),a[i].y=i;
	std::sort(a+1,a+n+1,[](re wt x,re wt y){return x.x==y.x?x.y<y.y:x.x>y.x;});
	rd(m);
	for(re int k,pos;m--;)
	{
		rd(k),rd(pos);
		for(re int i=1;i<=k;++i) b[i]=a[i];
		std::sort(b+1,b+k+1,[](re wt x,re wt y){return x.y<y.y;});
		prt(b[pos].x,'\n');
	}
	return;
}
```
[$\color{green}{\checkmark}$](https://codeforces.com/contest/1227/submission/205774840)。

---

## 作者：alan1118 (赞：1)

我愿称这道题为史上最水 *1600 之一。

## 题意
给你一个 $n$ 个数的序列，请你求出一个长度为 $k$，和最大的情况下字典序最小的子序列。问这个子序列的第 $p$ 项是多少？

## 思路

首先最让我惊讶的一件事：时间限制 $3$ 秒。

那就好办了，直接暴力解决。

我的思路是把数组用结构体存，结构体中存两个数：值（$num$）和序号（$id$）。

接着先按 $num$ 排一遍序，前 $k$ 个就是最优子序列，但要注意还要满足字典序最小，这里可以看我代码，就不过多解释了。

然后把这 $k$ 个数按 $id$ 排一遍序，在输出第 $p$ 个就完事儿了。

## Code
``` cpp
#include <iostream>
#include <algorithm>
using namespace std;
 
struct Node
{
	int num, id;
} a[105];
 
bool cmp1(Node a, Node b)
{
	if(a.num != b.num) return a.num > b.num; 
    return a.id < b.id; // 没有这个会 WA 在第 10 个点
}
 
bool cmp2(Node a, Node b)
{
	return a.id < b.id;
}
 
int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i].num, a[i].id = i;
	int m;
	cin >> m;
	while(m--)
	{
		sort(a+1, a+n+1, cmp1);
		int k, p;
		cin >> k >> p;
		sort(a+1, a+k+1, cmp2);
		cout << a[p].num << endl;
	}
	return 0;
}
```

---

## 作者：OIerZhang (赞：1)

# [CF1227D1 Optimal Subsequences (Easy Version)](https://www.luogu.com.cn/problem/CF1227D1)

[加强版传送门](https://www.luogu.com.cn/problem/CF1227D2)

## 思路

这道题数据很小，考虑暴力做法。

要使元素的和是所有长度为 $k$ 的子序列中最大的，我们其实可以将数组从大到小排序，排完序后的前 $k$ 项为答案子序列的元素。

我们再把它们按初始序列顺序排序，其中的第 $pos$ 项就是答案。

但是有一个坑点：答案子序列中，其字典序最小。这样，我们可以在排序时记录每个元素的下标，当两个元素一样时，下标小的靠前。

## 核心代码

sort 比较函数：

```cpp
bool cmp(node x, node y)
{
    if (x.x == y.x)
        return x.id < y.id; // 两个元素一样，下标小的靠前
    return x.x > y.x;
}
```

核心：

```cpp
for (int i = 1; i <= k; i++)
    t[i] = a[i];
sort(t + 1, t + 1 + k, cmp2);
cout << t[p].x << endl;
```

---

## 作者：Bai_R_X (赞：1)

## 思路
这道题为了子序列的和最大，我们必须使其全部元素都大于等于（可能有相同元素）剩下的元素。

然后还有一个细节，子序列在原数组中位置是严格递增的，所以我们输出时要按位置排序。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,m,p,i;
pair<int,int> a[105],b[105];
bool cmp(pair<int,int> x,pair<int,int> y)
{
	if(x.first!=y.first)return x.first>y.first;
	return x.second<y.second;
}
signed main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i].first;
		a[i].second=i;
	}
	sort(a+1,a+n+1,cmp);
	cin>>m;
	while(m--)
	{
		cin>>k>>p;
		for(i=1;i<=k;i++)
		{
			b[i].first=a[i].second;
			b[i].second=a[i].first;
		}
		sort(b+1,b+k+1);
		cout<<b[p].second<<endl;
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF1227D1 Optimal Subsequences (Hard Version) *1600](https://www.luogu.com.cn/problem/CF1227D1)

[CF1227D2 Optimal Subsequences (Hard Version) *1800](https://www.luogu.com.cn/problem/CF1227D2)

# 解题思路

本篇题解分 D1，D2 两个部分来写。

## D1 sol：

我们容易发现有以下两点性质：

- 要想子序列和**最大**，必须选择前 $k$ 大的数字。

- 比第 $k$ 大的数字还要大的数字是必须取的。

然后容易发现，我们能改变序列的差异只能是改变所有值为第 $k$ 大的数的选取情况。

那么显然，选取最前面的数是最优的。

直接暴力选取即可，时间复杂度 $O(nm + n \log n)$。

## D2 sol：

根据 D1 的思路，我们需要优化掉这个暴力。

考虑将询问离线，并按照查询的序列长度从小到大进行排序。

这样我们就只需要维护加数操作和目前加的数字有几个值为第 $k$ 大的数字即可。

加数操作和查询操作我们可以使用优先队列和树状数组维护。

时间复杂度 $O(m \log^2 n)$。

# 参考代码

## D1 code：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
#define bug cout<<"---------------------------------------\n";
ll _t_;
void _clear(){}
ll n,q;
ll a[100010],b[100010];
ll k;
map<ll,ll>mp,mp2;
bool cmp(ll x,ll y){
	return x>y;
}
void solve()
{
    _clear();
	cin>>n;
	forl(i,1,n)
		cin>>a[i],mp[a[i]]=1;
	for(auto i:mp)
		mp2[i.x]=++k;
	for(auto i:mp2)
		mp[i.y]=i.x;
	forl(i,1,n)
		a[i]=mp2[a[i]],b[i]=a[i];
	sort(b+1,b+1+n,cmp);
	cin>>q;
	while(q--)
	{
		ll x,y;
		cin>>x>>y;
		ll sum=0,num=b[x];
		ll last=0,L=x;
		while(b[L]==num)
			L--,last++;
		forl(i,1,n)
		{
			sum+=a[i]>num;
			if(a[i]==num && last)
				last--,sum++;
			if(sum==y)
			{
				cout<<mp[a[i]]<<endl;
				break;
			}
		}
	}
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
 //   cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

## D2 code：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<pii>
#define minqueue priority_queue<pii,vector<pii>,greater<pii>>
#define bug cout<<"---------------------------------------\n";
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
ll n,Q;
ll a[1000010],b[1000010];
ll k;
map<ll,ll>mp,mp2;
bool cmp(ll x,ll y){
	return x>y;
}
struct node{
	ll x,y,id;
}q[1000010];
bool pmc(node x,node y){
	return x.x<y.x;
}
maxqueue qu;
ll ans[1000010];
ll tree[1000010];
ll qwq[1000010];
void add(ll x,ll y){
	for(;x<=2e5+5;x+=lowbit(x))
		tree[x]+=y;
}
ll query(ll x)
{
	ll sum=0;
	for(;x;x-=lowbit(x))
		sum+=tree[x];
	return sum;
}
void solve()
{
    _clear();
	cin>>n;
	forl(i,1,n)
		cin>>a[i],mp[a[i]]=1;
	for(auto i:mp)
		mp2[i.x]=++k;
	for(auto i:mp2)
		mp[i.y]=i.x;
	forl(i,1,n)
		a[i]=mp2[a[i]],b[i]=a[i];
	sort(b+1,b+1+n,cmp);
	forl(i,1,n)
		qu.push({a[i],-i});
	cin>>Q;
	forl(i,1,Q)
		cin>>q[i].x>>q[i].y,q[i].id=i;
	sort(q+1,q+1+Q,pmc);
	ll sz=0;
	forl(i,1,Q)
	{
		while(sz<q[i].x)
		{
			pii now=qu.top();
			qu.pop();
			add(-now.y,1);
		//	add(-now.y+1,-1);
			sz++;
		}
		ll L=1,R=n;
		while(L<R)
		{
			ll Mid=(L+R)/2;
			if(query(Mid)<q[i].y)
				L=Mid+1;
			else
				R=Mid;
		}
		ans[q[i].id]=mp[a[L]];
		qwq[q[i].id]=L;
	}
	forl(i,1,Q)
//		cout<<qwq[i]<<':',
		cout<<ans[i]<<endl;
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
 //   cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：xuan_gong_dong (赞：1)

发现题解区都是 $O(n^2 \log{n})$？那我就写一篇不一样的吧。

## 题面
[Optimal Subsequences (Easy Version)](https://www.luogu.com.cn/problem/CF1227D1)
## 分析
- 首先为了满足第一个要求：直接初始排序一遍，然后去最大的前 $k$ 个就好了。
- 那对于第二个情况：排序后值大于 $a_k$ 的一定必须取完（不然就满足不了第一个要求了），等于 $a_k$ 就不一定取完了，要去前面需要用的几个，这样才能保证字典序最小。

直接暴力查整个初始数组就好了，复杂度为 $O(n^2)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[201100],b[201100];
int n,m;
bool cmp(int tx,int ty)
{
	return tx>ty;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	scanf("%d",&m);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=m;i++)
	{
		int k,pos;
		scanf("%d%d",&k,&pos);
		int tmp=k;
		while(a[tmp]==a[tmp-1])tmp--;
		tmp=k-tmp+1;
		int id=1;
		for(int j=1;j<=pos;j++)
		{
			while(b[id]<a[k]||(b[id]==a[k]&&tmp==0))id++;
			if(b[id]==a[k])tmp--;
			id++;
		}
		printf("%d\n",b[id-1]);
	}
	return 0;
}
```


---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1227D1)

## 思路
对于每次询问，可以发现由前 $k$ 大的 $k$ 个数组成的子序列的和一定是所有长度为 $k$ 的子序列中最大的之一，而又因为要求字典序最小，所以要按字典序为第二关键字排序（这样可以保证同样大的数之中一定是靠前的会被优先选中）。然后再把前 $k$ 大的数按照字典序排序，输出即可。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

struct Num {
    int val, idx;

    bool operator< (Num x) const {
        if (val != x.val) return val > x.val;
        return idx < x.idx;
    }
};
const int maxn = 1e2 + 10;

int n;
int a[maxn];
int m;
    int k, p;

Num num[maxn];

void work_m () {
    sort(num + 1, num + n + 1);

    scanf("%i%i", &k, &p);

    sort(num + 1, num + k + 1, 
        [] (Num x, Num y) {
            return x.idx < y.idx;
        }
    );
    
    printf("%i\n", num[p].val);
}
int main () {
    scanf ("%i", &n);
    FOR (1, n, i) {
        scanf("%i", &a[i]);

        num[i] = {a[i], i};
    }
    scanf("%i", &m);
    while (m--) {work_m();}
    return 0;
}
```

---

## 作者：longStone (赞：0)

# CF1227D1 Optimal Subsequences (Easy Version) 题解

## 思路

观察发现 $n , m$ 都很小，还给了 $3$ 秒的时间，可以直接暴力。

接下来看一下题目给的两个要求：

1. 长度为 $k$，且元素的和是所有长度为 $k$ 的子序列中最大。
2. 满足上述条件的所有长度为 $k$ 的子序列中，其字典序最小。

第一个要求可以将数组**从大到小**排序，取前 $k$ 大的数即可。

第二个要求是在数字有重复时发生的，为了让字典序最小，我们可以在排序时考虑这个数原来的编号，对于相同的数，**编号小的排前面，编号大的排后面**。

接着我们从前往后，按编号输出位置上的值。

## 代码

```c++
#include "bits/stdc++.h"
using namespace std;
int n, a[105], c[105][105], m, k, p;//a记录位置上的值，c记录长度为k的子序列每个位置上的编号
struct X
{
    int num, id;//将位置和数值放在一起
    bool operator <(X z)
    {
        if(num == z.num)	return id < z.id;//编号小的排前面
        return num > z.num;//从大到小排序
    }
}b[105];
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i];
        b[i].num = a[i];
        b[i].id = i;
    }
    sort(b + 1,b + n + 1);
    cin >> m;
    for(int i = 1;i <= m;i++)
    {
        cin >> k >> p;
        if(!c[k][0])
        {
            for(int j = 1;j <= k;j++)	c[k][j] = b[j].id;
            sort(c[k] + 1,c[k] + k + 1);
            c[k][0] = 1;
        }
        cout << a[c[k][p]] << '\n';
    }
    return 0;
}
```

---

## 作者：Novelist_ (赞：0)

由于 $n$ 和 $m$ 十分小，所以我们可以暴力模拟。首先，我们定义一个结构体数组 $a$。然后每次输入时将 $a$ 数组从大到小排序，再将 $a$ 的前 $k$ 个数按照字典序排序，最后输出 $a_{pos}$。

具体请看代码。

下面是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct k{
  int id,sum;
}a[102];
inline bool cmp1(const k x,const k y)
{
  return x.sum>y.sum;
}
inline bool cmp2(const k x,const k y)
{
  return x.id<y.id;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n,i,j,k,m,pos;
  cin>>n;
  for(i=1;i<=n;++i)
  cin>>a[i].sum,a[i].id=i;
  cin>>m;
  for(i=1;i<=m;++i)
  {
  	cin>>k>>pos;
  	sort(a+1,a+n+1,cmp1);//根据大小排序
  	sort(a+1,a+k+1,cmp2);//根据字典序排序
  	cout<<a[pos].sum<<'\n';
  }
  return 0;
}
```

---

## 作者：Novelist_ (赞：0)

本题数据非常小，所以我们可以直接暴力模拟。

首先我们需要求出和最大的子序列，我们只需贪心一下，找前 $k$ 个大的数，然后输出其中第 $pos$ 个数。

为了保持字典序，我们需要优先挑位置在前面的。

由于 $a$ 序列有点大，可以用映射。最好映射里不要用布尔。因为本蒟蒻错了。

我会放上我的正确代码和错误代码，请各位大佬斧正。

下面是正确代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,pos,i,j,t[102],a[102],ans[102],cut;
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin>>n;
  for(i=1;i<=n;++i)
  {
    cin>>a[i];
    t[i]=a[i];
  }
  cin>>m;
  sort(t+1,t+n+1);
  for(i=1;i<=m;++i)
  {
    map<int,int>b;
    cut=0;
    cin>>k>>pos;
    for(j=n-k+1;j<=n;++j)
    ++b[t[j]];
    for(j=1;j<=n&&cut<pos;++j)
    if(b[a[j]])
    --b[a[j]],ans[++cut]=a[j];
    cout<<ans[pos]<<'\n';
  }
  return 0;
}
```

下面是错误代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,pos,i,j,t[102],a[102],ans[102],cut;
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin>>n;
  for(i=1;i<=n;++i)
  {
    cin>>a[i];
    t[i]=a[i];
  }
  cin>>m;
  sort(t+1,t+n+1);
  for(i=1;i<=m;++i)
  {
    map<int,bool>b;
    cut=0;
    cin>>k>>pos;
    for(j=n-k+1;j<=n;++j)
    b[t[j]]=1;
    for(j=1;j<=n&&cut<pos;++j)
    if(b[a[j]])
    ans[++cut]=a[j];
    cout<<ans[pos]<<'\n';
  }
  return 0;
}
```

---

## 作者：The_jester_from_Lst (赞：0)

简易模拟题。

题目要求元素和最大，很显然我们只需一开始对原数组排序，取前 $k$ 个元素，一定是最大的。然而排序后元素的顺序会变，所以我们要把原数组记录下来，先取前 $k$ 个，把取了的元素记录到 $map$ 里，然后遍历原数组，每查到一个有记录的就把它加入 $ans$ 数组中，显然这样做也能满足字典序最小。最后输出 $ans_{pos}$ 即可。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define mod 722733748
using namespace std;
il int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
il void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
il int min(int x,int y){return (x<=y)?x:y;}
il int max(int x,int y){return (x>y)?x:y;}
const int JYAAKIOI=1145141919810;
int n,a[1086],m,b[1086],k,pos,ans[1086],s;
unordered_map<int,int>mp;
il bool cmp(int x,int y){
	return x>y;
}
signed main(){
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd(),b[i]=a[i];
	sort(b+1,b+1+n,cmp);
	m=rd();
	while(m--){
		s=0;
		k=rd(),pos=rd();
		for(int i=1;i<=k;++i)++mp[b[i]];
		for(int i=1;i<=n;++i){
			if(mp[a[i]]){
				--mp[a[i]];
				ans[++s]=a[i];
			}
		}
		wr(ans[pos]),putchar('\n');
	}
	return 0;
}
```

---

