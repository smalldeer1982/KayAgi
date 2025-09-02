# Hash Swapping

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018-summer-final/tasks/soundhound2018_summer_final_e

英小文字からなる長さ$ N $の文字列が $ M $ 個与えられ、 $ S_1,\ S_2,\ ...,\ S_M $ とします。以下のクエリを $ Q $ 個処理して下さい。

- swapクエリ($ type\ =\ 1,\ x,\ y,\ l,\ r $): $ S_x[l..r] $ と$ S_y[l..r] $ をswapする。
- hashクエリ($ type\ =\ 2,\ x,\ y\ =\ 0,\ l,\ r $): $ h(S_x[l..r]) $ を求め，出力する。

なお、

- 文字列 $ S $ に対し、$ S[l..r] $ を、$ S $の$ l $文字目から$ r $文字目まで(両端含む)の部分文字列を表すこととします。
- 英小文字 $ a $ に対し、ord$ (a)\ =\ 1, $ ord$ (b)\ =\ 2,\ ..., $ ord$ (z)\ =\ 26 $ とします。
- 文字列 $ S\ =\ c_1c_2...c_k $ に対し、$ \sum_{i=1..k}\ {\rm\ ord}(c_i)(1,000,000)^{i-1} $ を $ 10^9\ +\ 7 $ で割ったあまりを $ h(S) $ とします。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200,000 $
- $ 1\ \leq\ M\ \leq\ 20 $
- $ S_i $ は英小文字のみからなる
- $ 1\ \leq\ Q\ \leq\ 200,000 $
- $ type_i\ =\ 1,\ 2 $
- $ 1\ \leq\ x_i\ \leq\ M $
- swapクエリのとき, $ x_i\ <\ y_i\ \leq\ M $
- hashクエリのとき、$ y_i\ =\ 0 $
- $ 1\ \leq\ l_i\ \leq\ r_i\ \leq\ N $

### Sample Explanation 1

それぞれ、 - $ h("bc")\ =\ 3000002 $ - $ h("fghij")\ =\ 496944447 $ - $ h("gc")\ =\ 3000007 $ - $ h("fbhij")\ =\ 491944447 $ - $ h("bh")\ =\ 8000002 $ - $ h("agcij")\ =\ 496979442 $ を出力しています。

## 样例 #1

### 输入

```
5 2
abcde
fghij
8
2 1 0 2 3
2 2 0 1 5
1 1 2 2 2
2 1 0 2 3
2 2 0 1 5
1 1 2 1 3
2 1 0 2 3
2 2 0 1 5```

### 输出

```
3000002
496944447
3000007
491944447
8000002
496979442```

## 样例 #2

### 输入

```
7 3
pzocuwt
ghqsktw
ogvyhak
13
2 1 0 1 2
1 1 2 5 6
1 1 3 3 6
1 2 3 4 5
1 2 3 5 6
1 1 2 1 6
1 1 2 5 6
2 2 0 5 5
2 1 0 2 3
1 2 3 1 4
1 1 2 2 7
2 3 0 1 6
2 3 0 1 4```

### 输出

```
26000016
21
17000008
556958241
25847241```

# 题解

## 作者：FLAMEs_ (赞：4)

直接开眼了。

---

考虑这类问题怎么用线段树去维护。

不考虑修改操作，只考虑怎么维护一段区间的查询。

线段树上一个代表 $[L,R]$ 区间的节点，其两个儿子分别代表区间 $[L,mid]$ 与 $[mid + 1,R]$，其中 $mid=\lfloor\frac{L+R}{2}\rfloor$。

两个区间合并时，可以考虑让右半部分的贡献“右移” $(mid-L+1)$ 位，再加上左半部分的贡献。实现如下：

```cpp

inline void Pushup(int cur, int Len) {
	t[cur] = (t[Ls[cur]] + t[Rs[cur]] * Pw[Len] % Mod) % Mod;
  }
// Len = mid - L + 1;
```

例题：[ABC331F](https://www.luogu.com.cn/problem/AT_abc331_f)。

---

问题来了，如何进行修改？

这个部分，个人认为是非常神奇的一种想法。

考虑把线段树动态开点，然后把 $m$ 个字符序列初始对应的哈希值丢到线段树上。

应当注意到，交换一段区间，本质上就是 **交换两个区间对应的线段树子树**。

做法似乎显然了。如果当前递归的区间在修改区间内，交换两个位置对应的标号即可完成对应修改。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5, M = 22, lN = 2e5, Mod = 1e9 + 7, Bs = 1e6;
int n, m, q, idx, rt[N], Ls[N * 80], Rs[N * 80], t[N * 80], Pw[N];
char ch[N];
inline void Pushup(int cur, int Len) {t[cur] = (t[Ls[cur]] + t[Rs[cur]] * Pw[Len] % Mod) % Mod;}
void Build(int& cur, int L, int R) {
	if(!cur) cur = ++ idx;
	if(L == R) {
		t[cur] = ch[L] - 'a' + 1;
		return ;
	}
	int mid = (L + R) >> 1;
	Build(Ls[cur], L, mid);
	Build(Rs[cur], mid + 1, R);
	Pushup(cur, mid - L + 1);
}
void Update(int& cur, int& lst, int L, int R, int limL, int limR) {
	if(limL <= L && R <= limR) {
		swap(cur, lst);
		return ;
	}
	int mid = (L + R) >> 1;
	if(limL <= mid) Update(Ls[cur], Ls[lst], L, mid, limL, limR);
	if(limR > mid) Update(Rs[cur], Rs[lst], mid + 1, R, limL, limR);
	Pushup(cur, mid - L + 1); Pushup(lst, mid - L + 1);
}
int Query(int cur, int L, int R, int limL, int limR) {
	if(!cur) return 0; int mid = (L + R) >> 1;
	if(limL <= L && R <= limR) return t[cur];
	if(limL > mid) return Query(Rs[cur], mid + 1, R, limL, limR);
	if(limR <= mid) return Query(Ls[cur], L, mid, limL, limR);
	return (Query(Ls[cur], L, mid, limL, limR) + Query(Rs[cur], mid + 1, R, limL, limR) * Pw[mid - max(limL, L) + 1] % Mod) % Mod;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m; Pw[0] = 1;
	for(int i = 1; i <= lN; ++ i) Pw[i] = Pw[i - 1] * Bs % Mod;
	for(int i = 1; i <= m; ++ i) cin >> (ch + 1), Build(rt[i], 1, n);
	cin >> q;
	for(int i = 1, opt, inX, inY, inL, inR; i <= q; ++ i) {
		cin >> opt >> inX >> inY >> inL >> inR;
		if(opt == 1) Update(rt[inX], rt[inY], 1, n, inL, inR);
		else cout << Query(rt[inX], 1, n, inL, inR) << '\n';
	}
	return 0;
}
```

---

## 作者：DYYqwq (赞：2)

这个直接用平衡树维护就好了啊，修改是直接把两棵树分开，然后交换中间项再合起来就好了。

平衡树还有一个好处就是不用封装起来开 $20$ 个，动态开点比较好做。

然后说一下这个哈希的维护。

注意根节点也有一个字符，不要忘了加上它的长度，以及它的哈希也要算上。

```cpp
tree[i].hsh = (tree[ls].hsh + ord(tree[i].x) * pow_[tree[ls].sz] % mod + tree[rs].hsh * pow_[tree[ls].sz + 1] % mod) % mod;
```

时间复杂度是 $O(n \log n)$，可以通过。

然后以下是整个代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
mt19937 rnd(random_device{}());
struct node
{
	char x;
	int rd , ls , rs , sz , hsh;
}tree[4000010];
int n , m , q , cnt , pow_[200010] , rt[30];
inline int ord(char c)
{
	return c - 'a' + 1;
}
int new_node(char x)
{
	tree[++ cnt] = {x , rnd() , 0 , 0 , 1 , ord(x)};
	return cnt;
}
void pushup(int i)
{
	tree[i].sz = tree[tree[i].ls].sz + tree[tree[i].rs].sz + 1;
	tree[i].hsh = (tree[tree[i].ls].hsh + ord(tree[i].x) * pow_[tree[tree[i].ls].sz] % mod + tree[tree[i].rs].hsh * pow_[tree[tree[i].ls].sz + 1] % mod) % mod;
}
int meg(int x , int y)
{
	if(x == 0 || y == 0) return x | y;
	if(tree[x].rd < tree[y].rd)
	{
		tree[x].rs = meg(tree[x].rs , y);
		pushup(x);
		return x;
	}
	else
	{
		tree[y].ls = meg(x , tree[y].ls);
		pushup(y);
		return y;
	}
}
void split(int i , int &x , int &y , int sz)
{
	if(i == 0)
	{
		x = y = 0;
		return;
	}
	if(tree[tree[i].ls].sz < sz) x = i , split(tree[x].rs , tree[x].rs , y , sz - tree[tree[i].ls].sz - 1);
	else y = i , split(tree[y].ls , x , tree[y].ls , sz);
	pushup(i);
}
void range(int rt , int l , int r , int &x , int &y , int &z)
{
	split(rt , x , y , l - 1);
	split(y , y , z , r - l + 1);
}
signed main()
{
	pow_[0] = 1;
	for(int i = 1 ; i <= 200000 ; i ++) pow_[i] = pow_[i - 1] * 1000000 % mod;
	scanf("%lld%lld" , &n , &m);
	for(int i = 1 ; i <= m ; i ++)
	{
		string s;
		cin >> s;
		for(int j = 0 ; j < s.size() ; j ++) rt[i] = meg(rt[i] , new_node(s[j]));
	}
	scanf("%lld" , &q);
	while(q --)
	{
		int op , x , y , l , r;
		scanf("%lld%lld%lld%lld%lld" , &op , &x , &y , &l , &r);
		if(op == 1)
		{
			int qq , zbk , dyy , tyf , sjy , str;
			range(rt[x] , l , r , qq , zbk , dyy);
			range(rt[y] , l , r , tyf , sjy , str);
			rt[x] = meg(qq , meg(sjy , dyy));
			rt[y] = meg(tyf , meg(zbk , str));
		}
		else
		{
			int qq , zbk , dyy;
			range(rt[x] , l , r , qq , zbk , dyy);
			printf("%lld\n" , tree[zbk].hsh);
			rt[x] = meg(qq , meg(zbk , dyy));
		}
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

这题出的真好，模拟赛乱改这题然后拿着题套另一题搞诈骗的老哥素质好低下。

考虑把所有的字符串建成一棵线段树来维护哈希值，由于有多棵树，可以考虑动态开点。

然后我们思考怎么处理交换，发现我们其实就是把两棵树对应的一些节点交换位置，嫁接过去。

不难想到我们直接替换两棵树对应区间的两个节点的编号即可，具体实现如下：

```cpp
void Upd(int &u,int &u2,int L,int R,int l,int r)
{
	if(R<l||r<L)return;
	if(l<=L&&R<=r)
	{
		swap(u,u2);
		return;
	}
	Upd(Ls[u],Ls[u2],L,Mid,l,r),Upd(Rs[u],Rs[u2],Mid+1,R,l,r);
	Up(u,Mid-L+1),Up(u2,Mid-L+1);
}
```

这样我们就可以完成交换操作了。


然后这份代码在写的时候参考了 @FLAMEs_ 的实现，尤其是上传函数，在此鸣谢。
```cpp
#include<bits/stdc++.h>
#define LL long long
#define Mid (L+R>>1)
using namespace std;
const int N=2e5+5;
const int Mod=1e9+7;
const int P=1e6;
int n,m,Q,TOT,Rt[N],Ls[N*80],Rs[N*80];
LL H[N*80],Pw[N];
char C[N];
inline void Up(int u,int L){H[u]=(H[Ls[u]]+H[Rs[u]]*Pw[L]%Mod)%Mod;}
void Bt(int &u,int L,int R)
{
	if(!u)u=++TOT;
	if(L==R)
	{
		H[u]=C[L]-'a'+1;
		return;
	}
	Bt(Ls[u],L,Mid),Bt(Rs[u],Mid+1,R);
	Up(u,Mid-L+1);
}
void Upd(int &u,int &u2,int L,int R,int l,int r)
{
	if(R<l||r<L)return;
	if(l<=L&&R<=r)
	{
		swap(u,u2);
		return;
	}
	Upd(Ls[u],Ls[u2],L,Mid,l,r),Upd(Rs[u],Rs[u2],Mid+1,R,l,r);
	Up(u,Mid-L+1),Up(u2,Mid-L+1);
}
LL Qry(int u,int L,int R,int l,int r)
{
	if(R<l||r<L||!u)return 0;
	if(l<=L&&R<=r)return H[u];
	if(r<=Mid)return Qry(Ls[u],L,Mid,l,r);
	if(Mid<l)return Qry(Rs[u],Mid+1,R,l,r);
	return (Qry(Ls[u],L,Mid,l,r)+Qry(Rs[u],Mid+1,R,l,r)*Pw[Mid-max(l,L)+1]%Mod)%Mod;
}
int main()
{
	scanf("%d%d",&n,&m);
	Pw[0]=1;
	for(int i=1;i<N;i++)Pw[i]=Pw[i-1]*P%Mod;
	for(int i=1;i<=m;i++)scanf("%s",C+1),Bt(Rt[i],1,n);
	scanf("%d",&Q);
	for(int i=1,op,x,y,l,r;i<=Q;i++)
	{
		scanf("%d%d%d%d%d",&op,&x,&y,&l,&r);
		if(op==1)Upd(Rt[x],Rt[y],1,n,l,r);
		else printf("%lld\n",Qry(Rt[x],1,n,l,r));
	}
}
```

---

## 作者：Rainsleep (赞：1)

给线段树上每个节点赋一个编号，每次交换操作相当于交换编号。（交换其父亲对应儿子的编号）

查询操作直接类似哈希的合并简单完成。

[code](https://www.luogu.com.cn/paste/xai5f79q)

---

