# [AGC055E] Set Merging

## 题目描述

有 $N$ 个集合 $S_1, S_2, \ldots, S_N$。初始时，对于每个 $1 \leq i \leq N$，集合 $S_i$ 只包含整数 $i$（即 $S_i = \{i\}$）。

你可以进行如下操作：

- 任意选择一个满足 $1 \leq i \leq N-1$ 的 $i$，令 $U = S_i \cup S_{i+1}$（即 $S_i$ 和 $S_{i+1}$ 的并集）。然后，将 $S_i$ 和 $S_{i+1}$ 都替换为 $U$。

你的目标是通过有限次操作（可以为 $0$ 次），使得对于所有 $1 \leq i \leq N$，都有 $S_i = \{L_i, L_i+1, \ldots, R_i-1, R_i\}$。请判断是否可以达到目标状态。如果可以，请求出所需的最小操作次数。

## 说明/提示

## 限制条件

- $1 \leq N \leq 5 \times 10^5$
- $1 \leq L_i \leq R_i \leq N$

## 样例解释 1

可以证明无法达到目标状态。

## 样例解释 2

可以按如下方式进行操作达到目标状态：

- 选择 $i = 2$，此时 $S_1 = \{1\}, S_2 = \{2, 3\}, S_3 = \{2, 3\}, S_4 = \{4\}$。
- 选择 $i = 1$，此时 $S_1 = \{1, 2, 3\}, S_2 = \{1, 2, 3\}, S_3 = \{2, 3\}, S_4 = \{4\}$。
- 选择 $i = 3$，此时 $S_1 = \{1, 2, 3\}, S_2 = \{1, 2, 3\}, S_3 = \{2, 3, 4\}, S_4 = \{2, 3, 4\}$。
- 选择 $i = 2$，此时 $S_1 = \{1, 2, 3\}, S_2 = \{1, 2, 3, 4\}, S_3 = \{1, 2, 3, 4\}, S_4 = \{2, 3, 4\}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2
1 2
1 3```

### 输出

```
-1```

## 样例 #2

### 输入

```
4
1 3
1 4
1 4
2 4```

### 输出

```
4```

# 题解

## 作者：Neutralized (赞：3)

首先画个网格把限制的矩形给描出来。  
可以看出两维必须都是不降的，否则合并完了后面的一段，前面的一段就无法满足。   
不过看到这里差不多就做不动了（。  

下面直接扔出来一个 bot 构造：  
考虑一个排列 $a$，初始为 $1, 2, \dotsb, n$，钦定集合 $S_i$ 为区间 $[\min_{j = i}^{n} a_j, \max_{j = 1}^{i} a_j]$，那么每次操作 $i$ 可以看作是交换 $(a_i, a_{i + 1})$。  

其实可以发现这个就是把区间抽象了一下。  
如果始终定位区间左右端点所在位置，可以发现就是类似于，在一段极长的 $l_i$ 相同的区间 $[L, R]$ 内，$l_i$ 这个值在 $a_R$ 上，且 $[L, n]$ 没有比 $l_i$ 小的值。$r_i$ 也是同理的。  

重新观察这个过程，我们要填一个排列使得从 $1 \sim n$ 通过每次交换两项到达这个排列的步数最小，也就是填一个排列最小化逆序对。  
这个排列是最终态推出的，所以现在只需要考虑根据所有区间填一下就行了。  

根据上面说的那个 “可以发现”，其实我们已经找到了所有有效的位置的变化形态。  
我们把一段 $l$ 相同的区间 $[L, R]$，填一个 $l$ 在 $a_R$ 上；对于 $r$ 相同的填一个在 $a_L$ 上，这样已经确定了有效的位置。  
剩下的位置我们只需要顺序填没有放过的数即可，这样逆序对一定是最少的。  
最后 BIT 求一下逆序对可以做到 $O(n \log n)$。  

但是其实可以做到线性。  

具体地，我们设由 $l_i$ 填出的子序列为 $lef$，$r_i$ 为 $rig$，剩余最后补充的为 $ext$，那么我们只需要对每个子序列维护一个在值域上的指针，随时指向序列中的最大值，指针的移动显然是总量 $O(n)$ 的。  
通过这个指针和值域上的三个桶，我们可以轻易地维护对于每个序列，其它两个序列中已经填充的，比它小的数有多少个。  
再维护三个子序列已经归并的长度，就可以算出每个序列和另外两个序列产生的逆序对个数。  
注意到这三个序列内部都是递增的，所以内部是没有贡献的，所以把三组六个逆序对贡献加起来就做完了。  

你可以先把整个序列填出来，然后把三个子序列拎出来归并一下。  
由于树状数组感人的常数，和这个做法感人的常数，跑得差不多快（。  
略微分析一下，这个常数大概是不小于 9 倍的。  

代码未经精细实现，臭不可闻。  


```cpp
// head and definitions

int n, L[N], R[N], seq[N];
// cnt[x] : 序列 x 的桶
int cnt1[N], cnt2[N], cnt3[N];
// p[x] : 第 x 个序列的归并指针
// t[x] : 第 x 个序列的桶指针
// d[xy] : 第 y 个序列中目前有多少个小于 tx 的数
int p1, p2, p3, t1, t2, t3;
int d12, d13, d21, d23, d31, d32;
vector<pair<int, int>> lef, rig, ext; ll res; bool vis[N];
inline void nope() { cout << "-1\n", exit(0); }

main() {
	ios :: sync_with_stdio(0), cin.tie(0), cin >> n;
	for(int i = 1; i <= n; ++i) cin >> L[i] >> R[i];
	for(int i = 1; i < n; ++i)
		if(L[i] > L[i + 1] || R[i] > R[i + 1]) nope();
	for(int i = 1; i <= n; ++i) {
		if(i == n || L[i] < L[i + 1]) {
			// if(seq[i] && seq[i] != L[i]) nope();
			if(vis[L[i]]) nope();
			vis[seq[i] = L[i]] = 1, lef.ep(i, L[i]);
		}
		if(i == 1 || R[i] > R[i - 1]) {
			if(seq[i] && seq[i] != R[i]) nope();
			if(!seq[i] && vis[R[i]]) nope();
			vis[seq[i] = R[i]] = 1, rig.ep(i, R[i]);
		}
	}
	int ptr = 1; for(; vis[ptr]; ++ptr);
	for(int i = 1; i <= n; ++i)
		if(!seq[i]) {
			vis[seq[i] = ptr] = 1;
			for(ext.ep(i, ptr); vis[ptr]; ++ptr);
		}
	for(int i = 1; i <= n; ++i) if(seq[i] > n) nope();
	int Max = 0, Min = 2e9;
	for(int i = 1; i <= n; ++i)
		if((Max = max(Max, seq[i])) ^ R[i]) nope();
	for(int i = n; i >= 1; --i)
		if((Min = min(Min, seq[i])) ^ L[i]) nope();
	// finished checking -1
	int n1 = lef.size(), n2 = rig.size(), n3 = ext.size();
	auto Add = [&](int x, int v, int &p1, int &p2, int &p3, int &t1, int &t2, int &t3,
	int &d1, int &d2, int &d3, int &d4, int *c1, int *c2, int *c3) -> void {
		if(v <= t2) ++d3; if(v <= t3) ++d4;
		while(t1 < v) ++t1, d1 += c2[t1], d2 += c3[t1];
		++p1, ++c1[v], res += (p2 - d1) + (p3 - d2);
	};
	while(p1 < n1 || p2 < n2 || p3 < n3) {
		pair<int,int>
			x1 = {p1 == n1 ? +oo : lef[p1].first, 1},
			x2 = {p2 == n2 ? +oo : rig[p2].first, 2},
			x3 = {p3 == n3 ? +oo : ext[p3].first, 3}; int x, v;
		if(x1 > x2) swap(x1, x2); if(x1 > x3) swap(x1, x3); if(x2 > x3) swap(x2, x3); // 冒泡排序
		switch(x1.second) {
			case 1 :
				Add(lef[p1].first, lef[p1].second, p1, p2, p3, t1, t2, t3,
				d12, d13, d21, d31, cnt1, cnt2, cnt3); break;
			case 2 :
				Add(rig[p2].first, rig[p2].second, p2, p1, p3, t2, t1, t3,
				d21, d23, d12, d32, cnt2, cnt1, cnt3); break;
			case 3 :
				Add(ext[p3].first, ext[p3].second, p3, p1, p2, t3, t1, t2,
				d31, d32, d13, d23, cnt3, cnt1, cnt2); break;
			default :
				cout << "哼哼啊啊啊啊啊啊啊啊啊啊啊啊啊啊" << '\n';
		}
	}
	cout << res << '\n';
}
```

---

## 作者：xkcdjerry (赞：3)

UPD 2023-6-11：增加 $O(n)$ 时空的做法。

我们定义一次操作为有效操作**当且仅当**执行前后状态存在差别，即所被操作的两个集合不等。

显然，只保留有效操作一定不劣于保留所有操作操作，所以以下我们只讨论所有操作均为有效操作的情况。

我们可以维护一个长为 $n$ 的数组 $p$，初始时有 $p_i=i$，且当我们每次对 $i$ 和 $i+1$ 执行**有效**操作时，我们交换 $p_i$ 和 $p_{i+1}$。

现在，我声称对于任意由若干次有效操作得到的 $p$ 和 $S$，均有 $S_i=\{L_i,L_i+1,...,R_i-1,R_i\}$，其中 $L_i=\min(p_i,p_{i+1},...,p_{n-1},p_n),R_i=\max(p_1,p_2,...,p_{i-1},p_i)$。

证明如下：

对于初始情况，由定义有 $S_i={i}$，且显然 $L_i=R_i=i$，满足该结论。

现对于一个已满足该结论的一对 $p,S$，我们需要证明在执行任意有效操作后它们仍满足结论。

令其对 $i$ 和 $i+1$ 执行操作（$S_i \neq S_{i+1}$），称操作后的 $p,S$ 分别为 $p',S'$，以其计算出的 $L,R$ 分别为 $L',R'$，则：

---

若 $p_i>p_{i+1}$：
    
由 $L,R$ 的定义，显然对于所有 $i$ 均有 $L_i \leqslant p_i \leqslant R_i$，因此 $L_{i+1} \leqslant p_{i+1} < p_i,R_i \geqslant p_i > p_{i+1}$。  

由此可得 $L_i=\min(p_i,L_{i+1})=L_{i+1},R_{i+1}=\max(p_{i+1},R_i)=R_i$，即 $S_i=S_{i+1}$，故 $p_i>p_{i+1}$ 的情况下一定不是有效操作。

---

若 $p_i < p_{i+1}$：

显然操作后只会影响 $S_i,S_{i+1},R_i,L_{i+1}$：

由 $L,R$ 的定义，显然有：

$L_i < L_{i+1},R_i < R_{i+1}, L_i \leqslant R_i$

又因为 $p$ 是一个 $1 \sim n$ 的排列：  
$R_i=\max(p_1,p_2,...,p_{i-1},p_i) \geqslant i$  
$L_{i+1}=\min(p_{i+1},...,p_{n-1},p_n) \leqslant i+1$  

操作后有：

$R'_i = \max(p_1,p_2,...,p_{i-2},p_{i-1},p_{i+1}) = \max(R_{i-1},p_{i+1})$，又因为 $p_i<p_{i+1}$ 所以 $R'_i=\max(R_{i-1},\max(p_i,p_{i+1}))=R_{i+1}$，  
$L'_{i+1}=\min(p_{i},p_{i+2},p_{i+3},...,p_{n-1},p_n)=\min(p_{i},L_{i+2})$，又因为 $p_i<p_{i+1}$ 所以 $L'_{i+1}=\min(\min(p_i,p_{i+1}),L_{i+2})=L_i$。

因此，$S'_i=S'_{i+1}=S_i \cup S_{i+1}=\{L_i,L_i+1,...,R_{i+1}-1,R_{i+1}\}=\{L'_i,R'_i\}=\{L'_{i+1},R'_{i+1}\}$，满足上述条件。



至此，由数学归纳法得证。

---

那么假设我们已经知道了 $p$，我们怎么求出做了多少次有效操作呢？即问我们从一个有序数组开始每次交换一对满足 $p_i<p_{i+1}$ 的 $p_i,p_{i+1}$，如何通过最少的交换次数得到一个给定的 $p$。

时间倒流一下，这个问题就变成了给出一个数组 $p$，每次交换一对满足 $p_i>p_{i+1}$ 的 $p_i,p_{i+1}$，多少次能够使得这个数组变为一个有序数组。

这玩意就非常经典了，等效于对于给定数组冒泡排序的交换次数，而一个广为人知的结论就是冒泡排序的交换次数等于数组内的逆序对个数，

---

剩下的唯一问题就是，如何通过 $L,R$ 得出 $p$。

我们先考虑 $L$ 对 $p$ 的限制，对于一对相邻的 $L_i,L_{i+1}$，由于 $L_i > L_{i+1}$ 显然非法（由前证），所以仅存在两种情况：$L_i=L_{i+1}$ 和 $L_i<L_{i+1}$。

若 $L_i<L_{i+1}$，由于 $L_i=\min(p_i,p_{i+1},...,p_{n-1},p_n)=\min(p_i,L_{i+1})$，所以显然有 $p_i=L_i$，否则 $p_i$ 可能为 $\leqslant L_{i}$ 的任何值。

类似的可得，$R_{i-1} < R_{i}$ 时，$p_i=R_i$，否则 $p_i \leqslant R_i$。

特别的，$p_1=R_1,p_n=L_n$。

那么我们将被确定的填入后，发现剩余的均满足限制条件 $p_i \leqslant L_i, p_i \leqslant R_i$，且 $L_i,R_i$ 严格不递减。

那么显然，若存在两个这种仅限制值域区间的位置 $i,j$ 满足 $p_i > p_j$，由于 $\min(L_i,R_i) \leqslant \min(L_j,R_j)$，那么交换后仍满足条件。

且显然，若如此交换知道所有仅限制值域区间的均有序，则逆序对个数也会被最小化。

按上文方法模拟可以 $O(n)$ 构造出 $p$ 数组，计算逆序对复杂度 $O(n \log n)$，总复杂度 $O(n \log n)$。

代码：

```c++
#include <cstdio>
#define N 500010
int n,a[N],l[N],r[N];
bool set(int x,int v)
{
    if(a[x]&&a[x]!=v) return false;
    a[x]=v; return true;
}
bool vis[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",l+i,r+i);
    l[n+1]=r[n+1]=0x3f3f3f3f;
    for(int i=1;i<=n;i++) if(l[i]>l[i+1]||r[i]>r[i+1])
        return puts("-1"),0;
    for(int i=1;i<=n;i++) if(l[i]!=l[i+1])
        if(!set(i,l[i])) return puts("-1"),0;
    for(int i=1;i<=n;i++) if(r[i-1]!=r[i])
        if(!set(i,r[i])) return puts("-1"),0;
    int mn=0x3f3f3f3f,mx=0;
    for(int i=1;i<=n;i++) if(a[i])
    {
        if(vis[a[i]]) return puts("-1"),0;
        else vis[a[i]]=1;
    }
    for(int i=1,p=1;i<=n;i++) if(!a[i])
    {
        while(vis[p]) p++;
        a[i]=p;
        vis[p]=true;
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]>mx) mx=a[i];
        if(mx!=r[i]) return puts("-1"),0;
    }
    for(int i=n;i>=1;i--)
    {
        if(a[i]<mn) mn=a[i];
        if(mn!=l[i]) return puts("-1"),0;
    }
    long long ans=0;
    static int f[N];
    for(int i=n;i>=1;i--)
    {
        for(int j=a[i];j;j-=j&-j) ans+=f[j];
        for(int j=a[i];j<=n;j+=j&-j) f[j]++;
    }
    printf("%lld",ans);
}
```

---

UPD 2023-6-11：  
这个题还有 $O(n)$ 时空的做法~~但是因为常数原因被 $O(n \log n)$ 树状数组爆踩~~：

考虑最终数组是由三个有序数组覆盖得到的，因此显然可以拆分为至多 $3$ 个有序数组。  
形式化的来讲，可以找到三个数列 $R,S,T$ 使得：
$$
R \cup S \cup T=[1,n] \cap N^+\\
R \cap S = S \cap T = R \cap T = \emptyset
$$
且对于任意有意义的 $i$ 均有：
$$
A_i=a_{R_i},R_{i-1}<R_i,A_{i-1} \leqslant A_i\\
B_i=a_{S_i},S_{i-1}<S_i,B_{i-1} \leqslant B_i\\
C_i=a_{T_i},T_{i-1}<T_i,C_{i-1} \leqslant C_i
$$

> Universal problem-solving advice: Start with the simplest non-trivial variant of the problem you can.   --3Blue1Brown

考虑如何利用这一性质，首先思考“最简单的非平凡情况”：整个数组可以拆分为*两个*有序数组 $A,B$。  
显然 $A,B$ 内部无逆序对，而我们可以参考归并排序求逆序对个数求出 $A,B$ 间的逆序对个数：  
维护两个指针 $p,q$，指针 $p$ 指向最后一个在最终数组中位置在 $B_i$ 前的数字，指针 $q$ 指向最后一个小于等于 $B_i$ 的数字。

显然，$A_{q+1}$ 到 $A_p$ 间的数字均在 $B_i$ 左侧且大于 $B_i$，即和 $B_i$ 构成逆序对，此时 $B_i$ 对答案的贡献为 $\max(p-q,0)$。

注意这样没有统计到 $A$ 中小于 $B$ 且在 $B$ 右侧的逆序对贡献，因此需要交换 $A,B$ 后再双指针扫一遍。复杂度显然为 $O(n)$。

推广到数组可以被拆分为 $3$ 个（或 $k$ 个）有序数组的情况时，由于各个数组内部无逆序对且剩下的逆序对均为两个数组之间，即下标可以用相对顺序替代，所以可以将有序数组间的逆序对数量两两相加就能得到最终答案，复杂度显然不高于 $O(nk^2)$，在本题中 $k=3$，即复杂度为带 $18$ 倍常数的 $O(n)$。

代码（为精简删去了与 $O(n \log n)$ 算法的重复部分）：
```c++
#include <cstdio>
#define N 500010
int n,a[N],l[N],r[N],type[N];
bool set(int x,int v,int id)
{
    if(a[x]) return a[x]==v;
    //注意这里打上了type的tag记录第一次谁染色（即归属于谁）
    type[x]=id, a[x]=v; return true;
}
bool vis[N];

int top[3];
struct val{int i,v;}b[3][N];

long long ans;
void work(int x,int y)
{
    //处理一对有序数组
    int p1=1,p2=1;
    for(int i=1;i<=top[y];i++)
    {
        while(p1<=top[x]&&b[x][p1].v<b[y][i].v) p1++;
        p1--;
        while(p2<=top[x]&&b[x][p2].i<b[y][i].i) p2++;
        p2--;

        if(p2>p1) ans+=p2-p1;
    }
}

int main()
{
    scanf("%d",&n);
    //......
    //构造部分省略
    //......
    for(int i=1;i<=n;i++) b[type[i]][++top[type[i]]]={i,a[i]};
    //为了美观摆成矩阵形式
               work(0,1); work(0,2);
    work(1,0);            work(1,2);
    work(2,0); work(2,1);
    printf("%lld",ans);
}
```

---

## 作者：FZzzz (赞：2)

补不动 F 先来写个 E 的题解。

震撼。

------------
考虑一步外星人智慧转化：构造一个排列 $p$ 初始为 $1$ 到 $n$，每次合并两个集合则交换这两个位置的数。我们可以得到：$S_i=[\min\limits_{j=i}^np_j,\max\limits_{j=1}^ip_j]$。

显然知道这个结论之后归纳证明是容易的。由于 fyk 说需要 hyk 看懂我就不写证明了，但是由于 fyk 说需要 xqz 也看懂我还是写一下证明：

首先最开始成立。假设现在成立，我们欲证明一次操作之后也要成立。假设我们操作 $i$ 和 $i+1$。
- 若 $p_i>p_{i+1}$，则 $S_i=S_{i+1}$，交换之后显然两个 max 和 min 的值不会改变；
- 若 $p_i<p_{i+1}$，则 $S_i\cup S_{i+1}=[\min\limits_{j=i}^np_j,\max\limits_{j=1}^{i+1}p_j]$，而可知操作后 $\min\limits_{j=i+1}^np_j$ 等于现在的 $\min\limits_{j=i}^np_j$，$\max\limits_{j=1}^{i}p_j$ 等于现在的 $\max\limits_{j=1}^{i+1}p_j$，于是成立；

综上，结论得证。

（我觉得我其实还不如写一句“归纳显然”完事……）

后面的一切就顺理成章了。我们需要找到一个能导出目标集合序列的排列 $p$，并且最小化其逆序对数。首先，若 $l$ 或 $r$ 不递增显然不合法。

然后，若 $i=n$ 或 $l_i<l_{i+1}$，则可知 $p_i=l_i$，$r$ 同理。这样我们已经确定了排列中的一部分。同时，我们已经保证了，后缀 min 不会大于 $l$（因为后面肯定已经有一个 $p$ 等于这个 $l$），前缀 max 不会小于 $r$。

于是，想让目标排列导出目标集合序列，在不考虑逆序对个数时，我们只需最大化后缀 min 并且最小化前缀 max。只需顺着填没有被确定的部分即可做到这一点。而这样填也同时保证了逆序对最少！于是，我们可以这样确定目标排列，然后求一次逆序对即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
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
int n,l[maxn],r[maxn];
void myassert(bool f){
	if(!f){
		printf("-1\n");
		exit(0);
	}
}
int p[maxn],p2[maxn];
inline int lowbit(int x){
	return x&-x;
}
int c[maxn];
void modify(int x,int k){
	while(x){
		c[x]+=k;
		x-=lowbit(x);
	}
}
int query(int x){
	int s=0;
	while(x<=n){
		s+=c[x];
		x+=lowbit(x);
	}
	return s;
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	for(int i=1;i<=n;i++){
		l[i]=readint();
		r[i]=readint();
	}
	for(int i=1;i<=n;i++){
		if(i<n) myassert(l[i]<=l[i+1]);
		if(i==n||l[i]<l[i+1]){
			p[i]=l[i];
			myassert(!p2[l[i]]);
			p2[l[i]]=i;
		}
		if(i) myassert(r[i]>=r[i-1]);
		if(!i||r[i]>r[i-1]){
			myassert(!p[i]||p[i]==r[i]);
			p[i]=r[i];
			myassert(!p2[r[i]]||p2[r[i]]==i);
			p2[r[i]]=i;
		}
	}
	int cur=1;
	for(int i=1;i<=n;i++) if(!p[i]){
		while(p2[cur]) cur++;
		p[i]=cur++;
	}
	int mx=0;
	for(int i=1;i<=n;i++){
		mx=max(mx,p[i]);
		myassert(mx==r[i]);
	}
	int mn=n+1;
	for(int i=n;i>0;i--){
		mn=min(mn,p[i]);
		myassert(mn==l[i]);
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans+=query(p[i]);
		modify(p[i],1);
	}
	printf("%lld\n",ans);
	#ifdef LOCAL
	fprintf(stderr,"%d\n",(int)clock());
	#endif
	return 0;
}
```

---

