# [COCI 2018/2019 #6] Simfonija

## 题目描述

给定包含 $N$ 个元素的数组 $A,B$。将 $A$ 数组内的所有元素都加上一个**整数** $X$，并修改不超过 $K$ 个元素，使得下列代数式最小：

$$\sum_{i=1}^N |A_i-B_i|$$

## 说明/提示

#### 样例 2 解释

当选定 $X=3$，并将 $A$ 数组最后一个数改为 $7$ 后，$A,B$ 两数组完全相同，此时代数式的值为 $0$。

#### 数据规模与约定

对于 $40\%$ 的数据，$K=0$。

对于 $100\%$ 的数据，$1 \le N \le 10^5$，$0 \le K \le N$，$-10^6 \le A_i,B_i \le 10^6$。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2018-2019](https://hsin.hr/coci/archive/2018_2019/) [CONTEST #6](https://hsin.hr/coci/archive/2018_2019/contest6_tasks.pdf)  _T4 Simfonija_。**

## 样例 #1

### 输入

```
3 0
1 2 3
4 5 7```

### 输出

```
1```

## 样例 #2

### 输入

```
3 1
1 2 3
4 5 7```

### 输出

```
0```

## 样例 #3

### 输入

```
4 1
1 2 1 2
5 6 7 8```

### 输出

```
2```

# 题解

## 作者：Demeanor_Roy (赞：9)

- 前言：个人认为这道题挺有意思，是一道很不错的思维题。


------------
### Solution
- 考场上拿到这题,一眼看过去就注意到了高额的部分分，于是我们顺着 $k=0$	的特殊情况入手：

- 当 $k=0$ 时，问题就转化为了求使得 $\sum_{i=1}^n{A_i-B_i+x}$ 取到最小值的整数 $x$ , 不难看出 $A_i-B_i$为一个定值，那么这就等价于给定直线上 $n$ 个点，另找一个点使它到所有点距离之和最小，这就是一道排序经典题型，不会的请转[这儿](https://www.luogu.com.cn/problem/P1862)。

- 考虑完特殊情况，我们来思考一下一般情况：令 $C_i=A_i-B_i$ ,这时我们发现如果将 $C$ 序列中每个数的看作一个点，那么题目的要求等价于让我们找一个点，使得给定 $C$ 序列中 $n$ 个点到其距离的前 $n-k$ 小距离之和最小。

- 由于答案与每个 $C_i$ 所在位置无关，所以我们可以将 $C$ 序列从小到大排序，这时有一个十分重要的结论：对于任意点 $x$ ,到其距离前 $n-k$ 小的点，一定是 $C$ 序列中连续的一段。

- 证明也比较容易，因为对于任意一个点 $x$ ,如果我们将其插入 $C$ 序列，那么到它距离前 $n-k$ 小的点，一定是从它开始，向左向右扩展，直到扩展满 $n-k$ 个。

- 那么此时我们就无需按 $x$ 来分类，而是按区间分类，对于 $C$ 序列中每一个长度为 $n-k$ 的子段，用 $k=0$ 的方法求出这一段的最小答案，最后再取最小值就行了，当然由于要快速求答案,所以还需要用前缀和优化一下，具体方法链接里有，就不详细阐述了。

- 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int N=1e5+10;
int n,k,X,A[N],B[N],delta[N];
LL res=LLONG_MAX,sum[N];
LL get(int L,int R)
{
      int mid=(L+R)>>1;
      if((R-L+1)&1)	return sum[R]-sum[mid]-sum[mid-1]+sum[L-1];
      else return sum[R]-sum[mid]-sum[mid]+sum[L-1];	
} 
int main()
{
      freopen("simfonija.in","r",stdin);
      freopen("simfonija.out","w",stdout);
      scanf("%d%d",&n,&k);
      for(int i=1;i<=n;i++)	scanf("%d",&A[i]);
      for(int i=1;i<=n;i++)	scanf("%d",&B[i]);
      for(int i=1;i<=n;i++)	delta[i]=A[i]-B[i];
      sort(delta+1,delta+n+1);
      for(int i=1;i<=n;i++)	sum[i]=sum[i-1]+delta[i];
      for(int i=1;i<=k+1;i++)	res=min(res,get(i,i+n-k-1)); 
      printf("%lld",res); 
      return 0;
}
```

- 完结撒花~


---

## 作者：shuangmu (赞：5)

[题目链接](https://www.luogu.com.cn/problem/P7382)
## 题意

给定两个长度为 $n$ 的数组 $A$ 和 $B$，你可以给 $A$ 数组中的所有元素加上 $X$（这里 $X$ 应该能是负数），并修改不超过 $K$ 个元素，使得下列代数式最小：
$$
\sum_{i = 1}^{n} \lvert A_i - B_i \rvert
$$
## 思路

首先我们可以考虑 $K = 0$ 的情况。因为是让差最小，所以我们并不关心 $A_i$ 和 $B_i$ 的值，只关心他们的差值即可。我们令 $d_i$ 表示 $B_i-A_i$。如果没有 $X$，那么最后答案可以分为三部分：$d_i < 0$，$d_i = 0$，$d_i>0$。这时候，如果我们将 $d_i$ 排序，会发现其值呈阶梯状分布，如图：

[![pPQpWFI.png](https://s1.ax1x.com/2023/08/15/pPQpWFI.png)](https://imgse.com/i/pPQpWFI)

我们发现，答案就是这些黑线覆盖的面积。（想象一下从每一条黑线两侧延伸下来两条边，形成若干个矩形）

现在我们来考虑 $X$。我们发现，给 $A$ 加上 $X$ 相当于在上下平移这条红线，即 $0$ 所在的位置。我们来考虑平移时面积的变化 ：

[![pPQCFKS.png](https://s1.ax1x.com/2023/08/15/pPQCFKS.png)](https://imgse.com/i/pPQCFKS)
假如红线现在向上平移，设绿色面积为 $s_1$，蓝色面积为 $s_2$，两条黑线 $d_1$ 与 $d_2$ 交界处为 $mid$，我们发现，由于 $mid$ 偏左，故向上平移时，左侧面积的增加量要小于右侧面积的减少量，所以向上平移答案会更优；同理，如果 $mid$ 偏右，结果相反。不难想到，$mid$，也就是 $0$ 值的位置，应该位于一个靠中间的位置。而这个位置就是中位数所在的位置。

但是我们还有 $K$ 个数可以改动。显然，每次改动一定是让某个 $B_i$ 等于 $A_i$，也就是让 $d_i$ 为 $0$。另一个显然的事实是，无论 $mid$ 选在哪里，需要改动的 $d_i$ 一定是左右两侧连续的几个。那么，我们可以枚举左侧选 $i$ 个，那么右侧就是 $K-i$ 个。每次的中位数是单调不减的。我们只需要处理好每次改变 $0$ 值点后答案的变化即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
const int M = 2e6+100, del = 2000000; 
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch<'0' || ch>'9') {if(ch == '-') f = -1; ch = getchar();}
	while(ch>='0'&&ch<='9') {x = x*10+ch-48, ch = getchar();}
	return x * f;
}

int n, K;
int a[N], b[N], d[N];
int e[N];
int ed[N];
int id[M<<1], idx;
int main(){
// 	freopen("simfonija.in", "r", stdin);
// 	freopen("simfonija.out", "w", stdout);
	n = read(), K = read();
	for(int i = 1; i<=n; ++i){
		a[i] = read();
	}
	for(int i = 1; i<=n; ++i){
		b[i] = read();
	}
	for(int i = 1; i<=n; ++i){
		d[i] = b[i] - a[i];
	}
	sort(d+1, d+n+1);
	for(int i = 1; i<=n; ++i){
		if(i == n || d[i+1]!=d[i]){
			id[d[i]+del] = ++idx;
			ed[idx] = i;  
		}//预处理每段黑边的右端点。
	}
	int len = (n+1-K)/2;
	int X = d[len];
	long long ans = 0;
	for(int i = 1; i<=(n-K); ++i){
		ans+=abs(d[i]-X);
	}//左侧不选的答案
	int lst = X;
	long long ret = ans;
	for(int i = 1; i<=K; ++i){
		int nX = d[i+len];
		ans+= abs(d[n-K+i]-lst);//加上右侧弃选后增加的答案
		ans-= abs(d[i]-lst);//减去左侧选后减少的答案
		if(nX != lst){//如果中位数有变化，则 0 值线升高，要处理面积变化。
			ans-=(1ll*((n-K+i)-ed[id[lst+del]]) * (nX-lst));
			ans+=(1ll*(nX-lst)*(ed[id[lst+del]] - i));
			lst = nX;
		}
		ret = min(ret, ans);//答案取最小的
	}
	printf("%lld\n", ret);
	return 0;
}
```


---

## 作者：xietengyi (赞：4)

## 题意:
给你一个数组，选择长度确定的子序列，和一个数 $x$，使得 $\sum_{i = 1}^{n} a_i-b_i+x$ 最小，其中有 $k$ 项可以强制变为 $0$。
## 思路:
容易想出，可以令 $d_i=a_i-b_i$，则答案转化 $\sum_{i = 1}^{n} d_i+x$ 最小，其中可以使 $k$ 项为 $0$。

易证明出取长度为 $n-k$ 连续子区间不取 $0$。

枚举区间开头 $l$，则 $r=l+n-k-1$。

则可以使x取中位数 $-d_{mid}$ 使得答案变为

$$ans = \begin{cases}
  n-k \bmod 2 = 0 & \sum_{i = mid+1}^{r} {d_i} -\sum_{i = l}^{mid} {d_i}\\
  n-k \bmod 2 = 1 & \sum_{i = mid+1}^{r} {d_i} -\sum_{i = l}^{mid-1} {d_i}\\
\end{cases}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+6;
int n,k,d[N],res=1e18; 
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)){
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (isdigit(ch))  {
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return (f==1?x:-x);//输入 
}
inline int get (int l,int r) { //中位数求值
	int mid=(l+r)>>1;
	if ((r-l+1)&1) return (d[r]-d[mid])-(d[mid-1]-d[l-1]);
	return (d[r]-d[mid])-(d[mid]-d[l-1]);
}
signed main() {
	n=read(),k=read();
	for (int i=0;i<n;++i) d[i]=read();
	for (int i=0;i<n;++i) d[i]-=read();
	sort(d,d+n);//sort不影响答案 
	for (int i=1;i<n;++i) d[i]+=d[i-1];
	for (int i=0;i<=k;++i) res=min(res,get(i,i+n-k-1));//选择长度为n-k连续的一段 
	printf("%lld\n",res);
	return 0; 
}
```

---

## 作者：jingyu0929 (赞：2)

# P7382 Simfonija

&emsp;[题目传送门](https://www.luogu.com.cn/problem/P7382)

&emsp;可以想到，先修改某个数和先加之后再修改某个数的贡献是一样的，因为最优方案肯定是最后将他变成和 $b$ 数组一样的数。

&emsp;所以说我们就是要选择一段 $n - k$ 长度的区间，再选择一个数 $x$ ，求 $\min \sum |a_i + x - b_i|$。

&emsp;选区间的话直接暴力枚举就可以了，对于找到一个数 $x$ 的话，我们可以把 $b_i - a_i$ 看做一个变量，那么原来的式子就可以转化成这个样子：

$$\sum|x - (b_i - a_i)|$$

&emsp;这个式子的形式就有点像距离公式，所以问题就转变成了数轴上有 $n - k$ 个点，在数轴上找到一个点的距离离这个点的距离和最近。

&emsp;毫无疑问，如果数轴上的点的数量是奇数的话（设 $w_i = b_i - a_i$），那么 $x = w_{\frac{n + 1}{2}}$。如果数轴上的点是偶数的话，那么 $x = (w_\frac{n}{2} + w_{\frac{n}{2} + 1}) / 2$。

&emsp;所以说先将 $b_i - a_i$ 排一个序，在枚举区间的过程中就可以 $O(1)$ 求出 $x$。有了 $x$ 之后求出答案就很容易了（我这里用的是前缀和求）。

```cpp
#include<bits/stdc++.h>
#define se second
#define fi first
using namespace std;
typedef long long lwl;
typedef pair<int,int> pii;

const int N = 1e5 + 5;

int n,K;
pii w[N];
int c[N];
lwl sum[N];

lwl fr(){
	lwl x = 0, flag = 1;
	char t;
	t = getchar();
	while (t < 48 || t > 57){
		if (t == '-') flag = -1;
		t = getchar();
	}
	while (t >= 48 && t <= 57){
		x = x * 10 + t - 48;
		t = getchar();
	}
	return x*flag;
}

void fw(lwl x){
	if (x < 0) putchar('-'),x = -x;
	if (x > 9){
		fw(x / 10);
	}
	putchar(x % 10 + '0');
	return ;
}

// 前缀和
lwl get(int l,int r) {
	return sum[r] - sum[l - 1];
}

int main(){
	n = fr(), K = fr();
	for (int i = 1; i <= n; i ++) w[i].fi = fr();
	for (int i = 1; i <= n; i ++) w[i].se = fr();
	if (n == K) {
		puts("0");
		return 0;
	}
	for (int i = 1; i <= n; i ++) {
		c[i] = w[i].se - w[i].fi;
	}
	sort(c + 1, c + 1 + n);
	for (int i = 1; i <= n; i ++) {
		sum[i] = sum[i - 1] + c[i];
	}
	int k = n - K;
	lwl ans = linf;
	for (int i = 1; i <= n - k + 1; i ++) {
		int j = i + k - 1;
		int t1 = (i + j) >> 1,t2;
		if ((i + j) & 1) t2 = t1 + 1;
		else t2 = t1;
		lwl x = (c[t1] + c[t2]) >> 1;
		ans = min(ans,(t1 - i + 1) * x - get(i,t1) + get(t2,j) - (j - t2 + 1) * x);
	}
	fw(ans);
	return 0;
}
```

---

## 作者：Floating_Trees (赞：0)

十年 OI 一场空，不开 long long 见祖宗。

### 思路
我们可以先将加上 $X$ 后的式子表示出来：$\sum_{i=1}^N |A_i+X-B_i| = \sum_{i=1}^N |X - (B_i-A_i)|$，因为 $A_i$ 和 $B_i$ 已知，所以可记 $A_i+B_i=C_i$，那么将式子展开后可得 $|X-C_1| + |X-C_2| + |X+C_3|+ \cdots + |X - C_N|$，然后这就是一个初一所学的绝对值问题的提高（但不多，作业本上都有）。对于可以修改的 $K$ 个元素，肯定是将 $a_i$ 改为 $b_i$，这样可以使答案最小。然后我们就可以枚举将哪个区间加上 $X$，由于巨大的数据范围，可以使用前缀和优化。时间复杂度为 $O(N \log N + N)$（需要将 $C$ 排序，所以会带一个 $\log$）。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int N = 1e5 + 10;
int n, m;
ll a[N], b[N], c[N], sum[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	cin >> n >> m; m = n - m;
	for (int i = 1;i <= n;i++)
		cin >> a[i];
	for (int i = 1;i <= n;i++)
		cin >> b[i];
	for (int i = 1;i <= n;i++)
		c[i] = b[i] - a[i];
	// a[i] + x - b[i] = x - (b[i] - a[i])
	sort(c + 1, c + 1 + n);
	for (int i = 1;i <= n;i++)
		sum[i] = sum[i-1] + c[i];
	ll ans = LONG_LONG_MAX;
	for (int i = 1;i + m - 1 <= n;i++)
	{
		int l = i, r = i + m - 1;
		int mid = (l + r) >> 1;
		ans = min(ans, 1ll * c[mid] * (mid - l + 1) - (sum[mid] - sum[l-1]) + (sum[r] - sum[mid]) - 1ll * c[mid] * (r - mid));
		if (mid + 1 <= r) mid++;
		ans = min(ans, 1ll * c[mid] * (mid - l + 1) - (sum[mid] - sum[l-1]) + (sum[r] - sum[mid]) - 1ll * c[mid] * (r - mid));
		if (mid - 1 >= l) mid--;
		ans = min(ans, 1ll * c[mid] * (mid - l + 1) - (sum[mid] - sum[l-1]) + (sum[r] - sum[mid]) - 1ll * c[mid] * (r - mid));
		// cout << l << " " << r << " " << mid << " " << c[mid] << " ";
		// cout << 1ll * c[mid] * (mid - l + 1) - (sum[mid] - sum[l-1]) + (sum[r] - sum[mid]) - 1ll * c[mid] * (r - mid) << endl;
	}
	cout << ans << endl;

	return 0;
}
``````

---

## 作者：Zkl21 (赞：0)

### [P7382[COCI2018-2019#6] Simfonija](https://www.luogu.com.cn/problem/P7382)

转化题意，就是钦定一个整数 $x$，选定 $n-k$ 个 $a_i$ 和 $b_i$，令 $\sum_{j=1}^{n-k}|a_j+x-b_j|$ 最小。因此，我们只要钦定出最优方案下的 $x$，选定对于当前 $x$ 前 $n-k$ 小的 $|a_i+x-b_i|$ 即可。

#### 思路
首先，$a_i-b_i$ 是定值，设 $c_i=a_i-b_i$。钦定一个 $x$，如果令答案最小，发现选定的所有 $c_j$ 一定是在 $x$ 两侧连续排布。于是对 $c$ 排序，保证选定的所有 $c_j$ 是连续的，枚举所有长度为 $n-k$ 的连续子区间即可。

如果直接枚举求的话时间复杂度为 $O(n^2)$，需要用前缀和优化成 $O(n)$。对于用前缀和求中位数与每个值的差的绝对值之和的最小值是很有 trick 意味在里面的。思路来源于[这道题](https://www.luogu.com.cn/problem/P1862)以及[这篇题解](https://www.luogu.com.cn/blog/LMB001/solution-p1862)。

假设中位数为 $x$，分两种情况讨论。

* $r-l$ 是奇数，求的是 $\min\{\sum_{i=l}^{r}|c_i+x|\}$。
比 $x$ 小的数有 $c_l,c_{l+1},...c_{mid}$，比 $x$ 大的数就有 $c_{mid+1},c_{mid+2},...,c_r$，其中 $mid=\frac{l+r}{2}$。于是就可以转化成求 $\sum_{i=l}^{mid}|c_i+x|$ 和 $\sum_{i=mid+1}^r|c_i+x|$ 的和的最小值。
我们取出两个式子中的两边一项 $c_l$ 和 $c_r$，求 $\min\{|c_l+x|+|c_r+x|\}$，那么一定满足 $-c_r\le x\le -c_l$。
设 $ c_r\ge c_l\ge 0$ 则有 $\min\{|c_l+x|+|c_r+x|\}=x-c_l+c_r-x=c_r-c_l$。同理选出 $c_{l+1}$ 和 $c_{r-1}$，也能得出类似的结论...

    因此最小值为 $\sum_{i=mid+1}^rc_i-\sum_{i=1}^{mid}c_i$。
* 同理如果 $r-l$ 是偶数，可以推得所求的值就是 $\sum_{i=mid+1}^{r}-\sum_{i=l}^{mid-1}$。

总复杂度为 $O(n\log n)$，瓶颈在排序。
代码很简单，就不贴了，应该也比较好写。

---

## 作者：有趣的问题 (赞：0)

感觉挺奇妙的一道题，思路很巧。

先构造一个数组是给出两个数组的差，再排序，这一点不用多说。

然后我们考虑，要从其中选出 $K$ 个元素修改，那这 $K$ 个元素一定是排序后的数组中两端的元素。

既然这样，那剩下的 $n-K$ 个元素一定是新数组中连续的一段。

于是问题就变成了，在一段数中选择一个数 $x$，使得
$$
\sum_{i=1}^N |A_i-x|$$

最小。由小学奥数得知，这个数应该是这组数的中位数。

至于知道了中位数如何 $O(1)$ 的计算答案，另一篇题解已经讲的很清楚了。

放代码：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[100005],b[100005],cha[100005],n,k,sum[100005],ans,inf=0x3f3f3f3f3f3f3f3f;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i],cha[i]=a[i]-b[i];
	sort(cha+1,cha+n+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+cha[i];
	k=n-k,ans=inf;
	for(int i=1;i+k-1<=n;i++){
		int r=i+k-1;
		int mid=(i+r)>>1;
		int now=cha[mid]*(mid-i+1)-(sum[mid]-sum[i-1])+(sum[r]-sum[mid])-cha[mid]*(r-mid);
		ans=min(ans,now);
	}
	cout<<ans;
	return 0;
}


---

## 作者：yxy666 (赞：0)

我们假设 $x$ 为要修改的值，那么 $x$ 到底应该是多少呢？有些童鞋可能会讲，中位数或者众数。但是这样子是会有反例的。那么我们只好一个一个把 $x$给枚举过去了。但是这样子的话，时间效率为$O(N*K)$，不可能满分。所以我们就只能一下子出答案。那应该如果出呢？

```latex
我们设c[i]=A[i]-B[i],将c序列从小到大排序

设s[i]表示c[1]+c[2]+…+c[i]

k表示可以干掉的点
设x=c[mid]
因为左边的数值都是小于c[mid]，以i为起点,
那么左边这么一长串的代价就是c[mid]*(mid-i+1)-(s[mid]-s[i-1]),
右边这么一长串的代价就是(s[i+k-1]-s[mid])-c[mid]*(i+k-mid-1))

那么就能很快地得出答案了啊。
```
$code$ :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int n,k,a[maxn],c[maxn];
long long ans=(long long)1<<61,s[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;	
}//快读
int main(){
	n=read();k=n-read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)c[i]=a[i]-read();//构造c数组
	sort(c+1,c+1+n); 
	for(int i=1;i<=n;i++)s[i]=s[i-1]+c[i];//构造前缀和
	for(int i=1;i<=n-k+1;i++){
		int mid=(i+i+k)/2;//枚举，起点为i,终点为i+k,中点为（i+i+k）/2
		ans=min(ans,(long long)c[mid]*(mid-i+1)-(s[mid]-s[i-1])+(s[i+k-1]-s[mid])-(long long)c[mid]*(i+k-mid-1));
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

