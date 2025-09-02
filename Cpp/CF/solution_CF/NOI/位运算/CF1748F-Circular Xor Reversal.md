# Circular Xor Reversal

## 题目描述

给定整数 $n$。  
初始，有一个编号从 $0$ 开始的长度为 $n$ 的环形序列 $a$，满足 $a_i=2^i$ 对任意整数 $i(0\leq i<n)$ 成立。  
你的任务是将 $a$ 翻转，即使序列 $a$ 满足 $a_i=2^{n-i-1}$ 对任意整数 $i(0\leq i<n)$ 成立。  
为此，你可以进行下列操作至多 $2.5\times10^5$ 次：

- 选定整数 $i$，将 $a_i$ 的值改为 $a_i\text{ xor }a_{(i+1)\bmod n}$。  
其中 $\text{xor}$ 表示按位异或运算。

可以证明在题目限制下，本题一定有解。你需要找出任意一组满足要求的解。

## 样例 #1

### 输入

```
2```

### 输出

```
3
1 0 1```

## 样例 #2

### 输入

```
3```

### 输出

```
9
1 0 1 0 2 1 0 1 0```

# 题解

## 作者：BqtMtsZDnlpsT (赞：5)


翻转的本质，是 $\left\lfloor\frac n2\right\rfloor$ 次交换。

异或实现交换，不禁让人：`x^=y^=x^=y`。

令 $\text{nxt}_i=(i+1)\bmod n,\text{pre}_i=(i-1+n)\bmod n$。

令操作 $i$ 表示在 $i$ 这一位置进行一次操作。

于是我们尝试构造一个操作 $\operatorname{opr}(i,j)$ 表示：$a_i\leftarrow a_i\oplus a_j$（不改变其余位置的值）。


不难把序列看成一个有向环（$i$ 向 $\text{nxt}_i$ 连边）。


![zkPNeH.png](https://s1.ax1x.com/2022/11/13/zkPNeH.png)

令 $l$ 为 $i\to j$ 的距离。

$s_i(1\le i\le k=l-1)$ 为 $i$ 出发，距离为 $i$ 的点的编号。

设

- 先按环上 $i\to \text{pre}_j$ 的路径逆序各进行一次操作。

	如上图，依次进行操作 $s_k$，操作 $s_{k-1}$，$\dots$，操作 $s_1$，操作 $i$。
    
    令 $a'$ 表示操作后的数组，那么：
    
    $a'_{s_k}=a_{s_k}\oplus a_j$；
    
    $a'_{s_{k-1}}=a_{s_{k-1}}\oplus a_{s_k}\oplus a_j$；
     
     $\dots$
     
     $a'_{s_1}=a_j\oplus\left(\bigoplus_{i=1}^{k}a_i\right)$；
     
     $a'_i=a_i\oplus a_j\oplus\left(\bigoplus_{i=1}^{k}a_{s_i}\right)$。
     
- 按环上 $\text{nxt}_i\to \text{pre}_j$ 的路径顺序各进行一次操作。

	此时可以发现 $a_{s_1},\dots,a_{s_k}$ 的值已经复原。
    
- 先按环上 $i\to \text{pre}_{\text{pre}_j}$ 的路径逆序各进行一次操作。

	令 $a'$ 为操作后的数组，$a$ 为操作前的数组。
    
    $a'_{s_i}=\bigoplus_{j=i}^{k}a_{s_j}$；
    
    $a'_1=a_1\oplus\left(\bigoplus_{i=1}^{k}a_{s_i}\right)$。
    
    可以发现，此时 $a'_1$ 已经等于 $a_i\oplus a_j$。
    
- 按环上 $\text{nxt}_i\to \text{pre}_{\text{pre}_j}$ 的路径顺序各进行一次操作。

	复原 $a_{s_1},\dots,a_{s_k}$。
    
    
至此，我们通过 $4l-4$ 次操作实现 $a_i\leftarrow a_i\oplus a_j$。

交换两个数 $i,j$ 所需次数为 $4n-8+4\min(l,n-l)-4$。因为 $3$ 次操作分别为 $a_i\leftarrow a_i\oplus a_j,a_j\leftarrow a_i\oplus a_j,a_i\leftarrow a_i\oplus a_j$，前两项次数之和位 $4n-8$；后面一项，因为交换 $i,j$ 相当于交换 $j,i$，所以可以取 $\min$。

总次数为 ：

$$\begin{cases}
2.5n^2-6n+4 & n\equiv0\pmod4\\
2.5n^2-6n+6 & n\equiv2\pmod4\\
2.5n^2-8n+7.5 & n\equiv1\pmod2\\
\end{cases}$$

$n=400$ 时，操作次数为 $397604$，不行。

考虑优化。

我们根据 $\min$ 分成两个半圈。

![zk7ZnK.png](https://s1.ax1x.com/2022/11/14/zk7ZnK.png)

假设我们现在已经进行了 $\operatorname{opr}(x,y)$ 的前三步，可以发现，此时恰好完成了 $\operatorname{opr}(\text{nxt}_x,\text{pre}_y)$ 的第一步。

所以我们可以一起进行：$\operatorname{opr}(x,y),\operatorname{opr}(\text{nxt}_x,\text{pre}_y),\dots,\operatorname{opr}(0,n-1)$。

同理我们可以一起进行：$\operatorname{opr}(y,x),\operatorname{opr}(\text{pre}_y,\text{nxt}_x),\dots,\operatorname{opr}(n-1,0)$。

总次数为 ：

$$\begin{cases}
1.25n^2+2n-8 & n\equiv0\pmod4\\
1.25n^2+2n-7 & n\equiv2\pmod4\\
1.25n^2+n+6.25 & n\equiv1\pmod2\\
\end{cases}$$


$n=400$ 时，操作次数为 $200792$，行！

似乎吊打 std 了，std 的 $400$ 似乎是 $239997$（看提交记录里的 Answer，std 没拉下来测）。

由于切成两半，$n<4$ 时要特判，代码里用了上面那个暴力，也帮助大家理解（？）。

代码：

```cpp
//...............
#define For(i_,l_,r_) for(int i_=(l_);i_<=(r_);i_++)
#define Rep(i_,l_,r_) for(int i_=(l_);i_>=(r_);i_--)
int n,s[405],L,x,y;
int ans[400005],S;
inline int U(Ci x){return Add(x+1,n);}
inline int D(Ci x){return Add(x+n-1,n);}
inline void Work(Ci u){ans[++S]=u;}
inline void Opr(Ci u,Ci v){
	int x=u;L=0;
	while(x!=v)x=U(x),s[++L]=x;
	s[0]=u;
	Rep(i,L-1,0)Work(s[i]);
	For(i,1,L-1)Work(s[i]);
	Rep(i,L-2,0)Work(s[i]);
	For(i,1,L-2)Work(s[i]);
}
inline void Swap(Ci u,Ci v){
	Opr(u,v);
	Opr(v,u);
	Opr(u,v);
}
inline void Solvel0(){
	L=0;
	For(i,x,n-1)s[L++]=i;
	For(i,0,y)s[L++]=i;
	--L;
	Rep(i,L-1,0)Work(s[i]);
	For(i,0,L/2){
		For(j,i+1,L-i-1)Work(s[j]);
		Rep(j,L-i-2,i)Work(s[j]);
	}
}
inline void Solvel1(){
	L=0;
	For(i,0,n-1)s[L++]=i;
	--L;
	Rep(i,L-1,0)Work(s[i]);
	For(i,0,y){
		For(j,i+1,L-i-1)Work(s[j]);
		Rep(j,L-i-2,i)Work(s[j]);
		if(i==y)For(j,i+1,L-i-2)Work(s[j]);
	}
}
int tmp;
inline void Solver0(){
	L=0;
	For(i,y,x)s[L++]=i;
	--L;
	Rep(i,L-1,0)Work(s[i]);
	For(i,0,L/2){
		For(j,i+1,L-i-1)Work(s[j]);
		Rep(j,L-i-2,i)Work(s[j]);
		if(i==L/2)tmp=s[i];
	}
}
inline void Solver1(){
	L=0;
	For(i,tmp+1,n-1)s[L++]=i;
	For(i,0,tmp-(n&1))s[L++]=i;
	--L;
	Rep(i,L-1,0)Work(s[i]);
	For(I,tmp+1,x){
		int i=I-tmp-1;
		For(j,i+1,L-i-1)Work(s[j]);
		Rep(j,L-i-2,i)Work(s[j]);
		if(I==x)For(j,i+1,L-i-2)Work(s[j]);
	}
}
inline void ypa(){
	n=read();x=n-1;
	if(n<=3){
		For(i,0,(n>>1)-1)
			if(n-1-i-i<=i+i+1)Swap(i,n-i-1);
			else Swap(n-i-1,i);
		write(S,'\n');
		writel(ans+1,ans+1+S);
		return;
	}
	For(i,0,(n>>1)-1)
		if(n-1-i-i<=i+i+1){x=n-i-1,y=i;break;}
	x++,y--;
	Solvel0();Solvel1();Solvel0();
	x--,y++;
	Solver0();Solver1();Solver0();
	write(S,'\n');
	writel(ans+1,ans+1+S);//输出数组
}
signed main(){init();for(int T=1;T;T--)ypa();flush();return system("pause"),0;}
```

---

## 作者：devans (赞：4)

$3000$ 的高级构造题。

我们一步一步地解这道题。  
为方便，下面自动认为所有下标相关的元素均在模 $n$ 意义下计算。  
同时注意本题有关下标的计算细节不少，一定想清楚。  
下面用符号 $\oplus$ 表示异或。  
设 $\text{Dist}(i,j)=(j-i+n)\bmod n$，即对 $a_{i},a_{i+1},\cdots,a_{j-1}$ 操作所需的操作次数。

---

1. 我们有操作 $a_i\leftarrow a_i\oplus a_{i+1}$，如何扩展出操作 $a_i\leftarrow a_i\oplus a_j(0\leq i,j<n;i\not=j)$ ？  

操作本身足够简单，因此手玩一下就会有一些方案。

- 考虑下列步骤：  
	- 将 $a_i$ 先变成 $\bigoplus_{k=i}^{j-1}a_k$，所需操作次数为 $\text{Dist}(i,j)-1$。
	- 将 $a_{i+1}\sim a_{j-2}$ 复原，所需操作次数为 $\text{Dist}(i,j)-2$。
	- 将 $a_{i+1}$ 变成 $\bigoplus_{k=i+1}^{j}a_k$，所需操作次数为 $\text{Dist}(i,j)-1$。
	- 对 $a_i$ 操作，所需操作次数为 $1$。
	- 将 $a_{i+1}\sim a_{j-1}$ 复原，所需操作次数为 $\text{Dist}(i,j)-1$。
	- 此时我们达成了将 $a_i\leftarrow a_i\oplus a_j$，并使用了 $4\times\text{Dist}(i,j)-4$ 次操作。

2. 上述操作的问题在于对中间 $a_{i+1}\sim a_{j-1}$ 的操作似乎存在大量冗余。   
于是考虑把若干个上述扩展过的操作压缩在一起。  
如果我们希望对任意非负整数 $k(i+k<j-k)$，使 $a_{i+k}\leftarrow a_{i+k}\oplus a_{j-k}$，有没有什么更优秀的方法？

我们最终要得到的东西大概长这样：
```plain
0 1 2 3 4 5 6 7 8 | (position)-i

1 0 0 0 0 0 0 0 1
0 1 0 0 0 0 0 1 0
0 0 1 0 0 0 1 0 0
0 0 0 1 0 1 0 0 0
0 0 0 0 1 0 0 0 0
0 0 0 1 0 0 0 0 0
0 0 1 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0
```
这个东西长得非常特别。  
倒着思考，考虑我们得到这么一个东西前一些操作大概长什么样，于是有下面的猜测：
```plain
0 1 2 3 4 5 6 7 8 | (position)-i

1 0 0 0 0 0 0 0 1
1 1 0 0 0 0 0 1 0
1 1 1 0 0 0 1 0 0
1 1 1 1 0 1 0 0 0
1 1 1 1 1 0 0 0 0
1 1 1 1 0 0 0 0 0
1 1 1 0 0 0 0 0 0
1 1 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0
```
这个东西经过按照 $k=0,1\cdots$ 的顺序对 $a_{i+k}$ 进行操作即可得到更上面的那个矩阵。  
然后我们发现此时我们有简单的构造出前面这些数的方法，因此我们有了一种方案。

- 考虑下列步骤：  
	- 对每个非负整数 $k(i+k<j-k)$，用 $2\times(\text{Dist}(i,j)-k)-1$ 次操作执行以下步骤：  
    	- 将 $a_{i+k}$ 变成 $\bigoplus_{l=i}^{j-k}a_l$。
        - 复原 $a_{i+k+1}\sim a_{j-k-1}$。
    - 对每个非负整数 $k(i+k<j-k)$，用 $1$ 次操作执行以下步骤：
    	- 对 $a_{i+k}$ 操作。
- 通过计算，这总计需要约 $\dfrac{\text{Dist}(i,j)\times(\text{Dist}(i,j)+2)}{2}$ 次操作。

3. 各位应该都熟悉一种“自作多情”的用 $\color{red}3$ 次异或维护 `swap` 函数的方法，不过可以在这题中尝试用一下。  
4. 根据操作上限，我们一定可以进行步骤 2 中的操作至少 $\color{red}3$ 次。  

我们知道在一些情况下有 `swap(a,b)` 和 `a^=b,b^=a,a^=b` 等价，这给我们的最终的思考提供了思路。  
定义函数 $F(i,j)$ 表示选择 $i,j$ 并进行步骤 2 中的操作。  
我们的大体思路是：
```plain
original:
a[0] a[1] a[2] ... a[n-3] a[n-2] a[n-1]
step 1:
a[0]^a[n-1] a[1]^a[n-2] a[2]^a[n-3] ... a[n-3] a[n-2] a[n-1]
step 2:
a[0]^a[n-1] a[1]^a[n-2] a[2]^a[n-3] ... a[2] a[1] a[0]
step 3:
a[n-1] a[n-2] a[n-3] ... a[2] a[1] a[0]
```
于是分奇偶性讨论，考虑下列步骤：

- 如果 $n$ 是偶数，依次进行 $F(0,n-1),F\bigg(\dfrac{n}{2},\dfrac{n}{2}-1\bigg),F(0,n-1)$。
- 如果 $n$ 是奇数，依次进行 $F(0,n-1),F\bigg(\dfrac{n+1}{2},\dfrac{n-3}{2}\bigg),F(0,n-1)$。

至此，我们用约 $1.5\times n^2$ 次的操作次数解决了这个问题。  
下面的程序采用该方法，在 $n=400$ 时达到最大操作次数 $239997$ 次，可以通过。

```plain
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename T> void read(T &x) {
	x=0;int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	x=x*f;
}
const int N=250020;
int n,op[N],p[N],cnt=0,s1,s2,s3,s4;
void upd(int x){
	cnt++,op[cnt]=x%n;
}
void solve(int l,int r){
	s1=(r-l+n)%n;
	for(int i=0;i<=(s1+1)/2-1;i++){
		for(int j=(r-1-i+n)%n;j!=l+i;j=(j-1+n)%n) upd(j);
		for(int j=l+i;j!=r-i;j=(j+1)%n) upd(j);
	}
	for(int i=0;i<=s1/2-1;i++) upd(l+i);
}

signed main(){
	read(n);
	solve(0,n-1);
	if(n%2==0) solve(n/2,n/2-1);
	else solve(n/2+1,n/2-1);
	solve(0,n-1);
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++) cout<<op[i]<<' ';
	return 0;
}
```

---

小 upd。  
在题解的讨论区找到了更优的操作次数约为 $1.25\times n^2$ 的做法，  
有兴趣的就去看一看 [这位大佬](https://www.luogu.com.cn/blog/TOBapNw-cjn/solution-cf1748f) 的题解，毕竟人家先给出来。  
不过我还是在这里简述一下。

5. 我们对步骤 2 的利用似乎还是不好，表现在我们千里迢迢把 $a_{n-1}$ 一个一个移动到了 $a_0$。  
还总是移动了两次，而显然我们有将 $a_0$ 一步变到 $a_{n-1}$ 的操作。  

考虑将序列划分为两段 $[i;j],[j+1;i-1]$ 分别翻转（分三段或以上一定不优，因为翻转一个序列至少要 $\dfrac{n^2}{2}$ 级别的操作）。  
我们发现虽然直接做还是 $1.5\times n^2$ 次，但有 $0.25\times n^2$ 次操作可以覆盖，这样就优化到 $1.25\times n^2$ 次了。  
下面是图解，没看懂的可以对着理解一下。  
```plain
original:
0 1|2 3 4 5|6 7 - position 

0 0 0 0 0 0 0 1
0 0 0 0 0 0 1 0
0 0 0 0 0 1 0 0
0 0 0 0 1 0 0 0
0 0 0 1 0 0 0 0
0 0 1 0 0 0 0 0
0 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0

step 1 - f(2,5):
0 1|2 3 4 5|6 7 - position

0 0 0 0 0 0 0 1
0 0 0 0 0 0 1 0
0 0 1 0 0 1 0 0
0 0 0 1 1 0 0 0
0 0 0 1 0 0 0 0
0 0 1 0 0 0 0 0
0 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0

step 2 - f(4,3), which contains f(6,1):
0 1|2 3 4 5|6 7 - position

0 0 0 0 0 0 0 1
0 0 0 0 0 0 1 0
0 0 1 0 0 0 0 0
0 0 0 1 0 0 0 0
0 0 0 1 1 0 0 0
0 0 1 0 0 1 0 0
0 1 0 0 0 0 1 0
1 0 0 0 0 0 0 1

step 3 - f(0,7), which contains f(2,5):
0 1|2 3 4 5|6 7 - position

1 0 0 0 0 0 0 1
0 1 0 0 0 0 1 0
0 0 1 0 0 0 0 0
0 0 0 1 0 0 0 0
0 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 1

step 4 - f(6,1):
0 1|2 3 4 5|6 7 - position

1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0
0 0 1 0 0 0 0 0
0 0 0 1 0 0 0 0
0 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 1
```
代码就不整了，没上述做法好写。

---

## 作者：happy_dengziyue (赞：2)

### 1 思路

我们首先回顾其他题解写的思路，再补充一点我自己的技巧。

已有的题解写出了 $a_i\gets a_i\oplus a_j$ 的方法，让我们回顾一下：

1. 对 $[i,j-1]$ 执行一次后缀异或和；

2. 对 $[i+1,j-1]$ 还原；

3. 对 $[i,j]$ 执行一次后缀异或和；

4. 对 $[i+1,j]$ 还原。

其中，对 $[l,r]$ 执行一次后缀异或和意味着用 $r-l$ 次操作使得 $a_i(l\le i\le r)\gets \bigoplus_{j=i}^r a[j]$，即让 $a_{[l,r]}$ 变为这个子区间的后缀异或和。

我们还发现，如果先求 $a_i\gets a_i\oplus a_j$，再求 $a_{i-1}\gets a_{i-1}\oplus a_{j+1}$，那么前者的操作 $3$ 跟后者的操作 $1$ 重叠部分巨大，而操作 $4$ 则大量浪费了操作次数。

因此，考虑到交换 $x,y$ 等价于 `x^=y; y^=x; x^=y;`**（注意，在本篇题解中，交换 $x,y$ 不等价于交换 $y,x$）**，并且我们本质上要交换 $a_i,a_{n-i-1}$，所以我们可以先执行全部的 `x^=y`，再执行全部的 `y^=x`，再执行全部的 `x^=y`，调整一下顺序并且不进行不必要的操作 $4$ 就可以使用 $239997$ 次操作通过本题。

以上都是其他题解写出来的。那么怎么才能不进行不必要的操作 $4$ 呢？

我们可以首先不作优化，然后调整好操作顺序，**得到操作序列后将相邻的两个相同的操作消掉，就解决问题了。**显然这样做代码复杂度会减小，~~甚至将总操作次数优化到了 $239993$。~~

到这里我们就能够通过此题了，~~但是为了吊打 std，我们不妨再优化一下。~~

首先我们设 $dis(x,y)=(y-x+n)\bmod n$，即一条从 $x$ 到 $y$ 的弧的长度，发现如果 $dis(x,y)>dis(y,x)$，那么交换 $x,y$ 不如交换 $y,x$。所以我们在 $dis(i,n-i-1)>dis(n-i-1,i)$ 的时候选择交换 $a_{n-i-1},a_i$ 而非交换 $a_i,a_{n-i-1}$ 会更优。

最后实测可以用 $200788$ 次操作通过此题，~~远高于~~题解里最优秀的 $200792$ 次。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 400
int n;
vector<int>g1;
vector<int>g2;
int p[1000000];
int pi=0;
int ans[400000];
int ansi=0;
void upd(int x){p[++pi]=x;}
int dis(int x,int y){return (y-x+n)%n;}
void askxor(int x,int y){
	if((x+1)%n==y){upd(x); return;}
	for(int i=(y-1+n)%n;i!=x;i=(i-1+n)%n)upd((i-1+n)%n);
	for(int i=(x+1)%n;i!=(y-1+n)%n;i=(i+1)%n)upd(i);
	for(int i=(y-1+n)%n;i!=x;i=(i-1+n)%n)upd(i);
	upd(x);
	for(int i=(x+1)%n;i!=y;i=(i+1)%n)upd(i);
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1748F_1.in","r",stdin);
	freopen("CF1748F_1.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=0;i<n-i-1;++i){
		if(dis(i,n-i-1)<=dis(n-i-1,i))g1.emplace_back(i);
		else g2.emplace_back(n-i-1);
	}
	
	reverse(g1.begin(),g1.end());
	for(auto i:g1)askxor(i,n-i-1);
	reverse(g1.begin(),g1.end());
	for(auto i:g1)askxor(n-i-1,i);
	reverse(g1.begin(),g1.end());
	for(auto i:g1)askxor(i,n-i-1);
	
	for(auto i:g2)askxor(i,n-i-1);
	reverse(g2.begin(),g2.end());
	for(auto i:g2)askxor(n-i-1,i);
	reverse(g2.begin(),g2.end());
	for(auto i:g2)askxor(i,n-i-1);
	
	for(int i=1;i<=pi;++i){
		if(ansi&&ans[ansi]==p[i])--ansi;
		else ans[++ansi]=p[i];
	}
	printf("%d\n",ansi);
	for(int i=1;i<=ansi;++i)printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/123485064)

By **dengziyue**

---

## 作者：MSqwq (赞：2)

一道令人头大的题。。。  

题意：给你一个序列其中第 $a_i = 2^i $，$i\in[0,n)$，然后你可以对一些数进行若干次操作使其翻转，操作为选一个 $i$，进行 $a_i = a_i \oplus a_{(i+1)\bmod n}$。  

题解：  
首先你要发现很多性质：  
第一，把反转的操作理解为交换两数位置，那么需要交换。 $\left\lfloor\frac{n}{2}\right\rfloor$ 次 ，这个很显然，然后对于每个交换操作映射到异或上面其实就是 $x = x \oplus y $，$y = x \oplus y$，$x = x \oplus y$。  

第二，如果在本题中我想跨位置异或两个数，其实是需要很多次操作步骤的，即若交换 $i$ 和 $j$ 的位置，需要 $4 \times (j-i+n)\bmod n$ 次操作，我们发现若需要优化这个步骤需要最小化 $j-i$，那么我们假设 $j-i = 3$ ，其实只需要两步即可即：$a_i = a_i \oplus a_j$，$a_{i+1} = a_{i+1} \oplus a_{j-1}$。  

第三，那么我们将性质一和性质二结合起来，就可以发现一个新的结论：$a_{i} = a_{i} \oplus a_{n-j-1}$。  
思考到这一步其实就相当于解决了交换 $\left\lfloor\frac{n}{2}\right\rfloor$ 的实现问题，复杂度为$O (\dfrac{n^2}{2})$。  

那么对性质三进行加工：  
那么我们不妨假设这个处理的函数为 $f(i,j)$ ，意味反转区间 $[i,j]$ 。  
再设 $m = (j-i+n) \bmod n$ ， $b_j = a_{(i+k)\bmod n}$。   
那么加上结论三，就有 $b_{i} = b_{i} \oplus b_{m-j-1}$。   
这里我们就可以利用性质一进行三次操作，即 $f(0,n-1)$，$f(\frac{n-1}{2},\frac{n}{2}-1)$，$f(0,n-1)$ ，注意这里并不需要考虑 $n$ 的正负，因为向下取整就避免了这个问题，最坏情况也是自己和自己交换，我们是可以接受这种忽略不计的步数。   
简单证明一下复杂度，大概就是 $3\times \frac{n^2}{2} = 240,000 \le 25,000$ ，嗯非常优秀。  

其实说到这里就可以完成这题了，但怕读者不清楚 $f(i,j)$ 如何构造，我们进行进一步的介绍如何构造。 

首先对从 $m-1$ 到 $0$ 的每个 $i$ 执行操作:  
$\Rightarrow b = [(0...m),(1...m),(2...m)...,(i...m),...,b_m]$  
再对从 $1$ 到 $m-1$ 的每个 $i$ 执行操作:  
$\Rightarrow b = [(0...m),b_1,b_2,b_3,...,b_i,...,b_m]$  
重复 $\frac{m}{2}$次以上操作   
对从 $m-2$ 到 $1$ 的每个 $i$ 执行操作:  
$\Rightarrow b = [(0...m),(1...m-1),(2...m-1)...,(i...m-1),...,b_m]$  
对从 $2$ 到 $m-2$ 的每个 $i$ 执行操作:  
$\Rightarrow b = [(0...m),(1...m-1),b_2,b_3,...,b_i,...,b_m]$    

以上步骤写成通项其实就是:  
$\Rightarrow b  [(0...m),(1...m-1),(2...m-2),...,(i...m-i),(\left\lfloor\frac{m-1}{2}\right\rfloor...\left\lfloor\frac{m}{2}+1\right\rfloor)b_{\left\lfloor\frac{m+1}{2}\right\rfloor},...,b_i,...,b_m]$      
最后记得把每一坨异或起来就行了，柿子比较复杂，自己推一推其实就好了。  

第一次写这么难得题的题解，如果有什么写的不好的希望大家指出，不出意外我的思路就是这样。  
代码如下：  
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<functional>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{ 
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
int n;
vector<int>ans;
void MSqwq(int l,int r)
{
	int now=(r-l+n)%n;
	for(int i=0;i<=(now+1)/2-1;i++)
	{
		int tot=0,to=((r-i-1)%n+n)%n;
		ans.push_back(to),tot++;
		
		if(to!=(l+i)%n)
		{
			for(int j=to;j!=(l+i)%n;j=(j+n-1)%n)
				ans.push_back((j+n-1)%n),tot++;	
		}
		
		if(tot!=1)
		{
			to=(l+i+1)%n;
			ans.push_back(to),tot++;
			if(to!=((r-i-1)%n+n)%n)
			{
				for(int j=to;j!=((r-i-1)%n+n)%n;j=(j+1)%n)	
					ans.push_back((j+1)%n),tot++;
			}
		}
	}
	for(int i=0;i<=now/2-1;i++)ans.push_back((l+i)%n);
}

int main()
{
	n=read();
	MSqwq(0,n-1),MSqwq((n+1)/2,n/2-1),MSqwq(0,n-1);
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：Piggy343288 (赞：1)

这 3000？

以下，$\operatorname{op}(i)$ 代表对 $i$ 进行一次操作。

我们考虑暴力。因为每一位都是分开处理的，我们考虑仅仅把一段区间的端点交换。即我们希望通过 $\operatorname{solve(l, r)}$ 把 $a_ia_j$ 交换而其他下标不动。一个显然的想法是，我们一定需要大量的前后缀异或操作和差分操作，以达到把两个数异或的目的。  

那么我们不难思考出如下算法：  
- 做操作 $\operatorname{op}(j-2\sim i)$，然后 $a_{i+k}=\oplus_{w=i+k\sim j-1}a_w$。
- 还原 $a_{i+1}\sim a_{j-2}$。
- 做操作 $\operatorname{op}(j-1\sim i+1)$，然后 $a_i\oplus a_{i+1}$。
- 还原 $a_{i+1}\sim a_{j-1}$。

然后发现最后没有必要还原，然后略作计算发现这东西能过。所以暴力能过这道题！

---

## 作者：Alex_Wei (赞：1)

先进行一些探索：考虑 $i < j$，执行 $j - 1\to i$ 可以对 $a_i\sim a_j$ 做后缀和。然后再执行 $i + 1\to j - 1$ 还原 $a_{i + 1}\sim a_j$。这样，我们花了 $2(j - i)$ 的代价将 $a_i$ 变成了 $a_i\sim a_j$ 的异或和。

进一步地，再将 $a_i$ 变成 $a_i\sim a_{j - 1}$ 的异或和，我们可以花 $4(j - i)$ 的代价执行 $a_i\gets a_i\oplus a_j$ 的操作。将其表述为 $f(i, j)$。当 $i > j$ 时，也可以类似操作，代价为 $4(n + j - i)$。

为实现目标，只需交换 $a_i$ 和 $a_{n - 1 - i}$。关于交换，有一个非常经典的异或实现：`a ^= b ^= a ^= b`。因此，交换 $a_i$ 和 $a_j$ 可以表述为 $f(i, j), f(j, i), f(i, j)$。单次交换的平均次数为 $6n$，总操作次数为 $3n ^ 2$，无法接受。

进一步观察，我们发现在执行 $f(i, j)$ 的第三步时，相当于恰好执行了 $f(i + 1, j - 1)$ 的第一步。因此，常数砍半，总操作次数 $1.5 n ^ 2$，可以通过，[代码](https://codeforces.com/contest/1748/submission/184881118)。

在朴素做法中，我们执行了两次 $f(i, j)$。如果 $f(j, i)$ 的代价小于 $f(i, j)$ 的代价，我们可以考虑执行 $f(j, i), f(i, j), f(j, i)$ 达到相同的效果。这样，总操作次数为 $2.5n ^ 2$，类似优化后容易做到 $1.25 n ^ 2$。

---

## 作者：chroneZ (赞：1)

首先只考虑两个数 $a_i,a_j$，可以通过以下的异或操作实现交换操作：
$$a_i \gets a_i \oplus a_j$$
$$a_j \gets a_i \oplus a_j$$
$$a_i \gets a_i \oplus a_j$$
那么，如何类比到这道题呢？我们一步一步考虑。

## 算法 1

一种比较容易的思路是考虑如何使 $a_i \gets a_i \oplus a_j$。下文为简化叙述，记一个长为 $m$ 的数组 $b$，并记 $(l \dots r)$ 表示 $\oplus_{i=l}^{r}{b_i}$，$(l,r)$ 表示 $b_l \oplus b_r$。

考虑如何使 $b_0 \gets b_0 \oplus b_m$。首先**从 $m-1$ 向 $0$ 扫一遍**，此时的序列状态为：
$$b=[(0 \dots m),(1 \dots m),\dots,(m-1 \dots m),m]$$
因为要让 $b_0 \gets (0,m)$，所以递推地考虑能不能让 $b_1 \gets (1 \dots m-1)$。所以接下来可以**从 $1$ 向 $m-1$ 扫一遍，再从 $m-2$ 向 $1$ 扫一遍**：
$$b=[(0 \dots m),1,2,\dots,m-1,m]$$
$$b=[(0 \dots m),(1 \dots m-1),(2 \dots m-1),\dots,(m-2 \dots m-1),m-1,m]$$
这样一来再**从 $0$ 向 $m-2$ 扫一遍**，最终得到了：
$$b=[(0,m),1,2,\dots,m-1,m]$$

简单的分析一下，容易发现完成一次异或操作的复杂度达到了 $4m$ 的量级，完成一次交换操作就大概需要 $4n+4m$ 的操作量了，原序列需要 $\mathrm{swap}$ $\frac{n}{2}$ 次，因此我们大概需要 $2n^2+2nm$ 的操作量。然而这个题~~很毒瘤~~只留了 $250000$ 次操作机会，而 $2n^2$ 就已经达到 $320000$ 了。

## 算法 2

分析一下构造数组 $b$ 的过程，不难发现在我们枚举 $\mathrm{swap}$ 的时候是存在很多重复步骤的！因此想到如何尽量避免重复步骤。单次 $\mathrm{swap}$ 的过程显然没什么可优化的，所以考虑是否能减少 $\mathrm{swap}$ 的次数。

事实上是可以整体考虑的。观察算法 1 中构造 $b$ 数组的过程，容易发现得到 $b=[(0 \dots m),1,2,\dots,m-1,m]$ 是只需要 $2m$ 的操作数的。利用这个结论继续归纳的话，我们不难构造出如下的数组 $b$：

（$m$ 为偶）$b=[(0 \dots m),(1 \dots m-1),(2 \dots m-2),\dots,(\frac{m}{2}-1 \dots \frac{m}{2}+1),\frac{m}{2},\dots,m-1,m]$

（$m$ 为奇）$b=[(0 \dots m),(1 \dots m-1),(2 \dots m-2),\dots,(\frac{m-1}{2} \dots \frac{m+1}{2}),\frac{m+1}{2},\dots,m-1,m]$

最后**从 $0$ 向 $\lfloor \frac{m}{2} \rfloor - 1$ 扫一遍**即可得到：

（$m$ 为偶）$b=[(0,m),(1,m-1),(2,m-2),\dots,(\frac{m}{2}-1,\frac{m}{2}+1),\frac{m}{2},\dots,m-1,m]$

（$m$ 为奇）$b=[(0,m),(1,m-1),(2,m-2),\dots,(\frac{m-1}{2},\frac{m+1}{2}),\frac{m+1}{2},\dots,m-1,m]$

记将 $a$ 数组中的一段 $[l,r]$ 变为如上形式的过程为 $f(l,r)$。（即取出 $a$ 数组中的 $[l,r]$ 段作为 $b$ 数组时的操作过程）

（注意原题意中 $a$ 数组可以视作一个环，所以 $l>r$ 时意为 $[l,n-1] \cup [0,r]$）

![](https://cdn.luogu.com.cn/upload/image_hosting/bnbzx2cb.png)

（以下叙述默认 $n$ 为偶数）我们先试着执行一次 $f(0,n-1)$，发生改变的部分对应着上图中的 $A$ 部分。**这和开篇提到的交换有异曲同工之妙**，如果我们接着执行 $f(\frac{n}{2},\frac{n}{2}-1)$，发生改变的部分对应上图 $B$ 部分。所以我们把 $A,B$ 部分视为整体，可以得到一个大概的思路：依次进行 $f(0,n-1),f(\frac{n}{2},\frac{n}{2}-1),f(0,n-1)$，改变 $A,B,A$。注意 $A,B$ 两部分中编号相同的位置，拿 $1$ 举例：
- 当我们通过操作 $f(0,n-1)$ 改变了 $A$ 部分时，$A_1 \gets A_1 \oplus B_1$，即 $a_0 \gets a_0 \oplus a_{n-1}$
- 当我们通过操作 $f(\frac{n}{2},\frac{n}{2}-1)$ 改变了 $B$ 部分时，$B_1 \gets A_1 \oplus B_1$，即 $a_{n-1} \gets a_0 \oplus a_{n-1}$
- 最后一步通过操作 $f(0,n-1)$ 改变了 $A$ 部分时，$A_1 \gets A_1 \oplus B_1$，即 $a_0 \gets a_0 \oplus a_{n-1}$

上述操作过程对于其它编号同理。最终我们便成功反转了 $a$ 序列。

不妨分析一下复杂度，每次执行 $f$ 时操作次数为 $m+(m-1)+\dots+1+\frac{m}{2}=\frac{m^2+2m}{2}$。因此解决该题共需 $\frac{3}{2} (m^2+2m)$ 次操作。显然有 $m\leq n\leq 400$，故 $\frac{3}{2} (m^2+2m)\leq 241200$，可以通过。（实测 $n = 400$ 的点应该是 $239997$ 次）

摆一下结论：

- 若 $n$ 为偶数，依次执行 $f(0,n-1),f(\frac{n}{2},\frac{n}{2}-1),f(0,n-1)$ 即可反转序列。

- 若 $n$ 为奇数，依次执行 $f(0,n-1),f(\frac{n+1}{2},\frac{n-1}{2}-1),f(0,n-1)$ 即可反转序列。

## $\texttt{Main Code}$

```cpp
vector<int> ans;
int n;
inline void work(int l, int r){
	if(l > r) r += n;
	int opl = l, m = r - l;
	for(int i = 1; l <= r; i ^= 1){
		if(i){
			r--;
			for(int j = r; j >= l; --j)
				ans.push_back(j);
		}else{
			l++;
			for(int j = l; j <= r; ++j)
				ans.push_back(j);
		}
	}
	for(int i = opl; i < opl + m / 2; ++i) ans.push_back(i);
}
void solve(){
	cin >> n;
	if(n & 1){
		work(0, n - 1);
		work((n + 1) / 2, (n - 1) / 2 - 1);
		work(0, n - 1);
	}else{
		work(0, n - 1);
		work(n / 2, n / 2 - 1);
		work(0, n - 1);
	}
	cout << ans.size() << '\n';
	for(auto &x : ans) cout << x % n << ' ';
}
```

---

