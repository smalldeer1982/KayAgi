# [ABC384D] Repeated Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc384/tasks/abc384_d

周期 $ N $ をもつ無限数列 $ A=(A\ _\ 1,A\ _\ 2,A\ _\ 3,\dotsc) $ の先頭 $ N $ 項 $ A\ _\ 1,A\ _\ 2,\dotsc,A\ _\ N $ が与えられます。

この数列の空でない連続する部分列のうち、和が $ S $ となるものが存在するか判定してください。

ただし、無限数列 $ A $ が周期 $ N $ をもつとは、$ i\gt\ N $ を満たすすべての整数 $ i $ に対して $ A\ _\ i=A\ _\ {i-N} $ が成り立つことをいいます。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ A\ _\ i\leq\ 10\ ^\ 9 $
- $ 1\leq\ S\leq\ 10\ ^\ {18} $
- 入力はすべて整数
 
### Sample Explanation 1

数列 $ A $ は $ (3,8,4,3,8,4,3,8,4,\dotsc) $ のようになります。 $ A $ の部分列 $ (A\ _\ 2,A\ _\ 3,A\ _\ 4,A\ _\ 5,A\ _\ 6,A\ _\ 7,A\ _\ 8,A\ _\ 9)=(8,4,3,8,4,3,8,4) $ について $ 8+4+3+8+4+3+8+4=42 $ が成り立つので、`Yes` を出力してください。

### Sample Explanation 2

$ A $ の要素はすべて $ 3 $ 以上なので、$ A $ の空でない連続する部分列の総和は $ 3 $ 以上です。 よって、総和が $ 1 $ となるような部分列は存在しないため、`No` を出力してください。

## 样例 #1

### 输入

```
3 42
3 8 4```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 1
3 8 4```

### 输出

```
No```

## 样例 #3

### 输入

```
20 83298426
748 169 586 329 972 529 432 519 408 587 138 249 656 114 632 299 984 755 404 772```

### 输出

```
Yes```

## 样例 #4

### 输入

```
20 85415869
748 169 586 329 972 529 432 519 408 587 138 249 656 114 632 299 984 755 404 772```

### 输出

```
No```

# 题解

## 作者：Walrus (赞：4)

## 做法
发现我们能构造出来所有的 $S$ 一定是原数组的一段前缀加原数组总和的**非负整数倍**再加上原数组的一段后缀（**前后缀可以为空**）。

考虑预处理出 $pre$ 和 $suf$，直接 $O(N)$ 一遍扫过去，假设枚举前缀，那么就判断 $S$ 是否满足这个条件即可，具体的，有：
$$S=pre_i+sum\times k + suf_j$$

这个 $suf_j$ 不需要枚举，直接扔进 `map` 里判一下就可以了。

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define lowbit(i) (i & -i)
#define inf 0x3fffffff
#define int long long
#define pb push_back
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 5;
const int M = 5e4 + 5;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, m, k, res, a[N], xyk, tot;
int per[N], suf[N];
unordered_map<int, int> mp;

signed main() {
	FASTIO
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i], tot += a[i];
	rep(i, 1, n) per[i] = per[i - 1] + a[i];
	pre(i, n, 1) suf[i] = suf[i + 1] + a[i];
	rep(i, 0, n) mp[suf[i]] = 1;
	rep(i, 0, n) {
		if(k == per[i]) cout << "Yes", exit(0);
		if(k > per[i]) {
			m = k - per[i];
			m %= tot;
			if(mp[m]) cout << "Yes", exit(0);
		}
		else cout << "No", exit(0);
	}
	cout << "No";
	
	return 0;
}

```

---

## 作者：zlqwq (赞：3)

思维题。

为了模拟题目中无限的这个定义。我们可以让数量 $n$ 变成 $2 \times n$。

此时我们我们只需开一个队列，维护当前的区间和，设为 $res$。

如果 $res$ 与 $s$ 相等，就直接输出。

否则调节左右端点就行。如果小，右端点右移，否则左端点右移就行了。


```cpp
#include<iostream>
#include<queue> 
#define int long long
using namespace std;
int n;
const int MAXN=4e5+5;
int a[MAXN],s;
int sum=0;
signed main(){
	cin>>n>>s;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		sum+=a[i];
		a[i+n]=a[i];
	}
	s=s%sum;
	queue<int> stk;
	int val=0;
	for(int i=1;i<=n*2;++i){
		while(val>s){
			val-=stk.front();
			stk.pop();
		}
		if(val==s){
			cout<<"Yes";
			return 0;
		}
		val+=a[i];
		stk.push(a[i]);
	} 
	cout<<"No";
	return 0;
}
```

---

## 作者：icaijy (赞：3)

此题难点是数列会重复下去，直接暴力肯定不行。为了解决这个问题，我们观察到当 $S$ 很大时，需要重复取很多次这个周期。取足够次后，即再继续取就会超过 $S$ 时，让左边与数列末尾的一段拼接，右边与数列开头的一段拼接。这样就会形成一个很长的连续的数列。所以我们目标就是看拼接后能否满足目标数字。

对于取足够次周期这个问题，我们只需要让 $S$ 模周期的和，模完的就是我们拼接两端所需的数。

接下来就是如何检查能否拼接成功了。因为一边拼接开头一边拼接结尾，我们把周期重复存两次，在这个 $2N$ 大小的数列上进行双指针，取多了就让左指针右移，取少了就让右指针左移。刚好相等就成功了并结束。假如右指针超过 $2N+1$ 仍未成功，那就失败了。

以下是 AC 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
int a[400005];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,s;
    cin>>n>>s;
    int sum=0;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
        a[i+n]=a[i];
    }
    s%=sum;
    int l=0,r=0,cur=0;
    while (l<=r&&l<=2*n&&r<=2*n){
        while (cur<s&&r<=2*n) {
            r++;
            cur+=a[r];
        }
        while (cur>s&&l<=2*n){
            cur-=a[l];
            l++;
        }
        if (cur==s) {
            cout<<"Yes";
            return 0;
        }
    }
    cout<<"No";
    return 0;
}
```

---

## 作者：L01001101 (赞：2)

[$\color{000000}\text{AT\_abc384\_d Repeated Sequence}$](https://www.luogu.com.cn/problem/AT_abc384_d)

[$\color{000000}\text{D - Repeated Sequence}$](https://atcoder.jp/contests/abc384/tasks/abc384_d)

由于 $a$ 是以 $n$ 为周期的序列，因此若区间 $[l,r]$ 的和为 $s$，$[l,r]$ 一定是非负整数个长度为 $n$ 的周期加上一小段长度小于连续序列。

因此我们可以将 $s$ 模去一个周期的和，即 $s'=s\bmod sum$，得到的就是剩下一段序列的和。

接着我们枚举剩下序列的左端点 $l$，在前缀和序列上二分查询是否存在右端点 $r$ 使得 $\sum_{i=l}^{r}a_i=s'$ 即可。

由于左端点 $l$ 不定，而我们不可能每次将前缀和序列进行更新，因此直接在查询时将 $s'$ 加上 $[1,l-1]$ 的区间和即可。

注意到需要将序列复制一遍，因为剩余部分的序列可能横跨两个周期。

时间复杂度 $O(n \log n)$。

赛时写了个线段树 >_<。

```cpp
#include<cstdio>
typedef long long LL;
const int N=2e5+10;
int n;
LL s,sum;
int a[N<<1];
struct SegTree{
	int l,r;
	LL sum;
}t[N<<3];
inline LL read(){
	LL x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')ch=='-'?f=0:0,ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?x:-x;
}
inline void pushup(int p){t[p].sum=t[p<<1].sum+t[p<<1|1].sum;}
inline void build(int p=1,int l=1,int r=n<<1){
	t[p].l=l,t[p].r=r;
	if(l==r)return t[p].sum=a[l],void();
	int mid=l+r>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	pushup(p);
}
inline bool ask(int p,LL x){
	if(!x)return 1;
	if(t[p].l==t[p].r)return 0;
	return t[p<<1].sum<=x?ask(p<<1|1,x-t[p<<1].sum):ask(p<<1,x);
}
int main(){
	n=read(),s=read();
	for(int i=1;i<=n;++i)
		a[i]=read(),sum+=a[i],a[i+n]=a[i];
	s%=sum,sum=0;
	if(!s)return 0&puts("Yes");
	build();
	for(int i=1;i<=n;++i){
		if(ask(1,s+sum))return 0&puts("Yes");
		sum+=a[i];
	}
	puts("No");
	return 0;
}
```

---

## 作者：yyycj (赞：1)

## 原题跳转
[[ABC384D] Repeated Sequence](https://atcoder.jp/contests/abc384/tasks/abc384_d)

## 题目简述
给定一个每 $N$ 项为一个周期的无限序列 $A$，给定 $A_{1} \sim A_{N}$，判断是否存在一个 $A$ 的子序列使这个子序列的和为 $S$。如果存在输出 `Yes`，否则输出 `No`。

## 主要思路
不难发现，和为 $S$ 的子序列可以由三部分组成：  
1. 设 $x$ 为第一部分元素的个数（$0 \le x < N$），第一部分为 $A_{N-x+1} \sim A_{N}$（$x$ 为 $0$ 则没有）。
2. 若干个序列 $A$ 拼成的序列。
3. 设 $y$ 为第三部分元素的个数（$0 \le y < N$），第三部分为 $A_{1} \sim A _ {y}$（$y$ 为 $0$ 则没有）。

虽然第一部分和第三部分不能确定是如何组成的，但是第二部分可以，总和一定是若干个 $\sum _ {i=1} ^ {N} A _ {i}$ 的和且不超过 $S$ 的最大数。于是就可以先将 $S$ 取余 $\sum _ {i=1} ^ {N} A_{i}$，再判断是否可能存在第一部分和第三部分。

由于第二部分是若干个完整的序列，所以在去掉第二部分后，因为 $A$ 是一个无限序列，$A_{N}$ 的下一个元素可以理解为又是 $A_{1}$，所以第一部分和第三部分拼接起来也是连续的。

要判断是否存在这样一个序列，可以使用双指针的算法，由于第一部分和第三部分的元素数都 $< N$，所以拼接后的元素数一定不会 $> 2N$。 那么想要判断是否存在这个序列，就只需要对 $A_{1} \sim A_{2N}$ 进行枚举就可以了。暂且称 $A_{1} \sim A_{2N}$ 为 $A'$。

将序列 $A'$ 进行一次前缀和，根据双指针算法思路进行即可。如果 $\sum _ {i=l} ^ {r} A' _ {i} > S$，就不断增加 $l$，直到不大于为止，如果在这途中总和等于了 $S$，那么立即输出 `Yes` 并终止程序；如果在双指针枚举结束后还是没有出现总和等于 $S$ 的情况，输出 `No` 即可。

## AC Code
```cpp
#include<map>
#include<set>
#include<list>
#include<stack>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;

#define endl '\n'
typedef long long ll;
const int N = 4e5 + 10;       // 注意要开N的两倍，因为序列A'
typedef unsigned int ui;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
const double PI = acos(-1.0);
typedef unsigned long long ull;
// ----------------------------

// ----------------------------
ll a[N];           // 不开long long见祖宗
ll b[N];
// ----------------------------


int main() {
	ll s;
	int n;
	cin>>n>>s;
	ll sum = 0;
	for (int i=1;i<=n;i++) {
		cin>>a[i];
		sum += a[i];
	}
	// ------------------------
	s %= sum;   // 去除第二部分的总和
	for (int i=1;i<=n*2;i++) b[i] = b[i-1] + a[(i-1)%n+1];            // 构造序列A'
  // 双指针算法
	int l = 1;
	for (int r=1;r<=n*2;r++) {
		ll k = b[r] - b[l-1];
		while (k > s) {
			l++;
			k = b[r] - b[l-1];
		}
		if (k == s) {
			cout<<"Yes";
			return 0;
		}
	}
	// ------------------------
	cout<<"No";
	return 0;
}
```

---

## 作者：PUTONGDEYITIREN (赞：1)

# 思路
### 题面分析
这道题给了我们一个长度为 $n$ 的序列，叫我们把这个序列无限拼接形成一个无限序列，在上面截取一段，使这一段的和为给出的 $s$。这里我们应当分三种情况来分析。
### 分类讨论
* 这一段里至少含有一个长度为 $n$ 的完整序列。
* 这一段在一个长度为 $n$ 的完整序列中。
* 这一段里不含有一个长度为 $n$ 的完整序列。且分为两部分，分别属于两个长度为 $n$ 的完整序列中。
![](https://cdn.luogu.com.cn/upload/image_hosting/171cmllo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
### 核心思路
其实我们不难发现，这三种情况可以用一个式子来表示，就是我们分别找一个前缀和和一个后缀和，然后我们记这个序列的和为 $sum$，用 $m$ 取余 $sum$，再加上 $3$ 个 $sum$。再减去前缀和，最后取余 $sum$，看一下是否等于后缀和。用桶优化。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[200005],s,sum,f=0;
map<long long,long long> ma;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
	for(int i=0;i<=n;i++) s+=a[i],ma[s]=1;
	s=0;
	for(int i=n+1;i>=1;i--){s+=a[i];if(ma[(m%sum+3*sum-s)%sum]==1) f=1;}
	if(f==1) cout<<"Yes";
	else cout<<"No";
	return 0;
}

```

---

## 作者：sjh0626 (赞：1)

## 题意概括

给你一个周期为 $N$ 的无穷序列 $A=(A_1,A_2,A_3,\dots)$ 的前 $N$ 项 $A _ 1,A _ 2,\dots,A_N$ 。

请判断该无穷序列是否存在和为 $S$ 的非空连续子序列。

对于每个正整数 $i$ 来说，$i \le N$ 的周期为 $A_i=A_{i-N}$ 时，无穷序列 $A$ 的周期为 $N$。
## 思路分析
前缀和与二分结合，我们可以把 $A_1 \sim A_{2 \times N}$ 的前缀和 $Sum$ 序列求出来，然后把总和 $S$ 对总和取模，最后枚举右边界，二分左边界，看是否等于 $S$ 就可以做了。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
long long n,s,a[2000010],sum[2000010];
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=n+1;i<=2*n;i++){
		sum[i]=sum[i-1]+a[i%n];
	}
	s%=sum[n];
	for(int i=n;i<=2*n;i++){
		int l=1,r=i,mid;
		while(l<=r){
			mid=(l+r)/2;
			if(sum[i]-sum[mid-1]==s){
				cout<<"Yes";
				sjh0626s code;
			}
			else if(sum[i]-sum[mid-1]>s)l=mid+1;
			else r=mid-1;
		}
	}
	cout<<"No";
	sjh0626s code;
}
```

---

## 作者：__O_v_O__ (赞：1)

假设原序列为 $B$，$A$ 是无限重复它构成的序列。

首先，我们发现：$A$ 中的子序列一定是许多个 $B$ 拼接再加上一些“残余项”。

观察这个“残余项”：通过手算可知，它一定是 $B$ 的子序列，或是 $B$ 删除一段子序列所得的序列。

于是我们可以先把 $S$ 对 $B$ 序列的和取模，得到“残余项”的和 $t$，再使用前缀和+桶计算是否能满足。

具体来说，预处理前缀和 $s_i$，再扫一遍数组，同时使用桶记录某个前缀和是否出现过。设 $B$ 序列和为 $k$，遍历到 $i$ 时，判断 $s_i-t$ 或 $s_i-(k-t)$ 是否出现，然后把 $s_i$ 设为出现即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,s,a[200001],su,q[200001];
map<int,bool>mp;
signed main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++)cin>>a[i],su+=a[i],q[i]=q[i-1]+a[i];
	s%=su;
	mp[0]=1;
	for(int i=1;i<=n;i++){
		if(mp[q[i]-s]||mp[q[i]-(su-s)]){
			cout<<"Yes";
			return 0;
		}
		mp[q[i]]=1;
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
先让 $S$ 模周期的和，然后在 $A_1$ 到 $A_{2N}$ 中看有没有一段和为 $S$。可以求个前缀和，然后枚举右端点，用 map 维护出现过的左端点，判断是否存在 $s_l=s_r-S$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e6+10;
int n,s,a[N];
map<int,bool>mp;
signed main(){
	cin>>n>>s;
	for(int i=1;i<=n;++i) cin>>a[i],a[i+n]=a[i];
	for(int i=1;i<=n*2;++i) a[i]+=a[i-1];
	s%=a[n];
	for(int i=0;i<=n*2;++i){
		mp[a[i]]=1;
		if(mp[a[i]-s]) cout<<"Yes",exit(0);
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：0)

# AT_abc384_d 题解

提供一种 $O(n)$ 做法。

## 思路

由于选择的部分连续，所以可以把中间重复的部分给省掉，剩余部分可以用分类讨论 + 双指针。

为方便双指针和一些情况，把原数组复制一份。

接下来就是分类讨论：

记 $sum(l,r)$ 表示数组中 $l \sim r$ 的和。

- $S \equiv 0 \pmod {sum(1,n)}$ 时，显然成立。

- $sum(1,n) > S$ 时，在 $1 \sim n \times 2$ 中双指针找和为 $S$ 的子串即可。

- $sum(1,n) < S$ 时，令 $S \leftarrow S \bmod sum(1,n)$ 剩余部分与上一种情况相似。

时间复杂度：只有双指针，$O(n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e5+10;
int n;
ll a[N],S,sum[N];
int main()
{
	scanf("%d%lld",&n,&S);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=n+1;i<=n*2;i++)
	{
		a[i]=a[i-n];
		sum[i]=sum[i-1]+a[i];
	}//复制一份
	if(S%sum[n]==0) return puts("Yes"),0;
	if(sum[n]>S)
	{
		bool flag=0;
		for(int i=1,j=1;i<=n*2&&j<=n*2;i++)
		{
			while(j<n*2&&sum[j]-sum[i-1]<S) j++;
			if(sum[j]-sum[i-1]==S) flag=1;
		}
		if(flag){puts("Yes");return 0;}
	}
	else
	{
		S%=sum[n];
        //中间部分直接扔掉（免费
		bool flag=0;
		for(int i=1,j=2;i<=n*2&&j<=n*2;i++)
		{
            //sum(1~i)+sum(j~n)>S
			while(j<n*2&&sum[i]+sum[n]-sum[j-1]>S) j++;
			if(sum[i]+sum[n]-sum[j-1]==S) flag=1;
		}//双指针
		for(int i=1;i<=n;i++)
		{
			if(sum[i]==S) flag=1;
			if(sum[n]-sum[i-1]==S) flag=1;
		}//有可能只选左边的或只选右边的
		if(flag){puts("Yes");return 0;}
	}
	puts("No");
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

有一个无限循环的序列 $A'$，给定它的循环节是长度为 $N$ 的 $A=\{A_1,A_2,\cdots,A_N\}$，请问是否在 $A'$ 中存在一个子串 $\{A'_l,A'_{l+1},\cdots,A'_r\}$ 使得 $\sum_{i=l}^r A'_i=S$，数据范围 $N\le 2\times 10^5$。

## 解题思路

首先 $A'$ 序列无限循环，我们先把 $A$ 复制一份再拼到其后，形成字符串 $A_1$。显然，最后的答案子串中一定含有若干个 $A$，剩下的会分成两部分，将右边部分接到左边部分后，所形成的字符串一定是 $A_1$ 的子串（可以画画图）。于是记 $sum=\sum A$，则 $A$ 在答案子串中出现的次数即为 $\left\lfloor\frac{S}{sum}\right\rfloor$，则问题被转化成是否有 $(x,y)$ 满足

$$
sum\times\left\lfloor\frac{S}{sum}\right\rfloor+\sum_{i=x}^y A_{1_i}=S
$$

前面的部分可以预处理，后面要求一段区间是否满足条件，且是 $O(N)$ 的复杂度，考虑使用单调队列维护。每往队列中弹入一个数，重复判断前面的部分与队列的和是否超过 $S$，是的话弹出队头，每次操作完成后判断和是否为 $S$ 即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,x,a[400001],q[400001],head=1,tail,res,sum;

int main()
{
    n=read(); x=read();
    for(R int i=1; i<=n; ++i)
    a[i]=read(), a[n+i]=a[i], sum+=a[i];
    sum*=(x/sum); x-=sum;

    for(R int i=1; i<=n<<1; ++i)
    {
        q[++tail]=a[i]; res+=a[i];
        while(res>x && head<=tail) res-=a[head++];
        if(res==x) printf("Yes"), exit(0);
    }

    printf("No");
    return 0;
}
```

---

## 作者：Emplace (赞：0)

## 思路
这道题你可以尽量把前 $N$ 项数组里所有的和全都加起来，因为要是连续的如果你想往后面一段长度为 $N$ 的序列扩展，就必须选完（除非最后一段和第一段）。

那现在来考虑第一段和最后一段。

* 第一段可以发现末尾必须为第 $N$ 项。

* 最后一段可以发现开头必须是第 $1$ 项。

然后我们可以用二分解决。将需要的和（也就是 $S$）减完总和（直到不能减）。然后枚举第一段，去二分最后一段即可。

到这里你会发现是错的。你不一定要把需要的和减到不能减，而是可以少减几个导致可以往更后面与更前面延申。

到这里你还是会发现是错的。因为你可以在一段长度为 $N$ 的序列中选取中间的任意一段。对与这个你直接枚举左端点，二分右端点即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,s,a[300000],sum[300000],l=1,r=1;
signed main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=a[i]+sum[i-1];
	}
	for(int i=1;i<=n;i++){
		int l=i,r=n,f=0;
		while(l<=r){
			int mid=(l+r)/2;
			if(sum[mid]-sum[i-1]>s){
				r=mid-1;
			}
			else if(sum[mid]-sum[i-1]<s){
				l=mid+1;
			}
			else{
				f=1;
				break;
			}
		}
		if(f==1){
			cout<<"Yes";
			return 0;
		}
	}
	s%=sum[n];
	if(s==0){
		cout<<"Yes";
		return 0;
	}
	for(int k=1;k<=10;k++){
		int p=s;
		for(int i=1;i<=n+1;i++){
			int l=1,r=n,f=0;
			if(p<0){
				break;
			}
			while(l<=r){
				int mid=(l+r)/2;
				if(sum[n]-sum[mid-1]>p){
					l=mid+1;
				}
				else if(sum[n]-sum[mid-1]<p){
					r=mid-1;
				}
				else{
					f=1;
					break;
				}
			}
			if(f==1){
				cout<<"Yes";
				return 0;
			}
			p-=a[i];
		}
		s+=sum[n];
	}
	cout<<"No";
}
```
## ~~快点赞，不然我要彻底疯狂了！！！~~

---

## 作者：cyq32ent (赞：0)

考虑符合要求的串。如果 $S>\sum_{i=1}^Na_i$，那么串必定包含若干个完整的周期。我们去掉这些完整的周期，只考虑串末尾的一小段。易知这一小段的和为 $S\bmod\sum_{i=1}^Na_i$。这一小段的长度一定小于 $N$，而且它在序列 $A$ 上连续。我们发现，这个问题等价于一个长度为 $N$ 的环上找一个和为 $S\bmod\sum_{i=1}^Na_i$ 的段。按套路，我们破环为链，然后对于每一个可能的段的末尾，在前缀和数组中二分查找段的开头即可。时间复杂度 $\mathcal O(N \log N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s[402412];long long S;
int main(){
	cin>>n>>S;for(int i=1,x;i<=n;s[i]=s[i-1]+x,i++)cin>>x;
	for(int i=1;i<=n;i++)s[i+n]=s[i]+s[n];S%=s[n];
	for(int i=0;i<=2*n;i++)if(s[i]-S==*(lower_bound(s,s+1+i,s[i]-S)))return puts("Yes"),0;
	cout<<"No\n";
	return 0;
}
```

---

