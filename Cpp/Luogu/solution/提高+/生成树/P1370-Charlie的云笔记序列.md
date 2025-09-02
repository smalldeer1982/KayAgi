# Charlie的云笔记序列

## 题目背景

Charlie 是 oiinhand 的忠实粉丝。他有使用 oih 云笔记记录自己的题解的习惯。只有一点一滴的积累才能留下自己的足迹。

oih 云笔记有什么特点吗？

oih 的站长 soha 表示，目前 oih2 的云笔记功能比较简陋，但是正在开发 oih3 中的新版云笔记功能将是世界上最适合 oier 的储藏笔记的工具。

首先，新版云笔记支持 markdown 功能，并且可以实时预览，插入公式图片都不是问题。实时自动保存，不用担心突然断电啊文档消失，而且不管在哪里都可以看！

其次，可以一键生成题解模板摘要，不用各种复制粘贴了，超省事！

再者，云笔记可以给其他同学分享自己的笔记，共同进步。写完了笔记，还可以一键向洛谷投稿呢！

然而 Charlie 最喜欢的功能是 oih 的题目收藏。现在他收藏了一系列题目，但是觉得不过瘾所以正在玩弄这个功能。

## 题目描述

某天，Charlie 将收藏的题目抽象为一个序列。$a=[a_1,a_2,a_3,\cdots,a_{n-1},a_n]$。

设 $a[l:r]$ 表示序列 ${a_i}$ 第 $l$ 个数到第 $r$ 个数之间的子串，其中 $1 \le l \le r \le n$。形式化地，$a[l:r]={a_l,a_{l+1},a_{l+2},\cdots,a_{r-1},a_r}$。比如说，$a=[9,8,0,3,2,1]$，那么 $a[2:5]=[8,0,3,2]$。

Charlie 对序列 $[a_i]$ 定义了一个函数 $F(l,r)$，表示序列 $a[l:r]$ 的本质不同的子序列个数。特别地，一个空序列也被当作一个本质不同的子序列。

序列 $a[l:r]$ 的子序列定义为 $[a_{i_1},a_{i_2},a_{i_3},\cdots,a_{i_{k-1}},a_{i_k}]$，其中 $l \le i_1<i_2<i3<\cdots<i_{k-1}<i_k \le r$。比如说，$a=[9,8,0,3,2,1]$，那么 $[8,3,2]$ 是 $a[2:5]=[8,0,3,2]$ 的一个子序列。

长度为 $n$ 的序列 $a$ 和长度为 $m$ 的序列 $b$ 被称作本质不同的，当且仅当 $n\neq m$，或存在 $i$，使得 $a_i \neq b_i$。反之，则称这 $2$ 个序列是本质相同的。比如说，$[9,8]$ 和 $[9,7]$ 是本质不同的，$[9,8]$ 和 $[9,8,7]$ 也是本质不同的，而 $[9,8]$ 和 $[9,8]$ 是本质相同的。

举个例子，设 $a=[1,9,9,8,0,3,2,1]$，那么 $F(1,3)=6$，因为 $a[1:3]=[1,9,9]$ 有 $6$ 个子序列：$[],[1],[9],[1,9],[9,9],[1,9,9]$。

现在 Charlie 想知道，$\sum _{1\le l\le r\le n} F(l,r)$ 的值是多少。由于这个数可能很大，请输出它对 $998244353$（$7\times 17\times 2^23+1$，一个质数）取模后的结果。

## 说明/提示

- 对于 $10\%$ 的数据，$1\le n \le 10$；
- 对于 $30\%$ 的数据，$1 \le n \le 100$；
- 对于 $50\%$ 的数据，$1\le n \le 1000$，$0 \le a_i \le 10^5$；
- 对于 $100\%$ 的数据，$1 \le n \le 10^5$，$|a_i| \le 10^9$。

oiinhand 3.0 正在开发中。

这将是 oiers 都需要的工具，它不仅集合了全网所有大型 OJ 的资源（题目、题解）而且针对用户还可以将自己在其他 OJ 评测过的代码储存下来，并且有超贴心的云笔记功能，帮助大家最大效率练习。

soha 借此地征求意见，有奖哦！<http://www.wenjuan.com/s/M7fqIv/>

## 样例 #1

### 输入

```
8
1 9 9 8 0 3 2 1```

### 输出

```
814```

# 题解

## 作者：Amphetamine (赞：22)

这题好难啊。。如果没有一个题解真的不好做。


首先要统计所有F(l,r)

设dp[i]为F[i,i],F[i,i+1],F[i,i+2].....F[i,n]的和

显然如果没有重复的数字的话,dp[i]=dp[i+1]\*2+2;

很好理解，就是在F[i+1,i+1],F[i+1,i+2].....F[i+1,n]的前面填上或不填ai。再加上F[i,i]=2

然后就到了去重部分

若ai==aj(i<j)

则dp[i]-=dp[j+1]+1;

原因是 后面所有的F[j+1,j+1].....都会有一次重复(接ai,接aj)

而前面的F[i,j]也会有一次重复(只有ai或只有aj)

所以dp方程就出来了

dp[i]=dp[i+1]\*2+2;

dp[i]-=dp[j+1]+1;（ai==aj）

...
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
#ifdef ONLINE_JUDGE
char *TT,*mo,but[(1<<15)+2];
#define getchar() ((TT==mo&&(mo=(TT=but)+fread(but,1,1<<15,stdin)),TT==mo)?0:*TT++)
#endif
inline int read(){
    int x=0,c=0,f=1;
    for(;c<'0'||c>'9';c=getchar())f=c!='-';
    for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
    return f?x:-x;
}
int head[100010];
int a[100010],b[100010];
ll dp[100010];
ll ans;
int n;
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        b[i]=a[i];
    } 
    sort(b+1,b+n+1);
    int cnt=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
    dp[n]=2;
    head[a[n]]=n;
    for(int i=n-1;i>0;i--){
        dp[i]=(dp[i+1]*2+2)%mod;
        if(head[a[i]]){
            dp[i]=(dp[i]-dp[head[a[i]]+1]+mod-1)%mod;
            head[a[i]]=i;
        }
        head[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        ans=(ans+dp[i])%mod;
    }
    cout<<ans;
    return 0;
}
```
...

---

## 作者：kkksc03 (赞：22)

1 题⽬⼤意

令 F ( l , r )表⽰序列 a [ l : r ]的本质不同的⼦序列个数，求 ∑F ( l , r )，1 ≤ l ≤ r ≤ n


2 关键词

递推 动态规划

3 简要算法

考虑单独求 F ( l , r )，使⽤动态规划。

令 dp [ i ]表⽰ F ( l , i ) − 1的值（即不包含空序列）。那么状态转移⽅程为

dp [ i ] = ( dp [ i − 1] + 1) ∗ 2 − ( last [ a [ i ]]?0 : dp [ last [ a [ i ]] − 1] + 1) − 1

其中 last [ i ]表⽰值 a [ i ]上⼀次出现的位置。

那么考虑求 ∑F ( l , r )，1 ≤ l ≤ r ≤ n，同样使⽤动态规划。


改变 dp [ i ]的含义，令 dp [ i ]表⽰以 i为右端点时的⾮空的本质不同的⼦序列的数

量。沿⽤单独求 F ( l , r )的思路，状态转移⽅程为


dp [ i ] = i +∑dp [ j ] − sum [ a [ i ]]，j=1 to i-1

sum [ i ] =∑[ a [ j ] = a [ i ]] ∗ dp [ j ]，j=1 to i-1

其中 [ p ]表⽰ p为 tr ue时值为1， p为 f al se时值为0。

那么答案就是∑( dp [ i ] + 1) ∗ ( n − i + 1)。i=1 to n


---

## 作者：CaiXY06 (赞：8)

## 题意

求

$$\sum \limits_{l=1}^{n}\sum \limits_{r=l}^{n} F_{l,r}$$

$F_{l,r}$ 为序列 $a_i(l\leq i\leq r)$ 中本质不同的子串个数。

## Solution

很显然的一个动态规划吧。

我们设状态 $f_i$ 表示 $\sum \limits_{j=1}^{i} F_{j,i}$ 。

那么就有转移方程 $f_i=f_{i-1}\times 2^1+F_{i,i}$

也就是之前所有方案中出现的子串的最后是否出现 $a_i$ ，加上自己单个元素可有可无的贡献。

$F_{i,i}$ 显然就是 $2$ 。

但是你会发现，这样写连样例都过不了。

为啥呢？因为可能会有元素重复，导致某一部分的 $F_{l,r}$ 被计算两遍。

这时我们就应该再把这一部分消去，得

$$f_i=f_{i-1}\times 2^1-f_{j-1}+1(a_i=a_j)$$

其他大佬都用 **unique** 去重排序离散化，将 $a_i$ 的权值修改为在序列中的 **rank** ，但本蒟蒻不会用，所以我采用更加暴力朴素的方法，直接用一个 **map** 存储上一个 $a_j(a_i=a_j)$ 出现的位置。

虽然常数增大，但是仍然能过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,a[100010],f[100010],ans;
map<int,int>last;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		f[i]=((f[i-1]<<1)+2)%mod;
		if(last[a[i]])f[i]=(f[i]-(f[last[a[i]]-1]+1)+mod)%mod;
		last[a[i]]=i;
	}
	for(int i=1;i<=n;i++)ans=(ans+f[i])%mod;
	printf("%lld",ans);
	return 0;
}
```
在使用 **C++11** 的 **unordered_map** 和吸氧之后，成功获得了最优解！！

---

## 作者：Isshiki·Iroha (赞：5)

## 题解

### 前言

[博客](https://www.luogu.com.cn/blog/yousa22/solution-p1370)

[题目](https://www.luogu.com.cn/problem/P1370)

这其实是一道非常好的题，但是感觉题解没有那么详细，~~我每写一步都有一个新的问题~~。所以我特意写一篇题解来帮助大家。

### 正题

首先看要求什么

$$\sum_{l=1}^n\sum_{r=l}^nF(l,r)$$

我们发现就算能 $\text{O}(1)$ 求出每个值也会超时，其实有很多这样的题目，就是求每一个区间的值的和，因为我们并不关心每一个的区间的值，所以我们可以把一些区间绑起来一起算，一般是固定左或者右端点，具体看题目性质，我们为什么要这样做？就是因为我们希望通过一个较低的复杂度一次性推出一些区间的值的和。

比如这个题，可以令 $dp_l=\sum_{r=l}^nF(l,r)$，因为我们注意到如果 $l<l'$，那么计算 $l$ 为开头的值是必须会把后面的，也就是包含了 $l'$ 的值 ，那么答案就是 $\sum_{i=1}^ndp_i$，我们再来看怎么转移，比起一多很多个数加入，我们肯定希望每次只需要多算一个数的贡献，所以每一次从他右边一个来推出。

假设当前我们算到了 $i$，这个时候有两种情况：

> **1.** $i$ 右边的数字都不与 $a_i$ 相等，那么对于所有的 $F(i,r)$ 他们的值就是 $F(i+1,r) \times 2$，因为 $a_i$ 可以选或者不选，然后注意 $F(i,i)=2$（选自己和空），发现对于除了 $F(i,i)$，剩下的就是 $\sum_{l=i+1}^n F(l,r) \times 2 = dp_{i+1} \times 2$，那么总的就是 

> $$dp_i=dp_{i+1} \times 2 +2$$

> **2.**  $a_i$ 与后面的有相同，我们先从最简单的开始。

>> 1. **除了值为 $a_i$ 其他都不重复而且只有一个与 $a_i$ 相等（不妨设这里为 $j$）**，那么我们发现，只有在选了 $a_i$ 和选了 $j+1$ 后面的数组成的序列会和 $a_j$ 和后面的数组成的序列相同，或者就是 $i$ 和 $j$ 相同，那么重复的方案数其实就是 $dp_{j+1}+1$，**我们就可以看做是减去了 $a_j$ 为开头的那一部分**。


>> 2. **除了值为 $a_i$ 其他都不重复但是值为 $a_i$ 的会有多个**，这个时候就有人（其实只有我）不知道 $a_i$ 是应该只算离他最近的还是都算了，我们注意到，如果选了 $i$ 和 选了 $j\ (a_i= a_j)$ 的序列要一样，那么 $j$ 前面的等于 $a_i$ 的就不应该选， 其实这也等价于 $j$ 前面等于 $a_i$ 的选了，后面等于的不选（设为下标 $k$），然后随机选后面的数字（$>k$），因为数值都一样嘛。那么对于所有的 $j ,a_j=a_i$ 其实都可以把他的答案等价到离 $i$ 最近的那个 $j$ 上面，而且 $dp_{j+1}$ 本身就包含了这些答案 ，所以 2.1 提到的方程仍然使用。


>> 3. **题目要求，无特殊限制**，这时候可能就有人问，啊，你之前计算重复的都没有包括 $i,j$ 之间的数，如果是类似于 $2,\ldots,3,\ldots,2,\ldots,3,\ldots$ 怎么办？其实这在计算 $3$ 的时候就已经去掉了后面那个 $3$ 的答案了，之后的转移就相当于只有一个，然后再对 $2$ 的去重的时候中间的数字没有计算，所以不会有重复减少的情况了，2.1 的方程仍然使用

我们记录下来最左边值的为 $i$ 的下标 $Lst_i$，当然这一步需要离散化后计算，不然爆空间，则总方程是，注意加上模数防止爆负：

$$dp_i=(dp_{i+1}\times 2 +2 -dp_{Lst_{a_i}}-1+Mod)\%Mod$$

$$Lst_{a_i}=i$$

时间复杂度：离散化 $\text{O}(n \log n)$，Dp $\text{O}(n)$

代码：

（前面有一坨很大的模板不放上来了，$100\%$ 原创，[Template](https://www.luogu.com.cn/paste/3swxk4ey)）

```cpp
//Template By (HMS_Cheshire)小柴郡喵喵喵
#include<bits/stdc++.h>
using namespace std;
using lll = __int128;
using ll = long long;
const int maxn=1e5+10;
const ll Mod=998244353;
int n;
vector<int>a,Lst;
vector<ll>dp;
int main(){
	read(n);
	a.resize(n+1);
	dp.resize(n+2);
	Lst.resize(n+1);
	for(int i(1);i<=n;++i)read(a[i]);
	vector<int>Rank=Saratoga::Discretization(a.begin()+1,a.begin()+1+n,[](int A,int B){
		return A<B;	
	});
	for(int i(1);i<=n;++i)a[i]=Rank[i];
	for(int i(n);i>=1;--i){
		dp[i]=(dp[i+1]*2+2)%Mod;
		if(Lst[a[i]])dp[i]=(dp[i]-dp[Lst[a[i]]+1]-1+Mod)%Mod;
		Lst[a[i]]=i;
	}
	ll ans=0;
	for(int i(1);i<=n;++i){
		ans=(ans+dp[i])%Mod;
	}
	write(ans);
	return 0;
}
```



---

## 作者：沙鵖之祖 (赞：4)

~~说在前面：这题的题面如果不恶心的话还是正常的~~

题意概括：求一个串中**所有子串**的**所有本质不同子序列** 的数量和(断句十分清晰，确信)

用 dp 来做（废话）。

  蒟蒻先考虑用 $O(n^2)$ 的 dp 做，设是以 $i$ 为开头，以 $x(x\leqslant j)$ 为结尾的**所有本质不同子序列**的数量和。
  
考虑枚举 $i$,我们要求出每个 $f[i][j]$,怎么求呢，我们拿样例举个例子:

$1\: 9\: 9\: 8\: 0\: 3\: 2\: 1$

$i$ 最开始是 1 ，首先，$f[1][0]=1$(因为空序列也算,$f[1][0]$ 的序列集合为 $\left \{  \right\}$ )。

接下来是 $f[1][1]$,我们考虑加一个数字会使 $f$ 发生什么变化，我们发现，原来的 $f[1][0]$ 只有一个可行空序列，那么我们唯一一个可以新增的答案便是在空序列后加上一个 $a[1]$,由此可得，$f[1][1]=f[1][0]+f[1][0]=2$（原来的 $\left \{  \right\}$ 与新增的 $\left \{1  \right\}$ ）。

$f[1][2]$ 中，因为 $f[1][1]$ 中包含两个子序列（$\left \{  \right\}$,$\left \{1  \right\}$），我们便可以分别在其后加入 $a[2]=9 $,所以 $f[1][2]=f[1][1]+f[1][1]=4$（原来的 $\left \{  \right\}$,$\left \{1  \right\}$ 与新增的 $\left \{9  \right\}$,$\left \{1,9  \right\}$ ）。

$f[1][3]$ 点不一样了。

根据刚才的规律，我们可以在 $f[1][2]$ 的四个后面分别加入 $a[3]=9$,但是！！！假设我们真这么做了，我们得到的 $f[1][3]$ 的子序列集合将会由 $f[1][2] $中的 $\left \{  \right\}$,$\left \{1  \right\}$,$\left \{9  \right\}$,$\left \{1,9  \right\}$ 和新增的 $\left \{9  \right\}$,$\left \{1,9  \right\}$,$\left \{9,9  \right\}$,$\left \{1,9,9  \right\}$ 组成,发现了吗，在原来的与新增的集合中,$\left \{9  \right\}$,$\left \{1,9  \right\}$ **是重复了的**！

怎么办呢？

我们仔细研究一下为什么会这样，就能轻易得出结论：由于之前出现过一个 9,所以在 $\left \{  \right\}$ 与 $\left \{1  \right\}$ 这两个之后加 9 出现了两个选择：既可以加上 $a[2]$ ，也可以加上 $a[3]$ ！

由此，我们发现，**凡是在某个序列之后存在两个相同数字的时候，我们只会选取相同数字中第一个出现的计入答案**。

相应的，我们对于每个 $f[i][j]$ ,我们就要检查一下 $a[j]$ 的数值是否曾经出现过，我们设该数字在 $j$ 之前出现的最大坐标为 $bef[j]$,那么，凡是在 $bef[j]$ 之前结尾的子序列，它之后就肯定会优先加入 $a[bef[j]]$,而不是 $a[j]$，所以我们只能在以 $x(bef[j] \leqslant x<j)$ 结尾的子序列中计算贡献。

还记得我们对于 $f[i][j]$ 的定义吗？以 $i$ 为开头，以 $x(x \leqslant j)$ 为结尾的所有本质不同子序列的数量和，它本身就是一个**前缀和**！可以通过它来轻松计算每个 $f[i][j]$ 新增的答案：

$f[i][j]$ 新增的答案是 $f[i][j-1]-f[i][bef[j]-1]$。

所以 $f[i][j]=f[i][j-1]+f[i][j-1]-f[i][bef[j]-1]$。

答案怎么统计呢?首先我们发现用 $f[i][j]-f[i][j-1]$ 便可以得到以 $i$ 起始，以 $j$ 结束的可行子序列总数，它对答案的贡献应当**乘上** $(n-j+1)$ (由于我们已经锁定了有i开头，所以我们只考虑它会对 $(i,j)$ 到 $(i,n)$ 的子串的贡献)。

因为 $bef$ 可以预处理，我们便可以在的 $O(n^2)$ 时间复杂度中做完。

附：**空序列**的计数比较特殊，所以我放在最后统计了，因为每个字串都有空序列，所以空序列的贡献是 $ {\textstyle \sum_{i=1}^{n}}i $ ，即 $\frac{n(n+1)}{2}$。

附上代码 1：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e3+7,mod=998244353;
int f[N][N],ans,n,bef[N];
//bef代表在该点坐标之前，且距离该点坐标最近的点的坐标（如果不存在，坐标为0）
struct sequence{
	int a,pos;
	//a是该点的值，pos是该点在序列中的位置
}e[N];//处理bef数组用的

int read(){
	int x=0,s=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') s=-1;
		c=getchar();
	}while(c>='0'&&c<='9')
		x=x*10+c-'0',
		c=getchar();
	return x*s;
}

bool cmp(sequence x,sequence y){
	if(x.a!=y.a) return x.a<y.a;
	else return x.pos<y.pos;
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		e[i].a=read(),e[i].pos=i;
	sort(e+1,e+n+1,cmp);
	e[0].a=-mod;
	for(int i=1;i<=n;i++){
		if(e[i].a==e[i-1].a)
			bef[e[i].pos]=e[i-1].pos;
		else bef[e[i].pos]=0;
	}//输入数据并通过离散化计算出bef
	for(int i=1;i<=n;i++){
		f[i][i-1]=1;
		for(int j=i;j<=n;j++){
			f[i][j]=(f[i][j-1]+f[i][j-1]-f[i][bef[j]-1]+mod)%mod;
		}
	}for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			ans=(ans+(f[i][j]-f[i][j-1]+mod)*(n-j+1)%mod)%mod;
		}
	}printf("%lld",(ans+n*(n+1)/2)%mod);
	return 0;
}

```

然后我自闭了，丫的不知道怎么优化到 $O(n)$ 哪！！！

无奈之下，我开始**优化空间**，观察这一段：

```cpp
	for(int i=1;i<=n;i++){
		f[i][i-1]=1;
		for(int j=i;j<=n;j++){
			f[i][j]=(f[i][j-1]+f[i][j-1]-f[i][bef[j]-1]+mod)%mod;
		}
	}for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			ans=(ans+(f[i][j]-f[i][j-1]+mod)*(n-j+1)%mod)%mod;
		}
	}printf("%lld",(ans+n*(n+1)/2)%mod);
```

 
很明显，二维的 $f$ 明显不优，所以我们把 $i$ 去掉，每次枚举 $i$ 时进行**初始化**，并且把计算 $ans$ 合并到处理 $f$ 的步骤中，就可以优化到一维。

贴上空间优化后的核心代码：
```cpp
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++) f[j]=0;
		f[i-1]=1;
		for(int j=i;j<=n;j++){
			f[j]=(f[j-1]+f[j-1]-f[bef[j]-1]+mod)%mod;
			ans=(ans+(f[j]-f[j-1]+mod)*(n-j+1)%mod)%mod;
		}
	}printf("%lld",(ans+n*(n+1)/2)%mod);

```

然后我又自闭了。

我真傻，真的，我原以为对于每个 $i$ 都要进行枚举。

但是！！！每次枚举i时的初始化起始就是清空 $f$ 并且将 $f[i-1]$ 设为 1,所以我们可以将**每次枚举的初始化合并**！没错，我们可以一开始就将 $f[0]$（即 $f[1-1]$）到 $f[n-1]$ 同时设为1,然后一波带走就完啦！

时间复杂度 $O(n)$。

附上完整代码（细节看注释）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e5+7,mod=998244353;
int f[N],ans,n,bef[N];
//bef代表在该点坐标之前，且距离该点坐标最近的点的坐标（如果不存在，坐标为0）
struct sequence{
	int a,pos;
	//a是该点的值，pos是该点在序列中的位置
}e[N];//处理bef数组用的

int read(){
	int x=0,s=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') s=-1;
		c=getchar();
	}while(c>='0'&&c<='9')
		x=x*10+c-'0',
		c=getchar();
	return x*s;
}

bool cmp(sequence x,sequence y){
	if(x.a!=y.a) return x.a<y.a;
	else return x.pos<y.pos;
}

signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		e[i].a=read(),e[i].pos=i;
	sort(e+1,e+n+1,cmp);
	e[0].a=-mod;
	for(int i=1;i<=n;i++){
		if(e[i].a==e[i-1].a)
			bef[e[i].pos]=e[i-1].pos;
		else bef[e[i].pos]=0;
	}//输入数据并通过离散化计算出bef
	for(int i=0;i<=n;i++) f[i]=1;
	for(int i=1;i<=n;i++){
		f[i]=(f[i]+f[i-1]+f[i-1]-f[bef[i]-1]+mod)%mod;
		//注意！！！因为时间优化后我们的f提前被赋了值，所以我们处理f[i]时要事先加上f[i]
		ans=(ans+(f[i]-f[i-1]+mod)*(n-i+1)%mod)%mod;
	}printf("%lld",ans%mod);
	//同时，因为f被提前赋值，导致空序列被提前处理，最后可以不加(n+1)*n/2了
	return 0;
}

```

这篇题解写的很详细了，还有不懂的，请私信哦。

又：点个赞再走吧～





---

## 作者：Sweetie_Liu (赞：4)

# P1370 Charlie的云笔记序列
## 免责声明，以下纯属个人见解，如有不同欢迎私信。
### [题面](https://www.luogu.org/problem/P1370)
题面真的是干净的不行啊，设$f_{i,j}$为$i$到$j$本质不同的子序列个数，求$\sum_{1<=l<=r<=n}f_{i,j}$

首先我们想$f_{1,i}$如何求。我们考虑$f_{i-1}$和$f_{i}$的关系，我们新加入一个数，肯定会与之前已有的子序列和在一起变成新的子序列，然后继承之前的子序列，再加上$a_i$本身为一个新的子序列，我们的转移就是$f_{i} = 2f_{i-1}+1$,最后我们没有计算空序列，在$ans$后$+1$就好。

**但这样转移显然是有重复的，我们考虑如何去重，对于一对数$i<=j$且$a_i=a_j$时我们就会出现重复，对于$f_{j-1}$，它对$i$的贡献和对$j$的贡献时完全重复的，因为我们的$a_i=a_j$加上$j$之前的任何一个子序列，他们都是完全一样的，所以我们设$pre$为$i$之前最后一个等于$a_i$的位置**

我们完整的转移方程就会变成$f_{i} = 2f_{i-1}+1-pre?f_{pre-1}+1:0$

***但是这好像和我们要求的数相差甚远呢***

那我们就在其中加入0这个神仙东西，就可以解决神仙问题，我们可以把问题拆解成$ans=\sum_{i=1}^n\sum_{j=1}^{i}f_{j,i}$我们考虑求，$\sum_{j=1}^if_{j,i}$,我们设$g_i = \sum_{j=1}^if_{j.i}$，我们考虑类比上面的式子进行一顿操作$g_i = 2g_{i-1}+2-pre?g_{pre-1}+1:0$注意到我们这里时加上0，仔细考虑之后，我们如果根据定义去推式子，我们就能得到像楼下**kkk站长大人**的式子，我们结合对比之后，发现以上的递推式是通过算入0来达到直接从$2g_i$来转移，也就不用去乘上$(n-i+1)$这个系数。

***Code***

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = (int)1e5+10;
const int MOD = 998244353;
int n,len,a[MAXN],b[MAXN],f[MAXN],pre[MAXN];
int read(){
	int w=1,x=0,ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')w=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
	return x*w;
}
void discrete(){
	sort(b+1,b+1+n);
	len = unique(b+1,b+1+n) - b - 1;
	for(int i=1;i<=n;i++){
		a[i] = lower_bound(b+1,b+1+len,a[i]) - b;
	}
}
void Init(){
	n = read();
	for(int i=1;i<=n;i++)a[i] = read(),b[i] = a[i];
}
void Dp(){
	for(int i=1;i<=n;i++){
		f[i] = (2*f[i-1]%MOD+2)%MOD;
		if(pre[a[i]])f[i] = (f[i]-f[pre[a[i]]-1]-1+MOD)%MOD;
		pre[a[i]] = i; 
	}
	int ans = 0;
	for(int i=1;i<=n;i++)ans = (ans+f[i])%MOD;
	printf("%d\n",ans);
}
int main() {
	Init();
	discrete();
	Dp();
	return 0;
}
```

---

## 作者：Exber (赞：2)

## 做法

离散化 + dp。

考虑设状态 $dp_i=\sum\limits_{j=1}^i\operatorname{F}_{i,j}$，那么如果不需要去重的话，因为前面的每个子序列都可以接上或者不接上 $a_i$，$a_i$ 也可以自立门户（$\{a_i\}$ 和 $\varnothing$），所以：

$$dp_i=dp_{i-1}\times 2+2$$

但是题目要求本质不同的子序列的个数，所以要去重。考虑一个满足 $a_k=a_i$ 且 $k<i$ 的最大的 $k$，很明显**所有最后接上 $a_k$ 的子序列都算重了**，而最后接上 $a_k$ 的子序列有 $dp_{k-1}+1$ 个（即 $k$ 前面的和 $a_k$ 自己），所以转移方程为：

$$dp_i=dp_{i-1}\times 2+2-(dp_{k-1}+1)$$

其中 $k$ 为满足 $a_k=a_i$ 且 $k<i$ 的最大的整数，如果没有满足条件的 $k$，那么 $dp_{k-1}+1=0$。

那么实现起来也十分容易，首先离散化一下，然后用 $lst_w$ 存储最后一个 $w$ 的出现位置，然后转移即可。

最终答案为 $\sum\limits_{i=1}^ndp_i$，记得取模。

## AC 代码

```cpp
#include <iostream>
#include <algorithm> 
#include <cstdio>

using namespace std;

const long long mod=998244353;

int n,a[100005];
int b[100005],lst[100005];
long long dp[100005];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1); // 离散化
	for(int i=1;i<=n;i++)
	{
		a[i]=lower_bound(b+1,b+n+1,a[i])-b; // 离散化
	}
	for(int i=1;i<=n;i++)
	{
		dp[i]=((dp[i-1]*2+2-(lst[a[i]]>0?dp[lst[a[i]]-1]+1:0))%mod+mod)%mod; // 转移，因为有减法，所以需要 (%mod+mod)%mod
		lst[a[i]]=i; // 最后更新 lst
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=(ans+dp[i])%mod; // 计算答案，记得取模
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：1)

~~这个网站下次一定去！~~

------------
注：本题仅涉及到计数 DP 以及一系列基础知识点，因此作者不会详细赘述证明和原理，望周知！

------------
## 大致思路：
题目大意：给你一个序列，求出**它所有区间的本质不同的子序列个数**。（空序列也算作本质不同），数据范围 $n \le 10^5$。

首先，我们要明白一个事情：**不能光看题面的复杂还简单就马上决定用暴力**。尽管这道题确实看起来“很基础”（想清楚思路之后确实比较简单），但我们仍然要注意到它那可怕的 $n \le 10^5$ 的数据范围，因此，我们能忍受的时间复杂度只有 $O(n)$ 或者更好点就是 $O(\log(n))$。

接着，我们发现，这道题可以用 DP 来实现，所以我们先设计状态：**设 $dp_i$ 表示 $i$ 到 $n$（即后缀）所有可能的子序列的个数和**。那么很显然：$dp_n = 2$。因为这时只有最后一个元素和空序列符合条件了。知道了临界值，我们再根据 DP 的子问题重叠性的性质，可以很快推出转移方程：

$dp_i = dp_{i+1} \times2 + 2$。

说白了就是在 $(i+1,i+1)$，$(i+1,i+2)$，$(i+1,i+3)$ 一直到 $(i+1,n)$ 的前面加上或不加 $a_i$。再加上 $(i,i)$，它的值也就是 $2$。

之后考虑去重。如果 $a_i = a_j$，那么对于很多子序列都是会有重复的，于是我们需要减去 $dp[j]+1$（加 $1$ 是 $i$ 自身）。我们还要考虑一个问题：既然我们知道存在 $a_i = a_j$ 的情况，那我们怎么找到这个 $j$ 呢？对于如何找 $j$ 的位置，我们可以用一个 $nxt$ 数组来记录离当前最近的 $a_i$ 出现的位置。每次更新。因为 $a_i$ 范围到了 $10^8$，考虑离散化，。

最后在码代码时要注意一件事：**一定要记得取模**！！！

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 1e5 + 5;
const int mod = 998244353;
int n, cnt;
int a[N], aa[N], nxt[N];
int ans, dp[N];
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        aa[i] = a[i];
    }
    sort(aa + 1, aa + 1 + n);
    int cnt = unique(aa + 1, aa + 1 + n) - (aa + 1);
    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(aa + 1, aa + cnt + 1, a[i]) - aa;
    }
    dp[n] = 2;
    nxt[a[n]] = n;
    for (int i = n - 1; i >= 1; i--)
    {
        (dp[i] = dp[i + 1] * 2 + 2) %= mod;
        if (nxt[a[i]])
        {
            int pos = nxt[a[i]];
            dp[i] = (dp[i] - dp[pos + 1] - 1 + mod) % mod;
        }
        nxt[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        (ans += dp[i]) %= mod;
    }
    cout << ans << endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122706426)

[参考文献](https://www.cnblogs.com/nopartyfoucaodong/p/9787033.html)

---

## 作者：sigongzi (赞：1)

感觉不难，就不往自己的博客发了，留到洛谷上吧。。

首先呢可以用一个map求出来

**每个点到在它之前且离它最近的相同的数的距离**

这样做是为了求出可以用的左端点

例如样例是1 9 9 8 0 3 2 1

那么如果左端点在1和2，那么第三个9肯定不会当做序列开头被计入的，所以我们求出的这个数可以被作为开头计入的左端点数目应该是（样例）

1 2 1 4 5 6 7 7

考虑一下，求一个序列的互不重复的子序列，计算以每个位置开头的互不相同的子序列有多少个，假如后面有两个相同字符，我要从最近的那个转移过来

那么后面的思路就很明确了，从后往前遍历序列，再用一个map求出以每种值的数为开头的方案数，并且每个方案乘上后面可用的右端点

比如样例统计3 2这个子序列时，乘了2

具体操作就是加上一个点作为末尾的时候加上$n - i + 1$，再用一个外部变量记录map里面的总和

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define space putchar(' ')
#define enter putchar('\n')
#define eps 1e-10
#define ba 47
#define MAXN 100005
//#define ivorysi
using namespace std;
typedef long long int64;
typedef unsigned int u32;
typedef double db;
template<class T>
void read(T &res) {
    res = 0;T f = 1;char c = getchar();
    while(c < '0' || c > '9') {
	if(c == '-') f = -1;
	c = getchar();
    }
    while(c >= '0' && c <= '9') {
	res = res * 10 +c - '0';
	c = getchar();
    }
    res *= f;
}
template<class T>
void out(T x) {
    if(x < 0) {x = -x;putchar('-');}
    if(x >= 10) {
	out(x / 10);
    }
    putchar('0' + x % 10);
}
const int MOD = 998244353;
int N,a[MAXN],pre[MAXN],sum;
map<int,int> zz;
int inc(int a,int b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}
int mul(int a,int b) {
    return 1LL * a * b % MOD;
}
void update(int &x,int y) {
    x = inc(x,y);
}
void Solve() {
    read(N);
    for(int i = 1 ; i <= N ; ++i) read(a[i]);
    for(int i = 1 ; i <= N ; ++i) {
	pre[i] = i - zz[a[i]];
	zz[a[i]] = i;
    }
    zz.clear();
    int ans = 0;
    for(int i = N ; i >= 1 ; --i) {
	int t = inc(sum,(N - i + 1));
	update(sum,MOD - zz[a[i]]);
	update(sum,t);
	zz[a[i]] = t;
	update(ans,mul(pre[i],t));
    }
    update(ans,(1LL * N * (N - 1) / 2 + N) % MOD);
    out(ans);enter;
}
int main(){
#ifdef ivorysi
    freopen("f1.in","r",stdin);
#endif
    Solve();
}
```

---

