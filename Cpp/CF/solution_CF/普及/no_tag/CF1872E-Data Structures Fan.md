# Data Structures Fan

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ , as well as a binary string $ ^{\dagger} $ $ s $ consisting of $ n $ characters.

Augustin is a big fan of data structures. Therefore, he asked you to implement a data structure that can answer $ q $ queries. There are two types of queries:

- "1 $ l $ $ r $ " ( $ 1\le l \le r \le n $ ) — replace each character $ s_i $ for $ l \le i \le r $ with its opposite. That is, replace all $ \texttt{0} $ with $ \texttt{1} $ and all $ \texttt{1} $ with $ \texttt{0} $ .
- "2 $ g $ " ( $ g \in \{0, 1\} $ ) — calculate the value of the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of the numbers $ a_i $ for all indices $ i $ such that $ s_i = g $ . Note that the $ \operatorname{XOR} $ of an empty set of numbers is considered to be equal to $ 0 $ .

Please help Augustin to answer all the queries!

For example, if $ n = 4 $ , $ a = [1, 2, 3, 6] $ , $ s = \texttt{1001} $ , consider the following series of queries:

1. "2 $ 0 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{0} $ , since $ s = \tt{1001} $ , these are the indices $ 2 $ and $ 3 $ , so the answer to the query will be $ a_2 \oplus a_3 = 2 \oplus 3 = 1 $ .
2. "1 $ 1 $ $ 3 $ " — we need to replace the characters $ s_1, s_2, s_3 $ with their opposites, so before the query $ s = \tt{1001} $ , and after the query: $ s = \tt{0111} $ .
3. "2 $ 1 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{1} $ , since $ s = \tt{0111} $ , these are the indices $ 2 $ , $ 3 $ , and $ 4 $ , so the answer to the query will be $ a_2 \oplus a_3 \oplus a_4 = 2 \oplus 3 \oplus 6 = 7 $ .
4. "1 $ 2 $ $ 4 $ " — $ s = \tt{0111} $ $ \to $ $ s = \tt{0000} $ .
5. "2 $ 1 $ " — $ s = \tt{0000} $ , there are no indices with $ s_i = \tt{1} $ , so since the $ \operatorname{XOR} $ of an empty set of numbers is considered to be equal to $ 0 $ , the answer to this query is $ 0 $ .

 $ ^{\dagger} $ A binary string is a string containing only characters $ \texttt{0} $ or $ \texttt{1} $ .

## 说明/提示

Let's analyze the first test case:

1. "2 $ 0 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{0} $ , since $ s = \tt{01000} $ , these are the indices $ 1, 3, 4 $ , and $ 5 $ , so the answer to the query will be $ a_1 \oplus a_3 \oplus a_4 \oplus a_5 = 1 \oplus 3 \oplus 4 \oplus 5 = 3 $ .
2. "2 $ 1 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{1} $ , since $ s = \tt{01000} $ , the only suitable index is $ 2 $ , so the answer to the query will be $ a_2 = 2 $ .
3. "1 $ 2 $ $ 4 $ " — we need to replace the characters $ s_2, s_3, s_4 $ with their opposites, so before the query $ s = \tt{01000} $ , and after the query: $ s = \tt{00110} $ .
4. "2 $ 0 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{0} $ , since $ s = \tt{00110} $ , these are the indices $ 1, 2 $ , and $ 5 $ , so the answer to the query will be $ a_1 \oplus a_2 \oplus a_5 = 1 \oplus 2 \oplus 5 = 6 $ .
5. "2 $ 1 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{1} $ , since $ s = \tt{00110} $ , these are the indices $ 3 $ and $ 4 $ , so the answer to the query will be $ a_3 \oplus a_4 = 3 \oplus 4 = 7 $ .
6. "1 $ 1 $ $ 3 $ " — $ s = \tt{00110} $ $ \to $ $ s = \tt{11010} $ .
7. "2 $ 1 $ " — we are interested in the indices $ i $ for which $ s_i = \tt{1} $ , since $ s = \tt{11010} $ , these are the indices $ 1, 2 $ , and $ 4 $ , so the answer to the query will be $ a_1 \oplus a_2 \oplus a_4 = 1 \oplus 2 \oplus 4 = 7 $ .

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
01000
7
2 0
2 1
1 2 4
2 0
2 1
1 1 3
2 1
6
12 12 14 14 5 5
001001
3
2 1
1 2 4
2 1
4
7 7 7 777
1111
3
2 0
1 2 3
2 0
2
1000000000 996179179
11
1
2 1
5
1 42 20 47 7
00011
5
1 3 4
1 1 1
1 3 4
1 2 4
2 0```

### 输出

```
3 2 6 7 7 
11 7 
0 0 
16430827 
47```

# 题解

## 作者：BINYU (赞：10)

## 题意：

给定一个的数组 $a$ 和一个 **01** 数组 $s$（长度均为 $n$），需要支持两个操作：

1. 将 $s$ 数组中的 $l$ 至 $r$ 取反。

2. 查询所有 $s_i$ 为 0 或 1 对应的 $a_i$ 的异或和。

## 思路：

### 1. 线段树：

注意到 $n \le 10^5$，显然 $O(n\log n)$ 的线段树可过，对于本题，只需建立一棵线段树维护区间修改和全局查询即可。

### 2. 前缀和：

首先有两个显而易见的性质：
1. 无论 $s$ 数组现在长啥样， 所有 $s_i$ 为 $0$ 对应的 $a_i$ 的异或和异或所有 $s_i$ 为 $1$ 对应的 $a_i$ 的异或和一定为从 $a_1$ 到 $a_n$ 的异或和。

2. 对于一次操作 1，我们可以把它分成 $r-l+1$ 次“单点修改版”的操作 1 逐个操作，这启发我们对单个数的修改进行深度思考。

根据性质 1，我们可以只维护所有 $s_i$ 为 1 对应的 $a_i$ 的异或起来的值，设为 $ans$

根据性质 2，我们可以对所有要被操作的 $a_i$ 分类讨论：

1. 原来 $s_i = 0$，则原来贡献为 $0$，现在贡献为 $0 \oplus a_i = a_i$。

2. 原来 $s_i = 1$，则原来贡献为 $a_i$，现在贡献为 $a_i \oplus a_i = 0$。

可以发现，无论原来的 $s_i$ 为 0 还是 1，$ans$ 都会异或上 $a_i$，所以可以直接维护 $a$ 的前缀异或和 $sum$，使每一次操作 1 变为：$ans = ans \oplus sum_r \oplus sum_{l-1}$。

操作 1 和 2 的时间复杂度均为 $O(1)$，总时间复杂度 $O(n)$，比线段树要快。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls id << 1
#define rs id << 1 | 1
int t,n,q,op,l,r,x,a[100005];
int ans,sum[100005];
char s[100005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)
			scanf("%d",&a[i]);
		scanf("\n%s",s + 1);
		ans = 0;
		for(int i = 1;i <= n;sum[i] = sum[i - 1] ^ a[i],i++)
			if(s[i] == '1')ans ^= a[i];
		scanf("%d",&q);
		while(q--)
		{
			scanf("%d",&op);
			if(op == 2)
			{
				scanf("%d",&x);
				if(x == 1)printf("%d ",ans);
				else printf("%d ",sum[n] ^ ans);
			}
			else 
				scanf("%d %d",&l,&r),
				ans ^= sum[r] ^ sum[l - 1];
		}
		puts("");
	}
}
```

---

## 作者：LCat90 (赞：4)

一种麻烦的方法是直接建线段树然后打标记。

显然有巧妙的做法，考虑从异或的性质出发。

首先对于取反操作，被选的数字变为不选，没选的数字变为选了。可以通过直接异或上区间异或和得到。因为一个数异或自己奇数次得到的答案是自己，偶数次是 $0$，恰好满足。

然后是求整个序列异或和。如果是求标号 $1$ 的就直接输出结果，否则输出区间内其它元素的异或和。类似地可以通过所有元素异或和异或上当前标号为 $1$ 的异或和。

复杂度为线性。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, t, q, a[N], pre[N], ans;
char c[N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while(t--) {
		cin >> n; 
		for(int i = 1;i <= n; ++i) {
			cin >> a[i];
			pre[i] = pre[i - 1] ^ a[i];
		}
		cin >> c; ans = 0;
		for(int i = 1;i <= n; ++i) if(c[i - 1] == '1') ans ^= a[i]; int sb = pre[n]; 
		cin >> q;
		while(q--) {
			int op, l, r;
			cin >> op >> l;
			if(op == 2) {
				if(l == 1) cout << ans << " ";
				else cout << (sb ^ ans) << " "; 
			}
			else {
				cin >> r;
				ans ^= (pre[r] ^ pre[l - 1]);
			} 
		} cout << "\n";
	}
	return 0;
}
```

---

## 作者：One_JuRuo (赞：3)

## 思路

一眼顶真，这不就是线段树吗？还挺板的，然后速打了一个线段树。

就是用两个变量分别存这个区间的两个异或值，修改就是交换这两个变量的值，询问都是询问整体的，应该很好写，就不细讲了。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{long long l,r,xor0,xor1,tag;}t[400005];
long long T,n,v[100005],m,op,a,b;
char s[100005];
inline void pushup(long long p){t[p].xor0=t[p<<1].xor0^t[p<<1|1].xor0,t[p].xor1=t[p<<1].xor1^t[p<<1|1].xor1;}
inline void pushdown(long long p){swap(t[p<<1].xor0,t[p<<1].xor1),t[p<<1].tag^=1,swap(t[p<<1|1].xor0,t[p<<1|1].xor1),t[p<<1|1].tag^=1,t[p].tag=0;}
void build(long long p,long long l,long long r)
{
	t[p].l=l,t[p].r=r,t[p].tag=0;
	if(l==r)
	{
		if(s[l]=='0') t[p].xor0=v[l],t[p].xor1=0;
		else t[p].xor0=0,t[p].xor1=v[l];
		return;
	}
	long long mid=l+r>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	pushup(p);
}
void update(long long p,long long l,long long r)
{
	if(t[p].l>=l&&t[p].r<=r){swap(t[p].xor0,t[p].xor1),t[p].tag^=1;return;}
	if(t[p].tag) pushdown(p);
	long long mid=t[p].l+t[p].r>>1;
	if(mid>=l) update(p<<1,l,r);
	if(mid<r) update(p<<1|1,l,r);
	pushup(p);
}
long long ask(long long p,long long l,long long r,long long k)
{
	if(t[p].l>=l&&t[p].r<=r) return (k)?t[p].xor1:t[p].xor0;
	if(t[p].tag) pushdown(p);
	long long mid=t[p].l+t[p].r>>1,ans=0;
	if(mid>=l) ans=ask(p<<1,l,r,k);
	if(mid<r) ans=ans^ask(p<<1|1,l,r,k);
	return ans;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;++i) scanf("%lld",&v[i]);
		scanf("%s%lld",s+1,&m),build(1,1,n);
		while(m--)
		{
			scanf("%lld%lld",&op,&a);
			if(op==1) scanf("%lld",&b),update(1,a,b);
			else printf("%lld ",ask(1,1,n,a));
		}
		puts("");
	}
} 
```

## 另一种做法

一起打 CF 的另一个老哥没有用线段树，而是用了异或的性质。

因为一个数异或自己一定是 $0$，那么区间修改，就等于是异或这个区间原来有的数，把原来有的通过异或除掉，再异或原来没有的数，让他出现。

假设用两个变量 $s0$ 和 $s1$ 分别存整个区间的两个异或和，那么修改一个区间就是把这个区间的异或和异或给 $s0$ 和 $s1$。

可以提前预处理出异或前缀和，然后按照要求操作就行了。

因为没写这个方法，我又太懒了，所以这里就不放代码了。

---

## 作者：luan341502 (赞：2)

用异或的性质即可。

分别记录数字 $0$ 和 $1$ 对应的总的异或和。修改操作将两个异或和分别与区间异或和异或就能得到翻转后的答案，查询操作直接输出对应答案即可。

用异或前缀和优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,a[100005];
int q;
int ans[2],c[100005];
char str[100005];
int main(){
	scanf("%d",&t);
	while(t--){
		for(int i=1;i<=n;i++){
			c[i]=0;
		}
		ans[0]=ans[1]=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",a+i);
		}
		cin>>str+1;
		for(int i=1;i<=n;i++){
			ans[str[i]-'0']^=a[i];
			c[i]=c[i-1]^a[i];
		}
		scanf("%d",&q);
		while(q--){
			int op;
			scanf("%d",&op);
			if(op&1){
				int l,r;
				scanf("%d%d",&l,&r);
				ans[0]^=c[r]^c[l-1];
				ans[1]^=c[r]^c[l-1];
			}else{
				int x;
				scanf("%d",&x);
				printf("%d ",ans[x]);
			}
		}
		puts("");
	}
	return 0;
} 
```


---

## 作者：qwq___qaq (赞：1)

分块板子，记录一下 $0$ 和 $1$ 的异或，散块修改直接交换 $0,1$，整块打标记。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e5+5;
int T,n,q,opt,l,r,a[N],L[N],R[N],block[N],len,tot,sum[N][2],ans[2];
bool op[N],flg[N];
string s;
inline void build(int n){
	len=sqrt(n),tot=(n+len-1)/len;
	for(int i=1;i<=tot;++i){
		L[i]=(i-1)*len+1,R[i]=min(i*len,n);
		sum[i][0]=sum[i][1]=flg[i]=0;
		for(int j=L[i];j<=R[i];++j)
			block[j]=i,sum[i][op[j]]^=a[j];
	}
}
inline void update(int l,int r){
	int x=block[l],y=block[r];
	if(x==y){
		for(int i=l;i<=r;++i)
			ans[op[i]^flg[x]]^=a[i],op[i]^=1,ans[op[i]^flg[x]]^=a[i];
	} else{
		for(int i=l;i<=R[x];++i)
			ans[op[i]^flg[x]]^=a[i],op[i]^=1,ans[op[i]^flg[x]]^=a[i];
		for(int i=L[y];i<=r;++i)
			ans[op[i]^flg[x]]^=a[i],op[i]^=1,ans[op[i]^flg[x]]^=a[i];
		for(int i=x+1;i<y;++i)
			flg[i]^=1,ans[0]^=(sum[i][0]^sum[i][1]),ans[1]^=(sum[i][0]^sum[i][1]),swap(sum[i][0],sum[i][1]);
	}
}
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
    	cin>>n;
    	for(int i=1;i<=n;++i)
    		cin>>a[i];
    	cin>>s;
    	ans[0]=ans[1]=0;
    	for(int i=1;i<=n;++i)
    		op[i]=(s[i-1]=='1'),ans[op[i]]^=a[i];
    	build(n);
    	cin>>q;
    	while(q--){
    		cin>>opt>>l;
    		if(opt==1)
    			cin>>r,update(l,r);
    		else
				cout<<ans[l]<<' ';
		}
		cout<<endl;
	}
    return 0;
}
```

---

## 作者：ScottSuperb (赞：0)

## 解法分析
看到区间异或和问题，很容易就联想到使用异或前缀和解决。首先回顾一下异或的两条基本性质：$x \oplus  x = 0, x \oplus  0 = x$，因此当 $s$ 某段取反时，相对应的就是 $a$ 中异或上了这段的异或和。那么只需要在读入时记录标志为 $0$ 的数的异或和，查询时若 $g=1$ 直接异或上整个数组的异或和即可。
## 代码
read/write 函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

char getc() {
  char c = getchar();
  while (c ^ '0' && c ^ '1') c = getchar();
  return c;
}

const int N = 1e5 + 5;
int a[N], xs[N];

int main() {
  int T = read();
  while (T--) {
    int n = read(), ans = 0;
    for (int i = 1; i <= n; ++i) a[i] = read(), xs[i] = a[i] ^ xs[i - 1];
    for (int i = 1; i <= n; ++i)
      if (getc() == '0') ans ^= a[i];
    int q = read(), op, l, r;
    while (q--) {
      op = read();
      if (op & 1)
        l = read(), r = read(), ans ^= xs[r] ^ xs[l - 1];
      else
        write(ans ^ xs[n] * read());
    }
    pc('\n');
  }
  fls();
  return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

## Problem
给定一个长度为 $n$ 的数组和一个长度为 $n$ 的二进制串 $s$，现有两个操作：
1. `1 l r`，表示将 $l \le i \le r$ 的所有 $s_i$ 取反（$0$ 变 $1$，$1$ 变 $0$）；
2. `2 g`$(g\in {0,1})$，表示将所有 $s_i=g$ 的 $a_i$ 求异或和；
$1\le n\le 10^5,1\le t\le 10^4$.
## Solve
脑瘫题，不知道为啥这道题要放在 E。

首先，我们可以计算出操作二中一个串为 $g=0$ 和 $g=1$ 的初始异或和。分别记为 $g_0,g_1$。

对于操作一，无非是将 $a_i$ 从 $g_0$（ 或 $g_1$）里删除，将其加入 $g_1$（或 $g_0$）中，这个操作其实就是将 $g_0,g_1$ 同时异或 $l\sim r$ 的异或和。原理是异或的逆运算还是异或。

维护一个前缀异或和即可。但是我打的是线段树（因为一时脑抽没有想到前缀和

时间复杂度 $O(Tq\log n)$，前缀和可以做到 $O(Tq)$。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007
#define ls p<<1
#define rs p<<1|1

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 1e5 + 10;

struct Node {
  int l, r, val;
} t[N << 2];

int n, T, q, a[N], p0, p1;

string s;

void pushup(int p) {
  t[p].val = t[ls].val ^ t[rs].val;
}

void build(int p, int l, int r) {
  t[p].l = l, t[p].r = r;
  if(l == r) {
    t[p].val = a[l];
    return ;
  }
  int mid = (l + r) >> 1;
  build(ls, l, mid);
  build(rs, mid + 1, r);
  pushup(p);
}

int ask(int p, int l, int r) {
  if(l <= t[p].l && t[p].r <= r) {
    return t[p].val;
  }
  int mid = (t[p].l + t[p].r) >> 1, ans = 0;
  if(l <= mid) ans ^= ask(ls, l, r);
  if(r > mid) ans ^= ask(rs, l, r);
  return ans;
}

void solve() {
  p0 = p1 = 0;
  read(n);
  For(i,1,n) read(a[i]);
  cin >> s;
  s = " " + s;
  For(i,1,n) {
    if(s[i] == '0') p0 ^= a[i];
    else p1 ^= a[i];
  }
  build(1, 1, n);
  read(q);
  while(q--) {
    int op; read(op);
    if(op == 1) {
      int l, r, p;
      read(l, r);
      p = ask(1, l, r);
      p0 ^= p, p1 ^= p; 
    } else {
      int g; read(g);
      if(g == 0) cout << p0 << ' ';
      else cout << p1 << ' ';
    }
  }
  cout << '\n';
}

signed main() {
  read(T);
  while(T--) {
    solve();
  }
  return 0;
}
```

---

