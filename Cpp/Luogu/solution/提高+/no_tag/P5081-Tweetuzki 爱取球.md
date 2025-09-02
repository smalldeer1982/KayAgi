# Tweetuzki 爱取球

## 题目背景

本题为被指出的改编题……~~害怕被爆破~~

## 题目描述

Tweetuzki 有一个袋子，袋子中有 $N$ 个无差别的球。Tweetuzki 每次随机取出一个球后放回。求取遍所有球的期望次数。

取遍是指，袋子中所有球都被取出来过至少一次。

## 说明/提示

### 样例解释 1

第一次取出一个球即可取遍所有球。

### 样例解释 2

两次就取遍所有球的概率为 $\frac{1}{2}$，三次取遍所有球的概率为 $\frac{1}{4}$，四次取遍所有球的概率为 $\frac{1}{8}$，……，$k$ 次取遍所有球的概率为 $\frac{1}{2^{k-1}}$。故：

$$E(2) = \frac{2}{2} + \frac{3}{4} + \frac{4}{8} + \frac{5}{16} + \cdots = 3$$

### 样例解释 3

通过试验及计算可得：

$$E(3) = \frac{11}{2}$$

对 $20040313$ 取模后答案为 $10020162$。

## 数据范围及约定

对于 $30\%$ 的数据，$N \le 5$。  
对于 $70\%$ 的数据，$N \le 10^5$。  
对于 $100\%$ 的数据，$1 \le N \le 10^7$。

## 样例 #1

### 输入

```
1```

### 输出

```
1```

## 样例 #2

### 输入

```
2```

### 输出

```
3```

## 样例 #3

### 输入

```
3```

### 输出

```
10020162```

# 题解

## 作者：Protons (赞：11)

## 题解思路：正难则反
我们发现，因为该期望的概率数列是个不收敛数列，所以要想顺着题目的思路去推出期望几乎是不可能的，因此我们要另辟蹊径

## 引理：
**求证**：

假设对于一件事$A$，我们每一次做$A$时的成功率是$P$，如果本次不成功就继续做，最终期望$\dfrac{1}{p}$次做成

**证明：**

对于这个问题，我们显然不能正向去想，我们可以利用一个叫做递归公式的东西：我们设**期望$k$次做成$A$** ，则有：

$k=1+p*0+(1-p)*k$

**其中1表示第一次做$A$，如果成功了就再做0次，期望次数为$p*0$；如果不成功就再做$k$次，期望为$(1-p)*k$**

通过移项，我们得到

$k=\dfrac {1}{p}$

引理证毕
## 正文：
我们先来思考一个问题：**从$n$个球里取出1个球的概率**是多少

答案很简单，显然是1，由引理得，取出1个球成功的期望次数为$k_1=\dfrac{1}{p}=\dfrac{1}{1}=1$

那**从$n$个球中取出其他$n-1$个球中的一个球的概率**呢？其实也很好算，就是$\dfrac{n-1}{n}$，那成功的期望次数就是$k_2=\dfrac{1}{p}=\dfrac{n-1}{n}$

以此类推……………………

则**取遍这$n$个球的总期望次数**为：$k_{sum}=k_1+k_2+\text{…}+k_n=\dfrac{n}{n}+\dfrac{n}{n-1}+\text{…}+\dfrac{n}{1}=n*\sum\limits_{i=1}^{n-1}\dfrac{1}{n-i}$

所以最终这个题就是求个逆元和乘$n$就完事了

## 附加证明：线性筛逆元
我们知道，对于任意一个数$p$，都有$p=a*b+c$（$a,b,c$为任意整数）

则对于式子$p\equiv0\text{(mod p)}$

我们有$a*b+c\equiv0\text{(mod p)}$

把$c$挪到右边：$a*b\equiv-c\text{(mod p)}$

两边同时乘$c$的逆元$c^{-1}$：$a*b*c^{-1}\equiv-1\text{(mod p)}$

两边再同时乘$b$的逆元$b^{-1}$：$a*c^{-1}\equiv-b^{-1}\text{(mod p)}$

即可化为$b^{-1}\equiv-a*c^{-1}\text{(mod p)}$

同时，我们知道，在c++里，$int$类的除法都是自动向下取整的。所以我们可以得到：对于数$p=a*b+c$，有$a=\dfrac{p}{b}$、$c=p\%b$（我们要求的是$b$的逆元，$p$是模数）。我们设$inv[i]$为$i$的逆元，则有递推式：

$inv[i]=(1ll*(p-\dfrac{p}{i})*inv[p\%i])\%p$

证毕

以下是code：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long ll;
const int p=20040313;
ll inv[10000010],sum,n;
int main()
{
	scanf("%lld",&n);
	inv[1]=1;sum+=1;
	for(int i=2;i<=n;i++)//简短有力
	inv[i]=(1ll*(p-p/i)*inv[p%i])%p,sum=(sum+inv[i])%p;
	printf("%lld",n*sum%p);
	return 0;
}
```

---

## 作者：一扶苏一 (赞：8)

## Description

Tweetuzki 有一个袋子，袋子中有 $N$ 个无差别的球。Tweetuzki 每次随机取出一个球后放回。求取遍所有球的期望次数。

取遍是指，袋子中所有球都被取出来过至少一次。

## Input

一行一个整数 $N$

## Output

一行一个整数，表示期望次数对 $200403013$ 取模的结果

## Hint

$1~\leq~N~\leq~10^7$

## Solution

#### ~~期望嘛，就是你xjb乱推好几个看起来很靠谱事实上最多有一个是对的甚至可能一个也不对的式子，然后用蒙特卡洛方法拍一拍，挑一个最靠谱的交上去~~

感谢@_rqy提供指导

先给出结论：

$$E(n)~=~n~\times~(\sum_{i=1}^{n}~\frac{1}{i})$$

### 证明如下：

#### 引理：对于一次试验，有 $p~(0~\leq~p~\leq~1)$ 的概率成功，有 $1-p$ 的概率不成功，如果一次试验后不成功则重复进行试验，否则停止。则期望在 $\frac{1}{p}$ 步后停止试验

##### 证明：

设期望 $x$ 步后停止试验，根据已知以及期望的线性相加性，可得方程：

$$x~=~1~+~p~\times~0~+~(1~-~p)~\times~x$$

上述方程的直观解释是当前进行完一步后有 $p$ 的概率再进行 $0$ 次（停止），$1~-~p$ 的概率继续进行，由于下次试验和这次试验完全相同，所以有 $1~-~p$ 的概率期望再进行 $x$ 次。

解方程，得

$$x~=~\frac{1}{p}$$

##### 引理证毕。

于是考虑摸球，首先有 $n$ 个球没有被摸到的时候，摸一次摸到新球的概率为 $1$，根据引理，期望摸 $1$ 次。

然后剩下 $n~-~1$ 个球没有被摸到，摸一次摸到新球的概率为 $\frac{n-1}{n}$，根据引理，期望摸 $\frac{n}{n-1}$ 次。

然后剩下 $n~-~2$ 个球没有摸到，摸一次摸到新球的概率为 $\frac{n-2}{n}$ ，根据引理，期望摸 $\frac{n}{n-2}$ 次。

……~~（一位读者及时砸坏了复读机，停止了复读）~~

按照球的个数进行数学归纳，根据期望的可加性（非线性相加性），可以得到摸遍 $n$ 个球的期望

$$E(n)~=~n~+~\frac{n}{n-1}~+~\frac{n}{n-1}~+~\dots~+~\frac{n}{1}$$

提取公因数 $n$，可得

$$E(n)~=~n~\times~(\sum_{i=1}^{n}~\frac{1}{i})$$

### 证毕。

然鹅最后一个式子只是为了让结论变得优美一点，事实上用倒数第二个式子就可以做题了233

于是先筛一遍逆元，然后求答案即可。

## Code

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 10000010;
const int MOD = 20040313;

int n, ans;
int inv[maxn];

void GetInv();

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	GetInv();
	for (rg int i = 0; i < n; ++i) {
		ans = (ans + 1ll * n * inv[n - i]) % MOD;
	}
	qw(ans, '\n', true);
}

void GetInv() {
	inv[1] = 1;
	for(int i = 2; i <= n; ++i) inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
}
```

## Summary

对于一次试验，有 $p~(0~\leq~p~\leq~1)$ 的概率成功，有 $1-p$ 的概率不成功，如果一次试验后不成功则重复进行试验，否则停止。则期望在 $\frac{1}{p}$ 步后停止试验

---

## 作者：ezoixx130 (赞：3)

这是一道期望题。

如果按样例解释的方法，求$i$遍取遍所有球的概率，再累加的话，是不太可做的。

考虑换一种方式思考，假设当前还有$i$个球没有被取出过，那么这一次取出这$i$个球的其中一个的概率就是$\frac{i}{n}$，所以取出这$i$个球的其中一个的期望次数就是$\frac{1}{\frac{i}{n}}$，即$\frac{n}{i}$。

所以答案为：还有$n$个球没有取出过，取出这$n$个球的其中一个的期望次数+还有$n-1$个球没有取出过，取出这$n-1$个球的其中一个的期望次数+...+还有$1$个球没有取出过，取出这$1$个球的其中一个的期望次数，即$\sum\limits_{i=1}^{n}\frac{n}{i}$。

我们只需要线性求出逆元即可$O(n)$求出这个式子的值。

总时间复杂度:$O(n)$

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 10000010
#define p 20040313

int n,inv[MAXN],ans;

void init()
{
    inv[1]=1;
    for(int i=2;i<=n;++i)inv[i]=(long long)(p-p/i)*inv[p%i]%p;
}

int add(int a,int b)
{
    return a+b>=p?a+b-p:a+b;
}

int main()
{
    scanf("%d",&n);
    init();
    ans=1;
    for(int i=1;i<n;++i)
        ans=add(ans,(long long)inv[n-i]*n%p);
    printf("%d\n",ans);
}
```

---

## 作者：SSerxhs (赞：2)

设f(i)为n个球取遍i个的期望步数

考虑f(i+1)的来源，有i/n的可能性摸出摸过的，则无影响，其贡献为f(i+1)，而有(n-i)/n的可能性摸出没摸过的，则立即停止摸球，贡献为f(i)。所以f(i+1)=(i/n)*f(i+1)+((n-i)/n)*f(i)+1，整理可得f(i+1)=f(i)+(n-i)/n，则f(n)为n*s[n]，s[n]为逆元前缀和，线性推逆元即可

```cpp
// luogu-judger-enable-o2
#include <stdio.h>
#include <string.h>
const int N=1e7+2,p=20040313;
typedef long long ll;
int inv[N];
int n,i;
int main()
{
    inv[1]=1;
    scanf("%d",&n);
    for (i=2;i<=n;i++) inv[i]=p-(ll)inv[p%i]*(p/i)%p;
    for (i=2;i<=n;i++) inv[i]=(inv[i]+inv[i-1])%p;
    inv[n]=(ll)inv[n]*n%p;
    printf("%d",inv[n]);
}
```

---

## 作者：mrsrz (赞：1)

令$f_i$表示有$i$个球被取出来过，到有$i+1$个球被取出来过的期望步数。

$$f_i=\frac{n-i}{n}+\frac{i}{n}\times(f_i+1)$$

每次有$\frac{n-i}n$的概率取出一个新球，花费1步；或有$\frac i n$的概率取出一个取过的球，花费$1+f_i$步。

化简得：

$$f_i=\frac{n}{n-i}$$

最后的答案就是：

$$\sum_{i=0}^{n-1}f_i=\sum_{i=0}^{n-1}\frac{n}{n-i}=\sum_{i=1}^n\frac n i$$

用线性推逆元即可。

时间复杂度$O(n)$。

## Code：
```cpp
#include<cstdio>
const int md=20040313;
typedef long long LL;
int iv[10000001],ans,n;
int main(){
	iv[1]=1;
	scanf("%d",&n);
	for(int i=2;i<=n;++i)iv[i]=LL(md-md/i)*iv[md%i]%md;
	for(int i=0;i<n;++i)ans=(ans+LL(iv[n-i])*n)%md;
	printf("%d",ans);return 0;
}
```

---

## 作者：DiTeXy (赞：1)

```c
#include<bits/stdc++.h>
using namespace std;
const long long p=20040313;
long long ans,inv[10000005]={0};
int n;
int main()
{
    scanf("%d",&n);
	inv[1]=1;
	ans=1;
	for(int i=2;i<=n;i++)
	{
		inv[i]=(p-p/i)*inv[p%i]%p;
		ans=(ans+inv[i])%p;
	}
	ans=ans*n%p;
	printf("%lld\n",ans);
	return 0;
}

```

数学期望定义题。

第一个球取到不同的概率是1=n/n；

第二个球取到不同的概率是(n-1)/n;

……………………

第n个球取到不同的概率是(n-(n-1))/n=1/n;

————————————————————

取到第一个球的期望次数是1/(n/n)=n/n;

取到第二个球的期望次数是1/((n-1)/n)=n/(n-1);

取到第n个球的期望次数是1/(1/n)=n/1;

所以总数就是：

n*(1/n + 1/(n-1) + … + 1/2 + 1/1)

取模意义下就是：

n*(inv[n] + inv[n-1] + … + inv[2] + inv[1])

其中：inv[i]是i在%p意义下的逆元。

关于线性递推逆元可参考 [P3811 【模板】乘法逆元](https://www.luogu.org/problemnew/show/P3811)

复杂度O(n)，可过此题。

                                      ————————蒟蒻黑暗主宰参上。

---

## 作者：jijidawang (赞：0)

此题是三倍经验哦：
- [[SHOI2002] 百事世界杯之旅](https://www.luogu.com.cn/problem/P1291)
- [SP1026 FAVDICE - Favorite Dice](https://www.luogu.com.cn/problem/SP1026)
- [Tweetuzki 爱取球](https://www.luogu.com.cn/problem/P5081)

***

赠券收集问题

考虑目前已经集齐了 $k-1$ 面，那么我们要再整一个得到一个新的的概率肯定是 $\dfrac{n-k+1}{n}$ .

因为古典概型，于是整一个新面的期望步数就是概率的倒数也就是 $\dfrac n{n-k+1}$ .

所以答案就是
$$\sum_{i=1}^n\dfrac n{n-k+1}$$
显然就是 $nH_n$，其中 $H$ 是调和级数 .

到了这一步就是模意义调和级数的问题了，因为 $n\le 10^7$，所以可以直接线性筛出逆元来然后加起来 .

顺便一提这题似乎可以做到 $O(\sqrt n\log n)$，具体见 [P5702](https://www.luogu.com.cn/problem/P5702)，但是应该有细节差异 .

~~分块打表也能做到 $\sout{O(\sqrt n\log n)}$~~

核心代码
```cpp
const int N = 1e7, NN = 1e7 + 500, P = 20040313;
int n, inv[NN]; 
int main()
{
	inv[1] = 1;
	for (int i=2; i<=N; i++) inv[i] = (1ll * (P - P/i) * inv[P % i]) % P;
	scanf("%d", &n);
	int ans = 0;
	for (int i=1; i<=n; i++) ans = (ans + inv[i]) % P;
	printf("%lld\n", 1ll * n * ans % P);
	return 0;
}
```
（这题大概大家写的代码都差不多吧 233）

---

## 作者：XL4453 (赞：0)

题目分析：

数学题。

对于取到第 $i$ 个不同的球，取到的概率为 $\dfrac{n-i+1}{n}$。

取到的期望次数为：$\dfrac{n}{n-i+1}$。

统计一下期望的总次数就是：$\sum_{i=1}^{n}{\dfrac{n}{n-i+1}}$。

提取 $n$ 得： $n\times\sum_{i=1}^{n}{\dfrac{1}{n-i+1}}$。

等价于： $n\times\sum_{i=1}^{n}{\dfrac{1}{i}}$

也就是： $n\times\sum_{i=1}^{n}i^{-1}$

然后就显然了，线性筛求一下逆元和乘以 $n$ 就结束了。

------------
代码：

```cpp
#include<cstdio>
using namespace std;
long long ans,p=20040313,inv[10000007],n;
int main(){
	scanf("%lld",&n);
	inv[1]=1;
	for(int i=2;i<=n;i++)
	inv[i]=(p-(p/i))*inv[p%i]%p;
	for(int i=1;i<=n;i++)
	ans=(ans+inv[i])%p;
	ans=ans*n%p;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：themarine1982 (赞：0)

首先，这道题我们可以先拆成几个小问题  
  第一个，判断这个树是不是完全二叉树
  ```cpp
bool check(int x, int y){//把编号输进来
	if(x == -1 && y == -1){
		return true;//如果左边的节点和右边的节点都没有子节点就是对称的
	}
	if((x != -1) && (y != -1) && (tree[x].val == tree[y].val)&&check(tree[x].l,tree[y].r) && check(tree[x].r,tree[y].l)){
			return true;//如果左边的节点和右边的节点有对称子节点,并且权值相等，那就继续往下搜
	}
	return false;
}
```
然后寻找一颗最大的对称二叉树
```cpp
int res = 0;//记录最大值
void dfs(int root){
	if(tree[root].l != -1)//看看当前节点是否有左孩子{
		dfs(tree[root].l);//如果有左孩子，往下搜索
		tree[root].size_ += tree[tree[root].l].size_;
	}//计算当前节点连接的个数
	if(tree[root].r!=-1)//看看当前节点是否有右孩子{
		dfs(tree[root].r);//如果有右孩子，往下搜索
		tree[root].size_ += tree[tree[root].r].size_;
	}//计算当前节点连接的个数
	if(check(tree[root].l,tree[root].r)){
		res = max(res, tree[root].size_);
	}//检查以当前节点为根节点的子二叉树是否为对称二叉树，如果是把最大节点数存储一下
}
```
加上输入输出 最终代码为...
```pascal
#include <iostream>
using namespace std;
#define N 1000005
struct Node{
	int l, r;
	int val;
	int size_;
}tree[N];
bool check(int x, int y){
	if(x == -1 && y == -1){
		return true;
	}
	if((x != -1) && (y != -1) && (tree[x].val == tree[y].val)&&check(tree[x].l,tree[y].r) && check(tree[x].r,tree[y].l)){
			return true;
	}
	return false;
}






int res = 0;
void dfs(int root){
	//cout<<"help! I don't back!!";
	if(tree[root].l != -1){
		dfs(tree[root].l);
		tree[root].size_ += tree[tree[root].l].size_;
	}
	if(tree[root].r!=-1){
		dfs(tree[root].r);
		tree[root].size_ += tree[tree[root].r].size_;
	}
	if(check(tree[root].l,tree[root].r)){
		res = max(res, tree[root].size_);
	}
}

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> tree[i].val;
		tree[i].size_ = 1;
	}
	for (int i = 1; i <= n; ++i)
		cin >> tree[i].l >> tree[i].r;
	dfs(1);
	cout << res << endl;

```
这就是最终代码了   

 return 0;  
}



---

## 作者：muller (赞：0)

这是一道裸的概率期望

得到第一个不同的球需要1次，

得到第二个不同的球需要N/（N-1）次 ，

因为只需与第一个球不同即可， 概率是（N-1）/N，需要N/（N-1）次，

得到第三个不同球需要N/（N-2）次，

······

得到第N个不同球需要N/1次，

最后需要次数期望=1+N/（N-1）+N/（N-2）+···N/3+N/2+N/1 次。

直接求分数和就行，最后处理一下输出就行

代码非常短：

```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 20040313;
const int N = 10000005;
ll inv[N], ans = 0; 
int main() {
	int i, n; scanf("%d", &n); inv[1] = 1ll;
	for (i = 2; i <= n; ++i) inv[i] = ((MOD - MOD / i) * inv[MOD % i]) % MOD;
	for (i = 1; i <= n; ++i) ans = (ans + (inv[i] * n) % MOD) % MOD;
	printf("%lld\n", ans); 
	return 0;
}

```


---

