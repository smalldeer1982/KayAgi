# 「EZEC-6」0-1 Trie

## 题目背景

> $\mathbf{000111}$，这就是简单中所蕴含的优美。

众所周知，tlx 不会字符串。

## 题目描述

现在 tlx 有 $n$ 个 $\mathbf{1}$ 和 $m$ 个 $\mathbf{0}$，你需要把它们排列，但要保证任意的 $\mathbf{1}$ 互不相邻且第一个位置是 $\mathbf{0}$、最后一个位置是 $\mathbf{1}$，现在把所有可以构造出的串放到一棵 0-1 Trie 上，需要多少个节点？

**注意：节点计数时，不计算最开始的空节点，只计算代表“ $\mathbf{0}$ ”、“ $\mathbf{1}$ ”的节点。**  

**在本题中，我们认为用节点存储字符而非边， Trie 基本原理不变。**

因为答案可能很大而且询问较多，所以请在最后输出所有询问的答案对 $18888913$ （放心，是个质数）取模的结果的异或和（**异或和不再进行取模**）。

## 说明/提示

**【样例解释 #1】**

可以发现，所有能构造出的串有：  

$$\mathbf{000101}$$
$$\mathbf{001001}$$
$$\mathbf{010001}$$

构造 0-1 Trie，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/aql3bwo6.png)

共需 $15$ 个节点。


**【样例解释 #2】**

两次询问的答案分别为 $34$ 和 $4487317$。

------------

**【数据规模与提示】**

注意：本题采用**捆绑测试**，只有当你通过一个 Subtask 内的所有测试点后，你才能拿到这个 Subtask 的分数。

具体约束如下：  

Subtask $1$（$10\%$）：满足 $T\leq 10$，$n,m\leq 5$；

Subtask $2$（$20\%$）：满足 $T \leq 10$，$n,m\leq 1\times 10^3$；

Subtask $3$（$30\%$）：满足 $T\leq 10$，$n,m\leq 5\times 10^5$;


Subtask $4$（$40\%$）：无特殊限制。

对于 $100\%$ 的数据，满足 $1\le T \le 2\times10^6$，$1\le n,m\le 5\times 10^{18}$。

**本题输入量较大，建议采用较为快速的读入方式并注意常数因子对程序效率带来的影响。**



------------
 0-1 Trie 是一种特殊的 Trie ，只有 $\mathbf{0,1}$ 两种字符。
 
 如果你不了解 Trie，可以查看：[OI Wiki--Trie](https://deploy-preview-980--oi-wiki.netlify.app/string/trie/)。

## 样例 #1

### 输入

```
1
2 4```

### 输出

```
15```

## 样例 #2

### 输入

```
2
3 5
114514 1919810```

### 输出

```
4487351
```

## 样例 #3

### 输入

```
5
78 122
1000000 1000001
74859432 942432534
555555555 77777777 
6666666666 8888888888```

### 输出

```
12287990```

# 题解

## 作者：yyandy (赞：15)

[「EZEC-6」0-1 Trie](https://www.luogu.com.cn/problem/P7386)

现在 tlx 有 $n$ 个 $\mathbf{1}$ 和 $m$ 个 $\mathbf{0}$，你需要把它们排列，但要保证任意的 $\mathbf{1}$ 互不相邻且第一个位置是 $\mathbf{0}$、最后一个位置是 $\mathbf{1}$，现在把所有可以构造出的串放到一棵 0-1 Trie 上，需要多少个节点？

**注意：节点计数时，不计算最开始的空节点，只计算代表“ $\mathbf{0}$ ”、“ $\mathbf{1}$ ”的节点。**  

------------

$T\le 2\times 10^6,n,m\le 5\times 10^{18}$

一道有一定难度的题，大概想了一个小时（还是太菜了

个人的做法比较愚笨复杂，其他题解可能有更加优秀的解法。

保证任意两个 $1$ 互不相邻这个条件比较阴间，尝试将一个 $1$ 强制与一个 $0$ 捆绑起来，形成 $01$。

设 $F_{x,y}$ 为有 $x$ 个连续的 $01$，$y$ 个单独的 $0$ 的字典树节点数。

考虑这个字典树根节点的左右子树，如图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/2qmfbvwz.png)

图中用红色圈起的是有 $x$ 个连续的 $01$，$y$ 个单独的 $0$ 的字典树。

它的左儿子这边，也就是绿色圈起的，是去掉一个 $01$ 以后的字典树。

而右儿子这边，是去掉一个 $0$ 之后的字典树。

整个红圈里的字典树就相当于绿圈里的加上蓝圈里的再加上两个节点。

于是可以得到 $F_{x,y}=F_{x-1,y}+F_{x,y-1}+2,(x>1,y \ge 1) $ 的递推关系。

其中边界条件为 $F_{1,y}=y+2,F_{x,0}=2x$。

因为此时所有的节点形成了一条链，节点数就是链长。

（$F_{1,y}=y$ 是因为题目里写了最后一个位置是 $1$，所以至少有一个连续的 $01$）。

然后整个 $F$ 大概是这样的：

```
 列0  列1 列2 列3  列4
1: 2   3   4   5   6 
2: 4   9  15  22  30
3: 6  17  34  58  90
4: 8  27  63 123 215
```

除了第一行，都满足 $F_{x,y}=F_{x-1,y}+F_{x,y-1}+2$。

这样，我们总能够将 $F_{n,m}$ 表示为 $\sum k_j \times F_{1,j} + k_0\times 2$ 这样的形式。

对于 $n>1$， $k_j$ 的系数相当于在网格图中从 $(2,j)$ 走到 $(n,m)$ 路径数（只能向右或者向下）。

$k_j=\binom{n+m-j-2}{n-2}$。

而接下来要解决的就是 $k_0$ 的问题了。

这个 $k_0$ 相当于从 $\forall i\ge 2,j\ge 0$  $(i,j)$ 到 $(n,m)$ 的路径数量之和。

$k_0=\sum_{i=2}^n\sum_{j=0}^m \binom{n+m-i-j}{n-i}$

根据上指标求和的式子，可以得到

$k_0=\sum_{i=2}^n \binom{n+m-i+1}{n-i+1}=\sum_{i=2}^n\binom{n+m-i+1}{m}=(\sum_{i=2}^{n+1}\binom{n+m-i+1}{m})-1$

再用一次上指标求和，得到

$k_0=\binom{n+m}{m+1}-1$

加上前面的这些式子，暴力求是单次 $O(m)$ 的。

回来解决前面的这些式子。

$\sum_{j=0}^mk_j\times F_{1,j}=\sum_{j=0}^m(j+2)\times \binom{n+m-j-2}{n-2}$

$=\sum_{j=0}^m (m-j+2)\times \binom{n+j-2}{n-2}$

$=\sum_{j=0}^m (\sum_{k=1}^{m-j+1} \binom{n+j-2}{n-2})+\binom{n+j-2}{n-2}$ 改变一下循环的顺序，把外面的 $\binom{n+j-2}{n-2}$这一坨上指标求和。

$=(\sum_{k=1}^{m+1}\sum_{j=0}^{k-1 }\binom{n+j-2}{n-2})+\binom{n+m-1}{n-1}$ 上指标求和。

$=(\sum_{k=1}^{m+1}\binom{n+k-2}{n-1})+\binom{n+m-1}{n-1}$ 再次上指标求和。

$=\binom{n+m}{n}+\binom{n+m-1}{n-1}$

将式子整理一下

得到总的式子：

$F_{n,m}=\binom{n+m}{n}+\binom{n+m-1}{n-1}+2\times \binom{n+m}{m+1}-2$

已经可以求值了，不过如果你要精益求精的话，还可以继续化简，这一步不难（~~读者自证~~

最终式子为 $2\times \binom{n+m+1}{n}-\binom{n+m-1}{n}-2$，这样就可以只求两次组合数了。

---

## 作者：hanzhongtlx (赞：12)

这里是 0-1 Trie 官方题解。

这是一个没有 OI 思维的菜鸡的思路，您可能感觉他吃多了，希望轻喷 qwq。

个人感觉这个题的感觉需要一些画图理解，由于电脑上不好施展，这个艰巨的任务就得由各位做题的巨佬来实现了。   

我感觉这个做法更好：[神仙 @SOSCHINA 的题解](https://www.luogu.com.cn/paste/oxt9jmql)。

还有一种做法：[神仙 zmx_wzx_JY 的题解](https://www.luogu.com.cn/paste/kii3datm)

#### 为了方便，我们记有 $n$ 个 $\mathbf{1}$ 和 $n+m$ $\mathbf{0}$ 且认为两者同阶。

### **Step 1** 寻找合理的转化  

首先直接枚举是不行的，大概有 $10$ 分的样子，而且挺难写的。

我们可以理解成从有唯一构造方案的 $m=0$ 开始， $m$ 的增加代表着对每一种情况插入 $0$，那么，插入的 $0$ 的数量增加 $1$ ，树的节点数的增量 $\Delta$ 是如何变化的呢?    

可以发现 $\Delta$ 可以形式地表示为： 

$$(\sum x_i)+y-z$$  

这是什么玩意？我们慢慢来讲。   

容易发现一个性质，在 Trie 树上插入 $0$ 的时候，我们假设钦定在 $a-b$ 之间建设插入点，这个插入点如果合法，那他下边一定没有分支。  

这时候我们想到记录每一个和向下与 $1$ 接壤的 $0$ 节点 $i$ 的下面还有 $x_i$ 个节点，那么在这个位置插入得到的增量是 $x_i+1$。  

怎么理解呢？我们可以理解成在这个位置先复制一条链，递归地向下插入，然后同时在他下面建一条新链，同时在他和它下面的 $1$ 中间插入一个 $0$，一次增量是 $x_i+1$。  

但是有一个特殊点，就是处于末位位置的插入点，这时候不需要再递归下去了，而且他下面只有一个节点 $1$，于是，需要减掉。  

那么 $\Delta=(\sum x_i)+y-z$ 的含义也就十分明了了， $\sum x_i$ 不必多说，$y$ 代表插入可行的位置数， $z$ 代表叶节点的个数。

### **Step 2** 将增量数字化  

由于前面提到的性质：  

> 在 Trie 树上插入 $0$ 的时候，我们假设钦定在 $0-1$ 之间建设插入点，这个插入点如果合法，那他下边一定没有分支。  

我们其实容易归纳得到推论：  

> 对于一条链，如果他有 $y$ 个可以插入的点，那么这条链上的 $\sum x_i=y^2$（实质上是对 $2i-1$ 求和）。   

这是一个关键点，现在，我们只需要解决每一条链上有多少可以插入的点。  

我们模拟一下插入的过程，会发现一个比较显然的性质：  

> 对于一条有 $y$ 个插入点的链，插入后形成 $y$ 条新链，可插入的点分别为 $1,2......y$。   

其实我们可以看做是一个长为 $n$ 的数组 $a_i$，开始只有 $a_n=1$，每次插入操作等同于将每个数组加上下标大于它的数组的和，再进行计算。

有经验的巨佬一定知道这是一个经典的组合数学的问题，具体的式子我们一会再讨论。  

$z$ 的求法比较显然，其实就是问有多少种构造方案，是一个插板法的问题。  

容易发现，$m$ 次插入操作，减去的 $z$ 的和为：  

$$\sum_{i=0}^{m-1}\dbinom{n+i-1}{n-1}=\dbinom{n+m-1}{n}$$    

同样我们将 $(\sum x_i)+y$ 的和表示一下：  

我们为了方便，将第二次插入操作编号为 $0$，然后加上第一次操作的增量。  
$$\sum\left((\sum x_i)+y\right)=\sum_{i=0}^{m-2}\sum_{j=1}^n (j^2+j)\dbinom{n-j+i}{i}+n^2+n$$

到了这里，我们直接依式子模拟即可，时间复杂度 $\mathcal O(Tn^2)$，期望得分 $30$ 分。

ps：这三个性质的寻找大概是本题最难的地方了，我发现神仙 fyy 给出了一种很神仙的 dp（虽然暂时拿不到满分），貌似避过了这个阴间的问题，我似乎感觉我又做麻烦了。

ps：fyy 神仙已经用另类的方式（不过貌似我的方法更另类）推出并通过了此题，我只能膜拜 Orz。

ps：这个 dp 可能挺套路的，不过我做题比较少，没有想到，似乎把这道题质量给拉下来了？

### **Step 3** 推式子  

我们对 $\sum\left((\sum x_i)+y\right)$ 中比较繁琐的那一部分进行化简，首先交换求和符号：  

$$\sum_{j=1}^n(j^2+j)\sum_{i=0}^{m-2}\dbinom{n-j+i}{n-j}$$  

运用一下经典的组合求和恒等式：  

$$\sum_{j=1}^n(j^2+j)\dbinom{n+m-j-1}{n-j+1}$$   

以上的推导十分 naive，且比较套路，但是我们可以做到 $\mathcal O(Tn)$，期望得分 $60$ 分。

我们考虑一下：$j^2+j=2\dbinom{j+1}{2}$，于是：  

$$2\sum_{j=1}^n \dbinom{j+1}{2}\dbinom{n+m-j-1}{m-2}$$


这像极了范德蒙德卷积: 

$$\dbinom{n+m}{k}=\sum_{i=0}^k\dbinom{n}{i}\dbinom{m}{k-i}$$  

我们从组合意义上理解应该颇为简单，同理我们在组合意义上来说：  

$$\dbinom{k+1}{n+m+1}=\sum_{i\ge n\&k-i\ge m}\dbinom{i}n{}\dbinom{k-i}{m}$$  

因此，我们对答案进行化简，一定要注意枚举的范围：  

$$\text{原式}=2\left(\dbinom{n+m+1}{m+1}-\dbinom{n+2}{2}\dbinom{m-2}{m-2}\right)$$  

我们展开一下，并加上第一轮的增量，得到的式子为：  

$$2\dbinom{n+m+1}{n}-2n-2$$   

我们将 $\sum z$ 减去，然后别忘了初始的大小为 $2n$，得到答案：  

$$2\dbinom{n+m+1}{n}-\dbinom{n+m-1}{n}-2$$  

### **Step 4** 代码实现   

这个模数比较小，只有不到 $2e7$，我们线性处理逆元和阶乘，组合数的计算直接 Lucas 即可，这个地方的组合数计算不会超过 $3$ 次，几乎可以认为是线性。

当然我们要注意**在本题题意中**若 $n>m$ 无解则需要特判。

复杂度是 $\mathcal O(18888913+T\log n)$，注意一下常数即可获得 $100$ 分。

由于进行了一定程度上的卡常，导致 std 比较难看...

```cpp
#include"iostream"
#include"cstdio"
using namespace std;

#define ll long long
#define MOD 18888913
#define MAXN 19000005
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)

int t,rt=0;
ll n,m;
int fac[MAXN],inv[MAXN];
char buf[1<<21],*p1=buf,*p2=buf;

inline ll read()
{
	ll x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c<='9'&&c>='0') x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}

inline int Lucas(ll n,ll m)
{
	int ans=1;
	for(register int x,y;m&&ans;)
	{
		x=n%MOD,y=m%MOD;
		ans=x<y?0:1ll*ans*fac[x]%MOD*inv[fac[y]]%MOD*inv[fac[x-y]]%MOD;
		n/=MOD,m/=MOD;
	}
	return ans%MOD;
}

int main()
{
	inv[1]=1,fac[0]=fac[1]=1;
	for(register int i=2;i<MOD;i++) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD,fac[i]=1ll*fac[i-1]*i%MOD;
	scanf("%d",&t);
	for(register int i=1;i<=t;i++)
	{
		n=read(),m=read();
		if(n>m) continue;
		rt^=((Lucas(m+1ll,n)*2-Lucas(m-1ll,n)-2+MOD+MOD)%MOD); 
	}
	printf("%d\n",rt);
	return 0;
}
```

------------

### **extra** 一些彩蛋

我作为一不务正业的 whk 人，学考的考场上匆忙做完题，来推这个题，大概是一场物理和一场政治的功夫，我得到了这道题的 $\mathcal O(Tn)$ 的做法，那天回家大概是给了一种错误的  $\mathcal O(T\log n)$ 的解法，晚上随便举了个例子就错了。

当时因为乱套范德蒙德卷积，第二天发现类比的方法时大概激动得不行，所以就翘了几节网课把这道题贡献了一下。

对，那几个性质我也不知道我怎么发现的，就感觉十分神奇，果然，这并不是唯一的突破方式。

---

## 作者：dengyaotriangle (赞：7)

来讲讲怎么拿生成函数无脑推出此题。（别看过程这么长，其实除了求出递推式这一步其它部分在熟悉了基本生成函数的结论之后都是机械化的大力推式子，所以是无脑的）

首先先搞一个递推式，令 $f(n,m)$ 代表 $n$ 个 $1$，$m$ 个 $0$ 所需的 Trie 大小。

很显然地，$f(1,m)=m+1$

而对于 $n>1$，发现可以枚举这个字符串开始的连续的 0 的长度。所以有

$$f(n,m)=\sum_{j=n-1}^{m-1} (f(n-1,j)+2)$$ 

画成图是这样的，非常显然：
![](https://cdn.luogu.com.cn/upload/image_hosting/qce6tbtl.png)

那么我们就是要求这个东西的通项，怎么求？

**前置知识：数列的简单普通生成函数。**

我们观察到转移是从 $f(n-1,\cdots)\to f(n,\cdots)$ 的，不妨把每一行的所有 $f(n,m)$ 挂到生成函数上去，也就是设 $F_n(x)=\sum_{i} x^i f(n,i)$

那么 $F_1(x)=2x+3x^2+4x^3+\cdots$，其闭形式有很多推法，其中一种是观察到  
$$F_1(x)=2x+3x^2+4x^3+\cdots=\frac{\mathrm{d}}{\mathrm{d}x}(x^2+x^3+\cdots)$$

而众所周知 $1+x+x^2+\cdots=\frac1{1-x}$ ，那么 $F_1(x)=\frac{\mathrm{d}}{\mathrm{d}x}\frac{x^2}{1-x}=\frac{x(2-x)}{(1-x)^2}$

接下来考虑 $F_{n}(x)$ 与 $F_{n-1}(x)$ 的关系。观察上面的递推式，发现，$f(n,m)$ 就是一个 $f(n-1,m)$ 的前缀和的形式，而[我们知道](https://www.luogu.com.cn/problem/P5488)，一个生成函数与 $\frac1{1-x}$ 相乘就相当于其做前缀和。

所以 $F_{n-1}(x)$ 到 $F_n(x)$ 无非就三步：

1. 将 $F_{n-1}(x)$ 的 $x^m$ 项（$m\geq n-1$）全加上 $2$，这个是 $F_{n-1}(x)+\frac{2x^{n-1}}{1-x}$
2. 将 $F_{n-1}(x)$ 做前缀和，做完是 $\left(F_{n-1}(x)+\frac{2x^{n-1}}{1-x}\right)\frac1{1-x}$
3. 把 $F_{n-1}(x)$ 向上平移一项，因为观察到递推式中前缀和是从前一项开始的，最后得到 $F_{n}(x)=\left(F_{n-1}(x)+\frac{2x^{n-1}}{1-x}\right)\frac{x}{1-x}$

最后得到 $F_1(x)=\frac{x(2-x)}{(1-x)^2}$，
$$F_{n}(x)=\left(F_{n-1}(x)+\frac{2x^{n-1}}{1-x}\right)\frac{x}{1-x}$$

接下来就是高中数列内容了，我们把 $F_n(x)$ 看成一个数列，解其通项公式。

首先看到递推式中有 $x^{n-1}$ ，与 $n$ 相关，将其消去，具体来讲，递推式式两边同时除以 $x^n$
$$\frac{F_{n}(x)}{x^n}=\left(\frac{F_{n-1}(x)}{x^{n-1}}+\frac{2}{1-x}\right)\frac1{1-x}$$

那么现在，设  $G_n(x)=F_n(x)/x^n$，就是


$$G_n(x)=\left(G_{n-1}(x)+\frac{2}{1-x}\right)\frac1{1-x}$$

然后转化成，

$$G_n(x)+\frac2{x(1-x)}=\left(G_{n-1}(x)+\frac2{x(1-x)}\right)\frac1{1-x}$$

$$G_n(x)+\frac2{x(1-x)}=\left(G_{1}(x)+\frac2{x(1-x)}\right)\frac1{(1-x)^{n-1}}$$

代入 $G_1(x)=F_1(x)/x=\frac{(2-x)}{(1-x)^2}$
$$G_n(x)+\frac2{x(1-x)}=\left(\frac{(2-x)}{(1-x)^2}+\frac2{x(1-x)}\right)\frac1{(1-x)^{n-1}}$$

化简，得

$$G_n(x)=\frac{2-x^2}{x(1-x)^{n+1}}-\frac2{x(1-x)}$$
$$F_n(x)=x^nG_n(x)=x^{n-1}\left(\frac{2-x^2}{(1-x)^{n+1}}-\frac2{(1-x)}\right)$$

那么，
$$f(n,m)=[x^m]F_n(x)=[x^{m-(n-1)}]\left(\frac{2-x^2}{(1-x)^{n+1}}-\frac2{(1-x)}\right)$$

我们知道 
$$(1-x)^{-n-1}=\sum_{i}x^i(-1)^i\binom{-n-1}{i}=\sum_{i}x^i(-1)^i\frac{(-n-1)^{\underline{i}}}{i!}=\sum_{i}x^i\frac{(n+i)^{\underline{i}}}{i!}$$


$$(1-x)^{-n-1}=\sum_{i}x^i\binom{n+i}{i}$$

所以说，

$$\begin{aligned}f(n,m)=&[x^{m-(n-1)}]\left(\frac{2-x^2}{(1-x)^{n+1}}-\frac2{(1-x)}\right)\\


=&[x^{m-(n-1)}]\left((2-x^2)\sum_{i}x^i\binom{n+i}{i}\right)-[x^{m-(n-1)}](2(1+x+x^2+\cdots))\\

=&2[x^{m-(n-1)}]\sum_{i}x^i\binom{n+i}{i}-[x^{m-(n-1)-2}]\sum_{i}x^i\binom{n+i}{i}-2[m-(n-1)\geq 0]\\

=&2\binom{n+m-n+1}{m-n+1}-\binom{n+m-n-1}{m-n-1}-2[m-(n-1)\geq 0]\\

=&2\binom{m+1}{n}-\binom{m-1}{n}-2[m-(n-1)\geq 0]
\end{aligned}$$

于是就是lucas一下就好了。

另外，有一个结论是 $(p-1)!\equiv -1 \pmod{p}$，就不用求逆元了。

```cpp
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

const int mdn=18888913;
int fac[mdn],ifac[mdn];

int solve(long long n,long long m){
    if(m>n)return 0;
    if(n<mdn)return fac[n]*(long long)ifac[m]%mdn*ifac[n-m]%mdn;
    return solve(n%mdn,m%mdn)*(long long)solve(n/mdn,m/mdn)%mdn;
}
int main(){
    fac[0]=1;for(int i=1;i<mdn;i++)fac[i]=fac[i-1]*(long long)i%mdn;
    ifac[mdn-1]=mdn-1;//(p-1)! = -1 (mod p)
    for(int i=mdn-1;i>0;i--)ifac[i-1]=ifac[i]*(long long)i%mdn;
    int t;qio>>t;
    int cans=0;
    while(t--){
        long long n,m;
        qio>>n>>m;
        int ans=0;
        if(m>=n){
            ans=(2ll*solve(m+1,n)+mdn-solve(m-1,n)+mdn-2)%mdn;
        }
        cans^=ans;
    }
    qio<<cans<<'\n';
    return 0;
}
```

---

## 作者：zjjws (赞：5)

真的是高质量好题啊，让我这种组合数学不好的蒟蒻得到了锻炼。

我的做法比较生草：

考虑三个限制条件：

- 第一位必须是 $0$。

- 不能有 $1$ 相邻。

- 最后一位必须是 $1$。

先强制钦定每个 $1$ 前面有一个 $0$，将它们捆绑在一起。那么我们现在有了 $n$ 个 $01$ 和 $m-n$ 个 $0$。

此时无论怎么组合，前面两个条件就已经满足了。

以下我们称 **含有 $n$ 个 $01$ 和 $m$ 个 $0$ 的集合** 内部元素 **通过排列组合得到的所有方案放到 trie 树上后的节点个数** 为该集合的 **贡献**。

设 $f_{n,m}$ 表示含有 $n$ 个 $01$ 和 $m$ 个 $0$ 的集合的 **贡献**。

首先有很明显的边界：

$$\left\{\begin{matrix} f_{n,0}=2n \\ f_{1,m}=m+2 \end{matrix}\right.$$

同时 $f_{0,m},m>0$ 无定义，因为不满足第三条限制。

以及递推式：$f_{n,m}=f_{n-1,m}+f_{n,m-1}+2,n>1,m>0$。

那么我们现在就得到了 $f$ 的一些值（下标从零开始）：

$$
\begin{matrix}
 0 & \times & \times & \times\\
 2 & 3 & 4 &5 \\
 4 & 9 & 15 & \cdots\\
 6 & 17 & 34 & \cdots
\end{matrix}
$$

为了方便，以下用 $(x,y)$ 对应 $f$ 的二维矩阵中第 $x$ 行第 $y$ 列的元素。

考虑那个转移，实质上是：将一个要求的元素 $(x,y)$ 分裂成向上和向左的两个元素 $(x-1,y)$ 和 $(x,y-1)$，以及产生一个常数项贡献 $2$。

特殊的，第 $1$ 行和第 $0$ 列 **在定义中** 不能分裂。

不断进行上述过程，会得到若干个 $(1,i),i\in[1,m]$ 和 $(j,0),j\in[2,n]$ 这样的元素。

比较 Simple 的想法就是，直接枚举每个边界元素，计算其贡献，对于常数项系数 $2$，其贡献发生在每一次分裂的过程中。而每次分裂会使得个数 $+1$，那么就可以用总个数 $sum$ 减 $1$（一开始的一个元素 $(n,m)$），来获得 $2$ 做贡献的次数。

这样就有 $60$ 分的好成绩。

考虑到我们不能将贡献压缩到常数个点上的原因，就是这个边界上不能转移。

接下来，我们 **强制** 其转移，也就是将边界各往上往左扩展一格。为了符合转移式，第 $0$ 行的元素 $(0,i),i>0$ 全部设为 $-1$，第 $-1$ 列的元素全部设为 $0$。然后我们就可以强制把上一步中 $(1,i),i\in (1,m]$ 的所有点往 $(1,1)$ 转移，同时过程中会产生若干个值为 $-1$ 的元素。对于另一边也是一样的做法，可以将所有的贡献集中到 $(2,0)$ 这个元素上面。

然后对于 $0$ 和 $-1$ 的个数计算，都是形如 $\sum_{i=0}^r \binom{n}{i}$ 的形式，可以直接将其写为 $\binom{n+r+1}{r}$。

那么这里就可以 $\operatorname O(1)$ 求得，卢卡斯求组合数最多递归三层，所以是常数级别的（确信）。

以下包含了 $30/60/100$ 的代码（前两部分注释掉了）

```cpp
#include <stdio.h>
#define LL long long
using namespace std;
const int Rea=1e5+3;
struct Rin
{
    char c;
    inline char gc()
    {
        static char rea[Rea];
        static char *head,*tail;
        return head==tail&&(tail=(head=rea)+fread(rea,1,Rea,stdin),head==tail)?EOF:*head++;
    }
    inline Rin&operator >>(LL &x)
    {
        x=0;
        bool tag=false;
        for(c=gc();c>'9'||c<'0';c=gc())if(c=='-'){c=gc();tag=true;break;}
        for(;c>='0'&&c<='9';c=gc())x=(x<<1)+(x<<3)+(c^'0');
        if(tag)x=-x;
        return *this;
    }
    inline Rin&operator >>(int &x)
    {
        x=0;
        bool tag=false;
        for(c=gc();c>'9'||c<'0';c=gc())if(c=='-'){c=gc();tag=true;break;}
        for(;c>='0'&&c<='9';c=gc())x=(x<<1)+(x<<3)+(c^'0');
        if(tag)x=-x;
        return *this;
    }
}rin;

/* const int M=1e3+3;
const int M=18888913;
int f[M][M];
inline int dfs(int n,int m)
{
    if(n<0||m<0)return 0;
    if(m==0)return (n<<1)%M;
    if(f[n][m])return f[n][m];
    if(n>1)f[n][m]+=2+dfs(n-1,m);
    if(m)f[n][m]+=1+dfs(n,m-1)-(n>1);
    f[n][m]%=M;
    return f[n][m];
} */

const int M=18888913;
int sl[M];
int sr[M];
inline int prpr(int x,int y){return 1LL*x*y%M;}
inline int ksm(int x,int y){int ans=1;for(;y;y>>=1){if(y&1)ans=prpr(ans,x);x=prpr(x,x);}return ans;}
inline int C(LL a,LL b)
{
    if(a<b)return 0;
    if(a<M)return prpr(sl[a],prpr(sr[b],sr[a-b]));
    return prpr(C(a/M,b/M),C(a%M,b%M));
}
inline int work()
{
    // int n=rin(),m=rin();return dfs(n,m-n);
    LL n,m;
    rin>>n>>m;
    if(n>m)return 0;m-=n;
    if(n==1)return (m+2)%M;
    if(m==0)return (n<<1)%M;
    int ans=0;
    int sum=0;
    // for(int i=1;i<=m;i++)ans=(ans+prpr(i+2,C(n-2+m-i,n-2)))%M,sum=(sum+C(n-2+m-i,n-2))%M;
    // for(int i=2;i<=n;i++)ans=(ans+prpr(i<<1,C(n-i+m-1,m-1)))%M,sum=(sum+C(n-i+m-1,m-1))%M;
    // ans=(ans+prpr(sum-1,2))%M;
    ans=C(n-1+m-1,m-1)*3+((C(n-2+m,m))<<2);
    ans+=C(n+m-2,m-2);
    sum+=C(m+n-2,n-3);
    sum+=C(n-1+m-1,m-1);
    sum+=C(n+m-2,m);
    ans+=(sum-1<<1);
    return (ans%M+M)%M;
}
int main()
{
    int ans=0;
    /* for(int i=1;i<M;i++)f[i][0]=i<<1;
    for(int i=1;i<M;i++)f[1][i]=i+2;
    for(int i=2;i<M;i++)for(int j=1;j<M;j++)f[i][j]=(f[i-1][j]+f[i][j-1]+2)%M; */
    sl[0]=sr[0]=1;
    for(int i=1;i<M;i++)sl[i]=prpr(sl[i-1],i);
    sr[M-1]=ksm(sl[M-1],M-2);for(int i=M-2;i>=1;i--)sr[i]=prpr(sr[i+1],i+1);
    int T;
    for(rin>>T;T;T--)ans^=work();
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Mivik (赞：2)

[欢迎到我的博客查看](https://mivik.gitee.io/2021/solution/ezec-01-trie/)

第一次让我感到屈辱的推式...

有个显然的观察，答案等于 $(n+m)$ 乘上合法串的个数，再减去所有串按字典序排序后相邻两个的 $LCP$。如果你走 dp 那你就会沦为和我给同学做题时一样的心理崩溃，于是我们考虑组合。

不难发现由于我们按字典序排序，每种 $LCP$ 只会被计算一次。我们只需要考虑哪些 $LCP$ 是合法的并把它们的长度加起来即可。首先不难发现 $n$ 个 $1$ $m$ 个 $0$ 形成题目中要求串的方案是 $\binom{m-1}{n-1}$（隔板法），然后能形成合法串的充要条件显然是 $n\le m$。

于是我们开始枚举 $LCP$ 长度，再枚举其中有多少个 $1$。不难注意到相邻的两个字符串必然是这样的形式：
$$
\begin{aligned}
\text{枚举的前缀}+\underline 0\cdots\\
\text{枚举的前缀}+\underline 1\cdots
\end{aligned}
$$
否则 $LCP$ 就可以更长。于是 $LCP$ 末尾必然是 $0$。然后考虑上面合法串的充要条件，假设 $LCP$ 长度为 $i$ 且有 $j$ 个 $1$，我们得到下面的条件：
$$
\begin{aligned}
i-j&\ge j+1\\
(n+m-i)-(n-j)&\ge n-j\\
(n+m-i-1)-(n-j-1)&\ge n-j-1
\end{aligned}
$$
即 $2j+1\le i\le m-n+2j$。由于除去 $LCP$ 后面的部分至少有两个 $1$（如果只有一个 $1$，也就是 $i=n-m+1$，则上面列出的第一个字符串不合法）所以 $j$ 最大为 $n-2$。，于是我们得到相邻 $LCP$ 长度的和应为：
$$
\sum_{j=0}^{n-2}\sum_{i=2j+1}^{m-n+2j}i\binom{i-j-1}j
$$
于是开始无脑推式子。
$$
\begin{aligned}
&=\sum_{j=0}^{n-2}\left(\left(\sum_{i=2j+1}^{m-n+2j}(i-j)\binom{i-j-1}j\right)+j\sum_{i=2j+1}^{m-n+2j}\binom{i-j-1}j\right)\\
&=\sum_{j=0}^{n-2}\left(\left(\sum_{i=2j+1}^{m-n+2j}(j+1)\binom{i-j}{j+1}\right)+j\binom{m-n+j}{j+1}\right)\\
&=\sum_{j=0}^{n-2}(j+1)\binom{m-n+j+1}{j+2}+j\binom{m-n+j}{j+1}\\
&=(n-1)\binom{m-1}n+2\sum_{j=1}^{n-2}j\binom{m-n+j}{j+1}
\end{aligned}
$$
梅 开 二 度

把右边那个东西拿过来
$$
\begin{aligned}
&\sum_{j=0}^{n-2}j\binom{m-n+j}{j+1}\\
=&\left(\sum_{j=0}^{n-2}(m-n+j+1)\binom{m-n+j}{m-n-1}\right)-(m-n+1)\sum_{j=0}^{n-2}\binom{m-n+j}{m-n-1}\\
=&\left(\sum_{j=0}^{n-2}(m-n)\binom{m-n+j+1}{m-n}\right)-(m-n+1)\left(\binom{m-1}{m-n}-1\right)\\
=&(m-n)\left(\binom m{m-n+1}-1\right)-(m-n+1)\left(\binom{m-1}{m-n}-1\right)\\
=&(m-n)\binom m{m-n+1}-(m-n+1)\binom{m-1}{m-n}+1
\end{aligned}
$$
综合一下我们得到
$$
\begin{aligned}
Ans=&(n+m)\binom{m-1}{n-1}-(n-1)\binom{m-1}{n}-\\
&2(m-n)\binom m{m-n+1}+2(m-n+1)\binom{m-1}{m-n}-2
\end{aligned}
$$
已经可以 $O(1)$ 求了，但为什么你的式子那么丑啊！！！！

出于莫名奇妙的执着，我们化简一下
$$
\begin{aligned}
Ans=&(3m-n+2)\binom{m-1}{n-1}-(n-1)\binom{m-1}{n}-\\
&2(m-n)\binom m{n-1}-2\\
=&2\binom m{n-1}+\binom{m-1}n+2\binom{m-1}{n-1}-2\\
=&\binom{m-1}{n-1}+\binom m{n-1}+\binom{m+1}n-2\\
=&2\binom{m+1}n-\binom{m-1}n-2
\end{aligned}
$$
代码只有 Lucas，想必不用贴了。

/ Peace Out /

---

## 作者：Thinking (赞：2)

注意：本题解中的 $n,m$ 与题目定义相反。

首先考虑前30%。

考虑 DP。记 $f_{n,m}$ 为当有 $n$ 个 0，$m$ 个 1 时，题目所求的结点个数，那么显然有 $f_{n,1}=n+1,f_{n,n}=2n$。

同时，当 $n<m$ 时，方案不存在，$f_{n,m}=0$。

接下来考虑一般的 $f_{n,m}$。

注意到，对于序列的第二位，如果这一位为 0，则以这个结点为根的子树相当于 $n-1,m$ 对应的 0-1 Trie，结点数为 $f_{n-1,m}$；如果这一位为 1，则第三位必须为 0，从第三位开始的子树相当于 $n-1,m-1$ 对应的 0-1 Trie，结点数为 $f_{n-1,m-1}$。因此，我们得到 $f_{n,m}=f_{n-1,m}+(f_{n-1,m-1}+1)+1$。

注意到这个方程有明显的类似组合数的形式 ~~（其实题目的模数和范围就在明示Lucas了）~~，记 $f'_{n,m}=f_{n,m}+2$，则有 $f'_{n,m}=f'_{n-1,m-1}+f'_{n-1,m}$。

先给 $f'$ 打个表：

```
4
5 6
6 11 8
7 17 19 10
8 24 36 29 12
```

~~好像规律不是很显然？~~

考虑全部减去 $\binom{n-1}{m-2}$，有：

```
4
5 5
6 10 6
7 16 16 7
8 23 32 23 8
```

这样就变成了对称的。接下来再减去 $\binom{n+1}{m}$，有：

```
2
2 2
2 4 2
2 6 6 2
2 8 12 8 2
```

那么规律就非常显然了。

综上，$f_{n,m}=\binom{n-1}{m-2}+\binom{n+1}{m}+2\binom{n-1}{m-1}-2$，用 Lucas 定理计算即可。

```cpp
#include<cstdio>
#include<cctype>
typedef long long ll;
const int mod=18888913;
const int BUF=1<<23;
char rB[BUF],*rS,*rT;
inline char gc(){return rS==rT&&(rT=(rS=rB)+fread(rB,1,BUF,stdin),rS==rT)?EOF:*rS++;}
inline ll rd(){
    char c=gc();
    while(!isdigit(c))c=gc();
    ll x=c&15;
    for(c=gc();isdigit(c);c=gc())x=x*10+(c&15);
    return x;
}
int f[mod],g[mod];
void exgcd(int a,int b,int &x,int &y){
	if(b){
		exgcd(b,a%b,y,x);
		y-=a/b*x;
	}else{x=1;y=0;}
}
inline int inv(int a){
	int x,y;
	exgcd(a,mod,x,y);
	return x+((x>>31)&mod);
}
inline int C(int n,int m){return (ll)f[n]*g[m]%mod*g[n-m]%mod;}
inline int Lucas(ll n,ll m){
	int s=1;
	for(ll tn,tm;n&&m;n/=mod,m/=mod){
		if((tn=n%mod)<(tm=m%mod))return 0;
		s=(ll)s*C(tn,tm)%mod;
	}
	return s;
}
inline int solve(ll n,ll m){
	if(n<m)return 0;
	if(m==1)return (n+1)%mod;
	if(n==m)return n*2%mod;
	return (Lucas(n-1,m-2)+Lucas(n+1,m)+Lucas(n-1,m-1)*2-2+mod)%mod;
}
int main(){
	int T=rd(),i,ans=0;
	ll m;
	f[0]=f[1]=g[0]=g[1]=1;
	for(i=2;i<mod;++i)f[i]=(ll)f[i-1]*i%mod;
	g[mod-1]=inv(f[mod-1]);
	for(i=mod-2;i^1;--i)g[i]=(ll)g[i+1]*(i+1)%mod;
	while(T--){
		m=rd();
		ans^=solve(rd(),m);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Purslane (赞：1)

# Solution

$01$ Trie 上节点数的定义为：存在多少个 $01$ 字符串，满足他可能是一个合法字符串的前缀。

把基本字符改为 $01$ 和 $0$。

一个前缀可以由若干个基本字符拼接而成，**也有可能最后用了一半的 $01$**。

先只考虑 $01$ 拼接。假设有 $x$ 个 $01$ 和 $y$ 个 $0$，则方案是 $\binom{x+y}{x}$。

所以这类总的方案就是 $\sum_{i=0}^{c_{01}} \sum_{j=0}^{c_0} \binom{i+j}{i}$。发现内层实际上就是 $\binom{i+c_0+1}{i+1} = \binom{i+c_0+1}{c_0}$，再求一次和是 $\binom{c_0+c_{01}+2}{c_0+1} - 1$。

你还要减去钦定全串时末尾不是 $01$。这比较简单，就是 $\binom{c_{01}+c_0-1}{c_{01}}$。以及把 $01$ 全部用光了但是 $0$ 还没用光，就是 $\sum_{j=0}^{c_0-1} \binom{j+c_{01}}{c_{01}} = \binom{c_0+c_{01}}{c_{01}+1}$。

而一个前缀什么时候一定要用一半的 $01$ 呢？那就是 $0$ 已经不够用了。所以说，就是 $\sum_{i=0}^{c_{01}-1} \binom{c_0 + i}{ i }$，这个东西求和得到 $\binom{c_0+c_{01}}{c_0+1}$。

所以说！答案就是 $\binom{c_0+c_{01}+2}{c_0+1} - 2 - \binom{c_{01}+c_0-1}{c_{01}} - \binom{c_0+c_{01}}{c_{01}+1} + \binom{c_0+c_{01}}{c_0+1}$。

其中 $c_0=m-n$，$c_{01} = n$。

题目给了你一个 $2 \times 10^7$ 的模数，说明可以直接用 Lucas 定理算组合数。复杂度可以认为是 $O(1)$ 算一次。

芝士袋蚂：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e7+10,MOD=18888913;
int T,frac[MAXN],inv[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int cc(int u,int d) {
	if(u>d) return 0;
	return frac[d]*inv[u]%MOD*inv[d-u]%MOD;	
}
int C(int u,int d) {
	if(u<0||u>d) return 0;
	if(u==0&&d==0) return 1;
	return cc(u%MOD,d%MOD)*C(u/MOD,d/MOD)%MOD;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	frac[0]=1; ffor(i,1,MOD-1) frac[i]=frac[i-1]*i%MOD;
	inv[MOD-1]=qpow(frac[MOD-1],MOD-2);
	roff(i,MOD-2,0) inv[i]=inv[i+1]*(i+1)%MOD;
	int ans=0;
	while(T--) {
		int n,m,c01,c0;
		cin>>n>>m,c01=n,c0=m-n;
		if(c0<0) continue ;	
		int res=((C(c0+1,c0+c01+2)-C(c01,c01+c0-1)-C(c01+1,c0+c01)+C(c0+1,c0+c01)-2)%MOD+MOD)%MOD;
		ans^=res;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CatFromMars (赞：1)

独立乱搞出来了式子，和题解区不一样，简单记录一下 qwq

不难想到一个简单的 dp：设 $f(i, j)$ 为有 $i$ 个 $0$，$j$ 个 $1$ 的方案数。显然有方程 $f(i, j) = f(i - 1, j - 1) + f(i - 1, j) + 2$，边界条件是 $f(n, 1) = n + 1$。

这个式子怎么处理？$f(i, j) = f(i - 1, j - 1) + f(i - 1, j)$ 和组合数的递推式很像。于是我们考虑将 $+2$ 的部分单独提出来，对两个部分分别推导通项公式。

形式化的说，设 $p(i, j)$ 满足 $p(i, 1) = i + 1$，$p(i, j) = p(i - 1, j) + p(i - 1, j - 1)(j > 1)$。$g(i, j)$ 满足 $g(i, 1) = 0, g(i, j) = g(i - 1, j - 1) + g(i - 1, j) + 2$。$f(i, j) = p(i, j) + g(i, j)$，我们的问题变成分别推导 $p, f$ 的通项公式。

---

对于 $p(i, j)$，默认 $p(i, 0) = 1$，那么完全可以等价与 $p(1, 1) = 2$ 后的递推。这相当于给普通的杨辉三角在 $(1, 1)$ 的位置上 $+1$。我们可以把这两部分的三角分开计算，于是 $p$ 的三角就可以看成正常的杨辉三角和一个向右平移一个单位，向下平移一个单位的杨辉三角相应位置的加和。

这么说比较抽象，举一个例子，$p$ 的三角是这样的：
```
1 2
1 3 2
1 4 5 2
1 5 9 7 2
```

一个普普通通的杨辉三角是这样的
```
1 1
1 2 1
1 3 3 1
1 4 6 4 1
```
而因为我们是在 $(1, 2)$ 这个位置 $+1$，所以我们只考虑这个位置上 $+1$ 构成的三角，长这样
```
0 1
0 1 1
0 1 2 1
0 1 3 3 1
```
两个三角相应位置相加得到 $p(i, j) = {i\choose j} + {i - 1\choose j - 1}$

---
下面推导 $g$ 的。$g(i, j) = g(i - 1, j) + g(i - 1, j - 1) + 2$。结论 $g(i, j) = 2{i\choose (j - 1)} - 2$。我们来证明：

归纳法，$i = 1, j = 1$ 显然 $g(i, j) = 2$ 成立，那么

$g(i, j) = g(i - 1, j) + g(i - 1, j - 1)+ 2\\ = 2({i-1\choose j - 1}+{i - 1\choose j - 2} -2) + 2 = 2{i\choose j - 1} - 2$。也是成立的。

---
于是我们就得到 $f(i, j) = {i\choose j} + {i - 1\choose j - 1} +2{i\choose j - 1}-2$，Lucas 即可。

代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 18888913 + 10;
const int Mod = 18888913;
int fac[N + 10], ifac[N + 10];
ll n, m;
inline ll read() {
	ll k = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') {
		k = (k * 10ll + ch - '0');
		ch = getchar();
	}
	return k;
}
inline int qpow(int n, int m) {
	int res = 1;
	while(m) {
		if(m & 1) res = (ll)(res * n) % Mod;
		n = (ll)((ll)n * (ll)n) % Mod;
		m >>= 1;
	}
	return res;
}
void prep() {
	fac[0] = 1;
	for(int i = 1; i < Mod; ++i)
		fac[i] = (ll)(1ll * fac[i - 1] * i) % Mod;
	// cout << "QWQ" << endl;
	ifac[Mod - 1] = Mod - 1;
	for(int i = Mod - 2; i >= 0; --i)
		ifac[i] = (ll)(1ll * ifac[i + 1] * (i + 1)) % Mod;
}
inline int C(ll n, ll m) {
	if(m > n) return 0;
	else return (ll)(1ll * ((ll)(1ll * fac[n] * ifac[n - m]) % Mod) * ifac[m]) % Mod;
}
inline int lucas(ll n, ll m) {
	if(n < m) return 0;
//	cout << n << ' ' << m << ' ' << C(n % Mod , m % Mod) << endl;
	if(!m) return 1;
//	if(n < Mod && m < Mod) return C(n, m);
	else return (ll)(1ll * C(n % Mod, m % Mod) * lucas(n / Mod, m / Mod)) % Mod;
}

int main() {
	// ios::sync_with_stdio(0);
	// cin.tie(0), cout.tie(0);
	int T; T = read();
	prep();
	// cout << "QWQ" << endl;
	ll ans = 0;
	while(T--) {
		m = read(), n = read();
		if(m > n) continue;
		ll rest = ((2 * lucas(n, m - 1) + lucas(n - 1, m - 1) - 2 + lucas(n, m) + Mod) % Mod);
		ans ^= rest;
		// cout << rest << endl;
	}
	cout << ans << endl;
}
```

一个小小的后记：其实这道题中我是先推 $g$ 再推 $p$ 的，$g$ 的通项我当时是用打表瞪眼法（大雾）感知出来的，因为我当时用 $\dfrac{g(i, j)}{2} = {i\choose j - 1} - 1$ 进行的感知，这个只能说我运气比较好了 qwq，如果不是这么巧合我是看不出来的。$p$ 的通项当时使用奶龙的组合意义乱搞出来的，但是写题解的时候发现当时的想法很唐氏。其实题解里面这个做法似乎也说得不是特别的明白吧……最后 $f$ 式子貌似没有题解写，所以想要发出来 qwq。蒟蒻不太会计数，如果有任何纰漏或者更好的想法欢迎大家评论，爆踩小蒟蒻 qwq

---

## 作者：Richard_Whr (赞：1)

就纯推柿子呗。

首先我们知道一个结论：Trie 的大小是：
$$\sum\limits_{S \not= \emptyset}(-1)^{|S|-1} \operatorname{Lcp}(S)$$

其中这个 $\operatorname{Lcp}(S)$ 就是 $S$ 集合中的所有串的 $\operatorname{Lcp}$。

拆了这个式子，统计每种最长公共前缀的长度的容斥系数：

$$\sum\limits_{k=1}^{n}k \sum\limits_{\operatorname{Lcp}(s)=k}(-1)^{|S|-1}$$

由于是最长公共前缀，那就只有两种可能。一种就是一直到底是个完整的串，另一种就是在下一步必须分叉。

这个两个 $1$ 不能相邻的处理方法是给每个 $1$ 前面绑定一个 $0$，相当于有 $n$ 个 $01$ 和 $m-n$ 个 $0$ 在做任意归并。

而最后是 $1$ 的限制相当于直接拿掉了一个 $01$。

在此基础上考虑上面两种东西的容斥系数。

第一种是容易的，所有整串的 $|S|$ 都为 $1$，方案数就是 $\binom{m-1}{n-1}$。

第二种情况考虑什么时候会分叉，由于前面是一样的，因此剩余的两个东西数量都是一样的，两种分叉情况形如 $0,01$ 和 $01,0$ 以及 $01$ 和 $0,0$。

发现第一种情况更好凑，需要的物品数量更少，然后这会使 $\operatorname{Lcp}$ 的长度 $+1$。

算一下此时的容斥系数，所有集合的情况都形如在左分叉选一个非空集合 $S_1$，右分叉选一个非空集合 $S_2$，然后拼起来：

$$\sum\limits_{S_1 \not= \emptyset}\sum\limits_{S_2 \not= \emptyset}(-1)^{|S_1|+|S_2|-1}$$

$$\sum\limits_{S_1 \not= \emptyset}(-1)^{|S_1|}\sum\limits_{S_2 \not= \emptyset}(-1)^{|S_2|-1}$$

我们知道 

$$\sum\limits_{S \not= \emptyset}(-1)^{|S|-1}=1-[|S|=0]$$

$$\sum\limits_{S \not= \emptyset}(-1)^{|S|}=[|S|=0]-1$$

那上面这个容斥系数直接就是 $-1$。

接下来算方案数。

前面完全相同的部分直接枚举两种物品分别用了几个，由于最后钦定要放一个 $01$，分叉要求两个都得留一个，可以依此得出上界：

$$\sum\limits_{i=0}^{m-n-1}\sum\limits_{j=0}^{n-2}\binom{i+j}{i} \times (i+j \times 2+1)$$

令 $m=m-n-1,n=n-2$，拆成三部分：

第一部分：

$$\sum\limits_{i=0}^{m}\sum\limits_{j=0}^{n}\binom{i+j}{i}$$

这个是两次上指标前缀和（组合数列求和），算出来是：

$\binom{m+n+2}{n+1}-1$。

第二部分：

$$\sum\limits_{i=0}^{m}\sum\limits_{j=0}^{n}\binom{i+j}{j} \times i$$

把 $i$ 先提出来，然后后面就是一个上指标前缀和：

$$\sum\limits_{i=0}^{m}\binom{i+n+1}{n} \times i$$

注意到分子是常量，用一步吸收恒等式把分子换出来：

$$\sum\limits_{i=0}^{m}\binom{i+n+1}{n} \times \frac{(i+n+2)}{n+1} \times (n+1)-\sum\limits_{i=0}^{m}\binom{i+n+1}{n} \times (n+2)$$

右边那个不说了，左边这个吸收进去就是 $(n+1)\sum\limits_{i=0}^{m}\binom{i+n+2}{n+1}$，一样的处理手段。

第三部分：

$$\sum\limits_{i=0}^{m}\sum\limits_{j=0}^{n}\binom{i+j}{j} \times j$$

和第二部分对称，把 $n,m$ 互换就行了。

所有求和号都没了，最后的式子挺繁琐的，自己算一下吧。

最终要算三个组合数。

如果想继续化简就拿吸收恒等式乱搞一搞？

注意一下取模，不要爆。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+10,mod=18888913;
int fac[N],ifac[N];

int qmi(int a,int k)
{
	int res=1;
	while(k)
	{
		if(k&1) res=res*a%mod;
		k>>=1;
		a=a*a%mod;
	}
	return res;
}

int C(int n,int m)
{
	if(n<m || n<0 || m<0) return 0;
	if(n<mod && m<mod) return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
	return C(n/mod,m/mod)*C(n%mod,m%mod)%mod;
}
int T,n,m;

void init(int n)
{
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	ifac[n]=qmi(fac[n],mod-2);
	for(int i=n-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	init(mod-1);

	cin>>T;
	int sum=0; 
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		int ans=(m%mod+n%mod)%mod*C(m-1,n-1)%mod;
		m=m-n-1,n=n-2;
		if(m>=0 && n>=0)
		{
			int a=C(n+m+2,n+1),b=C(n+m+3,n+1),c=C(n+m+3,n+2);
			int _m=(m+1)%mod,_n=(n+1)%mod;
			int res=(a-1)+2*(_m*b%mod-(_m+1)*a%mod+1)%mod+_n*c%mod-(_n+1)*a%mod+1;
			res=(res%mod+mod)%mod;
			ans=((ans-res)%mod+mod)%mod;	
		} 
		sum=sum^ans;
	}
	
	cout<<sum<<"\n";

	return 0;
}
```

---

## 作者：CrTsIr400 (赞：1)

# [P7386 「EZEC-6」0-1 Trie](https://www.luogu.com.cn/problem/P7386)

---

> 解决互不相邻，通常会强制绑定 01。

首先拿到题目，任意的 $1$ 互不相邻，想到直接在 $1$ 前面强制加个 $0$，刚好可能满足第一个位置是 $0$ 的条件。

于是就变成了有 $n$ 个 $01$ 和 $m-n$ 个 $0$，最后一个位置是 $1$，把符合这样条件的串丢到一棵 $0/1$ Trie 上要的节点数量。

---

>  解决这种复杂条件的计数问题，往往 DP 是一种利器。

我们观察到这道题目的部分分很简单，$n^2$ 可以拿到 $30$ 分的好成绩。

考虑设 $f[x][y]$ 为有 $x$ 个 $01$，$y$ 个 $0$ 的 Trie 树。我们可以自己画图，枚举并且插入 $01$ 或者 $0$ 的分支，不约而同地想到了 $f[x][y]=f[x-1][y]+f[x][y-1]+2$。

边界条件是什么呢？$f[0][y]=y,f[x][0]=2x$。因为这两种情况都是一条链。

只用输出最终的 $f[x][y]$ 即可获得 $30$ 分，比较简单。

---

考虑这个式子能不能优化，因为它的形式比较简单，所以看起来确实是可以的。

尝试把中间所有依赖值都丢掉，我们只关心 $f[n][m]$。（这里重新改写了 $n,m$ 的定义，就是上面的 $x,y$）

> 解决这类问题，分离常数项是一个关键点，分离未知数也是一个关键点。

于是答案应该等于 $k_0\times 2+\sum k_j\times f[1][j]$ 的形式。

考虑找出这个 $k_j$，实际上就是 $(2,j)$ 点到 $(n,m)$ 点的路径条数，因为只有这些路径才能恰好贡献到答案。

于是 $k_j=\binom{n-2+m-j}{n-2}$。

---

> 组合数天生就有优秀的性质，上指标求和可以大大简化你的式子。

接下来考虑 $k_0$ 是什么东西。我们可以枚举每个 $i(i\ge 2),j(j\ge 0)$ 发现这些对答案最终贡献的 $2$ 都能加到  $f[n][m]$ 里面，但是因为有很多种走法，所以每种走法都会贡献 $2$。所以 $k_0$ 相当于 $\forall i\ge 2,j\ge 0$，$(i,j)$ 到 $(n,m)$ 的方案数。

于是 $k_0=\sum_{i=2}^n\sum_{j=0}^m \binom{n-i+m-j}{n-i}$。

先利用上指标求和，观察 $n-i$ 不动，于是答案就是 $\sum_{i=2}^n \binom{n+m-i+1}{n-i+1}$。看起来很麻烦，于是转化成 $\sum_{i=2}^n \binom{n+m-i+1}{m}$。

再次转化求和顺序，我们把 $n+1$ 算上去于是就变成了 $-1+\sum_{i=2}^{n+1}\binom{n+m-i+1}{m}$.

于是就变成了 $-1+\sum_{i=0}^{n-1}\binom{i+m}{m}$。

直接套用上指标求和的形式，变成 $\binom{n+m}{m+1}-1$。

于是这部分就搞完了。

---

> 推式子的时候，常用系数分离，交换循环层级，调整循环顺序，增加循环层级（如果有必要的话）。

接下来再推推式子，$\sum k_j\times f[1][j]$ 是啥。显然，$f[1][j]=(j+2)$。

那么原式= $\sum_{j=0}^m \binom{n-2+m-j}{m-j}(j+2)$。

把 $j$ 替换成 $m-j$（因为从 $0$ 开始枚举），原式= $\sum_{j=0}^m \binom{n-2+j}{j}(m-j+2)$。

带系数的不好搞，尝试把系数分离，变成两个循环，

则原式 $=\sum_{j=0}^m(\binom{n-2+j}{n-2}+ \sum_{k=0}^{m-j}\binom{n-2+j}{n-2})$

~~这是不是更加答辩了。~~

考虑系数分离，左边那坨式子变成了 $\sum_{j=0}^m \binom{n-2+j}{n-2}$。

于是直接调用 $\binom{n-1+m}{n-1}$ 即可。

---

把右边那坨式子交换一下循环顺序，$\sum_{k=0}^m \sum_{j=0}^{m-k}\binom{n-2+j}{j}$。

轻快地变成了 $\sum_{k=0}^m \binom{n-1+m-k}{n-1}$。

调整一下循环顺序，变成了 $\sum_{k=0}^m\binom{n-1+k}{n-1}$。

于是轻快地变成了 $\binom{n+m}{n}$。

整理一下，则 $\sum {k_j}\times f[1][j]=\binom{n+m}{m}+\binom{n+m-1}{m}$。

汇总答案，则为 $F[n][m]=\binom{n+m}{m}+\binom{n+m-1}{m}+2\times\binom{n+m}{m+1}-2$。

---

> 利用杨辉三角的性质，我们可以更加简洁。

能否再次整理？答案是可以的。

先来探究一下一般的模型，$\binom{a}{b}+\binom{a-1}{b}$ 等于什么？

等于 $2\binom{a}{b}-\binom{a-1}{b-1}$。

于是这个式子可以化简成 $2\binom{n+m}{m}+2\binom{n+m}{m+1}-\binom{n+m-1}{n}-2$。

我们知道 $\binom{n}{m}=\binom{n-1}{m}+\binom{n-1}{m-1}$。

于是原式 $=2\binom{n+m+1}{n}-\binom{n+m-1}{n}-2$。

于是这道题，总算是结束了。代码就没必要放了。



---

## 作者：是青白呀 (赞：0)

网格图优化 dp。

设 $f_{n,m}$ 表示剩余 $n$ 个 $1$，$m$ 个 $0$ 时的答案。我们知道根节点一定是 $0$，考虑下一位若是 $0$，则递归到 $f_{n,m-1}$ 的子问题；若下一位是 $1$，则再下一位一定是 $0$，递归到 $f_{n-1,m-1}$ 的子问题。于是可以写出 dp 式子：$f_{n,m}=f_{n,m-1}+f_{n-1,m-1}+2$，其中加的 $2$ 是根节点和根节点的 $1$ 儿子这两个点。边界是 $f_{1,m}=m+1$。

首先可以换元消去 $+2$ 的项，令 $g_{n,m}=f_{n,m}+2$，代入可以发现 $g_{n,m}=g_{n,m-1}+g_{n-1,m-1}$，边界为 $g_{1,m}=m+3$，$g_{i,i-1}=2$。注意加了 $2$ 后，原来为 $0$ 的位置会变成 $2$，因此我们新增了 $g_{i,i-1}$ 这个边界。

将 dp 转移放在平面直角坐标系的第一象限，等价于从某个边界出发，每次向上或向右上走一步，计算所有路径的权值和。下面分别考虑从两种不同边界出发的路径：

- 从边界 $(i,i-1)(i\ge 2)$ 出发的路径，我们要求第一步必须向上走到 $(i,i)$ 处。这样的路径权值均为 $2$，总贡献为 $\sum_{j=2}^n\binom{m-j}{n-j}\times 2=2\binom{m-1}{m-n+1}$。

- 从边界 $(1,i)(i\ge 1)$ 出发的路径，我们要求第一步必须向右上走到 $(2,i+1)$ 处。这样的路径权值为 $i+3$。总贡献为 $\sum_{j=1}^m\binom{m-j-1}{n-2}\times (j+3)$。

  注意到这里的求和由于带了一个乘积，是不好算的。因此我们考虑把每个乘积表示为另一种路线的种数。你发现若我们将起点设为 $(0,-3)$，每次要求往上或往右走一步，走到 $(1,i)$ 的方案数恰好为 $i+3$。因此，我们考虑将这部分计算为从 $(0,-3)$ 出发，走到 $(n,m)$ 的方案数，每条路径在首次离开第 $1$ 列时作分割，与原来的路径即可形成一一对应关系。

  需要注意的是，我们在走的过程中经过了 $(2,1),(2,0),(2,-1)$ 这三个点的路径是不合法的，需要减去。为了避免算重，我们只计数从右下方走到这三个点的路径，分别减去。最后可得出贡献为 $\binom{n+3}{n}-\binom{m+1}{n-2}-2\times \binom{m}{n-2}-3\times \binom{m-1}{n-2}$。

故 $g(n,m)$ 为 $2\binom{m-1}{m-n+1}+\binom{n+3}{n}-\binom{m+1}{n-2}-2\times \binom{m}{n-2}-3\times \binom{m-1}{n-2}$，$f$ 还要再减 $2$。预处理模数以下的阶乘并使用 Lucas 定理即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=2e7+2,mo=18888913;
const double PI=acos(-1);
void read(int &p){
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    p=x*w;
}
int quick_power(int base,int x){
    int res=1;
    while(x){
        if(x&1)res*=base,res%=mo;
        base*=base,base%=mo;
        x>>=1;
    }
    return res;
}
int T,jc[N],qj[N];
int c(int x,int y){
    if(x<y)return 0;
    return jc[x]*qj[y]%mo*qj[x-y]%mo;
}
int lucas(int x,int y){
    if(x<mo&&y<mo)return c(x,y);
    return c(x%mo,y%mo)*lucas(x/mo,y/mo)%mo;
}
int solve(){
    int n,m;
    read(n),read(m);
    if(n==1)return m+1;
    if(n>m)return 0;
    int res=0;
    res=2*lucas(m-1,m-n+1)+lucas(m+3,n)-lucas(m+1,n-2)-2*lucas(m,n-2)-3*lucas(m-1,n-2)-2;
    res=(res%mo+mo)%mo;
    return res;
}
signed main(){
    jc[0]=qj[0]=1;
    rep(i,1,mo-1)
        jc[i]=jc[i-1]*i%mo;
    qj[mo-1]=quick_power(jc[mo-1],mo-2);
    repp(i,mo-2,1)
        qj[i]=qj[i+1]*(i+1)%mo;
    read(T);
    int ans=0;
    while(T--)
        ans^=solve();
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：AlephRei (赞：0)

### Step 1 递推式

解决这种互不相邻问题时，$01$ 捆绑在一起时一个经典套路，合法串必然由 $n$ 个 $01$，$m-n$ 个 $0$ 组成，并且最末一定是 $01$。把有 $n$ 个 $01$，$m-n$ 个 $0$ 的串组成的字典树节点数量和记作 $f_{n,m}$。

如果 $n=1$， 只能先排 $0$ 再排 $01$，$f_{1,m}=m+2$。如果 $m=0$， 则 $f_{n,0}=2n$。不然，定然现在有在前面拼 $0$ 或 $01$ 两种，节点数就是 $f_{n-1,m}+f_{n,m-1}+2$。

### Step 2 通项

现在有递推式：$f_{n,m}=2+f_{n-1,m}+f_{n,m-1}$，$f_{n,0}=2n,f_{1,m}=m+2$。

要么按行进行生成函数， 要么去找到组合数的影子 (实际上把这个表旋转一下就是了)， 这里考虑消除掉 $+2$ 这一项，令 $h_{n+m,m}=f_{n,m}+2$，则 $h_{n+m,m}=h_{n+m-1,m}+h_{n+m-1,m-1}$ 并且 $h_{n,0}=2n+2,h_{n,n-1}=n+3$。这里的递推式已经长成组合数的形式的，但是边界条件没有满足。

猜想此时 $h_{n,m}$ 一定等于若干组 $k\binom{n+a}{m+b}$ 的和，对于一个单组 $m=0$ 时 $k\binom{n+a}{m+b}=k\binom{n+a}{b}$，$n=m+1$ 时 $k\binom{n+a}{m+b}=k\binom{n+a}{a-b+1}$。由 $n$ 的次数知，所有的 $a,b$ 都有 $b\le 1,a\le b$ 并且所有 $a,b$ 对中至少一个 $b=1$，至少有一个 $a=b$。

可以猜测只用两项 (就像插值一样)，假设一个 $b=1$， 一个 $a=b$ (不然第二个只能贡献常数)。设 $h_{n,m}=k_1\binom{n+a}{m+1}+k_2\binom{n+b}{m+b}$，需要满足：

$$
\left\{\begin{matrix}
k_1(n+a)+k_2\binom{n+b}{b}=2n+2\\
k_1\binom{n+a}{a}+k_2(n+b)=n+3\\
a,b\le 1
\end{matrix}\right.
$$

如果 $b<0$， 第一个方程左边第二项为 $0$，则 $k_1=2,a=1,k_2=-1,b=-1$ 是一组合法解，$b=0,b=1$ 就不用试了。

带入回去 $h_{n,m}=2\binom{n+1}{m+1}-\binom{n-1}{m-1}$，之后再推 $f_{n,m}$ 即可，此处不再赘述。计算的时候也仅需要 Lucas 计算组合数，代码不放了。

警示：注意输入的 $n,m$ 可能 $m<n$ 要判掉。

---

## 作者：TernaryTree (赞：0)

Preface: 我不会推式子，但是我很会找规律。

首先把每个 $1$ 前面绑一个 $0$，也就是有 $n$ 个 $01$，$m-n$ 个 $0$，最后一个是 $01$ 的 trie 节点数。$m<n$ 可以直接判掉答案为 $0$。

令 $n,m$ 同阶。注意到有 $n^2$ 的部分分，因此直接考虑 dp。记 $f_{i,j}$ 表示 $i$ 个 $01$，$j$ 个 $0$ 的 trie 结点数。你可以枚举这样的串最前面拼的是 $0$ 还是 $01$，如果是 $0$ 那么此时在根下面直接连上 $f_{i,j-1}$ 的 trie，否则在根下面建一个 $1$ 的点，在这个点下面接 $f_{i-1,j}$ 的 trie。所以有

$$f_{i,j}=f_{i-1,j}+f_{i,j-1}+2$$

边界为 $f_{1,j}=j+2$，$f_{i,-1}=0$（此处定义 $j=-1$ 是为了方便，容易发现 $f_{i,0}$ 这样转移是正确的）。

考虑找 $f_{i,j}$ 通项。将前面的递推与后面的 $+2$ 分开计算。

$+2$ 不过是一个常数，可暂时看做 $+1$，后面推完再乘 $2$ 即可。令 $g_{1,j}=g_{i,-1}=0$，$g_{i,j}=g_{i-1,j}+g_{i,j-1}+1$，求 $g_{i,j}$ 通项公式。显然地，可以令 $g'_{i,j}=g_{i,j}+1$，即可简单地消掉转移式的常数项：$g'_{1,j}=g'_{i,-1}=1$，$g'_{i,j}=g'_{i-1,j}+g'_{i,j-1}$，这是杨辉三角转移式，也就是每个位置是一个组合数。简单处理一下下标偏移量可以得出，$g'_{i,j}=\binom{i+j}{i-1}$，$g_{i,j}=\binom{i+j}{i-1}-1$。于是 $f_{i,j}$ 的一部分是 $2g_{i,j}=2\binom{i+j}{i-1}-2$。

接下来计算前面的部分。同理，令 $h_{1,j}=j+2$，$h_{i,-1}=0$，$h_{i,j}=h_{i-1,j}+h_{i,j-1}$，求 $h_{i,j}$ 通项公式。可以计算每个 $h_{1,j}$ 被算了几次。手摸逐层扩展一下会发现，对于一个点 $h_{n,m}$，每个 $h_{1,j}$ 会被计算 $\binom{n+m-2-j}{n-2}$ 次，则有

$$
\begin{aligned}
h_{n,m}&=\sum_{j=0}^m \binom{n+m-2-j}{n-2} (j+2) \\
&=\sum_{j=0}^m \binom{n-2+j}{n-2} (m-j+2) \\
&=(m+2)\sum_{j=0}^m \binom{n-2+j}{n-2}-\sum_{j=0}^m \binom{n-2+j}{n-2} j \\
\end{aligned}
$$

前者是经典式子 

$$\sum_{i=0}^m \dbinom{n+i}{n}=\dbinom{n+m+1}{n+1}$$

不会的话可以打一个表，这个找规律非常明显。

后面不会化，怎么办？？？继续打表。令 $D_{n,m}$ 表示 $\sum\limits_{j=0}^{n-m}\binom{m+j}{m}j$，可打出下表：

|  | $0$ | $1$ | $2$ | $3$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $0$ |  |  |  |
| $1$ | $1$ | $0$ |  |  |
| $2$ | $3$ | $2$ | $0$ |  |
| $3$ | $6$ | $8$ | $3$ | $0$ |

多打出几行就会发现，一定存在 $(j+1)\mid D_{i,j}$，且 $\frac{D_{i,j}}{j+1}=\binom{i+1}{j+2}$。于是我们得到了 $D_{i,j}$ 的通项：

$$D_{i,j}=(j+1)\dbinom{i+1}{j+2}$$

代会原式，有

$$
\begin{aligned}
&\sum_{j=0}^m \binom{n-2+j}{n-2} j \\
=&D_{n-2+m,n-2} \\
=&(n-1)\dbinom{n+m-1}{n}
\end{aligned}
$$

综合上述三部分，有

$$f_{n,m}=(m+2)\dbinom{n+m-1}{m}-(n-1)\dbinom{n+m-1}{n}+2\dbinom{n+m}{n-1}-2$$

Lucas 求组合数即可。

---

## 作者：gan1234 (赞：0)

## P7386「EZEC-6」0-1 Trie

### 分析 

Trie 树的每一个节点都对应了所有合法 $01$ 串的所有不重前缀。

所以 Trie 树的节点数就是合法前缀数。

由于第一个位置是 $0$，最后一个位置是 $1$，所以有三个位置已经确定了。

不考虑这三个位置，共有 $n-1$ 个 $1$，$m-2$ 个 $0$。

令 $N=n-1,M=m-2$。 

考虑 节点数 = $1$（第一个位置）$+$ 至多 $N$ 个 $1$ 与 $M$ 个 $0$ 组成的合法前缀方案数 $+$ $N$ 个 $1$ 与 $M$ 个 $0$ 组成的合法前缀方案数 $\times2$（后两个位置）。

使用隔板法，可以算出，以 $0$ 为结尾，$i$ 个 $1$ 与 $j$ 个 $0$ 的方案数为 $\binom{j}{i}$，以 $1$ 为结尾方案数为 $\binom{j}{i-1}$。

一个前缀合法，必须保证剩下的 $0$ 和 $1$ 能组成一个合法后缀。

以 $0$ 为结尾，合法的条件是 $N-i\le M-j+1$，以 $1$ 为结尾，合法的条件为 $N-i\le M-j$。

考虑枚举 $1$ 的个数与 $0$ 的个数。

答案就是：

$$1+\sum^{N-1}_{i=0}\sum^{M-N+i+1}_{j=1}\binom{j}{i}+\sum^M_{j=1}\binom{j}{N}+\sum^{N}_{i=1}\sum^{M-N+i}_{j=0}\binom{j}{i-1}+2\binom{M+1}{N}$$

### 推式子

中间有三个很复杂的式子，分别根据上指标求和与平行求和法化简即可。注意细节。

$$\sum^{N-1}_{i=0}\sum^{M-N+i+1}_{j=1}\binom{j}{i}=\sum^{N-1}_{i=0}\binom{M-N+i+2}{i+1}-1=\binom{M+2}{N}-2$$

$$\sum^M_{j=1}\binom{j}{N}=\binom{M+1}{N+1}-\binom{0}{N}$$

$$\sum^{N}_{i=1}\sum^{M-N+i}_{j=0}\binom{j}{i-1}=\sum^N_{i=1}\binom{M-N+i+1}{i}=\binom{M+2}{N}-\binom{M-N+1}{0}$$

因此最终答案为 
$$1+\binom{M+2}{N}-2+\binom{M+1}{N+1}-\binom{0}{N}+\binom{M+2}{N}-\binom{M-N+1}{0}+2\binom{M+1}{N}$$

$$=2\binom{M+2}{N}+\binom{M+1}{N+1}+2\binom{M+1}{N}-2$$

特判 $N\ge M+2$，此时答案为 $0$。

---

