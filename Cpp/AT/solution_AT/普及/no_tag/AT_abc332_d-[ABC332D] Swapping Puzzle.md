# [ABC332D] Swapping Puzzle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc332/tasks/abc332_d

$ H $ 行 $ W $ 列の $ 2 $ つのグリッド A, B が与えられます。

$ 1\ \leq\ i\ \leq\ H $ と $ 1\ \leq\ j\ \leq\ W $ を満たす各整数の組 $ (i,\ j) $ について、 $ i $ 行目 $ j $ 列目にあるマスをマス $ (i,\ j) $ と呼ぶとき、 グリッド A の マス $ (i,\ j) $ には整数 $ A_{i,\ j} $ が、 グリッド B の マス $ (i,\ j) $ には整数 $ B_{i,\ j} $ がそれぞれ書かれています。

あなたは「下記の $ 2 $ つのうちのどちらか $ 1 $ つを行う」という操作を好きな回数（ $ 0 $ 回でもよい）だけ繰り返します。

- $ 1\ \leq\ i\ \leq\ H-1 $ を満たす整数 $ i $ を選び、グリッド A の $ i $ 行目と $ (i+1) $ 行目を入れ替える。
- $ 1\ \leq\ i\ \leq\ W-1 $ を満たす整数 $ i $ を選び、グリッド A の $ i $ 列目と $ (i+1) $ 列目を入れ替える。

上記の操作の繰り返しによって、グリッド A をグリッド B に一致させることが可能かどうかを判定してください。 さらに、一致させることが可能な場合は、そのために行う操作回数の最小値を出力してください。

ここで、グリッド A とグリッド B が一致しているとは、 $ 1\ \leq\ i\ \leq\ H $ と $ 1\ \leq\ j\ \leq\ W $ を満たす全ての整数の組 $ (i,\ j) $ について、 グリッド A の マス $ (i,\ j) $ とグリッド B の マス $ (i,\ j) $ に書かれた整数が等しいこととします。

## 说明/提示

### 制約

- 入力される値は全て整数
- $ 2\ \leq\ H,\ W\ \leq\ 5 $
- $ 1\ \leq\ A_{i,\ j},\ B_{i,\ j}\ \leq\ 10^9 $

### Sample Explanation 1

初期状態のグリッド A の $ 4 $ 列目と $ 5 $ 列目を入れ替えると、グリッド A は下記の通りになります。 ``` 1 2 3 5 4 6 7 8 10 9 11 12 13 15 14 16 17 18 20 19 ``` 続けて、グリッド A の $ 2 $ 行目と $ 3 $ 行目を入れ替えると、グリッド A は下記の通りになります。 ``` 1 2 3 5 4 11 12 13 15 14 6 7 8 10 9 16 17 18 20 19 ``` 最後に、グリッド A の $ 2 $ 列目と $ 3 $ 列目を入れ替えると、グリッド A は下記の通りになり、グリッド B に一致します。 ``` 1 3 2 5 4 11 13 12 15 14 6 8 7 10 9 16 18 17 20 19 ``` 上に述べた $ 3 $ 回の操作でグリッド A をグリッド B に一致させることができ、 これより少ない回数の操作でグリッド A をグリッド B に一致させることはできないため、 $ 3 $ を出力します。

### Sample Explanation 2

問題文中の操作をどのように行ってもグリッド A をグリッド B に一致させることは不可能であるため `-1` を出力します。

### Sample Explanation 3

グリッド A ははじめからグリッド B に一致しています。

## 样例 #1

### 输入

```
4 5
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
1 3 2 5 4
11 13 12 15 14
6 8 7 10 9
16 18 17 20 19```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
1 1
1 1
1 1
1 1000000000```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 3
8 1 6
3 5 7
4 9 2
8 1 6
3 5 7
4 9 2```

### 输出

```
0```

## 样例 #4

### 输入

```
5 5
710511029 136397527 763027379 644706927 447672230
979861204 57882493 442931589 951053644 152300688
43971370 126515475 962139996 541282303 834022578
312523039 506696497 664922712 414720753 304621362
325269832 191410838 286751784 732741849 806602693
806602693 732741849 286751784 191410838 325269832
304621362 414720753 664922712 506696497 312523039
834022578 541282303 962139996 126515475 43971370
152300688 951053644 442931589 57882493 979861204
447672230 644706927 763027379 136397527 710511029```

### 输出

```
20```

# 题解

## 作者：rainbow_cat (赞：3)

### Part.1 Idea   
一看这个数据范围 $2\le H,W \le 5$ 就知道这道题可以使用暴力解决。计算可得总状态数为 $5! \times 5!=14400$ 种，我们使用一种 $O(n!m! \times nm)$ 的算法。    
我们用 $p_i$ 表示现在的第 $i$ 行原来的行数，$q_i$ 表示现在的第 $i$ 列原来的列数。对 $p$ 和 $q$ 分别求下一个排列并判断最小值即可。   
### Part.2 Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0x7f7f7f7f,num,a[6][6],b[6][6],p[6]={0,1,2,3,4,5},q[6]={0,1,2,3,4,5};
bool check(int x[6][6],int y[6][6])//判断是否相同
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(x[p[i]][q[j]]!=y[i][j])
				return 0;
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>b[i][j];
	do//由于不改变也是也是一种可能所以使用 do while
	{
		do
		{
			if(!check(a,b))continue;
			num=0;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					num+=(i<j&&p[i]>p[j]);//逆序对的数量就是交换次数
			for(int i=1;i<=m;i++)
				for(int j=1;j<=m;j++)
					num+=(i<j&&q[i]>q[j]);
			ans=min(ans,num);
		}while(next_permutation(q+1,q+m+1));//next_premutation 表示下一个排列		
	}while(next_permutation(p+1,p+n+1));
	if(ans==0x7f7f7f7f)ans=-1;
	cout<<ans;
	return 0;
}
```
### Part.3 additional information
代码中 $n$ 是题目中的 $H$，$m$ 是题目中的 $W$。    
[oiwiki 中的 `next_permutation`](https://oi-wiki.org/lang/csl/algorithm/)

---

## 作者：Phartial (赞：2)

以下记 $\pi(p)$ 表示排列 $p$ 的逆序对个数。

首先显然行和列相互独立。假设初始时 $A$ 的行编号为 $(1,2,\cdots,H)$，则将其变为 $(p_1,p_2,\cdots,p_H)$（其中 $p$ 是一个 $1\sim H$ 的排列）的最小操作次数是 $\pi(p)$（显然你每次交换最多只会减少一对逆序对），列编号同理。

考虑枚举行编号的最终形态 $(p_1,p_2,\cdots,p_H)$ 与列编号的最终形态 $(q_1,q_2,\cdots,q_W)$，设 $A'$ 是变换后的矩阵，则有 $A'_{i,j}=A_{p_i,q_j}$，且变换到 $A'$ 的最小操作次数为 $\pi(p)+\pi(q)$，校验 $A'$ 是否和 $B$ 相等并更新答案即可。

时间复杂度 $\mathcal{O}(N!^2N^2)$ 或 $\mathcal{O}(N!^2N\log N)$，其中 $N=\max(H,W)$。

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

const int kN = 6;

int n, m, a[kN][kN], b[kN][kN], p[kN], q[kN], ans = 114514;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> b[i][j];
    }
  }
  iota(p + 1, p + n + 1, 1);
  do {
    int cp = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j < i; ++j) {
        cp += p[i] < p[j];
      }
    }
    iota(q + 1, q + m + 1, 1);
    do {
      int cq = 0;
      for (int i = 1; i <= m; ++i) {
        for (int j = 1; j < i; ++j) {
          cq += q[i] < q[j];
        }
      }
      bool f = 1;
      for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
          f &= a[p[i]][q[j]] == b[i][j];
        }
      }
      if (f) {
        ans = min(ans, cp + cq);
      }
    } while (next_permutation(q + 1, q + m + 1));
  } while (next_permutation(p + 1, p + n + 1));
  cout << (ans == 114514 ? -1 : ans);
  return 0;
}
```

---

## 作者：FiraCode (赞：1)

## 思路:

考虑每次枚举交换哪一行或那一列，然后用 `vector` 来模拟，拿 `map` 来去重即可。

## Code：
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> a, b;
map<vector<vector<int>>, int> ma;

void bfs() {
	queue<pair<vector<vector<int>>, int>> q;
	q.push({a, 0});
	while (q.size()) {
		auto t = q.front().first;
		auto d = q.front().second;
		q.pop();
		if (t == b) {
			printf("%d\n", d);
			exit(0);
		}
		for (int i = 0; i < n - 1; ++i) {
			swap(t[i], t[i + 1]);
			if (!ma.count(t)) {
				ma[t] = 1;
				q.push({t, d + 1});
			}
			swap(t[i], t[i + 1]);
		}
		for (int i = 0; i < m - 1; ++i) {
			for (int j = 0; j < n; ++j) {
				swap(t[j][i], t[j][i + 1]);
			}
			if (!ma.count(t)) {
				ma[t] = 1;
				q.push({t, d + 1});
			}
			for (int j = 0; j < n; ++j) {
				swap(t[j][i], t[j][i + 1]);
			}
 		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	a.resize(n);
	for (int i = 0; i < n; ++i) {
		a[i].resize(m);
		for (int j = 0; j < m; ++j) scanf("%d", &a[i][j]);
	}
	b.resize(n);
	for (int i = 0; i < n; ++i) {
		b[i].resize(m);
		for (int j = 0; j < m; ++j) scanf("%d", &b[i][j]);
	}

	bfs();

	puts("-1");
	return 0;
}
```

---

## 作者：OldDriverTree (赞：1)

# Solution

考虑枚举行和列的交换后位置的全排列。

交换次数就是行的逆序对个数加列的逆序对个数。

对合法的方案取个最小值即可。

时间复杂度 $O(H!W!HW)$。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
int n,m,a[6][6],b[6][6];
int ans,row[6],col[6];

bool judge()
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (a[row[i] ][col[j] ]^b[i][j])
				return false;
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&b[i][j]);
	
	for (int i=1;i<=n;i++) row[i]=i;
	for (int i=1;i<=m;i++) col[i]=i;
	ans=1e9;
	do {
		do {
			int cnt=0;
			for (int i=1;i<=n;i++)
				for (int j=1;j<i;j++)
					if (row[i]<row[j]) cnt++;
			
			for (int i=1;i<=m;i++)
				for (int j=1;j<i;j++)
					if (col[i]<col[j]) cnt++;
			
			if (judge() ) ans=min(ans,cnt);
		}while(next_permutation(col+1,col+m+1) );
	}while (next_permutation(row+1,row+n+1) );
	printf("%d",ans>1e8?-1:ans);
	return 0;
}
```

---

## 作者：cjh20090318 (赞：1)

这题可能是 ABC 的 D 题里面难度的中等偏上，感觉确实和其他的 D 题相比有点难以实现。

## 题意

给两个 $H \times W$ 的矩阵 $A$ 和 $B$。

你可以对 $A$ 矩阵交换相邻两行或相邻两列若干次。

输出 $A$ 变换为 $B$ 的最小操作次数，如果不能则输出 `-1`。

## 分析

$2 \le H,W \le 5$，提醒着我们这个算法可能有一个指数级或者阶乘级的复杂度。

根据[冒泡排序](https://oi-wiki.org/basic/bubble-sort/)我们可以知道交换相邻两个数可以做到这个数列的任何一个全排列，而这样的一个操作代价就是这个序列的逆序对数量。

所以我们直接枚举行的全排列和列的全排列即可（枚举全排列可以使用 [`std::next_permutation`](https://zh.cppreference.com/w/cpp/algorithm/next_permutation) 实现）。

时间复杂度 $O(H!W!)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n,m;
int a[10][10],b[10][10];
int c[10][10];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++) scanf("%d",&a[i][j]),c[i][j]=a[i][j];
	for(int i=0;i<n;i++)for(int j=0;j<m;j++) scanf("%d",&b[i][j]);
	int ans=-1;
	vector<int> v(n);//枚举行的全排列。
	for(int i=0;i<n;i++) v[i]=i;
	do{
		int now=0;
		for(int i=0;i<n;i++)for(int j=0;j<m;j++){
			c[v[i]][j]=a[i][j];
		}
		for(int i=0;i<n;i++)for(int j=i-1;j>=0;j--)now+=v[j]>v[i];//计算行的逆序对。
		vector<int> w(m);//枚举列的全排列。
		for(int i=0;i<m;i++) w[i]=i;
		int tmp=-1;
		do{
			bool sol=1;
			for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(c[i][w[j]]!=b[i][j]){sol=0;break;}//判断操作后相等。
			if(sol){
				int ts=0;
				for(int i=0;i<m;i++)for(int j=i-1;j>=0;j--)ts+=w[j]>w[i];//计算列的逆序对。
				if(~tmp) tmp=min(tmp,ts);
				else tmp=ts;
			}
		}while(next_permutation(w.begin(),w.end()));
		if(~tmp){
			if(~ans) ans=min(ans,now+tmp);
			else ans=now+tmp;
		}
	}while(next_permutation(v.begin(),v.end()));
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：qejwdi (赞：1)

我们考虑最后行和列的位置。

那么一共有 $5! \times 5!$ 种情况，设行的排列为 $P$，列的排列为 $Q$，那么原来的 $A_{i,j}$ 此时就是 $A_{P_i,Q_j}$，那么枚举一下 $P,Q$，然后判断一下即可。

然后是怎么计算对于 $P,Q$ 的交换次数，显然就是逆序对的个数，因为每交换一次都会使得逆序对的个数减少 1。

---

## 作者：aCssen (赞：1)

### Solution
本文中的 $n,m$ 即是原题面中的 $w,h$。

$n$ 与 $m$ 都很小，考虑爆搜，问题在于爆搜要怎么写，每次枚举进行的操作肯定不行，因为这样不仅不能保证最优时间复杂度也相当炸裂。

换种思路，因为交换都是整行整列进行，所以考虑爆搜第一个矩阵中的第 $i$ 行最后变为了第几行，显然这是 $1 \sim n$ 的排列，第 $j$ 列最后变为了第几列，显然这是 $1 \sim m$ 的排列，因此爆搜就可以用两重枚举全排列实现。

这样的优势就在于枚举方案和检验合法性都非常容易，接下来考虑如何计算从初始状态到当前状态的操作数，因为行与列互不干扰，所以分开计算。

没有进行任何操作时，第 $i$ 行对应的就是第 $i$ 行，第 $j$ 列对应的就是第 $j$ 列，因此，我们可以认为开始时，两个排列是**有序的**。

然后从初始状态到当前状态的操作数显然等于从当前状态到初始状态的操作数，那么问题就变为：

> 给你一个排列，每次可以交换相邻的两个数，求将其从小到大排序的操作数。

这个问题的答案就是序列的逆序对数，证明平凡，因此统计两组排列的逆序对再相加数即可，在这种数据范围下，想怎么求就怎么求。

注意内层全排列开始时要初始化，以及求逆序对不要写错变量名。

时间复杂度 $\mathcal{O}(n!m!(nm+n^2+m^2))$。
### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
int a[10][10],b[10][10],p1[10],p2[10],n,m,ans=1e9;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&b[i][j]);
	for(int i=1;i<=n;i++) p1[i]=i;
	do{
		for(int k=1;k<=m;k++) p2[k]=k;
		do{
			bool f=true;
            for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					if(a[i][j]!=b[p1[i]][p2[j]]) f=false;
			if(f){
				int val=0;
				for(int i=1;i<=n;i++)
					for(int j=i+1;j<=n;j++)
						if(p1[i]>p1[j]) val++;
				for(int i=1;i<=m;i++)
					for(int j=i+1;j<=m;j++)
						if(p2[i]>p2[j]) val++;
				ans=min(ans,val);
			}
		}while(next_permutation(p2+1,p2+m+1));
	}while(next_permutation(p1+1,p1+n+1));
	if(ans==1000000000) printf("-1");
	else printf("%d",ans);
	return 0;
}
```

---

## 作者：BYR_KKK (赞：0)

显然，我们可以将行和列分开考虑。

结合起数据范围，我们可以分别枚举行、列的全排列。如果按照这种全排列能够得到目标排列，这就是一个合法的排列。

统计操作次数只需统计逆序对数即可。

结合代码理解。

**code**

```cpp

#include<bits/stdc++.h>
#define int long long
#define abs aabs

int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	} 
	while(c>='0'&&c<='9') x=x*10+(int)(c-'0'),c=getchar();
	return x*f;
}

int abs(int x){
	if(x>0) return x;
	else return -x;
}

int h,w,hh[6],ww[6];

const int inf=1e18;

int a[10][10],b[10][10];

signed main(){
	h=read(),w=read();
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++) a[i][j]=read();
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++) b[i][j]=read();
	for(int i=1;i<=h;i++) hh[i]=i;
	for(int i=1;i<=w;i++) ww[i]=i;
	int ans=inf;
	do{
		do{
			bool flag=1;
			for(int i=1;i<=h;i++)
				for(int j=1;j<=w;j++){
					if(b[i][j]!=a[hh[i]][ww[j]]) {
						flag=0;
						break;
					}
				}
			if(flag){
				//已经找到合法的序 
				int ret=0,ter=0;
				//赋权后找逆序对
				for(int i=1;i<=h;i++)
					for(int j=i+1;j<=h;j++){
						if(hh[i]>hh[j]) ret++;
					} 
				for(int i=1;i<=w;i++)
					for(int j=i+1;j<=w;j++) if(ww[i]>ww[j]) ret++;
				ans=std::min(ans,ret);
			}
		}while(std::next_permutation(ww+1,ww+w+1));
	}while(std::next_permutation(hh+1,hh+h+1));	
	if(ans==inf) std::printf("-1");
	else std::printf("%lld",ans);
	return 0;
}

```

---

## 作者：CheZiHe929 (赞：0)

# AT_abc332_d 题解

### 题目链接

[Atcoder](https://atcoder.jp/contests/abc332/tasks/abc332_d)

[Luogu](https://www.luogu.com.cn/problem/AT_abc332_d)

### 简要题意

见洛谷题面，已经翻译的很明确了，这里就不加赘述。

### 简要思路

首先注意到：$2 \leq H, W \leq 5$，因此我们可以大胆猜测这是一个很暴力的做法，不难想到全排列，接下来来详细说明一下做法。

用数组 $h$ 记录当前矩阵的第 $i$ 排对应原先 $A$ 矩阵中的第 $h_i$ 排。

用数组 $w$ 记录当前矩阵的第 $i$ 列对应原先 $A$ 矩阵中的第 $w_i$ 列。

全排列枚举每一种交换矩阵的形式，如果符合条件我们就统计当前 $h,w$ 数组中**逆序对**的数量，并和当前答案取最小值。

注：对于一个 $1$ 到 $n$ 每个数只出现一次的序列，如果想让它变成升序排列，那么至少要进行调换的次数为这个序列的**逆序对**的数量。

对于不存在答案的情况，我们只需刚开始时对答案赋一个极大的值，最后判断是否等于该值即可。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
const int INF=1e9+5;

int H,W;
int a[10][10],b[10][10];//a,b 矩阵
int h[10],w[10];//枚举全排列所用数组

signed main(){
	std::cin>>H>>W;
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)std::cin>>a[i][j];
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)std::cin>>b[i][j];
  	
  	for(int i=1;i<=H;i++)h[i]=i;
  	for(int j=1;j<=W;j++)w[j]=j;//初始赋值，注意从小到大
  	
  	int ans=INF;//赋初始较大值
  	do{
  	  	do{
			bool f=true;
			for(int i=1;i<=H;i++)
				for(int j=1;j<=W;j++)
					if(a[h[i]][w[j]]!=b[i][j]){
						f=false;
						break;
					}
   	  		if(f==false)continue;//判断当前矩阵是否等于 b 矩阵

      		int num=0;
      		for(int i=1;i<=H;i++)
				for(int j=1;j<=H;j++)
					if(i<j&&h[i]>h[j])num++;
			for(int i=1;i<=W;i++)
				for(int j=1;j<=W;j++)
					if(i<j&&w[i]>w[j])num++;//交换次数=两个数组的逆序对数量之和
      		ans=std::min(ans,num);//维护答案

    	}while(std::next_permutation(w+1,w+W+1));
  	}while(std::next_permutation(h+1,h+H+1));//全排列枚举每一种交换情况

  	if(ans==INF)std::cout<<-1<<endl;//答案没有变说明不存在答案
  	else std::cout<<ans<<endl;

  	return 0;
}
```

### AC 记录

[Atcoder](https://atcoder.jp/contests/abc332/submissions/48430745)

[Luogu](https://www.luogu.com.cn/record/139250052)

**THE END.**

**THANK YOU.**

---

## 作者：heyx0201 (赞：0)

# ABC332D Swapping Puzzle 题解
这次没打得成，掉灰了。

## Description
> 给定 $H \times W$ 的两个矩阵 $A,B$，每次交换 $A$ 的第 $i$ 行与第 $i+1$ 行（$1 \le i \lt H$），或者 $A$ 的第 $i$ 列和第 $i+1$ 列（$1 \le i \lt W$），求让 $A$ 变成 $B$ 的最小操作次数。

## Solution
数据这么小，直接全排列搜索。搜出两个序列 $v_1, v_2$，长度分别为 $H, W$。开两个用来还原 $v_1, v_2$ 的数组 $ok_1, ok_2$，每次枚举 $1 \le i \le H, 1 \le j \le W$，判断一下 $a_{v_{1_{i}}, v_{2_{j}}}$ 是否等于 $ b_{i,j}$，如果等于，那么统计交换次数，最后更新答案。

流程：

- 全排列
  - $W$ 全排列
    - 判断是否相等
    - 如果相等
      - 统计交换次数
      - 更新答案

## Accept Code
[Accept Record](https://atcoder.jp/contests/abc332/submissions/48420692)
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;

int a[MAXN][MAXN], b[MAXN][MAXN], v1[MAXN], v2[MAXN], n, m,
    ans = INT_MAX, t1[MAXN], t2[MAXN];

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> b[i][j];
    }
  }
  for (int i = 1; i <= n; i++) v1[i] = i;
  do {
    for (int i = 1; i <= m; i++) v2[i] = i;
    do {
      int cnt = 0;
      bool flag = 0;
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          if (a[v1[i]][v2[j]] != b[i][j]) {
            flag = 1;
          }
        }
      }
      if (!flag) {
        for (int i = 1; i <= n; i++) t1[i] = v1[i];
        for (int i = 1; i <= m; i++) t2[i] = v2[i];
        for (int i = 1; i <= n; i++) {
          for (int j = 1; j < n; j++) {
            if (v1[j] > v1[j + 1]) swap(v1[j], v1[j + 1]), cnt++;
          }
        }
        for (int i = 1; i <= m; i++) {
          for (int j = 1; j < m; j++) {
            if (v2[j] > v2[j + 1]) swap(v2[j], v2[j + 1]), cnt++;
          }
        }
        for (int i = 1; i <= n; i++) v1[i] = t1[i];
        for (int i = 1; i <= m; i++) v2[i] = t2[i];
        ans = min(ans, cnt);
      }
    } while (next_permutation(v2 + 1, v2 + m + 1));
  } while (next_permutation(v1 + 1, v1 + n + 1));
  cout << (ans == INT_MAX ? -1 : ans);
  return 0;
}
```

---

## 作者：xz001 (赞：0)

- 这道题有点迷惑人，一眼会让人你以为共有 $(5\times5)!$ 种方案，实际上由于只能交换行和列，故总共只有 $(5!)^2=14400$ 种情况，直接宽度优先搜索寻找最小次数即可。
- 由于宽搜时需要对一个矩阵进行操作，故可以将矩阵其放入一个 ```struct``` 里面并重载上 ```<``` 运算符，即可方便的用 ```map``` 维护步数。
- 代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }



int h, w, ans;




struct node {    
	int t[15][15];
	bool operator < (const node x) const {
		for (int i = 1; i <= h; ++ i)
		    for (int j = 1; j <= w; ++ j)
		        if (t[i][j] != x.t[i][j])
		            return t[i][j] < x.t[i][j];
		
		return false;
	}
	bool operator == (const node x) const {
		for (int i = 1; i <= h; ++ i)
		    for (int j = 1; j <= w; ++ j)
		        if (t[i][j] != x.t[i][j])
		            return false;
		            
		return true;
	}
	void sw (int x, int y) {
		for (int i = 1; i <= h; ++ i) swap(t[i][x], t[i][y]);
		return;
	}
};
map <node, int> p;
node a, b;


signed main() {
    scanf("%lld%lld", &h, &w);
    for (int i = 1; i <= h; ++ i) 
        for (int j = 1; j <= w; ++ j)
            scanf("%lld", &a.t[i][j]);
            
    for (int i = 1; i <= h; ++ i)
        for (int j = 1; j <= w; ++ j)
            scanf("%lld", &b.t[i][j]);
            
    if (a == b) {
    	puts("0");
    	return 0;
	}
            
    queue <node> q;
    
    q.push(a);
    
    p[a] = 0;
    
    while (q.size()) {
    	node u = q.front();
    	q.pop();
    	for (int i = 1; i < h; ++ i) {
    		node tmp = u;
    		swap(tmp.t[i], tmp.t[i + 1]);
    		if (!p.count(tmp)) {
    			p[tmp] = p[u] + 1;
    			q.push(tmp);
    			if (tmp == b) {
    				printf("%lld", p[tmp]);
    				return 0;
				}
			}
		}
		for (int i = 1; i < w; ++ i) {
			node tmp = u;
			tmp.sw(i, i + 1);
			if (!p.count(tmp)) {
				p[tmp] = p[u] + 1;
				q.push(tmp);
				if (tmp == b) {
					printf("%lld", p[tmp]);
					return 0;
				}
			}
		}
	}
	printf("-1");
    
    return 0;
}


```

---

