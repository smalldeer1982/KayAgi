# Video Cards

## 题目描述

Little Vlad is fond of popular computer game Bota-2. Recently, the developers announced the new add-on named Bota-3. Of course, Vlad immediately bought only to find out his computer is too old for the new game and needs to be updated.

There are $ n $ video cards in the shop, the power of the $ i $ -th video card is equal to integer value $ a_{i} $ . As Vlad wants to be sure the new game will work he wants to buy not one, but several video cards and unite their powers using the cutting-edge technology. To use this technology one of the cards is chosen as the leading one and other video cards are attached to it as secondary. For this new technology to work it's required that the power of each of the secondary video cards is divisible by the power of the leading video card. In order to achieve that the power of any secondary video card can be reduced to any integer value less or equal than the current power. However, the power of the leading video card should remain unchanged, i.e. it can't be reduced.

Vlad has an infinite amount of money so he can buy any set of video cards. Help him determine which video cards he should buy such that after picking the leading video card and may be reducing some powers of others to make them work together he will get the maximum total value of video power.

## 说明/提示

In the first sample, it would be optimal to buy video cards with powers $ 3 $ , $ 15 $ and $ 9 $ . The video card with power $ 3 $ should be chosen as the leading one and all other video cards will be compatible with it. Thus, the total power would be $ 3+15+9=27 $ . If he buys all the video cards and pick the one with the power $ 2 $ as the leading, the powers of all other video cards should be reduced by $ 1 $ , thus the total power would be $ 2+2+14+8=26 $ , that is less than $ 27 $ . Please note, that it's not allowed to reduce the power of the leading video card, i.e. one can't get the total power $ 3+1+15+9=28 $ .

In the second sample, the optimal answer is to buy all video cards and pick the one with the power $ 2 $ as the leading. The video card with the power $ 7 $ needs it power to be reduced down to $ 6 $ . The total power would be $ 8+2+2+6=18 $ .

## 样例 #1

### 输入

```
4
3 2 15 9
```

### 输出

```
27
```

## 样例 #2

### 输入

```
4
8 2 2 7
```

### 输出

```
18
```

# 题解

## 作者：RainFestival (赞：6)

题目给你 $n$ 个数，让你求 $\max\limits_{i=1}^{n}(\sum\limits_{k=1}^{n}a_k-\sum\limits_{k=1}^{n}(a_k\mod a_i))$

$n\le200000,\forall a_i\le200000$

暴力 $O(n^2)$ 显然不行

设 $q=\max\limits_{i=1}^{n}a_i$

定义 $s_i=\sum\limits_{k=1}^{n}\lfloor{\frac{a_k}{a_i}}\rfloor$

我们可以转化为求 $\max\limits_{i=1}^{n}s_i$

首先有一个性质，对于 $\forall i,j$ , 如果 $a_i=a_j$ 那么 $s_i=s_j$

注意到 $q\le 200000$ ,也就是说 $a_i\in [1,200000]$

所以我们枚举 $i$ , 如果 $a_i$ 是第一次出现，我们对 $a_i$ 求解

如果不是第一次出现，那么我们能找到一个求解过的 $a_p$ , 满足 $a_p=a_i$ ,所以 $s_p=s_i$ , $s_i$ 一定不会比 $s_p$ 优 $(s_i$ 一定不会 $>s_p)$

我们可以枚举 $x=\lfloor\frac{a_k}{a_i}\rfloor$

则对答案 $s_i$ 的贡献为 $p\cdot x$ ,其中 $p$ 是 $a_k\in[a_i\cdot x,a_i\cdot (x+1)-1]$ 的 $k$ 的数量

现在的重点是尽量快地求出 $a_k\in[a_i\cdot x,a_i\cdot (x+1)-1]$ 的 $k$ 的数量

我们可以利用前缀和 $O(q)$ 预处理 $O(1)$ 求

总共需要枚举的 $x$ 的量为 $\sum\limits_{i=1}^{q} \frac{q}{i}=O(q \log q)$

则总时间复杂度为 $O(n+q \log q)$ , 总空间复杂度为 $O(n+q)$ , 可以通过

$20$ 行代码：
```cpp
#include<cstdio>
#include<algorithm>
#define cnt 200000
int n,f[500005],g[500005],val[500005];
long long ans;
int solve(int l,int r){return g[r]-(l!=0?g[l-1]:0);}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&f[i]),++val[f[i]];
	for (int i=1;i<=cnt*2;i++) g[i]=g[i-1]+val[i];
	for (int i=1;i<=cnt;i++)
	{
		if (!val[i]) continue;
		long long s=0;
		for (int j=0;i*j<=cnt;j++) s=s+1ll*i*j*solve(i*j,i*(j+1)-1);
		ans=std::max(ans,s);
	}
	printf("%lld\n",ans);
}
```

然后就可以 AC 啦

QAQ


---

## 作者：ModestCoder_ (赞：4)

刚开始只会一个暴力

后来发现了一个突破口：$1<=a_{i}<=200000$

那么就可以做了，假设以$x$为基数，那么值在$[x*i,x*(i+1)-1]$之间的数都会变成$x*i$，所以开个桶就完事了

枚举每个数作为基数，枚举倍数，时间复杂度为$O(能过)$

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 200010
#define LL long long
using namespace std;
const LL N = 200000;
LL n, sum[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read();
	for (int i = 1; i <= n; ++i){
		int x = read();
		++sum[x];
	}
	for (int i = 1; i <= N; ++i) sum[i] += sum[i - 1];
	LL ans = 0;
	for (LL i = 1; i <= N; ++i)
		if (sum[i] != sum[i - 1]){
			LL s = 0;
			for (LL j = 1; i * j <= N; ++j) s += i * j * (sum[min(N, i * (j + 1) - 1LL)] - sum[i * j - 1]);
			ans = max(ans, s);
		}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：igAC (赞：3)

# $\text{Describe}$

模拟赛 $\text I$ 题，简单题。

[洛谷link](https://www.luogu.com.cn/problem/CF731F)

[Codeforces link](https://codeforces.com/contest/731/problem/F)

简要题意：给定一个长度为 $n$ 的序列 $a$，选择一个数 $a_i$，求最大的 

$$
\sum^{n}_ {j=1} \lfloor \dfrac{a_j}{a_i} \rfloor a_i
$$

# $\text{Solution}$

我们先来观察原式：

$$
\sum^{n}_ {j=1} \lfloor \dfrac{a_j}{a_i} \rfloor a_i
$$

我们发现 $a_i$ 是固定的，所以只需要快速求出 $\sum \lfloor \frac{a_j}{a_i} \rfloor$ 就行了。

那么问题又来了，我们该怎么求呢？

我们会发现 $ka_i \sim (k+1)a_i-1$ 的贡献是一样的，他们对答案的贡献都是 $k$。

这就启发了我们可以统计各个数字出现了多少次，这是可以做到的，因为 $a_i \le 2 \times 10^5$。

所以我们可以开一个线段树来维护（其实前缀和就行了，这个飞舞非想到了线段树/kk）。

对于每个 $a_i$，我们枚举它的倍数，看看出现了多少次，统计答案即可。

# $\text{Code}$

丑陋的线段树代码：

```cpp
//模拟赛 I 题 
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define int long long
#define N 200005
#define D 200000
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,a[N],ans;
bool vis[N];
struct Segment{
	int l,r;
	int val;
}node[N<<2];
void build(int index,int l,int r){
	node[index].l=l,node[index].r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(index<<1,l,mid);
	build(index<<1|1,mid+1,r);
}
void getnew(int index){node[index].val=node[index<<1].val+node[index<<1|1].val;}
void change(int index,int to){
	if(node[index].l==node[index].r){
		++node[index].val;
		return;
	}
	int mid=(node[index].l+node[index].r)>>1;
	if(to<=mid) change(index<<1,to);
	else change(index<<1|1,to);
	getnew(index);
}
int query(int index,int l,int r){
	if(l<=node[index].l && node[index].r<=r) return node[index].val;
	int mid=(node[index].l+node[index].r)>>1,res=0;
	if(l<=mid) res=query(index<<1,l,r);
	if(r>mid) res+=query(index<<1|1,l,r);
	return res;
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	build(1,1,D);
	for(int i=1;i<=n;++i) change(1,a[i]);
	for(int i=1;i<=n;++i) vis[a[i]]=1;
	for(int i=1;i<=D;++i){
		if(vis[i]){
			int d=0;
			for(int j=0;i*j<=D;++j) d+=query(1,i*j,min((int)D,i*(j+1)-1))*(i*j);
			ans=max(ans,d);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Kevin911 (赞：1)

## 题意

以数组中某个元素为模数 $p$，求 $\sum_{i=1}^n a_{i}-a_{i}\bmod p$ 的最大值。

## 思路：

可以通过预处理的方式，枚举以值域中的每个数为模数的和，最后在统计答案即可。

先枚举模数 $p$，然后会发现 $a_{i}-a_{i}\bmod p$ 就是 $\leq a_{i}$ 的最大的 $p$ 的倍数，可以写作 $\sum_{i=1}^n\lfloor\frac{a[i]}{p}\rfloor\times p$ 的形式。

看到 $\lfloor\frac{a[i]}{p}\rfloor$ 可以想到（$k$ 为整数）$\lfloor\frac{p\times k}{p}\rfloor$ 和 $\lfloor\frac{p\times (k+1)-1}{p}\rfloor$ 是相同的，所以一次枚举是通过前缀和统计 $p\times k$ 到 $p\times (k+1)-1$ 的出现次数，再乘上固定的倍数即可。

时间复杂度是调和级数。
$$
\sum_{i=1}^n \frac{n}{i}=O(n\log n)
$$
具体细节详见代码。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;//注意开大点，倍数可能超出值域
int a[maxn],b[maxn],sum[maxn];
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]++;
	for(int i=1;i<=1e6;i++) b[i]+=b[i-1];
	for(int i=1;i<=2e5;i++)
		for(int j=0;j<=2e5;j+=i) sum[i]+=(b[i+j-1]-b[max(j-1,0ll)])*(j/i*i);
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,sum[a[i]]);
	cout<<ans;
}
```

---

## 作者：Dream__Sky (赞：1)

首先根据模运算的性质，化简式子：
$$\max_{k=1}^{n}\sum_{i=1}^{n}(a_i-a_i\bmod a_k)=\max_{k=1}^{n}a_k\cdot\sum_{i=1}^{n}\lfloor \dfrac{a_i}{a_k}\rfloor$$

我们枚举每个 $k$，之后要快速求出 $\sum_{i=1}^{n}\lfloor \dfrac{a_i}{a_k}\rfloor$ 带来的贡献。

我们发现，根据向下取整的原理，对于每个 $a_i$，当它在 $[x\cdot a_k,(x+1)\cdot a_k-1]$ 这个范围中时，它的贡献为 $x$。

我们进行反推，枚举 $x$，来求出这个区间内数的个数，来算出贡献。此时可以用桶和前缀和来维护这个区间内个数的个数。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m=2e5,a[200010],v[200010],ans,daan;
signed main()
{
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		a[x]++,v[x]=1;
	}
	for(int i=1;i<=m;i++) a[i]+=a[i-1];

	for(int i=1;i<=m;i++){
		if(!v[i]) continue;
		ans=0;
		for(int k=1;k*i<=m;k++)
			ans+=k*(a[min(m,(k+1)*i-1)]-a[k*i-1]);
		daan=max(daan,ans*i);
	}
	cout<<daan;
	return 0;
}


```


---

## 作者：XXh0919 (赞：1)

这道题可以用暴力。通过读题我们可以知道对于每一个 $a_k$，它在 $[a_k\times j,a_k\times (j+1)-1]$ 这个区间内它的贡献为 $a_k\times j$，所以我们可以开一个桶，再用上前缀和即可。有个细节要注意：如果枚举的不是 $a$ 数组内的元素就跳过。

### AC Code：

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;
long long n;
ll a[500005];
ll t[500005],ans,f[500005],sum;

int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(ll i=1;i<=n;++i){
		cin>>a[i];
		t[a[i]]++;//装桶
		f[a[i]]++;
	}
	for(ll i=1;i<=200000;++i){
		t[i]+=t[i-1];//前缀和
	}
	for(ll i=1;i<=200000;++i){
		sum=0;
		if(!f[i])//不在 a 数组内
		   continue;//回炉重造
		for(ll j=i;j<=200000;j+=i){
			sum+=j*(t[min(200000ll,i+j-1)]-t[j-1]);//求出它的贡献
		}
		ans=max(ans,sum);//找最大
	}
	cout<<ans<<endl;
	return 0;
}
```
注：借鉴了神犇 [gz_jcxy](https://www.luogu.com.cn/user/667250) 的思路。

---

## 作者：ZLCT (赞：0)

# CF731F Video Cards
## 题目翻译
给定一个长度为 $n$ 的数组 $a$，求 $\max\limits_{j=1}^{n}\{\sum\limits_{i=1}^{n}(a_i-a_i\bmod a_j)\}$。
## 从题意入手
首先这题观察原题发现十分不容易思考，于是我们不妨转换一下题意，把取模运算替换。\
下面分别介绍两种思路：
1. 因为我们观察到原式每次其实可以拆分成 $(\sum\limits_{i=1}^{n}a_i)-(\sum\limits_{i=1}^{n}a_i\bmod a_j)$。\
观察到前半部分与 $j$ 无关，于是我们可以得出原问题的一个对偶问题 $\sum\limits_{i=1}^{n}a_i-\min\limits_{j=1}^{n}\{\sum\limits_{i=1}^{n}a_i\bmod a_j\}$。\
其实这样我们发现也不好办，于是我们继续考虑。
2. 对于这个 $a_i-a_i\bmod a_j$ 的形式，我们在数论里面也见到过，它就等于 $\lfloor{\frac{a_i}{a_j}}\rfloor$，那这个数我们就可以利用分块的思想暴力求了。\
对于每个 $a_j$，一共只会存在 $\lfloor{\frac{n}{a_j}}\rfloor$ 种不同的值，而根据数论分块的思想，我们可以 $O(1)$ 求出所有同样的值之和，而总复杂度就是一个调和级数，总复杂度 $O(n\log n)$。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+666;
const int maxn=2e5;
int n,a[N],b[N],ans,sum[N],cnt,c[N];
set<int>s;
signed main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        s.insert(a[i]);
        b[a[i]]++;
    }
    for(int i:s){
        c[++cnt]=i;
    }
    for(int i=1;i<=maxn;++i){
        sum[i]=sum[i-1]+b[i];
    }
    for(int i=1;i<=cnt;++i){
        int res=0;
        for(int j=1;j<=c[cnt]/c[i];++j){
            res+=c[i]*j*(sum[min(c[i]*j+c[i]-1,maxn)]-sum[min(c[i]*j-1,maxn)]);
        }
        ans=max(ans,res);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Xiphi (赞：0)

考虑暴力，对于一个 $a_k$，则在 $[a_k\times j,a_k\times (j+1)-1]$ 范围内的数的贡献就为 $a_k \times j$，暴力跳+桶子即可，复杂度调和级数。有一个细节就是如果枚举的是域值而非 $a$ 数组，则若次数不存在，则跳过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[200005];
int box[200005],S=0,vis[200005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		box[a[i]]++;
		vis[a[i]]++;
	}
	for(int i=1;i<=2e5;++i) box[i]+=box[i-1];
	for(int i=1;i<=2e5;++i){
		if(!vis[i]) continue;
		int ans=0;
		for(int j=i;j<=2e5;j+=i){
			ans+=j*(box[min(200000ll,i+j-1)]-box[j-1]);
		}
		S=max(S,ans);
	}
	cout<<S;
	return 0;
} 
```

---

## 作者：C6H14 (赞：0)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF731F)

[My blog](https://www.luogu.com.cn/blog/128433/#)


## 思路

先把式子转化一下：

$$
\max \limits_{k=1}^n \sum \limits_{i=1}^n (a_i-a_i \mod a_k) = \max \limits_{k=1}^n \sum \limits_{i=1}^n a_k * \left \lfloor \dfrac{a_i}{a_k} \right \rfloor = \max \limits_{k=1}^n a_k * \sum \limits_{i=1}^n \left \lfloor \dfrac{a_i}{a_k} \right \rfloor
$$

由此可以考虑这样做：枚举 $k$，想办法快速算出 $\sum \limits_{i=1}^{n} \left \lfloor \dfrac{a_i}{a_k} \right \rfloor$。

观察数据发现 $a_i$ 很小，可以用桶来存。

我们知道：$\left \lfloor \dfrac{0}{x}\right \rfloor = \left \lfloor \dfrac{1}{x}\right \rfloor = \ldots =\left \lfloor \dfrac{x-1}{x}\right \rfloor$。

那么可以维护桶的前缀和，记录在数组 $b[i]$ 中，对于每一个 $a_k$，将 $b$ 中答案相同的数一块一块地处理，最坏时间复杂度是 $O(n \log n)$。

**小优化**：

原式还可以这样转化：

$$
\max \limits_{k=1}^n \sum \limits_{i=1}^n (a_i - a_i \mod a_k) = \max \limits_{k=1}^n (\sum \limits_{i=1}^n a_i - \sum \limits_{i=1}^na_i \mod a_k) = \sum \limits_{i=1}^n a_i - \min \limits_{k=1}^n \sum \limits_{i=1}^n a_i \mod a_k
$$

根据初等数学知识可知，假如 $a_k$ 是 $a_{k'}$ 的倍数，则

$$
\sum \limits_{i=1}^n a_i \mod a_k > \sum \limits_{i=1}^n a_i \mod a_{k'}
$$

用类似于质数筛的方式可以少枚举一些 $a_k$。

## 代码

```cpp
ll n,ans,a[200005],b[200005],maxn;//a为原数组，b为桶的前缀和，maxn为值域上限
bool f[200005];//是否已经枚举过因子
int main()
{
	n=read();
	for (int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+1+n);
	maxn=a[n];
	for (int i=1;i<=n;++i)
		++b[a[i]];
	for (int i=1;i<=maxn;++i)
		b[i]+=b[i-1];
	for (int i=1;i<=n;++i)
	{
		if (f[a[i]])//枚举过因子就不用算了
			continue;
		for (int j=a[i];j<=maxn;j+=a[i])
			f[j]=1;
		ll cnt=0;
		for (int j=a[i];j<=maxn-a[i];j+=a[i])//一块块处理
			cnt=cnt+(b[j+a[i]-1]-b[j-1])*j;
		cnt+=(b[maxn]-b[maxn/a[i]*a[i]-1])*(maxn/a[i])*a[i];//防止数组越界
		ans=max(ans,cnt);
	}
	write(ans);
	return 0;
}
```


---

