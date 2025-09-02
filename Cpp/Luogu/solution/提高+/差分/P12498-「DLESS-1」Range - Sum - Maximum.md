# 「DLESS-1」Range | Sum | Maximum

## 题目描述

给出一个长度为 $n$ 的序列 $a$，定义一个区间 $[l,r]$ 的权值为 $\max_{l\le L\le R\le r}|\sum_{i=L}^Ra_i|$。

对于 $k=1,2,3,\dots,n$，求所有长度为 $k$ 的区间权值和。

## 说明/提示

#### 【样例解释】

样例中五组数据的 $ans$ 分别为：
- $\{4,3,2\}$
- $\{28,39,41,36,31,22,13\}$
- $\{28,39,41,36,31,22,13\}$
- $\{7,10,10,7\}$
- $\{18,23,19,14,7\}$

其中，对于第一组数据，各个区间的权值分别如下：

- $[1,1]:1$
- $[2,2]:1$
- $[3,3]:2$
- $[1,2]:1$
- $[2,3]:2$
- $[1,3]:2$

其中，长度为 $1$ 的区间有 $[1,1],[2,2],[3,3]$，权值和为 $4$；长度为 $2$ 的区间有 $[1,2],[2,3]$，权值和为 $3$；长度为 $3$ 的区间有 $[1,3]$，权值和为 $2$。

#### 【数据范围】

对于所有数据，保证：
- $1\le T\le10^4$
- $1\le n,\sum n\le10^6$
- $-10^6\le a_i\le10^6$

**本题采用打包测试**，各测试包描述如下：

| Subtask | $\sum n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $500$ | 无 | $5$ |
| $2$ | $5000$ | 无 | $20$ |
| $3$ | $10^6$ | $a_i\ge 0$ | $25$ |
| $4$ | $3\times10^5$ | 无 | $25$ |
| $5$ | $10^6$ | 无 | $25$ |


## 样例 #1

### 输入

```
5
3
1 -1 2
7
1 -2 -3 4 5 -6 -7
7
-1 2 3 -4 -5 6 7
4
1 1 2 3
5
1 4 -5 -2 6```

### 输出

```
1
31
31
4
11```

# 题解

## 作者：Gold14526 (赞：7)

发现区间 $[l,r]$ 的权值等于区间 $[l-1,r]$ 中最大的前缀和减去最小的前缀和。

于是问题转化为求出所有长度为 $k$ 的区间最大值和。

这个就比较套路了，对于每个前缀和 $s_i$，我们用单调栈求出其作为最大值的极长区间 $[l_i,r_i]$，设 $\Delta l=i-l_i+1,\Delta r=r_i-i+1,len=r_i-l_i+1$，不妨假设 $\Delta l\le \Delta r$，那么它对答案有以下贡献：

- 对于 $i\in[1,\Delta l]$，它对 $ans_i$ 有 $i\times s_i$ 的贡献。
- 对于 $i\in(\Delta l,\Delta r]$，它对 $ans_i$ 有 $\Delta l\times s_i$ 的贡献。
- 对于 $i\in(\Delta r,len]$ 它对 $ans_i$ 有 $(len-i+1)\times s_i$ 的贡献。

发现是区间加等差数列的形式，两次差分即可解决。

注意区间 $[l,r]$ 长度比 $[l-1,r]$ 长度小 $1$，所以上述的贡献的区间左右端点都要减一，或者最后要把 $ans_i$ 替换成原来的 $ans_{i+1}$。

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read()
{
	int x=0,zf=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')zf=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return x*zf;
}
void print(cll x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
void princh(cll x,const char ch)
{
	print(x);
	putchar(ch);
}
cint N=1e6;
int n,a[N+1],l[N+1],r[N+1];
ll s[N+1],ans[N+3];
struct stck{
	int a[N+1],t;
	void clear(cint x){a[0]=x,t=0;}
	void push(cint x){a[++t]=x;}
	void pop(){--t;}
	int top(){return a[t];}
	int size(){return t;}
	bool empty(){return (t==0);}
}st;
void calc()
{
	st.clear(-1);
	for(int i=0;i<=n;++i)
	{
		while(!st.empty()&&s[st.top()]<=s[i])st.pop();
		l[i]=st.top()+1;
		st.push(i);
	}
	st.clear(n+1);
	for(int i=n;i>=0;--i)
	{
		while(!st.empty()&&s[st.top()]<s[i])st.pop();
		r[i]=st.top()-1;
		st.push(i);
	}
	for(int i=0;i<=n;++i)
	{
		int p=i-l[i]+1,q=r[i]-i+1;
		if(p>q)swap(p,q);
		ans[0]+=s[i];
		ans[p]-=s[i];
		ans[q]-=s[i];
		ans[r[i]-l[i]+2]+=s[i];
	}
}
void solve()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
		s[i]=s[i-1]+a[i];
		ans[i]=0;
	}
	ans[0]=0;
	calc();
	for(int i=0;i<=n;++i)
	{
		s[i]=-s[i];
	}
	calc();
	for(int i=1;i<=n;++i)
	{
		ans[i]+=ans[i-1];
	}
	ll res=0;
	for(int i=1;i<=n;++i)
	{
		ans[i]+=ans[i-1];
		res^=ans[i]%(1ll*i*i);
	}
	princh(res,'\n');
}
int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}

```

---

## 作者：toolazy (赞：5)

哈哈，非常幸运，赛前我正好找到了两道还没写的题：[P10194 [USACO24FEB] Milk Exchange G](https://www.luogu.com.cn/problem/P10194) 以及它讨论区下面的 [CF/212/D Cutting a Fence](https://www.luogu.com.cn/problem/CF212D)：

> 给定长度为 $n$ 的序列 $\{a_i\}$，求出序列 $\{\text{ans}_i\}$，其中满足：
>
> $$
> \text{ans}_k=\sum_{1\le L\le R\le n}^{R-L+1=k}\bigg(\min_{i=L}^R\{a_i\}\bigg)
> $$
>
> 数据范围：$n\le 10^6$。

是不是神似？做完这题，原题就会做了。

> 我们考虑反向贡献，考虑一个元素 $a_i$ 对答案的贡献。
>
> $a_i$ 如果要成为某个区间的最小值，显然我们就可以提前找到一个左边最右的边界 $l_i$ 和右边最左的边界 $r_i$ 使满足：
>
> $$
> a_{i-l_i},a_{i+r_i}\ge a_i
> $$
>
> 你可以假设 $a_0=a_{n+1}=+\infty$，并且 $l_i$ 和 $r_i$ 不要直接取到 $0$ 本身，这个东西可以笛卡尔也可以单调栈简单做。
> 
> 那么，$a_i$ 能产生贡献的区间 $[l',r']$ 显然必须成为 $[i-l_i+1,i+r_i-1]$ 的子区间，并且还得有 $l'\le i\le r'$，也就是要包含 $a_i$ 本身。
>
> 不错，这个形式很连续。接下来，我们假设 $l_i\le r_i$，符合条件的子区间中：
>
> - 长度为 $1$ 的恰有 $1$ 个。
> - 长度为 $2$ 的恰有 $2$ 个。
> - 长度为 $3$ 的恰有 $3$ 个。
> - ......
> 
> 直到 $l_i$，我们迎来第一个转折点。
> 
> - 长度为 $l_i$ 的恰有 $l_i$ 个。
> - 长度为 $l_i+1$ 的仍只有 $l_i$ 个，因为左边已经触底了，不能扩张了。
> - 长度为 $l_i+2$ 的仍只有 $l_i$ 个。
> - 长度为 $l_i+3$ 的仍只有 $l_i$ 个。
> - ......
> 
> 直到 $r_i$，我们迎来第二个转折点。
> 
> - 长度为 $r_i$ 的仍只有 $l_i$ 个。
> - 长度为 $r_i+1$ 的却只有 $l_i-1$ 个，因为现在两边都触底了，区间数量只会越来越少。
> - 长度为 $r_i+2$ 的只有 $l_i-2$ 个。
> - 长度为 $r_i+3$ 的只有 $l_i-3$ 个。
> - ......
> - 直到最后，长度为 $l_i+r_i-1$ 的只剩下 $1$ 个。
> - 然后对于长度 $k\ge l_i+r_i$ 的 $\text{ans}_k$ 显然就没有贡献了，结束吧。

这个东西类似等差数列，你可以选择 SGT（等差数列的 tag 可以劈两半下传），也可以选择更简单的二维差分前缀和，相信在座各位动笔写写都会。

> 补：关于单调栈求解 $l_i,r_i$，需要注意处理相同数字。比如说：
>
> $$
> a=\{3,3,3\}
> $$
>
> 当这三个相同数字同时并排出现的时候，直接按照上面所说的，肯定会求解出：
>
> $$
> l=\{1,1,1\}\\
> r=\{1,1,1\}
> $$
>
> 这意味着，我们只计算了了区间 $[1,1],[2,2],[3,3]$ 的贡献，而 $[1,2],[2,3],[1,3]$ 却漏算了，最后的答案会偏小。
>
> 为了避免这个问题，让每个区间都被计算且只计算一次，我们规定：$l_i$ 以内必须要 **严格小于** 而 $r_i$ 以内可以 **小于等于**。
>
> 彼时再重新计算：
>
> $$
> l=\{1,1,1\}\\
> r=\{3,2,1\}
> $$
>
> 这样子就不会漏了。如果你和 [这份提交记录](https://www.luogu.com.cn/record/217014362)（几乎）一样，那你可能也是这样子。

然后 $\min$ 换 $\max$ 也是好做的，单调栈的时候大于改小于就好了。接下来我们回到原题：

> 定义区间 $[l,r]$ 的权值为：
>
> $$
> \max_{l\le L\le R\le r}\bigg\{\Big|\sum_{i=L}^{R}a_i\Big|\bigg\}
> $$

我当时看到这个式子的一瞬间就感觉圆梦了，头一回碰上了这个取绝对值的符号，这不就正好意味着......

> 我们光速考虑前缀和，记 $\text{pre}_i$ 表示 $[1,i]$ 的区间和，原式即为：
>
> $$
> \max_{l\le L\le R\le r}\bigg\{\Big|\text{pre}_R-\text{pre}_{L-1}\Big|\bigg\}
> $$
>
> 那说白了：取绝对值，其实就是 **极差**，并且我们 **不在意 $L,R$ 的先后关系**。
>
> 直接找到区间 $[l-1,r]$ 中 $\text{pre}$ 最大者和最小着，其差就是上式（极差的定义）。
>
> 所以，我们就把 $L,R$ 给独立开来了：
>
> $$
> \max_{l-1\le R\le r}\text{pre}_R-\max_{l-1\le L\le r}\text{pre}_{L}
> $$

这样就转化成了两个独立的问题，一个是『对于每个 $k$ 都求出长度为 $k$ 的子区间的区间最大值之和』，一个是『求出长度为 $k$ 的子区间的区间最小值之和』。

综上，我们得到了在 $O(n)$ 时间复杂度的解法。参考代码见下：

```c++
#include <iostream>
#include <stack>
using namespace std;

#define int long long

const int MAXN = 1e6 + 5;
const int INF = 0x3f3f3f3f3f3f3f3f;
int T, n, a[MAXN], ans;
int b[MAXN]; stack<int> stk;

namespace MAXIUM {
	
	int ans[MAXN];
	int ls[MAXN], rs[MAXN]; // find the first greater/equal one
	stack<int> stk;
	
	void solve() {
		for (int i = 2; i <= n + 1; i ++) b[i] = b[i - 1] + a[i - 1];
		b[0] = INF, b[n + 2] = INF;
		while (!stk.empty()) { stk.pop(); } stk.push(0);
		for (int i = 1; i <= n + 1; i ++) {
			while (b[stk.top()] < b[i]) stk.pop();
			ls[i] = i - stk.top(); stk.push(i);
		}
		while (!stk.empty()) { stk.pop(); } stk.push(n + 2);
		for (int i = n + 1; i >= 1; i --) {
			while (b[stk.top()] <= b[i]) stk.pop();
			rs[i] = stk.top() - i; stk.push(i);
		}
		for (int i = 1; i <= n + 1; i ++) ans[i] = 0;
		for (int i = 1; i <= n + 1; i ++) {
			int small = min(ls[i], rs[i]);
			int big = max(ls[i], rs[i]);
			ans[1] += b[i];
			ans[small + 1] -= b[i];
			ans[big + 1] -= b[i];
			ans[small + big + 1] += b[i];
		}
		for (int i = 1; i <= n + 1; i ++) ans[i] += ans[i - 1];
		for (int i = 1; i <= n + 1; i ++) ans[i] += ans[i - 1];
	}
	
}

namespace MINIUM {
	
	int ans[MAXN];
	int ls[MAXN], rs[MAXN]; // find the first smaller/equal one
	stack<int> stk;
	
	void solve() {
		b[0] = -INF, b[n + 2] = -INF;
		while (!stk.empty()) { stk.pop(); } stk.push(0);
		for (int i = 1; i <= n + 1; i ++) {
			while (b[stk.top()] > b[i]) stk.pop();
			ls[i] = i - stk.top(); stk.push(i);
		}
		while (!stk.empty()) { stk.pop(); } stk.push(n + 2);
		for (int i = n + 1; i >= 1; i --) {
			while (b[stk.top()] >= b[i]) stk.pop();
			rs[i] = stk.top() - i; stk.push(i);
		}
		for (int i = 1; i <= n + 1; i ++) ans[i] = 0;
		for (int i = 1; i <= n + 1; i ++) {
			int small = min(ls[i], rs[i]);
			int big = max(ls[i], rs[i]);
			ans[1] += b[i];
			ans[small + 1] -= b[i];
			ans[big + 1] -= b[i];
			ans[small + big + 1] += b[i];
		}
		for (int i = 1; i <= n + 1; i ++) ans[i] += ans[i - 1];
		for (int i = 1; i <= n + 1; i ++) ans[i] += ans[i - 1];
	}
	
}

inline int anspos(int x) {
	return (MAXIUM :: ans[x + 1] - MINIUM :: ans[x + 1]) % (x * x);
}

signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	for (cin >> T; T --; ) {
		cin >> n; ans = 0;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		MAXIUM :: solve();
		MINIUM :: solve();
		for (int i = 1; i <= n; i ++) ans ^= anspos(i);
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：5)

胡了一下，和题解差不多，还挺棒的！

首先前 $50$ 分和正解没什么关系。看完 $50$ 分之后，我就想，他有 $O(n^2)$ 个区间，怎么做到 $O(n)$ 复杂度呢？

首先考虑一个区间的权值是多少。那么区间和放到前缀和上就是两项之差，而加了绝对值使得不需要考虑两项的前后关系。所以一个区间的权值就是前缀和数组上这一段最大值和最小值的差。

现在还是没有解决不能枚举区间的问题。我又想了两分钟，发现可以套路的改成枚举每个位置的贡献。每个位置作为最大值的区间是可以简单计算的，开一棵笛卡尔树就行。那么有了这个区间之后，我就突然会做了。因为某个数作为最大值一定是形如一个 $[l,r]$ 的区间，同时必须包含这个数的形式。可以发现，这里面长度为 $1$ 的区间有 $1$ 个，长度为 $2$ 的区间有 $2$ 个，这样子下去，最终形成的形状会是先长度增加 $1$ 方案数增加 $1$，中间的一段方案数不变，最后在减少到 $1$ 种。

这个结论说明，一个数对答案的贡献相当于一个先上升的等差数列，然后平，最后下降的等差数列的形式。所以维护一个二维差分数组即可。

时间复杂度 $O(n)$。

代码没写，感觉很好写。

---

## 作者：chenbs (赞：3)

有点麻烦的一道题，我们现从部分分开始讲。

## 50 分做法

首先做前缀和，设 $s_i = \sum_{j=1}^{i} a_j$，那么区间 $[l,r]$ 的权值就变为了：

$$\max_{l \le L \le R \le r} |s_R - s_{L-1}|$$

这里有一个绝对值，所以我们不用考虑 $L,R$ 的顺序，只需要让 $s_R$ 最大，$s_{L-1}$ 最小即可，上面那个式子可以进一步转化为：

$$\left( \max_{l \le i \le r} s_i \right) - \left(  \min_{l-1 \le i \le r-1} s_i \right)$$

那么我们用 ST 表维护区间最值，暴力枚举即可。

## 100 分做法

注意到，求答案不需要枚举所有区间，可以直接计算**每个数对答案的贡献**。

$\max$ 的部分和 $\min$ 的部分差不多，下面先分析 $\max$ 部分的贡献。设 $[L_i,R_i]$ 为 $a_i$ 作为最大值的范围（**两遍单调栈求出**），不妨设 $a_i$ 距离 $L_i$ 更近。

对于 $1 \le k \le i-L_i+1$ 的答案，此时两边都碰不到，有 $k \times a_i$ 的贡献；

![](https://cdn.luogu.com.cn/upload/image_hosting/a2nfsace.png)

对于 $i-L_i+1 < k \le R_i-i+1$ 的答案，此时可以碰到左边，有 $(i-L_i+1) \times a_i$ 的贡献；

![](https://cdn.luogu.com.cn/upload/image_hosting/i2fnbmuj.png)

对于 $R_i-i+1 < k \le R_i - L_i + 1$ 的答案，此时两边都可以碰到，有 $((R_i - L_i + 1) - k + 1) \times a_i$ 的贡献；

![](https://cdn.luogu.com.cn/upload/image_hosting/vh2eodfo.png)

对于这种区间加等差数列的形式，两个差分即可解决。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, top;
long long a[1000005], s[1000005], s2[1000005];
int l[1000005], r[1000005]; // 每个值贡献范围
long long x[1000005], x2[1000005]; // 类似一次函数形式的差分，x[i]*i+x2[i]
void calc(int f) {
	for(int i=0; i<=n; i++) {
		int dl=i-l[i]+1, dr=r[i]-i+1, len=r[i]-l[i]+1;
		if(dl>dr) swap(dl, dr);
		x[1]+=f*a[i], x[dl+1]-=f*a[i];
		x2[dl+1]+=f*dl*a[i], x2[dr+1]-=f*dl*a[i];
		// (len-i+1)*a[i] = (len+1)*a[i] + i*(-a[i])
		x2[dr+1]+=f*(len+1)*a[i], x2[len+1]-=f*(len+1)*a[i];
		x[dr+1]-=f*a[i], x[len+1]+=f*a[i];
	}
}
int main() {
	cin>>T;
	while(T--) {
		cin>>n;
		for(int i=0; i<=n+1; i++) x[i]=x2[i]=0;
//		max{l<=i<=r} s_i - min{l-1<=i<r} s_i

		for(int i=1; i<=n; i++) cin>>a[i], a[i]+=a[i-1];
		top=0, s2[0]=-1;
		for(int i=0; i<=n; i++) {
			while(top>0 && s[top]<=a[i]) top--; // 一边取等，一边不取等，就可以保证不重不漏
			l[i]=s2[top]+1;
			s[++top]=a[i], s2[top]=i;
		}
		top=0, s2[0]=n+1;
		for(int i=n; i>=0; i--) {
			while(top>0 && s[top]<a[i]) top--;
			r[i]=s2[top]-1;
			s[++top]=a[i], s2[top]=i;
		}
		calc(1);
		top=0, s2[0]=-1;
		for(int i=0; i<=n; i++) {
			while(top>0 && s[top]>=a[i]) top--;
			l[i]=s2[top]+1;
			s[++top]=a[i], s2[top]=i;
		}
		top=0, s2[0]=n+1;
		for(int i=n; i>=0; i--) {
			while(top>0 && s[top]>a[i]) top--;
			r[i]=s2[top]-1;
			s[++top]=a[i], s2[top]=i;
		}
		calc(-1);
		
		for(int i=1; i<=n+1; i++) x[i]+=x[i-1], x2[i]+=x2[i-1];
		long long ans=0;
		for(int i=2; i<=n+1; i++) ans^=(x[i]*i+x2[i])%(1ll*(i-1)*(i-1));
		cout<<ans<<'\n';

	}
	return 0;
}
```

---

## 作者：冷却心 (赞：2)

注意到有区间和，于是记 $s_i=\sum_{j=1}^i a_i$ 且 $s_0 = 0$。那么一个区间 $[l,r]$ 的权值即为：

$$ \max_{l-1\le L < R \le r} |s_R-s_L|. $$

由于有绝对值，所以上述式子就等于 $\max s_i - \min s_i$。我们记 $\mathrm{ans}_k$ 表示长度为 $k$ 的子区间的答案，那么：

$$\mathrm{ans}_k=\sum_{i=0}^{n-k}\max_{j=i}^{i+k} s_j - \min_{j=i}^{i+k} s_j.$$

最大值和最小值的贡献本质相同，不失一般性的，我们只讨论最大值，最小值可以把整个前缀和序列取相反数就变成最大值了。区间最值那么考虑建大根笛卡尔树。我们设当前在点 $u$，子树的区间为 $[l,r]$，其父亲为 $f$。

看了一圈题解区，都是讨论跨过当前点的区间，比较不好写（并非），这里来一个更简单的方法。先说结论，我们对任意包含于 $[l,r]$ 的子区间都贡献 $a_u-a_f$，不需要跨越当前节点。这样如果贡献的区间没有跨过 $u$，那么 $a_u$ 的贡献会被其子节点删掉，所以是对的。形式化的，我们设 $l=r-l+1$，那么对于所有 $1\le k \le l$，有 $\mathrm{ans}_k\gets \mathrm{ans}_k + (l-k)(a_u-a_f).$ 这是一个前缀加等差数列，二维差分即可。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e6 + 10;
int n; LL A[N], Ans[N], d1[N], d2[N];
int stk[N], tp, ls[N], rs[N];

void DFS(int u, int l, int r, int f) {
	if (!u || r == l) return ;
	DFS(ls[u], l, u - 1, u); DFS(rs[u], u + 1, r, u);
	int len = r - l + 1; LL t = A[u] - A[f];
	d1[1] += (len - 1) * t; d2[2] -= t; d2[len + 1] += t;
	return ;
}

void Solve() {
	tp = 0; for (int i = 1; i <= n; i ++) ls[i] = rs[i] = 0;
	for (int i = 1; i <= n; i ++) {
		while (tp && A[stk[tp]] <= A[i]) ls[i] = stk[tp --];
		if (tp) rs[stk[tp]] = i;
		stk[++ tp] = i;
	}
	DFS(stk[1], 1, n, 0); return ;
}

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n; ++ n;
		for (int i = 2; i <= n; i ++) cin >> A[i], A[i] += A[i - 1];
		Solve(); 
		for (int i = 1; i <= n; i ++) A[i] = -A[i];
		Solve(); 
		LL res = 0;
		for (int i = 1; i <= n; i ++) d2[i] = d2[i - 1] + d2[i];
		for (int i = 1; i <= n; i ++) Ans[i] = Ans[i - 1] + d2[i] + d1[i];
		for (int i = 1; i <= n; i ++) res ^= Ans[i] % (1ll * i * i);
		cout << res << "\n"; 
		for (int i = 1; i <= n + 1; i ++) Ans[i] = d1[i] = d2[i] = 0;
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：1)

# P12498 题解

赛时一发过蓝题。

## 思路

单调栈与差分套差分。

$[l,r]$ 的权值为 $\max\limits_{l \le L \le R \le r}|\sum\limits_{i=L}^{R}a_i|$，容易发现绝对值内的式子可以用前缀和换掉，设 $p_k = \sum\limits_{i=1}^{k}a_i$，则 $[l,r]$ 的权值为 $\max\limits_{l \le L \le R \le r}|p_R-p_{L-1}|$，将绝对值拆掉，转换为 $\max\limits_{l \le L,R \le r}(p_R-p_{L-1})$，为了让二者之差最大，显然 $p_R$ 尽量大，$p_{L-1}$ 尽量小，即 $(\max\limits_{l \le R \le r}p_R) - (\min\limits_{l-1 \le L \le r-1} p_L)$，会发现这两部分没啥关系，可以拆开求。

对于 $0 \le i \le n$ 的每一个 $i$，我们可以求出当 $[l,r]$ 的最大值为 $p_i$ 时 $l$ 和 $r$ 的取值范围，设 $mxl_i$ 表示 $i$ 往左的第一个 $\ge i$ 的数字，$mxr_i$ 表示 $i$ 往右的第一个 $> i$ 的数字，那么，当 $mxl_i < l \le i$ 且 $i \le r < mxr_i$ 时，$p_i$ 是区间 $[l,r]$ 中的最大值。最小值也同理。这四个数据可以跑四次单调栈求出来，要注意当 $p_i = p_j$ 时的情况，等号应该放在左右其中一边。

接下来考虑如何统计长度为 $k$ 的区间权值和。对于 $i$，令 $L=i-mxl_i-1$，表示左端点到 $i$ 的距离 $l'$ 有 $0,1,2,\cdots,L$ 这 $L+1$ 种选择，令 $R=mxr_i-i-1$，表示右端点到 $i$ 的距离有 $0,1,2,\cdots,R$ 这 $R+1$ 种选择。

当左边取 $0$，右边取 $0$ 到 $R$ 的数时，区间长度分别为 $0,1,2,\cdots,R$。

当左边取 $1$，区间长度分别为 $1,2,3,\cdots,R+1$。

依此类推。

当左边取 $L$，区间长度分别为 $L,L+1,L+2,\cdots,L+R$。

也就是说 $p_i$ 作为最大值会对上述列出的所有长度产生贡献。

如果暴力解，时间复杂度是 $\mathcal{O}(n^2)$ 的。

如果用差分来做，我们很显然可以将 $0,1,2,\cdots,L$ 这些位置加上 $p_i$，将 $R+1,R+2,R+3,\cdots,L+R+1$ 这些位置减去 $p_i$，时间复杂度降到 $\mathcal{O}(n)$。

会发现可以再套一次差分，也就是将 $0$ 加上 $p_i$，$L+1$ 减掉 $p_i$，$R+1$ 减掉 $p_i$，$L+R+2$ 加上 $p_i$，时间复杂度降到 $\mathcal{O}(1)$。

对于最小值的处理也是这样，不再赘述。

求出最终的序列，就是题目中的 $ans$，由于长度为 $0$ 的无需统计，则将下标 $1$ 到 $n$ 的答案统计一下即可。

## 代码

```cpp
const int N=1000005;
const int inf=1e18;

int T,n;
int a[N],p[N];
int mxl[N],mxr[N];
int mnl[N],mnr[N];
stack<int> stk;
int s[N];

i32 main() {
    read(T);
    while (T--) {
        read(n);
        _rep(i,1,n) s[i]=0;
        _rep(i,1,n) read(a[i]);
        _rep(i,1,n) p[i]=p[i-1]+a[i];
        _rep(i,0,n) {
            while (!stk.empty() && p[stk.top()]<p[i]) stk.pop();
            if (stk.empty()) mxl[i]=-1;
            else mxl[i]=stk.top();
            stk.emplace(i);
        }
        while (!stk.empty()) stk.pop();
        _rrep(i,n,0) {
            while (!stk.empty() && p[stk.top()]<=p[i]) stk.pop();
            if (stk.empty()) mxr[i]=n+1;
            else mxr[i]=stk.top();
            stk.emplace(i);
        }
        while (!stk.empty()) stk.pop();
        _rep(i,0,n) {
            while (!stk.empty() && p[stk.top()]>p[i]) stk.pop();
            if (stk.empty()) mnl[i]=-1;
            else mnl[i]=stk.top();
            stk.emplace(i);
        }
        while (!stk.empty()) stk.pop();
        _rrep(i,n,0) {
            while (!stk.empty() && p[stk.top()]>=p[i]) stk.pop();
            if (stk.empty()) mnr[i]=n+1;
            else mnr[i]=stk.top();
            stk.emplace(i);
        }
        while (!stk.empty()) stk.pop();
        _rep(i,0,n) {
            int l=i-mxl[i]-1,r=mxr[i]-i-1;
            s[0]+=p[i],s[r+1]-=p[i];
            s[l+1]-=p[i]; if (l+r+2<=n) s[l+r+2]+=p[i];
            l=i-mnl[i]-1,r=mnr[i]-i-1;
            s[0]+=-p[i],s[r+1]-=-p[i];
            s[l+1]-=-p[i]; if (l+r+2<=n) s[l+r+2]+=-p[i];
        }
        _rep(t,1,2) _rep(i,1,n) s[i]=s[i-1]+s[i];
        int ans=0;
        _rep(i,1,n) ans^=(s[i]%(i*i));
        writeln(ans);
    }
    return 0;
}
```

---

