# Salyg1n and Array (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the versions is the limit on the number of queries. In this version, you can make no more than 57 queries. You can make hacks only if both versions of the problem are solved.

This is an interactive problem!

salyg1n has given you a positive integer $ k $ and wants to play a game with you. He has chosen an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ). You must print $ a_1 \oplus a_2 \oplus \ldots \oplus a_n $ , where $ \oplus $ denotes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operation. You can make queries of the following type:

- $ ? $ $ i $ : in response to this query, you will receive $ a_i \oplus a_{i + 1} \oplus \ldots \oplus a_{i + k - 1} $ . Also, after this query, the subarray $ a_i, a_{i + 1}, \ldots, a_{i + k - 1} $ will be reversed, i.e., the chosen array $ a $ will become: $ a_1, a_2, \ldots a_{i - 1}, a_{i + k - 1}, a_{i + k - 2}, \ldots, a_{i + 1}, a_i, a_{i + k}, \ldots, a_n $ .

You can make no more than $ 57 $ queries to answer the problem.

## 说明/提示

In the first test case, the jury has chosen the array $ a $ $ = $ $ [4, 2, 5, 1] $

In the second test case, the jury has chosen the array $ a $ $ = $ $ [5, 7, 1, 3, 3, 7] $

## 样例 #1

### 输入

```
2
4 2

6

4

6 6

4```

### 输出

```
? 1

? 3

! 2

? 1

! 4```

# 题解

## 作者：_sunkuangzheng_ (赞：9)

**【题目大意】**

交互题，交互库隐藏长度为 $n$ 的序列 $a$，你每次可以询问长度为 $k$ 的区间 $[l,l+k-1]$ 的异或值（$\oplus_{i=l}^{l+k-1}a_i$）并同时将这个区间翻转。$1 \le k \le n \le k^2 \le 2500$，你最多可以进行 $57$ 次询问。**保证 $n,k$ 均为偶数**。

**【题目分析】**

首先你要能计算出这题的数据范围：$1 \le k \le 50$。我们先考虑 $n \bmod k = 0$ 的情况，显然我们可以从 $1$ 开始问过去，只需要 $\dfrac{n}{k}$ 次询问就可以得到答案。由数据范围，$\dfrac{n}{k} \le k$，所以最多需要 $50$ 次询问。

类似的，如果 $n \bmod k \ne 0$，我们也可以先顺序问过前面的区间，最后留下一个长度在 $2 \sim 2k-2$ 的区间。下面的讨论都针对这个区间。为了表述直观，使用 $1,2,3$ 表示 $a_1,a_2,a_3$ 等。

先用一个例子来看，假设 $n = 10,k = 6$，我们的询问如下：

蓝色表示询问过 $1$ 次的数字，红色表示 $2$ 次，绿色表示 $3$ 次。

$$[\color{blue}{1,2,3,4,5,6}\color{black},7,8,9,10](\text{询问区间}\,[1,6])$$

$$[\color{blue}{6,5,}\color{red}{4,3,2,1,}\color{blue}7,8,\color{black}9,10](\text{询问区间}\,[3,8])$$

$$[\color{blue}{6,5,8,7,}\color{green}{1,2,3,4,}\color{blue}{9,10}\color{black}](\text{询问区间}\,[5,10])$$

你发现所有元素都被异或了奇数次，所以你将三次询问结果异或起来就是要求的值。

研究一下刚才我们的询问过程，核心在于第二次询问。记 $m = \dfrac{n \bmod k}{2} + 1$，我们询问以 $m + 1$ 为左端点的区间。这次操作会使得我们将区间 $[m+1,k]$ 被重复询问，即染上红色。与此同时，这段区间会被**恰好翻转到位置 $[n-k+1,n-m+1]$**。然后我们再询问 $[n-k+1,n]$ 的时候，这部分一定由询问过 $2$ 次的红色部分和未被询问过的黑色部分组成。经过这次操作，所有数字都会异或奇数次。

分析我们的询问次数。前半段最多花费 $\lfloor \dfrac{n}{k} \rfloor$ 次询问，后半段需要 $2$ 次询问，所以最多不会超过 $51$ 次询问，可以同时通过 E1 和 E2。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,x,i,pi;
int main(){
    cin >> t;
    while(t --){
        cin >> n >> k;int res = 0;
        if(n == k){
            cout << "? 1" << endl,cin >> res;
            cout << "! " << res << endl;continue;
        }
        for(i = 1;i <= n - k + 1;i += k) cout << "? " << i << endl,cin >> x,res ^= x;
        if(n % k == 0){cout << "! " << res << endl;continue;}
        cout << "? " << i - k + (n % k) / 2 << endl,cin >> x,res ^= x;
        cout << "? " << n - k + 1 << endl,cin >> x,res ^= x;
        cout << "! " << res << endl;
    }
}
```


---

## 作者：封禁用户 (赞：1)

# 题意
一条直线上有 $n$ 条线，给你左右端点。我们将他们两两配对，满足配对的两条线段有相交，不配对的线段不相交。

注意相交的定义：两条线段左右端点分别为 $l_x,r_x,l_y,r_y$。那么相交的定义为 $l_y \le l_x \le r_y$ 或 $l_y \le r_x \le r_y$ 或 $l_x \le l_y \le r_x$ 或 $l_x \le r_y \le r_x$。即有一条线段的一个端点在另一个线段之内，包括端点重合。

看一下样例的第一组：

```
7
2 4
9 12
2 4
7 7
4 8
```
![](https://cdn.luogu.com.cn/upload/image_hosting/uptostal.png)

绿的线段是选的，红的线段是删的。所以删一条。

# 思路
又是正难则反。我们将两两可以重一起的线段并成一条线段，就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/mh1q23wp.png)

这样就转换成了一个经典的贪心：在直线内取线段，让所有都不重叠，求取最多的线段数。

方法很简单，也就是按最右边排序，如果当前的与以前重复就跳过，不然就取即可。

这种方法并不会算重线段，因为同一条线段与不同的线段组出来的线段一定会有重复，所以不会算重。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int t;
struct ab{
	int l;
	int r;
	friend bool operator <(ab a,ab b){
		return a.r<b.r;
	}
}op[4000010];
struct abc{
	int l;
	int r;
}ss[2010];
int tot;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>t;
	while(t--){
		tot=0;
		int n;
		cin>>n;
		f(i,1,n){
			cin>>ss[i].l>>ss[i].r;
		}
		f(i,1,n){
			f(j,i+1,n){
				if(ss[i].l<=ss[j].r&&ss[i].l>=ss[j].l){
					op[++tot].l=min(ss[j].l,ss[i].l);
					op[tot].r=max(ss[i].r,ss[j].r);
				}else if(ss[i].r<=ss[j].r&&ss[i].r>=ss[j].l){
					op[++tot].l=min(ss[j].l,ss[i].l);
					op[tot].r=max(ss[i].r,ss[j].r);
				}else if(ss[j].l<=ss[i].r&&ss[j].l>=ss[i].l){
					op[++tot].l=min(ss[j].l,ss[i].l);
					op[tot].r=max(ss[i].r,ss[j].r);
				}else if(ss[j].r<=ss[i].r&&ss[j].r>=ss[i].l){
					op[++tot].l=min(ss[j].l,ss[i].l);
					op[tot].r=max(ss[i].r,ss[j].r);
				}
			}
		}
		sort(op+1,op+1+tot);
		int ll=-1,sum=0;
		for(int i=1;i<=tot;i++){
//			cout<<op[i].l<<" "<<op[i].r<<endl;
			if(op[i].l<=ll){
				continue;
			}
			sum++;
			ll=max(ll,op[i].r);
		}
//		cout<<"        ";
		cout<<n-2*sum<<endl;
	} 
	return 0;
}
```

---

## 作者：qiuzijin2026 (赞：1)

# Salyg1n and Array (hard version)

[题面](https://www.luogu.com.cn/problem/CF1867E2)

## 思路

题解里的图片中的红色表示异或的次数为奇，也就是已经算过了，白色代表没算。

我们发现如果 $n \bmod k=0$ 那么答案非常简单，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/vzoapluq.png)

但是难处理的部分就是 $n \bmod k$ 剩下的余数。

![](https://cdn.luogu.com.cn/upload/image_hosting/t4qjdrl5.png)

但是因为 $k$ 与 $n$ 均为偶数，所以 $n \bmod k$ 也为偶数。

于是就可以像下图这样把余数部分分成两半处理：

![](https://cdn.luogu.com.cn/upload/image_hosting/64c9afm2.png)

最后把各个部分的异或值异或起来就是答案。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int n,k;
int ans;
int tmp;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n>>k;
		ans=0;
		for(int i=1;i<=n/k;i++){
			cout<<"? "<<(i-1)*k+1<<endl;
			cin>>tmp;
			ans^=tmp;
		}
		if(n%k==0) cout<<"! "<<ans<<endl;
		else{
			cout<<"? "<<(n/k-1)*k+1+(n%k)/2<<endl;
			cin>>tmp;
			ans^=tmp;
			cout<<"? "<<n-k+1<<endl;
			cin>>tmp;
			ans^=tmp;
			cout<<"! "<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：One_JuRuo (赞：1)

# 写在前面

做 E1 的时候，直接想的正解，所以 E2 不需要改代码，E1 题解我也直接交的正解，详见[我的题解](https://www.luogu.com.cn/blog/AuroraWind/cf1867e1-salyg1n-and-array-simple-version)。

在这里呢，主要是稍微证明一下询问次数不会超，如下：

可以发现，有余数的情况，只会增加两次询问，而后面的操作会增加 $\frac n k$ 次情况，因为 $k\le n\le k^2$，所以询问最大次数是 $k+2$，也就是 $52$ 次，所以不仅能过 E1，E2 也是随便过的。


# 题解

还是放一下题解，当然和 E1 没有什么区别。

## 思路

首先考虑，$n$ 是 $k$ 的倍数的情况，直接枚举询问所有每一段就好，然后输出每一段的异或和的异或和。

![](https://cdn.luogu.com.cn/upload/image_hosting/1i9ukfhn.png)

如上图，每次询问都没有重叠部分，颠转互不干扰。

那么，$n$ 不是 $k$ 的倍数的情况呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/v8vf3blk.png)

可以看到，与第一种情况的区别就是末尾多了一小截，那么我们需要考虑如何计算这一小截的异或和。

很容易想到，提前在前面计算这个长度的异或和，后续就可以和第一种情况一样了。

可以发现，解题的关键就是查询后会颠转这个特殊性质，见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s7b8rh0i.png)

因为异或的性质，自己异或自己会变成 $0$，所以同一段的异或两次就会变成 $0$。使用这个性质可以发现，如果两个询问区间重叠，那么因为颠转，获得的异或和会转移到一起。

那么我们可以考虑先构造出前面一截是余数长度的区间的异或何，后续就是第一种情况了。

因为每次取得区间长度都是固定的，所以两段红色的区间长度也一定一样，因为两段长度和是余数，所以一段我们就取余数的一半。

因为 $n$ 和 $k$ 在题目中都给定了是正偶数，所以不用担心余数是奇数的情况。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,sum,a;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k,sum=0;
		if(n%k)
		{
			cout<<"? 1"<<endl;
			cin>>a,sum^=a;
			cout<<"? "<<1+(n%k)/2<<endl;
			cin>>a,sum^=a;
		}
		for(int i=(n%k)+1;i<=n;i+=k) cout<<"? "<<i<<endl,cin>>a,sum^=a;
		cout<<"! "<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：mayike (赞：1)

~~简单题~~

### [题目传送门](https://codeforces.com/problemset/problem/1867/E2)

## 思路

首先，必须知道 $x \operatorname{xor} x = 0,0 \operatorname{xor} x = x$，$x$ 规定为自然数。那么这题就简单了。

作图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ji08z9t9.png)

先问 $1$ 区间，再问了 $2$ 区间，则红色区域的异或值被抵消成 $0$，此时查询后要翻转区间，则区间 $2$ 转成区间 $3$，再询问区间 $4$，那么红色区域的异或值就回来了，此时的异或值为区间 $1$，区间 $2$ 的白色区域以及区间 $4$ 的白色区域的异或值。

因为区间长度为 $k$，所以这个操作等价于在假设询问过区间 $1$ 的情况下，后两次连续询问的长度是相同且在 $1 \le x \le k$ 里随便拟定长度的。

那么总次数至多为 $\frac{n}{k}+2 \le 52$ 满足条件，因为 $n,k$ 都是偶数，那么我们对 $a = n \bmod k$，这一段进行两次连续且长度相同的询问即可。

代码也比较短。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int T,n,k,cnt,ps,ans;
	cin>>T;
	while(T--){
		cin>>n>>k;
	    cnt=ps=ans=0;
		int sum=(n-k)/2,x,js;
		cnt=sum/k,ps=sum%k;
		cout<<"? "<<1<<endl;
		cin>>x,ans^=x,js=k+1;
		if(ps!=0){
			cout<<"? "<<js-(k-ps)<<endl;
			cin>>x,ans^=x,js=js+ps;
			cout<<"? "<<js-(k-ps)<<endl;
			cin>>x,ans^=x,js=js+ps;
		}for(int i=1;i<=cnt*2;i++){
			cout<<"? "<<js<<endl;
			cin>>x,ans^=x,js+=k;
		}cout<<"! "<<ans<<endl;
	}
}
```

---

## 作者：出言不逊王子 (赞：1)

神仙题，被 [LYY_yyyy](https://www.luogu.com.cn/user/466451) 带飞了。

发现 $k^2\le 2500$，即 $k\le 50$，和操作次数差不多。

因为题目要求整个数列的异或和，而这个显然是可以叠加的，所以我们思考直接暴力求出数组大部分的异或和。

现在还剩下最后 $n\bmod k<k$ 个数，我们思考怎么处理它。

我们还剩下七次操作，所以我们考虑在很少的操作次数内解决。

因为 $2|n,k$，所以 $2|n\bmod k$，这启示我们将最后一段劈成两部分 $[l,m]$ 和 $(m,n]$。

我们试着询问 $[m-k+1,m]$，发现除了我们想要的 $[l,m]$，还多了一段 $[m-k+1,l)$，因此我们需要把它消掉。

在询问后，我们发现最左边的这一段跑到了 $[m-k+1,m]$ 的最右边。再右边是什么？正好是我们想要的 $(m,r]$。

那我们再来一次操作就大功告成了。记得特判 $k|n$ 的情况。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int n,k,p,cur=1,d,s;
void mian(){
	cin>>n>>k;p=d=s=0;cur=1;
	while(cur+k-1<=n){
		cout<<"? "<<cur<<endl;
		int x;cin>>x;p^=x;
		cur+=k;
	}
	if(cur==n+1) return cout<<"! "<<p<<endl,void();
	int delta=n%k;
	int endp=delta/2+cur-1,startp=endp-k+1;
	cout<<"? "<<startp<<endl;cin>>d;
	cout<<"? "<<n-k+1<<endl;cin>>s;
	cout<<"! "<<(p^d^s)<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	int t;cin>>t;while(t--) mian();
	return 0;
}
```

---

## 作者：InversionShadow (赞：0)

很好的题。

注意到 $k^2\leq2500$，那么有 $k\leq50$。

显然暴力查出大部分值。

此部分代码如下：

```cpp
for (int i = 1; i + k - 1 <= n; i += k) {
  cout << "? " << i << endl;
  int x;
  cin >> x;
  res ^= x;
}
```

那么就被分成了长度：

$[ k ][ k ][...][n \bmod k]$ 

那问题是怎么求这 $[n \bmod k]$ 的异或值。

注意到 $n,k$ 均为偶数，考虑往除以二上靠：

$[k][...][\dfrac{n \bmod k}{2}][\dfrac{n \bmod k}{2}]$

注意到查询完一个区间就会反转，又注意到异或的性质 $x \oplus y \oplus y = x$。

所以我们可以构造出：


$[k][...][ \dfrac{(n \bmod k)}{2} ][ k - \dfrac{(n \bmod k)}{2}][ \dfrac{(n \bmod k)}{2} ][ \dfrac{(n \bmod k)}{2}]$

对前面这个 $[ k - \dfrac{(n \bmod k)}{2}][ \dfrac{(n \bmod k)}{2} ]$ 查询一次，然后就变成了：

$[k][...][ \dfrac{(n \bmod k)}{2} ][ \dfrac{(n \bmod k)}{2} ][ k - \dfrac{(n \bmod k)}{2}][ \dfrac{(n \bmod k)}{2}]$

对后面的两坨东西查询，这样 $[ k - \dfrac{(n \bmod k)}{2}]$ 的异或就被抵消了（异或了两次）。

```cpp
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
int t, n, k, i;
 
signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		if (n % k == 0) {
			int res = 0;
			for (i = 1; i + k - 1 <= n; i += k) {
				cout << "? " << i << endl;
				int x;
				cin >> x;
				res ^= x;
			}
			cout << "! " << res << endl;
		} else {
			int res = 0;
			for (i = 1; i + k - 1 <= n; i += k) {
				cout << "? " << i << endl;
				int x;
				cin >> x;
				res ^= x;
			}
			cout << "? " << n - (n % k) / 2 - (n % k) / 2 - (k - (n % k) / 2) + 1 << endl;
			int x;
			cin >> x;
			res ^= x;
			cout << "? " << n - (n % k) / 2 - (k - (n % k) / 2) + 1 << endl;
			cin >> x;
			res ^= x;
			cout << "! " << res << endl;
			// [ k - (n % k) / 2 ][ (n % k) / 2 ][ (n % k) / 2]
			// [ (n % k) / 2 ][ k - (n % k) / 2 ][ (n % k) / 2]
		}
	}
	return 0;
}
```

~~注意到，这篇文章一共出现了 $6$ 次注意到。~~

---

## 作者：Daniel_yao (赞：0)

## Problem
交互题。交互库有一个长度为 $n$ 的数列 $a$，求其所有元素的异或和，每次你可以选择一个 $i$，询问 $[i,i+k-1]$ 中的异或和，并将其翻转。询问不能超过 $57$ 次。**保证 $n$ 与 $k$ 均为偶数**。
## Solve
我们发现 E1 的程序不高效率的原因在于它有很多的冗余运算。比如，最后的剩余段会被询问 $(n \bmod k) + 1$ 次，这是很不高效的。我们发现前面的区间覆盖询问 $\left\lfloor \dfrac{n}{k} \right\rfloor$ 次是无法避免的。这时候，留给我们的剩余询问数就只剩下了 $7$ 个。所以我们要高效的处理剩余段的询问。

我们考虑将 $[k\left\lfloor \dfrac{n}{k} \right\rfloor+1,n]$ 折半，一半的长度记为 $l$。将左半段区间和 $[k\left\lfloor \dfrac{n}{k} \right\rfloor+1-l,k\left\lfloor \dfrac{n}{k} \right\rfloor]$ 一起询问，然后原数组 $[k\left\lfloor \dfrac{n}{k} \right\rfloor+1-l,k\left\lfloor \dfrac{n}{k} \right\rfloor]$ 将会被翻转到折半区间的左半段区间，再与右半段区间询问一次。这样，原本 $[k\left\lfloor \dfrac{n}{k} \right\rfloor+1,n]$ 将会被询问一次。$[k\left\lfloor \dfrac{n}{k} \right\rfloor+1-l,k\left\lfloor \dfrac{n}{k} \right\rfloor]$ 总共会被询问 $3$ 次，贡献一次答案。刚好将原数组的所有元素包含。

这样最多只需要询问 $52$ 即可，可以通过此题。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

int n, T, k, res;

int ask(int i) {
  cout << "? " << i << '\n';
  fflush(stdout);
  int x; cin >> x;
  return x;
}

void solve() {
  res = 0; 
  cin >> n >> k;
  int i;
  for (i = 1; i + k - 1 <= n; i += k) {
    res ^= ask(i);
  } 
  if(n % k == 0) {
    cout << "! " << res << '\n';
    fflush(stdout);
  } else {
    res ^= ask(i - k + (n % k) / 2);
    res ^= ask(n - k + 1);
    cout << "! " << res << '\n';
    fflush(stdout);
  }
  return ;
}

signed main() {
  cin >> T;
  while(T--) {
    solve(); 
  }
  return 0;
}
```

---

## 作者：233L (赞：0)

首先 $k \mid n$ 是好做的。对于 $k \nmid n$，可以先把前面的整段直接询问，后面的 $m(k<m<2k,2 \mid m)$ 个数再单独做。

考虑相邻询问的影响。假设先问 $[1,k]$，再问 $[2,k+1]$，我们记 $A= \oplus_{i=1}^{k-1}a_i, B=a_k,C=a_{k+1}$，那么第一次的结果是 $A \oplus B$，第二次的结果是 $A \oplus C$，两次异或起来就是 $B \oplus C$，且此时序列从 $ABC$ 变成了 $BCA$，相当于 $A$ 往右平移了 $2$ 格。于是可以继续往下迭代，最后 $A$ 会往右平移 $\frac{n-k}{2}$ 格，$A$ 的右侧还有一个元素，再询问一次，恰好就是所有元素的异或和。这样的询问次数是 $\frac{n}{k}+k$，因为 $n^2 \le k$，所以 $\frac{n}{k} \le k \le 50$，总次数就在 $100$ 以内，可以过 easy version。

https://codeforces.com/contest/1867/submission/222969045

---

接着来做 hard version。显然前面的整段没有优化空间，考虑优化后面 $m$ 个数的操作。注意到 $\frac{m-k}{2}$ 是整数，把前 $m-k$ 个数从中间切开分成两份，后 $m-k$ 个数同理，然后这 $m$ 个数就被分成 $5$ 段，和 easy version 类似的，从左到右询问 $3$ 次（每次覆盖了 $3$ 段）就能得到这 $m$ 个数的异或和。询问次数在 $53$ 次以内。

https://codeforces.com/contest/1867/submission/223035395

---

