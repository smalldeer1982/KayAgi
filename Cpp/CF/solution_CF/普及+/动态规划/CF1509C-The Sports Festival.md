# The Sports Festival

## 题目描述

The student council is preparing for the relay race at the sports festival.

The council consists of $ n $ members. They will run one after the other in the race, the speed of member $ i $ is $ s_i $ . The discrepancy $ d_i $ of the $ i $ -th stage is the difference between the maximum and the minimum running speed among the first $ i $ members who ran. Formally, if $ a_i $ denotes the speed of the $ i $ -th member who participated in the race, then $ d_i = \max(a_1, a_2, \dots, a_i) - \min(a_1, a_2, \dots, a_i) $ .

You want to minimize the sum of the discrepancies $ d_1 + d_2 + \dots + d_n $ . To do this, you are allowed to change the order in which the members run. What is the minimum possible sum that can be achieved?

## 说明/提示

In the first test case, we may choose to make the third member run first, followed by the first member, and finally the second. Thus $ a_1 = 2 $ , $ a_2 = 3 $ , and $ a_3 = 1 $ . We have:

- $ d_1 = \max(2) - \min(2) = 2 - 2 = 0 $ .
- $ d_2 = \max(2, 3) - \min(2, 3) = 3 - 2 = 1 $ .
- $ d_3 = \max(2, 3, 1) - \min(2, 3, 1) = 3 - 1 = 2 $ .

The resulting sum is $ d_1 + d_2 + d_3 = 0 + 1 + 2 = 3 $ . It can be shown that it is impossible to achieve a smaller value.

In the second test case, the only possible rearrangement gives $ d_1 = 0 $ , so the minimum possible result is $ 0 $ .

## 样例 #1

### 输入

```
3
3 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
1
5```

### 输出

```
0```

## 样例 #3

### 输入

```
6
1 6 3 3 6 3```

### 输出

```
11```

## 样例 #4

### 输入

```
6
104 943872923 6589 889921234 1000000000 69```

### 输出

```
2833800505```

# 题解

## 作者：Cutest_Junior (赞：15)

## 题解 CF1509C 【The Sports Festival】

### 题意

+ 对长度为 $n$ 的序列 $a$ 进行重排，设 $d_i=\max\limits_{j=1}^ia_j-\min\limits_{j=1}^ia_j$，要使 $\sum\limits_{i=1}^n d_i$ 最小；
+ $n\le2000$，$1\le a_i\le10^9$。

### 做法

我们发现无论怎么排 $d_n$ 始终不变，那就使 $\sum\limits_{i=1}^{n-1} d_i$ 最小。

容易想到把 $a_{max}$ 或 $a_{min}$ 放在最后面。

证明：如果其中一个放在最后面，只有 $d_n$ 等于 $a_{max}-a_{min}$，其他都小于 $a_{max}-a_{min}$。但如果提到前面，就有多个 $d_i$ 都增加到 $a_{max}-a_{min}$，而更前面的 $d_i$ 不会受到影响，则 $\sum\limits_{i=1}^n d_i$ 会变大。

因为每次都要用最大值和最小值，可以先对 $a$ 升序排序，容易根据上面的证明推出前 $i$ 个数在排序后的 $a$ 中一定是连续段。

至此，可以设计出状态 $dp_{i,j}$ 为前 $j-i+1$ 个数分别放 $a_i,a_{i+1},\dots,a_{j-1},a_j$ 时，最小的 $\sum\limits_{k=1}^{j-i+1}d_k$。

因为最后一个数一定是 $a_i$ 或 $a_j$，所以 $dp_{i,j}=\min(dp_{i+1,j},dp_{i,j-1})+a_j-a_i$。

然后惊奇的发现：这不是裸的区间 dp 吗？

### 代码

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 2005;

int a[N];

ll dp[N][N];

void solve() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + n + 1);
	for (int k = 1; k <= n; ++k) {
		for (int l = 1; l <= n; ++l) {
			int r = l + k - 1;
			if (r > n) {
				continue;
			}
			dp[l][r] = a[r] - a[l] + min(dp[l][r - 1], dp[l + 1][r]);
		}
	}
	printf("%lld\n", dp[1][n]);
}

int main() {
//	int t;
//	scanf("%d", &t);
//	while (t--) {
		solve();
//	}
}
```

---

## 作者：lsz_ (赞：5)

[题目链接（CF 版）](https://codeforces.com/problemset/problem/1509/C)

[题目链接（洛谷版）](https://www.luogu.com.cn/problem/CF1509C)

[更好的阅读体验](https://www.luogu.com.cn/blog/lsz-qwq/solution-cf1509c)

### 题意

+ 对长度为 $n$ 的数组 $s$ 进行重排，使得 $\sum\limits_{i=1}^n(\max\limits_{j=1}^is_j-\min\limits_{j=1}^is_j)$ 最小；

+ $1\leq n\leq2\times10^3,1\leq s_i\leq10^9$。

### 思路

易得是从后面开始放数的，因为最后面的数对答案影响最小。

设已经放完了 $k$ 个数，剩下的数构成集合 $A$，现在要填第 $n-k$ 个数。下面证明第 $n-k$ 个数只能放集合 $A$ 中的最大值或最小值。

证明：设集合 $A$ 中的最小值为 $A_{min}$，最大值为 $A_{max}$。若把 $A_{min}$ 或 $A_{max}$ 放在第 $n-k$ 位，则 $\forall x<n-k$，$\max\limits_{i=1}^xs_i-\min\limits_{i=1}^xs_i<A_{max}-A_{min}$，只有 $\max\limits_{i=1}^{n-k}s_i-\min\limits_{i=1}^{n-k}s_i=A_{max}-A_{min}$。反之则 $\exists x<n-k,S.T.\max\limits_{i=1}^xs_i-\min\limits_{i=1}^xs_i\geq A_{max}-A_{min}$，明显更劣。

得在任意时刻集合 $A=\{l,l+1,...,r-1,r\}$。

到这一步已经很明显了：区间 dp。

设 $f_{i,j}$ 为前 $j-i+1$ 位已经填满，填的是 $i,i+1,...,j-1,j$ 时 $\max\limits_{k=1}^{j-i+1}s_k-\min\limits_{k=1}^{j-i+1}s_k$ 的最小值。

因为该区间（即 $1$ 到 $j-i+1$）里的最大值减最小值必定为 $s_j-s_i$，得状态转移为 $f_{i,j}=\min(f_{i+1,j}+f_{i,j-1})+s_j-s_i$。

### 代码

```
#include<bits/stdc++.h>
#define LL long long
#define N 2010
using namespace std;
int n;
int a[N];
LL f[N][N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	sort(a+1,a+n+1);
	for(int l=2;l<=n;l++)
	{
		for(int i=1;i+l-1<=n;i++)
		{
			int j=i+l-1;
			f[i][j]=min(f[i][j-1],f[i+1][j])+a[j]-a[i];
		}
	}
	cout<<f[1][n];
	return 0;
}
```

---

## 作者：Moon_Goddy (赞：5)

## 前言：

这个菜鸡终于上1400了，写个题解纪念下

# 思路：

顺着模拟不好想，不妨**倒推**。

我们以$a[N]$数组表示已经从小到大排好序的速度。

容易想到，最后一定会加上速度**最大值**$-$速度**最小值**（即$d_n$）。

那么往前一步（即$d_{n-1}$）就会出现**两种**情况:

1.$d[n-1]=a[n-1]-a[1]$

2.$d[n-1]=a[n]-a[2]$

## 显而易见的贪心，于是我交了一发

~~然后第五个测试点就WA了~~

#### 问题出在哪里呢？

发现每一步的最优并不一定答案最优（一时没看懂可以好好想想为什么）

------------


于是想到了区间$dp$。

我们用$f[i][j]$ $(i<j)$表示取第$i$人速度**到**第$j$人速度时，答案的最小值。

### 于是：

$$f[i][j]=min(f[i][j-1]+a[j-1]-a[i],f[i+1][j]+a[j]-a[i+1])(i<j)$$



------------
代码附注释。

# CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2010;
#define ll long long
#define fuck printf("-1")
#define en printf(" ")
#define endl putchar('\n') 
#define yes printf("YES")
#define no printf("NO")
 
template<typename T>inline void read(T&x){
	x=0;char q;bool f=1;
	while(!isdigit(q=getchar()))if(q=='-')f=0;
	while(isdigit(q)){
		x=(x<<1)+(x<<3)+(q^48);
		q=getchar();
	}
	x=f?x:-x;
}
template<typename T>inline void print(T x){
	if(x<0){
		x=-x;
		putchar('-');
	}
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
int T,n; 
ll a[N];//空间不开白不开
ll ans;
ll f[N][N];//会爆int
int main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	sort(a+1,a+1+n);

	for(int l=1;l<n;l++){//区间长度
		for(int i=1;i+l<=n;i++){//左端点
			int j=i+l;//右端点
			f[i][j]=min(f[i][j-1]+a[j-1]-a[i],f[i+1][j]+a[j]-a[i+1]);//状态转移
		}
	}
	print(f[1][n]+a[n]-a[1]);//最后还得算上最后一步
	return 0;
}
```


---

## 作者：Supor__Shoep (赞：1)

首先由于数列的顺序可以改变，为了使得 $\sum_{i=1}^{n}d_i$ 的值最小，我们不难想到将原数组从小到大进行排序，这样排序之后，保证这个差值不会太大。同理，从大到小也是可以的，但是为了少写代码，这里使用从小到大的排序。

处理完之后，发现 $1\leq n\leq 2\times 10^3$，顿时想到区间 dp。状态就是正常的 $dp_{i,j}$，表示区间 $[i,j]$ 的答案。由于数组已经从小到大排序了，所以每次 dp 的时候只需要根据区间 $[i+1,j]$ 或者 $[i,j-1]$ 加上 $a_j-a_i$ 的值就可以了。

最后转移方程为：

$$dp_{i,j}=\min(dp_{i+1,j},dp_{i,j-1})+(a_j-a_i)$$

最后给一下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2005;
int n;
long long a[MAXN];
long long dp[MAXN][MAXN];//不开 long long 见祖宗
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)   cin>>a[i];
    sort(a+1,a+n+1);
    //可以省略掉初始化 dp[i][i]=0
    for(int len=2;len<=n;len++)
    {
        for(int i=1;i<=n-len+1;i++)
        {
            int j=i+len-1;
            dp[i][j]=a[j]-a[i]+min(dp[i+1][j],dp[i][j-1]);
        }
    }
    cout<<dp[1][n];
    return 0;
}
```

---

## 作者：jiangtaizhe001 (赞：1)

题目翻译：给出一个序列 $a_1,a_2,\dots,a_n$ ，将序列重新排列，定义 $d_i=\max\{a_1,a_2,\dots\,a_i\}-\min\{a_1,a_2,\dots\,a_i\}$ ,求 $\sum d_i$ 的最小值。  

我们先将序列进行排序（从小到大），我们发现，我们如果选择了 $a_i$ ,那么我们接下来就一定要选择 $a_{i-1}$ 或者是 $a_{i+1}$ （贪心？）。  
这时我们发现，我们选择的总是一个连续的子序列，所以我么就可以根据这个结论搜索。  
我们发现这题即可以贪心，同时可以搜索，那么显然就是DP。

数据范围 $n\le 2000$ ，而且我们发现，我们可以通过区间的扩展来得到答案，那么显然是区间DP，我们令 $f_{i,j}$ 为选择区间 $[i,j]$ 的答案，那么不难得到：
$$f_{i,j}=a_j-a_i+\min\{f_{i+1,j},f_{i,j-1}\}$$

代码：
```cpp
#include<cstdio>
#include<algorithm>
#define maxn 2039
using namespace std;
//#define debug
typedef long long ll;
typedef int Type;
inline Type read(){
	Type sum=0;
	int flag=0;
	char c=getchar();
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') c=getchar(),flag=1;
	while('0'<=c&&c<='9'){
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	if(flag) return -sum;
	return sum;
}
inline int min(int a,int b){ return a<b?a:b; }
ll f[maxn][maxn],sum[maxn];
int a[maxn],s[maxn];
int n;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++) s[i]=read();
    sort(s+1,s+n+1); n--;
    for(int i=1;i<=n;i++)
        a[i]=s[i+1]-s[i];
    for(int i=1;i<=n;i++)
        f[i][i]=a[i];
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+a[i];
    for(int i=n;i>=1;i--)
        for(int j=i+1;j<=n;j++)
			f[i][j]=min(f[i+1][j],f[i][j-1])+(sum[j]-sum[i-1]);
    printf("%lld",f[1][n]);
	return 0;
}////
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1509C)

&nbsp;

### 题目大意：
给定一个长度 $n$ 的序列 $s$，你可以重新调整序列中元素的顺序，使得 $\sum_{i=1}^n(\max_{j=1}^is_j-\min_{j=1}^is_j)$ 最小，输出这个最小值。

&nbsp;

### 解题思路：
考虑对于区间 $[l,r]$ 如何放置最优，显然，重新排列后的 $a_r$ 一定是区间内最大或最小的数，假设 $a_r$ 不满足该条件，则 $(\max_{i=l}^rs_i-\min_{i=l}^rs_i)$ 显然仍为 $[l,r]$ 间的最大值与最小值之差，而这时显然也会存在 $(\max_{i=l}^{r-j}s_i-\min_{i=l}^{r-j}s_i)(j>0)$ 也为 $[l,r]$ 间的最大值与最小值之差，显然不优。

同时由于上面这个条件，我们也可以得出区间 $[l,r]$ 的数按升序排列后在升序排列的 $s$ 序列中显然也可以找到相同的子段，于是我们可以将 $s$ 升序排列，然后用区间 `dp` 求解。

我们设 $dp[i][j]$ 为 区间 $[i,j]$ 之间的最小答案，转移方程为：

$$dp[i][j]=\min(dp[i+1][j],dp[i][j-1])+s[j]-s[i]$$

代码如下：

```cpp
int main(){
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		dp[i][i]=0;//区间长度为1的区间答案为0
	}
	
	sort(a+1,a+1+n);//升序排序
	
	for(int len=2;len<=n;len++){
		for(int i=1;i+len<=n+1;i++){
			int j=i+len-1;
			dp[i][j]=min(dp[i+1][j],dp[i][j-1])+a[j]-a[i];//转移
		}
	}
	
	printf("%lld",dp[1][n]);
	return 0;
}
```

我们可以发现转移只与长度为 $len-1$ 的区间有关，于是考虑滚动数组节省空间，将 `dp` 数组转为 $dp[i]$，指长度为 $len$ 时左端点为 $i$ 的区间的最小答案。

代码如下：

```cpp
int main(){
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		dp[i]=0;
	}
	
	sort(a+1,a+1+n);
	
	for(int len=2;len<=n;len++){
		for(int i=1;i+len<=n+1;i++){
			int j=i+len-1;
			dp[i]=min(dp[i+1],dp[i])+a[j]-a[i];

		}
	}
	
	printf("%lld",dp[1]);
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/x0poy0pg.png)

完结撒花 OvO！！！

---

## 作者：Erica_N_Contina (赞：0)

## 题意

对于给定的 $s$ 我们改变 $s$ 的顺序使得 $s$ 的所有前缀的极值差之和最小。

## 思路

我们假设 $s$ 已经从小到大排序好了。我们考虑一个初始的序列 $T$，假设 $T$ 中已经有一些数字了，已知 $T$ 中的最大值为 $maxn$，最小值为 $minn$，那么现在我们把一个数 $s_i$ 加入进来。如果 $s_i$ 在 $minn$ 和 $maxn$ 之间，那么很显然是没有影响的。如果 $s_i$ 大于 $maxn$，那么它对当前及后面的部分操作是有影响的。$minn$ 同理。

所以我们考虑如果把 $s$ 中的最小值放在最前面，把最大值放在第 $2$ 个位置，那么对于每个前缀，其 $minn$ 都是最小的，这样显然我们的差值就会变得很大。并且我们的最大值就放在第 $2$ 个位置，那么从长度为 $2$ 的前缀开始，$maxn$ 就是 $s$ 的最大值了，差值更大了。这种情况很显然是非常劣的情况。

那么我们是否可以发过来，把 $s$ 中的最大值和最小值放在最后面。那么继续，我们把次大值和次小值放在倒数第 $3,4$ 个位置，以此类推。这种情况可以证明一定是很优秀的做法。但是有些时候我们是把第 $k$ 大值放在后面还是把第 $k$ 小值放在后面是一个问题，因为对于第 $k$ 最值，不一定第 $k$ 大值要放在第 $k$ 小值放在后面，也有可能放在前面呀。

所以其实本题可以抽象为在一个双端队列 $s$（这里 $s$ 即题目中的 $s$ 从小到大排序）两端不断取出值来从后往前填充序列 $T_{ans}$（$T_{ans}$ 即为使得答案最小的 $s$ 的重排列）。每次我们可以从前面或者后面取出 $s$ 中的一个数填入 $T_{ans}$ 中。那么我们就可以定义 $dp_{l,r}$ 为从 $s$ 的前面取出 $l$ 个，从后面取出 $r$ 个时局部答案的最小值。那么 $dp_{l,r}$ 对应的局部 $T$ 序列的状态即 $T'={s_{l+1},\dots,s_{n-r}}$，很明显 $T'$ 中的 $maxn$ 即 $s_{n-r}$，$minn$ 即 $s_{l+1}$。

于是我们的 dp 转移可以写成：$dp_{l,r}=\min(dp_{l,r-1},dp_{l+1,r})+s_{n-r}-s_{l+1}$。实际代码中我们定义状态为 $dp_{n-r,l+1}$ 也是可以的，这样我们就枚举 $l$ 和 $r-l$ 即可。



## 代码

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long


#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


const int N=3e3+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;

int q;
int t,ans,a[M],mn=INF,mx;
int len,r;
int dp[N][N];
int s[M];

bool f2;


signed main(){
	// freopen("xor.in","r",stdin);
	// freopen("xor.out","w",stdout);
	n=rd;
	for(int i=1;i<=n;i++){
		s[i]=rd;
	}
	sort(s+1,s+n+1);
	for(int len=1;len<n;len++){
		for(int l=1,r=l+len;l<=n;l++,r=l+len){			
			dp[l][r]=min(dp[l+1][r],dp[l][r-1])+s[r]-s[l];
		}
	}
	cout<<dp[1][n];

	return 0;
}

/*
2
3 2 3 6
*/
```




---

## 作者：jasonliujiahua (赞：0)

# CF1509C The Sports Festival 1800

[题目传送门](https://www.luogu.com.cn/problem/CF1509C)
## 题意简述：
给定长度为 $n$ 的序列 $a$，你可以改变序列 $a$ 的顺序，求
$$\sum_{i=1}^n (\max_{j=1}^i a_j-\min_{j=1}^i a_j)$$
的最小值。
$1\le n \le 2×10^3;1\le a_i \le 10^9$
## 题目分析：
### Step 1：
**对于每一个 $1$ 到 $i$，其末尾应该是 $a_1$ 到 $a_i$ 的极值（最大或最小值）**
可以考虑贪心进行解释。记 
$$x=\max_{j=1}^i a_j-\min_{j=1}^i a_j$$
 我们可以发现 $x$ 在答案中出现的越少，答案越小。因为若用一个非极值去做第 $i$ 个数，则 $x$ 第一次出现的位置会更靠前，而第一次出现后 $1$ 到 $n$ 的答案每次的统计值都为 $x$，所以 $x$ 会出现不止一次。因此，极值应放在末尾。
### Step 2：
因为每个 $1$ 到 $i$ 都要用到极值，不妨考虑排序。
### Step 3：
有两种决策：最后放最大值或最小值。可以进行区间dp。
$\mathit{dp}_{i,j}$ 表示放 $a_i$ 到 $a_j$ 的答案。有转移方程：
$$\mathit{dp}_{i,j}=min(\mathit{dp}_{i+1,j},\mathit{dp}_{i,j-1})+a_i-a_j$$
$\mathit{dp}_{i+1,j}$ 代表 $a_i$ 到 $a_j$ 的最小值 $a_i$ 放在末尾，$\mathit{dp}_{i,j-1}$ 则是最大值。最后，不管谁放末尾，都要加上一个 $x$，即 $a_i-a_j$。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2010;
ll n,a[maxn],dp[maxn][maxn];
void init()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
}
void DP()
{
    for(int w=1;w<n;w++)
        for(int i=1,j=i+w;j<=n;i++,j++)
            dp[i][j]=min(dp[i+1][j],dp[i][j-1])+a[j]-a[i];
}
int main()
{
    init();
    DP();
    cout<<dp[1][n];
    return 0;
}
```



---

## 作者：Little09 (赞：0)

先把 $s$ 排序。从 $1$ 到 $n$ 地填入 $s_i$，显然每次填的应当与之前某次填的相邻（否则必亏）。

我们可以考虑把 $s$ 差分得到数组 $b$，利用类似费用提前计算的思想，在第 $i$ 个数填入数 $x$ （$x$ 是 $b$ 中的一个数）的代价应当是 $(n-i+1)*x$。意思就是这一个和之后所有的极差计算中都会涉及到 $x$。

直接上区间 DP 即可。

部分代码：

```cpp
void work()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for (int i=1;i<n;i++) b[i]=a[i+1]-a[i];
	n--;
	for (int i=1;i<=n;i++) dp[i][i]=b[i]*n;
	for (int len=2;len<=n;len++)
	{
		for (int i=1;i<=n;i++)
		{
			int j=i+len-1;
			if (j>n) break;
			dp[i][j]=min(dp[i][j-1]+b[j]*(n-len+1),dp[i+1][j]+b[i]*(n-len+1));
		}
	}
	cout << dp[1][n];
	return;
}
```


---

