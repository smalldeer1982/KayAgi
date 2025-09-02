# [ABC408C] Not All Covered

## 题目描述

AtCoder 国度有 $N$ 堵城墙和 $M$ 个炮塔。第 $i$ 个炮塔守卫着第 $L_i$ 到第 $R_i$ 堵城墙。

求至少摧毁多少个炮塔，使得至少一堵城墙没有被任何一个瞭望塔守卫。

## 说明/提示

**样例 1 解释**

摧毁炮塔 $1$ 后，城墙 $3$ 无炮塔守卫。不摧毁炮塔时任何城墙均有炮塔守卫，故答案为 $1$。

**样例 2 解释**

没有炮塔守卫城墙 $5$，你不需要摧毁任何炮塔。故答案为 $0$。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
10 4
1 6
4 5
5 10
7 10```

### 输出

```
1```

## 样例 #2

### 输入

```
5 2
1 2
3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
5 10
2 5
1 5
1 2
2 4
2 2
5 5
2 4
1 2
2 2
2 3```

### 输出

```
3```

# 题解

## 作者：Ashankamiko (赞：6)

# 题目简述
### 题意
给出 $N$ 座编号为 $1$ 到 $N$ 的塔楼，初始为空。有 $M$ 个区间存在炮塔（$L_i$ 到 $R_i$ 之间的炮塔需要叠加），问最少要消灭几个炮塔才能使那个塔楼没有炮塔。
### 思路
首先是暴力枚举。
- 定义 $cnt$ 数组为每座塔楼的炮塔数量。
- 对于 $M$ 次操作，每次都让 $L_i$ 到 $R_i$ 之间的数全部 $+1$。
- 最后遍历 $N$ 个塔楼，取出最小的 $cnt_i$。
- 时间复杂度为 $O(N \times (N+M))$。

最后的结果也显而易见，参考下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/b8u7h680.png)
所以本题需要这些算法（或更多）才不会超时（按照运行效率排序）：
- 树状数组。
- 线段树。
- 分块。

这里我采用分块解题，分块具有以下特点：
- 思路简单，直观，容易理解。
- 对于数据比较大的，效率往往不高，但足以通过本题。

其实本题的模板便是：[P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)，这一题写分块也能过。

这两题的区别在于：
- P3372 是对 $x$ 到 $y$ 之间的所有数加上 $k$，而这题只需对 $x$ 到 $y$ 之间的数 $+1$ 即可。
- P3372 查询为一整个区间，而这题查询时只需要查询一个数。

~~那这题不就变的更简单了吗（说白了还是线段树）。~~

## 分块
顾名思义，分块就是把一个序列分成多个块，处理这些块的时候就可以统一数据，减少时间的开销。

一般把每个块大小不超过 $\lfloor \sqrt{N} \rfloor$，共有 $\lceil \sqrt{N} \rceil$ 块，所以时间复杂度为 $O((N+M) \times \sqrt{N})$。

### 分块的基础变量
分块所需要的基础变量：
- 用 $sum_i$ 表示第 $i$ 段中，所有数的和。
- 用 $add_i$ 表示第 $i$ 段一整段需要修改的数，相当于对整段进行处理。
- 用 $pos_i$ 表示第 $i$ 个位置属于哪一段，需要初始化。
- 用 $L_i$ 和 $R_i$ 表示每一段开头和末尾的点。

在处理数据的时候，如果是整块，则直接令 $add_i \gets add_i+1$，否则，就按照暴力枚举的写法处理不是整块的部分，即：令 $a_i \gets a_i+1$。

同时，我们还需要更新第 $i$ 段的区间和 $sum_i$。
## [AC 代码](https://atcoder.jp/contests/abc408/submissions/66343985)
可以看出，这一题用分块做巅值耗时也仅仅为 $339$ 毫秒。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define in cin
#define out cout
const int N = 1e6 + 5;
int a[N], sum[N], add[N], L[N], R[N], pos[N], n, m, t; //如上所述
void change(int l, int r, int d) { //让l到r之间的数+d（对于本题，d=1）
	int p = pos[l], q = pos[r];
	if (p == q) { //在同一段内
		for (int i = l; i <= r; i++)
			a[i] += d;
		sum[p] += d * (r - l + 1);
	} else { //维护整段
		for (int i = p + 1; i <= q - 1; i++) //对一整段进行处理
			add[i] += d;
		for (int i = l; i <= R[p]; i++) //处理前段
			a[i] += d;
		sum[p] += d * (R[p] - l + 1);
		for (int i = L[q]; i <= r; i++) //处理后段
			a[i] += d;
		sum[q] += d * (r - L[q] + 1); //更新区间和
	}
}
int ask(int l, int r) { //查询l到r的区间
	int p = pos[l], q = pos[r], ans = 0;
	if (p == q) { //同一段内
		for (int i = l; i <= r; i++)
			ans += a[i];
		ans += add[p] * (r - l + 1);
	} else {
		for (int i = p + 1; i <= q - 1; i++) //同理
			ans += sum[i] + add[i] * (R[i] - L[i] + 1);
		for (int i = l; i <= R[p]; i++)
			ans += a[i];
		ans += add[p] * (R[p] - l + 1);
		for (int i = L[q]; i <= r; i++)
			ans += a[i];
		ans += add[q] * (r - L[q] + 1);
	}
	return ans;
}
signed main() {
	in >> n >> m;
	t = sqrt(n); //分块
  	//初始化
	for (int i = 1; i <= t; i++)
		L[i] = (i - 1) * sqrt(n) + 1, R[i] = i * sqrt(n);
	if (R[t] < n)
		t++, L[t] = R[t - 1] + 1, R[t] = n;
	for (int i = 1; i <= t; i++)
		for (int j = L[i]; j <= R[i]; j++)
			pos[j] = i, sum[i] += a[j];
	while (m--) { //m个区间
		int l, r;
		in >> l >> r;
		change(l, r, 1); //令这一整个区间都+1
	}
	int minx = INT_MAX;
	for (int i = 1; i <= n; i++) //n座塔楼
		minx = min(minx, ask(i, i)); //取出炮台数量的最小值
	out << minx; //输出答案
	return 0;
}
```

---

## 作者：GeorgeDeng (赞：2)

差分模板题。

如果看不懂题意的请自行利用 AI 翻译。

## Solution

因为要把 $n$ 个城墙中至少一个没有被炮塔保护，所以，我们的目标是被炮塔保护个数最少的那个城墙。

因为题目要求要摧毁的炮塔个数，所以只要求出那个城墙的被炮塔保护的个数就行了。

首先，暴力肯定是不行的。这时候，就要利用我们的差分了。

如果你不会差分，可以先去看看[模板题](https://www.luogu.com.cn/problem/P2367)。

我们定义 $s$ 数组为差分数组。

每次输入 $L_i$ 和 $R_i$，用差分把 $s_{L_i}\larr s_{L_i}+1, s_{R_i+1}\larr s_{R_i+1}-1$。

把差分数组回溯，$s_i\larr s_i+s_{i-1}$。

答案就显而易见了，就是 $s$ 数组中的最小值。

## code：

```cpp
#include <iostream>
#define int long long
using namespace std;

int n,m;
int s[1000005];//差分数组
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		s[a]++,s[b+1]--;//差分板子
	}
	for(int i = 1;i<=n;i++){
		s[i]+=s[i-1];
	}
	int minn = 0x7fffffffffffffff;//求最小值
	for(int i = 1;i<=n;i++){
		minn = min(minn,s[i]);
	}
	cout<<minn;//输出答案
	return 0;
}

```

---

## 作者：sjh0626 (赞：1)

## 思路分析
题目中说要使移去的炮台最少，也就是我们只需要找到炮台覆盖最少的位置就行了。

但是暴力去处理的话要超时，所以我们需要差分，差分就是前缀和的逆运算（后面减前面）。

因此我们用一个差分数组 `c`。对于每个炮台 `c[l]++`，因为 $l$ 处比前面多一个炮台，然后 `c[r+1]--`，因为 $r+1$ 处比前面少一个炮台。

最后前缀和一下，再取最小值就行了。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
#define PII pair<int,int>
using namespace std;
int t=1;
int n,m,l,r,c[1000010],minn=1e9;
void solve(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>l>>r;
		c[l]++;
		c[r+1]--;
	}
	for(int i=1;i<=n;i++){c[i]+=c[i-1];minn=min(minn,c[i]);}
	cout<<minn;
}
int main(){
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
//    cin>>t;
	while(t--){
		solve();
	}
	sjh0626s code;
}
```

---

## 作者：ouxiyao (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc408_c) [AT传送门](https://atcoder.jp/contests/abc408/tasks/abc408_c) 
# AT_abc408_c [ABC408C] Not All Covered 题解
老规矩，读题：炮塔 $i$ 守护第 $l$ 到第 $r$ 座城堡，给出一些炮塔，求最少炸掉多少座炮塔才能让一个城墙没炮守护。             
贪心，选择一个守护的炮塔最少的城墙，轰击其所有的炮即可。    
## 暴力
暴力统计每个炮塔被多少个炮守护者，复杂度太高，没写。
## 线段树（暴力修改）
区修区查，一眼线段树。     
每次修改限定区间的所有子节点，每个区间维护最小值。可惜比暴力多个 $\log$。       
代码：  

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define lc u<<1
#define rc u<<1|1
using namespace std;
int minn[N*4];
void pushup(int u){minn[u] = min(minn[lc],minn[rc]);}
void change(int u,int l,int r,int x,int y){
	if(x>r||y<l)return ;
	if(l==r){
		minn[u]++;
		return ;
	}
	int mid = (l+r)>>1;
	change(lc,l,mid,x,y);
	change(rc,mid+1,r,x,y);
	pushup(u);
}
int query(int u,int l,int r,int x,int y){
	if(x>r||y<l)return 2147483647;
	if(x<=l&&r<=y)return minn[u];
	int mid = (l+r)>>1;
	return min(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	int n,m,l,r;
	cin>>n>>m;
	for(int i = 1;i<=m;i++){
		cin>>l>>r;
		change(1,1,n,l,r);
	}
	cout<<query(1,1,n,1,n);
	return 0;
}//T了，不注释了
```
[笑](https://atcoder.jp/contests/abc408/submissions/66331782)
## 线段树（懒标记优化）
找到复杂度瓶颈没？ 

```cpp
if(l==r)
```
这就是复杂度高的原因！区修 $O(n^2\log n)$，只能想一个优化的办法：懒标记！        
每个节点维护一个标记，表示节点对应的区域每个点都加了多少。根节点到叶节点 $[i,i]$ 会经过所有包括 $i$ 的节点，so，将经过的所有结点的懒标记的值加起来就可以求出 $i$ 的值了！        
复杂度终于降下来了！$O(n\log n)$！     
代码（AC了）（直接提交的结果你猜）：

```cpp
#include<bits\stdc++.h>
#define N 1000005
#define lc u<<1
#define rc u<<1|1
using namespace std;
int minn[N*4],add[N*4];//最小值与懒标记
void pushup(int u){minn[u] = min(minn[lc],minn[rc]);}//维护最小值
void pushdown(int u){//更改懒标记
	if(add[u]){
		minn[lc]+=add[u];
		minn[rc]+=add[u];
		add[lc]+=add[u];
		add[rc]+=add[u];
		add[u] = 0;
	}
}
void change(int u,int l,int r,int x,int y){
	if(x>r||y<l)return ;//特判
	if(x<=l&r<=y){
		minn[u]++;
		add[u]++;//更改懒标记
		return 0;
	}
	pushdown(u);
	int mid = (l+r)>>1;
	change(lc,l,mid,x,y);//修改左子树
	change(rc,mid+1,r,x,y);//修改右子树
	pushup(u);
}
int query(int u,int l,int r,int x,int y){
	if(x>r||y<l)return 2147483647;//越界返回极大值
	if(x<=l&&r<=y)return minn[u];
	pushdown(u);
	int mid = (l+r)>>1;
	return min(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
}
int mian(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	int n,m,l,r;
	cin>>n>>m;
	for(int i = 1;i<=m;i++){
		cin>>l>>r;
		change(1,1,n,l,r);//区修
	}
	cout<<query(1,1,n,1,n);//区查
	return 0;
}

```
[嘿](https://atcoder.jp/contests/abc408/submissions/66336997)          
另：建议评黄或绿。

---

## 作者：ccxXF (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/AT_abc408_c)
## 题目分析
希望审核大大给过。

这道题第一眼看的就是一道暴力题，只需将每一个围墙的守卫个数算出来，再判断谁最小输出即可，可是只要是人看到数组大小就炸了，所以我思考了一下，忽然想到可以用**差分**来做！

差分是前缀和的逆运算，通过差分，对数列指定区间进行加减操作。定义一个数组储存差分后数组 $s$ 和差分数组 $a$，使得 $s_i = a_1 + a_2 + a_3 + \dots + a_i$，这个式子就可以用递推公式 $s_i = s_{i-1} + a_i$ 来简化时间复杂度。
```cpp
a[l]+=1;
a[r+1]-=1;
```
上面的代码可以使 $s_l$ 至 $s_r$ 的数字加 $1$，再将所有的 $s_i$ 改为 $a_1 + a_2 + a_3 + \dots + a_i$，就可以算出每一个围墙的守卫个数。

我们可以简化问题，将减少最少次数的问题改为计算 $s$ 数组中数值最小值的问题。证明也很简单：假设数组中数值最小值为 $n$，下标为 $t$，那么最优情况就是撤走有关 $t$ 的 $n$ 的守卫就是最优解。（$n$ 可能为 $0$）

下面是我本题赛时 AC 代码。
## 题目代码
```cpp
//点个赞qaq
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
int n,m,l,r,c;
const int N=1e6+1;
int a[1000001],s[1000001];
signed main(){
	speed
	cin>>n>>m;
	while(m--){
		cin>>l>>r;
		a[l]+=1;
		a[r+1]-=1;
	}
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	int minn=INT_MAX;
	for(int i=1;i<=n;i++)minn=min(minn,s[i]);
	cout<<minn;
	return 0;
}
```

---

## 作者：Chase12345 (赞：0)

一眼。

注意到我们要使得一个位置没有被覆盖，则我们需要去掉的个数就是覆盖的次数，此时覆盖的次数变为区间加。但是注意到只有最后一个作为查询，所以可以差分。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int a[N], d[N];

int main() {
	  int n, m, minn = 1e9;
	  cin >> n >> m;
	  for (int i = 1, l, r; i <= m; i++) {
		    cin >> l >> r;
		    d[l]++;
		    d[r + 1]--;
	  }
	  for (int i = 1; i <= n; i++) {
		    a[i] = a[i - 1] + d[i];
		    minn = min(minn, a[i]);
	  }
	  cout << minn << '\n';
	  return 0;
}

---

## 作者：Lyw_and_Segment_Tree (赞：0)

考虑对每个 $[l_i, r_i]$ 进行区间加操作，这一步可以使用差分或树状数组或线段树或其他数据结构和算法完成。

之后，设第 $i$ 个点被加了 $g_i$ 次，这相当于第 $i$ 个点被 $g_i$ 条线段覆盖，那么要使第 $i$ 个点不被覆盖，就要删去 $g_i$ 条线段。

因为要使修改次数最小，所以 $\displaystyle \min_{i = 1}^{n} g_i$ 即为答案。

[code](https://atcoder.jp/contests/abc408/submissions/66373255)

---

## 作者：CCY20130127 (赞：0)

## 题目分析：
如果要遍历每一个 $L$ 到 $R$ 之间的数，那么时间复杂度为 $O(n^2)$，即使是两秒钟也会超时。此时我们就要想一种时间复杂度 $O(n)$ 的算法，对了，差分！

这个问题可以转化为：找到最少需要移除多少个区间，使得剩下的区间不能完全覆盖 $1 \dots N$。

首先使用差分算法计算每个城墙被多少个炮台保护，在使用前缀和数组计算计算每个城墙被保护的具体次数，保护次数最少的城墙就是答案了！

## 正解：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6+10;
int n, m, a[N];
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
inline void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;//输入
	for (int i = 1; i <= m; i++) {
		int l, r;
		cin >> l >> r;//输入
		a[l]++;//差分维护
		a[r + 1]--;
	}
	int ans = 0, minn = INT_MAX;
	for (int i = 1; i <= n; i++) {
		ans += a[i];//前缀和
		if (ans < minn) minn = ans;//保护次数最少的城墙就是答案
	}
	cout << minn << "\n";//输出
	return 0;
}
```

---

