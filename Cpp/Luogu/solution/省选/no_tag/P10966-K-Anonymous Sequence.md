# K-Anonymous Sequence

## 题目描述

# K-Anonymous 序列

各种应用领域中爆炸式增长的网络数据引发了相关个人的隐私问题。最近的研究表明，在发布图形/社交网络数据之前简单地删除节点的身份并不能保证隐私。图本身的结构及其基本形式——节点度，可以揭示个体的身份。  
为了解决这个问题，我们研究了一个特定的图匿名化问题。我们称一个图为$k-anonymous$，如果对于每个节点$v$，图中至少存在$k-l$个与$v$具有相同程度的其他节点。我们感兴趣的是在具有最少图修改操作的图上实现$k-anonymous$。  
我们简化了这个问题。从整个图$G$中选取$n$个节点，并按升序列出它们的度数。我们定义一个序列$k-anonymous$，如果对于每个元素$s$，序列中至少存在$k-1$个等于$s$的其他元素。要让给定的序列$k-anonymous$，你只能做一个操作——减少序列中的一些数字。我们定义了修改的成本，即你修改的所有数字的差值。例如，$k=3$的序列$2,2,3,4,4,5,5$可以修改为$2,2,2,4,4,4,4,4$，满足$3-anonymous$，修改的成本为$|3-2|+|5-4|+|5-4|=3$。  
给出一个按升序排列的数字和$k$的序列，我们想知道在所有调整欧速序列$k-anonymous$的修改中，成本最小的修改。

## 样例 #1

### 输入

```
2
7 3
2 2 3 4 4 5 5
6 2
0 3 3 4 8 9```

### 输出

```
3
5```

# 题解

## 作者：_zuoqingyuan (赞：3)

“你只能做一个操作——减少序列中的一些数字”。

因为没看见这句话瞪这题瞪了两周。

前置：斜率优化 dp，[模板题](https://www.luogu.com.cn/problem/AT_dp_z)。

# 思路分析

怎么没有单调队列题解？

设 $dp_i$ 表示将 $a_{1\sim i}$ 修改为 K-Anonymous 序列的最小花费。

对于 $i<k$，显然不可能修改为合法序列。

对于 $i\ge k$，我们可以枚举 $j$，将 $a_{j+1\sim i}$ 修改为一段相同的数字，并将这段的花费累加到 $dp_j$ 上用来更新 $dp_i$。其中 $j\le i-k$。

因为我们只能减小某个数字，而序列单调不下降，所以我们只能把 $a_{j+1\sim i}$ 都修改为 $a_{j+1}$。

记 $S_i=\sum\limits_{j=1}^ia_j$，则：

$$dp_i=\begin{cases}\infty&i<k\\dp_j+(S_i-S_j)-(i-j)a_{j+1}&i\ge k\end{cases}$$

我们主要对后一种情况进行讨论，$k\gets k-1$。

$$dp_i=\min_{0\le j< i-k}\{dp_j+S_i-S_j-(i-j)a_{j+1}\}$$

把式子拆开，去掉 $\min$。

$$dp_i=dp_j+S_i-S_j-ia_{j+1}+ja_{j+1}$$

我们发现式子中只有一项同时包含 $i,j$。显然可以斜率优化，移项得。

$$dp_j-S_j+ja_{j+1}=ia_{j+1}+dp_i-S_i$$

令 

$$y=dp_j-S_j+ja_{j+1}$$

$$k=i$$

$$x=a_{j+1}$$

$$b=dp_i-S_i$$

则式子可以化为 $y=kx+b$ 的形式。因为 $a$ 单调不下降，所以 $k,x$ 均具有单调性，可以直接用单调队列，时间复杂度 $O(n)$。

# $\text{Code}：$

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long//防止爆 int
using namespace std;
const int N=5e5+10;
int n,k,a[N],s[N],l,r,q[N],dp[N];
inline int X(int x){return a[x+1];}
inline int Y(int x){return dp[x]-s[x]+x*a[x+1];}
void work(){
    scanf("%lld %lld",&n,&k);k--;
    for(int i=1;i<=n;i++)scanf("%lld",a+i),s[i]=a[i]+s[i-1];
    q[l=r=1]=0;dp[0]=0;//初始化
    for(int i=1,j;i<=n;i++){
        if(i<=k){dp[i]=0x3f3f3f3f;continue;}
        while(l<r&&(Y(q[l+1])-Y(q[l]))<=i*(X(q[l+1])-X(q[l])))l++;//防止精度误差
        dp[i]=dp[j=q[l]]+s[i]-s[j]-(i-j)*a[j+1];
        while(l<r&&(Y(q[r])-Y(q[r-1]))*(X(i-k)-X(q[r]))>=(Y(i-k)-Y(q[r]))*(X(q[r])-X(q[r-1])))r--;//防止精度误差
        q[++r]=i-k;//决策入队
    }
    printf("%lld\n",dp[n]);
    return;
}
void clear(){//清空
    memset(q,0,sizeof(q));
    memset(dp,0,sizeof(dp));
    l=r=0;
    return;
}
signed main(){
    int T=0;
    cin>>T;
    while(T--){
        work();
        clear();
    }
    return 0;
}
```

如有错误，请指出。

---

## 作者：wurldwen (赞：2)

**题解参考**

《挑战程序设计竞赛》p342-343

---

**题意简化**

给定一个长度为$n$的非严格单调递增数列$a_0, a_1,...,a_{n-1}$，每一次操作可以使数列中任何一项的值减$1$。现在要使数列中每一项都满足其他项中至少有$k-1$项和它相等。求至少要对这个数列进行多少次操作。

---

**问题分析**

由于 $a_0$ 是数列中最小的值，很显然没有必要把任何一个数减到 $a_0$ 以下，所以就有至少 $k-1$ 个其他的数需要减少至和 $a_0$ 相等。又因为减小大的值而保留小的值不会使结果更优，所以可以从小到大选择需要减少至 $a_0$ 的项。对于剩下的部分也有同样的结论成立。这样，我们就有了下面的 DP 方程。

---

**动态规划方程**

$dp_i$：只考虑前 $i$ 项的情况下，满足题目条件的最少操作次数。

$ dp_i = \min\left\{ dp_j + (a_{j+1} - a_j) + \dots + (a_{i-1} - a_j) \mid 0 \leq j \leq i-k \right\} $（将 $[j + 1, i - 1]$ 的$a$都减到$a_j$）

最终答案为 $dp_n$。

**注意**：$[0, k - 1]$的$a$操作完后全变为$a_0$, 区间内的$a$不能作为$a_j$被选取，所以$[k, 2k - 1]$的$i - k$ 无用

---

**优化与预处理**

直接计算的复杂度为 $O(n^3)$。不过转移方程中涉及到了部分和的计算，可以通过预处理出这些值对算法进行改进。

令 $S_i = a_0 + \dots + a_{i-1}$

$$
dp_i = \min\left\{ dp_j + S_i - S_j - a_j \times (i-j) \mid 0 \leq j \leq i-k \right\}
$$

这样复杂度就降为了 $O(n^2)$，不过由于题目中 $n$ 很大，仍然无法满足要求。由于只是按顺序进行转移是无法在规定时间内出解的，所以有必要挖掘转移方程中的一些特殊性质。

---

**线性函数优化**

对于某个 $i$，在 $j$ 从 $0$ 变化到 $i-k$ 的过程中 $S_i$ 是一个定值，因此先把它提到外面：

$$
dp_i = S_i + \min\left\{ dp_j - S_j - a_j \times (i-j) \mid 0 \leq j \leq i-k \right\}
$$

$\min$ 里面的项就是关于 $i$ 的线性函数：

$$
f_j(x) = -a_j \times x + dp_j - S_j + a_j \times j
$$

所以：

$$
dp_i = S_i + \min\left\{ f_j(i) \mid 0 \leq j \leq i-k \right\}
$$

也就是说，计算 $dp_i$ 就相当于从 $i-k+1$ 条直线中寻找 $x=i$ 的最小值。而 $dp_i$ 和 $dp_{i+1}$ 的区别仅在于 $dp_{i+1}$ 需要多考虑一条直线，并且所求的 $x$ 坐标增加了 $1$。

---

**特点分析**

- 使用某种数据结构维护所有可能成为最小值的直线的集合，并以成为最小值的顺序排列保存，记为 $L$。
- 计算 $dp_i$ 只需要取 $L$ 的头部的直线进行计算。
- $i$ 每增加 $1$，如果 $L$ 的头部的直线变得不是最小了，则删除之。
- 增加一条直线时对 $L$ 进行更新。
  
![](https://cdn.luogu.com.cn/upload/image_hosting/eattomwf.png)

如果使用二叉搜索树来维护 $L$，就可以得到一个 $O(n\log n)$ 的算法。更进一步，在本题中由于 $f_j$ 的斜率（$=-a_j$）具有非严格单调递减的性质，因而 $L$ 的更新可以从 $L$ 的末尾进行更新。这样，就可以使用双端队列代替二叉搜索树，从而更加高效地进行求解。

---

**双端队列优化**

- 使用双端队列维护所有可能成为最小值的直线的集合，并以成为最小值的顺序排列保存，记为 $L$。
- 计算 $dp_i$，只需要取 $L$ 的头部的直线进行计算。
- `i` 每增加 $1$，当 $L$ 的头部的直线变得不是最小时，则删除之。
- 增加一条直线时，先删除所有在 $L$ 的末尾中已经不可能成为最小值的直线，然后加入 $L$ 的末尾。

由于共对双端队列进行了最多 $n$ 次的加入和删除操作，因此这个算法的复杂度是 $O(n)$。

**注意**：

- 根据动态转移方程中提到的注意点，第一次添加的直线为$f_0(x)$， 之后需要等$i$更新到$2k$才能持续添加直线$f_{i - k}(x)$。
- 增加完当前的$f_{i - k}(x) $后还需要再次判断队首的直线是否过期，应该操作队尾再操作队首

---

**判定条件的推导**

假设有 3 条直线按照斜率排列有：

$$
f_1(x) = a_1 x + b_1 \\
f_2(x) = a_2 x + b_2 \\
f_3(x) = a_3 x + b_3
$$

其中 $a_1 \geq a_2 \geq a_3$

欲使得：

$$
a_2 x + b_2 \geq \min(a_1 x + b_1, a_3 x + b_3)
$$

即要求：

$$
a_2 x + b_2 - (a_1 x + b_1) \geq 0 
\text{或者} 
a_2 x + b_2 - (a_3 x + b_3) \geq 0
$$

即取 $a_2 x + b_2 < a_3 x + b_3$ 且 $a_2 x + b_2 < a_1 x + b_1$ 的补集。

解方程组：

$$
\begin{cases}
(a_2 - a_1)x < b_1 - b_2 \\
(a_3 - a_2)x > b_2 - b_3
\end{cases}
$$

$\Rightarrow$

$$
x < \frac{b_1 - b_2}{a_2 - a_1} ，
x > \frac{b_2 - b_3}{a_3 - a_2}
$$

$\Rightarrow$

$$
\frac{b_1 - b_2}{a_2 - a_1} > \frac{b_2 - b_3}{a_3 - a_2}
$$

取补集即：

$$
\frac{b_1 - b_2}{a_2 - a_1} \leq \frac{b_2 - b_3}{a_3 - a_2}
$$

故 $f_2$ 不可能成为最小值对应的直线 $\Leftrightarrow (a_2 - a_1)(b_3 - b_2) \geq (b_2 - b_1)(a_3 - a_2)$

---

**代码**

```
c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f(j, x) (-a[j] * x + dp[j] - S[j] + a[j] * j)

void solve () {
    int n, k; cin >> n >> k;
    vector<int>a(n), S(n + 1), dp(n + 1);
    for (int i = 0; i < n; i++) cin >> a[i]; 
    for (int i = 0; i < n; i++) S[i + 1] = S[i] + a[i];

    auto check = [&](vector<int>&ji) -> bool {  //分析j[1]对应的f_j是不是不可能再成为最小值了
        vector<int>ai(3), bi(3);//f_j对应的系数，常数
        for (int i = 0; i < 3; i++) {
            ai[i] = -a[ji[i]];
            bi[i] = dp[ji[i]] - S[ji[i]] + a[ji[i]] * ji[i];
        }
        return ((ai[1] - ai[0]) * (bi[2] - bi[1]) >= (bi[1] - bi[0]) * (ai[2] - ai[1]));
    }; 

    deque<int>dq;//存dp[i]可选的j, [0, k - 1]的a[i]操作完后全变为a[0], 区间内的a[i]不能作为a[j]被选取，所以[k, 2k - 1]的i - k 无用, 不能存
    dq.push_back(0);

    for (int i = k; i <= n; i++) { //[0, k - 1]的a[i]肯定是转为a[0]
        while (dq.size() > 1) { //清理队尾
            int lst1 = dq.back(); dq.pop_back();
            int lst2 = dq.back();
            vector<int>temp = {lst2, lst1, i - k};//顺序要对应斜率依次减小
            if (!check(temp)) {
                dq.push_back(lst1);
                break;
            }
        }
        if (i >= 2 * k) dq.push_back(i - k); //增加直线

        while (dq.size() > 1) { //清理队首
            int fst = dq.front(); dq.pop_front();
            int scd = dq.front();
            if (f(fst, i) < f(scd, i)) { //不满足条件说明不该被清理
                dq.push_front(fst);
                break;
            }
        }
        dp[i] = S[i] + f(dq.front(), i);  //更新dp[i]
    }
    cout << dp[n] << endl;
}

signed main () {
    //freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);  //数据量较大，可能卡输入
    int t; cin >> t; while(t--) solve();
}
```

---

## 作者：IkunTeddy (赞：1)

# 题目分析

我们有个显然的贪心，就是一定是连续的一段变成同一个值，且是最小的那个值。

所以我们考虑从后往前考虑。设 $f_i$ 表示后 $i$ 项满足条件的最小成本。

有转移 $f_i=\min\limits_{j=i+k-1}^{n}\{f_{j+1}+\text{sum}(i,j)-(j-i+1)\times a_i\}$。

这个 $O(n^2)$ 转移显然过不了。考虑优化。

首先先把 $\text{sum}(i,j)$ 用前缀和优化掉，记 $sum$ 表示前缀和数组。再将括号拆开，得到转移：

$f_i=\min\limits_{j=i+k-1}^{n}\{-j\times a_i +f_{j+1}+sum_j-sum_{i-1}-(-i+1)\times a_i\}$。

这个式子就比较显然了，我们直接上斜率优化的套路就行了，用李超线段树维护直线 $y=kx+b$ 的最小值，其中 $k=-j,b=f_{j+1}+sum_j-sum_{i-1}-(-i+1)\times a_i$。

# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
//
const int maxn=5e5+10;
const ll INF=1e18;
int T;
int n,k;
ll s[maxn];
ll disc[maxn];
ll f[maxn],sum[maxn];
struct Segment{
	ll k,b;
}p[maxn];
ll get(int i,ll x){return !i?INF:p[i].k*x+p[i].b;}
struct node{
	int ls,rs;
	int id;
}tree[maxn*4];
int rt,nodecnt;
int build(int l,int r){
	int v=++nodecnt;
	tree[v].id=tree[v].ls=tree[v].rs=0;
	if(l==r)return v;
	int mid=(l+r)>>1;
	tree[v].ls=build(l,mid);
	tree[v].rs=build(mid+1,r);
	return v;
}
void update(int v,int l,int r,int id){
	if(!tree[v].id){
		tree[v].id=id;
		return ;
	}
	int mid=(l+r)>>1;
	if(get(id,disc[mid])<get(tree[v].id,disc[mid]))swap(tree[v].id,id);
	if(get(id,disc[l])<get(tree[v].id,disc[l]))update(tree[v].ls,l,mid,id);
	if(get(id,disc[r])<get(tree[v].id,disc[r]))update(tree[v].rs,mid+1,r,id);
}
ll ask(int v,int l,int r,int x){
	if(l==r)return get(tree[v].id,disc[x]);
	ll res=get(tree[v].id,disc[x]);
	int mid=(l+r)>>1;
	if(x<=mid)res=min(res,ask(tree[v].ls,l,mid,x));
	else res=min(res,ask(tree[v].rs,mid+1,r,x));
	return res;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>s[i];
		for(int i=1;i<=n;i++){
			disc[i]=s[i];
			sum[i]=sum[i-1]+s[i];
		}
		for(int i=1;i<=n;i++)f[i]=INF;
		f[n+1]=0;
		rt=nodecnt=0;
		rt=build(1,n);
		for(int i=n;i>=1;i--){
			if(i+k-1<=n)update(rt,1,n,i+k-1);
			f[i]=ask(rt,1,n,i)-sum[i-1]-s[i]*(-i+1);
			p[i]={-i,sum[i]+f[i+1]};
		}
		cout<<f[1]<<'\n';
	}
	
	return 0;
}
```

---

## 作者：KinNa_Sky (赞：0)

首先一个想法是把序列划分成若干长度大于等于 $k$ 的段，每一段都使其全等于左端点，使代价和最小。

看到分段开始思考有没有决策单调性，也就是证明四边形不等式。

令 $s_i = \sum_{j = 1}^i a_j$，则 $w(i, j) = s_j - s_{i - 1} - (j - i + 1)a_i$。

根据结论要证明四边形不等式只需证明  
$$
\forall i < i + 1 \le j < j + 1\\ w(i, j) + w(i + 1, j + 1) \le w(i, j + 1) + w(i + 1, j)
$$

即证
$$
w(i, j + 1) - w(i, j) \ge w(i + 1, j + 1) - w(i + 1, j)
$$
即证
$$
\begin{aligned}
&s_{j + 1} - s_{i - 1} - (j - i + 2)a_i - s_{j} + s_{i - 1} + (j - i + 1)a_i \ge\\
&s_{j + 1} - s_{i} - (j - i + 1)a_{i + 1} - s_{j} + s_{i} + (j - i)a_{i + 1}
\end{aligned}
$$
即
$$
a_{j + 1} - a_i \ge a_{j + 1} - a_{i + 1}
$$

由于 $a$ 递增，故上式成立，则四边形不等式成立。

单调队列维护决策点，注意每段长度都要大于等于 $k$，所以决策点要延迟 $k$ 入队；然后我们只扫到 $n - k$，每个位置手动从把剩余部分划分成一段更新答案。

[Code](https://www.luogu.com.cn/paste/n58iuqmi) 或者 [Code](https://www.luogu.me/paste/n58iuqmi)

---

## 作者：封禁用户 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P10966)

就相当于是把一个序列分成若干组，每组都有至少 $k−1$ 个数字，花费就是这组的数字和 $sum$，再减去最小值 $\min n$ 乘以这个组的 $cnt$，也就是 $sum−( \min n\times cnt)$。

贪心的考虑，假设说有三个数字 $a_i,a_k,a_j,(i<k<j)$，那么从 $a_j$ 转移到 $a_i$ 的代价一定比从 $a_k$ 到 $a_i$ 的代价更大一些。

所以我们分成的组一定是连续的一段，那么就可以设计转移方程了。

设 $f_i$ 表示考虑前 $i$ 个数的花费。

$f_i=\min\left\{f_j+[sum_i−sum_j]−a_{j+1}\times(i−j)\right\}$

其中 $i−j\ge k$，此时算法复杂度为 $O(n^2)$，无法通过，考虑优化。

首先上式中的 $sum(i)$ 和是一个定值，提取并把里头的式子分解出来。

$f_i=sum_i+ \min {f_j−sum_j−(i−j)\times a_{j+1}}$

考虑两个点 $j,k(j<k)$。

当 $k$ 优于 $j$ 时，有：

$f_j-sum_j-(i−j)\times a_{j+1}\ge f_k−sum_k-(i−k)\times a_{k+1}$

化简：

$f_j−f_k+sum_k-sum_j+j\times a_{j+1}−k\times a_{k+1}\times a_{j+1}-a_{k+1}\le i$

这里要变号，因为 $a_{j+1}−a_{k+1}$ 小于等于 0

这种斜率的形式可以用单调队列来维护。

设 $X(j,k)=f_j-f_k+sum_k-sum_{j}+j\times a_{j+1}-k\times a_{k+1}\times a_{j+1}-a_{k+1}$

队首维护应该很明白了，如果 $X(j,k)\le i$，就删除 $j$，当然由于可能除数为 $0$，所以我们用乘法来维护，所以又得变一次号，不要忘了。

队尾维护：求得是最小值，所以维护一个下凸壳。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5;
int T,n,k,a[N],sum[N],f[N],q[N];
int qy(int x){
    return f[x]-sum[x]+1ll*x*a[x+1];
}
int qx(int x){
    return a[x+1];
}
void solve(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    int l=1,r=1;
    q[1]=0;
    for(int i=1;i<=n;i++){
        while(l<r&&qy(q[l])-qy(q[l+1])>=i*(qx(q[l])-qx(q[l+1])))++l;
//      f[i]=qy(q[l])+sum[i]-i*qx(q[l]);
        f[i]=f[q[l]]+sum[i]-sum[q[l]]-(i-q[l])*a[q[l]+1];
        int z=i-k+1;
        if(z>=k){
            while(l<r&& (qy(q[r-1]) - qy(q[r])) * (qx(q[r])-qx(z))>= (qy(q[r])-qy(z)) * (qx(q[r-1])-qx(q[r])) )--r;
            q[++r]=z;
        }
    }
    cout<<f[n]<<"\n";
}
signed main(){
    cin>>T;
    while(T--)solve();
    return 0;
}
```

---

