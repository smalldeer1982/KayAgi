# Identify the Operations

## 题目描述

We start with a permutation $ a_1, a_2, \ldots, a_n $ and with an empty array $ b $ . We apply the following operation $ k $ times.

On the $ i $ -th iteration, we select an index $ t_i $ ( $ 1 \le t_i \le n-i+1 $ ), remove $ a_{t_i} $ from the array, and append one of the numbers $ a_{t_i-1} $ or $ a_{t_i+1} $ (if $ t_i-1 $ or $ t_i+1 $ are within the array bounds) to the right end of the array $ b $ . Then we move elements $ a_{t_i+1}, \ldots, a_n $ to the left in order to fill in the empty space.

You are given the initial permutation $ a_1, a_2, \ldots, a_n $ and the resulting array $ b_1, b_2, \ldots, b_k $ . All elements of an array $ b $ are distinct. Calculate the number of possible sequences of indices $ t_1, t_2, \ldots, t_k $ modulo $ 998\,244\,353 $ .

## 说明/提示

$ \require{cancel} $

Let's denote as $ a_1 a_2 \ldots \cancel{a_i} \underline{a_{i+1}} \ldots a_n \rightarrow a_1 a_2 \ldots a_{i-1} a_{i+1} \ldots a_{n-1} $ an operation over an element with index $ i $ : removal of element $ a_i $ from array $ a $ and appending element $ a_{i+1} $ to array $ b $ .

In the first example test, the following two options can be used to produce the given array $ b $ :

- $ 1 2 \underline{3} \cancel{4} 5 \rightarrow 1 \underline{2} \cancel{3} 5 \rightarrow 1 \cancel{2} \underline{5} \rightarrow 1 2 $ ; $ (t_1, t_2, t_3) = (4, 3, 2) $ ;
- $ 1 2 \underline{3} \cancel{4} 5 \rightarrow \cancel{1} \underline{2} 3 5 \rightarrow 2 \cancel{3} \underline{5} \rightarrow 1 5 $ ; $ (t_1, t_2, t_3) = (4, 1, 2) $ .

In the second example test, it is impossible to achieve the given array no matter the operations used. That's because, on the first application, we removed the element next to $ 4 $ , namely number $ 3 $ , which means that it couldn't be added to array $ b $ on the second step.

In the third example test, there are four options to achieve the given array $ b $ :

- $ 1 4 \cancel{7} \underline{3} 6 2 5 \rightarrow 1 4 3 \cancel{6} \underline{2} 5 \rightarrow \cancel{1} \underline{4} 3 2 5 \rightarrow 4 3 \cancel{2} \underline{5} \rightarrow 4 3 5 $ ;
- $ 1 4 \cancel{7} \underline{3} 6 2 5 \rightarrow 1 4 3 \cancel{6} \underline{2} 5 \rightarrow 1 \underline{4} \cancel{3} 2 5 \rightarrow 1 4 \cancel{2} \underline{5} \rightarrow 1 4 5 $ ;
- $ 1 4 7 \underline{3} \cancel{6} 2 5 \rightarrow 1 4 7 \cancel{3} \underline{2} 5 \rightarrow \cancel{1} \underline{4} 7 2 5 \rightarrow 4 7 \cancel{2} \underline{5} \rightarrow 4 7 5 $ ;
- $ 1 4 7 \underline{3} \cancel{6} 2 5 \rightarrow 1 4 7 \cancel{3} \underline{2} 5 \rightarrow 1 \underline{4} \cancel{7} 2 5 \rightarrow 1 4 \cancel{2} \underline{5} \rightarrow 1 4 5 $ ;

## 样例 #1

### 输入

```
3
5 3
1 2 3 4 5
3 2 5
4 3
4 3 2 1
4 3 1
7 4
1 4 7 3 6 2 5
3 2 4 5```

### 输出

```
2
0
4```

# 题解

## 作者：tommymio (赞：7)

这种题肯定是结论题。

在拿到一个结论题的时候，如果没办法一眼看出结论，可以尝试推几个栗子，然后开始思考特殊的性质。

在很多样例中我们都发现，对于一个 $a_i$，如果我们当前要将它加进 $c$，可以选择删去 $a_{i-1}$ 或 $a_{i+1}$。设 $x$ 为 $a_{i-1},a_{i+1}$ 中无法被删去的数，则 $x$ 一定满足以下两个条件之一：

- 不存在 $x$。
- $x$ 在 $b$ 中出现的位置比 $a_i$ 在 $b$ 中出现的位置更晚。

所以我们就可以模拟这样的一个过程。如果 $a_{i-1}$ 与 $a_{i+1}$ 均可以被删去，根据乘法原理，答案要乘上 $2$。如果两个都不可被删去，则无解，输出 $0$。如果两个之一可被删去，答案不变。

```cpp
#include<cstdio>
typedef long long ll;
const ll mod=998244353;
int a[200005],b[200005],nxt[200005],pre[200005],isV[200005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void del(int x) {
    isV[a[x]]=0;
    pre[nxt[x]]=pre[x];
    nxt[pre[x]]=nxt[x];
}
int main() {
    int T=read();
    while(T--) {
        int n=read(),m=read(),ans=1;
        for(register int i=1;i<=n;++i) a[i]=read();
        for(register int i=1;i<=n;++i) pre[i]=nxt[i]=isV[i]=0;
        for(register int i=1;i<=n;++i) {pre[a[i]]=(i>1? a[i-1]:-1);nxt[a[i]]=(i<n? a[i+1]:-1);}
        for(register int i=1;i<=m;++i) {b[i]=read();isV[b[i]]=1;}
        for(register int i=1;i<=m;++i) {
            int f1=(pre[b[i]]!=-1&&!isV[pre[b[i]]]);
            int f2=(nxt[b[i]]!=-1&&!isV[nxt[b[i]]]);
            if(!f1&&!f2) {ans=0;break;}
            else if(f1&&f2) {ans=ans*2ll%mod;}
            isV[b[i]]=0;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：zztqwq (赞：4)

## Solution

拿到题没有思路，然后大力猜结论，本来以为 WA On Test 2，结果改一个取模就 AC 了，RP 真好（（

观察到如果想把某个数 $a_i$ 加入 $b$，则一定要在 $a_{i-1}$ 和 $a_{i+1}$ 中删掉一个。在纸上画画后我们发现一个规律：

> 令 $p_i$ 表示 $b_i$ 在 $\{a_i\}$ 中的下标，$t_i$ 表示 $ a_i$ 在 $\{b_i\}$ 中的下标（如果 $a_i\notin \{b_i\}$ 则令 $t_i=0$）。
> 枚举 $b_i$，令当前 $b_i$ 对答案的贡献 $c_i=0$，若 $p_i>1$ 且 $t_{p_i-1}<t_{p_i}$，$c_i$ 加一；类似地，若 $p_i<n$ 且 $t_{p_i+1}<t_{p_i}$，$c_i$ 加一。
> $\prod_{i=1}^m c_i$ 即为所求。

大白话版本：每个 $a_i$ 都找到自己在 $\{b_i\}$ 中是第几个被“提到”的（就是 $t_i$），如果左边的数没被提及过或者说左边的数比他提及的早，$c_i\gets c_i+1$（即 `c[i]++`）；右边做同样的操作，最后把 $c_i$ 乘起来就是答案。如果还无法理解可以直接翻下面的代码。

接下来证明一下为什么这样做是对的。

仔细思考一下，对于这个做法我们的迷惑点实际上是这样的：如果旁边的数已经前面的数删了，并且比当前这个数晚提及，那么答案就是错的。但实际上，这个命题是不存在的。以右边为例，如果发生这种情况，删除过程中一定会有一个情形：

> 若 $ a_i$ 为当前正在计算的数，则此时 $t_{i}>t_{i+1}<t_{i+2}$。

对于这种情况，根据前面的算法，$c_{i+1}=0$。因为计算总贡献时是 $\prod$ 而不是 $\sum$，所以如果出现这种情况答案肯定是 $0$，就算 $c_i$ 计算错了也无伤大雅；如果最后的答案不是 $0$，就肯定不会出现这种情况。

$$\mathcal{Q.E.D.}$$

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int N=2e5;
int a[N+10],b[N+10],tg[N+10],pos[N+10];
int main()
{ 
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(tg,-1,sizeof(tg));
		int n,m;
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++) 
		{
			scanf("%d",&a[i]);
			pos[a[i]]=i;
		} 
		for(int i=1;i<=m;i++) 
		{
			scanf("%d",&b[i]);
			tg[pos[b[i]]]=i;
		}
		int ans=1;
		for(int i=1;i<=m;i++) 
		{  
			int cnt=0;
			if(pos[b[i]]>1 && tg[pos[b[i]]-1]<tg[pos[b[i]]]) cnt++;
			if(pos[b[i]]<n && tg[pos[b[i]]+1]<tg[pos[b[i]]]) cnt++;
			ans*=cnt;
			ans%=998244353;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：AsunderSquall (赞：4)

update：远古题解一大堆格式错误，试图一个个修复。 


**题意**
给你两个数组 $ \{a_i\},\{b_i\} $，长度分别为 $ n,m $ 。  
满足  
-  $ \{a_i\} $ 是大小为 $ n $ 的置换（其实就是一个 $ 1 $ ~ $ n $ 的排列）。  
-  $ \forall x \in \{b_i\} ,x\in \{a_i \} $ 。  
-  $ \{b_i\} $ 中所有元素不重复。

你需要进行 $ m $ 次操作，每次你要从 $ a $ 中选一个下标 $ t $，然后选择 $ a $ 中下标为 $ t+1 $ 或者 $ t-1 $ 的数放在 $ c $ 数组的末尾（如果 $ a $ 数组存在下标 $ t-1 $ 或 $ t+1 $ ），然后将 $ a_t $ 删去，下标 $ t $ 后面的数往前移 $ 1 $ 位。  
最后问你有多少种方案可以使 $ c=b $。   



**题解**

刚开始还以为是什么神仙题，毕竟放在 div2 F 看着很吓人，但是我发现做出 E 的人明显比做出 F 的人少，而且做出F的人大部分都一遍过，因此开始猜结论。  
然后发现是大水题。  
这个结论很难说清楚，还是看题解吧。  

我们先把 $ b_i $ 从值替换成  $ b_i $ 在 $ a_i $ 中的位置。  
看上去下标 $ t $ 后面的数往前移 $ 1 $ 位这个操作比较麻烦，我们需要一种简单的数据结构来维护。需要支持：  
- 删除 $ 1 $ 个数操作。  
- 快速查找原下标所在的地方。  
- 快速查找前驱和后继。  

那么我们使用数组模拟双向链表：  

```cpp
struct TwoList//名字取得比较奇怪，不要介意
{
    int pre,nxt;
}L[N];
void Delete(int x)
{
    if (L[x].pre) L[L[x].pre].nxt=L[x].nxt;
    if (L[x].nxt) L[L[x].nxt].pre=L[x].pre;
}
```
先我们显然要把 $ a $ 中的数按照 $ b $ 的顺序一个一个加入 $ c $。   
`for (int i=1;i<=m;i++)`  
假如我们只考虑需要把 $ b_i $ 加入 $ c $ 数组。  
找到 $ a_{b_i} $ 的位置，由于我们是用数组模拟双向链表，直接访问下标即可。  
然后我们选择 $ a_{b_i} $ 的前驱或者后继，删除一个，再将 $ a_{b_i} $ 加入 $ c $ 中。  

显然有些数是不能删的，我们将它们打上 tag，然后删除的时候不能删除带有 tag 的数。  
为了方便，我们将 $ 0 $ 和 $ n+1 $ 打上 tag，这样就不用特判了。  
当 $ a_{b_i} $ 已经加入 $ c $ 中的时候，我们在之后的操作中可以把它删掉了，那么就把 tag 去掉。  
当查找到一个数时：   
- 前驱和后继都带 tag 时，答案就是 $ 0 $。   
- 前驱和后继中有一个 tag 时，答案数不变，删掉不带 tag 的数，然后将自身 tag 清除。    
- 前驱和后继都不带 tag 时，这个我们在下面进行重点分析。  

其实也没什么好分析的，将答案 $ \times 2 $，再删去任意一个数即可。  
为什么这样做是对的？  
 $ a_{b_i-1},a_{b_i},a_{b_i+1} $ 这 $ 3 $ 个数在操作之后都一样了，因为在此次操作后这 $ 3 $ 个数都不带 tag 了，而且他们下标连续，对其他位置的前驱/后继是否有 tag 的判断没有影响（也就是说删除 $ a_{b_i} $ 本身都对正确性没有影响）  

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5;
const int M=5005;
struct TwoList
{
    int pre,nxt;
}L[N];
void Delete(int x)
{
    if (L[x].pre) L[L[x].pre].nxt=L[x].nxt;
    if (L[x].nxt) L[L[x].nxt].pre=L[x].pre;
}
 
int a[N],b[N],tag[N],pos[N];
int n,m;
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		int ans=1;
		cin>>n>>m;
		for (int i;i<=n;i++) tag[i]=0;
		for (int i=1;i<=n;i++) cin>>a[i],pos[a[i]]=i;
		for (int i=1;i<=m;i++) cin>>b[i],b[i]=pos[b[i]],tag[b[i]]=1;
		for (int i=1;i<=n;i++)
    	{
    	    L[i].pre=i-1;
    	    L[i].nxt=i+1;
    	}
        L[n].nxt=0;
    	tag[0]=1;
		for (int i=1;i<=m;i++)
		{
			if (tag[L[b[i]].pre])
			{
				if (tag[L[b[i]].nxt]) {ans=0;}
				else Delete(L[b[i]].nxt);
			}
			else
			{
				if (tag[L[b[i]].nxt]) Delete(L[b[i]].pre);
				else 
				{
					ans=ans*2%998244353;
					Delete(L[b[i]].nxt);
				}
			}
			tag[b[i]]=0;
		}
		cout<<ans<<endl;
	}
	
}
```


---

## 作者：Theophania (赞：2)

对于一次操作，假设要加入数组 $b$ 的数是 $a_i$，那么需要删除 $a_{i-1}$ 或 $a_{i + 1}$，分类讨论以下三种情况：

1. $a_{i-1}$ 和 $a_{i + 1}$ 都存在于 $b$ 数组的 $a_i$ 之后，那么一个都不能删去，是无解的情况，最终的答案就是 $0$
2. $a_{i-1}$ 和 $a_{i + 1}$ 有一个存在于 $b$ 数组的 $a_i$ 之后，那么只能删去另一个，并且今后 $a_i$ 也可以被删除
3. $a_{i-1}$ 和 $a_{i + 1}$ 都不存在于 $b$ 数组的 $a_i$ 之后，那么有两种删除方式，并且今后 $a_i$ 也可以被删除

如果删除的是 $a_{i-1}$，说明 $a_{i-1}$ 是可删除的，而 $a_i$ 在此之后也变得可删除了，对于两端的影响和删除自身是一样的。如果删除 $a_{i+1}$ 也是一样的道理。

也就是说，对于可以删除的情况，只要更新一下答案，然后把自己删除就行了。这个过程可以用链表来模拟。

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

template <typename T>
inline void read(T &x)
{
    T data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    x = f * data;
}
template <typename T, typename... Args>
inline void read(T &t, Args &... args)
{
    read(t);
    read(args...);
}

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int maxn = 2e5 + 9;
const ll mod = 998244353;
int a[maxn], b[maxn], mp[maxn];
struct node
{
    int val, l, r;
};
node s[maxn];
void del(int pos)
{
    mp[s[pos].val] = 0;
    s[s[pos].r].l = s[pos].l;
    s[s[pos].l].r = s[pos].r;
}
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        int n, k;
        read(n, k);
        memset(mp, 0, sizeof(int) * (n + 2));
        memset(s, 0, sizeof(node) * (n + 2));
        a[n + 1] = n + 1;
        s[0].r = 1, s[n + 1].l = n;
        mp[0] = mp[n + 1] = n + 1;
        for (int i = 1; i <= n; ++i)
        {
            read(s[i].val);
            a[s[i].val] = i;
            s[i].l = i - 1;
            s[i].r = i + 1;
        }
        for (int i = 1; i <= k; ++i)
        {
            read(b[i]);
            mp[b[i]] = i;
        }
        ll ans = 1;
        bool flag = true;
        for (int i = 1; i <= k; ++i)
        {
            int now = b[i], pos = a[now];
            if (mp[s[s[pos].l].val] && mp[s[s[pos].r].val])
            {
                flag = false;
                break;
            }
            else if (mp[s[s[pos].l].val] || mp[s[s[pos].r].val])
                del(pos);        
            else
            {
                del(pos);
                ans = ans * 2 % mod;
            }
        }
        if (!flag)
            printf("0\n");
        else
            printf("%lld\n", ans);
    }
    return 0;
}
```



---

## 作者：_Sein (赞：1)

### 题意
>给你一个排列 $a$ ，你可以执行以下操作:
>
>选定一个位置 $t$ ，删除 $a_t$ ，然后选择 $a_{t-1}$ 或 $a_{t+1}$ 推进 $b$ 中。
>
>问有多少种操作方案可以由 $a$ 到 $b$ 。

### solution

判断一下对于一个关键点 $b_i$，它左边右边能不能选。

注意按照顺序选择，因为一旦关键点拿走了，这个关键点也是能贡献给相邻的关键点的。

```cpp
int a[N], p[N], b[N], l[N], r[N];
bool vis[N];
 
void solve() {
    int n, k; qr(n), qr(k);
   	rep (i, 1, n) qr(a[i]);
   	rep (i, 1, n)
   		l[a[i]] = i > 1 ? a[i - 1] : -1,
   		r[a[i]] = i < n ? a[i + 1] : -1;
   	rep (i, 1, k) {
		qr(b[i]); vis[b[i]] = 1;  
	}
	ll ans = 1;
	rep (i, 1, k) {
		bool fl = l[b[i]] != -1 && !vis[l[b[i]]];
		bool fr = r[b[i]] != -1 && !vis[r[b[i]]];
		if (fl && fr) ans = ans * 2 % mod;
		if (!fl && !fr) ans = 0; 
		vis[b[i]] = 0;
	} pr2(ans);
}
```



---

## 作者：RiceFruit (赞：0)

[点我返回题目](https://www.luogu.com.cn/problem/CF1442B)

[更好的阅读体验？](https://yaoyanfeng.blog.luogu.org/solution-cf1442b)
## 思路

当一个数在 $a$ 序列中的 $x$ 在 $b$ 序列中，设 $y$ 在它 $a$ 序列中 $x$ 的左边，$z$ 在 $a$ 序列中 $x$ 的右边。若要删 $y$ 记录 $x$ 则必须 $y$ 不在 $b$ 序列中，或者 $y$ 在 $b$ 序列中的位置比 $x$ 在 $b$ 序列前面才可以（显然），$z$ 同理。

接下来我们考虑证明删掉一个数，对于后面的数没有影响。

假设这个数是 $x$，它左边是 $x_1$，$x_1$ 左边是 $x_2$，$x_2$ 左边是 $x_3,\cdots,x_{p-1}$ 左边是 $x_p$，其中 $x,x_1,\cdots,x_p$ 都是 $b$ 序列中的数。

那么命题等价于证明在删除 $x$ 前删除 $x_1$ 没有影响。

证：首先删除 $x_1$ 一定是为了标记 $x$，而为了标记 $x_1$ 只能删除 $x2$，$\cdots$ 为了标记 $x_{p-1}$ 只能删除 $x_p$，那么 $x_p$ 肯定是由 $x_p$ 前面的数删除而标记。且 $x_p$ 前面一定会有数。

故我们的策略是：对于一个在 $b$ 序列中的数 $a_i$，则我们记一个 $s\gets 0$，当 $a_{i-1}$ 不在 $b$ 序列中或者 $a_{i-1}$ 在 $b$ 序列中的位置比 $a_i$ 在 $b$ 序列中的位置小时，$s\gets s+1$；当 $a_{i+1}$ 不在 $b$ 序列中或者 $a_{i+1}$ 在 $b$ 序列中的位置比 $a_i$ 在 $b$ 序列中的位置小时，$s\gets s+1$，然后让 $ans= ans\times s$ 即可。

于是我们就解决了本题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define ri register int
#define int long long
#define ull unsigned long long
#define lid (id<<1)
#define rid (id<<1|1)
void swap(int &x,int &y){int t=x;x=y;y=t;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
const int N=2e5+20,mod=998244353;
inline int read();
inline void write(int ans);
inline void put(int x,char c);
int T;
int n,k;
int a[N];
int b[N];
int rnk[N];
int ans;
signed main(){
	T=read();
	while(T--){
		n=read(),k=read();
		memset(rnk,0,sizeof rnk);
		ans=1;
		for(int i=1;i<=n;i++)
			a[i]=read();
		for(int i=1;i<=k;i++)
		{
			b[i]=read();
			rnk[b[i]]=i;
		}
		for(int i=1;i<=n;i++){
			if(!rnk[a[i]])
				continue;
			int xs=0;
			if(i>1&&rnk[a[i-1]]<rnk[a[i]])xs++;
			if(i<n&&rnk[a[i+1]]<rnk[a[i]])xs++;
			ans=ans*xs%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x % 10+'0');return;}
inline void put(int x,char c){write(x);putchar(c);return;}
```

---

## 作者：Milmon (赞：0)

[Milmon Page 链接：https://molmin.github.io/problem?id=40#solution](https://molmin.github.io/problem?id=40#solution)

首先记录出对于任意一个 $i$ 满足 $1\leq i\leq n$ 在 $a$ 数列中的位置，记为 $id_i$；以及其在 $b$ 数列中的位置，记为 $t_i$（若不在 $b$ 数列中出现，则记为 $t_i=-1$）。

分步处理 $b$ 数列中的每条记录。对于 $b_i$：

考虑第一种情况：该记录由删除 $a$ 数列中 $b_i$ 的前一个数而形成。首先它前面必须存在数，那么必须满足 $id_{b_i} > 1$；还需证明当该条件成立时，它前面必然存在数，在一开始的时候，它前面必然有数，而当它前面只剩一个数时，若要让前面的数被删除，那么必须记录 $b_i$ 这个数，矛盾。

其次，这样操作后会导致前一个数被删除。故若前一个数在 $b$ 数列中，那么必须位于 $b_i$ 的前面。

第二种情况：该记录由删除 $a$ 数列中 $b_i$ 的后一个数而形成。与情况一相似，此处不再赘述。

[Code 链接：https://molmin.github.io/problem?id=40#code](https://molmin.github.io/problem?id=40#code)

---

## 作者：Zn2Fe_PO4_2_4H2O (赞：0)

### 题目大意
给出一个长度为 $n$ 的序列 $A$ 和一个长度为 $m$ 的序列 $B$ ， $A$ 为 $1$ 到 $n$ 的一个排列， $B$ 中元素两两不同，你要进行 $m$ 次操作，每次在 $A$ 中选中一个数加入序列 $C$ 的末尾（序列 $C$ 初始为空），并在 $A$ 中将选中的数的相邻两数之一删除（若选中数在边界则只能删相邻的那一个），求令 $C=B$ 的操作方案数。

### 思路
考虑按照 $B$ 的顺序模拟过程，可以发现一个数不可以被删去当且仅当这个数在 $B$ 序列中排在当前选中的数的后面，于是我们模拟过程中可以这样统计答案：

1. 当前选中的数两边都可以删除

	$ans\leftarrow ans*2$

2. 当前选中的数在边界且旁边的数可以删除或当前选中的数只有一边可以删除

	$ans$ 不变
    
3. 当前选中的数在边界且旁边的数不可删或当前选中的数两边都不可删

	当前情况无解，直接输出 $0$

模拟以上过程即可 $AC$

### 代码

``````cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=2e5+5;
const int mod=998244353;
int n,m;
int a[NR],b[NR],pre[NR],nxt[NR];
bool vis[NR];
long long ans;
void solve(){
	cin >> n >> m;
	ans=1;
	for(int i=1;i<=n;i++) pre[i]=nxt[i]=0;
	for(int i=1;i<=n;i++) vis[i]=0;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=m;i++) cin >> b[i],vis[b[i]]=1;
	for(int i=1;i<=n;i++) pre[a[i]]=(i>1?a[i-1]:-1),nxt[a[i]]=(i<n?a[i+1]:-1);
	for(int i=1;i<=m;i++){
		bool x=(pre[b[i]]!=-1&&!vis[pre[b[i]]]);
		bool y=(nxt[b[i]]!=-1&&!vis[nxt[b[i]]]);
		if(!x&&!y){
			ans=0;break;
		}
		if(x&&y){
			ans*=2;ans%=mod;
		}
		vis[b[i]]=0;
	}
	cout << ans << endl;
} 
int main(){
	int t;cin >> t;
	while(t--) solve();
	return 0;
}
``````

---

## 作者：vеctorwyx (赞：0)

### 题目大意

有两个序列$a,b$，$b$一开始是空的；

每次操作可以从$a$中选择一个数$a_i$删去，然后把它左右两个数$a_{i-1},a_{i+1}$**之一**添加$b$最后，然后把$a_{i+1}......a_n$左移，把$a_i$的位置补上。

现在给你$a$序列和结果序列$b$，求进行$k$次操作后能得到$b$序列的方案数。

答案对``998244353``取模。

### sol

~~呜呜呜这题可算调出来了~~

考虑每一个$a$中的元素，此元素能被添加到$b$中的条件有：

- 它不能在被添加之前删除；

- 它左边或右边的元素被删掉了（前提是有左右元素）。

然后倒过来考虑：

对于每一个$b$中的一个元素在$a$中为$a_i$，

1. 如果$a_{i-1}$被删除了，使$a_i$加入$b$，那么$a_i$不能是最左边的元素，且$a_{i-1}$不能在这之后被加进$b$中（因为$a_{i-1}$~~已经没了~~）；

2. 同理，如果$a_{i+1}$被删除了，使$a_i$加入$b$，那么$a_i$不能是最右边的元素，且$a_{i+1}$不能在这之后被加进$b$中；

然后根据以上两种情况判断并统计答案就好了。

code：

```
#include<bits/stdc++.h>
#define int long long//十年oi一场空，不开longlong见祖宗
using namespace std;
int read(){
    int x=0,y=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')y=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*y;
}
int t,n,m;
int a[200010],pl[200010],b[200010];
set<int>q;//开个set，节省空间又能快速查找
signed main(){
	t=read();
	while(t--){
		n=read(),m=read();
		for(int i=1;i<=n;i++)
			a[i]=read(),pl[a[i]]=i;//pl记录的是当前值在a中的位置
		for(int j=1;j<=m;j++){
			b[j]=read();
			q.insert(b[j]);
		}
		int ans=1;
		for(int i=1;i<=m;i++){
			q.erase(b[i]);
			int ji=0;
			if(pl[b[i]]>1&&q.count(a[pl[b[i]]-1])<=0)//左边元素被删除
			ji++;
			if(pl[b[i]]<n&&q.count(a[pl[b[i]]+1])<=0)//右边元素被删除
			ji++;
			(ans*=ji)%=998244353;//统计答案
		}
		cout<<ans<<"\n";
	}
} 
```

---

