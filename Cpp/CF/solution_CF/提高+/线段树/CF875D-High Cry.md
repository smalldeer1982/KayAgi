# High Cry

## 题目描述

Disclaimer: there are lots of untranslateable puns in the Russian version of the statement, so there is one more reason for you to learn Russian :)

Rick and Morty like to go to the ridge High Cry for crying loudly — there is an extraordinary echo. Recently they discovered an interesting acoustic characteristic of this ridge: if Rick and Morty begin crying simultaneously from different mountains, their cry would be heard between these mountains up to the height equal the bitwise OR of mountains they've climbed and all the mountains between them.

Bitwise OR is a binary operation which is determined the following way. Consider representation of numbers $ x $ and $ y $ in binary numeric system (probably with leading zeroes) $ x=x_{k}...\ x_{1}x_{0} $ and $ y=y_{k}...\ y_{1}y_{0} $ . Then $ z=x | y $ is defined following way: $ z=z_{k}...\ z_{1}z_{0} $ , where $ z_{i}=1 $ , if $ x_{i}=1 $ or $ y_{i}=1 $ , and $ z_{i}=0 $ otherwise. In the other words, digit of bitwise OR of two numbers equals zero if and only if digits at corresponding positions is both numbers equals zero. For example bitwise OR of numbers $ 10=1010_{2} $ and $ 9=1001_{2} $ equals $ 11=1011_{2} $ . In programming languages C/C++/Java/Python this operation is defined as «|», and in Pascal as «or».

Help Rick and Morty calculate the number of ways they can select two mountains in such a way that if they start crying from these mountains their cry will be heard above these mountains and all mountains between them. More formally you should find number of pairs $ l $ and $ r $ ( $ 1<=l&lt;r<=n $ ) such that bitwise OR of heights of all mountains between $ l $ and $ r $ (inclusive) is larger than the height of any mountain at this interval.

## 说明/提示

In the first test case all the ways are pairs of mountains with the numbers (numbering from one):

 $ (1,4),(1,5),(2,3),(2,4),(2,5),(3,4),(3,5),(4,5) $ In the second test case there are no such pairs because for any pair of mountains the height of cry from them is $ 3 $ , and this height is equal to the height of any mountain.

## 样例 #1

### 输入

```
5
3 2 1 6 5
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4
3 3 3 3
```

### 输出

```
0
```

# 题解

## 作者：ii45i4 (赞：8)

[CF875D. High Cry](https://www.luogu.com.cn/problem/CF875D)

7KByte 的题解里，所谓的『极值分治』，其实就是笛卡尔树。在一类和最小值 / 最大值相关的问题中，笛卡尔树是一个不错的思考方向。

然而 7KByte 只提出了 $O(n \log^2 n)$ 的做法，但 $\text{or}$ 的性质那么强，我们理应有更优的做法。

---

和其它题解一样，还是先做补集转化，答案为总区间数量减去 $\text{or} = \max$ 的区间数量。

建出序列的笛卡尔树。对于一个点 $i$，设它的子树对应的区间为 $[x_i, y_i]$，那么以 $a_i$ 为 $\max$ 的区间 $[l, r]$ 一定满足 $l \in [x_i, i]$ 且 $r \in [i, y_i]$。

还有一个限制是 $\text{or} = \max$。这等价于 $\forall x \in [l, r]$，$x~\text{or}~a_i = 0$。那么找到**最大的 $\text{vl} \in [l, i - 1]$，满足 $a_{\text{vl}}~\text{or}~a_i \ne 0$**；同理找到**最小的 $\text{vr} \in [i + 1, r]$，满足 $a_{\text{vr}}~\text{or}~a_i \ne 0$**。那么满足条件的区间个数为 $(i - \text{vl}) \cdot (\text{vr} - i)$。

求 $\text{vl}$ 和 $\text{vr}$ 是复杂度瓶颈。

## Algorithm 1. $O(n \log V)$

其中 $V$ 是值域。

假设求 $\text{vl}$：我们对于每个 $k \in [0, \log(V)]$，**预处理出 $1 \sim i$ 中 $a_j$ 出现 $2^k$ 的最大的 $j$，记为 $\text{fl}(i, k)$**；对于每个没有在 $a_i$ 中出现的 $2^k$，取 $\max\{\text{fl}(i - 1, k)\}$ 即为 $\text{vl}$。$\text{vr}$ 的求法是类似的。

## Algorithm 2. $O(n \log n)$

当 $l$ 固定时，区间 $[l, r]$ 的 $\text{or}$ 一定随 $r$ 单调不降。二分即可。

这里给出 Algorithm 2 的代码。

```cpp
#include <bits/stdc++.h>
typedef long long LL; const int N = 2e5 + 7, LogN = 20, LogV = 30;
int n, a[N]; LL ans = 0;
struct ST{
	int lg2[N], f[N][LogN], s[N][LogN];
	void build() {
		lg2[0] = -1;
		for(int i = 1; i <= n; i++) lg2[i] = lg2[i >> 1] + 1, f[i][0] = i, s[i][0] = a[i];
		for(int i = 1; i <= lg2[n]; i++)
			for(int l = 1; l + (1 << i) - 1 <= n; l++) {
				if(a[f[l][i - 1]] > a[f[l + (1 << (i - 1))][i - 1]]) f[l][i] = f[l][i - 1];
				else f[l][i] = f[l + (1 << (i - 1))][i - 1];
				s[l][i] = s[l][i - 1] | s[l + (1 << (i - 1))][i - 1];
			}
	}
	int qmax(int l, int r) {
		int len = lg2[r - l + 1];
		if(a[f[l][len]] > a[f[r - (1 << len) + 1][len]]) return f[l][len];
		else return f[r - (1 << len) + 1][len];
	}
	int qor(int l, int r) {
		int len = lg2[r - l + 1];
		return s[l][len] | s[r - (1 << len) + 1][len];
	}
} st;
void dfs(int l, int r) {
	if(l == r) return ans++, void();
	int mid = st.qmax(l, r), vl = l - 1, vr = r + 1;
	if(st.qor(l, mid) != a[mid]) {
		int pl = l, pr = mid;
		while(pl < pr) {
			int pmid = (pl + pr + 1) >> 1;
			if(st.qor(pmid, mid) == a[mid]) pr = pmid - 1;
			else pl = pmid;
		}
		vl = pl;
	}
	if(st.qor(mid, r) != a[mid]) {
		int pl = mid, pr = r;
		while(pl < pr) {
			int pmid = (pl + pr) >> 1;
			if(st.qor(mid, pmid) == a[mid]) pl = pmid + 1;
			else pr = pmid;
		}
		vr = pl;
	}
	ans += LL(mid - vl) * (vr - mid);
	if(l != mid) dfs(l, mid - 1);
	if(mid != r) dfs(mid + 1, r);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	st.build(), dfs(1, n), printf("%lld\n", n * LL(n + 1) / 2 - ans);
	return 0;
}
```


---

## 作者：Limit (赞：6)

# 题目大意

给出一个序列 $a$,求有多少子串满足子串的 $\max$ 严格小于子串中所有数的或值.

# 分析

显然一个子串的或者肯定是大于等于子串的 $\max$,那么问题就变成了要求出有多少的子串的或值等于子串的 $\max$.再经过简单的分析,不难发现如果子串最大值的二进制中第 $k$ 位为 $0$,但子串中存在某数二进制下第 $k$ 位的值为 $1$,那么这个子串的或值必然大于最大值(最大值与这个数的或值必然大于最大值).

考虑对每个数计算以当前数为最大值时的不合法的子串数,即计算有多少子串的最大值在某个位置($i$)时有异或值等于最大值.那么这个子串的左端点($l$),右端点($r$)需要满足以下条件:

1.  $l\leq i\leq r$($i$ 位置必须在子串中)
2.  $\max\limits_{l\leq j\leq r}a_j=a_l\lor a_{l+1}\lor a_{l+2}\lor\dots\lor a_{r-2}\lor a_{r-1}\lor a_r=a_i$(子串的最大值等于子串的异或值等于 $a_i$)

于是可以处理出以某个数为最大值的区间以及对于某个数所不存在的二进制的位置上一次和下一次出现的位置,这样就可以通过简单计算计算出结果.

但是如果在序列中存在多个相同的数可能会出点小问题.

如第二个样例中的 `3 3 3 3`,直接计算某个数为最大值的区间会计算的结果都是 $[1,4]$,但这样在后面的计算中会出问题,但 $[1,4],[2,4],[3,4],[4,4]$ 就不会有问题了,所以可以强制某个数是某个区间的最大值需要满足在这个数之前(或者之后)不存在大于等于这个数的数.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
namespace IO
//快读模板
using namespace IO;
using namespace std;
const int MAXN=2e5+5;
int n;
int place[100];
struct Number
{
	int num,left,right,l,r;//每个位置的数,这个数不存在的二进制位置上一次出现的位置,下一次出现的位置,这个为最大值的区间的左端点,右端点
}arr[MAXN];
int st[MAXN],top=0;
int main()
{
	Read(n);
	REP(i,1,n)
	{
		Read(arr[i].num);
		arr[i].left=0;
		arr[i].right=n+1;
		REP(j,0,31)
		{
			if(arr[i].num&(1<<j))//如果这个数的二进制中存在第 j 位,那么就把第 j 位的上一次出现位置变为 i
			{
				place[j]=i;
			}
			else
			{
				arr[i].left=Max(arr[i].left,place[j]);//否则就与最近出现位置取更近的位置
			}
		}
		while(top&&arr[st[top]].num<arr[i].num)//计算左端点时用 <,右端点用 <=(反之同理)
		{
			top--;
		}
		arr[i].l=st[top];//单调栈处理出这个数为最大值的区间的左端点(右端点同理)
		st[++top]=i;
	}
	top=0;
	REP(i,0,31)
	{
		place[i]=n+1;
	}
	DOW(i,n,1)//同理
	{
		REP(j,0,31)
		{
			if(arr[i].num&(1<<j))
			{
				place[j]=i;
			}
			else
			{
				arr[i].right=Min(arr[i].right,place[j]);
			}
		}
		while(top&&arr[st[top]].num<=arr[i].num)
		{
			top--;
		}
		arr[i].r=st[top]?st[top]:n+1;
		st[++top]=i;
	}
	long long answer=1ll*n*(n+1)>>1;//总方案数
	REP(i,1,n)
	{
		answer-=1ll*(i-Max(arr[i].l,arr[i].left))*(Min(arr[i].r,arr[i].right)-i);//需要同时满足两个限制,所以直接对区间的端点取距离 i 近的那个就行了
	}
	Writeln(answer);
	return 0;
}
```

---

## 作者：1saunoya (赞：4)

考虑 or 不会超过 $\log$ 次变化，可以二分出来一个位置随便做，这个方法不在阐述。

这其实可以用单调栈，考虑一个数作为一个区间的最大值，那么如果或值比这个数要大，当且仅当有一个二进制位是最大值所不存在的，所以左右端点可以正反处理，然后做完了。

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x,I=y+1;i<I;++i)
#define per(i,x,y) for(int i=x,I=y-1;i>I;--i)
using namespace std;
using ll=long long;
void cmax(int&x,const int&y){x=x>y?x:y;}
void cmin(int&x,const int&y){x=x<y?x:y;}
template<class T>istream&operator>>(istream&in,vector<T>&V){for(auto&x:V)in>>x;return in;}
template<class T>ostream&operator<<(ostream&out,const vector<T>&V){for(auto x:V)out<<x<<' ';return out;}
template<class T>void sort(vector<T>&V){sort(V.begin(),V.end());}
template<class T>void reverse(vector<T>&V){reverse(V.begin(),V.end());}
template<class T>int SZ(const vector<T>&V){return (int)V.size();}
void debug(){cerr<<"whxorz"<<'\n';}

const int N = 200000 + 5;
int n, a[N];
int L[N], R[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	static int st[N], top;
	st[top = 0] = 0;
	for (int i = 1; i <= n; i++) {
		while (top && a[st[top]] < a[i]) { R[st[top--]] = i; }
		L[i] = st[top]; st[++top] = i;
	}
	while (top) R[st[top--]] = n + 1;
	for (int i = 1; i <= n; i++) {
		L[i]++;
		R[i]--;
	}
	static int tmpL[N], tmpR[N], tmp[32];
	for (int i = 1; i <= n; i++) tmpL[i] = 0;
	for (int j = 0; j < 31; j++) tmp[j] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 31; j++)
			if (a[i] >> j & 1)
				tmp[j] = i;
			else
				cmax(tmpL[i], tmp[j]);
	}
	for (int i = 1; i <= n; i++) tmpR[i] = n + 1;
	for (int j = 0; j < 31; j++) tmp[j] = n + 1;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < 31; j++)
			if (a[i] >> j & 1)
				tmp[j] = i;
			else
				cmin(tmpR[i], tmp[j]);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		if (L[i] <= tmpL[i])
			ans += 1ll * (R[i] - i + 1) * (tmpL[i] - L[i] + 1);
		if (tmpR[i] <= R[i])
			ans += 1ll * (i - L[i] + 1) * (R[i] - tmpR[i] + 1);
		if (L[i] <= tmpL[i] && tmpR[i] <= R[i])
			ans -= 1ll * (tmpL[i] - L[i] + 1) * (R[i] - tmpR[i] + 1);
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：free_fall (赞：3)

# 题目大意
给你一个长度为 $n$ 的数列 $a_i$，求满足区间或 $>$ 区间最大值的区间个数。
# 思路
看到题目后没有思路，那就从最暴力的方式开始，再继续优化。
## 方案一
枚举每一个区间，再分别求出区间最大值和区间最大或，如果该区间合法就将答案加一。时间复杂度算都不用算，肯定超时。
## 方案二
不难看出，方案一中有大部分时间浪费在计算区间最大值和区间最大或上，因为最大值和最大或的计算都有可重复性，所以我们可以使用 ST 表来优化搜索区间最大值和区间最大或。此时时间复杂度为 $O(n^2)$，看了一眼数据范围，还是会时间超限。
## 方案三
枚举每一个区间显然效率太低，我们可以枚举区间最大值，然后找到它前面最后一个不大于它的数，下标记为 $l _ 1$，再找到它前面第一个拥有它没有的二进制位的数，下标记为 $l _ 2$，$r _ 1$ 和 $r _ 2$ 同理。

所以根据乘法原理，区间数等于前面的数的个数乘上后面的数的个数，然后在 $l _ 1$、$l _ 2$ 之间和 $r _ 1$、$r _ 2$ 之间的部分要去重，这样从 $1$ 到 $n$ 依次枚举过来就能得到答案。

推导公式如下，将下标为 $i$ 时的合法区间数记为 $a_i$，注意去掉重复的部分：

$\left\{\begin{matrix}
a_i=a_i+(l2-l1+1)\times(r1-i+1)\left ( l1<l2 \right )  
 \\
a_i=a_i+(i-l1+1)\times(r1-r2+1)\left ( r2<r1 \right ) 
 \\
a_i=a_i-(l2-l1+1)\times (r1-r2+1)\left ( r1<l2,l1<l2 \right ) 
\end{matrix}\right.$

在寻找这些数时，可以使用倍增 ST 表优化，这样时间复杂度降到了 $O(n\log n)$，就能过掉这道题了，代码也非常简短。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],st[N][20][2];
long long ans;
void init(){
	for(int i=1;i<=n;i++){
		st[i][0][0]=st[i][0][1]=a[i];
	}
	for(int j=1;1<<j<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j][0]=max(st[i][j-1][0],st[i+(1<<j-1)][j-1][0]);
			st[i][j][1]=st[i][j-1][1]|st[i+(1<<j-1)][j-1][1];
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	init();
	for(int i=1;i<=n;i++){
		int l1=i,l2=i,r1=i,r2=i;
		for(int j=18;j>=0;j--){
			if(l1>(1<<j)&&st[l1-(1<<j)][j][0]<a[i])l1-=1<<j;
		}
		for(int j=18;j>=0;j--){
			if(r1+(1<<j)<=n&&st[r1+1][j][0]<=a[i])r1+=1<<j;
		}
		for(int j=18;j>=0;j--){
			if(l2>(1<<j)&&(a[i]|st[l2-(1<<j)][j][1])==a[i])l2-=1<<j;
		}
		l2--;
		for(int j=18;j>=0;j--){
			if(r2+(1<<j)<=n&&(a[i]|st[r2+1][j][1])==a[i])r2+=1<<j;
		}
		r2++;
		if(l2>=l1)ans+=1ll*(l2-l1+1)*(r1-i+1);
		if(r1>=r2)ans+=1ll*(i-l1+1)*(r1-r2+1);
		if(l2>=l1&&r1>=r2)ans-=1ll*(l2-l1+1)*(r1-r2+1);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：lyt_awa (赞：2)

## 思路
可以枚举最大值，对于每一个 $a_{i}$ 求出左边第一个比它大的数的下标和右边第一个比它大的数的下标 $l_1$ 和 $r_1$，再求出左边第一个和它亦或后的值比它大的数的下标和右边第一个和它亦或后的值比它大的数的下标 $l_2$ 和 $r_2$。

即求最大的区间 $\left ( l_1, r_1 \right ) $ 使得 $\max_{j\in \left ( l_1, r_1 \right )} a_{j} = a_i$。

再求最大的区间 $\left ( l_2, r_2 \right ) $ 使得 $a_{l_2+1}\operatorname{or}a_{l_2+2}\operatorname{or}...\operatorname{or}a_{r_2-1} = a_i$。

## 计算答案（**容斥**）

左端点在 $\left ( l_1, l_2 \right ] $ 内，这时右端点可以取 $\left [ i, r_1 \right ) $。

右端点在 $\left [ r_2, r_1 \right ) $ 内，这时左端点可以取 $\left ( l_1, i \right ]$。

左端点在 $\left ( l_1, l_2 \right ] $ 内，右端点在 $\left [ r_2, r_1 \right ) $ 内，会重复算减去。

最后要注意一个区间内多个最大值的情况，在多个最大值中只算最左边的就可以了。

------------
最后代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200003],st[200003][23],b[200003][23],n;
inline void init(int l) {
	st[l][0]=a[l],b[l][0]=a[l];
	for(int i=1; i<=20; i++)
		st[l][i]=max(st[l][i-1],st[min(l+(1<<(i-1)),n)][i-1]),
		         b[l][i]=b[l][i-1]|b[min(l+(1<<(i-1)),n)][i-1];
}
inline int rmq1(int l,int r) {
	int L=log(r-l+1)/log(2);
	return max(st[l][L],st[min(r-(1<<L)+1,n)][L]);
}
inline int rmq2(int l,int r) {
	int L=log(r-l+1)/log(2);
	return b[l][L]|b[min(r-(1<<L)+1,n)][L];
}
long long bs(int x) {
	int l,r,ans1=x,ans2=x;
	l=1,r=x-1;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(rmq1(mid,x-1)<a[x] && rmq2(mid,x)<=a[x]) ans1=mid,r=mid-1;
		else l=mid+1;
	}
	l=x+1,r=n;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(rmq1(x+1,mid)<=a[x] && rmq2(x,mid)<=a[x]) ans2=mid,l=mid+1;
		else r=mid-1;
	}
	return (ans2-x+1)*(x-ans1+1);
}
signed main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=n; i>=1; i--) init(i);
	long long ans=1LL*n*(n+1LL)/2LL;
	for(int i=1; i<=n; i++) ans-=bs(i);
	cout<<ans<<endl;
	return 0;
}
```
求 $l_1,r_1,l_2,r_2$ 用 **ST 表**的时间复杂度为 $O(n\log n)$。

还有 $l_1$ 和 $r_1$ 可以用**单调栈** $O(n)$ 预处理，会快一点点。

---

## 作者：dead_X (赞：2)

## 题意
翻译已经有很精简的了，不再赘述。
## 思路
**Main Idea:反面考虑，st-table，二分**


首先，我们发现虽然满足区间或大于区间最大值的区间个数很难求，但它的反面——区间或等于区间最大值很好求。

接下来考虑怎么求区间的或等于区间最大值的区间。

显而易见的思路是分别统计最大值为某个数的区间，而这个区间可能包含最大值左边的一些数和最大值右边的一个数。于是，你需要找到每个最大值中满足要求的区间的最左端点和最右端点。

然后，你又发现这个最左/右端点有单调性，那么直接上 st-table 预处理区间 sum 和 or，加上二分统计，最后把两边扩展的长度乘起来，就是这个数对应的不合法区间数量，最后用总区间数量减掉就可以了。

然后看了一眼数据范围，放了 $O(nlogn)$ 过，于是我们可以用上述暴力水过去。
## 代码
```
#include<bits/stdc++.h>
#define int long long 
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
int a[200003],st[200003][23],qwq[200003][23],n=read();
inline void init(int l)
{
	st[l][0]=a[l],qwq[l][0]=a[l];
	for(int i=1; i<=20; i++) 
    st[l][i]=max(st[l][i-1],st[min(l+(1<<(i-1)),n)][i-1]),
    qwq[l][i]=qwq[l][i-1]|qwq[min(l+(1<<(i-1)),n)][i-1];
}
inline int query(int l,int r)
{
	int L=log(r-l+1)/log(2);
	return max(st[l][L],st[min(r-(1<<L)+1,n)][L]);
}
inline int qwqry(int l,int r)
{
	int L=log(r-l+1)/log(2);
	return qwq[l][L]|qwq[min(r-(1<<L)+1,n)][L];
}
long long bs(int x)
{
    int l,r,ans1=x,ans2=x;
    l=1,r=x-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(query(mid,x-1)<a[x] && qwqry(mid,x)<=a[x]) ans1=mid,r=mid-1; else l=mid+1;
    }
    l=x+1,r=n;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(query(x+1,mid)<=a[x] && qwqry(x,mid)<=a[x]) ans2=mid,l=mid+1; else r=mid-1;
    }
    return (ans2-x+1)*(x-ans1+1);
}
signed main()
{
    for(int i=1; i<=n; i++) a[i]=read();
    for(int i=n; i>=1; i--) init(i);
    long long ans=1LL*n*(n+1LL)/2LL;
    for(int i=1; i<=n; i++) ans-=bs(i);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：comcopy (赞：1)

发现题解区里有二分 + ST 表 $O(N\log^2N)$ 的，但是仔细一思量，发现如果不用 $O(1)$ 的方法跳而用 $O(\log n)$ 的方法跳，这样可以省掉一个二分，最后时间复杂度是一样的且代码貌似更可观一点。(个人感觉。)

大体思路与题解是一样的，不过我们是暴力枚举最小值，然后 ST 表找端点。

所以就过来水一发题解了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
ll ans;
int mx[N][19],st[N][19],n,a[N];
void init(){
	for(int j=1;j<=18;++j)
		for(int i=1;i+(1<<j)-1<=n;++i){
			mx[i][j]=max(mx[i][j-1],mx[i+(1<<j-1)][j-1]);
			st[i][j]=st[i][j-1]|st[i+(1<<j-1)][j-1];
		}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		mx[i][0]=st[i][0]=a[i]; 
	}
	init();
	for(int i=1;i<=n;++i){
		int l1=i,l2=i,r1=i,r2=i;
        //暴力枚举每个点为最小值。
		for(int j=18;j>=0;--j)
			if(l1>(1<<j)&&mx[l1-(1<<j)][j]<a[i])l1-=(1<<j);
		for(int j=18;j>=0;--j)
			if(r1+(1<<j)<=n&&mx[r1+1][j]<=a[i])r1+=(1<<j);
		for(int j=18;j>=0;--j)
			if(l2>(1<<j) && (a[i]|st[l2-(1<<j)][j])==a[i])l2-=(1<<j);
		--l2;
		for(int j=18;j>=0;--j)
			if(r2+(1<<j)<=n && (st[r2+1][j]|a[i])==a[i]) r2+=(1<<j);
		++r2;
		if(l2>=l1)ans+=1ll*(l2-l1+1)*(r1-i+1);
		if(r1>=r2)ans+=1ll*(i-l1+1)*(r1-r2+1);
		if(l2>=l1 && r1>=r2)ans-=1ll*(l2-l1+1)*(r1-r2+1);
	}
	cout<<ans<<endl;
	return(0-0);
}
```


---

## 作者：7KByte (赞：1)

提供一个更简单的方法。

需要求区间最大值小于区间或的区间个数。

我们需要先预处理st表使得能够$\rm O(1)$求出区间或和区间最大值。

那么我们直接上极值分治，以区间最大值所在的位置为分治中点，枚举较小一段的端点，另一个端点可以通过二分求得。

由于极值分治的复杂度也是$\rm O(N\log N)$，算上二分总复杂度为$\rm O(N\log^2 N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int cur,n,a[N],f[N][18],g[N][18],t,bt[N];long long ed;
inline int ck(int x,int y){return a[x]>a[y]?x:y;}
inline int ask(int l,int r){
	cur=bt[r-l+1];
	return ck(f[l][cur],f[r-(1<<cur)+1][cur]);
}
inline int get(int l,int r){
	cur=bt[r-l+1];
	return g[l][cur]|g[r-(1<<cur)+1][cur];
}
void calc(int l,int r){
	if(l>=r)return;
	int mid=ask(l,r);
	calc(l,mid-1);calc(mid+1,r);
	int lim=a[mid];
	if(mid<=((l+r)>>1)){
		rep(i,l,mid){
			int L=mid,R=r,ans=r+1;
			while(L<=R){
				int cur=(L+R)>>1;
				if(get(i,cur)>lim)ans=cur,R=cur-1;
				else L=cur+1;
			}
			ed+=r+1-ans;
		}
	}
	else{
		rep(i,mid,r){
			int L=l,R=mid,ans=l-1;
			while(L<=R){
				int cur=(L+R)>>1;
				if(get(cur,i)>lim)ans=cur,L=cur+1;
				else R=cur-1;
			}
			ed+=ans-l+1;
		}
	}
}
int main(){
	scanf("%d",&n);t=log2(n);bt[0]=-1;
	rep(i,1,n)bt[i]=bt[i>>1]+1;
	rep(i,1,n)scanf("%d",&a[i]),g[i][0]=a[i],f[i][0]=i;
	rep(j,1,t)rep(i,1,n-(1<<j)+1)f[i][j]=ck(f[i][j-1],f[i+(1<<(j-1))][j-1]),g[i][j]=g[i][j-1]|g[i+(1<<(j-1))][j-1];
	calc(1,n);printf("%lld\n",ed);return 0;
}
```

---

## 作者：happybob (赞：0)

很套路的一个题。

首先发现，当左端点固定，随着右端点增加，区间 $\operatorname{or}$ 和区间 $\max$ 都是单调不递减的。

但是这个性质还不够强！我们发现，左端点固定，右端点增加时，每一次区间 $\operatorname{or}$ 发现改变，二进制至少有一位从 $0$ 变 $1$.这样，在 $O(\log v)$ 的变化数量级内，就会每一位都变成 $0$。

所以我们处理这个问题的一个经典套路就是枚举左端点， $O(\log v)$ 次二分，每次二分求出右端点的一段，使得区间 $\operatorname{or}$ 为一个定值。接着在这个区间内，$\max$ 也是单调的，再二分一次就好了。使用 ST 表维护，复杂度 $O(n \log n \log v)$。

除了 $\operatorname{or}$，其实 $\operatorname{and}$，$\gcd$，$\operatorname{lcm}$ 等都有这样的性质。

代码使用反面考虑，求出区间 $\operatorname{or} \leq $ 区间 $\operatorname{max}$ 的个数，然后用总区间个数减去他即为答案。

```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#pragma GCC target("avx,sse,sse2,sse3,popcnt")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

const int N = 2e5 + 5;

int LG2[N], n, a[N];
long long ans = 0LL;

class ST1
{
public:
	int f[N][30];
	void Init()
	{
		for (int i = 1; i <= n; i++)
		{
			f[i][0] = a[i];
		}
		for (int j = 1; j <= LG2[n]; j++)
		{
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
			{
				f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	int query(int l, int r)
	{
		int p = LG2[r - l + 1];
		return max(f[l][p], f[r - (1 << p) + 1][p]);
	}
}s1;

class ST2
{
public:
	int f[N][30];
	void Init()
	{
		for (int i = 1; i <= n; i++)
		{
			f[i][0] = a[i];
		}
		for (int j = 1; j <= LG2[n]; j++)
		{
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
			{
				f[i][j] = f[i][j - 1] | f[i + (1 << (j - 1))][j - 1];
			}
		}
	}
	int query(int l, int r)
	{
		int p = LG2[r - l + 1];
		return f[l][p] | f[r - (1 << p) + 1][p];
	}
}s2;

int main()
{
	for (int i = 2; i < N; i++)
	{
		LG2[i] = LG2[i / 2] + 1;
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	s1.Init();
	s2.Init();
	for (int i = 1; i <= n; i++)
	{
		int nowval = a[i], nowl = i, lastpos = i;
		while (true)
		{
			int l = nowl, r = n, resplace = 0;
			while (l <= r)
			{
				int mid = l + r >> 1;
				if (s2.query(i, mid) <= nowval)
				{
					resplace = mid;
					l = mid + 1;
				}
				else
				{
					r = mid - 1;
				}
			}
			
			// from lastpos to resplace: all or to be nowval
			l = lastpos, r = resplace;
			int rrp = 2e9;
			while (l <= r)
			{
				int mid = l + r >> 1;
				int p = s1.query(i, mid);
				if (p >= nowval)
				{
					rrp = mid;
					r = mid - 1;
				}
				else
				{
					l = mid + 1;
				}
			}
			ans += max(0LL, 1LL * resplace - rrp + 1);
			if (resplace == n) break;
			nowval = s2.query(i, resplace + 1);
			lastpos = resplace + 1;
		}
	}
	printf("%lld\n", 1LL * n * (n - 1LL) / 2 + n - ans);
	return 0;
}
```


---

## 作者：xfrvq (赞：0)

[$\tt Link$](/problem/CF875D)。

首先它是统计区间题，然后你就常规套路：枚举一个点，在计算特定包含此点的区间的答案（注意你不能数重）。

这个题正好多方面地符合我们的做法，因为如果从已知区间向外拓展，$\max$ 和 $\operatorname{or}$ 值也只会越来越大。

对于一个点 $i$，我们根据 $\max$ 这个限制找到最大值是它的最长区间，然后再找到 $\operatorname{or}$ 值也是它的最长区间，然后算算答案就行了。

比如说向外拓展，使得 $\max{a_{l\cdots r}}=a_i,\operatorname{or}a_{L\cdots R}=a_i$。

然后讨论几种答案区间。

+ 左端点在 $[l,L)$ 内，这时右端点可以取 $[i,r]$。
+ 右端点在 $(R,r]$ 内，这时左端点可以取 $[l,i]$。
+ 左端点在 $[l,L)$ 内，右端点在 $(R,r]$ 内，算重了减去。

从某种意义上来说像一个容斥。

---

然后挂第十个点。

然后调，发现如果一个区间等于最大值的数有两个，我的枚举区间部分就会出现数重或数漏的情况。

所以如果一个区间有多个最大值，我们在枚举最左边那个的时候统计。

代码真的短而难写，但是读起来比较通俗易懂。

```cpp
const int N = 2e5 + 5;

int n,a[N],nx[N],pv[N],st[N],tp;
int b[32][N],len[32];

int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",a + i);
	st[tp = 0] = n + 1;
	rep(i,n,1){
		while(tp && a[st[tp]] < a[i]) --tp;
		nx[i] = st[tp],st[++tp] = i;
	}
	st[tp = 0] = 0;
	rep(i,1,n){
		while(tp && a[st[tp]] <= a[i]) --tp;
		pv[i] = st[tp],st[++tp] = i;
	}
	rep(d,0,31) rep(i,1,n) if(a[i] >> d & 1) b[d][++len[d]] = i;
	rep(d,0,31) b[d][len[d] + 1] = n + 1;
	long long ans = 0;
	rep(i,1,n){
		int l = pv[i] + 1,r = nx[i] - 1,L = 1,R = n;
		rep(d,0,31) if(!(a[i] >> d & 1)){
			int *_ = lower_bound(b[d] + 1,b[d] + len[d] + 1,i);
			L = max(L,*prev(_) + 1); R = min(R,*_ - 1);
		}
		if(l < L) ans += 1LL * (L - l) * (r - i + 1);
		if(R < r) ans += 1LL * (r - R) * (i - l + 1);
		if(l < L && R < r) ans -= 1LL * (L - l) * (r - R);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Ynoi (赞：0)

事实上没必要像另一篇题解一样倍增的

我们预处理出$l_i$,$r_i$分别表示第i个数左边或右边值比它大 的最近的数的位置

那么 [$l_i+1,r_i-1$]就是i为最大值的区间

这个珂以用单调栈求出qwq

然后一个位置i,我们定义 $lx_i$ 为在$i$左边，离$i$最近的数的位置使得 $a_i$ $or$ $a_{lx_i} > a_i$

同理定义$rx_i$ 为在$i$右边，离$i$最近的数的位置使得 $a_i$ $or$ $a_{lx_i} > a_i$

（注，以上最近指位置最近）

求法很简单，如求$lx_i$，我们可以对于$a_i$的每一个二进制为0的位置，求出前面最近的一个数，使得这一位为1，然后对于每一位求出的这样的数取出max即可。求$rx_i$方法类似

之后就是求值了

一个最大值是$a_i$区间$[l,r]$合法，当且仅当$l_i <= l <=lx_i$或$rx_i <= r <=r_i$

这样容斥一下求解就行了

具体可以见代码
```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define pii pair<int,int>
#define fs first
#define sd second
#define mp make_pair
#define INF 0x3f3f3f3f
#define int long long

int n,m,ans;
int a[MAXN];
int l[MAXN],r[MAXN];
int t[MAXN];
int lx[MAXN],rx[MAXN];
stack< pii >s;

void rd() {
	cin >> n;
	for(int i = 1; i <= n; i ++) 
		cin >> a[i]; 
}

void ql()
{
	for(int i = 1; i <= n; i ++) {
		while(!s.empty() && a[i] > s.top().fs)
			s.pop();
		if(!s.empty()) l[i] = s.top().sd;
		s.push( mp(a[i],i) );
	}
	while(!s.empty()) s.pop();
	
	for(int i = n; i >= 1; i --) {
		while(!s.empty() && a[i] >= s.top().fs) s.pop();
		if(!s.empty()) r[i] = s.top().sd;
		else r[i] = n+1;
		s.push( mp(a[i],i) ); 
	}
}

signed main()
{
	rd();
	ql();
	for(int i = 1; i <= n; i ++)
	{
		lx[i] = 0;
		for(int j = 0; j <= 30; j ++) {
			if(a[i]&(1<<j)) {
				t[j] = i;
			} else
			lx[i] = max(lx[i],t[j]);
		} 
	}
	for(int i = 0; i <= 30; i ++)
		t[i] = n+1;
	for(int i = n; i >= 1; i --) {
		rx[i] = INF;
		for(int j = 0; j <= 30; j ++) {
			if(a[i]&(1<<j)) 
				t[j] = i;
			else  rx[i] = min(rx[i],t[j]);
		} 
	}
	for(int i = 1; i <= n; i ++) { 
		if(r[i] >= rx[i]) ans += (i - l[i]) * (r[i] - rx[i]);
		if(lx[i] >= l[i])	ans += (lx[i] - l[i]) * (r[i] - i);
		if(r[i] >= rx[i] && lx[i] >= l[i])	ans -= (lx[i] - l[i]) * (r[i] - rx[i]);
	} 
	cout<<ans<<"\n";
	return 0;
}

```





---

## 作者：jpwang (赞：0)

首先转化一下求不合法的数量，然后用总数减去不合法的就是答案了

考虑用单调栈把每个值作为最大值的区间找出来，记i的左右边界为L[i],R[i]

我们只需要比较i-L[i]和R[i]-i枚举较短的一段即可，记枚举端点为j

注意到or的和是单调的，那么我们可以二分一个最右的位置k，使得j与k在i的两侧，且sum[j,k]<=a[i]。用线段树或者什么的就可nlog^2n统计不合法区间

我们可以发现上面二分的过程非常慢，改成倍增就可以一个log过了

需要注意相同相邻数字的L和R怎么求，这个单调栈的时候(加一个or删一个)等号就行了

```cpp
#include <stdio.h>
#include <string.h>
#define rep(i,st,ed) for (register int i=st;i<=ed;++i)
#define drp(i,st,ed) for (register int i=st;i>=ed;--i)

typedef long long LL;
const int N=400005;

int stack[N],a[N];
int L[N],R[N];
LL wjp[N][21],lzh[N][21];

int read() {
	int x=0,v=1; char ch=getchar();
	for (;ch<'0'||ch>'9';v=(ch=='-')?(-1):(v),ch=getchar());
	for (;ch<='9'&&ch>='0';x=x*10+ch-'0',ch=getchar());
	return x*v;
}

int main(void) {
	// freopen("data.in","r",stdin);
	// freopen("myp.out","w",stdout);
	int n=read();
	rep(i,1,n) lzh[i][0]=wjp[i][0]=a[i]=read();
	rep(j,1,18) {
		rep(i,1,n) wjp[i][j]=wjp[i][j-1]|wjp[i+(1<<(j-1))][j-1];
		drp(i,n,1) {
			lzh[i][j]=lzh[i][j-1];
			if (i>=(1<<(j-1))) lzh[i][j]|=lzh[i-(1<<(j-1))][j-1];
		}
	}
	for (register int i=1,top=0;i<=n;++i) {
		for (;top&&a[stack[top]]<=a[i];) top--;
		L[i]=stack[top]+1; stack[++top]=i;
	} stack[0]=n+1;
	for (register int i=n,top=0;i>=1;--i) {
		for (;top&&a[stack[top]]<a[i];) top--;
		R[i]=stack[top]-1; stack[++top]=i;
	}
	LL ans=0;
	rep(i,1,n) if (i-L[i]<=R[i]-i) {
		for (register int j=L[i];j<=i;++j) {
			LL ly=a[j]; int now=j;
			drp(k,18,0) {
				if ((now+(1<<k)<=R[i])&&((ly|wjp[now+1][k])<=a[i])) {
					ly|=wjp[now+1][k];
					now+=(1<<k);
				}
			}
			if (now>=i&&now<=R[i]) ans+=now-i+1;
		}
	} else {
		for (register int j=i;j<=R[i];++j) {
			LL ly=a[j]; int now=j;
			drp(k,18,0) {
				if ((now-(1<<k)>=L[i])&&((ly|lzh[now-1][k])<=a[i])) {
					ly|=lzh[now-1][k];
					now-=(1<<k);
				}
			}
			if (now<=i&&now>=L[i]) ans+=i-now+1;
		}
	}
	printf("%lld\n", 1LL*n*(n+1LL)/2LL-ans);
	return 0;
}
```


---

