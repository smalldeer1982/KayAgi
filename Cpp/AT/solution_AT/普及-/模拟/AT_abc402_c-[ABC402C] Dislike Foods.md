# [ABC402C] Dislike Foods

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc402/tasks/abc402_c

AtCoder 餐厅使用编号为 $1$ 到 $N$ 的 $N$ 种食材。

同时，餐厅提供编号为 $1$ 到 $M$ 的 $M$ 道菜品。第 $i$ 道菜品使用了 $K_i$ 种食材，具体为食材 $A_{i,1},\ A_{i,2},\ \ldots,\ A_{i,K_i}$。

Snuke 君目前讨厌所有 $N$ 种食材。如果一道菜品使用了至少一种 Snuke 君讨厌的食材，他就不能吃这道菜；反之，如果一道菜品没有使用任何他讨厌的食材，他就可以吃这道菜。

Snuke 君计划用 $N$ 天时间来克服对食材的厌恶。在第 $i$ 天，他会克服对食材 $B_i$ 的厌恶，从此不再讨厌该食材。

对于每个 $i=1,2,\ldots,N$，请计算以下值：
- 在第 $i$ 天 Snuke 君克服对食材 $B_i$ 的厌恶后，他能够吃的菜品数量。

## 说明/提示

### 约束条件

- $1 \leq N \leq 3 \times 10^{5}$
- $1 \leq M \leq 3 \times 10^{5}$
- $1 \leq K_i \leq N$ ($1 \leq i \leq M$)
- 所有 $K_i$ 的总和不超过 $3 \times 10^{5}$
- $1 \leq A_{i,j} \leq N$ ($1 \leq i \leq M$, $1 \leq j \leq K_i$)
- $A_{i,j} \neq A_{i,k}$ ($1 \leq i \leq M$, $j \neq k$)
- $1 \leq B_i \leq N$ ($1 \leq i \leq N$)
- $B_i \neq B_j$ ($i \neq j$)
- 输入中的所有数值均为整数

### 样例解释 1

Snuke 君按以下顺序克服对食材的厌恶：
- 第 $1$ 天：克服食材 $1$。此时所有菜品都包含他讨厌的食材，因此输出 $0$。
- 第 $2$ 天：克服食材 $3$。此时菜品 $4$ 不再包含讨厌的食材，可以食用。其他菜品仍包含讨厌的食材，因此输出 $1$。
- 第 $3$ 天：克服食材 $2$。此时菜品 $1$ 也可以食用了。菜品 $1$ 和 $4$ 可以食用，其他不行，因此输出 $2$。
- 第 $4$ 天：克服食材 $5$。此时菜品 $3$ 也可以食用了。可以食用的菜品为 $1,3,4$，因此输出 $3$。
- 第 $5$ 天：克服食材 $4$。此时菜品 $2$ 也可以食用了。所有菜品都可以食用，因此输出 $4$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5 4
2 1 2
3 3 4 5
3 1 2 5
1 3
1 3 2 5 4```

### 输出

```
0
1
2
3
4```

## 样例 #2

### 输入

```
9 8
1 4
5 6 9 7 4 3
4 2 4 1 3
1 1
5 7 9 8 1 5
2 9 8
1 2
1 1
6 5 2 7 8 4 1 9 3```

### 输出

```
0
0
1
1
1
2
4
6
8```

# 题解

## 作者：John2014 (赞：2)

# AT_abc402_c [ABC402C] Dislike Foods 题解

## 题目大意

有 $N$ 种食材，$M$ 道菜，告诉你每道菜用的食材，和每种食材被克服的时间，让你求第 $i$ 天可以吃到多少种不同的菜。

## 思路

先记录下来每种食材会在哪一天被克服，然后找到每道菜中最晚被克服的时间。注意本题的数据范围 $1 \le N,M \le 3 \times 10^{5}$，开数组会炸。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<vector<int> > a(300010);
int b[300010],m,n,k[300010],ans[300010];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>k[i];
		a[i].resize(k[i]+10); //设置 vector 大小
		for(int j=1;j<=k[i];j++){
			cin>>a[i][j];
		} 
	} 
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		b[x]=i; //记录每种食材在哪天克服
	}
	for(int i=1;i<=m;i++){
		int day=0;
		for(int j=1;j<=k[i];j++){
			day=max(day,b[a[i][j]]); //找到最晚时间
		} 
		ans[day]++;
	} 
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=ans[i];
		cout<<sum<<"\n";
	}
	return 0;
}
```

---

## 作者：wyyinput (赞：1)

## 思路
看到所有 $K_i$ 的总和不超过 $3×10^5$ 这句话，可以想到先记录每个食材可以被吃的时间，算出每道菜最早能被食用的时间。这样时间空间都不会炸。每道菜最早能被食用的时间就是它的所有食材中能被食用时间的最大值。这样时间复杂度就能控制到 $m+k_i$ 的总和，既 $6×10^5$。一道菜现在可以食用，之后也一定可以食用。可以做个前缀和优化时间复杂度。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,q,b[300001],ans[300001];
vector<int>a[300001];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&k);
        while(k--){
            scanf("%d",&q);
            a[i].push_back(q);
        }
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&q);
        b[q]=i;
    }
    for(int i=1;i<=m;i++){
        int l=0;
        for(int j=0;j<a[i].size();j++){
            l=max(l,b[a[i][j]]);
        }
        ++ans[l];
    }
    for(int i=1;i<=n;i++){
        ans[i]+=ans[i-1];
        printf("%d\n",ans[i]);
    }
    return 0;
}
```
[AC记录](https://atcoder.jp/contests/abc402/submissions/65219892)

---

## 作者：kkkcs033 (赞：1)

题意简述

有 $N$ 种食物，每种食物由 $C_i$ 种食物构成。某人开始不喜欢所有食物，但他每天会多喜欢一种食物，求他每天能吃几道菜。

思路不难想到，用数组 ```int c[300005]``` 记录每道菜用了几种食材，```vector<int>a[300005]``` 记录每种食材被哪几道菜使用。

在他克服食材 $x$ 后遍历 $a_x$，如果 ```!--c[a[x][i]]``` 时 ```cnt++```，遍历完输出。切记不要输出后 ```cnt=0```。

朴素的一道模拟就完成了，代码也不长：


```cpp
//码风有点奇怪，勿喷（懒得能不多写就不写了）
#include<bits/stdc++.h>
using namespace std;
vector<int>a[300005];//STL真好用
int c[300005];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m,x,y;cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>y;
		while(y--){
			cin>>x,c[i]++;
			a[x].push_back(i);
		}
	}
	int cnt=0;
	while(n--){
		cin>>x;
		for(int i:a[x]) if(!--c[i]) cnt++;//
		cout<<cnt<<'\n';
	}
	return 0;
}
```

祝神犇们 AtCoder 越打越好！

---

## 作者：LittleAcbg (赞：0)

可以先算出每个食材从什么时候开始能被食用。对每道菜，它的食材可食用时间的最大值就是它最早能被食用的时间。随后，由于一道菜现在可以食用，以后也一定可以食用，所以做个前缀和即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+9;
int n,m,k,a,b,t[N],ans[N];
vector<int> d[N];
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
	{
		cin >> k;
		while (k--)
		{
			cin >> a;
			d[i].push_back(a); // 暂时存储菜品的原料列表
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		cin >> b;
		t[b] = i; // t[b] 表示材料 b 什么时候开始能吃
	}
	for (int i = 1; i <= m; ++i)
	{
		int res = 0;
		for (auto x : d[i]) res = max(res, t[x]); // 对这道菜的所有材料取 max
		++ans[res];
	}
	for (int i = 2; i <= n; ++i) ans[i] += ans[i - 1]; // 前缀和
	for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：0)

求出每种食材被克服的时间，求出每一道菜需要 $t_i$ 的时间才能吃。

对于每一个 $k$：答案为 $\sum\limits_{i=1}^M[t_i\le k]$。

对于 $t$ 数组排个序，每次二分一下就行了（虽然也可以用一个指针扫过去）。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,m,k[N],b[N],p[N],t[N];
vector<int>a[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>k[i];
		int x;
		for(int j=1;j<=k[i];j++)cin>>x,a[i].push_back(x);
	}
	for(int i=1;i<=n;i++)cin>>b[i],p[b[i]]=i;
	for(int i=1;i<=m;i++)
		for(int j=0;j<k[i];j++)
			t[i]=max(t[i],p[a[i][j]]);
	sort(t+1,t+m+1);
	int l=1;
	for(int i=1;i<=n;i++){
		while(l<=m&&t[l]<=i)l++;
		cout<<l-1<<'\n';
	}
	return 0;
}
```

---

## 作者：yyycj (赞：0)

## 题目简述
AtCoder 餐厅有 $N$ 种食材，$M$ 道菜，第 $i$ 道菜由 $K_{i}$ 种食材 $A_{i,1} \sim A_{i,K_{i}}$ 组成。

Snuke 一开始讨厌所有 $N$ 道食材，接下来 $N$ 天，他将在第 $i$ 天克服第 $B_{i}$ 种食材，当一道菜品中的所有食材都被克服后，Snuke 可以吃这道菜。

求对于 $i \in [1,n]$，第 $i$ 天可以吃几道菜。

## 主要思路
由于一道菜必须所有食材克服后才能吃，所以某道菜首次能吃的时间就是这道菜中的每种食材最后出现在 $B$ 中的下标。

记录整数数组 $cnt$，$cnt_{i}$ 表示有 $cnt_{i}$ 道菜**在今天**被克服。记录完后，将 $cnt$ 进行一次前缀和便是此题的答案。

## AC Code
```cpp
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
typedef long double db;
const int N = 3e5 + 10;
const int INT_INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
// ----------------------------

// ----------------------------
int pos[N], ans[N];
vector<int> vec[N];
// ----------------------------


int main() {
	int n, m, k, a, b; cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> k;
		for (int _ = 1; _ <= k; _++) {
			cin >> a;
			vec[i].push_back(a);
		}
	}
	for (int i = 1; i <= n; i++) {
		cin >> b;
		pos[b] = i;
	}
	// ----------------------------
	int maxn;
	for (int i = 1; i <= m; i++) {
		maxn = 0;
		for (int j : vec[i]) maxn = max(maxn, pos[j]);
		ans[maxn]++;
	}
	// ----------------------------
	for (int i = 1; i <= n; i++) {
		ans[i] += ans[i - 1];
		cout << ans[i] << endl;
	}
	return 0;
}
```

---

