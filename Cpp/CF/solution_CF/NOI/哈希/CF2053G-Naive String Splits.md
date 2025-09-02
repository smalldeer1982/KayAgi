# Naive String Splits

## 题目描述

Cocoly 有一个长度为 $m$ 的字符串 $t$，全部由小写字母组成。他希望可以把这个字符串拆分成多个部分。若存在一个字符串序列 $a_1, a_2, \ldots, a_k$，满足：

- $t = a_1 + a_2 + \ldots + a_k$，其中 $+$ 表示字符串的连接。
- 对于每个 $1 \leq i \leq k$，至少满足 $a_i = x$ 或 $a_i = y$。

那么就称字符串对 $(x, y)$ 是美丽的。

Cocoly 还有一个长度为 $n$ 的字符串 $s$，同样由小写字母构成。现在，对于每一个位置 $1 \leq i < n$，Cocoly 需要你来判断字符串对 $(s_1s_2 \ldots s_i, \, s_{i+1}s_{i+2} \ldots s_n)$ 是否美丽。

注意：由于数据量较大，输入输出需要进行优化，例如在 C++ 中，可以在 `main` 函数的开头加入以下代码，以提高效率：

```cpp
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);
}
```

## 说明/提示

举例来说，第一个测试用例中，$s = \tt aba$，$t = \tt ababa$。

- 当 $i = 1$：Cocoly 可以将 $t$ 分割为 $\texttt{a} + \texttt{ba} + \texttt{ba}$，因此字符串对 $(\texttt{a}, \texttt{ba})$ 是美丽的。
- 当 $i = 2$：Cocoly 可以将 $t$ 分割为 $\texttt{ab} + \texttt{ab} + \texttt{a}$，因此字符串对 $(\texttt{ab}, \texttt{a})$ 也是美丽的。

在第二个测试用例中，$s = \tt czzz$，$t = \tt czzzzzczzz$。

- 当 $i = 1$：可以证明无法通过字符串 $\texttt{c}$ 和 $\texttt{zzz}$ 将 $t$ 进行美丽的分割。
- 当 $i = 2$：Cocoly 可以将 $t$ 分割为 $\texttt{cz} + \texttt{zz} + \texttt{zz} + \texttt{cz} + \texttt{zz}$。
- 当 $i = 3$：Cocoly 可以将 $t$ 分割为 $\texttt{czz} + \texttt{z} + \texttt{z} + \texttt{z} + \texttt{czz} + \texttt{z}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
3 5
aba
ababa
4 10
czzz
czzzzzczzz
5 14
dream
dredreamamamam
5 18
tcccc
tcctccccctccctcccc
7 11
abababc
abababababc
7 26
aaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaa
19 29
bbbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbbbbbbbbbbbbbbbb```

### 输出

```
11
011
0010
0000
010100
111111
110010001100010011```

# 题解

## 作者：沉石鱼惊旋 (赞：12)

# 前言

这题太曲折了。最后的官方 Editorial 是我重写的。

<https://codeforces.com/blog/entry/136455>

~~并非本文抄袭官方题解，是官方题解抄袭本文。~~

# 题目翻译

给定长度为 $n$ 的字符串 $s$ 和长度为 $m$ 的字符串 $t$。对于每个 $k\in[1,n)$，问 $s$ 的长度为 $k$ 的前缀和 $s$ 的长度为 $n-k$ 的后缀这两个字符串，能不能拼接得到字符串 $t$。一个前缀 / 后缀可以使用多次。

$2\leq n,m\leq 5\times 10^6$。

多测，$1\leq T\leq 10^5$，$1\leq \sum m\leq 10^7$。

# 题目思路

不妨把前缀 $s_1$ 叫做短串，后缀 $s_2$ 叫做长串。如果 $|s_1|\gt |s_2|$ 换一下顺序不影响答案。

考虑一个贪心做法。我们每次先匹配几个短串，直到无法匹配。如果无法匹配，我们就尝试扔掉几个短串，放一个长串。枚举扔几个短串即可。**找到第一个位置使得可以放一个长串**。我们把这样放一次叫做一次『匹配过程』，每次『匹配过程』的开始位置就是上个『匹配过程』的下个位置。

但是这个做法是有漏洞的。下面将会说明这个漏洞的情况。

---

不难把长串看作是若干个短串拼上一个『尾巴』。

为什么只要找到第一个位置呢？为什么多反悔几个 $s_1$ 再放不会更优呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/v793c2d8.png)

上图是一个例子。红线是我们匹配 $s_1$ 的截止位置。三个橙色方框表示尝试匹配长串的选择。

最后一个是不合法的，跳过，换『第一个合法的放长串的位置』这个框。这个框是合理的。

选第二个框和选第一个框的差距在，结束匹配进行下一轮的时候，我们需要匹配的内容，是选择了一段 $s_1$ 的后缀放到了 $s_1$ 的开头。

如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/bmhz3e7z.png)

对齐得到下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/qur4odo1.png)

图中是 $|pre|\gt |suf|$ 的情况，另一种是同理的。

$pre+suf=suf+pre$，通过图片不难看出这里是 $pre+suf$ 需要“错位相等”的。也就是 $s_1$ 需要存在一个循环节，且『尾巴』也需要能够通过循环节拼出来，$s_2$ 前面那 $|s_1|$ 个字符还是需要能被循环节拼出来。

总结一下就是相当于 $s_1,s_2$ 有**公共循环节**。

也就是说，**反悔两次能凑出答案，反悔一次不一定可行**，需要满足二者有公共循环节。

有公共循环节这个太特殊了。首先这两个的公共循环节一定会是 $s$ 这个串的循环节。提前找到这个循环节，然后相当于是解方程，设 $a=|s_1|,b=|s_2|$，即判断是否有非负整数解 $x,y$ 满足 $xa+yb=|s|$。

这个解方程纯纯唬人。我们枚举 $y$，每一次计算枚举 $\mathcal O(\frac{m}{n})$ 次。最多 $n$ 次，复杂度 $\mathcal O(m)$。

---

漏洞解决了，剩下的情况我们**找到第一个可以放长串的位置就放**这个贪心是对的。

直接实现的话，复杂度最劣是调和级数的。考虑这个情况，$s_1=\texttt{a},s_2=\texttt{aaaaaaaab},t=\tt{aaaaaaaaaaaaaaaaaaaaaaaaab}$ 这种，我们尝试 $\mathcal O(\frac{m}{|s_1|})$ 步才能结束匹配短串。反悔每次至多 $\mathcal O(\frac{m}{|s_2|})$ 次，每次 $\mathcal O(\frac{|s_2|}{|s_1|})$。

---

好吧这个题确实是可以线性的。

首先设长串的前缀包含了 $c$ 个短串，那么我们反悔到的第一个『可以放长串的位置』只可能是反悔 $c$ 个短串或者 $c+1$ 个短串得到的。

这个很好理解，反悔 $c$ 个就是看作是长串的前缀，然后加上长串的『尾巴』。反悔 $c+1$ 个当且仅当长串的『尾巴』部分是短串的前缀。例如 CF 评论区的 hack：

<https://codeforces.com/blog/entry/136455?#comment-1234262>

```plain
1
8 8
abaabaab
abaababa
```

正确输出应该为

```plain
0010000
```

在 $k=3$ 的时候 $s_1=\texttt{aba},s_2=\texttt{abaab}$，此时我们先填充了 $2$ 个短串，但是只撤销 $c=1$ 个就会判成无解，std 的锅就是这么出的。只有在 $s_2$ 的『尾巴』部分是 $s_1$ 的前缀的时候才会出现这种情况。

所以我们每次计算的时候先二分出这个 $c$，复杂度是 $\mathcal O(\sum\limits_{i=1}^n\log(\frac n i))=\mathcal O(n)$ 的。之后反悔只需要进行两次判断。反悔过程做到线性了。

接下来对填充短串部分进行加速。暴力填充的 hack 上面已经给出了。如果直接使用一开始大家都认为是对的的『二分短串出现次数』的方法，那么可以通过

```plain
1
2 5000000
ab
abababab....abababab
```

这组 hack 卡到 $\log$。

@[_LHF_](/user/99506) 的评论指出两种替代方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/hozwdksl.png)

这里详细分析一下第二种做法。经过沟通，这里 lhf 老师笔误了。应该是匹配 $\frac{n}{|s_1|}$ 个。

类似分块，取 $B=\frac{n}{|s_1|}$。我们先尝试匹配 $B$ 个 $s_1$，也就是说每次匹配都可以往前推动 $n$ 个位置。之后剩下的部分不会超过 $B$ 个，二分出剩下内容具体有几个。而前面一次推进 $B$ 个的部分，至多反悔掉一次，后面二分，就变成了 $\mathcal O(\log B)$。每次至少可以填充 $|s_2|$ 个。这里计算一次答案复杂度就变成了 $\mathcal O(\frac{m}{|s_2|}\log B)$，总复杂度由于 $\mathcal O(\sum\limits_{i=1}^n\log(\frac n i))=\mathcal O(n)$ 所以是 $\mathcal O(m)$ 的。

至此，本题在线性时间解决了。

# 代码链接

这是一份依据 @[_LHF_](/user/99506) 指出的做法的第二条的实现。

[CF submission 299319348](https://codeforces.com/contest/2053/submission/299319348)

---

## 作者：IvanZhang2009 (赞：3)

先不考虑复杂度，就给你两个串，如何判定是否可以拼出 $t$ 呢？

我们考虑如何正确地直接贪心。**假设 $\bm{s_1,s_2}$ 不存在公共循环节**，原因后面再说。具体地，设我们试图用字符串 $s_1,s_2$ 拼出字符串 $t$，且 $\lvert s_1\rvert\le \lvert s_2\rvert$。此处给定一个贪心：不断地匹配短串 $s_1$，直到匹配不上为止，然后尝试匹配**一次** $s_2$。注意到这样可能会出问题，因为如果 $s_2$ 有若干个 $s_1$ 作为前缀，可能有类似反悔的操作。例如 $s_1=\tt{ab}$，$s_2=\tt{ababc}$。贪心匹配 $t=\tt{abababc}$ 时，先用 $s_1$ 匹配了 $3$ 次，然后直接塞 $s_2$ 也不合法，但是由于 $s_2$ 包含两次 $s_1$ 作为前缀，可以撤销掉这两个匹配重新尝试塞 $s_2$。

形式化地，设 $s_2=s_1^k+c$，我们每次先贪心匹配 $s_1$，然后遇到匹配不了的地方先直接匹配 $s_2$。如果失败了就撤回 $k$ 次 $s_1$ 的匹配，然后接着匹配 $s_2$。如果再失败，其实如果 $c$ 是 $s_1$ 的前缀，可以再撤回一次 $s_1$ 并尝试匹配，具体可以手玩下面这个数据中 $s_1=\tt{aba},s_2=\tt{abaab}$ 的情况：

```
1
8
abaabaab
abaababa
```
这个例子里，先匹配了两次 $\tt{aba}$，然后撤回发现 $\tt{ababa}\neq\tt{abaab}$ 然后似了。然而再撤回到开头匹配 $s_2$ 就能正确。

这启发我们考虑如何反悔。是否需要反悔多次呢？仍设 $s_2=s_1^k+c$，并且先假设有一个串 $t$ 我们要多反悔两次。这就相当于 $t=s_1^{k+2}+\dots$。多反悔两次相当于撤回 $k+2$ 个 $s_1$ 的匹配，即令 $t=s_2+b=s_1^{k}+c+b$。由于 $b$ 一定是接上 $s_1$ 或 $s_2$，可以认为 $s_1$ 是 $b$ 的前缀，于是 $t=s_1^{k}+c+s_1+\dots=s_1^{k+2}+\dots$。可以得到 $c+s_1+\dots=s_1+s_1$（注意 $c$ 必须是 $s_1$ 的前缀，长度必然更小）。两个 $s_1$ 可以覆盖自己，则它必然和 $c$ 存在公共循环节，与之前的假设不符。

于是姑且认为只需要多反悔一次即可。

对于 $s_1$ 和 $s_2$ 有公共循环节的部分，先判断 $t$ 是否也有这个公共循环节，剩下的部分相当于给定 $a,b,c$，求是否有关于方程 $ax+by=c$ 的对于 $x,y$ 的非负整数解。

考虑原问题，我们可以直接暴力地做这些操作！注意到对于短串的长度为 $i$，我们匹配短串的次数最多为 $\frac mi$，而 $\sum\frac mi$ 是调和级数，$O(m\log m)$ 可以接受。对于长串，容易发现其出现位置一定不重叠，而长串的长度是 $O(n)$ 的，于是单次时间复杂度 $O(\frac mn)$，做 $n$ 次是线性。

对于公共循环节的部分，我们不需要任何 exgcd，直接枚举长串的出现次数判断整除即可，时间复杂度同长串匹配，是线性的。

可以使用 hash 或 Z 实现匹配。时间复杂度 $O(m\log m)$。

关于把暴力匹配改成二分的做法，可以发现用 $s=\tt{ab}$，$t=\tt{ab}^{\frac{m_{\max}}2}$ 可以卡成 $O(m\log m)$，所以复杂度理论上还是没啥改进。

这题现在的数据还真是弱爆了，卡不掉二分，卡不掉错误的匹配。从题解看上去像是我造的但是大家其实都不太会造强数据啊，我只是稍微造了点能看的东西吧。不知道后面会不会再加强一下的。

给一个使用二分的代码，在这版数据下跑的挺快。hash 是 SA 改的，所以代码莫名其妙的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define base        2310907499
#define MOD         2933256077ll
#define int         long long
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
#define lowbit(x)   ((x)&(-(x)))
#define cntbit(x)   __builtin_popcount(x)
#define deal(v)     sort(all(v));v.erase(unique(v.begin(),v.end()),v.end())
#define lbound(v,x) lower_bound(all(v),x)-v.begin()
mt19937 sd(random_device{}());
int qpow(int a,int b,int m=MOD,int res=1){
	a%=m;
	while(b>0)res=(b&1)?(res*a%m):(res),a=a*a%m,b>>=1;
	return res;
}
int exgcd(int x,int y,int &a,int &b){
	if(y==0){
		a=1;b=0;
		return x;
	}
	int d=exgcd(y,x%y,a,b);
	int z=b;
	b=a-b*(x/y);
	a=z;
	return d;
}
int _x_,_y_;
inline int inverse(int x,int y=MOD){
	exgcd(x,y,_x_,_y_);
	return (_x_+y)%y;
}
int TT;
int h[1000];
uniform_int_distribution<int>rd(0,MOD-1);
struct SA{
    void initbase(int n=10000000){
        p1[0]=p2[0]=1;
        p1[1]=base;p2[1]=inverse(base);
        REP(i,2,n+1)p1[i]=p1[i-1]*p1[1]%MOD,p2[i]=p2[i-1]*p2[1]%MOD;
	}
    string s;
    int n;
    int p1[10000005],p2[10000005];
    int sum[10000005];
    int ask(int l,int r){
        return 1ull*(sum[r+1]+MOD-sum[l])*p2[l]%MOD;
    }
    void build(string S){
        s=S;n=s.size();
        sum[0]=0;
        REP(i,0,n)sum[i+1]=(sum[i]+p1[i+1]*h[s[i]]%MOD)%MOD;
    }
}sa;
int n,m;
bool same(int l,int L,int len){
    return sa.ask(l,l+len-1)==sa.ask(L,L+len-1);
}
bool check(int l,int r,int len,int op=1){
    if(op)l+=n,r+=n;
    if((r-l+1)%len)return 0;
    if(r-l+1==len)return 1;
    return same(l,l+len,r-l+1-len);
}
int getcopies(int x,int rt,int y,int len){
    int l=1,r=(rt-x+1)/len,res=0;
    if(!same(x,y,len))return 0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(x,x+mid*len-1,len,0))res=mid,l=mid+1;
        else r=mid-1;
    }
    return res;
}
string t,s;
int T;
void Main() {
	cin>>m>>n>>s>>t;
	T-=clock();
    sa.build(t+s);
    T+=clock();
    int f=m,g=0;
    for(int i=m-1;i>=1;--i)if(check(0,m-1,i))f=i;
    if(check(0,n-1,f,0)&&same(0,n,f))g=1;
    REP(i,0,m-1){
        int l1=0,l2=i+1,t1=i+1,t2=m-t1;
        if(t1>t2)swap(l1,l2),swap(t1,t2);
        if(t1%f==0&&t2%f==0){
        	if(!g){putchar(48);continue;}
			int x=t1/f,y=t2/f,z=n/f,op=0;
			for(int i=0;i*y<=z;++i)if((z-i*y)%x==0){op=1;break;}
			putchar(op+48);
			continue;
		}
        bool f=1;
        int x=0,ct=getcopies(l2+n,l2+t2-1+n,l1+n,t1);
        while(x<n){
            int l=getcopies(x,n-1,l1+n,t1);
            if(x+l*t1==n)break;
            else if(l<ct){f=0;break;}
            else{
            	x+=(l-ct)*t1;
				if(x+t2<=n&&same(x,l2+n,t2)){x+=t2;continue;}
			}
            if(l>=ct+1&&x-t1+t2<=n&&same(x-t1,l2+n,t2)){x+=t2-t1;continue;}
            f=0;break;
        }
        putchar(f+48);
    }
    puts("");
}
void TC() {
	sa.initbase();
    REP(i,0,200)h[i]=rd(sd);
    int tc=1;
    cin>>tc;
	while(tc--){
		Main();
		cout.flush();
	}
}
signed main() {
	return cin.tie(0),cout.tie(0),ios::sync_with_stdio(0),TC(),0;
}
```

---

## 作者：MatrixGroup (赞：3)

设 $s$ 分出来的前后缀为 $s=p+q$。如果我们能 $O(1)$ 判断下一个要匹配的是 $p$ 还是 $q$，使用字符串哈希 $O(1)$ 判断它是否就是要匹配的，就可以以两倍的调和级数的复杂度，即 $O(m\log n)$ 通过。

首先，若 $p+q=q+p$，则可以辗转相减得出 $p$ 和 $q$ 必然存在公共周期 $r$（不妨取 $r$ 为原串 $s=p+q$ 的最小周期），则可以拼成 $t$ 当且仅当 $t$ 也有 $r$ 为周期，且 $|t|=|p|a+|q|b$ 有非负整数解 $a,b$。可以枚举 $\max(|p|,|q|)$ 前面的系数，因为 $\max(|p|,|q|)\ge \dfrac n2$，于是这部分复杂度是 $O(n)$ 个 $O\left(\dfrac mn\right)$，即 $O(m)$。

否则，若 $p+q\neq q+p$，可以断言 $p+q$ 和 $q+p$ 第一个不同的位置，对应到原串里看它是 $p+q$ 和 $q+p$ 该位置的哪一个即可。（特别地，如果剩下的长度不足 $n$，则要么是较长的出现一次，要么是较短的一直拼，直接判断即可）换言之，对任意字符串 $p,q$，若 $p+q\neq q+p$，设 $r$ 为 $p+q$ 和 $q+p$ 第一个不同的位置，我断言 $p$ 开头加上一些 $p$，$q$ 的拼接的第 $r$ 个位置一定是 $p+q$ 的第 $r$ 个位置，而 $q$ 开头加上一些 $p$，$q$ 的拼接的第 $r$ 个位置一定是 $q+p$ 的第 $r$ 个位置。下面证明这一点。不失一般性，设 $|p|\le |q|$。

- 若 $r\le |p|$，换言之 $p$ 不是 $q$ 的前缀，显然。
- 否则，若 $q$ 不是 $p+p+p+p+\cdots$ 的前缀，则设 $q=kp+r_0(k\ge 1)$，其中 $p$ 不是 $r_0$ 的前缀，$r_0$ 也不是 $p$ 的前缀。显然 $r$ 就是 $r_0$ 和 $p$ 第一个不同的位置加上 $k|p|$，这个位置在 $p+q$ 里一定在 $(k+1)p$ 中。显然，$q$ 开头加上一些 $p$，$q$ 的拼接一定以 $q+p$ 为前缀，故后半句显然。而 $p$ 开头加上一些 $p$，$q$ 的拼接，设第一个 $q$ 前有 $k_0$ 个 $p$。（如果没有 $q$，不妨改成足够远处有 $q$ 而不影响）则整个串以 $(k_0+k)p$ 为前缀，故以 $(k+1)p$ 为前缀，因为第一个不同的位置在此已经出现，得证。
- 否则，$q$ 为 $p+p+p+\cdots$ 的前缀，则设 $q=kp+r_0(k\ge 1)$，其中 $r_0$ 为 $p$ 的非空真前缀。则 $p$ 开头加上一些 $p$ 和 $q$ 一定以 $p+q$ 为前缀，这是因为 $q$ 是 $p+q$ 的前缀，归纳可得也是 $k_0p+q$ 的前缀，取 $k_0$ 为第一个 $q$ 的前的 $p$ 的个数即证（和第二点中一样不妨设有 $q$）。而又显然 $q$ 开头加上一些 $p$ 和 $q$ 一定以 $q+p$ 为前缀，即证。

依此判断即可。

如果你和我写的一样，你可能会被卡常数。考虑 $p+q$ 和 $q+p$ 的第一个不同位置其实是 $s+s$ 和它的一个后缀的 LCP，可以用 Z 函数而不是二分哈希。然后也可以发现可以不用双哈希，单哈希能过。这是因为，如果假设出题人不对着卡，可以假设哈希的正确率是 $\dfrac 1p$。虽然看起来要比较调和级数那么多次，但是出现一次不同就可以判断出来不行了，因此你只要正确判断 $n-1$ 次不同。一个测试点的 $\sum n$ 最多不到 $10^7$，而本题截止写作为止共有 $81$ 个测试点，且 $\sigma n$ 卡满的不多（如果 $n=m$ 那可以直接判断，出题人肯定不会放很多这样的数据），而模数是 $10^9$ 级别，这是可以通过的。

[AC 代码](https://codeforces.com/contest/2053/submission/299270809)

---

## 作者：Unnamed114514 (赞：2)

我们先让问题普通化，即转化为给出两个字符串 $s_1,s_2$，问你能不能拼接成 $t$，不妨 $|s_1|\le|s_2|$，也就是说，$n$ 和 $m$ 只是用来考量复杂度的。

显然 dp 不便于解决这个问题，因此我们考虑贪心。

先把 $s_1$ 和 $s_2$ 有公共周期判掉，这种情况相当于得到一个 $ax+by=\dfrac{m}{L}(a<b\cup a+b=\dfrac{n}{L})$ 的不定方程，枚举 $y$ 即可，时间复杂度 $O(\sum\limits_{k=1}^n\dfrac{\frac{m}{\gcd(k,n-k)}}{\frac{\max\{k,n-k\}}{\gcd(k,n-k)}})=O(\sum\limits_{k=1}^n\dfrac{m}{\max\{k,n-k\}})\le O(\sum\limits_{k=1}^n\dfrac{m}{k})=O(m\log m)$，至于循环节部分，显然可以做到 $O(n\log n)$ 预处理。

考虑把 $s_2$ 表示成 $s_1^k+c$ 的形式，其中 $s_1^k$ 表示 $k$ 个 $s_1$ 拼起来，且 $s_1$ 不为 $c$ 前缀。

然后我们优先匹配 $s_1$。假设现在的串是 $\cdots s_1^c\cdots$，现在后面匹配不了 $s_1$ 了，那么现在我们显然要加入 $s_2$。

然后我们就需要往前回滚。因为后面不可能再匹配 $s_1$，所以我们至少需要往前回滚 $k$ 个，如果往前回滚 $k$ 个不行怎么办呢？

答案是回滚 $k+1$ 个，那如果 $k+1$ 个还是不行呢？我们需要继续回滚 $k+2$ 个吗？

我们先来解决这个问题。

首先如果 $k=0$ 那么无论回滚 $1$ 个还是回滚两个，因为有一个 $s_1$ 作为前缀那么都不行，否则 $k\ge1$，此时 $s_1$ 为 $s_2$ 的前缀，下述讨论均以此为基础。

如果回滚 $k+1$ 个和 $k+2$ 个都能得到 $s_2$，我们容易列出下列方程：

$$s_1+s_1^k+c=s_1^k+c+s_1$$

因为此时无论后面接 $s_1$ 还是 $s_2$，前 $|s_1|$ 个字符一定组成了 $s_1$。

画一下图就会发现，此时 $c$ 为 $s_1$ 的周期，那么 $c$ 就为 $s_1,s_2$ 的周期，但是 $c$ 为 $s_1,s_2$ 的公共周期的情况我们已经在开始时判掉了，此时不会存在这种情况，所以我们不需要反悔到 $k+2$。

为什么我们需要反悔到 $k+1$ 呢？

考虑以下数据：

```
8 8
abaabaab
abaababa
```

现在我们需要考虑 $s_1=s_{1,3},s_2=s_{4,8}$ 的情况：

首先我们先搞了两个 $s_1$，如果反悔一个的话，那么就会有 `ababa` 这个串，然后就会被判作不可以。但是显然我们存在 `abaab` 和 `aba` 拼接得到的方案，此时是反悔两次得到的。

所以我们反悔 $k+1$ 次是有必要的。

那么我们应该反悔 $k$ 次还是 $k+1$ 次呢？

如果反悔 $k$ 次和 $k+1$ 次都能得到 $s_2$ 的话，我们仍然可以列出如下等式：

$$s_1+s_1^k+c=s_1^k+c+s_1$$

那么此时仍然有 $c$ 为 $s_1,s_2$ 的公共循环节，所以不可能存在往前回滚 $k$ 和 $k+1$ 次都能得到 $s_2$ 的情况。

其实上述论证还存在的问题是：如果 $k$ 和 $k+1$ 都不行，那么是否需要反悔 $k+2$？

反悔 $k+1$ 得到 $s_2$ 的情况，当且仅当 $c$ 为 $s_1$ 的前缀时，此时你会发现如果能反悔 $k+2$ 得到 $s_2$ 的话，要么 $c$ 为 $s_1$ 前缀，此时反悔 $k+1$ 能得到；否则 $s_1$ 为 $c$ 前缀，这与 $s_1$ 不为 $c$ 前缀的定义矛盾。

那么这个贪心就证明完了，接下来要处理的是时间复杂度的问题。

如果只跳 $s_1$ 的话，复杂度是一个较为简单的调和级数。

注意到最多反悔次数为 $O(\dfrac{m}{|s_2|})$ 次，因为 $|s_2|\ge|s_1|$，所以反悔的时间复杂度也是不弱于调和级数的。

因此我们就得到了时间复杂度为 $O(n\log n)$ 的做法。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=5e6+5,base=13331,mod=1e9+7;
int T,n,m,L,l,h[2][N],p[N];
bool chk1[N],chk2[N];
string s,t;
int get_hash(int id,int l,int r){ 
	int res=h[id][r]-1ll*h[id][l-1]*p[r-l+1]%mod; 
	if(res<0) res+=mod;
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	p[0]=1;
	for(int i=1;i<=5e6;++i) p[i]=1ll*p[i-1]*base%mod;
	while(T--){
		cin>>n>>m>>s>>t,s=' '+s,t=' '+t;
		for(int i=1;i<=n;++i) h[0][i]=(1ll*h[0][i-1]*base+s[i])%mod;
		for(int i=1;i<=m;++i) h[1][i]=(1ll*h[1][i-1]*base+t[i])%mod;
		for(int i=1;i<=n;++i){
			if(n%i==0){
				chk1[i]=1;
				for(int j=1;j<=n/i;++j) if(get_hash(0,(j-1)*i+1,j*i)!=get_hash(0,1,i)){
					chk1[i]=0;
					break;
				}
				if(chk1[i]){
					if(m%i){
						chk2[i]=0;
						continue;
					}
					chk2[i]=1;
					for(int j=1;j<=m/i;++j) if(get_hash(1,(j-1)*i+1,j*i)!=get_hash(0,1,i)){
						chk2[i]=0;
						break;
					}
				}
			} else chk1[i]=0;
		}
		for(int k=1;k<n;++k){
			int L=__gcd(k,n-k);
			if(chk1[L]){
				if(!chk2[L]){
					cout<<0;
					continue;
				}
				int a=k/L,b=(n-k)/L,c=m/L;
				if(a<b) swap(a,b);
				bool flg=0;
				for(int i=0;i<=c/a;++i) if((c-i*a)%b==0){
					flg=1;
					break;
				}
				if(flg) cout<<1;
				else cout<<0;
				continue;
			}
			if(k<=n-k){
				int p=0;
				while((p+2)*k<=n&&get_hash(0,(p+1)*k+1,(p+2)*k)==get_hash(0,1,k)) ++p;
				int c=0,now=0;
				while(now<m){
					if(now+k<=m&&get_hash(1,now+1,now+k)==get_hash(0,1,k)){
						++c,now+=k;
						continue;
					}
					if(c>=p&&now-p*k+(n-k)<=m&&get_hash(1,now-p*k+1,now-p*k+(n-k))==get_hash(0,k+1,n)){
						c=0,now=now-p*k+(n-k);
						continue;
					}
					if(c>=p+1&&now-(p+1)*k+(n-k)<=m&&get_hash(1,now-(p+1)*k+1,now-(p+1)*k+(n-k))==get_hash(0,k+1,n)){
						c=0,now=now-(p+1)*k+(n-k);
						continue;
					}
					break;
				}
				if(now==m) cout<<1;
				else cout<<0;
			} else{
				int p=0;
				while((p+1)*(n-k)<=k&&get_hash(0,p*(n-k)+1,(p+1)*(n-k))==get_hash(0,k+1,n)) ++p;
				int c=0,now=0;
				while(now<m){
					if(now+(n-k)<=m&&get_hash(1,now+1,now+(n-k))==get_hash(0,k+1,n)){
						++c,now+=(n-k);
						continue;
					}
					if(c>=p&&now-p*(n-k)+k<=m&&get_hash(1,now-p*(n-k)+1,now-p*(n-k)+k)==get_hash(0,1,k)){
						c=0,now=now-p*(n-k)+k;
						continue;
					}
					if(c>=p+1&&now-(p+1)*(n-k)+k<=m&&get_hash(1,now-(p+1)*(n-k)+1,now-(p+1)*(n-k)+k)==get_hash(0,1,k)){
						c=0,now=now-(p+1)*(n-k)+k;
						continue;
					}
					break;
				}
				if(now==m) cout<<1;
				else cout<<0;
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

