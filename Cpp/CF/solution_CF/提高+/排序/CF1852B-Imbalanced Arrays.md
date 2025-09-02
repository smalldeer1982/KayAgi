# Imbalanced Arrays

## 题目描述

Ntarsis has come up with an array $ a $ of $ n $ non-negative integers.

Call an array $ b $ of $ n $ integers imbalanced if it satisfies the following:

- $ -n\le b_i\le n $ , $ b_i \ne 0 $ ,
- there are no two indices $ (i, j) $ ( $ 1 \le i, j \le n $ ) such that $ b_i + b_j = 0 $ ,
- for each $ 1 \leq i \leq n $ , there are exactly $ a_i $ indices $ j $ ( $ 1 \le j \le n $ ) such that $ b_i+b_j>0 $ , where $ i $ and $ j $ are not necessarily distinct.

Given the array $ a $ , Ntarsis wants you to construct some imbalanced array. Help him solve this task, or determine it is impossible.

## 说明/提示

For the first test case, $ b = [1] $ is an imbalanced array. This is because for $ i = 1 $ , there is exactly one $ j $ ( $ j = 1 $ ) where $ b_1 + b_j > 0 $ .

For the second test case, it can be shown that there exists no imbalanced array.

For the third test case, $ a = [0, 1, 0] $ . The array $ b = [-3, 1, -2] $ is an imbalanced array.

- For $ i = 1 $ and $ i = 3 $ , there exists no index $ j $ such that $ b_i + b_j > 0 $ .
- For $ i = 2 $ , there is only one index $ j = 2 $ such that $ b_i + b_j > 0 $ ( $ b_2 + b_2 = 1 + 1 = 2 $ ).

 Another possible output for the third test case could be $ b = [-2, 1, -3] $ .

## 样例 #1

### 输入

```
5
1
1
4
1 4 3 4
3
0 1 0
4
4 3 2 1
3
1 3 1```

### 输出

```
YES
1 
NO
YES
-3 1 -2 
YES
4 2 -1 -3 
YES
-1 3 -1```

# 题解

## 作者：dark_moon (赞：14)

# 分析
针对题目，可以先从较简单的情况入手，**这对接下来的解题有重要的作用**。

1. 如果在序列中有一个 $0$，那么这个 $0$ 的 $b$ 无疑就是 $-n$ 的值，因为不能有任何一个数的 $b$ 与之相加后大于 $0$。
2. 如果序列中存在一个 $n$，那么这个 $n$ 的 $b$ 无疑就是 $n$ 的值，因为任何一个数的 $b$ 与之相加后都大于 $0$。（**注**：由于不能有两个 $b$ 相加为 $0$，所以没有讨论还有一个 $b$ 为 $-n$ 的情况，但在接下来的分析中可以看到是不必要讨论那种情况的）
3. 如果在序列中同时存在 $0$ 和 $n$，则无解。这里可以感性理解，实际上，它也使得第 $1$ 条、第 $2$ 条和不能有两个 $b$ 相加为 $0$ 这三条信息冲突，故无解。
4. 如果在序列中既没有 $0$，又没有 $n$，则无解。这段证明较复杂，我们单独开一个小标题证明。
#### 证明：

我们考虑满足序列中 $a$ 最大的数，如果可以满足，则另说，否则这个序列一定无解。针对证明，我们假设第 $4$ 条的内容为条件，进行反证法的证明。

首先这个数的 $b$ 一定大于等于其他数的 $b$，因为 $b$ 与 $a$ 的值是直接挂钩的。

那么可以得知，这个数的 $b$ 一定不是负数，因为如果它为负数，则所有的 $b$ 都为负数，**则所有的 $a$ 都应该为 $0$，与条件冲突。**

再来考虑这个数的 $b$ 为正数。既然这个数的 $a$ 不为 $n$，那么就假设有至少一个 $b$ 是负数并且绝对值大于这个数的 $b$（下文称其为最小 $b$），但由于这个数的 $b$ 大于等于另外的所有 $b$，那么所有的 $b$ 与最小 $b$ 相加后都小于 $0$，**则最小 $b$ 对应的 $a$ 就应该为 $0$，与条件冲突。**

------------
至此，我们已经将所有最简单的情况考虑完了（后文称为极端情况，即对应第 $1$、$2$ 条），包括如何赋值和判断无解，但我们必须迈出重要的一步，进一步赋值完整个 $b$ 序列。

这里需要用到递归的 **（仅）** 思想：对于一个序列，其要么无解，要么一定有极端情况可以用来让我们赋值。当成功赋值后，要么对整个序列都有相同的影响，要么对整个序列毫无影响：

1. 成功赋值一个 $n$ 后，每个数都可以与其相加得到一对 $b_i+b_j>0$ 的 $(i,j)$，那么我们将这个 $n$ 对应的 $a$ 从序列中剥去，再将所有的剩下的 $a$ 都减去 $1$，剩下的 $n-1$ 个被减去 $1$ 的 $a$ 又可以组成一个新的序列，并且恰好 $n$ 被用去了，剩下的 $1$ 到 $n-1$ 及其负数都可以继续赋值。
2. 成功赋值一个 $-n$ 后，同理，只不过每个数与其相加都得不到一对 $b_i+b_j>0$ 的 $(i,j)$，那么直接将这个 $-n$ 对应的 $a$ 从序列中剥去即可。

现在为止，我们已经完全胜利，只需要对极端情况赋值，再生成一个新的序列，对其进行重复的操作即可。（由于是线性的，所以不需要递归，但是用到了递归的思想）

# 实现
实现也是一重难关。

我们发现，两个极端情况分别对应序列 $a$ 中的最小值和最大值，如果这两者不满足极端情况，则整个序列中都没有极端情况。并且，当我们剥去一个数后，整个 $a$ 序列的单调性是不会改变的。

显而易见的，我们先将 $a$ 序列排序，并且使用左右两个指针，不断判断左右两边的极端情况，并且使用一个变量记录被剥去了几个 $n$，即每个 $a$ 需要被减去几。

# 代码
代码较简单，细节也比较少，本题难点在于思考策略和证明策略。代码仅供参考：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
auto read = [&](){
	int x;
	scanf("%lld", &x);
	return x;
};
int t = read();
struct Node{
	int a, b, id;
};
bool cmp(Node a, Node b){
	return a.a < b.a;
}
signed main(){
	while(t --){
		int n = read();
		Node s[n + 5];
		int ans[n + 5];
		for(int i = 1; i <= n; i ++)
		s[i].a = read(), s[i].id = i;
		sort(s + 1, s + 1 + n, cmp);
		auto work = [&](){
			int l = 1, r = n;
			int now = n, add = 0;
			for(int i = n; i >= 1; i --){
				if(s[l].a + add == 0 && now - (s[r].a + add) == 0)
				return 0;
				if(s[l].a + add == 0){
					s[l].b = -i;
					now --;
					l ++;
				}
				else if(now - (s[r].a + add) == 0){
					s[r].b = i;
					now --;
					add --;
					r --;
				}
				else
				return 0;
			}
			for(int i = 1; i <= n; i ++)
			ans[s[i].id] = s[i].b;
			return 1;
		};
		if(work() == 1){
			printf("YES\n");
			for(int i = 1; i <= n; i ++)
			printf("%lld ", ans[i]);
			printf("\n");
		}
		else
		printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Zooping (赞：5)

### 分析
首先观察 $A$ 中的正数，和大于零可以有两种方式，一种为两个正数相加，另一种为绝对值较小的负数和正数相加。定义最小的负数为 $minn$，最大的正数为 $maxn$。

我们对 $B$ 讨论：

1. 如果 $B$ 中全是正数，那么 $A$ 中必定全为 $n$。
2. 如果 $B$ 中存在负数，那么将 $maxn$ 和 $minn$ 比较，如果 $minn$ 和任意数相加都小于 $0$，$A$ 中存在 $0$，且由 $minn$ 产生。如果 $maxn$ 和 $minn$ 相加大于 $0$，那么这个 $maxn$ 必然和其他数相加都大于 $0$，$A$ 中必然存在一个 $n$ 且由这个 $maxn$ 产生。

由此可以证明 **$A$ 中一定存在一个或多个 $0$ 或 $n$，但不可能同时存在。**

### 思路
我们确定了绝对值最大的数后不妨将这个数从 $A$ 中删去，继续求剩下的 $A$ 中绝对值最大的数，直至 $A$ 空。

### 实现
首先将 $A$ 排序便于找出最大与最小值，使用双指针分别从头尾开始，判断 $0$ 与 $n$ 的数量。特殊的，只有 $n$ 时，我们会考虑将 $A$ 中剩余数都减一，但肯定会超时，于是我们类比差分的思想，做标记来避免大量的修改。

### Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct numbers
{
	int num;
	int wei;
} a[100009];
int b[100009];
bool cmp(numbers x,numbers y)
{
	return x.num<y.num;
}
void s()
{
	int n;
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>a[i].num;
		a[i].wei=i;
	}
	sort(a+1,a+1+n,cmp);
	int cnt=n;
	int jian=0;
	int l=1;
	int r=n;
	while(cnt)
	{
		if((a[l].num+jian)!=0&&(a[r].num+jian)!=cnt)//0和n同时出现
		{
			cout<<"NO"<<endl;
			return;
		}
		if((a[l].num+jian)==0&&(a[r].num+jian)==cnt)//没有0和n
		{
			cout<<"NO"<<endl;
			return;
		}
		if(a[l].num+jian==0)//只存在0
		{
			b[a[l].wei]=-cnt;
			cnt--;
			l++;
		}
		else if(a[r].num+jian==cnt)//只存在n
		{
			b[a[r].wei]=cnt;
			cnt--;
			r--;
			jian--;
		}
	}
	cout<<"YES"<<endl;
	for(int i=1; i<=n; i++)cout<<b[i]<<" ";
	cout<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
		s();
}

```

---

## 作者：xs_siqi (赞：4)

一个类拓扑排序的方法。

我们不妨把 $b_i$ 看成点 $i$ 的度数。把构造看成各个点之间连边（当然自己也可能给自己连边，也就是自环）。

可能这样讲有点抽象，我们把样例的一部分截取出来解释：

```
4
1 2 3 4
```
对于这组样例，我们转化为这样一张图：

```
      ---- ----
      |  | |  |
1  2---3---4---
|  |   |   |
-----------

```

（$4$ 号点和所有点连边，$3$ 号点和 $2,3,4$ 连边，$2$ 号和 $3,4$ 连边，$1$ 号和 $4$ 连边）。

于是我们把它转为了图上连边方案问题。对于边的连接情况，很多东西我们都无法确定。但是这样两个东西我们是百分百能确定的：

- 度为 $n$ 的情况。显然这个点要给包括自己在内的所有点连一条边。

- 度为 $0$ 的情况。显然这个点跟所有点都不连边。

那么，我们优先处理度为 $n$ 的情况。将它跟所有点都连一条边。因为连边，所以自己的度数肯定要清零，而其他点都跟它连了边，所以度数都减一。

然后我们再查查有没有度数为 $0$ 的。如果度数为 $0$ 那么我们显然把它直接删掉就行了。

进一步地，我们发现对于没有必要限制在“度数为 $n$”之上。当度数等于当前节点数的时候，就应该跟所有点（包括自己）连一条边。

那么我们循环做下去就行了。当然还可能出现不合法情况，比如说，如果有节点的度数为负数必然不合法。因为它自己不能连边，但是还被强迫连边了。但是度数为总结点数的节点又必须和所有节点连边，矛盾了，说明不可行。

也就是说，对于开始时，我们从度数恰好为总结点数的节点开始删点处理，或者对于度数恰好为 $0$ 的开始删就行。如果同时存在呢？同时存在就矛盾了。同时存在就会出现度数为负数的情况，这种情况上文已经证明不合法了。

---

那么我们还剩下最后一件事情。对于开始时不存在度数为 $0$ 或者总结点数的节点，怎么办？

我们发现这种情况是无解的。证明如下。

对这种情况进行分类讨论。记最大度数点为 $x$。

当这个节点无自环，但是它连的其他点都有是有自环的（可以证明要是两个点想连边，必须有一个节点存在自环），那么从它连的任意一个点的最大度数点至少为 $x+1$。因为这个点能连到的点都存在自环。而随便从它连的点抽一个出来都有自环。边是无向边，所以随便抽出来的一个点可以连 $x$ 个有自环的点和至少一个没有自环的点，度数至少为 $x+1$。那么最大度数不为 $x$，矛盾。

当这个节点有自环，它连的其他点可以有自环可以无自环的情况，存在以下两种分类：

当整张图只存在单个自环的情况。由于 $x\neq n$，所以必然有一个节点取不到，那么这个节点的值就必须取区间 $[1,n)$。

那么对于至少一个取不到的点，它的取值的绝对值就应该比这个范围更大。但是不存在度数为 $0$ 的点，如果最小的点不能跟最大的连通图连边，则必然不能连边，不符合不存在度数为 $0$ 的点的情况，矛盾。

将这个情况推广到多个自环的情况下，我们发现对于任意一个自环节点 $a$，一个不连该自环的节点 $b$，显然有 $\max\{a\}>\min\{|b|\}$。连最小的点都没办法连到最大的联通图上，那么这个最小的点就无法跟任何东西连边。

有人会说这个点可以跟其它无自环的点连边。但是请注意，两个点都没有自环，无法连边。

综上证明了，当没有度数为最大点数，也没有度数为 $0$ 的情况下，是无解的。

---

接下来我们来讲这件事情要如何维护实现。我们将所有度数插入到一个 `multiset` 里动态维护最大值最小值。为什么采用这个？因为这件事是不可以去重的。如何减小整个区间 $1$ 的值？我们发现，把整个区间都减 $1$，就相当于把整个区间的判断值加 $1$。什么叫判断值？比如说，你要判断一个序列的数是否大于 $0$，区间减 $1$ 相当于讲问题转化为判断一个序列的数是否大于 $1$。这样我们维护一个左端点 $l$ 和右端点 $r$ 动态维护记录序列中节点数即可。

参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int t,n,tong[maxn],ans[maxn];
struct edge{int id,x;}a[maxn];
bool f;
bool cmp(edge x,edge y){return x.x<y.x;}
multiset<int> s;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i].x),a[i].id=i,
			s.insert(a[i].x);
		sort(a+1,a+n+1,cmp);
		int nown=n,lvl=0,k=n,l=0,r=n+1;
		while(s.size()){
			int top=*s.begin(),ed=*(--s.end());
			auto it=s.begin(),it2=--s.end();
			if(ed==nown&&top==0){
				printf("NO\n"),f=1;
				break;}
			else if(ed==nown)
				lvl++,s.erase(it2),ans[a[--r].id]=(k--);
			else if(top==lvl)
				s.erase(it),nown--,ans[a[++l].id]=-1*(k--);
			else{
				printf("NO\n"),f=1;
				break;}}
		if(!f){
			printf("YES\n");
			for(int i=1;i<=n;i++)printf("%d ",ans[i]);
			printf("\n");}
		while(s.size())s.erase(*s.begin());
		f=0;}
	return 0;}
```




---

## 作者：Mashu77 (赞：1)

我们假设当前出长度为 $len$，那么我们在序列中一定有一个 $len/0$，因为一定有一个绝对值最大的数，如果这个数是正数在原序列中就是 $len$，是负数在原序列中即为 $0$。

由上文，我们可以得到，一定不能有 $len$
 和 $0$
 同时出现的情况，也一定不能有 $len$
 和 $now$
 都不能出现的情况。

通过这个性质，我们就可以得到下面的解法：

- 如果序列中有一个值为 $len$
 的数，那么它一定和所有数的和都为正数，我们可以直接将它去掉，然后其它数 $-1$，这样我们就可以得到一个长度为 $len-1$
 的序列。
- 如果序列中有一个值为 $0$
 的数，那么它一定和所有数的和都为负数，我们可以直接将它去掉，这样我们也可以得到一个长度为 $len-1$
 的序列。
- 而若序列中既没有 $len$
 也没有 $0$，或 $len$
 和 $0$
 都有，那么一定是无解的。
 
通过这种方法我们就可以判断能否构造出一种解。

而构造解的方法也很简单：

- 数值：让删的数的绝对值，从大到小即可。
- 符号：如果删的是 $len$，则为正数；如果删的是 $0$，则为负数。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 1e5 + 8;
typedef long long ll;
struct Num{
	int val,pos;
	bool operator < (const Num &x){
		return val > x.val;
	}
}a[NN];
int T,n,hf;
int ans[NN];
ll pre[NN];
bool check(){
	int head = 1, tail = n;
	int cnt = 0;
	for(int i = 1; i <= n; ++i){
		if(a[tail].val == cnt && (n-i+1) - a[head].val + cnt == 0) return false;
		if(a[tail].val == cnt) {
			ans[a[tail].pos] = - (n-i+1);
			--tail;
		}
		else if((n-i+1) - a[head].val + cnt == 0){
			ans[a[head].pos] = (n-i+1);
			++head,++cnt;
		}
		else return false;
	}
	return true;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i = 1; i <= n; ++i) scanf("%d",&a[i].val),a[i].pos = i;
		sort(a+1,a+1+n);
		hf = -1;
		for(int i = 1; i <= n; ++i) pre[i] = pre[i-1] + a[i].val;
		if(!check()){puts("NO");continue;}
		puts("YES");
		for(int i = 1; i <= n; ++i) printf("%d ",ans[i]);
		puts("");
	}
}

---

## 作者：subcrip (赞：1)

如果我的理解没错，这题应该是 $O(n)$ 就可以解决的。 **我们先假设 $a$ 数组是排好序的。** 

首先观察到没有必要让两个 $b_i$ 相等。为什么呢？

> 观察1：如果存在一组解里有两个数相等 $b_i=b_j$，那么我们让 $b_j:=b_i+1$ 或者 $b_j:=b_i+2$，这仍然有一种是一组合法解。
>
> 证：我们来证明新的解合法。
>
> 对于 $k\not\in\{i,j\}$，假如 $b_k+b_i>0$，那么 $b_k+b_j\geqslant b_k+b_i+1>0$；假如 $b_k+b_i<0$，那么先尝试$b_j:=b_i+1$，则 $b_k+b_j=b_k+b_i+1\leqslant0$，如果等号取到我们再换成 $b_j:=b_i+2$即可。
>
> 对于 $k\in\{i,j\}$，类似可证。

我们发现题目规定 $|b_i|\leqslant n$，又不能 $b_i+b_j=0$，所以根据观察1，我们就可以从$(-1,+1),\cdots,(-n,+n)$ 这每一对中选一个出来，尝试由它们组成合法解就行。那么怎么选呢？

> 观察2：如果 $b_i>0$，则有 $a_i=posCount_{i+1}+i$；如果 $b_i<0$，则有 $a_i=posCount_{i+1}$。其中 $posCount_k$ 表示 $b_k,\cdots b_n$中正数的个数。
>
> 证：略。
>
> 观察3：如果 $b_j>0$，那么对 $i<j$ 有 $a_i<a_j$。
>
> 证：因为 $a_i\leqslant posCount_{i+1}+i\leqslant( posCount_{j+1}+j-i)+i=posCount_{j+1}+j=a_j$。

所以我们从 $n$ 遍历到 $1$，每次考虑 $b_i$ 应该等于 $i$ 还是 $-i$。如果 $posCount_{i+1}+i$ 在输入的 $a$ 数组中存在，那么我们就应该取 $b_i=i$，因为由观察3，更小的 $i$ 更难取到这个 $a_i$。否则就取 $b_i=-i$。

最开始说假设 $a$ 有序。但是真的需要有序吗？不用，因为如果无序，我们无非就是不知道我们算出的 $b_i$ 实际上应该对应于 $b_?$。新建一个数组 $slot$ 用来存放 $a_i$ 到 $i$ 的逆映射关系就行了。

# 代码

```cpp
// some useful macros here ...


void solve() {
    read(int, n);
    vector<vector<int>> slot(n + 1);
    for (int i = 0; i < n; ++i) {
        read(int, t);
        slot[t].push_back(i);
    }
    int pos = 0;
    vector<int> res(n);
    for (int i = n; i > 0; --i) {
        if (slot[pos + i].size()) {
            res[slot[pos + i].back()] = +i;
            slot[pos + i].pop_back();
            pos += 1;
        } else if (slot[pos].size()) {
            res[slot[pos].back()] = -i;
            slot[pos].pop_back();
        } else {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    putvec(res);
}

int main() {
    read(int, t);
    while (t--) solve();
}
```

---

## 作者：phil071128 (赞：0)

有趣的构造题，顿悟一下就很好做了，仅有 *1800 不知道为什么洛谷评蓝。

首先可以注意到，构造出的序列一定是排列。否则可以调整为排列而不影响答案。

因此结合题目两个要求，问题变为每个 $i=1\cdots n$，选择其为正数或者负数。

如果我们倒着做，无论当前位置选正还是选负，那么我们可以很轻松得到已经确定的偏序集合大小。如果正着做，那相当将题面中大于号改成小于号，也是可以做的。

具体的，倒序枚举并维护 $x,y$ 表示在 $i+1\sim n$ 选择的正数和负数数量，如果存在一个 $a_i=x+i$ 则构造一个 $+i$，否则如果存在一个 $a_i=n-i-y$ 则构造一个 $-i$，如果都不存在则无解。

```cpp
const int N=5e5+500;
int a[N],t[N],b[N];
pii c[N];
void work() {
	int n=read();
	for(int i=0;i<=n;i++) t[i]=0;
	for(int i=1;i<=n;i++) a[i]=read(),t[a[i]]++;
	int x=0,y=0;
	for(int i=n;i>=1;i--) {
		if((t[x+i]+t[n-i-y])==0) {
			puts("NO");return ;
		}
		if(t[x+i]) {
			t[x+i]--;
			b[i]=1;x++;
		}else{
			t[n-i-y]--;
			b[i]=-1;y++;
		}
	}
	puts("YES");
	for(int i=1;i<=n;i++) c[i]=pii(a[i],i);
	for(int i=1;i<=n;i++) b[i]*=i;
	sort(b+1,b+1+n);
	sort(c+1,c+1+n);
	for(int i=1;i<=n;i++) {
		a[c[i].se]=b[i];
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	cout<<endl;
}
signed main(){
//	fil();
	int T=read();while(T--) work();	
	return 0;
}
```

---

## 作者：kimi0705 (赞：0)

## part 0 题意

对于一个给定的长度为 $n$ 的数组 $A$，定义一个长度为 $n$ 的数组 $B$ 是不平衡的当且仅当以下全部条件满足：

1. $-n \leq B_{i} \leq n$ 且 $B_{i} \ne 0$。即每个数在 $[-n,n]$ 内且不为 $0$。

2. $\forall i,j \in [1,n], B_{i} + B_{j} \neq 0$。即数组内不存在一对相反数。

3. $\forall i \in [1,n], \sum_{j = 1}^{n} [ \left (B_{i} + B_{j} \right) > 0] = A_{i}$。即对于任意的 $i$，数组中与 $B_{i}$ 和大于 $0$ 的数的个数恰好为 $A_{i}$。**注意：这里需要计算本身。也即 $i$ 与 $j$ 可以相等。**

请构造长度为 $n$ 的不平衡序列。

## part 1 题解

考虑一下性质。
1. 对于每一个 $i$ 肯定存在且仅存在一个 $i$ 或 $-i$，由条件 1.2 可证。
2. 当 $A$ 中存在 $n$ 时，其 $B$ 值肯定为 $n$。
3. 当 $A$ 中存在 $0$ 时，其 $B$ 值肯定为 $-n$。
4. 当 $A$ 中存在 $n$ 和 $0$ 时无解，由以上三点即可证明。
5. 当 $A$ 中不存在存在 $n$ 和 $0$ 时无解，由 1.2.3 即可证明。

考虑递归，把每一个 $A$ 为 $0$ 或 $n$ 的删掉，并将每一个 $A_i$ 减一，即可转化为大小为 $n-2$ 的子问题，具体实现请读者自己尝试。

---

## 作者：hfjh (赞：0)

# CF1852B Imbalanced Arrays 题解
考虑因为没有相反数，所以最后的数取绝对值之后是一个排列。

我们对 $a$ 倒序排序，然后很显然大的是正数，小的是负数。

所以排序后大的在左边，小的在右边，我们需要找到这个正负的分界线。

那么界限需要满足 $\sum_{i = 1} ^ wa_i - w^2 = \sum_{i = w + 1}^na_i$。

因为每个正数和每个正数之间会做出 1 贡献，那么界限是 $w$ 代表有 $w$ 个正数，总贡献是 $w^2$。

剩余的贡献就是正数和负数加起来最后 $>0$，正数这边的贡献要和负数这边的贡献相等才可以。

我们把界限左边部分，也就是正数的贡献 $a_i = a_i- w$ 只考虑正数和负数的贡献。

我们把界限右边部分，也就是负数的贡献变为 $a_i+a_j < 0$ 的贡献，那么也就是 $a_i = n - a_i$。

现在负数之间也可以相互贡献，共有 $n - w$ 个负数，每个负数和所有负数都可以相互贡献，也减去相互的贡献，只剩正数和负数相加 $<0$ 的贡献。

现在负数的 $a_i$ 就是 $a_i = n - a_i - (n - w) = w - a_i$。

假设样例是 $a = {4,3,2,1}$ 界限 $w = 2$ ，变换后的 $a$ 就是 $a = 2,1,0,1$。

$$
\begin{aligned}
&\downarrow~~~~~~~~~\downarrow\\
&~2,1|0,1
\end{aligned}
$$

现在两个指正 $l,r$ 指向 $2,1$。

$2$ 代表第一个数负数中有两个和他相加 $>0$，当 $r - w = a_l$ 时这个数一定和所有正数相加都 $>0$，移动左指针，填 $4$。

当填完之后指针移动：

$$
\begin{aligned}
&~~~~\downarrow~~~~\downarrow\\
&~2,1|0,1
\end{aligned}
$$

左边的 $1$ 代表负数中有一个和他相加 $>0$，右边的 $1$ 代表正数中有一个和他相加 $<0$。

当 $w - l + 1 = a_r$ 时这个数一定和所有正数相加都 $<0$，移动右指针，填 $-3$。

这样一步一步推下去就可以了。
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 1e5 + 10;
int t, n, pr[N], w, l, r;
int ans[N];
ll sum, now;
struct node{
	int a, id; 
}p[N];
bool cmp(node a, node b){
	return a.a > b.a;
}
void input(){
	cin>> n;
	for(int i = 1; i <= n; ++i){
		cin>> p[i].a;
		p[i].id = i;
		sum += p[i].a;
	}
	sort(p + 1, p + 1 + n, cmp);
}
bool op(){
	for(int i = 0; i <= n; ++i){
		now += p[i].a;
		if(now - 1ll * i * i == sum - now){w = i;break;}
		if(i == n) return 0;
	}
	for(int i = 1; i <= n; ++i){
		if(i <= w) p[i].a = p[i].a - w;
		else p[i].a = n - p[i].a - (n - w);
	}
	l = 1, r = n;
	for(int i = n; i >= 1; --i){
		if(r == w){
			if(p[l].a == r - w) ans[p[l++].id] = i;
			else return 0;
		}
		else if(l == w + 1){
			if(p[r].a == w - l + 1) ans[p[r--].id] = -i;
			else return 0;
		}else{
			if(p[l].a == r - w) ans[p[l++].id] = i;
			else if(p[r].a == w - l + 1) ans[p[r--].id] = -i;
			else return 0;
		}
	}
	return 1;
}
int main(){
	cin>>t;	
	while(t--){
		now = sum = 0;
		input();
		if(op()){
			cout<<"YES"<<'\n';
			for(int i = 1; i <= n; ++i) cout<<ans[i]<<' ';
			cout<<'\n';
		}else{
			cout<<"NO"<<'\n';
		}
	}
}
```

---

## 作者：buaa_czx (赞：0)

## 思路

一个很重要的性质是，一个数列中必然存在一个绝对值最大的数，如果它是正的，那么它对应的 $a_i$ 一定是数列的长度，如果它是负的，那么它对应的 $a_i$ 一定是 $0$。

由此，我们每次找数列 $a$ 中等于数列长度的项或值为 $0$ 的项，并确定它们的值，然后更新数列 $a$ 即可。

如果在处理过程中数列 $a$ 不存在等于数列长度的项或值为 $0$ 的项或两种都存在，则无法进行构造。

这个过程可以对 $a$ 排序后用双指针来处理。

## 代码
 ```cpp
int n, b[maxN + 5];
struct node {
    int val, id;
} a[maxN + 5];
void solve() {
    cin >> n;
    rep(i, 1, n) {
        b[i] = 0;
        cin >> a[i].val;
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n, [](node x, node y) { return x.val < y.val; });
    int l = 1, r = n, cnt = 0, curr_n = n;
    while (l < r) {
        bool fl[2] = {(a[l].val - cnt == 0), (a[r].val - cnt == r - l + 1)};
        int l0 = l, r0 = r;
        if (fl[0] ^ fl[1]) {
            if (fl[0]) {
                while (a[l].val - cnt == 0) {
                    b[a[l].id] = -curr_n, l++;
                }
            } else {
                while (a[r].val - cnt == curr_n) {
                    b[a[r].id] = curr_n, r--;
                }
                cnt += r0 - r;
            }
            curr_n = r - l + 1;
        } else {
            cout << "NO\n";
            return;
        }
    }
    if (l == r && !b[a[l].id]) {
        if (a[l].val - cnt == 0) {
            b[a[l].id] = -1;
        } else if (a[l].val - cnt == 1) {
            b[a[l].id] = 1;
        } else {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    rep(i, 1, n) cout << b[i] << " ";
    cout << endl;
}
 ```

---

## 作者：fireinice (赞：0)

# CF1852B Imbalanced Arrays

给一个不需要递归构造的新方法()

> 对于一个给定的长度为 $n$ 的数组 $A$，定义一个长度为 $n$ 的数组 $B$ 是不平衡的当且仅当以下全部条件满足：
> 
> - $-n \leq B_{i} \leq n$ 且 $B_{i} \ne 0$。即每个数在 $[-n,n]$ 内且不为 $0$。
> 
> - $\forall i,j \in [1,n],B_{i} + B_{j} \neq 0$。即数组内不存在一对相反数。
> 
> - $\forall i \in [1,n],\sum_{j = 1}^{n} [\left (B_{i} + B_{j} \right) > 0] = A_{i}$。即对于任意的 $i$，数组中与 $B_{i}$ 和大于 $0$ 的数的个数恰好为 $A_{i}$。**注意： 这里需要计算本身。也即 $i$ 与 $j$ 可以相等。**
> 
> 请构造长度为 $n$ 的不平衡序列。

$b_i$ 要满足 $b_j>-b_i$ 的有恰好 $a_i$ 个，那么显然 $a_i$ 越大，$-b_i$ 就要越小，于是得到结论若 $a_i<a_j$，则 $b_i<b_j$。对于相等的 $a_i$ 显然可以随意钦定顺序。

因为有了 $b$ 的顺序，可以确定每个 $a_i$ 的 $-b_i\in [b_{n-a_i},b_{n-a_i+1}]$，属于同一个区间的 $-b_i$ 又因为已知 $b_i$ 的大小关系而可以确定，于是我们得到了一条包含 $b_i$ 和 $-b_i$ 的大小关系的长 $2n$ 的不等式链，因为一共只有 $2n$ 个数，只要从小到大对应赋值，然后判定是否对应位置为相反数即可。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N = 1e5 + 500;
int n;
struct P {
    int i, v;
} a[N];
bool cmp(P a, P b) {
    return a.v < b.v;
}
bool cmp2(P a, P b) {
    return a.i < b.i;
}
vector<int> bsep[N];
int bs[N * 2];
P b[N];
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].v;
        a[i].i = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        bsep[n - a[i].v].push_back(i);
    }
    int p = 0;
    for (int i = 0; i <= n; i++) {
        if (i > 0)
            bs[++p] = i;
        sort(bsep[i].begin(), bsep[i].end(), greater<int>());
        for (int v : bsep[i]) {
            bs[++p] = -v;
        }
        bsep[i].clear();
    }
    int bcnt = 0;
    for (int i = 1; i <= p; i++) {
        if (bs[i] != -bs[2 * n - i + 1]) {
            cout << "NO" << endl;
            return;
        }
        if (bs[i] > 0)
            b[++bcnt].v = i > n ? i - n : -(n - i + 1);
    }
    for (int i = 1; i <= n; i++)
        b[i].i = a[i].i;
    sort(b + 1, b + 1 + n, cmp2);
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        cout << b[i].v << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---

