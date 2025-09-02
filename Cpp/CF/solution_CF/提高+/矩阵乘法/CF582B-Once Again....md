# Once Again...

## 题目描述

现有一个长度为 $n×T$ 的序列 $a_1, a_2, ..., a_{n×T}$ ，满足 $a_i=a_{i-n} (n<i<=n×T)$ 。请找出这个序列中的最长不降子序列的长度。

## 说明/提示

样例中给出的序列如下：3, **1**, 4, **2**, **3**, 1, **4**, 2, 3, 1, **4**, 2. 加粗的数字是一种最长不降子序列的方案。

## 样例 #1

### 输入

```
4 3
3 1 4 2
```

### 输出

```
5
```

# 题解

## 作者：Dream_It_Possible (赞：9)

##  **题意**：
给你t个长度为n的数组。问你最长不下降子序列的长度。
## **解法**:
**1**.找数组最小循环节，
 _```len=n*min(n,t);```	_ 

**2**.找数字出现的最大次数
```cpp
int mxaa=0;
for(i=0;i<305;i++)
mxaa=max(mxaa,b[i]);
```
**3**.数组元素初始化：
```cpp
for(i=n+1;i<=len;i++)
	a[i]=a[i-n];
```

**4**.扫出长度为len的lis。
```cpp
for (i=1;i<=len;i++)
	{
		f[i]=1;
		for (j=i-1;j>=max(i-n,1);j--)
		{
			if (a[i]>=a[j])
			f[i]=max(f[i],f[j]+1);
		}
		mxa=max(mxa,f[i]);
	}
```
**5**.
t<=n输出mxa,

t>n，mxa再加上数字出现的最大次数*(t-n)

完整code:
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int a[10005],f[10005],b[305];
int main()
{
	int n,t,i,j;
	cin>>n>>t; 
	int len=n*min(n,t);	
	for (i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[a[i]]++;
	}
	int mxa=1;
	for(i=n+1;i<=len;i++)
	a[i]=a[i-n];
	for (i=1;i<=len;i++)
	{
		f[i]=1;
		for (j=i-1;j>=max(i-n,1);j--)
		{
			if (a[i]>=a[j])
			f[i]=max(f[i],f[j]+1);
		}
		mxa=max(mxa,f[i]);
	}
	if (n>=t)
	cout<<mxa<<endl;
	else
	{
		int mxaa=0;
		for(i=0;i<305;i++)
		mxaa=max(mxaa,b[i]);
		cout<<mxa+mxaa*(t-n)<<endl;
	}
	return 0;
}  
```

---

## 作者：Wen_kr (赞：7)

考虑一种暴力的做法

我们建立一个 $n * n$ 的矩阵 $mat$

令 $mat_{i,j}$ 表示从 $i$ 到 $j$ 的最长不下降子序列的长度

则我们可以像 $dp$ 一样预处理出长度 代码如下：

```cpp
//seq 为原序列
for(int i = 1;i <= n; ++ i)
	for(int j = 1;j <= n; ++ j)
    	if(seq[i] > seq[j]) mat[i][j] = -0x3f3f3f3f;
        else {
        	mat[i][j] = 1;
        	for(int k = 1;k < j; ++ k)
            	if(seq[k] <= seq[i])
                	mat[i][j] = max(mat[i][j], mat[i][k] + 1);
        }
```

处理完之后，我们考虑怎么求原序列重复 $T$ 次的结果

考虑重载矩阵乘法，则矩阵乘法变为：

$$C[i][j] = max_{k=1}^{n}\{a[i][k] + b[k][j]\}$$

这样使用矩阵快速幂即可得出答案。

时间复杂度： $O(n^3 log T)$


然而，这个时间复杂度是最优的吗？并不。

观察序列，发现序列中最多会出现 $n$ 个不同的元素，这告诉我们若 $T > n$ 在第 $n$ 次循环后新增加的最长不降子序列的长度等于序列中出现次数最多的元素个数。

而最长上升子序列可以在 $n log n$ 的时间内求出，因此我们求出长度为 $n*n$ 的最长不下降子序列长度即可通过出现次数最多的元素得到解。

时间复杂度 $O(n^2log^2n)$

代码复杂度为 $O(n^4)$
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n,T;
int seq[10050];
int ori[1050];
int dp[10050];
int sum[304];

int main()
{
	int mxn = 0;
	scanf("%d%d",&n,&T);
	for(int i = 1;i <= n; ++ i)
	{
		scanf("%d",&ori[i]);
		sum[ori[i]] ++;
		if(sum[ori[i]] > mxn) mxn = sum[ori[i]];
	}
	for(int i = 1;i <= min(n,T); ++ i)
		for(int j = 1;j <= n; ++ j)
			seq[(i - 1) * n + j] = ori[j];
	int lst = 0,cur = 0;
	int mxn1 = 0;
	for(int i = 1;i <= n * min(n,T); ++ i)
	{
		dp[i] = 1;
		for(int j = 1;j < i; ++ j)
			if(seq[j] <= seq[i])
				dp[i] = max(dp[i],dp[j] + 1);
		if(i / n == min(n,T) - 1 && i % n != 0)
			mxn1 = max(mxn1,dp[i]);
	}
	mxn1 = max(mxn1,dp[n * min(n,T)]);
	if(T <= n)
		printf("%d\n",mxn1);
	else
		printf("%d\n",mxn1 + mxn * (T - n));
}
```

---

## 作者：Eafoo (赞：2)

我们称第 $(i - 1) \cdot n + 1$ 个数 到 第 $i \cdot n$ 个数 为 第 $i$ 段。

首先分 $n \le T$ 和 $n > T$ 两种情况讨论。

如果 $n \le T$，那么我们直接把原数列复原出来跑个 LIS 就行。

如果 $n > T$，我们把整个序列分为三部分，左边一部分是前 $n - 1$ 段，右边一部分是最后一段，剩下的段归到中间部分中。

然后我们举例分析：

考虑这样一组数据：

```
3 6
1 1 2
```

那么原数列是：
```
1 1 2 | 1 1 2 | 1 1 2 | 1 1 2 | 1 1 2 | 1 1 2
```

我们先跑出来左边一部分和右边一部分合在一起的 LIS。由于原数列每一段都是相等的，所以这个过程也等同于对前 $O(n ^ 2)$ 个数求 LIS。

之后我们尝试把中间部分的数加进去，那么最终的答案就是刚才求出的 LIS 长度加上一段内每个数出现次数的最大值乘上剩余段的个数。

形式化地说，若设求出 LIS 的长度为 $x$，则答案为：

$
x + \displaystyle \max_{i  \in {[1, n]}} tot_{a_i} \times (T - n)
$

其中 $tot_i$ 表示 $i$ 在一段中的出现次数。

考虑证明这个结论。

我们不难发现，如果我们只在中间部分中选一种数插入刚刚求出的 LIS 中，一定会存在一种合法方案。

其次，如果我们选多种数插入刚刚的 LIS 中，是不存在合法方案的。

因此，我们只能选一段中出现次数最多的数插入 LIS 中。

用二分法求 LIS，时间复杂度 $O(n ^ 2 \log n)$。

``` cpp
#include <bits/stdc++.h>
#define ff fflush(stdout)
#define fop(x, l, r) for (int x = l; x <= r; ++x)
#define pof(x, r, l) for (int x = r; x >= l; --x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define int ll // 注意
int Pow(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, mmod(a, a)) if (b & 1) mmod(ans, a);
    return ans;
}
char gc() { char c; while (!isalpha(c = getchar())); return c; }
int read() {
    int x = 0; char c; bool f = 0;
    while (!isdigit(c = getchar())) if (c == '-') f = 1;
    do x = (x << 1) + (x << 3) + (c ^ 48); while (isdigit(c = getchar()));
    return f ? -x : x;
}

const int maxn = 1e4 + 3;

int a[maxn];
int lis[maxn], tot;

signed main() {
    int n = read(), T = read();
    fop(i, 1, n) {
        int x = read();
        fop(j, 0, min(n - 1, T - 1)) a[i + j * n] = x;
    }
    // 求 LIS
    fop(i, 1, min(n * T, n * n)) {
        if (a[i] >= lis[tot]) lis[++tot] = a[i];
        else *upper_bound(lis + 1, lis + tot + 1, a[i]) = a[i];
    }
    int res = 0;
    int ans = tot;
    // 统计答案
    if (n < T) fop(i, 1, n) {
        res = 0;
        fop(j, 1, n) if (a[j] == a[i]) ++res;
        ckmax(ans, tot + (T - n) * res);
    }
    printf("%lld\n", ans);
}
```

---

## 作者：gesong1234 (赞：1)

题目传送门：[CF582B](https://www.luogu.com.cn/problem/CF582B)。

# 思路

来个无脑矩阵快速幂做法。

设 $f_{i,j}$ 表示第 $i$ 次重复中已第 $j$ 项结尾的最长不降子序列长度，转移即为：

$$f_{i,j}=\max(\max_{a_k\le a_j} f_{i-1,k}+1,\max_{k<j,a_k\le a_j} f_{i,k}+1)$$

考虑重新定义矩阵乘法：

$$c_{i,j}=\max(c_{i,j},a_{i,k}+b_{k,j})$$

考虑构造一个矩阵 $A$ 使得 $[f_{i-1,1},f_{i-1,2},\cdots ,f_{i-1,n}]\times A=[f_{i,1},f_{i,2},\cdots ,f_{i,n}]$。

根据上面的转移即可写出矩阵，具体的可以看代码。

然后矩阵快速幂即可。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N=210;
int n,a[N],m;
struct node{
	int a[N][N];
	inline void init(){
		memset(a,-0x3f,sizeof(a));
	}
	node operator *(const node &b) const{
		node c;c.init();
		for (int i=1;i<=n;i++)
			for (int k=1;k<=n;k++)
				for (int j=1;j<=n;j++)
					c.a[i][j]=max(c.a[i][j],a[i][k]+b.a[k][j]);
		return c;
	}
}; 
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
node qpow(node a,int b){
	node s;s.init();
	for (int i=1;i<=n;i++) s.a[i][i]=0;
	while(b){
		if (b&1) s=s*a;
		a=a*a;
		b>>=1;
	}
	return s;
}
main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	node aa,b;aa.init(),b.init();
	for (int i=1;i<=n;i++) aa.a[1][i]=0;
	for (int i=1;i<=n;i++)//构造矩阵
		for (int j=1;j<=n;j++) if (a[i]<=a[j]){
			b.a[i][j]=1;
			for (int k=1;k<j;k++) if (a[k]<=a[j]) b.a[i][j]=max(b.a[i][j],b.a[i][k]+1);
		}
	aa=aa*qpow(b,m);
	int ans=0;
	for (int i=1;i<=n;i++) ans=max(ans,aa.a[1][i]);
	cout <<ans;
    return 0;
}
```

---

## 作者：jch123 (赞：1)

## 思路：

- $k \le n$ 时，直接暴力跑就行。
- $n<k$ 时，显然有一段应该重复去选，考虑选 $1,2,2\dots 2,3$ 与 $1,2,3,3,3\dots$ 是等价的，所以直接选 $a$ 里面出现次数最多的。

综上，先跑长度为 $n\times \min(n,k)$ 的最长不下降子序列，然后如果 $n<k$ 就去选出现次数最多的 $\times (k-n)$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int a[N],b[N],dp[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i],b[a[i]]++;
	int m=n*min(n,k);
	for(int i=n+1;i<=m;i++)
		a[i]=a[i-n];
	for(int i=1;i<=m;i++)
	{
		dp[i]=1;
		for(int j=i-1;j>=max(i-n,1);j--)
			if(a[i]>=a[j])
				dp[i]=max(dp[i],dp[j]+1);
	}
	int ans=0;
	for(int i=1;i<=m;i++)
		ans=max(ans,dp[i]);
	if(k<=n) cout<<ans;
	else 
	{
		int res=0;
		for(int i=1;i<=300;i++)
			res=max(res,b[i]);
		cout<<ans+res*(k-n);
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

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

const int N=5e5+5;
const int INF=1e18+5;
const int MOD=998244353;
int ans,m;
int f[N];
int a[N],b,cnt[N],len,T,n;

void dp(){
	for(int i=1;i<=len;i++){
		f[i]=1;
		for(int j=i-1;j>=max(1ll,i-n);j--){//只要枚举一个循环节内的即可
			if(a[i]>=a[j])f[i]=max(f[i],f[j]+1);
		}
	}
	for(int i=1;i<=len;i++)ans=max(ans,f[i]);
}

signed main(){
	n=rd,T=rd;
	for(int i=1;i<=n;i++)a[i]=rd,cnt[a[i]]++;
	len=n*min(n,T);
	for(int i=n+1;i<=len;i++)a[i]=a[i-n];
	
	dp();
	
	if(len==n*n){
		int mxn=0;//找出现次数最多的数字的出现次数
		for(int i=0;i<=300;i++)mxn=max(mxn,cnt[i]);
		ans+=mxn*(T-n);
	}
	cout<<ans<<endl;
}

```


## 思路

给你一个很长的但是有循环节且每个循环节不长的序列，求其最长不降子序列的长度。

那么我们肯定要从循环的角度考虑。我们考虑吧循环分成三个部分——头循环，中间循环，尾循环。其中中间循环包含 $T-2$ 个循环。

那么我们只需要考虑头循环和尾循环就行了。显然地，每个属于中间循环的循环中，我们都会选择若干个位置相同的数，且通常情况下，我们都会选数值相同的那个数字。

并且头循环和尾循环是一样的，所以我们可以把所有循环压缩成一个循环。

假设一个循环为 $a_1,\dots,a_n$，头循环中我们选择了 $a_{h_1},\dots,a_{h_k}$，尾循环中我们选择了 $a_{t_1},\dots,a_{t_l}$，中间循环我们选择了数字 $a_m$。那么我们可以使用 $T$ 计算出中间循环有几个 $a_m$ 的。这一点预处理即可。

可以证明，通常情况下我们应该**贪心**地选择出现次数最多的 $a_m$，其余的（即头尾）我们合在一起跑一次 LIS 的 dp 即可。

另外的特殊情况就是循环节中出现了降序部分且 $T<n$。考虑 `1 2 4 3`，$T=3$，那么很显然按上面的我们会跑出`1 2 2 3`，但是实际上我们可以 `1 2 2 3 3`。又或者是 `5 4 3 2 1`，在 $T<n$ 时，可以自己模拟一下。因此，我们应该要跑 $n$ 组合起来的 LIS 才对，这是个细节。

---



---

## 作者：SMTwy (赞：1)

当组数大了之后，一定是有一个数在不断重复的被选。

因为连续地选两个 $2$ 和 一个 $3$ 与选一个 $2$ 和两个 $3$ 在本质上是没有区别的。

那么考虑什么时候应该去匹配不下降序列，什么时候去重复地选那个数。

实际上，只需要对前 $n$ 块跑常规的最长不下降序列，再在求出来的序列上寻找哪个数在每个块中出现的次数最多即可。

对于前 $n$ 块跑是因为要保证不遗漏每一个可能组成序列的数，原数组长度就是 $n$，跑到 $n$ 就是极限，不会出现遗漏，$n$ 是 $100$，在复杂度上完全可以接受。

因为一定会有一个数重复，肯定是让在一个块中出现次数多的数去进行这个重复，并且可以在最后一块去补上不下降序列中大于它的数。

因为还要判断 $n$ 与 $T$ 的大小关系，所以我的代码里就直接拿 $100$ 去分讨了，本质是没有区别的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mx=300+10;
int n,T,a[mx*mx],low[mx*mx],cnt[mx*mx];
int b[mx],bb,dp[mx];
ll ans;
void MYH(){
    scanf("%d%d",&n,&T);
    for(int i=1;i<=n;++i){scanf("%d",&a[i]);cnt[a[i]]++;}
    if(T<=100){
        int tot=T*n;
        for(int t=2;t<=T;++t){
            for(int i=(t-1)*n+1;i<=t*n;++i){a[i]=a[i-n];}
        }
        low[1]=a[1];ans=1;
        for(int i=2;i<=tot;++i){
            if(a[i]>=low[ans]){
                low[++ans]=a[i];
                continue;
            }
            int pos=upper_bound(low+1,low+ans+1,a[i])-low;
            low[pos]=a[i];
        }
        printf("%lld\n",ans);
        return ;
    }
    for(int t=2;t<=100;++t){
        for(int i=(t-1)*n+1;i<=t*n;++i){
            a[i]=a[i-n];
        }
    }
    int tot=n*100;
    low[1]=a[1];ans=1;
    for(int i=2;i<=tot;++i){
        if(a[i]>=low[ans]){
            low[++ans]=a[i];continue;
        }
        int pos=upper_bound(low+1,low+ans+1,a[i])-low;
        low[pos]=a[i];
    }
    int ma=0,pos=0;
    for(int i=ans;i>=1;--i){
        if(cnt[low[i]]>ma){
            ma=cnt[low[i]];pos=i;
        }
    }
    ll o1=ma*(T-100);
    ans=ans+o1;
    printf("%lld\n",ans);
}
int main(){
  //  freopen("once.in","r",stdin);
  //  freopen("once.out","w",stdout);
    MYH();
    return 0;
}
```




---

