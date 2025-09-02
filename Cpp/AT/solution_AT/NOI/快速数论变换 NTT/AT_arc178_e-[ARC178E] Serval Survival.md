# [ARC178E] Serval Survival

## 题目描述

在一座长度为 $L$ 的桥上，有 $N$ 只薮猫。

第 $i$ 只薮猫位于距离桥左端 $A_{i}$ 的位置，满足 $0 < A_{1} < A_{2} < \cdots < A_{N} < L$。

对于 $i = 1, 2, \dots, N$，请回答以下问题。

> 薮猫们会依次进行以下 $3$ 个动作：
>
> - 动作 $1$：除第 $i$ 只以外的 $N-1$ 只薮猫各自选择面向左或右。
> - 动作 $2$：第 $i$ 只薮猫选择面向左或右。
> - 动作 $3$：所有同时开始移动。每只以每单位时间恰好移动 $1$ 的速度前进。当薮猫到达桥的任一端时，会离开桥。当两只薮猫相遇时，双方都会反转前进方向并继续移动。
>
> 第 $i$ 只薮猫非常聪明，也很喜欢这座桥，因此在动作 $2$ 选择方向时，会观察其他 $N-1$ 只的朝向，并选择能让自己在动作 $3$ 中留在桥上的时间更长的方向。动作 $1$ 中，$N-1$ 只薮猫的朝向共有 $2^{N-1}$ 种组合。请你计算，对于所有这些组合，第 $i$ 只薮猫能留在桥上的最长时间之和，并对 $998244353$ 取模。可以证明，输出的结果一定是整数。

## 说明/提示

### 限制条件

- $1 \leq N \leq 10^{5}$
- $0 < A_{1} < A_{2} < \cdots < A_{N} < L \leq 10^{9}$
- 输入均为整数

### 样例解释 1

当 $i=1$ 时，始终面向右是最优的。当 $i=2$ 时，选择与第 $1$ 只薮猫相反的方向是最优的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 167
9 24```

### 输出

```
182
301```

## 样例 #2

### 输入

```
1 924
167```

### 输出

```
757```

## 样例 #3

### 输入

```
10 924924167
46001560 235529797 272749755 301863061 359726177 470023587 667800476 696193062 741860924 809211293```

### 输出

```
112048251
409175578
167800512
997730745
278651538
581491882
884751575
570877705
747965896
80750577```

# 题解

## 作者：qiuzx (赞：3)

首先对于一种固定局面，如何计算某个 $i$ 移出木板的时刻？显然所有球的相对位置永远不会发生变化（如果移出木板可以看作一直向无穷远的地方移动），并且任意时刻朝左的球数目也不会发生变化。这意味着如果最开始有 $x$ 个球朝左，那么最后 $1,2,\cdots,x$ 这些球会从左边离开，$x+1,\cdots,n$ 这些球会从右边离开。这样我们就不需要关心球的编号，而是只需要关心所有球的位置集合是什么。于是将相撞反向看作互相穿过，不影响球的位置集合。从而设 $A_1,\cdots,A_x$ 为从小到大排列的初始向左的球，那么最终第 $i$ 个向左移出的球的时刻就是 $a_{A_i}$。换句话说，对于任意 $1\le i\le x$，它离开木板的时刻是 $a_{A_i}$。右侧也是同理。

这样我们就得到了一种很好地刻画木板离开时刻的方式，所以接下来考虑某个 $i$ 的决策应该是怎样的。设当前有 $x'$ 个球向左，$y'$ 个球向右，则显然 $x'+y'=n-1$。如果 $x'\ge i$，那么无论 $i$ 的决策如何，它总会从左边离开，因此对于这种情况 $i$ 必然初始向右，因为这样会让 $A_i$ 更大一些，此时答案为 $a_{A_i}$。同理，若 $y'\ge n-i+1$，那么 $i$ 一定从右边离开，此时 $i$ 必然向左。

但是在 $x'=i-1,y'=n-i$ 时，$i$ 的选择会影响到它从哪一侧离开，所以这里需要讨论一下。若 $i$ 向左，那么它会从左侧离开，答案为最右侧的一个向左的球的 $a_j$。若 $i$ 向右，那么它会从右侧离开，答案为最左侧的一个向右的球的 $L-a_j$。我们进一步讨论一下，设 $r$ 为最右侧的向左的球（不包含 $i$），$l$ 为最左侧的向右的球（不包含 $i$），那么如果 $r<i$，则必然是 $r=i-1,l=i+1$（因为向左的球有恰好 $x'=i-1$ 个），此时两种答案分别为 $a_i$ 和 $L-a_i$，因此最终答案为 $\max(a_i,L-a_i)$。否则答案和 $i$ 无关，分别为 $a_r$ 和 $L-a_l$，因此最终答案为 $\max(a_r,L-a_l)$。

现在我们也能够对于一个局面知道 $i$ 的决策了，并且这个形式也是不错的，所以下面就可以开始考虑计数了。前两种情况的答案种没有 $\max$，比较方便计数，所以先考虑这两种。注意到向左和向右是对称的，将所有 $a_i$ 变成 $L-a_i$ 并翻转整个序列即可将向右的情况转化为向左的，所以下面只讨论 $x'\ge i$ 的情形。此时枚举 $A_i=j$，那么相当于要求 $j$ 前面的所有球（不包含 $i$）中有恰好 $i-1$ 个朝左，且 $j$ 朝左。由于此时已经有 $i$ 个朝左了，所以后面的随意。注意 $j<i$ 是一定不可以的，因为前面根本没有 $i$ 个数，所以 $i$ 一定在 $j$ 的前面，那么可供选择的点总共是 $j-2$ 个。因此方案数为 $\displaystyle \binom{j-2}{i-1}2^{n-j}$，对答案的贡献为 $a_j$。这样对于一个 $i$ 我们需要计算 $\displaystyle \sum_j a_j\binom{j-2}{i-1}2^{n-j}$，组合数拆开之后是一个差卷积的形式，可以用 NTT 做到 $O(n\log n)$。

下面来处理 $x'=i-1$ 的情形。$r<i$ 是比较特殊的，这种情形只有一种出现的可能局面（即 $i$ 前面的都向左，$i$ 后面的都向右），所以先不管这种情况。对于更一般的情况，考虑最终贡献到答案的是 $a_r$ 还是 $L-a_l$。同样由于对称性，我们只对 $a_r\ge L-a_l$ 的情况计算答案，然后翻转取反之后算另一侧。需要注意的一个细节是如果 $a_r=L-a_l$，会算重一遍，所以在反过来算的时候要保证 $a_r>L-a_l$ 才计入贡献，但这只是实现细节的问题。

现在枚举 $r$，考虑一下会有什么限制。首先 $r$ 是最右侧的一个向左的，所以 $>r$ 的球必须全部向右。其次要满足 $a_r\ge L-a_l$。可以找到第一个满足 $a_r\ge L-a_l$ 的 $l$，则要求 $<l$ 的球必须全部向左。剩下的 $[l,r)$ 这些球可以随便选，但要保证选出恰好 $i-l-1$ 个球。注意如果 $l\ge i$ 那么一定是不行的，因此此时至少要选择 $i$ 个球朝左。这意味着 $[l,r)$ 区间内一定包含 $i$，所以这部分方案数是 $\displaystyle \binom{r-l-1}{i-l-1}$。显然对于一个 $r$ 来说 $l$ 是什么和 $i$ 无关，所以设这个 $l$ 为 $b_r$。这样我们需要算的式子就是 $\displaystyle \sum_r[b_r<i]a_r\binom{r-b_r-1}{i-b_r-1}$，$b_r$ 是很容易 two pointers 算出的（翻转之后取等的细节处理也只在 $b_r$ 的具体取值上有差异），假定已经算出了，下面只需快速计数即可。

对于那些 $b_r>r$ 的可以直接忽略了。如果 $b_r=r$，那么这意味着只有我们先忽略的平凡情况下 $r$ 会产生贡献，所以直接计入贡献之后忽略。现在对于 $b_r<r$ 的这些 $r$，其对于一个 $i>b_r$ 的贡献系数为 $\displaystyle a_r\binom{r-b_r-1}{i-b_r-1}$，这个组合数的上面是一个定值，所以考虑写成多项式的形式。具体来说，设答案多项式为 $f(x)$，即 $[x^i]f(x)$ 表示 $i$ 的答案，那么这个组合数可以写成 $(1+x)^{r-b_r-1}$。但此时下指标是 $i$ 贡献到 $i$，实际上下指标为 $i$ 时会对答案的 $i+b_r+1$ 这一项产生贡献，因此真正对答案的贡献是 $a_rx^{b_r+1}(1+x)^{r-b_r-1}$。

于是最后我们需要解决的问题是求多项式 $\displaystyle\sum_r a_rx^{b_r+1}(1+x)^{r-b_r-1}$ 的各项系数。这个看起来还是无从下手，但需要注意到 $b_r$ 是单调递减的，且 $r-b_r-1$ 是单调递增的。而当多项式求和的指标具有单调性的时候，可以使用分治进行优化。具体地，令 $c_i=i-b_i-1$，则我们对区间 $[l,r]$ 记录 $\displaystyle\sum_{i=l}^ra_ix^{b_r-b_i}(1+x)^{c_i-c_l}$ 的值。这个多项式的次数是 $b_r-b_l+c_l-c_r+1$ 的。从而在一层分治总所有维护的多项式次数之和是 $O(b_n+c_n)=O(n)$ 的。每次合并时只需要将右区间的多项式乘上 $(1+x)^{c_{mid+1}-c_l}$，左区间的多项式乘上 $x^{b_l-b_{mid+1}}$ 然后加起来即可。所以合并的复杂度是 $O(len\log len)$，总复杂度 $O(n\log^2n)$。

[代码](https://atcoder.jp/contests/arc178/submissions/53687953)

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18362386)

### [[ARC178E] Serval Survival](https://www.luogu.com.cn/problem/AT_arc178_e)

非常生气，点开一道看起来很正常的计数，推着推着就发现需要多项式/fn。

首先对于“撞上了之后调头”这种东西有经典的思想：可以看成是互相穿过并没有调头。但是因为要求第 $i$ 只猫走过的路，所以可以看成是和撞上的猫互换身份。

手玩一下可以发现，如果第 $i$ 只猫向左走，它会和 $a_i$ 左边的第一只向右的猫互换身份，然后和 $a_i$ 右边的第一只向左的猫互换身份，然后和 $a_i$ 左边的第二只猫向右的猫互换身份$\dots$，位置指的都是初始位置。

第 $i$ 只猫走的路程就等于最后一只和他交换身份的猫直走能走的路程（向右为 $L-a_i$，向左为 $a_i$）。据此，我们可以找出第 $i$ 只猫的策略。

设 $a_i$ 左边向右走的猫的集合为 $L$，$a_i$ 右边向左走的猫的集合为 $R$，分类讨论：

#### 1. $|L|>|R|$

如果他向左走，最后和他交换身份的猫是 $L$ 中从右向左第 $|R|+1$ 只猫。如果他向右走则是 $L$ 中从右向左第 $|R|$ 只猫。因为是向右走，显然靠左边的猫一定走的更远，所以此时他一定会向左走。

#### 2. $|L|<|R|$

和上文同理，一定会选择向右走。

#### 3. $|L|=|R|$

此时他有两种策略：选择 $L$ 中最靠左的 $L-a_i$ 和 $R$ 中最靠右的 $a_i$，这是唯一有决策的点，需要选较大值。

考虑暴力 DP：设 $ans_i$ 表示第 $i$ 只猫的答案。

第一种情况 $|L|>|R|$：

$$
\begin{aligned}
ans_i&=\sum_{j=1}^i(L-a_j)2^{j-1}\sum_{k=0}^{i-j-1}\binom{i-j-1}{k}\binom{n-i}{k}\\
&=\sum_{j=1}^i(L-a_j)2^{j-1}\sum_{k=0}^{i-j-1}\binom{i-j-1}{k}\binom{n-i}{n-i-k}\\
&=\sum_{j=1}^i(L-a_j)2^{j-1}\binom{n-j-1}{n-i}\end{aligned}
$$

上面使用了范德蒙德卷积化简。发现组合数可以拆成 $i,j,i-j$ 相关的式子，可以 FFT。

对于 $|L|<|R|$ 的情况同理，可以把整个序列倒过来做一遍。

第二种情况 $|L|=|R|$，假设最大值在右侧取到：

$$
\begin{aligned}
ans_i&=\sum_{j=i+1}^n a_j\sum_{k=0}^{j-i-1}\binom{j-i-1}{k}\binom{i-L_j}{k+1}\\
&=\sum_{j=i+1}^n a_j\sum_{k=0}^{j-i-1}\binom{j-i-1}{k}\binom{i-L_j}{i-L_j-k-1}\\
&=\sum_{j=i+1}^n a_j\binom{j-1-L_j}{i-1-L_j}
\end{aligned}
$$

$L_i$ 表示最小的 $j$ 满足 $m-a_j<a_i$。还是范德蒙德卷积，但是这个式子并不好用 FFT 处理。考虑写成生成函数形式，令 $Ans(x)$ 表示 $\sum_{i=0}^n ans_i x^i$，则：

$$
Ans(x)=\sum_{j=2}^n a_j (1+x)^{j-1-L_j}x^{1+L_j}
$$

$(1+x)^{j-1-L_j}$ 是为了构造组合数系数，$x^{1+L_j}$ 是因为 $j$ 对 $i$ 贡献，$i$ 的下指标是 $i-L_j-1$，需要做一个整体平移。

因为 $L$ 是单减的，$i-1-L_i$ 是单增的，可以分治解决：设 $A_i$ 表示 $L_i+1$，$B_i$ 表示 $i-1-L_i$，$(1+x)^{B_l}x^{A_r}F_{l,r}(x)$ 表示 $l,r$ 区间对答案的贡献。合并：

$$
F_{l,r}(x)=F_{l,mid}(x)x^{A_r-A_{mid}}+F_{mid+1,r}(x)(1+x)^{B_{mid+1}-B_l}
$$

合并的时候暴力 FFT 即可。这样最终答案就是 $(1+x)^{B_{pos}}x^{A_n}F_{pos,n}(x)$，$pos$ 表示最小的 $i$ 满足 $i-1-L_i>0$。因为 $A,B$ 的值域都是 $n$ 的，一个点最多被 $\log n$ 次 FFT 包含，可以分析出复杂度是 $\mathcal O(n\log^2 n)$。代码写得很烂。

```cpp
namespace Poly
{
    const int MAXN=400000;
    int Shape,Invn[MAXN+10],R[MAXN*4+10],Prt[MAXN*4];
    inline void init()
    {
        Invn[0]=1;
        for(int i=1;i<=MAXN;++i)Invn[i]=Cmul(Invn[i-1],i);
        int tmp=power(Invn[MAXN],MOD-2);
        for(int i=MAXN;i>=1;--i)Invn[i]=Cmul(tmp,Invn[i-1]),Mmul(tmp,i);
    }
    inline int inv(int x){return x<=MAXN?Invn[x]:power(x,MOD-2);}
    inline void NTT(vi&A,int n,int opt)
    {
        static ull B[MAXN*4+10];ull iv=power(n,MOD-2);A.resize(n);
        for(int i=0;i<n;++i)B[i]=A[R[i]];
        for(int mid=1;mid<n;mid<<=1)
        {
            for(int j=0;j<n;j+=mid<<1)
            {
                for(int k=j;k<j+mid;++k)
                {
                    ull x=B[k],y=Prt[mid+k-j]*B[k+mid]%MOD;
                    B[k]=x+y,B[k+mid]=x+MOD-y;
                }
            }
        }
        if(opt)for(int i=0;i<n;++i)A[i]=B[i]%MOD;
        else{reverse(B+1,B+n);for(int i=0;i<n;++i)A[i]=Cmul(B[i]%MOD,iv);}
    }
    inline void init(int lim)
    {
        if(lim==Shape)return;
        int n=lim/2;Shape=lim;
        for(int i=0;i<lim;++i)R[i]=(R[i>>1]>>1)|((i&1)?n:0);
        for(int i=1;i<lim;i<<=1)
        {
            int wm=power(Root,(MOD-1)/(i<<1));Prt[i]=1;
            for(int j=1;j<i;++j)Prt[i+j]=Cmul(Prt[i+j-1],wm);
        }
    }
    inline vi FFT(vi A,vi B,int N1=-1,int N2=-1)
    {
        if(N1!=-1)A.resize(N1+1);if(N2!=-1)B.resize(N2+1);
        int n=A.size()-1,m=B.size()-1,N=1,len=0;
        while(N<=n+m)N<<=1,++len;
        init(N),NTT(A,N,1),NTT(B,N,1);
        for(int i=0;i<N;++i)A[i]=Cmul(A[i],B[i]);
        return NTT(A,N,0),A.resize(n+m+1),A;
    }
}
int n,m,dl,fr[100010],inv[100010],pre[100010],suf[100010],ans[100010];
int a[100010],L[100010],R[100010],pw[100010],b[100010],res[100010];
inline int C(int n,int m){return m<0||m>n?0:Cmul(fr[n],inv[m],inv[n-m]);}
vi add(vi L,vi R)
{
	int N=max(L.size(),R.size());L.resize(N),R.resize(N);
	for(int i=0;i<N;++i)Madd(L[i],R[i]);
	return L;
}
vi move(vi A,int x)
{
	A.resize(A.size()+x);
	for(int i=A.size()-1;i>=x;--i)A[i]=A[i-x];
	for(int i=0;i<x;++i)A[i]=0;
	return A;
}
vi Binom(vi A,int x)
{
	vi B(x+1);
	for(int i=0;i<=x;++i)B[i]=C(x,i);
	A=Poly::FFT(A,B);
	return A;
}
vi A,B;
vi solve(int l,int r)
{
	if(l==r)return {a[l]};
	int mid=l+((r-l)>>1);
	return add(move(solve(l,mid),B[mid]-B[r]),
	Binom(solve(mid+1,r),A[mid+1]-A[l]));
}
void solve()
{
	A.resize(n+1),B.resize(n+1);
	int pos=0;
	for(int i=1;i<=n;++i)
	{
		if(i-1-L[i]>=0)A[i]=i-1-L[i],B[i]=L[i]+1;
		else A[i]=B[i]=0,pos=i;
	}
	for(int i=pos+1;i<=n;++i)Mdel(res[i],a[i]);
	vi D;
	if(pos<n)D=move(Binom(solve(pos+1,n),A[pos+1]),B[n]);
	for(int i=1;i<(int)D.size();++i)Madd(res[i],D[i]);
}
inline void mian()
{
	Poly::init(),read(n,m),fr[0]=inv[0]=pw[0]=1;
	for(int i=1;i<=n;++i)fr[i]=Cmul(fr[i-1],i),pw[i]=Cmul(pw[i-1],2);
	inv[n]=power(fr[n],MOD-2);
	for(int i=n-1;i>0;--i)inv[i]=Cmul(inv[i+1],i+1);
	for(int i=1;i<=n;++i)read(a[i]),b[i]=m-a[i];
	a[0]=-inf,a[n+1]=inf,b[0]=inf,b[n+1]=-inf;
	for(int i=n,r=0;i>=1;R[i--]=r)
	{
		suf[i]=Cadd(suf[i+1],Cmul(power(2,n-i),a[i]));
		while(a[r+1]<b[i])++r;
	}
	for(int i=1,l=n+1;i<=n;L[i++]=l)
	{
		pre[i]=Cadd(pre[i-1],Cmul(power(2,i-1),b[i]));
		while(b[l-1]<=a[i])--l;
	}
	write(Cadd(max(a[1],b[1])%MOD,suf[2]),'\n');
	if(n==1)return;
	if(n==2)return write(Cadd(max(a[n],b[n])%MOD,pre[n-1]));
	for(int i=n;i>1;--i)Madd(dl,Cmul(a[i],pw[n-i]));
	vi X={0},Y={0},Z={0};Z.resize(n+1);
	for(int i=1;i<=n;++i)X.eb(Cmul(b[i],pw[i-1],fr[n-i-1]));
	for(int i=1;i<=n;++i)Y.eb(inv[i-1]);
	for(int i=1;i<n;++i)Z[i]=Cmul(a[n-i+1],pw[i-1],fr[n-i-1]);
	X=Poly::FFT(X,Y),Z=Poly::FFT(Z,Y);
	for(int i=2;i<n;++i)
	{
		ans[i]=Cadd(Cmul(X[i],inv[n-i]),max(a[i],b[i])%MOD,suf[i+1],pre[i-1],Cmul(inv[i-1],Z[n-i+1]));
		Madd(dl,Cmul(b[i-1],pw[i-2]));
		Mdel(dl,Cmul(a[i],pw[n-i]));
		Mdel(ans[i],dl);
	}
	solve();
	for(int i=1;i<=n;++i)Madd(ans[i],res[i]);
	memset(res,0,sizeof(res));int v=a[n];
	for(int i=1;i<=n;++i)a[i]=b[n-i+1],L[i]=n-R[n-i+1]+1;
	solve();
	for(int i=1;i<=n;++i)Madd(ans[i],res[n-i+1]);
	for(int i=2;i<n;++i)write(ans[i],'\n');
	if(n>1)write(Cadd(max(v,b[n])%MOD,pre[n-1]));
}
```

---

