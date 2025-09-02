# Monoblock

## 题目描述

Stanley has decided to buy a new desktop PC made by the company "Monoblock", and to solve captcha on their website, he needs to solve the following task.

The awesomeness of an array is the minimum number of blocks of consecutive identical numbers in which the array could be split. For example, the awesomeness of an array

- $ [1, 1, 1] $ is $ 1 $ ;
- $ [5, 7] $ is $ 2 $ , as it could be split into blocks $ [5] $ and $ [7] $ ;
- $ [1, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9] $ is 3, as it could be split into blocks $ [1] $ , $ [7, 7, 7, 7, 7, 7, 7] $ , and $ [9, 9, 9, 9, 9, 9, 9, 9, 9] $ .

You are given an array $ a $ of length $ n $ . There are $ m $ queries of two integers $ i $ , $ x $ . A query $ i $ , $ x $ means that from now on the $ i $ -th element of the array $ a $ is equal to $ x $ .

After each query print the sum of awesomeness values among all subsegments of array $ a $ . In other words, after each query you need to calculate $ $$$\sum\limits_{l = 1}^n \sum\limits_{r = l}^n g(l, r), $ $  where  $ g(l, r) $  is the awesomeness of the array  $ b = \[a\_l, a\_{l + 1}, \\ldots, a\_r\]$$$.

## 说明/提示

After the first query $ a $ is equal to $ [1, 2, 2, 4, 5] $ , and the answer is $ 29 $ because we can split each of the subsegments the following way:

1. $ [1; 1] $ : $ [1] $ , 1 block;
2. $ [1; 2] $ : $ [1] + [2] $ , 2 blocks;
3. $ [1; 3] $ : $ [1] + [2, 2] $ , 2 blocks;
4. $ [1; 4] $ : $ [1] + [2, 2] + [4] $ , 3 blocks;
5. $ [1; 5] $ : $ [1] + [2, 2] + [4] + [5] $ , 4 blocks;
6. $ [2; 2] $ : $ [2] $ , 1 block;
7. $ [2; 3] $ : $ [2, 2] $ , 1 block;
8. $ [2; 4] $ : $ [2, 2] + [4] $ , 2 blocks;
9. $ [2; 5] $ : $ [2, 2] + [4] + [5] $ , 3 blocks;
10. $ [3; 3] $ : $ [2] $ , 1 block;
11. $ [3; 4] $ : $ [2] + [4] $ , 2 blocks;
12. $ [3; 5] $ : $ [2] + [4] + [5] $ , 3 blocks;
13. $ [4; 4] $ : $ [4] $ , 1 block;
14. $ [4; 5] $ : $ [4] + [5] $ , 2 blocks;
15. $ [5; 5] $ : $ [5] $ , 1 block;

 which is $ 1 + 2 + 2 + 3 + 4 + 1 + 1 + 2 + 3 + 1 + 2 + 3 + 1 + 2 + 1 = 29 $ in total.

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
3 2
4 2
3 1
2 1
2 2```

### 输出

```
29
23
35
25
35```

# 题解

## 作者：liangbowen (赞：17)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1715C)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1715c)

简单的数学题。

## 思路

每次只变一个数，因此考虑在短时间内计算：**每个位置的数**产生的贡献。

容易发现以下的条件：

+ 不管 $a_i$ 是什么，当它作为一个子串的首项时，块数一定会加一。共有 $(n - i + 1)$ 个串的首项是 $a_i$。
+ 如果 $a_i \ne a_{i-1}$，所有包含 $a_i$ 与 $a_{i+1}$ 的子串，块数都加一。乘法原理，头有 $(i - 1)$ 个位置可以选（$0$ 到 $i - 1$），尾有 $(n - i + 1)$ 个位置可以选（$i$ 到 $n$），共 $(i - 1) \times (n - i + 1)$。

那么，我们就可以知道 $a_{i - 1}$ 与 $a_i$ 间产生的贡献是多少。

```cpp
typedef long long LL;
LL calc(int i) //统计 a[i-1]与a[i]间产生的贡献
{
	LL k = n - i + 1; //以 a[i] 为头的所有子串，不管a[i-1]与a[i]相不相同，都要计算贡献。 
	if (a[i-1] == a[i]) return k;
	return 1ll * (i - 1) * (n - i + 1) + k; //不同才会产生贡献
}
```

然后，我们可以计算：原本的 $a$ 数组有多少贡献。这非常简单。

```cpp
LL sum = 0;
for (int i = 1; i <= n; i++) a[i] = read();
for (int i = 1; i <= n; i++) sum += calc(i);
```

那么，怎样在短时间内计算 $a_i$ 改变后的值呢？只需要：

1. 减去 $a_{i-1}$ 与 $a_i$ 产生的贡献，减去 $a_i$ 与 $a_{i + 1}$ 产生的贡献。因为它们过一会会变。
2. 更改 $a_i$。
3. 重新加上 $a_{i-1}$ 与 $a_i$ 产生的贡献，以及加上 $a_i$ 与 $a_{i + 1}$ 产生的贡献。

然后再输出结果即可。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define space putchar(' ')
#define endl putchar('\n')
using namespace std;
typedef long long LL;
int read()
{
	char op = getchar(); int x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
void write(LL x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
int n, m, a[100005];
LL calc(int i) //统计 a[i-1]与a[i]间产生的贡献
{
	LL k = n - i + 1; //以 a[i] 为头的所有子串，不管a[i-1]与a[i]相不相同，都要计算贡献。 
	if (a[i-1] == a[i]) return k;
	return 1ll * (i - 1) * (n - i + 1) + k; //不同才会产生贡献
}
int main()
{
	n = read(), m = read();
	LL sum = 0;
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) sum += calc(i);
	while (m--)
	{
		int i = read(), k = read(); //a[i] = k
		sum -= calc(i), sum -= calc(i+1);
		a[i] = k;
		sum += calc(i), sum += calc(i+1);
		write(sum), endl;
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Zigh_Wang (赞：11)

# 题面
[CF原版](https://www.codeforces.com/contest/1715/problem/C)
[洛谷中文题面](https://www.luogu.com.cn/problem/CF1715C)

# 分析
#### 预处理
先考虑在没有修改的情况下的初值，下面以 $\{1, 2, 2, 4, 5\}$ 为例：

我们可以先处理从 $1$ 开始的贡献，这点很显然。

我们再观察从下图中 第 $i$ 行 到 第 $i + 1$ 行 的和贡献变化 (下图中第 $i$ 行第 $j$ 列表示从 $i$ 到 $j$ 的贡献)，我么可以发现，如果 $a[i] = a[i  +1]$ 那么从这两行的**差值就为 1**，而如果 $a[i] \neq a[i + 1]$，则这两行的**差值就为 i**。
![在这里插入图片描述](https://img-blog.csdnimg.cn/4acd51dedc324bad80694955e09dccb8.png)
```cpp
for(int i = 1; i <= n; i++) {
	a[i] = inpt();
	if(a[i] != a[i - 1])
		nw++;
	ans += nw, tmp += nw;
}
for(int i = 2; i <= n; i++) {
	if(a[i] == a[i - 1]) {
		tmp--;
		ans += tmp;
	}else {
		tmp -= n - i + 2;
		ans += tmp;
	}
}
```
#### 修改
好了，现在预处理完了，那么修改怎么办呢？我们分成四种情况来讨论：
1. 如果我正在修改的数原来和他的**左边相同**，但修改后**不同**了：显然这样的情况我们需要对包含他的区间都 $+1$
![在这里插入图片描述](https://img-blog.csdnimg.cn/19c09238091d402ab0fbddfde0fbb667.png)
通过观察我们可以发现对答案的影响就是 $+ (i - 1) \times (n - i + 1)$；
```cpp
if(a[id] == a[id - 1] && x != a[id - 1])
	ans += 1ll * (id - 1) * (n - id + 1);
```
2. 如果我正在修改的数原来和他的**左边不同**，但修改后**相同**了：显然和上种情况相似，只是把所有 +1 改成 -1，则贡献是 $- (i - 1) \times (n - i + 1)$；
```cpp
if(a[id] != a[id - 1] && x == a[id - 1])
	ans -= 1ll * (id - 1) * (n - id + 1);
```
3. 如果我正在修改的数原来和他的**右边相同**，但修改后**不同**了：这种情况和第 1 种相似，但稍有不同
![在这里插入图片描述](https://img-blog.csdnimg.cn/575ccabbf4054e64aa753c4371a8c04d.png)
通过观察我们可以发现，贡献变成了 $+ i \times (n - i)$；
```cpp
if(a[id] == a[id + 1] && x != a[id + 1])
	ans += 1ll * id * (n - id);
```
4. 如果我正在修改的数原来和他的**右边不同**，但修改后**相同**了：与上种情况类似，贡献是 $- i \times (n - i)$。
```cpp
if(a[id] != a[id + 1] && x == a[id + 1])
	ans -= 1ll * id * (n - id);
```
**注意**：如果原来不同的情况，修改完之后与两边**都相同**了，可以发现会被上面四种情况完全覆盖。而其他几种情况则答案无变化。

# 代码实现
```cpp
//省略快读和头文件
int n, m;
int a[MAXN];
ll ans = 0, tmp = 0, nw = 0;

int main()
{
	n = inpt(), m = inpt();
	for(int i = 1; i <= n; i++) {
		a[i] = inpt();
		if(a[i] != a[i - 1])
			nw++;
		ans += nw, tmp += nw;
	}
	for(int i = 2; i <= n; i++) {
		if(a[i] == a[i - 1]) {
			tmp--;
			ans += tmp;
		}else {
			tmp -= n - i + 2;
			ans += tmp;
		}
	}
	
	while(m--) {
		int id = inpt(), x = inpt();
		
		if(a[id] == a[id - 1] && x != a[id - 1])//情况 1
			ans += 1ll * (id - 1) * (n - id + 1);
		if(a[id] != a[id - 1] && x == a[id - 1])//情况 2
			ans -= 1ll * (id - 1) * (n - id + 1);
		if(a[id] == a[id + 1] && x != a[id + 1])//情况 3
			ans += 1ll * id * (n - id);
		if(a[id] != a[id + 1] && x == a[id + 1])//情况 4
			ans -= 1ll * id * (n - id);
			
		a[id] = x;
		
		printf("%lld\n", ans);
	}
	
	return 0;
}


```

---

## 作者：luo_shen (赞：6)

**题意**  
有长度为 $n$ 的序列 $p$，每次操作给定两个数 $x,y$，将 $a_x$ 改为 $y$，求每次修改后 $\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}g(l,r)$，其中 $g(l,r)$ 在题目中有表示。  
**分析**  
根据块的定义，可以知道，若 $a_i\not= a_{i-1}$，则所有包含 $a_i$ 和 $a_{i-1}$ 的区间都会产生 $1$ 的贡献，总贡献为 $(n-i+1)\times(i-1)$。但对于每一个数对 $(l,r)$，$a_l$所在的块都不会计入答案，因此答案还要再加上 $\frac{n(n+1)}{2}$。那么如果修改 $a_x$ 的值，那么会变化的只有 $a_x$ 与 $a_{x-1}$ 一起产生的贡献和 $a_x$ 与 $a_{x+1}$ 一起产生的贡献。  
**代码**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans,n,m,a[100010],x,y;
signed main(){
    cin>>n>>m;
    ans=(n+1)*n/2;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        ans+=(a[i]!=a[i-1])*(n-i+1)*(i-1);
    }//对最初的序列进行统计
    while(m--){
        cin>>x>>y;
        ans-=(a[x]!=a[x-1])*(n-x+1)*(x-1);
        ans-=(a[x+1]!=a[x])*(n-x)*x;//去掉原贡献
        a[x]=y;
        ans+=(a[x]!=a[x-1])*(n-x+1)*(x-1);
        ans+=(a[x+1]!=a[x])*(n-x)*x;//计算新贡献
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Dregen_Yor (赞：5)

[博客食用效果更佳](https://www.cnblogs.com/Dregen-Yor/p/16612984.html)。

# 思路

根据题意我们不难看出，求一个区间的块的数量即求区间内 $a_i\neq a_{i-1}$ 的数量，如果直接枚举每个区间的话，时间复杂度是 $\mathcal O(n^2)$ 显然这样做是不行的，但是我们可以考虑每一个 $a_i\neq a_{i-1}$ 对答案产生的贡献，即有多少个区间包含 当前的 $i$ 和 $i-1$ 根据简单的组合数学知识和乘法原理，我们只需考虑在 $1$ 到 $i-1$ 中选一个点作为区间左端点的方案数，乘上在 $i$ 到 $n$ 之间选取一个点作为区间右端点的方案数，这样算出来的结果为该 $a_i\neq a_{i-1}$ 产生的贡献，再加上序列的所有子区间数量，即 $\dfrac{n\times (n+1)}{2}$ 即可。
 
## 代码如下

```cpp
for (int i = 2; i <= n; i++) {

	ans += (i - 1) * (n - i + 1) * (int)(a[i] != a[i - 1]);
}

ans += (n * (n + 1)) / 2;

```
----

每次修改的时候也是类似的做法，考虑每次修改后，修改的点 $i$ 修改之前是否和 $i-1$ 和 $i+1$ 相等，修改之后是否和 $i-1$ 和 $i+1$ 来考虑每次修改对答案产生的影响，若修改前相等修改后不相等则在原答案的基础上加上修改后产生的贡献，若修改前不相等修改后相等则减去原先对答案产生的贡献。具体细节看代码。

# 代码


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, f[1000100], a[100010], ans, b[100010];

signed main() {
	scanf("%lld%lld", &n, &m);

	for (int i = 1; i <= n; i++) {

		scanf("%lld", &a[i]);
	}

	for (int i = 2; i <= n; i++) {

		ans += (i - 1) * (n - i + 1) * (int)(a[i] != a[i - 1]);
	}

	ans += (n * (n + 1)) / 2;

	while (m--) {
		int op, x;
		scanf("%lld%lld", &op, &x);

		if (op > 1) {
			if (a[op - 1] == x && a[op - 1] != a[op]) {
				ans -= (op - 1) * (n - op + 1);
			} else if (a[op - 1] != x && a[op - 1] == a[op]) {
				ans += ((op - 1) * (n - op + 1));
			}
		}

		if (op <= n - 1) {
			if (x == a[op + 1] && a[op + 1] != a[op]) {
				ans -= op * (n - op);
			} else if (a[op] == a[op + 1] && a[op + 1] != x) {
				ans += (op * (n - op));
			}
		}

		a[op] = x;
		printf("%lld\n", ans);
	}

	return 0;
}


```


---

## 作者：simonG (赞：3)

我们先考虑更改一个数对答案造成的贡献。  
设在把 $a_i$ 改成了 $x$ ，且更改前后不同。

>* 若 $a_i=a_{i-1}$ ，显然，更改之后，区间 $[i-1,i]$ 内就多了一个块了，所有包含 $[i-1,i]$ 的区间的答案加 $1$ ，总答案加 $(i-1)\times(n-i+1)$.
>* 若 $a_i=a_{i+1}$ ，总答案加 $i\times(n-i)$.
>* 若 $x=a_{i-1}$ ， 显然，更改之后，区间 $[i-1,i]$ 内就少了一个块了，所有包含 $[i-1,i]$ 的区间的答案减 $1$ ，总答案减 $(i-1)\times(n-i+1)$.
>* 若 $x=a_{i+1}$ ， 总答案减 $i\times(n-i)$.

那么所有更改操作造成的贡献计算完毕，初值如何计算？  
我们不妨把数组看做全为 $0$ 的数组，答案为 $\dfrac{n\times(n+1)}{2}$.  
然后输入 $a_1,a_2,...,a_n$ ，相当于在 $i$ 位置进行一次修改.

```cpp
#include<algorithm>
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long int64;
const int64 N=1e5+10;
int64 n,q,ans,a[N],p,x;
int main() {
	scanf("%lld%lld",&n,&q);
	ans=n*(n+1)/2;
	for(int64 i=1; i<=n+q; i++) {
		if(i<=n) {scanf("%lld",&x); p=i;}
		else scanf("%lld%lld",&p,&x);
		if(a[p]==a[p-1]) ans+=(p-1)*(n-p+1);
		if(a[p]==a[p+1]) ans+=p*(n-p);
		if(x==a[p-1]) ans-=(p-1)*(n-p+1);
		if(x==a[p+1]) ans-=p*(n-p);
		a[p]=x;
		if(i>n) printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Code_星云 (赞：1)

由题得知，$g(l,r)$ 表示 $[l,r]$ 区间内块的个数。 因此我们维护 $sum[i]$ 表示 $[1,i]$ 的区间内块的个数。故 $g(l,r)=sum[r]-sum[l]+1$。

所以，我们可以将求答案的式子化为$\sum_{l=1}^{n}\sum_{r=l}^{n}(sum[r]-sum[l]+1)$  
上式又等同于   $\sum_{r=1}^{n}\sum_{l=1}^{r}(sum[r]-sum[l]+1)$

可以通过图来理解上面式子的变换
![](https://cdn.luogu.com.cn/upload/image_hosting/tpcw3gn1.png?xossprocess=image/resize,m_lfit,h_170,w_225)

我们假设 $n$ 为 $5$ ，要求的线段就是棕色部分，而第二个式子的意义就是粉色线段（最好自行理解一下）。

接下来我们考虑修改操作。   
每次只会修改一个点 $i$，所以我们讨论修改该点后对 $sum$ 数组的影响：  
1. 原先 $a[i] \ne a[i-1]$ ，现在相同了 ，所以对于 $j\in[i,n]$ ，$sum[j]$ 都会减 $1$ 。
2. 原先 $a[i] \ne a[i+1]$ ，现在相同了 ，所以对于 $j\in[i+1,n]$ ，$sum[j]$ 都会减 $1$ 。
3. 原先 $a[i]=a[i-1]$ ，现在不同了，所以对于 $j\in[i,n]$ ，$sum[j]$ 都会加 $1$ 。
4. 原先 $a[i]=a[i+1]$ ，现在不同了，所以对于 $j\in[i+1,n]$ ，$sum[j]$ 都会加 $1$ 。

接下来我们再考虑 $sum$ 数组的变化对答案的影响。
回顾一下式子：$\sum_{r=1}^{n}\sum_{l=1}^{r}(sum[r]-sum[l]+1)$   

我们发现，$1$ 那个部分永远不变。    
对于 $sum[l]$ ，可以借助图来理解。$sum[l]+1$ ,答案会减少 $lt[i]$ ($lt[i]$  表示 $l$ 作为图中棕色线段左端点的次数)。  
同理，$sum[r]+1$ 时，答案增加 $rt[i]$ ,表示 $r$ 作为棕色线段右端点的次数。

因此，我们维护每个点分别作为图中棕色线段左右端点的次数。（次数可以通过那个式子来理解。$i$ 作为右端点时的线段数就是内层循环数( $i$ )，作为左端点时，由于 $[i,n]$ 中每个点做循环时都会遍历一次 $i$ ,故答案是 $n-i+1$）
```cpp
for(int i=1;i<=n;i++) lt[i]=n-i+1; //左端点
for(int i=1;i<=n;i++) rt[i]=i; //作为右端点的次数
```
我们再顺便维护一下后缀和。
```cpp
for(int i=n;i>=1;i--) sl[i]=sl[i+1]+lt[i];
for(int i=n;i>=1;i--) sr[i]=sr[i+1]+rt[i];
```
维护后缀和有什么用呢？我们发现，每次修改完 $a[i]$ 后，发生改变的不仅有 $sum[i]$ ，$sum[i+1]$ , $sum[i+2]$....  
这表明答案会加上 $rt[i],rt[i+1],rt[i+2]...$ ， 会减去 $lt[i],lt[i+1],lt[i+2]...$。  
前缀和可以将此 $O(1)$ 维护。

所以，更改操作我们就用线性处理了。
```cpp
void make(int pl){
	ans-=sl[pl];
	ans+=sr[pl];
}
void del(int pl){
	ans+=sl[pl];
	ans-=sr[pl];
}
//以下在 main 函数里
while(m--){
	ll pl,x; scanf("%lld%lld",&pl,&x);
	if(x!=a[pl]){
		if(x==a[pl-1]) del(pl);
		if(x==a[pl+1]) del(pl+1);
		if(a[pl]==a[pl-1]) make(pl);
		if(a[pl]==a[pl+1]) make(pl+1);
	}
	a[pl]=x;
	printf("%lld\n",ans);
}
```

最后，我们只需要求出初始答案即可。暴力 $O(n^2)$ 会超时。     

线性做法是：现将数组构造成有 $n$ 个长度为 $1$ 的块。容易发现，构造完后的答案为 $\sum_{i=1}^{n}\sum_{j=1}^{i}j$ 。  
然后每次像修改操作一样，把 $i$ 位置的值修改为 $a[i]$，并修改答案。

总复杂度 $O(n+m)$ 。

------------
### 完整代码
```cpp
#include<cstdio>
#include<algorithm>
#define N 100005
using namespace std;
typedef long long ll;
ll n,m,a[N],sum[N],ans,rt[N],lt[N],sl[N],sr[N],b[N];
void make(int pl){
	ans-=sl[pl];
	ans+=sr[pl];
}
void del(int pl){
	ans+=sl[pl];
	ans-=sr[pl];
}
int main(){
	scanf("%lld%lld",&n,&m); a[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+((a[i]==a[i-1])?0:1);
	} 
	for(int i=1;i<=n;i++) lt[i]=n-i+1;
	for(int i=1;i<=n;i++) rt[i]=i;
	for(int i=n;i>=1;i--) sl[i]=sl[i+1]+lt[i];
	for(int i=n;i>=1;i--) sr[i]=sr[i+1]+rt[i];
	for(int i=1;i<=n;i++) ans+=1ll*(1+i)*i/2;
	for(int i=1;i<=n;i++) b[i]=i;
	for(int i=1;i<=n;i++){
		ll pl=i,x=a[i];
		if(x!=b[pl]){
			if(x==b[pl-1]) del(pl);
		    if(x==b[pl+1]) del(pl+1);
		    if(b[pl]==b[pl-1]) make(pl);
		    if(b[pl]==b[pl+1]) make(pl+1);
		}
		b[pl]=x;
	} 
	while(m--){
		ll pl,x; scanf("%lld%lld",&pl,&x);
		if(x!=a[pl]){
			if(x==a[pl-1]) del(pl);
		    if(x==a[pl+1]) del(pl+1);
		    if(a[pl]==a[pl-1]) make(pl);
		    if(a[pl]==a[pl+1]) make(pl+1);
		}
		a[pl]=x;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：hcywoi (赞：0)

对于一个操作 $x, d$

如果 $w[x] \neq d$，对答案有以下几种影响

*  `x > 1 && w[x - 1] == d` 那么对于 $\forall i$ $\forall j$ 如果满足 $i < x$ 和 $j \ge x$ 则 `g(i, j)` 就会减一，对答案的影响为 $-((x-1) \times (n-x+1))$
* `x < n && w[x + 1] == d` 那么对于 $\forall i$ $\forall j$ 如果满足 $i \le x$ 和 $j > x$ 则 `g(i, j)` 就会减一，对答案的影响为 $-(x \times (n-x))$
* `x > 1 && w[x - 1] == w[x]` 那么对于 $\forall i$ $\forall j$ 如果满足 $i < x$ 和 $j \ge x$ 则 `g(i, j)` 就会加一，对答案的影响为 $+((x-1) \times (n-x+1))$
* `x < n && w[x + 1] == w[x]`那么对于 $\forall i$ $\forall j$ 如果满足 $i \le x$ 和 $j > x$ 则 `g(i, j)` 就会加一，对答案的影响为 $+(x \times (n-x))$

那么我们可以先求出没有操作过的答案，对于每一个操作都维护一下答案

求没有操作过的答案也可以用类似的思想。

假设该序列没有重复，那么答案就为
$\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{i} j$

`w[x] == w[x - 1]` 那么对于 $\forall i$ $\forall j$ 如果满足 $i < x$ 和 $j \ge x$ 则 `g(i, j)` 就会减一，对答案的影响为 $-((x-1) \times (n-x+1))$，在这里不用判断 `w[i] == w[i + 1]`，因为遍历到 `i+1` 时会减去

### 时间复杂度
预处理是 $O(n)$

询问是 $O(m)$

所以时间复杂度为 $O(n + m)$

### Code
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

const int N = 100010, M = 100010, MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

int n, m;
int w[N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
	
	LL res = 0;
	for (int i = 1; i <= n; i ++ ) res += i * (i + 1ll) / 2; // 用高斯公式
	for (int i = 1; i <= n; i ++ )
		if (w[i] == w[i - 1])
			res -= (i - 1ll) * (n - i + 1);
	
	while (m -- )
	{
		int x, d;
		scanf("%d%d", &x, &d);
		if (w[x] != d)
		{
			if (x > 1 && w[x - 1] == d) res -= (x - 1ll) * (n - x + 1);
			if (x < n && w[x + 1] == d) res -= (LL)x * (n - x);
			if (x > 1 && w[x - 1] == w[x]) res += (x - 1ll) * (n - x + 1);
			if (x < n && w[x + 1] == w[x]) res += (LL)x * (n - x);
			w[x] = d;
		}
		printf("%lld\n", res);
	}

	return 0;
}
```

---

## 作者：SengRiy (赞：0)

[更好的阅读体验](https://www.luogu.com.cn/blog/HLXBK/cf1715c-monoblock-ti-xie)


### 题意

定义 $g(i, j)$ 为 $i$ 到 $j$ 中连续相同数字段的个数，更改 $q$ 次值。

且对于每次更改，求 $\sum\limits_{l = 1}^n \sum\limits_{r = l}^n g(l, r)$ 。

### 思路

$\sum\limits_{l = 1}^n \sum\limits_{r = l}^n g(l, r)$ 。

首先我们可以考虑以上的求和该如何计算，

可以想出，我们可以通过计算每个数字对 sum 贡献 $1$ 的次数，以此算出 sum。

假设 $a = \{1,2,2,3,4\}$ ，列个表格（记录做贡献的次数）：

$$
\begin{matrix}
 & 1 & 2 & 2 & 3 & 4\\
l = 1 & 5 & 4 & 0 & 2 & 1 \\
l = 2 & 0 & 4 & 0 & 2 & 1 \\
l = 3 & 0 & 0 & 3 & 2 & 1 \\
l = 4 & 0 & 0 & 0 & 2 & 1 \\
l = 5 & 0 & 0 & 0 & 0 & 1
\end{matrix}
$$

// 由于第二个 $2$ 前面相邻为第一个 $2$ ，故在包括第一个 $2$ 的区间中第二个 $2$ 不做贡献。

通过这个表格，我们可以发现（设一个数的下标为 $i$ ，且下标以 $1$ 开始）：

+ 当一个数不同于前面的数时，此数会为 sum 贡献 $i\times (n-i+ 1)$；

+ 反之，此数会为 sum 贡献 $(n - i + 1)$ 次。

### 代码

```cpp
  long long sum = 0;
  for (long long i = 1; i <= n; ++i) {
    cin >> a[i];
    if (a[i] != a[i - 1]) {
      p[i] = 1;
      sum += i * (n - i + 1);
    } else {
      sum += (n - i + 1);
    }
  }
 
  while (m--) {
    long long u, w;
    cin >> u >> w;
    if (a[u] != a[u - 1]) {
      if (w == a[u - 1]) {
        p[u] = 0;
        sum += -u * (n - u + 1) + (n - u + 1); 
      }
    } else {
      if (w != a[u - 1]) {
        p[u] = 1;
        sum += -(n - u + 1) + u * (n - u + 1);
      }
    }
 
    if (a[u] != a[u + 1]) {
      if (w == a[u + 1]) {
        p[u + 1] = 0;
        sum += -(u + 1) * (n - (u + 1) + 1) + (n - (u + 1) + 1);
      }
    } else {
      if (w != a[u + 1]) {
        p[u + 1] = 1;
        sum += -(n - (u + 1) + 1) + (u + 1) * (n - (u + 1) + 1);
      }
    }
 
    a[u] = w;
    cout << sum << '\n';
```

---

## 作者：happybob (赞：0)

## 题意

给定一个序列 $a$，其一个区间的价值 $g(l, r)$ 定义为这个区间连续段的数量。定义整个序列的价值为 $\sum\limits_{l = 1}^n \sum\limits_{r = l}^n g(l, r)$。给定序列 $a$ 和 $m$ 次询问，每次询问给定 $i,x$，执行 $a_i \leftarrow x$ 后询问序列价值。

## 解法

一眼看上去多次询问很容易想到数据结构。但是貌似并不好维护。

这里提供一种和题解不太相同的分类讨论做法。

假设目前序列价值为 $ret$，修改的参数是 $i,x$。

- 若 $a_i=x$，没有改动，不变。

- 若 $a_{i-1}=a_{i+1}=a_i$，例如 $[3, 3, 3] \rightarrow [3,4,3]$，对于 $l < i < r$，其贡献 $+2$，对于 $l=i, r > i$， 其贡献 $+1$，对于 $l < i, r= i$，其贡献 $+1$，故 $ret \leftarrow ret + 2(i-1)(n-i) + n-i + i - 1$。

- 若 $a_i = a_{i-1}$，分情况讨论：

	1. 若 $x \neq a_{i+1}$，例如 $[3, 3, 2] \rightarrow [3, 4, 2]$，对于 $l < i < r$，其贡献 $+1$，对于 $r=i, l < i$，其贡献 $+1$。对于 $l=i, r > i$，贡献不变。故 $ret \leftarrow ret + (i-1)(n-i) + i-1$。
    
	1. 若 $x=a_{i+1}$，例如 $[3,3,2] \rightarrow [3, 2, 2]$，对于 $l<i<r$，贡献不变，对于 $l=i, r>i$，其贡献 $-1$，对于 $l<i,r=i$，贡献 $+1$，故 $ret \leftarrow ret-(n-i)+(i-1)$
    
- 若 $a_i=a_{i+1}$，推的时候与上一情况同理，但有些不同，若 $x\neq a_{i-1}$，$ret \leftarrow ret + (i-1)(n-i) + n-i$。若 $x = a_{i-1}$，$ret \leftarrow ret+(n-i)-(i-1)$。

- 若 $a_{i-1}=a_{i+1}$，分情况讨论：

	1. 若 $x \neq a_{i-1}$，例如 $[3,2,3] \rightarrow [3,4,3]$，贡献不变。
    
	2. 若 $x = a_{i-1}$，例如 $[3,2,3] \rightarrow [3,3,3]$，对于 $l<i<r$，贡献 $-2$，对于 $l=i, r>i$，贡献 $-1$，对于 $l<i, r=i$ 贡献 $-1$。故 $ret \leftarrow ret - 2(i-1)(n-i) - (n-i) - (i-1)$。
    
- 若 $x=a_{i-1}$，例如 $[2, 3, 4] \rightarrow [2,2,4]$，对于 $l<i<r$，贡献 $-(1$，对于 $l=i, r>i$，贡献不变，对于 $l<i,r=i$，贡献 $-1$，故 $ret \leftarrow ret - (i-1)(n-i) - (i-1)$。

- 若 $x=a_{i+1}$，例如 $[2, 3, 4] \rightarrow [2,4,4]$，对于 $l<i<r$，贡献 $-1$，对于 $l<i,r=i$，贡献不变，对于 $l=i,r>i$，贡献 $-1$，故 $ret \leftarrow ret - (i-1)(n-i) - (n-i)$。

至此分类讨论结束，注意以上分类可能有些重叠，所以均使用 `if... else if...` 结构，每次选取第一个符合的分类。

第二个问题，如何预处理 $\sum\limits_{l = 1}^n \sum\limits_{r = l}^n g(l, r)$，考虑将序列变成若干个形如 $(L,R)$ 的段，每个段都为极大段且元素相同。每个段对于 $l<L_i<R_i<r$ 都有 $1$ 的贡献。对于 $l<L_i \leq r \leq R_i$ 也有 $1$ 的贡献。对于 $L_i \leq l \leq r \leq R_i$ 也有 $1$ 的贡献。

至此，问题解决，预处理 $O(n)$，单次询问 $O(1)$，总复杂度为线性，$O(n+m)$。

```cpp
#pragma GCC optimize("-Ofast")
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t, a[N];
vector<pair<int,int> > p;

signed main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	int l=1,r=1;
	//a[2]=3;
	for(int i=2;i<=n+1;i++)
	{
		if(a[i]!=a[i-1])
		{
			p.push_back(make_pair(l,r));
			l=r=i;
		}
		else
		{
			r=i;
		}
	}
	int ret=0;
	for(int i=0;i<p.size();i++)
	{
		int len=p[i].second-p[i].first+1;
		ret+=(p[i].first-1)*(n-p[i].second);
		ret+=len*(p[i].first-1);
		ret+=len*(n-p[i].second);
		for(int j=p[i].first;j<=p[i].second;j++)
		{
			ret+=(p[i].second-j+1);
		}
	}
	//printf("%lld\n",ret);
	while(m--)
	{
		int p=read(),x=read();
		if(a[p]==x) printf("%lld\n",ret);
		else
		{
			if(p==1)
			{
				if(a[1]==a[2])
				{
					ret+=n-1;
				}
				else if(a[2]==x)
				{
					ret-=n-1;
				}
			}
			else if(p==n)
			{
				if(a[n]==a[n-1])
				{
					ret+=n-1;
				}
				else if(a[n-1]==x) ret-=n-1;
			}
			else
			{
				if(a[p]==a[p-1]&&a[p]==a[p+1])
				{
					ret+=(p-1)*(n-p)*2;
					ret+=n-p;
					ret+=p-1;
				}
				else if(a[p]==a[p-1])
				{
					if(x!=a[p+1])
					{
						ret+=(p-1)*(n-p);
						ret+=p-1;
					}
					else
					{
						ret-=(n-p);
						ret+=(p-1);
					}
				}
				else if(a[p+1]==a[p])
				{
					if (x!=a[p-1])
					{
						ret+=(p-1)*(n-p);
						ret+=(n-p);
					}
					else
					{
						ret-=(p-1);
						ret+=(n-p);
					}
				}
				else if(a[p-1]==a[p+1])
				{
					if(x==a[p-1])
					{
						ret-=(p-1)*(n-p)*2;
						ret-=n-p;
						ret-=p-1;
					}
				}
				else
				{
					if(x==a[p-1])
					{
						//printf("111\n");33
						ret-=(p-1)*(n-p);
						ret-=(p-1);
					}
					else if(x==a[p+1])
					{
						ret-=(p-1)*(n-p);
						ret-=(n-p);
					}
				}
			}
			a[p]=x;
			printf("%lld\n",ret);
		}
	}
	return 0;
}


```


---

## 作者：tangtangpeng (赞：0)

## 题意

- 给定一个长度为 $n$ 的序列 $a$。
- $g(l,r)$ 为序列中区间 $[l,r]$ 能被分成的段数，如序列 $[1,1,2,2,2,1,1,3]$ 就能被分成 $[1,1],[2,2,2],[1,1],[3]$ 四段。
- $m$ 次询问，每次修改 $1$ 个值，并求此时的 $\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}g(l,r)$。

## 思路

这题并不需要用什么数据结构维护，我们应当立足求出于每次修改产生的贡献。

换一种思路，可以发现每一个序列分成若干段后都会出现一些“断点”，如如序列  $[1,1,2,2,2,1,1,3]$ 的断点就是第 $2,3$ 个元素之间，第 $5,6$ 个之间，以及第 $7,8$ 个之间共三个。

那么对于每一个序列的答案就是**跨过每一个断点的区间数量之和，加上区间的总数**，还是上面的区间，答案就是 $2 \times (8-2) + 5 \times (8-5) + 7 \times (8-7) + 8 \times 9 \div 2 = 70$，区间总数一定，所以可以先放在一边。

求出原序列的答案后，接下来考虑单点修改对答案的影响，假设此时我们令 $a_i=x$，我们首先减去这个点原先的贡献，然后加上修改之后的贡献就可以完成一次修改了。

贡献可以通过判断此时 $a_i$ 与它两边的 $a_{i-1},a_{i+1}$ 的关系得到：如果发现此时 $a_{i-1}≠a_i$，那就说明 $i-1,i$ 之间是断点，产生跨过这个断点的区间数量的贡献，即 $(i-1) \times (n - i + 1)$，判断 $a_{i+1}$ 也是同理的。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 10;
int n, m;
int a[N];
int ans;

signed main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	for(int i = 1; i <= n; i++)
		ans += (a[i] != a[i + 1]) * i * (n - (i + 1) + 1); 
	while(m--)
	{
		int i, x;
		cin >> i >> x;
		ans -= (a[i - 1] != a[i]) * (i - 1) * (n - i + 1);
		ans -= (a[i] != a[i + 1]) * i * (n - (i + 1) + 1);
		a[i] = x;
		ans += (a[i - 1] != a[i]) * (i - 1) * (n - i + 1);
		ans += (a[i] != a[i + 1]) * i * (n - (i + 1) + 1);
		cout << ans + n * (n + 1) / 2 << endl;
	}
	return 0;
}
```


---

## 作者：cachejtt (赞：0)

## 题意
给你一个序列 $a_1,a_2,\dots,a_n$，定义其段数为可以拆分数组的最小连续相同数字块的数量。即同色平台个数。例如 $111\red{222}3$ 的段数为 $3$。$11\red{22}3333\red{22}11\red{444}5$ 的段数为 $7$。记为 $\operatorname{g}(1,n)$。

现在给你一个长度为 $n$ 的初始序列和 $m$ 次操作。每次操作，给定一个下标 $i$ 和一个数 $x$，代表把数列的第 $i$ 项改为 $x$，**并保持下去**。（$1\le n,m\le 10^5$）

每次操作后，你都需要给出当前序列的所有子段段数和。换句话说，你需要计算

$$\sum\limits_{l = 1}^n \sum\limits_{r = l}^n \operatorname{g}(l, r),$$

## 思路

由于 $n,m$ 大，考虑预处理当前数列的值，在每次修改时 $O(1)$ 更新答案。 

### 修改
先考虑它与它相邻的数。

1. 如果从原来不同变成现在相同，会对答案有一个负的贡献。
2. 如果从原来相同变成不同，会对答案有一个正的贡献。

设当前正在考虑第 $i$ 位要变成 $x$。

若为情况 $1$，则一些子段的段数会减少，哪些子段呢？

![情况1](https://cdn.luogu.com.cn/upload/image_hosting/jw4r5lsu.png)

在 $l_1$ 段里选择 $l$，并在 $l_2$ 段内选择 $r$，则对应的 $\operatorname{g}(l,r)$ 比原来减少了 $1$。故总体答案应减少 $l\times r$。

而对于情况 $2$，在 $l_1$ 段里选择 $l$，并在 $l_2$ 段内选择 $r$，则对应的 $\operatorname{g}(l,r)$ 比原来增加了 $1$。故总体答案应减少 $l\times r$。答案应该加上 $l\times r$。

### 初始值
考虑构造一个初始都不相同的序列，例如 $-1,-2,-3,\dots,-n$，把输入当成 $n$ 次修改来做。

那么，对于序列 $-1,-2,-3,\dots,-n$，它的答案又是多少呢？由于每个数都互不相同，故对于其任意子段，**段数就等于其长度**。

我们知道长度为 $i$ 的子段有 $n+1-i$ 个。故其值为

$$\sum\limits_{i=1}\limits^{n}i\times (n-i+1)$$

即可处理好初始值。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
#define endl "\n"
using namespace std;
int t=1,n,m,a[100005],id,x,fx,xxx;
void chg(int id,int x){
  if(a[id]==a[id-1] && x!=a[id-1]){
    fx+=(id-1)*(n-id+1);
  }
  if(a[id]==a[id+1] && x!=a[id+1]){
    fx+=(id)*(n-id);
  }
  if(a[id]!=a[id-1] && x==a[id-1]){
    fx-=(id-1)*(n-id+1);
  }
  if(a[id]!=a[id+1] && x==a[id+1]){
    fx-=(id)*(n-id);
  }
  a[id]=x;
}
signed main(){
  ios::sync_with_stdio(0);
  cin>>n>>m;
  rep(i,1,n)a[i]=-i,fx+=i*(n+1-i);
  rep(i,1,n){
    cin>>xxx;
    chg(i,xxx);
  }
  rep(i,1,m){
    cin>>id>>x;
    chg(id,x);
    cout<<fx<<endl;
  }
  return 0;
}

```

---

## 作者：sixrc (赞：0)

由于是子区间问题，很容易想到计算每一块的贡献。

计算子区间贡献问题分为两步：计算初始贡献 & 考虑修改后答案的转移。下面分步来讲。

**计算初始贡献**

枚举子区间显然会超时，考虑枚举每一个数字相同的连续块。对于一个连续的块，记其开始位置为 $l$，结束位置为 $r$。它对哪些子区间有贡献呢？记子区间为 $[L,R]$，第一种是 $R>r$ 且 $L \le r$ 的子区间，第二种是 $R \in [l,r]$ 且 $L \le R$ 的子区间。对于第一种子区间，贡献就是 $r(n-r)$；对于第二种子区间，贡献就是 $l+(l+1)+...+r$，循环时统计或者用等差数列公式算即可。

**修改后答案的转移**

不难发现单点修改 $x$，答案的变化只会和 $x,x-1,x+1$ 有关。令修改后 $x$ 位置对应的值为 $a_x'$，则有四种情况会对答案产生影响：

- $a_x \ne a_{x-1},a_x'=a_{x-1}$

- $a_x =a_{x-1},a_x'\ne a_{x-1}$

- $a_x \ne a_{x+1},a_x'=a_{x+1}$

- $a_x=a_{x+1},a_x' \ne a_{x+1}$

贡献的变化计算类似，令子区间为 $[L,R]$，下面以第一种为例：

假设 $[3,5,6]$ 变化为了 $[3,3,6]$，对于 $[L,R] \text{ s.t. }R \ge x,L \le x-1$ 的 $[L,R]$ 答案全部 $-1$，因为原本它包含了 $[3,5]$，而现在只有 $[3,3]$ 了，也就是说它的块数 $-1$。

其它三种计算方法类似。需要注意的是，这种方法对于类似 $[3,5,5]$ 变化为 $[3,3,5]$ 的修改也做到了不重不漏。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, s, x, y, r, tmp, a[100010];
signed main(){
	scanf ("%lld%lld", &n, &m);
	for (int i=1; i<=n; i++){
		scanf ("%lld", &a[i]);
	}
	for (int i=1; i<=n+1; i++){
		if (a[i] != a[i-1]){
			r = i - 1;
			s += (n - r) * r + tmp;
			tmp = 0;
		}
		tmp += i;
	}
	for (int i=1; i<=m; i++){
		scanf ("%lld%lld", &x, &y);
		if (a[x-1] != a[x] && a[x-1] == y) s -= (x-1) * (n-x+1);
		if (a[x-1] == a[x] && a[x-1] != y) s += (x-1) * (n-x+1);
		if (a[x+1] != a[x] && a[x+1] == y) s -= x * (n-x);
		if (a[x+1] == a[x] && a[x+1] != y) s += x * (n-x);
		a[x] = y;
		printf ("%lld\n", s);
	}
	return 0;
}

```

---

## 作者：ExplodingKonjac (赞：0)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1715C)**

## 题目分析

考虑计算每个连续段的贡献。对于连续段 $[l,r]$，它会给每个与它相交的区间贡献 $1$。那么贡献就是与它相交的区间个数，也就是 $\dfrac{n(n+1)-l(l-1)-(n-r)(n-r+1)}{2}$。

修改什么的，可以使用 `std::set` 来维护连续段。单点修改先找到这个位置所在的段，再判断修改后是否会与两边的段合并，并且加上/减去贡献就行了。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

int n,m,a[100005];

struct Interval
{
	int l,r;
	Interval(int _l=0,int _r=0): l(_l),r(_r){}
	inline bool operator <(const Interval &rhs)const
		{ return l<rhs.l; }
};
set<Interval> s;
LL ans;
inline void add(const Interval &x)
{
	ans+=(LL)n*(n+1)/2-
		 (LL)(x.l-1)*x.l/2-
		 (LL)(n-x.r)*(n-x.r+1)/2;
	s.insert(x);
}
inline void del(const Interval &x)
{
	ans-=(LL)n*(n+1)/2-
		 (LL)(x.l-1)*x.l/2-
		 (LL)(n-x.r)*(n-x.r+1)/2;
	s.erase(x);
}
int main()
{
	qin>>n>>m;
	for(int i=1;i<=n;i++) qin>>a[i];
	int lst=1;
	for(int i=1;i<=n;i++) if(a[i]!=a[lst]) add(Interval(lst,i-1)),lst=i;
	add(Interval(lst,n));
	while(m--)
	{
		int x,y;
		qin>>x>>y;
		if(a[x]!=y)
		{
			auto it=--s.upper_bound(x),pre=prev(it),nxt=next(it);
			Interval now=*it,res(x,x);
			del(*it),a[x]=y;
			if(x>1 && x==now.l && a[x]==a[x-1]) res.l=pre->l,del(*pre);
			if(x<n && x==now.r && a[x]==a[x+1]) res.r=nxt->r,del(*nxt);
			add(res);
			if(now.l<res.l) add(Interval(now.l,res.l-1));
			if(now.r>res.r) add(Interval(res.r+1,now.r));
		}
		qout.writeln(ans);
	}
	return 0;
}
```


---

