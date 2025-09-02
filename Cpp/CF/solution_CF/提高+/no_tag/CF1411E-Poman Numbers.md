# Poman Numbers

## 题目描述

You've got a string $ S $ consisting of $ n $ lowercase English letters from your friend. It turned out that this is a number written in poman numerals. The poman numeral system is long forgotten. All that's left is the algorithm to transform number from poman numerals to the numeral system familiar to us. Characters of $ S $ are numbered from $ 1 $ to $ n $ from left to right. Let's denote the value of $ S $ as $ f(S) $ , it is defined as follows:

- If $ |S| > 1 $ , an arbitrary integer $ m $ ( $ 1 \le m < |S| $ ) is chosen, and it is defined that $ f(S) = -f(S[1, m]) + f(S[m + 1, |S|]) $ , where $ S[l, r] $ denotes the substring of $ S $ from the $ l $ -th to the $ r $ -th position, inclusively.
- Otherwise $ S = c $ , where $ c $ is some English letter. Then $ f(S) = 2^{pos(c)} $ , where $ pos(c) $ is the position of letter $ c $ in the alphabet ( $ pos( $ a $ ) = 0 $ , $ pos( $ z $ ) = 25 $ ).

Note that $ m $ is chosen independently on each step.

Your friend thinks it is possible to get $ f(S) = T $ by choosing the right $ m $ on every step. Is he right?

## 说明/提示

In the second example, you cannot get $ -7 $ . But you can get $ 1 $ , for example, as follows:

1. First choose $ m = 1 $ , then $ f( $ abc $ ) = -f( $ a $ ) + f( $ bc $ ) $
2. $ f( $ a $ ) = 2^0 = 1 $
3. $ f( $ bc $ ) = -f( $ b $ ) + f( $ c $ ) = -2^1 + 2^2 = 2 $
4. In the end $ f( $ abc $ ) = -1 + 2 = 1 $

## 样例 #1

### 输入

```
2 -1
ba```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 -7
abc```

### 输出

```
No```

## 样例 #3

### 输入

```
7 -475391
qohshra```

### 输出

```
Yes```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：6)

由于递归形式，字符串 $S$ 的每一字符 $x$ 的贡献肯定是 $2^x$ 或 $-2^x$ 之一。

考虑贡献序列的正负：什么样的贡献序列可以构成？

 - 对于 $n=2$，能构成 $-+$；
 - 对于 $n=3$，能构成 $--+$ 和 $+-+$；
 - 对于 $n=4$，能构成 $---+$，$+--+$，$-+-+$，$++-+$；
 - . . .

字符串的第 $n$ 位贡献肯定是 $+$，因为到达 $n$ 的每一次递归都为往右走。类似，第 $n-1$ 位贡献肯定是 $-$，因为到达 $n-1$ 需要恰好往左递归一次。

于是猜想所有第 $n$ 位是 $+$，第 $n-1$ 位是 $-$ 的贡献序列均可构造。接下来给一个具体构造：

$\operatorname{build}(S) =$
 - 如果 $S[1]=``-"$，选择 $m=1$。
 - 否则，如果 $S=``+"$，则 $S$ 为单个节点，停止。
 - 否则，$S$ 至少有两个 $+$。设次后一个 $+$ 的位置为 $x$；由于 $S[n-1]=``-"$，有 $S[x+1]=``-"$。$S[1:x+1]$ 的最后两位是 $``+-"$，取负并选择 $m=x+1$。

于是，删掉最后两位，问题变为如何将位置给予正负号，使得整体的和为 $T-2^{S[n]}+2^{S[n-1]}$。将剩余字符从大到小排序，贪心取：如果 $T>0$ 需要往上，否则往下。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

ll va[256];

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; ll t; cin >> n >> t;
    string s; cin >> s;
    int c = 1;
    iter(i, 'a', 'z'+1) {
        va[i] = c;
        c = 2 * c;
    }
    t = t - (va[s[n-1]] - va[s[n-2]]);
    s.pop_back(); s.pop_back();
    sort(all(s));
    reverse(all(s));
    for(char c:s){
        if(t<0)t+=va[c];
        else t-=va[c];
    }
    if(t==0)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}
```

---

## 作者：AsunderSquall (赞：1)


# 题意  
有一个小写字符串 $S$，长度为$n$。   
定义对一个小写字符的函数 $pos(x)=x-\text a$  
如 pos('a')=0,pos('z')=25。  

定义作用于字符串的函数  
$$f(S)=\begin{cases}2^{pos(S[1])}, & |S|=1,\\-f(S[1,m])+f(S[m+1,|S|]), & \text{otherwise}\end{cases}$$  
                             
其中 $m$ 是自己在每一步运算中定义的任意整数，满足 $m \in [1,|S|-1]$  

给你长度为 $n$ 的字符串 $S$ ，问你能不能通过构造每一步中合适的 $m$ ，最终使 $f(1,n)=T$。  
# 一些闲话  
这道题结论很简单，但是容易猜错，导致我
> 成为了**罚时巨怪**，以后还要继续努力！  

![](https://cdn.luogu.com.cn/upload/image_hosting/evbcyvhp.png)  
虽说如此，还是上紫了，可喜可贺。

# 题解  

首先，看这个函数分段的时候有正有负的非常麻烦，我们考虑每一位是正的还是负的。  
也就是说，我们要求什么样的正负序列是合理的。  

我们不妨称位置 $p$ 和 $p+1$ 之间的间隔为间隔 $p$。  
对于一个位置 $p$，当它确定正负号的时候，是间隔 $p$ 被选中时候。  
显然 $p=n$ 的时候确定了它是正的，因为不存在间隔 $n$。  
其次，$p=n-1$ 的时候确定了它是负的，因为只有一个间隔 $n-1$ 可以使它正负号发生改变。  
那么其他情况呢？  
事实上，其他的位置取任意正负号都是合法的。  

我们考虑位置 $p$ ，会使它正负号发生改变的间隔有 $(n-p)$ 个。并且，选中隔 $p$ 的时候对 $\forall x \in [p+1,n]$ 没有影响。  
所以我们只要在合适的时间选中间隔 $p$ 即可。  
我们发现间隔 $p$ 对前面的数字是有影响的，这没有关系，因为更前面的位置是根据后面的间隔插入来确定插入时间的，总能找到合适的时间插入。  
更具体地，如果要求 $p$ 是负的，那么把间隔 $p$ 放在开头，否则放在第二个位置。

这里放一份用单向链表实现的构造方式，可以参考一下  
```cpp
#include<bits/stdc++.h>
#define rd(x) x=read()
using namespace std;
const int N=2e5+5;
int n,head;
int nxt[N];
string s;
signed main()
{
    cin>>s;n=s.length();
    s=" "+s;//这是不提倡的把字符串变为从 1 开始下标的方法，但是我喜欢用
    if (s[n]=='-' || s[n-1]=='+') puts("impossible");else
    {
        head=n-1;
        for (int i=n-2;i>=1;i--)
        {
            if (s[i]=='-') {nxt[i]=head;head=i;}
            if (s[i]=='+') {nxt[i]=nxt[head];nxt[head]=i;}
            for (int x=head;x;x=nxt[x]) printf("%lld ",x);puts("");//这一句是用来显示构造过程的
        }
        for (int x=head;x;x=nxt[x]) printf("%lld ",x);puts("");
    }
}
```

那么问题就变为，有一个序列 $\{a\}$，序列里中的数都是 $2$ 的幂次，给每个数赋正负号，而是他们的和等于一个特定的数 $T$。  
首先 $a_n$ 必须为正，$a_{n-1}$ 必须为负，所以 $T\gets T-a_n+a_{n-1}$ 方便我们后面的计算。  

那么我们把剩下的数相同的计为一类统计个数。（这一步对应将 $S_{1,2,\cdots n-2}$ 统计每种字符的数量）。  
然后我们考虑怎么判断是否能表示出 $T$。  
显然 $T$ 的正负号不影响。  
然后我们从最高位往低位考虑。  
有一个简单的小结论，就是每考虑一位，都要使剩下的 $T$ 的绝对值尽量小。  
原因有点难解释，可以先看看代码。  
```cpp
for (int i=25;i>=0;i--)
{
	int p=(1LL<<i);
	T=ABS(T);
	if (T>=cnt[i]*p) T-=cnt[i]*p;//如果把所有的加起来都不够，那么就全部选上 
	else 
	{
		int t=T/p;//否则先尽可能多选，保持 T 为正 
		if ((cnt[i]-t)%2==0) T-=t*p;//如果剩下的数为偶数，那么可以一正一反抵消 
		else T-=(t+1)*p;//否则如果再加一个 p，|T|>=p，减去则有 |T|<=p，所以减去更优。 
	}
}
```
最后如果 $T$ 变成 $0$ 了，说明可以表示出来。  
然后我们来解释一下上面的小结论。  
理性证明好像比较难（有没有会的大佬教教我呀），我们来感性理解一下。  
首先假设我们已经使 $T$ 的绝对值最小了，显然此时 $|T|\le p$。  
假设我们减去的数中有一个变成了加，那么 $T \gets T+2p$。  
然后考虑到抵消这个 $2p$ 的影响也需要偶数个数，因此不加 $2p$ 更优。

完整代码  
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=2e6+5;
const int M=5005;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x);x=(x*x);y>>=1;}return ret;}

int T,n,y;
int a[N];
string s;
int cnt[N];
int ABS(int x){if (x<0) return -x;else return x;}
signed main()
{
	rd(n);rd(T);
	cin>>s;s=" "+s;
	for (int i=n-1;i<=n;i++) a[i]=ksm(2,s[i]-'a');
	T-=a[n];T+=a[n-1];
	for (int i=1;i<n-1;i++) cnt[s[i]-'a']++;
	for (int i=25;i>=0;i--)
	{
		int p=(1LL<<i);
		T=ABS(T);
		if (T>=cnt[i]*p) T-=cnt[i]*p;//如果把所有的加起来都不够，那么就全部选上 
		else 
		{
			int t=T/p;//否则先尽可能多选，保持 T 为正 
			if ((cnt[i]-t)%2==0) T-=t*p;//如果剩下的数为偶数，那么可以一正一反抵消 
			else T-=(t+1)*p;//否则如果再加一个 p，|T|>=p，减去则有 |T|<=p，所以减去更优。 
		}
	}
	if (T==0) puts("Yes");
	else puts("No");
}
```

---

## 作者：Priestess_SLG (赞：0)

十分神秘的题。考虑到对于给定的字符串 $s$ 完全可以将其映射到一个新的序列 $a$，满足 $a_i=2^{\text{pos}(s_i)}$。然后就是找寻一组 $o$ 满足 $\sum\limits_{i=1}^no_ia_i=T$ 且 $o$ 满足题目中给出的构造。因此此时只需要考虑哪些构造是合法的。

仔细观察 $f$ 函数可以发现：其实对于 $f_{[l,r]}$，可以在 $[l,r)$ 区间中选择一个整数 $m$，然后将区间 $[l,m]$ 中所有的 $o_i$ 符号取反（初始时 $\forall i,o_i=1$）。因此容易观察到对于序列的最后一个元素 $o_n$，显然不论区间 $[l,r]$ 怎样选择（需要保证 $1\le l<r\le n$），都无法选取 $m$ 使得 $m=n$。因此必有 $o_n=1$。

然而显然不只这一个特殊的限制条件。容易观察到，$n-1$ 位置想要被取到，当且仅当 $r=n$ 的时候选取 $m=n-1$。之后有 $r=n-1$，$m=n-1$ 将再也不会被选择。因此 $m=n-1$ 的情况必恰好被取反一次，必有 $o_{n-1}=-1$。

此时可以发现对于 $[1,n-2]$ 中的任何数 $i$，$o_i$ 都可以任取 $\lbrace 1,-1\rbrace$。然后考虑反悔贪心一开始 $[1,n-2]$ 全部选择 $1$，每一次选择最大的可以选的数贪心的将其的 $o_i$ 变为 $-1$ 即可。时间复杂度为 $O(n\log n)$ 可以通过。

---

## 作者：jasonliujiahua (赞：0)

# [CF1411E](https://www.luogu.com.cn/problem/CF1411E)

## Solution

### Step 1：

首先手摸样例可以发现 $m$ 是诈骗的，$f(1,n)$ 有 $2^{n-2}$ 种取值，是 $2^{a_n}-2^{a_{n-1}}+\sum_{i=1}^{n-2}\pm 2^{a_i}$（证明的话用归纳法应该非常好证，请读者自证）。因此设 $T'=T-(2^{a_n}-2^{a_{n-1}})$，问题变成了用若干 $2$ 的次幂加减凑成 $T'$ 的方案数。

### Step 2：

接下来进行问题的再转化使问题变得可以轻松解决，这好像是大部分题解未提到的。我们考虑先都取 $+$ 号，令 $T''=\left(\sum_{i=1}^{n-2}2^{a_i}\right)-T'$，问题又变成了：有 $n-2$ 个数 $2\times 2^{a_1},2\times 2^{a_2} \cdots 2\times 2^{a_{n-2}}$，可以**选或不选**能否凑出 $T''$。这就是经典的贪心了。对于一个大数，显然能放进去就放，这样剩下的小数更加灵活，更利于凑出答案。因此这道题就解决了，时间复杂度为排序的 $O(n\log n)$。


## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+10;
int n,t,a[maxn];
void init() 
{
	cin>>n>>t;
	for(int i=1;i<=n;i++) 
	{
		char c;
		cin>>c;
		a[i]=c-'a';
	}
}
void work()
{
	t-=((1ll<<a[n])-(1ll<<a[n-1]));
	int tmp=0;
	for(int i=1;i<=n-2;i++) 
	{
		tmp+=(1ll<<a[i]);
		a[i]++;
	}
	t=tmp-t;
	if(t<0)
	{
		printf("No\n");
		return; 
	}
	sort(a+1,a+n-1); 
	for(int i=n-2;i;i--)
		if((1ll<<a[i])<=t)
			t-=(1ll<<a[i]);
	if(t==0) printf("Yes\n");
	else printf("No\n");
} 
signed main()
{
	init();
	work();
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：0)

## CF1411E 【Poman Numbers】

### 题意

+ 有长度为 $n$ 的数列 $a$；
+ 函数 $f(l,r)$ 的计算方法：
+ 1. 若 $l==r$，$f(l,r)=2^{a_i}$；
  1. 否则，任选一个 $m$ 使 $l\le m<r$，$f(l,r)=-f(l,m)+f(m+1,r)$；
+ 给定 $x$，判断 $f(1,n)$ 是否可能为 $x$；
+ $2\le n\le10^5,0\le a_i\le25,\mid x\mid\le10^{15}$。

### 做法

对每个 $2^{a_i}$ 对答案的贡献记为“+” 或“-”，按顺序整理出一个符号序列 $s$，显然有最后两个符号一定为“-+”（长度为 $1$ 除外）。

接下来证明必要性，即如果 $s$ 后两个符号为“-+”，前面的符号无论怎么选，都存在合法方案。

先解决一些特殊情况，比如说目标序列 $s$ 只有在最后有一个“+”，那就每次选 $m=l$。

否则，$s$ 至少有两个“+”，显然不能还像上面那样每次选 $m=l$。

前面说了合法方案的序列最后两个符号一定为“-+”，也就是对于选的 $m$，一定有 $s[m-1]=$“+”，$s[m]=$“-”（要反过来）。发现 $s[r-1]=$“-”，也就是说倒数第二个“+”的前面一定是“-”，这样就可以分出两个更小的子问题，从而递归地证明。

现在问题转化成有一堆数，最后两位符号确定，前面符号任选，判断是否可以计算出数 $x$。没法 DP，更不能暴力。

先修改 $x$ 去除最后两位的影响。发现所有数都是 $2$ 的整数次方，那就贪心地从大到小排序，对于每个 $a_i$，当 $x<0$ 时选“+”，否则选“-”，然后修改 $x$。

当 $x<0$ 时如果选“-”，且最终 $x=0$，那修改的过程中一定会出现一个位置使 $x'$ 正好等于当前的 $x$。此时如果把前面的操作取反，最终结果不变且在一开始选了“+”。而如果此时本来就选“+”，修改的过程中不一定有 $x'$ 正好等于原来的 $x$。综上，此时选“-”一定不会更优。

---

