# [POI 2014] BAR-Salad Bar

## 题目描述

Bytea went to a salad bar.

There are $n$ fruits one next to another on the bar counter.

Specifically, these are apples and oranges.

Bytea can pick any contiguous part of the line of fruits for her salad.

The fruits she chooses will be added to the salad either from left to right or from right to left.

As Bytea loves oranges, she requires that throughout the salad making process, the number of oranges    in it should always be no smaller than the number of apples, regardless of whether these are added %    from left to right or from right to left.

Help Bytea out by writing a program that will find the longest contiguous part of the line of fruits    that satisfies her requirements.

有一个长度为n的字符串，每一位只会是p或j。求一个最长子串，使得不管是从左往右还是从右往左取，都保证每时每刻已取出的p的个数不小于j的个数。


## 说明/提示

有一个长度为n的字符串，每一位只会是p或j。求一个最长子串，使得不管是从左往右还是从右往左取，都保证每时每刻已取出的p的个数不小于j的个数。


## 样例 #1

### 输入

```
6
jpjppj
```

### 输出

```
4
```

# 题解

## 作者：bztMinamoto (赞：11)

[传送门](https://www.luogu.org/problemnew/show/P3564)

我是来帮楼下加藤大佬写题解的……全世界都没找到加藤大佬写法的说明……很难受……

首先我们把$p$看成$1$，$j$看成$-1$，一个区间满足条件就意味着这个区间的所有前缀和都大于等于$0$，所有后缀和都大于等于$0$

我们记录一下前缀和，所有前缀和大于等于$0$就是$sum[i]-sum[l-1]\geq  0$，所有后缀和都大于等于$0$就意味着$sum[n]-sum[i-1]\geq sum[n]-sum[r]$，即$sum[i-1]\leq sum[r]$，然后因为$sum[r]\geq sum[l-1]$已经在第一个条件里满足了，所以合起来就是$sum[i]\geq sum[l-1]$，$sum[r]\geq sum[i]$。用人话说，一个区间满足条件，那么这个区间内的$sum$都不小于$sum[l-1]$且$sum[r]$是这个区间中最大的数

于是我们定义$to[i]$，意思是$[i,to[i]]$中的所有数都大于等于$sum[i]$，且$sum[to[i]]$为这个区间中最大的数，$to[i]$为所有满足条件的数中最靠右的。那么我们就可以枚举左端点$i$，如果$s[i]==j$这个左端点肯定不行，否则这个左端点能匹配的最大的右端点就是$to[i-1]$

现在的问题就是怎么求出$to[i]$了，我们一开始先把所有的$to[i]$都赋值为$i$，这样到时候可以少讨论一些边界情况。

首先，如果$sum[i+1]<sum[i]$，即$s[i+1]$为$p$，那么$to[i]$只能等于$i$，因为它的下一个就小于它了。所以我们只考虑讨论$s[i+1]$为$j$的情况

我们考虑从后往前做，定义$nxt[i]$为它后面的第一个与它$sum$相等的位置，记录一个指针$las$，表示每一次的$to[i]$，现在做到了$i$，那么$las$应该是指在$to[i+1]$的位置。

那么转移会有两种情况

1.$to[i]=to[i+1]$，那么直接转移即可
![](https://i.loli.net/2018/11/16/5beecffa819e5.png)
2.$to[i]$变大。比如图中，$k$的位置才是$to[i]$
![](https://i.loli.net/2018/11/16/5beed07a0d603.png)
我们发现，在本题中，相邻两个数的值最多只会相差$1$，于是若是存在如图$2$的情况，那么必然存在$nxt[i]$。不难证明$[i+1,nxt[i]-1]$区间内的数肯定同时大于$sum[i]$或同时小于$sum[i]$，如果全都小于那么有$sum[i+1]<sum[i]$，我们之前已经处理掉了。所以$[i+1,nxt[i]-1]$之间的数必然全都大于$sum[i]$。因为$to[nxt[i]]$已经求出来了，如果$sum[to[nxt[i]]]\geq sum[las]$，我们可以把$[i,nxt[i]-1]$这一段给接上去，那么新的区间$[i,to[nxt[i]]]$肯定还是满足条件的，且不难证明不存在比它更优的。这种情况下我们让$las$指向$to[nxt[i]]$并更新$to[i]$即可。

只要处理出$[0,n-1]$的所有的$to[i]$就可以了，最后的答案就是$max\{to[i-1]-i+1\}(s[i]==p)$，时间复杂度$O(n)$

代码看楼下加藤大佬的好了

---

## 作者：foreverlasting (赞：11)

现在被迫开始刷Poi的所有题，发现这题洛谷没有题解，那我就发一波。

网上很多题解感觉都好复杂，要树状数组，单调栈，二分什么的。这里介绍一种思路：我们把**p**看做**1**，**j**看做**-1**。这样的话，对于这题所谓的从左从右取都是p的个数大于等于j的个数的条件就可以转变为前缀和和后缀和的所有值都大于等于0.然后找一段这样子的最长区间。

记前缀和为sum。
而对于一个合法的区间[l,r]，一定会有sum[l]<=sum[i]<=sum[r](l<=i<=r)

所以求出每一个点i对应的最远的满足条件的长度就行了。

code：
```
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(res x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
inline int _max(res x,res y){
    return x>y?x:y;
}
inline int _min(res x,res y){
    return x>y?y:x;
}
const int N=1e6+10;
int n,sum[N],minx;
int head[N],nxt[N],to[N];
char str[N];
int main(){
	memset(head,-1,sizeof(head));
	n=read();
	scanf("%s",str+1);
	for(res i=1;i<=n;i++){
		sum[i]=sum[i-1]+(str[i]=='p'?1:-1);
		minx=_min(minx,sum[i]);
	}
	for(res i=n;i>=0;i--){
		res x=sum[i]-minx;
        nxt[i]=head[x],head[x]=i,to[i]=i;
	}
	res ans=0;
    for(res i=n,pre=n;i>=1;i--){
        if(str[i]=='j')pre=i-1;
        else {
            if(nxt[i-1]>=0&&sum[to[nxt[i-1]]]>=sum[pre])pre=to[nxt[i-1]];
            to[i-1]=pre;
            res pos=pre-i+1;
            ans=max(pos,ans);
        }
    }
    write(ans);
    return 0;
}
```

---

## 作者：qyy_abc (赞：6)

前置知识：前缀和，单调栈，线段树上二分。

对原序列进行一个处理，将 `p` 当成 $1$，`j` 当成 $-1$，进行前缀和，设前缀和数组为 $a_i$。

对于一个满足题目条件的区间 $[l,r]$，$l$、$r$ 显然满足：

- $a_{l-1} \le \min_{i=l}^{r} a_i$

- $a_{r} \ge \max_{i=l}^{r} a_i$

扫一遍 $a$ 来枚举 $l-1$，找出最大的 $r$，满足上述两个限制，即 $a_{l-1}$ 小于等于区间 $[l-1,r]$ 最小值，$a_{r}$ 为区间 $[l,r]$ 最大值。

设当前扫到的位置是 $i$。考虑第一个限制怎么满足。设满足该限制的最远的点下标为 $lim$，发现 $lim$ 具有单调性（若 $lim$ 满足该限制，则 $lim-1$ 也一定满足该限制），可以使用线段树上二分。

> 线段树上二分大概的具体过程：
>
> 维护一个支持区间求 $min$ 的线段树，所有点初始值为 $inf$。
>
> 修改正常写。查询的时候，设当前线段树节点为 $p$，当前节点的左儿子为 $ls$，当前节点的右儿子为 $rs$，区间维护的最小值为 $mn$，查询的值为 $val$。
>
> > 当 $val \le tr[ls].mn$：说明 $val$ 是 $ls$ 维护区间的最小值了，故递归查询 $rs$；
> >
> > 否则，说明 $val$ 已经不是 $ls$ 维护区间的最小值，右端点不在 $ls$ 维护的区间内，递归查询 $ls$。
>
> 扫完一个点后，将它更新到线段树中。
>
> 因为所有点的初始值是 $inf$，所以保证了查询的时候 $i$ 之前的区间不对查询造成影响，最小只会查询到 $i$。

发现查询出的 $r$ 不一定满足第二个限制。怎么办？

考虑在扫的过程中，用单调栈维护满足第二个限制的 $r$。在扫到 $i$ 的时候，在单调栈中二分找出 $\le lim$ 的最大的 $r$。以 $i$ 为 $l-1$ 的最长符合题目条件的区间即为 $[i+1,r]$。扫的过程中，$ans$ 不断与算出的区间长度取 $max$ 即可。

注意 $l=1$ 的情况也要计算。

时间复杂度为 $O(n \log n)$，瓶颈在线段树上二分。

AC code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1000004;
int n;
int a[maxn];
namespace Segtree{
	struct node{
		int l,r;
		int mn;
	}tr[maxn<<2];
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid (tr[p].l+tr[p].r>>1)
	void build(int p,int l,int r){
		tr[p].l=l,tr[p].r=r;
		tr[p].mn=maxn;
		if(l==r) return;
		build(ls,l,mid);build(rs,mid+1,r);
	}
	void upd(int p,int loc,int val){
		tr[p].mn=min(tr[p].mn,val);
		if(tr[p].l==tr[p].r) return;
		if(loc<=mid) upd(ls,loc,val);
		else upd(rs,loc,val);
	}
	int qry(int p,int val){//到最远哪个点还是min 
		if(tr[p].l==tr[p].r){
			if(tr[p].mn<val) return tr[p].l-1;//到单个点的时候val仍然不是最小值，返回原区间-1
			return tr[p].l;
		}
		if(val>tr[ls].mn) return qry(ls,val);
		else return qry(rs,val);
	}
}using namespace Segtree;
int stk[maxn],tp;
int bs(int x){
	int l=1,r=tp+1,md;
	stk[r]=0;
	while(l<r){
		md=l+r>>1;
		if(stk[md]<=x) r=md;
		else l=md+1;
	}
	return stk[l];
}//单调栈中二分
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	char c;
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='p') a[i]=1;
		else a[i]=-1;
		a[i]+=a[i-1];
	}
	build(1,1,n);
	a[0]=maxn+528;//确保弹栈时不会弹空栈
	int ans=0;
	for(int i=n;i>=1;i--){
		int to=qry(1,a[i]);//lim
		to=bs(to);//满足条件的最大r
		if(!to) to=i;
		ans=max(ans,to-i);//求答案
		while(a[i]>a[stk[tp]]) tp--;
		stk[++tp]=i;//维护单调栈
		upd(1,i,a[i]);//更新线段树
	}
	int to=qry(1,0);
	to=bs(to);//特别处理区间为[1,r]的情况
	ans=max(ans,to);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：haoguhao (赞：5)

[传送门](https://www.luogu.com.cn/problem/P3564)
### 前言：
这个题在我们模拟赛的 T2，有一点点水，本做法借鉴[巨佬](https://www.luogu.com.cn/user/666072)的做法，简单易懂，跑的飞快。
### 题意：
就是让我们从给出的串中找到最长的字串使得：
1. 从左往右数时刻保持 `p` 比 `j` 多。
2. 从右往左数也时刻保持 `p` 比 `j` 多（其实可以不用把他俩一个看成 $1$ 一个看成 $-1$ 的）。
### 做法：
维护两个指针 $l,r$，显然我们是不能以字符串中的 `j` 做答案的开头和结尾的，于是就先去掉，然后开始遍历 $[l,r]$，定义两个变量 $sum1,sum2$，用来统计目前遍历到的 `p` 的数量与 `j` 的数量，所以如果 $sum2>sum1$，这个答案就不能要了,第一个限制就解决了。  
再看第二个限制，同时再定义两个变量 $s1,s2$，也是记录 `p` 和 `j` 的数量的，但略有不同，和一个记住位置的变量 $k$，如果有 $s1\ge s2$，那么答案就出现了，然后把 $s1$ 和 $s2$ 清零，用 $k$ 记录答案，这个地方很妙，可以自己模拟一下。因为全是 `p` 也是答案，一大串的 `j` 过后又有很多 `p` 和 `j` 抵消了也是答案，找到答案后统计答案，然后跳转到 $k$ 之后，因为答案的一部分不可能在 $k$ 之前，不然就变成更优的答案了。

### 贴上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){//快读
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f; 
}
int n，s1,s2,i,ans;
const int MAXN=1e6+5;
char s[MAXN];
int main(){
	n=read();
	for(int i=1;i<=n;i++) s[i]=getchar();
	int l=1,r=n;
	while(s[r]=='j') r--;//抹掉无用后缀 
	while(l<=r){
		while(s[l]=='j') l++;//每次抹掉无用前缀 
		int sum1=0,sum2=0,k=-1;
		for(i=l;i<=r;i++){
			if(s[i]=='p') sum1++,s1++;//记录p的数量 
			else sum2++,s2++;//记录j的数量 
			if(sum2>sum1) break;//从左往右数如果j的数量比p多一定不行 
			if(s1>=s2) s1=0,s2=0,k=i;//神之一手，自己模拟应该就理解了 
		} 
		if(k!=-1) i=k;//如果有答案出现直接跳转 
		ans=max(i-l+1,ans);//统计答案 
		l=i+1;s1=0;s2=0;//我们发现前面的东西再也不可能后面答案的一部分，于是直接跳转 
	}
	cout<<ans;
	
}
```
时间复杂度：$O(n)$。

---

## 作者：Leasier (赞：4)

前置芝士：[单调栈](https://oi-wiki.org/ds/monotonous-stack/)

首先不难想到可以把 `p` 当成 $1$、`j` 当成 $-1$ 进行一个前缀和，设前缀和数组为 $sum_i$，则合法区间 $[L, R]$ 需要满足：

- $\displaystyle\max_{i = L - 1}^{R - 1} sum_i \leq sum_R$
- $\displaystyle\min_{i = L}^R sum_i \geq sum_{L - 1}$

为了让条件变得易于维护，我们考虑预处理 $l_i, r_i$ 分别表示最后一个满足 $L \leq i$ 且 $sum_{L - 1} \leq sum_i$ 的 $L$、最后一个满足 $R \geq i$ 且 $sum_R \geq sum_{i - 1}$ 的 $R$。于是我们可以把条件转化为：

- $l_R \leq L$
- $r_L \geq R$

这时我们不难想到把 $l_R$ 挂在对应的 $L$ 上，从左到右扫一遍 $L$，加入所有对应的 $R$，再询问 $\leq r_L$ 的最大 $R$ 即可。

用单调栈预处理 $l_i, r_i$ 并用 set 维护当前可以选择的 $R$ 即可。时间复杂度为 $O(n \log n)$。

模拟赛时为了不被卡常写了树状数组，但在有 O2 时不必要。

代码：
```cpp
#include <iostream>
#include <stack>
#include <cstdio>

using namespace std;

int sum[1000007], _log2[1000007], st[1000007][27], l[1000007], r[1000007], cnt[1000007], tree[1000007];
int *bucket[1000007];
char a[1000007];
stack<int> s;

inline int lowbit(int x){
	return x & (-x);
}

inline void update(int n, int x, int k){
	while (x <= n){
		tree[x] = max(tree[x], k);
		x += lowbit(x);
	}
}

inline int get_max(int x){
	int ans = 0;
	while (x > 0){
		ans = max(ans, tree[x]);
		x -= lowbit(x);
	}
	return ans;
}

int main(){
	int n, ans = 0;
	scanf("%d", &n);
	scanf("%s", &a[1]);
	for (register int i = 1; i <= n; i++){
		if (a[i] == 'p'){
			sum[i] = sum[i - 1] + 1;
		} else {
			sum[i] = sum[i - 1] - 1;
		}
	}
	for (register int i = 1; i <= n; i++){
		s.push(i - 1);
		while (!s.empty() && sum[i] >= sum[s.top()]) s.pop();
		if (s.empty()){
			l[i] = 1;
		} else {
			l[i] = s.top() + 1;
			if (l[i] > i) l[i] = -1;
		}
	}
	while (!s.empty()) s.pop();
	for (register int i = n; i >= 1; i--){
		s.push(i);
		while (!s.empty() && sum[i - 1] <= sum[s.top()]) s.pop();
		if (s.empty()){
			r[i] = n;
		} else {
			r[i] = s.top() - 1;
			if (r[i] < i) r[i] = -1;
		}
	}
	for (register int i = 1; i <= n; i++){
		if (l[i] != -1) cnt[l[i]]++;
	}
	for (register int i = 1; i <= n; i++){
		bucket[i] = new int[cnt[i] + 1];
	}
	for (register int i = 1; i <= n; i++){
		if (l[i] != -1) bucket[l[i]][cnt[l[i]]--] = i;
	}
	for (register int i = 1; i <= n; i++){
		if (l[i] != -1) cnt[l[i]]++;
	}
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= cnt[i]; j++){
			update(n, bucket[i][j], bucket[i][j]);
		}
		if (r[i] != -1) ans = max(ans, get_max(r[i]) - i + 1);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：miaokehao (赞：4)

首先膜拜一下第一个发题解的大佬

网络上的题解较为复杂，而且对水平要求较高。所以本蒟蒻只好用一种玄学的方法：1.首先需要类似于前向星存边一样用O(n)的复杂度预处理出每个位置右边第一个前缀和相同的位置                                                    
    2.接下来用pre储存上一次留下的可能的最优位置，具体看代码
   ```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define res register int
#define M 1000005
using namespace std;
char A[M];
int sum[M],nxt[M],pev[M];
int last[M];
int main() {
	int n;
	scanf("%d %s",&n,A+1);
	for(res i=1; i<=n; i++) 
		sum[i]=sum[i-1]+(A[i]=='p'?1:-1);
	for(res i=n,x; i>=0; i--) {
		x=sum[i];
		nxt[i]=last[x];
		last[x]=i;
		pev[i]=i;
	}
	int ans=0;
	for(res i=1;i<=n;i++)
	  printf("%d ",sum[i]);
	puts("");
    for(res i=1;i<=n;i++)
	  printf("%d ",nxt[i]);
	puts("");
	for(res i=n,pre=n; i>=1; i--) {
		if(A[i]=='p') {//A[i]=p的话，可以保证i-1前缀和比自己小，就可以将i的最优解改为nxt[i-1]的最优解 
			if(nxt[i-1]&&sum[pev[nxt[i-1]]]>=sum[pre])pre=pev[nxt[i-1]];
			pev[i-1]=pre;
			ans=max(ans,pre-i+1);
		} else pre=i-1;//A[i]=j的话，只能保证i-1是可能最优解 
	}
	for(res i=1;i<=n;i++)
	  printf("%d ",pev[i]);
	puts("");
	printf("%d\n",ans);
	return 0;
}
```
 

---

## 作者：唐一文 (赞：4)

给一个空间巨大但是比较好想（？）的做法（

首先把 $\text p$ 看作 $1$，$\text j$ 看作 $-1$。那么一个子串满足要求等价于每个位置的前缀和与后缀和都非负。

先考虑只需要满足前缀/后缀非负的情况，记 $R_i$ 表示从 $i$ 开始能满足条件的最远右端点，$L_i$ 同理。显然它们具有单调性，ST表 + 二分即可。

可以发现一个子串 $[i,j]$ 满足要求的前提是满足 $L_j\leq i$ 并且 $j\leq R_i$。那么一个显然的暴力是枚举左端点 $i$，从 $R_i$ 开始往前枚举右端点 $j$，找到第一个满足 $L_j\leq i$ 的 $j$。

可以对 $L$ 开一个 ST表 维护区间最小值。每次从右端点二分即可。

注意此题的空间只能开一个 ST表！！1

[Code](https://www.luogu.com.cn/paste/ef12xlzf)

---

## 作者：renhao (赞：3)

很多题目，对于 $\Theta(n)$ 的方法确实比较难想，当然这是建立在不看题解并且在考试的时候。

很多时候，一些题目会有一些很显然的 $\Theta(n * \log n) $的方法，非常容易想到与实现，那何乐而不为呢？

首先，一个很常见的转换就是在比较两个东西的大小的时候把一个量看成-1，另一个看成1，这在很多题目都有体现，最经典的例子就是括号匹配。

#### 应该想到转换条件。

经过不断模拟可以发现，$[L,R]$合法就等价于 $sum[L] \le sum[i] \le sum[R]  ~~~~~~\forall i \in [L,R]$

一个很显然的想法是枚举右端点。
然后可以二分一下最左边可以取到哪里，假设这样二分得到位置 $x$

#### x一定是最小左边界的吗

很显然，$x$ 可能不合法，所以不能直接在数组上二分

在什么时候会不合法呢

存在一个 $p>x$ 满足 $sum[p]<sum[x]$ 的时候 $x$ 是不合法的

也就是说合法的$x$一定是单调递增的

那么用一个单调队列来维护合法的 $x$ 然后在单调队列上二分$x$就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
char s[N];
int n,cnt[N];
int q1[N],q2[N],r1,r2;
int Find(int x){
    int ret=-1;
    int l=1,r=r2;
    while(l<=r){
        int mid=(l+r)>>1;
        if(q2[mid]>=x){
            r=mid-1;
            ret=mid;
        }
        else l=mid+1;
    }
    return ret==-1?-1:q2[ret];
}
void Max(int &x,int y){
    if(x==-1||x<y) x=y;	
}
int main(){
    int ans=-1;
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        if(s[i]=='p') cnt[i]=1;
        else cnt[i]=-1;
        cnt[i]+=cnt[i-1];
    }
    r1=0,r2=0;
    q2[++r2]=0;
    q1[++r1]=0;
    for(int i=1;i<=n;i++){
        while(r1&&cnt[q1[r1]]<=cnt[i]) r1--;
        int L=q1[r1]+1;
        if(!r1) L=0;
        q1[++r1]=i;
        while(r2&&cnt[q2[r2]]>cnt[i]){
            r2--;
        }
        int to=Find(L);
        if(to==-1) to=i;
        q2[++r2]=i;
        Max(ans,i-to);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Nuyoah_awa (赞：3)

看没有人讲 set 加二分的解法，来补一篇题解。

### 题目大意

给定一个字符串，从中找出一个最长的子串，使得这个字符串从左往右扫和从右往左扫，始终保证 `p` 的个数不小于 `j` 的个数。

### 题目分析

先看数据范围，$n\le 10^6$。

大概时间复杂度就是 $\mathcal O(n) \sim \mathcal O(n \log n)$。

1. 我们先考虑从左往右扫，`p` 的个数不小于 `j` 的个数：

不妨将其变形为：一个子串区间 $l \sim r$，对于所有区间 $\sum\limits_{mid = l}^{mid \le r} mid \sim r$ 中，`p` 的个数不小于 `j` 的个数。

我们发现，对于每个区间，我们都可以通过前缀和判断是否合法，我们不妨将 `p` 看成 $1$，`j` 看成 $-1$，对于一个区间 $l \sim r$，如果 $s_r - s_l \ge 0$，那么就满足 `p` 的个数不小于 `j` 的个数。

所以一个子串需满足 $\sum\limits_{i = l}^{i \le r} s_r - s_i \ge 0$，即 $\sum\limits_{i = l}^{i \le r} s_i \le s_r$。

然后，我们容易发现，对于多个最长的合法区间（即左右界不可再延伸），它们有如下性质：

它们只可能像下图所示情况：

![P3564-1](https://z1.ax1x.com/2023/11/05/piQNfr4.png)

而不可能像下图的情况：

![P3564-2](https://z1.ax1x.com/2023/11/05/piQN2xU.png)

所以，我们很容易想到从左往右扫，用单调栈维护右界为 $r$，满足条件的最远左界 $g_i$。

2. 我们先考虑从右往左扫，`p` 的个数不小于 `j` 的个数：

思路同上，从右往左扫，求出 $f_i$。

3. 然后，我们就将问题转化为了区间覆盖问题。

我们观察如下图的情况（黄色表示 $f_i$，绿色表示 $g_i$，蓝色表示最长合法区间）：

![P3564-3](https://z1.ax1x.com/2023/11/05/piQNWMF.png)

我们不难发现，合法区间即为黄色和绿色都覆盖到的区间。

于是，我们可以枚举左界 $l$，然后看 $l \sim f_l$ 中被绿色覆盖的情况，对于答案有贡献的就是绿色区间右界在 $l \sim f_l$ 范围内，且左界在 $l$ 及其左边的情况，我们取最大值。

很明显，可以用 set 维护然后二分（具体见下面代码）。

看似上述情况可以用单调队列优化，但是我们发现 $f_i$ 显然不满足单调性，所以我们不能轻易地删除单调队列里的元素，这种情况下，单调队列退化成 $\mathcal O(n^2)$ 的。

时间复杂度是预处理 $\mathcal O(n)$，求答案枚举加二分 $\mathcal O(n \log n)$，总的时间复杂度也是 $\mathcal O(n \log n)$ 的。

PS：但是 set 自带的常数比较大，可能跑起来会比较慢，有可能会被轻微卡常（也可以写自己手写线段树）。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <stack>

using namespace std;

const int N = 1e6 + 5;
int n, sum[N], f[N], g[N], ans, m;
string str;
set <int> s;
vector <int> e[N];
stack <int> st;

int main()
{
    scanf("%d", &n);
    cin >> str;
    str = "#" + str;
    ans = 0;
    s.clear();
    for(register int i = 0;i <= n;i++)
        e[i].clear();
    for(register int i = 1;i <= n;i++)
        sum[i] = sum[i-1] + (str[i] == 'p' ? 1 : -1);
    while(!st.empty())  st.pop();
    for(register int i = n;i >= 1;i--)
    {
        st.push(i);
        while(!st.empty() && sum[st.top()] - sum[i-1] >= 0)
            st.pop();
        if(st.empty())
            f[i] = n;
        else
            f[i] = st.top() + 1;
    }
    while(!st.empty())  st.pop();
    for(register int i = 1;i <= n;i++)
    {
        st.push(i - 1);
        while(!st.empty() && sum[i] - sum[st.top()] >= 0)
            st.pop();
        if(st.empty())
            g[i] = 1;
        else
            g[i] = st.top() + 1;
        if(str[i] == 'p')
            e[g[i]].push_back(i);
    }
    for(register int i = 1;i <= n;i++)
    {
        for(register int j = 0;j < e[i].size();j++)
            s.insert(e[i][j]);
        if(str[i] == 'j') continue;
        set<int>::iterator it = s.upper_bound(f[i]);
        if(it != s.begin()) it--;
        //printf("%d %d\n", *it, i);
        if(it != s.end() && f[i] >= *it && g[*it] <= i)
            ans = max(ans, *it - i + 1);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Penguin_Chen (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P3564)

## 题目大意：

给定一个长度为 $n$ 的且只由 $\texttt{p}$ 和 $\texttt{j}$ 构成的字符串，要你找出一个最长的子串，满足从左往右和从右往左扫时，任何时刻 $\texttt{p}$ 的数量都大于等于 $\texttt{j}$ 的数量。

## 思路：

首先，通过观察，不难发现满足条件的字串的两端一定都是 $\texttt{p}$，所以，我们每次都可以去除前导 $\texttt{j}$。然后，我们用 $sum1$ 和 $sum2$，分别记录 $\texttt{p}$ 和 $\texttt{j}$ 的数量（前缀），用 $s1$ 和 $s2$ 记录后缀。既然要记录前缀和后缀，那么是不是要正反都扫一遍呢？并不需要，如果当前位是 $\texttt{p}$，就 `++sum1,++s1`，否则 `++sum2,++s2`。然后在每次 $s1$ 大于等于 $s2$ 时，将 $s1$ 和 $s2$ 清零。为什么呢？

举个例子：$\texttt{pppppjjjjpjjp}$，这时，我们从前往后扫，在扫到第十位 $\texttt{p}$ 时，如果 $s1$ 和 $s2$ 没有在第五位被清零（$sum1$ 等于 $sum2$，所以不会 `break`），$s1$ 就会大于 $s2$，那么，最长串就会被记为 $\texttt{pppppjjjjp}$。但是，我们发现这个字串并不符合要求（从右往左扫），这就是因为在第五位时没有清空 $s1$ 和 $s2$，所以前面的五个 $\texttt{p}$ 对第十位的 $\texttt{p}$ 造成了影响，因为假设我们不是从**左往右扫**，而是从**右往左扫**，那么这五个 $\texttt{p}$ 对于第十位的 $\texttt{p}$ 来说是在它之后的，但却对它造成了影响，这显然是错误的。

所以，“每次 $s1$ 大于等于 $s2$ 时，将 $s1$ 和 $s2$ 清零”这个操作就是为了**清除前缀对后缀的影响**（不理解就结合前面的例子多想一会）。至于复杂度嘛，因为这个算法有点玄学，不太确定，应该是 $O(n)$。

思路提供者：[巨佬](https://www.luogu.com.cn/user/666072)（这是他的赛时思路，~~踩爆标算~~）。

## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+11;
int n;
int l,r,ans;
int s1,s2;//记录后缀 
int sum1,sum2;//sum1记录p的数量，sum2记录j的数量（前缀）
char str[maxn];
signed main()
{
	freopen("1.in","r",stdin);
	std::ios::sync_with_stdio(false);
	cin>>n;
	cin>>str+1;
	l=1,r=n;
	while(str[r]=='j')--r;
	while(l<=r)
	{
		while(str[l]=='j')++l;
		int k=-1,i;
		sum1=0,sum2=0;
		for(int i=l;i<=r;++i)
		{
			if(str[i]=='p')
				++sum1,++s1;
			else
				++sum2,++s2;
			if(sum2>sum1)break;//j的数量大于p的数量，不符合要求，break 
			if(s1>=s2)//上面有解释 
				s1=0,s2=0,k=i;
		}
		if(~k)i=k; 
		ans=max(ans,i-l+1);//更新答案 
		s1=0,s2=0;
		l=i+1;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：hanhoudedidue (赞：3)

## 前言：
	
   考试考了这道，觉得蛮简单的，随便糊几下就过去了。考完一看竟然是个紫的，~~并且代码还踩爆标算~~，便来水篇题解。

## 题目大意：
	
   题意很简单啊，给出一个只包含 $\texttt{p}$ 和 $\texttt{j}$ 的字符串，找出一个最长的字串，使得不管从前往后还是从后往前数，过程中 $\texttt{p}$ 的个数不少于 $\texttt{j}$ 的个数。
   
## 分析：

我们发现，答案子串头和尾一定都是一段 $\texttt{p}$。从前往后遍历，我们往后推会发现若上一次的答案子串已经判完了，则之前的与这次的毫无关系，所以我们可以从前往后扫，看每次的最大长度，取最大值然后清空接着往后面扫。

现在想想怎么看每次的最大长度。如果我们只有一个从前往后 $\texttt{p} \ge \texttt{j}$ 这一个条件的话，只需要正面扫，用 $sum1$ 记录 $\texttt{p}$ 的个数，用 $sum2$ 记录 $\texttt{j}$ 的个数，若 $sum1 < sum2$ 则跳出，记录一下长度取最大值，然后清空 $sum1$ 和 $sum2$，再往后扫即可。

现在就只剩一个额外的条件了。我们同样也可以用 $s1$ 和 $s2$ 分别记录从后面数 $\texttt{p}$ 和 $\texttt{j}$ 的个数，扫的时候若 $s2 > s1$ 则用 $k$ 记录一下位置，若 $s2 \le s1$，则将 $s1,s2$ 均赋值为 $0$，并且将 $k$ 清空。若到最后 $s2$ 仍大于 $s1$ 则将 $i$ 跳回到 $k$。不难证明做法是正确的。

最后来证明前一个答案子串与后面的毫无关系：采用反证法：若有关系，则该子串与前一个有公共部分，但根据扫的过程和题目限制，包含这一段的答案是严格不优于前面的。所以后面的答案与前一个子串毫无关系。

时间复杂度很玄幻，约为 $O(n)$，几乎卡不掉，并且根据对拍一小时七百多万组证明其正确性。求大佬来卡。

## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int f=1,x=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return f*x;
}
inline void print(int x){
	if(x<0) {putchar('-');print(-x);return;}
	if(x>9) print(x/10);putchar(x%10+'0');
}
const int N=1e6+5;
int l,r,n,sum1,sum2,s1,s2,ans,k;
char a[N];
signed main(){
	freopen("salad.in","r",stdin);
	freopen("salad.out","w",stdout);
	n=read();l=1,r=n;
	for(int i=1;i<=n;i++) a[i]=getchar();
	while(a[r]=='j') r--;
	while(l<=r){
		while(a[l]=='j') l++;
		int i,k=-1;
		sum1=0,sum2=0;
		for(i=l;i<=r;i++){
			if(a[i]=='p') sum1++,s1++;
			else sum2++,s2++;
			if(sum2>sum1) break; 
			if(s1>=s2) s2=0,s1=0,k=i;
		}
		if(k!=-1) i=k;
		ans=max(ans,i-l+1);
		l=i+1;s1=s2=0; 
	}
	print(ans);
	return 0;
}
```
第一发交的时候竟然是最优解。如若有错欢迎来指出。

管理大大求过！

---

## 作者：鱼跃于渊 (赞：1)

## 做法
对于区间 $[l,r]$，我们首先考虑从左往右的限制，用 $p1$ 表示 $\texttt{p}$ 的数量，用 $p2$ 表示 $\texttt{j}$ 的数量。那么当我们从左往右扫时，若 $p1<p2$，则当前部分不合法，退出循环。  
再考虑从右往左的限制，用 $s1$ 表示 $\texttt{p}$ 的数量，用 $s2$ 表示 $\texttt{j}$ 的数量。那么当我们从左往右扫时，若 $s1 \ge s2$，则当前部分符合条件，用 $flag$ 记录当前位置，再将 $s1$ 和 $s2$ 都清零。  
当循环结束时，如果 $flag$ 记录了合法位置，则答案 $ans$ 更新为 $\max(ans,flag-l+1)$。然后令 $l=flag+1$，继续上面的流程，一直到 $l>r$ 为止。  
这个玄学做法的时间复杂度大约为 $O(n)$，我不会证明，不过本地跑 $10^8$ 的随机数据也才用时 1.5s。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
char s[N];
int n,w,ans,l,r,p1,p2,s1,s2,flag;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>(s+1);l=1;r=n;
	while(s[l]=='j') l++;
	while(s[r]=='j') r--;
	while(l<=r){
		flag=-1;p1=p2=s1=s2=0;
		for(int i=l;i<=r;i++){
			if(s[i]=='p'){
				p1++;s1++;
			}else{
				p2++;s2++;
			}
			if(p1<p2) break;
			if(s1>=s2){
				s1=s2=0;flag=i;
			}
		}
		if(flag!=-1){
			ans=max(ans,flag-l+1);
			l=flag+1;
		}
		while(s[l]=='j') l++;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：wangruibo20 (赞：1)

先来一个传送门：[P3564 [POI2014] BAR-Salad Bar](https://www.luogu.com.cn/problem/P3564)

## 题意

给定一段区间，每个值都为 $-1$ 或 $1$，求一段最长的区间，使得这段区间任意前缀和以及任意后缀和都为非负数。

## 分析过程

看到这种题，应该都会先想到求一次前缀和，再求一次后缀和吧（~~不会真的有人想不到吧~~）。

但是，这道题让我们要实现实时求前缀和与后缀和，这就遇到了一个问题：怎样同时知道一段区间的前缀和与后缀和？

~~em，好像不行……~~

因为我们只能实时求得前缀和。

不行就换种方式。我们用另一个类似前缀和的方法来通过前缀和得知后缀的情况。只要枚举的区间的类前缀和大于等于零时，就意味着此区间刚刚好是合法区间，将类前缀和清零，继续进行记录。

### 方法~~伪证~~证明:

>当第一次类前缀和大于等于零时，这个区间必然合法（读者自行思考），这时清零。
>
>当第 $i(i>1)$ 次大于等于零时，由于第 $i-1$ 次操作时区间合法，变量清零，第 $i$ 次前记录的是由上个合法区间右端点的右边点至现在点围出的区间，变量大于等于零时就表示这个区间现在合法，而两个合法区间相接，所得区间必然合法。
>
>由此，我们就得出了一段合法区间。

那么，上代码。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
char a[1000001];
ll n,l,mx,s1,s2,p,q;//s1表示正常前缀和，s2表示类前缀和 
int main(){
    cin>>n>>a;
    n--;
    for(;a[n]=='j';n--);
    while(l<=n){
        for(;a[l]=='j';l++);
        s1=s2=p=q=0;
        for(int i=l;i<=n;i++){
            if(a[i]=='p')s1++,s2++;//+1操作
            else s1--,s2--;//-1操作
            if(s1<0){
                p=i-1;//取最大合法区间
                break;
            }if(s2>=0){
                q=i;//开始一个新合法区间的记录
                s2=0;
            }
        }if(q)p=q;
        mx=max(mx,p-l+1);
        l=p+1;
    }printf("%lld",mx);
    return 0;
}
```

---

## 作者：rq_kyz (赞：1)

# 【题解】 P3564 [POI2014] BAR-Salad Bar

### 传送门

[P3564 [POI2014] BAR-Salad Bar](https://www.luogu.com.cn/problem/P3564)

---

### 题意

给定一个长度为 $n$ 的字符串，其中只包含 $p$ 和 $j$。求一个最长子串，使得不管是从哪个方向取，都保证每时每刻已取出的 $p$ 的个数不小于 $j$ 的个数。

---

### 分析

我们可以考虑一种类似贪心的策略。我们可以把 $p$ 看作 $1$，$j$ 看作 $-1$。首先我们需要记录前缀和，保证每个时候前缀和都为正。但是本题还需要用到后缀和，而前缀和和后缀和不好去同时维护。这里我们可以~~非常人类智慧的~~记录第二个前缀和，但是这个前缀和一旦大于等于 $0$，我们就将它设为 $0$，然后更新答案。为什么要这样呢？因为这样的话我们可以保证当上面的条件成立时，这个前缀和记录的这段区间的任意一个后缀和均大于等于 $0$（~~这里请读者自行感性理解一下~~）。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
char s[1000001];
int main(){
	ll n;
	scanf("%lld\n%s",&n,s+1);
	ll l=1,r=n,max_=0;
	while(s[r]=='j')//去掉末尾多余的j
		r--;
	while(l<=r){
		while(s[l]=='j')//去掉开头多余的j
			l++;
		ll fp=0,fj=0,bp=0,bj=0,p=0,q=0;
		//fp、fj表示原始的前缀和记录的p的个数与j的个数
		//bp、bj表示第二个前缀和记录的p的个数与j的个数
		//p为原始的前缀和的右端点，q为第二个前缀和的右端点
		for(int i=l;i<=r;i++){
			if(s[i]=='p'){//累计前缀和
				fp++;
				bp++;
			} else {
				fj++;
				bj++;
			}
			if(fp<fj){//如果前缀和已经不满足，就直接退出循环
				p=i;
				break;
			}
			if(bp>=bj){//更新第二个前缀和
				q=i;
				bp=0;
				bj=0;
			}
		}
		if(q)//如果更新过第二个前缀和，则直接设为第二个前缀和的结果
			p=q;
		max_=max(max_,p-l+1);//记录答案
		l=p+1;//更新开始左端点
	}
	printf("%lld",max_);
	return 0;
}
```

---

## 作者：Querainy (赞：1)

给一个不依赖 $\pm 1$ 的做法。

设前缀和是 $p$，问题就是找到最长的 $[l,r]$ 使得 $p_l,p_r$ 分别是区间中的 $\min,\max$。这个其它题解已经充分论述了。

考虑从右往左枚举 $l$，维护递增的非严格单调栈和递减的严格单调栈，那么递增单调栈中的元素 $r$ 都满足 $p_r$ 是区间 $\max$，而递减单调栈中 $l$ 右边第一个元素限制住了 $p_l$ 作为区间 $\min$ 的范围，问题是查询递减单调栈中 $l$ 右边第一个元素在递增单调栈中的前驱。

考虑用链表维护两个单调栈的归并（，同时维护每个元素在这个链表中的位置），在其中从递减单调栈中 $l$ 右边第一个元素向左找就 $O(1)$ 地找到了这个前驱。总复杂度 $O(n)$。

感觉很可能有更简单的（不依赖 $\pm 1$ 的）做法。有没有老哥教教。

---

## 作者：一扶苏一 (赞：1)

# 【线段树】【P3564】[POI2014]BAR-Salad Bar

## Description

给定一个长度为 $n$ 的只含字符 ``p`` 和 ``j`` 的字串，求其最长子串 $T$，满足无论从左往右遍历还是从右往左遍历，任意时刻的 ``p`` 的个数都不低于 ``j`` 的个数。

## Limitations

$1 \leq n \leq 10^6$

## Solution

这里有个比较无脑不需要分析的做法……

首先对于这类子区间问题，我们都考虑枚举右端点，然后对每个右端点最优化左端点。

我们将两个条件分开看，即考察只从左往右遍历时合法的左端点集合，已经只从右向左遍历时合法的左端点集合。显然合法字串的左端点集合时这两个集合的交集。

先考虑从右向左遍历的情况。显然当右端点 $r$ 处的值为 ``j`` 的时候不存在合法左端点，因此我们只考虑 $r$ 处为 ``p`` 的情况。注意到这种情况下，合法左端点的集合一定是连续的一段，且 $r$ 处一定是一个合法左端点。即如果某一位置不是一个合法的左端点，那么该处的左侧一定不合法。因此最左侧的合法左端点是可以二分的。我们考虑维护一个长度为 $r$ 的序列 $A$，第 $i$ 个数 $A_i$ 表示从 $[i, r]$ 的 ``p`` 的个数减去 ``j`` 的个数。那么我们只需要知道这个序列的后缀最小值，就可以二分出最后一个不合法的 $l$ 值。当右端点向右移动时，考虑如果新的位置是 ``p``，那么序列上所有位置的值都要加一，否则都要减一。因此我们需要一个支持区间加，查询最小值，并且可以 $O(\log n)$ 二分的数据结构。我们考虑直接用线段树去维护上述 $A$ 的区间最小值。然后直接在线段树上二分即可。

这里简单介绍直接在线段树上二分的方法，以本题为例，设线段树区间 $[l, r]$ 代表 $A_l$ 到 $A_r$ 的最小值，我们在当前节点，只需要检查右孩子的最小值是否非负，如果是，则递归左孩子，否则递归右孩子即可。

 再考虑从左向右遍历的情况。首先维护一个前缀和，设 `p` 的值为 $1$， `j` 的值为 $-1$，记 $sum_i$ 为 $i$ 处的前缀和。假设我们已经维护好了合法的左端点位置减去 $1$ 的集合，我们 $r$ 向右移时，可能合法的左端点之可能会增加 $r$ 本身一个位置。而所有在集合中且满足 $sum_l > sum_r$ 的 $l$ 值都要被从集合中移除。因此每个端点只会被加入和移除集合一次。我们需要一个能够将所有位置按照 $sum$ 值排序并动态维护插入某值，以及删除最小值的数据结构。因此我们考虑用堆来维护这个集合。

为了将两种情况的合法左端点和并，我们在第二种情况时同时用一个 ``std::set`` 来维护所有合法的左端点减去 $1$ 的值（在堆进行删除时顺手将 ``set`` 中元素删除即可），我们用第一种情况求出的最后一个不合法的左端点 ``l``，在 ``set`` 中求一个 ``lower_bound`` 即可找到最小的合法左端点减一后的值，用 $r$ 减掉这个数即是 $r$ 对应区间最长的长度。

## Code

```cpp
#include <cstdio>
#include <set>
#include <queue>
#include <algorithm>

const int maxn = 1000005;

int n, ans;
int sum[maxn];
char MU[maxn];

struct dat {
  int x;
  
  inline bool operator<(const dat &_others) const {
    return sum[x] < sum[_others.x];
  }

  dat(const int X = 0) : x(X) {}
};

std::set<int> ts;
std::priority_queue<dat> s;

struct Tree {
  Tree *ls, *rs;
  int l, r, v, tag;

  inline bool InRange(const int L, const int R) { return (L <= l) && (R >= r); }
  inline bool OutofRange(const int L, const int R) { return (l > R) || (r < L); }

  inline void maketag(const int V) {
    tag += V;
    v += V;
  }

  void pushdown() {
    if (tag == 0) return;
    ls->maketag(tag);
    rs->maketag(tag);
    tag = 0;
  }

  void pushup() {
    v = std::min(ls->v, rs->v);
  }

  void update(const int L, const int R, const int V) {
    if (InRange(L, R)) {
      maketag(V);
    } else if (!OutofRange(L, R)) {
      pushdown();
      ls->update(L, R, V);
      rs->update(L, R, V);
      pushup();
    }
  }

  int query() {
    if (l == r) {
      return (v < 0) ? l : 0;
    } else {
      pushdown();
      if (rs->v < 0) {
        return rs->query();
      } else {
        return ls->query();
      }
    }
  }


  Tree(const int L, const int R) : l(L), r(R), v(0), tag(0) {
    if (L == R) {
      ls = rs = NULL;
    } else {
      int M = (L + R) >> 1;
      ls = new Tree(L, M);
      rs = new Tree(M + 1, R);
    }
  }
};

void ReadStr(char *p);

int main() {
  freopen("1.in", "r", stdin);
  qr(n);
  ReadStr(MU + 1);
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + ((MU[i] == 'p') ? 1 : -1);
  }
  auto rot = new Tree(1, n);
  for (int i = 1; i <= n; ++i) if (MU[i] == 'j') {
    rot->update(1, i, -1);
    while ((!s.empty()) && (sum[i] < sum[s.top().x])) {
      int v = s.top().x;
      ts.erase(v); s.pop();
    }
  } else {
    s.push(i - 1); ts.insert(i - 1);
    rot->update(1, i, 1);
    int l = rot->query();
    while ((!s.empty()) && (sum[i] < sum[s.top().x])) {
      int v = s.top().x;
      ts.erase(v); s.pop();
    }
    l = *ts.lower_bound(l);
    ans = std::max(ans, i - l);
  }
  printf("%d\n", ans);
  return 0;
}

void ReadStr(char *p) {
  do *p = IPT::GetChar(); while ((*p != 'p') && (*p != 'j'));
  do *(++p) = IPT::GetChar(); while ((*p == 'p') || (*p == 'j'));
  *p = 0;
}

```





---

## 作者：forgotmyhandle (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3564)

## 分析
把 $\texttt{p}$ 视为 $1$，$\texttt{j}$ 视为 $-1$，做前缀和记为 $s$，则一个区间 $[l, r]$ 符合要求当且仅当 $s_{l - 1}$ 为 $s[l, r]$ 的最小值且 $s_r$ 为 $s[l, r]$ 的最大值。也就是求一个最长的区间，使得左端点是区间最小值，右端点为区间最大值，答案即为这个区间的长度减 $1$。

首先容易发现任意两个合法极大区间不交。包含的情况过于平凡，略去。设两个区间 $[a, b], [c, d](a < c < b < d)$ 都是合法极大区间，则 $s_a = \min s[a, b], s_c = \min s[c, d]$。注意到 $a < c < b$，所以 $s_a \leq s_c = \min s[c,d]$，即 $s_a = \min s[a, d]$。最大值也同理。所以 $[a, d]$ 也是合法区间，与 $[a, c]$ 和 $[b,d]$ 的极大性矛盾。

注意到单独一个点也是合法区间，所以我们枚举左端点 $l$，求出最大的 $r$ 使得 $[l, r]$ 为合法区间。求完之后 $l \leftarrow r + 1$（虽然不这样时间复杂度也是对的~~而且也不用上面那个证明写得一坨的性质了~~）。

有了 $l$ 之后，根据区间中所有数 $\ge l$ 我们可以知道 $r$ 的范围。设 $v_i$ 为 $i$ 右边第一个比 $i$ 小的数的位置，则 $r \in [l, v_l - 1]$。接下来根据贪心的原则，我们选择 $[l, v_l - 1]$ 之内的最后一个最大值的位置作为 $r$。设这个位置是 $t$，则若 $r \in [l, t)$，则将 $r$ 放在 $t$ 仍然合法且会更优。若 $r \in (t, v_l - 1]$，则易得 $[l, r]$ 不是合法区间。所以 $r = t$ 即为当前 $l$ 的答案。

然后求 $v_i$ 使用单调栈，区间最大值位置使用 ST 表维护，时间复杂度 $\mathcal{O}(n \log n)$。

最后只需要把所有枚举到的 $l$ 的 $r - l$ 取 $\max$ 即为所求。

注意到由于空间限制很小，ST 表里面同时存区间最大值及其位置会爆空间。我们只存区间最大值位置即可。

## 代码
```cpp
#include <iostream>
using namespace std;
int n;
int s[1000005];
string str;
int stk[1000005], sz;
int lg2[1000005];
int v[1000005];
int mx[21][1000005];
int Max(int x, int y) { return (s[x] < s[y] ? y : (s[x] > s[y] ? x : max(x, y))); }
int Query(int l, int r) {
    int k = lg2[r - l + 1];
    return Max(mx[k][l], mx[k][r - (1 << k) + 1]);
}
int main() {
    cin >> n;
    cin >> str;
    str = ' ' + str;
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + (str[i] == 'p' ? 1 : -1);
    for (int i = 0; i <= n; i++) {
        while (sz && s[stk[sz]] > s[i]) v[stk[sz--]] = i;
        stk[++sz] = i;
        mx[0][i] = i;
    }
    for (int i = 1; i <= 20; i++) {
        for (int j = 0; j + (1 << i) - 1 <= n; j++) 
            mx[i][j] = Max(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))]);
    }
    for (int i = 1; i <= sz; i++) v[stk[i]] = n + 1;
    lg2[0] = -1;
    for (int i = 1; i <= n; i++) lg2[i] = lg2[i - 1] + ((i & (i - 1)) == 0);
    int ans = 0;
    for (int i = 0; i <= n; ) {
        int t = Query(i, v[i] - 1);
        ans = max(ans, t - i);
        i = t + 1;
    }
    cout << ans << "\n";
    return 0;
}
```

线段树维护区间最大值位置可能会更快，因为查询次数不一定跑满，而 ST 表是满的。我比较懒，并没有实现，所以只是猜测。但是实际上也可以卡满。

---

## 作者：Silvestorm (赞：0)

### 题目大意

有一个长度为 $n$ 的字符串，每一位只会是 $p$ 或 $j$。求一个最长子串，使得不管是从左往右还是从右往左取，都保证每时每刻已取出的 $p$ 的个数不小于 $j$ 的个数。

$1\le n \le 10^6$。

### 题目类型

线段树，并查集，二分，单调队列，深度优先搜索，最大字段和。

### 解题思路

显然 $p$ 为正贡献，可以先将字符串转化成 $1,-1$ 类型数组，$p$ 代表 $1$，$j$ 代表 $-1$。那么问题就转化成了求最长子段，使其任何一位的前缀和与后缀和的值都是非负数。

对于如何解决这个问题，题解区已经有不少优秀的解法，而这里要介绍的是似乎还未出现的解法：暴力搜索。

首先我们可以从头到尾做类似最大子段和的处理，定义起始点 $res$ 与前缀和 $sum$，遍历到第 $i$ 个点时，如果 $sum$ 非负，那么从 $res$ 到 $i$ 这一段都是前缀合法的，否则更新 $res$，同时将这一段拿出来，从后往前进行上述处理。这样一步一步搜索，直到前缀和与后缀和都合法的子段出现，记录答案。

本以为 $n=10^6$ 的情况会超时，没想到稍稍优化一下，总耗时 $44ms$，~~简直快的飞起~~，数据弱是一方面，可能也有某些小结论在里边吧。

### code

```cpp
#include <bits/stdc++.h>
#define ll int
using namespace std;
ll n, a = 0, b = 1, num[1000100];
ll ans = 0;
void find(ll l, ll r, ll k)
{
	if (k == 0)//从前往后遍历
	{
		ll res = r, sum = 0;
		for (int i = r; i >= l; i--)
		{
			if (sum < 0)
			{
				for (int j = i + 1; j <= res; j++)
					if (num[j] == 1)
					{
						find(j, res, b);
						break;
					}
				sum = 0;
				res = i;
			}
			sum += num[i];
		}

		if (res == r)
		{
			ans = max(ans, r - l + 1);
			return;
		}

		if (sum >= 0)
			find(l, res, b);
	}
	else//从后往前遍历
	{
		ll res = l, sum = 0;
		for (int i = l; i <= r; i++)
		{
			if (sum < 0)
			{
				for (int j = i - 1; j >= res; j--)
					if (num[j] == 1)
					{
						find(res, j, a);
						break;
					}
				res = i;
				sum = 0;
			}
			sum += num[i];
		}

		if (res == l)
		{
			ans = max(ans, r - l + 1);
			return;
		}
		if (sum >= 0)
			find(res, r, a);
	}
	return;
}
void solve()
{
	string s;
	cin >> n >> s;
	for (int i = 0; i < n; i++)
		if (s[i] == 'p')
			num[i] = 1;
		else
			num[i] = -1;
	ll l = 0, sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (sum < 0)
		{
			find(l, i - 1, a);
			l = i;
			sum = 0;
		}

		sum += num[i];
	}
	find(l, n - 1, a);
	cout << ans << '\n';
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：EricWan (赞：0)

太思维了！本人使用的不是最优解，但能过。

## Step1 抽象与思考

将 `p` 看为 $1$，`j` 看为 $-1$，计算前缀和 $\text{sum}_i=\sum_{j=1}^{i}a_j$。

设选择区间 $[l,r]$，则要求：

$$\text{sum}_i-\text{sum}_{l-1}\ge0\;\forall\;i\in[l,r]$$

$$(\text{sum}_n-\text{sum}_{i-1})-(\text{sum}_{n}-\text{sum}_{r})\ge0\;\forall\;i\in[l,r]$$

于是可以简化为：

$$\text{sum}_{l-1}\le\text{sum}_i\le\text{sum}_r\;\forall\;i\in[l,r]$$

具体而形象的说，将 `jpppjpjpppjjjj` 的 $\text{sum}$ 用柱状图表示为：

![piJ8pQK.png](https://z1.ax1x.com/2023/11/13/piJ8pQK.png)

则要求 $[l,r]$ 中的 $\text{sum}$ 均在红线和橙线中间，为了方便，我们设 $L=l-1$，$R=r$，要找到 $R-L$ 最大的 $L$ 和 $R$，使得 $\text{sum}_{L}\le\text{sum}_i\le\text{sum}_R\;\forall\;i\in[L,R]$。

## Step2 预处理

处理 $\text{nxt}_i$ 表示 $\text{sum}_j\ge\text{sum}_i\;\forall\;j\in[i,\text{nxt}_i]$ 但 $\text{sum}_{\text{nxt}_i+1}<\text{sum}_i$。

处理这两个变量时可以这样办：

1. 使用树状数组，发现 $\text{nxt}_i=(\min j\;\forall\;j\in[i+1,n]\And \text{sum}_j<\text{sum}_i)-1$，于是从后向前遍历，计算 $\text{nxt}_i$ 后将当前的元素加入树状数组即可（$\text{sum}$ 为下标，$i$ 为元素的值，树桩数组维护前缀最小值）。

这一段预处理复杂度巨大，达到 $O(n\log n)$ 级别，但是能过。

## Step3 计算答案

按照 $\text{nxt}_i$ 进行答案的计算，设左边界为 $L$，我们的右界 $R$ 肯定要满足：

$$\max_{j=1}^{\text{nxt}_i}\text{sum}_j=\text{sum}_R$$

$$\max_{j=R+1}^{\text{nxt}_i}\text{sum}_j<\text{sum}_R$$

因此，我们使用 ST 表进行处理即可。

当然，这一段预处理复杂度巨大，达到 $O(n\log n)$ 级别，但还是能过。

---

感谢伟大的 @[wsc2008](https://www.luogu.com.cn/user/288866) 帮助我找到一个错别字。

---

## 作者：nkrqzjc_zzz (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/P3564)
------------
#### 写在前面

因为有大佬都对数据结构十分~~厌恶~~**喜欢**，想看看简单的方法，我就来讲讲本蒟蒻的方法。


------------

#### 思路1

首先有一个前缀和的思路，这个思路很好想，就是用前缀和记录一下从左到右的状态，$j$ 设为 $-1$，$p$ 设为 $1$，如果 $l \sim r$ 中的值都大于 1 ，就再用一层循环判断倒叙的答案，最后记录一下，找到最大的答案。

那么就可以想到一个简单的优化方法，加一个后缀和，可问题就来了，如果想要后缀和和前缀和一起加减，那就会有两个情况：一、 优化后还是二重循环，没有作用；二、后缀和没有办法和前缀和一起加减，或者说是前缀和会影响到后缀和的判断。


------------

#### 思路2
所以我们就要用一些**超人类智慧**的方法，方法如下：

先修改前缀和，将 $p$ 和 $j$ 分开存储，然后增加类似于后缀和的东西，后缀和随前缀和着加减，不过后缀和的判断条件与前缀和不同，只要 $p$ 的后缀和大于等于 $j$ 的后缀和，就立即更新答案，再清空后缀和，去除前缀和给后缀和带来的影响（其实这种方法已经不太像前后缀和了，感觉就是贪心）。具体如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l,ji,r,dn,h1,h2,q1,q2;
char a[1000002];
main(){
	cin>>n;
	cin>>a+1;
	l=1,r=n;
	while(a[r]=='j')r--;//去除后面没用的j
	while(l<=r){
		while(a[l]=='j')l++;//同理，去除前面没用的j，减小复杂度
		k=0;//k记录答案l到r区间的答案
		q1=0;q2=0;h1=0;h2=0;
        	//q2是区间内j的总数，q1是区间内p的总数，h2是j的后缀，h1是p的后缀
		for(int i=l;i<=r;i++){
			if(a[i]=='j'){//后缀与前缀同增
				q2++;
				h2++;
			}
			else{
				q1++;
				h1++;
			}
			if(q2>q1){//若j的数量已经大于p的数量
				ji=i;
				break;
			}
			if(a[i]=='p'&&h1>=h2){//若满足答案，马上更新
				h1=0;
				h2=0;
				k=i;
			}
		}
		if(k)ji=k;//若后缀和有答案，就用后缀和的答案
		dn=max(dn,ji-l+1);
		l=ji+1;//ji+1以前的东西已经没有意义了，直接舍掉
	}
	cout<<dn<<endl;
	return 0;
}
```


---

## 作者：Reanap (赞：0)

这道题让我自闭了数个小时。。。

首先分享一个非常不好的习惯--做题先看标签：

![QQ图片20200229183529.png](http://61.186.173.89:2019/2020/02/29/d640cf395414e.png)

于是可怜的我就被坑了。。。

看到二分答案，我首先打了个二分，想check函数。

问题转化为下面：我们把每个$p$想象成$1$,把每个$j$想象成$-1$,验证是否存在长度为$mid$的序列满足文中条件。

对于该序列[i,j]，我们可以维护一个前缀和$s1$和一个后缀和$s2$,那么我们只需要在[i,j]找到一个最小的$s1[k]$,检查$s1[k] - s1[i-1]$是否非负，找到一个$s2[w]$，检查$s2[w]-s2[j+1]$是否非负。

对于这两个最小值我们完全可以用双端队列来维护。

然后蒟蒻愉快地打好了代码。

~~WA穿，当场去世~~

仔细想一想，其实这道题它并不存在单调性，因为长度为$x+y$的序列存在，但长度为$x$的却不一定存在，因为这里要考虑正着取和倒着取。

~~随便举个例子都能发现~~

所以大家千万不要无脑二分，二分前一定要检查单调性。。。

大家也不要轻信盲从标签，要有自己的思考。

意识到这一点的我高度自闭，但显然，我的check函数中所用到的思路正解必然也会用到
~~不然我为什么要讲~~。

我们现在的已知有用条件就是对于一个序列判断他是否合法，即最小的$s1[k]$必须大于等于$s1[i-1]$，最小的$s2[w]$必须大于等于$s2[j+1]$，这两个条件从本质上来说是一样的，所以我们先选取第一个为根本进行分析。

既然$s1[k]$必须大于等于$s1[i-1]$，那么我们何不先把$i$确定下来，然后寻找以$i$为左端点的最长合法区间长度呢？我们把$i$确定下来后，我们又可以找到一个最小的$j1$,使得$s1[j1]$小于$s1[i-1]$。这就意味着，我们最长合法区间的长度的$j$必然小于$j1$。

我们现在要根据第二个条件确定最终的区间长度。怎么办呢？既然最小的$s2[w]$必须大于等于$s2[j+1]$，那么$s2[j+1]$必然小于该区间的每一个数，所以$s2[j+1]$必然是区间$[i+1,j1]$内的最小值，如果更小则不一定最长，如果更长，那么另外的$s2[j+1]$就必然大于$s2[w]$。

讲一下实现：

我们现在要枚举每一个$i$，然后找到在他右边的第一个小于它的位置。

关于此，我们可以用线段树处理，使用线段树维护前缀和的区间最小值，如果左边的最小值比$i$的值小，则往左边走，否则往右边走，每预处理一个$i$就把他的值改为极大值。（特别鸣谢$LYC$巨佬的帮助）

现在，我们要查询区间最小，显然是线段树维护后缀和的区间最小对吧。

这道题代码实现起来还是很烦的，希望大家自己实现一下。

实在不行再来参考一下我的结构。

```cpp
#include <deque>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1e6 + 5;
int s1[MAXN] , n , ans[MAXN];
char s[MAXN];
struct node {
	int id , val;
}t[MAXN << 2];
void build(int l , int  r , int now) {
	if(l == r) {
		t[now].val = s1[l];
		t[now].id = l;
		return;
	}
	int mid = (l + r) >> 1;
	build(l , mid , now << 1);
	build(mid + 1 , r , now << 1 | 1);
	if(t[now << 1].val < t[now << 1 | 1].val) 
		t[now] = t[now << 1];
	else t[now] = t[now << 1 | 1];
}
int find(int l , int r , int now , int x) {
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(t[now << 1].val < x) return find(l , mid , now << 1 , x);
	return find(mid + 1 , r , now << 1 | 1 , x);
}
void update(int l , int r , int now , int x) {
	if(l == r) {
		t[now].val = 1e9;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) update(l , mid , now << 1 , x);
	else update(mid + 1 , r , now << 1 | 1 , x); 
	if(t[now << 1].val < t[now << 1 | 1].val) 
		t[now] = t[now << 1];
	else t[now] = t[now << 1 | 1];
}
int get_min(int l , int r , int now , int x , int y) {
	if(l >= x && r <= y) {
		return t[now].id;
	}
	int mid = (l + r) >> 1 , re1 = 1e9 , re2 = 1e9;
	if(x <= mid) re1 = get_min(l , mid , now << 1 , x , y);
	if(y > mid) re2 = get_min(mid + 1 , r , now << 1 | 1 , x , y);
	if(re1 == 1e9) return re2;
	if(re2 == 1e9) return re1;
	if(s1[re1] < s1[re2]) return re1;
	else return re2;
}
int main() {
	scanf("%d" , &n);
	scanf("%s" , s + 1);
	if(n == 1) {
		if(s[1] == 'p') printf("1");
		else printf("0");
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		if(s[i] == 'p') s1[i] = s1[i - 1] + 1;
		else s1[i] = s1[i - 1] - 1;
	}
	build(1 , n + 1 , 1);
	s1[n + 1] = -1e9;
	for (int i = 0; i < n; ++i) {
		ans[i] = find(1 , n + 1 , 1 , s1[i]);
		if(i) update(1 , n , 1 , i);
		s1[i] = 0;
	}
	s1[n] = 0;
	for (int i = n; i >= 1; --i) {
		if(s[i] == 'p') s1[i] = s1[i + 1] + 1;
		else s1[i] = s1[i + 1] - 1;
	}
	s1[n + 1] = -1e9;
	build(1 , n + 1 , 1);
	int Ans = 0;
	for (int i = 1; i <= n; ++i) {
		int t = get_min(1 , n + 1 , 1 , i , ans[i - 1]);
		Ans = max(Ans , max(t - 1 , i) - i + 1);
	}
	printf("%d" , Ans);
	return 0;
} 

```

温馨提示，如果您的代码loj上40分，洛谷上80分参考以下数据：

```
5
ppppp
```

---

## 作者：Laoshan_PLUS (赞：0)

### 题意

给定一个由 $\texttt p$ 和 $\texttt j$ 组成的长度为 $n$ 的字符串，取一个子串 $S$，使得不管从左往右还是从右往左取，都保证每时每刻已取出的 $\texttt p$ 的个数不小于 $\texttt j$ 的个数。求 $\max\ \lvert S\rvert$。

### 解析

显然，我们可以把 $\texttt p$ 设为 $1$，把 $\texttt j$ 设为 $-1$，计算前缀和。

设 $a[i]$ 表示前缀和数组，那么我们发现：**$\boldsymbol{a[l-1]}$ 是区间 $\boldsymbol{[l-1,r]}$ 的最小值，而 $\boldsymbol{a[r]}$ 是区间 $\boldsymbol{[l-1,r]}$ 的最大值。**

所以我们要找到一个 **最小值在左端，而最大值在右端的最大区间**，显然单调栈维护。

### Talk is cheap. Show me the code.

```cpp
#include <bits/stdc++.h>
#define lp p << 1
#define rp p << 1 | 1
using namespace std;

constexpr int MAXN = 1e6 + 5;
int n, a[MAXN], r[MAXN], ans;
string ss;
stack<int> s;
struct SegTree {
	int l, r, c;
} st[MAXN << 2];

void build(int s, int t, int p) {
	st[p].l = s, st[p].r = t;
	if (s == t) {
		st[p].c = s;
		return;
	}
	int mid = (s + t) >> 1;
	build(s, mid, lp);
	build(mid + 1, t, rp);
	st[p].c = a[st[lp].c] > a[st[rp].c] ? st[lp].c : st[rp].c;
}

int sum(int l, int r, int p) {
	int s = st[p].l, t = st[p].r;
	if (l <= s && t <= r) return st[p].c;
	int mid = (s + t) >> 1;
	if (l > mid) return sum(l, r, rp);
	if (mid >= r) return sum(l, r, lp);
	int res1 = sum(l, r, lp), res2 = sum(l, r, rp);
	return a[res1] > a[res2] ? res1 : res2;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> ss;
	for (int i = 1; i <= n; i++) a[i] = a[i - 1] + (ss[i - 1] == 'p' ? 1 : -1);
	build(1, n, 1);
	s.push(n);
	for (int i = n - 1; i >= 0; i--) {
		while (!s.empty() && a[i] <= a[s.top()]) s.pop();
		// 找到i向右最远扩展到哪
		r[i] = s.empty() ? n : s.top() - 1;
		s.push(i);
		// sum(i+1,r[i],1)返回i+1到r[i]中最大的a的下标
		// 最大的a的下标，就是题目要求中满足题意的r，再减去i，就是以i为左端点这个满足题意最长的区间的长度
		// 枚举i，找最大值即可
		if (i + 1 <= r[i]) ans = max(ans, sum(i + 1, r[i], 1) - i);
	}
	cout << ans << '\n';
	
	return 0;
}
```

---

## 作者：Holy_Push (赞：0)

# 警告！这是一个跑的飞慢还巨长的做法！

经过几分钟的总结，我们可以知道，看到$POI$中非常像数据结构的题，并且数据范围为$n≤1000000$，那肯定会有一个很好想但比较烦的$O(nlogn)$做法，还会有一个很难想但很好写的$O(n)$做法……我是一个崇尚低思维的选手，所以就算再难码我也要用这种方法做！接下来我给出我做这道题时候的想法。我的做法是$nlogn$的。

我们先正着来，也就是先考虑从左往右取。

首先我们观察题目的要求。假设$sp[i],sj[i]$表示前$i$个字符中$p,j$的数量。那么如果区间$[l,r]$合法，那么对于任何$i∈[l,r]$，都有$sp[i]-sp[l-1]≥sj[i]-sj[l-1]$。移项得$sp[i]-sj[i]≥sp[l-1]-sj[l-1]$。

我们又发现，合法的区间一定是一段一段出现的。也就是说，如果$[l,r]$合法，那么$[l,l],[l,l+1]...[l,r-1],[l,r]$都是合法的（注意，我们仍然只考虑从左往右取）。而如果$[l,r]$不合法，那么$[l,r+1],[l,r+2]...[l,n]$都是不合法的。

于是我们可以考虑线段树。插入时，以$sp[i]-sj[i]$为下标（假设已经过某种操作都变成了正数），$i$为权值，从后往前插入。找右端点时，每次在$[1,sp[i-1]-sj[i-1]-1]$中找到最小的一个数，减一个$1$就是其右端点。这一部分应该很好考虑。于是我们得到了每个点的$rto$。如果某一位$i$上的字符是$j$，那么$rto[i]=i-1$，否则$[i,rto[i]]$就是最长的一个合法区间。

但是我们不仅要考虑正着来，还要考虑反着来。同样的做法，我们可以用同样的做法，得到每一位的左端点$lto$。

然后很显然，我们要对于每一个$i$，找到一个$j,j∈[lto[i],i],rto[j]≥i$，且这个$j$最小。我们显然可以再为$rto$建一棵线段树，然后在线段树上二分即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6,M=1e7;

int n,d[N],t[M],T[N*2],sp[N],sj[N],rto[N],lto[N],ans;
char c[N];

void update1(int i,int l,int r,int x,int y)
{
	t[i]=min(t[i],y);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (mid>=x) update1(i<<1,l,mid,x,y);
		else update1(i<<1|1,mid+1,r,x,y);
}

void update2(int i,int l,int r,int x,int y)
{
	t[i]=max(t[i],y);
	if (l==r) return;
	int mid=(l+r)>>1;
	if (mid>=x) update2(i<<1,l,mid,x,y);
		else update2(i<<1|1,mid+1,r,x,y);
}

int query1(int i,int l,int r,int x,int y)
{
	if (l>=x&&r<=y) return t[i];
	int mid=(l+r)>>1;
	if (mid>=y) return query1(i<<1,l,mid,x,y);
	if (mid<x) return query1(i<<1|1,mid+1,r,x,y);
	return min(query1(i<<1,l,mid,x,y),query1(i<<1|1,mid+1,r,x,y));
}

int query2(int i,int l,int r,int x,int y)
{
	if (l>=x&&r<=y) return t[i];
	int mid=(l+r)>>1;
	if (mid>=y) return query2(i<<1,l,mid,x,y);
	if (mid<x) return query2(i<<1|1,mid+1,r,x,y);
	return max(query2(i<<1,l,mid,x,y),query2(i<<1|1,mid+1,r,x,y));
}

void build(int i,int l,int r)
{
	if (l==r) {T[i]=rto[l];return;}
	int mid=(l+r)>>1;
	build(i<<1,l,mid);build(i<<1|1,mid+1,r);
	T[i]=max(T[i<<1],T[i<<1|1]);
}

int getQ(int i,int l,int r,int x,int y,int pos)
{
	if (T[i]<pos) return n+1;if (l==r) return l;
	int mid=(l+r)>>1;
	if (mid>=y) return getQ(i<<1,l,mid,x,y,pos);
		else if (mid<x) return getQ(i<<1|1,mid+1,r,x,y,pos);
			else
			{
				int ans=getQ(i<<1,l,mid,x,y,pos);
				if (ans==n+1) ans=getQ(i<<1|1,mid+1,r,x,y,pos);
				return ans;
			}
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=9999999;i++) t[i]=n+1;
	for (int i=1;i<=n;i++) 
	{
		c[i]=getchar();
		while (c[i]!='j'&&c[i]!='p') c[i]=getchar();
	}
	for (int i=1;i<=n;i++)
	{
		sp[i]=sp[i-1];sj[i]=sj[i-1];
		if (c[i]=='j') sj[i]++;else sp[i]++;
		d[i]=sp[i]-sj[i]+n+1;
	}
	d[0]=n+1;
	for (int i=n;i>=1;i--)
	{
		update1(1,1,n*2+1,d[i],i);
		rto[i]=query1(1,1,n*2+1,1,d[i-1]-1)-1;
	}	
	build(1,1,n);
	for (int i=1;i<=9999999;i++) t[i]=0;
	for (int i=0;i<=n;i++) sp[i]=sj[i]=d[i]=0;
	for (int i=n;i>=1;i--)
	{
		sp[i]=sp[i+1];sj[i]=sj[i+1];
		if (c[i]=='j') sj[i]++;else sp[i]++;
		d[i]=sp[i]-sj[i]+n+1;
	}
	d[n+1]=n+1;
	for (int i=1;i<=n;i++)
	{
		update2(1,1,n*2+1,d[i],i);
		lto[i]=query2(1,1,n*2+1,1,d[i+1]-1)+1;
	}
	for (int i=1;i<=n;i++)
		if (c[i]=='p')
		{
			int d=getQ(1,1,n,lto[i],i,i);
			ans=max(ans,i-d+1);
		}
	printf("%d\n",ans);
}
```


---

