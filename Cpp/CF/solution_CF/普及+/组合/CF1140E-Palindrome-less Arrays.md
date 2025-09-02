# Palindrome-less Arrays

## 题目描述

Let's denote that some array $ b $ is bad if it contains a subarray $ b_l, b_{l+1}, \dots, b_{r} $ of odd length more than $ 1 $ ( $ l < r $ and $ r - l + 1 $ is odd) such that $ \forall i \in \{0, 1, \dots, r - l\} $ $ b_{l + i} = b_{r - i} $ .

If an array is not bad, it is good.

Now you are given an array $ a_1, a_2, \dots, a_n $ . Some elements are replaced by $ -1 $ . Calculate the number of good arrays you can obtain by replacing each $ -1 $ with some integer from $ 1 $ to $ k $ .

Since the answer can be large, print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 3
-1 -1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5 2
1 -1 -1 1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5 3
1 -1 -1 1 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
4 200000
-1 -1 12345 -1
```

### 输出

```
735945883
```

# 题解

## 作者：Leap_Frog (赞：10)

### PS.
此题有一些细节有点毒瘤。  

### Problem.
见题目翻译，已经够简洁了，不再概括。  

### Solution.
首先，题目要求我们求有多少个不坏的串。  
串的好坏定义为一个串中是否有长度为奇数的回文子串。  

首先，我们考虑一下回文串的性质，瞪着串的好坏是做不出来题目的。  
我们发现，一个回文串中很显然有子回文串。  
这样不断递归，我们会得到长度为3的回文串。  
很显然，如果一个序列中有长度为3的回文串，那它肯定是坏的串（废话  
同时，如果一个串是坏的，那么它中肯定有一个长度超过3的回文串，那么它也肯定有一个长度为3的回文串。  
所以，我们证明了`有一个长度为3的回文子串`和`这个串是不好的`是充分必要条件。  

然后我们再来考虑如何表示一个串是否拥有长度为3的回文子串。  
首先，根据定义，一个长度为3的回文子串的开头和结尾相同，即$a_{i-1}=a_{i+1}$。  
所以如果一个串满足存在一个$i$，使得$a_{i-1}=a_{i+1}$，那么这个串就是坏的。  
那么我们很显然可以按照$i$的奇偶分别处理，最后把答案乘起来。  

然后，我们发现题目中有一个限制条件：$a_i=-1\;or\;1\le a_i\le k$。  
那么也就是说原序列中如果存在数，肯定是和$a_i$的范围是相同的。  
所以我们对于一段连续的$-1$序列，我们能发现区间左边的那个数和区间右边的那个数与这个$-1$序列的取值是无关的，有关的只有这两个数是否相同。  
一段连续的$-1$序列的方案数只与这个序列的长度和左右是否相同有关。  
那么很显然就考虑到dp。  

我们设$dp[i][0/1]$表示长度为$i$的连续$-1$序列在左右两边是否相同（0表示相同，1表示不相同）的情况下的方案数。  
那么很显然，我们可以枚举最后一位放什么，然后转移。  
则我们轻易地得到了状态转移方程式。  
$dp[i][0]=dp[i-1][1]\times(k-1)$  
$dp[i][1]=dp[i-1][1]\times(k-2)+dp[i-1][0]$  
初始状态便为$dp[0][0]=0,dp[0][1]=1$，这个很显然（长度都为0了。  

于是，笔者打出了这样的一份代码。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,P=998244353,ans,beg,dp[200005][2],a[200005],m=0,b[200005];
inline int ksm(int a,int q) {int r=1;for(;q;q>>=1,a=1ll*a*a%P) if(q&1) r=1ll*r*a%P;return r;}//快速幂
inline int wrk(int n,int a[])//分别处理奇偶位
{
	int ret=1;//返回值
	for(int i=1,j;i<=n;i=j+1)
	{
		while(i<=n&&a[i]!=-1) i++;j=i;//i找到第一个-1的位置
		while(j<=n&&a[j]==-1) j++;j--;//j找到最后一个-1的位置
		if(i>j) continue;//返回一次
		if(i==1&&j==n) ret=1ll*ret*ksm(k-1,n-1)%P*k%P;
//如果前后都没有限制，那也就是说第一格有k种放法，其他为了避免和上一个颜色相同有k-1种放法。
		else if(i==1||j==n) ret=1ll*(dp[j-i][0]+1ll*(k-1)*dp[j-i][1]%P)%P*ret%P;
//如果前后中有一个没有限制，那么没有限制那一边的颜色，可以推出上面的柿子
		else ret=1ll*ret*dp[j-i+1][a[i-1]!=a[j+1]]%P;
//否则直接套dp转移的结果
	}
	return ret;//返回答案
}
int main()
{
	scanf("%d%d",&n,&k),dp[0][0]=0,dp[0][1]=1,ans=1;//dp初始化
	for(int i=1;i<=n;i++) scanf("%d",a+i);//读入
	for(int i=1;i<=n;i++) dp[i][0]=1ll*dp[i-1][1]*(k-1)%P,dp[i][1]=(1ll*dp[i-1][1]*(k-2)%P+dp[i-1][0])%P;//dp转移
	for(int i=1;i<=n;i+=2) b[++m]=a[i];//把上面的序列按照奇偶分开分别处理
	ans=1ll*ans*wrk(m,b)%P,m=0;//ans乘上奇数的答案
	for(int i=2;i<=n;i+=2) b[++m]=a[i];//偶数
	return ans=1ll*ans*wrk(m,b)%P,printf("%d\n",ans),0;//ans乘上偶数的答案，输出ans
}
```
然后一交，woc怎么`Wrong Answer On 14`啊。。。  
我们发现，我们没有考虑一种情况，就是如果已经所有的数都放好了。  
而答案不符合，那么方案数应该是0，我们这个程序会跑出1，所以还要加个特判。  

### Coding.
AC代码如下（比楼上楼下的都短/cy
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,P=998244353,ans,beg,dp[200005][2],a[200005],m=0,b[200005];
inline int ksm(int a,int q) {int r=1;for(;q;q>>=1,a=1ll*a*a%P) if(q&1) r=1ll*r*a%P;return r%P;}
inline int wrk(int n,int a[])
{
	int ret=1;
	for(int i=1;i<n;i++) if(a[i]!=-1&&a[i]==a[i+1]) return 0;
//这就是我刚刚提到的特判
	for(int i=1,j;i<=n;i=j+1)
	{
		while(i<=n&&a[i]!=-1) i++;j=i;
		while(j<=n&&a[j]==-1) j++;j--;
		if(i>j||i<1||j>n) continue;
		else if(i==1&&j==n) ret=1ll*ret*ksm(k-1,n-1)%P*k%P;
		else if(i==1||j==n) ret=1ll*(dp[j-i][0]+1ll*(k-1)*dp[j-i][1]%P)%P*ret%P;
		else ret=1ll*ret*dp[j-i+1][a[i-1]!=a[j+1]]%P;
	}
	return ret;
}
signed main()
{
	scanf("%lld%lld",&n,&k),dp[0][0]=0,dp[0][1]=1,ans=1;
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	for(int i=1;i<=n;i++) dp[i][0]=1ll*dp[i-1][1]*(k-1)%P,dp[i][1]=(1ll*dp[i-1][1]*(k-2)%P+dp[i-1][0])%P;
	for(int i=1;i<=n;i+=2) b[++m]=a[i];
	ans=1ll*ans*wrk(m,b)%P,m=0;
	for(int i=2;i<=n;i+=2) b[++m]=a[i];
	return ans=1ll*ans*wrk(m,b)%P,printf("%lld\n",ans),0;
}
```
完结散花，无耻求赞

---

## 作者：Chaigidel (赞：10)

[Blog Link](https://blog.chaigidel.xyz/archives/%E9%A2%98%E8%A7%A3/Codeforces/CF1140E.html)

发现 $b$ 为坏的条件完全等价于 不存在长度为三的回文串，即 $a_i \neq a_{i+2}$，故考虑分奇偶处理，最后乘起来。

问题转换成 长度为 $n$ 的串，相邻数不能相等，方案有多少？

考虑分治

$a\neq b$，$f_{i,0/1}$ 表示中间 $-1$ 个数为 $i$，$1/0$ 表示两端数是否相等

- $a, -1, \dots, -1, b$ 有 $f_{i,0} = (k-2)f_{i-1,0}+f_{i-1,1}$
- $a, -1, \dots, -1, a$ 有 $f_{i,1} = (k-1)f_{i-1,0}$

特殊的 $f_{0,0} = 1, f_{0,1}=0$

最后还要考虑一些特殊情况

```cpp
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, l, r) for (int i = (l); i >= (r); --i)
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned int ui;

const int p = 998244353;

const int N = 201000;

#define mod(x) (x) %= 998244353

inline int mul(int x, int y) { return ((ll)x * y) % p; }
inline int add(int x, int y) { return ((ll)x + y) % p; }

int a[N], b[N], cnta, cntb;

int k, f[N][2];

int ksm(int a, int n) {
    int ret = 1;
    while (n) {
        if (n & 1) ret = mul(ret, a);
        a = mul(a, a);
        n >>= 1;
    }
    return ret;
}

int solve(int a[], int n) {
    if (n == 0) return 1;
    int l = 0, r = n - 1;
    int ret;
    for (; a[l] == -1 && l < n; l++)
        ;
    if (l == n) return mul(k, ksm(k - 1, n - 1));
    for (; a[r] == -1; --r)
        ;
    ret = mul(ksm(k - 1, l), ksm(k - 1, n - r - 1));
    int lst = l;
    for (l = lst + 1; l <= r; ++l) {
        if (a[l] == -1) continue;
        ret = mul(ret, f[l - lst - 1][a[lst] == a[l]]);
        lst = l;
    }
    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    cout.tie(0);
    int n;
    cin >> n >> k;

    f[0][0] = 1, f[0][1] = 0;
    rep(i, 1, n) {
        f[i][1] = mul(f[i - 1][0], k - 1);
        f[i][0] = add(mul(k - 2, f[i - 1][0]), f[i - 1][1]);
    }

    rep(i, 1, n) {
        if (i & 1)
            cin >> a[cnta++];
        else
            cin >> b[cntb++];
    }

    cout << mul(solve(a, cnta), solve(b, cntb));
    return 0;
}
```

---

## 作者：Rui_R (赞：7)

题意：若一个数组中存在长度为奇数的连续回文子串(长度>1)，他是坏的，否则是好的。

给出一个数组，其中$-1$可替换为$1$~$k$中的任何数

求其中可以替换后得到好数组的方案数，对998244353取模

[原题](https://www.luogu.com.cn/problem/CF1140E)

题目说存在长度为大于1的奇数的连续回文子串就是坏的，也就是说只要存在长度为3的奇数就是坏的

直接这么来看的话好像有点头疼啊，考虑转化的更方便些

我们注意到数组中**下标奇偶性不同**的数之间其实并无关联

那么，如果我们把原数组按其**下标的奇偶**分成两份，**好数组**的定义就成了：**数组中每一个数都不与其前一个数相同**

答案即为两份数组的合法方案数的积。

接下来考虑怎么求分组后的好数组个数：

首先，影响答案的只有不确定的数，即$-1$。那么，将每段连续的-1和其两端取值已经确定的数视作一段，并试着处理每段这样的数的方案数，最后相乘

显然每段的方案数和$-1$在哪里并没有关系。在深入思考，发现它的方案数跟它两端已确定的数的具体取值也基本没有关系。

和方案数有关的，只有 **$-1$ 的长度以及两端已确定的数是否相等**

试着递推预处理这个方案数：

$dp[i][0]$表示一段长为i的-1且其两端已确定的数取值不一致的方案数

$dp[i][1]$表示一段长为i的-1且其两端已确定的数取值一致的方案数

对于每个$dp[i][1]$:
![](https://cdn.luogu.com.cn/upload/image_hosting/c7s49vxd.png)

由于$a!=b$,$b$有$k-1$种取值

所以$dp[i][1]=dp[i-1][0]*(k-1)$;

而对于$dp[i][0]$:
![](https://cdn.luogu.com.cn/upload/image_hosting/7hlf2ngv.png)

由于$a!=c,b!=c$,$c$有$k-2$种取值

所以$dp[i][0]=dp[i-1][1]+(k-2)*dp[i-1][0];$

初始化，就是$dp[0][0]=1,dp[0][1]=0;$

剩下的，就是那些恶心的，烦人的细节了。具体请参见代码，加了注释，希望您能看懂。

$Code:$
```cpp
#include <cstdio>
#include <vector>

typedef long long ll;
const int maxn=2e5+5,mod=998244353;

int n,k,a[maxn];ll dp[maxn][2],ans=1;
std::vector<int> v1,v2;

ll count(std::vector<int> v){//计算其中一份数组的合法方案数
	ll res=1;
	for(int i=0;i<v.size();){
		int j;//下一个不为-1的位置
		if(v[i]==-1){//出现这种情况的唯一原因就是第一位为-1，原因见下
			for(j=i+1;v[j]==-1&&j<v.size();j++);//找到下一个不为-1的数，即得到一段连续的-1
			if(j==v.size()){//找到不能，也就是全是-1
				if(v.size()==1) return k;//要是就一个-1，那怎样都好，方案数就是k
				res=(dp[v.size()-2][0]*(k-1)+dp[v.size()-2][1])%mod;//否则计算
                //假设第一个点取值已固定，有(k-1)种可能是第一个点和最后一个点的值不同
                //还有一种可能是两个点相同
                res*=k;//由于第一个点有k种取值，还要乘k
                res%=mod;
                return res;
			}else{
				res*=(dp[j-1][0]*(k-1)+dp[j-1][1]);//已固定了一个点，也就是不用乘k，其余同上
                res%=mod;i=j;//将i转到下一个不为-1的位置
			}
		}else{//正常情况
			if(i==v.size()-1) return res;//如果已经是最后一位，直接返回
			for(j=i+1;v[j]==-1&&j<v.size();j++);//找到一段-1(i+1~j-1都是-1)
			if(j==v.size()){//找到不能
				res*=(dp[v.size()-i-2][0]*(k-1)+dp[v.size()-i-2][1])%mod;
				res%=mod;//也就是从i+1到结尾全是-1，处理方法与之前v[i]=-1是的第二种情况一致
			}else{//真正的正常情况
				if(v[i]==v[j]) res*=dp[j-i-1][1];//分类
				else res*=(dp[j-i-1][0]);//唯一正常而清爽的部分
				res%=mod;
			}
            i=j;//通过每次都将i转到不为-1的位置，保证了通常v[i]!=-1且不会漏点
            //而这也能在j=v.size()时结束循环
		}
	}return res;
}

int main(){
	scanf("%d%d",&n,&k);dp[0][1]=0,dp[0][0]=1;//初始化
	for(int i=1;i<=n;i++){
		dp[i][1]=dp[i-1][0]*(k-1);dp[i][1]%=mod;
		dp[i][0]=dp[i-1][1]+dp[i-1][0]*(k-2);dp[i][0]%=mod;
	}//预处理dp
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(i%2) v1.push_back(a[i]);//分组
		else v2.push_back(a[i]);
	}
	ans*=count(v1);ans%=mod;
	ans*=count(v2);ans%=mod;//计算
    printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Soulist (赞：5)

首先，一个回文串的内部还是一个回文串

所以不存在长度为奇数$\Longleftrightarrow$不存在长度为$3$的回文串。

进一步思考发现奇数位和偶数位彼此独立，所以可以单独提出来，就变成了相邻两位不相同的方案数，做完后要做个乘法。

朴素的$dp$是考虑记$dp_{i,k}$表示第$i$位为$k$的方案数，但这个显然会$T$得飞起。

发现实际上会影响到答案的只有一段连续的$-1$，所以我们可以对他们单独考虑。

发现不是$-1$的位置和值固定，可以变相的看作不会影响答案，于是做把很多段小的$-1$的答案算出来，做一个乘法原理好了。

考虑如何求解一段连续的$-1$的答案，进一步分析后发现对于一段$-1$，其两边的值是多少并不影响答案，有效的状态只有两边相等或者不相等两种。

于是可以考虑通过$dp$预处理出来长度为$i$的$-1$段两边相同$/$不相同的方案数。

我们设$dp_{i,0}$表示长度为$i$的$-1$段两边相同的方案数，$dp_{i,1}$为两边不同的方案数。

那么有转移：

> $dp_{i,0}=dp_{i-1,1}*(k-1)$

> $dp_{i,1}=dp_{i-1,1}*(k-2)+dp_{i-1,0}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 2e5 + 5 ; 
const int mod = 998244353 ; 
int n, k, a[N], num, b[N], dp[N][2], Ans ;
int solve() {
	int w = 1, len = 0, pre = 0 ; 
	rep( i, 1, num ) {
		if( b[i] == -1 ) ++ len ;
		else {
			if( len ) {
				if( !pre ) w = w * ( ( k - 1ll ) * dp[len - 1][1] % mod + dp[len - 1][0] ) % mod ;
				else if( pre == b[i] ) w = w * dp[len][0] % mod ; 
				else w = w * dp[len][1] % mod ;  
			} 
			pre = b[i], len = 0 ;
		}
	}
	if( len == num ) {
		w = k ;
		rep( i, 2, num ) w = ( w * ( k - 1ll ) ) % mod ; 
		return w % mod ; 
	} 
	if( len ) w = ( w * ( ( dp[len - 1][0] + ( k - 1ll ) * dp[len - 1][1] % mod ) % mod ) ) % mod  ;
	return w % mod ; 
}
signed main()
{
	n = read(), k = read() ;  
	rep( i, 1, n ) {
		a[i] = read() ; 
		if( i > 3 && a[i] == a[i - 2] && a[i] != -1 )
			puts("0"), exit(0) ; 
	}
	dp[0][0] = 0, dp[0][1] = 1 ; //0表示两边外相同，1表示不同 
	for( int i = 1; i <= n / 2 + 1; ++ i ) {
		dp[i][0] = ( dp[i - 1][1] * ( k - 1 ) ) % mod ;
		dp[i][1] = ( dp[i - 1][0] + ( ( k - 2 ) * dp[i - 1][1] % mod ) ) % mod ;
	}
	rep( i, 1, n ) if( i % 2 ) b[++ num] = a[i] ; 
	Ans = solve(), num = 0 ; 
	rep( i, 1, n ) if( i % 2 == 0 ) b[++ num] = a[i] ; 
	Ans *= solve(), Ans %= mod ; 
	printf("%d\n", Ans ) ;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：3)

看其他题解没有类似思路，故交一发。

本人思路与 [CF1591F](https://www.luogu.com.cn/problem/CF1591F) 类似，感兴趣的同学也可以去做做。

## 思路

容易发现，条件可以转化成 $a_i\not=a_{i+2}$，考虑分奇偶性处理。

考虑 $dp_{i,j}$ 表示看到第 $i$ 位，$a_i=j$ 的方案数。

转移 $dp_{i+2,j}=\sum_{k\not=j}dp_{i,k}$。若 $a_{i+2}\not=-1$，需要将除了 $dp_{i+2,a_{i+2}}$ 的值以外的 $dp$ 赋值为 $0$。

复杂度 $O(n^2)$，**无法**通过本题。

考虑优化，容易发现上面两个式子可以用区间加，区间乘，区间查询维护，故使用线段树维护即可，复杂度 $O(n\log n)$，可以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
const int p=998244353; 
struct vert{
	int num,mul,plu,size,tg;
};
int a[200005],b[200005];
struct sgt{
	vert f[2000005];
	void pushup(int now){
		f[now].num=(f[now*2].num+f[now*2+1].num)%p;
		f[now].size=f[now*2].size+f[now*2+1].size; 
	}
	void pushdown(int now){
		f[now*2].num=(f[now*2].num*f[now].mul+f[now].plu*f[now*2].size)%p;
		f[now*2+1].num=(f[now*2+1].num*f[now].mul+f[now].plu*f[now*2+1].size)%p;
		f[now*2].mul=(f[now*2].mul*f[now].mul)%p;
		f[now*2+1].mul=(f[now*2+1].mul*f[now].mul)%p;
		f[now*2].plu=(f[now*2].plu*f[now].mul+f[now].plu)%p;
		f[now*2+1].plu=(f[now*2+1].plu*f[now].mul+f[now].plu)%p;
		f[now].mul=1;
		f[now].plu=0;
	}
	void init(int now,int id){
		f[now].mul=1;
		f[now].plu=0;
		f[now].num=0;
		f[now].size=1;
	}
	void build(int now,int l,int r){
		if(l==r){
			init(now,l);
			return ; 
		}
		int mid=(l+r)>>1;
		f[now].mul=1;
		f[now].plu=0;
		build(now*2,l,mid);
		build(now*2+1,mid+1,r);
		pushup(now);
	}
	void modify1(int now,int l,int r,int ql,int qr,int mul1){
		if(ql<=l&&qr>=r){
			f[now].mul=(f[now].mul*mul1)%p;
			f[now].plu=(f[now].plu*mul1)%p;
			f[now].num=(f[now].num*mul1)%p;
			return ;
		}
		if(ql>r||qr<l) return ;
		pushdown(now);
		int mid=(l+r)>>1;
		modify1(now*2,l,mid,ql,qr,mul1);
		modify1(now*2+1,mid+1,r,ql,qr,mul1);
		pushup(now);
	}
	void modify2(int now,int l,int r,int ql,int qr,int plu1){
		if(ql<=l&&qr>=r){
			f[now].plu=(f[now].plu+plu1)%p;
			f[now].num=(f[now].num+plu1*f[now].size)%p;
			return ;
		}
		if(ql>r||qr<l) return ;
		pushdown(now);
		int mid=(l+r)>>1;
		modify2(now*2,l,mid,ql,qr,plu1);
		modify2(now*2+1,mid+1,r,ql,qr,plu1);
		pushup(now);
	}
	int qry(int now,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r) return f[now].num;
		if(ql>r||qr<l) return 0;
		pushdown(now);
		int mid=(l+r)>>1;
		return (qry(now*2,l,mid,ql,qr)+qry(now*2+1,mid+1,r,ql,qr))%p;
	}
}tree;
signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	tree.build(1,1,k);
	if(a[1]==-1){
		tree.modify2(1,1,k,1,k,1);
	}
	else{
		tree.modify2(1,1,k,a[1],a[1],1);
	}
	for(int i=3;i<=n;i+=2){
		int sum=tree.qry(1,1,k,1,k);
		tree.modify1(1,1,k,1,k,p-1);
		tree.modify2(1,1,k,1,k,sum);
		if(a[i]!=-1){
			sum=tree.qry(1,1,k,a[i],a[i]);
			tree.modify1(1,1,k,1,k,0);
			tree.modify2(1,1,k,a[i],a[i],sum);
		}
	}
	int ans=tree.qry(1,1,k,1,k);
	tree.build(1,1,k);
	if(a[2]==-1){
		tree.modify2(1,1,k,1,k,1);
	}
	else{
		tree.modify2(1,1,k,a[2],a[2],1);
	}
	for(int i=4;i<=n;i+=2){
		int sum=tree.qry(1,1,k,1,k);
		tree.modify1(1,1,k,1,k,p-1);
		tree.modify2(1,1,k,1,k,sum);
		if(a[i]!=-1){
			sum=tree.qry(1,1,k,a[i],a[i]);
			tree.modify1(1,1,k,1,k,0);
			tree.modify2(1,1,k,a[i],a[i],sum);
		}
	}
	ans=ans*tree.qry(1,1,k,1,k)%p;
	cout<<ans;
	return 0;
}
```

---

## 作者：duyi (赞：2)

## 题解 CF1140E Palindrome-less Arrays

发现【不存在长度大于$1$的奇回文串】，等价于【不存在长度为$3$的回文串】。

于是问题转化为对所有$i\geq 3$，$a_i\neq a_{i-2}$。也就是所有距离为$2$的两个位置，值都不相等。

可以发现，下标为奇数的位置和偶数的位置是互不影响的，考虑分别处理，然后把方案数乘起来。

以奇数为例。找到一个奇数位置$i$，满足$a_i=-1$且$a_{i-2}\neq -1$（也就是$i$是一段连续$-1$的开头），再找到最大的$j$，满足$j$也是奇数，且$a_{i},a_{i+2},\dots,a_{j}$都等于$-1$（也就是$j$是这段连续的$-1$的结尾）。对于每一段这样的“连续”的$-1$，它们对答案的贡献显然也是独立的，可以分别计算，然后乘起来。这里“连续”打引号，因为它们之间其实是间隔着一个偶数的，但如果只考虑奇数，它们就是连续的。

对一段“连续”的$-1$，在填好以后，相邻的两个数必须不相等，并且第一个数不能等于它前面的那个数（$a_i\neq a_{i-2}$），最后一个数不能等于它后面的那个数（$a_{j}\neq a_{j+2}$）。但也有特例，就是$i-2<1$或$j+2>n$时，最前面或最后面的那个数，可以不受限制。

具体来说，可以把一段“连续”的$-1$分为四类：

1. 左右都没有限制（$i-2<1$且$j+2>n$）。
2. 左右其中一边有限制（$i-2<1$或$j+2>n$，恰有一者成立）。
3. 左右都有限制，限制相同（$a_{i-2}=a_{j+2}$）。
4. 左右都有限制，限制不同（$a_{i-2}\neq a_{j+2}$）。

对于每种情况、每种长度的连续段，其方案数可以分别预处理出来，时间复杂度是$O(n)$的。例如，第四种情况最为复杂，是做一个DP：$dp[x][y\in\{0,1,2\}]$表示考虑了前$x$个位置，第$x$个位置的值，是等于左边的限制（$a_{i-2}$）还是等于右边的限制（$a_{j+2}$），还是两个都不等于。具体的转移可以见代码。

时间复杂度$O(n)$。

参考代码：

```cpp
//problem:CF1140E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MOD=998244353;
inline int mod1(int x){return x<MOD?x:x-MOD;}
inline int mod2(int x){return x<0?x+MOD:x;}
inline void add(int& x,int y){x=mod1(x+y);}
inline void sub(int& x,int y){x=mod2(x-y);}
inline int pow_mod(int x,int i){int y=1;while(i){if(i&1)y=(ll)y*x%MOD;x=(ll)x*x%MOD;i>>=1;}return y;}

const int MAXN=2e5;
int n,K,a[MAXN+5];
int f[4][MAXN+5],dp[MAXN+5][3];
/*
4种情况:
0. 左右都没有限制
1. 左右其中一边有限制
2. 左右都有限制,限制相同
3. 左右都有限制,限制不同
*/
void init(int maxlen){
	f[0][1]=K;
	for(int i=2;i<=maxlen;++i)
		f[0][i]=(ll)f[0][i-1]*(K-1)%MOD;
	f[1][1]=K-1;
	for(int i=2;i<=maxlen;++i)
		f[1][i]=(ll)f[1][i-1]*(K-1)%MOD;
	
	dp[1][0]=K-1;
	dp[1][1]=0;
	f[2][1]=K-1;
	for(int i=2;i<=maxlen;++i){
		dp[i][0]=((ll)dp[i-1][0]*(K-2) + (ll)dp[i-1][1]*(K-1))%MOD;
		dp[i][1]=dp[i-1][0];
		f[2][i]=dp[i][0];
	}
	
	dp[1][0]=K-2;
	dp[1][1]=0;
	dp[1][2]=1;
	f[3][1]=K-2;
	for(int i=2;i<=maxlen;++i){
		dp[i][0]=((K>3?(ll)dp[i-1][0]*(K-3):0LL) + (ll)dp[i-1][1]*(K-2) + (ll)dp[i-1][2]*(K-2))%MOD;
		dp[i][1]=mod1(dp[i-1][0]+dp[i-1][2]);
		dp[i][2]=mod1(dp[i-1][0]+dp[i-1][1]);
		f[3][i]=mod1(dp[i][0]+dp[i][1]);
	}
}
int main() {
	cin>>n>>K;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i+2<=n;++i){
		if(a[i]!=-1 && a[i]==a[i+2]){
			cout<<0<<endl;
			return 0;
		}
	}
	
	init((n+1)/2);
	int ans=1;
	for(int i=1;i<=n;i+=2){
		if(a[i]!=-1)
			continue;
		int j=i,len=1;
		while(j+2<=n && a[j+2]==-1){
			j+=2;
			len++;
		}
		int t=-1;
		if(i-2<1 && j+2>n)
			t=0;
		else if(i-2<1 || j+2>n)
			t=1;
		else if(a[i-2]==a[j+2])
			t=2;
		else
			t=3;
//		cout<<len<<" "<<t<<endl;
//		cout<<f[t][len]<<endl;
		ans=(ll)ans*f[t][len]%MOD;
		i=j;
	}
	for(int i=2;i<=n;i+=2){
		if(a[i]!=-1)
			continue;
		int j=i,len=1;
		while(j+2<=n && a[j+2]==-1){
			j+=2;
			len++;
		}
		int t=-1;
		if(i-2<1 && j+2>n)
			t=0;
		else if(i-2<1 || j+2>n)
			t=1;
		else if(a[i-2]==a[j+2])
			t=2;
		else
			t=3;
//		cout<<len<<" "<<t<<endl;
//		cout<<f[t][len]<<endl;
		ans=(ll)ans*f[t][len]%MOD;
		i=j;
	}
	cout<<ans<<endl;
	return 0;
}
```







---

## 作者：DPair (赞：1)

## 【前言】
本题解解法似乎与其他题解相似，但写法上更为清晰，思路也略有不同，个人感觉**超详细**，并且也许能回答部分同学的问题，希望管理员能通过，也希望能为其他同学们带来一些帮助。

## 【问题转化】

根据题意，我们不难发现本题中只有可以被我们人为改变的$-1$会对答案产生影响，因此我们认识到我们的思路要往$-1$上去靠拢。不难发现，在没有限制条件的情况下，每一个$-1$都有$k$种取值，可以考虑用组合的方法去思考。

下面考虑限制条件。

根据题意，数组中不能出现长度为奇数的连续回文串，而实际上，一旦出现了长度为奇数的回文串，就意味着必然出现了一个长度为$3$的回文串，且若这个长度为$3$的回文串没有出现，那么长度为其他奇数的回文串必然不会出现，因为一切长度大于$3$的奇数长回文串都必然从其对称轴开始包含一个长度恰为$3$的回文串。

由于不能让长度为$3$的回文串出现，而回文串对称轴上的那一个数又对是否回文的限制条件没有影响，那么我们对于每$3$个连着的数$a_{i-1},a_{i}a_{i+1}$，只需要考虑$a_{i-1}$与$a_{i+1}$的异同情况即可。

因此我们发现，每**一对**相隔一个数的数，都要保证它们是不同的，即下标**都为奇数**的**相邻**的数，与下标**都为偶数**的**相邻**的数，必须要保证不同。

因此我们考虑奇数偶数分开处理。

由此，问题转化为了**对于一个数列，其中-1可以替换为1到k的任意整数，问使其相邻两位互不相同的方案数**

## 【问题简化】

我们首先可以发现，每一段连续的$-1$对其他连续的$-1$段不会产生影响，原因在于一个数只可能影响其**相邻**的数，而**非**$-1$的数本身就不会改变，可以看作这些数**切割**了$-1$构成的序列。

那么为了使问题简化，考虑将$-1$段全部**分别**提取出来。形成多个新的且完全为$-1$的$-1$段。

但是，考虑到每一个$-1$段两端的数会影响这个$-1$段，由于本题只考虑异同情况，所以两端数的具体数值对答案没有影响，只需记录两端数的异同关系即可，并且由于这些$-1$段完全为$-1$，我们只需要记录这些段的长度即可。

## 【问题分类】

下面对于每一个被分离出来的$-1$段进行求解。

首先不难发现这些$-1$段可以分为$4$类：

1、两端都有数，且这两数不同

2、两端都有数，且这两数相同

3、两端只有一端有数（自然不用考虑异同，毕竟另一边连数都没有）

4、两端都没有其他数

不难发现，其中$3,4$两种情况只可能出现在一开始我们切割时的**段首**或**段尾**，因此切割可以这么实现：

```cpp
vector <pi> v;//type = 2(both side, same), type = 3(both side, different), type = 1(one side empty), type = 0(both side empty)

inline void init(int st){//st = 1时处理奇数，st=2时处理偶数
    int cnt = 0, l = 0;//cnt记录该段-1数，l记录该段左侧的数（为0则为空）
    for (register int i = st;i <= n;i += 2){
        if(~a[i]){//如果不为-1，（~(-1)=0）
            if(cnt){
                if(!l) v.push_back(make_pair(cnt, 1));//左侧为空，且右侧被记录到，只有一边有数
                else{
                    if(l ^ a[i]) v.push_back(make_pair(cnt, 3));//不相同
                    else v.push_back(make_pair(cnt, 2)); //相同
                }
                cnt = 0;//清空找下一段
            }
            l = a[i];
        }
        else cnt ++;
    }
    if(cnt){//扫描到最后，如果最后一段没有被清空，那么说明这一段右侧没有数
        if(!l) v.push_back(make_pair(cnt, 0));//两侧都没有数
        else v.push_back(make_pair(cnt, 1));//左侧有数，右侧没有
    }
}
```

复杂度显然$O(n)$

## 【问题求解】

处理完所有细节，开始考虑解决问题。

首先处理问题$1,2$。

仔细一想，诶？这不就是一个裸的$DP$吗？

容易想到设置状态$dp[i][0/1]$表示长度为$i$的$-1$串，$0$两侧相同，$1$两侧不同的方法数。

转移方程也容易考虑：
$$
dp[i][0] = (k - 1) * dp[i - 1][1]
 \\dp[i][1] = (k - 2) * dp[i - 1][1] + dp[i - 1][0]
$$
证明也容易，若该段两侧相同，则第$i$个能取的必然不与该段左侧相同，故这一位有$k-1$种取法，且必然使前$i-1$位两侧不同，故$dp[i][0] = (k - 1) * dp[i - 1][1]$

而若两侧不同，则第$i$项有$k-2$种**与左侧不同**的取法，且有$1$种**与左侧相同**的取法，故$dp[i][1] = (k - 2) * dp[i - 1][1] + dp[i - 1][0]$

由此解决了问题$1,2$。

接下来考虑问题$3,4$，发现它们完全可以由$1,2$转化而来，十分方便。

首先对于问题$3$，特判其长度为$1$的情况，此情况下答案显然为$k-1$，其他情况下，**不受影响可以自由取**的那一个$-1$可以看作一个常数，同样分类讨论是否与另一侧相同。易得有$k-1$种与另一侧不同，有$1$种与另一侧相同，设其长度为$len$，则答案显然为$(k-1)*dp[len-1][1]+dp[len-1][0]$，由此完成了问题$3$的转化。

再用相似的方法考虑问题$4$，用相同的思路，讨论其**两端**$-1$的情况，也因此要特判$len=1$与$len=2$的情况，$len=1$时显然答案为$k$，$len=2$时显然乘法原理答案为$k*(k-1)$，这里不多赘述了，考虑取一侧的$-1$有$k$种取值，然后就发现剩下的$len-1$个数成为了一个问题$3$，然后就能轻易得出答案$k * ((k-1)*dp[len-2][1]+dp[len-2][0])$

然后分类讨论即可，可见这一部分处理是$O(1)$的，算上总段数复杂度$O(n)$，而$DP$与预处理复杂度也是$O(n)$的，所以总复杂度$O(n)$，可以通过本题。

## 【思路超清晰de代码】

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef unsigned int UI;
typedef pair <int, int> pi;
#define MOD 998244353
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
//不要在意上面的快读快输
int n, a[200010];
LL k;
vector <pi> v;//type = 2(both side, same), type = 3(both side, different), type = 1(one side empty), type = 0(both side empty)

inline void init(int st){//st = 1时处理奇数，st=2时处理偶数
    int cnt = 0, l = 0;//cnt记录该段-1数，l记录该段左侧的数（为0则为空）
    for (register int i = st;i <= n;i += 2){
        if(~a[i]){//如果不为-1，（~(-1)=0）
            if(cnt){
                if(!l) v.push_back(make_pair(cnt, 1));//左侧为空，且右侧被记录到，只有一边有数
                else{
                    if(l ^ a[i]) v.push_back(make_pair(cnt, 3));//不相同
                    else v.push_back(make_pair(cnt, 2)); //相同
                }
                cnt = 0;//清空找下一段
            }
            l = a[i];
        }
        else cnt ++;
    }
    if(cnt){//扫描到最后，如果最后一段没有被清空，那么说明这一段右侧没有数
        if(!l) v.push_back(make_pair(cnt, 0));//两侧都没有数
        else v.push_back(make_pair(cnt, 1));//左侧有数，右侧没有
    }
}
LL dp[100010][2];//dp数组，具体上面有讲
LL ans = 1;
inline void DP(){
    dp[1][0] = k - 1;
    dp[1][1] = k - 2;
    for (register int i = 2;i <= (n >> 1) + 1;i ++){//由于分成了奇数偶数，长度顶多一半
        dp[i][0] = ((k - 1) * dp[i - 1][1]) % MOD;
        dp[i][1] = (((k - 2) * dp[i - 1][1]) % MOD + dp[i - 1][0]) % MOD;
    }
}

inline void work(int len, int type){//处理4类问题
    if(type >= 2) ans = (ans * dp[len][type & 1]) % MOD;//两边都有
    if(type == 1){//只有一边有
        if(len == 1) ans = (ans * (k - 1)) % MOD;
        else ans = (ans * ((((k - 1) * dp[len - 1][1]) % MOD + dp[len - 1][0]) % MOD)) % MOD;
    }
    if(type == 0){//两边都没有
        if(len == 1) ans = (ans * k) % MOD;
        else if(len == 2) ans = (ans * ((k * (k - 1)) % MOD)) % MOD;
        else ans = (ans * (k * (((k - 1) * dp[len - 2][1] + dp[len - 2][0]) % MOD) % MOD) % MOD) % MOD;
    }
}

int main(){
    read(n);read(k);
    for (register int i = 1;i <= n;i ++){
        read(a[i]);
        if(a[i] > 0 && i > 2 && a[i - 2] == a[i]){直接判断原数组是否有奇数长度的回文串，若有则直接无解输出0
            printf("0\n");
            return 0;
        }
    }
    init(1);init(2);DP();//预处理加DP（是不是超清晰？）
    for (register int i = 0;i < v.size();i ++) work(v[i].first, v[i].second);//每一段处理一次
    fprint(ans);putchar(10);
    return 0;
}
```

---

## 作者：t162 (赞：0)

一个序列是好的当且仅当不存在一个 $i$ 使得 $b_i=b_{i-2}$。

将数组按照奇偶性分类，问题变成了序列中已经有一部分被确定，要确定未确定的部分，使得序列相邻两项不相等的方案数。

如果这个序列中没有被确定的数，那么设这个序列的长度是 $l$，答案是 $k(k-1)^{l-1}$。

一个序列中已经确定的数会把序列分成若干段，每段都是独立的。开头和结尾的段可以直接算，如果段长是 $l$（不包含已经被确定的数）答案就是 $(k-1)^l$。

否则，设 $f(s,t,l)$ 表示段开头的数被指定为 $s$，结尾的数被指定为 $t$，段长为 $l$（包含两个被确定的数）。

那么这一段中可能存在 $l-1$ 个相等的两个相邻数，对这些相邻数设集合表示两个数相等的所有方案，答案就是被这些集合包含恰好 $0$ 次的元素个数。

设 $f(i)$ 表示任意钦定 $i$ 对相邻数相等的方案数的和，那么 $f(l-1)=[s=t]$，$f(l-2)=l-1$，其余的 $f(i)=\binom{l-1}{i}k^{l-2-i}$，直接二项式反演即可。

总时间复杂度 $\mathcal O(n)$。

```cpp
// Author: e3c8f1a924   Time: 2022年08月12日 星期五 09时07分53秒
#include<cstdio>
constexpr const int p = 998244353;
constexpr int maintain(int x) { return x >= p ? x - p : x; }
constexpr int plus(int x, int y) { return maintain(x + y); }
constexpr int minus(int x, int y) { return maintain(x - y + p); }
constexpr int mul(int x, int y) { return 1ll * x * y % p; }
int fac[200005], ifac[200005];
int C(int x, int y) { return mul(fac[x], mul(ifac[y], ifac[x - y])); }
int a[2][200005], f[200005], k[200005], K[200005], n;
int F(int s, int t, int l) {
	if (l == 2) return (s != t);
	f[l - 1] = (s == t), f[l - 2] = l - 1;
	for (int i = 0; i < l - 2; i++) f[i] = mul(C(l - 1, i), k[l - 2 - i]);
	int ret = 0;
	for (int i = 0; i <= l - 1; i++) {
		if (i & 1) ret = minus(ret, f[i]);
		else ret = plus(ret, f[i]);
	}
	return ret;
}
int main() {
	fac[0] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= 200000; i++) ifac[i] = mul(p - p / i, ifac[p % i]);
	for (int i = 2; i <= 200000; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int i = 1; i <= 200000; i++) fac[i] = mul(fac[i - 1], i);
	scanf("%d%d", &n, k + 1), k[0] = K[0] = 1;
	for (int i = 2; i <= n; i++) k[i] = mul(k[i - 1], k[1]);
	for (int i = 1; i <= n; i++) K[i] = mul(K[i - 1], k[1] - 1);
	for (int i = 1; i <= n; i++) scanf("%d", a[i % 2] + (i + 1) / 2);
	int ans = 1;
	for (int d = 0; d < 2; d++) {
		if (!(n + d) / 2) continue;
		int lst = 0;
		for (int i = 1; i <= (n + d) / 2; i++) {
			if (a[d][i] == -1) continue;
			if (lst == 0) ans = mul(ans, K[i - 1]);
			else ans = mul(ans, F(a[d][lst], a[d][i], i - lst + 1));
			lst = i;
		}
		if (lst == 0) ans = mul(ans, mul(k[1], K[(n + d) / 2 - 1]));
		else ans = mul(ans, K[(n + d) / 2 - lst]);
	}
	printf("%d\n", ans);
}
```

---

