# Folding Strip

## 题目描述

You have a strip of paper with a binary string $ s $ of length $ n $ . You can fold the paper in between any pair of adjacent digits.

A set of folds is considered valid if after the folds, all characters that are on top of or below each other match. Note that all folds are made at the same time, so the characters don't have to match in between folds.

For example, these are valid foldings of $ s = \mathtt{110110110011} $ and $ s = \mathtt{01110} $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1965C/cdcd37b9d52400313db3672e3c8605e2ff8b16ce.png)The length of the folded strip is the length seen from above after all folds are made. So for the two above examples, after the folds shown above, the lengths would be $ 7 $ and $ 3 $ , respectively.

Notice that for the above folding of $ s = \mathtt{01110} $ , if we made either of the two folds on their own, that would not be a valid folding. However, because we don't check for validity until all folds are made, this folding is valid.

After performing a set of valid folds, what is the minimum length strip you can form?

## 说明/提示

For the first example case, one optimal folding is to fold the strip in the middle, which produces a strip of length 3.

The third and fourth example cases correspond to the images above. Note that the folding shown above for $ s = \mathtt{110110110011} $ is not of minimal length.

## 样例 #1

### 输入

```
6
6
101101
1
0
12
110110110011
5
01110
4
1111
2
01```

### 输出

```
3
1
3
3
1
2```

# 题解

## 作者：Creeper_l (赞：6)

结论：从左往右考虑，每遇到两个相邻且相同的字符就翻转一次。这样一定合法且最优。

首先考虑方案的合法性。因为只要有两个相邻且相同的字符就翻转一次，所以最终所有相同字符的位置的奇偶性一定是相同的，且一定形如 $0101\dots$，所以一定合法。

接着考虑为什么一定最优。显然，两个相邻但不相同的字符一定不可能翻转，且翻转次数越多最终长度一定越小。所以每遇到两个相邻且相同的字符就翻转一次一定是最优的。

怎么计算答案？可以维护一个当前的方向，若翻转一次就转向，同时维护走到的最左端 $l$ 和最右端 $r$，那么 $r-l+1$ 就是答案。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5 + 10;
int T,n;
char a[MAXN]; 
signed main() {
	for(cin >> T;T;T--) {
		cin >> n >> (a + 1);
		int L = 1e18,R = -1e18,pos = 0;
		int Fangxiang = 1;a[0] = 'a';
		for(int i = 1;i <= n;i++) {
			if(a[i] == a[i - 1]) Fangxiang *= -1;
			else pos += Fangxiang;
			L = min(L,pos),R = max(R,pos);
		} cout << R - L + 1 << endl;
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：5)

结论题。

## 解题思路

注意到最终状态必定不存在两个连续相同的字符，可以推出长度 $\gt 2$ 的连续字符段不具有优势，故原字符串可以等价转化为连续段长度为 $1$ 或 $2$ 的字符串，具体的，长度为奇数的连续段等价于长度为 $1$ 的连续段，长度为偶数的连续段等价于长度为 $2$ 的连续段。

而在此种情况下不折叠一定不优，若折叠则方案唯一，模拟折叠即可。

---

## 作者：369Pai (赞：3)

手玩发现，不能再折叠的充要条件是剩下的串是一个 $01$ 交替的字符串。

必要性显然，充分性考虑如下操作：从左往右扫描，遇到相邻相同的字符，就在之间折叠一次。

![](https://espresso.codeforces.com/280a4f6913a5414847a672f67e504b230bcd6ba9.png)

证明一下合法性：首先对于长度 $> 2$ 的连续段，其可以视为长度 $\le 2$ 的，奇偶性相同的连续段。

然后对这样缩过的串考虑从左往右，依次在长度为 $2$ 连续段中间折叠，对于一次折叠，短的一半直接对应长的一半，长的一半多出来部分，可能对应空，可能对应若干次折叠后更长的。

即对于折叠之后的串，相同字母所在位置的奇偶性一定相同（否则会再次折叠），这也说明剩下的是一个 $01$ 交替的串。

假设对原串所有相邻相同位置都进行折叠，会得到唯一一个（翻转视作同一个）$01$ 交替的串。这是因为对于任意一种确定折叠位置集合，但折叠方向不同的折叠方式，都可以从内到外不停展开，得到形如“先向左折，再向右折，再向左折……”这样左右交替折的形式。

接下来证明，这个 $01$ 交替的串是长度最短的。

对于一个由初始字符串 $s$ 若干次折叠得到的字符串 $t$，如果在 $t$ 的基础上继续折叠得到 $t'$，那么可以使用与上一段类似的展开方法，通过直接对 $s$ 折叠，得到相同的字符串 $t'$。

而进行若干次折叠之后的串不长于原串，所以对于任意存在相邻相同位置的串，其都可以再进行折叠，得到唯一的，$01$ 交替的，长度不长于它的串。

实现：模拟对原串所有相邻相同位置都进行折叠的过程，维护 $l,r$，表示相对的左右边界位置，以及 $j$ 表示相对的当前位置，$k\in\{1,-1\}$ 表示方向。每次遇到相邻相同位置，改变方向；否则 $j'\leftarrow j+k$，更新 $l,r$。

```cpp
int l = 1 , r = 0;
for(int i = 0 , j = 0 , k = 1 ; i < n ; i++)
{
    if(i && s[i] == s[i - 1])k *= -1;
    else 
    {
        j += k;
        l = min(l , j);
        r = max(r , j);
    }
}
```

时间复杂度 $\mathcal{O}(n)$。

---

## 作者：N1K_J (赞：2)

酷炫题目。

题目大意：给定一个有 $n$ 个位置为 $0$ 或 $1$ 的纸条，每个位置是 $0$ 或 $1$。对纸条以两个位置之间为折痕折叠，进行若干次折叠后，如果最后纸条每个位置折叠后**同一位置所有叠在一起得数**相等，称这样的折叠合法，求最短能合法地折多短。

$\sum n \le 2 \cdot 10^5$。

考试的时候以为是只要最上面最下面相等，红温了。

非常神奇的结论题：在所有相邻相同数之间折叠一次，折叠后的结果满足 $0，1$ 分别分布在偶数或奇数位，是合法的折叠。

而这样折叠后的结果是形如 $0,1$ 交替出现的串，是无法继续折叠的。

因此，这就是答案。

模拟折叠过程就做完了。

[Code](https://codeforces.com/contest/1965/submission/258831804)

---

## 作者：WeWantToRun (赞：1)

大家好，我没猜到结论。

在草稿纸上做这个题的时候发现翻转顺序不影响结果，感觉上挺对的，但是我不会证。

于是可以先把连着三个相等的变成一个。然后最后的形状一定是形如 `10101010` 状物，所以把所有 `00` 和 `11` 的下标拿出来，那么折叠就可以相当于在差分数组上操作。

那么如果有三个数 $x,y,z$，其中 $x>y,z>y$，那么就一定可以取 $x$ 的后 $y$ 个，$z$ 的前 $y$ 个和 $y$ 给他折起来，变成 $x+z-y$。然后如果开头有两个数 $x<y$ 那么 $x$ 是没用的，反之结尾上也有类似的结论。由于认为操作的次序不影响结果，所以可以维护一个栈表示当前做到差分数组里的状态，那么不难发现这个栈是单调不降的。每次加入一个数然后看前一位能否折叠，然后类似单调栈往前推进。最后剩下一个单调不减的序列，根据前面的结论就可以等价为序列第一个数，也就是说最后栈底元素就是答案，模拟这个过程即可，时间复杂度 $O(n)$。

于是我做完了这个题也没猜出结论。代码就不放了。

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路
	经过实验，可知在相邻的且相同的两个格子之间折叠，最后得出的纸条一定是一个没有任何两个相邻格子相同的串，且折得越多，剩下的纸条一定越短，最后得知：每碰到相邻且相同的两个格子折叠就一定为最优。最后模拟纸的折叠，标记到达过的最左与最右，即可求出答案。
    
- ### 具体实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
char a[200005];
int main()
{
	scanf("%d",&T);
	int l,r,ans,bz;
	while(T--)
	{
		scanf("%d",&n);
		cin>>(a+1);
		l=0;
		r=0;
		ans=0;
		bz=1;
		for(int i=2;i<=n;i++)
		{
			if(a[i]==a[i-1]) bz=-bz;
			else ans+=bz;
			r=max(r,ans);
			l=min(l,ans);
		}
		printf("%d\n",r-l+1);
	}
}

---

## 作者：huhaoming2011 (赞：0)

## 题目大意
给你一个只有 $0$ 和 $1$ 的字符串，不断地进行翻折（前提是翻折后翻折所对应的格子里的字符相同），使得最后字符串的长度最小。
## 分析
很明显地发现，翻折时一定在某两个相邻且字符相等的格子之间为断点进行翻折。所以只要将它翻折直到最后剩下的字符串并无相邻的格子字符相同，即它为交替的形式，此时的答案即为最优解。时间复杂度为 $O(T \times n)$。
## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
signed main()
{
	int T,c[N];
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		char ch=getchar();
		while(ch!='1'&&ch!='0') ch=getchar();
		int j=0;
		while(ch=='1'||ch=='0')
		{
			c[++j]=ch-'0';
			ch=getchar();
		}
		int lft=0,rt=0,sum=0,ff=1;
		for(int i=2;i<=n;i++)
		{
			if(c[i]==c[i-1]) ff=-ff;
			else sum+=ff;
			lft=(lft>sum?sum:lft);
			rt=(rt>sum?rt:sum);
		}
		printf("%d\n",rt-lft+1);
	}
	return 0;
}
```
#### 感谢观看！！！

---

