# 「ALFR Round 4」B 颜料

## 题目背景

在小山的观念里，画展因色彩不同而绚丽。

## 题目描述

小山一共有 $n$ 副画作，每副画作都有其主要的颜料。具体的，第 $i$ 副画作的主要颜料的种类为 $a_i$。小山可以选择一段**编号连续**的画作组成一个画展，而画展的绚丽程度为（设该画展由第 $l$ 到第 $r$ 副画组成）：$\sum_{i=1}^W\sum_{j=i+1}^W\min(c_i,c_j)$，其中 $c_i$ 表示种类为 $i$ 的颜料在画展中出现的次数，$W$ 为所有颜料种类的值域。

现在小山想知道，若要画展的绚丽程度至少为 $k$，应至少选出多少副连续的画作？若无绚丽程度至少为 $k$ 的画展，则答案为 $-1$。

## 说明/提示

### 样例解释

选择第 $5$ 至第 $9$ 副画作组成画展，则 $c_1=0,c_2=1,c_3=1,c_4=2,c_5=0,c_6=0,c_7=0,c_8=0,c_9=1,\sum_{i=1}^9\sum_{j=i+1}^9\min(c_i,c_j)=6$。容易得知 $5$ 是符合要求的区间的最短长度。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | 所有的 $a_i(1\le i\le n)$ 都相同 |
| $1$ | $20$ | $n,a_i\le10^2$ |
| $2$ | $70$ | - |

对于 $100\%$ 的数据，$1\le n,a_i\le2\times10^6$，$1\le k\le 10^{15}$。

## 样例 #1

### 输入

```
10 6
2 3 4 3 3 4 2 4 9 2```

### 输出

```
5```

# 题解

## 作者：_LSA_ (赞：20)

# Solution

这题明明可以做到线性怎么包括官解都写的树状数组qwq。

首先，由于选择的区间是连续的一段，而且对于每个左端点 $l$，其对应满足权值超过 $k$ 的最小的右端点 $r$ 是显然单调的，所以考虑双指针，到这里根官方题解是一样的。

接下来考虑每次移动指针怎么更新权值。

记 $sz_i$ 为当前每个颜色出现的次数，$cnt_i$ 为 $sz_j \geq i$ 的 $j$ 的个数，就是颜色出现次数超过 $i$ 的颜色个数。

由于双指针移动时 $sz_{a_i}$ 只会变化 $1$，所以这两个数组是很容易维护的。

每次 $r$ 向右扩展时（这里的 $sz_{a_r}$ 还没更新），对于 $sz_x \le sz_{a_r}$ 的颜色 $x$ 是没有影响的，因为它们的 $\min$ 不变；而对于 $sz_x > sz_{a_r}$ 的颜色 $x$，由于 $\min(sz_{a_r}+1,sz_x) = \min(sz_{a_r},sz_x)+1$，所以权值会增加 $cnt_{sz_{a_r}+1}$。$l$ 的扩展是同理的。

时间复杂度 $O(n)$。

代码实现中是先更新 $sz$ 再更新权值的，跟上面的描述有点区别。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
    ll X = 0 ,r = 1;
    char ch = getchar();
    while(!isdigit(ch) && ch != '-') ch = getchar();
    if(ch == '-') r = -1,ch = getchar();
    while(isdigit(ch)) X = X*10+ch-'0',ch = getchar();
    return X*r;
}
const int N = 2e6+10;
int n,a[N],m;
int cnt[N],sz[N];
ll k;
int main(){
	n = read(); k = read();
	for(int i=1;i<=n;i++) a[i] = read();
	int ans = n+1;
	ll res = 0;
	for(int l=1,r=0;l<=n;l++){
		while(r < n && res < k){
			r++; sz[a[r]]++;
			cnt[sz[a[r]]]++;
			res += cnt[sz[a[r]]]-1;
		}
		if(res >= k) ans = min(ans,r-l+1);
		res -= cnt[sz[a[l]]]-1;
		cnt[sz[a[l]]]--; sz[a[l]]--;
	}
	printf("%d",ans == n+1 ? -1 : ans);
    return 0;
}

```

---

## 作者：szh_AK_all (赞：13)

假设区间的左端点为 $l$，右端点为 $r$，则显然，随着 $r$ 的增加，若 $l$ 不变，这段区间的权值是单调不减的。而题目又要求我们求出权值不小于 $k$ 的区间的最小长度，便可以使用双指针来解决。

具体的，若左端点为 $l$，右端点为 $r$ 的区间的权值小于 $k$，则将右端点右移，直到区间的权值不小于 $k$ 为止；若区间的权值不小于 $k$，先更新答案（区间的长度为 $r-l+1$），再将左端点右移，直到区间的权值小于 $k$ 为止。

关节在于如何计算区间更新后的权值。

具体的，如果一种新的颜料加入了区间，那么该颜料的贡献值应分为两部分：一、在区间内出现的次数比该颜料出现次数小的所有颜料的出现次数之和（当然，由于这是新种类的颜料，所以区间内没有出现次数比它小的颜料）；二、在区间内出现的次数不小于该颜料出现次数的颜料的种类数量乘上该颜料的出现次数。显然，这可以用两个树状数组来维护。

当然，如果新加入的颜料此前已在区间内出现过了，则应当先将此前这种颜料的贡献值减去，再加上加入后的贡献值。

删除操作同理。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long k;
int a[2000005];
long long c1[2000005], c2[2000005];
int read() {
    int x = 0, f = 1;
    char ch=getchar();
    while(ch < '0' || ch > '9') { 
        if(ch == '-') 
            f = -1;
        ch = getchar();
    }
    while(ch >='0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch -'0';
        ch = getchar();
    }
    return x * f;
}
void add(int x, long long y, long long c[]) {
	if (x < 0)
		return;
	for (; x <= n; x += x & (-x))
		c[x] += y;
}

long long ask(int x, long long c[]) {
	if (x < 0)
		return 0;
	long long ans = 0;
	for (; x; x -= x & (-x))
		ans += c[x];
	return ans;
}
long long t[3000005];

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
        a[i] = read();
	int l = 1, r = 0, ans = 1000000000;
	long long tmp = 0;
	int zh = 0;
	while (r < n) {
		if (tmp < k) {
			r++;
			if (t[a[r]]) {
				tmp -= (ask(t[a[r]] - 1, c1) + 1LL * (zh - 1 - ask(t[a[r]] - 1, c2)) * t[a[r]]);
				add(t[a[r]], -t[a[r]], c1);
				add(t[a[r]], -1, c2);
			}
			t[a[r]]++;
			if (t[a[r]] == 1)
				zh++;
			add(t[a[r]], t[a[r]], c1);
			add(t[a[r]], 1, c2);
			tmp += (ask(t[a[r]] - 1, c1) + 1LL * (zh - 1 - ask(t[a[r]] - 1, c2)) * t[a[r]]);
		}
        while (tmp >= k) {
            ans = min(ans, r - l + 1);
            l++;
            tmp -= (ask(t[a[l - 1]] - 1, c1) + (zh - 1 - 1LL * ask(t[a[l - 1]] - 1, c2)) * t[a[l - 1]]);
            add(t[a[l - 1]], -t[a[l - 1]], c1);
            add(t[a[l - 1]], -1, c2);
            t[a[l - 1]]--;
            if (t[a[l - 1]] == 0)
                zh--;
            else {
                add(t[a[l - 1]], t[a[l - 1]], c1);
                add(t[a[l - 1]], 1, c2);
                tmp += (ask(t[a[l - 1]] - 1, c1) + (zh - 1 - 1LL * ask(t[a[l - 1]] - 1, c2)) * t[a[l - 1]]);
            }
        }
	}
	if (tmp >= k)
		ans = min(ans, r - l + 1);
	if (ans == 1000000000)
		cout << -1;
	else
		cout << ans;
}
```

---

## 作者：Graph (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/P11012)

---

本题算法：双指针、树状数组。

一个简单的思路：求出以 $rt$ 结尾的最大的 $lt$，并满足区间 $[lt,rt]$ 的绚丽度至少为 $k$。

于是我们的暴力就出来了：枚举每一个 $rt$，对于每一个 $rt$，向前枚举 $lt$，并依次扫描 $[lt,rt]$ 内的所有元素，暴力判断是否满足要求。

时间复杂度：$O(n^3)$。

优化：枚举每一个 $rt$，对于每一个 $rt$，往前枚举 $lt$，于是每一次我们的区间就从 $[lt,rt]$ 变为 $[lt-1,rt]$，区间增加了一个元素 $a_{lt-1}$。

我们用 $num_i$ 代表 $i$ 在当前区间中出现了几次，如果新加入一个元素 $j$，那么 $num_j$ 要加一。

接下来算新加入一个元素 $i$ 对绚丽度作出的贡献，分两种情况讨论：

- 对于另外一个元素 $j$，满足 $num_j \le num_i$，那么若 $num_i$ 加一，最小值仍然取到 $num_j$，所以这种情况不作贡献。
- 对于另外一个元素 $j$，满足 $num_j > num_i$，若 $num_i$ 加一，最小值会取到 $num_i$，这种情况绚丽度加了 $1$。

因此，加入一个元素 $i$ 作出的贡献就是所有 $j$ 满足 $num_j > num_i$ 的个数，可以用树状数组维护。

时间复杂度：$O(n^2 \log n)$。

这样的时间复杂度仍然通过不了此题，我们需要继续优化。

注意到随着 $rt$ 的增加，$lt$ 是**单调不减**的，这样我们就能用双指针来求了，因为 $lt$ 和 $rt$ 都只会往前走，不会后退。

那么我们考虑删除一个元素 $i$ 减去的贡献，分两种情况讨论：

- 对于另外一个元素 $j$，满足 $num_j < num_i$，那么若 $num_i$ 减一，最小值仍然取到 $num_j$，所以这种情况不作贡献。
- 对于另外一个元素 $j$，满足 $num_j \ge num_i$，若 $num_i$ 减一，最小值会取到 $num_i$，这种情况绚丽度减了 $1$。

因此，删除一个元素 $i$ 减去的贡献就是所有 $j \ne i$ 满足 $num_j \ge num_i$ 的个数，依然可以用树状数组维护。

由于 $lt$ 最多加 $n$ 次，$rt$ 加 $n$ 次，每次要树状数组查询与修改，故时间复杂度为 $O(n \log n)$。

注意：树状数组的起始下标不能为 $0$，因此要将插入树状数组的 $num$ 都加一。

本题卡常，似乎不能用线段树。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e6+5;
int n,k,a[N],res=1e18,tree[N],num[N];

int lowbit(int x)
{
    return x&-x;
}

int query(int x)
{
    int sum=0;
    while(x!=0)
    {
        sum+=tree[x];
        x-=lowbit(x);
    }
    return sum;
}

void update(int x,int val)
{
    while(x<=2e6+1)
    {
        tree[x]+=val;
        x+=lowbit(x);
    }
    return ;
}

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    update(1,2e6);
    int lt=1,rt=0,ans=0;
    while(rt<n)
    {
        rt++;
        ans+=2e6-query(num[a[rt]]+1);
        update(num[a[rt]]+1,-1);
        num[a[rt]]++;
        update(num[a[rt]]+1,1);
        while(ans-(2e6-query(num[a[lt]])-1)>=k) //减1，不包含它自己
        {
            ans-=2e6-query(num[a[lt]])-1;
            update(num[a[lt]]+1,-1);
            num[a[lt]]--;
            update(num[a[lt]]+1,1);
            lt++;
        }
        if(ans>=k)
            res=min(res,rt-lt+1);
    }
    if(res==1e18)
        puts("-1");
    else
        cout<<res;
    return 0;
}
```

---

## 作者：jianhe (赞：7)

### 前置知识：
双指针，树状数组

### 简要题意：
选择 **连续** 的一段画作，并且满足绚丽程度 $\ge k$，求最小画作数量。

### 考场思路：
根据“连续”等字眼，自然想到用 **双指针** 来维护左右端点。遍历整个序列，时间复杂度是 $O(n)$ 的。

那么，如何在移动指针时更新绚丽程度呢？这是本题的难点。

分析 $\sum_{i=1}^W\sum_{j=i+1}^W\min(c_i,c_j)$ 这个式子，其实就是每种颜色出现次数与其他颜色出现次数取最小值，并相加的结果。

假设 $c_k$ 加上了 $1$，那么它会产生多少贡献呢？其实很简单，它只会对满足 $c_p > c_k$ 的 $\min(c_p,c_k)$ 产生 $1$ 的贡献。即对整个式子产生贡献的值为：当前序列中 $> c_k$ 的个数。 

同理，假设 $c_k$ 减去了 $1$，那么它只会对满足 $c_p \ge c_k$ 的 $\min(c_p,c_k)$ 减去 $1$ 的贡献。即对整个式子减去贡献的值为：当前序列中 $\ge c_k$ 的个数。

由于颜色出现次数不会超过 $n$，可以建一个树状数组，以颜色出现次数为下标，维护每种颜色的出现次数。这样，查询的复杂度是 $O(\log{n})$。

总复杂度 $O(n \log{n})$。

### 细节：
颜色出现次数可能为 $0$，那么我们可以将每个下标增加 $1$（把整个数组向右移），防止死循环。

其实特判也可以。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(x) (x&(-x))
const ll N=2e6+10;
ll n,k,a[N],col[N],ans,res,s[N],ct;
bool flag;
void add(ll x,ll y){
	x++;//避免 0 导致死循环，给下标+1
	while(x<=n+1) s[x]+=y,x+=lowbit(x);
}
ll query(ll x){
	x++;
	ll as=0;
	while(x) as+=s[x],x-=lowbit(x);
	return as;
}
ll ask(ll l,ll r){return query(r)-query(l-1);}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>k;ans=n+1;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(ll i=1,j=1;i<=n;i++){//双指针
		while(j<=n&&res<k) res+=ask(col[a[j]]+1,n),add(col[a[j]],-1),add(++col[a[j]],1),j++;
		if(res>=k) ans=min(ans,j-i);//更新答案
		res-=ask(col[a[i]],n)-1,add(col[a[i]],-1),add(--col[a[i]],1);
	}
	cout<<(ans==n+1?-1:ans);
	return 0;
}
```

---

## 作者：TigerNick (赞：3)

比赛时数组开小了，不然就AC了......

首先，本题让我联想到了[逛画展](https://www.luogu.com.cn/problem/P1638)，考虑能否使用双指针的策略维护一段区间呢？题目描述中，记 $c_i$ 表示种类为 $i$ 的颜料在画展中出现的次数。那么对于一个区间，每增加一个颜料 $x$ ， $c_x$ 便会增加 1 ，画展的绚丽程度是不减的，具有单调性，因此考虑双指针维护一段画展。

对于一个区间，每增加一个颜料 $x$ ， $c_x$ 便会增加 1 ，注意到这只会影响满足 $c_y>c_x$ 的颜料对 $(x,y)$ 的贡献。新加入的贡献值为满足 $c_y>c_x$ 的颜料 $y$ 的个数。删除同理。

如何快速统计颜料 $y$ 的个数呢？可以使用树状数组维护 $tree_i$ 表示**所维护的区间内，出现次数为 $i$ 的颜料的种类数**，加入或删除一个颜料 $x$ 
时，直接单点修改维护 $tree$ 即可。

时间复杂度 $O(n\log n)$ 。

```cpp
#include <bits/stdc++.h>
#define MAXN 2000010
#define INF 1000000000000
#define int long long
using namespace std;
int n,k,a[MAXN];
int tree[MAXN];
int sz[MAXN];
void chkmin(int &x,int y){x=y<x?y:x;}
int lowbit(int x){return x&(-x);}
void upd(int x,int k)
{
	if(x<=0) return;
	for(;x<=n;x+=lowbit(x))
		tree[x]+=k;
}
int q(int x)
{
	int res=0;
	if(x<=0) return 0;
	for(;x;x-=lowbit(x))
		res+=tree[x];
	return res;
}
int qry(int l,int r){return q(r)-q(l-1);}
void solve()
{
	cin>>n>>k;
	int l=1,r=0,sum=0,ans=INF;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		int tmp=qry(sz[a[i]]+1,n);
		if(sum+tmp>=k) chkmin(ans,r-l+2);
		r++;
		sz[a[i]]++;
		sum+=tmp;
		upd(sz[a[i]]-1,-1);
		upd(sz[a[i]],1);
		while(sum>=k)
		{
			sz[a[l]]--;
			upd(sz[a[l]]+1,-1);
			upd(sz[a[l]],1);
			int tmp2=qry(sz[a[l]]+1,n);
			sum-=tmp2;
			chkmin(ans,r-l+1);
			l++;
		}
	}
	if(ans<INF) cout<<ans;
	else cout<<-1;
}
signed main()
{
	ios::sync_with_stdio(0);
	int _T=1;//cin>>_T;
	while(_T--)solve();
    return 0;
}
```

---

## 作者：Eric159357 (赞：3)

我们记 $\sum_{i=1}^W\sum_{j=i+1}^W\min(c_i,c_j)=ans$，所有颜料种类的值域为 $W$。

首先说明为什么要使用双指针法：

我们假设，当区间左端点为 $l$ 时右端点最小为 $r$，则当左端点变为 $l+1$ 时，只有如下两种情况：

1. 若 $c_1$ 到 $c_W$ 中除了 $c_{a_{l}}$ 以外的数都比 $c_{a_{l}}$ 小，则去掉一个 $a_{l}$ 后，$c_{a_{l}}$ 仍会是 $c_1$ 到 $c_W$ 中的最大值，右端点不变。
2. 若不满足情况 $1$，则去掉一个 $a_{l}$ 后，一定存在一个 $i \neq a_{l}$，使得 $c_i > c_{a_{l}}$，这时 $\min (c_i,c_{a_{l}})$ 的值就会变小，$ans$ 也变小，显然此时右端点一定不降。

由此可见，随着 $l$ 的增加，$r$ 单调不降，可以使用双指针法。

我们不妨研究一下加入画作和去掉画作的过程。加入一个颜料为 $x$ 的画作可以看作将 $c_x$ 先赋值为 $0$，之后赋值为原来的值 $+1$。删除元素同理。

- 当 $c_x$ 从 $k$ 赋值为 $0$ 时，对 $ans$ 的贡献是 $-cnt_k \times k-sum_k+k$，其中 $cnt_{k}$ 表示当前有多少个 $c_i$ 大于等于 $k$，$sum_{k}$ 表示当前所有小于 $k$ 的 $c_i$ 之和。最后加了一个 $k$ 是因为 $k$ 本身也被算在 $cnt_{k}$ 中。

- 当 $c_x$ 从 $0$ 赋值到 $k$ 时，对 $ans$ 的贡献是 $cnt_k \times k+sum_k$。

因此我们可以在移动左右指针时用两个树状数组维护 $cnt_{k}$ 和 $sum_{k}$，并更新 $ans$ 的值。时间复杂度 $O(W \log W)$，常数有点大，所以要加一点小优化。

```cpp
#include <iostream>
#include <cstring>
#define MAXN 2000050
#define INF  2000010
#define ll long long
using namespace std;
ll n,k,a[MAXN],ans=INF,cur[MAXN],tmp=0;

struct BIT{
    int t[MAXN];
    void init()
    {
        memset(t,0,sizeof(t));
    }
    void addnum(int p,ll k)
    {
        for (int i=p;i<=MAXN-1;i+=i&-i)
            t[i]+=k;
    }
    ll getsum(int p)
    {
        ll ret=0;
        for (int i=p;i;i-=i&-i) 
            ret+=t[i];
        return ret;
    }
}cnt,sum;

void del(ll x)
{
    tmp-=cnt.getsum(x)*x-x+sum.getsum(x);
    cnt.addnum(1,-1); //将cnt[ 1,cur[a[l]] ] 减1
    cnt.addnum(x+1,1);
    sum.addnum(x+1,-x); //将sum[ cur[a[l]]+1,MAXN ] 减cur[a[l]]
    sum.addnum(INF,x);
}

void add(ll x)
{
    tmp+=cnt.getsum(x)*x+sum.getsum(x);
    cnt.addnum(1,1); //将cnt[ 1,cur[a[r]] ] 加1
    cnt.addnum(x+1,-1);
    sum.addnum(x+1,x); //将sum[ cur[a[r]]+1,MAXN ] 加cur[a[r]]
    sum.addnum(INF,-x);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cnt.init();
    sum.init();

    cin>>n>>k;
    for (int i=1;i<=n;i++) cin>>a[i];
    ll l=1,r=0;
    while (1)
    {
        if (tmp>=k&&l<r)
        {
            ans=min(ans,r-l+1);
            del(cur[a[l]]);
            cur[a[l]]--;
            if (cur[a[l]]) add(cur[a[l]]); //必要的常数优化
            l++;
        }
        else
        {
            r++;
            if (r>n) break;
            if (cur[a[r]]) del(cur[a[r]]); //必要的常数优化
            cur[a[r]]++;
            add(cur[a[r]]);
        }
    }
    if (ans==INF) cout<<-1<<endl;
    else cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Null_h (赞：2)

## 前言

一道在赛场上被卡很久的 T2，于是决定写篇题解纪念一下（嗯）。

另：赛后也是看了一些别的做法，例如树状数组之类的，写法上确实比较简洁，但是鉴于对该题目的个人见解，还是想写出来给诸位避个坑。

## 思路

看到题的第一眼就觉得答案满足单调性，一看数据范围更加确信，于是想到二分答案区间长度。

然后考虑 check 函数，它需要在 $O(n)$ 的时间里得到是否有一个规定长度的区间满足绚烂值 $\ge k$，那么如果先将第一个区间的答案处理好，然后达到 $O(1)$ 地移动区间（类似于滑动窗口的感觉），那么复杂度即满足要求。

接下来搓一下公式，研究一下性质。发现它只关注颜色的出现次数，而不关注具体是什么颜色，并且所有出现次数大于等于它的颜色都会使它产生一次贡献（当然不能是自己）。

记出现次数为 $i$ 的颜色有 $b_i$ 个，那么对于这些颜色所产生的贡献，我们分成两部分：

首先是其他出现次数为 $i$ 的，他们两两之间产生一次贡献，最后答案为 $i\times b_i\times (b_i-1)\div 2$。

以及所有比它大的数字，我们维护一个后缀和数组 $c$，最后总贡献为 $i\times b_i\times c_{i+1}$。

现在我们可以处理出第一个区间的答案了，接下来考虑如何移动。我们发现，如果向维护的区间中加入一个颜色，设它原来的出现次数为 $p$，那么对这两个数组的影响只有三处，体现在代码里长这样：
```cpp
c[p+1]++;
b[p]--;
b[p+1]++;
```
于是我们把涉及到他们的贡献全部重算一遍就可以了，删除一个颜色也是一样的。

现在可以写代码了（别急着抄）。

## 代码（被卡版）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[2000010],b[2000010],c[2000010],h[2000010],n;
int check(int x){
	//cout<<x<<':';
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	memset(h,0,sizeof(h));
	for(int i=1;i<=x;i++){
		h[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		b[h[i]]++;
	}
	int ansn=0,ans=0;
	for(int i=x;i>=1;i--){
		c[i]=b[i];
		c[i]+=c[i+1];
		ansn+=b[i]*i*c[i+1];
		ansn+=i*b[i]*(b[i]-1)/2;
	}
	//cout<<ansn<<' ';
	ans=ansn;
	for(int i=x+1;i<=n;i++){
		int p=h[a[i]];
		h[a[i]]++;
		ansn-=b[p]*p*c[p+1];
		ansn-=b[p+1]*(p+1)*c[p+2];
		ansn-=p*b[p]*(b[p]-1)/2;
		ansn-=(p+1)*b[p+1]*(b[p+1]-1)/2;
		c[p+1]++;
		b[p]--;
		b[p+1]++;
		ansn+=b[p]*p*c[p+1];
		ansn+=b[p+1]*(p+1)*c[p+2];
		ansn+=p*b[p]*(b[p]-1)/2;
		ansn+=(p+1)*b[p+1]*(b[p+1]-1)/2;
		p=h[a[i-x]];
		h[a[i-x]]--;
		p--;
		ansn-=b[p]*p*c[p+1];
		ansn-=b[p+1]*(p+1)*c[p+2];
		ansn-=p*b[p]*(b[p]-1)/2;
		ansn-=(p+1)*b[p+1]*(b[p+1]-1)/2;
		c[p+1]--;
		b[p]++;
		b[p+1]--;
		ansn+=b[p]*p*c[p+1];
		ansn+=b[p+1]*(p+1)*c[p+2];
		ansn+=p*b[p]*(b[p]-1)/2;
		ansn+=(p+1)*b[p+1]*(b[p+1]-1)/2;
		ans=max(ans,ansn);
		//cout<<ansn<<' ';
	}
	//cout<<'\n';
	return ans;
}
signed main(){
	int k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=1,r=n;
	if(check(n)<k){
		cout<<-1;
		return 0;
	}
	while(r-l>=1){
		int mid=l+r>>1;
		if(check(mid)>=k){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	cout<<r;
	return 0;
}
```


## 优化

结果快乐地[被卡常了](https://www.luogu.com.cn/record/175389254)呢。

一通优化无果后，我认为是中间的一段修改写的太暴力了。

于是思索了一下，发现这东西雀食可以优化，例如这三行：
```cpp
ansn-=p*b[p]*(b[p]-1)/2;
b[p]--;
ansn+=p*b[p]*(b[p]-1)/2;
```
这个乘法的常数不小，但是化简一下其实是：
```cpp
ansn-=p*(b[p]-1);
b[p]--;
```
好！于是对于所有类似的东西都化简一下，最后效果是这样的：

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[2000010],b[2000010],c[2000010],h[2000010],n,k,ma;

int check(int x){
	//cout<<x<<':';
	for(int i=1;i<=max(x,ma);i++){
		b[i]=c[i]=h[i]=0;
	}
	for(int i=1;i<=x;i++){
		h[a[i]]++;
	}
	for(int i=0;i<=ma;i++){
		b[h[i]]++;
	}
	int ansn=0,ans=0;
	for(int i=x;i>=1;i--){
		c[i]=b[i];
		c[i]+=c[i+1];
		ansn+=b[i]*i*c[i+1];
		ansn+=i*b[i]*(b[i]-1)/2;
	}
	//cout<<ansn<<' ';
	if(ans>=k)return ans;
	ans=ansn;
	for(int i=x+1;i<=n;i++){
		int p=h[a[i]];
		h[a[i]]++;
		ansn+=p*(b[p]-c[p+1]-1);
		ansn+=(p+1)*c[p+2];
		ansn-=p*(b[p]-1);
		ansn+=(p+1)*b[p+1];
		c[p+1]++;
		b[p]--;
		b[p+1]++;
		p=h[a[i-x]];
		h[a[i-x]]--;
		p--;
		ansn+=p*(-b[p]+c[p+1]-1);
		ansn-=(p+1)*c[p+2];
		ansn-=(p+1)*(b[p+1]-1);
		ansn+=p*b[p];
		c[p+1]--;
		b[p]++;
		b[p+1]--;
		ans=max(ans,ansn);
		if(ans>=k)return ans;
		//cout<<ansn<<' ';
	}
	//cout<<'\n';
	return ans;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ma=max(ma,a[i]);
	}
	if(check(n)<k){
		cout<<-1;
		return 0;
	}
	int l=1,r=n;
	while(r-l>=1){
		int mid=l+r>>1;
		int s=check(mid);
		if(s>=k){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	cout<<r;
	return 0;
}
```

---

## 作者：operator_ (赞：2)

# P11012 「ALFR Round 4」B 颜料

[题目传送门](https://www.luogu.com.cn/problem/P11012)

## 题解

考虑计算贡献，发现出现次数第 $i$ 大的数会被计算 $i-1$ 次。我们考虑双指针的同时维护答案，那么我们就需要维护加数和删数。出现次数是好维护的，重点在于动态维护其有序性。发现每次操作出现次数的变化量不会超过 $1$，于是其有序性只会变化 $O(1)$ 次，，吗？显然不是，因为如果有大量出现次数相同的数他就寄了，但是他最多只会有 $O(1)$ 种本质不同的出现次数会受到影响是真的，所以我们考虑维护一个 $l_i,r_i$，表示出现次数为 $i$ 的数，左右端点排序后分别是第几位（这里相当于是在维护有序数组中的每一个连续段），然后此时，每次操作就变得很好维护了。

仔细理解上述过程，我们实际上是对所有出现次数又统计了一遍出现次数。时间复杂度是 $O(n)$，但是根本跑不过带 $\log$ 的树状数组，怎么回事呢。一些细节写起来还是有点烦的。

代码：

```cpp
//Date: 2024-08-30 14:24:32
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
bool MBE;
namespace SOLVER {
int n,k,a[2000005],m1[2000005],mn[2000005],mx[2000005],now,ans=INT_MAX;
void add(int i) {
    now-=mn[m1[a[i]]]*m1[a[i]];
    mn[m1[a[i]]]++;m1[a[i]]++;mx[m1[a[i]]]++;
    now+=mx[m1[a[i]]]*m1[a[i]];
}
void det(int i) {
    now-=mx[m1[a[i]]]*m1[a[i]];
    mx[m1[a[i]]]--;m1[a[i]]--;mn[m1[a[i]]]--;
    now+=mn[m1[a[i]]]*m1[a[i]];
}
void MAIN() {
    cin>>n>>k;for(int i=1;i<=n;i++) a[i]=rd();
    for(int i=0;i<=2000000;i++) mn[i]=1;
    mx[0]=n;
    for(int l=1,r=1;l<=n;l++) {
        while(now-(r-l)<k&&r<=n) add(r++);
        if(now-(r-l)>=k) ans=min(ans,r-l);
        det(l);
    }
    if(ans>(int)1e9) puts("-1");
    else cout<<ans<<endl;
}
}
bool MED;
signed main() {
    //freopen(".in","r",stdin);freopen(".out","w",stdout);
    for(int tt=1;tt;tt--) SOLVER::MAIN();
    cerr<<(&MBE-&MED)/1024<<" B, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：yezicong1104 (赞：1)

### 思路一
暴力方法，枚举每个区间并计算，时间复杂度为 $O(n^4)$，肯定会超时。
### 思路二
我们发现，将画作的区间拓展后，绚丽程度一定不会变小，所以在思路一的基础上考虑用双指针优化。大致的代码如下：
```cpp
long long sum = 0; //存储绚丽程度
int l = 1, r = 1, ans = N;
while (r <= n) {
	//计算过程
	while (sum >= k && l <= r) {
		ans = min(ans, r - l + 1); //更新答案
		//计算过程
		l++;
	}
	r++;
}
```
计算过程的时间复杂度为 $O(n^2)$，总的时间复杂度为 $O(n^3)$。
### 思路三
在思路二中，每次计算的时间复杂度都是 $O(n^2)$。考虑优化：当 $r$ 向右拓展时，这是绚丽程度将增加多少？由于绚丽程度是区间内的数两两最小值的和，所以这取决于 $\min(c_i,c_{a_r})$ 是否增加。对于 $c_i$ 和原本的 $c_{a_r}$：
$$\min(c_i,c_{a_r})=\begin{cases}c_i & c_i < c_{a_r} \\ c_{a_r} & c_i \ge c_{a_r} \end{cases}$$
由此得：
$$\min(c_i,c_{a_r}+1)=\begin{cases} \min(c_i,c_{a_r}) & c_i \le c_{a_r} \\ min(c_i,c_{a_r})+1 & c_i > c_{a_r} \end{cases}$$
所以当 $r$ 向右拓展时，绚丽程度会增加 $c$ 序列中比 $c_{a_r}$ 大的数的个数，即 $sum\gets sum+\sum_{i=1}^n[c_i>c_{a_r}]$。
同理可得当 $l$ 向右回缩时，绚丽程度会减小 $c$ 序列中比 $c_{a_l}$ 大的数的个数，即 $sum\gets sum-\sum_{i=1}^n[c_i>c_{a_l}]$。
大致代码如下：
```cpp
long long sum = 0;
int l = 1, r = 1, ans = N;
while (r <= n) {
	for (int i = 1; i <= n; i++)
		sum += (c[i] > c[a[r]]);
	c[a[r]]++;
	while (sum >= k && l <= r) {
		ans = min(ans, r - l + 1);
		c[a[l]]--;
		for (int i = 1; i <= n; i++)
			sum -= (c[i] > c[a[l]]);
		l++;
	}
	r++;
}
```
这样就把计算的时间复杂度降到了 $O(n)$，总体时间复杂度为 $O(n^2)$，由于 $n\le 2\times 10^6$，但还是无法通过全部数据，能拿 $20$ 分。
### 思路四
每次计算大于 $c_{a_r}$ 和 $c_{a_l}$ 的数的个数要花很多时间，可以用一个 $cnt$ 数组存储，其中 $cnt_i$ 存储 $c$ 序列中大于 $i$ 的数的个数，那么当 $r$ 向右拓展时，就按顺序进行以下操作：
$$r\gets r+1$$
$$sum\gets sum+cnt_{c_{a_r}}$$
$$cnt_{c_{a_r}}\gets cnt_{c_{a_r}}+1$$
$$c_{a_r}\gets c_{a_r}+1$$
当 $l$ 向右回缩时，操作的顺序正好颠倒一下：
$$c_{a_l}\gets c_{a_l}-1$$
$$cnt_{c_{a_l}}\gets cnt_{c_{a_l}}-1$$
$$sum\gets sum-cnt_{c_{a_l}}$$
$$l\gets l+1$$
时间复杂度为 $O(n)$，可以拿满分了！
### AC 代码

```cpp
#include <iostream>

using namespace std;

typedef long long LL;
const int N = 2000010;
int a[N], c[N], cnt[N];

int main() {
	int n;
	LL k;
	scanf("%d%ld", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int ans = N;
	LL sum = 0;
	int l = 1, r = 1;
	while (r <= n) {
		sum += cnt[c[a[r]]];
		cnt[c[a[r]]]++;
		c[a[r]]++;
		while (sum >= k && l <= r) {
			ans = min(ans, r - l + 1);
			c[a[l]]--;
			cnt[c[a[l]]]--;
			sum -= cnt[c[a[l]]];
			l++;
		}
		r++;
	}
	printf("%d", ans == N ? -1 : ans); //特判
	return 0;
}
```

---

## 作者：zhoumurui (赞：0)

### 前置知识

[离散化](https://oiwiki.org/misc/discrete/)

[双指针](https://oiwiki.org/misc/two-pointer/)

[树状数组](https://oiwiki.org/ds/fenwick/)

[权值树状数组](https://oiwiki.org/ds/fenwick/#%E6%9D%83%E5%80%BC%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84%E5%8F%8A%E5%BA%94%E7%94%A8)

### 题面展示

给出一个长度为 $n$ 的序列，定义一个区间 $[l,r]$ 的权值为 $\sum_{i=1}^W \sum_{j=i+1}^W\min(c_i,c_j)$，其中 $c_i$ 表示 $i$ 在序列的 $[l,r]$ 区间内出现的次数，$W$ 为序列 $[l,r]$ 区间内的最大值。

求权值不小于 $k$ 的区间的最小长度。

$1 \le n,a_i \le 2 \times 10^6$，$1 \le k \le 10^{15}$。

### 解题思路

我们显然可以发现，$[l,r+1]$ 和 $[l-1,r]$ 的权值显然都比 $[l,r]$ 的权值要大。

因此我们可以枚举 $l$，然后逐步向右移动 $r$，一旦 $[l,r]$ 的权值不小于 $k$，那么以 $l$ 为左端点的答案就是 $r-l+1$，继续计算以 $l+1$ 为左端点的答案即可。

这个步骤可以进一步简化：

假设计算到 $[l,r]$ 的时候，发现这个区间的权值不小于 $k$ 了，那么无需重新从 $[l+1,l+1]$ 开始枚举。

因为我们计算过 $[l,r-1]$，它的权值小于 $k$，因此 $[l+1,r-1]$ 的权值也必然小于 $k$，所以我们可以从 $[l+1,r]$ 开始枚举。

（这其实就是一个双指针。）

但是这样优化以后，复杂度从 $O(n^3)$ 优化到了 $O(n^2)$，依然超时。因为以 $O(n)$ 的开销计算一个区间的权值实在是太慢了。

考虑，我们计算完区间 $[l,r]$ 的权值之后，能否利用这个结果来计算 $[l,r+1]$ 的权值或是 $[l+1,r]$ 的权值呢？

是可以的，我们考虑维护 $c_i$ 的权值树状数组。$c_i$ 本身是原序列的权值数组，而要维护的是 $c_i$ 

当我们的区间中多了一个数 $i$ 时，$c_i$ 的值加上 $1$，我们只需要统计多出的答案有多少就行了。

公式是 $\sum_{i=1}^W \sum_{j=i+1}^W\min(c_i,c_j)$，我们发现只需要**在 $c_i$ 加 $1$ 以前**，统计 $c$ 数组中有多少个值大于 $c_i$ 就好了。

那么我们就可以利用刚才开的权值树状数组，求该数组 $[c_i+1,W]$ 的区间和。 

缩小区间时把这部分再去掉就可以了。

本题有坑，标注在下面代码片段的注释中。

### 核心代码展示

#### 树状数组

```cpp
int s[2000005];
inline int lowbit(int x){
    return x&(-x);
}
inline void add(int k,int x){
    for (int i=k;i<=2000000;i+=lowbit(i))s[i]+=x;
}
inline int query(int k){
    int ans=0;
    for (int i=k;i;i-=lowbit(i))ans+=s[i];
    return ans;
}
```

#### 离散化

```cpp
for (int i=1;i<=n;i++){
    cin>>a[i];
    lsh[i]=a[i];
}
sort(lsh+1,lsh+1+n);
int m=unique(lsh+1,lsh+1+n)-lsh-1;
for (int i=1;i<=n;i++){
    a[i]=lower_bound(lsh+1,lsh+1+m,a[i])-lsh;
}
```

#### 双指针

```cpp
int ans=n;
int val=0;
add(1,1);
c[a[1]]++;
for (int i=1,j=1;i<=n;i++){
    while (j<n&&val<k){
        j++;
        val+=query(2000000)-query(c[a[j]]);
        if (c[a[j]])add(c[a[j]],-1);//坑点1:小心add(0,x)导致的死循环。
	        add(c[a[j]]+1,1);
        add(c[a[j]]+1,1);
        c[a[j]]++;//坑点2:注意调整 c 数组行的位置，根据该行位置的改变，周边行使用的 c[a[i]] 需要进行适当的偏移。
    }
    if (i==1&&j==n&&val<k){
        cout<<-1;
        return 0;
    }
    if (val>=k)ans=min(ans,(long long)(j-i+1));
    c[a[i]]--;//坑点2:注意调整 c 数组行的位置，根据该行位置的改变，周边行使用的 c[a[i]] 需要进行适当的偏移。
    add(c[a[i]]+1,-1);
    if (c[a[i]])add(c[a[i]],1);//坑点1:小心add(0,x)导致的死循环。
	        add(c[a[j]]+1,1);
    val-=query(2000000)-query(c[a[i]]);	    
}
cout<<ans;
```

---

## 作者：CNS_5t0_0r2 (赞：0)

闲话：~~关于赛时我都知道要用树状数组并且知道如何添加一个元素就是想不到用双指针这件事。~~

正解：树状数组 + 双指针。

显然，如果选择区间的端点为 $l$，其对应的满足要求的最短区间的右端点为 $r$，则对于左端点 $l + 1$，其对应的满足要求的最短区间的右端点肯定大于 $r$，这样就可以使用双指针解决了。

现在的问题就在于如何在移动指针的时候动态维护画展的绚丽程度。

对于题目中的 $c$，是可以 $O(1)$ 更新的。

假设添加的元素为 $a_r$，首先在树状数组上将 $c_{a_r}$ 减 $1$，表示出现次数为 $c_{a_r}$ 的数的个数少了 $1$。然后将计数器 $c$ 上将 $c_{a_{r}}$。最后将新的 $c_{a_r}$ 在树状数组上加 $1$。

考虑 $c_{a_r}$ 加 $1$ 会使哪些 $\min(c_i,c_{a_r})$ 发生变化，显然就是那些小于修改前 $c_{a_r}$ 的 $c_i$ 会发生变化（加 $1$）。绚丽程度的总变化量为 $c_i > c_{a_r}$ 的 $c_i$ 的个数（这里的 $c_{a_r}$ 为修改前的值）。

删除 $a_l$ 同理，不多赘述。

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6 + 9;
int n,ans;
int a[N],min_a,max_a;
int c[N];
int K;
struct BinaryIndexedTree{
	int t[N];
	int lowbit(int x){
		return x & (-x);
	}
	void update(int pos,int v){
		if(pos <= 0)
			return;
		for(int i = pos;i <= n;i += lowbit(i))
			t[i] += v;
	}
	int query(int pos){
		if(pos <= 0)
			return 0;
		int ret = 0;
		for(int i = pos;i;i -= lowbit(i))
			ret += t[i];
		return ret;
	}
	void clear(int pos){
		if(pos <= 0)
			return;
		for(int i = pos;i <= n;i += lowbit(i))
			t[i] = 0;
	}
} BIT;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> K;
	ans = n;
	min_a = LLONG_MAX;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
		min_a = min(min_a,a[i]);
		max_a = max(max_a,a[i]);
	}
	if(min_a == max_a){
		cout << -1;
		return 0;
	}
	int l = 1,r = 1;
	int tmp = 0;
	for(;l <= n;l++){
		for(;r <= n && tmp < K;r++){
			BIT.update(c[a[r]],-1);
			c[a[r]]++;
			BIT.update(c[a[r]],1);
			tmp += 1ll * (BIT.query(n) - BIT.query(c[a[r]] - 1) - 1);
		}
		if(r > n && tmp < K)
			break;
		ans = min(ans,r - l);
		BIT.update(c[a[l]],-1);
		c[a[l]]--;
		BIT.update(c[a[l]],1);
		tmp -= 1ll * (BIT.query(n) - BIT.query(c[a[l]]));
	}
	if(tmp >= K)//这里还要多判一次，否则会WA
		ans = min(ans,r - l);
	cout << ans;
	return 0;
}
```

---

## 作者：lilong (赞：0)

首先我们要对 $\sum_{i=1}^W \sum_{j=i+1}^W \min(c_i,c_j)$ 进行化简。具体地，一个 $c_i$ 会产生贡献，当且仅当存在一个 $c_j$ 满足 $c_j \ge c_i$。设这样的 $j$ 的个数为 $d$ 个，那么所产生的贡献为 $c_i \times d$。再枚举每个区间，这样就得到一个 $O(n^2W)$ 的做法，但无法通过本题。

事实上，这样枚举会出现很多冗余。比如一个区间 $[i,j]$ 的绚丽程度已经不小于 $k$，那么 $[i,j+1],[i,j+2],\cdots,[i,n]$ 的绚丽程度都一定是不小于 $k$ 的（出现次数增加，对应的贡献也会增加），但长度显然是前者更优，因此固定 $i$，$j$ 不断右移，一旦出现合法的区间，更新并退出即可。

继续推下去，假设 $[i,j]$ 是以 $i$ 为左端点的最短的合法区间，那么 $[i,j-1]$ 一定是不合法的（出现次数减少，对应的贡献也会减少），即 $[i+1,j-1]$ 一定也是不合法的（原因同上），那么下一个左端点 $i+1$ 确定右端点时直接从上一次的 $j$ 开始枚举即可。显然，$i,j$ 都是只向右移，每个数都被 $i,j$ 各扫到一次。

接下来考虑如何快速计算一个颜色 $a$ 进入或离开区间时的贡献。根据上文的结论，该贡献为 $\sum_{i=1}^W [c_i \ge c_a]\times[i\neq a]$。直接使用树状数组维护即可，具体实现时需要注意边界情况。

总时间复杂度 $O(n\log W)$，代码如下：


```cpp
#include <iostream>
#include <cstdio>
#define int long long
#define MOD 1000000007
#define W 2000000

using namespace std;

int n,k,a[2000001],c[2000001],rk[2000001],rev[2000001],sum,ans,flag;

int t[8000001];

int lowbit( int x )
{
	return x & ( -x );
}

void upd( int x , int y )
{
//	cout << x << ' ' << y << endl;
	for( int i = x ; i <= W ; i += lowbit( i ) )
		t[i] += y;
	return;
}

int que( int x )
{
	int sum = 0;
	for( int i = x ; i >= 1 ; i -= lowbit( i ) )
		sum += t[i];
	return sum;
}

void add( int x )
{
	int gs = que( W ) - que( c[x] );//这里先查询后修改能够规避上文 i = a 的情况
	if( c[x] ) upd( c[x] , -1 );
	c[x] ++;
	upd( c[x] , 1 );
	sum += gs;
}

void del( int x )
{
	int gs = que( W ) - que( c[x] - 1 ) - 1;//减 1 是为了去除自身
	upd( c[x] , -1 );
	c[x] --;
	if( c[x] ) upd( c[x] , 1 );
	sum -= gs;
	return;
}

signed main()
{
	cin >> n >> k;
	ans = 0x3f3f3f3f;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i];
	int i = 1,j = 0;
	while( i <= n )
	{
		
//		cout << i << ' ' << j << endl;
		while( j < n && sum < k ) j ++,add( a[j] );
//		add( a[j] );
		if( sum < k ) break;
//		cout << i << ' ' << j << ' ' << sum << ' ' << c[2] << endl;
		ans = min( ans , j - i + 1 );
		del( a[i] );
		i ++;
	}
	if( ans == 0x3f3f3f3f ) cout << -1;
	else cout << ans;
	return 0;
}
```

---

## 作者：hanchengyi (赞：0)

## 思路

题意很清晰，先考虑暴力解法，枚举 $[l,r]$ 区间，再枚举区间内每两个数，统计答案。

这样显然会超时。观察到题面中是**连续**区间，可以想到用双指针 $l$ 和 $r$，假设我们已经可以快速求出一个区间的答案 $val$，就可以先一直选前面的 $a_l$ 到区间中。如果 $val \ge k$，记录答案，尝试将前面的 $a_l$ 弹出，回到 $val < k$ 并继续扩大区间。

那么问题就变成了怎么求一个区间的答案。因为每次修改区间只有加入一个数和弹出一个数两种操作，所以每次的区间可以由上一次的区间转移。观察式子 $\sum_{i=1}^{W} \sum_{j=i+1}^{W} { \min(c_i,c_j) }$，其中 $c_i$ 在双指针移动时可以顺带统计。那么对于一个新加入的数 $i$，算出对应的 $c_i$，在目前区间内的每一个 $c_j$，与 $c_i$ 的关系只会有大于等于和小于两种情况。

对于区间内小于 $c_i$ 的 $c_j$，答案加上每个这样的 $c_j$ 的和，我们维护 $1$ 到 $c_i-1$ 的和。

对于区间大于等于 $c_i$ 的 $c_j$，答案加上每个这样的 $c_j$ 的数量乘 $c_i$。我们维护 $1 \le c_j \le c_i-1$ 的 $c_j$ 的个数 $sum$ 和总数 $total$，总数减去小于的就是大于等于的，$(total-sum-1) \times c_i$ 即增加的答案。

弹出一个数同理。维护用两个树状数组分别计算两种情况即可，详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define int long long
using namespace std;
const int N=3e6+9;
int n,k;
int a[N];
struct BIT{//树状数组
	int t[N];
	int lowbit(int x){
		return x&(-x);
	}
	
	void modify(int x,int v){
		if(x<=0) return ;
		for(int i=x;i<=n;i+=lowbit(i)) t[i]+=v;
	}
	
	int ask(int x){
		if(x<=0) return 0;
		int ans=0;
		for(int i=x;i>=1;i-=lowbit(i)) ans+=t[i];
		return ans;
	}
	
	int query(int l,int r){
		return ask(r)-ask(l-1);
	}
}T1,T2;
int tot;//有多少不同的数
int val;//区间答案
int f[N];//f[x]记录x的出现次数，也就是c
int ans=INF;//长度答案
bool flag=0;
void Pop(int x){//弹出
	int Times=f[a[x]];
	val-=T1.query(1,Times-1);//小于
	val-=Times*(tot-T2.query(1,Times-1)-1ll);//大于等于
	T1.modify(Times,-Times);
	T2.modify(Times,-1ll);
}
void Push(int x){//加入
	int Times=f[a[x]];
	T1.modify(Times,Times);//小于
	T2.modify(Times,1ll);//大于等于
	val+=T1.query(1,Times-1);
	val+=Times*(tot-T2.query(1,Times-1)-1ll);
}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=1,r=0;//双指针
	val=tot=0;
	while(r<n){
		if(val<k){//继续加入
			r++;
			if(!f[a[r]]) tot++;//第一次出现
			else Pop(r);
			//因为BIT中维护的是f[a[r]]，所以先弹出再加入进去
			f[a[r]]++;//个数+
			Push(r);//加回去
		}
		while(val>=k){//停下了，弹出前面的
			ans=min(ans,r-l+1);//记录答案
			flag=1;
			Pop(l);
			f[a[l]]--;//个数-
			if(!f[a[l]]) tot--;//如果这个数减没了
			else Push(l);//加回去
			l++;
		}
	}
	if(val>=k) ans=min(ans,r-l+1);
	//最后再统计一次，防止最后一直加没统计
	if(!flag) puts("-1");//无解
	else cout<<ans;
	return 0;
}
```

---

## 作者：MutU (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/P11012)

## 思路分析

比赛的时候赶着上飞机没做出来，赛后来看做法还是很明显的。

考虑每个 $c_i$ 会被计算几次贡献。显然，对于每一个 $j$ 使得 $c_j> c_i$，会使 $c_i$ 计入总贡献一次。而对于每一个 $j$ 使得 $c_j=c_i$，如果也计入一次贡献，该贡献会被重复计算两次。所以设 $tmp$ 记录下所有通过等于的方式累加的贡献，计算答案时减掉 $\frac{tmp}{2}$ 即可。

所以我们考虑维护大于某个数的元素的数量，较为简单的做法是树状数组。

## 深入探究

那么考虑如何枚举区间。

显然答案具有单调性，是否可以二分答案？

由此得到做法一（超时）：

>二分长度。对于每个长度 $x$，枚举长度为 $x$ 的所有区间。在转移区间时只需修改与头尾元素有关的贡献就行了。

## Code1（30pts）


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2001000;
int n,k,size[N],a[N],l,r,sum,tmp,size0;
int tree[N],res;
int lowbit(int x){ return x & (-x); }
inline void updata(int x,int d){
	if(x<=0) return;
	int u=x;
	while(u<=n){
		tree[u]+=d;
		u+=lowbit(u);
	}
}
inline int query(int x){
	if(x<0) return 0;
	int u=x,ans=0;
	while(u>0){
		ans+=tree[u];
		u-=lowbit(u);
	}
	return ans+size0;
}
//以上为树状数组部分 
inline void expand(){ //右端点右移一格 
	r++;
	int s1=n-query(size[a[r]]-1)-1,//大于等于的个数 
		s2=n-query(size[a[r]]),    //大于的个数  
		s3=s1-s2;			       //等于的个数 
	sum-=s2*size[a[r]]+s3*size[a[r]];
	tmp-=s3*size[a[r]]*2;
	//减去原本的贡献 
	updata(size[a[r]],-1);
	size[a[r]]++;
	updata(size[a[r]],1);
	if(size[a[r]]==1) size0--;
	s1=n-query(size[a[r]]-1)-1,//大于等于的个数 
	s2=n-query(size[a[r]]),    //大于的个数 
	s3=s1-s2;				   //等于的个数
	sum+=s1*size[a[r]]+s3*size[a[r]];
	tmp+=s3*size[a[r]]*2;
	//加上新的贡献 
	return;
}
inline void shrink(){ //左端点右移一格 
	int s1=n-query(size[a[l]]-1)-1,//大于等于的个数 
		s2=n-query(size[a[l]]),    //大于的个数 
		s3=s1-s2;				   //等于的个数
	sum-=s2*size[a[l]]+s3*size[a[l]]*2;
	tmp-=s3*size[a[l]]*2;
	//减去原本的贡献 
	updata(size[a[l]],-1);
	size[a[l]]--;
	updata(size[a[l]],1);
	if(size[a[l]]==0) size0++;
	s1=n-query(size[a[l]]-1)-1,//大于等于的个数 
	s2=n-query(size[a[l]]),    //大于的个数 
	s3=s1-s2;				   //等于的个数
	sum+=s2*size[a[l]]+s3*size[a[l]];
	tmp+=s3*size[a[l]]*2;
	//加上新的贡献 
	l++;
	return;
}
bool check(int x){ //判断可行性 
	int maxk=0;
	sum=0,tmp=0,size0=n,l=1,r=0;
	memset(size,0,sizeof(size));
	memset(tree,0,sizeof(tree));
	for(int i=1;i<=x;i++) expand();
	for(;r<=n;){
		maxk=max(maxk,sum-(tmp/2));
		if(maxk>=k) return 1;
		expand();
		shrink();
	}
	return (maxk>=k);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	int L=0,R=n;
	res=-1;
	while(L<=R){ //二分答案 
		int mid=L+R>>1;
		if(check(mid)) res=mid,R=mid-1;
		else L=mid+1;
	}
	cout<<res;
	return 0;
} 
```

复杂度带有两个 log，超时四个点。

于是思考是否有二分的必要。

可以发现，用双指针枚举区间也可以得到正确答案。

于是得到了做法二（AC）:

>开两个变量 $l,r$ 表示头尾，若当前区间不符合要求就将 $r$ 右移，否则将 $l$ 右移并记录答案。

## Code（100pts）


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2001000;
int n,k,a[N],size[N],size0;
int l,r;

int tree[N],sum,tmp,res=1e18;
int lowbit(int x){ return x & (-x); }
inline void updata(int x,int d){
	if(x<=0) return;
	int u=x;
	while(u<=n){
		tree[u]+=d;
		u+=lowbit(u);
	}
}
inline int query(int x){
	if(x<0) return 0;
	int u=x,ans=0;
	while(u>0){
		ans+=tree[u];
		u-=lowbit(u);
	}
	return ans+size0; //size0记录为0的个数，记得加上 
}
//以上为树状数组部分 
inline void expand(){ //右端点右移一格 
	r++;
	int s1=n-query(size[a[r]]-1)-1,//大于等于的个数 
		s2=n-query(size[a[r]]),    //大于的个数  
		s3=s1-s2;			       //等于的个数 
	sum-=s2*size[a[r]]+s3*size[a[r]];
	tmp-=s3*size[a[r]]*2;
	//减去原本的贡献 
	updata(size[a[r]],-1);
	size[a[r]]++;
	updata(size[a[r]],1);
	if(size[a[r]]==1) size0--;
	s1=n-query(size[a[r]]-1)-1,//大于等于的个数 
	s2=n-query(size[a[r]]),    //大于的个数 
	s3=s1-s2;				   //等于的个数
	sum+=s1*size[a[r]]+s3*size[a[r]];
	tmp+=s3*size[a[r]]*2;
	//加上新的贡献 
	return;
}
inline void shrink(){ //左端点右移一格 
	int s1=n-query(size[a[l]]-1)-1,//大于等于的个数 
		s2=n-query(size[a[l]]),    //大于的个数 
		s3=s1-s2;				   //等于的个数
	sum-=s2*size[a[l]]+s3*size[a[l]]*2;
	tmp-=s3*size[a[l]]*2;
	//减去原本的贡献 
	updata(size[a[l]],-1);
	size[a[l]]--;
	updata(size[a[l]],1);
	if(size[a[l]]==0) size0++;
	s1=n-query(size[a[l]]-1)-1,//大于等于的个数 
	s2=n-query(size[a[l]]),    //大于的个数 
	s3=s1-s2;				   //等于的个数
	sum+=s2*size[a[l]]+s3*size[a[l]];
	tmp+=s3*size[a[l]]*2;
	//加上新的贡献 
	l++;
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	size0=n;
	for(l=1,r=0;r<=n;){
		if(sum-(tmp/2)>=k){
			res=min(res,r-l+1);
			if(res==0) break;
			shrink();
		}else expand();
	}
	if(res==1e18) cout<<-1;
	else cout<<res;
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：0)

### 题意

给出长度为 $n$ 的序列 $a$。定义一段区间 $[l,r]$ 的绚丽程度 $X_{l,r}$ 为 $\sum_{i=1}^{W} \sum_{j=i+1}^W\min(c_i,c_j)$，其中 $W$ 是值域，$c_i$ 表示 $a$ 序列 $[l,r]$ 中 $i$ 出现的次数，求绚丽程度至少为 $k$ 的区间长度最小值。

### 思路

考虑固定右端点 $r$，对于 $l_1<l_2$ 有 $X_{l_1,r} \ge X_{l_2,r}$。

考虑固定左端点 $l$，对于 $r_1<r_2$ 有 $X_{l,r_1} \le X_{l,r_2}$。

可以使用双指针求出最短的区间 $[l,r]$。

对于每个 $r$，若当前 $[l,r]$ 绚丽程度大于 $k$，$l$ 向右移动直到不能再动，统计答案后，$r$ 向右移动。

我们需要一种快速的方式更新区间的绚丽程度。

由于双指针每次只删除或增加一个数，我们考虑如何快速统计增加或删除一个数的贡献。

对于一个数 $x$，记 $s$ 为小于 $x$ 的数的和，记 $C$ 为在 $[x,W]$ 内的数的个数。

则 $x$ 对绚丽程度的贡献为 $s + (C-1)x$。

因为小于 $x$ 的数和 $x$ 取 $\min$ 结果为本身，大于等于 $x$ 的数和 $x$ 取 $\min$ 结果为 $x$，减 $1$ 是减去 $x$ 本身。

动态维护这些值可以使用权值树状数组或权值线段树。

加入一个数 $num$ 时，删除 $c_{num}$ 的贡献，将 $c_{num}$ 加一，加入 $c_{num}$ 的贡献。

删除一个数 $num$ 时，删除 $c_{num}$ 的贡献，将 $c_{num}$ 减一，加入 $c_{num}$ 的贡献。 

同时动态维护上面的所有值。

开两棵树状数组，一棵维护和，一棵维护个数即可。

时间复杂度：$O(n\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6 + 5;
int n, W, k, a[N], c[N], val;
template <typename T> inline  void read(T& x) {
	x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
}
struct BIT {
	int t[N];
	void clear() {
		memset(t, 0, sizeof(t));
	}
	void add(int x, int y) {
		for (int i = x; i <= W; i += i & (-i)) t[i] += y;
	}
	int query(int x) {
		int res = 0;
		for (int i = x; i; i -= i & (-i)) res += t[i];
		return res;
	}
	int query(int x, int y) {
		return query(y) - query(x - 1);
	}
} T1, T2;
// T1 维护和
// T2 维护个数
int calc(int num) { // num 的贡献
	int res = 0;
	res += T1.query(num - 1);
	res += num * (T2.query(num, W) - 1);
	return res;
}
void del(int num) { // 删数
	val -= calc(c[num]); // 删除旧贡献
	T1.add(c[num], -c[num]); // 维护树状数组
	T2.add(c[num], -1);
	c[num] --; // 更改 c[num]
	if (c[num]) { // 加入新贡献
		T1.add(c[num], c[num]);
		T2.add(c[num], 1);
		val += calc(c[num]);
	}
}
void add(int num) { // 加数
	if (c[num]) { // 删除旧贡献
		val -= calc(c[num]); // 维护树状数组
		T1.add(c[num], -c[num]);
		T2.add(c[num], -1);
	}
	c[num] ++; // 更改 c[num]
	T1.add(c[num], c[num]); // 加入新贡献
	T2.add(c[num], 1);
	val += calc(c[num]);
}
signed main() {
	read(n), read(k);
	for (int i = 1; i <= n; i ++) read(a[i]), W = max(a[i], W);
	int l = 1, res = 1e9;
	for (int i = 1; i <= n; i ++) {
		add(a[i]); // 加入 i
		while (val >= k) { // 向右移动 l
			del(a[l ++]);
			if (val < k) { // 移不动了
				add(a[-- l]);
				break;	
			}
		}
		if (val >= k) res = min(res, i - l + 1); // 统计答案
	}
	if (res == 1e9) cout << -1;
	else cout << res;
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：0)

赛时只想到二分答案但是没有想到双指针。但是也过了。

二分答案和双指针的实现差不多，都是要支持增加进一个值，还有删除掉一个值。所以考虑如何快速增加、删除值并统计这个绚丽程度。

当我们将一个值 $a_i$ 增加进去时，它的出现次数 $c_{a_i}$ 将会 $+1$。这时 $c_{a_i}$ 对答案的贡献就会增加大于等于它本身的 $c$ 值个数（不包括自己）。这样的话可能很容易想到树状数组（我一开始也是树状数组，但是因为我赛时写的二分答案，所以带双 $\log$ 过不了，所以我才想到优化），但是发现这个只有 $+1$，所以可以直接在前缀和上维护。

把一个值删除掉也同理。

以下代码使用双指针+前缀和，总的时间空间复杂度均为 $O(n)$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[2000010],c[2000010],ans=1e9;
int s[2000010];
long long k,sum;
inline long long read()
{
    char c=getchar_unlocked();
    while(c<'0'||c>'9')c=getchar_unlocked();
    long long num=0;
    while(c>='0'&&c<='9')
        num=num*10+(c-'0'),c=getchar_unlocked();
    return num;
}
inline void addval(int x){sum+=s[n]-s[c[x]],s[c[x]]--,c[x]++;}
inline void delval(int x){--c[x],++s[c[x]],sum-=s[n]-s[c[x]];}
int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++)a[i]=read();
    int r=0;
    for(int l=1;l<=n;l++)
    {
        if(l>1)delval(a[l-1]);
        while(r<n&&sum<k)addval(a[++r]);
        if(sum>=k)ans=min(ans,r-l+1);
    }
    if(ans<1e9)printf("%d\n",ans);
    else printf("-1\n");
    return 0;
}
```

---

