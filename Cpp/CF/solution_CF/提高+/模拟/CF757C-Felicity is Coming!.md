# Felicity is Coming!

## 题目描述

It's that time of the year, Felicity is around the corner and you can see people celebrating all around the Himalayan region. The Himalayan region has $ n $ gyms. The $ i $ -th gym has $ g_{i} $ Pokemon in it. There are $ m $ distinct Pokemon types in the Himalayan region numbered from $ 1 $ to $ m $ . There is a special evolution camp set up in the fest which claims to evolve any Pokemon. The type of a Pokemon could change after evolving, subject to the constraint that if two Pokemon have the same type before evolving, they will have the same type after evolving. Also, if two Pokemon have different types before evolving, they will have different types after evolving. It is also possible that a Pokemon has the same type before and after evolving.

Formally, an evolution plan is a permutation $ f $ of $ {1,2,...,m} $ , such that $ f(x)=y $ means that a Pokemon of type $ x $ evolves into a Pokemon of type $ y $ .

The gym leaders are intrigued by the special evolution camp and all of them plan to evolve their Pokemons. The protocol of the mountain states that in each gym, for every type of Pokemon, the number of Pokemon of that type before evolving any Pokemon should be equal the number of Pokemon of that type after evolving all the Pokemons according to the evolution plan. They now want to find out how many distinct evolution plans exist which satisfy the protocol.

Two evolution plans $ f_{1} $ and $ f_{2} $ are distinct, if they have at least one Pokemon type evolving into a different Pokemon type in the two plans, i. e. there exists an $ i $ such that $ f_{1}(i)≠f_{2}(i) $ .

Your task is to find how many distinct evolution plans are possible such that if all Pokemon in all the gyms are evolved, the number of Pokemon of each type in each of the gyms remains the same. As the answer can be large, output it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first case, the only possible evolution plan is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757C/0f3d3fa4a05453bc60af48b50b7ec23b8573ce3e.png)In the second case, any permutation of $ (1,2,3) $ is valid.

In the third case, there are two possible plans:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757C/920c811062805c472b5e406e9e45765c9a8b28b8.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757C/56a5356a9ec69bf08d742b29dd884bc2d69e350c.png)In the fourth case, the only possible evolution plan is:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757C/f1bc71deb3bf669220272fbdea0bf59bbd336556.png)

## 样例 #1

### 输入

```
2 3
2 1 2
2 2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 3
3 1 2 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2 4
2 1 2
3 2 3 4
```

### 输出

```
2
```

## 样例 #4

### 输入

```
2 2
3 2 2 1
2 1 2
```

### 输出

```
1
```

## 样例 #5

### 输入

```
3 7
2 1 2
2 3 4
3 5 6 7
```

### 输出

```
24
```

# 题解

## 作者：Wf_yjqd (赞：1)

简单题又做了好久。

------------

显然一个种类可进化成另一个种类，当且仅当两个种类在每个训练馆个数都相同。

考虑将每个种类出现的位置哈希起来，那么哈希值相同的种类可以随便进化。

若有 $x$ 个哈希值相同的种类，方案数为 $x!$，总方案数乘起来即可。

------------

注意一次没出现的种类也可以相互进化。

实测需要哈希值的值域需要超过 int 的范围。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 bnt;
const ll mod=1e9+7,maxn=1e6+26,base=8414141,Mod=1e7+23;//564611849
ll n,m,mm,a,ans,jc[maxn];
map<ll,ll> cnt,zzcnt;
int main(){
    scanf("%lld%lld",&n,&m);
    jc[0]=1;
    for(ll i=1;i<=m;i++)
        jc[i]=jc[i-1]*i%mod;
    for(ll j=1;j<=n;j++){
        scanf("%lld",&mm);
        for(ll i=1;i<=mm;i++){
            scanf("%lld",&a);
            cnt[a]=bnt(cnt[a])*base+j%Mod;
        }
    }
    for(auto i:cnt)
        zzcnt[i.second]++;
    ans=1;
    for(auto i:zzcnt){
        m-=i.second;
        ans=ans*jc[i.second]%mod;
    }
    printf("%lld\n",ans*jc[m]%mod);
    return 0;
}
```


---

## 作者：daniEl_lElE (赞：1)

## 思路

考虑两种宝可梦可以互相转化的条件。当且仅当他们在**所有**的训练馆中出现次数都一样。

那么我们现在希望统计的就是每种宝可梦出现的次数。用 $\texttt{vector}$ 存储每种在哪些训练馆出现过几次。出现 $i$ 次直接考虑插入 $i$ 次即可。容易发现有序。

接下来对于每个 $\texttt{vector}$ 考虑存入一个 $\texttt{map}$ 中统计每种出现了几次。乘上其阶乘即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
#define ls i*2
#define rs i*2+1
#define Ls ls,l,mid
#define Rs rs,mid+1,r
using namespace std;
const int mod=1e9+7;
vector<int> vc[1000005];
map<vector<int>,int> mp;
signed main(){
	int n,m,ans=1;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int g;
		cin>>g;
		while(g--){
			int a;
			cin>>a;
			vc[a].push_back(i);
		}
	}
	for(int i=1;i<=m;i++){
		mp[vc[i]]++;
		ans=ans*mp[vc[i]]%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：泠小毒 (赞：1)

# Felicity is Coming!
神奇宝贝的进化方案是一个全排列，假设有三种宝可梦，那么对应就可以有：

（1,2,3）（1,3,2）（2,1,3）（2,3,1）（3,1,2）（3,2,1）这六种进化方案（六种全排列）

这里（1,3,2）相当于：1进化成1,2进化成3,3进化成2

需要满足所有约束条件才能作为可行进化方案：

对于一个训练馆，之前有a个b种类的宝可梦，那么训练馆里所有的宝可梦进化之后，还要有a个b种类的宝可梦才行，种类不能增加，不能减少，也不能改变

问一共有多少个可行方案
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190513/)
## 解法
如果a宝可梦和b宝可梦能互相进化，一定满足a出现过的训练馆和b出现过的训练馆以及次数都相同

所以开vector来维护这一性质，然后sort，~~没错vector之间可以直接sort（大雾~~

相同的一定放在一起，n个相同的会产生n!的贡献，对于没有出现过的宝可梦，也会产生一个贡献，因为进化是不能一对多或多对一的，所以贡献也是一个n!
## ac代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
vector<int>a[1000010];
int n,m,g,x;
ll cnt=1,ans=1;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
	{
        scanf("%d",&g);
        for(int j=1;j<=g;j++)scanf("%d",&x),a[x].push_back(i);
    }
    sort(a+1,a+m+1);
    for(int i=2;i<=m;i++)
        if(a[i]==a[i-1])cnt++,ans=ans*cnt%mod;
        else cnt=1;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
题意：  
神奇宝贝的进化方案是一个全排列，对于一个训练馆，之前有 $a$ 个 $b$ 种类的宝可梦，那么训练馆里所有的宝可梦进化之后，还要有 $a$ 个 $b$ 种类的宝可梦才行，种类不能增加，不能减少，也不能改变。问一共有多少个可行方案。

逆向思维。
## 分析。
因为两个宝可梦互相进化了之后，每个场馆中的这两种宝可梦数量都不会改变。所以如果两个宝可梦在所有场馆中数量都相等，那么这两个宝可梦一定可以互相进化。因此，我们可以考虑用变长数组存储每一种的宝可梦在每个场馆中的分布。通过记录出现的次数，如果两个宝可梦在场馆的的分布一样，那我们就可以选择将这两个宝可梦互相进化。

由于在 $n$ 个可以相互进化的宝可梦中寻找全排列，所以一共有 $n!$ 个方案，那么我们可以将变长数组从小到大排列，所以如果有相同的那么一定挨在一起，此时我们只要找到至少两个相邻的，表明有 $sum$ 个相同的，那么就代表有 $sum$ 个宝可梦可以相互进化。如果断层，则重新计数，然后统计答案即可。

代码如下，仅供参考：
```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const long long mod=1e9+7;
long long n,m,g,a;
vector<int> v[1000005];
long long sum,ans=1;
int main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		cin>>g;
		for (int j=1;j<=g;j++){
			cin>>a;
			v[a].push_back(i);
		}
	}
	sort(v+1,v+m+1);
	for (int i=1;i<=m;i++){
		if(v[i]==v[i-1]){
			sum++;//统计相同的宝可梦。
			ans=(ans*sum)%mod;
		}
		else sum=1;//重新计数。
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：囧仙 (赞：0)

## 题目简述

> 有 $m$ 个数字。你需要求出全排列 $a_i$，据此定义 $f(x)=a_x$。它需要满足 $n$ 个条件。每个条件会给定一个大小为 $g_i$ 的集合 $S$，表示 $S$ 当中的元素通过 $f$ 映射后和 $S$ 中的元素**一一对应**。  
> 询问有多少种全排列方案。$1\le m\le 10^6;1\le \sum g_i\le 5\times 10^5$。

## 题解

首先取 $a_i=i$。考虑通过交换其中的一些元素组成新的全排列。

**引理**：两个数字 $a_x,a_y$ 可以发生互换，当且仅当「出现了 $x$ 的条件」组成的集合等于「出现了 $y$ 的条件」组成的集合。

> 这是容易证明的。如果 $x,y$ 所在的条件集合相同，就说明每个有 $x$ 的条件给出的集合里都有 $y$，并且对于任意 $x,y$ 所在的集合 $T$ 都有 $a_x\in T;a_y\in T$。因此交换了 $a_x,a_y$ 后仍然符合条件；如果 $x,y$ 所在的条件集合不同，那么必然存在某个 $T$，使得 $x$ 在里面而 $y$ 不在，或者 $y$ 在里面而 $x$ 不在。不妨设 $x$ 在 $T$ 里而 $y$ 不在，那么 $a_x\in T;a_y\notin T$，交换后会导致 $a_x\notin T;a_y\notin T$。

有了引理后，我们会发现如果有 $t$ 个数字所处的条件集合完全相同，那么它们对答案的贡献是 $t!$（也就是任意交换两者都是合法的，因此对答案的贡献是 $t$ 个元素的全排列）。将每组这样的集合的贡献相乘即可得到答案。

用哈希求出哪些数字所处的条件集合完全相同，再统计答案即可。使用但哈希可能会被卡。总时间复杂度为 $\mathcal O(m+\sum g_i)$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
typedef unsigned int       u32;
typedef unsigned long long u64;
const int MOD =1e9+7;
const int MAXN=1e6+3;
int n,m,ans=1,F[MAXN]; u64 H[MAXN],G[MAXN]; map<u64,int> M;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
mt19937 MT(114514+223);
int main(){
    n=qread(),m=qread(),F[0]=1; up(1,n,i){
        int g=qread(),x; u32 u=i+MT(),v=i+MT();
        up(1,g,j) x=qread(),H[x]=H[x]*999853+u,G[x]=G[x]*13331+v;
    }
    up(1,m,i) ++M[H[i]^G[i]],F[i]=1ll*F[i-1]*i %MOD;
    for(auto &x:M) ans=1ll*ans*F[x.second]%MOD;
    printf("%d\n",ans);
    return 0;
}
```



---

