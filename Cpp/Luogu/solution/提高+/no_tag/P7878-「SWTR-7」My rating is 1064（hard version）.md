# 「SWTR-7」My rating is 1064（hard version）

## 题目背景

#### 本题是 My rating is ... 的 hard 版本。注意题目限制与 [easy](https://www.luogu.com.cn/problem/P7874) 版本不同。

#### 题目描述下方有简化题意。

[My rating is 1064.](https://codeforces.com/blog/entry/74503)（被 2 - Tower 炸掉了，因此现在打不开了）

## 题目描述

小 A 想在 Codeforces 上发 $n$ 篇帖子！例如：

> “My rating is 1064.”
>
> “I am PolarSea.”
>
> “你知道 phi 吗？你知道你的 phi 处是哪里吗？你知道它的 price 吗？1e9 + 7。”
>
>“每道题都很简单，全场虐题不用烦。T1 到场先签到，T2 上手随便切，T3 一交就能过，T4 稍想也能 A。DP 转移很容易，数学结论尽皆知。建图方法极明显，数据结构很一般。不卡空间不卡常，码量不大手不酸。没有毒瘤大模拟，只有良多大水题。片刻四题提交过，人人 AK 笑开颜。”
>
> “……”

为此，小 A 新注册了 $k$ 个账号。他决定按照顺序发出每篇帖子，并**用到所有 $k$ 个账号**。不过刷屏过多会引起 Mike 的注意并被封号，小 A 当然不希望这样：他进行了一些评估，得到了每篇帖子的安全指数 $a_i$，表示他发出第 $i$ 篇帖子后不被封号的概率。

由于第一印象非常重要，小 A 定义一个账号的安全指数为该账号所发出的**第一篇**帖子的安全指数。此外，如果**用同一个账号连续发出两个帖子**，该账号的安全指数会减小**这两篇帖子安全指数的较小值**。

小 A 希望找到这样一个发帖方案，使得所有账号的安全指数之和最大。你只需要求出安全指数之和的最大值即可。

---

**「简化题意」**

将 $1\sim n$ **不重不漏**地分进**恰好** $k$ 个集合 $S_1,S_2,\cdots,S_k$ 中 且 $|S_i|>0$。记 $i$ 被分入第 $d_i$ 个集合，求 

$$\left(\sum_{i=1}^k a[{\min_{j\in S_i}j}]\right)-\left(\sum_{i=1}^{n-1}\min(a_i,a_{i+1})[d_i=d_{i+1}]\right)$$

的最大值，其中左边的 $[x]$ 表示下标为 $x$，右边的 $[x]$ 表示当 $x$ 成立时取值为 $1$，当 $x$ 不成立时取值为 $0$。

## 说明/提示

**「样例 1 说明」**

小 A 可以使用账号 $1$ 发帖子 $1,2$ 和 $4$，用账号 $2$ 发帖子 $3$。其安全程度为 $(a_{\min(1,2,4)}-\min(a_1,a_2))+a_3=1-1+3=3$。

**「数据范围与约定」**

本题共有 6 个测试点。

- Testcase #0（1 point）：是样例。
- Testcase #1（20 points）：$k=2$。
- Testcase #2（20 points）：$n\leq 10$，$k\leq 4$。
- Testcase #3（15 points）：$k=3$。
- Testcase #4（20 points）：$n\leq 10^3$。
- Testcase #5（24 points）：无特殊限制。

对于 $100\%$ 的数据，$2 \leq k \leq n \leq 10^5$，$0 \leq a_i \leq 10^9$，$T=10$（除 Testcase #0）。  
对于所有测试点，时间限制 1s，空间限制 128MB。

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/) B2。  
idea & solution：[tzc_wk](https://www.luogu.com.cn/user/115194) & [Alex_Wei](https://www.luogu.com.cn/user/123294)（加强）；data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

> **My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. My rating is 1064. ……**
>
> **Upvote&emsp;-77&emsp;Downvote&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;PolarSea**  

## 样例 #1

### 输入

```
0
3
4 2
1 1 3 2
8 3
1 3 2 8 6 4 7 5
40 10
9843011 22841896 42690334 3412396 8420789 100693326 23390709 11537210 145661796 21418321 16914724 146120903 14287416 9157773 259599687 16469809 13371424 221660485 23554750 3004543 19382066 514113557 959488450 162305801 377127750 240963428 597774302 18789772 647693870 517468301 547221960 162988230 309004668 267293109 867629494 476230153 70400563 100943563 140708197 999999999
```

### 输出

```
3
13
5882440256
```

# 题解

## 作者：闲人 (赞：3)

## Step1：题目简化&粗略分析
与我以往写的题解不同，这一篇题解的第一个部分不再是《题目描述》，而是《题目简化&分析》，因为在我看来此题最大的障碍在于题目的理解。  
1. 首先，让我们理解一下什么叫做“用同一账号连续发多个帖子”。这其中有个很重要的一点，这会影响到我们后续的做题，注意此处的“连续”，设想一个问题，如果我发的所有帖子是不连续的（也就是说我在几个账号上循环发帖），那么就不存在同一账号上的“连续的多个帖子”了。

1. 其次，在理解了上一个问题之后再来看一下“该账号的安全指数会减小这两篇帖子安全指数的较小值”这句话做何理解（怎么感觉再讲阅读理解？）。其实很容易弄懂，这句话是指在同一账号中的连续帖子之间相邻连个帖子的最小值就是这个账号的风险，把这些值累加起来，第一篇帖子的安全系数减去累加起来的值就是这个账号的安全指数。

## Step2：题目详细分析  

在理解了第一部分的内容后就开始对题目进行一个较为深入的解析。  

### Step2_1：关于安全指数的来源

来源有二：其一，是本账号的第一篇帖子的安全指数。其二在后续发帖过程中所损失的安全指数。  

### Step2_2：如何使安全指数最大化  

1. 首先不难发现，总有一个账号的第一篇帖子是所有帖子的第一篇，应为所有帖子的的发帖顺序是固定的，只是在那个账号发事不固定的。  

1. 其次，根据 Step1_1 中提到的：“如果我发的所有帖子是不连续的（也就是说我在几个账号上循环发帖），那么就不存在同一账号上的‘连续的多个帖子’。”可以得出所有会损失安全值得操作会在第二个账号发了一个帖子后结束。  
1. 接下来，如果在用第二个账号发帖之后还有多余的账号，就可以用账号来发剩下帖子中价值最大的贴子以获取最大的收益。  
1. 最后一点，也是本题的关键：确定第二个账号发的第一个帖子是哪一篇。解决了这个问题，此题就结束了。

### Step2_3：如何解决 Step2_2_4 中所提到的问题

设想一个问题，如果前面帖子损失的安全指数已经大于了所有账号第一篇帖子中的最小值，那么我肯定会舍弃这个帖子然后减小前面帖子的损失。

这样的话我们就可以有效的解决 Step2_2_4 中的问题。

### 代码分析

接下来，只讲我个人的做题方法  

1. 先对所有相邻的贴子求一遍最小值，在对最小值求前缀和预处理。

1. 对原来序列排序，找出 $k - 1$ 个最大的帖子（还有一个帖子是所有帖子中的第一个，在 Step2_2_1 中有所讲解，并且记录这些帖子中最靠前的是哪一篇，（记位置为 $first\_where$ ）。
1. 枚举 $2$ 到 $first\_where$ 的每一个帖子作为第二个账号的第一篇帖子所获得的最大收益，求出答案

## AC code
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define reg register
#define ll long long

using namespace std;

int Time;
int T;
int n, k;

struct Node{
	ll size;
	int where;
}passage[100000 + 10];

ll pre[100000 + 10];
ll pre_[100000 + 10];
ll d[100000 + 10];

bool cmp(Node x, Node y) {return x.size > y.size;}

int main()
{
	scanf("%d", &Time);
	scanf("%d", &T);
	while(T--)
	{
		ll ans = 0, first = 0;
		ll Max = -1e9;
		ll value = 0;
		int first_where = 1e9;
		scanf("%d%d", &n, &k);
		for (reg int i = 1; i <= n; i++)
		{
			scanf("%d", &passage[i].size);
			passage[i].where = i;
			d[i] = pre[i] = passage[i].size;
		}
		first = passage[1].size;
		for (reg int i = 1; i < n; i++) pre[i] = min(passage[i].size, passage[i + 1].size);
		for (reg int i =1; i < n; i++) pre[i] = pre[i] + pre[i - 1];
		for (reg int i = 3; i <= n; i++) pre_[i] = pre[i - 2];
		sort(passage + 2, passage + n + 1, cmp);
		for (reg int i = 2; i <= k; i++) 
			first_where = min(first_where, passage[i].where);
		for (reg int i = 2; i <= k; i++) value += passage[i].size;
		Max = value + first - pre_[first_where];
		for (reg int i = 2; i < first_where; i++)
			Max = max(Max, (first - pre_[i] + d[i] + value - passage[k].size));
		printf("%lld\n", Max);
	}
	return 0;
}
```

## 后记

此篇题解写于 2021CSP 之前，在这里祝所有同学能在接下来的学习中跟进一步，考试中 rp++ ！

---

## 作者：Little09 (赞：3)

沿用 easy version 的思路：考虑如果到目前已经放了 $2$ 个集合及以上，那么接下来只要轮换放置就可以避免「用同一个账号连续发出两个帖子」。所以在放了 $2$ 个集合以后只要找到剩下前 $k-2$ 大的数放即可。

于是一定是把前 $x$ 个数放在第一个集合，第 $x+1$ 放在第二个集合，剩下的选出前 $k-2$ 大放在剩下集合。

然后直接倒着枚举 $x$，用堆（priority_queue）维护剩余的前 $k-2$ 大的数，计算即可。

```cpp
const int N=500005;
int n,m,T; 
ll a[N];
priority_queue<ll>p;
ll sum,ans;
inline void add(ll x)
{
	sum+=x;
	p.push(-x);
	ll u=-p.top();
	sum-=u;
	p.pop();
}
void work()
{
	n=read(),m=read()-2;
	for (int i=1;i<=n;i++) a[i]=read();
	ll tot=a[1];
	sum=0;
	while (!p.empty()) p.pop();
	for (int i=n-m+1;i<=n;i++) sum+=a[i],p.push(-a[i]);
	for (int i=2;i<=n-m-1;i++) tot-=min(a[i-1],a[i]);
	ans=tot+sum+a[n-m];
	for (int i=n-m-1;i>=2;i--)
	{
		add(a[i+1]);
		tot+=min(a[i],a[i-1]);
		ans=max(ans,tot+sum+a[i]);
	}
	printf("%lld\n",ans);
	return;
}
```


---

## 作者：MY（一名蒟蒻） (赞：3)

[P7878 「SWTR-07」My rating is 1064（hard version）](https://www.luogu.com.cn/problem/P7878)

[简单版](https://www.luogu.com.cn/problem/P7874) [题解](https://www.luogu.com.cn/blog/nizhuan/ti-xie-p7874-swtr-07my-rating-is-32easy-version)

## 题外话

赛时因为 Div1 B2 在 A2 前面，结合 Div2 前两题的难度，我就按顺序做了。这题还是调了我挺久的，不过赛时总算是想到了正解。

我很开心能赛时做出这道蓝题，这也是我第一次月赛 Div1 能 AC 一题。

写篇题解记录下想法吧。

## 思路

跟 easy version 相比，发帖子的限制放宽了。结合样例也可以知道这会对答案产生一些影响。

容易发现一个性质，我如果在一个号连续发帖，一定是一开始的时候全部堆在第一个号。

为啥？后面开第二个号就不需要付出代价丢掉一些我不要的帖子了。

一些自己的思想斗争现在看来奇奇怪怪，就不说了。

由于开了第二个号之后，后面的帖子中最大的都能拿下，那么我们需要动态地维护后面的帖子中，最大的而且能发出去的帖子的贡献和。

分段看代码解释。

---

首先答案的初值就是 easy version 中的答案。

```cpp
scanf("%d%d",&n,&k);

for(int i=1;i<=n;i++)
{
	scanf("%d",&a[i]);
	b[i]=a[i];
}
ans=a[1]+a[2]; sort(b+3,b+n+1);
for(int i=1;i<=k-2;i++) ans+=b[n-i+1];
```

接下来我们方便起见，倒序枚举每个帖子作为第二个号的第一个帖子。注意每个号都必须用到，那么太靠后的是不可能枚举到的。

```cpp
a1=a[1]; sum=0;//按要求把帖子全部塞给1，sum后面有用
for(int i=2;i<=n-k+1;i++) a1-=min(a[i],a[i-1]);
```

如何维护最大值和呢？数据结构维护。啥数据结构？堆就可以很好的维护，每次在插入堆和弹出堆顶的时候维护和就好了。

默认大根堆，需要转换一下。

```cpp
for(int i=n-k+3;i<=n;i++) {h.push(-a[i]); sum+=a[i];}
for(int i=n-k+2;i>1;i--)
{//不开 long long 见祖宗
	if(a1+1ll*a[i]+sum > ans) ans=a1+1ll*a[i]+sum;
	if(!h.empty() && a[i] > -h.top())
	{
		sum+=h.top(); h.pop(); sum+=a[i]; h.push(-a[i]);
	}
   //一开始就是最后一个，堆中是没有元素的
	if(h.empty()) {sum+=a[i]; h.push(-a[i]);}
   //维护的是后面的 k-2 个最大值，太多了就扔掉
	if((int)h.size() > k-2) {sum+=h.top(); h.pop();}
	a1+=min(a[i-1],a[i-2]);//复原
}
```

清空和输出答案就不放了，然后记得开 `long long` 。

***Thanks for your reading !***

---

## 作者：water_tomato (赞：1)

本文同步发表于个人博客：[Link](https://www.watertomato.com/p7878-%e3%80%8cswtr-07%e3%80%8dmy-rating-is-1064%ef%bc%88hard-version%ef%bc%89-%e9%a2%98%e8%a7%a3/)。

[题目链接](https://www.luogu.com.cn/problem/P7878)。

## 解析

首先第一个帖子肯定会由某一个账号发出。大力观察可以发现当第二个账号发帖之后，接下来一定可以至少两个账号交替发帖，即安全系数不再会有损失。我们仅需要解决第二个账号第一次发帖在哪一个位置即可。

假设我们确定了第二个账号第一次发帖的位置 $i$，那么剩下的 $k-2$ 个账号一定会在 $[i+1,n]$ 中选择 $k-2$ 的最大值进行发帖。因此，我们可以先将第二个账号第一次发帖的位置定在其最晚的可能的位置，然后向前递推。我们用一个堆维护除了第一个账号以外的 $k-1$ 个账号，每向前一个位置，我们就加上对应位置的损失值（这个损失不存在了），并且弹出堆中值最小的元素（不选它了），在强制选择该位置（即加入堆）。

这个过程中贡献值是容易维护的，详见代码（答案最后别忘了加上 $a_1$）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
const int inf=1e18;
int t,T,n,k,a[N];
priority_queue<int,vector<int>,greater<int> > q;
signed main(){
	scanf("%lld%lld",&t,&T);
	while(T--){
		scanf("%lld%lld",&n,&k);int now=0,ans=-inf;
		while(!q.empty()) q.pop();
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=1;i<=n-k;i++) now-=min(a[i],a[i+1]);//损失
		for(int i=n-k+2;i<=n;i++){now+=a[i];q.push(a[i]);}//先选这些元素
		ans=max(ans,now);
		for(int i=n-k+1;i>=2;i--){
			now+=min(a[i-1],a[i]);//减少损失
			now-=q.top();q.pop();//减去最小元素
			now+=a[i];q.push(a[i]);//加入当前元素
			ans=max(ans,now);//更新答案
		}
		printf("%lld\n",a[1]+ans);
	}
	return 0;
}
```

---

## 作者：intel_core (赞：1)

首先注意到 $a_i \ge 0$ ，所以如果开了两个账号之后同一个账号连续发帖的贡献就可以丢进垃圾桶了     

设第二个帖子第一次发帖时间为 $C$ ，那么 $1,2,3,....,C-1$ 将被连续发出，产生 $-\sum_{i=1}^{C-2}\min(a_i,a_{i+1})$ 的贡献，可以 $O(n)$ 处理出来    

接着考虑后面每个账号发出第一个帖子的贡献，根据咱们的最优策略，贡献一定是 $a_{C+1},....,a_n$ 中的前 $k-2$ 大数的和     

所以接下来问题变成了如何处理一个后缀前 $k$ 大的和    
方法有很多，主席树，$\text{CDQ}$ 之类的高级算法都可以    

但是如果你和我一样懒，不想手写，那么可以直接用 $\text{std::priority}$_ $\text{queue}$ ：
* 初始先把最后 $K-2$ 个数弹进堆里，并记录他们的和     
* 从后往前扫，每扫到一个数把和加上这个数，然后放到堆里   
* 最后把堆里最小的数弹掉，并把和减掉这个数    

总体复杂度 $O(n\log n)$ ，在 $O_2$ 的加持下超过了前述所有高级算法   

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
#define int long long
int a[NR],s[NR];
priority_queue<int,vector<int>,greater<int> >q;

signed main(){
	int t,T;cin>>t>>T;
	while(T--){
		int n,m;cin>>n>>m;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		if(m==1){
			int ans=a[1];
			for(int i=1;i<n;i++)ans-=min(a[i],a[i+1]);
			cout<<ans<<endl;
			continue;
		}
		while(!q.empty())q.pop();
		int sum=0;
		for(int i=1;i<=m-2;i++){
			q.push(a[n+1-i]);
			sum+=a[n+1-i];
		}
		memset(s,-999999,sizeof(s));
		s[n-m+3]=sum;
		for(int i=n-m+2;i>=1;i--){
			sum+=a[i];q.push(a[i]);
			sum-=q.top();q.pop();s[i]=sum;
		}
		int ans=-1e18,lcy=0;
		for(int i=2;i<=n;i++){
			ans=max(ans,a[1]+a[i]-lcy+s[i+1]);
			lcy+=min(a[i],a[i-1]);
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：do_while_true (赞：0)

特判掉 $k=2$．

显然，所有集合都用最优。

注意到如果用了 $x\geq 2$ 个集合，那么把剩下的数中最大的 $(k-x)$ 个单独放一个集合，多余的数，一定能选出一个集合来放进去使得不会对答案产生负贡献。

枚举第一个放入第二个集合是哪个元素 $x$，在它之前的一定放在同一个集合里面，这样我们再知道剩余 $(n-x)$ 个元素中最大的 $(k-2)$ 个是多少就可以快速计算这种放法的答案了，拿个 `multiset` 预处理一下即可。

容易发现这样做所有情况都考虑了进去，是不重不漏的。

时间复杂度大概是个 $\mathcal{O}(Tn\log n)$．

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 114514;
int n, k;
int a[N];
ll sum, ans, b[N];
void solve() {
	read(n); read(k); sum = 0;
	for(int i = 1; i <= n; ++i) read(a[i]), b[i] = 0;
	std::multiset<int>st;
	if(n == k) {
		for(int i = 1; i <= n; ++i) sum += a[i];
		printf("%lld\n", sum);
		return ;
	}
	k -= 2;
	if(k) {
		for(int i = n; i >= n-k+1; --i) sum += a[i], st.insert(a[i]);
		b[n-k] = sum;
		for(int i = n-k; i >= 3; --i) {
			if(*st.begin() < a[i]) {
				sum -= *st.begin();
				st.erase(st.begin());
				st.insert(a[i]);
				sum += a[i];
			}
			b[i-1] = sum;
		}
	}
	ans = sum = 0;
	sum = a[1];
	for(int i = 2; i <= n-k; ++i) {
		ans = Max(ans, sum + b[i] + a[i]);
		sum -= Min(a[i], a[i-1]);
	}
	printf("%lld\n", ans);
}
signed main() {
	int meishayong; read(meishayong);
	int T; read(T);
	while(T--) solve();
	return 0;
}
```

---

