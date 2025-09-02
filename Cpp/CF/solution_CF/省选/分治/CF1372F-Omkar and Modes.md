# Omkar and Modes

## 题目描述

Ray lost his array and needs to find it by asking Omkar. Omkar is willing to disclose that the array has the following qualities:

1. The array has $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) elements.
2. Every element in the array $ a_i $ is an integer in the range $ 1 \le a_i \le 10^9. $
3. The array is sorted in nondecreasing order.

Ray is allowed to send Omkar a series of queries. A query consists of two integers, $ l $ and $ r $ such that $ 1 \le l       \le r \le n $ . Omkar will respond with two integers, $ x $ and $ f $ . $ x $ is the mode of the subarray from index $ l $ to index $ r $ inclusive. The mode of an array is defined by the number that appears the most frequently. If there are multiple numbers that appear the most number of times, the smallest such number is considered to be the mode. $ f $ is the amount of times that $ x $ appears in the queried subarray.

The array has $ k $ ( $ 1 \le k \le \min(25000,n) $ ) distinct elements. However, due to Ray's sins, Omkar will not tell Ray what $ k $ is. Ray is allowed to send at most $ 4k $ queries.

Help Ray find his lost array.

## 说明/提示

The first query is $ l=1 $ and $ r=6 $ . The mode is $ 2 $ , and $ 2 $ appears $ 2 $ times, so $ x=2 $ and $ f=2 $ . Note that $ 3 $ also appears two times, but $ 2 $ is outputted because $ 2 $ is smaller.

The second query is $ l=1 $ and $ r=3 $ . The mode is $ 2 $ and $ 2 $ appears twice in the subarray with indices $ [1,3] $ .

The third query is $ l=4 $ and $ r=6 $ . The mode is $ 3 $ and $ 3 $ appears twice in the subarray with indices $ [4,6] $ .

The fourth query is $ l=3 $ and $ r=4 $ . The mode is $ 2 $ , which appears once in the subarray with indices $ [3,4] $ . Note that $ 3 $ also appears once in that range, but $ 2 $ is smaller than $ 3 $ .

## 样例 #1

### 输入

```
6

2 2

2 2

3 2

2 1```

### 输出

```
? 1 6

? 1 3

? 4 6

? 3 4

! 1 2 2 3 3 4```

# 题解

## 作者：syzf2222 (赞：6)

[或许更好的体验](https://www.cnblogs.com/syzf2222/p/15836804.html)

吐槽一句，这个不降的条件在翻译里属实是有些隐蔽。

考虑分治地处理，用 $solve(l,r)$ 求出区间 $[l,r]$ 内的所有数值。

求一遍区间众数 $x$ 和出现次数 $y$。若我们已经知道一个位置 $a_p=x$ ，则我们可以使用两次询问求出这个区间。

具体地，我们知道 $[p-y+1,p]$ 和 $[p,p+y-1]$ 之间一定至少有一个的众数也为 $x$。

如果我们还不知道，那么隔 $y$ 询问一个单点，注意到我们询问的每一个数都不同，且一定可以询问到一个 $x$。

但是这样还是会有很多重复的询问浪费了，于是我们利用以前的信息，从之前的最后一个比 $x$ 小的数的位置开始。

这样的话，询问区间众数一个 $k$，询问每个单点一个 $k$，确定区间两个 $k$，正好 $4k$，做完了。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,a[maxn];
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
map<int,int>mp;
map<int,int>::iterator it;
inline pii ask(int l,int r){
	if(l<1)l=1;if(r>n)r=n;
	if(l>r)return mkp(0,0);
	printf("? %d %d\n",l,r);
	fflush(stdout);
	int x=read(),y=read();
	return mkp(x,y);
}
inline void solve(int l,int r){
	if(l>r)return;
	//printf("solving interval:[%d,%d]\n",l,r);
	pii now=ask(l,r);
	int x=now.fi,y=now.se;
	if(r-l+1==y){
		for(int i=l;i<=r;i++)a[i]=x;
		mp[x]=l;return;
	}
	if(!mp[x]){
		it=mp.lower_bound(x);--it;
		for(int i=max(l,it->se+y);;i+=y){
			pii cur=ask(i,i);
			mp[cur.fi]=i;
			if(cur.fi==x)break;
		}
	}int pos=mp[x];
	pii L=ask(pos-y+1,pos);
	pii R=ask(pos,pos+y-1);
	int lb=0,rb=0;
	if(L.fi==x)lb=1+pos-L.se,rb=lb+y-1;
	else lb=pos+R.se-y,rb=lb+y-1;
	for(int i=lb;i<=rb;i++)a[i]=x;
	solve(l,lb-1);solve(rb+1,r);
}
int main(){
	mp[0]=0;
	n=read();solve(1,n);
	printf("! ");
	for(int i=1;i<=n;i++)
		printf("%d ",a[i]);puts("");
	fflush(stdout);
    return 0;
}
```

---

## 作者：win114514 (赞：2)

来个乱搞。

### 思路

考虑分治。

对于最裸的暴力。

我们可以调用 `solve(l, r)` 进行查询。

假如这个区间的众数的出现次数是区间长度，那么可以直接退出，否则我们可以继续分治。

我们把这个暴力进行加工一下。

我们知道 $l\sim r$ 的区间众数后。

1. 查询 $l\sim mid$ 的区间众数，若完全与 $l\sim r$ 一样，那么可以继续分治下去。

2. 若仅有出现次数不一样，那么意味着我们已经知道了这个数的出现位置，可以直接构造答案，从两侧继续分治。

3. 若都不一样，我们再查询 $mid\sim r$ 的区间众数，可以仿照第一条第二条继续构造。

感觉是一个比较粗糙的做法，但又好像比较难卡。

这个做法的上下界我也不会算，如果有人可以 Hack 也比较正常。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for(int i = (x); i <= (y); i++)
#define pre(i, x, y) for(int i = (x); i >= (y); i--)
inline void JYFILE19();

typedef long long i64;
typedef pair<int, int> PII;

bool ST;
const int N = 1e6 + 10;
const int mod = 998244353;

int n, m, a[N];
map<PII, PII> mp;

inline PII ask(int l, int r) {
  if(mp.count({l, r})) {
    return mp[{l, r}];
  }
  cout << "? " << l << " " << r << endl;
  int x, f;
  cin >> x >> f;
  return mp[{l, r}] = {x, f};
}
inline void solve(int l, int r) {
  if(l > r) return;
  int mid = (l + r) >> 1, x, f;
  tie(x, f) = ask(l, r);
  if(f == r - l + 1) {
    fro(i, l, r) a[i] = x;
    return;
  }
  int y, g, ls, rs;
  tie(y, g) = ask(l, mid);
  if(x == y && g != f) {
    ls = mid - g + 1, rs = ls + f - 1;
    fro(i, ls, rs) a[i] = x;
    solve(l, ls - 1);
    solve(rs + 1, r);
    return;
  }
  if(x == y) {
    solve(l, mid);
    solve(mid + 1, r);
    return;
  }
  tie(y, g) = ask(mid + 1, r);
  if(x == y && g != f) {
    rs = mid + g, ls = rs - f + 1;
    fro(i, ls, rs) a[i] = x;
    solve(l, ls - 1);
    solve(rs + 1, r);
    return;
  }
  solve(l, mid);
  solve(mid + 1, r);
  return;
}

signed main() {
  JYFILE19();
  cin >> n;
  solve(1, n);
  cout << "! ";
  fro(i, 1, n) {
    cout << a[i] << " ";
  }
  cout <<"\n";
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen("", "r", stdin);
  // freopen("", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED-&ST)/1048576.), LIM = 32;
  cerr << "MEMORY: " << MIB << endl, assert(MIB<=LIM);
}
```

---

## 作者：Inui_Sana (赞：0)

挺有趣的题。

交互题，无非就是要做到一点：把他给你的抽象的操作转化成“能通过这些操作得到什么具体的，和题目有关的信息”。

首先容易发现，如果我们知道了每个数出现的次数就可以还原出来整个序列。考虑从这方面入手。

然后考虑，先询问 $[1,n]$ 的众数显然可以得到一个数的出现次数。然后如果想要直到其他数的呢？那我们就要尽量避免问到同样的数。

具体地，若 $[1,n]$ 的众数 $x$ 出现次数为 $y$，考虑将当前序列分成若干个长度等于 $y$ 的块，剩下一个不满的单独一块。此时就有很好的性质了：

- 每种数至多作为众数返回 $2$ 次，因为它最多在两块中出现。

- 当前的 $x$ 一定在至少一块中作为众数出现一次。原因显然。

那么先考虑确定当前 $x$ 的出现区间，这样就可以递归成若干个子问题去找其他数。事实上这是简单的。

首先，若 $x$ 刚好占了一块的位置。那么询问这块返回的一定是 $(x,y)$。容易判断。

否则，考虑 $x$ 一定不包含于那个返回 $x$ 为众数的块。于是设返回了 $(x,y')$，那么询问这一块的前 $y'$ 个，就能知道 $x$ 是这一块的前 $y'$ 个还是后 $y'$ 个。又因为我们知道 $y$，于是剩下的 $x$ 位置也能一并求出（前一块的后 $y-y'$ 个或后一块的 $y-y'$ 个）。

然后只需要把 $x$ 给去掉，对于每一块剩下的部分分别当作子问题处理即可。这样每种数只会被查询到 $3$ 次。

但是容易发现一个问题：上面提到每种数至多作为众数返回 $2$ 次。如果这里去到 $2$ 是不是就寄了？

但是发现，如果一个数 $x$ 占一个块的前缀，并且在前面的块出现过。那么只要有一次询问到的众数是 $x$，只需要更新 $x$ 的出现次数，并且把 $x$ 去掉，对于剩下的部分继续做即可。

容易发现这样只需要从左到右做，由于后面部分的块长一定大于这个 $x$ 的出现次数 $y$（否则众数是 $x$，块长为 $y$），所以只需要 $3+1=4$ 次。刚好足够。这样问题就解决了。

具体实现参考代码，有一些边界要注意特判。

code：

```cpp
int n,m;
pii a[N];
map<int,int> c;
il pii ask(int l,int r){
	if(l>r){
		return Mp(0,0);
	}
	printf("? %d %d\n",l,r);
	fflush(stdout);
	int x,y;read(x);
	if(x==-1){
		assert(0);
	}
	read(y);
	return Mp(x,y);
}
void solve(int l,int r,int x,int y){
	if(l>r){
		return;
	}
	c[x]+=y;
	if(y==r-l+1){
		return;
	}
	if(c[x]!=y){
		auto [u,v]=ask(l+y,r);
		return solve(l+y,r,u,v);
	}
	int p=0;
	for(int i=l;i<=r;i+=y){
		a[i]=ask(i,min(i+y-1,r));
	}
	for(int i=l;i<=r;i+=y){
		if(i+y<=r&&a[i].fi==x&&a[i+y].fi==x){
			p=i+y-a[i].se;
			a[i]=ask(i,p-1),a[i+y]=ask(p+y,min(i+y+y-1,r));
			break;
		}
		if(a[i].fi==x){
			auto [u,v]=ask(i,i+a[i].se-1);
			if(u==x&&v==a[i].se){
				p=i-y+a[i].se;
				if(y!=a[i].se){
					a[i]=ask(p+y,min(i+y-1,r));
					a[i-y]=ask(i-y,p-1);
				}
			}else{
				p=i+y-a[i].se;
				if(y!=a[i].se){
					a[i]=ask(i,p-1);
					a[i+y]=ask(p+y,min(i+y+y-1,r));
				}
			}
		}
	}
	for(int i=l;i<=r;i+=y){
		if(i<p){
			solve(i,min(i+y-1,p-1),a[i].fi,a[i].se);
		}
		if(i>p){
			solve(max(i,p+y),min(i+y-1,r),a[i].fi,a[i].se);
		}
	}
}
void Yorushika(){
	read(n);
	auto [x,y]=ask(1,n);
	solve(1,n,x,y);
	printf("! ");
	for(auto [x,y]:c){
		rep(i,1,y){
			printf("%d ",x);
		}
	}
	puts("");
	fflush(stdout);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Missa (赞：0)

尝试证明一下 [syzf2222 的题解](https://www.luogu.com.cn/article/k4w77x5i) 的正确性。

有时可能称 $a_p$ 的值为颜色。

$4k$ 的来源为：找到一个 $a_p=x$ 一次，找到颜色 $x$ 的出现次数一次，根据以上两个信息求出 $x$ 的出现位置两次。

可以发现分治的 $(l, r)$ 一定满足 $a_{l-1} \neq a_l \cap a_{r} \neq a_{r+1}$，即同一种颜色不会被分隔开。由于每次去掉区间最小众数所在区间后递归，显然找到所有颜色的出现次数这一步是使用 $k$ 次询问的。

回忆做法，假如已知 $(l, r)$ 的最小众数 $x$ 出现 $y$ 次，且不知道一个位置为 $x$，我们找到最大的 $p'$，满足 $a_{p'}$ 已知且小于 $x$，每次往后跳 $y$ 步，询问该点颜色并保存，询问到任意颜色为 $x$ 的点即可。容易发现这个过程一定不会跳过值为 $x$ 的那段区间。只要证明这里询问的单点颜色两两不同，就能证明找到任意颜色 $x$ 所在位置这一步的次数也是 $k$。

一定不会问到之前分治时已知的颜色，因为我们的起点是最大的已知数值的小于 $p$ 的位置，中间的数值一定都没被问过。同时，因为区间一定包含整段颜色，且 $x$ 为区间众数，区间内同一个颜色至多被问一次。这就证明了整个过程中不会重复问同一个颜色。

~~这是蓝？~~

---

