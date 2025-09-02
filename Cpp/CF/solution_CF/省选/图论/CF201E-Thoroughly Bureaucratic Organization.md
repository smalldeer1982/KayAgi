# Thoroughly Bureaucratic Organization

## 题目描述

有n个人，每个人都有一个编号，编号范围在1-n以内，每个人的编号都不相同

你每次可以去询问最多m个不同的人，他们的编号是哪些，但是你不知道编号与这m个人的对应关系

现在你需要给出最少申请多少次，可以清楚知道这n个人每个人的编号

## 样例 #1

### 输入

```
5
4 1
4 2
7 3
1 1
42 7
```

### 输出

```
3
2
3
0
11
```

# 题解

## 作者：pyyyyyy (赞：3)

**PS：该题解非本人所写（本人仅略加整理），不过原作者没有署名,所以我不知道原作者是谁qwq**

>原文链接: https://pan.baidu.com/s/1DFRbm3z2k0a-ZrTM7tyrlQ 
>
>提取码: 4fq9

题目大意:给定一个1~n的排列，每次可以同时查询<=m个位置的值但返回的是值的集合(无序)，求最坏情况下最少进行多少次询问可以确定排列。$n,m\le10^9$。

因为限制条件是$\le m$所以满足单调性，考虑二分，问题转化为判断能否用k次询问查询出$n$个位置。

两个数字所在位置可以被区分，即至少存在一个询问，这两个数字在这次询问中出现状态不同。所有数字在什么位置都可以区分，等价于$n$个长度为k的二进制串两两不同。$m$实际上限制了任何一列(一次查询)内1的个数不超过某个值。

即如果存在一种方式给[1,n]分配一个$[1,2^k]$内的标号，且不存在一个二进制位上有超过$m$个标号有$1$，那么就可以查询出结果。注意到n实际上和k是无关的，考虑直接求:
$\max |S|:Si∈[1,2^k]$，S中不存在二进制位上有超过$m$个标号有$1$。

实际上，只需要考虑这样的集合，满足$1$的总个数不超过$k×m$即可。考虑如果存在一种标号方案达到了最大集合$|S|$，其中有一个位置A的1的个数超过了$m$个。那么因为总数一定，所以存在某个位置B不到m个。那么将某一个串$s$中第$A$位的1挪到第B位，这样不会使s和无关的串冲突，只有可能s和另一个第$A$位为$0$第B位为1的串冲突。但是第$A$位为$0$第B位为$1$的串的总数严格小于第$A$位为$1$第$B$位为$0$的串的个数，所以总存在一个$s$不会和任何串冲突。那么就可以执行这一次移动，迭代直到每个位置都不超过$m$。

那么问题就是求:
$max |S|:Si∈[1,2^k]，Σic[Si] <= km$。
不同$1$的个数之间一定不会冲突，一定是1个数越小的越优:即每次肯定是取完$C(k,i)$个长度为i的串(或其中一部分)，如果$1$的个数还有剩余，才会取$C(k,i+1)$。
因为$C(k,i)$是指数级的，只需要贪心迭代$log$次$km$就会用完。
加上二分复杂度$O(\log2n)$。
																

---

## 作者：ZHR100102 (赞：1)

一道能让边哥都说有难度的 adhoc 好题。核桃哪位大神把这个 *2600 放 S 组模拟赛 T2 的啊。

考虑如何区分两个人，显然**如果存在一次询问，使得其中一个人在返回的集合中，而另一个人不在返回的集合中，那么这两个人是不同的**。

继续考虑如何由此确定编号。我们考虑**数学归纳法**，先找出编号是 $1$ 的，然后由此找到编号为 $2,3,\dots$ 的。先对包含元素 $1$ 的集合对应的位置取个交，然后我们可能会得到多个位置。那么如何排除其余的位置呢？根据所有人的询问互异的结论，易知这多个位置如果在包含 $1$ 的集合里无法区分，那么就**一定可以在其他元素不含 $1$、但是对应的位置包含这几个位置之一的询问区别开来**，因此就只剩下了唯一的位置，对应编号 $1$。剩下的编号依次操作即可。

至此原问题被转化为：找出一个最小的 $k$，使得给 $n$ 个人分配互不相同的、值域在 $[0,2^k-1]$ 内的数后，对于每一个二进制位，是 $1$ 的数的个数 $\le m$。

最小的 $k$ 显然具有单调性，可以**二分**。考虑如何快速 check。

首先发现先**把 $\operatorname{popcount}$ 小的编号贪心地赋给某个人一定更优**。证明考虑调整法，如果一个 $\operatorname{popcount}$ 更大的编号先赋给了一个人，那么我从用一个 $\operatorname{popcount}$ 更小的、且是原编号二进制下的子集的编号代替一定更优。

那么我们对于 $\operatorname{popcount}=0,1,2,3,\dots,k$ 的询问的方案数分别计算，$\operatorname{popcount}=i$ 的询问共有 $C_{k}^{i}$ 次，如果剩下能放的 $1$ 的个数 $lst\le C_{k}^{i}$，那我们就直接放置，并且让 $lst$ 减掉它；否则就最多可以进行 $\left \lfloor \frac{lst}{i} \right \rfloor $ 次询问，然后 break 掉，因为后面一定放不了了。最后统计出最多能进行的询问次数，对应着最多能供给的人数，如果 $\ge n$ 则是合法的。

为什么不会出现 $lst \le i$ 但是能放的位置不足 $i$ 个的情况呢？考虑反证，假设有一个位置 $x$ 上 $1$ 被取的个数大于 $m$，那么一定有另一个位置 $y$ 的 $1$ 被取的个数小于 $m$，我们为了让方案合法，会把 $x$ 的 $1$ 移到 $y$ 上。并且这一定不会让询问重复，**因为 $x=0,y=1$ 的询问的个数一定小于 $x=1,y=0$ 的询问的个数**。所以调整后一定可以使得方案合法。

最后证明 check 的复杂度，注意到求答案的式子是 $\sum_{i=0}^kC_{k}^{i}=(1+1)^k=2^k$，所以**枚举 $k$ 的次数是 $O(\log V)$ 的**。综上，时间复杂度为 $O(t\log^2 n)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
ll n,m;
ll check(ll k)
{
    ll lst=m*k,res=1,ad=1;
    for(ll i=1;i<=k;i++)
    {
        ad=ad*(k-i+1)/i;
        if(lst-ad*i>0)
        {
            lst-=ad*i;
            res+=ad;
        }
        else
        {
            res+=lst/i;
            break;
        }
        if(res>=1000000000)return 1000000000;
    }
    return res;
}
void solve()
{
    cin>>n>>m;
    ll l=0,r=n,mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(check(mid)>=n)r=mid;
        else l=mid+1;
    }
    cout<<l<<'\n';
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Komomo (赞：1)

这个询问区分的很抽象，考虑具象化这个东西。给每个元素赋予一个长度为 $q$ 的询问序列 $s$，其中如果第 $i$ 次询问问了第 $j$ 个元素，则 $s_{j,i}=1$，容易发现能问出所有点的充要条件是所有元素的询问序列不同，而且对于任意 $i$，都有 $\sum s_{*,i}\le m$，其中 $*$ 代表所有这一维可能的值。

这个其实也不好做的，然后正解给了一个限制禁令：我们只要保证 $\sum s_{*,*}\le mq$ 即可，以下是证明：

> 考虑调整法，对于某一位 $i$，有 $\sum s_{*,i}>m$，再找一个和 $\le m$ 的位 $j$，将一个 $i$ 位的 $1$ 扔到 $j$ 上，我们声称这个操作永远能进行：
>
> - 首先既然有 $i$ 位的和大于 $j$ 位的和，肯定能找到一个元素，$s_{x,i}=1$ 且 $s_{x,j}=0$。
> - 如果在调整之后出现了矛盾，那只能和 $s_{y,i}=0$ 且 $s_{y,j}=1$ 的某个 $y$ 产生矛盾。但是根据前提，符合条件的 $x$ 数量肯定大于 $y$ 的数量，所以总是存在的。

所以我们只要保证最后这个总和满足条件就好了！二分 $q$，等价于从 $[0,2^q)$ 里面选 $n$ 个数，$\sum \text{popcount}$ 最小，这个直接贪心。

---

## 作者：Purslane (赞：1)

# Solution

我一直在往矩阵列秩为 $n$ 方面思考，但是好像不是简单的线性方程组。

引理：通过已知信息能出解的充要条件为 $\forall 1 \le i < j \le n$，都有 $i$ 和 $j$ 在某一次询问中状态不同。

证明：如果 $\exists 1 \le i < j \le n$，且 $i$ 和 $j$ 在所有询问中状态都相同，那么显然无法把它们区分出来。

否则使用数学归纳法。取出所有包含 $1$ 号元素的集合，求它们的交。根据约束，这些集合的交有且仅有一个元素。那么这个元素就是 $p_1$。把所有含有 $1$ 的集合中的 $p_1$ 删去即可。

本题使用二分答案，变为判定 $k$ 次询问能否把所有数区分开。每个元素是否在第 $i$ 次询问被包含可以用 $q_i$ 表示，$q_i$ 是 $0$ 到 $2^k-1$ 中的一个整数（$k$ 是询问次数）。且对于每个数位 $\mathfrak{s}$，都有 $\mathfrak{s}$ 在所有的 $q$ 中出现次数小于等于 $m$。

容易发现，对于 $q_i$ 每次贪心的选取 $\text{popcount}=x$ 的 $\dbinom{k}{x}$ 个数，$x$ 从 $1$ 开始变大，满足 $1$ 的总数 $\le mk$。

注意到 $\dbinom{k}{x}$ 在 $x$ 比较大的时候是指数级大小，所以在 $O(\log V)$ 次操作之后会超过 $mk$。

总的复杂度为 $O(\log^2 V)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
int T,n,m;
int check(int k,int op=0) {
	int sum=1,lim=m*k,C=k,_1=1;
	ffor(i,1,k) {
		int rst=min(C,lim/i);
		sum+=rst,lim-=rst*i;
		if(sum>=n) return 1;
		if(lim<=i) return 0;
		C=C*(k-i)/(i+1);
	}
	return 0;
}
int bfind(int l,int r) {
	int ans=r+1,mid;
	while(l<=r) {
		mid=l+r>>1;
//		cout<<mid<<' ';
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m;
		if(n==1) {cout<<0<<'\n';continue ;}	
		cout<<bfind(1,n)<<'\n';
	}
	return 0;
}
```

---

