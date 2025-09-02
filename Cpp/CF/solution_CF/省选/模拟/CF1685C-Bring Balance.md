# Bring Balance

## 题目描述

Alina 有一个长度为 $2n$ 的括号序列 $s$，由 $n$ 个左括号 `(` 和 $n$ 个右括号 `)` 组成。她想把这个括号序列变成一个平衡括号序列。

平衡括号序列定义为：能通过插入字符 `+` 和 `1` 使之成为合法数学表达式的序列。例如，序列 `(())()`、`()` 和 `(()(()))` 是平衡的，而 `)(`、`(()` 和 `(()))(` 就不是的。

在一次操作中，她可以反转 $s$ 的任意子串。

请求出最少几次操作可将 $s$ 转换为平衡括号序列。可以证明，这总是能在 $n$ 次操作中完成。

## 说明/提示

在第一组数据中，字符串已经平衡。

在第二组数据中，字符串转换如下：`())((()))(`$\to$`()()(()))(`$\to$`()()(())()`，最后一个字符串是平衡的。

在第三组数据中，字符串最终将被转换为 `((()))((()))`。

## 样例 #1

### 输入

```
3
2
(())
5
())((()))(
6
())((()))(()```

### 输出

```
0
2
3 4
9 10
1
2 11```

# 题解

## 作者：luogubot (赞：19)

给定一个由 $n$ 个 `(` 与 $n$ 个 `)` 组成的括号串，求出最少翻转多少个区间可以使得整个括号串合法，并构造一组方案。$1\leq n\leq 10^5$。

令左括号为 $+1$，右括号为 $-1$，需要使得最终序列前缀和都非负。

> 结论：任意括号串只需要翻转不超过 2 个区间。

证明：令 $a_i$ 表示把括号看成 $+1,-1$ 后的 $[1,i]$ 的前缀和，则找到 $a_x$ 值最大的任意一个 $x$，翻转 $[1,x],[x+1,2n]$ 必定合法。考虑翻转后的前缀和 $b_j$，在 $j\leq x$ 时等于 $a_x-a_{x-j}\ge 0$；在 $j>x$ 时等于 $a_x+a_{2n}-a_{j'-1}$，其中 $j'$ 是 $j$ 在翻转前的位置，由于 $a_{2n}=0$，所以 $a_x-a_{j'-1}\ge 0$。

不需要翻转的情况判一下就好了，问题转到了是否存在只翻转一个区间的方案。令 $l,r$ 是最前和最后一个前缀和小于 0 的位置，那么最终翻转的区间 $[L,R]$ 一定要满足 $L\leq l,R>r$，最终 $[1,L),(R,2n]$ 的前缀和没有改变，考虑 $i\in[L,R]$ 的新前缀和 $b_i=a_{L-1}+a_{R}-a_{i'}$，其中 $i'$ 是 $i$ 翻转前的位置，同样在 $[L,R]$ 中。那么需要 $a_{L-1}+a_{R}\ge a_i$ 对于 $i\in[L,R]$ 恒成立，于是贪心地选择 $L\leq l,R>r$ 且 $a_{L-1},a_{R}$ 最大的 $[L,R]$ 检验即可。

时间复杂度 $O(n)$。

---

## 作者：lxzy_ (赞：14)

~~写篇题解记录一下学长讲的为数不多能听懂的题~~

~~如果觉得废话太多可以直接看末尾结论~~

遇到括号序列、$01$ 串，并且要考虑其前缀的，可以转化成折线图，即将左括号看成 $+1$，右括号看成 $-1$，并计算序列中每个位置的前缀和，可以得到一个折线图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ifzuwl16.png)

题目中说 $0$ 和 $1$ 的数量相等，因此 $1$ 和 $n\times 2$ 对应的高度均为 $0$.

我们的目标便是将所有低于 $x$ 轴的点翻上来。

而我们能够进行的操作是区间反转，假设我们反转如下红色线段围住的区间：

![](https://cdn.luogu.com.cn/upload/image_hosting/zelzgcvw.png)

黑色是反转前的线段，绿色是反转后的线段，可以看出，对应点及其高度均关于两点连线（紫色线段）的中点中心对称， __也就是每次反转区间 $[l,r]$ 相当于将内部所有点变成关于线段 $lr$ 的中点的中心对称点。__

每次将某些低于 $x$ 轴的部分翻上去，就可能会有一些高于 $x$ 轴的部分翻下去，我们不希望这种事情发生，因此想办法处理。而其中原先高度最高的反转后高度肯定最低，只需要考虑它即可。


考虑反转了区间 $[l,r]$，原先高度最高的点为 $a$，反转后的点为 $a'$。当最高点刚好落在 $x$ 轴上时：

![](https://cdn.luogu.com.cn/upload/image_hosting/1arwocwb.png)

（其中相同颜色标注的线段相等）

我们有：

$$\frac{1}{2}h_a=\frac{1}{2}(h_l+h_r)$$

即：

$$h_a=h_l+h_r$$

__也就是说当 $[l,r]$ 中所有的 $a$ 满足 $h_a\leq h_l+h_r$ 时，反转 $[l,r]$ 后没有点会跑到 $x$ 轴下方。__

__结论：__

也就是说若能找到一个 $l$ 和 $r$ 满足上述条件，且在 $x$ 轴下方的点全部在 $[l,r]$ 之间，那么我们可以通过翻转一次 $[l,r]$ 直接得到答案。当然，在具体实现中，使用贪心策略，设 $p_l$ 为最左的低于x轴的点，设 $p_r$ 为最右的低于x轴的点，那么只需记录 $[1,p_l]$ 和 $[p_r,n\times 2]$ 中最高的点作为 $l,r$ 即可。

那如果不能一次搞定呢？那肯定是全部 $[l,r]$ 中都包含一个很高的 $x$，而这个 $x$ 肯定是所有点中高度最高的一个。于是我们可以 ~~化敌为友~~ ，直接反转 $[1+x]$ 和 $[x+1,n\times 2]$，共两次。（因为这两个区间内没有任何一个数大于 $x$ 的）

然后献上又臭又长的代码qwq：

```cpp
#include<cstdio>
#include<iomanip>
#define INF 0x7f7f7f7f
using namespace std;
const int N=2e5+50;
char s[N];
int h[N],pm,pk[N],ed1,ed2;
//pm记录最高点，pk记录所有低于x轴的点 
int n,t;
inline int Max(int a,int b){return a>b?a:b;}


pair<int,int> Work(int l,int r)//计算区间的最大值 
{
	int maxn=-INF,pos=0;
	for(int i=l;i<=r;i++){
		if(h[i]>maxn){
			maxn=h[i],pos=i;
		}
	}
	return make_pair(maxn,pos);
}
bool Check()
{
	int ml=0,mr=0,mm=0;
	pair<int,int> l,r,mid; 
	
	
	//注意这里h[i]表示i的前缀和，因此0才表示第一个括号，下面输出左区间+1也是同理 
	l=Work(0,pk[1]);
	mid=Work(pk[1],pk[ed2]);
	r=Work(pk[ed2],n*2);
	
	if(l.first+r.first>=mid.first){//有区间满足条件 
		printf("1\n");
		printf("%d %d\n",l.second+1,r.second);
		return true;
	}
	return false;
}
void Print()
{
	if(!ed2){//原序列为合法序列，不需要反转 
		printf("0\n");
		return ;
	}
	if(!Check()){//若没有区间满足条件 
		printf("2\n");
		printf("1 %d\n%d %d\n",pm,pm+1,2*n);
	}
}
void Pre()//初始化点的高度 
{
	ed1=ed2=0;
	for(int i=1;i<=n*2;i++){
		if(s[i]=='(') h[i]=h[i-1]+1;
		else h[i]=h[i-1]-1;
	}
}

void Solve()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	Pre();
	int maxn=-INF;//注意有的点可能小于0，因此 maxn 不能设为0，上同 
	for(int i=1;i<=n*2;i++){
		if(h[i]>=maxn){
			pm=i;
			maxn=h[i];
		}
		if(h[i]<0) pk[++ed2]=i;
	}
}
int main()
{
	scanf("%d",&t);
	while(t--){
		Solve();
		Print();
	}
	return 0;
}
```

然后就讲完力（喜）

---

## 作者：syf2008 (赞：3)

题意：

给定一个由 $n$ 个 `(` 与 $n$ 个 `)` 组成的括号串，求出最少翻转多少个区间可以使得整个括号串合法，并构造一组方案。

$1\le n \le 10^5$

做法：

一个做括号串很典的想法，把 `(` 记为 $+1$，把 `)` 记为 $-1$，我们可以从一个括号序列得到一张折线图。

![](https://cdn.luogu.com.cn/upload/image_hosting/0ehk78i7.png)

若要使一个括号串合法，那就需要保证，在折线图中不能出现小于 $0$ 的点。所以我们的目标便是将所有小于 $0$ 的点翻上来。翻转的方式是关于一个点中心对称。那么我们就要找到这个中心对称点。

我们可以证明，这个次数最多不会超过 $2$ 次。

设我们翻转的左端点在折线图中坐标为 $(X_L,Y_L)$，右端点在折线图中坐标为 $(X_R,Y_R)$，通过手玩不难发现，中心对称点的坐标为 $(\frac{X_L+X_R}{2},\frac{Y_L+Y_R}{2})$。

每次翻转的时候，肯定是一部分高于中心对称点的点翻下去，低于中心对称点的点翻上去。我们不希望答案更劣，所以我们要让上面翻下去的尽可能小。其中原先高度最高的反转后高度肯定最低，只需要考虑它即可。

设最高点位置 $(X_{\max},Y_{\max})$ ，中心对称后的坐标为 $(X_{\min},Y_{\min})$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5wyl5dp7.png)

根据初中数学的中点式子，我们不难列出下列等式：

$\frac{Y_{\max}+Y_{\min}}{2}=\frac{Y_L+Y_R}{2}$

得到 $Y_{\max}+Y_{\min}=Y_L+Y_R$

又因为翻转后点位置不能小于 $0$，所以最劣情况为 $Y_{\min}=0$。

得到 $Y_{\max}=Y_L+Y_R$ 时，达到最劣情况，若此时$Y_{\max}$ 继续增大，翻转点将会 $<0$。

所以我们可以找到折线图中的最高点，设为 $P$，将 $[1,P]$ 和 $[P+1,2n]$ 翻转，这样就可以保证操作次数 $\le 2$。

因为题目保证给定的是一个左括号和右括号相等的字符串，所以在 $1$ 和 $2n$ 的位置一定是 $0$。根据 $Y_{\max}=Y_L+Y_R$，因为折线图最高点为 $P$，所以区间内不存在一个位置高于 $P$。

注意特判一开始没有一个点低于 $0$，和一次翻转就能解决的情况。

---

## 作者：Purslane (赞：2)

# Solution

本题的重点在于猜到答案的上界。

将括号序列变为 $\pm 1$ 序列并取前缀和，得到 $pre$ 序列。取 $pre$ 序列的最大值，假设在位置 $p$，则翻转 $[1,p]$ 和 $[p+1,n+n]$ 显然符合要求。

因此答案 $\le 2$，我们只需要判断是否为 $0/1$，其他情况就是 $2$。

$0$ 是好判断的，直接扫描一遍观察是否是合法括号序列。

如果答案是 $1$，对于 $pre_i<0$ 的所有位置 $i$，显然要被覆盖在我们的翻转区间中。假设最终的翻转区间为 $[L,R]$，则对于 $\forall L \le i \le R$，$pre'_i=pre_{L-1}+pre_R-pre_i$，也就是 $pre_{L-1} + pre_R \ge pre_i$ 对于所有的 $L \le i \le R$ 都成立。这样选取能包含所有 $<0$ 位置最大的 $pre_{L-1}$ 和 $pre_{R}$ 显然最优。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int T,n,pre[MAXN];
string S;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>S,S="&"+S;
		ffor(i,1,n+n) {
			if(S[i]=='(') pre[i]=pre[i-1]+1;
			else pre[i]=pre[i-1]-1;
		}
		if(*min_element(pre+1,pre+n+n+1)==0) cout<<0<<'\n';	
		else {
			int p1=0,p2=0;
			pair<int,int> v1,v2;
			ffor(i,1,n+n) if(pre[i]<0) {
				if(!p1) p1=i;
				p2=i;
			}
			v1=v2={-1,0};
			ffor(i,0,p1) v1=max(v1,{pre[i],i});
			ffor(i,p2,n+n) v2=max(v2,{pre[i],i});
			int flg=1;
			ffor(i,p1,p2) flg&=(v1.first+v2.first>=pre[i]);
			if(flg) cout<<1<<'\n'<<v1.second+1<<' '<<v2.second<<'\n';
			else {
				cout<<2<<'\n';
				int mx=*max_element(pre+1,pre+n+n+1),pos=0;
				ffor(i,1,n+n) if(pre[i]==mx) pos=i;
				cout<<1<<' '<<pos<<'\n'<<pos+1<<' '<<n+n<<'\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：hfjh (赞：1)

# C. Bring Balance

## 题意

给你一个括号序列，你可以翻转任意子串，问最少几次反转成合法括号序列。

翻转指 `ABC->CBA`。

## 题解

看到括号序列就先想把折线图画出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/8yp5ce71.png)

样例 `())((()))(()`。

把 `(` 看做 $+1$，`)` 看做 $-1$，点坐标就是前缀和。

我们发现操作区间 $[l,r]$ 等同在折线图上把区间 $[l,r]$ 里面的图形按照 $l$ 点和 $r$ 点的中点进行中心对称。

我们发现找出全局最高的点 $w$，将 $[1,w]$ 和 $[w + 1, n]$ 操作一定会使括号序列合法，所以最多操作两次。

接下来考虑只操作一个区间 $[l,r]$ 的情况。

首先在 $y=0$ 以下的点必须被翻转到，我们找到左边第一个在 $y=0$ 以下的点，$l$ 一定在这个区间内找，$r$ 同理。

在区间内找一个最高的点，这样 $l,r$ 的中点尽可能高，本身在上面的点更不容易翻下去。

然后 `check` 一下合不合法。

注意特判不需要操作的情况。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
int t, n, a[N], pr[N];
int flag0 = 1, flag1 = 1; 
int l, r, mxl, mxr, wl, wr;
int mx, w;
char x;
void input(){
	cin >> n; n *= 2;
	for(int i = 1; i <= n; ++i){
		cin >> x; 
		if(x == '(') a[i] = 1;
		else a[i] = -1;	
	} 
}
void op(){
	mx = mxl = mxr = -1e9;
	flag0 = flag1 = 1;
	for(int i = 1; i <= n; ++i) pr[i] = pr[i - 1] + a[i]; 
	for(int i = 1; i <= n; ++i) if(pr[i] < 0) flag0 = 0;
	if(flag0){
		cout<<0<<'\n';
		return ;
	}
	for(int i = 0; i <= n; ++i) if(pr[i] < 0) {l = i; break;}
	for(int i = n; i >= 0; --i) if(pr[i] < 0) {r = i; break;}
	for(int i = 0; i <= l; ++i){
		if(mxl < pr[i]){
			mxl = pr[i];
			wl = i;
		}
	}
	for(int i = r; i <= n; ++i){
		if(mxr < pr[i]){
			mxr = pr[i];
			wr = i;
		}
	}
	for(int i = wl; i <= wr; ++i){
		if(mxl + mxr - pr[i] < 0) flag1 = 0;
	}
	if(flag1){
		cout<<1<<'\n';
		cout<<wl + 1<<' '<<wr<<'\n';
		return ;
	}
	for(int i = 1; i <= n; ++i){
		if(mx < pr[i]){
			mx = pr[i];
			w = i;
		}
	}
	cout<<2<<'\n';
	cout<<1<<' '<<w<<'\n';
	cout<<w + 1<<' '<<n<<'\n';
}
int main(){
	cin >> t;
	while(t--){
		input();
		op();
	}
	
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

这是本题目前最详细、最严谨的题解。本题的结论属实是太神了，很难想。

本文中的 $n$ 表示题目中的 $2n$。

考虑**确定上下界**。

引理：操作次数不会超过 $2$。

> 证明：把左括号看成 $1$，右括号看成 $-1$，则括号序列合法的条件等价于这个 $1,-1$ 序列的每一个前缀和 $s_i$ 都非负。找到令 $s_i$ 最大的 $s_{mxi}$，反转 $[1,mxi],[mxi+1,n]$ 是一定可以满足要求的。
>
> 为什么呢？反转过后的括号序列的前缀和数组是这样的：$[s_{mxi}-s_{mxi-1},s_{mxi}-s_{mxi-2},\cdots,s_{mxi}-s_0,s_{mxi}+s_n-s_{n-1},s_{mxi}+s_n-s_{n-2},\cdots,s_{mxi}+s_n-s_{mxi}]$。由于 $s_{mxi}$ 是最大的，因此总有 $s_{mxi}-s_j\ge 0$。又因为题目中保证了 $s_n=0$，故原命题得证。

现在我们已经知道了上限以及构造方法，下面只需要判断是否可以使用更少的操作次数完成。

如果原先括号序列就是合法的，则答案为 $0$，先判掉。

考虑贪心判断是否一次操作即可完成。这次操作一定要包含进所有 $s_i<0$ 的 $i$，因此先找出 $s$ 中第一个和最后一个 $<0$ 的位置 $l,r$。找到最大的 $s_{mxl},s_{mxr}$ 其中 $0\le mxl<l,r\le mxr\le n$。

引理：最优的策略一定是反转 $[mxl+1,mxr]$。也就意味着，如果这样反转不成，就一定不可能一次反转就成功。

> 证明：反转过后的括号序列的前缀和数组是这样的：$[s_1,\cdots,s_{mxl},s_{mxl}+s_{mxr}-s_{mxr-1},s_{mxl}+s_{mxr}-s_{mxr-2},\cdots,s_{mxl}+s_{mxr}-s_{mxl},s_{mxr+1},\cdots,s_n]$。最优的策略一定能让新的前缀和数组的每个元素尽可能大。现在，中间的每一项都加上了左边、右边最大的 $s_{mxl},s_{mxr}$，易证其它方案一定没有本方案优。

上述的证明也给出了操作次数为 $1$ 的构造方法。如果验证了不行，则必须操作 $2$ 次。

```cpp
// Title:  Bring Balance
// Source: CF1685C
// Author: Jerrywang
#include <cstdio>
#include <iostream>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=200010, inf=0x3f3f3f3f;
using namespace std;

int T, n, a[N]; char s[N];

void solve()
{
    scanf("%d%s", &n, s+1); n+=n; bool ok=1;
    rep(i, 1, n)
    {
        if(s[i]=='(') a[i]=a[i-1]+1;
        else a[i]=a[i-1]-1;
        ok&=a[i]>=0;
    }
    if(ok) return puts("0"), void();
    int l=1;
    while(l<=n && a[l]>=0) l++;
    int r=n;
    while(r && a[r]>=0) r--;
    int mx=-inf, mxi=0, mx1=-inf, mx1i=0; ok=1;
    rep(i, r, n) if(a[i]>mx) mx=a[i], mxi=i;
    rep(i, 0, l-1) if(a[i]>mx1) mx1=a[i], mx1i=i;
    rep(i, mx1i+1, mxi) if(mx-a[i-1]+mx1<0) ok=0;
    if(ok)
    {
        puts("1");
        printf("%d %d\n", mx1i+1, mxi); return;
    }
    mx=-inf, mxi=0;
    rep(i, 1, n) if(a[i]>mx) mx=a[i], mxi=i;
    puts("2");
    printf("%d %d\n%d %d\n", 1, mxi, mxi+1, n);
}

int main()
{
#ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin); ios::sync_with_stdio(0);
#endif
    scanf("%d", &T); while(T--) solve();
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

思路：

首先显然先想到将括号序列换成 $1$ 与 $-1$ 的序列，要求前缀和非负。

然后有一个结论：操作次数不超过 $2$
考虑前缀和最大的点 $x$，两次操作分别操作 $[1,x]$ 与 $[x+1,2n]$。

反证法证明两个前缀和单调，否则这个就不是最大点。

然后不用操作的判掉很简单，关键是一次操作的序列。

考虑 $l$ 为最早的前缀和小于 $0$ 的点，$r$ 为最大的前缀和小于 $0$ 的点，那么我们要操作的区间 $[L,R]$ 一定包含 $l,r$。

因为希望把最多的")"运到后面，把最多的"("运到前面，那么 $L$ 与 $R$ 分别取 $[1,l]$ 区间最大值与 $[r,2n]$ 区间最大值即可。然后检查能不能做到。时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
#define I inline
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define ll long long
#define db double
#define lb long db
#define N (200000+5)
#define M (400+5)
#define K (3000000+5)
#define mod 998244353
#define Mod (mod-1)
#define eps (1e-9)
#define ull unsigned ll
#define it iterator
#define Gc() getchar() 
#define Me(x,y) memset(x,y,sizeof(x))
#define Mc(x,y) memcpy(x,y,sizeof(x))
#define d(x,y) (n*(x-1)+(y))
#define R(n) (1ll*rand()*rand()%(n)+1)
#define Pc(x) putchar(x)
#define LB lower_bound
#define UB upper_bound
#define PB push_back
using namespace std;
int T,n,Mx,Q[N],W[N],m,L,R;char s[N],p[N];
I void Solve(){
	int i,j;scanf("%d",&n);m=2*n;scanf("%s",s+1);for(i=1;i<=m;i++) Q[i]=Q[i-1]+(s[i]^'('?-1:1);
	L=1;R=m;while(L<=m&&Q[L]>=0) L++;while(R&&Q[R]>=0) R--;if(L>R){puts("0");return;}for(i=L;i;i--) Q[i]>Q[L-1]&&(L=i+1);for(i=R;i<=m;i++) Q[i]>Q[R]&&(R=i);Mc(p,s);reverse(p+L,p+R+1);
	Mx=1;for(i=2;i<=m;i++) Q[i]>Q[Mx]&&(Mx=i);for(i=1;i<=m;i++) W[i]=W[i-1]+(p[i]^'('?-1:1);for(i=1;i<=m;i++) if(W[i]<0) {printf("2\n%d %d\n%d %d\n",1,Mx,Mx+1,m);return;}
	printf("1\n%d %d\n",L,R);
}
int main(){
	freopen("1.in","r",stdin);
	scanf("%d",&T);while(T--) Solve();
} 
```


---

## 作者：Hanx16Kira (赞：0)

# Bring Balance

[Luogu CF1685C](https://www.luogu.com.cn/problem/CF1685C)

## Solution

考虑将括号序列转化成为折线图，`(` 看作是 $(+1,+1)$，`)` 看作是 $(+1,-1)$，那么考虑一次翻转在折线图上有什么性质。假设翻转的区间为 $[l,r]$，折线图在 $x=l$ 处的坐标为 $(l,a)$，在 $x=r$ 处的坐标为 $(r,b)$，那么这次翻转相当于是将 $[l,r]$ 之间的所有点关于 $(\dfrac{l+r}{2},\dfrac{a+b}{2})$ 中心对称。问题变成如何翻转使得这个折线图所有部分都在 $x$ 轴之上。

观察发现，最多只需要两次操作就可以使得原序列符合条件。一个点 $(c,d)$ 关于 $(\dfrac{l+r}2,\dfrac{a+b}2)$ 会中心对称到 $(l+r-c,a+b-d)$。设全局最大值的位置为 $p$，那么翻转 $[1,p)$ 和 $(p,2n]$ 一定是一个合法解。对于 $[1,p)$ 中的点 $(c,d)$，有 $d\le y_p$，也就是说 $a+y_p-d=y_p-d\ge 0$，也就意味着这样翻转后，$[1,p)$ 中的所有点都将在 $x$ 轴之上。$(p,2n]$ 同理。

那么只需要判断是否存在 $1$ 次操作或者原本就是合法序列的情况。不操作的情况显然好做。对于只需要一次操作的，先找到第一个和最后一个 $y<0$ 的点 $p_1,p_2$，那么翻转的区间 $[L,R]$ 一定有 $L\le p_1,R\ge p_2$，并且 $L,R$ 选的位置 $y$ 越大越好。那么直接找 $[1,p_1)$ 和 $(p_2,2n]$ 中的最大值出现的位置作为 $L,R$，然后暴力验证即可。

时间复杂度 $\mathcal O(n)$。

```cpp
// Cirno is not baka!
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define Rof(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define FILE(filename) { \
    freopen(#filename ".in", "r", stdin); \
    freopen(#filename ".out", "w", stdout); \
}
#define All(x) x.begin(), x.end()
#define rAll(x) x.rbegin(), x.rend()
#define pii pair<int, int>
#define fi first
#define se second
#define i64 long long
#define mkp make_pair
// #define int long long
#define epb emplace_back
#define pb push_back
using namespace std;

const int _N = 2e5 + 5, mod = 1e9 + 7, inf = 1e9;
template<typename T> void Max(T &x, T y) {x = max(x, y);}
template<typename T> void Min(T &x, T y) {x = min(x, y);}

namespace BakaCirno {
    int N;
    int A[_N], B[_N];
    bool Check0() {
        return *min_element(A + 1, A + 2 * N + 1) >= 0;
    }
    bool Check1() {
        int p1 = 2 * N + 1, p2 = 0;
        For(i, 1, 2 * N) if (A[i] < 0)
            Min(p1, i), Max(p2, i);
        int l = max_element(A, A + p1 + 1) - A + 1;
        int r = max_element(A + p2 + 1, A + 2 * N + 1) - A;
        reverse(B + l, B + r + 1);
        partial_sum(B + 1, B + 2 * N + 1, B + 1);
        if (*min_element(B + 1, B + 2 * N + 1) >= 0) {
            cout << 1 << '\n';
            cout << l << ' ' << r << '\n';
            return 1;
        }
        return 0;
    }
    void _() {
        cin >> N;
        For(i, 1, 2 * N) {
            char c; cin >> c;
            B[i] = (c == '(' ? 1 : -1);
            A[i] = B[i] + A[i - 1];
        }
        if (Check0()) return cout << 0 << '\n', void();
        if (Check1()) return ;
        cout << 2 << '\n';
        int p = max_element(A + 1, A + 2 * N + 1) - A;
        cout << 1 << ' ' << p - 1 << '\n';
        cout << p + 1 << ' ' << 2 * N << '\n';
    }
}

signed main() {
    // FILE(test);
    cin.tie(0)->sync_with_stdio(0); int T = 1;
    cin >> T;
    while (T--) BakaCirno::_();
    // fout.flush();
}
```

---

