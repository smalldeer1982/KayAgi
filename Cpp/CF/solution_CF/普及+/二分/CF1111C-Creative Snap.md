# Creative Snap

## 题目描述

灭霸要摧毁复仇者们的基地！  

我们可以将复仇者的基地看成一个序列，每个位置都有可能有多个复仇者；但是每个复仇者只能占据一个位置。  
他们基地的长度刚好是$2$的整数幂，灭霸想要用最少的能量摧毁它们。他在摧毁过程中，可以选择：  
- 如果这段基地长度$\ge 2$，他可以将其分为相等长度的两半。  
- 烧掉这段基地。如果这段基地中没有复仇者，他需要消耗$A$的能量；如果有，则需要消耗$B*x*l$的能量。其中$l$是这段基地长度，$x$是这段中的复仇者数量。  

输出一个整数，表示他摧毁全部基地需要的最少能量。  
接下来一行$k$个整数，$a_i$表示第$i$个复仇者所在的位置

## 说明/提示

### 样例解释  
对于样例1，直接烧区间$[1,4]$需要能量为$4*2*2=16$。  
但是，如果将其分为$4$段，分别烧掉，所需能量只有$2+1+2+1=6$。  
可以证明没有更优的方案，所以输出`6`。 
对于全部数据：  
$1\le n \le 30$  
$1\le k \le 10^5$  
$1\le A,B \le 10^4$  
$1\le a_i \le 2^n$

## 样例 #1

### 输入

```
2 2 1 2
1 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 2 1 2
1 7
```

### 输出

```
8
```

# 题解

## 作者：花里心爱 (赞：4)

~~线段树板子题（雾）~~

理解题意，发现我们要维护的是一个长度为$2^n$的区间。于是我们想到用线段树来维护。

线段树的每个节点维护区间内的人数和价值，然后按照题意pushup即可。注意如果一个区间内的人数为0，这个区间的价值为A。

由于$2^n$很大，所以我们要动态开节点。建树的时候将所有人依次插入线段树中。最后答案即为根节点的价值。

~~然后就没有然后了qwq~~

时间复杂度$O(klog2^n) = O(kn)$。

下面放代码：
```cpp
#include <cstdio>
#include <algorithm>
#define int long long
#define maxn 100005

int n, k, A, B;
int a, rt = 1;
int c[maxn<<5], d[maxn<<5], cnt = 1; // c为区间人数，d为价值
int ls[maxn<<5], rs[maxn<<5];
// 注意动态开点线段树空间要开 log(区间长度) 倍（像我这种比较懒的就直接 << 5 了qwq）

void pushup(int cur, int len) {
    c[cur] = c[ls[cur]] + c[rs[cur]];
    d[cur] = std::min(B*c[cur]*len, d[ls[cur]] + d[rs[cur]]);
    // 更新d的过程对应2种方式：将cur看作1个区间的价值，拆分成2个区间的价值和
}

void ins(int& cur, int l, int r, int pos) {
    if(!cur) cur = ++cnt; // 动态开点
    if(l == r) {
        ++c[cur];
        d[cur] = B*c[cur];
        return;
    }
    int mid = (l+r)>>1;
    if(mid >= pos) ins(ls[cur], l, mid, pos);
    else ins(rs[cur], mid+1, r, pos);
    pushup(cur, r-l+1);
}

signed main() {
    scanf("%I64d%I64d%I64d%I64d", &n, &k, &A, &B);
    d[0] = A; // 空区间的价值为A（由于空区间一定没被访问，所以直接修改 d[0] 即可）
    while(k--) {
        scanf("%I64d", &a);
        ins(rt, 1, 1<<n, a); // 依次插入
    }
    printf("%I64d", d[1]);
    return 0;
}
```

---

## 作者：GKxx (赞：3)

水题

按照题意模拟即可

注意一个剪枝：如果当前处理的区间里一个avenger都没有，就直接返回$A$。

$2^{30}$差不多有十亿，但是$k$只有$10^5$，说明上面这种情况的发生频率还挺高的。因此能过

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkmax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

typedef long long LL;
const int maxn = 1e5 + 207;
int a[maxn];
int n, K, A, B;

inline LL count(int l, int r) {
    int pr = std::upper_bound(a + 1, a + K + 1, r) - a;
    --pr;
    int pl = std::upper_bound(a + 1, a + K + 1, l - 1) - a;
    --pl;
    return pr - pl;
}

LL solve(int l, int r) {
    int cnt = count(l, r);
    if (!cnt) return A;
    if (l == r) return B * cnt;
    int mid = (l + r) >> 1;
    return std::min(1ll * cnt * B * (r - l + 1), solve(l, mid) + solve(mid + 1, r));
}

int main() {
    read(n, K, A, B);
    for (int i = 1; i <= K; ++i) read(a[i]);
    std::sort(a + 1, a + K + 1);
    writeln(solve(1, 1 << n));
    return 0;
}
```

---

## 作者：Engulf (赞：3)

在题面中可以发现一个非常关键的点：

> 如果这段基地长度 $\ge 2$，他可以将其分为相等长度的两半。

很容易可以想到用 **分治** 来做。

令函数 `solve(l, r)` 表示摧毁区间 $[l, r]$ 需要的最小能量。

很好实现，但是值域比较大，达到了 $2 ^ {30}$，需要一点点剪枝。

1. 计算 $[l, r]$ 间的复仇者个数可以二分。
2. 如果没有复仇者，$[l, r]$ 的答案就是 $A$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 5;
int n, k, A, B;
int a[N];

int so1ve(int l, int r)
{
	int avengers = upper_bound(a + 1, a + k + 1, r) - lower_bound(a + 1, a + k + 1, l);
	if (!avengers) return A;
	if (l == r) return B * avengers;
	int mid = l + r >> 1;
	int split = so1ve(l, mid) + so1ve(mid + 1, r);
	return min(split, B * avengers * (r - l + 1));
}

signed main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	cin >> n >> k >> A >> B;
	for (int i = 1; i <= k; i ++ ) cin >> a[i];
	sort(a + 1, a + k + 1);
	cout << so1ve(1, 1 << n) << '\n';
	return 0;
}
```

---

## 作者：MornStar (赞：2)

#  CF1111C Creative Snap 题解
## 题目大意
灭霸要摧毁复仇者们的基地！ 

基地的长度刚好是 $2$ 的整数幂，他在摧毁过程中，可以选择：  
- 如果这段基地长度 $\ge 2$，他可以将其分为相等长度的两半。  
- 烧掉这段基地。如果这段基地中没有人，他需要消耗 $A$ 的能量；如果有，则需要消耗 $B*x*l$ 的能量。其中$l$是这段基地长度，$x$ 是这段中的复仇者数量。  

输出一个整数，表示他摧毁全部基地需要的最少能量。

$1\le n \le 30$  

## 思路

DFS 分治下去统计最小贡献，

1. 计算 $[l,r]$ 间的复仇者个数 $cnt$，可以使用二分查找确定第一个位置大于等于 $l$ 的复仇者和最后一个位置小于等于 $r$ 的复仇者。

2. 如果没有复仇者，答案就是 $A$，可以证明，再分下去不会更优。
3. 如果有复仇者，有两种方案，取其中较小值即可：
	- 一种是不拆成两半，代价为 $B\times cnt\times (r-l+1)$。

	- 一种是拆成 $[l,\left\lfloor \frac{l+r}{2}\right\rfloor]$ 和 $[\left\lfloor \frac{l+r}{2}\right\rfloor+1,r]$ 两半，答案为两段区间贡献的和。

## code

代码时间！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,A,B,in[100005],ans;
long long find(long long l,long long r){
	long long la=lower_bound(in,in+k+2,l)-in,ra=upper_bound(in,in+k+2,r)-in-1;//计算复仇者个数
	long long mid=(l+r)>>1;
	if(ra<la)	return A;
	else if(l==r)	return B*(ra-la+1);
	else return min(B*(ra-la+1)*(r-l+1),find(l,mid)+find(mid+1,r));
}
int main(){
	cin>>n>>k>>A>>B;
	for(int i=1;i<=k;i++)	cin>>in[i];
	sort(in+1,in+k+1);
	cout<<find(1,1<<n);
}
```
时间复杂度 $O($ 能过 $)$

---

## 作者：MiniLong (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1111C)

## 思路

按照题意进行递归模拟即可，枚到最底层直接返回 $ B $ 或 $ A $，但时间复杂度为 $ O(2^n) $，所以考虑剪枝。

因为在长度为 $ 2 ^ n $ 的区间内有绝大部分都是空的，所以当递归到一段空的区间时，直接返回 $A$。

先将序列 $a$ 排序，查询一段区间内的和时可以对于左右端点二分，和就是二分出来在序列 $a$ 中的下标差。

记得返回的时候要把递归下去的答案和 $ B \times x \times l $ 取最小值，因为 $ B \times x \times l $ 可能会小于它。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid (l + r >> 1ll)
using namespace std;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
};
using namespace fastio;
typedef pair<int, int> PII;
const int N = 100005, K = 35;
int n, k, A, B, a[N];
int solve(int l, int r){
    int res = 2e9, siz = 0;
    int u = lower_bound(a + 1, a + 1 + k, l) - a, v = upper_bound(a + 1, a + 1 + k, r) - a;
    siz = v - u;
    if(!siz) return A;
    if(l == r){
        return B * siz;
    }
    int x = solve(l, mid), y = solve(mid + 1, r);
    res = x + y;
    return min(res, siz * (r - l + 1) * B);
}
signed main(){
    read(n, k, A, B);
    for(int i = 1; i <= k; ++i) read(a[i]);
    sort(a + 1, a + 1 + k);
    int len = (1 << n);
    writeln(solve(1, len));
    return 0;
}
```

---

## 作者：tkdqmx (赞：2)

按照题意递归模拟。

为了防超时，进行以下剪枝优化：

计算 $[l,r]$ 间的复仇者个数 ，可以使用二分查找确定第一个位置大于等于 $l$ 的复仇者和最后一个位置小于等于 $r$ 的复仇者。

若没有复仇者，就直接返回 $A$。

如果有复仇者返回以下两种方案的最小值：

1.不拆成两半，代价为 $B*(r-l+1)*cnt$；

2.拆成 $[l,mid]$ 和 $[mid+1,r]$ 两半（其中 $mid = \lfloor \frac{l+r}{2} \rfloor$），答案为 $solve(l,mid)+solve(mid+1,r)$。

代码如下：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL n,k,A,B,s[100005];
LL solve(LL l,LL r){
	LL m1=lower_bound(s,s+k+2,l)-s,m2=upper_bound(s,s+k+2,r)-s-1;
    if(m2<m1)  return A;
    if(l==r)    return B*(m2-m1+1);
    LL mid=(l+r)>>1;
    return min(solve(l,mid)+solve(mid+1,r),B*(r-l+1)*(m2-m1+1));
}
int main(){
	cin>>n>>k>>A>>B;
	for(int i=1;i<=k;i++)	cin>>s[i];
	sort(s+1,s+k+1),s[0]=LONG_LONG_MIN,s[k+1]=LONG_LONG_MAX;
	cout<<solve(1ll,1ll<<n);
}
~~~

---

## 作者：swiftc (赞：1)

看了那么多大佬的线段树题解，本萌新瑟瑟发抖，那么就写一篇卡常能过的$dfs$题解吧

首先，对于每一段区间，我们可以用树状数组来维护其中的复仇者数量，然后讨论如何炸毁这段区间：

如果其中没有复仇者，直接炸毁即可

要不然把区间分成两段，枚举每一段是直接炸毁还是继续$dfs$下去，最后取答案的最小值即可

### 但是注意一下数据范围
$1≤n≤30$

这样树状数组一定会$MLE$的

那用$map$代替数组？

复杂度多了一个$log$，又$TLE$了

那么我们就要用一种神奇的数据结构了：```tr1::unordered_map```，它和map的用法一模一样，而且复杂度是$O(1)$的

我们这样就愉快的通过这道题了

### code:
```cpp
#include<bits/stdc++.h>
#include<tr1/unordered_map>
#pragma GCC optimize(3)
using namespace std;

#define int long long
int n,k,A,B,ans,a[100002],l;
tr1::unordered_map<int,int>tt;
void add2(int s,int v){
	for(int i=s;i<=l+5;i+=(i&-i)){
		tt[i]+=v;
	}
}
int ask2(int s){
	int sum=0;
	for(int i=s;i;i-=(i&-i))sum+=tt[i];
	return sum; 
}
int work2(int l,int r){
	int xr=ask2(r),xl=ask2(l-1);
	if(xr-xl==0){
		return A;
	}
	if(l==r){
		return B*(xr-xl);
	}
	int mid=(l+r)/2;
	int a1=work2(l,mid),a2=work2(mid+1,r);
	int b1=B*(mid-l+1)*(ask2(mid)-xl),b2=B*(r-mid)*(xr-ask2(mid));
	if(b1==0)b1=1e8;
	if(b2==0)b2=1e8;
	return min(B*(r-l+1)*(xr-xl),min(a1+b2,min(b1+a2,a1+a2)));
} 
main(){
	scanf("%lld%lld%lld%lld",&n,&k,&A,&B);
	l=pow(2,n);
	for(int i=1;i<=k;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=k;i++){
		add2(a[i],1);
	}
	printf("%lld\n",work2(1,l));
	return 0;
}
```


---

## 作者：Dilute (赞：1)

## [$$\texttt{在本人blog食用更佳QwQ}$$](http://dilute.coding.me/2019/02/12/Solutions/Solution-CF1111C/)

### 简单递归

首先我们如果要消灭一段区间$[l, r]$，我们可以有三种选择：

- 如果$[l, r]$区间内没人，那么直接花费$A$的代价将这段摧毁
- 如果$r  > l$（即这段区间长度$>2$），可以选择把它切割成$\left[ l, \lfloor \frac{l + r}2\rfloor\right]$ $\left[\lceil \frac{l + r}2\rceil, r\right]$两段
- 如果$[l, r]$区间内有人，直接花费$b * (r - l + 1) * x$的代价将其摧毁。

那么我们可以直接递归寻找对于每个区间的最优解

但是如果暴力找，那么是$O(2^n)$的。

然后我们可以发现一个很显然的结论，就是若一个区间内没人，那么第一种方案是肯定最优的。

可以理解成动态开点线段树上的$DP$

将这个优化加上去之后复杂度就是正确的QwQ

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647
#define int long long

int inp(){
    char c = getchar();
    int neg = 1;
    while(c < '0' || c > '9'){
        if(c == '-')
            neg = -1;
        c = getchar();
    }
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return neg * sum;
}

int pos[100010];
int n, k, a, b;

int solve(int l, int r){
    int cnt = std::upper_bound(pos + 1, pos + k + 1, r) - std::lower_bound(pos + 1, pos + k + 1, l);
    // printf("cnt [%d, %d] = %d\n", l, r, cnt);
    int mid = (l + r) >> 1;
    if(l == r && cnt != 0)
        return (r - l + 1) * cnt * b;
    return (cnt == 0) ? a : std::min((r - l + 1) * cnt * b, solve(l, mid) + solve(mid + 1, r));
}

signed main(){
    n = inp();
    k = inp();
    a = inp();
    b = inp();
    for(int i = 1; i <= k; i++)
        pos[i] = inp();
    std::sort(pos + 1, pos + k + 1);
    printf("%I64d\n", solve(1, 1 << n));
    return 0;
}
```



---

## 作者：NaCly_Fish (赞：1)

这题思路其实不难，但是当场我没想到正解，先说一下我当场想到的做法吧。

这题难点就在于怎么统计区间$[l,r]$中，有多少个$\text{Avenger}$。  
我就想，区间求和嘛，那就用树状数组+map维护啊。结果妥妥的T飞了QAQ  

官方题解中给出的做法是，将$\text{Avenger}$的位置排序，然后求$l$和$r$的前驱后继，就可以知道这个区间中有多少个$\text{Avenger}$了。  
这一点可以手写二分，也可以用`lower_bound`和`upper_bound`。

剩下的部分就很简单，对于计算区间$[l,r]$的最小花费，就是对比直接烧的花费和分开烧的最小花费和，写个递归函数就完事了。  
这个递归函数的边界条件是$l=r$和区间中$\text{Avenger}$数量为$0$，此时直接返回结果即可。  

献上丑陋的代码：  
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define N 100003
#define int long long
using namespace std;

int a[N];
int n,k,A,B;

inline void read(int &x);
void print(int x);
int dp(int l,int r);
inline int query(int l,int r);
inline int min(int x,int y);

signed main(){
    read(n),read(k),read(A),read(B);
    for(int i=0;i<k;++i)
        read(a[i]);
    sort(a,a+k);
    print(dp(1,1<<n));
}

int dp(int l,int r){
    int cur,mid,cnt = query(l,r);
    if(cnt==0) cur = A;
    else cur = cnt*(r-l+1)*B;
    if(cnt==0||r==l) return cur;
    mid = (r+l)>>1;
    return min(cur,dp(l,mid)+dp(mid+1,r));
}

inline int query(int l,int r){
    int *L,*R;
    L = lower_bound(a,a+k,l);
    R = upper_bound(a,a+k,r);
    return R-L;
}

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(int x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}

inline int min(int x,int y){
    return x<y?x:y;
}
```

---

## 作者：Zechariah (赞：1)

看着题目好像很复杂，其实我们按照题意模拟即可  
因为我们发现，将这个区间对半分下去，最多也就$31$层  
具体怎么做呢？对于某个区间，考虑将其对半分得到的价值更小还是整个的价值更小，dfs的时候存下这几个东西：  
- $st$表示当前区间的左端点的前一个位置（这样比较好处理）  
- $len$表示这个区间的长度  
- $l$和$r$表示这个区间包含的heroes是给出的序列排序后的$[l,r]$  

那么我们在dfs下去的时候，只需要二分出当前的$[l,r]$中哪些在左边，哪些在右边，如果对半分后某个区间是空的，这个区间的价值就是$A$，两个小区间的和与当前这个大区间比较，取较小值即可。  

复杂度$O(nlogk)$

```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5, mod = 10007;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl int chread(rg char s[])
    {
        rg int len = 0;
        rg char ch;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        s[len++] = ch;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            s[len++] = ch;
        s[len] = 0;
        return len;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
ll a[N], n, k, A, B;
ll dfs(rg int l, rg int r, rg ll len, rg int st)
{
    if (len == 0)return B * (r - l + 1)* (1 << len);
    rg ll ans = B * (r - l + 1)*(1 << len);
    rg int L = l, R = r;
    --len;
    while (L <= R)
    {
        rg int mid = L + R >> 1;
        if (a[mid] > st + (1 << len))R = mid - 1;
        else L = mid + 1;
    }L = R;
    rg ll ri, le;
    if (L >= l)le = dfs(l, L, len, st); else le = A;
    if (L < r)ri = dfs(L + 1, r, len, st + (1 << len)); else ri = A;
    return fast_IO::min(ans, le + ri);
}

int main(void)
{
    n = fast_IO::read(), k = fast_IO::read(), A = fast_IO::read(), B = fast_IO::read();
    for (rg int i = 1; i <= k; ++i)a[i] = fast_IO::read();
    sort(a + 1, a + k + 1);
    fast_IO::write(dfs(1, k, n, 0));
    return 0;
}

```

---

## 作者：newbiechd (赞：1)

动态开点线段树入门。

一看这题就想到线段树，结果值域$2 ^ {30}$，普通线段树显然爆空间，发现修改次数$\le 1e5$，可以动态开点。具体来说对于每一次修改，如果在线段树上要修改的当前结点还不存在，就新开一个结点记录这个结点的信息，注意左右儿子需要单独记了，不能直接$k << 1$和$k << 1 | 1$，其他操作就都一样了，空间复杂度$O(n k)$。这个题需要考虑空结点的贡献，只需要把$0$号节点的$v$值改成$A$就行了。

```cpp
#include <cstdio>
#include <cctype>
#define R register
#define I inline
#define B 1000000
#define L long long
using namespace std;
const int N = 100003;
char buf[B], *p1, *p2;
I char gc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, B, stdin), p1==p2) ? EOF : *p1++; }
I int rd() {
    R int f = 0;
    R char c = gc();
    while (c < 48 || c > 57)
    	c = gc();
    while (c > 47 && c < 58)
    	f = f * 10 + (c ^ 48), c = gc();
    return f;
}
int a, b, T;
struct segtree {
    int c, p, q, d;
    L v;
}e[N << 5];
I L min(L x, L y) { return x < y ? x : y; }
void insert(int &k, int l, int r, int x) {
    if (!k)
        k = ++T, e[k].d = r - l + 1;
    ++e[k].c;
    if (l == r) {
        e[k].v = 1ll * b * e[k].c;
        return ;
    }
    R int m = l + r >> 1;
    if (x <= m)
        insert(e[k].p, l, m, x);
    else
        insert(e[k].q, m + 1, r, x);
    e[k].v = min(e[e[k].p].v + e[e[k].q].v, 1ll * b * (e[e[k].p].c + e[e[k].q].c) * e[k].d);
}
int main() {
    R int n, m, rt = 0, i, x;
    n = 1 << rd(), m = rd(), a = rd(), b = rd();
    e[0].v = a;
    for (i = 1; i <= m; ++i)
        x = rd(), insert(rt, 1, n, x);
    printf("%I64d", e[rt].v);
    return 0;
}
```

可以结合这道题好好理解动态开点线段树。

---

## 作者：Erotate (赞：0)

### Solution

这里看到 $1 \leq n \leq 30$，直接暴力搜索显然会超时，这是考虑剪枝。

首先我们对 $a$ 数组进行排序，以便于在搜索的时候快速算出这段区间的英雄数量。

接下来，搜索的时候，我们分类讨论：

1. 如果一段区间没有英雄，直接摧毁。

2. 如果一个区间已经不能在分成两段（即长度为 $1$），那就只能直接摧毁。

3. 如果能继续分成两段，那要么直接摧毁，要么把这段区间分成两段分别摧毁，取两者的最小值。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
int n,k,A,B,a[N];
int dfs(int l,int r){
    int x=lower_bound(a+1,a+k+1,l)-a,y=upper_bound(a+1,a+k+1,r)-a;//计算这段区间有多少个英雄。
    if(y-x==0) return A;//注意，这一个判断一定要放在最前面，因为无论能不能分成两段，没有英雄的区间的摧毁代价都是 A。
    if(l==r) return (y-x)*B;
    int resl=dfs(l,l+r>>1),resr=dfs((l+r>>1)+1,r);
    return min(resl+resr,(y-x)*(r-l+1)*B);//取两者最小值。
}
signed main(){
    scanf("%lld%lld%lld%lld",&n,&k,&A,&B);
    for(int i=1;i<=k;++i) scanf("%lld",&a[i]);
    sort(a+1,a+k+1);//排序
    printf("%lld\n",dfs(1,1<<n));
}
```

### 后记

仔细想想，区间的总长度最大是 $2^{30}$，但是英雄最多只有 $10000$ 个，所以“一段区间没有英雄直接摧毁”这个剪枝还是很强的。

---

## 作者：zhang_kevin (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1111C)

# Content

有 $2^n$ 个基地，$k$ 个 $\verb!Avengers!$，每个 $\verb!Avengers!$ 占据一个位置（可以叠加），为了摧毁整个基地，从区间 $[1,2^n]$ 开始，对于每一个区间 $[l,r]$ 有两种选择：

1. 二分操作 $[l,mid]$ 和 $[mid+1,r]$。
2. 若当前区间内没有复仇者，则花费代价 $A$ 摧毁这个区间的基地，若有 $cnt$ 个复仇者，则花费代价 $B\times(r-l+1)\times cnt$ 摧毁这个区间的复仇者和基地。

求摧毁整个基地的最小代价。

# Solution

这道题很容易想到用分治做。

我们令递归函数 $get(l,r)$ 表示摧毁区间 $[l,r]$ 所需的最小能量。

这非常好实现，但是值域比较大，需要一点点剪枝（计算时可以使用二分）。

最后注意开 `long long`。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
typedef long long ll;
std::vector<ll> Avengers;
ll n, k, A, B;
inline ll get(ll l, ll r){
	ll i = lower_bound(Avengers.begin(), Avengers.end(), l) - Avengers.begin();
	ll j = upper_bound(Avengers.begin(), Avengers.end(), r) - Avengers.begin();
	j--;
	ll cnt = j - i + 1, power;
	if(cnt == 0){
		power = A;
	}else{
	    power = B * (r-l+1) * cnt;
	}
	if(l == r || cnt == 0){
		return power;
	}
	ll mid = (l+r) >> 1;
	ll Min = std::min(power, get(l, mid)+get(mid+1, r));
	return Min;
}
auto Solve = [](void) -> int{
	scanf("%lld%lld%lld%lld", &n, &k, &A, &B);
	for(ll i = 0; i < k; i++){
		ll val;
		scanf("%lld", &val);
		Avengers.push_back(val);
	}
	std::sort(Avengers.begin(), Avengers.end());
	printf("%lld", get(1, 1<<n));
	return 0;
}();
int main(){return Solve;}
```

---

