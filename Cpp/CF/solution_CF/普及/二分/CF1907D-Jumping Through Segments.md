# Jumping Through Segments

## 题目描述

Polycarp is designing a level for a game. The level consists of $ n $ segments on the number line, where the $ i $ -th segment starts at the point with coordinate $ l_i $ and ends at the point with coordinate $ r_i $ .

The player starts the level at the point with coordinate $ 0 $ . In one move, they can move to any point that is within a distance of no more than $ k $ . After their $ i $ -th move, the player must land within the $ i $ -th segment, that is, at a coordinate $ x $ such that $ l_i \le x \le r_i $ . This means:

- After the first move, they must be inside the first segment (from $ l_1 $ to $ r_1 $ );
- After the second move, they must be inside the second segment (from $ l_2 $ to $ r_2 $ );
- ...
- After the $ n $ -th move, they must be inside the $ n $ -th segment (from $ l_n $ to $ r_n $ ).

The level is considered completed if the player reaches the $ n $ -th segment, following the rules described above. After some thought, Polycarp realized that it is impossible to complete the level with some values of $ k $ .

Polycarp does not want the level to be too easy, so he asks you to determine the minimum integer $ k $ with which it is possible to complete the level.

## 说明/提示

In the third example, the player can make the following moves:

- Move from point $ 0 $ to point $ 5 $ ( $ 3 \le 5 \le 8 $ );
- Move from point $ 5 $ to point $ 10 $ ( $ 10 \le 10 \le 18 $ );
- Move from point $ 10 $ to point $ 7 $ ( $ 6 \le 7 \le 11 $ ).

Note that for the last move, the player could have chosen not to move and still complete the level.

## 样例 #1

### 输入

```
4
5
1 5
3 4
5 6
8 10
0 1
3
0 2
0 1
0 3
3
3 8
10 18
6 11
4
10 20
0 5
15 17
2 2```

### 输出

```
7
0
5
13```

# 题解

## 作者：abensyl (赞：10)

原题：[CF1907D Jumping Through Segments](https://www.luogu.com.cn/problem/CF1907D)。

二分答案好题。

## 思路

一看到最小可行的 $k$ 的这种问题，立刻考虑二分答案。

二分答案是简单的，不过如何检查答案就不那么容易了，因为每次条约长度为 $[-k,k]$ 中任意地正数，所以不容易确定每次跳跃后在区间中的最优点是哪里，导致直接去维护一个位置是比较困难的。

那么就考虑维护区间，假设 $[lef,rig]$ 为现在我们可能在的区间，初始时应当有 $lef=rig=0$，因为一开始在原点。

假如接下来的限制分别为 $[l_1,r_1]\dots[l_n,r_n]$，每次跳跃，我们都可以扩展刚才的 $[lef,rig]$ 区间，扩展成 $[lef-k,rig+k]$，这样的话就相当于是取遍了所有可能到达的点，不过由于每次跳跃之后都应该落在限制的区间内，所以新的可行区间 $[lef,rig]$ 应该变为 $[lef-k,rig+k]\cap[l_i,r_i]$，如果为空集，则说明 $k$ 的长度不够。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
int l[N],r[N];
bool check(int k,int n) {
	int posl=0,posr=0;
	for(int i=1;i<=n;++i) {
		posl=posl-k,posr=posr+k;
		if(posl>r[i]||posr<l[i]) return false;
		posl=max(posl,l[i]),posr=min(posr,r[i]);
	} return true;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--) {
		int n;
		cin>>n;
		for(int i=1;i<=n;++i) cin>>l[i]>>r[i];
		int lef=0,rig=2e9,res;
		while(lef<=rig) {
			int mid=lef+rig>>1;
			if(check(mid,n)) res=mid,rig=mid-1;
			else lef=mid+1;
		} cout<<res<<'\n';
	}
	return 0;
}
```
[我的 AC 记录](https://codeforces.com/contest/1907/submission/235908064)。

---

## 作者：kimidonatsu (赞：3)

题目要求要一个最优可行的 $k$ 值，当然考虑二分搜索。

因为我们需要检查是否可以以 $k$ 的步长通过线段，那么我们就从原点开始，移动 $[0 - k, 0 + k]$，如果可以移动那么开始检查：每次移动时，在左右两个方向上同时移动 $k$ 长度，如果和原线段有交点，说明可行，如果没有则说明不可行；当然，如果在原点上当前的 $k$ 就已经不能移动到相邻的线段上，那么也不可行。

流程其实归纳一下就是三步：枚举 $k$ - 移动 - 判断位置是否在线段上。

```cpp
#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2e5 + 7;

int n;
pair<int, int> a[N];

bool check(int k) {
	int l = 0, r = 0;
	for (int i = 1; i <= n; i++) {
		l = max(l - k, a[i].first);
		r = min(r + k, a[i].second);
		if (l > r) return 0;
	}
	return 1;
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i].first, &a[i].second);

	int l = -1, r = 1e9;
	while (r - l > 1) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid;
	}
	printf("%d\n", r);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
	return 0;
}

```


---

## 作者：lraM41 (赞：1)

思路：二分。判断时记录每次可以跳到的边界，若跳最远也无法抵达目标线段则不符合。跳 $n$ 次若都能跳到目标线段上即是可行的。

~~码风比较丑。将就看就行。~~

```
#include<bits/stdc++.h>
using namespace std;
int n,t,l,r,mid,a[200005],b[200005],s;
bool check(int k){
    int p=0,q=0;
    for(int i=1;i<=n;i++){
        p-=k,q+=k;//一个左边界，一个右边界。
        if(p>b[i]||q<a[i]) return 0;//不符合。
        p=max(p,a[i]),q=min(q,b[i]);//必须跳到线段上。
    }return 1;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i],r=max(r,b[i]);
    l=a[1];
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)) s=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<s<<'\n';
    return;
}
signed main(){
    cin>>t;
    while(t--) solve();
    return 0;
}

---

## 作者：WAis_WonderfulAnswer (赞：1)

## 二分

因为要求最小的 $k$，所以考虑二分。

那么如何判断一个 $k$ 是否合法呢？我们可以维护一个区间 $[l,r]$，表示我们当前可以在的区间范围，因为开始在原点，所以初始我们把 $l,r$ 都赋值为 $0$。

每次跳跃，我们把 $[l,r]$ 区间扩展为 $[l - k,r + k]$，因为每次可以跳 $[ - k,k]$ 之间的距离。假如这是第 $i$ 次跳跃，那么我们需要判断 $[l - k,r + k]$ 与 $[l_i,r_i]$ 区间是否有非空交集，因为第 $i$ 次跳跃必须落在第 $i$ 条线段上。

跳跃之后，我们把 $[l,r]$ 更新成 $[l - k,r + k]$ 与 $[l_i,r_i]$ 的非空交集，即 $l = \max(l - k,l_i)$，$r = \min(r + k,r_i)$。

如果 $l,r$ 更改后，$l > r$，说明 $[l - k,r + k]$ 与 $[l_i,r_i]$ 没有非空交集，也就是第 $i$ 次跳跃无法落在 $[l_i,r_i]$ 上，那么这个 $k$ 一定不符合要求。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int _,n,l[200010],r[200010];
bool check(int k)
{
	int ll=0,rr=0;
	for (int i=1;i<=n;i++)
	{
     //交集
		ll=max(ll-k,l[i]);
		rr=min(rr+k,r[i]);
		if (ll>rr) return false;
	}
	return true;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>_;
	while (_--)
	{
		cin>>n;
		for (int i=1;i<=n;i++) cin>>l[i]>>r[i];
		int l=0,r=1000000000,best=-1;
		while (l<=r)
		{
			int mid=(l+r)/2;
			if (check(mid))
			{
				best=mid;
				r=mid-1;
			}
			else
			{
				l=mid+1;
			}
		}
		cout<<best<<'\n';
	}
	return 0;
}
```



---

## 作者：ATION001 (赞：0)

## 题目描述
有 $n$ 条线段，第 $i$ 条线段范围为 $[l_i,r_i]$，开始时你在位置 $0$，你想跳到 $n$ 条线段上，你想要知道你至少需要跳多远的距离才可以跳到第 $n$ 条线段上。
## 思路
~~一眼二分。~~

其实就是进行移动然后判断是否合法（注意**向左跳和向右跳的情况都需要判断**）。假设你在 $i$ 节点进行移动，判断是否在第 $i+1$ 条线段的范围上。如果不在，就需要移动左端点，否则移动右端点。
### 详细讲解
```cpp
bool code(int k){
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		l-=k,r+=k;
		if(r<kl[i]||kr[i]<l){
			return false;
		}
		l=max(l,kl[i]),r=min(r,kr[i]);
	}
	return true;
}
```
我们二分查找最远需要跳的距离，记作 $k$。$l$ 和 $r$ 分别记录的是跳跃范围的左端点和右端点，每次 $l-k$，$r+k$，判断 $i+1$ 条线段的范围是否有一部分与跳跃的范围重叠，如果没有重叠（即无法跳到相应的范围），那么 $k$ 不满足要求，直接返回 `false`。**全部满足要求**才能返回 `true`。


---


然后奉上我的代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+3;
int t,n,kl[N],kr[N];
bool code(int k){
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		l-=k,r+=k;
		if(r<kl[i]||kr[i]<l){
			return false;
		}
		l=max(l,kl[i]),r=min(r,kr[i]);
	}
	return true;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(cin>>t;t;t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>kl[i]>>kr[i];
		}
		int l=0,r=1e9,mid;
		while(l<=r){
			mid=(l+r)>>1;
			(code(mid)?r=mid-1:l=mid+1);
		}
		cout<<l<<'\n';
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 思路：二分答案

我们可以二分枚举 $k$ 的值。每次看是否可以满足能到达第 $n$ 条线段，如果可以往较小值枚举，否则往较大值枚举。

# code
```cpp
#include <iostream>
using namespace std;
const int N = 2e5 + 10;
int t,n,l,r,mid,ans;
int ll[N],rr[N];
bool check(int x)
{
	int posl = 0,posr = 0;
	for (int i = 1;i <= n;i++)
	{
		posl -= x;
		posr += x;
		if (posl > rr[i] || posr < ll[i]) return false;
		posl = max(posl,ll[i]);
		posr = min(posr,rr[i]);
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1;i <= n;i++)
			cin >> ll[i] >> rr[i];
		l = 0;
		r = 1e9;
		ans = 0;
		while (l <= r)
		{
			mid = (l + r) >> 1;
			if (check(mid))
			{
				r = mid - 1;
				ans = mid;
			}
			else l = mid + 1;
		}
		cout << ans << '\n';
	}
}
```


---

## 作者：kczw (赞：0)

# 题意
一共 $t$ 组数据。

对于每组数据，在一条数轴上，给定 $n$ 个线段，第 $i$ 条线段的范围是 $[l_i,r_i]$。

你从原点开始，每次可以移动 $k$ 的距离，求最小的可以使得你达到第 $n$ 条线段的 $k$ 的值。
# 思路
二分枚举 $k$ 的值。

每次看是否可以满足能到达第 $n$ 条线段，如果可以往较小值枚举，否则往较大值枚举。
# 实现
```cpp
#include<iostream>
#define Min(a,b) a<b?a:b;
#define Max(a,b) a>b?a:b; 
using namespace std;
int t,n,mid,l[200005],r[200005];
bool check(){
	int L=0,R=0;
	for(int i=1;i<=n;i++){
		L-=mid;R+=mid;
		if(L>r[i]||R<l[i])return false;
		R=Min(R,r[i]);
		L=Max(L,l[i]);
	}return true;
}int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d%d",&l[i],&r[i]);
		int ans,lft=0,rgt=1e9;
		while(lft<=rgt){
			mid=(lft+rgt)>>1;
			if(check())ans=mid,rgt=mid-1;
			else lft=mid+1;
		}printf("%d\n",ans);
	}return 0;
}
```

---

## 作者：hjqhs (赞：0)

这场，有种 ABC 的感觉？  
显然二分 $k$，考虑如何 check。  
第一步能跳到 $[-k,k]$，如果和第一段没有交集则失败。否则第二步能跳到 $[l_1-k,r_1+k]$。以此类推即可。  
复杂度 $O(n \log V)$。
```cpp
// Problem: D. Jumping Through Segments
// Contest: Codeforces - Codeforces Round 913 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1907/D
// Memory Limit: 256 MB
// Time Limit: 5000 ms
// Created Time: 2023-12-22 17:41:59
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
typedef long long ll;
typedef unsigned long long ull;

const int N = 200005;
const int INF = 0x3f3f3f3f;

int T;
int n, l[N], r[N], le, ri;

void init() {
	le = ri = 0;
}

bool check(int k) {
	int cl = 0, cr = 0;
	
	rep(i, 1, n) {
		cl -= k, cr += k;
		
		if(cl > r[i] || cr < l[i]) return 1;
		
		cl = max(cl, l[i]), cr = min(cr, r[i]);
	}
	
	return 0;
}

void solve() {
	cin >> n; rep(i, 1, n) cin >> l[i] >> r[i], ri = max(ri, r[i]);
	
	while(le <= ri) {
		int mid = (le + ri) >> 1;
		
		if(check(mid)) le = mid + 1; else ri = mid - 1;
	}
	
	cout << le << '\n';
	
	return;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	cin >> T;
	while(T --) init(), solve();
	
	return 0;
}
```

---

## 作者：zhouruoheng (赞：0)

## Jumping Through Segments

### 题面翻译

数轴上有 $n$ 条线段，第 $i$ 条线段的范围是 $[l_i,r_i]$。

开始时在原点，每次可以跳至多 $k$ 的距离，但是在第 $i$ 次跳跃后一定要站在第 $i$ 条线段上。

求出最小的 $k$ 使得你可以跳到第 $n$ 条线段上。

### 分析

求最小的 $k$ 值，已知上界和下界，不难看出可以用二分答案，重点思考如何进行判断。

考虑每一步可以到达的区间，第一步可到达 $[-k,k]$ 如果和第二段没有交集，那肯定不满足要求，如果有交集说明下一步要从这交集开始跳，于是范围就变为 $[l-k,r+k]$。于是我们只需要一直求交集判断下一步是否有交集直到最后。

总复杂度为 $O(n \log{k})$。

### code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,t,a[N],b[N];
int check(int k)
{
	int l=0,r=0;
	for(int i=1;i<=n;i++)
	{
		l-=k,r+=k;
		if(l>b[i]||r<a[i]) return 1;
		l=max(l,a[i]),r=min(r,b[i]);
	}
	return 0;
}
void solve()
{
	cin>>n;
	int l=0,r=1,mid;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i],r=max(r,b[i]);
	while(l<r)
	{
		mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid;
	}
	cout<<l<<"\n";
}
int main ()
{
	cin>>t;
	while(t--) solve();
	return 0;
}

```


---

## 作者：Dawn_cx (赞：0)

题意：一个坐标轴上有 $n$ 条线段，从原点 $0$ 开始移动 $n$ 次，每次移动到第 $i$ 条线段上，这些移动的最大距离 $\le k$，求 $k$ 的最小值。

二分 $k$，判断 $k$ 是否可行我们通过一个贪心的思想来模拟。

首先对于当前位置 $now$，判断其在目标线段的左侧还是右侧，如果在左侧则要向左移动，在右侧则要向右移动，这两种情况是等价的我们以向右移动为例子。

如果向右移动到目标线段的左侧，发现还可以继续移动，这时我们就维护一个 $l,r$，代表目前可以向左、右走的多余距离。例如上述情况我们的 $l=0,r=$ 剩余的移动距离。

每当我们移动距离$k$发现仍然到不了目标线段时，此时就要用到这个多余距离来判断能否通过上一步剩余的距离来使我们移动到目标线段。

对于当前位置正好在目标线段的情况，向左向右的多余距离分别为该位置到左右端点的距离。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
const ll mod = 998244353;
inline void read(int &x){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch&15);ch=getchar();}
    x=s*w;
}
int n,t,l[N],r[N];
bool check(int x){
    int now=0,suml=0,sumr=0,movl=0,movr=0;
    for(int i=1;i<=n;i++){
        int cnt=0;
        if(now<l[i]){
            cnt=l[i]-now;
            movr=min(r[i]-l[i],x-cnt);
            if(movr<0){
                if(sumr+movr<0)return false;
            }
            sumr+=movr,sumr=min(sumr,r[i]-l[i]),suml=0;
            now=l[i];
        }
        else if(now>r[i]){
            cnt=now-r[i];
            movl=min(r[i]-l[i],x-cnt);
            if(movl<0){
                if(suml+movl<0)return false;
            }
            suml+=movl,suml=min(suml,r[i]-l[i]),sumr=0;
            now=r[i];
        }
        else{
            suml=min(x+suml,now-l[i]),sumr=min(x+sumr,r[i]-now);
        }
    }
    return true;
}
void solve(){
    read(n);
    for(int i=1;i<=n;i++)read(l[i]),read(r[i]);
    int le=0,ri=1e9,mid=0;
    while(le<ri){
        int mid=le+ri>>1;
        if(check(mid))ri=mid;
        else le=mid+1;
    }
    printf("%d\n",ri);
}
int main(){
    read(t);
    while(t--)solve();
    return 0;
}
```


---

