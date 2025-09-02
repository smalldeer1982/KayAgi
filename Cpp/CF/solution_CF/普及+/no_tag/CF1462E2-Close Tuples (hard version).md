# Close Tuples (hard version)

## 题目描述

This is the hard version of this problem. The only difference between the easy and hard versions is the constraints on $ k $ and $ m $ . In this version of the problem, you need to output the answer by modulo $ 10^9+7 $ .

You are given a sequence $ a $ of length $ n $ consisting of integers from $ 1 $ to $ n $ . The sequence may contain duplicates (i.e. some elements can be equal).

Find the number of tuples of $ m $ elements such that the maximum number in the tuple differs from the minimum by no more than $ k $ . Formally, you need to find the number of tuples of $ m $ indices $ i_1 < i_2 < \ldots < i_m $ , such that

 $ $$$\max(a_{i_1}, a_{i_2}, \ldots, a_{i_m}) - \min(a_{i_1}, a_{i_2}, \ldots, a_{i_m}) \le k. $ $ </p><p>For example, if  $ n=4 $ ,  $ m=3 $ ,  $ k=2 $ ,  $ a=\[1,2,4,3\] $ , then there are two such triples ( $ i=1, j=2, z=4 $  and  $ i=2, j=3, z=4 $ ). If  $ n=4 $ ,  $ m=2 $ ,  $ k=1 $ ,  $ a=\[1,1,1,1\] $ , then all six possible pairs are suitable.</p><p><span class="tex-font-style-bf">As the result can be very large, you should print the value modulo  $ 10^9 + 7 $  (the remainder when divided by  $ 10^9 + 7$$$).

## 样例 #1

### 输入

```
4
4 3 2
1 2 4 3
4 2 1
1 1 1 1
1 1 1
1
10 4 3
5 6 1 3 2 9 8 1 2 4```

### 输出

```
2
6
1
20```

# 题解

## 作者：light_ght (赞：3)

# 组合数




------------
### 分析


首先~~恶心人的~~是这是道纯英文的题的**题意**。借助一些奇怪的手段（指盲猜），我们可以明白这题面的意思是
 
给定 $t$ 个长为 $n$ 的数组 $a$，取元素个数为 $m$ 的数组 ${b}\in a$ 满足其中元素各不相同，使得 $num_1,num_2 \in b$ 满足 $max(num_1)-min(num_2)\leqslant k$，问最多能找出多少组，并取模 $10^9+7$。
 
想到是组合数之后，本想一发 ```sort``` 之后从头开始求区间的组合，但是偶发现有问题，由于数据**可能重复**，于是复杂度增加亿点点。
  
如数据 $1, 2, 3, 3, 4$ 按上述方法就是 $cnt$ 先加上 $1 \sim  3$ 之间的组合数，求完之后再加上 $2 \sim  4$ 之间的组合数，但是 $1 \sim  3$ 之间的 $2, 3, 3$ 和 $2 \sim  4$ 之间的 $2, 3, 3$ 重复了。~~于是卡了一节课 窝太菜了~~
   
后经学长点拨，在排序后先取一个值 $a_i$，再在 $( a_i,a_i+2 ]$ 范围内取两个值，便可以避免重复。（妙哉！）

例如，求 $1 \sim  3$ 时，取最小值 $1$，在 $( 1 , 3 ]$ 区间内（即 $2 ,3 ,3$）任取两个值；

接着求 $2 \sim  4$ 时，取最小值 $2$，在 $( 2 , 4 ]$ 区间内任取两个值。
   
不难看出，以上情况无重复。 
        
易得，求 $(a_i, a_i+k ]$ 同理。
   
想清楚原理后就不难实现了  

**记得开 long long！**

（代码中将数组 $a$ 记作 $ght$）

------------
### 实现 
 
   贴核心代码：
    
```cpp
	
const int N = 200005;
const int md = 1000000007;

int a[N];
ll f[N];
ll qpow(ll a, ll b) {  //快速幂
    ll ans = 1, base = a;
    while(b){
        if(b&1)ans=ans*base%md;
        base=base*base%md;
        b>>=1;
    }
    return ans;
}
ll ght(ll n, ll m) {
    if (n<m) return 0;
    return 1ll*f[n]*qpow(f[m],md-2)%md*qpow(f[n-m],md-2)%md;//这里一不小心就会被long long 卡爆
}
int t,n,m,k;

int main(){
    f[0]=1;
    for(int i=1;i<=200000;i++)
        f[i]=f[i-1]*i%md;	
    
    read(t);//快读相关
    while(t--){
        read(n,m,k);
        for (int i=0; i<n;i++) 
            read(a[i]);//快读相关
        
        sort(a,a+n);//排序以便枚举
        int p=0;
        ll ans=0;
        for (int i=0;i<n;i++){
            p=(int)(upper_bound(a,a+n,a[i]+k)-a);
            if(p-i>=m) {
                ans+=ght(p-i-1,m-1);
                ans%=md;
            }
        }
        wrti(ans);//快写相关
    }
	flush();//快写相关
    return 0;
}

```

完整代码已 AC。

[Easy 版本](https://www.luogu.com.cn/problem/CF1462E1) 就是设组合数的最大最小值之差为 $2$，且每组只查 $3$ 个元素，原理是一样的。

###  不开 long long 见祖宗！！！！！

管理员手下留情ya~


---

## 作者：shenmadongdong (赞：2)

~~我寻思这题岂不是有手就行。。。~~

题目大意：给你一个数列，要你选出 $m$ 个数，其中最大数和最小数相差不能超过 $k$，问你方案总数

我们可以先把这个数列排个序，然后枚举在这个数列中选取的最右边的数，数数左边有几个数和它的差在 $k$ 以内，然后算一算组合数就好了

至于如何算左边有几个数和它的差在 $k$ 以内，只需要把每个数的值统计一下，然后作一遍前缀和就好了

具体实现可以看代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const unsigned mod=1e9+7;
ll ksm(ll x,ll y){ll ret=1;while(y){if(y&1ll)ret=ret*x%mod;y>>=1ll;x=x*x%mod;}return ret;}//快速幂模板
ll n,m,k,a[200010],cnt[200010],fac[200010],inv[200010];
ll C(ll n,ll m){if(m>n||m<0)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}//组合数模板
int main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);//关闭流同步
    fac[0]=inv[0]=1;
    for(int i=1;i<=200000;i++) fac[i]=fac[i-1]*i%mod;
    for(int i=1;i<=200000;i++) inv[i]=ksm(fac[i],mod-2);//预处理组合数
	int T;cin>>T;
	while(T--)
    {
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
        for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];//前缀和
        sort(a+1,a+n+1);//排序
		ll ans=0;
        for(int i=n;i>=1;i--)
        {
            if (a[i]>k) ans+=C(i-cnt[a[i]-k-1]-1,m-1),ans%=mod;//组合数计算
            else ans+=C(i-1,m-1),ans%=mod;//为避免负下标RE而进行的特判
        }
        cout<<ans<<'\n';
        for(int i=1;i<=n;i++) cnt[i]=0;//多测记得要清零，不建议用memset
    }
    return 0;
}
```

---

## 作者：wcyQwQ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1462E2)

观察到极差和数组顺序是无关的，所以题目中子序列的要求其实是假的。

然后我们把 $a$ 数组排序，对每一个 $i$ 枚举当 $a_i$ 为最小值的贡献。观察到当左端点 $i$ 固定时，如果 $j$ 是一个满足条件的右端点，那么 $(i, j)$ 中的点也必定是满足条件的最大值，我们可以在 $a$ 中二分出 $a_i + k$ 的前驱，假设这个前驱的下标为 $j$，那么这个左端点 $i$ 的贡献即为 $\sum_{k=1}^{j - i - 1} \binom{k}{m - 2}$ （中间的每个数都可以和点 $i$ 匹配，所以要计算中间每个点的贡献），预处理组合数的前缀和即可做到预处理 $O(nm)$，查询 $O(n\log n)$。

---

## 作者：pyz51 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1462E1)

[CF传送门](https://www.luogu.com.cn/problem/CF1462E1)

[AC记录](https://codeforces.com/contest/1462/submission/296862922)
# 题意简述
~~翻译真是简洁啊，直接粘过来吧！~~  
给定 $t$ 个长为 $n$ 的数组 $a$，取元素个数为 $m$ 的 $a$ 的子序列 $b$ 满足 $\max(b_i) - \min(b_i) \leqslant k$ ，问最多能找出多少组，并取模 ${10}^9 + 7$。
# 前情回顾
[弱化版](https://www.luogu.com.cn/problem/CF1462E1)

[弱化版题解](https://www.luogu.com.cn/article/0iicw8dk)
# 题解
**看到这里之前，一定要保证你 AC 了弱化版或看过弱化版题解。**  
首先，我们不能只改掉与 $k$ 和 $m$ 有关的代码，否则 [link](https://codeforces.com/contest/1462/submission/296858279)。  
取模也没用，在算阶乘时就已经爆炸了。  
所以就要使用逆元，具体看[这里](https://blog.csdn.net/boliu147258/article/details/105758354)。
剩下的参照弱化版题解。  
求 $[l,r]$ 中有几个 $k$ 元组：$C_{r-l+1}^k$  
**不开 long long 见祖宗！！！**  
**最后一定看看 ans 是不是负数，是就再加上 $10^9+7$。**
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
#define CLOSE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define F first
#define S second
#define lowbit(x) x&-x
const int mod=1e9+7;
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int Stack[105];
inline void print(ll x){
    int cnt=0;
    if(x<0) putchar('-'),x=-x;
    while(x){
    	Stack[++cnt]=x%10;
    	x/=10;
    }
    while(cnt--) putchar((char)Stack[cnt+1]+'0');
    return;
}
#define int ll
int t,n,a[N],m,k,f[N],inv[N];
int qpow(int a,int b){//快速幂
	int p=1;
	while(b){
		if(b&1) p=(p*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return p;
}
int C(int n,int m){
	return (((f[n]*inv[m])%mod)*inv[n-m])%mod;
}
signed main(){
	f[0]=1;
	for(int i=1;i<=200000;i++) f[i]=(f[i-1]*i)%mod;
	inv[200000]=qpow(f[200000],mod-2);
    for(int i=199999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
    //预处理阶乘和逆元
    CLOSE
    cin>>t;
    while(t--){
    	int ans=0;
    	cin>>n>>m>>k;
    	for(int i=1;i<=n;i++) cin>>a[i];
    	sort(a+1,a+1+n);
    	int now=-inf,last=-1;
    	for(int i=1;i<=n;i++){
    		int tmp=i;
		    int l=i,r=n;
		    while(l<r){
		        int mid=l+r+1>>1;
		        if(a[mid]-a[i]<=k) l=mid;
		        else r=mid-1;
		    }
    		i=l;
    		if(a[i]<=now){
    			while(a[++tmp]==a[tmp-1]&&tmp<=n);
    			i=tmp-1;
			}
    		if(i-tmp>m-2) ans+=C(i-tmp+1,m)-(last!=-1&&last-tmp>m-2?C(last-tmp+1,m):0),last=i,ans%=mod;//计算组合
    		while(a[++tmp]==a[tmp-1]&&tmp<=n);
    		i=tmp-1;
		}
		cout<<(ans<0?ans+mod:ans)<<'\n';//特判ans
	}
    return 0;
}
```

---

## 作者：紊莫 (赞：0)

困难版题解。

这里需要注意到一个关键性质，序列的顺序是无关的。题目的本质就变成选 $m$ 个数，极差小于等于 $k$。

排序之后就好做了，钦定一个点为最小值，向后面找满足条件的数的个数记为 $x$。则答案相当于是 $\dbinom{x}{m-1} $（除去钦定的这一个）。

找的过程可以采用二分或者数据结构，因为数字比较大，最好算一下逆元。

[示例代码。](https://www.luogu.com.cn/paste/uavnccwf)

---

## 作者：ncwzdlsd (赞：0)

和 E1 思路基本相同。

组合数学。

有一个很好的点：答案与序列顺序无关。

将数组排序，从左至右枚举每一个数 $a_i$，令 $a_i$ 为 $m$ 元组的最小值，查找序列中满足 $a_j-a_i\leq k$ 的所有 $j$，则区间 $(i,j]$ 中任意两个数均满足要求，答案为 $C_{j-i}^{m-1}$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7,maxn=2e5+5;
int fac[maxn],inv[maxn],a[maxn];

int quickpow(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}

void init()
{
    fac[0]=1;
    for(int i=1;i<=2e5;i++) fac[i]=fac[i-1]*i%mod;
    inv[200000]=quickpow(fac[200000],mod-2);
    for(int i=199999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}

int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}

void solve()
{
    int n,m,k;cin>>n>>m>>k;
    int ans=0;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int j=1;
    for(int i=1;i<=n;i++)
    {
        while(a[j+1]-a[i]<=k&&j+1<=n) j++;
        // cout<<(j-i)<<' '<<(m)<<endl;
        if((j-i+1)>=m) ans+=C(j-i,m-1),ans%=mod;
        // else return cout<<"qwq\n",void();
    }
    cout<<ans<<"\n";
    // puts("");
}

signed main()
{
    int t;cin>>t;
    init();
    while(t--) solve();
    return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

~~可能是因为写的尺取法的原因吧，竟然跑得比较快。~~

首先，考虑到如果对于原序列任意 $m$ 个元素无法直接确定最大/最小值。并且答案与序列顺序无关，所以考虑对序列排个序，这样最大值就一定在右边，最小值就一定在左边。

我们先确定一个位置 $i$ 作为最左边的元素，那么因为序列是单调的，所以右端点 $r$ 也具有单调性，此时可以二分。然后考虑到 $i$ 增大的时候 $r$ 也会相应增大，所以可以用尺取法 $O(n)$ 求解。

同时，在 $[i+1,r]$ 中任取 $m-1$ 个元素，因为坐左边的 $i$ 也要算一个，所以就是组合数 $C_{r-i}^{m-1}$。

最后发现，瓶颈在排序，时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。~~其实桶排的话就可以做到纯线性只是不想打~~

注意要取模。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int T,n,a[maxn];
inline int f(int a){
	return a*(a-1)/2;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]);
		sort(a+1,a+n+1);
		int r=0,ans=0;
		for(int i=1;i<=n;++i){
			while(r<n&&a[r+1]<=a[i]+2)
				++r;
			ans+=f(r-i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

