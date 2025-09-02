# [ICPC 2015 WF] Weather Report

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/xqo70y6n.png)

你被气候测量协会雇佣，这是一家对长期跟踪全球天气趋势感兴趣的科学组织。当然，这不是一项简单的任务。他们在世界各地部署了许多小型设备，旨在定期测量当地的天气状况。这些设备价格低廉，功能有所限制。每天它们会观察四种标准天气中的哪一种发生：晴天、多云、雨天或青蛙雨。在每进行 $n$ 次这样的观察后，结果会被报告给主服务器进行分析。然而，设备数量庞大导致可用通信带宽超载。协会需要你的帮助来想出一种方法，将这些报告压缩成更少的比特。

对于某个设备的位置，你可以假设每天的天气是一个独立的随机事件，并且你会得到四种可能天气类型的预测概率。设备的每一个 $4^n$ 种可能的天气报告必须被编码为一个唯一的比特序列，且没有序列是其他序列的前缀（这是一个重要的属性，否则服务器将不知道每个序列何时结束）。目标是使用一种编码，最小化传输比特的期望数量。

## 说明/提示

时间限制：1000 毫秒，内存限制：1048576 KB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2015。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
0.9 0.049999 0.05 0.000001
```

### 输出

```
1.457510
```

## 样例 #2

### 输入

```
20
0.25 0.25 0.25 0.25
```

### 输出

```
40.000000
```

# 题解

## 作者：Starlight237 (赞：4)

## Huffman 树

设一棵二叉树的叶节点权值和深度分别为 $\{w_i\},\{d_i\}$，则定义 $\sum w_id_i$ 为这棵树的 **WPL**（这个名字并不准确，但是既然 OI-wiki 这么写，这里就沿用下来）。

给定所有叶节点和它们的 $w_i$，WPL 最小的二叉树称为这个叶节点权值序列的 **Huffman 树**。此外，这个二叉树应当满足除了叶节点的度为 0 以外，剩下的节点的度都是 2。

如下算法可以构建一个序列的 Huffman 树。

- 以给定的权值构造 n 棵只含有 1 个节点的二叉树，加入二叉树集合 $S$。
- 从 $S$ 中选取权值最小的两棵二叉树 $T_1,T_2$ 合并成一个大二叉树 $T$，并令 $w(T)=w(T_1)+w(T_2)$。从 $S$ 中删去 $T_1,T_2$，加入 $T$。
- 重复上一个步骤，直到 $S$ 中只剩下一棵二叉树。这棵二叉树就是 Huffman 树。事实上，合并过程中所有的 $w(T)$ 之和就是 Huffman 树的 WPL。

**Huffman 编码**

- 定义：将 $n$ 个不同的字符映射为互不为前缀的二进制编码，称为这组字符的**前缀编码**。若这组字符构成一个字符串 $S$，记 $f(S)$ 表示将 $S$ 中每个字符都替换成对应编码后 $S$ 的长度。使 $f(S)$ 最小的前缀编码称为 **Huffman 编码**。

如下算法可以构造对于一个字符集 $\Sigma$ 和字符串 $S$ 的 Huffman 编码。

设需要编码的字符分别为 $c_1,...,c_n$，它们在 $S$ 中出现的次数分别为 $w_1,...,w_n$，以 $c_i$ 为叶节点，$w_i$ 为它的权值，构建 Huffman 树。规定连接父亲和左儿子的边权为 $0$，连接右儿子则为 $1$，令 $c_i$ 的编码为从根节点走到 $c_i$ 途径的边权构成的 $0-1$ 字符串。容易证明这就是 Huffman 编码。并且 $f(S)$ 为 Huffman 树的 WPL。

回到本题：

> (**2021 集训队作业 P6915 【[ICPC2015 WF]Weather Report】**)给定 $4$ 种字符出现的概率，求所有 $4^n$ 个可能的长度为 $n$ 的字符串构成的集合的前缀编码，使得每个字符串的编码长度的期望值最小。

对于所有可能的字符串对应的概率求其 Huffman 树即可。但是 $4^n$ 太多了，无法接受。注意到一个字符串的权值（概率）仅与其四个字符出现的次数有关，即可以用有序四元组 $(a,b,c,d)(a+b+c+d=n)$ 表达。每个四元组的概率都容易计算，并且该四元组对应的字符串数量为 $\binom{n}{a}\binom{n-a}b\binom{n-a-b}c$。每个四元组作为一个状态 $(p,cnt)$，p 为它出现的概率，cnt 为它出现的次数，考虑对所有这些状态构建 Huffman 编码。

我们并不显式地建树，而只是开一个堆维护所有的 $w(T)$。

设堆顶为 $(p,cnt)$，若 $cnt>1$，对 $cnt$ 的奇偶性进行讨论，若 $cnt$ 为偶数，将 $(2p,cnt/2)$ 插入堆中，否则将 $(p,1)$ 插入堆中，再转化为 $cnt$ 为偶数的情况。

若 $cnt=1$，从堆中再取出一个状态 $(p',cnt')$ 和当前状态合并。若 $cnt'=1$，直接合并并且 `continue`，否则把状态拆成 $(p',cnt'-1)$ 和 $(p',1)$。后者直接和当前状态合并，前者插入堆中。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pi pair<double, ll>
const int N = 21;
int n, C[N][N];
double p[4][N];
priority_queue<pi, vector<pi>, greater<pi> > Q;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < 4; ++i) {
		p[i][0] = 1; double pp; scanf("%lf", &pp);
		for (int j = 1; j <= n; ++j) p[i][j] = p[i][j - 1] * pp;
	}
	for (int i = 0; i <= n; ++i) C[i][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n - i; ++j)
			for (int k = 0, l; k <= n - i - j; ++k)
				l = n - i - j - k,
				Q.push(make_pair(p[0][i] * p[1][j] * p[2][k] * p[3][l], (ll)C[n][i] * C[n - i][j] * C[n - i - j][k]));
	double ans = 0;
	while (!Q.empty()) {
		pi tp = Q.top(); Q.pop();
		if (Q.empty() && tp.second == 1) break;
		double pp = tp.first; ll cnt = tp.second;
		if (cnt > 1) {
			if (cnt & 1) Q.push(make_pair(pp, 1)), --cnt;
			ans += pp * cnt;
			Q.push(make_pair(pp * 2., cnt >> 1));
			continue;
		}
		tp = Q.top(), Q.pop();
		double qq = tp.first; cnt = tp.second;
		ans += pp + qq;
		Q.push(make_pair(pp + qq, 1));
		if (cnt > 1) Q.push(make_pair(qq, cnt - 1));
	}
	printf("%.6lf", ans);
	return 0;
}
```

---

## 作者：☯☯枫☯☯ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P6915)

[更好的阅读体验](https://www.cnblogs.com/lbh2021/p/15114201.html)

## 前置芝士：哈夫曼树

看到最小编码长度，当然要想起[哈夫曼树](https://baike.baidu.com/item/%E5%93%88%E5%A4%AB%E6%9B%BC%E6%A0%91/2305769?fr=aladdin#1)（又称最优二叉树）。哈夫曼树使用变长编码表对文本进行编码。基本思想是对出现次数多的字符使用较短的编码，对出现次数少的字符使用较长的编码，使得编码后字符串的平均长度及期望值降低。可以证明哈夫曼树的 WPL 是最小的。（WPL：树的带权路径长度，即从树根到每一叶子结点的带权路径长度之和）

在二进制下，哈夫曼树主要由以下过程构造：

1. 将每个结点看做一棵树，构成待构造的森林。
2. 每次在待构造的森林中选取两个根结点权值最小的树合并，作为一颗新树的左、右子树。新树的根结点权值为其左、右子树根结点的权值之和。
3. 删去选取的两棵树，将新树加入森林。
4. 重复步骤 2、3，直到森林中只剩下一棵树为止。该树即为所求的哈夫曼树。

在本题中，注意到本题顺序无关，因此有大量重复的情况。我们枚举每种天气出现的天数作为状态，打表可知在 $n=20$ 时，最多也仅有 $1771$ 种不同状态，远小于 $4^{20}=1099511627776$~~（打表大法好！）~~。所以可以对每种状态进行编码。将以上 $1771$ 种不同状态作为 $1771$ 棵树构造哈夫曼树。

尽管状态顺序无关，但相同的状态出现概率不同，对答案的贡献也不同。因此我们不仅要记录状态出现的概率，还要记录状态出现的次数。记四种天气出现的次数分别为 $\{i,j,k,u\}(u=n-i-j-k)$ 那么这种状态出现的概率 $P_i=p_1^i\times p_2^j\times p_3^k\times p_4^u$，不同的排布数 $Cnt_i=C_n^i\times C_{n-i}^j\times C_{n-i-j}^k$。

在哈夫曼树的模板中，每个结点仅代表一种排布。但在这里，每个结点代表的是一种状态，其中包含不同的排布情况。因此处理方法略有不同。

我们用小根堆维护哈夫曼森林，具体的：

- 若堆顶的状态排布数 $>1$：
  - 若排布数为偶数，将该结点“内部合并”，即将概率翻倍，排布数减半，作为一个新的结点。
  - 若排布数为奇数，先“取出”其中的一种排布，再进行偶数时的操作。
- 否则，取出第二个结点，将这两个结点合并。
  - 如果第二个结点的排布数 $>1$，将第二个结点的排布数减 $1$ 重新插入森林（因为与第一个结点合并仅需一种排布）。
  - 否则不再重新插入第二个结点（因为此时合并后原第二个结点的排布数已经为零）。

因为我们将概率作为结点的权值，最终构造完成时每个结点被计算的次数就是它们在哈夫曼树上的深度，也就是最终编码的长度，因此期望 $E=\sum\limits_{i=1}^{tot} P_i \times Cnt_i \times deep_i$。其中 $tot$ 为总状态数，$deep_i$ 表示结点 $i$ 在哈夫曼树上的深度，也表示编码的长度。

为了简便，我们并不显性连边构造哈夫曼树，而在合并结点时计算对答案的贡献即可。

枚举初始状态复杂度（或者说待合并结点数）为 $\mathcal{O}(n^3)$，堆以及内部合并复杂度都是 $\mathcal{O}(\log n)$。因此总时间复杂度为 $\mathcal{O}(n^3\log^2n)$。

~~尽管状态没那么多，但复杂度就是这样。~~

## Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define F(i,a,b) for(reg int i=(a);i<=(b);++i)
using namespace std;
bool beginning;
const int N=25;
int n;
double p[N],pa[N],pb[N],pc[N],pd[N];
ll c[N][N];
inline void init() {//预处理组合数 
	c[0][0]=1;
	F(i,1,20) {
		c[i][0]=c[i][i]=1;
		F(j,1,i-1)c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
}
struct P {
	double p;
	ll cnt;
	bool operator <(const P& a)const {
		return p>a.p;//重载小于号，变小根堆 
	}
};
bool ending;
int main() {
//	system("color fc");
// 	printf("%.2lfMB\n",1.0*(&beginning-&ending)/1024/1024);
	init();
	pa[0]=pb[0]=pc[0]=pd[0]=1.0;
	while(~scanf("%d",&n)) {
		F(i,1,4)scanf("%lf",&p[i]);
		F(i,1,20) {//预处理天气数的概率 
			pa[i]=pa[i-1]*p[1];
			pb[i]=pb[i-1]*p[2];
			pc[i]=pc[i-1]*p[3];
			pd[i]=pd[i-1]*p[4];
		}
		priority_queue<P>q;
		reg int u;
		F(i,0,n)F(j,0,n)F(k,0,n) {//插入初始结点 
			u=n-i-j-k;
			if(u<0)continue;
			q.push({pa[i]*pb[j]*pc[k]*pd[u],c[n][i]*c[n-i][j]*c[n-i-j][k]});
		}
		reg double ans=0;
		reg P x,y;
		while(!q.empty()) {
			x=q.top();
			q.pop();
			if(q.empty() and x.cnt==1)break;//仅剩一棵树 
			if(x.cnt>1) {//排布数大于 1 的情况 
				if(x.cnt&1)q.push({x.p,1}),--x.cnt;//奇数 
				ans+=x.p*x.cnt;//统计贡献 
				q.push({x.p*2,x.cnt/2});//内部合并 
			} else {//排布数为 1  
				y=q.top();
				q.pop();
				ans+=x.p+y.p;//统计贡献 
				q.push({x.p+y.p,1});
				if(y.cnt>1)q.push({y.p,y.cnt-1});//将第二个结点重新插入 
			}
		}
		printf("%.6lf\n",ans);
	}
	return 0;
}
```

[AC](https://www.luogu.com.cn/record/54594701)

欢迎交流讨论，请点个赞哦~

[双倍经验~](https://www.luogu.com.cn/problem/UVA1720)

~~双倍题解双倍快乐！~~

---

## 作者：henryhu2006 (赞：1)

## [ICPC2015 WF] Weather Report
题目大意已经被翻译概括得很清楚了，这里不多赘述。

做这道题前，你需要了解哈夫曼树，[哈夫曼树模板](https://www.luogu.com.cn/problem/P2168)。

### 过渡
二进制下的哈夫曼树的思想：选取两个数量最小的元素，合并成同一个元素（数量相加），然后在合并出来的元素的编码的最后加上一位 $0/1$ 区分这两种元素。

显然，“数量”可以改成“概率”，那么得到的答案就从“最短的压缩长度”变成了“最短压缩长度的期望值”，与本题符合。

### 暴力
枚举所有 $4^n$ 种可能的天气情况，然后按照概率丢进优先队列跑哈夫曼树。

时间复杂度 $\Theta(4^n\times n)$，无法通过 $20$ 的数据范围。

### 优化
可以发现，在 $4^n$ 种可能的天气情况中，有大量概率相同的情况。对于一个四种天气分别有 $a,b,c,d$ 天的情况，出现概率为 $p_{\operatorname{sunny}}^a\cdot 
p_{\operatorname{cloudy}}^b\cdot
p_{\operatorname{rainy}}^c\cdot
p_{\operatorname{frogs}}^d
$，情况数为 $\binom{a}{a+b+c+d}\times\binom{b}{b+c+d}\times\binom{c}{c+d}$。

因此，所有四种天气数量一样的情况可以压缩成一个元素处理。

具体来讲：

- 如果堆顶元素含有的情况数 $\ge2$，那么进行内部合并，概率翻倍，数量减半。特殊的，如果数量为奇数，将剩余的一种情况单独放进优先队列。
- 如果堆顶元素只有一种情况，那么从下一个元素单独取一种情况出来进行合并。

对于 $4$ 个非负整数相加等于 $n$，可能的情况数有 $\Theta(n^3)$ 种，（确定 $3$ 个即可确定剩下一个），所以时间复杂度即为 $\Theta(n^3\times 9\log^2n)$，由于 $n$ 只有 $20$，无需考虑常数。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=25; int n;
double A,B,C,D,ans,pa[N],pb[N],pc[N],pd[N];
ll c[N][N];
struct node{
	double p; ll num;
	inline bool operator < (const node&aa)const{
		return p>aa.p;
	}
}; priority_queue<node> q;
int main(){
	cin>>n>>A>>B>>C>>D,pa[0]=pb[0]=pc[0]=pd[0]=1;
	for(int i=1;i<=n;++i)
		pa[i]=pa[i-1]*A,pb[i]=pb[i-1]*B,
		pc[i]=pc[i-1]*C,pd[i]=pd[i-1]*D; // 预处理幂次
	for(int i=0;i<=n;++i){ // 组合数，n只有20，不会爆long long
		c[i][0]=1;
		for(int j=1;j<=i;++j)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
	for(int i=0;i<=n;++i) for(int j=0;j<=n;++j)
	for(int k=0;k<=n;++k) for(int l=0;l<=n;++l)
		if(i+j+k+l==n) 
			q.push((node){1.*pa[i]*pb[j]*pc[k]*pd[l],
			c[n][i]*c[n-i][j]*c[n-i-j][k]});
  	// 将所有可能情况加入优先队列
	while(1){
		node now=q.top(); q.pop();
		if(q.empty()&&now.num==1) break;
		if(now.num>1){ // 数量大于1
			if(now.num&1) q.push((node){now.p,1});
			// 零头
			q.push((node){2.*now.p,now.num>>1}),ans+=now.p*(now.num^(now.num&1)); 
			// 概率翻倍，数量减半
		}
		else{
			node tmp=q.top(); q.pop();
			q.push((node){now.p+tmp.p,1}),ans+=now.p+tmp.p;
			if(tmp.num>1) q.push((node){tmp.p,tmp.num-1});
			// 拆出独立元素合并
		}
	}
	printf("%.8lf",ans);
	return 0;
}
```

---

## 作者：qwer6 (赞：0)

## Description

（摘自洛谷题面，有所改编）。

给定4种天气情况出现的概率，你需要将 n 天的所有可能的 $4^n$ 种情况已某种方式编码为 01 串，使得任何一个编码不是另一个编码的前缀，求所有编码最短的期望长度。

## Solution

看到编码长度的期望最短，想到霍夫曼树求解。

容易想到暴力做法，也就是直接枚举出 $4^n$ 种不同的天气情况和概率，然后直接使用优先队列模拟霍夫曼树的构建，计算答案。

时间复杂度为 $O(n4^n)$，可以通过 $n\le 11$ 的数据，但是显然在面对 $n=20$ 规模的数据的时候会直接超时，所以我们需要优化。

哎，我们看看第一个样例，输出所有可能的概率，发现一个挺有意思的事情：有很多天气情况出现的概率是一样的。

这是不是巧合呢？其实不是，根据条件概率的相关知识，我们可以知道 $P=\prod_{i=1}^n p_i$，其中 $P$ 表示这 $n$ 天都出现我们指定的天气的概率，$p_i$ 表示第 $i$ 天出现我们指定的天气的概率。由于 $p_i$ 只有四种取值，所以也可以写出另外一种 $P$ 的计算公式 $P=p_1^xp_2^yp_3^zp_4^{n-x-y-z}$，其中 $x$ 为指定为晴朗天气的天数，$y$ 为指定为多云天气的天数，$z$ 为指定为大雨天气的天数。

我们发现只要 $x,y,z$ 确定，最后计算出的 $P$ 就是确定的，而与这 $n$ 天中具体每一天的天气是什么无关，所以对于一组 $(x,y,z)$，会有 $C_{n}^xC_{n-x}^yC_{n-x-y}^z$ 种可能的天气排列情况。

既然有这么多相同的概率，那是不是可以运用这个性质去优化构建霍夫曼树的构建呢？当然是可以的，我们考虑霍夫曼树的构建过程，从优先队列中取出当前的最小值和次小值，合并之后放回优先队列中。但是因为有很多相同的概率，所以我们可以发现有很多次操作取出的最小值和次小值都是相等的，我们可以直接加速这个过程。

我们将优先队列中的节点变为一个结构体，记录概率和对应的数量，然后先取出一个堆顶的元素，假设对应的概率为 $val$，对应的数量为 $cnt$，然后分类讨论。

1. $cnt$ 等于 $1$。

   显然这一个节点并不能完成合并，所以我们再取出第二个堆顶的元素，同样设对应的概率为 $val_0$，对应的数量为 $cnt_0$，然后从中分出一个来和这个节点合并，答案加上 $val+val_0$，然后向堆中放入一个值为 $val+val_0$，数量为 $1$ 的节点，同时，如果 $cnt_0$ 大于 $1$ 的话，向堆中放入一个值为 $val_0$，数量为 $cnt_0-1$ 的节点，也就是将剩下的值都放回去。

2. $cnt$ 为偶数。

   不用再取出第二个堆顶的元素，我们合并 $\frac{cnt}2$ 对 $val$，答案加上 $val\times cnt$，然后向堆中放入一个值为 $2\times val$，数量为 $\frac{cnt}{2}$ 的节点。

3. $cnt$ 为奇数。

   前面已经判断过 $cnt$ 等于 $1$ 的情况，所以这里 $cnt$ 大于等于 $3$。我们从这 $cnt$ 个相同元素中拆出一个单独的元素放回优先队列中，然后将剩下 $cnt-1$ 个元素按照偶数的方式处理即可。

那么这道题就写的差不多了，初始化枚举所有可能的 $(x,y,z)$ 计算概率和对应的数量放进优先队列中即可。

## Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
int n;
double p1,p2,p3,p4,ans;
int fac[25];
double pw1[25],pw2[25],pw3[25],pw4[25];
struct Node{
	double val;
	int cnt;
	bool operator >(const Node &a)const{
		return val>a.val;
	}
};
priority_queue<Node,vector<Node>,greater<Node>>q;
int A(int x,int y){
	return fac[y]/fac[y-x];
}
int C(int x,int y){
	return A(x,y)/fac[x]; 
}
signed main(){
	read(n);
	scanf("%lf%lf%lf%lf",&p1,&p2,&p3,&p4);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
	pw1[0]=pw2[0]=pw3[0]=pw4[0]=1.0;
	for(int i=1;i<=n;i++){
		pw1[i]=pw1[i-1]*p1;
		pw2[i]=pw2[i-1]*p2;
		pw3[i]=pw3[i-1]*p3;
		pw4[i]=pw4[i-1]*p4;
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j+i<=n;j++){
			for(int k=0;k+j+i<=n;k++){
				double p=pw1[i]*pw2[j]*pw3[k]*pw4[n-k-j-i];
				int cnt=C(i,n)*C(j,n-i)*C(k,n-i-j);
				q.push({p,cnt});
			}
		}
	}
	while(1){
		Node tmp1=q.top();
		q.pop();
		if(tmp1.cnt==1&&q.empty())break;
		if(tmp1.cnt==1){
			Node tmp2=q.top();
			q.pop();
			ans+=tmp1.val+tmp2.val;
			q.push({tmp1.val+tmp2.val,1});
			if(tmp2.cnt>1)q.push({tmp2.val,tmp2.cnt-1}); 
		}else if(tmp1.cnt&1){
			ans+=(tmp1.cnt-1)*tmp1.val;
			q.push({2*tmp1.val,tmp1.cnt/2});
			q.push({tmp1.val,1});
		}else{
			ans+=tmp1.cnt*tmp1.val;
			q.push({2*tmp1.val,tmp1.cnt/2});
		}
	}
	printf("%lf",ans);
}
```

---

