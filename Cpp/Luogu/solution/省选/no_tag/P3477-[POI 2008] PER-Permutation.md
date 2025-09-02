# [POI 2008] PER-Permutation

## 题目描述

Multiset is a mathematical object similar to a set,    but each member of a multiset may have more than one membership.

Just as with any set, the members of a multiset can be ordered    in many ways. We call each such ordering a permutation    of the multiset. For example, among the permutations of the    multiset{1,1,2,3,3,3,7,8}. there are {2,3,1,3,3,7,1,8}   and{8,7,3,3,3,2,1,1}.

We will say that one permutation of a given multiset is smaller    (in lexicographic order) than another permutation, if on the first    position that does not match the first permutation has a smaller    element than the other one. All permutations of a given multiset    can be numbered (starting from one) in an increasing order.

Task      Write a programme that   reads the description of a permutation of a multiset and a positive          integerm from the standard input,                      determines the remainder of the rank of that permutation in the          lexicographic ordering modulo m,         writes out the result to the standard output.

多重集合是数学中的一个概念，它的定义很像集合，但是在多重集之中，同一个元素可以出现多次。


和集合一样，多重集的的元素可以有很多种元素的排布顺序。我们把它叫作多重集的排列。


现在我们定义多重集的某个排列$s_i$比某个排列$s_j$

的大小比较为字典序比较。这样某个多重集的排列可以从小到大得排起来。


现在给你一个元素个数为n的多重集的一个排列和m，求这个排列的排名取模m。


## 说明/提示

感谢@远航之曲 贡献的翻译


## 样例 #1

### 输入

```
4 1000
2 1 10 2
```

### 输出

```
5
```

# 题解

## 作者：Sonnety (赞：11)

[可能更好的阅读体验](https://www.cnblogs.com/sonnety-v0cali0d-kksk/p/PER.html)

（upd：对 Hack 的有关分析已更新，见上个人博客↑）

## 解题思路：

首先看到这道题求排名，感觉还挺像[康托展开](https://www.luogu.com.cn/problem/P5367)的，但是康拓展开求的是 **不会出现重复元素的排列** 的排名，而这道题的难题主要有两个：

可重复和未知模数。

### 对于可能重复的元素：

我们思考康托展开本身的公式。

对于一个 $1$ 到 $n$ 的排列：${a_1,a_2,a_3,\dots,a_n}$，其排名为：

$$
\sum_{i=1}^{n} sum_{a_i}\cdot (n-i)!
$$

而 $sum_{a_i}$ 表示在 $a_i$ 之后比它元素小的个数。


```
int ans=0;
for(int i=1;i<=n;i++){
    int sum=0;
   	for(int j=i;j<=n;j++)
	if(a[i]<a[j])sum++;//统计sum
    ans=(ans+sum*jc[n-i])%998244353;//计算ans                       
}
printf("%d",ans+1);//别忘了+1

```

那考虑如何去重呢？

我们的 $(n-i)!$ 表示的是 $(i+1)-n$ 位置所有的方案数，对于不重复元素，两个元素互换位置是不同的方案，而重复的元素，两个元素互换位置方案相同，造成了方案数的重复计算。

因此，我们考虑将重复元素提出来，例如 ${39,39,39,39}$，它是一个方案，却计了 $4!$ 次。

所以，设从 $i-n$ 位置一共有 $piece_i$ 种元素，$cnt_{j}$ 表示在当前的 $piece_i$ 下的第 $j$ 个元素，答案为：

$$ans=\sum_{i=1}^{n} \dfrac{sum_{a_i}\cdot (n-i)!}{\prod_{j=1}^{piece_{i}} cnt_j}$$

然后你发现，如果从左往右扫，不断删除元素对于 $cnt_j$ 的处理较难，所以考虑从右往左倒序枚举，这样就成为了加入元素，无论是分子还是分母都较为简单。

### 对于不明的模数

对于不定模数，或许有两种解决方式：

* 使用不依赖模数性质的算法或利用给出的模数自带的性质。

* 对模数进行特殊的处理。

不知道数据有没有 114514 一类的模数，但是显然 114514 不是质数，所以费马小定理不能使用。

而我们只能考虑扩展欧几里得算法了，它要求我们求解的模数与求解数互质。

所以我们可以对分母 $\prod_{j=1}^{piece_{i}} cnt_j$ 和模数分解质因数，对于模数没有的质因子，扩展欧几里得求逆元。

对于共同的质因子，我们考虑直接消去，因为 $ans$ 是整数，所以 $\dfrac{sum_{a_i}\cdot (n-i)!}{\prod_{j=1}^{piece_{i}}\limits cnt_j} cnt_j$ 是整数，所以若存在共同质因子 $p_i$，其分子一定存在比分母更多的质因子 $p_i$，所以直接消去分子和分母所有的 $p_i$，然后使分子乘上本身比分母多的 $p_i$ 即可。

(tips:有关[Hack](https://www.luogu.com.cn/discuss/311351)，请注意这里的分子包含 $suma$，即帖中的 $w$。)

使用树状数组优化一下，跑的还是比较快的。


```
#include<bits/stdc++.h>
#define il inline
#define rg register int
#define cout std::cout
#define cerr std::cerr
#define endl '\n'
#define int long long
typedef long long ll;
typedef unsigned long long ull;
typedef double ff;
typedef long double llf;
const ff eps=1e-8;
int Max(int x,int y)    <% return x<y?y:x; %>
int Min(int x,int y)    <% return x<y?x:y; %>
int Abs(int x)  <% return x>0?x:-x; %>
#if ONLINE_JUDGE
char INPUT[1<<20],*p1=INPUT,*p2=INPUT;
#define getchar() (p1==p2 && (p2=(p1=INPUT)+fread(INPUT,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#endif
il int read(){
    char c=getchar();
    int x=0,f=1;
    while(c<48) <% if(c=='-')f=-1;c=getchar(); %>
    while(c>47) x=(x*10)+(c^48),c=getchar();
    return x*f;
}const int maxn=3e5+5;

int n,Mod,ptot,p[maxn],a[maxn],sa[maxn],rank[maxn],len;
int cnt_numerator[maxn],cnt_denominator[maxn];
ll sum[maxn],ans,cnt[maxn];

il ll mymod(ll x){ return x<Mod?x:x-Mod; }

il ll qpow(ll x,int k){
// x^k
    ll res=1;
    while(k){
        if(k&1) res=res*x%Mod;
        x=x*x%Mod;
        k=k>>1;
    }
    return res;
}

il void exgcd(int a,int b,int &x,int &y){
// 求得x是a在模Mod意义下的乘法逆元
    if(!b)  return x=1,y=0,void();
    exgcd(b,a%b,y,x);y=(y-(a/b)*x%Mod+Mod)%Mod;
}

#define lowbit(x) (x&-x)
il ll query(int pos){
    ll res=0;
    while(pos){
        res+=sum[pos];
        pos-=lowbit(pos);
    }
    return res;
}
il void update(int pos,int val){
    while(pos<=len){
        sum[pos]+=val;
        pos+=lowbit(pos);
    }
}
#undef lowbit

il ll solve_numerator(ll numerator){
// 对分子分解质因数
    if(!numerator)  return 1;
    for(rg i=1;i<=ptot;++i){
        if(numerator%p[i])  continue;
        while(!(numerator%p[i]))  ++cnt_numerator[i],numerator/=p[i];
    }
    return numerator;
}

il void back(ll numerator){
// 撤回ssum对cnt_numerator的影响
    if(!numerator)  return;
    for(rg i=1;i<=ptot;++i){
        if(numerator%p[i])  continue;
        while(!(numerator%p[i]))  --cnt_numerator[i],numerator/=p[i];
    }
}

il ll solve_denominator(ll denominator){
// 对分母分解质因数
    if(!denominator)    return 1;
    for(rg i=1;i<=ptot;++i){
        if(denominator%p[i])    continue;
        while(!(denominator%p[i]))    ++cnt_denominator[i],denominator/=p[i];
    }
    return denominator;
}

il void work(){
    int numerator=1,denominator=1,res=1,x=0,y=0,save;
    for(rg i=n;i>=1;--i){
        res=1;
        ++cnt[a[i]];
        numerator=numerator*solve_numerator(n-i)%Mod;
        save=numerator;
        denominator=denominator*solve_denominator(cnt[a[i]])%Mod;
        update(rank[i],1);
        int ssum=query(rank[i]-1);
        if(!ssum)   continue;   // 没有比当前位小的直接continue
        numerator=numerator*solve_numerator(ssum)%Mod;
        exgcd(denominator,Mod,x,y);     // 求非共同质因子的逆元x
        x=mymod(x%Mod+Mod);
        for(rg j=1;j<=ptot;++j) res=res*qpow(p[j],cnt_numerator[j]-cnt_denominator[j])%Mod; // 消去共同质因子
        res=res*numerator%Mod*x%Mod;
        ans=mymod(ans+res);
        back(ssum);numerator=save;
    }
}

il void input(){
    n=read(),Mod=read();
    for(rg i=1;i<=n;++i)    a[i]=read(),sa[i]=rank[i]=a[i];
    std::sort(sa+1,sa+1+n);
    len=std::unique(sa+1,sa+1+n)-(sa+1);
    for(rg i=1;i<=n;++i)    rank[i]=std::lower_bound(sa+1,sa+1+len,rank[i])-sa; // 离散化
    int save=Mod;
    for(rg i=2;i<=sqrt(Mod);++i){
        if(Mod%i)   continue;
        p[++ptot]=i;
        while(!(Mod%i))   Mod/=i;
    }
    if(Mod^1)   p[++ptot]=Mod;
    Mod=save;
}

signed main(){
#ifndef ONLINE_JUDGE
freopen("PER.in","r",stdin);
#endif
    input();
    work();
    printf("%lld\n",mymod(ans+1));
    return 0;
}
```

---

## 作者：xin700 (赞：9)

## 很有思维的一道题

这个题的题面非常简单，出题人很 ~~友好~~ ，没有搞什么奇怪的背景，~~（卡农（P3214）的作者看看人家）~~，所以理解题面就是：

**一句话题意：**

给定一个长度为 $n$ 的数列，求这个数列是在其全排列中的排名是多少，输出排名模 $m$ 的结果。

赵小兵同学：这不就是个康托展开嘛，看我 A 掉这个大水题。

于是，他打出了下面这个程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define INF 0x7f7f7f7f7f
const int one = 1e7+10;
inline void openfile()
{freopen("t.txt","r",stdin);}
namespace zxb
{
	int tree[1000005];
	int n;
	inline int lowbit(int x)
	{
		return x&-x;
	}
	inline void update(int x,int y)
	{
		while(x<=n){
			tree[x]+=y;
			x+=lowbit(x);
		}
	}
	inline int query(int x)
	{
		int sum=0;
		while(x)
		{
			sum+=tree[x];
			x-=lowbit(x);
		}
		return sum;
	}
	int mod;
	int jc[1000005];
	int a[1000005];
	inline short main()
	{
		//openfile();
		jc[0] = jc[1] = 1;
		cin >> n >> mod;
		for(int i=1;i<=n;i++)
		{
			jc[i]=(jc[i-1]*i)%mod;
			update(i,1);
		}
		int ans = 0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			ans=(ans+((query(a[i])-1)*jc[n-i]) % mod) % mod;
			update(a[i],-1);
		}
		cout<<ans +1<<endl;
	   	return 0;
	  }
}
signed main() { return zxb::main();}
```
然后。。。[赵小兵同学翻车记录](https://www.luogu.com.cn/record/49927140)

旁边的 $C$ 君看不下去了，转眼就打了一个暴力算法，并对赵小兵同学发来了鄙视
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define INF 0x7f7f7f7f7f
const int one = 1e7+10;
inline void openfile()
{freopen("t.txt","r",stdin);}
inline int get()
{
	int s = 0,f = 1;
	register char ch = getchar();
	while(!isdigit(ch))
	{
		if(ch == '-') f= -1;
		ch = getchar();
	}
	while(isdigit(ch))
	{
		s = s* 10 + ch - '0';
		ch = getchar();
	}
	return s * f;
}
namespace xin
{
	int a[one],b[one];
	int mod,n;
	inline bool comp()
	{
		for(register int i=1;i<=n;++i)
			if(a[i] != b[i])
				return false;
		return true;
	}
	inline short main()
	{
	//	openfile();
		n = get(); mod = get();
		for(register int i=1;i<=n;++i) a[i] = get(),b[i] = a[i];
		sort(a+1,a+1+n);
		int cnt = 1;
		while(next_permutation(a+1,a+n+1))
		{
			cnt++;
			if(comp() == 1) 
			{
				cout<<cnt % mod<<endl;
				return 0;
			}
		}
		return 0;
	}
}
signed main() { return xin::main();}
```
 $C$ 君的暴力记录[$C$ 君的暴力记录](https://www.luogu.com.cn/record/49927309)
 $C$ 君整整比赵小兵同学多了一倍的分数，这时候，坐在一旁的 $XIN$ 同学看不下去了，但 $XIN$ 同学一时间也无法想出正解，但是经过 $XIN$ 同学为期 $3$ 天的不懈奋斗，终于 $A$ 掉了这个题目：
 赵小冰和 $C$ 君都想要知道他的思路， $XIN$ 同学开始讲到：
 
 首先，要考虑每一个数位的贡献值，其实赵小兵同学的第一想法是不错的，但是只能说是不对，因为这个题目存在重复，也存在模数为合数的时候，所以康托展开就不管用了，所以要考虑别的想法，发现全排列就和本身的字典序有关，之后得出计算式：
 $$
 w \cdot \frac{(n-i)!}{\Pi \ {cnt[j]!}} 
 $$
 $cnt $ 就是从 $i$ 到 $n $ 中 $j$ 所出现的个数
 
 但是问题就又来了，合数应该怎么处理呢？？？
 
 最先考虑费马小定理：
 $$
 a^{p-1}≡1 (mod\ p)
 $$
 可是，模数为合数啊，所以考虑扩展欧几里的求出逆元：
 ```cpp
inline void exgcd(int a,int b,int &x,int &y)
{
    if(!b) { x = 1; y = 0; return;}
    exgcd(b,a%b,y,x);
    y -= a / b * x;
}
inline int get_inv(int x,int p)
{
    int a,b;
    exgcd(x,p,a,b);
    return (a % p + p) % p;
}
 ```
 之后可以用树状数组在 $log$ 的时间复杂度的情况下求出区间最小值：
 ```cpp
 namespace xin_bit
{
    int s[maxn];
    inline int lowbit(int x)
    {return x & -x;}
    inline void add(int x,int val)
    {
        while(x <= maxn)
        {
            s[x] += val;
            x += lowbit(x);
        }
    }
    inline int query(int x)
    {
        register int ret = 0;
        while(x)
        {
            ret += s[x];
            x -= lowbit(x);
        }
        return ret;
    }
}
 ```
 之后来一点小小的转移，将因子分解，之后再合并，最后就可以按照计算式求出本题的答案了。
 慷慨的 $XIN$ 还放出了代码：
 ```cpp
 #include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6+10;
namespace xin_io
{
    inline int get()
    {
        int s =0 ,f = 1;
        register char ch = getchar();
        while(!isdigit(ch))
        {
            if(ch == '-') f= -1;
            ch = getchar();
        }   
        while(isdigit(ch))
        {
            s = s *10 + ch - '0';
            ch = getchar();
        }
        return s * f;
    }
    inline void write(int x)
    {
        if(x < 0) putchar('-'),x = -x;
        if(x > 9) write(x/10);
        putchar(x % 10 + '0');
    }
}
using xin_io::get; using xin_io::write;
inline void openfile()
{freopen("t.txt","r",stdin);}
namespace xin_bit
{
    int s[maxn];
    inline int lowbit(int x)
    {return x & -x;}
    inline void add(int x,int val)
    {
        while(x <= maxn)
        {
            s[x] += val;
            x += lowbit(x);
        }
    }
    inline int query(int x)
    {
        register int ret = 0;
        while(x)
        {
            ret += s[x];
            x -= lowbit(x);
        }
        return ret;
    }
}
namespace xin
{
    #define m(c) cout<<sizeof(c) / (1 << 20) << "MB"<<endl
    #define min(a,b) (a) < (b) ? (a) : (b)
    #define max(a,b) (a) > (b) ? (a) : (b)
    int mod;
    int n,m;
    bool number[maxn];
    int prime[maxn];
    int i,j,count=0;
    inline void xin_shai(int N)
    {
        memset(number,true,sizeof(number));
        for(i=2;i<=N;i++)
        {
            if(number[i])
                prime[count++]=i;
            for(j=0;j<count and prime[j]*i<=N;j++)
            {
                number[prime[j]*i]=false;
                if(i%prime[j]==0)
                    break;
            }
        }
    }
    inline void exgcd(int a,int b,int &x,int &y)
    {
        if(!b) { x = 1; y = 0; return;}
        exgcd(b,a%b,y,x);
        y -= a / b * x;
    }
    inline int get_inv(int x,int p)
    {
        int a,b;
        exgcd(x,p,a,b);
        return (a % p + p) % p;
    }
    int cnt[110],link[110][maxn];
    int rec1[maxn],rec2[maxn];
    int temp,a[maxn],fac[maxn],num_fac = 0;
    inline void cont(int &x,int val)
    {
        for(register int i=1;i<=num_fac;++i)
        {
            register int zhuan = fac[i];
            while(!(x % zhuan))
                x/=zhuan,cnt[i] += val;
        }
    }
    inline int get_num()
    {
        int ret = 1;
        for(register int i=1;i<=num_fac;++i)
            ret = (ret * link[i][min(rec2[i],cnt[i])] ) % m;
        return ret;
    }
    inline int work()
    {
        int ans = 0,ret = 1;
        rec1[a[n]] = 1; xin_bit::add(a[n],1);
        for(register int i=n-1;i>=1;--i)
        {
            int zhuan  = n - i;
            cont(zhuan,1);
            ret *= zhuan; ret %= m;
            zhuan = ++rec1[a[i]];
            cont(zhuan,-1);
            ret = (ret * get_inv(zhuan,m) + m) % m;
            xin_bit::add(a[i],1);
            zhuan = get_num();
            ans += (ret % m * xin_bit::query(a[i] - 1) % m * zhuan % m + m ) % m;
            ans %= m;
        }
        return ++ans;
    }
    inline short main()
    {
        openfile();
        n = get(); m = get(); temp = m;
        for(register int i=1;i<=n;++i) a[i] = get();
        for(register int i=2;i<=sqrt(temp);++i)
        if(temp % i == 0)
        {
            fac[++num_fac] = i;
            link[num_fac][0] = 1;
            for(register int j=1;j<=maxn;++j)
                link[num_fac][j] = link[num_fac][j-1] * i % m,rec2[num_fac] ++;
            while(temp % i == 0)temp /= i;
        }
        if(temp > 1)
        {
            fac[++num_fac] = temp;
            link[num_fac][0] = 1;
            for(register int j=1;j<=maxn;++j)
                link[num_fac][j] = link[num_fac][j-1] * temp % m,rec2[num_fac]++;
        }
        int ans = work() % m;
        write(ans);
        putchar('\n');
        return 0;
    } 
}
signed main() {return xin::main();}
 ```
 修改了 $\LaTeX$ ，望通过。

---

## 作者：Rolling_star (赞：6)

~~这道题如果不是任意模数的话还是比较平凡的（~~

这道题的式子其实很好推，根据康托展开的思路，一位一位考虑，只不过是多重集，可能有重复情况，排除即可，每一位的式子为：

$$ ans_i=\dfrac{(n-i)!}{\prod cnt_j}\times\sum^n_{k=i+1}[ a_k<a_i] $$
（$cnt_j$ 为 $i-n$ 之间 $j$ 的个数，$a_i$ 为第 $i$ 位的值）

后面的和式为 $i-n$ 之间值大于第 $i$ 位的值的数量，同康托展开，用树状数组处理，接下来考虑如何处理任意模数。

$cnt_j$ 中有可能会出现与 $p$ 不互质的情况，这种条件下不存在逆元，所以可以借鉴扩展卢卡斯的思路，把分子和分母中 $p$ 的质因子拆分出来，再来计算分母逆元，最后累计答案的时候再把 $p$ 分离出来的质因子乘进去即可。

另外，对于每一位的答案肯定不能单独计算，否则时间复杂度会爆掉，所以考虑答案递推，首先从后向前推肯定相对简单，考虑每往前走一步对答案的影响，假设从 $t+1$ 走到 $t$ 分子，分子从 $(n-t-1)!$ 变为 $(n-t)!$ 乘上了 $n-t$，$cnt_{a_t}$ 增加了1，相当于乘上了 $\dfrac{cnt_{a_t}-1}{cnt_{a_t}}$，把上面两式分离质因子求逆元乘进答案递推即可，初始状态 $ans_n=0$

最后附上本蒟蒻炸裂代码：
```cpp
#include<bits/stdc++.h>
#define N 300005ll
#define int long long
using namespace std;

int n,m,s[N],ans=1,buk[N],cnt[100];
int x,y,fac[100][N],base[100],tot;
struct Fenwick{
    int c[N];
    inline int lowbit(int X) {return X&(-X);}
    inline void update(int pos,int val){
        for(int i=pos;i<=N-5;i+=lowbit(i))
            c[i]+=val;
    }
    inline int sum(int pos){
        int temp=0;
        for(int i=pos;i;i-=lowbit(i))
            temp+=c[i];
        return temp;
    }
}T;
void exgcd(int a,int b);
int inv(int a,int p);
void factor(int a);
void change(int &a,int type);
int prod();

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        scanf("%lld",s+i);
    factor(m);
    buk[s[n]]++;T.update(s[n],1);
    int tmpans=1,tmp;
    for(int i=n-1;i>=1;i--){
        T.update(s[i],1);
        change(tmp,1);
        tmpans=tmpans*tmp%m;
        tmp=++buk[s[i]];
        change(tmp,-1);
        tmpans=tmpans*inv(tmp,m)%m;
        ans=(ans+tmpans*T.sum(s[i]-1)%m*prod()%m)%m;
    }
    cout<<ans;
}

void exgcd(int a,int b){
    if(!b){
        x=1,y=0;
        return;
    }
    exgcd(b,a%b);
    int tmp=x;
    x=y,y=tmp-a/b*y;
}

int inv(int a,int p){
    exgcd(a,p);
    return (x%p+p)%p;
}

void factor(int a){
    for(int i=2;a!=1;i++)
        if(!(a%i)){
            base[++tot]=i;
            fac[tot][0]=1;
            while(!(a%i)) a/=i;
            for(int j=1;j<=N-5;j++)
                fac[tot][j]=fac[tot][j-1]*i%m;
        }
}

void change(int &a,int type){
    for(int i=1;i<=tot;i++)
        while(!(a%base[i])){
            a/=base[i];
            cnt[i]+=type;
        }
}

int prod(){
    int Tmp=1;
    for(int i=1;i<=tot;i++)
        Tmp=Tmp*fac[i][cnt[i]]%m;
    return Tmp;
}
```

---

## 作者：K8He (赞：5)

# 「题解报告」[[POI2008]PER-Permutation](https://www.luogu.com.cn/problem/P3477)

[更好的阅读体验](https://www.cnblogs.com/Keven-He/p/solution-P3477.html)

不理解哪里难了，学过扩卢并且推一下式子基本就是两眼切吧。

个人感觉顶多上位紫。

## 思路

首先设 $f_i$ 表示前 $i-1$ 位固定，第 $i$ 位选一个比原来小的，后面随便排的方案数。

显然 $(\sum_{i=1}^{n}f_i)+1$ 为答案，那么考虑如何快速求出 $f_i$。

考虑用“交换”的思想，即在后 $n-i$ 个数中找到比 $a_i$ 小的数和它换一下，然后再随便排。

然而这里是可重集，所以还要去重乘上 $\dfrac{1}{\prod_{j}(A_{cnt_j}^{cnt_j})}=\dfrac{1}{\prod_{j}(cnt_j!)}$。（$cnt_j$ 表示在 $i\sim n$ 中 $j$ 出现了几次）

那么可写出式子：

$$
f_i=\frac{(n-i)!}{\prod(cnt_j!)}\sum_{j=1}^{n}[a_i>a_j]\bmod M
$$

但是 $M$ 不是质数，没法直接求逆元，怎么办呢？

**用扩展卢卡斯的思想**。

[扩卢是啥？](https://www.cnblogs.com/Keven-He/p/CombinationAndCRT.html#exlucas)

首先把 $M$ 分解成 $p_1^{k_1}p_2^{k_2}\cdots p_t^{k_t}(p_i\in\mathbb{P})$，解决这个方程组：

$$
\begin{cases}
x \equiv \frac{(n-i)!}{\prod(cnt_j!)}\sum_{j=1}^{n}[a_i>a_j] \pmod{p_1^{k_1}}\\
x \equiv \frac{(n-i)!}{\prod(cnt_j!)}\sum_{j=1}^{n}[a_i>a_j] \pmod{p_2^{k_2}}\\
\dots\\
x \equiv \frac{(n-i)!}{\prod(cnt_j!)}\sum_{j=1}^{n}[a_i>a_j] \pmod{p_t^{k_t}}\\
\end{cases}
$$

这些内容可用 CRT 合并，然后注意这个方程：

$$
x \equiv \frac{(n-i)!}{\prod(cnt_j!)}\sum_{j=1}^{n}[a_i>a_j] \pmod{p^k}\\
$$

$\sum_{j=1}^{n}[a_i>a_j]$ 简单树状数组解决，问题就只剩下了如何求 $\dfrac{(n-i)!}{\prod(cnt_j!)}\bmod{p^k}$。

继续用扩卢的思想，**把分子和分母中的 $p$ 提取出来**：

$$
\large\dfrac{\frac{(n-i)!}{p^{x}}}{\frac{\prod(cnt_j!)}{p^{y}}}*p^{x-y}\bmod{p^k}
$$

直接提显然会 TLE，所以我们充分发挥人类智慧：求 $f_i$ 时倒序跑，这样**每次只用额外提出 $(n-i)$ 和 $cnt_{a_i}$ 的 $p$，然后与上一次的分子与分母合并即可**。

然后有个小细节：$x-y$ 可能为负，此时要发挥人类智慧用逆元淦。

然后就切掉了。

## 代码

```cpp
#include <bits/stdc++.h>
#define lowb(a, r, x) lower_bound(a + 1, a + r + 1, x) - a
#define uppb(a, r, x) upper_bound(a + 1, a + r + 1, x) - a
#define _for(i, a, b) for (ll i = a; i <= b; ++i)
#define for_(i, a, b) for (ll i = a; i >= b; --i)
#define far(i, vec) for (auto i : vec)
#define bdmd int mid = (l + r) >> 1
#define NO nullptr
typedef long double ldb;
typedef long long ll;
typedef double db;
const ll N = 3e5 + 10, INF = 1ll << 40;

class TreeArray {
public:
	ll b[N], mx;
	inline ll lowbit (ll x) { return x & -x; }
	inline void Update (ll x) {
		while (x <= mx) ++b[x], x += lowbit (x);
		return;
	}
	inline ll Query (ll x) {
		ll ans = 0;
		while (x > 0) ans += b[x], x -= lowbit (x);
		return ans;
	}
} ta;

namespace MathBasic {
	inline void GetFactor (ll x, std::vector <ll>& p, std::vector <ll>& k) {
		p.push_back (0), k.push_back (0);
		for (ll i = 2; i * i <= x; ++i) {
			if (!(x % i)) {
				p.push_back (i), k.push_back (0);
				while (!(x % i)) x /= i, ++k[k.size () - 1];
			}
		}
		if (x != 1) p.push_back (x), k.push_back (1);
		return;
	}
	inline ll ExGcd (ll a, ll b, ll& x, ll& y) {
		if (!b) { x = 1, y = 0; return a; }
		ll g = ExGcd (b, a % b, x, y), _x = x;
		x = y, y = _x - (a / b) * y;
		return g;
	}
	inline ll Inv (ll a, ll P) {
		ll x, y;
		ExGcd (a, P, x, y);
		return (x % P + P) % P;
	}
	inline ll FastPow (ll a, ll b, ll Mod = INF) {
		ll ans = 1;
		if (b < 0) a = Inv (a, Mod), b = -b;
		while (b) {
			if (b & 1) ans = ans * a % Mod;
			a = a * a % Mod, b >>= 1;
		}
		return ans;
	}
}

namespace CRT {
	using namespace MathBasic;
	ll a[N], m[N], fac[N], fm[N], in[N], cnt[N];
	std::vector <ll> p, k;
	inline void Pre (ll P) {
		GetFactor (P, p, k);
		ll len = p.size () - 1;
		_for (i, 1, len) fac[i] = fm[i] = 1;
		return;
	}
	inline ll Idx (ll x, ll P) {
		ll idx = 0;
		while (!(x % P)) x /= P, ++idx;
		return idx;
	}
	inline ll DelP (ll x, ll P) {
		while (!(x % P)) x /= P;
		return x;
	}
	inline ll CRT (ll n, ll j, ll ai, ll P) {
		ll ans = 0, len = p.size () - 1;
		++cnt[ai];
		_for (i, 1, len) {
			m[i] = FastPow (p[i], k[i]);
			in[i] += Idx ((n - j) ? (n - j) : 1, p[i]) - Idx (cnt[ai], p[i]);
			fac[i] = fac[i] * DelP ((n - j) ? (n - j) : 1, p[i]) % m[i];
			fm[i] = fm[i] * DelP (cnt[ai], p[i]) % m[i];
			a[i] = FastPow (p[i], in[i], m[i]) * fac[i] % m[i] * Inv (fm[i], m[i]) % m[i];
			ll q = P / m[i];
			ans = (ans + a[i] * q % P * Inv (q, m[i]) % P) % P;
		}
		return ans;
	}
}

namespace SOLVE {
	ll n, P, a[N], ans = 1;
	inline ll rnt () {
		ll x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	inline void In () {
		n = rnt (), P = rnt ();
		_for (i, 1, n) a[i] = rnt (), ta.mx = std::max (ta.mx, a[i]);
		return;
	}
	inline void Solve () {
		CRT::Pre (P);
		for_ (i, n, 1) {
			ll crt = CRT::CRT (n, i, a[i], P);
			ans = (ans + ta.Query (a[i] - 1) % P * crt % P) % P;
			ta.Update (a[i]);
		}
		return;
	}
	inline void Out () {
		printf ("%lld\n", ans);
		return;
	}
}
int main () {
#ifndef ONLINE_JUDGE
	freopen ("date.in", "r", stdin);
#endif
	SOLVE::In ();
	SOLVE::Solve ();
	SOLVE::Out ();
	return 0;
} /*



*/
```

---

## 作者：hbhz_zcy (赞：3)

题意是求出一个多重集下一个排列的排名。  
容易想到枚举全排列，但是显然不够优秀。  
发现所求等价于多重集下的康托展开，故考虑对原式子进行变形：  
$$1+\sum_{i=1}^N{(n-i)!\cdot \sum_{j=i+1}^Na[j]<a[i]}$$  
上面的意思是枚举 $i$，表示前面位置沿用，当前位置寻找更小的去替代，再后面随便乱填。  
为了应对产生的改变，可以除掉一个数进行去重：  
发现相同的数 $x$ 共有 $cnt[x]!$ 种排列方法，但是只算成一种排列。  
但相同数在前面的不算，因此我们需要动态维护一个 $cnt$  
因此答案为：  
$$1+\sum_{i=1}^N\frac{(n-i)!\sum_{j=i+1}^Na[j]<a[i]}{enum_{i+1}^N:\sum cnt[x]!}$$  
然后我们发现模数可能是合数，需要特殊的操作：  
我们发现较大的数可以用几个数的质因子唯一表示，但是质因子数太多，然而模数固定且质因子数少，故较大的数可以分解成模数所包含的质因子与余项的乘积。  
所以：  
1. 维护一个长度 $10$ 的数组，模数分解质因子。
2. 以下的数同样分解质因子，用长 $10$ 的数组表示，$0$ 下标为余项积（可以取模）初始化为 $1$，其它下标为该质因子的个数（这个取模当且仅当能够覆盖整个模数，因此“分解模数时记录个数，求值时分别用个数取模”的思路是错误的-）。  
3. 定义乘除操作，非 $0$ 下标直接加减，余项直接乘，除法用exgcd逆元。  
4. 定义求值操作：快速幂掉非零项，最后乘上余项就可以了（中间允许取模-）。  

关于主函数里怎么写：  
预处理出 $1$ 至 $maxn$ 阶乘，计算cnt数组和 $\frac{1}{\sum cnt[x]!}$，以及存储输入序列的权值树状数组。  
顺序扫描每个数，用前面提到的乘除操作更新cnt和树状数组，进而计算出答案（如果不逐步地推会超时）。  
代码里有很多冗余操作，望谅解。  
```cpp
//g++ -g k.cpp -o k -std=c++14 -O0 -Wall
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
const int maxn=3e5+10,maxm=15;
int N,mod,jc[maxn][maxm],fm[maxm][2],mtop=0,a[maxn],ft[maxn],cnt[maxn],ans=0;
int qd(){
	int rt=0;char c=getchar();
	while(c<'0'||c>'9')  c=getchar();
	while('0'<=c&&c<='9')  rt=(rt<<3)+(rt<<1)+c-48,c=getchar();
	return rt;
}
#define lowbit(t) (t&-(t))
void change(int t,int v){for(;t<maxn;t+=lowbit(t))  ft[t]+=v;}
int ask(int t){int rt=0;for(;t;t-=lowbit(t))  rt+=ft[t];return rt;}
LL qsm(LL x,int y){
	LL rt=1;
	for(;y;y>>=1,x=x*x%mod)  if(y&1)  rt=rt*x%mod;
	return rt;
}
void exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){x=1,y=0;return;}
	exgcd(b,a%b,x,y);LL _x=x;
	x=y,y=_x-a/b*y;
}
LL ni(int t){LL x,y;exgcd(t,mod,x,y);/*printf("ni %d = %lld\n",t,x);*/return (x%mod+mod)%mod;}
void calc1(int _a[],int _b[]){_a[0]=1LL*_a[0]*_b[0]%mod;for(int i=1;i<=mtop;i++)  _a[i]+=_b[i];}
void calc1(int _a[],int x){
	for(int i=1;i<=mtop;i++)  while(x&&x%fm[i][0]==0)  x/=fm[i][0],_a[i]++;
	_a[0]=1LL*_a[0]*x%mod;
}
void calc2(int _a[],int _b[]){
	for(int i=1;i<=mtop;i++)  _a[i]-=_b[i];
	_a[0]=_a[0]*ni(_b[0])%mod;
}
void calc2(int _a[],int x){
	for(int i=1;i<=mtop;i++)  while(x&&x%fm[i][0]==0)  x/=fm[i][0],_a[i]--;
	_a[0]=_a[0]*ni(x)%mod;
}
LL calc0(int _a[]){
	LL rt=_a[0];
	for(int i=1;i<=mtop;i++)  rt=rt*qsm(fm[i][0],_a[i])%mod;
	return rt;
}
int main(){
//	freopen("in.txt","r",stdin);
	N=qd(),mod=qd();int _x=mod;
	for(int i=2;i*i<=_x;i++){
		if(_x%i==0)  fm[++mtop][0]=i;
		while(_x%i==0)  fm[mtop][1]++,_x/=i;
	}if(_x-1)  fm[++mtop][0]=_x,fm[mtop][1]=1;
	jc[0][0]=1;for(int i=1;i<=N;i++){for(int j=0;j<=mtop;j++)  jc[i][j]=jc[i-1][j];calc1(jc[i],i);}
	for(int i=1;i<=N;i++)  change(a[i]=qd(),1),cnt[a[i]]++;
	int prod[10]={1};calc1(prod,jc[N-1]);
	for(int i=1;i<maxn;i++)  if(cnt[i]>1)  calc2(prod,jc[cnt[i]]);
	for(int i=1;i<=N;i++){
		change(a[i],-1);int x=ask(a[i]-1);
		if(x){/*printf("i=%d x=%d prod=%lld \n",i,x,calc0(prod));*/calc1(prod,x);ans=(ans+calc0(prod))%mod;calc2(prod,x);}
		calc1(prod,cnt[a[i]]--);calc2(prod,N-i);
	}
	printf("%d\n",(ans+1)%mod);
	return 0;
}
```

---

## 作者：Leap_Frog (赞：3)

### P.S.
woc 怎么其他三篇题解全部 UB ![](//xn--9zr.tk/fad)  
常数被吊打【悲】  

### Description.
求可重排列的[康托展开](https://baike.baidu.com/item/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80/7968428?fr=aladdin)  

### Solution.
首先，考虑比较字典序的过程。  
肯定有一个前缀是相同的，然后有一位不同，后面随便乱排。  
那么我们考虑枚举两排列第一位不同的位置。  
因为需要统计的排列字典序比给定排列小，所以当前这位有 $\sum_{i=w+1}^n[a_i<a_w]$ 种方案数。  
包括当前这个元素随机乱排的方案数为 $\frac{(n-w+1)!}{\prod cnt!}$，这个公式是 `有重复元素的排列问题` 的结论。  
可惜当前这个元素取值有限制，只有 $\sum_{i=w+1}^n[a_i<a_w]$ 种取值可以取。  
所以当前这位答案即为 $\frac{(n-w+1)!}{\prod cnt!}\times\frac{\sum_{i=w+1}^n[a_i<a_w]}{n-w+1}=\frac{(n-w)!}{\prod cnt!}\times\left(\sum_{i=w+1}^n[a_i<a_w]\right)$  
所以我们直接统计答案即可，注意值域不大，$\sum_{i=w+1}^n[a_i<a_w]$ 可以直接树状数组维护。  
然后就做完了。  

注意这题模数不一定是质数，不一定有逆元。  
所以我们需要参考[这题](https://www.luogu.com.cn/problem/CF1109E)的思路，求出 $P$ 的所有质因数，然后开桶统计他们。  
其他的因数和 $P$ 互质，所以可以 excrt 或者 欧拉定理 即可。  
本篇题解用的 欧拉定理。  

### Attention.
[其他题解全部 UB](https://www.luogu.com.cn/discuss/show/311351?page=2) 是怎么回事呢？下面就让小编带大家一起了解吧。  
欸，可以证明这个 $\frac{(n-w)!}{\prod cnt!}\times\left(\sum_{i=w+1}^n[a_i<a_w]\right)$ 肯定是整数。  
但是这不等于 $\frac{(n-w)!}{\prod cnt!}$ 就一定是整数了，其他题解就默认有保证这点然后就会计算负指数。  
所以他们的下标直接越界，然后就 ![](//xn--9zr.tk/xk) 了。  
其实小编刚开始写这题时也忽略了这点，不过小编写地快速幂所以会 TLE 然后看了半天 ![](//xn--9zr.tk/xk)  
大家可能会很惊讶所有题解为什么全都 UB 了呢？小编也很惊讶，但事实就是这样。  
这就是关于这道题的事情了，大家有什么想法呢，欢迎在评论区告诉小编一起讨论哦！  

### Coding.
感觉没啥好解释的，Attention 中的东西放到注释里去了
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
int n,P,a[300005],T[300005],mx,p[15],pc,ph,rs[300005],tp[15],tc=1,cnt[300005],iv[300005];
inline int ksm(int x,int q=ph-1) {int r=1;for(;q;q>>=1,x=1ll*x*x%P) if(q&1) r=1ll*r*x%P;return r;}
inline void add(int x) {for(;x<=mx;x+=x&(-x)) ++T[x];}
inline int qry(int x) {int r=0;for(;x;x-=x&(-x)) r+=T[x];return r;}
inline void TIM(int w,int &tc,int *tp) {for(int i=1;i<=pc;i++) while(w%p[i]==0) w/=p[i],tp[i]++;tc=1ll*tc*w%P;}
inline void DIV(int w,int &tc,int *tp) {for(int i=1;i<=pc;i++) while(w%p[i]==0) w/=p[i],tp[i]--;tc=1ll*tc*iv[w]%P;}
inline int CAL(int tc,int *tp) {int r=tc;for(int i=1;i<=pc;i++) r=1ll*r*ksm(p[i],tp[i])%P;return r;}
int main()
{
	read(n),read(P);int nt=ph=P;for(int i=1;i<=n;i++) read(a[i]),mx=max(mx,a[i]);
	for(int i=2;i*i<=nt;i++) if(nt%i==0) {p[++pc]=i,ph=ph/i*(i-1);while(nt%i==0) nt/=i;}
	int rs=0;add(a[n]),iv[1]=1,cnt[a[n]]++;if(nt^1) p[++pc]=nt,ph=ph/nt*(nt-1);
	for(int i=n-1;i;i--)
	{
		int w=qry(a[i]-1);TIM(n-i,tc,tp),add(a[i]),iv[n-i+1]=ksm(n-i+1);
		DIV(++cnt[a[i]],tc,tp);if(!w) continue;
		//这里就是上面 Attention 中的内容，必须先把 w 乘上后再计算答案
		TIM(w,tc,tp),rs=(rs+1ll*CAL(tc,tp))%P,DIV(w,tc,tp);
	}
	//cerr<<clock()*1.0/CLOCKS_PER_SEC<<endl;
	return printf("%d\n",(rs+1)%P),0;
}
```

---

## 作者：liangchenming (赞：2)

## 总体思路

从1开始向后枚举，依次固定住每一位看后面的能组合出多少种方案（因为 $2xxxx$ 一定比 $1xxxx$ 大），再乘上后面小于它的数的数量，最后再除以其后所有数字数量的阶乘的连乘就行了（我不知道啥叫康托展开）。

由此得到式子：$\frac{fac[n-i]\times xs}{s}$

其中 $s=∏ ^{i}_{n} fac[\ num[a[j]\ ]\ ]$

而其中 $xs$ 是从 $n-i+1$ 到 $n$ 中小于 $a[i]$ 的个数。

这里解释一下 $s$ 的含义：

因为题意是不重复的排列，所以我们必须去重，**而 $i$ 及其之后所有重复数字的数量全排列之积，就是去重所需除去的**，这很好解释，因为我们在直接算全排列的时候，把这些重复数字自己的排列也算进去了，因此我们依照分步求方案数的原则把它们的积除去就行了。而 $xs$ 中可能也有重复几个数字的，他们会与 $s$ 中重复的相同数字消掉，使之去重。而在做题中为了方便，$s$ 存储的是逆元形式。

至于 $xs$ 就可以使用树状数组来维护。

$m$ 未必为质数，也未必与分母互质，未必有逆元。

而一切整数都能拆成 $p_1^{k_1}\times p_2^{k_2}……p_x^{k_x}$ 的形式，所以我们把 $m$ 也如此拆开，分别让原答案对 $p_1^{k_1},p_2^{k_2}……,p_x^{k_x}$ 取模，由此构建中国剩余定理的方程组，之后合并求解就可以了。

而在取模的时候有可能因为分母和模数仍然不互质而导致求不出除数的逆元，所以参考扩展卢卡斯定理的应对方法，

**就是面对 $n! \mod p^k$  ，用 $n!$  除尽 $p$ 再取模得到$\frac{n!}{p^a} \mod p^k$ 最后再把提出来的 $p$ 乘进去(即乘$Pow(p,cnt)$)就行了。**

具体实现可以看看[这篇博客](https://blog.csdn.net/hqddm1253679098/article/details/82897638)。

为了防止 $TLE$，可以直接线性预处理，利用递推关系求出对于所有阶乘的应对方式（即所有 $n$ 的 $\frac{n!}{p^a} \mod p^k$）,具体见代码。


另一个问题就是从 $s$ 中消除本位影响的问题，当我们这一位的问题解决了而前往下一位的时候，那重复的本位数字就会少 $1$ ，如果 $num[i]>=2$ 应当从 $s$ 中先把 $inv[\ fac[\ num[i]\ ]\ ]$ 的影响消除，再乘上 $inv[\ fac[\ num[i]-1\ ]\ ]$ 。而消除自然要除以 $inv[\ fac[\ num[i]\ ]\ ]$ ，这时候我发现了某数逆元的逆元是其本身的道理，$So$消除时直接乘上 $fac[num[i]]$ 就行了。

另外就最后乘 $Pow(p,cnt)$ 时，不能从头再来算，$cnt$ 在本位结束后也要消除 $num[i]$ 影响并产生新的 $num[i]-1$ 下的 $cnt$ ，这样每次只要重新计算 $fac[n-i]$ 的 $cnt$ 就可以了。但是我发现这个过程还会 TLE，因此我就把 $Pow(p,cnt)$ 中从一到三千的 $cnt$ 都线性递推预处理出来了，毕竟 $cnt$ 不太可能到 $3000$ ，然后就 AC 了！

## 代码

```cpp


#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll c[500000];
ll a[500000];
ll as[500000];
ll b[500000];
ll d[500000];
ll num[500000];
ll f[500000];
ll m[500000];//pk
ll mo[500000];//p
ll fu[500000];
ll n,mk;
ll maxn;
ll tot;
ll phi[500000];
ll s; 
ll cnt;
ll mu[500000];
ll Pows[500000];
ll Pow(ll a,ll b,const ll p=LLONG_MAX)
{
	ll ans=1;
	while(b)
	{
		if(b&1)
			ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
ll di=1;
ll div(ll n)
{
	ll tmp=mk; tot=0;
    for (ll i=2;1ll*i*i<=tmp;i++) if (tmp%i==0)
    {
        mo[++tot]=i; m[tot]=1;
        while (tmp%i==0) tmp/=i,m[tot]*=i;
    }
    if (tmp>1) mo[++tot]=tmp,m[tot]=tmp;
    for (ll i=1;i<=tot;i++) phi[i]=m[i]-m[i]/mo[i];
}
ll lowbit(ll x)
{
	return x&(-x);
}
void update(ll x,ll val)
{
	while(x<=maxn)
	{
		c[x]+=val;
		x+=lowbit(x);
	}
}
ll query(ll x)
{
	ll ans=0;
	while(x>0)
	{
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
} 
ll fac(ll n,ll p,ll pk)
{
	if(!n)return 1;
	ll ans=1;
	for(ll i=1;i<pk;i++)
		if(i%p)
			ans=ans*i%pk;
	ans=Pow(ans,n/pk,pk);
	for(ll i=1;i<=n%pk;i++)
		if(i%p)
			ans=ans*i%pk;
	return ans*fac(n/p,p,pk)%pk;
}
ll inv(ll x,ll p)
{
	return Pow(x,phi[p]-1,m[p]);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b)
		x=1,y=0;
	else
	{
		exgcd(b,a%b,y,x);
		y-=x*(a/b);
	}
}
ll CRT(ll k)
{
	ll ANS=0,lcm=1,x,y;
	for(ll i=1;i<=k;++i)
		lcm*=m[i];
	for(ll i=1;i<=k;++i)
	{
		ll M=lcm/m[i];
		exgcd(M,m[i],x,y);
		x=(x%m[i]+m[i])%m[i];
		ANS=(ANS+M*x*as[i])%lcm;
	}
	return (ANS+lcm)%lcm;
}
int main()
{
	scanf("%lld%lld",&n,&mk);
	div(mk);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	ll len=unique(b+1,b+n+1)-b-1;
	for(ll i=1;i<=n;i++)
		{
			a[i]=lower_bound(b+1,b+len+1,a[i])-b;
			maxn=max(maxn,a[i]);
			num[a[i]]++;	
		}
	for(ll i=1;i<=n;i++)update(a[i],1);
	for(ll i=1;i<=maxn;i++)
	{
		mu[i]=c[i];
		fu[i]=num[i];
	}
	ll TJ=0;
	for(ll k=1;k<=tot;k++)
	{
		ll bnum=0;
		for(ll i=1;i<=maxn;i++)
		{
			c[i]=mu[i];
			num[i]=fu[i];
			bnum=max(num[i],bnum);
		}
		s=1;
		cnt=0;
		f[0]=1;
		for(ll i=1;i<=n;i++)
		{
			ll x=i;
			while(x%mo[k]==0)x/=mo[k];
			f[i]=(f[i-1]%m[k])*(x%m[k])%m[k];
		}
		for(ll i=1;i<=maxn;i++)
		{
			s=s*inv(f[num[i]],k)%m[k];
			for(ll j=num[i];j;j/=mo[k])
				cnt-=j/mo[k];
		}
		Pows[0]=1;
		for(int i=1;i<=3000;i++)
		{
			Pows[i]=ll((Pows[i-1]%m[k])*(mo[k]%m[k]))%m[k];
		}
		ll ans=0;
		for(ll i=1;i<=n;i++)
		{
			ll xs=query(a[i]-1);
			ll ys=f[n-i];
			for(ll j=n-i;j;j/=mo[k])
				cnt+=j/mo[k];
			ll res=ll((ys%m[k])*(s%m[k]))%m[k];
			res=ll((res%m[k])*(Pows[cnt]%m[k]))%m[k];
			res=ll((res%m[k])*(xs%m[k]))%m[k];
			as[k]=(as[k]%m[k] + res%m[k])%m[k];																						              update(a[i],-1);
			for(ll j=n-i;j;j/=mo[k])
				cnt-=j/mo[k];	
			if(num[a[i]]>=2)
			{
				s=s*f[num[a[i]]];
				for(ll j=num[a[i]];j;j/=mo[k])
					cnt+=j/mo[k];
				s=(s%m[k])*(inv(f[num[a[i]]-1],k)%m[k])%m[k];
				num[a[i]]--;
				for(ll j=num[a[i]];j;j/=mo[k])
					cnt-=j/mo[k];
			}
		}
 	}
 	ll ANS=CRT(tot)+1;
	cout<<ANS%mk<<endl;
}
```


---

## 作者：Zory (赞：2)

对$O(nlogn)$的做法奋战最后顺利bzoj和洛谷rk1，做法和cls的基本一样

首先如果m为质数就是道简单题，逐位考虑，设$now_j$为后缀中j的次数

$$
ans(k)=ans(k+1)+\frac{(n-k)!}{\prod_j now_j!}(\sum_j now_j)
$$

一开始用树状数组预处理出每个数后面更小的数字和，这样就是$O(nlogn)$的

现在m比较一般，可以有很多种处理方法，这里只介绍最直接自然的CRT，设当前模数为$d^k$，那么因为有阶乘除法需要把d提出来算

不妨搞个二元组$(a,b)=a+d^b$，把阶乘之类的用这个二元组搞，定义一下乘除法就好了，网上也基本上是这样，然而复杂度还是log方，主要是求逆元的问题。

cls用的是线性递推逆元，这我不是很理解在$p^k$的k>1的时候为什么能用，故我采用的是线筛+欧拉定理，因为素数为分布约为n/ln，然后注意到$p^k$只会超过$\sqrt m$最多一次，可以用exgcd求逆元；

综合复杂度为$O(nlogn)$

[code](https://www.luogu.org/paste/wune6kr6)



---

## 作者：bianshiyang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3477)

发现居然跑到了最优解，于是写篇题解纪念一下，顺便严格证明了一下答案的式子。

# 分析
如果 $a_i$ 两两不同，那么就变成[这题](https://www.luogu.com.cn/problem/P5367)，我们可以从这道题里借鉴一些经验：按照从左到右的顺序扫描每一个 $a_i$，统计若第 $i$ 位放置**在 $i$ 位置后且比 $a_i$ 小的数**能产生多少种排列方式，累加到答案里，然后钦定第 $i$ 位放置 $a_i$，继续考虑下一位。容易证明这样的做法是对的。

本题的关键就是求出若第 $i$ 位放置**在 $i$ 位置后且比 $a_i$ 小的数**能产生多少种排列方式。~~学过高中数学排列组合的都知道~~，对于一个可重集 $S=\{n_1\cdot a_1,n_2\cdot a_2,\cdots,n_k\cdot a_k\}$ 是由 $n_1$ 个 $a_1$，$n_2$ 个 $a_2$，$\cdots$，$n_k$ 个 $a_k$ 组成的多重集，记 $n=\sum\limits_{i=1}^k n_i$，$S$ 的全排列个数为：
$$\frac{n!}{\prod\limits_{i=1}^k n_i!}$$

这式子挺好理解的，就是先全排列，然后把重复的除掉（也可以设答案然后利用乘法原理得到全排列，再把乘的东西除过去）。

那么我们假设现在枚举到第 $i$ 位了，后面有 $s_i$ 个数比 $a_i$ 小，假设这些数分别为 $b_1,b_2,\cdots,b_{s_i}$，这里重复的也一起算了（换句话说 $b_j$ 之间可能会互相重复）。我们考虑第 $i$ 位放置 $b_j$ 产生的贡献，记 $\operatorname{cnt}_k$ 表示数 $k$ 在 $b_1,b_2,\cdots,b_{s_i}$ 中出现了多少次。那么此时贡献为 
$$\frac{(n-i)!}{(\operatorname{cnt}_{b_j}-1)!\prod\limits_{k\neq b_j}  \operatorname{cnt}_k!}=\frac{\operatorname{cnt}_{b_j}(n-i)!}{\prod\limits_{k}  \operatorname{cnt}_k!}$$

由于相同的 $b_j$ 的贡献相同且只应该被计算一次，故第 $i$ 位所产生的答案为 $\sum \frac{\operatorname{cnt}_{b_j}(n-i)!}{\prod\limits_{k}  \operatorname{cnt}_k!}=\frac{s_i(n-i)!}{\prod\limits_{k}  \operatorname{cnt}_k!}$。仔细观察这个式子，发现分母从后往前扫要更容易计算，因为每次只需要考虑多增加的 $\operatorname{cnt}_{a_i}$。分子中的 $(n-i)!$ 容易计算，而 $s_i$ 可以用权值树状数组计算，所以式子的贡献就都可以计算出来。

不过此题还是一个难点就是模数不一定与分母互质，换句话说，分母不一定存在逆元。注意到，上述式子在不取模的情况下实际上是个整数，所以我们可以将分母与模数不互质的部分先与分子进行约分，剩下的部分用扩展欧几里得求出逆元拼在一起即可。

具体地，我们对 $m$ 质因数分解，容易证明分解出来的质数个数不超过 $9$ 个，每次将分母拆成两部分：与这些质数互质的部分和不互质部分，互质的部分使用逆元解决，不互质的部分与分子约分再和互质的部分求出的结果相乘即得到答案（具体可以看代码）。

为了让代码~~跑到最优解~~更快，我们可以提前预处理每个质数的指数幂，至于需要处理多大的指数幂，我们可以求出一个较准确的上界（~~都是为了代码效率~~）。因为 $2$ 的幂次应该出现的最多，所以直接考虑 $2$ 的幂次的上限。若答案式子中分母为 $1$，而分子取到最大值 $(n-1)(n-1)!$，那么此时可以达到上限，令 $n=2^k+1$（$k$ 为某个正整数），则幂次的上限应该是 $\lfloor\log_2n\rfloor+\lfloor\frac{n}{2}\rfloor+\lfloor\frac{n}{2^2}\rfloor+\lfloor\frac{n}{2^3}\rfloor+\cdots=k+n-1$，处理到 $n+19$ 一定可以满足条件。虽然预处理到 $n$ 也可以过，但是会被下面这组数据 hack 掉：

```
input:
17 382205952
9 8 7 6 5 4 3 2 1 10 11 12 13 14 15 16 17

output:
217696897
```

  时间复杂度 $O(n\omega(m)\log n)$（$\omega(m)$ 表示 $m$ 质因数分解后质因数的个数，这里 $\omega(m)\le 9$），实际运行时间远远到不了这个上界。

# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+20;
int n,m,s,maxx,a[N],c[N],ans=1,res=1;//ans初始值为1是因为是计算排名，所以要加上自己，res表示分子和分母互质的部分对m取模的结果
int cnt[N],t[10],po[10][N];
vector<int> p;//存质数
void update(int x,int y){while(x<=maxx)c[x]+=y,x+=x&(-x);}
int query(int x){int res=0;while(x)res+=c[x],x-=x&(-x);return res;}//树状数组基本操作

void init(int x)//质因数分解m
{
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
		{
			p.push_back(i);
			while(x%i==0) x/=i;
		}
	if(x>1) p.push_back(x);
	s=p.size();
	for(int i=0;i<s;i++)
	{
		po[i][0]=1;
		for(int j=1;j<n+20;j++) po[i][j]=1ll*po[i][j-1]*p[i]%m;
	}//预处理每个质数的幂次
}

void exgcd(int x,int y,ll &a,ll &b)
{
	if(y==0) {a=1,b=0;return;}
	exgcd(y,x%y,a,b);
	ll c=a;a=b;b=c-b*(x/y);
}

int inv(int x)//求逆元
{
	ll a,b;
	exgcd(x,m,a,b);
	return (a%m+m)%m;
}

void add(int x,int f)//约分函数，f=1表示分子,f=-1表示分母
{
	if(x==0) return;
	for(int i=0;i<s;i++)
	{
		int tot=0;
		while(x%p[i]==0) tot++,x/=p[i];
		t[i]+=f*tot;
	}
	if(f==1) res=1ll*res*x%m;
	else res=1ll*res*inv(x)%m;
}

int calc()//计算约分后的结果
{
	int res=1;
	for(int i=0;i<s;i++) res=1ll*res*po[i][t[i]]%m;
	return res;
}

int main()
{
	scanf("%d%d",&n,&m);
	init(m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),maxx=max(maxx,a[i]);
	for(int i=n;i;i--)
	{
		update(a[i],1);
		int s=query(a[i]-1),x=++cnt[a[i]];
		add(n-i,1);add(x,-1);
		if(!s) continue;
		else add(s,1),ans=(ans+1ll*res*calc()%m)%m,add(s,-1);//注意这里要先加上s的贡献，再消去s的贡献，因为除去s的那一坨可能不是整数
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Melting_Pot (赞：0)

# PER-Permutation [P3477](https://www.luogu.com.cn/problem/P3477)
- ## 题目大意：
  一个元素个数为 $n$ 的多重集的一个排列和 $m$，求这个排列的字典序排名取模 $m$。
- ## 思考：
  - 首先，我们显然能够根据题意想到[康托展开](https://www.luogu.com.cn/problem/P5367)，但它们之间当然是有区别的（_~~这不是废话么~~_），本题的排列是一个可重的，范围不定的，不连续的无序排列。
  - 知道了区别，下一步呢？我们仍可以依照康托展开的思想，对排列的每一位进行考虑。
  - 本题的任意模数并不十分友好，因为在这种意义下逆元并不存在，因此考虑将模数分解，对每一个互质于当前答案贡献的模数分别计算，最后合并即可。
- ## 实现：
  - ### 式子：
    - $$ ans=\sum^n_{i=1}{\frac{val_{a_i}(n-i)!}{\prod^{col_{a_i}}_j{cnt_j!}}} $$
    - 式子中的 $a$ 为原排列，$val_i$ 表小于 $a_i$ 的，且未访问过的数的个数，$col_i$ 为原排列中，从 $i$ 到 $n$ 的数的种类数，$cnt$ 则是一个桶。
  - ### 转化：
    - 因为模数的不确定性，导致逆元无法求，因此我们先将模数 $p$ 分解为质因数 $p_i$，再把每一个 $ans_i$ 中存在的 $p$ 的因数消去，这样也就保证了 $ans_i$ 与 $p$ 互质，逆元也就十分好求了。
    - $ans_i$ 是分数的形式，因此我们要对分子分母分别消去 $p$ 的质因子，最后我们当然要把消去的质因子再乘回来，而 $ans_i$ 一定是个整数，也就是说，对于一个 $p_i$，分子中的数量一定比分母中的大，那么消去的（或者说需要乘回来的）质因子的形式也就是 ${p_i}^k(k\in \mathbb{Z})$。
    - 我们需要阶乘，而任意模数意义下的阶乘需要与当前答案贡献（也就是 $ans_i$）消去的质因子保持一致，预处理显然不现实，因此我们倒序枚举 $i$，处理分子分母的同时累计相乘，也就同时求出了 $(n-i)!$ 与 $cnt_j!$。
    - 接下来就是数据结构优化一下，不再赘述。
- ## 注意：
  - 要记得消除对 $val$ 的影响，因为它不具有累积效应。
  - 每走一步，先累积 $cnt$，再消除模数质因数。
- ## 代码（~~非常丑陋~~）：

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=10000010;
int n,p,x,y,maxn(0);
int son(1),mum(1),ans(0);
int cntson[N],cntmum[N];
int a[N],cnt[N],pmod[N],dat[N<<2];
int query(int pos,int l,int r,int ll,int rr){
  	if(!rr) return 0;
  	if(ll<=l&&r<=rr) return dat[pos];
  	int mid(l+r>>1),ans(0);
  	if(ll<=mid) ans+=query(pos<<1,l,mid,ll,rr);
  	if(mid<rr) ans+=query(pos<<1|1,mid+1,r,ll,rr);
  	return ans;
}
void modify(int pos,int l,int r,int x){
  	if(l==r) {dat[pos]++;return;}
  	int mid(l+r>>1);
  	if(x<=mid) modify(pos<<1,l,mid,x);
  	else modify(pos<<1|1,mid+1,r,x);
  	dat[pos]=dat[pos<<1]+dat[pos<<1|1];
}
int pow(int a,int k,int p){
  	int ans(1);
  	for(;k;a=a*a%p,k>>=1) if(k&1) ans=ans*a%p;
  	return ans;
}
void exgcd(int a,int b,int &x,int &y){
  	if(!b){x=1,y=0;return;}
  	exgcd(b,a%b,y,x),y=(y-(a/b)*x%p+p)%p;
}
void updateson(int x){
  	if(!x) return;
  	for(int i=1;i<=pmod[0];++i){
  		while(x%pmod[i]==0) {cntson[i]++,x/=pmod[i];}
  	}
  	son=son*x%p;
}
void updatemum(int x){
  	if(!x) return;
  	for(int i=1;i<=pmod[0];++i){
  		while(x%pmod[i]==0) {cntmum[i]++,x/=pmod[i];}
  	}
  	mum=mum*x%p;
}
int update(int x,int pos){
  	if(!x) return 0;
  	for(int i=1;i<=pmod[0];++i){
  		while(x%pmod[i]==0) cntson[i]+=pos,x/=pmod[i];
  	}
  	return x;
}
#undef int
int main(){
  	#define int long long
  	scanf("%lld%lld",&n,&p);
  	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),maxn=std::max(maxn,a[i]);
  	int mod=p;
  	for(int i=2;i<=std::sqrt(mod);++i){
  		if(mod%i) continue;
  		pmod[++pmod[0]]=i;
  		while(!(mod%i)) mod/=i;
  	}
  	if(mod!=1) pmod[++pmod[0]]=mod;
  	for(int i=n;i>=1;--i){
  		int aa(1);
  		++cnt[a[i]];
  		updatemum(cnt[a[i]]);
  		updateson(n-i);
  		modify(1,1,maxn,a[i]);
  		int nn(query(1,1,maxn,1,a[i]-1)),tem;
  		tem=update(nn,1);
  		for(int j=1;j<=pmod[0];++j) 
  			aa=aa*pow(pmod[j],std::abs(cntmum[j]-cntson[j]),p)%p;
  		exgcd(mum,p,x,y);
  		x=(x%p+p)%p;
  		aa=aa*(tem*son%p)%p*x%p;
  		update(nn,-1);//消除影响
  		ans=(ans+aa)%p;
  	}
  	std::cout<<((ans+1)%p+p)%p;
}
```

---

