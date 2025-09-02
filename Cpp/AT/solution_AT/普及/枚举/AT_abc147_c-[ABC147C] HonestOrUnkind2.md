# [ABC147C] HonestOrUnkind2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc147/tasks/abc147_c

$ 1 $ から $ N $ までの番号がついた $ N $ 人の人がいます。彼らはみな、必ず正しい証言を行う「正直者」か、真偽不明の証言を行う「不親切な人」のいずれかです。

人 $ i $ は $ A_i $ 個の証言を行っています。人 $ i $ の $ j $ 個目の証言は $ 2 $ つの整数 $ x_{ij} $ , $ y_{ij} $ で表され、$ y_{ij}\ =\ 1 $ のときは「人 $ x_{ij} $ は正直者である」という証言であり、$ y_{ij}\ =\ 0 $ のときは「人 $ x_{ij} $ は不親切な人である」という証言です。

この $ N $ 人の中には最大で何人の正直者が存在し得るでしょうか？

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ <\ =\ N\ <\ =\ 15 $
- $ 0\ \leq\ A_i\ \leq\ N\ -\ 1 $
- $ 1\ \leq\ x_{ij}\ \leq\ N $
- $ x_{ij}\ \neq\ i $
- $ x_{ij_1}\ \neq\ x_{ij_2}\ (j_1\ \neq\ j_2) $
- $ y_{ij}\ =\ 0,\ 1 $

### Sample Explanation 1

人 $ 1 $ と人 $ 2 $ が正直者であり、人 $ 3 $ が不親切な人であると仮定すると、正直者は $ 2 $ 人であり、矛盾が生じません。これが存在し得る正直者の最大人数です。

### Sample Explanation 2

$ 1 $ 人でも正直者が存在すると仮定すると、直ちに矛盾します。

## 样例 #1

### 输入

```
3
1
2 1
1
1 1
1
2 0```

### 输出

```
2```

## 样例 #2

### 输入

```
3
2
2 1
3 0
2
3 1
1 0
2
1 1
2 0```

### 输出

```
0```

## 样例 #3

### 输入

```
2
1
2 0
1
1 0```

### 输出

```
1```

# 题解

## 作者：HoshizoraZ (赞：4)

这题的特别点在于，有一些人说的话**并不是每句都错**，而是对错混杂。

而证言真正有说服力的，只有被确认是「诚实的人」。

暴力枚举每个人 诚实 / 不诚实，并将所有暂定为诚实的人的证言放在一起，观察是否有矛盾。

找到一种信息无矛盾、且诚实人数最多的情况，输出即可。

```cpp
#include <cstring>
#include <cstdio>
#define INF 1e9
#define eps 1e-6
typedef long long ll;

int n, a[50], x[50][50], y[50][50];
int b[50], bb[50], ans;

inline int max(int a, int b){
	return a > b ? a : b;
}

void check(){
	memset(bb, -1, sizeof(bb));
	for(int i = 1; i <= n; i++)
		if(b[i] == 1)				// 是诚实人的前提
			for(int j = 1; j <= a[i]; j++)
				if(b[x[i][j]] != y[i][j]) return;	// 这个诚实人的证言与暂定结果不符，矛盾
	int sum = 0;
	for(int i = 1; i <= n; i++)
		sum += b[i];				// 对合法情况计算答案
	if(ans < sum) ans = sum;
}

void dfs(int k){
	if(k == n){
		check();
		return;
	}
	for(int i = 0; i <= 1; i++){	// 暴力枚举每个人是否诚实
		b[k + 1] = i;
		dfs(k + 1);
	}
}

int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		for(int j = 1; j <= a[i]; j++)
			scanf("%d%d", &x[i][j], &y[i][j]);
	}
	dfs(0);
	printf("%d\n", ans); 

	return 0;
}
```

---

## 作者：SilverLi (赞：0)

首先看到 $1 \le n \le 15$，
想到状压。

因为不诚实的人的话**不一定**是正确的，所以就不判断不诚实的人。

还有几点注意：

1.要将用来存状态的数组初始化为当前状态；

2.当条件与状态不符合时，要舍弃这个状态（比如当前状态的第 $i$ 个人是诚实的，但他的见证中却说另一个在当前状态是诚实的人不诚实）。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=107;
int n,a[N],x[N][N],y[N][N];
int b[N],ch,ans,f;
signed main() {
	cin>>n;
	for(int i=0;i<n;++i) {
		cin>>a[i];
		for(int j=0;j<a[i];++j)	cin>>x[i][j]>>y[i][j];
		for(int j=0;j<a[i];++j)	--x[i][j];
	}
	for(int i=0;i<=(1<<n);++i) {
		memset(b,0,sizeof(b));
		for(int j=0;j<n;++j)	b[j]=(i>>j)&1;
		ch=f=0;
		for(int j=0;j<n;++j) {
			for(int k=0;k<a[j];++k) {
				if(((i>>j)&1)&&y[j][k])	b[x[j][k]]=1;
				if(((i>>j)&1)&&(!y[j][k]))	b[x[j][k]]=0;
				if(b[x[j][k]]&&(!((i>>x[j][k])&1)))	f=1;
				if((!b[x[j][k]])&&((i>>x[j][k])&1))	f=1;
				if(f)	break;
			}
			if(f)	break;
		}
		if(!f)
			for(int j=0;j<n;++j)	ch+=b[j];
		ans=max(ans,ch);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

~~一看数据范围：$N\leq15$ 盲猜 dfs 。~~

直接用 dfs 搜索每个人说谎还是不说谎。

特别的是，可能说谎的人不一定是每句话都说谎的，见到说谎的人就把他的话扔掉。

对于每一种情况，看一下诚实的人的话语是否和实际相符即可。

## _Code_
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=18;
int n;
int x[MAXN][MAXN],y[MAXN][MAXN];
int f[MAXN];
int a[MAXN];
int ans=0;
bool calc(){
	for(int i=1;i<=n;i++)
		if(f[i]==1)
			for(int j=1;j<=a[i];j++)
				if(f[x[i][j]]!=y[i][j])
					return false;
	return true;
}
void dfs(int p,int k){//搜索层，个数
	if(p==n+1){
		if(calc())
			ans=max(ans,k);
		return;
	}
	f[p]=1;
	dfs(p+1,k+1);
	f[p]=0;
	dfs(p+1,k);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=1;j<=a[i];j++)
			cin>>x[i][j]>>y[i][j];
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```


---

