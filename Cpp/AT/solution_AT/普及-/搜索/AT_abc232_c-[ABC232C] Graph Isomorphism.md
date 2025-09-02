# [ABC232C] Graph Isomorphism

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc232/tasks/abc232_c

高橋君と青木君は、それぞれ $ N $ 個のボールに $ M $ 本のひもを取り付けたおもちゃを持っています。

高橋君のおもちゃにおいて、ボールには $ 1,\ \dots,\ N $ と番号が付けられており、$ i\ \,\ (1\ \leq\ i\ \leq\ M) $ 本目のひもはボール $ A_i $ とボール $ B_i $ を結んでいます。

青木君のおもちゃにおいても同様に、ボールには $ 1,\ \dots,\ N $ と番号が付けられており、$ i\ \,\ (1\ \leq\ i\ \leq\ M) $ 本目のひもはボール $ C_i $ とボール $ D_i $ を結んでいます。

それぞれのおもちゃにおいて、同一のボールを結ぶようなひもは存在せず、$ 2 $ つのボールを $ 2 $ 本以上の異なるひもが結んでいることはありません。

すぬけ君は、$ 2 $ 人のおもちゃが同じ形であるかどうか気になっています。  
 ここで、$ 2 $ 人のおもちゃが同じ形であるとは、以下の条件を満たす数列 $ P $ が存在することをいいます。

- $ P $ は $ (1,\ \dots,\ N) $ を並べ替えて得られる。
- 任意の $ 1 $ 以上 $ N $ 以下の整数 $ i,\ j $ に対し、以下が成り立つ。
  - 高橋君のおもちゃにおいてボール $ i,\ j $ がひもで繋がれていることと、青木君のおもちゃにおいてボール $ P_i,\ P_j $ がひもで繋がれていることは同値である。

$ 2 $ 人のおもちゃが同じ形であるなら `Yes`、そうでないなら `No` と出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 8 $
- $ 0\ \leq\ M\ \leq\ \frac{N(N\ -\ 1)}{2} $
- $ 1\ \leq\ A_i\ \lt\ B_i\ \leq\ N\ \,\ (1\ \leq\ i\ \leq\ M) $
- $ (A_i,\ B_i)\ \neq\ (A_j,\ B_j)\ \,\ (i\ \neq\ j) $
- $ 1\ \leq\ C_i\ \lt\ D_i\ \leq\ N\ \,\ (1\ \leq\ i\ \leq\ M) $
- $ (C_i,\ D_i)\ \neq\ (C_j,\ D_j)\ \,\ (i\ \neq\ j) $
- 入力は全て整数である。

### Sample Explanation 1

高橋君のおもちゃは下図の左側のような形をしており、青木君のおもちゃは下図の右側のような形をしています。 !\[yes1\](https://img.atcoder.jp/ghi/abc232c\_yes1.jpg) 次の図から、$ 2 $ 人のおもちゃが同じ形であることがわかります。例えば $ P\ =\ (3,\ 2,\ 1,\ 4) $ とすると問題文中の条件を満たします。 !\[yes2\](https://img.atcoder.jp/ghi/abc232c\_yes2.jpg)

### Sample Explanation 2

$ 2 $ 人のおもちゃは同じ形ではありません。 !\[no\](https://img.atcoder.jp/ghi/abc232c\_no.jpg)

## 样例 #1

### 输入

```
4 4
1 2
1 3
1 4
3 4
1 3
1 4
2 3
3 4```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 6
1 2
1 3
1 4
3 4
3 5
4 5
1 2
1 3
1 4
1 5
3 5
4 5```

### 输出

```
No```

## 样例 #3

### 输入

```
8 0```

### 输出

```
Yes```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc232_c)

### 思路

由于 $N\le8$，可以用**全排列**解决此题。

先用邻接矩阵存储图，设两个图分别为 $A$ 和 $B$。初始化 $P_i=i$，然后对它进行全排列，代表着 $A_{i,j}$ 对应 $B_{P_{i},P_{j}}$。如果 $P$ 在某种排列下，所有的 $A_{i,j}$ 全部满足 $A_{i,j}=B_{P_{i},P_{j}}$，那么有解。否则在所有的情况下都不满足，则无解。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=10;
bool a[N][N],b[N][N];
int n,m,p[N];
bool check(){
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(a[i][j]!=b[p[i]][p[j]])
				return false;
	return true;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int u=read(),v=read();
		a[u][v]=a[v][u]=true;
	}
	for(int i=1;i<=m;++i){
		int u=read(),v=read();
		b[u][v]=b[v][u]=true;
	}
	for(int i=1;i<=n;++i)
		p[i]=i;
	do{
		if(check())
			return printf("Yes\n"),0;
	}while(next_permutation(p+1,p+n+1));
	printf("No\n");
	return 0;
}
```

---

## 作者：0Io_oI0 (赞：2)

首先注意到数据范围，我们很容易想到这道题可以用全排列 AC。

我们先用邻接矩阵存入图，然后对图进行全排列，然后每次判断如果一样，即 $a_{i,j}=b_{c_{i},c_{j}}$ 那么就输出 ```Yes```，否则输出 ```No```。

$Code$：
```cpp
#include<bits/stdc++.h>
#define I using
#define AK namespace
#define IOI std
#define i_ak return
#define ioi  0
I AK IOI;
bool a[10][10],b[10][10];
int n,m,c[10],u,v;
bool check(){
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i][j]!=b[c[i]][c[j]])return 0;
	return 1;
}
int main(){
    cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		a[u][v]=1;
		a[v][u]=1;
	}
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		b[u][v]=1;
		b[v][u]=1;
	}
	for(int i=1;i<=n;i++)c[i]=i;
	do{
		if(check()){
			puts("Yes");
			i_ak ioi;
        }
    }while(next_permutation(&c[1],&c[n+1]));
	puts("No");
	i_ak ioi;
}
```

---

## 作者：Pyrf_uqcat (赞：1)

这么水的题竟然可以交题解。

题目中 $n \le 8$，一眼全排列。

输入的是图中边的两个端点，考虑到数据范围小，以邻接矩阵存储。

将图进行全排列，判断两张图的每一条边是否完全一致，注意是需要全部满足。如果满足则有解，否则无解。

---

## 作者：jiqihang (赞：1)

### 题目链接
[[ABC232C] Graph Isomorphism](https://www.luogu.com.cn/problem/AT_abc232_c)
### 分析
$N \le 8$，可以用全排列来解决此题。

先用邻接矩阵存储图，设两个图分别为 $A$ 和 $B$。

把 $P_i$ 初始化为 $i$，对他进行全排列，然后分类讨论：

- 如果 $P$ 在某种排列下，**所有**的 $A_{i,j}$ 满足 $A_{i,j}=B_{P_i,P_j}$，则有解。
- 否则在所有的情况下都不满足，则无解。

---

## 作者：Autumn_Dream (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc232_c)

**思路：**

$1\le N\le8$，使用全排列即可。

先用邻接矩阵 $P$ 存储图，初始化 $P_i=i$，然后对 $P$ 进行全排列，可以使用 `next_permutation ()` 函数解决，然后判断 $A_{i,j}$ 与 $B_{P_{i},P_j}$ 是否相等即可。

[判断代码](https://www.luogu.com.cn/paste/ia0jqmho)

---

## 作者：TiAmo_qwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc232_c)


---
## 思路
先看数据：
$$1 \le n \le 8$$
数据很小，可以用**全排列**解决。

用邻接矩阵存储图，初始化 $f_{i} = i$，全排列 $f$，若在某一种排列的情况下，所有 $a_{i,j}$ 都满足 $a_{i,j}=b_{f_{i},f_{j}}$，说明有解，否则无解。


---

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define for(i, a, b) for(int i = (a); i <= (b); i++)
#define rof(i, a, b) for(int i = (a); i >= (b); i--)

const int N = 1e6 + 10;

int a[100][100], b[100][100];
int n, m, f[1000];

int check(){
	for(i, 1, n){
		for(j, 1, n){
			if(a[i][j] != b[ f[i] ][ f[j] ]){
				return 0;
			}
		}
	}
	return 1;
}
 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n >> m;
	
	for(i, 1, m){
		int x, y;
		cin >> x >> y;
		a[x][y] = a[y][x] = 1;
	} 
	for(i, 1, m){
		int x, y;
		cin >> x >> y;
		b[x][y] = b[y][x] = 1;
	} 
	for(i, 1, n){
		f[i] = i;
	}
	
	do{
		if(check()) return puts("Yes"), 0;
	}
	while(next_permutation(f + 1, f + n + 1));
	
	puts("No");
	return 0;
}

```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

一道全排列的水题。

先用邻接矩阵存储图，设图为 $A,B$。初始化 $P _ i = i$ 然后对它进行全排列。

如果 $P$ 在某种排列下，所有的 $A _{i, j}$ 全部满足 $A _{i, j} = B _{P _ i, p _ j}$ ，那么有解。否则无解。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 10 + 10;
bool a[N][N], b[N][N];
int n, m, p[N], u, v;
bool check () {
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			if (a[i][j] != b[p[i]][p[j]]) return false;
	return true;
}
int main () {
	cin >> n >> m;
	for (int i = 1; i <= m; i ++) {
		cin >> u >> v;
		a[u][v] = a[v][u] = true;
	}
	for (int i = 1; i <= m; i ++) {
		cin >> u >> v;
		b[u][v] = b[v][u] = true;
	}
	for (int i = 1; i <= n; i ++) p[i] = i;
	do {
		if (check ()) return cout << "Yes" << endl, 0;
	} while (next_permutation (p + 1, p + n + 1));
	cout << "No" << endl;
	return 0;
}
```

---

## 作者：Nahia (赞：0)

### 思路

> 当我看到题目中的 $N \le 8$ 时，我就已经做出这道题了。

没错，就是用**全排列**。先用邻接矩阵存图，然后对其中一个图进行全排列，每次都判断一下是否一样。如果有，就输出 `Yes`，否则输出 `No`。

### solution

```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[15][15],b[15][15];
int n,m,c[15];
bool check(){
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(a[i][j]!=b[c[i]][c[j]])
				return 0;
	return 1;
}
int main(){
    cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		a[u][v]=a[v][u]=1;
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		b[u][v]=b[v][u]=1;
	}
	for(int i=1;i<=n;i++)
		c[i]=i;
	do{
		if(check()){
			cout<<"Yes\n";
			return 0;
        }
	}while(next_permutation(c+1,c+n+1));
	cout<<"No\n";
	return 0;
}
```

---

