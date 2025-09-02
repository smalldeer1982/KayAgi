# [COCI 2019/2020 #6] Konstrukcija

## 题目背景

题目翻译来自 [LOJ3268](https://loj.ac/problem/3268)。

## 题目描述

**译自 [COCI 2019/2020 Contest #6](https://hsin.hr/coci/archive/2019_2020/) T3.** ***[Konstrukcija](https://hsin.hr/coci/archive/2019_2020/contest6_tasks.pdf)***

令 $G$ 为一个有向无环图。若 $G$ 的不同顶点 $c_1,c_2,c_3,\ldots c_n$ 满足有一条从 $c_1$ 到 $c_2$ 的路径，有一条从 $c_2$ 到 $c_3$ 的路径，……还有一条从 $c_{n-1}$ 到 $c_n$ 的路径，则称数组 $C = (c_1,c_2,c_3,\ldots c_n)$ 为一个从 $c_1$ 开始，在 $c_n$ 结束的有序数组。  
注意对于 $C$ 中任意的两个相邻的元素 $c_i,c_{i+1}$ 不必有直接连接的边，只需要有一条路径即可。

同时，我们定义有序数组 $C = (c_1,c_2,c_3,\ldots c_n)$ 的长度 $\mathrm{len}(C) = n$。因此，一个有序数组的长度即为其中包含的顶点个数。  
注意可以存在一个长度为 $1$，从同一个点开始并结束的有序数组。

并且，我们再定义有序数组 $C = (c_1,c_2,c_3,\ldots c_n)$ 的符号 $\mathrm{sgn}(C) = (-1)^{\mathrm{len}(C)+1}$。  
对于 $G$ 中的顶点 $x,y$，我们用 $S_{x,y}$ 表示所有从 $x$ 开始并在 $y$ 结束的有序数组的集合。

最后，我们定义顶点 $x,y$ 之间的矛盾值为 $\mathrm{tns}(x,y) = \sum\limits_{C \in S_{x,y}} \mathrm{sgn}(C)$。  
也就是说，顶点 $x,y$ 之间的矛盾值等于所有从 $x$ 开始并在 $y$ 结束的有序数组的符号之和。

给定一个整数 $K$，你需要构造一个最多 $1000$ 个点，$1000$ 条边的有向无环图满足 $\mathrm{tns}(1,N) = K$，其中 $N$ 为顶点个数。  
顶点以正整数 $1\ldots N$ 编号。

## 说明/提示

### 样例 1 解释
构造出的图包含 $6$ 个顶点。从 $1$ 开始在 $6$ 结束的有序数组有：

- $(1, 6)$；
- $(1, 4, 6)$；
- $(1, 5, 6)$；
- $(1, 3, 6)$；
- $(1, 2, 6)$；
- $(1, 4, 3, 6)$；
- $(1, 4, 2, 6)$；
- $(1, 5, 3, 6)$；
- $(1, 5, 2, 6)$；
- $(1, 3, 2, 6)$；
- $(1, 4, 3, 2, 6)$；
- $(1, 5, 3, 2, 6)$。
  
它们的长度分别为 $1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4$，  
所以它们的符号分别为 $-1, 1, 1, 1, 1,-1,-1,-1,-1,-1, 1, 1$。  
因此，$1$ 和 $6$ 的矛盾值为 $-1 + 1 + 1 + 1 + 1 - 1 - 1 - 1 - 1 - 1 + 1 + 1 = 0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5k7lbjtc.png)

-----

### 数据范围：


对于 $100\%$ 的数据，$|K| \le 10^{18}$。  
各子任务限制见下表：

|子任务|分值|限制|
|:-:|:-:|:-:|
|$0$|$0$|为样例|
|$1$|$13$|$1 \le K < 500$|
|$2$|$13$|$-300 < K \le 1$|
|$3$|$18$|$\lvert K\rvert < 10000$|
|$4$|$56$|-|

## 样例 #1

### 输入

```
0```

### 输出

```
6 6
1 4
1 5
4 3
5 3
3 2
2 6```

## 样例 #2

### 输入

```
1```

### 输出

```
1 0```

## 样例 #3

### 输入

```
2```

### 输出

```
6 8
1 2
1 3
1 4
1 5
5 4
2 6
3 6
4 6```

# 题解

## 作者：Feyn (赞：6)

[双倍经验，一模一样](https://www.luogu.com.cn/problem/P7256)

说一下模拟赛场上和场下关于这道题的心路历程。

$15$ 分应该是很容易的。考虑把 $1$ 和 $N$ 放在两边，然后在中间放一些点，然后这些点分别和起终点连边，显然这样每条支路就会有一个长度为 $3$ 的合法序列，于是最后的答案就是支路数减一，点数和边数都和输入是同级的。

然后我就开始思考能不能把这玩意拆分成几个部分，一顿手玩之后发现一种妙的图，具体构造方法是三个点为一列，列和列之间完全连边，不相邻的列不连边。大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/nvmdzux3.png)

发现这种图有一个性质，随着列数越来越多，整体的答案会是 $1\ -2\ \ 4\ -8\dots$ 这样的，十分有规律。而我们知道这个图形有一个性质，即各部分的贡献可以累加。于是就可以把询问的数拆分成许多数之和，然后就对各部分进行处理即可。于是考场上得了 $48$ 分，代码就不放了。

场下看了别人的代码并结合了官方的题解，却仍然久久未能明白，特别是那句 we
can add two nodes to a new level that are connected to all from the previous level 中的 previous 具体指什么百思不得其解（我太弱了），在咨询其它大佬之后用我的语言给出这道题的完整解法：

其实考场上的代码已经很靠近正解了，只是没有把问题进行很好的具象分析。我们可以令 $f_{x,0/1}$ 代表序列最后一个节点是 $x$，并且序列长度奇偶性确定时的方案数，转移就是枚举所有能到达 $x$ 的 $y$，$f_{x,p}=\sum f_{y,1-p}$。然后发现没必要加上后面那一维，所以我们可以令 $g_x$ 是 $f_{x,1}$ 和 $f_{x,0}$ 的差，那么方程就变成了 $g_x=-\sum g_y$。

观察上面那个模型，发现任意一个点都可以被前面任意一层的任意节点到达，所以可以记 $sum_x$ 为前 $x$ 层 $g$ 值总和，那么第 $x+1$ 层的 $g$ 值应该是 $-sum_x$，更新一下就有 $sum_{x+1}=sum_x-sum_x\times q=(1-q)sum_x$（假设每层的节点个数是 $q$）。有两个特殊值：$q=3$ 时会让总和扩大一倍，而 $q=2$ 时会让总和取反，我们可以利用这两个操作来构造出输入值。

显然越靠前的位置对答案的影响越大，考虑特殊情况，即 $K=2^r$ 的情况，显然我们可以一开始用一个 $q=3$ 的层，然后一直用 $r$ 次，这样可以保证得到的结果绝对值一定是 $K$，如果正负不对的话直接用 $q=2$ 的做法取反即可。

然后思考如何推广上述流程，也就是如何在一个二进制位上放一。通过第一个 subtask 的经验，任意一个直接和起点相连的边都对答案有一个负的贡献，那么假如当前的总和是负的，那么我们在本层添加一个直接和 $1$ 相连的点就可以了；如果总和是负的，那么直接通过操作把总和取反之后就是前面的问题了。

其它的就没什么了，有些细节需要自己思考一下，但如果理解了那些问题就很简单了。

代码比较短，由于某些原因压了点行，不影响可读性。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
#define adding for(int x:last)for(int y:now)ans.push_back((node){x,y})
using namespace std;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int m,cnt=1;

struct node{int a,b;};
vector<int>endll,last,now;
vector<node>ans;

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	if(m==0){printf("3 2\n1 2\n 2 3\n");return 0;}
	if(m==1){printf("1 0\n");return 0;}
	if(m==-1){printf("2 1\n1 2\n");return 0;}
	bool neg=false,op=false;if(m<0)m=-m,neg=true;
	int lg=1;while((1ll<<lg)<=m)lg++;lg--;
	
	for(int i=lg-1;i>=0;i--){
		now.clear();for(int j=0;j<3;j++)now.push_back(++cnt);
		if(i==lg-1)for(int x:now)ans.push_back((node){1,x});else adding;
		if(((1ll<<i)&m)==0){last=now;op^=1;continue;}
		if(op){last=now;now.clear();for(int j=0;j<2;j++)now.push_back(++cnt);adding;}
		now.push_back(++cnt);ans.push_back((node){1,cnt});last=now;op=true;
	}
	if(neg==op){now.clear();for(int i=0;i<2;i++)now.push_back(++cnt);adding;}
	++cnt;for(int x:now)ans.push_back((node){x,cnt});
	printf("%lld %lld\n",cnt,ans.size());
	for(node x:ans)printf("%lld %lld\n",x.a,x.b);
	
	return 0;
}
```

---

## 作者：ganpig (赞：3)

被现有题解的做法吓到了。

别看这是个黑题，其实就是 $-2$ 进制拆分的板子。

从输入为 $2$ 的一组样例入手。容易发现答案可以简化为下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/747eztfs.png)

在这张图中：

| $i$ | $1$ | $2$ | $3$ | $4$ | $5$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $\operatorname{tns}(1,i)$ | $1$ | $-1$ | $-1$ | $-1$ | $2$ |

分析一下 $\operatorname{tns}(1,5)$ 的计算过程：

- 从 $2$ 及其之前的结点 $1$ 转移，由于 $2$ 本身就是从 $1$ 转移来的，所以 $\operatorname{tns}(1,2)$ 与 $\operatorname{tns}(1,1)$ 互为相反数抵消了；
- 从 $3$ 及其之前的结点 $1$ 转移，由于 $1$ 已经被算过了，只有 $\operatorname{tns}(1,3)=-1$ 产生了贡献 $1$；
- 从 $4$ 及其之前的结点 $1$ 转移，由于 $1$ 已经被算过了，只有 $\operatorname{tns}(1,4)=-1$ 产生了贡献 $1$。

于是，$\operatorname{tns}(1,5)=2$ 是上一层答案 $-1$ 的 $-2$ 倍。

如果再加一层，是不是又能得到 $2$ 的 $-2$ 倍，即 $-4$ 了呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/xsjon0q1.png)

| $i$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $\operatorname{tns}(1,i)$ | $1$ | $-1$ | $-1$ | $-1$ | $2$ | $2$ | $2$ | $-4$ |

果真如此。同理，可以用这样的方式叠出 $-1,2,-4,8,\cdots,(-1)^{n+1}\cdot2^n$。

如何把这些结点的答案加成最后一个结点的答案，即题目所要求构造的 $\operatorname{tns}(1,n)$ 呢？

先从最后一层取一个点连到 $n$，这个操作对 $\operatorname{tns}(1,n)$ 没有贡献（因为上面抵消了），但保证了之后再连边时，之前的这些结点不会对其产生影响；

接着，在所需的层上“扩建”一个点，从这些点向 $n$ 连边即可。为了方便，可以一开始建“塔”时就在每层建四个结点，其中一个不往下连边（以保证其不会被下面的点依赖），只在最后向 $n$ 连边。

从 $K$ 的 $-2$ 进制表示中为 $1$ 的位连到最后一个结点即可。例如，$K=3=(-2)^2+(-2)^1+(-2)^0=(111)_{-2}$，那就这么连：

![](https://cdn.luogu.com.cn/upload/image_hosting/2we2xxea.png)

记得特判 $K=0$ 的情况，此时直接在 $1$ 之外建一个孤立点即可。~~（抄样例输出也不是不行）~~

于是，我们用超短的代码过掉了这道黑题。~~（以及它的镜像 [P7256](https://www.luogu.com.cn/problem/P7256)）~~

### $\text{Code}$

```cpp
#include <bits/stdc++.h>
int main() {
    long long k;
    std::cin >> k;
    if (!k) // 特判
        return puts("2 0"), 0;

    // -2 进制拆分
    std::vector<int> res;
    for (int b = 0; k; b++)
        if (k & 1ll << b)
            k -= (b & 1 ? -1ll : 1ll) << b, res.emplace_back(b);

    // 建“塔”
    std::vector<std::pair<int, int>> ans{{1, 2}, {1, 3}, {1, 4}, {1, 5}};
    int cnt = 5;
    for (int b = 1; b <= res.back(); cnt += 4, b++)
        for (int i = 0; i <= 2; i++)
            for (int j = 1; j <= 4; j++)
                ans.emplace_back(cnt - i, cnt + j);

    // 向 n 连边
    ans.emplace_back(cnt, cnt + 1);
    for (int b : res)
        ans.emplace_back(4 * b + 2, cnt + 1);

    printf("%d %d\n", cnt + 1, ans.size());
    for (auto [u, v] : ans)
        printf("%d %d\n", u, v);

    return 0;
}
```

---

## 作者：Wait_Add (赞：2)

## 性质一
若图的终点 $y$ 仅与一个点 $a$ 直接相连，且点 $a$ 不为起点，此图的矛盾值 $tns=1$。  

**证明**：  
若不选 $a$ 能得到有序数组 $C=(c_1,c_2,\dots,y)$，  
选上 $a$ 后一定存在有序数组 $C=(c_1,c_2,\dots,a,y)$，  
两数组奇偶性互异，符号 $sng$ 相反，对矛盾值的贡献为 $0$。  
## 性质二
若将两个图的部分点重合，  
所得图的矛盾值 $tns$ 等于两个图的 $tns$ 之和减去重合点构成图的 $tns$。  
![](https://cdn.luogu.com.cn/upload/image_hosting/witv5fch.png?x-oss-process=image/resize,m_fixed,,w_600)  

**证明**：  
图 $1$ 的贡献值等于只含紫色点的 $\sum sng$，加只含紫色点和红色点的 $\sum sng$，加只含紫色点和蓝色点的 $\sum sng$。  
图 $2$ 的贡献值等于只含紫色点的 $\sum sng$，加只含紫色点和红色点的 $\sum sng$。  
图 $3$ 的贡献值等于只含紫色点的 $\sum sng$，加只含紫色点和蓝色点的 $\sum sng$。  
因此 $tns1=tns2+tns3-$ 只含紫色点的 $\sum sng$。  

## 做法
这是一个 $tns_1=-1$ 的图一，  
![](https://cdn.luogu.com.cn/upload/image_hosting/w0c9hj11.png?x-oss-process=image/resize,m_fixed,,w_70)  
从终点向外新建一个点，以新建的点为终点，得到了一个 $tns_2=0$ 的图二（根据性质一）。  
![](https://cdn.luogu.com.cn/upload/image_hosting/nvvlx9u1.png?x-oss-process=image/resize,m_fixed,,w_120)  
将三个图三首尾重合，得到了图四，  
![](https://cdn.luogu.com.cn/upload/image_hosting/bm4dfng3.png?x-oss-process=image/resize,m_fixed,,w_120)  
根据性质二，图四的矛盾值 $tns_4=3tns_2-2tns_1=-2tns_1=2$，  

将图四从终点向外新建一个点，以新建的点为终点，得到了一个 $tns_5=0$ 的图五（根据性质一）。  
![](https://cdn.luogu.com.cn/upload/image_hosting/gcmwvfxa.png?x-oss-process=image/resize,m_fixed,,w_120)  
将三个图五的红色点重合，得到了图六，  
![](https://cdn.luogu.com.cn/upload/image_hosting/4j1we8li.png?x-oss-process=image/resize,m_fixed,,w_120)  
根据性质二，图六的矛盾值 $tns_6=3tns_5-2tns_1=-2tns_4=-4$，  
 
 同理，我们可以造出矛盾值为 $-2^k$ 的所有图。  
### 造出矛盾值为 $-2^k$ 的图后，如何将图结合在一起
先建一棵矛盾值为 $-2^{max}$ 的图，  
![](https://cdn.luogu.com.cn/upload/image_hosting/sdtio7nh.png?x-oss-process=image/resize,m_fixed,,w_120)  
再将从终点向外新建一个点，以新建的点为终点，此时矛盾值 $tns=0$（根据性质一）。  

若题目要求的 $k=3=-2^0+-2^2$，  
如图，新建一个点，连接起点和终点，新建一个点，连接第二层的点和终点。  
![](https://cdn.luogu.com.cn/upload/image_hosting/w3d0plgn.png?x-oss-process=image/resize,m_fixed,,w_300)  
此时的图相当于三个图重合：  
一棵矛盾值为 $-2^{max}$ 的图从终点向外新建一个点；  
一棵矛盾值为 $-2^{0}$ 的图从终点向外新建一个点；  
一棵矛盾值为 $-2^{2}$ 的图从终点向外新建一个点。  

重合的点构成的图为：  
一棵矛盾值为 $-2^{0}$ 的图；  
一棵矛盾值为 $-2^{2}$ 的图。  

根据性质二，图的矛盾值 $tns=-2^0+-2^2$。  
## code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+100;
bool v[N];
long long k,ans;
int main(){
	cin>>k;
	if(k==0){
	    printf("3 2\n");
	    printf("1 2\n");
	    printf("2 3\n");
	    return 0;
	}
	int b=0;
	for(;k;b++)
        if(abs(k)&1ll<<b)
            k+=(b&1?1ll:-1ll)<<b,
			v[b]=true,
			ans++;
	printf("%d %lld\n",b*4+3,7+12*b-12+ans+1);
	printf("1 2\n");
	printf("1 3\n");
	printf("1 4\n");
	printf("1 5\n");
	if(v[0])	printf("2 %d\n",b*4+3);
	for(int k=1;k< b;k++){
		if(v[k])	printf("%d %d\n",k*4+2,b*4+3);
		for(int i=k*4-1;i<=k*4+1;i++){
			printf("%d %d\n",i,k*4+2);
			for(int j=k*4+3;j<=k*4+5;j++)
				printf("%d %d\n",i,j);
		}
	}
	for(int i=b*4-1;i<=b*4+1;i++)
		printf("%d %d\n",i,b*4+2);
	printf("%d %d\n",b*4+2,b*4+3);
	return 0;
}
```

---

## 作者：SDLTF_凌亭风 (赞：1)

我们来定义这样一个点集合 $S<a,b>$，对于集合中的任意一个点 $x$，从 $a$ 到 $x$ 有一条路径，$b$ 到 $x$ 有一条路径，且 $x,b$ 不相同。

对于任意的有序数组 $C$，我们删去他的最后一个元素，并把它加入到以 $x$ 开头的一个新的有序数组 $C'$ 中且以 $S<a,b>$ 中的一些结点结尾，保证 $C'$ 的长度比 $C$ 的长度小 $1$。

这样我们就构造出了一个 $\operatorname{sgn}(C)=-\operatorname{sgn}(C')$，则 $\operatorname{tns}(x,y)=-\sum_{z\in S<a,b>}\operatorname{tns}(x,z)$。

考虑建立一个分层图。第一层只有一个点 $1$ 并且最后一层只有一个结点 $N$，那么在前两个子任务重，所有除了 $N$ 的节点都有一个指向下一层的有向边。

如果很难想象，请参考神经网络那道题的图片。

那么不难发现，如果在新的一层新增 $M$ 个结点，就会将所有 $\operatorname{tns}(1,x)$ 值的和乘以 $-(M-1)$。并且 $\operatorname{tns}(1,N)$ 等于所有 $\operatorname{tns}(1,x)(1\leq x < N)$ 值的和乘以 $− 1$。

那么在 $K=2^i$ 时答案就很好构造了。通过在新的一层上添加三个节点，我们可以使用 $3 +9(i−1)$ 个结点得到新的 $K$。如果不符合题意，直接下一级添加 $2$ 个结点并乘上 $-1$即可。

代码如下：

```cpp
#include <bits/stdc++.h>
#define floop(i, a, b) for(int i = (a); i < (b); i++)
#define fi first
#define se second
using ll = long long;
using PI = pair<int, int>
using namespace std;
struct Graph {
	int n;
	vector<PI> pntset;
	vector<int> lastlv;
	Graph(int _n, vector<PI> pts) { n = _n, pntset = pts; }
	Graph() { n = 1, lastlv.push_back(1); }
	inline ll time2(ll nowlv) {
		vector<int> novi = {n + 1, n + 2, n + 3};
		for(auto x : lastlv) for(auto y : novi) pntset.push_back(PI(x, y));
		return lastlv = novi, n += 3, -2 * nowlv;
	}
	inline ll del1(ll nowlv) {	return pntset.push_back(PI(1, n + 1)), lastlv.push_back(n + 1), ++ n nowlv - 1; }
	inline ll add1(ll nowlv) {
		vector<int> novi = {n + 1, n + 2};
		for(auto x : lastlv) for(auto y : novi) pntset.push_back(PI(x, y));
		return pntset.push_back(PI(1, n + 3)), novi.push_back(n + 3); lastlv = novim, n += 3, -nowlv - 1;
	}
	inline void ed() {
		vector<int> novi = {n + 1, n + 2};
		for(auto x : lastlv) for(auto y : novi) pntset.push_back(PI(x, y));
		lastlv = novi;
		for(auto x : lastlv) pntset.push_back(PI(x, n + 3));
		n += 3;
	}
	inline void edsub1() {
		for(auto x : lastlv) pntset.push_back(PI(x, n + 1));
		++ n;
	}
	inline void print() {
		cout << n << ' ' << (int)pntset.size() << end;
		for(auto p : pntset) cout << p.fi << ' ' << p.se << endl;
	}
};
vector<int> ksm(ll t) {
	vector<int> ret;
	for(; t; ret.push_back(t & 1), t >>= 1);
	reverse(ret.begin(), ret.end());
	return ret;
}

Graph dfs(ll t) {
	if(!t) {
		Graph g(3, {PI(1, 2), PI(2, 3)});
		return g;
	}
	Graph g;
	vector<int> binarno = ksm(abs(t));
	ll nowlv = 1;
	floop(i, 1, (int)binarno.size()) {
		nowlv = g.time2(nowlv);
		if(binarno[i]) nowlv = (nowlv < 0) ? g.del1(nowlv) : g.add1(nowlv);
	}
	(nowlv == t) ? (g.ed()) : (g.edsub1());
	return g;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	ll t; cin >> t;
	Graph g = dfs(t);
	g.print();
}
```

---

## 作者：Halberd_Cease (赞：0)

首先你应该了解答案是怎么来的。

增量地考虑，假设现在有一堆点，已经形成了若干条路径，所有以 $x$ 结尾的路径权值和为 $f_x$。如果有 $i,j,k,\dots$ 这几个点直接或者间接连接了 $x$，那么 $f_x=-f_i-f_j-f_k-\cdots$。显然每个节点统计的路径因为终点是自己所以不重。每一个能间接到达 $x$ 的点，均可以在以自己为终点的路径基础上，加上 $x$ 点得到终点为 $x$ 的新路径。因为长度 $+1$ 所以权值需要取反。初始值为 $f_1=1$。

手玩发现，在 $1$ 和 $n$ 之间构建层数为 $k$，每一层大小为 $3$，相邻两层之间完全连接的分层图，我们发现答案为 $-(-2)^k$。这启发我们使用二进制分解。

$O(\log^2 n)$ 的做法就是，将若干个这种分层图并联在 $1$ 和 $n$ 之间，期望得分 $44$ 分（实际上你还需要特殊考虑并联多个分层图答案不严格加上 $-(-2)^k$，每个分层图会偏移 $1$）。

继续手玩考虑找到更优的结构，但我们发现 $9$ 条边是将答案 $\times2$ 的最小代价了，因此并联计算总贡献没有前途，所以考虑只构建 $1$ 个分层图。

我们将分层图中节点的权值计算出来，发现第 $i(i\ge 1)$ 层（设节点 $1$ 在第 $0$ 层）的点权值为 $-(-2)^{i-1}$，这给了我们一个计算的依据。

来考虑一个子问题：如何让最终的答案加上 $x$。首先我们假设所有点都能到达 $n$，这时构造且仅构造一个新点 $i$ 使得权值为 $-x$，将这个点连向 $n$。我们发现最重要的一个地方就是需要一步构造点 $i$，因为多构造点会对最终答案产生额外的贡献。

剩下的问题就是如何用分层图中点的贡献构建特殊权值的点。前面提到了一个性质，就是第 $i$ 层的每个点，权值都是 $-(-2)^{i-1}$。第 $i$ 层的点直接前驱是第 $i-1$ 层的所有点。因此我们可以轻易构建出权值为 $-(-2)^{i}$ 的新点（即连接第 $i$ 层的 $3$ 个点，到达 $n$ 点），可以给最终答案贡献 $(-2)^{i}$。

至此已经可以做题了。但是我们希望分解更优美一些，考虑如何构造权值为 $(-2)^{k}$ 的新点让答案加上 $-(-2)^{k}$。回到分层图上，我们发现连接分层图第 $i$ 层 $1$ 个点会使答案变成 $0$，因为这时做贡献的点是 $i-1$ 层往上所有点和第 $i$ 层一个点。我们又知道第 $i$ 层一个点的贡献是 $i-1$ 层往上所有点的贡献的相反数。于是自然想到连接 $i$ 层两个点，那么这个点的权值就是 $i-1$ 层晚上所有点的贡献，即 $(-2)^{i-1}$，对最终答案的贡献就是 $-(-2)^{k-1}$。于是可以简单分正负数讨论，不用所谓 $-2$ 进制拆分。

还需要注意整个分层图的处理，我们希望整个分层图在一开始就全部能够到达 $n$，并且总贡献为 $0$。可以在分层图尾部串联上一个节点，根据上面结论串联后可以使得贡献变为 $0$。然后这个串联节点连向 $n$ 号点。

代码很好写，不需要任何特判。

:::success[code]
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 998244353;
#ifdef int
#define inf 0x3f3f3f3f3f3f3f3f
#else
#define inf 0x3f3f3f3f
#endif
const long long infll = 0x3f3f3f3f3f3f3f3f;
#define pii pair<int, int>
#define mkp(x,y) make_pair(x,y)

#ifndef LOCAL
#define SUBMIT
#endif

#ifdef SUBMIT
#define endl '\n'
//#define cin Fastio ::cin
//#define cout Fastio ::cout
#endif

template<typename T>
void read(vector<T> &vec)
{
    for(auto &x:vec)
    {
        cin>>x;
    }
}

int qpow(int n,int k)
{
    int res=1;
    while(k)
    {
        if(k&1)(res*=n)%=MOD;
        (n*=n)%=MOD;
        k>>=1;
    }
    return res;
}

vector<pii>edge;
int cnt=1;
int offi;

vector<int>veclevel[70];

void add(int level,int x)
{
    cnt++;
    for(int i=0;i<x;i++)edge.push_back({veclevel[level][i],cnt});
    edge.push_back({cnt,1000});
}

map<int,pii>mp;

void work()
{
    int fi=-1,sec=-2;
    mp[1]={0,1};
    for(int i=1;i<=61;i++)
    {
        mp[fi]={i,2};
        mp[sec]={i,3};
        fi=fi*-2;
        sec=sec*-2;
    }
    veclevel[0].push_back(1);
    for(int i=1;i<=61;i++)
    {
        veclevel[i].push_back(++cnt);
        veclevel[i].push_back(++cnt);
        veclevel[i].push_back(++cnt);
        for(auto x:veclevel[i-1])for(auto y:veclevel[i])edge.push_back({x,y});
    }
    ++cnt;
    for(auto x:veclevel[61])edge.push_back({x,cnt});
    edge.push_back({cnt,1000});
    int x;
    cin>>x;
    int sig=1;
    if(x<0)
    {
        sig=-1;
        x=-x;
    }
    int res=1ll<<60;
    while(res)
    {
        if(x>=res)
        {
            add(mp[res*sig].first,mp[res*sig].second);
            x-=res;
        }
        res>>=1;
    }
    cout<<1000<<' '<<edge.size()<<endl;
    for(auto x:edge)cout<<x.first<<' '<<x.second<<endl;
}

signed main()
{
    #ifndef LOCAL
    #ifndef NFILE
    // freopen("konstrukcija.in","r",stdin);
    // freopen("konstrukcija.out","w",stdout);
    #endif
    #endif
    
#ifndef cin
#ifdef SUBMIT
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
#endif
    int t=1;
    // cin>>t;
    while(t--)
    {
        work();
    }
}
```
:::

---

