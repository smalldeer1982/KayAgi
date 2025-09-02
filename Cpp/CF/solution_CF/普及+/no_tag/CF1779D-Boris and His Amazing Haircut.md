# Boris and His Amazing Haircut

## 题目描述

Boris thinks that chess is a tedious game. So he left his tournament early and went to a barber shop as his hair was a bit messy.

His current hair can be described by an array $ a_1,a_2,\ldots, a_n $ , where $ a_i $ is the height of the hair standing at position $ i $ . His desired haircut can be described by an array $ b_1,b_2,\ldots, b_n $ in a similar fashion.

The barber has $ m $ razors. Each has its own size and can be used at most once. In one operation, he chooses a razor and cuts a segment of Boris's hair. More formally, an operation is:

- Choose any razor which hasn't been used before, let its size be $ x $ ;
- Choose a segment $ [l,r] $ ( $ 1\leq l \leq r \leq n $ );
- Set $ a_i := \min (a_i,x) $ for each $ l\leq i \leq r $ ;

Notice that some razors might have equal sizes — the barber can choose some size $ x $ only as many times as the number of razors with size $ x $ .

He may perform as many operations as he wants, as long as any razor is used at most once and $ a_i = b_i $ for each $ 1 \leq i \leq n $ at the end. He does not have to use all razors.

Can you determine whether the barber can give Boris his desired haircut?

## 说明/提示

In the first test case, Boris's hair is initially $ [3,3,3] $ . Let us describe a sequence of $ 2 $ operations the barber can perform:

- The barber uses the razor with size $ 1 $ on the segment $ [2,2] $ ; hence Boris's hair becomes $ [3,1,3] $ .
- The barber uses the razor with size $ 2 $ on the segment $ [1,3] $ ; hence Boris's hair becomes $ [2,1,2] $ which is the desired haircut.

In the third test case, no operation has to be done since Boris's hair is already as desired.

In the fourth test case, no cuts will be able to increase the third element in $ [1,1,1] $ in a way that the array becomes $ [1,1,2] $ .

## 样例 #1

### 输入

```
7
3
3 3 3
2 1 2
2
1 2
6
3 4 4 6 3 4
3 1 2 3 2 3
3
3 2 3
10
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 9 10
10
1 2 3 4 5 6 7 8 9 10
3
1 1 1
1 1 2
12
4 2 4 3 1 5 6 3 5 6 2 1
13
7 9 4 5 3 3 3 6 8 10 3 2 5
5 3 1 5 3 2 2 5 8 5 1 1 5
8
1 5 3 5 4 2 3 1
13
7 9 4 5 3 3 3 6 8 10 3 2 5
5 3 1 5 3 2 2 5 8 5 1 1 5
7
1 5 3 4 2 3 1
3
19747843 2736467 938578397
2039844 2039844 2039844
1
2039844```

### 输出

```
YES
NO
YES
NO
YES
NO
YES```

# 题解

## 作者：xiaruize (赞：8)

**思路**

先排除存在 $a_i<b_i$ 的情况，这种情况一定为 `NO`

考虑对于每一个在 $b$ 中出现的数，求出至少需要几把这个高度的剪刀

对于高度 $h$ ，设当前考虑 $b_x=b_y=h$

当 $\max\limits^{y}_{i=x}b_i \leq h$ 时，显然 $b_x$ 与 $b_y$ 可以共用一个， 否则需要分开使用两个

可以使用 `ST表` 计算区间最大值  ~~当然你写线段树也没人拦着。。。~~

求出最小个数后检查是否足够即可

**Code**

```cpp
/*
    Name:
    Author: xiaruize
    Date:
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define repp(i, x, y) for (int i = x; i >= y; i--)
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int N = 2e5 + 10;

// bool st;
int t;
int n;
int a[N], b[N];
int m;
int c[N];
int f[N][22];
map<int, int> mp, cnt, sum;
// bool en;

void rmq_init()
{
    for (int i = 1; i <= n; i++)
        f[i][0] = b[i];
    int k = 20;
    for (int j = 1; j <= k; j++)
        for (int i = n; i >= 1; i--)
        {
            if (i + (1 << (j - 1)) <= n)
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
}

int rmq(int i, int j)
{
    int k = log2(j - i + 1);
    return max(f[i][k], f[j - (1 << k) + 1][k]);
}

void solve()
{
    mp.clear();
    cnt.clear();
    sum.clear();
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    rmq_init();
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> c[i];
        sum[c[i]]++;
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[i] < b[i])
        {
            NO;
            return;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == b[i])
            continue;
        if (!mp[b[i]])
            mp[b[i]] = i;
        else
        {
            int l = mp[b[i]];//上一个同样的值
            int x = rmq(l, i);//区间最大值
            if (x > b[i])//不能共用
                cnt[b[i]]++;
            mp[b[i]] = i;
        }
    }
    for (auto v : mp)
    {
        if (v.sec)
            cnt[v.fir]++;
    }//最后一段没有统计
    for (auto v : cnt)
    {
        if (sum[v.fir] < v.sec)
        {
            NO;
            return;
        }
    }
    YES;
}

signed main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // cerr<<(&en-&st)/1024.0/1024.0<<endl;
    // auto t_1=chrono::high_resolution_clock::now();
    cin >> t;
    while (t--)
        solve();
    // auto t_2=chrono::high_resolution_clock::now();
    // cout <<". Elapsed (ms): " << chrono::duration_cast<chrono::milliseconds>(t_2 - t_1).count() << endl;
    return 0;
}
```

---

## 作者：forgotmyhandle (赞：6)

## 题目
[CF1779D 题目传送门](/problem/CF1779D)

## 分析

应该让每一个 $x$ 覆盖尽量大的区间。

分析题目，可以知道对于每一个位置 $i$，有多少 $x > b[i]$ 覆盖了 $i$ 是不关键的，**关键是是否有一个 $x \leq b[i]$  是否覆盖了它。**

当位置 $i$ 被 $x < b[i]$ 覆盖，那这个位置会变成 $x$ 而不是 $b[i]$，就变不回来了，这是我们所不希望看到的。所以我们必须让 $x \ge b[i]$ 覆盖 $i$。这样，就得出 $x$ 不能覆盖 $i$ 的条件：$x < b[i]$。

有了上面的几个条件，我们就可以~~非常轻松的~~想出这题的解法：循环遍历每一个 $i$，同时整一个 set 用来存目前的所有正在用的操作 $x$。循环过程中，有以下两种情况：

1. 当前的 $b[i]$ 包含在 set 中，那就什么也不干，继续往下走；
2. 不包含，那就在所有还没用过的 $x$ 中找一个与 $b[i]$ 相等的 $x$，并将这个 $x$ 扔到 set 里，表示这个 $x$ 正在被用，同时将其从还没用过的 $x$ 中删掉。如果发现没有与 $b[i]$ 相等的 $x$ 没被用过，那就终止循环，答案为 NO。

在循环到某些位置 $i$ 时，由于 set 中有些 $x$ 会小于 $b[i]$，所以需要实时地把这些 $x$ 扔出去。因为一个操作的作用区间一定是连续的，所以如果这个 $x$ 在 $b[i]$ 这个地方不能用了，那这后面一定都不能用这一个 $x$。

附代码：
```cpp
#include <iostream>              // 懒得用 bits 的屑博主
#include <set>
using namespace std;
int a[200005], b[200005];        // 如题目，顾名思义
multiset<int> st, oks;           // st 用来存还没有没用过的 x，oks 用来存正在被用的 x
int main() {
    set<int>::iterator it;       // set 的迭代器，用来遍历 set / multiset，应该是一种指针
    int tc, n, m;                // n, m 如题意
    scanf("%d", &tc);
    while (tc--) {
        oks.clear();             // 初始化
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", b + i);
        }
        scanf("%d", &m);
        st.clear();             // 初始化
        int tmp;
        for (int i = 0; i < m; i++) {
            scanf("%d", &tmp);
            st.insert(tmp);     // 这个 x 还没有被用过
        }
        bool flag = true;       // 答案
        for (int i = 0; i < n; i++) {
            if (b[i] > a[i]) {
                flag = false;   // 由于操作不能把一个数变大，所以就有了这句话
                break;          // 直接退循环
            } else if (b[i] == a[i]) {
                while (!oks.empty() && *oks.begin() < b[i]) { // 因为 set 默认从小到大排序，所以如果有一个 x 不合要求，
                    oks.erase(oks.begin());                   // 那这个 x 一定排在前面（x 的不合规性满足单调性）
                }
            } else {
                while (!oks.empty() && *oks.begin() < b[i]) oks.erase(oks.begin()); // 同上
                if (oks.count(b[i]) == 0 && st.count(b[i]) >= 1) { // 没有与 b[i] 相同的 x 正在被用且还有与 b[i] 相同的 x 可以用
                    st.erase(st.find(b[i]));	// 注意！这里的 st 是可重集，直接用 st.erase(b[i]) 会把所有 b[i] 全删了，导致错误
                    oks.insert(b[i]);	// x 正在被用
                } else if (oks.count(b[i]) == 0 && st.count(b[i]) == 0) { //没有与 b[i] 相同的 x 可用了，答案为 NO
                    flag = false;
                    break;
                } //此处省略了刚才讨论的第一种情况
            }
        }
        cout << (flag ? "YES\n" : "NO\n"); // yee~~~
    }
    return 0;
}
```


## 本蒟蒻的第一篇题解 完结撒花！！！

---

## 作者：BFSDFS123 (赞：1)

注意到这道题只让你输出是否有解，所以我们只需要考虑做不到的时候有什么情况，判断后输出 NO 即可。

容易发现的做不到的情况有如下几个：

1. $a_i < b_i$
2. $x_i$ 中不存在 $b_i$ 且 $a_i \neq b_i$

我们发现，如果想让一个位置变成 $b_i$，那我们一定不能用小于 $b_i$ 的 $x_i$。

于是我们又发现，如果两个相等的 $b_i$ 之间，有一个大于这两个 $b_i$ 的数，那么我们一定不能用一个 $x_i$ 来覆盖他们两个，必须使用两个。

用这个思想，我们可以枚举每个值 $x$，然后找出满足所有 $b_i=x$ 的位置 $i$ 需要多少个等于 $b_i$ 的 $x_i$ 覆盖。如果需要的次数大于 $x_i$ 的次数，那么就无解。

其他的时候都有解。

具体实现方式可以用线段树来查找区间最大值

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define eps 1e-8
const int inf=0x3f3f3f3f;
const int Maxn=2e5+10;
int n,m;
int a[Maxn],b[Maxn];
int x[Maxn];
struct segtree{
	int maxx;
}t[Maxn<<2];
#define ls node<<1
#define rs node<<1|1
void pushup(int node)
{
	t[node].maxx=max(t[ls].maxx,t[rs].maxx);
}
void build(int node,int l,int r)
{
	if(l==r)
	{
		t[node].maxx=b[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(node);
}
int query(int node,int l,int r,int ql,int qr)
{
	if(ql<=l && r<=qr)
	{
		return t[node].maxx;
	}
	int mid=(l+r)>>1;
	int ans=0;
	if(ql<=mid)
	{
		ans=max(ans,query(ls,l,mid,ql,qr));
	}
	if(qr>mid)
	{
		ans=max(ans,query(rs,mid+1,r,ql,qr));
	}
	return ans;
}
int segbinsearch(int l,int r)
{
	int maxx=query(1,1,n,l,r);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		int res=query(1,1,n,l,mid);
		if(res==maxx)
		{
			return mid;
		}
		if(res<maxx)
		{
			r=mid+1;
		}else{
			l=mid-1;
		}
	}
}
map<int,vector<int> > mp2;
void work()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	scanf("%lld",&m);
	for(int i=1;i<=m;i++) scanf("%lld",&x[i]);
	map<int,int> mp;
	for(int i=1;i<=m;i++) mp[x[i]]++;
	for(int i=1;i<=n;i++)
	{
		if(mp[b[i]]==0 && a[i]!=b[i])
		{
			puts("NO");
			return ;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]<b[i])
		{
			puts("NO");
			return ;
		}
	}
	build(1,1,n);
	mp2.clear();
	for(int i=1;i<=n;i++)
	{
		if(a[i]==b[i]) continue;
		mp2[b[i]].push_back(i);
	}
	for(auto i:mp2)
	{
		int val=i.first;
		vector<int> tmp=i.second;
		int cnt=1;
		for(int i=0;i<tmp.size()-1;i++)
		{
			int mx=query(1,1,n,tmp[i],tmp[i+1]);
//			cout<<tmp[i]<<"->"<<tmp[i+1]<<":"<<mx<<endl;
			if(mx>val)
			{
				cnt++; 
			}
		}
//		cout<<val<<","<<cnt<<endl;
		if(cnt>mp[val])
		{
			puts("NO");
			return ;
		}
	}
	puts("YES");
}
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：苏联小渣 (赞：1)

~~纪念第一次 D 题被罚时罚到得分 750！~~

有几个小结论：

- 存在 $a_i<b_i$，一定无解。

- 存在 $a_i=b_i$，则不需要浪费操作次数。

剩余 $a_i>b_i$ 的，$a_i$ 其实没有用。发现一个区间 $[l,r]$ 对 $x$ 取 $\min$，如果 $i \in [l,r],b_i<x$，那么对它是不产生影响的。反过来，如果 $\exists i \in [l,r],b_i>x$，那对 $[l,r]$ 操作就是不合法的。所以考虑把 $b$ 离散化后倒序加点。用一个 vector 记录每一个 $b_i$ 出现的位置，对于枚举到一个数 $x$，设 $x$ 的所有位置从小到大排列为 $p_1,p_2,...$。流程如下：

- 首先令 $l=p_1$。

- 如果 $a_{p_i}=b_{p_i}$，则跳过；若树状数组上 $[l,p_i]$ 区间和不为 $0$，则需要的次数 $s \gets s+1$，$l \gets p_i$。也就是说，$[l,p_i]$ 中存在 $i$ 使得 $b_i>x$，根据上面的推导我们肯定不能对这个区间连着进行操作。

- 最后在树状数组上将所有 $p_i$ 加一。

- 如果 $s$ 大于给定操作最大次数，则无解。

正确性显然，因为每次都选择最大的合法的区间操作。代码细节有一些，主要集中在对于最后一个出现的位置的讨论。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, m, cnt, a[200010], b[200010], c[200010], d[200010];
map <int, int> mp;
map <int, int> :: iterator it;
vector <int> p[200010], pp[200010];
void add(int p, int x){
	for (; p<=n; p+=p&-p) d[p] += x;
}
int query(int p){
	int ret = 0;
	for (; p; p-=p&-p) ret += d[p];
	return ret;
}
int main(){
	scanf ("%d", &t);
	while (t --){
		int flag = 0;
		cnt = 0;
		mp.clear();
		scanf ("%d", &n);
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			d[i] = 0;
		}
		for (int i=1; i<=n; i++){
			scanf ("%d", &b[i]);
			if (a[i] < b[i]) flag = 1;
		}
		scanf ("%d", &m);
		for (int i=1; i<=m; i++){
			scanf ("%d", &c[i]);
		}
		for (int i=1; i<=n; i++) mp[b[i]] = 1;
		for (it=mp.begin(); it!=mp.end(); it++){
			it->second = ++cnt;
		}
		for (int i=1; i<=n; i++){
			b[i] = mp[b[i]];
			a[i] = mp[a[i]];
			if (a[i] != b[i]) p[b[i]].push_back(i);
			pp[b[i]].push_back(i);
		}
		for (int i=1; i<=m; i++) c[i] = mp[c[i]];
		mp.clear();
		for (int i=1; i<=m; i++) mp[c[i]] ++;
		for (int i=cnt; i>=1; i--){
			if (!mp[i] && p[i].size()){
				flag = 1;
				break;
			}
			int l = 0, tot = 0;
			if (pp[i].size() == 1){
				add(pp[i][0], 1);
				continue;
			}
			for (int j=0; j<p[i].size(); j++){
				if (j == p[i].size() - 1){
					tot ++;
					if (!l) break;
					if (query(p[i][j]) - query(l-1)) tot ++;
					break;
				}
				if (!l){
					l = p[i][j];
					continue;
				}
				if (query(p[i][j]) - query(l-1)){
					tot ++;
					l = p[i][j];
				}
			}
			for (int j=0; j<pp[i].size(); j++){
				add(pp[i][j], 1);
			}
			if (tot > mp[i]){
				flag = 1;
				break;
			}
		}
		for (int i=1; i<=n; i++){
			if (p[b[i]].size()) p[b[i]].clear();
			if (pp[b[i]].size()) pp[b[i]].clear();
		}
		if (flag) puts ("NO");
		else puts ("YES");
	}
	return 0;
}
```

---

## 作者：EBeason (赞：1)

### 思路
首先先考虑，如果 $a_i < b_i$，那么一定是无解的。  
之后呢再考虑一个问题，使长度变短但还大于 $b_i$ 有用吗？

答案很显然，必须有 $x_i = b_i$ 才能使此处不需要再理发。  
所以我们就对每个 $b_i$ 求需要不需要额外的剃须刀。  
对于 $b_i$ 而言，往前找到第一个等于 $b_i$ 的位置，如果他们中间有大于 $b_i$ 的那么需要额外剃须刀，否则不需要。  
最后验证一下答案，看`M`把剃须刀给的够不够用。  
由于 $b_i \leq 10^9$ 所以需要离散化＋二分，本人比较懒，所以直接用`map`水过去了。  
细节请参考代码。  
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define ls p<<1
#define rs p<<1|1
const int MaxN=1e6+100;
const int INF=1e9;
int T,N,M,a[MaxN],b[MaxN],c[MaxN];
map<int,int>mp;
map<int,int>mp1;
struct point
{
	int x;
}tree[MaxN];
template<class T>
inline void qread(T &sum)
{
	sum=0;int boo=1;
	char x=getchar();
	while(x<'0'||x>'9'){if(x=='-')boo=-1;x=getchar();}
	while(x>='0'&&x<='9'){sum=(sum<<1)+(sum<<3)+x-'0';x=getchar();}
	sum*=boo;
}
template<class T>
void qput(T x)
{
	if(x<0) {x=-x;putchar('-');}
	if(x>9) qput(x/10);
	putchar(x%10+48);
}
inline void updata(int p)
{
	tree[p].x=max(tree[ls].x,tree[rs].x);
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		tree[p].x=b[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	updata(p);
}
int query(int p,int l,int r,int x,int y)
{
	if(r<=y&&l>=x)
	{
		return tree[p].x;
	}
	int mid=(l+r)>>1,ans=0;
	if(mid>=x) ans=max(ans,query(ls,l,mid,x,y));
	if(mid<y) ans=max(ans,query(rs,mid+1,r,x,y));
	return ans;
}
inline void Solve()
{
	mp.clear();mp1.clear();
	qread(N);
	for(int i=1;i<=N;i++) qread(a[i]);
	for(int i=1;i<=N;i++) qread(b[i]);
	qread(M);
	for(int i=1;i<=M;i++) qread(c[i]);
	build(1,1,N);
	for(int i=1;i<=N;i++)
	{
		if(a[i]<b[i])
		{
			printf("NO\n");return;
		}
		if(a[i]>b[i])
		{
			if(!mp[b[i]])
			{
				mp[b[i]]=1;
				mp1[b[i]]=i;
			}
			else
			{
				int x=mp1[b[i]];
				int ans=query(1,1,N,x,i);
				mp1[b[i]]=i;
				if(ans>b[i])
				{
					mp[b[i]]++;
				}
			}
		}
	}
	for(int i=1;i<=M;i++)
	{
		mp[c[i]]--;
	}
	for(auto it:mp)
	{
		int x=it.second;
		if(x>0)
		{
			printf("NO\n");return;
		}
	}
	printf("YES\n");
}
signed main()
{
	qread(T);
	while(T--) Solve();
}
```

---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/17031653.html)

[题目传送门](https://codeforces.com/problemset/problem/1779/D)  
[题目翻译](https://www.luogu.com.cn/problem/CF1779D)  

### 题目解析
如果有 $a_i<b_i$ 直接输出 `NO`。  
我们发现：如果 $b_l=b_r=x$ 并且所有的 $l\le i \le r$ 都有 $b_i\le x$ 那么就可以一次解决。  
也就是说，如果 $b_l=b_r$ 并且所有的 $l\le i \le r$ 都有 $b_i\le x$ 那么我们就可以合并 $l,r$，否则就要分开两次。当然 $a_i=b_i$ 的话直接忽略 $i$ 即可。  
所以问题就转化为求一个区间内是不是比 $x$ 都小。  
我们考虑可以再转化为求一个区间内比 $x$ 小的数的个数，~~所以直接树套树就好了！~~  
考虑从小到大处理所有数，然后处理好了这个数字就把辅助序列的对应位置加一，然后树状数组维护区间和。  
这样我们就知道对于每个 $x$ 至少要用几次，看看是不是给出的数量大于等于需要的数量即可。  
时间复杂度：$\Theta(n\log n)$

赛时写的一点都不简单易懂的代码：
```cpp
int n,m,a[maxn],b[maxn],c[maxn],f[maxn];
struct JTZ{
	int pos,hei;
	bool operator < (const JTZ x) const {
		if(this->hei == x.hei) return this->pos < x.pos;
		return this->hei < x.hei;
	}
}arr[maxn];
int cc[maxn];
#define lowbit(x) (x&-x)
void add(int x,int y){ while(x<=n) cc[x]+=y,x+=lowbit(x); return; }
int que(int x){ int sum=0; while(x) sum+=cc[x],x-=lowbit(x); return sum; }
int que_i(int l,int r){ if(l>r) return 1; return que(r)-que(l-1)==r-l+1; }
void work(){
	n=read(); int i,r,j=1,k,cnt,las; for(i=1;i<=n;i++) cc[i]=0;
	for(i=1;i<=n;i++) a[i]=read(); for(i=1;i<=n;i++) b[i]=read();
	m=read(); for(i=1;i<=m;i++) c[i]=read(); sort(c+1,c+m+1);
	for(i=1;i<=n;i++) if(a[i]<b[i]){ puts("NO"); return; }
	for(i=1;i<=n;i++) arr[i].pos=i,arr[i].hei=b[i]; sort(arr+1,arr+n+1);
	for(i=1;i<=n;i=r){
		for(r=i;r<=n;r++) if(arr[i].hei!=arr[r].hei) break;
		las=cnt=0;
		for(k=i;k<r;k++){
			add(arr[k].pos,1); if(arr[k].hei==a[arr[k].pos]) continue;
			if(las==0){ cnt=1; las=arr[k].pos; }
			else{
				if(!que_i(las+1,arr[k].pos-1)) cnt++;
				las=arr[k].pos;
			}
		}
		while(j<=m&&c[j]<=arr[i].hei) cnt-=(c[j]==arr[i].hei),j++;
		if(cnt>0){ puts("NO"); return; }
	} puts("YES"); return;
}
```

---

## 作者：bsTiat (赞：0)

## 题意
给定一个数列 $ a $ 和一个目标数列 $ b $ ，可以进行 $ m $ 种操作，每种操作有一个自己的 $ x $，可以选择任意一段区间 $ [l,r]$，使得 $ \forall i \in[l,r],a_i=\min(a_i,x) $，可能有操作的 $ x $ 是相同的，每种操作只能进行一次，也可以不进行，问能否使得 $ a $ 变成 $ b $。

## 思路
显然贪心，先进行一个简单的判断，若 $ \exists a_i<b_i $ ，显然无解。

定义 $ S(l,r) $ 是否能将区间 $ [l,r] $ 的 $ a $ 变成 $ b $ ，若能，根据贪心进行最少的操作。

然后对于每个 $ S(l,r) $ ，我们先得到区间 $ [l,r] $ 的最大值 $ x $，然后找到改区间内 $ x $ 的每个所在位置，若每个 $ x $ 的所在位置 $ i $，$ a_i $ 都与 $ b_i $ 一样，那就不用消耗对应的 $ x $ 的操作，反之消耗一次，若没有该种操作或着该种操作用完了，则无解。

找到每个位置之后，用这些位置把原区间分割成多个子区间，然后就递归下去，就做完了。

直接做复杂度不太对，有一些小技巧优化一下，开一个 $ vector $ 存每个数的出现位置，而每一层至少消掉一个数，所以最多 $ n $ 层，每消掉一个数的复杂度是 $ \log c $，$ c $ 是这个数的出现次数，因为要二分，所以总复杂度为 $ O( n \log n) $。
## 代码

```cpp
#include<bits/stdc++.h>
# define int long long
using namespace std;
inline int rd(){
	int f=1,s=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){s=(s<<3)+(s<<1)+(c^48);c=getchar();}
	return s*f;
}
const int N = 5e5+5;
int t,n,m,ans,fla;
int a[N],b[N],s; 
int st[25][N],lg[N];
map<int,int>c,vis,rev;
vector<int>v[N];
int qry(int l,int r){
	int t=lg[r-l+1];
	return max(st[t][l],st[t][r-(1<<t)+1]);
}
bool check(int l,int r,int x){
	auto p=lower_bound(v[rev[x]].begin(),v[rev[x]].end(),l);
	while(p!=v[rev[x]].end()&&(*p)<=r){
		if(a[*p]!=b[*p]) {
			return false;
		} ++p;
	} return true;
} 
void solve(int l,int r){
	if(l>r) return;
	int x=qry(l,r);
	if(c.find(x)==c.end()||!c[x]) {
		if(!check(l,r,x)){
			fla=0; return;
		}
	} else  if(!check(l,r,x))--c[x];
	auto p=lower_bound(v[rev[x]].begin(),v[rev[x]].end(),l);
	int lst = l;
	while(p!=v[rev[x]].end()&&(*p)<=r){
		solve(lst,(*p)-1);
		lst=(*p)+1; ++p;
	} solve(lst,r);
}
signed main(){
	t=rd(); int x,cnt=0;
	for(int i=2;i<=N-5;++i)lg[i]=lg[i>>1]+1;
	while(t--){
		n=rd(); vis.clear(); rev.clear(); cnt=0;
		for(int i=1;i<=n;++i)a[i]=rd();
		for(int i=1;i<=n;++i)st[0][i]=b[i]=rd();
		for(int i=1;i<=lg[n];++i)
			for(int j=1;j+(1<<i)-1<=n;++j)
				st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
		m=rd(); c.clear(); 
		for(int i=1;i<=m;++i){
			x=rd(); ++c[x];
		}	
		fla=1;
		for(int i=1;i<=n;++i) {
			if(a[i]<b[i]) fla=0;
			if(rev.find(b[i])==rev.end())rev[b[i]]=++cnt;
		}
		if(!fla) {
			printf("NO\n");
			continue;
		}
		for(int i=1;i<=n;++i){
			if(!vis[rev[b[i]]]){
				v[rev[b[i]]].clear();
				v[rev[b[i]]].push_back(i);
				vis[rev[b[i]]]=1;
			}else v[rev[b[i]]].push_back(i);
		}
		solve(1,n);
		if(fla) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

