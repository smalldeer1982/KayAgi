# Powerful Ksenia

## 题目描述

Ksenia has an array $ a $ consisting of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ .

In one operation she can do the following:

- choose three distinct indices $ i $ , $ j $ , $ k $ , and then
- change all of $ a_i, a_j, a_k $ to $ a_i \oplus a_j \oplus a_k $ simultaneously, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

She wants to make all $ a_i $ equal in at most $ n $ operations, or to determine that it is impossible to do so. She wouldn't ask for your help, but please, help her!

## 说明/提示

In the first example, the array becomes $ [4 \oplus 1 \oplus 7, 2, 4 \oplus 1 \oplus 7, 4 \oplus 1 \oplus 7, 2] = [2, 2, 2, 2, 2] $ .

## 样例 #1

### 输入

```
5
4 2 1 7 2```

### 输出

```
YES
1
1 3 4```

## 样例 #2

### 输入

```
4
10 4 49 22```

### 输出

```
NO```

# 题解

## 作者：duyi (赞：19)

[噜啦噜啦咧噜啦噜啦咧的阅读体验](https://www.cnblogs.com/dysyn1314/p/14007401.html)


# CF1438D Powerful Ksenia

## 题目大意

给出 $n$ 个正整数 $a_1,a_2,\dots,a_n$。

在一次操作中，你可以：

- 选择三个不同的下标 $i$, $j$, $k$。
- 将 $a_i$, $a_j$, $a_k$ 三个值，全部置为 $(a_i\operatorname{xor} a_j\operatorname{xor} a_k)$。

请通过不超过 $n$ 次操作，使得序列里所有数都相等。注意：不需要最小化操作数量。

数据范围：$1\leq n\leq 10^5$，$1\leq a_i\leq 10^9$。

## 本题题解

首先，当 $n$ 为奇数时，不论 $a$ 中的数是什么，我们一定可以构造出一组解。具体方法如下：

考虑，如果序列里，除某个数 $a_p$ 外，其他（剩下偶数个数）数能两两配对，使得每对数相等。设配出的 $\frac{n-1}{2}$ 对下标分别为 $(u_1,v_1),(u_2,v_2),\dots,(u_{\frac{n-1}{2}},v_{\frac{n-1}{2}})$。则我们接下来只需要依次操作：

- $(p,u_1,v_1)$
- $(p,u_2,v_2)$
- $\dots$
- $(p,u_{\frac{n-1}{2}},v_{\frac{n-1}{2}})$

就能使得序列里所有数都等于 $a_p$。这是因为 $a_{u_i}=a_{v_i}$，所以每次三个数异或起来时，$a_{u_i},a_{v_i}$ 就会自己抵消掉，剩下 $a_p$。即：$\forall i:(a_{u_i}\operatorname{xor}a_{v_i}\operatorname{xor}a_p)=a_p$。这部分一共需要 $\frac{n-1}{2}$ 次操作。

思考如何达到这种 $\frac{n-1}{2}$ 对数两两相等的局面。可以依次对所有 $i=1,3,5,\dots ,n-2$，做操作 $(i,i+1,i+2)$。这样，就能使所有 $(i,i+1)$ 相等（$i=1,3,5,\dots,n-2$）。最后剩下 $p=n$。然后进行上述操作即可。

总共需要 $\frac{n-1}{2}+\frac{n-1}{2} = n-1$ 次操作。

---

当 $n$ 是偶数时，首先要观察到，一次操作**不会改变序列里所有数的异或和**。而最终序列中要求所有数都相等，异或和一定是 $0$，所以原序列的异或和也一定要是 $0$。

那么首先判断，如果原序列异或和不为 $0$，则直接输出 $\text{NO}$。

否则我们随便拿出一个数，不妨拿出 $a_n$。剩下奇数个数 $a_1,a_2,\dots,a_{n-1}$，通过上述的构造，一定能变成所有数都相等的情况，设这个相等的值为 $x$。那么这 $n-1$ 个数的异或和也为 $x$。因为序列里所有数异或和为 $0$，所以一定有 $x=a_n$。于是我们根本不需要考虑 $a_n$，直接对前 $n-1$ 个数用奇数的方法构造即可。

---

时间复杂度 $O(n)$。

## 总结

$n$ 是奇数的情况，是比较简单的构造。自己手玩一会应该就能看出来。

$n$ 是偶数时，用到一个技巧：观察每次操作**不变的量**（例如本题中是异或和。其他题目有时是奇偶性等等）。那么，开始局面的这个量，必须和目标局面相等。也就是说，我们找到一个必要条件。然后思考这个必要条件是否充分。如果充分，我们也就构造出了操作的方法。

## 参考代码

[勇敢向前进！！！前进有奖品！！！](https://www.cnblogs.com/dysyn1314/p/14007401.html)






---

## 作者：Purslane (赞：10)

## Solution

构造题 , 应先从小情况看起 .

- 三个数的情况 

不妨设它们为 $ [ a ,b ,c ] $ , 操作一下 , 变成了 $ [ x , x ,x ] $ , $ x $ 是它们的异或和 . 好像就做完了 .

- 四个数的情况

不妨设它们为 $ [ a , b , c , d ]$ , 把前三个操作一下 , 变成了 $ [ x , x , x , d ]$ , 好像没有结束 . 但我们假设最终状态 ( 假设能完成 ) 是 $ [ y , y , y , y] $ ,那么显然 , 异或和是 $ y \oplus y \oplus y \oplus y = 0$ .

这时我们注意到 : 如果对一个序列进行一次操作 , 异或和将变为 ( 设原状态为 $ [a , b , c , ... , z ]$ , 我们对$ a , b , c$操作 ) : $ ( a \oplus b \oplus c) \oplus ( a \oplus b \oplus c) \oplus ( a \oplus b \oplus c) \oplus ... \oplus z = a \oplus b \oplus c \oplus ... \oplus z$ , **没有改变** .

所以 , 我们发现 :  **对于一个偶数数列 , 它能变成全部一样的条件是 : 原序列异或和为** $ 0 $ . 

那么 , 回到开始 , 我们发现 : $ x \oplus x\oplus  x \oplus d = 0 \Rightarrow  x=d $ . 所以 , 我们知道 , 四个数只有前三个数和第四个数异或和相等 ( 其实也就是四个数异或和为 $ 0 $ ) 时有解 , 否则无解 .

- 五个数的情况和任意奇数的情况

不妨设它们为 $ [ a , b , c , d , e]$ .

我们将前 $ 3 $ 个操作一下 ,变成 $ [ x ,x , x ,d ,e ] $ ; 再把后三个操作一下 ,变成 $ [ x ,x , y , y ,y ]$  ; 好像 $ y $  更多一些 , 那我们把 $ x $ 变成 $ y $ : 将前两个和最后一个操作一下 ( $ x \oplus x \oplus y = y $ ) , 就全变成 $ y $ 了 .

受此启发 , 我们可以构造出一个方案 :  **从 第 $ 1 , 3 , 5 ... $个数出发 , 每次 $ 3 $ 个数操作一下 , 数列就可以变成 $ [ a , a , b , b , ... , z , z ,z ] $的情况 . 这时候我们把所有不是$ z $ 的数都变成 $ z $ , 也就可以将第 $ 1 $ 和 $ 2 $ , $3$ 和 $4$ , $5$ 和 $6$ ... 都和最后一个数操作一遍 , 我们就可以得到全是 $z$ 的序列了** .

这样操作数量是多少呢 ? 分析一下 , 第一轮要操作 $\frac{n-1}{2}$ 次 , 第二轮就是 $\frac{n-3}{2}$ 次 , 加起来是 $ n-2$ 次 . 满足限制 .

code :

```cpp
if(n&1) {
	printf("YES\n");
	printf("%d\n",n-1);
	for(int i=1;i<=n-2;i+=2) printf("%d %d %d\n",i,i+1,i+2);
	for(int i=1;i<=n-2;i+=2) printf("%d %d %d\n",i,i+1,n);
}
```

- 六个数的情况和任意偶数的情况

和奇数类比 , 我们也从 第 $ 1 , 3 , 5 ... $个数出发 , 每次 $ 3 $ 个数操作一下 . 设原序列是 $ [a ,b ,c ,d ,e ,f ] $ , 那么就会变成 $ [ x ,x ,y ,y ,y , f ] $ , 和四个数的一样 , 只有 $y =f $ 时才有解 ( 想一想为什么 ) , 此时不就成了 $ [ x,x,y,y,y,y]$ 了吗 ? 剩下的处理就一样了.

**对于任意偶数 , 我们采取一样的策略 . 先看第一轮操作后倒数第二个数和最后一个数是否相等 , 不等就无解** . 

**如果相等 , 那么从 $ 1 , 3 , ... ,(n-5) $ 开头的两个数都和最多的最后 $4$ 个数不一样 ,分别把它们和最后一个数操作一下即可.**

这样操作数量又是多少呢 ? 分析一下 , 第一轮要操作 $\frac{n-2}{2}$ 次 , 第二轮就是 $\frac{n-4}{2}$ 次 , 加起来是 $ n-3$ 次 . 也满足限制 .

code :

```cpp
for(int i=1;i<=n-2;i+=2) a[i]=a[i+1]=a[i+2]=a[i]^a[i+1]^a[i+2];
if(a[n]!=a[n-1]) printf("NO");
else {
	printf("YES\n%d\n",n-3);
	for(int i=1;i<=n-2;i+=2) printf("%d %d %d\n",i,i+1,i+2);
	for(int i=1;i<=n-4;i+=2) printf("%d %d %d\n",i,i+1,n);
}
 ```
 
 
 ## 总结
 
 这给我们提供了一个做构造题的好方法 : 从小情况起 , 类比出大情况 . 
 
 另外 , 异或又许多美妙的性质(比如同一个数异或两次为 $0$ ) , 对我们做题有很大帮助 .

---

## 作者：do_while_true (赞：4)

[$\text{不一样的阅读体验}$](https://www.cnblogs.com/do-while-true/p/13976971.html)

# $\mathcal{Translate}$

[题目链接](https://codeforces.com/problemset/problem/1438/D)

给定长度为 $n$ 的序列 $a$，现在有这样一种操作：选择 $(i,j,k)$ 满足 $1\leq i,j,k\leq n,i\neq j\neq k$，将 $a_i,a_j,a_k$ 分别替换为 $a_i\oplus a_j\oplus a_k$，询问是否可以在 $n$ 次及以下的操作次数内将这个序列的所有数都相等，如果可以的话给出构造方案。

$3\leq n\leq 10^5,1\leq a_i \leq 10^9$

# $\mathcal{Solution}$

考虑一次操作带来了什么：

1. 将三个数推平，也就是把任意三个数变成相等的一个数。

2. 如果三个数中有两个相等，那么相当于把三个数都推平成除了那两个相等的第三个数。

1.是显然的，因为操作就是把它们三个推平。

2.是因为如果其中 $a_i=a_j$，那么 $a_i\oplus a_j=0$，则 $a_i\oplus a_j\oplus a_k=0\oplus a_k=a_k$。

---

此时对于 $n$ 为奇数的时候的构造方法就十分明显了，利用1.把整个序列推平成两个两个相等的小段，再用2.通过最后一个不一样的数把前面的小段都推平成最后的那个数，操作总数共有 $(n-2)$ 个。

---

对于 $n$ 为偶数的时候呢？

首先有一个结论，一次操作不会对序列的总按位异或和产生改变。

设操作前按位异或和为 $sum$，则一次操作相当于 $sum=sum\oplus a_i\oplus a_j\oplus a_i\oplus a_k\oplus a_j\oplus a_k$，化简一下发现 $sum$ 还是 $sum$。

则原先序列 $sum$ 为 $0$ 是有解的必要条件，因为偶数个相同的数按位异或和为 $0$。

当 $sum$ 不为 $0$ 的时候无解，当 $sum$ 为 $0$ 的时候不看最后一个数正常用奇数做法做前 $(n-1)$ 个数，发现最后它们都相等了。

设前 $(n-1)$ 个数推平后的数为 $x$，则前 $(n-1)$ 个数的按位异或和为 $x$，因为总的按位异或和为 $0$，两个数异或一下就是最后一个数的值，$x\oplus 0=x$，所以最后一个数也为 $x$，故这种做法是可行的。

# $\mathcal{Code}$

```cpp
//Code by do_while_true
#include<iostream>
#include<cstdio>
inline int read() {
	int r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') w = 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		r = (r << 3) + (r << 1) + (ch ^ 48);
		ch = getchar();
	}
	return w ? ~r + 1 : r;
}
const int N = 100010; 
int n, a[N], sum;
signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), sum ^= a[i];
	if(!(n&1)) {
		--n;
		if(sum) {
			puts("NO");
			return 0;
		} 
	}
	puts("YES");
	printf("%d\n", n-2);
	for(int i = 1; i + 2 <= n; i += 2) printf("%d %d %d\n", i, i+1, i+2);
	for(int i = 1; i + 1 <= n - 3; i += 2) printf("%d %d %d\n", i, i+1, n);
	return 0;
}
```

---

## 作者：BBD186587 (赞：3)

首先，要发现两个性质。

1.一次操作其实相当于把三个数变为相同的一个数。

2.每次操作前后整个数列的异或和不变。

第一个性质比较显然，证明一下第二个性质。

设原来这三个数分别为 $x$，$y$，$z$，

操作前，它们的异或和为 $x \oplus y \oplus z$ ，

操作后，这三个数都变成了 $x \oplus y \oplus z$ ，

它们的异或和仍然为 $x \oplus y \oplus z$ 。

先考虑数列长度为奇数的情况。

首先，把相邻的三个数操作一下，每次操作的起点即为上次操作的终点。

操作后，整个数列就变为了若干段长度为2的相同的数，以及最后一段长度为3的相同的数。

这样，把最后一个数拿出来，与前面的每两个相同的数都做一次操作即可。

操作次数为 $n-2$ 次，可以通过。

接下来，考虑数列长度为偶数的情况。

如果是有解的，且数列长度为偶数，那么最后整个数列的异或和一定为0。

根据上面的性质2，可以得到数列操作前的异或和也一定为0，同理，整个数列在每一步操作后的异或和也为0。

现在已经可以判断无解了。

若有解，考虑把最后一个数单独拿出来，把前面的 $n-1$ 个数按照奇数的做法做一遍。

因为整个数列在每一步操作后的异或和一定为0，又因为数列的前 $n-1$ 个数已经相等了，所以，它们也一定和最后一个数相等。

操作次数为 $n-3$ 次。

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int N=1e5+10;
int n,a[N],sum;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum^=a[i];
	if(n%2==0&&sum) puts("NO"),exit(0);
	if(n%2==0) n--;
	printf("YES\n%d\n",n-2);
	for(int i=1;i<=n-2;i+=2) printf("%d %d %d\n",i,i+1,i+2);
	for(int i=1;i<=n-4;i+=2) printf("%d %d %d\n",i,i+1,n);
	return 0;
}
```

---

## 作者：Aiopr_2378 (赞：2)

# Solution CF1438D Powerful Ksenia

一道典型**构造题**，首先考虑小的情况。

比如 $n=3$ 的时候(好像做完了)。

那么 $n=4$ 呢？

一次操作之后就变成了 $[a,a,a,b]$ 的情况，如果对后 $3$ 个做一次会变成 $[a,b,b,b]$ 。如果 $a$ 不等于 $b$ 那么无解。

 $n=5$ 呢？ $[a,b,c,d,e]->[x,x,x,d,e]->[x,x,y,y,y]->[y,y,y,y,y]$ 

在这里我们发现了一个好方法：如果这三个数是 $[a,a,b]$ 的形式，那么操作一次之后就变成 $[b,b,b]$ 了！（ $a\oplus a=0$ ）也就是说，如果我们把数弄成 $[a,a,b,b,c,c,d,d,…,f,f,f]$ 的形式，那么就可以连续使用 $[x,x,f]$ 的形式把所有数赋成 $f$ 。

操作次数最多为 $(n-3)/2\times2+1=n-2$ 。

### 所以奇数个是一定有解的。

那要是偶数个呢？

根据上面的推论，显然发现：奇数个时，进行玩第一轮排序后，最后一定有3个数相等。

那要是偶数个呢，一定会有三个数相等 $(n-4,n-3,n-2)$ 。那么如果最后一个数和前面三个相等，就整出 $0$ 了！

这下子好判断了吧！

参考代码：

```cpp
#include<iostream>
using namespace std;
int n,a[100005],sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum^=a[i];
	}
	if(!(n&1)){
		--n;
		if(sum){
			cout<<"NO";
			return 0;
		} 
	}
	cout<<"YES"<<endl<<n-2<<endl;
	for(int i=1;i+2<=n;i+=2) cout<<i<<" "<<i+1<<" "<<i+2<<endl;
	for(int i=1;i+1<=n-3;i+=2) cout<<i<<" "<<i+1<<" "<<n<<endl;
	return 0;
}
```

谢谢观看

---

## 作者：275307894a (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF1438D)

这个构造还是很巧妙的。

有一个显然的性质:序列中所有数的异或和等于最后只有一种数时所有数的异或和。

还有一个结论:当有三个数$a,b,b$时，只要一次操作就能使其变成三个$a$。

那么事实上无解的情况已经呼之欲出了:当$n\bmod 2=1$且序列中的所有数异或和不为$0$即无解。

现在主要是三步:处理出所有数得异或和，令其为$a_n$，将剩余$n-1$个数两两相等。再用$\frac{n}{2}$次操作将其变为一样。

对于$n$为奇数的情况，我们只要对于每个$i=2k+1$做一次$(i,i+1,i+2)$的操作即可，这样$a_{i+2}$处即为前$i+2$个数的异或和。且前$i+1$个数任意一个位置$k$都与$k\bigoplus1$相等。这样一边就处理出了前两步。

对于$n$为偶数的情况，则最后的序列中的数是什么都可以。不妨令其为前$n-1$个数的异或和。这在有解的情况下其实就等于$a_n$，所以只要仿照上面做一遍即可。

总共做了$n-1$次操作。复杂度$O(n)$

代码实现:
```cpp
#include<cstdio>
using namespace std;
int n,m,k,x,y,z,a[1000039],ans,tot,pus;
int head,xs[1000039],ys[1000039],zs[1000039];
int main(){
	register int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]),ans^=a[i];
	if(n%2==0&&ans) {printf("NO\n");return 0;}
	for(i=3;i<=n;i+=2) xs[++head]=i-2,ys[head]=i-1,zs[head]=i;
	for(i=2;i<n;i+=2) xs[++head]=i-1,ys[head]=i,zs[head]=n;
	printf("YES\n%d\n",head);
	for(i=1;i<=head;i++) printf("%d %d %d\n",xs[i],ys[i],zs[i]);
}
```

---

## 作者：MoonPie (赞：1)

一道巧妙的构造题.

### 题目描述

---

给 $n$ 个正整数 $a_i$,$1 \le a_i\le10^9$.

每次操作是选三个不同的下标 $i,j,k$ ，让 $a_i,a_j,a_k$ 都变成 $a_i \oplus a_j\oplus a_k$ 也就是这三个数的异或和.

让你判断是否能在 $n$ 次操作内，使这 $n$ 个正整数的值变成相同的.

若能，第一行输出YES，第二行输出 $m$ 表示操作数两，接下来 $m$ 行每行三个整数，描述一次操作；

若不能，输出NO.

### 题解
---

考虑到 $a \oplus a \oplus  b = b $  ，

我们先将相同的数两两配对.

然后如果配对完剩下的数的**个数**是奇数，

可以任取其中的三个然后形成一个新的配对，重复操作直到只剩下 $1$ 个单独的元素.

最后每次那这个数，记作 $x$，和已经匹配完成的二元组进行一次操作，便可以使所有的数值变成 $x$.

这样的话，每个二元组最多被操作两次（形成一次，最后和 $x$ 一次），所以操作次数一定不超过 $n$.

并且可以发现，若 $n$ 是奇数，一定有解

---
如果配对完剩下的数的**个数**是偶数，及 $n$ 是偶数.

考虑到每次操作都是异或，那么这 $n$ 个数的异或和一定不发生改变，

其次是，考虑到最后是使得这 $n$ 个数相同，又有偶数个数，所以异或和为 $0$.

综上所述，若 $n$ 是偶数，且异或和不为 $0$ ，输出NO.

那么，若 $n$ 是偶数，且异或和为 $0$ 能？ 

貌似匹配到最后会剩下 $2$ 个元素，貌似不能用上面的算法了...

但如果仔细想想，**最后剩下的两个元素势必是相等的，因为异或和为0**

那就和奇数一样做就解决了

### codes

---

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace moonpie {
    #define P pair<int,int>
    #define fi first
    #define se second

    const int N=1e5+5;
    int n,a[N],cnt=0,ped[N];
    map<int,int> mp;
    P pi[N];
    struct operation {
        int x,y,z;
    };
    void solve() {
        cin>>n;
        int sum=0;
        for(int i=1;i<=n;++i) {
            scanf("%d",&a[i]);
            sum = (sum^a[i]);
        }
        if(sum!=0 && n%2==0) {
            printf("NO\n");
            return ;
        }

        for(int i=1;i<=n;++i) {
            if(mp[a[i]]) {
                pi[++cnt]=P(mp[a[i]],i);
                ped[i]=ped[mp[a[i]]]=1;
                mp[a[i]]=0;
            }
            else {
                mp[a[i]]=i;
            }
        }

        queue<int> Q;
        queue<operation> op;

        int flag=0;
        for(int i=1;i<=n;++i) {
            if(!ped[i]) {Q.push(i);flag=1;}
        }

        if(!flag) {
            Q.push(pi[cnt].fi);
            cnt--;
        }

        int ans=0;
        while(Q.size()>=3) {
            int u = Q.front(); Q.pop();
            int v = Q.front(); Q.pop();
            int w = Q.front(); Q.pop();
            ans++;
            op.push(operation{u,v,w});
            Q.push(w);
            pi[++cnt]=P(u,v);
        }
        
        int x = Q.front();
        for(int i=1;i<=cnt;++i) {
            ans++;
            op.push(operation{pi[i].fi,pi[i].se,x});
        }

        printf("YES\n");
        printf("%d\n",ans);

        while(!op.empty()) {
            printf("%d %d %d\n",op.front().x,op.front().y,op.front().z);
            op.pop();    
        }
        
    }
}
signed main() {
    moonpie::solve();
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

题目分析：

要求输出方案，所以考虑构造。

首先根据异或同一个数两次得到原数，可以得到：若操作的序列为 $x,x,y$，得到的结果就是 $y,y,y$。

然后根据这条性质，可以考虑先将序列异或成一个类似于 $x,x,y,y,z,z...a$ 的序列，其中最后一个数 $a$ 可以等于之前的某一个数，然后再用最后的一个 $a$ 一点一点异或回去，就能得到一个全部相等的序列。

再考虑如何构造这样的序列，显然有：把连续三个数异或完后下一次再带上这一次三个数的最后一个数向后异或三个数，举个例子就是：$a,b,c,d,e$ 一步操作（前三个）后变成：$x,x,x,d,e$，再操作一次（后三个）就是 $x,x,y,y,y$，达成了之前要求的序列形式。

计算一下总操作数，设 $n$ 表示原来的序列长度：则需要 $\dfrac{n-1}{2}$ 次操作来构造新串，然后还需要 $\dfrac{n-1}{2}-1$ 次操作来使得所有数相等，总共需要 $n-2$ 次操作。

但这样的序列显然不是所有长度的原序列都能构造的，根据构造规则，假如 $2\mid n$，那么最后一步就不能实现，也就导致构造序列最后有两个数是无法控制的，还原操作后还有一个数无法控制。

然后考虑如何判断这样的一个偶数序列是否能满足条件。发现每一次操作后三个数的总异或不变，而如果能构造成一个全相等序列，则其总异或一定是 $0$，那么就只需要判断原来的序列总异或是否为 $0$ 即可。

最后输出方案，这道题不需要输出最小的，可行就行（~~不然他就不是一道绿题了~~），那么就考虑一般构造：对于奇数个数的序列，每三个操作一次，然后再从后往前作相同操作，而对于一个可行的偶数序列，直接将其减一然后直接项奇数一样做，可以证明使得前 $n-1$ 个数构成相等的序列的最终值一定是等于一开始被抛弃的那一个数的。

------------
代码：
```cpp
#include<cstdio>
using namespace std;
int n,x,sum;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		sum^=x;
	}
	if(n%2==0){
		n--;
		if(sum!=0){
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	printf("%d\n",n-2);
	for(int i=1;i<=n-2;i+=2)printf("%d %d %d\n",i,i+1,i+2);
	for(int i=n-2;i>=3;i-=2)printf("%d %d %d\n",i,i-1,i-2);
	return 0;
}
```



---

## 作者：2x6_81 (赞：0)

### 题目大意
给你一堆数$a_1,a_2,...,a_n$，定义一次"操作"为：
1. 选择三个数 $i,j,k$
2. 让$a_i = a_j = a_k = a_i \oplus a_j \oplus a_k$

Ksenia希望最多使用n次"操作"将所有$a_i$变为全部相等

### 题解
分两种情况：一种是$n$为奇数，一种是$n$为偶数

如果是第一种情况：

可以发现，$a \oplus b \oplus b = a$，因此我们可以先将这$n$个数中的相同的数进行配对：

- 如果有三个两两不同的数，对这三个数进行一次"操作"；
- 之后将其中2个数配对，另一个数单独出来。

重复上述操作直到只剩一个没有配对的数。再将这个没有配对的数和其它配对的数进行$a \oplus b \oplus b = a$的操作。

显然，上述最多进行$n - 1$次"操作"

如果是第二种情况：

不妨令$X = a_1 \oplus a_2 \oplus ... \oplus a_n$，则易得无论进行多少次"操作"，X的值都不会变化。所以我们只需要判断$X$是否为$0$即可

1. 如果$X = 0$，那么对 $a_1,a_2,...,a_{n-1}$ 进行与$n$为奇数时同样的操作。可以发现在 $a_1 = a_2 = ... = a_{n-1}$ 成立后，$a_n = a_1$也成立了！
2. 如果$X \neq 0$，那么无论如何进行"操作"，$X$均不为$0$，也就是说$a_1 = a_2 = ... = a_n$ 不可能成立。因此输出$NO$


---

