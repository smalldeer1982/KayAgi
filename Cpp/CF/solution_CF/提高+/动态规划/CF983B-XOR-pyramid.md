# XOR-pyramid

## 题目描述

For an array $ b $ of length $ m $ we define the function $ f $ as

 $  f(b) = \begin{cases} b[1] & \quad \text{if } m = 1 \\ f(b[1] \oplus b[2],b[2] \oplus b[3],\dots,b[m-1] \oplus b[m]) & \quad \text{otherwise,} \end{cases}  $ where $ \oplus $ is [bitwise exclusive OR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

For example, $ f(1,2,4,8)=f(1\oplus2,2\oplus4,4\oplus8)=f(3,6,12)=f(3\oplus6,6\oplus12)=f(5,10)=f(5\oplus10)=f(15)=15 $

You are given an array $ a $ and a few queries. Each query is represented as two integers $ l $ and $ r $ . The answer is the maximum value of $ f $ on all continuous subsegments of the array $ a_l, a_{l+1}, \ldots, a_r $ .

## 说明/提示

In first sample in both queries the maximum value of the function is reached on the subsegment that is equal to the whole segment.

In second sample, optimal segment for first query are $ [3,6] $ , for second query — $ [2,5] $ , for third — $ [3,4] $ , for fourth — $ [1,2] $ .

## 样例 #1

### 输入

```
3
8 4 1
2
2 3
1 2
```

### 输出

```
5
12
```

## 样例 #2

### 输入

```
6
1 2 4 8 16 32
4
1 6
2 5
3 4
1 2
```

### 输出

```
60
30
12
3
```

# 题解

## 作者：fmj_123 (赞：7)

这道题一看感觉没什么思路,可是我们再看一下例子，
```
 f(1,2,4,8)
=f(1⊕2,2⊕4,4⊕8)
=f(3,6,12)
=f(3⊕6,6⊕12)
=f(5,10)
=f(5⊕10)
=f(15)
=15
```
我们可以发现：

设$f[i][j]$为第$i$层的第$j$个数，可得
$f[i][j]=f[i-1][j-1]\ xor \ f[i-1][j]$
(跟杨辉三角有点像啊这个)

那我们就可以递推出$f[i][j]$,再使用DP求出$max[i][j]$(表示从第$i$个数开始，长度为$j$的最大值)。就可以快速的求解了。

	
```
//在代码中，maxx[i][j]实际表示从第i个数开始，长度为j+1的最大值
#include<bits/stdc++.h>
using namespace std;
int n,q,l,r,f[5010][5010],maxx[5010][5010];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
	  scanf("%d",&f[i][0]);maxx[i][0]=f[i][0];//读入的数即为f[i][0]
    }
	for (int i=1;i<n;i++)
	{
		for (int j=1;j<=n-i;j++)
		{
		  f[j][i]=f[j][i-1]^f[j+1][i-1];
		  maxx[j][i]=max(f[j][i],max(maxx[j][i-1],maxx[j+1][i-1]));
          //处理f[i][j]和maxx[i][j]（意义同上）
	    }
	}
	scanf("%d",&q);
	for (int i=1;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		if (l>r) swap(l,r);
		if (r>n) r=n;if (l<=0) l=1;
		printf("%d\n",maxx[l][r-l]);//直接输出
	}
	return 0;
}
```

---

## 作者：zhm080507 (赞：3)

### 题意分析

即要求序列 $a$ 中从 $l$ 到 $r$ 中最长**连续子序列**使得 $$f(a_l,...,a_r)$$ 最大。

### 算法分析

注意到 $q$ 的数据范围很大，所以考虑 $O(n)$ 的查询方法。

我们用 $$f(i,k)$$ 表示从 $i$ 开始，到 $(i+k-1)$ 的函数值。

我们容易发现，对于一个序列，$f(i,k)$ 可以由 $f(i,k-1)$ 和 $f(i+1,k-1)$ 转移，
即：
$$
f(i,k)=f(i,k-1)⊕f(i+1,k-1)
$$
所以可以由 $O(n^2)$ 的预处理处理出每一个 $f(i,k)$。

```c++
	for(int i=1;i<=n;i++)
		f[i][0]=g[i][0]=a[i];
	for(int k=1;k<=n;k++){
		for(int i=1;i+k<=n;i++){
			f[i][k]=f[i][k-1]^f[i+1][k-1];
		}
	}
```

但我们发现这样仍然只能以 $O(n^2)$ 查询（枚举起始位置和序列长度），所以我们考虑用 $g(i,k)$ 来记录从从 $i$ 开始，到 $(i+k-1)$ 位间所有连续子序列中的最大函数值。

我们先将 $g(i,j)$ 赋值为从固定以 $i$ 为起点，到 $(i+k-1)$ 位的最大函数值，这一步可以和 $f$ 的预处理同时进行。

然后考虑倒序枚举 $i$，从后往前跟新 $g$ 数组的值：

```c++
	for(int k=1;k<=n;k++){
		for(int i=1;i+k<=n;i++){
			f[i][k]=f[i][k-1]^f[i+1][k-1];
			g[i][k]=max(f[i][k],g[i][k-1]);
		}
	}
	for(int i=n-1;i>=1;i--){
		for(int k=1;i+k<=n;k++){
			g[i][k]=max(g[i][k],g[i+1][k-1]);
		}
	}
```

然后就是完整代码，别忘了初始化。

```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N=5100;
ll a[N],f[N][N],g[N][N];
int n,m,l,r;

int read(){
	int res=0,ff=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') ff=-1;
		ch=getchar();
	}while(isdigit(ch)){
		res=(res<<1)+(res<<3)+ch-'0';
		ch=getchar();
	}
	return res*ff;
}

int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	
	for(int i=1;i<=n;i++)
		f[i][0]=g[i][0]=a[i];
	for(int k=1;k<=n;k++){
		for(int i=1;i+k<=n;i++){
			f[i][k]=f[i][k-1]^f[i+1][k-1];
			g[i][k]=max(f[i][k],g[i][k-1]);
		}
	}
	for(int i=n-1;i>=1;i--){
		for(int k=1;i+k<=n;k++){
			g[i][k]=max(g[i][k],g[i+1][k-1]);
		}
	}
	for(int i=1;i<=m;i++){
		l=read();r=read();
		ll tmp=g[l][r-l];
		printf("%lld\n",tmp);
	}
	return 0;
}
```

有问题欢迎私信我 ~~（小声的求点赞）~~。

---

## 作者：Running_a_way (赞：2)

简单区间 dp。想到区间 dp 就什么都会做了。

---

设计状态 $dp(l, r)$ 表示对原数组区间 $[l, r]$ 进行 $f$ 函数的结果。根据定义有如下转移：

$$
dp(l, r) \gets dp(l, r-1) \oplus dp(l + 1, r)
$$

再设 $g(l, r)$ 表示区间 $[l, r]$ 的所有子区间 $[i, j]$ 中 $dp(i, j)$ 的最大值。更新 $dp$ 的时候顺手对 $g$ 更新一下就好了。时间复杂度 $O(n^2 + q)$。

code:

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 5010;
int n, a[N], f[N][N], g[N][N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], f[i][i] = a[i], g[i][i] = a[i];
    for (int len = 2; len <= n; len++) {
        for (int l = 1, r = len; r <= n; l++, r++) {
            f[l][r] = f[l][r - 1] ^ f[l + 1][r];
            g[l][r] = max(max(g[l][r - 1], g[l + 1][r]), f[l][r]);
        }
    }
    int m; cin >> m;
    while(m--) {
        int l, r; cin >> l >> r;
        cout << g[l][r] << '\n';
    }
    return 0;
}
```

---

## 作者：wujingfey (赞：2)

水题解来了。[传送门](https://www.luogu.com.cn/problem/CF983B)

## 题解报告
题目的 $q$ 是 $10^5$ 级别，但 $n$ 只有 $5000$。所以看到这道题后第一个想法是预处理出所有 $f_{l,r}$ 然后 $O(1)$ 询问。那第一个问题就是怎么预处理了。

根据题目描述：
$$f_{a1,a2,a3,a4}=f_{a1\oplus a2,a2\oplus a3,a3\oplus a4}$$
然后 $a1$,$a2$,$a3$,$a4$ 全部已知，那异或后的所有值都可以根据题意模拟求出来。然后汇聚成表格 $f$。表格画出来是形如一个三角形。
![](https://cdn.luogu.com.cn/upload/image_hosting/deida3vk.png)

在图中每个格子代表的都是一个 $f_{l,r}$，具体来说，层数代表 $[l,r]$ 的长度，列数代表起点。比如第二行第三列代表的就是 $f_{2,3}$。

题目要求 $[l,r]$ 内最大的 $f$，只需要类似于前缀和一样，用 $pre_{i,j}$ 数组记录以 $(i,j)$ 为顶点能管控到的所有 $f$ 中的最大值就好啦。比如 $(2,3)$ 就是在 $(1,3)$,$(1,4)$,$(2,3)$ 中求 $f$ 最大值。

转移方式都很简单：
$$f_{i,j}=f_{i-1,j}\oplus f_{i-1,j+1}$$
$$pre_{i,j}=\max(f_{i,j},pre_{i-1,j},pre_{i-1,j+1})$$

## CODE:
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005;
int n,m,f[N][N],pre[N][N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int x; cin>>x;
		f[1][i]=x,pre[1][i]=x;
	}
	cin>>m;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=(n-i+1);j++){
			f[i][j]=(f[i-1][j]^f[i-1][j+1]);
			pre[i][j]=max(f[i][j],pre[i][j]);
			pre[i][j]=max(pre[i-1][j],pre[i][j]);
			pre[i][j]=max(pre[i-1][j+1],pre[i][j]);
		}
	}
	while(m--){
		int l,r; cin>>l>>r;
		cout<<pre[1+(r-l)][l]<<'\n';
	}
	return 0;
}
```

---

## 作者：Civilight_Eterna (赞：1)

一道水蓝 。

以下分析中的数字都是编号， 用来找规律。 

四个数时：

$$
\begin{aligned}
f(1,2,3,4)& = f(1\oplus2,2\oplus3,3\oplus4)\\&=f(1\oplus3,2\oplus4)\\&=1\oplus2\oplus3\oplus4
\end{aligned}
$$

五个数时：

$$
\begin{aligned}
f(1,2,3,4,5)& = f(1\oplus2,2\oplus3,3\oplus4,4\oplus5)\\&=f(1\oplus3,2\oplus4,3\oplus5)\\&=f(1\oplus2\oplus3\oplus4,2\oplus3\oplus4\oplus5)\\&=1\oplus5
\end{aligned}
$$ 

手绘一下， 可以发现是一个倒金字塔。 

我们用惊人的注意力发现，  

$f$  函数从 4 到 5 只在右侧增加了一列， 且可以由上一层相邻两个异或得到。 设 $dp_{i,j}$ 表示 $f(a_l,a_{l+1},...,a_{r-1},a_r)$ 

由上分析有转移式 $dp_{i,j}=dp_{i+1,j}\oplus dp_{i,j-1}$ 。

实现上我们先枚举 $j$  ， 再倒序枚举 $i$ 进行递推， 细节见代码。

注意是求所有 **连续子序列**  $f$ 的最大值， 所以最后再以同样的形式求一下最大值， 式子如下：
$$
dp_{i,j}=max(dp_{i+1,j} , dp_{i,j-1} , dp_{i,j})
$$
对于每次询问 $l,r$ 直接 输出 $dp_{l,r}$ 即可。 

时间复杂度 $O(n^2)$ 。

代码：



```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,a[5003];
ll dp[5003][5003];
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(ll j=1;j<=n;j++){
		for(ll i=j;i>=1;i--){
			if(i==j)dp[i][i]=a[i];
			else
				dp[i][j]=dp[i+1][j]^dp[i][j-1];
		}
	}
	for(ll j=1;j<=n;j++){
		for(ll i=j;i>=1;i--){
			dp[i][j]=max(dp[i][j],max(dp[i+1][j],dp[i][j-1]));
		}
	}
	cin>>m;
	for(int i=1,l,r;i<=m;i++){
		cin>>l>>r;
		if(l>r)swap(l,r);
		cout<<dp[l][r]<<'\n';
	}
	return 0;
}
```

---

## 作者：_Aurore_ (赞：1)

~~大水题~~

#### 关于性质

不难发现，对于一个长度为 $n$ 的数组 $a$，$f(a_{1,n})=f(a_{1,n-1} \oplus f(a_{2,n}))$ 。具体证明可以自己画一张图，就会发现这很合理。

#### 解决方案

这个 $f$ 函数值的求解是可以使用区间dp的，我们定义状态 $dp_{l,r}$ 表示 $f(a_{l,r})$ ，根据上面的性质进行转移。

答案需要求解 $\max f(a_{l,r}) (L \leqslant l \leqslant r \leqslant R)$
，那么我们可以在原来的 $dp$ 数组上在进行一次区间dp,转移方程如下：

$$dp_{l,r}= \max(dp_{l,r},\max(dp_{l+1,r},dp_{l,r-1}))$$

这合理吗，这十分合理。这个算法的时间复杂度是 $O(n^2)$ ，可以通过

#### 代码时间（实在不会在看）

```
#include<bits/stdc++.h>
#define int long long
#define MAXN 5001
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar(); 
	}
	return x*f;
}
int n,a[MAXN],f[MAXN][MAXN];
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		f[i][i]=a[i];
	for(int len=2;len<=n;len++)
		for(int l=1,r=len;r<=n;l++,r++)
			f[l][r]=f[l][r-1]^f[l+1][r];
	for(int len=2;len<=n;len++)
		for(int l=1,r=len;r<=n;l++,r++)
			f[l][r]=max(f[l][r],max(f[l][r-1],f[l+1][r]));
	int T=read();
	while(T--){
		int l=read(),r=read();
		cout<<f[l][r]<<endl;
	}
	return 0;
}
```


---

## 作者：Law_Aias (赞：1)

# <center>CF 983B 序列函数

## 题意:
　　给你一段序列，求出它们的最大异或和。
## 解法：
#### 其实这道题并不很难，但读题上可能会有困难。
> 其实样例我是用**Python 3**才看懂的。。。emmm

递归思想，令dp[0][i] = a[i]，令dp[i][j] 为 第i层递归的第j个连续（i+1）个数的 f() 值，则再将dp[i][j] 更新为 dp[i][j], dp[i-1][j] 、dp[i-1][j-1] 的最大值。则查找 l~r 的最大值时，只需要输出 dp[r-l][l-1] 即可。

## CODE :
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;
const int N = 5100;

int m,n,a[N];
int xor_sum[N][N];

void work_first() {
	for(int i = 2 ; i <= n ; i++) {
		for(int j = i ; j <= n ; j++) {
			xor_sum[i][j] = xor_sum[i - 1][j - 1] ^ xor_sum[i - 1][j];
		}
	}
	for(int i = 1 ; i <= n ; i++) {
		for(int j = i ; j <= n ; j++) {
			int xor_num = max(xor_sum[i - 1][j - 1] , xor_sum[i - 1][j]);
			xor_sum[i][j] = max(xor_sum[i][j] , xor_num);
		}
	}
}
void check_them() {
	scanf("%d",&m);
	for(int i = 1 ; i <= m ; i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		int ans = xor_sum[r - l + 1][r];
		printf("%d\n",ans);
	}
}

int main() {
	freopen("function.in","r",stdin);
	freopen("function.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",&a[i]);
		xor_sum[1][i] = a[i];
	}
	work_first();//预处理
	check_them();//查询
	return 0;
}

```

---

## 作者：大菜鸡fks (赞：1)

主要就是f[l][r]=f[l][r-1]^f[l+1][r]

然后就是一个前缀最大和的东西了

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5005;
int a[N],n;
inline void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
}
int f[N][N],dp[N][N];
inline void DP(){
	for (int i=1;i<=n;i++){
		dp[i][i]=f[i][i]=a[i];
	}
	for (int L=2;L<=n;L++){
		for (int i=1;i+L-1<=n;i++){
			f[i][i+L-1]=f[i][i+L-2]^f[i+1][i+L-1];
		}
	}
	for (int L=2;L<=n;L++){
		for (int i=1;i+L-1<=n;i++){
			dp[i][i+L-1]=max(f[i][i+L-1],max(dp[i][i+L-2],dp[i+1][i+L-1]));
		}
	}
}
int q;
inline void solve(){
	DP();
	scanf("%d",&q);
	for (int i=1;i<=q;i++){
		int l,r; scanf("%d%d",&l,&r);
		printf("%d\n",dp[l][r]);
	}
}
int main(){
	init(); 
	solve();
	return 0;
} 
```



---

## 作者：_Lazy_zhr_ (赞：0)

略微思考即可发现这是一道区间 dp。

我们定义 $val_{i,k}$ 表示从第 $i$ 个数开始到第 $i+k$ 个数结束（包括他们自身）所成的数组的 $f$ 值，$dp_{i,k}$ 表示从第 $i$ 个数开始到第 $i+k$ 个数结束（包括他们自身）所成的数组以及它的子数组中最大的 $f$ 值。

$val$ 的转移方程是 $val_{i,k}=val_{i,k-1}\oplus val_{i+1,k-1}$。$dp$ 的转移方程是 $dp_{i,k}=\max(val_{i,k},dp_{i,k-1},dp_{i+1,k-1})$。

代码如下：

```cpp
#define int long long
int n,q,val[5005][5005],dp[5005][5005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>val[i][0];
		dp[i][0]=val[i][0];
	}
	for(int k=1;k<n;k++) for(int i=1;i<=n-k;i++){
		val[i][k]=val[i][k-1]^val[i+1][k-1];
		dp[i][k]=max(val[i][k],max(dp[i][k-1],dp[i+1][k-1]));
	}
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<dp[l][r-l]<<"\n";
	}
}
```

---

## 作者：lwwwb_555 (赞：0)

~~这能有蓝？~~
# 题解
先手玩一下，比如：
$$f(a_1,a_2,a_3)=f(a_1 \oplus a_2,a_2\oplus a_3)=f(a_1\oplus a_3)$$
$$f(a_1,a_2,a_3,a_4)=f(a_1 \oplus a_2,a_2\oplus a_3,a_3\oplus a_4)=f(a_1\oplus a_3,a_2\oplus a_4)$$

我们惊奇的发现 $a_1\oplus a_3=f(a_1,a_2,a_3)$，$a_2\oplus a_4=f(a_2,a_3,a_4)$。

我们设 $g_{l,r}$ 表示区间 $l$ 到 $r$ 的函数值，于是就有 $g_{l,r}=g_{l,r-1}\oplus g_{l+1,r}$ 这个是可以 $O(n^2)$ 所有区间的的函数值。

我们再来想如何才能求得题目所要求的值呢？这也很容易想，在转移的时候我们对转移的两个值和自己的值取一个 $\max$ 就好了。

时间复杂度是 $O(n^2+m)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[5050],f[5050][5050],g[5050][5050];
int read(){
	int res=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		res=(res<<3)+(res<<1)+c-'0';
		c=getchar();
	}
	return res*f;
}//快读
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),f[i][i]=a[i],g[i][i]=a[i];
	for(int len=2;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			f[i][i+len-1]=(f[i][i+len-2]^f[i+1][i+len-1]);//求区间函数值
			g[i][i+len-1]=max(max(g[i][i+len-2],g[i+1][i+len-1]),f[i][i+len-1]);//对转移到这一位的两个函数值和自己的函数值取max
		}
	}
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		printf("%d\n",g[l][r]);
	}
	return 0;
} 
```

---

## 作者：RocksonLee (赞：0)

---
title: CF 983B XOR-pyramid    # 文章标题

## Problem

[Luogu](https://www.luogu.com.cn/problem/CF983B)

[Codeforces](https://codeforces.com/problemset/problem/983/B)

## Solution

由于异或允许结合律，所以我们对于一段数列，只需要递推得到即可。

设 $f[i][j]$ 为 第 $i$ 层的第 $j$ 个数，也可以说为 这是以第 $j$ 个数为结尾，长度为 $i$ 的异或和。

所以我们递推出 $f$ 然后在用 dp 求出 max 数组即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define il inline
#define INF 0x3f3f3f3f
#define cl(a, b) memset(a, b, sizeof(a))
typedef long long ll;
typedef unsigned long long ull;

#define N 5050

int n, q, f[N][N], maxn[N][N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &f[i][0]);
        maxn[i][0] = f[i][0];
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            f[j][i] = f[j][i - 1] ^ f[j + 1][i - 1];
            maxn[j][i] = max(f[j][i], max(maxn[j][i - 1], maxn[j + 1][i - 1]));
        }
    }
    scanf("%d", &q);
    for (int i = 1, l, r; i <= q; i++)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", maxn[l][r - l]);
    }
    return 0;
}
```


---

