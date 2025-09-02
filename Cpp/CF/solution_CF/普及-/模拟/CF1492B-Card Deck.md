# Card Deck

## 题目描述

You have a deck of $ n $ cards, and you'd like to reorder it to a new one.

Each card has a value between $ 1 $ and $ n $ equal to $ p_i $ . All $ p_i $ are pairwise distinct. Cards in a deck are numbered from bottom to top, i. e. $ p_1 $ stands for the bottom card, $ p_n $ is the top card.

In each step you pick some integer $ k > 0 $ , take the top $ k $ cards from the original deck and place them, in the order they are now, on top of the new deck. You perform this operation until the original deck is empty. (Refer to the notes section for the better understanding.)

Let's define an order of a deck as $ \sum\limits_{i = 1}^{n}{n^{n - i} \cdot p_i} $ .

Given the original deck, output the deck with maximum possible order you can make using the operation above.

## 说明/提示

In the first test case, one of the optimal strategies is the next one:

1. take $ 1 $ card from the top of $ p $ and move it to $ p' $ : $ p $ becomes $ [1, 2, 3] $ , $ p' $ becomes $ [4] $ ;
2. take $ 1 $ card from the top of $ p $ : $ p $ becomes $ [1, 2] $ , $ p' $ becomes $ [4, 3] $ ;
3. take $ 1 $ card from the top of $ p $ : $ p $ becomes $ [1] $ , $ p' $ becomes $ [4, 3, 2] $ ;
4. take $ 1 $ card from the top of $ p $ : $ p $ becomes empty, $ p' $ becomes $ [4, 3, 2, 1] $ .

 In result, $ p' $ has order equal to $ 4^3 \cdot 4 + 4^2 \cdot 3 + 4^1 \cdot 2 + 4^0 \cdot 1 $ $ = $ $ 256 + 48 + 8 + 1 = 313 $ .In the second test case, one of the optimal strategies is:

1. take $ 4 $ cards from the top of $ p $ and move it to $ p' $ : $ p $ becomes $ [1] $ , $ p' $ becomes $ [5, 2, 4, 3] $ ;
2. take $ 1 $ card from the top of $ p $ and move it to $ p' $ : $ p $ becomes empty, $ p' $ becomes $ [5, 2, 4, 3, 1] $ ;

 In result, $ p' $ has order equal to $ 5^4 \cdot 5 + 5^3 \cdot 2 + 5^2 \cdot 4 + 5^1 \cdot 3 + 5^0 \cdot 1 $ $ = $ $ 3125 + 250 + 100 + 15 + 1 = 3491 $ .In the third test case, one of the optimal strategies is:

1. take $ 2 $ cards from the top of $ p $ and move it to $ p' $ : $ p $ becomes $ [4, 2, 5, 3] $ , $ p' $ becomes $ [6, 1] $ ;
2. take $ 2 $ cards from the top of $ p $ and move it to $ p' $ : $ p $ becomes $ [4, 2] $ , $ p' $ becomes $ [6, 1, 5, 3] $ ;
3. take $ 2 $ cards from the top of $ p $ and move it to $ p' $ : $ p $ becomes empty, $ p' $ becomes $ [6, 1, 5, 3, 4, 2] $ .

 In result, $ p' $ has order equal to $ 6^5 \cdot 6 + 6^4 \cdot 1 + 6^3 \cdot 5 + 6^2 \cdot 3 + 6^1 \cdot 4 + 6^0 \cdot 2 $ $ = $ $ 46656 + 1296 + 1080 + 108 + 24 + 2 = 49166 $ .

## 样例 #1

### 输入

```
4
4
1 2 3 4
5
1 5 2 4 3
6
4 2 5 3 6 1
1
1```

### 输出

```
4 3 2 1
5 2 4 3 1
6 1 5 3 4 2
1```

# 题解

## 作者：KSToki (赞：5)

纪念 fst 场。
# 题目大意
给定一个 $n$ 的排列，每次可以将前任意 $k$ 个数**作为一个整体**放入栈中，求最终字典序最大的排列。
# 题目分析
还是比较简单的。既然要最大，那么一定是 $n$ 开头，则 $n$ 以后的数应与 $n$ 作为一个整体放进去。此时剩的是前一截，递归处理即可。

还有一种方法就是从后往前扫，扫过一个数给它打上标记，扫到当前最大值时把当前位置到上一个位置之间的数直接输出。这里不需要特判 $a_1$，可以证明最终它一定会成为当前最大值。
# 代码
用的是后一种方法。
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[100001];
bool h[100001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(R int i=1;i<=n;++i)
			a[i]=read(),h[i]=0;
		int p=n,lst=n+1;
		for(R int i=n;i;--i)
		{
			if(a[i]==p)
			{
				for(R int j=i;j<lst;++j)
					printf("%d ",a[j]);
				lst=i;
				--p;
				while(h[p])
					--p;
			}
			h[a[i]]=1;
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：xuezhe (赞：3)

场上随便猜了个结论：每次一定是找到序列中剩余数的最大值，然后把它连带后面一起塞到新序列中。

感性理解一下就是这个长得其实像一个 $n$ 进制数的形式，所以大致可证字典序越大，最终得到的价值越大，而最大化字典序直接用上面的方法就好了。

每次后缀取最大值其实取出的就相当于是倒着取出每个前缀最大值。

预处理出每个前缀最大值，然后按从大到小的顺序取出来就好了。

时间复杂度 $O(n)$。

Code:
```cpp
const int N(100005);
int t,n,p[N];
vector<int> v;
 
void fakemain(){
    Read(t);
    while(t--){
        v.clear();
        Read(n);
        for(int i=1;i<=n;++i){
            Read(p[i]);
            if(!v.size() || p[v.back()]<p[i])
                v.push_back(i);
        }
        v.push_back(n+1);
        for(int i=v.size()-2;~i;--i)
            for(int j=v[i];j<v[i+1];++j)
                Print(p[j],32);
        putchar(10);
    }
}
```

---

## 作者：Tenshi (赞：3)

化简一下式子，发现就是要求**字典序最大**的序列，按照操作规则，对于整堆牌，应该将最大的（以及它下面的牌）留在底部最后再放到另一堆，

类似的，对于最大的牌**上面的牌**，也是将最大的（以及它下面的牌）留在底部最后再放到另一堆，如此下去即可。

注意到操作过程需要维护**区间最大值**，可以打个`ST表`。

```
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define SET0(a) memset(a,0,sizeof(a))
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define DWN(i,a,b) for(int i=(a);i>=(b);i--)
#define INF 0x3f3f3f3f
typedef long long ll;

const int N=1e5+5,M=20;

int n;
int a[N];

//st
int st[N][M];
int Log[N];
void pre(){
    Log[1]=0;
    FOR(i,2,N-1) Log[i]=Log[i/2]+1;
}

void init(){
    FOR(j,0,M-1)
        for(int i=1;i+(1<<j)-1<=n;i++)
            if(!j) st[i][j]=a[i];
            else st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
}

int query(int l,int r){
    int s=Log[r-l+1];
    return max(st[l][s],st[r-(1<<s)+1][s]);
}

int main(){
	int T; cin>>T;
	pre();
	while(T--){
		cin>>n;
		FOR(i,1,n) cin>>a[i];
		init();

		int pt=n;
		DWN(i,n,1){
			int num=query(1,pt);
			//cerr<<num<<endl;
			if(a[i]==num){
				FOR(j,i,pt) cout<<a[j]<<' ';
				if(i-1) pt=i-1;
			}
		}
		cout<<endl;
	}
    return 0;
}
```

---

## 作者：超级玛丽王子 (赞：2)

## 题意翻译
给定序列 $[p_1,\cdots, p_n]$，试将其分为若干个子区间 $[{r_1},{r_2},\cdots,{r_m}]$ 并对区间序列 $r$ 倒序排列，使得排列后的新序列 $[q_1,q_2,\cdots,q_n]$ 满足 $\sum\limits_{i=1}^n n^{n-i}q_i$ 最大。求新序列。
## 解法
一个很显然的贪心。可以考虑计算结果为一个**不进位**的 $n$ 进制数 $\overline{q_1q_2q_3\cdots q_n}$，满足每一位都是正整数（$\forall _{q_i} q_i\ge0$）。_如果不理解这一点，请参考位值原理。_ 

显然，这个数的**字典序**越大，这个数就越大。因此我们可以考虑对序列 $p$ 记录**前缀最大值**序列 $m$，其中 $m_i=\max\limits_{1\le j\le i}\{p_j\}$。接下来从 $p_n$ 开始倒序扫描序列，一旦遇到**当前所在这一区间**（即还没有挪走的牌）中的最大值，就挪一次牌，使得新序列字典序最大。简单证明如下：
>设当前区间为 $[1,k]$，设当前区间次大值为 $m'_k$，$\operatorname{pos}_{<array>} m_i$ 表示 $m_i$ 在序列 $<array>$ 中的位置。假如不在 $m_k$ 处挪牌，而在 $m'_k$ 处挪牌，那么：
>	
>1. 若 $\operatorname{pos}_pm'_k>\operatorname{pos}_pm_k$，挪牌后 $\operatorname{pos}_qm_k$ 必然大于 $\operatorname{pos}_pm'_k$。也就是说新序列字典序在第 $\operatorname{pos}_pm'_k$ 位上不是最优的；
>2. 若 $\operatorname{pos}_pm'_k<\operatorname{pos}_pm_k$，挪牌后 $\operatorname{pos}_qm_k$ 仍必然大于 $\operatorname{pos}_pm'_k$。也就是说新序列字典序在第 $\operatorname{pos}_pm'_k$ 位上不是最优的。
>
>$\therefore Q.E.D.$

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T;
int n;
int a[N],mx[N],pos=0,last,b[N];
inline int read() {
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	int x=0;
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return x;
}
inline int write(int x) {
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int main(void) {
	T=read();
	while(T--) {
		n=read();
		pos=0,last=n+1;
		for(int i=1;i<=n;++i) a[i]=read(),mx[i]=max(mx[i-1],a[i]);
		for(int i=n;i>=1;--i) {
			if(a[i]==mx[i]) {
				for(int j=i;j<last;++j) b[++pos]=a[j];
				last=i;
			}
		}
		for(int i=1;i<=n;++i) write(b[i]),putchar(' ');
		putchar('\n');
	}
	return 0;
}
```
  
完结撒花~

---

## 作者：vectorwyx (赞：1)

把牌堆抽象成一个 $1\sim n$ 的排列，排列的值即为把这个排列看作 $n$ 进制数后的大小。所以最优方案就是贪心地查找剩下的数中的最大值，然后把它以及位于它后面的数全部放到目标牌堆中。核心操作为查找前缀最大值，用桶来维护就能做到 $O(n)$（当然也有其他方法）。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e6+5;
int a[N],b[N];

void work(){
	int n=read();
	fo(i,1,n) a[i]=read(),b[i]=1;
	int mx=n;
	go(i,n,1){
		int pos=i;
		while(pos&&a[pos]<mx) pos--;
		fo(j,pos,i) printf("%d ",a[j]),b[a[j]]=0;
		while(mx&&b[mx]==0) mx--;
		i=pos;
	}
	puts("");
}

int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：HC20050615 (赞：1)

# 翻译
你有一叠牌，共有 $n$ 张，编为 $p_1\sim p_n$（其中 $p_1$ 为最下面， $p_n$ 为最上面）,你要将这一叠牌移动至另一叠 $p_1'\sim p_n'$。

你的移动方式是：从上往下选择一部分牌（连续），将其按原顺序平移至第二叠牌的上方。

此时，我们令一叠牌的权值为 $\sum\limits_{i = 1}^{n}{n^{n - i} \cdot p_i} $。

最后你要使平移后的牌权值最高，求最后牌的摆放顺序，即按序输出 $p_1'\sim p_n'$。
# 题意分析
对于这类题，最关键的地方在于牌移动的顺序究竟该如何选择。所以我们要考虑两点，一个是它搬运的方式，另一个是它价值的计算。

1. 搬运方式：

我们可以看出，每次取牌时，断点处的牌会在这部分牌的最下方。

2. 统计方式：

我们可以发现，其答案可近似看作一个 $n$ 进制数，不过每一位的数为 $1\sim n$（正常的 $n$ 进制数应为 $0\sim n-1$）。所以，我们只要将答案减去 $11...1$，就可以将其转化为一个真正的 $n$ 进制数。我们又可以想到，两个 $n$ 进制数的大小比较方式为从高到低，只要有 $a_i$ 比 $b_i$ 大，则 $a>b$。所以，我们只需要让最大的数尽可能靠下就可以了。

因此我们从大往小（即从最上方往最下方）扫，遇到当前剩余牌的最大的，就将这一叠往后移，这样就可以保证大的牌尽可能在最下，以让最后的答案最大。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
int p[100001];
int s[100001];
bool b[100001];
int head;
inline void out()
{
	while(head)
	{
		cout<<s[head]<<" ";
		b[s[head--]]=1;
	}
	return ;
}
int main()
{
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		memset(b,0,sizeof(b));
		cin>>n;
		int now=n;
		for(int i=1;i<=n;i++)
		{
			cin>>p[i];
		}
		for(int i=n;i>=1;i--)
		{
			s[++head]=p[i];
			if(s[head]==now)
			{
				out();
			}
			while(b[now])
			{
				now--;
			}
		}
		out();
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：dalao_see_me (赞：0)

题目大意：有 $n$ 张牌，第 $i$ 张牌的点数为 $p_i$（$1\le p_i\le n$） 。每次从后往前取任意张牌，看做一个整体按照编号从小到大的顺序加入另一个地方。使得另一个地方的牌有最大字典序。求出这个最大字典序。

最大字典序，即为先看第一个，比完第一个，再看第二个，以此类推。我们可以先保证第一个是最大的，在“第一个是最大的”的前提下，保证第二个最大，以此类推。照这样模拟一下，就可以过了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+6;
int _,n,lst,mx;
int a[N],b[N];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	_=read();
	while(_--){
		n=read();queue<int>q;
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++)a[i]=read();
		lst=n;mx=n;
		for(int i=n;i;i--){
			if(a[i]==mx){
				for(int j=i;j<=lst;j++)q.push(a[j]),b[a[j]]=1;
				for(;mx;mx--)if(!b[mx])break;
				lst=i-1;
			}
		}
		for(int j=1;j<=lst;j++)q.push(a[j]),b[a[j]]=1;
		while(q.size()){
			printf("%d ",q.front());
			q.pop();
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Skies (赞：0)

## 题意
给你一个长为n的数组，你可以把后k个数作为整体放入栈中，问可得到的最大排列（可以理解为这 **n 个数所组成的 n 位数最大**）

## 思路

很明显可以发现，**越大的数放在前面，肯定越好**，所以每次，我们只要找到剩下的牌中最大的一张，然后把它及它之后的所有牌放入栈即可

这是一个**贪心**的思想。

至于为什么

我们来分析一下：

因为无论怎样排列，所得到的序列长度都相同。

所以只要高位大，低位无论如何排列，高位大的一定大！

然后开个 $vector$ 来存如何将序列分割

代码见下

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],b[1000010];
signed main() {
	int T,n;
	cin>>T;
	while(T--) {
		vector<int>ans;
		scanf("%d",&n);
		for(int i=1; i<=n; i++) {
			scanf("%d",&a[i]);
			b[i]=max(b[i-1],a[i]);
		}
		int id=b[n];
		ans.push_back(n+1);//末尾
		for(int i=n; i>=1; i--) {
			if(a[i]==id) {
				id=b[i-1];
				ans.push_back(i);//找到了，就压进去
			}

		}
		ans.push_back(1);//开始
		for(int i=0; i<ans.size()-1; i++) {
			int st=ans[i+1],en=ans[i];
			for(int j=st; j<en; j++) {
				printf("%d ",a[j]);
			}
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 张纸牌组成的一个牌堆，每张纸牌都有一个价值 $p_1,p_2,\dots,p_n$。每次选出最顶上的几个牌放到另外一个一开始为空的牌堆里面。定义一个牌堆的总值为 $\sum\limits_{i=1}^nn^{n-i} \cdot p_i$。请构造出一个可能的最终的牌堆，使得这个牌堆的总值最大。

**数据范围：$t$ 组数据，$t\in[1,10^3]$，$1\leqslant p_i\leqslant n\leqslant 10^5$。**
## Solution
我们不难想到，需要尽可能将 $p_i$ 大的牌放到前面去，因此我们想到这样一个贪心算法：将前 $1\sim n$ 个数的最大值所在位置记为 $maxi_i$（$maxi_i$ 可以通过边读入边记录，详见代码），然后从牌顶开始，每次将 $maxi_i$ 相等的牌按照原来的顺序放入新的牌堆，这样可以保证将 $p_i$ 大的牌放在前面而又符合要求。
## Code
```cpp
int n, p[100007], maxi[100007], ans[100007], cnt;

int main() {
 	MT {
		memset(ans, 0, sizeof(ans));
		memset(maxi, 0, sizeof(maxi));
		n = Rint, cnt = 0;
		F(i, 1, n) {
			p[i] = Rint;
			if(p[i] > p[maxi[i - 1]]) maxi[i] = i, ans[++cnt] = i;
			else maxi[i] = maxi[i - 1];
		}
		ans[++cnt] = n + 1;
		R(i, cnt, 1) F(j, ans[i], ans[i + 1] - 1) printf("%d ", p[j]);
		puts("");
	}
	return 0;
}
```

---

## 作者：cmll02 (赞：0)

注意式子。

显然把更大的数放在更下面更优。（多往下一个位置就会翻 $n$ 倍）

（简单理解：$n^kx+n^{k-1}(x-1)>n^k(x-1)+n^{k-1}x$）

那么直接贪心即可。

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
inline int read()
{
    int num=0;char c=getchar();
    while(c<48||c>57)c=getchar();
    while(c>47&&c<58)num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num;
}
inline int max(int a,int b)
{
    return a<b?a:b;
}
int a[100005],cnt,b[100005];
signed main()
{
    int T=read();
    while(T--)//、、
    {
        int n=read();
        cnt=n;
        for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]=i;
        int cur=n,qaq=0;
        while(cnt)
        {
            for(int i=b[cur];i<=cnt;i++)
            {
                printf("%d ",a[i]);
            }
            cnt=b[cur]-1;
            cur--;
            while(b[cur]>cnt)cur--;
        }
        puts("");
    }
}
```

---

