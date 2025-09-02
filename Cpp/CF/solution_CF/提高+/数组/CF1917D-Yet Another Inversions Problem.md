# Yet Another Inversions Problem

## 题目描述

给定一个长度为 $n$ 的排列 $p_0, p_1, \ldots, p_{n-1}$，其中 $p$ 是 $1$ 到 $2n-1$ 之间所有奇数的一个排列；以及一个长度为 $k$ 的排列 $q_0, q_1, \ldots, q_{k-1}$，其中 $q$ 是 $0$ 到 $k-1$ 的一个排列。

定义长度为 $nk$ 的数组 $a_0, a_1, \ldots, a_{nk-1}$，其元素如下：

对于所有 $0 \le i < n$ 和 $0 \le j < k$，有 $a_{i \cdot k + j} = p_i \cdot 2^{q_j}$。

例如，如果 $p = [3, 5, 1]$ 且 $q = [0, 1]$，那么 $a = [3, 6, 5, 10, 1, 2]$。

注意，题目中的所有数组均为从零开始编号。并且数组 $a$ 的每个元素都是唯一确定的。

请你计算数组 $a$ 中的逆序对数量。由于答案可能很大，只需输出其对 $998\,244\,353$ 取模的结果。

数组 $a$ 中的逆序对定义为一对下标 $(i, j)$，满足 $0 \le i < j < nk$ 且 $a_i > a_j$。

## 说明/提示

在第一个测试用例中，数组 $a$ 为 $[3, 6, 5, 10, 1, 2]$。其中有 $9$ 个逆序对，分别为 $(0, 4)$、$(0, 5)$、$(1, 2)$、$(1, 4)$、$(1, 5)$、$(2, 4)$、$(2, 5)$、$(3, 4)$、$(3, 5)$。这些都是满足 $i < j$ 且 $a_i > a_j$ 的下标对。

在第二个测试用例中，数组 $a$ 为 $[8, 4, 1, 2, 24, 12, 3, 6, 40, 20, 5, 10]$。其中有 $25$ 个逆序对。

在第三个测试用例中，数组 $a$ 为 $[1, 2, 4, 8, 16]$。其中没有逆序对。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
3 2
3 5 1
0 1
3 4
1 3 5
3 2 0 1
1 5
1
0 1 2 3 4
8 3
5 1 7 11 15 3 9 13
2 0 1```

### 输出

```
9
25
0
104```

# 题解

## 作者：SunsetLake (赞：15)

官方题解。
## 思路
首先可以把 $a$ 数组分成 $n$ 块，每块都是长为 $k$ 的 $q$ 数组。于是我们可以把答案拆成两部分计算：块内的贡献和块外的贡献。对于块内，$p_i$ 都是一样的，因此可以直接消去，计算的实际上就是 $q$ 序列的逆序对数，把这个值 $\times n$ 就行了。这样就只需要计算块与块之间的答案。

我们先固定 $p$ 的两个元素 $x$ 和 $y$，那么要计算的逆序对就是形如 $a_i=x\times 2^a$，$a_j=y\times 2^b$ 的 $(i,j)$。因为每个块内都是一个 $1 \sim k-1$ 的排列，因此把 $x$ 和 $y$ 两个块拉出来他们对应项的次幂都是相同的。也就是：$[x, 2x, 4x, \ldots, 2^kx]$ 和 $[y, 2y, 4y, \ldots, 2^ky]$。这时再考虑合并两个序列（排序）并且计算贡献。这里讨论 $x<y$ 的情况（$x>y$ 同理）。
- 如果 $[\color{blue}{x}$ $<\color{red}{y}$ $<$ $ \color{blue}{2x}\color{black}{]}$，那么序列就会长成这样：$[\color{blue}{x}, \color{red}{y}, \color{blue}{2x}, \color{red}{2y}, \color{blue}{4x}, \color{red}{4y}, \ldots, \color{blue}{2^kx}, \color{red}{2^ky}\color{black}{]}$。
- 如果 $[\color{blue}{2x}$ $<\color{red}{y}$ $<$ $ \color{blue}{4x}\color{black}{]}$，那么：$[\color{blue}{x}, \color{blue}{2x}, \color{red}{y}, \color{blue}{4x}, \color{red}{2y}, \color{blue}{8x}, \color{red}{4y}, \ldots, \color{blue}{2^{k-1}x}, \color{red}{2^{k-2}y}, \color{blue}{2^kx}, \color{red}{2^{k-1}y}, \color{red}{2^ky}\color{black}{]}$。
- 如果 $[\color{blue}{4x}$ $<\color{red}{y}$ $<$ $ \color{blue}{8x}\color{black}{]}$，那么：$[\color{blue}{x}, \color{blue}{2x}, \color{blue}{4x}, \color{red}{y}, \color{blue}{8x}, \color{red}{2y}, \color{blue}{16x}, \color{red}{4y}, \ldots, \color{blue}{2^{k-1}x}, \color{red}{2^{k-3}y}, \color{blue}{2^kx}, \color{red}{2^{k-2}y}, \color{red}{2^{k-1}y}, \color{red}{2^ky}\color{black}{]}$。
- $\cdots$

假如 $x$ 在 $p$ 中在 $y$ 的后面，那就应该用 $y$ 的视角去统计逆序对数，即对于每个红色的项去看它前面有多少个蓝色的项。这样就满足了逆序对顺序的要求，并且不会计算块内的贡献，只会考虑块间的答案，自然不会算重了。如何计算？观察一下规律：如果 $2^{num-1}x < y < 2^{num}x$，那么每个红色的 $y$ 的贡献就是 $num+(num+1)+(num+2)+\dots +k-1+\underbrace{k+k+\dots +k}_{num \text{个}}$。这是一个 $num \sim k-1$ 的等差数列再加上 $num \times k$。

若 $x$ 在 $p$ 中在 $y$ 的前面，那就该用 $x$ 的眼光去计数了。通过观察可得，其贡献为 $\underbrace{0+0+\dots +0}_{num \text{个}} +1+2+\dots +k-num$。这是 $1 \sim k-num$ 的等差数列。

有了这些结论，就可以 $O(n^2\log n)$ 算答案了。但是这需要枚举每个块，考虑如何优化这个过程。我们可以直接去枚举 $x$ 的取值，可以发现对于 $x$ 产生贡献的 $y$ 都是成倍增长的，$y,2y,4y,\dots ,2^ty$，也就是只会有 $\log$ 级个数！因此我们可以枚举这些 $y$ （在 $p$ 中在 $x$ 的后面），用树状数组统计他的出现次数，再用上面的结论计算贡献即可。
## code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
int t;
const int N=2e5+5,mod=998244353;
int n,p[N],q[N],mx;
ll k,c[N<<1],ans;
int lowbit(int x){
	return x&-x;
}
void clr(){
	for(int i=1;i<=mx;i++)c[i]=0;
}
void add(int id,ll d){
	for(int i=id;i<=mx;i+=lowbit(i))c[i]+=d;
}
ll query(int id){
	ll res=0;
	id=min(id,mx);
	for(int i=id;i;i-=lowbit(i))res+=c[i];
	return res;
}
void solve(){
	cin>>n>>k;
	mx=max(2*n-1,(int)k);
	for(int i=1;i<=n;++i)scanf("%d",&p[i]);
	for(int i=1;i<=k;++i)scanf("%d",&q[i]),q[i]++;//q[i]可能为0，所以统一加1
	clr();
	ans=0;
	for(int i=1;i<=k;++i)add(q[i],1),ans=(ans+i-query(q[i]))%mod;//块内逆序对
	ans=(ans*n)%mod;
	clr();
	for(int i=1;i<=n;++i)add(p[i],1);
	for(int i=1;i<=n;++i){
		int x=p[i];
		ll num=1;
		while(x<2*n){//x<y的情况
			int y=x*2;
			ll cnt=query(y)-query(x);//树状数组计数
			ll len=max(0ll,k-num);
			ans=(ans+(len+1)*len/2%mod*cnt%mod)%mod;
			x*=2;
			num++;
		}
		x=p[i];num=1;
		while(x>1){
			int y=(x+1)/2;//x是奇数
			ll cnt=query(x-1)-query(y-1);
			ll mn=min(num,k);
			ans=(ans+cnt*((k-1+mn)*(k-mn)/2%mod+mn*k%mod)%mod)%mod;
			num++;
			x=y;
		}
		add(p[i],-1);//只计算每个x后面的数的贡献
	}
	cout<<ans<<endl;
} 
int main(){
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Sakuya_maid (赞：4)

[题目地址](https://codeforces.com/contest/1917/problem/D)

考虑用树状数组去维护逆序对。

题目数据范围 $2\times 10^5$，这里有一个 trick 就是在 $2^{20}$ 次方之后，$p_i\times2^{20}$ 次方后一定比每个数都大。

因此，可以把 $k$ 分成两个部分，第一部分是 $0$ 至 $20$，第二部分是 $21$ 至 $k$。

首先，对于每个块内，它的贡献就是 $q$ 数组的逆序对。

然后，考虑它和它后面块的贡献，对于数的比较，我们可以 $p_i\times2^{q_j}$ 次方。

两边都有 $2$ 的多少次方，把它都移到 $i$ 这边，这时候左边就是 $p_i\times2^{d}$ 次方，右边是 $p_j$，然后对于每个 $d$ 单独算贡献，次数是 $k-\operatorname{abs}(b)$，$20$ 是上限。

对于 $0$ 至 $20$ 的情况时。

```c
    for(int i = n; i >= 1; -- i){
        for(int d = -20; d <= 20; ++ d){
            if(abs(d) >= k){
                continue;
            }
            if(d < 0)v = a[i] >> (- d);
            else v = a[i] << d;

            if(v > 2 * n)v = 2 * n;//边界为2n , v 过大了就是比每个数字都大贡献就是2n
            ans += query(v) * (k - abs(d)) % mod;//这种情况的次数
            ans %= mod;
        }
        update(a[i], 1);
    } 
```
对于 $21$ 至 $k$ 的情况时。


```c
    int all = (k + 1) * k / 2;

    for(int i = 0; i < min(21, k); ++ i){
        all -= (k - i);//大于20的次数
    }
                              
    for(int i = n; i >= 1; -- i){
        ans += query(2 * n) * all % mod;//如果有大于20的次数直接加
        ans %= mod;
        update(a[i], 1);
    } 
```

可以把他们结合起来，这里放一下全部代码。

```c
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ULL;
using LL = long long;

constexpr int N = 2e5 + 5, mod = 998244353;
constexpr double eps = 1e-8;
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

#define lowbit(x) (x & (-x))
#define PII pair<int, int>
#define mid ((l + r) >> 1)
#define int long long

int max(int a, int b){
    if(a > b)return a;
    else return b;
}

int min(int a, int b){
    if(a > b)return b;
    else return a;
}

int n, m, k, nm, ans;

int a[N], b[N];

void Sakuya()
{
    cin >> n >> k;

    vector<int>tr(k + 1);

    for(int i = 1; i <= n; ++ i){
        cin >> a[i];
    }

    for(int i = 1; i <= k; ++ i){
        cin >> b[i];
        ++ b[i];
        //2 的次方 1移动的时候++
    }

    auto update = [&](int x, int z) -> void{
        while(x <= nm){
            tr[x] += z;
            x += lowbit(x);
        }
    };

    auto query = [&](int x) -> int{
        int res = 0;
        while(x){
            res += tr[x];
            x -= lowbit(x);
        }
        return res;
    };

    nm = k;

    ans = 0;

    for(int i = k; i >= 1; -- i){
        update(b[i], 1);
        ans += query(b[i] - 1);
    }

    ans = ans * n % mod;//每个连通块都是 * n

    int all = (k + 1) * k / 2, v;

    for(int i = 0; i < min(21, k); ++ i){
        all -= (k - i);//大于20的次数
    }

    nm = 2 * n;//贡献最多取到2 * n
    tr.assign(2 * n + 1, 0);

    // cout << all << "\n";

    for(int i = n; i >= 1; -- i){
        for(int d = -20; d <= 20; ++ d){
            if(abs(d) >= k){
                continue;
            }
            if(d < 0)v = a[i] >> (- d);
            else v = a[i] << d;

            if(v > 2 * n)v = 2 * n;//边界为2 * n , v 过大了就是比每个数字都大贡献就是2*n
            ans += query(v) * (k - abs(d)) % mod;//这种情况的次数
            ans %= mod;
        }
        ans += query(2 * n) * all % mod;//如果有大于20的次数直接加
        ans %= mod;
        update(a[i], 1);
    } 

    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    for (cin >> T; T -- ; )
        Sakuya();

}
```

[提交记录](https://codeforces.com/contest/1917/submission/238837566)

---

## 作者：lizicheng3042 (赞：3)

说实话，建议评绿。  
题意简述我就不说了（因为我不会），所以我们直接开始正文。  
## 前置知识
如何在 $O(n\log n)$ 的时间内求逆序对。  
树状数组的单点修改和区间查询。  
分治思想。  
## 题目思路
首先，我们设长度为 $n$ 的排列存在数组 $a$ 中，长度为 $k$ 的排列存在数组 $b$ 中，那么因为 $a$ 和 $b$ 的所有数都是正整数，所以可以得到一个显而易见的东西：  
$$a\times 2^j_i\le a\times 2^{j+1}_ i $$  
有了这个式子，我们我们发现，对于在最终长度为 $nk$ 的扩展数组中，那些长度为 $k$ 的由 $a_i\times 2^j$ 组成的数，其内部是可以直接根据 $b$ 的大小来求逆序对的，也就是说，我们可以通过 $O(n\log n)$ 的复杂度来求出扩展数组中由相同 $a_i$ 扩展的 $k$ 个数内的逆序对。  
说完了内部逆序对，现在我们来考虑怎么解决由不同 $a_i$ 扩展的数之间怎么求逆序对。  
建设现在我们只考虑 $a_{i_1}$ 和 $a_{i_2}$ 两个数的扩展数，我们发现，一个规律：
![](https://cdn.luogu.com.cn/upload/image_hosting/rz84yqq9.png)  
如上图所示，假设 $a_{i_2}\times 2^j\le a_{i_1} < a_{i_2}\times 2^{j+1}$，
那么 $a_{i_1}$ 这个数对 $a_{i_2}$ 的扩展数的所有逆序对的个数为 $k-j$ 个，那么 $a_{i-1}\times 2^j$ 也是可以的。那么这样，我们就可以最终知道对于 $a_{i_2}\times 2^j\le a_{i_1} < a_{i_2}\times 2^{j+1}$ 来说，逆序对的个数。  
根据我们所推的式子，最终所有 $a_{i_1}\times j$ 的逆序对贡献和为 $(k-j)\times (k-j+1)\div 2$，由上面的结论和等差数列求和公式可知。那么接下来，就可以预处理出所有 $j$ 对应的结果（具体如何处理代码中会给出说明）。因为 $a$ 中每个数的大小范围都是 $1\le a_i\le 2\times n-1$ ，所以实际上 $j$ 可能的范围很小，大概在 $-20$ 到 $20$ 之间，大致相当于 $\log n$ 的范围。  
**但是要注意有关边界的问题，因为当 $k$ 较小时套用上面的式子会出现错误，所以当对应的 $j$ 大于 $k$ 之后应该直接判为 $0$ 或 $k^2$，具体视情况而定。**  
最后，我们只需要把每个数按照上面所讲的与将每个可能的 $j$ 的情况与之前所有的数比较一下，找出符合条件的数，然后加上对应的预处理值即可。  
那么现在我们就需要一个数据结构来维护前面的数的大小，要求支持单点修改和区间查询，那么，即将赶到战场的是——树状数组。（话说都这样了还用线段树干什么？）我们只需在查询完每个数与前面的数产生的逆序对后将这个数加入树状数组即可，在查询时，我们也可以直接从树状数组里查。  
那么现在，我们已经知对于所有 $a_i$ 的扩展数的内部的逆序对和与其他数的扩展数之间的逆序对，接下来把它们加起来就可以了，本题结。  
## 预计复杂度
对于每个数的每个可能的 $j$，都需要进行查询并将其插入树状数组，因为 $j$ 的个数大概是 $\log n$，所以对于每个数，所需的次数为 $\log^2 n$（树状数组查询的复杂度为 $\log n$），总复杂度为 $O(n\log^2n)$，可以通过本题。
## 总结
本题所需的编程知识并不高深，只是如何求逆序对以及如何使用树状数组。在编程知识外还需要进行分治，但不那么难想，~~所以感觉比较像绿题~~。
## 代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll ans,pre[100],ms,n,k,tree[800005],num[400005],u,u_p[25],T,do_wn[25],po1,po2,getq,ci[400005];
//因为没有把部分数组定义为长整型WA了两次，望吸取教训
const int sufmove=50;
const ll M=998244353;
int lb(int x)
{
	return x&(-x);
} 
void add(int x,int y)
{
	while(x<=u)
	{
		tree[x]+=y;
		x+=lb(x);
	}
}
int sum_t(int x)
{
	int o=0;
	while(x)
	{	
		o+=tree[x];
		x-=lb(x);
	}
	return o;
}
void check(int a,int nu)
{
	int b=a;
	po1=po2=0;getq=0;
	while(b!=1)
	{
		b>>=1;
		do_wn[++po2]=b;
	}
	b=a;
	u_p[0]=a;
	while(b<u)
	{
		b<<=1;
		u_p[++po1]=b;
	}
	for(b=po2;b;b--)
	{
		int yu=sum_t(do_wn[b]);
		ans+=(yu-getq)*pre[sufmove-b];//对于每种情况寻找对应的数目
		ans%=M;
		getq=yu;
	}
	b=0;
	for(b;b<=po1&&u_p[b]<=u;b++)
	{
		int yu=sum_t(u_p[b]);
		ans+=(yu-getq)*pre[sufmove+b];//对于每种情况寻找对应的数目
		ans%=M;
		getq=yu;		
	}
	ans+=(nu-1-getq)*pre[sufmove+b];
	ans%=M;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		ans=0;
		scanf("%lld%lld",&n,&k);
		u=n*2-1;
		for(int a=1;a<=n;a++)
		{
			scanf("%lld",&num[a]);
		}
		for(int a=1;a<=k;a++)
		{
			scanf("%lld",&ci[a]);
		}
		pre[sufmove]=(ll)(k*(k-1))/2ll;
		ms=(ll)(k*(k-1))/2ll;//如果是这样的数
		for(int a=1;a<=20;a++)
		{
			if(k>=a)
			{
				pre[a+sufmove]=pre[a+sufmove-1]+k-a+1;//数大应该是逆序对减少
				pre[sufmove-a]=pre[sufmove-a+1]-k+a;		
			}//增加相当于对不为k的位置加1，减少则相当于对不为0的位置减1.
			else//如果参考上面的图象，这个并不难想。
			{
				pre[a+sufmove]=pre[a+sufmove-1];
				pre[sufmove-a]=pre[sufmove-a+1];
			}
//			printf("(%lld %lld)",pre[a+sufmove],pre[sufmove-a]);
		}
		for(int a=1;a<=n;a++)
		{
			check(num[a],a);
			add(num[a],1);
//			printf("%lld  ",ans);
		}	
		for(int c=1;c<=u;c++)
			tree[c]=0;
		u=k;
		for(int a=1;a<=k;a++)
		{
			add(ci[a]+1,1);
			ans+=(ll)(sum_t(k)-sum_t(ci[a]+1))*n;
//			printf("(%d,%d)?",sum_t(k),sum_t(ci[a]+1));
			ans%=M;
		}	
		printf("%lld\n",ans);
		for(int c=1;c<=u;c++)
			tree[c]=0;		
	}

	return 0;
}
```


---

## 作者：waauto (赞：2)

我感觉这题比 F 难啊，早知道开完 C 先开 F 了，但是因为这题也上 Master 了，很开心，写一下题解。

首先我们观察到这两个序列本身都是一个排列。

我们对于考虑到 $p_i=x$ 考虑以下大小关系：

1.在 $k$ 长度的段内本身，数量是 $k$ 序列的逆序对数。

2.存在前面的位置满足 $y>x$，对于任何乘 $2^z$ 都有一个对应的。

3.存在前面的位置满足 $y\times 2^z>x$，此时去掉不能乘顶的 $z$ 个，任何都是对应的。

4.存在前面的位置满足 $y>x\times 2^z$，此时去掉不能乘顶的 $z$ 个，任何都是对应的。

首先对于 $1,2$ 是简单的，分别只需要求出序列 $q$ 的逆序对数和每次目前的逆序对数即可。

对于后面两种情况，考虑到 $2^z$ 是增长很快的，$\log n$ 次就不存在满足或者全部都满足了。

那么我们只需要暴力枚举指数，直到达到全部不满足或者全部满足的状态，剩下的就是等差数列求和或者没有贡献了。

每一步都可以在代码里面找到，没有完全理解实现的具体看代码即可。

贴一下代码。

```cpp
namespace BIT{
	const int SIZE=1e6+5;
	int t[SIZE];
	inline void add(uint x,int k){
		for(;x<SIZE;x+=x&(-x))t[x]+=k;
	}
	inline int ask(uint x){
		assert(x<SIZE);
		int res=0;
		for(;x;x-=x&(-x))res+=t[x];
		return res;
	}
	inline int query(uint l,uint r){
		assert(r>=l&&l>0&&r<SIZE);
		return ask(r)-ask(l-1);
	}
	inline void build(int *a,int n){
		F(i,1,n)add(i,a[i]);
	}
};
using namespace BIT;
const int N=2e5+5;
int a[N],b[N];
inline int get(int base,int x){
	base=1<<base;
	int l=1,r=x;
	while(r>l){
		int mid=(l+r)>>1;
		if(mid*base>x)r=mid;
		else l=mid+1;
	}
	return l;
}
inline void mian(){
	int n,k;cin>>n>>k;
	F(i,1,n)cin>>a[i];
	F(i,1,k)cin>>b[i],b[i]++;
	int ans=0,tmp=0;
	for(int i=1;i<=k;i++)t[i]=0;
	for(int i=1;i<=k;i++){
		tmp+=query(b[i],k);
		tmp%=mod;
		add(b[i],1);
	}
	ans=tmp*n%mod;F(i,1,2*n+2)t[i]=0;
	for(int i=1;i<=n;i++){
		int tmp=k*query(a[i],n*2);
		int qwq=k,now=a[i];
		while(qwq>1){
			qwq--;
			now*=2;
			if(now>n*2)break;
			tmp+=qwq*query(now,n*2);
			tmp%=mod;
		}
		qwq=k,now=a[i]+1;int cnt=1;
		while(qwq>1 and now!=1){
			qwq--;
			now=get(cnt,a[i]);
			tmp+=qwq*query(now,n*2);
			cnt++;
			tmp%=mod;
		}
		int aaa=query(1,n*2);qwq--;
		if(qwq)tmp+=aaa*qwq*(qwq+1)/2%mod;
		ans+=tmp;ans%=mod;
		add(a[i],1);
	}
	cout<<ans<<'\n';
}
```

---

## 作者：翼德天尊 (赞：1)

考虑贡献由两部分组成：$i$ 相同 $j$ 不同元素之间的逆序对，和 $i$ 不同 $j$ 不同元素之间的逆序对。

对于前者，个数即为 $q$ 序列逆序对个数乘上 $n$。考虑如何计算后者。

不难发现 $p$ 哪怕取到倍数的最大值 $2n-1$，对应到 $q$ 上也只是 $\log$ 级别的差距。故我们可以顺序枚举每一行，处理第 $i$ 行时，前 $i-1$ 行对第 $i$ 行的贡献最多只有 $\log$ 种，且每种 $p$ 都形如一段连续的区间。使用数据结构维护前 $i-1$ 行的 $p$，对于每种贡献，在数据结构中查询区间和即可得到产生该贡献的 $p$ 的个数。对于贡献，具体而言，一个正常的、不带偏移量的行会对下一行造成 $\sum_{i=1}^{k-1}i$ 的贡献，而对于会产生的 $\log $ 种贡献而言，都形如所有 $i$ 向左或向右堆积之后得到的值，只需知道具体地偏移量即可得到真正的贡献。

时间复杂度 $O(n\log ^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e5+5;
const int mod=998244353;
int n,k,p[N],q[N];
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
} 
int bmod(int x){
	return (x>=mod)?x-mod:x;
}
struct Bit{
	int sum[N];
	int lowbit(int x){
		return x&(-x);
	}
	void add(int x){
		for (int i=x;i<=k;i+=lowbit(i))
			sum[i]++;
	}
	int query(int x){
		int num=0;
		for (int i=x;i;i-=lowbit(i))
			num=bmod(sum[i]+num);
		return num;
	}
	void clear(){
		for (int i=1;i<=k;i++) sum[i]=0;
	}
}B;
struct Bit2{
	int sum[N];
	int lowbit(int x){
		return x&(-x);
	}
	void add(int x){
		for (int i=x;i<=2*n;i+=lowbit(i))
			sum[i]++;
	}
	int query(int x){
		int num=0;
		for (int i=x;i;i-=lowbit(i))
			num+=sum[i];
		return num;
	}
	void clear(){
		for (int i=1;i<=2*n;i++) sum[i]=0;
	}
}S;
bool vis[N];
int query(int l,int r){
	return S.query(r)-S.query(l-1);
}
int main(){
	// freopen("in.in","r",stdin);
	int t=read();
	while (t--){
		// cout<<t<<"=============\n";
		n=read(),k=read();B.clear(),S.clear();
		for (int i=0;i<n;i++) p[i]=read();
		for (int i=0;i<k;i++) q[i]=read()+1;
		ll ans=0;
		for (int i=k-1;i>=0;i--)
			ans=bmod(ans+B.query(q[i])),B.add(q[i]);
		ans=ans*n%mod;
		// cout<<ans<<"\n";
		for (int i=0;i<=2*n-1;i++) vis[i]=0;
		for (int i=0;i<n;i++){
			for (int j=1;j<=21;j++){
				int l=p[i]*(1ll<<j-1)+1,r=p[i]*(1ll<<j),x=min(j,k);
				if (l>2*n-1) break;
				r=min(r,2*n-1);
				ll num=query(l+1,r+1);
				// cout<<i<<" "<<x<<" "<<l<<" "<<r<<" "<<num<<" lll"<<"\n";
				ans=bmod(ans+1ll*x*k%mod*num%mod);
				if (x<k) ans=bmod(ans+1ll*(k-1+x)*(k-x)/2%mod*num%mod);
			}
			for (int j=1;j<=21;j++){
				int r=(1.0*p[i]/(1ll<<j-1)),l=(p[i]%(1ll<<j)==0)?(p[i]/(1ll<<j)):ceil(1.0*p[i]/(1ll<<j)),x=min(j-1,k);
				if (r<=0) break;
				l=max(1,l);
				ll num=query(l+1,r+1);
				// cout<<i<<" "<<j<<" "<<l<<" "<<r<<" "<<num<<" rrr"<<"\n";
				if (l>r) continue;
				ans=bmod(ans+1ll*(k-1-x+1)*(k-1-x)/2%mod*num%mod);
			}
			S.add(p[i]+1);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

duel 上分题。
### 题意
给一个长度为 $n$ 的数列 $p$，包含 $[1,2n]$ 中的所有奇数，再给一个长度为 $m$ 的数列 $q$，包含 $[0,m-1]$ 中的所有整数，下标均从 $0$ 开始。生成数列 $a_{im+j}=p_i\times2^{q_j}$，求 $a$ 的的逆序对数量模 $998244353$。
### 分析
不同的贡献分开来算。

不妨设每 $m$ 个分一段，段内 $p_i$ 的值固定，逆序对数即为 $q$ 的逆序对数，简单 BIT 优化计数。

块间考虑同一个 $q_i$ 之间的贡献，即为 $p$ 的逆序对，与上类似。

然后是 $q_i$ 不同。容易发现的是 $p$ 与 $q$ 对数值的贡献完全不对等，$q$ 作为指数，相差过大时会直接决定数值大小关系。所以对于 $q_i$ 差值大于 $\log n$ 的逆序对直接统计即可，不用管 $p$ 的贡献，不想动脑算式子直接 $O(m)$ 暴力。

最后考虑 $q$ 的贡献差值小于 $\log n$ 的情况，直接暴力枚举差值，扫描线的时候乘上差值带来的影响插进 BIT 里查贡献就可以了，时间复杂度 $O(n\log^2 n)$，BIT 小常数配合 CF 神机还是很轻松跑过的。
### 代码
duel 时的代码所以有点凌乱。注意多测清空。

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
const int LG=20;
const int mod=998244353;
int T;
int n,m,ans;
int p[maxn],q[maxn];
class Fenwick_Tree{
public:
	int c[maxn*2];
	void clear(){for(int i=1;i<=max(m,n*2);i++) c[i]=0;}
	int lowbit(int x){return x&(-x);}
	void update(int x,int k){
		while(x<=max(m,n*2)){
			c[x]+=k;
			x+=lowbit(x);
		}
	}
	int query(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
}tr;
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read(),m=read(),ans=0;
		for(int i=1;i<=n;i++) p[i]=read();
		for(int i=1;i<=m;i++) q[i]=read();
		tr.clear();
		for(int i=m;i>=1;i--){
			ans=(ans+tr.query(q[i]))%mod;
			tr.update(q[i]+1,1);
		}
		tr.clear();
		ans=ans*n%mod;
		for(int i=n;i>=1;i--){
			ans=(ans+tr.query(p[i]-1)*m%mod)%mod;
			tr.update(p[i],1);
		}
		for(int t=1;t<min(m,LG);t++){
			int res=0;
			tr.clear();
			for(int i=n;i>=1;i--){
				res=(res+tr.query(p[i]-1))%mod;
				if(p[i]*(1ll<<t)<=n*2) tr.update(p[i]*(1ll<<t),1);
			}
			tr.clear();
			for(int i=n;i>=1;i--){
				res=(res+tr.query(min(n*2,p[i]*(1ll<<t)-1)))%mod;
				tr.update(p[i],1);
			}
			ans+=res*(m-t);
		}
		for(int i=0;i<m;i++){
			int k=max(0ll,i-LG+1);
			ans=(ans+(n*(n-1)/2)%mod*k%mod)%mod;
		}
		cout<<ans<<'\n';
		tr.clear();
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

感觉是近期做过最难的 Div2 D，花了 2h 才自己做出来（虽然没看题解也没看 tag）。

设当前逆序对 $(a_x,a_y)$ 为 $(p_i' 2^{q_j'},p_i 2^{q_j})$。试着做一些分类讨论，逆序对一是要求 $x<y$，二是要求 $a_x>a_y$，先考虑 $x<y$ 的限制，也就是 $i'k+j'<ik+j$。

1. $i'=i$，那么 $j'<j$ 且 $q_j'>q_j$，相当于 $q$ 序列的逆序对个数 $qcnt$，总贡献 $n\cdot qcnt$。
2. $i'<i$，那么 $j',j$ 没有大小关系的要求，直接列出 $p_i' 2^{q_j'}>p_i 2^{q_j}$，考虑进一步对 $q_j,q_j'$ 的大小关系分类讨论：
   * $q_j'\le q_j$，那么 $p_i'>p_i\cdot 2^{q_j-q_j'}$，顺次枚举 $i$，把所有 $i'<i$ 的 $p_i'$ 放到一个桶里面，考虑从小到大枚举 $k=q_j-q_j',k\in[0,m)$，从桶中取出 $>p_i\cdot 2^k$ 的 $p_i'$ 个数，设为 $cur$，那么这一组 $(i,k)$ 的贡献为 $cur(m-k)$，$m-k$ 指满足 $q_j-q_j'=k$ 的有序数对 $(j,j')$ 组数。容易发现当 $p_i\cdot 2^k\ge 2n$ 的时候，必有 $cur=0$，所以对于每个 $i$，至多有 $\mathcal{O}(\log n)$ 个有贡献的 $k$，直接枚举 $(i,k)$ 并使用树状数组维护桶做到 $\mathcal{O}(n\log^2n)$。
   * $q_j'> q_j$，同理的，那么 $p_i<p_i'\cdot 2^{q_j'-q_j}$，考虑互换一下 $i,i'$，变成 $i'>i,p_i'<p_i\cdot 2^{q_j-q_j'}$，然后类似地倒序枚举 $i$，从小到大枚举 $k=q_j-q_j',k\in[1,m)$，这时候如果 $p_i\cdot 2^k\ge n$ 时，必有 $cur=n-i$（为了方便，$i$ 下标从 $1$ 开始），所以之后的直接等差数列求和即可，仍然是 $\mathcal{O}(n\log^2n)$。

然后就没有别的情况了，树状数组要平移一位并开到 $2n$ 因为 $p_i\in[0,2n)$。说实话这题还是有点难的，不过如果沉下心来认真分讨就不会做错了，代码也没有很难写，主要是一些小细节提前设计好就问题不大啦。


[Submission.](https://codeforces.com/contest/1917/submission/245991293)

---

## 作者：OtterZ (赞：0)

# 问题
给定两个数组 $a_i,b_i$，分别长为 $n,k$，其中 $a_i$ 为 $1$ 到 $2 \times n + 1$ 中奇数的排列，$b_i$ 为 $i$ 到 $k$ 的排列。
我们把两个数组拼在一起，得到 $c_{i \times k + j} = a_{i} \times2^{b_j}$，问 $c_i$ 的逆序对数。
# 解法
首先易证这道题无需查重，较为方便。  

我们可以将 $c_i$ 分为 $n$ 组，每组 $k$ 个，可以得到每一组内部的逆序对数即为 $b_i$ 的逆序对数。用常规求逆序对的树状数组解法可以得到 $\operatorname{O}(k\log k)$ 的解法。 

对于不同组之间的逆序对数，考虑两数间 $2$ 的指数差 $x$，容易得到二种出现逆序对的情况：

1. $i < j,a_i > a_j \times 2 ^ x$，一组这样的 $(i,j)$ 对应 $k - x$ 种情况，注意此时要求 $x > 0$。
2.  $i < j,a_i \times 2 ^ x> a_j$，一组这样的 $(i,j)$ 对应 $k - x$ 种情况。

我们可以优化一下，对于 $a_i \times 2 ^ x > 2 \times n - 1$，其必有 $n - i$ 组 $(i,j)$ 得到第二种情况。  
可以枚举 $i,x$，带小优化后用树状数组求可行的 $j$ 的个数可以得到 $\operatorname{O}(\min(n \log ^2 n, n\times k \log n))$ 的解法。
# 代码

```cpp
#include<cstdio>
using namespace std;
#define mod 998244353
int n,k,a[200009],b[200009];
int BIT[400009],sz,BIT2[400009],sz2;
#define lowbit(x) x&(-x)
void BIT_change(int pl,int val,int bit[],int bsz){
	for(int i = pl; i <= bsz; i += lowbit(i))
		bit[i] += val;
}
int BIT_query(int pl,int bit[],int bsz){
	int ans = 0;
	for(int i = pl; i > 0; i -= lowbit(i)){
		ans += bit[i];
	}
	return ans;
}
void slv(){
	scanf("%d %d",&n,&k);
	for(int i = 1; i <= n; i ++){
		scanf("%d",&a[i]);
	}
	for(int i = 1; i <= k; i ++){
		scanf("%d",&b[i]);
	}
	int ans = 0; 
	//得到的数列每k个一组，组内逆序对数显然等于b数组逆序对数
	//注意我们有n组
	sz = k;
	for(int i = 1; i <= sz; i ++){
		BIT[i] = 0;
	} 
	for(int i = k; i >= 1; i --){
		ans += BIT_query(b[i],BIT,sz);
		ans %= mod;
		BIT_change(b[i] + 1,1,BIT,sz);
	}
	ans = 1ll * ans * n % mod;
	//多组之间的逆序对数
	sz = 2 * n - 1;
	for(int i = 1; i <= sz; i ++){
		BIT[i] = 0;
	} 
	sz2 = 2 * n - 1;
	for(int i = 1; i <= sz2; i ++){
		BIT2[i] = 0;
	} 
	for(int i = 1; i <= sz2; i += 2){
		BIT_change(i,1,BIT2,sz2);
	}
	for(int i = n; i >= 1; i --){
		int met = ((1ll * k * (k - 1) >> 1) % mod + k) % mod;
		BIT_change(2 * n - a[i],-1,BIT2,sz2);
		for(int j = 0,t = a[i]; j < k && t <= 2 * n - 1; j ++,t = (t << 1)){
			int u = k - j;
			ans = (ans + 1ll * u * (BIT_query(t,BIT,sz)) % mod) % mod;
			if(j > 0)
				ans = (ans + 1ll * u * (BIT_query(2 * n - t,BIT2,sz2)) % mod) % mod;
			met = (met + mod - u) % mod;
			//printf("%d %d %d %d %d\n",i,j,BIT_query(t,BIT,sz),BIT_query(2 * n - t,BIT2,sz2),ans);
		}
		ans = (ans + 1ll * met * (n - i) % mod) % mod;
		BIT_change(a[i],1,BIT,sz);
	} 
	printf("%d\n",ans);
	for(int i = 1; i <= sz; i += 2){
		BIT_change(i,-1,BIT,sz);
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)
		slv();
	return 0;
}
```


---

## 作者：徐晨轩✅ (赞：0)

将逆序对数分为两部分（记两个数的下标分别为 $i_1 \cdot k_1 + j_1$ 和 $i_2 \cdot k_2 + j_2$）：

* $i_1 = i_2$
* $i_1 < i_2$

第一种的个数显然是 $q$ 的逆序对个数乘以 $n$。

对于第二种，我们需要统计满足如下关系的 $(i_1, j_1, i_2, j_2)$ 的组数：

$$p_{i_1} \cdot 2^{q_{j_1}} > p_{i_2} \cdot 2^{q_{j_2}}, i_1 < i_2$$

将上述式子移项，化简，得到：

$$\dfrac{p_{i_1}}{p_{i_2}} > 2^{q_{j_2} - q_{j_1}}$$

注意到 $\dfrac{1}{2n-1} \le \dfrac{p_{i_1}}{p_{i_2}} \le 2n-1$，故若 $q_{j_2} - q_{j_1}$ 太大，则所有 $(i_1, i_2)$ 均不满足，若太小则都满足，单独统计即可。除此外，只需要考虑 $|q_{j_2} - q_{j_1}| \le 20$ 的情况。

因为 $j_1, j_2$ 没有限制，可以先统计出 $|q_{j_2} - q_{j_1}| \le 20$ 中每一种 $q_{j_2} - q_{j_1}$ 有多少对 $(j_1, j_2)$。之后，对于每一个 $q_{j_2} - q_{j_1}$，枚举 $i_2$，使用树状数组求出满足上述关系式的 $i_1$ 个数即可。

实现时注意一些细节即可。具体可以看代码。

[Code](https://codeforces.com/contest/1917/submission/240085338)

---

