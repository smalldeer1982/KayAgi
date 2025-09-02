# Sorting Books

## 题目描述

One day you wanted to read something, so you went to your bookshelf to grab some book. But when you saw how messy the bookshelf was you decided to clean it up first.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481E/eb717b77908d0758f813f3cb2f376ac8a23aad06.png)There are $ n $ books standing in a row on the shelf, the $ i $ -th book has color $ a_i $ .

You'd like to rearrange the books to make the shelf look beautiful. The shelf is considered beautiful if all books of the same color are next to each other.

In one operation you can take one book from any position on the shelf and move it to the right end of the shelf.

What is the minimum number of operations you need to make the shelf beautiful?

## 说明/提示

In the first example, we have the bookshelf $ [1, 2, 2, 1, 3] $ and can, for example:

1. take a book on position $ 4 $ and move to the right end: we'll get $ [1, 2, 2, 3, 1] $ ;
2. take a book on position $ 1 $ and move to the right end: we'll get $ [2, 2, 3, 1, 1] $ .

In the second example, we can move the first book to the end of the bookshelf and get $ [2,2,1,1,1] $ .

## 样例 #1

### 输入

```
5
1 2 2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1 2 2 1 1```

### 输出

```
1```

# 题解

## 作者：流沫 (赞：13)

# CF1481E Sorting Books

题解有一个地方没说清楚，我下面补充。

预处理出每种颜色的最左最右位置 $l_i,r_i$，考虑动态规划处理题目的对偶问题，最多能保留几个不移动。令 $dp_i$ 为后缀 $suf_i$ 即 $a(i,n)$ 中能不动书数目的最大值。

**转移：**

考虑到第 $i$ 个位置

1. $i$ 是这个颜色的左端点，可以把和右端点之间的异色书移走，有转移 $dp_i\leftarrow cnt_{a_i}+dp_{r_{a_i}+1}$。
2. 如果不是，$cnt_{a_i}$ 为后缀中颜色为 $a_i$ 的数目。下面就是我要**补充**的地方。现在有一个方案是保留后缀中颜色为 $a_i$ 的不动，移动其他的，那么要移动多少？由于 $i$ 不是右端点，所以后续过程中在 $i$ 前面且跟 $i$ 同色的要跟 $i$ 相邻的话，必须一起移到后面，然后再把 $suf_i$ 中所有异色的再移出来。所以才有了转移 $dp_i\leftarrow cnt_{a_i}$，也就是其它全部移走的意思，这里有一个费用提前计算的思想。
3. 如果要移动当前的书，转移 $dp_i\leftarrow dp_{i+1}$。

由于要移动的最少，那么要保留的最多，所有转移取一个最大值。

这里再给出一组样例供理解第二点，**2 3 4 5 6 2 2 8**答案**2**。

### code
```cpp
const int N=1e6;
int n,m;
int a[N],dp[N],l[N],r[N],cnt[N];
signed main(){
	read(n);fs(i,1,n){
		read(a[i]);if(!l[a[i]])l[a[i]]=i;
		r[a[i]]=i;
	}
	fn(i,n,1){
		dp[i]=dp[i+1];
		++cnt[a[i]];
		if(i!=l[a[i]])dp[i]=max(dp[i],cnt[a[i]]);
		else dp[i]=max(dp[i],cnt[a[i]]+dp[r[a[i]]+1]);
	}
	printf("%d",n-dp[1]);
	return 0;
}
```

---

## 作者：huayucaiji (赞：10)

这个官方题解只讲了转移方程，根本没讲原理，这里全部重新做个解释。

我们先考虑答案的范围。如果我们贪心，那么最多操作次数为 $n$ 次，且一本书最多会被移动一次。

### 定状态

我们令 $l_i,r_i$ 分别为第 $i$ 种颜色从左往右数最早出现/最晚出现的位置。令 $f_i$ 为在最后将所有书归好类后，$[i,n]$ 内最多有多少本书无需移动。明显，我们需要倒序枚举。最后的答案为 $n-f_1$。

我们记 $tot_{i,j}$ 为在 $[j,n]$ 中，颜色为 $i$ 的书本有多少本。

### 列状态转移方程

$$f_i=\max\begin{cases}
f_{i+1}&1\leq i<n\\
tot_{a_i,i}&i\neq l_{a_i}\\
tot_{a_i,i}+f_{r_{a_i}+1}&i=l_{a_i}
\end{cases}$$

- 首先我们考虑的是 $i$ 这本书要移动，那么此时最多可以保留不动的就是 $f_{i+1}$ 本。
- 如果 $i$ 这本书不移动，那么显然颜色为 $a_i$ 的书都不要动，即 $tot_{a_i,i}$ 本。那为什么在 $i\neq l_{a_i}$，不加上 $f_{r_{a_i}+1}$ 呢？我们可以重点关注一下样例：

```plain
5
1 2 2 1 3
```

若加上了，我们得到的 $f$ 数组为 $4,4,3,2,1$（下标从 $1$ 开始）。明显是错误的，应该为 $3$。为什么会错呢？我们来具体分析发生了甚么。

从本质出发，为什么可以保持颜色为 $a_i$ 的书不移动，就是因为把 $[i,r_{a_i}]$ 中颜色不为 $a_i$ 的全部移走。如果过早地进行了与有区间的合并，可能就会有两个区间有部分重叠。只有等所有颜色为 $a_i$ 的数都出现过了，才可以进行区间的合并。

那上面那个样例说事，我们来理清关系：

- $f_1=f_2$
- $f_2=f_4+1$
- $f_4=f_5+1$。

好，到这里，就出现了问题。我们已经将 $[4,4],[5,5]$ 合并为了 $[4,5]$。而在 $[2,3]$ 出现后，我们又进行了合并，有区间 $[2,5]$。说明我们不可能将 $2$ 移走了。我饿么您此时为了做出最优决策，只能将第一个 $1$ 移走。明显是错误的。因为在 $[1,4]$ 区间可以被计算时，$[4,4]$ 已经“名花有主”了。

### 边界&初值

无。~~好干脆啊。~~

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=5e5+10; 

int n;
int a[MAXN],l[MAXN],r[MAXN],f[MAXN],tot[MAXN];

signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		a[i]=read();
		if(!l[a[i]]) {
			l[a[i]]=i;
		}
	}
	for(int i=n;i;i--) {
		if(!r[a[i]]) {
			r[a[i]]=i;
		}
	}
	
	for(int i=n;i;i--) {
		tot[a[i]]++;
		if(i==l[a[i]]) {
			f[i]=max(tot[a[i]]+f[r[a[i]]+1],f[i+1]);
		}
		else {
			f[i]=max(f[i+1],tot[a[i]]);//正确
		//	f[i]=max(tot[a[i]]+f[r[a[i]]+1],f[i+1]；//错误
		}
	}
	
	cout<<n-f[1]<<endl;
	return 0;
}
```

---

## 作者：Zpair (赞：7)

首先有一个简单的性质，就是一本书只会被放在最后一次。

所以我们考虑把所有被放在后面的书单独拿出来，然后按颜色排完序再放回去。

然后发现所有被拿出来的书中，最多有一种颜色的书没有全部被拿出来。且如果存在一种颜色的书没有被全部拿出来，则剩下的这种颜色的书应该被全部排在最后。

我们称完全留下的颜色为 A 类颜色，完全被拿出的颜色为 B 类颜色，排在最后未被完全拿出来的颜色为 C 类颜色。

然后考虑每一种颜色的性质。

显然 A 类颜色对应的一定是一段区间，然后这段区间包含所有这种颜色的书，区间中所有其他颜色的书都需要被拿出来。

然后就相当于把整个序列划分为若干段 A 类颜色对应区间，然后中间可以有空隙，但是 A 类颜色区间不能有交。然后 A 类颜色区间中的其他颜色都必须被选为 B 类颜色，除了最后的颜色可以不拿出来，因为它可以作为 C 类颜色。

可以结合下面的图理解一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/3p51fp8l.png)

图中 A 类颜色为红色，B 类颜色为蓝色，C 类颜色为绿色。

按上面的划分方式下标为 $2,3,4,6,7,9,10$ 的数需要被拿出。

设：$f_i$ 表示 $[i,n]$ 的区间合法的最大未被拿出个数，$S(l,r,x)=\sum_{i=l}^r [a_i=x]$.

然后若 $i$ 作为一个颜色的最左端点，则可以将其作为一个 A 类颜色段。所以有 $f_i \leftarrow f_{r_{a_i}+1}+S(i,r_{a_i},a_i)$.

否则可以将 $i$ 作为一个 C 类颜色段，此时需要将 $i$ 以后所有除了 $a_i$ 以外的颜色全部拿出，所以有：$f_i \leftarrow S(i,n,a_i)$.

然后可以将 $a_i$ 作为一个 B 类颜色，所以有 $f_i \leftarrow f_{i+1}$.

考虑这些转移的合法性。C 类颜色段一定只有一个，A 类颜色段一定不交，然后所有 A 类颜色段中间的点一定不会作为 A 类颜色，容易发现从这几个条件就可以完全限制序列的合法性。

转移的实现是平凡的，时间复杂度为 $O(n)$。

---

## 作者：fanfansann (赞：7)

## E - Sorting Books

一排书架上有 $n$ 本书排成一排，每本书上有一个颜色 $a_i$，你可以每次将一本书移动到书架的最右端，如果书架上的书，颜色相同的书都排到了一块，我们就认为他是漂亮的，请问将这个书架通过上面的那一种操作排成漂亮的书架，最少需要几次操作？

**Solution**

其实是超级简单的一道题 ~


首先根据题意，先不考虑最优解，我们直接全部往右乱扔就一定能满足，但是不一定是最优解，解决最优解问题，很明显要么贪心，要么DP，要么贪心 + DP。

首先考虑贪心策略，我们一上来最直观的感受就是，如果有一种颜色，没有完全在一块，中间参杂着其他颜色的书，但是这种颜色的书的数量非常非常的多，很明显我们就可以贪心地把这种颜色中间的书移走，这些这种颜色的书就会自动合并到一块，肯定比把这种颜色的很多很多的书一个一个丢到最右边要来的快，这一点很容易想到。

所以我们来尝试找一下，有没有这种颜色的书，或者好几种，只要区间不重叠就好，数量比它中间其他颜色的书的数量还要多，也就是找到若干个区间，但是直接找区间有点困难，题目只需要我们输出最少操作次数即可，所以在有了这个完美的贪心策略以后，我们考虑DP来模拟这个过程。


我们设 $f[i]$ 表示 $i\cdots n$ 区间里不需要移动的书的最大数量，很显然答案就是 $n-f[1]$。除去不需要移动的，把剩下的按照颜色的分类丢到右边就行了。

我们想要找到的是区间里书数量最多的颜色，并且可以是很多种区间不重叠的颜色，要先找区间，所以我们先存一下每种颜色的出现的左右区间 $l_i$ 和 $r_i$ ，因为要找数量最多的那一种，所以我们再使用 $cnt$ 数组存一下每种颜色出现的次数。因为现在考虑的是逆序 DP，所以再存一下 $\text cnt\_post_i$ ，表示的是 $i\cdots n$ 之间每种颜色的书的数量。

考虑转移方程：

（1）$\tt f\ [i] = \max\{f\ [i], f[i + 1]\}$


（2）$\tt  f[i] = \max\{f [i], {cnt\_post} [ a[ i]]\}$

我们取 $i\cdots n$ 里当前最优的一种颜色，也就是只选择一个区间的情况。为什么不能写成  $\tt  f[i] = \max\{f [i], {cnt\_post} [ a[ i]]+f[r[a[i]]+1]\}$ 呢，也就是为什么我们不能一块加上当前颜色区间右边的最优解呢？这样看上去好像没什么毛病呀？

参见样例：

```cpp
5
1 2 2 1 3
```

```cpp
2
```

会发现如果在没有完全完整的区间的基础之上更新，就会导致几个区间重叠，得到实际上是错误的 “最优解”

（3）当 $\tt l[a[i]]=i$时，$\tt f[i]=max\{cnt[a[i]]+f[r[a[i]]+1]\}$

这里我们已经完全走完了颜色 $\tt a[i]$ 的整个区间，可以跟其他区间合并以找到最优解，也不会导致区间重叠。


这个转移方程实际上就是选择区间 $[l_{a_i},r_{a_i}]$ 里，颜色 $a_i$ 不移动，因为 $f[i]$ 存的是 $i\cdots n$ 里不需要移动的书的最大数量，所以要加上 $r_{a_i}$ 右边的 $f$ ，应该很好理解 ~



**Code**

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;
const int N = 5e5 + 7, mod = 1e9 + 7;
typedef long long ll;
typedef int itn;

itn a[N], l[N], r[N];
int cnt[N], cnt_post[N];
itn n, m;
int f[N];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        if(l[a[i]] == 0) l[a[i]] = i;
        r[a[i]] = i;
        cnt[a[i]] ++ ;
    }

    for(int i = n; i >= 1; -- i) {
        f[i] = f[i + 1];
        cnt_post[a[i]] ++ ;
        if(i == l[a[i]])
            f[i] = max(f[i], f[r[a[i]] + 1] + cnt[a[i]]);
        else f[i] = max(f[i], cnt_post[a[i]]);
    }
    printf("%d\n", n - f[1]);
    return 0;
}

```

当然，我们上面使用逆序来求，实际上正序逆序没有任何区别 ~ 


-----------

牛逼群友用线段树搞出来了...

wxyyyds

%%%

~~我还没看懂啥意思~~ 
```cpp
#include <iostream>

namespace wxy{
const int N = 5e5 + 5,inf = 1e9 + 5;
#define int long long
int a[N],f[N],lst[N],fst[N],pre[N],cnt[N],n;
struct node{int l,r,add,max;}t[N << 2];
inline void pushup(int u){t[u].max = std::max(t[u << 1].max,t[u << 1 | 1].max);}
inline void pushdown(int u){
    if (t[u].add){
        t[u << 1].max += t[u].add; t[u << 1 | 1].max += t[u].add;
        t[u << 1].add = t[u << 1 | 1].add = t[u].add; t[u].add = 0; 
    }
}
inline void build(int u,int l,int r){
    t[u].l = l; t[u].r = r; t[u].add = 0;
    if (l == r){t[u].max = cnt[l]; return;}
    int mid = l + r >> 1;
    build(u << 1,l,mid);
    build(u << 1 | 1,mid + 1,r);
    pushup(u);
}
inline void cge(int u,int l,int r,int v){
    if (t[u].l == l && t[u].r == r){
        t[u].max += v; t[u].add += v;
        return;
    }
    int mid = t[u].l + t[u].r >> 1;
    pushdown(u);
    if (r <= mid) cge(u << 1,l,r,v);
    else if (l > mid) cge(u << 1 | 1,l,r,v);
    else {cge(u << 1,l,mid,v); cge(u << 1 | 1,mid + 1,r,v);}
    pushup(u);
}
inline int query(int u,int l,int r){
    if (t[u].l == l && t[u].r == r) return t[u].max;
    pushdown(u);
    int mid = t[u].l + t[u].r >> 1;
    if (r <= mid) return query(u << 1,l,r);
    else if (l > mid) return query(u << 1 | 1,l,r);
    else return std::max(query(u << 1,l,mid),query(u << 1 | 1,mid + 1,r));
}
inline void main(){
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++){
        pre[i] = lst[a[i]];
        lst[a[i]] = i;
        cnt[a[i]]++;
    }
    int pos = n;
    for (int i = n; i >= 1; i--){
        if (a[i] == a[n]) pos = i;
        else break;
    }
    int cr = cnt[a[n]] - (n - pos + 1);
    for (int i = 1; i <= n; i++)
        if (i != a[n]) cr += cnt[i];
    for (int i = 1; i <= n; i++)
        if (fst[a[i]] == 0) fst[a[i]] = i;
    int premax = 0;
    for (int i = 1; i <= n; i++){
        if (fst[a[i]] == i){
            f[i] = 1;
            f[i] = std::max(f[i],premax + 1);
        }else{
            f[i] = f[pre[i]] + 1;
        }
        if (lst[a[i]] == i) premax = std::max(premax,f[i]);
    }
    int ct = 0;
    int ans = n - f[n];
    for (int i = 1; i <= n; i++){
        if (a[i] == a[n]) continue;
        if (lst[a[i]] == i) ans = std::min(ans,cr - f[i]);
    }
    for (int i = 1; i <= n; i++)
        if (cnt[i] == 0) cnt[i] = -inf;
    build(1,1,n);  
    for (int i = 1; i <= n; i++){
        cge(1,a[i],a[i],-1);
        if (lst[a[i]] != i) continue;
        if (a[i]-1>=1)cge(1,1,a[i]-1,f[i]);
        if (a[i]+1<=n)cge(1,a[i]+1,n,f[i]);
        ans = std::min(ans,n - query(1,1,n));
        if (a[i]-1>=1)cge(1,1,a[i]-1,-f[i]);
        if (a[i]+1<=n)cge(1,a[i]+1,n,-f[i]);
    }
   std::cout << ans;
}
}signed main(){wxy::main(); return 0;}
```

---

## 作者：WaterSun (赞：4)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18541666)

# 思路

首先答案上界为 $n$，因为每本书操作一次一定能使得书架整齐。

因此考虑计算有多少本书能不操作，定义 $dp_i$ 表示以 $i$ 为开头的后缀中，最多能保留多少本书不动。答案显然为 $n - dp_1$，考虑转移：

- 如果 $i$ 位置选择操作，显然有 $dp_i \leftarrow dp_{i + 1}$。

- 如果 $i$ 位置选择不操作，有 $dp_i \leftarrow cnt_{a_i} + dp_{R_{a_i} + 1}$。其中 $cnt_i$ 表示后缀颜色 $i$ 出现数量，$R_i$ 表示最后一个颜色 $i$ 的书出现的位置。

但是你发现这个东西是有一些问题的，本质上是因为 $a_i$ 不操作需要将 $[i,R_{a_i}]$ 中颜色不为 $a_i$ 的书全部移走。这会导致有两个区间有交，导致有元素被计算重复。解决这个问题最好的方式就是只在 $L_{a_i}$ 加上 $dp_{R_{a_i} + 1}$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define chmax(a,b) (a = max(a,b))

using namespace std;

const int N = 5e5 + 10;
int n;
int cnt[N],dp[N];
int arr[N],L[N],R[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

int main(){
    n = read();
    for (re int i = 1;i <= n;i++){
        R[arr[i] = read()] = i;
        if (!L[arr[i]]) L[arr[i]] = i;
    }
    for (re int i = n;i;i--){
        cnt[arr[i]]++;
        dp[i] = dp[i + 1];
        if (i == L[arr[i]]) chmax(dp[i],cnt[arr[i]] + dp[R[arr[i]] + 1]);
        else chmax(dp[i],cnt[arr[i]]);
    }
    printf("%d",n - dp[1]);
    return 0;
}
```

---

## 作者：Daniel1234 (赞：1)

# 思路

写了一个比较直观的想法。

就是首先取出所有颜色的 $l$ 和 $r$，即在序列中最左边和最右边的位置（没有则为 $-1$）。

然后对右端点排序，设 $dp_i$ 表示当前到第 $i$ 段区间，此时最多保留几个数。转移就是枚举上一个取的颜色，统计答案要从后往前遍历，把 $dp_i$ 代表的区间右边的点的数的出现次数的最大值单独加上再求最大值，最后用 $n$ 减去最大值即可，时间复杂度 $O(n^2)$（设 $n$ 和 $V$ 同阶）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[500005];
struct node{
    int l, r, num;
}b[500005];
bool cmp(node x, node y){
    return x.r < y.r;
}
int dp[500005];
int num[500005];
signed main(){
    cin >> n;
    for(int i = 1; i <= n; i++)b[i].l = b[i].r = -1;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        b[a[i]].num++;
        if(b[a[i]].l == -1)b[a[i]].l = b[a[i]].r = i;
        else b[a[i]].r = i;
    }
    sort(b + 1, b + 1 + n, cmp);
    int st = 1;
    while(b[st].l == -1)st++;
    for(int i = st; i <= n; i++){
        dp[i] = b[i].num;
        for(int j = st; j < i; j++){
            if(b[j].r < b[i].l){
                dp[i] = max(dp[i], b[i].num + dp[j]);
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)num[i]=0;
    int mx = 0;
    int z = n + 1;
    for(int i = n; i >= st; i--){
        while(z - 1 > b[i].r)num[a[--z]]++, mx = max(mx, num[a[z+1]]);
        ans = max(ans, dp[i] + mx);
    }
    cout << n - ans << '\n';
    return 0;
}
```

# 优化

直接用树状数组优化 $dp$ 即可，时间复杂度 $O(n \log n)$（设 $n$ 和 $V$ 同阶）。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[500005];
struct node{
    int l, r, num;
}b[500005];
bool cmp(node x, node y){
    return x.r < y.r;
}
int dp[500005];
int num[500005];
int f[500005];
int lowbit(int x){
    return x & (-x);
}
void change(int now, int val){
    while(now <= n){
        f[now] = max(f[now], val);
        now += lowbit(now);
    }
}
int query(int now){
    int ans = 0;
    while(now){
        ans = max(ans, f[now]);
        now -= lowbit(now);
    }
    return ans;
}
signed main(){
    cin >> n;
    for(int i = 1; i <= n; i++)b[i].l = b[i].r = -1;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        b[a[i]].num++;
        if(b[a[i]].l == -1)b[a[i]].l = b[a[i]].r = i;
        else b[a[i]].r = i;
    }
    sort(b + 1, b + 1 + n, cmp);
    int st = 1;
    while(b[st].l == -1)st++;
    for(int i = st; i <= n; i++){
        dp[i] = b[i].num + query(b[i].l - 1);
        change(b[i].r, dp[i]);
        // cout << dp[i] << " ";
    }
    // cout << '\n';
    int ans = 0;
    for(int i = 1; i <= n; i++)num[i]=0;
    int mx = 0;
    int z = n + 1;
    for(int i = n; i >= st; i--){
        while(z - 1 > b[i].r)num[a[z-1]]++, mx = max(mx, num[a[z-1]]), z--;
        ans = max(ans, dp[i] + mx);
    }
    cout << n - ans << '\n';
    return 0;
}
```

---

## 作者：DerrickLo (赞：1)

考虑到最终答案显然 $\le n$，那么进行的操作一定是将若干个数保留下来，然后将其他数放到末尾，那么我们要做的就是最大化保留下来的数的个数。

考虑保留下来的数需要满足什么条件。如果将保留下来的数分成若干颜色相同的段，那么除了最后一段以外都必须包含所有这种颜色的数。

那么我们记 $f_i$ 表示前 $i$ 个数，选出若干本数，使得这些数排成一段后，如果分成若干颜色相同的段，每段都必须包含所有这种颜色的数，这样能选出的数的最大个数。

至于转移，可以预处理出每种颜色第一次出现的位置 $st_i$，最后一次出现的位置 $ed_i$ 和这种颜色的出现次数 $cnt_i$。那么考虑是否选择第 $i$ 个数，可以得到转移：

$$f_i=\begin{cases}
f_{i-1} & ed_{a_i}\ne i\\
\max\{f_{i-1},f_{st_{a_i}-1}+cnt_{a_i}\} & ed_{a_i}=i
\end{cases}$$

最后我们枚举保留的数中除了最后一段的结尾位置 $i$，那么最后一段显然是贪心地选择 $[i+1,n]$ 中的出现次数最多的数，而这个可以倒着枚举得到。

时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[500005],st[500005],ed[500005],cnt[500005],f[500005],cntt[500005],ans,maxx;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],cnt[a[i]]++;
	for(int i=1;i<=n;i++)ed[a[i]]=i;
	for(int i=n;i;i--)st[a[i]]=i;
	for(int i=1;i<=n;i++){
		f[i]=f[i-1];
		if(ed[a[i]]==i)f[i]=max(f[i],f[st[a[i]]-1]+cnt[a[i]]);
	}
	for(int i=n;i;i--){
		ans=max(ans,f[i]+maxx);
		cntt[a[i]]++,maxx=max(maxx,cntt[a[i]]);
	}
	cout<<n-ans;
	return 0;
}
```

---

## 作者：wrzSama (赞：1)

## 题目大意

给定一个长度为 $n$ 的颜色序列 $a$，每次操作可以把一个元素放在序列的最右端，问让相同颜色的元素放在一起的最小操作次数。

## 思路

我们发现只要将几个颜色相同的元素之间的元素全部操作走，那么这几个相同颜色的元素就放在了一起，而这几个元素不需要被操作。因此，我们可以 $dp$ 不需要被操作的元素的最大数量。设 $dp_i$ 表示令区间 $[i,n]$ 之间的元素满足相同颜色的元素放在一起的不需要被操作的元素的最大数量，$c_i$ 记录颜色为 $i$ 的元素数量,$l_i$ 记录颜色为 $i$ 的元素最靠左出现的位置，$r_i$ 记录颜色为 $i$ 的元素最靠右出现的位置。从大到小枚举 $i$，当加进来一个元素 $a_i$，先令 $c_{a_i}$ 加 $1$。如果与它颜色相同的元素都在它右边即 $l_{a_i}=i$，那么 $dp_i=max(dp_{i+1},c_{a_i}+dp_{r_{a_i}+1})$，即尝试用所有颜色 $a_i$ 的元素都不操作来更新答案；如果 $l_{a_i} \neq i$，那么尝试用颜色为 $a_i$ 且在 $i$ 及其右边的元素不操作来更新答案，因为左边还有颜色为 $a_i$ 的元素需要放在这，所以就不能从 $dp_{r_{a_i}+1}$ 转移，$dp_i=max(dp_i,c_{a_i})$。最后，输出 $n-dp_1$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,m,a[500005],dp[500005],l[500005],r[500005],c[500005];
int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
		if(!l[a[i]]) l[a[i]]=i;
		r[a[i]]=i;
	}
	for(int i=n;i;--i)
	{
		dp[i]=dp[i+1];
		++c[a[i]];
		if(i!=l[a[i]]) dp[i]=max(dp[i],c[a[i]]);
		else dp[i]=max(dp[i],c[a[i]]+dp[r[a[i]]+1]);
	}
	write(n-dp[1]);
	return 0;
}
```


---

## 作者：qfpjm (赞：1)

# 题解

- 此题 $n$ 较大，考虑 $O(n)$ 的解法。

- 我们肯定会想到动归，由于移动的书不好用于转移，所以我们定义 $dp_i$ 为以 $i$ 开头的后缀中不移动的书数量的最大值。

- 我们还要记录颜色 $a_i$ 出现的第一个位置与最后一个位置 $st_{a_i},ed_{a_i}$，以及后缀中颜色 $a_i$ 的数量 $cnt_{a_i}$。

- 考虑如何转移。首先，如果要将这本书一道末尾，那么 $dp_i=dp_{i+1}$。然后我们再分两种情况考虑：

1.  这本书的颜色 $a_i$ 是颜色 $a_i$ 第一次出现的地方，那么我们可以将其与最后一次出现的位置之间异色的书移走，状态转移方程为：$dp_i=\max(dp_i,cnt_{a_i}+dp_{ed_{a_i}+1})$；

1. 如果不是，那么我们将后缀中的全部已到末尾，这样才是更优的，状态转移方程为：$dp_i=cnt_{a_i}$。

- 由于是从后往前推，而且状态设计是不动的书的最大值，所以最后的答案为：$n-dp_1$。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a[500005], st[500005], ed[500005], cnt[500005], dp[500005];

int main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
		if (!st[a[i]])
		{
			st[a[i]] = i;
		}
		ed[a[i]] = i;
	}
	for (int i = n ; i >= 1 ; i --)
	{
		dp[i] = dp[i + 1];
		cnt[a[i]] ++;
		if (i != st[a[i]])
		{
			dp[i] = max(dp[i], cnt[a[i]]);
		}
		else
		{
			dp[i] = max(dp[i], dp[ed[a[i]] + 1] + cnt[a[i]]);
		}
	}
	cout << n - dp[1];
}
```


---

## 作者：shenmadongdong (赞：1)

可以把问题倒过来想，考虑可以有多少种书不动

可以考虑通过通过一个dp来记录 $[1,i]$ 区间中每种书所在的范围互不相交可以取到的最多本书

当所在位置是某一种书的最后一本时，将其与这种书的最左边一本书的左边的书的状态与这种书的本数的和取 max，这样就可以转移了

最多的不动的书就是每个点左边互不相交可以取到的最多本书数目和右边出现最多次的一种书的数目之和取个 max

代码大概长这样：
```cpp
#include<bits/stdc++.h>
int n,a[500010],l[500010],r[500010],dp[500010],mx[500010],cnt[500010],ans;
int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) !l[a[i]]&&(l[a[i]]=i),r[a[i]]=i;
	for(int i=n;i>=1;i--) cnt[a[i]]++,mx[i]=std::max(mx[i+1],cnt[a[i]]);
	for(int i=1;i<=n;i++) dp[i]=dp[i-1],r[a[i]]==i&&(dp[i]=std::max(dp[i],dp[l[a[i]]-1]+cnt[a[i]])),ans=std::max(ans,dp[i]+mx[i+1]);
	std::cout<<n-ans<<'\n';
	return 0;
}
```

---

## 作者：Phobia (赞：0)

正难则反，注意到一本书最多只会移动一次，考虑最多留下几本书。

显然有留下来的书一定是已经排好的，或者最右边一段相同的书还剩下一点（这点从样例二中可以发现，而且也就最右边的书能接上），然后枚举一下就做完了。

写得 $\mathcal{O}\left(n\log n\right)$ 比较糙，精细实现可以做到 $\mathcal{O}\left(n\right)$。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

inline int read()
{
    int res = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        ;
    for (; isdigit(ch); ch = getchar())
        res = (res << 3) + (res << 1) + (ch & 15);
    return res;
}

const int N = 5e5 + 5;

int n, m, a[N], tre[N];

vector<int> hsh[N];

struct node
{
    int l, r, id;
    bool operator<(const node& rhs) const
    {
        return r < rhs.r;
    }
} b[N];

void add(int x, int v)
{
    for (; x <= n; x += x & -x)
        tre[x] = max(tre[x], v);
}

int get(int x)
{
    int ans = 0;
    for (; x >= 1; x -= x & -x)
        ans = max(ans, tre[x]);
    return ans;
}

int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        hsh[a[i] = read()].push_back(i);
    for (int i = 1; i <= n; ++i)
    {
        if (hsh[i].empty())
            continue;
        b[++m] = (node){ *hsh[i].begin(), *hsh[i].rbegin(), i };
    }
    sort(b + 1, b + m + 1);
    for (int i = 1; i <= m; ++i)
        add(b[i].r, get(b[i].l - 1) + hsh[b[i].id].size());
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < hsh[i].size(); ++j)
            ans = max(ans, get(hsh[i][j] - 1) + (int)hsh[i].size() - j);
    }
    printf("%d\n", n - ans);
    return 0;
}
~~~

---

## 作者：XFlypig (赞：0)

首先有个最简单的观察，被移动的书在序列右侧可以随便排列。

由于和序列后面关联性很强，所以考虑倒序 DP。

设 $f_i$ 表示从 $i$ 到 $n$ 能留下来的最多的书，同时要满足一个条件，即对于某一颜色而言，若左侧还有未被考虑的书，那么已经被考虑的那些书要么都是被移动过的，要么
满足他们右侧没有不移动的书，也就是前面的同色书移动后可以接到它们后面。

转移式很简单，不选直接继承。选的话由于要满足条件，所以如果当前的书是它的同色书中最左侧的一本，那么可以加上右端点后一个位置的 DP 值，如果不是，由于要满足条件，所以除同色书其余的都要移动，转移代码如下。

```cpp

cnt[col[i]] ++ ;
f[i] = f[i + 1];
f[i] = max(f[i], cnt[col[i]]);
if (i == Left[col[i]])
    f[i] = max(f[i], cnt[w[i]] + f[Right[col[i]] + 1]);

```
答案即为 $n - f_1$。

---

## 作者：AIskeleton (赞：0)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16838444.html)

$* \text{Defficult:} \color{Red}{2500}$

一道很有 AT 风格的 DP。

## Description

有 $n$ 本书，每本书有一个颜色，每次操作可以将一本书移动到最右。

求问使所有相同颜色的书相邻的最小移动次数。

$n \le 5 \cdot 10^5$

## Solution

首先可以想到，最大的移动次数不会超过 $n$，且每本书的移动次数不会超过一次。

因为显然，所有书按照颜色排序然后分别移动即可。

反向考虑，设法求出不用移动的书的最大值。

对于每种颜色的数，记录其最左边出现的位置 $l_i$，和最右边出现的位置 $r_i$。

设 $f_i$ 表示使位置在范围 $[i,n]$ 之内的书按照要求排列的**最大不移动的书的数量**。

考虑如何转移：

首先，所有情况下的 $i$，都可以选择移动，使之与其他同颜色的书相邻，即 $f_i =f_{i+1}$。

转移的过程中，记录此时每种书的出现次数 $cnt_i$。

剩下的转移要分情况讨论。

- $i = l_{a_i}$

此时可以选择不移动所有颜色为 $a_i$ 的书，有转移 $f_{i} = cnt_{a_i} + f_{r_{a_i} +1}$。

- $i \ne l_i$

跟上面一样，考虑颜色为 $a_i$ 的书不移动。

此时的转移是 $f_i = cnt_{a_i}$。

比如考虑 $[1,2,2,1,1,3]$，当前 $i=4$ 的情况。

如果选择上述转移，实际上的操作是：

$[1,2,2,1,1,3] \implies [2,2,1,1,3,1] \implies [2,2,1,1,1,3]$，操作次数为 $2$，等于 $cnt_{a_i}$。

总结一下，状态转移方程式是：
$$
f_i = \max \begin{cases}f_{i+1}\\cnt_{a_i}&i \ne l_{a_i}\\f_{r_{a_i}+1}&i=l_{a_i}\end{cases}
$$
最后的答案就是 $n-f_1$。

时间复杂度：$O(n)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define L(i,j,k) for(int (i)=(j);i<=(k);(i)++)
#define R(i,j,k) for(int (i)=(j);i>=(k);(i)--)
#define FST ios::sync_with_stdio(0);cin.tie(0);
const int N=2e6+100;
int n,a[N],l[N],r[N],cnt[N],f[N];
signed main(){
  FST;cin>>n;L(i,1,n) cin>>a[i],r[a[i]]=i;
  L(i,1,n) if(!l[a[i]]) l[a[i]]=i;
  R(i,n,1){
    cnt[a[i]]++;if(i==l[a[i]]) 
        f[i]=max(cnt[a[i]]+f[r[a[i]]+1],f[i+1]);
    else f[i]=max(f[i+1],cnt[a[i]]);
  }cout<<n-f[1];
}//CSP-S 2022 RP++
```


---

