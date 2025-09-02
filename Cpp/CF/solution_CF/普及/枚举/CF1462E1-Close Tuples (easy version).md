# Close Tuples (easy version)

## 题目描述

This is the easy version of this problem. The only difference between easy and hard versions is the constraints on $ k $ and $ m $ (in this version $ k=2 $ and $ m=3 $ ). Also, in this version of the problem, you DON'T NEED to output the answer by modulo.

You are given a sequence $ a $ of length $ n $ consisting of integers from $ 1 $ to $ n $ . The sequence may contain duplicates (i.e. some elements can be equal).

Find the number of tuples of $ m = 3 $ elements such that the maximum number in the tuple differs from the minimum by no more than $ k = 2 $ . Formally, you need to find the number of triples of indices $ i < j < z $ such that

 $ $$$\max(a_i, a_j, a_z) - \min(a_i, a_j, a_z) \le 2. $ $ </p><p>For example, if  $ n=4 $  and  $ a=\[1,2,4,3\] $ , then there are two such triples ( $ i=1, j=2, z=4 $  and  $ i=2, j=3, z=4 $ ). If  $ n=4 $  and  $ a=\[1,1,1,1\]$$$, then all four possible triples are suitable.

## 样例 #1

### 输入

```
4
4
1 2 4 3
4
1 1 1 1
1
1
10
5 6 1 3 2 9 8 1 2 4```

### 输出

```
2
4
0
15```

# 题解

## 作者：light_ght (赞：6)

# 组合数

[~~看不懂的~~题目传送门](https://www.luogu.com.cn/problem/CF1462E1)  

  ###  [博客食用 效果更佳](https://www.luogu.com.cn/blog/Rstar-PanzerTigerII/solution-cf1462e1) 
  
------------
## 分析
 - 首先~~恶心人的~~是这是道纯英文的题的**题意**。借助@walk_alone
 dalao的题解，我们可以明白这题面的意思是 ：给定一个数组 $a$，取 $x \ ,y \ ,z\in a$ 满足 $x \ne y \ne z$，使得 $max(x \ ,y \ ,z) - min(x \ ,y\ ,z) \leqslant 2 $，问最多能找出多少组。
 
- 拿到题首先想的是 **`dfs`**，写了一个 $O(n^2)$ 的code 。当然对于一个 $2^5$ 的数据不 TLE 才怪。还好数据不算太强，勉强搞过几个点。

  （随后听到机房大犇 @xspcz 在议论能不能用 **`map`** 存数据。但我不会啊……）

- 最终在大犇们早都做完这题之后，我才感觉这题和组合数有些沾边（果然还是我太蒻了），于是想到了一个优雅的~~暴力~~算法。

 什么？你不知道组合数？巧了，我[本来也不清楚，帮你度娘。](https://baike.baidu.com/item/%E7%BB%84%E5%90%88%E6%95%B0/2153250?fr=aladdin)

- 本想一发 **`sort`** 之后从头开始求区间的组合，但是窝发现有问题，由于数据**可能重复**。
  
  如数据 $1 \ 2 \ 3 \ 3 \ 4$，按上述方法就是答案计数器先加上 $1$ 和 $3$ 之间的组合数，求完之后再加上 $2$ ~ $4$ 之间的组合数，但是 $1$ ~ $3$ 之间的 $2 \ 3 \ 3$ 和 $2$ ~ $4$ 之间的 $2 \ 3 \ 3$ 重复了。~~于是卡了一节课 窝太菜了~~
   
         
- 后经学长点拨，在排序后先取一个值 $a[i]$，再在 $(a[i],a[i+2])$ 范围内取两个值，便可以避免重复。（妙哉！）

	例如，求 $1$ ~ $3$ 时，取最小值 $1$，在 $(1,3]$ 区间内（即 $2 \ 3 \ 3$）任取两个值；
    
   接着求 $2$ ~ $4$ 时，取最小值 $2$，在 $(2,4]$ 区间内任取两个值。
    
    	不难看出，以上情况无重复。 
   
- 想清楚原理后就不难实现了   

------------
## 实现 
 
   贴核心代码：
    
```cpp
	
   int t, /*anti-cheating*/ n;
	//本来想用桶，但后来想想没甚必要 
   int main(){ ios::sync_with_stdio(0);//加速cin、cout ，使其复杂度接近printf、scanf   
	cin>>n;  
	while(n--)｛  
		ll cnt=0;//！！！不开long long 见祖宗！！！ 
		cin>>t;		
		for(int i=1;i<=t;i++)
			cin>>ght[i];		
		sort(ght+1, ght+t+1);//排序数据以便枚举 
    		int r=1;
		for(int i=1;i<=t;i++){
			while(ght[r+1]<=2+ght[i] && r+1<=t） 
				r++;			
			if(r>=i+2)
				cnt+=(ll)(r-i-1)*(r-i);//！！被long long 卡死了一次 ！！
			}
		cout<<cnt<<endl;
		}
	}
```
 满分17，目测已过。。
 

[Hard 版本](https://www.luogu.com.cn/problem/CF1462E2)就是将组合数的最大最小值之差改为了输入的数据，原理是一样的。




##  重申一遍！！不开long long见祖宗！！！！！


------------
[**没事的话，来我主页逛逛？**](https://www.luogu.com.cn/user/426545)


本蒟蒻为了防止图床炸掉重写本题解，望管理大大高抬贵手 :-）

    

---

## 作者：Weekoder (赞：5)

### 思路

（完全再现赛时思路。）

首先，根据三元组条件 $\max(a_i, a_j, a_k) - \min(a_i, a_j, a_k)$，我们可以想到快速统计多组三元组，节省时间。也就是说，只要最小值和最大值固定，剩下的数就可以随便选取。

可是，假设固定了最小值和最大值，又要怎样知道选取的第三个数是否小于最小值，或者大于最大值呢？换句话说，如果要逐个判断每个数是否满足条件，就无法达到快速统计的目的。解决方案很简单：三元组的选取与数组的排列无关，可以将数组排序，这样答案就固定在了一个区间里。

现在，我们可以整理一下题目的最终要求：在排序后的数组中，找到所有的 $l,r(l<r)$ 满足 $a_r-a_l\le2$，统计答案。

现在有两个问题，我们来逐一解决。

1. 如何在 $\mathcal{O}(n\log n)$ 的时间复杂度内找到 $l,r$？

事实上，只需要找到较大的区间，就能一并统计较小区间的答案。由于数组有序，显然可以枚举 $l$，二分查找最大的 $r$。

2. 得到了 $l,r$，如何统计答案？

当起点为 $i$，终点为 $j$ 时，答案为区间长度减二 $(j-i+1)-2=j-i-1$（减去起点和终点，中间的数都可以作为三元组中的一个数）。然而，只是这样是不够的：上面说到“只需要找到较大的区间，就能一并统计较小区间的答案”，但这里并没有统计到小区间，也就是更小的终点 $j$。起点为 $i$ 的总贡献可以表示为：

$$
\begin{aligned}
{} & \sum_{x=i+2}^jx-i-1 \\
= & (\sum_{x=i+2}^jx)-(j-(i+2)+1)\times i-(j-(i+2)+1)\times1 \\
= & (\sum_{x=i+2}^jx)-(j-i-1)-(j-i-1)\times i
\end{aligned}
$$

$\displaystyle\sum_{x=i+2}^jx$ 可以用高斯求和公式计算，即 $\text{sum}(l,r)=\displaystyle\sum_{i=l}^ri=\displaystyle\frac{(l+r)\times(r-l+1)}{2}$。

于是这道题就很简单了：排序，枚举，统计答案。

注：三元组数量差不多在 $n^3$ 左右，开 long long！

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 5;

int T, n, a[N], ans;

int bin_search(int X) {
    int l = X - 1, r = n + 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (a[mid] - a[X] <= 2)
            l = mid;
        else
            r = mid;
    }
    return l;
}

int sum(int l, int r) {
    return (l + r) * (r - l + 1) / 2;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	while (T --) {
	    cin >> n;
	    ans = 0;
	    for (int i = 1; i <= n; i++)
	       cin >> a[i];
	    sort(a + 1, a + 1 + n);
	    for (int i = 1; i <= n; i++) {
	        int id = bin_search(i);
	        if (id - i + 1 < 3)
	           continue;
	        ans += sum(i + 2, id) - (id - i - 1) - (id - i - 1) * i;
	    }
	    cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：4)

### 思路

我们可以先给整个数列进行 **排序**。接着，我们对排序后的数组枚举每个下标 $i$ ，假设 $a_i$ 就是最小值。然后，**二分** 求出满足 $a_i\le a_j \le a_i+2$ 的 $j$ 的个数（ 假设为 $siz$ ）。最后，用排列组合公式 $\dbinom{siz}{2}=\dfrac{siz(siz-1)}{2}$ 计算出答案。

时间复杂度 $O(n\log n)$ 。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=2e5;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,t,a[Maxn+5];
long long ans; // 注意 long long

inline int Find(int x) // 二分
{
    int l=1,r=n;
    while(l<r)
    {
        int mid=(l+r+1)/2; // 注意是 l+r+1
        if(a[mid]<=x) l=mid;
        else r=mid-1;
    }
    return l;
}

int main()
{
    t=read();
    while(t--)
    {
        n=read(),ans=0;
        for(int i=1;i<=n;++i) a[i]=read();
        sort(a+1,a+n+1); // 排序
        for(int i=1;i<=n;++i)
        {
            int pos=Find(a[i]+2);
            int siz=pos-i;
            ans=ans+1ll*siz*(siz-1)/2; // 统计答案
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：walk_alone (赞：4)

这题要我们找到三元组满足最大值最小值小于等于2，其实就是一个简单排列组合的问题了。

这题数据范围如此的友好$a_i<=n$，完全可以放心大胆的桶排，用cnt数组记录每个数出现多少次，然后进行枚举：

对于每一个$x$，从小到大的去遍历，我们都可以有以下几种搞法凑出这个三元组：(其实就是$x$,$x+1$,$x+2$的排列组合)。但是要注意：有些不能重，不能走回头路，要不然就有下面的数顶替上来造成重复，如选择了$1,2,3$就不能重选$2,1,3$。因此这里是顺序往上枚举

$x,x,x$

$x,x+1,x+2$

$x,x+1,x+1$

$x,x+2,x+2$

$x,x,x+2$

$x,x,x+1$

然后组合公式用起来，

$ans+=\frac{cnt[x](cnt[x]-1)(cnt[x]-2)}{6}+cnt[x]cnt[x+1]cnt[x+2]+\frac{cnt[x]cnt[x+1](cnt[x+1]-1)}{2}+\frac{cnt[x]cnt[x+2](cnt[x+2]-1)}{2}+\frac{cnt[x]cnt[x+2](cnt[x]-1)}{2}+\frac{cnt[x]cnt[x+1](cnt[x]-1)}{2}$

代码就不放了，一个模拟就是。

---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1462E1)

[CF传送门](https://www.luogu.com.cn/problem/CF1462E1)

[AC记录](https://codeforces.com/contest/1462/submission/296857703)
# 题意简述
~~翻译真是简洁啊，直接粘过来吧！~~  
给出 $T$ 组询问，每次给出一个含 $n$ 个整数的数列 $a$，求满足如下条件的三元组 $(i,j,k)$ 的个数。

$$
\left\{
      \begin{array}{lr}
      i< j< k & \\
      \max(a_i, a_j, a_k) - \min(a_i, a_j, a_k) \le 2.
      
      \end{array}
\right.
$$
# 题解
首先，肉眼可见的是：暴力枚举 $i,j,k$ 显然不行。  
然后我们发现，条件中有一个 $\max$ 和一个 $\min$，当务之急是先干掉这两个麻烦。  
在给数组排序后，$\max(a_i, a_j, a_k)$ 就变成了 $a_k$，$\min(a_i, a_j, a_k)$ 就变成了 $a_i$。  
而且，只要 $a_r-a_l \le 2(l<r)$，那么在 $[l,r]$ 中的任意三数都满足以上条件。  
由于这个题比较简单，所以我们只需要算出:
$$C_{r-l+1}^3=\dfrac{(r-l+1)\times (r-l)\times (r-l-1)}{6}$$
即可求出 $[l,r]$ 中的三元组个数。 
# 注意
万一有两个区间重叠，要减去重叠部分的三元组个数。  
不开 long long 见祖宗！！！
# 推荐题目
[升级版](https://www.luogu.com.cn/problem/CF1462E2)
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
int t,n,a[N];
signed main(){
    CLOSE
    cin>>t;
    while(t--){
    	int ans=0;
    	cin>>n;
    	for(int i=1;i<=n;i++) cin>>a[i];
    	sort(a+1,a+1+n);//排序
    	int now=-inf,last=-1;
    	for(int i=1;i<=n;i++){
    		int tmp=i;
		    int l=i,r=n;
		    while(l<r){
		        int mid=l+r+1>>1;
		        if(a[mid]-a[i]<=2) l=mid;
		        else r=mid-1;
		    }//算出区间的右端点
    		i=l;
    		if(a[i]<=now){
    			while(a[++tmp]==a[tmp-1]&&tmp<=n);
    			i=tmp-1;
			}
    		if(i-tmp>1) ans+=(i-tmp+1)*(i-tmp)*(i-tmp-1)/6-(last!=-1&&last-tmp>1?(last-tmp+1)*(last-tmp)*(last-tmp-1)/6:0),last=i;//统计三元组个数
    		while(a[++tmp]==a[tmp-1]&&tmp<=n);
    		i=tmp-1;
		}
		cout<<ans<<'\n';
	}
    return 0;
}
```

---

## 作者：songtaoran (赞：0)

看到这种题第一眼想到枚举中间点，可惜我太蒻了没想出来。  
考虑二分。  
对于每个最小值（$a_i$），二分最大值，统计答案即可。  
都二分了当然要排序啦。  
怎么统计答案呢？  
假设最大值的下标是 $j$，则 $i + 2$ 到 $j$ 都可以作为最大值（因为还得有一个中间点）。  
可得  
$$
  ans = \sum_{t = i + 2}^j t - i - 1 = (\sum_{t = i + 2}^j t) - (i + 1) \times (j - i - 1)
$$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T, n, a[200010];
ll sum(ll l, ll r){
	return (l + r) * (r - l + 1) / 2;
}
ll Binary_Search(ll x){ // 注意函数名不能叫 binary_search, 会与库函数重名 
	ll l = x, r = n;
	while(l < r){
		ll mid = (l + r + 1) >> 1; // 注意 +1 
		if(a[mid] - a[x] <= 2) l = mid;
		else r = mid - 1;
	}
	return l;
}
int main(){
	cin >> T;
	while(T--){
		scanf("%lld", &n);
		ll cnt = 0;
		for(ll i = 1; i <= n; i++) scanf("%lld", &a[i]);
		sort(a + 1, a + n + 1);
		for(ll i = 1; i <= n; i++){
			ll id = Binary_Search(i);
			if(id - i < 2) continue; // 此时 id 无法作为末尾点
			cnt += sum(i + 2, id) - (id - i - 1) * (i + 1);
		}
		printf("%lld\n", cnt);
	}
	return 0;
}
```
[提交记录 - $285129343$](https://codeforces.com/problemset/submission/1462/285129343)

---

## 作者：__zhuruirong__ (赞：0)

## 做法分析

我们可以枚举 $i$，然后分类讨论 $a_i$ 最小、$a_i$ 最大、$a_i$ 是中间值的贡献，最后减去重复部分就行了。

怎么求贡献值呢？我们可以倒序枚举，用一个 `map` 来记录 $(i,n]$ 中的每个数的出现的次数，比如说 $a_i$ 最小，就累计一下从 $a_i$ 到 $a_i+2$ 的数字有几个，记作 $sum_i$，则贡献是 $sum_i\times (sum_i-1)\div 2$，即可能构成三元组的数量。其他情况以此类推。

**注意去重！**

## AC代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10;
int T, n, a[N], sum[N];

signed main() {
  cin >> T;
  while(T--) {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    map<int, int> vis;
    int ans = 0;
    for(int i = n; i >= 1; i--) {
      sum[i] = vis[a[i]] + vis[a[i] + 1] + vis[a[i] + 2];
      ans += sum[i] * (sum[i] - 1) / 2;
      sum[i] = vis[a[i] - 1] + vis[a[i]] + vis[a[i] + 1];
      ans += sum[i] * (sum[i] - 1) / 2;
      sum[i] = vis[a[i] - 2] + vis[a[i] - 1] + vis[a[i]];
      ans += sum[i] * (sum[i] - 1) / 2;
      sum[i] = vis[a[i] - 1] + vis[a[i]]; // 去重
      ans -= sum[i] * (sum[i] - 1) / 2;
      sum[i] = vis[a[i]] + vis[a[i] + 1];
      ans -= sum[i] * (sum[i] - 1) / 2;
      vis[a[i]]++;
    }
    cout << ans << endl;
  }
}
```

---

## 作者：紊莫 (赞：0)

简单版解法。

开一个桶记录前缀和后缀中数字出现次数，可以枚举时顺便递推。

因为差值很小，可以暴力枚举中间项，排列组合左右，这里直接**全部**写出来方便观察。

```cpp
cin>>n;int ans=0;
map<int,int> t1,t2;
F(i,1,n) cin>>a[i];
F(i,1,n) t2[a[i]]++;
F(i,1,n){
	t2[a[i]]--;
	ans+=t1[a[i]]*(t2[a[i]]+t2[a[i]+1]+t2[a[i]+2]+t2[a[i]-1]+t2[a[i]-2])+
		 t1[a[i]+1]*(t2[a[i]]+t2[a[i]+1]+t2[a[i]+2]+t2[a[i]-1])+
		 t1[a[i]+2]*(t2[a[i]]+t2[a[i]+1]+t2[a[i]+2])+
		 t1[a[i]-1]*(t2[a[i]]+t2[a[i]+1]+t2[a[i]-2]+t2[a[i]-1])+
		 t1[a[i]-2]*(t2[a[i]]+t2[a[i]-1]+t2[a[i]-2]);
	t1[a[i]]++;
}
cout<<ans<<'\n';
```

虽然内容有点多，但是思维量较少。


[完整示例代码。](https://www.luogu.com.cn/paste/xzvzw1et)

---

## 作者：ncwzdlsd (赞：0)

组合数学。

有一个很好的点：答案与序列顺序无关。

将数组排序，从左至右枚举每一个数 $a_i$，令 $a_i$ 为三元组的最小值，查找序列中满足 $a_j-a_i\leq 2$ 的所有 $j$，则区间 $(i,j]$ 中任意两个数均满足要求，即 $C_{j-i}^2$。

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
    int n;cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int j=1;
    for(int i=1;i<=n;i++)
    {
        while(a[j+1]-a[i]<=2&&j+1<=n) j++;
        if(j-i>=2) ans+=(j-i)*(j-i-1)/2;
    }
    cout<<ans<<"\n";
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

~~可能是因为写的尺取法的原因吧，竟然跑了个最优解。~~

首先，考虑到如果对于原序列任意 $3$ 个元素无法直接确定最大/最小值，并且答案与序列顺序无关，所以考虑对序列排个序，这样最大值就一定在右边，最小值就一定在左边。

我们先确定一个位置 $i$ 作为最左边的元素，那么因为序列是单调的，所以右端点 $r$ 也具有单调性，此时可以二分。然后考虑到 $i$ 增大的时候 $r$ 也会相应增大，所以可以用尺取法 $O(n)$ 求解。

同时，在 $[i+1,r]$ 中任取 $2$ 个元素，所以就是组合数 $C_{r-i}^2=\dfrac{(r-i)(r-i-1)}{2}$。

最后发现，瓶颈在排序，时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$，可能是其它代码二分的常数问题，用尺取法会快很多。~~其实桶排的话就可以做到纯线性只是不想打~~

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

## 作者：haokee (赞：0)

我们先枚举其中的 $i$（令 $a_i$ 表示为三元组中最小的那个）。假设 $a_l=i$ 的有 $a$ 个，那么我们可以在这 $a$ 个数当中任选一个。然后我们需要找到 $j$ 和 $z$。最大的数是 $i+2$，但是由于并不需要差等于 $2$ 只要求小于就行，因此我们大于 $i$ 但是不超出 $2$ 的数量为 $b$。

选了 $a$ 个当中的第 $l$ 个，那么 $a$ 个当中的前 $l-1$ 个都不能选（因为要保证顺序），然后在 $b-(a-l)$ 个剩余的元素当中任选两个元素。答案就为 $\displaystyle\sum_{i=1}^n \sum_{l=1}^{a} \binom{b-a+l}{2}$。

```cpp
```

---

