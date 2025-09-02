# Outstanding Impressionist

## 题目描述

Eric 仍然记得整数数组形式的 $n$ 个印象。他将它们记录为 $w_1,w_2,\ldots,w_n$ 。然而，他对印象的记忆力很差。对于每个 $1\leq i\leq n$ ，他只能记住 $ l_i \leq w_i \leq r_i $ 。

Eric 认为，印象 $i$ 是唯一的，当且仅当存在一个可能的数组 $w_1,w_2,\ldots,w_n$ ，使得 $w_i\neq w_j$ 对所有具有 $j\neq i$ 的 $1\leq j\leq n$ 都成立。

请帮助 Eric 确定印象 $i$ 是否对每个 $1\leq i\leq n$ 是唯一的，对每个 $i$ 是独立的。也许你的判断可以帮助改写最后的故事。

## 样例 #1

### 输入

```
5
2
1 1
1 1
4
1 3
1 3
1 3
1 3
6
3 6
2 2
1 2
1 1
3 4
2 2
7
3 4
4 4
4 4
1 3
2 5
1 4
2 2
3
4 5
4 4
5 5```

### 输出

```
00
1111
100110
1001111
011```

# 题解

## 作者：zhangzirui66 (赞：3)

首先观察到对于每个记忆只需满足它是独特的，所以当我们选择一个值时，除了 $l=r$ 的所有记忆都能躲开它，当 $l=r$ 时，记录一次 $l$ 即可。

预处理每个记忆类型到 $f$ 数组后（题面中限制了 $1 \le l,r \le 2\times n$），我们就得到了一个很有前途的 $O(n^2)$ 做法。

第二层循环枚举的是有无可行的记忆类型，其实可以对 $f$ 数组做前缀和，检查 $f_r-f_{l-1}$ 是否为 $0$，若为 $0$，说明 $l$ 和 $r$ 之间没有一个可行点，输出 $0$，否则可行，输出 $1$。

代码不算复杂：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[200005], b[200005], f[400005], now;
map<int, int> mp;
int main(){
	cin >> t;
	while(t --){
		cin >> n;
		mp.clear();
		for(int i = 1; i <= n; i ++) cin >> a[i] >> b[i];
		for(int i = 0; i <= n * 2; i ++) f[i] = 1;//复制为均可
		for(int i = 1; i <= n; i ++){
			if(a[i] == b[i]) mp[a[i]] ++;//此数不可行
		}
		for(int i = 1; i <= 2 * n; i ++){
			if(mp[i]) f[i] = 0;//标记上不可行
		}
		for(int i = 1; i <= 2 * n; i ++) f[i] += f[i - 1];//做前缀和
		for(int i = 1; i <= n; i ++){
			if((a[i] == b[i] && mp[a[i]] == 1) || f[b[i]] - f[a[i] - 1]) cout << 1;//前半部分特判了一下，如果只有它一个只包含 a[i]，也是可以的
			else cout << 0;
		}
		cout << "\n";
	}
	return 0;
}
```
警示后人，$f$ 数组要开两倍空间，否则 WA on #8。

---

## 作者：Sakura_Emilia (赞：2)

# Solution

由于这道题涉及到处理区间问题，其实可以直接无脑树状数组。

对于每个位于第 $i$ 个位置的数，其他数只需要和第 $i$ 个位置的数不同即可，这些其他位置的数内部可以有相等。因此在整个问题中，发挥决定性因素的，是那些取值唯一的数。只需要找出所有取值唯一的数，将其放置在数轴上标记该值所在的位置。之后遍历所有区间，检查该区间是否存在没有被标记的空缺。这个过程使用树状数组的区间查询很容易实现。

最后特别处理一下当遍历到取值唯一的区间的情形即可。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
#define el else
#define wl while
#define rt return
#define il inline
#define br cout << endl;
using namespace std;
const int N = 1e6 + 8;

int T, n, ll[N], rr[N];
int tr[N];
map<int, int> st;

il void init() {
    for(int i = 0; i <= 2 * n; i++)
        tr[i] = 0;
    st.clear();
}

il int lowBit(int x) {
    return x & (-x);
}

il void add(int x) {
    for(int i = x; i <= 2 * n; i += lowBit(i))
        tr[i] += 1;
}

il int sum(int x) {
    int res = 0;
    for(int i = x; i; i -= lowBit(i))
        res += tr[i];
    return res;
}

il bool ok(int l, int r) {
    return sum(r) - sum(l - 1) != r - l + 1;
}

il void solve() {
    init();
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> ll[i] >> rr[i];
        if(ll[i] == rr[i]) {
            if(st[ll[i]] == 0)
                add(ll[i]);
            st[ll[i]]++;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(ll[i] == rr[i]) {
            if(st[ll[i]] == 1)
                cout << '1';
            el
                cout << '0';
        } el {
            if(ok(ll[i], rr[i]))
                cout << '1';
            el
                cout << '0';
        }
    }
    br
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    wl(T--)
        solve();

    rt 0;
}
```

---

## 作者：Autumn_Rain (赞：1)

题面翻译。

有 $t$ 组数据。有 $n$ 个限制 $l,r$。问对于所有 $i$，能否构造出长为 $n$ 的数组 $w$ 使得:

1. 对于所有 $1 \le j \le n$，有 $l_j \le w_j \le r_j$。

2. $w_i$ 与数组中其它数均不相等。

可以输出 $1$，不可以输出 $0$。

---

思路。

我们把 $l_i=r_i$ 这种情况称为一个点。$l_i \ne r_i$ 的情况称作一条线。若一个数不与数组中其它值重复，那么我们称它是唯一的。

考虑暴力，对于每个 $1\le i\le n$，对于每个 $l_i\le x\le r_i$，我们想一一枚举 $x$，并检查位置 $i$ 的值为 $x$ 时是否是唯一的，即和其它数都不相等。这样显然会超时。



对于每个 $j≠i$，如果限制是一条线，我们总可以将 $w_j$ 切换为与 $x$ 不同的值，也就是线上另外一些点。因此，当且仅当现在限制是点，而且存在一个不同的点和当前点覆盖值相同时才会重复。

用 $a_i$ 记录覆盖在 $i$ 上不同**点**（不是线）的数量。如果 $i$ 限制是一条线，那么当且仅当对于所有 $l_i\le x\le r_i$ 都有 $a_x\ge 1$ 时位置 $i$ 才不是唯一的。也就是线上所有点都被固定点占据了。



---



关于这里我曾经问过一个很唐的问题。感谢 [@Le0Chan](https://www.luogu.com.cn/user/1024338) 的解答。现在帖子由于太唐被我删了。节选一段问答供参考（有删改）。

Q：对于限制是一条线的情况，有没有可能即使没有点覆盖在线上，但是有很多完全包含在内的线，通过种种限制，覆盖整条线呢？我就是不知道，会不会这些线把 $w_i$ 的所有可能取值都覆盖，但是题解代码只判了点。我好奇怎么证明正确性。

A：不可能，反证：第一步是先选定定一个符合要求的点作为 $w_i$。假设存在 $j$ 使得此时 $w_j=w_i$，因为 $j$ 的范围是区间，则任意将 $w_j$ 左移或者右移都可以使其不等于 $w_i$。

所以是正确的。


---



当 $i$ 的限制是一个点时，当且仅当 $a_{l_i}≥2$ 时，它不能是唯一的。这个 $2$ 一次是自己，一次是别人占据，所以重复了。

所有这些都可以在前缀和内快速检查，因此总时间复杂度为 $O(\sum n)$。



---

代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
#define ll long long
int n;
const int N=4e5+10;
int l[N],r[N];
int a[N],s[N];
void solve(){
	cin>>n;
	for(int i=1;i<=2*n;i++){
		s[i]=a[i]=0;
	}
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
		if(l[i]==r[i]){
			s[l[i]]=1;
			a[l[i]]++;
		}
	}
	for(int i=1;i<=2*n;i++){
		s[i]+=s[i-1]; 
	}
	for(int i=1;i<=n;i++){
		if(l[i]==r[i]){
			if(a[l[i]]==1)cout<<1;
			else cout<<0;
		}
		else{
			if(s[r[i]]-s[l[i]-1]==r[i]-l[i]+1){
				cout<<0;
			}
			else cout<<1;
		}
	}
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	int T;	
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
} 
```

---

## 作者：lalaji2010 (赞：1)

# CF2053B Outstanding Impressionist

## 分析

对于第 $i$ 个位置，我们可以选择将其设置为 $[l_i,r_i]$ 区间中的任意一个数字，我们想要让其他的位置都不设置为当前位置 $i$ 设置的数，看是否可行。

显然，当前位置 $i$ 不可行当且仅当 $[l_i,r_i]$ 中的每一个数字，都有至少一个其他的位置**必须**填；即 $\forall j \in [l_i,r_i]$，存在一个位置 $k$，满足 $1 \leq k \leq n,k \neq i,l_k=r_k=j$。

然后我们对于每一个形如 $l_x=r_x$ 的限制进行标记，令 $d[l_x]=1$，令 $c[l_x]$ 自增 $1$，然后前缀和处理就能在后面对于每一个位置的取值区间 $O(1)$ 地来判断区间中的数字是否都被其他位置必须填。特别地，若某一个位置 $i$ 满足 $l_i=r_i$，则特殊处理，判断 $c[l_i]$ 是否大于等于 $2$ 即可。

记得数组用多少清多少，不要使用 memset。

代码是赛时写的，有点丑，见谅。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,a[200005],b[200005],c[500005],d[500005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int mx=0;
		for(int i=0;i<=2*n;i++){
			c[i]=0;
			d[i]=0;
		} 
		for(int i=1;i<=n;i++){
			cin>>a[i]>>b[i];
			if(a[i]==b[i]){
				d[a[i]]=1;
				c[a[i]]++;
				mx=max(mx,a[i]);
			}
		}
		for(int i=1;i<=mx;i++){
			c[i]=c[i-1]+c[i];
			d[i]=d[i-1]+d[i];
		}
		for(int i=1;i<=n;i++){
			if((a[i]!=b[i]&&d[b[i]]-d[a[i]-1]>=b[i]-a[i]+1)||(a[i]==b[i]&&c[b[i]]-c[a[i]-1]-1>=b[i]-a[i]+1)) cout<<0;
			else cout<<1;
		}
		puts("");
	}
	return 0;
} 
```

---

## 作者：Cute_yhb (赞：1)

哦对啦！有个小秘密，如果区间 $[l_i,r_i]$ 中的 $l_i=r_i$，那么这个区间的元素的值就确定啦！必须等于 $l_i$！如果 $l_i < r_i$，那就不一定哦~

可以给每个位置一个小标记数组 $v_i$，如果 $v_i=1$，就说明有一个区间 $[l_j, r_j]$，而且 $l_j=r_j=v_i$。如果没有这样的区间，就 $v_i=0$ 啦~

接下来我们只要维护每个区间 $[l_i,r_i]$，并检查它是否符合规定！哇~ 这能通过线段树来做哦！首先，把所有 $l_i=r_i$ 的区间标记一下，然后对每个区间 $[l_i,r_i]$，如果 $l_i=r_i$，就小小地修改一下它的值，然后检查每个位置是不是都被标记啦！你看看，这样时间复杂度就是 $O(n)$ 或 $O(n\log n)$，好简单~(｡♥‿♥｡)

---

## 作者：linch (赞：1)

## Problem
有一个长度为 $n$ 的整数序列 $w$，对于每一个 $1\le i\le n$，都要满足 $l_i \le w_i \le r_i$。对于每个 $1\le i\le n$，求出是否有一种可能的序列 $w$ 使得 $w_i \ne w_j$ 对于每个 $1\le j \le n$ 成立。询问之间相互独立。

## Solution
设当前正在对第 $i$ 个数进行询问。

容易发现，当 $l_j \ne r_j$ 时，$w_j$ 可以取多个数，不会对答案造成影响。因为此时哪怕该数取值区间 $[l_j,r_j]$ 和询问的数取值区间 $[l_i,r_i]$ 重合，也肯定可以满足 $w_i \ne w_j$，那么我们就不需要考虑这种情况。

接下来考虑 $l_j=r_j$ 的情况。此时 $w_j$ 必须要取一个确定的数 $l_j$。容易发现，**当询问数 $w_i$ 的取值区间 $[l_i,r_i]$ 中所有数都被确定必须要取**，就不符合题意了。

但是直接用数组标记是否被确定必须要取，在询问时遍历 $[l_i,r_i]$，时间复杂度过高，考虑优化。

尝试使用前缀和数组 $pre_j$ 记录区间 $[1,j]$ 内的数字必须要取的数量。询问时计算 $[l_i,r_i]$ 内必须要取的数字个数即可。

对于被询问数 $w_i$，注意特判只有 $i$ 存在 $l_i = r_i$ 的情况。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+10;
int t,n,l[maxn],r[maxn],pre[maxn],cnt[maxn];
void init(){
	for(int i=1;i<=2*n;i++) cnt[i]=0;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		init();
		for(int i=1;i<=n;i++){
			cin>>l[i]>>r[i];
			if(l[i]==r[i]) cnt[l[i]]++;
		}
		for(int i=1;i<=2*n;i++){
			pre[i]=pre[i-1]+(cnt[i]>0);
		}
		for(int i=1;i<=n;i++){
			int k=pre[r[i]]-pre[l[i]-1];
			if(l[i]==r[i] && cnt[l[i]]==1) k--;
			if(k==r[i]-l[i]+1) cout<<"0";
			else cout<<"1";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：banned_gutongxing (赞：1)

对于这道题，手玩样例后发现：

- 对于 $l_i=r_i$ 的，只要不存在 $j\in[1,n]$  且 $j\neq i$ 满足 $l_j=r_j=l_i$，答案就是 `0`。否则都是 `1`。
- 对于 $l_i\neq r_i$ 的。考虑其他所有的 $j$。
  - 如果 $l_j<l_i$，此时我们直接让他是 $l_j$ 即可，没有任何贡献。
  - 如果 $r_j>r_i$，此时我们直接让他是 $r_j$ 即可，亦没有贡献。
  - 否则包含。考虑区间里面的所有值 $k\in[l_i,r_i]$ 都存在 $l_j=r_j=k(j\in[1,n],j\neq i)$，那么肯定为 `0`。否则就一定会出现有一个值 $p$ 不存在任何 $l_j=r_j=k(j\in[1,n],j\neq i)$，对于一个区间与 $p$ 相交，那么直接取不相交部分即可，此时输出 `1`。

快速判断区间是否被完全覆盖，直接使用线段树即可。

## 代码
```cpp
// Problem: B. Outstanding Impressionist
// Contest: Codeforces - Good Bye 2024: 2025 is NEAR
// URL: https://codeforces.com/contest/2053/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');}
	}
	void write(int x,char y){write(x);write(y);}
	#ifndef int
	void read(long long &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void write(long long x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');}
	}
	void write(long long x,char y){write(x);write(y);}
	#endif
	const int MAXN = 4e5+10;
	struct segmentree{
		int l,r;
		int cover;
		int tot;
	}tree[MAXN<<3];
	void pushup(int k){
		tree[k].cover = (tree[k*2].cover&&tree[k*2+1].cover);
	}
	void build(int k,int l,int r){
		tree[k].l = l;
		tree[k].r = r;
		tree[k].tot = 0;
		tree[k].cover = 0;
		if(tree[k].l==tree[k].r) return;
		int mid = (l+r)>>1;
		build(k*2,l,mid);
		build(k*2+1,mid+1,r);
	}
	void modify(int k,int x,int y){
		if(tree[k].l>x||tree[k].r<x) return;
		if(tree[k].l==x&&tree[k].r==x){
			tree[k].tot += y;
			tree[k].cover = 1;
			return ;
		}
		modify(k*2,x,y);
		modify(k*2+1,x,y);
		pushup(k);
	}
	bool pd(int k,int l,int r){
		if(tree[k].l>r||tree[k].r<l) return 1;
		if(tree[k].l>=l&&tree[k].r<=r){
			return tree[k].cover;
		}
		return pd(k*2,l,r)&&pd(k*2+1,l,r);
	}
	int get(int k,int x){
		if(tree[k].l>x||tree[k].r<x) return 0;
		if(tree[k].l==x&&tree[k].r==x){
			
			return tree[k].tot;
		}
		return get(k*2,x)+
		get(k*2+1,x);
		
	}
	int n;
	int l[MAXN],r[MAXN];
	signed main(){
		read(n);
		build(1,1,2*n);
		for(int i = 1;i<=n;i++){
			read(l[i]);read(r[i]);
			if(l[i]==r[i]) modify(1,l[i],1);
		}
		for(int i = 1;i<=n;i++){
			if(l[i]==r[i]){
				if(get(1,l[i])>1) write(0);
				else write(1);
			}else write(!(int)pd(1,l[i],r[i]));
		}
		write(endl);
		return 0;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

首先容易得到一个结论：若任何一个数的取值区间长度大于 $1$，则无论等轴设定为任何一个数，这个数都可以避开。

所以判断可行性的方案显然。当且仅当对于任何 $l_i\le x\le r_i$ 满足 $\exist j\neq i\space l_j=r_j=x$ 时 $i$ 不可能独特，否则可以独特。

容易使用前缀和优化判断过程。

时间复杂度 $O(n+V)$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <chrono>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 4e5 + 10;
int n, dv[N], l[N], r[N], cnt[N];
void init_global()
{
}
void init_local()
{
	scanf("%d", &n);
	memset(dv + 1, 0, n << 3);
	memset(cnt + 1, 0, n << 3);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", l + i, r + i);
		if (l[i] == r[i])
			dv[l[i]] = true, cnt[l[i]]++;
	}
}
void run()
{
	for (int i = 1; i <= 2 * n; i++)
		dv[i] += dv[i - 1];
	for (int i = 1; i <= n; i++)
	{
		if (l[i] == r[i])
		{
			putchar(cnt[l[i]] == 1 ? '1' : '0');
			continue;
		}
		putchar(dv[r[i]] - dv[l[i] - 1] == r[i] - l[i] + 1 ? '0' : '1');
	}
	putchar('\n');
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	scanf("%d", &T);
	init_global();
	while (T--)
	{
		init_local();
		run();
	}
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：_lmh_ (赞：0)

显然只有 $l=r$ 的情况是有意义的（否则不管选什么数，总有和它不相等的选择），所以开一个 $a_i$ 代表是否存在 $l=r=i$ 的位置，和 $c_i$ 代表 $l=r=i$ 的数量。

判断 $l=r$ 的情况是简单的，只有一种选择，所以只需要看是否 $c_l=1$ 即可。（此时自己已经对 $c$ 做出了一个贡献）

否则，需要满足至少有一个 $l\le i\le r$ 使得 $a_i=0$，对其做前缀和即可快速判断。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lson (u<<1)
#define rson (u<<1|1)
const ll N=400007;
ll T,n,m,l[N],r[N],a[N],cnt[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;m=n<<1;for (int i=1;i<=m;++i) a[i]=cnt[i]=0;
		for (int i=1;i<=n;++i){
			cin>>l[i]>>r[i];
			if (l[i]==r[i]){a[l[i]]=1;cnt[l[i]]++;}
		}
		for (int i=1;i<=m;++i) a[i]+=a[i-1];
		for (int i=1;i<=n;++i){
			if (l[i]==r[i]) cout<<(cnt[l[i]]==1);
			else cout<<(a[r[i]]-a[l[i]-1]!=r[i]-l[i]+1);
		}
		cout<<'\n';
	}
	return 0;
}
```

---

