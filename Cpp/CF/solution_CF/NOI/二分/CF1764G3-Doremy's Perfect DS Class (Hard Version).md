# Doremy's Perfect DS Class (Hard Version)

## 题目描述

本题与另外两个版本的唯一区别在于最多允许的查询次数。在本版本中，你最多可以进行 $ \mathbf{20} $ 次查询。只有当你解决了所有版本的问题后，才能进行 Hack。

这是一个交互题。

“大家好！Doremy 的完美数据结构课马上开始啦！想要拥有和我一样高的智商就来努力吧！”在今天的数据结构课上，Doremy 正在教大家一个强大的数据结构——Doremy 树！现在她给你出了一道小测验，以证明你在认真听课。

给定一个长度为 $ m $ 的数组 $ a $，Doremy 树支持查询 $ Q(l,r,k) $，其中 $ 1 \leq l \leq r \leq m $ 且 $ 1 \leq k \leq m $，该查询返回数组 $ \left[\lfloor\frac{a_l}{k} \rfloor, \lfloor\frac{a_{l+1}}{k} \rfloor, \ldots, \lfloor\frac{a_r}{k} \rfloor\right] $ 中不同整数的个数。

Doremy 有一个秘密排列 $ p $，它是 $ 1 $ 到 $ n $ 的一个排列。你可以进行查询，每次查询你给出 $ 3 $ 个整数 $ l,r,k $（$ 1 \leq l \leq r \leq n $，$ 1 \leq k \leq n $），你会收到 $ Q(l,r,k) $ 在数组 $ p $ 上的值。你能否在最多 $ \mathbf{20} $ 次查询内，找到下标 $ y $（$ 1 \leq y \leq n $）使得 $ p_y=1 $？

注意，排列 $ p $ 在你进行任何查询之前就已经确定。

## 说明/提示

示例中的排列为 $ [3,5,2,1,4] $。

示例交互过程如下（仅为说明，空行仅为清晰起见）：

- 第一次查询，$ \lfloor\frac{3}{4}\rfloor=0,\lfloor\frac{5}{4}\rfloor=1,\lfloor\frac{2}{4}\rfloor=0 $，所以答案为 $ 2 $。
- 第二次查询，$ \lfloor\frac{2}{3}\rfloor=0,\lfloor\frac{1}{3}\rfloor=0,\lfloor\frac{4}{3}\rfloor=1 $，所以答案仍为 $ 2 $。
- 第三次查询，$ \lfloor\frac{2}{5}\rfloor=0,\lfloor\frac{1}{5}\rfloor=0 $，所以答案为 $ 1 $。
- 第四次查询，$ \lfloor\frac{2}{2}\rfloor=1,\lfloor\frac{1}{2}\rfloor=0,\lfloor\frac{4}{2}\rfloor=2 $，所以答案为 $ 3 $。

在 $ 4 $ 次查询后得到了正确答案，因此该过程判为正确。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5

2

2

1

3```

### 输出

```
? 1 3 4

? 3 5 3

? 3 4 5

? 3 5 2

! 4```

# 题解

## 作者：dead_X (赞：11)

## 前言

3,000 AC 纪念！

## 思路

考虑二分，即判定 $x\in[1,r]$。

先考虑 $k=2$ 的情况，对于一个询问区间，如果 $2x$ 和 $2x+1$ 一个在里面，一个在外面，我们就称 $x$ 为 disconnected element，我们可以通过 $Q(l,r,2)$ 求出一个区间的 disconnected element 数量。

显然如果 $2x$ 和 $2x+1$ 都是 $[1,n]$ 内的整数，那么它们对 $Q(1,t,2)$ 和 $Q(t+1,n,2)$ 的贡献是一样的。 

因此如果 $n$ 是奇数，我们已经做完了：$1$ 一定在 disconnected element 更多的一侧。

如果 $n$ 是偶数，我们可能出现 $1$ 在左边 $n$ 在右边这种情况，一种 Naive 的方式是直接暴力求出 $n$ 在哪里（因为只有 $\frac{n}{n}\geq 1$），需要 $30$ 次。

稍微改进一点的方法是我们在二分到两侧 disconnected element 相同之后确定 $n$ 在哪一侧，只需要 $21$ 次。

最后考虑在二分的最后一次优化掉一个询问。记 $q(l,r)=Q(l,r,2)$，则我们现在已知 $A=q(1,l+1)-q(1,l-1),B=q(l+2,n)-q(l,n)$（因为这几个值都在之前的二分被查询过），我们发现 $1$ 对 $(A,B)$ 的贡献一定是 $(1,-1)$，而剩下的数对 $(A,B)$ 的贡献可能是 $(1,1)$ 或 $(-1,-1)$，先找出那个贡献，再询问其中有意义的一侧即可。

特别地，如果我们仍然无法确定 $n$ 是否在当前二分的范围内，直接询问这个元素是否是 $n$ 即可。

## 代码

感觉比 std 好看。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int query(int l,int r,int k)
{
	printf("? %d %d %d\n",l,r,k),
	fflush(stdout);
	return read();
}
int F(int l,int r){return (query(l,r,2)<<1)-(r-l+1);}
int f[2003],g[2003];
signed main()
{
	int n=read(),l=1,r=n-1,ans=n,flg=-1;
	g[1]=f[n]=((n+1)&1)+1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(l==r)
		{
			if(flg==-1&&((n+1)&1))
			{
				if(mid==1) (query(mid+1,n,n)-1)&&(ans=l);
				else (!(query(1,mid,n)-1))&&(ans=l);
				break;
			}
			else if(g[l]-g[l+2]) (F(1,l)>f[l-1])&&(ans=l);
			else (F(l+1,n)<g[l+2])&&(ans=l);
			break;
		}
		f[mid]=F(1,mid),
		g[mid+1]=F(mid+1,n);
		int v=f[mid]-g[mid+1];
		if(v>0) ans=mid,r=mid-1;
		else if(v<0) l=mid+1;
		else
		{
			if(flg==-1)
			{
				if(mid==1) flg=!(query(mid+1,n,n)-1);
				else flg=query(1,mid,n)-1;
			}
			if(flg) l=mid+1;
			else ans=mid,r=mid-1;
		}
	}
	printf("! %d\n",ans);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

这种题目一般都考虑从较特殊的 $k = 2$ 或 $k = n$ 入手。$k = n$ 看起来不太可行，因此考虑 $k = 2$。

从 $30$ 次询问限制可以想到二分。设 $\mathrm{solve}(l, r)$ 表示已知答案 $a \in [l, r]$，希望确定答案。设 $m = \frac {l + r} 2$。

关键问题在于确定答案究竟在 $[l, m]$ 还是 $[m + 1, r]$ 中。这里有个有趣的思想，就是我们不能将眼光仅局限于 $[l, r]$，因为 $\mathrm{solve}(l, r)$ 并不是一个严格的子问题，$l\sim r$ 并不是 $1\sim r - l + 1$ 的排列，我们依然需要依靠 $p_1\sim p_n$。换言之，我们只需要确定答案在 $[1, m]$ 或 $[m + 1, r]$ 中。

根据这样的思想，考虑如何询问。

将 $p_i$ 全部除以 $2$ 下取整，称 $x, y$ 配对当且仅当 $p_x, p_y$ 除以 $2$ 下取整相同。

当 $n$ 为奇数时，除了 $a$ 以外的所有位置均有与其配对的位置，而询问 $Q(l, r, 2)$ 相当于求出 $r - l + 1$ 减去区间配对数，则区间落单数可由 $r - l + 1$ 减去两倍区间配对数得到，即 $2Q(l, r, 2) - (r - l + 1)$。设 $f(l, r)$ 表示 $[l, r]$ 的区间落单数，则对于 $f(1, m)$ 和 $f(m + 1, n)$，因为每个除了 $a$ 以外的区间落单位置会同时在 $[1, m]$ 和 $[m + 1, n]$ 中出现，所以只需递归进入 $f$ 较大的那个区间即可。时间复杂度询问次数 $2\lceil\log_2 n\rceil \leq 20$。

当 $n$ 为偶数时，设 $p_b = n$，则 $a, b$ 均没有与其配对的位置。类似地，求出 $f(1, m)$ 和 $f(m + 1, n)$。若已知 $b\leq m$ 或 $b > m$，则扣除 $b$ 的贡献后类似 $n$ 为奇数做。否则，若 $f(1, m) > f(m + 1, n)$，说明 $a, b\leq m$。若 $f(1, m) < f(m + 1, n)$，说明 $a, b > m$。若 $f(1, m) = f(m + 1, n)$，说明 $a, b$ 在 $m$ 的两侧。

考虑确定 $b$ 的位置。注意到将所有数除以 $n$ 下取整之后，只有 $p_b = 1$，其它均为 $0$。利用这一点，我们断言若 $r - l + 1 \geq 2$，则 $b\in [l, r]$ 当且仅当 $Q(l, r, n) = 2$。因此，若 $m > 1$，可直接询问 $Q(1, m, n)$ 确定 $b$ 是否在 $[1, m]$ 中。否则 $m = 1$，因为 $n\geq 3$，所以询问 $Q(m + 1, n, n)$ 确定 $b$ 是否在 $[m + 1, n]$ 中。

确定 $b$ 的位置后，因我们向相反方向递归，所以若此时 $b\leq m$ 则接下来一定有 $b\leq m'$，若此时 $b > m$ 则接下来一定有 $b > m'$。询问次数 $2\lceil\log_2 n\rceil + 1 \leq 21$，可以通过 G2。

最后优化通常是通过已知信息简少询问次数。

考虑到卡满 $\lceil \log_2 n\rceil$ 上界的二分过程必然经过 $r - l + 1 = 2$ 的情形。当 $l \neq 1$ 时，我们必然询问过 $Q(1, l - 1, 2)$，否则 $Q(1, l - 1, 2) = 0$。当 $r\neq n$ 时，我们必然询问过 $Q(1, r, 2)$，否则 $Q(1, r, 2) = \lfloor \frac n 2\rfloor + 1$。对于 $Q(l, n, 2), Q(r + 1, n, 2)$ 同理。

考虑 $[l, r]$ 中不是 $a$ 的位置 $x$。我们容易根据此时是否确定 $b$ 来判断 $x$ 是否等于 $b$。若 $x = b$，则直接进入判断 $b$ 的位置的分支，只需花掉一次询问。若 $x\neq b$，则考虑与 $x$ 配对的位置，若与 $x$ 配对的位置 $< l$，则 $Q(1, r, 2) - Q(1, l - 1, 2) = 1$ 且 $Q(l, n, 2) - Q(r + 1, n, 2) = 2$。若与 $x$ 配对的位置 $> r$，则情况相反，不再赘述。

基于此，不妨设与 $x$ 配对的位置 $< l$，则若 $Q(1, l, 2) = Q(1, l - 1, 2)$，说明 $x = l$，$a = r$，否则说明 $x = r$，$a = l$。同样只需花掉一次询问。

综上，我们在 $r - l + 1 = 2$ 的分支少花掉了一次询问，询问次数 $2(\lceil \log_2 n\rceil - 1) + 1 + 1\leq 20$。[代码](https://codeforces.com/contest/1764/submission/183178528)。

---

## 作者：honglan0301 (赞：4)

如果还不会做 G2 题，可以先去看 [CF1764G2题解](https://www.luogu.com.cn/blog/529697/solution-cf1764g2) qwq。
## 题目分析
我们只需要在 G2 题的基础上，再在 $n$ 为偶数时优化掉一次询问就好了。

在二分的最后一次询问中，已经只剩下了 $l,l+1$ 两个位置可能是 $1$, 却还要询问两次。我们考虑优化这一次操作。

分两种情况看。当问到此时还没有区分开 $1$ 和 $n$ 的位置关系时，显然两个数中一个是 $1$, 另一个是 $n$。只需要询问一次 $1,l,n$ 或 $l+1,r,n$ 就好了。这种情况下只需要 $2\times(\log(1024)-1)+1=19$ 次操作，可以通过本题。

而当问到此刻已经区分开 $1$ 和 $n$ 时，考虑利用好之前的询问。根据我二分的规则，记询问 $l,r,k$ 的答案为 $Q(l,r,k)$, 我们应当已经知道了 $Q(1,l-1,2),Q(1,r,2),Q(l,n,2),Q(r+1,n,2)$，即知道了这几段中未配对数的数量。因为 $l,l+1$ 两个位置中不是 $1$ 的那个数必然要么和左侧段配对，要么和右侧段配对，而这是可以由上述四个询问的答案所确定的。那么我们只需根据它的配对情况询问 $1,l,2$ 或 $r,n,2$ 即可。这种情况下只需要 $2\times(\log(1024)-1)+1+1=20$ 次操作，可以通过本题。

注意有一些边界条件的答案，虽然我们可能没有问过，但也应该知道。比如 $Q(1,1,2)=1,Q(1,0,2)=0$ 等等。

## 代码
```cpp
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>
#include <stdlib.h>
using namespace std;
int n,flag,q[1035][1035];
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
int ask(int l,int r,int k)
{
	printf("? %d %d %d\n",l,r,k);
	fflush(stdout);
	return read();
}
void putans(int x)
{
	printf("! %d\n",x);
	fflush(stdout);
}
bool check1(int x)
{
	int a=ask(1,x,2);
	int b=0;
	if(x+1<=n)
	{
		b=ask(x+1,n,2);
	}
	int c=x-2*(x-a);
	int d=(n-x)-2*((n-x)-b);
	if(c>d)
	{
		return 1;
	}
	return 0;
}
void solve1()//n为奇数 
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check1(mid))
		{
			r=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	putans(l);
}
bool check2(int x)
{
	int a=ask(1,x,2);
	q[1][x]=a;//记录询问答案 
	int b=ask(x+1,n,2);
	q[x+1][n]=b;
	int c=x-2*(x-a);
	int d=(n-x)-2*((n-x)-b);
	if(c>d)
	{
		return 1;
	}
	else if(c<d)
	{
		return 0;
	}
	else
	{
		if(!flag)
		{
			int e=ask(1,x,n);
			if(e==2)
			{
				flag=1;
				return 0;
			}
			else
			{
				flag=2;
				return 1;
			}
		}
		else if(flag==1)
		{
			return 0;
		}
		else if(flag==2)
		{
			return 1;
		}
	}
}
void solve2()//n为偶数 
{
	int l=1,r=n;
	while(l<r)
	{
		if(l+1==r)//最后一次要特殊判断 
		{
			if(!flag)//一个是1，一个是n 
			{
				int a;
				if(l>1)
				{
					a=ask(1,l,n);
				} 
				else
				{
					a=3-ask(r,n,n);
				}
				if(a==2)
				{
					l=r;
					break;
				}
				else
				{
					break;
				}
			}
			else
			{
				if(q[1][l-1]+1==q[1][r])
				{
					int a=ask(1,l,2);
					if(a==q[1][l-1])
					{
						l=r;
						break;
					}
					else
					{
						break;
					}
				}
				else if(q[r+1][n]+1==q[l][n])
				{
					int a=ask(r,n,2);
					if(a!=q[r+1][n])
					{
						l=r;
						break;
					}
					else
					{
						break;
					}
				}
			}
		}
		int mid=(l+r)>>1;
		if(check2(mid))
		{
			r=mid;
		}
		else
		{
			l=mid+1;
		}
	}
	putans(l);
}
int main()
{
	n=read();
	if(n%2==1)
	{
		solve1();
	}
	else
	{
		q[1][1]=1;//边界条件 
		q[1][0]=0;
		q[n][n]=1;
		q[n+1][n]=0;
		q[1][n]=n/2+1;
		solve2();
	}
}
```

---

## 作者：樱雪喵 (赞：3)

## G1

考虑 $1$ 和其他的数有什么不同点。我们令询问的 $k=2$，那么只有 $1$ 的值是 $0$，其余都不是。这看起来并没有什么用，因为我们只能知道不同的数的个数。

但是真的没有用吗？可以发现，若 $k=2$，则所有数下取整后是两两配对的，$\lfloor\frac{2}{2}\rfloor=\lfloor\frac{3}{2}\rfloor,\lfloor\frac{4}{2}\rfloor=\lfloor\frac{5}{2}\rfloor,\dots$。当 $n$ 为奇数时，只有 $1$ 是单出来的；$n$ 为偶数时，$1$ 和 $n$ 两个数都是单出来的。

先考虑奇数的情况怎么做。

对于一个区间 $[l,r]$，若 $\text{query}(l,r,2)=x$，可以得到 $[l,r]$ 中有 $2x-(r-l+1)$ 个数字没有被配对。所以假设我们找了一个分界点 $mid$，并求出 $[1,mid]$ 中有 $L$ 个没配对，$[mid+1,n]$ 中有 $R$ 个没配对。那么如果同一组的数分到了一边一个，它们可以互相消掉，只有 $1$ 是无论如何都无法被配对的。

这就是说，若 $L<R$，$1$ 就在 $[mid+1,n]$ 中；否则 $1$ 在 $[1,mid]$ 中。那么我们可以二分这个 $mid$ 的位置，求出答案，询问次数 $2\log n\le 20$。

再考虑 $n$ 是偶数的情况。

现在，我们同样询问得到了 $L$ 和 $R$ 的值。分类讨论 $1$ 和 $n$ 的位置情况：

- 如果都在左侧，应该是 $L=R+2$；
- 如果都在右侧，应该是 $R=L+2$；
- 如果一左一右，$L=R$。

发现在一左一右的情况下，我们没法判断哪一边是 $1$。

但仔细思考一下，发现 $n$ 的位置是好找的：令 $k=n$，这样只有 $n$ 的答案是 $1$，其他都是 $0$。因此可以在一开始先二分找出 $n$ 的位置，就能知道 $L=R$ 时 $1$ 在哪边了。

找 $n$ 的位置只需要询问一边，所以总询问次数是 $3\log n\le 30$。

## G2

发现找 $1$ 的位置的过程是不好优化的，现在的询问次数瓶颈在找 $n$ 的位置。

实际上，我们只关心 $n$ 在 $mid$ 的哪一侧，而不关心它的具体位置。可以这样优化：

- 当第一次出现 $L=R$ 的情况时，我们通过一次 $\text{query}(1,mid,n)$ 判断 $n$ 在 $mid$ 的哪一侧。
- 当再次出现这个情况时，发现有一条性质：如果之前判断过 $n$ 在 $mid$ 的右侧，我们的二分区间只会往左不会往右，也就是说以后 $n$ 永远在 $mid$ 的右侧，反之同理。

因此，在第一次判断时记录 $n$ 在 $mid$ 的哪一侧，以后不需要再次判断。总询问次数为 $2\log n+1\le 21$。

## G3

限制是 $20$，还需要再卡掉一次询问。

考虑二分的终止状态，在 $l+1=r$ 的情况下，把两边都问一遍看起来就不太划算。能不能只问一边呢？

### Case 1
如果我们现在还没询问过 $n$ 在 $mid$ 的哪一侧，说明 $n$ 还在区间 $[l,r]$ 中。换句话讲，$l$ 和 $r$ 的位置上一个是 $n$ 一个是 $1$。

这种情况是好办的：一次询问就能找出 $n$ 的位置，剩下的那个自然是 $1$。

### Case 2

$n$ 不在区间里，考虑我们已经知道了哪些信息。

在达成当前局面之前，我们曾令 $mid=l-1$，也曾令 $mid=r$。也就是说，我们知道 $\text{query}(1,l-1,2)$ 和 $\text{query}(r+1,n,2)$ 的答案。

设 $[1,l-1]$ 未配对的个数为 $L$，$[r+1,n]$ 为 $R$。因为已经知道 $n$ 在哪一侧，可以在这步直接减掉 $n$ 的贡献。

那么若 $L<R$，表明 $[l,r]$ 中剩余的两个数，除了 $1$ 以外的那个是跟 $[1,l-1]$ 中的某个数配对的。  
因此我们询问 $[1,l]$ 中未配对的个数为 $L'$，若 $L'<L$，说明这个数与左边配对成功了，$1$ 在 $r$ 位置上；否则说明配对失败了，$1$ 在 $l$ 位置。

$L>R$ 同理。

至此，最后一步二分被优化到一次询问，询问次数上界为 $2\log n\le 20$。

```cpp
const int N=2005;
int n,L[N],R[N];
il int ask(int l,int r,int k)
{
    cout<<"? "<<l<<" "<<r<<" "<<k<<endl;
    int x=read();
    if(k==2) {if(l==1) L[r]=2*x-(r-l+1); if(r==n) R[l]=2*x-(r-l+1);}
    return x;
}
bool flag,pos;
int main()
{
    n=read();
    int l=1,r=n;
    while(l<r)
    {
        if(l+1==r)
        {
            if(!flag&&n%2==0) 
            {
                if(l>1) pos=(ask(1,l,n)>1);
                else pos=(ask(r,n,n)==1);
                if(pos) l=r;else r=l;break;
            }
            int ansl=L[l-1],ansr=R[r+1];
            if(n%2==0) {if(pos) ansl--;else ansr--;}
            if(ansl>ansr)
            {
                ask(1,l,2);
                if(L[l]<L[l-1]) l=r;
                else r=l;
            }
            else
            {
                ask(r,n,2);
                if(R[r]<R[r+1]) r=l;
                else l=r;
            }
            break;
        }
        int mid=(l+r)>>1;
        ask(1,mid,2),ask(mid+1,n,2);
        if(L[mid]>R[mid+1]) r=mid;
        else if(L[mid]<R[mid+1]) l=mid+1;
        else 
        {
            if(!flag) 
            {
                if(mid>1) pos=(ask(1,mid,n)>1);
                else pos=(ask(mid+1,n,n)==1);
                flag=1;
            }
            if(pos) l=mid+1; else r=mid;
        }
    }
    cout<<"! "<<l<<endl;
    return 0;
}
```

---

## 作者：james1BadCreeper (赞：2)

询问能告诉我们什么？好奇怪啊，不知道。尝试从给定的 $k$ 值开始分析。$k=1$ 没什么意义，然后尝试从特殊的，比如 $k=2,n$ 开始分析。$k=n$ 比较好说，只有 $n$ 可以被记入答案，可以根据此找出 $n$ 的位置。$k=2$ 则可以将数分为两组，在 $n$ 为奇数时只有 $1$ 是单独一组，$n$ 为偶数时只有 $1,n$ 是单独一组。

从别的地方再想一想，都要求 $\log$ 级别的询问，不难想到二分。设 `solve(l, r)` 代表答案在 $[l,r]$ 的位置中，我们需要确定 $1$ 在 $[l,mid]$ 还是 $[mid+1,r]$ 里。咦，感觉不太对，不是严格的子问题！但是我们只需要寻找答案在哪里，因此只需要分别答案在 $[1,mid]$ 还是 $[mid+1,n]$ 就好了。

选择从 $k=2$ 入手，$x,y$ 分为一组仅当它们除以二下取整后的值相等。我们可以求出两个区间中在自己区间内没有匹配的数的数量，然后这个数量大的，答案就在哪里（因为剩下的每有一个都是成对的）。

$n$ 是偶数怎么办呢？我们只需要找到 $n$ 就行，不难发现 $k=n$ 可以很好的完成这个任务。当两个区间的值相等时，说明 $1,n$ 各占一个，我们令 $k=n$，询问其中一个，看 $n$ 是否在其中。找到 $n$ 的位置之后发现之后的递归不会受到影响（如果 $p_n> mid$，我们会递归到 $[l,mid]$，必定有 $p_n>mid'$）。

这个做法可以通过 G2。想过掉 G3，我们需要想方法杀掉那一次多余的询问。

怎么杀？对于 $r-l+1=2$ 的情况，使用两次询问有点扯皮，我们看能不能只用一次询问杀掉它。核心思想是，充分利用我们之前问出来的信息。当我们递归到 $[l,r]$ 时，曾令一个 $mid=l-1$，也令了一个 $mid=r$，因此我们知道 $Q(1,l-1,2),Q(1,r,2),Q(l,n,2),Q(r+1,n,2)$ 的答案。现在 $l,r$ 中一个是 $1$，一个是和其他数能匹配上的某个奇怪的东西，吗？注意，另一个可能是 $n$，如果我们还没有确定 $n$ 的位置，那么通过询问 $Q(r,n,n)$ 或 $Q(1,l,n)$ 将其判掉。

现在再看怎么 $l,r$ 一个是 $1$，另一个是可匹配数。可匹配数只能配在 $[1,l-1]$ 或 $[r+1,n]$，如果 $Q(1,l-1,2)+1=Q(1,r,2)$，那么说明可匹配数的匹配数是开在 $[1,l-1]$ 的（这个数除以二下去整的值与 $[1,l-1]$ 中的某个数撞了），否则开在 $[r+1,n]$。确定了这一点之后，我们就可以锁定 $1$ 的位置了！以开在 $[1,l-1]$ 为例，如果 $Q(1,l-1,2)=Q(1,l,2)$，说明 $l$ 处开可匹配数，与 $[1,l-1]$ 中的某个数匹配，$1$ 就开在 $r$ 处。

这样在 $r-l+1=2$ 时我们只花费了一次询问，可以通过 G3。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n, flag; 
map<pair<int, int>, int> f; 
int query(int l, int r, int k) {
	if (l >= r) return l == r; 
	if (l == 1 && r == n) return n / k + 1; 
	if (k == 2 && f.find({l, r}) != f.end()) return f[{l, r}]; 
	printf("? %d %d %d\n", l, r, k); fflush(stdout); 
	int ans; scanf("%d", &ans); 
	if (k == 2) f[{l, r}] = ans; 
	return ans; 
}

int solve(int l, int r) {
	if (l == r) return l; 
	if (n % 2 == 0 && r - l + 1 == 2) {
		if (!flag) {
			if (r < n) return query(r, n, n) == 2 ? l : r; 
			return query(1, l, n) == 2 ? r : l; 
		}
		if (query(1, r, 2) - query(1, l - 1, 2) == 1) { // 与非 1 数的匹配在 [1, l-1]
			int x = query(1, l - 1, 2), y = query(1, l, 2); 
			if (x + 1 == y) return l; 
			return r; 
		} else {
			int x = query(r + 1, n, 2), y = query(r, n, 2); 
			if (x + 1 == y) return r; 
			return l; 
		}
	}
	int mid = l + r >> 1; 
	int L = 2 * query(1, mid, 2) - mid; 
	int R = 2 * query(mid + 1, n, 2) - (n - mid); 
	if (n % 2 == 0) {
		if (!flag) {
			if (L == R) {
				bool con = 0; 
				if (mid > 1 && query(1, mid, n) == 2) con = 1; 
				if (con) flag = 1, --L; 
				else flag = -1, --R; 
			}
		} else {
			if (flag == 1) --L; 
			else --R; 
		}
	}
	return L > R ? solve(l, mid) : solve(mid + 1, r); 
}

int main(void) {
	scanf("%d", &n); 
	return !printf("! %d\n", solve(1, n)); 
}
```

---

## 作者：tzc_wk (赞：1)

考虑什么样的询问能得到比较有用的信息。显然对于一般（即不算大不算小）的 $k$ 我们其实不能得到任何信息，这是因为区间中不同数这个东西其实没有什么特别好的性质可言，因此我们只能从特别大和特别小的 $k$ 入手：

- 当 $k=n$ 时候，只有 $\lfloor\dfrac{n}{k}\rfloor=1$，其他都是 $0$，这可以帮助我们确定 $n$ 的位置。
- 当 $k=2$ 时候，不难发现，对于大部分数都在 $[1,n]$ 中存在另一个数满足俩数 $\lfloor\dfrac{i}{k}\rfloor$ 相等。只有俩例外：$1$ 与 $n$ 是偶数时的 $n$。

稍加思考可以发现，第二条是非常重要的性质，它可以帮我们确定 $1,n$ 的位置，而第一条则是将 $1$ 与 $n$ 区别开来的。更具体地，对于任意的 $a_i\ne 1$ 且 $a_i\ne n$，都有 $Q(1,i,2)-Q(1,i-1,2)+Q(i,n,2)-Q(i+1,n,2)=1$，而对于 $a_i=1$ 来说上式值则为 $2$。

不妨假设 $n$ 是偶数。我们把 $1$ 和 $n$ 的位置称为“**关键位置**”，那么考虑 $v_i=Q(1,i,2)+Q(1,n,2)-Q(i+1,n,2)-i$，显然 $v_i$ 就是 $[1,i]$ 中关键位置的个数。这样一个朴素想法是先用 $k=n$ 二分出 $n$ 的位置，然后再二分计算 $v_i$ 来判断 $1$ 在左边还是在右边。这样朴素实现是 $3\log n$，但是由于实现不够精细需要 $31$ 次询问，连 G1 都过不了。

我们发现分两次二分其实很浪费，考虑将两个数一起二分，定义状态 $\text{solve}(l,r,op)$ 表示目前二分到 $[l,r]$，$op=2$ 说明 $1,n$ 都在里面，$op=1$ 说明只有 $1$ 在里面，考虑怎么规划下一次二分：

- 如果 $[l,mid]$ 中没有关键位置，那么直接 $\text{solve}(mid+1,r,op)$。
- 如果 $[l,mid]$ 中关键位置数量 $=op$，那么同理 $\text{solve}(l,mid,op)$。
- 如果 $op=2$ 且 $[l,mid]$ 中恰有一个关键位置，那么通过 $Q(l,mid,n)$ 判断左边的关键位置是不是 $n$，如果是就 $\text{solve}(mid+1,r,1)$，否则 $\text{solve}(l,mid,1)$。
- 注意特判 $r-l=1,op=2$ 的情形。

这样差不多是 $2\log n$ 的，但是由于中途多调用了一次 $Q(l,mid,n)$ 所以最坏需要 $21$ 次询问，能过前两个 subtask，但是第三个还需卡常。

我们发现那个 $Q(l,mid,n)$ 是不太好省去的，因此可以卡的地方在于**最后一次二分的询问次数**，即 $r-l=1,op=1$。我们发现，要么 $Q(1,r,2)-Q(1,l-1,2)=1$ 要么 $Q(l,n,2)-Q(r+1,n,2)=1$，取决于这段区间中不同于 $1$ 的数所配对的位置在左边还是右边，如果是在左边那么我们调用 $Q(r,n,1)$ 判断是等于 $Q(l,n,2)$ 还是 $Q(r+1,n,2)$ 即可，如果在右边则调用 $Q(1,l,2)$，由于 $Q(1,r,2),Q(1,l-1,2),Q(l,n,2),Q(r+1,n,2)$ 这四个数的值肯定在之前的二分中就事先问好了，所以最多只会多一次调用，刚好 $20$ 次询问。

```cpp
const int MAXN=1024;
int n;map<tuple<int,int,int>,int>mem;
int query(int l,int r,int k){
	if(l>r)return 0;
	if(l==1&&r==n)return n/k+1;
	if(mem.count(mt(l,r,k)))return mem[mt(l,r,k)];
	cout<<"? "<<l<<" "<<r<<" "<<k<<endl;
	int res;cin>>res;return mem[mt(l,r,k)]=res;
}
int cnt[MAXN+5];
int ask_key(int x){
	if(~cnt[x])return cnt[x];
	return cnt[x]=query(1,x,2)+query(1,n,2)-query(x+1,n,2)-x;
}
int calc(int l,int r,int k,int hav){
	if(l==r)return l;
	if(k==2&&r-l==1){
		if(l==1)return query(2,3,n)==2?1:2;
		else return query(l-1,l,n)==2?r:l;
	}
	if(k==1&&r-l==1){
		if(query(1,r,2)-query(1,l-1,2)==1)return query(1,l,2)==query(1,l-1,2)?r:l;
		else return query(r,n,2)==query(r+1,n,2)?l:r;
	}
	int mid=l+r>>1,v=ask_key(mid)-hav;
	if(k==2){
		if(v==2)return calc(l,mid,k,hav);
		else if(!v)return calc(mid+1,r,k,hav);
		else{
			if(query(l,mid,n)==2)return calc(mid+1,r,1,hav+1);
			else return calc(l,mid,1,hav);
		}
	}else return (v)?calc(l,mid,k,hav):calc(mid+1,r,k,hav);
}
int main(){
	scanf("%d",&n);
	if(n%2==1){
		memset(cnt,-1,sizeof(cnt));
		int L=1,R=n,p=0;
		while(L<=R){
			int mid=L+R>>1;
			if(!ask_key(mid))L=mid+1;
			else p=mid,R=mid-1;
		}cout<<"! "<<p<<endl;
	}else{
		memset(cnt,-1,sizeof(cnt));int res=calc(1,n,2,0);
		cout<<"! "<<res<<endl;
	}
	return 0;
}
```



---

## 作者：Iam1789 (赞：1)

## 前言
合格考的时候曾经尝试搞出这道题，但是当时并没有什么思路。今天重新思考了一下会了。我果然还是只能随机思考 adhoc 题。
## 正文
先考虑 $n$ 为奇数，考虑 $k=2$ 时，按 $\lfloor \frac{a}{k} \rfloor$ 的值将 $1$ 到 $n$ 分组，则有大漂亮性质：$1$ 所在的组大小为 $1$，其它组大小皆为 $2$。

考虑判断 $1$ 的位置 $y$ 是否 $\leq \text{mid}$。对于所有大小为 $2$ 的组，设其两个元素的位置全 $\leq \text{mid}$ 的有 $x$ 对，全 $> \text{mid}$ 的有 $y$ 对，剩下的有 $z$ 对。询问 $(1,\text{mid},2)$ 和 $(\text{mid}+1,r,2)$，设结果分别为 $b,c$，有如下方程组：

$$ \begin{cases}  x+y+z=\lfloor\frac{n}{2} \rfloor+1\ \\x+z=b \\ y+z=c\end{cases}$$

方程组足以解出 $x,y,z$。

$a_1,\cdots,a_{\text{mid}}$ 中有 $2x+z$ 个不为 $1$ 的元素，如果 $2x+z=\text{mid}$，则 $1$ 的位置 $>\text{mid}$，否则 $\leq \text{mid}$。

考虑二分 $\text{mid}$，最劣询问次数为 $2\lceil\log n\rceil$。

接着考虑 $n$ 为偶数。与 $n$ 为奇数不同的是，除了 $1$ 之外，$n$ 所在的组大小为 $1$。因此在判断的时候，可能同时出现 $2x+z\neq \text{mid}$ 和 $2y+z \neq n-\text{mid}$ 的情况。此时 $1$ 与 $n$ 分别在 $\text{mid}$ 的两边。如何判断哪边是 $n$ 呢？如果 $\text{mid} >1$，我们询问 $(1,\text{mid},n)$，否则询问 $(\text{mid}+1,n,n)$。如果结果为 $2$，则说明 $n$ 在对应区域，将其排除。最劣情况下询问次数为 $3\lceil\log n\rceil$，当 $n=1024$ 时为 $30$ 次，可以通过第一个子任务。

考虑第一次遇到上述情况后，我们便知道了 $1$ 相对于 $n$ 是在左边还是在右边，记录下来，后面无需再问，最劣询问次数降低为 $2\lceil\log n \rceil +1$，当 $n=1024$ 时为 $21$ 次，可以通过第二个子任务，但是第三个子任务恰好被卡了 $1$ 次/oh

考虑二分时最后一次判断。此时 $1$ 的位置的范围 $[l,r]$ 已经被限制为 $r-l=1$。如果此时仍未能区分出 $1$ 和 $n$，我们直接用上文方法区分。
否则此时的 $a_l$ 和 $a_r$ 其中一个为 $1$，另一个所在组大小为 $2$。这次判断前我们已经询问过 $(1,l-1,2),(1,r,2),(l,n,2),(r+1,n,2)$ 四组询问，我们可以据此判断与非 $1$ 数配对数的位置是 $<l$ 还是 $>r$。设上述四组询问结果分别为 $d,e,f,g$。若 $d=e$，则其位置 $<l$，反之亦然。不妨设其位置 $<l$。我们进行一次询问 $(r,n,2)$，设结果为 $h$。若 $h>g$，则 $1$ 的位置为 $r$，否则为 $l$。最劣询问次数降低为 $2\lceil\log n \rceil$，当 $n=1024$ 时为 $20$ 次，可以通过所有子任务。

---

## 作者：Sol1 (赞：1)

场切 3000，好耶。~~要是 G1 没脑残 wa 半天估计就场切 3300 了。~~

这题的 subtask 设置还是很好的。

## G1（$3\log_2 n$ 次）

首先我们考虑如果能问任意多次如何求出答案。

数据范围明显提示二分，考虑整体折半：询问 $[1,m],k$ 和 $[m+1,n],k$。

考虑到如果 $k>2$ 则 $1$ 没有特殊性，即整体除 $k$ 下取整以后有多于一个数是 $0$；同时 $k=1$ 的答案就是区间长度，从而我们先尝试询问 $k=2$。但是在 $k=2$ 时，如果 $n$ 是偶数，那么 $1$ 和 $n$ 的地位一致：都只出现 1 次，也无法区分。于是我们先考虑 $n$ 是奇数的情况。

$n$ 为奇数时，一侧的区间会比另一侧长 1 单位。如果一个数在两侧都出现，则既不会影响两侧的答案的差，也不会影响两侧的长度的差；如果只在一侧出现，则同时影响答案的差和长度的差。

从而如果没有 $1$，那么我们不需要查询即可知道两侧答案的差就是长度的差除以 2。因为扰动的只有一个 $1$，所以我们尝试从两侧分别删掉 $1$（一侧删掉后，查询结果与长度分别 $-1$），$1$ 所在的一侧删掉后将满足长度与查询结果的对应关系，从而我们可以确定 $1$ 在哪一侧。

但是这个方法依赖于除 $2$ 后除了 $0$ 以外的所有数都出现两次，因此第一次二分之后无法直接对两侧递归。

注意到上面的方法并不依赖于折半，即，对于任意 $i$ 都可以确定 $1$ 是在 $[1,i]$ 中还是 $[i+1,n]$ 中。

从而我们二分到区间 $[l,r]$ 后，求 $m=\dfrac{l+r}{2}$，然后两次询问求 $1$ 是在 $[1,m]$ 还是 $[m+1,n]$，然后递归二分。

于是我们用 $2\log n$ 次询问解决 $n$ 是奇数的情况。考虑 $n$ 是偶数。

注意到整体除 $n$ 后只有 $n$ 是 $1$，从而我们很容易通过二分使用 $\log n$ 次操作求出 $n$ 的位置。然后手动把 $n$ 去掉就可以了。这里有一个细节：当二分区间长度缩小至 $2$ 时，需要从区间外捆绑一个 $0$ 来二分。

然后就用 $3\log n\leq 30$ 次询问解决了本题，可以通过 G1。

## G2（$2\log_2 n+1$ 次）

奇数的情况不用管。

$n$ 是偶数时我们真的需要 $n$ 的具体位置吗？

仔细思考一下，如果二分时 $0$ 和 $n$ 在同一边，我们只要再尝试从一边去掉两个孤立元素就可以递归二分。如果不在同一边才会导致无法区分。此时用一次询问可以求出 $n$ 在哪一边，然后 $0$ 就在另一边，然后在这之后 $n$ 就会离开二分区间，于是它在二分中点的哪一边就确定了，从而之后就不需要考虑 $n$ 了。

如此改进后 $n$ 最多消耗 $1$ 次询问，从而我们使用 $2\log_2 n+1\leq 21<25$ 次询问解决本题，可以通过 G2。

## G3（$2\log_2n$ 次）

奇数的情况还是不用管。

考虑充分利用一下询问的信息来强行省掉 $1$ 次。不妨针对二分区间长度为 $2$ 的时候进行讨论，我们需要用 $1$ 次询问解决所有情况：

### 1 $n$ 在区间内

用 $1$ 次询问求出 $n$ 的位置即可。

### 2 $n$ 不在区间内

设区间为 $[l,r]$，我们在之前一定求出了 $[1,l-1],[1,r],[l,n],[r+1,n]$ 四个区间的答案。区间中的另一个数的另一次出现一定在区间外的某一侧。不妨记上面的 $4$ 个区间的答案分别为 $v_1,v_2,v_3,v_4$。

#### 2.1 出现在 $[1,l-1]$

此时必有 $v_1+1=v_2,v_4+2=v_3$，可以利用该条件进行判断。

此时，询问 $[1,l]$，如果答案等于 $v_1$，则说明 $l$ 处的数在左侧出现过，从而答案是 $r$；否则答案是 $l$。

#### 2.2 出现在 $[r+1,n]$

判断条件改为 $v_1+2=v_2,v_4+1=v_3$，剩下同理。

于是最大操作次数下降至 $2(\log_2n-1)+1+1=2\log_2n\leq 20$，可以通过 G3。

```cpp
int n, nps, cnt, atl;
map <pair <int, int>, int> mp;

inline void find1(int l, int r) {
    if (l == r) {
        cout << "! " << l << endl;
        return;
    }
    if (l == r - 1) {
        if (n % 2 == 0 && atl == -1) {
            if (l > 1) {
                cout << "? " << 1 << " " << l << " " << n << endl;
                int res;
                cin >> res;
                if (res == 2) cout << "! " << r << endl;
                else cout << "! " << l << endl;
            } else {
                cout << "? " << r << " " << n << " " << n << endl;
                int res;
                cin >> res;
                if (res == 2) cout << "! " << l << endl;
                else cout << "! " << r << endl;
            }
        } else {
            int vll = mp[make_pair(1, l - 1)];
            int vlr = mp[make_pair(1, r)];
            int vrl = mp[make_pair(l, n)];
            int vrr = mp[make_pair(r + 1, n)];
            if (vll + 1 == vlr) {
                cout << "? " << 1 << " " << l << " " << 2 << endl;
                int res; cin >> res;
                if (res == vll + 1) cout << "! " << l << endl;
                else cout << "! " << r << endl;
            } else {
                cout << "? " << r << " " << n << " " << 2 << endl;
                int res; cin >> res;
                if (res == vrr + 1) cout << "! " << r << endl;
                else cout << "! " << l << endl;
            }
        }
        return;
    }
    int m = l + r >> 1;
    int resl; 
    if (mp[make_pair(1, m)]) resl = mp[make_pair(1, m)];
    else {
        cout << "? " << 1 << " " << m << " " << 2 << endl; 
        cin >> resl;
        mp[make_pair(1, m)] = resl;
    }
    int resr;
    if (mp[make_pair(m + 1, n)]) resr = mp[make_pair(m + 1, n)];
    else {
        cout << "? " << m + 1 << " " << n << " " << 2 << endl;
        cin >> resr;
        mp[make_pair(m + 1, n)] = resr;
    }
    
    int lenl = m, lenr = n - m;
    if (atl == 0) {
        lenr--;
        resr--;
    } else if (atl == 1) {
        lenl--;
        resl--;
    }
    if ((resl - 1 - resr) * 2 == (lenl - lenr - 1)) find1(l, m);
    else if ((resr - 1 - resl) * 2 == (lenr - lenl - 1)) find1(m + 1, r);
    else if ((resl - 2 - resr) * 2 == (lenl - lenr - 2)) find1(l, m);
    else if ((resr - 2 - resl) * 2 == (lenr - lenl - 2)) find1(m + 1, r);
    else {
        if (m > 1) {
            cout << "? " << 1 << " " << m << " " << n << endl;
            int res;
            cin >> res;
            if (res == 1) {
                atl = 0;
                find1(l, m);
            } else {
                atl = 1;
                find1(m + 1, r);
            }
        } else {
            cout << "? " << m + 1 << " " << n << " " << n << endl;
            int res;
            cin >> res;
            if (res == 2) {
                atl = 0;
                find1(l, m);
            } else {
                atl = 1;
                find1(m + 1, r);
            }
        }
    }
}
```



---

## 作者：OoXiao_QioO (赞：0)

在下文，我们令“两个数配对”表示这两个数相等。不直接用“两个数相等”是因为可能有歧义，需要读者自己注意。

不难发现这个下取整对于 $n$ 的奇偶性有影响，所以我们要分类讨论。

* 若 $n$ 是奇数

第一反应是令 $k=2$。此时只有 $1$ 自己是一组，其他连续两个数都是同一个值。

那么我们可以对于每个位置 $i$，查询 $[1,i-1]$ 和 $[1,i]$ 的答案。如果这两个区间答案一样，那么这个位置肯定不是 $1$；如果不一样，再查询 $[i,n]$ 和 $[i+1,n]$。因为 $1$ 不会和左右任意一个数配对，因此若这两种情况都不一样，那么这个位置肯定就是 $1$，此时询问次数就是 $2n-2$ 次。

考虑优化，若查询一个区间 $[l,r]$，那么答案数就是 $len-x$，其中 $x$ 是配对数字都在区间内的对数。所以我们也能得出这个区间的未配对数。

更进一步地，发现对于位置 $i$，如果查询 $[1,i]$ 和 $[i+1,n]$，由于这两个区间内未配对的数字要么是 $1$，要么会和另一个区间中的数字配对，因此这两个区间中未配对数多的那个区间一定包含 $1$。

这样就可以通过 $k$ 不断向下二分，最后只需要 $20$ 步操作就可以解决 $n$ 是奇数的情况。

* 若 $n$ 是偶数

此时 $1$ 和 $n$ 都没有点可以配对，那么我们需要找到 $n$ 并把他消除掉，那么找 $1$ 就变得简单了。

注意到 $k$ 可以取除了 $2$ 的数，通过手玩样例发现，令 $k=n$ 可以找到 $n$ 在那里，那么可以 先找到 $n$ 再找 $1$，此时需要 $40$ 步。也就是找两次 $20$ 步。

可是若一直取 $n$，优化的前景不大，那么继续考虑 $k$ 的取值。

继续优化，还是令 $k=2$，查询 $[1,i]$ 和 $[i+1,n]$，我们发现此时有两种情况：

1. 左右两边未配对的数量相差 $2$，这时候 $1$ 和 $n$ 一定都在较大的那边，直接递归求解即可。

2. 左右两边未配对数量相等，此时肯定 $1$ 和 $n$ 各在一边，再查询一次 $k=n$，就知道了 $n$ 再哪里。

至于为什么有这两种情况请读着自己思考。


---


综合一下，所以现在只需要 $21$ 步。

但是题目要求是 $20$ 次，还要再优化一次。发现最后处理 $[i,i+1]$ 需要两步，看看能不能从中减少一步。

分类讨论：
1. $1$ 和 $n$ 都在 $[i,i+1]$ 中，显然只需要查询一步就知道哪里是 $n$ 了。

2. 只有 $1$ 在 $[i,i+1]$ 中，考虑利用前面推出的信息。注意到我们已经知道 $[1,i-1],[1,n],[1,i+1],[i+2],n$ 的答案（如果区间为空或者区间为 $[1,n]$ 那也知道了答案）。假设这个区间中两个数分别是 $1$ 和 $x$，那么 $x$ 一定也有一个和它匹配的数字。我们考虑通过 $[1,i-1]$ 和 $[1,i+1]$ 就知道了和 $x$ 配对的数字在 $[1,i-1]$ 还是在 $[i+2,n]$，接下来再判断一步就找到 $1$ 了。

---

## 作者：FLAMEs_ (赞：0)

做了半天的交互题，感觉做完之后整个人升华了。

前言：这类题目似乎需要很好的“和出题人对上脑电波”，不然什么也想不到。而且，遇到这类向下取整相关的题目时，应当考虑 $k = 2$ 或者 $k = n$ 的情况，从这种特殊情况为突破口去思考题目。

以下用 $Q(l,r,k)$ 表示向交互库发起一组形如 ```? l r k``` 的询问。

部分参考了 fjy666 大佬的题解，表示衷心感谢/bx

[戳我看 G2 题解](https://www.luogu.com.cn/blog/gggggggghost/CF1764G2)

## G3 做法

**请确保你已经会用 $21$ 次询问通过 G2。**

发现 $Q(mid+1,n,n)$ 很难优化掉，考虑优化掉限制最少的 $l=r$ 的情况。

优化主要在于 **利用已知信息**，具体过程：

我们在处理 $l = r$ 区间时，显然已经询问完了 $[1,l-1],[l,n],[1,r+1],[r+2,n]$ 这四个区间。每次询问 $k = 2$ 时，我们考虑用 $\text{map}$ 存一下已经询问过的区间的答案。

令 $p= Q(l,n,2),q=Q(r+2,n,2)$。对 $p$ 与 $q$ 分类讨论。

- $p=q$

此时 $1$ 不可能处在该位置上，原来二分所记录的答案即为最终答案。

- $p=q+1$

有如下三种情况：**$l$ 处为 $1$，$l+1$ 处出现的值在 $l+2\sim n$ 中出现过**；$l$ 处出现的值在 $1\sim l-1$ 出现过，$l+1$ 处出现的值在 $l+2\sim n$ 中出现过；$l$ 处出现的值在 $1\sim l-1$ 出现过，$l+1$ 处为 $1$。

此时，$l$ 处为 $1$ 当且仅当 $Q(1,l-1,2)+2=Q(1,l+1,2)$ 而且 $Q(l+1,n,2)=Q(l+2,n,2)$，对应上方两种限制。

- $p=q+2$

首先，必须保证 $l$ 在 $1\sim l-1$ 中没出现过。我们发现，当 $p=q+2$ 时，本质上就是在 $l+1$ 与 $l+2$ 塞了两个不同于 $1\sim l-1$ 之间所有数的数。再 $l$ 不为 $n$ 即可。

至此，我们优化掉了一组询问，通过了 G3。

代码相较 G2 重构了一部分，原因是需要加入 $\text{map}$ 维护等部分。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> Pii;
int n, L, R, Ans, Npos;
map <Pii, int> Mp;
int Ask(int L, int R, int p) {
	if(Mp.count({L, R}) && p == 2) return Mp[{L, R}];
	int x; if(L == R) x = 1;
	else if(L == 1 && R == n) x = n / p + 1;
	else cout << "? " << L << " " << R << " " << p << endl, cin >> x;
	if(p == 2) Mp[{L, R}] = x; return x;
}
int main() {
	cin >> n;
	if(n & 1) {
		L = 1, R = n;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(mid == n) {
				Ans = n;
				break;
			}
			int Lval = Ask(1, mid, 2); Lval = 2 * Lval - mid;
			int Rval = Ask(mid + 1, n, 2); Rval = 2 * Rval - (n - mid);
			if(Lval < Rval) L = mid + 1;
			else R = mid - 1, Ans = mid;
		}
		cout << "! " << Ans;
		return 0;
	}
	L = 1, R = n; int flag = -1;
	while(L <= R) {
		int mid = (L + R) >> 1;
		if(mid == n) {
			Ans = n;
			break;
		}
		if(L == R && L != 1) {
			if(flag == -1) {
				if(Ask(1, L, n) == 1) Ans = mid;
				break;
			}
			int Vx = Ask(L, n, 2), Vy = Ask(L + 2, n, 2);
			if(Vx - Vy == 0) break;
			else if(Vx - Vy == 1) {
				if(Ask(1, L + 1, 2) - Ask(1, L - 1, 2) == 2 && Ask(L + 1, n, 2) == Ask(L + 2, n, 2)) Ans = mid;
			}else {
				if(Ask(1, L - 1, 2) != Ask(1, L, 2)) Ans = mid;
			}
			break;
		}
		int Lval = Ask(1, mid, 2); Lval = 2 * Lval - mid - (1 <= flag && flag <= mid);
		int Rval = Ask(mid + 1, n, 2); Rval = 2 * Rval - (n - mid) - (mid + 1 <= flag && flag <= n);
		if(Lval > Rval) R = mid - 1, Ans = mid;
		else if(Lval < Rval) L = mid + 1;
		else {
			if(mid == 1) {
				if(Ask(mid + 1, n, n) == 2) {
					flag = mid + 1;
					Ans = mid, R = mid - 1;
				}else L = mid + 1, flag = 1;
			} else {
				if(Ask(1, mid, n) == 2) L = mid + 1, flag = 1;
				else Ans = mid, flag = mid + 1, R = mid - 1;
			}
		}
	}
	cout << "! " << Ans;
	return 0;
}
```

---

## 作者：huazai676 (赞：0)

[link](https://www.luogu.com.cn/problem/CF1764G3)

## 30 次询问
容易 $Q(l,r,n)$ 加二分用 $\log n$ 次确定 $n$ 的位置，以此类推确定 $n-1,n-2...$ 的位置，但是操作次数很少，需要想办法快速得到与 $1$ 有关的信息。

试一试发现，当 $Q(l,r,k=2)$ 时，$2 \ 3,4 \ 5...$ 两两配对后值都相等了，只有 $1$（或者 $1$ 和 $n$）没有配对。这时候二分，$[1,x]$ 中未配对的一定和 $[x+1,n]$ 中未配对的两两配对。如果两区间未配对数不相等，说明 $1$ 一定在多的那边；否则 $1$ 和 $n$ 都无配对且在两个区间内。这时候可以事先用 10 次询问得到 $n$ 的位置然后二分下去即可。

## 25 次询问
其实不需要预处理 $n$ 的位置，只有在遇到未配对数相等的时候 $Q(1,x,n)$ 或 $Q(x+1,n,n)$ 知道 $n$ 在哪个区间即可，21 次询问。

## 20 次询问
中间那次 $Q(l,r,n)$ 不好被省略，于是考虑最后一只用 1 次求出答案。

如果最后答案是 $l,r=l+1$ 中的一个，此时区间 $[1,l-1],[l,n],[1,r],[r+1,n]$ 要么已经在之前的二分过程中被询问，要么是空区间或 $[1,n]$ ，记 $f_{x,y}$ 表示 $[x,y]$ 中未配对数的数量，则 $f_{1,l-1}=f_{1,r}$（加入 $1$ 后未配对数量加一，加入另一个数后未配对数量又减一）说明 $l,r$ 中的某个数与 $[1,l-1]$ 中的数配对，此时 $Q(1,l,2)$ 得到 $f_{1,l}$，若 $f_{1,l-1}+1=f_{1,l}$ 则 $l$ 为答案；其它情况与此类似。

[code](https://codeforces.com/contest/1764/submission/232017074)

---

## 作者：Terac (赞：0)

考虑询问能给出什么信息。

当 $k=n$ 时，可以二分 $n$ 位置用 $\log_2 n$ 次询问确定 $n$ 的位置。但暂时看不出这对如何求 $1$ 的位置有什么用处。

当 $k=2$ 时，发现 $1$ 是唯一 $\left\lfloor\frac{p_i}{2}\right\rfloor=0$ 的数，其余的数总是有 $\left\lfloor\frac{2i}{2}\right\rfloor$ 和 $\left\lfloor\frac{2i+1}{2}\right\rfloor$ 成对出现，当 $n$ 为偶数时除外，此时 $\left\lfloor\frac n 2\right\rfloor$ 也是单独的，但可以通过 $k=n$ 来求出 $n$ 的位置。

称 $\left\lfloor\frac{p_i}{2}\right\rfloor=\left\lfloor\frac{p_j}{2}\right\rfloor$ 的 $(i,j)$ 互为匹配，区间中 $\left\lfloor\frac{p_i}{2}\right\rfloor$ 只出现了一次的 $i$ 为独立数。

先考虑 $n$ 为奇数的情况，可以通过询问计算出 $[l,r]$ 中的独立数个数，具体地，设询问结果为 $x$，独立数个数为 $y$，有 $y+\frac{(r-l+1-y)}{2}=x$，可得 $y=2x-(r-l+1)$。

显然 $[1,x]$ 和 $[x+1,n]$ 中，除去 $1$ 的独立数个数是相同的，故独立数多的那一个区间里一定有 $1$，可以依靠这个进行二分。总共需要 $2\log_2 n=20$ 次询问。

$n$ 为偶数时，即 $n$ 也可能是多出的独立数，只需要在左右区间独立数个数相等时，靠 $k=n$ 的询问求出独立数是在左边还是右边，再去另一边递归即可。于是我们在 $2\log_2n+1=21$ 次询问内解决了问题。仍无法通过。

考虑再优化掉一个询问，确定 $n$ 的那次询问显然是必要的，尝试优化二分的最后一个询问 $[l,l+1]$，令 $q(l,r)=query(l,r,2)$，此时已知 $q(1,l-1),q(1,l+1),q(l,n),q(l+2,n)$，可以利用这些信息。

若 $n$ 位置仍不确定，说明两数中有一数是 $n$。直接用 $1$ 次询问令 $k=n$ 来找 $n$ 即可。

否则剩下两个数，一个是 $1$，一个是值在 $2\sim n-1$ 的独立数，称为 $x$，$x$ 肯定会在 $[1,l-1]$ 或 $[l+2,n]$ 中找到自己的匹配。

- 若 $q(1,l+1)=q(1,l-1)+1$，说明对于 $[1,l-1]$，加上 $p_l,p_{l+1}$ 后只增加了 $1$ 这个独立数，说明 $x$ 的匹配在 $[1,l-1]$ 中，再查询 $q(1,l)$，与 $q(1,l-1)$ 比对即可找到 $1$ 的位置。

- 否则 $q(1,l+1)=q(1,l-1)+2$，$[1,l-1]$ 加上 $p_l,p_{l+1}$ 后增加了 $1$ 和 $x$ 两个独立数，说明 $x$ 的匹配在 $[l+1,n]$ 中，查询 $q(l,n)$，与 $q(l+1,n)$ 比对即可找到 $1$ 的位置。

于是我们在 $2\log_2 n+1-1=20$ 次询问内解决了问题。

---

## 作者：fjy666 (赞：0)

## 题意简述

[CF1764G](https://www.luogu.com.cn/problem/CF1764G3)  
有一个长为 $n$ 的排列 $p$，你每次可以询问 $l,r,k$，得到 $|\{\lfloor\dfrac{a_i}{k}\rfloor\}(l\le i \le r)|$，请用不超过 $30/25/10$ 次（G1/G2/G3）询问得出 $1$ 的位置。

$1\le n\le 1024$。

## 题解

首先考虑 $n$ 为奇数的情况。  
这时候有一个很好的性质：除了 $1$ 之外剩下所有数 $\lfloor\dfrac{x}{2}\rfloor$ 都是成对出现的。  
因此，如果把 $p$ 分成两半 $[1,k]$ 和 $[k + 1,n]$ 的话，$\lfloor\dfrac{x}{2}\rfloor$ **只出现一次的数**的个数最多的一半必然是含有 $1$ 的一半。  

只出现一次的数非常好求，$\operatorname{len}-(\operatorname{len} - \operatorname{query(l,r,2))}\times 2$ 即为所求。

考虑二分 $1$ 的操作次数。由于每次折半只需要 $2$ 次询问，总操作次数为 $2\log_2n\le 20$。

以下是这一部分的代码实现。（代码中 $[L,R]$ 表示 $1$ 的可能区间，注意并不保证 $[L,R]$ 内一定含有 $1$）
```cpp
int L = 1, R = n, ans = -1;
while(L <= R) {
	if(mid == n) {
		ans = mid;
		break;
	}
	int ansL = query(1, mid, 2), ansR = query(mid + 1, n, 2);
	ansL = mid - (mid - ansL) * 2, ansR = (n - mid) - (n - mid - ansR) * 2;
	if(ansL > ansR) ans = mid, R = mid - 1;
	else L = mid + 1;
}
printf("! %d\n", ans);
fflush(stdout);
```

****

下面来考虑 $n$ 为偶数的部分。  
这时候会出现一个问题，即 $\lfloor\dfrac{n}{2}\rfloor$ 也是独一无二的。  
因此，如果一次二分 $mid$ 恰好分开了 $1$ 和 $n$ 的话（对应到二分里，就是 $ansL = ansR$），我们无法得知哪边是 $1$，哪边是 $n$。

不过询问的 $k$ 不一定是 $2$ 啊。  
令 $k=n$，这样的询问可以一次很轻松的区分出 $n$ 和其它的数。  
在 $ansL=ansR$ 的时候额外进行一次询问来求出 $n$ 的大致位置即可继续二分。

总操作次数为 $2\log_2n
+1\le 21$。

代码实现：
```cpp
int L = 1, R = n, ans = -1, id_n = -1;
while(L <= R) {
	if(mid == n) {
		ans = mid;
		break;
	}
	int ansL = query(1, mid, 2), ansR = query(mid + 1, n, 2);
	ansL = mid - (1 <= id_n && id_n <= mid) - (mid - ansL) * 2, ansR = (n - mid) - (mid < id_n && id_n <= n) - (n - mid - ansR) * 2;
	if(ansL > ansR) ans = mid, R = mid - 1;
	else if(ansL < ansR) L = mid + 1;
	else {
		assert(id_n == -1);
		//1和n两线分居，使用一次询问找到
		if(mid == 1) {
			if(query(mid + 1, n, n) == 2) {
				id_n = mid + 1;
				ans = mid;
				R = mid - 1;
			} else L = mid + 1, id_n = 1;
		} else {
			if(query(1, mid, n) == 2) L = mid + 1, id_n = 1;
			else ans = mid, id_n = mid + 1, R = mid - 1;
		}
	}
}
printf("! %d\n", ans);
fflush(stdout);
```

结合以上两部分可以通过 G1 和 G2。
****
还需要优化掉一次询问。我们发现，用来寻找 $n$ 的这次询问是 **无法优化的**。那就换个思路，把 $L=R$ 时的两次询问优化到一次。

本质上，要快速求出 $L$ 是不是 $1$。  

在遇到 $L=R$ 的时候，我们实际上已经经过 $mid=L-1$ 和 $mid=R+1$ 的两次询问了。  
那么我们已经询问过 $(1,L-1),(L,n),(1,L+1),(L+2,n)$  这个区间了。（以下默认 $k=2$，匹配为除以 $2$ 下取整相同）  
核心思想是充分利用已知信息。
令 $p = (L,n), q= (L+2,n)$，分类讨论 $p - q$。

- $p - q = 0$，显然 $L$ 处的值不可能为 $1$。
- $p - q = 1$，有以下几种情况：$L$ 处为 $1$，$L+1$ 与 $L+2\sim n$ 中的一个数匹配；$L$ 和 $1\sim L-1$ 的数匹配，$L+1$ 与 $L+2\sim n$ 中的数匹配；$L$ 与 $L+1$ 匹配；$L$ 与 $L+2\sim n$ 的数匹配，$L+1$ 为 $1$。  
此时 $L$ 处为 $1$ 当且仅当 $(L+1,n) = (L+2,n)\land (1,L-1)+2=(1,L+1)$。
- $p-q=2$，只需保证 $L$ 不与 $1\sim L-1$ 匹配且 $L$ 不为 $n$ 即可。

综上，一次询问就足以确定 $1$ 的位置。（有人可能疑惑 $n$ 可能会有影响，可以参考[代码](https://codeforces.com/contest/1764/submission/223435026)）

---

## 作者：AtomAlpaca (赞：0)

## 题目

交互题。每次产生一个 $[1,n]$ 的排列 $p$。

每次询问 $l,r,k$，得到 $\left\lfloor\dfrac{p_l}k\right\rfloor,\left\lfloor\dfrac{p_{l+1}}k\right\rfloor,\cdots,\left\lfloor\dfrac{p_r}k\right\rfloor$ 中数的种类数。

要求在 $30$(easy)/$24$(medium)/$20$(hard) 次询问内找到 $1$ 的位置。$n \le 1024$。

很厉害的一道题目！然而自己只想到 medium 的做法。但是很喜欢！

## 题解

### easy version

看到 $1024$ 和 $30$，感觉像是 $3\log n$。于是猜是二分。

然后发现 $k=2$ 的情况相当于把每个 $2x, 2x+1$ 配对，最后剩下无法配对的是 $1$ 和 $n$（$n$ 为偶数时）。考虑把 $n$ 是奇数和偶数的情况分开解决。

当 $n$ 为奇数时，我们考虑先把 $1$ 删去，于是把这个序列分成两个区间时，两个区间内的、无法配对的数的数量是相等的。然后我们把 $1$ 扔到某一边，这边的无法配对的数的数量会增加，我们就能判定 $1$ 在哪一边了。

考虑怎么求无法配对的数的数量。设一次询问 $l, r, k$ 的答案为 $q(l, r, k)$，那么 $(r - l + 1) - q(l, r, k)$ 显然就是配对的对数，因此未配对的对数就是 $(r - l + 1) - 2\times ((r - l + 1) - q(l, r, k))$，也就是 $2 q(l, r, k) - (r - l + 1)$。

于是我们可以通过两次操作把目标范围缩小一半，并且操作次数是十分优秀的 $O(2 \log n)$。

然后考虑 $n$ 为偶数怎么做。发现只是在奇数的情况下多了一个 $n$ 的干扰。然后我们发现一个区间 $[l, r]$ 含有 $n$ 当且仅当 $q(l, r, n)=2$，于是我们可以提前把 $n$ 的位置二分出来，然后套用奇数的方法，加下特判就好了。操作次数是并不十分优秀的 $O(3 \log n)$。但是能够通过 easy version。

### medium version

考虑优化 easy version 的做法。

我们发现每次把排列划分成两段时，如果 $1, n$ 在同侧，我们其实是不用处理的，直接往未配对较多的一边跳就行；在异侧时，我们得到的 $1$ 的新范围内一定不会再有 $n$。于是我们发现异侧的情况最多仅有一次，而且我们只需要知道 $n$ 在哪一边即可。于是我们可以把操作次数优化到 $O(2 \log n + 1)$。足以通过 medium version。

### hard version

我们发现 $O(2 \log n + 1)$ 最大有 $21$，恰好无法通过 hard version。考虑继续优化。

考虑偶数情况一定会经过 $r = l + 1$ 的区间，这个区间是较好处理的。分为两种情况。

1. 还未出现 $1, n$ 异侧，即 $l, r$ 对应的分别是 $1, n$；
2. 出现了 $1, n$ 异侧，即 $l, r$ 其中一个是 $1$，另一个不一定。

第一种情况是好处理的，通过询问 $q(1, l, n)$ 或 $q(r, n, n)$ 判断其中一个是否为 $n$ 即可。第二种情况则稍难一些。

由于我们现在的区间为 $[l, r]$，则我们之前一定询问过 $q(1, l - 1, 2), q(1, r, 2), q(l, n, 2), q(r + 1, n, 2)$ 这些区间。我们可以利用这些信息。

- 假如 $q(1, r, 2) = q(1, l - 1, 2) + 1$ 说明加上 $l, r$ 之后，和 $[1, l-1]$ 中的区间匹配上了一个数，于是判断 $q(1, l, 2)$ 是否等于 $q(1, l - 1, 2)$ 便能得到 $l$ 这个位置是和前面匹配上的数还是 $1$；
- 否则，一定有 $q(l, n, 2) = q(r + 1, n, 2) + 1$，这种情况的处理方式和上面是对称的。

于是我们在 $r = l + 1$ 的区间上优化掉了一次操作，操作次数变为 $O(2 \log n)$，可以通过 hard version。

## 代码

```c++
#include <bits/stdc++.h>

bool flg, lft;
int n;
std::map < std::pair<int, int>, int > mp;

int qry(int l, int r, int k)
{
  if (l == r) { return 1; }
  if (l > r) { return 0; }
  if (k == 2 and mp.find({l, r}) != mp.end()) { return mp[{l, r}]; }
  int res = 0;
  printf("? %d %d %d\n", l, r, k); fflush(stdout);
  scanf("%d", &res);
  if (k == 2) { mp[{l, r}] = res; }
  return res;
}

int solve1(int l, int r)
{
  if (l == r) { return l; }
  int k = l + ((r - l) >> 1), x = 2 * qry(1, k, 2) - k, y = 2 * qry(k + 1, n, 2) - (n - k);
  if (x > y) { return solve1(l, k); } else { return solve1(k + 1, r); }
}

int solve0(int l, int r)
{
  if (l == r) { return l; }
  if (r - l == 1)
  {
    if (!flg)
    { 
      if (l > 1) { return ((qry(1, l, n) == 2) ? r : l); }
      else { return qry(r, n, n) == 2 ? l : r; };
    }
    if (qry(1, r, 2) == qry(1, l - 1, 2) + 1)
    {
      if (qry(1, l, 2) == qry(1, l - 1, 2)) { return r; } else { return l; }
    }
    else
    {
      if (qry(r, n, 2) == qry(r + 1, n, 2)) { return l; } else { return r; }
    }
  }
  int k = l + ((r - l) >> 1); int x = 2 * qry(1, k, 2) - k, y = 2 * qry(k + 1, n, 2) - (n - k);
  if (x == y)
  {
    if (!flg)
    {
      if (qry(1, k, n) == 2) { flg = lft = true; } else { flg = true; }
    }
    if (lft) { solve0(k + 1, r); } else { return solve0(l, k); }
  }
  if (x > y) { return solve0(l, k); } else { return solve0(k + 1, r); }
}

int main()
{
  scanf("%d", &n);
  if (n & 1) { printf("! %d\n", solve1(1, n)); } else { printf("! %d\n", solve0(1, n)); }
}
```



---

## 作者：Dream_poetry (赞：0)

### 思路：
首先令 $k = 2$，然后如果 $n$ 是奇数，显然此时只有 $1$ 自己一个人一组。

显而易见的，我们可以对于每个位置 $i$，查询 $[1, i − 1]$ 和 $[1, i]$ 的答案，如果答案一样，那这个位置肯定不是 $1$。

如果不一样，我们再查一下 $[i, n]$ 和 $[i + 1, n]$。由于 $1$ 不会和左右任意一个人配对，不难发现如果这两种情况都不一样，那这里一定是 $1$，这样我们就做到了 $2n − 2$ 次查询。

#### 进行优化。

如果我们查询一个区间 $[l, r]$，那么得到的答案自然是 $len-$ 配对数字都在区间内的对数，因此我们自然也能得到这个区间的未配对数。

这个时候发现，对于第 $i$ 个位置，如果我们查询 $[1, i]$ 和 $[i + 1, n]$，由于这两个区间内没配对的数字要么是 $1$，要么会和另一个区间中的数字配对，因此这两个区间中，未配对数多的那个一定包含 $1$。

这样就可以通过 $k$ 不断向下二分，最后只需要 $20$ 步操作就可以解决 $n$ 是奇数的情况。

太棒了，所以然后呢？


#### 再考虑 $n$ 是偶数的情况。

这个时候 $1$ 和 $n$ 都没人配对，我们需要找到 $n$ 并将它去掉。

注意到 $k$ 可以取别的数，我们如果只是让 $k = 2$ 未免有些弱，而且看上去也区分不了 $1$ 和 $n$，而不难发现，令 $k = n$ 就可以找到 $n$ 在哪里，于是可以先找 $n$ 再找 $1$，需要 $40$ 步。

显然无法接受。

#### 再优化。

令 $k = 2$，查询 $[1, i]$ 和 $[i + 1, n]$，发现此时会有两种情况: 

1. 左右两边未配对数量相差 $2$，这个时候 $1$ 和 $n$ 一定都在较大的那边，直接递归处理。

2. 左右两边未配对数量相等，这个时候一定 $1$ 在一边，$n$ 在另一边，可以通过查询 $k = n$ 判断哪边是 n。

所以只需要 $21$ 次，多么毒瘤的答案，依然无法接受。

#### 最终优化！

我们发现，最后处理区间 $[i, i + 1]$ 还需要两步操作，考虑省掉一步。

$1$ 和 $n$ 都在 $[i, i + 1]$ 中，我们显然只需要查询一步就可以知道哪边是 n。

只有 $1$ 在 $[i, i + 1]$ 中，我们考虑利用一下前面的信息。

注意到我们一定已经知道 $[1, i − 1]$，$[i, n]$，$[1, i + 1]$，$[i + 2, n]$ 的答案 (如果区间为空或者区间为 $[1,n]$ 显然我们也知道答案)，假设这个区间中的两个数是 $1$ 和 $x$，那么 $x$ 一定有一个和它配对的数字。

我们考虑通过 $[1, i − 1]$ 和 $[1, i + 1]$ 就可以知道和 $x$ 配对的数字在 $[1, i − 1]$ 还是在 $[i + 2, n]$。

接下来只需要一步判断就可以找到 $1$ 了。

万岁，总算写完了。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
int n;

int l,r;
int ans;
int flag;

inline int ask(int l,int r,int k){
	printf("? %lld %lld %lld\n",l,r,k),
	fflush(stdout);
	int x;
	cin>>x;
	return x;
}
int g[500005];
int f[500005];

int query(int l,int r){
	return (ask(l,r,2)<<1)-(r-l+1);
}

signed main(){
	cin>>n;
	l=1;
	r=n-1;
	ans=n;
	flag=-1;
	if (n%2) g[1]=f[n]=1;
	else g[1]=f[n]=2;
	
	while (l<=r){
		int mid=(l+r)>>1;
		if (l==r){
			if (flag==-1 && (!(n%2))){
				if (mid==1){
					if (ask(mid+1,n,n)!=1){
						ans=l;
					}			
				}
				else{
					if (ask(1,mid,n)==1){
						ans=l;
					}
				}
				break;
			}
			else if (g[l]-g[l+2]){
				if (query(1,l)>f[l-1]){
					ans=l;
				}
			}
			else{
				if (query(l+1,n)<g[l+2]){
					ans=l;
				}
			}
			break;
		}	
		f[mid]=query(1,mid);
		g[mid+1]=query(mid+1,n);
		int val=f[mid]-g[mid+1];
		if (val>0){
			ans=mid;
			r=mid-1;
		}
		else if (val<0){
			l=mid+1;
		}
		else{
			if (flag==-1){
				if (mid==1) flag=(ask(mid+1,n,n)==1);
				else flag=ask(1,mid,n)-1;
			}
			if (flag){
				l=mid+1;
			}
			else{
				ans=mid;
				r=mid-1;
			}
		}
	}
	printf("! %lld",ans);
	return 0;
}
```

---

## 作者：周子衡 (赞：0)

注意到 $k$ 比较大的时候，我们询问回来的信息基本没什么用。一个自然的想法是考虑 $k$ 很小的情况，也就是 $k=2$。

注意到 $k=2$ 时，相当于把 $(2,3),(4,5),(6,7),...$ 两两配对当成同一个数，而 $1$ 以及 $n$（仅在 $n$ 为偶数的情况下）是孤独的，这非常有利于我们找到 $1$ 的位置。我们先讨论 $n$ 是奇数的情况，此时只有 $1$ 一个数是孤独的。

考虑二分查找，我们需要快速判定 $1$ 所在的位置是否 $\leq x$。对于一次询问 $([l,r],2)$，设返回的结果为 $c$，那么我们可以知道 $[l,r]$ 内仅出现一次的数共有 $2c-(r-l+1)$ 个。（方便起见，下面记$[l,r]$ 内仅出现一次的数的数量为 $F(l,r)$。）我们看看 $[1,x]$ 和 $[x+1,n]$ 内仅出现一次的数哪个多，就能知道 $1$ 在哪一边了。这样一次判定需要用 $2$ 次询问，总共判定次数上限为 $2\lceil\log_2n\rceil=20$，已经可以通过了。

接着考虑 $n$ 是偶数的情况。此时有 $1,n$ 两个孤独的数需要处理。注意到我们可以令 $k=n$，可以在 $\lceil\log_2n\rceil$ 次询问内确定 $n$ 的位置。剩下的部分我们如法炮制，可以在 $2\lceil\log_2n\rceil$ 次以内再把 $1$ 找出来，这样总询问次数上界为 $3\lceil\log_2n\rceil=30$，已经可以通过 G1 了。

我们还可以做得更好。考虑一开始的时候不先去确定 $n$ 的位置。我们还是二分，维护一个区间 $[l,r]$，表示当前我们确定 $1,n$ 都在 $[l,r]$ 内。每次取中点 $x$，比对 $[1,x]$ 和 $[x+1,n]$ 内只出现一次的数的数量，可以得到以下三个结论之一：

- $1,n$ 位置都 $\leq x$：把二分区间变为 $[l,x]$ 即可。
- $1,n$ 位置都 $> x$：把二分区间变为 $[x+1,r]$ 即可。
- $1,n$ 位置一个 $\leq x$，一个 $> x$：我们调用一次询问 $([l,x],n)$，看看 $n$ 到底在哪个区间，那么 $1$ 一定就在另一个区间了。接着类似地二分下去就可以了。

这样我们至多额外消耗 $1$ 次询问，询问次数上界达到了 $21$ 次，已经足够通过 G2 了。

通过 G3 需要稍微做一些细节上的处理。当二分区间 $[l,r]$ 长度为 $2$ 时，我们希望能在 $1$ 次询问而不是 $2$ 次询问内求出 $1$ 的位置。为此我们需要充分利用已经得到的信息。在此时，我们一定已经得知了 $F(1,l-1),F(1,r),F(l,n),F(r,n)$ 的值。

- 如果 $F(1,l-1)=F(1,r)$，说明 $[l,r]$ 中不是 $1$ 的那个数的另一次出现是在这个区间的左边。我们询问 $F(1,l)=F(1,r-1)$ 的值就可以确定 $1$ 到底是哪个。
- 如果 $F(l,n)=F(r+1,n)$，说明 $[l,r]$ 中不是 $1$ 的那个数的另一次出现是在这个区间的右边。我们询问 $F(r,n)=F(l+1,n)$ 的值就可以确定 $1$ 到底是哪个。
- 否则这个区间里恰好一个 $1$ 一个 $n$，通过 $([1,l],n)$ 或者 $([r,n],n)$ 都可以轻松分辨哪个是 $1$。

这样我们就省下了一次询问，可以通过 G3 了。

```cpp
#include<cstdio>
#include<cstring>

using namespace std;

const int SMALL=0,BIG=1;

int n;

int f[1100][1100];

int F(int l,int r)
{
	if(f[l][r]!=-1)return f[l][r];int &ans=f[l][r];
	if(l>r)return ans=0;
	if(l==1&&r==n){if(n&1)return ans=1;return ans=2;}
	printf("? %d %d %d\n",l,r,2);fflush(stdout);
	int x=0;scanf("%d",&x);
	ans=2*x-(r-l+1);return ans;
}
bool check_n(int p) // returns whether value n lies in [1, p]
{
	if(p!=1)
	{
		printf("? %d %d %d\n",1,p,n);fflush(stdout);
		int x=0;scanf("%d",&x);return x==2;
	}
	printf("? %d %d %d\n",p+1,n,n);fflush(stdout);
	int x=0;scanf("%d",&x);return x==1;
}

int main()
{
	scanf("%d",&n);
	memset(f,-1,sizeof(f));
	
	int l=1,r=n;
	
	if(n%2==1)
	{
		while(l<r)
		{
			int mid=(l+r)>>1;
			int x=F(1,mid),y=F(mid+1,n);
			if(x>y)r=mid;else l=mid+1;
		}
	}
	else
	{
		
		int sta_n=-1;
		while(l<r)
		{
			if(r-l==1)
			{
				if(F(1,l-1)==F(1,r))
				{
					if(F(1,l)==F(1,l-1)-1)l++;else r--;
				}
				else if(F(l,n)==F(r+1,n))
				{
					if(F(r,n)==F(r+1,n)-1)r--;else l++;
				}
				else
				{
					if(check_n(l))l++;else r--;
				}
				break;
			}
			int mid=(l+r)>>1;
			int x=F(1,mid),y=F(mid+1,n);
			if(x==y)
			{
				if(sta_n==-1)
				{
					if(check_n(mid))l=mid+1,sta_n=SMALL;else r=mid,sta_n=BIG;
				}
				else if(sta_n==BIG)r=mid;else l=mid+1;
			}
			else if(x>y)r=mid;else l=mid+1;
		}
	}
	
	printf("! %d\n",l);fflush(stdout);	
}

---

