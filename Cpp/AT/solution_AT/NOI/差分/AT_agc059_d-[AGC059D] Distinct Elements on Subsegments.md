# [AGC059D] Distinct Elements on Subsegments

## 题目描述

给定一个整数序列 $A=(A_1,\ A_2,\ \ldots,\ A_{N+K-1})$（$1 \leq A_i \leq N+K-1$），对于每个 $i$，定义 $B_i$ 为 $A_i, A_{i+1}, \ldots, A_{i+K-1}$ 这 $K$ 个数中不同元素的个数，得到序列 $B=(B_1,\ B_2,\ \ldots,\ B_N)$。

给定 $B_1, B_2, \ldots, B_N$，判断是否存在一个序列 $A$ 能够生成该序列 $B$，如果存在，请构造出任意一个满足条件的 $A$。

对于每个输入文件，需要解答 $T$ 个测试用例。

## 说明/提示

### 限制条件

- $1 \leq T \leq 5 \cdot 10^4$
- $2 \leq N \leq 2 \cdot 10^5$
- $2 \leq K \leq 2 \cdot 10^5$
- $1 \leq B_i \leq K$
- 每个输入文件中所有 $N$ 的总和不超过 $2 \cdot 10^5$。
- 每个输入文件中所有 $K$ 的总和不超过 $2 \cdot 10^5$。
- 输入中的所有值均为整数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 3
1 2 1
4 3
1 2 2 1
6 4
3 3 3 3 3 3```

### 输出

```
NO
YES
1 1 1 2 2 2 
YES
1 2 3 1 2 3 1 2 3```

# 题解

## 作者：arundo (赞：3)

[AGC059D] Distinct Elements on Subsegments 题解。

尝试给一个人类可能想到的过程。

首先会有的想法是，$B$ 数组的 $\Delta$（$\Delta_i=B_{i+1}-B_i$）只能为 $0/\pm 1$，否则无解。

进一步考察 $\Delta$，会发现对于 $\pm 1$ 都能找到确定的对应关系，即 $\Delta_i=+1$ 时 $A_{i+1\sim i+K-1}$ 中存在 $A_i$ 且不存在 $A_{i+K}$，$\Delta_i=-1$ 时 $A_{i+1\sim i+K-1}$ 中不存在 $A_i$ 且存在 $A_{i+K}$。但 $\Delta_i=0$ 时对应关系是不确定的，即 $A_i$ 和 $A_{i+K}$ 有两种可能关系（同时存在或不存在）。

那么，先假定我们知道了每种关系选择什么。如何判断此时是否有解？

一个直观的感受是，左边的一个点要和右边的一些点中某个相同，意味着也应该存在对称的“右边的一个点和左边的一些点中某个相同”的关系。

形式化以上描述，令所有满足 $A_{i+1\sim i+K-1}$ 中存在 $A_i$ 的 $i$ 构成集合 $\{L\}$，并类比定义 $\{R\}$。则刚才的想法即为将所有 $\{L\}$ 和 $\{R\}$ 内元素匹配起来，使得它们互相满足。

容易发现此时 $|\{L\}|$ 和 $|\{R\}|$ 必须相等，而匹配一定一一对应匹配最优，否则交换可能导致额外的 $R_i-L_i\ge K$。

形式化地说，当且仅当两集合个数相同且 $\forall i,R_i-L_i\ge K$ 时，$A$ 存在解。

如果满足以上条件，可以从前向后，贪心为每个 $A_i$ 选择颜色，以此构造解（若不在 $\{R\}$ 中则新开一个颜色，否则选择其匹配的 $L$ 的颜色）。容易证明这样的过程唯一且合法。

最后解决遗留的问题：为每个 $\Delta_i=0$ 选择方案。

首先注意到，因为数最多只有 $K$ 个，所以当 $B_i=K$ 时，选择的一定是同时不存在。

事实上，或许可以猜测到，对于其他的 $\Delta_i=0$，直接让其选择同时存在一定可以覆盖到所有情况。证明考虑若其同时不存在，因为 $B_i<K$，所以 $A_{i+1\sim i+K-1}$ 中必定存在一对 $x<y$ 使得 $A_x=A_y$，此时 $L_n=x$ 与 $R_m=y$ 匹配。如果将其当前状态转为存在，则转而匹配 $(i,x)$ 与 $(y,i+K)$，其一定不劣。

因此按照上述方法构造 $\{L\}$、$\{R\}$ 后，判断是否有解并构造方案即可。

注意特殊处理前 $K$ 个对 $\{R\}$ 和后 $K$ 个对 $\{L\}$ 的贡献，这是平凡的。贪心选择尽量靠近中间的即可。

---

## 作者：zhiyin123 (赞：2)

一个直观的图论题解。

# Distinct Elements on Subsegments【题解】【AGC059D】

## 约定

**集合** $[t]$（$t\in\mathbb{N}^+$）表示集合 $\{1,2,\dots,t\}$。

## 正文

首先，序列 $b$ 要满足:

- $\forall i$，$1\leq b_i\leq k$。
- $\forall i$，$|b_i-b_{i-1}|\leq 1$。

这是显然的。如果不满足，就一定无解。在后面的讨论中，不妨默认序列 $b$ 已经满足这两个条件。

因为 $a_i$ 的**值域限制很宽松**，为 $[n+k-1]$，所以我们可以加强给序列 $a$ 赋值的限制，假设序列 $a$ 中值为 $v$ 的位置恰为 $p_1,p_2,\dots,p_k$（$p_1<p_2<\cdots<p_k$）（即有且仅有 $p_1,p_2,\dots,p_k$ 满足 $a_{p_1}=a_{p_2}=\cdots=a_{p_k}=v$），那么我们**不允许**出现 $i$ 满足

$$
p_i+k\leq p_{i+1}
$$

否则，我们就可以直接给序列 $a$ 的 $p_{i+1},p_{i+2},\dots,p_k$ 位置**赋上新的值**。这么做显然不会让合法的序列 $a$ 变得不合法（合法指能生成出给定的序列 $b$）。 

我们可以把序列 $a$ 看做**若干条链交错**构成的序列，其中，$\forall i\in[1,n+k-1]$，$i$ 代表**图** $G$ 中的节点 $i$；而 $\forall i\neq j$，节点 $i$ 和节点 $j$ 在同一条**链**上，当且仅当 $a_i=a_j$；令图 $G$ 中所有边都**从编号小的节点连向编号大的节点**。

例如，序列 $a$ 是

$$
1,2,5,3,4,3,3,5,4,2
$$

时，所对应的图 $G$ 为

![graph1](https://cdn.luogu.com.cn/upload/image_hosting/4cuyi1t4.png)

每个节点上都写着节点的索引，第 $i$ 个节点的**颜色**代表 $a_i$。（如果您是色觉障碍者，那实在是对不起了 qwq）

这样做有什么好处呢？其实，根据序列 $b$，我们可以**直接确定一些节点入度为 $0$，一些节点出度为 $0$**。

具体来讲：

- 如果 $b_{i-1}+1=b_{i}$，那么 $G$ 中的 $i+k-1$ 号节点**一定是一条链的开头**，入度为 $0$。
- 如果 $b_{i-1}-1=b_i$，那么 $G$ 中的 $i-1$ 号节点**一定是一条链的结尾**，出度为 $0$。

当然，因为图 $G$ 中仅有若干条链，所以一个节点的入度（或出度）要么是 $0$ 要么是 $1$。

这里不妨设第 $i$ 个节点的入度为 $in(i)$，出度为 $out(i)$。

由上面的启发，我们考虑构造出所有 $i$ 的 $in(i)$ 和 $out(i)$，然后再由此构造出序列 $a$。

什么样的 $in(i)$ 和 $out(i)$ 是合法的呢？首先，它们有如下限制：

1. $\{1,2,\dots,k\}$ 中**恰好**有 $b_1$ 个整数 $i$ 满足 $in(i)=0$。
2. $\{n,n+1,\dots,n+k-1\}$ 中**恰好**有 $b_n$ 个整数 $i$ 满足 $out(i)=0$。

不妨设第 $j$ 个 $in(i)=1$ 的 $i$ 为 $X(j)$（即 $\{1,2,\dots,X(j)\}$ 中恰好有 $j$ 个整数 $t$ 满足 $in(t)=1$），第 $j$ 个 $out(i)=1$ 的 $i$ 为 $Y(j)$。

为了能让各个点的入度和出度**完美匹配**，要满足：

3. 若 $\{1,2,\dots,n+k-1\}$ 中**恰好**有 $x$ 个整数 $i$ 满足 $in(i)=1$，**恰好**有 $y$ 个整数 $j$ 满足 $out(j)=1$，那么**一定有** $x=y$。
4. $\forall i$，$1\leq X(i)-Y(i)<k$。小于 $k$ 是因为，一开始我们对给序列 $a$ 赋值**添加的限制**。

以及序列 $b$ 的差分带来的限制

5. 若 $b_{i-1}<b_i$，则 $out(i-1)=0,in(i+k-1)=1$；
6. 若 $b_{i-1}=b_i$，则有两种情况
	- 若 $b_i=k$，则 $out(i-1)=0,in(i+k-1)=0$；（这是因为子段中的数互不相同）
	- 若 $b_i<k$，则 $out(i-1)=in(i+k-1)$。
7. 若 $b_{i-1}>b_i$，则 $out(i-1)=1,in(i+k-1)=0$。

容易发现，限制 $3$ 是**多余的**，当其他限制满足是，自然就能构造出若干条链。

那么，我们需要努力满足的限制就是限制 $4$，其要求

$$
\forall i,1\leq X(i)-Y(i)<k
$$

而我们**有一定自由性的限制**为限制 $1,2,6$。具体的

1. 直接令 $in(1)=in(2)=\cdots=in(b_1)=0$。
2. 直接令 $out(n+k-b_n)=out(n+k-b_n+1)=\cdots=out(n+k-1)=0$。
3. 若 $b_{i-1}=b_i$ 且 $b_i<k$，直接令 $out(i-1)=in(i+k-1)=1$。

这么做的话，对于满足限制 $4$ 来说，显然是**不劣的**。

于是，我们就构造出了 $in(i)$ 和 $out(i)$。

如果我们验证这个构造满足限制 $4$ 的话，就能构造出一个合法的 $a$ 序列。

构造序列 $a$ 的过程十分简单，我们让变量 $i$ 从 $1$ 遍历到 $n+k-1$，同时在遍历的构成中构造 $a_i$，则可分为下面的情况讨论：

- 若 $in(i)=0$，则直接给 $a_i$ 赋一个与 $a_1,a_2,\dots,a_{i-1}$ **均不同**的新值。
- 若 $in(i)=1$，则可先找到一个**唯一的** $j$，满足 $X(j)=i$（可以通过 $O(n+k)$ 预处理整数函数 $X$ 的逆函数，做到 $O(1)$ 查询），然后，令 $a_i$ 为 $a_{Y(j)}$。

最后，总复杂度为 $O(n+k)$。

## 代码

```cpp
#include<bits/stdc++.h>
using std::cerr; using std::setw; using std::endl;
using std::cin; using std::cout;
template<typename Tp>
Tp mabs(const Tp &x){return x<0?-x:x;}
using ll=long long;
constexpr int MAXN=2e5,MAXK=2e5;
int N,K,B[MAXN+5],A[MAXN+MAXK+5];
bool in[MAXN+MAXK+5],out[MAXN+MAXK+5];
int X[MAXN+MAXK+5],Y[MAXN+MAXK+5],Id[MAXN+MAXK+5];
bool solve(){
    cin>>N>>K; for(int i=1;i<=N;i++) cin>>B[i];
    if(*std::min_element(B+1,B+N+1)<1) return 0;
    if(*std::max_element(B+1,B+N+1)>K) return 0;
    for(int i=2;i<=N;i++) if(mabs(B[i]-B[i-1])>1) return 0;
    std::fill(in+1,in+N+K,1); std::fill(out+1,out+N+K,1);
    for(int i=2;i<=N;i++){
        if(B[i-1]+1==B[i]){
            in[i+K-1]=0;
        }else if(B[i-1]-1==B[i]){
            out[i-1]=0;
        }else{
            if(B[i]==K){
                in[i+K-1]=0;
                out[i-1]=0;
            }
        }
    }
    std::fill(in+1,in+B[1]+1,0);
    std::fill(out+N+K-B[N],out+N+K,0);
    std::fill(Id+1,Id+N+K,0);
    int xcnt=0,ycnt=0;
    for(int i=1;i<=N+K-1;i++) if(in[i])  X[++xcnt]=i;
    for(int i=1;i<=xcnt;i++) Id[X[i]]=i;
    for(int i=1;i<=N+K-1;i++) if(out[i]) Y[++ycnt]=i;
    for(int i=1;i<=xcnt;i++){
        int d=X[i]-Y[i];
        if(!(1<=d&&d<K)) return 0;
    }
    for(int i=1,c=0;i<=N+K-1;i++){
        if(in[i]==0){
            A[i]=++c;
        }else{
            A[i]=A[Y[Id[i]]];
        }
    }
    return 1;
}
int main(){
    std::ios::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
    int T; cin>>T;
    for(int t=1;t<=T;t++){
        if(solve()){
            cout<<"YES"<<'\n';
            for(int i=1;i<=N+K-1;i++) cout<<A[i]<<' ';
            cout<<'\n';
        }else{
            cout<<"NO"<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：Felix72 (赞：1)

设位置 $i$ 的元素为“右-重要的”，当且仅当 $[i, i + k - 1]$ 里它的颜色独一无二，此时记 $f_i = 1$；同理可以定义“左-重要的”，此时记 $g_i = 1$。

考虑 $b_i$ 和 $b_{i + 1}$ 的关系，他们的差一定不能大于一。则转化条件，有：

- 如果 $b_i = b_{i + 1}$，则 $f_i = g_{i + k}$；
- 如果 $b_i + 1 = b_{i + 1}$，则 $f_i = 1, g_{i + k} = 0$；
- 如果 $b_i - 1 = b_{i + 1}$，则 $f_i = 0, g_{i + k} = 1$。

把能确定的先确定了，继续思考合法的条件。这个 $f$ 和 $g$ 肯定形成了某种对应关系，我们继续挖掘一下。考虑最后可能的一个合法序列，令 $rn_i$ 为右边第一个颜色和 $ans_i$ 相同的元素，没有即 $\inf$。同理定义 $ln_i$。我们可知 $f_i, g_i$ 的值与 $rn_i, ln_i$ 的值直接相关，且又因为 $rn$ 和 $ln$ 一一对应（你在我的右边第一个，我就在你的左边第一个），所以记录 $f_x = 1$ 的集合 $\{x\}$，$g_y = 1$ 的集合 $\{y\}$，$x, y$ 之间一一对应。

我们构造一组合法的 $x, y$ 就可以了。先前已经确定了很多 $f, g$，我们就考虑维护两个指针 $i, j : 1 \to n + k - 1$，$i$ 在前 $j$ 在后，每次 $g_i = 1$ 就是需要匹配了，我们移动 $j$ 知道 $j \in [i - k + 1, i]$ 且 $f_j = 1$ 或 $f_j$ 未确定，然后把他们匹配起来，如果 $f_j$ 未确定，那就在确定它的同时把 $g_{j + k} = 1$。

这个贪心策略是很好证明的。匹配完之后，我们已经知道哪些元素相等，并查集扫一遍就出答案了。

---

## 作者：UnyieldingTrilobite (赞：1)

对于题目所述的序列 $A$，按如下方法构造序列 $L$ 和 $R$，长度均与 $A$ 相同：当 $A_{[\max\{i-k,0\}+1,i-1]}$ 中有与 $A_i$ 相同的数时候 $L_i=1$，否则 $L_i=0$；$R_i$ 同理，但区间是 $A_{[i+1,\min\{i,n\}+k-1]}$。

现在我们对 $L$ 与 $R$ 序列作出一些论断：

+ 对于 $1\le i\lt n$，考虑 $A_{[i+1,i+k-1]}$ 中不同数的个数，分别向这个区间的左边和右边延展一位然后回撤贡献，得到 $B_i-(1-R_i)=B_{i+1}-(1-L_{i+k})$。将这个式子变形一下，得到 $L_{i+k}-R_i=B_i-B_{i+1}$。

+ 考察每个数对 $B_1$ 的贡献，得到 $\sum_{i=1}^k(1-L_i)$。简单变形得到 $B_1=k-\sum_{i=1}^kL_i$。同理 $B_n=k-\sum_{i=1}^kR_{n+i-1}$。

但这些性质显然是不够的，我们考虑改变 $L$ 的刻画：一个数与它从左到右上一次出现的位置之差小于 $k$。如此，我们考虑对于给定的数，把它所有出现位置排成一列（避免边界情况可以假设列之起始有一个 $-\infty$），可以发现当且仅当位置列中相邻两个数的差小于 $k$ 的时候，相邻位置中靠右的那一个的 $L$ 值会被赋为一。同理我们考虑 $R$，会发现和 $L$ 的赋一几乎完全一致，除了赋的是相邻位置中靠左的那一个。这样我们可以推出一点更多的性质：

+ 把所有 $R_i=1$ 的 $i$ 从左到右排成一列，记为 $X_1,X_2,\cdots,X_t$；把所有 $L_i=1$ 的 $i$ 从左到右排成一列，记为 $Y_1,X_2,\cdots,Y_t$（注意到 $L$ 和 $R$ 出现一的次数是相等的，上一段足以说明这一点）。那么有 $1\le Y_i-X_i\lt k$。

这个性质其实包含了两个不等式： $Y_i\gt X_i$ 和 $Y_i\lt X_i+k$。前者是因为每个 $Y$ 都对应有一个更小的 $X$，若 $Y_i\le X_i$ 那么一定有 $i$ 个 $X_j$ 小于 $X_i$ 导出矛盾。后者是类似的，考虑 $X_i+k$ 去对应 $Y$ 即可。

现在，对于给定的 $B$，如果我们能在上面几条约束下找到合法的 $L,R$ 两个序列，那么事实上构造 $A$ 将是相当容易的。从左到右扫一遍，如果 $L_i=0$ 那就随便甩一个没用过的权值上去，否则 $i=Y_j$ 一定对某个 $j$ 成立，赋 $A_i$ 为 $A_{X_j}$ 即可。注意我们这里强制规定了 $L_i$ 和 $R_i$ 对应，这是无伤大雅的，因为我们可以证明这样的 $A$ 重算 $L,R$ 序列一定是我们用来构造 $A$ 的这一组，进而通过前两条约束一定可以反推出正确的 $B$。

我们考虑如何在 $B$ 的约数下构造出符合条件的 $L$ 和 $R$。注意 $L_{i+k}-R_i=B_i-B_{i+1}$ 这一性质，如果 $B_i\not=B_{i+1}$ 那么我们一定可以唯一确定 $L_{i+k}$ 和 $R_i$（考虑到这俩值域是 $\{0,1\}$ 而且我们知道它们的差非零）。否则，如果 $B_i=B_{i+1}=k$，那我们会意识到 $A_{[i+1,i+k-1]}$ 中不同数至多 $k-1$ 个，进而 $L_{i+k}=R_{i}=0$。否则我们就会面临一个选择：把这俩都赋值为零或者都赋值为一。但实际上，我们接下来可以证明：遇到这种情况，只要全部选赋一，一定是更加可行的。

为了证明这一点，我们现在可以不妨假设已经构造出了一组合法的 $L$ 和 $R$，并且有 $i$ 满足 $B_i\not=k$ 且 $L_{i+k}=R_i=0$。我们把 $L_{i+k}$ 与 $R_i$ 均重赋值为一。考虑到 $B_i\not=k$，我们得知 $L_{[i+1,i+k-1]}$ 中一定有一，而 $R_{[i+1,i+k-1]}$ 中一定也有一，而且它们是配对的。我们将 $i$ 插入 $X$ 序列并将 $i+k$ 插入 $Y$ 序列。我们注意到，$i$ 将匹配的值在 $[i+1,i+k-1]$ 之间且 $i+k$ 将匹配的值在 $[i+1,i+k-1]$ 之间。至于中间的 $X$ 和 $Y$，每个 $Y$ 将匹配更前的 $X$ 而每个 $X$ 将匹配更后的 $Y$，那么 $Y\gt X$ 依然成立；$i+1\le X,Y\le i+k-1$，那么 $Y-X\lt k$ 也依然成立。于是我们新得到的 $L,R$ 依然是合法的。

这时候我们发现这些约束对 $L$ 最开头的 $k$ 个元素没有效力。但我们观察到还有一条性质 $B_1=k-\sum_{i=1}^kL_i$，这其实告诉了我们 $L_{[1,k]}$ 中需要多少个一。为了更好地完成匹配，实际上我们只需要把所有一尽量往后塞就可以了。这样，$Y_i\gt X_i$ 能更好地完成，而 $Y_i\lt X_i+k$ 由于 $Y_i\le k$ 也一定依然成立。$R$ 同理，最后 $k$ 个元素的所有一尽量往前塞就好了。

由以上所述，我们已经可以构造出一个尽量合法的 $L$ 和 $R$。但是很遗憾，我们并不能完美证明它是合法的，所以我们需要再检查一下 $X$ 和 $Y$ 的合法性，如果没问题的话，就可以构造 $A$ 了。

代码比较好写。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 9;
int t, n, k, a[N], b[N];
bool l[N << 1], r[N << 1];
bool calc() {
  memset(l + 1, false, b[1]);
  memset(l + b[1] + 1, true, k - b[1]);
  memset(r + n, true, k - b[n]);
  memset(r + n + k - b[n], false, b[n]);
  for (int i = 1; i < n; ++i) {
    int d = b[i] - b[i + 1];
    if (d == 1)
      l[i + k] = true, r[i] = false;
    else if (d == -1)
      l[i + k] = false, r[i] = true;
    else if (!d)
      l[i + k] = r[i] = b[i] < k;
    else
      return false;
  }
  vector<int> x, y;
  for (int i = 1; i < n + k; ++i) {
    if (r[i]) x.push_back(i);
    if (l[i]) y.push_back(i);
  }
  int t = x.size();
  if ((int)y.size() != t) return false;
  for (int i = 0; i < t; ++i)
    if (y[i] <= x[i] || y[i] >= x[i] + k) return false;
  int tot = 0;
  for (int i = 1, j = 0; i < n + k; ++i)
    if (!l[i])
      a[i] = ++tot;
    else
      a[i] = a[x[j++]];
  return true;
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  for (cin >> t; t; --t) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> b[i];
    if (!calc())
      cout << "NO";
    else {
      cout << "YES" << '\n';
      copy_n(a + 1, n + k - 1, ostream_iterator<int>{cout, " "});
    }
    cout << '\n';
  }
  return cout << flush, 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc059_d)

**题目大意**

> 给定一个长度为 $n+k-1$ 序列 $a$ 所有长度为 $k$ 的子区间的颜色数 $b_1\sim b_n$，构造原序列或报告无解。
>
> 数据范围：$n,k\le 2\times 10^5$。

**思路分析**

显然考虑差分 $b_{i+1}-b_i$，显然我们只关心 $a_{i+k}$ 在 $a_{[i+1,i+k-1]}$ 中是否出现过，以及 $a_i$ 是否在 $a_{[i+1，i+k-1]}$ 中出现过。

分别记为 $l_{i+k},r_i$，那么 $b_{i+1}=b_i+r_i-l_{i+k}$。

考虑如何刻画 $l,r$，对于所有值相同的下标，我们把下表距离 $<k$ 的匹配起来，那么右边的数 $l_i=1$，左边的数 $r_j=1$。

那么存在一种排列 $p_1\sim p_m$ 使得 $l_{i}-r_{p_i}\in[1,k)$。

通过观察可以猜测我们在 $l,r$ 同时升序时取得一个最优的匹配。

然后考虑通过 $l,r$ 构造原排列：如果 $l_i=0$，那么取一个新的值，否则取对应的 $a_{r_i}$ 的值即可，容易证明所有条件全部满足。

我们只要构造一组合法的 $\{l_i\},\{r_i\}$ 即可。

显然 $b_{i+1}-b_i\in\{1,-1,0\}$，如果 $b_{i+1}-b_i\ne 0$ 那么 $l_{i+k},r_i$ 直接确定，否则我们要考虑 $l_{i+k},r_i$ 同时取 $1$ 还是 $0$。

容易猜测取 $l_{i+k}=r_i=1$ 时更优，可以证明错位之后一定不会更劣，当且仅当 $b_{i}=k$ 时不能取 $l_{i+k}=r_i=1$。

最后只有 $l_{[1,k]}$ 和 $r_{[n,n+k-1]}$ 未处理，而他们的唯一限制就是 $b_1=k-\sum_{i=1}^k l_i$ 和 $b_n=k-\sum_{i=n}^{n+k-1} r_i$。

那么贪心来说肯定把 $l,r$ 取靠近中间值（$l_i$ 往右，$r_i$ 往左）即可。

时间复杂度 $\mathcal O(n+k)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=4e5+5;
int a[MAXN],b[MAXN];
bool l[MAXN],r[MAXN];
void solve() {
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	for(int i=1;i<=n+k-1;++i) a[i]=l[i]=r[i]=0;
	for(int i=0;i<k-b[1];++i) l[k-i]=true;
	for(int i=0;i<k-b[n];++i) r[n+i]=true;
	for(int i=1;i<n;++i) {
		int d=b[i+1]-b[i]; //b[i+1]=b[i]+r[i]-l[i+k]
		if(d<-1||d>1) return puts("NO"),void();
		if(d==1) r[i]=true;
		if(d==-1) l[i+k]=true;
		if(d==0) r[i]=l[i+k]=(b[i]<k);
	}
	vector <int> L,R;
	for(int i=1;i<=n+k-1;++i) {
		if(l[i]) L.push_back(i);
		if(r[i]) R.push_back(i);
	}
	if(L.size()!=R.size()) return puts("NO"),void();
	for(int i=0;i<(int)L.size();++i) if(L[i]<=R[i]||L[i]>=R[i]+k) {
		return puts("NO"),void();
	}
	puts("YES");
	int v=0;
	for(int i=1,j=0;i<=n+k-1;++i) {
		a[i]=(l[i]?a[R[j++]]:++v);
		printf("%d ",a[i]);
	}
	puts("");
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

