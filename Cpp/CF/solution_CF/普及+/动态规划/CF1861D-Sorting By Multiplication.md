# Sorting By Multiplication

## 题目描述

You are given an array $ a $ of length $ n $ , consisting of positive integers.

You can perform the following operation on this array any number of times (possibly zero):

- choose three integers $ l $ , $ r $ and $ x $ such that $ 1 \le l \le r \le n $ , and multiply every $ a_i $ such that $ l \le i \le r $ by $ x $ .

Note that you can choose any integer as $ x $ , it doesn't have to be positive.

You have to calculate the minimum number of operations to make the array $ a $ sorted in strictly ascending order (i. e. the condition $ a_1 < a_2 < \dots < a_n $ must be satisfied).

## 说明/提示

In the first test case, we can perform the operations as follows:

- $ l = 2 $ , $ r = 4 $ , $ x = 3 $ ;
- $ l = 4 $ , $ r = 4 $ , $ x = 2 $ ;
- $ l = 5 $ , $ r = 5 $ , $ x = 10 $ .

 After these operations, the array $ a $ becomes $ [1, 3, 6, 12, 20] $ .In the second test case, we can perform one operation as follows:

- $ l = 1 $ , $ r = 4 $ , $ x = -2 $ ;
- $ l = 6 $ , $ r = 6 $ , $ x = 1337 $ .

 After these operations, the array $ a $ becomes $ [-10, -8, -6, -4, 5, 1337] $ .In the third test case, the array $ a $ is already sorted.

## 样例 #1

### 输入

```
3
5
1 1 2 2 2
6
5 4 3 2 5 1
3
1 2 3```

### 输出

```
3
2
0```

# 题解

## 作者：lalaouye (赞：6)

### 废话：

VP 时 T3 思路不清晰，写了很久，然后这题没时间做了，赛后五分钟 AC 了（还好不是正赛，不然我会气死的）。

所以做题前思路一定要清晰且严谨！

### 思路：

观察这个问题，发现如果 $l$ 到 $r$ 不是单调的，那么完全没必要一起乘。

那么本题中的操作将会一整段一整段的进行，我们肯定会让段数尽可能小，于是就可以 dp 了。

设 $f_{i,0/1}$ 表示当前这一段上升/下降段数的最小数量，因为我们并不需要特别关注段之间的大小关系（因为可以自己调整相对关系嘛，但是是有细节的，具体后面会讲），所以转移是简单的，需要分三种情况讨论，具体如下：

1.当 $a_i=a_i-1$ 时，无论如何 $i$ 和 $i-1$ 都不可能分在一段，所以

$$f_{i,0}=\min(f_{i-1,0},f_{i-1,1})+1$$

$$f_{i,1}=f_{i-1,1}+1$$

为什么 $f_{i-1,0}$ 不能转移到 $f_{i,1}$？因为前面并没有将数变成负数，但是当前这一段变成了负数，那不就不能单调递增了吗？所以所有的 $f_{i,1}$ 都不能由 $f_{i-1,0}$ 转移。

2.当 $a_i<a_{i-1}$ 时

$$f_{i,0}=\min(f_{i-1,0},f_{i-1,1})+1$$

$$f_{i,1}=f_{i-1,1}$$

应该不难理解，当 $a_i>a_{i-1}$ 时同理，那答案是什么呢？

我们发现如果 $n$ 处于一个单调递增的段时，这个段是没必要乘的，所以答案要减 $1$，但是当 $n$ 处于一个单调递减的段时，显然必须要乘，所以不能减，那么最终答案等于 $\min(f_{n,0}-1,f_{n,1})$。

[code](https://codeforces.com/contest/1861/submission/226812180)



---

## 作者：DerrickLo (赞：6)

我们可以枚举变成负数和不变负数的分界点，然后对于变成负数的部分，若 $a_{i+1}\le{a_i}$ 则需要进行一次操作，不变负数的部分若 $a_i\le{a_{i+1}}$ 则需要进行一次操作，那么可以动态的算出变成负数的部分与不变成负数的部分分别要操作多少次。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int ans=INT_MAX,now=0,now1=0;
		for(int i=1;i<n;i++)if(a[i]>=a[i+1])now++;
		ans=min(ans,now);
		for(int i=1;i<n;i++){
			if(a[i]>=a[i-1])now1++;
			if(a[i]>=a[i+1])now--;
			ans=min(ans,now+now1);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Ericby666 (赞：4)

## [题目链接](https://www.luogu.com.cn/problem/CF1861D)
由于题目中的 $x$ 可以为任意整数，所以 $x$ 也可以为负整数，当一个序列严格降序时，就可以给该序列的每一个元素乘上一个负数，使其严格升序。

于是我们可以用 $sh_i$ 来表示从 $i$ 到 $n$ 的严格升序的序列数量，用 $xi_i$ 来表示从 $1$ 到 $i$ 的严格降序的序列数量。然后枚举每一个元素，让该元素前的所有元素都乘负数，该元素后的所有元素都乘正数。再将所有的操作次数取最小值即可。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[200005],sh[200005],xi[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		int n,ans=2e9;
		scanf("%d",&n);
		sh[n+1]=0;
		a[n+1]=-1;//预处理
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]>=a[i-1])xi[i]=xi[i-1]+1;
			else xi[i]=xi[i-1];
		}
		for(int i=n;i>=1;i--){
			if(a[i]>=a[i+1])sh[i]=sh[i+1]+1;
			else sh[i]=sh[i+1];
		}
		for(int i=0;i<n;i++)ans=min(ans,xi[i]+sh[i+1]-1);//-1是因为有一个序列不需要乘任何数
        	//枚举到n-1即可，因为给前n-1个数都乘上负数后，仅剩第n个元素为正数，所以第n个元素必大于前n-1个元素
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：2huk (赞：1)

**题意**：

> 你可以对数组 $A$ 执行任意次操作（可以为 $0$ 次），每一次操作，你可以选择一个 $l$ 和 $r$（$1\le l\le r\le n$），以及**任意**一个整数 $x$，对于所有满足 $l\le k\le r$ 的 $k$，$A_k$ 将乘以 $x$。
>
> 求让 $A$ 数组**严格升序**（$A_1< A_2<\dots<A_n$）的最少操作次数。

**做法**：

首先考虑如果要求 $x$ 必须为正怎么做。

如果 $a_i \ge a_{i+1}$，那么 $a_{i+1}$ 要乘的数一定大于 $a_i$ 要乘的数。

所以答案至少为「$a_i \ge a_{i+1}$ 的数量」。而且可以取等号，答案为「$a_i \ge a_{i+1}$ 的数量」。

同理如果要求 $x$ 必须为负，答案为「$a_i \le a_{i+1}$ 的数量」。因为乘一个负数会变号。

对于本题，我们可以枚举负数与正数的分界点。预处理前后缀即可。

<https://codeforces.com/contest/1861/submission/273952469>

---

## 作者：huangrenheluogu (赞：1)

题目中有一句关键的话：

> Note that you can choose any integer as $x$ , it doesn't have to be positive.

当 $x$ 是负数的时候，发现可以变号，就是 $a>b,x<0\Rightarrow ax<bx$。

所以，我们构造的数列就是前面负，后面正。

发现 $a_l,a_{l+1},\dots,a_r$ 同时乘上一个数，内部符号如果有不同的，那么最后还会有两种符号，这就启发我们按单调递增/单调递减分类。

比如 $a_1,a_2,a_3,a_4,a_3>a_1>a_2,a_3>a_4$，那么我们可以分成 $a_1,a_2$ 和 $a_3, a_4$ 两组，第一组乘上一个绝对值较大的负数，第二组乘上一个绝对值较小的负数，就可以 $a_1<a_2<a_3<a_4$ 了。

那么，我们可以从前往后找单调递减的数目，从后往前找单调递增的数目。

我们可以枚举正负号的分界点，左边需要单调递减，右边需要单调递增，所以这样的数目都有了，就可以 $O(1)$ 直接算了。

[code](https://codeforces.com/contest/1861/submission/237885664)

---

## 作者：Natori (赞：1)

update on 2023.9.18：修改事实性错误，感谢 @[w_camellia](https://www.luogu.com.cn/user/939191) 同学指出。

>[CF1861D Sorting By Multiplication](https://www.luogu.com.cn/problem/CF1861D)

简单思维题。

------------

首先乘 $0$ 一定是不优的，原因显然。

考虑最终合法序列的形式，由于可以乘负数，所以一定是一段单调递增的负数接一段单调递增的正数（当然也可能只有负数段或只有正数段）。

因此，考虑枚举 $i \in [0,n]$ 表示下标在 $[1,i]$ 中的数要变成负数，下标在 $(i,n]$ 中的数要变成正数。在两段中分别从左向右扫（注意题目保证数组元素是正数）：

- 对于要变成负数的段，假设当前考虑到第 $j$ 项，此时下标在 $[1,j-1]$ 之内的数已经满足要求。若 $a_{j-1} \le a_j$，则乘上一个负数之后会有 $a_{j-1} \ge a_j$，不符合条件，于是需要对下标在 $[1,j-1]$ 之内的数进行一次操作，即乘上一个正数。

- 要变成正数的段同理，判断条件为 $a_j \ge a_{j+1}$。

直接按上面的策略模拟，时间复杂度 $\mathcal{O}(n^2)$。

------------
考虑优化，注意到每次只会把序列的一个前缀全部变成负数，考虑预处理最终序列中所有数都是正数的情况下，最少需要多少次操作，记作 $cnt_1$。同时设 $cnt_2$ 表示负数前缀所需要的最小操作次数。

然后，枚举 $i \in [1,n)$ 表示之前的正负分割点，结合两种情况的判断条件，就可以动态维护两段各自需要的最小操作次数。具体而言，每次遇到满足 $a_{i-1} \le a_i$ 的 $i$，就 $cnt_2$ 自增 $1$；若 $a_i \ge a_{i+1}$，则 $cnt_1$ 自减 $1$。

另记一个变量 $ans$ 维护答案即可，时间复杂度 $\mathcal{O}(n)$。

核心代码：

```cpp
int cnt1=0,cnt2=0,ans=oo;
for(int i=1; i<n; i++)
	if(a[i]>=a[i+1])
		cnt1++;
ans=min(ans,cnt1);
for(int i=1; i<n; i++) {
	if(a[i-1]<=a[i])
		cnt2++;
	if(a[i]>=a[i+1])
		cnt1--;
	ans=min(ans,cnt1+cnt2);
}
```

---

## 作者：eb0ycn (赞：0)

## 思路

显然要按乘数的正负分类，因为乘 $0$ 一定不优。

设 $f_{i,0/1}$ 表示到了第 $i$ 个数，选择乘正数或负数的最小操作次数。显然，$f_{0,0}=0$，$f_{0,1}=1$。

### 一、$a_i>a_{i-1}$

此时 $a_i$ 可以和 $a_{i-1}$ 乘相同的正数，但不能乘相同的负数；若 $a_{i-1}$ 乘了负数，则 $a_{i}$ 可以不变，也可以乘更大的负数。所以 $f_{i,0} \gets \min(f_{i-1,0},f_{i-1,1})$，$f_{i,1} \gets f_{i-1,1}+1$。

### 二、$a_i<a_{i-1}$

此时，$a_i$ 可以和 $a_{i-1}$ 同乘一个负数；若 $a_{i-1}$ 乘了正数，$a_i$ 就必须乘更大的正数。所以 $f_{i,0} \gets \min(f_{i-1,0}+1,f_{i-1,1})$，$f_{i,1} \gets f_{i-1,1}$。

### 三、$a_i=a_{i-1}$

此时，若 $a_{i-1}$ 乘正数，$a_i$ 必须乘上更大的数；若 $a_{i-1}$ 乘负数，$a_i$ 可以不变或乘更大的数。所以 $f_{i,0} \gets \min(f_{i-1,0}+1,f_{i-1,1})$，$f_{i,1} \gets f_{i-1,1}+1$。

然后我们发现 $f$ 数组第一维可以滚动掉。

## 代码


```cpp
#include<cstdio>
int min(int x,int y){return x>y?y:x;}
int t,n,a,la,f[2];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n),la=0,f[0]=f[1]=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&a);
			if(a>la)f[0]=min(f[0],f[1]),++f[1];
			if(a<la)f[0]=min(f[0]+1,f[1]);
			if(a==la)f[0]=min(f[0]+1,f[1]),++f[1];
			la=a;
		}
		printf("%d\n",min(f[0],f[1]));
	}
	return 0;
}
```

---

## 作者：Xssion37_XY (赞：0)

由于 $x$ 为任意整数，我们可以考虑对单调递减的部分乘以负数，那么这个部分就会单调递增满足条件。

首先考虑不需要操作的情况，非常简单，按要求扫一遍并记录不满足条件的数量，为 $0$ 则直接输出 $0$ 即可。

然后用这个数量作为最坏情况下的修改数量（因为最坏情况下是对单点进行依次修改）。

因为整个序列最后会被分为负数和非负数两个部分，考虑平衡两部分的操作次数，那么枚举分界点即可。

由于负数的部分与非负数部分相反，所以要注意符号方向。


```cpp
while (T --) {
		int n;
		cin >> n;
		int ans = 0x7f7f7f7f;
		cnt = 0;
		xnt = 0;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		for (int i = 1; i < n; i ++) {
			if (a[i] >= a[i + 1]) { 
				cnt ++; 
			}
		}
		if (cnt == 0) {
			cout << cnt << endl;
			continue;
		}
		ans = min(ans,cnt);
		for (int i = 1; i < n; i ++) {
			if (a[i] >= a[i - 1]) xnt ++;
			if (a[i] >= a[i + 1]) cnt --;
			ans = min(ans,xnt + cnt);
		}
		cout << ans << endl;
	}
```

---

## 作者：modfisher (赞：0)

## 思路

不难发现：一段严格上升的子串乘上一个正数还是一段严格上升的子串，一段严格下降的子串乘上一个负数会变成一段严格上升的子串。

而且：如果区间 $[l,r]$ 至少被分为 $k_1$ 段连续的严格上升的子串，则（只乘正数）使其严格上升至少需要进行 $k_1-1$ 次操作（记为操作 $1$）；如果区间 $[l,r]$ 至少被分为 $k_2$ 段连续的严格下降的子串，则（只乘负数）使其严格上升至少需要进行 $k_2$ 次操作（记为操作 $2$）。这两个结论都是显然的。

考虑到一段子串如果被乘上了负数，那么它的左端点前面的所有数都要变成负数。所以，我们可以考虑枚举一个节点 $x$（$0\leq x\leq n$），定义 $k_1[i]$ 表示区间 $[1,i]$ 至少被分为 $k_1[i]$ 段连续的严格下降的子串，$k_2[i]$ 表示区间 $[i,n]$ 至少被分为 $k_2$ 段连续的严格上升的子串 。若 $x\geq 1$，对 $[1,x]$ 使用操作 $2$，共需 $k_1[x]$ 次操作；若 $x<n$，对 $[x+1,n]$ 使用操作 $1$，共需 $k_2[x+1]$ 次操作。对于其操作次数取最小值即可。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int a[maxn], down[maxn], k = 0, up[maxn];

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n;
		scanf("%d", &n);
		down[1] = 1;
		for(int i = 1; i <= n; i ++){
			scanf("%d", &a[i]);
			if(i >= 2){
				if(a[i] >= a[i - 1]){
					down[i] = down[i - 1] + 1;
				}else{
					down[i] = down[i - 1];
				}
			}
		}
		up[n] = 1;
		for(int i = n - 1; i >= 1; i --){
			if(a[i] >= a[i + 1]) up[i] = up[i + 1] + 1;
			else up[i] = up[i + 1];
		}
		int ans = 2147483647;
		for(int i = 0; i <= n; i ++){
			ans = min(ans, down[i] + max(up[i + 1] - 1, 0));
		}
		printf("%d\n", ans);
		k = 0; 
	}
	return 0;
}
```


---

## 作者：ForwardStar (赞：0)

观察发现，对于每一个数我们操作一次就可以将成为正确大小位置，例如可以将最后一个数乘上一个极大的正数，第一个数可以乘一个绝对值极大的负数，以此类推......而这对已经满足单调性的区间也同样成立。    
而一段单调递增的子区间同时乘一个正数相对大小位置不变，乘负数相对大小位置相反，所以我们可以对前面每个单调递减的区间乘负数，后面每个单调递增的区间乘正数就行了。  
我们只需要枚举每个分界点，这个分界点前都乘负数，后面都乘正数，每个分界点的答案就是前面极大的不重叠单调递减的区间数量和后面极大的不重叠单调递增的区间数量减一。因为可以有一个区间如如不动，所以要减一。  
代码：
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;
const int N=2e5+55,inf=2147483647;
int T,n;
int a[N],l[N],r[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
                /*先预处理出每个位置前面的单调递减区间数量
                和后面单调递增区间数量*/
		for(int i=1;i<=n;i++){
			l[i]=l[i-1];
			if(a[i]>=a[i-1])l[i]++;
		}
		r[n+1]=0;
		a[n+1]=-1;
		for(int i=n;i>=1;i--){
			r[i]=r[i+1];
			if(a[i]>=a[i+1])r[i]++;
		}
		int ans=1e9;
		for(int i=0;i<n;i++)ans=min(ans,l[i]+r[i+1]-1);
        /*这里没有枚举i=n的情况，因为i=n时，实际上你是要给所有数
都乘负数，此时不能有区间如如不动，所以这种情况是不能-1的，
这种情况也是不会出答案的，你给n之前的数都乘负数了最后一个数是整数肯定
就是最大的了*/
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：One_JuRuo (赞：0)

## 思路

先考虑不能把数变为负数的情况。

显然，当 $a_i\ge a_{i+1}$ 时，需要对 $[i+1,n]$ 的数都要乘以一个很大的数。

所以答案是 $a_i\ge a_{i+1}$ 的个数。

但是可以变为负数，考虑把一部分变为递减的，再变成负数，另一部分正常计算。

因为负数一定小于正数，所以一定是前半部分变为递减的，后半部分变为递增的。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200005],ans,b[200005],c[200005];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n),a[n+1]=ans=c[n+1]=0,ans=0x3f3f3f3f;
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1;i<=n;++i) b[i]=b[i-1]+(a[i]>=a[i-1]);//注意，这里从1开始多计算了一步
		for(int i=n;i>=1;--i) c[i]=c[i+1]+(a[i]>=a[i+1]);//注意，这里从n开始多计算了一步
		for(int i=0;i<n;++i) ans=min(ans,b[i]+c[i+1]-1);//注意，b和c都多计算了一步，但是要额外的一步用于前半部分乘以负数，所以只用减1
		printf("%d\n",min(ans,b[n]));//注意，b多计算了一步，但是需要额外一步乘以负数，所以不需要减
	}
	return 0;
}
 
```

---

## 作者：cosf (赞：0)

## [CF1861D](https://codeforces.com/problemset/problem/1861/D) [Sorting By Multiplication](https://www.luogu.com.cn/problem/CF1861D)

赛时秒切，感觉比 C 题简单了不知道多少倍，~~应该评黄~~。

## 思路

由于有可以乘负数这个方法，比较复杂，我们先考虑不能乘负数（和 $0$）的情况。

注意到，如果有两个相邻的数不满足升序，那么显然需要进行一次操作让它们升序。并且，这次操作只能解决一个问题。因为，让两个数从降序变成升序需要让前面那个数变小或者后面那个数变大。而如果你进行一次让 $l$ 到 $r$ 乘数的话，$a_l$ 会变大，$a_r$ 也会变大，只有前者可以解决一个问题。

那么，考虑可以乘负数的情况。注意到，负数一定小于正数，所以乘负数只会乘一次，即让一个前缀都乘上一个负数。之后就十分类似了，用前缀和统计一下即可。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXN 200005

int t;

int val[MAXN];

int main()
{
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		int s = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> val[i];
			if (i > 1)
			{
				if (val[i - 1] >= val[i])
				{
					s++;
				}
			}
		}
		int res = s;
		s++;
		for (int i = 2; i <= n; i++)
		{
			if (val[i - 1] >= val[i])
			{
				s--;
			}
			if (i > 2)
			{
				if (val[i - 2] <= val[i - 1])
				{
					s++;
				}
			}
			res = min(res, s);
		}
		cout << res << endl;
	}
}
```


---

