# Voting (Hard Version)

## 题目描述

The only difference between easy and hard versions is constraints.

Now elections are held in Berland and you want to win them. More precisely, you want everyone to vote for you.

There are $ n $ voters, and two ways to convince each of them to vote for you. The first way to convince the $ i $ -th voter is to pay him $ p_i $ coins. The second way is to make $ m_i $ other voters vote for you, and the $ i $ -th voter will vote for free.

Moreover, the process of such voting takes place in several steps. For example, if there are five voters with $ m_1 = 1 $ , $ m_2 = 2 $ , $ m_3 = 2 $ , $ m_4 = 4 $ , $ m_5 = 5 $ , then you can buy the vote of the fifth voter, and eventually everyone will vote for you. Set of people voting for you will change as follows: $ {5} \rightarrow {1, 5} \rightarrow {1, 2, 3, 5} \rightarrow {1, 2, 3, 4, 5} $ .

Calculate the minimum number of coins you have to spend so that everyone votes for you.

## 说明/提示

In the first test case you have to buy vote of the third voter. Then the set of people voting for you will change as follows: $ {3} \rightarrow {1, 3} \rightarrow {1, 2, 3} $ .

In the second example you don't need to buy votes. The set of people voting for you will change as follows: $ {1} \rightarrow {1, 3, 5} \rightarrow {1, 2, 3, 5} \rightarrow {1, 2, 3, 5, 6, 7} \rightarrow {1, 2, 3, 4, 5, 6, 7} $ .

In the third test case you have to buy votes of the second and the fifth voters. Then the set of people voting for you will change as follows: $ {2, 5} \rightarrow {1, 2, 3, 4, 5} \rightarrow {1, 2, 3, 4, 5, 6} $ .

## 样例 #1

### 输入

```
3
3
1 5
2 10
2 8
7
0 1
3 1
1 1
6 1
1 1
4 1
4 1
6
2 6
2 3
2 8
2 7
4 4
5 5
```

### 输出

```
8
0
7
```

# 题解

## 作者：Chaigidel (赞：8)

按 $m$ 降序考虑

考虑所有 $m_i=x$ ，记 $m_i=x$ 的人数为 $s$，记 $m_i<x$ 的人数为 $p$

若 $p\ge x$ 可以直接继续考虑

若 $p < x$ 则需要在 $m_i>x$ 中买人，用 `multiset` 维护一下

按道理说应该要特殊考虑把 $m_i=x$ 一起买下来的特殊情况，但是不考虑也是对的 ~~存疑~~

设当前正在考虑 $m_i = x$ ，$m_i=x$ 的人数为 $s$ ，$m_i<x$ 的人数为 $p$

第一个 $m_i>x$，记 $y=m_i$，必然有 $p+s+cnt\ge y$

考虑 $x$ ， $need = x-p-cnt$

$s-need=s-x+p+cnt=y-x>0$

所以 $s>need$

所以不用考虑买全部 $m_i=x$



```cpp
std::vector<ll> v[N];

void solve(){
    int n; cin >> n;
    rep(i, 0, n) v[i].clear();
    rep(i, 1, n){
        ll m, p; cin >> m >> p; v[m].push_back(p);
    }
    std::multiset<ll> s;
    ll prev = n, cnt = 0, res = 0;
    per(i, n, 0){
        prev -= v[i].size();
        int need = i - prev - cnt;
        for(auto x : v[i]) s.insert(x);
        for(; need > 0; --need){
            ++cnt;
            res += *s.begin();
            s.erase(s.begin());
        }
    }
    cout << res << endl;
}
```


---

## 作者：fighter (赞：7)

~~搬运官方题解+添油加醋~~

这是一道巧妙的思维题。

我们最先可以想到按照m值对这些人进行分类，然后按m从大到小分别考虑。

对于一个当前的$m_i$，我们可以假设m值大于$m_i$的人都已经被说服了，并且其中有$cnt$ 个人是通过氪金收买的。同时，我们设m值小于$m_i$的人的数量为$pre$，由于最终m值比当前小的$pre$个人都会对当前这些人的选择产生影响，所以我们可以发现，此时共有$pre+cnt$个人对当前的选择产生了影响。

所以如果$pre+cnt>=m_i$，那么我们不需要氪金，这些人就会被说服。
如果$pre+cnt <m$，那么我们就需要通过氪金来增加$cnt$，使得这些人被说服。具体地，我们要维护一个堆，来存放所有m值大于等于$m_i$的人，我们从这些人中贪心选取最小代价即可。

```cpp
#include <bits/stdc++.h>
#define MAX 200005
#define ll long long
using namespace std;

int n, m[MAX];
ll p[MAX];
vector<int> v[MAX];

void solve(){
    priority_queue<ll, vector<ll>, greater<ll> > s;
    int pre = n, cnt = 0;
    ll ans = 0;
    for(int i = n-1; i >= 0; i--){
        pre -= v[i].size();
        for(int j = 0; j < v[i].size(); j++){
            s.push(v[i][j]);
        }
        int x = i-pre;
        while(cnt < x){
            ans += s.top();
            s.pop();
            cnt++;
        }
    }
    cout << ans << endl;
}

int main()
{
    int T;
    cin >> T;
    while(T--){
        scanf("%d", &n);
        for(int i = 0; i < n; i++) v[i].clear();
        for(int i = 1; i <= n; i++){
            scanf("%d%lld", &m[i], &p[i]);
            v[m[i]].push_back(p[i]);
        }
        solve();
    }

	return 0;
}
```

---

## 作者：xukuan (赞：6)

这题有点难想

首先看数据范围，$n \leq 2*10^5$，要么贪心+递推要么dp

这里显然不能用线性dp，因为线性dp不满足无后效性

那么我们考虑贪心+递推

这题要让**所有人**给你投票

所以是**对难以跟风的进行贿赂，让容易跟风的跟风**

我们对所有选民根据需要他跟风的人数把贿赂他们所要的钱放到一个vector里（pascal党请自行手写指针），然后按vector从大到小遍历：

先把vector里所有的元素推进一个小根堆里面

然后如果当前的总数不能让他们跟风，贿赂要钱最少的，直到能让他们跟风或贿赂完了为止

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=200010;
ll n,ans;
vector<ll> people[N];
priority_queue<ll,vector<ll>,greater<ll> > q;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

int main(){
	for(ll T=read(); T; T--){
		n=read();
		for(ll i=0; i<=n; i++) people[i].clear();
		for(ll i=1; i<=n; i++){
			ll x=read(),y=read();
			people[x].push_back(y);
		}
		ans=0; while(!q.empty()) q.pop();
		for(ll i=n-1; i>=0; i--){
			for(ll j=0; j<(ll)people[i].size(); j++) q.push(people[i][j]);
			while(q.size()>n-i){
				ans+=q.top();
				q.pop();
			}	
		}
		write(ans); putchar('\n');
	}
	return 0;
}
```

---

## 作者：Schwarzkopf_Henkal (赞：5)

这题……很有意思(

观察题目之后我们有几个结论：

1. 如果决定好了要氪哪几个人的金，那么在什么时候买，什么顺序买的结果是一样的。当然一开始就买掉最方便。

2. 如果我们把所有选民按$m$排序的话，当你在处理指定$m_i$的选民的时候，$m$小于$m_i$的选民都被或收买或跟风掉了（或者他们**应该**被或氪金或跟风掉了，具体是跟风还是氪金不重要。）。

3. 在处理指定$m_i$的选民的时候，由于我们要所有选民都为你投票，那么我们需要下面两种操作中的一种，氪他们所有人或者让人数多到足以让他们跟风。可以直接取min或者证明一下为什么氪所有人是多余的（略）~~我有一个伪证，还是不贴出来了~~。

遍历所有$m_i$的选民，发现在小于的全部投了的之后，如果不能满足他们的需求，我们需要在大于等于$m_i$的选民中抽出几个具有最小的$q$的选民来补充，注意现在我们已经省略了氪掉所有人的操作。并且，抽过的不能再抽。

具体实现：我原本有一个很丑的代码，但是感觉正常人想起来应该会方便一点点，现在不见了。可以把所有选民丢进$m$做下标的vector里，码起来方便，而且反正$m < n$，也可以不丢。抽出最小的，可以用堆，如果从n开始遍历的话可以顺序把元素推进堆里面，要方便一些。正序倒序是随意的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,tot;
vector<int>w[200005];
multiset<int>mts;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        mts.clear();
        for(int i=0;i<=n;i++)
            w[i].clear();
        for(int i=1,x,y;i<=n;i++){
            cin>>x>>y;
            w[x].push_back(y);
        }
        tot=0;
        for(int i=0;i<=n;i++)
            tot+=w[i].size();
        int cur=0;
        long long ans=0;
        for(int i=n;i>=0;i--){
            tot-=w[i].size();
            for(int j=0;j<w[i].size();j++)
                mts.insert(w[i][j]);
            int need=i-tot;
            while(cur<need){
                ans+=*mts.begin();
                mts.erase(mts.begin());
                cur++;
            }
        }
        cout<<ans<<'\n';
    }
}
```
I'm Schwarzkopf Henkal.

---

## 作者：晴空一鹤 (赞：4)

## Solution

贪心题，关键在于要敢猜结论。设 $q_i$ 为第 $i$ 个人最后拉票的顺序。

首先发现和那个限定时间完成作业，每个作业未完成有不同惩罚的题很像，唯一不同的是这里不需花费的条件是 $q_i>m_i$（即把第 $i$ 个人安排到第 $m_i$ 个人之后）。

于是就有一个类似的结论：尽量先安排花费大的，把他安排到当前 $m_i$ 后第一个空余的位置，如果没空位置了就为其付出代价。

为什么是对的？可以由微调法证，假设当前某人因为位置满了而要为其付出代价，由贪心顺序可知，前面占了位置的一定付出代价都不小于他，交换后一定不会更优。

注意到此题 $n\le2\times 10^5$，因此要做一点小优化，我们可以用并查集维护每个位置后第一个空位置，这个空位置被占了后，把其左边位置的祖先合并到右边位置即可。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int f[500005],n,ans,tt;
struct no{
    int l,r;
    friend bool operator<(no a,no b){
    return a.l>b.l;
    }
}t[200005];
int inline find(int x){
     if(f[x]==x)
     return x;
     return f[x]=find(f[x]);
}
void inline hb(int x,int y){
  f[find(x)]=find(y);
}
void inline slove(){
ans=0;
    cin>>n;
    for(int i=0;i<n;i++)
    f[i]=i,cin>>t[i+1].r>>t[i+1].l;
    for(int i=n;i<=2*n;i++)
    f[i]=i;
    sort(t+1,t+n+1);
    for(int i=1;i<=n;i++){
    if(find(t[i].r)<n&&t[i].r!=n)
    hb(find(t[i].r),find(t[i].r)+1);
    else
    ans+=t[i].l;
    }
    cout<<ans<<endl;
}
signed main(){
    cin>>tt;
    while(tt--)slove();
}
```

---

## 作者：guodong (赞：4)

[1251E2 - Voting (Hard Version) 2400](https://codeforces.com/contest/1251/problem/E2)：一直在纠结可以买自己的情况…… 然而根本就不用担心这个。

[在我的博客里阅读](http://101.34.155.150/2021/10/25/%e6%9d%bf%e5%88%b7-cf-%e8%ae%a1%e5%88%92/)
> 容易发现你可以选后面前 $k$ 个点或者是选自己的点，但是很多题解都不说为什么**直接选 $k$ 个点就是正确的**，或者是含糊带过，这里带来一个简洁的证明。

证明一下不用选自己所有点的情况。

按照 $m$ 倒序考虑所有点，我们当前在考虑 $m_i$ 的点集，一共有 $cnt$ 个点，在前面的过程中，我们买了 $k$ 个 $>m_i$ 的点。一共有 $pre$  个点比 $m_i$ 小。



  发现 $\texttt {std::upper\_bound}(m_i)$ 的点已经满足条件了，我们有 
  $$pre+k+cnt>m_i$$ 
  设当前需要的点数为 $need$ , 有
  $$need+k+pre=m_i$$ 
  联立两式有 
  $$cnt>need$$ 
  也就是说把当前点买光不是最优解，买前 $need$ 大的才是。
 
代码写起来很容易。
```cpp
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <queue>
#define For(i,a,b) for(int i = (int)(a);i <= (int)(b); ++i)
using namespace std;
const int N = 1002000;
priority_queue<int,vector<int>,greater<int> > Q;
vector<int> V[N];
signed main()
{
#ifdef NICEGUODONG
	freopen("data.in","r",stdin);
#endif
	int T;scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		For(i,1,n) V[i].clear();
		For(i,1,n){
			int m,s;
			scanf("%d%d",&m,&s);
			V[m].push_back(s);
		}
		long long ans = 0;
		int cnt = 0;
		int pre = n;
		while(!Q.empty()) Q.pop();
		for(int i = n - 1; i >= 1; --i){
			pre -= V[i].size();
			int need = i - pre;
			for(auto v : V[i]) 
				Q.push(v);
			while(cnt < need){
				++cnt;
				ans += Q.top();
				Q.pop();
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：w33z8kqrqk8zzzx33 (赞：4)

居然没有人用这个方法写吗（

考虑到最小化选择了的代价等于最大化未选择了的代价。

假设选择了 $k$ 位人，没选择的跟风值分别为 $x_1,x_2,\dots,x_{n-k}$，其中 $x_i\le x_{i+1}$，则 $\forall i:[x_1,x_2,\dots,x_{n-k}]_i\le[k,k+1,\dots,n-1]_i$。

这等价于 $[0,0,\dots,0,x_1,x_2,\dots,x_{n-k}]\le[0,1,\dots,n-1]$，其中 $\le$ 为按位小于等于。注意 $0$ 没必要钦定在最前面，只需要作为一个窟窿的意义。

于是我们可以贪心从 $0$ 遍历至 $n-1$，每一次尝试放最贵的人到这个位置上使得他跟风值小于等于当前遍历值。如果没有，则设为窟窿。

这一步可以直接用 priority queue 模拟，答案为堆里剩余价值之和。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)

pair<int,int> xd[200005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t;cin>>t;
	while(t--) {
		int n;cin>>n;
		rep(i, n)
			cin>>xd[i].first>>xd[i].second;
		sort(xd, xd+n);
		xd[n].first = 1e9; int c=0;
		priority_queue<int> z;
		rep(i, n) {
			while(xd[c].first == i) z.push(xd[c++].second);
			if(z.size()) z.pop();
		}
		long long sm=0;
		while(z.size()) sm+=z.top(),z.pop();
		cout<<sm<<endl;
	}
}

```

---

## 作者：Little09 (赞：2)

稍微记录一下我的思路吧。

首先按照 $m$ 排序。肯定是先选定要买一些人，剩下的人按照顺序决定过去。一个人合法的条件是他前面人的个数 $+$ 他后面买了的人的个数 $\ge m$。第 $i$ 个人前面有 $i-1$ 个人，所以条件变成第 $i$ 个人要么后面买了至少 $m_i-(i-1)$ 个人，要么买了第 $i$ 个人。

对这个做一个 $O(n^2)$ 的 DP 就可以过 E1 了，但是对这个 DP 找不到什么优化的地方，也难用数据结构处理。

我们设 $b_i=m_i-(i-1)$。定义 $c_i=\max_{j=i}^n b_j$。容易发现由于 $m$ 已经排过序了，所以 $b_i\le \max_{j=i+1}^n b_j+1=c_{i+1}+1$。根据这个我们可以证明这个结论：

- 倒着考虑到第 $i$ 个人的时候，一定在 $[i,n]$ 中选了至少 $c_i$ 个人。

归纳这个东西。$i=n$ 显然成立。$i<n$ 时由于 $[i+1,n]$ 均成立，所以在 $[i+1,n]$ 中选了至少 $c_{i+1}$ 个人。如果不选第 $i$ 个，那么在 $[i,n]$ 中已经至少选了 $b_i$ 个，而 $[i+1,n]$ 中又至少选了 $c_{i+1}$ 个，所以显然满足；如果选第 $i$ 个人，那么至少选了 $c_{i+1}+1$ 个人，所以也满足大于等于 $b_i$。

所以这是个充要条件。也就是说，倒着做到第 $i$ 个人的时候，只要满足在 $[i,n]$ 中选了至少 $c_i$ 个人就行了。用堆维护即可。

---

## 作者：kkio (赞：2)

越往后的就越容易超过 $ m $。

显然的贪心策略：能让大的往后的就往后放，不然就给别人让位。从 $ m $ 大到小考虑，相同 $ m $ 的先把 $ p $ 大的放后面，如果已经不能超过 $ m $ 了，那么就放前面。

然后你就可以轻松的切掉这道题啦(

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
int n;
vector<int> s[maxn];
void solve()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		int m,p;
		scanf("%lld%lld",&m,&p);
		s[m].push_back(p);	
	}
	int ans=0,tot=n;
	for(int i=n-1;i>=0;i--)
	{
		sort(s[i].begin(),s[i].end());
		while(!s.empty())
		{
			if(tot<=i)ans+=s[i].back();
			else tot--;
			s[i].pop_back();
		}
	}
	printf("%lld\n",ans);
}
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)solve();
}
```


但是这个贪心是错的，因为从大到小考虑可能会使小的 $ m $ 失去被放的机会。这个时候贪心就会忽略掉 $ m $ 小的，但是将 $ m $ 大的换成 $ m $ 小的可能使答案更优。

那么就用反悔贪心，用反悔堆存下之前放在后面的值，如果当前的堆顶比现在的 $ p $ 小的话，那么将这个换掉一定更优，将堆顶弹出，计算贡献。

代码实现几乎没有什么要注意的，照做就好了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
int n;
priority_queue< int,vector<int>,greater<int> > q;
vector<int> s[maxn];
void solve()
{
	scanf("%lld",&n);
	while(!q.empty())q.pop();
	for(int i=1;i<=n;i++)
	{
		int m,p;
		scanf("%lld%lld",&m,&p);
		s[m].push_back(p);	
	}
	int ans=0;
	for(int i=n-1;i>=0;i--)
	{
		sort(s[i].begin(),s[i].end());
		while(!s[i].empty())
		{
			int x=s[i].back();
			s[i].pop_back();
			if(q.size()&&n-q.size()<=i)
			{
				if(q.top()<x)ans+=q.top(),q.pop(),q.push(x);
				else ans+=x;
			}
			else 
				q.push(x);
		}
	}
	printf("%lld\n",ans);
}
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)solve();
}
```


---

## 作者：thjkhdf12 (赞：2)

本题思考很有难度，首先将所有选民按跟风值排好序（代码中直接用vector数组省去了这个排序的步骤），然后从后往前遍历，遍历时先把当前跟风值的选民的所有贿赂值加入小根堆中，如果当前跟风的人数大于$n-i$即跟风的人数已经超过了应有的跟风人数（堆中的人表示认为这些人已经跟风了，所以堆的大小就是当前的跟风人数）举个例子，样例输入中第三个样例当扫到$2$时，堆中有$6$个数字，认为这$6$个人都已经跟风了但当前的跟风值却是$2$，代表这$6$个人中应该有两个人目前还不应该跟风，那么就从小根堆的堆顶弹出最小的贿赂值去贿赂他们，使人数达到标准（如果不懂可以看一下代码的注释）

处理时倒着扫时认为前面的人都已经投票给你，而是贿赂还是跟风等之后扫到再行处理

```cpp
#include<iostream>
#include<queue>
using namespace std;

#define mfor(i,a,b) for(register int i=(a);i<=(b);i++)
#define mrep(i,a,b) for(register int i=(a);i>=(b);i--)
#define LLL __int128
#define Re register
typedef long long int LL;
const int INF = 0x3f3f3f3f;
const long long int INFLL = 0x3f3f3f3f3f3f3f3f;

const int maxn = 300010;

int T;
int n;
vector<int>g[maxn];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--)
    {
        priority_queue<int, vector<int>, greater<int>>heap;
        cin >> n;
        mfor(i, 0, n)
        {
            g[i].clear();
        }
        mfor(i, 1, n)
        {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
        }
        LL ans = 0;
        mrep(i, n - 1, 0)
        {
            mfor(j, 0, (int)g[i].size() - 1)//强转成signed int防止size是0出错
            {
                heap.push(g[i][j]);
                //认为这些人都跟风了
            }
            while (heap.size() > n - i)	//如果跟风人数比n减去当前扫到的跟风值人还多，说明无法让这些人全部跟风
            {
                ans += heap.top();	//从中贿赂贿赂值最小的人
                heap.pop();
            }
        }
        cout << ans << endl;
    }
    return 0;
}

---

## 作者：Comentropy (赞：1)

## 分析

### Part 1 直觉
首先给出一种解题时的推测（本能反应）：先按需求排序，然后尽可能选择代价小的。

上述方法错误。因为可能存在选代价大的就可以获得很多人的选票的情况，如下方数据。
```
input:
3
0 6
2 7
3 8

output:
8
```


### Part 2 分析
于是观察题意，如果正向难处理就反着来吧。从需求量最大的人（见 ```ps1```）开始处理。

首先在能接受的情况下尽可能接受。当不可接受时，即 $ need > n - p $（$p$ 为当前已接受人数） 时，再考虑购买的事情（见 ```ps2```）。此时选择收买代价最小的人即可。

如此操作，记录每次操作后的最多省下的钱即可。

### 证明 & 说明

```ps1```: 此处说明：若一个人此时不能免费，此后一定也不能免费取得，因为需求量是单调下降的，并满足：$ need > n - p $， 故只需倒序考虑。

```ps2```: 此处说明：由 ```ps1``` 可知其正确性，此步考虑的代价最小可通过 ```priority_queue``` 或 ```set``` 维护。求答案时需要开 ```long long```。

另外，本题有双倍经验，但是要对代码略作修改 [P6346 [CCO2017] 专业网络](https://www.luogu.com.cn/problem/P6346) 。

## Code

解题的函数代码如下。

```cpp

typedef long long LL;
typedef pair<LL,LL> PII;
PII a[N];

void solve(){
    priority_queue<int,vector<int>,greater<int> >q ;
    LL sum=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].first,&a[i].second);
        sum+=a[i].second;
        // first is need. second is value.
    }
    sort(a+1,a+1+n);
    LL f=0,res=0;
    for(int i=n;i>=1;i--){
        f+=a[i].second;
        q.push(a[i].second);
        if(a[i].first>n-q.size()){
            f-=q.top();
            q.pop();
        }
        res=std::max(res,f);
    }
    printf("%lld\n",sum-res);
    return ;
}

```


---

## 作者：elbissoPtImaerD (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P6346)，下文记 $m$ 为 $a$，$p$ 为 $b$。

最优策略一定是先把所有要代价的朋友交完，然后剩下的全部不花费代价。

那么只需考虑给定不花费代价的项目判断合法。

按 $a_i$ 从大到小排序，显然有需要满足第 $i$ 个不花费代价的朋友 $x$ 要 $a_x \le n-i$。

直接贪心，维护不花费代价的朋友集合即可。

```cpp
void Solve() {
  int n; cin>>n;
  LL s=0;
  ve<pii>a(n); for(auto&[x,y]:a) cin>>x>>y,s+=y;
  sort(rll(a));
  multiset<int>S;
  for(auto[x,y]:a) {
    S.ep(y);
    if(n-Sz(S)<x) S.erase(begin(S));
  }
  cout<<(s-accumulate(all(S),0LL))<<'\n';
  return;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

首先显然如果我们钦定了对于每个人 $i$ 是贿赂还是让他跟风，则先贿赂谁后贿赂谁是不影响答案的。

显然跟风的过程是 $m$ 升序去跟的。我们直接排序先。

那么我们就可以考虑到一个事实，如果 $i$ 是跟风的，那么 $1\sim i-1$ 必然已经被跟掉了。

然而如果前面的不够让他跟风呢？我们在 $m$ 大于当前值的人中寻找一些花费最小的，也就是目前不知道是不是跟风的，贿赂一些，使得可以把目前的跟风掉即可。

如何实现呢？我们 $m$ 从大往小处理，这样前面跟风的改成贿赂就不会算重了。记录目前已经贿赂的人数即可。至于找花费最小的，可以使用 `std::multiset` 维护。具体可以看看代码。

```cpp
#include <bits/stdc++.h>
#define m first
#define p second
using namespace std;
#define clr() fflush(stdout);
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
const int N=5e5+5;
vector<int> e[N];
long long ret;
int i, n, pre, x, y, lft, now;
int main()
{
	int t; scanf("%d", &t);
    while(t--)
	{
        ret=0;
        rep(i, 0, n) e[i].clear();
        cin>>n;
        rep(i, 1, n)
		{
            cin>>x>>y;
            e[x].emplace_back(y);
        }
        multiset<int> q;
        pre=n; now=0;
        req(i, n, 0)
		{
            if(e[i].empty())continue;
            pre-=e[i].size();
            lft=i-pre-now;
            for(auto ins : e[i]) q.insert(ins);
            while(lft-->0)
			{
            	++now;
                ret+=*q.begin();// printf("%lld\n", ret);
                q.erase(q.begin());
            }
        }
        printf("%lld\n", ret);
    }
}
```

---

## 作者：出言不逊王子 (赞：0)

有一种最极端的方法，就是买下所有人，成本记为 $t$。

我们希望成本最小，所以我们希望省下的钱最多。

省下钱，很显然只能通过跟风的形式。

$m$ 很小的乌合之众很容易被吸引过来，所以我们优先考虑 $m$ 大的人。

我们现在处理 $m$ 从大到小第 $i$ 大的人。

我们假设通过跟风被吸引过来的人的集合是 $q$。我们假设他会跟风，所以 $i$ 一开始也在 $q$ 里面。

则最多有 $n-|q|$ 个人我们可以收买。**注意，$q$ 里面的人我们还不知道他是不是真的会投票，所以不计入**。

如果我们把剩下的所有人都收买了，但是他还是不跟风，怎么办？

- 花钱收买他。
- 现在花钱收买另一个人，从而让他跟风。

第二个操作是啥意思呢？

因为此时 $|q|$ 最多是 $i$。

假设 $m_i$ 非常高，那么让他跟风，本来就完全没戏。

那么这个操作就是在 $q$ 中选代价最大的，其他人继续出局，该收买的就乖乖收买。

假如 $m_i$ 比较小，那么他自己就直接被吞噬进去了。

可以手动模拟一下 [P6346](https://www.luogu.com.cn/problem/P6346) 的样例 $3$，能有更深的理解。

也可以手动模拟如下样例：

```
7
6 10
6 9
6 8
5 7
5 6
5 5
5 4
```

对于前三个人，$q$ 集合只养得起一个，所以就是在 $q$ 集合里打擂台。

对于后四个人，$q$ 集合能多养一个了，因为只要五个人被收买，就能有至少一个 $m=5$ 的人成功跟风。可是其他三个 $m=5$ 的人为了养起这个人，必须被收买。

否则大家都互相干瞪眼，没人投出第一张票。

那这三个 $m=5$ 的人是谁呢？肯定是 $p$ 值最小的。

所以用一个优先队列维护集合 $q$。

如果 $p_i$ 非常小，挪来挪去还不如直接买，那就不管了，直接收买 $p_i$ 完事。

记省下的钱是 $r$，答案就是 $t-r$。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define mid (l+r>>1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=200001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
struct per{
	int m,p;
}a[N];
bool cmp(per x,per y){return x.m<y.m;}
priority_queue<int,vector<int>,greater<int> > q;//q里面的表示我们认为他真的会投票的
//但是可能不会呢？那这样一来我们就只能买了
int n,m[N],p[N],tot,g,res;
void mian(){
	tot=g=res=0;
	n=read();fs(i,1,n,1) a[i].m=read(),a[i].p=read(),tot+=a[i].p;
	sort(a+1,a+n+1,cmp);while(!q.empty()) q.pop();
	ft(i,n,1,-1){//先找M大的，这意味着他们的抗打击能力最强 
		//很显然我们希望这些被保的最多
		g+=a[i].p;
		q.push(a[i].p);//我进去，我肯定也能保了
		//注意，此时“保”是我们期待的，但不一定是真的
		if(a[i].m>n-q.size()){//保了的以外的我们全买了，还不够？
			int t=q.top();q.pop();//不过还好欠的不多（顶天一个）
			//因为一个位置最多给你放一个进去，所以ai不会太大，也就是说换了以后它肯定能成功 
			g-=t;
		}
		res=max(res,g);//这次投票活动作废
	} 
	cout<<tot-res<<'\n';
}
signed main(){
	int t=read();while(t--) mian();
	return 0;
}

```

---

