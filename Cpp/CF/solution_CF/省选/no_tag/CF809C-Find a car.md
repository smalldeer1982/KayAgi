# Find a car

## 题目描述

After a wonderful evening in the restaurant the time to go home came. Leha as a true gentlemen suggested Noora to give her a lift. Certainly the girl agreed with pleasure. Suddenly one problem appeared: Leha cannot find his car on a huge parking near the restaurant. So he decided to turn to the watchman for help.

Formally the parking can be represented as a matrix $ 10^{9}×10^{9} $ . There is exactly one car in every cell of the matrix. All cars have their own machine numbers represented as a positive integer. Let's index the columns of the matrix by integers from $ 1 $ to $ 10^{9} $ from left to right and the rows by integers from $ 1 $ to $ 10^{9} $ from top to bottom. By coincidence it turned out, that for every cell $ (x,y) $ the number of the car, which stands in this cell, is equal to the minimum positive integer, which can't be found in the cells $ (i,y) $ and $ (x,j) $ , $ 1<=i&lt;x,1<=j&lt;y $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809C/ae332bca5d9d01e82f5b508b0b8ed89c69aaabc8.png)The upper left fragment $ 5×5 $ of the parkingLeha wants to ask the watchman $ q $ requests, which can help him to find his car. Every request is represented as five integers $ x_{1},y_{1},x_{2},y_{2},k $ . The watchman have to consider all cells $ (x,y) $ of the matrix, such that $ x_{1}<=x<=x_{2} $ and $ y_{1}<=y<=y_{2} $ , and if the number of the car in cell $ (x,y) $ does not exceed $ k $ , increase the answer to the request by the number of the car in cell $ (x,y) $ . For each request Leha asks the watchman to tell him the resulting sum. Due to the fact that the sum can turn out to be quite large, hacker asks to calculate it modulo $ 10^{9}+7 $ .

However the requests seem to be impracticable for the watchman. Help the watchman to answer all Leha's requests.

## 说明/提示

Let's analyze all the requests. In each case the requested submatrix is highlighted in blue.

In the first request $ (k=1) $ Leha asks only about the upper left parking cell. In this cell the car's number is $ 1 $ . Consequentally the answer is $ 1 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809C/d2875ff3db76503beed44fa5c085d5d3869ee951.png)

In the second request $ (k=5) $ suitable numbers are $ 4,1,2,3,2,1 $ . Consequentally the answer is $ 4+1+2+3+2+1=13 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809C/ede1b276e2f90d48fe9a9d6eefb80fff17357cda.png)

In the third request $ (k=10000) $ Leha asks about the upper left frament $ 5×5 $ of the parking. Since $ k $ is big enough, the answer is equal to $ 93 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809C/34d4b59403122816fc368bbef865be8d24e23c43.png)

In the last request $ (k=2) $ none of the cur's numbers are suitable, so the answer is $ 0 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809C/c06af08c1e07e51a52a8f851e5994e563f76af08.png)

## 样例 #1

### 输入

```
4
1 1 1 1 1
3 2 5 4 5
1 1 5 5 10000
1 4 2 5 2
```

### 输出

```
1
13
93
0
```

# 题解

## 作者：zhoukangyang (赞：21)

[来蒟蒻的博客园里来看 /kel](https://www.cnblogs.com/zkyJuruo/p/14356706.html)

题解区里面写的都是数位 $dp$，蒟蒻来一个奇怪的做法。

通过打表发现这是一个分形，然后可以发现 $a_{i, j} = (i - 1) \oplus (j - 1) + 1$ （蒟蒻也不知道怎么证明）

考虑把这个矩阵转化为前缀和。现在我们要求的是 $f(x, y) = \sum\limits_{i = 0}^{x-1} \sum\limits_{j = 0}^{y-1} [i \oplus j + 1 \le t] i \oplus j + 1$

这个东西可以用类似于二维树状数组的东西来搞。把这个前缀和分成很多个矩阵，每个矩阵都是 $(x - lowbit(x), x), (y - lowbit(y), y)$ 的形式。

我们让 $lowbit(x) \ge lowbit(y)$ 

发现对于每一个区间内的 $y$ 坐标，那么他们异或上 $x$ 坐标区间后的值的集合是固定的！让 $t = (x - lowbit(x) ) \oplus (y - lowbit(y))$，那么 $y$ 坐标异或上 $x$ 坐标区间后的值是一段区间，区间都是 $[t, t + lowbit(x))$ (注意之后还要 $+1$)

时间复杂度 $\Theta(T \log r_1 \log r_2)$

代码很好写：

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++)
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define ull unsigned long long
#define db double
#define pii pair<int, int>
#define mkp make_pair
using namespace std;
const int N = 1e3 + 7;
const int mod = 1e9 + 7;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar();
	return x * f;
}
int n, m, T;
int Sum(int l, int r) {
	return (ll) (r - l + 1) * (l + r) / 2 % mod;
}
int Get(int l1, int r1, int l2, int r2, int k) {
	if(r1 - l1 < r2 - l2) swap(l1, l2), swap(r1, r2);
	int mn = (l1 ^ l2), len = r1 - l1;
	mn ^= (mn & (len - 1));
	if(k <= mn) return 0;
	return (ll) (r2 - l2) * Sum(mn + 1, min(k, mn + len)) % mod;
}
int work(int x, int y, int k) {
	int res = 0;
	for(int i = x; i; i -= (i & -i)) for(int j = y; j; j -= (j & -j)) (res += Get(i - (i & -i), i, j - (j & -j), j, k)) %= mod;
	return res;
}
void Main() {
	int l1 = read(), l2 = read(), r1 = read(), r2 = read(), k = read();
	printf("%d\n", ((work(r1, r2, k) - work(l1 - 1, r2, k) - work(r1, l2 - 1, k)
	 + work(l1 - 1, l2 - 1, k)) % mod + mod) % mod);
}
int main() {
	T = read();
	while(T--) Main();
	return 0;
}
```

---

## 作者：zhylj (赞：12)

[获得更不好的阅读体验，你可以前往我的博客](http://zhylj.cc/index.php/archives/59/)。

观察样例可以发现，最开始的 $4\times 4$ 的每一行 / 每一列都包含了 $1,2,3,4$ 四个元素。再注意到表格有一部分是重复的，于是猜想：

**引理 1**：对于左上角 $2^{n}\times 2^n$ 大小的矩形，每一行每一列都包含 $1,2,\cdots,2^n$ 的数。

**证明**：考虑对 $n$ 施归纳法，当 $n = 1$ 时显然成立。

否则当 $n > 1$ 时由归纳假设左上角的 $2^{n-1}\times 2^{n-1}$ 矩形的每行每列都包含了 $1,\cdots,2^{n-1}$，故左下角和右上角的 $2^{n-1}\times 2^{n-1}$ 矩形不可能包含在 $1,\cdots,2^{n-1}$ 之中的数，这相当于把 $\operatorname {mex}$ 的「最小正整数」的限制，变为「$>2^{n-1}$ 的最小整数」的限制。故把左上角的数加上 $2^{n-1}$ 放在左下角和右上角即是新的方案。而对于右下角的数，只受内部和右上角、左下角的影响，但左上角、右下角又全部超过了 $2^{n-1}$，所以实际上不可能影响到它，故这部分的数也就和左上角完全相同了。

容易验证新的矩阵仍然满足条件。

**引理 2**：$a_{i,j}=(i-1)\oplus (j-1) + 1$，其中 $\oplus$ 为按位异或。

**证明**：考虑先前的构造方法，假如我们把整个矩阵所有数减一，并且行列的编号也全部减一，那么我们递归的过程实际上是在依次考察 $i,j$ 的最高位：若 $i,j$ 的最高位不同（位于左下角或右上角），则加上 $2^{n-1}$，然后去掉最高位（进入左上角）。可以发现这就是异或的过程。

接下来我们考虑直接把整个矩阵所有数减一，并且行列的编号也全部减一后的答案。

考虑数位 dp，首先矩阵可以拆成四个前缀，然后记 $f_{0/1,0/1,0/1,n}$ 表示考虑了最高 $n$ 位，$i$ 是否顶到了上界，$j$ 是否顶到了上界，$i\oplus j$ 是否顶到了上界的方案数。转移考虑直接枚举 $i,j$ 在这一位分别是什么，判断一下是否合法以及是否继续顶着上界即可。

[代码链接](https://codeforces.ml/contest/809/submission/129928248)。

---

## 作者：myee (赞：5)

### 思路

#### 转化题意

注意到这个“没有出现过的最小正整数”很不舒服。

改定义：

$$b_{x,y}=a_{x+1,y+1}-1$$

则我们有

$$b_{x,y}=\operatorname{mex}(\{b_{x,k}|0\le k<y\}\cup\{b_{k,y}|0\le k<x\})$$

而我们所求的即

$$\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}[a_{i,j}\le k]a_{i,j}=\sum_{i=x_1-1}^{x_2-1}\sum_{j=y_1-1}^{y_2-1}[b_{i,j}<k](b_{i,j}+1)$$

设

$$f_k(x,y)=\sum_{i<x}\sum_{j<y}[b_{i,j}<k]$$

$$g_k(x,y)=\sum_{i<x}\sum_{j<y}[b_{i,j}<k]b_{i,j}$$

$$h_k=f_k+g_k$$

于是即求 

$$h_k(x_2,y_2)-h_k(x_2,y_1-1)-h_k(x_1-1,y_2)+h_k(x_1-1,y_1-1)$$

因此现在的任务就是快速计算 $f,g$。

我们指出如下事实：

$$b_{x,y}=x\oplus y$$

其中 $\oplus$ 表示**异或**。

证明：
> 构造 $2$ 堆石子的 nim 游戏 $a_1,a_2$，设其 SG 值为 $c_{a_1,a_2}$。
> 
> 由 SG 函数的定义式，我们得到 $c_{a_1,a_2}=\operatorname{mex}(\{c_{a_1,k}|0\le k<a_2\}\cup\{c_{k,a_2}|0\le k<a_1\})$。
> 
> 于是使用数学归纳法容易证明，$b_{x,y}=c_{x,y}$。
> 
> 由 SG 定理，我们得到 $c_{a_1,a_2}=a_1\oplus a_2$。
> 
> 因此，$b_{x,y}=x\oplus y$。

于是

$$f_k(x,y)=\sum_{i<x}\sum_{j<y}[i\oplus j<k]$$

$$g_k(x,y)=\sum_{i<x}\sum_{j<y}[i\oplus j<k](i\oplus j)$$

这不就是[储能表](https://www.luogu.com.cn/problem/P4067)吗！

因此数位 dp 是能做的。当然，这并不优美。

考虑有没有更加优美的做法。

#### 异或卷积

我们发现和式内部仅和 $i\oplus j$ 有关，而枚举的却是 $i,j$。

因此考虑能否**对每个 $z=x\oplus y$，反推出有多少个合法的 $(x,y)$ 有序二元组满足此点**。

定义数列 $f,g$ 的**异或卷积**为数列

$$h_z=\sum_{x\oplus y=z}f_xg_y$$

不妨记为 $h=f\times_\oplus g$。

显然这个柿子的组合意义为枚举 $f,g$ 对应下标异或值为 $z$ 的方案数，其中 $f,g$ 分别表示其作为子式时变量异或和为某值的方案数。

考虑计算 $f_k(x,y),g_k(x,y)$ 的过程。

$$f_k(x,y)=\sum_{i<x}\sum_{j<y}[i\oplus j<k]=\sum_{z<k}\sum_{i<x}\sum_{j<y}[i\oplus j=z]$$

$$g_k(x,y)=\sum_{i<x}\sum_{j<y}[i\oplus j<k](i\oplus j)=\sum_{z<k}z\sum_{i<x}\sum_{j<y}[i\oplus j=z]$$

于是记

$$f_i=[i<x]$$

$$g_i=[i<y]$$

$$h=f\times_\oplus g$$

则

$$h_z=\sum_{i<x}\sum_{j<y}[i\oplus j=z]$$

因此

$$f_k(x,y)=\sum_{z<k}h_z$$

$$g_k(x,y)=\sum_{z<k}zh_z$$

#### 特殊形式的异或卷积

接下来的任务就是观察如何快速计算与记录这个异或卷积的结果了。

因为值域较大，所以异或卷积显然不能暴力使用基于快速沃尔什变换的集合对称差卷积实现，我们考虑观察性质。

不妨设在讨论范围内，一个数列非零值的下标总是小于 $2^m$。

我们发现，对于数列 $f,g$，其**前一半或后一半下标对应的值总是相等**，**另一半下标对应地递归满足相同性质**。

简单讨论容易验证，**异或卷积保持这个性质不变**，因此 $h=f\times_\oplus g$ 也满足这个性质。

**于是我们可以使用 $m+1$ 对数，来表示这样的一个数列（记录是前一半还是后一半为定值；记录具体是什么值）；对于这么一对数列的异或卷积，我们总可以在 $O(m)$ 的时间内实现，并返回一个仍保持此性质的数列。**

这个结论有一个经典的习题：[loj3073「2019 集训队互测 Day 2」序列](https://loj.ac/p/3073)。感兴趣可以去做一做。

因此，我们就可以优美地在 $O(\log v)$ 的时间内解决每一问了。

### Code

翻译没翻到位，原来是对 $10^9+7$ 取模的……

代码跑得很快。

下面是核心代码。

---
#### Update on 2022.11.5

打牛客发现异或卷积板子假了，回来修一修。

---


```cpp
const ullt Mod=1e9+7;
typedef ConstMod::mod_ullt<Mod>modint;
typedef std::vector<std::pair<bol,modint> >vec;
typedef std::vector<modint>modvec;
const uint M=32;ullt Len[M+1];
modvec User(vec a){
    modvec Ans(M+1);
    for(uint i=0;i<=M;i++)Ans[i]=a[i].second*Len[i];
    for(uint i=M;i;i--)Ans[i-1]+=Ans[i];
    return Ans;
}
vec mul(vec A,vec B){
    vec Ans(M+1);modvec UserA=User(A),UserB=User(B);
    for(uint i=0;i<M;i++)
    {
        Ans[i].first=A[i].first==B[i].first;
        Ans[i+1].second+=Ans[i].second+A[i].second*B[i].second*Len[i];
        Ans[i].second+=A[i].second*UserB[i+1]+B[i].second*UserA[i+1];
    }
    Ans[M].second+=A[M].second*B[M].second;
    return Ans;
}
vec get(ullt r){
    vec Ans(M+1);
    for(uint i=0;i<M;i++)if(r>=Len[i])Ans[i]={0,1},r-=Len[i];else Ans[i]={1,0};
    Ans[M].second=r;return Ans;
}
modint sum(ullt l,ullt r){return(l+r-1)*(r-l)/2;}
modint find(vec A,ullt k){
    modint ans;ullt from=0;
    for(uint i=0;i<M;i++)if(A[i].first)
    {
        if(k>Len[i])ans+=sum(from+Len[i]+1,from+k+1)*A[i].second,k=Len[i];
    }else{
        if(k<=Len[i]){
            ans+=sum(from+1,from+k+1)*A[i].second;
            return ans;
        }
        ans+=sum(from+1,from+Len[i]+1)*A[i].second;
        k-=Len[i];
        from+=Len[i];
    }
    if(k)ans+=(from+1)*A[M].second;
    return ans;
}
```


---

## 作者：tzc_wk (赞：4)

[Codeforces 题目传送门](https://codeforces.com/contest/809/problem/C) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF809C)

首先拿到这类题第一步肯定要分析题目给出的矩阵有什么性质。稍微打个表即可发现题目要求的矩形是一个**分形**。形式化地说，该矩形可以通过以下方式生成：$A_n$ 为一个 $2^n\times 2^n$ 的矩阵，$A_0=[1]$，$A_i=\begin{bmatrix}A_{i-1}&A'_{i-1}\\A'_{i-1}&A_{i-1}\end{bmatrix}$，其中 $A'_{i}$ 也是一个 $2^i\times 2^i$ 的矩阵，其第 $x$ 行 $y$ 列的元素为 $A_i$ 第 $x$ 行 $y$ 列的元素加上 $2^i$。

接下来就是我想不到的地方了，碰到这类生成方式与二进制联系异常紧密的矩阵，我们要尝试将其与位运算建立联系。这里就有一个性质，那就是该矩阵第 $x$ 行第 $y$ 列的数为 $(x-1)\oplus(y-1)+1$，证明可以大力归纳，应该不难，这里就不再赘述了。~~要说怎么发现的我也不知道，反正对于我这类没脑子选手肯定是想不到的咯。~~

于是此题可以转化为求 $\sum\limits_{i=l_1}^{r_1}\sum\limits_{j=l_2}^{r_2}(i-1)\oplus(j-1)+1[(i-1)\oplus(j-1)+1\le k]$。看到这类矩形求和的问题首先将其差分拆成四个形如 $\sum\limits_{i=0}^{x-1}\sum\limits_{j=0}^{y-1}i\oplus j+1[i\oplus j+1\le k]$ 的部分。于是现在问题转化为怎么求左边这坨东西。这里又有一个我想不到的套路，发现这东西长得挺像二维树状数组，因此我们可以将这个矩阵拆成 $\log^2n$ 个形如 $[x-\text{lowbit}(x),x),[y-\text{lowbit}(y),y)$ 的子矩阵，不妨假设 $\text{lowbit}(x)\ge \text{lowbit}(y)$，记 $t=(x-\text{lowbit}(x))\oplus (y-\text{lowbit}(y))$，那么显然 $[x-\text{lowbit}(x),x),[y-\text{lowbit}(y),y)$ 中任意两数异或起来的值刚好是 $[t,t+\text{lowbit}(x))$ 中每个数恰好出现 $\text{lowbit}(y)$ 次，因为 $\forall v\in[t,t+\text{lowbit}(x)),j\in [y-\text{lowbit}(y),y)$ 都有 $v\oplus j\in[x-\text{lowbit}(x),x)$，这个稍微想想就能想明白，因此对于所有形如 $[x-\text{lowbit}(x),x),[y-\text{lowbit}(y),y)$ 可以 $\mathcal O(1)$ 计算贡献。因此单次时间复杂度 $\log^2n$，总复杂度 $T\log^2n$。

可能有几个地方讲得不是太明白，具体看代码罢。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define y0 y101010101010
#define y1 y010101010101
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MOD=1e9+7;
const int INV2=5e8+4;
int sum(int l,int r){return 1ll*(l+r)*(r-l+1)%MOD*INV2%MOD;}
int calc(int l1,int r1,int l2,int r2,int k){
	if((r1-l1+1)<(r2-l2+1)) l1^=l2^=l1^=l2,r1^=r2^=r1^=r2;
	int tl=(l1^l2)&~(r1-l1),tr=min(tl+r1-l1,k-1);
	if(tl>k-1) return 0;return 1ll*(r2-l2+1)*sum(tl+1,tr+1)%MOD;
}
int solve(int x,int y,int k){
	int ans=0;
	for(int i=x;i;i&=(i-1)) for(int j=y;j;j&=(j-1))
		ans=(ans+calc(i&(i-1),i-1,j&(j-1),j-1,k))%MOD;
//	printf("%d %d %d %d\n",x,y,k,ans);
	return ans;
}
int main(){
	int qu;scanf("%d",&qu);
	while(qu--){
		int x1,y1,x2,y2,k;scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&k);
		printf("%d\n",((solve(x2,y2,k)-solve(x2,y1-1,k)-solve(x1-1,y2,k)+solve(x1-1,y1-1,k))%MOD+MOD)%MOD);
	}
	return 0;
}
/*
1
6 3 9 5 1
*/
```



---

## 作者：FlashHu (赞：3)

~~通过瞪眼法~~发现，$a_{i,j}=(i-1)\text{ xor }(j-1)+1$。

二维差分一下，我们只要能求$\sum\limits_{i=0}^x\sum\limits_{j=0}^yi\text{ xor }j\le k$就好了。

比较套路的数位DP。

从高位往低位做，设$f[t][0/1][0/1][0/1]$表示到第$t$位，$i,j,i\text{ xor }j$已确定的值是否卡到$x,y,k$前$t$位的上界的方案数和权值和。

每一位的转移都是一个小讨论：如果之前卡到上界，这一位可以接着卡，或者如果这一位的上界是$1$，就可以填$0$转移到不卡上界。如果之前不卡了，那么这一位随便选。

注意到最开始的式子里有一个$+1$，所以要输出$\sum$权值和+方案数。

下面的代码使用了压位和define可能会比较丑
```cpp
#include<bits/stdc++.h>
#define R register int
using namespace std;
const int YL=1e9+7;
int t,fc[8],fs[8],gc[8],gs[8];
inline int in(){R x;scanf("%d",&x);return x;}
inline void M(R&x){if(x>=YL)x-=YL;}
#define T(x,u,v) if(i>1||w==x)Trans(i>>1,li,u,v,i>1?w^x:w)
void Trans(R i,R li,R u,R v,R w){//暴搜转移
    if(!i){
        if(w)gs[v]=(gs[v]+fc[u]*(long long)t)%YL;
        return M(gc[v]+=fc[u]),M(gs[v]+=fs[u]);
    }
    if(i&li){T(0,u,v|i);T(1,u,v);}//讨论开始
    else T(0,u,v);
    T(0,u|i,v|i);
    T(1,u|i,v|i);
}
int Dp(R n,R m,R k){
    if(n<0||m<0)return 0;
    memset(fc,0,32);fc[0]=1;
    memset(fs,0,32);
    for(t=1<<30;t;t>>=1){
        Trans(4,!!(n&t)*4|!!(m&t)*2|!!(k&t),0,0,0);
        memcpy(fc,gc,32),memset(gc,0,32);
        memcpy(fs,gs,32),memset(gs,0,32);
    }
    R s=0;
    for(R i=0;i<8;++i)M(s+=fs[i]),M(s+=fc[i]);
    return s;
}
int main(){
    for(R q=in();q--;){
        R x1=in()-2,y1=in()-2,x2=in()-1,y2=in()-1,k=in()-1;
        cout<<((Dp(x2,y2,k)-Dp(x1,y2,k)-Dp(x2,y1,k)+Dp(x1,y1,k))%YL+YL)%YL<<endl;
    }
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

通过归纳证明可以得知，这个矩阵可以被看做一个 $1$ 加上若干次扩展。一次扩展是将目前 $2^i\times2^i$ 的矩阵复制 $4$ 遍成为 $2^{i+1}\times2^{i+1}$ 的矩阵，然后将左下右上的矩阵加 $2^i$。

不难发现减一后等价于 $i\oplus j$。

于是问题转化为求 $x_1\leq i\leq x_2,y_1\leq j\leq y_2,0\leq i\oplus j\leq k$ 的 $i\oplus j$ 之和。

容易设计数位 dp：$dp1_{k,tag_1,tag_2,tag_3}$ 和 $dp2_{k,tag_1,tag_2,tag_3}$ 表示后 $k$ 位，$tag_{1/2/3}$ 分别表示 $i,j,i\oplus j$ 是否顶满时，符合要求的 $i,j$ 数以及所有符合要求的 $i\oplus j$ 的后 $k$ 位和。

复杂度是 $O(T\log n)$，其中 $n$ 是 $\max(x_2,y_2,k)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int __int128
using namespace std;
int s1[35],s2[35],s3[35];
int dp1[35][2][2][2],dp2[35][2][2][2],vis[35][2][2][2];
pair<int,int> dfs(int pos,int lim1,int lim2,int lim3){
	if(pos==-1){
		return make_pair(1,0);
	}
	if(vis[pos][lim1][lim2][lim3]){
		return make_pair(dp1[pos][lim1][lim2][lim3],dp2[pos][lim1][lim2][lim3]);
	}
	vis[pos][lim1][lim2][lim3]=1;
	for(int i=0;i<=(lim1?s1[pos]:1);i++){
		for(int j=0;j<=(lim2?s2[pos]:1);j++){
			int k=i^j;
			if(k>(lim3?s3[pos]:1)) continue;
			auto p=dfs(pos-1,lim1&(i==s1[pos]),lim2&(j==s2[pos]),lim3&(k==s3[pos]));
			dp1[pos][lim1][lim2][lim3]+=p.first;
			dp2[pos][lim1][lim2][lim3]+=p.second+1ll*k*(1<<pos)*p.first;
		}
	}
	return make_pair(dp1[pos][lim1][lim2][lim3],dp2[pos][lim1][lim2][lim3]);
}
int qry(int x,int y,int z){
	for(int i=0;i<=30;i++) s1[i]=x&1,x>>=1;
	for(int i=0;i<=30;i++) s2[i]=y&1,y>>=1;
	for(int i=0;i<=30;i++) s3[i]=z&1,z>>=1;
	auto p=dfs(31,1,1,1);
	return p.first+p.second;
}
signed main(){
	long long q; cin>>q;
	while(q--){
		long long x1,x2,y1,y2,k;
		cin>>x1>>y1>>x2>>y2>>k;
		x1--,x2--,y1--,y2--,k--;
		memset(dp1,0,sizeof(dp1));
		memset(dp2,0,sizeof(dp2));
		memset(vis,0,sizeof(vis));
		int ans=qry(x2,y2,k);
		memset(dp1,0,sizeof(dp1));
		memset(dp2,0,sizeof(dp2));
		memset(vis,0,sizeof(vis));
		if(x1) ans-=qry(x1-1,y2,k);
		memset(dp1,0,sizeof(dp1));
		memset(dp2,0,sizeof(dp2));
		memset(vis,0,sizeof(vis));
		if(y1) ans-=qry(x2,y1-1,k);
		memset(dp1,0,sizeof(dp1));
		memset(dp2,0,sizeof(dp2));
		memset(vis,0,sizeof(vis));
		if(x1&&y1) ans+=qry(x1-1,y1-1,k);
		cout<<(long long)(ans%((int)(1e9+7)))<<"\n";
	}
	return 0;
}

```

---

## 作者：xuanxuan001 (赞：2)

子矩阵可以很容易地转换为二维前缀。那么看完这题，第一步肯定要打表。

可以随便打出前 8x8 的表：

```
1 2 3 4 5 6 7 8
2 1 4 3 6 5 8 7
3 4 1 2 7 8 5 6
4 3 2 1 8 7 6 5
5 6 7 8 1 2 3 4
6 5 8 7 2 1 4 3
7 8 5 6 3 4 1 2
8 7 6 5 4 3 2 1
```

然后发现对于一个 $2^n \times 2^n$ 的矩阵，那么把它平分成四部分，它们都是相似的，左上和右下相同，右上和左下也相同，但每个值都刚好比左上/右下的对应位置高 $2^{n-1}$。

感性理解一下好像确实是对的，然后继续观察可以发现这样一个矩阵有一个更神奇的性质：每行每列的数刚好都是一个 $1$ 到 $2^n$ 的排列。那么有了这个神奇的性质，我们就可以直接用公式求出一个子矩阵的一行或一列的不超过 $p$ 的数的和以及个数，通过乘法就可以得到几整行或几整列的。

然后就可以递归求解了。设 $f(n,m,p,x,l)$ 表示一个 $n \times m$ 的矩阵中所有不超过 $p$ 的数加上 $l$ 的和，并且保证 $n,m \le x$ 且 $x = 2^k(k \in \operatorname Z)$。注意是每个数分别加上 $l$ 再求和。

然后分讨转移即可，注意最多只能有一个向下递归的分支，这样才能保证复杂度为 $\log 10^9$，不妨设 $n \le m$。

那么大致思路就是分讨这个矩阵的位置：
1. 被左上角包含，那么直接转移即可。
2. 包含了左上角，那么递归求出右下角的部分的答案，而其他的都可以利用那个神奇的性质得出。
3. 其他情况就一定是包含了左上角的上面若干行和右上角的左上角，那么递归求出右上角部分并直接的出左上角的部分即可。

分讨比较复杂，但写之前把定义想清楚，认真推一下还是比较简单的。

代码：

```
#include<cstdio>
#define TY ll
#define MAXN 100002
#define debug if(1==1)
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
using namespace std;
typedef double db;
typedef long long ll;
const TY M=1e9+7;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
inline void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(b&1)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a){if(a>9)qw(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY T=qr(),x1,y1,x2,y2,p,ans;
TY js(TY x){return (x*(x+1)>>1)%M;}
TY findans(TY n,TY m,TY p,TY x,TY l){
	if(!n||!m)return 0;if(n>m)n^=m^=n^=m;updmn(p,x);
//	qw(n,' ');qw(m,' ');qw(p,' ');qw(x,'\n');
	if(x==1)return l+1;x>>=1;
	if(p<=x){//如果 p<=x，那么只有左上角和右下角有用
		if(m<x)return findans(n,m,p,x,l);//大概就是按文字题解顺序分讨的
		if(n<=x&&m>=x)return (n*js(p)+p*n%M*l)%M;
		return (x*p%M*l+x*js(p)+findans(n-x,m-x,p,x,l))%M;
	}TY ans;if(m<x)return findans(n,m,x,x,l);
	if(n<=x&&m>=x){
		ans=n*js(x)%M;add(ans,l*x%M*n%M);
		add(ans,findans(n,m-x,p-x,x,l|x));return ans;
	}ans=x*js(x)%M;add(ans,x*x%M*l%M);n-=x;m-=x;
	p-=x;add(ans,findans(n,m,x,x,l));
	add(ans,(n+m)*(l|x)%M*p%M);
	add(ans,js(p)*(n+m)%M);return ans;
}int main(){
	while(T--){
		x1=qr()-1;y1=qr()-1;x2=qr();y2=qr();p=qr();
		ans=findans(x2,y1,p,1073741824,0);
		add(ans,findans(x1,y2,p,1073741824,0));ans=M-ans;
		add(ans,findans(x2,y2,p,1073741824,0));
		add(ans,findans(x1,y1,p,1073741824,0));qw(ans,'\n');
	}return 0;
}
```

---

## 作者：Albedo (赞：2)

# $\texttt{Solution}$

首先我们可以先打一个 $20\times 20$ 的表（方便看出巨大的数字差）。

然后发现这样子的一个事实：
$$
a(x+2^k,y+2^k)=a(x,y)\\
a(x+2^k,y)=a(x,y)+2^k\\
a(x,y+2^k)=a(x,y)+2^k\\
$$

那么我们就可以得到：$a(x,y)=(x-1)\oplus(y-1)+1$

那么我们事实上就是要求：
$$
\sum_{i=x_1}^{x2}\sum_{j=y_1}^{y_2} (i-1)\oplus (j-1)+1 ((i-1)\oplus (j-1)+1\le k)
$$

一个差分之后，就是一个比较套路的数位 $\texttt{DP}$ 了。

我们考虑设 $f(x,0\sim2,0\sim 2,0\sim 2)$ 表示做到第 $i$ 位，相对于 $n,m,k$ 当前的状态（小于限制，等于限制，超过限制）时的答案。

发现这样子不好转移，那么再设一个辅助数组，记录这种状态下有多少中方案，然后套路转移就好了。

时间复杂度： $\mathcal O(T\times \log n)$

# $\texttt{Code}$

``` cpp
long long Va(long long x,long long y){if (x==y) return 1;if (x<y) return 0;return 2; } 
long long Vb(long long x,long long y,long long z){
	if ((x<y)) return 0;if (x>y) return 2;return z;
}
long long calc(long long n,long long m){
	if ((n<0)||(m<0)) return 0;
	for (i=0;i<=30;i++) for (A=0;A<=2;A++) for (B=0;B<=2;B++) for (C=0;C<=2;C++) f[i][A][B][C]=e[i][A][B][C]=0;
    for (A=0;A<=1;A++)
       for (B=0;B<=1;B++)
           f[0][Va(A,n&1)][Va(B,m&1)][Va(A^B,K&1)]+=A^B,e[0][Va(A,n&1)][Va(B,m&1)][Va(A^B,K&1)]++;
	for (i=1;i<=30;i++)
        for (lst1=0;lst1<=2;lst1++)
           for (lst2=0;lst2<=2;lst2++)
             for (lst3=0;lst3<=2;lst3++)
                for (now1=0;now1<=1;now1++)
                   for (now2=0;now2<=1;now2++){
                   	   tagA=((n&(1ll<<i))>0);tagB=((m&(1ll<<i))>0);tagC=((K&(1ll<<i))>0);
                   	   valA=Vb(now1,tagA,lst1);valB=Vb(now2,tagB,lst2);valC=Vb(now1^now2,tagC,lst3);
                   	   f[i][valA][valB][valC]+=((now1^now2)*(1ll<<i)*e[i-1][lst1][lst2][lst3])+f[i-1][lst1][lst2][lst3];
                   	   f[i][valA][valB][valC]%=MOD;
                   	   e[i][valA][valB][valC]+=e[i-1][lst1][lst2][lst3];
                   	   e[i][valA][valB][valC]%=MOD;
				   }
	long long tot=0;
	for (lst1=0;lst1<=1;lst1++)
	   for (lst2=0;lst2<=1;lst2++)
	      for (lst3=0;lst3<=1;lst3++)
	        tot=(tot+f[30][lst1][lst2][lst3]+e[30][lst1][lst2][lst3]) % MOD;
	return tot;
}
void Main(){
	Xa=read();Ya=read();Xb=read();Yb=read();K=read();
	Xa--;Ya--;Xb--;Yb--;K--;
	tot=calc(Xb,Yb)-calc(Xa-1,Yb)-calc(Xb,Ya-1)+calc(Xa-1,Ya-1);
	tot=(tot % MOD+MOD) % MOD;
	printf("%lld\n",tot);     
	return ;
}
```



---

## 作者：chenxia25 (赞：2)

终于把这题 A 掉了，感动中国（

做这题也是一波三折啊……几天前想的时候想假掉了，交上去 T 了，然后咕了好几天一直咕到现在。然后这数位 DP 又不是一般的难写，写的过程中心态崩过几次。然后又不是一般的难调，调出来之后交上去又 WA 了……然后发现是爆 `ll` 了，改成 `__int128_t` 上去，又 CE 了……只好手动把爆炸的地方改过来才 AC。

---

**[Portal]( https://www.luogu.com.cn/problem/CF809C )**

首先打个表发现这是一个分形，形式化的表述就是 $a=\begin{bmatrix}a&a+n_a\\a+n_a&a\end{bmatrix}$。然后我就直接递归了，写得像二维线段树一样，以为是二次对数的。但其实这个是假的，因为二维线段树是横着竖着各分为若干个整区间，横竖独立，而这个除此之外还要满足横竖相等（即是个正方形）。

然后就自爆了，就看题解了。发现一个结论：$a_{i,j}=(i-1)\oplus(j-1)+1$。那么到底怎么才能发现这个结论我也是不知道的，因为我要智商没智商，要眼力没眼力。

我们考虑将所求问题二位前缀和一下，那么问题归约到求 $\sum\limits_{i=0}^x\sum\limits_{j=0}^y[i\oplus j<k]((i\oplus j)+1)$。这也是个比较难的问题。考虑类似数位 DP（二进制）地统计答案：将 $x,y$ 分别拆成位数比原数低的、和原数的一个前缀后面随便加的一些，这样每部分都是一个固定的前缀后面有若干位随便放的这个形式，并且数量是对数级别的。现在我们只要求，两个这样形式的数的上面那个 $\sum$ 的值是多少，并且还要是常数时间，这样总时间复杂度是二次对数。

这个就分类小讨论一下即可。注意到局面是下面这个样子的：

```
.----.----------.
| h1 |    z1    |
.----.-----.----.
|    h2    | h2 |
.----------.----.
|        k      |
.---------------.
```

那么显然可以分为三段。第一段上下的异或和是固定的，那么就讨论一下与 $k$ 的这段的大小。如果大那就为 $0$，如果小那就后面随便取（这个很容易算出式子，等差数列也可以搞定），如果相等就继续往下。然后看第二段，这个第一个数的部分是自己取的，第二个数的部分是固定的。于是分小于和等于 $k$ 这部分两种加起来。小于的话后面随便取，容易列式；等于的话，后面要小于，也容易。

代码异常难写，细节多的一批。我第一遍写完后只有一个错误也是蛮了不起的。

**_[code]( https://www.luogu.com.cn/paste/0y3ef2ss )_**

---

## 作者：xyin (赞：1)

看到题目中的矩形是 $10^9\times 10^9$，在实际做的时候我们肯定得找到某种规律，使得我们可以能快速的求出某一格的值，这里我打出了 $8\times 8$ 的表，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/gnulx081.png)

我们像上面一样把它们分成 $4$ 个子矩形，观察可以发现，最开始$\color{blue}\texttt{左上角}$的 $4\times 4$ 的矩形每一行每一列都包含了 $1,2,3,4$ 四个元素。而$\color{red}\texttt{右下角}$的矩形和$\color{blue}\texttt{左上角}$一模一样。进一步观察得$\color{seagreen}\texttt{右上角}$和$\color{orange}\texttt{左下角}$的一样，且等于$\color{blue}\texttt{左上角}$的值 $+4$。

结论：对于$\color{blue}\texttt{左上角}$的 $2^{n-1}\times 2^{n-1}$ 的矩形，每一行每一列都包含了 $1,2,3,\dots ,2^{n-1}$，$\color{red}\texttt{右下角}$的矩形和$\color{blue}\text{左上角}$一模一样，$\color{seagreen}\texttt{右上角}$和$\color{orange}\texttt{左下角}$的一样，且等于$\color{blue}\texttt{左上角}$的值 $+2^{n-1}$。

感性理解一下，对于左下角和右下角的矩形，不能包含 $1,2,3,\dots ,2^{n-1}$ 中的数，相当于在最小正整数的基础上还要加上一个 $2^{n-1}$,它的变化趋势其实就是和左上角是相同的。对于右下角的数，能影响它的只有左下角和右上角，但由于左下角和右上角都 $>2^{n-1}$，所以它其实就和左上角一样。总的来说，四个子矩形的变化趋势都相同。

怎么判断 $(x,y)$ 位于哪个子矩形？我们发现对于 $x\le 4,y\le 4$（位于左上角）和 $4<x\le 8,4<y\le 8$（位于右下角）的这些点对 $(x,y)$ 有一个共同点，即 $x,y$ 的最高位都相同（最高位在这里指二进制下的第 $4$ 位）。那么 $x,y$ 的最高位不同的时候，就位于右上角和左下角了吗？不是的，例如 $(4,5),(4,6)$ 这个时候我们可以把 $x,y$ 同时减去 $1$ 再判断最高位是否相同。但我们发现对于上面的第一种情况，$x,y$ 同时减 $1$ 后的最高位也相同，那我们就可以直接简化成判断 $x-1$ 与 $y-1$ 的最高位是否相同。

如果相同（位于左下角或右上角），则加上 $2^{n-1}$（$n$ 为最大数的二进制位数）；否则（位于左上角或右下角），则不考虑最高位。这样就相当于进行异或操作，得到的值与实际值差 $1$，我们最后还要再加上 $1$。

综上，结论为：$a_{i,j}=(i-1)\oplus (j-1)+1$。

在实现时，可以先将行和列以及每个格子的权值 $-1$，则合法的 $a_{i,j}=i\oplus j\le k-1$

然后就可以直接套数位 DP 了，设 $f_{i,0/1,0/1,0/1}$ 表示考虑到了二进制的第 $i$ 位，其中 $x$ 的第 $i$ 是否卡到上界，$y$ 的第 $i$ 位是否卡到上界，$i\oplus j$ 是否卡到上界。

注意我们最后的答案应该是：合法的权值加上合法的数量。求解一个矩形的答案，转化为二维前缀和就行，别忘了取模。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pai pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define _4781 0
using namespace std;
const int N=32;
const int mod=1e9+7;
int read(int x=0,bool f=1,char c=0){
    while (!isdigit(c=getchar())) f=c^45;
    while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?x:-x;
}
int q,a,b,c,d,k,ans;
bool vis[N][2][2][2];//记搜
int up1[N],up2[N],up3[N];
//分别为 x,y,k 二进制下每一位的上界
int dp1[N][2][2][2],dp2[N][2][2][2];
// dp1 为合法的数量，dp2 为合法的权值
pai dfs(int pos,int l1,int l2,int l3){
    if (pos<0) return mk(1,0);
    if (vis[pos][l1][l2][l3])
        return mk(dp1[pos][l1][l2][l3],dp2[pos][l1][l2][l3]);
    vis[pos][l1][l2][l3]=1;
    for (int i=0;i<=(l1?up1[pos]:1);i++)
        for (int j=0,sum;j<=(l2?up2[pos]:1);j++){
            if ((i^j)>(l3?up3[pos]:1)) continue;
            else sum=i^j;
            pai p=dfs(pos-1,l1&(i==up1[pos]),l2&(j==up2[pos]),l3&(sum==up3[pos]));
            dp1[pos][l1][l2][l3]+=p.first;
            dp2[pos][l1][l2][l3]+=p.se+sum*(1ll<<pos)*p.fi;
        }
    dp1[pos][l1][l2][l3]%=mod;dp2[pos][l1][l2][l3]%=mod;
    return mk(dp1[pos][l1][l2][l3],dp2[pos][l1][l2][l3]);
}
int query(int x,int y,int k){
    memset(dp1,0,sizeof(dp1));
    memset(dp2,0,sizeof(dp2));
    memset(vis,0,sizeof(vis));
    for (int i=0;i<=30;i++){
        up1[i]=(x>>i)&1;
        up2[i]=(y>>i)&1;
        up3[i]=(k>>i)&1;
    }
    pai p=dfs(30,1,1,1);
    return (p.first+p.second)%mod;
}
signed main(){
    for (int q=read();q;q--){
        a=read()-1,b=read()-1;
        c=read()-1,d=read()-1;
        k=read()-1;ans=0;
        ans+=query(c,d,k);
        if (a) ans=(ans-query(a-1,d,k)+mod)%mod;
        if (b) ans=(ans-query(c,b-1,k)+mod)%mod;
        if (a&&b) ans=(ans+query(a-1,b-1,k))%mod;
        printf("%lld\n",ans);
    }
    return _4781;
}
```

---

## 作者：Wei_Han (赞：0)

场上会了单点求值的办法，没想到前缀求和，无敌了。

一种不用注意力的方法，通过打出 $30 \times 30$ 的表来可以发现这是个分形的东西，一大个大矩形的长度为 $2^k$，那么他就可以被分为边长为 $2^k$，$2^{k-1}$，$2^{k}$，$2^{k-1}$ 的四个小矩形，而且可以观察得出大矩形的每一行都是一个 $2^k$ 的排列，你甚至还可以得出他的分形规律，但对正解没什么用。

每次询问一个矩形的答案，自然可以差分变成询问四个左上角在 $(1,1)$ 的小矩形的答案，现在就要考虑怎么求一个覆盖左上角的矩形的答案。

由于这个东西的特性，我们先将他向外补到 $2^k$，然后讨论他右下角点的位置：

![](https://cdn.luogu.com.cn/upload/image_hosting/2wiy7gfu.png)

像这样，假设他在右下角，那么蓝色部分就是一个完整的边长为 $2^{k-1}$ 的矩形，通过之前观察发现他的每一行都是 $[1,2^{k-1}]$ 的排列，所以可以直接求和，对于红色部分的两块多余部分，我们发现看他们的长边，都是 $[2^{k-1}+1,2^k]$ 的排列，他们也可以直接算出来，然后还剩下最后的绿色部分，由于我们前面补出的是一个正方形，所以绿色部分肯定在主对角线上，所以他左上角的值是 $1$，这样就可以继续向下递归求解这个小矩形的答案。

类似的，假设这个点在左下角或者右上角，那么他就只剩向左/上的红色部分，这个跟上面一致是可以算出来的，然后在递归小矩形的答案，但是由于他不在主对角线上，所以他的值会有一定偏移量，其实就是 $2^{k-1}$，递归时也要加上。

假设这个点在左上角，就是当前区间取大了，还可以取到更小的正好包含这个点的区间，所以令 $k$ 缩小即可。

代码很好写，注意取模。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define fo(a,i,b) for(ll i=a;i<=b;++i)
#define Fo(a,i,b) for(ll i=a;i>=b;--i)
#define pr printf("\n")
#define pp printf(" ")
#define pb push_back
#define fi first
#define se second
#define pii pair<ll,ll>
//typedef long long ll;
typedef __int128 ll;
using namespace std;
const ll N=1e5+5;
inline void read(ll &opp){ll t=1,s=0;char ch=getchar();while(!((ch>='0'&&ch<='9')||ch=='-')) ch=getchar();if(ch=='-') t=-1,ch=getchar();while(ch>='0'&&ch<='9') s=s*10+(ch-'0'),ch=getchar();opp=s*t;}
inline void wr(ll x){if(x<0) putchar('-'),x=-x;if(x>=10) wr(x/10),putchar((x%10+'0'));else putchar((x+'0'));}
const ll mod=1e9+7;
inline ll qpow(ll a,ll b){return (!b?1ll:qpow(a%mod*a%mod,b>>1ll)*((b&1ll)?a%mod:1ll)%mod);}
inline ll get(ll l,ll r,ll k,ll z){if(l>k) return 0;r=min(r,k);if(r<l) return 0;return ((l+r)%mod*(r-l+1)%mod*(ll)500000004%mod*z%mod)%mod;}
inline ll solve(ll x,ll y,ll len,ll k,ll opt){
	if(x==len&&y==len) return get(1+opt,len+opt,k,len)%mod;
	ll siz=len>>1;
	if(x<=siz&&y<=siz) return solve(x,y,len>>1,k,opt);
	if(x>siz&&y>siz) return (get(1+opt,siz+opt,k,siz)+get(siz+1+opt,len+opt,k,y-siz)+get(siz+1+opt,len+opt,k,x-siz)+solve(x-siz,y-siz,siz,k,opt))%mod;
	if(x<=siz&&y>siz) return (get(1+opt,siz+opt,k,x)+solve(x,y-siz,siz,k,opt+siz))%mod;
	if(x>siz&&y<=siz) return (get(1+opt,siz+opt,k,y)+solve(x-siz,y,siz,k,opt+siz))%mod; 
}
inline ll check(ll x1,ll y1,ll k){
	if(!x1||!y1) return 0;
	ll now=0;while((1ll<<(now))<max(x1,y1)) now++;
	return solve(x1,y1,1ll<<now,k,0)%mod;
}
int main(){
	ll q;read(q);
	fo(1,i,q){
		ll x1,y1,x2,y2,k;
		read(x1),read(y1),read(x2),read(y2),read(k);
		wr((check(x2,y2,k)-check(x2,y1-1,k)+mod-check(x1-1,y2,k)+mod+check(x1-1,y1-1,k)+mod)%mod),pr;
	}
	return 0;
}
``````

---

