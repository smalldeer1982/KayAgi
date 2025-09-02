# [UOI 2025] Simple Task

## 题目描述

我们称一个非空的正整数序列为*奇异*序列，如果其元素之和是一个质数。

给定一个长度为 $n$ 的数组 $a$，**其中的元素均为质数**。同时给定一个整数 $k$。

请将数组 $a$ 分割成 $k$ 个**非空**子序列$^1$，使得：
- 数组 $a$ 的每个元素恰好属于其中一个子序列；
- 在这些子序列中，*奇异*序列的数量尽可能少。

本题每个测试包含多组输入数据，你需要分别独立处理每组数据。

**注意：本题没有"无额外限制"的评分 Subtask。**

## 说明/提示

$^1$ 序列 $c$ 称为数组 $b$ 的子序列，如果可以通过从数组 $b$ 中删除若干元素（可能为零个）来得到序列 $c$。

### 评分标准

- （$2$ 分）：$T \leq 20$，$k=1$；
- （$5$ 分）：$n \leq 4$，所有 $1\le i\le n$ 满足 $a_i \leq 10^4$；
- （$8$ 分）：$T \leq 20$，$n \leq 10$，所有 $1\le i\le n$ 满足 $a_i \leq 10^4$；
- （$4$ 分）：$n$ 为偶数，所有 $1\le i\le n$ 满足 $a_i > 2$；
- （$18$ 分）：$n$ 为奇数，所有 $1\le i\le n$ 满足 $a_i > 2$；
- （$10$ 分）：$2\cdot k \ge n + 1$；
- （$29$ 分）：$n$ 为偶数；
- （$24$ 分）：$n$ 为奇数。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 1
5 5 13
4 2
2 3 5 7
5 3
3 3 5 5 13
6 5
2 2 2 3 3 3```

### 输出

```
1
3 13 5 5
0
2 2 7
2 3 5
1
1 13
2 3 3
2 5 5
4
1 2
1 2
1 2
1 3
2 3 3```

# 题解

## 作者：cwfxlh (赞：2)

## [P12551 [UOI 2025] Simple Task](https://www.luogu.com.cn/problem/P12551)   

分讨题，细节比较多，单纯的恶心人，实际思维难度应该没有黑。为了理解方便，下文中忽略了若干没有难度的细节。      

特判掉 $k=1$。     

部分分启发很好，先看部分分。   

### $n$ 是偶数

如果 $a_i$ 全是奇质数，那么方案是显然的，每次合并两个奇质数为偶数，如果全是偶数了那就随便合。这样每操作一次就少俩质数，显然最优。    

如果加上 2 会怎么样呢。   

如果奇质数的数量和 2 的数量都是偶数，那么按照上一种情况的做法也是可以的（注意这里要区分 2 和大于 2 的偶数）。    

有了这个合并的想法，于是我们可以做 $k<\frac{n}{2}$ 了，这是简单的。

如果奇质数的数量和 2 的数量都是奇数该怎么办呢。如果存在一个奇质数 $a_x$ 满足 $a_x+2$ 不是质数，那么将它与一个 2 配对起来，把剩下的数按照上一种情况去合并就可以了。    

接下来可以解决 $k=\frac{n}{2}$ 了，因为找不到 $a_x+2$ 是奇合数，所以怎么划分答案都不会小于 1，直接将相邻两个匹配就可以了。

如果找不到这个数，那么考虑 $p,p+2,p+4$ 模 3 的余数互不相同，所以当 $p\not=3$ 时 $p+4$ 一定是合数。尝试将一个奇质数与两个 2 配对，配对完成后剩下偶数个奇质数，奇数个 2，将多出来那个 2 随便合并一下就可以了。    

但是如果所有的奇质数都是 3，上面的做法就不管用了。有两种办法，一种是取 3 个 3 拼成一个 9，另一种是取 3 个 2 和一个 3 拼一个 9，两种方法必定会有一个可行。    

如果你找不到一个奇质数 +2 是合数，此时如果 2 的个数是 1，那拼出 $p+4$ 的做法又废掉了，不过此时我们有：奇质数的数量大于 3（小于等于 3 的前面都被解决了）。   

考虑如下结论：任意 5 个奇质数中，一定能选出 3 个奇质数的和是合数。分讨他们模 3 的余数即可证明这个结论（这里奇质数等于 3 是允许的）。      

在前 5 个奇质数中选出 3 个合成一个合数，然后将剩下两个与 1 个 2 合并，问题就解决了，将偶数随便合并即可。     

### $n$ 是奇数   

同理可以做掉 $k<\frac{n}{2}$。   

如果全是奇质数，那么在前 5 个奇质数中找 3 个合并成合数，这部分就解决了。   

如果 2 的数量是奇数，那么将偶数个奇质数两两合并，然后再将多出来的 2 加到某一对上面。   

如果 2 的数量是偶数，则仿照上面，如果能找到一个奇质数满足其 +2 后是合数，那么两者匹配，剩余奇数个 2 和偶数个奇质数，将奇质数合并后把多出来那一个 2 加过去。否则考虑找一个不是 3 的奇质数，将其与两个 2 合并。     

如果奇质数全是 3，当 3 的数量大于 1 的时候，选择将 3 个 3 合成一个 9，否则选择 3 个 2 和一个 3 合成一个 9。       

于是问题就解决了，复杂度 $O(n\log n)$。真是一场酣畅淋漓的食雪啊。    

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int testnum,n,k,a[100003],k1,k2,k3,k4,k5,k6,k7,k8,k9,bcj[100003],cnt2,rk;
int finf(int xx){if(bcj[xx]!=xx)bcj[xx]=finf(bcj[xx]);return bcj[xx];}
vector<int>lst[100003];
bool isp(int xx){
	for(int i=2;i*i<=xx;i++)if(xx%i==0)return false;
	return true;
}
void printans(){
	for(int i=1;i<=n;i++){lst[i].clear();lst[i].shrink_to_fit();}
	for(int i=1;i<=n;i++)lst[finf(i)].emplace_back(i);
	k1=0;k3=0;
	for(int i=1;i<=n;i++){
		if(lst[i].size()!=0){
			k2=0;
			for(auto j:lst[i])k2+=a[j];
			if(isp(k2))k1++;
		}
	}
	cout<<k1<<'\n';
	for(int i=1;i<=n;i++){
		if(lst[i].size()!=0){
			cout<<lst[i].size()<<' ';
			for(auto j:lst[i])cout<<a[j]<<' ';
			cout<<'\n';
		}
	}
	return;
}
void merge(int xx,int yy){
	if(xx<1||xx>n||yy<1||yy>n||finf(xx)==finf(yy)||k<=0)return;
	k--;bcj[finf(xx)]=finf(yy);
	return;
}
void smpmerge(){
	for(int i=1;i<n;i+=2)merge(i,i+1);
	for(int i=1;i<n;i++)merge(i,i+1);
	printans();
	return;
}
void sol(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	cnt2=0;
	for(int i=1;i<=n;i++)cnt2+=(a[i]==2);
	for(int i=1;i<=n;i++)bcj[i]=i;
	if(k==1){
		for(int i=1;i<=n;i++)bcj[i]=1;
		printans();
		return;
	}
	k=n-k;
	rk=k;
	if(n%2==1&&cnt2%2==1){
		for(int i=cnt2+1;i<=n;i+=2)merge(i,i+1);
		for(int i=1;i+1<=cnt2;i+=2)merge(i,i+1);
		merge(cnt2,cnt2+1);
		if(cnt2==n)merge(cnt2-1,cnt2);
		for(int i=1;i<n;i++)merge(i,i+1);
		printans();
		return;
	}
	if(n%2==1&&cnt2%2==0){
		if(k<=(n/2)){
			for(int i=1;i+1<=cnt2;i+=2)merge(i,i+1);
			for(int i=cnt2+1;i+1<=n;i+=2)merge(i,i+1);
			printans();
			return;
		}
		if(cnt2>0){
			for(int i=cnt2+1;i<=n;i++)if(a[i]!=3)swap(a[i],a[cnt2+1]);
			if(a[cnt2+1]==3){
				if(cnt2+1==n){
					for(int i=1;i+1<n-4;i+=2)merge(i,i+1);
					merge(n,n-1);merge(n-1,n-2);merge(n-2,n-3);
					merge(n-4,n-5);
					for(int i=1;i<n;i++)merge(i,i+1);
					printans();
					return;
				}
				merge(n-2,n-1);merge(n-1,n);
				for(int i=1;i+1<n-2;i+=2)merge(i,i+1);
				for(int i=1;i<n;i++)merge(i,i+1);
				printans();
				return;
			}
			for(int i=1;i+1<=cnt2-2;i+=2)merge(i,i+1);
			for(int i=cnt2+2;i+1<=n;i+=2)merge(i,i+1);
			if(!isp(a[cnt2+1]+2)){
				merge(cnt2,cnt2+1);
				if(cnt2>2)merge(cnt2-1,cnt2-2);
				else merge(cnt2-1,cnt2+2);
				for(int i=1;i<n;i++)if(finf(i)!=finf(cnt2)&&finf(i+1)!=finf(cnt2))merge(i,i+1);
				merge(1,n);
				printans();
				return;
			}
			merge(cnt2,cnt2+1);merge(cnt2-1,cnt2);
			for(int i=1;i<n;i++)if(finf(i)!=finf(cnt2)&&finf(i+1)!=finf(cnt2))merge(i,i+1);
			merge(1,n);
			printans();
		}
		else{
			int flg=0;
			for(int i=1;i<=5&&flg==0;i++){
				for(int j=i+1;j<=5&&flg==0;j++){
					for(int u=j+1;u<=5&&flg==0;u++){
						if((a[i]+a[j]+a[u])%3==0){
							swap(a[n],a[u]);
							swap(a[n-1],a[j]);
							swap(a[n-2],a[i]);
							merge(n,n-1);merge(n-1,n-2);
							flg=1;
						}
					}
				}
			}
			for(int i=1;i+1<=n-3;i+=2)merge(i,i+1);
			for(int i=1;i<n;i++)merge(i,i+1);
			printans();
			return;
		}
	}
	if(n%2==0&&cnt2%2==0){smpmerge();return;}
	if(n%2==0&&cnt2%2==1){
		if(k<(n/2)){
			for(int i=1;i<n;i+=2)if(a[i]%2==a[i+1]%2)merge(i,i+1);
			printans();
			return;
		}
		for(int i=cnt2+1;i<=n;i++){
			if(!isp(a[i]+2)){
				swap(a[i],a[n]);
				swap(a[cnt2],a[n-1]);
				smpmerge();
				return;
			}
		}
		if(k==(n/2)){smpmerge();return;}
		if(cnt2>1){
			for(int i=cnt2+1;i<=n;i++)if(a[i]!=3)swap(a[i],a[cnt2+1]);
			if(a[cnt2+1]==3){
				if(cnt2+1==n){
					for(int i=1;i+1<=n;i+=2)merge(i,i+1);
					merge(cnt2-1,cnt2);
					smpmerge();
					return;
				}
				if(cnt2>1){
					swap(a[n-1],a[cnt2]);
					swap(a[n-2],a[cnt2-1]);
					swap(a[n-3],a[cnt2-2]);
					for(int i=n-3;i<n;i++)merge(i,i+1);
					for(int i=1;i+1<n-3;i+=2)merge(i,i+1);
					for(int i=1;i<n;i++)merge(i,i+1);
					printans();
					return;
				}
				for(int i=2;i+1<n-2;i+=2)merge(i,i+1);
				merge(n-2,n-1);merge(n-1,n);
				for(int i=1;i<n;i++)merge(i,i+1);
				printans();
				return;
			}
			merge(cnt2,cnt2+1);merge(cnt2-1,cnt2);
			if(cnt2>3)merge(cnt2-2,cnt2-3);
			else merge(cnt2-2,cnt2+2);
			for(int i=1;i<cnt2-3;i+=2)merge(i,i+1);
			for(int i=cnt2+2;i<=n;i+=2)merge(i,i+1);
			for(int i=1;i<n;i++)if(finf(i)!=finf(cnt2)&&finf(i+1)!=finf(cnt2))merge(i,i+1);
			merge(1,n);
			printans();
		}
		else{
			int flg=0;
			for(int i=2;i<=6&&flg==0;i++){
				for(int j=i+1;j<=6&&flg==0;j++){
					for(int u=j+1;u<=6&&flg==0;u++){
						if((a[i]+a[j]+a[u])%3==0){
							swap(a[n],a[u]);
							swap(a[n-1],a[j]);
							swap(a[n-2],a[i]);
							flg=1;
						}
					}
				}
			}
			merge(n-2,n-1);merge(n-1,n);
			for(int i=2;i+1<n-2;i+=2)merge(i,i+1);
			for(int i=1;i<n;i++)merge(i,i+1);
			printans();
		}
		return;
	}
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>testnum;
	while(testnum--)sol();
	return 0;
}
```

---

## 作者：Monomial (赞：1)

大型分讨题。
		
我们先尝试解决一些简单的 case，然后进行拓展。

- $k=1$
		
直接 check 和是不是质数即可。
		
- $2k \geq n+1$
		
容易发现在此情况下肯定有一些子序列必须长度为 $1$，于是我们就考虑让长度为 $1$ 的子序列个数尽量少，即去缩短剩余子序列的长度。
		
我们将 $a_{i}$ 分为 $a_{i}=2$ 和 $a_{i} \not= 2$ 两类。同类之间两两形成的 pair 的和必然是合数，我们对其配对，其不重的配对数下界应当是 $\lceil \frac{n-1}{2} \rceil$，必然 $\geq k$。
		
- $2 \mid n$ 且 $a_{i} > 2$
		
注：后面的 case 默认保证 $2k \leq n$ 且 $k \not= 1$，因此会省略一些特判。
		
我们还是和刚刚一样考虑两两配对，这时我们一定能配出 $\frac{n}{2}$ 对，把前 $k-1$ 对分别塞进 $k-1$ 个子序列，剩下的全塞进最后一个。

- $2 \nmid n$ 且 $a_{i} > 2$

如果按之前的配对方法，现在会多出来一个数，那么意味着我们现在需要找到一个长度为 $3$ 的子序列满足其元素和为合数。
		
那么，我们考虑将 $a_{i}$ 按 $\bmod 3$ 分类。
		
由于前面的限制，此时有 $n \geq 5$，那么必然有三个数的和为 $3$ 的倍数。
		
考虑证明，如果三种余数都出现，显然从三种中各拿一个就能获得 $3$ 的倍数。而如果出现的种类数 $\leq 2$，那么必有一种出现次数 $\geq 3$，从这种中取 $3$ 个也能获得 $3$ 的倍数。
		
剩余部分和前面是类似的。 

- $2 \mid n$ 且 $a_{1}=2$
		
在这个 case 内，我们先判掉一些简单的情况，我们设 $c_{2}$ 为 $2$ 出现次数。
		
$2 \mid c_{2}$ 是非常容易的，我们仍然可以完成配对。否则我们尝试在 $a_{i} > 2$ 的数中尝试找到一个和 $2$ 配对和为合数的，这样也可以直接配对解决。
	
另外我们需要判掉 $n=4$ 和 $n=2k$ 的情况。
		
接下来我们的想法是，找到一个长度为 $3,4$ 的子序列，使其和为合数。
		
我们此时再次对 $a_{i}$ 分类，此时可以分为 $3$ 类：$a_{i} = 2,a_{i} = 3,a_{i} \equiv 5 \pmod 6$，记作 $2,3,5$。

我们尝试找出一些简单的方案，例如，有 $\{2,3,5,5\},\{2,2,2,3\}$ 是合法的，这样我们将剩余的转化为了 $2 \mid n$ 且 $2 \mid c_{2}$ 的问题。
		
接下来，还有 $\{2,3,5\},\{2,2,5\}$ 是合法的，这样我们将剩余的转化为了 $2 \nmid n$ 且 $2 \nmid c_{2}$ 的问题，后面会提到这样的问题也是简单的。
		
经过一些简单的讨论，可以发现我们只剩下了 $2,3,3,\dots,3$ 和 $2,5,5,\dots,5$ 两种情况，统一记作 $2,x,x,\dots,x$。
		
我们将其分成 $\{2,x,x\},\{x,x,x\},x,x,\dots,x$。此时，剩下单独的 $x$ 可以两两配对，我们将其塞满剩余的空子序列后，接到 $\{2,x,x\}$ 后即可。

至此，我们解决了 $2 \mid n$ 的 case。

- $2 \nmid n$ 且 $a_{1}=2$

我们沿用上一个 case 的记号。
		
$2 \nmid c_{2}$ 的情况是简单的，我们去掉一个 $2$，然后视作 $2 \mid n$ 且 $2 \mid c_{2}$ 的问题，此时所有的子序列的和都是偶数，我们将 $2$ 塞进任意一个子序列即可，在 $2 \nmid c_{2}$ 时我们同样考虑用一个 $>2$ 的数和 $2$ 配对。
		
我们再次尝试去找一些长度为 $3$ 的子序列，使其和为合数。例如，$\{3,3,3\},\{5,5,5\}$ 是合法的
		，这样我们将剩余的转化为了 $2 \mid n$ 且 $2 \mid c_{2}$ 的问题。

那么（我们此时以同样方法记 $c_{3},c_{5}$），最后我们只剩下这几种情况：$c_{3}=0/2,c_{5}=1$ 和 $c_{3}=1,c_{5}=0/2$。

对于前者，我们构造 $\{2,2,5\}$，剩下配对即可；对于后者，需要做一些简单的讨论，若 $c_{5}=2$，我们构造 $\{2,2,5\},\{3,5\}$，剩下配对；若 $c_{5}=0$ 且 $2k+1=n$，那么必有一个子序列和为质数，否则我们构造 $\{2,2,2,3\}$，剩下配对，多出的 $2$ 塞进其他的子序列。 
				
至此，我们解决了 $2 \nmid n$ 的 case，也就成功解决了这题！
		
时间复杂度 $\mathcal{O}(n)$。

---

## 作者：EuphoricStar (赞：1)

首先特判 $m = 1$ 和 $m = n$。接下来令 $m = n - m$，这样 $m$ 表示合并的次数。

注意到我们一次合并可以合并 $2, 2$ 和两个奇质数 $p_i, p_j$，这样会使质数数量减 $2$。

所以自然是根据奇质数个数的奇偶性讨论。

如果有偶数个奇质数，那么我们可以把奇质数两两配对，把 $2$ 两两配对，如果有奇数个 $2$ 那么把剩下的 $2$ 随便并到另一个集合内。这样除了最后一次合并，每次合并质数数量都减 $2$，是最优的。

如果有奇数个奇质数，设奇质数个数为 $t$。

首先若 $m \le \left\lfloor\frac{t}{2}\right\rfloor + \left\lfloor\frac{n - t}{2}\right\rfloor$ 那么可以把 $2$ 和奇质数两两配对的次数比需要的多，所以直接把 $2$ 和奇质数两两配对即可。

否则注意到我们最后一定至多剩下一个质数。所以只需判是否能让剩下的数都不是质数。

只需依次判断是否存在 $p_i + 2$，$p_i + 2 + 2$，$p_i + p_j + p_k$，$p_i + 2 + 2 + 2$，$p_i + p_j + p_k + 2$，$p_i + p_j + p_k + 2 + 2$ 不是质数，其中 $p_i, p_j, p_k$ 为位置互不相同的奇质数。若存在则把它们合并，再把剩下的奇质数和 $2$ 两两配对即可。这部分发现枚举量其实很难卡满，所以暴力枚举即可。

注意到 $p_i + 2$，$p_i + 2 + 2$，$p_i + 2 + 2 + 2$ 恰好有一个是 $3$ 的倍数，$p_i + p_j + p_k$，$p_i + p_j + p_k + 2$，$p_i + p_j + p_k + 2 + 2$ 同理。所以如果上述情况都不存在，说明 $2$ 的个数 $\le 3$，且不存在 $x$ 使得 $\bmod 3 = x$ 的奇质数有 $\ge 3$ 个，且不能同时存在 $\bmod 3 = 0, \bmod 3 = 1, \bmod 3 = 2$ 的奇质数。这样奇质数的数量 $\le 4$，所以不用判断能不能选出 $5$ 个或者个数更多的奇质数。

代码比较精神污染。

```cpp
// Problem: P12551 [UOI 2025] Simple Task
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12551
// Memory Limit: 256 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 100100;
const int N = 3000000;

ll n, m, a[maxn];
int pr[N], tot;
bool vis[N + 5];

inline void init() {
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) {
			pr[++tot] = i;
		}
		for (int j = 1; j <= tot && i * pr[j] <= N; ++j) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				break;
			}
		}
	}
}

inline bool check(ll x) {
	if (x <= N) {
		return !vis[x];
	}
	for (int i = 1; i <= tot && 1LL * pr[i] * pr[i] <= x; ++i) {
		if (x % pr[i] == 0) {
			return 0;
		}
	}
	return 1;
}

int fa[maxn], b[maxn];
ll f[maxn];
vector<int> vc[maxn];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

inline void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		fa[x] = y;
		f[y] += f[x];
	}
}

void solve() {
	scanf("%lld%lld", &n, &m);
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		cnt += (a[i] == 2);
		fa[i] = i;
		f[i] = a[i];
		vector<int>().swap(vc[i]);
	}
	if (m == 1) {
		ll sum = 0;
		for (int i = 1; i <= n; ++i) {
			sum += a[i];
		}
		printf("%d\n%lld ", check(sum), n);
		for (int i = 1; i <= n; ++i) {
			printf("%lld%c", a[i], " \n"[i == n]);
		}
		return;
	}
	m = n - m;
	if (!m) {
		printf("%lld\n", n);
		for (int i = 1; i <= n; ++i) {
			printf("1 %lld\n", a[i]);
		}
		return;
	}
	if ((n - cnt) % 2 == 0) {
		for (int i = cnt + 1; i < n && m; i += 2) {
			merge(i, i + 1);
			--m;
		}
		for (int i = 1; i < cnt && m; i += 2) {
			merge(i, i + 1);
			--m;
		}
		if (m && (cnt & 1)) {
			for (int i = 1; i <= n; ++i) {
				if (i != cnt && fa[i] == i && f[i] % 2 == 0) {
					merge(cnt, i);
					--m;
					break;
				}
			}
		}
		int lst = 0;
		for (int i = 1; i <= n; ++i) {
			if (fa[i] == i) {
				if (lst && m) {
					merge(lst, i);
					--m;
				}
				lst = i;
			}
		}
	} else if (m <= cnt / 2 + (n - cnt) / 2) {
		for (int i = cnt + 1; i < n && m; i += 2) {
			merge(i, i + 1);
			--m;
		}
		for (int i = 1; i < cnt && m; i += 2) {
			merge(i, i + 1);
			--m;
		}
	} else {
		bool fl = 0;
		if (cnt && m >= cnt / 2 + (n - cnt - 1) / 2 + 1) {
			for (int i = cnt + 1; i <= n; ++i) {
				if (!check(a[i] + 2)) {
					merge(cnt, i);
					--m;
					fl = 1;
					break;
				}
			}
			if (fl) {
				int lst = 0;
				for (int i = cnt + 1; i <= n && m; ++i) {
					if (fa[i] != i || f[i] != a[i]) {
						continue;
					}
					if (lst) {
						merge(i, lst);
						lst = 0;
						--m;
					} else {
						lst = i;
					}
				}
				for (int i = 1; i + 2 <= cnt; i += 2) {
					merge(i, i + 1);
					--m;
				}
				if (m && cnt % 2 == 0) {
					for (int i = 1; i <= n; ++i) {
						if (i != cnt - 1 && fa[i] == i && f[i] % 2 == 0) {
							merge(i, cnt - 1);
							--m;
							break;
						}
					}
				}
				lst = 0;
				for (int i = 1; i <= n; ++i) {
					if (fa[i] == i) {
						if (f[i] & 1) {
							continue;
						}
						if (lst && m) {
							merge(lst, i);
							--m;
						}
						lst = i;
					}
				}
			}
		}
		if (!fl && cnt >= 2 && m >= (cnt - 1) / 2 + (n - cnt - 1) / 2 + 2) {
			for (int i = cnt + 1; i <= n; ++i) {
				if (!check(a[i] + 4)) {
					merge(cnt, i);
					merge(cnt - 1, i);
					m -= 2;
					fl = 1;
					break;
				}
			}
			if (fl) {
				int lst = 0;
				for (int i = cnt + 1; i <= n && m; ++i) {
					if (fa[i] != i || f[i] != a[i]) {
						continue;
					}
					if (lst) {
						merge(i, lst);
						lst = 0;
						--m;
					} else {
						lst = i;
					}
				}
				for (int i = 1; i <= cnt - 3 && m; i += 2) {
					merge(i, i + 1);
					--m;
				}
				if (m && cnt >= 3 && (cnt & 1)) {
					for (int i = 1; i <= n; ++i) {
						if (i != cnt - 2 && fa[i] == i && f[i] % 2 == 0) {
							merge(i, cnt - 2);
							--m;
							break;
						}
					}
				}
				lst = 0;
				for (int i = 1; i <= n; ++i) {
					if (fa[i] == i) {
						if (f[i] & 1) {
							continue;
						}
						if (lst && m) {
							merge(lst, i);
							--m;
						}
						lst = i;
					}
				}
			}
		}
		if (!fl && n - cnt >= 3 && m >= (cnt + 1) / 2 + (n - cnt - 3) / 2 + 2) {
			for (int i = cnt + 1; i <= n && !fl; ++i) {
				for (int j = i + 1; j <= n && !fl; ++j) {
					for (int k = j + 1; k <= n && !fl; ++k) {
						if (!check(a[i] + a[j] + a[k])) {
							merge(i, j);
							merge(j, k);
							m -= 2;
							fl = 1;
							break;
						}
					}
				}
			}
			if (fl) {
				int lst = 0;
				for (int i = cnt + 1; i <= n && m; ++i) {
					if (fa[i] != i || f[i] != a[i]) {
						continue;
					}
					if (lst) {
						merge(i, lst);
						lst = 0;
						--m;
					} else {
						lst = i;
					}
				}
				for (int i = 1; i < cnt && m; i += 2) {
					merge(i, i + 1);
					--m;
				}
				if (m && (cnt & 1)) {
					for (int i = 1; i <= n; ++i) {
						if (i != cnt && fa[i] == i && f[i] % 2 == 0) {
							merge(cnt, i);
							--m;
							break;
						}
					}
				}
				lst = 0;
				for (int i = 1; i <= n; ++i) {
					if (fa[i] == i) {
						if (f[i] & 1) {
							continue;
						}
						if (lst && m) {
							merge(lst, i);
							--m;
						}
						lst = i;
					}
				}
			}
		}
		if (!fl && cnt >= 3 && m >= (cnt - 2) / 2 + (n - cnt - 1) / 2 + 3) {
			for (int i = cnt + 1; i <= n; ++i) {
				if (!check(a[i] + 6)) {
					merge(cnt, i);
					merge(cnt - 1, i);
					merge(cnt - 2, i);
					m -= 3;
					fl = 1;
					break;
				}
			}
			if (fl) {
				int lst = 0;
				for (int i = cnt + 1; i <= n && m; ++i) {
					if (fa[i] != i || f[i] != a[i]) {
						continue;
					}
					if (lst) {
						merge(i, lst);
						lst = 0;
						--m;
					} else {
						lst = i;
					}
				}
				for (int i = 1; i <= cnt - 4 && m; i += 2) {
					merge(i, i + 1);
					--m;
				}
				if (m && cnt % 2 == 0) {
					for (int i = 1; i <= n; ++i) {
						if (i != cnt - 3 && fa[i] == i && f[i] % 2 == 0) {
							merge(i, cnt - 3);
							--m;
							break;
						}
					}
				}
				lst = 0;
				for (int i = 1; i <= n; ++i) {
					if (fa[i] == i) {
						if (f[i] & 1) {
							continue;
						}
						if (lst && m) {
							merge(lst, i);
							--m;
						}
						lst = i;
					}
				}
			}
		}
		if (!fl && n - cnt >= 3 && cnt && m >= cnt / 2 + (n - cnt - 3) / 2 + 3) {
			for (int i = cnt + 1; i <= n && !fl; ++i) {
				for (int j = i + 1; j <= n && !fl; ++j) {
					for (int k = j + 1; k <= n && !fl; ++k) {
						if (!check(a[i] + a[j] + a[k] + 2)) {
							merge(i, j);
							merge(j, k);
							merge(i, cnt);
							m -= 3;
							fl = 1;
							break;
						}
					}
				}
			}
			if (fl) {
				int lst = 0;
				for (int i = cnt + 1; i <= n && m; ++i) {
					if (fa[i] != i || f[i] != a[i]) {
						continue;
					}
					if (lst) {
						merge(i, lst);
						lst = 0;
						--m;
					} else {
						lst = i;
					}
				}
				for (int i = 1; i <= cnt - 2 && m; i += 2) {
					merge(i, i + 1);
					--m;
				}
				if (m && cnt % 2 == 0) {
					for (int i = 1; i <= n; ++i) {
						if (i != cnt - 1 && fa[i] == i && f[i] % 2 == 0) {
							merge(cnt - 1, i);
							--m;
							break;
						}
					}
				}
				lst = 0;
				for (int i = 1; i <= n; ++i) {
					if (fa[i] == i) {
						if (f[i] & 1) {
							continue;
						}
						if (lst && m) {
							merge(lst, i);
							--m;
						}
						lst = i;
					}
				}
			}
		}
		if (!fl && n - cnt >= 3 && cnt >= 2 && m >= (cnt - 1) / 2 + (n - cnt - 3) / 2 + 4) {
			for (int i = cnt + 1; i <= n && !fl; ++i) {
				for (int j = i + 1; j <= n && !fl; ++j) {
					for (int k = j + 1; k <= n && !fl; ++k) {
						if (!check(a[i] + a[j] + a[k] + 4)) {
							merge(i, j);
							merge(j, k);
							merge(i, cnt);
							merge(i, cnt - 1);
							m -= 4;
							fl = 1;
							break;
						}
					}
				}
			}
			if (fl) {
				int lst = 0;
				for (int i = cnt + 1; i <= n && m; ++i) {
					if (fa[i] != i || f[i] != a[i]) {
						continue;
					}
					if (lst) {
						merge(i, lst);
						lst = 0;
						--m;
					} else {
						lst = i;
					}
				}
				for (int i = 1; i <= cnt - 3 && m; i += 2) {
					merge(i, i + 1);
					--m;
				}
				if (m && (cnt & 1)) {
					for (int i = 1; i <= n; ++i) {
						if (i != cnt - 2 && fa[i] == i && f[i] % 2 == 0) {
							merge(cnt - 2, i);
							--m;
							break;
						}
					}
				}
				lst = 0;
				for (int i = 1; i <= n; ++i) {
					if (fa[i] == i) {
						if (f[i] & 1) {
							continue;
						}
						if (lst && m) {
							merge(lst, i);
							--m;
						}
						lst = i;
					}
				}
			}
		}
		if (!fl) {
			for (int i = 1; i < cnt && m; i += 2) {
				merge(i, i + 1);
				--m;
			}
			for (int i = cnt + 2; i < n && m; i += 2) {
				merge(i, i + 1);
				--m;
			}
			if (m && (cnt & 1)) {
				for (int i = 1; i <= n; ++i) {
					if (i != cnt && fa[i] == i && f[i] % 2 == 0) {
						merge(cnt, i);
						--m;
						break;
					}
				}
			}
			int lst = 0;
			for (int i = 1; i <= n; ++i) {
				if (fa[i] == i) {
					if (f[i] & 1) {
						continue;
					}
					if (lst && m) {
						merge(lst, i);
						--m;
					}
					lst = i;
				}
			}
			if (m) {
				merge(cnt, cnt + 1);
				--m;
			}
		}
	}
	int t = 0;
	for (int i = 1; i <= n; ++i) {
		t += (fa[i] == i && check(f[i]));
		vc[find(i)].pb(a[i]);
	}
	printf("%d\n", t);
	for (int i = 1; i <= n; ++i) {
		if (fa[i] == i) {
			printf("%d", (int)vc[i].size());
			for (int j : vc[i]) {
				printf(" %d", j);
			}
			putchar('\n');
		}
	}
}

int main() {
	init();
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：littlez_meow (赞：0)

序列其实是假的，就是集合。接下来称最少的和为质数的子序列数为答案。

题意等价于一次操作可以删掉两个数 $x,y$ 加入 $x+y$，求恰好操作 $n-k$ 次使得集合中质数尽可能少的方案数。称这个操作为合并。

跟着子任务分析。子任务三和正解关系不大，略。下面默认后面的子任务已经判掉了前面的子任务。

#### 子任务一 $k=1$

全部加起来判和是否为质数即可。

#### 子任务六 $2k\ge n+1$

你发现每次合并至多减少两个质数，所以答案的下界是 $n-2(n-k)=2k-n$ 和 $0$ 取 $\max$。当然在这个子任务下界直接就是 $2k-n$。

你发现我们每次合并要么取两个 $2$ 要么取两个奇质数就可以做到每次质数个数 $-2$ 了。由于 $2k\ge n+1$ 我们可以一直这样合并，所以可以取到下界。

#### 子任务二 $n\le 4$

判掉子任务一、六，只需要考虑 $n=4,k=2$。枚举两个分一组的 $3$ 种情况，取答案最小的划分方式即可。

由于 $4$ 个元素中一定存在两个奇偶性相同，把这两个合并剩下两个合并答案至多为 $1$。而一组 $3$ 个一组 $1$ 个答案至少为 $1$，所以不需要考虑一组三个一组一个。

#### 子任务四 $2|n,a_i>2$

下面认为 $1<k\le\lfloor\dfrac n 2\rfloor,n\ge 5$。由于 $n$ 是偶数可以加强成 $n\ge 6$。

由于现在全部都是奇数，可以直接先把奇数两两合并，没有奇数了随意合并，答案可以取到 $0$。

#### 子任务七 $2|n$

现在多了 $2$ 怎么办？

我们对 $2$ 个数的奇偶性分类。

若 $2$ 有偶数个，由于 $2|n$，因此奇质数也有偶数个。把奇质数两两合并，$2$ 两两合并，剩下的随意合并可以让答案取到 $0$。

若 $2$ 有奇数个，我们尝试找到一个奇质数 $x$，使得 $x+2$ 为合数。

如果我们找到了这样的 $x$，则合并 $2,x$，剩下的奇质数两两合并，$2$ 两两合并。此时只有一个元素是奇合数，其他都是偶数。因为 $k>1$，最后至少可以剩下两个元素。把偶数随意合并，答案可以取到下界 $0$。
 
如果我们找不到这样的 $x$，那么我们继续分类。

若 $k=\dfrac n 2$，你把一个 $2$ 和随便一个奇质数合并，剩下的和上面一样做，得到答案为 $1$。不难发现答案无法等于 $0$。

否则，至少可以合并 $\dfrac{n+2}2$ 次。我们先进行 $\dfrac{n+2}2$ 次合并，有如下四种情况：

+ 至少有 $3$ 个 $2$ 和 $1$ 个 $3$。这时可以用 $3$ 次合并把这四个数变成 $9$，然后剩下 $n-4$ 个数 $2$ 和奇质数分别两两合并。共合并 $\dfrac{n+2}2$ 次。

+ 至少有 $5$ 个 $2$。由于不存在元素 $x$ 使得 $x+2$ 为合数，故 $a$ 中所有奇质数 $x$ 均满足 $x\equiv 2\pmod 3$（因为模 $3$ 余 $1$ 则 $+2$ 为合数）或 $x=3$。刚刚已经判掉了有 $3$ 的情况，因此现在没有 $3$，于是先将其中 $3$ 个 $2$ 合并，再将 $2$ 个 $2$ 和任意奇质数合并，剩下的 $n-6$ 个数 $2$ 和奇质数分别两两合并。共合并 $\dfrac{n+2}2$ 次。

+ 恰好有 $3$ 个 $2$。因为 $n\ge 6$，所以至少有 $3$ 个奇质数。刚刚分析过 $a$ 中奇质数模 $3$ 余 $2$，故把 $3$ 个奇质数合并会得到合数。再把 $3$ 个 $2$ 合并，剩下的同理。共合并 $\dfrac{n+2}{2}$ 次。

+ 恰好有 $1$ 个 $2$。这个时候可以有 $3$，至少有 $5$ 个奇质数。你发现任意 $5$ 个质数中，都能选出 $3$ 个使得它们的和不是质数。因为质数模 $3$ 的余数只能为 $1,2$，根据鸽巢原理总有一个余数至少出现了 $3$ 次。又因为任意三个质数的和 $>3$，故为 $>3$ 的 $3$ 的倍数。选出和为合数的 $3$ 个奇质数合并，将 $1$ 个 $2$ 和另外 $2$ 个奇质数合并，剩下同理。共合并 $\dfrac{n+2}{2}$ 次。

现在我们手上只会有 $1$ 个奇合数和 $n-1$ 个偶数。多出来的合并次数拿来随意合并偶数即可，答案为 $0$。

#### 子任务五 $2\nmid n,a_i>2$

首先 $1<k\le \dfrac{n-1}2,n\ge 5$。

直接在前 $5$ 个数中找到和为合数的三个数，剩下的数两两合并，多出来的合并次数同子任务七。答案为 $0$。

#### 子任务八 $2\nmid n$

仿照子任务七进行分类讨论。

若 $2$ 的个数为奇数，则奇质数个数为偶数。先丢掉一个 $2$，剩下的奇质数两两合并，$2$ 两两合并，再将丢掉的 $2$ 和合并后的随意一个元素合并。多出来的合并次数同上。答案为 $0$。

若 $2$ 的个数为偶数，则奇质数个数为奇数。我们尝试找到一个奇质数的三元组，使得这三个奇质数之和为合数。

如果能找到，那么把这三个合并，剩下同理。多余的合并次数同上。答案为 $0$。

否则奇质数最多 $3$ 个，那么 $2$ 至少 $2$ 个。还有以下两种情况：

+ 至少存在一个 $\neq 3$ 的元素 $x$。将 $x$ 和 $2$ 个 $2$ 单独拎出来，剩下的奇质数和 $2$ 分别两两合并。如果 $x\equiv 1\pmod 3$，就将 $x$ 和 $1$ 个 $2$ 合并，另一个 $2$ 和合并后的随意一个偶数合并；如果 $x\equiv 2\pmod 3$，就将 $x$ 和 $2$ 个 $2$ 合并。这样只会进行 $\dfrac{n+1}2$ 次合并，多余的合并次数同上。

+ 所有元素都 $=3$，那么就只可能有 $1$ 个奇质数（否则可以选择 $3+3+3=9$ 为合数）。模仿子任务七，按照 $k$ 的取值分类：

  + 当 $k=\dfrac{n-1}2$，你的操作次数不足以支撑 $3$ 和 $3$ 个 $2$ 合并，因此答案至少为 $1$。把所有 $2$ 两两合并再把 $3$ 和随意一个合并后的元素合并即可取到下界。
 
  + 否则，$k\le\dfrac{n-3}2$。又因为 $n=5$ 时只能 $k=1$ 已经被子任务一判掉了，所以 $n\ge 7$，至少有 $6$ 个 $2$。那么就可以将其中 $3$ 个 $2$ 与 $3$ 合并，$3$ 个 $2$ 合并，剩下的 $2$ 两两合并，多余的合并次数同子任务七。答案为 $0$。
 
综上，我们只要实现子任务一、二、六、七、八即可。输入的 $a$ 已经给你排好序，所以时间复杂度 $O(\sum n)$，根据实现可能还会带一个筛质数的 $O(V)$ 或 $O(V\log\log V)$（线性筛或埃氏筛） 以及判断质数的 $O(\sqrt V\sum n)$ 或 $O(T\log V)$（暴力判或 Miller-Rabin），可能还需要并查集之类的维护带个 $\log n$ 或 $\alpha(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
using namespace std;
const int MAXN=3e5+1;
int n,k,ans;
bitset<MAXN>isp;
vector<int>seq[MAXN];
namespace Sub1{
inline void main(){
	ll sum=0;seq[1].resize(n);ans=1; 
	F(i,1,n){int a;cin>>a;sum+=a;seq[1][i-1]=a;}
	for(ll i=2;i*i<=sum;++i) if(sum%i==0) return ans=0,void();
}
}
namespace Sub6{
int c2;
vector<int>odd;
inline void main(){
	c2=0;vector<int>().swap(odd);ans=2*k-n;
	F(i,1,n){int a;cin>>a;if(a==2) ++c2;else odd.push_back(a);}
	F(i,1,n-k){
		if(c2>=2) seq[i].push_back(2),seq[i].push_back(2),c2-=2;
		else seq[i].push_back(odd.back()),odd.pop_back(),seq[i].push_back(odd.back()),odd.pop_back(); 
	}
	F(i,n-k+1,k){
		if(c2) seq[i].push_back(2),--c2;
		else seq[i].push_back(odd.back()),odd.pop_back();
	}
}
}
int a[MAXN],dsu[MAXN],id[MAXN];
int find(int x){return dsu[x]==x?x:dsu[x]=find(dsu[x]);}
inline void merge(int cnt,queue<int>&q){
	for(int i=cnt,x,y;i;--i){
		x=q.front();q.pop();y=q.front();q.pop();
		x=find(x),y=find(y);
		dsu[x]=y;q.push(y);
	}
	memset(id,0,sizeof(int)*(n+1));
	int qwq=0;
	F(i,1,n) if(dsu[i]==i) id[i]=++qwq;
	F(i,1,n) seq[id[find(i)]].push_back(a[i]);
}
namespace Sub2{
inline void main(){
	ll sum=0;ans=2;
	F(i,1,n) cin>>a[i],sum+=a[i];
	F(i,2,4){
		if(!isp[a[1]+a[i]]&&isp[sum-a[1]-a[i]]<ans){
			ans=isp[sum-a[1]-a[i]];seq[1].clear(),seq[2].clear();
			seq[1]={a[1],a[i]};
			F(j,2,4) if(j!=i) seq[2].push_back(a[j]); 
		}
		if(!isp[sum-a[1]-a[i]]&&isp[a[1]+a[i]]<ans){
			ans=isp[a[1]+a[i]];seq[1].clear(),seq[2].clear();
			seq[1]={a[1],a[i]};
			F(j,2,4) if(j!=i) seq[2].push_back(a[j]); 
		}
	}
}
}
namespace Sub7{
int c2;
inline void main(){
	c2=0;iota(dsu+1,dsu+n+1,1);ans=0;
	F(i,1,n) cin>>a[i],c2+=(a[i]==2);
	if(c2&1){
		int x=-1;
		F(i,1,n) if((a[i]&1)&&!isp[a[i]+2]){x=i,dsu[i]=c2;break;}
		if(x!=-1){
			queue<int>q;
			F(i,1,c2-1) q.push(i);
			F(i,c2+1,n) if(x!=i) q.push(i);
			return merge(n-k-1,q);
		}
		if(k==n/2){
			queue<int>q;ans=1;
			F(i,1,n) q.push(i);
			return merge(n-k,q);
		}
		if(c2>=3&&a[c2+1]==3){
			dsu[c2]=dsu[c2-1]=dsu[c2-2]=c2+1;
			queue<int>q;
			F(i,1,c2-3) q.push(i);
			F(i,c2+2,n) q.push(i);
			return merge(n-k-3,q);
		}
		if(c2>=5){
			dsu[c2]=dsu[c2-1]=c2+1;
			dsu[c2-3]=dsu[c2-4]=c2-2;
			queue<int>q;
			F(i,1,c2-5) q.push(i);
			F(i,c2+2,n) q.push(i);
			q.push(c2-2);
			return merge(n-k-4,q);
		}
		if(c2==3){
			dsu[c2-1]=dsu[c2-2]=c2;
			dsu[c2+1]=dsu[c2+2]=c2+3;
			queue<int>q;
			F(i,c2+4,n) q.push(i);
			q.push(c2);
			return merge(n-k-4,q);
		}
		if(c2==1){
			int x=0,y=0,z=0;
			F(i,2,6) F(j,i+1,6) F(t,j+1,6) if(!isp[a[i]+a[j]+a[t]]){x=i,y=j,z=t;break;}
			dsu[x]=dsu[y]=z;
			F(i,2,6) if(i!=x&&i!=y&&i!=z) dsu[i]=1;
			queue<int>q;
			F(i,7,n) q.push(i);
			q.push(1);
			return merge(n-k-4,q);
		}
		return;
	}
	queue<int>q;
	F(i,1,n) q.push(i);
	merge(n-k,q);
}
}
namespace Sub8{
int c2;
inline void main(){
	c2=0;iota(dsu+1,dsu+n+1,1);ans=0;
	F(i,1,n) cin>>a[i],c2+=(a[i]==2);
	if(c2&1){
		queue<int>q;dsu[1]=3;
		for(int i=2;i<=n;i+=2) dsu[i]=i+1,q.push(i+1);
		return merge((n-1)/2-k,q);
	}
	int x=-1,y,z,lim=min(c2+5,n);
	F(i,c2+1,lim) F(j,i+1,lim) F(t,j+1,lim) if(!isp[a[i]+a[j]+a[t]]){x=i,y=j,z=t;break;}
	if(x!=-1){
		dsu[x]=dsu[y]=z;
		queue<int>q;
		F(i,1,n) if(i!=x&&i!=y&&i!=z) q.push(i);
		return merge(n-k-2,q);
	}
	F(i,c2+1,n) if(a[i]!=3){x=i;break;}
	queue<int>q;
	if(x==-1){
		if(k==(n-1)/2){
			F(i,1,n) q.push(i);ans=1;
			return merge(n-k,q); 
		}
		dsu[c2]=dsu[c2-1]=dsu[c2-2]=c2+1;
		dsu[c2-4]=dsu[c2-5]=c2-3;
		F(i,1,c2-6) q.push(i);
		q.push(c2-3);
		return merge(n-k-5,q);
	}
	if(a[x]%3==1){
		dsu[1]=x;
		F(i,3,n) if(i!=x) q.push(i);
		q.push(2);
		merge(n-k-1,q);
	}else{
		dsu[1]=dsu[2]=x;
		F(i,3,n) if(i!=x) q.push(i);
		merge(n-k-2,q);
	}
}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	int T;
	isp[1]=1;
	for(int i=2;i*i<MAXN;++i) if(!isp[i]) for(int j=i*i;j<MAXN;j+=i) isp[j]=1;
	isp.flip();
	for(cin>>T;T;--T){
		F(i,1,k) vector<int>().swap(seq[i]);
		cin>>n>>k;
		if(k==1) Sub1::main();
		else if(2*k>=n+1) Sub6::main();
		else if(n<=4) Sub2::main();
		else if(n&1) Sub8::main();
		else Sub7::main();
		cout<<ans<<"\n";
		F(i,1,k){
			cout<<seq[i].size()<<" ";
			for(int j:seq[i]) cout<<j<<" ";
			cout<<"\n";
		}
	}
	return 0;
}
```

---

