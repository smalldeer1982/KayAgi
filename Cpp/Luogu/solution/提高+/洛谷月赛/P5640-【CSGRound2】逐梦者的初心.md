# 【CSGRound2】逐梦者的初心

## 题目背景

#### 注意：本题时限修改至250ms，并且数据进行大幅度加强。本题强制开启O2优化，并且不再重测，请大家自己重新提交。

由于Y校的老师非常毒瘤，要求zhouwc在csp考前最后3天参加期中考，zhouwc非常生气，决定消极考试，以涂完卡但全错为目标。现在retcarizy看zhouwc太可怜了，想要帮zhouwc解决一个问题，但他自己又太忙了，咕咕咕，于是就把问题甩给了你。

## 题目描述

给你一个长度为n的字符串S。

有m个操作，保证$m\le n$。

你还有一个字符串T，刚开始为空。

共有两种操作。

第一种操作：

在字符串T的末尾加上一个字符。

第二种操作：

在字符串T的开头加上一个字符。

每次操作完成后要求输出有几个$l \in [1,T.size]$满足以下条件：

对于$\forall i \in [1,l]$有$T_{T.size-l+i} \ne S_{i}$ 

$Tip:$字符串下标从1开始。$T.size$表示T的长度。

## 说明/提示

注意：本题采用**捆绑测试**，只有当你通过一个subtask的所有点后，你才能拿到这个subtask的分数

对于所有的数据 $n \leq 10^6,m \leq 3.3333 \times 10^4,|\sum|\leq10^3,S_i \in [1,|\sum|]$。($\sum$表示字符集)

subtask1$(17\%)$:$m \leq 333$

subtask2$(33\%)$:$m \leq 3333$

subtask3$(20\%)$:$|\sum|\leq2$

subtask4$(30\%)$:无特殊条件


#### 样例解释：
第一次操作后，$T="1"$,

$l=1$时$T[1]=S[1]$，所以答案为0

第二次操作后，$T="21"$,

$l=1$时，$T[2]=S[1]$

$l=2$时，$T[1]!=S[1]$,$T[2]!=S[2]$所以答案为1

第三次操作后，$T="213"$,

$l=1$时，$T[3]!=S[1]$;

$l=2$时，$T[2]=S[1]$;

$l=3$时，$T[3]=S[3]$所以答案为1


## 样例 #1

### 输入

```
10 3
1 2 3 1 2 3 2 3 2 3
0 1
1 2
0 3```

### 输出

```
0
1
1```

# 题解

## 作者：zhouwc (赞：23)

#### 官方题解

##### subtask1

对于每次操作，枚举$l$，枚举$i$，判断一下。考察了循环语句和分支语句的简单应用。

时间复杂度$O(m^3)$

##### subtask2

记录下每次操作后每个$i$满不满足条件。

考虑在末尾加一个字符

不难发现原来的$i$变成了现在的$i+1$，再把新加入的字符对状态的影响处理一下。

再考虑在开头加一个字符

原来的状态不用变，只要把新加入的字符对状态的影响处理。

时间复杂度$O(m^2)$

##### subtask3

字符集非常小，答案只有在特殊情况下才存在，可能存在什么神奇的做法。

##### subtask4	

每个位子和每种字符都是独立的，对每种字符都记录一下位子。

用$f[i]=0 or 1$表示长度为$i$的后缀可不可以，0表示可以，1表示不行。

考虑f只有0和1，可以用bitset优化，对每种字符都开一个bitset记录是不是该字符。

在末尾加一个字符时，左移后做or运算。

在开头加一个字符时，直接or上该字符出现的状态左移长度减一位。

答案就是范围内0的个数。

复杂度$O(m^2/w)$

std：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<bitset>
using namespace std;
int n,m,opt,S[1000005],dt;
bitset<35005> f,id[1005],now;
int read(){
	int ans=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch<='9'&&ch>='0'){
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans;
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		S[i]=read();
	for(int i=1;i<=m;i++)
		id[S[i]].set(i);
	now.set();
	for(int i=1;i<=m;i++){
		opt=read();
		dt=read();
		now.reset(i);
		if(opt==0)
			f=(f<<1)|id[dt];
		else
			f=f|(id[dt]<<(i-1));
		printf("%d\n",(~(f|now)).count());
	}
	return 0;
}
```


附录：

##### 关于如何使用bitset

简单的来说，bitset就是压位优化的0/1数组。

定义一个长度为$len$的bitset：

```
bitset<len> f;
```

把f的每一位都改为1

```
f.set();
```

把f的第i位改为1

```
f.set(i);
```

把f的每一位都改为0

```
f.reset();
```

把f的第i位改为0

```
f.reset(i);
```

求f有几个1

```
f.count();
```

各类位运算和整数类型一样

```
f=f<<1;
f=f>>1;
f=f&f;
f=f|f;
f=f^f;
f=~f;
```



---

## 作者：Nemlit (赞：12)

$Updata:$本篇题解现在已经不能通过，就当成是一个常熟优秀的暴力吧，仅供参考


发现我们需要往前/往后插入元素，所以我们可以先预处理出整个T数组，然后记录当前T的左右端点，这样就不需要用什么数据结构来维护了

发现题意其实就是要你求出有多少个L，满足S的前L个数和T的后L个数互不相等

考虑加入每一个数的贡献：

$Case1:\ $往前面插入元素

发现往T数组前面插入元素对我们已经满足条件的L不会产生影响，暴力扫一遍，看是不是整个T与S的前缀互不相等，在存入答案即可

$Case2:\ $往后面插入元素：

首先，如果$S[1]=T[r]$那么则说明$L=1$的时候满足，我们需要加入答案

对于插入前我们已经满足L，我们暴力扫一遍，如果$T[r]=S[r-i+1]$了，则说明这个L已经不合法，删掉即可

于是我们现在需要维护一个东西，支持快速插入，删除，遍历，我这里使用的链表

然后存在一个坑点，最好先把链头设成虚拟节点，否则的话如果删掉链头需要更新（我这里采用的是后者）

~~代码其实挺好写的~~

## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i , a , b) for(int i = (a) , i##Limit = (b) ; i <= i##Limit ; ++ i)
#define maxn 1000006
int n, m, a[maxn], Ans, nxt[maxn], pre[maxn], opt[maxn], w[maxn], b[maxn], x, l, r, t;
il void del(int x) {
	nxt[pre[x]] = nxt[x], pre[nxt[x]] = pre[x];
}
il void solve2() {
	for(re int i = t; i; i = nxt[i]) { 
		if(b[r] == a[r - i + 1]) {
			del(i), -- Ans;
			if(t == i) t = nxt[i];
		}
	}
	if(b[r] != a[1]) pre[t] = r, nxt[r] = t, t = r, ++ Ans;
}
il void solve() {
	rep(i, l, r) if(a[i - l + 1] == b[i]) return;
	pre[t] = l, nxt[l] = t, t = l, ++ Ans;
}
signed main() {
	n = read(), m = read();
	rep(i, 1, n) a[i] = read();
	rep(i, 1, m) opt[i] = read(), w[i] = read(), x += opt[i];
	l = x + 1, r = x;
	rep(i, 1, m) {
		if(opt[i] == 1) b[-- l] = w[i];
		else b[++ r] = w[i];
	}
	l = x + 1, r = x;
	rep(i, 1, m) {
		if(i == 1) {opt[i] == 1 ? -- l : ++ r; solve();}
		else if(opt[i] == 1) -- l, solve();
		else ++ r, solve2();
		printf("%d\n", Ans);
	}
	return 0;
}

```

---

## 作者：天泽龟 (赞：5)

不知道数据加强了没有，本篇题解就来分享一下考试的心路历程和$bitset$正解做法。

---

### $17$分：

按照题目模拟即可。

## $50$分考场思路：

这档分必须要得到AC本题的先决结论，我们手玩样例。

1. `i=1`时：

	T= 1  
    S= 1

易得无解。

2. `i=2`时，在**左边**$(op=1)$插入：
	
    T= 2 1  
    S= 1 2
    
此时可发现，对于`l=1`的情况答案没有变化，**因为题目是对于$T$串是从后往前去更新的，只更新的元素可能在`l=i`时造成贡献。**

于是`l=2`时，我们只需暴力扫一遍，看有没有同位置相同的元素即可。

3. `i=3`时，在**右边**$(op=0)$插入：

	T= 2 1 3  
    S= 1 2 3

此时对于`l=1`，是T[3]与S[1]匹配，发现不符后贡献加1.

对于`l=2`，是`T[2..3]`与`S[1..2]`匹配，可以注意到`T[2]`与`S[1]`我们在之前是已经匹配过的，那时候是相同，所以这次还是无贡献；

更有甚者，我们发现`l=3`时,前两项仍旧在之前匹配过但当时存在贡献，而`T[3]=S[3]`，所以本次是无贡献的。

**所以对于这类情况，只需要让更新的那一个元素与$S$串一 一匹配，再考虑之前的串上一次是否产生贡献，这样直接与起来就是当前的答案了。** 

---

所以对于$50$分，我考场的解法是这样的：

我们用两个数组$l[i],r[i]$维护输入的字符串，`op=0`加在$l[i]$里，`op=1`加在$r[i]$里，这样每次考虑`op=1`时，我们只需倒序枚举$l[i]$，正序枚举$r[i]$，保证所有元素均不为`x`就行了。

我们再设$ans[i]$为长度为i时是否对答案造成贡献。我们知道对于`op=0`的情况，这次的$ans[i]$其实就是由上次的$ans[i-1]$与$x=s[i]$一起影响的。那么我们只需先把$ans[i]$右移一位，令$ans[1]=1$（第一位只受第二个因素影响），然后单独考虑$x=s[i]$即可。

### $70$分：

出题人说这是给乱搞选手留的，但实际上就是$50$分暴力。

因为所有字符由$1,2$构成，所以对于`op=1`的操作，撞车的概率极大，所以只要撞车我们就直接标记无贡献,`break`即可。这样$O(M^2)$是跑不满的，卡一卡就能过。

上我丑陋的代码：
```cpp
#include <iostream>
#include <cstring>
#include <vector>
#define inf 2147483647
using namespace std;

int n,m,s[3330450],le[33336],ri[33336],ans[33336],ans0[33338];

int read()
{
  int n=0;
  char c=getchar();
  while(c>'9'||c<'0') c=getchar();
  while(c>='0'&&c<='9') n=(n<<1)+(n<<3)+(c^48),c=getchar();
  return n;
}
int main()
{
	n=read(); m=read(); ans[0]=1;
	for (int i=1;i<=n;i++) s[i]=read();
	for (int i=1,op,x,sm=0;i<=m;i++)
	{
		op=read(); x=read(); 
        if (op) le[++le[0]]=x; else ri[++ri[0]]=x;
		if (!op) {	sm=0;
			for (int j=i;j>=2;j--) ans[j]=ans[j-1]; ans[1]=1; 
			for (int j=1;j<=i;j++) 
			ans[j]=(ans[j] && (x!=s[j]) ),sm+=ans[j];
			printf("%d\n",sm);
		}
		else {
			ans[i]=(x!=s[1]); int p=1;
			for (int j=le[0];ans[i] && j>=1;j--,p++) {
				ans[i]=(ans[i] && (le[j]!=s[p]) );
				if (!ans[i]) break;
			}
			for (int j=1;ans[i] && j<=ri[0];j++,p++) {
				ans[i]=(ans[i] && (ri[j]!=s[p]) );
				if (!ans[i]) break;
			}
			sm+=(ans[i]);	printf("%d\n",sm);
		}
	}
}
```

## $50$正解思路：
由于`op=0`优化不了，之前那个思路$70$分封顶了。。易知正解应该和$\sum$发生关系，但是没想出来。。

我们设$id[x][i]$表示字符$x$在$S$的第$i$位上是否出现，$ans[i]$仍和上面相同。

那么对于`op=0`还是一样的想法，用$id$表示就是$ans[i-1] ~~and ~~id[x][i]$；对于`op=1`时，我们发现当$x=S[i-l+1]$时对于`l`就无贡献了，这个用$id$表示即为$ans[i] ~~and ~~(id[x][i-l+1])$，直接$O(m^2)$扫即可。

但是对于这个暴力，只含有乱七八糟的$bool$数组，即可用$bitset$优化，代码也很简练：
```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#define inf 2147483647
using namespace std;

int n,m,s[3330450],le[33336],ri[33336];
bitset<36000> ans,id[1011],now;

int read()
{
  int n=0;
  char c=getchar();
  while(c>'9'||c<'0') c=getchar();
  while(c>='0'&&c<='9') n=(n<<1)+(n<<3)+(c^48),c=getchar();
  return n;
}

int main()
{
	n=read(); m=read(); ans[0]=1;
	for (int i=1;i<=n;i++) s[i]=read();
	for (int i=1;i<=m;i++) id[s[i]].set(i);
	now.set();
	for (int i=1,op,x,sm=0;i<=m;i++)
	{
		op=read(); x=read(); now.flip(i);  //now来限制到了第几位 
		if (!op) ans=(ans<<1)|id[x]; else ans|=(id[x]<<(i-1));
		printf("%d\n",(~(ans|now)).count());  //用了集合转换的思想。 
	}
	return 0;
}
```
于是就没了。。。

---

## 作者：lqx_bnu (赞：4)

代码已经很多了，主要是努力再解释一下官方题解的意思。

$O(m^3)$的做法很容易想，按照题意模拟即可。预计得分$17pts$。

对于$O(m^2)$的做法，因为这个题实际上是查找$S$的前$l$个和$T$的后$l$个是否严格不相等，我们考虑记录$dp[l]$表示在上述意义下$l$是否合法。容易知道，在$T$串最后插入一个字符时，因为$S$串始终不变，$T$串的最后$l$个字符从原本$T$串的后$l$个字符变成了原本$T$串的后$l-1$个字符加上新加入的字符，所以为了比较新的$T$串后$l$个字符是否合法，我们只需要比较新字符、原本$T$串的后$l-1$个字符是否相等即可。即$dp[i]=dp[i-1]|(ch==S[i])$。这样，对于每个加入的字符，只需要用$O(1)$的复杂度检查每个枚举到的$l$是否合法即可。

在$T$串最前面插入一个字符时，因为原本所有的合法的$l$依然没有变化，只是增加了一个新的$l$,所以我们只需暴力$check$新加入的答案$l$，对于每一位枚举是否不同即可。

时间复杂度$O(m^2)$，预计得分$50pts$。是我在考场上想出来的方法。

考虑优化$O(m^2)$的做法，我们找到了状压神器——$bitset$，它可以将复杂度优化到原来的$\frac{1}{32}$。如果常数优秀一些这个方法可以过。

考虑刚才的方法算过了哪些不可能合法的状态，我们知道所有的字符其存在位置都是独立的，所以我们用一个$bitset$数组$id[i]$记录字符$i$在哪些位置上出现过。只要加入的新数$dt$对应的位置是$id[dt]$上$1$的位置，则该状态肯定不合法。

所以这样优化的关键在于同时算出了所有合法的状态。所以我们用$f$的第$i$位的$0/1$表示后缀长度为$i$时是否合法。

如果在$T$串尾部加入新的字符，则对于长度是$i$的情况一定是由$i-1$的情况和新加入位的情况同时转移来（见上述$O(n^2)$做法），而所有新加入的位对应与$S$串中哪些位相同已经存储好，假设加入的字符是$dt$，则$f=(f<<1)|id[dt]$。

如果在$T$串头部加入新的字符，设原来$T$串有效的后缀长度有$l$位，则新的$T$串后$l$位是否合法状态不变，所以新旧$T$串前面$l$位答案一样；

在$T$串头部插入新字符时，我们发现遇到了一些新的问题：

第一，我们发现在头部加入字符时，后面的所有字符都往后移了一位。

第二，我们需要比较加入的新字符和第一个字符是否相同。

很明显困难在于解决第一个问题。因为我们如果要想比较移动之后的字符和$S$的关系，在不知道其它任何东西的情况下，需要另用一个$O(n)$检查。

解决这个问题的方法是一个非常重要的思想：费用提前。在每次从队尾加入一个字符时，我们将这个字符所能贡献到答案的所有位置一次存好。方法很简单，假设我们每次加进的字符是$dt$，考虑这一位对应到$S$串的所有可能。如果$dt$对应到的某一位上$id[dt]$在同样的位上恰好是$1$，说明当队尾不断加入字符使当前这个$dt$恰好对应到刚才说的这一位上，则这样的方案肯定是不合法的。

考虑如何进行这样的操作。假设$dt$是在第$i$位加入队列，则$dt$离$T$结尾的长度是$i-1$。注意这里我们只讨论$T$序列结尾的费用提前，因为其它点情况和结尾一样。假设$dt$对应的$id$值在第$k$位上是$1$，说明$dt$在取到第$k$位时整体一定不合法。这时$dt$距离队尾的距离是$l-1$，所以$dt$的位置由队尾左移$i-1$位得到，所以当$dt$取到$k$时，队尾应该取到$k-l+1$位，但是注意是反着存的，所以：
$$
f=f|(id[dt]<<x-1)
$$
代码几乎就是官方题解，不过还是上一下代码：

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<bitset>
using namespace std;
int n,m,opt,S[1000005],dt;
bitset<35005> f,id[1005],now;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int main(){
    n=read();
    m=read();
    for(int i=1;i<=n;i++)
        S[i]=read();
    for(int i=1;i<=m;i++)
        id[S[i]].set(i);
    now.set();
    for(int i=1;i<=m;i++){
        opt=read();
        dt=read();
        now.reset(i);
        if(opt==0)
            f=(f<<1)|id[dt];
        else
            f=f|(id[dt]<<(i-1));
        printf("%d\n",(~(f|now)).count());
    }
    return 0;
}
```

注意得开$O(2)$。

---

## 作者：傅思维666 (赞：3)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11837509.html)

在考场上一开始发现这道题是道绿题，但是自己却没什么成形的思路，顿觉一身冷汗...不说匹配，就前面的那个在头尾加入字符串我就有些束手无策的感觉。果然还是蒟蒻太菜了。

越到这种时候越要冷静。（哈哈哈）在我冷静之后一段时间内，我灵光乍现（前一段时间刚总结完STL，详情请见下面的博客：）

[C++STL容器全解]( https://www.cnblogs.com/fusiwei/p/11823234.html )

发现在头尾加元素可以用deque这种容器来实现。（哇哈哈哈哈哈）而且deque还是STL中为数不多支持随机访问的容器，简直不要太好用！

考场思路一开始的思路是暴力枚举匹配。

期望50分，但只能拿17pts.

代码：

```cpp
#include<cstdio>
#include<deque>
using namespace std;
const int maxn=1e6+10;
int n,m,tot,flag;
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0,f=1;
	char ch=nc();
	while(ch<48){if(ch=='-')f=-1;ch=nc();}
	while(ch>47)	x=(((x<<2)+x)<<1)+ch-48,ch=nc();
	return x*f;
}
int s[maxn];
deque<int> q;
int main()
{
	n=read(),m=read();
	for(int i=0;i<n;i++)
		s[i]=read();
	while(m--)
	{
		tot=0;
		int opt=read();
		int ch=read();
		if(!opt)
			q.push_back(ch);
		else
			q.push_front(ch);
		for(int i=0;i<q.size();i++)
		{
			flag=0;
			for(int j=0;j<=i;j++)
				if(q[q.size()-i+j-1]==s[j])
				{
					flag=1;
					break;
				}
			if(!flag)
				tot++;
		}
		printf("%d\n",tot);
	}
	return 0;
}
```

我的脚步就到此为止了么？不可能！然后我就深入地想了一下，并且在原暴力的基础上进行了一些优化。但是暴力优化并没有起到太大的效果。那么就一定是思路的问题。于是我又重新思考了一下。我的思路是这样的：

既然时间不允许每次都暴力匹配，而匹配过程还不能进行优化，那么最终的正解不可能是每次都匹配。一定有什么玄妙的规律。

于是我在草纸上随便画了画...

（这里插一嘴，我在写题解的时候注重对思路历程的剖析。也就是不止讲怎么做是对的，还要讲如果是一道新题，怎么想才能想到正解。但是有些细节真的很难口述明白，比如草纸画图这种东西，恳请读者见谅并自己老老实实拿张草纸边看题解边模拟。这样事半功倍。）

发现，每一道题答案是否合法是可以通过之前的答案转移过来的。

具体一点就是，当元素往前面插，那么插入之前的老数列的答案是不会被影响的。只需要扫描一遍这个新数列和给定的数列$S$是否是全部不等的，如果是的话就说明有了一个合法答案。

当元素往后面插的时候，就会影响之前的老数列的答案。也就是说，需要一一匹配**前面合法的答案是否还能保持合法性**。

思路是对的，但是代码不会写了，考试剩下的两个小时全都在尝试着实现这个思路，但是失败了。

于是最终还是17分。

看了和我思路相似的题解，我才恍然大悟。因为向后插入的时候需要匹配前面所有的合法答案。那么怎么知道前面都有哪些答案合法呢？很简单，再开一个$vector$存一下就可以了。

大约是这样：

```cpp
#include<cstdio>
#include<deque>
#include<vector>
#pragma GCC optimize(2)
using namespace std;
const int maxn=1e6+10;
int n,m;
int s[maxn];
bool flag;
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<48){if(ch=='-')f=-1;ch=nc();}
    while(ch>47)    x=(((x<<2)+x)<<1)+ch-48,ch=nc();
    return x*f;
}
deque<int> q;
vector<int> vec;
vector<int>::iterator it;
int main()
{
    n=read();m=read();
    for(int i=0;i<n;i++)
        s[i]=read();
    while(m--)
    {
        int opt=read();
        int x=read();
        if(opt)
        {
            q.push_front(x);
            flag=0;
            for(int i=0;i<q.size();i++)
                if(q[i]==s[i])
                {
                    flag=1;
                    break;
                }
            if(!flag)
                vec.push_back(q.size());
        }
        else
        {
            q.push_back(x);
            it=vec.begin();
            while(it!=vec.end())
            {
                (*it)++;
                if(s[*it-1]==x)
                    vec.erase(it);
                else
                    ++it;
            }
            if(s[0]!=x)
                vec.push_back(1);
        }
        printf("%d\n",vec.size());
    }
    return 0;
}
```

本来这样的话开一开$O2$就过了。但是出题人又改了数据、压了时限，于是这个思路变成了$70$分代码。

那么我们看一下正解：

每个位子和每种字符都是独立的，对每种字符都记录一下位子。

用$f[i]=0 \,\,\,or\,\,\,1$表示长度为$i$的后缀可不可以，0表示可以，1表示不行。

考虑$f$只有$0$和$1$，可以用$bitset$优化，对每种字符都开一个$bitset$记录是不是该字符。

在末尾加一个字符时，左移后做$or$运算。

在开头加一个字符时，直接$or$上该字符出现的状态左移长度减一位。

答案就是范围内$0$的个数。

于是传说中的双端队列变成了bitset......

---

## 作者：Lucifer_Bartholomew (赞：3)

# 模拟
题目有两种操作：放一个数到${T}$前面或放一个数到${T}$后面。

我们发现对于新放到前面的数,它只会影响以自己为开头的数列的匹配,对之前的答案不会有影响,所以就可以直接扫一遍整个数列与${S}$的前缀有没有相等的,没有就答案加1。

而对于新放到后面的数,它只能作为其他数列的结尾,而且它只会影响已经满足条件的数列,不可能把不满足条件的数列变得满足条件。所以可以将之前满足条件的${l}$记录下来,再看新放的数是否与${S}_{l+1}$相同,若相同,则不再满足条件,答案就减1；

可以用vector维护${l}$,用deque维护${T}$。开${O_2}$后只跑了50${ms}$(毕竟deque常数巨大,您如果不想开${O_2}$可以自己手写双向队列)。

细节见代码。

update:关于这篇题解,它${m^2}$咕了。它真的只能当模拟暴力题解阅读了。

```cpp
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int a[1000001];//存S
vector<int> ans;//存L
deque<int> q;//存T
int main()
{
	int n=read(),m=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	while(m--)
	{
		int t=read(),x=read();
		if(t)//放到前面
		{
			q.push_front(x);
			int cnt=1;
			bool flag=1;
			for(deque<int>::iterator it=q.begin();it!=q.end();++it,++cnt)//暴力遍历T找相等
				if(*it==a[cnt])
				{
					flag=0;
					break;
				}
			if(flag)ans.push_back(q.size());//没有相等的就答案加1
		}
		else//放到后面
		{
			q.push_back(x);
			vector<int>::iterator it=ans.begin();
			while(it!=ans.end())//遍历之前的满足条件的L看新加的数是不是也满足条件
			{
				(*it)++;//更新L的长度
				if(a[*it]==x)ans.erase(it);//如果现在不满足条件,以后也不会满足条件,那么就从满足条件的L中删去
				else ++it;
			}
			if(a[1]!=x)ans.push_back(1);//特殊的,新加的数可以单独一个去匹配
		}
		printf("%d\n",ans.size());//有多少个满足条件的L就是答案
	}
    return 0;
}
```
~~我是蒟蒻~~

---

