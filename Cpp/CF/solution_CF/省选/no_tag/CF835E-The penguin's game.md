# The penguin's game

## 题目描述

Pay attention: this problem is interactive.

Penguin Xoriy came up with a new game recently. He has $ n $ icicles numbered from $ 1 $ to $ n $ . Each icicle has a temperature — an integer from $ 1 $ to $ 10^{9} $ . Exactly two of these icicles are special: their temperature is $ y $ , while a temperature of all the others is $ x≠y $ . You have to find those special icicles. You can choose a non-empty subset of icicles and ask the penguin what is the bitwise exclusive OR (XOR) of the temperatures of the icicles in this subset. Note that you can't ask more than 19 questions.

You are to find the special icicles.

## 说明/提示

The answer for the first question is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF835E/3579feff85b3a33a65d7529a532f9fbb51cc40c4.png).

The answer for the second and the third questions is 1, therefore, special icicles are indexes 1 and 3.

You can read more about bitwise XOR operation here: [https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 样例 #1

### 输入

```
4 2 1
2
1
1```

### 输出

```
? 3 1 2 3
? 1 1
? 1 3
! 1 3```

# 题解

## 作者：xzggzh1 (赞：10)

我来讲讲怎么想出这题而不只是怎么解出这题。

题意：

有一个序列，其中有恰好 $2$ 个数是 $y$ ，剩下的 $n-2$ 个数是 $x$ 。

你每次可以询问一个集合的异或和。

你需要用不超过 $19$ 次询问找到两个为 $y$ 的数的下标。其中 $n\leq 1000$ 。

---

要素察觉：$\log$ 、异或、交互、找 $2$ 个。

看到这里就应该可以想到这个著名的定理（误。

> 两个不同的数的二进制不完全相同。

这个套路有些常见，解法就是对于每个二进制询问这位上是 $1$ 的位置的集合，那么必然有一次问到的集合中只包含其中一个。

上面是看到题后直觉的内容，下面讲思考的内容。

可以发现询问操作的具体作用：可以问得一个区间里面有偶数个 $y$ 还是 奇数个 $y$ （实现也非常简单，假设偶数个 $y$ 然后看输入是否和假设之后的值一样即可）。

套路化的，先查询一遍每个二进制为 $1$ 的位置的集合（消耗次数 $10$ ）， 然后可以得出以下内容。

$y1$ 和 $y2 $ 在每个位置上是否相同。（设 $y1,y2$ 为这两个 $y$ 的位置）。

我们只要问出 $y1$,$y2$ 中的一个即可得到全部答案。

这就要用到刚才那个著名的~~定理~~了，先随便取一个位 $base$，在这个位上，$y1$ 和 $y2$ 不相同。那么如果询问的集合中的 $base $ 位都是同一个值，那么这个集合中至多有 $1$ 个 $y$ 。

根据这个，那么就好处理了。先钦定 $y1$ 的 $base$ 位是 $1$ （这样可以减少一次询问）。对于每一位 $x(x\not = base)$ ， 都查询 $x$ 和 $base $ 位都是 $1$ 的位置的集合,可以得出 $y1$ 在这个位置上是否是 $1$ 就可以完整求出其中一个了，题目得解。

---

下面是核心代码：

```cpp
const int Maxm=10;
int n,m,x,y,base,a[Maxm],odd[Maxm];//odd=1 ->奇数个
int ask(int G)
{
    int res,qaq=0;
    vector<int>out;
    for(int i=1;i<=n;i++)
    if((i&G)==G)out.push_back(i);if(!out.size()) return 0;
    printf("? %d ",out.size());
    for(int i=0;i<out.size();i++)
    printf("%d ",out[i]);puts("");
    fflush(stdout);res=R();
    if(out.size()%2) qaq=x;
    if(res==qaq) return 0;
    else return 1;//表示有奇数个y
}
int main()
{
    n=R();x=R();y=R();int res;
    for(int i=0;(1<<i)<=n;i++)
    if(odd[i]=ask(1<<i))base=i;
    for(int i=0;(1<<i)<=n;i++)
    {
        if(i==base) continue;
        if(odd[i]==0){if(ask((1<<base)+(1<<i))==1)a[i]=1; }
		else if(ask((1<<base)+(1<<i))==1) a[i]=1;
	}
    int ans1=0,ans2=0;a[base]=1;
    for(int i=0;(1<<i)<=n;i++)
    {
        ans1+=a[i]*(1<<i);
        ans2+=(odd[i]?1-a[i]:a[i])*(1<<i);
    }
    if(ans1>ans2) swap(ans1,ans2);
    printf("! %d %d\n",ans1,ans2);
}

```






---

## 作者：yzy1 (赞：7)

## 声明

博客编辑页和管理员题解审核页使用的 $\KaTeX$ 版本较低，不支持 `\def` 指令，可能会导致本题解中的部分公式渲染异常．而在题目对应的题解展示页面和个人博客渲染页面使用的 $\KaTeX$ 为高版本，则无此问题．

## 题目大意

交互题，有一个长度为 $n$ 的序列，其中有恰好两个 $y$，剩下 $n-2$ 个为 $x$．其中 $n,x,y$ 给定．每次可以询问一个集合的异或和，你需要用不超过 $19$ 次询问找到两个 $y$ 的下标．$1 \le n \le 10^3$，$1 \le x,y \le 10^9$．

## 简要做法

首先考虑如何利用题目给你的询问操作．我们可以发现在 $x,y$ 均为常量的情况下，询问得到的回答只和询问集合大小的奇偶性和包含 $y$ 个数的奇偶性有关，具体关系如下：

$$
\def{\arraystretch}{1.5}
\begin{array}{|c|c|c|}
\hline
\textsf{集合大小奇偶性} & \textsf{包含 $y$ 个数奇偶性} & \textsf{答案} \\
\hline
\textsf{奇} & \textsf{奇} & y \\
\hline
\textsf{奇} & \textsf{偶} & x \\
\hline
\textsf{偶} & \textsf{奇} & x \oplus y \\
\hline
\textsf{偶} & \textsf{偶} & 0 \\
\hline
\end{array}
$$

则询问操作转化为：每次询问所选集合 $y$ 的个数的奇偶性．

考虑一个很简单的做法，对序列中元素进行二进制拆位分组，共分 $\lceil \log_2 n \rceil$ 组，每组的一对集合按照二进制第 $i$ 位分类．则可以证明，至少存在一组使得两个 $y$ 恰好在一对集合中分开．然后分别对两个集合进行二分查找．即可找到两个 $y$ 的下标．显然这种方式需要花费的次数为最多 $\lceil \log_2 n \rceil + \lceil \log_2 \lfloor \frac n 2 \rfloor \rceil + \lceil \log_2 \lceil \frac n 2 \rceil \rceil$ 次．无法通过本题．

更进一步地，我们来分析二进制拆位的本质．当我们询问以第 $i$ 位为依据拆出来的一对集合中的一个时，若得到的回答是包含奇数个 $y$，则表示两个 $y$ 的下标的二进制表示中第 $i$ 位取不同的值，否则代表这一位取相同的值．换句话说，我们可以在得到任意一个将两个 $y$ 分开的集合对的同时得到两个 $y$ 的下标的异或值．由于异或的逆运算还是异或，由此可以得出一个做法：当得到第一个 $y$ 的下时，无需再对第二个 $y$ 所在的集合进行二分查找，可以直接利用异或值与第一个 $y$ 的下标计算．这种方式需要花费的次数为最多 $\lceil \log_2 n \rceil + \lceil \log_2 \lfloor \frac n 2 \rfloor \rceil$ 次．可以通过本题．

## 代码参考

见 [原始 OJ 提交](https://codeforces.com/contest/835/submission/206714290)．


---

## 作者：MspAInt (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF835E)

第一次做交互题是讲师教的/hanx

设两个答案分别为 $y_1,y_2$。

因为 xor 操作的自反性，每次询问得到的其实是 $y$ 在该集合中出现次数的奇偶性。

一看这个 $19$ 次询问就很 $\log$，于是一个显然的做法横空出世：对于每一个下标 $i$，如果其二进制第 $j$ 位为 $1$，就把它丢进 $p_j$（一个动态数组）里。显然一定存在若干个 $j$ 使得 $y_1,y_2$ 其中一个出现在 $p_j$ 里（即出现了奇数次）。我们找到这两个 $y$ 分别出现的两个数组，然后借着询问把它们二分出来。

然而这样询问数已经接近 $30$ 了，考虑更优的做法。

如果在某一个 $p_j$ 里只有 $y_1$ 的下标存在，则 $2^j$ 对 $y1 \operatorname{xor}y2=Y$ 是有贡献的。那么我们只要在分组时求出 $Y$，然后二分 $y1$ 即可求出 $y2=y1\operatorname{xor}Y$。

显然这样只要询问两个 $\log$ 次，可以通过。

[record](https://vjudge.net/solution/45140285/TghpN5S3X3LnCjix2VZ1)

---

## 作者：cyffff (赞：3)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF835E)
## 题意
$n$ 个数，每个数有编号，有且仅有两个数为 $b$，其余为 $a$。每次询问你可以取出一些数，交互库会告诉你这些数的异或和。

你需要用不超过 $19$ 次询问求出这两个为 $b$ 的数的编号。

$n\le1000$。
## 思路
和 P8849 很像。考虑转化。

设答案编号为 $x,y$。

我们想通过询问求出 $x,y$ 是否同时在或者不在我们询问的集合里。

考虑询问集合大小，如果它为奇数，当回答为 $a$ 时 $x,y$ 同时在或者不在我们询问的集合，反之则一个在我们询问的集合中，另一个不在。同理，集合大小为偶数时也是相似的，当回答为 $a$ 时 $0$ 同时在或者不在我们询问的集合，反之则一个在我们询问的集合中，另一个不在。

考虑对于每一位 $i$，将编号第 $i$ 位为 $0$ 的放到 $S_0$，其余放到 $S_1$，查询 $S_0$，可以得到 $x,y$ 这一位是否相同。换个说法，我们通过 $\log n$ 次询问得到了 $x\text{ xor }y$。

指定一位 $w$，$x,y$ 在第 $w$ 位不同，不妨指定 $x$ 第 $w$ 位为 $1$。对于每一位 $i\ne w$，把编号第 $i$ 位为 $1$ 且第 $w$ 位为 $1$ 的放到 $S_0$，其余放到 $S_1$，查询 $S_0$。通过这次询问，我们可以求出 $x$ 这一位是否为 $1$，回答为 $0$ 时，$x$ 在 $S_1$ 中，说明其第 $i$ 位为 $0$，反之同理。这里有 $\log n-1$ 次询问。

综上，我们通过 $2\log n-1$ 次询问求出了 $x$ 和 $x\text{ xor }y$，输出时要注意 $x<y$。

时间复杂度 $O(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e3+10;
int a,b;
inline int query(vector<int>qry){
	printf("? %d ",qry.size());
	for(auto k:qry)
		printf("%d ",k);
	puts("");
	fflush(stdout);
	int x;
	scanf("%d",&x);
	if(qry.size()%2){
		if(x==a) return 0;
		return 1;
	}else{
		if(x==0) return 0;
		return 1;
	}
}
int T;
int main(){
	T=1;
	while(T--){
		int n,xt=0,p,x=0;
		scanf("%d %d %d",&n,&a,&b);
		for(int i=0;(1<<i)<=n;i++){
			vector<int>a;
			a.clear();
			for(int j=1;j<=n;j++)
				if(j&(1<<i))
					a.push_back(j);
			if(!a.size()||a.size()==n) continue;
			int tmp=query(a);
			if(tmp) xt|=1<<i,p=i;
		}
		x|=1<<p;
		for(int i=0;(1<<i)<=n;i++){
			if(i==p) continue;
			vector<int>a;
			a.clear();
			for(int j=1;j<=n;j++)
				if((j&(1<<i))&&(j&(1<<p)))
					a.push_back(j);
			int tmp;
			if(!a.size()||a.size()==n) tmp=0;
			else tmp=query(a);
			x|=tmp<<i;
		}
		if((xt^x)<x) x=xt^x;
		printf("! %d %d\n",x,xt^x);
		fflush(stdout);
	}
	flush();
}
```
再见 qwq~

---

## 作者：xcrr (赞：3)

好题好题

看到 19，不禁想到询问次数可能是 $2\cdot \log$。

假设那两个冰柱分别是 $Y_1,Y_2$，其余冰柱是 $X$。

于是我一眼想二分。然而因为两个 $Y$ 都在原集合里，没办法做。如果只有一个 $Y$ 在集合里就好办了。

于是想怎么把两个 $Y$ 拆到两个集合。考虑经典的 $\log$ 复杂度内拆集合，使得任意两个数都至少有一次在不同集合的方法：每次对二进制每一位拆，这位为 1 去左边集合，0 去右边集合。

而且我们可以判断一个集合内是否有奇数个 $Y$，即异或值为 $y$（集合大小为奇数）或者 $x+y$（集合大小为偶数）。

初步做法出来了，$\log$ 次拆集合，每次询问其中一个，如果有奇数个 $Y$，那么就拆分成功了。

这时候可以在集合内二分了。但是如果给两个集合都做二分，总共询问是 $3\cdot \log$ 次。考虑只给一个集合二分，求出 $Y_1$。因为前面拆集合的操作可以确定 $Y_1$ 和 $Y_2$ 在每位上是否相同，合在一起可以确定 $Y_1 \oplus Y_2$，所以我们可以求出 $Y_2$。

没有细节，上代码。

```cpp
//沉着冷静
int n,x,y;
int fd(vector<int>t)
{
	int sz=t.size();
	vector<int>now;
	now.push_back(-1);
	for(auto c:t)now.push_back(c);
	int sum=0;
	for(int i=(1<<9);i;i>>=1)
	{
		if(sum+i>sz)continue;
		cout<<"? "<<sum+i<<' ';
		for(int j=1;j<=sum+i;j++)
		cout<<now[j]<<' ';
		cout<<endl;
		fflush(stdout);
		int p;
		cin>>p;
		if((((sum+i)&1)&&p==y)||(!((sum+i)&1)&&p==(x^y)));
		else sum+=i;
	}
	return now[sum+1];
}
inline void solve(){
	cin>>n>>x>>y;
	int w=0,a=-1;
	vector<int>st;
	for(int i=0;i<=9;i++)
	{
		st.clear();
		for(int j=1;j<=n;j++)
		if((j>>i)&1)st.push_back(j);
		if(!st.size())continue;
		cout<<"? "<<st.size()<<' ';
		for(auto c:st)cout<<c<<' ';
		cout<<endl;
		fflush(stdout);
		int p;
		cin>>p;
		if(((st.size()&1)&&p==y)||(!(st.size()&1)&&p==(x^y)))
		{
			if(a==-1)a=fd(st);
			w^=(1<<i);
		}
	}
	int b=a^w;
	if(a>b)swap(a,b);
	cout<<"! "<<a<<' '<<b<<endl;
	fflush(stdout);
}

```

---

## 作者：ykzzldz (赞：2)

经典套路：二进制分组。

首先，先对于编号二进制下每一位为 $1$ 的集合依次询问，花费次数 $10$，此时我们可以知道两个 $y$ 的编号二进制下每一位是否相同。

于是，我们只需要在剩下 $9$ 次询问中确定一个 $y$ 的值即可。我们找到一个位置 $p$，这一位上，两个 $y$ 的值不同，那么可以直接钦定这一位为 $1$，容易想到，这一定是合法的，且这样可以节省一次询问。

考虑下面一个例子，两个 $y$ 二进制编号分别为：
```
01001
11010
```
首先，我们已经知道了每一位是否相同，且我们钦定一个 $y$ 的第一位为 $1$。我们从第二位开始依次进行询问，每次询问第一位为 $1$，第 $p$ 位为 $1$ 的数的集合。分类讨论：

1. $p$ 位相同：例子中第 $2,3$ 位的情况，若交互库返回 $1$，说明这一位两个都为 $1$，否则都为 $0$。

2. $p$ 位不同：例子中第 $4,5$ 位的情况，若交互库返回 $1$，说明第一位为 $1$ 的那个 $y$ 第 $p$ 位为 $1$，否则为 $0$，另一个相反。

这题就做完了，$n$ 为 $1000$ 时询问次数恰好为 $19$ 次。

---

## 作者：MuelsyseU (赞：1)

一种不需要运用二进制分析、完全从逻辑上推导的解法。但个人认为该做法和二进制相关做法本质相似。

---

显然对于任意询问，答案实际上只有 $x\operatorname{xor}y$、$x$、$y$ 以及 $0$ 两种可能。由于 $y$ 仅有 $2$ 个，因此可能存在于询问集合中的 $x$ 可能有 $s-2,s-1,s$ 个，通过计算即可得知 $y$ 的个数。但会发现 $x\operatorname{xor}x=0$，因此实际上只能得知个数的奇偶性。

考虑一次询问答案为奇数，意味着得到了两个集合，其中各有一个 $y$。则可以在两个集合内分别二分询问左半区间，如果答案仍为 $1$ 意味着该区间一定恰好存在一个 $y$，反之则为另一半恰好存在。此时即可将其中一个 $y$ 的可能范围缩小。这样就可在 $2\lfloor\log n\rfloor$ 次询问内解决。

---

但是查询时很可能出现答案为偶数（$0$ 或 $2$），即 $y$ 可能均在询问集合中，也可能均在其余部分。那么我们同样必须缩小问题的规模来判断，也就是对这两个集合均分为两半，一次性查询所有集合的左半边（即下图的左半部分）。

![](https://cdn.luogu.com.cn/upload/image_hosting/3w77myfk.png)

容易发现这样最多进行 $\lceil\log n\rceil$ 次，就一定会找到一次答案为 $1$ 的询问，即已经将 $y$ 分别划分在两个集合中，总询问次数为 $O(\log n)$

---

但是问题是这样极限次数为 $3\lfloor\log n\rfloor$ 级别，不能通过。容易发现，二分过程中需要 $2$ 次询问来将规模缩小一半，但划分过程却只需要 $1$ 次。因此考虑预先尽可能缩减二分的两个集合大小。

容易发现，我们划分的过程中，每次划分意味着之前的询问答案始终为 $0$，也就是下图中每次询问，红色和蓝色部分只有其中一个存在答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/ss14us9b.png)

容易发现，实际上答案可能所在的区间**长度**不断缩小，最后两个答案一定恰好分别在划分出的一个区间的两半中。

因此，可以对所划分出的各个区间继续二分（上图 $4$ 个红色部分），即这些区间中恰有一个包含 $1$ 个 $y$，直至答案缩减为一个区间。此时，即可在 $1$ 次操作内将问题缩小一半的规模。只剩一个区间后，套用二分做法即可。

不妨设 $n=2^t$，划分过程查询了 $k$ 次，则会划分出 $2^k$ 个长度为 $2^{t - k}$ 的红色区间，最后在两个这样的区间内二分，则总查询次数为 $k+k+2(t-k)=2t=\lfloor\log n\rfloor+\lceil\log n\rceil\le19$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int T, n, x, y, sz, ssz, num, tp, cnt;
const int sx = 6, sy = 9;
pair<int, int> a[2005], b[2];
inline int query() {
	ssz = 0, ++cnt;
	tp = 0;
	for (int i = 0; i < num; ++i) ssz += (a[i].second - a[i].first + 1) / 2;
	printf("? %d ", ssz);
	for (int id = 0; id < num; ++id) {
		sz = a[id].second - a[id].first + 1;
		for (int i = a[id].first; i < a[id].first + sz / 2; ++i) printf("%d ", i), tp ^= (i == sx || i == sy) ? y : x;
	}
	// sz 为奇数：ans = y 即可
	// sz 为偶数：ans = x ^ y 即可
	cout << endl, fflush(stdout), scanf("%d", &tp);
	return (ssz & 1) ? tp == y : tp == (x ^ y);
}
inline int check1(int id, int mid) {
	printf("? %d ", mid), ++cnt;
	tp = 0;
	for (int i = b[id].first; i < b[id].first + mid; ++i) printf("%d ", i), tp ^= (i == sx || i == sy) ? y : x;
	cout << endl, fflush(stdout), scanf("%d", &tp);
	return (mid & 1) ? tp == y : tp == (x ^ y);
}
inline int check(int l, int r) {
	ssz = 0, ++cnt;
	tp = 0;
	for (int i = l; i < r; ++i) ssz += (a[i].second - a[i].first + 1) / 2;
	printf("? %d ", ssz);
	for (int id = l; id < r; ++id) {
		sz = a[id].second - a[id].first + 1;
		for (int i = a[id].first; i < a[id].first + sz / 2; ++i) printf("%d ", i), tp ^= (i == sx || i == sy) ? y : x;
	}
	cout << endl, fflush(stdout), scanf("%d", &tp);
	return (ssz & 1) ? tp == y : tp == (x ^ y);
}
inline int find1(int id) {
	int mid, l = 0, r = b[id].second - b[id].first + 1;
	while (l + 1 < r) {
		mid = (l + r) >> 1;
		if (check1(id, mid)) r = mid;
		else l = mid;
	}
	return b[id].first + l;
}
inline int find(int l, int r) {
	int mid;
	while (l + 1 < r) {
		mid = (l + r) >> 1;
		if (check(l, mid)) r = mid;
		else l = mid;
	}
	return l;
}
signed main() {
	scanf("%d%d%d", &n, &x, &y), num = 1;
	//找到答案为 1 的集合  
	a[0] = make_pair(1, n);
	while (!query()) {
		tp = num;
		for (int i = 0; i < num; ++i) {
			sz = a[i].second - a[i].first + 1;
			a[tp++] = make_pair(a[i].first, a[i].first + sz / 2 - 1), a[i].first += sz / 2;
		}
		num = tp;
	}
	//缩减至 1 个区间 
	for (int i = 0; i < num; ++i)
		if (a[i].first >= a[i].second) a[i] = make_pair(0, 0);
	sort(a, a + num);
	int l = 0;
	while (a[l].first == 0) ++l;
	int t = find(l, num);
	sz = a[t].second - a[t].first + 1;
	b[1] = make_pair(a[t].first, a[t].first + sz / 2 - 1), b[0] = make_pair(a[t].first + sz / 2, a[t].second);
	//二分
	int s0 = find1(0), s1 = find1(1);
	if (s0 > s1) swap(s0, s1);
	printf("! %d %d\n", s0, s1), fflush(stdout); 
	//cout << cnt << endl;
	return 0;
}
```


---

## 作者：Purslane (赞：1)

# Solution

无聊的交互题。

首先考虑给你一个集合 $S$，你能不能判断其中是否有 $y$。我们发现，通过交互库给我们的信息，如果 $S$ 中有 $0$ 或 $2$ 个 $y$，情况是一模一样的。因此，只有 $S$ 有 $1$ 个 $y$ 才能判出来。

那我们的一个想法是，先找到一个只包含一个 $y$ 的 $S$，然后在这上面二分。然后对其补集进行同样的操作。

那么有什么方法可以保证能在比较少的步数内找到一个这样的 $S$ 呢？考虑两个含 $y$ 的位置，必有一个二进制位下二者不同。于是从小到大枚举二进制位，把数按照这一位上是 $0$ 还是 $1$ 进行分组。假设我们在 $t$ 轮后，终于出解了。

那么我们先对 $S$ 和其补集中较小者的进行二分，这样最多用 $9$ 轮就可以出解。那么你发现，我们已经消耗了 $9+t$ 次询问，最多还剩 $10-t$ 次询问，完全不够对另一个集合进行二分啊。

然后考虑实际上你已经知道了另一个位置二进制表示的后 $t$ 位是多少，你只需要确定剩下的前 $10-t$ 位。这些直接逐位确定即可。

PS：事实上我们完全可以不用去写二分。全部从低位往高位逐位确定即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int n,x,y;
int al_x(int sze) {return x*(sze&1);}
int query(vector<int> s) {
	cout<<"? "<<s.size()<<' ';
	for(auto id:s) cout<<id+1<<' ';
	cout<<endl;
	int res; cin>>res;
	return res;	
}
vector<int> operate(int w,vector<int> ori) {
	vector<int> s1,s2;
	for(auto id:ori) if(id&(1<<w)) s1.push_back(id); else s2.push_back(id);
	if(s1.size()&&query(s1)!=al_x(s1.size())) return s1;
	return s2;	
}
int main() {
	cin>>n>>x>>y;
	vector<int> S,T; 
	int pos1=0,pos2=0,flg=-1;
	ffor(i,0,9) {
		vector<int> s1,s2;
		ffor(j,0,n-1) if(j&(1<<i)) s1.push_back(j);
		else s2.push_back(j);
		if(s1.size()&&query(s1)!=al_x(s1.size())) {
			flg=i,S=s1,T=s2; break ;	
		}
	}
	ffor(i,0,9) if(i!=flg) S=operate(i,S);
	pos1=S[0],pos2=(pos1&((1<<flg+1)-1))^(1<<flg);
	vector<int> ano;
	ffor(i,0,n-1) if((i&((1<<flg+1)-1))==pos2) ano.push_back(i);
	ffor(i,flg+1,9) ano=operate(i,ano);
	pos2=ano[0];
	if(pos1>pos2) swap(pos1,pos2);
	cout<<"! "<<pos1+1<<' '<<pos2+1<<endl;
	return 0;
}

```

---

## 作者：zhenjianuo2025 (赞：1)

### Problem

[题目传送门](https://www.luogu.com.cn/problem/CF835E)

交互题。

有一个序列，其中有恰好 $2$ 个数是 $y$，剩下的 $n-2$ 个数是 $x$。

每次可以询问一个集合的异或和。

在不超过 $19$ 次询问中找到两个为 $y$ 的数的下标。

### Solve

考虑集合的异或和对找到 $y$ 有什么帮助。

- 若询问的集合的大小为奇数：
	- 若集合内 $y$ 的个数为奇数，则异或和应等于 $y$；
   - 若集合内 $y$ 的个数为偶数，则异或和应等于 $x$。
- 若询问的集合的大小为偶数：
	- 若集合内 $y$ 的个数为奇数，则异或和应等于 $x⊕y$；
   - 若集合内 $y$ 的个数为偶数，则异或和应等于 $0$。
   
这样，一次询问就可以了解集合内 $y$ 的个数的奇偶性。

枚举所有下标的二进制位，把所有下标分为两个集合：下标的这一位为 $1$ 的和这一位为 $0$ 的。查询该位为 $1$ 的集合，如果集合内 $y$ 的个数为奇数，两个 $y$ 的下标异或值的这一位就必定为 $1$，否则这一位为 $0$。

这样，我们经过最多 $10$ 次询问，得到了两个下标的异或值，也就是确定了一个下标就可以确定另一个。

将所有下标再次分为两个集合，保证两个 $y$ 一定分别在一个集合中。

对其中一个集合二分，求得一个 $y$ 的位置，也就求出了另一个 $y$ 的位置。这一步最多需要 $9$ 次询问。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n, x, y, xr;
bool query(vector<int> g) {
	cout << "? " << g.size() << " ";
	for (register int i = 0; i < g.size(); i++) cout << g[i] << " ";
	cout << endl;
	int res;
	cin >> res;
	if (g.size() & 1) {
		if (res == x) return 0;
		if (res == y) return 1; 
	} else {
		if (res == 0) return 0;
		if (res == x ^ y) return 1;
	}
}
signed main() {
	cin >> n >> x >> y;
	for (register int i = 0; i < 10; i++) {
		vector<int> g; g.clear();
		for (register int j = 1; j <= n; j++) if (j & (1 << i)) g.push_back(j);
		if (g.size() && query(g)) xr |= 1 << i;
	}
	vector<int> g; g.clear();
	for (register int i = 1; i <= n; i++)
		if ((i ^ xr) <= n && (i ^ xr) > i) g.push_back(i);
	int l = 0, r = g.size() - 1;
	while (l < r) {
		const int mid = (l + r) >> 1;
		vector<int> z; z.clear();
		for (register int i = l; i <= mid; i++) z.push_back(g[i]);
		if (query(z)) r = mid;
		else l = mid + 1;
	}
	cout << "! " << min(g[l] ^ xr, g[l]) << " " << max(g[l] ^ xr, g[l]) << endl;
	return 0;
} 
```

---

## 作者：Echoternity (赞：0)

因为考虑到有 $n\leq 1000$ 的话，还明确规定了 $19$ 次，我们可以很容易发现 $2^{10}=1024$，那我们大胆猜测这道题可以在 $2\log_2 n$ 的时间内解决，就往位运算或者二分那个方面想。

对于主题库那道题得到两个集合的异或以及 $\text{CodeForces}$ 上得到一个集合里的异或，实际上求得的都是同一个东西——两个特殊点是否**同时**在你选取的集合中。这是显然的，可以自证。

那么我们考虑二分，查找 $[1,\frac{n}{2}],[1,\frac{n}{2^2}],\cdots,[1,\frac{n}{2^r}]$，这样可以得到其中一个点所在的位置，然后把整个序列划分成两部分分别二分，这样的话，时间复杂度是不会超过 $2\log_2 n$ 的。

具体来讲，是如下操作：

我们钦定一个二进制位 $r$ （从 $n$ 的最高位向下枚举），然后每一次把 $x \operatorname{and} 2^r=1$ 的 $x$ 都提出来组成集合（即二进制位 $r$ 为 $1$ 的所有数），直到找到某一位 $r$ 使得两个特殊点不在同一个集合里，从这一位开始，我们可以二分得到集合答案。

我们先枚举左集合得到第一个特殊点记作 $resf$，也就是二分 $[0,2^r-1]$ 区间，这是左集合的答案，用同样的方法得到右集合答案，二分 $[2^r,2^{r+1}-1]$ 区间，得到第二个特殊点记为 $ress$。

现在我们的情况是，用了 $\mathcal O(\log_2 n)$ 的时间获得了 $resf,ress$ 在 $r$ 位以下的答案，现在考虑向上推进。注意到，我们每一次向上推一位，都会得到两个相同的答案记作 $resf',ress'$，他们与原答案的不同在于 $r+1$ 位的不同，这样的话，我们需要在这两者中判断，这是简单的，直接询问某一个，得到信息，如果是，则当前的 $resf,ress$ 就是答案，否则 $resf+2^{r+1},ress+2^{r+1}$ **可能**是答案，并向 $r+2$ 位推进。

两道题的思路是一样的。

``` c++
// ----- Eternally question-----
// Problem: CF835E The penguin's game
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF835E
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by: Eternity
// Time: 2022-11-13 18:58:47
// ----- Endless solution-------

#include<bits/stdc++.h>
#define re register
typedef long long ll;
template<class T>
inline void read(T &x)
{
	x=0;
	char ch=getchar(),t=0;
	while(ch<'0'||ch>'9') t|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	if(t) x=-x;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1){ read(x),read(x1...); }
template<class T>
inline void write(T x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
template<>
inline void write(bool x){ std::cout<<x; }
template<>
inline void write(char c){ putchar(c); }
template<>
inline void write(char *s){ while(*s!='\0') putchar(*s++); }
template<>
inline void write(const char *s){ while(*s!='\0') putchar(*s++); }
template<class T,class ...T1>
inline void write(T x,T1 ...x1){ write(x),write(x1...); }
template<class T>
inline bool checkMax(T &x,T y){ return x<y?x=y,1:0; }
template<class T>
inline bool checkMin(T &x,T y){ return x>y?x=y,1:0; }
#define int long long
int X,Y,N,Xr;
inline bool query(std::vector<int>Vec)
{
	std::cout<<"? "<<Vec.size()<<" ";
	for(int i:Vec) std::cout<<i<<" ";std::cout<<std::endl;
	int type;std::cin>>type;
	if(Vec.size()&1)
	{
		if(type==X) return 0;
		if(type==Y) return 1;
	}
	else
	{
		if(type==0) return 0;
		if(type==X^Y) return 1;
	}
}
signed main()
{
	std::cin>>N>>X>>Y;
	for(int i=0;i<10;++i)
	{
		std::vector<int>Vec;Vec.clear();
		for(int j=1;j<=N;++j) if(j&(1<<i)) Vec.push_back(j);
		if(Vec.size()&&query(Vec)) Xr|=1<<i;
	}
	std::vector<int>Vec;Vec.clear();
	for(int i=1;i<=N;++i)
		if((i^Xr)<=N&&(i^Xr)>i) Vec.push_back(i);
	int l=0,r=Vec.size()-1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		std::vector<int>V;V.clear();
		for(int i=l;i<=mid;++i) V.push_back(Vec[i]);
		if(query(V)) r=mid;
		else l=mid+1;
	}
	std::cout<<"! "<<std::min(Vec[l]^Xr,Vec[l])<<" "<<std::max(Vec[l]^Xr,Vec[l])<<std::endl;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

有趣。

众所周知，异或运算有自反性：$a\operatorname{xor}a=0$。

那么我们每次 Query 得到的值只可能是：$0$，$x$，$y$，$x\operatorname{xor} y$。  
其中，$y$ 与 $x\operatorname{xor} y$ 表示查询的集合中有奇数个 $y$，（即一个 $y$）。

我们想到，假若我可以确定在某一个集合中有且仅有一个 $y$，那么我可以通过二分的做法在 $\log n$ 的查询次数下找到 $y$。

那如何确定呢？

即考虑在什么时候 $p_1$ 和 $p_2$ 会被分开（即有何不同）。

唯一的条件是，$p_1 \neq p_2$。

那自然想到对下标做二进制分组：我们做 $\log n$ 次分组，第 $i$ 次分组将第 $i$ 位为 $1$ 的下标和 $0$ 的下标分到两边。

这样的话，我们可以在 $\log n$ 实现确定一个集合有且仅有一个 $y$。

但是这样最劣是 $3\log n$ 的，还差一点点。

发现在做二进制分组时，我们已经求出了 $p_1 \operatorname{xor} p_2$，那只需做一次二分求出 $p_1$ 即可。

[$\color{green}{\checkmark}$](https://codeforc.es/contest/835/submission/205528080)。

---

## 作者：dbxxx (赞：0)

[您可在博客中查看本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf835e.html)

设两个 $y$ 的下标分别是 $a$ 和 $b$。

为方便说明，下文所有的第 $i$ 位指的都是该数二进制从低到高第 $i$ 位。

观察答案的返回值，发现返回值有四种：$0$，$x$，$y$，$x \oplus y$，而且保证这四个数是互异的。容易看出：

- 当返回值是 $0$ 时，说明有偶数个 $x$ 和偶数个 $y$；
- 当返回值是 $x$ 时，说明有奇数个 $x$ 和偶数个 $y$；
- 当返回值是 $y$ 时，说明有偶数个 $x$ 和奇数个 $y$；
- 当返回值是 $x \oplus y$ 时，说明有奇数个 $x$ 和奇数个 $y$。

显然我们更关心 $y$ 的奇偶性。不难想出：

如果询问反馈有偶数个 $y$，说明 $a$ 和 $b$ 要么均在本次询问的集合，要么均落在外面。

如果询问反馈有奇数个 $y$，说明 $a$ 和 $b$ 有一个落在本次询问的集合，有一个落在外面。

这里我注意到，看起来后面那种反馈的信息量就更足一点。

那么本题看似选取一个子集查询的过程，其实就是将所有数分成两组的过程：查询集合里面的，和外面的。

---

再观察询问次数和 $n$ 的关系。发现询问次数的上界大概率是 $2\lceil \log_2n \rceil - 1$。可以想到二进制或者二分。

联想到 [P5304 GXOI/GZOI2019 旅行者](https://www.luogu.com.cn/problem/P5304)，有一个性质是两个数的二进制一定有某一位不同。

那道题里，我们分了 $\log_2 n$ 次组，第 $i$ 次分组，我们将第 $i$ 位是 $1$ 的分到一个组，是 $0$ 的分到一个组。

这样保证了每两个不同的数都至少一次被分在不同的组中，而且分组次数很低。

---

对于这个题，我们试着先询问 $10$ 次，第 $i$ 次询问取集合：所有第 $i$ 位是 $1$ 的数。

这样以来，一定有一次询问的反馈是落在了不同的组，我们设这是第 $k$ 次询问。

而且，我们顺便获取到了 $a \oplus b$ 的值。这意味着只要我们求出两者其中之一，就可以求出另一个。

---

我们知道，$a$ 和 $b$ 中的第 $k$ 位，一个是 $1$，一个是 $0$。我们就令那个是 $1$ 的是 $a$。

考虑询问第 $k$ 位和第 $i$ 位都是 $1$ 的。这样相对于查询第 $k$ 位的那次询问，我们把第 $k$ 位是 $1$ 但是第 $i$ 位是 $0$ 的丢到集合外边了。

如果返回的结果是 $a$ 和 $b$ 在同侧，说明 $a$ 的第 $i$ 位是 $0$（$a$ 被丢到外边了），否则说明 $a$ 的第 $i$ 位是 $1$。

显然查询的 $i$ 不必等于 $k$。所以这部分只用询问 $9$ 次。总询问次数满足要求。

---

如果想不到刚刚这种策略也没关系。一个更普通的想法是，直接在第 $k$ 位是 $1$ 的集合中二分即可。

具体来讲，我们先查询【第 $k$ 位是 $1$ 的集合】的一半。如果返回的结果是 $a$ 和 $b$ 同侧，说明 $a$ 在另一半。否则说明 $a$ 还在这一半。继续二分查找即可。

第 $k$ 位是 $1$ 的集合大小一定不超过原集合大小的一半。原因是这个集合中的任何一个数将第 $k$ 位改成 $0$ 后，会严格变小。显然还在原集合里面。所以第 $k$ 位是 $1$ 的集合大小一定不超过第 $k$ 位是 $0$ 的集合大小。

所以这部分可以 $9$ 次询问达到目的。

---

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-12-19 22:20:46 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-12-19 22:41:16
 */
#include <bits/stdc++.h>
inline int read() {
    int x = 0;
    bool f = true;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = false;
    for (; isdigit(ch); ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    return f ? x : (~(x - 1));
}

int n, x, y;

inline int ask(int S) {
    std :: vector <int> vec;
    for (int i = 1; i <= n; ++i)
        if ((i & S) == S)
            vec.push_back(i);
    
    if (vec.empty())
        return 0;
    
    printf("? %d ", (int)vec.size());
    for (int v : vec)
        printf("%d ", v);
    puts("");
    fflush(stdout);

    int ans = read();
    return (ans == y || ans == (x ^ y)) ? 1 : 0;
}

int t[15];

int main() {
    n = read();
    x = read();
    y = read();

    int k = 0;
    int x = 0;
    
    for (int i = 0; i < 10; ++i) {
        t[i] = (1 << i);
        int ans = ask(t[i]);
        if (ans) {
            k = i;
            x |= t[i];
        }
    }

    int a = t[k];
    
    for (int i = 0; i < 10; ++i) if (i ^ k) {
        if (ask(t[i] | t[k]))
            a |= t[i];
    }
    
    int b = (a ^ x);
    if (a > b)
        a ^= b ^= a ^= b;
    
    printf("! %d %d\n", a, b);
    return 0;
}
```

---

