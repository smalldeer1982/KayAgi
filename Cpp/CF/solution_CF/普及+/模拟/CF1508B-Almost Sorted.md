# Almost Sorted

## 题目描述

Seiji Maki doesn't only like to observe relationships being unfolded, he also likes to observe sequences of numbers, especially permutations. Today, he has his eyes on almost sorted permutations.

A permutation $ a_1, a_2, \dots, a_n $ of $ 1, 2, \dots, n $ is said to be almost sorted if the condition $ a_{i + 1} \ge a_i - 1 $ holds for all $ i $ between $ 1 $ and $ n - 1 $ inclusive.

Maki is considering the list of all almost sorted permutations of $ 1, 2, \dots, n $ , given in lexicographical order, and he wants to find the $ k $ -th permutation in this list. Can you help him to find such permutation?

Permutation $ p $ is lexicographically smaller than a permutation $ q $ if and only if the following holds:

- in the first position where $ p $ and $ q $ differ, the permutation $ p $ has a smaller element than the corresponding element in $ q $ .

## 说明/提示

For the first and second test, the list of almost sorted permutations with $ n = 1 $ is $ \{[1]\} $ .

For the third and fifth test, the list of almost sorted permutations with $ n = 3 $ is $ \{[1, 2, 3], [1, 3, 2], [2, 1, 3], [3, 2, 1]\} $ .

## 样例 #1

### 输入

```
5
1 1
1 2
3 3
6 5
3 4```

### 输出

```
1 
-1
2 1 3 
1 2 4 3 5 6 
3 2 1```

# 题解

## 作者：Alex_Wei (赞：17)

> [题目传送门](https://www.luogu.com.cn/problem/CF1508B)。

> 题意简述：定义一个排列 $a_1,a_2,\cdots,a_n$ 是 “几乎有序” 的，当且仅当对于每一个位置 $i\ (1\leq i<n)$，满足 $a_{i+1}\geq a_i-1$。请求出长度为 $n$ 的所有 “几乎有序” 的排列中，字典序第 $k$ 小的那一个。
> 多组询问，$1\leq \sum n\leq 10^5$，$1\leq k\leq 10^{18}$。

---

考虑一个 “几乎有序” 的排列满足什么性质：给定的 $a_{i+1}\geq a_i-1$ 保证了**相邻的若干个递减的数，一定是依次减 $1$ 的**。因此，最终排列的形式一定是 $b_1,b_1-1,\cdots,1,b_2,b_2-1,\cdots,b_1+1,\cdots,n,n-1,\cdots,b_c+1$ 。

上面的形式又可以这样描述：将 $1\sim n$ 从左到右排成一排，相邻的两个数间有空隙。现在选择若干（设为 $c$）个空隙，并将这个排列切成 $c+1$ 段区间（也就是在 $b_1,b_2,\cdots,b_c$ 右边切一刀），将每一段区间翻转，就可以得到一个 “几乎有序”的排列。

不难发现，每一种切割方案，就对应了一个 “几乎有序” 的排列。反过来，如果有一个 “几乎有序” 的排列，那么我们就可以构造出相应的切割方案。也就是说，**切割方案与符合条件的排列是一一对应的**。

切割方案有 $2^{n-1}$ 个（$n-1$ 个空隙可以选择切或不切），所以 “几乎有序” 的排列个数就是 $2^{n-1}$。

至于字典序，可以证明：如果将所有空隙是（$0$）否（$1$）切割看成一个**从左往右**的二进制数，设其十进制数值为 $v$，那么该排列在所有长度为 $n$ 的 “几乎有序” 的排列中，字典序第 $v+1$ 小。

简要证明：设长度为 $n$ 的二进制数从左到右的每一位分别为第 $1,2,3,\cdots,n$ 位。考虑两个**二进制数** $x,y$，不妨设 $x>y$。假设它们对应的切割方案所得到的排列为 $ax,ay$，那么因为 $x>y$，我们总能找到一个位置 $i$ 使得 $x,y$ 的前第 $i-1$ 位都相同，且 $x$ 的第 $i$ 位为 $1$，$y$ 的第 $i$ 位为 $0$。注意 $1$ 代表不切割，$0$ 代表切割。这样一来，如果 $ay_p=i$，那么 $ax_p>i$，且 $p$ 之前的所有位置 $j\ (1\leq j<p)$ 都有 $ax_j\geq ay_j$。得证。

代码比较好写，注意特判一下 $n\geq 62$ 的情况（此时 $2^n>k$）

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n,k;
void solve(){
	cin>>n>>k,k--;
	if(n<62&&k>>n-1)return puts("-1"),void();
	for(int i=1,p=1;i<=n;i=p+1,p=i){
		while(p<n&&n-p<=62&&(k>>n-p-1)&1)p++;
		for(int j=p;j>=i;j--)cout<<j<<" ";
	} cout<<endl;
}

int main(){
	int t=1;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Eibon (赞：4)

因为 $a_{i} = a_{i+1}+1$，或者 $a_{i} \le a_{i+1}$，所以一个合法的序列，如果有下降区段，则必然是由1到n的序列被划分成若干段，然后翻转得来的。

因为 $n$ 个数有 $n-1$ 个间隙，每个间隙都可以选择插或不插，所以最终方案数为 $2^{n-1}$。

容易发现，将插入视为 $1$，不插入视为 $0$ 所构成的二进制数，转为的十进制数加一即为其大小排名。因为插得越往后，翻转过来所占的权重就越小，排名也就越小。

[Alex_Wei](https://www.luogu.com.cn/user/123294) 大佬的[代码](https://www.luogu.com.cn/article/00wuxqlm)有些抽象，解释一下。

$k$ 先默认减一，因为十进制数加一即为其大小排名，这里减去好使下面操作方便。

```cpp
k>>n-1
```
表示k在右移 $n-1$ 位后，即除去 $2^{n-1}$ 后的值。这里现将 $k$ 减 $1$，因为 $k \le 2^{n-1}$，除完后，判断是否大于 $1$ 即可。

```cpp
p<n&&n-p<=62&&(k>>n-p-1)&1
```

$p<n$ 很好理解，因为插板子不能插在数组外面。

$n-p \le 62$，因为 $k$ 的值不能大于 $2^{62}$，在此之前只要按照顺序输出即可。

当前位在 $p$，如果 $p+1$ 也合法，则 $k$ 中 $p+1$ 位必须要有 $1$，才能接着插。

最后 $i$ 和 $p$ 即为需要翻转的左端点和右端点，倒序输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int T,n,k,ans,cnt;
int a[maxn];
signed main()
{
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		if((k-1)>>(n-1)&&n<=62){//2^(n-1)>=k
			printf("-1\n");
			continue;
		}
		k--;
	    for(int i=1,now=1;i<=n;i=now+1,now=i){
			while(now<n&&n-now<=62&&(k>>(n-(now+1)))&1){
				now++;
			}
			for(int j=now;j>=i;j--){
				printf("%lld ",j);
			}
		}
		printf("\n");
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Cry_For_theMoon (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1508B)

感谢这个 2E 让我上紫大成功

注意到定义都是针对相邻元素的：

- $a_i<a_{i+1}$ （排列，所以忽略等于）

或

- $a_i=a_{i+1}+1$

条件二比较特殊，我们发现它对应 $k,k-1,k-2,...,k-l+1$ 这样一条每次都减去 $1$ 的**子段**。我们称其为**链**

我们不妨在 $n,n-1,...,1$ 这 $n$ 个数上作划分，划分出来的每一段都是最后符合要求的排列的一个**极长**链。然后对这些链调整顺序形成一个排列。

注意到链的顺序是有要求的。具体地，应该满足第 $i$ 条链的结尾小于第 $i+1$ 条链的开头。这个约束让每一种划分方案**有且只有一种排列方案**，同时也告诉我们**不同划分方案得到的排列不同**。所以总的符合要求排列数量等于划分方案数，即 $2^{n-1}$.

既然答案按照字典序排列，显而易见的套路是枚举首元素，计算以该元素开头的方案数，如果次序小于等于方案数就确定了第一位，否则增加。但这样时间似乎比较危险。

似乎陷入了死路一条。

然后考虑首项是 $2$. 你会发现 $1$ 必须跟在 $2$ 后面

拓展，不难发现，如果首元素是 $k$，那么前 $k$ 个元素依次是 $k,k-1,k-2,...,1.$ 这里给出一个简单的证明：

$k=1$ 不用证了。

$1$ 要么放最前面，要么放 $2$ 后面，最前面是 $k$ 了所以 $1$ 只能放 $2$ 后面。$2$ 同理得放在 $3$ 的后面，...,直到 $k$，它本身就在第一个。

所以如果我们选择首项为 $k$，实际上开头就填了前 $k$ 小的元素。此时**剩下部分的方案数转成了一个子问题。**

然后就可以直接枚举首项，缩减成子问题，重复这个过程了（我还是建议写递归不容易错）。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const ll INF=2e18;
ll T,n,k;
ll power(ll a,ll n){
	if(n>60)return INF;
	if(n==0)return 1;
	ll tmp=power(a,n/2);tmp*=tmp;
	if(n&1)tmp*=a;return tmp;
}
void solve(){
	cin>>n>>k;
	if(k>power(2,n-1)){
		printf("-1\n");return;
	}
	int now=1;
	while(true){
		rep(i,1,n){
			if(i+now-1>n)break;
			if(k<=power(2,n-now-i)){
				per(j,now+i-1,now){
					printf("%d ",j);
				}
				now+=i;break;
			}else k-=power(2,n-now-i);
		}
		if(now>n)break;
	}
	printf("\n");
}
int main(){
	cin>>T;
	while(T--){
		solve();	
	}
	return 0;
}
```


---

## 作者：LTb_ (赞：3)

提供一个比较神秘的解法

除了我估计没人会写这种东西（捂脸

观察一个 *almost sorted* 的序列，它应当是许多个公差为 $-1$ 的等差序列拼在一起的形式

考虑长度为 $n$ 的 *almost sorted* 序列的个数 $f_n$，不难得到 $f_n = 1 + \sum\limits_{i=1}^{n-1} f_i$，也即 $f_n = 2^{n-1}$——因为 $n$ 是当前排列中最大的数，在它的序列之后一定是 $\left < n-1, n-2, n-3 \cdots \right >$ 直到序列末尾（当然最后一个数不一定是 $1$），在它之前的序列是一个长度小于 $n$ 的 *almost sorted* 序列。枚举 $n$ 在序列中的位置即得到上式。

然后注意到 $k$ 的范围仅仅是 $10^{18} \approx 2^{60}$，也就是说当 $n$ 超过 $60$ 的时候最终的序列前面一定是 $\left<1, 2, 3 \cdots \right>$。于是对前 $n-z$ 位输出 $1 \sim n-z$，对后 $z$ 位做一个 $z^2$ 暴力依次确定每一个位置的值，其中 $z \ge 60$。这部分的复杂度显然是个常数，于是整个算法的时间复杂度为 $O(n)$。

[赛时代码](https://codeforces.com/contest/1509/submission/113256152)



---

## 作者：TLE_Automat (赞：2)

## [CF 1509E(div.2) & 1508B(div.1)](https://codeforces.com/contest/1509/problem/E)

**题意：**

定义一个 $1$ 到 $n$ **排列**是 ```almost sorted``` 的，当且仅当这个排列满足 $\forall i\in[1,n) \wedge i\in \mathbf{Z} , p_i-1\le p_{i+1}$ 。

现在给定整数 $n$ 和 $k$ ，输出 $1$ 到 $n$ 的所有排列中字典序第 $k$ 小的 ```almost sorted``` 的排列。

**数据范围：**

$n\le 10^5 , k\le 10^{18}$ 。

**解题过程：**

第一眼感觉这题十分不可做，根本找不到突破口，那肯定要根据题意挖掘性质。

这个东西是个排列，并且要满足 $p_i -1 \le p_{i+1}$ ，根据这点能发现 $p$ 的**单调子区间**只有两种情况：

- 单调递增，从前到后依次 $+1$ ，形成一个上升的**覆盖连续值域**的区间。

- 单调递减，从前到后依次 $-1$ ，形成一个下降的**覆盖连续值域**的区间。

画成图大概长这个样子：

**然而我想到这里就不会做了，过了两天看了几眼官方题解，才明白做法。**

![](https://cdn.luogu.com.cn/upload/image_hosting/ilmrltp3.png)

根据以上性质，通过这个图可以直观地发现，一个合法排列，一定可以由排列 $1,2,...,n$ 翻转一些不相交的子段获得，并且与翻转方式一一对应。（简单证明就是因为上面两点性质，并且后面的单调递增的区间没法移到前面来，否则不合法）

**其实想到这里这题基本上已经做完了，可惜当时没有深入发掘到区间 $\text{reverse}$ 这点性质，为啥结论就在眼前，但我却看不出来呢？**

分析到这一步，可以比较轻松得到长度为 $n$ 的合法排列的个数就是 $2^{n-1}$ ，插板证明即可。

然后接着就很简单了，考虑从头开始翻，由于翻的长度越大，字典序越大，所以我们可以直接枚举翻的长度，然后计算字典序比当前翻转之后的排列的字典序小的排列个数，并与 $k$ 比较，以这种方式来确定右端点。**由于多翻转一个之后产生比它字典序小的合法排列的个数指数级增长** ，所以时间复杂度为 $O(n\log_{2}(k))$ 。

**丑陋的 $\text{cpp}$ ：**

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

int n; ll kkk;
inline ll calc(int l,int r)
{
	ll res=0;
	for(int i=l;i<=r-1;i++)
	{
		if(n-i-1>=60) return (ll)2e18;
		res+=(1ll<<(n-i-1));
	}
	return res;
}

void solve()
{
	scanf("%d%lld",&n,&kkk);
		
	if(n<=60 && kkk>(1ll<<(n-1)))
	{
		puts("-1");
		return ;
	}
	
	vector<int> ans;
	int pos=1,r=-1;
	for(;r<=n;r++)
	{
		r=pos;
		while(r+1<=n && calc(pos,r+1)<kkk) r++;
//		printf("[%d , %d] and %lld\n",pos,r,calc(pos,r+1));
			
		kkk-=calc(pos,r);
		for(int i=r;i>=pos;i--)
			ans.push_back(i);
		pos=r+1;
	}
	
	assert((int)ans.size()==n);
	for(int i=0;i<n;i++) printf("%d ",ans[i]);
	puts("");
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

-------



---

## 作者：Miko35 (赞：2)

人比较蠢，没有发现 $n>60$ 必然有解的性质，不过还是二分过掉了这题。

容易发现，一个合法排列一定是将 $1,2,\dots ,n$ 中的某些互不相交的区间反转得到的。然后，如果不考虑第 $k$ 大而只考虑计数，就令 $p_n$ 表示长度为 $n$ 的合法排列的个数。

考虑这个排列的第一个数填什么，如果填 $x(x<n)$，那么前 $x$ 个数一定是 $x,x-1,x-2,\dots,1$，还剩下 $n-x$ 个数 $[x+1,n]$ 要构成一个合法的排列，也就是 $p_{n-x}$；如果填 $n$，那么整个序列一定是倒序的，只有一种。由此可得 $p_n=1+\sum\limits_{i=1}^{n-1}p_i,p_1=1$，也就是 $p_n=2^{n-1}$。

然后把第 $k$ 大加进来，朴素做法无非是从小到大枚举此位置填的数，然后计算方案数判断是否合法。令 $f(i,x)$ 表示前 $i-1$ 个数都已经填好，第 $i$ 个数填 $x$ 后序列的方案数，容易得知，$x=n$ 时 $f(i,x)=1$，反之 $f(i,x)=2^{n-x-1}$。

二分一下 $i$ 位置要填的数 $mid$，要计算的是此位置填 $i$ 至 $mid-1$ 的方案数之和，也就是 $g(i,mid)=\sum\limits_{k=i}^{mid-1}f(i,k)=2^{n-i}-2^{n-mid}$。比较其与 $k$ 的大小即可。

时间复杂度 $O(n\log n\log \log k)$，可以解决 $k$ 比 $10^{18}$ 更大的状况。

预处理 $2$ 的幂次可以做到 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define rgi register int
#define mid (l+r>>1)
#define fin(x) freopen(x,"r",stdin)
#define fout(x) freopen(x,"w",stdout)
typedef long long ll;
using namespace std;
inline void read(){}template <typename T,typename... Ts> inline void read(T& A,Ts&... As){
	T x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	A=x*f,read(As...);
}
inline void write(char a){putchar(a);}
template <typename T> inline void write(T a){
	if(a<0ll)putchar('-'),a=-a;
	if(a>9ll)write(a/10ll);
	putchar(a%10ll+'0');
}
template <typename T,typename... Ts> inline void write(T A,Ts... As){write(A),write(As...);}
const int N=100010;
ll n,t,k,a[N];
inline ll qpow(ll a,ll b){
	if(b<0)return 0;
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a;
		b>>=1,a=a*a;
	}
	return ans;
}
ll check(ll i,ll x){
	if(x==i)return 0;
	if(log2(k)+1<n-x)return k+1;
	ll tmp=qpow(2,n-x);
	if(log2(k+tmp)+1<n-i)return k+1;
	return qpow(2,n-i)-tmp;
}
signed main(){
	read(t);
	while(t--){
		read(n,k),memset(a,0,sizeof a);
		if((n==1&&k==2)||(k>2&&log2(k-1)+1>=n)){
			puts("-1");
			continue;
		}
		for(rgi i=1;i<=n;++i){
			if(a[i])continue;
			int l=i-1,r=n+1;
			while(r>l+1){
				if(check(i,mid)<k)l=mid;
				else r=mid;
			}
			k-=check(i,l);
			for(rgi j=0;l-j>=i;++j)a[i+j]=l-j;
		}
		for(rgi i=1;i<=n;++i)write(a[i],' ');
		puts("");
	}
	return 0;
}
```



---

## 作者：Little09 (赞：2)

考虑把 $n$ 个数依次填入。如果某次填到 $x$ 且 $x$ 前面存在没有填过的数字，那么必然会从 $x$ 倒退回去填完这些数。

我们设 $n$ 个数的 Almost Sort 个数是 $f_n$（$f_0=1$）。我们可以发现第一个数可以填 $1-n$ 的每一个数，如果填了 $i$ 的个数应当是 $f_{n-i}$。所以稍微转换一下变得到：

$$f_n=\sum_{i=0}^{n-1}f_i$$

好家伙，这不就是 $f_n=2^{n-1}(n\ge 1)$。

在考虑字典序的时候，我们只要从第一位开始依次填入每一个数即可。我们从小到大枚举应当填入哪一个数，如果这个数后的 Almost Sort 个数值超过剩余的字典序，就填入这个数并从这个数倒回去填它前面的数。仔细思考发现代码复杂度是线性。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(x) memset(x,0,sizeof(x))
//const ll inf=1000000000000000000; 

const int N=200001;
int n,T;
ll k; 
ll f[N];

inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 

inline ll F(ll x)
{
	if (x>61) x=61;
	return f[x];
}

void dfs(int x,ll y)
{
	if (x==n) return;
	ll res=0;
	for (int i=x+1;i<=n;i++)
	{
		if (res+F(n-i)>=y)
		{
			for (int j=i;j>=x+1;j--) cout << j << " ";
			dfs(i,y-res);
			return;
		}
		res+=F(n-i);
	}
}

void work()
{
	cin >> n >> k;
	if (n<=61&&k>f[n])
	{
		puts("-1");
		return;
	}
	dfs(0,k);
	puts("");
	return;
}

int main()
{
	f[0]=f[1]=1ll;
	for (int i=2;i<=61;i++) f[i]=f[i-1]*2ll;
	T=read();
	while (T--)
	{
		work();
	}
	return 0;
}
```


---

