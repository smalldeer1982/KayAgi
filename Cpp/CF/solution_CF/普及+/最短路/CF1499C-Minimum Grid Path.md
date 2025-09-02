# Minimum Grid Path

## 题目描述

Let's say you are standing on the $ XY $ -plane at point $ (0, 0) $ and you want to reach point $ (n, n) $ .

You can move only in two directions:

- to the right, i. e. horizontally and in the direction that increase your $ x $ coordinate,
- or up, i. e. vertically and in the direction that increase your $ y $ coordinate.

In other words, your path will have the following structure:

- initially, you choose to go to the right or up;
- then you go some positive integer distance in the chosen direction (distances can be chosen independently);
- after that you change your direction (from right to up, or from up to right) and repeat the process.

You don't like to change your direction too much, so you will make no more than $ n - 1 $ direction changes.

As a result, your path will be a polygonal chain from $ (0, 0) $ to $ (n, n) $ , consisting of at most $ n $ line segments where each segment has positive integer length and vertical and horizontal segments alternate.

Not all paths are equal. You have $ n $ integers $ c_1, c_2, \dots, c_n $ where $ c_i $ is the cost of the $ i $ -th segment.

Using these costs we can define the cost of the path as the sum of lengths of the segments of this path multiplied by their cost, i. e. if the path consists of $ k $ segments ( $ k \le n $ ), then the cost of the path is equal to $ \sum\limits_{i=1}^{k}{c_i \cdot length_i} $ (segments are numbered from $ 1 $ to $ k $ in the order they are in the path).

Find the path of the minimum cost and print its cost.

## 说明/提示

In the first test case, to reach $ (2, 2) $ you need to make at least one turn, so your path will consist of exactly $ 2 $ segments: one horizontal of length $ 2 $ and one vertical of length $ 2 $ . The cost of the path will be equal to $ 2 \cdot c_1 + 2 \cdot c_2 = 26 + 176 = 202 $ .

In the second test case, one of the optimal paths consists of $ 3 $ segments: the first segment of length $ 1 $ , the second segment of length $ 3 $ and the third segment of length $ 2 $ .

The cost of the path is $ 1 \cdot 2 + 3 \cdot 3 + 2 \cdot 1 = 13 $ .

In the third test case, one of the optimal paths consists of $ 4 $ segments: the first segment of length $ 1 $ , the second one — $ 1 $ , the third one — $ 4 $ , the fourth one — $ 4 $ . The cost of the path is $ 1 \cdot 4 + 1 \cdot 3 + 4 \cdot 2 + 4 \cdot 1 = 19 $ .

## 样例 #1

### 输入

```
3
2
13 88
3
2 3 1
5
4 3 2 1 4```

### 输出

```
202
13
19```

# 题解

## 作者：snnu_lgw (赞：3)

### Description

在一个 $n*n$ 的矩阵中，你从 $(0,0)$ 走到 $(n,n)$，每次只能向上走或者向右走，且每次能走的距离至少为 $1$ （肯定也不能越界），然后走完这一次之后必须要更换方向（由向上到向右，或者相反），且规定换方向的次数至多为 $n-1$，即最多有 $n$ 段路，最少有 $2$ 段路 。题目给定每一段 segment 都有一个权值 $c[i]$，代表走这段路的花费，现在求 $min: \sum_{i=1}^k c[i]*length[i]$，其中 $k$ 为 segment 的段数，$length[i]$ 为这段路的长度。 

### Solution

原本以为会是一个 $dp$ 的做法，想着想着发现是一个贪心。

读题可知，一开始向上或者向右没有影响，所以就假设一开始先向右走。

然后取法就有了一个比较常见的贪心做法。设向右走里面有 $cnt_a$ 个权值，最小值设为 $a_{min}$，这么多个权值的前缀和为 $sum_a$。同理，向上走有 $cnt_b$ 个权值，最小值设为 $b_{min}$，前缀和记为 $sum_b$。贪心策略为：除了 $a$ 和 $b$ 中的最小值，其余的线段长度都取 $1$。即可得到当前取法情况下的总花费：
$$
ans=a_{min}*(n-cnt_a+1)+sum_a-a_{min}+b_{min}*(n-cnt_b+1)+sum_b-b_{min}
$$
显然可以看出，处理 $a$ 和 $b$ 的情况是完全一样的。不过一定要注意：向上和向右的线段数目要么相同，要么相差 $1$，不可能相差大于等于 $2$ 。

同时注意看数据范围，一定记得开 long long 

所以接下来就可以枚举每一个 segment 的 cost 啦，见代码。

### Code

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll c[100000+10]; // cost

int main()
{
	int t; cin>>t;
	while(t--)
	{
		int n; cin>>n;
		for(int i=1;i<=n;i++)
			scanf("%lld",&c[i]);
		
		ll a_sum = c[1], b_sum = c[2]; //前缀和 
		ll a_min = c[1], b_min = c[2]; //当前最小值 

		ll ans = a_min*n+b_min*n;
		for(int i=2;i<=n-1;i++)
		{//在枚举的过程中直接修改ans
			if(i%2==0){
				a_sum += c[i+1];
				a_min = min(a_min,c[i+1]);
//				b_sum += c[i]; //注意不要重复累加前缀和
				b_min = min(b_min,c[i]);
				ans = min(ans,a_min*(n-(i+1)/2)+a_sum-a_min+b_min*(n-i/2+1)+b_sum-b_min); 
			}
			else {
//				a_sum += c[i];
				a_min = min(a_min,c[i]);
				b_sum += c[i+1];
				b_min = min(b_min,c[i+1]);
				ans = min(ans,a_min*(n-i/2)+a_sum-a_min+b_min*(n-(i+1)/2+1)+b_sum-b_min);
			}			
		}
		cout<<ans<<endl;
	} 
	return 0;
}

```



---

## 作者：moqizhu2005 (赞：2)

### CF 1499C Minimum Grid Path

根据题意，可以发现位置位于奇数位置和偶数位置的数一定分别是向上或者是向右的，把所有位于奇数位置和偶数位置的数字取出来。

取法考虑贪心，向上或向右所有数其中最小的数尽可能取越大的距离，即除了最小的数之外其他数距离均取$1$。

由于向上向右总距离相等，所以不需要分开讨论。

接下来通过枚举使用的$n$，即总共分割的线段数。

设前$i$的奇数位置中最大值为$g_i$，偶数位置中最大值为$f_i$，奇数位置中所有数字的和为$d_i$，偶数位置中所有数字的和为$s_i$，共有$x$个偶数，$y$个奇数，那么前$i$的总花费为：

$$ans_i=f_i*(n-x+1)+(s_i-f_i)+g_i*(n-y+1)+(d_i-g_i)$$

由于每次查询最大值的区间都是$[i,n]$，所以可以$O(n)$预处理最大值和前缀和。

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll maxn=100005,inf=(1ll<<60);
ll t,n,c[maxn],f[maxn],g[maxn],s[maxn],d[maxn];
int main(){
    scanf("%lld",&t);
    while(t--){
    	scanf("%lld",&n);
    	f[0]=g[0]=inf;
    	for(int i=1;i<=n;i++){
    		scanf("%lld",&c[i]);
    		f[i]=g[i]=inf;
		}
		for(int i=1;i<=n;i++){
			if(i%2==0){
				s[i]=s[i-1]+c[i];
				d[i]=d[i-1];
				f[i]=min(f[i-1],c[i]);
				g[i]=g[i-1];//注意不更新的数据也要继承
			}
			else{
				d[i]=d[i-1]+c[i];
				s[i]=s[i-1];
				g[i]=min(g[i-1],c[i]);
				f[i]=f[i-1];
			}
		}
		ll ans=inf;
    	for(int i=2;i<=n;i++){
    		ll x=i/2,y=(i+1)/2;
    		ans=min(ans,f[i]*(n-x+1)+s[i]-f[i]+g[i]*(n-y+1)+d[i]-g[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：fanfansann (赞：1)

 

**Problem**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210410213902190.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)


**Solution**

显然第一印象就是我们对于 $c_i$ 小的就多走一点，$c_i$ 大的就少走一点，发现少走一点，也就**至少走一步**，如果我们当前的 $c_i$ 是最小的，那么显然**直接走到头**也就是走完这个方向的所有步数是最优的。有了这个印象以后，我们分析题意，发现每次选择方向必须是不同的方向，所以我们走的时候必须上，右，上，右...这样交替地行走，所以我们直接**奇偶交替行走**，分别选择不同的 $c_i$ ，因为往右走和往上走都是一样的，都是走 $n$ 步，一共走 $2\times n$ 步，所以向上向右，谁奇谁偶是无所谓的，我们$O(n)$贪心地走一遍即可。

**Code**


```cpp
// Problem: C. Minimum Grid Path
// Contest: Codeforces - Educational Codeforces Round 106 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1499/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;
#define int long long
const int N = 500007, INF = 2e9;

int t, n, m;
int a[N];

void solve()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; ++ i) 
		scanf("%lld", &a[i]);
	
	int even = INF, odd = INF, cnt_even = 0, cnt_odd = 0;
	int ans_even = 0, ans_odd = 0;
	int ans = (a[1] + a[2]) * n;
	for(int i = 1; i <= n; ++ i) {
		if(i & 1) {
			ans_odd += a[i];
			cnt_odd ++ ;
			odd = min(odd, a[i]);
		}
		else {
			ans_even += a[i];
			cnt_even ++ ;
			even = min(even, a[i]);
		}
		ans = min(ans, ans_even + even * (n - cnt_even) + ans_odd + odd * (n - cnt_odd));
	}
	printf("%lld\n", ans);
}

signed main()
{
	scanf("%lld", &t);
	while(t -- ) {
		solve();
	}
	return 0;
}
```

---

## 作者：Zzzzzzzm (赞：1)

## 题目难度
~~黄色~~的思维题，还是需要思考比较长的时间

## 数据分析
 $n\times n$ 的图中，$t$ 组数据，所以只有 $O(n)$ 或者 $O(n\log_2{n})$ 才能过。

## 题目分析

首先要明确分为**横着的与竖着的，并且只能转向才能到下一个数。**
如果设第一个为横着走，那么奇数个也是横着走，偶数个都是竖着走的。
那么记录下当前横纵的 $minn$ 与 $minm$ ，表示横着的到当前的最小值与纵着的当前最小值。让剩下的每一个都走一个，$minn$ 走 $n-i+1$ 个。

什么意思呢？我们用图分析样例第三组：

$i=1$ ，$j=1$ ![](https://cdn.luogu.com.cn/upload/image_hosting/b52lsv04.png)

$i=2$ ，$j=1$![](https://cdn.luogu.com.cn/upload/image_hosting/u4bakqk2.png)

$i=2$ ，$j=2$![](https://cdn.luogu.com.cn/upload/image_hosting/mpvi9vzw.png)

$i=3$ ，$j=2$
![](https://cdn.luogu.com.cn/upload/image_hosting/dgy6agu3.png)

看到这里，相信大家都明白了，所以我们直接上代码了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int n;
long long b[100005];
long long a[100005];
 
template<typename T>								//快读快写 
inline void read(T&x){
	x=0; char q; bool f=1;
	while(!isdigit(q = getchar()))	if(q == '-')	f = 0;
	while(isdigit(q)){
		x = (x<<1)+(x<<3)+(q^48);
		q = getchar();
	}
	x = f?x:-x;
}
 
template<typename T>
inline void write(T x){
	if(x<0){
		putchar('-');
		x = -x;
	}
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
 
int main(){
	read(t);
	while(t--){										//t组数据 
		read(n);
		for(register int i = 1; i <= n; ++i){		//输入a[]与b[]，即横着的和竖着的。 
			if(i%2)	read(a[i/2+1]);
			else	read(b[i/2]);
		}
		long long mina = a[1], minb = b[1], suma = a[1] * n, sumb = b[1] * n, ans = suma+sumb;	//初始化，为i=1，j=1时。 
		for(register int i = 3; i <= n; ++i){
			if(i % 2 == 1){							//如果该修改横了 
				int j = i/2+1;
				if(a[j] < mina){					//如果当前小于最小值 
					suma -= mina*(n-j+1);			//把(n-j+1)个mina改为minn 
					suma += a[j] * (n-j+1);
					mina = a[j];
				}
				else{
					suma -= mina;					//否则修改一个 
					suma += a[j];
				}
				ans = min(ans, suma+sumb);
			}
			else{
				int j = i/2;						//与上同理 
				if(b[j] < minb){
					sumb -= minb*(n-j+1);
					sumb += b[j] * (n-j+1);
					minb = b[j];
				}
				else{
					sumb -= minb;
					sumb += b[j];
				}
				ans = min(ans, suma+sumb);
			}
		}
		write(ans);									//输出 
		putchar('\n');
	}
	return 0;
}
```
### tips:十年OI一场空，不开long long见祖宗

---

## 作者：TsH_GD (赞：0)

 分析出来了一个虚假的贪心：

现在让当前的步数代价走完全程（之前的肯定都只走一步）。

比较每一个的最小值，如果这个不用两个维度走的话大概率是对的。

但是出现了问题在于这是两个维度。

每一个维度虽然数值上不相关，但是步数关系上是相关的（比方说，我现在右向我只选了 $ 3 $ 组数据，但是上向就不能选第 $ 6 $ 组了（不能跳着选））。

那么我们只需要让最小的步数尽量走的更多，每一次都枚举一遍，最后比较一下选最小的就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long  a[2102100];
int main() {
	long long  T;
	cin>>T;
	while(T--) {
		long long  n;
		cin>>n;
		for(long long  i=1; i<=n; i++)cin>>a[i];
		long long  res1=1e18,minn2=1e18;
		long long  res2=1e18,minn1=1e18;
		long long  sum1=0;
		long long  sum2=0;
		long long  ans=1e18;
		for(long long  i=1; i<=n; i++) {
			if(i%2) {
				res1=0;
				sum1+=a[i];
				res1+=sum1;
				minn1=min(minn1,a[i]);
				res1+=(n-(i)/2-1)*minn1;
			} 
			else {
				res2=0;
				sum2+=a[i];
				res2+=sum2;
				minn2=min(minn2,a[i]);
				res2+=(n-(i-1)/2-1)*minn2;
			}
			ans=min(ans,res1+res2);
		}
		cout<<ans<<endl;
	}
}

```

---

