# [ABC310E] NAND repeatedly

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc310/tasks/abc310_e

`0` と `1` からなる長さ $ N $ の文字列 $ S $ が与えられます。 $ S $ は長さ $ N $ の数列 $ A=(A\ _\ 1,A\ _\ 2,\ldots,A\ _\ N) $ の情報を表しており、$ S $ の $ i $ 文字目 $ (1\leq\ i\leq\ N) $ が `0` のとき $ A\ _\ i=0 $ 、`1` のとき $ A\ _\ i=1 $です。

\\\[\\sum \_ {1\\leq i\\leq j\\leq N}(\\cdots((A \_ i\\barwedge A \_ {i+1})\\barwedge A \_ {i+2})\\barwedge\\cdots\\barwedge A \_ j)\\\]

を求めてください。

より厳密には、次のように定められる $ f(i,j)\ (1\leq\ i\leq\ j\leq\ N) $ に対して $ \displaystyle\sum\ _\ {i=1}\ ^\ {N}\sum\ _\ {j=i}\ ^\ Nf(i,j) $ を求めてください。

\\\[f(i,j)=\\left\\{\\begin{matrix} A \_ i&amp;(i=j)\\\\ f(i,j-1)\\barwedge A \_ j\\quad&amp;(i\\lt j) \\end{matrix}\\right.\\\]

ただし、否定論理積 $ \barwedge $ は次を満たす二項演算子です。

\\\[0\\barwedge0=1,0\\barwedge1=1,1\\barwedge0=1,1\\barwedge1=0\\\]

## 说明/提示

### 制約

- $ 1\leq\ N\leq10^6 $
- $ S $ は `0` と `1` からなる長さ $ N $ の文字列
- 入力はすべて整数
 
### Sample Explanation 1

$ 1\leq\ i\leq\ j\leq\ N $ を満たすすべての組 $ (i,j) $ に対して、$ f(i,j) $ の値は以下のようになります。 - $ f(1,1)=0=0 $ - $ f(1,2)=0\barwedge0=1 $ - $ f(1,3)=(0\barwedge0)\barwedge1=0 $ - $ f(1,4)=((0\barwedge0)\barwedge1)\barwedge1=1 $ - $ f(1,5)=(((0\barwedge0)\barwedge1)\barwedge1)\barwedge0=1 $ - $ f(2,2)=0=0 $ - $ f(2,3)=0\barwedge1=1 $ - $ f(2,4)=(0\barwedge1)\barwedge1=0 $ - $ f(2,5)=((0\barwedge1)\barwedge1)\barwedge0=1 $ - $ f(3,3)=1=1 $ - $ f(3,4)=1\barwedge1=0 $ - $ f(3,5)=(1\barwedge1)\barwedge0=1 $ - $ f(4,4)=1=1 $ - $ f(4,5)=1\barwedge0=1 $ - $ f(5,5)=0=0 $ これらの総和は $ 0+1+0+1+1+0+1+0+1+1+0+1+1+1+0=9 $ なので、$ 9 $ を出力してください。 $ \barwedge $ は結合法則を満たさないことに注意してください。 例えば、$ (1\barwedge1)\barwedge0=0\barwedge0=1\neq0=1\barwedge1=1\barwedge(1\barwedge0) $ です。

## 样例 #1

### 输入

```
5
00110```

### 输出

```
9```

## 样例 #2

### 输入

```
30
101010000100101011010011000010```

### 输出

```
326```

# 题解

## 作者：shinkuu (赞：12)

好像还可以写（？）

因为每一位不是 $0$ 就是 $1$，一共只有 $4$ 种不同转移。考虑从前往后推，记录前面每个 $j$ 到当前位置 $i$ 所对应子串，结果为 $0$ 和 $1$ 的个数。分每种转移计算。记 $cnt$ 为 $1$ 的个数。

- $a_i=0$

即前面所有 $j$ 到该位置子串结果都为 $1$，$[i,i]$ 子串为 $0$。所以 $cnt\leftarrow i-1$。

- $a_i=1$。

即前面所有 $j$ 的结果反转，$0$ 变 $1$，$1$ 变 $0$。$[i,i]$ 结果为 $1$。所以 $cnt\leftarrow i-cnt$。

每个位置执行 $ans\leftarrow ans+cnt$ 统计答案。

核心代码不压行 $5$ 行。rated 首 A。

```cpp
int n,m;
char s[N];
void solve(){
	scanf("%d%s",&n,s+1);
	ll ans=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='1')
			cnt=i-cnt;
		else 
			cnt=i-1;
		ans+=cnt;
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：Coffee_zzz (赞：6)

### 分析

看到 $10^6$ 的范围和看着就很能 dp 的式子，考虑线性 dp。

- 目标：求 $\sum\limits_{i=1}^N\sum\limits_{j=i}^N f(i,j)$ 的值，其中

$$f(i,j)=\begin{cases}
A_i &i=j\\
f(i,j-1)\barwedge A_j &i<j
\end{cases}$$

- 状态定义：定义 dp 数组 $dp_{i,j}\ (1 \le i \le n,j \in\{0,1\})$ 表示 $f(1,i)\sim f(i,i)$ 中 $j$ 的数量，形式化地，$dp_{i,j}=\sum\limits^i_{k=1} [j=f(k,i)]$。

- 初始状态：如果 $A_1=0$，则说明 $f(1,1)=0$，$dp_{i,0}=1$；如果 $A_1=1$，则说明 $f(1,1)=1$，$dp_{i,1}=1$。

- 状态转移：我们分 $A_i=0$ 和 $A_i=1$ 两类去考虑。 

  - 如果 $A_i=0$，则根据 $0\barwedge0=1,1\barwedge0=1$ 可以知道，上一位的 $0$ 转移到这位会变成 $1$，上一位的 $1$ 转移到这位还是 $1$。同时，还要考虑新增的 $f(i,i)$，此时 $f(i,i)=A_i=0$。所以 $dp_{i,0}=1$，$dp_{i,1}=dp_{i-1,0}+dp_{i-1,1}$。

  - 如果 $A_i=1$，则根据 $0\barwedge1=1,1\barwedge1=0$ 可以知道，上一位的 $0$ 转移到这位会变成 $1$，上一位的 $1$ 转移到这位会变成 $0$。同时，也要考虑新增的 $f(i,i)$，此时 $f(i,i)=A_i=1$。所以 $dp_{i,0}=dp_{i-1,1}$，$dp_{i,1}=dp_{i-1,0}+1$。

  综上所述，转移方程为：

$$
dp_{i,0}=\begin{cases}
1 & A_i=0\\
dp_{i-1,1} & A_i=1\\
\end{cases}
$$
$$
dp_{i,1}=\begin{cases}
dp_{i-1,0}+dp_{i-1,1} & A_i=0\\
dp_{i-1,0}+1 & A_i=1\\
\end{cases}
$$
                           
- 最终答案：我们要求的是 $\sum\limits_{i=1}^N\sum\limits_{j=i}^N f(i,j)$，根据 dp 数组的定义可以知道 $\sum\limits_{i=1}^N\sum\limits_{j=i}^N f(i,j)=\sum\limits_{i=1}^N dp_{i,1}$，即 $dp_{1,1}+dp_{2,1}+dp_{3,1}+\cdots+dp_{N,1}$。
                           
### 代码
                           
```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],dp[N][2];
signed main(){
	int n,ans=0;
	string s;
	cin>>n>>s;
	for(int i=1;i<=n;i++) a[i]=s[i-1]-'0';
	if(a[1]==0) dp[1][0]=1;
	else dp[1][1]=1;
	for(int i=2;i<=n;i++){
		if(a[i]==0){
			dp[i][1]=dp[i-1][0]+dp[i-1][1];
			dp[i][0]=1;
		}
		else{
			dp[i][1]=dp[i-1][0]+1;
			dp[i][0]=dp[i-1][1];
		}
	}
	for(int i=1;i<=n;i++) ans=ans+dp[i][1];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_Richardguo_ (赞：5)

我们先来看一下样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/6ys60ako.png)

我们把第 $i$ 行第 $j$ 个数表示为 $f(i,j)$ 其中：

$ f(i,j) = \begin{cases} A_i &\ (i = j) \\ f(i,j-1) \barwedge A_j &\ (i \lt j) \end{cases}$


答案就是倒三角中 $1$ 的个数。

## 思路
对于图中每一列计算 $0$ 和 $1$ 的个数，分情况讨论：
1. 如果当前输入进来的数是 $0$ 我们发现：
	1. 当前这列 $0$ 的个数 $=1$ 。
	2. 当前这列 $1$ 的个数 $=$ 上一列$0$的个数 $+$ 上一列 $1$ 的个数。
2. 如果当前输入进来的数是 $1$ 我们发现：
	1. 当前这列 $0$ 的个数 $=$ 上一列 $1$ 的个数。
	2. 当前这列 $1$ 的个数 $=$ 上一列 $0$ 的个数 $+1$ 。
    
于是我们用两个计数器： $cnt0$ 和 $cnt1$ 来执行以上操作。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	ll cnt0=0,cnt1=0,ans=0;
	for(int i=1;i<=n;i++){
		char s;cin>>s;
		if(s=='0'){
			cnt1+=cnt0;
			cnt0=1;
		}
		else swap(cnt0,cnt1),cnt1++;
		ans+=cnt1;
	} 
	cout<<ans<<"\n";
	return 0;
}


```
    

---

## 作者：mRXxy0o0 (赞：4)

一种极其无脑全是套路的做法~~（绝对不是因为没想到正解）~~。

关注到要求出每一个区间的值，我们可以迅速联想到从小到大枚举右端点，同时维护前面所有以这个点为右端点的区间值。

根据一般套路，大致发现线段树可以做到这一点。

观察题目给出的变换规律，可以发现：新增一个 $0$ 等同于赋值为 $1$；新增一个 $1$ 等同于取反。

这两个操作都可以很好的用线段树实现。

具体地，从小到大枚举右端点，同时维护每个左端点到这里的值，新增左端点时等同于区间操作，查询也是区间求和。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=1e6+10;
int n;
ll ans;
char a[N];
struct node{
	int l,r,sum1,sum0,laz1,laz2;
}tr[N<<2];
inline void pushup(int u){
	tr[u].sum0=tr[u<<1].sum0+tr[u<<1|1].sum0;
	tr[u].sum1=tr[u<<1].sum1+tr[u<<1|1].sum1;
}
inline void pushdown(int u){
	if(tr[u].laz1){
		swap(tr[u<<1].sum0,tr[u<<1].sum1);
		swap(tr[u<<1|1].sum0,tr[u<<1|1].sum1);
		tr[u<<1].laz1^=1;
		tr[u<<1|1].laz1^=1;
		if(~tr[u].laz2) tr[u].laz2^=1;
		tr[u].laz1=0;
	}
	if(~tr[u].laz2){
		if(tr[u].laz2){
			tr[u<<1].sum0=tr[u<<1|1].sum0=0;
			tr[u<<1].sum1=tr[u<<1].r-tr[u<<1].l+1;
			tr[u<<1|1].sum1=tr[u<<1|1].r-tr[u<<1|1].l+1;
		}
		else{
			tr[u<<1].sum1=tr[u<<1|1].sum1=0;
			tr[u<<1].sum0=tr[u<<1].r-tr[u<<1].l+1;
			tr[u<<1|1].sum0=tr[u<<1|1].r-tr[u<<1|1].l+1;
		}
		tr[u<<1].laz1=tr[u<<1|1].laz1=0;
		tr[u<<1].laz2=tr[u<<1|1].laz2=tr[u].laz2;
		tr[u].laz2=-1;
	}
}
inline void build(int u,int l,int r){
	tr[u]={l,r,0,0,0,-1};
	if(l==r) return ;
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
inline void mdf(int u,int l,int r,int k){
	if(l<=tr[u].l&&tr[u].r<=r){
		if(k){
			swap(tr[u].sum0,tr[u].sum1);
			tr[u].laz1^=1;
		}
		else{
			tr[u].sum0=0;
			tr[u].sum1=tr[u].r-tr[u].l+1;
			tr[u].laz1=0;
			tr[u].laz2=1;
		}
		return ;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) mdf(u<<1,l,r,k);
	if(r>mid) mdf(u<<1|1,l,r,k);
	pushup(u);
}
inline void add(int u,int x,int v){
	if(tr[u].l==tr[u].r){
		tr[u].sum0=(v==0);
		tr[u].sum1=(v==1);
		return ;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(x<=mid) add(u<<1,x,v);
	else add(u<<1|1,x,v);
	pushup(u);
}
inline int query(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].sum1;
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1,res=0;
	if(l<=mid) res+=query(u<<1,l,r);
	if(r>mid) res+=query(u<<1|1,l,r);
	return res;
}
int main(){
	scanf("%d%s",&n,a+1);
	build(1,1,n);
	for(int i=1;i<=n;++i){
		if(i>1){
			mdf(1,1,i-1,a[i]^48);
		}
		add(1,i,a[i]^48);
		ans+=query(1,1,i);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Phartial (赞：2)

怎么都是 dp 做的，就我是手玩出来的吗/oh。

首先关于 $\operatorname{NAND}$ 有一个经典技巧：$x\barwedge 0=1,x\barwedge 1=\neg x$。

发现一个 $0$ 会将值强制置 $1$，而一个 $1$ 会将值取反，于是 $f(l,r)$ 的值只取决于区间内最后一个 $0$ 后 $1$ 的数量。

注意到 $n$ 个 $1$ 依次 $\operatorname{NAND}$ 的值为 $n\bmod 2$。

考虑枚举 $r$，对 $S_r$ 分类讨论：

- 若 $S_r=\mathtt{0}$：那么对所有 $l\in[1,r)$，不管前面得到了什么值，最后 $x\barwedge S_r$ 都能得到 $1$，于是贡献为 $r-1$。注意 $l=r$ 时 $f(r,r)=0$，没有贡献；
- 若 $S_r=\mathtt{1}$：考虑维护连续 $1$ 的个数，记作 $c$。那么每出现一个 $1$，得到的值会取反，所以有：
  - 在 $l\in(r-c,r]$ 中，$1,0$ 交替出现，贡献为 $\lceil\frac{c}{2}\rceil$；
  - 对于 $l=r-c$，由于 $0\barwedge 1=1$，所以 $f(l,r)$ 即为 $c$ 个 $1$ 依次 $\operatorname{NAND}$ 的值，即 $c\bmod 2$；
  - 对于 $l\in[1,r-c)$，由于位于 $S_{r-c}$ 的 $0$ 总能将前面的值变成 $1$，所以 $f(l,r)$ 为 $c+1$ 个 $1$ 依次 $\operatorname{NAND}$ 的值，即 $(c+1)\bmod 2$，总贡献为 $((c+1)\bmod 2)\times(r-c-1)$。

$c$ 的维护是 trival 的，于是我们就能在 $\mathcal{O}(n)$ 的时间内求出答案了。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

int n;
LL ans;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int r = 1, c = 0; r <= n; ++r) {
    char ch;
    cin >> ch;
    if (ch == '0') {
      c = 0;
      ans += r - 1;
    } else {
      ++c;
      ans += (c + 1) / 2;
      if (r > c) {  // 判断 r-c 是否存在
        ans += c & 1;
        ans += (c + 1 & 1) * (r - c - 1);
      }
    }
  }
  cout << ans;
  return 0;
}
```


---

## 作者：incra (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc310_e)
### 前言
看到 F 题可做，就没看 E 题，结果 F 题拍错了，赛后看了一眼 E 题，才发现那么水，以后要注意做题策略。
### 题解
设 $one$ 为以 $i$ 为结尾的所有区间中，NAND 和为 $1$ 的数量，$zero$ 以 $i$ 为结尾的所有区间中，NAND 和为 $0$ 的数量。

若当前数为 $1$，那么所有以 $0$ 为 NAND 和的区间的 NAND 和都变为 $1$，以 $1$ 为 NAND 和的区间的 NAND 和都变为 $0$，同时还有区间 $[i,i]$ 的 $1$，故变化方式为 $one=zero,zero=one+1$（注意，这个是要同时进行的，即赋值时要用原来的值进行计算）。

剩下的当前数为 $0$ 的情况，请读者自行推导。
### 代码
```cpp
#include <iostream>
using namespace std;
typedef long long LL;
int n;
int main () {
	LL ans = 0;
	int zero = 0,one = 0;
	cin >> n;
	for (int i = 1;i <= n;i++) {
		char x;
		cin >> x;
		if (x == '0') one += zero,zero = 1;
		else swap (zero,one),one++;
		ans += one;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：0000pnc (赞：2)

为什么都是 dp 做的。

手玩发现，一个序列的与非和为 $0$，当且仅当这个序列满足以下 $3$ 种情况任意一种：

* $\{0\underbrace{11\cdots 1}_{2k}\}$，$k \ge 0$

* $\{\underbrace{\cdots 0}_{\gt 1}\underbrace{11\cdots 1}_{2k+1}\}$，$k\ge 0$

* $\{\underbrace{11\cdots 1}_{2k}\}$，$k \ge 1$

对于每个 $1$ 的连通块，计算其贡献即可。

[Submission](https://www.luogu.com.cn/record/115912211)

---

## 作者：fcy20180201 (赞：1)

## 题意
给定长度为 $N$ 的 $01$ 串 $A$，求 $\sum^{n}_{1 \le i \le j \le N}      (((A_i ⊼A_{i+1})⊼ A_{i+2})⊼ \cdots⊼A_j)$。


其中 $⊼$ 为双目逻辑运算符， $0 ⊼ 0=1,1⊼0=1,0⊼1=1,1⊼1=0$。
## 做法
这题的 NAND 运算不满足结合律，我好像只想到能用 dp 做......

题目要求的其实是有多少个 ${i,j}(i \le j)$ 满足 $(((A_i ⊼A_{i+1})⊼ A_{i+2})⊼ \cdots⊼A_j)=1$，把问题转化成计数问题。我们又发现，一段运算的值只能是 $0$ 或 $1$，乘上 $A$ 的长度也不会爆掉，就能想到 dp。
### 定义
$dp_{i,j}$ 表示以结尾为 $i$，值为 $j$ 的 $(((A_x ⊼A_{x+1})⊼ A_{x+2})⊼ \cdots⊼A_i)$ 有多少个。
### 转移
- 当 $A_i=0 \space\space\space dp_{i,0}=1 \space\space\space$ 因为一段运算里只要有 $0$，结果就为 $1$，除非这个 $0$ 没有与其他任何数做运算。
- 当 $A_i=1 \space\space\space dp_{i,0}=dp_{i-1,1}\space\space\space$ 因为 $1$ 只有和 $1$ 做运算才是 $0$。
 
- 当 $ A_i=0\space\space\space dp_{i,1}=dp_{i-1,0}+dp_{i-1,1}\space\space\space$ 因为 $0$ 只要和别的数做运算，结果一定是 $1$。
- 当 $A_i=1\space\space\space dp_{i,1}=dp_{i-1,0}+1 \space\space\space$ 因为 $1$ 只有和 $0$ 做运算时才得 $1$，或不与任何数做计算也是 $1$。

### 初始化
将 $dp_{0,0}$ 和 $dp_{0,1}$ 初始化为 $0$。乘法算式得初始值为 $1$ 因为 $1$ 乘上任何数都为另一个乘数，但 $⊼$ 运算没有这个性质，因此两种值的初始个数都为 $0$。
### 统计答案
由于 $dp_{i,1}$ 的定义是以第 $i$ 位结尾的结果为 $1$ 的式子 $\sum_{i=0}^{n} dp_{i,1}$ 即可。
## 代码核心部分
```cpp
	for(int i=1;i<=n;i++){
		dp[i][0]=(b[i]?dp[i-1][1]:1ll);
		dp[i][1]=(b[i]?dp[i-1][0]+1:dp[i-1][0]+dp[i-1][1]);		
	}
	for(int i=1;i<=n;i++)ans+=dp[i][1];
```


---

## 作者：Genius_Star (赞：1)

### 题意：
给出一个长度为 $ N $ 的，仅包含 $ 0 $ 和 $ 1 $ 的字符串 $ S $ ，其中， $ S $ 的第 $ i $ 位表示 $ A_i $ 的值。

请求出以下式子的值：

$$\displaystyle \sum_{ 1 \leq i \leq j \leq N } (\cdots((A_i\barwedge A_{i+1})\barwedge A_{i+2})\barwedge\cdots\barwedge A_j)$$

### 思路：

直接按照题意 $f_{i,j}$ 暴力的话时间复杂度是 $O(N^2)$ 的，但是因为 $N$ 的最大值为一百万，只能考虑 $O(N)$ 或者 $O(N \log N)$ 的做法。

考虑以第 $i$ 个数结尾的贡献，发现，如果 $A_i$ 是 $0$ 的话，前面的无论怎么算过来，和 $0$ 进行 $\barwedge$ 运算结果都是 $1$，所以对于以 $0$ 结尾的第 $i$ 个数，所产生的答案是 $i-1$（因为如果 $i=j$，贡献为 $A_i$）。

那么如果 $A_i$ 是 $1$ 呢？我们先观察一下，对于第一个 $1$，他的前面全部都是 $0$，计算到 $i-1$ 的结果肯定是 $1$，而 $1 \barwedge 1=1$，然后发现如果从 $i-1$ 开始算的话 $1\barwedge0=1$，又有一个贡献，所以对于第一个 $1$ 他的答案是 $2$（还有自己本身）。

如果不是第一个 $1$，但是 $i-1$ 的位置是 $0$，到达 $i-1$ 的时候计算到的结果只有 $1$，加上 $i-1$ 和自己进行的 $\barwedge$，所以答案也是 $2$。

若是对于多个连着的 $1$ 呢？发现对于连着的 $1$，最前面的 $1$ 的前面肯定是 $0$，所以对于第一个连着的 $1$，答案是 $2$，这是我们前面推出来的结论。

那么第二个 $1$ 呢？发现在和第一个 $1$ 进行 $\barwedge$ 肯定变成了 $0$，然后和自己 $\barwedge$，贡献为 $1$，总共产生的答案为 $i-2$，为什么不是 $i-1$ 呢？因为 $A_i \barwedge A_{i-1}=0$，所以要减少一个贡献。

对于第三个 $1$ 呢？我们发现，对于连着的 $1$，我们都需要用前面的答案和自己做 $\barwedge$ 运算，发现前面是 $0$，和自己做 $\barwedge$ 运算是 $1$，前面是 $1$，做 $\barwedge$ 运算的答案是 $0$。

诶，这不就取反了吗？所以对于连着的 $1$，除了第一个以外，其他的都等于 $i-k$，$k$ 为上一个数的答案，这样我们可以写出简短的代码。
### 完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,sum; 
string s;
signed main(){
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++){
		int x=i,y=s[i]-'0';
		if(y){
			a=x-a;
//			cout<<a<<' '<<y<<' '<<a+y<<'\n';
			sum+=a+y;
			a+=y;
		}
		else{
			a=x;
//			cout<<a<<' '<<y<<' '<<a+y<<'\n';
			sum+=a+y;
		}
	}
	cout<<sum<<endl;
    return 0;
}
```


---

## 作者：wizardMarshall (赞：1)

由于 $\LaTeX$ 格式原因，题意中的特殊操作用 $\oplus$ 表示。

## 题意

求

$$\displaystyle \sum_{1\le i \le j \le n}(\dots(a_{i}\oplus a_{i+1}) \oplus a_{i+2}) \oplus \dots \oplus a_j)$$

其中，$\oplus$ 运算为一种布尔运算。

$0 \oplus 0 = 1,0 \oplus 1 = 1, 1 \oplus 0 = 1,1\oplus1=0$

-----

## 思路

对于每一组 $i,j$，其实就是求一段区间内连续的数做运算得出的结果。我们考虑枚举 $j$，计算以 $j$ 结尾的区间运算值。

可以记录 $c_0$ 与 $c_1$，分别表示**从之前某一点开始至当前区间的运算结果**为 $0$ 或为 $1$ 的区间个数。

由于运算是从前往后做，做到某一个值的时候不关心之前的值，只关心之前的结果，因此可以线性递推。

问题就转变成了如何在每一次循环结束的时候根据 $a_i$ 改变 $c_0$ 与 $c_1$。我们分类讨论。

如果 $a_i$ 是 $0$，原先为 $0$ 的变成了 $1$，原先为 $1$ 的还是 $1$。$c_1=c_0+c_1$。

如果 $a_i$ 是 $1$，原先为 $0$ 的变成了 $1$，原先为 $1$ 变成了 $0$。交换 $c_0$ 与 $c_1$。

可以借助代码理解一下。时间复杂度 $O(n)$。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005];
int str(int x, int y) {//操作
	if (!x || !y) {
		return 1;
	}return 0;
}
signed main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
		scanf("%1lld", &a[i]);
	}int c0 = 0, c1 = 0;//记录结果个数
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += a[i];//当前只有一个点的区间也要算上
		ans += c0 * str(0, a[i]);//之前区间结果是0，对ai做操作后的结果乘上c0
		ans += c1 * str(1, a[i]);//c1同理
		if (a[i] == 0) {//改变c0与c1
			c1 = c0 + c1;
			c0 = 0;
		}else {
			swap(c0, c1);
		}
		if (a[i] == 0) {//新加一个i为左端点的区间
			c0++;
		}else {
			c1++;
		}
	}cout << ans;
    return 0;
}/*
*/

```

---

## 作者：_sunkuangzheng_ (赞：1)

**【题目分析】**

仔细阅读题目中关于 $\barwedge$ 运算的定义，发现**只要参与运算的数字有 $0$，答案一定为 $1$**。因此我们先统计每一个数字后面 $0$ 的个数，从后往前遍历时加上答案。

再去考虑 $1$ 对答案的贡献。我们观察每一个连续的由 $0,1$ 组成的子段，计算它的贡献。以下黑色部分表示答案为 $0$，蓝色表示答案为 $1$。

$$0\color{blue}{0}\color{black}{1}\color{blue}{1}\color{b}{1}\color{blue}{1}\color{b}{1}\color{blue}{0}\color{blue}{0}$$

发现每 $2$ 个连续的数字 $1$ 对答案会有 $1$ 的贡献，且贡献的位置在后面。即，设连续的 $1$ 有 $k$ 个，对答案的贡献是 $\lfloor \dfrac{k}{2} \rfloor$。

可是还有一种特殊情况：当前位置是 $0$，后面有连续 $k$ 个 $1$。因为这个 $0$ 对答案的贡献是 $0$，所以此时后面连续 $k$ 个 $1$ 的贡献是 $\lceil \dfrac{k}{2} \rceil$，因为 $1$ 贡献的位置在前面。

注意本题要开 `long long`（考虑 $10^6$ 个 $0$）。至此代码就很好写了，只有 $9$ 行哦。

**【代码】**

```cpp
#include <bits/stdc++.h>
long long n,cnt0,ans,cnt1,sum;std::string s;
int main(){
    std::cin >> n >> s;
    for(int i = n-1;i >= 0;i --)
        if(s[i] == '0') sum += cnt1 / 2,ans += (cnt0 ++) + sum + ((cnt1 % 2 == 1) && s[i+1] == '1'),cnt1 = 0;
        else cnt1 ++,ans += cnt0 + sum + (cnt1-1) / 2 + 1;
    return std::cout << ans,0;
}
```

---

## 作者：Jasper08 (赞：0)

考虑枚举 $j$。显然 $A_j=0$ 时，$\forall 1\le i<j,f(i,j)=1$。那么 $j$ 对答案的贡献为 $j-1$。

$A_j=1$ 时，我们记上一个 $0$ 出现的位置为 $last$，则 $A_j$ 前有 $j-last$ 个连续的 $1$。

- $last<i\le j$：显然奇数个 $1$ 依次 NAND 的结果为 $1$，偶数个 $1$ 依次 NAND 的结果为 $0$。那么这些连续的 $1$ 对答案的贡献为 $\left\lceil \dfrac{j-last}{2} \right\rceil$。
- $i=last$：由于 $0\overline{ \wedge }1=1$，所以此时 $last$ 对答案的贡献取决于 $j-last$ 是否为奇数，若为奇数则其对答案的贡献为 $1$，否则为 $0$。
- $1\le i<last$：此时 $f(i,last)=1$，那么会产生 $j-last+1$ 个连续的 $1$，若其为奇数则其对答案的贡献为 $last-1$，否则为 $0$。

将这三部分加起来即可。注意特判 $last=0$ 即 $0$ 还未出现的情况。

时间复杂度 $O(n)$。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1e6+10;

int n, last, a[N]; ll ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%1d", &a[i]);

    for (int i = 1; i <= n; ++i) {
        if (!a[i]) ans += i-1, last = i;
        else {
            int len = i-last;
            ans += (len+1)/2 + (last>0)*(len&1) + (last>0)*(len+1&1)*(last-1);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

一个比较简单的 dp 题。

定义 $F_i$ 表示 $\sum_{j=1}^i f(j,i)$ 的值。

当 $S_i=0$ 时，$f(j,i)=1$ 当且仅当 $j \ne i$，所以 $F_i=i-1$。

当 $S_i=1$ 时，$f(j,i)=1$ 当且仅当 $f(j,i-1)=0$，所以 $F_i=i-F_{i-1}$。

最后只需要输出 $\sum_{i=1}^n F_i$ 就可以了。

时间复杂度 $O(N)$，代码长度比前三个题还短。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long dp[1000005];
int main(){
	int n;
	scanf("%d",&n);
	string s;
	cin>>s;
	long long ans=0;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='0') dp[i]=i-1;
		else dp[i]=i-dp[i-1];
		ans+=dp[i];
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：best_brain (赞：0)

$\qquad$[原题面](https://atcoder.jp/contests/abc310/tasks/abc310_e)

$\qquad$一眼看上去：好麻烦啊，要统计每个子区间的答案，这个运算还是新运算，还有运算顺序的问题……但仔细分析后，我们发现，若一次只统计以某一个位置为右端点的所有区间的答案，最后将所有位置的答案累加，是一个可行的思路。那么该怎么统计以某一个位置为右端点的所有区间的答案呢？

$\qquad$我们来进行一波分类讨论：首先，我们观察这个新运算，发现若两个数只要有一个是 $0$，那么最终的结果一定是 $1$。所以，第一种情况就是：第 $i$ 个位置为 $0$，最终的答案为 $(i-1)$。

$\qquad$剩下的情况就是第 $i$ 个位置为 $1$ 了。在这个情况下，又要包含三个小情况：

1. $[1,i]$ 全为 $1$，此时，不难发现，每增加一个 $1$，区间的值就要异或一个 $1$，所以最终的答案就是 $(i+1)/2$；
2. $[2,i]$ 为 $1$，$a[1]$ 为 $0$，这时，左端点在 $[2,i]$ 的答案跟上一情况一样，为 $((i-2+1)+1)/2$，此时，最前方的 $0$ 对答案不会造成任何贡献，所以 $[1,i]$ 的值等于 $[2,i]$ 的值。所以若 $[2,i]$ 长度为奇，答案加一，否则不变；
3. $[k,i]$ 为 $1$，$a[k-1]$ 为 $0$，$k\geq2$。这时，左端点在 $[k-1,i]$ 的答案跟上一情况一样，此时，我们发现，从 $[k-2,i]$ 到 $[1,i]$ 的值都为 $[k-1,i]$ 的值异或 $1$，所以答案再加上 $[k-2,i]$ 的值乘 $(k-2)$。

$\qquad$在代码实现时，我们可以记录下后缀最长连续 $1$ 的长度和最后一个 $0$ 的位置，便于计算。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 1e6 + 5;
int n;
int a[maxn];
char ch[maxn];
LL f[maxn];

int main() {
    scanf("%d", &n);
    scanf("%s", ch + 1);
    for(int i = 1; i <= n; i ++) a[i] = (int)(ch[i] - '0');
    int lst = 0, fir = 0;//lst:后缀最长连续1，fir:最后一个0的位置
    for(int i = 1; i <= n; i ++) {
        if(a[i]) {
            lst ++;//连续1长度++
            if(fir == 0) f[i] = (lst + 1) / 2;//[1,i]全为1，第一种情况
            else if(fir == 1) f[i] = (lst + 1) / 2 + (lst & 1);//[2,i]为1，a[1]为0，第二种情况
            else f[i] = (lst + 1) / 2 + (lst & 1) + ((lst + 1) & 1) * (fir - 1);//第三种情况
        }
        else f[i] = 1LL * (i - 1), lst = 0, fir = i;//0的情况
        f[i] += f[i - 1];//求个前缀，便于输出
    }
    printf("%lld\n", f[n]);
    return 0;
}
```


---

## 作者：D2T1 (赞：0)

dp，设 $f_{i,0/1}$ 表示从 $i-1$ 方向来一个 $0/1$，走过 $[i,n]$ 对答案的贡献。

首先考虑 $f_{n,0/1}$。$0\barwedge0/1$ 都是 $1$，所以 $f_{n,0}=1$；$f_{n,1}=!a_n$。

然后就可以倒着求出转移：

$$
\begin{aligned}
f_{i,0}&=f_{i+1,1}+1\\
f_{i,1}&=f_{i+1,!a_i}+!a_i
\end{aligned}
$$

在转移过程中计算答案就可以了。

```cpp
//AT_abc310_e
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
int n, a[N], f[N][2];
char s[N];

void solve(){
	scanf("%d", &n);
	scanf("%s", s+1);
	for(int i = 1; i <= n; ++ i){
		a[i] = s[i] - '0';
	}
	ll ans = a[n];
	f[n][0] = 1;
	f[n][1] = 1 - a[n];
	for(int i = n-1; i >= 1; -- i){
		ans += a[i];
		ans += f[i+1][a[i]];
		f[i][0] = f[i+1][1] + 1;
		f[i][1] = f[i+1][1-a[i]] + 1-a[i];
	}
	printf("%lld\n", ans);
}

int main(){
	solve();
	return 0;
}
```

---

