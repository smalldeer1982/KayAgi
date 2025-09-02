# [ABC223H] Xor Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc223/tasks/abc223_h

長さ $ N $ の正整数列 $ A\ =\ (A_1,\ \dots,\ A_N) $ が与えられます。

$ Q $ 個のクエリを処理してください。$ i\ \,\ (1\ \leq\ i\ \leq\ Q) $ 番目のクエリでは、$ A_{L_i},\ A_{L_i\ +\ 1},\ \dots,\ A_{R_i} $ から $ 1 $ つ以上の要素を選び、それらの排他的論理和を $ X_i $ にできるかどうか判定してください。

 排他的論理和とは 整数 $ a,\ b $ のビットごとの排他的論理和 $ a\ \mathrm{xor}\ b $ は、以下のように定義されます。

- $ a\ \mathrm{xor}\ b $ を二進表記した際の $ 2^k\ \,\ (k\ \geq\ 0) $ の位の数は、$ a,\ b $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \mathrm{xor}\ 5\ =\ 6 $ となります（二進表記すると: $ 011\ \mathrm{xor}\ 101\ =\ 110 $）。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 4\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \lt\ 2^{60} $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ 1\ \leq\ X_i\ \lt\ 2^{60} $
- 入力は全て整数である。

### Sample Explanation 1

$ 1 $ つ目のクエリでは、$ A_1,\ A_3 $ を選ぶことで排他的論理和を $ 7 $ にすることができます。 $ 2 $ つ目のクエリでは、どのように要素を選んでも排他的論理和を $ 7 $ にすることはできません。

## 样例 #1

### 输入

```
5 2
3 1 4 1 5
1 3 7
2 5 7```

### 输出

```
Yes
No```

## 样例 #2

### 输入

```
10 10
8 45 56 9 38 28 33 5 15 19
10 10 53
3 8 60
1 10 29
5 7 62
3 7 51
8 8 52
1 4 60
6 8 32
4 8 58
5 9 2```

### 输出

```
No
No
Yes
No
Yes
No
No
No
Yes
Yes```

# 题解

## 作者：L_zaa_L (赞：8)

我们可以采取前缀和的思路记 $p_i$ 表示从 $1\dots i$ 这几位组成的线性基，我们考虑怎么将前 $l-1$ 个删掉，我们可以多记 $id_i$ 表示这个位置是什么时候被插入的，查询的时候我们就可以直接将 $id_i<l$ 的删掉。

同时我们还要保证是由 $l\dots r$ 这几位组成的，删掉 $id_i<l$ 的可能这一位原本是有 $id_i\ge l$ 这种情况的，所以我们每次插入的时候可以贪心：插入一个数 $x$，它的位置为 $s$，我们还是从大到小去插入这个数，只不过当我们插入某一位的时候，如果这一位的 $id_i<w$，我们将这一位的值换为 $x$ 肯定是最优的，那么我们将这一位线性基的值和 $id_i$ 与 $x,s$ 交换，用交换出来的继续向下找就行了。

最后关于如何判断 $x$ 能被异或出来，我们直接由最高位开始，如果 $x$ 在这一位有，就直接异或上这一位的值，最后判断剩下来的是不是 $0$ 就行了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e6+5,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
//typedef __int128_t i128;
//i128 _base=1;
//inline int mol(int x){return x-Mod*(_base*x>>64);}
//inline void Add(int &x,int y){x=mol(x+y+Mod);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int n,Q;
int a[N];
vector<int>q[N];
struct Basis2{
	int w[62],id[62];
	Basis2(){memset(w,0,sizeof w);memset(id,0,sizeof id);}
	inline void ins(int x,int f){
		Rof(i,60,0){
			if(x&(1ll<<i)){
				if(!w[i]) return (void)(w[i]=x,id[i]=f);
				if(id[i]<f) swap(f,id[i]),swap(x,w[i]);
				x^=w[i];
			}
		}
	}
}gg[N],ans;
inline void solve(){
	n=read();Q=read();
	For(i,1,n) a[i]=read();
	For(i,1,n){
		For(j,0,60) gg[i].w[j]=gg[i-1].w[j],gg[i].id[j]=gg[i-1].id[j];
		gg[i].ins(a[i],i);
	}
	while(Q--){
		int l=read(),r=read(),x=read();
		ans=gg[r];
		For(i,0,60) if(ans.id[i]<l) ans.w[i]=0;
		Rof(i,60,0){
			if(x&(1ll<<i)){
				x^=ans.w[i];
			}
		}
		if(!x) puts("Yes");
		else puts("No");
	}
}
signed main(){
	//_base=(_base<<64)/Mod;
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	int T=1;
	while(T--){solve();}
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}


```

---

## 作者：EXODUS (赞：5)

# Part 1：前言
纪念一下自己独立做出来的一道 ABC 的 ex 题，同时也是一个和题解区做法不同的题解。

这好像也是我第一次写猫树，笑嘻了。

# Part 2：正文

~~作为一名 SDOIer，我们精通数据结构。~~

求一个集合能否异或出来某个数首先想到线性基，然后套上区间的皮可以想到维护一颗线段树，我们就有了一个 $O(n\log n\log V+q\log n\log^2 V)$ 的好做法，具体来说是对线段树上每个点维护一个线性基，然后询问时把拆出来的 $O(\log n)$ 个线性基合并，显然过不去。

注意到上面那个做法预处理和询问的复杂度好像不是很平衡，可能可以有一些平衡方式可以把一个 $\log V$ 开到根号下，但是我不会。

然后我又想了一会分块，分块的复杂度是 $O(B\log n+\frac{n}{B}{\log^2 n})$，取 $B=\sqrt{n\log n}$ 可以得到一个 $O(n\log n\sqrt{n\log n})$ 的更为厉害的做法，如果我们用带删除线性基或者跑回滚莫队的话能做到 $O(n\log n\sqrt{n})$，但是还是差的不行。

怎么做？猫树分治！

猫树的核心思想是对于每个代表区间 $[l,r]$ 的节点维护其在 $[l,mid]$ 中的后缀信息和 $[mid+1,r]$ 中的前缀信息。考虑此时我们只需要把每个询问区间定位到一个节点，满足其跨过该节点代表的区间中点，然后把前后缀信息拼起来即可。在这里不过多赘述。

复杂度是什么？注意到线段树的一个特殊性质是区间长度和为 $O(n\log n)$ 的，那么预处理复杂度是 $O(n\log n\log V)$ 的，单次询问每次会拆出至多 $2$ 个线性基，对其做线性基合并则是 $O(\log^2 V)$ 的，总时间复杂度是 $O(n\log n\log V+q\log^2 V)$ 的。

注意到空间炸成了 $O(n\log n\log V)$，离线后把询问挂到节点上即可做到 $O(n\log V)$ 空间。

然后被卡常了。看了眼 Atcoder 的题解竟然也有这个做法，他也被卡常了（笑），然后把他的火车头拉下来过了。

# Part 3：代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=(1<<19)+7;
bool memb=0;
ll a[N];
struct Basis{
	ll val[61];
	void insert(ll v){for(int i=59;i>=0;i--)if((v>>i)&1){if(val[i])v^=val[i];else{val[i]=v;break;}}}
	bool ask(ll v){for(int i=59;i>=0;i--)if((v>>i)&1){if(val[i])v^=val[i];else return 0;}return 1;}
	void clear(){memset(val,0,sizeof(val));}
};
void merge(Basis &lhs,const Basis &rhs){for(int i=59;i>=0;i--)if(rhs.val[i])lhs.insert(rhs.val[i]);}
struct Query{
	int l,r;ll x;
	int ans;
}q[N];
struct Cat_Tree{
	Basis bas[N];
	vector<int>que[20];
	void work(int d){
		for(auto i:que[d]){
			auto tmp=bas[q[i].l];
			if(q[i].l!=q[i].r)merge(tmp,bas[q[i].r]);
			q[i].ans=tmp.ask(q[i].x);
		}
	}
	void solve(int l,int r){
		// printf("%d %d %d\n",d,l,r);
		int mid=(l+r)>>1;
		bas[mid].clear();bas[mid].insert(a[mid]);
		for(int i=mid-1;i>=l;i--)bas[i]=bas[i+1],bas[i].insert(a[i]);
		bas[mid+1].clear();bas[mid+1].insert(a[mid+1]);
		for(int i=mid+2;i<=r;i++)bas[i]=bas[i-1],bas[i].insert(a[i]);
	}
	void solve(int _n){
		int n=1;while(n<_n)n<<=1;
		for(int j=1,i=0;j<=n;j<<=1,i++){
			for(int k=0;k<n;k+=j)solve(k,k+j-1);
			work(i);
		}
	}
	void query(int l,int r,int x){
		int g=(l^r)?(__lg(l^r)+1):0;
		que[g].eb(x);
	}
}ct;
int n,Q;
bool meme=0;
int main(){
	// Debug("%.5lfMB\n",fabs(&meme-&memb)/1024.0/1024.0);
	read(n,Q);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=Q;i++){
		read(q[i].l,q[i].r,q[i].x);
		ct.query(q[i].l,q[i].r,i);
	}
	ct.solve(n+1);
	for(int i=1;i<=Q;i++){
		if(q[i].ans)puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：toolong114514 (赞：1)

# AT_abc223_h [ABC223H] Xor Query 题解
## 解题思路
首先一眼可以看出是个线性基题。

如果已知当前区间的线性基，那么直接把查询的数在线性基上分解，看一下是否成功即可。

我们先考虑如何直接查询区间的线性基。

显然有预处理 $O(n\log^3{n})$，单次查询 $O(\log^2{n})$ 的 ST 表，或者 $O(n\log^3{n}))$ 的线段树，以及 $O(n\sqrt{n}\log{n})$ 的回滚莫队（线性基不支持删除）。

不过这些数据结构做法很容易被卡掉。

我们要返璞归真，从纯粹的线性基角度思考。

考虑一个弱化版问题：所有查询的区间均为 $[1,i]$ 的形式。

直接对询问离线，挨个处理即可。

那么对于形如 $[l,r]$ 的区间，就是在 $[1,r]$ 的基础上，加入了一个 $l$ 的限制。

如果我们对于每个区间 $[1,i]$，都从右到左插入元素，那么每一位都是由尽可能靠右的元素贡献的。

我们只需要记录每位被贡献的元素下标，就可以判断下标是否小于 $l$（是则认为这一位没有值），然后正常处理，就能一次性处理所有右端点相同的询问。

当然，直接暴力预处理 $n$ 个这样的线性基的时间复杂度是 $O(n^2\log{n})$ 的，会超时。

我们要考虑如何通过从右到左插入的区间 $[1,i]$ 的线性基推导出同样从右到左插入的区间 $[1,i+1]$ 的线性基。

我们先插入 $a_{i+1}$，再按照每位记录的下标从大到小给 $[1,i]$ 的线性基排序，依次插入到新的线性基中即可。

这样就圆满地解决了处理线性基的问题，搭配离线询问就做完了（你不嫌麻烦也可以记录 $n$ 个线性基依次回答询问）。

时间复杂度约为 $O(n\log^2{n})$，可以通过本题。

听说有 $O(n\log{n})$ 的做法？
## 参考代码

```cpp
#include<algorithm>
#include<iostream>
using namespace std;
const int N=1e6+10;
#define int long long
struct node{
	int l,r,val,fm;
	bool ans;
}ask[N];
bool cmp1(node pre,node nxt){
	return pre.r<nxt.r;
}
bool cmp2(node pre,node nxt){
	return pre.fm<nxt.fm;
}
int zyh[61],lp[61],a[N];
void ins(int x,int p){
	for(int i=60;i>=0;i--){
		if(x&(1ll<<i)){
			if(!zyh[i]){
				lp[i]=p;
				zyh[i]=x;
				break;
			}else{
				x^=zyh[i];	
			}
		}
	}
}
bool check(int x,int p){
	for(int i=60;i>=0;i--){
		if(x&(1ll<<i)){
			if(!zyh[i]||lp[i]<p) return false;
			x^=zyh[i];
		}
	}
	return true;
}
int n,q;
struct ccf{
	int tmp,tp;
}sb[61];
bool cmp3(ccf pre,ccf nxt){
	return pre.tp>nxt.tp;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=q;i++){
		cin>>ask[i].l>>ask[i].r>>ask[i].val;
		ask[i].fm=i;
	}
	sort(ask+1,ask+q+1,cmp1);
	for(int i=1;i<=q;i++){
		if(ask[i].r!=ask[i-1].r){
			for(int j=ask[i-1].r+1;j<=ask[i].r;j++){
				for(int k=0;k<=60;k++){
					sb[k].tmp=zyh[k];
					sb[k].tp=lp[k];
					zyh[k]=lp[k]=0;
				}
				sort(sb+0,sb+61,cmp3);
				ins(a[j],j);
				for(int k=0;k<=60;k++){
					ins(sb[k].tmp,sb[k].tp);
				}
			}
		}
		ask[i].ans=check(ask[i].val,ask[i].l);
	}
	sort(ask+1,ask+q+1,cmp2);
	for(int i=1;i<=q;i++){
		if(ask[i].ans) cout<<"Yes\n";
		else cout<<"No\n";
	}
}
```
[本代码可以通过 AT 评测。](https://www.luogu.com.cn/record/175655243)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2024/9/2.

---

## 作者：xie_lzh (赞：0)

前置知识：异或线性基。

本题要求求出区间能否异或出一个给定的数，容易想到区间线性基，但是这个不太好搞。

考虑扫描线。

在扫描线过程中，考虑在线性基中多维护一个下标最大值，表示这一位最靠右的位置。

那么我们在扫描线的询问区间时，我们只需要考虑那些下标在左端点右边的二进制位，这些位是属于当前询问区间的。

如果无法利用下标在左端点右边的二进制位凑出则无解。

其他属于线性基模板，不再赘述。

没啥代码实现难度。

复杂度 $\Theta(n\times \log V)$ 其中 $V$ 为值域。

[Code](https://atcoder.jp/contests/abc223/submissions/58085918)

---

## 作者：C6H14 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc223_h)

## 题目大意

给你 $n$ 个数，多组询问，查询下标在 $[l,r]$ 内的数是否可以选择一些数异或得到 $x$（$n \leqslant 4 \cdot 10^5$，$a_i \leqslant 2^{60}$）。

## 分析

选数异或=线性基。

区间选数=区间线性基。

~~于是我们得到了一个线段树维护区间线性基的铀锈做法~~。

但是我们不需要修改，用线段树就是大炮炸蚊子，太浪费了。

考虑对于每一个 $r$ 我们都维护一个线性基，其中每一个基向量都尽量选择最靠右的数。

将 $a_i$ 插入到第 $i$ 个线性基时，先将前一个线性基复制到第 $i$ 个线性基中，然后插入时多加一个操作：将 $a_i$ 与当前基向量在原序列中的位置比较，将最靠右的换到线性基中，另一个拿去接着插入。

具体实现可以看代码，时间复杂度为 $\Theta ((n+q) \log a_i)$，空间复杂度为 $\Theta (n \log a_i)$。

## 代码

```cpp
const ll N=400005;
ll bas[N][62],id[N][62],n,q;
void ins(ll n,ll x)
{
	ll y=n;
	for (ll i=60;i>=0;--i)
	{
		if (!(x&(1ll<<i)))
			continue;
		if (!bas[n][i])
		{
			bas[n][i]=x;
			id[n][i]=y;
			return;
		}
		if (id[n][i]<y)
			swap(id[n][i],y),swap(bas[n][i],x);
		x^=bas[n][i];
	}
}
bool check(ll l,ll r,ll x)
{
	for (ll i=60;i>=0;--i)
	{
		if (!(x&(1ll<<i)))
			continue;
		if (id[r][i]<l)
			return false;
		x^=bas[r][i];
	}
	return true;
}
int main()
{
	n=read(),q=read();
	for (int i=1;i<=n;++i)
	{
		memcpy(id[i],id[i-1],sizeof(id[i]));
		memcpy(bas[i],bas[i-1],sizeof(bas[i]));
		ins(i,read());
	}
	while (q--)
	{
		ll l=read(),r=read(),x=read();
		if (check(l,r,x))
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
```


---

