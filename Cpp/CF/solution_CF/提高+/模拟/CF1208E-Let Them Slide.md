# Let Them Slide

## 题目描述

给定 $n$ 个长度可以不同的数组。你还有一个有 $w$ 列、$n$ 行的表格。第 $i$ 个数组水平放在第 $i$ 行。你可以在每一行内滑动该数组，只要它占据若干连续的单元格且完全位于表格内即可。

你需要分别独立地求出每一列 $j$（$1 \leq j \leq w$）的最大整数和。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1208E/66577db70aaef36d98c0a37e28a9702a11eb45eb.png) 上图从左到右分别展示了第 $1$、$2$、$3$ 列的最优放置方式。注意，只要数组仍在窗口内，你可以让某一列不包含某个数组，此时该数组对该列的贡献视为 $0$。

## 说明/提示

第一个样例的示意图见题面。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
3 2 4 8
2 2 5
2 6 3
```

### 输出

```
10 15 16 
```

## 样例 #2

### 输入

```
2 2
2 7 8
1 -8
```

### 输出

```
7 8 
```

# 题解

## 作者：HyperSQ (赞：6)

对于一个特定的列 $j$ ，容易发现，对于第 $i$ 个序列，可滑动选择的区间为 $S=\left[ \max\{1,w-len_i+j\},\min\{len_i,j\} \right]$。由于两个端点在 $j$ 移动的过程中是单调不降的，所以很容易想到一个 $O(nw)$ 的做法：对于每一个序列 $O(w)$ 枚举 $j$ 跑一个单调队列，维护 $S$ 中的最大值。

但不是每一个 $j$ 都需要更新单调队列。

对于 $S$，发现单调队列当且仅当 $w-len_i+j\geq1$ 时更新左端点，$j\leq len_i$ 时才会更新右端点。整理一下，发现需要更新的 $j$ 不超过 $2\times len_i$ 。

因此可以 $O(len)$ 处理每个序列，最终复杂度为线性。

当然，有个细节是可能可以不选择当前序列中的任意一个数，当且仅当序列可以全部挪动到 $j$ 的左边或右边，这体现在 check 函数内。

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define mp make_pair
using namespace std;
 
const int maxn=2e6+5;
int n,w,len,L,R,now;
int que[maxn],a[maxn],val[maxn];
vector<pii> Event[maxn];
long long ans;

void update(int l,int r){
	while(L<=R&&que[L]<l) L++;
	for(int i=now+1;i<=r;i++){
		while(L<=R&&a[que[R]]<a[i]) R--;
		que[++R]=i;
	}now=r;
}
bool check(int len,int j){
	return w-len+1>j||len<j;
}
 
int main(){
	scanf("%d%d",&n,&w);
	for(int i=1;i<=n;i++){
		scanf("%d",&len);
		now=0;
		for(int j=1;j<=len;j++) scanf("%d",&a[j]);
		L=1,R=0;int j=1,ret=0;
		for(j=1;j<=len;j++){
			update(max(1,len-w+j),min(j,len));
			ret=(check(len,j)?max(0,a[que[L]]):a[que[L]]);
			Event[j].push_back(mp(i,ret));
		}
		for(j=max(j,w-len+1);j<=w;j++){
			update(max(1,len-w+j),min(j,len));
			ret=(check(len,j)?max(0,a[que[L]]):a[que[L]]);
			Event[j].push_back(mp(i,ret));
		}
	}
	for(int j=1;j<=w;j++){
		for(int i=0;i<Event[j].size();i++){
			pii p=Event[j][i];
			ans-=val[p.first];ans+=p.second;
			val[p.first]=p.second;
		}printf("%lld ",ans);
	}
}
```

---

## 作者：MicroSun (赞：3)

线段树+思维好题。

考虑分开每一个滑块统计对各列的贡献。明显地，如果该滑块长为 $n$，滑块中的数字为 $a_1 \dots a_n$，表格宽度为 $m$，在不考虑 $0$ 的情况下会对第 $j$ 列做出 $\max\limits_{i=\max\{1,n-m+1\}}^{\min\{n,j\}} a_i$ 的贡献。可以用线段树维护这个 `max` 的式子，写出以下代码：

```cpp
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)
using ll=long long;
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
ll tr[maxn<<2],a[maxn],ans[maxn];
void pushup(int u){tr[u]=max(tr[ls(u)],tr[rs(u)]);}
void build(int u,int l,int r){
	if(l==r){
		tr[u]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls(u),l,mid);
	build(rs(u),mid+1,r);
	pushup(u);
}
ll get(int u,int l,int r,int s,int t){
	if(t<l||r<s) return LLONG_MIN;
	if(s<=l&&r<=t) return tr[u];
	int mid=(l+r)>>1;
	return max(get(ls(u),l,mid,s,t),get(rs(u),mid+1,r,s,t));
}
void solve(){
	int q,m;
	cin>>q>>m;
	while(q--){
		int n;
		cin>>n;
		rep(i,1,n) cin>>a[i];
		build(1,1,n);
		rep(i,1,m){
			ll c=get(1,1,n,max(1,n-m+i),min(n,i));
			if(n-m+i<1||i>n) c=max(c,0ll);
			ans[i]+=c;
		}
	}
	rep(i,1,m) cout<<ans[i]<<" \n"[i==m];
}
```

但是时间复杂度不符合要求。

于是考虑优化：每一行的大部分列都得到了 $\max\limits_{i=1}^n a_i$ 的贡献，只有 $\sum n\le 10^6$ 个元素不是。

考虑再写一个维护 `ans` 的线段树，将这些大部分元素直接区间修改加上 $\max\limits_{i=1}^n a_i$，其他元素逐一处理即可。

Code:

```cpp
// Problem: E. Let Them Slide
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int maxn=1e6+10;

#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
ll a[maxn];
namespace sumt{
ll tr[maxn<<2],tag[maxn<<2];
void pushup(int u){tr[u]=tr[ls(u)]+tr[rs(u)];}
void pd(int u,int l,int r){
	if(tag[u]){
		int mid=(l+r)>>1;
		tag[ls(u)]+=tag[u];
		tag[rs(u)]+=tag[u];
		tr[ls(u)]+=(mid-l+1)*tag[u];
		tr[rs(u)]+=(r-mid)*tag[u];
		tag[u]=0;
	}
}
void upd(int u,int l,int r,int s,int t,int e){
	if(t<s) return;
	if(t<l||r<s) return;
	if(s<=l&&r<=t){
		tag[u]+=e;
		tr[u]+=(r-l+1)*e;
		return;
	}
	pd(u,l,r);
	int mid=(l+r)>>1;
	upd(ls(u),l,mid,s,t,e);
	upd(rs(u),mid+1,r,s,t,e);
	pushup(u);
}
ll get(int u,int l,int r,int s,int t){
	if(t<l||r<s) return 0;
	if(s<=l&&r<=t) return tr[u];
	pd(u,l,r);
	int mid=(l+r)>>1;
	return get(ls(u),l,mid,s,t)+get(rs(u),mid+1,r,s,t);
}
}
//重复部分省略
void solve(){
	int q,m;
	cin>>q>>m;
	while(q--){
		map<int,int> mp;
		int n;
		cin>>n;
		rep(i,1,n) cin>>a[i];
		mxt::build(1,1,n);
		ll mx=mxt::get(1,1,n,1,n);
		if(mx>=0){
			sumt::upd(1,1,m,n,m-n+1,mxt::get(1,1,n,1,n));
			rep(i,1,n-1){
				mp[i]=1;
				ll c=mxt::get(1,1,n,max(1,n-m+i),min(n,i));
				if(n-m+i<1||i>n) c=max(c,0ll);
				sumt::upd(1,1,m,i,i,c);
			}
			rep(i,m-n+2,m){
				if(!mp.count(i)){
					ll c=mxt::get(1,1,n,max(1,n-m+i),min(n,i));
					if(n-m+i<1||i>n) c=max(c,0ll);
					sumt::upd(1,1,m,i,i,c);
				}
			}
		}
		else{
			sumt::upd(1,1,m,1,m-n,0);
			rep(i,m-n+1,m){
				if(!mp.count(i)){
					ll c=mxt::get(1,1,n,max(1,n-m+i),min(n,i));
					if(n-m+i<1||i>n) c=max(c,0ll);
					sumt::upd(1,1,m,i,i,c);
				}
			}
		}
	}
	rep(i,1,m) cout<<sumt::get(1,1,m,i,i)<<" \n"[i==m];
}
```

---

## 作者：tzc_wk (赞：3)

到我的[CSDN博客](https://blog.csdn.net/weixin_43217244/article/details/100103267)里查看效果更佳哦。

[E - Let Them Slide](https://codeforc.es/contest/1208/problem/E)

题意：有$n$个数组和一个长为$w$宽为$n$的矩阵。给出这$n$个数组，现在将这个$n$个数组放在矩阵上，每个数组占用一行，并且每一个数组中的每一个位置都在矩阵范围内。对于第$i$列，我们可以通过合理安排使得这一列中所有元素之和尽可能大，记这个最大值为$s_i$。求出所有$s$的值。

思路：

~~又是一道线段树的题，害得我场上想到但是没时间写了。~~

我们知道，假设我们现在考虑数组$i$，对于大部分$1 \leq j \leq w$，数组$i$中每一个位置放在$j$列上都是合法的，只有少部分不合法。因此我们可以对于每一个数组，先把所有$s_i$加上该数组的最大值（可用线段树求出），部分情况特判一下就可以了。由于所有数组的长度之和不超过$10^6$，需要特判的也不会超过$2 \times 10^6$，最多进行$2 \times 10^6 \times log\ 10^6$次操作，可以在规定时间内求出。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int N,n=1,w,l,a[1000005],ans[1000005],sum;
struct segTree{
	struct node{
		int l,r,val;
	} s[4000005];
	inline void clear(int k,int l,int r){
		s[k].val=0;
		if(l==r){
			return;
		}
		int mid=(l+r)>>1;
		clear(k<<1,l,mid);
		clear(k<<1|1,mid+1,r);
	}
	inline void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;s[k].val=0;
		if(l==r){
			s[k].val=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		s[k].val=max(s[k<<1].val,s[k<<1|1].val);
	}
	inline int query(int k,int l,int r){
		if(l<=s[k].l&&s[k].r<=r){
			return s[k].val;
		}
		int mid=(s[k].l+s[k].r)>>1;
		if(r<=mid)		return query(k<<1,l,r);
		else if(l>mid)	return query(k<<1|1,l,r);
		else			return max(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
	}
} st;
signed main(){
	cin>>N>>w;
	for(int i=1;i<=N;i++){
		st.clear(1,1,n);
		cin>>n;
//		memset(a,0,sizeof(a));
		for(int j=1;j<=n;j++){
			cin>>a[j];
		}
		st.build(1,1,n);
		int mx=max(0ll,st.s[1].val);sum+=mx;
//		cout<<"mx="<<mx<<endl;
		for(int j=1;j<=min(n+2,w);j++){
			int cur=-LLONG_MAX;
			int l=j+n-w,r=j;
			if(l<1)	cur=0,l=1;
			if(r>n)	cur=0,r=n;
			cur=max(cur,st.query(1,l,r));
			ans[j]+=(cur-mx);
		}
		for(int j=w;j>=max(w-(n+1),n+3);j--){
			int cur=-LLONG_MAX;
			int l=j-w+n,r=j;
			if(l<1)	cur=0,l=1;
			if(r>n)	cur=0,r=n;
			cur=max(cur,st.query(1,l,r));
			ans[j]+=(cur-mx);
		}
	}
	for(int i=1;i<=w;i++){
		cout<<sum+ans[i]<<" ";
	}
	return 0;
}
/*
3 3
3 2 4 8
2 2 5
2 6 3
*/
```

---

## 作者：MusicBox (赞：3)

首先，我们发现，第 $i$ 行的木块可以滑动 $w - l[i]$ 的距离，那么，对于第 $j$ 列，它能获得 $[j - (w - l[i]), j]$ 这个区间的数字，我们可以使用滑动窗口解决这个问题，每一行都移动 $w$ 次，复杂度 $O(nw)$。

我们画图，发现，如果 $w$ 远大于 $l[i]$，那么，$w - l[i] > l[i]$ 的情况下，因为窗口大小比数列大小更大，我们中间会有很多次无效的滑动窗口的行动。

显然中间无效滑动的窗口值就是该行所有数字的极值，我们可以通过一个差分数组维护区间加操作，而两边的窗口值，我们可以直接前缀后缀处理最大值，复杂度为 $O(l[i])$。

如果 $w - l[i] < l[i]$，窗口的移动次数是 $w$ 次，而 $w < 2 \cdot l[i]$，复杂度为 $O(l[i])$。

可能有点抽象，分讨的过程建议自己画图理解一下？

分讨一下，复杂度为 $O(\sum l[i])$。

code :

```cpp
/*
 * @Descripttion: 
 * @version: 
 * @Author: Linmobi
 * @Date: 2023-08-11 08:31:23
 * @LastEditors: Linmobi
 * @LastEditTime: 2023-08-12 10:32:46
 */
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull; 
#define rep(i, a, b) for(int i = (a); i <= signed(b); i ++)
#define per(i, a, b) for(int i = (a); i >= signed(b); i --)

using namespace std;

const int P = 1e9 + 7;
const int L = 1e6 + 5;

inline ll qpow(ll a, ll b) { ll ans = 1, q = a; while(b) { if(b & 1) { ans *= q; ans %= P; } q *= q; q %= P; b >>= 1; } return ans; }
inline int read() { int f = 0, x = 1; char ch = getchar(); while(ch < '0' || ch > '9') { if(ch == '-') x = -1; ch = getchar(); } while(ch >= '0' && ch <= '9') { f = (f << 1) + (f << 3) + ch - '0'; ch = getchar(); } return x * f; }

int n, w;

int l[L], ans[L], qs[L];

vector<int> p[L];

deque<pair<int, int> > q;

signed main() {
    n = read(), w = read();
    rep(i, 1, n) {
        l[i] = read();
        rep(j, 1, l[i]) p[i].push_back(read());
    }
    rep(i, 1, n) {
        int lb = w - l[i] + 1;
        if(lb > l[i]) {
            int maxn = 0;
            rep(j, 1, l[i] - 1) {
                maxn = max(maxn, p[i][j - 1]);
                ans[j] += maxn;
            }
            maxn = 0;
            int cnt = 0;
            per(j, l[i], 2) {
                maxn = max(maxn, p[i][j - 1]);
                ans[w - (cnt)] += maxn;
                cnt ++;
            }
            maxn = max(maxn, p[i][0]);
            qs[w - cnt + 1] -= maxn;
            qs[l[i]] += maxn;
        } else {
            q.push_back({0ll, 0ll});
            rep(j, 1, w) {
                int nownum = 0;
                if(j <= l[i]) {
                    nownum = p[i][j - 1];
                }
                // cerr << nownum << endl;
                while(!q.empty() && q.front().first < (j - lb + 1)) q.pop_front();
                while(!q.empty() && q.back().second < nownum) {
                    q.pop_back();
                }
                q.push_back({j, nownum});
                ans[j] += q.front().second;
            }
        }
        while(!q.empty()) q.pop_back();
    }
    rep(i, 1, w) {
        qs[i] += qs[i - 1];
    }
    rep(i, 1, w) {
        ans[i] += qs[i];
    }
    rep(i, 1, w) {
        printf("%lld%c", ans[i], i == w ? ' ': ' ');
    }
    return 0;
} 
```

---

## 作者：Awdrgysxc (赞：2)

[Manthan, Codefest 19 (open for everyone, rated, Div. 1 + Div. 2)A-F](https://blog.csdn.net/zyn_615/article/details/100185305)
## 【Analysis】
#### 从$O(N^3)$到$O(N)$

 - $O(N^3)$ 
 		暴力,对每个格子找最大值，一行一行处理，注意要加上0；
 		
 - $O(N^2logN)$
 	在暴力上用线段树查区间最值（线段树）
 - $O(NlogN)$
    可以发现同一行对很多列的贡献是相同的，可以线段树区间加；（线段树）
 - $O(NlogN)$
 	发现满足单调性，用单调队列,相同的用线段树加；当时只想到了这一步；（单调队列加线段树）
 - $O(N)$
 	继续优化，发现答案只要最后$O(N)$加一下就好了，这样就可以用差分代替线段树了（单调队列加差分）
 
 
 单调队列里的数有两个单调性，一个是权值单调性，二是有效区域单调递增
 ## 【Code】
 
https://www.luogu.org/paste/6xrmxqht


---

## 作者：CC__DIAMOND (赞：1)

本题的所有题解似乎都是单调队列和线段树，然而它其实也可以是一道思维量与细节都很高的**单调栈**好题。  
根据题意，数组不能平移到方框之外，所以对于每个数组的每一个元素，它能够做出贡献的范围是一个区间。如果我们用 $i$ 表示方框中位置的横坐标，用 $x$ 表示元素在数组中的坐标，我们可以推出如果 $x$ 对 $i$ 处的答案有贡献 $i \in [x,x+w-l]$。然而对于同一个位置，每一个数组中只能有一个元素做出贡献。所以我们可以用单调栈扫两次，把较小元素的区间中，和较大元素区间重合的部分去掉。核心代码如下：
```cpp
for (int x = 1; x <= len; ++x) {
            r[x] = x + w - len;
            while (top && v[s[top]] <= v[x]) {
                r[s[top]] = min(r[s[top]], x - 1);
                --top;
            }
            s[++top] = x;
        }
        top = 0;
        for (int x = len; x; --x) {
            l[x] = x;
            while (top && v[s[top]] < v[x]) {
                l[s[top]] = max(l[s[top]], x + w - len + 1);
                --top;
            }
            s[++top] = x;
        }
        top = 0;
```
具体原理就是在单调栈中维护一个严格不递增的序列，在每个元素入栈时把它的左端点设为 $x$ 在每个元素入栈时把所有小于它的元素全部出栈，并尝试用右端点限制左端点，因为比它小的元素右端点只能到比它左端点小 $1$ 的位置，再往右就会与它的区间重合。对于求右端点方法也是一样的，只要把循环倒过来即可。注意 $l$ 对应代码中的 $len$，代码中的 $l$ 代表右端点。在每一轮以后，我们要用每个元素贡献答案中的区间，使用差分维护每次更新即可做到 $\mathcal{O}(1)$ 最后总时间复杂度是 $\mathcal{O}(\sum{l}+n)$。此外，还有两点应当注意，首先数组中小于零的值是不能更新答案中 $[w-l,l]$ 以外的部分（因为这部分以外的答案可以不被数组的任何一部分覆盖，相当于取 $0$，优于负数），其次为了保证区间不重合也不缺少，单调栈的出栈判定必须是一个取等，另一个不取。最后代码如下：
```cpp
// 万能头与IO略（本题输入很大，建议采用快读）
namespace Solution {
constexpr int max_w = 1e6 + 10;
int l[max_w], r[max_w], v[max_w]; // 每个元素的大小于区间
int s[max_w], top = 0; // 手写栈
ll d[max_w]; // 答案的差分数组
void solve() {
    int n, w;
    IO::io.read(n);
    IO::io.read(w);
    for (int i = 1; i <= n; ++i) {
        int len;
        IO::io.read(len);
        for (int i = 1; i <= len; ++i) IO::io.read(v[i]);
        for (int i = 1; i <= len; ++i) {
            r[i] = i + w - len;
            while (top && v[s[top]] <= v[i]) {
                r[s[top]] = min(r[s[top]], i - 1); // 小于等于当前元素的元素贡献的区间最右到 i-1（这里的i其实是x但是懒得改了）
                --top;
            }
            s[++top] = i;
        }
        top = 0;
        for (int i = len; i; --i) {
            l[i] = i;
            while (top && v[s[top]] < v[i]) {
                l[s[top]] = max(l[s[top]], i + w - len + 1);
                --top;
            }
            s[++top] = i;
        }
        top = 0;
        // 数组一定会覆盖的区域，超出的部分负数的贡献无效
        int ml = w - len + 1, mr = len;
        for (int i = 1; i <= len; ++i) {
            if (v[i] < 0) l[i] = max(l[i], ml), r[i] = min(r[i], mr);
            if (l[i] > r[i]) continue;
            d[l[i]] += v[i];
            d[r[i] + 1] -= v[i];
        }
    }
    ll sum = 0;
    for (int i = 1; i <= w; ++i) {
        sum += d[i];
        IO::io.write(sum);
        IO::io.push(' ');
    }
    IO::io.push('\n');
}
}

int main() {
    Solution::solve();
    return 0;
}
```

---

## 作者：licn (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1208E)

对于 $w_i$ 在 $a_i$ 中有一个固定长度的取值范围，会想到单调队列，就用单调队列 $q$ 维护。这个固定的长度 $S$ 是 $w-len_i+1$。

每一次 $i$ 从 $1$ 到 $w$。

当 $q_l<i-S+1$ 时，$l+1$；

当 $a_i \ge a_{q_r}$ 时，$r-1$。

如果枚举到的 $i$ 大于 $len$ 那么 $a_i$ 就是 $0$。

时间复杂度：$O(nw)$。

如何优化？

我们发现 $\sum len_i \le 10^6$，我们只需要枚举到 $len_i$ 后面还没有出队的一个一个出队，每一个出队的覆盖长度也是 $S$。用差分数组给区间 $q_l$ 到 $q_l+S-1$ 增加 $a_{q_l}$。

时间复杂度：$O(\sum len_i)$。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n,w,a[N],d[N],sum;
signed main(){
	scanf("%lld%lld",&n,&w);
	while(n--)
	{
		int len;
		scanf("%lld",&len);
		int k=w-len;
		for(int i=1;i<=len;i++)scanf("%lld",&a[i]);
		int q[N],l=1,r=0;
		a[0]=-1e18;
		for(int i=1;i<=len;i++)
		{
			while(l<=r&&q[l]<i-k)l++;
			while(l<=r&&a[i]>=a[q[r]])r--;
			q[++r]=i;
			int ret;
			if(i<=k)ret=max(0ll,a[q[l]]);
			else ret=a[q[l]];
			d[i]+=ret,d[i+1]-=ret;
		}
		int L=len+1;
		for(;l<=r;l++)
		{
			int R=q[l]+k;
			d[L]+=max(0ll,a[q[l]]),d[R+1]-=max(0ll,a[q[l]]);
			L=R+1;
		}
	}
	for(int i=1;i<=w;i++)sum+=d[i],printf("%lld ",sum);
	return 0;
}

---

## 作者：xukuan (赞：1)

翻译：[https://www.luogu.org/blog/xukuan/translation-cf1208e](https://www.luogu.org/blog/xukuan/translation-cf1208e)

先放一下这题的错解，单调队列不成立的原因

这种方法忽悠了许多人（我在比赛时也是这么想的）

错的原因是单调队列会导致时间复杂度变成$O(n * \sum w)$，TLE#11

放上比赛时的代码：

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
 
ll n,m,sum,a[1000010],ans[1000010];
deque<ll> q;
 
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
	n=read(); m=read();
	for(ll i=1; i<=n; i++){
		sum=read();
		for(ll j=1; j<=sum; j++) a[j]=read();
		while(!q.empty()) q.pop_front();
		for(ll j=1; j<=m; j++){
			while(!q.empty()&&a[j]>=a[q.back()]) q.pop_back();
			if(!q.empty()&&q.front()+m-sum+1<=j) q.pop_front();	
			q.push_back(j);
			if(a[q.front()]>=0||(j>m-sum&&j+m-sum<=m)) ans[j]+=a[q.front()];
		}
		for(ll j=1; j<=sum; j++) a[j]=0;
	}
	for(ll i=1; i<=m; i++){
		write(ans[i]);
		putchar(' ');
	}
	return 0;
}
```

正解：线段树

点信息：每个点的值

区间信息：每个区间的最大值

目标信息：区间$[l,r]$的最大值

对于每个询问，我们加上区间$[1,w]$的最大值，对于部分不符合的进行特判

此外要注意一个位置可能是空的，要视为0

时间复杂度：$O(\sum w*log \sum w)$

代码的输入输出优化与线段树两个部分时常规板子，均不加注释

代码：
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=1000010,INF=2147483647;
ll T,n,m,sum,a[N],ans[N];
struct SegmentTree{
	ll l,r,sum;
}tree[N<<2];

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

inline void clear(ll p){
	tree[p].l=tree[p].r=tree[p].sum=0;
}

inline void clean(ll p){
	if(tree[p].l==tree[p].r){
		clear(p);
		return;
	}
	clear(p);
	clean(p<<1); clean(p<<1|1);
	return;
}

inline void pushup(ll p){
	tree[p].sum=max(tree[p<<1].sum,tree[p<<1|1].sum);
}

void build(ll p,ll l,ll r){
	tree[p].l=l; tree[p].r=r;
	if(l==r){
		tree[p].sum=a[l];
		return;
	}
	ll mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}

ll query(ll p,ll l,ll r){
	if(l<=tree[p].l&&tree[p].r<=r) return tree[p].sum;
	ll mid=(tree[p].l+tree[p].r)>>1,ans=-INF;
	if(l<=mid) ans=max(ans,query(p<<1,l,r));
	if(r>mid) ans=max(ans,query(p<<1|1,l,r));
	return ans;
}

int main(){
	T=read(); m=read();
	while(T--){
		n=read();
		for(ll i=1; i<=n; i++) a[i]=read();
		clean(1);
		build(1,1,n);
		sum+=max(0ll,tree[1].sum);
		for(ll i=1; i<=min(n+2,m); i++){
			ll cur=-INF,l=i+n-m,r=i;
			if(l<1){cur=0;l=1;}//左边可以放空的
			if(r>n){cur=0;r=n;}//右边可以放空的
			cur=max(cur,query(1,l,r));//记下最大值
			ans[i]+=cur-max(0ll,tree[1].sum);//记下差值
		}
		for(ll i=m; i>=max(m-n-1,n+3); i--){//这部分时重复的，我就不写了
			ll cur=-INF,l=i-m+n,r=i;
			if(l<1){cur=0;l=1;}
			if(r>n){cur=0;r=n;}
			cur=max(cur,query(1,l,r));
			ans[i]+=cur-max(0ll,tree[1].sum);
		}
	}
	for(ll i=1; i<=m; i++){
		write(sum+ans[i]);
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：beifa (赞：0)

## 写在最前：
本蒟蒻试图写线段树，但是挂了半天，一直调不出来，在这里感谢 zzy 和 pvz 大佬的指点，直接用差分即可。写篇题解，一是加深印象，二是补充题解区的做法或更详细地分析 ~~（没有用差分的吧）~~。
#### 注意：
前置知识是**差分**和**单调队列**。
## 暴力做法：
### 思路：
时间复杂度 $O(nw)$，直接 T 飞。做法就是单调队列暴力 $1$ 到 $w$，枚举 $n$ 次，注意一个细节就是队列前面先使 $0$ 入队，为了避免滑块都是负数的情况。
### 暴力的 CODE：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int head , tail;
int n , w;  
int ans[1000010] , l[1000010];
int q[1000010];

signed main()
{
    cin >> n >> w;
    for(int i = 1 ; i <= n ; ++i)
    {
        int num;
        cin >> num;
        for(int j = 1 ; j <= num ; ++j)
        {
            cin >> l[j];
        }
        head = 1;
        tail = 1;
        q[1] = 0;
        for(int j = 1 ; j <= w ; ++j)
        {
            while(head <= tail && j-q[head] >= w-num+1) head++;
            while(head <= tail && l[j] >= l[q[tail]]) tail--;
            q[++tail] = j;
            ans[j] += l[q[head]];
        }
        for(int j = 1 ; j <= num ; ++j)
        {
            l[j] = 0;
        }
    }
    for(int i = 1 ; i <= w ; ++i)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
```
显然过不去此题。怎么办呢？
## 正解：
### 思路：

其实很简单，我们发现这样一件事情，滑块的长度之和很小，考虑从这里入手。\
case 1：当滑块的长度 $num\times 2\ge w$，说明滑块占了这一行的一大半，直接暴力即可。\
case 2：当滑块的长度 $num\times 2<w$，说明滑块占的位置很小。显然中间有很大一段最大值是相等的，暴力就挂在这里，没有必要一个一个修改相加，考虑使用差分。

------------

所以最后我们的做法是：\
对于每一行，\
对于 case 1，直接暴力并差分。最多处理 $2\times num$ 次。\
对于 case 2，单调队列暴力处理 $1$ 到 $num$ 和 $w-num+1$ 到 $w$ 的位置并进行差分，这里需要 $2\times num$ 次操作，将 $num+1$ 到 $w-num$ 的位置区间修改差分，这里只需要一次处理。\
最终把 $ans$ 进行前缀和输出即可。
### CODE:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int head , tail;
int n , w;  
int ans[1000010] , l[1000010];//ans表示最终答案，l表示输入的滑块
int q[1000010];//模拟队列，存的是下标

signed main()
{
    cin >> n >> w;
    for(int i = 1 ; i <= n ; ++i)
    {
        int num;
        cin >> num;
        int maxn = -1e17;
        for(int j = 1 ; j <= num ; ++j)
        {
            cin >> l[j];
            maxn = max(maxn,l[j]);
        }
        head = 1;
        tail = 1;
        q[1] = 0;
        if(num*2 >= w)//case1暴力处理
        {
            for(int j = 1 ; j <= w ; ++j)
            {
                while(head <= tail && j-q[head] >= w-num+1) head++;
                while(head <= tail && l[j] >= l[q[tail]]) tail--;
                q[++tail] = j;
                ans[j] += l[q[head]];//差分
                ans[j+1] -= l[q[head]];
            }
        }
        else//case2
        {
            for(int j = 1 ; j <= num ; ++j)//前面一段
            {
                while(head <= tail && j-q[head] >= w-num+1) head++;
                while(head <= tail && l[j] >= l[q[tail]]) tail--;
                q[++tail] = j;
                ans[j] += l[q[head]];
                ans[j+1] -= l[q[head]];
            }

            ans[num+1] += l[q[head]];//中间一段
            ans[w-num+1] -= l[q[head]];

            for(int j = w-num+1 ; j <= w ; ++j)//后面一段
            {
                while(head <= tail && j-q[head] >= w-num+1) head++;
                while(head <= tail && l[j] >= l[q[tail]]) tail--;
                q[++tail] = j;
                ans[j] += l[q[head]];
                ans[j+1] -= l[q[head]];
            }
        }
        for(int j = 1 ; j <= num ; ++j)//数据千万条，清空第一条
        {
            l[j] = 0;
        }
    }
    for(int i = 1 ; i <= w ; ++i)//直接前缀和输出即可
    {
        ans[i] = ans[i-1]+ans[i];
        cout << ans[i] << " ";
    }
    return 0;
}
```

---

## 作者：Leap_Frog (赞：0)

### P.S.
可以不带 $\log$  

### Description.
略  
翻译 $W\rightarrow$ 题解 $n$  
翻译 $n\rightarrow$ 题解 $m$  
翻译 $w\rightarrow$ 题解 $l$  

### Solution.
就长度为 $l$ 的一个窗口它会造成什么样的贡献。  
首先全局一段前缀加上前缀最大值，一段后缀加上后缀最大值，其他加上全局最大值。  
所以我们发现有 $O(l)$ 段区间答案需要单独计算，其他答案相同。  
相当于变成一个区间加，最后全局查问题。  
直接差分就行了，$O(n)$ 的总复杂度。  

然后考虑怎么计算。  
分成两类，第一类是 $2l<n$，这样左边、右边不会互相影响。  
然后就相当于左边加上前缀最大值，右边加上后缀最大值，中间直接差分加全局最大值。  
第二类是 $2l\ge n$，左边、右边的区间有部分重合，需要一个 RMQ。  
此时用四毛子什么的就很不划算，可以直接滑动窗口。  
这样的区间不超过 $2$ 个，所以每次 $O(n)$ 就行了。  

注意考虑一下空序列的情况，就相当于在 $0$ 和 $l+1$ 处塞两个 $0$。  

总复杂度 $O(n+\sum l)$

### Coding.
```
int m,n,a[N],q[N],hd,tl;ll cf[N];
inline void add(int l,int r,ll w) {cf[l]+=w,cf[r+1]-=w;}
int main()
{
	read(m,n);
	for(int C=1,l;C<=m;C++)
	{
		hd=1,tl=0,read(l);for(int i=1;i<=l;i++) read(a[i]);
		int mx=0;for(int i=1;i<=l;i++) mx=max(mx,a[i]);
		int llim=l,rlim=n-l+1;if(llim<rlim)
		{
			add(llim,rlim,mx);int lm=0,rm=0;
			for(int i=1;i<llim;i++) lm=max(lm,a[i]),add(i,i,lm);
			for(int i=n;i>rlim;i--) rm=max(rm,a[i-n+l]),add(i,i,rm);
		}
		else
		{
			q[hd=tl]=0,a[l+1]=0;for(int i=1;i<=n;i++)
			{
				while(hd<=tl&&n-i<l-q[hd]) hd++;
				if(i<=l+1) {while(hd<=tl&&a[q[tl]]<=a[i]) tl--;q[++tl]=i;}
				add(i,i,a[q[hd]]);
			}
		}
	}
	for(int i=1;i<=n;i++) cf[i]+=cf[i-1];
	for(int i=1;i<=n;i++) printf("%lld%c",cf[i],i==n?'\n':' ');
	return 0;
}
```

---

## 作者：foreverlasting (赞：0)

[推销博客](https://foreverlasting1202.github.io/2019/08/27/CF1208%E9%A2%98%E8%A7%A3/)

### E Let Them Slide

题意：有$n$行$m$列的网格，每行有一个长度为$l_i$的可滑动的窗口，窗口上每个位置有个权值。现要你滑动窗口使得每一列的权值和最大（每一列都是独立的，不是同时的），求每一列的最大权值和。$1\leq n,m,\sum_{i=1}^n l_i\leq 10^6,-10^9\leq a_i\leq 10^9$。

做法：考场上胡了一个线段树的做法，因为每个值贡献的区间是连续的，所以想到在线段树上维护时间戳再加上懒标记的做法，然而细节过多，很难写。优秀的做法是讨论$2\ast l_i$与$m$的关系。若$2\ast l_i\leq m$，则说明中间有一块的权值都是相等的，这一段可以在$O(l_i)$的时间里维护出，另外两边都是暴力。若$2\ast l_i>m$，直接线段树维护区间最大值，暴力查找即可。复杂度$O(nlogn)$。

code:
```cpp
//2019.8.27 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define unl __int128
#define eps 5.6e-8
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
//#define pc(x) __builtin_popcountll(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define ull unsigned LL
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
//inline int read() {
//    res s=0,ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
inline int read() {
    res s=0,ch=gc(),w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s*w;
}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline void write(RG unl x){
//    if(x>10)write(x/10);
//    putchar(int(x%10)+'0');
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//clock_t start=clock();
//inline void ck(){
//    if(1.0*(clock()-start)/CLOCKS_PER_SEC>0.1)exit(0);
//}
const int N=1e6+10;
namespace MAIN{
    int n,w;
    LL ans[N],Ans[N];
    int a[N];
    int mx[N<<2];
    void build(res rt,res l,res r){
        if(l==r){mx[rt]=a[l];return;}
        res mid=(l+r)>>1;
        build(rt<<1,l,mid),build(rt<<1|1,mid+1,r),mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
    }
    int querymx(res rt,res l,res r,const res &L,const res &R){
        if(L<=l&&r<=R)return mx[rt];
        res mid=(l+r)>>1;
        if(L<=mid&&R>mid)return max(querymx(rt<<1,l,mid,L,R),querymx(rt<<1|1,mid+1,r,L,R));
        if(L<=mid)return querymx(rt<<1,l,mid,L,R);
        return querymx(rt<<1|1,mid+1,r,L,R);
    }
    inline void MAIN(){
        n=read(),w=read();
        while(n--){
            res l=read();
            for(res i=1;i<=l;i++)a[i]=read();
            if(l*2<=w){
                res mx=0;
                for(res i=1;i<=l;i++)mx=max(a[i],mx),ans[i]+=mx;
                Ans[l+1]+=mx,Ans[w-l+1]-=mx,mx=0;
                for(res i=w;i>=w-l+1;i--)mx=max(mx,a[i+l-w]),ans[i]+=mx;
            }
            else {
                a[l+1]=0,build(1,0,l+1);
                res p=w-l;
                for(res i=1;i<=w;i++)ans[i]+=querymx(1,0,l+1,max(0,i-p),min(i,l+1));
            }
        }
        for(res i=2;i<=w;i++)Ans[i]+=Ans[i-1];
        for(res i=1;i<=w;i++)printf("%lld ",ans[i]+Ans[i]);
    }
}
int main(){
//    srand(19260817);
//    freopen("signin.in","r",stdin);
//    freopen("signin.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

