# 「SWTR-6」GCDs & LCMs

## 题目描述

小 A 有一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$。

他想从这些数中选出一些数 $b_1,b_2,\cdots,b_k$ 满足：对于所有 $i\ (1\leq i\leq k)$，$b_i$ 要么是序列 $b$ 中的最大值，要么存在一个位置 $j$ 使得 $b_j>b_i$ 且 $b_i+b_j+\gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)$。

- 如果你不知道 $\gcd$ 和 $\mathrm{lcm}$ 是什么，可以点击最底部的「帮助/提示」部分的链接。

小 A 想让选出的数之和尽量大。请求出这个最大值。

## 说明/提示

**「样例 1 说明」**

可以选择 $b=\{2,3\}$，因为 $2+3+\gcd(2,3)=\mathrm{lcm}(2,3)$。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n\leq2$；
- Subtask 2（20 points）：$n\leq 17$；
- Subtask 3（15 points）：$a_i\leq 2\times 10^3$；
- Subtask 4（15 points）：$n\leq 2\times 10^3$；
- Subtask 5（10 points）：$n\leq 5\times 10^4$；
- Subtask 6（10 points）：$a_i\leq 10^7$；
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^5$，$1\leq a_i\leq 10^9$。

**「帮助/提示」**

$\gcd$ 表示[最大公约数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fr=aladdin)，$\mathrm{lcm}$ 表示[最小公倍数](https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B0/6192375?fr=aladdin)。

**「来源」**

[【LGR-075】洛谷 8 月月赛 II Div.2 & SWTR-06 & EZEC Round 3](https://www.luogu.com.cn/contest/33190)。

idea & solution & data by [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
4
4 3 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
10
6 7 18 4 17 10 9 1 3 8```

### 输出

```
19```

## 样例 #3

### 输入

```
3
123456789 234567890 123456789```

### 输出

```
246913578```

# 题解

## 作者：Alex_Wei (赞：56)

因为是简单题所以放一下官方题解吧。

> [题面传送门](https://www.luogu.com.cn/problem/P6786)。

> 题意简述：从给定序列 $a$ 中选出一个子序列满足：对于所有不为最大值的 $b_i$，总有 $b_j$ 使得 $b_i+b_j+\gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)$。求子序列所有数之和的最大值。

---

Subtask 1：$n\leq2$。

傻子都会做的部分分。

Subtask 2：$n\leq 17$。

枚举 $a$ 的所有子集并判断是否合法。可以预处理出所有合法对 $(i,j)$ 满足 $a_i+a_j+\gcd(a_i,a_j)=\mathrm{lcm}(a_i,a_j)$。时间复杂度为 $O(2^nn^2)$。如果不预处理时间复杂度为 $O(2^nn^2\log a_i)$，较难通过。

Subtask 4：$n\leq 3\times 10^3$。

枚举所有 $i,j$ 使得 $i<j$ 且 $a_i+a_j+\gcd(a_i,a_j)=\mathrm{lcm}(a_i,a_j)$，将所有这样的 $i,j$ 之间连一条边，最后求出连通块里所有点的权值之和的最大值即可。时间复杂度 $O(n^2\log a_i)$。

Subtask 3：$a_i\leq 3\times 10^3$。

类似 Subtask 4 枚举权值，时间复杂度 $O(\log a_i\max a_i^2)$。

---

#### 结论 1：

对于任意 $x,y$ 满足 $x+y+\gcd(x,y)=\mathrm{lcm}(x,y)$，总有 $x=\frac{2}{3}y$ 或 $y=\frac{2}{3}x$。

#### 证明 1：

不妨设 $x\leq y$。当 $x=y$ 时，原式不成立，所以 $x<y$。

因为 $x<y$，$\gcd(x,y)<y$，所以 $x+y+\gcd(x,y)<3y$。

又因为 $x+y+\gcd(x,y)>y$ 且 $\mathrm{lcm}(x,y)$ 是 $y$ 的整数倍，所以 $x+y+\gcd(x,y)=2y$，即 $\mathrm{lcm}(x,y)=2y$。

因为 $x\times y=\gcd(x,y)\times \mathrm{lcm}(x,y)$，所以 $x\times y=2y\times \gcd(x,y)$，得到 $\gcd(x,y)=\frac{x}{2}$。

带回原式得到 $x+y+\frac{x}{2}=2y$，解得 $x=\frac{2}{3}y$ 或者 $y=\frac{3}{2}x$。

#### 推论 1.1

根据结论 1，对于每个**偶数** $x$，满足 $x+y+\gcd(x,y)=\mathrm{lcm}(x,y)$ 且大于 $x$ 的 $y$ 有且只有一个，即 $y=\frac{3}{2}x$。**而奇数则不存在这样的 $y$。**

根据上面的结论，我们很容易得出，如果将选出来的数从小到大排序，去重，一定满足 $b_i=\frac{2}{3}b_{i+1}\ (1\leq i<k)$。

---

Subtask 7：无特殊限制。

因此，$O(n)$ 枚举最小值就能确定整个序列 $b$，二分或用 map 实现在 $O(\log a_i)\ /\ O(\log n)$ 的时间内查找一个数在序列 $a$ 中的出现次数，并且记录一个数是否被计算过。

每个数最多只会被计算一次，总时间复杂度：二分 $O(n\log a_i)$，map $O(n\log n)$，不过 map 常数更大一点。

值得注意的是，如果不判断一个数是否被计算过，那么时间复杂度可能会退化成 $O(n\log n\log a_i)$，只能通过 Subtask 5。

Subtask 6 是给不会二分或 map 的参赛者准备的部分分（不过可能没多大必要）。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N=3e5+5;

map <int,int> mp;
int n,a[N]; ll ans;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],mp[a[i]]++;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		ll tmp=a[i],cnt=0;
		while(mp[tmp]){
			cnt+=tmp*mp[tmp],mp[tmp]=0;
			if(tmp%2==0)tmp=tmp/2*3;
			else break;
		}
		ans=max(ans,cnt);
	} cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Alarm5854 (赞：8)

这道题目是一道非常不错的题目，做法也不难想到，我就来讲解一下各个部分分怎么得，其实也是我在比赛时的经历以及赛后的总结，本篇题解的代码在结尾。

--------

### $25$ 分做法（子任务 $1,2$）：  

观察到 $n \le 17$，所以可以枚举选哪些数，选完以后判断一下选到的数列是否合法，时间复杂度为 $O(n^22^n)$。

--------

### $55$ 分做法（子任务 $1,2,3,4$）：

发现条件 $b_i<b_j$ 且 $b_i+b_j+\gcd(b_i,b_j)=\text{lcm}(b_i,b_j)$，在比赛的时候我就想到了图论，对于 $a$ 数组，先去重与离散化，统计 $a$ 数组每个数出现的次数（用另一个数组备份 $a$ 数组，$a_i$ 出现的次数记为 $cnt_i$），接着两重循环枚举 $i,j$，如果满足 $a_i<a_j$ 且 $a_i+a_j+\gcd(a_i,a_j)=\text{lcm}(a_i,a_j)$，就由 $i$ 号节点向 $j$ 号节点连边，并将 $j$ 号节点的入度加一。做完以后先给 $f$ 数组赋初值，$f_i$ 表示以 $a_i$ 结尾的最大数列之和，$f_i=a_i \times cnt_i$。然后做一个拓扑排序，对于节点 $v$，则 $f_v=\max(f_u)+a_i \times cnt_i$，其中 $u$ 为连向 $v$ 的节点，时间复杂度为 $O(n^2)$，但子任务 $3$ 由于 $a_i \le 2 \times 10^3$，去重后不同的 $a_i$ 的数量也会小于 $2 \times 10^3$，所以也是可过的。

--------

### $100$ 分做法（赛时）：

$55$ 分做法的改进，设 $x=ak,y=bk$，则 $\gcd(x,y)=k,\text{lcm}(x,y)=abk$，若 $x+y+\gcd(x,y)=\text{lcm}(x,y)$，则有 $ak+bk+k=abk$，由于 $k \neq 0$，所以 $1+a+b=ab$，设 $a<b$，则唯一的整数解为 $a=2,b=3$。所以只需枚举 $i$，找 $a_i$ 的 $1.5$ 倍，这个可以用 `lower_bound` 来找，如果存在，设其为 $a_j$，就由 $i$ 号节点向 $j$ 号节点连边，接下来的做法就同 $55$ 分做法了，时间复杂度为 $O(n \log n)$。

--------

### $100$ 分做法（赛后）：

可以发现，一个状态只由上一个状态得来，所以在去重、离散化、统计操作之后，可以枚举 $i$，先将 $f_i$ 赋值为 $a_i \times cnt_i$，找 $a_i$ 的 $2/3$，如果存在，设其为 $a_j$，则 $f_i$ 还要额外加上 $f_j$，代码复杂度可以降低，时间复杂度仍为 $O(n \log n)$。

--------

如果不太会实现的话，可以看代码，别忘记开 LL，[代码在此](https://www.luogu.com.cn/paste/56us13yw)，有注释，请大家做好学术诚信，抵制抄题解行为。


---

## 作者：Konnyaku_LXZ (赞：6)

我们从这个式子进行突破：

$x+y+gcd(x,y)=lcm(x,y)$。

不妨令 $x \le y$。

令 $t=gcd(x,y)$;

令 $u=x/t,v=y/t$，则 $x = u \times t,y = v \times t$。

则原式变为：

$x+y+gcd(x,y)=x \times y / gcd(x,y)$。

将 $x,y$ 换成 $u,v,t$ ，得：

$u \times t + v \times t + t=u \times t \times v \times t / t$。

$t \times (u+v+1) = u \times v \times t$。

$u + v + 1 = u \times v$。

$(u-1) \times v = u + 1$。

$v = \frac{u+1}{u-1}$。

因为 $u,v$ 都是质数，所以 $u \ge 2$ ， $v \ge 2$。

$\frac{u+1}{u-1} \ge 2$。

$u+1 \ge 2u-2$。

$u \le 3$。

所以 $2 \le u \le 3$。

所以 $u=2,v=3 $ 或 $u=3,v=2$。

因为 $x \le y$，所以 $u \le v$ 。

所以 $u=2,v=3$。

**结论：若 $x,y$ $(x \le y)$ 满足 $x+y+gcd(x,y)=lcm(x,y) $，当且仅当** $x:y=2:3$。

有了这个结论以后，题目就变得十分容易了。

我们先将 $a$ 数组排序，然后把里面相同的元素合并，记录它们的值和出现次数。

设 $f_i$ 表示第 $i$ 个元素的答案。

则有初始值 $f_i=x_i*t_i$ （其中 $x_i$ 表示第 $i$ 个元素的值， $t_i$ 表示它在 $a$ 数组中的出现次数。

然后我们从左到右遍历一遍 $b$ 数组，对于当前第 $i$ 个元素，我们二分找到 $b$ 数组中等于它的 $2/3$ 的元素（没找到就continue掉），设该元素的下标为 $x$，则 $f_i+=f_x$，$f$ 的最大值即为答案。

Code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
#include<stack>
using namespace std;

const int MAXN=5e5+50;
typedef long long LL;

LL N,a[MAXN],x[MAXN],t[MAXN],f[MAXN],cnt=0,Ans=0;

void Init(){
	scanf("%lld",&N);
	for(int i=1;i<=N;++i) scanf("%lld",&a[i]);
	sort(a+1,a+1+N);//先排序 
	for(int i=1;i<=N;++i){//保存元素值和出现次数 
		if(a[i]==a[i-1]) ++t[cnt];
		else x[++cnt]=a[i],t[cnt]=1;
	}
	for(int i=1;i<=cnt;++i) f[i]=x[i]*t[i],Ans=max(Ans,f[i]);//计算f数组的初始值并更新最大值 
}

void Solve(){
	for(int i=2;i<=cnt;++i){
		if(x[i]%3!=0) continue;//如果不能整除三的话直接跳过 
		LL val=x[i]/3*2;
		LL pos=lower_bound(x+1,x+i,val)-x;//二分 
		if(pos>=i||pos<1||val!=x[pos]) continue;
		f[i]+=f[pos];//更新f值 
		Ans=max(Ans,f[i]);//取最大值 
	}
}

void Print(){
	cout<<Ans<<endl;
}

int main()
{
	Init();
	Solve();
	Print(); 
	return 0;
}
```

---

## 作者：Rubidium_Chloride (赞：3)

8月月赛II C题题解

## 0.前言

[$\color{Red}{\text{在}}\color{orange}\text{博}\color{yellow}\color{green}\text{客}\color{Turquoise}\text{里}\color{blue}\text{看}\color{purple}\color{Red}\text{效}\color{orange}\text{果}\color{yellow}\text{更}\color{green}\text{好}\color{Turquoise}\text{哦}\color{blue}!$](https://www.luogu.com.cn/blog/Rolling-blog1424/solution-p6786)

## 1.题目大意

- 给定 $n$ 和 $n$ 个整数 $a_1,a_2\dots a_{n-1},a_n$，从中选出 $k$ 个整数 $b_1,b_2\dots b_{k-1},b_k$，使得对于每个 $b_i,i=1,2\dots k-1,k$，要么 $b_i=\max\left( b_1,b_2\dots b_{k-1},b_k\right)$，要么存在一个 $j$ 使 $b_j>b_i$，且 $b_i+b_j+\gcd(b_i,b_j)=\operatorname{lcm}(b_i,b_j)$。求 $\sum\limits^{k}_{i=1} b_i$ 的最大值；

- $1\le n\le 3\times 10^5,1\le a_i \le 10^9$。

## 2.分析解法

一看题面，哇，$\gcd$，再一看，哇，$\operatorname{lcm}$，此时作者就意识到了，这可能是一道数学题。

作者先试了一下两边同时乘以 $\gcd(b_i,b_j)$（因为 $\operatorname{lcm}(c,d)\times \gcd(c,d)=c\times d$），然后发现不行。

然后作者发现，两边同时除以 $\gcd(b_i,b_j)$ 是可行的，并且能够得到一个对解题非常有帮助的式子，下面给大家证明一下。

PS：和题目中一样，这里设 $b_i<b_j$。

原来的式子：$b_i+b_j+\gcd(b_i,b_j)=\operatorname{lcm}(b_i,b_j)$

两边同时除以 $\gcd(b_i,b_j)$，设 $b_i=k\times \gcd(b_i,b_j),b_j=l\times \gcd(b_i,b_j)$，则 $\operatorname{lcm}(b_i,b_j)=k\times l\times \gcd(b_i,b_j)$，且 $k<l,k>0,l>0$；

得到：$k+l+1=k\times l$；

移项，做一些处理：$k\times l-k-l+1=2$；

左边因式分解：$(k-1)\times (l-1)=2$；

$\because k<l,k>0,l>0$

$\therefore k-1=1,l-1=2$

$\therefore k=2,l=3$

$\therefore \dfrac{b_i}{b_j}=\dfrac{2}{3}$

所以我们得到了一个惊人的式子：对于任意的序列 $b$，里面要么只有一个数值的元素，要么必定有一个数，和他形成 $2:3$ 的关系。

所以除去重复的数字，$b$ 序列就是一个等比数列。

先把原数组排一个序，接下来我们依次考虑每一个数，如果它在之前的等比序列中已经出现过，那么就不用再次计算（因为必定不会更优），如果它不是2的倍数，那么也不用计算。否则就计算从它开始的，公比为 $\dfrac{3}{2}$ 的等比数列，知道 $a$ 数列中不包含项为止。

如何判断包含？可以利用 $\operatorname{lowerbound}$ 和 $\operatorname{upperbound}$ 来判断。

那么如何考虑重复数字呢？在排完序以后，可以用 $s_i$ 表示值与 $a_i$ 相同的所有数的和。然后在统计答案的时候直接加上 $s_i$ 就可以了。

其他更详细的解释请见代码，总时间复杂度是 $O(n\log n)$。

## 3.CODE

介于本题比较麻烦，还是贴一下代码吧。

```cpp
#include<bits/stdc++.h>
#define N 300009 
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
inline ll read() {
    ll x=0,f=1;int c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
ll n,a[N],ans,sm[N];bool vst[N];
ll exist(ll x){//判断是否存在
	ll v;
	if((v=(lower_bound(a+1,a+n+1,x)-a))!=(upper_bound(a+1,a+n+1,x)-a)) return v;
	return 0;
}
void solve(ll i){
	ll sum=0,tmp=a[i];
	ll v;
	while(exist(tmp)){
		v=exist(tmp);//如果存在，找到它第一次出现的位置
		sum+=sm[v],vst[v]=1;//把所有的值为tmp的全部加上
		if(tmp%2!=0) break;
		tmp=tmp/2*3;//下一个数
		if(tmp>a[n]) break;//如果不可能存在，跳出循环
	}
	ans=max(ans,sum);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1,t,s;i<=n;i++){
		if(a[i]!=a[i-1]){ans=max(ans,(ll)s*a[t]),sm[t]=s*a[t];s=1,t=i;}//别忘了更新只有1种值的情况
		else s++,vst[i]=1;//为防止重复计算，把重复的数字只统计一遍
		if(i==n) sm[t]=s*a[t],ans=max(ans,(ll)s*a[t]);//sm就是上文提到过的s数组
	}
	for(int i=1;i<=n;i++){
		if(!vst[i]&&a[i]%2==0) solve(i);//如果没有算过而且该数能被2整除，再算一次
	}
	printf("%lld",ans);
	return 0;
}

```



## 4.后记

祝大家AC本题，也祝洛谷月赛能够办的越来越好！

---

## 作者：lndjy (赞：3)

首先，我们可以打一个暴力，就是枚举每个位置作为最后一个，然后匹配。这样是 $n^2$ 的，只有25分。

然后看到了数据范围，容易想到只有当一个条件满足时，这个式子才能成立。

这个条件不会推，这时就可以打表找规律。

看这个暴力代码，所有选中的数，都放在 `vector` 里，所以我们可以把 `vector` 输出出来，看看结果。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
int inline read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*f;
}
const int N=1e6+5,maxx=1e6;
int a[N],n;
int gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	a[i]=read();
	int ans=0;
	sort(a+1,a+n+1);
	vector<int> v;
	for(int x=1;x<=n;x++)
	{
	int sum=0;
	v.clear();
	for(int i=x;i>=1;i--)
	{
		if(i==x||(!v.empty()&&a[i]==v[0]))
		{
			sum+=a[i];
			v.push_back(a[i]);
		}
		else
		for(int j=0;j<v.size();j++)
		{
			if(v[j]+a[i]+gcd(v[j],a[i])==(v[j]*a[i]/gcd(v[j],a[i])))
			{
				sum+=a[i];
				v.push_back(a[i]);
				break;
			}
		}
	}
	ans=max(ans,sum);
	cout<<sum<<" ";
	for(int j=0;j<v.size();j++)
	cout<<v[j]<<" ";
	cout<<endl;
	}
	return 0;
}
```
这是样例的结果，第一个数为和，接下来是选择的数。

```
1 1
3 3
4 4
10 6 4
7 7
8 8
19 9 6 4
10 10
17 17
18 18
```

观察到**选择的数都为上一个数的三分之二**，比如 `9 6 4`。

如果对这个规律不放心，可以自己造一个 $1-20$ 的：

```cpp
20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
```

然后输出出来的是这样的，同样满足选择的数都为上一个数的三分之二。

```cpp
1 1
2 2
5 3 2
4 4
5 5
10 6 4
7 7
8 8
19 9 6 4
10 10
11 11
20 12 8
13 13
14 14
25 15 10
16 16
17 17
38 18 12 8
19 19
20 20
```

然后确定了结论，就可以写出正解了，用 `map` 记录一下就可以了。

```cpp
#define int long long
using namespace std;
int inline read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*f;
}
const int N=1e6+5,maxx=1e6;
int a[N],n;
int gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
map<int,int> m;
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	a[i]=read();
	long long ans=0;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		long long sum=0;
		m[a[i]]++;
		while(1)
		{
			if(m[a[i]])
			sum+=m[a[i]]*a[i];
			else break;
			if(a[i]%3!=0) break;
			a[i]=a[i]/3*2;
		}
		ans=max(ans,sum);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：SymphonyOfEuler (赞：3)

题目意思是从一些数中选出一些 $b$，使得他们的和最大，满足要么是最大的数，要么有个 $j$ 满足 $b_j $ 大于 $b_j $ & $b_i+b_j+gcd(b_i,b_j)=lcm(b_i,b_j)$。

**5pts 方法（非正解）：**

说了n<=2，所以集合里最多有两个数字，所以根据两个条件来得到结果就行。

很明显，但是建议追求正解的大佬不看/kk

**100pts 方法：**

需要经过一些推柿子，但是我觉得书虫的柿子很好了，所以主要是提供代码思路和代码。

使用map大法，输入进来的元素做一个记号，输入完把数组排序一遍，枚举i得到 $map[a_i]$ 有记号的时候，一个数字对于有多少个 $a_i$ 加上，然后把 $map[a_i]$ 清零。这个之后，得到 $a_i$ 能被2整除的话，$a_i=\frac{1}{2}a_i\times3$。否则break。存一个答案，每次和每次枚举 $i$ 得到的另一个结果取max值，最后这个就是答案。

这道题的精髓是用STL里的map来作记号，由于有可能还有其他的做法，我贴一下代码：

```
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 500005;

map<ll, ll> cnt; //map

ll n, a[MAXN];

int main() {
    cin >> n;
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
        ++cnt[a[i]];//作记号
    }
    sort(a, a + n + 1);//排序
    ll maxn = -0x3f3f3f3f;
    for (ll i = 1; i <= n; ++i) {
        ll sum = 0;
        while (cnt[a[i]] != 0) {
            sum += a[i] * cnt[a[i]];
            cnt[a[i]] = 0;
            if (a[i] % 2 == 0) {
                a[i] = a[i] / 2 * 3;
            } else break;
        }
        maxn = max(maxn, sum);
    }
    cout << maxn << '\n';
    return 0;
}
```



---

## 作者：pomelo_nene (赞：2)

结论：若 $b_i+b_j +\gcd(b_i,b_j)=\operatorname{lcm}(b_i,b_j)$ 且 $b_j > b_i$，满足 $\dfrac{b_j}{b_i}=\dfrac{3}{2}$。

充分性证明：

令 $b_i = 2 x,b_j=3x$，带入显然成立。

必要性证明：

令 $\gcd(b_i,b_j)=x$，可以改写为 $b_i=px,b_j=qx$ 并且 $\gcd(p,q)=1$。带入原式可得：$px+qx+x=pqx$，即解方程 $p+q+1=pq$，其中 $\gcd(p,q)=1,p<q$。

发现 $p=2,q=2$ 不成立而 $p=2,q=3$ 成立。当 $p,q \in \operatorname{Prime}$ 并且 $p>2,q>3$ 时，发现不存在 $p+q+1 \geq pq$，因此没有更大的解。

结论证明，于是就可以得到代码了吧。用一个桶把它装下来（可以用 `map`，也可以离散化）。首先处理只有一种数的情况，然后再对于每个数搜索，如果当前数 $s$ 不存在，返回；是 $2$ 的倍数，则继续搜索 $\dfrac{3s}{2}$。

因为每次我们都要缩掉一个 $2$，一次递归搜索时间复杂度看情况写成 $O(\log a_i)$ 或者是 $O(\log n \log a_i)$。这份代码的时间复杂度是 $O(n \log n \log a_i)$。常数很大。

```cpp
#include<bits/stdc++.h> 
using namespace std;
typedef long long LL;
map<LL,bool> used;
map<LL,LL> maplive;
map<LL,LL>::iterator it;
LL n,a[300005],ans,tmp;
void dfs(LL now)
{
//	printf("%d\n",now);
	if(maplive.find(now)==maplive.end())	return ;
	tmp+=maplive[now]*now;
	if(now%2==0)	dfs(now/2*3);
}
int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;++i)
	{
		scanf("%lld",&a[i]);
		++maplive[a[i]];
	}
	for(it=maplive.begin();it!=maplive.end();++it)
	{
		pair<LL,LL> s=*it;
		ans=max(ans,s.first*s.second);
	}
	for(it=maplive.begin();it!=maplive.end();++it)
	{
		pair<LL,LL> s=*it;
		if(used[s.first])	continue;
//		puts("------");
		tmp=0;
		dfs(s.first);
		ans=max(ans,tmp);
	}
	printf("%lld",ans);
	return 0;
}
```

$ \ $

---

## 作者：wuyonghuming (赞：2)

### 技巧：
我们如何判断两个数能不通过其他的数在同一个序列？题目要求的是：

$$x+y+\gcd(x,y)=\mathrm{lcm}(x,y)$$

但是这样判断严重影响复杂的效率，要对这些数两个两个判断，时间一定来不及。我们需要更快速的判断方法。我们发现样例中的  $2$ 和  $3$， $4$ 和  $6$， $6$ 和  $9$ 符合条件。而且后者都是前者的  $1.5$ 倍。那么是否一个数是另一个数的  $1.5$ 就可以使两个数在同一个序列？
是的，而且这是唯一不通过其他数来是两个数在同一个序列的方法。下面给出证明：

假设我们设前面的那个数是  $x$ 后面的数就是  $1.5x$，前面的数要比后面的数来得大。我们知道一个偶数的最大约数除了它自己之外一定是这个偶数除以  $2$ 的值，我们也知道，一个偶数的最小公倍数是这两个数乘积除以它们最大公约数的值，既然后面这个数是  $1.5x$ 那么它一定有  $x\div2$ 这个因子，那么它们的最小公倍数就是  $1.5x\times x \div0.5x=3x$， $3x=1.5x+x+0.5x$， $x$ 和  $1.5x$ 可以不通过其他数在一个序列。

那为什么其他倍数不可以呢？因为超过  $1.5x$ 后除了  $x$ 的倍数就不会有比  $0.5x$ 更大的公约数。那么它们的最小公倍数就一定是更大的数，只有可能  $y$ 是  $x$ 的倍数，假设后面那个数是  $y$，则最大公约数为  $x$ 最小公倍数为  $y$，则  $x+y+x=y$ 明显不成立，另外如果两个数的公约数越小形成的公倍数就会越大，超过  $1.5x$ 的数肯定就不能和它不通过其他数在同一个序列了。

那如果  $x\le y<1.5x$，时是不是也不可以不通过其他的数使得这两个数在同一序列呢?是的。这个数除了  $0.5x$ 最大的约数也只有可能是  $\tfrac{1}{3}x$ ，那么  $1\tfrac{1}{3}x$ 和  $x$ 的最大公约数是  $\tfrac{1}{3}x$ ，最小公倍数就是  $1\tfrac{1}{3}x\times x\div\tfrac{1}{3}x=4x$， $1\tfrac{1}{3}x+x+\tfrac{1}{3}x=4x$，这个等式明显不成立，但是最小公倍数会随着最大公约数的缩小而扩大，所以  $x\le y<1.5x$ 没有成立的 $y$。

通过上面的证明，我们得到了当  $y=1.5x$ 时  $x+y+\gcd(x,y)=\mathrm{lcm}(x,y)$ 成立。
### 思路：
既然已经推出式子，我们就可以计算了，我们可以通过一个  $map$ 来记录每个数有几个，然后从每个数出发，如果这个数乘以  $1.5$ 依旧是整数，就继续，说明这些数是一个序列的，最后把它们都加起来，更新最大值。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
map<long long,long long> m;
long long ans,s,p,n,a[300001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		m[a[i]]++;//这个数的个数加一
	}
	for(int i=1;i<=n;i++)
	{
		s=a[i],p=m[s]*s;//赋初始值，当前应该等于第一项
		while(m[s]&&s%2==0)//如果这个数的个数等于零就不能继续就算下面还有它的1.5被也不能连接了，如果这个数是奇数，它乘以1.5就不是整数了
		{
			s*=1.5;//往下走
			p+=m[s]*s;//加上下一项的值
		}
		ans=max(ans,p);
	}
	cout<<ans;
	return 0;
}
```
注意根据数据范围选择合适的变量类型。

谢谢管理审核，大家观赏。

---

## 作者：InformationEntropy (赞：2)

本题是一道数学题，推柿子即可。

下面本蒟蒻推导的过程。

我们设有满足条件的两个数 $x,y(x<y)$，$\gcd(x,y)=c$。

令 $a=\dfrac{x}{c},b=\dfrac{y}{c}$，可以确定 $a<b$，则：

 $$ac+bc+c=abc$$
   
 $$\because c\not=0$$
   
 $$\therefore a+b+1=ab$$
   
 $$\because a<b$$
   
 $$\therefore 2b+1>ab$$

 $$\because b\not=0,1\le a<b$$
   
 $$\therefore 2+\dfrac{1}{b}>a ,2<2+\dfrac{1}{b}<3$$
   
 $$\therefore 1\le a<3$$
   
我们将 $a=1$ 代入 $a+b+1=ab$ 中得 $b+2=b$，方程无解，所以 $a\not=1$。则 $a$ 只能为 2，此时  $b=3$。

得出结论：对于所有的 $x$ 和 $y$（$1< x< y$），若满足 $x+y+\gcd(x,y)= \operatorname{lcm}(x,y)$，则 $\dfrac{x}{y}=\dfrac{2}{3}$。

同样，对于一个合法升序序列 $b$，满足除最后一个数外，均有 $\dfrac{b_i}{b_{i+1}}=\dfrac{2}{3}$。

接下来思路就很清晰了。我们枚举合法序列的最小数，就可以确定整个序列。当遇到奇数，或它的下一个数不在输入序列中时，说明它后面肯定没数了，就更新答案，并枚举下一个序列。

PS：

- 每遇到一个数都要标记，表示它用过了。因为我们是用最小数确定一个序列，当序列后面的一个数先前统计过了，再从它开始统计，那么得到的序列只可能是它所在的合法序列的子序列，浪费了时间。

- 同一个数可能出现许多次，我们需要把相同的数都加入它所在的序列里。

由于本题 $a_i\leq 10^9$，不能直接用数组记录每个数出现的次数，所以这里提供两种解决方法：二分查找和 map 映射。

map 就不必说了，它相当于一个下标为任何类型的数组。但由于它的调用次数比较多，加上常数比较大，所以较慢（但可通过本题）。

二分的思路就是把所有数的值和出现次数存在一个结构体数组中，然后每次只需查找一次当前数在结构体数组中的下标即可，不必重复查找，因此比 map 要快很多。

map 代码（1.18s）

```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
#define max(a, b) (a>b)?a:b;
using namespace std;
typedef long long ll;
inline void read(int &x)//快读
{
    x=0;
    int f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        {
            f=-1;
        }
        ch=getchar();
     }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x*=f;
}
map<int, int>ma;//两个int分别为数值和出现次数
int a[1000001];
int main()
{
    int n;
    read(n);
    for(int i=1; i<=n; i++)
    {
        read(a[i]);
        if(!ma.count(a[i])){
            ma[a[i]]=1;
        }else{
            ma[a[i]]++;
        }
     }
     sort(a+1, a+n+1);//排序，从小到大枚举
     ll ans=0;
     for(int i=1; i<=n; i++)
     {
         ll t=a[i];
         ll sum=0;
         while(ma[t])//在原序列内则继续
         {
             sum+=t*ma[t];
             ma[t]=0;//用过了就归零
             if(t%2==0) t=t/2*3;
             else break;//为奇数，终止
          }
          ans=max(ans, sum);
      }
      cout << ans;
      return 0;
}
```
二分代码（170ms，比 map 快几倍）

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define max(a, b) (a>b)?a:b;
using namespace std;
typedef long long ll;
inline void read(int &x)
{
    x=0;
    int f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        {
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x*=f;
}
int a[1000001];
struct node{
    int x, times;
}s[1000001];//用结构体存储每个数出现的次数，每次查询一个数复杂度为O(log2cnt)
int cnt;
int find(int n)//手写二分
{
    int l=1, r=cnt;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(s[mid].x==n) return mid;
        else if(s[mid].x<n) l=mid+1;
        else r=mid-1;
    }
    return -1;//如果不在输入序列中则返回-1
}
int main()
{
    int n;
    read(n);
    for(int i=1; i<=n; i++)
    {
        read(a[i]);
    }
    sort(a+1, a+n+1);
    for(int i=1; i<=n; i++)
    {
        if(a[i]!=a[i-1])
        {
            s[++cnt].x=a[i];
            s[cnt].times=1;
        }else{
            s[cnt].times++;
        }
    }//排序初始化每个数出现的次数。
    ll ans=0;
    for(int i=1; i<=n; i++)
    {
        ll t=a[i];
        ll sum=0;
        int sub=find(t);//找到当前数在结构体数组中的下标
        while(s[sub].times)
        {
            sum+=t*s[sub].times;
            s[sub].times=0;
            if(t%2==0)
            {
                t=t/2*3;
                sub=find(t);
                if(sub==-1) break;
            }else break;
        }
        ans=max(ans, sum);
        //与map差不多，不再赘述。
    }
    cout << ans;
    return 0;
}
```


---

## 作者：Lonely_NewYear (赞：1)

# 洛谷 P6786 题解

## 题目分析

这题如果能知道那些情况下这个式子能满足，不就简单多了？于是考虑简化这个式子。

设两数为 $X,Y(X<Y),\ \gcd(X,Y)=d,\ x=X/d,\ y=Y/d,\ \text 则\,lcm(X,Y)=dxy$。

$$X+Y+\gcd(X,Y)=lcm(X,Y)\\
dx+dy+d=dxy\\
d(x+y+1)=dxy\\
x+y+1=xy\\
y+1=x(y-1)\\
2=(x-1)(y-1)\text 且x<y\\
x=2,y=3\\
X:Y=dx:dy=x:y=2:3$$

这也就说明对于每一个数**最多只能有一个数**使得等式成立。

所以可以考虑递推，数组 $f_i$ 表示 $a_i$ 为最大值时满足条件的数列和的最大值。处理时从头到尾扫一遍，每次找到当前这个数的 $\frac{2}{3}$ 在 $a$ 数组中的位置 $j$，$f_i=a_i+f_j$。但是这个递推要求无后效性，考虑到只有较小的数才有可能对大数产生贡献，所以可以将原数组排序后再进行处理。要注意特判有相同的数的情况。答案为 $\max(f_i)$。

需要扫一遍数组同时二分查找原数的 $\frac{2}{3}$ ，所以时间复杂度为 $O(n\log n)$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long f[300001],ans;
int n,a[300001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		f[i]=a[i];
		if(a[i-1]==a[i])
		{
			f[i]+=f[i-1];
		}
		else if(a[i]%3==0&&binary_search(a+1,a+n+1,a[i]/3*2))
		{
			int j=upper_bound(a+1,a+n+1,a[i]/3*2)-a-1;
			f[i]+=f[j];
		}
		ans=max(ans,f[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

谢谢观看！

---

## 作者：littleKtian (赞：1)

考虑化简 $a+b+\gcd(a,b)=\operatorname{lcm}(a,b)$ 这个式子。

设 $c=\gcd(a,b),x=\dfrac{a}{c},y=\dfrac{b}{c}$，显然 $\operatorname{lcm}(a,b)=\dfrac{ab}{c}=cxy,\gcd(x,y)=1$。

带入，有 $cx+cy+c=cxy$。

化简并移项，因式分解得 $(x-1)(y-1)=2$。

易知此方程的**正整数解**只有 $\begin{cases}x=3\\y=2\end{cases},\begin{cases}x=2\\y=3\end{cases}$ 两组。

由此我们就可以将数列 $b$ 的要求描写成下面的形式：

对于任意 $b_i$，其满足下列两项要求之一：

+ **不存在 $b_j$，使得 $b_j>b_i$。**
+ 存在 $b_j$，使得 $b_j>b_i$ 且 $\dfrac{b_j}{b_i}=\dfrac{3}{2}$。

于是这题就变成一道简单的 dp 题了。

不想卡常的可以直接写 $O(n\log n)$ 的 sort+二分查找/map，想卡常的可以写 $O(n)$ 的 基排+双指针。

---

## 作者：y0y68 (赞：1)

感觉就是黄题吧。。

首先简单地推推柿子：

$$
b_i + b_j + \gcd(b_i,b_j)= lcm(b_i,b_j)
$$
$$
\Longrightarrow b_i+b_j + \gcd(b_i,b_j)=\frac{lcm(b_i,b_j)}{\gcd(b_i,b_j)} \times \gcd(b_i,b_j)
$$
$$
\Longrightarrow b_i+b_j=\gcd(b_i,b_j) \times \left( \frac{lcm(b_i,b_j)}{gcd(b_i,b_j)}-1 \right)
$$
$$
\Longrightarrow \frac{b_i}{\gcd(b_i,b_j)} + \frac{b_j}{\gcd(b_i,b_j)} + 1 = \frac{lcm(b_i,b_j)}{\gcd(b_i,b_j)} = \frac{b_i \times b_j}{\gcd(b_i,b_j)^2} = \frac{b_i}{\gcd(b_i,b_j)} \times \frac{b_j}{\gcd(b_i,b_j)}
$$
$$
\Longrightarrow \left( \frac{b_i}{\gcd(b_i,b_j)} - 1 \right) \times \left( \frac{b_j}{\gcd(b_i,b_j)} - 1 \right) = 2
$$
$$
\Longrightarrow \frac{b_i}{\gcd(b_i,b_j)},\frac{b_j}{\gcd(b_i,b_j)} = 2,3
$$
$$
\Longrightarrow \max(b_i,b_j)=3,\min(b_i,b_j)=2
$$

题目就变成了：若 $b_i$ 不是 $b$ 中最大的，则存在一个 $b_j$，使得 $\frac{b_i}{b_j}=\frac{2}{3}$，于是就做完了。

代码，时间复杂度为 $O(n \log n)$：

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int N=3e5+5;
int n,ans,a[N];
map<int,int>cnt;//统计每个数在a中的出现次数
map<int,bool>vis;//每个数是否找到过
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),cnt[a[i]]++;
	//以下类似找最长链过程
	for(int i=1;i<=n;i++){
		if(vis[a[i]])continue;
		int x=a[i],s=0;//s表示总和，x表示当前数
		while(cnt[x]){
			s+=cnt[x]*x,vis[x]=1;
			if(x&1)break;
			x+=x>>1;
		}
		ans=max(ans,s);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：codecode (赞：1)

#### 题解：

首先看到题目中的式子便知道需要化简（$O(n^2)$ 的复杂度是过不了的），而对于此类有 $\gcd$ 出现的式子，常用做法是把 $\gcd$ 设出来。

如果正整数 $a,b\;(a>b)$ 满足 

$$a+b+\gcd(a,b)=\operatorname{lcm}(a,b)$$

设 $d=\gcd(a,b)$，则 $d|a$ 且 $d|b$，设 $a=dx,b=dy$。

熟知 $\gcd(a,b)\times\operatorname{lcm}(a,b)=ab$，得 $\operatorname{lcm}(a,b)=dxy$。

将以上结果带入原式得

$$\begin{aligned}dx+dy+d &= dxy\\x+y+1 &= xy\\(x-1)(y-1)&=2\end{aligned}$$

而 $x,y$ 为正整数，且 $x>y$，故只能是 $x=3,y=2$。

特别地，原题的条件等价于：

> 对于所有 $i\;(1\leq i \leq k)$，$b_i$ 要么是序列 $b$ 中的最大值，要么存在一个位置 $j$ 使得 $b_j:b_i=3:2$。

我们要最大化 $\sum b_i$。

事实上, 我们可以在所有满足 $b_j:b_i=3:2$ 的 $(b_i,b_j)$ 间连有向边，于是条件即化为：若选择了一条有向边的入点，则必须选出点，且至多选一个没有出边的点，最大化点权和。

这即要求我们在图中找到点权和最大的连通分支，寻找连通分支可以并查集维护。

总时间复杂度 $O(n\log n)$。

------------

#### 代码：

好吧，当时的代码写得有点丑，还写复杂了（

（用 `map` 写会简短很多）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5+2333;
int n,ans,res;
struct juju{int data,fa;}a[maxn];
int f(int x){ //并查集 路径压缩
	if(a[x].fa==x)return x;
	return a[x].fa=f(a[x].fa);
}
bool cmp1(juju u,juju v){return u.data<v.data;}
bool cmp2(juju u,juju v){return u.fa<v.fa;}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].data;
	sort(a+1,a+n+1,cmp1); 
	for(int i=1;i<=n;i++)
		a[i].fa=i;
	for(int i=2;i<=n;i++) //值相同的需要合作一个
		if(a[i].data==a[i-1].data)a[i].fa=a[i-1].fa;
	for(int i=1;i<=n;i++){
		if(a[i].data%2)continue;
		int tmp=a[i].data/2*3,k=0;
		int l=i,r=n+1;
		while(l<r){ //二分查找 a[i]/2*3
			int mid=(l+r)/2;
			if(a[mid].data>tmp)r=mid;
			else if(a[mid].data<tmp)l=mid+1;
			else{k=mid;break;}
		}
		if(k){int f1=f(k),f2=f(i);a[f1].fa=f2;} //图并不一定要建出来，只要将它们划入同一个连通分支就可以了，也就是合并它们所在的并查集
	}
	for(int i=1;i<=n;i++){
		int u=f(i);
		a[i].fa=a[u].fa;
	}
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++){ //寻找权值和最大的连通分支，这里还可以用桶实现
		if(a[i].fa!=a[i-1].fa){
			ans=max(ans,res);res=0;
		}
		res+=a[i].data;
	}
	ans=max(ans,res);
	cout<<ans;
	return 0;
}
```


---

## 作者：TZMydl (赞：1)

~~显然的数学题。~~

自认为讲得比较详细，适合新手食用哦！~~（其实我也是新手）~~

本题的精髓在于推出这样的结论：

有两个数 $a$ 和 $b(a<b)$，若 $a+b+\gcd(a,b)=\operatorname{lcm}(a,b)$，则 $a=\dfrac{2}{3}b$。

下面证明这个结论：

设 $g=\gcd(a,b)$，$l=\operatorname{lcm}(a,b)$，则 $g+a+b=l$，并且我们知道 $l*g=a*b$；

两边同乘 $g$，得：

$g^2+g \times a+g \times b=a \times b$；

再同时除以 $g^2$，得：

$1+\dfrac{a}{g}+\dfrac{b}{g}=\dfrac{a \times b}{g^2}$；

也即：

$1+\dfrac{a}{g}+\dfrac{b}{g}=\dfrac{a}{g} \times \dfrac{b}{g}$；

这时我们就可以设 $x=\dfrac{a}{g}$，$y=\dfrac{b}{g}$，则有：

$1+x+y=x \times y$ 即 $x \times y-x-y+1=2$；

对左边的多项式进行因式分解，得：

$(x-1) \times (y-1)=2=1 \times 2$；

由于 $g=\gcd(a,b)$，故 $g \mid a$，$g \mid b$；

故 $x$，$y$ 是正整数 $(x<y)$，则有方程组：

$\begin{cases}x-1=1\\y-1=2\end{cases}$；

解得：

$\begin{cases}x=2\\y=3\end{cases}$;

故 $\dfrac{x}{y}=\dfrac{\dfrac{a}{g}}{\dfrac{b}{g}}=\dfrac{a}{b}=\dfrac{2}{3}$，即 $a=\dfrac{2}{3}b$，证毕。

结论证完了，接下来说说代码实现的思路：

~~当然是用map无脑模拟啦。~~

这里还是要讲一下为什么要使用map。

我们模拟用到了桶的思想，但是，如果用一般的数组模拟，桶容量是 $1 \times 10^9$ 的，会MLE，显然是不可行的；

而map就不一样了，它是动态开辟空间的，所以用了map，空间复杂度就不再和 $\max a_i$ 而是和 $n$ 有关了，这样显然就不会爆空间了。

有了map之后，我们就可以放心大胆地进行模拟了：

在读入的时候用一个桶统计 $a_i$ 这个数出现的次数；

在循环的时候，若 $a_i$ 还没有被加入到一种方案的数列中，则创建一个以 $a_i$ 为核心的数列作为一种新的方案；

在创建的过程中，我们利用 $\dfrac{a}{b}=\dfrac{2}{3}$ 这个结论，将小于 $a_i$ 的数（如果符合条件）加入数列中，并且将加入到数列里的数在桶中的位置清空，代表这个数已经被统计过；

因为 $\dfrac{a}{b}=\dfrac{2}{3}$，所以 $\dfrac{b}{a}=\dfrac{3}{2}$，将大于 $a_i$ 的数（如果符合条件）加入数列中，并且进行清空操作；

这样下来，我们每一次循环都会获得一种方案，用临时变量即时统计该方案中数列中的数之和，并更新答案；

这里的符合条件是指用我们目前的数，可以由 $\dfrac{a}{b}=\dfrac{2}{3}$ 得到另一个正整数，若不符合条件，则不必再继续寻找，正确性是显然的，读者可以自己思考；

这样，我们的模拟就完美地结束啦！

由于每一个数都只会被统计一次，所以时间复杂度是妥妥的 $O(n \log(n))$ (map自带 $O(\log(n))$ 的时间复杂度，常数也挺大，~~不过似乎可以用unordered_map把时间复杂度降到 $O(1)$~~)；

读者可根据模拟过程自行分析一下时间复杂度；

最后，再叮嘱一句：**十年OI一场空，不开long long见祖宗！**

下面是代码时间：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<map> 
#define ll long long 
using namespace std;
int n,a[300005];
ll ans=0;
map<int,int> m;
inline int read(){
	int num=0;char ch=getchar();bool f=0;
	while(!isdigit(ch)){
		f|=(ch=='-');
		ch=getchar();
	}
	while(isdigit(ch)){
		num=(num<<1)+(num<<3)+(ch^48);
		ch=getchar();
	}
	return f?-num:num;
}
inline ll max(ll a,ll b){
	if(a>b)return a;
	return b;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		m[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(!m[a[i]])continue;
		ll s=0;
		s+=(ll)m[a[i]]*a[i];
		int x=0,y=0;
		if(a[i]%2==0)x=a[i]/2*3;
		if(a[i]%3==0)y=a[i]/3*2;
		while(m[x]){
			s+=(ll)m[x]*x;
			m[x]=0;
			if(x%2==0)x=x/2*3;
			else break;
		}
		while(m[y]){
			s+=(ll)m[y]*y;
			m[y]=0;
			if(y%3==0)y=y/3*2;
			else break;
		}
		m[a[i]]=0;
		ans=max(s,ans);
	}
	printf("%lld",ans);
	return 0;
}
```

这是本蒟蒻的第一篇题解，码了几个小时，如有不足请在评论或私信指出。

希望管理大大给过！

都看到这里了，不顺便点个赞吗？

---

## 作者：SSerxhs (赞：1)

设 $\gcd(b_i,b_j)=z,b_i=xz,b_j=yz$，根据 $ab=\gcd(a,b)\times \text{lcm}(a,b)$ 可得 $xz+yz+z=xyz$

由于 $z\ne 0$，有 $xy-x-y=1$

即 $(x-1)(y-1)=2$

由于 $x<y$ 且均为正整数则 $x=2,y=3$,（此时 $x,y$ 互质，也保证了 $z$ 是 $\gcd$）

即 $\dfrac{b_i}{2}=z=\dfrac{b_j}{3}$

因此，对于一个非最大值的 $b_i$，$1.5\times b_i$ 必定也要被选出，又因为最大值是唯一的，所以所选出的数在排序后构成公比为 $1.5$ 的等比数列，可以通过快速排序 + 二分或双指针 dp 解决。这里用的是暴力搜索 + 哈希表，时间复杂度也可以做到单 $log$ (但因为代码中哈希表使用 map ，时间复杂度为 $O(nlog\max \{a_i\}logn)$ )

```
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
const int N=3e5+2;
ll ans,na;
map<int,int> mp;
int a[N],b[N],sum[N];
int n,i,j,gs,x;
bool ed[N];
int main()
{
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		if (!(j=mp[a[i]])) sum[mp[a[i]]=++gs]=1; else ++sum[j];
	}
	for (i=1;i<=n;i++)
	{
		na=(ll)sum[j=mp[a[i]]]*a[i];
		if (ed[j]) continue;
		x=a[i];ed[j]=1;
		while ((x&1)==0)
		{
			x=3*(x>>1);
			na+=(ll)sum[j=mp[x]]*x;
			if (!j) break;
			ed[j]=1;
		}
		if (na>ans) ans=na;
	}
	printf("%lld",ans);
}
```

复杂度证明:答案不超过 $log_{1.5}\max \{a_i\}$，每次内层循环只有在答案得以延长的情况下才会继续循环，循环次数至多 $O(nlog\max \{a_i\})$，故总复杂度为 $O(nlog\max \{a_i\}logn)$。

---

## 作者：CuberStan (赞：1)


## 一个树(链)形图遍历+二分查找的鬼畜题解
这是一道显然的数学题，但由于本人太菜在比赛期间没有推出来任何有用的结论。最后只是爆搜乱搞了40pts。

做这道题目的时候，首先看到 25pts n<=17 的部分分，就自然想到了爆搜。这25pts最为基本，也是最好拿的，代码就不放了。


在拿到25pts后，就看到了 n<=2000 的又15pts,我们自然想到了搜索的优化。


本蒟蒻在比赛期间想到了构造一个图,对于每组满足条件的i,j都建一条从i通往j的边，最后就形成了一个完整的树形图（对于本题来说，实际上退化成了几条链和很多散点）。

建图代码如下：
```
for(ll i=1;i<=n;i++){
		for(ll j=i+1;j<=n;j++){
			if(满足表达式){
				add(i,j);
			}
		}
	}
```


由于整个数列都是正数，所以在遍历起点相同的情况下，自然向下取得越多答案越优，这样整个搜索的框架就自然出来了。
代码见后文正解完整代码。

这么写只有40pts，剩下全是TLE。
原因很简单：在建图的时候使用了二重循环，复杂度为$\Theta(n^2)$，对于 n<=3e5 的数据自然爆炸。

所以怎么降低建图的复杂度？

如果给出了一个 i，在不用整个扫一遍的情况下就能找到匹配的 j，自然复杂度就低了很多。怎么找出 i 和 j 的关系呢？

# **重点来了**




令   $i={\gcd(x,y)},j=\operatorname{lcm}(x,y)$

因为  $\operatorname{lcm}(x,y)=\frac{xy}{\gcd(x,y)}$

则 $x+y+i=j=\frac{xy}i$

$1+\frac{x}i+\frac{y}i-\frac{xy}{i^2}=0$

令$a=\frac{x}i,b=\frac{y}i$

则$1+a+b=a \times b$

$(a-1) \times (b-1)=2$

由于 $a-1,b-1$为正整数

则方程有解$\begin{cases}a=2\\b=3\end{cases}$和$\begin{cases}a=3\\b=2\end{cases}$

设 $x<y$ 则$a<b$ 

则$\frac{a}{b}=\frac{x}{y}=\frac{2}{3},$即对于满足题目表达式的$x,y(x<y)$,有

$x=\frac{2}{3}y$


于是，我们有了这个至关重要的结论:

## 若对于两个正整数$x,y(x<y)$有$x+y+\gcd(x,y)=\operatorname{lcm}(x,y) $，则$x=\frac{2}{3}y$ 。

也就是说，对于一个节点 i,如果有一个节点 j 的值满足$a[i]=\frac{2}{3}a[j]$，则建一条边(i , j)。这样就构成了一个完整的图(~~全是链和散点的图~~)。

用lower_bound即可在log级复杂度下完成j的查找，整个代码的复杂度是 $\Theta(n\log n)$（主要在于建图上），搜索的复杂度是 $\Theta(n)$

具体细节见代码实现（~~136ms,跑得挺快的~~）。

完整代码如下(杜绝抄袭):
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#define ll long long
#define G() c=getchar()
#define I() isdigit(c)
using namespace std;
inline ll read(){
	ll x=0,f=1;char G();
	while(!I()){f=c=='-'?-1:1,G();}
	while(I()){x=(x<<1)+(x<<3)-'0'+c;G();}
	return x*f;
}
ll n,a[300005],d[300005],ans,cnt,b[300005];
/* a数组储存具体数值,d数组储存排名第i的数出现的次数
b数组储存i节点指向的节点（由于图退化成链，所以每个点至多指向一个节点，若无指向的节点则为0）*/
bool vis[300005],vis1[300005];
// vis数组用于搜索时判断是否搜过，vis1数组处理判重复数
ll max(ll x,ll y){return x>y?x:y;}//手写max防爆
ll dfs(ll u){
	vis[u]=1;
	ll x=0;
	if(!b[u])return d[u]*a[u];//如果这条链到头了，直接返回
	if(!vis[b[u]])x+=dfss(b[u]);
	return x+d[u]*a[u];
}
int main(){
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);//先排序
	for(ll i=1;i<=n;i++){
		d[i]=1;
		if(vis1[i]){
			d[i]=d[i-1];//若该位置已经处理过了，说明该位置的数字是重复出现的，直接继承上一个位置的数字
			continue;
		}
		for(ll j=i+1;j<=n;j++){
			if(a[j]!=a[i])break;
			vis1[j]=1;
			d[i]++;
		}//如果没有处理过，暴力循环处理并标记
	}
	for(ll i=1;i<n;i++){
		if(a[i]%2)continue;//由上面结论可知,a[i]必须为偶数才有可能满足条件
		ll t=lower_bound(a+1,a+n+1,a[i]*3/2)-a;//STL大法好
		if(a[i]*3!=a[t]*2)continue;
		b[i]=t;//建边，由i指向t
	}
	for(ll i=1;i<=n;i++)if(!vis[i])ans=max(ans,dfs(i));
	cout<<ans;
   return 0;//结束
}
```

造图遍历+二分查找估计算是一个比较奇葩的解法了，也有神犇用map直接模拟，本蒟蒻想不起来这样的处理方法，直接%%%。

感谢大家阅读，希望能够对大家有所帮助。
这也是本蒟蒻的第一篇题解，码了几个小时，如有不足请在评论或私信指出，希望审核大大给通过！

---

## 作者：Islauso (赞：1)

[传送门](https://www.luogu.com.cn/problem/P6786)

这道题其实乍一看很难，但其实就是一道推数学规律的题，只要把这个规律推出来了，剩下的也就很好办了。

最关键的就是题面中所给的那个式子，$b_i+b_j+\gcd(b_i,b_j)=\operatorname{lcm}(b_i,b_j)$，我们令 $x=\gcd(b_i,b_j)$，$p_i=b_i\div x$，$p_j=b_j\div x$，则根据最小公因数和最大公倍数的定义可以得到：

$$
p_i\cdot x+p_j\cdot x=x\cdot p_i\cdot p_j-x\\
p_i+p_j=p_i\cdot p_j-1\\
p_i\cdot p_j-p_i-p_j+1=2\\
(p_i-1)\cdot(p_j-1)=2
$$

很明显可以知道

$$
p_i\in \mathbb{N_+},p_j\in\mathbb{N_+}
$$

于是就可以推出

$$
p_i=2,p_j=3
$$

所以

$$
b_i:b_j=2:3
$$

也就是说，对于一个数，要么它是序列中最大的那个，要么就有另外一个数是它的 $\dfrac{3}{2}$ 倍。

因此，对于选出来的序列 $b_1,b_2,b_3,\cdots,b_k$，将其**去重**并从小到大排序后，应该满足 $\dfrac{3}{2}b_i=b_{i+1}$，也就是一个公比为 $\dfrac{3}{2}$ 的等比数列，至于为什么是去重后，因为我们只关心这个数有没有比它大 $\dfrac{1}{2}$ 的数，只要满足这个条件，无论有几个和这个数相同的数，我们都可以把它们放在序列里面，比如 $2,2,2,3,3$ 这个序列就是满足条件的。

这样，问题就转化成了，在给定序列中寻找一个公比为 $\dfrac{3}{2}$ 的等比序列，并且这个序列中所有数的和最大。对于这个问题，我的思路是 DP，先对原序列进行排序和去重，用 $f_i$ 表示以第 $i$ 个数结尾的公比为 $\dfrac{3}{2}$ 的等比数列中所有数的最大的和，状态转移方程也很好想，就是对于 $a_i$，找有没有 $a_j=\dfrac{2}{3}a_i$，如果有，那么 $f_i\leftarrow f_j+f_i$，如果没有，就不管它，由于事先已经对序列排序并去重，所以这个找的过程可以用二分解决（别跟我说桶排，$10^9$ 的值域你自己去排），时间复杂度为 $O(n\log n)$，对付 $3\times 10^5$ 的数据也够了。

至于预处理，在去重的时候顺便解决一下就好了，具体的可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[300001],b[300001];//a 是原数组，b 是去重后的数组
long long ans,f[300001];
int check(int l,int r,int val)//二分查找，如果有值为 val 的数则返回下标，没有则返回 -1
{
	while(l<=r)//记得一定要有等于！！！
	{
		int mid=(l+r)/2;
		if(b[mid]==val)
			return mid;
		if(b[mid]>val)
			r=mid-1;
		if(b[mid]<val)
			l=mid+1;
	}
	return -1;
} 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);//排序
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=a[i-1])//去重
			b[++k]=a[i];
		f[k]+=a[i];//预处理，如果和上一个数相同，就自动加到一起
	}
	for(int i=1;i<=k;i++)
	{
		if(b[i]%3==0)//一定要有这个条件！
		{
			int t=check(1,i,b[i]/3*2);
			if(t!=-1)
				f[i]+=f[t];
		}
		ans=max(ans,f[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：infinities (赞：0)

首先，看到题目里唯一的柿子 $b_i +b_j+\gcd(b_i,b_j)=\operatorname{lcm}(b_i,b_j)$，会比较懵，因为这个柿子好像只能暴力枚举的样子。

其实可以两边同除以一个 $\gcd(b_i,b_j)$，这里设 $\frac{b_i}{\gcd(b_i, b_j)} =x$，$\frac{b_j}{\gcd(b_i,b_j)} =y$，则有 $x + y+1=xy$，容易看出（或者枚举比较小的 $x,y$）这样的正整数 $x,y$ 其实有且只有一对，即样例里的 $x=2,y=3$（可以反过来）。

于是这样就好办了。

能选择配对的两个数一定大的是 $3k$，而小的是 $2k$，而且重复的数显然要一起选或者一起不选。

于是可以枚举每一个序列里的数作为最大值，按如上所述的方法向下配对，看最大值即可。

具体实现可以开个 map，如果怕 map 超时可以换成 C++11 的黑科技 unordered_map，单次操作是 $O(1)$ 级别的，虽然常数巨大而且可能会被卡。

用 map 总复杂度是 $O(n \log_{\log_23}n \log n)$ 的。中间那一坨奇怪的东西是因为每次向下计算的时候数字会缩小到原来的 $\frac{2}{3}$。

代码中间有一坨是原来写的复杂度错误的东西的，懒得删了。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint regester int
const int maxn = 1e6 + 10;
const int INF = 1e9;
using std::ios;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::unique;
using std::lower_bound;
using std::swap;
using std::abs;
using std::acos;
using std::queue;
using std::map;
using std::string;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int n, a[maxn], num[maxn];
int cnt = 0;
struct div2{
	int pos, num;
}d2[maxn];
struct div3{
	int pos, num, nnm;
}d3[maxn];
bool cmp2(div2 a, div2 b){
	return a.num > b.num;
}
bool cmp1(div3 a, div3 b){
	return a.num > b.num;
}
int ans, vis[maxn];
std::unordered_map<int, int>ma;
signed main(){
	n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
	}
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; i++){
		++ma[a[i]];
		if(a[i] == a[i - 1])++num[cnt];
		if(a[i] != a[i - 1])++num[++cnt]; 
	}
	n = unique(a + 1, a + 1 + n) - a - 1;
	for(int i = 1; i <= n; i++){
		d3[i].pos = d2[i].pos = i;
		d3[i].nnm = a[i];
		if(a[i] % 3 == 0)d3[i].num = a[i] / 3;
		if(a[i] % 2 == 0)d2[i].num = a[i] / 2;
	}
	sort(d3 + 1, d3 + 1 + n, cmp1);
	sort(d2 + 1, d2 + 1 + n, cmp2);
	int j = 1;
	for(int i = 1; i <= n; i++){
		ans = max(ans, ma[d3[i].nnm] * d3[i].nnm);
		if(d3[i].num == 0){
			continue;
		}
		int aa = d3[i].num * 3, sum = 0, now = i, fl = 1, fll = 0, op = 0;
		if(aa % 3 == 0)sum += ma[aa] * aa;
		while(j <= n && fl && aa % 3 == 0){
			op = 1;
			aa = aa * 2 / 3;
			if(ma[aa])sum += ma[aa] * aa; else break;
		}
		ans = max(ans, sum);
	}
	cout << ans;
}
```

---

## 作者：K_Madoka (赞：0)

根据打表，可以得出一个结论：

$a+b+gcd(a,b)=lcm(a,b)\quad(a\leq b)$，当且仅当$a=\frac{2}{3} b$。

所以，这个结论我们怎么推呢：
$$a+b+gcd(a,b)=lcm(a,b)$$

$$∵ lcm(a,b)=\frac{a\cdot b}{gcd(a,b)}$$

$$∴a+b+gcd(a,b)=\frac{a \cdot b}{gcd(a,b)}$$

$$∴\frac{a}{gcd(a,b)}+\frac{b}{gcd(a,b)}+1=\frac{a\cdot b}{gcd(a,b)^2}$$

$$∴\frac{a}{gcd(a,b)}+\frac{b}{gcd(a,b)}=\frac{a}{gcd(a,b)}\times\frac{b}{gcd(a,b)}-1$$

$$∴\frac{a\cdot b}{gcd(a,b)}+\frac{a}{gcd(a,b)}+\frac{b}{gcd(a,b)}-1=0$$

$$∴\frac{a\cdot b}{gcd(a,b)}+\frac{a}{gcd(a,b)}+\frac{b}{gcd(a,b)}+1=2$$

$$∴(\frac{a}{gcd(a,b)}-1)\times(\frac{b}{gcd(a,b)}-1)=2$$

最后你会发现$\frac{a}{gcd(a,b)}=2$，$\frac{b}{gcd(a,b}=3$，$∴a=\frac{2}{3}b$

那么得出这个结论后，我们就可以对每个数看最长能延伸多少，统计答案就行了。

---

## 作者：sfmmdm (赞：0)

题目里有一个看似很恐怖的要求“使 $b_j>b_i$ 且 $b_i+b_j+ \gcd(b_i,b_j) = \operatorname{lcm}(b_i,b_j)$。”

~~于是我们想到，这一定是一道数论题。~~

那么让我们看一看对于两个整数 $x,y$，什么时候才会满足 $x+y+\gcd(x,y)=\operatorname{lcm}(x,y)$ 吧。

我们知道，对于任意**正整数** $x,y$，$\gcd(x,y) \mid x$ 且 $\gcd(x,y) \mid y$，那么我们不妨设 $x=k_1\gcd(x,y),y=k_2\gcd(x,y)(k_1,k_2 \in \mathbb{N^*})$。那么

$$\operatorname{lcm}(x,y)=\dfrac{xy}{\gcd(x,y)}=\dfrac{k_1k_2\gcd(x,y)^2}{\gcd(x,y)}=k_1k_2\gcd(x,y)$$

原式就可化为：

$$k_1\gcd(x,y)+k_2\gcd(x,y)+\gcd(x,y)=k_1k_2\gcd(x,y)$$

两边同时除以 $\gcd(x,y)$，就可以得到 $k_1+k_2+1=k_1k_2$。

我们只要找到满足条件的 $k_1$ 和 $k_2$，就可以找出所有满足条件的 $x,y$ 了。

我们继续：

$${k_2+1}=k_1(k_2-1)$$

$$\frac{k_2+1}{k_2-1}=k_1$$

很明显，当 $k_1,k_2 \in \mathbb{N^*}$ 时，只存在以下两组解：

$\begin{cases}k_1=2\\k_2=3\end{cases}$ 或 $\begin{cases}k_1=3\\k_2=2\end{cases}$

也就是说，对于任意两个**正整数** $b_i<b_j$，要使 $b_i+b_j+ \gcd(b_i,b_j) = \operatorname{lcm}(b_i,b_j)$，当且仅当 $b_i:b_j=2:3$

至此，我们得出了一个惊人的结论，那就是：

**~~这题根本就不是数论题。~~**

这题实际上就是在说，在序列中找到一些数，使这些数在去重、排序后是一个公比为 $1.5$ 的等比数列，且这个数列和最大。

那我们可以在对原数据排序后，用动态规划实现，设 $f_i$ 表示**排序后**以 $a_i$ 结尾能组成的和最大的数列的和。初值 $f_1=a_1$。

$$f_i=\begin{cases}f_{i-1}+a_i&a_{i-1}=a_i\\f_j+a_i&a_{i-1} \neq a_i ,\dfrac{a_j}{a_i}=\dfrac{2}{3},a_j \neq a_{j+1}\end{cases}$$

答案为 $\max\{f_i\},1\le i \le n$

这里解释一下，当 $a_{i-1}=a_i$ 时，我们只要在 $i-1$ 处构造出的数列中再加上本身即可。否则，我们要找到使 $\dfrac{a_j}{a_i}=\dfrac{2}{3}$ 成立的**最后一个** $j$，将其累加到 $f_i$ 里。

由于数据被排序，则 $j$ 是随着 $i$ 的增加而增加的，所以我们只要用双指针扫过一遍数组即可，DP 的时间复杂度为 $O(n)$，加上排序，整体时间复杂度为 $O(n \log n)$。

程序实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300005],n;
long long f[300005],ans;
int main() {
    scanf("%d",&n);
    for(int i=1; i<=n; i++) scanf("%d",a+i);
    sort(a+1,a+1+n);
    for(int i=1; i<=n; i++) f[i]=a[i];//提前在f数组中初始化为a[i]，方便之后的计算
    int j=1;
    for(int i=2; i<=n; i++) {
        if(a[i]!=a[i-1]) {
            if(a[i]%3!=0) continue; //如果a[i]不是3的倍数，直接跳过
            int div=a[i]/3*2;
            long long sum=0;
            while(j<=i&&a[j]<=div) {//这里扫过边界，则j-1就是要的结果
                j++;
            }
            if(a[j-1]==div) sum=f[j-1];
            f[i]+=sum;
        } else f[i]+=f[i-1];
    }
    for(int i=1; i<=n; i++) {
        ans=max(ans,f[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：a___ (赞：0)

看起来很难但其实很水。   

________

$$a+b+\gcd(a,b)=\operatorname{lcm}(a,b)$$   
将 $\operatorname{lcm}(a,b)$ 用 $\gcd(a,b)$ 表示：   
$$a+b+\gcd(a,b)=\frac{ab}{\gcd(a,b)}$$    
两边同除一个 $\gcd(a,b)$：  
$$\frac{a}{\gcd(a,b)}+\frac{b}{\gcd(a,b)}+1=\left(\frac{a}{\gcd(a,b)}\right)\left(\frac{b}{\gcd(a,b)}\right)$$   
记 $x=\dfrac{a}{\gcd(a,b)},y=\dfrac{a}{\gcd(a,b)}$：   
$$x+y+1=xy$$   
移项，整理得：   
$$xy-x-y+1=2$$   
因式分解：   
$$(x-1)(y-1)=2$$   
由于 $x,y\in N^* $，则若 $x<y$：   
$$x=2,y=3$$   
即：   
$$\frac{a}{\gcd(a,b)}=2,\frac{b}{\gcd(a,b)}=3$$   
即：   
$$b=\frac 3 2 a$$   

所以存在 $j$ 使 $b_j>b_i$ 且 $b_i+b_j+\gcd(b_i,b_j)=\operatorname{lcm}(b_i,b_j)$ 等价于 $b_j=\frac 3 2 b_i$。    

也就是说，数列 $b$ 中的一个数要么是最大值，要么一定是一个数的 $\frac 2 3$。于是通过枚举 $b$ 中最小值然后不断乘 $\frac 3 2$ 即可得到整个数列。   
注意：同一个数可能有多个。    
```cpp
#include<cstdio>
#include<algorithm>
const int N=3e5+10;
int n,a[N];
bool vis[N];
long long sum,ans;
int main()
{
    int i,j,k;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    scanf("%d",&a[i]);
    std::sort(a+1,a+1+n);
    for(i=1;i<=n;i++)
    if(!vis[i])
    {
        sum=0;
        for(j=a[k=i];k<=n&&a[k]==j;k=std::lower_bound(a+1,a+1+n,j=j/2*3)-a)
        {
            while(k<=n&&a[k]==j)sum+=j,vis[k]=true,++k;
            if(j&1)break;
        }
        if(sum>ans)ans=sum;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Loser_King (赞：0)

### Part 0 前言

月赛C的题目，一道大数论。

考时口胡，考后证明。

## Part 1 题意

> 从一个数组中挑出 $k$ 个数，保证这 $k$ 个数满足对于数 $b_i$ ，有 $b_i+b_j+\gcd(b_i,\;b_j)=\operatorname{lcm}(b_i,\;b_j) (i<j\le k)$

## Part 2 做法

直接暴力枚举每个数选还是不选的时间复杂度高达 $O(2^n\times n)$，最多只能过 $Subtask\;1+2$。

所以肯定需要更快的做法。

思考 $b_i+b_j+\gcd(b_i,\;b_j)=\operatorname{lcm}(b_i,\;b_j) (i<j)$ 这个式子的性质。

考试时通过样例和猜想口胡地认为 $b_i:b_j=2:3$ 。

考后才进行了严谨的证明：

（[先放一个链接表示这是未看过讲评自己推出来的](https://www.luogu.com.cn/paste/p1nifr8o)）

$b_i+b_j+\gcd(b_i,b_j)=\operatorname{lcm}(b_i,b_j)\;(i<j)$ 

$b_i\div \gcd(b_i,b_j)+b_j \div \gcd(b_i,b_j)+1=b_i\times b_j \div \gcd(b_i,b_j)^2$

令$x=b_i\div \gcd(b_i,b_j)$，$y=b_j \div \gcd(b_i,b_j)$

则$x+y+1=xy(x<y)$

$xy-x=y+1$

$x(y-1)=y+1$

$x=\frac{y+1}{y-1}=1+\frac{2}{y-1}$

$\because$ $x$ 是正整数

$\therefore$ $\frac{2}{y-1}$ 是正整数

$\therefore$ $y=2$ 或 $y=3$。

当 $y=2$ 时，$x=3(\texttt{Wrong})$

当 $y=3$ 时，$x=2$

$\therefore$ $x+y+1=xy$ 的解为$x=2,y=3$。

$\therefore$ $x=b_i\div \gcd(b_i,b_j)=2$，$y=b_j \div \gcd(b_i,b_j)=3$

$b_i=\gcd(b_i,b_j)\times 2,\;b_j=\gcd(b_i,b_j)\times 3$

$\frac{b_i}{b_j}=\frac{\gcd(b_i,b_j)\times 2}{\gcd(b_i,b_j)\times 3}=\frac{2}{3}$

使用 `std::map<int,int>` 来存储最大值为`x`时的最大和。

递推，最后遍历`map`即可。

## Part 3 Code

比较短。

``` 
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,a[333333];
map<int,int>sum;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n==1){cout<<a[1]<<endl;return 0;}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		sum[a[i]]+=a[i];
		if(a[i]%3==0&&a[i]!=a[i-1])sum[a[i]]+=sum[a[i]/3*2];
	}
	for(map<int,int>::iterator i=sum.begin();i!=sum.end();i++)
	    ans=max(ans,i->second);
	cout<<ans<<endl;
}
```

---

## 作者：zjrdmd (赞：0)

本篇题解主要来讲解证明过程，具体的实现过程可参照其他题解或者代码实现。

相信很多人都猜到了结论，下面给出感性证明。

 $a+b+gcd(a,b)=lcm(a,b)$
 
 设$gcd(a,b)=d$，则$a=pd,b=qd,lcm(a,b)=a\times b/gcd(a,b)=pd\times qd/d=pqd$
 
原式转换为$pd+qd+d=pqd$。

再转换为$(p+q+1)d=pqd$。

$p+q+1=pq$。

所以在保证了$gcd(p,q)=1$的情况下，$p+q+1=pq$成立且$p>0,q>0$当且仅当$p=2,q=3$或者$p=3,q=2$。

那么所有满足 $a+b+gcd(a,b)=lcm(a,b)$的解一定是$p|a,q|b$，所以只有$2|a,3|b$或者$3|a,2|b$时，原式成立。

P.S，由于代码大部分是考场写的，所以当时特判了$n\leq 2$的点，大家凑合着看吧（核心代码在work3里）

```cpp
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#define ri register int
#define int long long
 
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

const int N=3e5+5,inf=1e9+7;

int n;
int vis[N];
int a[N];
int dp[N];
int ans=0;
std::map<int,int>mp,Pi;

int gcd(int x,int y){
	return (y==0)?x:gcd(y,x%y); 
}
 
int lcm(int x,int y){
	return x*y/gcd(x,y);
} 

void work1(){
	int x=read(),y=read();
	if(gcd(x,y)+x+y==lcm(x,y)||x==y)printf("%lld",x+y);
	else printf("%lld",std::max(x,y));
	exit(0);
}

void work2(){
	int x=read();
	printf("%lld",x);
	exit(0);
}

bool cmp(int x,int y){
	return x>y;
}

void work3(){
	bool check=false;
	std::sort(a+1,a+n+1,cmp);
//	for(ri i=1;i<=n;i++)printf("%d ",a[i]);
//	printf("\n");
    dp[1]=a[1]*mp[a[1]];
    Pi[a[1]]=1;
	for(ri i=2;i<=n;i++){
		dp[i]=std::max(dp[i],a[i]*mp[a[i]]);
		Pi[a[i]]=i;
		if(a[i]==-1)break;
		if(a[i]%2!=0)continue;
		int j=a[i]/2*3;
		dp[i]=std::max(dp[i],dp[Pi[j]]+a[i]*mp[a[i]]);
	}
//	for(ri i=1;i<=n;i++)printf("%d ",dp[i]);
//	printf("\n");
    for(ri i=1;i<=n;i++)ans=std::max(ans,dp[i]);
	printf("%lld",ans);
}

signed main(void){
	n=read();
	if(n==2)work1();
	else if(n==1)work2(); 
	for(ri i=1;i<=n;i++){
		a[i]=read();
		mp[a[i]]+=1;
		ans=std::max(mp[a[i]]*a[i],ans); 
	}
	for(ri i=1;i<=n;i++){
		if(a[i]%2!=0&&a[i]%3!=0)a[i]=-1;
	}
    work3(); 
	return 0;
}

```


---

