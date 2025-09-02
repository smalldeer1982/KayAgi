# 题目信息

# [ARC133C] Row Column Sums

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc133/tasks/arc133_c

$ H $ 行 $ W $ 列からなるマス目があります．

すぬけくんは，各マスに $ 0 $ 以上 $ K-1 $ 以下の整数を書き込もうとしています． ここで，以下の条件を満たす必要があります．

- 各 $ 1\ \leq\ i\ \leq\ H $ について，$ i $ 行目にあるマスに書かれた整数の総和を $ K $ で割った余りは $ A_i $ である．
- 各 $ 1\ \leq\ i\ \leq\ W $ について，$ i $ 列目にあるマスに書かれた整数の総和を $ K $ で割った余りは $ B_i $ である．

条件を満たすようにマスに整数を書き込むことができるかどうか判定し，また可能な場合は，書き込む整数の総和としてありうる最大値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 200000 $
- $ 2\ \leq\ K\ \leq\ 200000 $
- $ 0\ \leq\ A_i\ \leq\ K-1 $
- $ 0\ \leq\ B_i\ \leq\ K-1 $
- 入力される値はすべて整数である

### Sample Explanation 1

以下のように書き込めば良いです． ``` ----------------- | 2 | 0 | 2 | 2 | ----------------- | 2 | 2 | 0 | 1 | ----------------- ``` この書き方は条件を満たしています． 例えば $ 1 $ 行目に書かれた整数の総和は $ 6 $ であり，これを $ K(=3) $ で割ったあまりは $ A_1(=0) $ になっています． この書き方では整数の総和は $ 11 $ になっており，これはありうる最大値です．

## 样例 #1

### 输入

```
2 4 3

0 2

1 2 2 0```

### 输出

```
11```

## 样例 #2

### 输入

```
3 3 4

0 1 2

1 2 3```

### 输出

```
-1```

# AI分析结果

### 题目翻译
# [ARC133C] Row Column Sums

## 题目描述

有一个 $H$ 行 $W$ 列的网格。

Snuke 想要在每个格子中填入 $0$ 到 $K-1$ 之间的整数，并且需要满足以下条件：

- 对于每个 $1 \leq i \leq H$，第 $i$ 行中所有格子中的整数之和对 $K$ 取模的结果等于 $A_i$。
- 对于每个 $1 \leq i \leq W$，第 $i$ 列中所有格子中的整数之和对 $K$ 取模的结果等于 $B_i$。

请判断是否存在满足条件的填数方案，如果存在，求出所有格子中整数之和的最大值。

## 说明/提示

### 约束

- $1 \leq H, W \leq 200000$
- $2 \leq K \leq 200000$
- $0 \leq A_i \leq K-1$
- $0 \leq B_i \leq K-1$
- 输入的所有值都是整数

### 样例解释 1

以下是一种满足条件的填数方案：
```
-----------------
| 2 | 0 | 2 | 2 |
-----------------
| 2 | 2 | 0 | 1 |
-----------------
```
例如，第 $1$ 行中所有格子中的整数之和为 $6$，对 $K(=3)$ 取模的结果为 $A_1(=0)$。这种填数方案下，所有格子中的整数之和为 $11$，这是可能的最大值。

## 样例 #1

### 输入
```
2 4 3

0 2

1 2 2 0
```

### 输出
```
11
```

## 样例 #2

### 输入
```
3 3 4

0 1 2

1 2 3
```

### 输出
```
-1
```

### 算法分类
数学、构造

### 题解分析与结论
本题的核心在于如何通过数学推导和构造方法，判断是否存在满足条件的填数方案，并求出最大可能的整数之和。所有题解都基于以下关键思路：

1. **无解条件**：如果所有行的和与所有列的和在对 $K$ 取模的意义下不同余，则无解。
2. **最大和构造**：将所有格子初始化为 $k-1$，然后通过减去必要的值来满足行和列的条件。
3. **最终答案**：最大和为 $n \times m \times (k-1) - \max(\sum c, \sum d)$，其中 $\sum c$ 和 $\sum d$ 分别是行和列需要减去的总和。

### 所选题解
#### 题解1：mountain_climber (4星)
- **关键亮点**：详细解释了如何通过减去必要的值来满足行和列的条件，并证明了最终答案的正确性。
- **代码实现**：通过计算每行和每列需要减去的值，最终输出最大和。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,k,aa,bb;
int main(){
	cin>>n>>m>>k;
	for(int i=0;i<n;i++){
		long long t;
		cin>>t;
		aa+=(m*(k-1)-t)%k;
	}
	for(int i=0;i<m;i++){
		long long t;
		cin>>t;
		bb+=(n*(k-1)-t)%k;
	}
	if(aa%k!=bb%k) cout<<-1<<endl; 
	else cout <<n*m*(k-1)-max(aa,bb)<<endl; 
	return 0;
}
```

#### 题解2：anonymous_Y (4星)
- **关键亮点**：简洁明了地解释了无解条件和最大和的构造方法。
- **代码实现**：通过计算每行和每列需要减去的值，最终输出最大和。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,k,aa,bb;
int main(){
	cin>>n>>m>>k;
	for(int i=0;i<n;i++){
		long long t;
		cin>>t;
		aa+=(m*(k-1)-t)%k;
	}
	for(int i=0;i<m;i++){
		long long t;
		cin>>t;
		bb+=(n*(k-1)-t)%k;
	}
	if(aa%k!=bb%k) cout<<-1<<endl; 
	else cout <<n*m*(k-1)-max(aa,bb)<<endl; 
	return 0;
}
```

#### 题解3：Nuclear_Fish_cyq (4星)
- **关键亮点**：详细解释了如何通过减去必要的值来满足行和列的条件，并证明了最终答案的正确性。
- **代码实现**：通过计算每行和每列需要减去的值，最终输出最大和。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
#define mod 998244353
#define lwbd lower_bound
#define upbd upper_bound
//#define range
using namespace std;
void read(int &x){
	cin >> x;
	return;
}
void readll(ll &x){
	cin >> x;
	return;
}void readdb(db &x){
	cin >> x;
	return;
}
ll n, m, k, sa, sb;

//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 0; i < n; i++){
		ll t;
		cin >> t;
		sa += (m * (k - 1) - t) % k;
	}
	for(int i = 0; i < m; i++){
		ll t;
		cin >> t;
		sb += (n * (k - 1) - t) % k;
	}
	if(sa % k != sb % k){
		cout << -1 << endl;
	}
	else{
		cout << n * m * (k - 1) - max(sa, sb) << endl;
	}
	return 0;
}
```

### 最优关键思路
1. **无解条件**：首先检查所有行的和与所有列的和在对 $K$ 取模的意义下是否同余，若不同余则无解。
2. **最大和构造**：将所有格子初始化为 $k-1$，然后通过减去必要的值来满足行和列的条件。
3. **最终答案**：最大和为 $n \times m \times (k-1) - \max(\sum c, \sum d)$，其中 $\sum c$ 和 $\sum d$ 分别是行和列需要减去的总和。

### 可拓展之处
类似的问题可以通过数学推导和构造方法来解决，特别是在涉及模运算和最大化/最小化问题时。类似的题目包括矩阵填充、模运算约束下的优化问题等。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

---
处理用时：43.75秒