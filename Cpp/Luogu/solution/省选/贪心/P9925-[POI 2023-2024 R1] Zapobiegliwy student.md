# [POI 2023/2024 R1] Zapobiegliwy student

## 题目背景

译自 [XXXI Olimpiada Informatyczna - I etap](https://sio2.mimuw.edu.pl/c/oi31-1/dashboard/) [Zapobiegliwy student](https://sio2.mimuw.edu.pl/c/oi31-1/p/zap/)。

## 题目描述

考虑如下的一个简单问题：

> 你有 $n$ 个线段在数轴上，你要选出尽量多的线段，使它们两两不交。

我知道你一定会做，但你需要解决这个：

你有 $n$ 个线段在数轴上，你要选出尽量多的线段对 $(u_i,v_i)_{i=1}^k$，即最大化 $k$。

满足 $k+1$ 个要求：

- $u_1,u_2,\cdots,u_k$ 两两不交。
- $v_1,u_2,u_3,\cdots,u_k$ 两两不交。
- $u_1,v_2,u_3,u_4,\cdots,u_k$ 两两不交。
- $\cdots$
- $u_1,u_2,\cdots,u_{k-1},v_k$ 两两不交。

其中 $\forall i$，$u_i$ 与 $v_i$ 不能相同。

## 说明/提示

如果你的第一行正确但是方案不对（可以不输出方案，此时不要有换行），你能得到 $50\%$ 的分数。

如果你的方案合法并且第一行和答案相差不超过 $1$，你能得到 $15\%$ 的分数。

| 子任务编号 | 限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $n\leq3000$ | 40 |
| 2 | $n\leq500000$ | 60 |


## 样例 #1

### 输入

```
8
1 5
3 10
4 8
9 12
11 16
14 15
20 22
15 21
```

### 输出

```
3
1 3
4 6
8 7
```

## 样例 #2

### 输入

```
见附件```

### 输出

```
见附件```

## 样例 #3

### 输入

```
见附件```

### 输出

```
见附件```

# 题解

## 作者：phoenixzhan (赞：3)

设最多可以选出 $t$ 条彼此无交的线段（这是个经典的贪心问题），显然我们可以构造出 $t-1$ 组的方案：任取其中一条线段作为其他 $t-1$ 条线段的 pair，于是只需要判断是否有 $t$ 组的方案。


由于最多可以选出 $t$ 条无交线段，考察最后答案的 $t$ 组线段中，一条线段 $u_i$ 和它的 pair $v_i$，显然 $v_i$ 和 $u_i$ 有交，且 $v_i$ 和 $u_{i-1},u_{i+1}$ 无交。有了这些性质，随便贪一贪就可以了。把所有线段按右端点排序，每次选出两条右端点最小的线段作为 $u$ 和 $v$，即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pii pair<int, int>
#define piii tuple<int, int, int>
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define deb(var) cerr << #var << '=' << (var) << "; "
#define int long long
namespace Loser {
	int n;
	struct Seg {
		int fi, se, id;
	} a[500010]; 
	bool cmp(Seg a, Seg b) {
		return a.se == b.se ? a.fi < b.fi : a.se < b.se;
	}
	int cnt; vector<int> ans;
	int tot; vector<pii> res; 
	void main() {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se, a[i].id = i;
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1, r = 0; i <= n; i++) {
			if (a[i].fi < r) continue;
			cnt++; r = a[i].se; ans.pb(a[i].id);
		}
		int pre = 0;
		for (int i = 1, r = 0, R = 0; i <= n; i++) {
			if (a[i].fi < R) {
				if (a[i].fi >= r && !pre) pre = i; continue;
			}
			int k = i + 1;
			if (pre) {
				k = pre; pre = 0;
				tot++, res.pb(mp(a[i].id, a[k].id)); r = R = a[i].se; continue;
			}
			while (k <= n && a[k].fi < r) k++;
			if (k <= n) tot++, res.pb(mp(a[i].id, a[k].id)); r = a[i].se, R = a[k].se; i = k; 
		}
		deb(cnt), deb(tot);
		if (tot >= cnt) {
			cout << tot << '\n';
			for (auto i: res) cout << i.fi << ' ' << i.se << '\n'; return;
		}
		cout << cnt - 1 << '\n';
		for (int i = 1; i < ans.size(); i++) cout << ans[i] << ' ' << ans[0] << '\n';
	}
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1; while (T--) Loser::main(); return 0;
}

```

---

## 作者：waauto (赞：1)

一个非常典的贪心。

首先先考虑那个非常经典的原问题。

你按照 $r$ 排个序，每次优先取 $r$ 比较小的线段即可。

这样显然是最优的，归纳法可以证明。

由于 $v$ 可以重复，那么此时你有一个操作就是给目前的答案 $-1$，然后输出的时候每一个都指向最后一个线段。

这样你就有了高贵的 $15$ 分。

那么本题最麻烦的部分其实就是如何构造一个方案，满足题意得情况下答案不需要 $-1$。

我们还是考虑原来那个经典的选线段问题。

我们先记录出来要跑出来的答案，我们发现，第一组的线段 $r$ 端点靠左会比较优。

我们同样使用数学归纳法，当确定了前一组的答案，那么后一组显然 $r$ 分别较小会更优一些。

这样我们就得到了一个和第一种问题一样的贪心方式。

那么我们就可以考虑一个类似于双序列扩展那题的做法。

首先把整个序列排个序，跑出第一个答案。

我们维护双指针表示考虑到了多少个线段，我们选了多少线段。

维护两个数组表示你目前选择的答案，每次的时候把 $u$ 丢进第一个数组， $v$ 丢进第二个数组，然后两个数组是一个**相互管辖**的关系，每次贪心的向前跳答案，最后如果第二个数组没装满再把指针减小一个单位。

那么这道题就做完了。

一下是一个参考的代码。

```cpp
#include <bits/stdc++.h>
#define S cerr << "SYT AK IOI" <<endl;
#define M cerr << "MKF AK IOI" <<endl;
#define CONNECT_BASE(x,y) x##y
#define CONNECT(x,y) CONNECT_BASE(x,y)
#define DEBUG_BASE(x) cerr<<#x<<'='<<x<<' '
#define DEB_1(x) DEBUG_BASE(x)
#define DEB_2(x,y) DEB_1(x),DEB_1(y)
#define DEB_3(x,y,z) DEB_1(x),DEB_2(y,z)
#define DEB_4(x,y,z,w) DEB_1(x),DEB_3(y,z,w)
#define DEB_5(a,b,c,d,e) DEB_1(a),DEB_4(b,c,d,e)
#define DEB_6(a,b,c,d,e,f) DEB_1(a),DEB_5(b,c,d,e,f)
#define COUNT_BASE(_1,_2,_3,_4,_5,_6,x,...) x
#define COUNT(...) COUNT_BASE(__VA_ARGS__,6,5,4,3,2,1,0)
#define D(...) std::cerr << "[In Line " << __LINE__ << "]: ",CONNECT(DEB_,COUNT(__VA_ARGS__))(__VA_ARGS__) , cerr << '\n'

using namespace std;
const int N=5e5+5;
struct node{
	int l,r,id;
	bool operator <(const node &x)const{
		if(r==x.r)return l>x.l;
		return r<x.r;
	}
}a[N],c[N];
int b[N<<1];
vector<int>ans;	int n;
vector<node>s;
bool vis[N];
int ao[N];
struct un{
	int l,r,id;
	bool operator <(const un &x)const{
		return l<x.l;
	}
};
int anss[N],nxt[N],r[N],r2[N];
inline bool ck(){
	int l=0;
	r[0]=-1;
	anss[0]=nxt[0]=-1;
	for(int i=1;i<=n;i++){
		if(a[i].l>=r2[l] and anss[l] and nxt[l]){
			l++;
			anss[l]=a[i].id;
			r[l]=a[i].r;
		}
		else if(!nxt[l] and a[i].l>=r[l-1]){
			nxt[l]=a[i].id;
			r2[l]=a[i].r;
		}
	}
	if(!nxt[l])l--;
	if(l!=(int)ans.size())return 0;
	cout<<l<<endl;
	for(int i=1;i<=l;i++)cout<<anss[i]<<" "<<nxt[i]<<endl;
	return 1;
}
int main(){
	cin.tie(nullptr)->sync_with_stdio(false);

	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r,a[i].id=i;
	sort(a+1,a+1+n);
	int pre=-1,d=0;
	for(int i=1;i<=n;i++){
		if(a[i].l>=pre)pre=a[i].r,d++,ans.push_back(a[i].id),vis[a[i].id]=1,s.push_back(a[i]);
	}
	if(ck()){
//		cout<<ans.size()<<endl;
//		for(int i=0;i<(int)ans.size();i++)cout<<ans[i]<<" "<<ao[i]<<endl;
		return 0;
	}
	cout<<ans.size()-1<<endl;
	for(int i=0;i+1<(int)ans.size();i++){
		cout<<ans[i]<<" "<<ans[ans.size()-1]<<endl;
	}
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：1)

## 思路

简单问题就是按右端点排序然后贪心选。

对于本题，按简单问题可以做出一组大小为 $ans$ 的解，然后可以得到一组对于本题的大小为 $ans-1$ 的解，就是去掉一条线段并把它作为所有的 $v$。

本题瘤于简单问题，所以不可能会有大小超过 $ans+1$ 的解，现在我们只需考察是否有大小恰为 $ans$ 的解。

把这 $k$ 对排序，使得 $u_i$ 在 $u_{i+1}$ 的左侧。

有以下性质：

- $v_i$ 交且仅交于 $u_i$。证明就是不交就有 $ans+1$ 大小的解了，交于其他 $u$ 就不是合法的解了。
- $v_i$ 严格地在 $u_{i-1}$ 和 $u_{i+1}$ 之间。
- $u_i$ 严格地在 $u_{i-1},v_{i-1}$ 和 $u_{i+1},v_{i+1}$ 之间。

根据第一条性质，做法就是直接贪心地两个两个选。实现时注意后两条，$u_i$ 受到 $i-1$ 的限制比 $v_i$ 多，也更多地限制 $i+1$。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#define N 500009
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,ans,bns,u[N],v[N];
struct node
{
	int l,r,i;
	inline bool operator<(const node&kkk)const{return r<kkk.r;}
}a[N];
main()
{
	read(n);for(int i=0;i<n;read(a[i].l),read(a[i].r),a[i].i=i+1,++i);
	sort(a,a+n);
	for(int i=0,lst=-1;i<n;++i)if(lst<=a[i].l)++bns,lst=a[i].r;
	for(int i=0,lstu=-1,lstv=-1,thsu,thsv;i<n;++i,u[ans]&&v[ans]&&
		(lstu=thsu,lstv=thsv,++ans))
		if(!u[ans]&&lstu<=a[i].l&&lstv<=a[i].l)u[ans]=a[i].i,thsu=a[i].r;
		else if(!v[ans]&&lstu<=a[i].l)v[ans]=a[i].i,thsv=a[i].r;
	if(ans==bns)
	{
		printf("%d\n",ans);
		for(int i=0;i<ans;printf("%d %d\n",u[i],v[i]),++i);
		return 0;
	}
	ans=0;
	for(int i=0,lst=-1;i<n;++i)if(lst<=a[i].l)u[ans++]=a[i].i,lst=a[i].r;
	for(int i=0;i<ans;v[i++]=u[ans-1]);
	printf("%d\n",ans-1);
	for(int i=0;i<ans-1;printf("%d %d\n",u[i],v[i]),++i);
}
/*
7
1 4
1 4
5 8
6 10
9 15
10 16
10 17

9
1 11
5 21
20 31
25 41
40 51
45 61
60 71
65 81
80 91
*/
```

---

## 作者：Felix72 (赞：0)

不难想到一个可能不优的做法：动态规划求出最大独立线段集合，取其中一条线段为剩下所有线段的替换即可。

接下来考虑到如果存在更优的做法，那么我们一定能给集合里的每一条线段都找到一个“同伴”，使得替换为同伴后与其他线段仍然不交。那么用贪心思想，如果一条线段找不到同伴，就把他在合法的情况下替换为它后面的一条线段，再试一试即可。

如果有线段实在没有找到同伴，或者会跟前后已选定的线段冲突，说明没有更优解了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 500010;
int n;
struct node {int l, r, id;} s[N];
inline bool cmp(node x, node y) {return x.r < y.r;}
int f[N], p[N], rec[N];
int hve[N], tot; bool is[N];
int mate[N], ans[N][2];
inline bool pd(int n1, int n2, int n3, int n4)
{
	return (!(n2 <= n3 || n4 <= n1));
}
int main()
{
	#ifdef LOCAL
	freopen("P9925.in", "r", stdin);
	freopen("P9925.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> s[i].l >> s[i].r, s[i].id = i;
	sort(s + 1, s + n + 1, cmp);
	for(int i = 1; i <= n; ++i)
	{
		f[i] = 1;
		int l = 1, r = i - 1, fin = 0;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(s[mid].r <= s[i].l) fin = mid, l = mid + 1;
			else r = mid - 1;
		}
		f[i] = f[p[fin]] + 1;
		rec[i] = p[fin];
		if(f[i] > f[p[i - 1]]) p[i] = i;
		else p[i] = p[i - 1];
	}
	tot = f[p[n]];
	int pos = p[n];
	while(pos)
	{
		hve[tot] = pos;
		is[pos] = true;
		--tot;
		pos = rec[pos];
	}
	tot = f[p[n]];
	for(int i = 1; i < tot; ++i)
		ans[i][0] = s[hve[i]].id, ans[i][1] = s[hve[tot]].id;
	hve[tot + 1] = n + 1;
	bool flag = true;
	for(int i = 1; i <= tot; ++i)
	{
		for(int j = hve[i] + 1; j < hve[i + 1]; ++j)
		{
			if(pd(s[mate[i - 1]].l, s[mate[i - 1]].r, s[hve[i]].l, s[hve[i]].r))
			{
				hve[i] = j;
				if(!pd(s[hve[i - 1]].l, s[hve[i - 1]].r, s[j - 1].l, s[j - 1].r))
					mate[i] = j - 1;
			}
		}
		if(pd(s[mate[i - 1]].l, s[mate[i - 1]].r, s[hve[i]].l, s[hve[i]].r))
			flag = false;
		if(mate[i]) continue;
		for(int j = hve[i] + 1; j < hve[i + 1]; ++j)
		{
			if(!pd(s[hve[i - 1]].l, s[hve[i - 1]].r, s[j].l, s[j].r))
			{
				mate[i] = j;
				break;
			}
		}
	}
	for(int i = 1; i <= tot; ++i)
	{
		if(hve[i] <= hve[i - 1]) flag = false;
		if(mate[i] == 0)
			flag = false;
		if(pd(s[hve[i]].l, s[hve[i]].r, s[hve[i + 1]].l, s[hve[i + 1]].r)) flag = false;
		if(pd(s[mate[i]].l, s[mate[i]].r, s[hve[i - 1]].l, s[hve[i - 1]].r))
			flag = false;
		if(pd(s[mate[i]].l, s[mate[i]].r, s[hve[i + 1]].l, s[hve[i + 1]].r))
			flag = false;
		if(!pd(s[mate[i]].l, s[mate[i]].r, s[hve[i]].l, s[hve[i]].r))
			flag = false;
	}

	if(flag)
	{
		cout << tot << '\n';
		for(int i = 1; i <= tot; ++i)
			cout << s[hve[i]].id << " " << s[mate[i]].id << '\n';
		return 0;
	}

	cout << tot - 1 << '\n';
	for(int i = 1; i < tot; ++i)
		cout << ans[i][0] << " " << ans[i][1] << '\n';
	return 0;
}
/*
g++ P9925.cpp -o P9925 -std=c++14 -Wall -DLOCAL
./P9925
*/
```

---

