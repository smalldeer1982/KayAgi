# [ABC338E] Chords

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_e

円周上に $ 2N $ 個の点が等間隔に並んでおり、ある点から始めて時計回りに $ 1 $ から $ 2N $ までの番号が付けられています。

円周上にはさらに $ N $ 個の弦があり、$ i $ 個目の弦は点 $ A_i $ と点 $ B_i $ を結んでいます。 ここで、$ A_1,\dots,A_N,B_1,\dots,B_N $ は全て相異なることが保証されます。

弦どうしの交点が存在するかどうか判定してください。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\ \leq\ 2N $
- $ A_1,\dots,A_N,B_1,\dots,B_N $ は全て相異なる
- 入力は全て整数

### Sample Explanation 1

!\[\](https://img.atcoder.jp/abc338/de1d9dd6cf38caec1c69fe035bdba545.png) 図のように、弦 $ 1 $（点 $ 1 $ と点 $ 3 $ を結ぶ線分）と弦 $ 2 $（点 $ 4 $ と点 $ 2 $ を結ぶ線分）が交点を持つので、`Yes` を出力します。

### Sample Explanation 2

!\[\](https://img.atcoder.jp/abc338/1b3b982c8d6ca59f00ca0edd218fb9c4.png) 図のように、弦どうしの交点は存在しないので、`No` を出力します。

## 样例 #1

### 输入

```
3
1 3
4 2
5 6```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
6 1
4 3
2 5```

### 输出

```
No```

## 样例 #3

### 输入

```
4
2 4
3 7
8 6
5 1```

### 输出

```
Yes```

# 题解

## 作者：spfa_ (赞：13)

[[ABC338E] Chords](https://www.luogu.com.cn/problem/AT_abc338_e)

[更好的阅读体验？](https://www.cnblogs.com/123wwm/articles/17993556)

### 题意简述

给一个圆，上面有 $2n$ 等分的点，编号为 $1\sim 2n$，再给 $n$ 条弦，问是否存在一对相交的弦。

### 题目分析

先考虑把圆拉直，那么弦会形成若干个区间，显然若两个区间区间包含或没有交点，则图上这两条弦就没有相交。则可以用类似括号匹配的方法去判断即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f = c == '-' ? -1 : f, c = getchar();
	while (c >= '0' && c <= '9') x = (x<<3)+(x<<1)+(c^48), c = getchar();
	return x*f;
}

inline void write(int x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x/10);
	putchar('0'+x%10);
}

typedef pair <int, int> pii;
const int N = 4e5+5;
int n, top, stk[N];
pii v[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x = read(), y = read();
		if (x > y) swap(x, y);
		v[x] = mk(1, i);
		v[y] = mk(0, i);
	}
	for (int i = 1; i <= n<<1; ++i) {
		if (v[i].fi) stk[++top] = v[i].se;
		else if (stk[top--] != v[i].se) puts("Yes"), exit(0);
	}
	puts("No");
	return 0;
}
```

---

## 作者：fcy20180201 (赞：8)

## 思路
对于这种稀奇古怪的题，一定要观察样例。

通过观察，我们发现两条线段 $[a,b](a<b)$ 和 $[c,d](c<d)$ 相交当且仅当 $a \lt c \lt b \lt d$，和环没有半毛钱关系，~~环就是用来唬人的~~。

因此将所有线段按照左端点排序，考虑每一条线段时，看这条线段的左右端点有没有**跨过前面某条线段的右端点**。如果有就直接 `Yes`。否则把右端点插进一个 `set` 里，这样以后的线段只要在 `set` 里二分查找就能确定有没有“跨过前面某条线段的右端点”。

时间复杂度 $\mathcal O(n \log n)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct seg{
	int a,b;
}s[200005];
bool operator <(const seg &x,const seg &y){return x.a<y.a;}
set<int>r;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&s[i].a,&s[i].b);
		if(s[i].a>s[i].b)swap(s[i].a,s[i].b);
		//钦定左端点 < 右端点
	}
	sort(s+1,s+n+1);//排序
	for(int i=1;i<=n;i++){
       	if(r.upper_bound(s[i].a)!=r.upper_bound(s[i].b)){puts("Yes");return 0;}
		//如果该线段跨过了前面某个线段的右端点，直接输出 Yes
		r.insert(s[i].b);
		//将右端点插入 set
	}
	puts("No");
	return 0;
}


```

---

## 作者：StayAlone (赞：8)

线性复杂度，最傻最简单无 stack 无 DS 做法！

## 思路

考虑实现这样一个函数：$f(l,r)$ 表示 $l+1,r+1,\cdots ,r$ 这些点所相关的边之间：

- 若这些点所相关的边不能内部解决，返回 $1$。内部解决是指对于任意点，其对应点仍然在 $[l,r]$ 之间，**且不产生交点**。
- 否则返回 $0$。

优美的是，这个函数并不考虑环上跨越 $1-n$ 的情况，因此可以简单地递归求解。

- 若 $l>r$，返回 $0$。
- 若 $l=r$，必定无法内部解决，返回 $1$（事实上区间长度为奇数都必定无法内部解决）。
- 否则，拿出 $l$ 及其对应点 $p$。若 $p$ 在 $[l, r]$ 外，显然不符合内部解决的要求，返回 $1$；否则递归子问题 $f(l + 1, p - 1)$ 和 $f(p + 1, r)$。

怎么判断圆内有没有交点？

找到 $1$ 的对应点 $y$，发现 $1-y$ 这根弦将圆划分成两个部分，两个部分都是不跨越 $1-n$ 的，因此使用上面的函数算一遍就行了。这里运用了一个充分必要的条件：若两部分均可以内部解决，那么不会有跨越 $1-y$ 的交点；反过来同样成立。

时间复杂度 $\mathcal O(n)$。代码非常短。

```cpp
int n, to[MAXN];

il bool check(int l, int r) {
	if (l > r) return 0;
	int q = to[l];
	if (q < l || q > r) return 1;
	return check(l + 1, q - 1) | check(q + 1, r);
}

int main() {
	read(n);
	rep1(i, 1, n) {
		int a, b; read(a, b);
		to[a] = b; to[b] = a; // to[x] 就是 x 点的对应点
	} int y = to[1];
	puts(check(2, y - 1) | check(y < n * 2 ? y + 1 : 1, n * 2) ? "Yes" : "No");
	rout;
}
```

---

## 作者：Genius_Star (赞：7)

### 思路：

~~刚开始以为是计算几何……~~

感觉下位绿。

自己手玩一下，发现对于 $l \to r$ 的连线，如果 $[l+1,r-1]$ 内只要有一个点的连线如果超过了 $[l,r]$ 范围，则视为有交点。

定义 $T_i$ 表示第 $i$ 个点连向的目标，定义：

$$Max=\max\limits_{l+1}^{r-1} (T_i)$$

$$Min=\min\limits_{l+1}^{r-1} (T_i)$$

如果 $Max>r$ 或者 $Min<l$ 则代表区间 $[l+1,r-1]$ 有点连到 $[l,r]$ 外面了。

求区间 $\max$ 和 $\min$ 可以用线段树或者 ST 表。

**时间复杂度为 $O(N \log N)$。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=400400;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll l,r;
	ll Max,Min;
}X[N<<2];
struct St{
	ll x,y;
	friend St max(const St&a,const St&b){
		St c;
		c.x=max(a.x,b.x);
		c.y=min(a.y,b.y);
		return c;
	}
};
ll n;
ll A[N],B[N],T[N];
void pushup(ll k){
	X[k].Max=max(X[k<<1].Max,X[k<<1|1].Max);
	X[k].Min=min(X[k<<1].Min,X[k<<1|1].Min);
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	if(l==r){
		X[k].Max=X[k].Min=T[l];
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
St qurey(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return {X[k].Max,X[k].Min};
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return qurey(k<<1,l,r);
	else if(l>mid)
	  return qurey(k<<1|1,l,r);
	else
	  return max(qurey(k<<1,l,mid),qurey(k<<1|1,mid+1,r));
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		A[i]=read();
		B[i]=read();
		if(A[i]>B[i])
		  swap(A[i],B[i]);
		T[A[i]]=B[i];
		T[B[i]]=A[i];
	}
	build(1,1,2*n);
	for(int i=1;i<=n;i++){
		if((A[i]==1&&B[i]==n*2)||(A[i]+1==B[i]))
		  continue;
		auto t=qurey(1,A[i]+1,B[i]-1);
//		cerr<<t.x<<' '<<t.y<<'\n';
		if(t.y<A[i]||t.x>B[i]){
			puts("Yes");
			exit(0);
		}
	}
	puts("No");
	return 0;
}
```


---

## 作者：STARSczy (赞：6)

# 思路：
感觉都写得好复杂，现有的 $5$ 篇题解里时间复杂度全都带 log。其实这题就是一个括号序列匹配，使用栈即可。

由于问题是 $n$ 个弦是否相交，将每个弦的两端点看做左括号和右括号，那么弦不相交和括号匹配一一对应为充要条件。以样例二为例，括号匹配后，就是序列为 `((()))`。而下标为 $1,2,3$ 的左括号**分别**匹配 $4,5,6$，因此输出 Yes。

那么，栈里面存储下标，当括号序列合法，左右端点一定匹配，栈为空；反之不然，因为若端点不能匹配，右端点不能匹配左端点，就会被当做左端点压入栈，最终栈不可能为空。也就是说，最有只需判断栈是否为空即可。

# 代码：
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define int long long
#define fi first
#define se second
using namespace std;
const int maxn=1e6+10,mod=1e9+7;

int n,x,y,a[maxn],st,stk[maxn];

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	rep(i,1,n) cin>>x>>y,a[x]=a[y]=i;
	rep(i,1,n*2) if(stk[st]!=a[i]) stk[++st]=a[i];//压入左端点
	else --st;//匹配时弹出左端点
	cout<<(st?"Yes":"No");//是否为空
	return 0;
}
```

---

## 作者：CheZiHe929 (赞：4)

# AT_abc338_e 题解

### 题目链接

[Atcoder](https://atcoder.jp/contests/abc338/tasks/abc338_e)

[Luogu](https://www.luogu.com.cn/problem/AT_abc338_e)

### 题目大意

有一个有 $2 \times n$ 个节点的圆。

该圆上有 $n$ 条弦，其中第 $i$ 条弦连接 $a_i$ 和 $b_i$（保证所有 $a_i$ 和 $b_i$ 的值都不同）。

问这些弦是否有交点。

### 简要思路

很多环状的题都是把它切开当成一条链来做的（比如 [P1063](https://www.luogu.com.cn/problem/P1063)），这道题也不例外。

那么我们这道题就转换成了一条从 $1$ 到 $2 \times n$ 的序列，有 $n$ 条曲线，每条曲线从 $a_i$ 连向了 $b_i$，让我们判断这些曲线是否有交点。

~~话说不知道大家有没有想起来括号匹配，我感觉有点像。~~

接下来我们考虑什么情况下不会出现交点：

1. 形如 $1$ 连向 $n$、$2$ 连向 $n-1$、$3$ 连向 $n-2\dots$ 这样的序列，像括号匹配中 `((((()))))` 这样的情况。

2. $a_1$ 连向 $a_2$、$a_3$ 连向 $a_4\dots$，其中 $a$ 数组是一个单调递增的序列，像括号匹配中 `()()()()()()()()` 这样的情况。

3. 当然还有上述两种情况的结合，如 `(()())`。

但是不管上述何种情况，都满足同一个条件：当遇到第 $i$ 条曲线的终点 $b_i$ 时，它之前所剩的未出现终点的最后一条曲线的起点一定是对应的 $a_i$。

这就是栈的后进先出的原理，因此此题用栈来解决。

当我们在遍历时遇到了一个曲线的终点，我们就要看当前栈顶是否是该终点对应的起点，如果不是则证明会有交点。

注意在一条序列上，编号较小的为起点，编号较大的为终点。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
const int MAXN=4e5+5;

int n,a[MAXN],b[MAXN];
int f[MAXN];//f[i] 为 1 表示该点是一条曲线的起点，为 2 则表示是终点
int num[MAXN];//num[i] 表示以 i 为起点/终点的曲线的编号
std::stack<int> s;//栈中存着节点的编号

signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

    std::cin>>n;
    for(int i=1;i<=n;i++){
    	std::cin>>a[i]>>b[i];
		f[std::min(a[i],b[i])]=1;
		f[std::max(a[i],b[i])]=2;
		num[a[i]]=num[b[i]]=i;
	}
	
	for(int i=1;i<=2*n;i++){//注意节点编号为 1~2n
	    if(f[i]==1)s.push(i);//起点
	    else if(num[s.top()]!=num[i]){//起点终点编号不对应
	    	std::cout<<"Yes\n";
	    	return 0;
		}else s.pop();//弹掉当前起点
	}
	std::cout<<"No\n";

	return 0;
}
```

### AC 记录

[Atcoder](https://atcoder.jp/contests/abc338/submissions/49783356)

[Luogu](https://www.luogu.com.cn/record/144993884)

**THE END.**

**THANK YOU.**

---

## 作者：__Dist__ (赞：3)

### 题目大意

在一个圆上有 $2N$ 个等间隔的点，从某点开始按顺时针方向依次编号为 $1$ 至 $2N$。

圆上还有 $N$ 条线，其中 $i$ 条线连接点 $A_i$ 和 $B_i$。保证 $A_1,\dots,A_N,B_1,\dots,B_N$ 互不相同的。

判断这些线之间是否有交点。

（~~机翻勿喷~~）

### 思路讲解

感觉思路奇葩的，差分。

把一个圆拉直，像这样：

![](https://img.atcoder.jp/abc338/ff4c78532301561b18080c6a52985806.png)

不难发现，如果这个图有交点，当且仅当一条线的一个端点在另一条线段的两个端点之内，而这条线的另一个端点不在（有点绕口，我语文不好）。

但是如果每次判断的话复杂度太高。我们可以建立一个 $a$ 数组，把这条线段覆盖的区间的所有点（包括两端）$a_i$ 同时加上一个数，最后进行判断，如果一条线段两端点 $a_{x_i},a_{y_i}$ 的值不等，就说明有交点。如果所有的线段两端点值都相等，就说明没有交点。

但是每次从 $x_i$ 加到 $y_i$ 复杂度太高，可以通过差分解决。

### 代码环节

思路看不懂就看代码吧！

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4e5 + 5;
int n;
int a[MAXN];
int x[MAXN], y[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x[i], &y[i]);
		if(x[i] > y[i]) swap(x[i], y[i]);
		a[x[i]] += i;
		a[y[i] + 1] -= i;
	}
	for (int i = 1; i <= n + n; i++) {
		a[i] += a[i - 1];
	}
	for (int i = 1; i <= n + n; i++) {
		if(a[x[i]] != a[y[i]]) {
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0;
}
```

---

## 作者：2huk (赞：3)

## Problem Statement

There are $2N$ points placed at equal intervals on a circle, numbered $1$ to $2N$ in a clockwise direction starting from a certain point.

There are also $N$ chords on the circle, with the $i$\-th chord connecting points $A_i$ and $B_i$. It is guaranteed that all the values $A_1,\dots,A_N,B_1,\dots,B_N$ are distinct.

Determine whether there is an intersection between the chords.

## Solution

首先我们保证 $a_i < b_i$。若不满足先把它们交换。

然后圆拆开成一条链。一张官方题解的图示：

![img](https://img.atcoder.jp/abc338/ff4c78532301561b18080c6a52985806.png)

可以发现，如果两条线 $x, y$ 有交叉，那么一定有 $a_x < a_y < b_x < b_y$。

枚举 $x$，然后找是否存在一个 $y$ 满足以上条件。

如果我们令 $c_i$ 表示在 $a_x = i$ 时 $b_x$ 的值。由于 $a_i, b_i$ 这总共 $2n$ 个数互不相同，所以 $c_i$ 是唯一确定的。那么上面的问题其实就是：

> 是否存在一个 $a_x < j < b_x$，使得 $c_j > b_x$。

这是经典问题。我们只需要求这个区间内的最大值，然后判断是否大于 $b_x$ 即可。也就是判断：
$$
\max_{j = a_x + 1}^{b_x - 1} c_j > b_x
$$
这就是静态区间求最大值的问题。ST 表即可。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 400010, M = 25;

int n, a[N], b[N];
int st[N][M];

int query(int l, int r) {
	if (l > r) return -2e9;
	int k = log2(r - l + 1);
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i] >> b[i];
		if (a[i] > b[i]) swap(a[i], b[i]);
		st[a[i]][0] = max(st[a[i]][0], b[i]);
	}
	
	for (int j = 1; j < M; ++ j )
		for (int i = 1; i + (1 << j) - 1 <= 2 * n; ++ i )
			st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	
	for (int i = 1; i <= n; ++ i )
		if (query(a[i] + 1, b[i] - 1) > b[i])
			return puts("Yes"), 0;
	
	puts("No");
	
	return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：3)

## problem statement
一个圆上有 $2n$ 个点将其平分，有 $n$ 条弦，第 $i$ 条连接了这些点中的 $a_i$ 和 $b_i$，所有的 $a_i$ 和 $b_i$ 互不一样，求这些弦有无交点。有交点输出 `Yes`，否则输出 `No`。

## solution
我的思路可能复杂了些，欢迎大家指出其中可以优化之处。

最开始，想到了一个点，连一条边，会把这个圆上的点分成两部分，这两部分的点互相不能连接，否则就会有交点。但是肯定做不到把点分成两部分，所以我们要想一种方法判断一条边和之前已经判断过的边有无交点。

从分成的两部分入手，除去当前的这条边连接的点，剩下偶数个点，所以在这条线左边和右边的点的个数奇偶性相同，两边是同理的，我们判断一边即可。

如果一部分中已经有边连接的点是偶数个，那么说明可以两两配对，没有交点，因为这些点不会与当前直线有交点，而且如果与之前的直线有交点的话那就已经被判断了。而如果是奇数个，就不能两两配对，必会和当前直线相交。

所以我们就需要维护一段弧上的已经被连接的点的个数，这里我用了树状数组，不过应该有更简单的方法。

代码就不展示了，树状数组和其他的东西都比较好写，~~当然你愿意写线段树我也不介意~~。

---

## 作者：Shunpower (赞：2)

主席树是好文明。

考虑枚举两根相交的弦中的其中一根 $i$，并钦定 $A_i<B_i$（弦分割出的圆的两半边在这个问题当中没有差异）。那么显然若存在一根弦 $j$ 连接了区间 $(A_i,B_i)$ 之间的点到其之外（$[1,A_i)\cup(B_i,2n]$）的点，就存在了相交的情况，否则不会存在。

那么这个问题相当于问是否存在一条弦 $j$ 满足有一端在 $(A_j,B_j)$ 之中，另一端在 $[1,A_i)\cup(B_i,2n]$ 之中，这就是一个裸的二维数点，直接主席树猛做即可。

[我的代码](https://atcoder.jp/contests/abc338/submissions/49732267)。由于题目保证一个点上只有一根弦，所以边界写得并不算很严谨，但可以通过。

---

## 作者：lostxxx (赞：2)

[题目传送门](https://atcoder.jp/contests/abc338/tasks/abc338_e)

# 题目大意

共有 $N$ 条直线，分别连接 $A_i B_i$ 。随后判断有无直线相交。注意，所有点都必须被连接到，不会有点被重复连接。

# 题目分析

我们可以把每一条直线看做一个区间，在这个区间中，不仅可以相交，也可以包含。所以我们先判断这个区间中是否有奇数个点，如果有，那么意味着一定会有相交，如果没有，那么就进行下一步遍历判断。
```cpp
if ((a[i].r-a[i].l+1)%2==1){
	cout<<"Yes";
	return 0;
}
```
我们先将所有直线的最小连接点进行排序，随后再 $O(n)$ 遍历即可。两种情况：第一是两个端点都被包含，第二种是一个端点被包含，另一个没有，直接输出即可。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
struct node{
	ll l,r;
}a[200100];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
bool cmp(node a,node b){
	return a.l<b.l;
}
int main(){
	n=read();
	for (int i=1;i<=n;i++){
		a[i].l=read();
		a[i].r=read();
		if (a[i].l>a[i].r)
			swap(a[i].l,a[i].r);
		if ((a[i].r-a[i].l+1)%2==1){
			cout<<"Yes";
			return 0;
		}
	}
	sort(a+1,a+n+1,cmp);
	for (int i=1;i<=n;i++){
		if (a[i+1].l>a[i].l && a[i+1].l<a[i].r){
			if (a[i+1].r<a[i].l || a[i+1].r>a[i].r){
				cout<<"Yes";
				return 0;
			}
		}else if (a[i+1].r>a[i].l && a[i+1].r<a[i].r){
			if (a[i+1].l<a[i].l || a[i+1].l>a[i].r){
				cout<<"Yes";
				return 0;
			}
		}
	}	
	cout<<"No";
}
```


---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc338_e)

## $\mathtt{Solution}$

考虑怎么判断有没有相交弦，假设第 $i$ 条弦连接了点 $l_i$ 和点 $r_i$。

对于每一个 $1\le i\le n$，对于 $l_i\le j\le r_i$，与之连接的点编号也在 $[l_i,r_i]$ 之内。

否则，弦 $(l_i,r_i)$ 一定与弦 $(l_j,r_j)$ 相交。

所以，令 $g_i$ 为与点 $i$ 连接的点的编号，用 ST 表或者线段树维护区间最大值和最小值即可。

```cpp
#include<bits/stdc++.h>
#define left rt * 2
#define right rt * 2 + 1
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 4e5 + 5, MR = 2e6 + 5;
int n, l[MAXN], r[MAXN], g[MAXN];
struct Segment_tree{
	int lf[MR], rf[MR], maxx[MR], minn[MR];
	void push_up(int rt){maxx[rt] = max(maxx[left], maxx[right]), minn[rt] = min(minn[left], minn[right]);}
	void build(int rt, int l, int r){
		lf[rt] = l, rf[rt] = r;
		if(l == r){
			minn[rt] = maxx[rt] = g[l];
			return ;
		}
		int mid = l + r >> 1;
		build(left, l, mid);
		build(right, mid + 1, r);
		push_up(rt);
	}
	int query_max(int rt, int l, int r){
		if(l > rf[rt] || lf[rt] > r)return 0;
		if(l <= lf[rt] && rf[rt] <= r)return maxx[rt];
		return max(query_max(left, l, r), query_max(right, l, r));
	}
	int query_min(int rt, int l, int r){
		if(l > rf[rt] || lf[rt] > r)return 1e9;
		if(l <= lf[rt] && rf[rt] <= r)return minn[rt];
		return max(query_min(left, l, r), query_min(right, l, r));
	}
}tr;
int main(){
	n = read();
	for(int i = 1;i <= n;i ++)l[i] = read(), r[i] = read();
	for(int i = 1;i <= n;i ++)
		g[l[i]] = r[i], g[r[i]] = l[i];
	tr.build(1, 1, 2 * n);
	for(int i = 1;i <= n;i ++){
		if(l[i] > r[i])swap(l[i], r[i]);
		if(l[i] + 1 == r[i])continue;
		int h = tr.query_min(1, l[i] + 1, r[i] - 1), p = tr.query_max(1, l[i] + 1, r[i] - 1);
		if(h < l[i] || p > r[i]){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}

```


---

## 作者：lalaouye (赞：1)

观察一下，发现弦 $A_n,B_n$ 和 弦 $A_m,B_m$ 相交当且仅当 $A_n<A_m<B_n<B_m$，其中 $n$ 和 $m$ 顺序显然可以换。

然后我们只需要对其按 $A$ 进行排序，在数组每一位 $n$ 进行一次查询，每次查询数组最后一个 $A_m$ 使得 $A_n<A_m$，然后看是否有 $B_i$ 使得 $B_n<B_i$ 且 $n<i\le m$ 即可，这里可直接查区间最大值，用 ST 表维护，时间复杂度 $O(n\log n)$。

代码：

```cpp
#include <bits/extc++.h>
#define int long long
#define ls (p << 1)
#define rs (ls | 1)
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
#define x first
#define y second
#define inf 1000000000
#define linf 1000000000000000000
using namespace std;
typedef long long ll;
constexpr ll N = 4e5 + 5, base = 37;
inline int rd ()
{
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) { x = (x << 1) + (x << 3) + ch - 48; ch = getchar (); }
	return x * f;
}
pii a[N];
int n;
int f[N][25];
int qry (int x, int y)
{
	int k = log2 (y - x + 1);
	return max (f[x][k], f[y - (1 << k) + 1][k]);
}
signed main ()
{
	// freopen ("1.in", "r", stdin);
	// freopen ("1.out", "w", stdout);
	n = rd ();
	rep (i, 1, n) a[i].first = rd (), a[i].second = rd ();
	rep (i, 1, n) if (a[i].first > a[i].second) swap (a[i].first, a[i].second);
	sort (a + 1, a + n + 1);
	rep (i, 1, n) f[i][0] = a[i].second;
	rep (j, 1, 24)
	{
		rep (i, 1, n - (1 << j) + 1)
		{
			f[i][j] = max (f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
	bool chk = 0;
	rep (i, 1, n)
	{
		int j = upper_bound (a + 1, a + n + 1, pii (a[i].y, 0)) - a - 1;
		if (qry (i, j) > a[i].y) chk = 1;
	}
	puts (chk ? "Yes" : "No");
}
```


---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc338_e)

## 题目大意
一个圆上有 $1$ 到 $2\times n$ 这些点，从小到大等距离分布。现给出 $n$ 条弦，对于每条弦给出左右两端点的序号 $a_i$ 和 $b_i$ ，判断这些弦是否有交点，有输出 `Yes`，否则输出 `No`。保证所有的 $a_i$ 和 $b_i$ 均两两不相等。
## 数据范围
$2\le n\le 2\times 10^5$，$1\le A_i,B_i\le 2\times n$。

如果要让一条弦与别的弦没有交点，那么这一条弦把圆的左右两边分割开来之后，左边的点与右边的点没有相连的弦。此时可以考虑栈，从 $1$ 到 $2\times n$ 遍历，当第一次遇到某条弦的端点时将弦入栈，第二次遇到某条弦的端点时判断另一个端点是否有在栈顶，如果没有就说明一定有一个点在圆上夹在两个端点之间且与它相连的点还未遍历到，此时就会出现这样的情况：    
![](https://cdn.luogu.com.cn/upload/image_hosting/0evs0zzp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)    
也就是在栈顶上的那个点会穿过这条弦与另一个点连接，那么就输出 `Yes`，否则弹出栈顶。

如果到最后还没有输出 `Yes`，就输出 `No`。
# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[400010]={0},dy[400010];
stack<int> s;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		dy[x]=y,dy[y]=x;
	}
	for(register int i=1;i<=2*n;i++)
	{
		if(s.empty()){s.push(i),t[i]=1;continue;}
		if(s.top()==dy[i]){s.pop();continue;}
		if(t[dy[i]]){printf("Yes");return 0;}
		t[dy[i]]=1,s.push(i);
	}
	printf("No");
	return 0;
}
```

---

## 作者：tanzicheng (赞：1)

## [ABC338E] Chords 题解
### 题目翻译
一个圆上现在有 $2N$ 个等距的点，它们之间用 $N$ 条线连接起来，问这 $N$ 条线之间是否会出现交叉。
### 解题思路
首先看到这道题，第一眼：st表，可惜本蒟蒻不会。所以，我来发一篇用栈来做的题解。

先来观察一下这两张图：

![A](https://img.atcoder.jp/abc338/de1d9dd6cf38caec1c69fe035bdba545.png)

![B](https://img.atcoder.jp/abc338/1b3b982c8d6ca59f00ca0edd218fb9c4.png)

通过这两张图，不难发现：这道题与 [括号序列](https://www.luogu.com.cn/problem/P1241) 相似。第一张图片为例，这个圆环便可以转换为：`([)]{}` ，不匹配，所以有交点。
### 具体实现
从 $1$ 开始遍历，如果遇到与栈顶不能配对的数，就入栈，否则退栈，最后判断一下栈是否为空即可。

AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
map<int,int> uv;
stack<int> st;
signed main(){
	cin >>n;
	for(int i=1;i<=n;i++){
		int u,v;
		cin >>u>>v;
		uv[u]=v;
		uv[v]=u;    //u与v连通
	}
	for(int i=1;i<=2*n;i++){
		if(!st.empty()&&st.top()==uv[i]){
			st.pop();    //如果匹配，则出栈
		}
		else{
			st.push(i);    //如果不匹配，则入栈
		}
	}
	if(!st.empty()){    //栈非空就是有交点
		cout <<"Yes";
	}
	else{
		cout <<"No";
	}
	return 0;
} 
```

---

## 作者：wflhx2011 (赞：1)

## 题目大意

有 $2\times n$ 个点顺时针分布在圆环上，$n$ 条边连接，问这 $n$ 条边有无交点。

# Solution

这次题目还可以。

首先建一个栈，随便放一个数，不然会越界。

之后，将一条边端点打上相同编号，依次入栈，如果有与他相同的就出栈。

最后，如果只剩下一开始放进去的数，就没有交点，否则就有交点。

## Why?

画图模拟，发现如果 $2$ 条边有交点，他们的端点就会交替出现，就会有几个点不与队首匹配，最后也就不能让栈只剩下一开始放进去的数。

明白思路后，代码也就好写了：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct nod
{
	int x,y;
}k[400005];
stack<int>s;
int p[400005];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>k[i].x>>k[i].y;
	for(int i=1;i<=n;i++)
		p[k[i].x]=p[k[i].y]=i;
	s.push(-7);
	for(int i=1;i<=2*n;i++)
		if(p[i]==s.top()&&!s.empty())
			s.pop();
		else
			s.push(p[i]);
	if(s.size()==1)
		cout<<"No";
	else
		cout<<"Yes";
	return 0;
}
```

---

## 作者：abensyl (赞：1)

原题：[[ABC338E] Chords](https://www.luogu.com.cn/problem/AT_abc338_e)。

## 思路

从本题中透露出一个重要的思想，多边形连线的交点问题可以转化为区间是否存在交集的问题。

考虑把一条从顶点 $i$ 到 $j$（$i<j$）的连线转化为区间 $[i,j]$，题目中所给出的 $n$ 条线就变成了 $n$ 个这种区间。

我们考虑区间与线段交点之间的关系，得到以下结论：

- 如果两个区间 $[s_1,t_1]$ 和 $[s_2,t_2]$ 是包含关系，那么从 $s_1$ 到 $t_1$ 的线段与从 $s_2$ 到 $t_2$ 的线段是没有交点的；  
- 如果两个区间 $[s_1,t_1]$ 和 $[s_2,t_2]$ 是互斥关系，那么从 $s_1$ 到 $t_1$ 的线段与从 $s_2$ 到 $t_2$ 的线段是没有交点的；
- 如果两个区间 $[s_1,t_1]$ 和 $[s_2,t_2]$ 交集不空且并非完全包含，那么 $s_1$ 到 $t_1$ 的线段与从 $s_2$ 到 $t_2$ 的线段会有交点的；

那么这样就可以通过判断区间之间相互的关系来判断多边形中对角线是否存在交点了。

这个问题的实现，有可以转化为括号匹配问题，这样，我们可以通过栈来维护它。

## 代码
```cpp
int mat[M];
void solve() {
	int n;
	cin>>n;
	rep(i,1,n) {
		int u,v;
		cin>>u>>v;
		mat[u]=v;
		mat[v]=u;
	}
	stack<int> stk;
	rep(i,1,n*2) {
		if(mat[i]>i) stk.push(i);
		else {
			int tp=stk.top();
			stk.pop();
			if(tp!=mat[i]) {
				cout<<"Yes\n";
				return;
			}
		}
	} cout<<"No\n";
}
```

---

## 作者：GGapa (赞：1)

本篇题解使用的方法是**不完全正确的算法（以下简称不完全算法）**，但能通过本题，具有一定的学习意义，请需要正解的同志们跳过这一篇题解，谢谢。

# 思路

不妨设 $A_l \leq B_l$，易得：若 $A_l < B_l < A_r <B_r$，其中 $A_l$、$A_r$ 分别代表弦 $A$ 的左右端点。

但是现在问题出现了，我们该如何实现这一推论呢？

[AtCoder的官方题解](https://atcoder.jp/contests/abc338/editorial/9181)上说可以使用一种基于栈的“imos”算法，但是在考试前我们可能没有接触这一类算法。

那该怎么办呢？

在考场上我们要大胆猜测，小心求证，如果没时间了甚至可以不求证。一份半对的代码总比宝玲要强。

这时候，经过对样例的分析，我们大胆猜测一种不能保真的贪心：

- 将每条弦的左端点值按照从小到大排序，结合上面的推论，将第 $i$ 和第 $i + 1$ 条弦进行比较。

我们就能快速的完成以下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

pair<int, int> a[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        if(a[i].first > a[i].second) swap(a[i].second, a[i].first);
    }
    sort(a + 1, a + 1 + n);
    for(int i = 1; i < n; i++) {
        if((a[i + 1].first <= a[i].second && a[i].second <= a[i + 1].second)) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No";
    return 0;
}
```

本以为会看到一片橙色，但令人惊喜的是，只错了一个点，说明我们这个随便想的贪心适用于大部分情况。

那该怎么解决最后那一抹红色呢？

通过小心的推敲，我们很快就发现了这份代码的漏洞，有时第 $i$ 条弦可能会与第 $i + 2$ 甚至 $i + 3$ 条弦有交点，若我们只与第 $i + 1$ 条弦进行比较的话，可能覆盖不了少部分情况，也就是那最后一个错误的点。

很快我们就能得到这个不完全算法的第二版：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

pair<int, int> a[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        if(a[i].first > a[i].second) swap(a[i].second, a[i].first);
    }
    sort(a + 1, a + 1 + n);
    for(int i = 1; i < n; i++) {
        if((a[i + 1].first <= a[i].second && a[i].second <= a[i + 1].second) || (a[i + 2].first <= a[i].second && a[i].second <= a[i + 2].second)) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No";
    return 0;
}
```

我们提交上去，发现顺利的通过了这道题。

# 反思

这道题能带给我们什么启发呢？

- 不要一看到题就想着写正解，可能会有一种不完全正确的方法带来惊喜。
- 在构思不完全算法时不要轻易放弃，有可能在稍微改一下就能过。

注：此方法不适用于 CodeForces，如果用了的话，可能会被叉到爆炸。

---

## 作者：_ZML_ (赞：1)

# 思路
思路还是很显然的，简单总结一下思路：

1. 首先，将圆环从点 $1$ 到 $2N$ 切开，并将其拉直成一条直线。
2. 在切开状态下，原来的弦变成了直线上的曲线。我们需要判断这些曲线之间是否存在交点。
3. 在切开状态下，曲线之间的交点等价于满足 $A_i < A_j < B_i < B_j$ 的不同曲线 $i$ 和 $j$ 的存在。
4. 为了判断曲线之间是否存在交点，我们可以使用栈来管理曲线。首先，准备一个空栈 $S$。
5. 遍历直线上的每个点，按顺序执行以下操作：
   - 如果当前点是某个曲线的左端点，将该曲线的标识符加入栈 $S$ 的末尾。
   - 如果当前点是某个曲线的右端点，从栈 $S$ 的末尾移除一个元素。
    - 如果移除的元素不是当前曲线的标识符，说明存在交点，返回结果并终止程序。
6. 如果程序在遍历结束后没有返回结果，说明曲线之间不存在交点。

这种使用栈的算法能够在 $O(N)$ 的时间复杂度内判断曲线之间是否存在交点。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> s[400010];
int stk[400010];
signed main() {
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int a,b;
		cin>>a>>b;
		if(a>b) swap(a,b);
		s[a-1]={0,i};
		s[b-1]={1,i};
	}
	int p=0;
	for(int i=0;i<2*n;i++) {
		int t=s[i].first, num=s[i].second;
		if(t==0) stk[++p]=num;
		else {
			if(stk[p]!=num) {
				cout<<"Yes";
				return 0;
			}
			p--;
		}
	}
	cout<<"No";
	return 0;
}
```



---

## 作者：2023lpx (赞：1)

## 题目大意

在一个圆上有 $2n$ 个点，每两个互不相同的点相连，问这些点所形成的弦相不相交。

## 思路

对于样例，我们先看一个图：

![](https://img.atcoder.jp/abc338/ff4c78532301561b18080c6a52985806.png)

转载自 [atcoder.jp](https://atcoder.jp/contests/abc338/editorial/9181)

我们把原来的圆展开成一条链，可以发现：

- 原来的图的形态还在。
  
- 如果有弦相交，那么那两条弦的端点在链上也一定是相交的。
  

所以这道题可以用**栈**来做。

我们用一个栈 $S$ 记录现在**待匹配的点的另一半**。

每次进栈时就判断其对应的另一半是否在栈里：

- 在，判断其是否在栈顶。
  
  - 在，弹栈。
    
  - 不在，代表有弦相交，输出 ```Yes```。
    
- 否，压栈。
  

若操作全部合法，输出 ```No```。

于是问题圆满解决。

时间复杂度 $O(n)$。

## code

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int const maxn=200000;
int n;
int a[maxn+1],b[maxn+1];
int num[maxn*2+1];
int stack[maxn*2+1];
int top;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
        if(a[i]>b[i]){
            swap(a[i],b[i]);
        }
        num[a[i]]=b[i];
        num[b[i]]=a[i];
    }
    for(int i=1;i<=n*2;i++){
        if(num[i]>i){
            top++;
            stack[top]=i;
        }
        else{
            if(stack[top]==num[i]){
                top--;
            }
            else{
                printf("Yes");
                return 0;
            }
        }
    }
    printf("No");
    return 0;
}
```

---

## 作者：WilliamFranklin (赞：1)

### 主要思路

看到这道题，我首先想到的是“化曲为直”。。。

考虑将这些弦看作一些线段，然后就将这个问题转化成了是否有两个不相同的数 $i$ 和 $j$ 满足第 $i$ 个线段和第 $j$ 个线段有交集且第 $i$ 个线段不包含第 $j$ 个线段，第 $j$ 个线段不包含第 $i$ 个线段。

那么这个问题就好解决了，我们就只用看，线段 $i$ 所覆盖的区域中是否存在一个点满足以它为端点的线段的另一个端点在线段 $i$ 的外面。

我们从小到大做，就又转化成了线段 $i$ 所覆盖的区域中是否存在一个点满足以它为端点的线段的另一个端点大于线段 $i$ 的右端点。

最后这就变成了一个区间求最大值的问题。

看下代码吧（用线段树做的）。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2e5 + 5;
int n;
struct node {
	int maxn;
	int l, r;
} tr[N * 8];
int a[N * 2];
void pushup(int u) {
	tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
}
void build(int u, int l, int r) {
	tr[u].l = l, tr[u].r = r;
	if (l == r) {
		tr[u].maxn = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}
int query(int u, int x, int y) {
	if (x <= tr[u].l && tr[u].r <= y) {
		return tr[u].maxn;
	}
	int ans = 0;
	int mid = tr[u].l + tr[u].r >> 1;
	if (x <= mid) ans = max(ans, query(u << 1, x, y));
	if (y > mid) ans = max(ans, query(u << 1 | 1, x, y));
	return ans;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		a[x] = y;
		a[y] = x;
	}
	build(1, 1, 2 * n);
	for (int i = 1; i <= 2 * n; i++) {
		if (a[i] > i) {
			if (a[i] == i + 1) continue;
			if (query(1, i + 1, a[i] - 1) > a[i]) {
				cout << "Yes";
				return 0;
			}
		}
	}
	cout << "No";
	return 0;
} 
```

### 谢谢观看

---

## 作者：yshpdyt (赞：0)

## 题意
一个圆，上面有 $2n$ 个点均匀分布，给定 $n$ 条弦，判断有无交点。

## Sol
经典套路。

注意到实际上就是判断区间是否相交，保证区间 有 $[l,r]$，$l<r$，然后左端点升序排序，依次增加右端点，每次判断区间内是否包含其他区间的右端点即可。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1200005
#define endl "\n" 
#define x first
#define y second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n;
pair<ll,ll>p[N];
namespace tr{
    #define mid ((l+r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    ll mx[N],lzy[N];
    void lt(ll p,ll x){
        mx[p]+=x;
        lzy[p]+=x;
    }
    void build(ll p,ll l,ll r){
        mx[p]=lzy[p]=0;
        if(l==r){
            mx[p]=0;
            return ;
        }
        build(ls,l,mid);
        build(rs,mid+1,r);
        mx[p]=max(mx[ls],mx[rs]);
    }
    void pushdown(ll p){
        lt(ls,lzy[p]);
        lt(rs,lzy[p]);
        lzy[p]=0;
    }
    void upd(ll p,ll l,ll r,ll le,ll ri,ll t){
        if(le<=l&&ri>=r){
            lt(p,t);
            return ;
        }
        pushdown(p);
        if(le<=mid)upd(ls,l,mid,le,ri,t);
        if(ri>mid)upd(rs,mid+1,r,le,ri,t);
        mx[p]=max(mx[ls],mx[rs]);
    }
    ll qr(ll p,ll l,ll r,ll le,ll ri){
        if(le<=l&&ri>=r)return mx[p];
        pushdown(p);
        ll ans=-inf;
        if(le<=mid)ans=max(ans,qr(ls,l,mid,le,ri));
        if(ri>mid)ans=max(ans,qr(rs,mid+1,r,le,ri));
        return ans;
    }
}using namespace tr;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        if(p[i].x>p[i].y)swap(p[i].x,p[i].y);
    }
    sort(p+1,p+n+1);
    build(1,1,n);
    for(int i=1;i<=n;i++){
        if(qr(1,1,n+n,p[i].x,p[i].y)>0){
            cout<<"Yes\n";
            return 0;
        }
        upd(1,1,n+n,p[i].y,p[i].y,1);
    }
    cout<<"No\n";
    return 0;
    return 0;
}


```

---

## 作者：zsyzsy_2012 (赞：0)

树状数组板子题。

先按照 $A _ {i}$ 的大小排序，然后从 $1$ 到 $n$ 遍历，设当前值为 $i$，发现只有对于 $j<i$，且 $A _ {i}<B _ {j}<B _ {i}$ 时才能形成交点。这显然是一个树状数组经典问题，我们定义一个 $C$ 数组，每次把 $C_{B _ {i}}$ 加上 $1$，然后求 $ {\textstyle \sum_{A _ {i} + 1}^{B _ {i} - 1}C _ {i}} $ 就可以。这道题有一个坑点：如果 $A _ {i} > B _ {i}$，记得刚开始时就要交换。

下面是本题的 AC 代码：

```
//By zsyzsy_2012 2024.1.29 15:20
#include <bits/stdc++.h>
#define N 200010
#define lowbit(x) (x & -x)
using namespace std ;
int n , c[N * 8] ;
void modify(int x , int y) {
	for( ; x <= 2*n ; x += lowbit(x)) {
		c[x] += y ;
	}
}
struct node{
	int a,b;
}s[N];
bool cmp(node p , node q){
	return p.a < q.a;
}
int find(int x) {
	int ans = 0 ;
	for( ; x > 0 ; x -= lowbit(x)) {
		ans += c[x] ;
	}
	return ans ;
}
signed main() {
	scanf("%d" , &n) ;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&s[i].a,&s[i].b);
		if(s[i].a > s[i].b)swap(s[i].a,s[i].b);
	}
	sort(s+1,s+1+n,cmp);
	for(int i = 1 ; i <= n ; i++) {
		int now=find(s[i].b-1)-find(s[i].a);
		if(now){
			puts("Yes");
			return 0;
		}
		modify(s[i].b,1);
	}
	puts("No");
	return 0 ;
}
```


---

## 作者：MrPython (赞：0)

**阅前注意：本文下标均从 0 开始，代码通常遵循“左闭右开”规则。**
## 题意简述
在圆上有 $N$ 条弦（不会共用一个端点），判断是否有任意两条弦相交。

## 思路简析
圆上问题不好想，不如转换成 OIer 们喜闻乐见的序列问题。将圆从 $2N-1$ 号点与 $0$ 号点间断开，拉直，让它变成区间问题。

例如：  
![1706595909043.png](https://img2.imgtp.com/2024/01/30/huPknssU.png)  
可以转化成：  
![1706596374816.png](https://img2.imgtp.com/2024/01/30/948wyUih.png)  

容易发现，当两条弦相交时，当且仅当他们所对应**的区间不存在包含关系但有重叠**（形式化的，对于区间 $[a,b]$ 与 $[c,d]$，应满足 $a<c<b<d$ 或 $c<a<d<b$）。此时可以通过两层循环枚举两个区间，实现 $O(N^2)$ 的暴力做法。

如何优化到题目可接受的复杂度内？我使用了**树状数组**。

具体来说：
1. 维护一个树状数组，初始全部为 $0$
2. 按照左端点从小到大的顺序枚举区间
	1. 先判断区间两端的单点值是否相同，若不相同则说明出现交点
    2. 否则将该区间内元素 $+1$。

## 正确性证明
证明可能有不严谨，还请谅解，理解万岁。

假如数组内已经存入了区间 $[a,b]$。那么对于满足 $a\le i\le b$ 的任意 $i$，其树状数组单点查询的结果 $f_i = 1$。加入第二个区间 $ [c,d] $ 时，按左端点排序使其必定满足 $a<c$。那么 $[c,d]$ 与 $[a,b]$ 的关系有以下几种：
- $a<b<c<d$，此时 $f_c=f_d=0$，区间无重合。
- $a<c<b<d$，此时 $f_c=1,f_d=0$，两个区间满足题目要求。
- $a<c<d<b$，此时 $f_c=f_d=1$，两个区间是包含关系，不会产生交点。


## 代码
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
// 树状数组类，随用随拷贝
class FenwickTree{
    vector<int> tree;
    int prefix_sum(size_t p) const{
        int res=0;
        for (--p;p<tree.size();p=(p&p+1)-1) res+=tree[p];
        return res;
    }
public:
    FenwickTree(size_t n):tree(n){}
    void add_point(size_t p,int const& val){
        for (;p<tree.size();p|=p+1) tree[p]+=val;
    }
    int get_sum(size_t l,size_t r) const{
        return prefix_sum(r)-prefix_sum(l);
    }
    size_t size(void) const{return tree.size();}
};
class DifferenceFenwick{
    FenwickTree tree;
public:
    DifferenceFenwick(size_t n):tree(n){}
    friend istream& operator>>(istream& in,DifferenceFenwick& t){
        for (size_t i=0;i<t.size();i++){
            int x;
            in>>x;
            t.add_point(i,x);
        }
        return in;
    }
    void add_interval(size_t l,size_t r,int const& val){
        tree.add_point(l,val),tree.add_point(r,-val);
    }
    void add_point(size_t p,int const& val){add_interval(p,p+1,val);}
    int get_val(size_t p){return tree.get_sum(0,p+1);}
    size_t size(void){return tree.size();}
};
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n;
    cin>>n;
    vector<pair<ui,ui>> a(n);
    for (pair<ui,ui>& i:a){
        cin>>i.first>>i.second;
        if (--i.first > --i.second) swap(i.first,i.second); // 下标从 0 开始，因此全部 -1；检查大小关系，满足 左端点<右端点
    }
    sort(a.begin(),a.end());  // 按照左端点排序。std::pair 已经重载了相关运算符。
    DifferenceFenwick d(n*2); // 步骤 1
    for (pair<ui,ui> i:a){    // 步骤 2
        if (d.get_val(i.first)!=d.get_val(i.second)) cout<<"Yes",exit(0);  // 2.1
        d.add_interval(i.first,i.second+1,1);  // 2.2
    }
    cout<<"No";
    return 0;
}
```

---

## 作者：FL_sleake (赞：0)

**此题解所述做法无需线段树、树状数组等前置知识。**

### 题意简述

有 $2n$ 个点等距离地分布在一个圆上，从一个点开始顺时针以 $1$ 到 $2n$ 编号。  

现在有 $n$ 条弦，第 $i$ 条弦连接点 $a_i$ 和 $b_i$，保证所有 $a_1,\cdots,a_n,b_1,\cdots,b_n$ 不同。  

判断弦之间是否有交点。

### 解题思路

考虑分治。

定义函数 $solve(l,r)$ 表示从 $l$ 点出发顺时针到 $r$ 点的这一段点之间的连线是否有交点，则答案即为 $solve(1,n)$ 的值。

用数组 $to$ 记录下来每一个点连线的对应点是多少。对于 $solve(l,r)$，以 $to_l$ 为分界线进行分治。如果 $to_l$ 不在 $l,r$ 的范围内，则和之前划定的范围不符，一定出现交点。否则，进行 $solve(l+1,to_l-1)$ 和 $solve(to_l+1,r)$。注意如果 $l>r$ 则返回无交点。因为我们在进行 $solve(l+1,to_l-1)$ 时为了简便没有判断大小。

说起来有点抽象，实际上代码非常简便，可以结合代码理解一下。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define max(a,b) (a>b?a:b)
int n,a[200010],b[200010],to[400010];
int solve(int l,int r){
	if(l>r) return 0;
	if(!(to[l]>=l&&to[l]<=r)) return 1;
	return solve(l+1,to[l]-1)|solve(to[l]+1,r);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i],to[a[i]]=b[i],to[b[i]]=a[i];
	n*=2;
	cout<<(solve(1,n)?"Yes":"No")<<endl;
	return 0;
}
```

### 后记

事实上，本题还有一个括号匹配的做法。即可以将对应的两点类比成对应的括号，然后进行括号匹配。这种解法不再赘述，如有需要可以参考下面的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200010],b[200010],id[400010];
stack<int> s;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i],id[a[i]]=b[i],id[b[i]]=a[i];
	for(int i=1;i<=n*2;i++){
		if(!s.empty()&&id[s.top()]==i) s.pop();
		else s.push(i);
	}
	cout<<(s.empty()?"No":"Yes")<<endl;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

除了启发式合并那题以外见过的最简单 ABC E 题。

如果存在两条线段 $\{l_1,r_1\},\{l_2,r_2\}$ 满足 $r_1>l_2$，那么一定存在交点，也就是说，只要某条线段的一端在另一条线段里，且另一端不在，一定存在交点。为了维护是否有端点在线段里，考虑对每一条线段覆盖的所有点（即所有满足 $l\le i\le r$ 的 $i$）加上特殊标记（每条线段都不同），就可以判断是否存在这样的情况。考虑线段树，给区间加上一个值，并保证所有线段的特殊标记不同（也可以区间覆盖）。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int int
int d[1600010],b[1600010],a[1600010];
void update(int l,int r,int s,int t,int c,int p)
{
    if(l<=s&&t<=r)
    {
        d[p]+=(t-s+1)*c;
        b[p]+=c;
        return;
    }
    int m=s+((t-s)>>1);
    if(b[p]&&s!=t)
    {
        d[p<<1]+=b[p]*(m-s+1);
        d[p<<1|1]+=b[p]*(t-m);
        b[p<<1]+=b[p];
        b[p<<1|1]+=b[p];
    }
    b[p]=0;
    if(l<=m) update(l,r,s,m,c,p<<1);
    if(m<r) update(l,r,m+1,t,c,p<<1|1);
    d[p]=d[p<<1]+d[p<<1|1];
}
int query(int l,int r,int s,int t,int p)
{
    if(l<=s&&t<=r) return d[p];
    int m=s+((t-s)>>1);
    if(b[p]&&s!=t)
    {
        d[p<<1]+=b[p]*(m-s+1);
        d[p<<1|1]+=b[p]*(t-m);
        b[p<<1]+=b[p];
        b[p<<1|1]+=b[p];
    }
    b[p]=0;
    int ans=0;
    if(l<=m) ans+=query(l,r,s,m,p<<1);
    if(m<r) ans+=query(l,r,m+1,t,p<<1|1);
    return ans;
}
int main()
{
    int cnt=1,n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	int u,v;
    	cin>>u>>v;
    	if(u>v) swap(u,v);
    	if(query(u,u,1,n<<1,1)!=query(v,v,1,n<<1,1))
    	{
    		cout<<"Yes";
    		return 0;
		}
		update(u,v,1,n<<1,cnt,1);
		cnt=max(cnt+1,query(u,u,1,n<<1,1)+1); 
	}
	cout<<"No";
    return 0;
}

---

## 作者：_qingshu_ (赞：0)

~~怎么会有人 D 没看懂把 E 秒了啊。~~

# 题意：

给定一个总共有 $2\times N$ 个点的环，其中存在 $N$ 条线段，第 $i$ 条线段经过两个点 $l_i,r_i$。保证互不相同，询问途中有无相交线段。

# 思路：

首先，线段的 $l_i,r_i$ 不存在有序性，我们可以考虑将其转换成  $l_i<r_i$，这个操作并不会影响原本的线段。然后将这些线段按照左端点排序。

对于两个存在相交点的线段 $i,j(i<j)$，我们可以得知 $l_i<l_j<r_i<r_j$，所以我们现在的目标转为如何在 $\mathcal{O}(N)$ 的时间内求得是否存在满足条件的 $i,j$。

我们可以考虑遍历 $j$，因为在前面的所有线段中，一旦出现 $l_j>r_i$，那么 $i$ 线段就一定不会对答案产生贡献，否则最有可能产生相交的一定是 $r_i$ 最小的一个。

我们可以考虑使用优先队列记录前面的线段，以右端点为关键字从小到大排序，设 $k$ 为队列顶部，每当出现了 $l_j>r_k$ 的时候就弹出，表示不可能存在与其相交的线段，$l_j<r_k$ 的时候，若队列非空，那么 $k$ 点产生答案的可能最大，且如果 $k$ 无法产生贡献，那么其余线段均不可能产生。

总时间复杂度 $\mathcal{O}(N)$。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct edge{
	int l,r;
}e[5200010];
inline bool ccmp(edge x,edge y){
	return x.l<y.l;
}
struct cmp{
    inline bool operator()(int u,int v)const{
        return e[u].r>e[v].r;
    }
};
priority_queue<int,vector<int>,cmp>qq;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>e[i].l>>e[i].r;
		if(e[i].l>e[i].r){
			swap(e[i].l,e[i].r);
		}
	}
	stable_sort(e+1,e+n+1,ccmp);
	for(int i=1;i<=n;i++){
		while(!qq.empty()&&
        e[i].l>e[qq.top()].r){
			qq.pop();
		}
		if(!qq.empty()&&e[i].r>e[qq.top()].r){
			cout<<"Yes";
			exit(0);
		}
		qq.push(i);
	}
	cout<<"No";
	
}
```

---

## 作者：_JF_ (赞：0)

## [ABC338E] Chords 

算是最简单的一道 E 了吧，很一眼。

不妨考虑枚举每一条线段，看有没有线段和他相交，记一个点 $i$ 所连出去的线段的另一个端点是 $p_i$。

做法也很简单，就拿第二个样例作为举例，比如枚举到第二条线段时，我们只用找到 $[2,5]$ 之间所有点最大的 $p_i$ 是否要大于 $5$，如果有，那就一定有交点。维护的是最大值也能保证不会漏掉情况，因为他只问了你存在性。同理，找到 $[2,5]$ 最小的 $p_i$，如果小于 $2$，那也显然有交点。


维护静态区间最值随便弄个数据结构就好了吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =6e5+10;
int n,f[N][20],f1[N][20],Log[N];
struct node{
	int l,r;
}que[N];
int Querymax(int l,int r){
	int k=log2(r-l+1);
	return max(f[l][k],f[r-(1<<k)+1][k]);
}
int Querymin(int l,int r){
	int k=Log[r-l+1];
	return max(f1[l][k],f1[r-(1<<k)+1][k]);
}
int main()
{
	bool F=true;
	memset(f1,0x3f,sizeof(f1));
	cin>>n;
	for(int i=1,x,y;i<=n;i++)
		cin>>x>>y,que[i].l=x,que[i].r=y,f[x][0]=f1[x][0]=y,f[y][0]=f1[y][0]=x;
	for(int j=1;j<=log2(2*n);j++)
		for(int i=1;i+(1<<j)-1<=2*n;i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]),f1[i][j]=min(f1[i][j-1],f1[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=n;i++){
		if(que[i].l>que[i].r)	swap(que[i].l,que[i].r);
		if(que[i].l==1&&que[i].r==n||(que[i].l==que[i].r-1))	continue;
		int maxx=Querymax(que[i].l+1,que[i].r-1),minn=Querymin(que[i].l+1,que[i].r-1);
		if(maxx>que[i].r||minn<que[i].l)	F=false;
	}
	cout<<((F==false)?"Yes":"No")<<endl;
	return 0;
}
```


---

## 作者：OldDriverTree (赞：0)

# Solution
考虑破环成链，对于一条 $l$ 到 $r$ 的弦，看成两条线段：$l$ 到 $r$ 和 $r$ 到 $n+l$。

可以发现如果存在两条线段 $[l_1,r_1]$ 和 $[l_2,r_2](l_1<l_2)$ 存在重叠部分，且第二条线段不完全包含第一条线段，那么就会存在交点。

考虑把所有线段按左端点从小到大排序，用一个 $\texttt{set}$ 存之前线段的右端点，如果 $\texttt{set}$ 中存在一个右端点 $r$ 使得右端点在当前的区间里，那么就会存在交点，输出 `Yes`。

如果不存在，输出 `No`。

但是直接这样做样例 2 会 $\texttt{WA}$，可以发现，如果一条线段被另一条线段包含，那么这条线段对应的的第二个线段也不存在交点，特判一下即可。

时间复杂度 $O(N\log N)$。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=4e5;
bool st[N];
set<int> s;
int n;

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
struct range
{
	int l,r;
	bool operator <(range o)const {
		return l<o.l;
	}
}a[N];

int main()
{
	n=read();
	for (int i=0;i<n;i++)
	{
		int l=read(),r=read();
		if (l>r) swap(l,r);
		a[i<<1]={l,r},a[i<<1|1]={r,n+n+l};
	}
	n=n<<1,sort(a,a+n);
	for (int i=0;i<n;i++) {
		if (a[i].r>n&&st[a[i].r-n]) continue;
		auto it=s.upper_bound(a[i].l);
		if (it!=s.end()&&(*it)<a[i].r) return !printf("Yes");
		else if (it!=s.end()&&(*it)>a[i].r) st[a[i].l]=true;
		s.insert(a[i].r);
	}
	printf("No");
	return 0;
}
```

---

## 作者：0x282e202e2029 (赞：0)

## 题意简述

[题目传送门](/problem/AT_abc338_e)

在圆周上有 $2N$ 个等间距的点，沿顺时针方向标号为 $1$ 到 $2N$。

有 $N$ 条弦，其中第 $i$ 条弦连接点 $A_i$ 和 $B_i$。保证不同的弦连接的点互不相同。

请确定这些弦之间有无交点。

## 思路

注意到若两条弦相交，则无论把图形如何变化，这两条弦仍然相交。

因此，采用**化曲为直**的方法，把圆上的弦看作区间。问题转化为求这些区间有无交错。

对于这个新问题，我们用树状数组维护未被匹配的区间左端点数。

从头到尾扫一遍，遇到区间左端点把此位置的值 $+1$ 设为新的未匹配左端点，遇到右端点把对应左端点的值 $-1$ 匹配对应的左端点，若此时右端点和左端点的前缀和值不等，则意味着左右端点间有未被匹配的左端点，即存在交错区间，输出 `Yes`。反之，若扫完仍未发现交错区间，则输出 `No`。

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n, a, b;
int chord[400005] = {}, match[400005] = {};
int t[400005] = {}, res;

// 树状数组
inline int lowbit(int x) { return x & (-x); }
void modify(int x, int k) { while (x <= 2 * n) { t[x] += k, x += lowbit(x); } }
int query(int x) { res = 0; while (x > 0) { res += t[x], x -= lowbit(x); } return res; }

int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a >> b;
		chord[a] = chord[b] = i;
	}
	for (int i = 1; i <= 2 * n; ++i) {
		if (match[chord[i]] == 0) { // 区间左端点
			match[chord[i]] = i;
			modify(match[chord[i]], 1); // 设为未匹配
		}
	}
	for (int i = 1; i <= 2 * n; ++i) {
		if (match[chord[i]] != i) { // 区间右端点
			modify(match[chord[i]], -1); // 匹配左端点
			if (query(i) != query(match[chord[i]] - 1)) { // 存在交点
				cout << "Yes" << endl;
				return 0;
			}
		}
	}
	cout << "No" << endl; // 真的没有
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

首先，我们先断环为链，图也就成了这样子（拿样例一举例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/oavm2z6j.png?x-oss-process=image/resize,m_lfit,h_250,w_400)

我们发现，环上的交叉在链上仍然存在。

我们又发现，如果一条线 $[l,r]$ 如果没与其他线段相交，则去掉它内部的所有线段后，$l$ 和 $r$ 一定就挨一起了。

所以我们可以用一种类似“合法括号序列”的做法：

准备，依次对每个 $\forall1\le i\le 2\times n$ 的 $i$ 进行以下操作：

- 如果 $i$ 是某条线段的开始，则将 $i$ 所对应线段的编号加入栈。
- 如果 $i$ 是某条线段的结束，则将栈顶弹出，如果弹出的数不是 $i$ 所对应线段的编号，则有交叉，如果在程序结束时仍然没有交叉，则确实没有。

这个做法根据上面的结论比较好证明，就不证明了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a,b;
stack<int> st;
map<int,pair<int,int> > mp;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a>>b;
    	if(b<a) swap(a,b);
    	mp[a]={i,0},mp[b]={i,1};
	}
	for(int i=1;i<=2*n;i++){
		if(mp[i].second==0){
			st.push(mp[i].first);
		}
		else{
			if(st.top()!=mp[i].first){
				puts("Yes");
				return 0;
			}
			else{
				st.pop();
			}
		}
	}
	puts("No");
    return 0;
}

```


---

## 作者：Dtw_ (赞：0)

[atcoder](https://atcoder.jp/contests/abc338/tasks/abc338_e)

[luogu](https://www.luogu.com.cn/problem/AT_abc338_e)

# 题目大意

有 $2\times N$ 个点，在一个环上，给定 $N$ 条弦的起点和终点，问所有的弦有没有交点。

# 思路
我们一步一步来，按照人的思维方式慢慢展开，先易后难的想。

起初我把这题想的比较简单，以至于第一个思路是歪解，后面是正解。

一个环上考虑不太好想，我们可以把环剪开，贴一张 atcoder 官方题解上的图

![](https://img.atcoder.jp/abc338/ff4c78532301561b18080c6a52985806.png)

首先我们应该保证对于每条弦：起点小于终点，如果不是那 `swap` 一下。

我们可以用 `pair` 记录一下每条弦的起点和终点，按照起点排序：

如果第 $i$ 条弦的起点大于 $i-1$ 条弦的终点，并且 $i$ 条弦的终点大于 $i-1$ 条弦的终点，那就是有交点的。

注意：这里并不需要判断第 $1$ 条弦和第 $N$ 条弦，因为节点不是重叠的。

然后你就会写出来这样一份代码：


```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n;

vector<pair<int, int>> X;

signed main()
{
	cin >> n;
	for(int i=1; i<=n; i++)
	{
		int a, b;
		cin >> a >> b;
		if(a > b)
		{
			swap(a, b);
		}
		X.push_back(make_pair(a, b));
	}
	sort(X.begin(), X.end());
	for(int i=1; i<X.size(); i++)
	{
		if(X[i].fi < X[i-1].se && X[i].se > X[i-1].se)
		{
			cout << "Yes" << endl;
			return 0;
		}
	}
	cout << "No" << endl;
	return 0;
}


```



然后你会发现，错了（我只错了一个点）显然这是歪解：

![](https://cdn.luogu.com.cn/upload/image_hosting/sc8n684x.png)

这就被 hack 了，因为只能判断 $i$ 和 $i-1$ 所以就错了，那我们应该对于每个 $i$ 向前查找所有的 $j$ 满足 $j$ 的起点小于 $i$ 的终点且 $i$ 的终点大于 $j$ 的终点，那这样复杂度为 $O(\sum_{i=1}^{N} i)$ 也就是 $O(\frac{N(N+1)}{2})$ ，但 $N\leq 2\times10^5$ ，显然是过不了的。优化的话是可行的，但这里说一下另一种办法。考虑换一种思路。

## 正解

我们发现对于每一个起点都有一个匹配的终点，这很像括号序列。那么我们考虑用栈来维护每一个节点，对于每个节点当他作为起点时就入栈，如果遇到了和他相匹配的终点就出栈，如果遇到不匹配的终点那显然是存在交点的。

用结构体储存每一个点的状态，是起点还是终点，是几号弦的节点。
用 `vector` 储存遇到过的节点，因为题目保证没有重复的点所以这样是可以的。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n, m;

int s[N];

struct Node
{
	int op, id;
};

Node X[N];
vector<int> g;

signed main()
{
	cin >> n;
	for(int i=1; i<=n; i++)
	{
		int a, b;
		cin >> a >> b;
		if(a > b)
		{
			swap(a, b);
		}
		g.push_back(a);
		g.push_back(b);
		m++;
		X[a] = {0, m};
		X[b] = {1, m};
	}
	sort(g.begin(), g.end());
	stack<Node> st;
	for(auto v : g)
	{
		int op = X[v].op;
		int id = X[v].id;
		if(op == 0)
		{
			st.push({op, id});
		}
		else
		{
			if(st.top().id == id)
			{
				st.pop(); 
			}
			else
			{
				puts("Yes");
				return 0;
			}
		}
	}
	puts("No");
	return 0;
}




```




---

## 作者：CodingOIer (赞：0)

## [ABC338E] Chords 题解

### 思路分析

在本题中，每一条线可以看为将圆切分成了两半，只要它不跨越了两个区域就没有交叉。

就是个括号序列嘛！

每次将对应的变放到数组中，然后就是括号序列，匹配完则为没有交叉，反之亦然。

### 代码实现

感觉本次的 E 题好简单~

```cpp
/**
 * @file AtCoder\ABC338\E.cpp
 * @author CodingOIer (redefinition0726@163.com)
 * @brief AtCoder
 * @version 1.0
 * @date 2024-01-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdio>
#include <stack>
constexpr int MaxN = 2e5 + 5;
int n;
int p[MaxN * 4];
std::stack<int> stack;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        p[a] = a;
        p[b] = a;
    }
    for (int i = 1; i <= 2 * n; i++)
    {
        if (p[i] == 0)
        {
            continue;
        }
        if (!stack.empty() && stack.top() == p[i])
        {
            stack.pop();
        }
        else
        {
            stack.push(p[i]);
        }
    }
    printf("%s\n", stack.empty() ? "No" : "Yes");
    return 0;
}
```

---

## 作者：FreedomKing (赞：0)

某人赛时写了个线段树还没调出来我不说是谁。

### 题目大意

有一个圆，上面均匀分布着 $2\times N$ 个点，给出 $N$ 条边无重点地接满这些边，问是否存在任意两边产生交点。

### 思路

因为要存在交点，所以选定的这两条边必定有交集但不存在包含关系。

最开始糊了个随机想碰碰运气，结果喜提挂两个点，遂开始想正解。

第一眼看上去挺像线段树的，可以想到一个类似于维护每个节点哈希值每次加边判断此边两端点哈希值是否相等的做法，感觉是很对的，但是我没调出来。

直到赛后跟爆切了这场的大佬讨论此题解法，大佬说这就是个裸的括号匹配，一语点醒梦中人。

首先一定要保证每边两端点左小右大，具体做法就是将每条边染成一种颜色，开一个栈，然后记录其左端点是否入栈，如果此边左端点入过了转，当枚举到了它的右端点时且栈不为空，则必定有边符合存在交集但不存在包含关系了，否则弹出这条边即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,xN=1e7+5,mN=1e4+5,mod=1e9+7,mmod=998244353;
map<pair<int,int>,bool>mp;
priority_queue<int,vector<int>,less<int>>pq;
vector<int>e[N];
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){x/=gcd(x,y);return (x*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abs(int x){return (x>0?x:-x);}
}
int a[N];
bool vis[N];
signed main(){
	int n=qr;
	for(int i=1;i<=n;i++){
		int x=qr,y=qr;
		if(x>y) swap(x,y);
		a[x]=a[y]=i;
		vis[i]=true;
	}
	stack<int>st;
	for(int i=1;i<=(n<<1);i++){
		if(!vis[a[i]]){
			int tp=st.top();
			if(tp!=a[i]){
				puts("Yes");
				return 0;
			}
			else st.pop();
		}
		else{
			vis[a[i]]=false;
			st.push(a[i]);
		}
	}
	puts("No");
	return  0;
}
```

---

## 作者：Loser_Syx (赞：0)

我们称一个孤单的点 $i$ 为以 $x$ 号边为基准，其中 $i$ 在一侧，与 $i$ 对应的点在另一侧，显而易见，这样子 $i$ 所在边和 $x$ 号边是相交的。  
于是你可以断环成链，因为只需要知道是否存在相交的边，所以任意的孤单点 $i$ 都可以视为答案，考虑将一对点 $(a_i,b_i)$ 转化为贡献的形式。

因为 $(a_i,b_i)$ 其中有任意一个孤单点的话，$x$ 的某一个顶点一定在 $[a_i,b_i]$ 之内，另一个一定在外面，于是就可以考虑对 $[a_i,b_i]$ 进行差分操作，记差分数组为 $c$，最后再将 $c$ 转化为前缀和的形式。  
因为 $x$ 一定是横穿 $(a_i,b_i)$ 的，所以我们如果 $x$ 的任意一侧，出现了 $c_{b_i}-c_{a_i} \neq 0$ 的情况，那么说明有孤单点了。

为了保证差分的正确性，我们需要保证 $a_i < b_i$。

因为所有的 $a_i,b_i$ 都不相等，所以每个点只会与一个点连边，故保证了正确性。

复杂度为 $O(n)$。

```cpp
const int N=4e5+19;
int a[N];
struct node {
	int x, y;
} b[N];
signed main() {
	int n=read();
	for (int i=1;i<=n;++i) {
		int x,y; read(x,y);
		if (x>y) swap(x, y);
		b[i] = {x,y};
		a[x]++; a[y+1]--;
	}
	for (int i=1;i<N;++i) a[i]+=a[i-1];
	//for (int i=1;i<10;++i) cout << a[i] << ' ';
	for (int i=1;i<=n;++i) {
		if (a[b[i].y] - a[b[i].x]) return cout << "Yes",0;
	}cout << "No";
	return 0;
} 
```

---

## 作者：xz001 (赞：0)

我们形象地想一想，两条线相交，就是说其中一条线卧在圆上，另一条从其中穿出。

也就是说若 $(x,y)$ 与 $(a,b)$ 相交，要么 $x<a<y<b$，要么 $a<x<b<y$。

所以问题就变成了，求一对 $(i,j)$，使得 $a_i<a_j<b_i<b_j$。

我们可以维护区间最大 $b_j$，然后枚举每一条线，判断区间 $(a_i,b_i)$ 内最大的 $b_j$ 是否大于 $b_i$ 即可。

代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, mod = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, a[N], b[N], st[N][22];

int query (int l, int r) {
	int s = log2 (r - l + 1);
	return max(st[l][s], st[r - (1 << s) + 1][s]);
}

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i) {
    	scanf("%lld%lld", a + i, b + i);
    	if (a[i] > b[i]) swap(a[i], b[i]);
	}
    for (int i = 1; i <= n; ++ i) {
    	st[a[i]][0] = max(st[a[i]][0], b[i]);
	}
	for (int j = 1; j <= 20; ++ j)
	    for (int i = 1; i + (1 << j) - 1 <= 2 * n; ++ i)
	        st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	        
	for (int i = 1; i <= n; ++ i) {
		if (a[i] == b[i]) continue;
		if (query (a[i] + 1, b[i] - 1) > b[i]) {
			puts("Yes");
			return 0;
		}
	}
	puts("No");
    return 0;
}


```

---

## 作者：Hog_Dawa_IOI (赞：0)

第一次 ABC 中 $34$ 分钟之后通过 E 题（尽管没有把 D 题 A 掉），为了纪念写篇题解。     

题意：有 $2n$ 个点均匀分布在一个圆上，顺时针方向由 $1$ 到 $2n$ 依次编号。在这个圆内有 $n$ 条边，每条边连接不同的 $2$ 个点，没有一个点同时连接 $2$ 条或以上的边（换句话说，这些边都是这个圆的弦）。问是否有弦相交。  
（数学中弦的定义：连接圆上任意两点的线段叫做弦。）    

官方题解的图不是很契合我当时的第一想法，自己造个图。     
![](https://cdn.luogu.com.cn/upload/image_hosting/4wrsw9s7.png)   
造的很丑，但是基本符合我当时的想法：把“弦”拆到圆外面去，可以更加直观地看到，两条边如果相交，那么其中一条边的一个端点会处于另一条边两个端点之间。         
再抽象一点，一条边看做一对括号，那么如果有边相交，那么这个括号就无法被匹配。     
那么问题就变成判断这些规定好的括号对匹配不匹配。这就很典了：用一个栈，遇到左括号就入栈，遇到右括号就判断栈顶和当前右括号是不是同一对，是就弹栈顶，不是就直接输出 `No`。      
不过事实上我们可以不用在实际上把它真的变成一个括号序列，可以用数字来代替，这样既能方便地判断两个点是否在同一对“括号”内，又能暗中调整好“左括号”和“右括号”的顺序。     
最后总结一下算法流程：     
1. 对每个点用它来自的边的编号重新编号。
2. 从点 $1$ 到点 $2n$ 进行遍历。   
- 如果这个点是这一对中第一个出现的点，那么说明我们把它当做左括号，把这个点所在的边的编号加入栈。  
- 如果不是，那么我们把它当做右括号，判断栈顶的“左括号”是否和当前点是同一对，是就弹栈，否则输出 `No`。
3. 如果到最后括号序列完美匹配成功，那么输出 `Yes`。   

附上超级短小精悍的代码：
```cpp
#include<stdio.h>
long long n,a,b,zhan[400005],num[400005];bool f[200005];
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a,&b),num[a]=num[b]=i;
    for(int i=1;i<=2*n;i++)
    {
        if(!f[num[i]]) zhan[++zhan[0]]=num[i],f[num[i]]=1;
        else if(zhan[zhan[0]]==num[i]) zhan[0]--,f[num[i]]=0;
        else {printf("Yes");return 0;}
    }
    printf("No");
}
```

---

## 作者：yyrwlj (赞：0)

## 题意简述

有 $n \times 2$ 个点顺次排成一圈，有 $n$ 条线段不重不漏的连接了这些点，给出这 $n$ 条线段连接的两个点编号，问是否有线段相交。

## 思路

设某条线段连接的两个点编号分别是 $a$ 和 $b$（$a < b$），那么有其它线段和这条线段相交，当且仅当有其它线段的一个端点编号在区间 $[a, b]$ 内，另一个不在。

考虑记录每个点对应的另一个点是什么，然后线段树维护区间最值查询。

## Code

```cpp
#include <iostream>
using namespace std;
const int N = 200005;
pair<int, int> g[N];
int to[N << 1], w[N << 3][2];
void build(int u,int l,int r)
{
    if (l == r)
    {
        w[u][0] = w[u][1] = to[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    w[u][0] = min(w[u << 1][0], w[u << 1 | 1][0]);
    w[u][1] = max(w[u << 1][1], w[u << 1 | 1][1]);
}
int query(int u,int l,int r,int L,int R,int op)
{
    if (L <= l && r <= R)
        return w[u][op];
    int mid = (l + r) >> 1, ans = 0;
    if (op == 0)
    {
        ans = 1e9;
        if (L <= mid)
            ans = query(u << 1, l, mid, L, R, 0);
        if (mid < R)
            ans = min(ans, query(u << 1 | 1, mid + 1, r, L, R, 1));
    }
    else
    {
        if (L <= mid)
            ans = query(u << 1, l, mid, L, R, 1);
        if (mid < R)
            ans = max(ans, query(u << 1 | 1, mid + 1, r, L, R, 1));
    }
    return ans;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        g[i] = {a, b};
        to[a] = b;
        to[b] = a;
    }
    const int m = n * 2;
    build(1, 1, m);
    for (int k=1;k<=n;k++)
    {
        int a = g[k].first, b = g[k].second;
        if (a > b)
            swap(a, b);
        if (b - a == 1 || a == 1 && b == m)
            continue;
        int mn = query(1, 1, m, a + 1, b, 0);
        int mx = query(1, 1, m, a + 1, b, 1);
        if (mn < a || mx > b)
        {
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}
```

---

