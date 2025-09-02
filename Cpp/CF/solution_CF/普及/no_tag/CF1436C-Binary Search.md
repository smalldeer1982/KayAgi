# Binary Search

## 题目描述

Andrey thinks he is truly a successful developer, but in reality he didn't know about the binary search algorithm until recently. After reading some literature Andrey understood that this algorithm allows to quickly find a certain number $ x $ in an array. For an array $ a $ indexed from zero, and an integer $ x $ the pseudocode of the algorithm is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1436C/98f912f0399d121a6bf6605fa8d3ccffae3c8c30.png)Note that the elements of the array are indexed from zero, and the division is done in integers (rounding down).

Andrey read that the algorithm only works if the array is sorted. However, he found this statement untrue, because there certainly exist unsorted arrays for which the algorithm find $ x $ !

Andrey wants to write a letter to the book authors, but before doing that he must consider the permutations of size $ n $ such that the algorithm finds $ x $ in them. A permutation of size $ n $ is an array consisting of $ n $ distinct integers between $ 1 $ and $ n $ in arbitrary order.

Help Andrey and find the number of permutations of size $ n $ which contain $ x $ at position $ pos $ and for which the given implementation of the binary search algorithm finds $ x $ (returns true). As the result may be extremely large, print the remainder of its division by $ 10^9+7 $ .

## 说明/提示

All possible permutations in the first test case: $ (2, 3, 1, 4) $ , $ (2, 4, 1, 3) $ , $ (3, 2, 1, 4) $ , $ (3, 4, 1, 2) $ , $ (4, 2, 1, 3) $ , $ (4, 3, 1, 2) $ .

## 样例 #1

### 输入

```
4 1 2```

### 输出

```
6```

## 样例 #2

### 输入

```
123 42 24```

### 输出

```
824071958```

# 题解

## 作者：tuzhewen (赞：5)

蛮有思维的题目:)

内什么,我们可以发现只要在它的$mid<pos$，那么一定要使得$a_{mid}<=x$，如果$mid>pos$，那么一定要使得$a_{mid}>x$，这样的话就可以使得最终找到$x$而不用完全保证数组的单调性。

所以我们记录一下要几个数字小于$x$(记为$cnt1$)，几个数字大于$x$(记为$cnt2$)，才能保证二分的时候一定会找到$x$，那么接下来就是一个排列数的问题了。也就是说从小于$x$的数字(记为$sum1$)里面选$cnt1$个进行排列，从大于$x$的数字(记为$sum2$)里面选$cnt2$个进行排列，然后剩下$n-cnt1-cnt2-1$(要去掉$x$本身)个数字里面的随便排（也就是全排列），把它们乘一乘就好了。写成式子是这个样子$P_{sum1}^{cnt1}\times P_{sum2}^{cnt2}\times (n-cnt1-cnt2-1)!\%mod$

那么就很显然的可做了，$ACcode$如下：

```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
#define fi first
#define se second
const int INF=0x3f3f3f3f,mod=1e9+7,N=100005;
using namespace std;
int x,n,pos;
int cnt1,cnt2;
int fac[N],inv[N];
int qpow(int a,int b) {
	int res=1,tp=a;
	while(b) {
		if(b&1)res=1ll*res*tp%mod;
		tp=1ll*tp*tp%mod;
		b>>=1;
	}
	return res;
}
ll P(int n,int m) {
	return 1ll*fac[n]*inv[n-m]%mod;
}
int main() {
	scanf("%d%d%d",&n,&x,&pos);
	fac[0]=1,inv[0]=1;
	F(i,1,N-4) fac[i]=fac[i-1]*1ll*i%mod;
	F(i,1,N-4) inv[i]=qpow(fac[i],mod-2);//求阶乘的逆元，个人习惯
	int l=0,r=n;
	while(l<r) {
		int mid=(l+r)/2;
		if(mid<=pos) l=mid+1,cnt1+=(mid<pos);
		else r=mid,cnt2++;
	}//模拟二分的过程
	ll ans=1ll*P(x-1,cnt1)*
			P(n-x,cnt2)%mod*
			fac[n-cnt1-cnt2-1]%mod;//有x-1个数字小于x，n-x个数字大于x，然后就是上面的式子了
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：3)

### $\text{Difficulty : 1500}$
---
### 解题思路：

其实并不需要是严格递增序列才能检查出 $x$，只要能骗过去就行了。

由于 $n$ 是固定的，所以每一次二分查找的位置也是固定的那几个，只要这些位置上在 $x$ 左边的被查到的位置上是比 $x$ 小的数，在 $x$ 右边的数是比 $x$ 大的数就行了。

首先模拟一遍这个二分查找的过程，确定被查找的点的位置和数量，不妨设在 $x$ 左边的有 $a$ 个，右边的有 $b$ 个，一共有 $n$ 个数。那么可以任意排列的就有 $n-a-b-1$ 个位置，同时有 $d=n-x$ 个比 $x$ 大的数，$c=x-1$ 个比 $x$ 小的数。

所以总的方案数就是 $A(c,a)\times A(d,b)\times(n-a-b-1)!$。

展开：$\dfrac{c!}{(c-a)!}\times \dfrac{d!}{(d-b)!}\times(n-a-b-1)!$。

其中 $n=c+d+1$，带入得到 $\dfrac{c!}{(c-a)!}\times \dfrac{d!}{(d-b)!}\times(c+d-a-b)!$。

也就是 $\dfrac{(x-1)!}{(x-1-a)!}\times \dfrac{(n-x)!}{(n-x-b)!}\times(n-1-a-b)!$

直接无脑 $O(n)$。

---
### 代码：

```pascal
#include<cstdio>
using namespace std;
#define int long long
const int MOD=1000000007;
int n,x,pos,l,r,mid,a,c,b,d,ans;
signed main(){
	scanf("%I64d%I64d%I64d",&n,&x,&pos);
	l=0;r=n;
	while(l<r){
		mid=(l+r)>>1;
		if(mid<=pos){
			l=mid+1;
			if(mid!=pos)a++;
		}
		else r=mid,b++;
	}
	ans=1;
	for(int i=x-a;i<=x-1;i++)ans=(ans*i)%MOD;
	for(int i=n-x-b+1;i<=n-x;i++)ans=(ans*i)%MOD;
	for(int i=1;i<=n-1-a-b;i++)ans=(ans*i)%MOD;
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：vеctorwyx (赞：2)

### 题目大意

对于题目描述的二分查找方法（伪代码部分），长度为$n$的序列$S$有多少种排列使得二分查找能在位置$pos$找到数$x$（每个数$i$（$1\le i \le n$）仅会在序列中出现一次），答案对$1000000007$取模。

### sol

组合数学题。

如果我们想在第$pos$个位置上找到$x$,~~我们肯定要保证第pos位是x~~，我们必须保证在二分过程中所有在$pos$左边的$mid$的点权都比$x$小，而$pos$右边的点权都比$x$大，否则就会搜到别处去（~~自己手玩一下就能明白~~）。

那么思路就有了：

1. 二分找出所有涉及的$mid$（注意去重！）；

1. 求种类数（**注意这里是排列数，不是组合数**）。

	设$pos$左边有$a$个$mid$，右边有$b$个$mid$，
    
    则所有$mid$的排列个数为$\large\prod_{i=x-a}^{x-1}\prod_{j=n-x}^{n-x-b+1}i*j$（~~希望我表达正确~~），
    
    或者表示为$\large \frac{(x-1)!}{(x-a-1)!}*\frac{(n-x)!}{(n-x-b)!}$；
    
    再算上剩下的数字的全排列（个数为$(n-a-b-1)!$个），就得到了总排列数
    
    $\large ans=\frac{(x-1)!}{(x-a-1)!}*\frac{(n-x)!}{(n-x-b)!}*(n-a-b-1)!$
    
剩下的就是代码实现的事情了。

code：

```
#include<bits/stdc++.h>
#define int long long//十年oi一场空，不开longlong见。。
#define p 1000000007//别忘了取模
using namespace std;
int a[1010];
int n,x,pos,ans=1;
signed main()
{
    cin>>n>>x>>pos;
    int l=0,r=n;
    while(l<r)
    {
       
        int mid=l+r>>1;
        if(mid<=pos)
        l=mid+1,a[mid]=1;
        else
        r=mid,a[mid]=2;
    }
    int hi=0,lo=0;
    for(int i=0;i<n;i++)//标记去重
    {
        if(i==pos)
        continue;
        if(a[i]==2)
        hi++;//比pos大的mid数
        else if(a[i]==1)
        lo++;//比pos小的mid数
    }
    for(int i=x-1;i>=x-lo;i--)//建议枚举求排列数不容易错^_^
    ans=(ans*1ll*i)%p;
    for(int i=n-x;i>=n-x-hi+1;i--)
    ans=(ans*1ll*i)%p;
    for(int i=1;i<=n-hi-lo-1;i++)
    ans=(ans*1ll*i)%p;
    cout<<ans;
    return 0;
}
```
~~附[原题链接](http://codeforces.com/problemset/problem/1436/C)。~~

---

## 作者：tommymio (赞：1)

根据二分过程抽象出一棵树，发现从 $[l,r]=[0,n]$ 的初始态到 $[l,r]=[pos+1,pos+1]$ 的终态必然只有一条路径。路径上向左走就是收缩右边界，向右走就是收缩左边界。也就是说，经过二分最终得到 $l=pos+1$ 的过程是唯一的。

那么，就可以模拟一遍，从而得到二分过程中每一个点与 $x$ 的大小关系。设二分过程中 $\leq x$ 的点有 $cnt_0$ 个，$>x$ 的点有 $cnt_1$ 个，则最终答案为：

$$
A_{x-1}^{cnt_0-1}\times A_{n-x}^{cnt_1}\times A_{n-cnt_0-cnt_1}^{n-cnt_0-cnt_1}
$$

时间复杂度为 $O(n \log n)$。可能出题人开 $n=10^3$ 的数据，是想给杨辉三角的 $O(n^2)$ 也放了吧/yun

**Show the Code**

```cpp
#include<cstdio>
typedef long long ll;
const ll mod=1e9+7;
int cnt0,cnt1;
ll fac[1005],inv[1005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline ll A(int n,int m) {return fac[n]*inv[n-m]%mod;}
inline ll pow(ll x,int p) {ll res=1;for(;p;p>>=1) {if(p&1) res=res*x%mod; x=x*x%mod;}return res;}
inline void find(int l,int r,int pos) {
    while(l<r) {
        int mid=l+r>>1;
        if(mid<=pos) l=mid+1,++cnt0;
        else r=mid,++cnt1;
    }
}
int main() {
    int n=read(),x=read(),pos=read();
    inv[0]=fac[0]=1ll;
    for(register int i=1;i<=n;++i) {fac[i]=fac[i-1]*i%mod;inv[i]=pow(fac[i],mod-2);}
    find(0,n,pos);
    if(cnt1>n-x||cnt0>x) printf("0\n");
    else printf("%lld\n",A(x-1,cnt0-1)*A(n-x,cnt1)%mod*fac[n-cnt0-cnt1]%mod);
    return 0;
}
```

---

## 作者：jun头吉吉 (赞：1)

## 题意
二分查找大家都会吧！

![](https://cdn.luogu.com.cn/upload/image_hosting/x2o0iadl.png)

根据《信息学奥赛一本通》我们知道，二分查找只有当 $a$ 单调时成立。到事实上，对于某些不单调的序列，上面的二分查找同样成立。

因此你想给《信息学奥赛一本通》的作者寄一封信，但在这之前你想找到有多少大小为 $n$ ，第 $pos$ 位为 $x$ 的排列能够找到 $x$ （即使上面的函数的返回值为`true`）。

一个排列指 $n$ 个介于 $1$ 和 $n$ 之间的任意顺序的不同整数组成的数组，下标从 $0$ 开始。

因为答案数很大，请对 $10^9+7$ 取模。
## 题解
一个挺有趣的题目。

倒推二分查找的过程，通过 $pos$ 与 $mid$ 的关系逆推往左还是往右，再判断当前的数字是进第一个`if`还是第二个`else`

然后假设有 $a$ 个小于 $x$ ，$b$ 个大于$x$，则最后的答案为
$$A_{x-1}^a\times A_{n-x}^b\times A_{n-a-b-1}^{n-a-b-1}$$

值得注意的一点是，如果存的是小于等于，那么要特判第$pos$个位置。
## 代码
```cpp
#define int long long
const int mod=1e9+7;
using namespace std;
bool mxydy[2100],mdy[2100];
int n,x,pos;
template<class T>T ksm(T a,T b,T c){
    T res=1;
    while(b){
        if(b&1)res=res*a%c;
        a=a*a%c;b>>=1;
    }return res;
}
int A(int n,int m){
	if(m>n)return 0; 
	int res=1;
	for(int i=1;i<=m;i++)
		(res*=(n-i+1))%=mod;
	return res;
}
signed main(){
	in::read(n,x,pos);//x++;
	int left=0,right=n;
	while(left<right){
		int mid=left+right>>1;
		if(pos<mid){
			right=mid;
			mdy[mid]=1;
			//printf("%d 大于\n",mid);
		}else{
			left=mid+1;
			mxydy[mid]=1;
			//printf("%d 小于等于\n",mid);
		}
	}
	int xydy=0,dy=0;
	for(int i=0;i<n;i++)
		xydy+=mxydy[i],
		dy+=mdy[i];
	if(mxydy[pos])xydy--;
	//printf("%d %d\n",xydy,dy);
	out::write(A(x-1,xydy)*A(n-x,dy)%mod*A(n-xydy-dy-1,n-xydy-dy-1)%mod);
	out::flush();
	return 0;
}
```

---

## 作者：MVP_Harry (赞：1)

挺不错的一道题。

我们可以人脑模拟一下这个二分的过程，比如，第一次$\text{mid} = N/2$，此时，如果$\text{pos}$在$\text{mid} - 1$的左边，那么$a[pos] \ge x$，反之同理。（如果正好等于$\text{pos}$，那就跳过）

可以将这个过程从头到位模拟几遍，就得到了一些特定位置时$a[i]$ 与$x$的关系。不妨设在我们求出来的这些位置里面有$m$个是需要满足大于$x$的，有$n$个是小于$x$的。而总共有$N - x$个大于$x$的数，$x - 1$个小于$x$的数。由基本的组合尝试可求出

$$\text{ans} = P(N - x, m) \cdot P(x - 1, n) \cdot P(N - x - m, N - x - m) \cdot P(x - 1 - n, x - 1 - n) \cdot C(\text{tot} - m - n - 1, \text{tot} - x - m).$$

其中，$\text{tot}$是总共有多少数，$P(a, b)$表示有多少排列，而$C(a, b)$表示有多少组合。虽然柿子看上去比较复杂，但其实很trivial的，大家自己可以推一推。

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, m, n) for (ll i = m; i <= n; i++)
#define per(i, m, n) for (ll i = m; i >= n; i--) 

const ll maxn = 1005;
const ll mod = 1e9 + 7;
ll dp[maxn], coeff[maxn][maxn]; 

ll calc(ll x, ll y) {
	ll ans = 1; 
	rep(i, 0, y - 1) ans = ans * (x - i) % mod; 
	return ans; 
}

void binary() {
	coeff[0][0] = 1;
	rep(i, 1, 1000) coeff[i][i] = 1, coeff[i][0] = 1;
	rep(i, 1, 1000) rep(j, 1, 1000) coeff[i][j] = (coeff[i - 1][j - 1] + coeff[i - 1][j]) % mod;  
}

void solve() {
	ll N, x, pos;
	cin >> N >> x >> pos; 
	ll l = 0, r = N, cnt_small = 0, cnt_big = 0; 
	while (l < r) {
		ll mid = (l + r) / 2;
		// [l, mid], [mid + 1, r]; 
		if (pos + 1 <= mid) {
			// a[mid] > x;
			dp[mid] = 1, cnt_big++; 
			if (mid == pos) dp[mid] = 0, cnt_big--;
			r = mid; 
		} else {
			// a[mid] <= x; 
			dp[mid] = -1, cnt_small++; 
			if (mid == pos) dp[mid] = 0, cnt_small--;  
			l = mid + 1;  
		}
	}
	// [1, x - 1], [x + 1, N]
	ll ans = 1;
	ans = ans * (calc(N - x, cnt_big)) % mod * calc(x - 1, cnt_small) % mod * calc(N - x - cnt_big, N - x - cnt_big) % mod;
	ans = ans * calc(x - 1 - cnt_small, x - 1 - cnt_small) % mod; 
	ans = ans * coeff[N - cnt_big - cnt_small - 1][N - x - cnt_big] % mod; 
	cout << ans << "\n"; 
}	

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0); 
	ll testcase = 1; 
	binary(); 
	while (testcase--) {
		solve();
	}    
	return 0; 
}
```

---

