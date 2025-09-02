# Make It Increasing

## 题目描述

You are given an array of $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ , and a set $ b $ of $ k $ distinct integers from $ 1 $ to $ n $ .

In one operation, you may choose two integers $ i $ and $ x $ ( $ 1 \le i \le n $ , $ x $ can be any integer) and assign $ a_i := x $ . This operation can be done only if $ i $ does not belong to the set $ b $ .

Calculate the minimum number of operations you should perform so the array $ a $ is increasing (that is, $ a_1 < a_2 < a_3 < \dots < a_n $ ), or report that it is impossible.

## 样例 #1

### 输入

```
7 2
1 2 1 1 3 5 1
3 5```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3
1 3 2
1 2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 0
4 3 1 2 3```

### 输出

```
2```

## 样例 #4

### 输入

```
10 3
1 3 5 6 12 9 8 10 13 15
2 4 9```

### 输出

```
3```

# 题解

## 作者：ran_qwq (赞：28)

[题目传送门](https://www.luogu.com.cn/problem/CF1437E)

upd on 2023/10/5：修改了一处笔误，感谢@bloodstalk  指出。

首先是一个常见的套路：把所有 $a_i$ 减去 $i$，问题转化为使 $a$ **单调不降**（好像不转化也行，但后面的处理不太方便）。

有些位置不能修改，我们将不能修改的 $k$ 个位置劈开，把数列分成 $k+1$ 段，每段分开求。

我们规定 $b_0=0,b_{m+1}=n+1$。如果某一段开始大于这一段结束，即存在一个 $i\in[1,m+1]$，满足 $a_{b_{i-1}}>a_{b_i}$，那么这段无论怎么改都不能使 $a$ 单调不降，此时无解。

每一段修改的要尽量少，不修改的要尽量多。那么问题就转化为：求每段的**最长不下降子序列**。

设 $x$ 为最长不下降子序列长度，这段的答案就是 $b_i-b_{i-1}-1-x$。每段答案求和即可。

但如果一个数小于这段开始，或大于这段结束，无论如何它都要修改，不能放进最长不下降子序列中，求的时候要跳过它。

[CF 提交记录](https://codeforces.com/contest/1437/submission/219042904)

---

## 作者：MikeDuke (赞：13)

考虑如何判断无解

比如：$1, *, *, *, *, 2$显然不合法，但$1, *, *, *, *, 114514$事可行的。

题目所要求的是**严格上升**的**整数**数列，

因此对于任意的两个限制点$i$和$j$，若$i<j$，则应满足$ j - i \le a_j - a_i $

即两个元素的差值应当大于它们之间需要填的数的个数

-----------

显然在最后构成的答案数列中，上述条件仍然成立。

-----------

$ j - i \le a_j - a_i $ 等价于 $ a_i - i \le a_j - j $

即 如果将元素的价值看为$a_i-i$，则在答案中的元素价值单调不降

------------

您所要最小化的是**更改**的次数，因此您需要在答案序列中最大化原数列元素出现的个数

“在原数列中选尽可能多的位置元素不变，调整其余位置，使调整后的序列价值单调不降”

“LIS（最长上升子序列）”

**价值视为$a_i-i$，求LIS就行了。**

------------

这时您生气地发现有一些位置被钦定不能修改，因此直接求整个数列的LIS不太行。

但您很快意识到这无所谓，

$k$个限制点将原数列分成了$k+1$段，每段相互之间没有影响，因此对每段单独求LIS即可。

------------

每段答案，即最小更改次数，为段长减LIS长度。

------------

------------

## 简要题解：

$k$个限定位置将原数列划分成$k+1$段。

对每段，将每个元素的值视为$a_i-i$，求LIS，此段的答案即为段长减LIS长度。

总答案为每段答案的和。

## code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define M 500005

int n, m, ans, a[M], b[M];

vector<int> LIS;

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { (x *= 10) += ch - '0'; ch = getchar(); }
	return x * f;
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read() - i; // 将每个元素的价值视为a[i]-i
	a[0] = -2e9; a[n+1] = 2e9;
	for (int i = 1; i <= m; i++)
		b[i] = read();
	b[0] = 0; b[m+1] = n+1;

	for (int i = 0, l, r; i <= m; i++)
	{
		l = b[i], r = b[i+1];
		if (a[l] > a[r])
		{ printf("%d\n", -1); return 0; }

		LIS.clear(); // 求[b[i]+1, b[i+1]-1]这段区间的LIS
		for (int j = l + 1; j <= r - 1; j++)
			if (a[j] >= a[l] && a[j] <= a[r]) // a[j]满足条件，可以出现在区间中
			{
				auto pos = upper_bound(LIS.begin(), LIS.end(), a[j]);
				if (pos == LIS.end()) LIS.push_back(a[j]);
				else *pos = a[j];
			}
		ans += (r-l-1) - LIS.size(); // 此段答案为段长-LIS长度
	}

	printf("%d\n", ans);

	return 0;
}
```

注：这里所说的最长上升子序列，实际上是最长不降子序列，但代码实现几乎完全一致

---

## 作者：Werner_Yin (赞：6)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/-solution-CF-1437E.html)
# 题目大意

给你一个数列 $a$ ,一个集合 $b$ , 对于每个$b$ 中的元素$x$， $a_x$ 不能修改，其他都可以修改，问最少多少次可以将$a$ 修改为严格单调递增的。如果不存在，输出 $-1$ 。

# 思路

我们先考虑不存在的情况，一定是存在$x,y\in b,x < y$ ,$a_y-a_x < y-x$ , 这样无法在 $a_x,a_y$ 中任意修改满足严格单调递增。

------

那么接下来考虑最小的修改次数。

加入我们没有修改限制呢？

那么就是一个经典的$DP$ 问题了。

我们将原数组变形，让$a_x = a_x -x$，然后跑一遍最长不下降子序列就行了（用 $nlogn$ 的算法），答案就是　$n-$最长不下降子序列长度了。

但是有限制，我们先考虑一下没有限制的代码。

```cpp
for(int i = 1;i <= n;i++) a[i] -= i;
for(int i = 1;i <= n;i++){
	if(e == 0 || a[i] >= l[e]) {
	    l[++e] = a[i];
	}
	else{
	    int p = upper_bound(l+1,l+e+1,a[i])-l;
	    l[p] = a[i];
	}
}//e : l 数组的末尾标号。
```

这样的代码会在遍历 $a$  数组时不断更新自己的一个假想的答案序列，使它每个值尽可能的小，然后容下一个新的值，使答案最大。

在判过是否满足后，$\forall x\in b$ ，$a_x$ 一定也可以在处理后形成一个不下降子序列，我们要保证不修改它们，就要让它们处于这个假想的答案序列中，于是我们可以加上几行：

```cpp
//lasb ,上一个不能修改的位置在我们当前维护的假想答案序列中的位置。
//ban[i] , a[i] 是否禁止修改。
for(int i = 1;i <= n;i++){
	if(e == 0 || a[i] >= l[e]) {
	    l[++e] = a[i];
	    if(ban[i]) lasb = e;
	}
	else{
	    int p = upper_bound(l+1,l+e+1,a[i])-l;
	    if(p <= lasb) continue;//如果我们要更改的位置小于上一个不能修改的位置，那么就不能更改假想的答案序列
	    l[p] = a[i];
	    if(ban[i]) lasb = p,e = p;//答案序列p后面的位置都不满足条件，因为它们不能大于这个不能修改的位置，因此对我们要的最长不下降子序列不能产生贡献。
	}
}
```



魔改一下这个算法后，就可以$AC$ 了。（具体理解见代码，可以结合一下$nlogn$的最长不下降子序列的算法）

# Code

```cpp
#define re(x) read(x)

const int MAXN = 1e6+10;

int n,k;
int a[MAXN],l[MAXN],e,b[MAXN],lasb=0;
bool ban[MAXN];

int main (){
    re(n);re(k);
    for(int i = 1;i <= n;i++) re(a[i]);
    for(int i = 1;i <= k;i++) re(b[i]),ban[b[i]]=1;
    sort(b+1,b+k+1);
    for(int i = 2;i <= k;i++)
		if(a[b[i-1]] - b[i-1] > a[b[i]] - b[i]){
	    	return puts("-1"),0;
		}
    for(int i = 1;i <= n;i++) a[i] -= i;
    for(int i = 1;i <= n;i++){
		if(e == 0 || a[i] >= l[e]) {
	    	l[++e] = a[i];
	    	if(ban[i]) lasb = e;
		}
		else{
	    	int p = upper_bound(l+1,l+e+1,a[i])-l;
	    	if(p <= lasb) continue;
	    	l[p] = a[i];
	    	if(ban[i]) lasb = p,e = p;
		}
    }
    printf("%d",n-e);
    return 0;
}
```

---

## 作者：George1123 (赞：5)


更木棒的体验 $\to$ [`George1123`](https://www.cnblogs.com/George1123/p/13891553.html)

---

## 题面

> [CF1437E Make It Increasing](https://www.luogu.com.cn/problem/CF1437E) 

> 给 $n$ 个数 $a_i$，固定 $k$ 个下标 $b_i$，求只修改不在 $b_i$ 中的下标的值使 $a_i$ 严格单调递增的最少修改次数。

> 数据范围：$1\le n\le 5\cdot 10^5$，$0\le k\le n$。

---

## 题解

分成 $k+1$ 段做没有问题，蒟蒻的做法是线段树维护 `dp`。

旁边老爷的做法是区间长度减去最长上升子序列长度，蒟蒻没想到，还想了单调队列优化好久。

题目转化为对于一个区间，第一个元素最后一个元素固定的最少修改次数。

把 $a_i$ 减去 $i$，就变成非严格单调递增了。

设 $f_i$ 表示不修改 $i$ 的前缀最少修改次数。

$$f_i=\min_{j=1,a_j\le a_i}^{i-1} (f_j+i-j-1)\Longrightarrow f_i=i-1+\min_{j=1,a_j\le a_i}^{i-1}( f_j-j)$$

所以可以建一个 $a_i$ 值域线段树，值为 $f_i-i$。

$f_i$ 的值就是当前线段树 $[0,a_i]$ 之间的最大值 $+i-1$。

每次求出 $f_i$ 后在 $a_i$ 上更新 $f_i-i$ 即可。

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define bg begin()
#define ed end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define L(i,a,b) for(int i=(b)-1,i##E=(a)-1;i>i##E;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=5e5+2;
int n,a[N],dn,d[N],k,b[N],ans;

//SegmentTree
const int tN=N<<2;
#define mid ((l+r)>>1)
int mn[tN];
void build(int k=0,int l=0,int r=dn){
    mn[k]=iinf; if(r-l==1) return;
    build(k*2+1,l,mid),build(k*2+2,mid,r);
}
void pushup(int k){mn[k]=min(mn[k*2+1],mn[k*2+2]);}
void fixmn(int x,int v,int k=0,int l=0,int r=dn){
    if(r<=x||x+1<=l) return;
    if(r-l==1) return mn[k]=min(mn[k],v),void();
    fixmn(x,v,k*2+1,l,mid),fixmn(x,v,k*2+2,mid,r),pushup(k);
}
int rangemn(int x,int y,int k=0,int l=0,int r=dn){
    if(r<=x||y<=l) return iinf; if(x<=l&&r<=y) return mn[k];
    return min(rangemn(x,y,k*2+1,l,mid),rangemn(x,y,k*2+2,mid,r));
}

//DP
int tmp[N];
int dp(int* arr,int len){
    R(i,dn=0,len) d[dn++]=arr[i];
    sort(d,d+dn),dn=unique(d,d+dn)-d;
    R(i,0,len) tmp[i]=lower_bound(d,d+dn,arr[i])-d;
    build(),fixmn(tmp[0],0); int res=-1;
    R(i,1,len){
        res=rangemn(0,tmp[i]+1)+i-1;
        fixmn(tmp[i],res-i);
    }
    // R(i,0,len) cout<<arr[i]<<' ';cout<<'\n';
    // R(i,0,len) cout<<f[i]<<' ';cout<<'\n';
    // cout<<f[len-1]<<'\n';
    return res;
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k,a[0]=-iinf,a[n+1]=+iinf;
    R(i,1,n+1) cin>>a[i],a[i]-=i;
    R(i,0,k) cin>>b[i];
    R(i,1,k)if(a[b[i]]<a[b[i-1]]) cout<<-1<<'\n',exit(0);
    if(k==0) ans=dp(a,n+2);
    else {
        ans+=dp(a,b[0]+1);
        R(i,1,k) ans+=dp(a+b[i-1],b[i]-b[i-1]+1); 
        ans+=dp(a+b[k-1],n-b[k-1]+2);
    }
    cout<<ans<<'\n';
    return 0;
}
```
---

**祝大家学习愉快！**

---

## 作者：allqpsi (赞：2)

~~比赛时没 A 赛后我来打题解了。~~

#### 思路：

要我们在不改个别地方时将数组修改为严格单调递增，很容易先想到最长上升子序列。

可有不可修改的地方怎么办呢？我们先偷个懒，将数组的每个元素减去它的位置。为什么这么做呢？这样，我们就可以将问题转成最长不下降序列，不再需要考虑此位置可不可以取此数了。（虽然不这么做也可以，但会更麻烦。）

做完这一点后，我们以不可改的下标和 1 与 $n$ 为边界，将数组分成许多段，每一段分别处理。可发现，此段需修改的数为有几个数减它的最长不下降序列。最后每个区间加起来，便为答案。

#### 注意：

我们每一段的最长不下降序列，必须包括它的开头与结束的数。这怎么办呢？我们只需在做最长不下降序列时，包含开头与结束的数便可以了。

#### 注意中注意：

我们以 1 与 $n$ 为边界时要注意。若此地方其实是可改的，我们便在最长不下降序列可以不包括它。此时需加特判。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,vi[500005],a,f[500005],top=0,st=1,ans=0;
bool vis[500005];
int find(int x){
	int l=1,r=top,aa=0;
	while(l<r){
		int mid=(l+r)/2;
		if(f[mid]<=x){
			aa=mid;
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	while(f[l]<=x){
		aa=l;
		l++;
	}
	return aa;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>vi[i];
		vi[i]-=i;
	}
	for(int i=1;i<=m;i++){
		cin>>a;
		vis[a]=1;
	}
	memset(f,-127,sizeof(f));
	for(int i=1;i<=n;i++){
		int t;
		if(vi[i]>=f[top]){
			f[++top]=vi[i];
			t=top;
		}
		else if(vi[i]>=f[1]||!vis[st]){
			if(vi[i]<f[1]){
				f[1]=vi[i];
				t=1;
			}
			else{
				t=find(vi[i])+1;
				f[t]=min(f[t],vi[i]);
			}
		}
		if(vis[i]||i==n){
			if(vis[st]&&vis[i]&&vi[i]<vi[st]){
				cout<<-1;
				return 0;
			}
			if(!vis[i]){
				ans+=i-st+1-top;
			}
			else{
				ans+=i-st+1-t;
			}
			for(int i=1;i<=top;i++){
				f[i]=1e9+1;
			}
			top=1;
			f[top]=vi[i];
			st=i;
		}
		t=2;
	}
	cout<<ans;
} 
```

---

## 作者：iodwad (赞：2)

考虑改变次数最小等价于保留最多个数字不变动，那么就很像一个最长上升子序列问题。但是这个子序列必须是合法的，具体来说，子序列中相邻两个数字之间必须留够足够数字给那些被修改的。$dp(i)=\max\limits_{j<i,i-j\leq a_i-a_j}\{dp(j)\}+1$。用树状数组维护即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define mp std::make_pair
#define pb push_back

const int MAXN = 5e5 + 4;
const int INF = 0x3f3f3f3f;

int n, K;
int a[MAXN | 1], b[MAXN | 1], num[MAXN | 1], bit[MAXN | 1], dp[MAXN | 1];

inline int read() {
  register int x = 0, v = 1;
  register char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') v = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * v;
}

int query(int x) {
  int res = -INF;
  for (int i = x; i > 0; i -= i & -i) res = std::max(res, bit[i]);
  return res;
}

void modify(int x, int y) {
  for (int i = x; i <= n + 2; i += i & -i) bit[i] = std::max(bit[i], y);
}

void clear(int x) {
  for (int i = x; i <= n + 2; i += i & -i) bit[i] = -INF;
}

int main() {
  n = read();
  K = read();
  for (int i = 1; i <= n; ++i) num[i] = a[i] = read();
  for (int i = 1; i <= K; ++i) b[i] = read();
  for (int i = 2; i <= K; ++i) {
    if (a[b[i - 1]] > a[b[i]] || (a[b[i]] - a[b[i - 1]] < b[i] - b[i - 1])) {
      printf("-1");
      return 0;
    }
  }
  for (int i = 1; i <= n; ++i) num[i] = a[i] = a[i] - i;
  std::sort(num + 1, num + 1 + n);
  int tot = std::unique(num + 1, num + 1 + n) - num - 1;
  for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(num + 1, num + 1 + tot, a[i]) - num;
  for (int i = 0; i <= n; ++i) ++a[i];
  b[++K] = n + 1;
  a[n + 1] = n + 2;
  int ans = 0;
  for (int i = 0; i <= n + 2; ++i) bit[i] = -INF;
  for (int i = 1; i <= K; ++i) {
    if (b[i - 1] + 1 == b[i]) continue;
    modify(a[b[i - 1]], 1);
    dp[b[i - 1]] = 1;
    for (int j = b[i - 1] + 1; j <= b[i]; ++j) {
      dp[j] = query(a[j]) + 1;
      modify(a[j], dp[j]);
    }
    for (int j = b[i - 1]; j <= b[i]; ++j) clear(a[j]);
    ans += b[i] - b[i - 1] + 1 - dp[b[i]];
  }
  printf("%d\n", ans);
  return 0;
}
```


---

## 作者：InQueue (赞：1)

首先有套路：对每个 $1\le i\le n$ 做 $a_i\gets a_i-i$，然后最终要求改成一个单调不降序列。显然答案不变。下文都对调整后的 $a$ 讨论。

无解条件：当且仅当存在 $1\le i<k$ 使得 $a_{b_i}>a_{b_{i+1}}$ 时无解。

规定：$a_0=-\infty,a_{n+1}=+\infty,b_0=0,b_{k+1}=n+1$。

将 $a$ 按照 $b$ 分为 $k+1$ 段，即 $A_i=(a_{b_{i-1}+1},a_{b_{i-1}+2},\cdots,a_{b_i-1})$。记 $L_i = a_{b_{i-1}},R_i=a_{b_i}$。

此时段间是独立的。接下来考虑某个段 $(A,L,R)$ 内的操作。

考虑选取一个子序列使其保持不变，则一个选取方案 $(i_1,i_2,\cdots,i_l)$ 合法，当且仅当 $L\le A_{i_1}\le A_{i_2}\le \cdots\le A_{i_l}\le R$。故转化为求首项 $\ge L$，末项 $\le R$ 的最长不降子序列。

如果你用 BIT 实现，算完一段后应该对操作过的位置依次清空，否则复杂度不对。

总时间复杂度为 $O(n\log n)$。

[CF 提交记录](https://codeforces.com/contest/1437/submission/307093825)。

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

### 题意

给定序列 $a$，固定一些位置。定义一次操作为修改一个位置的数。问最少需要多少次操作使得序列严格递增。

### 题解

严格递增可以通过 $a_i\leftarrow a_i-i$ 的方式变成单调不减。

判断无解即判断所有前后两个固定的位置 $i<j$ 是否均满足 $a_i\le a_j$。

容易发现固定的位置将序列分成了 $k+1$ 段，每一段问题相互独立。

每一段内即询问该段最少多少次修改使得这一段单调不减。

由于修改一个数的花费固定为 $1$，我们只需要最小化修改的数的个数。所以我们找到该段内的最长单调不减子序列。容易发现由于我们的限制是单调不减，不在这个子序列中的数均能通过变成其左边或右边的位于该子序列内的数从而满足要求。

但是这么做可能没有顾及到左右端点的限制要求。有两种解决方法，一种是强制最长单调不减子序列的开头和结尾为该段的左右端点，另一种是在求子序列的时候将值域不在 $[a_l,a_r]$ 的数剔除。前者相对而言比较麻烦。

最长单调不减自序列是经典问题，这里不限制做法。~~为什么不尝试万能的线段树呢？~~

```cpp
#include <bits/stdc++.h>
#define lint __int128
// #define int long long
#define Il inline
#define fi first
#define se second
#define vec vector
#define pb push_back
#define IT ::iterator
#define p_q priority_queue

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef double db;
const int N=5e5,Inf=1e9;
const db eps=1e-9,pi=acos(-1.0);

mt19937 rnd(time(0));
Il int rint(int l,int r){return rnd()%(r-l+1)+l;}

int n,m,a[N+5],b[N+5],ans=0,dp[N+5];
int id=0,rt,mx[N*32+5],ls[N*32+5],rs[N*32+5];

Il void chg(int ps,int l,int r,int &p,int x){
    int mid=(l+r)>>1;if(!p)p=++id;
    if(l==r){mx[p]=x;return;}
    if(ps<=mid)chg(ps,l,mid,ls[p],x);
    else chg(ps,mid+1,r,rs[p],x);
    mx[p]=max(mx[ls[p]],mx[rs[p]]);
    return;
}

Il int qmx(int ql,int qr,int l,int r,int p){
    int mid=(l+r)>>1,ret=0;if(!p)return 0;
    if(ql<=l&&r<=qr)return mx[p];
    if(ql<=mid)ret=max(ret,qmx(ql,qr,l,mid,ls[p]));
    if(qr>mid)ret=max(ret,qmx(ql,qr,mid+1,r,rs[p]));
    return ret;
}

Il void solve(int l,int r){
    if(r-l<2)return;
    rt=++id;int mxl=0;
    for(int i=l+1;i<r;i++){
        if(a[i]<a[l]||a[i]>a[r])continue;
        dp[i]=qmx(-Inf,a[i],-Inf,Inf,rt)+1;
        chg(a[i],-Inf,Inf,rt,dp[i]);mxl=max(mxl,dp[i]);
    }
    ans+=(r-l-1)-mxl;
    return;
}

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;for(int i=1;i<=n;i++)cin>>a[i],a[i]-=i;
    a[0]=-Inf;for(int i=1;i<=m;i++){cin>>b[i];if(a[b[i]]<a[b[i-1]]){cout<<-1;return 0;}}
    a[b[++m]=n+1]=Inf;for(int i=1;i<=m;i++)solve(b[i-1],b[i]);
    cout<<ans;
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

这是一篇没有发现结论，直接硬做的题解。

考虑 $dp_{i,j}$ 表示考虑前缀 $[1,i]$ 且 $a_i = j$ 的最小修改次数。

$$dp_{i,a_i} = \sum_{j < a_i} dp_{i-1,j}$$。

$$dp_{i,j} = \sum_{k < j} dp_{i-1,k} + 1$$。

不妨 $g_{i,j} = \min_{k \leq j} dp_{i,j}$。

有 $g_{i,j} = min(g_{i,j},g_{i-1,a_i - 1} + 1)(j \geq a_i)$。

$$g_{i,j} = g_{i-1,j-1}+1$$。

考虑 $F_i(k) = g_{i,i+k}$。

有 $F_i(j) = \min(F_i(j),F_{i-1}(a_i - i)+1)$。

$$F_{i}(j) = F_{i-1}(j)$$。

考虑线段树维护 $F_{i}(x)$，维护 $x \gets \min(x,k) + c$ 与单点查询即可，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//F_i(k) = F_{i-1}(k)+1 (i \not in b)
//F_i(k) = min(F_i(k),F_{i-1}(a_i - i)) (k>=a[i]-i)
//y(x) = min(x,k)+c
//单点查询
#define int long long
const int maxn = 5e5+114;
const int inf = 1e13+114;
struct info{
    int k,c; 
    info(int K=inf,int C=0){
        k=K,c=C;
    }
    info operator+(const info &x)const{
        return info(min(k,x.k-c),x.c+c);
    }
}tag[maxn<<2];
int a[maxn],vis[maxn],b[maxn],n;
void pushdown(int cur){
    tag[cur<<1]=tag[cur<<1]+tag[cur];
    tag[cur<<1|1]=tag[cur<<1|1]+tag[cur];
    tag[cur]=info();
    return ;
}
void change(int cur,int lt,int rt,int l,int r,info c){
    if(l>r) return ;
    if(rt<l||r<lt) return ;
    if(l<=lt&&rt<=r){
        tag[cur]=tag[cur]+c;
        return ;
    }
    int mid=(lt+rt)>>1;
    pushdown(cur);
    change(cur<<1,lt,mid,l,r,c);
    change(cur<<1|1,mid+1,rt,l,r,c);
}
int query(int cur,int lt,int rt){
    if(lt==rt){
        return min(inf,tag[cur].k)+tag[cur].c;
    }
    int mid=(lt+rt)>>1;
    pushdown(cur);
    return min(query(cur<<1,lt,mid),query(cur<<1|1,mid+1,rt));
}
int ask(int cur,int lt,int rt,int pos){
    if(lt==rt){
        return min(inf,tag[cur].k)+tag[cur].c;
    }
    int mid=(lt+rt)>>1;
    pushdown(cur);
    if(pos<=mid) return ask(cur<<1,lt,mid,pos);
    else return ask(cur<<1|1,mid+1,rt,pos);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    int k;
    cin>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
        a[i]-=i;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        int l=1,r=n+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(a[mid]<=b[i]-i) l=mid;
            else r=mid;
        }
        b[i]=l;
    }
    for(int i=1;i<=k;i++){
        int x;
        cin>>x;
        vis[x]=1;
    }
    tag[1]=info(inf,inf);
    change(1,1,n,b[1],n,info(0,0));
    if(vis[1]==0){
        change(1,1,n,1,b[1]-1,info(0,1));
    }
    for(int i=2;i<=n;i++){
        int dp=ask(1,1,n,b[i]);
        change(1,1,n,1,n,info(inf,vis[i]==0?1:inf));
        change(1,1,n,b[i],n,info(dp,0));
    }
    int ans=query(1,1,n);
    cout<<(ans<=n?ans:-1)<<'\n';
    return 0;
}
```

---

## 作者：Starry_Ocean (赞：0)

- 参考文章：[MikeDuke](https://www.luogu.com.cn/user/150218) 的《[题解 CF1437E 【Make It Increasing】](https://www.luogu.com.cn/article/y5edrki7)》。


### 主要思路
按照题意，我们需要构造一个序列 $a_1 , a_2 , a_3 ,   \cdots , a_n$ 满足 $a_1 \le a_2 \le a_3 \le \cdots \le a_n $ 。

题目已经给出了一个序列，我们需要修改这个序列，满足上述关系，同时有一些位置的元素不能修改，因此我们可以考虑分段，将原序列分为 $k+1$ 段，对于每一段，把这一段的元素个数设为 $m$ 仅需构造 $A_1 \le A_2 \le \cdots \le A_m$ 的序列即可，然后把这 $k+1$ 段拼接在一起，依然能完成总目标。所以，这是一个分治问题。

如何构造这个子序列呢？

观察这个序列，发现：对于任意一对 $i,j$ ， 满足 $1 \le i < j \le m$ ， 一定有 $j-i \le a_j-a_i$ 。因此，一定有 $a_i-i \le a_j-j$ 。所以，如果我们将第  $i(1 \le i \le n) $ 的价值记为 $a_i-i$ ,则在答案中的元素价值单调不降。

最后，我们的任务是最小化修改次数，也就是最大化保留元素个数。此时，我们仅仅只需要求一个 LIS 即可。如果你不知道这是什么，[文章](https://blog.csdn.net/hwdn3000/article/details/104937044)，[模板题](https://www.luogu.com.cn/problem/B3637)，我双手奉上。

综合以上叙述，我们的最终答案就是每段的段长减去 LIS 长度。

为了让优化程序，我在代码中使用了二分优化 LIS ，使用了一个函数 (代码第 28 行) ， 如果您不了解此函数的用法，详见[此文章](https://blog.csdn.net/weixin_60033897/article/details/135204120)。

### AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500006
using namespace std;
ll n,k,ans,a[N],b[N];
vector<ll> LIS;
int main(){
	cin>>n>>k;
	for(ll i = 1;i <= n;++i){
		cin>>a[i];
		a[i]-=i;
	}
	a[0]=-1e15,a[n+1]=1e15;
	for(ll i = 1;i <= k;++i){
		cin>>b[i];
	}
	b[0]=0,b[k+1]=n+1;
	for(ll i = 0;i <= k;++i){//执行k+1次（有k+1段） 
		ll L = b[i] , R = b[i+1];
		if(a[L]>a[R]){
			cout << -1;
			return 0;//特判 
		}
		//接下来，我们要求出(b[i]+1,b[i+1]-1) 这段区间的LIS 
		LIS.clear();//先清空 
		for(ll j = L+1;j <= R-1;++j){
			if(a[L]<=a[j]&&a[j]<=a[R]){//如果合法，就要满足a[L]<=a[j]<=a[R] 
				auto pos=upper_bound(LIS.begin(),LIS.end(),a[j]);
				if(pos==LIS.end()) LIS.push_back(a[j]);
				else *pos=a[j];
			}
		}
		ans+=(R-L-1-LIS.size());
	}
	cout << ans;
	return 0;
} 
```

[AC 记录](https://codeforces.com/contest/1437/submission/277600909)

---

## 作者：Reunite (赞：0)

套路地，令 $a_i\leftarrow a_i-i$，把单调上升转化为单调不降，因为有固定不动的限制，所以显然是一段一段的做，段的端点若不合法则显然不可能合法。

转化为，对于一个序列 $a_{l,r}$，钦定上下界为 $[L,R]$，问将其转化为值域在上下界内的单调不降序列最小修改次数。最小修改次数即区间 $len$ 减去最大保留次数，然后这个就是一个最长单调不降序列的板子了，直接上 BIT 优化一下，注意每次清空，复杂度 $O(n\log n)$。

```cpp

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,k,m;
int a[500005];
int b[500005];
int t[500005];

inline void add(int x,int k){while(x<=m) t[x]=max(t[x],k),x+=x&-x;return ;}
inline int ask(int x){int s=0;while(x) s=max(s,t[x]),x^=x&-x;return s;}
inline void init(int x){while(x<=m) t[x]=0,x+=x&-x;return ;}

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int solve(int l,int r){
	int tt=0,ans=0,mx=0;
	for(int i=l;i<=r;i++){
		if(a[i]<a[l-1]||a[i]>a[r+1]){ans++;continue;}
		b[++tt]=a[i];
		int x=ask(a[i]);
		mx=max(mx,x+1);
		add(a[i],x+1);
	}
	for(int i=1;i<=tt;i++) init(b[i]);
	return r-l+1-mx;
}

int main(){
	in(n),in(k);
	for(int i=1;i<=n;i++) in(a[i]),a[i]-=i,b[i]=a[i];
	sort(b+1,b+1+n);
	m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+m,a[i])-b;
	int las=0,ans=0;
	for(int i=1;i<=k;i++){
		int r;
		in(r);
		if(a[las]>a[r]){puts("-1");return 0;}
		ans+=solve(las+1,r-1);
		las=r;
	}
	a[n+1]=m;
	if(las<n) ans+=solve(las+1,n);
	printf("%d\n",ans);

	return 0;
}
```

---

