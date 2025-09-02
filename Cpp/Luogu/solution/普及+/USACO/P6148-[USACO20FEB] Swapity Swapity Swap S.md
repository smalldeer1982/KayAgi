# [USACO20FEB] Swapity Swapity Swap S

## 题目描述

Farmer John 的 $N$ 头奶牛（$1\leq N\leq 10^5$）站成一排。对于每一个 $1\leq i\leq N$，从左往右数第 $i$ 头奶牛的编号为 $i$。

Farmer John 想到了一个新的奶牛晨练方案。他给奶牛们 $M$ 对整数 $(L_1,R_1)\ldots (L_M,R_M)$，其中 $1\leq M\leq 100$。他让她们重复以下包含 $M$ 个步骤的过程 $K$（$1\leq K\leq 10^9$）次：

对于从 $1$ 到 $M$ 的每一个 $i$：
- 当前从左往右数在位置 $L_i\ldots R_i$ 的奶牛序列反转她们的顺序。
- 当奶牛们重复这一过程 $K$ 次后，请对每一个 $1\leq i\leq N$ 输出从左往右数第 $i$ 头奶牛的编号。

## 说明/提示

#### 样例解释：
初始时，奶牛们的顺序从左往右为 [$1,2,3,4,5,6,7$]。在这一过程的第一步过后，顺序变为 [$1,5,4,3,2,6,7$]。在这一过程的第二步过后，顺序变为 [$1,5,7,6,2,3,4$]。再重复这两个步骤各一次可以得到样例的输出。

#### 子任务：
- 测试点 $2$ 满足 $N=K=100$。
- 测试点 $3$-$5$ 满足 $K\leq 10^3$。
- 测试点 $6$-$10$ 没有额外限制。

## 样例 #1

### 输入

```
7 2 2
2 5
3 7```

### 输出

```
1
2
4
3
5
7
6```

# 题解

## 作者：Diaоsi (赞：29)

## 题目链接：[传送门](https://www.luogu.com.cn/problem/P6148)
## 思路：
**用快速幂去维护置换**

根据题意，每次操作时都会将区间 $(L_1,R_1)…(L_M,R_M)$ 内的奶牛翻转一次。

由于这个翻转是固定的，所以每次操作奶牛编号的置换也是固定的。

我们可以预处理出一个映射 $f(x)$ 表示 $x$ 经过置换后变成什么。

**预处理的时间复杂度为：**

$$O(nm)$$

此时我们只需要求 $f^k(x)$ 即可得到答案。

通过观察我们发现该置换符合结合律。

### 举个例子：

令 $h$ 表示“先 $f$ 后 $g$ ”的置换。

设 $f=\{2,1,4,3\}~,~g=\{3,1,2,4\}$。 

那么“先 $f$ 后 $g$ ”的映射就是 $\{1,3,4,2\}$ 。

则 $h$ 可以表示为 $h(x)=g(f(x))$ 。

这样我们就可以使用快速幂去求 $f^k(x)$ 。

**总的时间复杂度为：**

$$O(nm+n\log k)$$

## 代 码 放 送：

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,k,l[N],r[N];
struct Permu{
	int m[N];
}a,e;
inline void init(){
	for(int i=1;i<=n;i++)
		a.m[i]=e.m[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l[i],&r[i]);
		reverse(e.m+l[i],e.m+r[i]+1);
	}
}
inline Permu Mul(Permu x,Permu y){
	Permu c;
	for(int i=1;i<=n;i++)
		c.m[i]=x.m[y.m[i]];
	return c;
}
inline void Qpow(int p){
	while(p!=0){
		if(p&1)a=Mul(a,e);
		p>>=1;e=Mul(e,e);
	}
}
int main(){
	freopen("swap.in","r",stdin);
	freopen("swap.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	init();
	Qpow(k);
	for(int i=1;i<=n;i++)
		printf("%d\n",a.m[i]);
	return 0;
}
```
## 鸣谢：[Sweetlemon](https://www.luogu.com.cn/user/25008)

---

## 作者：kradcigam (赞：27)

# 前言

考场上没想到用倍增，呜呜呜~，只写了个找循环节，然后就 $30$ 分。

# 正文
## 分析

考虑用倍增，其实这道题和[这道题](https://www.luogu.com.cn/problem/P3083)是有异曲同工之处的。

我们 $f_{ij}$ 记录第 $j$ 个元素，经过 $2^i$ 次翻转后，这个元素的值。

### 求 $f_{0,j}$

好，那么显然，我们要先求出 $f_{0,j}$。
```cpp
read(n);read(m);read(k);//读入
for(int i=1;i<=m;i++)read(a[i]),read(b[i]);//读入
for(int i=1;i<=n;i++)c[i]=i;//给c数组赋初值
for(int i=1;i<=m;i++)reverse(c+a[i],c+b[i]+1);//模拟
for(int i=1;i<=n;i++)f[0][i]=c[i];//经过1次翻转第i个元素的值为c[i]
```

### 写倍增

因为 $2^i=2^{i-1}+2^{i-1}$

所以，$f_{i,j}=f_{i-1,f_{i-1,j}}$

给第 $j$ 个元素操作 $2^{i-1}$ 次，再操作 $2^{i-1}$ 次，就相当于直接操作 $2^i$ 次。

学过 $LCA$ 的应该都会。

```cpp
for(int i=1;i<=30;i++)
	for(int j=1;j<=n;j++)
		f[i][j]=f[i-1][f[i-1][j]];//就是之前的公式
```

### 得到答案

我们知道，任何一个十进制整数都是可以转成二进制形式

这里的话，我们就拆分 $k$。这里的步骤也很像 $LCA$。

```cpp
for(int i=1;i<=n;i++){
	int x=i,m=k;
	for(int j=30;j>=0;j--)
		if(m>=(1ll<<j)){
			m-=(1ll<<j);//拆
			x=f[j][x];//操作
		}
	writen(x);//输出
}
```
### 复杂度

这个复杂度显然是 $O(n \log k)$ 是一个不错的复杂度。
## 总代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
template<typename T>inline void write(T x){
	if(x<0)putchar('-'),x*=-1;
	if(x>9)write(x/10);
	putchar(x%10+48);
}
template<typename T>inline void writen(T x){
	write(x);
	puts("");
}
const int MAXM=1e2+10,MAXN=1e5+10;
int n,m,k,a[MAXM],b[MAXM],c[MAXN],f[35][MAXN];
int main(){
	read(n);read(m);read(k);
	for(int i=1;i<=m;i++)read(a[i]),read(b[i]);
	for(int i=1;i<=n;i++)c[i]=i;
	for(int i=1;i<=m;i++)reverse(c+a[i],c+b[i]+1);
	for(int i=1;i<=n;i++)f[0][i]=c[i];
	for(int i=1;i<=30;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=f[i-1][f[i-1][j]];
	for(int i=1;i<=n;i++){
		int x=i,m=k;
		for(int j=30;j>=0;j--)
			if(m>=(1ll<<j)){
				m-=(1ll<<j);
				x=f[j][x];
			}
		writen(x);
	}
	return 0;
}
```
# 后记

感谢 @LightningUZ 帮我调了这道题的代码，帮我调出了一个小错误。

如果题解有误，欢迎在下面评论或私信我，使得这篇题解更好。

---

## 作者：泥土笨笨 (赞：21)

先回顾一下比赛时候的心路历程。

每一个区间翻转，复杂度是$O(n)$，每次有最多$100$次翻转，所以一次操作是$100n$的复杂度，题目中n的范围是$1 \leq n \leq 10^5$，那么每次操作都是$10^7$，而总共要做$k$次，$k$的范围是$1 \leq k \leq 10^9$，如果我们真的做$k$次，必然超时。按照这个数据量，真实操作不能超过100次，否则会有超时的风险。

那么第一反应是是否有循环节？理论上确实有，因为一旦走到一个之前见过的完全相同的局面，再往下走就循环了，一共有$n$个数字，最多走$n!$次肯定能走到一个重复的局面，但是这个循环节太长了。也无法证明100步以内一定会循环。

既然$1 \leq k \leq 10^9$，所以$log_2k$在$30$左右，是符合我们的要求的。所以考虑能否类似倍增的思想，把操作“合并”在一起，设一次操作为$f$，那么在$f$的基础上再做一次$f$，得到$f^2$操作。在$f^2$的基础上再做一次$f^2$，得到$f^4$操作……这样我们依次得到每一个这种$2$的幂次操作，把$k$次操作拆成这些$2$的幂次操作连做的形式，就能在$log$时间内完成。（有同学问我：“老师，你是怎么想到这样做的？”多做点题吧，学过矩阵加速DP的话，思路比较像，就容易想到了）

举个例子，看看样例。
```
7 2 2
2 5
3 7
```
初始序列为
```
1 2 3 4 5 6 7
```
按照题意模拟一轮操作以后，得到
```
1 5 7 6 2 3 4
```
表示原来1到7的序列，经过一轮操作会被换成这样。注意这个序列我们要换一种思路来看，这个序列第二个位置上是5，还可以表示，“操作完以后，原来5位置的数，被写到了2位置。”原来如果5位置就是5，当然可以。但是如果原来5位置上是别的数字，还是把那个位置上的数字拿过来。这是后面算法的关键思路。

继续看，在
```
1 5 7 6 2 3 4
```
基础上，我们再做一轮操作。但是这次我们**不按照题意模拟了**。我们直接把它**平方**。为了方便，我们设这个序列为a序列，下标从1开始。设平方之后的结果是b数组。

因为a[1]是1，表示$b[1]$的位置是原来a[1]上的数，所以b[1]=1

因为a[2]是5，表示b[2]是a[5]，所以b[2]=2

因为a[3]是7，表示b[3]是a[7]，所以b[3]=4

以此类推，我们可以求出来b数组，即操作两轮以后的序列是

```
1 2 4 3 5 7 6
```

这和直接按照题目模拟翻转来翻转去得到的结果是一样的！看明白了么？

所以我们在
```
1 2 4 3 5 7 6
```
的基础上，再平方一遍，就能得到操作4遍的结果是什么，然后再把4遍的结果平方一遍，得到8次操作的结果。其实这个结果也可以看成是一种规则，即对于一个原始数组，按照一个规则走一遍，得到一个结果数组。之前我们的原始数组和规则是同一个，但是不是同一个完全可以。

再举一个例子，我们想知道$k=3$的时候的结果。我们已经知道了一步的结果是：（为了方便设为f[1]）
```
1 5 7 6 2 3 4
```
然后做两遍的规则是：(为了方便设为f[2])
```
1 2 4 3 5 7 6
```
那么把f[1]当做原始数组，f[2]当成规则，在f[1]上应用一次f[2]，

因为f[2]的第1个数字是1，所以f[3]的第1个数字是f[1]的第1个数1

因为f[2]的第2个数字是2，所以f[3]的第2个数字是f[1]的第2个数5

因为f[2]的第3个数字是4，所以f[3]的第3个数字是f[1]的第4个数6

以此类推，可以得到f[3]，即三次操作的结果是：
```
1 5 6 7 2 4 3 
```
可以看到，和我们暴力模拟3次的结果是一样的。

因此，我写了一个函数用来做一次运算：

```cpp
//计算从a数组，根据rule的规则，返回运算的结果
vector<int> trans(vector<int> a, vector<int> rule) {
    //定义一个vector来装结果，0位置空着不用，所以申请n+1的长度，初始都给0
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        //结果的i位置是原数组的rule[i]位置上的数
        ans[i] = a[rule[i]];
    }
    return ans;
}
```

第一个问题解决了。我们再来看第二个问题，如何进行k次运算？这里的算法类似于快速幂，如果不懂快速幂请移步先学习一下。写一个init函数，来计算一次运算出来的规则，存在一个vector里面，这个就按照题意模拟就行，初始化一个1到n的序列，然后模拟m次翻转操作。

```cpp
vector<int> init() {
    vector<int> a(n + 1, 0);
    for (int i = 0; i <= n; ++i) {
        a[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        for (int x = l[i], y = r[i]; x < y; ++x, --y) {
            swap(a[x], a[y]);
        }
    }
    return a;
}
```

之后定义一个变量base等于一轮的规则，即init的结果。定义一个a数组表示目前为止的结果。然后看k的最末位，如果是1，在结果上应用一次base，然后base自己平方，再把k除以2，整体看起来特别像快速幂

```cpp
vector<int> a;
    for (int i = 0; i <= n; ++i) {
        a.push_back(i);
    }
    vector<int> base = init();
    while (k) {
        if (k & 1) {
            a = trans(a, base);
        }
        base = trans(base, base);
        k >>= 1;
    }
```

总的代码如下：
```cpp
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;
int n, m, k, l[105], r[105];

vector<int> init() {
    vector<int> a(n + 1, 0);
    for (int i = 0; i <= n; ++i) {
        a[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        for (int x = l[i], y = r[i]; x < y; ++x, --y) {
            swap(a[x], a[y]);
        }
    }
    return a;
}

//计算从a数组，根据rule的规则，返回运算的结果
vector<int> trans(vector<int> a, vector<int> rule) {
    //定义一个vector来装结果，0位置空着不用，所以申请n+1的长度，初始都给0
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        //结果的i位置是原数组的rule[i]位置上的数
        ans[i] = a[rule[i]];
    }
    return ans;
}

int main() {
//    freopen("swap.in", "r", stdin);
//    freopen("swap.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        cin >> l[i] >> r[i];
    }
    vector<int> a;
    for (int i = 0; i <= n; ++i) {
        a.push_back(i);
    }
    vector<int> base = init();
    while (k) {
        if (k & 1) {
            a = trans(a, base);
        }
        base = trans(base, base);
        k >>= 1;
    }
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << endl;
    }
    return 0;
}
```

---

## 作者：tuxiaobei (赞：13)

**本篇题解讲解较为细致，大佬可略过**

### 题意

初始状态 $1\sim N$ 的一个序列，执行 $M$ 个翻转区间操作 $K$ 次。

### 算法1

暴力翻转，时间复杂度 $O(NMK)$ 。 
期望得分：$20$ 分。

### 算法2

我们来仔细观察一下翻转变换，来看一下样例执行第一次的结果：

![](http://study.xndxfz.com/wp-content/uploads/2020/03/批注-2020-03-01-172104.jpg)

一次执行有两种含义：
1.一次执行后序列的值(废话)
**2.一次执行后位置的变化情况(可以知道一个位置的数在一次执行后会跑到哪个位置)**

上图中的箭头即表示位置的变化情况。

还不理解？让我们再来看看第二次执行：

![](http://study.xndxfz.com/wp-content/uploads/2020/03/批注-2020-03-01-172336.jpg)

这下明白了吧，所以我们可以建立 $b$ 数组，

$b_i$ 表示位于 $i$ 位置的数执行一次后会移动至 $b_i$ 位置。

```cpp
for (int i = 1; i <= n; i++) b[a[i]] = i; //建立b数组,a数组为原序列执行一次后的结果
```

|  $i$  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |
| :---: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| $b_i$ |  1   |  5   |  6   |  7   |  2   |  4   |  3   |

接下来我们只需要 $O(N)$ 就可以完成一次执行。

时间复杂度 $O(N(M+K)) $。

时间复杂度瓶颈在于 $K$ 过大。

期望得分：$50$ 分。

### 算法3

发现执行是会出现循环的，执行若干次后会变回原数列，

只要出现循环，我们对循环节取模就可以得到最终的序列了，

看起来是一个很好的优化，然而循环节长度其实非常长，甚至远超过 $K$ ，达到了指数级别(之后会证明)。

所以时间复杂度依然是 $O(N(M+K)) $，期望得分：$50$ 分。

### 算法4

虽然算法3得分没有提高，但给了我们一个很好的思路，**找循环**。

整体的循环节长度很长，但我们来考虑下对于每个数的循环节。

我们再来看一下 $b$ 数组

|  $i$  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |
| :---: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| $b_i$ |  1   |  5   |  6   |  7   |  2   |  4   |  3   |

可以发现有三组循环 $(1\to),(2\to 5 \to),(3 \to 6 \to 4 \to 7 \to)$。

每个数必定都会有且仅属于一个循环，

或者这样理解，把 $i \to b_i$ 看作一条边，每个位置看作点，所有点的入度和出度均为 $1$ 。

因为根据定义可得，一个位置只可能移动至一个位置，是一个一对一映射的关系。

可以看作在图中找环。

我们可以得到所有循环的循坏节长度之和为 $N$ ， $O(N)$  时间就能找到所有循环。

找到循环后简单计算就可以知道全部执行完成后的位置了。

时间复杂度 $O(NM+N)=O(NM)$。

期望得分：$100$ 分。

同时发现整体的循环节长度即为各组循环节长度的最小公倍数，为指数级别。

code：

```cpp
#include <bits/stdc++.h>
#define maxn 200000
using namespace std;

int a[maxn], b[maxn], c[maxn];
bool f[maxn]; //代表数是否已经访问过
int main()
{
	freopen("swap.in", "r", stdin);
	freopen("swap.out", "w", stdout);
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) a[i] = i;
	for (int i = 1, l, r; i <= m; i++) {
		scanf("%d%d", &l, &r);
		reverse(a + l, a + r + 1);
	}
	for (int i = 1; i <= n; i++) b[a[i]] = i;
	for (int i = 1; i <= n; i++) {
		if (f[i]) continue;
		int p = b[i];
		vector<int> v;  //储存循环节
		v.push_back(i);
		while (p != i) v.push_back(p), p = b[p];
		int q = k % (v.size());
		int sz = v.size();
		for (int i = 0; i < sz; i++) {
			f[v[i]] = true;
			c[v[q]] = v[i];
			q++;
			if (q >= sz) q = 0;
		}
	}
	for (int i = 1; i <= n; i++) printf("%d\n", c[i]);
}
```

### 算法5

算法4前半部分序列翻转用平衡树优化，

时间复杂度 $O(M \log N+N)$。

（当然这题完全不需要）

期望得分：$100$ 分。

---

## 作者：CrTsIr400 (赞：9)

这道题刚入手，我的第一反应就是：~~暴力~~**模拟**!

没啥好说的，直接`reverse` $k$ 遍，**时间复杂度 $\operatorname{O}(nmk)$ ，还似乎吃得消。**

结果我看了看数据范围，就吓得一身冷汗。。。

$k\le 10^9,n\le10^5,m\leq10^2$

这模拟只能**骗到 $20$ 分（以内）啊**？

我于是开始**找规律**，结果啥规律也找不出，对于每个数据，都有不同的规律，**循环节**也不好计算。

那——要不使用**判断循环节**？用哈希判重？

不行。如果循环节**太长了**，就大于 $100$ ，**也会把这算法卡掉**。这个大概是$30-40$分的思路。

欸？能不能一次做**多组**操作？能不能**一次做 $l$ 组**？使得时间复杂度大大降低？

理论上可行。比如说你把这个 $l$ 设成 $10^5$ 以上，效率就会大大提升。

但是，实际上这个算法还是很慢。$O(\frac{nmk}{l})$ 这个复杂度其实还是很高，而且万一这个循环节不在第 $l$ 的整数倍位上，这样还要加上一个 $nml$ 。

其实把 $l$ 设成 $\sqrt{k}$ 这种数，时间复杂度会大大减少，到达 $O(nm\sqrt{k})$这种级别。

既然一次做均匀的 $\frac{k}{l}$ 次操作不行，我能不能做不均匀的操作？**比如对于 $i$ 次，就做 $2^i$ 组操作？能否实现？**

恭喜你，你懂得了这道题要使用**倍增**。

这个**倍增**，顾名思义，就是**成倍增长**。

举个例子：**倍增求`LCA`**。

`LCA`是啥？就是树上**两个点的最近公共祖先。**

然后我们就可以使用**倍增。**

指定两个节点，让你每个节点往上跳$2^i$辈（更准确的说法是每个节点往上$2^i$代祖先），如果碰到了，就可以更加细化，往下继续二分。

推荐做`LCA`模板题嗷。

倍增必要的小工具：

把一个数二进制分解。

首先，可以 $O(1)$ 求出这个数的二进制最高位（也可以不用求，对于$10^9$以内的数据，从$30$往下搜就可以，对于$10^{18}$数量级，$63$往下搜绰绰有余）。

然后让 $i$ 指针往下搜，如果这个数**大于等于**$2^i$，就**减去**$2^i$。顺便让另外求值的那个变量与这个$f[i]$有关联。

我们可以确定一个倍增数组$f[i][j]$，

表示 $a$ 数组在经过了 $2^i$次操作后所生成的新的$a_j$。

然后预处理完成后，就开始二进制拆分。

具体看代码。

```cpp
	in(n,m,k);
	Fu(i,1,n)f[0][i]=i;
	Fu(i,1,m)in(t1,t2),reverse(a+t1,a+t2+1);
	Fu(i,1,30)Fu(j,1,n)f[i][j]=f[i-1][f[i-1][j]];
	Fu(i,1,n)
	{
		int t=k,x=i;
		Fd(j,30,0)
		if(t>=(1<<j))t-=(1<<j),x=f[j][x];
		out(x);
	}
```



---

## 作者：信守天下 (赞：6)

## [题目传送门](https://www.luogu.com.cn/problem/P6148)
## 思路
操作数量非常庞大，分析区间的变化非常困难。

但不难发现，操作时不同位置之间是不会相互影响的，所以可以逐个位置进行分析。

对于每个位置，我们可以计算出一组操作后它变换到的位置。

由于操作是可逆的，所以经过⼀定数量的操作后，必然会回到最初的位置。

这些位置便构成了⼀个环，每组操作其实就是让位置在环上移动⼀下。

那么利⽤同余就可以快速求出组操作后的位置。

我们只要找到每一个环，然后对每个环上的位置统一进行求解即可。

## 复杂度分析
### 时间复杂度
计算位置变化 $O(NM)$ 。

找环与求解总共 $O(N)$ 。

总时间复杂度为 $O(NM)$。
### 空间复杂度
记录位置的变化 $O(N)$ 。

记录每个环 $O(N)$ 。

总空间复杂度为 $O(N)$ 。
## $code$
~~~cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
const int kMaxM = 101;
int a[kMaxN], p[kMaxN], b[kMaxN], l[kMaxM], r[kMaxM];
int n, m, k;
int main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    cin >> l[i] >> r[i];
  }
  for (int i = 1; i <= n; i++) {  // 计算每个位置一轮反转后的位置
    p[i] = i;
    for (int j = 1; j <= m; j++) {  // 枚举m次反转
      if (p[i] >= l[j] && p[i] <= r[j]) {
        p[i] = l[j] + r[j] - p[i];
      }
    }
  }
  for (int i = 1, t; i <= n; i++) {  // 枚举每个位置计算结果
    if (!a[i]) {                     // 当前位置尚未计算
      b[t = 0] = i;                  // 初始化起点
      do {                           // 寻找变换的环
        b[t + 1] = p[b[t]];
      } while (b[++t] != b[0]);
      for (int j = 0; j < t; j++) {  // 计算环上每个位置的变换
        a[b[(j + k) % t]] = b[j];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << a[i] << endl;
  }
  return 0;
}
~~~

---

## 作者：45dino (赞：5)

这道题是铜组最后一题的改编版，当时做铜组时打了个暴力就AK了，没想到银组还有。

可以想到倍增，因为无法算出循环的周期，而枚举会爆。

用一个change函数计算从n次操作后再进行m次操作，算出$2^0$,$2^1$,$2^2$……次操作后的结果再相乘。

问题来了，如何写这个change函数？

先手玩一下样例
```
1234567//操作0次&&第一组
  ||
 _  _
 \  /
  \/
1576234//操作1次&&第二组
  ||
 _  _
 \  /
  \/
（1243576//操作3次&&第三组（不加入数组））
  ||
 _  _
 \  /
  \/
1234567//操作4次&&真正的第三组
```
可以发现，在第二组转向第三组时，第二组的第一位是第三组的第一位(第二组中一的位置），第二位是第三组的第五位（第二组中二的位置），第三位是第三组的第六位（三的位置），第四位是第三组的第七位……

于是发现，操作n次再操作1次就是“调用”第一组；

操作n次再操作2次就是“调用”第二组；

操作n次后再操作4次就是“调用”真正的第三组……

于是，问题便迎刃而解。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int s[35][100001];
void change(int x,int y)
{
	for(int i=1;i<=n;i++)
	{
//		cout<<s[x][i]<<" ";
		s[x][i]=s[y][s[x][i]];//消化一下这句代码
//		cout<<s[x][i]<<endl;
	}
	return ;
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		s[0][i]=i;
	for(int i=1;i<=n;i++)
		s[1][i]=s[0][i];
	for(int i=1;i<=m;i++)
	{
		int a,b;
		cin>>a>>b;
		for(int i=a;i<=(a+b)/2;i++)
			swap(s[1][i],s[1][a+b-i]);//第一次交换，即求第一组时要手动转换
	}
	for(int i=2;i<=31;i++)
	{
		for(int l=1;l<=n;l++)
			s[i][l]=s[i-1][l];
		change(i,i-1);
	}
	for(int i=1;i<=n;i++)
		s[34][i]=s[0][i];//34是随便用的，并一定是34.
	int cnt=1;
	while(k)
	{
		if(k%2)
		{
			change(34,cnt);
		}	
		cnt++;
		k/=2;//二进制转换
	}
	for(int i=1;i<=n;i++)
		cout<<s[34][i]<<endl;
	return 0;
}
```


---

## 作者：wylt (赞：5)

USACO 2020 February 白银组T1 Swapity Swapity Swap

原题面（英文）：[http://www.usaco.org/index.phppage=viewproblem2&cpid=1014](http://www.usaco.org/index.php?page=viewproblem2&cpid=1014)

官方题解（英文）：[http://www.usaco.org/current/data/sol_swap_silver_feb20.html](http://www.usaco.org/current/data/sol_swap_silver_feb20.html)


------------
### 题意简述

对于原始序列为 $1-N$ 的 $N$ 个数，你需要每次对它进行 $M$ 次操作，反转区间 $\left[l_{i}\ ,r_{i}\right]$ ，一共进行 $K$ 轮，输出最后的序列。

其中 $N\le10^5,M\le100,K\le10^9$ 。

### 题目分析

数据这么大，模拟肯定不行，但是我们可以发现 $N*M$ 只有 $10^7$ ，

而如果加上 $K$ 直接就超过时间复杂度了，

所以无论如何 $K$ 都不能以 $O(K)$ 出现在复杂度内，

但同样我们可以发现 $O(N*M)$ 是可以的。

所以我们可以尝试对于初始序列进行一轮操作，得出在 $O(N*M)$ 内的序列，

我们可以得出一个结论：就是这 $M$ 次操作仅仅是换位置，而不是换数字。

要怎么想呢？因为对于初始的序列 $1-N$ 我们可以把它看作数组的位置下标，

那么每次操作不就是调换位置，不用管此时在这个位置上的数，

也就是我们只要得出进行 $M$ 次操作后第 $i$ 位会换到的位置并标记，

每一轮结束后就只用调位置就行了，不用再模拟一遍 $M$ 。

拿样例来解释，就是：

			初始序列为 1,2,3,4,5,6,7
        		先处理出进过 M 次得出的序列为 1,5,7,6,2,3,4
                	可以得出1->1,2->5,3->6,4->7,5->2,6->4,7->3
                    上面的数字全都代表数组下标，比如下标2上的数变到了下标5上
                    那么第二轮就是 1,5,7,6,2,3,4 中，位置1上的数不变，
                    位置2上的数到了位置5，位置3上的数到了位置6……
                    则最后序列就变为 1,2,4,3,5,7,6
那么此时的时间复杂度就成了 $O(NM+NK)$ 。

再进一步思考，我们可以发现一个**更广泛的结论** ：

经过 $a$ 次 $M$ 操作后序列为 $p_{1},p_{2},p_{3}…,p_{n-2},p_{n-1},p_{n}$

(即下标 $i$ 上的数变成了下标 $p_{i}$ 上的数)

经过 $b$ 次 $M$ 操作后序列为 $q_{1},q_{2},q_{3}…,q_{n-2},q_{n-1},q_{n}$

则经过 $a+b$ 次操作后的序列为 $p_{q_{1}},p_{q_{2}},p_{q_{3}}…,p_{q_{n-2}},p_{q_{n-1}},p_{q_{n}}$

或 $q_{p_{1}},q_{p_{2}},q_{p_{3}}…,q_{p_{n-2}},q_{p_{n-1}},q_{p_{n}}$

其中 $a+b$ 次操作可理解为先经过 $a$ 次操作，再经过 $b$ 次操作。

如果不太理解，可以以 $1-N$ 的初始序列自己推一下。

所以此时就出现了一个简化 $K$ 的好方法，就是用快速幂的思想 $\log(K)$ 次求出最终序列

时间复杂度 $O(NM+N\log(K))$

还有一点是反转时可以用 $a(i)=a(l+r-i)$ 来做。

------------
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int a[100005];
int b[100005];
int c[100005];

int main(){
	int n,m;
	long long k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		a[i]=i;
	}
	int l,r;
	//先求出一轮完的序列 
	while(m--){
		cin>>l>>r;
		for(int i=l;i<=r;i++){
			b[i]=a[l+r-i];
		}
		for(int i=l;i<=r;i++){
			a[i]=b[i];
		}
		//b[i]辅助a[i]反转 
	}
	//用c数组存第一轮完的位置，a相当于快速幂中的res 
	for(int i=1;i<=n;i++){
		c[i]=a[i];
		a[i]=i;//给a初始值，相当于快速幂中的res=1 
	}
	while(k>0){
		if(k&1){
			//执行a+c 
			for(int i=1;i<=n;i++){
				a[i]=c[a[i]];
				//这里就不用辅助数组了，因为不是在一个数组上对换 
			}
		}
		//执行c+c 
		for(int i=1;i<=n;i++){
			b[i]=c[c[i]];
		}
 		for(int i=1;i<=n;i++){
			c[i]=b[i];
		}
		k>>=1;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<endl;
	}
	return 0;
}

```


---

## 作者：UperFicial (赞：2)

我们定义 $m$ 次操作为一次操作。

我们知道：$2^i=2^{i-1}+2^{i-1}$，倍增的核心就是这玩意儿。

设 $f_{i,j}$ 为 $j$ 号元素经过 $2^i$ 次操作到了哪个位置。

很容易想到 $j$ 先通过 $2^{i-1}$ 次操作到达的位置在通过 $2^{i-1}$ 操作到达的位置即为通过 $2^i$ 次操作到达位置，因为 $2^i=2^{i-1}+2^{i-1}$。

所以就可以递推，$f_{i,j}=f_{i-1,f_{i-1,j}}$。

对于初始化，我们对于 $f_{0,j}$ 特就是一次操作可以暴力。

这样我们拆分 $k$ 变成若干个 $2$ 次幂的数相加，就可以得到 $i$ 位置经过 $k$ 次操作到达的位置。

然后这道题就做完了。

---

## 作者：tommymio (赞：2)

考虑把 $m$ 个步骤合成一次操作，将每次操作看成一次置换群的运算。

这样问题就转化成这个置换的 $k$ 次幂，显然可以快速幂 $O(n \log k)$ 啊，但是考虑到置换运算的特殊性，还可以优化。

我比较菜，只会一个 $O(n)$ 的做法，总时间复杂度是 $O(nm)$ 的，能过就行（雾

**迷思：算法的瓶颈在合成 $m$ 个步骤的部分，考虑能否 $O(n+m)$ 处理出将这 $m$ 个步骤合成后的操作。**

根据置换的性质，我们知道一个置换可以被拆成若干个不交的循环置换的运算。所以这样我们就可以独立处理每一个循环置换了！

而对于每一个循环置换，由于两两不交，我们又可以独立处理一个循环置换内的每一位数。对于每一个循环置换我们一遍处理完，这样均摊就是 $O(n)$ 的了，非常好想。

算法大概思路就是这样，不需要使用任何数据结构。

使用 $\text{Splay}$ 处理合成步骤的部分确实可以做到 $O(m \log n)$，但是意义并不大。想一想，有没有 $O(n+m)$ 的做法呢（~~您图灵奖预定了~~

```cpp
#include<cstdio>
#include<vector>
std::vector<int> cyc[100005];
int a[100005],mp[100005],rk[100005],bel[100005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();} 
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int gcd(int a,int b) {return b==0? a:gcd(b,a%b);}
inline void swap(int &x,int &y) {int tmp=x;x=y;y=tmp;}
inline void Myreverse(int *des,int l,int r) {for(register int i=0;i<r-l&&l+i<r-i;++i) swap(des[l+i],des[r-i]);}
signed main() {
	int n=read(),m=read(),k=read(),T=0;
	for(register int i=1;i<=n;++i) a[i]=bel[i]=i;
	for(register int i=1;i<=m;++i) {
		int l=read(),r=read();
		Myreverse(a,l,r);
	}
	for(register int i=1;i<=n;++i) {mp[i]=a[i];a[i]=i;rk[i]=-1;}
	for(register int i=1;i<=n;++i) {
		int cur=mp[i],tot=1;
		if(rk[i]!=-1) continue;
		cyc[i].push_back(i);
		rk[i]=0; rk[cur]=1; 
		while(cur!=i) {
			cyc[i].push_back(cur);
			bel[cur]=i;
			rk[mp[cur]]=rk[cur]+1;
			++tot; cur=mp[cur];
		}
	}
	for(register int i=1;i<=n;++i) {
		int fx=bel[i];
		int round=k%cyc[fx].size();
		printf("%d\n",cyc[fx][(rk[i]+round)%cyc[fx].size()]);
	}
	return 0; 
}
```







---

## 作者：7KByte (赞：2)

题意

>给定一个$1\sim N(N\le10^5)$排列，定义一次操作是将$M(M\le10^2)$个区间翻转，求$K(K\le10^9)$次操作后的排列。


分析

显然我们可以在$\operatorname{O(NM)}$的时间内求出一次操作后的排列，记作$\mathrm{P}$。

$\mathrm{P_i}$则表示经过一次操作后原来位置$i$上的数移到了位置$\mathrm{P_i}$。每次操作的位移都是相同的。

这样我们可以考虑倍增优化这个过程，$\mathrm{F_{i,j}}$表示位置$i$上的数在操作$2^j$次后的最终位置。

直接转移即可，方程$F_{i,j}=F_{F_{i,j-1},j-1}$。

时间复杂度$\operatorname{O(NM+NlogK)}$，代码简单不贴$\cdots$

但是这篇题解并没有结束因为还有更好的方法

如果我们将每个位置看作一个节点，整个排列看作图，$\mathrm{P}$看作边。

因为每个节点都是一进一出，所以整张图的一个环的森林（包括**自环**）。

我们$DFS$出每个环的长度，直接用$\mathrm{K}\ \operatorname{mod\ Len}$，余数直接$\operatorname{O(1)}$处理即可。

时间复杂度$\operatorname{O(NM)}$。

```cpp
#include<cstdio>
#include<algorithm>
#define N 100005
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,m,k,p[N],v[N],a[N];
int sta[N],tp;
void dfs(int x){
	sta[tp++]=x;v[x]=1;
	if(!v[p[x]])dfs(p[x]);
}
void work(){
	rep(i,1,n)if(!v[i]){
		tp=0;
		dfs(i);
		int step=k%tp;
		rep(j,0,tp-1)
		  a[sta[j]]=sta[(j+step)%tp];
		  //,cout<<sta[j]<<" ";
		//cout<<endl;
	}
}
int main(){
	//freopen("swap.in","r",stdin);
	//freopen("swap.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,n)p[i]=i;
	rep(i,1,m){
		int l,r;scanf("%d%d",&l,&r);
		rep(j,l,(l+r)>>1)swap(p[j],p[r-j+l]);
	}
	work();
	rep(i,1,n)printf("%d\n",a[i]);
	return 0;
}
```

其实这个算法还可以继续优化，我们对序列建``Splay Tree``，快速进行旋转操作。

时间复杂度$\operatorname{O(MlogN+N)}$，代码太复杂不贴$\cdots$

---

## 作者：zzw4257 (赞：1)

## 【S】交换Swapity Swapity Swap

> 给定初始排列$\{1,2\cdots n\}$
>
> 定义每次操作为对$\forall i\in[1,m]$,将排列的$l_i$到$r_i$项下标翻转
>
> 求执行$K$次操作后的排列

设操作一次后的**结果**是$\{p_i\}$

定义置换$\pi=\begin{pmatrix}1&2&\cdots&n\\p_1&p_2&\cdots&p_n\end{pmatrix}$

根据~~经验~~可知排列与置换一一对应，其实是说这样一个到达排列的**操作迭代**和**置换叠加**对应

通过这个结论我们就可以实现置换叠加了

置换叠加或者说乘法是具有结合律的因此可以倍增

---

## 作者：xiaozeyu (赞：1)

上面的人一个个都用 c++ reverse函数

我这有种更平和的方法--暴力

但上面的人没给多高的评价（对于暴力）

比如

![](https://cdn.luogu.com.cn/upload/image_hosting/rt7fz3qw.png)

但自信点 啊

![](https://cdn.luogu.com.cn/upload/image_hosting/mgm70ert.png)

可以看到6个点都可以水，这60分在比赛中是可以必拿的暴力，必须要学会啊！！



------------


可以列表找找规律

![](https://cdn.luogu.com.cn/upload/image_hosting/bbo7geto.png)

不会函数交换，直接用while

```cpp
int x,y;
scanf("%d%d",&x,&y);
while(x<y)
{
	swap(a[x],a[y]);
   x++;
	y--;
}
```



可以每次把每个数字换位置:

```cpp
for(int i=1;i<=n;i++)
{
	int now=i;
	bool flag=false;
	for(int j=1;j<=k;j++)
	{
		now=a[now];
		if(now==i&&!flag)
		{
			j=k-k%j;
			flag=true;
		}	
	printf("%d\n",now);
}
```


------------


因为直接n*k 太慢了

所以需要 j=k-k%j; 

找规律节约时间（一次够了）

谁说时间慢、分低？？

你看

![](https://cdn.luogu.com.cn/upload/image_hosting/vfhdvc4z.png)


还行，上代码

------------


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010];
int m,k;
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) a[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		while(x<y)
		{
			swap(a[x],a[y]);
			x++;
			y--;
		}
	}
	for(int i=1;i<=n;i++)
	{
		int now=i;
		bool flag=false;
		for(int j=1;j<=k;j++)
		{
			now=a[now];
			if(now==i&&!flag)
			{
				j=k-k%j;
				flag=true;
			}
		}	
		printf("%d\n",now);
	}
}
```


---

## 作者：yuzhechuan (赞：1)

### 题解：

很容易发现从某一个位置出发，经过一次操作后的终点是固定的

将这种转移关系转化成有向边，则每个点有且只有一条出边

显然的，我们得到了一棵基环内向树森林

对于环上的点，$k$次操作就相当于直接在环上转圈圈，记录环上的点的顺序再取个模即可

对于树上的点，我们可以从树与环的连接点作为树根向下扩展，同时开栈记录到根路径上每个深度的点的编号，于是往下做的同时额外判一下这个栈里的元素就好了（注意这边是要建反向边的）

---

思维难度比较低，代码可能较长，需要一点STL的基础知识？

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=1e5+5,M=105;
int mp[N],l[M],r[M],lim,st[N],en,h[N],low[N],dfn[N],scc[N],nxt[N],d[N],cnt,id[N],sn,ans[N],k,n,m;
bool v[N];
vector<vector<int> > record;

struct edge{
	int n,v;
}e[N];

void add(int x,int y){
	e[++en]=(edge){h[x],y};
	h[x]=en;
}

void tarjan(int x){ //正常tarjan找环
	st[++lim]=x;
	v[x]=1;
	dfn[x]=low[x]=++cnt;
	if(!dfn[nxt[x]]){
		tarjan(nxt[x]);
		low[x]=min(low[x],low[nxt[x]]);
	}
	else{
		if(v[nxt[x]]) low[x]=min(low[x],dfn[nxt[x]]);
	}
	if(low[x]==dfn[x]){
		sn++;
		int top;
		for(;;){
			top=st[lim--];
			v[top]=0;
			scc[top]=sn;
			if(top==x) break;
		}
	}
}

void dfs(int x,int deep){
	d[deep]=x; //更新栈
	if(k<=deep) ans[d[deep-k]]=x; //这种情况下不会走到环里，直接访问栈就好了
	else{
		int k=::k; //双冒号是全局变量
		k-=deep; //减掉到树根部分的长度
		k%=record[mp[scc[d[0]]]].size(); //在环上转圈圈
		ans[record[mp[scc[d[0]]]][(k+id[d[0]])%record[mp[scc[d[0]]]].size()]]=x;
	}
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v;
		if(scc[y]==scc[x]) continue;
		dfs(y,deep+1);
	}
}

signed main(){
	read(n);read(m);read(k);
	for(int i=1;i<=m;i++) read(l[i]),read(r[i]);
	for(int i=1;i<=n;i++){
		int &pos=nxt[i];
		pos=i;
		for(int j=1;j<=m;j++) if(l[j]<=pos&&pos<=r[j]) pos=l[j]+r[j]-pos; //处理出每个位置出发会到哪
		add(pos,i); //连反向边
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i); //找环
	for(int i=1;i<=n;i++) if(scc[nxt[i]]==scc[i]&&!v[scc[i]]){
		int x=nxt[i];
		v[scc[i]]=1;
		vector<int> ring;
		id[i]=0;
		ring.push_back(i);
		mp[scc[i]]=record.size(); //mp表示这是第几个环
		while(x^i) id[x]=ring.size(),ring.push_back(x),x=nxt[x];//遍历一遍这个环，id表示当前点在环里的位置
		record.push_back(ring); //塞进环的集合里
	}
	for(int i=1;i<=n;i++) if(scc[nxt[i]]==scc[i]) dfs(i,0); //是一个树与环的交点就往下拓展
	for(int i=1;i<=n;i++) write(ans[i]),puts("");
}
```

---

## 作者：saihaze (赞：0)

## 为什么会想到倍增？
此题有一种朴素做法——先模拟出每进行一轮变换，原本在位置i的牛会来到的位置，记为 $f[i]$ ；随后对于每头牛，以 $O(K)$ 的时间复杂度模拟出 $K$ 轮变换后的位置。总时间复杂度为 $O(NK)$。

然而，$K$ 实在太大了，这让我们无法接受。于是可以考虑倍增，将 $K$ 变成 $\log_2{k}$，具体做法是求出 $dest[i, j]$，表示经过 $2^j$ 轮变换后原本在位置 $i$ 的牛的新位置。然后利用二进制拆分的思想，用若干个 $2^p$ 拼出 $K$ 来。
## 代码实现
```c
#include <stdio.h>

int n, m;
long long k;
int l[101], r[101];

// dest[i][j]表示位置在i的牛，经过2^j轮变换到达的位置。
// 根据倍增的思想，有以下状态转移方程：
// dest[i][j] = dest[dest[i][j - 1]][j - 1]
int dest[100001][31];

// 利用朴素的模拟预处理出f[i][0]，也就是经过一轮变换后每头牛到达的位置。
void preprocess(void) {
    int id[100001];
    for (int i = 1; i <= n; i++) {
        id[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int* itr1 = id + l[i];
        int* itr2 = id + r[i];
        while (itr1 < itr2) {
            int tmp = *itr1;
            *itr1 = *itr2, *itr2 = tmp;
            itr1++, itr2--;
        }
    }
    for (int i = 1; i <= n; i++) {
        dest[id[i]][0] = i;
    }
}

// 利用状态转移方程递推。
void dp(void) {
    for (int j = 1; j < 31; j++) {
        for (int i = 1; i <= n; i++) {
            dest[i][j] = dest[dest[i][j - 1]][j - 1];
        }
    }
}

int main(void) {
    //freopen("swap.in", "r", stdin);
    //freopen("swap.out", "w", stdout);
    scanf("%d%d%lld", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", l + i, r + i);
    }
    preprocess(), dp();
    int id[100001];
    // 利用二进制拆分思想，得到最终答案。
    // 注：每一个整数都能表示为若干个2的幂的和。
    for (int i = 1; i <= n; i++) {
        int pos = i;
        for (int j = 0; j < 31; j++) {
            if (k & 1LL << j) {
                pos = dest[pos][j];
            }
        }
        id[pos] = i;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d\n", id[i]);
    }
    return 0;
}
```


---

## 作者：Ezis (赞：0)

一开始想到一个暴力（当然超时）。

$O(NK)$的算法。

但在枚举样例后发现。

### 出现了重复！

能否找寻环节呢？

~~可以，但~~超时……

再去枚举样例，发现他可以构造出一个环！

把第一次变换后的序列和初始序列在一起，再对应连边。

最后构造一个栈，枚举图中的环，栈顶元素为第一个我们要找的值，接下来不断循环枚举，直到再次找到 $a[i]$ 。

时间复杂度： $O(nm)$ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int maxm=105;
int n,m,k;
int l[maxm],r[maxm];
int ans[maxn],b[maxn],s[maxn];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	memset(ans,-1,sizeof(ans));
	for(int i=1;i<=m;i++)
		scanf("%d%d",&l[i],&r[i]);
	for(int i=1;i<=n;i++)
		b[i]=i;
	for(int i=1;i<=m;i++){
		int mid=l[i]+(r[i]-l[i])/2;
		for(int j=l[i];j<=mid;j++)
			swap(b[j],b[l[i]+r[i]-j]);
	}
	for(int i=1;i<=n;i++){
		if(ans[i]!=-1)
			continue;
		s[0]=i;
		int j=i,cnt=0;
		while(b[j]!=s[0]){
			s[++cnt]=b[j];
			j=b[j];
		}
		for(int j=0;j<=cnt;j++)
			ans[s[j]]=s[(j+k)%(cnt+1)];
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

