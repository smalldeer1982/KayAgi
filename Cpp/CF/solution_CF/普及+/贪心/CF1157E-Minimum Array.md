# Minimum Array

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ . All elements of both arrays are from $ 0 $ to $ n-1 $ .

You can reorder elements of the array $ b $ (if you want, you may leave the order of elements as it is). After that, let array $ c $ be the array of length $ n $ , the $ i $ -th element of this array is $ c_i = (a_i + b_i) \% n $ , where $ x \% y $ is $ x $ modulo $ y $ .

Your task is to reorder elements of the array $ b $ to obtain the lexicographically minimum possible array $ c $ .

Array $ x $ of length $ n $ is lexicographically less than array $ y $ of length $ n $ , if there exists such $ i $ ( $ 1 \le i \le n $ ), that $ x_i < y_i $ , and for any $ j $ ( $ 1 \le j < i $ ) $ x_j = y_j $ .

## 样例 #1

### 输入

```
4
0 1 2 1
3 2 1 1
```

### 输出

```
1 0 0 2 
```

## 样例 #2

### 输入

```
7
2 5 1 5 3 4 3
2 4 3 5 6 5 1
```

### 输出

```
0 0 0 1 0 2 4 
```

# 题解

## 作者：「已注销」 (赞：9)

贪心，使用`std::multiset`维护

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001];
multiset<int>s;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(int i=1;i<=n;++i)scanf("%d",&a[0]),s.insert(a[0]);
    for(int x,i=1;i<=n;++i){
        auto it=s.lower_bound((n-a[i])%n);
        if(it==s.end())x=*s.begin(),s.erase(s.begin());
        else x=*it,s.erase(it);
        printf("%d ",(x+a[i])%n);
    }
}
```


---

## 作者：ModestCoder_ (赞：7)

刚刚自己研究出了一个小技巧

对于每一个$a_i$，找$n-a_i$是否存在，不存在就找$n-a_i+1,n-a_i+2$...以此类推

想到用链表去实现一个查询的操作，但是一个一个找还是太慢，这让我想到了并查集

并查集的路径压缩的思路正好可以用在这里优化链表的查找

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 200010
using namespace std;
int n, a[maxn], cnt[maxn], nxt[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int get(int x){ return cnt[x] ? x : nxt[x] = get(nxt[x]); }

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i){
		int x = read();
		++cnt[x];
	}
	for (int i = 0; i < n; ++i) nxt[i] = i + 1; nxt[n] = 0;
	for (int i = 1; i <= n; ++i){
		int x = get(n - a[i]);
		--cnt[x]; printf("%d ", (a[i] + x) % n);
	}
	return 0;
}
```


---

## 作者：rui_er (赞：5)

容易想到贪心，依次枚举每个 $a_i$，每次在可重集 $b$ 中找到比 $n-a_i$ 大的最小的数（模意义下），输出后把这个数删掉。

但是因为是模意义下，所以二分还需要断环成链，太麻烦了，因此改用并查集优化暴力。具体地，先统计每个数在 $b$ 中的出现次数，然后维护一个循环链表，链表里每个数指向比它大的最小的存在的数，再加上路径压缩优化即可。

```cpp
// Problem: CF1157E Minimum Array
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1157E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n, a[N], b[N], cnt[N], nxt[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
int find(int x) {return cnt[x] ? x : nxt[x] = find(nxt[x]);}

int main() {
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d", &a[i]);
	rep(i, 1, n) scanf("%d", &b[i]);
	rep(i, 1, n) ++cnt[b[i]];
	rep(i, 0, n-1) nxt[i] = (i + 1) % n;
	rep(i, 1, n) {
		int ans = find(n-a[i]);
		printf("%d%c", (a[i]+ans)%n, " \n"[i==n]);
		--cnt[ans];
	}
	return 0;
}
```

---

## 作者：两年打铁 (赞：3)

题目描述

给定两个长度为n的序列a和b，可以对b进行任意顺序变换，得到序列c.

对于序列c，ci=(ai+bi)%n

求得字典序最小的c序列方案。

## 分析
对于ai（ai>0）,最优的肯定是n-ai,对于ai=0的情况，最优的肯定是0,（~~废话~~）

既然要求字典序最小，那就是贪心了啦，对于任意ai找到>=最优情况的一个数就行了，

最方便的就是multiset。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int big=0x7fffffff;
void read(int &x)
{
	x=0;
	char ch=getchar();
	int pd=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			pd=-pd;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=pd;
}
void write(const int &x)
{
	char ggg[10001];
	int s=0;
	int tmp=x;
	if(tmp==0)
	{
		putchar('0');
		return;
	}
	if(tmp<0)
	{
		tmp=-tmp;
		putchar('-');
	}
	while(tmp>0)
	{
		ggg[s++]=tmp%10+'0';
		tmp/=10;
	}
	while(s>0)
	{
		putchar(ggg[--s]);
	}
}

int n,a[2000001],len;
int f[1001];
int l,r;
int ans[1000001];
multiset<int>s;
multiset<int>::iterator it;
int main()
{
	read(n);
	s.insert(big);
	s.insert(-big);
	for(register int i=1;i<=n;++i)
	{
		read(a[i]);
	}
	for(register int i=1;i<=n;++i)
	{
		int xx;
		read(xx);
		s.insert(xx);
	}
	for(register int i=1;i<=n;++i)
	{
		int fi=a[i]==0?0:n-a[i];
		it=s.lower_bound(fi);
		int now=*it;
		if(now==big)
		{
			it=s.lower_bound(0);
			now=*it;
		}
		s.erase(it);
		write((now+a[i])%n);
		putchar(' ');
	}
} 
```


---

## 作者：Frozencode (赞：2)

使用multiset从a数组第一位开始匹配，复杂度$O(nlogn)$,详见注释。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
	{
		write(x/10);
	}
	putchar(x%10+'0');
}
ll n,a[maxn],c[maxn],cur;
multiset<ll> s;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		cin>>cur;
		s.insert(cur);//将b数组插入multiset中。
	}
	multiset<ll>::iterator it;
	for(int i=1;i<=n;i++)
	{
		cur=n-a[i];//cur是对a[i]的最佳匹配值。
		it=s.lower_bound(cur);//基于multiset的有序性在其中找和匹配值最接近的。
		if(it==s.end())//如果找不到那么就用第一个值。
		{
			it=s.begin();
			c[i]=(*it+a[i])%n;
			s.erase(it);
		}
		else
		{
			c[i]=(*it+a[i])%n;
			s.erase(it);
		}
	}
	for(int i=1;i<=n;i++)cout<<c[i]<<" ";
	return 0;
}
```
大家可能有疑惑，为什么只要在set中找到值它就一定是**最优**的？

这里证明一下，反证法：
假设这个值为$a$,在它前面有一个值$b$使得$a[i]+b\ mod\ n<a[i]+a\ mod\ n$，那么：

$Case1$:如果$a[i]+a < n$，应该会找到$b$而不是找到$a$，**矛盾**。

$Case2$:$a[i]+a > n$,同理得$a[i]+b < n$,因为$a[i]+b\ mod\ n<a[i]+a\ mod\ n$，所以$a-b>n$，这与$0\leqslant b<a<n$**矛盾**，故只要在set中找到值它就一定是**最优**的。


---

## 作者：Parabola (赞：2)

### Part0.题外话

本场穿越火线最水的题...

我觉得比A还简单

~~你敢相信A暴力复杂度是正确的？~~

然后我还是太菜了，div3都才切3题...晚上精力不太好？（借 口）

### Part1.思路

乱搞就好了，由于我们要的是字典序最小的，而且你不准动A数组，所以对于i从1~n，应该优先让$C_i$小。

那换句话来说对于i从1~n我们考虑数组$A$和$B$配对的时候就用最优的$B$去匹配$A_i$

而我们知道，$A_i$如果能和$B_j = n-A_i$配对的话这样得到的$C_i$就是0

那如果不存在呢？就是第一个比$n-A_i$大的数咯

如果不存在第一个比$n-A_i$大的呢？那就整个$B$里的最小值1咯

所以mutiset搞搞就好了

### Part2.Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200000 + 5;
const int inf = 0x3f3f3f3f;

int n , A[N] , B[N] , C[N];
multiset <int> s;

int main() {
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; ++i) scanf("%d" , A + i);
	for(int i = 1 ; i <= n ; ++i) scanf("%d" , B + i) , s.insert(B[i]);
	s.insert(inf);
	for(int i = 1 ; i <= n ; ++i) {
		auto it = s.lower_bound(n - A[i]);
		if(*it == inf) it = s.begin();
		C[i] = (*it + A[i]) % n;
		s.erase(it);
	}
	for(int i = 1 ; i <= n ; ++i) printf("%d " , C[i]);
}
```


---

## 作者：Bpds1110 (赞：1)

提供一种比较蠢的考场写法。

可以发现，对于每个数，读入后模 $n$ 对于最终的答案没有影响。

因为是按字典序，所以可以考虑逐位贪心。

对于每个 $a_i$，最终对应的 $b_i$ 无非就是两种情况：$b_i$ 为 $[0, n - a_i - 1]$ 中最小的，或为 $[n - a_i, n]$ 中最小的，注意都是要**还未被选中的**。第二种情况，右边界为 $n$ 是以防 $n - a_i > n - 1$。

发现可以用桶来进行维护，并对桶进行前缀和操作。然后在桶上二分最小的出现过的位置，两种情况分类讨论，求最小即可。

然而，每次选定后，桶无法直接更新前缀和。于是，我们考虑树状数组维护。因为一开始模了 $n$，下标固然不会越界。

时间复杂度约为 $O(n \log n \log n)$，稍微慢了一点。但是能过。

注意一点，树状数组 $0$ 的下标要偏移。否则会出现死循环。


```cpp
#include <bits/stdc++.h>
#define int long long
int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

const int N = 2e5 + 10; 

int n, a[N]; 

namespace tree {
	int d[N]; 
	int lowbit(int x) { return x & -x; }
	void update(int pos, int k) {
		for (++ pos; pos <= n; pos += lowbit(pos)) d[pos] += k;
		return void();
	}
	int query(int pos) {
		int ans = 0;
		for (++ pos; pos > 0; pos -= lowbit(pos)) ans += d[pos];
		return ans; 		
	}
} using namespace tree; 

signed main() {

	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++ i) std::cin >> a[i], a[i] %= n;
	for (int i = 1; i <= n; ++ i) {
		int tmp; std::cin >> tmp;
		update(tmp % n, 1); 
	}
	for (int i = 1; i <= n; ++ i) {
		int l = 0, r = n - a[i] - 1, ans1 = -1, ans2 = -1;
		while (l <= r) {
			int mid = l + r >> 1, q = query(mid);
			if (q > 0) ans1 = mid, r = mid - 1;
			else l = mid + 1; 
		}
		l = n - a[i]; r = n;
		int tmp = query(n - a[i] - 1); 
		while (l <= r) {
			int mid = l + r >> 1, q = query(mid) - tmp;
			if (q > 0) ans2 = mid, r = mid - 1;
			else l = mid + 1;
		}
		int ans = 0;
		if (ans1 == -1) {
			std::cout << (a[i] + ans2) % n << " ";
			update(ans2, -1);
		}
		else if (ans2 == -1) {
			std::cout << (a[i] + ans1) % n << " ";
			update(ans1, -1);
		}
		else {
			if ((a[i] + ans1) % n < (a[i] + ans2) % n) std::cout << (a[i] + ans1) % n << " ", update(ans1, -1);
			else std::cout << (a[i] + ans2) % n << " ", update(ans2, -1);
		}
	}
	std::cout << "\n";
	
	return 0;
}
```

---

## 作者：花里心爱 (赞：1)

看到几乎全CF用的都是STL做法，我在这里讲一种不用STL的做法。

首先，题目要求$c$的字典序最小，那么我们应该从前到后依次贪心地选取能让当前位最小的值。

由于$a_i, b_i \leq n-1$，$a_i+(n-a_i) \equiv 0 \pmod n$，所以当前能取的最小值为$n-a_i$。如果不能取$n-a_i$，那么就要取$n-a_i+1$，以此类推。

然后我们开一个$next$数组，记录当前数可到达的下一个数。初始化$next[i] = i+1$，$next[n-1] = 0$。然后当$next[i]$取完的时候，让$next[i] = next[next[i]]$。注意这个过程需要递归对每一个访问到的数都更新。

复杂度同路径压缩的并查集。

下面放代码：
```cpp
#include <cstdio>
#define maxn 200005

int n;
int a[maxn];
int b[maxn], s[maxn];
int nxt[maxn];

int getnxt(int x) {
    if(!s[x]) {
        if(!s[nxt[x]]) nxt[x] = getnxt(nxt[x]);
        x = nxt[x];
    }
    return x;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) scanf("%d", &b[i]), ++s[b[i]];
    for(int i = 0; i < n; ++i) nxt[i] = i+1;
    nxt[n-1] = 0;
    for(int i = 1; i <= n; ++i) {
    	int x = getnxt(n-a[i]); --s[x];
        printf("%d ", (a[i]+x)%n);
	}
    return 0;
}
```

---

## 作者：sieve (赞：0)

# 题解：[Minimum Array](https://www.luogu.com.cn/problem/CF1157E)

## 思路

看到题目，直接二分去找第一个大于等于 $(n - a_i) \bmod n$ 就好啦，找到以后，删除这个，对于删除，可以使用 $\texttt{vector}$ 或者 $\texttt{multiset}$，个人认为后者的操作更加简单，所以用了后者。

注意，如果找到的是最后一个，一定要把指针指向第一个！

最后输出找到的数加上 $a_i$ 然后模上 $n$ 就行了。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,a[N],b[N];
multiset<int> s;
signed main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>b[i],s.insert(b[i]);
	for(int i=1;i<=n;++i)
	{
		auto k=s.lower_bound((n-a[i])%n);
		if(k==s.end()) k=s.begin();
		cout<<(*k+a[i])%n<<' ';
		s.erase(k);
	}
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1157E)

简单题吧。

注意到要求字典序最小，那直接贪心。

按照余数分类，注意到两个数相同（在本题下），造成的影响是一样的。

对于当前的 $a_i$，把他转成 $p=a_i \bmod x$，考虑余数，所以我们按照余数从 $[n-p,n-1]$ 和 $[0,n-p-1]$ 顺序查找，找到第一个数和 $a_i$ 配肯定是最优的。因为按照这样的顺序保证 $c_i$ 尽可能小。 

怎么做呢。考虑分块维护，对于每个块维护块内第一个非 $0$ 位置即可。然后配完以后单点修改，直接重构块即可。

时间复杂度 $O(n \sqrt n)$，不用动脑。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =3e5+10;
int tot,l[N],Tag[N],r[N],pos[N],n,a[N],T[N];
void CG(int x){
	bool f=false;
	for(int i=l[x];i<=r[x];i++)
		if(T[i]!=0)	{f=true,Tag[x]=i;break;}
	if(!f)	Tag[x]=-1;
}
void Devide(){
	int len=sqrt(n-1); 
	if(len!=0)	tot=(n-1)/len;
	else	tot=1;
	if(len*len!=n-1)	tot++;
	for(int i=1;i<=tot;i++)	l[i+1]=(i-1)*len,r[i+1]=l[i+1]+len-1;
	r[tot]=n-1;
	for(int i=1;i<=tot;i++) for(int j=l[i];j<=r[i];j++)	pos[j]=i;
	for(int i=1;i<=tot;i++)	CG(i);
}
void update(int x){
	T[x]--; CG(pos[x]);
}
int Query(int L,int R){
	if(pos[L]==pos[R]){
		for(int i=L;i<=R;i++)	if(T[i]!=0)	return i;
		return -1;
	}
	for(int i=L;i<=r[pos[L]];i++)	if(T[i]!=0)	return i;
	for(int i=pos[L]+1;i<=pos[R]-1;i++)	if(Tag[i]!=-1)	return Tag[i];
	for(int i=l[pos[R]];i<=R;i++)	if(T[i]!=0)	return i;
	return -1;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1,x;i<=n;i++)	cin>>x,T[x]++;
	Devide();
	for(int i=1;i<=n;i++){
		int x=a[i]%n,lst=(n-x)%n;
		int now=Query(lst,n-1);
		if(now!=-1)	
			cout<<(x+now)%n<<' ',update(now);
		else
			now=Query(0,lst-1),cout<<(x+now)%n<<' ',update(now);
	}
	cout<<endl;
	return 0;	
} 
```

---

## 作者：YFF1 (赞：0)

## 分析：
使用特殊数据结构维护贪心的策略，在找不到与当前的数加起来后取模的数等于零时，找那个最小的数去进行取模操作。详情请见代码。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],b[200005];
multiset<int>s;//multiset可以放入重复的数，还可以自动排序，删除时也很方便
signed main () {
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		s.insert(b[i]);
	}
	for(int i=1;i<=n;i++){
		int x=n-a[i],y;
		if(x>*s.rbegin()){
			y=*s.begin();
			auto pos=s.begin();
			s.erase(pos);
		}
		else {
			auto pos=s.lower_bound(x);
			y=*pos;
			s.erase(pos);
		}
		printf("%d ",(a[i]+y)%n);
	}
	return 0;
}
```

---

## 作者：COsm0s (赞：0)

贪心。

显然对于 $a_i$，任意一个在 $\bmod\ n$ 意义上 $b_i=n-a_i$ 即为最优情况。

所以满足 $b_i > n-a_i$ 且 $b_i$ 最小时为最优解。当不存在这种情况时，即 $\min b_i$ 为最优解。

这就是我们的贪心策略。

满足维护序列最小和查询，`multiset` 即可。

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DOW(i, r, l) for (int i = (r); i >= (l); -- i)
//#define int long long
#define pii pair<int, int>
#define MPR make_pair
#define L first
#define R second
using namespace std;
namespace Cosmos {
	const int N = 2e5 + 5, inf = 1e9, mod = 998244353;
	const double PI = acos(-1);
	int a[N];
	multiset<int> se;
	int main() {
		int n, x;
		cin >> n;
		REP(i, 1, n) cin >> a[i];
		REP(j, 1, n) cin >> x, se.insert(x); 
		REP(i, 1, n) {
			auto now = se.lower_bound((n - a[i]) % n);
			if(now == se.end()) now = se.begin();
			cout << (*now + a[i]) % n << ' ';
			se.erase(now);
		}
		return 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) Cosmos::main();
	return 0;
}
```


---

## 作者：caohan (赞：0)

# 思路

就是贪心，但是需要些小技巧降降复杂度。

容易想到，在 $b_i$ 中，如果有 $n-a_i$ 就能把某一位变成  $0$，让字典序更小。

可是这种情况如果不存在了，即在 $i$ 之前已经把 $n-a_i$ 匹配完或者根本没有。这时考虑 $n+1-a_i,n+2-a_i \cdots $ 存在的最小值。若还是不存在，那就找 $b_i$ 的最小。

这些个操作可以使用 multiset，即可重集完成。

一些实现的细节在代码里有注明。

# 代码

```cpp
#include<bits/stdc++.h>
#define mod 100003
using namespace std;
multiset <int > s;//定义可重集 
int a[200005];
int c[200005];
int b[200005];
signed main()
{
	ios::sync_with_stdio (0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		s.insert(b[i]);
	}//输入 
	for(int i=1;i<=n;i++)
	{
		int x=(n-a[i])%n;//预计查找范围的起点
		auto it=s.lower_bound(x);//直接用自带的log查找
		if(it==s.end())
		{
			it=s.begin();
		}//没找着，用最小 
		cout<<(*it+a[i])%n<<" ";
		s.erase(it);//输出并擦除 
	}
	return 0;
}
```

---

