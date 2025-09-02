# 声海 | Sea of Voices

## 题目背景

「真是，如梦似幻呢。」

“怎么？”

「我看见你从开始到现在的一切记忆；看见你，从一次次或欢喜或失落中走来。那些场景在我眼前浮现，像梦，却又那么模糊——我只听见那些声音，只感到那片声音的海洋将我环围… 你听得见吗？」

“当然。毕竟，它们是我的记忆啊。”

「或许，一次生命，便是一场发声的历程吧。我们诞生时的啼哭，便在向世界发出宣告降临的声音；在一次次挑战的过程中，我们向一切阻碍我们的事物唱出不屈的战歌；在日常的点滴中，我们向所珍视之人倾诉内心深处的话语… 这样的声音，这样的感情，是不是就是我们所生存世界的本质呢？」

“或许就是这样吧。纵使一路走来，我们看见了无尽的景色，但只有那些与我们内心共鸣的声音——或来自于自然、或来自于他人的灵魂——才会真正地改变我们自己。”

「是啊… 但愿，在这片声音的海洋里，你不会迷失你的方向。我期许着听见更多，关于你的声音。怀揣着这种信念，向前走下去吧。」

“你也一样。”

> We'll see creation come undone
>
> 我们会见证自己存在的印记被世界拂去
>
> These bones that bound us will be gone
>
> 而那些既有的束缚将不再留存
>
> We'll stir our spirits till we're one
>
> 我们会洗涤自己的灵魂直至合为一体
>
> Then soft as shadows we'll become
>
> 然后成为掠影，散失在虚无之中

## 题目描述

“但是… 曾有一些人，在我的生命里留下了重要的声音，我却无法回忆起了…”

「为什么呢？」

“不妨让我们把问题变得形式化一点。我想回忆起的声音有 $n$ 个，它们的共鸣度——非负整数 $a_i$，是单调不降的。最初它们互不干涉，但随着时间的推移，多个相邻的声音会交织在一起形成新的声音——也就是说，对于任意的 $1\le l\le r\le n$，第 $l$ 一直到第 $r$ 个声音会交织在一起形成新的声音，而这个声音的共鸣度便是这些声音共鸣度的总和。”

「也就是说，例如 $n=3$，$a=[1,2,4]$，那么最终 $\dfrac{3\times(3+1)}2=6$ 个声音的共鸣度分别是 $1,2,4,3,6,7$？」

“没错。现在我把最终所有声音的共鸣度无序地告诉你，你能帮我还原最开始 $n$ 个声音的共鸣度吗？”

「乐意之至。」

### 简要题意

$a$ 为长度为 $n$ 的非负整数序列，满足 $\forall 1<i\le n,a_{i-1}\le a_i$。现 **无序** 地给出 **可重集** $S=\left\{\sum_{k=l}^r a_k|1\le l\le r\le n\right\}$，试还原 $a$。

## 说明/提示

对于全部数据，有 $1\le n\le 2000$，$0\le a_i\le 10^5$。

Subtask 1（5 pts）：保证 $n=2$。

Subtask 2（15 pts）：保证 $n=3$。

Subtask 3（30 pts）：保证 $n\le 100$。

Subtask 4（50 pts）：无特殊限制。

## 样例 #1

### 输入

```
3
1 2 3 4 6 7```

### 输出

```
1 2 4```

## 样例 #2

### 输入

```
5
1 3 4 7 8 9 10 11 15 17 18 19 24 27 28```

### 输出

```
1 3 7 8 9```

# 题解

## 作者：Mivik (赞：30)

## Subtask 1

因为元素都是非负的，我们直接输出最小的两个数即可。

## Subtask 2

（真的有人需要吗？）

## Subtask 3

（我想了一下，不是很会）

## Subtask 4

我们考虑，是什么让我们最小的第三个数不一定是原来的第三个数？是 $a_1+a_2$！因此我们拓展一下这个思路，每次推算出 $a_i$ 的值后把 $S_1,S_2,\dots,S_i$（$S_k$ 表示 $a$ 的前 $k$ 项和）从给出的数里面删去（注意重复的数一次只能删一个），于是剩下不相关的数要么就包含 $a_{i+1}$，要么就包含比 $a_{i+1}$ 更大的数，都是大于 $a_{i+1}$ 的。这时我们再取最小值就是 $a_{i+1}$ 的值了。

这个维护可重数集的插入删除最小值直觉是用 multiset，但想想常数过大应该过不去。于是我们把原来的数集先排好序，然后用一个优先队列从小到大维护删除了的数，每次取数集最小值的时候检查一下就好了。时间复杂度是 $O(n^2\log n)$ 的。显然有不带 $\log$ 的做法，不过作为签到题并没有必要为了微小的复杂度差距增大码量。

[ametus.h](https://pastebin.com/U0qK4eJb) / [code](https://pastebin.com/VNYnGpmx)


---

## 作者：TheSky233 (赞：17)

## Description

给出**可重集** $S=\left\{ \sum^r_{k=l}a_k|1\leq l \leq r \leq n \right\}$，求原来的 $\{a\}$。

## Solution

### Subtask 1-2

简单模拟一下即可。

### Subtask 3-4

首先对输入的数组 $S$ 进行排序，容易想到，$S_1$ 和 $S_2$ 必定也是 $a_1$ 和 $a_2$，因为这两个元素显然不可能通过两个比它更小的元素相加得到。接下来考虑 $S_3$。

1. $S_3=a_1+a_2$，此时应当略过 $S_3$，继续向后找 $a_3$。
2. $S_3 \neq a_1+a_2$，此时的 $S_3$ 就是 $a_3$。

拓展开来，对于每一个 $S_i$，假设已经找到了 $k$ 个元素，我们要先判断这个数是否是之前已经确定的 $a$ 数组中某段区间的和，如果是，就跳过。不是就加进 $a$ 数组中。那么，如何判断它是否是某个区间的和呢?

暴力枚举区间的左端点和右端点？复杂度为 $O\left(n^2\right)$，算上外层的一个循环和统计直接变成 $O\left(n^4\right)$，会 TLE。即使加上前缀和优化，也还是 $O\left(n^3\right)$，怎么办？用桶。

我们每当找到一个 $a_i$，就扫一遍 $a$ 数组的后缀和，并把桶内当前后缀和的值减 $1$。这样，我们就做到了 $O\left(n\right)$ 预处理，$O\left(1\right)$ 查询了。


------------

- Q：为什么不用前缀和要用后缀和？
- A：前缀和无法处理后缀的和，但后缀和却可以处理任意一段的和。对于区间和 $\sum^r_{k=l}a_k|1 \leq l \leq k \leq r$，它一定会在扫描到 $a_r$ 的时候做 $r-l+1$ 次后缀和得到。

如果还没有搞懂，来看一组数据：
```cpp
6
1 2 3 5 7 8 9 11 14 16 17 20 20 25 27 28 31 40 45 47 48
```
正确输出是```1 2 5 9 11 20```。

如果做前缀和，则前缀和为```1 3 8 17 28 48```。

最后输出的答案为 ```1 2 5 7 9 11```。

注意到了吗？前缀和把 $7$ 这个漏网之鱼给放过去了。

而后缀和呢？（上面一行为后缀和，下面一行为 $a$ 数组）
```cpp
1 2 3 5 7 8 9 14 16 17......
^ ^   ^     ^
1 2   5     9         ......
```
完美解决。

------------

- Q：为什么要把桶内扫到的值减 $1$ 而不是直接赋值为 $-1$？
- A：为了处理有重复元素的情况。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

inline int calc(int n){
	return n*(n+1)/2;
}

int n,a[2500000],ans[2005],j;
int h[100005],sum;

int main(){
	cin>>n;
	for(int i=1;i<=calc(n);i++) cin>>a[i];
	sort(a+1,a+calc(n)+1);
	for(int i=1;i<=calc(n);i++){
		h[a[i]]++;//当前数出现过，就把它在桶里面的值加一
		if(h[a[i]]>0){//出现的次数大于不该出现的次数
			ans[++j]=a[i];
			if(j==n) break;
			sum=0;
			for(int k=j;k>=1;k--){
				sum+=ans[k];
				if(sum>100000) break;//最大不应该超过限制，而且不加会 RE
				h[sum]--;//这个元素不应该出现，所以减一
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
}
```
时间复杂度 $O\left(n \log n + n^2\right)$，[AC](https://www.luogu.com.cn/record/69238395)。

## Conclusion

看不懂官方题解的过来集合！

敲了一个小时的题解，给个赞吧 qwq。

---

## 作者：Syamoe (赞：7)

题目还是出的很好的吧。

这一道题目我记得在USACO 2020 的 12 月铜牌赛中出现过，只不过算是简化版，只有 3 个数字。

首先要明确，题目中所谓的“共鸣度”，就是几个最初声音的所有垒加的方法

其实，此题可以直接使用队列,

队列最大的好处就是可以直接从队列里把数据删掉。

而这道题目呢，其实就是一到排序的题目，

先以第一组样例为例：

$1$ $2$ $3$ $4$ $6$ $7$

这列数字为3个最初声音开始的，那么，排序之后的结果一定就是几个数字先单个再两两组合最后3个加和吗？显然不是的。

我们可以先把这些排序之后的数字理解为“一组数字”，在这一组数字中，第一项 $a_1$ 一定是一个最小的最初声音，而第二项 $a_2$ 也一定是第2小的最初声音，而最大的一项 $a_n$ 必定是3个最初声音的加和，也就可以推算出来第三个最初声音（最大的）为 $a_n$ $-$ $a_1$ $-$ $a_2$ 的结果。

既然找到规律了，那么多个数字的也就变得不那么难了，队列可以将数据删除，因此，我们直接让已经确定了的3个最初声音从里面出去即可。

这就是本题的思路 qwq


---

## 作者：FFTotoro (赞：5)

一个绿题，暴力居然过了……

~~本来以为要用前缀和的~~

输入一排数据，排序后用一个 vector 存放答案，先放入第一个元素和第二个元素，然后从第三个元素开始枚举，如果是若干个已选择的元素之和则不选，否则压入 vector，然后注意几个特判就可以了。

特判的具体做法见代码。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
int a[10000001],b[2001],c;
vector<int> v; // 存放最终答案
signed main(){
	ios::sync_with_stdio(false);
	int n; cin>>n; int s=n*(n+1)/2;
	for(int i=1;i<=s;i++)cin>>a[i];
	sort(a+1,a+s+1); // 排序
	v.push_back(a[1]); v.push_back(a[2]);
	for(int i=3;i<=s;i++){ // 从前扫到后
		bool flag=false;
		for(int j=2;j<=v.size();j++){ // 枚举区间长度
			for(int k=b[j];k<=v.size()-j;k++){ // 枚举左端点
				for(int l=k;l<k+j;l++)c+=v[l]; // 暴力加和
				if(c==a[i]){b[j]++;  c=0; flag=true; break;} // 说明是多个数的和，跳出循环
				if(c>a[i]){c=0; break;} // 特判优化，如果总和超过了当前枚举的元素，继续枚举下去也没有意义了，和只会越来越大
			}
			if(flag)break;
		}
		if(!flag){
			v.push_back(a[i]);
			if(v.size()==n)break; // 特判，如果个数够了就跳出循环
		}
	}
	for(int i=0;i<v.size();i++)cout<<v[i]<<' ';
	return 0;
}
```

---

## 作者：Ginger_he (赞：3)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/15887615.html)
# 题目描述
$a$ 为长度为 $n$ 的非负整数序列，满足 $\forall 1<i\le n,a_{i-1}\le a_i$。现**无序**地给出**可重**集 $S=\{\sum_{k=l}^ra_k|1\le l\le r\le n\}$，试还原 $a$。
# 题解
先声明一下，$a$ 为给定的序列，$b$ 为还原后的 $a$，$c_{i,j}$ 为 $\sum_{k=i}^jb_k$，$s$ 为 STL 容器 multiset，下述区间的长度均大于 $1$。  
由于给定的数是无序的，所以先对 $a$ 排序。若 $a_i$ 在 $s$ 中出现过，则它为 $b$ 某一段区间的和，将其从 $s$ 中删掉即可；若 $a_i$ 没在 $s$ 中出现过，不妨假设 $b_j=a_i$，我们将所有以 $j$ 结尾的 $b$ 的区间和放入 $s$ 中即可。
## 注意
- 给定的数中可能有重复，所以要用 multiset。
- multiset 的 erase 要删除其指针。
- multiset 的常数很大，卡卡常就行了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
const int maxn=2001005;
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
int n,m,x,a[maxn],b[2005],c[2005],cnt;
multiset<int> s;
multiset<int>::iterator pos;
int main()
{
	n=read();
	m=n*(n+1)/2;
	for(rint i=1;i<=m;i++)
		a[i]=read();
	sort(a+1,a+m+1);
	for(rint i=1;i<=m;i++)
	{
		if(s.count(a[i]))
		{
			pos=s.find(a[i]);
			s.erase(pos);
		}
		else
		{
			b[++cnt]=a[i];
			for(rint j=1;j<cnt;j++)
				s.insert(c[j]+=b[cnt]);
			c[cnt]=b[cnt];
			if(cnt==n)
			    break;//这个优化很重要
		}
	}
	for(rint i=1;i<=n;i++)
		printf("%d ",b[i]);
	return 0;
}
```

---

## 作者：zbk233 (赞：2)

## 解题思路

一道很有意思的题。

因为实际上的输入数据是无序的，所以先要进行排序。

首先，容易看出，最小的两个数一定是最初的声音共鸣度。

我们把这两个数，也就是 $a_1$ 与 $a_2$ 放进队列中。

那么，$a_1$ 与 $a_2$ 的和肯定是它们交织而成的，我们用一个标记数组将 $a_1+a_2$ 标记为已经访问过。

接下来，再将 $a_1+a_2$ 入队，将 $a_1$ 出队。

如果 $a_3$ 不是 $a_1+a_2$，那么就继续遍历 $a_3$。

接着，遍历队列中的所有元素，也就是 $a_2$ 与 $a_1+a_2$，把 $a_2+a_3$ 与 $a_1+a_2+a_3$ 标记为已经访问过了，再依次入队。

最后将 $a_3$ 入队。

事实上，当遍历到 $a_i$ 时，队列里的元素一定是 $a_{i-1},a_{i-1}+a_{i-2},...,a_{i-1}+a_{i-2}+...+a_1$。

也就是说，这些元素加上 $a_i$ 后是 $a_i$ 的每一个后缀和。

知道了每一个 $a_i$ 的每一个后缀和，就能排除所有的非最初的声音共鸣度，最后剩下的就是最初的声音共鸣度了。

但是，还有一个问题，就是标记数组的。

对于标记数组，因为输入会有重复的数，所以不能只记录这个数字是否被标记过，而是要记录这个数字应该出现的次数，当遍历到这个数时，只要让这个数对应的标记数组中的元素减一即可。

而当标记数组中的数小于或等于 $0$ 时，就说明这个数不能选择了。

还有一个问题，就是数据范围。

数据范围中给的是 $a_i$ 的大小，而不是输入数据的大小。

所以我们要进行剪枝，将所有大于 $10^5$ 的数全部跳过。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2001005],vis[100005],n,m;
queue<int> q;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	m=n*(n+1)/2;
	for(int i=1;i<=m;i++) cin>>a[i];
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++){
		if(a[i]>100000) continue;
		vis[a[i]]++;
		if(vis[a[i]]>0){
			int len=q.size();
			for(int j=1;j<=len;j++){
				int tmp=q.front();
				q.pop();
				if(tmp+a[i]>100000) continue;
				vis[tmp+a[i]]--;
				q.push(tmp+a[i]);
			}
			q.push(a[i]);
			vis[a[i]]--;
			cout<<a[i]<<' ';
		}
	}
	return 0;
}
```


---

## 作者：wheneveright (赞：2)

## 思路

考虑暴力，即 $S$ 中最小的前两个数必然是原先数组中的最小两个数字，将其存入 $a_1, a_2$，并且从 $S$ 中移除，读者自证不难。

然后就是将 $a_1 + a_2$ 从 $S$ 中移除，接下来最小的数必然是第三个数 $a_3$，同样也是进行移除后，将 $a_1 + a_2 + a_3, a_2 + a_3$ 两个数分别移除，并且重复此操作。

枚举要移除的数和寻找新的 $a$ 中元素复杂度是 $O(n^2)$ 然后删除部分暴力是 $O(n)$，这样就获得了一个 $50$ 分的好成绩。

考虑优化，发现 $O(n^2 \log n)$ 完全能过，所以考虑优化 $O(n)$ 的删除过程。

首先如果所有的 $x, x \in S$ 互不相同，那么可以用二分和一个 tag 来标记是否已经被移除。具体过程的话大致是这样：

```cpp
for (int i = 1; i <= m; i++)
	if (!vis[i]) {
		a.push_back (b[i]); // 如果没出现过的话先加入集合
		sum += b[i]; now = sum; // 将其累计的集合的总和中
		for (auto j : a) {
			int id = lower_bound (b + 1, b + 1 + m, now) - b;
			// 二分找到第一个大于等于当前区间和的位置，并且删去，可以证明 b[id] 只有可能等于 now
			vis[id] = true; now -= j; // 打上标记，表示删除
			// 这里是从 a 的第一个元素开始遍历的，所以每次减去 j 后 now 依旧是一个连续 a 的区间的和
		}
	}
```

其中 `a` 为 `vector < int >` 类型。

`for (int i : a)` 等价于 `for (int j = 0, i = a[j]; j < a.size (); j++, i = a[j])`。

然后考虑有重复的情况，如果当前查找到的 `id` 已经被删除，那么就要删去其后面第一个未被删除的元素，直接用 `for` 循环往后跳的话会退化到 $O(n)$。

考虑这个过程：每次只删除一个元素，要支持跳到某元素的后面第一个未标记过的。完成这个过程可以用并查集优化的链表，这个与花神游历各国那题和廊桥分配的部分解法优化相同。

## 完整代码

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;

int n, m, now, sum; // sum 记录当前 a 集合中的元素和，用 vector 模拟集合 
bool vis[maxn * maxn];
int b[maxn * maxn];
int fa[maxn * maxn];
int getfa (int id) { return id == fa[id] ? id : fa[id] = getfa (fa[id]); }
vector < int > a;

int main () {
	cin >> n; m = (n + 1) * n / 2;
	for (int i = 1; i <= m; i++) cin >> b[i], fa[i] = i;
	sort (b + 1, b + 1 + m);
	for (int i = 1; i <= m; i++)
		if (!vis[i]) {
			a.push_back (b[i]); // 因为 b 是有序的，所以按顺序加入 a 后必然也是有序的 
			sum += b[i]; now = sum;
			for (int j : a) {
				int id = getfa (lower_bound (b + 1, b + 1 + m, now) - b);
				vis[id] = true; now -= j; fa[id] = id + 1; // 删除后将被删除元素链接到后面 
			}
		}
	for (int i : a) printf ("%d ", i);
	return 0;
}
```

---

## 作者：xhz_ (赞：2)

## 思路

基本思路是通过筛法和二分，将最开始 $n$ 个声音的共鸣度给筛选出来。

我们可以先对已读入的共鸣度进行排序，然后从最小的开始。如果，第 $i$ 个共鸣度未被标记等于某一段原共鸣度之和，那么就将第 $i$ 个共鸣度记录下来，并将当该共鸣度参与且为之中最大的各段之和，进行二分查找，将找到的位置做标记。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long s[2001001],v[2001001],a[2001],top=0;
int find(int l,int r,unsigned long long x){//二分查找，要注意找的是左边界。 
	int mid;
	while(l<r){
		mid=(l+r)>>1;
		if(s[mid]==x)r=mid;
		else if(s[mid]>x)r=mid;
		else l=mid+1;
	}return l;
}
int main(){
	int n,m;cin>>n;m=n*(n+1)/2;
	for(int i=1;i<=m;i++){
		scanf("%llu",&s[i]);
	}
	sort(s+1,s+m+1); 
	int i=1,flag=0,same=1;
	while(i<=m){
		if(top==n)break;//当所有原共鸣度已经找到，就没必要再循环了 
		if(v[i]){i+=v[i];continue;}//如果已经被标记不能为原共鸣度，就跳过 
		a[++top]=s[i];
		unsigned long long tot=0;int last=i,now;//last从i开始是因为比i小的位置不可能有比tot+s[i]大的值 
		for(int j=top-1;j;j--){
			tot+=a[j];
			now=find(last,m,tot+s[i]);
			v[now]++;last=now; 
		}
		if(v[i])i+=v[i];//因为是共鸣度可以为0的 
		i++;
	}
	for(int i=1;i<=top;i++)printf("%llu ",a[i]);
	return 0;
}
```


---

## 作者：Mars_Dingdang (赞：1)

暴力出奇迹……

## 题目大意
现在有一个长度为 $n$ ，非严格递增的非负整数序列 $a_i$。给出所有 $\dfrac{n(n+1)}2$ 个子段和 $\sum_{i=l}^r a_i$，请还原出原序列。

## 大体思路
当 $n=1$ 时直接输出即可。

除此之外，**记 $m=\dfrac{n(n+1)}2$**，一个很显然的结论是，将所有子段和按从小到大排序后，最小的两项 $s_1, s_2$ 一定是原序列的 $a_1, a_2$。

然后，考虑哪些数有可能称为 $a_3$：将 $a_1+a_2$ 标记一次（表示这一项作为子段和，不可能是 $a_3$），继续遍历 $s$。当遇到一个被标记的数时，令其被标记的次数减一（原因是题目中提到 $S$ 为可重集）并跳过；遇到第一个未被标记的数即为 $a_3$，以此类推。

也就是说，我们可以将算法流程概括为：

- 假设现在已经求出 $a_1\sim a_{k-1}$，$a_k$ 待求。

- 向后遍历 $s$，
	1. 若 $s_i$ 被标记过，令标记次数 $-1$ 并跳过；
   2. 若 $s_i$ 为被标记过，则 $a_k=s_i$。（若 $a_k>s_i$，由于前面的若干项构成的子段和都已被标记，不妨设 $s_i=a_u+a_v(k\le u)\ge a_k+a_v\ge a_k$ 矛盾，不可能。）

- 将所有 $a_k$ 贡献的子段和标记。具体地，需要将 $\operatorname{sum}(2\sim k), \operatorname{sum}(3\sim k),\cdots, \operatorname{sum}(k-1\sim k)$ 标记。因此，需要记录前 $k-1$ 项的后缀和并逐一标记同时更新，最后将 $a_k$ 加入后缀和。

这样，标记子段和的单次时间复杂度为 $O(n)$，扫描 $s$ 时由于所有被标记的和均被跳过，真正的复杂度也是 $O(n)$，计算 $a_i$ 复杂度 $O(n^2)$。处理标记时可以用 `unordered_map`，在 $O_2$ 下较快。

全题复杂度 $O(m\log m)$，其中 $m=\dfrac{n(n+1)}2$，瓶颈在于排序。

## 完整代码
```cpp
//并不完整，去掉头文件和快读等
int n, s[maxn], a[maxn], sum[maxn], tot;
unordered_map <int, int> del; //删除标记
int main () {
	read(n);
	int m = (n * (n + 1) / 2);
	rep(i, 1, m) read(s[i]);
	sort(s + 1, s + m + 1); //排序
	if(n == 1) return writeln(s[1]), 0; //特判
	
	a[++a[0]] = s[1]; 
	a[++a[0]] = s[2];
	sum[++tot] = a[2];
	sum[++tot] = a[1] + a[2]; // 后缀和
	del[sum[tot]] ++;
	
	rep(i, 3, m) {
		if(del[s[i]] > 0) {
			del[s[i]] --;
			continue;
		}
		a[++a[0]] = s[i];
		rep(j, 1, tot) {
			sum[j] += s[i];
			del[sum[j]] ++;
		}
		sum[++tot] = s[i];
	}	
	rep(i, 1, a[0]) write(a[i]), putchar(' ');
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：1)

# 前言

本题需要一点点思考时间。

# 正文

我们观察一下样例，发现一个特殊性质：

将 $S$ 排个序，我们发现不难发现 $S$ 的前两项恰好是 A 的前两项。

于是就把他们扔进去。看到值域过小我们开个数组，记录一下每个数出现了几次。

仔细思考发现，可以维护一个后缀和，每次发现一个计数不为的数都把他加入 $A$，然后拿他更新。

我们的后缀和能干嘛？当然是删别的数了，直接把计数器减去一。

问题是，为什么这样做是对的？

由于 $S$ 中的每一个数都是 $A$ 的子段和，所以你前一个 $A$ 的数早就把之前的是这个后缀和的人都删除了，所以你自己做自己的就行了。

因此我们就做到了不遗漏的删除每一个等于 $A$ 子段和的数。

若一个数之前没被删完，就一定是 $A$ 的其中一个数。

注意要把自己也删一次。

## 小优化

超出值域的就扔掉不要了...

## 复杂度

值域是 $10^5$，后缀和跑个 $N$ 下，差不多 $\mathcal{O}(KN)$，实际上跑不满，最多只有 $\mathcal{O}(N^2)$，还有排序的 $\mathcal{O}(N\log_2N$)。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

long long N, tot;
long long arr[4000005], v[2005];
int cnt[100005];

signed main()
{
	cin >> N;
	memset(cnt, 0, sizeof(cnt));
	N = (N * (N + 1)) / 2;
	for(long long i = 1; i <= N; ++ i)
		cin >> arr[i]; 
	
	sort(arr + 1, arr + N + 1);
	for(long long i = 1; i <= N; ++ i)
	{
		if(arr[i] > 1e5)
			break;
		
		++ cnt[arr[i]];
	}
	
	tot = 2;
	v[1] = arr[1];
	v[2] = arr[2];
	-- cnt[v[1] + v[2] > 1e5 ? 0 : v[1] + v[2]];
	-- cnt[v[1]];
	-- cnt[v[2]];
	for(long long i = arr[2]; i <= 1e5; ++ i)
	{
		while(cnt[i] > 0)
		{
			++ tot;
			v[tot] = i;
			int sum = 0;
			for(long long j = tot; j >= 1; -- j)
			{
				sum = sum + v[j];
				if(sum > 1e5)
					break;
					
				-- cnt[sum];
			}
		}
	}
	
	for(long long i = 1; i <= tot; ++ i)
			cout << v[i] << ' ';
			
	return 0;
}
```

# 后言

感谢出题人提供的优质题目！

---

## 作者：Unnamed114514 (赞：1)

### 题意
有一个序列 $a$，还有一个序列 $b$，其中 $b$ 包含所有的 $\sum\limits_{i=l}^{r}a_i$。现在给出 $b$，求 $a$。

### 思路
首先，我们将 $b$ 按照从小到大排序。然后，用一个标记数组 `vis` 标记每个数是否被访问过。

那么，如果没被访问过，就加入数组，并和之前加过的数求一次和，再更改这个和的标记即可。

注意是**可重集**，桶要开成 `int`，值域比较大，用 `map`，时间复杂度 $O(n^2\log n^2)$（排序）。

但是，我们会 T 飞，只有 $50$ 分的好成绩。

时间复杂度已经不能优化了，我们考虑如何剪枝：

剪枝 1：如果生成的数组已经有 $n$ 个元素，那么就不需要更新标记。

其实这个剪枝就可以过了，但还可以更进一步：

剪枝 2：因为答案不超过 $10^5$，所以我们不用存储 $10^5$ 以上的标记，这样桶可以直接用 `int` 存。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e6;
int n,a[maxn],t,v[2005],s,t1[maxn];
inline char gc(){
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	register int res=0;
	static char ch=gc();
	if(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=gc();
	}
	return res;
}
int main(){
	n=read();
	int k=n*(n+1)>>1;//输入个数
	for(int i=1;i<=k;++i){
		a[i]=read();
		if(a[i]<=1e5)
			++t1[a[i]];//剪枝 1
	}
	sort(a+1,a+k+1);
	for(int i=1;i<=k;++i)
		if(t1[a[i]]){
			printf("%d",a[i]);
			putchar(' ');
			v[++t]=a[i];
			if(t==n)
				return 0;//剪枝 2
			for(int j=t;j;--j){
				s+=v[j];
				if(s>1e5)
					break;//剪枝 1
				--t1[s];
			}
			s=0;
		}
    return 0;
}
```

---

## 作者：rzh123 (赞：0)

# P8148 题解  

题目链接：[P8148 声海 | Sea of Voices](https://www.luogu.com.cn/problem/P8148)  

首先澄清一点：  
数据范围里的 $0\le a_i \le 10^5$ 中 $a_i$ 指的是“最初的声音”，而不是输入数据。  
题解中输入数据用 $b_i$ 表示。  

首先，$b_i$ 中有一部分数据是由小的 $a_i$ 组合成的，所以需要根据已知的 $a_i$ 排除 $b_i$ 中由已知 $a_i$ 组合成的数据，剩下没有被排除的就是答案。  

这很像“素数筛”。  

思路类似于素数筛。首先 $a_i$ 是非负的，而且递增，所以先把 $b_i$ 排序，然后从最小开始扫。由于是 $b_i$ 可重复，要改进一下素数筛，不能用 `bool` 数组记录筛掉的数，而是用桶，$no_x$ 记录当前需要删除多少个 $x$。每遍历到一个 $b_i$，就检查这个应不应该（保留即 $no_{b_i}$ 是否为 $0$），不保留就把删除标记减一，保留就像素数筛一样，再遍历一次 $1\sim i-1$（设为 $j$），删除每一个 $\sum\limits_{k=j}^{i}a_k$，直到得到 $n$ 个答案。  

为了加快区间求和的速度，可以用前缀和，记录 $a_i$ 的前缀和。  

时间复杂度：$\mathcal{O}(n \log n + n^2)$。  

代码：  
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc getchar()
#define pc(c) putchar(c)
#define N 2001077
#define A 100007
int n,s;
int a[N];
int ans[N];
int ss[N];
int no[A];
int read(){
	int t=0;
	char c=gc;
	while(c<'0'||c>'9') c=gc;
	while(c>='0'&&c<='9') t=10*t+(c^48),c=gc;
	return t;
}
void write(int x){
	if(x<10){
		pc(x|48);
		return;
	}
	write(x/10);
	pc((x%10)|48);
}
int main(){
	int c=0;
	n=read();
	s=((n*(n+1))>>1);
	for(int i=1;i<=s;++i){
		a[i]=read();
	}
	std::sort(a+1,a+s+1);
	for(int i=1;i<=s;++i){
		if(no[a[i]]){
			--no[a[i]];
		}
		else{
			write(a[i]);
			pc(' ');
			++c;
			ss[c]=ss[c-1]+a[i];
			if(c==n){
				break;
			}
			for(int j=1;j<c;++j){
				int t=ss[c]-ss[j-1];
				if(t<A){
					++no[t];
				}
			}
		}
	}
	return 0;
}
```  
[AC 记录](https://www.luogu.com.cn/record/69318253)  


---

## 作者：Lonely_NewYear (赞：0)

# P8148 题解

## 题目大意

给你一个长度为 $n$ 的单调不下降非负整数序列 $a$ 的所有区间和，求原序列 $a$。

## 题目分析

手玩一下样例#2。

```
5
1 3 4 7 8 9 10 11 15 17 18 19 24 27 28
```

注意样例是帮我们排过序的，实际数据点可能无序。

因为 $a$ 单调不下降，所以 $a_1$ 肯定是这些区间和中最小的，那么 $a_1=1$。

把 $a_1$ 舍弃，剩下的数中要不然包含 $a_2$ 要不然包含比 $a_2$ 大的数，所以说此时 $a_2$ 最小，那么 $a_2=3$。

把 $a_2$ 舍弃，剩下的数除了 $a_1+a_2$，肯定 $a_3$ 最小，所以我们可以先找到 $a_1+a_2$，即 $4$，把它舍弃，然后找到当前最小值赋给 $a_3$，所以 $a_3=7$。

把 $a_3$ 舍弃，找到 $a_2+a_3$ 和 $a_1+a_2+a_3$，舍弃，找最小值赋给 $a_4$……

当数据规模扩展到 $n$，我们在寻找 $a_i$ 时，就需要把所有 $a_1$ 到 $a_{i-1}$ 的后缀和舍弃，找到当前最小值赋给 $a_i$。

具体实现可以把所有数先排一下序，要舍弃一个数的话就把这个数加入一个小根堆 $q$，找最小值时用一个指针，如果当前数在小根堆中（注意因为当前数是最小值，所以肯定是堆头），那么指针后移一位，同时把推头 pop 掉，重新寻找最小值。说的不清楚可以看看代码。

瓶颈在于把每个数加入小根堆，时间复杂度 $O(n^2\log n)$。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m;
int a[2001001],ans[2001];//这里 a 指输入数组，ans 是原数组
priority_queue<int,vector<int>,greater<int> > q;//小根堆
int main()
{
	scanf("%d",&n);
	m=n*(n+1)/2;
	for(int i=1;i<=m;i++)scanf("%d",&a[i]);
	sort(a+1,a+m+1);
	int now=1;
	for(int i=1;i<=n;i++)
	{
		while(!q.empty()&&a[now]==q.top())now++,q.pop();//找最小值
		ans[i]=a[now];
		int sum=0;
		for(int j=i;j;j--)sum+=ans[j],q.push(sum);//计算后缀和，舍弃
	}
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}
```

谢谢观看！

---

## 作者：water_three (赞：0)

### 题目大意：
有一个数列 $a_i$，从其中选任意连续个数相加组成很多新的数，再将这些新的数无序插入原数列，题目要求求这个原数列。
### 思路：
排序后，由于对于任何 $a_i$，其值都为**非负数**，所以很容易发现 $a_1$ 和 $a_2$ 必定是原数列的值，因为它们不能通过相加得到。那么对于 $a_3$ 呢？容易发现如果 $a_3$ 等于 $a_1 + a_2$。那么它就是新生成的数。因此，我们考虑先将给出的 $a_i$ 排序，依次判断当前数是新生成的，还是原来就有的。如果 $a_i$ **不可以通过比它小的几个数相加得到**，那么它就是原数列的值。这时，就维护一下它和前面几个原来的数相加的和。

#### 注意：
* 要去掉给出的数列里没有涉及到的数。
* 有可能有的原数列里的数等于新生成的数。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=5000000;
long long n,a[MAXN],ans[MAXN],tot,now=1,idx,sum[MAXN];
priority_queue <int,vector<int>,greater<int> > dai;
int main() {
	cin>>n;
	for(long long i=1; i<=n*(n+1)/2; i++)scanf("%d",&a[i]);
	sort(a+1,a+n*(n+1)/2+1);
	for(long long i=1; i<=n*(n+1)/2; i++) {
		if(i==1) {
			ans[++tot]=a[i];
			printf("%d ",ans[tot]);
		} else if(i==2) {
			ans[++tot]=a[i];
			printf("%d ",ans[tot]);
			dai.push(a[1]+a[2]);
			sum[1]=a[1];
			sum[2]=a[2]+a[1];
		} else {
			while(!dai.empty()&&dai.top()<a[i])dai.pop();//去掉给出的数列里没有涉及到的数 
			if(!dai.empty()&&a[i]==dai.top()) {
				dai.pop();
				continue;
			} else {
				ans[++tot]=a[i];
				printf("%d ",ans[tot]);
				sum[tot]+=sum[tot-1]+a[i];
				for(long long k=tot-1; k>=1; k--) {
					dai.push(sum[tot]-sum[k-1]);
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：cqbzhyf (赞：0)

[题面](https://www.luogu.com.cn/problem/P8148)

先看数据范围，$0 \le a_i \le 10^{5}$，也就是说 $\ge 10^{5}$ 的数字一定不是答案，所以想办法往数值大小上思考，就有了**桶**的做法。

首先将输入数组中 $\le 10^{5}$ 的数字全部放入桶中，枚举 $0$ ~ $10^{5}$，如果桶中有这个数，将现在的答案与当前元素相加排除几个元素的共鸣（如果超过 $10^{5}$，直接跳出），最后将当前枚举元素放入答案数组。

最后输出即可。

## 代码在这里

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int ch=0,num=0;
	char c=getchar();
	while(!isdigit(c))ch|=(c=='-'),c=getchar();
	while(isdigit(c))num=(num<<1)+(num<<3)+(c^48),c=getchar();
	return ch?-num:num;
}
int n,cnt[100005],t[100005],tot,x;
signed main(){
	n=read();
	int m=n*(n+1)/2;
	for(int i=1;i<=m;++i){
		x=read();
		if(x<1e5)++cnt[x];
	}
	for(int i=0;i<=1e5;++i){
		while(cnt[i]){
			int sum=i; 
			for(int j=tot;j;--j){
				sum+=t[j];
				if(sum>1e5)break;
				--cnt[sum];
			} 
			--cnt[i];
			t[++tot]=i;
		}
	}
	for(int i=1;i<=tot;++i)printf("%lld ",t[i]);
	return 0;
} 
```

---

