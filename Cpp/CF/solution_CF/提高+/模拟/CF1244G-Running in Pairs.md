# Running in Pairs

## 题目描述

**题目大意**：

找出两个1到n的全排列p和q，使得
$\sum^n_{i=1} \max(p_i,q_i)$尽量大且不超过给定的k。

## 样例 #1

### 输入

```
5 20
```

### 输出

```
20
1 2 3 4 5 
5 2 4 3 1 
```

## 样例 #2

### 输入

```
3 9
```

### 输出

```
8
1 2 3 
3 2 1 
```

## 样例 #3

### 输入

```
10 54
```

### 输出

```
-1
```

# 题解

## 作者：what_can_I_do (赞：8)

[传送门](https://www.luogu.com.cn/problem/CF1244G)

超水 $2400$。

首先，我们先想一下这一题取得的最小值也就是 $\frac{n\times(n+1)}{2}$ 的时候要怎么构造。很显然，取最小值时，$p_i=q_i$，因为但凡你有一个 $p_i$ 不等于 $q_i$，那么就会有另一个 $p_j$ 不等于 $q_j$，那么原来相等的两个更大的数就会被分散到两个更小的数里面与它们配对，就会导致结果比原来多了大的数与小的数的差值，值会更大。

接下来会发现我们在构造完取最小值时的情况的 $p$ 和 $q$ 后若交换还没参与交换过的 $p_i$ 和 $p_j$ 那么总共的值会增加 $p_i$ 与 $p_j$ 的差值，原因其实就是上一段的最后讲的那样。所以我们可以考虑先把 $p$ 和 $q$ 排序，将 $p_i$ 和 $q_i$ 都先设为 $i$，然后此时从 $1$ 到 $n$ 枚举 $i$，此时 $i$ 可以交换的位置就是 $i$ 到 $n-i+1$，因为 $n-i+1$ 更后面的位置已经和前面的换掉了，所以现在不能换。当 $i$ 大于等于 $n-i+1$ 时，退出循环。

接下来对于 $p_i$ 来说它的交换可以使值多上 $0$ 到 $n-2\times i+1$，考虑凑数。如果此时的值与 $k$ 的差值小于等于 $n-2\times i+1$，那么完全可以直接用 $p_i$ 换使值直接等于 $k$，记现在的值为 $sum$，让 $p_i$ 与 $p_{i+k-sum}$ 交换即可，否则直接将 $p_i$ 和 $p_{n-i+1}$ 互换，值加上 $n-2\times i+1$，直接加最大的使值可以更靠近 $k$。

然后就做完了。记得在构造之前先判断是否可以构造。

至于为什么可以这么做，因为每次可加的值时从零开始的一个连续的整数区间，与别的相拼凑得到的值也是一个连续的整数区间。

# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;ll k,sum=0;
ll p[1000010];
int main()
{
	scanf("%d%lld",&n,&k);
	if(1ll*n*(n+1)/2>k)
	{
		puts("-1");
		return 0; 
	}
	for(register int i=1;i<=n;i++) p[i]=i,sum+=p[i];
	for(register int i=1;i<=n;i++)
	{
		int ly=n-i+1;
		if(i>=ly) break;
		if(sum==k) break;
		if(k-sum<=ly-i) swap(p[i],p[i+(k-sum)]),sum=k;
		else swap(p[i],p[ly]),sum+=ly-i;
	}
	printf("%lld\n",sum);
	for(register int i=1;i<=n;i++) printf("%lld ",p[i]);
	puts("");
	for(register int i=1;i<=n;i++) printf("%d ",i);
	puts("");
	return 0;
}
```

---

## 作者：xukuan (赞：7)

这是这次比赛最可做的四道题（ABDG）之一，估计绿题难度

简单构造

因为输出顺序与答案正确性无关，所以我们假设输出的两个序列中一个是按照从$1$到$n$的顺序来的。

我们发现一个性质：排列可以造出的和为$[\sum_{i=1}^n i,\sum_{i=1}^n max(i,n-i+1)]$

所以$<\sum_{i=1}^n i$的输出$-1$，$\geq \sum_{i=1}^n max(i,n-i+1)$的仿造样例2输出

现在$k$的范围变成了$[\sum_{i=1}^n i,\sum_{i=1}^n max(i,n-i+1))$

构造方式：

设当前的未填数区间为$[L,R]$，如果填进$R$之后的和$\leq k$就填$R$，否则填$L$

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=1000010;
ll n,k,l,r,a[N],b[N];

int main(){
	cin>>n>>k;
	for(ll i=1; i<=n; i++){
		l+=i;
		r+=max(n-i+1,i);
	}
	if(k<l){
		cout<<-1<<endl;
		return 0;
	}
	if(k>=r){
		cout<<r<<endl;
		for(ll i=1; i<=n; i++) printf("%lld ",i);
		putchar('\n');
		for(ll i=1; i<=n; i++) printf("%lld ",n-i+1);
		return 0;
	}
	for(ll i=1; i<=n; i++) a[i]=i;
	for(ll i=1; i<=n; i++) b[i]=n-i+1;
	ll L=1,R=n,sum=l;
	for(ll i=1; i<=n; i++){
		if(R>=a[i]&&sum+R-a[i]<=k){
			sum+=R-a[i];
			b[i]=R--;
		}
		else b[i]=L++;
	}
	printf("%lld\n",k);
	for(ll i=1; i<=n; i++) printf("%lld ",a[i]);
	putchar('\n');
	for(ll i=1; i<=n; i++) printf("%lld ",b[i]);
	return 0;
}

```

---

## 作者：fade_away (赞：3)

# Solution

虾搞了一个做法，感觉和其他人的都有点区别。

我们考虑最终产生贡献的数是哪些，我们把所有 $2n$ 个数从大到小写成一行：$n,n,n-1,n-1,...1,1$ ，然后把对答案有贡献的数当成左括号，没有贡献的当成右括号，这样会产生一个括号序列，贡献的和相当于每个左括号位置对应的数的和。

可以发现当这个括号序列合法时，必然是有解的（因为此时每一对对应的括号的位置的奇偶性不同，且相邻括号位置奇偶性不同）具体构造方法为：对于一对对应的括号的位置 $(p,q)$ ，倘若 $p$ 是偶数，则把 $p,q$ 分别放在两个排列的开头，倘若 $p$ 是奇数，则把 $q,p$ 分别放在两个排列的末尾。

当答案最小时括号序列显然是 $()()()()\dots()$ ，然后考虑让答案变大，我们可以贪心地从前往后把每个左括号尽量往前移，不难发现这样可以遍历到所有可能产生的答案。

时间复杂度 $O(n)$。

## Code 

```cpp
ll n, m;
int flag[MAXN], c[MAXN], Ans0[MAXN], Ans1[MAXN], stk[MAXN];

signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	read(n), read(m);
	if (m < (n * (n + 1) >> 1)) { print(-1); return 0; }
	m -= n * (n + 1) >> 1;
	flag[1] = 1;
	for (int i = 1; i <= n ; ++ i) c[i * 2 - 1] = c[i * 2] = n - i + 1;
	for (int i = 2; i <= n ; ++ i) {
		int t = i * 2 - 1;
		if (m > c[i] - c[t]) m -= c[i] - c[t], flag[i] = 1;
		else {
			while (m) m -= (c[t - 1] - c[t]), -- t;
			flag[t] = 1;
			for (int j = i + 1; j <= n ; ++ j) flag[j * 2 - 1] = 1;
			break;
		}
	}
	ll ans = 0;
	int L = 1, R = n, top = 0;
	for (int i = 1; i <= n + n ; ++ i) {
		if (flag[i]) stk[++ top] = c[i], ans += c[i];
		else {
			if (i & 1) Ans0[L] = c[i], Ans1[L] = stk[top --], ++ L;
			else Ans1[R] = c[i], Ans0[R] = stk[top --], -- R;
		}
	}

	print(ans), putc('\n');
	for (int i = 1; i <= n ; ++ i) print(Ans0[i]), putc(' ');
	putc('\n');
	for (int i = 1; i <= n ; ++ i) print(Ans1[i]), putc(' ');
	putc('\n');
	return 0;
}
```


---

## 作者：caidzh (赞：3)

其实是很傻逼的一道题，不知道为什么放在了$G$

首先我们定义第一个跑道上的序列为$A$，第二个为$B$

那么我们钦定$A={1,2,3,...}$，下面我们只对$B$进行操作，容易发现这是与原题意等价的

然后我们先把$A$与$B$匹配的价值调到最小，也就是使得$B={1,2,3,...}$

接下来我们考虑把后面的数换到前面去使得价值变大，我们知道如果只把后面的任意一个位置的数提到第一个位置，然后数整体后移，能产生的最大贡献是$n-1$，当然如果$k\le n-1$，那么这一次交换已经可以达成目的了，因为这次交换提升的价值一定包含$1$到$n-1$所有的数

如果$k>n-1$，那么把$n$提到最前面的位置，接下来的问题是一个子问题，递推求解即可。

当然我也欢迎$hack$的辣！
```
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
int n,k,sum,a[1000010],Max,K,ans,used[1000010];
signed main()
{
	n=read();k=read();
	if(k<(n+1)*n/2){printf("-1");return 0;}k-=(n+1)*n/2;
	for(int i=1;i<=n/2;i++){
		if(k>n-(i*2-1)){a[i]=n-i+1;used[n-i+1]=1;k-=(n-(i*2-1));Max=i;}
		else{a[i]=i+k;used[i+k]=1;Max=i;break;}
	}int p=1;
	for(int i=Max+1;i<=n;i++){while(used[p])p++;a[i]=p;used[p]=1;}
	for(int i=1;i<=n;i++)ans+=max(a[i],i);cout<<ans<<endl;
	for(int i=1;i<=n;i++)printf("%d ",i);printf("\n");
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
```


---

## 作者：KDL_ANIPLEX (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1244G)

超水蓝题。

感觉思路挺独特的。

首先，容易发现对于 $p$，输出 $1$ 到 $n$，只改变 $q$ 即可。

其次，不看 $k$，知道结果最大时为 $p$，$q$相反（样例一、二）；结果最小时为 $p$，$q$相同。

再次，最小结果大于 $k$ 时无解；最大结果小于等于 $k$ 时答案为最大结果。

猜想，若有解，最大结果大于 $k$ 时，一定能凑出 $k$，不理解看完就知道了。

我们设 $g$ 为 $k$ 减最小结果，我们要凑出 $k$，只能改变 $q$ 的顺序，将 $g$ 逐渐改变为零。

以下为正文。

贪心地，我们想让 $g$ 尽量快速地改变为零，于是将 $q$ 尽量为 $n$ 到 $1$。

循环，由前往后。$p$ 第 $i$ 位值为 $i$，$q$ 的对应位值为 $j$，若 $j>i$，$g$ 就减少了 $j-i$。

若此时 $g<j-i$，那么将 $j$ 修改为 $g+i$（$g+i$ 肯定没用过），此时 $g=0$，结果为 $k$。对于剩下的数，要保证不会有多贡献，从小到大输出即可。（感性理解：大的数都被用完啦，所以不会有多贡献）。

以下为代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, k;
signed main() {
	cin >> n >> k;
	if ((n + 1) * n / 2 > k) {
		cout << "-1\n";
		return 0;
	}//无解
	int ans;
	if (n % 2) ans = (n + n / 2) * (n / 2 + 1);
	else ans = (n + n / 2 + 1) * (n / 2);
	cout << min(ans, k) << endl; //答案
	for (int i = 1; i <= n; i++)
		cout << i << " "; //p
	cout << "\n";
	int g = k - (n + 1) * n / 2;
	for (int i = 1, j = n; i <= n; i++, j--) {
		if (g >= j - i) { //情况一
			cout << j << " ";
			g -= max(1LL * 0, j - i);
		} else { //情况二
			cout << g + i << " ";
			int u = g + i;
			for (int op = 1; op <= j; op++)
				if (op != u) cout << op << " ";
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：k1saki (赞：2)

### - 前言：
# ~~这道G题好水啊~~  
#### 不会用LaTeX请见谅
### - 题意：  
给定$n,k$,求出$1$~$n$的两个排列,求$∑max(ai,bi)(1<=i<=n)$  
但不能超过$k$  
### - 思路  
显然可以发现$∑max(ai,bi)$最小时,两排列均为$1,2,3,...,n-1,n$  
此时$∑max(ai,bi)=n*(n+1)/2$,如果该值已经大于$k$  
显然不可能实现,输出$-1$  
如果还不足$k$,每次操作时将未经过交换的最小的$ai$,和最大的$aj$进行交换,  
将$k$减去$a(n-i)-ai$  
如果操作后大于$k$，改为交换$ai$和$ai+k$,然后输出初始的$k$和当前排列  
### - 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,a[1000005],b[1000005];
int main() {
	cin>>n>>k;
	long long kk=k;
	if (n*(n+1)/2>k)
	{
		puts("-1");
		return 0;
	}
	for (int i=1;i<=n;i++)
		a[i]=i,b[i]=i;
	k-=n*(n+1)/2;
	for (int i=1;i<=n/2;i++)
	{
		if ((n-2*i+1)>=k)
		{
			int tmp=i+k;
			swap(a[i],a[tmp]);//大于k则交换ai，ai+k
			cout<<kk<<endl;
			for (int j=1;j<=n;j++)
				printf("%lld ",a[j]);
			puts("");
			for (int j=1;j<=n;j++)
				printf("%lld ",b[j]);//直接输出，结束程序
			return 0;
		}
		swap(a[i],a[n-i+1]);//交换
		k-=(n-2*i+1);
	}
	cout<<kk-k<<endl;
	for (int i=1;i<=n;i++)
		printf("%d ",i);
	puts("");
	for (int i=n;i>=1;i--)
		printf("%d ",i);//达不到k，输出
	return 0;
}
```

---

## 作者：osfly (赞：0)

### some interesting things:

xgf 哥哥要求布置的捏。

没看题解做出来了。

第一道独立做出来的 *2400！一发过！

---

### 正文

根据题意，首先能得出：

答案与顺序无关。

所以我们能令其中一个排列是有序的。

原题的式子就能变成：$\sum\limits^n_{i=1}\max(i,p_i)$。

考虑另外一个排列。将排列初始置为最小值。

然后就能发现一个东西：

如果将 $i$ 和 $n-i+1$ 两两交换定能取得最大值。

如果什么都不交换定能取得最小值。

那么，如果 $k<$ 最小值，此时肯定是无解的。

如果 $k>$ 最大值，答案一定是将 $i$ 和 $n-i+1$ 两两交换。

那么考虑 最小值 $\leq k\leq $ 最大值的情况。

容易发现此时答案就为 $k$。

令 $s$ 为当前的序列算出来的值与 $k$ 之间的差值。

我们发现如果交换两个未被交换过的 $(i,j)$，那它们对原式子的贡献为 $j-i$。

那我们可以去枚举 $i\ (1\leq i\leq \lfloor\frac{n}{2}\rfloor)$，令 $j=n-i+1$。

1. 如果 $k\leq j-i$，那么我们将 $i$ 和 $j$ 交换，并将 $s$ 减去 $j-i$，因为交换这一对的贡献是 $j-i$。

2. 否则，则交换 $(i,i+s)$，这样的贡献是 $s$，刚刚好。

代码很好写，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e6+10;
ll n,k;
int ans[N];
int main()
{
	scanf("%lld%lld",&n,&k);
	if(k<n*(1+n)>>1)
	{
		printf("-1");
		return 0;
	}
	ll maxn=0;
	for(int i=1;i<=n;i++)
	{
		int j=n-i+1;
		maxn+=max(i,j);
	}
	if(k>maxn)
	{
		printf("%lld\n",maxn);
		for(int i=1;i<=n;i++) printf("%d ",i);
		printf("\n");
		for(int i=n;i>=1;i--) printf("%d ",i);
		return 0;
	}
	printf("%lld\n",k);
	k-=n*(1+n)>>1;
	for(int i=1;i<=n;i++) printf("%d ",i),ans[i]=i;
	printf("\n");
	for(int i=1;i<=n>>1&&k;i++)
	{
		int j=n-i+1;
		if(k>=j-i) swap(ans[i],ans[j]),k-=j-i;
		else swap(ans[i],ans[i+k]),k=0;
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：YLWang (赞：0)

兔队（在某群）：这$G$不是$B$难度吗，惊了

我：啊我康康。

10min后，pp了。

这个$G$真的是简单。

首先我们将第一个序列固定不动，即$a_i = i$。这样我们只需要考虑$B$序列就可以了。

那么，使答案最小的$B$序列就是$1, 2, ..., n$. 使答案最大的$B$序列就是$n, n-1, n-2, ..., 1$.

容易使用贪心的方法构造出最小和最大答案之间的所有答案。

可以结合代码理解哦。

```
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define reaD() read()
#define pb push_back
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(register int i = (k); i >= (j); i--)
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define DEBUG printf("Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
#define int long long
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
#define MAXN 1000005
int n, k;
int a[1000005];
signed main()
{
	cin >> n >> k;
	if(k < n * (n + 1) / 2) {
		printf("-1\n");
		return 0;
	}
	For(i, 1, n) a[i] = i;
	int sum = n * (n + 1) / 2;
	int del = k - sum, ans = sum;
	for(int i = n; i >= (n+2)/2; i--) {
		if(i - (n-i+1) <= del) {
			del -= (i - (n - i + 1));
			swap(a[i], a[n-i+1]);
		} else {
			int pos = i - del;
			swap(a[i], a[pos]);
			del = 0;
			break;
		}
	}
	cout << k - del << endl;
	For(i, 1, n) printf("%d ", i);printf("\n");
	For(i, 1, n) printf("%d ", a[i]);
    return 0;
}
 
 
 ```



---

