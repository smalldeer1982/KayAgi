# 「SWTR-7」My rating is -32（easy version）

## 题目背景

#### 本题是 My rating is ... 的 easy 版本。注意题目限制和数据范围与 [hard](https://www.luogu.com.cn/problem/P7878) 版本不同。

#### 请注意特殊的时空限制，题目描述下方有简化题意。

[My rating is -32.](https://codeforces.com/blog/entry/71123)

说明：上方的帖子是机房里某个同学很久很久以前的黑历史，现在成了机房传世经典，不是为了出比赛才发的，请不要误会。

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

为此，小 A 新注册了 $k$ 个账号。他决定**按照从 $1$ 到 $n$ 的顺序**发出每篇帖子，并**用到所有 $k$ 个账号**。不过刷屏过多会引起 Mike 的注意并被封号，小 A 当然不希望这样：他进行了一些评估，得到了每篇帖子的安全指数 $a_i$，表示他发出第 $i$ 篇帖子后不被封号的概率。

由于第一印象非常重要，小 A 定义一个账号的安全指数为该账号所发出的**第一篇**帖子的安全指数。此外，如果**用同一个账号连续发出两个帖子**，Mike 会立刻封掉这个账号，因此这种情况**是不合法的**。

小 A 希望找到这样一个发帖方案，使得所有账号的安全指数之和最大。你只需要求出安全指数之和的最大值即可。

---

**「简化题意」**

将 $1\sim n$ **不重不漏**地分进 $k$ 个集合 $S_1,S_2,\cdots,S_k$ 中，满足**相邻的数不在同一集合** 且 $|S_i|>0$。求 

$$\sum_{i=1}^k a[{\min_{j\in S_i}j}]$$

的最大值，其中 $[]$ 表示**下标**。

## 说明/提示

**「样例 1 说明」**

小 A 只能使用账号 $1$ 发帖子 $1$ 和 $3$，剩下的帖子用账号 $2$ 发。其安全程度为 $a_{\min(1,3)}+a_{\min(2,4)}=2$。

**「数据范围与约定」**

本题共有 6 个测试点。

- Testcase #0（1 points）：是样例。
- Testcase #1（10 points）：$k=2$。
- Testcase #2（30 points）：$n\leq 10$，$k\leq 4$。
- Testcase #3（15 points）：$k=3$。
- Testcase #4（20 points）：$n\leq 64$，$k\leq 7$。
- Testcase #5（24 points）：无特殊限制。

对于 $100\%$ 的数据，$2 \leq k \leq n \leq 10^4$，$0 \leq a_i \leq 10^9$，$T=10$。  
对于所有测试点，**时间限制 200ms，空间限制 16MB。**

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/) B1。  
idea & solution：[tzc_wk](https://www.luogu.com.cn/user/115194)；data & 验题：[Alex_Wei](https://www.luogu.com.cn/user/123294)。

> **My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. My rating is -32. ……**
>
> **Upvote&emsp;-43&emsp;Downvote&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;PolarSea**  

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
2
12
5684074840```

# 题解

## 作者：cancan123456 (赞：7)

首先假设我们只有两个账号，那么只能这么发：12121212…（第i个数表示发第i个帖子的账号编号）

然后第一个数和第二个数是不能变的，然后假设我们又有了一个账号，那么我们肯定要选剩下的数中最大的。

所以我们对 $a_3-a_n$ 排序，取出最大的 $k-2$ 个数，加起来，然后再加上 $a_1+a_2$，就得到了答案。

Tips：开long long.

代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 10005
int a[maxn]; 
void inline solve() {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	long long ans = a[0] + a[1];
	sort(a + 2, a + n);
	for (int i = n - 1; i >= n - (k - 2); i--) {
		ans += a[i];
	}
	printf("%lld\n", ans);
}
int main() {
	int t;
	scanf("%*d %d", &t);
	for (int i = 1; i <= t; i++) {
		solve();
	}
	return 0;
}
```

---

## 作者：Cai_LJiu (赞：5)


### 题目解析：
小A有k个号要发贴，总共n条帖子，不能把连续的两条帖子发在同一个号上

要求每个号发的第一条的安全指数相加最高

---
### 思路：

先把前两条发出去，然后找到剩下的前k-2大的帖子相加就可以

因为剩下的如果是在前k大的里面，就可以拿别的号发，不是的话就用前两个号发

因为这题输入比较大，所以用上快读

---


AC代码：
```c
#include<bits/stdc++.h>
#define LL long long
#define LD long double
#define rep(a,b,c) for(int a=b;a<=c;++a)
inline int read()  //快读模板
{
 	int num=0;
 	char ch=getchar();
 	while(ch<'0'||ch>'9') 
	 	ch=getchar();
 	while(ch>='0'&&ch<='9')
 	{
  		num=(num<<1)+(num<<3)+ch-'0';
 	 	ch=getchar();
 	}
 	return num;
}
const int N=10010;  //2≤n≤10000 
using namespace std;
int main()
{
	LL a[N],ans;
	int t,T,n,k;
	cin>>t>>T;
	rep(i,1,T)
	{
		cin>>n>>k;
		rep(j,1,n)
			a[j]=read();//调用快读
		ans=a[1]+a[2];//先把前两条发出去
		a[1]=-1;//把a[1]和a[2]设到最小，方便下面快排
		a[2]=-1;
		sort(a+1,a+1+n);//快排
		rep(ccy,1,k-2)//找到剩下的前k-2大的帖子相加
			ans+=a[n+1-ccy];
		cout<<ans<<endl;
	}
	return 0;
}

```
---

---

## 作者：cyhyyds (赞：4)

根据测试点我们逐个讨论。

## Testcase #0
输出样例，不用我多说了吧。

## Testcase #1
$k=2$，也就是只有两个集合。

因为相邻的数不能放在一个集合，所以 $1$ 和 $2$ 不在同一个集合中。

那么，这两个集合中的最小值就分别为 $1$ 和 $2$。

所以，答案就是 $a_1+a_2$。

## Testcase #2
留给暴力的。

## Testcase #3

$k=3$，也就是只有三个集合。

当只有两个集合的情况下，前两个集合贡献的答案是固定的，于是我们只需要讨论第三个集合。

显然，我们可以构造出第三个集合中最小值分别为 $3$ 到 $n$ 的情况，因为当第三个集合中的最小值为 $mn$ 时，我们可以将 $3$ 到 $mn - 1$ 的数字分给第一个集合或者第二个集合。

所以第三个集合贡献的答案就是 $a_3$ 到 $a_n$ 的最大值。

所以，答案就是 $a_1+a_2+max_{a_3-a_n}$

## Testcase #4
留给复杂度好一点的暴力。

## Testcase #5

需要正解了。

当你做到 Testcase #3 时，正解其实已经离你不远了。

我们发现，前两个集合贡献的答案是固定的，也就是 $a_1+a_2$。

所以我们对剩下的 $k-2$ 个集合进行讨论。

猜想：剩下 $k-2$ 个集合的答案就是从大到小取 $k-2$ 个数。

于是你过了这道题。

至于为什么是这样呢？

首先按照上面的猜想将使答案最大的 $k$ 个数先填充进 $k$ 个集合。

显然，剩下的 $n-k$ 个数可以再放入这 $k$ 个集合中并且与集合中的任意一个数不相邻，且不影响答案。

因为对于剩下的 $n-k$ 个数中的任意一个数 $p$，都可以塞到第一个集合中，因为没有正整数比 $1$ 小，所以不影响答案。

所以正解的答案就是 $a_1+a_2$ 再加上前 $k-2$ 大的数，并且这前 $k-2$ 大的数不能是 $a_1$ 或 $a_2$。

## 核心代码

```
if (k == 2) {
	printf ("%lld\n", a[1].val + a[2].val);
}
	
else {
	int mx = -1;
       
    long long ans = a[1].val + a[2].val;
	
	sort (a + 1, a + 1 + n, cmp);//从大到小排序。 
			
	int tot = 0;
			
	for (int i = 1; i <= n; i ++) {
		if (a[i].id != 1 && a[i].id != 2) {//不取a1和a2。 
			ans += a[i].val;
				
			tot ++;
		}
				
		if (tot == k - 2) {
		//取了 k-2 个数。 
				
			break;
		}
	}
			
	printf ("%lld\n", ans);
}
```

按照子任务一步一步做真的好容易启发正解的思路！


---

## 作者：Infinity_Detail (赞：3)

一道挺简单的思维题。


------------


### 题意：
给你 $n$ 个帖子、 $k$ 个账号，每个帖子给你一个安全指数 $a_n$ ，要求两个账号不能连着发帖，求最大安全指数。

### 思路：
不难想到，因为同一个账号不能连续两次发帖，所以前两个帖子是必须用不同的账号来发的。也就是说，前两个帖子的安全指数（也就是 $a_1$ 和 $a_2$ ）一定要加在 $ans$ （存答案的变量）里。

然后，因为一个贴只能发一遍，发完安全指数就无效了，所以我们可以把 $a_1$ 和 $a_2$ 置为 $0$ .

接下来，已经发过帖的两个账号显然不能贡献答案了，而两个账号足以实现无限循环了（bushi）。所以以后一遇到小的数，就可以用这两个账号来发，一直反复发到遇到相对大的数，就用别的账号来发。而且可以很好地实现反复横跳，保证对答案的最大贡献。

到这一步，答案已经很明显了。

但是还有一个问题，怎么判断哪个数在这 $n$ 个安全指数里是相对大的呢？

很简单，我们从大到小排个序就行。

所以对于排序后的数组，答案就是：$\sum\limits_{i=1}^{k-2}a_i+ans$.

注意，这个数组 $a$ 到了 $1e9$ ，所以答案要记得开 long long 。

### 代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=a;i<=b;++i)
#define Rep(i,a,b) for(register int i=a;i>=b;--i)
using namespace std;
bool cmp(int a,int b){
    return a>b;
}
signed main(){
	int t,T;
	cin>>t;
	cin>>T;
	int n,k;
	int a[10005];
	For(i,1,T){
		cin>>n>>k;
		For(i,1,n){
			cin>>a[i]; 
		}
		long long ans=0;
		ans+=a[1];
		a[1]=0;
		ans+=a[2];
		a[2]=0;
		sort(a+1,a+n+1,cmp);
		For(i,1,k-2){
			ans+=a[i];
		}
		cout<<ans<<endl;
		continue;
	}
    return 0;
}
```
望通过~

---

## 作者：言琢დ (赞：3)

首先由题意，相邻的数不在同一集合 $S$。

所以 $a_1,a_2$ 必然分属两个集合。

所以 $a_1,a_2$ 必然产生贡献。

然后考虑怎么最大化剩下 $k-2$ 个集合 $S_i$ 的贡献。

那当然是让剩下 $n-2$ 个数中最大的 $k-2$ 个数产生贡献。

产生方法是，剩下 $k-2$ 个集合每个集合塞一个数。

然后 $n-2-(k-2)=n-k$ 个数全部扔到 $S_1$ 里面去，它们都比 $a_1$ 大，显然不产生贡献。

计算答案的方法非常简单：就是 $a_1+a_2+\text{剩下}k-2\text{个最大的}a_i$ 就可以。

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
inline int in();
inline void wr(int);
const int N=(int)1e4+5;
int a[N];
signed main(signed argc,char**argv){
#ifndef ONLINE_JUDGE
	freopen("7874.in","r",stdin);
	freopen("7874.out","w",stdout);
#endif
	/*
	相邻的数不在同一集合，所以 a1 a2 一定产生贡献；
	其他的 k-2 个项全部取最大的，扔到不同集合中即可；
	多余的全部扔到 S1 集合中用于废弃即可；
	*/
	register int t=in();
	register int T=in();
	while(T--){
		register int n=in(),k=in();
		for(register int i=1;i<=n;++i)
			a[i]=in();
		register int s=a[1]+a[2];
		std::stable_sort(a+3,a+1+n);
		for(register int j=n;j>=n-k+3;--j)
			s+=a[j];
		wr(s),putchar('\n');
	}
}
inline int in(){
	register char c=getchar();
	register int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	return x*f;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)wr(x/10);
	putchar(x%10+'0');
}
```

---

## 作者：MY（一名蒟蒻） (赞：2)

[P7874 「SWTR-07」My rating is -32（easy version）](https://www.luogu.com.cn/problem/P7874)

简单签到题。

我还是觉得读原题面更好理解。

由于在本题中，同一账号连续发出两个帖子不合法，那么第一个和第二个一定发在两个不同的账号当中。答案累加这两帖的安全指数。

然后在剩下的帖子中选取安全指数最大的 $k-2$ 个统计进答案即可。

为啥？因为比较小的我显然可以找到一个垃圾桶丢，使得没有一个账号连续发出两个帖。

时限 200ms ,空限 16MB ， $n\ 10^4$ 级别，无脑 `sort` 就可以了。

感谢阅读！

---

