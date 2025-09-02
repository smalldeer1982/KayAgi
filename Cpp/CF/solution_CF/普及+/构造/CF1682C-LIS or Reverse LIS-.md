# LIS or Reverse LIS?

## 题目描述

You are given an array $ a $ of $ n $ positive integers.

Let $ \text{LIS}(a) $ denote the length of [longest strictly increasing subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence) of $ a $ . For example,

- $ \text{LIS}([2, \underline{1}, 1, \underline{3}]) $ = $ 2 $ .
- $ \text{LIS}([\underline{3}, \underline{5}, \underline{10}, \underline{20}]) $ = $ 4 $ .
- $ \text{LIS}([3, \underline{1}, \underline{2}, \underline{4}]) $ = $ 3 $ .

We define array $ a' $ as the array obtained after reversing the array $ a $ i.e. $ a' = [a_n, a_{n-1}, \ldots , a_1] $ .

The beauty of array $ a $ is defined as $ min(\text{LIS}(a),\text{LIS}(a')) $ .

Your task is to determine the maximum possible beauty of the array $ a $ if you can rearrange the array $ a $ arbitrarily.

## 说明/提示

In the first test case, $ a $ = $ [6, 6, 6] $ and $ a' $ = $ [6, 6, 6] $ . $ \text{LIS}(a) = \text{LIS}(a') $ = $ 1 $ . Hence the beauty is $ min(1, 1) = 1 $ .

In the second test case, $ a $ can be rearranged to $ [2, 5, 4, 5, 4, 2] $ . Then $ a' $ = $ [2, 4, 5, 4, 5, 2] $ . $ \text{LIS}(a) = \text{LIS}(a') = 3 $ . Hence the beauty is $ 3 $ and it can be shown that this is the maximum possible beauty.

In the third test case, $ a $ can be rearranged to $ [1, 2, 3, 2] $ . Then $ a' $ = $ [2, 3, 2, 1] $ . $ \text{LIS}(a) = 3 $ , $ \text{LIS}(a') = 2 $ . Hence the beauty is $ min(3, 2) = 2 $ and it can be shown that $ 2 $ is the maximum possible beauty.

## 样例 #1

### 输入

```
3
3
6 6 6
6
2 5 4 5 2 4
4
1 3 2 2```

### 输出

```
1
3
2```

# 题解

## 作者：_Ad_Astra_ (赞：7)

一道很好的思维题。

很容易想到如果一个数 $x$ 在 $a$ 中出现了 $2$ 次及以上，那么它肯定在 $LIS(a)$ 和 $LIS(a')$ 中均出现过，把这些数的数量记作 $cnt1$ 。

对于剩下的只出现了 $1$ 次的数（记作 $y$ ），它们只有以下的三种可能：

+ $y$ 在 $LIS(a)$ 中。
+ $y$ 在 $LIS(a')$ 中。
+ $y$ 既在 $LIS(a)$ 中，又在 $LIS(a')$ 中。（很明显这样的 $y$ 只有一个。）

把这样的 $y$ 的个数记为 $cnt2$ ，那么只要 $cnt2 \gt 0$ ，这部分对答案的贡献就是 $\lfloor \frac{cnt2}{2} \rfloor + 1$ ，否则为 $0$ 。这个式子还可以进一步转换成不论 $cnt2$ 是否等于 $0$ ，答案都是 $\lfloor \frac{cnt2 + 1}{2} \rfloor$ 。

所以总答案即为 $\lfloor \frac{cnt2 + 1}{2} \rfloor + cnt1$ ， 由于$a_i \le 10^9$ ，开桶数组记录会 $TLE$ ，所以可以使用 `map` 解决。复杂度 $O(nlogn)$ 。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int,int>
#define fir first
#define sec second 
const int inf=0x3f3f3f3f3f3f3f3f;
#define ISMOD998244353
#ifdef ISMOD998244353
const int mod=998244353;
#else
const int mod=1e9+7;
#endif
void chmax(int &a,int b)
{
	a=max(a,b);
}
void chmin(int &a,int b)
{
	a=min(a,b);
}
int popcount(int x)
{
	return __builtin_popcount(x);
}
void eadd(int &a,int b)
{
	a=(a+b)%mod;
}
void esub(int &a,int b)
{
	a=((a-b)%mod+mod)%mod;
}
void emul(int &a,int b)
{
	a=(a*b)%mod;
}
int add(int a,int b)
{
	return (a+b)%mod;
}
int sub(int a,int b)
{
	return ((a-b)%mod+mod)%mod;
}
int mul(int a,int b)
{
	return (a*b)%mod;
}
const int maxn=2e3;
int jc[maxn+10],jcn[maxn+10];
int quickpow(int x,int p)
{
    int base=x;
    int ans=1;
    while(p)
    {
        if(p&1)ans=ans*base%mod;
        p>>=1;
        base=base*base%mod;
    }
    return ans%mod;
}
void init()
{
    jc[0]=jc[1]=1;
    for(int i=2;i<=maxn;i++)jc[i]=jc[i-1]*i%mod;
    jcn[maxn]=quickpow(jc[maxn],mod-2);
    for(int i=maxn-1;i>=0;i--)jcn[i]=jcn[i+1]*(i+1)%mod;
}
int C(int n,int m)
{
    if(m<0)return 0;
    if(m==0)return 1;
    if(m>n)return 0;
    return ((jc[n]*jcn[m])%mod*jcn[n-m])%mod;
}
void undir_add_edge(vector <int> g[],int u,int v)
{
	g[u].push_back(v);
	g[v].push_back(u);
}
void dir_add_edge(vector <int> g[],int u,int v)
{
	g[u].push_back(v);
}
void output_judge(bool b)
{
	cout<<(b?"yes":"no");
}
void output_Judge(bool b)
{
	cout<<(b?"Yes":"No");
}
void output_JUDGE(bool b)
{
	cout<<(b?"YES":"NO");
}
#define outlen(X) fixed<<setprecision(X)
const double precision=1e-6;
bool dequal(double a,double b)
{
	return (abs(a-b)<=precision);
}
bool dless(double a,double b)
{
	return (b-a>=precision);
}
bool dgreater(double a,double b)
{
	return (a-b>=precision);
}
#define IS_MULTI_TEST

int n,cnt1,cnt2;
map<int,int>mp;
void main_solve()
{
	mp.clear();
	cnt1=cnt2=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		mp[x]++;
	}
	for(auto it=mp.begin();it!=mp.end();it++)
	{
		int id=it->fir,x=it->sec;
		if(x>=2)cnt1++;
		else cnt2++;
	}
	cout<<cnt1+(cnt2+1)/2<<endl;	
}
signed main()
{
	#ifdef IS_MULTI_TEST
		int t;
		cin>>t;
		while(t--)main_solve();
	#else
		main_solve();
	#endif
	return 0;
}
```

---

## 作者：jockbutt (赞：5)

# 题意

定义一个数列的价值为它的最长上升子序列的项数和最长下降子序列的项数，现在让这个数列重排，使这个数列价值最大。

# 解法

首先，不难想到，这个数列的最大值肯定在中间，左右分别是一段连续上升的子序列和连续下降的子序列，其他对于答案没有贡献的就随便放。  

接着，我们研究哪些数字不会产生贡献。可以发现，对于一种相同的数字，左边放一个，右边也放一个，其他的就没有用了。意思就是说，相同的数字最多贡献两次。

于是，我们可以记录一下每个数字的出现次数，然后加上这类数字的贡献即可。注意答案要除以二。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int BUFFER_SIZE=5<<20;
char RB[BUFFER_SIZE],*RP=RB,*RT=RB;
#define getchar() RP==RT?(RT=RB+fread(RB,1,BUFFER_SIZE,stdin),RP=RB,*RP++):*RP++;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')	{x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n;
const int maxn=2e5+10;
int a[maxn];
map <int,int> mp;
int ans;
signed main(){
	int T=read();
	while(T--)
	{
		n=read(),ans=0;
		mp.clear();
		for(int i=1;i<=n;++i)
		{
			a[i]=read(),mp[a[i]]++;
			if(mp[a[i]]<=2)	ans++;
		}
		printf("%d\n",(ans+1)/2);
	}
	return 0;
}
```


---

## 作者：IceKylin (赞：3)

# CF1682C LIS or Reverse LIS? 题解
### [原题链接（in luogu）](https://www.luogu.com.cn/problem/CF1682C)
### [原题链接（in CodeForces）](https://codeforces.com/contest/1682/problem/C)
### [更好的阅读体验？](https://www.luogu.com.cn/blog/std-IK/cf1682c-ti-xie)

这是一道 **思维题**，可以通过计算 **贡献** 的方法得到正解。

题目要求重排序列 ${\{a_n\}}$ 使得 ${\min\{LIS(a),LIS(a^{'})\}}$ 最大，其实等价于要求 **最长严格上升子序列** 和 **最长严格下降子序列** 的较小值最大。

设 ${ans=\min\{LIS(a),LIS(a^{'})\}}$

那么容易想到，将最大值（最小值）排在正中间，将序列分为左右两部分
：左边包含最长严格上升（下降）子序列，右边包含最长严格下降（上升）子序列。可以证明此时的 $ans$ 是最大的。

得出这一步后，讨论每一个数对 $ans$ 的贡献。

1.  当这个数为最大值时，无论出现几次，都能同时贡献 ${LIS(a)}$ 和 ${LIS(a^{'})}$。${ans\gets ans+2}$

2.  当这个数不为最大值，只在序列中出现 **一次** 时，只能贡献 $LIS(a)$ 和 $LIS(a^{'})$ 中的一者。${ans\gets ans+1}$

3.  当这个数不为最大值，在序列中出现 **多次** 时，既可以贡献 $LIS(a)$，也可以贡献 $LIS(a^{'})$。但 **不能** 贡献超过两次，因为题目中要求 **严格** 二字。${ans\gets ans+2}$

最后 ${ans\gets ans\div 2}$（可以自己思考一下原因）。

上述过程可使用 map 模拟， **时间复杂度** 为 ${O(n\log n)}$。

小技巧：讨论中的第一点可以归入第二点，只需将最后一步修改为 ${ans\gets (ans+1)\div 2}$ 即可。

P.S. 此题多组数据，不要忘记 **多测清空**。

## AC 代码
```cpp
//By IceKylin
#include<bits/stdc++.h>
#define mii map<int,int>
using namespace std;
int t,n,ans;
mii mp;


int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		mp.clear();
		for(int i=1;i<=n;++i){
			int a;
			cin>>a;
			++mp[a];
			if(mp[a]<=2)++ans;
		}
		cout<<(ans+1)/2<<'\n';
	}
	return 0;
}
```

---

## 作者：World_Creater (赞：2)

这是一道 $1400$ 的~~诈骗~~构造题。  
首先一种很显然的直觉：将这个序列排成一个单峰序列，这样答案就是  $\Big\lceil\dfrac{len}{2}\Big\rceil$（$len$ 为这个单峰序列的长度）。  
接下来考虑相同的数字怎么处理：  
1. 如果某一个数字的出现次数只有两次，我们可以把一个放在峰的左边，另一个放在峰的右边。
2. 如果某一个数字的出现次数在两次以上，那么在保持策略 $1$ 的情况下，这个数字无论放在什么地方都不可能产生贡献。

因此：我们的策略非常简单：把某个数在数列中只保留最多 $2$ 次，多余的直接扔掉。

由于数据过大不能用桶，考虑用排序完成以上操作。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],cnt;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cnt=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++)
		{
			if(i<3||a[i]!=a[i-1]||a[i]!=a[i-2])
			cnt++;
		}
		cout<<(cnt+1)/2<<"\n";
	}
}
```

---

## 作者：lanos212 (赞：2)

结论题（?

题意就是重排一些数使从前面和后面的 $\operatorname{LIS}$ 的较小值要尽可能大。

那么肯定要让两者的公共部分尽可能多才能使答案更优。

考虑如前面已经有了一个 $\operatorname{LIS}$，从后面再插过来一个 $\operatorname{LIS}$，我们发现它们最多只能有一个公共点:

![](https://cdn.luogu.com.cn/upload/image_hosting/wdytqsu8.png)

那么我们就可以构造出这么一种方案，使前后都会有一个公共点存在:

![](https://cdn.luogu.com.cn/upload/image_hosting/lp0ci4ui.png)

也就是使这个序列先不降再不升。

那么前面这段和后面这段的每一段种不能有相同的数字，反之如果数字都不相同那就一定可以排成一个 $\operatorname{LIS}$。

考虑对于每一个数字，如果它只出现一次，那么就一定可以使用。

如果出现两次，那么可以一个放在前面的 $\operatorname{LIS}$，一个放在后面的 $\operatorname{LIS}$。

如果出现三次及以上，我们只能把剩下的扔掉了，只使用两个数。

那么为了让前后的 $\operatorname{LIS}$ 尽可能平均地长，那么就把所有可用数字前后平均地放，注意由于有一个交点在，如果可用数字有 $x$ 个，那么答案就是 $\left \lfloor \frac{x+1}{2} \right \rfloor$。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[1000001],top;
int main(){ 
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>t;
	while (t--){
		cin>>n;
		for (int i=1;i<=n;++i) cin>>a[i];
		sort(a+1,a+n+1);
		top=0; long long l=0;
		for (int i=1;i<=n;++i){
			if (a[i]!=a[i-1]){l=1; ++top;}
			else{++l; if (l<=2) ++top;}//<=2有几个用几个，>2只能用2个 
		}
		cout<<(top+1)/2<<'\n';
	}
	return 0;
}
```


---

## 作者：冰冻罗非鱼 (赞：1)

#### 题目大意：

设一个长为 $n$ 的整数序列 $a$ 是 $a_1,a_2,a_3,\dots,a_n$ ，那么 $a'$ 是 $a_n,a_{n-1},a_{n-2}, \dots ,a_1$ ，且 $\mathrm{LIS}(a)$ 是 $a$ 的最长严格递增子序列的长度。现在给定 $a$ 数组，对数组进行重排后，求 $\min ( \mathrm {LIS} (a), \mathrm {LIS} (a'))$ 的最大值。

输入 $t$ 组数据，每组数据先输入 $n$，然后输入 $n$ 个整数。输出 $t$ 行，每行一组数据的答案，按输入顺序。

---

#### 分析：

&emsp;&emsp; 其实正解是不难想到的（~~可是原题翻译错了~~）。既然可以重排，又需要使数组顺序和逆序两种情况的 $\mathrm{LIS}$ 都尽可能大，那么思路就显而易见了：把所有数中最大的数放在数列的最中间，把剩下的数分成两部分，一部分放在最中间数的左边，要求这一部分的数按大小不下降进行排列，另一部分放在右边，要求按照大小不上升进行排列，同时，让这两部分数的个数尽可能相等。

&emsp;&emsp;注意到，在整个数列中，一种数的贡献最多为 $2$，当它的个数为 $2$ 时，一个放在左边，一个放在右边，如果大于 $2$ 的话，那就无法有更多的贡献了。。因此我们需要记录每个数出现的次数，如果出现次数大于 $2$ ，就不加上它的贡献。这样，遍历整个数列，加上贡献，最后除以二即可（因为加的是两边数列所有数的贡献），考虑到数可能很大，这里用 `map` 进行优化

&emsp;&emsp;然而这里有个特例，对于最中间的那一个数，它的贡献始终为 $2$，因为左边的最长上升序列的终点是它，右边的最长下降序列的起点也是它，特殊处理即可。

```cpp
//2022/7/12 
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10000;
int t,n;
map<int,int> a;
int main(){
	cin >> t;
	while(t--){
		cin >> n;
		int ans = 0,b;
		a.clear();
		for(int i = 1; i <= n ; i++){
			cin >> b; // 一边输入，一边处理 
			a[b]++;
			if(a.find(b) == a.end() || (a.find(b) != a.end() && a[b] <= 2))ans++; // 如果该数出现次数小于二，加上该数的贡献，并把出现次数加一 
		}
		cout << (ans + 1) / 2 << "\n"; // 处理最中间的数这一特殊情况 ，记得除以2哦 
	}
} 
```



---

## 作者：jucason_xu (赞：1)

很明显，将序列反转后的 $\mathrm{LIS}$ 就是 $\mathrm{LDS}$（Longest Decrease Subsequence）。

那么求最大可能的 $\min(|\mathrm{LIS}|,|\mathrm{LDS}|)$。

我们用 map 统计每个数出现的次数。然后遍历 map，分情况讨论。

+ 如果这个数出现大于1次，它可以在 $\mathrm{LIS}$ 和 $\mathrm{LDS}$ 中各贡献一次。

+ 如果这个数出现次数等于1，它可以在 $\mathrm{LIS}$ 和 $\mathrm{LDS}$ 中选择一个贡献一次。

并且，$\mathrm{LIS}$ 和 $\mathrm{LDS}$ 中可能会有公共的点，并且 **由于一个单调升，一个单调降，公共点最多只有一个** 。如果我们把某一个出现次数等于 $1$ 的数安排为交点，它就可以贡献两次。如果交点出现次数大于 $1$ 呢？那么这个数已经在两个序列中各贡献一次，再安排为交点就没有新的贡献。

所以，我们只需要按上述分配，然后把剩余出现次数为1的平均分配给 $\mathrm{LIS}$ 和 $\mathrm{LDS}$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
int n,a[200005];
void solve(){
	map<int,int>mp;
	int a1=0,a2=0,ans=0;
	cin>>n;
	rep(i,1,n)cin>>a[i];
	rep(i,1,n){
		if(mp[a[i]]>1)continue;
		else if(mp[a[i]]==1)a2++;
		else a1++;
		mp[a[i]]++;
	}
	if(a1>a2)a1--,ans++;
	ans+=(a1+a2)/2;
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	rep(i,1,t)solve(); 
	return 0;
}
```


---

## 作者：Tetrahydrofunina (赞：1)

这个序列能构成的最好的情况，就是一个单峰序列，峰在中间（这样的话，两边的的单调序列长度相等，取最小值也最大）。但是，这道题要求必须**严格单调**，也就是说，如果有相同元素，是不会算入长度的。因此，我们要考虑每个点对答案的**贡献**。对于不同出现次数的数，对答案的贡献是不同的。
+ 出现 $1$ 次：因为要使两边长度平衡，所以只有出现了两个出现1次的数，才能使答案 $+1$（安排在两边，两边都 $+1$，取最小值，也$+1$），所以对答案的贡献是 $\frac{1}{2}$。
+ 出现 $≥2$ 次：可以直接把两个安排在两边使答案 $+1$，并且因为不算相等的，所以剩下的都没用。综上，这种数对答案的贡献是 $1$。

代码自己打吧，用 `map`。

---

## 作者：t162 (赞：0)

先把问题转化成求一个序列，是原序列的重新排列，使得 最长上升子序列 长度和 最长下降子序列 长度的最小值最大。

假设序列中出现恰好一次的元素种数是 $x$，出现至少两次的元素种数是 $y$。

首先有答案的一个上界：

- 若 $x\neq 0$，答案上界是 $\left\lfloor\frac{x-1}{2}\right\rfloor+y+1$；
- 否则，答案上界是 $y$。

一个基本事实是，对于每种不同的元素，在 最长上升子序列 和 最长下降子序列 中各最多贡献 $1$ 的长度。

那么对于 $x=0$ 的情况，答案至多为 $y$；

对于 $x\neq 0$ 的情况，先假设 最长上升子序列 和 最长下降子序列 相交于一个出现次数为奇数的元素，其余的出现次数为奇数的元素最多在一个子序列中有 $1$ 的贡献，而出现次数为偶数的元素在两个子序列中都可以有 $1$ 的贡献，取个 $\min$ 就有上界 $\left\lfloor\frac{x-1}{2}\right\rfloor+y+1$。

构造也非常显然，这里就不再赘述了。

```cpp
// e3c8f1a924 2022年05月22日 星期日 22时57分58秒
#include<cstdio>
#include<map>
std::map<int, int> v;
int n, a[200005];
int main() {
	int t; scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i), v[a[i]]++;
		int once = 0, twice = 0;
		for (int i = 1; i <= n; i++) {
			if (!v[a[i]]) continue;
			if (v[a[i]] == 1) once++;
			else twice++;
			v[a[i]] = 0;
		}
		if (once) {
			printf("%d\n", 1 + (once - 1) / 2 + twice);
		} else printf("%d\n", twice);
	}
}
```

---

## 作者：Unnamed114514 (赞：0)

### 题意
对于一个数组 $a$，将其重组得到新的数组 $b$，将 $b$ 翻转得到 $c$，求 $\min(\operatorname{LIS}(b),\operatorname{LIS}(c))$。
### 思路
对于出现过两次及以上的数字（数量：$sum$）一边一个，出现过一次的字符（数量：$sum1$）一边一个，中间再放一个。答案就是 $sum+\dfrac{sum1+1}{2}$。

统计出现次数可以排序解决，时间复杂度 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int T,n,a[maxn];
inline int read(){
	int res=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		f|=(ch=='-');
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return f?-res:res;
}
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;++i)
			a[i]=read();
		int sum=0,sum1=0;
		sort(a+1,a+n+1);
		for(int i=1;i<=n;++i)
			if(a[i]!=a[i-1]){
				if(a[i]!=a[i+1])
					++sum1;
				else
					++sum;
			}
		printf("%d\n",sum+(sum1+1)/2);
	}
	return 0;
}
```

---

