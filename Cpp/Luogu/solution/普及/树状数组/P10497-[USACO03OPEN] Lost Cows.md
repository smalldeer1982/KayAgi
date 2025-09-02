# [USACO03OPEN] Lost Cows

## 题目描述

有 $N (2 \leq N \leq 8000)$ 头奶牛，它们在编号范围 $[1,N]$ 内具有唯一的标号。在一个极其糟糕的判断展示中，它们去了附近的“水坑”，在晚饭前喝了太多啤酒。到了排队吃晚饭的时候，它们没有按照编号升序的顺序排队。可惜的是，FJ 没有办法对它们进行排序。

此外，他在观察问题方面也不太擅长。他没有记下每头奶牛的编号，而是得到了一个相当愚蠢的统计数据：对于队伍中的每一头奶牛，他知道在这头奶牛之前，有多少头奶牛的编号确实比它小。给定这些数据，请告诉 FJ 奶牛的精确排列顺序。

## 样例 #1

### 输入

```
5
1
2
1
0```

### 输出

```
2
4
5
3
1```

# 题解

## 作者：Ia_aI (赞：28)

# 基本思路
遵循从已知推出未知的原则，如果从前向后做，第
一个位置前面没有数字，第二个位置上要求有 $1$ 个数字比其小，这时完全没办法确第二个位置的数字为多少，可能性太多了。于是从后向前做。

举个例子：$1$ $2$ $1$ $0$。

它的最后一个位置为 $0$，于是只能填 $1$，因为 $1$ 是最小的，没有数字比它小。确定后则将 $1$ 加入树状数组。

倒数第二个位置为 $1$，由于 $1$ 已使用过了，于是这个位置只能放 $3$ 了。

倒数第三个位置为 $3$，由于 $1$，$3$ 已使用过，于是这个位置只能放 $5$ 了。

# 解法一：暴力做法
## 思路

开一个数组 $vis$，初值均为 $0$。

将读入的数字倒过来做，设当前处理的数字为 $a$，则在 $vis$ 数组中进行查找一个最小的位置，满足前缀和为 $a+1$。

找到这个位置后，将其标为 $1$。

时间复杂度为 $O(n^2)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10001],s,st[10001];
bool vis[10001];
int main()
{
  cin>>n;
  for(int i = 2;i <= n;i++) cin>>a[i];
  for(int i = n;i >= 1;i--)
  {
    s = 0;
    for(int j = 1;j <= n;j++)
      if(vis[j] == 0)
      {
        s++;
        if(s == a[i] + 1)
        {
          vis[j] = 1;
          st[i] = j;
        }
      }
  }
  for(int i = 1;i <= n;i++) cout<<st[i]<<'\n';
  return 0;
}
```
# 解法二：二分加树状数组

## 思路

可以发现本题就是在不断找某个前缀和为给定的值，并且其值越小越好。

于是可以二分这个位置，然后统计其前缀和。

时间复杂度为 $O(n\log^2n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5000001],s,st[5000001],c[5000001];
bool vis[5000001];
int lowbit(int x)
{
  return x & (-x);
}
void add(int i,int x)
{
  while(i <= n)
  {
    c[i] += x;
    i += lowbit(i);
  }
}
int query(int i)
{
  int t = 0;
  while(i > 0)
  {
    t += c[i];
    i -= lowbit(i);
  }
  return t;
}
signed main()
{
  cin>>n;
  for(int i = 1;i <= n;i++)
  {
    add(i,1);
  }
  for(int i = 2;i <= n;i++)
  {
    scanf("%d",&a[i]);
  }
  for(int i = n;i >= 1;i--)
  {
    int l = 1,r = n;
    while(l <= r)
    {
      int mid = (l + r) / 2;
      if(query(mid) > a[i]) r = mid - 1;
      else l = mid + 1;
    }
    st[i] = l;
    add(l,-1);
  }
  for(int i = 1;i <= n;i++) printf("%d\n",st[i]);
  return 0;
}
```
# 结语
如果这篇题解对您有帮助，就请点个赞支持一下吧！

---

## 作者：Wendy_Hello_qwq (赞：16)

[题目传送门。](https://www.luogu.com.cn/problem/P10497)

[原文食用效果更佳。](https://www.luogu.com/article/e6inu5tj)

## 题意

给你一个整数 $n$，表示有 $n$ 头奶牛，每头奶牛的品牌号码都是 $1\sim n$ 的整数，告诉了你每一头奶牛前面的比它品牌号码小的奶牛数，让你**按顺序**输出奶牛的品牌。

## 分析

当我们知道了一头奶牛前面的奶牛的品牌号码的顺序，还有这头奶牛前面有多少头奶牛比它品牌号码小的时候，就可以知道这头奶牛排在第几个。

比如现在告诉你这头奶牛前面有 $x$ 头奶牛的品牌号码已排好顺序，还告诉你这头奶牛前面有 $y$ 头奶牛的品牌号码比它小，那么，这头奶牛的品牌号码就在 $y$ 和 $y+1$ 之间。

## Code

```cpp
#include <cstdio>
using namespace std;
int n, t, a[8007], bz[8007];
int main()
{
	// 第一个位置 
	a[1] = 1;
	scanf ("%d", &n);
	for (int i = 2; i <= n; i++)
	{
		// 这个品牌的奶牛有多少 
		scanf ("%d", &t);
		// 向后移，移到t+1的位置，腾出位置放新的奶牛 
		for (int j = n; j >= t + 1; j--)
			a[j + 1] = a[j];
		// 当前t+1的位置放新奶牛 
		a[t + 1] = i;
	}
	// 从第n头奶牛开始往前推，记录奶牛品牌 
	for (int i = n; i >= 1; i--)
		bz[a[i]] = i;
	// 输出 
	for (int i = 1; i <= n; i++)
		printf ("%d\n", bz[i]);
	return 0;
}
```

[AC 记录。](https://www.luogu.com.cn/record/168899083)

完结撒花。

作者写题解不易，点个赞再走呗。

---

## 作者：MoonCake2011 (赞：7)

呃啊，怎么改题了。

于是我，又过来了。

因为改题后也很简单。

题意是这样的：

有 $n$ 个数组成的数列，已知它们每个数前面有多少个比它小的数。

求每个数的排名。

设已知的大小数列为 $a$，排名数列为 $rk$。

从后向前考虑，因为 $rk_n$ 就等于 $a_n+1$。

这个很好想。

因为前 $n-1$ 个数加它本身就是整个数列。

接着，推不动了。

即使知道了 $rk_n$ 也无法推算 $rk_{n-1}$。

于是，辅助数组，启动。

可以设置一个 `bool` 型的辅助数组 $f$ 。

$f_i=1$ 代表 $rk$ 为 $i$ 的数没有出现，为 $0$ 则相反。

计算出 $rk_n$ 可以更新 $f$ 数组。

然后，就在剩下的 $n-1$ 个 $1$ 中选择。

这 $n-1$ 个 $1$ 代表前 $n-1$ 个没选的。

第 $n-1$ 个数是前 $n-1$ 个数的第 $a_{n-1}+1$ 小。

所以，在现存 $f$ 数组上，选择正数第 $k$ 个 $1$ 的那个位子（下标），就是 $rk_{n-1}$。

然后，修改 $f$ 数组，依此类推。

梳理一下，我们需要（对 $f$ 数组）干什么。

第一，单点修改。

第二，查询前缀和为 $k$ 的位置。

仅此而已。

单点加前缀，可以启动树状数组。

查询位置，启动二分。

时间复杂度 $O(n\log^2n)$。

不够优秀。

因为树状数组是倍增思想的产物，所以果断选择用倍增替换二分。

每次倍增，我们需要求区间 $[2^a+2^b\dots2^n+1,2^a+2^b\dots2^n+2^m]$ 的值。

等一下,这个值不是树状数组 $c_{2^a+2^b\dots2^n+2^m}$ 的值吗？

赚大了。

第 $k$ 小，时复降低到 $O(\log n)$ 了（倍增的时间）。

时间复杂度 $O(n\log n)$。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100010];
int c[100010];
inline int lowbit(int x){
	return x&-x;
}
inline void update(int x,int k){
	while(x<=n) c[x]+=k,x+=lowbit(x);
}
inline int get_kth(int k){
	int ans=0,sum=0;
	for(int i=30;i>=0;i--){
		if(ans+(1<<i)>n) continue;
		if(sum+c[ans+(1<<i)]<k) ans+=(1<<i),sum+=c[ans];
	}
	return ans+1;
}
int ans[100010];
int main() {
    ios::sync_with_stdio(0);
	cin>>n;
	update(1,1);
	for(int i=2;i<=n;i++) cin>>a[i],update(i,1);
	for(int i=n;i>=1;i--){
		int p=get_kth(a[i]+1);
		update(p,-1);
		ans[i]=p;
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
	return 0;
} 
```

---

## 作者：Chtholly_Tree (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P10497)

## Part 1 翻译

### 题目描述

Farmer John 的 $n$ 头奶牛编号为 $1, 2, \cdots n$，由于奶牛们的愚蠢，他们总是没法按照 Farmer John 希望的按照编号从小到达的顺序排成一排。现在奶牛们已经排成了一排。Farmer John 知道排在位置 $i$ 的奶牛前面有 $a_i$ 头奶牛的编号比它小。Farmer John 想知道每头奶牛的正确位置应该在哪里。

### 输入格式

第 $1$ 行：一个整数 $n$ 表示奶牛的数量。

接下来 $n - 1$ 行，分别表示第 $2$ 头奶牛到第 $n$ 头奶牛前面有多少奶牛的编号比它小。由于第 $1$ 头奶牛前面没有牛，所以没有该信息。

### 输出格式

输出 $n$ 行：每行一个整数，第 $i$ 行的整数表示当前排在位置 $i$ 的牛的正确位置应该是多少。

## Part 2 思路

因为没有树状数组的题解，所以我来写一篇。

从后往前考虑每头牛：

第 $n$ 头牛：由于它的后面没有牛了，所以它排 $a_n + 1$ 位。

第 $n - 1$ 头牛：它后面只有 $1$ 头牛，且排 $a_n + 1$ 位，除 $a_n + 1$ 以外，剩下的名次中它排 $a_{n - 1} + 1$ 位。

以此类推，第 $i$ 头牛排除第 $[i + 1, n]$ 牛已经使用的排位后，排在第 $a_i + 1$ 位。

问题转换为在一个**动态变化**的序列中找第 $a_i + 1$ 小的元素。

可以使用二分答案 + 树状数组：

定义 $cnt_i$ 记录排位 $i$ 是否可使用，$cnt_i = 1$ 表示可使用，$cnt_i = 0$ 表示不可使用。

二分答案 $mid$，如果小于等于 $mid$ 的编号中可用数量大于等于 $a_i + 1$，表示 $mid$ 大了，反之 $mid$ 小了。

$mid$ 左边可用的排位就是 $cnt_1$ 到 $cnt_{mid}$ 的累加和，可以使用树状数组维护。

## Part 3 代码

```cpp
#include <bits/stdc++.h>
#define int long long
//#pragma GCC optimize(3, 2, "Ofast")

using namespace std;

const int N = 100005;
int n, a[N], c[N], ans[N];

inline int lowbit(int x) {
	return x & -x;
}

void add(int x, int v) {
	while (x <= n) {
		c[x] += v;
		x += lowbit(x);
	}
}

int sum(int x) {
	int ans = 0;
	while (x) {
		ans += c[x];
		x -= lowbit(x);
	}
	return ans;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	add(1, 1);
	for (int i = 2; i <= n; i++) {
		cin >> a[i];
		add(i, 1);
	}
	for (int i = n; i >= 1; i--) {
		int l = 1, r = n + 1;
		while (l < r) {
			int mid = l + r >> 1;
			if (sum(mid) >= a[i] + 1) r = mid;
			else l = mid + 1;
		}
		ans[i] = l;
		add(l, -1);
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
	
	return 0;
}
```

---

## 作者：wrh316 (赞：6)

本题正解为平衡树，但是我们发现 $n \le 8000$，$O(n^2)$ 是能过的，所以直接考虑模拟。
### 思路
和插入排序的思路差不多，如果有 $x$ 头奶牛的品牌号码比当前奶牛小，那么当前奶牛应该排在这 $x$ 头奶牛的后面，也就是说，这头奶牛应该排在 $x + 1$，$x$ 就是当前的 $a _ {i}$。

平衡树思路代码就不写了，大家有时间可以自己去试一试。
### 代码
```c++
#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

typedef long long ll;
int n;
int a[MAXN], dis[MAXN];
bool vis[MAXN];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 2; i <= n; i++) cin >> a[i];
	for (int i = n; i >= 1; i--) {
		int cnt = 0;
		for (int j = 1; j <= n; j++) {
			if (!vis[j]) {
				cnt++;
				if (cnt == a[i] + 1) {
					dis[i] = j;
					vis[dis[i]] = true;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) cout << dis[i] << "\n";
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：5)

从第 $N$ 头牛到第 $1$ 头牛依次模拟。对于第 $i$ 头牛，他的号码就是当前所有没有被占用的号码中第 $a_i+1$ 小的。

因为当前所有没有被占用的号码就是第 $1 \sim i$ 头牛的号码，而前面有 $a_i$ 头牛的号码比这头牛的号码小，那么这头牛的号码就是第 $a_i+1$ 小的。

时间复杂度 $O(N^2)$，可以通过。
```cpp
#include<cstdio>
using namespace std;
const int N=8010; int a[N],ans[N]; bool book[N];//ans 是最终答案，book 用来记录号码是否被占用
int main() {
  int n; scanf("%d",&n);
  for(int i=2;i<=n;i++) scanf("%d",&a[i]);
  for(int i=n;i>=1;i--) {
    int cnt=0;
    for(int j=1;j<=n;j++)//在没有被占用的号码中求出第 a[i]+1 小的
      if(!book[j]) {
        cnt++;
        if(cnt==a[i]+1) { ans[i]=j,book[ans[i]]=true; break; }
      }
  }
  for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
  return 0;
}
```

update：

（感谢 <https://www.luogu.com.cn/article/6l66uy9z> 给予我灵感）

上述操作相当于在一个集合里进行如下操作：

- 插入 $1 \sim N$。
- 求第 $a_i+1$ 小的数。
- 删除一个数。

可以用 Treap 维护，时间复杂度 $O(N \log N)$。

代码比较长，所以放在[剪贴板](/paste/5fjz5p61)里。

---

## 作者：ycy1124 (赞：3)

## 题意
有 $n$ 头奶牛，品牌都是  $1\sim n$ 之间的整数，告诉你每头奶牛前有多少头奶牛的品牌比它小，按 **顺序** 输出排队奶牛的品牌。
## 分析
如果知道一头奶牛前面奶牛的品牌顺序，又知道他前面有多少头奶牛比他小，这样明显就可以知道他在前面所有奶牛品牌序列中排第几。

例如:现在有  $m$ 头奶牛的品牌的排序后的序列，现在告诉你第 $m+1$ 头奶牛前面有 $k$ 奶牛的品牌比他小，那他的品牌一定是介于第 $k$ 头奶牛的品牌与第  $k+1$ 头奶牛的品牌之间。 
## 实现
用数组记录前面奶牛的品牌序列来模拟此过程，每次读入一头新的奶牛的数据 $k$ 时，将原序列的第 $k+1 \sim m$ 头奶牛 **向后移一个** ，把空位给新的奶牛。最后记录+输出。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[8001],b[8001];
int main(){
	int n;
	a[1]=1;
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		int x;
		scanf("%d",&x);
		for(int j=n;j>=x+1;j--){//向后移。
			a[j+1]=a[j];
		}
		a[x+1]=i;
	}
	for(int i=n;i>=1;i--){//记录。
		b[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",b[i]);
	}
	return 0;
}
``````
[AC 记录](https://www.luogu.com.cn/record/168918666)。

最后也是  $\mathcal{O}(N^2)$ 通过此题。

---

## 作者：spider_men (赞：2)

我们发现正着做不好做，每个数可能因为后面的数而让位。

正难则反，第 $n$ 个数显然是 $a_n+1$，现在前 $n-1$ 个数只能是 $\le n$ 且 $\neq a_n+1$ 的正整数，第 $n-1$ 个数就是其中第 $a_{n-1}+1$ 小的，然后再把第 $n-1$ 个数删去找第 $a_{n-2}+1$ 小的，以此类推，直到求出第 $1$ 个数为止。

涉及到删数和求第 $k$ 小的操作，可以维护一个树状数组表示每个数是否被删去，再在树状数组上二分求第 $k$ 小。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,x,a[N],c[N],ans[N];
int lowbit(int x){return x&(-x);}
void add(int x,int k){
	for(int i=x;i<=2*n;i+=lowbit(i)) c[i]+=k;
}
int sum(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=c[i];
	return res;
}
int main(){
	scanf("%d",&n);
	add(1,1);
	for(int i=2;i<=n;i++){
		scanf("%d",&a[i]);
		add(i,1);
	}
	for(int i=n;i>=1;i--){
		int l=1,r=n,t;
		while(l<=r){
			int mid=(l+r)>>1;
			if(sum(mid)>=a[i]+1){
				t=mid;
				r=mid-1;
			}else l=mid+1;
		}
		ans[i]=t;
		add(t,-1);
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
} 
```

---

## 作者：pragma_GCC (赞：1)

## 题目大意
有 $n$ 头奶牛，已知它们的身高为 $1$ 到 $n$，但不清楚这个排列是什么。现让它们排成一列，并给出第 $2$ 到 $n$ 头奶牛前面有多少头奶牛的身高比自己低。求这个排列。  
数据范围：$2 \le n \le 8000$。  
#### 思路分析
由于 $n \le 8000$ ，故可以选择时间复杂度为 $n^2$ 的做法。从后往前依次考虑，对任意 $i$，剩余的数中第 $a[i+1]$ 小的数即为当前位的答案。
#### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100010];
bool f[100010];
int ans[100010];
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		if(i!=1)cin>>a[i];
		f[i]=1;
	}
	for(int j=n;j>=1;j--){
		int cnt=0;
		int i=0;
		while(cnt<=a[j]){
			i++;
			if(f[i]){cnt++;}
		}
		ans[j]=i;
		f[i]=0;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：I_am_Lord_Voldemort (赞：1)

这里给一种平衡树 $O(n\log{n})$ 的做法。
  
  根据题意，给出了每个点前，排名小于该点的点的数量。则可以把点 $a_i$ 的位置，即 $i$，作为权值。把点插入到平衡树中排名 $a_i$ 处，就可以保证每个点与之前点的相对位置的正确性。因此该做法正确。
  
  统计答案时，若中序遍历到点 $i$，权值为 $v$，即在原序列位置为 $v$，则第 $v$ 个点排名为 $i$。
  
  下面上代码：
``` 
#include<bits/stdc++.h>
using namespace std;
/*--------------------------------------------------*/
//BST定义 
const int maxn=2e5+10;
const double alpha=0.7;
struct node{
	int ls,rs;
	int val;  //权值 
	int size; //数量 
}t[maxn];
int top=1,order[maxn],cnt=0;
int root=0;
int ans[maxn]; //答案 
/*--------------------------------------------------*/
//BST节点操作 
void inorder(int u){ //回收 
	if(!u) return;
	inorder(t[u].ls); //左子树 
	order[++cnt]=u; //自己 
	inorder(t[u].rs); //右子树 
}
void setnode(int u){ //设置初值 
	t[u].ls=t[u].rs=0;
	t[u].size=1;
}
void pushup(int u){ //统计数量 
	t[u].size=t[t[u].ls].size+t[t[u].rs].size+1;
}
/*--------------------------------------------------*/
//重构操作 
void build(int l,int r,int &u){ //重建 
	int mid=(l+r)>>1;
	u=order[mid];
	if(l==r){setnode(u);return;} //叶子节点
	if(l<mid) build(l,mid-1,t[u].ls);
	if(l==mid) t[u].ls=0; //有无左子树
	build(mid+1,r,t[u].rs); //一定有右子树 
	pushup(u); //统计 
}
void rebuild(int &u){ //摧毁替罪羊 
	cnt=0;
	inorder(u);
	if(cnt) build(1,cnt,u);
	else u=0;
} 
void print_tree(int u){
	if(u){
		cout<<"v="<<t[u].val<<",l="<<t[u].ls<<",r="<<t[u].rs<<",size="<<t[u].size<<endl;
		print_tree(t[u].ls);
		print_tree(t[u].rs);
	}
}
/*--------------------------------------------------*/
//修改操作
bool check(int u){ //是否平衡 
	if((double)t[u].size*alpha<=(double)max(t[t[u].ls].size,t[t[u].rs].size)) return true; //不平衡
	return false; //平衡 
} 
void insert(int &u,int rand,int x){ //插入 
	if(!u){
		//cout<<"insert ok"<<endl;
		u=++top;
		t[u].val=x;
		setnode(u);
		//cout<<u<<" "<<t[u].val<<endl;
		return;
	}
	t[u].size++;
	if(t[t[u].ls].size>=rand) insert(t[u].ls,rand,x);
	else insert(t[u].rs,rand-t[t[u].ls].size-1,x);
	if(check(u)) rebuild(u);
}
/*--------------------------------------------------*/ 
int dfn=0;
void getans(int u){
	if(t[u].ls) getans(t[u].ls);
	ans[t[u].val]=++dfn;
	if(t[u].rs) getans(t[u].rs);
}
/*--------------------------------------------------*/ 
signed main(){
	ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	int n,x;
	cin>>n;
	root=1;t[1].val=1;setnode(1);
	for(int i=2;i<=n;i++){
		cin>>x;
		insert(root,x,i);
		//print_tree(root);
	}
	getans(root);
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
}
 ```

---

## 作者：xiao7_Mr_10_ (赞：1)

好的如你所见，这道题给出每个奶牛前面比它矮的个数然后让我们求每个奶牛的排名。

令第 $i$ 奶牛前面比它矮的个数为 $a_{i}$。

正着太难了，考虑倒着来。

先维护一个排名序列，表示第 $i$ 名是否被用过。

所以第 $n$ 只奶牛的排名就是 $a_{n}+1$，然后我们在排名序列中把它删掉，后面同理。可以发现每次就是在排名序列中找到第 $a_{i}+1$ 小的数然后删掉这个数，我们可以用线段树二分维护这个东西，所以时间复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,a[N],c[N<<2];
void updata(int x){
	c[x]=c[x<<1]+c[x<<1|1]; 
}
void build(int x,int l,int r){
	if(l==r){
		c[x]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	updata(x);
}
void change(int x,int l,int r,int s,int k){
	if(l==r){
		c[x]=k;
		return;
	}
	int mid=(l+r)>>1;
	if(s<=mid)change(x<<1,l,mid,s,k);
	else change(x<<1|1,mid+1,r,s,k);
	updata(x);
}
int query(int x,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(c[x<<1]>=k)return query(x<<1,l,mid,k);
	else return query(x<<1|1,mid+1,r,k-c[x<<1]);
}
int b[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 2;i <= n;i++)cin >> a[i];
	build(1,1,n);
	for(int i = n;i >= 1;i--){
		b[i]=query(1,1,n,a[i]+1);
		change(1,1,n,b[i],0);
	}
	for(int i = 1;i <= n;i++)cout << b[i] << "\n";
	return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

# P10497 [USACO03Open] Lost Cows
## 思路分析
首先，假设我们已知第 $i$ 头奶牛前面所有奶牛的顺序（从小到大排序），同时还知道这头奶牛前面有 $x$ 头奶牛比它小，那么就不难推断出，当前这头奶牛就一定会排在第 $x+1$ 处的位置。  
因此，我们只需要将原来排在 $x+1$ 位置上的奶牛和它后面的奶牛一起向右挪一个位置，将 $x+1$ 的位置空出，并把当前着头奶牛放进 $x+1$ 的位置即可。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[8005],ans[8005];
int main(){
    cin>>n;
    a[1]=1;  //特殊处理第一头奶牛
    for (int i=2;i<=n;i++){  //注意，从2开始到n
        cin>>x;
        for (int j=n;j>=x+1;j--) a[j+1]=a[j];  //右移，腾出位置。注意，要从右往左（这只蒟蒻在这里卡了好久）
        a[x+1]=i;  //腾出来的位置放当前奶牛
    }
    for (int i=n;i>=1;i--) ans[a[i]]=i;  //记录答案
    for (int i=1;i<=n;i++) cout<<ans[i]<<'\n';  //输出答案
    return 0;  //圆满结束！
}
```

---

## 作者：Dazlin7 (赞：0)

## 题意

有 $n$ 头牛站成一列，第 $i$ 头牛知道他的前面有 $a_i$ 头牛比他低。求它在所有牛中的高度排名。

## 思路

我们需要将每头奶牛插入到一个有序的序列中，并输出每头奶牛在最终序列中的位置。这类似于插入排序的思路。

我们发现正序不好考虑，所以可以倒序从第 $n$ 头奶牛到第 $1$ 头奶牛依次处理。对于第 $i$ 头奶牛，我们需要将其插入到当前有序序列中的适当位置。当前所有没有被占用的号码就是第 $1$ 到第 $i$ 头奶牛的号码，我们需要在这些号码中找到第 $a_i + 1$ 小的号码，并将第 $ i$ 头奶牛插入到该位置。我们从后向前移动已有的奶牛，为新奶牛腾出插入位置，同时记录每头奶牛的最终位置。

在插入过程中，记录每头奶牛在最终序列中的位置。


时间复杂度 $O(n^2)$。


## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,si[8050], op[8050];
int main() {
    si[1] = 1;
    cin>>n;
    for (int i = 2; i <= n; i++)
// 从第二个元素开始，依次读取每个元素并插入到正确的位置
    {
        int x;
        cin>>x;
        for (int j = n; j >= x + 1; j--) {
            si[j + 1] = si[j];
        }
        // 在正确的位置插入新元素
        si[x + 1] = i;
    }
    
    // 将 s 中的索引位置映射到 op
    for (int i = n; i >= 1; i--) {
        op[si[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d\n", op[i]);
    }
    
    return 0;
}
```

---

## 作者：_zuoqingyuan (赞：0)

# 题意简述

>有 $n$ 头牛站成一列，每头牛知道他的前面有 $A_i$ 头牛比他低。求它在所有牛中是第几低的。
>
> $1\le n\le 10^5,A_i<i。$

# 思路分析

第 $i$ 头牛的身高排名 $H_i$ 一定**不小于** $A_i$，因为第 $i$ 牛身后可能有其他牛比它高。这启发我们从后往前依次确定每一头牛的身高。

假设我们正在确定 $H_k$，而 $H_{k+1\sim n}$ 的身高均已经确定。显然，$H_k\ge A_k$ 且使得 $i\in[k+1,n]$ 均满足 $H_k\ne H_i$ 。

为了保证第 $i$ 头牛前有 $A_i$ 头比它低，我们选择没有出现在 $1\sim A_i,H_{k+1}\sim H_{n}$ 中的最小整数作为 $H_k$。

我们定义一个 $01$ 序列 $a$，$a_i=1$ 则表示 $i$ 未在 $H_{k+1}\sim H_n$ 中出现过。第 $k$ 头牛的身高就是第 $A_k$ 个 $1$ 在 $a$ 的下标。然后令 $a_{H_k}\to 0,k\to k-1$，直到 $k=1$。

我们如何解决「第 $A_k$ 个 $1$ 在 $a$ 的下标」这个问题？


令 $S$ 为 $a$ 的前缀和，实际就是在求解**第一个** $S_i=A_k$ 的位置 $i$。因为 $a$ 为 $01$ 序列，所以 $S$ 单调不减，可以用二分查找快速找到对应位置。因为**存在对 $a$ 的修改**，我们可以用树状数组或线段树动态维护前缀和。

二分查找和单点查询均为 $O(\log n)$，总时间复杂度为 $O(n\log ^2n)$，其中 $\log^2n=(\log n)^2$。截止目前，时间复杂度已经足够通过本题了。

## 进一步优化

我们可以用线段树继续优化到 $O(n\log n)$。线段树的基本思想就是分治，因此可以和二分结合，衍生出更快的方法。

我们假设当前求解问题的答案位于 $[l,r]$ 这个区间，$sum$ 为 $[1,l-1]$ 的 $a_i$ 之和。令 $mid=\frac{l+r}{2}$，$val$ 是 $[l,mid]$ 这个区间内的 $a_i$ 之和。

我们分两种情况缩小问题范围：

- $sum+val<A_k$：此时任何 $i\in [l,mid]$ 均有 $S_i<A_k$，故答案在 $[mid+1,r]$ 中。

- $sum+val\ge A_k$：此时存在 $i\in [l,mid]$ 使得 $S_i\ge A_k$。我们要找最小的一个，所以答案在 $[l,mid]$ 中

不断递归，直到 $l=r$，答案即为 $l$，具体的更多细节可以看代码。

# Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=1e5+10;
int n,s[N],t[N];
struct node{
    int l,r,sum;
}a[4*N];
void pushup(int p){
    a[p].sum=a[2*p].sum+a[2*p+1].sum;
}
void build(int p,int l,int r){
    a[p]=node{l,r,r-l+1};
    if(l==r)return;
    int mid=(l+r)/2;
    build(2*p,l,mid);
    build(2*p+1,mid+1,r);
    return;
}
void change(int p,int x){
    if(a[p].l==a[p].r)return a[p].sum=0,void();
    int mid=(a[p].l+a[p].r)/2;
    if(x<=mid)change(2*p,x);
    else change(2*p+1,x);
    pushup(p);
}
int ask(int p,int k){
    if(a[p].l==a[p].r)return a[p].l;
    int mid=(a[p].l+a[p].r)/2;
    if(k<=a[2*p].sum)return ask(2*p,k);
    else return ask(2*p+1,k-a[2*p].sum);
}
int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++)scanf("%d",s+i),s[i]++;
    s[1]++;
    build(1,1,n);
    for(int i=n;i>=1;i--){
        int pos=ask(1,s[i]);
        t[i]=pos;
        change(1,pos);
    }
    for(int i=1;i<=n;i++)printf("%d\n",t[i]);
    return 0;
}
```

# The End

这种线段树和二分结合的方法叫“线段树二分”~~（好像不用说也知道）~~。其实树状数组也可以和倍增结合，达到类似的效果。

推荐题目：[全局第 $k$ 小。](https://www.luogu.com.cn/problem/P3369)

---

