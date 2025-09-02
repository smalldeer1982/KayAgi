# Array Splitting

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ and an integer $ k $ .

You are asked to divide this array into $ k $ non-empty consecutive subarrays. Every element in the array should be included in exactly one subarray. Let $ f(i) $ be the index of subarray the $ i $ -th element belongs to. Subarrays are numbered from left to right and from $ 1 $ to $ k $ .

Let the cost of division be equal to $ \sum\limits_{i=1}^{n} (a_i \cdot f(i)) $ . For example, if $ a = [1, -2, -3, 4, -5, 6, -7] $ and we divide it into $ 3 $ subbarays in the following way: $ [1, -2, -3], [4, -5], [6, -7] $ , then the cost of division is equal to $ 1 \cdot 1 - 2 \cdot 1 - 3 \cdot 1 + 4 \cdot 2 - 5 \cdot 2 + 6 \cdot 3 - 7 \cdot 3 = -9 $ .

Calculate the maximum cost you can obtain by dividing the array $ a $ into $ k $ non-empty consecutive subarrays.

## 样例 #1

### 输入

```
5 2
-1 -2 5 -4 8
```

### 输出

```
15
```

## 样例 #2

### 输入

```
7 6
-3 0 -1 -2 -2 -4 -1
```

### 输出

```
-45
```

## 样例 #3

### 输入

```
4 1
3 -1 6 0
```

### 输出

```
8
```

# 题解

## 作者：米奇 (赞：10)

## 思维题

当时比赛时一看到题还以为是dp，后发现不对。

观察这题有什么奇怪的特征，就是每段乘的数是一次加1的。

考虑一段区间比如说是形如:2A3B,现在要使这段区间整体后移一位，就变成了:3A4B。发现就是加上了一个区间和sum。

那么答案可以看成k段后缀区间的和（注意区间1-n是一定要的）

##代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int n,k,ans,a[N],b[N];
multiset<int,greater<int> >s;
multiset<int,greater<int> >::iterator it;
signed main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);	
    for(int i=n;i;i--)b[i]=b[i+1]+a[i];
    b[1]+=1e15;
    sort(b+1,b+n+1);
    for(int i=n;i>=n-k+1;i--)ans+=b[i];
    int x=1e15;
    printf("%lld",ans-x);
    return 0;
}
```

---

## 作者：Mr_Wu (赞：7)

我们可能可以列出一个类似斜率优化的式子，不过对于这个复杂度没有用。

那我们只好找找规律，令 $m_i$ 表示第 $i$ 段的结束位置，比如

$a=[1,-2,-3,4,-5,6,-7]$ 分段 $[1,-2,-3],[4,-5],[6,-7]$ 后 $m_1=3,m_2=5,m_3=7$。规定一下 $m_0=0$.

那么这个分段方法的权值应该是

$$ \sum_{i=1}^k i\times (S_{m_i}-S_{m_{i-1}}) $$

其中 $S_i$ 表示 $\sum\limits_{j=1}^i a_j$，也就是前缀和。这么算的目的是 $S_r-S_{l-1}$ 表示 $\sum\limits_{i=l}^{r} a_i$，而每段的代价是这一段的编号乘上这一段的和，也就是 $i\times (S_{m_i}-S_{m_{i-1}})$ 了。

把上面那个式子化开：

$$ \begin{aligned} & \sum_{i=1}^k i\times (S_{m_i}-S_{m_{i-1}}) \\ & = \sum_{i=1}^k iS_{m_i}-\sum_{i=1}^{k} iS_{m_{i-1}} \\ &= \sum_{i=1}^k iS_{m_i}-\sum_{i=0}^{k-1} (i+1)S_{m_i} \\ &= kS_{m_k}-\sum_{i=1}^{k-1} S_i \end{aligned} $$

现在问题明朗了，$kS_{m_k}=kS_n$ 是个定值，我们只需要让 $\sum\limits_{i=1}^{k-1} S_i$ 最小，而我们只需要在 $S_1,S_2,\cdots,S_{n-1}$ 中选取 $k-1$ 个最小的，排序一遍就行了。

复杂度 $O(n\log n)$

```cpp
#include <cstdio>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

inline ll read()
{
    char c = getchar();
    ll ret = 0, t = 1;
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') t = -1, c = getchar();
    while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret * t;
}

#define MAXN 300005

int N, K;
ll a[MAXN], s[MAXN], ans;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif
    N = read(), K = read(); int i;
    for (i = 1; i <= N; ++i) s[i] = s[i - 1] + read();
    std::sort(s + 1, s + N);
    for (i = 1; i < K; ++i) ans -= s[i];
    ans += K * s[N];
    printf("%I64d", ans);
    return 0;
}
```

---

## 作者：StephenYoung (赞：5)

#### 大意

有一段长度为n的序列，要分成$k$段，第$i$段要乘上$i$，求最大值，即$ans=\sum_{i=1}^ki*sum_{p_i}$。

#### 思路

简化式子+前缀和

#### 实现

$ans=\sum_{i=1}^ki*sum_{p_i}$

$=$
$sum_{p_1}+2*(sum_{p_2}-sum_{p_1})+3*(sum_{p_3}-sum_{p_2})+...+k*(sum_{p_k}-sum_{p_{k-1}})$

$=$
$k*(sum_n)-\sum_{i=1}^{k-1}sum_{p_i}$

#### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=300050;
ll n,k,a[maxn],s[maxn],ans=-10000000000,tot;

int main()
{
	scanf("%lld%lld",&n,&k);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];
	}
	sort(s+1,s+n);
	for(ll i=1;i<k;i++)
	{
		tot+=s[i];
	}
	printf("%lld",s[n]*k-tot);
	return 0;
}
```


---

## 作者：gorokokoro (赞：2)

设 $f(i,\,j)$ 为将后 $i$ 个数字分为 $j$ 段的最大价值，则有简单 $\text{DP}$：$f(i,\,j)=\sum_{t=i}^na_t+\max_{t=i+1}^nf(t,\,j-1)$ 。

答案即为 $f(1,\,k)$ 。显然这个是平方级别复杂度。

如果认真观察，则可发现这个 $\text{DP}$ 实际上只是将最大的 $k-1$ 个后缀和加在了一起，最后加上了整个序列的和。因此直接贪心取出最大的 $k-1$ 个后缀和即可。

当然我现场是并没有想到这个办法，但打表发现 $f$ 满足函数凸性，于是可以直接使用 $\text{wqs}$ 二分解决。

注意二分边界不能太大，不然乘上 $n$ 之后会爆掉。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#define N 300020
using namespace std;

class Data
{
public:
    long long x;
    long long y;

    Data(long long _x = 0, long long _y = 0) : x(_x), y(_y)
    {
        return;
    }

    Data operator+(const Data &that) const
    {
        return Data(this -> x + that.x, this -> y + that.y);
    }

    bool operator<(const Data &that) const
    {
        return this -> x != that.x ? this -> x < that.x : this -> y > that.y;
    }
};

long long a[N];
Data f[N];
long long g[N];

void DP(long long n, long long k)
{
    long long i;
    Data v;

    f[n] = Data(a[n] + k, 1);
    for(i = n - 1; i >= 1; i --)
    {
        v = max(v, f[i + 1]);
        f[i] = v + Data(g[i] + k, 1);
    }

    return;
}

long long BSFind(long long n, long long k)
{
    long long l, m, r;

    for(l = -1000000000000, r = 1000000000000; l + 1 < r; )
    {
        m = (l + r) >> 1;
        DP(n, m);

        if(f[1].y <= k)
            l = m;
        else
            r = m;
    }

    DP(n, l);

    return f[1].x - l * k;
}

int main(void)
{
    long long n, k;
    long long i;

    scanf("%I64d %I64d", &n, &k);
    for(i = 1; i <= n; i ++)
        scanf("%I64d", &a[i]);
    for(i = n; i >= 1; i --)
        g[i] = g[i + 1] + a[i];
    printf("%I64d\n", BSFind(n, k));

    return 0;
}
```


---

## 作者：localhost (赞：0)

咋一看：

$f[i][j] = MAX(f[i-1][j-1]+a[j]*i,f[i][j-1]+a[j]*j)$

但$n \le 3 \times 10^5$,。。。

。。。

那么其实这不是dp题，而是思维题

我们发现：

$(s[r]-s[l])\times k +(s[r']-s[l'])\times(k-1)+...+s[r''']$

$s$表示前缀和，$g$表示后缀和

相当于：

$g[x_1]+g[x_2]+g[x_3]+...$

那我们给后缀和排个序就可以了

### 注意：

答案里必须要有$g_1$，这就是为什么要$g_1$加$(1ll<<50)$再答案减$(1ll<<50)$的原因,还有记得$long\ long$



```cpp
#include<bits/stdc++.h>
namespace ZDY{
	#pragma GCC optimize(3)
	#define il __inline__ __attribute__ ((always_inline))
	#define rg register
	#define ll long long
	#define ull unsigned long long
	#define db double
	#define sht short
	#define MB template <class T>il
	#define Fur(i,x,y) for(int i=x;i<=y;i++)
	#define Fdr(i,x,y) for(int i=x;i>=y;i--)
	#define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
	#define clr(x,y) memset(x,y,sizeof(x))
	#define cpy(x,y) memcpy(x,y,sizeof(x))
	#define fin(s) freopen(s".in","r",stdin)
	#define fout(s) freopen(s".out","w",stdout)
	#define fcin ios::sync_with_stdio(false)
	#define l2(n) (int(log2(n)))
	#define inf 0x3f3f3f3f
	MB T ABS(T x){return x>0?x:-x;}
	MB T MAX(T x,T y){return x>y?x:y;}
	MB T MIN(T x,T y){return x<y?x:y;}
	MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
	MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 300011
ll n,k,g[N],a[N],ans=0;
int main(){
	in>>n>>k;
	Fur(i,1,n)in>>a[i];
	Fdr(i,n,1)g[i]=g[i+1]+a[i];g[1]+=1ll<<50;
	sort(g+1,g+n+1);
	Fdr(i,n,n-k+1)ans+=g[i];
	ans-=1ll<<50;
	out<<ans<<ln;
}
```

---

## 作者：hpbl (赞：0)

设第$i$段的左端点为$l_i$，则$l_1 = 1$,右端点$r_i=\begin{cases} l_{i+1}-1 \ (i<k) \\ n \ (i=k) \end{cases}$

记$sum_i$为$a$的后$n-i+1$个数的和即从$a_i$加到$a_n$的和（后缀和）

$ \sum\limits_{i=1}^{n} (a_i \cdot f(i)) = \sum\limits_{i=1}^k \sum\limits_{j=l_i}^{r_i}(i \cdot a_i) = \sum\limits_{i=1}^k \sum\limits_{j=l_i}^n a_j = \sum\limits_{i=1}^{n} sum_{l_i} = sum_1 + \sum\limits_{i=2}^nsum_{l_i}$

由于$l_i \ (i>1)$可以是$2 , 3, \cdots , n$中的任意$k-1$个不同数的一个有序排列，因此取$sum_2 , sum_3 , \cdots , sum_n$中的前$k-1$大的值之和加上$sum_1$即可。

可以用$multiset$维护。

Code:

```cpp

 #include<cstdio>
#include<set>
using namespace std;
typedef long long ll;
int n,k;
ll a[300001],sum[300002],ans;
multiset<ll> s;
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=n;i;i--) sum[i]=sum[i+1]+a[i];
	for(int i=2;i<=n;i++)
	{
		s.insert(-sum[i]);
		if(s.size()>=k) s.erase(--s.end());
	}
	for(set<ll>::iterator it=s.begin();it!=s.end();it++) ans-=*it;
	printf("%lld\n",ans+sum[1]);
}
```



---

## 作者：Moon_Lighter (赞：0)

## 题意： 
给出一个长度为 $n$ 的序列 $a$ ，题目要求分为恰好 $Q$ 段。求的是第 $i$ 个点的贡献是 $a_i(f(i),f(x))$ 表示 $x$ 所属的是第几段。

## 思路： 
 $1·$ 让每个元素都选 $Q$ 遍。然后不断的删除。

 $2·$ 先求一遍前缀和。然后找出前缀和最小的 $Q-1$ 个前缀，将其从答案中减去。初始答案为所有元素和 $×K$ 。

 $3·$ 被减 $s$ 遍的元素就位于第 $Q-s$ 段中。
 
 $4·$ 按以上操作即符合题意。

## 代码： 
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
long long s[maxn];
int main(){
    int n,j;scanf("%d%d",&n,&j);
    for(int i=1,x;i<=n;++i){
 	    scanf("%d",&x),s[i]=s[i-1]+x;
    }
    long long a=(long long)j*s[n];
    sort(s+1,s+n-1+1);
    --j;
    for(int i=1;j;--j,++i){
     	a-=s[i];
    }
    printf("%lld\n",a);
    return 0 
}


```

---

## 作者：Xie_BR (赞：0)

这道题有一些大佬会说：  
# 结构体就搞定了    
于是本蒟蒻准备试一试，没想到还成功了Orz  

所以我们来看一看这道题：  
1、存一个id & val  
2、每一次输入的val赋值为前面的和，这样sort的时候就可以避免重复了Orz  
3、最后的判断，我们来看代码吧~~~  

## AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long
#define MK 10000010
using namespace std;
int n,k;

struct node
{
	int id,val;
}e[MK];

int cmp(node a,node b)
{
	return a.val < b.val;
}

signed main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&e[i].val);
		e[i].val += e[i-1].val;
		e[i].id = i;
	}
	int res = e[n].val*k;
	sort(e+1,e+n+1,cmp);
	int step = 0;
	for(int i=1;i-step <= k-1;i++)
	{
		if(e[i].id==n)
		{
			step = 1;
			continue;
		}
		res-=e[i].val;
	}
	printf("%lld\n",res);
	return 0;
}
```

# ：）

---

