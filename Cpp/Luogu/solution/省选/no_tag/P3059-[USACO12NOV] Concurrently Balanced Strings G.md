# [USACO12NOV] Concurrently Balanced Strings G

## 题目描述

农夫约翰养了一只非常特殊的奶牛品种，以其独特的外貌而闻名，每只奶牛的皮上都有一个巨大的圆形斑点（根据奶牛的朝向不同，这可能看起来像左括号或右括号）。

一天早上，约翰把他的奶牛们分成了 $K$ 行，每行 $N$ 头奶牛（$1 \leq K \leq 10, 1 \leq N \leq 50,000$）。由于奶牛们朝向任意方向，所以这个队列可以用 $K$ 个长度为 $N$ 的括号字符串 $S_1,..., S_k$ 来描述。约翰非常激动地注意到他的牛群中有一些“并发平衡”的范围，其中范围 $i...j$ 的奶牛只有在每个字符串 $S_1,..., S_k$ 在该范围内都是平衡的情况下才能同时平衡（我们将在下面定义单个括号字符串平衡的含义）。例如，如果 $K = 3$ ，我们有

- $S_1 = \texttt{)()((())))(())}$
- $S_2 = \texttt{()(()()()((())}$
- $S_3 = \texttt{)))(()()))(())}$

那么范围 $[3...8]$ 是并发平衡的，因为 $S_1[3...8] = \texttt{((()))}$ ，$S_2[3...8] = \texttt{()()()}$ ，$S_3[3...8] = \texttt{(()())}$ 。范围 $[10...13]$ 和 $[11...12]$ 也是并发平衡的。

给定 $K$ 个长度为 $N$ 的括号字符串，帮助约翰计算范围 $(i,j)$ 的数量，使得范围 $i...j$ 在 $K$ 个字符串中都是并发平衡的。

对于单个括号字符串的“平衡”的定义有几种方式。也许最简单的定义是括号的数量必须相等，并且对于字符串的任何前缀，左括号的数量必须至少和右括号的数量一样多。例如，以下字符串都是平衡的：

- $\texttt{()}$
- $\texttt{(())}$
- $\texttt{()(()())}$

而这些字符串则不是平衡的：

- $\texttt{)(}$
- $\texttt{())(}$
- $\texttt{((())))}$

给出 $K$ 个长度为 $N$ 的括号序列，问有多少个区间在 $K$ 个序列中对应的子串均平衡。

## 样例 #1

### 输入

```
3 14 
)()((())))(()) 
()(()()()((()) 
)))(()()))(()) 
```

### 输出

```
3 
```

# 题解

## 作者：DengDuck (赞：12)

# 前言
现在是 $2023$ 年 $7$ 月 $29$ 日凌晨 $1$ 点 $47$ 分，我听着我歌单的歌，进入了精神极其不正常的状态（正经人谁在凌晨边听摇滚边写题啊）。

所以我会胡言几句，大家请选择性忽视。

这道题是我们欢乐赛搬的，考场上用朴素的 $O(nm^2)$ 双指针水出了 $89$ 分的佳绩。

考试之后因为没有暴切十分气愤啊！所以研读了一手第一篇题解，写出了这个没什么区别但是有大区别的高级重置优秀版。
# 题目分析


## 第一次转换
括号序列的合法可以运用一个转换来判断。

把左括号变成 $1$，右括号变成 $-1$，然后求前缀和 $sum$，合法的序列 $[l,r]$ 当且仅当满足 $sum_r=sum_{l-1}$ 和 $sum_{l-1}\leq sum_{i}(i\in[l,r])$。

显然第一个条件比较好维护，第二个条件是一个类似于范围的东西，所以先处理第二个条件比较好。

那么我们怎么来找出满足这两个条件的序列呢？

我们可以枚举左端点 $l$，然后找 $r$，为什么不用 $r$ 呢？我们发现判断与前缀有关与后缀无关。

## 第二次转换

在考虑满足第二个条件之前，我们还有一个棘手的问题：

我们还要转换一下，我们发现对于 $l$ 可能有多个 $r$ 是合法的，比如 $\texttt{()()()}$ 这种括号序列。

这是怎么回事呢？我们发现 $l$ 匹配了第一个答案 $r_1$ 之后，后面可能会并列其他的括号序列，只有这种情况，这个原因很简单，不证明。

我们发现对于其他的 $r$，我们完全可以去掉 $[l,r_1]$ 这个部分，由 $r_1+1$ 开始向后匹配，方案数是从 $l$ 匹配的方案减去一（因为你不能向前匹配 $r_1$）。

收到启发我们可以求出 $r_1$ 然后从后向前求出 $f_i=f_{r_1+1}+1$。

## 第二个条件

好了，接下来考虑满足第二个条件，我们怎么求出限制范围？

我们发现说起来第一个小于本项的好像维护起来没什么头绪，但是我们仔细观察，我们会发现边界是很有特点的！

因为我们的前缀和每次不是加一就是减一，所以第一个小于本项一定为 $sum_{l-1}-1$ 啊！

那边界不就很好求了？我们考虑维护一个我们后面 $fir_x$ 表示 $sum_i=x$ 合法的一个最小的 $i$。

可以倒序去做（这道题很多倒序啊），来维护。

最后就求出了一个边界了，由于这道题字符串不唯一，所以我们要对于 $l$ 取所有字符串中的边界最小值。

## 第一个条件

第一个条件就很简单了，但是第一条不是一个告诉我们“不可以”的条件，而是让我们“怎么做”的条件，所以和第二个条件的维护略有不同。

我们求出一个最小的 $r$ 使得对于每个字符串 $sum_r=sum_{l-1}$，说白了，我们把所有字符串的前缀和摆成二维表格，我们怎么快速判断两列的信息是否相同？

相信“快速判断”“信息相同”应该可以让你快速想到哈希，我们用哈希来存储一列的信息，然后用第二个条件的方式来做。

由于值域比较大，用 `map` 维护是一个不错的选择，我们就可以找到第一个和当前列完全相同的一列。

注意我们需要和第二个条件结合，如果我们维护出的 $r_1$ 超越了边界，那么一定是无解的，因为我们这个已经是最小解了，所以我们用各种小手段阻止统计即可。

求出 $r_1$ 之后保存即可，后面倒序统计答案用。

时间复杂度懒得算，大概是 $\mathcal O(nm\log m)$ 的。

# 代码实现

注意保存 $i$ 对应的 $r_1$ 是代码的 `nxt` 数组。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL M = 15;
const LL N = 5e4 + 5;
const LL inf=1e9;
const LL mod=1e9+7;
LL n, m, sum[M][N],ans,fir[N*4],lim[N*4],nxt[N*4],hsh[N],f[N];
char s[M][N];
map<LL,LL>ma;
int main() 
{
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '(')sum[i][j] = sum[i][j - 1] + 1;
			else sum[i][j] = sum[i][j - 1] - 1;
			hsh[j]=(hsh[j]*13+sum[i][j])%mod;
		}
	}
	memset(lim,127,sizeof(lim));
	for(int i=1;i<=n;i++)
	{
		memset(fir,127,sizeof(fir));
		for(int j=m;j>=1;j--)
		{
			fir[sum[i][j]+N]=j;
			lim[j]=min(lim[j],fir[sum[i][j-1]-1+N]);
		}
	}
	for(int i=m;i>=1;i--)
	{
		nxt[i]=ma[hsh[i-1]];
		ma[hsh[i]]=i;
	}
	for(int i=m;i>=1;i--)
	{
		if(nxt[i]&&nxt[i]<lim[i])
		{
			f[i]=f[nxt[i]+1]+1;
			ans+=f[i];
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：ccsc (赞：10)

先说题意：
	
   >我们看题可知（惨不忍睹的英语），找人翻译（感谢机房最可爱的朵jm，和陪我过样例的mhy）
   
   >针对于本题，我们已知k个长度为n的括号序列，需要求出有多少个区间在k个序列中对应的子串均平衡。
   
   那么什么是均平衡？
   
   我们针对于样例进行解释：
   
   	S_1 = )()((())))(())					
    S_2 = ()(()()()((())
	S_3 = )))(()()))(())
    
    有区间【3……8】、【10……13】、【11……12】符合；why？
    
    看：
   	S_1[3...8] = ((()))
   	S_2[3...8] = ()()() 
   	S_3[3...8] = (()())
    
    所以题意应该理解了吧！
    
那么题便变得简单了起来：

我们可以这么想：

>考虑DP。
f[i]表示以ii为左端点的合法区间个数。令pos[i]表示以ii为左端点，最靠左的合法右端点。
那么有如下转移：
f[i]=f[pos[i]+1]+1.
后面的“+1”表示[i……pos[i]]这段合法区间，f[pos[i]+1]表示在这段合法区间的基础上，还可以在后面拼接更多合法区间。

>那么我们的目的就是求pos[i],
考虑一段区间为什么合法？
我们令左括号为1，右括号为-1，然后对于每一行单独求前缀和。
那么对于每行单独考虑，一个区间[l,r]需要满足2个限制：

			sum[r]−sum[l−1]=0
			区间中任意一点i满足sum[i]−sum[l−1]>=0
   
我们考虑分开处理这2个限制。
对于每个左端点i，处理出使得区间前缀为负的第一个点，那么只要右端点不超过这个点，就满足第二点限制。


对于同一列的每一行都求出这个值，然后取min，得到值t,表示第i列的右端点只要不超过t就可以对k行都满足第二点限制。


那么令这个最小的，令左端点i不满足第二点限制的右端点为lim[i]

那么继续思路：

然后从大到小枚举列i，那么我们要处理的就是第一点限制。

只需要查询最近的一个右端点满足当前列的k行与第i−1列的k行相同即可，

如果这个最近的右端点都大于等于lim[i],那么对于这个左端点就没有合法方案了。

否则我们就找到了pos[i].
   
   那么这两个东西应该如何求呢？

求lim[i]:
>先对每一行求出对应的右端点，然后取min即可，接下来讲如何对于每行求这个右端点。
如果有右端点满足使得以i为左端点的区间前缀和为负，那么肯定会有一个右端点最先满足这个东西，也就是sum[j]−sum[i−1]=−1.那么我们查询满足sum[j]=sum[i−1]−1的最小值即可。
这个我们从大到小枚举i,用minn[i]表示到当前为止，值为i的点的最小下标是多少，然后就可以直接得到了。

求pos[i]:
>用和上面类似的方法，只不过我们这次是要找一个使得k元组相等的最小j。
因为k很小，所以可以把k个值都存到map里暴力找。

code(感性理解……谢谢):
```cpp
/*
	Name: luogu P3059 [USACO12NOV]同时平衡线Concurrently Balanced Strings
	Copyright: 网络题解、ccsc
	Author: ccsc
	Date: 15-10-19 14:45
	Description: 
*/
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define ll long long
#define inf 2139062143
ll ans,f[100100];
int lim[100100],minn[100100],n,m;
char s[100100];
map <signed ll,int> M;
struct node{
    int s[12];signed ll opt;
    
    friend bool operator ==(node a,node b)
    {
        for(ri i=1;i<=m;i++)if(a.s[i]!=b.s[i]) return false;
        return true;
    }
}sum[100100];

inline void upmax(int &a,int b){if(b>a)a=b;}
inline void upmin(int &a,int b){if(b<a)a=b;}

inline int read()
{
    int x=0;
    bool f=0;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
    	if(ch=='-')f=1;
    	ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar(); 
	}
	return f?-x:x;
}
int main()
{
    m=read();
	n=read();
	for(ri i=1;i<=m;i++)
    {
        scanf("%s",s+1);
        for(ri j=1;j<=n;j++) 
            sum[j].s[i]=sum[j-1].s[i]+((s[j]==')')?-1:1);
    }
    
	for(ri i=1;i<=n;i++) lim[i]=inf;
    for(ri i=1;i<=m;i++)
    {
        memset(minn,127,sizeof(minn));
        for(ri j=n;j;j--)//对于每行的每个点找右边的，最近的，区间和为-1的点(比当前前缀小1
        {
            upmin(minn[(sum[j].s[i]+50000)],j);//先加入，防止第一个括号是右括号
            upmin(lim[j],minn[(sum[j-1].s[i]-1+50000)]);//判断[l, r]=0,需要用到sum[l - 1]和sum[r]
        }
    }
    for(ri i=1;i<=n;i++)
        for(ri j=1;j<=m;j++)
            sum[i].opt=sum[i].opt*13+sum[i].s[j];
    
	
	for(ri i=n;i;i--)
    {
        int pos=M[sum[i-1].opt];//找最小的和当前l - 1前缀相同的前缀
        if(pos&&pos<lim[i]) f[i]=f[pos+1]+1,ans+=f[i];
        if(M[sum[i].opt]) upmin(M[sum[i].opt],i);
        else M[sum[i].opt]=i;
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Eterna (赞：7)

模拟赛场切，但是我的做法怎么这么烂。

统计点对，考虑分治。每次计算考虑区间中越过中点的点对贡献。

就是要考虑怎样的两个串 $s_1,s_2$ 拼起来是一个合法串，设当前区间是 $[l,r]$，先考虑 $k=1$ 的情况：

>我们把 `(` 看作 $1$，`)` 看作 $-1$。
>
>则一个串是合法的，当且仅当其最小前缀和与最大后缀和均为 $0$。这是经典的。
>
>$s_1,s_2$ 拼起来合法，至少需要 $s_1$ 最小前缀和为 $0$，且 $s_2$ 最大后缀和为 $0$。同时，这两个字符串的和是 $0$，即左右括号数相同。
>
>但是在满足上述条件的前提下，会不会有跨过中点的前后缀导致整个串不合法呢？其实，我们发现一个跨过中点的前缀，可以用整个串剪掉一个不跨中点的后缀组成。若该后缀合法，这个跨过中点的前缀也是合法的。注意整个串和为 $0$。
>
>所以我们只用考虑 $s_1$ 的前缀与 $s_2$ 的后缀。

从中点 $\mathrm{mid}$ 向 $l$ 走，若区间 $[i,\mathrm{mid}]$ 最小前缀和为 $0$，我们将它的区间和加入 map。

然后，从中点 $\mathrm{mid}+1$ 向 $r$，若区间 $(\mathrm{mid},i]$ 最大后缀和为 $0$。将其区间和相反数在 map 的出现次数加入答案。相反数是为了保障整个的和是 $0$。

$k>1$ 的情况是类似的，就是我们需要 $k$ 个区间和都为 $0$，$k$ 个最小前缀和都为 $0$，$k$ 个最大后缀和都为 $0$。hash 一下就可以解决。

复杂度是 $\mathcal{O}(nk \log^2  n)$ 或 $\mathcal{O}(nk \log  n)$。

给一个赛时实现：


```cpp
#include<bits/stdc++.h>
#define N 50005
#define int long long
#define rd read()
#define gc getchar()
using namespace std;
inline int read()
{
	register int x=0,ss=1,s=gc;
	while(!isdigit(s)&&s!='-')s=gc;
	if(s=='-')ss=-1,s=gc;
	while(isdigit(s))x=(x<<1)+(x<<3)+(s^48),s=gc;
	return ss*x;
}
const int mod=5000100000000009ll;
int k,n,ans;
int sm[11][N],d[11],g[11];
string s;
struct node
{
	int b[11];
	inline int get()
	{
		int hs=0;
		for(int i=1;i<=k;i++)hs=(hs*247ll+b[i]*277ll+9)%mod;
		return hs;
	}
};map<int,int> mp;
vector<node> v;
inline void solve(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1;
	solve(l,mid),solve(mid+1,r);
	memset(g,0,sizeof(g));
	memset(d,0,sizeof(d));
	for(int i=mid;i>=l;i--)
	{
		for(int j=1;j<=k;j++)g[j]+=sm[j][i],d[j]+=sm[j][i],d[j]=min(d[j],0ll);
		int fl=0;node G={0,g[1],g[2],g[3],g[4],g[5],g[6],g[7],g[8],g[9],g[10]};
		for(int j=1;j<=k;j++)if(d[j])fl=1;
		if(!fl)v.push_back(G),mp[G.get()]++;
	}
	memset(g,0,sizeof(g));
	memset(d,0,sizeof(d));
	for(int i=mid+1;i<=r;i++)
	{
		for(int j=1;j<=k;j++)g[j]-=sm[j][i],d[j]+=sm[j][i],d[j]=max(d[j],0ll);
		int fl=0;node G={0,g[1],g[2],g[3],g[4],g[5],g[6],g[7],g[8],g[9],g[10]};
		for(int j=1;j<=k;j++)if(d[j])fl=1;
		if(!fl)ans+=mp[G.get()];
	}
	mp.clear();
}
signed main()
{
	k=rd,n=rd;
	for(int i=1;i<=k;i++)
	{
		cin>>s;
		for(int j=0;j<n;j++)
		{
			if(s[j]=='(')sm[i][j+1]=1;
			else sm[i][j+1]=-1;
		}
	}
	solve(1,n);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：2018ljw (赞：5)

挺神仙一道题......似乎能线性但我太菜了最后那块复杂度没压掉（不过带个小 $\log$ 依旧是最优解）

题意：给定 $k$ 个长为 $n$ 的括号序列，问有多少个区间在这 $k$ 个中对应的括号序列均合法。

首先利用栈对每个串的每个位置求出一个 $p_{i}$，表示位置 $i$ 的括号匹配成功时，另一半的括号位置。显然，对于每个能匹配的括号，$p$ 是唯一的。对于不能匹配的括号，令 $p=0$ 或 $p=n+1$ 均可。

不难发现区间 $[l,r]$ 合法的充要条件是 $k$ 个串均满足 $l\le p_{l...r}\le r$，那么对于每个位置我们实际只用维护这 $k$ 个串中的 $\max\{p\}$ 和 $\min\{p\}$ 即可，记为 $up_i$ 和 $dn_i$。

那么区间合法等价于 $l\le \min\{dn_i\}$，$\max\{up_i\}\le r$。

考虑枚举 $l$，如何确定 $r$。先不考虑 $dn$ 的限制，只关注 $up$ 的约束。由于 $\max$ 可加不可减，所以我们倒序枚举 $l$。

维护数集 $S$ 表示所有可能成为右端点的 $r$。当我们枚举到 $l$ 时，将 $l$ 加入到 $S$ 中。

设 $w_{l,r}=\max\{up_{l\dots r}\}$，当 $l$ 变成 $l-1$ 时，$w_{l-1,r}=\max\{w_{l,r},up_{l-1}\}$。那么我们需要维护 $w$ 吗？不需要。

显然当 $w_{l,r}>r$ 时，$r$ 就不可能再作为右端点出现。所以每次更新 $l$ 时，我们先将 $l$ 插入数集中，然后删去所有 $<up_l$ 的数即可。$S$ 中剩下的数即为以 $l$ 为左端点时，只考虑 $up$ 的限制，可能的右端点。由于我们插入是从大往小插的，所以使用一个栈即可维护，总复杂度 $O(n)$。

再考虑 $dn$ 的限制。

$S$ 中的元素只是可能的 $r$，但我们要找的是满足 $\min\{dn_{l\dots r}\}\ge l$ 的 $r$。关注到 $\min$ 是单调的，我们实际上只需要找到第一个 $dn<l$ 的位置。

依旧维护一个栈 $T$，每次 $l$ 变小时，先将 $l$ 压入栈中，之后不断弹出栈顶直至满足 $dn_{top}<l$。此时设 $pos=top-1$ 就是我们 $r$ 的取值上界。求解 $pos$ 的总复杂度也是 $O(n)$。

之后就是对于 $S$，查询其中有多少个数 $\le pos$ 累加进答案里。这里没想到线性的做法，但栈 $S$ 是单调递减的，直接在 $S$ 里二分位置计算即可。$S$ 栈元素一般不会很多，所以这部分 $O(n\log n)$ 但常数很小。

总结一下：
1. 第一个栈求出每个括号的匹配位 $p$，对每个位置求出 $p$ 的最大最小值。
2. 倒序枚举 $l$，第二个栈维护可能的右端点，每次删除所有 $<up_l$ 的值。
3. 第三个栈维护 $dn<l$ 的下标，每次清除栈顶不合法的元素确定右端点取值范围。
4. 根据取值范围在第二个栈里二分位置统计答案。

复杂度 $O(nk+n\log n)$。
```cpp
#include<cstdio>
#include<cstring>
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
int n,k,dn[50002],up[50002];
int stk[50001],top,s2[50001],t2;
char s[50001];
long long ans;
int main(){
	int i,j;
	scanf("%d%d",&k,&n);
	for(i=1;i<=n;i++)dn[i]=n+1;
	while(k--){
		top=0;
		scanf("%s",s+1);
		for(i=1;i<=n;i++){
			if(s[i]=='(')stk[++top]=i;
			else{
				if(!stk[top])dn[i]=0;
				else{
					int p=stk[top--];
					dn[p]=min(dn[p],i);
					up[p]=max(up[p],i);
					dn[i]=min(dn[i],p);
					up[i]=max(up[i],p);
				}
			}
		}
		while(top)up[stk[top--]]=n+1;
	}
	top=0;
	s2[++t2]=n+1;
	for(i=n;i;i--){
		stk[++top]=i;
		while(top&&stk[top]<up[i])top--;
		s2[++t2]=i;
		while(t2&&dn[s2[t2]]>=i)t2--;
		int pos=s2[t2]-1;
		int l=1,r=top,res=top+1;
		while(l<=r){
			int mid=l+r>>1;
			if(stk[mid]>pos)l=mid+1;
			else r=mid-1,res=mid;
		}
		ans+=top-res+1;
	}
	printf("%lld",ans);
}
```

---

## 作者：yhy2024 (赞：5)

%%% eterna。

经典的，对于括号序列，将左括号看作 $1$，右括号看作 $-1$，$v_i$ 为 $i$ 转换后的值。合法条件变成对，总和为 $0$，于最小前缀大于 $0$，或最大后缀小于 $0$。

考虑分治，现在做到 $[l,r]$，怎样的 $j \le mid$，能对 $i > mid$，做贡献。

记 $mx_{l,r}$ 为 $[l,r]$ 的最大后缀，$mn_{l,r}$ 为 $[l,r]$ 最小前缀。

结论：只要满足三个条件：

$$\sum_{k=j}^i v_k=0$$

$$mn_{j,mid} \ge 0$$

$$mx_{mid+1,i} \le 0$$

第一个条件不解释。对于第二、三个条件已经满足了不跨中点的情况。

以跨中点的最小前缀为例，对于任意一个前缀，可通过和减后缀表示，而后缀最大值大于 $0$，区间和为 $0$，前缀最小值一定小于 $0$，跨中点的最大后缀同理。

对于十个序列，做一个哈希即可。

时间 $O(nk \log n)$。

```cpp
#include<bits/stdc++.h>
#define rd read()
#define N 50005
#define inf LONG_LONG_MAX
#define int long long
#define md 1000000007
using namespace std;
int w[15][N],cnt,n,k;
char s[N];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
struct Node{int s[15];};
unordered_map<int,int>mp;
inline int get(Node o){
	int res=0;
	for(int i=1;i<=k;i++) res=(res*212+o.s[i])%214567454363ll;
	return res;
}
inline void solve(int l,int r){
	if(l==r) return;
	int mid=l+r>>1,i=mid,j=mid+1,mn[15],mx[15],fl;
	Node L,R;
	for(int p=1;p<=k;p++) R.s[p]=L.s[p]=mn[p]=mx[p]=0;
	solve(l,mid),solve(mid+1,r);
	for(;i>=l;i--){
		fl=1;
		for(int p=1;p<=k;p++){
			L.s[p]+=w[p][i];
			mn[p]=min(mn[p]+w[p][i],w[p][i]);
			if(mn[p]<0) fl=0;
		}
		if(fl) mp[get(L)]++;
	}
	for(;j<=r;j++){
		fl=1;
		for(int p=1;p<=k;p++){
			R.s[p]-=w[p][j];
			mx[p]=max(mx[p]+w[p][j],w[p][j]);
			if(mx[p]>0) fl=0;
		}
		if(fl) cnt+=mp[get(R)];
	}
	mp.clear();
}
signed main(){
	cout.tie(0);
	k=rd,n=rd;
	for(int i=1;i<=k;i++){
		cin>>s+1;
		for(int j=1;j<=n;j++){
			if(s[j]=='(') w[i][j]=1;
			else w[i][j]=-1;
		}
	}
	solve(1,n);
	cout<<cnt;
	return 0;
}
```

---

## 作者：lightup37 (赞：4)

## 题意

给定 $k$ 个长度为 $n$ 的括号串 $S_1, S_2\cdots S_k$，求这样的区间 $[l, r]$ 之数量，满足对于任一 $i\in[1, k], S_{i}[l .. r]$ 是合法的括号串。

## 解法

不妨考察只有一个串 $S$ 的情况将如何处理。这个问题可以通过一个栈解决：我们将每个括号依次进入栈中，弹出匹配的括号并记录。容易证明在任意一个合法的 $S$ 的子串中，每个括号所所匹配的括号不会改变。不妨记 $t_i$ 为第 $i$ 个括号所匹配的括号，那么一个区间 $[l, r]$ 合法，当且仅当对所有 $i\in[l, r]$ 都有 $a_i\in [l, r]$。

多个串的情况也是类似的，我们设 $r_i$ 是这些串 $i$ 位置上的最小 $t_i$，$p_i$ 是这些串 $i$ 位置上的最大 $t_i$。一个区间合法的条件是类似的。

所求即 $\sum\limits_{l, r} [\min\limits_{j\in[l, r]}\{t_i\}\ge l] [\max\limits_{j\in[l, r]}\{p_i\}\le r]$。

考察到固定 $l$，则使得 $\min\limits_{j\in[l, r]}\{t_i\}\ge l$ 的 $r$ 都位于一个形如 $(l, goodl_{l}]$ 的区间内。对固定的 $r$ 也有类似性质。

所求即 $\sum\limits_{l, r} [l\in [goodr_r, r)][r\in (l, goodl_l]] = \sum\limits_{l} \sum\limits_{r\le goodl_l} [l\in [goodr_r, r)]$。

线段树维护即可。

```cpp
#include <bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define uf(i,x,y) for(int i=x, i##end=y; i<i##end; ++i)
#define ll long long
#define pir pair<int, int>
#define fir first
#define sec second
#define mp make_pair
#define pb push_back
#define int ll
char ch;
int rd() {
	int f=1, x=0; ch=getchar();
	while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
	while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
#define _ 50005
int ner[15][_], ans, n, k; char str[15][_];
int r=0; pair<int, char> stk[_];

// sgt
int s[_<<2], add[_<<2];
void pushup(int p) {
	s[p] = s[p<<1] + s[p<<1|1];
}
void pushdown(int p, int l, int r) {
	if(!add[p]) return ;
	int mid = l+r>>1;
	s[p<<1] += add[p] * (mid-l+1);
	s[p<<1|1] += add[p] * (r-mid);
	add[p<<1] += add[p]; add[p<<1|1] += add[p]; add[p]=0;
}
void modify(int p, int l, int r, int ql, int qr) {
	if(ql>qr || qr == 0) return ;
	if(ql <= l && r <= qr) {
		s[p] += r-l+1; add[p] += 1; 
		return ;
	}
	pushdown(p, l, r);
	int mid=l+r>>1;
	if(ql<=mid) modify(p<<1, l, mid, ql, qr);
	if(qr>mid) modify(p<<1|1, mid+1, r, ql, qr);
	pushup(p);
}
int query(int p, int l, int r, int ql, int qr) {
	if(ql <= l && r <= qr) return s[p];
	pushdown(p, l, r);
	int mid=l+r>>1, res=0;
	if(ql<=mid) res += query(p<<1, l, mid, ql, qr);
	if(qr>mid) res += query(p<<1|1, mid+1, r, ql, qr);
	return res;
}

int mn[_][20], mx[_][20], lg2[_];
int querymn(int i, int j) {
	if(i>j) return 0x3f3f3f3f;
	int ans = lg2[j-i+1];
	return min(mn[i][ans], mn[j-(1<<ans)+1][ans]);
}
int querymx(int i, int j) {
	if(i>j) return -0x3f3f3f3f;
	int ans = lg2[j-i+1];
	return max(mx[i][ans], mx[j-(1<<ans)+1][ans]);
}
int min(int x, int y) {
	return x<y ? x : y;
} 
int max(int x, int y) {
	return x>y ? x : y;
} 
int gdr[_], gdl[_], p[_];
signed main() {
	rd(k); rd(n); f(i,0,k-1) scanf("%s", str[i]+1);
	f(j,0,k-1) {
		r=0;
		f(i,1,n) {
			if(r && stk[r].sec=='(' && str[j][i] == ')') {
				ner[j][i] = stk[r].fir; ner[j][stk[r].fir] = i; --r;
			} else {
				stk[++r] = mp(i, str[j][i]);
			}
		}
	}
	lg2[1]=0; f(i,2,n) lg2[i] = lg2[i>>1] + 1;
	memset(mn, 0x3f, sizeof(mn));
	memset(mx, -0x3f, sizeof(mx));
	f(j,0,k-1) f(i,1,n) if(ner[j][i]) mn[i][0] = min(mn[i][0], ner[j][i]); else mn[i][0] = -0x3f3f3f3f;
	f(j,0,k-1) f(i,1,n) if(ner[j][i]) mx[i][0] = max(mx[i][0], ner[j][i]); else mx[i][0] = 0x3f3f3f3f;
	f(j,1,19) for(int i=1; i+(1<<j)-1<=n; ++i) mx[i][j] = max(mx[i][j-1], mx[i+(1<<(j-1))][j-1]);
	f(j,1,19) for(int i=1; i+(1<<j)-1<=n; ++i) mn[i][j] = min(mn[i][j-1], mn[i+(1<<(j-1))][j-1]);
	f(l,1,n) {
		int r = l;
		d(j,0,19) if((r+(1<<j))<=n && querymn(l, r+(1<<j)) >= l) r += (1<<j);
		gdl[l] = r;
	}
	f(r,1,n) {
		int l = r;
		d(j,0,19) if((l-(1<<j))>=1 && querymx(l-(1<<j), r) <= r) l -= (1<<j);
		gdr[r] = l;
	}
	f(i,1,n) p[i]=i; sort(p+1, p+n+1, [](int x, int y){return gdl[x] < gdl[y];});
	int q=0;
	f(i,1,n) {
		while(q<gdl[p[i]] && q<n) { modify(1, 1, n, gdr[q+1], q+1-1); ++q; }
		ans += query(1, 1, n, p[i], p[i]);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：TonviaSzt (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P3059)

**思路分析**

转前缀和 $q$，考虑如何判断一个子串 $[l,r]$ 合法，发现一个充分非必要条件是 $q_l=q_r$，再考虑完备性，当 $(l,r)$ 中每一个 $q_i$ 均小于 $q_l$ 时完备。完备性证明显然，左括号数量始终 $\ge$ 右括号数量。

那么基本思路就有了，用 hash 记录下一个相同的 hash 值，设 $dp_i$ 表示以 $i$ 为起点的满足题意的子串数量，则有 $dp_i=dp_{nt+1}+1$，$nt$ 是 $i$ 开头最短的合法子串的右端点。

问题只剩下如何求右端点位置，根据第一段的两个需要同时成立的条件，设每一列取 hash 后的序列为 $q'$，设 $r$ 为 $l$ 向右第一个满足 $q'_l=q'_r$ 的位置，则当且仅当 $r<\min(每个串以 l 为起点向右第一个小于 q_l的位置)$ 时，$nt=r$，否则 $nt$ 不存在。

不难想到 $r$ 的求法：从右向左扫描，动态更新桶和 $r$ 序列。

那**每个串以 $l$ 为起点向右第一个小于 $q_l$ 的位置**怎么求？第一想法是树状数组或 st 表，可行。不过根据括号序列的性质，$q$ 序列在预处理过程中只存在 +1 和 -1 的情况，所以要求的这个位置 $pos$ 必满足 $q_{pos}=q_l-1$，因此用求 $r$ 的方法即可快速求 $pos$。

最后发现所有的求解都要求先知道右侧的值，所以一个循环从右向左遍历即可，码量亲和。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
int k,n,q[15][N],f[N],t,mn[15][N<<1];
char s[15][N];
map<int,int> mp;
int main(){
	scanf("%d%d",&k,&n);
	for(int i=1;i<=k;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=n;j++) q[i][j]=q[i][j-1]+(s[i][j]^')'?1:-1);
	}
	memset(mn,0x3f,sizeof(mn));
	for(int i=n+1;i;i--){
		int x=0,l=n+1;
		for(int j=1;j<=k;j++){
			mn[j][q[j][i]+N]=i;l=min(l,mn[j][q[j][i-1]+N-1]);
			x=x*131+q[j][i-1];
		}
		if(mp.count(x)&&mp[x]<=l) f[i]=f[mp[x]]+1;t+=f[i];
		mp[x]=i;
	}
	printf("%d",t);
}
```
降低码量时多了一些细节，影响不大。

---

## 作者：ZHR100102 (赞：2)

模拟赛搬的题，dp 思路很明显，但难点就在于找到要转移的点在哪。

# 暴力

首先我们可以先考虑 $k=1$ 的情况，这应该很好想，就是对于每一个右括号，找到其匹配的左括号，然后进行转移即可，这个过程可以用栈维护。

$dp_i$ 定义为以 $i$ 为结尾的合法序列个数。假设当前右括号在 $i$ 处，匹配的左括号在 $j$ 处，则：

$$dp_i=dp_{i-1}+1$$

注意**一定是要在保证能找到的情况下，转移离自己最近的左括号**，才能保证所有括号序列都被统计到了。

最后扫一遍把所有的 $dp_i$ 累加即可。这是我考场上的暴力做法。

# 正解

上面的做法，我们发现可以拓展到全局，也就是同时有 $k$ 个序列的情况。

我们考虑一个括号序列的常用 trick：**把左括号看作 $+1$，把右括号看作 $-1$，一个括号序列合法，当且仅当其总和为 $0$ 且任何一段前缀和都 $\ge 0$。**

总和为 $0$ 很好考虑，我们主要想任何一段前缀和 $\ge 0$ 怎么搞。

观察到前缀和数组每次相对前一项的变化量要么是 $1$ 要么是 $-1$，并且由于先要保证能找到，所以我们先找出可以匹配的左括号的区间左端点。

但是这样并不好做，因为如果 $[l,r]$ 的和 $<0$，$[l-1,r]$ 的和却不一定 $<0$。**所以固定右括号的方式不可行。**

**因此，我们才考虑固定左括号，去寻找右括号，并且把 dp 倒着做。**

于是找出前缀和 $<0$ 的就很简单了，对于一个左括号，其最多能匹配到的右括号一定在后面离自己最近的使前缀和 $<0$ 的地方。

这个我们可以通过从后往前扫描，记录下考虑序列第 $i$ 位到第 $n$ 位里面前缀和为每一种数的最小下标，这样我们就可以快速查询在左括号后面，第一个使前缀和 $<0$ 的右括号在哪了。

如果找不到，就说明右括号在右边的哪里都可以，所以赋为最大值。

算完最大右端点后，我们对于每一列，求出其最大右端点中的最小值，这就是某一列里可能的匹配范围。

接下来考虑总和为 $0$ 的限制，很容易发现对于前缀和数组而言是这样的：

$$f_i-f_{j-1}=0$$

可得：

$$f_{i}=f_{j-1}$$

一个括号序列合法，必须每一行都满足这个条件，也就是说对于两个列而言，每一行的前缀和相同，它才可能合法。

所以我们对每一列哈希，存进 unordered_map，然后统计**离自己最近的且在最大右端点左边的**相同位即可。

最后来个 dp 就完事了，时间是 $O(nk)$ 的，但 unordered_map 可能有点常数。

# 代码

代码还是比较好写的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
const ll eps=500005,mod=998244353;
int n,k,a[15][50005],f[15][50005],tot[15][110005],r[15][50005],pr[50005],y[50005];
ll hs[50005],dp[50005],ans;
unordered_map<ll,int>mp;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>n;
	//处理原括号序列、前缀和数组、各列的哈希值
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
		{
			char c;
			cin>>c;
			if(c=='(')a[i][j]=1;
			else a[i][j]=-1;
			f[i][j]=f[i][j-1]+a[i][j];
			hs[j]=(hs[j]*10007%mod+f[i][j])%mod;
		}
	}
	//统计右边最远可达的括号
	memset(tot,0x3f,sizeof(tot));
	memset(r,0x3f,sizeof(r));
	for(int i=1;i<=k;i++)
	{
		for(int j=n;j>=1;j--)
		{
			tot[i][f[i][j]+eps]=j;
			r[i][j]=tot[i][f[i][j-1]-1+eps];
		}
	}
	//记录对于每一列而言的右边界
	memset(pr,0x3f,sizeof(pr));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			pr[i]=min(pr[i],r[j][i]);
		}
	}
	//找出相同的哈希值
	for(int i=n;i>=1;i--)
	{
		mp[hs[i]]=i;
		y[i]=mp[hs[i-1]];
	}
	//dp
	for(int i=n;i>=1;i--)
	{
		if(y[i]!=0&&y[i]<=pr[i])
		{
			dp[i]=dp[y[i]+1]+1;
		}
	}
	//统计答案
	for(int i=1;i<=n;i++)
	{
		ans+=dp[i];
	}
	cout<<ans;
	return 0;
}
```

# 后记

后来发现也可以选择固定右括号，只要用个 ST 表然后二分就好了，时间是 $O(nk\log n)$ 的。

---

## 作者：Kelvin2009 (赞：1)

这是一道括号匹配加动态规划。

首先考虑括号匹配。一种经典的想法：令左括号表示 $1$，右括号表示 $-1$，对其进行前缀和。

该括号匹配需合法，这要求：该括号匹配中从左端点向右端点中左端点和各点围成的区间，其区间和始终非负。

对此可以维护一个 $limi_j$ 表示以 $i$ 为左端点中第一个右括号多于左括号的位置（使其后继各情况都不合法）。

由于是第一个，右括号一定恰好比左括号多一个。因此用桶从后往前记录，处理出统一的对于每行的 $limi$。

引出 DP 状态。容易发现：$k$ 行中，以 $l$ 为左端点，一定存在一个最小单位的括号序列长度使 $k$ 个子序列都是合法的（此长度可能不存在，即无法合法）。

设 $dp_i$ 表示以 $i$ 为整个括号序列左端点的合法总方案数。可以将其所在的最小单位与在它右边紧挨着的括号匹配联系起来。令其所在最小单位的右端点为 $pos_{i}$，易得：
$$dp_{i}=\lbrack pos_{i}<limi_i\rbrack\cdot(dp_{pos_{i}+1}+1)$$ 

考虑如何求 $pos_{i}$，由于 $k$ 行都得合法，对 $k$ 个相同的列位置的前缀和 $sum$ 序列做哈希。

继续从后往前桶记录。先不考虑 $limi$ 的限制，后面 DP 时再排除掉非法情况（若“最小单位”不合法，以该点为左端点不可能合法）。对于 $l$，寻找右边最小的位置，使各行该位置上的的前缀和与其 $sum_{l-1}$ 相同，使此区间内左右括号数量相等（该位置对于 $k$ 行都是统一的，因此令哈希值相同即可，对哈希值的对应位置进行记录）。


---

代码：


---


```cpp
#include<bits/stdc++.h>
using namespace std;
const int range=5e4+5;
const long long base=7;
const int lim=0x3f3f3f3f;
const long long mod1=1e9+7;
int n,k;
int pos[range];
char c[15][range];
map<long long,int>ma;
long long ans,dp[range];
int sum[15][range],nxt[range<<2],limi[range<<2];
struct hush
{
	long long hush1[range];
	hush(){memset(hush1,0ll,sizeof(hush1));}
	inline void add(int posi,int val){hush1[posi]=(hush1[posi]*base%mod1+(long long)val)%mod1;}
}hush;
int main()
{
	scanf("%d%d",&k,&n);
	for(int i=1;i<=k;i++)
	{
		scanf(" %s",(c[i]+1));
		for(int j=1;j<=n;j++) sum[i][j]=sum[i][j-1]+(c[i][j]=='('?1:-1),hush.add(j,sum[i][j]);
	}
	memset(limi,lim,sizeof(limi));
	for(int i=1;i<=k;i++)
	{
		memset(nxt,lim,sizeof(nxt));
		for(int j=n;j;j--) nxt[sum[i][j]+range]=j,limi[j]=min(limi[j],nxt[sum[i][j-1]-1+range]);
	}
	for(int i=n;i;i--) pos[i]=ma[hush.hush1[i-1]],ma[hush.hush1[i]]=i;
	for(int i=n;i;i--) if(pos[i] && pos[i]<limi[i]) dp[i]=dp[pos[i]+1]+1,ans+=dp[i];
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：odt63 (赞：1)

## 思路

一种 `vector<int>, vector<int>` 的 map 做法，代码稍长一些但是特别好想。

先考虑 $k = 1$ 时的做法，后面 $k$ 增大时在原基础上改动一点就可以了。

看到左右括号，我们容易想到遇到左括号加 $1$，右括号减 $1$，记第到 $i$ 个位置的前缀和为 $sum_i$。显然，区间 $[l,r]$ 若是合法的，必须满足以下条件：

- 左括号和右括号的数量相等。
- 在任何位置，前面的右括号个数不能超过左括号。

用数学的形式表达，就是：

- $sum_r - sum_{l-1} = 0$。
- 对于 $[l, r]$ 之间的任意一点 $i$，满足 $sum_i - sum_{l - 1} \geq 0$。

移项，得：

- $sum_r = sum_{l-1}$。
- 对于 $[l, r]$ 之间的任意一点 $i$，满足 $sum_i \geq sum_{l - 1}$。

我们分开考虑每个条件。

若假设 $l$ 为当前计算区间的左端点，那么若存在一点 $i$ 满足 $sum_i < sum_{l - 1}$ 且 $i \geq l$，那么 $i$ 以及后面的所有点和 $l$ 所构成的区间都是不合法的。那么我们找到 $l$ 右边第一个比 $sum_{l - 1}$ 小的位置 $R$（可以用单调栈预处理），那么 $R$ 以前的位置都可能合法。条件二的限制就解决了。结合条件一，我们预处理每个 $sum$ 值都出现过的坐标，用 vector 存起来排序，在 $sum_{l - 1}$ 查找 $[i, R - 1]$ 之间有几个坐标，加到答案即可。

对于增加的 $k$，$R$ 取 $k$ 个数里的最小值，由于 $k \leq 10$，我们直接把 $k$ 个 $sum$ 放到一个 vector 里并做成 map，每次用 vector 查就好了，自己想想就清楚了。

时间复杂度 $O(nk \log n)$。

## 代码

```cpp
// By 0x0F
#include <bits/stdc++.h>
// #define AT_contest
#ifdef AT_contest
#include <atcoder/all>
using namespace atcoder;
#endif

using namespace std;

// #define int long long
#define fi first
#define se second
#define pb push_back
#define sz(x) (x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define mpii map<int, int>
#define vi vector<int>
#define fr front
#define bk back
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - 48; ch = getchar();}
    return x * f;
}
#define inf 0x7fffffff
#define INF 0x3f3f3f3f3f3f3f3fll
#if defined(int)
#define RETURN_MAIN signed
#endif
#if !defined(int)
#define RETURN_MAIN int
#endif

char s[12][50010];
int sum[12][50010], rmax[12][50010];
map<vi, vi> mp;
RETURN_MAIN main() {
    int k = read(), n = read();
    for (int i = 1; i <= k; i++) scanf("%s", s[i] + 1);
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= n; j++) {
            if (s[i][j] == '(') sum[i][j] = sum[i][j - 1] + 1;
            else sum[i][j] = sum[i][j - 1] - 1;
        }
    for (int i = 1; i <= k; i++) sum[i][n + 1] = -inf;
    for (int i = 1; i <= k; i++) {
        stack<int> st; st.push(n + 1);
        for (int j = n; j >= 0; j--) {
            while (!st.empty() && sum[i][st.top()] >= sum[i][j]) st.pop();
            rmax[i][j] = st.top();
            st.push(j);
        }
    }
    for (int j = 0; j <= n; j++) {
        vi tmp;
        for (int i = 1; i <= k; i++) tmp.pb(sum[i][j]);
        mp[tmp].pb(j);
    }
    int ans = 0;
    for (int j = 1; j <= n; j++) {
        int R = inf;
        for (int i = 1; i <= k; i++) R = min(R, rmax[i][j - 1] - 1);
        // R 为能达到的最远点
        vi tmp;
        for (int i = 1; i <= k; i++) tmp.pb(sum[i][j - 1]);
        if (R <= j) continue;
        vi pos = mp[tmp];
        int vl = lower_bound(all(pos), j) - pos.begin(), 
            vr = upper_bound(all(pos), R) - pos.begin();
        ans += vr - vl;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：fight_for_humanity (赞：0)

[Better experience](https://www.cnblogs.com/fight-for-humanity/p/18357516)。


由题意可知，应当满足 $sum_{l-1} = sum_r,sum_i \le sum_r(i ∈ [l,r-1])$。

对于第二条式子，对于每个 $l$，找到第一个不满足的 $r$，就可以确定位置范围，再让第一条去限定即可。

但是对每个 $l$ 而言会有多个 $r$ 满足条件，我们发现对于满足条件的 $r1,r2$，两边是相互独立且都合法的，那么方案数就有了继承关系 $g_{r2} + 1 \to g_{r1}$。那么我们找到最左边的即可。

我们这个前缀序列的性质就是每次只会 $+1,-1$，故第一个小于 $sum$ 的位置，其值一定为 $sum-1$，那么倒着扫的同时维护即可。

对于第一条式子，应当**快速判断信息相同**，故对每列做哈希，可以使用 `map`。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod1 = 1e9 + 7, mod2 = 1e9 + 9, bas = 50000;
int n,k;
char s[50010];
int sum[15][50010];
ll hsh1[50010],hsh2[50010];
int pos[50010 << 1], lim[50010],r[50010];
ll f[50010];
struct Donny {
	size_t operator () (pair<ll, ll> donny) const {
		return donny.first * 111ll + donny.second;
	}
};
unordered_map<pair<ll, ll>, int, Donny> mp;
int main(){
	scanf("%d%d",&k,&n);
	for(int i = 1;i<=k;++i){
		scanf("%s",s+1);
		for(int j = 1;j<=n;++j){
			if(s[j] == '(')sum[i][j] = sum[i][j-1] + 1;
			else sum[i][j] = sum[i][j-1] - 1;
			hsh1[j] = (hsh1[j]*133%mod1+sum[i][j])%mod1;
			hsh2[j] = (hsh2[j]*133%mod2+sum[i][j])%mod2;
		}
	}
	memset(lim,0x3f,sizeof lim);
	for(int i = 1;i<=k;++i){
		memset(pos,0x3f,sizeof pos);
		for(int j = n;j;--j){
			pos[sum[i][j] + bas] = j;
			lim[j] = min(lim[j],pos[sum[i][j-1] - 1 + bas]);
		}
	}
	for(int i = n;i;--i){
		r[i] = mp[{hsh1[i-1],hsh2[i-1]}];
		mp[{hsh1[i],hsh2[i]}] = i;
	}
	ll ans = 0;
	for(int i = n;i;--i){
		if(r[i] && r[i] < lim[i]){
			f[i] = f[r[i]+1] + 1;
			ans += f[i];
		}
	}
	printf("%lld",ans);
	return 0;
}
```
#### 总结：
1. 看到**快速判断信息相同**，可做哈希。
1. 括号序列转前缀和的一个性质：相邻值变化为 $1$。

---

