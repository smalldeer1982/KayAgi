# Consecutive Sum

## 题目描述

You are given an array $ a $ with $ n $ integers. You can perform the following operation at most $ k $ times:

- Choose two indices $ i $ and $ j $ , in which $ i \,\bmod\, k = j \,\bmod\, k $ ( $ 1 \le i < j \le n $ ).
- Swap $ a_i $ and $ a_j $ .

After performing all operations, you have to select $ k $ consecutive elements, and the sum of the $ k $ elements becomes your score. Find the maximum score you can get.

Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ .

## 说明/提示

In the first test case, we can get a score of $ 11 $ if we select $ a_1, a_2 $ without performing any operations.

In the third test case, we can get a score of $ 15 $ if we first swap $ a_1 $ with $ a_4 $ and then select $ a_3, a_4, a_5 $ .

## 样例 #1

### 输入

```
5
3 2
5 6 0
1 1
7
5 3
7 0 4 0 4
4 2
2 7 3 4
3 3
1000000000 1000000000 999999997```

### 输出

```
11
7
15
10
2999999997```

# 题解

## 作者：yitian_ (赞：9)

## 题目分析

题目要求我们对一个长度为 $ n $ 的数组进行一系列特定的交换操作，每次交换操作允许选择两个索引 $ i $ 和 $ j $ 进行交换，但是要求 $i\bmod k = j \bmod k$，其中 $ k $ 是给定的一个正整数。在完成所有操作后，需要从数组中选择一个长度为 $ k $ 的连续子数组，使其元素之和尽可能大。

简而言之，我们需要设计一种策略来选择交换操作，以及在完成所有操作后，找到数组中一个长度为 $ k $ 的连续子数组，使其元素之和最大。

## 思路

我们可以发现，$ i \,\bmod\, k = j \,\bmod\, k $ 其实就是表示 $a_i$ 和 $a_j$ 的距离为 $k$。那么我们可以通过以下步骤完成题目：

1. **遍历和计算**：嵌套循环遍历数组，并计算连续子数组的和。外层循环控制遍历每个连续子数组的起始位置，内层循环则从当前起始位置开始，以步长 $y$ 遍历数组。在内层循环中，找到每个连续子数组中的最大值，并累加到 $ans$ 中。

2. **输出**：最后，输出 $ans$，即连续子数组和的总和。

总体而言，这个思路通过计算每个测试用例中，连续子数组中最大的元素的和，找到每个连续子数组的最大值。

## C++ 代码实现

```c
#include<bits/stdc++.h> // 包含标准库头文件
using namespace std;

int t,maxn=-1; // t为测试用例数量，maxn为最大值初始值设为-1

void LG(int x,int y) // 定义函数LG，参数为数组长度x和连续子数组长度y
{
	long long ans=0; // ans为连续子数组和的总和
    int Sum[105]={0}; // 定义一个长度为105的数组Sum，用于存储输入的数组元素
    for(int i=1;i<=x;i++)  // 循环读取数组元素
    {
    	cin >> Sum[i]; // 输入数组元素
    }
    for(int i=1;i<=y;i++) // 外层循环控制连续子数组的起始位置
	{
        for(int j=i;j<=x;j+=y) // 内层循环计算当前连续子数组的和
		{
            if(maxn<Sum[j]) maxn=Sum[j]; // 更新当前连续子数组中的最大值
        }
        ans+=maxn; // 将当前连续子数组的最大值累加到总和中
        maxn=-1; // 重置最大值为-1，为下一个连续子数组的计算做准备
    }
    cout << ans << endl; // 输出当前测试用例的连续子数组和的总和
}

int main()
{
    cin >> t; // 输入测试用例数量
    for(int i=1;i<=t;i++) // 循环处理每个测试用例
	{
		int n,k;
		cin >> n >> k; // 输入数组长度n和连续子数组长度k
        LG(n,k); // 调用函数LG，计算当前测试用例的结果
    }
    return 0; // 程序正常结束
}
```

---

## 作者：QingDeng_Star (赞：3)

## 大致题意
给定一个长度为 $n$ 的数组 $a$ ，你可以进行最多 $k$ 次下面的操作。

 选择两个下标 $i$ 和 $j$ , 满足 $i$ $\bmod$ $k$ $=$ $j$  $\bmod$ $k$ $($ $1$ $\le$ $i$ $<$ $j$ $\le$ $n$ $)$.

交换 $a_i$ 和 $a_j$ .

在进行完你的操作之后（不必用完 $k$ 次操作的机会，你需要在数组中选择一段长度为 $k$ 的区间，此区间的各个元素的和即为你的分数，请求出你能得到的最大分数。

## 思路
一眼贪心好题。可以看出当下标膜 $k$ 同余时，就可以交换，简单证明后可得出，我们一定可以把膜 $k$ 同余的最大数放到长度为 $k$ 的区间里，简单模拟即可。
```c
#include <bits/stdc++.h>
using namespace std;
long long a[105],b[105];
int main(){
	int t;
	cin>>t;
	while(t--) 
	{
		int n,k;
		cin>>n>>k;
		memset(a,0,sizeof a);//初始化 
		for(int i=1;i<=n;i++) 
		{
			cin>>b[i];
			a[i%k]=max(a[i%k],b[i]);
		}
		long long ans=0;//保险起见开 long long 
		for(int i=0;i<k;i++) 
			ans+=a[i];
		cout<<ans<<endl;
	}
	return 0;//完结散花
}
```

---

## 作者：0zhouyq (赞：3)

## CF1733A 题解

[传送门](https://www.luogu.com.cn/problem/CF1733A)

### 思路：

贪心。

第 $i$ 次操作 ($1\leq i\leq k$) 可以把 $a$ 数组中下标模 $k$ 余 $i$ 的最大值转移到 $a$ 数组下标为 $i$ 的位置，此时最大的操作次数就为 $k$，满足题意。此时，选取的长度为 $k$ 的连续元素就应该是 $a_1$ 到 $a_n$，直接枚举累加输出就好了。贪心的正确性可以证明。详情见代码。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int maxn[101];
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int n,k;
		scanf("%lld %lld",&n,&k);
		for(int i=0;i<=100;i++) maxn[i]=-0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=n;i++){
			int x;
			scanf("%lld",&x);
			int p=i%k;
			maxn[p]=max(maxn[p],x);
		}
		int ans=0;
		for(int i=0;i<k;i++){
			ans+=maxn[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Charles_with_wkc (赞：2)

# 思路：
给定一个长度为 $n$ 的数组 $a$，你可以进行最多 $k$ 次下面的操作。选择两个下标使得 $i \bmod k = j \bmod k ( 1 \le i,j \le n)$ 我们就交换 $a_i$ 和 $a_j$。在进行完你的操作之后，你需要在数组中选择一段长度为 $k$ 的区间，此区间的各个元素的和即为你的分数，请求出你能得到的最大分数。
# 核心代码：
```cpp
for(int i=1;i<=n;i++){
     cin>>b[i];
     a[i%k]=max(a[i%k],b[i]);//计算
}
long long ans=0;
for(int i=0;i<k;i++){
     ans+=a[i];//累和求答案
}		
```

---

## 作者：_Tatsu_ (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF1733A)
#### 2024-7-9 update: 修改代码缩进
###### ~~这是本蒟蒻第一次写题解，请多多包涵！~~
## 题目简述
给定一个长度为 $n$ 的数组 $a$，你可以进行最多 $k$ 次下面的操作：
 
- 选择两个索引 $i$ 和 $j$，满足 $i \bmod k = j \bmod k(1≤ i < j ≤n)$。
 
- 交换 $a_i$ 和 $a_j$。
 
你需要在数组中选择一段长度为 $k$ 的区间，此区间的各个元素的和即为你的分数，请求出你能得到的最大分数。

## 题目解答:
只有两个数的位置的编号余数相同，才能交换两个数。所以，就一定能把所有位置余数相同的数中的最大数放到一个区间长度为 $k$ 的区间中。
## AC code:
``````````````````````cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,k,a[100005],s[100005],sum=0; 
int main()
{
	cin>>t;
	while(t--)
    {
		cin>>n>>k;
		sum=0;
		memset(s,0,sizeof s);
       	for(int i=1;i<=n;i++)
        {
    	  	cin>>a[i];
            s[i%k]>a[i]?s[i%k]=s[i%k]:s[i%k]=a[i];
        }
    	for(int i=0;i<k;i++)
        {
    		sum+=s[i];
        }
    	cout<<sum<<endl;
	}
	return 0;
}
````````````````````````````````

---

## 作者：Pump_kin (赞：1)

我们发现这道题目是让我们在 $k$ 次操作内构造一个区间，使得这个区间和最大。

我们先说一下构造方法，就是取序列中序列编号对于 $m$ 取余的值一样的最大数，然后求和。

现在，我们来证明一下这个方法的正确性。

首先，我们可以说明，如果 $i$ 和 $j$ 对于 $p$ 同余，那么这两个数是不可能同时出现在这个区间中的。

这是由于整个区间的长度是 $k$，所以不会出现。

然后，我们就可以说明，这样取一定是最大的了，因为对于每一个数，都是最大的，所以总和自然是最大的了。

最后，我们来证明一定存在一种方案使得可以凑出这样一个长度为 $k$ 的区间。

我们只需要这样操作：

> 如果这个数是整个数列的这种编号模 $p$ 的最大的数，那么什么也不做。
>
> 否则，只需要让这个数和整个数列的这种编号模 $p$ 的最大的数交换一下，就可以了。

至此，我们就证明了这种方案的正确性。

代码：（竟然跑到了最优解 Rank $1$）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=200;
ll ans;
int t,n,k;
int x,maxx[N];
int read(){
	int ans=0,f=1;
	char op=getchar();
	while(op<'0'||op>'9'){
		if(op=='-')f=-1;
		op=getchar();
	}
	while(op<='9'&&op>='0'){
		ans=(ans<<3)+(ans<<1)+op-'0';
		op=getchar();
	}
	return ans*f;
}
int main(){
	t=read();
	while(t--){
		n=read(),k=read();
		for(int i=0;i<k;i++)maxx[i]=0;ans=0;
		for(int i=1;i<=n;i++)x=read(),maxx[i%k]=max(maxx[i%k],x);
		for(int i=0;i<k;i++)ans+=maxx[i];
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：sgl654321 (赞：1)

### 题目大意
- 给定一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，你可以进行最多 $k$ 次操作。
- 每一次操作，你可以选定两个数 $i,j$，满足 $i\bmod k=j\bmod k$，此时你可以交换 $a_i$ 与 $a_j$。
- 结束操作后，你可以选定一个长度为 $k$ 的区间 $[x,x+k-1]$，并求出 $\sum_{i=x}^{x+k-1}a_i$ 的值。询问所有的区间中，这个最大值是多少。

### 解题思路
由于我们最多可以进行 $k$ 次操作，所有考虑贪心。我们把序列中下标模 $k$ 同余的数放入一个集合内。令 $b_i$ 表示下标模 $k$ 余 $i$ 的集合内的最大值。

每一次操作，我们把一个集合中最大的数 $b_i$ 放到下标为 $i$ 的位置中去。这样我们就可以得到一个最大的子串 $[1,k]$ 了。

因此我们只需要统计每一个集合中的最大值之和就可以了。具体见代码。

### 参考代码
注意到本题有多组数据，因此务必注意清零。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,a[100010],b[100010],ans; 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		ans=0;
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i%k]=max(b[i%k],a[i]);
		}
		for(int i=0;i<k;i++)
			ans+=b[i];
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：lostxxx (赞：0)

# 题目分析

我们通过样例发现，每一个数能够产生交换的位置只有 $i$ ，$i+k$ ，$i+2k$ ，$\dots$ ，$i+nk$ 。所以我们可以开一个二维数组 $a_{i,j}$ 表示分别表示第 $i \bmod k$ ，$\frac{i}{k}$ 个。然后对数组的第二维进行从大到小排序，取最大的那一个。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t;
ll n,k;
ll a[110][110];
bool cmp(ll a,ll b){
	return a>b;
}
int main(){
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));
		cin>>n>>k;
		for (int i=1;i<=n;i++){
			cin>>a[i%k][i/k];
		}
		for (int i=0;i<k;i++)
			sort(a[i],a[i]+n+1,cmp);
		ll ans=0;
		for (int i=0;i<k;i++)
			ans+=a[i][0];
		cout<<ans<<endl; 
	}
}
```

---

## 作者：NEKO_Daze (赞：0)

洛谷题目传送门：[CF1733A](https://www.luogu.com.cn/problem/CF1733A)   | |  CF原题传送门：[1733A](https://codeforces.com/contest/1977/problem/A)

#### 简要题意

给出一个长度为 $n$ 的数组，每次可以选取两个数 $a_i,a_j$，若 $i\bmod k=j\bmod k$ 则可进行交换。求出进行任意次操作后可得的最大子段和。
#### 思路

显然，对于第 $i$ 个元素，只能移动到第 $i+xk$ 个元素的位置，即 $a_i$ 只能和 $a_{i+xk}$ 交换。对于每个索引 $i$（$k + 1 \le i \le n$），$a_1$ 至 $a_k$ 中正好有一个元素可以与 $a_i$ 互换。如果 $a_i$ 大于该元素，则交换它们。此过程最多执行 $n - k$ 次操作。执行操作后，选择 $a_1$ 到 $a_k$。这就是我们能得到的最大分数。

```cpp
#import<bits/stdc++.h>
using namespace std;
long long k, n, s, t, x, a[100005];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	for(cin >> t; t--;)
	{
		cin >> n >> k;
		for(int i = 1; i <= n; i++)
		{
			cin >> x;
			a[i % k] = max(a[i % k], x);
		}
		s = 0;
		for(int i = 0; i < k; i++)s += a[i];
		cout << s << endl;
		fill(a, a + k, 0);
	}
    return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题目大意

对于 $t$ 组数据中，每一组长度为 $n$ 的序列中，可以最多实现 $k$ 次交换。对于每一次交换，有下面两种：

- 选择两个索引 $i$ 和 $j$，满足 $i$ 除以 $k$ 的余数等于 $j$ 除以 $k$ 的余数，特别的，必须满足 $1\le i<j \le n$。
- 交换 $a_i$ 和 $a_j$。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1733A)

贪心算法。

对于第 $i$ 次操作，是把数组中下标除以 $k$ 余 $i$ 的最大值转移至下标 $i$ 的位置，又因为只有两个数除以 $k$ 的余数要相同才可以交换位置，所以，我们就不妨把所有下标除以 $k$ 的余数的最大数放在一个数组中储存，然后相加求出和。这时就可以满足题意，操作次数为 $k$ 次，正确性显然。

参考代码：

```
#include <bits/stdc++.h>
#define int long long
#define rep(i,x,y) for (int i=x;i<=y;i++)
using namespace std;
int t,f[10001],a[10001],n,k;
inline int read () {int s=0,w=0;char c=getchar ();while (!isdigit (c)){w|=(c=='-');c=getchar ();}while (isdigit (c)) {s=(s<<1)+(s<<3)+(c^48);c=getchar ();}return w?-s:s;}
inline void write (int x) {if (x<0) putchar ('-'),x=-x;if (x>9) write (x/10);putchar (x%10|48);}
signed main() {
    t=read ();
    while (t--) {
    	memset (f,0,sizeof (f));
    	n=read (),k=read ();
    	rep (i,1,n) {
    		a[i]=read ();
    		f[i%k]=max (f[i%k],a[i]);
		}
		int ans=0;
		rep (i,0,k-1) ans+=f[i];
		printf ("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：qusia_MC (赞：0)

贪心。

## 题意简述
把 $n$ 个数分成 $k$ 组，分组的规则是：对于任意 $1\le i\le n$，则 $a_i$ 的组别为 $i\bmod k$。现在在每一组里面找一个最大值，（用 $max$ 数组表示）求 $\sum^{n}_{i=1}max_i$。
## 思路
看题意简述就能看出来吧？我要证明一下。

- 为什么不能选别的区间呢？

  区间 $[m,m+k]$ 之中的 $a_m\sim a_{m+k}$ 中必有 $i \bmod k$ 的所有值（$0\sim k-1$），这样的话，无论怎么选，都是从每一组里找一个最大值。
  
- 为什么是最大值呢？

  - 第一，是题目要求最大。
  
  - 第二，我们可以对于任意的 $m$ 满足：
  
     - $1\le m\le n$
     
     - $i\equiv m\pmod k$
  
   这样的话，我们可以直接交换两数。我们可以找到一个最大值然后和 $m\bmod k$ 交换。这样就可以实现最优。
   
## code
加了一点优化，题解复杂去最优。其他大佬都是 $O(n+k)$ 我是 $O(\max(n,k))$。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long//一定开long long
signed main()
{
	int t,n,k,l,sum=0,maxx[111];
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=0;i<min(n,k);i++)
	    {
	    	scanf("%d",&l);//快速输入
	    	sum+=l;
	    	maxx[i]=l;//提前累计
		}
		for(int i=k;i<n;i++)
		{
			scanf("%d",&l);
			if(l>maxx[i%k])//找到了更大的
			{
				sum=sum-maxx[i%k]+l;//答案更新
				maxx[i%k]=l;//最大值更新
			}
		}
		cout<<sum<<"\n";//输出
		sum=0;//别忘了归零
	}
	return 0;
}
```

---

## 作者：zk_y (赞：0)

[题目转送门](https://www.luogu.com.cn/problem/CF1733A)

# 题目简述

给定一个长度为 $ n $ 的数组 $ a $，你可以进行最多 $ k $ 次下面的操作

- 选择两个索引 $ i $ 和 $ j $ , 满足 $ i \,\bmod\, k = j \,\bmod\, k $ ( $ 1 \le i < j \le n $ ).
- 交换 $ a_i $ 和 $ a_j $ .

在进行完你的操作之后（不必用完 $ k $ 次操作的机会），你需要在数组中选择一段长度为 $ k $ 的区间，此区间的各个元素的和即为你的分数，请求出你能得到的最大分数。

# 题目解答

我们发现只有两个数的位置的编号同余，才能交换两个数的位置。所以，我们就一定可以能把所有位置同余的数中最大数放到一个区间长度为 $k$ 的区间中。这个是很容易证明的，大家可以自行尝试一下。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200;
#define ll long long
ll num,tot[N],t,n,k;
ll ans;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		ans=0;//注意答案需要每次清零 
		memset(tot,0,sizeof(tot));//数组也需要清零（注意清零） 
		for(int i=1;i<=n;i++){
			scanf("%d",&num);
			tot[i%k]=max(tot[i%k],num);
		}
		for(int i=0;i<k;i++){
			ans+=tot[i];
		}
		printf("%lld\n",ans);//输出答案 
	}
	return 0;
}
```

---

## 作者：RP_INT_MAX (赞：0)

## $\tt Solution$

贪心典题。

下标模 $k$ 同余，这是一个重要性质。

令 $\text{mx}_i$ 表示下标模 $k$ 余 $i$ 的所有元素的最大值。将 $\text{mx}$ 数组求和即可。

正确性显然。

## $\tt Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,k;
ll a[110],mx[110];
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--) {
		memset(mx,0,sizeof mx);
		cin>>n>>k;
		for(int i=1;i<=n;++i) {
			cin>>a[i];
			mx[i%k]=max(mx[i%k],a[i]);
		}
		long long ans=0;
		for(int i=0;i<k;++i) ans+=mx[i];
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：zfx_VeXl6 (赞：0)

只需求出 $\sum\limits_{j=0}^{k-1}\max(a_i|1\le i\le n,i\bmod k=j)$ 即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int t, n, k;
ll a[101], mx[101], ans;
int main() {
	cin >> t;
	while (t--) {
		memset(mx, 0, sizeof(mx));
		ans = 0;
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			mx[i % k] = max(mx[i % k], a[i]);
		}
		for (int i = 0; i < k; i++)
			ans += mx[i];
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：jasonshen_ (赞：0)

## 题意

给定一个长度为 $ n $ 的数组 $ a $，你可以进行最多 $ k $ 次下面的操作。

- 选择两个索引 $ i $ 和 $ j $ , 满足 $ i \,\bmod\, k = j \,\bmod\, k $ ( $ 1 \le i < j \le n $ )。
- 交换 $ a_i $ 和 $ a_j $ 。

在进行完你的操作之后（不必用完 $ k $ 次操作的机会），你需要在数组中选择一段长度为 $ k $ 的区间，此区间的各个元素的和即为你的分数，请求出你能得到的最大分数。

## 分析
一道很简单的贪心，可证明。因为上面几篇大佬的题解都有详细论述，这里就不再赘述，可看代码。
```cpp

#include <bits/stdc++.h>
using namespace std;
int main() {
	int t, n, k, a;
	cin>>t;
	while (t--) {
		cin>>n>>k;
		vector<int> v(k);
		for (int i=0;i<n;++i) cin>>a, v[i%k]=max(v[i%k], a);
		long long s=0;
		for (auto x: v) s+=x;
		cout<<s<<endl;
	}
	return 0;
}

```

---

