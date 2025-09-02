# Prefix Flip (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is the constraint on $ n $ and the required number of operations. You can make hacks only if all versions of the problem are solved.

There are two binary strings $ a $ and $ b $ of length $ n $ (a binary string is a string consisting of symbols $ 0 $ and $ 1 $ ). In an operation, you select a prefix of $ a $ , and simultaneously invert the bits in the prefix ( $ 0 $ changes to $ 1 $ and $ 1 $ changes to $ 0 $ ) and reverse the order of the bits in the prefix.

For example, if $ a=001011 $ and you select the prefix of length $ 3 $ , it becomes $ 011011 $ . Then if you select the entire string, it becomes $ 001001 $ .

Your task is to transform the string $ a $ into $ b $ in at most $ 2n $ operations. It can be proved that it is always possible.

## 说明/提示

In the first test case, we have $ 01\to 11\to 00\to 10 $ .

In the second test case, we have $ 01011\to 00101\to 11101\to       01000\to 10100\to 00100\to 11100 $ .

In the third test case, the strings are already the same. Another solution is to flip the prefix of length $ 2 $ , which will leave $ a $ unchanged.

## 样例 #1

### 输入

```
5
2
01
10
5
01011
11100
2
01
01
10
0110011011
1000110100
1
0
1```

### 输出

```
3 1 2 1
6 5 2 5 3 1 2
0
9 4 1 2 10 4 1 2 1 5
1 1```

# 题解

## 作者：gaozitao1 (赞：8)

**题目大意**：给定两个二进制字符串 $a$ 和 $b$ ，通过不超过 $2n$ 次操作，将字符串 $a$ 变成字符串 $b$。每一次操作将字符串 $a$ 的前 $p$ 个字符中 $0$ 变成 $1$，$1$ 变成 $0$，并将前 $p$ 个字符反转。

做这一道题之前，建议先做一下这一道题的简单版本 [CF1381A1 Prefix Flip (Easy Version)](https://www.luogu.com.cn/problem/CF1381A1) 。

对于 CF1381A1 ，可以考虑每次使 $a$ 与 $b$ 的最后一个字符相同，这样最多操作 $2n$ 次，在操作上符合要求。

但是这样时间复杂度是 $O\left(n^2\right)$，不能通过本题，需要优化。

可以发现，如果修改的时候同时考虑两个字符串的话，是很麻烦的，所以，可以考虑**一次只修改一个字符串**。

如果每一个字符串中只有 $0$ 或只有 $1$，那么最多操作一次就可以了。

这可以给我们启发：**可以将每一个字符串变成只有一种字符的字符串**。

所以，接下来的任务就是如何将每一个字符串变成只有一个字符的字符串。

这个可以从前面开始遍历，如果这个位置与后一个位置不同，那么就对这一个位置之前的进行操作，一直到最后就可以了。

举个例子：$01010\to11010\to00010\to11110\to00000$。

而且，我们经过上面的操作之后，**每一个字符串的字符与原字符串最后一个字符相同**，所以我们就不需要在数组中修改了，这样就减少了许多时间复杂度。

最后，我们**要判断这两个字符串是否一样**，如果一个全是 $0$，另一个全是 $1$，那么就需要对整个字符串进行操作。

还有一个问题：题目中让我们输出操作字符串 $a$ 的方案，但是我们在处理的过程中操作字符串 $b$ 了，所以输出时对字符串 $b$ 的方案应该倒着输出。

对于每一个字符串，最多操作 $n-1$ 次，最后判断是否一样，最多操作 $1$ 次，这样，总共操作不超过 $2n-1$ 次，符合要求。

时间复杂度为 $O\left(n\right)$。

**代码：**
```cpp
#include<cstdio>
#include<iostream>
const int N=100000;
char a[N+1],b[N+1];
int c[N],d[N];//c和d分别记录a和b的操作
int main()
{
	register int i,j,k,n,t;//j和k分别统计a和b的方案数
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%s%s",&n,a+1,b+1);
		j=k=0;//注意清零
		for(i=1; i<n; ++i)
		{
			if(a[i]!=a[i+1])
				c[++j]=i;//将a变成只有一种字符的字符串
			if(b[i]!=b[i+1])
				d[++k]=i;//将b变成只有一种字符的字符串
		}
		if(a[n]!=b[n])//如果两个字符串不一样，那么就要对整个字符串操作一次
			c[++j]=n;
		printf("%d ",j+k);//输出方案数
		for(i=1; i<=j; ++i)
			printf("%d ",c[i]);//输出a的操作
		for(i=k; i; --i)
			printf("%d ",d[i]);//倒着输出b的操作
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：onglu (赞：8)

~~真的没有人写平衡树吗~~  
~~为什么这么难的一道题这么多人直接秒了啊~~  
~~原来不是平衡树啊，那没事了~~
## 思路
写了EZVersion之后，就顺着EZVersion的思路走了。  
倒叙枚举，每次判断$a[j]$和$b[j]$是否相同，如果相同就跳过，不同就去改变$b[j]$。  
如果$a[1]$和$b[j]$相同，那么直接对$(1,j)$进行操作即可。  
如果不同，那么我们先操作$(1,1)$再操作$(1,j)$。  
这样想法就很显然了，但是时间复杂度是$O(n^2)$的，瓶颈在于翻转。  
自然 ~~（我是傻逼）~~ 地想到了使用平衡树维护序列翻转，我们用splay维护序列即可，具体怎么翻转见[P3391 【模板】文艺平衡树](https://www.luogu.com.cn/problem/P3391)。  
只需要把$1$~$n$对应改成数组下标即可。  
时间复杂度$O(Tnlogn)$。  
具体见代码吧。  

  
  ## 代码
  ```cpp
  #include <bits/stdc++.h>
#define siz(x) tree[x].siz
#define son(x, k) tree[x].ch[k]
#define qwq(x) tree[x].qwq
#define val(x) tree[x].val
#define fa(x) tree[x].fa
#define f(x) tree[x].f
#define Mid ((l + r) >> 1)
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define ll long long
#define ull unsigned long long
using namespace std;
const int N = 3e5 + 1009;
const int inf = (1 << 31) - 1;
int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-') f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';;
	return f * num;
}
int n, a[100009], b[100009], ans[300009];
char s[300009];


int root = 1;
struct Node{
	int siz, val, ch[2], fa, f, qwq;
}tree[N];
void update(int x){
	siz(x) = siz(son(x, 0)) + siz(son(x, 1)) + 1;
}
int chk(int x){
	return son(fa(x), 1) == x;
}
void rotate(int x){
	int y = fa(x), z = fa(y), k = chk(x), w = son(x, k ^ 1);
	son(y, k) = w; fa(w) = y;
	son(z, chk(y)) = x; fa(x) = z;
	son(x, k ^ 1) = y; fa(y) = x;
	update(y);update(x);
}
void splay(int x, int goal = 0){
	while(fa(x) != goal){
		int y = fa(x), z = fa(y);
		if(z != goal){
			if(chk(x) == chk(y))rotate(y);
			else rotate(x);
		}
		rotate(x);
	}
	if(!goal) root = x;
}
void build(int l, int r, int rt){
	if(l == r){
		val(rt) = l; siz(rt) = 1;
		son(rt, 0) = son(rt, 1) = 0;
		return ;
	}
	val(rt) = Mid;
	if(Mid - 1 >= l){
		son(rt, 0) = lson;
		fa(lson) = rt;
		build(l, Mid - 1, lson);
	}
	if(Mid + 1 <= r){
		son(rt, 1) = rson;
		fa(rson) = rt;
		build(Mid + 1, r, rson);
	}
	update(rt);
}
void pushdown(int x){
	if(f(x)){
		f(x) = 0;
		if(son(x, 0)) f(son(x, 0)) ^= 1;
		if(son(x, 1)) f(son(x, 1)) ^= 1;
		a[val(x) - 1] ^= 1;
		swap(son(x, 0), son(x, 1));
	}
}
int Kth(int k){
	int cur = root;
	while(cur){
		if(f(cur))pushdown(cur);
		if(son(cur, 0) && siz(son(cur, 0)) >= k) cur = son(cur, 0);
		else if(siz(son(cur, 0)) + 1 >= k)return cur;
		else k -= siz(son(cur, 0)) + 1, cur = son(cur, 1);
	}
}
void print(int x){
	pushdown(x);
	if(son(x, 0))print(son(x, 0));
	if(val(x) > 1 && val(x) < n + 2)printf("%d ",a[val(x) - 1]);
	if(son(x, 1))print(son(x, 1));
}
void Change(int l, int r){
	l = Kth(l); r = Kth(r + 2);
	splay(l);splay(r, l);
	f(son(r, 0)) ^= 1;	
}
int Query(int x){
	return a[val(Kth(x + 1)) - 1];
}
void work(){
	int cnt = 0;
	n = read(); root = 1;
	memset(tree, 0, sizeof(tree));
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)a[i] = s[i] - '0';
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)b[i] = s[i] - '0';
	build(1, n + 2, 1);
	
	for(int j = n; j > 1; j--)if(Query(j) != b[j]){
		
		if(Query(1) == 1 - b[j]){
			ans[++cnt] = j;
			Change(1, j);
			//如果直接换就行的话
		}else {
			ans[++cnt] = 1;
			Change(1, 1);
			ans[++cnt] = j;
			Change(1, j);
		}
		
	}
	if(Query(1) != b[1]){
		ans[++cnt] = 1;
	}
	printf("%d ", cnt);
	for(int i = 1; i <= cnt; i++)
		printf("%d ", ans[i]);
	printf("\n");

}
int main()
{
	int Case = read();
	while(Case--) work();
	return 0;
}
/*
一位一位来
想要把最后一位变成0,先看首位是不是1
如果不是的话，就要在之前找到一个0，
如果没有的话，就1和2位置reverse一下
想要把最后一位变成1,先看首位是不是0
如果不是的话，就要在之前找到一个1，
如果没有的话，就1和2位置reverse一下

需要维护单点查询，序列翻转，维护一个tag即可
*/
```

---

## 作者：Isenthalpic (赞：7)

教练讲的一种做法。

不需要模拟过程，大致思路是将原始$01$序列和目标$01$序列全都变为只包含$0$或只包含$1$的序列。

从前往后扫描，如果遇到不一样的将前面全部反转，然后记录步骤。

注意目标的步骤必须逆向，即倒序输出，中间还有特判。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,T,ans1[N],ans2[N]; 
char a[N],b[N];
int main(){
	scanf("%d",&T);
	while(T--){
		int tot=0,num=0;
		scanf("%d %s %s",&n,a+1,b+1);
		for(int i=1;i<n;i++)if(a[i]!=a[i+1])ans1[++tot]=i; 
		for(int i=1;i<n;i++)if(b[i]!=b[i+1])ans2[++num]=i; 
		if(a[n]==b[n])printf("%d ",tot+num);
		else printf("%d ",tot+num+1);
		for(int i=1;i<=tot;i++)printf("%d ",ans1[i]);
		if(a[n]!=b[n])printf("%d ",n); 
		for(int i=num;i>=1;i--)printf("%d ",ans2[i]);
		puts("");
	} 
	return 0;
}
```


---

## 作者：Guess00 (赞：4)

## CF1381A2 Prefix Flip (Hard Version)
在阅读本篇题解前请先阅读本人Easy Version的[$\color{red}\texttt{题解}$](https://www.luogu.com.cn/blog/Guess00/solution-CF1381A1)

每次进行一次操作时都会将$a_1,a_2,..a_i$都翻转一遍，然而每次翻转时只看$a_1$和$a_i$(一头一尾)，于是可以记录下翻转次数和$a_1$和$a_i$的位置，这样就将$\Theta(n^2)$优化至$\Theta(n)$。

令$l$为$a_1$在初始$a$上的位置，$r$为$a_i$在初始$a$上的位置。不难发现，从后往前进行操作时第$i-1$位肯定在第$i$位的旁边，所以从$i$转移到$i-1$时只需$+1$或$-1($之所以会$+1$是因为翻转后$r$可能小于$l).$详细细节见代码。

$\mathbb{CODE:}$
```cpp
#include <bits/stdc++.h>
const int MAXN=100005;
int T,n,i,j,l,r,t,cnt,ans[MAXN<<1];//t用来进行a[r]a[l]到a[i]a[1]的转移 
bool a[MAXN],b[MAXN];
char c;
inline void read(int &x)//快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)//快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
signed main(void)
{
	read(T);
	while (T--)
	{
		read(n);
		for (i=1;i<=n;i++)
		{
			c=getchar();
			while (c!='0' && c!='1')
				c=getchar();
			a[i]=(c=='1');
		}
		for (i=1;i<=n;i++)
		{
			c=getchar();
			while (c!='0' && c!='1')
				c=getchar();
			b[i]=(c=='1');
		}
		for (l=1,i=r=n,cnt=t=0;i>=1;i--,r+=(l<r)?-1:1)//这一句话中包括:从后往前模拟,一些变量的赋初值,每次r的转移 
		{
			if ((a[r]^t)==b[i])  //如果这位本身就相等就不用进行任何操作
                continue;
            if ((a[l]^t)==b[i])  //b[i]!=?a[i]
                ans[++cnt]=1;
            ans[++cnt]=i;
            std::swap(l,r);  //因为要翻转,所以交换lr来代替整段翻转 
            t^=1;//这种处理方式应该很常见吧,每次翻转值会被负一次,每两次又会变回来,用t来体现负了几次 
		}
		print(cnt),putchar(' ');
		for (i=1;i<=cnt;i++)  //输出 
			print(ans[i]),putchar(' ');
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Illusory_dimes (赞：1)

前言：之所以会有 A3 是因为算是 A2 的加强版吧。

$\text{STO}$ $\color{black}{\text{T}}\color{red}{\text{erryWang}}$ $\text{ORZ}$

## Description

给定 $01$ 文本串，母串以及两串的长度 $n$ ，给定一种操作，可以对文本串任意前缀进行 $01$ 取反，并同时反转整个选定的前缀。

求一种不多于 $n + 1$ 次操作的方案，使得文本串转变成母串。

多测。

$\sum n \leq 3 \cdot 10 ^ 5$

（原题 A2 的要求是操作次数不超过 $2n$ ）

## Analysis

感觉这种操作非常的莫名其妙，又是取反还有翻转，不知道该怎么从操作本质上下手了。

所以会有很多奇奇怪怪的想法，不过我们要直切主题，就暂时不管其他奇奇怪怪的算法了。

我们不用想那么多通过什么技巧能多少多少次还原一个区间，只需要想，假如操作不是前缀，有什么不一样的地方。

相比之下，前缀操作明显的特点就是假如后半部分已经还原，就不再需要照顾，所以我们可以考虑倒序还原。

看操作的本质，我们有什么是可以直接掌控的，能发现对于第一位的前缀，它的翻转是没有体现出来的，从而我们可以直接控制第一位的 $01$ 。

而要体现出翻转的特性的话，第一位一定会翻到最后一位，所以我们可以通过控制第一位的 $01$，然后把一个前缀翻转，能够至少还原后缀的一位。

所以每次至多两次操作还原一个位置，总体就能很好地控制在 $2n$ 操作内。

不过数据强度不是很大的话，这个东西是很容易下 $n + 1$ 的，不过为了严谨性，我们还是认为这个做法只能做原题。

## Solution

idea from $\color{black}{\text{T}}\color{red}{\text{erryWang}}$ from $\color{red}{\text{icecuber}}$

其实就是上一个做法的改编版。

我们考虑到对于每一位我们只是有可能要做翻转第一位的 $01$，假如我们必须要只用一次复原一位咋办。

不妨换一种思路，我们改成均摊一位一次，相当于我们通过放宽操作次数，但是同时让多位同时满足。

我们可以理解成我一个人一次性解决不了，我就在拉一个人下水，但是两次能同时解决掉两人。

提前放一句话，因为对 $b$ 的操作倒过来是等价于对 $a$ 操作，所以本质上母串可以是两者的任何一个，所以我们仅对文本串是 $a$ ，母串是 $b$ 的情况讨论（同时注意我们是对于每一个情况都要让两个串都作为母串做一次判断）。

同时，我们先提前假设我们处理到了第 $i$ 位。

1. $a_i = b_i$

这种情况非常舒服，因为你发现根本没有翻转什么事，直接删掉就行了。

2. $a_1 \neq b_i$

否则，我们尝试通过一次操作让母串增加一位相等，有翻转+取反，所以母串的最后一位就对应了文本串的第一位的相反值，所以就会有上面那个条件。

3. $b_{i - 1} = b_i$

之前的算法到这里就没有然后了，所以我们就只能考虑再拉一位下水。

因为有了之前不满足的条件，首先就有 $a_1 = b_i$，所以也有 $a_1 = b_{i - 1}$，现在因为牵扯到了两位，所以要考虑 $a_2$ 的值了。

因为 $a_1$ 的值取反之后就不等于最后一位，所以必须先取反一次：

如果 $a_1 = a_2$ 的话，就有 $a_2 = b_{i - 1}$，所以 $a_2$ 也要先取反一次，一合计发现对前两位操作就算翻转也不影响，再对整个串操作就可以了。

否则就更简单了，第二维都不用管了，直接对第一位操作，再对整个串操作就行了。

两次，完美。

4. $a_1 = a_2$

同样利用上之前不满足的条件：$a_1 = b_i, b_{i - 1} \neq b_i$。

所以可以由此推得 $a_2 \neq b_{i - 1}$ ，整合一下，第二位并不需要翻转，只需要操作第一位，再把整个串操作一次就够了。

两次，完美。

5. $a_{i - 2} \neq a_{i - 1}$

现在又没有头绪了，只好把眼光放到第三位上，再拉一位下水。

$a_i \neq b_i,a_1 = b_i,b_{i - 1} \neq b_i,a_1 \neq a_2$，当然因为之前的所有操作 $a$ 和 $b$ 都做过母串，所以上面的条件 $a$ 和 $b$ 互换也是可以的（不然推不动）。

所以整个一串加上 $01$ 只有两种取值：

$$a_{i - 2} \neq a_{i - 1} \neq a_i \neq b_i \neq b_{i - 1} \rightarrow a_{i - 1} = b_{i},\ a_{i - 2} = b_{i - 1}$$

所以我们可以先操作 $i - 1$ 再操作 $i$ 就可以把 $a_{i - 2},\ a_{i - 1}$ 右移一位，并且两次操作不影响数值，于是就匹配上两位了。

两次，完美（虽然实际上用了三位，但是只还原了两位）

6. 没有什么情况的了

所有条件都不管用怎么办，那么现在两个串应该长这个样子了（嫖一张 $\color{black}{\text{T}}\color{red}{\text{erryWang}}$ 的图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/y3pus83s.png)

（其中不同的颜色就表示不同的数值）

现在是不得不拖第三位下水了，这也就意味着我们可以操作三次了。

首先我们可以向上一个操作把 $a_{i - 2},a_{i - 1}$ 右移一位，欸，最后一位就满足了。

同时我们也清楚 $a_1,a_2$ 也都会右移一位，而此时第一位上是取反了的 $a_i$，对着上面那张图看，$a$ 前两位就都是红色了。

假如我们再对 $i - 1$ 操作，对应到 $b_{i - 1},b_{i - 2}$ 恰好都是蓝色，正好是我们想要的。

所以剩下的这种情况我们可以通过操作 $i - 1,i,i - 1$ 来还原三位，非常舒服。

------------

但是这没完，我们发现最后一种操作的上限至少是 $i \ge 5$，所以最后我们可能会剩下 $i = 1,2,3,4$ 的位数没有还原。

怎么办呢，Analysis 的做法会让我们不能保持上限 $n + 1$ 的。

不过考虑到位数过少，我们可以尝试暴力枚举然后尝试每一种翻转可能，确定一个不超限制的方案。

但是有例外，样例中有这么一个东西：

```
2
01
10
3 1 2 1
```

我们发现这个例子必须要用到 $3$ 次操作，算是一个唯一的例外（$a$ 和 $b$ 反过来当我没说），所以即使我们从大局上看上限是 $n$ 的，但是因为这个例外，我们也只能做到 $n + 1$ 的了。

## Code_Ana

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;

#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout);
#define Check(a) freopen(a".in", "r", stdin), freopen(a".ans", "w", stdout);

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i7;
typedef std::pair<int, int> pii;
#define fi first
#define se second
#define mp std::make_pair
#define eps 1e-6

const int mod = 1e9 + 7;
template <typename A>
inline int M(A x) {return x;}
template <typename A, typename ...B>
inline int M(A x, B ... args) {return 1ll * x * M(args...) % mod;}

#define mi(x) (x >= mod) && (x -= mod)
#define ad(x) (x < 0) && (x += mod)

const int N = 3e5 + 10;

int n, a[N], b[N];
char s[N], t[N];

inline void mian() {
	std::cin >> n >> s >> t;
	for (int i = 1; i <= n; ++i) {
		a[i] = s[i - 1] - '0';
		b[i] = t[i - 1] - '0';
	}

	int l = 1, r = n, fg = 0;
	std::vector<int> an;
	for (int i = n; i >= 1; --i) {
		a[r] ^ fg ^ b[i] && (
			!(a[l] ^ fg ^ b[i]) && (an.emplace_back(1), a[l] ^= 1), 
			an.emplace_back(i), std::swap(l, r), fg ^= 1
		);

		l < r && (--r); l > r && (++r);
	}

	std::cout << an.size() << " ";
	for (int v : an) std::cout << v << " ";
	std::cout << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// File("flip");

	int t; std::cin >> t; while (t--) mian();

	return 0;
}
```

## Code_Sol

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;

#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout);
#define Check(a) freopen(a".in", "r", stdin), freopen(a".ans", "w", stdout);

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i7;
typedef std::pair<int, int> pii;
#define fi first
#define se second
#define mp std::make_pair
#define eps 1e-6

const int mod = 1e9 + 7;
template <typename A>
inline int M(A x) {return x;}
template <typename A, typename ...B>
inline int M(A x, B ... args) {return 1ll * x * M(args...) % mod;}

#define mi(x) (x >= mod) && (x -= mod)
#define ad(x) (x < 0) && (x += mod)

struct Flipper {
	std::deque<int> p;
	int siz;
	std::vector<int> all;
	bool fli;

	Flipper(string ni) {siz = fli = 0; for (auto c : ni) p.push_back(c - '0'), ++siz;}

	inline void pop() {--siz; fli && (p.pop_front(), 1); !fli && (p.pop_back(), 1);}

	int operator [](int i) {
		i < 0 && (i += siz);
		if (fli) return p[siz - 1 - i] ^ 1;
		return p[i];
	}

	inline void flip(int r) {
		all.push_back(r > 0 ? r : siz + r);

		if (r > 0) {
			int l = 0;
			fli && (l = siz - r, r = siz);
			reverse(p.begin() + l, p.begin() + r);
			for (int i = l; i < r; ++i) p[i] ^= 1;
		}
		else if (!r) fli ^= 1;
		else {
			int dan;
			fli && (dan = p.front(), p.pop_front(), p.push_back(dan ^ 1), 1);
			!fli && (dan = p.back(), p.pop_back(), p.push_front(dan ^ 1), 1);
			fli ^= 1;
		}
	}
} ;

int n; string S, T;

inline void mian() {
	std::cin >> n >> S >> T;
	Flipper a(S), b(T);

	auto pop = [&](int cn) {while (cn--) a.pop(), b.pop();};

	while (a.siz >= 5) {
		if (a[-1] == b[-1]) pop(1);
		else if (a[-1] == b[-1]) pop(1);
		else if (a[0] == a[-1]) a.flip(0), pop(1);
		else if (b[0] == b[-1]) b.flip(0), pop(1);
		else if (b[-2] == b[-1]) a.flip(a[0] ^ a[1] ? 1 : 2), a.flip(0), pop(2);
		else if (a[-2] == a[-1]) b.flip(b[0] ^ b[1] ? 1 : 2), b.flip(0), pop(2);
		else if (a[0] == a[1]) a.flip(1), a.flip(0), pop(2);
		else if (b[0] == b[1]) b.flip(1), b.flip(0), pop(2);
		else if (a[-3] != a[-2]) a.flip(-1), a.flip(0), pop(2);
		else if (b[-3] != b[-2]) b.flip(-1), b.flip(0), pop(2);
		else a.flip(-1), a.flip(0), a.flip(-1), pop(3);
	}

	for (int I = 0; ; ++I) {
		bool sig = 0;
		for (int S = 0; S < 1 << (I << 1); ++S) {
			for (int i = 0; i < I; ++i) a.flip(min(S >> (i << 1) & 3, a.siz));

			bool fg = 1;
			for (int i = 0; i < a.siz; ++i) fg &= (a[i] == b[i]);
			if (fg) {sig = 1; break;}

			for (int i = I - 1; i >= 0; --i) a.flip(min(S >> (i << 1) & 3, a.siz));
			for (int i = 0; i < (I << 1); ++i) a.all.pop_back();
		}
		if (sig) break;
	}

	std::vector<int> ans = a.all;
	reverse(b.all.begin(), b.all.end());
	ans.insert(ans.end(), b.all.begin(), b.all.end());

	std::cout << ans.size() << " ";
	for (int x : ans) std::cout << x << " ";
	std::cout << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int T; std::cin >> T; while (T--) mian();

	return 0;
}
```

---

## 作者：xuezhe (赞：1)

下面定义翻转为调转顺序，反转为对区间按位取反。

首先不难发现，翻转并反转一个前缀，对剩下这部分的后缀是没有影响的。

所以可以从右到左依次确定每一位。

另外我们可以发现翻转并反转长度为 $1$ 的前缀可以看作只有反转没有翻转。

所以当从右到左扫的过程中如果找到 $a_i \neq b_i$ 就可以将 $a_1$ 调整至 $a_1 \neq b_i$ 后翻转并反转长度为 $i$ 的前缀，这里下标从 $1$ 开始，下同。

此时我们可以暴力模拟，时间复杂度 $O(n^2)$，操作次数为 $O(2n)$ 次，可以通过 Easy 部分。

可以发现由于在不考虑翻转并反转长度为 $1$ 的前缀的情况下，翻转并反转的前缀长度逐渐减小，所以我们所需要考虑的一段前缀必然是原序列中连续的、正序或逆序的、可能被反转过的一段区间。

所以我们只需要记录这段区间的左端点和右端点，以及翻转反转的情况就好了。

时间复杂度 $O(n)$，操作次数为 $O(2n)$ 次，可以通过 Hard 部分。

Code：

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int t,n;
char a[100005],b[100005];
vector<int> op;
int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        op.clear();
        cin>>n>>(a+1)>>(b+1);
        int l=1,r=n,rev=0;
        for(int i=n;i;--i){
            if((a[r]^rev)==b[i]){
                (l<r)?(--r):(++r);
                continue;
            }
            if((a[l]^rev)==b[i])
                op.pb(1);
            op.pb(i);
            swap(l,r);
            (l<r)?(--r):(++r);
            rev^=1;
        }
        cout<<op.size();
        for(int i=0;i<int(op.size());++i)
            cout<<' '<<op[i];
        cout<<'\n';
    }
    cout<<endl;
    return 0;
}
```


---

## 作者：素质玩家孙1超 (赞：1)

题意：给两串长度为 $n$ 的 $01$ 串 $a$ 、$b$ ，你可以若干次经行操作：将 $a$ 的一个前缀反转再对该前缀取反。要求在 $2n$ 次操作内把 $a$变成 $b$，输出方案。

---

是一个比较恶心的大模拟，首先要推出一个类似公式的东西，然后直接“代入”就好了。

+  首先考虑退化版

退化版要求操作次数在 $3n$ 次内，稍微观察一下，对于每一位，都可以用最多三次操作使其取反。

例如长度为 $5$ 的序列 $  a,b,c,d,e $，要反转第 $5$ 个。

对长度为 $5$ 的前缀操作得：$e',d',c',b',a'$（ $x'$ 表示对 $x$ 取反）。

对长度为 $1$ 的前缀操作得：$ e ,d',c',b',a'$。

对长度为 $5$ 的前缀操作得：$a,b,c,d,e'$。

成功得将 $e$ 取反。

+ 考虑强化版

首先我想到了对每 $2$ 位进行操作，如果能在 $4$ 步之内转成其他任意形式，就算完成了。但手玩了一会后发现做不到，只能类似退化版推一下：

例如长度为 $5$ 的序列 $  a,b,c,d,e $，要对最后两个进行整体操作。

对长度为 $5$ 的前缀操作得：$e',d',c',b',a'$

对长度为 $2$ 的前缀操作得：$ d,e,c',b',a'$。

对长度为 $5$ 的前缀操作得：$a,b,c,e',d'$。

我们发现最后两个被取反并且交换了。那么意味着对于字串 $00$ 变成 $11$ 或 $11$ 变成 $00$ 可以只用三次操作。但其他情况仍然不行。

所以我们只能再看第三位，假设现在处理的串为 $01$ ( $10$ 的情况类似)：

1.若对应的目标串与之只差一位，那么我们仍然可以用三次操作处理两位。

2.若对应的目标串为 $10$ ，那么我们看下一位：如果下一位匹配上了，我们可以直接用 $6$ 次将前两位处理完成，这样均摊下来仍然是合理的（相当于   $6$次处理三位）；若下一位无法匹配，则又有以下两种情况：$011$ 对应 $100$ ，$010$ 对应 $101$ ，前者可以把后两位和第一位分别处理花费 $6$
 次，后者可以用 $3$ 次操作完成，即对三位进行类似上文提到的整体操作。
 
 
 这样思路大底就完整了。但还有一些细节：
 
 如果长度是三的倍数，那么完全没问题直接三个三个处理。
 
 如果长度是三的倍数余 $1$ ，则可以先处理第一位。
 
 如果长度是三的倍数余 $2$ ，则可以先处理前两位。（第一位 $1$ 次操作加上第二位 $3$ 次操作）。
 
 
---

代码（比赛的时候写的，思路比较凌乱，代码又长又丑）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e5+5;
inline int R()
{
	char c;int res,sign=1;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;
}
int a[Maxn],b[Maxn],n; 
int main()
{
	int t=R();
	while(t--)
	{
		n=R();
		for(int i=1;i<=n;i++)
		{
			char c;
			while((c=getchar())!='0'&&c!='1') ;
			a[i]=c-'0';
		}
		for(int i=1;i<=n;i++)
		{
			char c;
			while((c=getchar())!='0'&&c!='1') ;
			b[i]=c-'0';
		}
		if(n==3)
		{
			if(a[1]!=a[2]&&a[2]!=a[3])
			{
				if(b[1]!=b[2]&&b[2]!=b[3])
				{
					if(b[1]!=a[1])
					{
						puts("1 3");
						continue;
					}
				}
			}
			else 
			{
				if(a[1]==a[2]&&b[1]==b[2]&&a[1]!=b[1])
				{
					if(a[3]==b[3])
					{
						puts("1 2");
						continue;
					}
					if(a[3]!=b[3])
					{
						puts("4 2 3 1 3");
						continue;
					}
				}
			}
		}
		int ans=0;
		if(a[1]!=b[1]) ans++;//printf("1 ");
		for(int i=2;i<=n;i+=2)
		{
			if(i==n)
			{//如果扫到头了 
				if(a[i]!=b[i])
				{
					ans+=3;//printf("%d %d %d ",i,1,i);
				}
				break;
			}
			if((a[i]==b[i])+(a[i+1]==b[i+1])==0)
			{//如果都不匹配 
				if(a[i]==a[i+1])//11->00 
				{
					ans+=3;//printf("%d %d %d ",i+1,2,i+1);
				}
				else //如果是10->01 
				{
					if(i+2>n)//到头了 
					{
						ans+=6;//printf("%d %d %d ",i,1,i);
						//printf("%d %d %d ",i+1,1,i+1);
					}
					else if(a[i+2]==b[i+2])//第三个相等的 
					{
						ans+=6;//printf("%d %d %d ",i,1,i);
						//printf("%d %d %d ",i+1,1,i+1);
					}
					else //第三个不相同 
					{
						if(a[i+1]==a[i+2])
						{
							ans+=6;
						//	printf("%d %d %d ",i+2,2,i+2);
						//	printf("%d %d %d ",i,1,i);
						}
						else 
						{
							ans+=3;//printf("%d %d %d ",i+2,3,i+2);
						}
					}
					i++;
				}
			}
			else if((a[i]==b[i])+(a[i+1]==b[i+1])==1)
			{
				if(a[i]==b[i]) ans+=3;//printf("%d %d %d ",i+1,1,i+1);
				else  ans+=3;//printf("%d %d %d ",i,1,i); 
			}
		}
		//puts("");
		if(ans>n*2)//失败 
		{
			ans=0;
		//if(a[1]!=b[1]) ans++;//printf("1 ");
		for(int i=1;i<=n;i+=2)
		{
			if(i==n)
			{//如果扫到头了 
				if(a[i]!=b[i])
				{
					ans+=3;//printf("%d %d %d ",i,1,i);
				}
				break;
			}
			if((a[i]==b[i])+(a[i+1]==b[i+1])==0)
			{//如果都不匹配 
				if(a[i]==a[i+1])//11->00 
				{
					ans+=3;//printf("%d %d %d ",i+1,2,i+1);
				}
				else //如果是10->01 
				{
					if(i+2>n)//到头了 
					{
						ans+=6;//printf("%d %d %d ",i,1,i);
						//printf("%d %d %d ",i+1,1,i+1);
					}
					else if(a[i+2]==b[i+2])//第三个相等的 
					{
						ans+=6;//printf("%d %d %d ",i,1,i);
						//printf("%d %d %d ",i+1,1,i+1);
					}
					else //第三个不相同 
					{
						if(a[i+1]==a[i+2])
						{
							ans+=6;
						//	printf("%d %d %d ",i+2,2,i+2);
						//	printf("%d %d %d ",i,1,i);
						}
						else 
						{
							ans+=3;//printf("%d %d %d ",i+2,3,i+2);
						}
					}
					i++;
				}
			}
			else if((a[i]==b[i])+(a[i+1]==b[i+1])==1)
			{
				if(a[i]==b[i]) ans+=3;//printf("%d %d %d ",i+1,1,i+1);
				else  ans+=3;//printf("%d %d %d ",i,1,i); 
			}
		}
		//puts("");
		printf("%d ",ans);
	//	if(a[1]!=b[1]) printf("1 ");
		for(int i=1;i<=n;i+=2)
		{
			if(i==n)
			{//如果扫到头了 
				if(a[i]!=b[i])
				{
					printf("%d %d %d ",i,1,i);
				}
				break;
			}
			if((a[i]==b[i])+(a[i+1]==b[i+1])==0)
			{//如果都不匹配 
				if(a[i]==a[i+1])//11->00 
				{
					printf("%d %d %d ",i+1,2,i+1);
				}
				else //如果是10->01 
				{
					if(i+2>n)//到头了 
					{
						printf("%d %d %d ",i,1,i);
						printf("%d %d %d ",i+1,1,i+1);
					}
					else if(a[i+2]==b[i+2])//第三个相等的 
					{
						printf("%d %d %d ",i,1,i);
						printf("%d %d %d ",i+1,1,i+1);
					}
					else //第三个不相同 
					{
						if(a[i+1]==a[i+2])
						{
							printf("%d %d %d ",i+2,2,i+2);
							printf("%d %d %d ",i,1,i);
						}
						else 
						{
							printf("%d %d %d ",i+2,3,i+2);
						}
					}
					i++;
				}
			}
			else if((a[i]==b[i])+(a[i+1]==b[i+1])==1)
			{
				if(a[i]==b[i]) printf("%d %d %d ",i+1,1,i+1);
				else  printf("%d %d %d ",i,1,i); 
			}
		}
		puts("");
			continue;
		}
		printf("%d ",ans);
		if(a[1]!=b[1]) printf("1 ");
		for(int i=2;i<=n;i+=2)
		{
			if(i==n)
			{//如果扫到头了 
				if(a[i]!=b[i])
				{
					printf("%d %d %d ",i,1,i);
				}
				break;
			}
			if((a[i]==b[i])+(a[i+1]==b[i+1])==0)
			{//如果都不匹配 
				if(a[i]==a[i+1])//11->00 
				{
					printf("%d %d %d ",i+1,2,i+1);
				}
				else //如果是10->01 
				{
					if(i+2>n)//到头了 
					{
						printf("%d %d %d ",i,1,i);
						printf("%d %d %d ",i+1,1,i+1);
					}
					else if(a[i+2]==b[i+2])//第三个相等的 
					{
						printf("%d %d %d ",i,1,i);
						printf("%d %d %d ",i+1,1,i+1);
					}
					else //第三个不相同 
					{
						if(a[i+1]==a[i+2])
						{
							printf("%d %d %d ",i+2,2,i+2);
							printf("%d %d %d ",i,1,i);
						}
						else 
						{
							printf("%d %d %d ",i+2,3,i+2);
						}
					}
					i++;
				}
			}
			else if((a[i]==b[i])+(a[i+1]==b[i+1])==1)
			{
				if(a[i]==b[i]) printf("%d %d %d ",i+1,1,i+1);
				else  printf("%d %d %d ",i,1,i); 
			}
		}
		puts("");
	}
}
```

---

## 作者：hfctf0210 (赞：0)

可以发现这样的做法：每次找到最靠后的与b不同从串，然后通过旋转满足条件。但要判断a的第一位与该位是否相同，若相同，则需变换第1位使得其满足翻转后与该位相同，操作数2*n。至于翻转操作，打标记即可
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
int n,k,t,a[N],b[N],c[N];
char sa[N],sb[N];
void solve(int l,int r)
{
	if(l==r){if((a[l]^t)!=b[1])c[++k]=1;return;}
	int now=r,m=abs(r-l)+1,dir=l<r?-1:1,tmp=m;
	while(now-dir!=l&&(a[now]^t)==b[tmp])now+=dir,tmp--;
	if(now-dir==l)return;
	if(now==l){c[++k]=1;return;}
	if((a[l]^t)==b[tmp])c[++k]=1,a[l]^=1;
	t^=1,c[++k]=abs(l-now)+1;
	solve(now,l-dir);
}
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s%s",&n,sa+1,sb+1);
		k=t=0;
		for(int i=1;i<=n;i++)a[i]=sa[i]-'0',b[i]=sb[i]-'0';
		solve(1,n);
		printf("%d",k);for(int i=1;i<=k;i++)printf(" %d",c[i]);
		puts("");
	}
}
```


---

## 作者：do_while_true (赞：0)

考虑把两个字符看成一段 $0$ 和一段 $1$ 的形式。

每次把前面一段 $0$ 都修改为0，这个时候与后面紧跟着的 $1$ 组成了一段前缀 $1$ 再修改前缀 $1$ ，再修改 前缀 $0$ ...

可以在最多 $n$ 次操作下把一个长度为 $n$ 的序列修改为全部的 $0$。

现在是全 $0$，那么我们对应的也可以用相似的方法把后面的 $0$ 修改成一段段 $1$ 来修改为第二个串。

这些操作的最坏情况下也是修改 $n$ 次。

那么一共所有的操作是形如 $010101...$ 修改为 $101010...$ (反过来也同理)

模拟一下容易发现最多操作数为 $2n$。


[$\mathcal{Code}$](https://codeforces.com/contest/1382/submission/87592037)

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
inline int read()
{
	int r=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		r=(r<<3)+(r<<1)+(ch^48);
		ch=getchar();
	}
	return r*w;
}
int n,a[100011],b[100011],cnt,c[200010],f[100010],f2[100010];
int main()
{int T=read();while(T--){
	n=read();
	cnt=0;
	for(int i=1;i<=n+1;i++)
		f[i]=f2[i]=0;	
	for(int i=1;i<=n;i++) {
		scanf("%1d",&a[i]);
		f[i]=a[i]==1 ? f[i-1]+1 : 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%1d",&b[i]);
	for(int i=n;i>=1;i--)
		f2[i]=b[i]==1 ? f2[i+1]+1 : 0;
	for(int i=2;i<=n+1;i++)
		if(f[i]==0&&f[i-1]>0) {
			if(i-f[i-1]-1!=0) c[++cnt]=i-f[i-1]-1;
			c[++cnt]=i-1;
		}
	for(int i=n-1;i>=0;i--)
		if(f2[i]==0&&f2[i+1]>0) {
			c[++cnt]=i+f2[i+1];
			if(i!=0) c[++cnt]=i;
		}
	printf("%d ",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",c[i]);
	puts("");
}
return 0;
}
```

---

## 作者：Anita_Hailey (赞：0)

## 正文


一个构造题，考虑 hard 版本，他说了要不多于 2n 次。所以由于 cf 的惯例，我们一定可以两次搞出来一位，最多，于是考虑怎么 2 次出一位。

由于他给你的是前缀，所以我们考虑搞最后那一位，这样子之后的操作不会在影响它了。所以问题站变成了：考虑一个长度为n的串，按照题目的操作，要把它最后一位搞出来。


令 $h1$ 为初始串，$h2$ 为结果串。

分二种情况讨论

- 以第一次为例，这样的话，我们 $h1[1]$ 和 $h2[n]$ 要不一样才能进行一个 $n$ 翻转，那么事实上一样的话，如果我们先进行一个 $1$ 反转即可。

- 以第二次为例，我们要 $h1[n]$ 和 $h2[n-1]$ 一样才行，如果不一样的话，还是可以先进行 $1$ 反转，最后做一个 $n$ 反转即可。


那么，做好映射就很重要了，这里直接给出 了

假如之前的串是 abcdef 那么，我们最后的结果是 dcebfa, 不难观察出规律了。下边是代码，有兴趣可以看看
```cpp

namespace Solution
{
#define IOS std::ios::sync_with_stdio( false ), std::cin.tie( 0 ), std::cout.tie( 0 )
#define Rep( i, j, k ) for( int i = j; i >= k; --i )
#define rdi( ) read < int > ( )
#define rdl( ) read < long long > ( )
#define pti( i ) print < int > ( i ), putchar( '\n' )
#define ptl( i ) print < long long > ( i ), putchar( '\n' )
#define For( i, j, k ) for( int i = j; i <= k; ++i )
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::map;
	using std::queue;
	using std::deque;
	using std::set;
	using std::pair;
	const int Maxn = 204001;
	int t, n, s1[ Maxn ], s2[ Maxn ]; 
	inline char gck( )
	{
		char ch = gc( );
		while( ch == ' ' || ch == '\r' || ch == '\n' )
			ch = gc( );
		return ch;
	}
	void fakemain( )
	{
		t = rdi( );
		while( t-- )
		{
			n = rdi( );
			For( i, 1, n )
				s1[ i ] = gck( ) - '0';
			For( i, 1, n )
				s2[ i ] = gck( ) - '0';
			vector < int > ans;
			Rep( i, n, 1 )
			{
				int k = n - i;
				int a = s2[ i ];
				if( ( n - i ) & 1 )
				{
					int b = s1[ n - k / 2 ];
					if( b != a )
						ans.push_back( 1 );
					ans.push_back( i );
				}
				else
				{
					int b = s1[ k / 2 + 1 ];
					if( b == a )
						ans.push_back( 1 ); 
					ans.push_back( i );
				}
			}
			printf( "%d", ( int ) ans.size( ) ); 
			for( auto &to : ans )
				printf( " %d", to );
			pc( '\n' ); 
		}
		return;
	}

} // namespace Solution
```


---

## 作者：10circle (赞：0)

### 审题

有两个 $01$ 串 $a,b$，让你通过选择 $a$ 的一个前缀并将它取反并反转来将 $a$ 变成 $b$。最多可以操作 $2n$ 次。

### 分析

这个又取反又反转的操作实在是不好弄，但是我们可以先从前往后将 $a$ 的各位变成同一种，都是 $0$ 或 $1$，再从后往前将 $a$ 变成 $b$。这个方法就很好的解决了反转的问题，因为当前面都是同一种时，操作之后前面的顺序也不会变，又因为当 $a$ 的后面都与 $b$ 一样时，操作前面并不会打乱后面的顺序。具体实现请见代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int read(){
	int a=0,b=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')b=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a*b;
}
int a[1000005];
int b[1000005];
int ans[1000005];
int main(){
	int t=read();
	while(t--){
		int n=read(),k=1;
		for(int i=1;i<=n;i++)scanf("%1d",&a[i]);
		for(int i=1;i<=n;i++)scanf("%1d",&b[i]);
		bool fg=a[1];//fg代表在i前面的数字都是几
		for(int i=2;i<=n;i++){
			if(a[i]!=fg){
				ans[k]=i-1;k++;//将i-1之前的翻转，使之前的与a[i]一样 
				fg=a[i];
			}
		}
		for(int i=1;i<=n;i++)a[i]=fg;//把a数组全部赋值成fg 
		bool ag=a[n];
		for(int i=n;i>=1;i--){
			if(ag!=b[i]){//因为有个取反，所以要用一个ag来存储现在前面是0还是1 
				ans[k]=i,k++;
				ag=!ag;//现在前面已经被取反 
			}
		}
		cout<<k-1<<' ';
		for(int i=1;i<k;i++)cout<<ans[i]<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

