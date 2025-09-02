# 『JROI-5』Interval

## 题目背景

小 C 喜欢带有区间操作的数据结构，因为这样的题总会有一档好写的 $\mathcal{O}\left(n^2\right)$ 部分分。

## 题目描述


**本题读入量较大，建议使用较快的读入方式，可以参考 [赛时公告板](https://www.luogu.com.cn/paste/lueudpd5)**

小 C 有一个长度为 $n$ 的序列 $a$，第 $i$ 项为 $a_i$。

$a$ 是一个 $1\sim n$ 的排列（即 $1\sim n$ 在 $a$ 中各出现一次）。

定义 $\operatorname{Mex}_{l,r}$ 为 $\{a_l,a_{l+1},
\cdots,a_{r-1},a_r\}$ 中**没有出现过的最小正整数**。

例如，$\operatorname{Mex}\{2,3\}=1,\operatorname{Mex}\{1,2,3\}=4$。

小 C 还有一个长度为 $n$ 的数列 $f$。

定义一个区间 $\left[l,r\right]$ 是合法的当且仅当 
$$f_{r-l+1}< \operatorname{Mex}_{l,r}$$

小 C 希望你告诉他，最短的合法区间的长度是多少，特别的，如果没有区间合法，则输出 `0`。

## 说明/提示

【样例解释】

对于 #1，容易发现 $\left[1,3\right]$ 是最短的合法区间。

对于 #2，容易发现 $\left[3,3\right]$ 是最短的合法区间。

对于 #3，容易发现没有合法的区间。

---

对于 $10\%$ 的数据，满足 $1\leq n\leq 100$。

对于 $20\%$ 的数据，满足 $1\leq n\leq 1000$。

对于另外 $10\%$ 的数据，满足 $f$ 不升，即满足 $f_1\geq f_2\geq\cdots\geq f_n$，且 $1\leq n\leq 10^6$。

对于 $100\%$ 的数据，满足 $1\leq n\leq 4\times 10^6,1\leq f_i\leq 10^9$。


## 样例 #1

### 输入

```
5
2 3 1 5 4
2 2 3 4 5```

### 输出

```
3```

## 样例 #2

### 输入

```
5
2 3 1 5 4
1 2 2 4 5```

### 输出

```
1```

## 样例 #3

### 输入

```
5
1 3 4 2 5
6 7 8 9 10```

### 输出

```
0```

## 样例 #4

### 输入

```
见附件```

### 输出

```
见附件```

# 题解

## 作者：caibet (赞：12)

**更新日志**：

- 2022.3.28 发现之前自己通过多写 $6$ 行代码给算法加了个 $\log$，进行了优化。
- 2022.10.17 图挂了，改地址。
- 2023.11.7 发现这个动图不仅和一般图片同样好理解还不容易回顾和思考，因此换成了静态图。同时补充了一些描述。

**题意**：

给定两个长度为 $n$ 的数列 $a$ 和 $f$。

定义 $\text{Mex}\{l,r\}$ 为 $a$ 数列在区间 $[l,r]$ 里的元素中未出现的最小正整数。

求出最小的 $r-l+1$，使 $f_{r-l+1}<\text{Mex}\{l,r\}$。

**解法**：

容易看出 $r-l+1$ 代表了区间长度。

既然对于相同的区间长度，$f_{len}$ 的值不变，那么对于每一个长度我们可以找一找最大的 $\text{Mex}$ 值，然后与 $f$ 值进行比较。

显然，这样的贪心思路正确。接下来我们看怎么求同一个长度下最大的 $\text{Mex}$ 值。

题目告诉我们，$\text{Mex}\{l,r\}$ 为 $a$ 数列在区间 $[l,r]$ 里的元素中**未出现的最小正整数**。

那我们故意找茬，偏偏就让所有正整数依次出现，这样 $\text{Mex}$ 即可达到最大值。

但故意找茬是要吃生瓜蛋子的。如果使 $1,2,3,4,\dots ,k$ 都在区间内的最小区间长度为 $len$，那么长度不小于 $len$ 的区间的最大 $\text{Mex}$ 值才可以扩展为 $k+1$。

我们来用样例解释一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/c5bv94nh.png)

那么对于 $a=\{2,3,1,5,4\}$，我们得到了数组 $b=\{2,2,4,4,6\}$，其中 $b_i$ 表示区间长度为 $i$ 时的最大 $\text{Mex}$ 值。

由于 $\text{Mex}$ 值不断增加，所以这样覆盖对于每一个长度得到的 $\text{Mex}$ 值一定是最大的（考虑反证：如果不是最大，则最大的 $\text{Mex}$ 值一定会在之后更新这个长度）。

**优化**：

从上面可以看出，由于下划线表示的区间是被数字撑大的，所以区间大小不减，最大 $\text{Mex}$ 递增，所以 $b$ 数组单调不减。因而每次扩展区间，我们需要做的，由区间取较大值替换转换为区间覆盖。

同时可以发现，每次区间覆盖的值，也就是当前的 $\text{Mex}$ 值比前一次多一（第一次除外）。于是我们可以使用差分求和。

最后一一比较 $b_i$ 和 $f_i$ 即可。

```cpp
namespace{
	const int lim=4e6+2;
	int n,a[lim],f[lim],p[lim],b[lim],L=0x7f7f7f7f,R=0;
	void work(){
		n=read();
		F(i,1,<=n) a[i]=read(),p[a[i]]=i;//记录每个数字的位置，方便后续撑大区间时的处理
		F(i,1,<=n) f[i]=read();
		b[1]=1;//第一次实际加上了2，而程序只加了1，因此要提前设置
		F(i,1,<=n){
			L=min(L,p[i]);
			R=max(R,p[i]);//撑大区间
			++b[R-L+1];//差分加
		}
		F(i,1,<=n){
			b[i]+=b[i-1];
			if(f[i]<b[i]){//比较
				cout<<i;
				return;
			}
		}
		cout<<0;
	}
}
```

---

## 作者：蒟蒻炒扇贝 (赞：8)

这道题蛮小清新的。

------------
我们根据 $\text{Mex}_{l,r}$ 的定义，可以发现如果要满足题目要求 $f_{r-l+1} < \text{Mex}_{l,r}$ ，那么序列 $[a_l,a_{l+1},...,a_r]$ 必定拥有区间 $[1,f_{r-l+1}]$ 内的所有数。

为什么呢？想一想下面这个问题：如果我们想要构造一个序列 $b$ 使得**整个**序列的 $\text{Mex}$ 值要大于正整数 $f$ ，你会怎么构造？我们是不是会把所有**小于等于** $f$ 的正整数全部塞进这个序列里，这样这个序列~~显然~~一定是满足条件的。

那么对于这题我们就有一些思路了，从小到大枚举区间长度 $i$，每次判断这个区间长度是否合法，合法的依据便是查看在整个序列中，是否存在一个长度为 $i$ 的子序列满足条件 $p$ ：序列拥有集合 $[1,f_{i}]$ 内的所有数。

现在的任务便是如何以 $\mathop{O(1)}$ 的时间复杂度验证是否存在一个满足 $p$ 的子序列。

事实上，每次我们只需要看集合 $[1,f_i]$ 中的数字最早出现在序列 $a$ 中的位置（我们设这个位置为 $L$ ）和最晚出现在序列 $a$ 中的位置（我们设这个位置为 $R$ ）就可以了。这样我们便可以保证在序列 $[a_L,a_{L+1},...,a_R]$ 中必定拥有集合 $[1,f_i]$ 中的全部数字，且 $R-L+1$ 最小。

我们设数字 $x$ 在序列 $a$ 的下标为 $pos_{x}$，用 $qmax$ 数组维护 $pos$ 数组的前缀最大值，用 $qmin$ 维护 $pos$ 数组的前缀最小值，那么 $L=qmin_{f_i}$ 和 $R=qmax_{f_i}$ 便可以在 $\mathop{O(1)}$ 的时间复杂度内快速求出。

接下来我们判断这个区间长度是否合法，只要 $L,R$ 满足 $R-L+1\le i$ 即可。

等等，为什么条件是 $R-L+1\le i$ 而不是 $R-L+1= i$ 呢？我们回到之前构造 $b$ 序列的那个情境，想一想下面这个问题，如果往一个满足上述要求的序列 $b$ 再塞上几个数字，那进行操作之后的序列 $b$ 还能不能满足上述条件呢？当然可以，因为你向一个已经满足条件的序列 $b$ 再塞上几个数字之后，$b$ 序列整体的 $\text{Mex}$ 值肯定不会少于之前的，所以无论再往这个序列塞多少数字，这个序列依旧是合法的。

所以即使 $R-L+1<i$，我们依然可以再往这个区间塞上几个数字让区间长度等于 $i$。

总体的思路有了，那么就用代码来实现吧！代码的总时间复杂度为 $\mathop{O(n)}$。

注意要使用快读或 ```scanf```。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int x=0,fh=1;
    char ch=getchar();
    while(!isdigit(ch))
	{
        if(ch=='-') fh=-1;
        ch=getchar();
    }
    while(isdigit(ch))
	{
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*fh;
}
const int MAXN=4e6+5;
int f[MAXN],a[MAXN],n,pos[MAXN],qmin[MAXN],qmax[MAXN];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]]=i;
	for(int i=1;i<=n;i++)f[i]=read();
	qmin[0]=2e9,qmax[0]=-2e9;
	for(int i=1;i<=n;i++)qmin[i]=min(qmin[i-1],pos[i]),qmax[i]=max(qmax[i-1],pos[i]);
	for(int i=1;i<=n;i++)
	{
		if(f[i]>n)continue;
		int l=qmin[f[i]],r=qmax[f[i]];
		if(r-l+1<=i)
		{
			cout<<i;
			return 0;
		}
	}
	cout<<0;
	return 0;
}
```


---

## 作者：Cocoly1990 (赞：8)

官方题解。

**B**

考虑改写条件，根据整数的离散性，容易写为 

$$f_{r-l+1}\leq \operatorname{Mex}_{l,r}-1$$

观察到 $\operatorname{Mex}$ 存在单调性。如何理解该单调性呢？假设 $\operatorname{Mex}_{l_0,r_0}=x$，那么对于任意的 $p>l_0-r_0+1$，都存在至少一个长度为 $p$ 的区间 $\left[l_1,r_1\right]$ 使得 $\operatorname{Mex}_{l_1,r_1}\geq x$.

显然这对我们极具启发意义，与其枚举区间长度，不如枚举 $\operatorname{Mex}$，对于每个 $\operatorname{Mex}=x$，我们都可以求出最短的区间 $\left[l_0,r_0\right]$ 使得 $\operatorname{Mex}_{l_0,r_0}-1=f_{r-l+1}$，那么只要 $r_0-l_0+1\leq r-l+1$，区间 $\left[l,r\right]$ 就是合法的。

那么如何 $\mathcal{O}\left(1\right)$ 求出 $\left[l_0,r_0\right]$ 呢，容易发现，如果 $\operatorname{Mex}_{l_0,r_0} \geq x$，那么$1\sim x-1$ 必须在 $\left[l_0,r_0\right]$ 出现，所以，我们用数组记录下每个数出现的位置，做前缀 $\max,\min$ 即可快速求解。

```c++
for(int i = 1; i <= n; i ++)
	pos[a[i]] = i;	
_min[0] = n + 1;
for(int i = 1; i <= n; i ++){
	_max[i] = max(_max[i - 1], pos[i]);
	_min[i] = min(_min[i - 1], pos[i]);
}
```

之后就可以快速求解满足 $\operatorname{Mex} = i + 1$ 的最短区间，我们不妨把它设为 $g\left[i\right]$.

```
for(int i = 1; i <= n; i ++)
	g[i] = _max[i] - _min[i] + 1;
```

然后枚举区间长度判断即可解决。

```c++
int ans = 0;
for(int i = 1; i <= n; i ++){
	if(f[i] <= n && g[f[i]] <= i){
		ans = i;
		break; 
	} 
}
```

综合时间复杂度 $\mathcal{O}\left(n\right)$ 的。

部分分分别是给 $\mathcal{O}\left(n^3\right),\mathcal{O}\left(n^2\right),\mathcal{O}\left(n\log n\right)$ 的。

---

## 作者：Reseamus (赞：5)

### 题意简述
- 给出 $1\sim n$ 的一个排列 $a_1,a_2,...,a_n$ 与长度为 $n$ 正整数序列 $f_1,f_2,...,f_n$。

- $\forall 1\le l\le r\le n$，求出使得 $\min\limits_{i\in[1,l)\cup(r,n]}a_i>f_{r-l+1}$（式中左半部分即为题目中的 $\operatorname{Mex_{l,r}}$，后文简写为 $\operatorname{Mex_{l,r}}$）成立的最小的 $r-l+1$，如果没有，则输出 $0$。即求出满足上述条件的 $[1,n]$ 的长度最短的子区间 $[l,r]$ 的长度。

### 题目分析

维护一个序列 $s$，$s_k$ 表示所有长度为 $k$ 的子区间 $[l,r]$ 所对应的 $\operatorname{Mex_{l,r}}$ 的最大值。如果 $s_k>f_k$，那么这个区间长度就一定是合法的，反之则一定不合法。所以只要求出 $s$，就可以解决这道题目。

$s$ 可以用贪心求出来。

#### 贪心策略：
首先确定最大的区间长度的 $s$ 值。即 $s_{n-1}=max\{a_1,a_n\}$，并同时确定子区间 $[l,r]$ 的位置，然后依次从大至小递推区间的长度，每次比较当前区间 $[l,r]$ 的左端点 $a_l$ 与右端点 $a_r$ 的大小，如果左端点大，就将区间缩小为 $[l+1,r]$，如果右端点大，就将区间缩小为 $[l,r-1]$，并同时用出区间的端点来更新当前区间长度的 $s$ 值，即 $s_i=min\{s_{i+1},max\{a_l,a_r\}\}$，直到区间长度缩小为 $1$，$s$ 序列求出为止。



#### 证明：
要证明贪心策略是正确的，只需证明对于 $[l,r]\subsetneqq [1,n]$，如果 $[l,r]$ 满足 $\operatorname{Mex_{l,r}}$ 最大，即 $s_{r-l+1}=\operatorname{Mex_{l,r}}$，那么 $s_{r-l}=min\{s_{r-l+1},max\{a_l,a_r\}\}$ 一定成立。

分两种情况讨论（由于 $a$ 是一个排列，所以 $max\{a_l,a_r\}\ne s_{r-l+1}$）。

1. $max\{a_l,a_r\}>s_{r-l+1}$

	贪心法求出的答案为 $s_{r-l}=s_{r-l+1}$。
    
    设存在区间 $[p,q]\subsetneqq [1,n]$ 且 $q-p+1=r-l,\operatorname{Mex_{p,q}}>s_{r-l}$，则 $\operatorname{Mex_{p,q}}>s_{r-l+1}$。
    
    $\because$ 由 $\operatorname{Mex}$ 的定义可得，$\operatorname{Mex_{p,q}}\le\operatorname{Mex_{p-1,q}},\operatorname{Mex_{p,q}}\le\operatorname{Mex_{p,q+1}}$
    
    $\therefore \operatorname{Mex_{p-1,q}}>s_{r-l+1},\operatorname{Mex_{p,q+1}}>s_{r-l+1}$，矛盾。
    
    所以，在这种情况下，贪心策略是成立的。
    
    
2. $max\{a_l,a_r\}<s_{r-l+1}$
	
    贪心法求出的答案为 $s_{r-l}=max\{a_l,a_r\}$，不妨设 $a_l<a_r$，则 $s_{r-l}=a_r$
    
    设存在区间 $[p,q]\subsetneqq [1,n]$ 且 $q-p+1=r-l,\operatorname{Mex_{p,q}}>s_{r-l}$
    
    (1) 若 $r\notin [p,q]$，则 $\operatorname{Mex_{p,q}}=\min\limits_{i\in[1,p)\cup(q,n]}a_i\le a_r=s_{r-l}$，矛盾。
    
    (2) 若 $r\in[p,q]$
    
    $\because$ $q-p+1=r-l<r-l+1$
    
    $\therefore$ $l\notin[p,q]$
    
    $\therefore$ $\operatorname{Mex_{p,q}}=\min\limits_{i\in[1,p)\cup(q,n]}a_i\le a_l<a_r=s_{r-l}$，矛盾。
    
    所以，在这种情况下，贪心策略是成立的。

证毕。
    
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e6+1;
int n;
int a[N],f[N];
int s[N];
inline int read()
{
	int x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		f[i]=read();
	int l,r;//当前的区间
	if(a[1]>a[n])//求出最长的区间的s值
	{
		s[n-1]=a[1];
		l=2,r=n;
	}
	else
	{
		s[n-1]=a[n];
		l=1,r=n-1;
	}
	for(int i=n-2;i>=1;i--)//从大到小递推区间的长度
	{
		if(a[l]>a[r])//贪心
		{
			s[i]=min(s[i+1],a[l]);
			l++;
		}
		else
		{
			s[i]=min(s[i+1],a[r]);
			r--;
		}
	}
	for(int i=1;i<n;i++)//找出最短合法区间的长度
		if(s[i]>f[i])
		{
			cout<<i;
			getchar();
			getchar();
			return 0;
		}
	cout<<0;//没有合法区间
	getchar();
	getchar();
	return 0;
}
```
    

---

## 作者：苏联小渣 (赞：3)

### 题目大意

给两个序列 $a,f$，$a$ 为 $1$ 到 $n$ 的一个排列，求一个最短的区间 $[l,r]$，满足该区间内没有出现过的最小正整数大于 $f_{r-l+1}$。

### 分析

先评价一下：放在 J 组第二题难度比较合适，但可能部分分给的不够充足~~导致没打暴力直接打正解~~

---

看到这题第一反应应该是枚举区间，但是从 $a$ 数组入手无论如何都会超时，于是考虑从 $f$ 数组入手。

首先需要明确几个概念：

- 设区间长度为 $x$，则题目要求这个区间内没出现的最小正整数大于 $f_x$。

- 由上一条可得，$[1,f_x]$ 的**所有数**都必须在这个区间内出现。

- 如果 $f_x > n$，可以直接排除。代入不等式即可。（优化 $1$）

- 如果 $f_x > x$，也可以直接排除。因为无论如何，没出现的最小正整数都会小于等于 $f_x$。（优化 $2$）

明确了这几点，这题就基本做完了。首先我们需要排序，要从小区间推大区间。我们遍历 $f$ 数组，对于 $i \in [1,n]$，分别用一个指针从 $f_{i-1}$ 走到 $f_i$，统计其中的数在 $a$ 中的最小位置和最大位置。由于 $\forall a_i \le 4 \times 10^6$，故可以用桶来记录每一个 $a_i$ 对应的位置。

由我们的遍历方式可以知道，对于每一个 $f_i$，我们已经寻找到了 $[1,f_i]$ 中的数在 $a$ 的最小位置和最大位置，所以这个区间一定是**合法的最小区间**。由于这个区间往外拓宽一点也没关系，所以只需满足这个区间的长度**小于等于** $f_i$ 在原序列中对应的位置，即对应的区间长度即可。

但这个方法需要两重循环，每一个 $i$ 中还要 $j$ 从 $f_{i-1}$ 推到 $f_i$。但由于第二重循环在整个过程中最多只执行了 $n$ 次，即 $i$ 从 $1$ 到 $n$，$j$ 最多从 $1$ 到 $n$（因为通过优化 $1$ 已经把大于 $n$ 的情况全部排除了），所以加上排序的复杂度，最终时间复杂度为 $\mathcal{O}(n\log n+2n)$，可以通过。

补充说一句：寻找最小值和最大值其实是可以预处理的，但直接这样寻找也不会超时。故在此从略。还有本题数据有些水，导致不加两个优化也可以过。理论上不加优化最多要跑 $10^9$ 次。

### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, minn=1e9+7, maxx, ans=1e9+7;
struct node{
	int p, x;
}a[4000010];
struct F{
	int num, id;
	bool operator < (const F &A) const{
		return num < A.num;
	}
}f[4000010];
inline int read(){
	int s=0, w=1; char ch = getchar();
	while (ch < '0' || ch > '9'){if (ch == '-') w=-1; ch=getchar();}
	while (ch >= '0' && ch <= '9'){s=(s<<1)+(s<<3)+ch-48; ch=getchar();}
	return s * w;
}
int main(){
	n = read();
	for (int i=1; i<=n; i++){
		a[i].x = read();
		a[a[i].x].p = i;//记录每一个数的位置 
	}
	for (int i=1; i<=n; i++){
		f[i].num = read();
		f[i].id = i;//由于要排序故记录位置，即对应的区间长度（这点很重要） 
	}
	sort (f+1, f+n+1);
	for (int i=1; i<=n; i++){
		for (int j=f[i-1].num+1; j<=f[i].num; j++){//从上一个数推到这一个数 
			minn = min(minn, a[j].p);//记录最小位置 
			maxx = max(maxx, a[j].p);//记录最大位置 
		}
		if (f[i].num > n) break;//优化1，排序后这个大于n剩下的都大于n 
		if (f[i].num > f[i].id) continue;//优化2 
		if (maxx - minn + 1 <= f[i].id) ans = min(ans, f[i].id);
		//判断是否符合，小于等于要特别注意（本质上是包含和被包含的关系），题解中有解释 
	}
	printf ("%d\n", ans == 1e9+7 ? 0 : ans);//不符合记得输出0 
	return 0;
}
```

---

## 作者：Liu45318 (赞：3)

[题目传送门~](https://www.luogu.com.cn/problem/P8087)

用 $ pos_i $ 记录 $ i $ 在序列 $ a $ 中出现的下标，记 $ \operatorname{maxn}_p $ 表示 $ \max \limits_{1\le x\le p}pos_x $，$ \operatorname{minn}_p $ 表示 $ \min \limits_{1\le x\le p}pos_x $，那么 $ \operatorname{Mex}_{\operatorname{minn}_p,\operatorname{maxn}_p}>p $。这很好理解，因为 $ \{a_{\operatorname{minn}_p},...,a_{\operatorname{maxn}_p}\} $ 中已经包含了 $ 1\sim p $ 所有数。

只要有 $ \operatorname{maxn}_{f_i}-\operatorname{minn}_{f_i}\le i $，$ \{ a_{\operatorname{minn}_{f_i}},...,a_{\operatorname{minn}_{f_i}+i}\} $ 中一定包含了 $ 1\sim f_i $ 所有数，所以 $ \operatorname{Mex}_{\operatorname{minn}_{f_i},\operatorname{minn}_{f_i}+i}>f_i $。

所以对于代码的编写我们大概就有思路了：将 $ i $ 从 $ 1 $ 到 $ n $ 遍历，找到的第一个可以令 $ \operatorname{maxn}_{f_i}-\operatorname{minn}_{f_i}\le i $ 的 $ i $ 即是答案。特别地，如果无法找到一个合法的 $ i $，答案为 $ 0 $。

关于 $ \operatorname{minn} $ 和 $ \operatorname{maxn} $，我用了一种类似记忆化搜索的方法，详见代码。

这样，我们就可以在 $ \mathcal{O}(n) $ 的时间复杂度内通过本题了。

AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=4e6+10;
const int INF=0x7fffffff;

int n,a[MAXN],f[MAXN];
int pos[MAXN],ans;
int maxn[MAXN],minn[MAXN];

int read(){
	int s=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s;
}

void input(){
	n=read();
	for (int i=1;i<=n;i++){
		a[i]=read();
		pos[a[i]]=i; //记录 a[i] 出现的下标
	}
	for (int i=1;i<=n;i++)
		f[i]=read();
}

int query(int x,int opt){
	//opt=1 表示求 maxn[x];opt=2 表示求 minn[x]
	if (!x){ //边界
		if (opt==1) return 0;
		return INF;
	}
	if (!maxn[x]){ //当前 x 之前没有算过 maxn 和 minn
		maxn[x]=max(query(x-1,1),pos[x]);
		minn[x]=min(query(x-1,2),pos[x]);
	}
	if (opt==1) return maxn[x];
	return minn[x];
}

void solve(){
	for (int i=1;i<=n;i++){
		int t1=query(f[i],1);
		int t2=query(f[i],2);
		if (t1-t2+1<=i){ //上文推出的公式
			ans=i;
			break;
		}
	}
}

void output(){
	printf("%d\n",ans);
}

int main(){
	input();
	solve();
	output();
	return 0;
} 
```

---

## 作者：囧仙 (赞：2)

## 题解

观察到一条性质：如果 $[l,r]$ 区间的长度固定，那么 $\operatorname{Mex}_{l,r}$ 的值越大，越有可能满足 $F_{r-l+1}<\operatorname{Mex}_{l,r}$。因此需要计算出在每个区间长度的情况下，可能得到的最大 $\operatorname{Mex}$ 值。记为 $P_x$。

但是正过来计算是比较麻烦的。不妨通过另外一个角度：如果要使得 $\operatorname{Mex}$ 值为 $x$，所需要的最短的 $[l,r]$ 的长度 $A_x$。容易发现，如果 $[l,r]$ 的长度大于 $A_x$，那么存在一种方案使得 $[l,r]$ 区间包含「使得 $\operatorname{Mex}$ 值等于 $x$ 的区间」。因此计算出了 $A_x$ 后就能以此更新 $P$ 数组 $[A_x,n]$ 部分。

下面考虑如何计算出 $A_x$ 数组。设原数组里数字 $i$ 的位置是 $X_i$，那么 $1\sim x$ 这些数字组成的位置集合为 $S_x=\{X_1,X_2,\cdots,X_x\}$，选取其中的最小值作为 $l_x$，最大值为 $r_x$，那么区间 $[l_x,r_x]$ 则为包含 $S_x$ 的最短的区间。因而 $A_x\gets r_x-l_x+1$。从小到大枚举 $x$ 即可维护 $l_x$ 和 $r_x$ 的值。然后令 $P_{A_x}\gets x$。

最后更新一下 $P$ 数组。从 $2$ 到 $n$ 枚举 $i$，然后令 $P_i\gets \max\{P_{i-1},P_i\}$ 即可得到真正的 $P$ 数组。枚举一下区间长度 $i$，将 $P_i$ 和 $F_i$ 比较即可。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=4e6+3;
int A[MAXN],B[MAXN],F[MAXN],l=1e9,r=0;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int n,t,M[MAXN];
int main(){
    n=qread();
    up(1,n,i) A[i]=qread(),B[A[i]]=i;
    up(1,n,i){
        l=min(l,B[i]),r=max(r,B[i]); M[r-l+1]=i+1;
    }
    up(1,n,i) F[i]=qread();
    up(1,n,i){
        t=max(t,M[i]); if(F[i]<t) printf("%d\n",i),exit(0);
    }
    puts("0");
    return 0;
}
```

---

## 作者：Iam1789 (赞：1)

推销题解合集：[link](https://www.luogu.com.cn/blog/Iam1789/lgr-102-ti-xie)

考虑到特定长度区间内最大的 $\text{MEX}$ 并不容易计算，所以我们转而枚举 $\text{MEX}$。

维护一个双指针 $l,r$，代表 $\text{MEX}$ 达到某个值的时候所需要的最短区间。一旦 $\text{MEX}> \text{len}=r-l+1$ 立即输出答案。~~然后我们发现大样例炸了~~

重新思考，发现 ${\exists i>j,f_i<f_j}$。有时候增长区间所需要的 $\text{MEX}$ 反倒会减小。因此，直接忽略更新前后区间长度 $\text{len},\text{len}^{\prime}$ 之间的长度是错误的。

于是在 $\text{MEX}$ 更新到 $\text{MEX}^{\prime}$，最短区间长度从 $\text{len}$ 更新到 $\text{len}^{\prime}$ 时，我们用 $\text{MEX}$ 来检查 $[\text{len},\text{len}^{\prime})$ 之间的长度，就可以做到不漏了。时间复杂度 $\Theta(n)$。

---

## 作者：water_three (赞：1)

### 题目大意 ：
给定一个数列 $a_i$，在其中选连续的 $k$ 个数，使得其中没有出现的最小的正整数大于 $f_k$，并输出最小的 $k$。其中 $a_i$ 是一个 $1$ 到 $n$ 的排列。
### 思路：
随便编几个数据很容易发现当 $k$ 最小且符合要求时，此时选数可能有很多种方法，于是考虑依次枚举 $k$。
### 优化：
因为 $f_i$ 是定值，所以我们考虑使 $MEX_{l,r}$ 最大，此时才更容易得到最优解。容易发现，当 $k$ 为 $1$ 时，选 $1$ 这个数，会使最小的正整数变为 $2$。而如果选 $2$，会使最小的正整数变为 $1$。所以只用选 $1$ 这个数就可以判断 $k$ 的合法最小值是不是 $1$。

所以我们设 $left$ 为选取区间的左端点，$right$ 为右端点，初始时区间内只包含 $1$, 当 $k$ 增大时，将区间向没有包含的最小的正整数扩展，在此过程中，需要注意判断是否满足要求。

（具体实现详见代码）
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long const MAXN=4000001;
inline long long read() {
	long long x=0;
	bool flag=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')
			flag=0;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return (flag?x:~(x-1));
}
long long s=0,MIN=2,ans=0,a[MAXN],f[MAXN],pan=0,mapp[MAXN],shi[MAXN];//MIN为当前区间内没有包含的最小的正整数
int main() {
	long long n;
	n=read();
	for(long long i=1; i<=n; i++) {
		a[i]=read();
		mapp[a[i]]=i;//每个元素在哪个位置
		if(a[i]==1) {
			s=i;
		}
	}
	for(long long i=1; i<=n; i++)f[i]=read();
	long long left=s;
	long long right=s;
	shi[1]=1;
	while(left>=1&&right<=n) {
		if(f[right-left+1]<MIN)break;//在转移的过程中满足了条件
		else if(left==1&&right==n) {
			pan=1;//当k==n时还没有满足条件时就无解
			break;
		} else {
			if(mapp[MIN]<left) {//当MIN的位置在LEFT左边
				while(left>1) {
					left--;
					shi[a[left]]=1;//标记已经经过的数
					if(left!=mapp[MIN]) {
						if(f[right-left+1]<MIN)break;
					} else {
						while(shi[MIN]==1) {//当找到MIN时需要考虑途中经过的数
							MIN++;
						}
						break;
					}
				}
			} else {//在右边
				while(right<n) {
					right++;
					shi[a[right]]=1;
					if(right!=mapp[MIN]) {//同上
						if(f[right-left+1]<MIN)break;
					} else {
						while(shi[MIN]==1) {
							MIN++;
						}
						break;
					}
				}
			}
		}
	}
	if(pan)cout<<"0"<<endl;
	else {
		cout<<(right-left+1)<<endl;
	}
	return 0;
}
```


---

## 作者：by_chance (赞：1)

[P8087 『JROI-5』Interval](https://www.luogu.com.cn/problem/P8087)

挺清新的一个题，主要考察想法。

一读题，就看到一个 $Mex$ 函数，~~那肯定是博弈论啊！~~ 又看到一个“合法”的定义。

$Mex$ 函数不好分析，因此我们着重分析这个“合法”。不难想到：

$$f_{r-l+1} \lt Mex_{l,r}$$

与“在区间 $[l,r]$ 中出现了小于等于 $f_{r-l+1}$ 的所有数”等价。

然后你发现自己分析不下去了。

这时候就需要一点逆向思维。我们可以尝试求出：对一个给定的x，如果存在区间 $[l,r]$ 满足 $x \lt Mex_{l,r}$，那么区间 $[l,r]$ 的长最小值是多少。

这个问题就比较好处理了，只要求出包含 $1,2,...,x$ 的最短区间就可以了。不难在 $O(n)$ 的时间里求出对所有 $1 \le x \le n$ 的答案：每一次增加一个数的时候，考虑一下区间端点是否需要变化。大于 $ n $ 的部分不用考虑，它们一定不满足。

最后比较以下这个区间长与 $f$ 数组就可以了。

细节见代码。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=4e6+5;
int n,a[N],p[N],f[N],g[N],l,r;
//p[i]表示数字i在排列a中出现的位置
//g[i]表示上面说的最短区间长
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		p[a[i]]=i;
	}
	for(int i=1;i<=n;i++)f[i]=read();
	l=r=p[1];g[1]=1;
	for(int i=2;i<=n;i++){
		l=min(l,p[i]);
		r=max(r,p[i]);
		g[i]=r-l+1;
        	//每当x增加1，考虑x的位置，更新区间
	}
	for(int i=1;i<=n;i++){
		if(f[i]>n)continue;
		if(g[f[i]]<=i){
			printf("%d\n",i);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：0)

这是一道不错的思维题，赛时我的思路是逆向思维法。从长度为 $n$ 的合法区间开始判断，因为由 $f_{r - l + 1} < \rm Mex_{l,r}$可知，若让区间成为合法区间，需要使 $\rm Mex_{l,r}$ 尽可能大。所以就有了一个策略：从长度为 $n$ 的区间开始，若为合法区间则更新答案，否则去除两端的较大数，直至区间为 $1$。

而对于 $k = \rm Mex_{l,r}$ 的更新也很简单，由于逆着操作，所以一开始的值为 $n + 1$，当去除数字之后，直接更新为 $\min (k,x)$，$x$ 表示被去除的数字。

思路十分简单且清晰，那么直接给出代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 4e6 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,k,l,r,ans = INF;
int a[MAX],f[MAX];
int main ()
{
	n = read ();
	for (int i = 1;i <= n;++i) a[i] = read ();
	for (int i = 1;i <= n;++i) f[i] = read ();
	k = n + 1;//k 代表 Mex 函数的值，一开始为 n + 1
	l = 1;r = n;
	for (int i = n;i >= 1;--i)//逆向思维
	{
		if (f[i] < k) ans = min (ans,r - l + 1);//存在合法区间，答案被更新
		if (a[l] < a[r]) k = min (k,a[r--]);//右侧端较大，去除右侧的数字，同时 k 进行更新
		else k = min (k,a[l++]);//去除左端
	}
	if (ans == INF) printf ("0\n");//答案未被更新，也就是没有合法区间
	else printf ("%d\n",ans);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：C_S_L (赞：0)

考虑一个合法的区间 $[l,r]$ 。

因为 $f_{r-l+1}<Mex_{l,r}$ ，所以 $\{1,2,\cdots,f_{r-l+1}\}\subseteq\{a_l,a_{l+1},\cdots,a_{r-1},a_r\}$ 。

我们设 $y_i$ 表示所有包括 $1\sim i$ 的区间的长度的最小值。

为了求到 $y_i$，我们可以记录下每个数的位置，然后每次更新最左端位置和最右端位置。

该部分代码如下：

```cpp
int l=n+1,r=0;
for(int i=1; i<=n; ++i) {
	cmin(l,x[i]);
	cmax(r,x[i]);
	y[i]=r-l+1;
}
//x[i]表示i在排列a中的位置
```

然后，我们依次对 $\{f_1,f_2,\cdots,f_n\}$ 中的每个 $f_i$ 进行判断，如果满足 $y_{f_i}\leqslant i$，则说明这个 $i$ 符合条件。

第一个符合条件的 $i$ 即为最小的区间长度。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4000010;
int n,x[N],y[N];
void cmax(int&a,int b) {
	if(a<b) {
		a=b;
	}
}
void cmin(int&a,int b) {
	if(a>b) {
		a=b;
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1,a; i<=n; ++i) {
		scanf("%d",&a);
		x[a]=i;
	}
	int l=n+1,r=0;
	for(int i=1; i<=n; ++i) {
		cmin(l,x[i]);
		cmax(r,x[i]);
		y[i]=r-l+1;
	}
	for(int i=1,f; i<=n; ++i) {
		scanf("%d",&f);
		if(f>n) {
			continue;
		}
		if(i>=y[f]) {
			printf("%d\n",i);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
```


---

## 作者：vegetable_king (赞：0)

在[博客](https://yjh965.github.io/post/jroi-5-interval-ti-jie/)食用更佳。

# 思路

因为 $a$ 是一个排列，所以我们可以记录 $i$ 出现的位置 $p_i$。

根据 $p_i$，我们可以递推出 $l_i$ 和 $r_i$ 满足 $\operatorname{Mex}_{l_i, r_i} = i + 1$ 且 $r_i - l_i + 1$ 最小。根据 $\operatorname{Mex}$ 的定义，$l_i = \min(l_i - 1, p_i)$，$r_i = \max(r_i - 1, p_i)$。

我们可以再处理出 $s_i$ 代表区间长度为 $i$ 的最大 $\operatorname{Mex}$ 值。

$\operatorname{Mex}$ 值为 $x$ 且长度 $l$ 最小，相当于 $x$ 就是满足长度为 $l$ 的最大 $\operatorname{Mex}$ 值，所以对于每一个 $i$，$s_{r_i - l_i + 1} = i + 1$。

如果 $L \le l$ 且 $r \le R$，$\operatorname{Mex}_{L, R} \ge \operatorname{Mex}_{l, r}$，所以 $s_i$ 还要和 $\max_{j = 1}^{i - 1} s_j$ 取最大值。

处理出 $s_i$ 后，枚举区间长度 $i$，判断是否满足 $s_i > f_i$ 即可。

# 代码

```cpp
#include <algorithm>
#include <cstdio>

using namespace std;

int n, x, p[4000001], a[4000001], l, r, s[4000001], ans;
int main(){
	scanf("%d", &n);
	for (int i = 1;i <= n;i ++) scanf("%d", &x), p[x] = i;
	for (int i = 1;i <= n;i ++) scanf("%d", &a[i]);
	l = r = p[1], s[1] = 2;
	for (int i = 2;i <= n;i ++) l = min(l, p[i]), r = max(r, p[i]), s[r - l + 1] = i + 1;
	for (int i = 1;i <= n;i ++) s[i] = max(s[i - 1], s[i]);
	for (int i = 1;i <= n;i ++){
		if (s[i] > a[i]){
			printf("%d", i);
			return 0;
		}
	}
	printf("%d", 0);
}
```

---

