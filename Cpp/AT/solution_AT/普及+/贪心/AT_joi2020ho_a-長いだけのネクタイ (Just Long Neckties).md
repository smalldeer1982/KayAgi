# 長いだけのネクタイ (Just Long Neckties)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020ho/tasks/joi2020ho_a

あなたは Just Odd Inventions 社を知っているだろうか？この会社の業務は「ただ奇妙な発明 (just odd inventions)」をすることである．ここでは略して JOI 社と呼ぶ．

JOI 社は新商品「長いだけのネクタイ」を開発した．ネクタイは $ N\ +\ 1 $ 種類あり，各種類には $ 1 $ から $ N\ +\ 1 $ までの番号がついている．$ i $ 番目 ($ 1\ \leqq\ i\ \leqq\ N\ +\ 1 $) の種類のネクタイの長さは $ A_i $ である．

JOI 社は社員を集め，ネクタイの試着会を行うことにした．試着会には $ N $ 人の社員が参加し，$ j $ 人目 ($ 1\ \leqq\ j\ \leqq\ N $) の社員がはじめに付けているネクタイの長さは $ B_j $ である．

試着会は以下の手順で行われる予定である．

1. まず，試着会で使わないネクタイを $ 1 $ 種類選ぶ．
2. 次に，各社員はそれ以外のネクタイから試着するネクタイを $ 1 $ 種類選ぶ．ただし，どの $ 2 $ 人も同じ種類のネクタイを選ばないようにする．
3. 最後に，各社員は今付けているネクタイを外し，先ほど選んだネクタイを試着する．

長さ $ b $ のネクタイを付けていた社員が，長さ $ a $ のネクタイを試着すると大きさ $ \max\{a\ −\ b,\ 0\} $ の奇妙さを感じる．(ここで，$ \max\{a\ −\ b,\ 0\} $ は，$ a\ -\ b $ と $ 0 $ のうち小さくない方を表す．) 試着会において各社員の感じる奇妙さの最大値を，その試着会の**奇妙さ**とする．

試着会で使わないネクタイが $ k $ 番目の種類のネクタイのとき，試着会の奇妙さとして考えられる最小の値を $ C_k $ とする．

各種類のネクタイの長さ，各社員がはじめに付けているネクタイの長さが与えられた時，$ C_1,\ C_2,\ \ldots,\ C_{N\ +\ 1} $ の値を求めるプログラムを作成せよ．

- - - - - -

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 200\,000 $.
- $ 1\ \leqq\ A_i\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ i\ \leqq\ N\ +\ 1 $)．
- $ 1\ \leqq\ B_j\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ j\ \leqq\ N $)．

### 小課題

1. ($ 1 $ 点) $ N\ \leqq\ 10 $.
2. ($ 8 $ 点) $ N\ \leqq\ 2\,000 $.
3. ($ 91 $ 点) 追加の制約はない.

- - - - - -

### Sample Explanation 1

例えば，試着会は次のように行われる． - $ 4 $ 番目の種類のネクタイを使わないことにする． - 社員 $ 1 $ が $ 1 $ 番目の，社員 $ 2 $ が $ 2 $ 番目の，社員 $ 3 $ が $ 3 $ 番目の種類のネクタイを選ぶ． - 各社員が試着する． このとき，各社員が感じる奇妙さは順に $ 2,\ 0,\ 3 $ となるから，この試着会の奇妙さは $ 3 $ である． 社員が選ぶネクタイを変えることで、試着会の奇妙さを $ 1 $ にすることができる．例えば，試着会を次のように行うとする． - $ 4 $ 番目の種類のネクタイを使わないことにする． - 社員 $ 1 $ が $ 2 $ 番目の，社員 $ 2 $ が $ 3 $ 番目の，社員 $ 3 $ が $ 1 $ 番目の種類のネクタイを選ぶ． - 各社員が試着する． このとき，各社員が感じる奇妙さは順に $ 1,\ 1,\ 0 $ となるから，この試着会の奇妙さは $ 1 $ である． これが $ 4 $ 番目の種類のネクタイを使わない場合の試着会の奇妙さの最小値なので，$ C_4\ =\ 1 $ である． - - - - - -

## 样例 #1

### 输入

```
3
4 3 7 6
2 6 4```

### 输出

```
2 2 1 1```

## 样例 #2

### 输入

```
5
4 7 9 10 11 12
3 5 7 9 11```

### 输出

```
4 4 3 2 2 2```

# 题解

## 作者：DgNeHzL7777 (赞：1)

## 思路

拿走一个数后，让 $a$ 数组的最大值对应 $b$ 数组的最大值，让 $a$ 数组的次大值对应 $b$ 数组的次大值，以此类推。这样一定是最优的。

我们先把 $a$ 数组、 $b$ 数组排序，用 $maxx_{i}$ 表示 $a_{1} - b_{1}$ 到 $a_{i} - b_{i}$ 的最大值，$d_{i}$ 表示 $a_{i+1} - b_{i}$ 的值。用 $ans_{i}$ 记录拿走 $a_{i}$ 所得的答案。具体看代码，有注释。

## 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 200005
#define R(x) x=read()
#define int long long
using namespace std;

inline int read() {
	int x=0,y=1;
	char e=getchar();
	while(e<'0'||e>'9') {
		if(e=='-')y=-1;
		e=getchar();
	}
	while(e>='0'&&e<='9') {
		x=(x<<3)+(x<<1)+(e^'0');
		e=getchar();
	}
	return x*y;
}

struct node {
	int d,id;
} a[N];
//我们要在保留a[i]的信息的同时记录原本的编号
//这样排序后，原编号不会丢失。
int n,b[N];
bool cmp(node x,node y) {
	return  x.d<y.d;//按照信息从小到大排序
}
int ans[N];
int maxx[N];
int maxxx=-0x3f3f3f3f;
int d[N];
signed main() {
	R(n);
	for(int i=1; i<=n+1; ++i) {
		R(a[i].d);
		a[i].id=i;
	}
	for(int i=1; i<=n; ++i) {
		R(b[i]);
	}
	sort(b+1,b+1+n);
	sort(a+1,a+2+n,cmp);
	for(int i=1; i<=n; ++i) {
		d[i]=a[i+1].d-b[i];
		maxx[i]=max(maxx[i-1],a[i].d-b[i]);
	}
	ans[a[n+1].id]=maxx[n];
	/*
	看这一组样例，如果拿掉7，那么答案就为maxx[n]
	3
	3 4 6 7
	2 4 6
	7的编号为a[n+1].id 
	所以ans[a[n+1].id] 
	*/
	maxxx=d[n];
	//maxxx表示d数组后缀最大值 
	for(int i=n; i>=1; --i) {//枚举拿走排序后的a[i] 
		//拿走第i个之后，前i-1个不变，所以是maxx[i-1]
		//拿走第i个后，差的最大值可能在后面，所以max(maxxx,maxx[i-1]) 
		ans[a[i].id]=max(maxxx,maxx[i-1]);
		maxxx=max(maxxx,d[i-1]);//更新maxxx 
	}
	for(int i=1; i<=n+1; ++i) {
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：rexmqy (赞：0)

## 思路：

这个题目考虑用贪心来做，推一下公式：$\max\{a\ −\ b,\ 0\}$，为了使这个数字更小，让奇怪度最大值最小化，所以可以将 $a$ 数组和 $b$ 数组排序，这样可以使两个数字的差更小，先把的 $n+1$ 个人的最大值算出来，然后后面的人每次都和前面的比较算出最大的奇怪度，最后输出每次除去 $a_k$ 的奇怪度最大值的最小化。

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int ma[N];
struct node
{
	int id;//存储编号
	int val;//存储的值
}a[N],b[N];
bool cmp(node x,node y)//排序函数
{
	return x.val<y.val;//按照值的大小排序
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n+1;i++)
	{
		cin>>a[i].val;
		a[i].id=i;//记录编号
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i].val;
	}
	sort(a+1,a+2+n,cmp);//排序
	sort(b+1,b+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		ma[a[n+1].id]=max(a[i].val-b[i].val,ma[a[n+1].id]);
	}
	for(int i=n;i;i--)
	{
		ma[a[i].id]=max(ma[a[i+1].id],a[i+1].val-b[i].val);//求奇怪度最大值最小化
	}
	for(int i=1;i<=n+1;i++)
	{
		cout<<ma[i]<<' ';
	}
	return 0;
}
```

本蒟蒻的第一篇题解，求管理员通过。

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_joi2020ho_a)

### $\texttt{Description}$

一共有 $n$ 个人，第 $i$ 个人的初始值是 $b_i$，并且第 $i$ 个人可以在 $a$ 数组选一个 $a_j$ 且两个不同的人不能够选相同的 $a_j$，选完之后就会产生一个为 $\max(a_j-b_i,0)$ 的值。现在问对于每一个 $a_j$，每个人把它拿走会产生的最大值最小是多少。

### $\texttt{Solution}$

一开始看到要求最小值，想到了二分，但是好像没有单调性，于是果断放弃这个想法。

这题的正解应该是贪心。我们需要将答案最大值最小化，也就是将每一个 $a_j-b_i$ 最小化，那我们就可以将 $a$ 数组和 $b$ 数组进行排序，让每个差值最小化。但是因为要按照输入顺序输出答案，所以我们需要用到结构体或者 $\texttt{pair}$ 维护下标，并且还需要开一个数组来存储答案。

注意结构体数组 $a$ 的长度是 $n+1$。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int, int> Pair;

const int N = 1e6 + 5;
Pair a[N], b[N];
// first 储存值，second 储存下标
int n, ans[N];

bool cmp(const Pair &q, const Pair &h) {
	return q.first < h.first;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	
	for (int i = 1; i <= n + 1; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	
	for (int i = 1; i <= n; i++) {
		cin >> b[i].first;
		// b 无需储存下标
	}
	
	sort(a + 1, a + n + 2, cmp); // 注意，是 a + n + 2
	sort(b + 1, b + n + 1, cmp);
	
	for (int i = 1; i <= n; i++) ans[a[n + 1].second] = max(a[i].first - b[i].first, ans[a[n + 1].second]);
	
	// 更新最大值
	
	int pos = n;
	while (pos) ans[a[pos].second] = max(a[pos + 1].first - b[pos].first, ans[a[pos + 1].second]), pos--;
	for (int i = 1; i <= n + 1; i++) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：Double_Light (赞：0)

首先考虑 $a$ 与 $b$ 长度都为 $n$，不从 $a$ 中取数的情况。

容易想到贪心：将 $a$ 与 $b$ 从小到大排序，最后 $a_i$ 对应 $b_i$。

那么考虑 $a$ 的长度为 $n+1$ 的情况。

根据上面的贪心策略，$a_i$ 对应的只能是 $b_i$ 或 $b_{i-1}$（也就是 $a_{1\sim i-1}$ 没有被拿走和 $a_{1\sim i-1}$ 中被拿走了一个数的情况），所以可以直接考虑维护两个数组 $f$ 和 $g$，表示 $a_i$ 对应 $b_i$ 和 $a_{i+1}$ 对应 $b_i$ 的最大值，然后再维护 $f$ 的前缀最大值和 $g$ 的后缀最大值。

对于每次询问拿走 $a_k$，答案为 $\max(\textmd{maxf}_{i-1},\textmd{maxg}_{i})$。

注意答案必须要排序排回来。

**以下代码中 $a$ 数组对应上文的 $b$，$b$ 数组对应上文的 $a$**。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int a[200005];
struct node{
	int x,id,ans;
}b[200005];
int lmx[200005],yhb[200005];
int maxlmx[200005],maxyhb[200005];
bool cmp(node x,node y){
	return x.x<y.x;
}
bool cmp2(node x,node y){
	return x.id<y.id;
}
int main(){
	cin>>n;
	for(int i=1;i<=n+1;i++){
		cin>>b[i].x;
		b[i].id=i;
	}
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+2,cmp);
	for(int i=1;i<=n;i++){
		lmx[i]=max(0,b[i].x-a[i]);
		yhb[i]=max(0,b[i+1].x-a[i]);
	}
	for(int i=1;i<=n;i++)maxlmx[i]=max(maxlmx[i-1],lmx[i]);
	for(int i=n;i>=1;i--)maxyhb[i]=max(maxyhb[i+1],yhb[i]);
	for(int i=1;i<=n+1;i++){
		b[i].ans=max(maxlmx[i-1],maxyhb[i]);
	}
	sort(b+1,b+n+2,cmp2);
	for(int i=1;i<=n+1;i++)cout<<b[i].ans<<' ';
	cout<<endl;
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

模拟赛上考了这个题，场切了（~~那肯定的~~），来补一下题解。

首先考虑一个多项式复杂度算法。发现若将 $A$ 和 $B$ 两个数组都从小到大匹配之后小的匹配小的大的匹配大的最优秀，正确性：令 $A$ 中元素为 $a_0,a_1$（$a_0<a_1$）$B$ 中元素为 $b_0,b_1$（$b_0<b_1$）那么若按照顺序的话贡献为 $\max(a_0-b_0,0)+\max(a_1-b_1,0)$，如果交换顺序的话贡献为 $\max(a_1-b_0,0)+\max(a_0-b_1,0)$。简单分类讨论大小关系即可证明。具体不写了。

但是问题是每一次都需要从 $A$ 中删除一个数，一共执行 $n$ 次操作那么时间复杂度就是 $O(n^2\log n)$ 的。可以发现排序的操作大多都是重复的，因此考虑优化排序的过程。容易发现若一开始将 $A$ 数组排序，那么删除 $A$ 中一个元素之后 $A$ 剩下的一定是一个排序完了的前缀 $Pre$ 和一个排序完了的后缀 $Suf$，并且满足 $|Pre|+|Suf|=|B|=|A|-1$。因此考虑处理出前缀的权值 $f_i$ 表示 $A$ 中的 $1\sim i$ 配对 $B$ 中的 $1\sim i$ 所需要的花费最小多少，后缀权值 $g_i$ 表示 $A$ 中 $i+1\sim n+1$ 和 $B$ 中 $i\sim n$ 配对最小的花费是多少。若删除的元素在 $A$ 中对应位置为 $p$，那么可以直接计算出答案为 $\max(f_p,g_{p+1})$ 排序的时候记录一下原来是第几个元素即可。容易发现 $f$ 和 $g$ 都可以在线性时间复杂度内一遍扫描预处理出。因此这个题目就做完了，时间复杂度为 $O(n\log n)$，瓶颈在于排序。若采用基数排序则时间复杂度为 $O(n)$。

具体见 $O(n\log n)$ 实现的赛时代码：

```cpp
int n;cin>>n;
F(i,1,n+1)cin>>b[i].x,b[i].id=i;
F(i,1,n)cin>>a[i];
sort(a+1,a+n+1);
sort(b+1,b+n+2);
F(i,1,n)
  pref[i]=max(pref[i-1],max(0ll,b[i].x-a[i]));
G(i,n,1)
  suff[i]=max(suff[i+1],max(0ll,b[i+1].x-a[i]));
F(i,1,n+1)
  res[b[i].id]=max(pref[i-1],suff[i]);
F(i,1,n+1)cout<<res[i]<<' ';
cout<<'\n';
```

附录 $O(n^2\log n)$ 暴力代码：

```cpp
int n;cin>>n;
F(i,1,n+1)cin>>b[i].x,b[i].id=i;
F(i,1,n)cin>>a[i];
sort(a+1,a+n+1);
sort(b+1,b+n+2);
F(i,1,n+1){
  int cnt=0;
  F(j,1,i-1)
    cnt=max(cnt,max(0ll,b[j].x-a[j]));
  F(j,i,n)
    cnt=max(cnt,max(0ll,b[j+1].x-a[j]));
  res[b[i].id]=cnt;
}
F(i,1,n+1)cout<<res[i]<<' ';
cout<<'\n';
```

---

## 作者：Wan__Ye__Chu (赞：0)

## 题目大意
一共有 $n$ 个人有一个长度为 $N+1$ 的数组 $a$ 和 长度为 $N$ 的数组 $b$，第 $i$ 个人的初始值为 $b_i$。 第 $i$ 个人可以选一个 $a_j$（任意两个人不能选相同的 $ a_j $）选完之后可以产生一个 $\max(0,a_j-b_i)$ 的值。

现在有 $ N+1$ 的询问，对于第 $k$ 次询问，若拿走 $a_k$ 问每个人产生的值中的最大值最小是多少？

## 思路

一道很好的贪心。首先我们先排序，排序后可以发现，取最大的 $b_j$ 和最大的 $a_i$ 配对一定是最优的，同理，取最小的 $b_j$ 和 最小的 $a_i$ 配对也一定是最优的。

然后，我们可以吧我们拿掉一个数的数组 $ a $ 看成两个区间，答案就是这两个区间的最大值，然后维护一下就可以了。

## 参考代码
（看到题解区的 dalao 都用了结构体，我就来写一个没有用结构体的帕）

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,a[1114514],b[1114514],c[1114514],d[1114514],QAQ[1114514];


int main()
{
	ios::sync_with_stdio(0);//取消cin cout 同步流，可以加快代码运行速度
	cin>>n;
	for(int i=1;i<=n+1;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	sort(a+1,a+n+2);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		c[i]=max(c[i-1],a[i]-b[i]);
		d[n-i+1]=max(d[n-i+2],a[n-i+2]-b[n-i+1]);	
	}
	for(int i=1;i<=n+1;i++)
	{
		int qwq=max(c[i-1],d[i]);
		QAQ[i]=max(qwq,0);
	}
	for(int i=1;i<=n+1;i++)
		cout<<QAQ[i]<<" ";
	return 0;
}
```
记得点个赞哦 qvq 。

---

## 作者：WZWZWZWY (赞：0)

给出数组 $a$ 和数组 $b$，如何求最小的 $\max\{a-b,0\}$ 和，也就是使数组的元素两两相减的和最小呢？

根据我们做题的经验，要使从小到大排序后的两个数组两两相减的结果最小，结果一定是每个下标相同的 $(a_i-b_i)$ 的和。


------------

### 证明

（借鉴了[别人的题解](https://www.luogu.com.cn/blog/166078/p6877-post)的方法 QWQ）：

使 $i < j$，那么 $a_i\le a_j$，$b_i\le b_j$。

∴ $a_i-b_j\le a_j-b_j\le a_j-b_i$。

所以 $\max\{a_i-b_j,a_j-b_i\}=a_j-b_i$。

$a_i-b_i\le a_j-b_i$，所以最小值为 $a_i-b_i$ 而不是 $a_j-b_i$。


------------

咳咳，接下来的有种清晰的**思路**：

1. 先**排序**。

2. 假设被拿走的那个帽子从来就没有过，那么接下来只要使剩下的人与领结**对应地结合**即可（因为数量相同了）。

排序好说，对于每次拿走帽子，如何快速求出结果呢？

由于排好序了，若拿走 $a$ 数组中的一个值，那么它后面的每一位都要往前挪一步来补了这个缺口，这样两个数组刚好数量和位置都对应了。

那么预处理用 $pre$ 数组记录 $(a_i-b_i)$ 的前缀最大值与 $nxt$ 数组记录 $(a_{i+1}-b_i)$ 的后缀最大值，结果就是 $\max\{pre["i"-1],nxt["i"]\}$。


然后就结束了。

真的结束了吗？其实还差一点。你发现“$i$”打了引号，为什么呢？

因为我们排序过了，但是，题目问的可不是你排序后的数组顺序啊……所以还要加个结构体记录之前的顺序。

```
#include <iostream>
#include <algorithm>
using namespace std;
struct stu {
	int va, id;
} a[200005];
int b[200005], pre[200005], nxt[200005], co[200005], n;
bool cmp(stu a, stu b) {
	return a.va < b.va;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n + 1; i++) {
		cin >> a[i].va; a[i].id = i;
	}
	for (int i = 1; i <= n; i++) cin >> b[i];
	sort (a + 1, a + 2 + n, cmp);
	sort (b + 1, b + 1 + n);
	for (int i = 1; i <= n; i++) 
		pre[i] = max(pre[i - 1], a[i].va - b[i]);
	for (int i = n; i >= 1; i--) 
		nxt[i] = max(nxt[i + 1], a[i + 1].va - b[i]);
	for (int i = 1; i <= n + 1; i++) co[a[i].id] = i;
	for (int i = 1; i <= n + 1; i++) cout << max(pre[co[i] - 1], nxt[co[i]]) << " ";
	
} 
```

还有什么问题可以在评论区留言哦。

---

## 作者：chl090410 (赞：0)

## The Solution to AT_joi2020ho_a 長いだけのネクタイ (Just Long Neckties)

### 题目大意

一共有 $N$ 个人，有一个长度为 $N+1$ 的数组 $a$ 和一个长度为 $N$ 的数组 $b$，第 $i$ 个人的初始值是 $b_i$。第 $i$ 个人可以选一个 $a_j$（任意两个人不能选相同的 $a_j$ ）选完后会产生一个 $\max(a_j-b_i,0)$ 的值。

现在有 $N+1$ 次询问，对于第 $k$ 次询问，若拿走 $a_k$ 问每个人产生的值中的最大值最小是多少？

### 分析

设 $a$ 数组中有元素 $a,b$，$b$ 数组中有元素 $c,d$，满足 $a>b,c>d$。

若 $a$ 对应 $c$，$b$ 对应 $d$，则产生的值中的最大值为 $\max(a-c,b-d,0)$。

若 $a$ 对应 $d$，$b$ 对应 $c$，则产生的值中的最大值为 $\max(a-d,b-c,0)$。

因为 $a>b$，所以 $a-d>b-d$，因为 $d<c$，所以 $a-d>a-c$。

于是就有 $\max(a-d,0)\ge \max(a-c,b-d,0)$，而要求产生的值中的最大值的最小值，所以第一种办法肯定更优。

类似的，我们可以推导多个元素的最优解的求法：先将两个数组排序，然后依次求出各个位置的元素的差，再求最大值即可。

直接暴力枚举是 $O(N^2)$ 的，会超时。我们只需先将 $a$ 数组中各个元素与 $b$ 数组对应元素及其前一位元素的差值先求出，再遍历 $a$ 数组，求出最大值，就可以将时间复杂度降到 $O(N)$。

### Accode 如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,b[200005],s[200005],k[200005],p,l,x;
struct node{
	int sz,yw;
}a[200005];
bool cmp(node a,node b){
	return a.sz<b.sz;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n+1;i++){
		cin>>a[i].sz;
		a[i].yw=i;
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	sort(a+1,a+n+2,cmp);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		a[i].sz=max(l,a[i].sz-b[i]);
		k[i]=max(l,a[i+1].sz-b[i]);
	}
	for(int i=1;i<=n;i++){
		x=max(a[i].sz,x);
		a[i].sz=x;
	}
	x=0;
	a[0].sz=-1;
	k[n+1]=-1;
	for(int i=n;i>=1;i--){
		x=max(k[i],x);
		k[i]=x;
	}
	for(int i=1;i<=n+1;i++){
		s[a[i].yw]=max(a[i-1].sz,k[i]);
	}
	for(int i=1;i<=n+1;i++){
		cout<<s[i]<<" ";
	}
	return 0;
}

---

## 作者：rainygame (赞：0)

比较平凡的一道题。

首先可以发现一个简单的性质，取最大的 $A_i$ 和最大的 $B_j$ 配一定是最优的，同理，取最小的 $A_i$ 和最小的 $B_j$ 配也一定是最优的。这样我们可以先对 $A$ 和 $B$ 排序处理。

排序之后，我们可以发现，在有序的 $A$ 里面相邻地换“空位”，只会影响一个人的产生的值，所以问题转化为：

给定一些数，需要满足一些询问：

- 把其中一个 $x$ 改为 $y$。
- 求这些数最大值。

这可以用 `multiset` 维护，将 $x$ 删除并添加一个 $y$ 即可，注意 `multiset` 的删除方式。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200002

int n, now;
int b[MAXN], ans[MAXN];
multiset<int, greater<int>> st;

struct Node{
    int ind, val;
}a[MAXN];

bool cmp(Node a, Node b){
    return a.val < b.val;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<=n+1; ++i){
        cin >> a[i].val;
        a[i].ind = i;
    }
    for (int i(1); i<=n; ++i) cin >> b[i];
    sort(a+1, a+n+2, cmp);
    sort(b+1, b+n+1);

    for (int i(1); i<=n; ++i) st.insert(max(a[i+1].val-b[i], 0ll));
    ans[a[1].ind] = *st.begin();
    for (int i(2); i<=n+1; ++i){
        st.insert(max(a[i-1].val-b[i-1], 0ll));
        st.erase(st.find(max(a[i].val-b[i-1], 0ll)));
        ans[a[i].ind] = *st.begin();
    }
    for (int i(1); i<=n+1; ++i) cout << ans[i] << ' ';

    return 0;
}

```


---

## 作者：IkunTeddy (赞：0)

# 题目大意
一共有 $N$ 个人，有一个长度为 $N+1$ 的数组 $a$ 和一个长度为 $N$ 的数组 $b$，第 $i$ 个人的初始值是 $b_i$。第 $i$ 个人可以选一个 $a_j$（任意两个人不能选相同的 $a_j$）选完后会产生一个 $\max(a_j-b_i ,0)$ 的值。

现在有 $N+1$ 次询问，对于第 $k$ 次询问，若拿走 $a_k$ 问每个人产生的值中的最大值最小是多少？
# 题目分析
组合优化类问题，要么选 dp 要么选贪心。这个题如果选 dp 状态转移方程明显不好写，那么考虑贪心。

现在考虑贪心策略，是不是只要满足对于每个 $b_i$ 他所选的 $a_j$ 都比他大，或者是所有 $a_j$ 中比他小的最少的，答案就一定是最优的。**这里可以好好想一下**。

现在只要将两个数组排序一下就可以求答案了，现在再来思考一下每次询问会对答案有什么影响，如果拿掉了一个数，是不是就将整个 $a$ 分成了两个区间，答案就是两个区间的最大值，即 $ans=\max(mx_l,mx_r)$。这个问题很典型，直接维护一下前缀最大值和后缀最大值然后 $O(1)$ 求就行了。

# Code
如果要用名称为 $next$ 的数组的话必须要打一个自定义的 namespace，不然的话本地跑不会出问题，但提交会 CE。就像我下面一样
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
namespace buyaochaotijie{
	const int maxn=2e5+10;
	struct Id{
		int v,id;
	}a[maxn];
	bool cmp(Id a,Id b){
		return a.v<b.v;
	}
	int b[maxn];
	int pre[maxn],next[maxn];
	int ans[maxn];
	int main(){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n+1;i++){
			scanf("%d",&a[i].v);
			a[i].id=i;
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
		}
		sort(a+1,a+2+n,cmp);
		sort(b+1,b+1+n);
		for(int i=1;i<=n;i++){
			int j=n-i+1;
			pre[i]=max(pre[i-1],a[i].v-b[i]);
			next[j]=max(next[j+1],a[j+1].v-b[j]);
		}
		for(int i=1;i<=n+1;i++){
			ans[a[i].id]=max(pre[i-1],next[i]);
		}
		for(int i=1;i<=n+1;i++)printf("%d ",max(0,ans[i]));
	
		return 0;
	}
}
int main(){
	buyaochaotijie::main();
	return 0;
}



```


---

