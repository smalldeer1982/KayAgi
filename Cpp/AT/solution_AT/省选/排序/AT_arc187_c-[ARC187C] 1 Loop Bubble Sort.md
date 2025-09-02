# [ARC187C] 1 Loop Bubble Sort

## 题目描述

对于长度为 $N$ 的排列 $P$，定义一次操作如下：

- 枚举正整数 $i \in [1,n)$，若 $P_i>P_{i+1}$，则交换 $P_i$ 和 $P_{i+1}$。

现在告诉你对 $P$ 执行一次操作之后的序列 $Q$。

若 $Q_i \not =-1$ 则操作之后的序列的第 $i$ 个数等于 $Q_i$；否则，$Q_i$ 可以取任意数。

求排列 $P$ 的数量，对 $998244353$ 取模。

## 说明/提示

$N \leq 5000$，$Q$ 中每种非 $-1$ 的数最多出现一次。

## 样例 #1

### 输入

```
4
-1 -1 2 4```

### 输出

```
6```

## 样例 #2

### 输入

```
6
-1 -1 -1 -1 2 -1```

### 输出

```
120```

## 样例 #3

### 输入

```
15
-1 -1 -1 -1 -1 4 -1 -1 -1 -1 7 -1 -1 -1 -1```

### 输出

```
237554682```

# 题解

## 作者：是青白呀 (赞：11)

首先一个经典的结论是：一轮冒泡排序做的事，实际上是将序列按照每一个前缀最大值划分成若干个区间，并将每个区间的最大值（初始时在最前面）循环移位至区间末尾。

考虑记录前缀最大值进行 dp。我们预处理 $pos_i$ 表示 $Q$ 中值的位置，不存在则值为 $0$；$num_i$ 表示 $\leq i$ 的数中有多少个未在 $Q$ 中出现；$pren_i$ 表示 $1\sim i$ 中 $Q$ 上有多少个 $-1$。设 $f_{i,j}$ 表示考虑到 $P$ 的前 $i$ 个数，当前前缀最大值为 $j$ 的方案数。下面考虑转移：

- 若 $P_i=j$，也即当前位置是前缀最大值。此时 $j$ 会向后移动，也即需要满足 $pos_{j}\geq i$ 或 $pos_j=0$；同时上一个前缀最大值会被放在 $i-1$ 的位置。设上一个前缀最大值为 $k$，我们需要满足 $Q_{i-1}=k$ 或 $pos_k=0$。对于满足条件的 $k<j$，我们有 $f_{i,j}\gets f_{i-1,k}$。

- 若 $P_i<j$，则 $P_i$ 会向前移动一位。继续根据 $Q_i$ 的取值分类：

  - 若 $Q_{i-1}\neq -1$，则此时该位置只能填写 $Q_{i-1}$，且之前一定没有填写过这个数（由于其 $pos$ 已经确定，故无论是否作为前缀最大值，转移都不合法）。故我们有 $f_{i,j}\gets f_{i-1,j}$。
  - 若 $Q_{i-1}=-1$，则该位置可以填未在 $Q$ 中出现过、且之前的 $-1$ 未被填过的小于 $j$ 的数。此时，$Q$ 中 $i-1$ 之前的填在 $-1$ 处的值一定小于 $j$，故剩余可行的值还有 $num_{j-1}-pren_{i-2}$ 个。故我们有 $f_{i,j}\gets f_{i-1,j}\times (num_{j-1}-pren_{i-2})$。

使用前缀和优化掉第一种情况的枚举 $k$ 的操作即可做到 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define double long double
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=5002,M=15,S=(1<<8)+5,inf=(ll)1e18+7,mo=998244353;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,a[N];
int f[N][N],sum[N][N],pren[N],num[N],pos[N];
bool equ(int x,int v){
    if(a[x]>0)return a[x]==v;
    return !pos[v];
}
signed main(){
    read(n);
    rep(i,1,n){
        read(a[i]);
        if(a[i]!=-1)pos[a[i]]=i;
        pren[i]=pren[i-1]+(a[i]==-1);
    }
    if((a[n]>0&&a[n]!=n)||(a[n]==-1&&pos[n])){
        puts("0");
        return 0;
    }
    rep(i,1,n)
        num[i]=num[i-1]+(!pos[i]);
    f[0][0]=1;
    rep(i,0,n)
        sum[0][i]=1;
    rep(i,1,n){
        rep(j,1,n){
            //1.i is prefix max
            if(!pos[j]||pos[j]>=i)f[i][j]+=sum[i-1][j-1];
            //2.i isnot
            if(a[i-1]!=-1){
                if(a[i-1]<j)f[i][j]+=f[i-1][j];
            }
            else f[i][j]+=f[i-1][j]*(num[j-1]-(pren[i-1]-1));
            f[i][j]%=mo;
            sum[i][j]=(sum[i][j-1]+f[i][j]*equ(i,j))%mo;
        }
    }
    printf("%lld\n",f[n][n]);
    return 0;
}
```

---

## 作者：eastcloud (赞：11)

首先考虑怎么刻画这个冒泡排序的过程，手玩一下可以发现，一轮冒泡排序把所有前缀最大值移到了下一个前缀最大值之前，且我们只做了这样的操作。

由于题目还要求了每个位置必须放什么数，因此我们平常用于求解排列个数的方法例如从小到大插入或是怎么计数一下都不太方便，因此不妨就从冒泡排序的过程入手设计思路。

在这里，前缀最大值是比较重要的，因此你可以考虑记录一下在我们目前构造出来的这个排列中，做一轮冒泡排序移到最前面的是什么数，设 $f_{i,j}$ 表示我们已经填了 $i$ 个数，同时进行的冒泡排序中目前移到最前面的是 $j$。

怎么转移呢？先考虑一下题目给的部分数被钦定了的限制，考虑我们怎么满足这个限制：这个数要么从前面被移过来，要么从后面被一次交换换过来，要么不动，而这些在我们转移到第 $i$ 位的时候都是方便处理的。

还要注意一个问题：如果后面需要放的数被前面放了怎么办？这好办，直接前面钦定不要填就好了，设 $sum_{i,j}$ 表示 $[i+1,n]$ 这个区间中有多少个 $q_k$ 使得 $q_k\neq -1$ 且 $q_k<j$，可以得出转移：

- 若 $a_i=-1$，要么在下一个位置填一个比 $j$ 大的数，注意这里如果 $j$ 被后面钦定了，则不能进行此转移，因为你的 $j$ 移不过去了，我们有 $f_{i,j}\rightarrow f_{i+1,k}$；要么在下一个位置填一个比 $j$ 小的数，注意同样不能填填过的，有 $(j-i-sum_{i,j})f_{i,j} \rightarrow f_{i+1,j}$。

- 若 $a_i \neq -1$，那么如果 $j=q_i$，那么你下面必须填一个比 $j$ 大的，但是这次不用考虑被后面选了，转移同上；否则你需要保证 $j>q_i$，且下一个位置就填 $q_i$，有 $f_{i,j}\rightarrow f_{i+1,j}$。

最后别忘了前面向比 $j$ 大的转移需要前缀和优化，代码很短。


```cpp
int main(){
    int n=read();
    for(int i=1;i<=n;i++){
        q[i]=read();
        if(q[i]!=-1)buc[q[i]]++;
    }
    if(q[n]!=-1 && q[n]!=n){write(0);return 0;}
    for(int i=1;i<=n;i++)f[1][i]=1;
    for(int i=1;i<n;i++){
        if(q[i]!=-1)buc[q[i]]--;
        for(int j=1;j<=n;j++)sum[j]=sum[j-1]+buc[j];
        for(int j=1;j<=n;j++){
            if(!f[i][j])continue;
            if(q[i]!=-1){
                if(q[i]==j) for(int k=j+1;k<=n;k++)Add(f[i+1][k],f[i][j]);
                else if(q[i]<j)Add(f[i+1][j],f[i][j]);
            }
            else{
                int tot=j-1-(i-1)-sum[j-1];
                if(tot<=0)continue;
                Add(f[i+1][j],mul(f[i][j],tot));
            }
        }
        if(q[i]==-1){
            int S=0;
            for(int j=1;j<=n;j++){
                Add(f[i+1][j],S);
                if(!buc[j])Add(S,f[i][j]);
            }
        }
    }
    write(f[n][n]);
    return 0;
}
```

---

## 作者：封禁用户 (赞：6)

这个题细节有点多啊。

考虑冒泡排序的本质，就是对于一个 $a_i$ 满足 $\max\limits_{j = 1} ^ {i - 1}{a_j} < a_i$ 将它交换到第一个比它大的数之前。更直观的，记 $pre_i = \max\limits_{j = 1} ^ i a_i$，在一个坐标系上出现 $(i, pre_i)$ 这个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/sm0n6drh.png)

如果一个排列建出来长这个样子，那么显然的就是对于类似 $BF$ 的线段（即这一段所有前缀最大值相等）上面所有点会循环左移，即除开头外，其它元素向前移动 $1$，开头移动到结尾。

这个时候性质就足够了，可以 dp 了。

设 $f(i, j)$ 表示填了前 $i$ 个数，当前最大值为 $j$ 的方案数。（即会出现 $(i, j)$ 的方案数）。

转移的话，根据上述模拟的过程可以推出来，当前位置 $j$ 要填 $i$ 的话，要么 $j$ 是 $i$ 开头的段的结尾；要么就是 $i$ 不是某一段开头，且 $j + 1$ 填 $i$。

记 $cnt_j$ 表示 $Q$ 中 $[i + 1, n]$ 中 $[1, j]$ 的出现次数。

根据上述过程可知，$i$ 填的数和 $Q_{i - 1}$ 有关。

+ 若 $Q_{i - 1} = -1$ 则当前位置可以随意填，无影响，则 
	+ 若 $k > j$，则 $f(i, k) \leftarrow f(i - 1, j)$。
	+ 否则，$f(i, j) \leftarrow f(i - 1, j) \times (j - (i - 1) - cnt_{j - 1})$。
+ 若 $Q_{i - 1} \neq -1$，则有两种情况，
	+ 若 $Q_{i - 1} < j$ 则当前位置必须填 $Q_{i - 1}$，而 $Q_{i - 1} < j$ 小不会影响前缀最大值，$f(i, j) \leftarrow f(i - 1, j)$。
	+ 否则，这一段到这里就结束了，因此当前的数需要比 $Q_{i - 1}$ 大，即
		+ $k > Q_{i - 1}, f(i, k) \leftarrow f(i - 1, Q_{i - 1})$。

这样就能写出 $\mathcal{O}(n ^ 3)$ 的代码了，而每次区间加都是加的后缀，差分维护即可实现 $\mathcal{O}(n ^ 2)$。

[$\texttt{Code}$](https://atcoder.jp/contests/arc187/submissions/59990530)

---

## 作者：Eraine (赞：6)

编号：AT_arc187_c  
tag：计数 dp  
难度：$\color{orange}{2574}$

“冒泡排序有一种被出烂但是每次碰到我都不会的美感。” —— wosile

该题只要求一轮冒泡排序，然后考虑一轮冒泡排序的效益实际上是把一段最大值在第一个元素的段把最大值放到了最后面，然后要求这若干段的最大值递增。

这很好考虑啊！那实际有用的状态发现只有当前段的 $\max$ 而已。那么钦定 $f_{i,j}$ 表示第 $i$ 个元素所在联通块 $\max$ 为 $j$ 的方案数。为了方便相邻段转移，所以再钦定 $g_{i,j}$ 表示第 $i$ 个元素所在联通块 $\max$ 为 $j$，且第 $i$ 个元素为当前联通块最后一个元素的方案数。

接下来会发现统计经过一轮变化后的排列要比统计原排列要轻松简单。因为经过一轮变化后的排列的每个元素实际位置恰好对应了给定序列的位置。如果序列全为 $-1$ 那是较为简单的。现在有了给定元素之后约束比较麻烦，那么就来细致刻画约束。

往 $f_{i,j}$ 转移，也就是在 $w=(j-1)-(i-1)-(\sum[a_k\lt j])+(\sum_{1\le k\lt i}[a_k\lt j])$ 个元素中任意选出一个作为当前值。若当前位置已被钦定，那么除了 $a_k\ge j$ 的情况无法转移，其余转移系数为 $1$；否则转移系数为 $w$。

往 $g_{i,j}$ 转移，那么当前 $a$ 只能被钦定为 $j$。所以要特判一下 $a_i\neq j$ 和 $pos_j\neq i$ 的情况。转移系数为 $1$。

从 $f_{i-1,j}$ 可以直接 $\Theta(1)$ 转移，从 $g_{i-1,p}(p\lt j)$ 前缀和优化可以将 $\Theta(n)$ 转移优化到 $\Theta(1)$。

状态数 $\Theta(n^2)$，转移 $\Theta(1)$。

$\Theta(n^2)$。

[submission](https://atcoder.jp/contests/arc187/submissions/59920610)

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：Hanghang (赞：5)

### [ARC187C](https://www.luogu.com.cn/problem/AT_arc187_c)

挺好的题，感谢大神 hyc 的指导。

鲜花：场上运气好通过了 D 没过 C，上了大分。

考虑直接模拟 $P$ 序列的操作过程，假设当前操作了 $1\sim i$，那么当前的 $P_i$ 一定是前缀最大值。

那么自然想到设状态 $f_{i,j}$ 表示当前考虑了 $1\sim i$ 的所有冒泡交换操作，$P_i=j$  且 $\forall k < i \land Q_k >0，Q_k=P_k$  的方案数。（此时 $P_i$ 为前缀最大值）

现在考虑从 $f_{i-1,k}$ 转移到 $f_{i,j}$，那么自然而然分为两种情况 $Q_{i-1}=-1$ 和 $Q_{i-1} \neq -1$。

定义集合 $S$ 为 $Q_i$ 中所有出现过的正数集合，记 $cnt_i$ 表示有多少个小于等于 $i$ 的数没有出现在 $S$ 内，$w_i$ 表示前 $i$ 个数中有多少个 $Q_j=-1$。

对于第一种情况，那么我们需要让 $P_{i-1}$ 成为一个不在集合 $S$ 里面的数，那么分两种情况，一种是第 $i$ 个位置放比 $k$ 大的数 $j$，那么要满足的 $k$ 不在 $S$ 内，这个可以前缀和优化做到 $O(1)$，第二种第 $i$ 个位置放 比 $k$ 小的数 $v$，那么会贡献到 $f_{i,k}$ 且 $v$ 不在 $S$ 内，那么此时 $v$ 的选法有 $cnt_{k-1}-w_{i-1}$ 种，$O(1)$ 转移。

第二种情况，需要让 $P_{i-1}=Q_{i-1}$，那么还是分为两种情况，一种是第 $i$ 个位置填了 $P_{i-1}$，那么需要满足 $k>P_{i-1}$，贡献到 $f_{i,k}$，第二种是第 $i$ 个位置填了 $j$，那么需要满足 $j>a_{i-1}\land k=a_{i-1}$,都是 $O(1)$ 转移的。

那么本题复杂度就是 $O(n^2)$，非常优美的一道题。

可以配合代码理解：

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=5003,H=998244353;
ll n,a[N],cnt[N],f[N],g[N],h[N];
bool ban[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)if(a[i]!=-1)ban[a[i]]=1;
	for(int i=1;i<=n;i++)cnt[i]=cnt[i-1]+(ban[i]==0),f[i]=1;
	for(int t=1,w=0;t<n;w+=a[t++]==-1)
	{
		memcpy(g,f,sizeof(g));memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++)h[i]=(h[i-1]+(ban[i]==0)*g[i])%H;
		for(int i=1;i<=n;i++)
		{
			if(a[t]==-1)f[i]=(g[i]*(cnt[i-1]-w)+h[i-1])%H;
			else if(i>a[t])f[i]=(g[i]+g[a[t]])%H;
		}
	}
	cout<<f[n];
}
```

---

## 作者：UniGravity (赞：3)

## Solution ARC187C 1 Loop Bubble Sort

鲜花：这题赛后花两天时间才调出来。

### 题意
> 对于一个长度为 $n$ 的排列 $a$，定义一次操作为依次对于 $i\in[1,n)$，若 $a_i>a_{i+1}$ 则 swap 它们（即对于序列 $a$ 执行单次冒泡排序的操作）。   
> 现在给你一个序列 $ans$，其中钦定了一些位置。你要求出有多少个排列 $a$ 使得对 $a$ 进行单次操作后满足 $a$ 和 $ans$ 在钦定的这些位置相等。

先分析题目所说的单次冒泡排序的操作。我们发现假设处理到 $a_i$，其会跟随 swap 操作一直往后移到第一个大于 $a_i$ 的位置前。即将 $a$ 划分成若干个段，每个段的**最大值均为这个段的第一个数**，且每一段的第一个数依次递增。然后对于每个段循环向左移位。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/me30qsxg.png)

考虑知道了 $ans$ 如何倒着推出 $a$，此时变成了选出一些段，每个段的**最大值必须在其末尾**，且若从左往右对段编号，编号小的段的最大值小于编号大的段。每种划分 $ans$ 的方案数都对应着一种合法的 $a$，我们只需对前者计数即可。

此时我们发现就变成了较为经典的 dp 形式，记 $f_{i,j}$ 表示钦定 $i$ 是当前段的最后一个元素，且值为 $j$ 的方案数。那么它可以从 $f_{k,l}\ (0\le k<i,0\le l<j)$ 转移过来，表示选了 $(k,i]$ 这个段。

考虑朴素的 dp 方式，记 $sum_i$ 表示**值域**在 $[1,i]$ 内被钦定的数的个数，$cnt_i$ 表示**下标**在 $[1,i]$ 内**未被钦定的个数**。

式子略繁杂但是不难推，建议自己先去推一下。这里直接给出：

$$f_{i,j}=\sum_{k=0}^{i-1}\sum_{l=0}^{j-1}f_{k,l}\frac{(j-sum_j-[ans_i\neq j]-cnt_k)!}{(j-sum_j-cnt_i)!}$$

后面的代表乘上的排列数，$[ans_i\neq j]$ 意思是如果最后一个是 $-1$ 那么其值必须为 $j$，直接钦定了。

然后需要判掉 $f_{i,j}$ 不合法的情况，细节较多。

考虑优化。首先发现 $l$ 这维后面乘上的系数都一样，所以前缀和一下，记 $g_k$ 表示当前的 $\sum f_{k,l}$，此时时间复杂度变成了 $O(n^3)$。

然后发现优化后的式子调换 $i,j$ 的枚举顺序，仍然可以前缀和。$f_{i,j}$ 涉及到的 $g$ 的下标是一个区间，因为需要满足 $(k,i]$ 这个区间的最大值不能超过 $j$ 所以 $k$ 不能过小。这个伴随 $i$ 的增大是具有单调性的，所以可以双指针。

时间复杂度 $O(n^2)$，[code](https://atcoder.jp/contests/arc187/submissions/59973037)

---

## 作者：SFlyer (赞：3)

首先扔出一个结论，如果 $Q$ 中没有 $-1$，那么答案是 $2^k$，其中 $k=\sum_{i=2}^n [Q_i=\max(Q_{1\sim i})]$。考虑证明。

设 $Q_i=\max(Q_{1\sim i})$ 的位置（包含 $i=1$）是 $a_1\sim a_{k+1}$。那么设 $f_i$ 为 $1\sim a_i$ 的答案，显然 $f_1=1$。考虑 $Q_{a_i}$ 放哪。我们发现可以插在前面一个前缀最大值 $a_j$ 的正后方，而 $a_j+1\sim a_i$ 是啥都固定了，并且 $1\sim a_j$ 是 $f_j$。还有一种情况是插在最前面。那么得出 $f_i=\sum_{j=1}^{i-1}f_j+1$，则 $f_1=1,f_2=2,f_3=1+2+1=4,f_4=1+2+4+1=8,\cdots, f_{k+1}=2^{k}$。

因此设 $f_{i,j}$ 为前 $i$ 位，现在 $\max$ 是 $j$ 的答案即可。为了方便，设 $Q_0=0$，最后答案是 $\frac{f_{n,n}}{2}$。

---

## 作者：Acoipp (赞：2)

考虑 $Q$ 确定了之后 $P$ 的方案数是多少。

容易发现，$P'_n=n$，并且如果我们找到 $n-1$ 的位置设为 $i$，假如原来的 $P$ 中 $n-1$ 在 $n$ 的前面，那么 $P_{i+1}$ 一定为 $n$，因为 $n-1$ 是除了 $n$ 之外最大的数，如果 $n-1$ 停在了 $i$ 这个位置，那么说明 $n-1<P_{i+1}$，那么 $P_{i+1}$ 就只能为 $n$ 了，并且 $i+1$ 及后面的位置在 $P'$ 确定之后只有 $1$ 种填法。

如果 $n-1$ 在 $P$ 中的位置在 $n$ 后面，设 $P$ 中 $n$ 的位置为 $j$，那么 $P'_{j-1}=\max\{P_1,P_2,\dots,P_{j-1}\}$，并且 $j+1$ 及后面的位置在 $P'$ 确定之后只有 $1$ 种填法。

因此，我们可以归纳地证明，$Q$ 确定之后 $P$ 的方案数就是 $2^c$，$c$ 是 $Q$ 的前缀最大值个数减去 $1$。

而这个 $2^c$ 不太好处理，我们考虑对二元组 $(Q,S)$ 计数，$S$ 是一个集合，表示 $S$ 中的每个元素都是前缀最大值，但是不要求所有前缀最大值的位置都在 $S$ 中，例如 $Q=[1,2,3,4,5]$，那么 $S=\{1,3,4\}$ 是合法的。

设 $f_{i,j}$ 表示前 $i$ 个元素中第 $i$ 个元素是前缀最大值，恰好为 $j$ 符合条件的 $S$ 数量，辅助数组 $g_{i,j}$ 表示前 $i$ 个元素中第 $i$ 个元素是前缀最大值，至多为 $j$。边界情况为 $f_{0,0}=1$，答案为 $f_{n,n}$，容易发现 $g_{i,j} = \sum_{k=1}^j f_{i,k}$。

然后考虑转移，为了方便，这里只转移 $Q_i=-1$ 的情况，首先，枚举 $Q_i=k$，再枚举 $1 \le j \le i$，满足 $\max_{l=j}^i Q_l \le Q_i$，然后 $f_{i,k} \gets g_{j-1,k-1} \times A_{a}^b$，其中 $a$ 是 $1 \sim k-1$ 没有确定的元素（即 $1 \le Q_j \le k-1$ 的 $j$ 的个数）减去 $Q_1 \sim Q_{j-1}$ 中 $-1$ 的个数（已经选择的），$b$ 是 $Q_j \sim Q_{i-1}$ 中 $-1$ 的个数，注意，枚举 $k$ 的时候要确保没有 $Q_j=k$。

上面转移的组合意义很简单，就是把 $a$ 个数按照顺序填入 $b$ 个空的方案，就是 $A_a^b = \frac{a!}{(a-b)!}$。

最后把 $A$ 的两个阶乘拆开，就可以直接分离贡献，用前缀和优化到 $O(n^2)$ 了，怎么分离就不细讲了，留作读者思考。

时间和空间复杂度都是 $O(n^2)$。

---

## 作者：weirdoX (赞：2)

## C - 1 Loop Bubble Sort
我们考虑从大到小添加值 $i$，我们记**目前填入的最靠左的位置在 $j$**，我们发现如果 $pos_i < j$，那么它最终会移动
$j-1$，如果 $pos_i>j$，那么它最终会移动到 $pos_i-1$，然后我们都知道了最终会移动到的位置，我们就
$dp_{i,j}$ 表示考虑了值域 $[i,n]$，目前最靠左的位置是 $j$，然后大概简单分类讨论一下 $i$ 这个值最终位置是否确定了
（是否在 $Q$ 中确定了），或者最终位置在 $Q$ 的某个 $-1$ 上，对于不确定的，可以前缀和优化。
时间复杂度：$O(n^2)$。

### 核心代码：
```cpp

const int N = 5043;
int n;
int q[N], suf[N], p[N];
mi dp[N][N], s[N][N];

int main() {
    scanf("%d", &n);
    rep(i,1,n) {
        scanf("%d", &q[i]);
        p[q[i]] = i;
    }
    per(i,n,1) {
        suf[i] = suf[i + 1] + (q[i] == -1);
    }
    dp[n + 1][n + 1] = 1;
    int cnt = 0;
    per(i,n,1) {
        per(j,n + 1,1) {
            s[i + 1][j] = s[i + 1][j + 1] + (q[j - 1] == -1) * dp[i + 1][j];
        }
        if (p[i]) {
            rep(j,1,p[i]) dp[i][j] += dp[i + 1][p[i] + 1];
            rep(j,1,p[i]) dp[i][j] += dp[i + 1][j];
        } else {
            rep(j,1,n) {
                dp[i][j] += s[i + 1][j + 1];
                if (suf[j] > cnt)
                    dp[i][j] += dp[i + 1][j] * (suf[j] - cnt);
            }
            cnt++;
        }
    }
    printf("%d\n", dp[1][1].v);
    return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

设 $c_i$ 表示 $[1,i-1]$ 中比 $a_i$ 大的数量，那么有经典结论：一次冒泡排序相当于全部 $-1$ 再整体左移一位，最后所有 $c$ 对 $0$ 取 max。所以容易发现，对于一个固定的排列 $p$，答案就是 $2^{x-1}$，$x$ 表示 $p$ 对应的 $c$ 序列中 $0$ 的数量，也就是前缀最大值的数量。

于是可以直接进行 dp 了。设 $f_{i,j}$ 表示目前填完了值域 $[i,n]$，当前的前缀最大值填到了 $j$。转移可以分成放在 $j$ 前面 / 后面两种情况考虑。

如果这个数已经出现，直接放到对应位置上。如果没有出现，放在前面就是枚举一个 $-1$，把 $j$ 转移到这个位置上；放在后面的话，所有 $-1$ 本质相同，可以直接乘上一个 $-1$ 个数的系数。发现所有系数都与 $i,j$ 相关，不需要额外记录维度了。放前面的转移可以用前缀和优化，因此时间复杂度为 $\mathcal O(n^2)$。

注意特判无解的情况。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=5009,Mod=998244353;
ll n,a[N],pos[N],dp[N][N],suf[N],sq[N],sum[N],b[N],c[N];
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,1,n)a[i]=read();
    if(n<=10){
        rep(i,1,n)b[i]=i;
        ll ans=0;
        do{
            rep(i,1,n)c[i]=b[i];
            rep(i,1,n-1){
                if(c[i]>c[i+1])swap(c[i],c[i+1]);
            }
            ll fl=1;
            rep(i,1,n){
                if(~a[i]&&c[i]!=a[i]){
                    fl=0;
                    break;
                }
            }
            if(fl)ans++;
        }while(next_permutation(b+1,b+n+1));
        write(ans%Mod);
        return 0;
    }
    rep(i,1,n){
        if(~a[i])pos[a[i]]=i;
    }
    if(pos[n]&&pos[n]!=n)return puts("0"),0;
    if(~a[n]&&a[n]!=n)return puts("0"),0;
    a[n]=n,pos[n]=n;
    per(i,n,1){
        suf[i]=suf[i+1];
        if(!~a[i])suf[i]++;
    }
    dp[n][n]=1;
    per(i,n,1){
        sq[i]=sq[i+1];
        if(!pos[i])sq[i]++;
    }
    per(i,n,1){
        per(j,n,1)sum[j]=(sum[j]+sum[j+1])%Mod;
        rep(j,1,n){
            if(!~a[j])dp[i][j]=(dp[i][j]+sum[j])%Mod;
        }
        if(i==1)break;
        memset(sum,0,sizeof(sum));
        rep(j,1,n){
            if(!dp[i][j])continue;
            ll cnt=suf[j]-sq[i];
            if(cnt<0)continue;
            if(pos[i-1]){
                if(pos[i-1]==j)continue;
                if(pos[i-1]>j)dp[i-1][j]=(dp[i-1][j]+dp[i][j])%Mod;
                else dp[i-1][pos[i-1]]=(dp[i-1][pos[i-1]]+dp[i][j]*2)%Mod;
            }
            else {
                dp[i-1][j]=(dp[i-1][j]+dp[i][j]*cnt)%Mod;
                sum[j-1]=(sum[j-1]+dp[i][j]*2)%Mod;
            }
        }
    }
    write(dp[1][1]%Mod),putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

