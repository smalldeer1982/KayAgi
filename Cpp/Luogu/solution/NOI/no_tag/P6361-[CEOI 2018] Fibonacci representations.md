# [CEOI 2018] Fibonacci representations

## 题目背景

译自 CEOI2018 Day2 T1. [Fibonacci Representations](https://ceoi2018.pl/wp-content/uploads/2018/08/fib.pdf)。

## 题目描述

我们定义斐波那契数列为
$$
\begin{aligned}
F_1&=1\\
F_2&=2\\
F_n&=F_{n-1}+F_{n-2} \text{ for } n \ge 3
\end{aligned}
$$
序列的前面若干项为 $1,2,3,5,8,13,21,\ldots$。

对一个正整数 $p$，定义 $X(p)$ 为将 $p$ 用若干个**不同的**斐波那契数的和表示的方案数，两个方案不同当且仅当有一个斐波那契数恰好只在其中一个方案中出现。

给定一个长度为 $n$ 的正整数序列 $a_1,a_2,\ldots,a_n$，对于他的一个非空前缀 $a_1,a_2,\ldots,a_k$，我们定义 $p_k=F_{a_1}+F_{a_2}+\cdots+F_{a_k}$。

你的任务是对于所有 $k=1, 2, \ldots, n$，求出 $X(p_k)$ 对 $10^9+7$ 取模的值。

## 说明/提示

#### 样例解释

$p_k$ 的值如下：
$$
\begin{aligned}
p_1&=F_4=5\\
p_2&=F_4+F_1=5+1=6\\
p_3&=F_4+F_1+F_1=5+1+1=7\\
p_4&=F_4+F_1+F_1+F_5=5+1+1+8=15
\end{aligned}
$$

$5$ 可以用两种方法表示：$F_2+F_3$ 和单独的 $F_4$（即分别为 $2+3$ 和 $5$），所以 $X(p_1)=2$。

我们有 $X(p_2)=2$ 因为 $p_2=1+5=2+3$。

将 $7$ 表示成若干不同的斐波那契数之和的唯一一种方案是 $2+5$。

最后，$15$ 可以表示成 $2+13$ 和 $2+5+8$（两种方案）。

#### 数据规模与约定

对于 $100\%$ 的数据，$1\le n\le 10^5,\ 1\le a_i\le 10^9$。

所有测试数据被划分成以下若干个有附加限制的子任务。每个子任务中包含若干个测试点。

| 子任务 | 附加限制 | 分值 |
| :--: | :---: | :--: |
| $1$ | $n, a_i \leq 15$ | $5$ |
| $2$ | $n, a_i \leq 100$ | $20$ |
| $3$ | $n \leq 100$，$a_i$ 是不同的完全平方数 | $15$ |
| $4$ | $n \leq 100$ | $10$ |
| $5$ | $a_i$ 是不同的偶数 | $15$ |
| $6$ | 无附加限制 | $35$ |

## 样例 #1

### 输入

```
4
4 1 1 5```

### 输出

```
2
2
1
2```

# 题解

## 作者：warzone (赞：13)

为行文方便，用如下形式

$$\begin{matrix}
	b_1&b_2&\cdots&b_{k-1}&b_k&b_{k+1}&\cdots\\
	1&2&\cdots&k-1&k&k+1&\cdots
\end{matrix}$$
表示 $p=b_1F_1+b_2F_2+\cdots+b_{k-1}F_{k-1}+b_kF_k+b_{k+1}F_{k+1}+\cdots$ 。

---------------------------------------

首先对于单个斐波那契数 $F_k$，显然它可以被自己表示：

$$
\begin{matrix}
	\cdots&0&0&0&0&1&0&\cdots\\
	\cdots&k-4&k-3&k-2&k-1&k&k+1&\cdots
\end{matrix}$$

我们将 $F_k$ 展开为 $F_{k-1}+F_{k-2}$，便得到一个另一个表示它的方案：


$$\begin{matrix}
	\cdots&0&0&1&1&0&0&\cdots\\
	\cdots&k-4&k-3&k-2&k-1&k&k+1&\cdots
\end{matrix}$$

下一个方案是什么？因为题目要求用**不同的**斐波那契数表示，即**没有重复**，  
我们只能将 $F_{k-2}$ 展开为 $F_{k-3}+F_{k-4}$，因此下一个方案只能是

$$\begin{matrix}
	\cdots&1&1&0&1&0&0&\cdots\\
	\cdots&k-4&k-3&k-2&k-1&k&k+1&\cdots
\end{matrix}$$

以此类推，我们发现所有方案都一定满足

$$
\begin{matrix}
	\cdots&1&1&0&1&0&\cdots&1&0&1&0&0&\cdots\\
	\cdots&i&i+1&i+2&i+3&i+4&\cdots&k-3&k-2&k-1&k&k+1&\cdots
\end{matrix}$$

的形式。

--------------------

接下来考虑多个不相邻且不相同的斐波那契数的情形：

$$
\begin{matrix}
	\cdots&0&1&0&\cdots&0&1&0&\cdots\\
	\cdots&i-1&i&i+1&\cdots&k-1&k&k+1&\cdots
\end{matrix}
$$
若我们将 $F_k$ 展开，为保证没有重复，其展开会被 $F_i$ “堵住”：

$$
\begin{matrix}
	\cdots&0&1&0&1&1&0&1&\cdots&0&1&0&\cdots\\
	\cdots&i-1&i&i+1&i+2&i+3&i+4&i+5&\cdots&k-2&k-1&k&\cdots
\end{matrix}
$$
接下来我们将 $F_i$ 展开，但由展开形式得知，它是会留下 $\cdots101010$ 的轨迹，  
因此 $F_k$ 受到的堵塞最多有一个单位距离的缓解：

$$
\begin{matrix}
	\cdots&0&1&0&1&0&0&1&1&0&1&\cdots\\
	\cdots&i-4&i-3&i-2&i-1&i&i+1&i+2&i+3&i+4&i+5&\cdots
\end{matrix}
$$

因此，对于多个不相邻且不相同的斐波那契数

$$p=F_{a_1}+F_{a_2}+\cdots+F_{a_n}\quad(\forall i\in[1,n)\cap\mathrm{N},a_{i+1}-a_i\ge 2)$$

$F_{a_i}$ 展开的方案数只与 $F_{a_{i-1}}$ **是否展开** 有关。

于是设 $f_i$ 为 $F_{a_i}$ 不展开时表示 $F_{a_1}+F_{a_2}+\cdots+F_{a_i}$ 的总方案数，  
$g_i$ 为 $F_{a_i}$ 展开时表示 $F_{a_1}+F_{a_2}+\cdots+F_{a_i}$ 的总方案数，则

$$
\begin{cases}
	f_i=f_{i-1}+g_{i-1}\\
	g_i=\left\lfloor\dfrac{a_i-a_{i-1}-1}{2}\right\rfloor f_{i-1}+\left\lfloor\dfrac{a_i-a_{i-1}}{2}\right\rfloor g_{i-1}
\end{cases}
$$

显然转移可以表示为矩阵

$$
\begin{bmatrix}
	1&1\\\left\lfloor\dfrac{a_i-a_{i-1}-1}{2}\right\rfloor
	&\left\lfloor\dfrac{a_i-a_{i-1}}{2}\right\rfloor
\end{bmatrix}{f_{i-1}\brack g_{i-1}}={f_i\brack g_i}
$$

直接用平衡树维护转移矩阵即可通过子任务 3、5  。

--------------------------------

最后考虑存在相同或相邻的斐波那契数的情形。

根据[斐波那契编码](https://oi-wiki.org/math/fibonacci/#_9)，我们总有办法把 $\displaystyle p_k=\sum_{i=1}^kF_{a_k}$   
唯一表示成不相同且不相邻的斐波那契数。

类似 [[NOI2021] 密码箱](https://www.luogu.com.cn/problem/P7739)，
用平衡树维护形如

$$
\begin{matrix}
	\cdots&1&0&1&0&1&0&1&\cdots\\
	\cdots&i&i+1&i+2&i+3&i+4&i+5&i+6&\cdots
\end{matrix}
$$

的连续段。

考虑插入 $F_{a_i}$，如果其破坏了不相邻的性质：

$$
\begin{matrix}
	\cdots&1&1&1&0&1&0&1&0&0&\cdots\\
	\cdots&a_i-1&a_i&a_i+1&a_i+2&a_i+3&a_i+4&a_i+5&a_i+6&a_i+7&\cdots
\end{matrix}
$$

显然它可以和后面的不断合并，直到连续段的末尾：

$$
\begin{matrix}
	\cdots&1&0&0&0&0&0&0&1&0&\cdots\\
	\cdots&a_i-1&a_i&a_i+1&a_i+2&a_i+3&a_i+4&a_i+5&a_i+6&a_i+7&\cdots
\end{matrix}
$$

如果其破坏了不相同的性质：

$$
\begin{matrix}
	\cdots&0&0&1&0&1&0&1&0&2&0&\cdots\\
	\cdots&a_i-8&a_i-7&a_i-6&a_i-5&a_i-4&a_i-3&a_i-2&a_i-1&a_i&a_i+1&\cdots
\end{matrix}
$$

我们将 $F_{a_i}$ 一直展开到连续段的开头，展开方案就会刚好覆盖路径上所有的 $0$：

$$
\begin{matrix}
	\cdots&1&1&1&1&1&1&1&1&1&0&\cdots\\
	\cdots&a_i-8&a_i-7&a_i-6&a_i-5&a_i-4&a_i-3&a_i-2&a_i-1&a_i&a_i+1&\cdots
\end{matrix}
$$

接下来从后往前合并这些 $1$：

$$
\begin{matrix}
	\cdots&1&0&0&1&0&1&0&1&0&1&\cdots\\
	\cdots&a_i-8&a_i-7&a_i-6&a_i-5&a_i-4&a_i-3&a_i-2&a_i-1&a_i&a_i+1&\cdots
\end{matrix}
$$

相比于插入前，相当于 $F_{a_i}$ 前面的往后走一个单位距离，并在最前面留下一个 $1$。

特别的，连续段的末尾为 $F_1$ 或 $F_2$ 的情况要特别处理，这里留给读者自行思考。

处理完这些情况后，还要处理连续段与前趋后继的合并，~~所以代码实现要亿点分类讨论~~。

-----------------------

### Code

```cpp
#include<stdio.h>
#include<string.h>
#include<random>
typedef unsigned int word;
const word mod=1e9+7;
struct matrix{//矩阵
	word num[4];
	inline matrix(){}
	inline matrix(word a,word b,word c,word d){
		num[0]=a,num[1]=b,num[2]=c,num[3]=d;}
	#define mul(a,b) (1ull*num[a]*p.num[b])
	#define plus(a,b,c,d) (mul(a,b)+mul(c,d))%mod
	inline matrix operator()(const matrix &p)const{
		return matrix(
			plus(0,0,1,2),plus(0,1,1,3),
			plus(2,0,3,2),plus(2,1,3,3));}
	#undef mul
	#undef plus
}const I(1,0,0,1);
struct READ{//快读快写
	char c;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator >>(type &num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
std::mt19937 RAND(std::random_device{}());
struct treap{
	treap *l,*r;
	word f,cnt,end,blc;
	//f 第一个 1 的位置
	//cnt 1 的个数
	//end 最后一个 1 的位置
	matrix val,sum;
	//val 当前连续段的转移矩阵之积
	//sum 整棵平衡树的转移矩阵之积
	inline treap(){blc=RAND();}
	inline void calc(const word d){//计算转移矩阵 (a_i-a_{i-1}=d)
		end=f? f+((cnt-1)<<1):0;
		sum=val=matrix(
			(1ull*(cnt-1)*((d-1)/2)+1)%mod,
			(1ull*(cnt-1)*(d/2)+1)%mod,
			(d-1)/2,d/2);
	}
	inline void pushup(){
		sum=val;
		if(l) sum=sum(l->sum);
		if(r) sum=r->sum(sum),end=r->end;
		else end=f? f+((cnt-1)<<1):0;
	}
}p[1u<<17];
inline treap* merge(treap *l,treap *r){
	if(l==0) return r;
	if(r==0) return l;
	if(l->blc<=r->blc){
		l->sum=r->sum(l->sum);
		l->end=r->end;
		return l->r=merge(l->r,r),l;
	}
	r->sum=r->sum(l->sum);
	return r->l=merge(l,r->l),r;
}
inline treap* split(treap *&rt,word size){
	//分离 f>size 的连续段
	if(rt==0) return 0;
	treap *out=0;
	if(size<rt->f){
		out=split(rt->l,size);
		treap *swap=rt->l;
		rt->l=out,out=swap;
		swap=rt,rt=out,out=swap;
		return out->pushup(),out;
	}
	if(size==rt->f) out=rt->r,rt->r=0;
	else out=split(rt->r,size);
	return rt->pushup(),out;
}
inline treap* splitend(treap *&rt){
	if(rt->r){
		treap *out=splitend(rt->r);
		return rt->pushup(),out;
	}
	treap *out=rt;
	rt=rt->l,out->l=0;
	return out->pushup(),out;
}
inline treap* splitbegin(treap *&rt){
	if(rt->l){
		treap *out=splitbegin(rt->l);
		return rt->pushup(),out;
	}
	treap *out=rt;
	rt=rt->r,out->r=0;
	return out->pushup(),out;
}
word n,psiz;
treap *rt=p,*mid,*right;
inline void getend(){//讨论 mid 与后继的拼接情况
	treap *mid_=right;
	right=split(mid_,mid->f+(mid->cnt<<1));
	if(mid_) mid->cnt+=mid_->cnt;
	mid->calc(mid->f-rt->end);
	if(right){
		treap *nxt=splitbegin(right);
		nxt->calc(nxt->f-mid->end);
		mid=merge(mid,nxt);
	}
	rt=merge(merge(rt,mid),right);
}
inline void insert(word val){
	mid=split(rt,val);
	right=split(mid,val+1);
	if(mid) mid->f=mid->end+1,mid->cnt=1;//在连续段的最前面
	else if((rt==p&&rt->r==0)||val>rt->end+2)//没有插入到已有的连续段中
		mid=p+(++psiz),mid->f=val,mid->cnt=1;
	else if(mid=splitend(rt),val==mid->end+2) ++mid->cnt;
		//拼接到连续段的末尾
	else if((val-mid->f)&1){//破坏了不相邻的性质
		if(val!=mid->end+1){//在连续段中间
			mid->cnt=(val+1-mid->f)/2;
			val=mid->end+1;
			mid->calc(mid->f-rt->end);
			rt=merge(rt,mid);
		}else if(++val,mid->cnt!=1){//在连续段末尾
			--mid->cnt,mid->calc(mid->f-rt->end);
			rt=merge(rt,mid);
		}
		mid=right,right=split(mid,val+1);
		if(mid) mid->f=mid->end+1;
		else mid=p+(++psiz),mid->f=val;
		mid->cnt=1;
	}else if(val==mid->end){//破坏了不相接的性质（在连续段末尾）
		if(mid->f!=1&&mid->f!=2)
			return val=mid->f-2,++mid->f,getend(),insert(val);
		//开头不为 1 或 2 的情况
		if(mid->f==1) ++mid->f;
		else --mid->f,++mid->cnt;
		//开头为 1 或 2 的情况
	}else{//破坏了不相接的性质（在连续段中间）
		treap *nxt=p+(++psiz);
		nxt->f=mid->end+1,nxt->cnt=1;
		mid->cnt=(val-mid->f)/2;
		if(mid->f!=1&&mid->f!=2){
			if(val=mid->f-2,++mid->f,mid->cnt){
				mid->calc(mid->f-rt->end);
				rt=merge(rt,mid);
			}
			return mid=nxt,getend(),insert(val);
		}
		//开头不为 1 或 2 的情况
		if(mid->f==2){
			--mid->f,++mid->cnt;
			mid->calc(mid->f-rt->end);
			rt=merge(rt,mid);
		}else if(++mid->f,mid->cnt){
			mid->calc(mid->f-rt->end);
			rt=merge(rt,mid);
		}
		mid=nxt;
		//开头为 1 或 2 的情况
	}
	getend();
}
int main(){
	cin>>n;
	rt->f=0,rt->cnt=1,rt->end=0;
	rt->val=rt->sum=I;
	for(word val;n;--n){
		cin>>val,insert(val);
		printf("%u\n",(rt->sum.num[0]+rt->sum.num[2])%mod);
	}
	return 0;
}
```

---

## 作者：Loser_Syx (赞：5)

有一个性质，对于某个数 $n$，一定唯一有一个数组（即 $n$ 的斐波那契表示）$b\  (b_i \in \{0,1\})$ 且相邻两位不同时为 $1$，使得 $\sum_i b_iF_i = n$。可以考虑反证法证明。

由于对于某个 $F_{x}$ 可拆为 $F_{x-1}+F_{x-2}$，故考虑 dp，定义 $f_{i,0/1}$ 表示对于 $F_{a_i}$ 拆或不拆的方案数。

显然有 $f_{i,0}=f_{i-1,0}+f_{i-1,1}$，而因为 $F_{x}=F_{x-1}+F_{x-2}=F_{x-1}+F_{x-3}+F_{x-4}=\ldots$，显然不能拆前面几项，不然就会重复出现。这么一直拆直到与 $F_{i-1}$ 的答案相重，所以有 $f_{i,1}=\lfloor\frac{a_i-a_{i-1}-1}{2}\rfloor f_{i-1,0}+\lfloor\frac{a_i-a_{i-1}}{2}\rfloor f_{i-1,1}$。

用 Treap 维护矩阵乘法是好做到 $O(n \log n)$ 的。

以上为 $#5$ 做法，下面考虑 $a_i$ 会重复的做法。

考虑一开头的表示方法，我们维护这个 $b$ 表示，那么只需保证相邻两位不同时为 $1$。是个分讨。

- $b_{a_i-1}=b_{a_i}=b_{a_i+1}=0$。直接加入 $a_i$。
- $b_{a_i-1}=1$ 或 $b_{a_i+1}=1$。这时候根据 $F_{x}=F_{x-1}+F_{x-2}$ 把 $b_x$ 往前面合并。
- $b_{a_i}=1$。我们把其中一个 $F_{a_i}$ 分成 $F_{a_i-1}+F_{a_i-2}$，再把 $F_{a_i}$ 与 $F_{a_i-1}$ 合并起来，这个时候再看看 $F_{a_i-2}$ 会不会变成 $2$ 即可。手玩一下就发现是集体向高位移一位并在最近一个 $b_x=b_{x+1}=0$ 的 $x$ 停下来。$x$ 可能 $\leq 0$，记得特判。

分析复杂度，发现操作 $2$ 实际上是删除了一个 $a_i$，那么就是 $O(n)$ 次。而操作 $3$ 的平移的话使用一个平衡树维护并且在平衡树上二分找到 $x$ 即可。复杂度 $O(n \log n)$。

---

## 作者：mysterys (赞：3)

$Lemma$：[齐肯多夫表示法](https://baike.baidu.com/item/%E9%BD%90%E8%82%AF%E5%A4%9A%E5%A4%AB%E5%AE%9A%E7%90%86/7612155 "齐肯多夫表示法")

我们先抛开题目：对于一个数 $x$, 考虑将它表示为一些不同的斐波那契数之和的方案数是多少。

我们记 $F_i$ 表示斐波那契数列的第 $i$ 项，$p_i$ 表示将 $x$ 用齐肯多夫表示法拆分后第 $i$ 项在斐波那契数列中的下标。

发现由于每个斐波那契数列中的数都可以被拆分成前两项之和，于是我们得到了一个可以用矩阵来帮助转移的 $dp$ :


记 $f_{i,0/1}$ 表示用齐肯多夫表示法表示出 $x$ 后，考虑拆分序列的前 $i$ 项，$F_{p_i}$ 拆/不拆的方案数。

让我们回到原问题，我们需要动态插入一些 $a_i$，并维护答案。如果 $a_i$ 互不相同，可以利用平衡树直接维护矩阵乘法。

我们考虑一些 $a_i$ 相同的情况。一种解决方法是将 $2\times F_i$ 拆分成  $F_{i-2} + F_{i+1}$ 然后借助一些分类讨论和平衡树维护交替 $01$ 段解决。

对于简单的分类讨论别的题解已经写得很详细了，现在来讲一下比较特殊的情况和 corner case: 

我们将 $2\times F_i =F_{i-2} + F_{i+1}$ 的情况手动展开，发现本质上是对于一段极长的 $01$ 交替的值域区间做平移。我们前面在维护矩阵时已经记录的差分数组，所以这一部分可以用平衡树上二分解决。**具体的**：我们对于每个点记录其前驱和后继以及前驱和它的差值是否为 $2$ 即可。

然后就是最重要的一些边界，考虑新加入的点所在的极长连续 $01$ 段如果一直蔓延到了 $1$ 或者 $2$，那么这时候我们无法把它的前面这一段区间做平移。手玩一下发现其实这个过程就是递归到边界，然后不断向右合并。于是只要再维护某个数右侧极长的 $01$ 交替段即可。同样平衡树上二分 + 分裂就做完了。

另一种特殊情况就是 $2 \times F_2 = F_1 + F_3$，特判即可。

注意转移矩阵的顺序和边界就可以比较轻松地写完这道题。

---

## 作者：Eznibuil (赞：3)

~~考场想出正解没写出来的是什么\*\*，是我啊，那没事了。~~

首先想想对于一个数，方案数是多少？

考虑尽量将这个数拆成比较大的斐波那契数。显然由于斐波那契数列满足后一个大概是前一个的 $\frac{1+\sqrt5}2$ 倍所以一定能拆成互不相同的斐波那契数。找出其中拆得最少、数字最大的那个方案，显然没有相邻的斐波那契数。设方案为 $a_1,\dots,a_k$，并且 $\forall1\le i<k,a_i<a_{i+1}$（也就是升序），即原数是 $F_{a_1}+\cdots+F_{a_k}$。

于是可以设一个 DP 状态 $f_{i,0/1}$ 表示当前算出了 $a_1,\dots,a_i$ 的答案，是否让最后一个也就是 $a_i$ 拆为了两个。则方程为：
$$\begin{cases}f_{i,0}=f_{i-1,0}+f_{i-1,1}\\f_{i,1}=\lfloor\frac{a_i-a_{i-1}-1}2\rfloor f_{i-1,0}+\lfloor\frac{a_i-a_{i-1}}2\rfloor f_{i-1,1}\end{cases}$$
静态的查询就可以做了。

现在考虑修改的问题。注意到本身给的形式就很优美，有 $p_i=p_{i-1}+F_{a_i}$，那么维护刚刚的 $a_1,\dots,a_k$（不是题面的）该怎么办呢？也就是说，现在单点插入一个新的斐波那契数该如何修改？

重新改写一下，不妨维护一个 $b_1,\dots,b_{2\times10^9}$ 表示 $b_1F_1+b_2F_2+\cdots+b_{2\times10^9}F_{2\times10^9}$。显然这些数都是取 $0/1$ 的。

分类讨论一下，有两种情况：把 $b_i$ 从 $0$ 变为 $1$、从 $1$ 变为 $2$。

第一种情况比较简单，如果 $b_i$ 和 $b_{i+1}$ 同时为 $1$，那么便清零并令 $b_{i+2}$ 为 $1$（把此称为进位）。显然连续进位必须满足这段区间是交替的 $1$ 和 $0$。

第二种情况差不多，注意到 $2F_i=F_{i-2}+F_{i+1}$，此时如果 $b_{i-2}$ 为 $1$ 则将变为 $2$，于是继续拆分（把此称为反向进位或者“退位”）。显然连续退位也得满足这段区间是交替的 $1$ 和 $0$。

此时就有了一个天然的想法：平衡树维护交替 $1$ 和 $0$ 的区间，查询时注意到方程形式很好，所以 DDP，用矩阵乘起来。

这时候就做完了，但是不妨说细一点。

首先是如果一段交替 $1$ 和 $0$ 的区间中间有一个变成了 $2$，放个例子：
$$
\begin{aligned}
0\quad0\quad1\quad0\quad1\quad0\quad1\quad0\quad2\quad0\quad1\quad0\quad1\quad0\quad1\quad0\quad0\\
0\quad0\quad1\quad0\quad1\quad0\quad2\quad0\quad0\quad1\quad1\quad0\quad1\quad0\quad1\quad0\quad0\\
0\quad0\quad1\quad0\quad2\quad0\quad0\quad1\quad0\quad0\quad0\quad1\quad1\quad0\quad1\quad0\quad0\\
0\quad0\quad2\quad0\quad0\quad1\quad0\quad1\quad0\quad0\quad0\quad0\quad0\quad1\quad1\quad0\quad0\\
1\quad0\quad0\quad1\quad0\quad1\quad0\quad1\quad0\quad0\quad0\quad0\quad0\quad0\quad0\quad1\quad0
\end{aligned}
$$
左侧 $2$ 不断退位，而第一次退位产生的 $1$ 又导致右侧不断进位，最后整个区间断成了三截。最左一截和最右一截是孤立的 $1$，中间一截则是交替的 $1$ 和 $0$。

其次是假设这段交替 $1$ 和 $0$ 的区间中 $1$ 的个数为 $x$，距离上一个区间中间夹了 $y$ 个零，这段区间 DP 状态是 $f_{0/1}$，上一段是 $g_{0/1}$，那么有方程：
$$\begin{cases}f_0=(x\lfloor\frac y2\rfloor+1)g_0+(x\lfloor\frac{y+1}2\rfloor+1)g_1\\f_1=\lfloor\frac y2\rfloor g_0+\lfloor\frac{y+1}2\rfloor g_1\end{cases}$$
只需要 $2\times2$ 的矩阵转移即可。

最后请记得分讨比较恶心，有各种细节，不要写错了。

---

## 作者：Add_Catalyst (赞：1)

# P6361 [CEOI 2018] Fibonacci representations 题解

------

## 知识点

Fibonacci 数列，平衡树，齐肯多夫定理，连续段 DP，矩阵优化 DP，动态 DP。

## 分析

### 定义

- > 为方便，我们学习一下[大佬](https://www.luogu.com.cn/user/104726)的[表示形式](https://www.luogu.com.cn/article/dhmaeuag)：
  > $$
  > \begin{matrix}
  > b_1 & b_2 & \ldots & b_{k-1} & b_k & b_{k+1} & \ldots \\
  > 1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots \\
  > \end{matrix}
  > $$
  > 表示：
  > $$
  > p = \sum_{i} b_i \cdot F_{i} \\
  > $$

- 定义 $F_{n+2}$ 的分裂：变为 $F_{n} + F_{n+1}$。

### 引入

我们从题目给定的条件考虑一下，很明显，有一种**逐个插入**的意味，那么我们就可以从这个角度来思考。

### 分裂

既然是逐个插入，就必定有最简单的只有一种的情况，我们先来看看这种：
$$
\begin{matrix}
0 & 0 & \ldots & 0 & 1 & 0 & \ldots \\
1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots \\
\end{matrix}
$$
它在过程中一直符合题目要求的前提（没有重复的斐波那契数）下可以如何分裂？

- 分裂一次：
  $$
  \begin{matrix}
  0 & 0 & \ldots & 1 & 1 & 0 & \ldots \\
  1 & 2 & \ldots & {k-2} & {k-1} & {k} & \ldots \\
  \end{matrix}
  $$
  似乎没什么。

- 分裂两次：
  $$
  \begin{matrix}
  0 & 0 & \ldots & 1 & 1 & 0 & 1 & \ldots \\
  1 & 2 & \ldots & {k-4} & {k-3} & {k-2} & {k-1} & \ldots \\
  \end{matrix}
  $$
  发现一个问题：如果我们把 $k-1$ 对应的 $1$ 去掉，就又变成了“分裂一次”的情况。

- 分裂 $n$ 次……

所以我们可以得出结论：一个斐波那契数分裂过程中，在所有它分裂出来的数中，只有最小的那个可以再分裂。

那么这种情况的答案就很简单，为 $\lfloor \frac{k-1}{2} \rfloor + 1$。

### 去重

我们紧接着再看下一步，插入第二个，我们可以粗略分成两种：

- 插入的第二个与第一个不同：
  $$
  \begin{matrix}
  0 & 0 & \ldots & 0 & 1 & 0 & \ldots & 0 & 1 & 0 & \ldots \\
  1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots & {m-1} & m & {m+1} & \ldots \\
  \end{matrix}
  $$
  感觉这种仍旧是没什么……

- 插入的第二个与第一个相同：
  $$
  \begin{matrix}
  0 & 0 & \ldots & 0 & 2 & 0 & \ldots \\
  1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots \\
  \end{matrix}
  $$
  似乎两个相同的不是很好，这样分解起来不如上面舒畅。

这种有相同的就不便于分解，所以我们尝试让它分裂：

$$
\
\begin{matrix}
0 & 0 & \ldots & 0 & 2 & 0 & \ldots \\
1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots \\
\end{matrix} \\
\Downarrow \\
\begin{matrix}
0 & 0 & \ldots & 1 & 1 & 1 & 0 & \ldots \\
1 & 2 & \ldots & {k-2} & {k-1} & k & {k+1} & \ldots \\
\end{matrix} \\
$$
考虑上面的性质，我们可以联想到：是不是对于任何正整数，都有一种把它表示成**不同** Fibonacci 数的和方案呢？

答案是肯定的。

### 合并

分裂后发现还有两个可以合并，我们再把它们合起来，最终得到：
$$
\begin{matrix}
0 & 0 & \ldots & 1 & 0 & 0 & 1 & \ldots \\
1 & 2 & \ldots & {k-2} & {k-1} & k & {k+1} & \ldots \\
\end{matrix} \\
$$
从这个现象，以及上一步中我们得到的结论，又可以进一步猜想：是不是对于任何正整数，都有一种把它表示成不同且**互不相邻**的斐波那契数的和的方案呢？

答案还是肯定的，这个就是**齐肯多夫（Zeckendorf）定理**的一部分，具体证明可以百度。

> 完整的齐肯多夫定理是：
>
> 任何正整数都可以表示成若干个不连续的斐波那契数（不包括第一个斐波那契数，**即本题中不存在的那个 $F_0$**）之和。这种和式称为**齐肯多夫表述法**。
>
> 对于任何正整数，其齐肯多夫表述法都可以由贪心算法（即每次选出最大可能的斐波那契数）得到。
>
> ——[齐肯多夫定理_百度百科 (baidu.com)](https://baike.baidu.com/item/齐肯多夫定理/7612155)。

### DP 设计

发现对于 $p$，它的齐肯多夫表述法可以让我们对它求出本题答案：

- 设 $p$ 的齐肯多夫表述法按升序排序后为 $\set{Z_i}$，共有 $m$ 项。
- 设 $f_{i,0/1}$ 分别表示 $Z_i$ 有没有分裂时的方案数，$0$ 代表没有，$1$ 代表有。
- 设 $\Delta_i = Z_i-Z_{i-1}(i>1)$，特别地，$i=1$ 时 $\Delta_1 = Z_1$。

那么就有初态和方程：
$$
f_{0,0} = 1,f_{0,1} = 0 \\
\begin{cases}
f_{i,0} = f_{i-1,0} + f_{i-1,1} \\
f_{i,1} = 
\lfloor \frac{\Delta_i - 1}{2} \rfloor f_{i-1,0} 
+ \lfloor \frac{\Delta_i}{2} \rfloor f_{i-1,1} \\
\end{cases}
$$
最终答案即为 $f_{m,0} + f_{m,1}$。

我们可以用矩阵表示：
$$
\begin{bmatrix}
1 & 1 \\
\lfloor \frac{\Delta_i - 1}{2} \rfloor& \lfloor \frac{\Delta_i}{2} \rfloor\\
\end{bmatrix}
\begin{bmatrix}
f_{i-1,0} \\
f_{i-1,1} \\
\end{bmatrix}
=
\begin{bmatrix}
f_{i,0} \\
f_{i,1} \\
\end{bmatrix}
$$
（我们直接把这个塞到平衡树中就可以拿到子任务 3 和 5 的分数。）

### 动态维护

我们现在已经有了有静态的齐肯多夫表述法集合，考虑维护支持插入的动态的齐肯多夫表述法集合。

假设现在要在原**齐肯多夫表述法集合 $Z$** 插入第 $k$ 个斐波那契数。

- 原集合中不包含第 $k-1,k,k+1$ 个斐波那契数。
  $$
  \begin{matrix}
  b_{1} & b_{2} & \ldots & 0 & 0 & 0 & \ldots \\
  1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots \\
  \end{matrix}
  $$
  直接加入即可。

- 原集合中包含第 $k+1$ 个斐波那契数。
  $$
  \begin{matrix}
  b_{1} & b_{2} & \ldots & b_{k-1} & 0 & 1 & \ldots \\
  1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots \\
  \end{matrix}
  $$
  那么我们不断往后合并 ~~，总有一天会合并完的~~。

- 原集合中不包含第 $k+1$ 个斐波那契数，但是包含第 $k-1$ 个。
  $$
  \begin{matrix}
  b_{1} & b_{2} & \ldots & 1 & 0 & 0 & \ldots \\
  1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots \\
  \end{matrix}
  $$
  那么我们不断往后合并 ~~，总有一天会合并完的~~。

- 原集合中包含第 $k$ 个斐波那契数。
  $$
  \begin{matrix}
  b_{1} & b_{2} & \ldots & 0 & 1 & 0 & \ldots \\
  1 & 2 & \ldots & {k-1} & k & {k+1} & \ldots \\
  \end{matrix}
  $$
  这种情况有点特殊，想象一下我们把第 $k$ 个分裂成 $k-1$ 和 $k-2$ 后，发现原本就有一个 $k-2$ 存在，这该怎么办？

  设 $q$ 满足以下条件：

  1. $q \equiv k\pmod 2$。
  2. $\forall i \in [1,\frac{k-q}{2}],(k-2i)\in Z$。
  3. $q$ 是所有满足条件 1 和 2 的值中最小的那个。

  又分两种情况：

  - $q>2$：

    会变成：
    $$
    \begin{matrix}
    b_{1} & b_{2} & \ldots & 1 & 0 & 0 & 1 & \ldots & 1 & 0 & 1 & \ldots \\
    1 & 2 & \ldots & q-2 & q-1 & q & q+1 & \ldots & {k-1} & k & {k+1} & \ldots \\
    \end{matrix}
    $$
    但是这个并不能像上面一样暴力地修改……

    考虑矩阵转移，发现其只由该值和上一个值的差值 $\Delta$ 决定，而整个序列改变差值的或插入的最多只有 $3$ 个，即：

    1. 插入一个 $q-2$。
    2. $q(\to q+1)$ 的差值可能改变。
    3. $k+1$ 后面的差值会改变。

  - $q = 1$：我们把插入的 $k$ 不断分裂，得到：
    $$
    \begin{matrix}
    2 & 1 & 1 & \ldots & 1 & 1 & 0 & \ldots \\
    1 & 2 & 3 & \ldots & {k-1} & k & {k+1} & \ldots \\
    \end{matrix}
    $$
    再从后面逐个合并，又会得到：
    $$
    \begin{matrix}
    0 & 1 & 0 & \ldots & 1 & 0 & 1 & \ldots \\
    1 & 2 & 3 & \ldots & {k-1} & k & {k+1} & \ldots \\
    \end{matrix}
    $$
    修改其实是一样修改差值的思路：

    1. $1(\to 2)$ 的差值会改变。
    2. $k+1$ 后面的差值会改变。

  - $q = 2$：同理可得：
    $$
    \begin{matrix}
    1 & 0 & 1 & \ldots & 1 & 0 & 1 & \ldots \\
    1 & 2 & 3 & \ldots & {k-1} & k & {k+1} & \ldots \\
    \end{matrix}
    $$
    修改：

    1. 插入一个 $1$。
    2. $k+1$ 后面的差值会改变。

  如果原本还存在 $k+2$ 的话，只要在此基础上再处理一下即可。

## 实现方式

用平衡树中维护一些差值为 $2$ 的连续段即可实现动态维护。

中间的一些情况处理完之后会变成其他情况，所以我们可以用递归的形式实现。

那么转换成连续段后，每个转移矩阵的值需要重新定义：假设**一个连续段与上一个中间有 $\Delta$ 个 $0$**，共包含 $c$ 个 $1$，则矩阵变为：
$$
\
\begin{bmatrix}
1 & 1 \\
0 & 1 \\
\end{bmatrix}^{c-1}
\begin{bmatrix}
1 & 1 \\
\lfloor \frac{\Delta}{2} \rfloor & \lfloor \frac{\Delta + 1}{2} \rfloor\\
\end{bmatrix} \\
=
\begin{bmatrix}
1 & c-1 \\
0 & 1 \\
\end{bmatrix}
\begin{bmatrix}
1 & 1 \\
\lfloor \frac{\Delta}{2} \rfloor & \lfloor \frac{\Delta + 1}{2} \rfloor\\
\end{bmatrix} \\
=
\begin{bmatrix}
(c-1)\lfloor \frac{\Delta}{2} \rfloor+1 & (c-1)\lfloor \frac{\Delta + 1}{2} \rfloor+1 \\
\lfloor \frac{\Delta}{2} \rfloor & \lfloor \frac{\Delta + 1}{2} \rfloor\\
\end{bmatrix}
$$
或者按照实际意义也可推得。

### 复杂度

那么暴力合并的均摊次数也就是 $O(n)$ 的，其他修改单次次数也较少，则复杂度为 $O(nw^3\log_2{n})$，其中 $w=2$。

## 代码

```cpp
//#define Plus_Cat "fib"
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define uint unsigned int
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define FOR(i,a,b) for(int i(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i(a);i>=(int)(b);--i)
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define EDGE(g,i,x,y) for(int i=(g).h[(x)],y=(g)[(i)].v;~i;y=(g)[(i=(g)[i].nxt)>0?i:0].v)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);return Main();}signed Main
using namespace std;
constexpr int N(1e5+10);

namespace IOE {
	//Fast IO...
} using namespace IOE;

namespace Modular {
	//Modular
} using namespace Modular;

int n;
mt19937 rng(random_device {}());

struct Mat {
	int d[4];

	Mat(int val=0) { d[0]=d[3]=val,d[1]=d[2]=0; }

	Mat(int d0,int d1,int d2,int d3) { d[0]=d0,d[1]=d1,d[2]=d2,d[3]=d3; }

	Mat(int del,int cnt) {
		int a(del>>1),b((del+1)>>1);
		--cnt,d[0]=add(mul(cnt,a),1),d[1]=add(mul(cnt,b),1),d[2]=a,d[3]=b;
	}

	int &operator [](int i) { return d[i]; }

	int const &operator [](int i) const { return d[i]; }

	friend Mat operator *(const Mat &A,const Mat &B) {
		return Mat(
			(int)add(mul(A[0],B[0]),mul(A[1],B[2])),(int)add(mul(A[0],B[1]),mul(A[1],B[3])),
			(int)add(mul(A[2],B[0]),mul(A[3],B[2])),(int)add(mul(A[2],B[1]),mul(A[3],B[3]))
		);
	}
};

struct Treap {
	int rt,tot;
	struct node {
		int sta,cnt,lst;
		Mat sel,pro;
		int ls,rs;
		uint blc;
		node(int sta=0,int cnt=0,int lst=0,Mat sel=Mat(1),Mat pro=Mat(1),int ls=0,int rs=0,uint blc=rng()):
			sta(sta),cnt(cnt),lst(lst),sel(sel),pro(pro),ls(ls),rs(rs),blc(blc) {}
		void Update(int _lst) { lst=sta?sta-2+(cnt<<1):0,pro=sel=Mat(sta-_lst-1,cnt); }
	} tr[N];

	Treap():rt(0),tot(0) {}
#define ls(p) (tr[p].ls)
#define rs(p) (tr[p].rs)
	void Init() { tr[rt=tot=1]=node(0,1,0); }

	void Up(int p) {
		tr[p].lst=(rs(p)?tr[rs(p)].lst:(tr[p].sta?tr[p].sta-2+(tr[p].cnt<<1):0));
		tr[p].pro=tr[p].sel;
		if(ls(p))tr[p].pro=tr[p].pro*tr[ls(p)].pro;
		if(rs(p))tr[p].pro=tr[rs(p)].pro*tr[p].pro;
	}

	int Merge(int p,int q) {
		if(!p||!q)return p|q;
		if(tr[p].blc<=tr[q].blc)
			return tr[p].lst=tr[q].lst,tr[p].pro=tr[q].pro*tr[p].pro,rs(p)=Merge(rs(p),q),p;
		return tr[q].pro=tr[q].pro*tr[p].pro,ls(q)=Merge(p,ls(q)),q;
	}

	int Split(int &p,int key) { //[<=key] -> p,[>key] -> o
		if(!p)return 0;
		int o(0);
		if(key<tr[p].sta)return o=Split(ls(p),key),o^=ls(p)^=o^=ls(p),p^=o^=p^=o,Up(o),o;
		if(key==tr[p].sta)return o=rs(p),rs(p)=0,Up(p),o;
		return o=Split(rs(p),key),Up(p),o;
	}

	int Split_begin(int &p) {
		int o(0);
		if(ls(p))return o=Split_begin(ls(p)),Up(p),o;
		return o=p,p=rs(p),rs(o)=0,Up(o),o;
	}

	int Split_end(int &p) {
		int o(0);
		if(rs(p))return o=Split_end(rs(p)),Up(p),o;
		return o=p,p=ls(p),ls(o)=0,Up(o),o;
	}

	int Cal() { return add(tr[rt].pro[0],tr[rt].pro[2]); }

	void Link(int &p,int &q) {
		int o(q);
		q=Split(o,tr[p].sta+(tr[p].cnt<<1));
		if(o)tr[p].cnt+=tr[o].cnt;
		tr[p].Update(tr[rt].lst),rt=Merge(rt,p);
		if(q)tr[o=Split_begin(q)].Update(tr[rt].lst),rt=Merge(rt,Merge(o,q));
	}

	void Insert(int key) {
		int p(Split(rt,key)),q(Split(p,key+1));
		if(p)return tr[p].sta=tr[p].lst+1,tr[p].cnt=1,Link(p,q);
		if((rt==1&&!rs(rt))||key>tr[rt].lst+2)return tr[p=++tot].sta=key,tr[p].cnt=1,Link(p,q);
		if(tr[p=Split_end(rt)].lst+2==key)return ++tr[p].cnt,Link(p,q);
		if((key-tr[p].sta)&1) {
			if(key!=tr[p].lst+1)
				tr[p].cnt=(key+1-tr[p].sta)>>1,key=tr[p].lst+1,tr[p].Update(tr[rt].lst),rt=Merge(rt,p);
			else if(++key,tr[p].cnt>1)--tr[p].cnt,tr[p].Update(tr[rt].lst),rt=Merge(rt,p);
			return p=q,q=Split(p,key+1),(p?tr[p].sta=tr[p].lst+1:tr[p=++tot].sta=key),tr[p].cnt=1,Link(p,q);
		}
		if(key==tr[p].lst) {
			if(tr[p].sta>2)return key=tr[p].sta-2,++tr[p].sta,Link(p,q),Insert(key);
			if(tr[p].sta==1)return tr[p].sta=2,Link(p,q);
			return tr[p].sta=1,++tr[p].cnt,Link(p,q);
		}
		int o(++tot);
		tr[o].sta=tr[p].lst+1,tr[o].cnt=1,tr[p].cnt=(key-tr[p].sta)>>1;
		if(tr[p].sta>2) {
			key=tr[p].sta-2,++tr[p].sta;
			if(tr[p].cnt)tr[p].Update(tr[rt].lst),rt=Merge(rt,p);
			return Link(p=o,q),Insert(key);
		}
		if(tr[p].sta==2)return tr[p].sta=1,++tr[p].cnt,tr[p].Update(tr[rt].lst),rt=Merge(rt,p),Link(p=o,q);
		tr[p].sta=2;
		if(tr[p].cnt)return tr[p].Update(tr[rt].lst),rt=Merge(rt,p),Link(p=o,q);
		return Link(p=o,q);
	}
#undef ls
#undef rs
} trp;

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	I(n),trp.Init();
	while(n--) {
		int key;
		I(key),trp.Insert(key),O(trp.Cal(),'\n');
	}
	return 0;
}
```

------

---

## 作者：Leasier (赞：1)

注意到结论：所有自然数都可以对于于某种唯一的斐波那契拆分。

形式化地，对于所有正整数 $n$，都可以将其唯一地表示为 $n = \displaystyle\sum_{i = 1}^m F_{a_i}$，其中 $a_i$ 均为正整数且 $\forall 1 \leq i < m, a_i \leq a_{i + 1} - 2$。证明略去。

考虑在知道拆分方式的前提下计数。显然每个 $F_{a_i}$ 可以选择拆或不拆，若拆则拆后最大项必为 $F_{a_i - 1}$。

考虑 dp，设 $dp_{i, 0/1}$ 表示不拆 / 拆 $F_{a_i}$ 时 $\displaystyle\sum_{j = 1}^i F_{a_j}$ 的拆分方案数。

初值：$dp_{0, 0} = 1, dp_{0, 1} = 0$。

转移：$dp_{i, 0} = dp_{i - 1, 0} + dp_{i - 1, 1}$，$dp_{i, 1} = \lfloor \frac{a_i - a_{i - 1} - 1}{2} \rfloor dp_{i - 1, 0} + \lfloor \frac{a_i - a_{i - 1}}{2} \rfloor dp_{i - 1, 1}$。

答案：$dp_{m, 0} + dp_{m, 1}$。

对于 Subtask 5，注意到 $a_i$ 两两不重复且不相邻，则它们恰好构成一组合法拆分，于是我们平衡树上 ddp 即可。时间复杂度为 $O(n \log n)$。

- **写 Treap 的 `merge` 时要注意不要把实际维护的值和随机堆的权值搞混了，否则会真·Treap 成链！！！**

接下来考虑如何维护一组合法拆分，下面以插入 $F_a$ 为例。

首先是三种比较简单的情况：

- $F_a, F_{a + 1}, F_{a - 1}$ 均不存在：直接插入 $F_a$ 即可。
- $F_a$ 不存在，$F_{a + 1}$ 存在：删去原来的 $F_{a + 1}$ 并插入 $F_{a + 2}$ 即可。
- $F_a, F_{a + 1}$ 不存在，$F_{a - 1}$ 存在：删去原来的 $F_{a - 1}$ 并插入 $F_{a + 1}$ 即可。

但注意到 $F_a$ 可能本来就有（事实上上面插入 $F_{a + 2}, F_{a + 1}$ 的情况也会存在这个问题），怎么办呢？

首先特判掉 $a = 1$ 的情况。考虑把 $2F_a$ 拆成 $F_{a - 2} + F_{a + 1}$，但此时 $F_{a - 2}$ 可能本来就有，而且这个情况可以递归下去，于是直接递归下去处理的时间复杂度不太对，那怎么办呢？

手玩一下会发现，上面的过程可以描述为：

- 设 $x$ 表示最大 $x$ 满足 $(a - x) \bmod 2 = 0$ 且 $F_{x - 2}$ 不存在。
- $\forall b \in [x, a]$ 且 $F_b$ 本来就有，删去 $F_b$ 并插入 $F_{b + 1}$。
- 插入 $F_{x - 2}$。

也就是说，这个过程实际上相当于本来就有的值的平移。注意到在前面的 dp 中，我们事实上只关心一个数与其前驱的差，考虑在平衡树上维护差分，找 $x$ 的过程可以在平衡树上二分，每次修改后更新一遍边界即可。

需要注意的是 $x$ 可能不存在，此时满足 $F_1, F_3, \cdots, F_a$ 或 $F_2, F_4, \cdots, F_a$ 都存在，特殊处理一下边界即可。

时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef struct {
	int a00;
	int a01;
	int a10;
	int a11;
} Matrix;

typedef struct {
	int ls;
	int rs;
	int size;
	int add;
	int diff;
	int real_val;
	int max_val_pos;
	int max_diff;
	int heap_val;
	Matrix mat;
	Matrix prod;
} Node;

const int mod = 1e9 + 7;

Matrix operator *(Matrix &a, Matrix &b){
	Matrix ans;
	ans.a00 = (1ll * a.a00 * b.a00 + 1ll * a.a01 * b.a10) % mod;
	ans.a01 = (1ll * a.a00 * b.a01 + 1ll * a.a01 * b.a11) % mod;
	ans.a10 = (1ll * a.a10 * b.a00 + 1ll * a.a11 * b.a10) % mod;
	ans.a11 = (1ll * a.a10 * b.a01 + 1ll * a.a11 * b.a11) % mod;
	return ans;
}

void operator *=(Matrix &a, Matrix &b){
	a = a * b;
}

inline int add(int x, int y){
	return x + y >= mod ? x + y - mod : x + y;
}

namespace Treap {
	int id = 0, root = 0;
	Node tree[100007];
	stack<int> s;
	
	inline void pushdown(int x){
		if (tree[x].add != 0){
			int ls = tree[x].ls, rs = tree[x].rs;
			if (ls != 0){
				tree[ls].add += tree[x].add;
				tree[ls].real_val += tree[x].add;
			}
			if (rs != 0){
				tree[rs].add += tree[x].add;
				tree[rs].real_val += tree[x].add;
			}
			tree[x].add = 0;
		}
	}
	
	inline void update(int x){
		int ls = tree[x].ls, rs = tree[x].rs;
		tree[x].size = 1;
		tree[x].max_diff = tree[x].diff;
		if (ls == 0){
			tree[x].prod = tree[x].mat;
		} else {
			tree[x].size += tree[ls].size;
			tree[x].max_diff = max(tree[x].max_diff, tree[ls].max_diff);
			tree[x].prod = tree[ls].prod * tree[x].mat;
		}
		if (rs == 0){
			tree[x].max_val_pos = x;
		} else {
			tree[x].size += tree[rs].size;
			tree[x].max_diff = max(tree[x].max_diff, tree[rs].max_diff);
			tree[x].max_val_pos = tree[rs].max_val_pos;
			tree[x].prod *= tree[rs].prod;
		}
	}
	
	void split_by_val(int x, int &y, int &z, int k){
		if (x == 0){
			y = z = 0;
			return;
		}
		pushdown(x);
		if (tree[x].real_val <= k){
			y = x;
			split_by_val(tree[x].rs, tree[x].rs, z, k);
		} else {
			z = x;
			split_by_val(tree[x].ls, y, tree[x].ls, k);
		}
		update(x);
	}
	
	inline int new_node(int x){
		int ans;
		if (!s.empty()){
			ans = s.top();
			s.pop();
		} else {
			ans = ++id;
		}
		tree[ans].ls = tree[ans].rs = tree[ans].add = 0;
		tree[ans].size = 1;
		tree[ans].real_val = x;
		tree[ans].max_val_pos = ans;
		tree[ans].heap_val = rand();
		return ans;
	}
	
	int merge(int x, int y){
		if (x == 0) return y;
		if (y == 0) return x;
		pushdown(x);
		pushdown(y);
		if (tree[x].heap_val < tree[y].heap_val){
			tree[x].rs = merge(tree[x].rs, y);
			update(x);
			return x;
		}
		tree[y].ls = merge(x, tree[y].ls);
		update(y);
		return y;
	}
	
	void split_by_size(int x, int &y, int &z, int k){
		if (x == 0){
			y = z = 0;
			return;
		}
		pushdown(x);
		if (tree[tree[x].ls].size < k){
			y = x;
			split_by_size(tree[x].rs, tree[x].rs, z, k - tree[tree[x].ls].size - 1);
		} else {
			z = x;
			split_by_size(tree[x].ls, y, tree[x].ls, k);
		}
		update(x);
	}
	
	int find1(int x, int k){
		if (x == 0) return 0;
		pushdown(x);
		if (k < tree[x].real_val) return find1(tree[x].ls, k);
		if (k == tree[x].real_val) return x;
		return find1(tree[x].rs, k);
	}
	
	inline bool count(int x){
		return find1(root, x) != 0;
	}
	
	inline void search(int x, int &ans){
		int ls = tree[x].ls, rs = tree[x].rs;
		pushdown(x);
		if (rs != 0 && tree[rs].max_diff > 2){
			ans += tree[ls].size + 1;
			search(rs, ans);
			return;
		}
		if (tree[x].diff > 2){
			ans += tree[ls].size + 1;
			return;
		}
		if (ls != 0 && tree[ls].max_diff > 2){
			search(ls, ans);
			return;
		}
		ans = -1;
	}
	
	int find2(int x, int k){
		if (x == 0) return 0;
		pushdown(x);
		if (k <= tree[tree[x].ls].size) return find2(tree[x].ls, k);
		k -= tree[tree[x].ls].size;
		if (k == 1) return x;
		return find2(tree[x].rs, k - 1);
	}
	
	inline int get_val(int k){
		return tree[find2(root, k)].real_val;
	}
	
	inline void add(int l, int r, int k){
		int y, z, w;
		split_by_size(root, y, z, l - 1);
		split_by_size(z, z, w, r - l + 1);
		tree[z].add += k;
		tree[z].real_val += k;
		root = merge(y, merge(z, w));
	}
	
	inline int query(){
		return ::add(tree[root].prod.a00, tree[root].prod.a01);
	}
}

inline Matrix make(int x){
	Matrix ans;
	ans.a00 = ans.a10 = 1;
	ans.a01 = (x - 1) / 2;
	ans.a11 = x / 2;
	return ans;
}

inline void do_remove(int x){
	int y, z, u;
	Treap::split_by_val(Treap::root, y, z, x - 1);
	Treap::split_by_val(z, z, u, x);
	Treap::s.push(z);
	if (u != 0){
		int v;
		Treap::split_by_size(u, u, v, 1);
		Treap::tree[u].diff = Treap::tree[u].max_diff = Treap::tree[u].real_val - Treap::tree[Treap::tree[y].max_val_pos].real_val;
		Treap::tree[u].mat = Treap::tree[u].prod = make(Treap::tree[u].diff);
		u = Treap::merge(u, v);
	}
	Treap::root = Treap::merge(y, u);
}

inline void do_insert(int x){
	int y, z, u;
	Treap::split_by_val(Treap::root, y, z, x - 1);
	Treap::split_by_val(z, z, u, x);
	if (z == 0) z = Treap::new_node(x);
	Treap::tree[z].diff = Treap::tree[z].max_diff = x - Treap::tree[Treap::tree[y].max_val_pos].real_val;
	Treap::tree[z].mat = Treap::tree[z].prod = make(Treap::tree[z].diff);
	if (u != 0){
		int v;
		Treap::split_by_size(u, u, v, 1);
		Treap::tree[u].diff = Treap::tree[u].max_diff = Treap::tree[u].real_val - x;
		Treap::tree[u].mat = Treap::tree[u].prod = make(Treap::tree[u].diff);
		u = Treap::merge(u, v);
	}
	Treap::root = Treap::merge(y, Treap::merge(z, u));
}

inline void release(int x){
	int y, z, u;
	Treap::split_by_val(Treap::root, y, z, x - 1);
	Treap::split_by_val(z, z, u, x);
	Treap::tree[z].diff = Treap::tree[z].max_diff = x - Treap::tree[Treap::tree[y].max_val_pos].real_val;
	Treap::tree[z].mat = Treap::tree[z].prod = make(Treap::tree[z].diff);
	if (u != 0){
		int v;
		Treap::split_by_size(u, u, v, 1);
		Treap::tree[u].diff = Treap::tree[u].max_diff = Treap::tree[u].real_val - x;
		Treap::tree[u].mat = Treap::tree[u].prod = make(Treap::tree[u].diff);
		u = Treap::merge(u, v);
	}
	Treap::root = Treap::merge(y, Treap::merge(z, u));
}

inline void insert(int a){
	if (!Treap::count(a)){
		if (Treap::count(a + 1)){
			do_remove(a + 1);
			insert(a + 2);
		} else if (a > 1 && Treap::count(a - 1)){
			do_remove(a - 1);
			insert(a + 1);
		} else {
			do_insert(a);
		}
	} else if (a == 1){
		do_remove(1);
		insert(2);
	} else {
		int x, y, rank, pos = 0;
		Treap::split_by_val(Treap::root, x, y, a);
		rank = Treap::tree[x].size;
		Treap::search(x, pos);
		Treap::root = Treap::merge(x, y);
		if (pos == -1){
			Treap::add(1, rank, 1);
			if (!Treap::count(a + 2)){
				release(a + 1);
			} else {
				do_remove(a + 1);
				do_remove(a + 2);
				insert(a + 3);
			}
			if (a % 2 == 0) do_insert(1);
			return;
		}
		int val = Treap::get_val(pos);
		Treap::add(pos, rank, 1);
		release(val + 1);
		if (!Treap::count(a + 2)){
			release(a + 1);
		} else {
			do_remove(a + 1);
			do_remove(a + 2);
			insert(a + 3);
		}
		insert(val - 2);
	}
}

int main(){
	int n;
	scanf("%d", &n);
	srand(time(NULL));
	for (register int i = 1; i <= n; i++){
		int a;
		scanf("%d", &a);
		insert(a);
		printf("%d\n", Treap::query());
	}
	return 0;
}
```

---

## 作者：Larunatrecy (赞：0)

首先考虑只有 $F_n$ 一个数时怎么拆分：$F_n\to F_{n-1},F_{n-2}$，注意到此时如果拆 $F_{n-1}$ 那么无论如何最后都不可能让每个数最多出现一次，因此只会拆 $F_{n-2}$，然后 $F_{n-1},F_{n-2}\to F_{n-1},F_{n-3},F_{n-4}……$，一共有 $\lfloor \frac{n+1}{2}\rfloor$ 种不同的拆法。

现在假设不止一个数，并且满足：

- 任意两个不相同。
- 任意两个不相邻。

那么可以用类似上述的过程证明只有拆分没有合并，因此排序之后每一段是独立的，而第 $i$ 段的长度只和第 $i-1$ 个位置是否拆分有关，那么可以有一个 DP 为 $f_{i,0/1}$ 表示前 $i$ 个位置，第 $i$ 个是否拆分的方案数，转移可以写成简单的矩阵乘法，用平衡树维护矩阵连乘可以做到 $O(n\log n)$。

对于一般的情况，我们考虑通过一些变换变成上面的样子。

我们知道有个东西叫做斐波那契表示，即每个数可以唯一表示为上述的形态，现在考虑动态维护加入数 $x$ 的过程：

- 如果 $x-1,x,x+1$ 都没有出现，那么直接加入就好了。
- 如果 $x$ 没有出现，那么可以把 $x-1,x$ 或者 $x,x+1$ 合并起来，然后向 $x+1$ 递归，因为一个数只会被删除一次，所以均摊正确。
- 如果 $x$ 出现了，那么需要把一个 $x$ 拆分成 $x-2,x-1$，然后继续向左拆分，接着再从右到左依次合并，通过分析可以发现，如果设 $l$ 是满足 $l,l+2,l+4……,x-4,x-2,x$ 都存在的最小的 $l$，那么做完之后会变成 $l-2,l+1,l+3……x-3,x-1,x+1$，可以在平衡树上二分找到 $l$，然后平移一位，方便起见只需要维护相邻两个位置的差分。这里细节很多，因为需要特判 $l\leq 2$ 的情况，并且平移之后有可能和前面或者后面的段合并，递归进行即可，只会进行 $O(1)$ 次。

所以总复杂度均摊 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>inline void read(T &x)
{
    x=0;char c=getchar();bool f=0;
    for(;c<'0'||c>'9';c=getchar())f|=(c=='-');
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c-'0');
    x=(f?-x:x);
}
typedef long long LL;
const int mod = 1e9+7;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int mul(int a,int b){return 1ll*a*b%mod;}
struct mat
{
    LL w[2][2];
    mat()
    {
        w[0][0]=w[1][1]=w[1][0]=w[0][1]=0;
    }
    void init()
    {
        w[0][0]=w[1][1]=1;
        w[1][0]=w[0][1]=0;
    }
};
mat operator *(mat A,mat B)
{
    mat C;
    for(int k=0;k<2;k++)
    for(int i=0;i<2;i++)
    for(int j=0;j<2;j++)
    C.w[i][j]=add(C.w[i][j],1ll*A.w[i][k]*B.w[k][j]%mod);
    return C;
}
const int N = 5e5+7;
struct node
{
    mat F,W;
    int l,r;
    int val,key,siz,sum,mx,mn;
    #define mx(x) tr[x].mx
    #define mn(x) tr[x].mn
    #define sum(x) tr[x].sum
    #define F(x) tr[x].F
    #define W(x) tr[x].W
    #define l(x) tr[x].l
    #define r(x) tr[x].r
    #define val(x) tr[x].val
    #define key(x) tr[x].key
    #define siz(x) tr[x].siz
}tr[N];
void pushup(int k)
{
    F(k).init();
    if(l(k))F(k)=F(l(k));
    F(k)=F(k)*W(k);
    if(r(k))F(k)=F(k)*F(r(k));
    siz(k)=siz(l(k))+siz(r(k))+1;
    sum(k)=sum(l(k))+val(k)+sum(r(k));
    mx(k)=max(max(mx(l(k)),mx(r(k))),val(k));
    mn(k)=min(min(mn(l(k)),mn(r(k))),val(k));
}
int idx=0;
mat gen(int d)
{
    mat F;
    F.w[0][0]=1;
    F.w[0][1]=(d+1)/2-1;
    F.w[1][0]=1;
    F.w[1][1]=(d+2)/2-1;
    if(d==0)F.w[0][1]=0;
    return F;
}
int namestk[N],stktop=0;
int newid(int d)
{
    int k=(stktop>0?namestk[stktop--]:++idx);
    key(k)=rand();
    W(k)=gen(d);
    val(k)=d;
    l(k)=r(k)=0;
    pushup(k);
    return k;
}
int Merge(int x,int y)
{
    if(!x||!y)return x+y;
    if(key(x)<key(y))
    {
        r(x)=Merge(r(x),y);
        pushup(x);
        return x;
    }
    l(y)=Merge(x,l(y));
    pushup(y);
    return y;
}
void Split(int k,int v,int &x,int &y)
{
    if(!k)
    {
        x=y=0;
        return;
    }
    if(sum(l(k))+val(k)<=v)
    {
        x=k;
        Split(r(k),v-sum(l(k))-val(k),r(k),y);
    }
    else
    {
        y=k;
        Split(l(k),v,x,l(k));
    }
    pushup(k);
}
void Divide(int k,int rnk,int &x,int &y)
{
    if(!k)
    {
        x=y=0;
        return;
    }
    if(siz(l(k))+1<=rnk)
    {
        x=k;
        Divide(r(k),rnk-siz(l(k))-1,r(k),y);
    }
    else
    {
        y=k;
        Divide(l(k),rnk,x,l(k));
    }
    pushup(k);
}
int root=0,n;
int qryr(int x)
{
    return sum(x);
}
int stk[N],top=0;
void sigly(int x,int l)
{
    if(!x)return;
    top=0;
    while(l(x))stk[++top]=x,x=l(x);
    stk[++top]=x;
    W(x)=gen(val(x)-l);
    val(x)-=l;
    for(int i=top;i>=1;i--)pushup(stk[i]);
}
void Ins(int x)
{
    int A=0,B=0,C=0;
    Split(root,x,A,B);
    int v=qryr(A);
    int k=newid(x-v);
    sigly(B,x-v);
    root=Merge(Merge(A,k),B);
}
void Del(int x)
{
    int A=0,B=0,C=0;
    Split(root,x,root,B);
    Split(root,x-1,root,A);
    int v=qryr(root);
    sigly(B,v-x);
    namestk[++stktop]=A;
    root=Merge(root,B);
}
int get(int v)
{
    int x=root;
    while(x)
    {
        int p=sum(l(x))+val(x);
        if(p==v)return 1;
        if(p>v)x=l(x);
        else
        {
            v-=p;
            x=r(x);
        }
    }
    return 0;
}
void extend(int x)
{
    while(get(x+1))
    {
        Del(x+1);
        x+=2;
    }
    Ins(x);
}
void solve(int x)
{
    //printf("solve(%d)\n",x);
    if(x==1)
    {
        bool f1=get(x),f2=get(x+1);
        if(!f1&&!f2)
        {
            Ins(x);
            return;
        }
        if(!f1)
        {
            Del(x+1);
            solve(x+2);
            return;
        }
        Del(x);
        extend(x+1);
        return;
    }
    bool f1=get(x-1),f2=get(x),f3=get(x+1);
    //cout<<x<<' '<<f1<<' '<<f2<<' '<<f3<<endl;
    if(!f1&&!f2&&!f3)
    {
        Ins(x);
        return;
    }
    if(!f2)
    {
        if(f1)
        {
            Del(x-1);
            solve(x+1);
            return;
        }
        Del(x+1);
        solve(x+2);
        return;
    }
    if(x==2)
    {
        Del(x);
        Ins(x-1);
        solve(x+1);
        return;
    }
    int A=0,B=0,C=0;
    Split(root,x,A,B);
    int y=A,c=0;
    while(y)
    {
        if(r(y)&&!(mx(r(y))==2&&mn(r(y))==2))y=r(y);
        else
        {
            c+=siz(r(y));
            if(val(y)!=2)break;
            c++;
            y=l(y);
        }
    }
    int p=x-2*c;
    if(p==0)p=2;
    sigly(B,1);
    root=Merge(A,B);
    Split(root,p-1,A,B);
    sigly(B,-1);
    root=Merge(A,B);
    if(x-2*c==2)
    {
        Del(x+1);
        extend(x+1);
        solve(1);
        return;
    }
    if(x-2*c==1)
    {
        Del(x+1);
        solve(x+1);
        return;
    }
    if(x-2*c==0)
    {
        Del(x+1);
        extend(x+1);
        solve(1);
        return;
    }
    Del(x+1);
    extend(x+1);
    solve(p-2);
}
void Print(int x,int d)
{
    if(l(x))Print(l(x),d),d+=sum(l(x));
    d+=val(x);
    if(d==0)printf(":");
    else printf("%d ",d);
    if(r(x))Print(r(x),d);
}
int main()
{
    //freopen("a.in","r",stdin);
    read(n);
    root=newid(0);mn(0)=1e9;
    for(int i=1;i<=n;i++)
    {
        int x;
        read(x);
        solve(x);
        printf("%d\n",add(F(root).w[0][0],F(root).w[0][1]));
    }
    return 0;
}
```

---

