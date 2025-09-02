# The World Is Just a Programming Task (Hard Version)

## 题目描述

This is a harder version of the problem. In this version, $ n \le 300\,000 $ .

Vasya is an experienced developer of programming competitions' problems. As all great minds at some time, Vasya faced a creative crisis. To improve the situation, Petya gifted him a string consisting of opening and closing brackets only. Petya believes, that the beauty of the bracket string is a number of its cyclical shifts, which form a correct bracket sequence.

To digress from his problems, Vasya decided to select two positions of the string (not necessarily distinct) and swap characters located at this positions with each other. Vasya will apply this operation exactly once. He is curious what is the maximum possible beauty he can achieve this way. Please help him.

We remind that bracket sequence $ s $ is called correct if:

- $ s $ is empty;
- $ s $ is equal to "( $ t $ )", where $ t $ is correct bracket sequence;
- $ s $ is equal to $ t_1 t_2 $ , i.e. concatenation of $ t_1 $ and $ t_2 $ , where $ t_1 $ and $ t_2 $ are correct bracket sequences.

For example, "(()())", "()" are correct, while ")(" and "())" are not.

The cyclical shift of the string $ s $ of length $ n $ by $ k $ ( $ 0 \leq k < n $ ) is a string formed by a concatenation of the last $ k $ symbols of the string $ s $ with the first $ n - k $ symbols of string $ s $ . For example, the cyclical shift of string "(())()" by $ 2 $ equals "()(())".

Cyclical shifts $ i $ and $ j $ are considered different, if $ i \ne j $ .

## 说明/提示

In the first example, we can swap $ 7 $ -th and $ 8 $ -th character, obtaining a string "()()()()()". The cyclical shifts by $ 0, 2, 4, 6, 8 $ of this string form a correct bracket sequence.

In the second example, after swapping $ 5 $ -th and $ 10 $ -th character, we obtain a string ")(())()()(()". The cyclical shifts by $ 11, 7, 5, 3 $ of this string form a correct bracket sequence.

In the third example, swap of any two brackets results in $ 0 $ cyclical shifts being correct bracket sequences.

## 样例 #1

### 输入

```
10
()()())(()
```

### 输出

```
5
8 7
```

## 样例 #2

### 输入

```
12
)(()(()())()
```

### 输出

```
4
5 10
```

## 样例 #3

### 输入

```
6
)))(()
```

### 输出

```
0
1 1
```

# 题解

## 作者：Logey (赞：9)

这题最大的价值在于引入了一种非常直观有效的思考括号序列相关题目的工具：折线图。

对于一个长度为 $n$ 的括号序列，把左括号看做 $+1$，右括号看做 $-1$，求出该序列的前缀和数组 $h_i$。

一个括号序列合法的充要条件为：

 - $\forall i \in [0, n], h_i \geq 0$；
 - $h_n = 0$。

将 $h_i$ 画到平面直角坐标系中，可以发现合法的充要条件是：

  - 整条直线不低于 $x$ 轴。
  - $h_n=0$

现在回到题目中，先来思考一个没有修改的 $Case$，即一个序列循环移位之后合法的括号序列有多少个。

若 $h_i=n$ ，结论是**所有最小值所在的位置都一一对应一个合法的括号序列**。

设所有最小值的位置为 $p_i$。可以发现原序列中 $p_i$ 的位置一定是右括号，且任意 $h_{p_i} \leq 0$。使得位置 $p_{i}+1$为新的序列的开头即可得到一个合法的括号序列。

至于为什么是合法的括号序列，则需要考虑该循环唯一对于前缀和数组的影响以及判定合法的充要条件。

设 $t = |\min h_i|$，可以发现操作之后，原来 $(p_i, n]$ 的位置整体上移 $y$ 个单位长度，且将 $[0, p_i]$ 这个折线也向上平移 $t$ 之后接到了后面。

现在思考一下这个折线图是否合法：

 - 整条折线向上平移了 $t$，可以发现一定不越过 $x$ 轴。
 - 左右括号的数量并没有变化，所以 $h_n$依然为 $0$。

至此简单的 $Case$ 已经解决了。

现在再考虑上进行一次修改，要使得最小值的数量最多。

一定只需要考虑交换不同的括号，否则这个操作相当于没做。

现在考虑交换对于 $h_i$ 数组的影响。

 - 交换`(`和`)` 相当于区间减 $2$。
 - 交换`）`和`(`相当于区间加$2$。

可以发现操作 $2$ 不会使得答案变优。

先将序列变成其中一个最小值对应的合法括号序列，这个操作一定是可以完成的，变换之后必然不会有区间是一段前缀和后缀拼起来，具体原因下面讲。

变换之后 $t=0$。

答案一定来自最小值是否变化两种情况。

 - 最小值不变，则需要最大化修改区间内 $2$ 的数量，且不能包含 $1, 0$。
 - 最小值变化，则需要最大化 $1$ 的数量，且不包含 $0$。

如果将原有的 $0$ 变成 $-2$ 显然是不优的，因为不会比原序列 $0$ 的数量更多。

至此问题解决，根据实现不同可以做到 $O(n)$  或者 $O(n \log n)$。


---

## 作者：Kelin (赞：6)

## [题意](https://blog.csdn.net/BeNoble_/article/details/102672972)
给你一个长度为$n$的括号序列$s$

定义一个能够完全匹配的括号序列为合法序列

定义$f(s)$表示有多少位置$i$使得$s_{i...n}s_{1...i-1}$为合法序列

交换$s$的任意两个字符，使得$f(s)$最大

---

## 题解
首先判断是否左括号数量是否与右括号相等

将原序列转变成一个合法的括号序列

找到一个**累计**右括号最多的地方，前后交换一下即可

记录每个左括号的位置和对应右括号的位置并给它们编号

记$Cnt_i$表示编号为$i$的那一对括号里面有多少合法括号子列

特别的，记录$Cnt_0$表示不交换时有多少位置符合条件

考虑交换对答案的影响

①：交换编号为$p$的括号对且这对括号不被任何其他括号包含

>即$s_1...s_i(t_1...t_j)c_1...c_k\Rightarrow s_1...s_i)t_1...t_j(c_1...c_k$
>
>合法的位置有$(c_1...c_ks_1...s_i)t_1...t_j;t_j(c_1...c_ks_1...s_i)t_1...t_{j-1};...;t_1...t_j(c_1...c_ks_1...s_i)$
>
>答案就是$Cnt_p+1$（其中$s,t,c$均为不可分割的合法括号子序列）

②：交换编号为$p$的括号对且这对括号只被包含一层

>即$s_1...s_i(t_1...t_a(t_{a+1}...t_b)t_{b+1}...t_j)c_1...c_k\Rightarrow s_1...s_i(t_1...t_a)t_{a+1}...t_b(t_{b+1}...t_j)c_1...c_k$
>
>那么答案就是$Cnt_0+Cnt_p+1$

③：交换编号为$p$的括号对且这对括号被包含的层数大于$1$

>一种简单的情况即$((...(t_a...t_b)...))\Rightarrow ((...)t_a...t_b(...))=(t_1t_a...t_bt_k)$
>
>可以发现这种交换答案是不会改变的

④：交换不是相对应的括号

>如果是交换最外层的括号即$(...)t_1...t_j(...)\Rightarrow(...(t_1...t_j)...)$，答案会减小；甚至变为$1$，如$s(t)c\Rightarrow s)t(c$
>
>如果跨越包含自己的括号交换，一种简单情况即$((a))(b)\Rightarrow()a))(b($，答案会变成$1$；其他情况也同理
>
>如果是交换同一层（不是最外层）之间的括号，则答案不会改变，因为不能改变最外层的括号匹配

综上可以分析发现，只有操作①②可能会使得答案变大的，所以只需要考虑这两种情况即可

时间复杂度$O(n)$

```cpp
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=3e5+5;
typedef int arr[N];
int n,sL=1,sR=1,Mid,Min,Num,Top,Ans;
arr L,R,fa,stk,Cnt;
char c[N],s[N];
int main(){
	#ifndef ONLINE_JUDGE
		file("s");
	#endif
	scanf("%d\n",&n);gets(c+1);
	fp(i,1,n){
		c[i]=='('?++Top:--Top;
		if(Top<Min)Min=Top,Mid=i;
	}
	if(Top)return puts("0\n1 1"),0;
	fp(i,Mid+1,n)s[i-Mid]=c[i];
	fp(i,1,Mid-1)s[i+n-Mid]=c[i];
	fp(i,1,n)
		if(s[i]=='(')stk[++Top]=++Num,L[Num]=i;
		else R[stk[Top]]=i,fa[stk[Top]]=stk[Top-1],++Cnt[stk[--Top]];
	Ans=Cnt[0];
	fp(i,1,Num)
		if(Cnt[i]+1>Ans&&!fa[i])Ans=Cnt[i]+1,sL=L[i],sR=R[i];
		else if(Cnt[0]+Cnt[i]+1>Ans&&fa[i]&&!fa[fa[i]])Ans=Cnt[0]+Cnt[i]+1,sL=L[i],sR=R[i];
	(sL+=Mid)>n?sL-=n:0,(sR+=Mid)>n?sR-=n:0;
	printf("%d\n%d %d",Ans,sL,sR);
return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
折磨题，想了一个上午+调了一个中午。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
我们考虑先去处理 easy version。

看到 $n$ 只有 $500$，考虑 $n^3$ 乱搞。

直接大力枚举出交换的是哪两个括号，此时复杂度已经来到 $n^2$。

接着就是要做到 $O(n)$ 数个数。

发现是括号匹配问题，考虑经典 trick。

碰到左括号就 $+1$，右括号就 $-1$，那么前缀累加一下，累加到负数的就是括号匹配不上的地方。

例如 `()(())))(`，其前缀和即为：$1,0,1,2,1,0,-1,-2,-1$。

考虑那些位置移到后面去才可能产生答案：必然是负数最大的位置。

因为合法段移来移去没有区别，所以只需考虑那一段单调的 $-1,-2,\dots,-x$。

如果我只移了这段的前面部分，那么最后面的 $-x$ 肯定消不完。

而如果我多移了一点，那么就会有一些 $+1$ 被移到最后面去，因为加的减少了，就相当于多减了一点，显然是必然会有新的数被减到负数。

这个实现也就比较简单了。

接着顺着这个思路，我们来考虑 D2。

显然我们的所有交换操作，当且仅当交换的两个括号不同时才会改变答案。

具体的，还是考虑前缀和，`(` 即变为 `)`，即相当于区间 $-2$，而 `)` 变为 `(`，即相当于区间 $+2$。

那这个时候我们就有两种可能性：
1. 区间加了之后，最小值变大了，与这个最小值相同的垫更多了，答案变大了。
2. 区间减了之后，最小值不变，而与这个最小值相同的值变多了，答案变大了。

显然的是，并不会出现**区间加后最小值不变**更优和**区间减后最小值变大**更优。

因为只有一次修改操作，所以对于**区间加后最小值不变**的情况，并不会有新的值变为最小值，而最小值反而有可能变少，所以严格不优。

后者则是同理，所以这时我们只需要考虑这两种情况。

第一种情况下，因为最小值改变了，所以并不是很好处理。

而第二种情况，最小值不变，所以我们只需要对于一个 `(` 左端点，找到一个最右的 `)` 右端点，满足他们这一段的前缀和的 $\min\ge mn+2$，其中 $mn$ 表示全局最小值。

这个时候他对答案额外的贡献就是 $mn+2$ 的值的数量。

上面那个可以用 ST 表+二分实现，下面那个可以先确定 $mn+2$ 直接前缀和数区间。

现在我们的问题便来到了怎么算第一种情况。

既然死活不会算，就只能把这种折磨情况转化掉了。

其实，我们可以发现，这种情况其实是严格不优的。

因为我们可以通过先把一段后缀移成前缀的方式把第一种情况全部化为第二种情况。

下面给个略证：

我们考虑，固定这个最小值。

显然的是，根据前面 D1 的做法，我们知道，在前缀和为 $mn$ 的时候把后缀这段移成前缀，可以得到合法的括号序列。

因为我们移一次和移很多次本质是相同的，所以我们不妨把最初的括号序列移成合法的括号序列。

在这个情况下 $mn$ 即为 $0$，因为是合法括号序列，所以左右两端点肯定可以取到 $0$，并且取不到负数。

此时考虑第一种情况的操作，我们会发现**第一种操作不存在**。

因为左右两端点肯定是 $0$，也就是最小值不可能大于 $0$，也就是无法改变最小值。

所以第一种操作不存在，自然不用考虑第一种操作。

原结论得证。

所以我们可以考虑通过**把最初的括号序列移成合法的括号序列**的方式避免情况一。

剩下就只有情况二了，直接使用上面说的方法实现即可，复杂度 $O(n\log n)$。

但是我们还可以有另一种实现方式。

考虑求出每个 `(` 对应的右括号，那么我们只需要考虑交换这两个括号即可。

因为不难发现，在合法括号序列中，`(` 对应的右括号必然是最右端，要么就不存在。

此时也只剩下三种情况：

1. 这层括号外层没套括号。

    此时如果交换这组括号，这组括号外的所有括号都会失效，可计算的答案只有这组括号中的合法括号数 $+1$。
   
    注意此处的合法括号的定义，`(())` 算做一个合法括号，`()` 也只算做一个合法括号，`()()` 算做两个合法括号。

2. 这层括号外套着一层括号。

    此时你会发现，因为这组括号内部也是合法的（因为整个括号序列是合法的）。

    所以对于这一部分括号序列，你会发现他的前缀和的左端点恰好值为 $2$。

   而因为合法，所以这一段前缀和的值严格不小于 $2$。

   所以这段前缀和的 $\min$ 恰好是 $2$，根据前面的计算方法，我们只需要数出来 $2$ 的个数加上总的个数再加上最外层括号的 $1$ 即可。

4. 这层括号外面套了不止一层括号。

    类似于 $3$，我们发现这段括号的前缀和的 $\min$ 不小于 $3$，显然 $-2$ 后不会有任何贡献。

所以我们只需要先用一遍 dfs 跑出来每对括号内的合法答案数，再按照上面的方法处理即可做到 $O(n)$。
## 代码
因为懒所以只实现了 $O(n)$ 做法。

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=6e5+10,V=3e5,M=310,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,dt,mn=0,k=0,ans,L,R,a[N],st[N],ss[N],nxt[N];char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='('||c==')'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int dfs(int u){for(int i=u+1;i<nxt[u];i++) if(s[i]=='(') i=dfs(i),ss[u]++;return nxt[u];}
inline void solve()
{
    read();rd(s,n);m=n;for(int i=1;i<=n;i++) a[i]=a[i-1]+(s[i]=='('?1:-1);if(a[n]) return put("0\n1 1\n");
    for(int i=1;i<=n;i++) if(a[i]<mn) mn=a[i],k=i;for(int i=1;i<=k;i++) s[++n]=s[i],a[i]=0;
    for(int i=k+1;i<=n;i++) if(s[i]=='(') st[++dt]=i;else nxt[st[dt--]]=i;
    for(int i=k+1;i<=n;i++) a[i]=a[i-1]+(s[i]=='('?1:-1);nxt[k]=n+1;dfs(k);ans=ss[k];L=k+1,R=k+1;
    for(int i=k+1;i<=n;i++)
        if(s[i]=='('&&a[i]==1){if(ans<ss[i]+1) ans=ss[i]+1,L=i,R=nxt[i];}
        else if(s[i]=='('&&a[i]==2){if(ans<ss[i]+ss[k]+1) ans=ss[i]+ss[k]+1,L=i,R=nxt[i];}
    print(ans);put('\n');print(L%m),put(' '),print(k==0?R:R%m),put('\n');
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

