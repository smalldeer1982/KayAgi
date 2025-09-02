# Almost Difference

## 题目描述

Let's denote a function

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF903D/775e2389c0046855a8c7f1a2f9b05b0f64f8c0ab.png)

You are given an array $ a $ consisting of $ n $ integers. You have to calculate the sum of $ d(a_{i},a_{j}) $ over all pairs $ (i,j) $ such that $ 1<=i<=j<=n $ .

## 说明/提示

In the first example:

1. $ d(a_{1},a_{2})=0 $ ;
2. $ d(a_{1},a_{3})=2 $ ;
3. $ d(a_{1},a_{4})=0 $ ;
4. $ d(a_{1},a_{5})=2 $ ;
5. $ d(a_{2},a_{3})=0 $ ;
6. $ d(a_{2},a_{4})=0 $ ;
7. $ d(a_{2},a_{5})=0 $ ;
8. $ d(a_{3},a_{4})=-2 $ ;
9. $ d(a_{3},a_{5})=0 $ ;
10. $ d(a_{4},a_{5})=2 $ .

## 样例 #1

### 输入

```
5
1 2 3 1 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
6 6 5 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
6 6 4 4
```

### 输出

```
-8
```

# 题解

## 作者：QQH08 (赞：4)

对于 $d$ 函数的第二类，我们发现 $a_i$ 只能是整数，所以 $y$ 只能是 $x+1$ 或 $x-1$（$y=x$ 的时候和第一类一样）。所以我们先全部按照第一类算。

对于第一类，我们先对 $a$ 求后缀和 $s$ ，显然 $a_i$ 第一类的贡献是 $s_{i+1}-a_i \times(n-i)$ 。

然后考虑第二类，从 $n \rightarrow 1$ 枚举 $i$，用 map 记录每个数值对应 $a_i$ 的个数，对 $a_i+1$ 和 $a_i-1$ 修改答案。

注意用 long double（话说CF是不是不能用__int128？）
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long double lb;
const int N=200005;
int n;
lb ans,a[N],s[N];
map<lb,lb> mp;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%Lf",&a[i]);
	for(int i=n;i>=1;i--)s[i]=s[i+1]+a[i];
	for(int i=1;i<=n;i++)
		ans+=(s[i+1]-a[i]*(lb)(n-i));
	for(int i=n;i>=1;i--){
		mp[a[i]]++;
		if(mp[a[i]+1]>0)ans-=mp[a[i]+1];
		if(mp[a[i]-1]>0)ans+=mp[a[i]-1];
	}
	printf("%.0Lf",ans);
	return 0;
}
```


---

## 作者：迟暮天复明 (赞：2)

不是这就 \*2200 了？

显然 $\sum_{i=1}^n\sum_{j=i+1}^n a_j-a_i$ 这个东西是很好求的。对于 $|x-y|=1$ 的情形，开个 map 然后从左往右扫一遍，对于每一个数统计一下它左边有几个它 $-1$ 有几个它 $+1$ 然后修改答案即可。

---

## 作者：RedLycoris (赞：2)

这是什么题目啊，竟然回爆long long.....

这里介绍一个不用压位的方法

---

思路：

分类讨论即可

1.直接加上所有的y-x

2.单独处理所有的|x-y|$\le$1的情况

复杂度:O(n)

map是O(n log n)

注意:对于爆long long 的情况，可以用long double

只不过会慢一点，而且精度只比long long 大一点

---

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ll long long
using namespace std;
const int mxn=200005;
map<ld,ld>cnt_m;
ld l_cnt[mxn],h_cnt[mxn],sum[mxn],ans,n,a[mxn];
int main(){
	cin>>n;
	for(ll i=1;i<=n;++i)cin>>a[i];
	for(ll i=n;i;--i){            //从后往前统计，就不用二分了
		++cnt_m[a[i]];
		l_cnt[i]=cnt_m[a[i]-1];
		h_cnt[i]=cnt_m[a[i]+1];
		sum[i]=sum[i+1]+a[i];
	}
	for(ll i=1;i<=n;++i)ans+=sum[i]-a[i]*(n-i+1)+l_cnt[i]-h_cnt[i];
	cout<<fixed<<setprecision(0)<<ans<<endl;  //一定要控制输出的小数位为0！否则会输出类似于1e9+09之类的东西
}
```

---

## 作者：wizardMarshall (赞：1)

## 题意



定义


给定长度为 $n$ 的序列 $a$，求
$$\sum_{i=1}^n\sum_{j=i+1}^n f(a_i,a_j)$$

其中 $f$ 的定义如下：

$$f(x,y)=\begin{cases}y-x,&\text{if }|x-y|>1\\0,&\text{if }|x-y|\le 1\end{cases}$$

简单来说就是每一对差的绝对值大于 $1$ 的差之和（这里的差是后面减前面）。

## 思路

考虑 $O(n)$ 或 $O(n \log n)$ 的算法。

发现绝对值小于等于 $1$ 的情况不太好跟其他东西一起求，因此我们先不考虑这个条件，将其他数的答案都求出来。即为：

$$\sum_{i=1}^n(i-1)a_i+s_{i-1}$$

其中 $s_i$ 的意思是前 $i$ 项的前缀和。这个式子非常好理解，就是后面的 $i-1$ 个 $a_i$ 分别减去前面的这些数。

然后考虑绝对值小于等于 $1$ 的情况。这里可以分情况讨论 $a_j=a_i+1$ 以及 $a_j=a_i-1$（如果 $a_j=a_i$，就没有必要处理）。

我们使用一个 map 来从后往前处理之前多减的那些数。记录每一个数，之后分别加上比 $a_i$ 小一的数的个数（感性理解，多减了这些数），比 $a_i$ 大一的类似。

----

做到最后还会发现普通的长整型存不下，可以使用 `long double`。当需要输出整数的时候：

```c++
printf(".0Lf", ans);
```

这样就避免了输出科学计数法形式的错误。

----

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

long double a[200005];
map <long double, long double> mp;
signed main() {
	int n;
	cin >> n; 
	for (int i = 1; i <= n; i++) {
		scanf("%Lf", &a[i]);
	}
	long double sum = 0, s = 0;//记录答案和前缀和
	for (int i = 1; i <= n; i++) {
		sum += (a[i] * (i - 1) - s);
		s += a[i];
	}
	for (int i = n; i >= 1; i--) {
		if (mp[a[i] + 1]) {//记录之前错加（或错减）的个数
			sum -= mp[a[i] + 1];
		}
		if (mp[a[i] - 1]) {
			sum += mp[a[i] - 1];
		}mp[a[i]]++;//同时对当前数进行操作
	}printf("%.0Lf", sum);
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：1)

注意到直接求是不好求的，因此不直接求。

显然，我们先按照一般的 $|x-y| >1$ 的情况去求得答案，然后再特殊处理一下 $|x-y| \leq 1$ 的情况即可。

先考虑 $|x-y| > 1$ 这种情况。

对于每一个 $a_i$，他要算的就是 $a_i-a_{i-1}+a_i-a_{i-2}+\cdots+a_i-a_1$ 这样一个式子，显然有 $i$ 个 $a_i$ 相乘，然后再减去 $a_1\sim a_{i-1}$ 这一段的和，可以使用前缀和来做。

然后考虑 $|x-y| = 1$ 这种情况。

如果这个函数没有对 $|x-y| \leq 1$ 做特殊的限制，那么这组 $d(x,y)$ 的值是 $\pm 1$，如果是 $1$ 那就是 $x$ 比 $y$ 恰好小 $1$，如果是 $-1$ 那就是 $x$ 比 $y$ 恰好大 $1$。

考虑使用一个 `std::map` 来记录第 $1\sim i-1$ 个数中 $x$ 的数量，对于每个 $i$：

- 假设第 $1\sim i - 1$ 存在 $p$ 个 $a_i + 1$，那么答案就加上 $q$，因为我们在前面的计算中将这几组数的函数值看做了 $-1$，所以要加上。
- 假设第 $1\sim i - 1$ 存在 $q$ 个 $a_i -1$，那么答案就减去 $q$，因为我们在前面的计算中将这几组数的函数值看做了 $1$，所以要减去。

代码很好写（因为翻译里说卡 `long long` 所以偷懒用了 Python，但是你 C++ 用 `std::map` 也行）：

```python
n = int(input())
a = list(map(int, input().split()))
mp = {}
for i in range(n): mp[a[i]] = mp[a[i] + 1] = mp[a[i] - 1] = 0
ans = 0
tot = 0
for i in range(n):
  ans += i * a[i] - tot
  tot += a[i]
  ans += mp[a[i] + 1]
  ans -= mp[a[i] - 1]
  mp[a[i]] += 1
print(ans)
```

---

## 作者：1234567890sjx (赞：0)

考虑将 $|a_i-a_j|>1$ 和 $|a_i-a_j|\le 1$ 的两个部分分开计算。$|a_i-a_j|>1$ 的部分可以扫描的时候记录一下之前计算过部分的和然后用 $i\times a_i$ 减去她。$|a_i-a_j|\le 1$ 的部分可以分三类然后扫描一次并用 `map` 来记录当前所有数的出现次数。然后就做完了。总的时间复杂度为 $O(n\log n)$，瓶颈在于 `map`。还有就是这个题会炸 `long long`，需要使用 `__int128`、`long double` ~~或者 Python~~。

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

定义函数：$d(a_i,a_j)= \begin{cases}
a_j-a_i,\quad &if\left| a_i-a_j \right| > 1 \\
0,\quad &if\left| a_i-a_j \right| \leq 1
\end{cases} $。

给定长度为 $n$ 的序列 $a$，求 $\sum_{i=1}^n\sum_{j=i+1}^nd(a_i,a_j)$。

注意：答案可能会爆
```cpp
long long
```
!

## 思路

边输入边计算，维护 $cnt$ 数组记录当前值为 $x$ 的数的个数，同时计算 $sum$，记录当前数值之和。

当我们处理到第 $j$ 个数时，对于函数 $f(a_i,a_j)=a_j-a_i$，所求结果 $ans$ 需要加上 $a_j \times j-sum$，将函数 $f(a_i,a_j)$ 与函数 $d(a_i,a_j)$ 进行对比，可以发现 $d(a_i,a_j)$ 所求结果 $ans$ 即为 $f(a_i,a_j)$ 的所求结果再减去多加的部分，即 $\left| a_i-a_j \right| \leq 1$ 的部分。于是便得知 $ans$ 需要加上 $a_j \times j-sum-(a_j \times(cnt_{a_j}+cnt_{a_{j+1}}+cnt_{a_{j-1}})-a_j \times cnt_{a_j}-a_{j+1} \times cnt_{a_{j+1}}-a_{j-1} \times cnt_{a_{j-1}})$。化简后得 $ans$ 需要加上 $a_j \times j-sum+cnt_{a_{j+1}}-cnt_{a_{j-1}}$。

注意所有变量需用 
```cpp
long double
```
来存储，否则会爆！

## 代码

接下来放上我的简短代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>cnt;
long double n,a,sum,ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
	cin>>a;
	ans+=i*a-sum+cnt[a+1]-cnt[a-1];
	sum+=a;
	cnt[a]++;
    }
    printf("%.0Lf",ans);
    return 0;
}
```

---

## 作者：_jimmywang_ (赞：0)

不过多赘述题意与解题方法，其他题解都已经讲的很好了。

这里提供一种不依赖 `map` 的 $O(n)$ 做法。

如果值域很小，那么显然我们可以倒着跑，记录当前每个数出现了几次，然后进行计算。

于是我们可以进行一个离散化，把值域缩小。

但是如果直接离散化，会导致原本两个数相差不为 1 但是离散完以后相差等于 1。

为避免这种情况，我们把离散化修改一下。代码如下：

```
#define ll __int128
#define f(i,a,b) for(ll i=a;i<=b;i++)

ll a[200010],cnt;//原数组,计数器
struct node{ll x,id;}b[200010];
bool cmp(node a,node b){return a.x<b.x;}

//主函数内
f(i,1,n)b[i]={a[i],i};
sort(b+1,b+n+1,cmp);
f(i,1,n){
	if(b[i].x!=b[i-1].x){
		if(b[i].x-b[i-1].x==1)cnt++;
		else cnt+=2;
	}a[b[i].id]=cnt;
}
```

若排完序后相邻两个数相等，那么这个数就等于当前的 $cnt$。

要不然如果差等于 1，就将 $cnt$ 加一。

否则 $cnt$ 加 2。

这样就不仅保证了值域降下来，而且使得差不为 1 的元素不会互相影响。

完整代码（使用 `__int128`）：

```
// Problem: D. Almost Difference
// Contest: Codeforces - Educational Codeforces Round 34 (Rated for Div. 2)
// URL: https://codeforces.com/contest/903/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Author: jimmyywang

#include<bits/stdc++.h>
using namespace std;
#define ll __int128
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rd()
#define pb push_back
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll t,n,m,ans,cnt;
ll a[200010];
ll c[200010];
struct node{ll x,id;}b[200010];
bool cmp(node a,node b){return a.x<b.x;}
ll s[400010];
void out(ll x){
	if(x==0){putchar('0');return;}
	if(x<0)putchar('-'),x=-x;
	int p[100010],now=0;
	while(x)p[++now]=x%10,x/=10;
	for(int i=now;i>=1;i--)printf("%d",p[i]);
}
int main(){
	n=d;f(i,1,n)a[i]=d,b[i]={a[i],i},c[i]=c[i-1]+a[i];
	f(i,1,n)ans+=i*a[i]-c[i];
	sort(b+1,b+n+1,cmp);
	f(i,1,n){
		if(b[i].x!=b[i-1].x){
			if(b[i].x-b[i-1].x==1)cnt++;
			else cnt+=2;
		}a[b[i].id]=cnt;
	}for(int i=n;i>=1;i--){
		s[a[i]]++;
		ans+=s[a[i]-1];
		ans-=s[a[i]+1];
	}out(ans);
	return 0;
}
```

---

## 作者：Great_Influence (赞：0)

调死我了。。。。。。

题目大意很简单，不作赘述。可以轻松想到直接计算全答案，在将相差1的数对减去（或加回）即可。全答案推一下式子就可以了，至于相差1的数对，可以用map维护一下。

然后就是重点。你会发现，codeforces的数据非常强，还有的答案会爆long long。直接压位即可。注意codeforces需要打%I64d而不是%lld

代码：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x)
{
	T s=0,f=1;char k=getchar();
	while(!isdigit(k)&&(k^'-'))k=getchar();
	if(!isdigit(k)){f=-1;k=getchar();}
	while(isdigit(k)){s=s*10+(k^48);k=getchar();}
	x=s*f;
}
void file()
{
	#ifndef ONLINE_JUDGE
		freopen("test.in","r",stdin);
		freopen("test.out","w",stdout);
	#endif
}
const int MAXN=2e5+7;
static long long n,a[MAXN];
static map<long long,long long>G;
void init()
{
	read(n);
	Rep(i,1,n)read(a[i]);
}
static long long plu,upper;
const long long bas=1e9;
void solve()
{
	static long long u;
	Rep(i,1,n)
	{
		u=a[i];
		if(!G.count(u))G[u]=1ll;
		else ++G[u];
		if(G.count(u-1))plu-=G[u-1];
		if(G.count(u+1))plu+=G[u+1];
	}
	upper+=plu/bas,plu%=bas;
	Rep(i,n/2+1,n)
	{
		plu+=(a[i]-a[n-i+1])*(2ll*i-n-1ll);
		upper+=plu/bas,plu%=bas;
	}
	if(upper<0&&plu>0)++upper,plu-=bas;
	if(upper>0&&plu<0)--upper,plu+=bas;
	if(upper)printf("%I64d%09I64d\n",upper,abs(plu));
	else printf("%I64d\n",plu);
}
int main()
{
	file();
	init();
	solve();
	return 0;
}



```

---

## 作者：BFSDFS123 (赞：0)

比较简单的一道题，不知道为什么是蓝题。

思维不够，数据结构来凑。

对于一个数 $x$，我们将 $x+1,x,x-1$ 都离散化。然后用两个树状数组维护离散化后某个区间的数的**个数**和原数之和。

倒着计算，每次计算一下可以做出贡献的所有数的个数以及和。然后计算一下就行了。计算后更新树状数组。

注意到这道题会爆 long long，所以要用 long double。

```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long double
bool isdigit(char ch)
{
	return (ch>='0' && ch<='9');
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return w*s;
}
const signed  Maxn=6e5+10;
int n;
int Ar[Maxn];
#define lowbit(x) (x&(-x))
int siz;
int C[Maxn];
int D[Maxn];
void update(signed pos,signed val)
{
	while(pos<=siz)
	{
		C[pos]+=val;
		pos+=lowbit(pos);
	}
}
int query(signed pos)
{
	int ans=0;
	while(pos)
	{
		ans+=C[pos];
		pos-=lowbit(pos);
	}
	return ans;
}

void update2(signed pos,signed val)
{
	while(pos<=siz)
	{
		D[pos]+=val;
		pos+=lowbit(pos);
	}
}
int query2(signed pos)
{
	int ans=0;
	while(pos)
	{
		ans+=D[pos];
		pos-=lowbit(pos);
	}
	return ans;
}

int Gen[Maxn];
map<int,int> pp;
signed main()
{
	n=read();
	map<int,int> mp;
	for(signed i=1;i<=n;i++)
	{
		Ar[i]=read();
		mp[Ar[i]]=1;
		mp[Ar[i]-1]=1;
		mp[Ar[i]+1]=1;
	}
	signed cnt=0;
	for(auto i:mp)
	{
		int gen=i.first;
		cnt++;
		Gen[cnt]=gen;
		pp[gen]=cnt;
	}
	siz=mp.size();
	int ans=0;
	for(signed i=n;i>=1;i--)
	{
		signed id=pp[Ar[i]];
		int val=Gen[id];
		int ans1,ans2,cnt1,cnt2;
		if(id-2<=0)
		{
			ans1=0,cnt1=0;
		}else{
			ans1=query(id-2),cnt1=query2(id-2);
		}
		
		if(id+2>siz)
		{
			ans2=0,cnt2=0;
		}else{
			ans2=query(siz)-query(id+2-1),cnt2=query2(siz)-query2(id+2-1);
		}		
		int res=(ans2+ans1)-(cnt2+cnt1)*Ar[i];
		ans+=res;
		update(id,val);
		update2(id,1);
	}
	
	printf("%.0Lf",ans);
	return 0;
}
```

---

