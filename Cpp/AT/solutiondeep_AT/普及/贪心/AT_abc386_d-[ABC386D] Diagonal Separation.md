# 题目信息

# [ABC386D] Diagonal Separation

## 题目描述

有一个 $N \times N$ 的网格，高桥君希望将每个格子涂成黑色或白色，并满足以下条件：

- 对于每一行，存在一个整数 $i$（$0 \leq i \leq N$），该行从左到右的前 $i$ 个格子是黑色，其余的为白色。
- 对于每一列，存在一个整数 $i$（$0 \leq i \leq N$），该列从上到下的前 $i$ 个格子是黑色，其余的为白色。

目前已有 $M$ 个格子被涂上了颜色。具体来说，第 $i$ 个被涂色的格子位于第 $X_i$ 行、第 $Y_i$ 列。如果 $C_i$ 为 `B`，表示该格子已经被涂黑；如果 $C_i` 为 `W`，则表示该格子已经被涂白。

请判断剩下的 $N^2 - M$ 个格子是否可以通过适当选择颜色来满足上述所有条件。

## 说明/提示

- $1 \leq N \leq 10^9$
- $1 \leq M \leq \min(N^2, 2 \times 10^5)$
- $1 \leq X_i, Y_i \leq N$
- 任意两个不同的 $i$，$(X_i, Y_i) \neq (X_j, Y_j)$
- $C_i$ 为 `B` 或 `W`

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 3

4 1 B

3 2 W

1 3 B```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2

1 2 W

2 2 B```

### 输出

```
No```

## 样例 #3

### 输入

```
1 1

1 1 W```

### 输出

```
Yes```

## 样例 #4

### 输入

```
2289 10

1700 1083 W

528 967 B

1789 211 W

518 1708 W

1036 779 B

136 657 B

759 1497 B

902 1309 B

1814 712 B

936 763 B```

### 输出

```
No```

# AI分析结果

### 题目内容重写
【题目内容】
# [ABC386D] Diagonal Separation

## 题目描述

有一个 $N \times N$ 的网格，高桥君希望将每个格子涂成黑色或白色，并满足以下条件：

- 对于每一行，存在一个整数 $i$（$0 \leq i \leq N$），该行从左到右的前 $i$ 个格子是黑色，其余的为白色。
- 对于每一列，存在一个整数 $i$（$0 \leq i \leq N$），该列从上到下的前 $i$ 个格子是黑色，其余的为白色。

目前已有 $M$ 个格子被涂上了颜色。具体来说，第 $i$ 个被涂色的格子位于第 $X_i$ 行、第 $Y_i$ 列。如果 $C_i$ 为 `B`，表示该格子已经被涂黑；如果 $C_i` 为 `W`，则表示该格子已经被涂白。

请判断剩下的 $N^2 - M$ 个格子是否可以通过适当选择颜色来满足上述所有条件。

## 说明/提示

- $1 \leq N \leq 10^9$
- $1 \leq M \leq \min(N^2, 2 \times 10^5)$
- $1 \leq X_i, Y_i \leq N$
- 任意两个不同的 $i$，$(X_i, Y_i) \neq (X_j, Y_j)$
- $C_i$ 为 `B` 或 `W`

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 3

4 1 B

3 2 W

1 3 B```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2

1 2 W

2 2 B```

### 输出

```
No```

## 样例 #3

### 输入

```
1 1

1 1 W```

### 输出

```
Yes```

## 样例 #4

### 输入

```
2289 10

1700 1083 W

528 967 B

1789 211 W

518 1708 W

1036 779 B

136 657 B

759 1497 B

902 1309 B

1814 712 B

936 763 B```

### 输出

```
No```

### 题解分析与结论

本题的核心在于判断给定的黑白格子是否满足每行和每列的分段涂色条件。具体来说，需要确保每个白色格子的右下方没有黑色格子，否则会导致矛盾。

#### 关键思路与技巧
1. **排序与贪心**：通过将格子按行和列排序，可以简化问题的处理。贪心地维护最左侧的白色格子的列值，确保黑色格子不会出现在其右下方。
2. **二分查找与后缀最大值**：通过二分查找快速定位符合条件的黑色格子，并利用后缀最大值数组来判断是否存在矛盾。
3. **离散化与树状数组**：对于需要频繁查询和更新的场景，离散化和树状数组的结合可以高效地处理数据。

#### 最优思路总结
最优的解决思路是结合排序、贪心、二分查找和后缀最大值的方法。首先对所有格子按行和列排序，然后维护一个最左侧的白色格子的列值，通过二分查找和后缀最大值数组来判断是否存在矛盾。这种方法的时间复杂度为 $O(M \log M)$，能够高效地处理大规模数据。

### 高星题解推荐

#### 题解1：作者：xiaoke2021 (赞：7)
- **星级**：★★★★★
- **关键亮点**：通过排序和贪心策略，维护最左侧的白色格子的列值，确保黑色格子不会出现在其右下方。代码简洁高效，思路清晰。
- **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct T{
	int x,y;
	char c;
}node[200000+5];
int n,m;
int wy=2147483647; // 维护的值，初始设为无穷大
bool cmp(T a,T b){
	if(a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		char c;
		cin>>node[i].x>>node[i].y>>node[i].c;
	}
    sort(node+1,node+1+m,cmp); // 结构体排序
	for(int i=1;i<=m;i++){
		if(node[i].c=='W') wy=min(wy,node[i].y); // 是白色就维护最左侧的白色方块的列的值
		else if(node[i].y>=wy){ // 是黑色就判断是否合法
			cout<<"No";
			return 0;
		}
	}
    cout<<"Yes";
	return 0;
}
```

#### 题解2：作者：LionBlaze (赞：5)
- **星级**：★★★★☆
- **关键亮点**：通过二分查找和后缀最大值数组，高效判断是否存在矛盾。代码结构清晰，逻辑严谨。
- **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
class black { public: int x, y; } blacks[200005];
class white { public: int x, y; } whites[200005];
int ymax[200005];
int main() {
	int n, m; scanf("%d%d", &n, &m);
	int bcur = 0, wcur = 0;
	for(int i=1;i<=m;i++) {
		int x, y; scanf("%d%d", &x, &y); getchar(); char c = getchar();
		if(c == 'B') blacks[++bcur] = {x, y}; else whites[++wcur] = {x, y};
	}
	sort(blacks + 1, blacks + bcur + 1, [](const black &x, const black &y) { return x.x < y.x; });
	sort(whites + 1, whites + wcur + 1, [](const white &x, const white &y) { return x.x < y.x; });
	for(int i=bcur;i>=1;i--) ymax[i] = max(ymax[i+1], blacks[i].y);
	int bptr = 0;
	for(int i=1;i<=wcur;i++) {
		while(blacks[bptr].x < whites[i].x) bptr++;
		if(ymax[bptr] >= whites[i].y) { printf("No\n"); return 0; }
	}
	printf("Yes\n");
	return 0;
}
```

#### 题解3：作者：_zqh_ (赞：1)
- **星级**：★★★★☆
- **关键亮点**：通过二分查找和后缀最大值数组，高效判断是否存在矛盾。代码结构清晰，逻辑严谨。
- **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, tb, tw, mx[N];
pair<int, int> B[N], W[N];
void solve() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int l, r; char c; cin >> l >> r >> c;
		if (c == 'B') B[++tb] = {l, r}; else W[++tw] = {l, r};
	}
	sort(B + 1, B + tb + 1);
	for (int i = tb; i >= 1; i--) mx[i] = max(mx[i + 1], B[i].second);
	for (int i = 1; i <= tw; i++) {
		int t = lower_bound(B + 1, B + tb + 1, W[i]) - B;
		if (mx[t] >= W[i].second) return cout << "No", void();
	}
	cout << "Yes";
}
int main() { solve(); return 0; }
```

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：67.75秒