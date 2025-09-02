# Swaps

## 题目描述

You are given two arrays $ a $ and $ b $ of length $ n $ . Array $ a $ contains each odd integer from $ 1 $ to $ 2n $ in an arbitrary order, and array $ b $ contains each even integer from $ 1 $ to $ 2n $ in an arbitrary order.

You can perform the following operation on those arrays:

- choose one of the two arrays
- pick an index $ i $ from $ 1 $ to $ n-1 $
- swap the $ i $ -th and the $ (i+1) $ -th elements of the chosen array

 Compute the minimum number of operations needed to make array $ a $ lexicographically smaller than array $ b $ .For two different arrays $ x $ and $ y $ of the same length $ n $ , we say that $ x $ is lexicographically smaller than $ y $ if in the first position where $ x $ and $ y $ differ, the array $ x $ has a smaller element than the corresponding element in $ y $ .

## 说明/提示

In the first example, the array $ a $ is already lexicographically smaller than array $ b $ , so no operations are required.

In the second example, we can swap $ 5 $ and $ 3 $ and then swap $ 2 $ and $ 4 $ , which results in $ [3, 5, 1] $ and $ [4, 2, 6] $ . Another correct way is to swap $ 3 $ and $ 1 $ and then swap $ 5 $ and $ 1 $ , which results in $ [1, 5, 3] $ and $ [2, 4, 6] $ . Yet another correct way is to swap $ 4 $ and $ 6 $ and then swap $ 2 $ and $ 6 $ , which results in $ [5, 3, 1] $ and $ [6, 2, 4] $ .

## 样例 #1

### 输入

```
3
2
3 1
4 2
3
5 3 1
2 4 6
5
7 5 9 1 3
2 4 6 10 8```

### 输出

```
0
2
3```

# 题解

## 作者：fuxuantong123 (赞：5)

# CF1573B Swaps 题解
## 思路
首先答案是一定是 $b$ 中的某一元素与 $a$ 中一个小于它的元素都移到第一位。

可以从小到大排序 $a$ 和 $b$，然后枚举 $b_i$，则 $a_{1 \sim n}$ 中移动到第一位的最小值加上 $b_i$ 移动到第一位的值即为答案，统计最小值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int x,i;
}a[100010],b[100010];
bool cmp(node x,node y){
	return x.x<y.x;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].x);
			a[i].i=i;
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i].x);
			b[i].i=i;
		}
		sort(a+1,a+n+1,cmp);
		sort(b+1,b+n+1,cmp);
		int mi=2147483647;
		int ans=2147483647;
		for(int i=1;i<=n;i++){
			mi=min(a[i].i-1,mi);
			ans=min(ans,mi+b[i].i-1);
		}
		printf("%d\n",ans);
	}
	
return 0;
}
```


---

## 作者：mahaoming (赞：3)

# CF1573B Swaps 题解

### 思路

首先答案是一定是 $a$ 中的某一元素与 $b$ 中一个大于它的元素都移到第一位。

所以直接暴力，对于两个数组直接排序。对于所有方案取最小值，由于答案是单调的，所以只需要扫描一遍 $b$ 数组即可。


### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct st{
	int a,i;
}a[100005],b[100005];
bool cmp(st x,st y){
	return x.a<y.a;
}
int t,n,s,m;
int main(){
	cin>>t;
	while(t--){
		m=0x3f3f3f3f,s=0x3f3f3f3f;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i].a;
			a[i].i=i;
		}
		for(int i=1;i<=n;i++){
			cin>>b[i].a;
			b[i].i=i;
		}
		sort(a+1,a+n+1,cmp);
		sort(b+1,b+n+1,cmp);
		for(int i=1;i<=n;i++)m=min(m,a[i].i),s=min(s,m+b[i].i);
		cout<<s-2<<endl;
	}
	return 0;
}
```


---

## 作者：_Han (赞：3)

# CF1573B
## 题意
$t$ 组数据，每组数据给出两行长度为 $n$ 的数列，一行为奇数排列 $A$ ，另一行为偶数排列 $B$ ，每次可以交换任意行相邻两数的位置，问最少通过几次操作使得 $A$ 的字典序小于 $B$ 。  

## **Sol**
要使 $A$ 的字典序小于 $B$ ，只要使 $A$ 中的第一个数小于 $B$ 中第一个数即可。  
显然能想到 $n^2$ 的朴素做法，枚举每个 $A$ 中的数并找到 $B$ 中第一个大于它的数，算出两数移动到第一位的操作次数和，求最小值即为答案。 

考虑对该这一做法进行优化。  
我们定义一个数组 $f$ , $f[i]$ 表示 $1$ 到 $i$ 移动到对应数列首位的最小操作次数。  
对于每个读入的 $B[i]$ ，它所需的操作次数即为 $i-1+f[i]$。 $i-1$ 为当前数移动到 $B$ 首位时的操作次数， $f[i]$ 为 $A$ 中比 $B[i]$ 小的数移动到首位的最小操作次数。

## **Code**
```cpp
#include<bits/stdc++.h> 
#define N 100005
using namespace std;
int t,n,a[N],b[N],f[N<<1];
inline int read()
{
	int az=0,ff=1;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') ff=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		az=az*10+(int)(ch-'0');
		ch=getchar();
	}
	return az*ff;
}
signed main()
{
	t=read();
	while (t--)
	{
		n=read();
		memset(f,0x7f7f7f7f,sizeof(f)); //f数组初始化最大值
		int minn=0x7f7f7f7f;
		for (int i=1;i<=n;i++) 
		{
			a[i]=read();
			f[a[i]]=i-1; //a[i]移动至首位需要i-1次操作
		}
		for (int i=1;i<=n;i++) b[i]=read();
		for (int i=1;i<=n<<1;i++)
		  f[i]=min(f[i],f[i-1]); //计算出1~i移动到首位的最小操作次数
		for (int i=1;i<=n;i++)
		  minn=min(minn,i-1+f[b[i]]); //按上述方法计算min值
		printf("%d\n",minn);
	}
}
```


---

## 作者：yangzd (赞：2)

# 题目大意

将 $(1,2,3,...2n)$ 的某种排列中的奇数和偶数分开，形成由奇数组成的排列 $A$ 和偶数组成的排列 $B$ ，你可以执行操作：

将某个排列中相邻的两个元素交换位置

问至少需要多少次操作，才能使 $A$ 的字典序小于 $B$ 的字典序。

# 分析

即 $A$ 的第一个元素小于 $B$ 的第一个元素。所以答案是对于 $A$ 中的某一元素，寻找 $B$ 中第一个大于它的元素，并将这两个元素都移到第一位。然后对于所有这样的方案，取最小值。

这样的查询是 $O(n^2)$ 的，我们不妨按大小顺序考虑 $A$ 中的元素： $1,3,5,7,...,2n-1$ ，对于每一个元素询问答案。由于答案是单调的，所以只需要扫描一遍 $B$ 即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	ios::sync_with_stdio(0);
	
	long long n;
	
	cin >> n;
	
	long long a[n],b[n],c[2*n];
	
	for(long long i=0; i<n; i++)
		cin >> a[i]; 
		
	for(long long i=0; i<n; i++)
		cin >> b[i]; 
		
	long long ans=n;
	 
	for(long long i=1,j=0; i<2*n; i+=2)
	{
		while(b[j]<i)
			j++;
			
		c[i]=j;
	}
	
	for(long long i=0; i<n; i++) 
		ans=min(ans,c[a[i]]+i);
		
	cout << ans << endl;
	
	return 0;	
}
```

---

## 作者：ttq012 (赞：1)

暴力求解，对于 $a$ 数组的任意元素，若要使他作为 $a_1$ ，需要找出 $b$ 数组中第一个大于 $a_i$ 的元素，记他的位置为 $j$。需要的操作次数为 $i+j-2$ ，明显超时 时间复杂度 $O(N^2)$

新建一个 $pos$ 数组用于记录第一个大于某个奇数的偶数出现在 $b$ 中的位置。最后在遍历 $a$ 数组的过程中即可求解。时间复杂度 $O(N)$

```cpp
#include <cstdio>

constexpr int power_10(int x) noexcept {
	int ans = 1;
	for (int i = 1; i <= x; i ++)
		ans = ans * 10;
	return ans;
}

const int N = 1000010;

int a[N];
int b[N];
int pos[N];

inline bool isdigit(char x) noexcept {
	return x >= '0' && x <= '9';
}

template <class _Tp>
inline _Tp min(_Tp a, _Tp b) noexcept {
	if (a < b)
		return a;
	else
		return b;
}

inline int quick_read() noexcept {
	int x = 0, f = 1;
	char ch;
	while (! isdigit (ch = getchar()))
		if (ch == '-')
			f = -f;
	x = ch - '0';
	while (isdigit (ch = getchar()))
		x = (x << 3) + (x << 1) + ch - '0';
	return x * f;
}

inline void quick_write(int x) {
	if (x == 0)
		putchar('0');
	else {
		int a[20] = {0};
		int top = 0;
		while (x) {
			int temp = x % 10;
			a[++ top] = temp;
			x /= 10;
		}
		for (int i = top; i >= 1; i --)
			putchar(a[i] + '0');
	}
}

int main() {
	int t = quick_read();
	while (t --) {
		int n = quick_read();
		int ans = (int) 1E9 + 7;
		for (int i = 1; i <= n; i ++)
			a[i] = quick_read();
		for (int i = 1; i <= n; i ++)
			b[i] = quick_read();
		for (int i = 1, j = 1; i <= 2 * n; i += 2) {
			while (b[j] < i)
				j ++;
			pos[i] = j;
		}
		for (int i = 1; i <= n; i ++)
			ans = min(ans, i + pos[a[i]] - 2);
		quick_write(ans);
		puts("");
	}
	return 0;
}

```


---

## 作者：Troubadour (赞：1)

### 题意
给你两行数，每行 $n$ 个，一行全是奇数，一行全是偶数，你可以交换任意一行的相邻两个数，问经过多少次操作之后可以使得第一行的字典序小于第二行。

 -----
### 分析
先来重提一个概念：什么叫字典序？

就是我们从第一位开始比较，第一位较大的字典序更大，第一位相同就比较第二位，以此类推比下去。

回到题目。一行全是奇数，一行全是偶数，这第一位无论如何不可能相等的。
所以我们只需要使第一行第一个数小于第二行第一个数就可以了。

我的做法是，枚举其中一行的每一位作为首位的情况，考虑另一行把哪一位移过来才能满足题目要求且移动次数最小，最后取一个最小值就行了。

咱们来看一下样例最后一组数据：
```
5
7 5 9 1 3
2 4 6 10 8
```
以枚举第二行为例：

考虑 $2$ 作为首位，第二行不用移动；第一行可选的首位有 $1$，移过来需要 $3$ 次操作，总代价为 $3$；

$4$ 作为首位，第二行移动 $1$ 次；第一行可选的首位有 $1$、$3$，移动 $1$ 需要的操作次数最少，需要 $3$ 次操作，总代价为 $4$；

$6$ 作为首位，第二行移动 $2$ 次；第一行可选的首位有 $1$、$3$、$5$，移动 $5$ 需要的操作次数最少，需要 $1$ 次操作，总代价为 $3$；

$10$ 作为首位，第二行移动 $3$ 次；第一行可选的首位有 $1$、$3$、$5$、$7$、$9$，移动 $7$ 需要的操作次数最少，需要 $0$ 次操作，总代价为 $3$；

$8$ 作为首位，第二行移动 $4$ 次；第一行可选的首位有 $1$、$3$、$5$、$7$，移动 $7$ 需要的操作次数最少，需要 $0$ 次操作，总代价为 $4$；

综上，答案为 $3$。

至于如何实现，我们处理出第一个序列上每一个数移动到第一位所需要的次数，记录下它们的**前缀最小值**，对于序列二的每一个数，直接查询即可。注意，做前缀最小值之前，所有数字对应的操作次数初始化为 inf。

#### 最后，注意多组数据。
----------

### Code：
```cpp
#include<bits/stdc++.h>
struct istream
{
	istream operator>>(int &x)
	{
		x = 0;
		char ch = getchar();
		while (!isdigit(ch))ch = getchar();
		while (isdigit(ch))x = x * 10 + ch - '0', ch = getchar();
		return *this;
	}
}cin;
namespace XMSU
{
	const int N = 2e5 + 5;
	int a, b, n, ans;
	int mi[N];
	void work()
	{
		cin >> n;
		ans = INT_MAX;
		memset(mi, 0x3f, sizeof(int)*(n * 2 + 5));
		for (int i = 1;i <= n;i++)
		{
			cin >> a;
			mi[a] = i - 1;
		}
		for (int i = 1;i <= 2 * n;i++)
		{
			mi[i] = std::min(mi[i - 1], mi[i]);
		}
		for (int i = 1;i <= n;i++)
		{
			cin >> b;
			ans = std::min(ans, i - 1 + mi[b]);
		}
		std::cout << ans << '\n';
	}
}
int main()
{
	int T;
	cin >> T;
	while (T--)XMSU::work();
	return 0;
}
```
PS：赛场上没有想到前缀最小值的做法，直接写了一棵线段树上去，达到了相同的效果……

---

## 作者：vigza (赞：0)

# CF1573b
## 解法说明
想法：对一个数列进行一系列交换操作可以使一个数从 $i$ 位置移动到 $1$ 位置，要使 $a$ 数列字典序小于 $b$ 序列，只要使 $a$ 的首元素小于 $b$ 的首元素就行了。

那么可以考虑从 $a$ 中移动一个较小的元素 $a[i]$ 到 $a$ 列首， $b$ 中移动第一个比 $a[i]$ 大的元素 $b[j]$ 到 $b$ 列首。操作花费 = $(i-1) + (j-1)$。直接 $O(n^2)$ 枚举显然不妥。

考虑 $a$ 排序后从元素最小的开始递增枚举，用一个指针 $j$ 维护 $b[j]$ 的位置，由于后继的 $a[i]$ 只会更大， $b[j]$ 有可能小于 $a[i]$，所以只有在 $j$ 或 $j$ 的后面才能找到第一个比 $a[i]$ 大的 $b[j]$。
### Code：

```cpp
void solve(){
	read1(n);
	read(a,n);
	read(b,n);
	map<int,int> id;
	if(a[1]<b[1]){//不用多说了吧
		cout<<0<<endl;
		return ;
	}
	lfor(i,1,n) id[a[i]] = i;
	sort(a.begin()+1,a.begin()+1+n);
	int ans = INF;
	int j = 1;
	lfor(i,1,n){
		int p = id[a[i]];
		while(b[j]<a[i]) j++;
		ans = min(ans,j-1+p-1);
	}
	cout<<ans<<endl;
}
```


---

## 作者：_QWQ__QWQ_ (赞：0)

## 题意：
对于给定的序列 $ a_{A1},a_{A2},…,a_{An} $、$ b_{B1},b_{B2},…,b_{Bn} $，从中取出 $ a_{Ak} $ 与 $ b_{Bk} $，使得 $ a_{Ak}<b_{Bk} $，且 $ A_k+B_k $ 的值最小。

## 思路：
可以快速推断出：对于 $ a_{Ak} $，找到所有大于它的 $ b_{Bk} $，再找到这些 $ b_{Bk} $ 中 $ B_k $ 最小的那个。
例如本题输入样例3，若取 $ a $ 数组的 $ 5 $，则 $ b $ 数组中 $ 6 $，$ 10 $，$ 8 $ 三个元素皆符合题意，而这三个元素中位置最小的是 $ 6 $，故取 $ 6 $。

由于给定的序列为奇偶顺序排列，故我们可以将 $ a $ 序列处理成 `1=1,2=3,3=5,…,n=2*n-1` 以及 `1=2,2=4,…,n=2*n` 。
而数组的读入则为：下标存值，元素内容存位置。
则：对于任意的 $ a_k $，我们只需要找到 $ b_k $ 到 $ b_n $ 中位置最小的那个即可。而要实现这一目的，只需要倒序遍历处理一遍 $ b $ 数组即可。

## 附AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
const long long maxm=1e18+5;
long long t,ans,n,a[maxn],b[maxn],x;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=maxm;
		for(int i=1;i<=n;i++){
			cin>>x;
			a[(x+1)/2]=i;
		}
		for(int i=1;i<=n;i++){
			cin>>x;
			b[x/2]=i;
		}
		for(int i=n-1;i>=1;i--){
			b[i]=min(b[i],b[i+1]);
		}
		for(int i=1;i<=n;i++){
			ans=min(ans,a[i]+b[i]-2);
		}
		if(ans!=maxm){
			cout<<ans<<"\n";
		}
		else{
        		cout<<0<<"\n";
   	  	}
	}
	return 0;
}

```

---

## 作者：cannotdp (赞：0)

#### 题意见原题目，不再多说

### 前置芝士：字典序

 _在数学中，字典或词典顺序（也称为词汇顺序，字典顺序，字母顺序或词典顺序）是基于字母顺序排列的单词按字母顺序排列的方法。 这种泛化主要在于定义有序完全有序集合（通常称为字母表）的元素的序列（通常称为计算机科学中的单词）的总顺序。  ——百度_
 
 那么对于本题来讲，使序列 $a$ 的字典序小于序列 $b$，就是让序列 $b$ 的第一个数字大于序列 $a$ 的第一个数字。
 
 ### 思路
 
 由于 $n \leq 10^5$，所以我们可以开一个桶数组 $f$。当 $i$ 为奇数时，$f_i$ 表示在 $a_i$ 这个点到第一个位置的距离，即 $f_{a_i}=i-1$。随后我们进行一个简单的动态规划即可结束此题。
 
 ### 代码实现
 
 ```
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N=1e5+10;
int t;
int n;
int a[N],b[N];
int f[N<<1];
int ans;
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		memset(f,0x3f3f3f3f,sizeof(f));//注意这里开0x7fffffff会爆掉 
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),f[a[i]]=i-1;		
		for(int i=1;i<=n;i++) scanf("%d",&b[i]);	
		for(int i=1;i<=n*2;i++) f[i]=min(f[i],f[i-1]);//注意i<=n*2 
		ans=0x7fffffff;
		for(int i=1;i<=n;i++) ans=min(ans,f[b[i]]+i-1);
		printf("%d\n",ans);
	} 
	return 0;
} 
```


---

## 作者：Dehydration (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1573B)

先看题面：

首先有$s$ 组数据。

对于每一组数据：

给出两行长度为 $t$ 的数列，

一行为奇数排列 $W_1$ ，另一行为偶数排列 $W_2$，

操作：每次可以交换 $W_1$ 或 $W_2$ 中任意相邻两数的位置。

问题：问最少通过几次操作使得 $W_1$ 的字典序小于 $W_2$。

思路看代码。

#### CODE:
```cpp
#include <bits/stdc++.h>//万能头
using namespace std;
const int maxn=100010,inf=0x3f3f3f3f;//初始化
int a[maxn],b[maxn],f[maxn<<1];
int main(){
	int n,t;scanf("%d",&t);
	while (t--){
		scanf("%d",&n);memset(f,0x3f,sizeof f);
		for (int i=1;i<=n;++i) scanf("%d",&a[i]),f[a[i]]=i-1;
		for (int i=1;i<=n;++i) scanf("%d",&b[i]);
		for (int i=1;i<=(n<<1);++i) f[i]=min(f[i],f[i-1]);
		int ans=inf;
		for (int i=1;i<=n;++i) ans=min(ans,f[b[i]]+i-1);
		printf("%d\n",ans);
	}//三次for循环加判断
	return 0;
}
```



---

