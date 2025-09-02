# [ARC160A] Reverse and Count

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc160/tasks/arc160_a

$ (1,\ 2,\ \dots,\ N) $ の順列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ が与えられます。  
 $ 1\ \leq\ L\ \leq\ R\ \leq\ N $ を満たす整数の組 $ (L,\ R) $ に対して、$ A $ の $ L $ 番目から $ R $ 番目までの要素を反転してできる順列を $ f(L,\ R) $ とします。  
 ここで、「$ A $ の $ L $ 番目から $ R $ 番目までの要素を反転する」とは、$ A_L,\ A_{L+1},\ \dots,\ A_{R-1},\ A_R $ を $ A_R,\ A_{R-1},\ \dots,\ A_{L+1},\ A_{L} $ に同時に置き換えることを言います。

$ (L,\ R) $ を $ 1\ \leq\ L\ \leq\ R\ \leq\ N $ を満たすように選ぶ方法は $ \frac{N(N\ +\ 1)}{2} $ 通りあります。  
 このような $ (L,\ R) $ の組全てに対して順列 $ f(L,\ R) $ をすべて列挙して辞書順にソートしたときに、先頭から $ K $ 番目にある順列を求めてください。

  数列の辞書順とは？数列 $ S\ =\ (S_1,S_2,\ldots,S_{|S|}) $ が数列 $ T\ =\ (T_1,T_2,\ldots,T_{|T|}) $ より**辞書順で小さい**とは、下記の 1. と 2. のどちらかが成り立つことを言います。 ここで、$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します。

1. $ |S|\ \lt\ |T| $ かつ $ (S_1,S_2,\ldots,S_{|S|})\ =\ (T_1,T_2,\ldots,T_{|S|}) $。
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して、下記の $ 2 $ つがともに成り立つ。 
  - $ (S_1,S_2,\ldots,S_{i-1})\ =\ (T_1,T_2,\ldots,T_{i-1}) $
  - $ S_i $ が $ T_i $ より（数として）小さい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 7000 $
- $ 1\ \leq\ K\ \leq\ \frac{N(N\ +\ 1)}{2} $
- $ A $ は $ (1,\ 2,\ \dots,\ N) $ の順列
 
### Sample Explanation 1

$ 1\ \leq\ L\ \leq\ R\ \leq\ N $ を満たす $ (L,\ R) $ の組全てに対して順列 $ f(L,\ R) $ をすべて列挙すると次のようになります。 - $ f(1,\ 1)\ =\ (1,\ 3,\ 2) $ - $ f(1,\ 2)\ =\ (3,\ 1,\ 2) $ - $ f(1,\ 3)\ =\ (2,\ 3,\ 1) $ - $ f(2,\ 2)\ =\ (1,\ 3,\ 2) $ - $ f(2,\ 3)\ =\ (1,\ 2,\ 3) $ - $ f(3,\ 3)\ =\ (1,\ 3,\ 2) $ これらを辞書順にソートしたときに $ 5 $ 番目に来る順列は $ f(1,\ 3)\ =\ (2,\ 3,\ 1) $ です。よってこれを出力します。

### Sample Explanation 2

答えは $ f(1,\ 5) $ です。

## 样例 #1

### 输入

```
3 5
1 3 2```

### 输出

```
2 3 1```

## 样例 #2

### 输入

```
5 15
1 2 3 4 5```

### 输出

```
5 4 3 2 1```

## 样例 #3

### 输入

```
10 37
9 2 1 3 8 7 10 4 5 6```

### 输出

```
9 2 1 6 5 4 10 7 8 3```

# 题解

## 作者：SqrtSecond (赞：8)

一句话题意：定义 $f(l,r)$ 是将排列 $\{a_i\}$ 的区间 $[l,r]$ 翻转后的序列，求所有的 $f(l,r)(1\le l\le r\le n)$ 中字典序第 $k$ 小的序列。 $(n\le 7000)$

由于它是按照字典序排序的，所以我们先来看一下如何比较 $f(l_1,r_1)$ 与 $f(l_2,r_2)$ 的大小。

首先如果 $l_1=l_2$ 就直接比较 $a_{r_1}$ 与 $a_{r_2}$ 即可，由于 $\{a_i\}$ 是一个排列，其右端点的值一定不同。

否则不妨设 $l_1<l_2$，此时只需要比较第一个不同的位置的值，也就是 $a_{r_1}$ 与 $a_{l_1}$ 即可。有一种例外是 $l_1=r_1$，这种情况下相当于 $f(l_1,r_1)$ 对原数组没有产生影响，这种情况下则要比较 $a_{l_2}$ 与 $a_{r_2}$ 的大小。

于是，我们就有一种 $O(1)$ 比较两个 $f(l,r)$ 的方法。

如果直接把每个区间求出来并排序，时间复杂度是 $O(n^2\log n)$ ，过不了。

但是，我们发现只需要求出排序后第 $k$ 小的值，恰好在[P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)中提到了一种能够在 $O(n)$ 内求出序列第 $k$ 小的方法。于是，我们只需要调用 STL 中的 `nth_element` 函数即可。

顺便提一下 `nth_element` 的用法。用 `nth_element` 函数求序列第 `k` 小的方法是 `nth_element(a+l,a+k,a+r+1)` 。调用完以后，区间 $[1,k)$ 中所有数 $\le a_k$，区间 $(k,n]$ 中所有数 $\ge a_k$ 。该函数对重载运算符后的结构体同样适用。

时间复杂度 $O(n^2)$ 。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[7010],cnt;
struct node{int l,r;}b[25000000],ans;
bool operator <(node b,node c)
{
	if(b.l==c.l)return a[b.r]<a[c.r];
	if((b.l<c.l&&b.l!=b.r)||c.l==c.r)return a[b.r]<a[b.l];
	return a[c.l]<a[c.r];
}//判断同一数组翻转不同区间后字典序的大小关系
signed main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		for(int j=i;j<=n;++j)b[++cnt]={i,j};
	}
	nth_element(b+1,b+k,b+cnt+1);//求出第k小
	reverse(a+b[k].l,a+b[k].r+1);
	for(int i=1;i<=n;++i)printf("%d ",a[i]);
	return 0;
}
```


---

## 作者：Hypercube (赞：7)

这场 ABC 都很典。

首先不难发现除了 $l=r$ 的情况以外，所有翻转方案两两不同。

一个比较自然的想法是把 $l=r$ 特判一下，即计算一下有多少序列比原序列字典序小，设为 $cnt$ 个。对于 $k \in [cnt+1,cnt+n]$ 的询问直接特判输出原序列即可。同时为了使剩下的方案连续，对于 $k > cnt+n$ 的询问直接减去 $n$ 即可。

然后问题就转化为了只能翻转 $l \neq r$ 的区间，求字典序第 $k$ 小的序列。

我们从左到右考虑每一位是否作为翻转区间的左端点。

假设当前考虑的是第 $i$ 位，且保证排列的前 $i-1$ 位不变，那么实际上只有两种状态（翻转区间是否以第 $i$ 位为左端点）。如果以第 $i$ 位为左端点，那么相当于从后 $n-i$ 个数中取一个换到第 $i$ 个位置上。而由于后面的数是两两不同的，所以任何一种翻转方式的字典序都是可以比较翻转后的第 $i$ 位判断的（当然这其实也分成两种情况，一种是换来的数比 $p_i$ 小，另一种是换来的数比 $p_i$ 大）。而如果不以 $i$ 为左端点，那就相当于前 $i$ 为都固定不变，那么就直接到下一位再考虑即可。

具体怎么实现呢？假设说 $i$ 后面比 $p_i$ 小的数有 $x$ 个，比 $i$ 大的数有 $y$ 个，要查询**前 $i-1$ 个数不翻转**的所有方案中的第 $k$ 个。如果说 $k \le x$ 或者 $k \ge x+ \frac{(n-i)(n-i-1)}{2}+1$ 的都可以直接输出答案了。（考虑三种情况恰好对应字典序上三段连续的区间）。否则将 $k$ 减去 $x$，下一位继续考虑即可。

实现细节在代码里。精细实现可以做到 $O(n \log n)$。

```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,k,cnt,p[200005],p1[200005],p2[200005];
struct pri {int num,p;};
bool operator < (pri a,pri b) {return a.num<b.num;}
priority_queue <pri> q;
struct BIT {
    int c[200005];
    int lowbit(int x) {return x&(-x);}
    void add(int x) {for(; x<=n; x+=lowbit(x)) c[x]++;}
    int Query(int x) {if(!x) return 0;int ans=0;for(; x; x-=lowbit(x)) ans+=c[x];return ans;}
    int query(int l,int r) {return Query(r)-Query(l-1);}
} bit;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0); 
    cin>>n>>k;
    for(int i=1; i<=n; i++) cin>>p[i];
    for(int i=n; i>=1; i--) {
        p1[i]=bit.query(1,p[i]);
        p2[i]=bit.query(p[i],n);
        bit.add(p[i]);
        cnt+=p1[i];
    }
    if(k>cnt&&k<=cnt+n) {
        for(int i=1; i<=n; i++) cout<<p[i]<<' ';
        cout<<'\n';
        return 0;
    }
    if(k>cnt+n) k-=n;
    for(int i=1; i<=n; i++) {
        int num1=p1[i],num2=p2[i],num=(n-i)*(n-i-1)/2;
        if(k<=num1) {
            for(int j=i+1; j<=n; j++) q.push((pri) {
                -p[j],j
            });
            for(int j=1; j<k; j++) q.pop();
            for(int j=1; j<i; j++) cout<<p[j]<<' ';
            for(int j=q.top().p; j>=i; j--) cout<<p[j]<<' ';
            for(int j=q.top().p+1; j<=n; j++) cout<<p[j]<<' ';
            cout<<'\n';
            return 0;
        } else if(k>num1+num) {
            k-=(num1+num);
            k=(num2-k+1);
            for(int j=i+1; j<=n; j++) q.push((pri) {
                p[j],j
            });
            for(int j=1; j<k; j++) q.pop();
            for(int j=1; j<i; j++) cout<<p[j]<<' ';
            for(int j=q.top().p; j>=i; j--) cout<<p[j]<<' ';
            for(int j=q.top().p+1; j<=n; j++) cout<<p[j]<<' ';
            cout<<'\n';
            return 0;
        } else {
            k-=num1;
        }
    }
    return 0;
}

```


---

## 作者：Pengzt (赞：4)

[ARC160A](https://www.luogu.com.cn/problem/AT_arc160_a)

最暴力的想法是直接将所有能表示出的排列排序，时间复杂度 $\mathcal{O}(n^2\log n)$，显然无法通过。

考虑将所有能表示出的排列按字典序依次枚举。

令 $i$ 之前的排列不变。发现当 $a_i \neq i$ 时，排列 $\dots i \dots$ 只会有 $1$ 的贡献。当 $a_i = i$ 时，会有 $\frac{(n - i)\times(n - i - 1)}{2} + n$ 种排列，如果这个值与之前的值加起来 $> k$，就令 $i = i + 1$ 继续做，如果 $= k$ 就直接输出。

还有一种做法就是直接用 nth_element。

时间复杂度：$\mathcal{O}(n ^ 2)$

代码就不放了。

---

## 作者：六楼溜刘 (赞：2)

## 题意
- 给你一个排列 $A=(A_1,A_2,\dots,A_N)$，定义 $f(i,j)$ 为排列 $A$ 中区间 $[i,j]$ 翻转后构成的新排列，其中 $i \le j$。
- 容易发现共有 $\frac{n(n+1)}{2}$ 个不同的 $f$，求出所有 $f$ 中字典序第 $N$ 小的。
- $1 \le N \le 7000,1 \le K \le \frac{n(n+1)}{2}$，$A$ 是一个排列（即 $\forall 1 \le i\le N,1 \le A_i \le N,\forall 1 \le i <j\le N,A_i \ne A_j$）

## 题解

这是一个比较另类的做法。

首先，由于 $A$ 是一个排列，它没有重复数字，所以我们只要知道 $i,j,i',j'$ 就可以比较 $f(i,j)$ 和 $f(i',j')$的字典序了。具体来说，分四种情况讨论：

- $i=j$ 且 $i'=j'$，两序列字典序相等，随便怎么处理。
- $i=i'$，此时若 $A_j<A_{j'}$ 则 $f(i,j)<f(i',j')$，反之亦然。
- $i<i'$ 或 $i'=j'$ 且 $i\ne j$，此时若 $A_j<A_i$ 则 $f(i,j)<f(i',j')$，反之亦然。
- $i>i'$ 或 $i=j$ 且 $i'\ne j'$，此时若 $A_{i'}<A_{j'}$ 则 $f(i,j)<f(i',j')$，反之亦然。

这个结论很显然，因为字典序的大小关系就是两序列第一个不同元素的大小关系，我们只用比较第一个不同元素即可，注意判断相等情况。

接下来我们把这个问题转化为了求二元组 $(i,j)$ 构成的序列第 $K$ 小，注意 $(i,j)$ 构成的二元组的数量为 $\frac{n(n+1)}{2}$，但这道题 $N$ 最大是 $7000$，所以还要求这一步的时间复杂度为 $O(n)$。

这种时候为什么不问问神奇的 STL 库呢？其实 STL 库中正好有一个函数可以解决我们的需求，它就是 `nth_element`。这个函数要传三个参数，举个例子，`nth_element(s+1,s+k,s+n+1)` 会使 $\forall 1 \le i < k ,s_i\le s_k$ 同时 $\forall k<i<n,s_i \ge s_k$。此时 $s_k$ 就是序列第 $k$ 小，而通常这个函数的复杂度是 $O(n)$ 的，只有在 $n$ 比较小的时候可能被卡到 $O(n^2)$，但能被卡到 $O(n^2)$ 的时候 $O(n^2)$ 也能过所以完全没有影响。

复杂度 $O(N^2)$，完全能过。

### code
```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=7005,inf=0x3f3f3f3f;
int n,k,a[N];
struct Node{
	int l,r;
	bool operator <(const Node &pp)const{
		if(l==r&&pp.l==pp.r){
			return l<pp.l;//这里随便怎么判都行，我为了方便调试这样写
		}else if(l==pp.l){
			return a[r]<a[pp.r];
		}else if((l!=r)&&(l<pp.l||pp.l==pp.r)){
			return a[r]<a[l];
		}else{
			return a[pp.l]<a[pp.r];
		}
	}
};
Node s[N*N];//注意开平方空间
int cnt;
void print(Node q){
	forup(i,1,q.l-1){
		printf("%d ",a[i]);
	}
	fordown(i,q.r,q.l){
		printf("%d ",a[i]);
	}
	forup(i,q.r+1,n){
		printf("%d ",a[i]);
	}
}
signed main(){
	n=read();k=read();
	forup(i,1,n){
		a[i]=read();
	}
	forup(i,1,n){
		forup(j,i,n){
			s[++cnt]=Node{i,j};
		}
	}
	nth_element(s+1,s+k,s+cnt+1);
	print(s[k]);
}
```


---

## 作者：Mars_Dingdang (赞：0)

在后续过程中很容易发现，这道题目麻烦的地方在于可以 $L=R$。因此我们预处理出 $L=R$ 的 $n$ 个操作得到的序列的排名，特判 $k$ 在这一范围内时直接输出原序列，否则当 $k$ 大于其时令 $k\leftarrow k-n$。

然后我们去掉了所有的 $L=R$ 的序列。考虑对于当前的 $l$，记 $l$ 右边比 $a_l$ 小的数的个数为 $f_l$，则有 $f_l$ 种操作通过改变首个数使得序列变小，有 $n-l-f_l$ 种操作通过改变首个数使得序列变大，因此如果 $k$ 落在这个范围内，直接 reverse 并输出。

否则说明 $a_l$ 不会改变，输出 $a_l$，然后在 $[l+1,n]$ 范围内解决问题即可。相应地，$k$ 需要减去 $f_l$。

基于对各种细节地处理，可以在 $O(n\log n)$ 或者 $O(n^2)$ 的复杂度通过本题。下列代码是平方的复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 7005;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, K, a[maxn], pos[maxn];
int f[maxn];
inline void solve(int l, int k) {
	if(l > n) exit(0);
	if(k <= f[l]) {
		int p = 0;
		vector <int> v; v.clear();
		rep(i, l + 1, n) if(a[i] < a[l]) {
			v.push_back(a[i]);
		}
		sort(v.begin(), v.end());
		p = pos[v[k - 1]];
		reverse(a + l, a + p + 1);
		rep(i, l, n) write(a[i]), putchar(' ');
		exit(0);
	}
	else if(k > f[l] + (n - l) * (n - l - 1) / 2) {
		k -= f[l] + (n - l) * (n - l - 1) / 2;
		vector <int> v; v.clear();
		rep(i, l + 1, n) if(a[i] > a[l]) {
			v.push_back(a[i]);
		}
		sort(v.begin(), v.end());
		int p = pos[v[k - 1]];
		reverse(a + l, a + p + 1);
		rep(i, l, n) write(a[i]), putchar(' ');
		exit(0);
	}
	write(a[l]), putchar(' ');
	solve(l + 1, k - f[l]);
}
int main () {
	read(n); read(K);
	rep(i, 1, n) read(a[i]), pos[a[i]] = i;
	int cnt = 0;
	rep(L, 1, n)
		rep(R, L + 1, n) {
			if(a[R] < a[L]) cnt ++;
		}
	if(K >= cnt + 1 && K <= cnt + n) {
		rep(i, 1, n) write(a[i]), putchar(' ');
		return 0;
	}
	else if(K > cnt + n) K -= n;
	
	rep(i, 1, n) {
		rep(j, i + 1, n) f[i] += (a[j] < a[i]);
	}
	solve(1, K);
	
	return 0;
}
```

---

## 作者：luohanzhao (赞：0)

[题目传送门：[ARC160A] Reverse and Count。](https://www.luogu.com.cn/problem/AT_arc160_a)

简述题意：给定一个长度为 $N$ 的排列  $A$ ，你可以选择一个区间并翻转它，求出你所有得到的新排列中**字典序**第 $K$ 小的。为方便描述，我们令翻转区间为 $[l, r], (1 \leq l \leq r \leq n)$。

我们知道，字典序是从头到尾依次考虑的，现在考虑到第 $i$ 位，能改变字典序的只有原序列第 $i$ 位之后的数，因为若是 $l \leq i = r$，那么第 $i$ 位上的数一定会影响到前面的字典序。

考虑前 $i - 1$ 位不进行更改，那么第 $i$ 位有三种情况：

- $l = i, r = i$

- $l > i$

- $l = i, r > i$

对于第一种情况，我们发现区间翻转了，但是，没有完全翻转。并且，$i$ 可以等于任意值，不予考虑。

对于第二种情况，新序列为 $B = \{A_1, A_2, \dots,A_i, \dots, A_{l - 1}, A_r, A_{r - 1}, \dots, A_{l + 1}, A_l, A_{r + 1}, \dots, A_{n-1}, A_n\}$。

就等价于前 $i$ 位都不更改，属于 $i + 1$ 的考虑范围。总共会有 $\frac{(n - i) \times (n - i + 1)}{2} + i$ 种情况。

对于第三种情况，新序列为 $B = \{A_1, A_2, \dots, A_{l - 1}, A_r, A_{r - 1}, \dots, A_{l + 1}, A_l, A_{r + 1}, \dots, A_{n-1}, A_n\}$。

我们发现字典序由第 $r$ 位决定，不同的 $r$ 只会产生一种不同的结果，$A_r$ 越小字典序越小。

---

有了以上的结论，我们考虑遍历 $i$，$j$，翻转区间 $[l, r]$ 满足 $l = i$ 且 $A[r] = j$ 。

所以翻转后的序列中，$j$ 越小序列的字典序就会越小。记 $cnt$ 为现在有多少序列的字典序已经统计过了，当 $cnt = k$ 时得到答案。

这样做的话正确性可以保证，时间复杂度为 $O(N ^ 2)$，无压力通过。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, a[7005], to[7005], l = 1, r, cnt;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i(1); i <= n; i++)scanf("%d",&a[i]), to[a[i]] = i;
	for(int i(1); i <= n && !r; i++)for(int j(1); j <= n; j++)
	{
		if(to[j] < i)continue;
		if(a[i] == j)//情况2
		{
			if(cnt + (n - i) * (n - i + 1) / 2 + i >= k)break;//判断k是否在l>i的情况中
			cnt += (n - i) * (n - i + 1) / 2 + i;
		}
		else if(++cnt >= k){l = i, r = to[j];break;}//情况3
	}
	reverse(a + l, a + 1 + r);
	for(int i(1); i <= n; i++)cout << a[i] << " ";
	return 0;
}
```

---

## 作者：快乐的大童 (赞：0)

[AT 传送门](https://atcoder.jp/contests/arc160/tasks/arc160_a)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_arc160_a)

### 题目大意
设 $f_{i,j}$ 为将排列 $a$ 的子区间 $[i,j]$ 翻转后形成的排列，对于每个 $1\le i\le j\le n$，求字典序第 $k$ 小的 $f_{i,j}$。

$n\le 7000$。
### 题解
由于比较的是字典序，所以考虑从左到右考虑每一位应该是什么。

对于第 $i$ 个位置，考虑计算这一位填 $j$ 的方案数（之前已经考虑完全）：

- $j$ 的位置在 $i$ 之前：方案数 $0$。
- $j$ 的位置在 $i$ 之后：方案数 $1$（将这一位和 $i$ 组成的区间翻转）。
- $j$ 的位置在 $i$ 上：方案数 $\dfrac{(n-i+1)(n-i)}{2}+i$（$[1,1],[2,2],\cdots,[i,i]$ 共 $i$ 种方案，在区间 $[i+1,n]$ 内选择一个子区间共 $\dfrac{(n-i+1)(n-i)}{2}$ 方案。显然这些选择方式都能使 $j$ 原封不动）

我们用 $k$ 来减去第 $i$ 位填 $j$ 的方案数，如果 $k$ 将要减为 $0$ 或负数，则说明第 $i$ 位必须要取 $j$。

这种情况下，若 $j$ 的方案数只有 $1$，那么答案肯定是它。

否则直接考虑下一个位置该填什么。

如果枚举完所有位置也没拿到决策，直接输出原序列即可（因为这表明每一位都原封不动）。
### 代码
```cpp
//去掉了火车头，留下了代码部分
//rd()是快读函数，write(,' ')是快输函数+输出空格
#define rep(a,b,c) for(int a=b;a<=c;a++)
const int maxn=7e3+5,maxm=2e5+5;
int n,k,a[maxn],pos[maxn];
void solve_the_problem(){
	n=rd(),k=rd();rep(i,1,n)a[i]=rd(),pos[a[i]]=i;
	int gx,sign;
	rep(j,1,n){
		rep(i,1,n){
			if(pos[i]<j) continue;
			if(pos[i]==j) gx=(n-j+1)*(n-j)/2+j;//gx 即为方案数 
			else gx=1;
			if(k-gx<=0){
				sign=i;
				break;
			}
			k-=gx;
		}
		if(pos[sign]!=j){
			reverse(a+j,a+pos[sign]+1);
			rep(i,1,n)write(a[i],' ');
			return;
		}
	}
	rep(i,1,n)write(a[i],' ');
}
```


---

