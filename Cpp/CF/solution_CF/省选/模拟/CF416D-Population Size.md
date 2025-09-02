# Population Size

## 题目描述

Polycarpus develops an interesting theory about the interrelation of arithmetic progressions with just everything in the world. His current idea is that the population of the capital of Berland changes over time like an arithmetic progression. Well, or like multiple arithmetic progressions.

Polycarpus believes that if he writes out the population of the capital for several consecutive years in the sequence $ a_{1},a_{2},...,a_{n} $ , then it is convenient to consider the array as several arithmetic progressions, written one after the other. For example, sequence $ (8,6,4,2,1,4,7,10,2) $ can be considered as a sequence of three arithmetic progressions $ (8,6,4,2) $ , $ (1,4,7,10) $ and $ (2) $ , which are written one after another.

Unfortunately, Polycarpus may not have all the data for the $ n $ consecutive years (a census of the population doesn't occur every year, after all). For this reason, some values of $ a_{i} $ ​​may be unknown. Such values are represented by number -1.

For a given sequence $ a=(a_{1},a_{2},...,a_{n}) $ , which consists of positive integers and values ​​-1, find the minimum number of arithmetic progressions Polycarpus needs to get $ a $ . To get $ a $ , the progressions need to be written down one after the other. Values ​​-1 may correspond to an arbitrary positive integer and the values $ a_{i}>0 $ must be equal to the corresponding elements of sought consecutive record of the progressions.

Let us remind you that a finite sequence $ c $ is called an arithmetic progression if the difference $ c_{i+1}-c_{i} $ of any two consecutive elements in it is constant. By definition, any sequence of length 1 is an arithmetic progression.

## 样例 #1

### 输入

```
9
8 6 4 2 1 4 7 10 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
9
-1 6 -1 2 -1 4 7 -1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5
-1 -1 -1 -1 -1
```

### 输出

```
1
```

## 样例 #4

### 输入

```
7
-1 -1 4 5 1 2 3
```

### 输出

```
2
```

# 题解

## 作者：AlanCRL (赞：5)

# CF416D 题解
## 题目大意
给你一个 $n$ 个数的序列，序列中的 $-1$ 可以被视为是任何数，需要构造几段等差数列（且数列内的数都要是正整数）。并最小化段数并输出。

## 题解
### 分析
这道题并没有想象中那么难。我的代码是一个简单的贪心，复杂度是 $O(n)$。需要注意一些细节（见文末）。

---

主体思路：通过 $2$ 个数计算公差，判断数的同时考虑 $-1$。  
我们就从一个样例入手吧。  

输入
```txt
9
-1 6 -1 2 -1 4 7 -1 2
```

输出
```txt
3
```

其中一种可行的方案：`8 6 4 2 1 4 7 10 2` 这个例子我们一共分成 $3$ 段。  
- `8 6 4 2`  
- `1 4 7 10`  
- `2`  

### 学习详细思路

初始变量：
```cpp
int g = 0x7fffffffffffffff; //公差，初值是极大值
int last = -1; //上一个不为 -1 的数的位置
int cnt = 0; //统计两个数中间有多少个 -1
int idx = 0; //统计每段前有多少 -1
```

我们开始模拟程序进入循环：  

#### 第一段：  
- 当 $i = 1, a_i = -1$ 时：`idx++` 统计每段前的 -1 个数，后面有大作用。  
- 当 $i = 2, a_i = 6$ 时：`last = 2` 记录不为 -1 数的位置，后续用于计算公差。  
- 当 $i = 3, a_i = -1$ 时：`cnt++` 记录两个数之间 -1 的个数（用于计算公差）。  
- 当 $i = 4, a_i = 2$ 时：现在有 2 个数了，已经可以计算公差：`(a[i] - a[last]) / (cnt + 1)`。 此时 `a[i]` 为 $2$，`a[last]` 为 $6$。  
	通过他们的差值，然后除以 `cnt + 1` ，加一是因为 $i$ 个数间有 $i+1$ 个间隔，这样我们就得出公差是 $-2$ 即每次减二，方差为整数。

	我们先不着急继续往后看，因为前面还有一个 $-1$ 没有考虑：  
	```cpp
	if (idx)
	{
		if (a[last] - idx * g <= 0)
		{
			ans++;
			i--; //从当前位置开始下一段，先-- 因为 continue 会++
			last = -1, cnt = 0, idx = 0, g = 0x7fffffffffffffff;
			continue;
		}
		idx = 0;
	}
	```
	如果段首存在 $-1$，则判断按照公差前面的值会不会小于等于 $0$。如果小于等于 $0$，则结束本段，并开启下一段并重置变量。

- 当 $i = 5, a_i = -1$ 时：按照公差现在已经小于等于 $0$ 了，需要重新开启一段并重置变量。  

#### 第二段

- 当 $i = 5, a_i = -1$ 时：再次从 $-1$ 开始，并 `idx++`。  
- 当 $i = 6, a_i = 4$ 时：一个数不能计算公差，先让 `last` 记录位置（防止接下来是 $-1$）。  
- 当 $i = 7, a_i = 7$ 时：两个数直接计算公差：`a[i] - a[last]` 是 $3$。  
同时验证段首的 $-1$ 是 $1$ 大于 $0$ 符合条件无需多开一段。  
- 当 $i = 8, a_i = -1$ 时：按照公差计算，我们直接可以将其替换成 $10$，但需要判断是否大于 $0$ 否则又必须开启新的一段。  
- 当 $i = 9, a_i = 2$ 时：公差已经不符合了，现在需要开启新的一段并重置变量。  
- 当 $i = 9, a_i = 2$ 时：再次来到 $2$，只有一个数自己是一个数列。  

### 代码
为了防止抄袭，删去了一些不重要的内容。
```cpp
#define int long long //需要开 long long

const int N = 2e5 + 5;

int n, ans = 1;
int a[N];

signed main()
{
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);

	int g = 0x7fffffffffffffff; //公差，初值是极大值
	int last = -1; //上一个正整数的位置
	int cnt = 0; //统计两个数中间有多少个 -1
	int idx = 0; //统计每段前有多少 -1

	for (int i = 1; i <= n; i++)
	{
		if (a[i] == -1) //当前数是 -1
		{
			if (last == -1) //首段开始是 -1
			{
				idx++;
				continue;
			}

			if (g != 0x7fffffffffffffff) //已经计算出公差了，需要判断 -1 是否符合条件
			{
				a[i] = a[last] + g, last = i; //直接改变其值，使连续的 -1 可以直接计算

				if (a[i] <= 0) //不符合条件，重新开始一段
				{
					ans++;
					a[i] = -1;
					last = -1, cnt = 0, g = 0x7fffffffffffffff;
					i--;
					continue;
				}
			}
			else cnt++;
		}
		else
		{
			if (last == -1) //如果上一个正整数没有记录，说明目前是本段中第一个正整数，记录并跳过
			{
				last = i;
				continue;
			}

			if (g == 0x7fffffffffffffff) //计算公差
			{
				if (cnt) //两正整数间存在-1
				{
					long double tmp = a[i] - a[last];
					tmp /= cnt + 1;

					if (tmp != (int)tmp)
					{
						ans++;
						last = -1, cnt = 0, idx = 0, g = 0x7fffffffffffffff;
						i--;
						continue;
					}
					else g = tmp;

					cnt = 0;
				}
				else g = a[i] - a[last]; //两正整数相邻求公差

				if (idx) //段首存在 -1
				{
					if (a[last] - idx * g <= 0) //不能满足重开一段
					{
						ans++;
						i--;
						last = -1, cnt = 0, idx = 0, g = 0x7fffffffffffffff;
						continue;
					}
					idx = 0;
				}
			}
			else //存在公差
			{
				if (a[i] - a[last] != g)  //判断下个数是否满足条件
				{
					ans++;
					last = -1, cnt = 0, g = 0x7fffffffffffffff;
					i--;
					continue;
				}
			}
			last = i;
		}
	}

	write(ans);

	return 0;
}
```

### 提示

以下是一些特殊样例，看看你考虑到了吗？  
- `3 2 1 -1 -1 -1 -1 1 2 3` `3`：注意判断 $-1$ 处填入值是否在正整数范围内。  
- `-1 1 7 -1 5` `2` 可以是 `1 1 7 6 5`。  
- `-1 -1 2 -1 -1 -1 5 9` `2`：可以是 `2 2 2 2 2 5 9` 注意考虑 $-1$。  

好了，题解到此结束！觉得写的不错点个赞再走吧！有疑问请联系我。

---

## 作者：jianhe (赞：4)

### 前言：
![](https://cdn.luogu.com.cn/upload/image_hosting/a8y9r8lw.png)
鉴定为 corner case 受害者。

重构代码后才过。

### 思路：
其实思路非常简单。先考虑没有 $-1$ 的情况，可以贪心地分段，如果当前的数能和前面的数构成等差数列，就不分段。否则分段。

证明比较容易，也可以感性理解一下。如果一个数可以归到前面一段，那么一定不劣于归到后面，留给后面的数更长的可能。

再考虑 $-1$。由于 $-1$ 可以替换为任何正整数，我们可以先跳过 $-1$，算出这段等差数列的公差，再往后比较。

### 细节：
细节超级多。

注意 $-1$ 能替换的是**正整数**，要特判小数与负数的情况。

等差数列公差可以为 $0$。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10;
ll n,a[N],ans,last,p,t,g,ct,ct2;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;){
		ans++;
		ct=0,ct2=1;
		while(i<=n&&a[i]==-1) i++,ct++;//找第1个非 -1
		if(i>n) break;
		p=a[i++];
		while(i<=n&&a[i]==-1) i++,ct2++;//找第2个非 -1
		if(i>n) break;
		if((p-a[i])%ct2) continue;//公差应为整数
		g=(p-a[i])/ct2;//公差
		if(p+g*ct<1) continue;//-1 不能被替换为负数
		for(last=i++,p=1;i<=n;i++)
			if(~a[i]&&a[last]-a[i]!=g*p) break;//非 -1 应构成等差数列
			else if(a[i]==-1&&a[last]-g*p<1) break;//-1 不能被替换为负数
			else if(a[i]==-1) p++;
			else last=i,p=1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Twig_K (赞：4)

- 只要确定了首项和公差，整个等差数列就是确定的（[CF1654E](https://www.luogu.com.cn/problem/CF1654E) 也用到这一点）。
- 如果可以合并，将一个数合并到前面一段等差段中，答案不会增加。所以我们每次新开一段时，贪心地让这一段尽可能长，这样一定是最优的。
- 被替换的 $-1$ 只能替换成正整数。这意味着一些 $-1$ 不能无脑合并。

很好想到的是，如果两个数 $a_i$ 和 $a_j$ 属于同一个连续段，他们应该满足：
- $$(a_i-a_j)$$ 是 $(i-j)$ 的倍数。
- 如果当前连续段公差已经确定，两者求得公差应该与规定的公差一致。

再来考虑一段连续的 $-1$ 怎么分配。
- 若一段 $-1$ 是输入数组的一段前缀：记录一下个数，**等到后一个连续段时处理**。
- 若一段 $-1$ 被一个连续段包含（即左边的非 $-1$ 数和右边的非 $-1$ 数都是同一个等差数列内的元素）：这个时候可以不需要考虑，既然左右界已经满足上面两条，中间 $-1$ 的位置一定是正整数。
- 若一段 $-1$ 夹在两个连续段中间（即左右非 $-1$ 元素不属于同一个等差数列）：在满足值非负的前提下，先尽量往前一个数列塞。多出来的**等到后一个连续段时处理**。

我们从左往右扫，记录当前连续段的一些信息，并在一些需要的时候新开一段，使总段数最少。

根据上面加粗的内容，我们需要记录当前连续段前待处理的 $-1$ 的个数（并不是前面紧挨着的所有 $-1$ 的个数，因为有一些已经被上一段处理掉了），记为 $plst$。

当前连续段可能有三种状态：

- 当前段为空，记 $flag=0$。
- 当前段有一项非 $-1$ 的数，但还没有公差，记 $flag=1$。
- 当前段公差已经确定（至少有两项非 $-1$ 的数），记 $flag=2$。

设当前遍历到下标 $i$，上一个不是 $-1$ 的位置为 $lst$。记 $lft$ 为连续的 $-1$ 的个数（注意和 $plft$ 区分）。

当 $a_i=-1$ 时，直接将 $lft$ 加一并跳过即可。大力讨论 $a_i \not= -1$ 的情况。

- 当 $flag=0$ 时，新开一段（答案加一），$flag$ 标记为 $1$，$plft$ 赋值为 $lft$（在此之前数的一段 $-1$ 属于待处理的），$lft$ 清零（因为 $a_i \not= -1$ 终止 $-1$ 连续段了）。
- 当 $flag=1$ 时，此时数列中已经有一个数了，$a_i$ 有机会成为第二个：
  - $$(a_i-a_{lst})$$ 不是 $(i-lst)$ 的倍数：把 $a_{lst}$ 单独分一段，并且带走它前面所有未处理的 $-1$ 和它与 $a_i$ 之间的 $-1$，并将 $lst$ 和 $plst$ 都清零（$-1$ 都被带走了）；新开一个数列，$a_i$ 作为第一项，$flag$ 标记为 $1$。
  - $$(a_i-a_{lst})$$ 是 $(i-lst)$ 的倍数，这时候我们计算出公差，根据公差处理 $lst$ 前的 $plft$ 个 $-1$，如果前面有填入负数，那么不可行，把 $a_{lst}$ 单独分一段，并新开一个 $a_i$ 开头的数列（同上一情况）。否则，如果前面待处理的 $-1$ 能顺利填入，就将 $flag$ 标记为 $2$。

清零 $lft$。
- 当 $flag=2$ 时，如果 $a_i$ 能放进前面的连续段里，清零 $lft$ 即可。否则新开一段，和上面大体相似，值得注意的是，对于 $lst$ 和 $i$ 之间的一段 $-1$，先尽量塞到 $lst$ 一段处，多出来的部分更新到新段的待处理 $plft$ 中。清零 $lft$。

代码比上面的文字简介很多。

```cpp
//for solution
#include<bits/stdc++.h>
#define int long long
#define For(i,il,ir) for(register int i=(il);i<=(ir);++i)
using namespace std;
const int maxn=2e5+10;
namespace stO_Orz{
	int n,ans;
	int a[maxn];
	int lft,plft;
	int flag,lst,d;
	bool check(){ For(i,1,n) if(~a[i]) return 0; return 1; }
	signed my_main()
	{
		scanf("%lld",&n);
		For(i,1,n) scanf("%lld",&a[i]);
		if(check()){ printf("1\n"); return 0; }
		For(i,1,n)
		{
			if(a[i]==-1ll){ lft++; continue; }
			if(!flag) ++ans,flag=1,plft=lft;
			else if(flag==1)
			{
				if(abs(a[i]-a[lst])%(i-lst)) ++ans,flag=1;
				else{
					flag=2,d=(a[i]-a[lst])/(i-lst);
					if(d>0&&a[lst]-plft*d<=0) ++ans,flag=1;
				}
				plft=0;
			}else{
				if(abs(a[i]-a[lst])%(i-lst)||(i-lst)*d!=a[i]-a[lst])
				{
					++ans,flag=1;
					if(d>=0) plft=0;
					else plft=max(0ll,lft-(a[lst]-1)/(-d));
				}
			}
			lft=0,lst=i;
		}
		if(lft&&flag==2&&d<0&&a[lst]+lft*d<=0) ans++;
		printf("%lld\n",ans);
		return 0;
	}
}
signed main(){ return stO_Orz::my_main(); }
```

---

## 作者：tonyre (赞：2)

# CF416D 题解

## 1 题面

给定只包含**正整数**和 $-1$ 的一个长度为 $n(n\le2\times 10^5)$ 的序列 $a(a_i\le10^9)$，$-1$ 可以被替换成任意**正整数**。求该序列**最少**可以划分成几个等差数列。

需要注意，**公差为 $0$ 也是等差数列**。

## 2 题解

### 2.1 分析

根据题意，每一个等差数列越长越好。所以采用贪心的策略：

只要当前的数可以成为前面的等差数列的元素，就让它成为；否则让它成为新的等差数列的第一项，继续扩展。

显然，对于 $-1$，也如此处理，要不然变成前面的元素，要不然就去帮助后面。

### 2.2 实现

这题贪心看起来很简单，其实特别复杂。

假设我们已经完成了前 $i-1$ 个元素的工作（即将前面的都划分成等差数列），我们便要在 $[i,n]$ 的区间找到一个最长的等差数列。

首先我们找到该区间内的最前面的两个给定的正整数，$a_x$ 和 $a_y$。

* 假如没有找到两个正整数。

  * $x$ 和 $y$ 都没有找到，说明全是 $-1$，随便变成一个等差数列就行了。
  * 没找到 $y$，说明其他的都是 $-1$，将 $-1$ 都变成 $a_x$ 就行了。

  综上，此时**只需要一个等差数列就能把这区间搞定**，直接结束。

* 假如**公差不是整数**，即 $a_y-a_x$ 不能被 $y-x$ 整除，此时只能将 $[i,y-1]$ 区间内所有 $-1$ 都变成 $a_x$，接下来就该处理 $[y,n]$ 区间。

* 假如 $a_i$ 被赋为**非正整数**，即 $a_x-(x-i)d\le 0$，此时同上情况，处理 $[y,n]$ 区间。

除去上述特殊情况，$[i,y]$ 区间都可以成为一个等差数列。

考虑将这个等差数列继续扩展，看一下有没有后面的数同样可以成为等差数列的元素的。该元素要不然由 $-1$ 变过来，要不然给定正整数本就合法。同样需要注意，**不能被赋非正整数值**。

### 2.3 检验

这种做法的正确性显而易见，我们来看一个样例：`-1 6 -1 2 -1 4 7 -1 2`。

首先找到正整数 $6$ 和 $2$，可以得出公差为 $-2$。于是将 $a_1$ 赋为 $8$，$a_3$ 赋为 $4$ 。此时完成了 $[1,4]$ 的区间，考虑扩展，发现会将 $a_5$ 赋为 $0$，无法扩展。

同理，将 $a_5$ 赋为 $1$ 后，完成了 $[5,7]$ 的区间，考虑扩展，将 $a_8$ 赋为 $10$，此时无法继续扩展。

最后只剩 $a_9$，它自己组成一个等差数列。

所以结果为 $3$。

此做法时间复杂度为 $O(n)$，可以通过。

## 3 参考代码

**注意开 `long long`。**

```c++
#include<iostream>
#define int long long//不开 long long 见祖宗
using namespace std;
const int MAXN=200005;
int a[MAXN];
signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int cnt=0;
    for(int i=1;i<=n;)
    {
        cnt++;
        int x=0,y=0;
        for(int j=i;j<=n;j++)
            if(a[j]!=-1)
            {
                if(!x) x=j;
                else
                {
                    y=j;
                    break;
                }
            }
        if(!y) break;//特殊情况1
        if((a[y]-a[x])%(y-x)!=0)//特殊情况2
        {
            i=y;
            continue;
        }
        int d=(a[y]-a[x])/(y-x);
        if(a[x]-(x-i)*d<=0)//特殊情况3
        {
            i=y;
            continue;
        }
        for(i=y;i<=n;i++)
        {
            if(a[i]+d<=0) break;//非正整数
            if(a[i+1]!=-1&&a[i]+d!=a[i+1]) break;
            a[i+1]=a[i]+d;
        }
        i++;
    }
    cout<<cnt<<endl;
    return 0;
}
```



---

## 作者：Insulin (赞：1)

### CF416D Population Size 题解

---

#### 题目大意

---

给定一个长度为 $ n $ 的数列，其中每个元素 $ a_i $ 小于等于 $ 10^9 $ 的正整数或 $ -1 $ 代表任意正整数。让你找出在这个序列中最少可以分成多少个为等差数列的子串。

#### 分析

---

因为 $ n \leqslant 10^9 $ 所以暴力求解是不可行的~~应该没有人会在看到这是道紫题时依然暴力求解吧~~。

我的代码是贪心，时间复杂度 $ \Theta (n) $，解题思路如下：

#### 变量

-----

```cpp

int n,s[N],i; //n，输入数组和遍历变量
int num,num1; //分别记录第一串-1和第二串-1的数量
int chr,now,ans; //公差，第一个已知正整数和输出的答案

```

众所周知，我们只要知道了等差数列的首项和公差，我们就可以推出之后的任意一项。但是这个题里的 $ -1 $ 就让人烦恼了。所以，我们在统计每一个等差数列时，先跳过开头的 $ -1 $ 并统计它们的数量，记录下第一个确认的正整数，再跳过第二串 $ -1 $ 并记录下它们的数量，记录下第二个确认的正整数，然后，开始特判：

1. 第一个和第二个已知正整数可不可以形成公差，不可以就把第一串 $ -1 $ 和第二串 $ -1 $ 变成第一个确定的正整数，然后进入下一层循环。注：公差为零也是等差数列。

2. 等差数列为升序且当前公差会让前面的 $ -1 $ 变为非负整数时也把第一串 $ -1 $ 和第二串 $ -1 $ 变成第一个确定的正整数，然后进入下一层循环。

$ 2 $ 中情况如下：

```cpp

-1, -1, -1, 1, 2 -> -2, -1, 0, 1, 2

```

这显然是不合法的。

#### 样例测试

---

```cpp

7
-1 -1 4 5 1 2 3
  
```

- 当 $ i = 1\sim 2 $，$ a_i = -1 $ 时，$ ans + 1 $，$ num  + 1 $，统计 $ -1 $ 的个数。

- 当 $ i = 3 $，$ a_i = 4 $ 时，$ now $ 记录下 $ a_i $  的值。

- 当 $ i = 4 $，$ a_i = 5 $ 时，因为 $ 4 $ 和 $ 5 $ 之间没有 $ -1 $ 所以直接特判。

- 当 $ i = 5 $，$ a_i = 1 $ 时，$ a_i $ 不符合公差，进入下一个循环，$ ans + 1 $，$ now $ 再记录下 $ a_i $ 的值。

- 当 $ i = 6 $，$ a_i = 2 $ 时，因为 $ 1 $ 和 $ 2 $ 之间没有 $ -1 $ 所以再次特判。

- 当 $ i = 7 $，$ a_i = 3 $ 时，$ 7 $ 符合公差。

- 当 $ i = 8 $ 时，$ i > n $ 循环结束。

#### 代码

---

注意开 long long！！！

```cpp

#include <bits/stdc++.h>
#define int long long
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;
const int N = 2e5 + 5;
int n,s[N],num,chr,now,ans,num1;
signed main(){
    fst
    cin >> n;
    for (int i = 1;i <= n;i++) cin >> s[i];
    int i = 1;
    while (i <= n){
    	ans++;
        num = 0,num1 = 0;
        while (i <= n && s[i] == -1) num++,i++;
        if (i == n + 1) break;
        now = s[i],i++;
        while (i <= n && s[i] == -1) num1++,i++;
        if (i == n + 1) break;
		if ((s[i] - now) % (num1 + 1) != 0) continue;
        chr = (s[i] - now) / (num1 + 1);
        if (now - num * chr <= 0) continue;
        i++;
        while (i <= n){
        	if (s[i] == -1){
        		if (s[i - 1] + chr <= 0) break;
				s[i] = s[i - 1] + chr,i++;
			}
			else{
				if (s[i] != s[i - 1] + chr) break;
				i++;
			}
		}
    }
    cout << ans;
    return 0;
}

```

#### 附语

---

本蒟蒻的第二篇题解，求通过！！！

如有错误请及时指出，我必及时改正。

---

## 作者：CarroT1212 (赞：1)

好好好，三个月前做过，这回遇到又不会。

首先考虑没有 $-1$ 的时候怎么求答案。贪心地分割即可，每一位尽量跟前面的数组成等差数列，如果配不上就新开一个等差数列继续配，因为优先配前面的显然比自己单独开一组要优。

然后现在有 $-1$ 了。发现其实本质上并没有什么区别，在处理不是 $-1$ 的数的过程中再去考虑 $-1$ 对匹配造成的影响即可。影响也就四种：

+ 加入 $-1$ 后公差非整数，如 $4$ $6$ $8$ 塞成了 $4$ $-1$ $-1$ $6$ $-1$ $-1$ $8$。
+ 加入 $-1$ 后公差不相等，如 $4$ $6$ $8$ 塞成了 $4$ $-1$ $6$ $8$。
+ 延续等差数列的时候变成了非正数，如 $8$ $6$ $4$ $-1$ $-1$ $-1$，不拆的话后面两个 $-1$ 要变成 $0$ $-2$。
+ 作为等差数列开头的时候变成了非正数，如 $-1$ $-1$ $-1$ $4$ $6$ $8$。

于是按类似没有 $-1$ 的做法来，先找到两个不是 $-1$ 的数，再去判数列开头到第二个非 $-1$ 数间是否满足条件，不满足就取第二个非 $-1$ 数作为开头再搞；然后尝试延伸，途中反复判断是否满足所有条件。

```cpp
ll n,a[N],ans;
int main() {
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for (ll i=1,l,r;i<=n;) {
		ans++;
		for (l=i;a[l]==-1&&l<=n;l++);
		for (r=l+1;a[r]==-1&&r<=n;r++);
		if (l>n||r>n) break;
		ll tmp=(a[r]-a[l])/(r-l),flg=1;
		if ((a[r]-a[l])%(r-l)!=0||a[l]-(l-i)*tmp<=0) { i=r; continue; }
		for (ll k=r+1;k<=n;k++)
			if (a[r]+(k-r)*tmp<=0||a[k]!=-1&&a[k]!=a[r]+(k-r)*tmp) { flg=0,i=k; break; }
		if (flg) break;
	}
	printf("%lld",ans);
	return 0;
}
```

11-17 upd：原来数字不加 `$$` 过不了审。

---

