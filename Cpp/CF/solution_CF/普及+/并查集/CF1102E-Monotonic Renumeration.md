# Monotonic Renumeration

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. Let's denote monotonic renumeration of array $ a $ as an array $ b $ consisting of $ n $ integers such that all of the following conditions are met:

- $ b_1 = 0 $ ;
- for every pair of indices $ i $ and $ j $ such that $ 1 \le i, j \le n $ , if $ a_i = a_j $ , then $ b_i = b_j $ (note that if $ a_i \ne a_j $ , it is still possible that $ b_i = b_j $ );
- for every index $ i \in [1, n - 1] $ either $ b_i = b_{i + 1} $ or $ b_i + 1 = b_{i + 1} $ .

For example, if $ a = [1, 2, 1, 2, 3] $ , then two possible monotonic renumerations of $ a $ are $ b = [0, 0, 0, 0, 0] $ and $ b = [0, 0, 0, 0, 1] $ .

Your task is to calculate the number of different monotonic renumerations of $ a $ . The answer may be large, so print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
5
1 2 1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
100 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
1 3 3 7
```

### 输出

```
4
```

# 题解

## 作者：云浅知处 (赞：4)

这题还是需要思考一会的。

[更好的阅读体验？](https://www.luogu.com.cn/blog/wwwluogucn/solution-cf1102e)
***
$1.$初步思路

首先，由第三个条件$b_{i+1}=b_i$或$b_{i+1}=b_i+1$，我们可以知道：$b_{i+1}\geqslant b_i$

所以，这个数列一定是**升序排列**的！

再回过头来看第二个条件：如果$a_i=a_j$，则$b_i=b_j$。

那么，在一个升序排列的数列中，有两个数相等，会发生什么呢？**这两个数之间的所有数都相等！**

假设$b_i,b_j$之间有一个数$b_k$不与它们相等。

那么，如果$b_k>b_i$，又因为$b_i=b_j$，所以$b_k>b_j$。

又因为$k<j$，所以$b_k\leqslant b_j$，矛盾。

同理可证$b_k<b_j$一样不可能。

所以，如果$b_i=b_j$，那么一定有$b_i=b_{i+1}=b_{i+2}=\cdots=b_{j-1}=b_j$。

也就是说，如果$a_i=a_j$，那么区间$[b_i,b_j]$中的每一个数都只有一种可能的情况。

换言之，它们都随着$b_i$的改变而改变，所以它们只有一种可能的情况。

进一步，如果有两个重叠的区间，那么这两个区间中的每一个数应该都是相等的。

即如果$a_i=a_j,a_n=a_m$，且$i<n<j<m$（保证是重叠的），那么必有$b_i=b_{i+1}=\cdots=b_{m-1}=b_{m}$。

则此时我们就可以把区间$[b_i,b_j]$与区间$[b_n,b_m]$看作一个区间$[b_i,b_m]$。

比如样例，$a_1=a_3,a_2=a_4$，则$b_1=b_2=b_3=b_4$。

再回过头来看题，我们可以发现，我们只需要统计出那些可以$+1$的位置的数量$t$，则 $2^t$ 就是最终答案，因为可以$+1$就意味着这个位置有两种可能的情况。
***
$2.$实现思路

大致思路就是先输入，然后从后往前扫一遍记录下每个数最后出现的位置$r$，然后再从前往后扫一遍，途中不断更新$r$即可。

至于快速幂取余，可以去看[P1226 【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)
***
至于代码，就不贴了。在明白了以上知识之后，写出一篇AC代码是很容易的啦～ ~~（逃~~

$\text{The end.}$

---

## 作者：Crazyouth (赞：1)

## 分析

这么一眼的线段树为什么没人写。注意到两个相同 $a$ 值间的 $b$ 值一定全都相等，那么我们就可以对每个 $a$ 值处理出它最后出现的位置，并将 $x$ 最后出现的位置记为 $pos_x$，那么我们只需要从 $1$ 到 $n$ 扫一遍，到 $i$ 的时候把 $i\sim pos_{a_i}$ 都染上和 $i$ 相同的颜色（特别地，如果 $i$ 没有染过色，那么创建一种新的颜色）。最后答案为 $2^{col}$，$col$ 表示一共用了的颜色数量。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int N=200010;
map<int,int> pos[2];
int lz[N<<2],sum[N<<2];
int a[N];
void upd(int l,int r,int s,int t,int p,int k)
{
	if(l<=s&&t<=r)
	{
		lz[p]=k;
		sum[p]=((t-s+1)*k);
		return;
	}
	int m=s+t>>1;
	if(lz[p])
	{
		lz[p<<1]=lz[p];
		lz[p<<1|1]=lz[p];
		sum[p<<1]=((m-s+1)*lz[p]);
		sum[p<<1|1]=((t-m)*lz[p]);
		lz[p]=0;
	}
	if(l<=m) upd(l,r,s,m,p<<1,k);
	if(r>m) upd(l,r,m+1,t,p<<1|1,k);
	sum[p]=sum[p<<1]+sum[p<<1|1];
}
int qry(int k,int s,int t,int p)
{
	if(k==s&&s==t) return sum[p];
	int m=s+t>>1;
	if(lz[p])
	{
		lz[p<<1]=lz[p];
		lz[p<<1|1]=lz[p];
		sum[p<<1]=((m-s+1)*lz[p]);
		sum[p<<1|1]=((t-m)*lz[p]);
		lz[p]=0;
	}
	if(k<=m) return qry(k,s,m,p<<1);
	else return qry(k,m+1,t,p<<1|1);
	sum[p]=sum[p<<1]+sum[p<<1|1];
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(!pos[0][a[i]]) pos[0][a[i]]=i;
		pos[1][a[i]]=i;
	}
	int colcnt=0;
	for(int i=1;i<=n;i++)
	{
		if(!qry(i,1,n,1)) upd(i,pos[1][a[i]],1,n,1,++colcnt);
		else upd(i,pos[1][a[i]],1,n,1,qry(i,1,n,1));
	}
	int ans=1;
	for(int i=1;i<colcnt;i++) ans=(ans<<1)%mod;
	cout<<ans;
}

---

## 作者：wangyibo201026 (赞：0)

## 一道好题

首先，从题目三个条件中寻找突破口。

题目说明 $b_{i + 1}$ 只可能等于 $b_i + 1$ 或者 $b_i$，并且 $a_i = a_j$ 时，$b_i = b_j$，则对于两个相同的数 $a_i, a_j(i \leq j)$，肯定 $b_i = b_{i + 1} = \cdots = b_{j - 1} = b_j$，可以自己想一下为什么。

然后，就可以将序列 $a$ 分为很多个区间，此时这些区间里的数只有两种状态，自己也可以想一下是怎么一回事。

但是这很多个区间有可能是交叉的，比如说以下样例：

```
5
1 2 1 3 2
```

此时，第一个区间为 $(1, 3)$ (注：第一个数代表左端点，第二个数代表右端点)，第二个区间为 $(2, 4)$，明显有交叉部分。

在这里，我们可以利用并查集来合并区间，但是这种方法过于复杂，我们可以利用一种更为简洁的方法来合并，提供算法流程：

1. 把所有的区间按照上述方法存进数组。

2. 把数组按照左端点的大小排序。

3. 如果当前的左端点小于之前的最大右端点（因为右端点没有排序），就合并上一个和当前的区间。

4. 如果违反流程 $3$，则计数器加加，表示区间加一个。

然后，区间（互不交叉）的数量就成功的统计完了，但需要注意的是：

1. 由于 $a_i \leq 10^9$，所以数组不可能开的下这么大，要使用 map。

2. 注意计数器初始化为 $1$，自己想想为什么。

然后，知道了有多少个区间（默认互不交叉，默认有 $cnt$ 个区间），就需要用到数学思维：

每个区间都有两种选择（前面的加强版），因为根据第二条规则。所以本来答案应该是 $2^{cnt}$，但是 $b_1 = 0$，所以有一个区间只有一种选择，则答案为 $2^{cnt - 1}$。

请注意取模。

至于次方怎么求，请学习快速幂或者循环求次方，这里作者用得是快速幂（装逼）。

## 代码

代码来了：

```cpp
#include<bits/stdc++.h>
#define int long long   //由于可能会超一点点，所以开 long long

using namespace std;

const int mod = 998244353;   //常量

int n, a[200005], len, cnt = 1;
map<int, int> mini, maxi;

struct node{
  int l, r;
}c[200005];

int fastpow(int a, int b, int p){    //快速幂
  int ans = 1;
  while(b){
    if(b & 1){
      ans = a % p * ans % p % p;
    }
    b >>= 1;
    a = a % p * a % p % p;
  }
  return ans % p;
}

bool cmp(node x, node y){
  return x.l < y.l;
}

void Solve(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }
  for(int i = n; i >= 1; i--){
    if(maxi[a[i]] == 0){
      maxi[a[i]] = i;      //求数 a[i] 在序列里最晚出现在哪里
    }
  }
  for(int i = 1; i <= n; i++){
    if(mini[a[i]] == 0){
      mini[a[i]] = i;     //反之，求最早的
    }
  }
  for(int i = 1; i <= n; i++){
    c[++len].l = mini[a[i]];     //存到数组里
    c[len].r = maxi[a[i]];
  }
  sort(c + 1, c + 1 + n, cmp);
  int maxi = c[1].r;
  for(int i = 2; i <= n; i++){    //求有多少个区间
    if(c[i].l >= maxi){
      cnt++;
    }
    maxi = max(maxi, c[i].r);
  }
  cout << fastpow(2, cnt - 1, mod);    //输出
}

signed main(){
  Solve();
  return 0;
}
```

## 最后收尾

中间有些细节没讲，可以细细琢磨。

---

## 作者：xyf007 (赞：0)

### 如果发现$a_i=a_j$，那么$b_i=b_{i+1}=...=b_j$
### 所以问题转化成求有多少不相交的线段。
# 一定要开long long!!!
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
int n,a[200001];
map<int,int>r;//记录a[i]最后出现的位置
void checkmax(int &x,int y)
{
	if(x<y)
	{
		x=y;
	}
}
long long ksm(long long a,long long b,long long mod)
{
	long long s=1;
	while(b)
	{
		if(b&1)
		{
			s=s*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return s;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=n;i>=1;i--)
	{
		if(r[a[i]]!=0)
		{
			continue;
		}
		r[a[i]]=i;
	}
	int temp=1,last=1,ans=0;
	while(temp<=n)
	{
		for(;temp<=last&&temp<=n;temp++)
		{
			checkmax(last,r[a[temp]]);//如果其中有线段延伸到后面，后移右端点
			//cout<<"temp:"<<temp<<' '<<"last:"<<last<<endl; 
		}
		ans++;
		last++;
		if(last>n)
		{
			break;
		}
	}
	printf("%lld",(ksm(2,ans-1,998244353)+998244353)%998244353);
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

做法就是统计出序列中有可以+1的位置数cnt，因为可以+1意味着有两种情况，答案就是2^cnt  
形如 1 2 3 ... 3 这样，显然两个3之间是不能+1的，因为+1就不相同了，那么是不是记录每一个数字最后出现的位置然后模拟往后跳就行了呢？  

考虑这样的数据  
1 2 3 ... 4 ... 3 4  
如果我们直接模拟，那么就会把最右边的4也统计到cnt里

一个比较简单的做法，首先离散化，然后记录每一个数字最后出现的位置，然后从1到n扫一遍，记录一个right指针表示当前应该跳到的最右侧，然后还是依次往后扫，途中不断更新right指针，这样就能避免上述情况造成的问题
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 3e5 + 10, mod = 998244353;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int a[N], b[N], last[N];

int main()
{
    rg int n = fast_IO::read(), tot = 0;
    rg ll ans = 1;
    for (rg int i = 1; i <= n; ++i)b[i] = a[i] = fast_IO::read();
    sort(b + 1, b + n + 1); tot = unique(b + 1, b + n + 1) - b - 1;
    for (rg int i = 1; i <= n; ++i)last[a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b] = i;
    rg int right = 1;
    for (rg int i = 1; i <= n; ++i)
    {
        if (i <= right)
        {
            right = fast_IO::max(right, last[a[i]]);
            continue;
        }
        right = last[a[i]];
        (ans <<= 1) %= mod;
    }
    fast_IO::write(ans);
    return 0;
}

```

---

