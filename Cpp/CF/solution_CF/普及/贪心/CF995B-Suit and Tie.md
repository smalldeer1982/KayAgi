# Suit and Tie

## 题目描述

Allen is hosting a formal dinner party. $ 2n $ people come to the event in $ n $ pairs (couples). After a night of fun, Allen wants to line everyone up for a final picture. The $ 2n $ people line up, but Allen doesn't like the ordering. Allen prefers if each pair occupies adjacent positions in the line, as this makes the picture more aesthetic.

Help Allen find the minimum number of swaps of adjacent positions he must perform to make it so that each couple occupies adjacent positions in the line.

## 说明/提示

In the first sample case, we can transform $ 1 1 2 3 3 2 4 4 \rightarrow 1 1 2 3 2 3 4 4 \rightarrow 1 1 2 2 3 3 4 4 $ in two steps. Note that the sequence $ 1 1 2 3 3 2 4 4 \rightarrow 1 1 3 2 3 2 4 4 \rightarrow 1 1 3 3 2 2 4 4 $ also works in the same number of steps.

The second sample case already satisfies the constraints; therefore we need $ 0 $ swaps.

## 样例 #1

### 输入

```
4
1 1 2 3 3 2 4 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 1 2 2 3 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
3 1 2 3 1 2
```

### 输出

```
3
```

# 题解

## 作者：Karry5307 (赞：3)

### 题意

给定一个长度为 $2n$ 的序列，其中 $1\sim n$ 每个元素各有两个，求最少需要的交换次数使得 $1\sim n$ 中每个元素出现的两个位置相邻。

$\texttt{Data Range:}1\leq n\leq 100$

### 题解

瞎写了个贪心，然后就过了？

我又是差点没看数据范围的傻逼。

首先，因为两边的元素相较中间的元素来说更难调整，所以肯定是使得两边的元素尽量不动最好，这里给个证明：

假设当前情况下要调整的元素为 $x$ 和 $x^\prime$，其中 $x$ 是最左边的那个元素。由于 $x$ 向右移动等价于 $x^\prime$ 向左移动，所以需要移动的次数不变。

如果将 $x$ 与 $x^\prime$ 放到中间来的话，有可能存在一对元素 $y$ 和 $y^\prime$，使得 $x$ 和 $x^\prime$ 被夹在 $y$ 和 $y^\prime$ 中间。这个时候如果将 $y$ 和 $y^\prime$ 配对的话将会跨越这两个元素造成额外的操作次数。

但是注意到当 $x^\prime$ 的位置向左移动的时候其他元素的相对位置不变，所以如果将 $x^\prime$ 移动到最左端会比移动到其他地方少跨越这一对的操作次数，于是结论就成立了。

既然有了这个贪心性质的话，每次找到最左边的一个元素和与之配对的那个元素然后暴力交换统计即可。因为 $n$ 的范围很小所以怎么写都能过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,pos,res;
ll x[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read()*2;
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	for(register int i=1;i<=n;i+=2)
	{
		for(register int j=i+1;j<=n;j++)
		{
			if(x[j]==x[i])
			{
				pos=j;
				break;
			}
		}
		for(register int j=pos;j>i+1;j--)
		{
			swap(x[j],x[j-1]),res++;
		}
	}
	printf("%d\n",res);
}
```

---

## 作者：小张的8424 (赞：2)

第一篇题解交上去后洛谷没给过，说方法重复，不过那也是情理之中的事，因为我只是用那篇题解充实我的博客。

一次我打codeforce比赛，看到一道题，怎么也想不出来。这时爸爸叫我吃一个苹果，我吃完后，灵光一闪，终于想出了这道题。

这次我发现这道题居然还没人发题解，所以我就写了这么一篇题解。
## 题目意思
一个数列有$2n(1\leq n\leq 100)$个数，两两相同，但是是打乱的，每一次操作可以交换相邻两个数，要求把每一对相同的数都交换到一起，例如：
$$11233244→11323244→11332244$$
输出最少操作次数。（上面的例子是$2$）

[题目传送门](https://www.luogu.org/problemnew/show/CF995B)
## 分析
首先，我们发现无论交换过程多么复杂，对于每一对数来说，都是要交换到一起的，一步也少不了。所以说，看起来十分复杂的操作过程就被分解成每一对数交换到一起的过程。

再看下面的例子：
$$(1)1212→1122$$
$$(2)1212→1221$$
上面两种方法哪个更好？

很显然第一种好，第二种不好的原因在于操作以后，被交换到一起的一对把另一对隔开了，这样就需要耗费更多操作次数才能将隔开的一对换到一起。

所以，移到一起的一对不能隔开任何一对数，而只有它们在被交换到一起时在边上，才不会隔开别的数。

再想一种情况，如果把左边的向左移，或把右边的向右移，会使这一对之间的距离更远，会白白增加操做次数，得不偿失。

只有其中一个就在边上的时候，才能做到最优。

综合以上分析，我们终于找到了贪心策略：
1. 找到最右边的数
2. 找到和它配对的数
3. 把这个数一直和它右边的数交换，直到和最右边的数交换到一起。
4. 每一次和右边的数交换都算一次交换，计入次数中。
5. 然后最右边的两个数就可以抹去了。

输入样例#3：
```
3
3 1 2 3 1 2
```
输出样例#3：
```
3
```
我们用以上方法走一遍样例3，看看对不对：
$$312312$$
首先找到最右边的$2$。
$$31231\underline 2$$
找到另一个$2$。
$$31\underline 231\underline 2$$
交换到一起。（操作$2$次）
$$312312→313212→313122$$
最右边的$2$就可以抹去了。
$$3131(22)$$
再找到最右边的$1$。
$$313\underline 1(22)$$
找到另一个$1$。
$$3\underline 13\underline 1(22)$$
交换。（操作一次）
$$3131(22)→3311(22)$$
抹去右边的两个$1$。
$$33(1122)$$
而两个$3$也可以抹去了。
$$(331122)$$
加起来$2+1=3$，刚好$3$步，再想一下有没有反例，嗯……好像没有，然后写程序，提交程序……AC。
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,i,j,tot=0;
    //n对数，操作tot次。
	cin>>n;
	n*=2;
    //2n个数
	int a[n];
	for(i=0;i<n;i++)
		cin>>a[i];
    //输入
	while(n!=0)
	{
		for(i=0;i<n-1;i++)
			if(a[i]==a[n-1])
				break;
        //找到和最后一个一样的数配对
		tot+=n-i-2;
        //n-i-2是操作次数（不信你数数看，用样例3）
		for(j=i;j<n-1;j++)
			swap(a[j],a[j+1]);
        //操作
		n-=2;
        //其实这就相当于把最后两个数抹去
        //因为下标大于n的数我们压根不看
	}
	cout<<tot<<endl;
    //输出
	return 0;
}
```
另外，其实向左移并从左边抹去数也是可以的，这里就不发代码了。

本来还有一些要写的，不过忘了，所以到这里就结束了。

---

## 作者：fengyuxuan (赞：0)

## 题目大意

有 $2n$ 个数，两个相同的数是一对，求让每一对数都相邻的最少移动次数（只能移动相邻两个数）

## 题目解析

### 贪心即可！

第一步：找一对数的第一个数。

第二步：在后面的数中找到与之相同的数（组成一对）。

第三步：把它与前一个数交换，交换到这一对数的第一个数后面，并统计交换次数。
## 如何实现

第一步：因前面的数已经成对，所以每次找奇数项即可。

第二步：循环查找。

第三步：循环交换。

## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,ans,a[500];
int main()
{
	cin>>n;
	for(int i=1;i<=2*n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		c=a[2*i-1];//第一步
		for(int j=2*i;j<=2*n;j++)
			if(a[j]==c)//第二步
				for(int k=j;k>2*i;k--)
					swap(a[k],a[k-1]),ans++;//第三步		
	}
	cout<<ans;
	return 0;
}

```




---

## 作者：Piwry (赞：0)

## 解析

考虑一种移动方案：

1. 找到最右侧（或最左侧，策略基本同）的元素 $x$
2. 找到 $x$ 对应（值相同）的另一元素 $x'$
3. 将 $x'$ 向右移动直到与 $x$ 相邻
4. “抹去” 这组元素，再如此循环

接下来我们证明这种方案一定是不劣的（即至少移动次数最少）

考虑每次找到的一对的元素 $x, x'$。由于将 $a_i$ 向右移动也可视为将 $a_{i+1}$ 向左移动，因此在某个的移动方案中，一定**至少**包含将 $x$ 向左移动 $i$ 次，将 $x'$ 向右移动 $j$ 次，直至 $x, x'$ 相邻

现在我们指出，将 $x$ 向左移动的 $i$ 次，全部转化为 $x'$ 向右的移动（即 $x$ 少向左移动 $i$ 次，而 $x'$ 多向右移动 $i$ 次），一定是不劣的

首先无论是将 $x'$ 向右移动或将 $x$ 向左移动，都会拉近 $x, x'$ 这一对的距离

再考虑第一次移动 $x$ 对其它元素对的影响。由于 $x$ 是在最边缘的（“抹去” 的元素不记），因此移动 $x$ **一定**会拉远另一对的距离（即和 $x$ 交换的元素所属的对）；而移动 $x'$ 有可能可以拉近另一对的距离

于是用归纳法不难得出，不移动 $x$ 一定是不劣的（即刚才的结论）

（证明可能有些细节问题，但大体思路就是这样X）

## CODE

直接模拟即可

```cpp
#include <cstdio>

int a[200];

int main(){
	int n;
	scanf("%d", &n);
	n *=2;
	for(int i =0; i < n; ++i)
		scanf("%d", &a[i]);
	int end =n-1, ans =0;
	while(end >= 1 && a[end] == a[end-1])
		end -=2;
	while(end >= 1){
		int pos =end-1;
		while(a[pos] != a[end])
			--pos;
		ans +=end-pos-1;
		for(int i =pos; i < end; ++i)
			a[i] =a[i+1];
	//	a[end-1] =a[end];
		end -=2;
	}
	printf("%d", ans);
}
```

---

