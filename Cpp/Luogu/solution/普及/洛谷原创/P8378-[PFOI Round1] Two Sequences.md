# [PFOI Round1] Two Sequences

## 题目背景

syzf2222 喜欢并查集！特别是路径压缩的并查集。

## 题目描述



```cpp
inline int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
	fx=find(x),fy=find(y);
	if(fx==fy)return;fa[fx]=fy;
}
```

这是他惯用的并查集代码，初始时对于每个 $x$ 有 `fa[x]=x`。

接下来的 $T$ 天中，每天小 h 都给了他一个 $n$，表示并查集的大小（每天的 $n$ 可能是不同的）。

调皮的小 x 见他不在机房，每天都在并查集上不断 `merge`。
注意到小 x 不喜欢 `==`，他觉得这特别像他的眼睛，于是他不会使 `merge` 函数在第二行的条件语句中被 `return`，否则他会十分气愤。

现在的已知信息就只有最终的 $fa$ 数组了。
而 syzf2222 希望还原小 x 的操作序列（即若干次按顺序进行的 `merge` 操作）。由于他名字里有很多个 2 而且本人也非常 2 ，他希望知道对于每一天，有多少个 $fa$ 数组**恰好**能被还原成**两种**操作序列，答案对 $998244353$ 取余数。

两个操作序列不同，当且仅当某次 `merge` 时的变量 `fx,fy` 至少有一个不同。



## 说明/提示

【样例解释】

对于第一天，$n=3$，共有 $fa=[1,1,1],[2,2,2],[3,3,3]$ 这三种 $fa$ 数组使得恰有两种操作序列。

以 $fa=[1,1,1]$ 为例，两种操作序列分别为 `merge(2,1),merge(3,1)` 和 `merge(3,1),merge(2,1)`，其他 `merge` 参数不同的方案与上述两种的其中一种是本质相同的（每次的 `fx,fy` 都一样）。

---

【数据范围】

**「本题采用捆绑测试」**

- $\texttt{Subtask 1(10 pts)：}T=1,\ n\le 10$；
- $\texttt{Subtask 2(30 pts)：}T=10^2,\ n\le 10^3$；
- $\texttt{Subtask 3(60 pts)：}$无特殊限制。

对于 $100\%$ 的数据，满足 $1\le T\le 10^5,\ 1\le n\le 10^9$。

## 样例 #1

### 输入

```
4
3
20
8492
114514```

### 输出

```
3
61560
822256526
988192964
```

# 题解

## 作者：Abeeel51 (赞：22)

这道题非常有意思。

看这个数据范围你就知道要推式子吧。

题意：

一个并查集，最开始 $fa_i=i$。在这个数组进行多次带路径压缩的合并操作，保证每次合并的两个点 $i$ 和 $j$ 的关系是 $fa_i \ne fa_j$。给定 $fa$ 的大小 $n$，有多少种 $fa$ 数组可以通过两次合并得到，取余 $998244353$。

那么考虑所有不可以的建树方法：

- 一个 $\text{father}$ 有三个 $\text{son}$

这样就会有 $6$ 种操作方式，不可能满足题目。

- 一个非根的 $\text{father}$ 有两个 $\text{son}$

这样就有两种方式，如果再添加一条边则会出现四种操作方式，不可能满足题目。

也就是说

这棵构造的树一定是两种结构：

〇 $\leftarrow$ 〇 $\leftarrow$ 〇 $\leftarrow$ 〇

和

〇 $\leftarrow$ 〇 $\leftarrow$ 〇

$\uparrow$

〇

比较抽象，就是表示了两种建树方式，分别是一条直线和在根处分成两个叉。

当然，分了叉之后两条边长度就必须是 $1$。

如果叉的一条边长度为 $2$，那么这个树长这样：

〇 $\leftarrow$ 〇 $\leftarrow$ 〇

$\uparrow$

〇

单独的那条边可以穿插在 $\text{merge}$ 任意的位置，然而另一条则不是，就有三种顺序。

到这里我们知道上面的第二种结构只有一种可能性，就是：

〇 $\leftarrow$ 〇

$\uparrow$

〇

所以，大小为 $n$ 的并查集合并后只能有 $1$ 个三个点的树或者 $2$ 个两个点的树，再大就不可行了。

那么，整理公式：

〇 $\leftarrow$ 〇

〇 $\leftarrow$ 〇

或者

〇 $\leftarrow$ 〇

$\uparrow$

〇

是可行的。

第一种方案数 $\binom{n}{4} \times \frac{\binom{4}{2}}{2}\times2\times2$

第二种方案数 $\binom{n}{3} \times 3$

整理公式，得答案为：

$\frac{n(n-1)(n-2)^2}{2}$

每组样例都这样算，别忘了取模，还有，取错模可是 $40\text{pts}$ 哦！

代码来了，只给关键

```cpp
printf("%lld\n",1ll*(n-1)*n/2%mod*(n-2)%mod*(n-2)%mod%mod);
```
给个赞再走吧谢谢。

---

## 作者：Thunder_Lake (赞：12)

###### 蒟蒻第一次写题解，写的不好，见谅。

## Solution

~~看到这个题第一眼就知道这肯定不是并查集的题~~

把题意转化一下：```fa``` 数组进行**两次** ```merge``` 操作可以得到几种序列

更简单一点，可以看成把 ```fa``` 数组中的两个元素分别改变成另一个元素，由多少种不同的方案

把玩一下样例我们发现只有两种情况：


- 把两个元素改成一样的值

- 把两个元素改成两个不一样的值


讨论一下这两种情况


------------

第一种情况：

第一个被修改元素时有 $n$ 个位置可以选，修改的值不能选择该元素的值，所以有 $n - 1$ 个值可以修改。

第二个被修改元素不能选第一个元素，也不能选第一个元素被修改的那个值，所以有 $n - 2$ 个位置可以选，被修改的值和第一个元素被修改的值一样，只有一种情况。

有可能会出现重复情况，注意去重

根据乘法原理可得：

$$ \frac {n(n - 1)(n - 2)}{2} $$

------------

第二种情况

第一个被修改元素时有 $n$ 个位置可以选，修改的值不能选择该元素的值，所以有 $n - 1$ 个值可以修改。

第二个被修改元素不能选第一个元素，也不能选第一个元素被修改的那个值，所以有 $n - 2$ 个位置可以选，被修改的值不能选该元素、第一个被修改的元素，修改第一个元素的值，所以有 $n - 3$ 种情况。

根据乘法原理可得：

$$ \frac {n(n - 1)(n - 2)(n - 3)}{2} $$


最后把这两种情况的方案数加起来就是最终答案:

$$ \frac {n(n - 1)(n - 2)}{2} + \frac {n(n - 1)(n - 2)(n - 3)}{2} $$

化简得：

$$ \frac {n(n - 1)(n - 2)^{2}}{2} $$

代码注意一下精度就好了

## AC Code

```
#include <iostream>
#define ull unsigned long long

using namespace std;

const ull mod = 998244353;
ull T, n;

ull work(ull n){
	ull res = 0;
	res += n;
	res *= (n - 1);
	res /= 2;
	res %= mod;
	res *= (n - 2);
	res %= mod;
	res *= (n - 2);
	res %= mod;
	
	return res;
}

int main(){
	cin >> T;
	while(T--){
		cin >> n;
		cout << work(n) << endl;
	}
	
	
	return 0;
}
```

---

## 作者：gyc18 (赞：7)

此题解为官方题解

不难发现最终一定是 2 个大小为 2 的树，或者 1 个大小为 3 的菊花，其余都没有动过。从而答案是 $\dfrac{n(n-1)(n-2)^2}{2}$。

证明：

首先容易发现任意森林都有至少 1 种方式建立：自下而上一个一个挂，不发生路径压缩。

我们尝试分析一下这个树最后是什么结构。

**Observation 1**：不能出现一个点有 3 个孩子。

**证明**：显然如果有 3 个孩子就贡献了 6 种顺序，就一定不是恰好 2 个操作序列了。

**Observation 2**：不能出现一个非根的点有 2 个孩子。

**证明**：考虑方案数最小的情况肯定是直接就是这样一个结构，以

```plain
1 2
2 3
2 4
```

为例。

首先直接自下而上的有两种。

然后我可以先把 4 挂到 3 上，再把 3 挂到 2 上，然后 merge(4,1)，此时 4 由于路径压缩会挂到 2 上，然后 2 再会挂到 1 上，这就又多出一种，对称的也还有一种。

因此这个结构会贡献 4 种操作序列，从而不能出现。

---

那么到这一步，每一个树必须要么是一条链，要么是根上挂两条链。

**Observation 3**：根分叉之后的两个子链长度必须都是 1。

**证明**：否则取长度 >1 的子链的前 2 个点，这 3 条边有 3 种顺序，从而不能出现。

到这一步，每一个树必须要么是一条链，要么是一个 3 个点的菊花。

**Observation 4**：所有大小 $\geq 2$ 的树里面，要么只能有 1 个大小 $\geq 3$ 的树，要么只能有 2 个大小 $=2$ 的树。

**证明**：如果有一个大小 $\geq 3$ 的树，那么任意一个和它不连通的树的操作都有 $\geq 3$ 个位置可以放，从而方案数爆炸；如果有 3 个大小 $=2$ 的树，那么它们的顺序有 6 种方案，爆炸。

所以我们要么选四个点然后组成两对有序对，要么选三个点然后选一个点当根。前者方案数是 $\dbinom{n}{4}\times \dfrac{\binom{4}{2}}{2}\times 2\times 2$，后者方案数是 $\dbinom{n}{3}\times 3$。整理得到答案为 $\dfrac{n(n-1)(n-2)^2}{2}$。

---

## 作者：Joker_1212 (赞：4)

# P8378 [PFOI Round1] Two Sequences

本蒟蒻的第一篇C++题解

[在博客中食用更佳](https://www.luogu.com.cn/blog/Joker-1212/p8378-cpp)

## 题意

[原题传送门](https://www.luogu.com.cn/problem/P8378)

并查集代码如下
```cpp
inline int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    fx=find(x),fy=find(y);
    if(fx==fy)return;fa[fx]=fy;
}
```
初始时对于每个$n$有`fa[x]=x`。且`merge`时`return`语句绝不会执行。

现在问：有多少个`fa`数组，能还原成两种操作序列？（两个操作序列不同，当且仅当某次 `merge` 时的变量 `fx,fy` 至少有一个不同。）

数据范围：$1 \leqslant T \leqslant 10^5,\;1 \leqslant n \leqslant 10^9$

不懂并查集的戳：[并查集_百度百科](https://baike.baidu.com/item/%E5%B9%B6%E6%9F%A5%E9%9B%86/9388442?fr=aladdin)

------------------------------------------

## 分析

首先可以明确：每调用一次`merge(x, y)`，就会将`fa[x]`变为`fa[y]`的值，即将一个值变为其他值。

### Step $1$

先思考一下：`merge`函数到底被调用了几次？

首先注意到：对于$n$次调用，每一次调用都可以和其他调用更换位置，形成新的操作序列，因此如果调用了$n$次`merge`，则会有$n!$种不同的序列。然后根据题意可得: 只有两种不同的操作序列。因此`merge`一共调用了$2$次

### Step $2$

再思考一下：`merge`函数有什么特殊限制？
`fx`和`fy`肯定不会相等，否则就会执行`return`语句，不符合条件。这意味着每执行一次`merge`，都会使`fa`中的一个值变为`fa`中的其他值。

### Step $3$

最后就可以推导公式了。

要调用两次`merge`，有两种方案：

方案一：从$n$个值中选取$2$个($\mathrm{C}_n^2$)值，变成剩下$n-2$个值中的任意$1$个($\mathrm{C}_{n-2}^1$)
。用排列组合知识可得：此时的`fa`数组数（记为$f_1(n)$）的表达式为：

$$f_1(n) = \mathrm{C}_n^2 + \mathrm{C}_{n - 2} ^ 1 = \frac{n(n - 1)(n - 2)}{2}$$


方案二：从$n$个值中选$1$个($\mathrm{C}_n^1$)值，变为剩下的$n-1$个值中的任意一个($\mathrm{C}_{n-1}^1$)。再从剩下的$n - 2$个值中选取一个($\mathrm{C}_{n-2}^1$)，变为剩下的$n-3$值中的一个($\mathrm{C}_{n-3}^1$)。同时因为这两次操作互换后`fa`数组仍然相同，所以还要除以$2$。用排列组合知识可得：此时的`fa`数组数（记为$f_2(n)$）的表达式为：

$$
f_2(n)=\frac{\mathrm{C}_n^1+\mathrm{C}_{n - 1}^1+\mathrm{C}_{n - 2}^1+\mathrm{C}_{n - 3}^1}{2}
=\frac{n(n - 1)(n - 2)(n - 3)}{2}
$$

综上所述：对于元素个数为$n$的序列，可能的`fa`数组数（记为$f(n)$）为

$$
f(n)=f_1(n) + f_2(n)
= \frac{n(n - 1)(n - 2)}{2}+\frac{n(n - 1)(n - 2)(n - 3)}{2}
$$

到了这一步，我们便能写出代码

---

## 代码

`AC` Code 如下。注释在代码里。最后只有一句话

> 莫抄袭，棕了少年名，空悲切

```cpp
#include <bits/stdc++.h> //可以换成#include<cstdio>
using namespace std;
#define MOD 998244353

// 快读，不解释
int read()
{
    char s = getchar();
    int ans = 0;
    while (s < '0' || s > '9')
        s = getchar();
    while (s >= '0' && s <= '9')
    {
        ans = ans * 10 + s - '0';
        s = getchar();
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)   //不解释
    {
        long long n;
        scanf("%lld", &n);
        // 为了一步一取模，先对n的奇偶进行判断，把2除进n或n-1中
        if (n % 2 == 0)
            printf(
                "%lld\n",
                ((n / 2) * (n - 1) % MOD * (n - 2) % MOD +
                 (n / 2) * (n - 1) % MOD * (n - 2) % MOD * (n - 3) % MOD) %
                    MOD);
        else
            printf(
                "%lld\n",
                (n * ((n - 1) / 2) % MOD * (n - 2) % MOD +
                 n * ((n - 1) / 2) % MOD * (n - 2) % MOD * (n - 3) % MOD) %
                    MOD);
    }
    return 0;
}
```

最后，都看到这里了，不点个赞再走吗？

---

## 作者：nullqtr_pwp (赞：3)

# 	[PFOI Round1] Two Sequences 题解

先看看这个树最后能是什么结构？注意到孩子挂靠在父节点的顺序可以随意改变，设某个结点有 $k$ 个孩子，那么就有 $k!$ 种 merge 方式（全排列），显然，$k\le 2$，那么 $k=1$ 时就是一条链；考虑 $k=2$ 时，假设树不是菊花，假设 $fa_a=a,fa_b=a,fa_c=b,fa_d=b$，显然，这个结构有大于 $2$ 种方案。那么树就是一个菊花。

再注意到一个性质（A）：子链长度 $=1$，若子链长度 $\ge2$，不妨设子链长度为 $2$，设为 $fa_a=a,fa_b=a,fa_c=b$，那么这 $3$ 条边有 $3$ 种顺序，超。

考虑单棵树为菊花时的情况，不难发现大小必然是 $3$，（否则在大小 $\ge 4$ 时，其余子节点挂在根节点的情况至少有 $A_n^n\ge6$ 种，故不成立）即为 $fa_a=a,fa_b=a,fa_c=a$，而 $merge(a,b)$ 与 $merge(a,c)$ 的顺序可以对调，这样的话选出 $a,b,c$ 有 $C_n^3$ 种，选一个数当根节点有 $3$ 种，故此种情况下的数目为 $3\times C_n^3$ 种。

考虑树为一条链的情况，由性质 A，大小必为 $2$，那么为了有两种操作方式，还需要一个链，所以设为 $fa_a=a,fa_b=a,fa_c=c,fa_d=c$，那么选出 $a,b,c,d$ 有 $C_n^4$ 种，连接 $2$ 条边且保证每个节点的度恰好为 $1$ 有 $3$ 种，各自选父节点有 $2$ 种，此情况下有 $C_n^4\times3\times2^2=12\times C_n^4$ 种情形。

综上，本题答案为 $3\times C_n^3+12\times C_n^4\mod 998244353$ 

本题的代码实现还是很有意思的，要边算边取模，否则 $10^9$ 的数据范围算的时候就爆 ```long long``` 了。

赛时 AC 代码：
```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
inline int read(){
	register int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int mod=998244353;
int t,n;
signed main(){
	t=read();
	while(t--){
		n=read();if(n==3){puts("3");continue;} 
		int ans=0;
		ans+=((((n*(n-1))>>1)%mod)*(n-2))%mod;
		ans+=((((n*(n-1))>>1)%mod)*((n-2)*(n-3)%mod))%mod;
		printf("%lld\n",ans%mod);
	}
}
```


---

## 作者：5793__qwq (赞：1)

### 推柿子！！！
>对于 $100\%$ 的数据，满足 $ 1\le T\le 10^5,\ 1\le n\le 10^9$。

这数据范围就只可能~~打表~~推柿子。

### 分析：

这题有两种情况：

1. 两个点并到同一个祖先。如这样： ![](https://cdn.luogu.com.cn/upload/image_hosting/wzj75b0u.png)
2. 两个不相关的合并。如这样： ![](https://cdn.luogu.com.cn/upload/image_hosting/kl5mupbn.png)

### 计算：

第一种情况：

> 先选 $3$ 个点，有 $C^{3}_{n}= \frac{n\times(n-1)\times(n-2)}{6}$ 种可能
    
> 再合并，有 $3$ 种合并，一共为 $\frac{n\times(n-1)\times(n-2)}{2}$ 种可能
   
第二种情况：
  
> 先选 $4$ 个点,有 $C^{4}_{n}= \frac{n\times(n-1)\times(n-2)\times(n-3)}{24}$ 种可能
    
> 再合并，有 $6\times2$ 种合并，一共为    $\frac{n\times(n-1)\times(n-2)\times(n-3)}{2}$ 种可能

总计 $\frac{n\times(n-1)\times(n-2)+n\times(n-1)\times(n-2)\times(n-3)}{2}=\frac{n\times(n-1)\times(n-2)^{2}}{2}$ 种可能。

### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long t,n;
int main(){
	cin>>t;
	for(int i=1;i<=t;++i){
		cin>>n;
		cout<<n*(n-1)/2%mod*(n-2)%mod*(n-2)%mod<<'\n';
	}
	return 0;
}
```

	

---

## 作者：c7h5n3o6_tnt (赞：1)

# ~~MOer 教你推式子~~

## 前置知识

- 并查集（至少了解描述并查集的图是怎么画的）；

- 排列组合 ~~（OIer 小奥应该都没少学吧）~~。

## 公式推导

### 分析情况：

首先，**描述这个并查集的图不能拆分成 $2$ 棵以上树**（不包括单点），否则显然有至少 $A_3^3=6$ 种操作序列。

其次，**任意其中的点，度数都不会大于 $2$。**

> 随便举一个例子：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/nnyb0o2c.png)
>
> 图中的节点 $2$ 有三条边与之相连，我们可以构造三种操作序列形成这种图：
>
> - `merge(3,2);merge(4,3);merge(2,1)`
>
> - `merge(3,2);merge(4,2);merge(2,1)`
>
> - `merge(4,2);merge(3,2);merge(2,1)`
>
>（其实还有，就不列举了）。

所以我们得到一个结论：**这个并查集，由最多两条链组成。**

我们现在讨论一条特殊的链：

![](https://cdn.luogu.com.cn/upload/image_hosting/reew0vs8.png)

这条链特殊在：没有任何两条边指向同一个节点。

容易发现，对于这一种链，**只有一种操作序列**：`merge(1,2);merge(2,3);merge(3,4)`。

然后，我们猜测：是否对于任何只含有两条具有这种性质的链，就有 $A_2^2=2$ 种操作序列呢？

显然是错误的。

> 比如说：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/0oayofj3.png)
>
> 这个图有三种操作序列：
>
> - `merge(4,5);merge(1,2);merge(2,3)`
>
> - `merge(1,2);merge(2,3);merge(4,5)`
>
> - **`merge(1,2);merge(4,5);merge(2,3)`**
>
> 换句话说，它没有固定操作的顺序，**甚至可以一条链建了一半暂停，去建另一条链。**

于是我们知道，它只能含有两条不相连的边：

![](https://cdn.luogu.com.cn/upload/image_hosting/kanszbs5.png)

这是可行的。

它有两种操作序列：

- `merge(1,2);merge(3,4)`
- `merge(3,4);merge(1,2)`

还有一种情况：这条链中，**有两条边指向同一个节点**：

![](https://cdn.luogu.com.cn/upload/image_hosting/zbi52h9l.png)

这就是可行的，因为节点 1 和节点 3 谁先指向 2 无关紧要。

**但是，这就是不符合要求的：**

![](https://cdn.luogu.com.cn/upload/image_hosting/ku8zqkjq.png)

原因很相似：可以半条链建了一半暂停，去建另半条链。

**于是，我们得知，只有这两种情况，才能刚好有两种操作序列：**

![](https://cdn.luogu.com.cn/upload/image_hosting/kanszbs5.png)![](https://cdn.luogu.com.cn/upload/image_hosting/zbi52h9l.png)

### 推导公式：

- 对于左图的情况：我们构造四元数对 $(1,2,3,4)$ 表示左图（节点 $1$ 指向节点 $2$，节点 $3$ 指向节点 $4$）。

  我们发现，这样的四元数对共有 $A_n^4$ 个。

  但是，显然，数对 $(1,2,3,4)$ 和 $(3,4,1,2)$ 是等价的。

  所以，共有 $\dfrac{A_n^4}{2}$ 个。 

- 对于右图的情况：我们构造三元数对 $(1,2,3)$ 表示左图（节点 $1$ 指向节点 $2$，节点 $3$ 也指向节点 $2$）。

  我们发现，这样的四元数对共有 $A_n^3$ 个。

  但是，显然，数对 $(1,2,3)$ 和 $(3,2,1)$ 是等价的。

  所以，共有 $\dfrac{A_n^3}{2}$ 个。 

于是，两种情况加起来，**共有 $\dfrac{A_n^4}{2}+\dfrac{A_n^3}{2}$ 个**。

但是，这个公式，计算机不便计算，于是我们可以改进一下：

$$\begin{aligned}\dfrac{A_n^4}{2}+\dfrac{A_n^3}{2}&=\frac{n\cdot(n-1)\cdot(n-2)\cdot(n-3)}{2}+\frac{n\cdot(n-1)\cdot(n-2)}{2}\\&=\frac{n\cdot(n-1)\cdot(n-2)^2}{2}\end{aligned}$$

借助这个公式，我们就可以愉快地敲代码了。



## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353

int main(){
	long long n,t;
	cin >> t;
	while(t--){
		cin >> n;
		cout << n * (n - 1) / 2 % mod * (n - 2) % mod * (n - 2) % mod << endl;
	}
	return 0;
}
```

这里有一点需要注意一下：我在计算 $n\cdot(n-1)$ 后除了 $2$，这有一个好处，就是 $n\cdot(n-1)$ 一定是偶数，免去了计算完再除 $2$ 的麻烦。

---

## 作者：Silence_World (赞：0)

# 思路

比较简单的一道题，非常重要的一点是精度（挂了八九次 QAQ）我们分析一下题目，其实题目就是很明了的告诉我们给我们一堆数，让我们从中选两个数换成其他的数，问最后方法有几种，分类讨论。

两个改成相同数字：第一个数可以是所有的数，为 $n$ 种，第二个不能选相同的，可知为 $n-1$ 种，共 $n-2$ 个数可变，乘法原理可知，结果为 $n(n-1)(n-2)$，但是注意一点，两个数内部是无排列顺序的，即：

$$\frac{n(n-1)(n-2)}{A^2_{2}}$$
即：

$$\frac{n(n-1)(n-2)}{2}$$

不同的也是同理，另外一个也选上多乘一个 $(n-3)$，即：

$$\frac{n(n-1)(n-2)(n-3)}{2}$$

相加得：

$$\frac{n(n-1)(n-2)}{2}+\frac{n(n-1)(n-2)(n-3)}{2}$$

提取公因式得：

$$\frac{n(n-1)(n-2)^2}{2}$$

得到答案，结束。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
#define mod 998244353
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int n1=n;
		n*=(n1-1);
		n/=2;
		n%=mod;
		n*=(n1-2);
		n%=mod;
		n*=(n1-2);
		n%=mod;
		cout<<n<<endl;
	}
	return 0;
} 
```


---

## 作者：wanghx (赞：0)

#### [题目链接](https://www.luogu.com.cn/problem/P8378)
并查集:

在一些有 $ N $ 个元素的集合应用问题中，我们通常是在开始时让每个元素构成一个单元素的集合，然后按一定顺序将属于同一组的元素所在的集合合并，其间要反复查找一个元素在哪个集合中

并查集代码~~题目中给了~~
```cpp
inline int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
inline void merge(int x,int y){
    fx=find(x),fy=find(y);
    if(fx==fy)return;fa[fx]=fy;
}
```
刚开始 $ fa_{x}=x;$


我们可以发现：

每调用一次  $merge(x, y)$ ，就会将 $fa_{x}$ 变为 $fa_{y}$ 的值，即将一个值变为其他值。

$merge$ 函数有什么特殊限制?
$fx$ 和 $fy$ 肯定不会相等，否则就会执行 $return$ 语句。
这意味着每执行一次 $merge$，都会使 $fa$ 中的一个值变为 $fa$ 中的其他值。
本题要边算边取模

然后 是~~你们最爱的~~代码
```cpp
#include<bits/stdc++.h> 
#define int unsigned long long 
#define il inline
using namespace std;
il int read(){   //快读
	int ans=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}
const int mod=998244353;
int t,n;
signed main(){
	t=read();
	while(t--){
		n=read();
                if(n==3){puts("3");continue;} 
		int sum=0;
		sum+=((((n*(n-1))>>1)%mod)*(n-2))%mod;
		sum+=((((n*(n-1))>>1)%mod)*((n-2)*(n-3)%mod))%mod;
		printf("%llu\n",sum%mod);
	}
	return 0;
}
```
#### ~~这题样例太臭了~~


---

## 作者：Ilovechemistry_AFO (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8378)

**题意**

给定一个并查集的 $fa$ 数组的大小 $n$ ，求有几种 $fa$ 序列可以恰好还原 $2$ 种操作序列。

**分析**

很容易可以分析出，原序列必然只进行两次操作，且父亲被修改的两个节点不同。

让我们先排除一些不可能的情况：
   
  	
$1.$ 每个节点的子节点数小于 $3$ ：若至少有一个节点有至少 $3$ 个子节点，这样的子节点可以至少贡献 $s!$ 种情况，其中 $s$ 为该节点的子节点数，易知总情况数会大于等于 $6$ 。
   
   
 $2.$ 由 $1$ ，子节点数为 $2$ 的节点数至多有 $1$ 个:共两种原序列，因此至多有 $2\div2!=1$ 个这样的节点。
   
   
$3.$ 根节点子节点数为 $2$ 的子树的深度小于等于 $2$ ：若深度大于等于 $3$ ，此棵树至少贡献 $3$ 种顺序（此时树的形态为根节点的儿子只有一个有一个儿子）。
   
   综上所述，该序列应满足仅有两节点的父节点发生变化，且改变成的父节点可以相同。

因此，先选出两个节点 $x$ 和 $y$ ，再任意选出两个节点即可。

由上述分析，共有 $C_n^2$ $\times$ $(n-2)^2$ $=$ $\dfrac{n(n-1)(n-2)^2}{2}$ 种序列。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long n,t;
long long ksm(long long a,long long  b){
	long long ans=1;
	while(b){
		if(b&1)
		ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}//赛时用了快速幂
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		printf("%lld\n",(long long)(n*(n-1)/2%mod*((n-2)*(n-2)%mod))%mod);
	}
	return 0;
}
```

感谢阅读！

---

## 作者：V1mnkE (赞：0)

因为题目要求是：只能按两种方法得到的序列。变换两个位置的先后次序即为两种方法，若变换三个及以上位置，则先后次序会大于两种。

因此，我们需要变换两个位置即可得到答案，我们需要从 $n$ 个位置中挑选出这两个位置，即 $C_n^2$。

具体变化，第一个位置只能变成剩下的 $n-2$ 个位置的数，因为如果第一个位置变成该位置的数，会不符合题意。若第一个位置变换成第二个位置的数时，这时候该方法唯一了，两个位置变换的次序不能颠倒了。故只能变成剩下的 $n-2$ 个位置。同理，第二个位置也可以变换成剩下 $n-2$ 个位置的数。

因此得到答案 $ans = \frac {n(n-1)(n-2)^2}2$。

注意：使用 ``long long`` 类型，同时在每次乘法后进行 ``%`` 操作。除以 $2$ 的操作应与 $n\times (n-1)$ 一起处理，因为这样不会出现小数。

## 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
   long long t,n;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        if(n==3)cout<<3<<endl;
        else{
            long long k=0,g=0;
            k=((n-2)*(n-2))%998244353;
            g=(n*(n-1)/2)%998244353;
            cout<<(k*g)%998244353<<endl;
        }
    }
    return 0;
}
```

---

## 作者：赵悦岑 (赞：0)

# P8378 [PFOI Round1] Two Sequences 题解

[P8378 [PFOI Round1] Two Sequences](https://www.luogu.com.cn/problem/P8378)

## 题意

这道题题面不怎么好理解，我们来分析一下：

> 调皮的小 x 见他不在机房，每天都在并查集上不断 merge。 注意到小 x 不喜欢 ==，他觉得这特别像他的眼睛，于是他不会使 merge 函数在第二行的条件语句中被 return，否则他会十分气愤。

这一句表示，操作序列中每一个操作的 `fx,fy` 都一定不同，也就是每一次 `merge` 均会发生一次合并。

>现在的已知信息就只有最终的 $fa$ 数组了。 而 syzf2222 希望还原小 x 的操作序列（即若干次按顺序进行的 `merge` 操作）。由于他名字里有很多个 2 而且本人也非常 2 ，他希望知道对于每一天，有多少个 $fa$ 数组恰好能被还原成两种操作序列，答案对 $998244353$ 取余数。

每一种操作序列一定会对应一个 $fa$ 数组，我们就需要求出有多少个 $fa$ 数组**有且仅能由两种操作序列得到**。

>两个操作序列不同，当且仅当某次 `merge` 时的变量 `fx,fy` 至少有一个不同。

这里表示两次 `merge`是否相同不取决于它所操作的点，**而是它所操作的连通块**。

注意！这里的 $fa$ 数组不是在最后对于每个数 `find` 得到的数组，也就是 $fa_i$ 数组**并不一定就是 $i$ 所在连通块的编号**，因为有可能 $fa_i$ 数组**没有更新**，$fa_i$ 应该保持最后一次 `find` 或 `merge` 的结果。

我们来看一下样例：$fa$ 为 $[1,1,1]$ 的时候，有 ` merge(2,1)`,`merge(3,1)` 和 `merge(3,1)`,`merge(2,1)` 两种。

肯定有人想问：`merge(2,1)`,`merge(3,2)` 为什么不行，因为它与第一种情况**所操作的连通块是相同**的，$fx,fy$ 分别是 (2,1),(3,1)。

肯定也有人想问：`merge(3,2)`,`merge(2,1)` 为什么不行,这种情况的 $fx,fy$ 虽然和之前不同，但是它得到的 $fa$ 数组是 $[1,1,2]$ ，因为 $fa_3$ 在第二次操作后**并没有更新**！

## 思路

我们把整个图分成许多连通块，显然，**总的情况数不少于所有连通块的情况数**，也就是说不能有任何一个连通块情况多于 $2$ 个。

对于每个连通块，我们先分一个类：$fa$ 数组为**最新的**和**不为最新的**两种情况

### $fa$ 为最新

在这种情况中，由于 $fa$ 数组是最新的，说明 $fa$ 内所有数都是相同的（注意，现在讨论的都只针对一个连通块）。显然，连通块中**点个数越多，情况越多**。社总共 $m$ 个点，显然，如果所有点都直接连到根节点所在连通块，就会有 $m-1$ 个 `merge`，而这些操作是没有顺序的，所以总情况就是 $(m-1)!$，因此，$m$ 多于 $3$ 时，总情况数一定多于 $2$。而我们可以验证 $m=2,3$ 均是合法的。

其中 $m=2$ 时有 $1$ 种操作序列，每个序列中均有 $1$ 个操作（称其为连通块 $1$）。

$m=3$ 时有两种操作序列 $2$ 种序列，每个操作序列中均有 $2$ 个操作（称其为连通块 $2$）。

### $fa$ 不为最新

首先，$m=2$ 是不可能，只有 $m \geqslant 3$ 时有可能。

如果要满足不为最新，一定有一条链长度不小于 $3$，也就是不少于 $2$ 个操作，而如果有多条链，情况数一定多于 $2$，不可能，因此整个连通块就是一条链。（称其为连通块 $3$）

### 合并

我们已经有 $3$ 中合法的连通块了，我们要把他们组合起来：

如果使用连通块 $1$，由于它已经有两种操作序列了，所以再添加任何一个连通块情况数一定增加，所以只能有 $1$ 个连通块 $1$。

如果使用连通块 $2$，显然它不能和连通块 $1$ 组合。如果用 $2$ 个连通块 $2$，由于我们只需要保证连通块内部操作的相对顺序不变，不同连通块的操作顺序可以改变、交叉，所以共有 $2$ 种情况，符合。而和连通块 $3$ 搭配，由于连通块 $3$ 操作数不少于 $2$，总序列数一定多于 $2$，不符。

如果使用连通块 $3$，由于它有不少于 $2$ 个操作，只添加 $1$ 个操作都有不少于 $3$ 种的情况，无法使用。

于是我们得到了两种图：$1$ 个连通块 $1$ 和 $2$ 个连通块 $2$。

## 计算

然后，我们运用~~小学~~数学知识，来计算总情况数：

首先计算第一种情况，首先要选出 $3$ 个点，情况数为

$$\frac{n(n-1)(n-2)}{6}$$

对于任意 $3$ 个点，要选出 $1$ 个作为根节点，其它 $2$ 均指向它，所以有 $3$ 种情况，总共就是

$$\frac{n(n-1)(n-2)}{2}$$

然后是第二种情况，首先选出 $4$ 个点

$$\frac{n(n-1)(n-2)(n-3)}{24}$$

然后选 $2$ 个根节点，共 $6$ 种

$$\frac{n(n-1)(n-2)(n-3)}{4}$$

剩下的点各选一个连通块加入

$$\frac{n(n-1)(n-2)(n-3)}{2}$$

总共的情况就是

$$\frac{n(n-1)(n-2)(n-3)+n(n-1)(n-2)}{2} $$

也就是

$$\frac{n(n-1)(n-2)^2}{2} $$

## code

```cpp
#include<cstdio>
#include<iostream>
typedef long long ll;
const ll P=998244353;
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int main()
{
    int T=read();
    while(T--)
    {
        ll n=read();
        printf("%lld\n",(n*(n-1)/2)%P*(n-2)%P*(n-2)%P);
    }
    return 0;
}
```

---

