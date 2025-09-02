# [ABC393F] Prefix LIS Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc393/tasks/abc393_f

给定一个长度为 $ N $ 的整数序列 $ A=(A_1,A_2,\dots,A_N) $。

请处理 $ Q $ 个查询。第 $ i\ (1 \leq i \leq Q) $ 个查询如下：

- 给定整数 $ R_i $ 和 $ X_i $。求数列 $ (A_1,A_2,\dots,A_{R_i}) $ 的（不一定连续的）子序列中，满足严格单调递增且所有元素不超过 $ X_i $ 的最长长度。保证 $ X_i \geq \min\{ A_1, A_2, \dots, A_{R_i} \} $。

## 说明/提示

### 约束条件

- $ 1 \leq N, Q \leq 2 \times 10^5 $
- $ 1 \leq A_i \leq 10^9 $
- $ 1 \leq R_i \leq N $
- $ \min\{ A_1, A_2, \dots, A_{R_i} \} \leq X_i \leq 10^9 $
- 输入中所有值均为整数

### 样例解释 1

- **第 1 个查询**：数列 $ (2,4) $ 中严格单调递增且所有元素不超过 $ 5 $ 的最长子序列长度为 $ 2 $。具体来说，子序列 $ (2,4) $ 满足条件。
- **第 2 个查询**：数列 $ (2,4,1,3,3) $ 中严格单调递增且所有元素不超过 $ 2 $ 的最长子序列长度为 $ 1 $。具体来说，子序列 $ (2) $ 或 $ (1) $ 满足条件。
- **第 3 个查询**：数列 $ (2,4,1,3,3) $ 中严格单调递增且所有元素不超过 $ 3 $ 的最长子序列长度为 $ 2 $。具体来说，子序列 $ (2,3) $ 或 $ (1,3) $ 满足条件。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5 3
2 4 1 3 3
2 5
5 2
5 3```

### 输出

```
2
1
2```

## 样例 #2

### 输入

```
10 8
2 5 6 5 2 1 7 9 7 2
7 8
5 2
2 3
2 6
7 3
8 9
9 6
8 7```

### 输出

```
4
1
1
2
1
5
3
4```

# 题解

## 作者：Moya_Rao (赞：8)

# 前言

第一次场切 F，当然得写篇题解纪念下啦！

话说我打比赛那会儿用了四十多分钟才干掉 D 题，看了眼 E 发现自己毫无头绪，一时好奇看了一眼 F，结果思路就直接出来了！当时只剩下不到半个小时，我敲代码的时候非常紧张，生怕写不完。其实上完全不用担心，代码又不长，顶多用了十分钟就写完了，测完样例提交便直接 AC 了。激动万分，这可是我第一次赛时做出 F 啊！

好啦，废话也唠嗑了这么多了，接下来开始讲解题目吧。

# 题目大意

给定一个长度为 $n$ 的正整数序列 $a$。

现在有 $m$ 组询问，每组询问给定两个参数 $R$ 和 $X$，表示需要算出 $a$ 的前 $R$ 项组成的最长上升子序列的最长长度。不过有一个限制，就是这个最长上升子序列中的最大值不能超过 $X$。  
请对于每组询问，求出这个最长上升子序列的最长长度并依次输出。

$1 \le n,m \le 2 \times 10^5$，$1 \le a_i \le 10^9$。  
$1 \le R \le n$，$\min\{a_1,a_2,\dots,a_R\} \le X \le 10^9$。

# 思路

首先看到题目中的“最长上升子序列”，立马就会想到求解最长上升子序列长度的方法。又看到数据范围不支持进行 $O(n^2)$ 的操作，因此当然是使用[此题](https://www.luogu.com.cn/problem/P1020)中出现过的 $O(n \log{n})$ 法求最长上升子序列的长度啦。  
如果你不会，请先左转学习如何在 $O(n \log{n})$ 的时间内求出最长上升子序列的长度。  
不过这里需要强调一点，这种方法里用到的一个 $k$ 数组，它的第 $i$ 位表示的是长度为 $i$ 的最长上升子序列中最后一个数值最小能是多少，可万万不要误解了它的意思哟，因为它在接下来的解题步骤中有着不小的帮助！具体是什么帮助呢，嘿嘿，你就接着看吧，现在我不告诉你！

那么接下来呢？看一下每组询问的要求，对，每组询问都只需要求出 $a$ 数组中的前 $R$ 项所组成的那个最长上升子序列的长度。可是最普通的办法只能求出整个 $a$ 数组的最长上升子序列的长度啊。  
这可怎么办啊？其实上很简单啦，我们回想一下求解最长上升子序列长度时的步骤，我们是一个一个把数值放进去的，也就是说，在放完第 $R$ 个数并且还没有开始放第 $R+1$ 个数的时候来回答这个询问就对啦。

这时你可能会有些疑惑：这个我懂，但是对于这道题目又有什么用呢？总不至于每组询问都求一次吧，那样时间复杂度绝对不行的啊。  
对对对，你说的对，于是接下来我们要用到的法宝就是——离线操作！我们将每组询问都存下来，放进一个结构体数组 $q$ 里边，记得存下编号。接着按照 $R$ 排个序，正常求一遍最长上升子序列，顺便弄一个指针 $now$ 从 $1$ 开始遍历每组询问。每当放完第 $i$ 个数值，就看看从 $now$ 的位置开始，有没有一段询问给出的 $R = i$，如果有的话，直接把当前求出来的答案给到这些询问并同时修改 $now$ 的值。最后我们把 $q$ 再按照编号还原，将答案依次输出就好啦！

做完了吗？当然没有！大家肯定都注意到了：题目中的每组询问都还有一个 $X$ 的限制！  
这个限制该怎么解决呢？很简单，还记得之前提到的那个 $k$ 数组吗？对，就是我还特意强调了定义的那个，现在它要派上用场啦！我们可以修改代码中直接将 $k$ 数组的长度给到答案的那一部分，改为在 $k$ 数组中寻找最后一个位置 $d$ 使得 $k_d \le X$，给答案 $d$ 就好啦。  
为什么要这么干？回想一下它的定义看看，想明白了吗？对，就是找到那个最大值，最大值必须不超过 $X$，然后我们又希望这个子序列的长度是越长越好，所以我们要找到的那个位置要尽量靠后，而这个数组一定是严格上升的，所以满足二分所需的单调性，就可以解决了。

思路都叙述完毕了，现在我们来分析一下它的时间复杂度，输入输出的线性时间不用在乎，给所有询问排序两次（前面有一次按照 $R$ 升序的，后面还有一次按照编号还原）需要 $O(m \log{m})$（不管常数），求最长上升子序列又需要 $O(n \log{n})$，二分算答案那一部分还需要 $O(m \log{n})$。由于 $n$ 和 $m$ 是同阶级的，所以总时间复杂度可以看作 $O(n \log{n})$，跑得还挺快呢。

# [AC](https://atcoder.jp/contests/abc393/submissions/62839873) 代码

这份代码是我将赛时的那份 AC 代码拿来，删掉根本没用上的快读后的结果。代码应该比较好理解，因此我就没有添加注释了，结合着思路一起看看吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
struct node{int id,r,x,ans;}q[N];
int n,m,a[N],k[N],len;
bool cmp1(node d1,node d2){return d1.r<d2.r;}
bool cmp2(node d1,node d2){return d1.id<d2.id;}
int Find(int num){
    int l=1,r=len,as=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(num<=k[mid])as=mid,r=mid-1;
        else l=mid+1;
    }
    return as;
}
int KanKan(int num){
    int l=1,r=len,as=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(num>=k[mid])as=mid,l=mid+1;
        else r=mid-1;
    }
    return as;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        cin>>q[i].r>>q[i].x;q[i].id=i;
    }
    sort(q+1,q+m+1,cmp1);
    int now=1;
    for(int i=1;i<=n;i++){
        if(a[i]>k[len])k[++len]=a[i];
        else k[Find(a[i])]=a[i];
        while(now<=m&&q[now].r==i){
            q[now].ans=KanKan(q[now].x);now++;
        }
    }
    sort(q+1,q+m+1,cmp2);
    for(int i=1;i<=m;i++)cout<<q[i].ans<<"\n";
    return 0;
}
```

如果本篇题解对你有帮助，请你留下一个小小的赞，谢谢啦！

---

## 作者：Lovely_yhb (赞：5)

### 题意

给定一个长度为 $n$ 的序列 $a$。

有 $q$ 次询问，每次询问 $r$ 和 $x$ 求前 $r$ 个数中每个数都小于等于 $x$ 的最长上升子序列的长度。

### 思路

把询问按 $r$ 从小到大排序，这样只需要逐渐向后拓展即可。

设 $f_i$ 表示以长度为 $i$ 的上升子序列结尾的最小值。答案是所有满足 $f_k\le x$ 的 $k$ 的最大值。

发现同一时刻，$f$ 是单调不降的，所以查询可以二分，在 $f$ 中查找第一个大于 $x$ 的位置。

向后拓展 $a_i$ 的时候，二分查找 $f$ 中第一个大于等于 $a_i$ 的位置，把这个位置变成 $a_i$。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct node {int r,x,id,ans;} q[N];
bool cmp(node a,node b) {return a.r<b.r;}
bool cmp1(node a,node b) {return a.id<b.id;}
int n,Q,a[N],qi=1;
int main() {
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>Q;
	for (int i=1; i<=n; i++) cin>>a[i];
	for (int i=1; i<=Q; i++) cin>>q[i].r>>q[i].x,q[i].id=i;
	sort(q+1,q+Q+1,cmp);
	vector<int> f;
	f.push_back(0);
	for(int i=1; i<=n; i++) {
		auto it=lower_bound(f.begin(),f.end(),a[i]);
		if(it==f.end()) f.push_back(a[i]);
		else *it=a[i];
		while(qi<=Q&&q[qi].r==i) {
			q[qi].ans=upper_bound(f.begin(), f.end(), q[qi].x)-f.begin()-1;
			qi++;
		}
	}
	sort(q+1,q+Q+1,cmp1);
	for(int i=1;i<=Q;i++) cout<<q[i].ans<<endl;
	return 0;
}
```

---

## 作者：dingxiongyue (赞：2)

# 题解：AT_abc393_f [ABC393] F - Prefix LIS Query  

## Description：
给定一个长度为 $N$ 的序列 $A$，你需要回答 $Q$ 次形如 $R_i$，$X_i$ 的询问，答案为前 $R_i$ 个元素的中不超过 $X_i$ 的最长上升子序列的长度。  

即**离线LIS**。  

## Analysis：
将所有询问存储下来，在正常处理最长上升子序列的同时维护答案。  

遍历所有元素，若在动态数组 $f$ 中有第一个大于等于 $A_i$ 的值，则将该位置改为 $A_i$，否则将 $A_i$ 放入 $f$ 尾部。同时遍历 $R_i = i$ 的询问，$f$ 中第一个大于 $X_i$ 的位置的下标即为答案。  

详见代码。  

时间复杂度 $O(N \log N + Q)$。

## Code：
[AC记录](https://www.luogu.com.cn/record/204019789)  
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
typedef std::pair<int, int> PII;
const int N = 2e5 + 10;
int n, m;
int _r, _x;
int a[N];
int ans[N];
std::vector<int> f;
std::vector<PII> r[N];
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) 
		a[i] = read();
	for (int i = 1; i <= m; i++) {
		_r = read(), _x = read();
		r[_r].push_back({_x, i});
	}
	for (int i = 1; i <= n; i++) {
		auto it = lower_bound(f.begin(), f.end(), a[i]);
		if (it == f.end()) f.push_back(a[i]);
		else *it = a[i];
		for (int j = 0; j < r[i].size(); j++) {
			int R = r[i][j].first, id = r[i][j].second;
			auto t = upper_bound(f.begin(), f.end(), R);
			ans[id] = t - f.begin();
		} 
	}
	for (int i = 1; i <= m; i++) 
		write(ans[i]), printf("\n");
	return 0;
}
```

---

## 作者：under_the_time (赞：1)

## 题意

> 给定一个长度为 $n$ 的序列 $a$，有 $Q$ 个询问，第 $i$ 个询问给定 $(r_i,x_i)$，对于所有 $a$ 中以 $r_i$ 结尾前缀的子序列，求长度最长的严格递增子序列满足子序列的每一项都 $\le x_i$。
>
> $1\le n,Q\le 2\times 10^5$，$1\le a_i\le 10^9$。

## 题解

先不考虑 $x_i$ 的限制，考虑把询问离线下来，对 $a$ 的每个前缀逐个处理。把 $a_i$ 进行离散化，建一颗线段树，线段树上区间 $[l,r]$ 记录值在 $[l,r]$ 中的所有点中，最大的以这个点为结尾的最长上升子序列长度。假设我们处理到以 $i$ 结尾的前缀，那么我们查询 $[1,a_i-1]$ 区间的答案，这个答案加一即为 $i$ 的答案，再插入到线段树上 $a_i$ 的位置。

现在有了 $x_i$，我们把 $x$ 和 $a$ 放在一起进行离散化，在线段树上考虑，我们查询 $[1,x_i]$ 中的答案即可。时间复杂度 $O(n\log n)$。

```cpp
// Problem: F - Prefix LIS Query
// Contest: AtCoder - AtCoder Beginner Contest 393
// URL: https://atcoder.jp/contests/abc393/tasks/abc393_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Good luck to the code >w<
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define abs(x) (((x) > (0)) ? (x) : (-(x)))
#define lowbit(x) ((x) & (-(x)))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define BCNT __builtin_popcount
#define cost_time (1e3 * clock() / CLOCKS_PER_SEC)
mt19937 rnd(time(0));
const int maxn = 4e5 + 5;
int n, Q, a[maxn]; pair<pair<int, int>, int> que[maxn];
int tmp[maxn];
int mx[maxn << 2];
void update(int rt) { mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]); }
int query(int l, int r, int rt, int nowl, int nowr) {
	if (nowl > nowr) return 0;
	if (nowl <= l && r <= nowr) return mx[rt];
	int mid = (l + r) >> 1, res = 0;
	if (nowl <= mid) res = max(res, query(lson, nowl, nowr));
	if (mid < nowr) res = max(res, query(rson, nowl, nowr));
	return res;
} void modify(int l, int r, int rt, int now, int k) {
	if (l == r) return mx[rt] = max(mx[rt], k), void(0);
	int mid = (l + r) >> 1;
	if (now <= mid) modify(lson, now, k);
	else modify(rson, now, k);
	update(rt);
} int Ans[maxn];
int main() {
	scanf("%d %d", &n, &Q); int m = 0;
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]), tmp[++ m] = a[i];
	for (int i = 1; i <= Q; i ++)
		scanf("%d %d", &que[i].first.first, &que[i].first.second), que[i].second = i, tmp[++ m] = que[i].first.second;
	sort(tmp + 1, tmp + m + 1), m = unique(tmp + 1, tmp + m + 1) - tmp - 1;
	for (int i = 1; i <= n; i ++) a[i] = lower_bound(tmp + 1, tmp + m + 1, a[i]) - tmp;
	for (int i = 1; i <= Q; i ++) que[i].first.second = lower_bound(tmp + 1, tmp + m + 1, que[i].first.second) - tmp;
	sort(que + 1, que + Q + 1);
	for (int i = 1, j = 1; i <= n && j <= Q; i ++) {
		int ans = query(1, 4e5, 1, 1, a[i] - 1) + 1;
		modify(1, 4e5, 1, a[i], ans);
		for (; que[j].first.first == i; j ++)
			Ans[que[j].second] = query(1, 4e5, 1, 1, que[j].first.second);
	} for (int i = 1; i <= Q; i ++)
		printf("%d\n", Ans[i]);
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

## 思路
一眼离线，先按 $R$ 给询问排序。你会发现由于求的是最长上升子序列（以下称 LIS），所以 LIS 中的每一个数都 $\le X$ 本质上就是它的最后一个数字 $\le X$。

考虑我们使用 $O(N\log N)$ 算法求一个长度为 $N$ 的序列 $A$ 的 LIS 的过程，$f_i$ 记录着长度为 $i$ 的 LIS 最后一个数最小可能是多少。诶？那么这个询问不就是在要求找出最大的 $i$ 使得 $f_i\le X$ 吗？我们知道 $f$ 是不降的，所以二分就行了。

离线处理，时间复杂度 $O(Q\log Q+(Q+N)\log N)$。
## 代码
### 纯净版求 LIS 代码（供参考）
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,a[300000],f[300000],ans;
int main(){
	memset(f,0x3f,sizeof(f)),f[0] = 0;
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
	for(int i = 1;i <= n;i ++){
		x = lower_bound(f + 1,f + n + 1,a[i]) - f - 1;//a_i 可以接在最长长 x 的序列后 
		f[x + 1] = min(f[x + 1],a[i]),ans = max(ans,x + 1);//接上后长度为 x+1 
	}
	printf("%d",ans);
	return 0;
}
```
### 本题代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
struct node{
	int r,x,w;
	bool friend operator < (const node &a,const node &b){
		return a.r < b.r;
	}
};
int n,q,a[300000],ans[300000],it = 1,f[300000],x;
node qry[300000];
int main(){
	memset(f,0x3f,sizeof(f)),f[0] = 0;
	scanf("%d%d",&n,&q);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
	for(int i = 1;i <= q;i ++) scanf("%d%d",&qry[i].r,&qry[i].x);
	for(int i = 1;i <= q;i ++) qry[i].w = i;
	sort(qry + 1,qry + q + 1);//按 R 排序 
	for(int i = 1;i <= n;i ++){
		x = lower_bound(f + 1,f + n + 1,a[i]) - f - 1; 
		f[x + 1] = min(f[x + 1],a[i]);//求 LIS 部分 
		while(qry[it].r == i){
			ans[qry[it].w] = upper_bound(f + 1,f + n + 1,qry[it].x) - f - 1;//二分找第一个 i 使 f_i<=X_it 
			it ++;
		}
	}
	for(int i = 1;i <= q;i ++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：SunburstFan (赞：1)

### F - Prefix LIS Query

#### 题目大意

给定一个长度为 $N$ 的序列，$Q$ 个查询，每个查询提供了两个整数 $R_i$ 和 $X_i$，要求在序列的前 $R_i$ 个元素中，找到一个递增的子序列，其元素值都不大于 $X_i$，并且求出这个子序列的最大长度。

#### 解题思路

**树状数组（Fenwick Tree）**和**离散化**。

1. 离散化。
2. 对于每个查询，需要求出在前 $R_i$ 个元素中，值不大于 $X_i$ 的递增子序列的最大长度。使用动态规划与树状数组：
   - 树状数组维护一个区间内的递增子序列长度信息。
   - 对于每个元素 `A[i]`，我们可以查询树状数组中小于 `A[i]` 的最大值，然后更新当前元素的递增子序列长度。
   - 使用树状数组进行更新和查询，使得每次查询的时间复杂度为 $O(\log N)$。
3. 按 $X_i$ 排序查询，并按升序依次处理查询。这样可以保证在处理每个查询时，所有小于等于 $X_i$ 的元素已经被处理过了。

#### 核心代码

```cpp
struct T{
    int n;
    vector<int> t;
    T(int _n):n(_n),t(n+1){}

    void u(int i,int v){
        for(;i<=n;i+=i&-i)
            t[i]=max(t[i],v);
    }
    int q(int i){
        int r=0;
        for(;i;i-=i&-i)
            r=max(r,t[i]);
        return r;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> a(n);

    for(int i = 0; i < n; i++) cin >> a[i];

    vector<int> c = a;
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    vector<int> d(n);
    T t1(c.size());
    for(int i = 0; i < n; i++){
        int p = lower_bound(c.begin(), c.end(), a[i]) - c.begin() + 1;
        d[i] = t1.q(p - 1) + 1;
        t1.u(p, d[i]);
    }

    vector<int> x(n);
    for(int i = 0; i < n; i++) x[i] = i;

    sort(x.begin(), x.end(), [&](int i, int j){ return a[i] < a[j]; });

    struct Q{ int x, r, i; };
    vector<Q> qs(q);
    for(int i = 0; i < q; i++){
        int r, x; cin >> r >> x;
        qs[i] = {x, r, i};
    }

    sort(qs.begin(), qs.end(), [](Q p, Q q){ return p.x < q.x; });

    T t2(n);
    vector<int> s(q);

    int j = 0;
    for(auto& z : qs){
        while(j < n && a[x[j]] <= z.x){
            t2.u(x[j] + 1, d[x[j]]);
            j++;
        }
        s[z.i] = t2.q(z.r);
    }

    for(int v : s) cout << v << '\n';

    return 0;
}
```

---

## 作者：szh_AK_all (赞：1)

有些典。

考虑计算 LIS 的方法。

这里用线段树或者是树状数组优化 dp 的方式求 LIS 比较合适。设 $f_i$ 表示在以位置 $i$ 结尾的最长递增子序列，那么对于每次询问，我们相当于是要找出满足 $i\le R$ 且 $a_i\le X$ 的最大 $f_i$，同样可以使用线段树计算，具体是将每个询问按照 $R$ 的值挂到对应的位置上，离线统计答案即可。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005], b[200005];
int c[200005], n, nn, q;

struct no {
	int ans, la;
	no(int aa = 0, int bb = 0) {
		ans = aa;
		la = bb;
	}
} t[200005 << 2];

void pushdown(int d) {
	if (t[d].la == 0)
		return;
	t[d * 2].ans = max(t[d * 2].ans, t[d].la), t[d * 2].la = max(t[d * 2].la, t[d].la);
	t[d * 2 + 1].ans = max(t[d * 2 + 1].ans, t[d].la), t[d * 2 + 1].la = max(t[d * 2 + 1].la, t[d].la);
	t[d].la = 0;
}

void bu(int d, int l, int r) {
	if (l == r) {
		t[d].ans = t[d].la = 0;
		return;
	}
	int mid = (l + r) / 2;
	bu(d * 2, l, mid);
	bu(d * 2 + 1, mid + 1, r);
	t[d].ans = max(t[d * 2].ans, t[d * 2 + 1].ans);
}

void add(int d, int l, int r, int ll, int rr, int z) {
	if (ll > rr)
		return;
	if (ll <= l && r <= rr) {
		t[d].ans = max(t[d].ans, z);
		t[d].la = max(t[d].la, z);
		return;
	}
	pushdown(d);
	int mid = (l + r) / 2;
	if (ll <= mid)
		add(d * 2, l, mid, ll, rr, z);
	if (rr > mid)
		add(d * 2 + 1, mid + 1, r, ll, rr, z);
	t[d].ans = max(t[d * 2].ans, t[d * 2 + 1].ans);
}

int ask(int d, int l, int r, int ll, int rr) {
	if (ll > rr)
		return 0;
	if (ll <= l && r <= rr)
		return t[d].ans;
	pushdown(d);
	int mid = (l + r) / 2, ans = 0;
	if (ll <= mid)
		ans = max(ans, ask(d * 2, l, mid, ll, rr));
	if (rr > mid)
		ans = max(ans, ask(d * 2 + 1, mid + 1, r, ll, rr));
	return ans;
}
int f[200005], da[200005];

struct node {
	int k, id;
	node(int aa = 0, int bb = 0) {
		k = aa;
		id = bb;
	}
};
vector<node>g[200005];

signed main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1);
	nn = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(b + 1, b + nn + 1, a[i]) - b;
	for (int i = 1; i <= q; i++) {
		int x, y;
		cin >> x >> y;
		int k = lower_bound(b + 1, b + nn + 1, y) - b;
		if (b[k] > y)
			k--;
		g[x].push_back(node(k, i));
	}
	bu(1, 1, n);
	for (int i = 1; i <= n; i++) {
		f[i] = ask(1, 1, n, 1, a[i] - 1) + 1;
		add(1, 1, n, a[i], nn, f[i]);
		for (node x : g[i]) {
			da[x.id] = ask(1, 1, n, 1, x.k);
		}
	}
	for (int i = 1; i <= q; i++)
		cout << da[i] << "\n";
}
```

---

## 作者：Tang_chao (赞：1)

## **[ABC393F] Prefix LIS Query 题解**

发现我的做法比标算长一倍就难绷（
### 题面

多次问询，每次只考虑前 $r$ 个数中小于等于 $x$ 的数，求最长严格上升子序列（LIS）长度。

---
### 解法

如果每次暴力重算 LIS。时间复杂度 $O(n^3)$ 或 $O(n^2 \log n)$。  
考虑优化上述暴力。肯定要找到各个问询的 LIS 的关系。

先解决问询中的 $r$。将问询按 $r$ 排序，结合游标回答即可。来看 $x$ 怎么处理。


考虑用二分查找的方式更新的 LIS，好证它的最大值最小。记它为 $qwq$。
 
> 可以发现 $qwq$ 的某个前缀子段 $pwp$ 也是当前相等长度中最大值最小的。  
> 感性证明：考虑忽视最后若干个数的添加操作。既然 $qwq$ 是最大值最小的，那么 $pwp$ 当然也是啦。
> 
> 同时有推论，最大值不超过特定值的最长 LIS 总有 $qwq$ 的某个前缀。  
> 感性证明：如果没有，由上一个性质可换成相等长度的 $qwq$ 的前缀，一定不劣。

~~事实上这里直接二分就是标算（）（）还是继续说我的不要脸做法。~~

把所有 $pwp$ 记录下来并操作一下即可。

具体地，定义一种点，记录前 $id$ 个数中，小于等于 $val$ 的数的 LIS 长度 $len$。对于所有 $qwq$ 的每个前缀子段，都有一个与其对应的点。

那么每个问询变成查询 $\max len_i (val_i \le x,id_i \le r)$。对应下图（样例）中一个左下角矩形的最大值。

这个就很经典了，用游标和树状数组即可维护。把点按 $val$ 排序，问询按 $x$ 排序，可以省掉离散化。

![pwp](https://cdn.luogu.com.cn/upload/image_hosting/638u8oet.png)

但是点太多啦，考虑优化。在加入一个数时，最多改变一个 $qwq$ 的前缀，而其余的都是之前记录过滴！所以只用记录这个改变了的点（即深紫色的点），共 $n$ 个。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200009
int n,m,len,a[N],qwq[N],bit[N],ans[N];

struct node{ int len,val,id; } p[N];
bool operator < (node a,node b){ return a.val < b.val; }
struct query{ int r,x,id; } q[N];
bool operator < (query a,query b){ return a.x < b.x; }

int lowbit(int x){ return x & -x; }
void upd(int x,int v){
	while(x <= n){
		bit[x] = max(v,bit[x]);
		x += lowbit(x);
	}
}
int cal(int x){
	int mx = 0;
	while(x){
		mx = max(mx,bit[x]);
		x -= lowbit(x);
	}
	return mx;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i <= n;i++) cin>>a[i];
	for(int i = 1;i <= m;i++) cin>>q[i].r>>q[i].x,q[i].id = i;
	
	for(int i = 1;i <= n;i++){
		if(a[i] > qwq[len]){
			qwq[++len] = a[i];
			p[i] = {len,a[i],i};
		}else{
			int pos = lower_bound(qwq + 1,qwq + len + 1,a[i]) - qwq;
			qwq[pos] = a[i];
			p[i] = {pos,a[i],i};
		}
	}
	sort(p + 1,p + n + 1);
	sort(q + 1,q + m + 1);
	
	int j = 1;
	for(int i = 1;i <= m;i++){
		while(p[j].val <= q[i].x && j <= n){
			upd(p[j].id,p[j].len);
			j++;
		}
		ans[q[i].id] = cal(q[i].r);
	}
	for(int i = 1;i <= m;i++) cout<<ans[i]<<"\n";
}
```

---

## 作者：Tairitempest (赞：1)

## [ABC399F] Prefix LIS Query

这个题目我们可以用线段树解决。值域很大达到了 $10^9$，所以需要离散化处理。

首先按照贪心结合二分的方法求出每个位置的最长上升子序列，用数组存储每个位置的最长上升子序列。

接下来处理询问：由于不需要强制在线，我们把所有的询问按 $R$ 值排序然后离线处理。对于前 $R_i$ 个值，用单点赋值结合区间最大值线段树来维护最大值不大于某个值的最长上升子序列，添加一个新的数值的时候，只需要把该数值位置的线段树值单点修改为原值和这个值的最长上升子序列的长度的最大值就可以了。对于一个 $X_i$ 最大值就是数值不超过 $X_i$ 的位置中最长的最长上升子序列的长度，调用对应的线段树值即可。

复杂度是 $O(N \log N+Q\log N)$，足以通过本题。
## Code
```cpp
// LUOGU_RID: 204043244
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,Q,a[200010],x[200010],res[200010],vallen;
ll cache[200010],tot;
struct Node{
	ll l,r,val;
} T[800010];
void build(ll l,ll r,ll id){
	T[id].l=l;T[id].r=r;
	if(l==r) return;
	else{
		ll mid=(r+l)/2;
		build(l,mid,id*2);
		build(mid+1,r,id*2+1);
	}
}
void modify(ll k,ll p,ll id){
	if(T[id].l==T[id].r){
		T[id].val=max(T[id].val,k);
	}else{
		ll mid=(T[id].l+T[id].r)/2;
		if(p<=mid) modify(k,p,id*2);
		if(mid<p) modify(k,p,id*2+1);
		T[id].val=max(T[id*2].val,T[id*2+1].val);
	}
}
ll check(ll l,ll r,ll id){
	if(l<=T[id].l&&T[id].r<=r) return T[id].val;
	else{
		ll mid=(T[id].r+T[id].l)/2,ans=0;
		if(l<=mid) ans=max(ans,check(l,r,id*2));
		if(mid<r) ans=max(ans,check(l,r,id*2+1));
		return ans;
	}
}

struct question{
	ll r,x,id,ans;
} q[200010];

bool comp1(question A,question B){
	return A.r<B.r;
}

bool comp2(question A,question B){
	return A.id<B.id;
}

ll findpos(ll val){
	ll l=1,r=vallen; 
	while(l<r){
		ll mid=(l+r+1)/2;
		if(x[mid]>val)  r=mid-1;
		else l=mid;
	}
	return l;
}

int main(){
	cin>>n>>Q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		x[i]=a[i];
		if(tot==0||a[i]>cache[tot-1]){
			cache[tot]=a[i];
			res[i]=++tot;
		}else{
			ll l=0,r=tot-1; 
			while(l<r){
				ll mid=(l+r)/2;
				if(cache[mid]>=a[i])  r=mid;
				else l=mid+1;
			}
			if(cache[l]>a[i]) cache[l]=a[i];
			res[i]=l+1;
		}
	}
	sort(x+1,x+n+1);
	vallen=unique(x+1,x+n+1)-x-1;
	build(1,vallen,1);
	for(int i=1;i<=Q;i++){
		cin>>q[i].r>>q[i].x;
		q[i].id=i;
	}
	ll pos=1;
	sort(q+1,q+Q+1,comp1);
	for(int i=1;i<=n;i++){
		modify(res[i],findpos(a[i]),1);
		while(q[pos].r<=i&&pos<=Q){
			q[pos].ans=check(1,findpos(q[pos].x),1);
			pos++;
		}
	}
	sort(q+1,q+Q+1,comp2);
	for(int i=1;i<=Q;i++) cout<<q[i].ans<<endl;
	
	return 0;
}
```

---

## 作者：zengziqvan (赞：0)

将询问离线，在每个位置 $i$ 记录所有 $R_j =i$ 的查询。

设 $f_i$ 表示以 **值** $i$ 结尾的最长上升子序列长度。

从前往后扫描序列，假设扫到位置 $i$。

则当前 $f_{a_i}\gets \min_{1\le j\le a_i} f_j  +1$．

注意到此时我们只处理了 $\le i$ 的位置，所以对于询问 $Q_j\; R_j=i$ 可以直接查询 $\max_{1\le k\le Q_j}f_k$ 并保存答案。

问题在于怎么快速更新 $f$ 数组。

注意到单点修改，前缀查询且 **每个位置上更新的值单调不降**，所以可以使用树状数组维护。

复杂度 $O(n\log n)$，需要离散化。

[submissions](https://atcoder.jp/contests/abc393/submissions/62787520)

那么为什么要保证 **每个位置上更新的值单调不降** 才能够用树状数组维护前缀最大值呢？

因为由于上述限制，导致前缀最大值一定单调不降，树状数组保存的信息单调不降。

但如果没有这个限制，若当前的被修改的位置的值本来就是最大值，但修改后变小了，就很难保证其他位置保存的信息的正确性。

~~如果你写了什么奇奇怪怪的黑科技那就当我没说。至少我的写法无法在没有该限制的情况下维护。~~

---

## 作者：CatnipQwQ (赞：0)

我们先考虑学过的求整个序列的 LIS 的算法：记录一个序列 $f$，初始时为空，从小到大枚举 $i$，若 $a_i$ 大于 $f$ 中的最大值或 $f$ 为空就把它插入到 $f$ 的末尾，否则用它替换 $f$ 中下标最小的不小于 $a_i$ 的数。由于 $f$ 单调递增，这里可以用二分找到这样一个位置，复杂度 $O(n \log n)$。

考虑从 DP 角度探索这个算法的本质：$f_i$ 实际上就是长度为 $i$ 的 LIS 的最后一个元素的最小值。设 $p_i$ 表示加入 $a_i$ 时放到的位置，对于 $j<p_i$，有 $f_j<a_i$，所以 $a_i$ 不能更新这样一个位置。对于 $j>p_i$，有 $f_{j-1}\geq a_i$，所以不存在一个以 $a_i$ 结尾的长度为 $j$ 的 LIS，同样不能更新。所以每次加入一个数时只有 $f_{p_i}$ 需要更新。所以这个算法是正确的。

回到这个问题，对于一个询问 $p,x$，考虑在加入完 $a_p$ 后的 $f$，根据我们上面的讨论，二分找到 $f$ 中最后一个不大于 $x$ 的位置 $j$，则 $j$ 就是这个询问的答案，所以只需要把询问离线下来去做就可以啦 awa。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005], f[200005], ans[200005];
vector<pair<int,int> > query[200005];
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i=1; i<=n; i++)
		scanf("%d", &a[i]);
	for(int i=1; i<=q; i++)
	{
		int r, x;
		scanf("%d%d", &r, &x);
		query[r].push_back({x, i});
	}
	int tail=0;
	for(int i=1; i<=n; i++)
	{
		if(f[tail]<a[i])
			f[++tail]=a[i];
		else
			f[lower_bound(f+1, f+tail+1, a[i])-f]=a[i];
		for(auto it:query[i])
			ans[it.second]=upper_bound(f+1, f+tail+1, it.first)-f-1;
	}
	for(int i=1; i<=q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：_determination_ (赞：0)

你看，这一堆询问，显然要对某一维做扫描线啊。

这题其实就是最长上升子序列套个扫描线的壳子罢了，考虑最长上升子序列的状态设计。$f_i$ 表示以 $i$ 为结尾的最长上升子序列长度。

我们有两种选择：对 $R$ 做扫描线和对 $X$ 做扫描线，作者赛事选择了 $X$。

对 $X$ 做扫描线，每个状态只会被加入一次。我们按 $a_i$ 从小到大加入点，$f_i$ 就是 $\max_{j=1}^{i-1}f_j+1$。查询的时候直接找 $\max_{i=1}^{R}f_i$ 即可。我们只需要求前缀 $\max$，用树状数组或线段树维护即可。

---

## 作者：zhouzihang1 (赞：0)

## 思路

关于求 LIS，一般有二分和 dp 两种做法，然而此题数据范围不支持 dp，所以考虑二分。

注意到题目给每组询问都标上了下标，所以考虑按照 $R_i$ 升序排序，依此处理。

按照正常的二分做法，处理完 $R_i$ 时，vector 容器中存储着 LIS 长度为 $j$ 的最后一个元素的最小值，且容器内元素递增，于是对于 $X_i$ 的限制，可以二分完成。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,a[N],Q;
struct node{
	int R,X,ans,id;
}q[N];
bool cmp1(node _,node __){return _.R<__.R;}
bool cmp2(node _,node __){return _.id<__.id;}
int main()
{
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=Q;i++) scanf("%d%d",&q[i].R,&q[i].X),q[i].id=i;
	sort(q+1,q+Q+1,cmp1);
	int last=0;
	vector<int> v;
	for(int i=1;i<=Q;i++)
	{
		int r=q[i].R,x=q[i].X;
		for(int j=last+1;j<=r;j++)
		{
			if(v.empty()||a[j]>v.back()) v.push_back(a[j]);
			*lower_bound(v.begin(),v.end(),a[j])=a[j];
		}
		int pos=upper_bound(v.begin(),v.end(),x)-v.begin();
		q[i].ans=pos;
		last=r;
	}
	sort(q+1,q+Q+1,cmp2);
	for(int i=1;i<=Q;i++) printf("%d\n",q[i].ans);
//	for(int i:v) printf("%d ",i);
	return 0;
}
```

---

## 作者：Aegleseeker_ (赞：0)

## 题意

给你一个长度为 $1\le n\le 2\times 10^5$ 的序列，$q$ 次询问，每次给你一个 $r,x$，求出前缀 $a[1,r]$ 中所有 $\le x$ 的数的 LIS。

## 题解

本质是 dp 数组的二维数点。

我们先求出朴素的那个 LIS 数组 $f_i$，代表不考虑大小限制，$a[1,i]$ 的前缀 LIS。这个很容易 $O(n\log n)$ 求出。

接下来考虑一个性质：如果 $f_i$ 能从 $f_j$ 转移过来且 $a_j>x$，那么 $a_i,a_j$ 都不满足 $\le x$ 的限制。这说明我们不需要考虑所有 $a_i>x$ 的 $f_i$，而对于所有 $a_i\le x$ 的 $f_i$，若其能从 $f_j$ 转移过来，则 $a_j\le x$。

这说明我们只需要考虑所有 $a_i\le x$ 的 $f_i$，取 $\max$ 即可。这样二维数点的刻画就变得显然了：**求 $i\le r,a_i\le x$ 的 $f_i$ 的最大值**，离线扫描线，动态开点线段树是容易维护的。复杂度 $O(n\log n)$。

注意到 LIS 也可以通过动态开点值域线段树求出，所以代码其实并不长。

**警示后人：如果你的写法需要清空线段树，那么请记得你的权值树大小是多少。**

submission：https://atcoder.jp/contests/abc393/submissions/62807573

---

## 作者：sh1kong (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/AT_abc393_f)

纪念一下第一次做出来有质量的 F！

不过这题还是比较典的。

在线做有些困难，考虑离线下来，按照 $R$ 从小到大去做。

考虑记 $f_i$ 表示以 $i$ 结尾的 LIS 的长度，这个东西权值线段树可以 $\mathcal{O(n\log n)}$ 维护。

那么对于每个 $i$，你先把 $f_i$ 计算出来。然后处理询问。对于一个询问 $x$，相当于需要找到一个 $j$ 满足 $A_j \le x$，且 $f_j$ 的值最大。你会发现这个东西还是可以用权值线段树维护，那么就做完了。甚至一棵权值线段树就够了。

注意到 $A_i \le 10^9$，所以需要离散化。

[赛时代码](https://atcoder.jp/contests/abc393/submissions/62806591)，写的有点乱，见谅。

---

## 作者：Yuexingfei_qwq (赞：0)

qwq。
## 思路  
其实就是用二分法求最长上升子序列，只要多加一些改动。  
对于输入的数据排序，二分法求最长上升子序列，用 `upper_bound` 更新答案即可。
## AC CODE  
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a / __gcd(a, b) * b
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned long long;

int n;
str s;
std::vector<int> v;

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> n >> s;
	base(s);
	F(i, 1, n, 1) {
		if (s[i] == '1') {
			v.push_back(i);
		}
	}
	int m = v[(int)v.size() / 2];
	int ans = 0;
	F(i, 0, (int)v.size() - 1, 1) {
		ans += abs(v[i] - (m - (int)v.size() / 2 + i));
	}
	cout << ans << el;
	r0;
}
```

[AC 记录](https://atcoder.jp/contests/abc393/submissions/62786156)

--- 
完结~~不~~散花。

---

## 作者：_Weslie_ (赞：0)

看到 LIS 就是 LIS 了。

## Solution AT_abc393_f

### Idea

考虑将询问离线，按照 $R_i$ 排序。

我们设 $l$ 表示前 $i$ 个数的整个最长上升子序列（长度为 $tot$）。注意 $l$ 存的是整个序列。

于是我们对于一个 $x$，读入进来：如果 $x>l_{tot}$，则说明 $x$ 只能被插在最长上升子序列的末尾；否则我们 $\tt lower\_bound$ 出第一个使 $l_{pos}$ 大于等于 $x$ 的 $pos$（显然 $l$ 有单调性），将 $l_{pos}$ 替换为 $x$。因为 $l_{pos}$ 大于等于 $x$，这样做一定是不劣的（把更大的数替换为更小的数，在更小的范围内可以有更大的答案）。

答案统计就非常简单了：对于 $X_i$，直接二分出第一个 $pos$ 使 $l_{pos}>X_i$，则在 $[1,pos)$ 内有 $l_{pos}\le X_i$。$pos-1$ 就是答案。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int b[N],a[N],n,q,cnt,ans[N],l[N],tot;
struct node{
    int r,x,id;
    friend bool operator <(node _,node __){
        return _.r<__.r;
    }
}e[N];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[++cnt]=a[i];
    }
    for(int i=1;i<=q;i++){
        scanf("%d%d",&e[i].r,&e[i].x);
        b[++cnt]=e[i].x;
        e[i].id=i;
    }
    sort(b+1,b+cnt+1);
    int len=unique(b+1,b+cnt+1)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+len+1,a[i])-b;
        // printf("%d ",a[i]);
    }
    // printf("\n");
    for(int i=1;i<=q;i++){
        e[i].x=lower_bound(b+1,b+len+1,e[i].x)-b;
        // printf("%d %d\n",e[i].r,e[i].x);
    }
    sort(e+1,e+q+1);
    for(int i=1,j=1;i<=n;i++){
        if(l[tot]<a[i])l[++tot]=a[i];
        else {
            int x=lower_bound(l+1,l+tot+1,a[i])-l;
            if(l[x]!=a[i])l[x]=a[i];
        }
        while(j<=q&&e[j].r<=i){
            ans[e[j].id]=upper_bound(l+1,l+tot+1,e[j].x)-l-1;
            j++;
        }
        // for(int k=1;k<=tot;k++)printf("%d ",l[k]);
        // printf("\n");
    }
    for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
}
```

---

## 作者：linjinkun (赞：0)

> 大概评级：绿。

一看到这种题目，就知道肯定是数据结构题，我们首先用一个众所周知的二分来求出 $pos$ 数组，$pos_i$ 表示以 $i$ 结尾的最长上升子序列的大小，然后将询问离线，弄一个 `vector`，命名 $s$，把询问中每个 $R_i$ 为 $i(1 \le i \le n)$ 的询问存进 $s_i$ 中，然后遍历每个 $i(1 \le i \le n)$，每次先修改动态开点权值线段树上的点 $a_i$，将它改为 $pos_i$，然后遍历 $s_i$，将 $s_i$ 中存储的询问全部拿出来，然后查询即可。

总时间复杂度：$O(n+n \log n+q+q \log q) = O(n \log n+q \log q)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e7+5;
int a[N];
int low[N];
int pos[N];
struct node
{
	int l;
	int r;
	int ls;
	int rs;
	int maxx;
}t[N];
struct node1
{
	int x;
	int y;
};
vector<node1>e[N];
int cnt;
void update(int &rt,int l,int r,int x,int v)
{
	if(!rt)
	{
		rt = ++cnt;
		t[rt].l = l;
		t[rt].r = r;
	}
	if(t[rt].l == t[rt].r)
	{
		t[rt].maxx = max(t[rt].maxx,v);
		return;
	}
	int mid = t[rt].l+t[rt].r>>1;
	if(x<=mid)
	{
		update(t[rt].ls,l,mid,x,v);
	}
	else
	{
		update(t[rt].rs,mid+1,r,x,v);
	}
	t[rt].maxx = max(t[t[rt].ls].maxx,t[t[rt].rs].maxx);
}
int query(int rt,int l,int r)
{
	if(!rt)
	{
		return 0;
	}
	if(l<=t[rt].l&&t[rt].r<=r)
	{
		return t[rt].maxx;
	}
	int mid = t[rt].l+t[rt].r>>1,maxx = 0;
	if(l<=mid)
	{
		maxx = max(maxx,query(t[rt].ls,l,r));
	}
	if(r>mid)
	{
		maxx = max(maxx,query(t[rt].rs,l,r));
	}
	return maxx;
}
int ans[N];
signed main()
{
    int n,_,o = 0;
    scanf("%d %d",&n,&_);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    int id = 0;
    for(int i = 1;i<=n;i++)
    {
        if(a[i]>low[id])
        {
            low[++id] = a[i];
            pos[i] = id;
        }
        else
        {
            int poss = lower_bound(low+1,low+id+1,a[i])-low;
            low[poss] = a[i];
            pos[i] = poss;
        }
    }
    for(int i = 1;i<=_;i++)
    {
    	int x,y;
    	scanf("%d %d",&x,&y);
 		e[x].push_back({i,y});
	}
	for(int i = 1;i<=n;i++)
	{
		update(o,1,1e9,a[i],pos[i]);
		for(auto it:e[i])
		{
			ans[it.x] = query(o,1,it.y);
		}
	}
	for(int i = 1;i<=_;i++)
	{
		printf("%d\n",ans[i]);
	}
    return 0;
}
```
总结：这道题的精髓在于将询问离线。

---

## 作者：VitrelosTia (赞：0)

不关心具体值所以先离散化。考虑单次询问怎么做，设 $f_{i,j}$ 表示考虑到 $i$，最大值 $j$ 的答案。暴力转移 $f_{i,j} = \begin{cases}\ \ \max\limits_{k<i} \ \ f_{k,j} \ \ \ \ \ \ \ \ \ j \neq a_i \\ \max\limits_{k<i,p<a_i} f_{k,p}+1 \ \ j = a_i \end{cases}$，发现转移不依赖第一维，直接丢掉。然后考虑多次询问，可以直接离线之后按 $r$ 扫描，在 $r$ 处答案即为 $\max\limits_{i\le x}f_i$。树状数组显然可以轻松维护这个过程。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define test cerr << "test\n"
#define print(x) cout << #x << " = " << x << endl
#define file(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

const int N = 2e5 + 5;
int n, Q, a[N]; vector <pair <int, int>> v[N];
struct qry { int r, x, o; } q[N];
int b[N << 1], m, ans[N];
int o(int x) { return lower_bound(b + 1, b + m + 1, x) - b; }
int c[N << 1]; int qwq(int x) { return x & (-x); }
void update(int x, int k) { for (; x <= m; x += qwq(x)) c[x] = max(c[x], k); }
int query(int x) { int a = 0; for (; x; x -= qwq(x)) a = max(a, c[x]); return a; }

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> Q;
    for (int i = 1; i <= n; i++) cin >> a[i], b[++m] = a[i];
    for (int i = 1; i <= Q; i++) cin >> q[i].r >> q[i].x, b[++m] = q[i].x;
    sort(b + 1, b + m + 1); m = unique(b + 1, b + m + 1) - (b + 1);
    for (int i = 1; i <= n; i++) a[i] = o(a[i]);
    for (int i = 1; i <= Q; i++) q[i].x = o(q[i].x), q[i].o = i, v[q[i].r].push_back({q[i].x, q[i].o});
    for (int i = 1; i <= n; i++) {
        update(a[i], query(a[i] - 1) + 1);
        for (auto [x, o] : v[i]) ans[o] = query(x);
    }
    for (int i = 1; i <= Q; i++) cout << ans[i] << '\n';
    return 0;
}

```

---

## 作者：xiaofu15191 (赞：0)

首先我们要学会 $O(n \log n)$ 计算 $\text{LIS}$。

将 $A$ 中的元素按从小到大的顺序离散化。现在 $A_i \in [1,n]$。用一棵线段树维护 $f$，每次查询区间 $[1,A_i-1]$，我们就可以得到可以转移到 $f_i$ 的最大答案——从第 $1$ 个元素到第 $i$ 个元素的 $\text{LIS}$ 长度。

然后我们将询问离线来做。将询问按 $R_i$ 为第一关键字排序。遍历每一次询问，我们只会将 $A_i$ 依次放入线段树。此时该询问的答案就是线段树中 $[1,R_i]$ 的最大答案。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;
struct segtree
{
	long long tree[800010],lazy[800010];//change the size!
	void update(long long now,long long l,long long r,long long x,long long val)
	{
		if(r<x||l>x) return;
		if(l==r)
		{
			tree[now]=val;
			return;
		}
		long long mid=(l+r)>>1;
		if(x<=mid) update(now<<1,l,mid,x,val);
		else update(now<<1|1,mid+1,r,x,val);
		tree[now]=max(tree[now<<1],tree[now<<1|1]);
	}
	long long query(long long now,long long l,long long r,long long x,long long y)
	{
		if(r<x||l>y) return 0;
		if(x<=l&&r<=y) return tree[now];
		long long mid=(l+r)>>1,ans=0;
		if(x<=mid) ans=max(ans,query(now<<1,l,mid,x,y));
		if(y>mid) ans=max(ans,query(now<<1|1,mid+1,r,x,y));
		return ans;
	}
}s;
long long n,q,num[400010],f[400010],reflect[400010],cnt,ans[400010];
set<long long>st;
map<long long,long long>mp;
struct query
{
	long long x,y,id;
}queries[400010];
bool cmp(query a,query b)
{
	if(a.x<b.x) return true;
	else if(a.x==b.x&&a.y<b.y) return true;
	else return false;
}
int main()
{
	scanf("%lld%lld",&n,&q);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&num[i]);
		st.insert(num[i]);
	}
	for(auto i:st) mp[i]=++cnt,reflect[cnt]=i;
	for(long long i=1;i<=n;i++) num[i]=mp[num[i]];
	for(long long i=1;i<=q;i++) scanf("%lld%lld",&queries[i].x,&queries[i].y),queries[i].id=i;
	sort(queries+1,queries+q+1,cmp);
	long long j=1;
	for(long long i=1;i<=q;i++)
	{
		while(j<=n&&j<=queries[i].x)
		{
			long long tmp=s.query(1,1,n,1,num[j]-1);
			f[j]=tmp+1;
			s.update(1,1,n,num[j],f[j]);
			j++;
		}
		auto it=st.upper_bound(queries[i].y);
		if(it==st.begin())
		{
			ans[queries[i].id]=0;
			continue;
		}
		it--;
		long long tmp=mp[*it];
		ans[queries[i].id]=s.query(1,1,n,1,tmp);
	}
	for(long long i=1;i<=q;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：luogu_starblue (赞：0)

这题和 [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972) 很像。

首先考虑朴素的做法，我们可以考虑 dp，设 $f[i][j]$ 表示考虑前 $i$ 个数，且最后一个数为 $j$ 的最长子序列的长度，转移很简单。
$$f[i][j]=\begin{cases}
  f[i-1][j] & j\neq a_i \\
  \max(f[i-1][j],\displaystyle\max_{k=1}^{j-1}f[i-1][k]+1) & j=a_i
\end{cases}
$$

则对于每一个询问，答案为。
$$
  ans=\max_{j=1}^{X_i}f[R[i]][j]
$$
然而直接转移即使离散化后复杂度也是 $O(n^2)$ 级别的，我们可以考虑用数据结构去优化这个转移过程。

由柿子不难发现我们需要维护数据结构实现查找前缀最大值和进行单点修改，可以用树状数组或线段树实现。

至于询问，我们将所有询问离线下来，然后按 $R_i$ 排序，依次处理即可。

$A_i$ 与 $X_i$ 值域太大，需要离散化。

最终时间复杂度为 $O(N\log N + Q\log Q)$。

具体见代码。


```cpp
#include<bits/stdc++.h>
#define lson cur<<1,l,mid
#define rson cur<<1|1,mid+1,r
#define root 1,0,m
using namespace std;
const int maxn=2e5+9;
int a[maxn];
vector<int>b;
struct node
{
	int r,x,id;
	bool operator<(const node &you)const
	{
		return r<you.r;
	}
}ask[maxn];
int t[maxn<<2];
void pushup(int cur)
{
	t[cur]=max(t[cur<<1],t[cur<<1|1]);
}
void modify(int cur,int l,int r,int x,int k)
{
	if(l==r)
	{
		t[cur]=max(t[cur],k);
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid)modify(lson,x,k);
	else modify(rson,x,k);
	pushup(cur);
}
int query(int cur,int l,int r,int x,int y)
{
	if(x<=l&&y>=r)
	{
		return t[cur];
	}
	int mid=l+r>>1;
	int res=0;
	if(x<=mid)res=max(res,query(lson,x,y));
	if(y>=mid+1)res=max(res,query(rson,x,y));
	return res;
}
int ans[maxn];
int main()
{ 
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b.push_back(a[i]);
	}
	b.push_back(0);
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	int m=b.size()-1;//离散化 
	for(int i=1;i<=q;i++)
	{
		cin>>ask[i].r>>ask[i].x;
		ask[i].id=i;
	}
	sort(ask+1,ask+1+q);//离线 
	for(int i=1,j=1;i<=n;i++)
	{
		int pos=lower_bound(b.begin(),b.end(),a[i])-b.begin();
		modify(root,pos,query(root,0,pos-1)+1);//更新f数组 
		while(j<=q&&ask[j].r==i)
		{
			int pos=upper_bound(b.begin(),b.end(),ask[j].x)-b.begin();
			ans[ask[j].id]=query(root,0,pos-1);//查询答案 
			j++;
		}
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}

```

---

## 作者：SpringFullGarden (赞：0)

## 题意

有一个长度为 $n$ 的序列 $a_i$。有 $q$ 个查询，每次查询给出 $r, x$，求序列 $a_i$ 在长度为 $r$ 的前缀中，每个元素不超过 $x$ 的最长上升子序列的长度。

## 思路

前置知识：[P1020 [NOIP 1999 提高组] 导弹拦截](https://www.luogu.com.cn/problem/P1020)。

观察到，因为要求最长上升子序列的长度，所以子序列中最后一个元素 $\le x$ 即可。

将询问离线下来，按照 $r$ 排序，这样就可以不用考虑 $r$ 的影响了。

设 $f_i$ 表示长度为 $i$ 的最长上升子序列的末尾元素的最小值，显然 $f_i$ 是单调不降的。

当用 $a_i$ 更新的时候，更新询问的 $r$ 为 $i$ 的答案，可以通过二分得到答案。

## 代码

```cpp
struct que {
    int r, x, ans, id;
} q[200005];
int a[200005], f[200005];

bool cmp(que x, que y) {
    return x.r < y.r;
}
bool Cmp(que x, que y) {
    return x.id < y.id;
}
signed main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
    int n = rd(), Q = rd();
    for(int i = 1; i <= n; i++) a[i] = rd();
    for(int i = 1; i <= n; i++) f[i] = inf;
    for(int i = 1; i <= Q; i++) 
        q[i].r = rd(), q[i].x = rd(), q[i].id = i;
    sort(q + 1, q + Q + 1, cmp);
    for(int i = 1, j = 1; i <= n; i++) {
        int l = 0, r = i;
        while(l < r) {
            int mid = (l + r + 1) >> 1;
            if(f[mid] < a[i]) l = mid;
            else r = mid - 1;
        }
        f[l + 1] = min(f[l + 1], a[i]);
        while(q[j].r == i) {
            l = 0, r = i;
            while(l < r) {
                int mid = (l + r + 1) >> 1;
                if(f[mid] <= q[j].x) l = mid;
                else r = mid - 1;
            }
            q[j].ans = l, j++;
        }
    }
    sort(q + 1, q + Q + 1, Cmp);
    for(int i = 1; i <= Q; i++) cout << q[i].ans << '\n';
    return 0;
}
```

---

## 作者：lilong (赞：0)

比较简单的 LIS 模板题。

回顾使用树状数组求解 LIS 问题的过程：用树状数组的下标表示 $a$ 的值域，存储 $f$ 的最大值。求解时在 $[1,a_i-1]$ 上取最大值，并更新到 $a_i$ 对应的位置。

类似地，在本题中，询问前 $R$ 个数且值不超过 $X$ 的 LIS 长度，发现正好能用树状数组存储的信息解决。具体地，先把所有询问离线下来，并对 $a$ 离散化，从前往后求 LIS。假设当前到了第 $i$ 位，那么先用当前 $a_i$ 更新树状数组，再解决所有 $R=i$ 的询问，答案即为 $[1,X]$ 上的最大值（只需保证最大的一项即最后一项不超过 $X$ 即可）。最后再一遍输出答案即可。

总时间复杂度 $O( ( n + m )\log n)$。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct Q
{
    int x,id;
};

vector<Q> q[1000001];
int n,m,ans[1000001],a[1000001];
int f[1000001],tp;
int ls[1000001],tot;
int t[1000001];

int lowbit( int x )
{
    return x & ( -x );
}

void upd( int x , int y )
{
    for( int i = x ; i <= tot ; i += lowbit( i ) )
        t[i] = max( t[i] , y );
    return;
}

int que( int x )
{
    int mx = 0;
    for( int i = x ; i >= 1 ; i -= lowbit( i ) )
        mx = max( mx , t[i] );
    return mx;
}

bool cmp( Q x , Q y )
{
    return x.x < y.x;
}

int main()
{
    int r,x;
    cin >> n >> m;
    for( int i = 1 ; i <= n ; i ++ )
        cin >> a[i],ls[++ tot] = a[i];
    for( int i = 1 ; i <= m ; i ++ )
    {
        cin >> r >> x;
        ls[++ tot] = x;
        q[r].push_back( { x , i } );
    }
    sort( ls + 1 , ls + tot + 1 );
    tot = unique( ls + 1 , ls + tot + 1 ) - ls - 1;
    for( int i = 1 ; i <= n ; i ++ )
    {
        a[i] = lower_bound( ls + 1 , ls + tot + 1 , a[i] ) - ls;
        for( auto &p : q[i] )
            p.x = lower_bound( ls + 1 , ls + tot + 1 , p.x ) - ls;
    }
    for( int i = 1 ; i <= n ; i ++ )
        sort( q[i].begin() , q[i].end() , cmp );
    for( int i = 1 ; i <= n ; i ++ )
    {	
		upd( a[i] , que( a[i] - 1 ) + 1 );
        for( auto p : q[i] )
            ans[p.id] = que( p.x );
    }
    for( int i = 1 ; i <= m ; i ++)
        cout << ans[i] << '\n';
    return 0;
}
```

---

## 作者：lfxxx_ (赞：0)

先对所有的 $A_i$ 和 $X_j$ 离散化，记 $V$ 为所有 $A_i$ 和 $X_j$ 的最大值。

我们定义 $f_i$ 为前 $i$ 个数中的最长严格上升子序列，然后插入到一颗权值线段树中。

我们发现权值线段树对于查询无能为力，于是我们把权值线段树换成主席树，每个节点维护有 $3$ 个信息：

1. $l_p$，表示这个节点的左端点；

2. $r_p$，表示这个节点的右端点；

3. $mx_p$，表示对于所有满足 $l_p \le A_i \le r_p$ 的 $i$，$f_i$ 的最大值。

查询就只需要查询第 $R_i$ 颗树上的所有 $1 \le A_i \le X_i$ 的节点了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=5e6+5;
int mx[M],ls[M],rs[M],rt[N],tot;
void pushup(int p)
{
    mx[p]=0;
    if(ls[p])mx[p]=max(mx[p],mx[ls[p]]);
    if(rs[p])mx[p]=max(mx[p],mx[rs[p]]);
}
int build(int pl,int pr)
{
    int p=++tot;
    if(pl==pr){return p;}
    int mid=(pl+pr)>>1;
    ls[p]=build(pl,mid);
    rs[p]=build(mid+1,pr);
    pushup(p);
    return p;
}
int update(int p,int pl,int pr,int x,int d)
{
    ++tot;
    ls[tot]=ls[p];
    rs[tot]=rs[p];
    mx[tot]=mx[p];
    p=tot;
    if(pl==pr)
    {
        mx[p]=max(mx[p],d);
        return p;
    }
    int mid=(pl+pr)>>1;
    if(x<=mid)ls[p]=update(ls[p],pl,mid,x,d);
    else rs[p]=update(rs[p],mid+1,pr,x,d);
    pushup(p);
    return p;
}
int query(int p,int pl,int pr,int L,int R)
{
    if(!p)return 0;
    if(L<=pl&&pr<=R)return mx[p];
    int mid=(pl+pr)>>1;
    if(R<=mid)return query(ls[p],pl,mid,L,R);
    if(L>mid)return query(rs[p],mid+1,pr,L,R);
    return max(query(ls[p],pl,mid,L,R),query(rs[p],mid+1,pr,L,R));
}
int a[N],p[N],x[N],dp[N],rk[N<<1];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i],rk[i]=a[i];
    for(int i=1;i<=m;++i)
        cin>>p[i]>>x[i],rk[i+n]=x[i];
    sort(rk+1,rk+n+m+1);
    int V=unique(rk+1,rk+n+m+1)-rk-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(rk+1,rk+V+1,a[i])-rk;
    for(int i=1;i<=m;i++)x[i]=lower_bound(rk+1,rk+V+1,x[i])-rk;
    rt[0]=build(0,V);
    for(int i=1;i<=n;++i)
    {
        dp[i]=query(rt[i-1],0,V,0,a[i]-1)+1;
        rt[i]=update(rt[i-1],0,V,a[i],dp[i]);
    }
    for(int i=1;i<=m;++i)
        cout<<query(rt[p[i]],0,V,1,x[i])<<'\n';
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路：

考虑 dp。

考虑离线操作，先对所有查询按照 $r$ 由小到大进行排序。

我们设 $f_i$ 表示长度为 $i$ 的最长上升子序列的结尾数最小是几。

显然 $f$ 具有单调性，所以我们接下来考虑二分。

从左往右考虑每个 $a_i$，我们通过二分找到一个位置 $x$，使得 $f_{x-1}<a_i \le f_x$，用 $a_i$ 更新 $f_x$，或者 $a_i$ 会更新当前最长上升子序列的长度，这是要注意维护我们当前最长上升子序列的长度。

对于每次查询，若当前所处理到的 $i$ 恰好等于其 $r$，则直接通过 ```upper_bound``` 得到一个下标，这个下标就是这次查询得到的答案。

最后输出即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[1000005];
struct node{
	int r,x,id;
}ask[1000005];

inline bool cmp(node x,node y){
	return x.r<y.r; 
}

int f[1000005];// f[i]:长度为 i 的最长上升子序列的结束值最小是几

int R;// 当前最长上升子序列长度

 
int ans[1000005];

int tot=1;

signed main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}	
	for (int i=1;i<=m;i++){
		cin>>ask[i].r>>ask[i].x;
		ask[i].id=i;
	} 
	sort(ask+1,ask+m+1,cmp);
	for (int i=1;i<=n;i++){
		int l=1;
		int r=R;
		while (l<=r){
			int mid=(l+r)/2;
			if (f[mid]<a[i]){
				l=mid+1;
			}
			else{
				r=mid-1;
			}
		}
		f[l]=a[i];
		R=max(R,l);
		for (int j=tot;j<=m;j++){
			if (ask[j].r!=i){
				break;
			}
			ans[ask[j].id]=upper_bound(f+1,f+R+1,ask[j].x)-f-1;
			tot++;
		}
	} 
	for (int i=1;i<=m;i++){
		cout<<ans[i]<<'\n';
	}
	return 0;
}
```

---

## 作者：MutU (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/AT_abc393_f)

话说 at 是真没题出了吗，这种裸题都来了。

另外，这是我第二次不会 $e$ 但一眼 $f$ 了，怎么回事呢？

### 题意简述

> 给你一个整数序列 $a$，有 $q$ 个形如 $r_i$ $x_i$ 的询问：考虑构造 $(a_1,a_2,...,a_{r_i})$ 的子序列 $b$，满足 $b$ 中元素严格递增，且 $b$ 中最大元素不超过 $x_i$。求出 $b$ 长度的最大值。

考虑到 $b$ 严格递增，所谓 $b$ 中最大元素显然是最后一个元素。

### Case #1

首先，假如只是求最长严格递增子序列，应该怎么做？

- **我会线段树优化 dp！**

较为显然的线段树优化 dp：

令 $f_i$ 表示以元素 $a
_i$ 结尾的严格递增子序列的长度最大值，每次转移只需考虑当前元素前面比它小的元素，那么朴素转移是平方复杂度的。

我们将原数列元素离散化，线段树上的一段区间维护以这一段区间中元素结尾的子序列最大长度。

转移就变为 $f_i=query(1,a_i-1)+1$，其中 $query(l,r)$ 表示以区间 $(l,r)$ 中元素结尾的子序列最大长度。

### Case #2

考虑如何处理询问。

- **我会主席树！**

我们做一次上文中的 dp，对于每个 $f_i$ 存入主席树。

对于询问 $i$，求出下标 $1 \sim r_i$，结尾元素 $\le x_i$ 的子序列最大值即可。

但是主席树还是太吃码力了。不过这样简单又强势的做法当然不止一个。

- **我会询问离线！**

根据套路，这种询问下标单一的主席树问题都可以用询问离线解决。

将询问离线，按照 $r_i$ 从小到大排序。

依然做上文中的 dp，若当前处理到 $i$，我们可以顺便计算所有 $r_i=i$ 的询问：$ans_i=query(1,x_i)$。

于是做完了。

### Code

由于赛时的一些奶龙错误导致多次神秘 RE，代码中离散化和其它一些部分相当诡异，将就看一下。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 400100;
int n,q,a[N],f[N];
struct que{
	int r,x;
	int id;
}t[N];
int tree[N*4];
inline void push_up(int x){
	tree[x]=max(tree[x*2],tree[x*2+1]);
	return;
}
inline void updata(int l,int r,int L,int R,int x,int d){
	if(l>=L && r<=R){
		tree[x]=max(tree[x],d);
		return;
	}
	int mid=l+r>>1;
	if(mid>=L) updata(l,mid,L,R,x*2,d);
	if(mid+1<=R) updata(mid+1,r,L,R,x*2+1,d);
	push_up(x);
	return;
}
int query(int l,int r,int L,int R,int x){
	if(L>R) return 0;
	if(l>=L && r<=R) return tree[x];
	int mid=l+r>>1,ans=0;
	if(mid>=L) ans=max(ans,query(l,mid,L,R,x*2));
	if(mid+1<=R) ans=max(ans,query(mid+1,r,L,R,x*2+1));
	return ans;
}
int p[N*4],tot,cnt,ans[N];
map <int,int> ma1;
bool cmp(que a,que b){
	return a.r<b.r;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i],p[++tot]=a[i];
	}
	for(int i=1;i<=q;i++){
		cin>>t[i].r>>t[i].x;
		t[i].id=i;
		p[++tot]=t[i].x;
	}
	sort(p+1,p+1+tot);
	for(int i=1;i<=tot;){
		int tmp=p[i];
		ma1[tmp]=++cnt;
		while(i<=tot && p[i]==tmp) i++;
	}
	for(int i=1;i<=n;i++) a[i]=ma1[a[i]];
	for(int i=1;i<=q;i++) t[i].x=ma1[t[i].x];
	sort(t+1,t+1+q,cmp);
	tot=1;
	for(int i=1;i<=n;i++){
		f[i]=query(1,cnt,1,a[i]-1,1)+1;
		updata(1,cnt,a[i],a[i],1,f[i]);
		while(tot<=q && t[tot].r==i){
			ans[t[tot].id]=query(1,cnt,1,t[tot].x,1);
			tot++;
		}
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

[提交记录](https://atcoder.jp/contests/abc393/submissions/62823065)

---

