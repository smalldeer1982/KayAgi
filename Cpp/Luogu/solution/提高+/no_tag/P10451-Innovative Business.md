# Innovative Business

## 题目描述

有 $N$ 个元素，编号 $1,2,\dots,N$，每一对元素之间的大小关系是确定的，关系具有反对称性，但不具有传递性。

**注意**：不存在两个元素大小相等的情况。

也就是说，元素的大小关系是 $N$ 个点与 $\frac{N \times (N-1)}{2}$ 条有向边构成的任意有向图。

然而，这是一道交互式试题，这些关系不能一次性得知，你必须通过不超过 $10000$ 次提问来获取信息，每次提问只能了解某两个元素之间的关系。

现在请你把这 $N$ 个元素排成一行，使得每个元素都小于右边与它相邻的元素。

你可以通过我们预设的 bool 函数 compare 来获得两个元素之间的大小关系。

例如，编号为 $a$ 和 $b$ 的两个元素，如果元素 $a$ 小于元素 $b$，则 compare(a,b) 返回 true，否则返回 false。

将 $N$ 个元素排好序后，把他们的编号以数组的形式输出，如果答案不唯一，则输出任意一个均可。

---

为了适配 OJ，本题交互格式进行修改。改为 I/O 交互。

```cpp
bool compare(int a, int b)
{
    cout << "? " << a << ' ' << b << endl;
    bool t;
    cin >> t;
    return t;
}
```

请在代码里填写此函数。**擅自修改内容后果自负。**

## 说明/提示

测试数据满足 $1 \le N \le 1000$。

## 样例 #1

### 输入

```
3

1

0

0```

### 输出

```
? 1 2

? 1 3

? 2 3

! 3 1 2```

# 题解

## 作者：pangyuchen75 (赞：5)

## 思路

本题说：

> 关系具有反对称性，但不具有传递性。

这个性质满足归并排序的性质。

所以可以在归并排序的时候询问两两的大小关系，只需要加一个比较函数即可：

```cpp
bool compare(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    bool t;
    cin >> t;
    return t;
}
```

## 代码

话不多说，直接上代码：

```cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 5;

int n;
int a[N];
int t[N];

bool compare(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    bool t;
    cin >> t;
    return t;
}

void Merge_sort(int le, int rt) {
    if (le == rt)
        return;
    
    int mid = (le + rt) / 2;
    Merge_sort(le, mid);
    Merge_sort(mid + 1, rt);
    int i = le, j = mid + 1, k = le;

    while (i <= mid && j <= rt) {
        if (compare(a[i], a[j])) {
            t[k] = a[i];
            i ++ ;
        } else {
            t[k] = a[j];
            j ++ ;
        }

        k ++ ;
    }

    while (i <= mid) {
        t[k] = a[i];
        i ++ ;
        k ++ ;
    }

    while (j <= rt) {
        t[k] = a[j];
        j ++ ;
        k ++ ;
    }

    for (int x = le; x <= rt; x ++ )
        a[x] = t[x];
}

void inp() {
    cin >> n;
}

void work() {
    for (int i = 1; i <= n; i ++ )
        a[i] = i;
    
    Merge_sort(1, n);
    cout << "!";

    for (int i = 1; i <= n; i ++ )
        cout << " " << a[i];
    
    puts("");
}

int main() {
    inp();
    work();

    return 0;
}
```

## 完结撒花！

---

## 作者：Tenil (赞：4)

# Solution

这里是博客：[Tenil](https://www.cnblogs.com/tenil)，有更好的看题体验哦~

## 题意
[原题链接](https://www.luogu.com.cn/problem/P10451)

定义二元关系 $\operatorname{S}$，其满足反对称性且不满足传递性。

现有互异元素 $N(N \le 1000)$ 个，可以进行不多于 $10000$ 次提问，每次提问可以得知两指定元素 $a,b$ 的 $a \operatorname{S}b$ 结果。求序列 $a_N$ 满足：对任意 $x_i,x_{i+1} \in a_N$，有 $x_i  \operatorname{S} x_{i+1}$。

解释一下：

反对称性：对集合 $X$ 上的二元关系 $\operatorname{S}$，对任意 $x_1,x_2 \in X(x_1 \ne x_2)$，若 $x_1 \operatorname{S}x_2$，则 $x_2 \operatorname{S} x_1$ 不成立。

>例如：“小于”是实数集上的二元关系，它满足反对称性，即有：对任意 $x_1,x_2 \in R(x_1 \ne x_2)$，若 $x_1 < x_2$，则 $x_2 <x_1$ 不成立。

传递性：对集合 $X$ 上的二元关系 $\operatorname{S}$，对任意 $a,b,c \in X$（$a,b,c$ 互不相等），若 $a \operatorname{S}b$ 且 $b\operatorname{S}c$，则有 $a \operatorname{S}c$ 成立。

>例如：“小于”是实数集上的二元关系，它满足传递性，即有：对任意 $a,b,c \in R$（$a,b,c$ 互不相等），若 $a<b$ 且 $b<c$，则有 $a<c$ 成立。

由此可见，本题题面所述“小于”并非正常理解的小于，而是一种比较特殊的二元关系。基于图的思想和题目提示，我们可以尝试用图转化问题：

>元素 $\Rightarrow$ 节点 $\hspace{1.5cm}$ 二元关系 $\operatorname{S} \Rightarrow$ 边（$a\operatorname{S}b$ 为真 $\Rightarrow$ 有一条从 $a$ 到 $b$ 的有向边）
>
>满足反对称性 $\Rightarrow$ 没有无向边 $\hspace{1.5cm}$ 不满足传递性 $\Rightarrow$ 要求最终结果为链

（也即原题所述：也就是说，元素的大小关系是 $N$ 个点与 $\frac{N \times (N-1)}{2}$ 条有向边构成的任意有向图。）

所以，原题即为：在只能得知指定的 $10000$ 条边的有向完全图（或称 [竞赛图](https://baike.baidu.com/item/%E7%AB%9E%E8%B5%9B%E5%9B%BE/5743906)）中找一条 Hamilton 路径。

## 分析

### 1.有向完全图一定存在 Hamilton 路径的证明（可跳过）

为了论述的严谨性，我们先证明有向完全图一定存在 Hamilton 路径。（当然，可以直接从百度百科找定理秒，[百科链接](https://baike.baidu.com/item/%E5%93%88%E5%AF%86%E9%A1%BF%E5%9B%BE/2587317)）

以下是一个自认比较简单，十分粗糙但相对好懂的证明（若有不完备还请指出）：

考虑归纳法：

设有一个 $n(n \ge 2)$ 阶有向完全图。

$n =2$，显然成立；

设 $n=k$ 时成立，对 $n=k+1$，考虑如何添加一个点：

(如图，只画了 6 个点，但假设中间还有很多点，除了 Hamilton 路径和 $ \left \langle 1,6\right \rangle  $ 间的边外的边省略)

![](https://cdn.luogu.com.cn/upload/image_hosting/0wsekc97.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ks6beg5w.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/v3e250gu.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/f7gxpcut.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/4iberl8f.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/oj8d37ma.png)

现在考虑一下链首尾连接的情况（图 1 到图 4）：对于图1这种成环的情况（情况 A），任意一点以任意取向都可以接入（如图 3(7-6-1-2-3-4-5)图 4(1-2-3-4-5-6-7)），直接不用看。重点是不成环的（图 5 到图 6）。

对图 5 情况，若新加点连边为 $ \left \langle 8,1\right \rangle $ 或 $ \left \langle 6,7\right \rangle$，则直接成立（情况 B）；若为图 6 情况，考虑链上任意一点（此例为 3），若 3 与 7 之间连边为 $\left \langle 3,7\right \rangle  $，则 3,4,5,6,7 部分与整体形似，可以类似上述考虑方式地分隔，直至达成情况 A 或情况 B，或者分隔出的联通块阶数为 2，一定成立。3 与 7 之间连边为 $ \left \langle 7,3 \right \rangle $ 同理。

于是 $n=k+1$ 时成立，故结论得证。

### 2.算法思路

根据上述论述过程，我们也能够得到一种方法：在已有链上插入新加点，在不能直接接上链头和链尾时，可以枚举中间某点缩小**一定存在可以插入处**的链范围。于是我们可以想到一种形似二分的写法：每次插入新点时，提问 $mid=(l+r) \div 2$ 与新加点的边的取向，从而确定某部分一定有可插入处，缩小范围直至确定，然后直接插入即可。

最大提问次数约 $\sum_{i=1}^N {\log_2i} \approx 8529<10000$，可以通过此题。

不算插入的话时间复杂度为 $O(n\log n)$，vector 暴力插入，于是成了 $O(n^2)$。但对于 $N \le 1000$ 也是绰绰有余了。

## 实现

先选一个点进数组，然后进行拓展：每次拓展选取数组内现有数的中间一个，和新加点进行提问，根据方向缩小区间，直至可以直接连入时，暴力连入即可。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>

using namespace std;

typedef long long ll;

ll fr() {
	ll x=0,f=1;char c=getchar();
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)) {
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}//只读一个也要写快读的屑

inline bool compare(int a, int b)
{
    cout << "? " << a << ' ' << b << endl;
    bool t;
    cin >> t;
    return t;
}

const int maxn=1e3+100;
ll n;
vector<ll> ans(maxn);

int main(){
	n=fr();
	ans[1]=1;
	for(register int i = 2; i <= n; i++){
			int l=0,r=i,mid;//记得从0开始，不然左端接不上
			while(l+1 < r) {//分割链长为2合法，不是一般的l<r的写法
				mid=(l+r)>>1;
				if(compare(i,ans[mid])) r=mid;
				else l=mid;
			}
			ans.insert(ans.begin()+r,i);
	}
	printf("!");
	for(register int i = 1; i <= n; i++) printf(" %lld",ans[i]);
	return 0;
}
```

## 闲话

如果觉得有用，还请点个赞吧！

## to 审核大大

审核大大：并非抄袭，本文于已有题解方法思路不一，与 [@yong2024 的题解](https://www.luogu.com.cn/article/nca2gw59) 代码有相像，但原因是我们都基于二分实现，且他的代码有边界特判，这点本题解代码已优化。这里有修改过程中的代码 [剪贴板](https://www.luogu.com.cn/paste/6wxkscgf)。本次提交还望通过，谢谢！

---

## 作者：yong2024 (赞：4)

# [P10451 Innovative Business](https://www.luogu.com.cn/problem/P10451) 题解
## 题意：
给出一个 $\text N$ 阶竞赛图，可以查询两个点之间的有向边方向，查询次数 $x \le 10000$，要求求出任意一条 $\text Hamilton$ 路径。
## 分析：
### 1. 对于竞赛图上 $\text Hamilton$ 路径存在性的证明：
对于 $N \le 2$ 的情况，不难发现显然成立，考虑归纳，假设对于 $\text k$ 阶竞赛图存在 $\text Hamilton$ 路径，我们考虑加入第 $\text k+1$ 个点，对于 $\text k$ 阶竞赛图上的一个 $\text Hamilton$ 路径，我们记作 $v_0 \to v_1 \to v_2 \to \cdots \to v_k$，讨论如下：
1. 存在 $v_{k+1} \to v_0$，那么显然此时 $v_{k+1}$ 可以被添加在路径开头，形成新的 $\text Hamilton$ 路径 $v_{k+1} \to v_0 \to v_1 \to v_2 \to \cdots \to v_k$。
2. 存在 $v_k \to v_{k+1}$，那么此时 $v_{k+1}$ 可以被添加在路径末尾，形成新的 $\text Hamilton$ 路径 $ v_0 \to v_1 \to v_2 \to \cdots \to v_k \to v_{k+1}$。
3. 对于剩余情况，我们假设不存在这样一个位置可以使得 $v_i \to v_{k+1} \land v_{k+1} \to v_{i+1}$（因为如果存在这样的位置，那么则有一个 $\text Hamilton$ 路径为 $ v_0 \to v_1 \to v_2 \to \cdots v_i \to v_{k+1} \to v_{i+1} \cdots\to v_k$），那么因为存在 $ v_0 \to v_{k+1}$ 则必然存在 $v_1 \to v_{k+1}$（否则存在 $v_{k+1} \to v_1$）。那么对于 $ v_x \to v_{k+1}$ 我们可以推出 $ v_{x+1} \to v_{k+1}$，否则与假设矛盾。于是我们可以得到 $\forall x \in [1,k] \cap N,\exist v_x \to v_{k+1}$，故存在 $v_k \to v_{k+1}$，不存在于此情况中。
### 2. 关于题目的思路
由上文，我们知道了，一个新加入的点必然可以被添加到一个已存在的 $\text Hamilton$ 路径中，且其必然在开头、中间、结尾其中至少一处可被插入。

于是，我们考虑逐个添加点到之前求出的 $\text Hamilton$ 路径中，为解决此问题，我们需要求出一个新的点可插入路径的位置，但是如果逐个枚举，那么询问次数显然无法接受。

注意到当 $\text Hamilton$ 路径长度较短时，比如 $1,2$ 我们很容易的可以添加进这个新的点，且因为此关系不具有传递性，如果要插入一个点，那么我们只需要考虑和这个点相邻的一个或两个点是否满足限制，其他点则对其无影响，于是我们考虑用类似分治的思路，考虑相似的结构，从而将询问次数下降到 $N\log N$ 级别。

每当我们查询当前需要插入的数字 $\text k$ 和路径中第 $\text x$ 个数 $ans(x)$ 的大小时，整个序列实质上以 $\text x$ 为界被分成了两个部分，当 $\text k < ans(x)$ 时，左侧部分无法在两端被插入，则其必然在中间可以被插入，与原路径形式相似，当 $\text k > ans(x)$ 时，右侧部分无法在两端被插入，则其必然在中间可以被插入，与原路径形式相似，于是可以选择其中一个部分循环“查询、砍半、缩小”的操作，而对于 $\text x$ 的取值，我们不难发现，当其将原路径恰好分为两段时期望最好。

注意到，在上述操作中，进行了 $\text N$ 次插入和 $N\log N$ 次下标访问，所以直接使用了数组来达到 $O(1)$ 查询和 $O(N)$ 的暴力插入，很遗憾的是我暂时还没有找到一个可以兼顾两者的方法，导致此代码时间复杂度为 $O(N^2)$，不过在 $N \le 1000$ 时依然可以正常通过本题。
### 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[1005];
bool compare(int a,int b){
    cout<<"? "<<a<<' '<<b<<endl;
    bool t;
    cin>>t;
    return t;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	ans[1]=1;
	for(int i=2;i<=n;++i){
		if(compare(i,ans[1])){
			int x=ans[1];
			for(int j=i;j>1;--j)ans[j]=ans[j-1];
			ans[1]=i;
		}else{
			int l=1,r=i;
			while(l+1<r){
				int mid=(l+r)>>1;
				if(compare(i,ans[mid])){
					r=mid;
				}else{
					l=mid;
				}
			}
			int x=ans[r];
			for(int j=i;j>r;--j)ans[j]=ans[j-1];
			ans[r]=i;
		}
	}
	cout<<'!';
	for(int i=1;i<=n;++i)cout<<' '<<ans[i];
	return 0;
}
```

---

## 作者：qcf2010 (赞：3)

这道题是《算法竞赛进阶指南》上的一道题，按照书上的思路，这道题我们可以用二分的方法来解决。

## 思路

题目是要把 $n$ 个数按照“从小到大”的顺序进行排列。根据数学归纳法，若前 $k-1$ 个元素已经按要求排列好，那么我们只要找到第 $k$ 个元素可以插在哪个元素前面，这道题就可以顺利解决。

那如何找到这个位置呢？这个时候就应当使用二分的方法了。若查找的是第 $k$ 个元素插入的位置，则最初二分的区间为 $[1,k]$，$mid$ 表示第 $k$ 个元素应放在第 $mid$ 个元素前面，而区间中的 $k$ 表示第 $k$ 个元素放在当前所有元素（即 $k-1$ 个元素）之后。若第 $k$ 个元素比第 $mid$ 个元素小，则令 $r=mid$，否则令 $l=mid+1$。最终第 $k$ 个元素应插在第 $l$ 个元素之前。

## 证明二分的正确性

实际上，我们并不会真的像下面说的一样去依次比较，以下只是算法正确性的证明，而我们只需二分查找第 $k$ 个元素的位置即可。

### 如果第 $k$ 个元素比第 $mid$ 个元素小。

继续比较第 $k$ 个元素和第 $mid-1$ 个元素的大小，若第 $k$ 个元素比第 $mid-1$ 个元素大，则第 $k$ 个元素可以插在第 $mid-1$ 个元素和第 $mid$ 之间；否则说明第 $k$ 个元素比第 $mid-1$ 个元素小，继续比较比较第 $k$ 个元素和第 $mid-2$ 个元素的大小，以此类推，直至发现第 $k$ 个元素比第 $1$ 个元素小，那就放在第 $1$ 个元素前面，即整个序列的最左边。

### 如果第 $k$ 个元素比第 $mid$ 个元素大。

同理。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> a={0,1};
//从 a[1] 开始使用，默认第 1 个元素在 a[1]

bool compare(int a,int b){
    cout<<"? "<<a<<" "<<b<<endl;
    bool t;
    cin>>t;
    return t;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n;
    //从第 2 个元素开始查找其位置（第一个元素在 a[1]）
	for(int i=2;i<=n;++i){
		int l=1,r=i;
		while(l<r){
			int mid=(l+r)>>1;
			if(compare(i,a[mid])) r=mid;
			else l=mid+1;
		}
        //先将第 i 个元素放在序列的最后面，然后交换相邻元素直至第 i 个元素移动到正确的位置上。
		a.push_back(i);
		for(int j=i;j>l;j--) swap(a[j],a[j-1]);
	}
	
	cout<<"! ";
	for(int i=1;i<=n;++i) cout<<a[i]<<" ";

	return 0;
}
```

---

## 作者：FZY_CZY (赞：3)

这道题不是在《算法竞赛进阶指南》是一道二分的题目吗？貌似没有人写二分的题解。

这道题看上去很深奥，是一道交互题，实际上没有想象中的那么恐怖，就是二分上面做一个小小的证明。

# 题意
有 $n$ 个数，你可以通过查询得到他们的相对关系，特别的，在本题中`关系具有反对称性，但不具有传递性。`，也就是说，$a>b \implies b<a$，但是 $a<b,b<c \nRightarrow a<c$，现在，你需要通过你询问得到的若干个相对关系。

# 思路
我们有一个答案序列 $res$，我们考虑从 $1$ 到 $n$，逐个插入到 $res$ 当中，在查找当前的 $i$ 可以插入到哪一个位置的时候，可以用二分（原因后面解释）。

我们都知道，在二分中，很重要的就是一个二段性——就是在区间中任意一个节点上，都满足节点左边某个条件成立，右边某个条件不成立。我们常说的根据单调性来二分也是这个原因。

但是很明显，因为不具备关系的传递性，所以是不具备单调性的，但是具有二段性，为什么呢？我们来证明一下。

我们可以设置两个哨兵（方便理解，但不需要实现），在序列最左边的左边一位赋值为负无穷，在序列最右边的右边以为赋值为正无穷，每当我们得到一个中点 $mid$ 时，如果 $res_{mid} > i$，那么 $mid$ 左边一定有一个满足 $res_j<i<res_j+1$ 的位置，因为从 $mid$ 不断往左枚举 $j$，肯定会有一个点，在 $j+1$ 的时候 $res_{j+1}>i$，而 $res_j<i$，因为序列中两个元素之间是满足单调性的，那么这个位置就一定会被找到（哨兵方便理解的作用就在这里），虽然我们无法保证 $mid$ 右边是否会有答案，但是这不重要，因为答案是多解的，只要，左边一定能存在答案，就可以构成一个合法序列，这就足够了，反之亦然。

# 代码
```cpp
// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.
#include<bits/stdc++.h>
using namespace std;
bool compare(int a, int b)
{
    cout << "? " << a << ' ' << b << endl;
    bool t;
    cin >> t;
    return t;
}
int main(){
	int N;
	cin>>N;
	vector<int>res(1,1);
    for (int i=2;i<=N;i++)
    {
		int l=0,r=res.size()-1;
		while (l<r)
		{
			int mid=l+r+1>>1;
			if (compare(res[mid],i)) l=mid;
			else r=mid-1;
		}
		res.push_back(i);
		for (int j=res.size()-2;j>r;j--) swap(res[j],res[j+1]);
		if (compare(i,res[r])) swap(res[r],res[r+1]);
	}
	cout<<"! ";
	for (auto i=0;i<res.size();i++) cout<<res[i]<<" ";
	return 0;
}
``````
在比较大小的时候调用交互库即可。

完结撒花！！！

---

## 作者：hlc110516 (赞：2)

这是一道~~水题~~蓝题。（不知为什么很多题解要用竞赛图）


算法分析
---



首先猜测算法，题目要求我们用不超过 10000 次比较得出正确的顺序。因为 $n$ 达到 1000，所以肯定不能用一些比较次数达到 $n^2$ 量级的排序算法（比如冒泡排序等）。因此直接使用二路归并算法进行排序。


复杂度分析
---

二路归并最多会递归 $O(\log_2 n)$ 层，每一层会进行最多 $O(n)$ 次，所以比较次数最多 $O(n\log_2 n)$ 次，10000 次随便过。


code
---

```
#include<iostream>
using namespace std;
int n,a[1005],b[1005];
bool compare(int a, int b)
{
    cout << "? " << a << ' ' << b << endl;
    bool t;
    cin >> t;
    return t;
}
void msort(int l,int r){
    if(l>=r)return;
    int mid=(l+r)>>1;
    msort(l,mid);
    msort(mid+1,r);
    for(int i=l;i<=r;i++)b[i]=a[i];
    for(int i=l,j=mid+1,k=l;i<=mid||j<=r;k++)
    if(i<=mid&&(j>r||compare(b[i],b[j])))a[k]=b[i++];else a[k]=b[j++];
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)a[i]=i;
    msort(1,n);
    cout<<'!';
    for(int i=1;i<=n;i++)cout<<' '<<a[i];
    return 0;
}
```

第一次写题解，如果有误欢迎指出。

---

## 作者：yedalong (赞：1)

二分与插入排序的结合体。
## Solution
如果不会插入排序的同学可以先去了解一下，这道题目我们可以通过二分的方式高效的在有序序列中找到当前需要插入的元素的合适位置然后再通过 `vector` 实现插入功能，由于 $n$ 很小，$n^2$ 并不会炸，这里使用 `vector` 只是为了简化代码，不用也可以。询问次数 $n\log n$，最坏情况下仍小于 $10000$。
## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> ans;
bool ask(int a, int b){
	cout<<"? "<<a<<' '<<b<<'\n';
    bool t;
    cin>>t;
    return t;
}
int main(){
	cin>>n;
	ans.push_back(0),ans.push_back(1);
	for(int i = 2;i<=n;i++){
		int l=1,r=i-1,res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(ask(ans[mid],i)) l=mid+1,res=mid;
			else r=mid-1;
		}
		auto tmp=ans.begin();
		advance(tmp,res+1);
		ans.insert(tmp,i);
	}
	cout<<"! ";
	for(auto t:ans) if(t) cout<<t<<' ';
	return 0;
}
```

---

## 作者：_zuoqingyuan (赞：1)

奇奇怪怪的题？

# 题目大意

给定 $n$ 个点的有向图，对于任意不相同两点 $i,j$，都存在一条 $i\to j$ 或 $j\to i$ 的边。

你可以进行一些询问 $x,y$，每次询问会回答是否存在一条从 $x\to y$ 的边，请你通过询问找到这样一条图上路径：在不重复经过某个点的前提下且经过每个点。

$n\le 10^3$，询问此时不超过 $10^4$。

# 思路分析

首先这条路径一定存在。

假设我们现在求出 $1\sim k$ 的合法路径 $p_1\to p_2\to \dots \to p_k$，考虑像 $1\sim k$ 中加入 $k+1$ 这个点。

如果存在 $p_k\to k+1$，则将 $k+1$ 插入末尾。

如果不存在 $p_k\to k+1$，则一定存在 $k+1\to p_k$。则 $k+1$ **可能**插入到 $p_{k-1}$ 和 $p_{k}$ 之间，不过还必须满足一个条件：存在 $p_{k-1}\to k+1$。

如果存在 $p_{k-1}\to k+1$，则插入，反之则一定说明存在 $k+1\to p_{k-1}$，则 $k+1$ **可能**插入到 $p_{k-2}$ 和 $p_{k-1}$ 之间，同时需要 $p_{k-2}\to k+1$。

就这样往前推，一旦推到某个满足 $p_{x}\to k+1\to p_{x+1}$ 的位置后插入，否则一直往前推，直到推出不存在 $p_1\to k+1$，则说明一定存在 $k+1\to p_1$，将 $k+1$ 插入到 $p_1$ 之前即可。

至此证明了这样一条路径一定存在。

如果模仿上面的过程一定会 TLE。考虑如何快速插入，可以用二分查找模拟上述过程，假设我们要找的位置 $x\in [l,r]$，满足 $k+1$ 可以插入到 $p_{x-1},p_{x}$ 之间，初始 $l=1,r=k$，每次查询 $mid$，最后询问总次数不超过 $10000$。


# Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
bool cmp(int a,int b){
    cout<<"? "<<a<<' '<<b<<endl;
    bool t;cin>>t;return t;
}
int n,ans[1005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		if(i==1)ans[1]=1;
		else{
			if(cmp(ans[i-1],i)){
				ans[i]=i;
			}else{
				int l=1,r=i-1,mid;
				while(l<r){
					mid=(l+r)>>1;
					if(cmp(i,ans[mid]))r=mid;
					else l=mid+1;
				}
				for(int j=i-1;j>=l;j--)ans[j+1]=ans[j];
				ans[l]=i;
			}
		}
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
} 
```

时间复杂度 $O(n^2)$。

个人认为这很困难。

如有错误，请指出。

---

## 作者：ppip (赞：0)

称题目中的关系为 $<_X$，根据反对称性定义 $>_X$。题目要求构造一个序列满足 $a_1<_Xa_2<_X\dots<_X a_n$。

首先，假设能对长度 $n$ 的序列排序，一定可以对长度为 $n+1$ 的序列排序。

证明：我们添加两个特殊的元素 $a_0=-\infty$ 和 $a_{n+1}=\infty$ 分别“小于”所有数和“大于”所有数。现在该序列为 $a_0 <_X a_1<_X a_2 <_X\dots<_X a_n <_X a_{n+1}$。对于一个新的数 $b$，有 $a_0 <_X b,a_{n+1}>_X b$。所以，一定存在一个 $x$，满足 $a_{x} <_X b, a_{x+1} >_X b$。

现在考虑归并排序。设两个序列为 $a,b$。首先将 $b_1$ 插入 $a$，根据上面的命题，一定可以成功插入。然后假设我们已经成功插入了 $b_1\sim b_y$，且 $a_x <_X b_y <_X a_{x+1}$，那么：

- 若 $b_{y+1}<_X a_{x+1}$，直接将 $b_{y+1}$ 插入在 $a_{x+1}$ 前面；
- 否则，有 $a_{x+1} <_X b_{y+1} <_X a_{n+1}$。根据之前的命题，一定可以找到位置插入。

于是 $b_{y+1}$ 无论如何都可以插入在 $b_y$ 之后的某个位置，所以我们证明了可以归并两个序列，这样就可以归并排序了。

实现时，直接比较 $a,b$ 的第一个数的大小关系，取出较“小”的即可。可以发现这和上面的插入流程是等价的。

---

