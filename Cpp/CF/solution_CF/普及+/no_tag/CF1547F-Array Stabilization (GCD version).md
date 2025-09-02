# Array Stabilization (GCD version)

## 题目描述

You are given an array of positive integers $ a = [a_0, a_1, \dots, a_{n - 1}] $ ( $ n \ge 2 $ ).

In one step, the array $ a $ is replaced with another array of length $ n $ , in which each element is the [greatest common divisor (GCD)](http://tiny.cc/tuy9uz) of two neighboring elements (the element itself and its right neighbor; consider that the right neighbor of the $ (n - 1) $ -th element is the $ 0 $ -th element).

Formally speaking, a new array $ b = [b_0, b_1, \dots, b_{n - 1}] $ is being built from array $ a = [a_0, a_1, \dots, a_{n - 1}] $ such that $ b_i $ $ = \gcd(a_i, a_{(i + 1) \mod n}) $ , where $ \gcd(x, y) $ is the greatest common divisor of $ x $ and $ y $ , and $ x \mod y $ is the remainder of $ x $ dividing by $ y $ . In one step the array $ b $ is built and then the array $ a $ is replaced with $ b $ (that is, the assignment $ a $ := $ b $ is taking place).

For example, if $ a = [16, 24, 10, 5] $ then $ b = [\gcd(16, 24) $ , $ \gcd(24, 10) $ , $ \gcd(10, 5) $ , $ \gcd(5, 16)] $ $ = [8, 2, 5, 1] $ . Thus, after one step the array $ a = [16, 24, 10, 5] $ will be equal to $ [8, 2, 5, 1] $ .

For a given array $ a $ , find the minimum number of steps after which all values $ a_i $ become equal (that is, $ a_0 = a_1 = \dots = a_{n - 1} $ ). If the original array $ a $ consists of identical elements then consider the number of steps is equal to $ 0 $ .

## 样例 #1

### 输入

```
5
4
16 24 10 5
4
42 42 42 42
3
4 6 4
5
1 2 3 4 5
6
9 9 27 9 9 63```

### 输出

```
3
0
2
1
1```

# 题解

## 作者：Him_shu (赞：13)

## 题目+样例



题目已经特别好理解了，在此我就解释一下样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/ab91nvs7.png)

**解释：**

![](https://cdn.luogu.com.cn/upload/image_hosting/mhddga5l.png)

故此可知，答案是 $3$。


## 分析

既然题目是问：最少多少次操作后满足 $a$ 序列所有元素相同？

- 那么最后的时候每一项的值是多少呢？

 回答：最后相等时，每一项的值为所有初始项的 $\gcd$。

------------

- 但有环怎么办？

回答：**双倍链**解决环问题。

**[双倍链学习](https://www.cnblogs.com/FuTaimeng/p/5427426.html)**

```cpp
for(int i=1;i<=n;i++){
  cin>>a[i];
  a[n+i]=a[i];
}
```



------------

不妨把思路打开。

- 在第 $x$ 次操作后，第 $i$ 项的值是多少？

回答：为 $\gcd(a_i,a_{i+1},...,a_{i+x})$（注意环下标），这个可以用 **ST表**快速计算。

**[ST表学习](https://oi-wiki.org/topic/rmq/)**

```cpp
void in(){
  for(int i=1;i<=n*2;i++){
    st[i][0]=a[i];
  }
  for(int j=1;(1<<j)<=n*2;j++){
    for(int i=1;i+(1<<j)-1<=n*2;i++){
      st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
  }
}
int out(int a,int b){
  int k=log(b-a+1)/log(2.0);
  return __gcd(st[a][k],st[b-(1<<k)+1][k]);
}
```

------------

大家能看到在操作次数存在一个临界值 $x$，大于等于 $x$ 就一直是一个固定的值 $\gcd(a_1,a_2,...,a_n)$（~~这个在前面讲过了~~）。

- 这么说 $x$ 是单调的，不妨考虑**二分答案**。

在第 $x$ 次操作后，判断每项是否相等。

对于所有的 $i$: 

$\gcd(a_i,a_{i+1},...,a_{i+x})$ 是否等于 $\gcd(a_1,a_2,...,a_n)$。

**[二分学习](https://oi-wiki.org/basic/binary/)**

```cpp
bool isok(int x){
  for(int i=1;i<=n;i++){
    if(out(i,i+x)!=zh){
      return 0;
    }
  }
  return 1;
}
```
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double
#define int long long
#define mod 1000000007
#define inf 1e14
#define N 400005
int t,n,a[N],st[N][64],zh;
void in(){
  for(int i=1;i<=n*2;i++){
    st[i][0]=a[i];
  }
  for(int j=1;(1<<j)<=n*2;j++){
    for(int i=1;i+(1<<j)-1<=n*2;i++){
      st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
  }
}
int out(int a,int b){
  int k=log(b-a+1)/log(2.0);
  return __gcd(st[a][k],st[b-(1<<k)+1][k]);
}
bool isok(int x){
  for(int i=1;i<=n;i++){
    if(out(i,i+x)!=zh){
      return 0;
    }
  }
  return 1;
}
signed main(){
  cin>>t;
  while(t--){
    cin>>n;
    for(int i=1;i<=n;i++){
      cin>>a[i];
      a[n+i]=a[i];
    }
    in();
    zh=out(1,n);
    int l=0,r=n,ans;
    while(l<=r){
      int mid=(l+r)/2;
      if(isok(mid)){
        r=mid-1;
        ans=mid;
      }
      else{
        l=mid+1;
      }
    }
    cout<<ans<<'\n';
  }
  return 0;
}
```

---

## 作者：MatrixCascade (赞：12)

先断环成链，显然，$p$ 次操作后每个 $a_i$ 会变成 $\gcd(a_i,a_{i+1},...,a_{i+p})$ ，我们可以先把所有数除以 $\gcd(a_1,a_2,...,a_n)$ ，然后只需要求出对于 $1 \to n$ 中每个 $i$，最小的 $p$ 使得 $\gcd(a_i,a_{i+1},...,a_{i+p})=1$，答案就是对每个 $p-1$ 取 max，线段树+双指针维护即可。

注意特判所有数相等的情况。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
//#define int long long
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define down(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
int a[505050];
int ans[2000001];
int ls(int x)
{
	return x<<1;
}
int rs(int x)
{
	return x<<1|1;
}
void pushup(int x)
{
	ans[x]=__gcd(ans[ls(x)],ans[rs(x)]);
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		ans[p]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	pushup(p);
}
int qry(int p,int l,int r,int nl,int nr)
{
	if(l>=nl&&nr>=r)return ans[p];
	int mid=(l+r)>>1;
	int nw=0;
	if(nl<=mid)nw=__gcd(nw,qry(ls(p),l,mid,nl,nr));
	if(nr>mid)nw=__gcd(nw,qry(rs(p),mid+1,r,nl,nr));
	return nw;
}
signed main()
{
	int T=read();
	while(T--)
	{
		n=read();
		up(i,1,n)a[i]=read();
		int gd=0;
		up(i,1,n)gd=__gcd(gd,a[i]);
		int tot=1;
		up(i,2,n)tot+=(a[i]==a[1]);
		if(tot==n)
		{
			puts("0");
			continue;
		}
		up(i,1,n)a[i+n]=a[i];
		int mx=0;
		up(i,1,n+n)a[i]/=gd;
		build(1,1,n*2);
		int l=1,r=1;
		up(r,1,n*2)
		{
			while(l<=r&&qry(1,1,n+n,l,r)==1)++l;
			mx=max(mx,r-l+1);
		}
		cout<<mx<<endl;
	}
}

```


---

## 作者：HoshizoraZ (赞：10)

**观前提醒**：

- 本题解与官方提供的解法不同，想了解官方解法请点击[这里](https://codeforces.ml/blog/entry/92715)。

- [可能更好的阅读体验](https://www.cnblogs.com/zengpeichen/p/14999323.html)。

- upd on 2021/7/15：修改了一处错误

### 题意

有 $n$ 个数 $a_1,a_2,...,a_n$（这里略有改动，原题是下标为 $0 \sim n-1$，此处为方便变成 $1 \sim n$）。

每次新设立一个数组 $b$，且 $b_i = \gcd(a_i,a_{i+1})$，特别地 $b_n=\gcd(a_n,a_1)$，然后将序列 $b$ 的值都赋值给 $a$。

问需要操作多少次，使得 $a_1=a_2=...=a_n$。

$n \le 2 \times 10^5$，$1 \le a_i \le 10^6$。


### 分析

首先我们需要知道一个结论：$\gcd(a,b,c)=\gcd(\gcd(a,b),c)$。

简略证明如下：

可以将 $a,b,c$ 质因数分解。

设 $p_i$ 为从小到大第 $i$ 个质数，$a=\prod\limits_{i} p_i^{A_i}$，$b=\prod\limits_{i} p_i^{B_i}$，$c=\prod\limits_{i} p_i^{C_i}$，其中 $A_i,B_i,C_i$ 均为非负整数。

那么可以进行推导。

$$
\begin{aligned}
右式 &= \gcd\left(\gcd\left({\prod\limits_{i} p_i^{A_i},\prod\limits_{i} p_i^{B_i}}\right),c\right) \\
&= \gcd \left(\prod\limits_{i} p_i^{\min(A_i,B_i)},c\right)\\
&= \gcd \left(\prod\limits_{i} p_i^{\min(A_i,B_i)},\prod\limits_{i} p_i^{C_i}\right) \\
&= \prod\limits_{i} p_i^{\min(A_i,B_i,C_i)} \\
&= 左式 \\
\end{aligned}
$$

### 断环成链

我们发现由于首尾将序列 $b$ 的构造方式是把序列 $a$ 在环上求，所以为了方便，我们将 $a$ 复制，接到原来的 $a$ 尾部。

### 继续分析

如果我们是第一次操作，那么 $b_i=\gcd(a_i,a_{i+1})$，此时我们暂时不将 $b$ 赋给 $a$，先拿数组 $c$ 保存。

第二次操作，有 $b_i=\gcd(c_i,c_{i+1})=\gcd\left(\gcd(a_i,a_{i+1}),\gcd(a_{i+1},a_{i+2})\right)=\gcd(a_i,a_{i+1},a_{i+2})$。

然后就可以发现第 $k$ 次操作有 $b_i=\gcd{a_i,a_{i+1},a_{i+2},...,a_{i+k}}$，**这一行 $a$ 是初始序列。**

如果想知道要几次操作使得 $a_1,a_2,...,a_{n}$ 相等，相当于求需要几次操作，使得所有的 $b_i$ 均等于 $\gcd(a_1,a_2,...,a_n)$。

那么如果这个次数不够，那么**至少存在**一个 $b_i$ 的值不等于（即**大于**） $\gcd(a_1,a_2,...,a_n)$。

综上所述，我们需要求一个最**小**的 $k$，使得 $1 \le i \le n$ 的所有 $i$，均有 $\gcd(a_i,a_{i+1},...,a_{i+k-1})=\gcd(a_1,a_2,...,a_n)$，此时答案即为 $k-1$。

### 算法选择

如果我们对每个位置 $i$ 按顺序暴力寻找 $k$，那复杂度为 $n^2 \log \max\{a_i\}$ 的，显然不行。

发现，如果满足 $\gcd(a_i,a_{i+1},...,a_{i+k-\color{red}2})=\gcd(a_1,a_2,...,a_n)$，那么一定有 $\gcd(a_i,a_{i+1},...,a_{i+k-\color{red}1})=\gcd(a_1,a_2,...,a_n)$。

即存在一个 $j$，若 $k \le j$ 其 $\gcd$ 的值**不等于** $\gcd(a_1,a_2,...,a_n)$，反之 $k>j$ 时二者相等。

所以，对于每个 $i$ 我们可以**二分查找**最小的 $k$。

最后还存在一个问题，就是逐步求 $\gcd(a_i,a_{i+1},a_{i+2}...)$ 这步会拖慢程序的效率。

观察到原始的 $a_i$ 不会改变，且多次给同一个 $a_i$ 求 $\gcd$ 不影响结果，我们可以使用 ST 表。

先对**已经破环的链**存入 ST 表进行预处理，在查询的时候只需要 $O(\log \max\{a_i\})$ 的复杂度（用于求 $\gcd$）。

这个做法时间复杂度为 $\mathcal{O}(n \log n \log \max\{a_i\})$，在 $4$ 秒的限制下可以轻松通过。

### 代码

```cpp
#include <bits/stdc++.h>
#define INF 1e9
#define eps 1e-6
typedef long long ll;
using namespace std;
 
int t, n, a[400010], GCD, ans, st[400010][20];
bool b[400010], bb;
 
int gcd(int x, int y){
    if(!y) return x;
    return gcd(y, x % y);
}
 
int query(int i, int j){    // ST 表查询
    int k = log2(j - i + 1);
    return gcd(st[i][k], st[j - (1 << k) + 1][k]);
}
 
int main(){
 
    cin >> t;
    while(t--){
        cin >> n, ans = bb = 0;
        for(int i = 1; i <= n; i++)
            cin >> a[i], b[i] = 0;
        for(int i = 1; i <= n; i++) a[i + n] = a[i], st[i][0] = st[i + n][0] = a[i];    // 破环为链
        for(int i = 1; i <= n; i++)
            if(a[i] != a[1]){
                bb = 1;
                break;
            }
        if(!bb){
            puts("0");
            continue;
        }
        GCD = a[1];
        for(int i = 2; i <= n; i++) GCD = gcd(GCD, a[i]);
        for(int j = 1; (1 << j) <= n + n; j++)    // 注意这里是 n + n，ST 表需要处理整条链
            for(int i = 1; i + (1 << j) - 1 <= n + n; i++)
                st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        for(int i = 1, L, R, mid; i <= n; i++){
            L = i, R = n + i - 1;
            while(L < R){    
                int mid = (L + R) >> 1;
                if(query(i, mid) != GCD) L = mid + 1;
                else R = mid;
            }
            ans = max(ans, L - i);
        }
        printf("%d\n", ans);
    }
 
    return 0;
}

```

---

## 作者：chrisgr_pretty_girl (赞：4)

解法比较抽象，但貌似比较快。  
首先我们知道求 $$\gcd$$ 就是对两个数所有质因数的指数求最小值，那么最后操作得到的元素一定是所有质因数最小指数次幂的积。  
有点抽象，所以我举个例子 $$12$$ 是由 $$3$$ 的一次方和 $$2$$ 的平方乘积得到的，$$16$$ 是由 $$2$$ 的三次方得到的，所以二者的 $$\gcd$$ 就是 $$2$$ 的平方。  
明白了这些，那么我们就有一个想法了，可以先将所有数扫一遍，求出每个质因子的最小指数，那么答案就是非最小指数到最小指数的距离。  
因为 $$10^6$$ 以内的质数很多，所以我们求的时候不能一个一个指数的枚举。但我们发现 $$10^6$$ 以内的数的质因子个数很少，为常数级别。所以我们求最大距离的时候只需要枚举位置，并对当前位置的数含有的质因子操作即可。

时间复杂度瓶颈在求质因数的最小指数，时间复杂度近似 $$O(n \sqrt{a_{max}})$$。完美通过。

###### code  
```cpp
#include<bits/stdc++.h>
#define aa a[i]
using namespace std;
const int N = 2e5 + 5, U = 1e6 + 5;
int n, a[N], p[N << 1], mn[N << 1], ans, cnt[N << 1];
bool book[U], book2[U], book3[U];
vector<int> mem;
struct node { int x, y; };
vector<node> num[N], lst;
inline void init() {
    for(int i = 2; i < U; ++i) {
        if(!book[i]) p[++p[0]] = i;
        for(int j = 1; j <= p[0]; ++j) {
            if(1ll * p[j] * i >= U) break;
            if(book[p[j] * i]) break;
            book[p[j] * i] = 1;
        }
    }
}
int main() {
    init();
    int t;
    scanf("%d", &t);
    while(t--) {
        ans = 0;
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            num[i].clear();
            for(int j = 1; j <= p[0] && 1ll * p[j] * p[j] <= a[i]; ++j) {
                int cnt1 = 0;
                while(!(aa % p[j])) ++cnt1, aa /= p[j];
                if(cnt1) {
                    ++cnt[j], mem.push_back(j), mn[j] = mn[j] ? min(mn[j], cnt1) : cnt1;
                    num[i].push_back({j, cnt1});
                }
            }
            if(aa ^ 1) {
                int now = lower_bound(p + 1, p + p[0] + 1, aa) - p;
                mem.push_back(now);
                mn[now] = mn[now] ? min(mn[now], 1) : 1, ++cnt[now];
                num[i].push_back({now, 1});
            }
        }
        sort(mem.begin(), mem.end());
        unique(mem.begin(), mem.end());
        for(int i = mem.size() - 1; ~i; --i) {
            int now = mem[i];
            if(cnt[now] ^ n) mn[now] = 0, cnt[now] = 0;
        }
        for(int i = 1; i <= (n << 1); ++i) {
            int ii = i % n;
            ii = ii ? ii : n;
            for(int j = num[ii].size() - 1; ~j; --j) {
                node now = num[ii][j];
                if(now.y ^ mn[now.x]) book2[now.x] = 1;
            }
            vector<node> mm;
            while(!lst.empty()) {
                node now = lst.back();
                lst.pop_back();
                if(!book2[now.x]) {
                    ans = max(ans, i - now.y);
                }
                else book3[now.x] = 1, mm.push_back(now);
            }
            for(int j = num[ii].size() - 1; ~j; --j) {
                node now = num[ii][j];
                if(!book3[now.x] && book2[now.x]) mm.push_back({now.x, i});
            }
            for(int i = mm.size() - 1; ~i; --i) {
                int now = mm[i].x;
                book2[now] = book3[now] = 0;
            }
            while(!mm.empty()) lst.push_back(mm.back()), mm.pop_back();
        }
        printf("%d\n", ans);
        while(!mem.empty()) {
            int now = mem.back();
            mn[now] = cnt[now] = 0;
            mem.pop_back();
        }
    }
    return 0;
}
```

---

## 作者：shao0320 (赞：3)

### CF1547F Array Stabilization (GCD version)

贡献个 $O(N\log^2N)$ 的套路做法。

首先观察到这个问题具有单调性，即如果我操作了 $k$ 次就可以使所有数变得相同，那么操作 $x(x>k)$ 次也一定可以。

再考虑操作多次的序列是什么样的。如果我们将整个序列复制一份扔到后边去，那么我们操作 $k$ 次的数列的第一项长成这个形式：

$$
a_1=\gcd{a_1,\cdots,a_k+1}
$$

因此可以用 $\text{ST}$ 表在 $O(N\log N)$的时间内算出操作 $k$ 次的数列。

二分答案即可。


---

## 作者：KaisuoShutong (赞：2)

# CF1547F Array Stabilization (GCD version)

掉估值了，写篇题解。  
本文为不同于官解的**倍增**做法。

## 题意
略。
## 题解

观察可以发现，第 $k$ 次操作后的序列会变成：

$\gcd(a_1,...,a_{1+k})~~\gcd(a_2,...,a_{2+k})~~...~~\gcd(a_n,a_1,...,a_k)$

那么只需对于 $\forall i\in [1,n]$，求出最小的 $k$ 使得 $k$ 次操作后的序列的第 $i$ 项为 $1$。答案即为所有 $k$ 的最大值。

怎么做到？倍增。  
断环为链，预处理出 $f(i,j)$ 表示 $i$ ~ $(i+2^j-1)$ 的 $\gcd$ 值。  
对于每个点，向后倍增即可。

时间复杂度 $O(n\cdot \log n)$。

点个赞吧。

```cpp
pw[0]=1;int t=0;
for(int j=1;(pw[t=j]=pw[j-1]*2)<=n;j++)
	for(int i=1;pw[j]+i<=n+1;i++) {
		fa[i][j]=__gcd(fa[i][j-1],fa[i+pw[j-1]][j-1]);
	}
s[n]=a[n];
for(int i=n-1;i;i--) s[i]=__gcd(s[i+1],a[i]);
int ans=0;
for(int i=1,aws,pre,x,gc;i<=n;i++) {
	if(s[i]==s[1]) pre=0,x=i-1,gc=0;
	else pre=s[i],x=0,gc=n-i+1;
	for(int j=t;~j;j--) if(x+pw[j]<=n&&(aws=__gcd(fa[x+1][j],pre))!=s[1]) pre=aws,x+=pw[j],gc+=pw[j];
	ans=max(ans,gc);
}
cout<<ans<<'\n';
```

---

## 作者：二gou子 (赞：2)

## Solution

先将问题转化一下，假设我们对一个位置 $i$ 操作了 $x$ 次，那么 $a_i$ 就会变成 $gcd(a_i,a_{i+1},...,a_{i+x})$ （先不考虑 $i+x>n$ 的情况），容易发现我们最多会操作 $n-1$ 次，因为 $n-1$ 次之后所有的数都会变成 $gcd(a_1,a_2,...,a_n)$

首先我们可以发现一个性质，假设最后所有的数都变成了 $gcdd$ ，那么我们可以在一开始把所有的 $a_i$ 变成 $a_i/gcdd$ ，然后最后序列就会变成全是 $1$ 的序列了。所以现在我们要找的就是最长的满足 $gcd(a_l,a_{l+1},...,a_r)>1$ 的序列了，而最后的长度就是 $r-l+1$ ，这就是我们需要的最多的操作次数，现在问题就转化为了如何求出这个最长的序列

我们考虑最短的不合法序列，这样也就是说最长合法序列再往两边扩展任意一个都会出现一个质因数 $p$ ，使得不是所有数的因子，那么我们现在就要找这个数，从而找到合法序列

所以首先我们来一手线性筛素数，筛出 $MAXa$ 以内的素数，然后对于每一个 $a_i$ 直接暴力质因数分解，时间复杂度应该是 $O(n\sqrt{MAXa})$ ，不过不用慌这题给了 $4s$ 跑过去绰绰有余。我们通过 $vector$ 存一下每个数的质因子，之后我们就枚举每个位置 $i$ ，然后在每个位置 $i$ 上枚举 $a_i$ 的质因子，暴力往两边扩展。我们一边扩展一边约去质因子，这其实很显然：一边跑一边约不会影响结果，因为如果枚举到那个被约去的位置左右两边都无法扩展了，说明都不包含这个质因子，那么约去也不会影响答案。所以说最终的时间复杂度应该是 $O(n\sqrt{MAXa}+\sum_{i=1}^n p_i)$，其中 $p_i$ 表示 $a_i$ 的质因子个数。为了便于实现我们使用 $set$ 来插入和删除每个位置上的质因数，带了一个 $2$~$3$ 的常数，无伤大雅

## Code

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<set>
#define ll long long
using namespace std;
const int N=1e6+5;
int T,n,tot;
int pri[N],a[N];
int v[N];
void xxs(){
	v[1]=1;
	for(int i=2;i<=N-5;i++){
		if(!v[i]){
			v[i]=i;
			pri[++tot]=i;
		}
		for(int j=1;j<=tot&&pri[j]*i<=N-5;j++){
			v[i*pri[j]]=pri[j];
			if(i%pri[j]==0) break;
		}
	}
}
int gcd(int x,int y){
	if(y==0) return x;
	else return gcd(y,x%y);
}
set<int> s[N];
int main()
{
	xxs();
	scanf("%d",&T);
	while(T--){
		int ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			s[i].clear();
			scanf("%d",&a[i]);
		}
		
		int gcdd=0;
		for(int i=1;i<=n;i++){
			gcdd=gcd(a[i],gcdd);
		}
		
		for(int i=1;i<=n;i++){
			a[i]/=gcdd;
		}
		
		for(int i=1;i<=n;i++){
			while(v[a[i]]>1){
				int di=v[a[i]];
				s[i].insert(di);
				while(a[i]%di==0){
					a[i]/=di;
				}
			}
		}		
		
		for(int i=1;i<=n;i++){
			for(set<int>::iterator it=s[i].begin();it!=s[i].end();it++){
           //这里的两个指针细节比较多，需要细细斟酌
				int l=i-1,r=i+1;
				if(l==0) l=n;
				if(r==n+1) r=1;
				while(s[l].count(*it)){
					s[l].erase(*it);
					l--;
					if(l==0) l=n;
					if(l==i) break;
				}
				while(s[r].count(*it)){
					s[r].erase(*it);
					r++;
					if(r==n+1) r=1;
					if(r==i) break;
				}
				if(r==i||l==i) ans=n-1;
				else{
					if(r<=l){
						ans=max(ans,n-l+r-1);
					}
					else{
						ans=max(ans,r-l-1);
					}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：D2T1 (赞：1)

[$\color{blue}{\text {pwp }~{\to\textbf{My blog}\gets}}~\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

## 题解 CF1547F

首先观察题意，可以发现最后的 $a$ 序列所有元素相同，且都为 $\gcd(a_1,a_2,...,a_n)$。所以问题就变成了：求一个最小的 $k$ 使得 $a$ 中每一个长度为 $k+1$ 的区间的 $\gcd$ 为 $\gcd(a_1,a_2,...,a_n)$。

可以发现这个 $k$ 具有单调性。如果 $k$ 满足题意，则 $k+1$ 必定满足题意，因为 $\gcd(a,a)=a$。所以我们考虑二分答案：每次二分出一个 $k$，求出 $a$ 中每个长度为 $k$ 的序列的 $\gcd$，比较是否相等。

现在我们就需要一个快速的算法求 $a$ 中一段子序列的 $\gcd$，且不用带修。所以考虑 **ST 表**。因为 $\gcd(\gcd(a,b),\gcd(a,c))=\gcd(a,b,c)$。

总复杂度 $O(n \log^2n)$（没记错的话求 $\log$ 是 $O(\log n)$ 的）。

由于 `memset` 这东西复杂度是 $O(n)$ 的，慎用。

## 代码

```cpp
//CF1547F
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int lg2[N], st[N][40];
int t, n, a[N];

int ask(int l, int r){
	if(l <= n && r > n) return __gcd(ask(l, n), ask(1, r-n));
	int k = lg2[r-l+1];
	return __gcd(st[l][k], st[r-(1<<k)+1][k]);
}
bool check(int k){
	int t = ask(1, 1+k-1);
	for(int i = 2; i <= n; ++ i)
		if(ask(i, i+k-1) != t) return false;
	return true;
}

int main(){
	scanf("%d", &t);
	for(int i = 2; i < N; ++ i)
		lg2[i] = lg2[i>>1] + 1;
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i)
			scanf("%d", &a[i]), st[i][0] = a[i];
		for(int j = 1; j <= lg2[n]; ++ j)
			for(int i = 1; i <= (n) - (1<<j) + 1; ++ i)
				st[i][j] = __gcd(st[i][j-1], st[i+(1<<j-1)][j-1]);
		int l = 1, r = n;
		while(l < r){
			int mid = l + r >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%d\n", l-1);
	}
	return 0;
}
```

---

## 作者：BreakPlus (赞：1)

$\large \text{Discription}$

给定 $n$ 和长度为 $n$ 的序列 $a$，求最小的 $k$，使得对于所有的 $i$，$f(i,k)$ 相等。其中，当 $i \le n-k$ 时，$f(i,k)=\gcd \{a_i,a_{i+1},...,a_{i+k}\}$；否则，$f(i,k)=\gcd \{a_i,a_{i+1},...,a_n,a_1,...,a_{i+k-n}\}$。

$\large \text{Solution}$

$\text{Part\ 1}$ 题意转换

首先，根据原题题面，我们先设有序列 $a=\{u,v,w,x\}$。

一次操作：$a=\{\gcd(u,v),\gcd(v,w),\gcd(w,x),\gcd(x,u)\}$

两次操作：$a=\{\gcd(u,v,w),\gcd(v,w,x),\gcd(w,x,u),\gcd(x,u,v)\}$

现在再转换为上面的描述应该不难了吧。

$\text{Part\ 2}$ 快速计算（ST 表优化）

假设我们知道 $k$，然后怎么快速判断是否满足相等呢？对于区间求 $\gcd$ 的问题，我们可以使用 ST 表进行优化，预处理 $O(n \log_2 n)$，单次查询 $O(1)$，整体判断相等 $O(n)$，相比线段树更快。接下来我们讨论一下哪些问题可以用 ST 表区间 $O(1)$ 查询。

1. 最值。ST 表在查询时会用两个有相交部分的区间的答案结合起来，变成这个区间的答案，最值显然是可以的。
2. $\gcd$。最大公约数在多个数运算的时候，有重复部分是对答案没有影响的。
3. 其它 **运算时允许有重复部分** 的问题。

$\text{Part\ 3}$ 利用单调性

引理：当 $k=x$ 满足条件时，$k=x+1$ 也是满足条件的。

回归原来的题意，相等时再进行一次操作，显然也是相等的。利用这个就可以愉快地二分答案了。

注意：$k$ 的上界是 $n$，不用我说了吧。

$\text{Part\ 4}$ 算法总结

首先我们用 ST 表预处理，复杂度 $O(n \log_2 n)$。然后二分 $k$，判断时用 ST 表查询 $n$ 次，判断复杂度 $O(n)$。

总时间复杂度：$O(n \log_2 n)$。 比大多数题解更优。

$\large \text{Code}$

『 $\textsf{Talk is cheap, show you the code.}$ 』

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
#define Maxn 200010 
int t,n,a[Maxn],f[25][Maxn];
int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}
int Query(int L,int R){
	int p=log2(R-L+1);
	return gcd(f[p][L],f[p][R-(1<<p)+1]);
}
bool AreYouOK(){
	for(int i=2;i<=n;i++) if(a[i]!=a[i-1]) return false;
	return true;
}
void Solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),f[0][i]=a[i];
	for(int i=1;i<=log2(n);i++)
		for(int j=1;j<=(n-(1<<i)+1);j++)
			f[i][j]=gcd(f[i-1][j],f[i-1][j+(1<<(i-1))]);
	if(AreYouOK()) {
		puts("0"); return;
	}
	int L=1,R=n,ans;
	while(L<=R){
		int mid=L+R>>1;
		for(int i=1;i<=n;i++){
			if(i<=n-mid) a[i]=Query(i,i+mid);
			else a[i]=gcd(Query(i,n),Query(1,i+mid-n));
		}
		if(AreYouOK()) ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef FILEIO
	freopen("CF1547F.in","r",stdin);
	freopen("CF1547F.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--) Solve();
	return 0;
}
```

---

## 作者：AK_400 (赞：1)

首先注意到做 $k$ 次操作后 $\gcd(a_i,a_{i+1},\cdots,a_{i+k})\to a_i$（令 $a_{i+n}=a_i$，下同）。

这里给出证明：

当 $k=0$ 时，显然成立。

设 $k=x-1$ 时成立，当 $k=x$ 时，有

$$
\begin{aligned} a_i&=\gcd(\gcd(a_i,a_{i+1},\cdots,a_{i+k}),\gcd(a_{i+1},a_{i+2},\cdots,a_{i+k+1}))\\
&=\gcd(a_i,a_{i+1},\cdots,a_{i+k},a_{i+1},a_{i+2},\cdots,a_{i+k+1})\\
&=\gcd(a_i,\gcd(a_{i+1},a_{i+1}),\gcd(a_{i+2},a_{i+2}),\cdots,\gcd(a_{i+k},a_{i+k}),a_{i+k+1})\\
&=\gcd(a_i,a_{i+1},\cdots,a_{i+k+1})
\end{aligned}
$$

于是如果进行第 $k$ 次之后合法，则有

$$
\forall i\in[0,n-1),\gcd(a_i,a_{i+1},\cdots,a_{i+k})=\gcd(a_{i+1},a_{i+2},\cdots,a_{i+k+1})
$$

注意到如果某次操作之后是合法的，那么再进行一次操作之后也是合法的。

于是可以二分答案，判断部分使用 st 表即可。

因为在第 $n-1$ 次操作之后所有的数都会变成所有数的 $\gcd$，将其设为二分上界即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void read(int &x){
    x=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
}
int n,a[200005],st[400005][19],lg[400005];
int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}
void init(){
    for(int i=1;i<19;i++){
        for(int j=1;j+(1<<i)-1<=n+n;j++){
            st[j][i]=gcd(st[j][i-1],st[j+(1<<i-1)][i-1]);
        }
    }
}
int qu(int l,int r){
    return gcd(st[l][lg[r-l+1]],st[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
}
bool chk(int x){
    for(int i=2;i<=n;i++){
        if(qu(i-1,i+x-1)!=qu(i,i+x))return 0;
    }
    return 1;
}
void slv(){
    read(n);
    for(int i=1;i<=n;i++)read(a[i]),st[i][0]=st[i+n][0]=a[i];
    init();
    int l=0,r=n,mid;
    while(l<r){
        mid=l+r>>1;
        if(chk(mid))r=mid;
        else l=mid+1;
    }
    cout<<l<<endl;
    for(int i=1;i<=n+n;i++)for(int j=0;j<19;j++)st[i][j]=0;
    return;
}   
signed main(){
    for(int i=2;i<=4e5;i++)lg[i]=lg[i>>1]+1;
    int T;cin>>T;while(T--)
    slv();
    return 0;
}
```

---

## 作者：lgx57 (赞：0)

非常简单的一道题（~但是为什么数组开小了呢？~）

首先，看到环上的问题，基本上的思路就是先把他转化成链的情况，注意要开 $2$ 倍空间。

容易发现可以把整个序列的 $\gcd$ 除掉，这样只需要考虑最后全部是 $1$ 的情况。

容易发现以下的事情：

$$\gcd(a_1,a_2) \to b_1$$

$$\gcd(b_1,b_2) \to c_1$$

此时的 $c_1=\gcd(a_1,a_2,a_3)$。

那么这个问题就容易了。由于 $a_i$ 在操作 $k$ 次后会变成 $\gcd(a_i,a_{i+1},\cdots,a_{i+k-1})$（此处已断环成链），所以只需要找到最长的连续子串，使得它的 $gcd$ 不为 $1$ 即可。

只需要维护 st 表，然后枚举左端点二分即可。

时间复杂度：$O(n\log^2 n )$


```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+5;
int a[N],n;
int b[N<<1];
int st[N<<1][30];//数组开 2 倍。
void init(){
	int p=log2(n);
	for (int i=1;i<=n;i++) st[i][0]=b[i];
	for (int k=1;k<=p;k++){
		for (int i=1;i+(1<<k)<=n+1;i++){
			st[i][k]=__gcd(st[i][k-1],st[i+(1<<(k-1))][k-1]);
		}
	}
}
int query(int l,int r){
	int p=log2(r-l+1);
	return __gcd(st[l][p],st[r-(1<<p)+1][p]);
}
void sol(){
	cin>>n;
	int g=0;
	for (int i=1;i<=n;i++) cin>>a[i],g=__gcd(g,a[i]);
	for (int i=1;i<=n;i++) a[i]/=g;
	for (int i=1;i<=n;i++) b[i]=b[n+i]=a[i];//断环成链
	n<<=1;//注意是 2 倍
	init();
//	for (int i=1;i<=n;i++) cout<<b[i]<<" \n"[i==n];
	int ans=0;
	for (int i=1;i<=n/2+1;i++){
		int l=i,r=n/2+i-1,Ans=0;
		while (l<=r){
			int mid=(l+r)>>1;
			if (query(i,mid)!=1) l=mid+1,Ans=mid;
			else r=mid-1;
		}
		if (!Ans) continue;
//		cout<<"??? "<<i<<' '<<Ans<<endl;
		ans=max(ans,Ans-i+1);
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while (t--) sol();
	return 0;
}
```

---

## 作者：oymz (赞：0)

# 题面

给定序列 $a$ 长度为 $n$。

每次操作把 $a_i$ 变成 $ \gcd(a_i, a_{(i + 1) \ mod \ n}) $ 且 $1 ≤ i ≤ n$。

求何时序列元素唯一。

## 数据范围
$ 1\leq T \leq 10^4 $

$2 \sum n ≤ 2⋅10^5$

$1 ≤ a_i ≤ 10^6$

# 性质

通过[模拟操作](https://www.luogu.com.cn/paste/eg3hmt4f)可知：

- 在每一轮操作中每一个元素都是一个**区间右端点扩展**的 $gcd$**区间**。

- [操作次数最多为 $n - 1$ ](https://www.luogu.com.cn/paste/737c0gxn)。

# 思路

如果暴力模拟操作那么时间复杂度将会是 $O(n^2)$ 的。

通过观察数据范围和[模拟操作](https://www.luogu.com.cn/paste/eg3hmt4f)可以发现这题需要**区间静态查询**优化。

由于此时可以快速查询**任意元素在任意操作中的值**便可以使用**二分答案**优化。

# Code


```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5, L = 32;//Note_L

int n, t;
int a[N], f[N][L], log_2[N];

int Gcd(int a, int b){///Note_Gcd()
  return !b ? a : Gcd(b, a % b);
}

void Init(){///Note_Init()
  for(int i = 2; i <= n; i++){
    log_2[i] = log_2[i >> 1] + 1;///Note_log_2[]
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < L; j++){
      f[i][j] = 0;
    }
  }
  for(int i = 0; i < n; i++){
    f[i][0] = a[i];
  }
}

void ST(){///Note_ST()_0
  for(int i = 1; i < L; i++){
    for(int j = 0; j < n; j++){
      f[j][i] = Gcd(f[j][i - 1], f[(j + (1 << (i - 1))) % n][i - 1]);///Note_ST()_1
    }
  }
}

int Query(int x, int len){
  int k = log_2[len];
  return Gcd(f[x][k], f[(x + len - (1 << k)) % n][k]);///Note_Query()
}

int Check(int len){///Note_Check()
  int sum = Query(0, len);
  for(int i = 0; i < n; i++){
    if(Query(i, len) != sum){
      return 0;
    }
  }
  return 1;
}

int Search(){///Note_Search()
  int l = 0, r = n;
  while(l < r){
    int mid = (l + r) >> 1;
    if(Check(mid + 1)){
      r = mid;
    }else{
      l = mid + 1;
    }
  }
  return l;
}

void Solve(){
  cin >> n;
  for(int i = 0; i < n; i++){
    cin >> a[i];
  }
  Init();
  ST();
  cout << Search() << '\n';
}

int main(){
  cin >> t;
  while(t--){
    Solve();
  }
  return 0;
}
/**
Note_L{
  Log_2 2e5
  
	即最大的分段等级
	
	|————————————————————————————|最大等级
	|——————————————|
	|————————|
	|———|
	|—|最小等级
}

Note_Gcd(){
  最大公因数
}

Note_Init(){
  初始化

  初始化log_2[]
  ///
  清空
  ///
  初始化f[][] 如果不进行操作则元素i为元素i
}

Note_log_2[]{
  log_2[i] 表示 log_2 i
}

Note_ST()_0{
  基于倍增思想的区间静态查询
  f[i][j] 表示 元素i在进行了2^j次操作后的值
}

Note_ST()_1{
  可以看做是一种类似于DP转移的操作

  |—————————————————————————————————|
  f[j][i] = gcd(f[j][i - 1], f[(j + (1 << (i - 1))) % n][i - 1])
  |————————————————|————————————————|
  f[j][i - 1]      f[(j + (1 << (i - 1))) % n][i - 1]
}

Note_Query(){
  |—————————————————————————————————|
  (x)                               (x + len - 1)
  Query(x, len) = Gcd(f[x][log_2[len]], f[(x + len - (1 << log_2[len])) % n][log_2[len]])
  |——————————————————————|
  f[x][log_2[len]]
             |——————————————————————|
             f[(x + len - (1 << log_2[len])) % n][log_2[len]]
}

Note_Search(){
  二分答案
}

Note_Check(){
  二分检查函数
}
*/
```

---

## 作者：JOKER_chu (赞：0)

## ~~Cross Fire~~ CF1547F 参战记录

### 题意

给出一个长度为 $n$，元素为 $a_0 \dots a_{n - 1}$ 的数组 $a$。

每次操作都需要对数组进行以下的变化：

对于每个满足 $0 \leq i < n$ 的 $i$，将 $a_i$ 变化为 $\gcd(a_i, a_{i + 1 \bmod n})$。

求出最少的操作次数使得 $a$ 数组所有元素相等。

### 思路：

我们看一下变化过程：

对于每个满足 $0 \leq i < n$ 的 $i$，$a_i$ 在第 $m$ 次操作之后会变为 $\gcd(a_i, a_{i + 1 \bmod n} \dots a_{i + m \bmod n})$。

我们要追求的是最小的 $m$，发现一个性质，每个 $a_i$ 在第 $n$ 此操作后一定会相等。因为任何满足 $0 \leq i < n$ 的 $a_i$ 在与 $a$ 数组其他数做运算后都会是 $\gcd(a_1,a_2,\dots,a_n)$。于是我们发现，一定存在一个数 $m$ 使得操作 $m$ 轮之后无论再进行多少次操作，$a$ 数组都不会变化了。这个性质十分显然，当所有 $a_i$ 相等时，$\gcd(a_1 \dots a_n)$ 显然不会变化。

于是想到二分 $m$，确定最小的 $m$ 使得所有 $a_i$ 相等，因为这个答案存在一个**单调性**：当你求得的 $m$ 使得答案成立时，最小的答案一定 $\leq m$，所以使用二分。

求区间 $\gcd$ 有多种方法，这里使用 ST 表实现。因为最大公因数运算具有结合律。所以我们才可以使用 ST 表维护区间 $\gcd$。

### 时间复杂度

预处理 ST 表 $O(n \log n)$。

二分 $O(n \log n)$。

各种奇奇怪怪的初始化 $O(n)$。

每组数据总时间 $O(n \log n)$。

### 代码

马蜂奇特

```cpp
#include <iostream>

#define endl '\n' // 不会超时

using namespace std;

const int N = 4e5 + 5, Log = 2e1 + 5;

int t, n, m, l, r, a[N], st[Log][N], ans[N];

int gcd(int a, int b){
  return !b ? a : gcd(b, a % b);
}

int query(int x, int y){ //  ST 表查询
  int ret = a[x];
  for(int i = 20, le = y - x + 1; i >= 0; --i){
    if(( le >> i & 1 ) == 1){
      ret = gcd(ret, st[i][x]);
      x += ( 1 << i );
    }
    // cout << x << " " << i << endl;
  }
  return ret;
}

bool function1(int x){ // 检查答案是否可行
  bool ret = 0;
  // cout << x << endl;
  for(int i = 1; i <= n; ++i){
    ret |= ans[i] != query(i, i + x); // 区间 gcd
    // cout << i << " " << i + x << " " << query(i, i + x) << endl;
  }
  // cout << ret << endl;
  return ret ^ 1;
}

int main(){
  ios :: sync_with_stdio(0), cin.tie(0);
  cin >> t;
  while(t--){
    cin >> n;
    for(int i = 1; i <= n; cin >> a[i++]);
    for(int i = 1; i <= n; ++i) a[i + n] = a[i]; // 将数组断环成链，减少取模细节
    for(int i = 1; i <= ( n << 1 ); ++i){
      st[0][i] = a[i];
    }
    for(int i = 1; i <= 20; ++i){ // ST 表
      for(int j = 1; j <= ( n << 1 ) - ( 1 << i - 1 ); j++){
        st[i][j] = gcd(st[i - 1][j], st[i - 1][j + ( 1 << i - 1 )]);
      }
    }
    for(int i = 1; i <= n; ++i){
      ans[i] = query(1, n);
    }
    int l = 0, r = n + 1;
    while(l < r){ // 二分
      int mid = (l + r) >> 1;
      if(function1(mid) == 1){
        r = mid;
      }else{
        l = mid + 1;
      }
    }
    cout << l << endl;
  }
  return 0;
}

```

完结撒花！！！

---

## 作者：__LZH__ (赞：0)

#  CF1547F Array Stabilization (GCD version)

# 题意

有一个长度为 $n$ 的数组 $a$，通过一次操作可得 $b$ 数组，其中：$b_i = \gcd(a_i, a_{(i + 1) \% n} )$，操作后将 $b$ 数组再赋到 $a$ 上。求最少要多少次操作可将 $a$ 数组所有元素变为相同。

# 思路

可以看到，做 $k$ 次操作其实就相当于以每个下标为起点求长度为 $k + 1$ 的区间中所有元素的最大公因数，区间最大公因数可以用ST表（此题满足幂等律，不懂的可以看[这里](https://oi-wiki.org//ds/sparse-table/)）来 $O(1)$ 求解。由于操作越多越能达到条件，所以满足单调性，可以二分。

# 时空复杂度

时间：预处理ST表 $O(n \log n)$，二分 $O(n \log n)$，总时间 $O(n \log n)$。

空间：ST表存储 $O(n \log n)$，预处理 $\log$ 为 $O(n)$。

code：

```cpp
#include<bits/stdc++.h>

using namespace std;

int gcd(int a, int b){
  return (!b) ? a : gcd(b, a % b);
}

int T, n, f[35][400010], log2n[400010];

int answer(int x, int y){//求区间GCD
  int k = log2n[y - x + 1];
  return gcd(f[k][x], f[k][y - (1 << k) + 1]);
}

bool check(int x){
  int ans = 0;
  for(int i = 1; i <= n; i++){
    int k = answer(i, i + x);
    if(!ans){
      ans = k;
    }else{
      if(k != ans){
        return 0;
      }
    }
  }
  return 1;
}

void solve(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> f[0][i];
    f[0][i + n] = f[0][i];//复制一段解决循环
  }
  for(int i = 1; i <= 30; i++){//ST表
    for(int j = 1; j + (1 << i) - 1 <= n * 2; j++){
      f[i][j] = gcd(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
    }
  }
  for(int i = 2; i <= n * 2; i++){//O(1)查询的关键
    log2n[i] = log2n[i >> 1] + 1;
  }
  int l = 0, r = n, ans = 0;
  while(l <= r){//二分
    int mid = (l + r) >> 1;
    if(check(mid)){
      r = mid - 1, ans = mid;
    }else{
      l = mid + 1;
    }
  }
  cout << ans << '\n';
}

int main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--){
    solve();
  }
  return 0;
}

```

---

## 作者：lateworker (赞：0)

这题既然能用线段树做，怎么能没有 zkw？~~顺便水一篇 zkw 线段树题解~~

### 思路

题意已经很清楚了。我们先定义 $\gcd(a_1,a_2)=a_1\times a_2$。

- 给定序列 $[a_1,a_2,...,a_n]$，每次操作都会将其变为 $[a_1\times a_2,a_2\times a_3,...,a_n\times a_1]$。

- 对于任意 $x,y,z$，存在 $x\times y\times y\times z=x\times y\times z$。

不难得出，对于每个 $a_i$，在 $k$ 次操作后会变为 $a_i\times a_{i+1}\times ...\times a_{i+k}$，所有元素相同就相当于 $a_i\times a_{i+1}\times ...\times a_{i+k}=1$。

这是一个不用修改的区间查询问题，可以考虑用 **zkw 线段树** 维护区间 $\gcd$。

另外，如果存在 $a_l\times ...\times a_r=1$，必有 $a_l\times ...\times a_{r+1}=1$。可以考虑用 **双指针** 遍历序列，详见代码注释。

### 实现

zkw 线段树是一种非常普信的数据结构，写起来非常简单，网上也有很多介绍，这里不做讲解。注意事项：

- 记得断环成链，数组要开两倍长度，线段树要开八倍长度。

- 在建树维护前要先约去序列的最大公因数。

- 要特判序列中每一项都相等的情况。

接下来是 AC 代码：

**本题解禁止理解性默写!**

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2e5+10;
// 多组数据，写一个namespace防止CE
namespace Main {
    int a[N<<1], n, gcd, ans;
    int st[N<<3], tn; // zkw线段树相关变量
    // 多测清空，要控制清空长度，用memset会T飞
    inline void init() { 
        for(int i=1;i<=n;++i) a[i]=0;
        for(int i=tn;i<=tn+n;++i) st[i]=0; // zkw线段树可以只清底层
        n = gcd = tn = ans = 0;
    }
    #define le (u<<1)
    #define ri (u<<1|1) 
    // 建树
    inline void build() {
        for(tn=1;tn<=n+1;tn<<=1);
        for(int i=1;i<=n;++i) st[tn+i]=a[i];
        for(int u=tn-1;u;--u) st[u]=__gcd(st[le],st[ri]); 
    }
    // 查询 gcd(l->r)
    inline int query(int l, int r) {
        int ret = 0;
        for(l+=tn-1,r+=tn+1;l^r^1;l>>=1,r>>=1) {
            if(~l&1) ret=__gcd(ret, st[l^1]);
            if(r&1) ret=__gcd(ret, st[r^1]);
        }
        return ret;
    }
    // 特判每一项相等的情况，顺便求出 gcd(1->n)
    inline bool check() {
        bool ret = true;
        for(int i=1;i<=n;++i) {
            gcd = __gcd(gcd, a[i]);
            if(a[1]!=a[i]) ret = false;
        }
        return ret;
    }
    // 自定义主函数
    inline int main() {
        cin>>n;
        for(int i=1;i<=n;++i) cin>>a[i];
        if(check()) return 0;
        for(int i=1;i<=n;++i) // 断环成链，约去最大公因数
            a[i]/=gcd, a[i+n]=a[i];
        n<<=1;
        build();
        // 双指针维护答案
        for(int l=1,r=1;r<=n;++r) {
            // 如果 gcd(l->r)=1，尝试缩小范围
            while(l<=r&&query(l,r)==1) ++l; 
            ans = max(ans, r-l+1);
        }
        return ans;
    }
}
int main() {
    ios::sync_with_stdio(0); // 关闭缓冲区，加快读入速度
    int t; cin>>t;
    while(t--) // init多测清空，调用自定义主函数
        Main::init(), cout<<Main::main()<<"\n";
    return 0;
}
```


---

