# Alice and Bob are playing a Normal Game

## 题目描述

给定一个长度为 $n$ 的序列，Alice 和 Bob 交替操作一共 $k$ 次，第 $i$ 次当前操作的人必须选一个 $-x_i \sim x_i$ 的整数把它插在序列开头或结尾，Alice 先手（也就是说 $i$ 为奇数时由 Alice 来插入一个 $-x_i\sim x_i$ 的整数，$i$ 为偶数时由 Bob 来插入一个 $-x_i\sim x_i$ 的整数）。

记最终的序列为 $a_1,a_2,\dots,a_{n+k}$，则得分为 $\sum_{i=1}^{n+k} (-1)^{i-1}a_i$。Alice 希望得分最大，Bob 希望得分最小。在两人都采取最优策略的情况下，求最终得分。

## 说明/提示

**本题采用捆绑测试**

| 子任务编号 | 分值 | 特殊限制 |
| :----------: | :----------: | :----------: |
| $0$ | $25$ | $n,k,x_i\le 5$ |
| $1$ | $25$ | $n,k\le 10$ |
| $2$ | $25$ | $n,k\le 100$ |
| $3$ | $25$ | 无特殊限制 |

对于所有数据，保证 $1\le n,k\le 2\times 10^5$，$0\le |a_i|,x_i\le 10^9$。

本题测试点较多，为了保证评测速度，本题时限 500ms，保证时限在 std 所用最大时间的 5 倍以上。

## 样例 #1

### 输入

```
2 2
1 3
2 2```

### 输出

```
-2```

# 题解

## 作者：VinstaG173 (赞：7)

一个挺有意思的题。

注意到当目前的总和绝对值是 $t$，新加入的数在 $[-x,x]$ 中的时候我们能够得到的值只能在 $[-x-t,x-t] \cup [-x+t,x+t]$ 中且能取遍其中任意整数。这个值域是关于 $0$ 对称的。

因此无论谁是最后操作者都想要最终绝对值最大，只要按照自己的要求取正负就可以了。故我们知道最后一个人肯定会选择 $-x_k-t$ 或 $x_k+t$，而其对手希望让这个绝对值尽可能小。由于 $x_k$ 给定，因此只要让 $t$ 尽可能小。这样讨论下去我们就会发现最后一个人会一直选择将绝对值从 $t$ 变成 $t+x_i$，其对手会一直选择将绝对值从 $t$ 变成 $\max\{t-x_i,0\}$。因此我们只要照此模拟即可。时间复杂度 $O(n)$。

Code:
```cpp
#include<cstdio>
#define rg register
#define ll long long
int n,k,x,t;ll r;
int main(){
	n=read(),t=k=read();for(rg int i=0;i<n;++i){
		x=read(),r+=((i&1)?-x:x);
	}if(r<0)r=-r;while(k--){
		x=read(),r=(k&1)?((r>x)?(r-x):0):(r+x);
	}return 0&printf("%lld\n",(t&1)?r:-r);
}
```

---

## 作者：stntn (赞：6)

### 题意
Alice 和 Bob 交替操作一个序列，在两人采取最优策略的情况下求最终结果

### 分析
考察式子 $\sum_{i=1}^{n+k} (-1)^{i-1}a_{i}$ 容易发现，当某数处于奇数位时，该数对结果产生正贡献，偶数位则负。

基于以上结论我们观察玩家的操作：

##### 操作一：在序列末尾加上某个数

对于该操作，易发现其贡献仅取决于数的大小、符号和位置，由于数字可以在 $-x_{i}\sim x_{i} $ 间选取，故**总有一种办法可以使其对己方产生正贡献。**

##### 操作二：在序列开头加上某个数

该操作会对整个序列产生位移，导致**已有的正负贡献交换**，且由上分析可知，总有一种办法可以使其在第一位的数对己方产生正贡献。

接着我们分析操作先后对结果的影响，易发现，最后一轮的玩家总可以~~扭转乾坤~~通过进行**操作二**将优势转为己方，并且加入一个对己方有正贡献的数。

到这里分析就差不多完毕了，我们可以做出如下结论：

- 对于最后操作的玩家（winner）在整场游戏中所要做的就是**尽量拉大正负贡献之差距**
- 对于非最后操作的玩家（loser）只能**尽量减小正负贡献之差距**

### 注意事项

- $-x_{i}\sim x_{i} $ 可以选取两端及中间的数~~卡了我好久~~
- 要开 long long

## code
```cpp
#include<bits/stdc++.h>
#define N 200010
#define re register
#define int long long
using namespace std;
template <typename T> inline void read(T &a)
{
	T x=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	a=x*w;
}
int n,k,a[N],x,len;
int p[2];//1正 0负 
bool flag;

inline void work_loser(bool v)
{
	if(abs(p[0]-p[1])<=x)
	{
		if(len&1) p[1]=p[0];
		else p[0]=p[1];
		return;
	}
	if(p[1]>=p[0])
		if(len&1) p[1]-=x;
		else p[0]+=x;
	else
		if(len&1) p[1]+=x;
		else p[0]-=x;
}

inline void work_winner(bool v)
{
	if(p[v^1]>p[v])
		swap(p[v^1],p[v]),
		v ? p[1]+=x : p[1]-=x;
	else
		if(len&1) v ? p[1]+=x : p[1]-=x;
		else v ? p[0]-=x : p[0]+=x;
}

signed main()
{
	read(n);read(k);
	for(re int i=1;i<=n;i++)
	{
		read(a[i]);
		i&1 ? p[1]+=a[i] : p[0]+=a[i];
	}
	len=n+1;
	if(k&1) flag=1;//A win
	else flag=0;//B win
	for(re int i=1;i<=k;i++)
	{
		read(x);x=abs(x);
		if(i&1)
			if(flag) work_winner(1);
			else work_loser(1); 
		else
			if(flag) work_loser(0);
			else work_winner(0); 
		len++;
	}
	printf("%lld\n",p[1]-p[0]);
	return 0;
}
```


---

## 作者：Level_Down (赞：3)

首先来分析一下每次操作可以造成的效果：

设原有数列的得分为 $a$，插入的数值为 $t$。

假设加在首位，现有数列的得分为 $t - a$。

假设加在尾位，现有数列的得分为 $a + t$ 或 $a - t$。

然后因为 $t$ 的值在 $[-x_i,x_i]$。

综合起来，我们发现每一次操作我们可以把原有数列的得分随意取正或取反，再加上一个值在 $[-x_i,x_i]$ 区间内的数。

再思考题目中所谓的**最优策略**是什么：

首先排除每次操作只考虑自己最终任务的局部最优策略。

然后我们发现每个人每局的最优策略和这场比赛中最后一个进行操作的人是谁有关。

假如最后一个人是 Alice，那么 Bob 每局操作的目的就是要让 Alice 最后一局**能变出的最大值最小**。

我们再回到每次操作的效果，由于 $x_k$ 的值是固定的，那么显然，Bob 的操作就是要让原得分取正或是取反的幅度最小，也就是让原得分的**绝对值最小**。

反之，Alice 就是要让原得分的绝对值最大。

当最后一人是 Bob 时，上述操作的人选就互相调换，也就是最后做出操作的人要让原得分的绝对值最大，另一人要让原得分的绝对值最小。

**然后切记要开 long long！**

至此，按照上述思路模拟即可。

易懂的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[200005];
long long ans,x,p = 0;
bool flag;
inline int read(){
   register int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main()
{
	n = read(),k = read();
	for (int i = 1; i <= n; i++)
		{
			x = read();
			if (i & 1) ans += x;
			else ans -= x;
		}
	if (k & 1) flag = true;	
	ans = abs(ans);
	for (int i = 1; i <= k; i++)
		{
			x = read();
			if (i == k) {
				if (flag) ans += x;
				else ans = -ans - x;
				continue;
			}
			if (i & 1) {
				if (flag) ans += x;
				else ans = max(p,ans - x);
			} else {
				if (!flag) ans += x;
				else ans = max(p,ans - x);
			}
		}
	printf("%lld",ans);	
	return 0;
}
```


经过删减的简洁代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[200005],x,f = 1;
long long ans,p = 0;
int main()
{
	scanf("%d%d",&n,&k);
	for (int i = 1; i <= n; i++){
		scanf("%d",&x);
		if (i & 1) ans += x;
		else ans -= x;
	}
	ans = abs(ans);
	if (k & 1) f = 0;
	for (int i = 1; i < k; i++){
		scanf("%d",&x);
		if ((i + f) & 1) ans += x;
		else ans = max(p,ans - x);
	}
	scanf("%d",&x);
	if (!f) printf("%lld",ans + x);
	else printf("%lld",-ans - x);	
	return 0;
}
```


---

## 作者：WER_very_fox (赞：3)

拿到题目后可看出，无论怎么加数都无法改变初始序列的绝对值大小，于是先算出初始序列的绝对值，记为 $s$。  

再读题目发现，最后一个操作的人有优势，可以决定最终结果的正负，于是 TA 只要让序列的绝对值更大即可，而另一个人则是让序列绝对值更小。  

于是我们分情况讨论：  

$k\bmod2=1$ 时：  
Alice 最后操作，想让序列绝对值更大，则每次操作后绝对值变为 $s+x_i$。  
Bob 想让序列绝对值更小，则每次操作当 $s>x_i$ 时，将绝对值变为 $s-x_i$；反之，将绝对值变为 $0$。  
最后输出 $s$ 即可。

$k\bmod2=0$ 时，同理，最后输出 $-s$。  

AC code:
```cpp
#include<cstdio>
#define ll long long
using namespace std;
ll n,k,a,s;
int main()
{
	ll i;
	scanf("%lld%lld",&n,&k);
	for(i=1;i<=n;i++)
		if(i%2)
			scanf("%lld",&a),s-=a;
		else
			scanf("%lld",&a),s+=a;
	s=s>0?s:-s;
	if(k%2)
	{
		for(i=1;i<=k;i++)
			if(i%2)
				scanf("%lld",&a),s+=a;
			else
			{
				scanf("%lld",&a);
				if(a>=s)
					s=0;
				else
					s-=a;
			}
		printf("%lld",s);
	}
	else
	{
		for(i=1;i<=k;i++)
			if(i%2==0)
				scanf("%lld",&a),s+=a;
			else
			{
				scanf("%lld",&a);
				if(a>=s)
					s=0;
				else
					s-=a;
			}
		printf("%lld",-s);
	}
	return 0;
}
```


---

## 作者：Gao_yc (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8002)

### $ \mathcal{Solution} $：

我们对于每次操作，记录下操作后的得分。

于是我们可以这样理解第 $i$ 次的操作：选择 $ans$（上一次操作后的得分）的正负性并加上一个 $-x_i \sim x_i$ 的数。

首先我们考虑找到最优策略，然后每次操作从第 $1$ 次到第 $k$ 次跑一遍直接计算答案。

那么最优策略是什么呢？贪心让每次答案的绝对值最大显然是最好想到的。但是有一个非常重要的性质：**最后一个进行操作的人可以选择最终答案的正负性**。这就意味着另外一个人的最优策略并不是让绝对值最大，而是最小（不然你无论多么努力把答案的绝对值加到了极大，还是给对方帮忙）。

所以不是最后一个操作的人的最优策略是使答案接近于 $0$。

于是贪心算法就很明了了。

代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e6;
int n,k,x;
int read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ans=(ans<<1)+(ans<<3)+(ch^48);
		ch=getchar();
	}
	return ans*f;
}
long long ans;
long long max(long long a,long long b)
{
	return a>b?a:b;
}
int main()
{
//	freopen("","r",stdin);
//	freopen("","w",stdout);
	n=read();k=read();
	int aa;
	for(int i=1;i<=n;++i)
	{
		aa=read();
		if(i&1) ans+=aa;
		else ans-=aa;
	}
	if(k&1)
	{
		for(int i=1;i<=k;++i)
		{
			x=read();
			if(i&1) ans=abs(ans)+abs(x);
			else ans=max(0,abs(ans)-abs(x));
		}
		ans=abs(ans);
	}
	else
	{
		for(int i=1;i<=k;++i)
		{
			x=read();
			if(i&1) ans=max(0,abs(ans)-abs(x));
			else ans=abs(ans)+abs(x);
		}
		ans=-abs(ans);
	}
	printf("%lld",ans);
    return 0;
}
```


---

## 作者：CSP_Sept (赞：1)

### Solution

题意很简洁了，考虑贪心。

我们考虑最后一个操作的人，如果是 Alice。

那么 Alice 就要在过程中让得分尽可能大，而 Bob 知道自己已经无力控制局面，他会让 Alice 的得分尽可能小。

具体地，若 Alice 拿到得分 $sum$，那么他会让得分变成 $|sum|+x_i$。而 Alice 的得分变小，当且仅当 $|sum|$ 变小。

所以 Bob 要让得分的绝对值尽可能小。考虑用 Bob 手上的 $x_i$ 把 $|sum|$ 降下来。

记 $R=|sum|$。若 $x_i\ge R$，显然 $sum\in[-x_i,x_i]$，于是 Bob 就可以取 $sum$ 把得分降为 $0$。否则，就降成 $R-x_i$。显然这是可以实现的，并且这是可能达到的最能符合要求的值。

而对于 Bob 最后一个操作，同上分析，我们有如下方案：

- 若 Bob 拿到得分 $sum$，那么他会让得分变成 $-|sum|-x_i$。
- 而 Alice 会把得分降为 $\max(0,R-x_i)$。

### Code

```cpp
#include <bits/stdc++.h>

#define N 200010
#define ll long long
using namespace std;
inline int rd();
int a[N], x[N];
int n, k;
ll sum = 0;
int op(int ind){ return ind & 1 ? 1 : -1; }
ll ab(ll k){ return k > 0 ? k : -k; }
int main(){
	n = rd(), k = rd();
	for(int i = 1 ; i <= n ; i++)
		a[i] = rd(), sum += op(i) * a[i];
	for(int i = 1 ; i <= k ; i++){
		x[i] = rd();
		if(i & 1){
			if(k & 1)
				sum = ab(sum) + x[i];
			else
				sum = ab(sum) < x[i] ? 0 : ab(sum) - x[i];
		}
		else{
			if(k & 1)
				sum = ab(sum) < x[i] ? 0 : ab(sum) - x[i];
			else
				sum = -ab(sum) - x[i];
		}
	}
	printf("%lld\n", sum);
	return 0;
}
inline int rd(){
	char c;
	bool flag = 0;
	while((c = getchar()) < '0' || c > '9')
	    if(c == '-') flag = 1;
	int res = c - '0';
	while((c = getchar()) >= '0' && c <= '9')
	    res = (res << 3) + (res << 1) + c - '0';
	return flag ? -res : res;
}
```

---

## 作者：IYSY2009I (赞：0)

> 在很长时间之后（注：本文写于 2022 年 7 月 12 日），我已经不知道我是如何在考场上被这道题降智的了——题记

这个游戏只有两种操作：

1. 向结尾插入一个数
2. 向开头插入一个数

那么我们就分别来考虑这两种操作的特性。

首先，我们来考虑向结尾插入一个数。设插入前的得分为 $ans$，插入的数为 $x$，则插入后的分数为 $ans+x$。

我们再来考虑向开头插入一个数。设插入前的得分为 $ans$，插入的数为 $x$，则插入后的分数为 $-ans+x$。

举个例子：$a=\{1,3\},x=2$，则原来的得分为 $(-1)^{1-1} \times 1+(-1)^{2-1} \times 3=-2$，若将 $x$ 插入前面，得分为 $(-1)^{1-1} \times 2+(-1)^{2-1} \times 1+(-1)^{3-1} \times 3=4$，若将 $x$ 插入后面，得分为 $(-1)^{1-1} \times 1+(-1)^{2-1} \times 3+(-1)^{3-1} \times 2=0$，符合上面说的规律。

我们惊喜地发现，最后一个人是可以决定得分的正负性的。因为当得分 $>=0$ 时，它可以通过在前面插入一个负数使得分 $<0$ 或在后面插入一个正数使得分 $>0$；当得分 $<=0$ 时，它可以通过在前面插入一个正数使得分 $>0$ 或在后面插入一个负数使得分 $<0$。

我们这个时候再来考虑最优策略：假设 Bob 进行最后一次操作，即 $k \bmod 2=0$。那么作为 Bob，显然希望这个得分为负。当然，由于 $x_i=0$ 的存在，可能会出现最终得分为 $0$ 的情况。这时如果当前得分 $=ans$，很显然最小得分是：

$$\begin{cases} ans-x_i & ans \leq 0 \\ -ans-x_i & ans>0 \end{cases}$$

$$=-|ans|-x_i$$

我们发现，最后的得分仅与 $ans$ 的绝对值有关：当 $ans$ 的绝对值越大，得分越小；当 $ans$ 的绝对值越小，得分越大。所以 Alice 的最优策略就是每一次操作都尽可能的使 $ans$ 的绝对值变小，Bob 的最优策略就是每一次操作都尽可能的使 $ans$ 的绝对值变大并在最后一步使 $ans \le 0$。

Alice 为先手的时候同理，大家自己推推。

最后我用自己的亲身经历证明了不开 $\texttt{long long}$ 是会见祖宗的。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
long long ans;
int k;
void Alice(){
	for(int i=1;i<=k;i++){
		long long x=read();
		if(i%2){
			if(ans<0) ans-=x;
			else ans+=x;
		}
		else{
			if(ans<0){
				ans+=x;
				if(ans>0) ans=0;
			}
			else{
				ans-=x;
				if(ans<0) ans=0;
			}
		}
	}
	printf("%lld",abs(ans));
	return;
}
void Bob(){
	for(int i=1;i<=k;i++){
		long long x=read();
		if(i%2){
			if(ans<0){
				ans+=x;
				if(ans>0) ans=0;
			}
			else{
				ans-=x;
				if(ans<0) ans=0;
			}
		}
		else{
			if(ans<0) ans-=x;
			else ans+=x;
		}
	}
	printf("%lld",-abs(ans));
	return;
}
int main(){
	int n=read();
	k=read();
	for(int i=1;i<=n;i++){
		if(i%2) ans+=read();
		else ans-=read();
	}
	if(k%2) Alice();
	else Bob();
	return 0;
}
```


---

## 作者：听取MLE声一片 (赞：0)

做这题并不需要什么博弈论之类的。

首先将两个操作简化，由最终统计结果的方式来看，假设现在序列算出来的结果是 $m$，把一个数放在开头就是把所有数取相反数，就可以更改为 $-m$；放在最后就是维持前面所有数不变，还是 $m$。又因为可以插入正数和负数，所有插入的数的符号就不需要考虑了。所以，假设目前的结果为 $m$，$p$ 为  $-x_i\sim x_i$ 的任意一个整数，我们就可以这样简化操作：

>1.将结果变为 $m+p$。

>1.将结果变为 $m-p$。

由此可以发现，最后一个操作的人可以决定结果，因为Ta可以决定最后的符号。因为Ta可以决定符号，所以他会使过程中 $|m|$ 尽可能大，而另一个人会使 $|m|$ 尽量小。

最关键的是，如果另一个人手中的数 $x_i$ 的**绝对值不小于** $m$ 的**绝对值**，那么另一个人就可以将其变为 `0`。

注：这里Ta指最后操作的人，另一个人指不最后操作的人，可以用 `k` 的奇偶性判断。

代码就很好实现了：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
int n,k,a[N],b[N],m;
signed main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();//可以不要
		if(i%2==1)
			m-=a[i];
		else m+=a[i];
	}
	for(int i=1;i<=k;i++)
		b[i]=read();
	if(k%2==1){
		for(int i=1;i<k;i++){
			if(i%2==1){
				m=abs(m)+b[i];
				continue;
			}
			if(abs(m)<=b[i]){
				m=0;
				continue;
			}
			m=abs(abs(m)-b[i]);
		}
		m=abs(m)+b[k];
		cout<<m;
		return 0;
	} 
	for(int i=1;i<k;i++){
		if(i%2==0){
			m=abs(m)+b[i];
			continue;
		}
		if(abs(m)<=b[i]){
			m=0;
			continue;
		}
		m=abs(abs(m)-b[i]);
	}
	m=-abs(m)-b[k];
	cout<<m;
	return 0;
}

```


---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8002)

## 题意

一开始有一个序列 $a_1,a_2,…,a_n$，记此时的 $ans$ 为 $\sum_{i=1}^n(-1)^{i-1}a_i$，接下来有一个**公开**的非负整数操作序列 $x_1,x_2,…,x_k$，即 Alice 和 Bob 都知道。

接下来 Alice 和 Bob 交替操作一共 $k$ 次，Alice 先，第 $i$ 次操作为使 $ans$ 变为 $p\pm ans(-x_i\le p\le x_i)$。

Alice 希望最后的 $ans$ 最大，而 Bob 希望最后的 $ans$ 最小，在两人都采取最优策略的情况下，求出最后的 $ans$。

## 分析

乍一看好像是 $\text{Alpha-Beta}$ 剪枝，然而 $1≤n,k≤2×10^5
,0\le |a_i|,x_i\le 10^9$ 的范围是过不了的。

------------

于是我们考虑自己当一回 Alice & Bob ~~精神分裂~~：

#### $\text{Round 1 \ \ }k=1$

>- Alice：天助我也，Bob 什么都做不了，我只要使答案最大就可以了，$ans\Longleftarrow x_1+\left|ans\right|$。

#### $\text{Round 2 \ \ }k=2$

>- Alice：最后一次操作是 Bob 执行的，不论我这轮操作后 $ans$ 的大小如何，Bob 都可以通过 $ans\Longleftarrow -x_2-\left|ans\right|$ 使最后的结果尽可能小，既然这样，我只要使 $\left|ans\right|$ 尽可能小就可以了，如果 $\left|ans\right|\le x_1$，显然可以使它变为 $0$，否则最小只能变成 $\left|ans\right|-x_1$ 了。
>- Bob：我现在掌握着最后一轮的结果，要使答案尽可能小， 只要 $ans\Longleftarrow -x_2-\left|ans\right|$，无论如何答案都是最小的。

#### $\text{Round 3 \ \ }k=3$

>- Alice：最后一次操作是我执行的，那是我会使 $ans\Longleftarrow x_3+\left|ans\right|$，所以我只要使 $\left|ans\right|$ 尽可能大就好了，$ans\Longleftarrow x_1+\left|ans\right|$。
>- Bob：局势对 Alice 十分有利，她最后得到的答案与 $\left|ans\right|$ 有关，所以我还是要使其尽可能小，如果 $\left|ans\right|\le x_2$，显然可以使它变为 $0$，否则最小只能变成 $\left|ans\right|-x_2$ 了。
>- Alice：该做什么就显而易见了，$ans\Longleftarrow x_3+\left|ans\right|$。

------------

不难发现，Alice 和 Bob 所做的举动和 $k$ 的奇偶性有关：

- $k\bmod 2=1$：Alice 每次使 $\left|ans\right|$ 最大，Bob 每次使 $\left|ans\right|$ 最小。
- $k\bmod 2=0$：Alice 每次使 $\left|ans\right|$ 最小，Bob 每次使 $\left|ans\right|$ 最大。

于是按题意模拟即可，时间复杂度 $O(n+k)$，空间复杂度 $O(1)$。

## 代码
  
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=2e5+10;
int n,k;
ll ans,x;
ll minabs(ll a,ll b){//ans绝对值的最小值
	if(abs(a)<=b)
		return 0;
	return abs(a)-b;
}
int main(){
	n=read();k=read();
	for(int i=1;i<=n;i++)
		ans+=(read()*(i%2?1:-1));
	if(k%2)
		for(int i=1;i<=k;i++){
			x=read();
			if(i%2)
				ans=x+abs(ans);
			else
				ans=minabs(ans,x);
		}
	else
		for(int i=1;i<=k;i++){
			x=read();
			if(i%2)
				ans=minabs(ans,x);
			else
				ans=-x-abs(ans);
		}
	write(ans);
	return 0;
}
```


---

