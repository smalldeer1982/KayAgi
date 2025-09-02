# 「GFOI Round 2」Colors

## 题目背景

> 世界が鮮やかに 染まって

## 题目描述

有 $n$ 个球排成一排，从左到右依次编号为 $1 \sim n$。每个球初始都是红色的。第 $i$ 个球的初始权值为 $p_i$。**保证 $\bm{n}$ 为奇数且 $\bm{p}$ 是一个 $\bm{1 \sim n}$ 的排列。**

你需要恰好进行 $\frac{n - 1}{2}$ 次操作。在一次操作中，你需要：

- 选择一个**红色**的球 $i$，使得 $1 \sim i - 1$ 中至少有一个红球且 $i + 1 \sim n$ 中至少有一个红球。
- 设 $j$ 为最大的整数使得 $j < i$ 且球 $j$ 为红球，$k$ 为最小的整数使得 $k > i$ 且球 $k$ 为红球。你要将球 $i$ 和球 $k$ 都染成蓝色。
- 然后进行以下两种操作的**恰好一个**：
	- 将 $p_j$（即球 $j$ 的权值）修改为 $\max(p_i, p_j, p_k)$；
    - 将 $p_j$（即球 $j$ 的权值）修改为 $\min(p_i, p_j, p_k)$。

容易发现进行了 $\frac{n - 1}{2}$ 次操作后恰好剩下一个红球。

你需要对于每个 $1 \sim n$ 的正整数 $x$，求出是否能合理地进行操作，使得最后剩下的红球的权值为 $x$。

## 说明/提示

#### 【样例解释】

对于第一组数据，初始的球的状态（颜色和权值）依次为 $\color{red}{3\ 2\ 1}$。

你需要进行 $1$ 次操作。在这次操作中你只能选择球 $2$，将球 $2$ 和球 $3$ 染成蓝色。

- 若你选择将 $p_1$ 修改为 $\max(p_1, p_2, p_3)$，那么操作后球的状态变为 $\color{red}{3}\ \color{blue}{2\ 1}$，最后剩下的红球的权值为 $3$；
- 若你选择将 $p_1$ 修改为 $\min(p_1, p_2, p_3)$，那么操作后球的状态变为 $\color{red}{1}\ \color{blue}{2\ 1}$，最后剩下的红球的权值为 $1$。

所以你输出一个 $01$ 串需要使得第 $1$ 和第 $3$ 位为 $1$，其余位为 $0$。

对于第二组数据，容易证明最后剩下的红球权值可以取 $1 \sim n$ 之间的所有正整数。下面给出一个能使得最后剩下的红球权值为 $2$ 的操作过程：

- 初始的球的状态为 $\color{red}{1\ 3\ 5\ 2\ 4}$。
- 选择球 $2$，将球 $2$ 和球 $3$ 染成蓝色，并将 $p_1$ 赋值为 $\max(p_1, p_2, p_3) = 5$。操作后球的状态变为 $\color{red}{5}\ \color{blue}{3\ 5}\ \color{red}{2\ 4}$。
- 选择球 $4$，将球 $4$ 和球 $5$ 染成蓝色，并将 $p_1$ 赋值为 $\min(p_1, p_4, p_5) = 2$。操作后球的状态变为 $\color{red}{2}\ \color{blue}{3\ 5\ 2\ 4}$。

#### 【数据范围】

**本题采用捆绑测试。**

| 子任务编号 | $n \le$ | $\sum n \le$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $5$ | $10^4$ | 无 | $16$ |
| $2$ | $19$ | $10^4$ | 无 | $19$ |
| $3$ | $99$ | $10^6$ | 无 | $19$ |
| $4$ | $10^6 - 1$ | $10^6$ | A | $3$ |
| $5$ | $10^6 - 1$ | $10^6$ | 无 | $43$ |

- 特殊性质 A：$p_i = i$。

对于所有数据，满足：

- $1 \le T \le 10^5$；
- $3 \le n \le 10^6 - 1$ 且 $n$ 是奇数；
- $\sum n \le 10^6$；
- $p$ 是一个 $1 \sim n$ 的排列。

## 样例 #1

### 输入

```
4
3
3 2 1
5
1 3 5 2 4
5
5 4 3 1 2
9
4 7 3 6 1 2 5 8 9```

### 输出

```
101
11111
11101
111111101```

# 题解

## 作者：缪凌锴_Mathew (赞：9)

场上胡了一堆结论过了，证明一下这些结论。

下面我们只考虑 $n>5$ 的情况，$n\le 5$ corner case 太多了直接跑暴力。

接下来认为删除后球会自动往前补位（即只考虑红球，蓝球不重要）。

这样一次操作必定为操作 $i-1,i,i+1$ 这三个位置。

发现删除 $i,i+1$ 和删除三个位置中任意两个没有区别，于是操作是对称的。

**结论 $1$：$5\le i\le n-4$，$i$ 为奇数，最后一定能剩下权值 $p_i$。**

> 考虑 $p_{i-1}>p_i$ 的情况，$p_{i-1}<p_i$ 是对称的。
>
> - $\exists j<i-1,p_j>p_i$，那么不断操作 $1,2,3$ 这三个位置，选择 $p'_1\gets\max(p_1,p_2,p_3)$。
>   
>   操作直到球 $i$ 到达 $3$ 的位置，也就是把 $1\sim i-2$ 的球合成一个最大值。
>
>   因为 $\exists j<i-1,p_j>p_i$，合出来的 $p'_1>p'_3=p_i$，又 $p'_2=p_{i-1}>p'_3=p_i$，此时操作 $1,2,3$ 这三个球，选择 $p'_1\gets\min(p_1,p_2,p_3)$，这样 $p'_1=p_i$。
>
>   ![](https://s3.bmp.ovh/imgs/2024/11/17/1dd0d22c4b06a353.png)
>
> - $\forall j<i-1,p_j<p_i$，操作 $i-3,i-2,i-1$，选择 $p'_{i-3}\gets \min(p_{i-3},p_{i-2},p_{i-1})$。
>
>   这样去掉了 $p_{i-1}$，$p_i$ 是前缀最大，直接不断选择 $\max$ 操作即可把 $i$ 移动至 $1$。
>
>   即不断操作 $1,2,3$，选择 $p'_1\gets\max(p_1,p_2,p_3)$。
>
>   ![](https://s3.bmp.ovh/imgs/2024/11/18/9e79c2f826b64e02.png)
>
> 以上证明了可以删掉 $1\sim i-1$，对称，同理可以删掉 $i+1\sim n$。

**结论 $2$：$1\le i\le n$，$i$ 为偶数，最后不能剩下权值 $p_i$ 当且仅当 $p_i$ 两侧权值范围无交。**

权值范围无交意思是 $\max\limits_{j<i}p_j<p_i<\min\limits_{j>i}p_j$ 或者 $\min\limits_{j<i}p_j>p_i>\max\limits_{j>i}p_j$。

> 考虑 $p_{i+1}>p_i$ 的情况，$p_{i+1}<p_i$ 是对称的。
>
> 若 $\exists j<i-1,p_j>p_i$，那么不断操作 $1,2,3$ 这三个位置，选择 $p'_1\gets\max(p_1,p_2,p_3)$。
>   
> 操作直到球 $i$ 到达 $2$ 的位置，也就是把 $1\sim i-2$ 的球合成一个最大值。
>
> 因为 $\exists j<i-1,p_j>p_i$，合出来的 $p'_1>p'_2=p_i$，又 $p'_3=p_{i+1}>p'_2=p_i$，此时操作 $1,2,3$ 这三个球，选择 $p'_1\gets\min(p_1,p_2,p_3)$，这样 $p'_1=p_i$。
>
> ![](https://s3.bmp.ovh/imgs/2024/11/18/0bc179193dcf922b.png)
>
> 又根据结论 $1$，可以删掉 $i+2\sim n$，这样最终剩下 $p_i$。
>
> 对称地，还有可能 $p_{i-1}>p_i$，$\exists j>i+1,p_j>p_i$。
>
> 剩下的情况就是 $\max\limits_{j<i}p_j<p_i<\min\limits_{j>i}p_j$ 或者 $\min\limits_{j<i}p_j>p_i>\max\limits_{j>i}p_j$。
>
> 这些情况无论怎么操作，必定会操作 $i-1,i,i+1$，这时 $p_i$ 是中位数，不能保留。

接下来就只用考虑 $p_3$ 和 $p_{n-2}$ 能不能保留，两种情况对称，只考虑 $p_3$ 行不行。

> - $p_3$ 不是 $p_1,p_2,p_3$ 的中位数，删去 $p_1,p_2$，根据结论 $1$，可以删掉 $4\sim n$，剩下 $p_3$。
> - $p_3$ 是 $p_1,p_2,p_3$ 的中位数，不妨设 $p_1>p_3>p_2$。（$p_1<p_3<p_2$ 是对称的）
> 
>   操作 $1,2,3$ 或者 $3,4,5$ 肯定无用，只有可能操作 $2,3,4$。
> 
>   只有 $p_2<p_3,p_4<p_3$ 才能操作 $2,3,4$，于是需要一个 $<p_3$ 的 $p_4$。
> 
>   找到第一个 $i>3,p_i<p_4$ 的 $i$，找不到无解。
> 
>   - $i$ 是奇数，第一个 $j>i,p_j>p_3$ 的 $i$，找不到无解。
> 
>     取 min 合成 $p_4\sim p_i$ 为 $p'_4<p_3$。
> 
>     取 max 合成 $p_{i+1}\sim p_n$ 为 $p'_5>p_3$。
> 
>     $p_2>p_3<p'_4$，取 min 删去 $p_2$ 和 $p'_4$。
> 
>     $p_1>p_3<p'_5$，取 min 删去 $p_1$ 和 $p'_5$。
> 
>     剩下 $p_3$，必定有解。
>     
>     ![](https://s3.bmp.ovh/imgs/2024/11/19/e89df63ac16c2d90.png)
> 
>   - $i$ 是偶数，第一个 $j+1>i,p_j>p_3$ 的 $i$，找不到无解。
> 
>     取 min 合成 $p_4\sim p_{i+1}$ 为 $p'_4<p_3$。
> 
>     取 max 合成 $p_{i+2}\sim p_n$ 为 $p'_5>p_3$。
> 
>     同理，必定有解。
>     
>     ![](https://s3.bmp.ovh/imgs/2024/11/19/6f109a8fb89b4ee3.png)

代码实现模拟上述过程即可，时间复杂度 $O(n)$。

```cpp
#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<numeric>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1e6+10;
const int N=1e6;
const int INF=0x3f3f3f3f;
const long long LINF=0x3f3f3f3f3f3f3f3f;
const int mod=998244353;
int n;
int a[MAXN];
bool ans[MAXN];
int suf_max[MAXN],suf_min[MAXN];
bool f[32];
void dfs(int s){
	if(f[s]){
		return ;
	}
	f[s]=true;
	if(s==(s&-s)){
		return;
	}
	for(int i=1;i<n-1;i++)
	{
		if(~s&(1<<i)){
			continue;
		}
		int j=i-1,k=i+1;
		while(~j&&~s&(1<<j))
		{
			j--;
		}
		while(k^n&&~s&(1<<k))
		{
			k++;
		}
		if(~j&&k^n){
			int p=a[i+1]+a[j+1]+a[k+1]-max({a[i+1],a[j+1],a[k+1]})-min({a[i+1],a[j+1],a[k+1]});
			if(a[i+1]==p){
				dfs(s^(1<<i)^(1<<j));
				dfs(s^(1<<i)^(1<<k));
			}
			if(a[j+1]==p){
				dfs(s^(1<<j)^(1<<i));
				dfs(s^(1<<j)^(1<<k));
			}
			if(a[k+1]==p){
				dfs(s^(1<<k)^(1<<i));
				dfs(s^(1<<k)^(1<<j));
			}
		}
	}
}
inline void work(){
	if(a[1]<a[3]&&a[2]>a[3]){
		ans[a[3]]=false;
		for(int i=4;i<=n;i++)
		{
			if(a[i]>a[3]){
				for(int j=i+1+(i&1);j<=n;j++)
				{
					if(a[j]<a[3]){
						ans[a[3]]=true;
						break;
					}
				}
				break;
			}
		}
	}
	if(a[1]>a[3]&&a[2]<a[3]){
		ans[a[3]]=false;
		for(int i=4;i<=n;i++)
		{
			if(a[i]<a[3]){
				for(int j=i+1+(i&1);j<=n;j++)
				{
					if(a[j]>a[3]){
						ans[a[3]]=true;
						break;
					}
				}
				break;
			}
		}
	}
}
inline void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	if(n<=5){
		memset(f,false,sizeof(f));
		dfs((1<<n)-1);
		for(int i=1;i<=n;i++)
		{
			ans[a[i]]=f[1<<(i-1)];
		}
		for(int i=1;i<=n;i++)
		{
			putchar(ans[i]+'0');
		}
		putchar('\n');
		return ;
	}
	memset(ans,true,sizeof(bool)*(n+1));
	suf_max[n]=a[n];
	suf_min[n]=a[n];
	for(int i=n-1;i;i--)
	{
		suf_max[i]=max(suf_max[i+1],a[i]);
		suf_min[i]=min(suf_min[i+1],a[i]);
	}
	int pre_max=a[1],pre_min=a[1];
	for(int i=1;i<=n;i++)
	{
		if(~i&1&&(pre_max<a[i]&&a[i]<suf_min[i+1]||pre_min>a[i]&&a[i]>suf_max[i+1])){
			ans[a[i]]=false;
		}
		pre_max=max(pre_max,a[i]);
		pre_min=min(pre_min,a[i]);
	}
	work();
	reverse(a+1,a+1+n);
	work();
	for(int i=1;i<=n;i++)
	{
		putchar(ans[i]+'0');
	}
	putchar('\n');
}
signed main(){
	#ifdef LOCAL
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	atexit([](){fprintf(stderr,"%.3lfs\n",(double)clock()/CLOCKS_PER_SEC);});
	#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：Aventurine_stone (赞：6)

## 1. 题目分析
题目保证 $n$ 为奇数，且 $p$ 中数互不相同且都 $\ge 1$ 且 $\le n$。  
我们先把题目的一次操作简单化，一次操作我们可以看成选择相邻的三个数，保留其中的最大值或最小值，其余数删除。之后的每次操作都是在前一次操作所剩下的序列上进行的。  
我们要求出每个数是否能被保留，因为数是三个一起操作，也就是一次操作会删除两个数，对于奇数位上的数和偶数位上的数，其所展现的最终形态必然不同，~~这个待会儿再解释~~，所以我们需要进行分类讨论。  
接下来我们用**大**来表示比我们所指定位上的数要大的数，用**小**来表示比我们所指定位上的数要小的数。  
### 偶数位
由于 $n$ 为奇数，故偶数位的前后都有奇数个数，按照每次删除两个数，那么其所展现的最终形态便是其左右分别只剩下一个数。那么这便会出现以下四种情况。  
![](https://cdn.luogu.com.cn/upload/image_hosting/ckec8zr7.png)  
可以看到只有出现最上面或最下面的情况，此位置上的数可以被保留。我们只需要知道在此位置前和后的最大值和最小值就行了。  
因为其前后的最大值和最小值一定能被保留，如果其前后的最大值都大于它或其前后的最小值都小于它，那么这个数便可以被保留，否则不能被保留。  
### 奇数位
也是由于 $n$ 为奇数，故奇数位的前后都有偶数个数，按照每次删除两个数，除了位置 $1$ 和位置 $n$ 外，其它位置所展现的最终形态便是左右分别只剩下两个数。简单推一下，可以得到会出现以下八种情况。  
![](https://cdn.luogu.com.cn/upload/image_hosting/ttlnpr6m.png)  
~~图有点丑，将就着看吧~~。我们可以看到其只有最上面的六种情况此位置上的数才能被保留。  
要判断情况是否成立，我们可以贪心找数，比如对于第一种情况，我们找到在此数左边和它距离最近且大于它的数，因为这样可以使后面的搜索范围最大，所以一定最优。然后因为一次要删两个数，若找到的数与此数之间的格子有奇数个，那么我们要把找到的数的后一个数也删掉才行（如果后一个数大于找到的数也没影响，因为这样保留后一个数对情况没有影响），若找到的数与此数之间的格子有偶数个，那么之间的格子刚好删完，不用做特殊处理。然后我们在左边剩下的数中找是否有比此数更大的数即可，右边也是同理。其他情况与此情况的判定方法一样。  
位置 $1$ 和位置 $n$ 的处理：它们要么右边剩两个数，要么左边剩两个数，如果有两个数都大于或都小于此数，也就是出现单边的大大和小小的情况，那么此数便可以被保留。
## 2. 题目做法
### 偶数位
我们要维护的是 $1$ 到 $x - 1$ 和 $x + 1$ 到 $n$ 的最大值和最小值。  
- 暴力维护，$O(n^2)$。  
对于每个下标，直接往左右暴力扫一遍，这里不过多阐述，反正过不了。
- 线段树或 st 表维护，$O(n \log{n})$。  
直接建一颗支持两种询问的线段树，预处理 $O(n)$，每次询问 $O(\log{n})$。  
st 表预处理 $O(n \log{n})$，每次询问 $O(1)$，应该都可过。
- 线性扫描预处理，$O(n)$。  
因为要维护的两个区间要么左端点不变，要么右端点不变，我们可以用莫队的左移右移思想来 $O(n)$ 预处理出区间的最大值和最小值，可过。
### 奇数位
我们要维护的是在 $x$ 左边或右边的离 $x$ 最近的大于或小于 $p_x$ 的数的位置。  
- 暴力维护，$O(n^2)$。  
也是往前往后暴力扫，加些优化[过了](https://www.luogu.com.cn/record/189670581)，并且跑的飞起，需要代码可以私信我。
- 权值线段树维护，$O(n \log{n})$。  
在值域上存下标的最大和最小值，很难写，且常数巨大，预估卡常大师才能过吧。
- 单调栈维护，$O(n)$。  
分别用栈从左到右，从右到左扫一遍，就可以做到边扫边记录了。但写出来跑的竟然没有暴力快，离谱。
## 3. 代码
这里放的是线性扫描预处理和单调栈的代码。

```cpp
#include<bits/stdc++.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
using namespace std;
const int N=1000010,M=1001;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int T,n;
int a[N],lmx[N],lmn[N],rmx[N],rmn[N];
int ls[N],lb[N],rs[N],rb[N];
bool p[N],vl[5],vr[5];//大大，大小，小大，小小
stack<int>ss,sb;
int main()
{
//	freopen("my.in","r",stdin);
//	freopen("my.out","w",stdout);
	T=read();
	lmn[0]=INT_MAX;
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)
			a[i]=read(),p[i]=0;
		lmx[1]=lmn[1]=a[1];
		for(int i=2;i<=n;i++)
			lmx[i]=max(lmx[i-1],a[i]),lmn[i]=min(lmn[i-1],a[i]);
		rmx[n+2]=rmx[n+1]=0,rmn[n+2]=rmn[n+1]=INT_MAX;
		rmx[n]=rmn[n]=a[n];
		for(int i=n-1;i;i--)
			rmx[i]=max(rmx[i+1],a[i]),rmn[i]=min(rmn[i+1],a[i]);
		for(int i=1;i<=n;i++)
		{
			while(!ss.empty()&&a[ss.top()]>a[i])
				rs[ss.top()]=i,ss.pop();
			while(!sb.empty()&&a[sb.top()]<a[i])
				rb[sb.top()]=i,sb.pop();
			ss.push(i),sb.push(i);
		}
		while(!ss.empty())
			rs[ss.top()]=0,ss.pop();
		while(!sb.empty())
			rb[sb.top()]=0,sb.pop();
		for(int i=n;i;i--)
		{
			while(!ss.empty()&&a[ss.top()]>a[i])
				ls[ss.top()]=i,ss.pop();
			while(!sb.empty()&&a[sb.top()]<a[i])
				lb[sb.top()]=i,sb.pop();
			ss.push(i),sb.push(i);
		}
		while(!ss.empty())
			ls[ss.top()]=0,ss.pop();
		while(!sb.empty())
			lb[sb.top()]=0,sb.pop();
		for(int i=1;i<=n;i++)
		{
			if(i&1)
			{
				int ls1=ls[i],lb1=lb[i],rs1=rs[i],rb1=rb[i],t;
				vl[1]=vl[2]=vl[3]=vl[4]=vr[1]=vr[2]=vr[3]=vr[4]=0;
				if(ls1>1)
				{
					t=ls1-!((i-ls1)&1)-1;
					vl[2]=lmx[t]>a[i],vl[4]=lmn[t]<a[i];
				}
				if(lb1>1)
				{
					t=lb1-!((i-lb1)&1)-1;
					vl[1]=lmx[t]>a[i],vl[3]=lmn[t]<a[i];
				}
				if(rs1)
				{
					t=rs1+!((rs1-i)&1)+1;
					vr[3]=rmx[t]>a[i],vr[4]=rmn[t]<a[i];
				}
				if(rb1)
				{
					t=rb1+!((rb1-i)&1)+1;
					vr[1]=rmx[t]>a[i],vr[2]=rmn[t]<a[i];
				}
				if(i==1)
					p[a[i]]=(vr[1]||vr[4]);
				else if(i==n)
					p[a[i]]=(vl[1]||vl[4]);
				else
					p[a[i]]=((vl[1]&&(vr[1]||vr[4]))||(vl[2]&&vr[3])||(vl[3]&&vr[2])||(vl[4]&&(vr[1]||vr[4])));
			}
			else if((lmx[i-1]>a[i]&&rmx[i+1]>a[i])||(lmn[i-1]<a[i]&&rmn[i+1]<a[i]))
				p[a[i]]=1;
		}
		for(int i=1;i<=n;i++)
			putchar(p[i]+'0');
		putchar(10);
	}
	return 0;
}
```

---

## 作者：FQR_ (赞：4)

题意可以转化为：有 $n$ 个球，每次可以将三个相邻的球合并成一个新的球，新的球的权值为三个球的权值的最大值或最小值。求最终剩下的球的权值可能是多少。

容易发现，每次合并操作会使得两个权值消失。于是我们可以枚举每一个球，判断这个球的权值在合并的过程中是否可以不消失。

我们按照球位置 $x$ 的奇偶性来讨论：

## $x$ 为偶数

那么 $x$ 的左边和右边都有奇数个球。于是可以先将它左边的球合并为一个球，将它右边的球合并为一个球，最后将这三个球合并成一个。若这一位是合法的，需要满足左右两个球的权值都大于 $p_x$ 或都小于 $p_x$。

有一个结论：将奇数个连续的球合并成一个球，最终球的权值可以取到这些球权值的最大值或最小值。每次合并都取最大值或都取最小值即可。

那么，如果想让左右两个球的权值都大于 $p_x$，最优的方案是让左边的球的权值为 $\max_{1\le i\le x-1} p_i$，让右边球的权值为 $\max_{x+1\le i\le n} p_i$，然后判断这两个值是否都大于 $p_x$ 即可。想让左右两个球的权值都小于 $p_x$ 也同理，左右分别取最小值即可。

## $x$ 为奇数

那么 $x$ 的左边和右边都有偶数个球。可以将左边和右边再分别分成两个奇数段，因此可以先将它左边的球合并成两个球，将它右边的球合并成两个球，最后将这五个球合并成一个球。

将五个球合并成一个球有以下两种方案：

- 将左侧或右侧的三个球合并成一个球，再将剩下的三个球合并成一个球；
- 将中间的三个球合并成一个球，再将剩下的三个球合并成一个球。

那么，若这五个球合并成一个球，且最终球的权值等于中间球的权值，则有以下情况。其中 `0` 表示这个球的权值小于 $p_x$，`1` 表示这个球的权值大于 $p_x$。

- `00-11`
- `11-00`
- `00-00`
- `11-11`
- `01-10`
- `10-01`

其中前两种情况可以用第一种方案合并，中间两种情况使用两种方案都可以，最后的两种情况可以用第二种方案。

那么，我们定义 $l_{0/1,0/1}$ 表示左侧是否可以取到这种情况。例如 $l_{0,1}$ 表示将左侧合并成两个球，是否可以做到第一个球的权值小于 $p_x$，第二个球的权值大于 $p_x$。$r_{0/1,0/1}$ 的定义同理。我们现在考虑如何求这些值。

以  $l_{0,1}$ 为例，实际上是求是否可以将左侧划分成两个奇数段，第一段的最小值小于 $p_x$，第二段的最大值大于 $p_x$。我们可以贪心来做：找到 $x$ 左面的第一个大于 $p_x$ 的位置 $y$，若此时 $[y,x-1]$ 的长度为偶数，就将 $y$ 减少 $1$。此时求 $[1,y-1]$ 的最小值是否小于 $p_x$ 即可。

求出 $l_{0/1,0/1}$ 和 $r_{0/1,0/1}$ 的值后，判断是否可以满足上述六种情况中的一个即可。

特别地，要注意 $x=1$ 或 $x=n$ 的情况。以 $x=1$ 为例，将它的右边的球合并成两个球，要求这两个球的权值都大于 $p_1$ 或都小于 $p_1$。因此若满足 $r_{1,1}$ 和 $r_{0,0}$ 中的任意一个，则 $p_1$ 就是合法的。$x=n$ 同理，若满足 $l_{1,1}$ 和 $l_{0,0}$ 中的任意一个，则 $p_n$ 就是合法的。

___

上述的所有值都可以使用单调栈、前缀最大/最小值、后缀最大/最小值求出。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define up(s,e,i) for(int i=s;i<=e;i++)
#define down(s,e,i) for(int i=s;i>=e;i--) 
#define endl '\n' 

namespace Main
{
    const int N = 1000010;
    int n;
    int a[N];
    bool ans[N];
    int qmx[N], qmn[N], hmx[N], hmn[N]; // 前缀最大值、前缀最小值、后缀最大值、后缀最小值
    bool l[2][2], r[2][2];
    int lmx[N], rmx[N], lmn[N], rmn[N]; // x 左边第一个比它大的数的位置、x 左边第一个比它小的数的位置、x 右边第一个比它大的数的位置、x 右边第一个比它小的数的位置
    void solve()
    {
        cin >> n;
        up(1, n, i) cin >> a[i];
        qmn[0] = hmn[n + 1] = 0x3f3f3f3f;
        qmx[0] = hmx[n + 1] = 0;
        up(1, n, i) qmx[i] = max(qmx[i - 1], a[i]), qmn[i] = min(qmn[i - 1], a[i]);
        down(n, 1, i) hmx[i] = max(hmx[i + 1], a[i]), hmn[i] = min(hmn[i + 1], a[i]);

        vector<int> stk1, stk2;
        up(1,n,i)
        {
            while(!stk1.empty() && a[stk1.back()] < a[i]) stk1.pop_back();
            while(!stk2.empty() && a[stk2.back()] > a[i]) stk2.pop_back();
            lmx[i] = stk1.empty() ? 0 : stk1.back();
            lmn[i] = stk2.empty() ? 0 : stk2.back();
            stk1.push_back(i), stk2.push_back(i);
        }
        stk1.clear(), stk2.clear();
        down(n,1,i)
        {
            while(!stk1.empty() && a[stk1.back()] < a[i]) stk1.pop_back();
            while(!stk2.empty() && a[stk2.back()] > a[i]) stk2.pop_back();
            rmx[i] = stk1.empty() ? 0 : stk1.back();
            rmn[i] = stk2.empty() ? 0 : stk2.back();
            stk1.push_back(i), stk2.push_back(i);
        }


        up(1,n,i)
        {
            if(i%2==0)
            {
                if ((qmx[i - 1] > a[i] && hmx[i + 1] > a[i]) || (qmn[i - 1] < a[i] && hmn[i + 1] < a[i])) ans[a[i]] = 1;
                else ans[a[i]] = 0;
            }
            else
            {
                ans[a[i]] = 0;
                up(0, 1, x) up(0, 1, y) l[x][y] = r[x][y] = 0;
                if(lmx[i])
                {
                    int pl = lmx[i];
                    if(pl %  2 == 1) pl--;
                    if(pl >= 1 && qmx[pl - 1] > a[i]) l[1][1] = 1;
                    if(pl >= 1 && qmn[pl - 1] < a[i]) l[0][1] = 1;
                }
                if(lmn[i])
                {
                    int pl = lmn[i];
                    if(pl % 2 == 1) pl--;
                    if(pl >= 1 && qmx[pl - 1] > a[i]) l[1][0] = 1;
                    if(pl >= 1 && qmn[pl - 1] < a[i]) l[0][0] = 1;
                }
                if(rmx[i])
                {
                    int pl = rmx[i];
                    if(pl % 2 == 1) pl++;
                    if(pl <= n && hmx[pl+1] > a[i]) r[1][1] = 1;
                    if(pl <= n && hmn[pl+1] < a[i]) r[1][0] = 1;
                }
                if(rmn[i])
                {
                    int pl = rmn[i];
                    if(pl % 2 == 1) pl++;
                    if(pl <= n && hmx[pl+1] > a[i]) r[0][1] = 1;
                    if(pl <= n && hmn[pl+1] < a[i]) r[0][0] = 1;
                }
                if(i==1) 
                {
                    if(r[0][0] || r[1][1]) ans[a[i]] = 1;
                }
                else if(i==n)
                {
                    if(l[0][0] || l[1][1]) ans[a[i]] = 1;
                }
                else
                {
                    if((l[0][0] || l[1][1]) && (r[0][0] || r[1][1])) ans[a[i]] = 1;
                    if(l[1][0] && r[0][1]) ans[a[i]] = 1;
                    if(l[0][1] && r[1][0]) ans[a[i]] = 1;
                }
            }
        }
        up(1, n, i) cout << ans[i];
        cout << endl;
    }
    
    void main()
    {
        ios::sync_with_stdio(0);
        cin.tie(0);cout.tie(0);
        int _;cin>>_;while(_--) solve();
    }
};

int main()
{
    Main::main();
    return 0;
}
```

---

## 作者：_lmh_ (赞：4)

一些题外话：赛时 20min 把这题秒了，加上 1A 共耗时 33min。坏消息是报名太晚，痛失首杀。最后 Div1 rk7，一分钱没拿到。

题目中把操作方式写得很抽象，实际上它等价于：每次选择排列中连续的三个数，将它们删除，并在原位放上它们的最小值或者最大值。

对排列 $p$ 中每一个数单独处理。假设我们目前在处理位置 $x$ 上的数，则令数列 ${a_i}$ 为：

$$a_i=\begin{cases}0&p_i<p_x\\1&p_i=p_x\\2&p_i>p_x\end{cases}$$

那么显然原先的操作可以直接套用到现在的序列上，我们的目标是最后剩下的数是原序列中唯一的那个 $1$。此时，这个 $1$ 只能和两个 $0$ 或者两个 $2$ 操作。

### Part 1：$x\equiv0\pmod 2$

现在考虑一个只有 $0$ 和 $2$ 的长度为奇数的序列，对它操作可以得到什么结果。

注意到对三个 $0$ 进行一次操作只能变成 $0$，对三个 $2$ 进行一次操作只能变成 $2$，但是如果三个数中同时有 $0$ 和 $2$，就可以变成任意一个。

这样我们发现，只要这个序列中有 $0$，就一定存在一种操作方法使得这个序列变成 $0$。$2$ 同理。

如果 $x\equiv 0\pmod 2$，那么它两边的数列长度都为奇数。只要两边都能变成 $0$ 或都能变成 $2$，那么就有解。

否则，只可能是一边全是 $0$，另一边全是 $2$。这样的话，出现对 $0,1,2$ 进行操作就废了。然而，每次操作会减少 $2$ 个数，而左边（不妨这样假设）$0$ 的个数和右边 $2$ 的个数都是奇数，因此无法在不进行 $0,1,2$ 的操作且不把 $1$ 搞没的前提下去掉所有的 $0$，因而无解。

维护前后缀最大最小值即可，时间复杂度 $O(n)$。

### Part 2：$x\equiv 1\pmod 2$

下证明：长度大于 $2$ 且长度为偶数的由 $0$ 和 $2$ 组成的数列可以通过操作变成两个相等的数。

假设数列第一个数为 $0$，由之前对奇数长度数列性质的推导，只要后面有 $0$，就可以把去掉第一个数的部分变成 $0$。否则，后面全部都是 $2$，但数列长度大于 $2$，那么此时对去掉最后一个数的部分操作使其变成 $2$，就会剩下两个相同的数。

所以，如果 $x\ne 3$ 且 $x\ne n-2$，那么它两段的序列长度要么是 $0$，要么 $>2$，可以变成两个相同的数然后和中间的 $1$ 操作把它留下来。

下只考虑 $x=3$ 的情况。$x=n-2$ 同理。

不妨假设 $n\ge 7$，此时 $x$ 右边的序列长度 $>2$。$n=3$ 和 $n=5$ 的情况是类似的，最后会给出结论。

如果 $(a_1,a_2,a_3)=(0,0,1)$ 或 $(2,2,1)$，那么把序列后半部分变成两个相同的数，显然有解。

否则，不妨设 $(a_1,a_2,a_3)=(0,2,1)$。显然我们不能对 $a_1,a_2,a_3$ 进行操作，所以必定有一次操作是对 $2,1,2$ 进行，此时 $a_4=2$。之后我们肯定还有一次对 $0,1,0$ 进行的操作。

也就是说，我们必须从后面凑出一个 $2$ 和一个 $0$。假设 $p\le n+1$ 为最小的使得 $\max_{i=4}^p{a_i}=2$ 的偶数（令 $a_{n+1}=2$），那么 $a_4\sim a_p$ 的子序列长度为奇数，显然可以凑出一个 $2$。（这里 $p=n+1$ 是个 corner case，不过不要紧，后面会把这种情况排除掉）

同时，由于 $p$ 是最小的满足条件的偶数，所以把 $a_4\sim a_{p-2}$ 合并凑不出 $2$，把 $a_4\sim a_{p+2}$ 合并不优。现在，我们还需要在 $a_{p+1}\sim a_n$ 中凑出一个 $0$。这个判断是简单的。

由此，我们解决了 $n\ge 7$ 的情况。

当 $n=3$ 或 $n=5$，$x=3$ 时，有如下结论：

$n=3$ 时，有解当且仅当 $(a_1,a_2,a_3)=(0,0,1)$ 或 $(2,2,1)$。

$n=5$ 时，有解当且仅当 $(a_1=a_2\wedge a_4=a_5)\vee (a_1=a_5\wedge a_2=a_4)$。

证明显然。

由此，我们在 $O(n)$ 的时间复杂度内解决了问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1000007;
ll T,n,p[N],premn[N],premx[N],sufmn[N],sufmx[N],ans[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for (int i=1;i<=n;++i){cin>>p[i];ans[i]=1;}
		premn[0]=sufmn[n+1]=1e9;premx[0]=sufmx[n+1]=0;
		for (int i=1;i<=n;++i){
			premn[i]=min(premn[i-1],p[i]);
			premx[i]=max(premx[i-1],p[i]);
		}
		for (int i=n;i;--i){
			sufmn[i]=min(sufmn[i+1],p[i]);
			sufmx[i]=max(sufmx[i+1],p[i]);
		}
		for (int i=2;i<=n;i+=2) if ((premx[i-1]<p[i]&&p[i]<sufmn[i+1])||(sufmx[i+1]<p[i]&&p[i]<premn[i-1])) ans[p[i]]=0;
		if (p[1]<p[3]&&p[2]>p[3]){
			ans[p[3]]=0;
			ll pos=4;
			while(pos<n&&p[pos]<p[3]&&p[pos-1]<=p[3]) pos+=2;
			if (pos<n){
				for (int i=pos+1;i<=n;++i) ans[p[3]]|=(p[i]<p[3]);
			}
		}
		if (p[1]>p[3]&&p[2]<p[3]){
			ans[p[3]]=0;
			ll pos=4;
			while(pos<n&&p[pos]>p[3]&&p[pos-1]>=p[3]) pos+=2;
			if (pos<n){
				for (int i=pos+1;i<=n;++i) ans[p[3]]|=(p[i]>p[3]);
			}
		}
		if (p[n]<p[n-2]&&p[n-1]>p[n-2]){
			ans[p[n-2]]=0;
			ll pos=n-3;
			while(pos>0&&p[pos]<p[n-2]&&p[pos+1]<=p[n-2]) pos-=2;
			if (pos>0){
				for (int i=1;i<pos;++i) ans[p[n-2]]|=(p[i]<p[n-2]);
			}
		}
		if (p[n]>p[n-2]&&p[n-1]<p[n-2]){
			ans[p[n-2]]=0;
			ll pos=n-3;
			while(pos>0&&p[pos]>p[n-2]&&p[pos+1]>=p[n-2]) pos-=2;
			if (pos>0){
				for (int i=1;i<pos;++i) ans[p[n-2]]|=(p[i]>p[n-2]);
			}
		}
		for (int i=1;i<=n;++i) cout<<ans[i];cout<<'\n';
	}
	return 0;
}
```

---

