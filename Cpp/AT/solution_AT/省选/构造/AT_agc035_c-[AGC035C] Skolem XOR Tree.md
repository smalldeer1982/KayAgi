# [AGC035C] Skolem XOR Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc035/tasks/agc035_c

整数 $ N $ が与えられます。$ 1 $ から $ 2N $ までの番号がついた $ 2N $ 個の頂点を持つ木であって次の条件を満たすものが存在するか判定し、存在するならばその一例を示してください。

- $ 1 $ 以上 $ N $ 以下の各整数 $ i $ について、頂点 $ i,\ N+i $ の重みが $ i $ であるとする。このとき、$ 1 $ 以上 $ N $ 以下の各整数 $ i $ について、頂点 $ i,\ N+i $ 間のパス上にある頂点 (両端を含む) の重みのビットごとの排他的論理和が $ i $ である。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 10^{5} $

### Sample Explanation 1

\- 出力例は以下のグラフを表します。 !\[d004b05438497d50637b534e89f7a511.png\](https://img.atcoder.jp/agc035/d004b05438497d50637b534e89f7a511.png)

### Sample Explanation 2

\- 条件を満たす木が存在しません。

## 样例 #1

### 输入

```
3```

### 输出

```
Yes
1 2
2 3
3 4
4 5
5 6```

## 样例 #2

### 输入

```
1```

### 输出

```
No```

# 题解

## 作者：pomelo_nene (赞：30)

下面的 $x'$ 皆表示 $x$ 的另外一个结点。

首先考虑无解情况。显然，当 $\operatorname{lowbit}(n)=n$ 的时候无解。

因为这样的话会存在 $n$ 与 $n'$，除了这两个数以外找不到其他的数的异或和为 $n$。因此无法匹配。

考虑其他的情况。分奇数和偶数考虑。有一个比较好用的性质：

$$
x \operatorname{xor} 1 = x+1( x \ \text{is an even number})
$$

因此，如果我们假设 $1$ 节点为根，就可以发现，将所有的数对 $(x,x+1)$（其中 $x$ 为偶数并且 $x+1 \leq n$）匹配到一起就会比较好处理。我们可以找到路径 $x \to x+1 \to 1 \to x',x+1 \to 1 \to x' \to (x+1)'$ 满足条件。

现在还有两个遗留的问题没有处理：

- 作为根的 $1$ 没有匹配，如何添加 $1'$？

假设 $1$ 为根，随便找一个叶子结点接上 $1'$，找到路径 $1 \to x \to (x \operatorname{xor} 1) \to 1'$。

- 如果 $n$ 是偶数，那么 $n,n'$ 就会遗留，如何处理？

考虑还是在根上处理。因为无解情况排除以后可以满足 $n$ 在转化成二进制之后有两个 $1$，于是找到一条路径 $n \to \operatorname{lowbit}(n) \to 1 \to (n - \operatorname{lowbit}(n) + 1)' \to n'$ 满足条件。

至此，我们在修修补补中完成了构造方法。

```cpp
#include<cstdio>
using namespace std;
int lowbit(int x){return x&(-x);}
int main(){
	int n;
	scanf("%d",&n);
	if(lowbit(n)==n)	return puts("No")&0;
	puts("Yes");
	for(int i=2;i<=n-1;i+=2)
	{
		printf("1 %d\n",i);
		printf("1 %d\n",i+n+1);
		printf("%d %d\n",i,i+1);
		printf("%d %d\n",i+n,i+n+1);
	}
	printf("%d 3\n",n+1);
	if(n%2==0)
	{
		printf("%d %d\n",n+lowbit(n)+1,n);
		printf("%d %d\n",n+n,n-lowbit(n));
	}
	return 0;
}
```

---

## 作者：chen_zhe (赞：13)

# [AGC035C] Skolem XOR Tree

月考之余做做构造题玩玩。

这个题比较好地考察了一些异或的性质。在一般的情况下我们用的较多的是异或的交换律，以及自己异或自己为 $0$。但是这个题不一样。

首先，我们要知道一点，对于一个偶数 $a$，必定存在 $a \bigoplus (a+1) =1$。因为偶数的二进制是形如 `1xxxxx0` 的，加上 $1$ 就形如 `1xxxxx1` 了，根据异或的计算方式，前面都是相同位，故为 $0$，只有最后一位为 $1$。这个性质应该可以推广到 $2^n \mid a$ 时，$\forall b \in [1,2^n) \cap Z,a \bigoplus (a+b)=b$。证明同上。

接着还有一点，不妨设 $a>b$，那么 $a \bigoplus b$ 的结果不可能超过 $a$ 最高位的 $1$ 所对应的位权乘以 $2$。证明显然，因为最高位的 $1$ 对应的位权乘以 $2$，代表着 $a$ 最高位的左边的一位，这一位必定是 $0$。而 $a>b$，所以 $b$ 的那一位也是 $0$，$0 \bigoplus 0=0$，故不存在。

----

那么我们知道了这么多奇怪的性质，能做什么呢？

首先考虑一下这个题的无解情况。当 $n$ 属于 $2$ 的整数次幂时，那么这个时候节点 $n,2n$ 都赋权为 $n$，这样两者异或结果是 $0$。而中间经过的其他节点的权值是必定小于 $n$ 的。因为 $n$ 正好是 $2$ 的整数次幂，因而小于 $n$ 的数字，在 $n$ 的最高位 $1$ 所对应的二进制位上必定是 $0$。因此，凑不出异或和为 $n$ 这个条件。故此时无解。

那么别的情况下呢？其实根据第一条性质，会发现别的情况一定有解。

既然对于偶数 $a$ 来说，$a \bigoplus (a+1)=1$，而且又根据 $1 \bigoplus 1=0$，那么我们可以考虑根据这两点，考虑整两个 $1$ 对消，这样就可以保留 $a$ 和 $(a+1)$ 了。因此经过尝试，可以发现，联结下述路径：$1 \to a,1 \to (a+1),a \to (a+n+1),(a+1) \to (a+n)$，这样可以满足 $a$ 和 $a+1$ 这两个节点。

然后会发现这么做，要对 $1$ 进行特殊判断，我们会发现，$1 \bigoplus 2 \bigoplus 3=0$。（当然如果一直异或到任意一个 $2^{n-1}$ 都是成立的，不再展开）。因此，我们可以链接 $1 \to 2,2 \to 3,3 \to (n+1),(n+1) \to (n+2),(n+2) \to (n+3)$，这样就可以保证了。

因为 $a+n+1$，当 $2\mid n$ 且 $a=n$ 时会超过 $n$，因此也要进行特殊处理。我们可以找到两个正整数 $(x,y)$，使得 $x \bigoplus y \bigoplus 1=n$。此时只需连接 $n \to x,2n \to y$ 即可。注意，对 $(x,y)$ 应该对 $3$ 进行特判，因为 $3$ 是被特殊构造出来的。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
	int n=read();
	if (!(n&(n-1))) 
		puts("No");
	else
	{
		puts("Yes");
		puts("1 2");
		puts("2 3");
		cout << 3 << " " << n+1 << endl;
		cout << n+1 << " " << n+2 << endl;
		cout << n+2 << " " << n+3 << endl;
		for (int i=4;i+1<=n;i+=2)
		{
			int j=i+1;
			cout << 1 << " " << i << endl;
			cout << 1 << " " << j << endl;
			cout << i << " " << j+n << endl;
			cout << j << " " << i+n << endl;
		}
		if (n%2==0)
		{
			for (int i=4;i<=n;i++)
			{
				int j=n^i^1;
				if (j!=3 && j<n)
				{
					cout << i << " " << n << endl;
					cout << j << " " << 2*n << endl;
					return 0;
				}
			}
		}
	}
	return 0;
}

```



---

## 作者：_bestow (赞：5)

AGC 就应该出这种有趣构造题。

首先考虑 $n=2^k$ 的情况，显然 $n\to 2n$ 的路径无法满足情况，所以无解。

我们想要一条路径异或起来等于某个值 $x$，那么考虑异或的性质，我们不妨找到一个 $x\bigoplus k$，和 $k$，然后把他们两个异或起来。还可以发现这个 $k$ 直接取 $1$ 就可以。所以对于每个 $x,x\bigoplus 1$ 我们都可以把它们和 $1$ 串起来，最后 $1$ 再随便串一个即可。

但是这样如果 $n$ 是偶数时没有 $n\bigoplus 1$，我们这时考虑再串一个 $y$，我们发现取 $y=n-1$ 时刚刚好，由于 $n$ 是偶数，那么 $n\bigoplus n-1$  一定全是 $1$ 且不止一个 $1$ 的二进制数。再异或一个 $1$，必然可以找到。我们把它们串起来，就可以得到答案。

代码非常简单，就不放了。

---

## 作者：hgckythgcfhk (赞：2)

重点说一下怎么想到构造方法的。

先锐评一下这个题，我觉得这个题本来可以很难而且很有趣，但样例已经把构造方法告诉我们了，这题最大的败笔就是样例给的太恰到好处，建议先别看样例，~~都来看题解了，我说了好像和没说一样~~。

首先 $n+i$ 这个东西表示起来比较影响我们看，我们暂时先认为 $i$ 和 $n+i$ 是同一个点复制出来的两个点，都把它的编号叫作 $i$。

然后，再给几个结论：

1. 当 $n+1$ 是 $2$ 的幂的时候，树是这样的链：

$1\to 2\to 3\to 4\to \dots n\to 1\to 2\to \dots\to n$

特别地，当 $n=1$ 时，无解。

2. 当 $n$ 是 $2$ 的幂的时候无解。

3. 路径是否包括起点和终点不重要。

现在看看，哪个结论最重要？

显然，最后一个最重要，一方面，这个结论的正确性是显然的，另一方面，这个结论可以推出前两个结论。

由于最后一个结论只是一句正确的废话，很多人可能想不到，我先说一下是怎么想到的，认识我的应该知道我选择题极其垃圾，~~GESP 能在 AK 掉大题的情况下只考 $82$ 的应该全国找不到第二个~~，像这种路径是否包括起点和终点，根节点深度是 $0$ 还是 $1$，树的高度是按根节点深度是 $0$ 还是 $1$ 算的最大深度之类的问题我都得现推，看到这个题，一眼路径，捕捉到关键词，试样例，于是还没开始试，就发现了这个结论。

那我都打算试了，那就试试吧，反正也不知道该干点什么，一看样例，嗯？构造方法这么特殊？那试试 $4$，发现无解，同时发现结论 $2$，因为起点和终点并不重要，所以我们可以认为不包括起点终点，反正会被异或掉，那么一堆比一个 $2$ 的幂小的数肯定异或不出来这个数，异或结果某一位上有 $1$ 的前提是至少得有一个数这一位上是 $1$，这个结论正确性显然，根据异或的定义就能证出来。

好，然后试试 $5$，发现不是很好做，放弃。

上面我们都试了 $4$ 了，$4$ 是 $2$ 的幂啊，我们看到 $3$ 的构造方法很特殊，肯定和 $3=4-1$ 有关吧，因为 $2$ 的幂减 $1$ 的性质也很特殊，除了比最高位还高的位其他位都是 $1$，那先试试 $7$ 的时候这个结论能不能成立，发现这个时候就很直观了，上面我们把 $i+n$ 看成 $i$ 的用处就体现出来了，那句正确的废话的用处似乎也体现出来了，我们发现，在这样的链上，两个一样的点的距离正好都是 $n+1$，而且正好能把 $n$ 个数覆盖一遍，且只有起点和终点的数会覆盖两遍，去掉起点和终点，那相当于这 $n$ 个点正好缺着起点和终点的数。

有个结论，这个结论就是得当定理记住的那种，不作解释：

$$\operatorname{xor}_1^{2^n-1}=0$$

那我从中间拿走一个数，根据异或的自反性，和结论 $1$ 的情况一样。

此时，这个题其实已经做完了，你可能会问，那不是这种特殊数的怎么办？

这么说吧，先画一条 $7$ 的链，你只要肯试，从 $9$ 开始，最多试到 $11$，就一定能做出来，这里我放个图然后解释一下这个图，一边解释一边就做出来了。

```cpp
8--9
   |
   1--2--3--4--5--6--7--1--2--3--4--5--6--7
   |
   8
   |
   9
```
怎么想到的呢，我先满足 $8$ 和 $9$ 都做不到，但是假设我们只有 $1,8,9$ 那和只有 $1,2,3$ 本质上是一样的，但我们只有一个 $1$，考虑 $9$，如果把 $1$ 当作中间点，可以把起点上的 $1$ 消掉，然后剩下 $8$，发现终点正好是 $9$ 那我们就要把这个 $8$ 消掉，此时我们已经没有 $9$ 可用了，只能用 $8$，发现这样的 $9\to 1\to 8\to 9$ 的链正好可以消掉起点，那我们只需要浪费掉剩下的 $8$ 即可，有了构造 $9$ 的经验，我们很自然的得到，需要在不破坏树此时的结构的前提下构造一条 $8\to 1\to 9\to 8$ 的链，于是画出上图，注意我上面那个 $8$ 其实可以竖着画，这里拐个弯虽然不改变树的结构但对于后面画图是有用的。

```cpp
   10
   |
8--9
   |
   1--2--3--4--5--6--7--1--2--3--4--5--6--7
   |  |
   8  10
   |
   9
```
$10=2\operatorname{xor}8$，所以根据上面的过程很自然的得到 $10\to 2\to 8 \to 10$，这里 $1\to 9$ 等价于 $8$。

```cpp
   10
   |
8--9
   |
   1--2--3--4--5--6--7--1--2--3--4--5--6--7
   |  |  |
   8  10 11
   |  |
   9  11
```
同上 $2\to 10$ 等价于 $8$。

于是我们可以直接一步画出 $14$。
```cpp
   10
   |
8--9
   |
   1--2--3--4--5--6--7--1--2--3--4--5--6--7
   |  |  |  |  |  |
   8  10 11 12 13 14
   |  |  |  |  |
   9  11 12 13 14
```
然后怎么做就不需要我描述了，具体过程用程序解释，但其实最重要的是图。

为防止因为火车头被打回，省略了宏定义和头文件，但不影响阅读。
```cpp
void edge(cit u,cit v){cout<<u<<' '<<v<<'\n';}
signed main(){open;int n;cin>>n;if(n&n-1){cout<<"Yes\n";
	if(!(n&n+1)){for(int i=1;i<n+n;++i)edge(i,i+1);return 0;}
	int st=1<<31-__builtin_clz(n);edge(1,st);edge(1,st+1);edge(st+1,st+n);edge(st,st+1+n);
	edge(st-1,n+1);for(int i=1;i<st-1;++i)edge(i,i+1),edge(i+n,i+n+1);
	for(int i=st+2;i<=n;++i)edge(i,i-st),edge(i-1,i+n);return 0;}cout<<"No";}

```
由于上午一直 waiting，程序有点小问题没发现，现在改过了，注意，不要光推着后面把中间的骨架落下，还有 AT 强制 C++17 不要 `register`。

---

## 作者：justin_cao (赞：2)

可以发现，对于$\forall i\geq 0,2i\bigoplus 2i+1=1$。

那么可以考虑，将$2i$和$2i+1$跟$1$相连，$n+2i$跟$2i+1$相连，$n+2i+1$跟$2i+1$相连，这样由于$2i\bigoplus2i+1\bigoplus 1=0$相当于是抵消了，所以是满足题目的条件的。

但是还需要考虑两个问题。

首先是$1$怎么办，发现$1\bigoplus 2\bigoplus 3=0$，于是可以考虑让$1,2,3,n+1,n+2,n+3$顺次相连，可以发现是满足条件的。（其它的按照上面的方法连）

第二个是如果$n$是偶数，$n$怎么办。那就考虑找到两个点$x,y$，使得$x\bigoplus y\bigoplus 1=n$，那么将$n$连上$x$，$2n$连上$y$，那么这条路径的权值显然是$n$了。这个$x,y$任意合法的即可，但是要注意，$x$和$y$不能选$3$，因为$3$号点到$1$的距离（不算$1$）并不是$3$。

另外无解的情况，看第二个问题可以发现，如果$n$是$2$的次幂，那么就不可能有小于$n$的两个数异或$1$得到$n$，因为最高位只有$n$有$1$。

那么这样就做完了。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m;
int main()
{
    n=read();m=log2(n);
    if((1<<m)==n)   return puts("No"),0;
    puts("Yes");
    printf("%d %d\n",1,2);
    printf("%d %d\n",2,3);
    printf("%d %d\n",3,n+1);
    printf("%d %d\n",n+1,n+2);
    printf("%d %d\n",n+2,n+3);
    for(int i=2;2*i+1<=n;i++)
    {
        printf("%d %d\n",1,2*i);
        printf("%d %d\n",1,2*i+1);
        printf("%d %d\n",2*i,2*i+n+1);
        printf("%d %d\n",2*i+1,2*i+n);
    }
    if(!(n&1))
    {
        for(int i=2;i<=n;i++)
        {
            if(i==3)  continue;
            int y=(i^1^n);
            if(y==3||y>n)  continue;
            printf("%d %d\n",n,i);
            printf("%d %d\n",2*n,y);
            break;
        } 
    }
    return 0;
}
```

---

## 作者：Grisses (赞：1)

首先发现 $n=2^k$ 时最高为位只有 $n$ 有 1，显然无法构造一条首尾都为 $n$ 的链的异或值为 $n$。

考虑符合条件的树长什么样子：对于 $x$，$x$ 和 $x+n$ 路径上的所有点的异或值为 $x$，比如 $2\to4\to6\to2+n\to4+n\to6+n$ 这样一条链。

也就是说如果我们现在有 $x_1\oplus x_2\oplus x_3\cdots\oplus x_m=0$，我们就可以把这些点依次串起来得到一条链。或者如果有 $x_1\oplus x_2\oplus x_3\cdots\oplus x_m=X$，我们可以构造一条 $x_1\to x_2\to x_3\to\cdots\to x_m\to X\to x_1+n\to\cdots\to x_m+n$ 的链（前提是 $X$ 已经被另外安排好了位置）。后面将这两种链分别简记为 $x_1\to x_2\to x_3\to\cdots\to x_m$ 和 $x_1\to x_2\to x_3\to\cdots\to x_m\leadsto X$。

然后我们发现如果 $n$ 是一个奇数，那么 $\bigoplus\limits_{i=1}^{n}i\in\{0,1\}$。也就是说要么可以一条链拉完，要么就先放 $1\to2\to3$，再用 1 连接剩下的链。

然后我们发现如果 $x$ 是一个偶数就没有如此优秀的性质了。

考虑记 $\bigoplus\limits_{i=1}^{n}i=z$。记 $x$ 表示 $z$ 除去 $2^0$ 位后的最低位的 1 对应值。因为一开始就判掉 $n=2^k$ 了，所以显然是能取到值的。考虑先放一条 $2\to x\to x+2$ 或者当 $x=2$ 时放一条 $4\to2\to6$。将这 3 个数记为 $a,b,c$。

然后记 $y=z\oplus x,u=y\oplus 1$，然后放一条 $x+1\to y\to u\leadsto x$ 的链。

最后记剩下的 $n-6$ 个数为 $x_{1,n-6}$，放一条 $x_1\to x_2\to x_3\to\cdots\to x_{n-6}\leadsto y$ 的链就完了。

考虑证明这样的正确性：

首先考虑 3 条链的合法性：我们第一步放置的 $a\to b\to c$，显然是满足 $a\oplus b\oplus c=0$ 的；第二步的 $y\oplus u=1,(x+1)\oplus 1=x$ 所以有 $(x+1)\oplus y\oplus u=x$；剩下的 $\bigoplus\limits_{i=1}^{n-6}x_i=z\oplus(a\oplus b\oplus c)\oplus((x+1)\oplus y\oplus u)=z\oplus x=y$。

再考虑证明 $a,b,c,x+1,y,u$ 互不相同且均不超过 $n$：首先，显然 $a,b,c,x+1$ 互不相同以及 $y\neq u$。因为 $x+1=x\oplus 1,x\oplus y=z,z\neq 0,z\neq 1,y\oplus u=1$，如果有相等可以简单地推出矛盾。

但是我们发现好像上述证明只对 $n>6$ 有用，所以 $n=6$ 手玩一下特判就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/cb6a0pn0.png)

---

[代码](https://atcoder.jp/contests/agc035/submissions/61525850)。

---

## 作者：Exp10re (赞：1)

躺床上不到五分钟搓出来的构造。

### 解题思路

考虑无解的情况，不难发现，若存在 $k\in \mathbb{Z}$ 满足 $n=2^k$ 则无解，原因任取其他数异或必定不能得到 $n$。

接下来对 $n \mid 2$ 和 $n \nmid 2$ 进行分类讨论。

- $n \nmid 2$

在此种情况下，$\forall 3 \leq k \leq n,k\nmid 2$ 均有 $k-1\leq n$ 以及 $(k-1) \oplus 1=k$，由此可知，$\forall 2 \leq i \leq n$，在 $n \nmid 2$ 的条件下有 $(i \oplus 1) \leq n$。

不妨考虑对于每一对 $(k,k-1)$ 进行构造：考虑将所有 $\forall 2\leq i \leq n$ 连一条边 $(i,1)$，然后再连一条边 $(i+n,i \oplus 1)$。

如此，$i$ 与 $i+n$ 之间的点为 $1$ 与 $(i \oplus 1)$，两者异或值为 $i$。

接下来只需要考虑在哪里放 $(1+n)$，注意到 $(k) \oplus (k \oplus 1)=1$，只需要连一条边 $(1+n,2+n)$ 即可。

- $n \mid 2$

先考虑构造 $n-1$ 的结果，再考虑往这棵树上放 $n$ 与 $2n$。

对于 $n \ne 2^k$ 显然有 $n \oplus \operatorname{lowbit}(n)=n - \operatorname{lowbit}(n)$，故我们连接两条边 $(n,\operatorname{lowbit}(n))$ 以及 $(2n,(n - \operatorname{lowbit}(n)) \oplus 1)$ 即可。

如此，$(n,2n)$ 路径上的点的点权为 $\{\operatorname{lowbit}(n),1,(n - \operatorname{lowbit}(n)) \oplus 1\}$，显然三者异或值为 $n$。

如此完成了构造，代码很短不放了。

---

## 作者：Xy_top (赞：1)

简单的构造题。

先考虑无解，当且仅当 $n=\operatorname{lowbit}(n)$，因为比 $n$ 小的数的最高位都没到 $n$ 的最高位，异或起来就不可能到 $n$，此时只有两个 $n$ 就无解了。

考虑将 $x$ 和 $x + 1$ 一起解决，其中 $x$ 为偶数。

有一种显然的办法是：将 $x$ 和 $x+1$ 分别挂在 $1$ 下面，然后再将 $x+n$ 和 $x+n+1$ 分别挂在 $x+1$ 和 $x$ 下面就行了。

然而对于 $n$ 为偶数的情况，$n$ 不能和 $n+1$ 配对。（超了）考虑继续沿用之前的方法，找到两个数 $x$ $y$，把两个 $n$ 分别挂在 $x$ $y$ 下面，但是 $x\oplus y\oplus 1=n$ 时才行。

怎么办呢？首先 $x\oplus y=n\oplus1=n+1$。然后就是找到两个 $x$ $y$ 使得异或和为 $n+1$，如果找 $n$ 和 $1$ 那就是自己和自己连显然不行。此时可以让 $x=\operatorname{lowbit}(n + 1 - \operatorname{lowbit}(n+1))$，$y=n+1-x$。（其实说明白了就是把 $n+1$ 二进制下倒数第二位单独拎出来，剩下的再组成 $y$）

最后考虑 $n+1$ 怎么处理，参考样例的解法，$1\to 2$，$2\to 3$，$3\to n+1$，$n+1\to n+2$，$n+2\to n+3$，剩下的依旧挂在 $1$ 上。

说了这么多，来看一下代码吧：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
int lowbit (int x) {return x & -x;}
signed main () {
	cin >> n;
	if (lowbit (n) == n) {
		cout << "No";
		return 0;
	}
	cout << "Yes" << '\n';
	cout << 1 << ' ' << 2 << '\n';
	cout << 2 << ' ' << 3 << '\n';
	cout << 3 << ' ' << n + 1 << '\n';
	cout << n + 1 << ' ' << n + 2 << '\n';
	cout << n + 2 << ' ' << n + 3 << '\n';
	for (int i = 4; i + 1 <= n; i += 2) {
		cout << i << ' ' << 1 << '\n';
		cout << 1 << ' ' << i + 1 << '\n';
		cout << n + i << ' ' << i + 1 << '\n';
		cout << n + i + 1 << ' ' << i << '\n';
	}
	if (n % 2 == 0) {
		int x = n + 1;
		cout << n << ' ' << lowbit (x - lowbit (x) ) << '\n';
		cout << 2 * n << ' ' << x - lowbit (x - lowbit (x) );
	}
	return 0;
}
```


---

## 作者：GIFBMP (赞：1)

一道少见的自己想出来的构造题，写发题解纪念一下。

首先对于 $n>1$ 且 $n$ 为奇数的情况，我们发现，对于 $2$ 到 $n$ 之间的所有偶数 $x$，有 $x \operatorname{xor} x+1=1$。那么我们对于每一个 $x$，都构造以下的路径：$x+n\rightarrow x+1+n\rightarrow1\rightarrow x\rightarrow x+1$，即可满足题意。至于 $n+1$，它可以接在任意一个 $x+1$ 下方。

对于 $n$ 为偶数的情况，记 $k$ 为满足 $2^k\le n$ 的最大的 $k$。显然若 $2^k=n$，则无解。因为此时其它任意两个数都无法通过异或得到 $n$。

于是我们记 $a=2^k$，$b=n-a$，容易看出它们都是偶数，且 $a\operatorname{xor} b=n$。但我们发现，在我们刚才构造出的树上，权值为 $a$ 和 $b$ 的节点中间还隔了一个节点 $1$，这时应该怎么办呢？这又要用到上面提到的性质了，由于 $b+1\operatorname{xor} b=1$，我们可以构造出一条 $n\rightarrow a\rightarrow 1\rightarrow b+n+1\rightarrow n\times2$ 的路径，这样问题就解决了。

Code:

```cpp
#include <cstdio>
using namespace std ;
int n , x ;
bool flag ;
int main () {
	scanf ("%d" , &n) ; x = n ;
	for (; x % 2 == 0 ; x >>= 1) ;
	if (x == 1) return !printf ("No") ;
	puts ("Yes") ;
	if (n % 2 == 0) flag = 1 ;
	for (int i = 2 ; i <= n - flag ; i += 2)
		printf ("1 %d\n%d %d\n1 %d\n%d %d\n" , i , i , i + 1 , i + n + 1 , i + n , i + n + 1) ;
	printf ("%d %d\n" , n + 1 , 3) ;
	if (flag) {
		int x1 = 1 , x2 ;
		for (; x1 <= n ; x1 <<= 1) ;
		x1 >>= 1 ; x2 = n - x1 ;
		//printf ("*%d %d\n" , x1 , x2) ;
		printf ("%d %d\n%d %d\n" , x1 , n , x2 + 1 + n , 2 * n) ;
	}
	return 0 ;
}
```

---

## 作者：SpeMars (赞：1)

先判无解，显然，当这个数为 $2$ 的非负整数
幂时无解

证明：这个点最高位只能由自己异或得到，其他点不存在最高位的 $1$。

这一题要用到一个有用的性质：

当 $a$ 为偶数时： $a\oplus 1= a+1$

当 $a$ 为奇数时： $a\oplus 1= a-1$ 

我们考虑利用根节点 $1$ 来进行构造。

令 $ p(x) $ 表示 $ x+n $ (权值相等的对应点)。

我们想办法在 $x$ 和 $p(x)$ 间构造出一个 $x$ 。

令 $x$ 为偶数 , 则 $x+1$ 为奇数， $x\oplus 1= x+1$ ,那么 $(x+1)$ 就构造出来了。

那么 $x$ 就可以由 $(x+1)\oplus 1= x$ 构造出来。

所以一对 $x$ , $x+1$ 就可以交叉放在树上， 两个点的对应点 $p(x)$ , $p(x+1)$ 也交叉放在树上。

且某一端与 $1$ 相连。

那么 $p(1)$ 直接随便连在某一条链的最后即可。

但是 $n$ 为偶数的情况会多出 $n$ 和 $p(n)$ 。

我们把 $n$ 拆成 $\operatorname{lowbit}(n)$ 和 $n-\operatorname{lowbit}(n)$

那么这两个数异或起来就能得到 $n$ 了，但是由于要经过 $1$ 所以我们拆成:

$n=(\operatorname{lowbit}(n)+1) \oplus 1 \oplus(n-\operatorname{lowbit}(n))$

那么找到 $p(\operatorname{lowbit}(n)+1))$ 和 $n-\operatorname{lowbit}(n)$ 这两个点即可。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n;
int lowbit(int x){return (x&(-x));}
int p(int i){return (i+n);}
signed main(){
	scanf("%d",&n);
	if(n==lowbit(n)){
		puts("No");
		return (0^0);
	}
	puts("Yes");
	for(int i=2;i<=n-1;i+=2){
		printf("%d %d\n",1,i);
		printf("%d %d\n",1,p(i+1));
		printf("%d %d\n",i,i+1);
		printf("%d %d\n",p(i+1),p(i));
	}
	printf("%d %d\n",3,p(1));
	if(!(n&1)){
		printf("%d %d\n",p(lowbit(n)+1),n);
		printf("%d %d\n",(n-lowbit(n)),p(n));
	}
	return (0^0);
}
```


---

## 作者：xht (赞：1)

## [Skolem XOR Tree](https://atcoder.jp/contests/agc035/tasks/agc035_c)

### 题意

- 构造一棵 $2n$ 个点的树，满足：
  - 对于 $i \in [1,n]$，将 $i$ 和 $i+n$ 的点权设为 $i$。
  - $i$ 与 $i+n$ 在树上的路径上经过的所有点的点权异或和为 $i$。
- $n \le 10^5$。

### 题解

若 $n$ 为 $2^i$ 则无解。

否则，若 $n$ 为奇数，则对于 $i$ 为偶数，连边 $(i,i+1),(i+1,n+1),(n+1,i+n),(i+n,i+1+n)$，最后连边 $(1,2)$。

若 $n$ 为偶数，在上面的图的基础上挂上 $n$ 和 $2n$ 即可，随便构造。

### 代码

```cpp
int main() {
	int n;
	rd(n);
	if (n - (n & -n) == 0) return prints("No"), 0;
	prints("Yes");
	print(1, 2);
	for (int i = 2; i < n - !(n & 1); i += 2)
		print(i, i + 1), print(i + 1, n + 1), print(n + 1, i + n), print(i + n, i + 1 + n);
	if (!(n & 1)) {
		int x = n & -n, y = n - x;
		print(n, x + 1), print(n * 2, y + n);
	}
	return 0;
}
```

---

## 作者：cosf (赞：0)

竟然是紫题。

简化表达，把题目当成一棵树里有 $2n$ 个点，编号为 $1$ 到 $n$ 的各两个。

首先，我们先看看什么时候无解。如果 $n = 2^k$，那么，从 $1$ 到 $n - 1$ 当中都没有第 $k$ 位为 $1$ 的数，那么两个 $n$ 之间的路径异或和的第 $k$ 位一定不为 $1$，因此无解。

对于其他情况，我们可以给出一个答案。

$n=3$ 时输出（$1 - 2 - 3 - 1 - 2 - 3$），其他情况，可以通过往该方案添加点边的方式解决。

当 $n$ 是奇数的时候，令 $n = 2m + 1$，则显然有 $2m + 1 = 2m \oplus 1, 2m = (2m + 1) \oplus 1$，因此，我们向中间的那个 $1$ 连两条链：$1 - 2m - (2m + 1), 1 - (2m + 1) - 2m$。

当 $n$ 是偶数的时候，令 $n = 2m$，先构造一个 $n' = 2m - 1$ 的解。此时注意到 $n \oplus 1 = \text{lowbit}(n) \oplus (n - \text{lowbit}(n) + 1)$，因此，两个 $n$ 分别连接到 $\text{lowbit}(n)$ 和 $n - \text{lowbit}(n) + 1$ 即可，这样就形成了链 $n - \text{lowbit}(n) - 1 - (n - \text{lowbit}(n) + 1) - n$，符合要求。

代码也非常好写。

```cpp
#include <iostream>
using namespace std;

#define popcount __builtin_popcount
#define lowbit(x) ((x) & -(x))

int main()
{
    int n;
    cin >> n;
    if (popcount(n) == 1)
    {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes\n";
    cout << "1 2\n";
    cout << "2 3\n";
    cout << "1 " << 3 + n << '\n';
    cout << 3 + n << ' ' << 2 + n << '\n';
    cout << 2 + n << ' ' << 1 + n << '\n';
    for (int i = 4; i < n; i += 2)
    {
        cout << "1 " << i << '\n';
        cout << i << ' ' << i + 1 << '\n';
        cout << "1 " << i + n + 1 << '\n';
        cout << i + n + 1 << ' ' << i + n << '\n';
    }
    if (n % 2 == 0)
    {
        cout << n << ' ' << lowbit(n) << '\n';
        cout << n + n << ' ' << n - lowbit(n) + 1 + n << '\n';
    }
    cout.flush();
    return 0;
}

```

---

## 作者：Corzica (赞：0)

显然， $n$ 是 $2$ 的幂次时无解（没有数可以形成 $n$）。

注意到一个比较好的性质：对于任意自然数 $k$，有 $4k\oplus(4k+1)\oplus(4k+2)\oplus(4k+3)=0$。

而当 $\oplus_{i=1}^n i=0$ 时，我们可以把 $1$ 到 $n$ 串起来两次来构造一个可行的解，这时 $n+1 \equiv0\pmod 4$。

现在考虑 $n+1 \not\equiv0\pmod 4$ 的情况。

如果 $n+1\equiv 1 \pmod 4$，可以把 $n$ 作二进制分解，然后在串的过程中让这些二进制位靠在一起，然后把两个 $n$ 分别串在第一个二进制位上和最后一个二进制位上。

如果 $n+1\equiv 2 \pmod 4$，注意到 $n \oplus (n-1) \oplus 1=0$，可以把 $n,n+1,1$ 串在一起。

如果 $n+1\equiv 3 \pmod 4$，可以对 $n$ 做余 $1$ 的操作，对 $n-1,n-2$ 做余 $2$ 的操作。

还要记得特判一下 $n-3$ 是 $2$ 的幂次且 $n+1\equiv 3 \pmod 4$ 的情况，此时无法进行拆分，直接连到 $2$ 就行。

然后就做完了。

感觉，不如按 $2$ 分组，只能说水平还是太低下了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, vis[100005], cnt, ins[100005];
vector<int> v;
inline void fac() {
	for (int i = 1; i <= (n + 1) / 4 * 4 - 1; i *= 2) {
		if (n & i) {
			v.push_back(i);
			ins[i] = 1;
		}
	}
	cnt = v.size() - 1;
	for (int i = 1; i <= (n + 1) / 4 * 4 - 1; i++) {
		if (!ins[i]) v.push_back(i);
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	if ((n & -n) == n) {
		cout << "No";
		return 0;
	}
	cout << "Yes\n";
	if ((n + 1) % 4 == 3 && ((n - 2) & (2 - n)) == (n - 2)) {
		for (int i = 1; i < (n + 1) / 4 * 4 - 1; i++) {
			cout << i << " " << i + 1 << "\n";
		}
		cout << (n + 1) / 4 * 4 - 1 << " " << n + 1 << "\n";
		for (int i = 1; i < (n + 1) / 4 * 4 - 1; i++) {
			cout << n + i << " " << n + i + 1 << "\n";
		}
		cout << 1 << " " << n - 2 << "\n";
		cout << n - 2 << " " << n - 1 << "\n";
		cout << 1 << " " << 2 * n - 1 << "\n";
		cout << 2 * n - 1 << " " << 2 * n - 2 << "\n";
		cout << n << " " << 2 * n - 1 << "\n";
		cout << n * 2 << " " << 2 << "\n";
		return 0;
	}
	fac();
	for (int i = 0; i < v.size() - 1; i++) {
		cout << v[i] << " " << v[i + 1] << "\n";
	}
	cout << v[v.size() - 1] << " " << v[0] + n << "\n";
	for (int i = 0; i < v.size() - 1; i++) {
		cout << v[i] + n << " " << v[i + 1] + n << "\n";
	}
	if ((n + 1) % 4 == 1) {
		cout << n << ' ' << v[0] << "\n";
		cout << 2 * n << " " << v[cnt] << "\n";
	} else if ((n + 1) % 4 == 2) {
		cout << 1 << " " << n << "\n";
		cout << n << ' ' << n - 1 << "\n";
		cout << 1 << ' ' << 2 * n - 1 << "\n";
		cout << 2 * n - 1 << " " << 2 * n << "\n";
	} else if ((n + 1) % 4 == 3) {
		cout << n << " " << v[0] << "\n";
		cout << 2 * n << " " << v[cnt] << "\n";
		cout << 1 << " " << n - 1 << "\n";
		cout << n - 1 << ' ' << n - 2 << "\n";
		cout << 1 << ' ' << 2 * n - 2 << "\n";
		cout << 2 * n - 2 << " " << 2 * n - 1 << "\n";
	}
}
```

---

## 作者：Eznibuil (赞：0)

展现思路过程。$\oplus$ 是异或。

从样例入手，样例说可以 $1-2-3-1-2-3$。

使用惊人的注意力脑补出 $(1-)x-x\oplus1-1-x-x\oplus1$。给 $1$ 加括号的意思是只有两个 $1$，所以围绕中间的 $1$ 可以形成大量的 $x-x\oplus1-1-x-x\oplus1$ 的结构，最后再把一个 $1$ 随便挂在一个末端即可。

于是现在已经解决了 $n$ 是奇数的情况（$n=1$ 肯定无解，样例都告诉你了）。

考虑 $n$ 是偶数，再次使用惊人的注意力注意到如果 $n=x\oplus y$，则可以构造 $n-x\oplus1-1-y-n$，所以补在 $n-1$ 的答案上即可。因此，如果 $n$ 拆不成两个更小的数的异或就是无解的，也就是 $n$ 是 $2$ 的幂时无解。

时间复杂度 $O(n)$。
```c
#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	if(!(n&n-1))
		return printf("No"),0;
	printf("Yes\n%d 2",n+1);
	for(int i=2;i<n;i+=2)
		printf("\n%d %d\n%d 1\n1 %d\n%d %d",i,i+1,i+1,n+i,n+i,n+i+1);
	if(!(n&1))
		printf("\n%d %d\n%d %d",n,n&n-1^1,n+(n&-n),n<<1);
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

首先可以先手推几个小的，发现 $n$ 等于 $3$ 的时候可以用 $1\to2\to3\to1\to2\to3$。

注意看这里的 $2\to3\to1\to2\to3$，来说一下怎么把这个拓展到 $n$ 的范围，因为 $2i\oplus(2i+1)=1$ 所以假如是 $n$ 是奇数的情况就可以用同样的方式来做，$n$ 是偶数的情况会剩下一个 $n$ 看这个 $1$，周围链接他的点是 $2$ 到 $n-1$。

然后就一定可以找出来两个数，异或起来是 $n$ 了，吗？

发现如果 $n$ 是 $2^k$ 次方时一定不可能被异或出来，这时候就是无解，这下是构造出来了。

这里因为随便找一个能异或出来的就行，就找 $\operatorname{lowbit}$ 就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
void link(int x, int y) {
    cout << x << " " << y << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if ((n & (n - 1)) == 0) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for (int i = 2; i <= n - 1; i += 2) {
        link(1, i);
        link(1, i + n + 1);
        link(i, i + 1);
        link(i + n, i + n + 1);
    }
    link(n + 1, 3);
    if (n % 2 == 0) {
        link((n & -n) + 1 + n, n);
        link(n * 2, n ^ (n & -n));
    }
    return 0;
}
```

---

## 作者：ZigZagKmp (赞：0)

本文同步于我的 [cnblog](https://www.cnblogs.com/ZigZagKmp/p/14383310.html)

## 题意简述
构造一棵 $2n$ 个点的树，第 $i$ 个点和第 $i+n$ 个点的权值都是 $i$ ，并且第 $i$ 个点到第 $i+n$ 个点的路径上点的权值异或和为 $i$。

$1\le n\le 10^5$。

## 算法分析
首先这题无解很好判断，如果 $n=2^k,k\in N$，则 $n$ 和 $2n$ 之间没没有点能把最高位异或掉，因此路径一定非法，一定无解。

下面考虑对其余情况进行构造。

样例给了一个 $n=3$ 的构造，其结构比较简单（1-2-3-1-2-3），我们考虑以此为基础构造。

因为利用(1-2-3-1-2-3)我们可以构造出后两位的任意情况，所以考虑按模4剩余类分类讨论。

1. $n=4k+3$
如下图构造即可：
![](https://img2020.cnblogs.com/blog/1794715/202102/1794715-20210206221416029-745787909.png)

由上图我们不难发现因为彼此独立，我们现在的构造也能处理 $n=4k+2,n=4k+1$ 的情况，下面不再讨论。

2. $n=4k$
其实主要就是考虑最后一个点怎么放。

如果 $n=4$ 显然无解。

否则找 $n$ 的 `lowbit`（记为 $t$ ），在`1'`的上面找到对应节点 $x_1$ 满足 $x_1\ \mathrm{xor}\  1=t$ ，在`1'`的下面找对应节点 $x_2$ 满足 $x_2\ \mathrm{xor}\  t=n$。将 $n,n'$ 分别和 $x_1,x_2$ 连边即可。可以证明 $x_1,x_2<n$，因此一定存在节点。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
signed main(){
	read(n);
	if((n&(-n))==n)puts("No");//n=2^k无解
	else{
		puts("Yes");
		printf("%d %d\n",1,2);
		printf("%d %d\n",2,3);
		printf("%d %d\n",3,n+1);
		printf("%d %d\n",n+1,n+2);
		printf("%d %d\n",n+2,n+3);//构造好3的基础
		int mdl=n%4;
		for(int i=4;i<=n-4;i+=4){//每4个一组，按第一类连边
			printf("%d %d\n",i,i+1);
			printf("%d %d\n",i+2,i+1);
			printf("%d %d\n",i+3,i+1);
			printf("%d %d\n",i+1,n+1);
			printf("%d %d\n",n+1,i+n);
			printf("%d %d\n",i+n,i+n+1);
			printf("%d %d\n",n+2,n+i+2);
			printf("%d %d\n",3,n+i+3);
		}
		if(mdl==0){//第二种情况
			int tt=(n&(-n));
			int tmp=(n^tt);
			printf("%d %d\n",n,tt|1);
			printf("%d %d\n",2*n,tmp+n);
		}
		if(mdl==1){//第一种情况 n=4k+1
			int i=n-1;
			printf("%d %d\n",i,i+1);
			printf("%d %d\n",i+1,n+1);
			printf("%d %d\n",i+n,i+n+1);
			printf("%d %d\n",n+1,i+n);
		}
		if(mdl==2){//第一种情况 n=4k+2
			int i=n-2;
			printf("%d %d\n",i,i+1);
			printf("%d %d\n",i+2,i+1);
			printf("%d %d\n",i+1,n+1);
			printf("%d %d\n",i+n,i+n+1);
			printf("%d %d\n",n+1,i+n);
			printf("%d %d\n",n+2,n+i+2);
		}
		if(n>3&&mdl==3){//第一种情况 n=4k+3
			int i=n-3;
			printf("%d %d\n",i,i+1);
			printf("%d %d\n",i+2,i+1);
			printf("%d %d\n",i+3,i+1);
			printf("%d %d\n",i+1,n+1);
			printf("%d %d\n",i+n,i+n+1);
			printf("%d %d\n",n+1,i+n);
			printf("%d %d\n",n+2,n+i+2);
			printf("%d %d\n",3,n+i+3);
		}
	}
	return 0;
}
```


---

## 作者：yyxmy (赞：0)

首先考虑在什么情况下会无解， 显然当$n$为$2$的整数次幂的条件下会无解，因为二进制最高位上没有数和它相同。

现在我们考虑异或的一个性质， 那就是当$i$为偶数时, $i$异或$i+1$ = 1， 那么只用分别把$i$和$i+1$与1连一下即可， 那$1$与谁配呢， 我们发现$1,2,3$的异或和为$0$， 于是可以先把$1,2,3$的构造出来，然后把$i$和$i+1$配对, 那么现在有个问题， 就是当$n$为偶数的时候会单出来一个。 一定可以找到小于n的$x$和$y$, 使$1$异或$x$异或$y$ = 0, 把$x$和$y$找到就行了。
```cpp
#include <bits/stdc++.h>
using namespace std;
int k, a[111], d[100001], n;
int main() {
	for(int i = 1; i <= 100000; i <<= 1) d[i] = 1;
	cin >> n; 
	if(d[n]) {printf("No\n"); return 0;} 
	printf("Yes\n");
	printf("1 2\n2 3\n3 %d\n%d %d\n%d %d\n", n + 1, n + 1, n + 2, n + 2, n + 3);
	for(int i = 4; i < n; i += 2){
		printf("%d %d\n", i, 1 + n); printf("%d %d\n", i + 1, 1 + n);
		printf("%d %d\n", i + n, i + 1); printf("%d %d\n", i + n + 1, i);
	}
	if(n % 2 == 0){
		for(int i = 2; i <= n; i++){
			int p = i ^ 1 ^ n;
			if(p < n && p > 1) {
				if(i == 2) printf("%d %d\n", i + n, n);
				else printf("%d %d\n", i, n);
				printf("%d %d\n", p, n + n);
				return 0;
			}
		}
	}
}

```


---

