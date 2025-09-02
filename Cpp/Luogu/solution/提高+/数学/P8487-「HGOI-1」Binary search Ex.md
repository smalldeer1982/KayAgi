# 「HGOI-1」Binary search Ex

## 题目背景

此题为 [div.2 B](https://www.luogu.com.cn/problem/P8481) 的 extra sub，并非完整的题，总分为 $25$ 分（进入主题库后满分为 $100$ 分）。

$\text{bh1234666}$ 正在学习[二分查找](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE/10628618?fr=aladdin)。

## 题目描述

众所周知二分查找的 $\text{mid}$ 在计算时可以取 $\lfloor\dfrac{l+r}{2}\rfloor$ 或者 $\lceil\dfrac{l+r}{2}\rceil$,于是有选择困难症的 $\text{bh1234666}$ 同学在自己的二分查找代码中加入了随机化，每次随机选取其中的一个作为 $\textit{mid}$。

现在 $\text{bh1234666}$ 告诉你了他要找的数在序列内的下标（从 $0$ 开始，可以理解为在一个 $0\sim n-1$ 的升序序列内查询询问的数），他想知道在运气最好的情况下循环需要进行几次（即代码中 $\textit{cnt}$ 的可能的最终值的最小值）。

循环：
```cpp
int find(int *num,int x,int len)
{
	int l=0,r=len-1,mid,cnt=0,w;
	while(l<r)
	{
		cnt++;
		w=rand()%2;
		mid=(l+r+w)/2;
		if(num[mid]-w<x) l=mid+!w;
		else r=mid-w;
	}
	return mid;
}
```
递归：
```
int cnt;
int get(int *num,int x,int l,int r)
{
	if(l==r) return l;
	cnt++;
	int w=rand()%2;
	int mid=(l+r+w)/2;
	if(num[mid]-w<x) return get(num,x,mid+!w,r);
	else return get(num,x,l,mid-w);
}
int find(int *num,int x,int len)
{
	cnt=0;
	return get(num,x,0,len-1);
}
```
注：以上两代码完全等价。

## 说明/提示

### 样例 1 解释

还原后的输出：$3\  3\  3$。

找 $2$：

取 $[1,5]$。

取 $[1,3]$。

取 $[3,3]$（退出循环）。

### 样例 2 解释

还原后的输出：$3\ 4\ 3\  3\  4$。

#### 数据生成器

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
ull sd = 111111111111111111ull, sd2, k = 1;
ull qu, n, ans;//qu表示每次询问的位置。 
inline ull get_q(int i)
{
	sd = (sd2 ^ (sd2 >> 3)) + 998244353;
	return ((sd2 = sd ^ (sd << 37)) & k) + ((i & 1) ? 0 : (n - k - 1));
}
int q, q2;
void init()
{
	//Put your code here or not.
}
inline ull get_ans(ull x)
{
	//Put your code here.
}
int main()
{
	cin >> n;
	sd2 = n;
	while((k << 1) <= n + 1) k <<= 1;
	k -= 1;
	cin >> q >> q2;
	init();
	for(int i = 1; i <= q; i++)
	{
		cin >> qu;
		ans += get_ans(qu) * i;
	}
	for(int i = 1; i <= q2; i++)
	{
		qu = get_q(i);
		ans += get_ans(qu) * (i + q);
	}
	cout << ans << endl;
	return 0;
}
```

### 数据范围及约定

此题不进行捆绑测试，分数为各点分数之和。数据存在梯度，如下表所示。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{ExTest} & \textbf{Score} & \textbf{特殊限制} \cr\hline
1 & 5 & n,q_2 \le 2^{20}\cr\hline
2 & 5 & n \le 2^{30},q_2 \le 2\times 10^6 \cr\hline
3 & 5 & n \le 2^{40},q_2 \le 5 \times 10^6 \cr\hline
4 & 5 &  n \le 2^{50},q_2 \le  2\times 10^7 \cr\hline
5 & 5 &  n \le 2^{60},q_2 \le 2\times 10^8 \cr\hline
\end{array}
$$
对于 $100\%$ 的数据，$1 \le n \le 2^{60}$，$1 \le q+q_2 \le n$，$q \le 2^{20}$，$q_2 \le 2 \times 10^8$。

本题保证时限是 std 的两倍以上且使用给出的模板可以通过此题。

## 样例 #1

### 输入

```
10
3 0
2 6 8```

### 输出

```
18```

## 样例 #2

### 输入

```
13
5 0
0 1 4 6 11
```

### 输出

```
52```

## 样例 #3

### 输入

```
1928374
10 1000000
193 3489 238 438 8 912 83 19 12489 10```

### 输出

```
10000215403302```

# 题解

## 作者：bh1234666 (赞：3)

看到这题第一反应可能是贪心，二分时每次使区间最小，但是这样做是不正确的。因为直接贪心时靠前的操作权值$^*$小，靠后的操作权值大，靠前的决策会影响靠后的决策，即权值小的决策影响权值大的决策，显然不正确。

$^*$ 此处权值定义较复杂，可以简单理解为对后续长度产生影响（缩短 $1$）的概率。

例如对于 $n=13$，查询序列的第 $5$ 个（下标为 $4$，接下来的位置均指下标）。直接贪心过程为：
$$
[0,12] \stackrel{w=1}{\longrightarrow}  [0,5] \stackrel{w=0}{\longrightarrow} [3,5] \stackrel{w=1}{\longrightarrow} [4,5] \stackrel{w=0}{\longrightarrow} [4,4]
$$

但实际上有更优解法：

$$
[0,12] \stackrel{w=0}{\longrightarrow} [0,6]\stackrel{w=0}{\longrightarrow}[4,6] \stackrel{w=1}{\longrightarrow} [4,4]
$$

第一步贪心看似比最优解短了 $1$ ,贪心的下一步使得查找的值出现在了中部，导致 $ [3,5] \stackrel{w=1}{\longrightarrow} [4,5]$ 这一步无法使得长度折半。而贪心前面短的那一步最优解在下一步除二时除掉了，而在更靠后的 $[4,6] \stackrel{w=1}{\longrightarrow} [4,4]$ 比贪心短了 $1$。

对于 $\text{sub2}$ ，发现每次 $w$ 的值不会影响答案，直接输出 $\log_2 n$ 即可。

发现询问次数只有 $100$ 次，直接暴力。为便于实现，可以采用递归实现的二分，每次递归时分两类递归取最小即可。

由于递归层数为 $\log_2 n$ 层，每层分两种情况，最终复杂度为 $O(nq)$，可以通过此题。


核心代码：

```
int find(int k,int f,int l)
{
	if(f==l) return 0;
	int mid=(f+l)>>1,ret=32;
	if(mid<k) ret=find(k,mid+1,l);
	else ret=find(k,f,mid);
	mid=(f+l+1)>>1;
	if(mid<=k) ret=min(ret,find(k,mid,l));
	else ret=min(ret,find(k,f,mid-1));
	return ret+1;
}
int main()
{
	int i,n,q,k;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d",num+i); 
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d",&k);
		for(i=0;i<n;i++)
			if(num[i]==k) break;
		printf("%d\n",find(i,0,n-1));
	}
	return 0;
}
```

### extra:

对于给定的 $n$，考虑查找第 $0\sim n-1$ 下标时所需要的次数。

显然次数只能为 $\lfloor \log n\rfloor\sim \lfloor \log n\rfloor +1$。

写出 $n$ 的二进制，设高位连续的 $1$ 的数量为 $t$，低位连续的 $0$ 的数量为 $k$。

当 $n$ 为偶数时 $w$ 不会影响二分下一步的情况，因此显然存在 $2^k$ 个循环节。

考虑每次操作对区间长度 $len$ 的影响，每次操作的实质是：

当 $len_i$ 为偶数时，$len_{i+1}=\lfloor \dfrac{len_i}{2}\rfloor$。

当 $len_i$ 为奇数时，若查找的数不在序列正中间，则可以选择 $len_{i+1}=\lfloor \dfrac{len_i}{2}\rfloor$ 或者 $\lfloor \dfrac{len_i}{2}\rfloor+1$，若查找的数在正中间则 $len_{i+1}=\lfloor \dfrac{len_i}{2}\rfloor+1$。

显然要被查找的数不会连续两次出现在正中间，因此必然可以通过某种操作使得所处位最高的 $0$(指 $len$ 在二进制下，下同) 不产生进位。也就是说单个循环节内的答案只与开头连续的 $1$ 有关，显然对于连续的 $1$，会间隔出现不进位和进位的情况。

注意，虽然最高位的 $0$ 可以使得处理到 $1$ 时长度一定，但是查询的数在序列中的相对位置会受到低位的影响，因此循环节不会被高位的 $0$ 消除掉。

即循环节内部对称且中间部分为 $\lfloor \log n\rfloor$，开头结尾受到 $t$ 的影响会出现 $\lfloor \log n\rfloor$ 与 $\lfloor \log n\rfloor+1$ 相间的情况，长度为 $2^t-2$。

预处理循环节长度，得到询问在某个循环节的位置，判断是否在受到 $t$ 影响的区间及奇偶性（在 $\lfloor \log n\rfloor$ 与 $\lfloor \log n\rfloor+1$ 相间区间时）即可得到答案。

~~以上说明纯属扯淡，这个结论是我输出了 n 为 90 到 128 的结果以后观察得出的。~~

时间复杂度 $O(q)$。

核心代码:

```
int get_ans(int x)
{
	if(n==1) return lgt;//lgt为[log n]
	else
	{
		x%=len;//len为循环节长度，即n/2^k
		if(x>len/2) x=len-x-1;
		if(x>(1<<n)-2) return lgt;//此处的n为t
		else if(x&1) return lgt+1;
		else return lgt;
	}
}
```

注意到会进行大量的取模运算，可以采用 barrett 约减优化取模，其原理是通过成本较低的乘法运算和位运算替换取模（整除）运算。

预处理 $brt=\lfloor 2^{r}/len\rfloor$，可以通过 $brt\times x /2^r$ 得到 $\lfloor x/len \rfloor$ 的近似值，当 $r$ 足够大时，得到的近似值与精确值至多差 $1$。

我们可以通过 $x-brt\times x /2^r$ 来得到 $x\bmod len$ 的近似值，若得到的值大于 $len$ 则减 $len$ 即可。

于是我们就通过两次减法一次乘法一次位运算（除二的幂次）和一次条件判断（上述运算的成本均远小于取模）替换掉了一次取模运算。

barrett 部分核心代码：

```
brt=((__uint128_t)1<<brtcnt)/len;//brt初始化
```

```
x=x-len*(unsigned long long)(brt*x>>brtcnt);
if(x>=len) x-=len;//等价于x%=len
```

---

## 作者：Sktic (赞：2)

[P8481 Binary search](https://www.luogu.com.cn/problem/P8481) & [P8487 Binary search Ex ](https://www.luogu.com.cn/problem/P8487)

注：因为许多人比较习惯于采用 $[1,n]$ 的数组形式，所以本篇题解中默认区间编号为 $[1,n]$ 而不是题目中的 $[0,n-1]$ ，不过不影响理解题意。



题目大意：对于一个离散化后的区间 $[1,n]$ ，二分查找其中的一个位置 $x$，设每次查找的区间为 $[l,r]$ ，每次查找时当区间长度为偶数时下一次查找的区间为 $[l,\frac{r-l+1}{2}]$ 或 $[\frac{r-l+1}{2}+1,r]$ ，当区间长度为奇数时下一次查找的区间为 $[l,\lfloor\frac{r-l+1}{2}\rfloor-1]$ ， $[\lfloor\frac{r-l+1}{2}\rfloor,r]$ ， $[l,\lfloor\frac{r-l+1}{2}\rfloor]$ ， $[\lfloor\frac{r-l+1}{2}\rfloor+1,r]$ ，求最少的查找次数使最终的区间为 $[x,x]$ 。多组样例。



原题目中的数据范围为 $1\le n \le 2^{20},1\le q\le10^2,1\le num\le 10^9$ ，可以考虑采用 $\text{map}$ 离散化后进行暴力 $\text{dfs}$ 查找（因为 $q$ 最多只有 $100$ ）。



注意此题的贪心不可行，因为样例 $2$ 中查询 $10$ 的位置时直接贪心的选取小的区间 $[1,6]$ 会使后来 $10$ 出现在区间中央，使得解法不是最优，于是考虑对每种情况都进行一遍 $dfs$ 取最小值。时间复杂度 $O(nq)$ ，可以通过此题。

AC Code:

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
map<int,int>mp;
int dfs(int x,int l,int r)
{
	if(l==r)
		return 0;
	int len=r-l+1,mid=l+r>>1;
	if(len%2==0)
	{
		if(x<=mid)
			return dfs(x,l,mid)+1;
		else
			return dfs(x,mid+1,r)+1;
	}
	else
	{
		if(x<mid)
			return min(dfs(x,l,mid-1),dfs(x,l,mid))+1;
		else if(x>mid)
			return min(dfs(x,mid+1,r),dfs(x,mid,r))+1;
		else
			return dfs(x,l,mid)+1;
	}
	return 10086;
}
int main()
{
	ios::sync_with_stdio(false);
	int n,q,k;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>k;
		mp[k]=i;
	}
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int x;
		cin>>x;
		x=mp[x];
		cout<<dfs(x,1,n)<<endl;
	}
	return 0;
}
```



对于本题的 $\text{extra sub}$ ，由于数据范围达到了 $1\le n \le2^{60},1\le sumq\le 2^{20}$ ，我们要考虑更优的做法。



由于二分查找，所以答案只能为 $\lfloor\log_2n\rfloor$ ， $\lfloor\log_2n\rfloor+1$ 。考虑寻找其中规律。



通过~~打 表~~观察分析可得，设 $n$ 的二进制开头连续的 $1$ 的个数为 $s$ ，结尾连续的 $0$ 的个数为 $t$ ，当 $2|n$ 时区间长度确定，不会影响下一步操作，故设循环节长 $len=2^t$ ，当 $x$ 对 $len$ 取膜后位于 $len$ 的左右两部分，长度 $\le 2^s-2$ 时此时的答案由奇偶性决定，而在中间部分时（即对于两端的距离均 $>2^s-2$ ）时答案固定为 $\lfloor\log_2n\rfloor$ 。



时间复杂度 $O(q)$ ，可以通过~~80分~~。



因为本题中的 $x$ 过大，取模时速度较慢，由于模数不一定与 $10$ 互质，无法使用蒙哥马利，只能考虑采用 $\text{barrett}$ 加快取模速度。预处理一个常量 $mu=\frac{2^{2\times k}}{len}$ （要求取模的数 $x$ 的位数 $\le2\times k$ 且模数位数 $\le k$ ），则 $mu\times \frac{n}{2^{2\times k}}$ 就等于 $2$ 的近似值，当 $2\times k$ 足够大时，近似值可以~~胡萝卜鸡~~忽略不计，由 $n \bmod p=n-\lfloor\frac{n}{p}\rfloor\times p$ 可得 $n \bmod len=n-len\times mu\times \frac{n}{2^{2\times k}}$ ，若得到的值 $\ge len$ 则减去 $len$ 即可得到正确结果。

于是采用此优化后代码运行速率大大加快，可以通过此题。注意计算时由于数字过大导致溢出 $\text{unsigned long long}$ 的情况。

AC Code（由于修改了 $114514$ 次所以比较丑）:

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
typedef __uint128_t L;
typedef unsigned long long ull;
ull sd = 111111111111111111ull, sd2, k = 1;
ull qu, n;
ull ans;
inline ull get_q(int i)
{
	sd = (sd2 ^ (sd2 >> 3)) + 998244353;
	return ((sd2 = sd ^ (sd << 37)) & k) + ((i & 1) ? 0 : (n - k - 1));
}
struct FastMod
{
    ull b,m;
    FastMod(ull b):b(b),m(ull((L(1)<<56)/b)){}
    ull reduce(ull a)
    {
        ull q=(ull)((L(m)*a)>>56);
        ull r=a-q*b;
        return r>=b?r-b:r;
    }
};
FastMod F(2);
inline ull log2(ull x)
{
	return 63-__builtin_clzll(x);
} 
ull q, q2;
ull logn,len,t=0,s=0;
ull getzero(ull x)
{
	ull ans=0;
	while((x&1)==0)
	{
		x>>=1;
		ans++;
	}
	return ans;
}
ull getone(ull x)
{
	ull ans=0;
	while(x)
	{
		if(x%2)
			ans++;
		else
			ans=0;
		x>>=1;
	}
	return ans;
}
void init()
{
	t=getzero(n);
	s=getone(n);
	logn=log2(n);
	len=n>>t;
	F=FastMod(len);
}
inline ull get_ans(ull x)
{
	if(n==1)
		return logn;
	x=F.reduce(x);
//	cout<<len<<" "<<x<<endl;
	if(x>len>>1)
		x=len-x-1;
	return (x<((ull)1<<s)-2&&x&1)?logn+(ull)1:logn; 
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	sd2 = n;
	while((k << 1) <= n + 1) k <<= 1;
	k -= 1;
	cin >> q >> q2;
	init();
	for(int i = 1; i <= q; i++)
	{
		cin >> qu;
		ans += get_ans(qu) * i;
	}
	for(int i = 1; i <= q2; i++)
	{
		qu = get_q(i);
		ans += get_ans(qu) * (i + q);
	}
	cout << ans << endl;
	return 0;
}
```



---

