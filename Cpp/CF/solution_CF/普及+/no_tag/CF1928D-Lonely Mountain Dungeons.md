# Lonely Mountain Dungeons

## 题目描述

Once, the people, elves, dwarves, and other inhabitants of Middle-earth gathered to reclaim the treasures stolen from them by Smaug. In the name of this great goal, they rallied around the powerful elf Timothy and began to plan the overthrow of the ruler of the Lonely Mountain.

The army of Middle-earth inhabitants will consist of several squads. It is known that each pair of creatures of the same race, which are in different squads, adds $ b $ units to the total strength of the army. But since it will be difficult for Timothy to lead an army consisting of a large number of squads, the total strength of an army consisting of $ k $ squads is reduced by $ (k - 1) \cdot x $ units. Note that the army always consists of at least one squad.

It is known that there are $ n $ races in Middle-earth, and the number of creatures of the $ i $ -th race is equal to $ c_i $ . Help the inhabitants of Middle-earth determine the maximum strength of the army they can assemble.

## 说明/提示

In the first test case, the inhabitants of Middle-earth can form $ 3 $ squads. Since $ x = 0 $ , the army's strength will not decrease due to the number of squads. The inhabitants can be distributed among the squads as follows:

- The single representative of the first species can be sent to the first squad.
- The first representative of the second species can be sent to the first squad, the second representative of the second species can be sent to the second squad. Then the total strength of the army will increase by $ b = 1 $ .
- The first representative of the third species can be sent to the first squad, the second representative of the third species can be sent to the second squad, the third representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 3 \cdot b = 3 $ , as they form three pairs in different squads.

Thus, the total strength of the army is $ 4 $ .

In the second test case, the inhabitants of Middle-earth can form $ 3 $ squads. Since $ x = 10 $ , the army's strength will decrease by $ 20 $ . The inhabitants can be distributed among the squads as follows:

- The first representative of the first species can be sent to the first squad, the second representative of the first species can be sent to the second squad. Then the total strength of the army will increase by $ b = 5 $ .
- The first and second representatives of the second species can be sent to the first squad, the third and fourth representatives of the second species can be sent to the second squad, the fifth representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 8 \cdot b = 40 $ .
- The first representative of the third species can be sent to the first squad, the second representative of the third species can be sent to the second squad, the third representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 3 \cdot b = 15 $ , as they form three pairs in different squads.

Thus, the total strength of the army is $ 5 + 40 + 15 - 20 = 40 $ .

## 样例 #1

### 输入

```
5
3 1 0
1 2 3
3 5 10
2 5 3
4 3 3
3 2 1 2
4 1 0
4 1 4 2
4 1 10
4 1 4 2```

### 输出

```
4
40
9
13
0```

# 题解

## 作者：FFTotoro (赞：8)

这道题送我上紫名。

似乎大部分人的做法都是二分、三分。这里提供一个组合数学 + 差分的赛时做法。

首先观察到每个族群互相独立，又因为 $\sum c_i\le 2\times 10^5$，这启发我们对于每个族群分别求解答案最后合并。

对于一个有 $c$ 人族群，考虑将其分成 $x$ 个队伍是能获得的最大价值。根据初中的简单不等式知识，显然要尽量将其均分才能产生最大价值，具体地，将其分为 $x_1=c\bmod x$ 个有 $p_1=\left\lceil\dfrac{x}{c}\right\rceil$ 人的队伍和 $x_2=x-c\bmod x$ 个有 $p_2=\left\lfloor\dfrac{x}{c}\right\rfloor$ 的队伍。运用简单组合数学知识，能得出产生的价值为同一种小队之间的价值 $\dfrac{p_1^2bx_1(x_1-1)}{2}+\dfrac{p_2^2bx_2(x_2-1)}{2}$ 与不同种小队之间产生的价值 $p_1p_2bx_1x_2$ 之和。于是对于每个 $x(1\le x\le c_i)$ 分别计算即可。

最后统计答案的时候，如果枚举到的队伍数比前面某个族群的人数 $c_i$ 还大，那么它的贡献应该为队伍为 $c_i$ 时的贡献。赛时暴力维护 T 了一发后直接拍个线段树上去，赛后发现可以用差分数组更为简单的维护。于是时间复杂度 $O(\sum c_i)$，可以通过此题。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
int C2(int x){
  return x*(x-1)>>1;
}
main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,b,m=1,x; cin>>n>>b>>x;
    vector<int> c(n);
    for(auto &i:c)cin>>i,m=max(m,i);
    vector<int> d(m+1);
    auto upd=[&](int l,int r,int x){
      d[l]+=x; if(r<m)d[r+1]-=x;
    };
    for(int i=0;i<n;i++){
      vector<int> s(c[i]+1);
      for(int j=1;j<=c[i];j++){
        int y=c[i]/j,x1=c[i]%j,x2=j-x1;
        s[j]=(y+1)*(y+1)*b*C2(x1)+y*y*b*C2(x2)+y*(y+1)*b*x1*x2;
        upd(j,j,s[j]);
      }
      if(c[i]+1<=m)upd(c[i]+1,m,s[c[i]]);
    }
    int w=0;
    for(int i=1;i<=m;i++)
      w=max(w,(d[i]+=d[i-1])-(i-1)*x);
    cout<<w<<'\n';
  }
  return 0;
}
```

---

## 作者：int_R (赞：3)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18013982/CF1928D)

[原题链接](https://www.luogu.com.cn/problem/CF1928D)

设 $F(n,m)$ 是将 $n$ 个同种族的人放到 $m$ 个队伍中可以获得的贡献。可以发现在同一个队伍中的人不能互相产生贡献，所以尽可能平均分配是最优的。

设 $p=\lfloor \dfrac{n}{m}\rfloor,q=n\bmod m$，那么有 $m-q$ 个队伍中有 $p$ 个人，$q$ 个队伍中有 $p+1$ 个人，贡献是

$$F(n,m)=\dfrac{n(n+1)}{2}-(m-q)\times\dfrac{p(p+1)}{2}-q\times\dfrac{(p+1)(p+2)}{2}$$

设 $f_j$ 是分成 $j$ 个队伍可以获得的贡献，枚举每个种族 $i$，使 $f_j\gets f_j+F(c_i,min(j,c_i))$，相当于单点加与后缀加，差分前缀和就行了。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int MAXN=2e5+10;
int T,n,b,z,c[MAXN],f[MAXN],MAX,ans;
inline int F(int x,int y)
{
    int p=x/y,q=x%y;
    return x*(x+1)/2-(y-q)*p*(p+1)/2-q*(p+1)*(p+2)/2;
}
inline void work()
{
    cin>>n>>b>>z;
    for(int i=1;i<=n;++i)
    {
        cin>>c[i];MAX=max(MAX,c[i]);
        for(int j=1;j<c[i];++j)
        {
            int cur=F(c[i],j)*b;
            f[j]+=cur,f[j+1]-=cur;
        }
        f[c[i]]+=F(c[i],c[i])*b;
    }
    for(int i=1;i<=MAX;++i)
        f[i]+=f[i-1],ans=max(ans,f[i]-(i-1)*z);
    for(int i=1;i<=MAX;++i) f[i]=0;
    cout<<ans<<'\n';MAX=ans=0;return ;
}
signed main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>T;while(T--) work();
    return 0;
}
```

---

## 作者：Drimpossible (赞：2)

妙妙题。

首先一个很直观的想法是枚举分多少队（假设分了 $i$ 队），然后把每一种人分别考虑算答案即可。

对于 $c_j\leq i$ 的种族可以不管，直接把所有贡献累加进答案即可。但是 $c_j>i$ 的种族怎么办呢？有一个很启发式的结论是：把每一组尽量平均地分配。

考虑证明其正确性：首先，这种情况产生的贡献是总对数减去每一组内的对数。贪心的考虑如果当前每组分配的人数不平均，把新的一个人放在较少的组减少的对数一定是比放在人数多的对数少的，而总对数是不变的，所以这样做是正确的。

表达式即为：
$$
\begin{pmatrix}c_j\\2\end{pmatrix}-\begin{pmatrix}\frac{c_j}{i}\\2\end{pmatrix}\times i -\frac{c_j}{i}\times (c_j \text{ mod }i)
$$

再来说下时间复杂度，由于每次要枚举的 $c_j$ 都是大于 $i$ 的，又因为 $\sum c_j \leq2\times 10^5$，所以总个数不超过 $\frac{2\times 10^5}{i}$，所以时间复杂度即为 $O(\frac{V}{1}+\frac{V}{2}+\frac{V}{3}+......+\frac{V}{V})=O(V \ln V)$ 是调和级数的。

核心代码：

```cpp
int C(int x){return x*(x-1)/2;}
void solution(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)cin>>c[i];
	sort(c+1,c+n+1);
	int ans=0,sum=0,pos=1;
	for(int i=1;i<=c[n];i++){
		while(pos<=n&&c[pos]<=i)
			sum+=C(c[pos]),pos++;
		int res=sum;
		for(int j=pos;j<=n;j++)
			res+=C(c[j])-C(c[j]/i)*i-(c[j]/i)*(c[j]%i);
		ans=max(ans,res*a-(i-1)*b);
	}
	cout<<ans<<endl;
}
```


---

## 作者：w9095 (赞：2)

[CF1928D Lonely Mountain Dungeons](https://www.luogu.com.cn/problem/CF1928D)

提供一个三分做法。

假设我们已经知道了分 $x$ 队，那对于每一个种族，我们就应该尽量平均分到这 $x$ 个队伍中。我们可以先将总数 $c_i$ 平均分，再把余数 $r$ 分给前 $r$ 个元素，每个元素分一个 $1$。

然后，我们需要统计答案。我们发现这是一个类似带权数线段的计数，所以我们对于平均分之后的数维护一个后缀和。每处理到一个数时，将后缀和减去这个数，并用这个数乘以后缀和乘以 $b$ 累加到答案中。这个过程的时间复杂度是 $O(c_i)$ 的，由于题目保证 $\sum c_i\le2\times10^5$，这个时间复杂度可以接受。

接下来，我们考虑优化寻找答案的过程。记分 $x$ 队的战斗力为 $F_x$，可以证明 $F_x$ 为单峰函数。当前分的队数越多，扩一个队能增加的收益就越少。因为同一个队不可以贡献的对数是该队人数平方级别的，分的队数越多，平均分人数减少越慢。但是扩一个队的代价一定，所以答案的差分是递减的。因此，$F_x$ 为单峰函数。

既然答案是单峰的，直接三分即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,b,x,a[300000];
long long check(long long w)
{
	long long ans=0;
	if(w==0)return 0;
	for(int i=1;i<=n;i++)
	    {
	    	long long tol=a[i],s=a[i]/w,r=a[i]%w;
	    	for(int i=1;i<=r;i++)tol-=(s+1),ans+=(s+1)*tol;
	    	while(tol>0)tol-=s,ans+=s*tol;
		}
	return ans*b-x*(w-1);
}
 
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long ans=0,mx=0;
	   	scanf("%lld%lld%lld",&n,&b,&x);
	   	for(int i=1;i<=n;i++)
	   	    {
		    scanf("%lld",&a[i]);
		    mx=max(mx,a[i]);
		    }
		long long l=0,r=mx;
		while(l<=r)
		   {
		   	long long mid1=(l*2+r)/3,mid2=(l+r*2)/3;
		   	if(check(mid1)<=check(mid2))ans=max(ans,check(mid2)),l=mid1+1;
		   	else r=mid2-1;
		   }
	   	printf("%lld\n",ans);
	   }
	return 0;
}
```

感谢 [sunrise1024](https://www.luogu.com.cn/user/368884) 提供的证明。

---

## 作者：Silvestorm (赞：1)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF1928D)。

多组测试数据。

有 $n$ 类人，第 $i$ 类人有 $c_i$ 个。你需要 $(k-1)\times x$ 的代价把他们分成 $k$ 组。在一种分组下，每有两个同类的人被分到不同的组，会产生 $b$ 的贡献。求最大收益。

所有测试点：$1\le n,c_i\le 2\times 10^5$，$b\le 10^6$，$x\le10^9$。

### 题目类型

三分。

### 解题思路

简单理解，在不考虑分组代价的时候，肯定是组分得越多越好。那么考虑代价之后，这就是一个单峰函数，我们要做的就是找到峰顶。显然是三分做法。

首先来解决一个问题：分好组之后如何计算收益（~~计算代价那么简单不用我说吧~~）。

先来一个贪心小结论：分好组之后，任何一个组能对余下的人产生收益，因此每个组的分配都应该尽可能的平均。

显然每一个组的人数不一定相同。假设这类人的总人数为 $c$，分为 $k$ 组，人数少的那些组人数为 $a$，共有 $x$ 组，那么人数多的那些组人数就是 $b(b=a+1)$，共有 $y$ 组，我们可以分别对其计算贡献。

对于任意一个组,它带来的贡献是：这个组的人数 $\times$ 除去这个组剩余的人数。

那么这一类人的计算公式为 $(x\times a\times (c-a)+y\times b\times (c-b))\times b\div2$。

接下来解决最后的问题，$k$ 的确定，会三分的可以略过这里，但由于本蒟蒻不会三分，所以自认为写了个优化二分。

单峰函数找峰顶，跟单调性有关，二分取 $mid$ 和 $mid+1$，根据这两数得出的结果，比较一下大小，得出此处的单调性，如果前者的收益大，那么答案就在 $mid$ 左边的区间里，否则在 $mid$ 右边的区间里。

### code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
long long b, c, d, q, x, k, m, ans = 0;
ll n,num[200100];
void find(ll l, ll r)
{
	if (l == r)
		return;
	ll mid = (l + r) >> 1;
	ll mid1 = mid + 1;
	ll tem = -x * (mid - 1), tem1 = -x * (mid1 - 1);//计算代价
	for (int i = 0; i <n; i++)//计算贡献
	{
		tem += ((mid - num[i] % mid) * (num[i] / mid) * (num[i] - num[i] / mid) + (num[i] % mid) * ((num[i] + mid - 1) / mid) * (num[i] - ((num[i] + mid - 1) / mid))) * b / 2;//我知道很抽象但是上面给了公式了就懒得优化了
		tem1 += ((mid1 - num[i] % mid1) * (num[i] / mid1) * (num[i] - num[i] / mid1) + (num[i] % mid1) * ((num[i] + mid1 - 1) / mid1) * (num[i] - ((num[i] + mid1 - 1) / mid1))) * b / 2;
	}
	if (tem1 == tem)
	{
		ans = max(ans, tem);
		return;
	}
	if (tem1 > tem)
	{
		ans = max(tem1, ans);
		find(mid1, r);
	}
	else
	{
		ans = max(ans, tem);
		find(l, mid);
	}
}
void solve()
{
	m = 0;
	ans = 0;
	k = 0;
	cin >> n >> b >> x;
	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
		m = max(m, num[i]);//缩小区间的范围
	}
	find(1, m);
	cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int h;
	cin >> h;
	// h = 1;
	while (h--)
	{
		solve();
	}
	return 0;
}

```


---

## 作者：ZhongYuLin (赞：1)

形式化题意：

设：$f(x,y)$ 表示将 $x$ 个元素分配到 $y$ 个位置上产生的贡献最大值（处于不同位置上的一组产生 $1$ 的贡献，例如形如 $1,1,1$ 的分配将产生 $3$ 的贡献）。

给定 $n,b,x$ 以及 $c_1...c_n$。

求：$b\sum_{i=1}^{n}f(c_i,y)-x(y-1)$ 的最大值。

显然：$f(x,y)=\frac{y\lfloor \frac{x}{y} \rfloor(y\lfloor \frac{x}{y} \rfloor-\lfloor \frac{x}{y} \rfloor)}{2}+(x \bmod y)(y\lfloor \frac{x}{y} \rfloor-\lfloor \frac{x}{y} \rfloor)+\frac{[(x \bmod y)-1](x \bmod y)}{2}$

打表或分析实际意义可知：
	
$f(x,y) \leq f(x,x)$，对于确定的 $x$，函数上界收敛。

于是 $b\sum_{i=1}^{n}f(c_i,y)$ 上界也收敛。

同时，$x(y-1)$ 单调上升，且上界不收敛。

所以，待求值为单峰函数，三分即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using ll=long long;
using namespace std;
const int N=2e5+10;
ll n,b,x;
ll c[N];
ll f(int x,int y){if(!y)return -N;ll k=x/y,s=k*y,l=x%y;return y*k*(s-k)/2+l*(s-k)+(l-1)*l/2;}
ll calc(int y){
	ll ans=0;
	for(int i=1;i<=n;++i)ans+=f(c[i],y);
	return ans*b-(y-1)*x;
}
void solve(){
	cin>>n>>b>>x;for(int i=1;i<=n;++i)cin>>c[i];
	int l=1,r=N,mid,ans;
	for(;l<=r;)mid=l+r>>1,calc(mid-1)<=calc(mid+1)?l=mid+1,ans=mid:r=mid-1;
    printf("%lld\n",max({calc(ans+1),calc(ans),calc(ans-1)}));
}
signed main(){
	ios::sync_with_stdio(cin.tie(cout.tie(0)));
	int T;for(cin>>T;T--;)solve();
	return 0;
}
```


---

## 作者：lfxxx (赞：1)

每个人只与和他同一队的同类人不产生贡献，要让这些人尽可能少，又因为 $(a+b)^2 > a^2 + b^2$ 所以我们需要将这些人尽可能分散，因此平均分配给每个队伍即可，那么不难发现对于队伍数大于 $c_i$ 的情况，实际上贡献全部相同，那么你就有了 $O(n + \sum c)$ 的做法，可以通过，但是 $c_i$ 开大就会很慢，考虑当队伍数变多时，每个队伍平均的人数变少的速度会变慢，而乘法增加的速度不变，因此答案关于队伍数实际上是单峰的，考虑定义 $f(i)$ 为 $i$ 支队伍时的答案。那么对 $f(i+1) - f(i) - x$ 二分出最后一个大于等于 $0$ 的位置即可，时间复杂度 $O(n \log \sum c)$。

```cpp
#include<bits/stdc++.h>
#define int __int128
namespace IO{
    const int SIZE=1<<21;
    static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
    #define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
    #define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
    #define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
    #define puts(x) IO::Puts(x)
    template<typename T>
    inline void read(T&x){
        for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
        for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15);
        x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
        for(int i=0;s[i];++i)
            putchar(s[i]);
        putchar('\n');
    }
    struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
#define lowbit(x) (x&(-x))
using namespace std;
//假若小队数从 k-1 -> k
//-x
//数量大于等于 k 的小队数乘 (k-1) 乘 b
const int maxn = 2e5+114;
int c[maxn],n,b,x;
int check(int k){
    int ans=0;
    for(int i=1;i<=n;i++){
        int p=c[i]/k;
        int e=c[i]%k;
        //(1,k-1) p
        //k p+e
        ans+=c[i]*(c[i]-1)/2*b;
        ans-=(p*(p-1)/2)*b*(k-e);
        ans-=(p+1)*((p+1)-1)/2*b*e;
    }
    return ans;
}
void work(){
    read(n);
    read(b);
    read(x);
    for(int i=1;i<=n;i++) read(c[i]);
    int l=0,r=200001;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(check(mid+1)-check(mid)<=x) r=mid;
        else l=mid;
    }
    write(check(r)-x*(r-1));
    putchar('\n');
    return ;
}
signed main(){
    int t;
    read(t);
    while(t--) work();
    return 0;
}
/*
3 1 0
1 2 3
*/
```


---

## 作者：naroanah (赞：0)

## 题意简述：

有 $n$ 个种族，第 $i$ 个种族有 $c_i$ 个生物。你可以把它们任意分成若干组。对于一对同一种族的生物，如果它们不在同一组内，则提供 $b$ 点兵力值。同时假如你分成了 $k$ 组，那么兵力值要扣除 $(k - 1) \times x$ 点。求最大的兵力值。

## 思路：

注意到不同种族之间互不干扰，可以只对一种考虑。

感性理解不难发现，如果组数 $k$ 一定，我们一定会尽可能对每一组平均分配，这样产生贡献最大。考虑对于每一种组数算出最大贡献。

$c \bmod k = 0$ 是平凡的。对于有余数的情况，我们会把余数平摊给某些组，未得到平摊的记作 A 组，得到记作 B 组。

假设 $r \gets c \bmod k, t \gets k - r, g \gets \lfloor \dfrac{c}{k} \rfloor, h \gets  \lceil \dfrac{c}{k} \rceil$。

那么我们有贡献 $value \gets (\dfrac{(t - 1)tg^2}{2}) + (\dfrac{(r - 1)rh^2}{2}) + (tgrh)$。

三个部分分别是 A 组与 A 组，B 组与 B 组， A 组与 B 组。

计算方式是先选出两个组，再乘上两组内两两匹配的方案数。

由于 $\sum c_i \le 2 \times 10 ^ 5$ ，较大的 $c_i$ （$\ge \sqrt {2 \times 10 ^ 5}$​）数量最多根号级别，复杂度是对的。

最后枚举 $k$ 暴力计算答案即可。

## 代码：

```cpp
//#define NDEBUG
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define repp(i, l, r) for(int i = (l); i < (r); i++)
#define req(i, r, l) for(int i = (r); i >= (l); i--)
#define reqq(i, r, l) for(int i = (r); i > (l); i--)
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define fi first
#define se second
#define all(x) begin(x), end(x)
using namespace std;
namespace pbds = __gnu_pbds;
namespace cxx = __gnu_cxx;
constexpr int N = 2e5 + 10, inf = 0x3f3f3f3f, INF = 0x7f7f7f7f, mod = 998244353;
constexpr double eps = 1e-9;
template<typename T1, typename T2> void chkmin(T1& x, T2 y) {if(x > y) x = y;}
template<typename T1, typename T2> void chkmax(T1& x, T2 y) {if(x < y) x = y;}
int c[N];
int n, b, x;
vector<ll> f[N];
void solve() {
    cin >> n >> b >> x;
    rep(i, 1, n) cin >> c[i];
    sort(c + 1, c + n + 1); 
    rep(i, 1, n) f[i].resize(c[i] + 1, 0);
    rep(i, 1, n) {
        rep(k, 2, c[i]) {
            ll r = c[i] % k, t = k - r, g = c[i] / k, h = (c[i] - 1) / k + 1;
            f[i][k] = t * (t - 1) / 2 * g * g + 
                      r * (r - 1) / 2 * h * h + 
                      r * t * g * h;
            //cerr << f[i][k] << " ";
        }
        //cerr << "\n";
    }
    int cur = 1, maxk = c[n]; ll tot = 0;
    ll Ans; Ans = 0;
    rep(i, 2, maxk) {
        while(cur <= n and c[cur] < i) tot += f[cur][c[cur]], cur++;
        ll ans = tot;
        rep(j, cur, n) ans += f[j][i]; 
        ans = ans * b - 1ll * (i - 1) * x;
        chkmax(Ans, ans);
    }
    cout << Ans << "\n";
}
signed main() {
    ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin >> T; while(T--) solve();
    return 0;
}
```

---

## 作者：徐晨轩✅ (赞：0)

提供一种与官方题解不同的解法。

首先，考虑确定 $k$ 后如何计算最大权值。先考虑一个种族的情况，其余类似。令有 $a_i$ 人去了第 $i$ 个小组，那么对权值的贡献则为 $b\sum_{1 \le i < j \le n} a_ia_j$。注意到 $\sum_{1 \le i < j \le n} a_ia_j=\dfrac{c^2-\sum_{i=1}^na_i^2}2$。显然，分的越均匀，$\sum_{i=1}^na_i^2$ 越小，权值也就越大。这样，我们就可以 $O(1)$ 地计算一个种族对权值的贡献。

然后，考虑枚举 $k$。使用分块决策：令 $sq = \sqrt{\sum_{i=1}^n c_i}$，则分别枚举 $k \le sq$ 和 $k > sq$。第一部分需要 $O(n \cdot sq)$ 的复杂度，而对于后半部分，若 $c_i \le sq$，则无论 $k$ 在满足 $k > sq$ 的情况下取何值，对权值的贡献均不变，所以可以预处理。而若 $c_i > sq$，这种情况最多有 $sq$ 种，枚举即可。

总时间复杂度：$O(n \cdot sq)$。

[Code](https://codeforces.com/contest/1928/submission/245834128)

---

## 作者：Cure_Wing (赞：0)

[CF1928D Lonely Mountain Dungeons](https://www.luogu.com.cn/problem/CF1928D)

### 思路

假设我们确定了 $k$ 即分的队伍数，想一下如何计算总的价值。

首先一定要减去 $(k-1)x$，这是题目所规定好的损失。

对于剩下 $c_i\le k$ 的物种，我们把它每只生物都分别分到一组。这样他们两两不在同一组，可以贡献最大价值 $b\times\frac{c_i\times(c_i-1)}{2}$。

而对于 $c_i>k$ 的物种，我们放完前 $k$ 只生物后，就不得不出现生物在同一组的情况。如何让同一列之间的损失最小呢？显然挑同种生物数最小的那一列。因为放到同种生物数为 $a$ 会损失 $b\times\frac{a}{2}$ 的价值，显然 $a$ 越小损失越小。所以基本放法就是每 $k$ 只生物放一层，放完为止。

放完了 $c_i>k$ 的物种，计算他们的价值。容易发现所有列生物数只会有两种：$\lfloor{\frac{c_i}{k}}\rfloor$ 和 $\lceil{\frac{c_i}{k}}\rceil$。而两种列的数量分别有 $(k-c_i\bmod k)$ 和 $(c_i\bmod k)$ 列。对于生物数为 $\lfloor{\frac{c_i}{k}}\rfloor$ 的列，他们会与 $(k-c_i\bmod k-1)$ 列的 $\lfloor{\frac{c_i}{k}}\rfloor$ 只生物和 $(c_i\bmod k)$ 列的 $\lceil{\frac{c_i}{k}}\rfloor$ 只生物产生价值。对于生物数为 $\lceil{\frac{c_i}{k}}\rceil$ 的列，他们会与 $(k-c_i\bmod k)$ 列的 $\lfloor{\frac{c_i}{k}}\rfloor$ 只生物和 $(c_i\bmod k-1)$ 列的 $\lceil{\frac{c_i}{k}}\rfloor$ 只生物产生价值。但是这样子会出现相互产生贡献的情况，最后对总和除以 $2$ 即可。（实现的时候用了另一种计算方式，可以看作是把上述式子拆开。）

挖掘一下可行的 $k$ 的范围，一定不大于 $\max c_i$，显然留空列没有任何用处。所以我们从小到大枚举 $k$，计算 $k$ 为对应值的总价值。对于 $c_i\le k$ 的部分，因为他们的价值不再变化，我们可以开个变量记录他们的价值和，之后只需要再次计算 $c_i>k$ 的部分的价值即可。这启发我们对 $c_i$ 排序，这样就可以用一个指针维护断点。最后打擂台取最优值即可。时间复杂度为 $O(\sum(\max c_i\times n))$，看起来不太可行。但由于 $\sum c_i\le2\times10^5,\max c_i\le(\sum c_i)-n-1$，而且还要保证 $c_i$ 不同的数尽可能多，很难达到上限。估计一下时间复杂度最坏为 $O(\sum(n\sqrt{\sum c_i}))$，可以通过。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=200005;
constexpr long long inf=1e18;
int t,n,b,x,c[N];
long long ans,sum;
inline long long get(int w,int p){
	long long tot=0;
	for(int i=p;i<=n;++i) tot+=1ll*(c[i]-c[i]%w)*(w-1)*(c[i]/w-1)/2+1ll*(c[i]%w)*(w-1)*(c[i]/w)+1ll*(c[i]/w)*w*(w-1)/2+1ll*(c[i]%w)*(c[i]%w-1)/2;//计算剩余部分的价值（式子可能有些奇怪）
	return tot;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<ans<<'\n'){
		cin>>n>>b>>x;ans=-inf;sum=0;
		for(int i=1;i<=n;++i) cin>>c[i];
		std::sort(c+1,c+n+1);
		int j=1;
		for(int i=1;i<=c[n];++i){
			for(;j<=n&&c[j]<i;++j) sum+=1ll*b*c[j]*(c[j]-1)/2;//不会改变的价值记录
			ans=std::max(ans,sum+1ll*b*get(i,j)-1ll*(i-1)*x);//计算价值和
		}
	}
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

赛时做法，好像和很多人不大一样。

显然平均分是最优的，将把 $n$ 个数分到 $k$ 个队的代价记为 $calc(n,k)$。考虑贪心，先把初始状况，也就是所有生物都在一个队的情况扔到优先队列里，每次取出 $calc(i,k+1)-calc(i,k)$ 最大的生物 $i$ 再分组，也就是多分一组能产生贡献最大的生物。

但需要注意，最终场上队伍数是所有生物中最大生物数的最大值，因此如果有一个生物多分组时导致场上队伍数增多，它本身会带一个 $-x$ 的代价。可以实时更新最大值，魔改一下比较函数就可以了。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T,n,sum,ans,a[N],tot[N],b,d,x,total;
//priority_queue<pair<int,int>,vector<pair<int,int> >,less<pair<int,int> > >q; 
struct Node{
	int w,u;
	friend bool operator <(const Node &xxx,const Node &yyy){
		if(tot[xxx.u]+1>d){
			if(tot[yyy.u]+1>d)return xxx.w<yyy.w;
			else return xxx.w-x<yyy.w;
		}
		else{
			if(tot[yyy.u]+1>d)return xxx.w<yyy.w-x;
			else return xxx.w<yyy.w;
		}
    }
};
priority_queue<Node>q;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int calc(int x,int y){
	int t=x%y,k=x/y;
	return (t*(k+1)*(x-k-1)+(y-t)*k*(x-k))/2;
}
signed main(){
	//freopen("std.in","r",stdin);
	T=read();
	while(T--){
		n=read();b=read();x=read();sum=0;d=1,total=0;ans=-1e18;
		for(int i=1;i<=n;i++){
			a[i]=read(),tot[i]=1;
			if(tot[i]<a[i])q.push({calc(a[i],2)-calc(a[i],1),i});
			total+=calc(a[i],1)*b;
			sum+=a[i];
		}
		//cout<<"&&&&&"<<endl;
		total=-(d-1)*x;ans=max(ans,total);
		while(!q.empty()){
			int u=q.top().u;
			total+=q.top().w*b;
			//cout<<total<<endl;
			q.pop();
			tot[u]++;
			//cout<<u<<" "<<tot[u]<<endl;
			if(tot[u]>d)d=tot[u],total-=x;
			if(tot[u]<a[u]){
				q.push({calc(a[u],tot[u]+1)-calc(a[u],tot[u]),u});
			}
			ans=max(ans,total);
			//cout<<total<<endl;
			//cout<<endl;
		}
		printf("%lld\n",ans);
	}
	return 0;
}


```


---

