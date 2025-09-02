# [Ynoi2010] Fusion tree

## 题目背景

题目背景和题意无关，可以跳过

## 1.前言：
Fusion Tree，中文译作融合树，是一种亚log的数据结构，与1993年由Michael L.Fredman和Dan E.Willard提出。

用途：$O( \log n/ \log w+ \log w )$时间复杂度支持插入，删除，前驱，后继，min，max，以及用于整数排序。

信息论断言对$n$个数的排序在最坏情况下需要$n\log n$次比较，不过对这个界我们还需要一些研究。

有人证明了任意unit cost RAM算法，其中只包含加法，减法，乘法，和0比较（但是不包含除法和位运算）最坏情况下需要$\Omega(n\log n)$的时间去对$n$个数排序。

如果允许使用除法和位运算，他们有一个线性时间复杂度的算法，但是这个算法对unit cost滥用。

这里我们规定我们使用的计算模型的字长是w，每个输入的数都是在$[0,2^w-1]$中的整数。

## 2.一些记号：
对于一个集合$S$和一个整数$x$，定义$rank(S,x)$为S集合中$\le x$的元素个数。
对于一些非负整数$a$，定义$bin(a_1,...,a_n)=2^{a_i}+...+2^{a_n}$。

对于两个非负整数$a,b$，定义$msb(u,v)$为$u$和$v$最高的不相同的位。

## 3.概述：
Fusion Tree大概可以看做是一棵特殊的B-Tree，特性：

1. 叉数$B=O(w^{1/5})$

2. 在一次搜索时，每个在搜索路径上的节点的正确的儿子可以被$O(1)$确定

从这些特性我们可以看出Fusion Tree单次操作的时间复杂度是$O( \log _w(n) + \log w) = O( \log n/\log w +\log  w)$的，比$O( \log n )$低。

但是由于其实现方式，Fusion Tree每次对内部节点的更新复杂度是$O( B^4 )$的。
为了控制Fusion Tree均摊的更新复杂度，我们将这棵B-Tree的每对叶子节点之间的部分替换为一个大小大约为$O( B^4 )$的Weight Balanced Tree，只在WBT根节点发生变化的时候更新Fusion Tree的内部节点。

具体来说，我们B-Tree维护的是一个排序后的数组的分块，其中每个块都由一棵平衡二叉搜索树维护，fusion tree上只维护一个值来表示块边界，用途是指引每次插入，删除，查询在哪个块中。

可以发现这样我们把内部节点的变化次数除掉了一个$B^4$。

## 4.压缩key的表示：

如何$O(1)$确定搜索路径上的一个节点的正确的儿子：

考虑一个B-Tree的节点，其上面包含了$k$个key，其中$B/2 \le k \le B$，记作$S={u_1,u_2,...u_k}$。

然后我们定义出$B(S)$表示"有区别的位的位置"，用人话来说就是我们把这$k$个key的trie建出来，然后所有有超过$1$个儿子的节点的高度构成的集合
（当然这里我们不用把trie建出来，只是这么解释比较直观，而且更能反映出其的一些性质）。

再定义一个集合$K(S)$，为$S$只保留$B(S)$中那些位之后的值，记作$K(S)={u'_1,u'_2,...u'_k}$，发现这个压缩操作对于原集合是保序的。

对于一个任意的$w-bit$的数$u$，我们记$u'(S)$表示$u$只保留$B(S)$中那些位，即把非$B(S)$中的位都置为$0$之后的值。

下面引理表达了一个压缩key的重要性质：

### 引理1：
设$B(S)$排序后为$c_1<c_2<...<c_r$，定义边界$c_0=-1,c_{r+1}=b$。

定义$u'_i$为$K(S)$中任意的一个压缩后的key。

对于一个任意的$w-bit$的数$u$，满足$u \neq u_i$，

设$msb(u'(S),u'_i)=c_m$，即$u$和$u_i$在bit位置$c_{m+1},...,c_r$位置处相等，但是在$c_m$处不相等，如果$u'(S)=u'_i$，则我们记$m=0$。

如果$u$和$u_i$不同的最高位$p$满足$p>c_m$，那么我们可以通过：

1. 唯一的一个区间$[c_{j-1},c_j]$满足$p$属于这个区间

2. $u$和$u_i$的大小关系

来确定$rank(S,u)$的值。

证明平凡，把trie画出来，显然可以画成一个平面图，然后可以发现这两个可以唯一地确定出一个平面区域，这个区域中的$S$集合元素个数就是$rank(S,u)$（感觉这种东西光写一堆自然语言也不能说明正确性，需要形式化证明一下？）。

注意到这个引理虽然是对任意$u_i$成立的，但是要求$u$和$u_i$不相同的最高位不是$B(S)$中的一个点，可以发现这个$u_i$其实必须在$u$"脱离"这个trie的位置，也就是$p$的父亲子树中。

引理$1$使得我们可以将$rank(S,u)$的计算规模降低到$rank(K(S),u'(S))$，通过计算$rank(K(S),u'(S))$，我们可以确定$u'(S)$在$K(S)$中的前驱后继$u'_j$和$u'_{j+1}$（这两个值不一定存在，但经过平凡的讨论就可以解决。

如果$u_j \le u \le u_{j+1}$，那我们已经解决了这个问题
否则我们令$i=j$或者$i=j+1$，计算出$msb(u_i,u)=p$，然后只要我们知道了包含$p$的区间$[c_j,c_{j+1}]$，我们就可以通过引理$1$来确定出$rank(S,u)$的值。

这里如果我们$u_j \le u \le u_{j+1}$，那我们已经达成了目的，不用继续考虑了。

否则如果不满足$u_j \le u \le u_{j+1}$，也就是说我们在这个sketch的过程中丢失了信息，即说明保留$K(S)$这些位的信息是不够的，那么$p$一定不在$K(S)$中，也就是说$i=j$和$i=j+1$中$p$较小的$i$满足$p>c_m$，故可以使用引理$1$。

计算$K(S)$和$u'(S)$：
我们发现没有平凡的方法可以将一个$w-bit$的数$u$在$O(1)$时间把$B(S)$那些位提取出来之后放到连续的一段中（可能可以通过硬件支持实现？），即使经过了一定预处理。

其实我们不需要做到这个，可以用具有：

1. 将需要提取出的位提取出，并放到（可以不连续）的更短的一段中

2. 保序性

的其他变化来实现我们需要的效果。

我们可以通过一次恰当的乘法和一次与运算来实现这个：

沿用引理$1$的定义，设我们需要从$u$中提取这些位，令$C=bin(c_1,...,c_r)$。

假设我们已经算出了$C$，我们先通过令$v=u\;\mathrm{AND}\;C$来将$u$中不需要的那些位置$0$。

然后我们将$v$乘以一个量$M$，从而把$v$中我们需要的那些$bit$转化到一个狭窄的范围内，然后再通过一次$\mathrm{AND}$来清除掉不需要的位置
这里给出对一个量$M$的存在性证明和构造：

记$M=bin(m_1,...,m_r)$，如果我们暂时忽略交叉和进位造成的影响，那么可以认为$v$乘$M$是把$c_1,...c_r$这些位置的位重新定位到了。

$c_1+m_1,...,c_r+m_r$上。

如果对任意$1 \le i,j \le r$，这$r^2$个$c_i+m_j$都是不同的，那么就不会发生交叉和进位了。

我们现在的目标是构造一个整数集合${m_1,...,m_r}$，使得：

1. $c_1+m_1<c_2+m_2<...<c_r+m_r$

2. 对任意$1 \le i,j \le r$，$c_i+m_j$都是两两不同的。

3. 变换后的区间$[c_1+m_1,c_r+m_r]$"相对较小"，这里的相对较小其实只要是$O( poly(r) )$的即可，因为这样我们可以通过调整树的叉数来满足后续的条件。

### 引理2：

给一个$r$个整数的序列，$c_1<...<c_r$，存在一个$r$个整数的序列，$m_1,...m_r$，满足：

1. $c_1+m_1<c_2+m_2<...<c_r+m_r$

2. 对任意$1 \le i,j \le r$，$c_i+m_j$都是两两不同的。

3. $(c_r+m_r)-(c_1+m_1) \le r^4$

证明：

先考虑证明存在整数序列$m'_1,...,m'_r$，使得对任意$i,j,a,b$，$m'_i+c_a$与$m'_j+c_b$在模$r^3$的意义下不同余。

如果我们找到了这样的整数序列，那么所有$r^2$个$c_i+m'_j$都是两两不同的，并且由于这个是在模$r^3$意义下两两不同的，所以我们可以对第$i$个$c_i+m'_i$加上$(i-1)*r^3$，这样就可以保证对所有$i$满足$c_i+m'_i<c_{i+1}+m'_{i+1}$了。

关于$m'_1,...,m'_r$的存在性：

使用数学归纳法来证明，显然我们可以找到$m'_1$，这个平凡。

假设结论对$t$成立，即我们已经找到了$m'_1,...,m'_t$，满足对任意$1 \le i,j \le t$，$a,b$,有$m'_i+c_a$与$m'_j+c_b$在模$r^3$的意义下不同余。
可以观察到$m'_{t+1}+c_i \equiv m'_s+c_j (\mod r^3\;)$，即$m'_{t+1} \equiv m'_s+c_j-c_i (\mod r^3\;)$。


我们可以令$m'_{t+1}$是$[0,r^3)$中最小的和所有$m'_s+c_j-c_i$不同余的数，这里$1 \le s \le t,1 \le i,j \le r$。

由鸽巢原理，由于$t*r^2<r^3$，所以我们一定可以找到$m'_{t+1}$。

故当$t+1 \le s$时，结论对$t+1$成立
由数学归纳法知结论对$s$成立，同时我们这里给出了一个暴力的$O( r^4 )$的构造算法（$r$轮，每轮最坏枚举$O( r^3 )$个位置）。

## 5.融合：
融合树的"融合"即指将每个节点上的key放到同一个$w-bit$的word上，通过对这个word进行运算来一起处理这些key。

沿用之前$u_i$和$B(S)=\{c_i\}$的记号：

我们这个B-Tree的每个节点存了$C=bin(c_1,...c_r)$和$M=bin(m_1,...,m_r)$这两个量，用于计算$u'(S)$，同时还存了$D=bin(c_1+m_1,...,c_r+m_r)$这个量，用于清空$u'(S)$的计算中不需要的位。

同时还需要两个数组，存排序后的$u_i$和$u'_i$，和一个表$f[i][j][2]$表示引理$1$中，如果知道了$u_i$和$j$，还有$u$和$u_i$的大小关系，我们唯一确定的答案是多少。

回顾之前的内容，当我们算出了$j=rank(K(S),u'(S))$后，如果$u$不在$[u_j,u_{j+1}]$的区间中，那么我们把$u'(S) \;\mathrm{XOR}\; u'_j$和$u'(S) \;\mathrm{XOR}\; u'_{j+1}$比较一下，较小的值所对应的$u'_h$，$h=j$或$j+1$，和$u$有更长的公共前缀，即$msb$更小。

令$m=msb(u,u_h)$，然后我们需要知道$m$被哪个$B(S)$中的区间$[c_i,c_{i+1}]$包含，所以需要进行一次$i=rank(B(S),m)$的计算
还需要进行一次$u$和$u_h$的比较，这个平凡，当这些都做完了，我们查一下表$f$即可得到$rank(S,u)$。

可以发现fusion tree的每个内部节点需要存下$O( B^2 )$大小的表，内部节点个数是$O( n/B^4 )$个，所以是$O( n )$空间的。

下面给出对

1. $rank(K(S),u'(S))$

2. $rank(B(S),m)$，其中$m$是在$[0,w]$中的整数

3. 两个$w-bit$的整数$u,v$，$msb(u,v)$

的计算方法：

### $O(1)$计算$rank(K(S),u'(S))$：
我们把每个$K(S)$中的元素前面补一个$1$，然后从小到大拼到一起来，这个拼起来的操作就是所谓的"融合"。

由于我们$K(S)$中有$k$个元素，每个元素有$r^4$位，所以这里总共用了$k(r^4+1)$位，由于$B/2 \le k \le B$，所以我们总的位数是$O( B^5 )$的，由于$B=O( w^{1/5} )$，所以总的位数是$O( w )$的。

所以我们拼起来的这个东西是$O( 1 )$个word的，这里将其定义为$A$。

令$C=\sum \limits _{i = 0} ^ {B} 2^{(r^4+1)i}$
通过$u'(S) \times C$，可以将$u'(S)$前面补一个$0$之后复制$B$遍，然后拼到一起
通过$A-u'(S) \times C$，可以发现对每个$A$中补$1$的位置，其对应的那个$u_i(S)$如果$<u'(S)$，则这个$1$变成$0$，否则$1$不变
所以我们通过$(A-u'(S) \times C)\&C$，然后对这个word数$1$的个数即可知道$rank(K(S),u'(S))$。

由于这个word只在$2^{(r^4+1)i}$这样的位置有$1$，我们可以通过一次对$2^{r^4+1}-1$的取模来得到其中$1$的个数，虽然对常数取模可以用乘法和位运算$O(1)$实现，但我们这里可以给出一个更合适的构造。

我们可以通过将其乘$C \& (2^{(r^4+1)k}-1)$，这样相当于把其叠加了$k$次之后加起来，可以发现其中有一个长为$r^4+1$的段，这段的二进制表示的值等于这个word在$2^{(r^4+1)i}$这些位置的元素的和。

通过位移和$\mathrm{AND}$我们可以取出这个长$r^4+1$的段，于是就完成了。

答案即$((((A-u'(S) \times C) \& C) \times (C \& (2^{(r^4+1)k}-1))) \& C)>>((k(r^4+1)-1)$

### $O(1)$计算$rank(B(S),m)$，$m$是在$[0,w]$中的整数：

由于我们可以$O(1)$计算$rank(K(S),u'(S))$，所以把这个查出来然后判断那一个数的大小，并且进行一次查表即可。

### $O(1)$计算$msb(u,v)$：
等价于求$u \;\mathrm{XOR}\; v$的最高位$1$的位置，设$A=u \;\mathrm{XOR}\; v$。

我们将$A$分为$r^c$大小的块，总共$r$块，这里$c$是一个常数,$c>1$
令$C=(100...0100...0......)_2$，这里每两个$1$之间有$r-1$个$1$，$C$是一个常数。

注意到：

$((100...0)_2-0)\&(1<<(r^c)-1)=(1<<(r^c)-1)$

$((100...0)_2-y)\&(1<<(r^c)-1)=0$，这里$y>0$

先考虑对每个块去掉首位，块内是否有$1$。

我们用$A\& \sim C$可以去掉每一块的首位。

然后用$C-(A\& \sim C)$可以使得每一块中除首位外如果有$1$，则其在该块首位为$0$，否则为$1$。

然后用$(C-(A\& \sim C))\&C$去掉了$C-(A\& \sim C)$中每一块中除首位外的部分。

然后用$(C-((C-(A\& \sim C))\&C))$可以得到：如果一块中除首位外有$1$，则块首位为$1$，否则为$0$，且块首位外所有位置都是$0$的一个数
再考虑对每个块只保留首位，块内是否有$1$。

这个用$A\&C$即可。

最后$(A\&C)|(C-((C-(A\& \sim C))\&C))$可以得到：如果一块中有$1$，则块首位为$1$，否则为$0$，且块首位外所有位置都是$0$的一个数。

令$D= \sum \limits _{k=0}^{r-1} 2^{k(r^c-1)}$，

通过$(((A\&C)|(C-((C-(A\& \sim C))\&C))) \times D)>>(w-r)$可以将每块首位的数字拼到一个长$r$的二进制数中。

然后我们可以使用前面的$O(1)$计算$rank$的方法，令$B'(S)={2^i}$，$i$在$[0,r-1]$间，是整数。

通过$rank(B'(S),(((A\&C)|(C-((C-(A\& \sim C))\&C))) \times D)>>(w-r))$就可以得到这个长$r$的二进制数中第一个非0的首位的位置了。

我们知道了第一个非$0$位在哪个块中，然后查这个块里面第一个非$0$位的位置就可以了。

由于我们每个块是$r^c$的大小，所以对一个大小为$r^c$，包含了$2^i$的集合用一次rank即找到了块内第一个非$0$的首位位置。

取$c=4,r=w^{1/5}$，$r^c=w^{4/5}$，我们便$O(1)$查询，$O(w^{4/5})$预处理时间复杂度解决了这个问题，由于预处理次数是$O( n/B^4 )$，所以这里也是线性的。

综上所述，我们得到了一个单次操作复杂度$O( \log n/\log w + \log w )$的数据结构，这里**据说**可以通过一些优化做到$O( \log n/\log w )$，但在这里由于我还没看所以暂时不做介绍。

## 6.一些拓展
如果我们允许下列中的一个：

1. 放松线性空间的限制

2. 保留线性空间的限制，但是使用随机化和整数除法

那么我们可以得到一个$O( \sqrt{ \log n } )$的动态搜索的时间复杂度上界。

当$n$超过$2^{(\log w)^2/36}$时（这里$1/36$的常数是论文中给出的，由于我的部分细节和论文中不同，可能是不同的常数），

对于1的case，可以通过使用vEB树来实现，对于2的case，可以通过使用Y-fast trie实现。

对于这样的$n$，这两个数据结构可以在$O( \log \log U )=O( \log w )=O( \sqrt{\log n} )$的时间完成一次搜索操作。

当$n$小于这个数时，

对于较小的$n$，我们使用fusion tree，通过调节$B=Θ(2^ {\sqrt{\log n}})$。

在这个$B$下，我们的时间复杂度是$O( \log n/\log B + \log B ) = O( \sqrt{\log n} )$。

综上所述，如果引入随机化和整数除法，可以$O( n \sqrt{\log n} )$时间，线性空间整数排序。

## 7.总结
由信息论可以证明基于比较的排序下界是$\Omega( n\log n )$的，但整数排序其实是非常复杂的一个问题，还有待研究。

## 题目描述

魔法森林里有一颗大树，下面经常有小孩召开法。

大树可以看做一个有 $n$ 个节点，$n - 1$ 条边的无向连通图。大树的每个节点都有若干瓶矿泉水，初始第 $i$ 个节点有 $a_i$ 瓶矿泉水。

麦杰斯住在大树顶端，有一天他想改造一下大树，方便他巨大多喝水之后可以垃圾分类矿泉水瓶。

麦杰斯喜欢二进制运算，所以他会有以下三种操作：

1. 将树上与一个节点 $x$ 距离为 $1$ 的节点上的矿泉水数量 $+1$。这里树上两点间的距离定义为从一点出发到另外一点的最短路径上边的条数。
2. 在一个节点 $x$ 上喝掉 $v$ 瓶水。
3. 询问树上与一个节点 $x$ 距离为 $1$ 的所有节点上的矿泉水数量的异或和。

麦杰斯共有 $m$ 次操作，他希望你在每次 $3$ 操作后告诉他答案。

## 说明/提示

Idea：dangxingyu，Solution：dangxingyu，Code：dangxingyu，Data：dangxingyu

对于 $30\%$ 的数据，满足 $n \le 10^3$，$m\le 10^3$。

对于 $60\%$ 的数据，满足 $n \le 10^5$，$m \le 10^5$。

对于另外 $10\%$ 的数据，存在一个点满足所有点到该节点的距离 $\le 1$。

对于 $100\%$ 的数据，满足 $1\le n \le 5\times 10^5$，$1\le m \le 5\times 10^5$，$0\le a_i \le 10^5$，$1 \le x \le n$，$opt\in\{1,2,3\}$。

保证任意时刻每个节点的矿泉水数非负。

温馨提示：矿泉水瓶不是干垃圾也不是湿垃圾，而是可回收垃圾。


## 样例 #1

### 输入

```
3 2
1 2
2 3
1 1 4
1 1
3 2```

### 输出

```
5```

# 题解

## 作者：ShuYuMo (赞：36)

**UDP** On 2020/12/20 真的不是抄的OI-WiKi ……，一样是因为OI-Wiki上的这一部分内容是我写的……。更改：一处代码错误、更好的表述。

**UDP** On 2021/09/27 删除了一部分无关内容，可以参考OI-Wiki上的版本。

一些前置知识~

### 维护异或和

01-trie 是指字符集为 $\{0,1\}$ 的 trie。01-trie 可以用来维护一些数字的异或和，支持修改（删除 + 重新插入），和全局加一（即：让其所维护所有数值递增 `1` ，本质上是一种特殊的修改操作）。

如果要维护异或和，需要按值从低位到高位建立 trie。

 **一个约定** ：文中说当前节点 **往上** 指当前节点到根这条路径，当前节点 **往下** 指当前结点的子树。

#### 插入 & 删除

如果要维护异或和，我们 **只需要** 知道某一位上 `0` 和 `1` 个数的 **奇偶性** 即可，也就是对于数字 `1` 来说，当且仅当这一位上数字 `1` 的个数为奇数时，这一位上的数字才是 `1` ，请时刻记住这段文字：如果只是维护异或和，我们只需要知道某一位上 `1` 的数量即可，而不需要知道 trie 到底维护了哪些数字。

对于每一个节点，我们需要记录以下三个量：

-  `ch[o][0/1]` 指节点 `o` 的两个儿子， `ch[o][0]` 指下一位是 `0` ，同理 `ch[o][1]` 指下一位是 `1` 。
-  `w[o]` 指节点 `o` 到其父亲节点这条边上数值的数量（权值）。每插入一个数字 `x` ， `x` 二进制拆分后在 trie 上 路径的权值都会 `+1` 。
-  `xorv[o]` 指以 `o` 为根的子树维护的异或和。

具体维护结点的代码如下所示。

```cpp
void maintain(int o) {
  w[o] = xorv[o] = 0;
  if (ch[o][0]) {
    w[o] += w[ch[o][0]];
    xorv[o] ^= xorv[ch[o][0]] << 1;
  }
  if (ch[o][1]) {
    w[o] += w[ch[o][1]];
    xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
  }
  // w[o] = w[o] & 1;
  // 只需知道奇偶性即可，不需要具体的值。当然这句话删掉也可以，因为上文就只利用了他的奇偶性。
}
```

插入和删除的代码非常相似。

需要注意的地方就是：

- 这里的 `MAXH` 指 trie 的深度，也就是强制让每一个叶子节点到根的距离为 `MAXH` 。对于一些比较小的值，可能有时候不需要建立这么深（例如：如果插入数字 `4` ，分解成二进制后为 `100` ，从根开始插入 `001` 这三位即可），但是我们强制插入 `MAXH` 位。这样做的目的是为了便于全局 `+1` 时处理进位。例如：如果原数字是 `3` （ `11` ），递增之后变成 `4` （ `100` ），如果当初插入 `3` 时只插入了 `2` 位，那这里的进位就没了。

- 插入和删除，只需要修改叶子节点的 `w[]` 即可，在回溯的过程中一路维护即可。

```cpp
namespace trie {
const int MAXH = 21;
int ch[_ * (MAXH + 1)][2], w[_ * (MAXH + 1)], xorv[_ * (MAXH + 1)];
int tot = 0;
int mknode() {
  ++tot;
  ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
  return tot;
}
void maintain(int o) {
  w[o] = xorv[o] = 0;
  if (ch[o][0]) {
    w[o] += w[ch[o][0]];
    xorv[o] ^= xorv[ch[o][0]] << 1;
  }
  if (ch[o][1]) {
    w[o] += w[ch[o][1]];
    xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
  }
  w[o] = w[o] & 1;
}
void insert(int &o, int x, int dp) {
  if (!o) o = mknode();
  if (dp > MAXH) return (void)(w[o]++);
  insert(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}
void erase(int o, int x, int dp) {
  if (dp > 20) return (void)(w[o]--);
  erase(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}
}  // namespace trie
```

#### 全局加一

所谓全局加一就是指，让这颗 trie 中所有的数值 `+1` 。

形式化的讲，设 trie 中维护的数值有 $V_1, V_2, V_3 \dots V_n$ , 全局加一后 其中维护的值应该变成 $V_1+1, V_2+1, V_3+1 \dots V_n+1$ 

```cpp
void addall(int o) {
  swap(ch[o][0], ch[o][1]);
  if (ch[o][0]) addall(ch[o][0]);
  maintain(o);
}
```

我们思考一下二进制意义下 `+1` 是如何操作的。

我们只需要从低位到高位开始找第一个出现的 `0` ，把它变成 `1` ，然后这个位置后面的 `1` 都变成 `0` 即可。

下面给出几个例子感受一下：（括号内的数字表示其对应的十进制数字）

    1000(10)  + 1 = 1001(11)  ;
    10011(19) + 1 = 10100(20) ;
    11111(31) + 1 = 100000(32);
    10101(21) + 1 = 10110(22) ;
    100000000111111(16447) + 1 = 100000001000000(16448);

对应 trie 的操作，其实就是交换其左右儿子，顺着 **交换后** 的 `0` 边往下递归操作即可。

回顾一下 `w[o]` 的定义： `w[o]` 指节点 `o` 到其父亲节点这条边上数值的数量（权值）。

有没有感觉这个定义有点怪呢？如果在父亲结点存储到两个儿子的这条边的边权也许会更接近于习惯。但是在这里，在交换左右儿子的时候，在儿子结点存储到父亲这条边的距离，显然更加方便。

### 01-trie 合并

指的是将上述的两个 01-trie 进行合并，同时合并维护的信息。

可能关于合并 trie 的文章比较少，其实合并 trie 和合并线段树的思路非常相似，可以搜索“合并线段树”来学习如何合并 trie。

其实合并 trie 非常简单，就是考虑一下我们有一个 `int marge(int a, int b)` 函数，这个函数传入两个 trie 树位于同一相对位置的结点编号，然后合并完成后返回合并完成的结点编号。

考虑怎么实现？
分三种情况：

- 如果 `a` 没有这个位置上的结点，新合并的结点就是 `b` 
- 如果 `b` 没有这个位置上的结点，新合并的结点就是 `a` 
-   如果 `a` , `b` 都存在，那就把 `b` 的信息合并到 `a` 上，新合并的结点就是 `a` ，然后递归操作处理 a 的左右儿子。

     **提示** ：如果需要的合并是将 a，b 合并到一棵新树上，这里可以新建结点，然后合并到这个新结点上，这里的代码实现仅仅是将 b 的信息合并到 a 上。

```cpp
int marge(int a, int b) {
  if (!a) return b;  // 如果 a 没有这个位置上的结点，返回 b
  if (!b) return a;  // 如果 b 没有这个位置上的结点，返回 a
  /*
    如果 `a`, `b` 都存在，
    那就把 `b` 的信息合并到 `a` 上。
  */
  w[a] = w[a] + w[b];
  xorv[a] ^= xorv[b];
  /* 不要使用 maintain()，
    maintain() 是合并a的两个儿子的信息
    而这里需要 a b 两个节点进行信息合并
   */
  ch[a][0] = marge(ch[a][0], ch[b][0]);
  ch[a][1] = marge(ch[a][1], ch[b][1]);
  return a;
}
```

其实 trie 都可以合并，换句话说，trie 合并不仅仅限于 01-trie。



对于本题

每个结点建立一棵 trie 维护其儿子的权值，trie 应该支持全局加一。
       可以使用在每一个结点上设置懒标记来标记儿子的权值的增加量。
       
```cpp
using namespace std; 
namespace trie{
    const int _n = _ * 25;
    int rt[_];
    int ch[_n][2];
    int w[_n]; 
    int xorv[_n];
// w[i] is in order to save the weight of edge which is connect `i` and its `parent`.
    int tot = 0;
    void maintain(int o){
        w[o] = xorv[o] = 0;
        if(ch[o][0]){ w[o] += w[ch[o][0]]; xorv[o] ^=  xorv[ch[o][0]] << 1; }
        if(ch[o][1]){ w[o] += w[ch[o][1]]; xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1); }
    }
    inline int mknode(){ ++tot; ch[tot][0] = ch[tot][1] = 0; w[tot] = 0; return tot; }
    void insert(int &o, int x, int dp){
    	if(!o) o = mknode();
        if(dp > 20) return (void)(w[o] ++);
        insert(ch[o][ x&1 ], x >> 1, dp + 1);
        maintain(o); 
    }
    void erase(int o, int x, int dp){
        if(dp > 20) return (void )(w[o]--);
        erase(ch[o][ x&1 ], x >> 1, dp + 1);
        maintain(o);
    }
    void addall(int o){
        swap(ch[o][1], ch[o][0]);
        if(ch[o][0]) addall(ch[o][0]);
        maintain(o);
    }
}

int head[_];
struct edges{
	int node;
	int nxt;
}edge[_ << 1];
int tot = 0;
void add(int u, int v){
	edge[++tot].nxt = head[u];
	head[u] = tot;
	edge[tot].node = v;
}

int n, m;
int rt;
int lztar[_];
int fa[_];
void dfs0(int o, int f){
    fa[o] = f;
    for(int i = head[o];i;i = edge[i].nxt){
        int node = edge[i].node;
        if(node == f) continue;
        dfs0(node, o);
    }
}
int V[_];
inline int get(int x){ return (fa[x] == -1 ? 0 : lztar[fa[x]]) + V[x]; }
int main()
{
    clock_t c1 = clock();
    
    n = read(), m = read();
    for(int i = 1;i < n;i++){
        int u = read(), v = read();
        add(u, v); add(rt = v, u);
    }
    dfs0(rt, -1);
    for(int i = 1;i <= n;i++) { V[i] = read(); if(fa[i] != -1)trie::insert(trie::rt[fa[i]], V[i], 0);  }
    while(m--){
        int opt = read(), x = read();
        if(opt == 1){
            lztar[x] ++;
            if(x != rt) {

                if (fa[fa[x]] != -1) trie::erase(trie::rt[fa[fa[x]]], get(fa[x]), 0);
                V[fa[x]]++;
                if (fa[fa[x]] != -1) trie::insert(trie::rt[fa[fa[x]]], get(fa[x]), 0);
			}
            trie::addall(trie::rt[x]);
        } else if(opt == 2){
            int v = read();
            if(x != rt) trie::erase(trie::rt[fa[x]], get(x), 0);
            V[x] -= v;
            if(x != rt) trie::insert(trie::rt[fa[x]], get(x), 0);
        } else {
            int res = 0;
            res = trie::xorv[trie::rt[x]];
            res ^= get(fa[x]);
            printf("%d\n", res);
        }
    }
    std::cerr << "\n\nTime:  " << clock() - c1 << "  ms" << std::endl;
	return 0;
}
```
        

---

## 作者：FZzzz (赞：20)

抢个题解的一血吧。

话说这题也不算很难而且特别清真为啥没人做啊。

首先这种题其实是个很经典的 trick 就是对于每个点只维护它的所有儿子。然后对于父亲单独处理。对于父亲的处理是平凡的，不再赘述。

然后考虑一个节点，我们要处理的就是单点修改和全局加，然后要查询全局异或和。

好那现在我明确的告诉你这个题我不会。

……

不对啊你发现每次全局加的都是一啊，这个肯定得有用啊。

考虑加上一到底会对一个数造成什么样的影响。

不就是把最低位的零变成一然后把它下面的所有一都变成零吗，这个怎么处理啊。

我们从低位到高位建一个 trie，然后按位考虑每一位，对于零就直接把它变成一，然后对于一就变成零，但是还要递归下去。

所以我们直接就交换一下儿子然后递归下去修改，维护一下子树异或和就行了。

然后就是这样了。下面是代码，从指针改成数组版就快了一些。
```cpp
#include<algorithm>
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=5e5+5;
int n,m,a[maxn];
vector<int> g[maxn];
int fa[maxn];
void dfs(int u){
	for(int i=0;i<(int)g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs(v);
	}
}
int addv[maxn];
int sz=0,base[maxn*25],ch[maxn*25][2],xorv[maxn*25],s[maxn*25];
int newnode(int x){
	sz++;
	base[sz]=x;
	xorv[sz]=s[sz]=0;
	ch[sz][0]=ch[sz][1]=0;
	return sz;
}
void pushup(int x){
	s[x]=xorv[x]=0;
	if(ch[x][0]){
		s[x]+=s[ch[x][0]];
		xorv[x]^=xorv[ch[x][0]];
	}
	if(ch[x][1]){
		s[x]+=s[ch[x][1]];
		xorv[x]^=xorv[ch[x][1]];
		if(s[ch[x][1]]&1) xorv[x]|=1<<base[x];
	}
}
void insert(int u,int x){
	if(base[u]>20) s[u]++;
	else{
		if(x>>base[u]&1){
			if(!ch[u][1]) ch[u][1]=newnode(base[u]+1);
			insert(ch[u][1],x);
		}
		else{
			if(!ch[u][0]) ch[u][0]=newnode(base[u]+1);
			insert(ch[u][0],x);
		}
		pushup(u);
	}
}
void erase(int u,int x){
	if(base[u]>20) s[u]--;
	else{
		if(x>>base[u]&1) erase(ch[u][1],x);
		else erase(ch[u][0],x);
		pushup(u);
	}
}
void modify(int u){
	swap(ch[u][0],ch[u][1]);
	if(ch[u][0]) modify(ch[u][0]);
	pushup(u);
}
int rt[maxn];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	m=readint();
	for(int i=1;i<n;i++){
		int u,v;
		u=readint();
		v=readint();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	for(int i=1;i<=n;i++) a[i]=readint();
	for(int i=1;i<=n;i++) rt[i]=newnode(0);
	for(int i=2;i<=n;i++) insert(rt[fa[i]],a[i]);
	while(m--){
		int opt=readint();
		if(opt==1){
			int x=readint();
			addv[x]++;
			modify(rt[x]);
			if(x>1){
				if(fa[x]>1) erase(rt[fa[fa[x]]],a[fa[x]]+addv[fa[fa[x]]]);
				a[fa[x]]++;
				if(fa[x]>1) insert(rt[fa[fa[x]]],a[fa[x]]+addv[fa[fa[x]]]);
			}
		}
		else if(opt==2){
			int x,v;
			x=readint();
			v=readint();
			if(x>1) erase(rt[fa[x]],a[x]+addv[fa[x]]);
			a[x]-=v;
			if(x>1) insert(rt[fa[x]],a[x]+addv[fa[x]]);
		}
		else{
			int x=readint();
			if(x>1){
				if(fa[x]>1) printf("%d\n",xorv[rt[x]]^(a[fa[x]]+addv[fa[fa[x]]]));
				else printf("%d\n",xorv[rt[x]]^a[fa[x]]);
			}
			else printf("%d\n",xorv[rt[x]]);
		}
	}
	return 0;
}
```
~~不仅比 std 多一个 k，时间还是 std 的两倍，被卡飞。~~

~~加了个火车头终于过了。~~

---

## 作者：Cylete (赞：9)

感觉做过几次这种类似的题目

~~然而还是不会~~

有个很常见的trick是：

#### - 统一维护一个点所有儿子的异或和，单独维护父亲

考虑一个节点，我们要处理的就是**单点修改和全局加**，然后要查询**全局异或和**

我们发现对 1 个数 +1 可以看作从**低到高位的第一个 0 修改成 1，该 0 后面的 1 修改成 0**

将一个节点的所有儿子对应的数放到该节点对应的 01 trie 中进行修改的话就是

- **将 0,1 翻转后走 0 那边，然后递归地进行翻转就行**

因为本人太菜参考的其他题解的代码

具体见代码

```cpp
const int N = 5e5 + 10;

int n, m;

int cut, head[N], ver[N << 1], next[N << 1];
inline void add(int x, int y)
{
	ver[++cut] = y; next[cut] = head[x]; head[x] = cut;
}

int f[N];
inline void dfs(int x, int fa)
{
	f[x] = fa;
	for(R int i = head[x]; i; i = next[i])
	{
		int y = ver[i];
		if(y == fa) continue;
		dfs(y, x);
	}
}

int base[21 * N], ch[21 * N][2], xorv[21 * N], num[21 * N], tot;
inline int newnode(int x)
{
	tot++;
	base[tot] = x;
	ch[tot][0] = ch[tot][1] = 0;
	xorv[tot] = num[tot] = 0;
	return tot;
}

inline void pushup(int x)
{
	num[x] = xorv[x] = 0;
	if(ch[x][0])
	{
		num[x] += num[ch[x][0]];
		xorv[x] ^= xorv[ch[x][0]];
	}
	if(ch[x][1])
	{
		num[x] += num[ch[x][1]];
		xorv[x] ^= xorv[ch[x][1]];
		if(num[ch[x][1]] & 1) xorv[x] |= 1 << base[x];\\这一位为1且出现次数为奇数，则异或和为1
	}
}

inline void insert(int x, int val)\\插入
{
	if(base[x] > 20) num[x]++;
	else
	{
		if(val >> base[x] & 1)
		{
			if(!ch[x][1]) ch[x][1] = newnode(base[x] + 1);
			insert(ch[x][1], val);
		}
		else
		{
			if(!ch[x][0]) ch[x][0] = newnode(base[x] + 1);
			insert(ch[x][0], val);
		}
		pushup(x);
	}
}

inline void erase(int x, int val)\\删除
{
	if(base[x] > 20) num[x]--;
	else
	{
		if(val >> base[x] & 1) erase(ch[x][1], val);
		else erase(ch[x][0], val);
		pushup(x);
	}
}

inline void modify(int x)\\加1操作
{
	swap(ch[x][0], ch[x][1]);
	if(ch[x][0]) modify(ch[x][0]);
	pushup(x);
}

int root[N], a[N], ad[N];
int opt, x, y;

signed main()
{
	into();
	read(n); read(m);
	for(R int i = 1; i < n; i++)
	{
		read(x); read(y);
		add(x, y); add(y, x);
	}
	dfs(1, 0);
	for(R int i = 1; i <= n; i++) read(a[i]);
	for(R int i = 1; i <= n; i++) root[i] = newnode(0);
	for(R int i = 2; i <= n; i++) insert(root[f[i]], a[i]);
	while(m--)
	{
		read(opt); read(x);
       		\\暴力修改，先删去之前的 再修改值 再加回去
		if(opt == 1)
		{
			ad[x]++;
			modify(root[x]);
			if(x != 1)
			{
				if(f[x] != 1) erase(root[f[f[x]]], a[f[x]] + ad[f[f[x]]]);
				a[f[x]]++;
				if(f[x] != 1) insert(root[f[f[x]]], a[f[x]] + ad[f[f[x]]]);
			}
		}
		if(opt == 2)
		{
			read(y);
			if(x != 1) erase(root[f[x]], a[x] + ad[f[x]]);
			a[x] -= y;
			if(x != 1) insert(root[f[x]], a[x] + ad[f[x]]);
		}
        	\\分三种情况
		if(opt == 3)
		{
			if(x != 1)
			{
				if(f[x] != 1) writeln(xorv[root[x]] ^ (a[f[x]] + ad[f[f[x]]]));
				else writeln(xorv[root[x]] ^ a[f[x]]);
			}
			else writeln(xorv[root[x]]);
		}
	}
	return 0;
}
```

---

## 作者：Leap_Frog (赞：7)

### P.S.
这绝对是我 Ynoi 中代码写地最短地一题了 ![](//xn--9zr.tk/wq)。  
小跳蛙无药可救。  
### Description.
给定一棵树，要求支持以下操作。
1. 对于一个点，和它相邻地所有点权值 $+1$。
2. 单点修改一个点的权值。
3. 查询与一个点相邻所有点的异或和。

### Solution.
首先，修改/查询相邻点这个操作很奇怪。  
让我们不禁联想到了一个套路：  
每个点维护它所有孩子的权值，父亲的权值暴力修改。  
这样因为除根之外的所有点都仅有一个父亲，所以时空复杂度正确。  

然后，我们又看到了异或和操作。  
想到异或就直接想到了要用 01trie 表示异或操作。  
单点修改直接硬上 01trie 修改就好了，相当于插入一个数删除一个数。  
因为我们维护的是某个结点的 size，所以可以直接对 size --。  

不过，这两个问题结合起来就又产生了一个问题——如何对 01trie树 做全局 +1。  
正常的 01trie树 是无法处理这个问题的。  
不过我们开动人类智慧，反建 trie树。  
大概就是第一层按照最后一位分类。  
这样我们就可以暴力模拟进位了。  
大概就是首先交换左右儿子，然后对原来为 1 的那棵子 01trie 继续 +1。  
正常的 01trie 维护了大小关系，反建大小关系信息丢失。  
不过这题并不需要查询 K小 之类的问题，所以丢失了也可以解题。  

然后这题就做完了。  

### Coding.
30 行代码如下，宣传优（du）良（liu）码风。
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
const int N=500005,M=21;
int n,m,ch[N*M][2],vl[N*M],tt,sz[N*M],rt[N],lz[N],a[N];
struct edge{int to,nxt;}e[N<<1];int et,head[N],fa[N];
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
inline void pushup(int x) {sz[x]=sz[ch[x][0]]+sz[ch[x][1]],vl[x]=(vl[ch[x][0]]^vl[ch[x][1]])<<1|(sz[ch[x][1]]&1);}
inline void allr(int x) {if(!x);else swap(ch[x][0],ch[x][1]),allr(ch[x][0]),pushup(x);}
inline void insrt(int &x,int v,int dep=0) {x?x:x=++tt;if(dep==M) sz[x]++;else insrt(ch[x][(v>>dep)&1],v,dep+1),pushup(x);}
inline void erase(int &x,int v,int dep=0) {if(!x);else if(dep==M) sz[x]--;else erase(ch[x][(v>>dep)&1],v,dep+1),pushup(x);}
inline void dfs0(int x) {for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa[x]) fa[e[i].to]=x,dfs0(e[i].to);}
inline int qry(int x) {return fa[x]?lz[fa[x]]+a[x]:a[x];}
inline void Add(int x,int w) {(fa[x]?erase(rt[fa[x]],qry(x)):void()),a[x]+=w,(fa[x]?insrt(rt[fa[x]],qry(x)):void());}
inline void Mdf(int x) {lz[x]++,(fa[x]?Add(fa[x],1):void()),allr(rt[x]);}
inline void Que(int x) {printf("%d\n",vl[rt[x]]^qry(fa[x]));}
int main()
{
	read(n),read(m);for(int i=1,x,y;i<n;i++) read(x),read(y),adde(x,y),adde(y,x);
	dfs0(1);for(int i=1;i<=n;i++) read(a[i]),(fa[i]?insrt(rt[fa[i]],a[i]):void());
	for(int op,x,y;m--;) {read(op),read(x);op==1?Mdf(x):(op&1?Que(x):(read(y),Add(x,-y)));}
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：5)

lxl 说过邻域信息维护父亲一定死，所以数据结构维护每个点的儿子，特判父亲。

考虑每个点的数据结构需要支持什么操作：全局加一，单点修改，全局异或和。用 01Trie 维护。

与维护最大异或对的 01Trie 不同，从低位到高位建树，每个点上维护子树异或和，修改时 push up。

考虑怎么 push up。从 $u$ 往其 $0/1$ 子树中走到叶子形成的数，就是从 $u$ 的 $0/1$ 孩子走到叶子形成的数后面加一位 $0/1$，

所以 $u$ 子树数集包含 $u$ 的 $0$ 孩子子树数集中所有数后面加一位 $0$，$u$ 的 $1$ 孩子子树数集中所有数后面加一位 $1$，

即 $u$ 子树数集中，$u$ 的 $0$ 孩子子树异或和后面加一位 $0$；若 $u$ 的 $1$ 孩子子树数集大小为奇数，其异或和后面加一位 $1$，否则加 $0$。

考虑怎么全局加一。加一的过程实际上是从低到高按位取反，若当前位取反后为 $0$ 则继续取反下一位，

所以从上往下交换 $0/1$ 孩子，然后继续交换 $0$ 孩子的 $0/1$ 孩子。

指针非常好写。

```cpp
#include <cstdio>
#include <algorithm>
#define V(x) a[x] + z[f[x]]
#define O(x, k) if(f[x]) C(V(x), 0, r[f[x]]);a[x] += k;if(f[x]) C(V(x), 0, r[f[x]])
using namespace std;
struct E{int v, t;}e[1000050];
int n, m, c, a[500050], z[500050], f[500050], h[500050];
void A(int u, int v) {e[++c] = {v, h[u]};h[u] = c;}
struct T
{
	T *c[2];int s, w;T() : c{0, 0}, w(0) {}void u()
	{
		if(c[s = w = 0]) s ^= c[0]->s, w ^= c[0]->w << 1;
		if(c[1]) s ^= c[1]->s, w ^= c[1]->w << 1 | c[1]->s; 
	}
}*r[500050];
void C(int x, int d, T *&p)
{
	if(!p) p = new T;if(d >= 20) return void(p->s ^= 1);
	C(x, d + 1, p->c[x >> d & 1]);p->u();
}
void M(T *p) {if(p) swap(p->c[0], p->c[1]), M(p->c[0]), p->u();}
void D(int u)
{
	for(int i = h[u], v;i;i = e[i].t)
		if(!r[v = e[i].v]) C(a[v], 0, r[f[v] = u]), D(v);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v;i < n;++i)
		scanf("%d%d", &u, &v), A(u, v), A(v, u);
	for(int i = 1;i <= n;++i) scanf("%d", a + i);D(1);
	for(int i = 0, o, x, v;i < m;++i)
	{
		scanf("%d%d", &o, &x);
		switch(o)
		{
			case 1: ++z[x];M(r[x]);if(f[x]) {O(f[x], 1);}break;
			case 2: scanf("%d", &v);O(x, -v);break;
			case 3: printf("%d\n", (r[x] ? r[x]->w : 0) ^ V(f[x]));break;
		}
	}
	return 0;
}
```


---

## 作者：xiezheyuan (赞：3)

## 简要题意

你需要维护一个 $n$ 个点的树，点有点权，有 $m$ 次操作，支持：

- `1 x` 将与点 $x$ 距离为 $1$ 的所有点的点权加上 $1$。
- `2 x v` 将点 $x$ 的点权减去 $v$。
- `3 x` 求所有与点 $x$ 距离为 $1$ 的所有点的点权的异或和。

$1\leq n,m\leq 5\times 10^5,0\leq a_i\leq 10^5$。

## 思路

我愿称此为 Ynoi Educational Round。

首先观察本题，我们大致可以对于每个点，将其所有子节点塞入到某一个数据结构中，这种数据结构需要支持修改一个数的值，全局所有数加上 $1$，查询所有数的异或和。

然后对于操作 $1$，我们先对 $x$ 的所有子节点全局加上 $1$，然后单独考虑父节点。为了方便后面的维护，我们给每个点记录一个标记，表示进行了多少次邻域加 $1$ 操作，然后就可以考虑父节点对祖父节点的结构的更新。

接着是操作 $2$，我们可以直接修改在父亲的结构中的值（记得考虑），操作 $3$ 先求出所有子节点的异或和，再考虑父节点即可。

现在的问题是，如何实现一个数据结构，支持修改一个数的值，全局所有数加上 $1$，查询所有数的异或和，我们考虑 01 trie。

但是我们通常建立的维护异或极值的 01 trie 似乎难以支持全局加 $1$ 这一操作。故我们考虑**将每个数从低到高插入到 trie 中**。

由于是按照从低到高插入的，因此也可以模拟全局加 $1$ 的从低到高进位。

具体地，由于 $0+1=1,1+1=(10)_2$，所以这一位相当于取反了，所以需要**交换两个子树**，然后原本的 $1$ 子树（现在的 $0$ 子树）受到进位影响，需要继续加 $1$，递归即可。时间复杂度显然为 $O(\log V)$，代码如下：

```cpp
void update(int i){
    swap(trie[i][0], trie[i][1]);
    if(trie[i][0]) update(trie[i][0]);
    pushup(i);
}
```

然后我们需要同时维护异或和，这时我们模仿其他数据结构（线段树、平衡树等）的思想，采用**将子节点的数据上推到父节点**的方法，将所有数据上推到根节点，也就是喜闻乐见的 `pushup`。

记 $f_i$ 表示 01 trie 中以 $i$ 为根的子树所代表的 01 trie 的所有元素的异或和，那么考虑从子节点中转移，对于 $0$ 子节点的数据 $f_j$，只需要令 $f_i\gets 2f_j$ 即可。单数对于 $1$ 子节点就不一样，这一位的答案与子树的元素数量的奇偶性有关（如果为偶数，那么这一位就相消了），不妨再记录一个值，表示每个点储存的数的奇偶性，不难发现这样就可以正确求出 $f_i$ 了：

```cpp
// 这里的 xort 是 f(i)，w 是奇偶性
void pushup(int i){
    xort[i] = w[i] = 0;
    if(trie[i][0]) xort[i] ^= (xort[trie[i][0]] << 1), w[i] ^= w[trie[i][0]];
    if(trie[i][1]) xort[i] ^= (xort[trie[i][1]] << 1) | w[trie[i][1]], w[i] ^= w[trie[i][1]];
}
```

至于修改一个元素的值，可以看成先删除后插入。由于 $x\oplus x=0$，所以删除一个数 $x$ 可以看成再插入一个 $x$ 来和之前的 $x$ 的贡献相消：

```cpp
void insert(int x, int &i, int lvl=0){
    if(!i) i = ++tot;
    if(lvl > 30) return (w[i] ^= 1), void();
    insert(x >> 1, trie[i][x & 1], lvl + 1);
    pushup(i);
}
```

于是这道题就做完了。时间复杂度 $O(m\log V)$。

做完本题后可以去看看 [P6623 \[省选联考 2020 A 卷\] 树](https://www.luogu.com.cn/problem/P6623)，该题目同样也是 01 trie 维护异或和的应用，不过还要写 01 trie 合并，01 trie 合并与线段树合并类似，都是对应子树暴力合并信息：

```cpp
int merge(int x, int y){
    if(!x || !y) return x | y;
    w[x] ^= w[y], xort[x] ^= xort[y];
    trie[x][0] = merge(trie[x][0], trie[y][0]), trie[x][1] = merge(trie[x][1], trie[y][1]);
    return x;
}
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5, N_ = 2e7 + 5;

int trie[N_][2], w[N_], xort[N_], tot;

void pushup(int i){
    xort[i] = w[i] = 0;
    if(trie[i][0]) xort[i] ^= (xort[trie[i][0]] << 1), w[i] ^= w[trie[i][0]];
    if(trie[i][1]) xort[i] ^= (xort[trie[i][1]] << 1) | w[trie[i][1]], w[i] ^= w[trie[i][1]];
}

void insert(int x, int &i, int lvl=0){
    if(!i) i = ++tot;
    if(lvl > 30) return (w[i] ^= 1), void();
    insert(x >> 1, trie[i][x & 1], lvl + 1);
    pushup(i);
}

void update(int i){
    swap(trie[i][0], trie[i][1]);
    if(trie[i][0]) update(trie[i][0]);
    pushup(i);
}

int n, m, father[N], a[N], tag[N];
vector<int> g[N];
int rt[N];

void dfs(int u, int fa){
    father[u] = fa;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs(v, u);
        insert(a[v], rt[u]);
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for(int i=1,u,v;i<n;i++){
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for(int i=1;i<=n;i++) cin >> a[i];
    dfs(1, 0);
    while(m--){
        int op, x, v; cin >> op >> x;
        if(op == 1){
            update(rt[x]), tag[x]++;
            int f = father[father[x]];
            if(f) insert(a[father[x]] + tag[f], rt[f]);
            if(father[x]) a[father[x]]++;
            if(f) insert(a[father[x]] + tag[f], rt[f]);
        }
        else if(op == 2){
            cin >> v;
            if(father[x]) insert(a[x] + tag[father[x]], rt[father[x]]);
            a[x] -= v;
            if(father[x]) insert(a[x] + tag[father[x]], rt[father[x]]);
        }
        else{
            int ans = xort[rt[x]];
            ans ^= (a[father[x]] + tag[father[father[x]]]);
            cout << ans << '\n';
        }
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Little09 (赞：3)

发现每个点距离为 $1$ 的节点就是儿子或者父亲，因此可以把儿子和父亲分开来算。

计算父亲是很容易的，直接维护 $a$ 的值。对于操作 $1$ ，在父亲上标记就行了，表示这个点进行过几次的操作 $1$。

对于每个节点维护儿子，就会发现是要维护：单点加入、单点删除、全局 $+1$，全局异或和。

如果对 01-trie 比较熟悉，可以发现 01-trie 可以维护这个东西。从低位到高位建立 01-trie，大致是要维护每个节点的子树的异或和 $val$，还有每个节点到父亲的边权 $w$（指这条边被经过了几次）。

由于是异或，会发现可以只考虑 $w$ 的奇偶性。于是 push_up 大致是这样的：

```cpp
inline void push_up(int u)
{
	w[u]=0,val[u]=0;
	if (nxt[u][0])
	{
		w[u]^=w[nxt[u][0]];
		val[u]^=(val[nxt[u][0]]<<1);
	}
	if (nxt[u][1])
	{
		w[u]^=w[nxt[u][1]];
		val[u]^=(val[nxt[u][1]]<<1);
		if (w[nxt[u][1]]==1) val[u]^=1;
	}
}
```

注意到只考虑 $w$ 的奇偶性，因此 insert 和 delete 本质相同。你可以理解为，先加入一个数 $x$，要把它删除等同于再加一个 $x$，这样异或和为 $0$ 了。所以其实没有必要写两个函数（但是好像基本上题解都写了）。

如何处理全局 $+1$？从低到高考虑，每一位 $1$ 变成 $0$ 同时进位，$0$ 变成 $1$ 不进位。递归做就行了。

```cpp
void add(int x)
{
	swap(nxt[x][0],nxt[x][1]);
	if (nxt[x][0]) add(nxt[x][0]);
	push_up(x);
}
```

于是就可以维护了。注意一些实现的细节。

[提交记录](https://www.luogu.com.cn/record/61173676)。[代码实现](https://www.luogu.com.cn/paste/x2bpdqvk)。


---

## 作者：FreeTimeLove (赞：3)

## 一、题意

定义一个点的**临点**为与此点距离为 $1$ 的点的点集。

给定一棵 $n$ 个节点的树，每次给定一个点 $u$，支持单点修改，$u$ 的**临点**加 $1$，查询 $u$ 的**临点**的异或和。

## 二、思路

发现直接考虑**临点**不好处理，考虑钦定一个**根**，将**临点**分为 $u$ 的**儿子**和**父亲**。那么我们就可以对每个节点建一棵 $\text{01Trie}$ 维护**儿子**的异或和，父亲的修改可以单独处理。查询时就查询 $\text{01Trie}$ 内的答案与 $u$ 父亲的值的异或和即可。

那么**临点**加 $1$ 的操作可以拆分为 $\text{01Trie}$ 的**全局加 $1$ **和父亲的**单点修改**。先考虑如何全局加 $1$。分析**在二进制下**一个数加 $1$ 的变化可以看出，加 $1$ 实际上是将低位起一段连续的 $1$ 赋值为 $0$，再将更高一位的 $0$ 赋值为 $1$。

这里有一个 trick：我们从低位向高位建 $\text{01Trie}$，每个节点维护子树内的**数值**的个数的**奇偶**与子树内的**异或和**。在全局加 $1$ 时，我们进入一个节点，交换其 $01$ 儿子，再递归进入它的 $0$ 儿子，直到当前节点没有 $0$ 儿子。仔细观察可以发现，这其实就是对**所有数**不断将低位的 $1$ 变为 $0$，再将全 $1$ 前缀的下一个 $0$ 变为 $1$ 的过程。

注意此时 $u$ 的儿子加 $1$ 会对其**儿子的儿子**产生影响，但我们不能依次修改其儿子的值。这里可以在每个节点处记录一个 tag，更新 $u$ 的临点时将 $u$ 上的 tag 加 $1$，查询一个节点的值时要计算它的值与其**父亲**的 tag 之和。

单点修改时，计算 $u$ 的原值，在 $u$ 的父亲的 $\text{01Trie}$ 上删除，再在 $\text{01Trie}$ 上插入新值并更新 $u$ 的值即可。并且由于在 $\text{01Trie}$ 中我们只记录数值个数的奇偶与异或和，插入与删除其实并无区别。



### AC code

```cpp
//written_by_FTL
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#define ll long long
#define LD long double
#define i7 __int128
#define re return
#define con continue
using namespace std;
const int N=5e5+5;
int rd(){
	int ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
int n,m,u,v,k,rt[N],a[N],tg[N];
int nd[N],tt=1;
struct edge{
	int v,nxt;
}e[N<<1];
void add(int u,int v){
	e[++tt]={v,nd[u]};
	nd[u]=tt;
}
int f[N];
namespace TR{
	#define b ((x>>k)&1)
	#define t d[v]
	#define vl t.s[b]
	#define vr t.s[b^1]
	#define tl d[vl]
	#define tr d[vr]
	int num=0,x=0,k=0;
	struct data{
		int s[2]={0};int c=0,ans=0;
	}d[N*25];
	void pu(int v){//合并节点的值
		t.c=tl.c^tr.c;
		t.ans=(tl.ans<<1)^((tr.ans<<1)|tr.c);
	}
	void ins(int &v,int x,int k){//插入一个数
		if(!v)v=++num;
		if(k>20){t.c^=1;re;}
		ins(vl,x,k+1);
		pu(v);
	}
	void ud(int v){//全局加1
		swap(vl,vr);
		if(t.s[0])ud(t.s[0]);
		pu(v);
	}
	#undef b
	#undef t
	#undef vl
	#undef vr
}
void dfs(int u,int fa){
	f[u]=fa;
	for(int i=nd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa)con;
		dfs(v,u);
	}
}
int main(){
	n=rd(),m=rd();
	for(int i=1;i<n;i++){
		u=rd(),v=rd();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		a[i]=rd();
		if(f[i])TR::ins(rt[f[i]],a[i],0);
	}
	for(int i=1;i<=m;i++){
		switch(rd()){
			case 1:{
				u=rd();
				if(rt[u]){
					TR::ud(rt[u]);
					tg[u]++;
				}
				if(f[u]){
					u=f[u];
					v=a[u]+tg[f[u]];
					a[u]++;
					if(f[u]){
						TR::ins(rt[f[u]],v,0);
						TR::ins(rt[f[u]],v+1,0);	
					}	
				}
				break;
			}
			case 2:{
				u=rd(),k=rd();
				v=a[u]+tg[f[u]];
				a[u]-=k;
				if(f[u]){
					TR::ins(rt[f[u]],v,0);
					TR::ins(rt[f[u]],v-k,0);	
				}
				break;
			}
			case 3:{
				u=rd();
				printf("%d\n",TR::d[rt[u]].ans^(a[f[u]]+tg[f[f[u]]]));
				break;
			}
		}
	}
	re 0;
}
```

### $\text{The End.}$



---

## 作者：Gmt丶FFF (赞：2)

很久前写的，现在来补一下。

首先可以想到对于每个节点建一棵 01-trie，插入这个节点所有子节点的值，并存储每一个子树的异或和，维护这个需要在 01-trie 中 pushup，pushup 内判断 $1$ 的个数，来判断这一位是否有值，然后将左右子树的值异或起来即可。

对于操作 $1$，首先先把父亲从其父亲的父亲的 01-trie 中删除，然后再修改父亲的点权，再在父亲的父亲的 01-trie 中插入父亲，修改此节点的 01-trie 时，我们遍历整棵 01-trie，然后交换左右儿子，由于可能会有进位的情况，所以交换了后进入原来这一位为 $1$ 的子树，即现在这一位为 $0$ 的子树。最后打上懒标记，以判断一个点的点权。

对于操作 $2$，先从父亲的 01-trie 中删除，再修改点权，再插入即可。

对于操作 $3$，我们用之前说的维护的整棵树的异或和，然后再异或上父亲的值即可。

时间复杂度：$O(n\log n)$，由于整体常数很小，不需卡常都能过。比起~~毒瘤分块题~~，还是挺简单的了，需代码私。

---

## 作者：Refined_heart (赞：2)

总结一些细节上的问题，以及这一类套路。

### 题目大意

题面很简洁。

### $\text{Solution:}$

这是 `Trie` 的经典套路，全局 $+1$ 。类似的还有全局异或。

考虑 $+1$ 的影响，容易发现是把从二进制下第 $0$ 位连续的 $1$ 全部变成 $0,$ 再把下一位变成 $1$ 。

从题目开始分析，我们需要支持求全局的异或和，并且还要给每一个数都 $+1$ ，这个数据结构就必然需要和二进制的本身结构有关系。那就可以想到 `Trie` 了。

通过上述的分析容易想到 **按照二进制位从低到高** 建树。

考虑每次暴力修改，对于当前点，我们进行了 $+1$ 的操作，**当且仅当它们的父亲全部进位。** 那么如果当前点也需要 $+1$ ，容易发现它的左右孩子是需要 **调换位置** 的。直接 `swap(tr[x][0],tr[x][1])` 即可。

继续需要 $+1$ 的就是原来是 $1$ 的部分，对应现在的 `tr[x][0]` 。递归下去即可。

注意到递归到最下层是可能需要新建节点的，感觉很麻烦。——可以在建树的时候就直接把可能出现的最高位给建立出来，这样之后就不需要判断了。

继续思考，我们需要支持一个维护异或和的操作。如何维护？

容易发现，一个二进制位异或出来有贡献，当且仅当有奇数个数出现过这个数位。

于是我们就可以直接在 `Trie` 上面维护异或和了：设 `sx[x]` 表示以 $x$ 为根的子树中所有数形成的异或和。那么只有它的右孩子（也就是二进制位 $1$ 对应的节点）的 `siz` 是 $1$ 才可以继续加上这一位。否则它只能等于它孩子的异或值。

维护 `siz` 就很容易了，直接每次插入的时候走到的节点的 `siz[x]^=1` 即可。

然后考虑修改。发现修改有两种：一种修改同查询类似，一种修改是单点修改。

先考虑单点修改。如果我们维护 `val[x]` 表示 $x$ 当前的水瓶数目，那么我们可以简单地直接减掉。但是这个东西造成的其他影响我们需要看我们如何维护询问的答案。

先搞清楚，距离 $=1$ 的节点是包括父亲的，但是显然如果修改的时候要考虑到父亲就会变得很麻烦。

那不妨把父亲单独考虑。这样，一个节点维护它所有孩子节点的值组成的 `Trie` ，每次查询只需要查询出这个点的 `Trie` 维护的答案以及其父亲的水瓶数目，再异或一下即可。

那修改的时候就会涉及到其父亲维护的树，同样需要修改，我们把这个值原来的值给删掉，更新后再加进去即可。

对于第一类修改也是一样的。我们维护一个标记 `tg[x]` 表示将 $x$ 的子树点都加了多少。而对于父亲的修改可以等价于第二类修改一样暴力修改。

这样复杂度就是 $O(n\log n)$ 了。

### 实现细节

* 删除的操作不需要实现。我们维护的是异或和，利用它的性质，每次再插入一个就行了。

* 修改需要注意，每次修改是需要带上其父亲给它加的数的，这样才可以保证它父亲维护的答案正确。否则如果每次会更新值的话，维护的 `Trie` 就乱了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef double db;
//#define int long long
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
#define poly vector<int>
#define Bt(a) bitset<a>
#define bc __builtin_popcount
#define pc putchar
#define ci const int&
const int mod = 998244353;
const db eps = 1e-10;
inline int Max(ci x, ci y) {return x > y ? x : y;}
inline int Min(ci x, ci y) {return x < y ? x : y;}
inline db Max(db x, db y) {return x - y > eps ? x : y;}
inline db Min(db x, db y) {return x - y < eps ? x : y;}
inline int Add(ci x, ci y, ci M = mod) {return (x + y) % M;}
inline int Mul(ci x, ci y, ci M = mod) {return 1ll * x * y % M;}
inline int Dec(ci x, ci y, ci M = mod) {return (x - y + M) % M;}
typedef pair<int, int> pii;
inline int Abs(int x) {return x < 0 ? -x : x;}
//char buf[1<<21],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char Obuf[105000],*O=Obuf;//Siz shoule be the size of Out File
int pst[30],ptop;
inline void Fprint(){fwrite(Obuf,1,O-Obuf,stdout);}
inline void Fwrite(int x){
  if(x==0){*O++='0';if(O-Obuf>100000)Fprint(),O=Obuf;return;}
  if(x<0)*O++='-',x=-x;ptop=0;
  while(x)pst[++ptop]=x%10,x/=10;
  while(ptop)*O++=pst[ptop--]+'0';
  if(O-Obuf>100000)Fprint(),O=Obuf;
}
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') w = -1;ch = getchar();}
    while (isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
    return s * w;
}
inline void write(int x) {
    if (x < 0)putchar('-'), x = -x;
    if (x > 9)write(x / 10);
	pc(x % 10 + '0');
}
inline int qpow(int x, int y) {
    int res = 1;
    while (y) {if (y & 1)res = Mul(res, x);x = Mul(x, x);y >>= 1;}
    return res;
}
inline void cadd(int &x, int y) {x += y;}
inline void cmul(int &x, int y) {x *= y;}
inline void cmax(int &x, int y) {x = Max(x, y);}
inline void cmin(int &x, int y) {x = Min(x, y);}
const int N = 2e6 + 10;
const int SN = 23;
namespace Refined_heart{
	int n,m,head[N],tot;
	int val[N],pa[N],ad[N];
	struct E{
		int nxt,to;
	}e[N];
	inline void link(int x,int y){
		e[++tot]=(E){head[x],y};
		head[x]=tot;
	}
	const int RN = N << 3;
	int rt[N],node,tr[RN][2],siz[RN];
	int sv[RN];
	inline void pushup(int x,int dep){
		sv[x]=sv[tr[x][0]]^sv[tr[x][1]];
		if(siz[tr[x][1]])sv[x]|=(1LL<<(dep+1));
	}
	void insert(int &x,int v,int dep){
		int D=dep+1;
		if(!x)x=++node;
		siz[x]^=1;
		if(dep==SN)return;
		int nx=v>>D&1;
		insert(tr[x][nx],v,dep+1);
		pushup(x,dep);
	}
	void dfs(int x,int fa){
		pa[x]=fa;
		for(int i=head[x];i;i=e[i].nxt){
			int j=e[i].to;
			if(j==fa)continue;
			dfs(j,x);
			insert(rt[x],val[j],-1);
		}
	}
	void changeroot(int x,int dep){
		swap(tr[x][0],tr[x][1]);
		if(tr[x][0]){changeroot(tr[x][0],dep+1);}
		pushup(x,dep);
	}
	int queryroot(int x){return sv[x];}
	void change(int pos){
		if(pa[pos]){
			int vl=(pa[pa[pos]]?ad[pa[pa[pos]]]:0);
			if(pa[pa[pos]]){insert(rt[pa[pa[pos]]],val[pa[pos]]+vl,-1);}
			val[pa[pos]]++;
			if(pa[pa[pos]]){insert(rt[pa[pa[pos]]],val[pa[pos]]+vl,-1);}
		}
		ad[pos]++;
		changeroot(rt[pos],-1);
	}
	void query(int pos){
		int vl=0;
		if(pa[pos]&&pa[pa[pos]])vl=ad[pa[pa[pos]]];
		int ans=queryroot(rt[pos]);
		if(pa[pos])ans^=(val[pa[pos]]+vl);
		write(ans);pc('\n');
	}
	void solve(){
		n=read();m=read();
		for(int i=1;i<n;++i){
			int u=read(),v=read();
			link(u,v);link(v,u);
		}
		for(int i=1;i<=n;++i)val[i]=read();
		dfs(1,0);
		for(int i=1;i<=m;++i){
			int opt=read();
			if(opt==1||opt==3){
				int x=read();
				if(opt==1)change(x);
				else query(x);
			}
			else{
				int x=read(),v=read();
				int vl=(!pa[x]?0:ad[pa[x]]);
				if(pa[x])insert(rt[pa[x]],val[x]+vl,-1);
				val[x]-=v;
				if(pa[x])insert(rt[pa[x]],val[x]+vl,-1);
			}
		}
	}
}
signed main(){
// 	freopen("in.txt","r",stdin);
	Refined_heart::solve();
	return 0;
}


```

---

## 作者：Genius_Star (赞：1)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18815039)

### 思路：

对于这种邻域问题，lxl 说过维护父亲一定死；于是考虑使用某种数据结构对每个点维护其所有儿子的信息；查询时通过这个数据结构快速算出儿子的贡献后再特殊加上父亲的贡献即可。

考虑这个数据结构需要支持什么？

- 插入，删除。

- 全局 $+1$。

- 全局异或和。

有异或相关，考虑使用 01trie，但是有全局 $+1$，故考虑从低位到高位建树。

对于一个点 $u$，表示一个前缀形态 $S$（设长度为 $len$），我们设：

- `siz[u]` 表示有多少个插入进来的数前缀形态是 $u$。

- `ch[u][0/1]` 表示 $S$ 末尾添上 $0/1$ 后的形态编号。

- 同时维护 `xor[u]` 表示若只考虑 $u$ 子树内的点的异或和，即只考虑所有前缀形态为 $S$ 的数的异或和中 $> len$ 的位，即将第 $len + 1$ 位看作第 $0$ 位来做。

因为 01trie 是二叉树的结构，和线段树类似，于是考虑仿照线段树通过儿子上传合并信息：

- $siz_u = siz_{ch_{u, 0}} + siz_{ch_{u, 1}}$。

- $xor_u = 2(xor_{ch_{u, 0}} \oplus xor_{ch_{u, 1}}) + [siz_{ch_{u, 1}} \& 1]$。

那么插入与删除就很简单了，修改叶子节点，然后一路合并上传上来；查询即 $xor_{rt}$。

考虑怎么做全局 $+1$ 操作，$+1$ 其本质上是对于一个二进制数，找到从低到高的第一个 $0$ 赋值为 $1$，前面的全部清空为 $0$。

那么在 01trie 中，模拟进位：

- 若有进位下传到了 $u$ 节点（初始下传到 $rt$ 节点），那么若下一位为 $0$，直接赋值为 $1$ 后停止下传；否则下一位为 $1$，先赋值为 $0$ 然后继续下传。

其本质上是将所有前缀状态为 $u$ 的点的二进制下一位的 $0$ 与 $1$ 交换，故直接 `swap(ch[u][0], ch[u][1])` 即可；然后下传到**交换后**的 `ch[u][0]` 继续更新。

单次时间复杂度为 $O(dep)$，这里 $dep = \log W$。

故总时间复杂度为 $O(N \log W)$。

[**link**](https://www.luogu.com.cn/record/212721432)

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 5e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
namespace XorTree{
	const int M = 20 * N + 10;
	int cnt;
	int ch[M][2];
	int siz[M], sum[M]; 
	inline int newnode(){
		++cnt;
		siz[cnt] = sum[cnt] = 0;
		ch[cnt][0] = ch[cnt][1] = 0;
		return cnt;
	}
	inline void pushup(int k){
		siz[k] = siz[ch[k][0]] + siz[ch[k][1]];
		sum[k] = (siz[ch[k][1]] & 1) | ((sum[ch[k][0]] ^ sum[ch[k][1]]) << 1);
	}
	inline void insert(int k, int v, int dep){
		if(dep >= 20){
			++siz[k];
			return ;
		}
		if(!ch[k][v & 1])
		  ch[k][v & 1] = newnode();
		insert(ch[k][v & 1], v >> 1, dep + 1);
		pushup(k);
	}
	inline void del(int k, int v, int dep){
		if(dep >= 20){
			--siz[k];
			return ;
		}
		del(ch[k][v & 1], v >> 1, dep + 1);
		pushup(k);
	}
	inline void addall(int k){
		swap(ch[k][0], ch[k][1]);
		if(ch[k][0])
		  addall(ch[k][0]);
		pushup(k);
	}
	inline int askxor(int k){
		return sum[k];
	}
};
int n, m, op, x, v;
int rt[N], a[N], tag[N], fa[N];
vector<int> E[N];
inline void link(int u, int v){
	E[u].push_back(v);
	E[v].push_back(u);
}
inline void dfs(int u, int f){
	for(auto v : E[u]){
		if(v == f)
		  continue;
		fa[v] = u;
		dfs(v, u);
		XorTree::insert(rt[u], a[v], 0);
	}
}
bool End;
int main(){
	n = read(), m = read();
	for(int u, v, i = 1; i < n; ++i){
		u = read(), v = read();
		link(u, v);
	}
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		rt[i] = XorTree::newnode();
	}
	dfs(1, 0);
	while(m--){
		op = read(), x = read();
		if(op == 1){
			++tag[x];
			XorTree::addall(rt[x]);
			if(fa[fa[x]]){
				XorTree::del(rt[fa[fa[x]]], a[fa[x]] + tag[fa[fa[x]]], 0);
				++a[fa[x]];
				XorTree::insert(rt[fa[fa[x]]], a[fa[x]] + tag[fa[fa[x]]], 0);
			}
			else if(fa[x])
			  ++a[fa[x]];
		}
		else if(op == 2){
			v = read();
			if(fa[x])
			  XorTree::del(rt[fa[x]], a[x] + tag[fa[x]], 0);
			a[x] -= v;
			if(fa[x])
			  XorTree::insert(rt[fa[x]], a[x] + tag[fa[x]], 0);
		}
		else{
			write(XorTree::askxor(rt[x]) ^ (a[fa[x]] + tag[fa[fa[x]]]));
			putchar('\n');
		}
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：1)

### 分析：
题目中要求维护与给定节点距离为 $1$ 的节点的权值异或和，所以很自然的考虑对每个节点建维护其儿子的 01trie，然后对父亲单独计算。

考虑操作一，本质上就是对于一个 01trie 的全局加，考虑一开始建树时，将所有权值按从低到高位插入 01trie，那么对于全局加来讲，就是将节点的 $01$ 儿子交换，然后继续递归需要进位的儿子，继续加 $1$，最后再将左右儿子的异或值合并，得到该节点的异或值。具体来说，合并就是将 $0$ 儿子的异或值乘以 $2$，再加上 $1$ 儿子的异或值乘以 $2$，最后再根据 $1$ 儿子的子树大小的奇偶性来判断这一位上是 $0$ 是 $1$，即需不需要加 $1$。对于父亲来说，直接加 $1$ 即可，同时对父亲的父亲的 01trie 进行修改。对于所有儿子的权值维护方法，考虑对当前节点打一个标记，所有的节点的真实权值就成了自己的权值加上父亲的标记，这样即可快速维护了。

对于操作二和操作三，按照上面的方法修改和查询即可。
### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 800005 
#define p1 (tr[p].son[0])
#define p2 (tr[p].son[1])
using namespace std; 
int n,m;
int a[N],fa[N];
vector<int> g[N];
struct trie{
	int root[N];
	struct tree{
		int son[2];
		int sum;
		int xorv; 
	}tr[N*40];
	int tot=0;
	int add(){
		int id=++tot;
		tr[id].son[0]=tr[id].son[1]=tr[id].sum=tr[id].xorv=0;
		return id;
	}
	void push_up(int p){
		tr[p].sum=tr[p].xorv=0;
		if(p1!=0){
			tr[p].sum+=tr[p1].sum;
			tr[p].xorv^=(tr[p1].xorv<<1);
		} 
		if(p2!=0){
			tr[p].sum+=tr[p2].sum;
			tr[p].xorv^=(tr[p2].xorv<<1);
			tr[p].xorv|=tr[p2].sum&1;
		} 
		tr[p].sum=tr[p].sum&1;
	}
	int insert(int id,int x,int t){
		if(!id) id=add();
		if(t>25){
			tr[id].sum++;
			return id;
		}
		tr[id].son[x&1]=insert(tr[id].son[x&1],x>>1,t+1);
		push_up(id);
		return id;
	}
	void erase(int id,int x,int t){
		if(t>25){
			tr[id].sum--;
			return ;
		}
		erase(tr[id].son[x&1],x>>1,t+1);
		push_up(id);
	}
	void addall(int p){
		swap(p1,p2);
		if(p1!=0) addall(p1);
		push_up(p);
	}
}T;
void dfs(int x,int f){
	fa[x]=f;
	for(auto i:g[x]){
		if(i==f) continue;
		T.root[x]=T.insert(T.root[x],a[i],0);
		dfs(i,x);
	}
} 
int addtag[N];
main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		cin>>a[i]; 
		T.root[i]=T.add();
	}
	dfs(1,0);
	while(m--){
		int op,x,v;
		cin>>op>>x;
		if(op==1){
			T.addall(T.root[x]);
			addtag[x]++;
			if(x!=1){
				if(fa[x]!=1) T.erase(T.root[fa[fa[x]]],a[fa[x]]+addtag[fa[fa[x]]],0);
				a[fa[x]]++;
				if(fa[x]!=1) T.insert(T.root[fa[fa[x]]],a[fa[x]]+addtag[fa[fa[x]]],0);
			} 
		}
		else if(op==2){
			cin>>v;
			if(x!=1) T.erase(T.root[fa[x]],addtag[fa[x]]+a[x],0);
			a[x]-=v;
			if(x!=1) T.insert(T.root[fa[x]],addtag[fa[x]]+a[x],0);
		}
		else{
			if(x!=1){
				if(fa[x]!=1){
					cout<<(T.tr[T.root[x]].xorv^(a[fa[x]]+addtag[fa[fa[x]]]))<<'\n';
				}
				else cout<<(T.tr[T.root[x]].xorv^a[fa[x]])<<'\n';
			}
			else cout<<T.tr[T.root[x]].xorv<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：1)

## 题目大意
这个题大概就是说，给你一棵有 $n$ 个节点的树，有三种操作，共 $m$ 次：

- 将与给出的点 $x$ 距离为 $1$ 的点上的权值全都加一。

- 将给出的点 $x$ 的权值 $-v$。

- 输出所有与给出的点 $x$ 距离为 $1$ 的点的权值异或和。
## 大体思路
（若不理解，边看文字边看代码可能会好一些）。

### 准备工作
首先先建树，按正常思路我们先把题目给出的树按父子关系建出来，这里使用邻接表，然后深搜把每个点的父亲求出来，一般来讲，这道题空间开 $25$ 倍就够了。

看到问题涉及“异或和”，我们考虑一下 01-trie。

我们开始建树，没有这个节点就新加一个，为了怕他进位之后让我们多加结点，我们强制性的让他每一个数字有 $20$ 位（最大能达到 $1048576$，因为我们最多有 $10^5+5\times 10^5$ 这么大，留 $2^{20}$ 足矣）,然后我们一位一位的往后递归，将这个数的整个二进制全都建了，然后后面的补 $0$，直到大于二十，给 $w$ 标记一下就返回，之后回溯会向上传，相当于维护了个差分数组。

过程中，我们记得维护结点，往上传你现在的权值 $w$，然后维护异或和，由于 trie 上维护的只是一个个数字，而并不会体现在哪一位，所以每次处理都要左移一位，才能体现出我比我儿子的位数多，否则就和儿子的低位异或掉了，答案是明显错误的。

注意一点，由于异或的性质是奇数个相同的异或为 $1$，偶数个为 $0$，维护异或和的时候，我们只需要注意 $0$ 和 $1$ 的数量即可，若当前数值为 $1$ 且边被经历的次数为奇数（也就是说儿子里面这一位为 $1$ 的有奇数个），则该位的异或值为 $1$。

### 操作

万事俱备，只欠东风，我们开始处理他的操作吧。

- 第一个操作——全局 $+1$：

我们首先要知道，在二进制中加一，就是从低位到高位找第一个 $0$，把他变成 $1$，再把后面的 $1$ 全都变成 $0$，首先打个懒标记，由于要修改离自己距离为 $1$ 的点，由于我们维护的是子树的异或和，所以我们要修改当前节点父亲，然后可以下传下来，我们的操作是先把父亲从父亲的父亲那里删掉，然后重新加载一下父亲，然后向下传即可，在遍历整棵 0-1trie 的时候要交换左右儿子。

- 第二个操作——单点修改：

比较简单，和上一个不同的是，我们只需要从当前节点的父亲上删掉当前节点，修改后再加上即可。

- 第三个操作——询问：

正常求距离为 $1$ 的异或和，我们只需要把维护的他的子树和他的父亲一起异或了就可以了。

**代码中有详细用法解析，若要参考代码请认真阅读我所定义的变量及函数意义。**

本题轻度卡常，如果超时了可以把部分操作替换成位运算，本题解是 AC 代码。
## Code
```cpp
#include<bits/stdc++.h>//注意注释中树上以及 trie 上的区别 
using namespace std;
vector<int> t[500005];//记录的父子关系
int fa[500005];//各点在树上的父亲信息
int a[500005];//权值
int w[12500005];//trie 上该节点到父亲结点经过的边数 
int root[500005];//各数所对应树的根节点的位置
int tot;//当前点给到哪一个了，加了新点的下标是多少
int tr[12500005][5];//建立的 01trie，第一维是指结点编号，第二维指这一位是 0/1
int xo[12500005];//以该节点为根的子树的异或和 
int laz[500005];//懒标记，在修改的时候会下传
int q(int x){
	if(fa[x]==0){
		return a[x];
	}
	return a[x]+laz[fa[x]];
}
void xf(int x){//处理完后面的维护该结点，后面的结点会对该节点的部分数值产生影响
	w[x]=0;//初始化一下，要从下向上加 
	xo[x]=0;//子树的异或和也会有影响，毕竟修改了数值
	if(tr[x][0]){
		w[x]+=w[tr[x][0]];//加权，上传
		xo[x]^=(xo[tr[x][0]]<<1);//处理子树的异或和，为了位数要左移 
	}
	if(tr[x][1]){
		w[x]+=w[tr[x][1]];//加权，上传
		xo[x]^=(xo[tr[x][1]]<<1)|(w[tr[x][1]]%2);//不一样的是，如果这条边被经历了奇数次（这一位为 1 的有奇数个）且权值为 1，则异或和为 1，毕竟是异或，欧数次就是 0 了 
	}
}
void xg(int& r,int v,int dep){
	if(!r){
		r=++tot;//没有这个节点就新加一个
	}
	if(dep>20){
		w[r]++;//超过强制给的二十位了，+1 到时候往上回溯 
		return ;//没必要继续处理了
	}
	xg(tr[r][v%2],v/2,dep+1);//类似“短除”得出其二进制，然后递归下，后面的会自动补 0 
	xf(r);//他后面的点处理完之后就要维护该节点了，结点的 w 要往上传的 
}
void sc(int& r,int v,int dep){
	if(dep>20){
		w[r]--;//xg 的反操作 
		return ;
	}
	sc(tr[r][v%2],v/2,dep+1);//遍历下去 
	xf(r);//在 trie 中下放 
}
void dfs(int x,int f){
	fa[x]=f;
	for(auto v:t[x]){
		if(v==f){
			continue ;
		}
		dfs(v,x);
	}
}
void fz(int x){
	swap(tr[x][0],tr[x][1]);
	if(tr[x][0]){//没找到 0 
		fz(tr[x][0]);//继续顺着操作 
	}
	xf(x);//下放一下 
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		t[u].push_back(v);
		t[v].push_back(u);//记录父子关系
	}
	dfs(1,0);//正常搜索，找到父亲 
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(fa[i]){//避免超界，fa[i]不存在，之后都是这样的 
			xg(root[fa[i]],a[i],0);//对这个权值进行建点
		}
	}
	while(m--){//开始处理操作
		int op;
		cin>>op;
		if(op==1){//操作 1——全局 +1 
			int x;
			cin>>x;
			laz[x]++;
			if(fa[x]){//这些 if 都防止越界 
				if(fa[fa[x]]){
					sc(root[fa[fa[x]]],q(fa[x]),0);//先删掉父亲 
				}
				a[fa[x]]++;//修改之后 
				if(fa[fa[x]]){
					xg(root[fa[fa[x]]],q(fa[x]),0);//再把父亲加回来 
				}
			}
			fz(root[x]);//然后开始遍历反转后面的 1 
		}
		else if(op==2){//操作 2——单点修改 
			int x,y;
			cin>>x>>y;
			if(fa[x]){
				sc(root[fa[x]],q(x),0);//删自己 
			}
			a[x]-=y;//减掉 
			if(fa[x]){
				xg(root[fa[x]],q(x),0);//再加进去 
			}
		}
		else{
			int x;
			cin>>x;
			int ans=xo[root[x]];
			ans^=q(fa[x]);
			cout<<ans<<'\n';
		}
	} 
	return 0;
}
```

---

## 作者：CPPfive (赞：1)

写一篇题解来纪念我自己 ac 的第一道 Ynoi 的题目。
## 题目分析
对于这一类涉及与一个点相邻的所有点的树上问题，有一个常用的 trick 是将父亲结点单独处理。对于这道题，我们查询异或和的时候将子结点的异或和查出来后再异或上父亲结点就可以了。

所以我们的问题变成了：如何维护子结点的异或和？我们来看题目需要支持的两种修改操作：
 
 1.将与一个点相邻的所有点都加 $1$。
 
 2.将一个点减去一个值。
 
~~很显然~~第一个操作看上去更加困难一些，所以我们先考虑如何实现第一个操作。

我们发现，当我们把一个数加 $1$ 的时候，如果把这个数看成二进制，那么它改变的仅仅是它最后一个 $0$ 的右边部分（包括这个 $0$）。实际上对一个二进制数加 $1$，就相当于把这个数的最后一个 $0$ 以及它的右边部分全部取反。

当很多个数同时进行上述操作时，我们想到可以用 0-1trie 树来维护。对每个结点分别建一个 trie 树（维护这个结点的所有子结点，注意每个数是倒序插入），如果我们认为左结点对应 $0$，右结点对应 $1$ 的话，每一次操作的时候从当前结点访问右儿子（当然是交换前的右儿子），每到一个结点就把这个结点的左右儿子结点交换，直到当前结点没有右儿子为止结束，此时 trie 树里就已经完成了每个数加 $1$ 的任务（想一想，为什么）。

最后，我们还需要做的事情就是在完成上述操作的同时维护异或和。当我们交换一次左右儿子结点时，实际上只对异或和的某一位有影响。如果这次取反的数的数量是奇数，那么异或和的这一位也取反，如果是偶数，那就不会有影响。所以我们在 trie 树上记录经过某一个点的数的个数，当我们交换一个结点的左右儿子时，改变的数的个数就是经过这个结点的数的个数。

到这里我们已经解决了子结点的异或和的问题了，但是别忘了，我们还要维护父亲结点。我们不能把每一个相邻的结点的值一个一个加 $1$，那样显然太慢了。所以我们可以在这个结点上打标记，当我们查询一个结点的值的时候，顺便查询一下它的父结点（如果有的话）是否有标记就可以了。

以上就是本题的大致思路了。如果您理解了第一个操作，那么第二个操作也是非常简单的。如果您没有看懂关于 trie 树的操作，那么强烈建议您画一张 trie 树手玩一下，然后再来看本题解。

最后一个小提示：插入 trie 树的时候记得把每一个数都补成相同的长度，这样可以避免很多多余的操作。

## 代码
```cpp
//洛谷P6018 

#include <bits/stdc++.h>
using namespace std;
const int MAXN=500050,MAXS=10000050;
int son[MAXS][2],cnt[MAXS],xsum[MAXN],tot;
int tcnt[MAXN],a[MAXN],fa[MAXN];
int N,M;
int h[MAXN],to[MAXN<<1],nxt[MAXN<<1],tot1;

void insert(int rt,int x){
	++cnt[rt];xsum[rt]^=x;
	for(int i=0;i<=19;++i){
		if(!son[rt][1&(x>>i)]) son[rt][1&(x>>i)]=++tot;
		rt=son[rt][1&(x>>i)];++cnt[rt]; 
	}
}
void del(int rt,int x){
	--cnt[rt];xsum[rt]^=x;
	for(int i=0;i<=19;++i){
		rt=son[rt][1&(x>>i)];--cnt[rt];
	}
}
bool find(int rt,int x){
	for(int i=0;i<=19;++i){
		if(!cnt[son[rt][1&(x>>i)]]) return 0;
		rt=son[rt][1&(x>>i)];
	}
	return 1;
}
void reverse(int rt){
	int i=0,t=rt;
	for(int j=0;j<=19;++j){
		swap(son[t][0],son[t][1]);
		xsum[rt]^=(cnt[t]%2)?(1<<i):0;
		t=son[t][0];
		if(!cnt[t]) return;
		++i;
	}
}

void add(int u,int v){
	to[++tot1]=v;nxt[tot1]=h[u];h[u]=tot1;
}
void dfs(int x,int f){
	fa[x]=f;
	for(int i=h[x];i;i=nxt[i]){
		if(to[i]==f) continue;
		dfs(to[i],x);
		insert(x,a[to[i]]); 
	}
}
int getval(int x){
	if(!fa[x]) return a[x];
	return a[x]+tcnt[fa[x]];
}

int main()
{
	scanf("%d%d",&N,&M);
	tot=N;
	for(int i=1;i<N;++i){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	for(int i=1;i<=N;++i) scanf("%d",&a[i]);
	dfs(1,0);
	for(int i=1;i<=M;++i){
		int opt;scanf("%d",&opt);
		if(opt==1){
			int x;scanf("%d",&x);
			++tcnt[x];
			if(fa[x]){
				int t=fa[x];
				if(fa[t]){
					del(fa[t],a[t]+tcnt[fa[t]]);++a[t];insert(fa[t],a[t]+tcnt[fa[t]]);
				}
				else ++a[t];
			}
			reverse(x);
		}
		else if(opt==2){
			int x,v;scanf("%d%d",&x,&v);
			if(fa[x]){
				del(fa[x],getval(x));a[x]-=v;insert(fa[x],getval(x));
			}
			else a[x]-=v;
		}
		else{
			int x;scanf("%d",&x);
			int ans=0;if(fa[x]) ans^=getval(fa[x]);
			ans^=xsum[x];printf("%d\n",ans); 
		}
	}
	
	return 0;
}
```


---

## 作者：yangdezuo (赞：1)

## 题目描述
给你一棵 $n$ 个结点的树，每个结点有权值。$m$ 次操作。需要支持以下操作。

将树上与一个节点 $x$ 距离为 $1$ 的节点上的权值 $+1$。这里树上两点间的距离定义为从一点出发到另外一点的最短路径上边的条数。
在一个节点 $x$ 上的权值 $-v$。
询问树上与一个节点 $x$ 距离为 $1$ 的所有节点上的权值的异或和。对于 $100\%$ 的数据，满足 $1\le n \le 5\times 10^5$，$1\le m \le 5\times 10^5$，$0\le a_i \le 10^5$，$1\le x \le n$，$opt\in\{1,2,3\}$。保证任意时刻每个节点的权值非负。
## 题解
每个结点建立一棵 trie 维护其儿子的权值，trie 应该支持全局加一。可以使用在每一个结点上设置懒标记来标记儿子的权值的增加量。（别看这是紫题，其实还好）
## 简单贴个代码
```cpp
#include <bits/stdc++.h>//万能头
using namespace std;
const int _ = 5e5 + 10;

namespace trie {
const int _n = _ * 25;
int rt[_];
int ch[_n][2];
int w[_n];  //`w[o]` 指节点 `o` 到其父亲节点这条边上数值的数量（权值）。
int xorv[_n];
int tot = 0;

void maintain(int o) {  // 维护w数组和xorv（权值的异或）数组
  w[o] = xorv[o] = 0;
  if (ch[o][0]) {
    w[o] += w[ch[o][0]];
    xorv[o] ^= xorv[ch[o][0]] << 1;
  }
  if (ch[o][1]) {
    w[o] += w[ch[o][1]];
    xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
  }
}

int mknode() {  // 创造一个新的节点
  ++tot;
  ch[tot][0] = ch[tot][1] = 0;
  w[tot] = 0;
  return tot;
}

void insert(int &o, int x, int dp) {  // x是权重，dp是深度
  if (!o) o = mknode();
  if (dp > 20) return (void)(w[o]++);
  insert(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}

void erase(int o, int x, int dp) {
  if (dp > 20) return (void)(w[o]--);
  erase(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}

void addall(int o) {  // 对所有节点+1即将所有节点的ch[o][1]和ch[o][0]交换
  swap(ch[o][1], ch[o][0]);
  if (ch[o][0]) addall(ch[o][0]);
  maintain(o);
}
}  // namespace trie

int head[_];

struct edges {
  int node;
  int nxt;
} edge[_ << 1];

int tot = 0;

void add(int u, int v) {
  edge[++tot].nxt = head[u];
  head[u] = tot;
  edge[tot].node = v;
}

int n, m;
int rt;
int lztar[_];
int fa[_];

void dfs0(int o, int f) {  // 得到fa数组
  fa[o] = f;
  for (int i = head[o]; i; i = edge[i].nxt) {  // 遍历子节点
    int node = edge[i].node;
    if (node == f) continue;
    dfs0(node, o);
  }
}

int V[_];

int get(int x) { return (fa[x] == -1 ? 0 : lztar[fa[x]]) + V[x]; }  // 权值函数

int main() {
  cin >> n >> m;
  while(1){//防复制
  	cout<<"别抄";
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);  // 双向建边
    add(rt = v, u);
  }
  dfs0(rt, -1);  // rt是随机的一个点
  for (int i = 1; i <= n; i++) {
    cin >> V[i];
    if (fa[i] != -1) trie::insert(trie::rt[fa[i]], V[i], 0);
  }
  while (m--) {
    int opt, x;
    cin >> opt >> x;
    if (opt == 1) {
      lztar[x]++;
      if (x != rt) {
        if (fa[fa[x]] != -1) trie::erase(trie::rt[fa[fa[x]]], get(fa[x]), 0);
        V[fa[x]]++;
        if (fa[fa[x]] != -1)
          trie::insert(trie::rt[fa[fa[x]]], get(fa[x]), 0);  // 重新插入
      }
      trie::addall(trie::rt[x]);  // 对所有节点+1
    } else if (opt == 2) {
      int v;
      cin >> v;
      if (x != rt) trie::erase(trie::rt[fa[x]], get(x), 0);
      V[x] -= v;
      if (x != rt) trie::insert(trie::rt[fa[x]], get(x), 0);  // 重新插入
    } else {
      int res = 0;
      res = trie::xorv[trie::rt[x]];
      res ^= get(fa[x]);
      printf("%d\n", res);
    }
  }
  return 0;//结束
}

```


---

## 作者：chen_qian (赞：1)

**update：修改了一些改了一点小错误，并更加详细的提供了说明。感谢[大佬](https://www.luogu.com.cn/user/130387)指出不详细的地方**

对于树上的一个节点，距离其为 $1$ 的节点他的儿子和父亲，所以对于每一个点维护一个 trie 树，然后暴力修改其父亲信息即可。

所以我们要支持的操作就是：

- 删除

- 插入

- 全局加一

- 求异或和

本题解代码写法与 OIwiki 上的相似，主要的是解释一下 trie 树维护信息时自己的一些理解。

```cpp
int newnode(){
	int x=++tot;
	ch[x][0]=ch[x][0]=0;
	w[x]=0;
	return x;
}
void push_up(int x){
	w[x]=xorv[x]=0;
  	if(ch[x][0]){
    	w[x]+=w[ch[x][0]];
    	xorv[x]^=(xorv[ch[x][0]]<<1);
  	}
  	if(ch[x][1]) {
    	w[x]+=w[ch[x][1]];
    	xorv[x]^=(xorv[ch[x][1]]<<1)|(w[ch[x][1]]&1);
  	}
  	//w[x]=w[x]&1;
}
void insert(int &p,int x,int dep){
	if(!p) p=newnode();
	if(dep>20){
		w[p]++;
		return ;
	}
	insert(ch[p][x&1],x>>1,dep+1);
	push_up(p);
}
void erase(int &p,int x,int dep){
	if(dep>20){
		w[p]--;
		return ;
	}
	erase(ch[p][x&1],x>>1,dep+1);
	push_up(p);
}
void add(int p){
	swap(ch[p][1],ch[p][0]);
  	if(ch[p][0]) add(ch[p][0]);
  	push_up(p);
}
```

以上是 trie 树的代码。首先你要明白 trie 树上的端点是不存储信息的，实际上存储信息的是边。我们这里从**低位到高位**进行存储数字，即下图

![](https://cdn.luogu.com.cn/upload/image_hosting/0xgrianr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


这样存储就以为着我们在计算当前的节点 $x$ 的子树的异或和时，子节点的 $y$ 的异或和需要前移一位。这里异或和是用 $xorv_x$ 来表示的。

那么对于每一个边，如果这条边的被经历的次数是奇数次且这条边的权值为 $1$ 那么这一位的异或和才会是 $1$。所以我们就要知道每一条边被经历了多少次。记 $w_x$ 表示 $x$ 到其父亲的边经过了多少次。

显然我们每插入一个数，其到根节点的路径上的 $w_x$ 都要加一，如何完成这个操作呢，实际上，我们套用一个前缀和的思想，直接将最底端的 $w_x$ 加一，然后回溯时加上即可。

剩下的就比较简单了。

整体加 $1$ 操作则是我们从低位到高位开始找第一个出现的 0，把它变成 1，然后这个位置后面的 1 都变成 0 即可。

```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int ch[25*N][2],w[25*N],tot,xorv[25*N],root[N],lazy[N],v[N];
int n,m;
int newnode(){
	int x=++tot;
	ch[x][0]=ch[x][0]=0;
	w[x]=0;
	return x;
}
void push_up(int x){
	w[x]=xorv[x]=0;
  	if(ch[x][0]){
    	w[x]+=w[ch[x][0]];
    	xorv[x]^=(xorv[ch[x][0]]<<1);
  	}
  	if(ch[x][1]) {
    	w[x]+=w[ch[x][1]];
    	xorv[x]^=(xorv[ch[x][1]]<<1)|(w[ch[x][1]]&1);
  	}
}
void insert(int &p,int x,int dep){
	if(!p) p=newnode();
	if(dep>20){
		w[p]++;
		return ;
	}
	insert(ch[p][x&1],x>>1,dep+1);
	push_up(p);
}
void erase(int &p,int x,int dep){
	if(dep>20){
		w[p]--;
		return ;
	}
	erase(ch[p][x&1],x>>1,dep+1);
	push_up(p);
}
void add(int p){
	swap(ch[p][1],ch[p][0]);
  	if(ch[p][0]) add(ch[p][0]);
  	push_up(p);
}
struct edge{
	int v,next;
}e[N*2];
int head[N],idx;
void addedge(int u,int v){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
}
int fa[N];
void dfs(int x,int f){
	fa[x]=f;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==f) continue;
		dfs(y,x);
	}
}
int get(int x){
	return fa[x]==0?v[x]:lazy[fa[x]]+v[x];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		addedge(a,b);
		addedge(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		scanf("%d",&v[i]);
		if(fa[i]) insert(root[fa[i]],v[i],0);
	}
	while(m--){
		int op,x,y;
		scanf("%d%d",&op,&x);
		if(op==1){
			lazy[x]++;
			if(fa[x]){
				if(fa[fa[x]]) erase(root[fa[fa[x]]],get(fa[x]),0);
				v[fa[x]]++;
				if(fa[fa[x]]) insert(root[fa[fa[x]]],get(fa[x]),0);
			}
			add(root[x]);
		}
		if(op==2){
			scanf("%d",&y);
			if(fa[x]) erase(root[fa[x]],get(x),0);
			v[x]-=y;
			if(fa[x]) insert(root[fa[x]],get(x),0);
		}
		if(op==3){
			int res=0;
			res^=xorv[root[x]];
			int ans=get(fa[x]);
			res^=ans;
			printf("%d\n",res);
		}
	}
	return 0;
}
```





---

## 作者：liruixiong0101 (赞：0)

又是一道包含了很多经典 trick 的题目。

---

看到操作 13，想到维护每个点周围的点的点权的 01 trie，操作 1 就是 01trie 全局加一，操作二就是查询全局异或和，也就是 [P6623 [省选联考 2020 A 卷] 树](https://www.luogu.com.cn/problem/P6623)。

但是这样显然是不正确的，因为这样操作 1 还会影响到父亲的父亲和儿子的儿子，儿子的儿子是无法维护的，我们应该换一种方式考虑。

这个做法做不了的原因是我们既维护了儿子的信息，又维护了父亲的信息，导致一个节点的信息改了需要操作很多的 01trie，我们不妨将一个 01trie 所需要维护的信息减少，一个 01trie 只维护其儿子的信息，那么就很好处理了，操作 1 只会修改自己和自己的父亲的父亲（父亲的父亲可以暴力修改），操作 3 可以查询儿子点权的异或和在和父亲异或一下即可。

现在我们来考虑操作 2，有了前面的铺垫这个操作就很简单了，我们发现操作 2 只会修改其父亲的 01 trie 的某一个数，我们直接暴力修改即可。

到这里我们还会遇到一个小问题，就是在暴力修改的时候，我们需要知道一个点的点权，每一次修改我们还要维护每一个点的点权。这里我们可以维护被 2 操作和 1 操作父亲单点加的点权，和因为 1 操作被父亲所加的点权，这两个数相加就是实际点权。

```cpp
#include <bits/stdc++.h>
#define Val(u) (u ? a[u] + af[fa[u]] : 0)

using namespace std;

const int kMaxN = 5e5 + 5, kL = 20, kMaxV = 2e7;

int n, m, a[kMaxN], af[kMaxN], fa[kMaxN], tot, root[kMaxN], nex[kMaxV][2], ss[kMaxV], sx[kMaxV];
//  a : 单点加的点权 / af : 1 操作加的点权 / ss : 子树和 / sx : 子树异或和
vector<int> g[kMaxN];

int NewNode() { return ++tot; }

void PushUp(int u) {
  ss[u] = ss[nex[u][0]] + ss[nex[u][1]];
  sx[u] = 2 * (sx[nex[u][0]] ^ sx[nex[u][1]]) + ss[nex[u][1]] % 2;
}

void Insert(int &u, int dep, int x) {
  !u && (u = NewNode());
  if (dep == kL) return (ss[u]++, sx[u] = 0, (void)0);
  Insert(nex[u][x >> dep & 1], dep + 1, x);
  PushUp(u);
}

void Delete(int u, int dep, int x) {
  if (dep == kL) return (ss[u]--, (void)0);
  Delete(nex[u][x >> dep & 1], dep + 1, x);
  PushUp(u);
}

void Replace(int u, int x, int y) {
  if (u) Delete(u, 0, x), Insert(u, 0, y);
}

void Change(int u, int dep) {  // +1
  if (!u || dep == kL) return;
  Change(nex[u][1], dep + 1);
  swap(nex[u][0], nex[u][1]);
  PushUp(u);
}

void Dfs(int u, int f) {
  fa[u] = f;
  for (int v : g[u]) {
    if (v != f) {
      Dfs(v, u), Insert(root[u], 0, a[v]);
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Dfs(1, 0);
  for (int o, x, y; m; m--) {
    cin >> o >> x;
    if (o == 1) {
      Change(root[x], 0), Replace(root[fa[fa[x]]], Val(fa[x]), Val(fa[x]) + 1), af[x]++, a[fa[x]]++;
    } else if (o == 2) {
      cin >> y, Replace(root[fa[x]], Val(x), Val(x) - y), a[x] -= y;
    } else {
      cout << (sx[root[x]] ^ Val(fa[x])) << '\n';
    }
  }
  return 0;
}
```

---

## 作者：Coffee_zzz (赞：0)

对于每个结点，特殊处理其父亲，用 trie 维护其所有儿子的权值的异或和，在 trie 上做单点修改，并利用懒标记做全局加 $1$ 即可。

---

用 trie 维护一些数的异或和是简单的，只需要对于 trie 上的每个结点 $u$ 维护下列信息：

- 该结点到其父亲结点之间的边被经过的次数 $w_u$；
- 以该结点为根的子树内的数的异或和 $x_u$。

直接转移即可。

---

在 trie 上做全局加 $1$ 也是简单的，只需要从低位到高位维护，每次交换当前结点的左右儿子，并对交换后 $0$ 侧的儿子继续递归即可。

注意这样做只在该结点维护的 trie 中做了加 $1$ 操作，需要给父亲结点的权值加 $1$，并给当前结点的懒标记加 $1$。记得在父亲结点的父亲结点的 trie 中对父亲结点的权值进行单点修改。

```cpp
#include <bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int N=6e5,L=20;
int n,m,tot,fa[N],a[N];
int nxt[N*22][2],tag[N],w[N*22],x[N*22];
vei ve[N];
void dfs(int u,int f){
	fa[u]=f;
	for(auto v:ve[u]){
		if(v==f) continue;
		dfs(v,u);
	}
}
void maintain(int u){
	w[u]=x[u]=0;
	if(nxt[u][0]){
		w[u]+=w[nxt[u][0]];
		x[u]^=x[nxt[u][0]]<<1;
	}
	if(nxt[u][1]){
		w[u]+=w[nxt[u][1]];
		x[u]^=(x[nxt[u][1]]<<1)|(w[nxt[u][1]]&1);
	}
}
void insert(int &u,int x,int dp){
	if(!u) u=++tot;
	if(dp==L) w[u]++;
	else insert(nxt[u][x&1],x>>1,dp+1),maintain(u);
}
void erase(int u,int x,int dp){
	if(dp==L) w[u]--;
	else erase(nxt[u][x&1],x>>1,dp+1),maintain(u);
}
void add(int u){
	if(u==0) return;
	swap(nxt[u][0],nxt[u][1]);
	add(nxt[u][0]);
	maintain(u);
}
int get(int u){
	if(fa[u]) return a[u]+tag[fa[u]];
	else return a[u];
}
void solve(){
	cin>>n>>m;
	tot=n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		ve[u].pb(v);
		ve[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int u=2;u<=n;u++) insert(fa[u],get(u),0);
	for(int i=1;i<=m;i++){
		int op,u;
		cin>>op>>u;
		if(op==1){
			add(u);
			if(fa[fa[u]]) erase(fa[fa[u]],get(fa[u]),0);
			if(fa[u]) a[fa[u]]++;
			tag[u]++;
			if(fa[fa[u]]) insert(fa[fa[u]],get(fa[u]),0);
		}
		else if(op==2){
			int v;
			cin>>v;
			if(fa[u]) erase(fa[u],get(u),0);
			a[u]-=v;
			if(fa[u]) insert(fa[u],get(u),0);
		}
		else{
			if(fa[u]) cout<<(get(fa[u])^x[u])<<endl;
			else cout<<x[u]<<endl;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：happybob (赞：0)

操作与一个点相邻的所有点，考虑以 $1$ 为根 DFS，然后将每个这样的点分为其父亲和儿子考虑。注意到父亲只有一个，考虑只维护儿子的答案，父亲特判处理一下即可。

考虑我们要做什么操作？单点修改，全局 $+1$，求全局异或值。考虑 01-Trie 维护。单点修改就是删一个数加一个数，容易维护，全局异或值可以考虑算每一位的贡献。具体地，插入时从低位到高位插入，考虑每个点维护以这个点为根的插入时结尾点数量，`pushup` 时直接合并左右两子树的点数量。同时维护 $s$ 表示以这个点为根的子树全部数异或，上传时考虑往 $1$ 这条边走时，如果点数是奇数就加上贡献。具体可以看代码：

```cpp
void pushup(int u)
{
	tr[u].sum = tr[u].cnt = 0;
	if (tr[u].son[0])
	{
		tr[u].cnt += tr[tr[u].son[0]].cnt;
		tr[u].sum = tr[tr[u].son[0]].sum << 1;
	}
	if (tr[u].son[1])
	{
		tr[u].cnt += tr[tr[u].son[1]].cnt;
		tr[u].sum ^= (tr[tr[u].son[1]].sum << 1) | (tr[tr[u].son[1]].cnt & 1);
	}
}
```

其中左移 $1$ 的原因是我们从低往高位插，考虑这个点事实上是末尾加入了一个 $0$ 或 $1$。

全局异或即根节点的 $sum$ 值。

现在考虑全局 $+1$ 怎么维护。似乎有些困难，因为 01-Trie 基于二进制，于是我们考虑 $+1$ 在二进制下的意义。其实是将最低的 $0$ 位变成 $1$，然后让这个位右边全都变成 $0$。也就是将最低的 $0$ 位右边全部取反。

其实就是从根节点开始，每次尝试往 $1$ 的边走，如果能走就走，并且交换 $0$ 和 $1$ 的边。

于是整个题就做完了，特别注意处理父亲节点的贡献。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int N = 5e5 + 5, M = 21;

int rt[N];
int fa[N];
vector<int> son[N];
vector<int> G[N];
int n, m;
int a[N];
int cnt[N], c2[N];

void dfs(int u, int f)
{
	fa[u] = f;
	for (auto& j : G[u])
	{
		if (j != f)
		{
			dfs(j, u);
			son[u].emplace_back(j);
		}
	}
}

inline int qry(int u)
{
	int res = a[u] + c2[u] + (fa[u] ? cnt[fa[u]] : 0);
	return res;
}

class Trie
{
public:
	int idx;
	struct Node
	{
		int cnt, sum;
		int son[2];
	}tr[2 * N * M];
	void pushup(int u)
	{
		tr[u].sum = tr[u].cnt = 0;
		if (tr[u].son[0])
		{
			tr[u].cnt += tr[tr[u].son[0]].cnt;
			tr[u].sum = tr[tr[u].son[0]].sum << 1;
		}
		if (tr[u].son[1])
		{
			tr[u].cnt += tr[tr[u].son[1]].cnt;
			tr[u].sum ^= (tr[tr[u].son[1]].sum << 1) | (tr[tr[u].son[1]].cnt & 1);
		}
	}
	void ins(int& rt, int x)
	{
		if (!rt) rt = ++idx;
		int u = rt;
		vector<int> v;
		for (int i = 0; i <= 20; i++)
		{
			v.emplace_back(u);
			int p = ((x >> i) & 1);
			if (!tr[u].son[p]) tr[u].son[p] = ++idx;
			u = tr[u].son[p];
		}
		tr[u].cnt++;
		for (int i = v.size() - 1; i >= 0; i--) pushup(v[i]);
	}
	void del(int& rt, int x)
	{
		int u = rt;
		vector<int> v;
		for (int i = 0; i <= 20; i++)
		{
			v.emplace_back(u);
			int p = ((x >> i) & 1);
			u = tr[u].son[p];
		}
		tr[u].cnt--;
		for (int i = v.size() - 1; i >= 0; i--) pushup(v[i]);
	}
	void add(int u)
	{
		swap(tr[u].son[0], tr[u].son[1]);
		if (tr[u].son[0]) add(tr[u].son[0]);
		pushup(u);
	}
}tr;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
	{
		for (auto& j : son[i]) tr.ins(rt[i], a[j]);
	}
	while (m--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int u;
			cin >> u;
			tr.add(rt[u]);
			int rm = qry(fa[u]);
			cnt[u]++;
			if (fa[u]) c2[fa[u]]++;
			if (fa[fa[u]])
			{
				tr.del(rt[fa[fa[u]]], rm);
				tr.ins(rt[fa[fa[u]]], rm + 1);
			}
		}
		else if (op == 2)
		{
			int u, x;
			cin >> u >> x;
			int rm = qry(u);
			if (fa[u])
			{
				tr.del(rt[fa[u]], rm);
				tr.ins(rt[fa[u]], rm - x);
			}
			a[u] -= x;
		}
		else if (op == 3)
		{
			int u;
			cin >> u;
			int res = (fa[u] ? qry(fa[u]) : 0);
			res ^= tr.tr[rt[u]].sum;
			cout << res << "\n";
		}
	}
	return 0;
}
```


---

## 作者：xfrvq (赞：0)

两年前一点也不会的。现在会了就留题解权当纪念吧。

---

套路地对每个点维护其儿子的信息。父亲单独处理。

至于怎么维护单点修改/全局加一/全局异或和？考虑对于每个点为其所有儿子建立**低位到高位**的 01 Trie，然后全局加一相当于如下过程：

+ 从 Trie 树的根开始 dfs。
+ 对于当前点的 $0$ 儿子，考虑**在这一位加一**，即将其存到 $1$ 儿子上。
+ 对于当前点的 $1$ 儿子，考虑**加一后会进位**，故将其存到 $0$ 儿子上，并**递归处理为这个 $0$ 儿子子树加一**。
+ 注意到上述过程仅涉及**交换儿子，改变 Trie 树形态**，不涉及**新建/删除节点**。

然后单点修改暴力做，全局异或和套路地拆位，对于每个二进制位维护 Trie 树中**有多少这一位为 0/1 的数**。注意到全局加一操作时要**动态修改维护的信息**。这时考虑换一个点的 0/1 儿子时发生了什么（这个子树产生的**这一位的 0/1 贡献**互换了）。而这个贡献就是**它的 0/1 儿子分别的子树大小**，随便维护即可。

代码不难写。注意叶子节点不用维护儿子信息，根节点不在我们维护的范畴（即 $a_1$ 不在 Trie 树上）要分开维护。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int n,m,a[N],fa[N],pos[N];
int rt[N],C[2][40 * N],F[40 * N],S[2][20][N],T[40 * N],tot;
vector<int> G[N];

int ins(int x,int u){
	int p = rt[u];
	for(int i = 0,j;i < 20;++i){
		if(!C[j = x >> i & 1][p]) F[C[j][p] = ++tot] = p;
		++T[p = C[j][p]],++S[j][i][u];
	}
	return p;
}

void ers(int p,int u){
	for(int i = 19;~i;--i)
		--S[p == C[1][F[p]]][i][u],--T[p],p = F[p];
}

void add(int u){
	T[0] = 0; 
	for(int i = 0,p = rt[u];p && i < 20;++i)
		S[0][i][u] += T[C[1][p]] - T[C[0][p]],
		S[1][i][u] += T[C[0][p]] - T[C[1][p]],
		swap(C[0][p],C[1][p]),p = C[0][p];
}

int ask(int p,int s = 0){
	for(int i = 19;~i;--i)
		s |= (p == C[1][F[p]]) << i,p = F[p];
	return s;
}

int qry(int u,int s = 0){
	for(int i = 0;i < 20;++i)
		s |= (S[1][i][u] & 1) << i;
	return s;
}

void dfs(int u,int ft){
	if(!ft || G[u].size() != 1) rt[u] = ++tot;
	for(int v : G[u]) if(v != ft)
		pos[v] = ins(a[v],fa[v] = u),dfs(v,u);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1,u,v;i < n;++i)
		scanf("%d%d",&u,&v),
		G[u].push_back(v),G[v].push_back(u);
	for(int i = 1;i <= n;++i) scanf("%d",a + i);
	dfs(1,0);
	for(int o,p,x;m--;){
		scanf("%d%d",&o,&p);
		if(o == 1){
			if(rt[p]) add(p);
			if(x = fa[p]){
				if(x == 1) ++a[1];
				else {
					a[x] = ask(pos[x]) + 1;
					ers(pos[x],fa[x]);
					pos[x] = ins(a[x],fa[x]);
				}
			}
		} else if(o == 2){
			scanf("%d",&x);
			if(p == 1) a[1] -= x;
			else {
				a[p] = ask(pos[p]) - x;
				ers(pos[p],fa[p]);
				pos[p] = ins(a[p],fa[p]);
			}
		} else {
			int s = rt[p] ? qry(p) : 0;
			if(p == 1 || fa[p] == 1) printf("%d\n",s ^ a[fa[p]]);
			else printf("%d\n",s ^ ask(pos[fa[p]]));
		}
	}
	return 0;
}
```

---

## 作者：Phartial (赞：0)

# [Ynoi2010] Fusion tree 题解

题意：给你一棵点带权的无根树，你需要支持以下操作：

1. 给一个点的所有邻居的权值加一（以下称该操作为邻居加）；
2. 单点修改；
3. 查询一个点的所有邻居的权值的异或和（以下称该操作为查询邻居异或和）。

令 $1$ 为根，对于一次对 $x$ 的邻居加操作，我们可以直接修改 $x$ 的父亲，并对 $x$ 的儿子打上加法 tag，这样我们就做到了维护每一个点的值。

考虑如何查询 $x$ 的邻居异或和，我们可以用一棵 01-trie 来维护 $x$ 的儿子的权值，那么我们需要支持以下操作：插入、删除、全局异或和、全局加 $1$。

前三个操作都很好做，对于第四个操作，注意到如果我们从低位到高位建 01-trie 的话，加 $1$ 就会有很好的性质：它总是将当前节点的 $0$ 子树和 $1$ 子树交换，然后给新的 $0$ 子树里的点加 $1$。由于树高是 $\mathcal{O}(\log V)$ 的，所以全局加 $1$ 的时间复杂度是 $\mathcal{O}(\log V)$ 的。

那么我们现在已经能维护 $x$ 的儿子的异或和了，直接把 $x$ 的父亲也加进去就行了。

总时间复杂度 $\mathcal{O}(n+m\log V)$。

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int kN = 5e5 + 1, kV = 2e5 + 1, kL = 18;

struct E {
  int c[2], s, x;
} t[kN * kL];
int n, q, a[kN], ta[kN], f[kN], rt[kN], c;
vector<int> e[kN];

void D(int x, int _f) {
  f[x] = _f;
  for (int i : e[x]) {
    if (i != _f) {
      D(i, x);
    }
  }
}
void Pu(int x) {
  E &p = t[x], &l = t[p.c[0]], &r = t[p.c[1]];
  p.x = ((l.x ^ r.x) << 1) ^ (r.s & 1);
  p.s = l.s + r.s;
}
void I(int &r, int v, int cv) {
  static int s[kL], tp = 0;
  if (!r) {
    r = ++c;
  }
  int x = r;
  for (int i = 0; i < kL; ++i) {
    s[tp++] = x;
    int &y = t[x].c[v >> i & 1];
    if (!y) {
      y = ++c;
    }
    x = y;
  }
  t[x].s += cv;
  for (; tp; Pu(s[--tp])) {
  }
}
void A(int x) {
  if (!x) {
    return;
  }
  swap(t[x].c[0], t[x].c[1]);
  A(t[x].c[0]);
  Pu(x);
}
int G(int i) { return a[i] + ta[f[i]]; }
void A(int x, int v) {
  if (x > 1) {
    I(rt[f[x]], G(x), -1);
  }
  a[x] += v;
  if (x > 1) {
    I(rt[f[x]], G(x), 1);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    e[x].push_back(y), e[y].push_back(x);
  }
  D(1, 0);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 2; i <= n; ++i) {
    I(rt[f[i]], a[i], 1);
  }
  for (int o, x, v; q--;) {
    cin >> o >> x;
    if (o == 1) {
      ++ta[x];
      if (x > 1) {
        A(f[x], 1);
      }
      A(rt[x]);
    } else if (o == 2) {
      cin >> v;
      A(x, -v);
    } else {
      cout << (t[rt[x]].x ^ G(f[x])) << '\n';
    }
  }
  return 0;
}
```


---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给定一颗带点权的树，要求支持以下操作：

- 将与一个点相邻的点的点权加一

- 修改一个点的点权

- 查询与一个点相邻节点的异或和

## 题目分析

与一个点相邻的点是一个反直觉的题设。不过可以很容易想到将其转为儿子加父亲。

而对于异或和来讲，可以用 trie 树维护。这样后两个操作其实都很板，关键在第一个操作。

对于第一个操作，父亲相当于单点修改。而对于儿子则是要全局加 $1$。加一这个东西和二进制结合在一起看起来就很可做了。简单模拟发现，对于一个二进制数，加一相当于将其低位连续的 $1$ 置 $0$，并将从低位起第一个 $0$ 置 $1$，这在 trie 树上是非常好模拟的，每次交换 $0$ 儿子和 $1$ 儿子，然后递归处理 $0$ 儿子即可。

不过这时候修改儿子不能直接修改其点权，导致要查询其点权时有麻烦。但可以发现一个点只有在其父亲要被操作才会出现这种麻烦，用一个懒标记记录即可。复杂度 $O(n\log V)$，其中 $V$ 表示点权可能的最大值。

- 补充

这题虽然没怎么卡常数，但还是可以优化一下自己的代码的。

很多同学都用左右儿子的信息合并成当前节点的信息，根节点的信息就是答案。但可以注意到，对于每个 trie 树，要知道所有元素的异或和，只需要知道每个深度中 $1$ 节点的 siz 之和的奇偶性。所以可以直接统计这个值。但在 $1$ 操作时，我们还要记录两个儿子的 siz，这个用标记永久化可以使得代码效率高很多，这样没有 pushup 的函数调用，代码也更为丝滑，轻松拿到[最优解](https://www.luogu.com.cn/record/132549143)。比第二快了很多。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =5e5+5;
using namespace std; 
int n=read(),m=read(),tot=n,root[N],laz[N],h[N],a[N],to[N<<1],nxt[N<<1],cnt; 
bool ct[N][21];
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
struct node{
	int son[2];
	bool siz;
}trie[M]; 
inline void insert(int rt,int x){
	if(!rt)return;
	int pr=rt;
	rep(p,0,19){
		ct[pr][p]^=x&1,trie[rt].siz^=1;
		if(!trie[rt].son[x&1])trie[rt].son[x&1]=++tot;
		rt=trie[rt].son[x&1],x>>=1;
	}
}
inline void Plus(int now,int rt,int p){
	if(!now)return;
	swap(trie[now].son[0],trie[now].son[1]);
	if(trie[trie[now].son[0]].siz^trie[trie[now].son[1]].siz)ct[rt][p]^=1;
	Plus(trie[now].son[0],rt,p+1);
}
inline int query(int x){
	int ans=0;
	rep(i,0,19)ans+=ct[x][i]<<i;
	return ans;
}
int f[N];
inline int got(int x){
	if(!x)return 0;
	return a[x]+laz[f[x]];
}
inline void dfs(int x,int fa){
	root[x]=x,f[x]=fa;
	e(x)if(y^fa)insert(x,a[y]),dfs(y,x);
}
inline void modify(int x,int k){ 
	if(!x)return; 
	insert(f[x],got(x)),a[x]+=k,insert(f[x],got(x));
}
int main(){
    for(int i=1,x,y;i^n;i++)x=read(),y=read(),add(x,y),add(y,x);
	rep(i,1,n)a[i]=read();
	dfs(1,0);
	for(int i=1,opt,x;i<=m;i++){
		opt=read(),x=read();
		if(opt==1)laz[x]++,Plus(x,x,0),modify(f[x],1);
		else if(opt==2)modify(x,-read());	
		else pf(query(x)^got(f[x])),putchar('\n'); 
	}
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：0)

对于树上领域问题，考虑拆为父亲和儿子两部分分别处理。

1. 父亲

这时我们需要维护出每个点的权值。

对于一般的数据结构，如果要修改，那么它必然得是连续的区间。而修改所有儿子的话，显然用 $dfn$ 序之类的东西，它是不连续的。

现在，我们试图找到所有儿子之间的共性。你会发现，对于它的所有儿子，我们发现它们的深度是相同的，并且在 dfs 的顺序下，在该深度，该节点的所有儿子深度是连续的。

区间加单点查，我们可以对每个深度分别开树状数组维护，每个节点算一次，总长度是 $O(n)$ 的。

2. 儿子

我们发现区间 $+1$ 区间异或仍然是不好做的，注意到 $+1$ 的区间和查询的区间只有每个节点的所有儿子对应的区间。这启发我们单独维护每个节点的儿子的信息，因为每个节点在此时指挥对它父亲贡献一次所以仍然是 $O(n)$ 的，这时我们就把区间问题转化为了全局问题。

对于异或，考虑在 Trie 上处理。$2$ 操作我们先用前面的树状数组查询出这个点当前的权值后把它从 Trie 里面删掉然后修改后再插回去。现在很棘手的问题就在于，$1$ 操作怎么处理，对于异或的查询，只需要维护每一位有多少个 $1$ 即可。

注意到直接全局加全局异或不是很好维护，所以我们应该从这个 $+1$ 入手。

在二进制下，一个数 $+1$ 相当于找到这个数最低位的 $0$，然后把它和更低位全部取反。

注意到本题并不需要比较大小关系，所以我们按照上面的性质，从低到高存显然是更便于处理的。

对于取反，就是在 Trie 上交换左右儿子。也就是说，这个操作我们可以在 Trie 上交换一个节点的左右儿子后，原来往 $0$ 走的方向不用取反，原来往 $1$ 走的方向要取反，那么我们继续递归原来往 $1$ 的方向（即现在往 $0$ 的方向）即可。

---

