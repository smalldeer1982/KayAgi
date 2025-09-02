# Foe Pairs

## 题目描述

给定一个 $1$ 到 $n$ 数字组成的全排列，同时给定 $m$ 对元素 $(a_i,b_i)$。

你的任务是统计有多少个不同的区间 $(x,y)(1 \le x \le y \le n)$，这些区间不包含任意一个给定的元素对，即不能同时含有元素对 $(a_i,b_i)$ 的两个元素，这两个元素的先后顺序不限定。

## 样例 #1

### 输入

```
4 2
1 3 2 4
3 2
2 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
9 5
9 7 2 3 1 4 6 5 8
1 6
4 5
2 7
7 2
2 7
```

### 输出

```
20
```

# 题解

## 作者：世末OIer (赞：6)

贪心。对于每一对数:
先让a[i]<b[i]

再让r[b[i]]=max(r[b[i]],a[i]+1) //在它前面的靠它最近的不能越过的下标。

最后累加r[i]-a[i]+1即可。

```cpp
using namespace std;
int p[300005],r[300005];
int main(){
	int i,j,n,m,x,y;
	ll rt=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i) scanf("%d",&x),p[x]=i;
	for(i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		x=p[x],y=p[y];
		if(x>y) swap(x,y);
		r[y]=max(r[y],x+1);
	}
	x=1;
	for(i=1;i<=n;++i){
		x=max(x,r[i]);
		rt+=i-x+1;
	}
	printf("%I64d\n",rt);
	return 0;
}
```

---

## 作者：Hurraciny (赞：1)

~~小小问一下，这是怎么给到蓝的~~

# 直入正题

本题需要掌握的算法：Sort 大法、简单双指针、（可能一点点快读？）

看到题目可能有些没有头绪的，直接将所有的对按右端点排序，然后直接枚举以 $i$ 为结尾的区间数，（同时每次将右端点为 $i$ 的对加入）所有加起来就是答案了～。

不难发现，求以第 $i$ 个点为终点的区间数只需求得离当前最近的左端点，再用 $i$ 减去它（应该不用解释了）。

# 做法

- 以右边点的位置为关键字排序
- 从 $1$ 遍历到 $n$
  - &#x20;取右端点小于等于 $i$ 的对的左端点位置中的最大值 $x$。

  - 答案加上 $i-x$。

# 代码

```cpp
#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
#define int long long
namespace IO{
    inline int input(){
        int x = 0;
        bool f = 0;
        char ch = getchar();
        while(!isdigit(ch)){
            if(ch == '-')
                f = 1;
            ch = getchar();
        }
        while(isdigit(ch)){
            x = (x<<1)+(x<<3)+(ch^48);
            ch = getchar();
        }
        if(f)
            x = -x;
        return x;
    }
    inline void print(int x){
        if(x >= 10)
            print(x/10);
        putchar(x%10+'0');
    }

}
using namespace IO;
const int N = 3e5+13;
#define PII pair<int, int>
int n, m;
int a[N];
int pos[N];
PII p[N];
signed main(){
    n = input();
    m = input();
    for(int i = 1; i <= n; i++)
        pos[input()] = i;
    for(int i = 1; i <= m; i++){
        int x = input(), y = input();
        p[i].first = max(pos[x], pos[y]);
        p[i].second = min(pos[x], pos[y]);
    }
    sort(p+1, p+1+m);
    int ptr = 1;
    int ans = 0;
    int maxx = 0;
    for(int i = 1; i <= n; i++){
        while(p[ptr].first <= i && ptr <= m)
            maxx = max(maxx, p[ptr++].second);
        ans += i-(maxx);
    }
    print(ans);
    return 0;
}

```

---

## 作者：UperFicial (赞：1)

感觉我做的比较麻烦。

思路是容斥，因为统计不合法的区间是容易的，因为只要统计区间左右端点包含两次出现位置的情况。

我们统计出每个数对第一次出现和第二次出现的位置，记为左端点和右端点。

然后考虑每一个点作为区间左端点，有多少个区间右端点是不合法的。这里的端点不是上述的端点要注意。

首先我们可以通过左端点排序+双指针可以得到**可能被包含**的一段后缀，显然我们只要找到这个后缀最小的右端点后，右端点右边的点都是不合法的右端点。

最后用总区间数量 $\dfrac{n(n+1)}{2}$ 减去不合法的数量即可。

复杂度 $O(n\log n)$，瓶颈在排序。

```cpp
const int MAXN(3e5+10);

int n,m;
int pos[MAXN];

struct node
{
	int l,r;
};
node a[MAXN];

inline bool cmp(node x,node y)
{
	return x.l<y.l;
}

int minn[MAXN];
ll ans;

int main()
{
    n=read(),m=read();
    rep(i,1,n) pos[read()]=i;
    rep(i,1,m)
    {
    	int x=read(),y=read();
    	a[i].l=pos[x],a[i].r=pos[y];
    	if(a[i].l>a[i].r) Swap(a[i].l,a[i].r);
    }
    sort(a+1,a+1+m,cmp);
    minn[m+1]=INF;
    rev(i,m,1) minn[i]=Min(minn[i+1],a[i].r);
    int tot(1);
    rep(i,1,n)
    {
    	while(a[tot].l<i&&tot<=m) ++tot;
    	if(tot==m+1) break;
    	ans=ans+n-minn[tot]+1;
    }
    printf("%lld\n",1ll*n*(n+1)/2-ans);
    return 0;
}
```

---

## 作者：forever516 (赞：0)

# 题意
题意很清晰，不做过多解释。
# 解法
我的思路是贪心。由题面易看出贪心这类做法（我无法保证每个人都这样想，但至少我是这样想的）对于每一对数，保证单调的
$a_i \le b_i$。再记录遍历到
$i$
的前面靠
$i$
最近的
$i+1$
不能越过的下标，根据我的贪心思路就可以有这条递推式：$r_{b_i}=\max(r_{b_i},a_i+1)$。维护完数组
$r$
后，就很好算了，最后直接累加
$r_i-a_i+1$
即可，这个值就是最终答案。

提交后，事实证明，贪心思路不错，是可以过了这题的。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+10;
ll n,m,x,y,ans=0,p[N],r[N],k=1;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){cin>>x;p[x]=i;}
	for(int i=1;i<=m;++i){
		cin>>x>>y;
		x=p[x];
		y=p[y];
		if(x>y) swap(x,y);
		r[y]=max(r[y],x+1);
	}
	for(int i=1;i<=n;++i){k=max(k,r[i]);ans+=i-k+1;}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiaruize (赞：0)

打duel随机到的题，一开始思路假了一次，感觉比较不牛。

发现目前题解里面的做法好像都是 $\mathcal{O}(n)$ 的预处理，来个直白一点的。

先把每个限制转换为原来数组上的一对 $(l,r)$，这个是容易做到的。

然后考虑正序枚举当前统计的区间的左端点 $L$，因为这些限制，所有右端点 $R$ 一定随着 $L$ 增大而增大，现在要解决如何在改变 $L,R$ 的时候动态维护限制。

对于每个位置 $i$，记录从这个位置出发的限制 $(l,r)$，当且仅当 $i\in [L,R]$ 时，这个限制产生作用，可以用 ``multiset`` 维护。具体来说，当 $R$ 到达当前点时加入限制，在 $L$ 离开时删除，每次 $R$ 与 ``multiset`` 中最小值比较。

几个细节：
1. 注意 $R$ 的上界问题，建议在 ``multiset`` 中压入 $n+1$。
2. 注意每个点可能被多个限制包含，**一定要用 ``multiset``**。
3. 注意 **$N\leq 3\times 10^5$**，不是 $2\times 10 ^5$。

```cpp
const int N = 3e5 + 10;

int n, m;
pii s[N];
int a[N];
int pos[N];
vector<int> vec[N];
multiset<int> st;

void solve()
{
    cin >> n >> m;
    rep(i, 1, n)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }
    rep(i, 1, m) cin >> s[i].first >> s[i].second;
    rep(i, 1, m)
    {
        s[i].first = pos[s[i].first];
        s[i].second = pos[s[i].second];
        if (s[i].first > s[i].second)
            swap(s[i].first, s[i].second);
        vec[s[i].first].push_back(s[i].second);
    }
    int res = 0;
    int cur = 0;
    st.insert(n + 1);
    rep(i, 1, n)
    {
        while (cur < (*st.begin()))
        {
            cur++;
            for (auto v : vec[cur])
                st.insert(v);
        }
        res += cur - i;
        for (auto v : vec[i])
        {
            st.erase(st.find(v));
        }
    }
    cout << res << endl;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF652C)
## 思路
把所有的位置看成一个数轴，再把限制看成线段。那么，问题就变成了求有多少个区间不包含任意一条线段。
## 做法
设 $pos_i$ 为数字 $i$ 的位置，$c_i$ 为位置 $i$ 最远能到的位置。对于任意一条线段，若 $pos_{a_i}$ 大于 $pos_{b_i}$ 则交换 $a_i$ 与 $b_i$。顺便更新 $c_{pos_{b_i}}$。 然后依次枚举右端点，发现区间左端点可以在 $c_i$ 与 $i$ 之间，则答案应该加上 $i - c_i + 1$。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
const I N = 3e5 + 10;
I n,m,a[N],pos[N],b[N],c[N];
LL ans;
struct Info{//每一条限制 
	LL a,b;
	bool operator < (const Info &B){
		if(b == B.b) return a > B.a;
		return b < B.b;
	}
}r[N];
I main(){
	scanf("%d%d",&n,&m);
	for(I i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		pos[a[i]] = i;//ai 的位置 
	}
	for(I i = 1;i <= m;i++){
		I a,b;
		scanf("%d%d",&a,&b);
		r[i].a = pos[a],r[i].b = pos[b];
		if(r[i].a > r[i].b)//需要交换 
			swap(r[i].a,r[i].b);
		c[r[i].b] = max((LL)c[r[i].b],r[i].a + 1);//更新最远的到达位置 
	}
	LL last = 1;//初始最远的位置为 1 
	for(I i = 1;i <= n;i++){
		last = max(last,(LL)c[i]);//继续更新 
		ans += (LL)i - last + 1;//更新答案 
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：cosf (赞：0)

## [CF652C](https://www.luogu.com.cn/problem/CF652C)

这篇题解的做法同样适用于 $p$ 不是全排列且值域不大的情况。

可以用双指针，维护 $l, r$，$r$ 表示以 $l$ 为左端点时右端点最右能是多少。

容易证明，当 $l$ 从左往右转移时，$r$ 也从左往右转移。

当 $r$ 每转一位，就给答案加上 $r - l + 1$，表示以 $r$ 为右端点有多少个可行的子串。

我们再统计两个桶 $vis_i, ban_i$，表示 $i$ 在当前 $p_{l\dots r}$ 中出现了几次，以及 $i$ 与 $p_{l\dots r}$ 中不同的数冲突了几次。

转移 $r$ 时，如果 $ban_{p_{r+1}} = 0$，就可以转移。如果转移过程中使 $vis_{p_r}$ 从 $0$ 变到 $1$，则给和它禁止同时出现的数的 $ban$ 加上一。

转移 $l$ 时，如果 $vis_{p_l}$ 从 $1$ 变到 $0$，则给和它禁止同时出现的数的 $ban$ 减去一。

总体复杂度理论是 $O(nm)$。但由于本题是全排列，时间复杂度降至 $O(n + m)$。

记得开快读或者关同步流，否则再快的算法也拯救不了你。

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 300005

using ll = long long;

int fr[MAXN]; // vis
int vd[MAXN]; // ban

vector<int> e[MAXN];

int a[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	ll res = 0;
	for (int i = 1, j = 0; i <= n; i++)
	{
		while (!vd[a[j + 1]] && j < n)
		{
			j++;
			res += j - i + 1;
			if (!fr[a[j]])
			{
				for (int k : e[a[j]])
				{
					vd[k]++;
				}
			}
			fr[a[j]]++;
		}
		if (j == n)
		{
			break;
		}
		if (fr[a[i]] == 1)
		{
			for (int k : e[a[i]])
			{
				vd[k]--;
			}
		}
		fr[a[i]]--;
	}
	cout << res << endl;
	return 0;
}

```


---

## 作者：DerrickLo (赞：0)

我们先将 $a_i$ 和 $b_i$ 转成位置，设为 $l_i$ 和 $r_i$。

然后按 $l_i$ 从大到小进行排序，接着枚举左端点 $L$，然后右端点一定要小于所有满足 $l_i\ge L$ 的 $r_i$ 中的最小值，这可以动态维护，然后个数就很好算了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,pp[300005],x,minx,ans,now=1;
struct nd{
	int l,r;
	friend bool operator<(const nd&a,const nd&b){
		return a.l>b.l;
	}
}a[300005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m,minx=n;
	for(int i=1;i<=n;i++)cin>>x,pp[x]=i;
	for(int i=1;i<=m;i++)cin>>a[i].l>>a[i].r,a[i].l=pp[a[i].l],a[i].r=pp[a[i].r];
	for(int i=1;i<=m;i++)if(a[i].l>a[i].r)swap(a[i].l,a[i].r);
	sort(a+1,a+m+1);
	for(int i=n;i;i--){
		while(a[now].l==i&&now<=m)minx=min(minx,a[now].r-1),now++;	
		ans+=max(0ll,minx-i+1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑双指针，枚举左端点 $i$，看右端点 $j$ 最多拓展到哪里。

我们对每个点开个 `vector`，存这个点选了之后哪些的另一个不能选。

对于 $j$，如果存在这个点的 `vector` 内的数 $k$ 满足 $i \leq k < j$，那么 $j$ 就不能作为右端点了。我们直接对于每个点的 `vector` 存一下 $<j$ 的最大值，看一下是否大于等于 $i$ 就可以做到拓展时 $O(1)$ 判断了。

```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, a[N], m;
int l[N], r[N];
int pos[N];
vector<int> gg[N];
int maxn[N],minn[N];

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	memset(maxn,0,sizeof maxn);
	memset(minn,0x3f,sizeof minn);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		pos[a[i]]=i;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>l[i]>>r[i];
		gg[pos[r[i]]].emplace_back(pos[l[i]]);
		gg[pos[l[i]]].emplace_back(pos[r[i]]);
	}
	for(int i=1;i<=n;i++)
	{
		for(auto&j:gg[i]) 
		{
			if(j>=i) continue;
			maxn[i]=max(maxn[i],j),minn[i]=min(minn[i],j);
		}
	}
	long long ans=0;
	int j=1;
	for(int i=1;i<=n;i++)
	{
		j=max(j,i);
		while(j<=n)
		{
			if(maxn[j]>=i) goto E;
//			for(auto&k:gg[j])
//			{
//				if(k<j&&k>=i)
//				{
//					goto E;
//				}
//			}
			j++;
		}
		E:;
		ans+=j-i;
	//	cout<<"!!!: " << i << " " << j << "\n";
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

首先完成一个全排列的映射，将全排列转化为一个从 $1$ 开始的公差为 $1$ 的等差数列。

然后用尺取法做，约束条件放到大的那一个那边存下来，每一次将左指针移动到最左边满足条件的地方，但此时一个点可能有多个约束条件，不好处理。

这时发现有在映射后，一些约束条件是严格没用的，也就是当约束条件的前一个小于另一个的前一个。那么后一个限制满足时前一个限制一定满足，但前一个限制满足时后一个限制并不一定满足，这也就是映射的意义所在。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,p[300005],po[300005],x,y,l,r;
long long ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		po[x]=i;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		p[max(po[x],po[y])]=max(p[max(po[x],po[y])],min(po[x],po[y]));
	}
	l=1;
	while(r<n){
		r++;
		l=max(l,p[r]+1);
		ans+=(long long)(r-l+1);
	}
	printf("%I64d",ans);
	return 0;
}
```


---

