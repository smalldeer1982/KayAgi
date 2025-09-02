# Odd-Even Subsequence

## 题目描述

Ashish has an array $ a $ of size $ n $ .

A subsequence of $ a $ is defined as a sequence that can be obtained from $ a $ by deleting some elements (possibly none), without changing the order of the remaining elements.

Consider a subsequence $ s $ of $ a $ . He defines the cost of $ s $ as the minimum between:

- The maximum among all elements at odd indices of $ s $ .
- The maximum among all elements at even indices of $ s $ .

Note that the index of an element is its index in $ s $ , rather than its index in $ a $ . The positions are numbered from $ 1 $ . So, the cost of $ s $ is equal to $ min(max(s_1, s_3,       s_5, \ldots), max(s_2, s_4, s_6, \ldots)) $ .

For example, the cost of $ \{7, 5, 6\} $ is $ min( max(7, 6),       max(5) ) = min(7, 5) = 5 $ .

Help him find the minimum cost of a subsequence of size $ k $ .

## 说明/提示

In the first test, consider the subsequence $ s $ = $ \{1,       3\} $ . Here the cost is equal to $ min(max(1), max(3)) = 1 $ .

In the second test, consider the subsequence $ s $ = $ \{1, 2,       4\} $ . Here the cost is equal to $ min(max(1, 4), max(2)) = 2 $ .

In the fourth test, consider the subsequence $ s $ = $ \{3,       50, 2, 4\} $ . Here the cost is equal to $ min(max(3, 2), max(50,       4)) = 3 $ .

## 样例 #1

### 输入

```
4 2
1 2 3 4```

### 输出

```
1```

## 样例 #2

### 输入

```
4 3
1 2 3 4```

### 输出

```
2```

## 样例 #3

### 输入

```
5 3
5 3 4 2 6```

### 输出

```
2```

## 样例 #4

### 输入

```
6 4
5 3 50 2 4 5```

### 输出

```
3```

# 题解

## 作者：LeavingZzz (赞：11)

# Solution For CF1370D  
Upd：有序列表把后面的排版弄坏了/kk  


------------

~~这题赛时就差那么一丢丢就打出来了/wq~~  
希望各位比赛的时候不要慌张，以免造成我这样的悲剧/kk  


------------
## $\mathsf{DesCription}$  
题目要从一个长度为 $N$ 的序列中选出一个长度为 $k$ 的子序列，将一个子序列的花费定义为这个子序列中奇数位置的元素的最大值和偶数位置元素的最大值中的最小值。  
注意，这列的奇数位置和偶数位置是指在子序列中的编号而不是在原序列中的编号。  
## $\mathsf{Analysis}$  
首先我们可以想到，要得到在奇数位置和偶数位置的最大值，但是最后是取二者最小值，所以实际上我们可以只最小化一个。  
考虑二分答案，二分出选出子序列中奇数位置**或者**偶数位置的最大值，设为 $p$，我们这意味着我们要check两次：一次检查奇数位置满足条件，即奇数位置只能选取满足 $a_i\le p$ 的元素（注意是子序列中的编号为奇数）；第二次检查偶数位置同理。  


------------
梳理步骤：  
 1. 读入（顺便得到二分范围，即值域）  
 2. 二分最大值，对于每一个最大值check两次，分别是奇数和偶数位置选取满足 $a_i\le p$ 如果在奇数位置或者偶数位置能选取到 $k$ 个元素那么这个 $p$ 是满足条件的，记录答案，然后右端点左移；如果不满足条件那么左端点右移。  


------------

 
 时间复杂度 $O(Nloga_i)$  
 
 $\large\mathsf{Code:}$  
 ```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<set>
using namespace std;
typedef long long LL;
const int maxn=200007;
int A[maxn];
int N,K;
inline int Re()
{
	char c;
	int re;
	while((c=getchar())>'9'||c<'0');
	re=c-48;
	while((c=getchar())>='0'&&c<='9')
	re=re*10+c-48;
	return re;
}
bool check(int p)
{
	int cnt=0;
	for(int i=1;i<=N;i++)//检查奇数位置 
	{
		if((cnt&1))
		{
			if(A[i]<=p)
				cnt++;//奇数位置要满足不能超出限制 
		}
		else cnt++;//偶数位置无所谓qwq 
	}
	if(cnt>=K) return true;//奇数位置满足条件直接返回
	//不满足条件我们还有一次机会
	cnt=0;
	for(int i=1;i<=N;i++)//检查偶数位置 
	{
		if(!(cnt&1))
		{
			if(A[i]<=p)
				cnt++;
		}
		else cnt++;
	}
	if(cnt>=K) return true;//偶数位置满足条件 
	return false;//都不行 
}
int main()
{
	N=Re();K=Re();
	int L=1,R=0;
	for(register int i=1;i<=N;i++)
	{
		A[i]=Re();
		R=max(A[i],R);
	}
	int mid,ans;
	while(L<=R)//二分答案 
	{
		mid=L+R>>1;
		if(check(mid)) ans=mid,R=mid-1;
		else L=mid+1; 
	}
	printf("%d",ans);
	return 0;
}
```
~~萌新上分，越上越昏~~  
$\huge\mathcal{The\text{ }End}$  
谢谢管理员大大审核^_^

---

## 作者：promise_ (赞：4)

最大值最小，我们不难想到二分答案来解决。

根据题目描述，我们需要找到一个数 $x$ 作为代价，使得在长度为 $k$ 的子序列中，奇数位置上的最大值和偶数位置上的最大值中的较小值不超过 $x$。

为了判断某个数 $x$ 是否合法，我们可以使用贪心的策略。遍历原数组，每当当前奇数位置的数大于 $x$ 时，我们可以跳过该位置，让下一个位置成为奇数位置。同样地，对于偶数位置的数，当其大于 $x$ 时，我们可以跳过该位置，让下一个位置成为偶数位置。在整个过程中，如果剩下的数的个数不小于 $k$，那么 $x$ 就是合法的。

通过二分法，我们可以找到一个合法的 $x$ 的最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int l,r,ans,mid,n,k,a[N];
bool chk1(int x,int y){
	int now=1,len=n;//now表示当前是奇数位置还是偶数位置，len表示剩余的元素个数。
	for(int i=1;i<=n;i++){
		if(now==y&&a[i]>x)//当当前位置i的元素大于x且需要选择的位置与当前位置的奇偶性相同
		now=!now,len--;
		now=!now;
	}
	return len>=k;
}
bool chk2(int x){
	return chk1(x,1)|chk1(x,0);//判断给定的now的情况下，是否存在一个长度至少为k的子序列
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],r=max(r,a[i]);
	l=1;
	while(l<=r){
		mid=(l+r)>>1;
		if(chk2(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：PanH (赞：3)

这场比赛成功掉了 $20$ 多分。~~这题我怎么会没想到二分答案啊啊啊！~~

最大值最小，于是可以往二分答案上想。

二分两个最大值中的最小值。

就是说子序列的奇数位置或偶数位置上的数全部小于等于当前 $mid$。

那么在 check 的时候只要从左到右扫一遍，分两种情况——奇数和偶数，统计比 $mid$ 小的且位置不连续的数的数量，判断一下最长的子序列长度是否大于等于 要求长度。

code：

```
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
const int N=2e5+5;
int l,r,mid,n,m,a[N],maxn,ans;
bool check(int k)//核心部分
{
	int tot1=0,tot2=0;
	for(int i=1,p=0;i<=n;i++)//奇数位置能否全部小于等于k
		if(p)	tot2++,p=0;
		else	if(a[i]<=k)	tot1++,p=1;
	if(tot1+tot2>=m)	return 1;
    
	tot1=0,tot2=0;
	for(int i=1,p=0;i<=n;i++)//偶数位置能否全部小于等于k
		if(p)	{if(a[i]<=k) tot2++,p=0;}
		else	tot1++,p=1;
	if(tot1+tot2>=m)	return 1;
	return 0;
}
int main()
{
	read(n),read(m);
	for(int i=1;i<=n;i++)	read(a[i]),r=max(a[i],r);
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))	r=mid-1,ans=mid;
		else	l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：IceKylin (赞：2)

# CF1370D Odd-Even Subsequence 题解
### [原题链接（in luogu）](https://www.luogu.com.cn/problem/CF1370D)
### [原题链接（in CodeForces）](https://codeforces.com/problemset/problem/1370/D)
### [更好的阅读体验？](https://www.luogu.com.cn/blog/std-IK/cf1370d-ti-xie)

这是一道较难想到的 **二分答案** 题目。

二分答案的思维难度普遍较大，但还是存在突破口：题目中若出现 **最大值最小（最小值最大）** 等字样，往往说明容易转化成 **判定性问题**，所以二分的思路就呼之欲出了。时间复杂度通常为 ${O(A\log R)}$，其中 ${A}$ 表示判定的时间复杂度，${R}$ 表示二分的值域。

此题的 **单调性** 显而易见：若 ${a_i}$ 是可能的代价，那么对于任意满足 ${a_j\ge a_i}$ 的 ${a_j}$，也是可能的代价，但并不是最优的。

然后考虑在 ${O(n)}$ 的时间复杂度内实现 check 函数。

以 **奇数位判定** 为例：

1. 设 check 的数为 ${x}$。

2. 在序列 ${a}$ 中找出所有满足 **两两不相邻** 且 ${a_i \le x}$ 的 ${a_i}$。

3. 在两两之间（以及子序列最后）任取一位作为偶数位，统计总个数，与 ${k}$ 作比较。

偶数位判定同理，可自行思考。

最后的 **时间复杂度** 为 ${O(n\log R)}$，其中 ${R=\max \{a_i\}-\min \{a_i\}}$。

此题有一处 **理论上的优化**，可以 copy 序列 ${a}$ 得到序列 ${b}$，将序列 ${b}$ 排序后二分下标即可，时间复杂度降至 ${O(n\log n)}$。但实际上并没有快很多，原因是 copy 和排序都是需要时间的，所以优化后的程序 **常数大**，实际运行时间与原做法相差无几。

P.S. 注意二分的边界问题。

## AC 代码
```cpp
//By IceKylin 
#include<bits/stdc++.h>
#define maxn 200050
#define il inline
using namespace std;
int n,k,a[maxn],b[maxn];


il bool check(int x){
	int odd=0,even=0; 
	for(int i=1;i<=n;++i){
		odd+=!(odd&1)||a[i]<=x;
		even+=(even&1)||a[i]<=x;
	}
	return max(odd,even)>=k;
}


il int binary_search(int l,int r){
	int ans=r;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(b[mid])){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return b[ans];
} 


int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	cout<<binary_search(1,n);
	return 0;
}
```


---

## 作者：卓易最可爱 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1370D)

这题我用的做法是二分，二分子序列 $s$ 的代价，当子序列的代价取到某个值的时候，计算最大的长度。

这里有一个我不知道的东西，这个子序列不一定是连续的，可以在数组$a$里隔一个取，或是隔几个取，但是不能把前后的顺序打乱。

我们要做的就是二分子序列 $s$ 的代价。所以我们要写一个check，用来判断在二分出来的那个代价下，最长的子序列长度。分别 check 奇数位置 和 偶数位置，原因就是 check 奇数位置和 check 偶数位置算出来的长度是不一样的。（大家自己试一下就知道了）显然我们要取二者中更大的那个，因为如果 check 奇数位置$小于$题目要求的$k$，但是 check 偶数位置并没有，那么就说明我们如果取更大的长度还可以继续缩小代价。所以显然取更大的长度才是正解。

为什么我们在 check 奇数位置的时候不用考虑偶数位置呢？因为子序列 $s$ 的代价是奇数位的最大值和偶数位的最大值，只要奇数满足那就必然有解。
check 偶数位置的时候同理。

```cpp
#include<iostream>
#include<cmath>
#define MAXN 200010
using namespace std;
int n, k, s, a[MAXN], l, r;
bool check(int x){
	int num = 0, tot = 0;
	for (int i = 1; i <= n; i++) { // check奇数位置 
		if (num % 2 == 0) num++; // 注意这里应该用num来判断是不是在奇数位 
		else if (a[i] <= x) num++;
	}
	for (int i = 1; i <= n; i++) { // check偶数位置 
		if (tot % 2 == 1) tot++; // 与上面同理 
		else if (a[i] <= x) tot++;
	}
	num = max(num, tot); // 取两个里面更大的 
	return num >= k; // 如果算出来的长度比要求的长度更大那么就说明可以缩小 
}
int main(){
	int ans = 0;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	    cin >> a[i], r = max(r, a[i]);
	while (l <= r){
		int mid = (l + r) / 2; 
		if (check(mid)) r = mid - 1;
		else l = mid + 1;
	}
	cout << l;
	return 0;
}
```

---

## 作者：45dinо (赞：2)

一开始没有理解“子序列”的意义，以为必须要是连续的，调了40min的单调队列，后来在 ```@_Leaving``` 神犇的指导下才把“子序列”和“子段”分清楚。

$S$ 的子序列：将 $S$ 去掉一些元素，剩下的元素。（不一定连续，但要保留原本的顺序）

$S$ 的子段：从 $S$ 中取出一些**连续的**元素。

当 $S=\{1,2,3,4\}$ 时，
- $\{1,4\}$ 不是 $S$ 的子段，但却是 $S$ 的子序列。
- $\{4,1\}$ 不是 $S$ 的子序列。（当然也不是子段）
- $\{1,2\}$ 既是 $S$ 的子序列，也是 $S$ 的子段。

于是，就可以用二分来解。

对于每一个 $x$ ，要判断它为代价的最长子序列的长度是否大于等于 $k$ 。

关键代码如下：
```cpp
bool check(int p)
{
	int cnt=0;//先判断奇数位的最大值为p的情况
	for(int i=1;i<=n;i++)
	{
		if(cnt&1)
		{
			if(a[i]<=p)
				cnt++;
		}
		else
			cnt++;		
	}	
	if(cnt>=k)
		return 1;
	cnt=0;//如果奇数位不行，考虑偶数位
	for(int i=1;i<=n;i++)
	{
		if(cnt&1)
			cnt++;
		else
		{
			if(a[i]<=p)
				cnt++;
		}
	}
	if(cnt>=k)
		return 1;
	return 0;
} 
```
喜闻乐见的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200001],l=1,r;
bool check(int p)
{
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(cnt&1)
		{
			if(a[i]<=p)
				cnt++;
		}
		else
			cnt++;		
	}	
	if(cnt>=k)
		return 1;
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(cnt&1)
			cnt++;
		else
		{
			if(a[i]<=p)
				cnt++;
		}
	}
	if(cnt>=k)
		return 1;
	return 0;
} 
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		r=max(r,a[i]); 
	}
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	cout<<l;
	return 0;
} 
```


---

## 作者：wizardMarshall (赞：1)

## 题意

找到一个长度为 $k$ 的子序列 $s$，使得 $\min \{ \max\{ s_1,s_3\dots  \},\max\{ s_2,s_4\dots  \} \}$ 最小。求出这个最小值。

## 思路

简单来说就是求奇数位和偶数位两个序列分别的最大值，再求出最小值。观察发现只需要使**其中一个**尽可能小。

但直接处理不太好办，我们可以考虑二分答案，然后对于奇偶分别判断是否满足。

拿奇数来举例子。假设当前二分到 $mid$，维护一个变量 $c$ 记录当前子序列元素个数，然后挨个贪心判断。

- 如果 $c \equiv 0 \pmod 2$，说明前面有偶数个数，当前这个 $a_i$ 在子序列中是奇数。于是我们判断 $a_i\le mid$ 是否成立，再更新 $c$。

- 否则直接 $c + 1 \to c$。因为没有限制。


偶数判断也是同理，只是奇偶判断不同。最终判断是否超过题目要求的长度 $k$。如果满足条件，为使答案尽可能小，右端点左移；否则，左端点右移。

可以结合代码理解。

## 代码

```c++



#include <bits/stdc++.h>
using namespace std;


int a[200005];
int n, k;

bool check1(int x) {//这个是判断偶数的
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (cnt % 2) {
			cnt++;//下一个奇数，直接加
		}else {
			if (a[i] <= x) {//判断条件满足再加
				cnt++;
			}
		}
		if (cnt >= k) {
			return 1;
		}
	}return 0;
}
bool check2(int x) {//奇数也一样
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (cnt % 2) {
			if (a[i] <= x) {
				cnt++;
			}
		}else {
			cnt++;
		}
		if (cnt >= k) {
			return 1;
		}
	}return 0;
}
signed main() {
	cin >> n >> k;
	int mx = 0, mi = 2e9;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		mx = max(mx, a[i]);
		mi = min(mi, a[i]);
	}
	int l = mi, r = mx, temp = mx;
	while (l <= r) {//二分找到满足条件的最小值
		int mid = (l + r) / 2;
		if (check1(mid) || check2(mid)) {//其中一个满足即可
			r = mid - 1;
			temp = mid;
		}else {
			l = mid + 1;
		}
	}
	cout << temp;
    return 0;
}



```

---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑二分答案，然后转换为判定性问题。

题目要求的是取奇数和偶数中较小的一个，所以只需要保证奇数或者偶数中的一个小就行了，可以对于奇数和偶数位置各做一次判断。

然后注意到其实 $k$ 越大问题越强，则直接求出在选择奇数位置或者偶数位置时权值不超过二分出来的的结果的最长的满足条件的长度即可。

求值部分直接贪心。如果当前的位置不被限制就直接往里面塞，如果在限制位置且当前值要比限制值大则需要从前面减掉一个位置让这个位置落到不被限制的位置上（或者理解为不取这个数，两者结果上是等价的）。注意位置的奇偶性的更改。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int l,r,ans,mid,n,k,a[200005];
bool check1(int x,int y){
	int now=1,len=n;
	for(int i=1;i<=n;i++){
		if(now==y&&a[i]>x)
		now=!now,len--;
		now=!now;
	}
	return len>=k;
}
bool check(int now){
	return check1(now,1)|check1(now,0);
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),r=max(r,a[i]);
	l=1;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：RyexAwl (赞：0)

# 题目大意
给定一个长度为$n$的序列$a$，求出长度至少为$k$的子序列，使得：

所有下标为奇数的元素的最大值与所有下标为偶数的元素的最大值的最小值最小

即$min(max(s_1,s_3,s_5...),max(s_2,s_4,s_6...))$

$2 ≤k≤2\times10^5$

$Time\ Limit:2s$

$input:$
```
4 2
1 2 3 4

```

$output:$

```
1
```
## 思路
我们如果考虑枚举每种组合方式，其复杂度是指数级的。

那么我们考虑能不能将这个问题转化为一个判定问题？

即$a_i$为在奇数位/偶数位时的最大值能否构造出一个符合条件的$s$

那么，我们可以$O(n)$的时间$check$：

对于在奇数位，即在$a$中找到不连续的至少$k-\lfloor\frac{k}{2}\rfloor$个不大于$a_i$的数

（且对于最后一位，如果$k$一共有偶数位而其小于$a_i$的数恰好有$k-\lfloor\frac{k}{2}\rfloor$个，而最后一位是$n$则也是不合法的，对于偶数位的check也同理）

证明：若当前满足条件的有$c$个数（即小于等于$a_i$），且$c≥k$

如果$k\ mod\ 2\ ==\ 0$ 那么$\lfloor\frac{k}{2}\rfloor=\frac{k}{2}$

而在$c$中间至少存在$c-\frac{k}{2}-1$个间隔可以插入偶数项，且可以保证最后一项为偶数项。

而因为$c≥k$，因此保证$c≥\frac{k}{2}+1$，而其最后一位为偶数项。

因此必定合法。


对于在偶数位，即在$a$中找到不连续的至少$\lfloor\frac{k}{2}\rfloor$个不大于$a_i$的数

因此我们可以遍历一遍$a$进行$check$

我们的答案就是所有合法的方案中最小的$a_i$。

但是这种$check$有一种问题，我们选的是最多的，但选的方案中不一定包含$a_i$。但任意一种不包含$a_i$的方案必然可以转化为最大值为小于$a_i$的一种方案，因此对取$min$是没有影响的。

```cpp
bool check(int x,int state){
	
	if (state == 1){
		int c = 0,right = 0;
		for (int i = 1; i <= n; i++){
			if (a[i] <= x){
				right = i;
				c++;
				i++;
				//if (i <= n)b++;
			}
		}
		if (c == k - k / 2 && right == n && k % 2 == 0) return false;
		return c  >= k - k / 2;
	}else{
		int c = 0,right = 0;
		for (int i = 2; i <= n; i++){
			//cout << i << endl;
			if (a[i] <= x){
				right = i;
				c++;
				i++;
				//if (i <= n)c++;
			}
		}
		//cout << right << endl;
		if (c == k / 2 && right == n && k % 2 != 0) return false;
		return c  >= k / 2;
	}
}
```

而对于我们所找到的这段不连续的数，如果其可以找到对应的$s_1,s_3,s_5...$，而我们的目标为$min(max(s_1,s_3,s_5...),max(s_2,s_4,s_6...))$

而对于$max(s_2,s_4,s_6...)$，因为在$a$中一定存在至少$k$个不连续的且小于$a_i$的元素，因此在这些元素之间至少可以包含$\lfloor\frac{k}{2}\rfloor$个元素，而这些元素可以当偶数位。且对应着一种合法的偶数方案。


因此我们可以朴素枚举$a_i$，每次用$a_i$去取$min$更新$ans$，复杂度$O(n^2)$。

那么我们已经把这个问题的求解转化为了判定，那么此时就应该证明其单调性，试图用二分将复杂度降到$O(n\log n)$。

单调性证明：

我们要证明的命题如下：

命题一：对于任一合法的$a_i$，则对于任何大于等于$a_i$的$a_j$都合法

命题二：对于任一不合法的$a_i$，则对于任何小于等于$a_i$的$a_j$都不合法

对于命题一：
如果$a_i$为奇数项

如果对于$a_i$来说，设其满足不连续的不大于$a_i$的数的个数为$c_i$，对于$c_i$，最小为$k-\lfloor\frac{k}{2}\rfloor$，且$a_j$为大于等于$a_i$的正整数集合中最小的元素。

如果$k-\lfloor\frac{k}{2}\rfloor$

那么这$k$个数必然不相邻

若不存在相邻的情况，则$k-\lfloor\frac{k}{2}\rfloor+1$

而对于$a_j$，在满足$a_i$的集合中，至多有两个元素与$a_j$相邻。

此时，$c_j=k-\lfloor\frac{k}{2}\rfloor-1$

那么如果$a_j$为偶数项，则必定满足

当$\lfloor \frac{k}{2} \rfloor=\frac{k}{2}-1$时（即$k$一共有奇数项）

$c_j=k-\frac{k}{2}$（则$a_j$作奇数项时一定合法）

当$\lfloor \frac{k}{2} \rfloor=\frac{k}{2}$时（即$k$一共有偶数项）


$c_j=k-\frac{k}{2}-1$

而它既不能放在奇数项，又不能放在偶数项是不是就不合法了呢？

**但是这并不影响二分的最终结果**

**因为最多会有两个在$c_j$两边的小于$a_j$的值，而如果我们选取不选$a_j$，仍然可以保证其所选的数大于等于$k$，而因为它比$a_i$大，必然不会成为答案，而答案一定在$a_j$的左边，即对于任一$a_j$只要其非连续地小于等于它的数大于等于特定值，答案一定在$a_j$的左边，**

而对于命题二，同样地如果$a_i$不合法有以下两种可能：

1.不大于$a_i$的数的个数不足$k$

2.小于$a_i$的数不能够满足不连续分布

首先对于1，$a_j$必然不可能

而对于2，因为我们每次找的都是连续的，不超过$a_i$的，而$a_i$没找到，则$a_j$必然找不到。

因此我们的$check$是满足单调性的。

```cpp
#include <iostream>
#include <algorithm>
 
using namespace std;
 
 
const int maxn = 2e5 + 10;
 
int a[maxn],b[maxn];
int n,k;
 
bool check(int x,int state){
	
	if (state == 1){
		int c = 0,right = 0;
		for (int i = 1; i <= n; i++){
			if (a[i] <= x){
				right = i;
				c++;
				i++;
				//if (i <= n)b++;
			}
		}
		if (c == k - k / 2 && right == n && k % 2 == 0) return false;
		return c  >= k - k / 2;
	}else{
		int c = 0,right = 0;
		for (int i = 2; i <= n; i++){
			//cout << i << endl;
			if (a[i] <= x){
				cout << a[i] << " ";
				right = i;
				c++;
				i++;
				//if (i <= n)c++;
			}
		}
		//cout << right << endl;
		if (c == k / 2 && right == n && k % 2 != 0) return false;
		return c  >= k / 2;
	}
}
 
int main(){
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		b[i] = a[i];
	}	
	sort(b + 1,b + n + 1);
	
	int l = 1,r = n;
	while(l < r){
		int mid = r + l >> 1;
		cout << l << " " << r << " " << mid << endl;
		if (check(b[mid],0) || check(b[mid],1)) r = mid;
		else l = mid + 1;
	}
	cout << b[l];
	
	

	//system("PAUSE");
	
	return 0;
}
```





















---

