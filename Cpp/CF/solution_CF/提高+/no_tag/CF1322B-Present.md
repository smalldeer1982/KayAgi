# Present

## 题目描述

Catherine received an array of integers as a gift for March 8. Eventually she grew bored with it, and she started calculated various useless characteristics for it. She succeeded to do it for each one she came up with. But when she came up with another one — xor of all pairwise sums of elements in the array, she realized that she couldn't compute it for a very large array, thus she asked for your help. Can you do it? Formally, you need to compute

 $ $$$ (a_1 + a_2) \oplus (a_1 + a_3) \oplus \ldots \oplus (a_1 + a_n) \\ \oplus (a_2 + a_3) \oplus \ldots \oplus (a_2 + a_n) \\ \ldots \\ \oplus (a_{n-1} + a_n) \\  $ $ </p><p>Here  $ x \\oplus y $  is a bitwise XOR operation (i.e.  $ x $  <span class="tex-font-style-tt">^</span>  $ y$$$ in many modern programming languages). You can read about it in Wikipedia: [https://en.wikipedia.org/wiki/Exclusive\_or#Bitwise\_operation](https://en.wikipedia.org/wiki/Exclusive_or#Bitwise_operation).

## 说明/提示

In the first sample case there is only one sum $ 1 + 2 = 3 $ .

In the second sample case there are three sums: $ 1 + 2 = 3 $ , $ 1 + 3 = 4 $ , $ 2 + 3 = 5 $ . In binary they are represented as $ 011_2 \oplus 100_2 \oplus 101_2 = 010_2 $ , thus the answer is 2.

 $ \oplus $ is the bitwise xor operation. To define $ x \oplus y $ , consider binary representations of integers $ x $ and $ y $ . We put the $ i $ -th bit of the result to be 1 when exactly one of the $ i $ -th bits of $ x $ and $ y $ is 1. Otherwise, the $ i $ -th bit of the result is put to be 0. For example, $ 0101_2 \, \oplus \, 0011_2 = 0110_2 $ .

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 2 3```

### 输出

```
2```

# 题解

## 作者：Daidly (赞：27)

由题可知，对答案每一位有贡献的是 $(a[i]+a[j])$ 的每一位，所以可以按位考虑。

- 两个数第 $k$ 位的和，与前 $k$ 位有联系。

不妨先求 $a[j]$ 的前 $i$ 位，用 $b[j]$ 储存：

- 第一种：$b[j]=a[j] \bmod 2^{k+1}$，代码为：`b[j]=a[j]%(1<<(i+1))`。

- 第二种：$b[j]=a[j] \And 2^{k+1}-1$，比如取数 $X=10101110$ 的前 $4$ 位，只需要另找一个数 $Y$，令 $Y$ 的前 $4$ 位为 $1$，其余位为 $0$，即 $Y=00001111$，然后将 $X$ 与 $Y$ 进行按位与运算 $(X \And Y=00001110)$ 即可得到 $X$ 的前 $4$ 位。代码为：`b[j]=a[j]&((1<<(i+1))-1)`。

效果一样，自行选择。

然后考虑 $b[j_1]+b[j_2]$ 第 $i$ 位为 $1$ 的条件：

- 不进位：$b[j_1]+b[j_2]\in[2^i,2^{i+1}-1]$，代码为：`(1<<i,(1<<(i+1))-1)`。

- 进位：$b[j_1]+b[j_2]\in[2^i\times2+2^i,(2^{i+1}-1)\times 2]$，$b[j_1]+b[j_2]\in[3\times 2^i,2^{i+2}-2]$，代码为：`(3<<i,(1<<(i+2))-2)`。

由于 $b$ 数组的顺序对答案没有影响，所以可以用 `two-pointers` 计算。

关于双指针函数：

```cpp
bool tp(int x,int y){
	if(x>y)return 0;
	int num=0;
	for(int i=n,l=1,r=1;i;--i){
		while(l<=n&&b[i]+b[l]<x)l++;
		while(r<=n&&b[i]+b[r]<=y)r++;
		num+=r-l-(l<=i&&i<r);
	}
	return (num>>1)&1;//判断num除2是奇是偶 
}
```
设定为 `bool` 函数，计算 $b[j_1]+b[j_2]\in[2^i,2^{i+1}-1]\cup [3\times 2^i,2^{i+2}-2]$ 的个数是奇是偶。

当然，在这里我们可以分开算，然后再与上两个 `bool` 函数返回值：

`int cnt=tp(1<<i,(1<<(i+1))-1)^tp(3<<i,(1<<(i+2))-2);`

若在区间 $[2^i,2^{i+1}-1]$ 和区间 $[3\times 2^i,2^{i+2}-2]$ 中有且只有一个区间有奇数个 $(b[j_1],b[j_2])$ 满足条件（根据 奇 $+$ 偶 $=$ 奇），则更新答案。

最后一点，判断 $i$ 的最大值（最大计算到前几位）：

由题可知：答案为两数之和再取异或值，所以答案的位数小于等于最大的数对和位数，因为 $1\leq a_i\leq 10^7$，所以两数之和小于等于 $2\times 10^7$，又因为 $2^{25}=33554432>2\times 10^7$，所以 $i\leq 25$ 即可（这里位数指二进制位数）。

整体代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 400005
int n,a[MAXN],b[MAXN],ans;
bool tp(int x,int y){
	if(x>y)return 0;
	int num=0;
	for(int i=n,l=1,r=1;i;--i){
		while(l<=n&&b[i]+b[l]<x)l++;
		while(r<=n&&b[i]+b[r]<=y)r++;
		num+=r-l-(l<=i&&i<r);
	}
	return (num>>1)&1;//判断num除2是奇是偶 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	//2^25=33554432>2*1e7
	for(int i=0;i<=25;++i){
		for(int j=1;j<=n;++j){
			b[j]=a[j]%(1<<(i+1));
			//b[j]=a[j]&((1<<(i+1))-1)
		}
		sort(b+1,b+n+1);
		int cnt=tp(1<<i,(1<<(i+1))-1)^tp(3<<i,(1<<(i+2))-2);
		ans+=cnt*(1<<i);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xht (赞：21)

按位考虑。

对于第 $k$ 位，我们只关心每个数对 $2^{k+1}$ 取模后的值。

对于两个取模后的数，如果要在第 $k$ 位为 $1$，和必须在 $[2^k, 2^{k+1}-1]$ 或 $[2^k + 2^{k+1}, 2^{k+2}-2]$ 中。

排序之后双指针扫一遍即可，时间复杂度 $\mathcal O(n \log n \log w)$。

```cpp
const int N = 4e5 + 7;
int n, a[N], b[N], ans;

inline bool calc(int L, int R) {
	if (L > R) return 0;
	ll ret = 0;
	for (int i = n, l = 1, r = 1; i; i--) {
		while (l <= n && b[i] + b[l] < L) ++l;
		while (r <= n && b[i] + b[r] <= R) ++r;
		ret += r - l - (l <= i && i < r);
	}
	return (ret >> 1) & 1;
}

inline bool solve(int k) {
	for (int i = 1; i <= n; i++) b[i] = a[i] & ((1 << (k + 1)) - 1);
	sort(b + 1, b + n + 1);
	return calc(1 << k, (1 << (k + 1)) - 1) ^ calc(3 << k, (1 << (k + 2)) - 2);
}

int main() {
	rd(n), rda(a, n);
	for (int i = 0; i < 26; i++) ans |= solve(i) << i;
	print(ans);
	return 0;
}
```

---

## 作者：gyh20 (赞：13)

按位计算。

两个数第 $k$ 位的和，仅跟前 $k$ 位有关。

计算第 $k$ 位时，将所有数对第 $k+1$ 位取模，对于位置 $i,j$，两个数的和第 $k$ 位有值当且仅当 $2^k \leq a_i+a_j<2^{k+1}$ 或 $a_i+a_j>=2^{k+1}+2^k$。

可以排序一遍然后二分/双指针求解，有值的个数即为和大于等于 $2^k$ 的个数 $-$ 和大于等于 $2^{k+1}$ 的个数 $+$ 和大于等于$2^{k+1}+2^k$ 的个数，然后判断奇偶性即可 。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int n,a[400002],ans[32],b[400002],f;
signed main(){
	n=read();
	for(re int i=1;i<=n;++i){
	b[i]=a[i]=read();
	}
	sort(a+1,a+n+1);
	for(re int i=0;i<=25;++i){
		int l=1;
		for(re int j=1;j<=n;++j)a[j]=b[j]%(1<<(i+1));
		sort(a+1,a+n+1);
		for(re int j=n;j;--j){
			while(a[j]+a[l]<(1<<i)&&l<j)++l;
			if(l>=j)break;
			ans[i]+=j-l;
		}		
		l=1;
		for(re int j=n;j;--j){
			while(a[j]+a[l]<((1<<(i+1)))&&l<j)++l;
			if(l>=j)break;
			ans[i]-=j-l;
		}
		l=1;
		for(re int j=n;j;--j){
			while(a[j]+a[l]<((1<<(i+1))+(1<<i))&&l<j)++l;
			if(l>=j)break;
			ans[i]+=j-l;
		}
	}
	for(re int i=0;i<=25;++i){

		f+=(ans[i]&1)*(1<<i);
	}
	printf("%d",f);
}
```


---

## 作者：Clouder (赞：8)

值域很奇怪，考虑按位处理。  

枚举第 $i$ 个数的第 $k$ 位，统计所有 $a_i + a_j$ 中第 $k$ 位为 $1$ 的个数，根据奇偶性判断答案第 $k$ 位的值。  
   
可以发现，第 $k$ 位的取值仅与前 $k$ 位有关。  

令 $b_i = a_i \text{ and } (2^{k+1} - 1)$，那么仅考虑 $b_j + b_i$ 即可确定第 $k$ 位取值。  

$b_i + b_j$ 何时第 $k$ 位为 $1$？当 $b_j + b_i \in [2^k,2^{k+1}-1]$ 时肯定成立，但还要考虑第 $k$ 位进位后又被第 $k-1$ 位进位为 $1$，因此 $b_j + b_i \in [2^{k+1} + 2^k,2^{k+2} - 2]$ 同样是合法的。  

这个东西当然可以大力树状数组维护，时间复杂度 $O(n \log^2 a_i)$，不太可行。  

可以考虑按 $b_i$ 排序，然后用双指针来统计个数，可以做到 $O(n \log n \log a_i)$，应该能过。  

然后这里排序可以用归并排序，这样就能稳定通过了。  

时间复杂度 $O(n \log a_i)$.  

```cpp
#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 4e5 + 100;
int n, a[maxn], b[maxn], id[maxn], maxx, ans;
int L[maxn], Lid[maxn], R[maxn], Rid[maxn];
void mergesort(int k)
{
    int lnum = 0, rnum = 0;
    for (int i = 1; i <= n; ++i)
        if (a[id[i]] & (1 << k)) R[++rnum] = b[i] | (1 << k), Rid[rnum] = id[i];
        else L[++lnum] = b[i], Lid[lnum] = id[i];
    int p1 = 1, p2 = 1, p = 1;
    while (p1 <= lnum && p2 <= rnum)
        if (L[p1] <= R[p2]) b[p] = L[p1], id[p++] = Lid[p1++];
        else b[p] = R[p2], id[p++] = Rid[p2++];
    while (p1 <= lnum) b[p] = L[p1], id[p++] = Lid[p1++];
    while (p2 <= rnum) b[p] = R[p2], id[p++] = Rid[p2++];
}
int count(int ll, int rr)  // count how many in [ll,rr] using two pointer
{
    int bitnum = 0, l = 1, r = n;
    for (int i = n; i; L[i--] = l)
        while (l < i && b[l] + b[i] < ll) ++l;
    for (int i = 1; i <= n; R[i] = std::min(i - 1, r), ++i)
        while (r > 0 && b[i] + b[r] > rr) --r;
    for (int i = 2; i <= n; ++i)
        if (R[i] >= L[i]) bitnum += R[i] - L[i] + 1;
    return bitnum;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), maxx = std::max(maxx, a[i]);
    for (int i = 1; i <= n; ++i) id[i] = i;
    for (int k = 0; (1 << k) <= (maxx << 1); ++k)
    {
        mergesort(k);
        int bitnum = count(1 << k, (1 << (k + 1)) - 1) + count((1 << k) + (1 << (k + 1)), (1 << (k + 2)) - 2);
        if (bitnum & 1) ans |= 1 << k;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：HPXXZYY (赞：6)

$\color{blue}{\texttt{[Solution]}}$

因为是二进制的操作，所以我们考虑二进制下的答案（下面的讨论是针对二进制的）。

显然每一位是互相独立的，所以我们只考虑第 $k$ 位，最后在统计每一位的答案即为总答案。

记 $b_{i}=a_{i} \mod \left ( 2^{k+1} -1 \right )$，即 $a_{i}$ 的末 $k$ 位值。

如果第 $k$ 位对答案有贡献，则代表有奇数个 $b_{i}+b_{j}$ 的第 $k$ 位为 $1$。

现在的问题是，如何求出有多少对 $(i,j)$ 满足 $b_{i}+b_j$ 的第 $k$ 位为 $1$。

如果 $b_{i}+b_{j} \in [2^k,2^{k+1}-1]$，那么 $(i,j)$ 是满足条件的。

但是我们还要考虑这样的情况：第 $k$ 位进位了，然后第 $k-1$ 位进位了，最后第 $k$ 位为 $1$。这个情况有点复杂，但是我们可以证明，此时 $b_i+b_j \in [2^{k+1}+2^k,2^{k+2}-2]$。

现在的问题是，如何快速的求出有多少对 $(i,j)$ 满足 $b_{i}+b_{j} \in[L,R]$。

显然，$b$ 数组内部的顺序对答案没有影响，所以我们将 $b$ 数组排序。然后的事情就可以用 `Two-pointers` 解决了。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=4e5+100;
int a[N],b[N],n,ans;
inline int count(int u,int v){
	register int sum=0;//统计和 
	for(int i=n,l=1,r=1;i>=1;i--){// *1
		while (l<=n&&b[i]+b[l]<u) l++;
		while (r<=n&&b[i]+b[r]<=v) r++;
		sum+=r-l-(l<=i&&i<r);//*2 
	}
	return (sum>>1)&1;//*3
}
inline int calc(int k){
	for(int i=1;i<=n;i++)
		b[i]=a[i]&((1<<(k+1))-1);
	sort(b+1,b+n+1);//记得排序 
	return count(1<<k,(1<<(k+1))-1)^count(3<<k,(1<<(k+2))-2);
}
inline void calc_answer(){
	for(int i=0;i<27;i++)
		ans+=calc(i)<<i;
}
int main(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)
		a[i]=read();
	calc_answer();
	printf("%d",ans);
	return 0;
}
```

需要注意的代码细节：

1. 代码 $1$ 处，注意 $i$ 应该是倒序枚举，否则 `Two-pointers` 是错的。
2. 代码 $2$ 处：注意当 $i \in [l,r]$ 时，$i$ 是不能算入 $\texttt{sum}$，因为任意 $(i,i)$ 都是不合法的。
3. 代码 $3$ 处：注意上面我们把每个 $(i,j)$ 算了两次（$i$ 一次，$j$ 一次），所以注意先除以二。
4. 代码涉及位运算处：注意位运算的优先级低于加减，所以勤加括号。

---

## 作者：do_while_true (赞：3)

看上去异或里面套了层加法不好拆位，但是依然可以对每个二进制位处理。

现在考虑第 $k$ 位，那么产生贡献的数字对一定满足以下条件之一：

- 第 $k$ 位相同且前 $(k-1)$ 位进位；
- 第 $k$ 位不同且前 $(k-1)$ 位不进位。

那就按照前 $(k-1)$ 位排序，然后能产生进位的一定是一个后缀，所以维护一个前缀第 $k$ 位是 $1$ 的个数，然后双指针就能算合法的数字对个数了。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
const int N=400010;
int bit(int x){
	return 1<<x;
}
int all(int x){
	return (1<<x)-1;
}
int n,a[N],s[N];
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	int ans=0;
	for(int o=0;o<=24;o++){
		ll sum=0;
		if(!o){
			for(int i=1;i<=n;i++)s[i]=((a[i]>>o)&1)+s[i-1];
			for(int i=1;i<=n;i++){
				if(a[i]&bit(o))
					sum+=i-1-s[i-1];
				else
					sum+=s[i-1];
			}
			if(sum&1)ans|=bit(o);
		}
		else{
			sort(a+1,a+n+1,[&](const int &x,const int &y){return (x&all(o))<(y&all(o));});
			for(int i=1;i<=n;i++)s[i]=((a[i]>>o)&1)+s[i-1];
			int p=n+1;
			for(int i=1;i<=n;i++){
				while(p>=1&&(((a[p-1]&all(o))+(a[i]&all(o)))&bit(o)))--p;
				//[p,n]进位
				//[1,p-1]不进位
				if(a[i]&bit(o)){
					sum+=p-1-s[p-1];
					sum+=s[n]-s[p-1];
				}
				else{
					sum+=s[p-1];
					sum+=(n-p+1)-(s[n]-s[p-1]);
				}
				sum-=p<=i;
			}
			sum/=2;
			if(sum&1)ans|=bit(o);
		}
	}
	cout << ans << '\n';
    #ifdef do_while_true
//		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：UperFicial (赞：2)

$\text{update 2022.9.8}$：经 @wuxikui 指正，更改了复杂度。

看到位运算先按位考虑，因为每一位相互独立。

对于两个数 $x,y$，我们计算 $x+y$ 是否在二进制下对第 $k$ 位有贡献，实际上是考虑 $x+y$ 在模 $2^{k+1}$ 意义下对第 $k$ 位是否有贡献，因为第 $k$ 位之后的那些位我们是不用考虑的。


那么对于在模 $2^{k+1}$ 意义下 $x+y$ 的和 $z$，我们分情况进行讨论。

对于 $x+y$ 不进位的情况。如果 $z\in [2^k,2^{k+1}-1]$，那么说明第 $k$ 位是 `1`，因为 $z$ 的最高位不可能为 $0$。

对于 $x+y$ 进位的情况，最多也只可能进一位，也就是说需要满足 $z$ 的第 $k$ 位，和第 $\left(k+1\right)$ 位都为 `1`。

$z$ 最大为 `11111...`，这个东西可以表示成 $2^{k+2}-1$，最小为 `11000...`，这个可以理解成 $2^k$ 左移了一位，然后又加上了 $2^k$，即 $2^k\times 2+2^k$。

所以得到 $z\in [2^k+2^{k+1},2^{k+2}-1]$。

根据异或的性质，第 $k$ 位只有有奇数对儿 $(x,y)$ 使得它们的和 $z$ 在模 $2^{k+1}$ 意义下恰好是在上述任意一区间内，那么第 $k$ 位才有贡献。

如何算这个对数就很简单了，我们把每个数在模 $2^{k+1}$ 下的结果排一个序，双指针维护即可。

复杂度 $\Theta\left(n\log V\log n\right)$。

细节问题代码中都有注释：

```cpp
inline bool solve(int k)
{
	rep(i,1,n) b[i]=a[i]%(1<<(k+1));
	int l1=1<<k,r1=(1<<(k+1))-1;
	int l2=(1<<k)+(1<<(k+1)),r2=(1<<(k+2))-1;//合法的两个区间 
	sort(b+1,b+1+n);
	int j1(1),j2(1);
	ll sum=0;
	rev(i,n,1)
	{
		while(j1<=n&&b[i]+b[j1]<l1) ++j1;//一直找直到找到 b[i]+b[j1]>=l1 
		while(j2<=n&&b[i]+b[j2]<=r1) ++j2;//一直找直到找到 b[i]+b[j2]>r1
		//合法的区间为 [l1,r1-1] 
		sum+=j2-j1;
		if(j1<=i&&i<j2) --sum;//i 自己不能和自己匹配。 
	}
	j1=1,j2=1;
	rev(i,n,1)
	{
		while(j1<=n&&b[i]+b[j1]<l2) ++j1;
		while(j2<=n&&b[i]+b[j2]<=r2) ++j2;
		sum+=j2-j1;
		if(j1<=i&&i<j2) --sum; 
	}
	sum>>=1;
	return sum&1;
}

int main()
{
//	freopen("read2 .txt","r",stdin);
	n=read();
	rep(i,1,n) a[i]=read();
	int ans(0);
	rep(i,0,26) ans|=(solve(i)<<i);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：RockyYue (赞：1)

### 题意

求 $\bigoplus_{1\le i<j\le n}{(a_i+a_j)}$，其中 $2\le n\le 4\times 10^5,1\le a_i\le 10^7$

### 解法

异或求和题考虑：

①对于每个 $i$ 求和所有 $j$。

②考虑答案每一位。

这里加起来异或的操作不适合对于每个 $i$ 分别处理，考虑处理答案每一位，设当前处理到答案第 $k$ 位。

则要求使得 $a_i+a_j$ 二进制第 $k$ 位为 $1$ 的有序二元组 $(i,j)$ 的个数，第 $k$ 位取决于 $a_i$ 和 $a_j$ 的第 $k$ 位和更小位的进位，故更大的位不予考虑，即 $a_i=a_i \bmod 2^{k+1}$，此时 $a_i+a_j\in [2^k,2^{k+1}-1]$ 或 $[2^{k+1}+2^{k},2^{k+2}-2]$（因为取模后最大就是 $2\times (2^{k+1}-1)$）。此时我们对于每个 $a_i$ 分别处理出 $a_j$ 的范围即可，最后求和由奇偶性得出答案第 $k$ 位。

---

## 作者：hleternity (赞：0)

## 简单题意

求 $ \bigoplus_{i=1}^n \bigoplus_{j=i+1}^n (a_i+a_j) $ 。

## 思路

- 首先由于考虑将每个数改为二进制，考虑每一位对答案的贡献。

- 由于只有一种运算异或,所以答案 $ans=\sum_{i=0}^{+\infty}(cnt_i \bmod 2)2^i$ 。 

- 我们对第 $i$ 位考虑，那么能对第 $i$ 为做贡献的只有前 $i$ 位，设第 $j$ 个数的前 $i$ 位为 $b_j$ ，则 $b_j=a_j \bmod 2^{i+1}$ 。

- 我们接着考虑这一位能作贡献当且仅当这一位上为 $1$ ,那么能在第 $i$ 位上为 $1$ ,有两种情况：

  1.第 $i$ 位上不进位。那么 $b_i+b_j \in [2^i,2^{i+1}-1]$ 。

  2.第 $i$ 位上不进位。那么 $b_i+b_j \in [2^{i+1}+2^i,2^{i+2}-2]$ 。注意这里的右边界是减 $2$ ，因为第 $i$ 位发生进位后认为 $1$ ,那么前 $i-1$ 位也一定向前进位了。

- 那么最后第 $i$ 位上为 $1$ ，当且仅当 $cnt_1+cnt_2$ 为奇数。

- 现在问题转化为给定 $n$ 个数，选择两个互不相同的数，使两数之和在一个区间内。问这样的数对有多少个。

  - 直接将原数组从小到大排序，维护一个双指针。
  - 从后往前扫，找到每个数对应的合法区间 $[l,r]$ 。同时若第 $i$ 个数在这个区间内，应将其减去。
  - 最后由于每个合法数对会算两遍，所以还要除二。

---

## 作者：baoziwu2 (赞：0)

传统的遍历计数显然不能满足题目的需求，因此我们直接考虑能够对答案造成贡献的因素，即 $(a_i + a_j)$ ，由于答案的每一位不会互相影响，所以按位考虑。

考虑对 $(ans)_2$ 中第 $pos$ 位能造成的贡献情况有：

- 在没有进位的情况下，若干个 $(a_i + a_j)$ 的异或和上第 $pos$ 位为$1$。 $(1)$
- 在有进位的情况下，若干个 $(a_i + a_j)$ 的异或和上第 $pos$ 位为 $0$，第 $pos - 1$ 位进位 $1$。 $(2)$

这两种情况对答案第 $pos$ 位造成贡献当且仅当上述两个命题异或后为 $1$。

更高位不会影响当前的答案，所以可以略作简化：

建立一个 $b$ 序列，满足 $b_i = a_i \mod 2^{pos + 1}$。

在 $b$ 序列中对于两个位置 $i, j$ ，两个数的和在第 $k$ 位为 $1$ 情况分别有：

- 不进位：$ 2^{k} \leq b_{i}+b_{j} \leq 2^{k+1} - 1$ 。
- 进位：$ 2^{k+1}+2^{k} \leq b_{i}+b_{j} \leq 2\times (2^{k + 1} - 1)$。

使得 $(1)$ 为真的贡献的只有满足 $2^{k} \leq b_{i}+b_{j} \leq 2^{k+1} - 1$ 中二元组 $(b_i, b_j)$ 的个数除以 $2$ 后为奇数。

使得 $(2)$ 为真的贡献只有满足 $2^{k+1}+2^{k} \leq b_{i}+b_{j} \leq 2\times (2^{k + 1} - 1)$ 中二元组 $(b_i, b_j)$ 的个数除以 $2$ 后为奇数。

发现 $b$ 序列中各元素顺序对答案无影响，因此考虑排序后利用单调性，采用双指针求解。

代码如下：

```C++
#include <iostream>
#include <algorithm>

using namespace std;

int const N = 4e5 + 5;

int n, a[N];

inline void read(int &n) {
	int res = 0, f = 1; char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) {
		res = res * 10 + c - '0';
		c = getchar();
	}
	n = res * f;
}

class solution {
	int b[N];

	inline bool check(int l, int r) {
		if(l > r) return 0;
		int res = 0;
		for(int i = n, ql = 1, qr = 1; i; -- i) {
			while(ql <= n and b[i] + b[ql] < l) ++ ql;
			while(qr <= n and b[i] + b[qr] <= r) ++ qr;
			res += qr - ql - (ql <= i and i < qr);
		}
		return (res >> 1) & 1;
	}

	inline bool solve(int pos) {
		for(int i = 1; i <= n; ++ i)
			b[i] = a[i] & ((1 << pos + 1) - 1);
		sort(b + 1, b + 1 + n);
		return check(1 << pos, (1 << pos + 1) - 1) xor check((1 << pos + 1) + (1 << pos), ((1 << pos) - 1) << 1);
	}
  public:
	inline int getAns() {
		int ans = 0;
		for(int i = 0; i < 31; ++ i)
			ans |= solve(i) << i;
		return ans;
	}
} sol;

int main() {
	read(n);
	for_each(a + 1, a + 1 + n, read);

	printf("%d\n", sol.getAns());

	return 0;
}
```

---

## 作者：Yansuan_HCl (赞：0)

异或是困难的，因此考虑**按位处理**（重要的思想）。每次考虑最终答案的第 $k$ 位，其值就是所有和中**第 $k$ 位为 $1$ 的个数**的奇偶性。

和的第 $k$ 位是否为 $1$ 和更高位没有关系。可设 $b_i = a_i \bmod 2^{k+1}$，则 $\forall i,j, x=b_i + b_j \in [0,2^{k+1}-2]$。若 $x$ 的第 $k+1$ 位是 $0$，则 $x \in [2^k, 2^{k+1}-1]$；若是 $1$，则 $x \in [2^{k+1}+2^k, 2^{k+1}-2]$。

发现值域是两个连续段组成的，可以排序后双指针维护。

[代码](https://www.luogu.com.cn/paste/3a04l6vc)

---

## 作者：vectorwyx (赞：0)

明明 noip 考前还推出过类似结论，再见到就一窍不通了……

拆位，问题转为一个包含 $n$ 个二进制数的序列，问选出任两个数满足它们和的第 $i$ 位为 $1$ 的方案数。

先只保留前 $i$ 位，然后分类讨论。如果第 $i$ 位上没有进位那么 $a_i+a_j\in[2^i,2^{i+1})$，否则 $a_i+a_j\in[2^i+2^{i+1},2^{i+1}+2^{i+1})$。排序后双指针即可，复杂度 $O(n\log{a_i}\log n)$，如果采用基排，时间复杂度会降为 $O(n\log a_i)$。

btw，这个结论也可以拓展到 $p$ 进制下，把上述式子中的 $2$ 替换为 $p$ 即可。

代码如下：

```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

const int N=1e6+5;
int a[N],n,b[N],pw[N],ans;

signed main(){
	cin>>n;
	fo(i,1,n) a[i]=read();
	pw[0]=1;fo(i,1,25) pw[i]=pw[i-1]<<1;
	fo(t,0,24){
		fo(i,1,n) b[i]=a[i]%pw[t+1];
		sort(b+1,b+1+n);
		//out(b,1,n);
		int l=1,r=1,cnt=0;
		go(i,n,1){
			int x=pw[t]-b[i],y=pw[t+1]-1-b[i];
			while(l<=n&&b[l]<x) l++;
			while(r<=n&&b[r]<=y) r++;
			cnt+=r-l;
		}
		l=r=1;
		go(i,n,1){
			int x=pw[t]-b[i]+pw[t+1],y=pw[t+1]-1-b[i]+pw[t+1];
			while(l<=n&&b[l]<x) l++;
			while(r<=n&&b[r]<=y) r++;
			cnt+=r-l;
		}
		fo(i,1,n) if((b[i]+b[i])>>t&1) cnt--;
		cnt/=2;
		if(cnt&1) ans|=pw[t];
	}
	cout<<ans;
	return 0;
}
/*
-------------------------------------------------
*/
```

 



---

## 作者：盧鋅 (赞：0)

### B. Present（*2100）

对于位运算我们考虑按位贡献，考虑答案第K位，即考虑所有和的第K位的数量的奇偶性，我们考虑如何在第K位产生贡献，首先两个不超过K位的二进制数最大能表示$2^{k+1}-1$，所以两数的和最大为$2^{k+2}-2$，假如在第K位产生贡献即第K位为1，那么两数和应该在
$$
[2^k,2^{k+1}-1] \cup [2^{k+1}+2^k,2^{k+2}-2]
$$
范围内，假定我们确定一个数$t$，那么另一个数$ans$，应该满足一下条件：
$$
\forall ans \in [2^k-t,2^{k+1}-1-t] \cup [2^{k+1}+2^k-t,2^{k+2}-2-t]
$$
那么显然的是，假如$t < 2^k$，那么$\forall ans+t \notin [2^{k+1}+2^k,2^{k+2}-2]$这时候我们只要利用前缀和去统计属于$[2^k-t,2^{k+1}-1-t]$范围内的值即可。

假如$t\ge2^k$，那么$2^k \le\forall ans+t \le 2^{k+2}-2$，这时候我们考虑不产生贡献的区间即$(2^{k+1}-1,2^{k+1}+2^k)$，同理我们可以利用容斥原理和前缀和计算出产生的贡献。

最后我们要考虑自身产生的贡献，若自身产生贡献，应当消除，由于重复计算，结果应/2。

~~关于复杂度，这不很明显吗？（ε=ε=ε=┏(゜ロ゜;)┛~~

~~~c++
const int maxn = 400000+5;
int sum[1<<25],num[maxn],n;
signed main(){
    read(n);
    FOR(i,1,n)read(num[i]);
    int ans=0;
    for(int len=2;len<=(1<<25);len<<=1){
        memset(sum,0,sizeof sum);
        int u=len>>1,v=len-1;
        FOR(i,1,n)sum[num[i]&v]++;
        FOR(i,1,len-1)sum[i]+=sum[i-1];
        ll s=0;
        FOR(i,1,n){
            int t=(num[i]&v);
            int l=((u-t+len)&v),r=v-t;
            if(l<=r)s+=(sum[r]-sum[l-1]);
            else s+=n-(sum[l-1]-sum[r]);
            if(((t+t)&v)>=u)s--;
        }
        s>>=1;
        if(s&1)ans^=u;
    }
    Write(ans);
    return 0;
}
~~~



---

