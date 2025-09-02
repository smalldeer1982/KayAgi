# [USACO19JAN] Sleepy Cow Sorting G

## 题目背景

USACO 19年一月月赛金组第二题

## 题目描述

Farmer John正在尝试将他的 $N$ 头奶牛（$1\le N\le 10^5$），方便起见编号为 $1\ldots N$，在她们前往牧草地吃早餐之前排好顺序。

当前，这些奶牛以 $p_1,p_2,p_3,\ldots,p_N$ 的顺序排成一行，Farmer John站在奶牛 $p_1$ 前面。他想要重新排列这些奶牛，使得她们的顺序变为 $1,2,3,\ldots,N$，奶牛 $1$ 在 Farmer John 旁边。

今天奶牛们有些困倦，所以任何时刻都只有直接面向 Farmer John 的奶牛会注意听 Farmer John 的指令。每一次他可以命令这头奶牛沿着队伍向后移动 $k$ 步，$k$ 可以是 $1$ 到 $N−1$ 之间的任意数。她经过的 $k$ 头奶牛会向前移动，腾出空间使得她能够插入到队伍中这些奶牛之后的位置。

例如，假设 $N=4$，奶牛们开始时是这样的顺序：

```plain
 FJ: 4 3 2 1
```

唯一注意 FJ 指令的奶牛是奶牛 $4$。当他命令她向队伍后移动 $2$ 步之后，队伍的顺序会变成：

```plain
 FJ: 3 2 4 1 
```

现在唯一注意 FJ 指令的奶牛是奶牛 $3$，所以第二次他可以给奶牛 $3$ 下命令，如此进行直到奶牛们排好了顺序。

Farmer John 急欲完成排序，这样他就可以回到他的农舍里享用他自己的早餐了。请帮助他求出一个操作序列，使得能够用最少的操作次数将奶牛们排好顺序。

## 样例 #1

### 输入

```
4
1 2 4 3```

### 输出

```
3
2 2 3```

# 题解

## 作者：HRLYB (赞：25)

[P5200 Sleepy Cow Sorting](https://www.luogu.org/problem/P5200)


我们发现，如果数列的后缀是递增的，那么是可以不用处理的.

由此引申出一种思路：把整个序列分成两个部分，前一个部分是还未排好序的，后一个部分是已经排好序的.

又因为每头牛最多被移动一次（显然每次只能移动队头，最多$n-1$次就可以保证有序了），后缀不用移动，因此，从后往前数第一个**不递减的数**，1~它全都得移动（不然移动不了它），它的位置就是最小移动数. 


最小移动数求得后，还要求每头牛移动的距离. 这也不难想到，该距离就是当前未排好序的序列的长度-1 加上 这个元素应该在排好序的序列中的位置**前面元素**的数量.


为此应该维护一个最长的上升后缀，每一次插入到这个数在上升后缀应该在的位置.

我们不妨设计$1-n$的数组，其中$1$表示该元素已经在排好序的序列中，$0$表示该元素还未排序. 那么我们就可以知道指定元素的“前面元素”的数量了.

也就是说，对于已排好的序列，我们需要一种数据结构，支持计算前缀和和单点修改. 

### 而且1e5的数据规模，复杂度大约在$O(nlogn)$左右

~~不难想到使用树状数组.~~

然后本题就完成了.


```cpp
#include<bits/stdc++.h>
#define maxn 100010
using namespace std;
int n,a[maxn],tree[maxn],ans[maxn];
int lowbit(int x){return x&(-x);}
void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i))tree[i]+=k;
}
int query(int x){
	int ret=0;
	for(int i=x;i;i-=lowbit(i))ret+=tree[i];
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int k=0,sum=n;
	while(a[n-k]>a[n-k-1]){
		add(a[n-k],1);//加入有序序列
		sum--;
		k++;
	}
	add(a[n-k],1),sum--;//无论如何，都要把后缀的第一个元素加入，a[n-k]<a[n-k-1]，a[n-k]才是不降后缀的第一个元素
	for(int i=1;i<=sum;i++){
		add(a[i],1);
		ans[i]=sum-i+query(a[i]-1);//求有序序列前缀和
	}
	printf("%d\n",sum);
	for(int i=1;i<=sum;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```
我们主要要学习这题的分段维护思想，分段处理是否排好序的情况，把复杂问题分解为已解决不影响后面操作和未解决两部分，既方便思考，也方便写代码.



---

## 作者：SymphonyOfEuler (赞：20)

这题是树状数组好题，~~竟然是紫题~~，但是既然是教练的，我就写篇题解吧。

我是学了线段树又学的树状数组，~~以后永远不写线段树了~~，而且还比线段树快，教练让我们痛苦了那么长时间，wtnl。

### **关于树状数组：**

不会树状数组的可以戳[这里](https://www.luogu.com.cn/problem/P3374#submit)做一下模板。~~但是我稍微BB两句~~

树状数组就是巧妙地运用了lowbit函数，表示离父亲还有多少步。此处lowbit就是转换二进制，然后取反，之后加一，这就是lowbit。

定一个c数组维护这个数列上某个区间的和。

这样造出了一棵树，单点修改就是沿着树往右走，修改所有的c。

此处单点修改和区间查询复杂度都是$O(log n)$，建树复杂度$O(n log n)$常数比线段树都小。 

### **这题思路：**

只要数列中逆序对 $i<j$ && $p_i>p_j$ 那么就需要往后移动。
所以只有后面的数不用动，所以队尾都不是逆序。所以我们计算一下末尾的那几个数的长度，这就是有多少个不用操作的数，这样第一问的$K$就解决了。

我们用树状数组维护目前出现过的元素。

我们用update函数标记这个区间$p_i$ 这个地方。
 
我们可以然后从1到k循环，得到答案，求完答案再update一下就做完了。

具体可以看注释

```
#include <bits/stdc++.h>

using namespace std;


const int MAXN = 500005;

int n;

int c[MAXN], a[MAXN];

inline int lowbit(int x) { return x & -x; }//lowbit

void update(int x) {//标记函数
    while (x <= n) {
        c[x]++;
        x += lowbit(x);
    }
}

int sum(int x) {//求和函数
    int res = 0;
    while (x > 0) {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    int k = n - 1;
    while (k > 0 && a[k] < a[k + 1]) { //求k
        k--;
    }
    printf("%d\n", k); //先输出k
    for (int i = k + 1; i <= n; ++i) { //一开始标记不需要动的
        update(a[i]);
    }
    for (int i = 1; i <= k; ++i) { //求需要动的答案
        printf("%d ", k - i + sum(a[i]));
        update(a[i]);
    }
    printf("\n");
    return 0;
}
```

看蒟蒻写的这么认真，点个赞再走呗~


---

## 作者：Boeing737_MAX_8 (赞：15)

### 【转+翻译】

毕竟这是USACO的题，官方有题解，~~在这里缺席似乎不太好~~，**讲得很详细**，虽然和已有的几篇意思相近，但我还是给一下。

### 翻译+解释

首先我们思考一下，如果答案是k，**意味着什么**？ 这意味着**最后有n-k个数**没有被操作过（**没有被变更过顺序**）


**也就是说k有一个下限，也就是答案**：那**n-k个不用变更顺序的数字以外的数字**将会**插入到末尾k个**已经构建顺序的**元素中的正确的位置**中。

**例如：**$(3, 4, 5, 2, (1, 6)) \rightarrow (4, 5, 2, (1, 3, 6)) \rightarrow (5, 2, (1, 3, 4, 6)) \rightarrow (2, (1, 3, 4, 5, 6)) \rightarrow (1, 2, 3, 4, 5, 6)$

现在我们要干的，就是得到那长度为n-k的指令序列。容易发现，在队头牛的移动步数即是**未排序的牛数量-1加上后面已经建立顺序的牛中小于队头牛的数量。** 例如以上例子中，第一头牛需要移动3+1步。

每次完成这个操作后，队头的牛将会成为已经被排序的牛的一部分。**不幸的是，这个naive的算法的复杂度最差能达到 $O(N^2)$**

~~别灰心，别去看下一篇题解，还没完~~

我们可以**通过数据结构来优化**这个$N^2$玩意：**维护一个集合$S \subseteq \{1,\dots,n\}$，并可以高效地执行以下操作：**

1. 往$S$中插入$x \in \{1,\dots,n\}$
2. 对于一个$y \in \{1,\dots,n\}$，询问集合中小于y的元素个数

有很多数据结构可以解决，最简单的或许是树状数组（Fenwick tree），一种**支持单点修改，和区间查询**（问询$A_1 + \dots + A_i$)的数据结构，~~（如不会，请自行B**du)~~

 _原文中稍稍对实现进行了一点解释，但我认为树状数组不用在这里多说了_
 
两种操作都只需要**对数级别的时间**，算法执行$O(n)$次这样的操作，**复杂度也就是$O(N \log N)$**

**对我的翻译和解释有异议和疑问，欢迎评论或私信。**

代码见后

### 原文
(Analysis by Franklyn Wang and Dhruv Rohatgi)
We first ask ourselves, if the answer is $k$, what does that entail? If the answer is $k$, this means that none of the final $n - k$ change their relative order, and that they must already be in order.

This gives a lower bound on $k$. It turns out that it also gives the answer, since we can insert the other $n - k$ numbers into their correct positions in the last numbers $k$.

For an example: $(3, 4, 5, 2, (1, 6)) \rightarrow (4, 5, 2, (1, 3, 6)) \rightarrow (5, 2, (1, 3, 4, 6)) \rightarrow (2, (1, 3, 4, 5, 6)) \rightarrow (1, 2, 3, 4, 5, 6)$

Now we need to find a sequence of instructions of length $n-k$. The first instruction is the number of unsorted cows minus one, plus the number of cows in the sorted suffix with indices smaller than the first cow's index. In the above example, the first cow needs to move $3 + 1$ spaces down the line.

After this instruction, the first cow will become part of the sorted suffix, and we recurse. Unfortunately, a naive implementation of this algorithm will take $O(N^2)$ time in the worst case.

We can speed it up with a data structure that maintains a set $S \subseteq \{1,\dots,n\}$ and performs the following operations efficiently: (1) For some $x \in \{1,\dots,n\}$, insert $x$ into $S$; (2) for some $y \in \{1,\dots,n\}$, count the number of elements of $S$ which are smaller than $y$.

There are a number of data structures which can solve this; perhaps the simplest is a Fenwick tree, which supports point updates (add $v$ to element $i$ of an array $A$) and prefix sums (given some $i$, compute $A_1 + \dots + A_i$). Inserting an element $x$ corresponds to incrementing $A_x$, and counting the elements smaller than $y$ corresponds to computing $A_1 + \dots + A_{y-1}$.

Both operations take logarithmic time, and the algorithm performs $O(N)$ such operations, for an overall time complexity of $O(N \log N)$.

```
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100100
 
int T[MAXN];
 
void inc(int i)
{
	for(i++;i<MAXN;i+=(i&-i))
		T[i]++;
}
 
int getSum(int i)
{
	int c = 0;
	for(i++;i>0;i-=(i&-i))
		c += T[i];
	return c;
}
 
 
int p[MAXN];
 
int main()
{
	int N;
	cin >> N;
	for(int i=0;i<N;i++)
	{
		cin >> p[i];
		p[i]--;
	}
	int j = N-1;
	while(j > 0 && p[j-1] < p[j])
		j--;
	cout << j << '\n';
	for(int i=j;i<N;i++)
		inc(p[i]);
	for(int i=0;i<j;i++)
	{
		cout << (j - 1 - i) + getSum(p[i]);
		if(i < j - 1) cout << ' ';
		inc(p[i]);
	}
	cout << '\n';
	return 0;
}
```

---

## 作者：CYJian (赞：13)

感觉这一次USACO Gold的题目好简单啊。。~~一小时没有就AK了。。~~

---

这道题的话。。~~如果做了Bronze的童鞋就知道这道题就是多输出了一个方案数~~

其实还是很简单。。

这道题的思路非常简单，我们只要维护一个最长的上升后缀，每一次插入的话就插入到这个数在上升后缀应该在的地方就好了。。

如何找到这个位置呢？？

非常简单，就是 当前需要插入的数的位置到上升后缀的最前端的距离+上升后缀里面小于当前数的数的个数。这个东西就是当前这个数需要往后挪动的距离。

对于求有多少个数小于当前数，可以使用树状数组,非常短~~(函数就两行)~~

```
#include <bits/stdc++.h>

using namespace std;

#define reg register
#define ge getchar()
#define Re read()
#define FI "sleepy.in"
#define FO "sleepy.out"
#define MAXN 100000

inline int read() {
	reg int x = 0, ch;
	while(!isdigit(ch = ge)) ;
	while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = ge;
	return x;
}

int a[MAXN + 1];
int T[MAXN + 1];

inline void Add(reg int p) { while(p <= MAXN) T[p]++, p += p & -p; }
inline int Ask(reg int p) { reg int x = 0; while(p) x += T[p], p ^= p & -p; return x; }

int main() {
	reg int n = Re;
	for(reg int i = 1; i <= n; i++) a[i] = Re;
	reg int la = n + 1;
	for(reg int i = n; i >= 1; i--) {
		if(a[i] > la) {
			printf("%d\n", i);
			for(reg int j = 1; j <= i; j++) {
				printf("%d%c", i - j + Ask(a[j]), " \n"[j == i]);
				Add(a[j]);
			}
			break;
		}
		la = a[i], Add(a[i]);
	}
}
```

---

## 作者：Yang818 (赞：6)

**十分建议做这道题前把两道树状数组的模板题做好**

## 题目大意

有 $n$ 个数字，按照打乱的顺序排放。你每次可以操控第一个数字，让它往后移任意位。最后要求这些数按照从小到大的顺序排列。

第一问是：最少移动几次可以移动完。

第二问是：每次移动几个。

这道题把第一小问做出来了，第二小问其实就迎刃而解了。

## 分析

本蒟蒻当然不会一下就想到正解，于是就随便拿两组数据试了试：

| 样例 | 移动次数 |
| -----------: | -----------: |
| 124356 | 3 |
| 342516 | 4 |
| 516342 | 5 |

到这里其实很多大佬已经可以看出来了，但本人毕竟还是蒟蒻，没看出来规律。因为对那些不用移动的数字特别烦感，于是决定把它们拿出来研究研究。

| 样例 |不用移动的数字| 移动次数 |
| -----------: | -----------: | -----------: |
| 124356 | 356 | 3 |
| 342516 | 16 | 4 |
| 516342 | 2 | 5 | 


通过上图，本蒟蒻终于发现了其中的奥妙。
**不用移动的数字其实就是从结尾开始倒着看的不上升连续序列**
我们来证实一下：

因为最后要排列成上升序列，并且还要移动次数最少，所以我们要把前面的数插在一个最一开始就上升的子序列里，这样就可以不用移动这个序列中原本的元素，达到最少移动的效果，但是每次只能移动第一个数字，所以这个序列必须是连续的，并且最后一位是结尾。

**第一问就这样搞定了！**
```cpp
	int ans;
	for(ans=n;a[ans]>a[ans-1];ans--){
		......
	}
	......
	cout<<ans<<endl;
```
做第二问的时候需要看这个数在第一问求出的不用移动的数字中应该排在第几位，这就用到了树状数组。

每次找到一个不用移动的数字，就在把这个数字作为下标在树状数组中加一。之后插入数字的时候只用查树状数组中有多少个比待插入的数字小的就可以得到往后移动几位了。

## 代码

代码还需要吗？

```cpp
#include<bits/stdc++.h>
using namespace std;

int t[500010],g_n,g_m;//本题不开long long 也可以

int lowbit(int x){
	return x&-x;
}
int g_a[500010];
void modify(int x,int delta){//标准树状数组函数
	for(int i=x;i<=g_n;i+=lowbit(i))
		t[i]+=delta;
}

int query(int x){
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i)){
		ans+=t[i];
	}
	return ans;
}
int main(){
	cin>>g_n;
	for(int i=1;i<=g_n;i++){
		cin>>g_a[i];
	}
	int ans;
	for(ans=g_n;g_a[ans]>g_a[ans-1];ans--){//第一问
		modify(g_a[ans],1);
	}
	modify(g_a[ans--],1);
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++){
		cout<<ans-i+query(g_a[i])<<" ";//这个原理上面解释了
		modify(g_a[i],1);
	}
	return 0;
}

```

---

## 作者：lukelin (赞：3)

**[安利一下我的博客](https://www.cnblogs.com/linzhengmin/p/11039120.html)**  
拿到这个问题，我们从头开始思考。  
我们把序列看做两部分，一部分在前表示**待排序**的，记为**序列1**，一部分在后表示**已排序**的，记为**序列2**。  
因为**序列2**在后，所以不必担心它影响**序列1**的排序，那么对于**序列1**的第一个元素，显然珂以放到**序列2**的某个对应位置，使**序列2**仍然保持有序  
那么很简单，我们发现只需要将**序列1**的**每个元素**都移动一次即可完成排序，这显然是最优的  
讲一下初始化，对于**序列2**，我们发现显然从最后一个逆序对的**第二个元素**开始一直到**序列的最后一个元素**珂以直接作为**序列2**的，那么剩下的元素按原来的顺序放入**序列1**，接下来我们珂以直接模拟这个操作。  
目前的复杂度是$\Theta(n^2)$，显然对于本题来说无法通过。  
那么消耗时间比较多的部分是什么呢？就是如何找到**序列1的第一个元素**在序列2中的**对应位置**（换而言之就是计算答案）。  
我们需要在$\Theta(log_2n)$的时间内求出**序列1的第一个元素**在序列2中的**对应位置**（为什么是$\Theta(log_2n)$而不是$\Theta(1)$看数据范围就知道啦）。首先我们发现**序列2**是有序的，无需模拟，然后怎么做呢？基于$\Theta(log_2n)$的复杂度，我们想到了神奇的树状数组，开始在**序列2**中的所有元素的位置上插入一个1，然后对于**序列1**的第i个元素，记为$a_i$，我们只需要查询$[1,a_i)$有几个数就知道答案了，然后再往$a_i$的位置上插入一个1，持续模拟即可。  

好了放个代码  
```cpp
#include <cstdio>
#include <vector>
#define ll long long

using namespace std;

ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int p[100005];
int fen[100005];

#define lowbit(x) (x&(-x))

int n;

void add(int pos){
    for ( ; pos <= n; pos += lowbit(pos)) ++fen[pos];
}

int query(int pos){
    int sum = 0;
    for ( ; pos; pos -= lowbit(pos)) sum += fen[pos];
    return sum;
}

vector<int> ans(0); 

int main(){
    n = read(); bool flg = 1;
    for (int i = 1; i <= n; ++i){
        p[i] = read();
        if (p[i] != i) flg = 0;
    }
    if (flg){puts("0"); return 0;}
    int i;
    for (i = n; i >= 1; --i)
        if (p[i] < p[i - 1])
            break;
    for (int j = i; j <= n; ++j)
        add(p[j]);
    for (int j = 1; j < i; ++j){
        ans.push_back(query(p[j]) + i - j - 1);
        add(p[j]);
    }
    printf("%d\n", ans.size());
    for (int j = 0; j < ans.size(); ++j)
        printf("%d%c", ans[j], ((j == ans.size() - 1) ? '\n' : ' '));
    return 0;
}
```

---

## 作者：lxxwxxxxx (赞：3)

一道十分经典的树状数组的题目。

看到这道题目时，我莫名地想到了那道求冒泡排序操作数的题，但是这道题与那道题不同的是，这道题的对象是固定唯一的。但是我们仍然可以将其转化为冒泡排序的题。

很容易，我们能发现这个这个序列可以分为两部分，一部分是位于前段的“非有序序列”，里面包含的元素**不是一直单调递增的**。另一部分是位于后段的“有序序列”，里面的元素肯定是单调递增的。而第一部分的末尾，就是两部分的分界，也是第一问的答案。

要想求出这个分界点，我们只需从后往前枚举，保证元素从后往前递减就行了（千万不要从前往后，我刚开始就是错在这里的）。

这时候，我们考虑前半部分，那是需要操作的部分。

我们将后半部分作为参照，前半部分里每个元素作为需要移动的对象，从左往右枚举对象，一个对象需要移动的距离是其位置与分界的距离，加上在后半部分其应呆的位置与分界的距离。说起来有点绕，但是说白了就是在后半部分找到一个位置，使其前面的元素刚好小于当前对象，后面的元素刚好大于当前对象，然后用这个位置与对象的位置求取距离，这就是一个对象需要移动的距离，也就是第二问的答案。

要想快速求取后半部分中比对象小的元素，我们可以用线段树来维护，然后用求在第二部分里有多少数是小于这个对象的。

```cpp
#include<iostream>
#include<cstdio>
#define Maxn 120000
using namespace std;
typedef long long ll;
int n,num[Maxn],ans1;
struct Tree{//树状数组 
	ll tree[Maxn];
	ll lowbit(ll x){return x&(-x);}
	void add(ll i,ll x){for(;i<=n;i+=lowbit(i)) tree[i]+=x;}
	ll search(ll i){ll res=0;for(;i;i-=lowbit(i))res+=tree[i];return res;}
}t;
int main(){
	scanf("%lld",&n);
	ans1=n;
	for(ll i=1;i<=n;i++) scanf("%lld",&num[i]);
	while(ans1&&num[ans1-1]<num[ans1]) ans1--;//一定要从后往前枚举 
	ans1--;//分界是在第一部分的，而此时的 ans1 是在第二部分的临界点的，所以要跳到第一部分去 
	printf("%lld\n",ans1);
	for(ll i=ans1+1;i<=n;i++) t.add(num[i],1);//我们将第二部分存入树状数组中作为对照 
	for(ll i=1;i<=ans1;i++){printf("%lld ",ans1-i+t.search(num[i]));t.add(num[i],1);}//经典的逆序对问题 
	//移动的距离是当前位置与分界的距离加上在第二部分有多少数是小于当前对象点的
	//在处理完一个对象后，我们要将它放入后半部分中，也就是存入树状数组中 
	return 0;
}
```


---

## 作者：ValiZpg (赞：2)

贪心嘛，思路还是很简单的。。。

引用前一篇大佬题解的话，“我们只要维护一个最长的上升后缀，每一次插入的话就插入到这个数在上升后缀应该在的地方就好了”。

插在哪个位置，也就是查找当前数在上升后缀中的排名
我一瞧，这不是明摆着的平衡树吗，只需提供插入和排名操作吗？

本蒟蒻手残，不想打替罪羊，于是就用pbds凑合了【~~不要揍我~~】

下面贴上我丑陋的代码....

```
#pragma comment(linker,"/STACK:1024000000,1024000000")
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define ms(a,x) memset(a,x,sizeof a)
#define sz(x) (int)(x.size())
#define pb push_back
#define mkp make_pair
#define inf 0x3f3f3f3f
#define N 100005
using namespace std;
using namespace __gnu_pbds;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
using Balanced_Tree=tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>;
Balanced_Tree seq;
int n,a[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	ms(a,0x3f);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n;i&&a[i]<a[i+1];i--) seq.insert(a[i]);
	int k=n-sz(seq);
	cout<<k<<endl;
	for(int i=1;i<=k;i++){
		cout<<n-sz(seq)+seq.order_of_key(a[i])-1;
		if(i!=k) cout<<" ";
		seq.insert(a[i]);
	}
	return 0;
}

```

---

## 作者：king_xbz (赞：1)

这道题做出来的关键在于如何划分序列进而进行贪心求解。

我们可以把序列截成两段，前半段满足递减，然后我们只需修改后半段即可。

而在后半段的非单调序列中，我们需要求出该列长并依次进行修改即可。

具体进行单点修改和区间查询的操作我们可以用线段树或数状数组。

这里我们选用比较好写的树状数组，复杂度大概在O(nlogn)。

具体代码实现：
```cpp
inline int lowbit(int x)
{
	return x&(-x);//lowbit
}

inline void adds(int x,int y)
{
	for(fint i=x;i<=ns;i+=lowbit(i))
	tree[i]+=y;
	return ;//单点修改
}

inline int get_tot(int x)
{
	int ans=0;
	for(fint i=x;i;i-=lowbit(i))
	ans+=tree[i];//区间查询
	return ans;
}
```
树状数组的lowbit，求和，修改

PS:不了解树状数组的可以->[树状数组模板题的讲解](https://www.luogu.com.cn/blog/kingxbz/solution-p3368)（趁机安利我的博客）

然后是贪心的实现；

我们可以使用do-while循环结构，并定义flag作为循环边界以便及时终止
```cpp
inline void begin_todo()
{
	int now=n+1;
	do
	{
		if(a[n]>now)//如果不满足递减
	    cout<<n<<endl,flag=1;
	    if(flag)
	    for(fint i=1;i<=n;i++)
	    cout<<n-i+get_tot(a[i])<<" ",adds(a[i],1);
	    adds(a[n],1),now=a[n];//更新最长递减序列
	}
	while(n--&&!flag);//终止循环条件
	return ;
}
```
最后上完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define fint register int
#define p 436534
#define h 5001
using namespace std;
int n,ns;
bool flag;
int tree[p];
int a[p];
inline int read();
inline int lowbit(int x);
inline void begin_todo();
inline int get_tot(int x);
inline void adds(int x,int y);
signed main()
{
	n=read(),ns=n;
	for(fint i=1;i<=n;i++)
	a[i]=read();
	begin_todo();
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
} 

inline int lowbit(int x)
{
	return x&(-x);
}

inline void adds(int x,int y)
{
	for(fint i=x;i<=ns;i+=lowbit(i))
	tree[i]+=y;
	return ;
}

inline int get_tot(int x)
{
	int ans=0;
	for(fint i=x;i;i-=lowbit(i))
	ans+=tree[i];
	return ans;
}

inline void begin_todo()
{
	int now=n+1;
	do
	{
		if(a[n]>now)
	    cout<<n<<endl,flag=1;
	    if(flag)
	    for(fint i=1;i<=n;i++)
	    cout<<n-i+get_tot(a[i])<<" ",adds(a[i],1);
	    adds(a[n],1),now=a[n];
	}
	while(n--&&!flag);
	return ;
}
```
祝大家ac愉快

---

## 作者：henry_y (赞：1)

想出来一个结论的话就可以挺顺理成章地把后面想出来了。

**每头牛最多被移动一次**。

其实也挺显然的，因为每次只能移动队头。

考虑什么牛不会被移动，其实就是最后面那段递增序列不用移动。从后往前数第一个不
递增的数，1~它全都得移动（因为要把前面的移动了才能移动它）。

而又由上面那个结论可以知道，我们可以在移动的过程中顺便维护出它应该在的位置。
这个可以用bit解决。

首先对于每个$j(1\leq i \leq x)$（x为从后往前数第一个不递增的数），它至少要往后$x-i$头牛（这样才能把x扔到前面），然后考虑把它插入到后面那个递增序列的合适位置，即比它小的数有多少个（这个东西用bit可以很方便的维护）。

那这样的效率就是$O(nlogn)$的了。

~~安利自己的[$blog$](https://www.cnblogs.com/henry-1202/)~~

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 100010
int c[N], a[N], n, tot, ans[N];

#define lowbit(i) (i&(-i))
void add(int x, int v) {
    for(int i = x; i <= n; i += lowbit(i)) c[i] += v;
}
int query(int x) { int ans = 0;
    for(int i = x; i; i -= lowbit(i)) ans += c[i];
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int now = n + 1;
    for(int i = n; i; --i) {
        if(a[i] > now) {
            printf("%d\n", i);
            for(int j = 1; j <= i; ++j) {
                printf("%d ", i - j + query(a[j]));
                add(a[j], 1);
            }
            puts("");
            break;
        }
        add(a[i], 1); now = a[i];
    }
}
```

---

## 作者：chen_qian (赞：1)

T1 [Cow Poetry](https://www.luogu.com.cn/problem/P5196)

首先是完全背包求方案数的问题，记$f[i][j]$表示长为$i$的诗句韵脚为$j$的方案总数，由于当前单词的韵脚只决定最后一个单词。所以实际上它可以从任意韵脚的方案转移过来（及没有任何限制)所以我们以$dp[i]$表示长为$i$的诗句的总方案数。

再之后，我们对于每一种韵脚的诗句，记有$t[i]$个这样的诗句，他们所有的都有$s[i]=\sum_{j=1}^{n}{f[k][j]^{t[i]}}$,最后$ans=\prod_{i=1}^{26}s[i]$
```
#include<bits/stdc++.h>
#define N 5005
#define mod 1000000007
#define ll long long
using namespace std;
int n,k,m;
int a[N],b[N];
int f[N][N],dp[N];
int t[N*10];
ll ksm(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1) ans=(ans*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return ans;
}
int main(){
	freopen("poetry.in","r",stdin);
	freopen("poetry.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=m;i++){
		char c;
		cin>>c;
		t[c-'A'+1]++;
	}
	dp[0]=1;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			if(i>=a[j]){
				f[i][b[j]]=(f[i][b[j]]+dp[i-a[j]])%mod;
				dp[i]=(dp[i]+dp[i-a[j]])%mod;
			}
		}
	}
	ll ans=1;
	for(int i=1;i<=26;i++){
		if(!t[i]) continue;
		ll res=0;
		for(int j=1;j<=n;j++)
			if(f[k][j]) res=(res+ksm(f[k][j],t[i]))%mod;
		ans=(ans*res)%mod;
	}
	cout<<ans;
	return 0;
}
```

T2 [Sleepy Cow Sorting](https://www.luogu.com.cn/problem/P5200)

不难发现只有最后的递增后缀是不用进行操作，所以直接找出，那么第一问就迎刃而解，那么后面的递增后缀其实就已经是排好序的了，第二问其实就是在问把一个数插入到一个已经有序的数列中，问其应该放在放在第几个位置，就是再平衡树中的 rank，但在这里使用平衡树未免有点大题小作了。

那就用值域树状数组来代替吧！（树状数组其实可以离线实现平衡树）

```
#include<bits/stdc++.h>
#define N 100010
#define lb(x) x&-x
using namespace std;
int n,a[N],c[N],ans[N];
void add(int x,int v){
	for(;x<=N;x+=lb(x)) c[x]+=v;
}
int ask(int x){
	int ans=0;
	for(;x;x-=lb(x)) ans+=c[x];
	return ans;
}
int main(){
	freopen("sleepy.in","r",stdin);
	freopen("sleepy.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int l=0;
	for(int i=n;i>1;i--){
		if(a[i-1]>a[i]) break;
		l++;
		add(a[i],1);
	}
	add(a[n-l],1);l++;
	cout<<n-l<<endl;
	for(int i=1;i<=n-l;i++){
		add(a[i],1);
		ans[i]=n-l-i+ask(a[i]-1);
	}
	for(int i=1;i<=n-l;i++) printf("%d ",ans[i]);
	return 0;
}
```
T3 [Shortcut](https://www.luogu.com.cn/problem/P5201)

新知get！！！

最短路树

对于一个图，我们以某个源点来进行最短路算法，假如说每一条最短路都是唯一，那么将不在最短路上的边删掉，剩下的图是一个树。

证明先鸽了。。。

那么这道题我们就只用那么对于这道题，由于牛只会走字典序最小的路径，所以相当于最短路唯一，我们就可以把最短路树给建出来。那么如果当前的节点$x$向源点添了一条边，只会影响$x$及其子树上的节点的最短路，且影响程度都为$(dis[x]-t)*size[x]$。（$size[x]$表示在最短路树上的以$x$为根的子树上的点权和

```
#include<bits/stdc++.h>
#define N 10005
#define M 50005 
#define ll long long
using namespace std;
int n,m,t,head[N],idx;
struct edge{
	int v,next;
}e[2*N];
void add(int u,int v){
	e[++idx].v=v;
	e[idx].next=head[u];
	head[u]=idx;
}
vector<pair<int,int> > v[N];
ll dis[N];
bool vis[N];
void dijkstra(){
	for(int i=1;i<=n;i++) dis[i]=1ll<<62;
	memset(vis,0,sizeof(vis));
	priority_queue<pair<ll,int> > q;
	dis[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=0;i<v[x].size();i++){
			int y=v[x][i].first,w=v[x][i].second;
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				q.push(make_pair(-dis[y],y));
			}
		}
	}
}
ll size[N],c[N];
ll ans=0;
void dfs(int x,int fa){
	size[x]=c[x];
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].v;
		if(y==fa) continue;
		dfs(y,x);
		size[x]+=size[y];
	}
	ans=max(ans,(ll)(dis[x]-t)*size[x]);
}
int main(){
	freopen("shortcut.in","r",stdin);
	freopen("shortcut.out","w",stdout);
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		v[x].push_back(make_pair(y,z));
		v[y].push_back(make_pair(x,z));
	}
	for(int i=1;i<=n;i++) sort(v[i].begin(),v[i].end());
	dijkstra();
	for(int x=1;x<=n;x++){
		for(int i=0;i<v[x].size();i++){
			int y=v[x][i].first,w=v[x][i].second;
			if(dis[y]+w==dis[x]){
				add(x,y);
				add(y,x);
				break;
			}
		}
	}
	dfs(1,0);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：白鲟 (赞：0)

## 前言
~~纪念考试拿了一次满分。~~

## 题意简述
每次操作可将序列首后移任意步，求使得序列升序排列的最小操作次数。

## 题目分析
通过观察可以找到贪心策略：找到从左往右最后一个递减的位置（称作目标位置），并将其及之前的数插入之后的序列。

正确性易得：
- 必要性：目标位置之前的数移动不会使得该位置的逆序被调整，因此操作至少进行到目标位置；
- 充分性：目标位置之后的序列一开始为升序；由于后移步数任意，总可以找到一种移动方式，使目标位置之前的数插入其后的升序序列后保持升序。

之后给出可行方案：在操作进行到某个位置的时候，应当将其向后移至目标位置，然后再移动至它在升序序列中的应处位置。前一步容易计算；后一步可以用树状数组维护升序序列中比当前数小的数的数目。

时间复杂度为 $O(n\log n)$。

## 代码
```cpp
#include<cstdio>
using namespace std;
const int maxn=1e5;
int n,pos,c[maxn+1],BIT[maxn+1];
inline int lowbit(int x)
{
	return x&(-x);
}
void add(int x)
{
	for(int i=x;i<=n;i+=lowbit(i))
		++BIT[i];
	return;
}
int sum(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=BIT[i];
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&c[i]);
	c[0]=n+1;
	for(int i=n;i;--i)
		if(c[i]<c[i-1])
		{
			pos=i;
			break;
		}
	printf("%d\n",pos-1);
	for(int i=pos;i<=n;++i)
		add(c[i]);
	for(int i=1;i<pos;++i)
	{
		printf("%d ",pos-i+sum(c[i])-1);
		add(c[i]);
	}
	return 0;
}
```

---

