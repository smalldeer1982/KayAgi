# Permutation of Given

## 题目描述

You were given only one number, $ n $ . It didn't seem interesting to you, so you wondered if it's possible to come up with an array of length $ n $ consisting of non-zero integers, such that if each element of the array is replaced by the sum of its neighbors (the elements on the ends are replaced by their only neighbors), you obtain a permutation of the numbers in the original array.

## 说明/提示

In the first test, the array \[ $ 1, 2, -2, -1 $ \] is suitable, because if each element is replaced by the sum of its neighbors, the resulting array is \[ $ 2, -1, 1, -2 $ \], which is a permutation of the original array.

In the second test, it can be shown that there is no solution.

## 样例 #1

### 输入

```
4```

### 输出

```
YES
1 2 -2 -1```

## 样例 #2

### 输入

```
5```

### 输出

```
NO```

# 题解

## 作者：良心WA题人 (赞：6)

## 思路

考虑序列的最后四个数，我们假设已经构造出 $n-2$ 的情况且最后两个数为 $p,q$，令新加的两个数为 $x,y$。有：

$$b_{n-2}=p+x,b_{n-1}=q+y,b_{n}=x$$

其他的并没有发生变化，不作考虑。

我们让 $b_n$ 对应上 $a_{n-1}$，则之前 $b_{n-2}$ 对应的 $a_{n-3}=p$ 和 $b_n=y$ 无法对应以外，其他的全部都成功对应。

考虑让目前没有对应的 $b_{n-2}$ 和 $b_{n-1}$ 分别对应这两个。显然只有一种解：

$\left\{\begin{matrix} 
  x=-q\\  
  y=p-q 
\end{matrix}\right.$。

接下来只需要考虑任意时刻都不为 $0$ 即可。我们将式子多拆几次，会发现会产生循环，且只要 $p\not=0\wedge q\not=0\wedge p\not=q$ 则中间一定不会出现 $0$。

那么对于偶数，因为 $n=2$ 任意情况都成立，只需要随便找两个满足上述条件的 $a_1$ 和 $a_2$ 即可。

然而奇数出题人很阴险没给 $n=7$ 的样例，其实是有解的，我们 ~~WA 了后蒯 CF 的输出~~手玩一下，随便弄一组解就好。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=1e6+4;
int a[NN];
int main()
{
	int n;
	scanf("%d",&n);
	if(n==3||n==5)
	{
		printf("NO");
		return 0;
	}
	if(!(n%2))
	{
		a[1]=1,a[2]=2;
		for(int i=3;i<=n;i+=2)
		{
			a[i]=-a[i-1];
			a[i+1]=a[i-2]-a[i-1];
		}
	}
	else
	{
		a[1]=-5,a[2]=8,a[3]=1,a[4]=-3,a[5]=-4,a[6]=-2,a[7]=5;
		for(int i=8;i<=n;i+=2)
		{
			a[i]=-a[i-1];
			a[i+1]=a[i-2]-a[i-1];
		}
	}
	puts("YES");
	for(int i=1;i<=n;i++)
		printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：代码小明 (赞：6)


## 总体思路

本题通过每次在已知序列中加入 $2$ 个元素的方法，可以构造出满足条件的序列 $A$ ，这里提供一种新的构造方法。

## 性质

因为序列 $A$ 中所有元素构成的可重集与序列 $B$ 中所有元素构成的可重集完全相等，所以 $A$ 中所有元素之和与 $B$ 中所有元素之和相等。
$$
 \sum_{i=1}^{n}B_i=\sum_{i=1}^{n}A_i
$$

题目中除 $A_1$ 和 $A_n$ 以外，所有序列 $A$ 中的元素都对序列 $A$ 元素的总和产生一个两份贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/waxcaphu.png)

可以表示为：

$$
\sum_{i=1}^{n}B_i = A_1+A_n+2 \cdot \sum_{i=2}^{n-1}A_i
$$

经过等量代换，我们发现序列 $A$ 具有这样一个性质

$$
\sum_{i=1}^{n}A_i = A_1+A_n+2 \cdot \sum_{i=2}^{n-1}A_i
$$

$$
\sum_{i=2}^{n-1}A_i=0
$$


## 构造


我们可以由此从已知序列，推出长度比此序列多 $2$ 的新序列，具体方法如下:


我们记已知序列 $A$ 的长度为 $len$。

当我们在一个已知序列 $A$ 加入两个新元素时，假设构造出的新序列 $A'$ 仍然满足条件。

那么根据先前推导的性质，我们可以求出新加入的第一个数：

![](https://cdn.luogu.com.cn/upload/image_hosting/vb5bceyg.png)

$$
A'_{len+1}=0-\sum_{i=2}^{len}A_i
$$


假设已知序列 $B$ 中最后一个元素为 $x$ ，不妨设与它相对应的元素为 $y$。

当我们加入新元素时，会产生新的贡献关系，从而破坏元素 $x$ 和 $y$ 的对应关系。

此时没有元素与 $x$ 对应，又因为元素 $A'_{len+1}$ 已经与 $B'_{len+2}$ 对应，所以只能让元素 $A'_{len+2}$ 与 $x$ 对应：

![](https://cdn.luogu.com.cn/upload/image_hosting/l6071f7d.png)

此时，我们发现除了 $y$ 以外的元素都一一对应，而且通过满足前面推出的性质，我们使两个序列和相等，那么 $B'_{len+1}$ 自然就可以与 $y$ 对应了。

至此，所有元素均完成配对，成功由已知序列 $A$ 构造出比此序列多 $2$ 的新序列 $A'$ ，且 $A'$ 满足题意。

## 实现

我们发现，在 $n<7$ 内不能构造出一组 $n$ 为奇数的序列 $A$ ，此时无解。

所以我们通过构造出两组最短序列 $A$ ，一组 $n$ 为奇数，一组 $n$ 为偶数，按照上文提到的方式构造即可。

$n$ 为偶数：

```cpp
2
-1 1
```

$n$ 为奇数：

```cpp
7
-5 8 1 -3 -4 -2 5
```

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[1000010];
int b[1000010];
int sum[1000010];

void init(){
	if(n%2==0) a[1]=-1,a[2]=1;
	else a[1]=-5,a[2]=8,a[3]=1,a[4]=-3,a[5]=-4,a[6]=-2,a[7]=5;
	for(int i=1;i<=(n%2?7:2);i++){
		if(i!=1) b[i-1]+=a[i];
		b[i+1]+=a[i];
		sum[i]=sum[i-1]+a[i];
	}
}

int main(){
	cin>>n;
	if(n%2&&n<7){
		cout<<"NO"<<endl;
		return 0;
	}
	
	init();
	cout<<"YES"<<endl;
	
	for(int k=(n%2?8:3);k<=n;k+=2){
		
		int s=sum[k-1]-sum[1];//cout<<s<<endl;
		
		a[k]=-s;
		b[k-1]+=a[k];
		b[k+1]+=a[k];
		
		a[k+1]=b[k-1];
		b[k]+=a[k+1];
		b[k+2]+=a[k+1];
		
		sum[k]=sum[k-1]+a[k];
		sum[k+1]=sum[k]+a[k+1];
		
	}
	
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
	
	return 0;
}
```






---

## 作者：言琢დ (赞：4)

## CF1918G Permutation of Given

**本做法可以在有解的情况下，构造出 $|a_i|\le3$ 的解。**

写在前面：如果你着急看答案，可以直接翻到最下面。

---

## Solution

首先写一个答案模拟器：

```cpp
const int N = (int) 1e1 + 5;
int n, a[N], b[N], c[N], ans, LIM;
void go(){
  for (int i = 1; i <= n; ++i) {
    do {
      a[i] = 1 + rand() % LIM;
      if (rand() & 1) a[i] *= -1;
    } while (!a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    if (i == 1) b[i] = a[i+1];
    else if (i == n) b[i] = a[i-1];
    else b[i] = a[i-1] + a[i+1];
    c[i] = a[i];
  }
  std::stable_sort(b + 1, b + 1 + n);
  std::stable_sort(c + 1, c + 1 + n);
  for (int i = 1; i <= n; ++i)
    if (b[i] != c[i]) return;
  for (int i = 1; i <= n; ++i)
    print(a[i]), putchar(' ');
  putchar('\n');
  if (++ans >= 5) exit(0); // 只输出前 5 组解
}
int main(){
  srand(time(NULL));
  n = init();
  for (LIM = 2; LIM <= 10; ++LIM) { // 设定绝对值取值范围
    int T = (int) 1e5;
    while (T--) go();
  }
}
```

然后发现 $n$ 为偶数时，都可以构造出 $|a_i|\le2$ 的解。

### $n=4$

- **`-1 1 -1 -2`**
- `1 2 -2 -1`
- `-2 -1 1 -1`
- `-1 1 -1 -2`
- `-1 1 -1 -2`

### $n=6$

- `-1 -2 -1 1 2 -2`
- `2 -2 -1 1 2 1`
- **`1 -1 1 2 -2 -1`**
- `-1 -2 2 1 -1 1`
- `1 2 -2 -1 1 -1`

### $n=8$

- `-1 -2 2 1 -1 1 -1 -2`
- `1 2 -2 -1 1 -1 1 2`
- **`-1 1 -1 -2 2 1 -1 1`**
- `-1 -2 2 1 -1 1 -1 -2`
- `1 2 -2 -1 1 -1 1 2`

### $n=10$

- **`2 1 -1 1 -1 -2 2 1 -1 1`**

你可能没有听懂我的意思，其实我的意思是说，我想我可能发现了一种可以无限增长的序列。

首先，如果你不认可 **全部取相反数**、**序列整体翻转**，那么我认为我们就没得谈了。

如果 $\{a_n\}$ 是一组合法解，那么 $b_i=-a_i$ 或 $b_i=a_{n-i+1}$ 构成的 $\{b_n\}$ 也一定是一组合法解，并且与 $\{a_n\}$ 本质相同。

基于这种打算，我们观察到 $n$ 为偶数时，这样的序列具有某种神奇的延续关系。

我们把粗体的部分整理出来看看，它们长成了什么样子：

- $n=4$：`-1 1 -1 -2`

- $n=6$：`1 -1 1 2 -2 -1`（将这条序列全部取反）

- $n=8$：`-1 1 -1 -2 2 1 -1 1`（前四个位置与 $n=4$ 完全相同）

- $n=10$：`2 1 -1 1 -1 -2 2 1 -1 1`（将这条序列倒过来看）

也就是说，从 `-1 1` 开始，这个序列可以像这样扩展下去：

| `-1 1` |  |  |  |  |  |  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| `-1 1` | `-1 -2` |  |  |  |  |  |
| `-1 1` | `-1 -2` | `2 1` |  |  |  |  |
| `-1 1` | `-1 -2` | `2 1` | `-1 1` | `-1 -2` |  |  |
| `-1 1` | `-1 -2` | `2 1` | `-1 1` | `-1 -2` | `2 1` |  |
| `-1 1` | `-1 -2` | `2 1` | `-1 1` | `-1 -2` | `2 1` | $\cdots$ |

这样，对于所有 $n$ 为偶数的情况，咱们就都解决啦。

但是还有一个棘手的问题，那就是 $n$ 为奇数。

首先，不加证明地给出 $n=3$ 和 $n=5$ 无解，因为程序跑不出来，这理由很合理吧？

然后我们来看看 $n=7$ 和 $n=9$ 和 $n=11$ 的情况，能给我们带来些什么：

### $n=7$

- `-3 1 2 1 -1 -3 -2`
- `3 -1 -2 -1 1 3 2`
- `2 -1 1 -1 -2 3 3`
- `3 3 -2 -1 1 -1 2`
- `3 3 -2 -1 1 -1 2`
- `-2 1 -1 1 2 -3 -3`
- `-2 -3 -1 1 2 1 -3`
- `-3 1 2 1 -1 -3 -2`

真是个比较遗憾的事情，因为我居然跑不出 $|a_i|\le2$ 的解。但没关系，$|a_i|\le3$ 也不是很难研究。

我们首先把重复的方案进行剔除，比如说翻转对称，或者是取反对称。

- `-3 1 2 1 -1 -3 -2`
- `2 -1 1 -1 -2 3 3`

这个过程直接用肉眼就可以进行剔除。

剔除完了之后，我们尝试让它和 $n=9$ 的解建立类似的联系，因此我们还需要把 $n=9$ 的情况跑出来。

- `-1 2 -2 -3 -1 1 2 1 -3`
- `1 -2 2 3 1 -1 -2 -1 3`

再把 $n=11$ 的解找一找：

- `3 1 -1 2 -2 -3 -1 1 2 1 -3`
- `-1 -1 2 -1 1 3 -2 -2 1 -1 -3`

喜报，$n=9$ 和 $n=11$ 居然都可以找出 $|a_i|\le3$ 的解。

那么我们第一件事当然是把它们和 $n=7$ 的解进行对比：

你别说，这眼力还真的很猛。

把第一条 $n=11$ 的序列翻转：`-3 1 2 1 -1 -3 -2 2 -1 1 3`

正好对上了！

| -3 | 1 | 2 | 1 | -1 | -3 | -2 |  |  |  |  | | | | | | | | |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| -3 | 1 | 2 | 1 | -1 | -3 | -2 | 2 | -1 | 1 | 3 |
 |-3  |1  |2  |1 | -1  |-3  |-2 | 2  |-1 | 1 | 3  |-3  |-2 | 2 | -1 |
 |-3  |1  |2  |1 | -1  |-3  |-2 | 2  |-1 | 1 | 3  |-3  |-2 | 2 | -1 | 1 | 3 | -3 | -2 |

下面的两行，是强行把前面的位置固定下来，然后稍作修改 `go` 函数得到的。（否则碰撞概率太低，根本不可能随得出来）

`go` 函数的第一个 `for` 循环改成这个样子：

```cpp
for (int i = 1; i <= n; ++i) {
  do {
    a[i] = 1 + rand() % LIM;
    if (rand() & 1) a[i] *= -1;
  } while (!a[i]);
  if (i == 2 || i == 4 || i == 10) a[i] = 1;
  if (i == 1 || i == 6 || i == 12) a[i] = -3;
  if (i == 3 || i == 8 || i == 14) a[i] = 2;
  if (i == 5 || i == 9 || i == 15) a[i] = -1;
  if (i == 11) a[i] = 3;
  if (i == 7 || i == 13) a[i] = -2;
}
```

然后就发现了一个循环节。

`-3 1 2 1 -1 -3 -2 2 -1 1 3 -3 -2 2 -1 1 3 -3 -2`

来看第二个 $-3$ 的位置。

$$\begin{aligned}-3 ~1~ 2~ 1~ -1\\ \red{-3 ~-2 ~2 ~-1 ~1 ~3}\\ \blue{-3 ~-2 ~2 ~-1 ~1 ~3} \\~-3 ~-2\cdots\end{aligned}$$

用咱们发现的这条序列，可以秒杀 $n=7$、$n=9$、$n=11$ 的情况。

然后我们把刚才的验证程序改成这个样子：

```cpp
const int N = (int) 2e1 + 5;
int n, a[N] = {0,-3,1,2,1,-1,-3,-2,2,-1,1,3,-3,-2,2,-1,1,3,-3,-2}, b[N], c[N], ans, LIM;
void go(){
  for (int i = 1; i <= n; ++i) {
    if (i == 1) b[i] = a[i+1];
    else if (i == n) b[i] = a[i-1];
    else b[i] = a[i-1] + a[i+1];
    c[i] = a[i];
  }
  std::stable_sort(b + 1, b + 1 + n);
  std::stable_sort(c + 1, c + 1 + n);
  for (int i = 1; i <= n; ++i)
    if (b[i] != c[i]) return;
  for (int i = 1; i <= n; ++i)
    print(a[i]), putchar(' ');
  putchar('\n');
}
int main(){
  srand(time(NULL));
  n = init();
  go();
}
```

也就是直接打表并且进行验证，果不其然！$n\ge7$ 为奇数的情况都可以这么搞！

堪称完美！

## Code

```cpp
#include<cstdio>
int init(){
	char c = getchar();
	int x = 0, f = 1;
	for (; c < '0' || c > '9'; c = getchar())
		if (c == '-') f = -1;
	for (; c >= '0' && c <= '9'; c = getchar())
		x = (x << 1) + (x << 3) + (c ^ 48);
	return x * f;
}
void print(int x){
	if (x < 0) x = -x, putchar('-');
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int N = (int) 1e6 + 5;
int even[N] = {6, -1, 1, -1, -2, 2, 1};
int odd[N] = {11, -3, 1, 2, 1, -1, -3, -2, 2, -1, 1, 3};
int main(){
	int n = init();
	if (n % 2 && n < 7) { puts("No"); return 0; }
	puts("Yes");
	if (n & 1)
		for (int i = 1; i <= n; ++i)
			if (i <= odd[0]) print(odd[i]), putchar(' ');
			else print(odd[i] = odd[i-6]), putchar(' ');
	else
		for (int i = 1; i <= n; ++i)
			if (i <= even[0]) print(even[i]), putchar(' ');
			else print(even[i] = even[i-6]), putchar(' ');
}
```

---

## 作者：chroneZ (赞：2)

考虑增量构造，假定目前我们拥有一个长为 $n$ 的合法序列 $s$。记将 $s$ 的每一项替换为相邻项之和后的序列为 $s'$。

稍作尝试可以发现只新增一个数是不可做的，进而尝试每次新增两个数。此即，

$$
[\dots, a, b] \Rightarrow [\dots, a, b, x, y]
$$

容易发现新增两个数后，$s'$ 中发生变化的只有最后三个数，因此 $x, y$ 仅需要满足 $\{a + x, b + y, x\} = \{a, x, y\}$。简单分类讨论后可以求出一种合法方案：$x = -b, y = a - b$。

显然我们只要找到最小的偶数解与奇数解便可解决本题。通过小范围搜索，可以得知 $[1, 2]$ 与 $[-3, -3, 2, 1, -1, 1, -2]$ 分别是最小的偶数解与奇数解。在此基础上按上述方式增量即可。

如果你使用的不是这两个序列，注意增量后的序列不能含有 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  
  int n; cin >> n;
  // n = 2, res = [1, 2]
  // n = 7, res = [-3, -3, 2, 1, -1, 1, -2]
  if(n == 3 || n == 5) {
    cout << "No\n";
    return 0;
  }
  cout << "Yes\n";
  if(n % 2 == 0) {
    vector<int> res{1, 2};
    for(int i = 2; i < n; i += 2) {
      int a = res[i - 2], b = res[i - 1];
      res.push_back(-b), res.push_back(a - b);
    }
    for(int i = 0; i < n; i++) {
      cout << res[i] << " \n"[i == n - 1];
    }
  } else {
    vector<int> res{-3, -3, 2, 1, -1, 1, -2};
    for(int i = 7; i < n; i += 2) {
      int a = res[i - 2], b = res[i - 1];
      res.push_back(-b), res.push_back(a - b);
    }
    for(int i = 0; i < n; i++) {
      cout << res[i] << " \n"[i == n - 1];
    }
  }
  // Searching out a solution when n is small.
  // auto judge = [&](vector<int> a) {
  //   auto b = a;
  //   b[0] = a[1], b[n - 1] = a[n - 2];
  //   for(int i = 1; i < n - 1; i++) {
  //     b[i] = a[i - 1] + a[i + 1];
  //   }
  //   sort(a.begin(), a.end()), sort(b.begin(), b.end());
  //   for(int i = 0; i < n; i++) {
  //     if(a[i] != b[i]) {
  //       return 0;
  //     }
  //   }
  //   return 1;
  // };
  // vector<int> a(n, 0);
  // function<bool(int)> dfs = [&](int p) {
  //   if(p == n) {
  //     if(judge(a)) {
  //       for(int i = 0; i < n; i++) {
  //         cout << a[i] << " \n"[i == n - 1];
  //       }
  //       return true;
  //     } else {
  //       return false;
  //     }
  //   }
  //   for(int i = -3; i <= 3; i++) {
  //     if(i == 0) {
  //       continue;
  //     }
  //     a[p] = i;
  //     if(dfs(p + 1)) {
  //       return true;
  //     }
  //   }
  //   return false;
  // };
  // dfs(0);
}
```

---

## 作者：LXcjh4998 (赞：1)

[题目链接](https://codeforces.com/problemset/problem/1918/G)
# 题意
~~自己看翻译。~~
# 思路
## 递推
我们先假设对于 $n$，我们构造出了 $1$ 个满足条件的序列 $A$，现在证明可以通过序列 $A$，构造 $1$ 个满足条件的长度为 $n+2$ 序列 $A'$。

对于每个 $A_i$，显然都有 $1$ 个 $B_j$ 与之一一对应。而在添加 $2$ 个数后，$A_{n-1}'$ 就不能与 $B_n'$ 对应了，而变成 $A_{n+1}'$ 与 $B_{n+2}'$ 对应。

现在 $A_{n-1}'$ 和 $A_{n+2}'$ 还没有与 $B'$ 对应，$B_n'=A_{n-1}'+A_{n+1}'$ 和 $B_{n+1}'=A_n'+A_{n+2}'$ 还没有与 $A'$ 对应。

因此，可以令 $\begin{cases}A_{n-1}'+A_{n+1}'=A_{n+2}'&\\A_n'+A_{n+2}'=A_{n-1}'&\end{cases}$，解得 $\begin{cases}A_{n+1}'=-A_n'&\\A_{n+2}'=A_{n-1}'-A_n'&\end{cases}$。

因此，只需令 $\forall1\le i\le n,A_i'=A_i$；$A_{n+1}'=-A_n,A_{n+2}'=A_{n-1}'-A_n'$ 即可。

所以，我们的任务转化为对长度为奇数和偶数求满足条件的基序列。
## 构造基序列
### 偶数
显然，$1,2$ 就是 $1$ 个符合条件的序列。

---
### 奇数
首先先证明没有长度为 $3$ 的符合条件的序列（长度为 
$5$ 的序列样例就有，不予证明）。

首先，显然有 $B_1=A_2=B_3=a$，由于序列 $B$ 已经有 $2$ 个 $a$，所以序列 $A$ 中也至少有 $2$ 个 $a$。

不妨设 $A_1=a,A_3=b$，则有 $b=A_3=B_2=A_1+A_3=a+b$，即 $a=0$，矛盾。

所以没有长度为 $3$ 的符合条件的序列。

---
现在要构造一个长度为 $7$ 的符合条件的序列。

我们不妨令
$$\begin{cases}A_1+A_3=A_5&\\A_2+A_4=A_7&\\A_3+A_5=A_4&\\A_4+A_6=A_1&\\A_5+A_7=A_3\end{cases}$$
设 $\begin{cases}A_1=a&\\A_2=b\end{cases}$，则有
$$\begin{cases}A_1=a&\\A_2=b&\\\displaystyle A_3=a-\frac{b}{2}&\\A_4=-a-b&\\\displaystyle A_5=-\frac{b}{2}&\\A_6=2a+b&\\A_7=-a\end{cases}$$

当 $a=1,b=2$ 时，便可构造满足条件的 $1$ 个序列 $1,2,-2,-3,-1,4,-1$。
# 代码
[AC 记录](https://codeforces.com/contest/1918/submission/309421125)
```cpp
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<iomanip>
#include<string>
#include<stack>
#include<random>
#define re register
#define ll long long
#define ull unsigned long long
#define vl __int128
#define ld long double
#define LL 2e18
#define INT 1e9
#define INF 0x3f3f3f3f
#define lb(x) (x&(-x))
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
int T=1;
using namespace std;
inline bool blank(const char x){return !(x^32)||!(x^10)||!(x^13)||!(x^9);}
template<typename Tp>inline void read(Tp &x){x=0;re bool z=true;re char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=(x<<1)+(x<<3)+(a^48);x=(z?x:~x+1);}
inline void read(double &x){x=0.0;re bool z=true;re double y=0.1;re char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=x*10+(a^48);if(a!='.')return x=z?x:-x,void();for(a=gc();isdigit(a);a=gc(),y/=10)x+=y*(a^48);x=(z?x:-x);}
inline void read(ld &x){x=0.0;re bool z=true;re ld y=0.1;re char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=x*10+(a^48);if(a!='.')return x=z?x:-x,void();for(a=gc();isdigit(a);a=gc(),y/=10)x+=y*(a^48);x=(z?x:-x);}
inline void read(char &x){for(x=gc();blank(x)&&(x^-1);x=gc());}
inline void read(char *x){re char a=gc();for(;blank(a)&&(a^-1);a=gc());for(;!blank(a)&&(a^-1);a=gc())*x++=a;*x=0;}
inline void read(string &x){x="";re char a=gc();for(;blank(a)&&(a^-1);a=gc());for(;!blank(a)&&(a^-1);a=gc())x+=a;}
template<typename T,typename ...Tp>inline void read(T &x,Tp &...y){read(x),read(y...);}
template<typename T>inline void read(T *begin,T *end){re T *i;if(begin<end)for(i=begin;i<end;++i)read(*i);else for(i=begin-1;i>=end;--i)read(*i);}
template<typename Tp>inline void write(Tp x){if(!x)return pc(48),void();if(x<0)pc('-'),x=~x+1;re int len=0;re char tmp[64];for(;x;x/=10)tmp[++len]=x%10+48;while(len)pc(tmp[len--]);}
inline void write(const double x){re int a=6;re double b=x,c=b;if(b<0)pc('-'),b=-b,c=-c;re double y=5*powl(10,-a-1);b+=y,c+=y;re int len=0;re char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);pc('.');for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}
inline void write(const ld x){re int a=6;re ld b=x,c=b;if(b<0)pc('-'),b=-b,c=-c;re ld y=5*powl(10,-a-1);b+=y,c+=y;re int len=0;re char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);pc('.');for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}
inline void write(const pair<int,double>x){re int a=x.first;if(a<7){re double b=x.second,c=b;if(b<0)pc('-'),b=-b,c=-c;re double y=5*powl(10,-a-1);b+=y,c+=y;re int len=0;re char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);a&&(pc('.'));for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}else printf("%.*lf",a,x.second);}
inline void write(const pair<int,ld>x){re int a=x.first;if(a<7){re ld b=x.second,c=b;if(b<0)pc('-'),b=-b,c=-c;re ld y=5*powl(10,-a-1);b+=y,c+=y;re int len=0;re char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);a&&(pc('.'));for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}else printf("%.*Lf",a,x.second);}
inline void write(const char x){pc(x);}
inline void write(const bool x){pc(x?49:48);}
inline void write(char *x){fputs(x,stdout);}
inline void write(const char *x){fputs(x,stdout);}
inline void write(const string &x){fputs(x.c_str(),stdout);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x),write(y...);}
template<typename T>inline void write(T *begin,T *end,const char c=' '){re T *i;for(i=begin;i<end;++i)write(*i,c);}
template<typename T>inline void init(T *begin,T *end,const T& val=T()){re T* i;for(i=begin;i<end;++i)*i=val;}
template<typename T>inline T max(T *begin,T *end){re T *ans,*i;for(i=begin;i<end;++i)if(i==begin||*ans<*i)ans=i;return *ans;}
template<typename T>inline T min(T *begin,T *end){re T *ans,*i;for(i=begin;i<end;++i)if(i==begin||*i<*ans)ans=i;return *ans;}
template<typename T>inline T calc_sum(T *begin,T *end,const T& val=T()){re T ans=val,*i;for(i=begin;i<end;++i)ans+=*i;return ans;}
template<typename T>inline bool is_equal(T *begin,T *end,const T& val=T()){re T *i;for(i=begin;i<end;++i)if(*i!=val)return false;return true;}

ll mod=0;
const int MAXN=1e6;
const int N=MAXN+10;
//#define DEBUG
//#define more_text

int n,a[N];

void SOLVE(int _){
	read(n);
	if(n==3||n==5){
		write("NO");
		return;
	}
	if(n&1){
		a[1]=1,a[2]=2,a[3]=-2,a[4]=-3,a[5]=-1,a[6]=4,a[7]=-1;
		for(int i=8;i<=n;i+=2)a[i]=-a[i-1],a[i+1]=a[i-2]-a[i-1];
	}
	else{
		a[1]=1,a[2]=2;
		for(int i=3;i<=n;i+=2)a[i]=-a[i-1],a[i+1]=a[i-2]-a[i-1];
	}
	write("YES\n");
	write(a+1,a+n+1);
}
/*
Input:

Output:

Outline:

*/
int main(){
	#ifdef DEBUG
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	#ifdef more_text
	read(T);
	#endif 
	for(int i=1;i<=T;++i)SOLVE(i);
	#ifdef DEBUG
	fclose(stdin);fclose(stdout);
	#endif
	return 0;
}
```

---

## 作者：Luzhuoyuan (赞：1)

你们的构造怎么都这么简单。为什么每次做构造题都会被降智。

设 $b$ 为产生的序列。题目要求 $a,b$ 组成的可重集相等，那我干脆让中间一大段都满足 $a_i=b_i$ 好了。随便钦定 $a$ 的头两项，就可以构造出这样一个循环序列：

```
a = 1 -2 -3 -1 2 3 1 -2 -3 ...
b =   -2 -3 -1 2 3 1 -2    ...
```

但是这样 $b_1$ 和 $b_n$ 就出问题了。考虑给它拼上一个火车头。

```
a = c d e x y ...
b = d ? ? ? y ...
```

这里 $x,y$ 都是已经确定的、在中间一大段的部分。我们尝试让 $b$ 中的三个问号分别填上数字 $c,e,x$。

考虑 $b_2$，由于 $a_i\ne 0$，故 $b_2\ne c,b_2\ne e$，则 $b_2=x$。再考虑 $b_4$，发现 $b_4\ne e$，则 $b_4=c$，这样 $b_3=e$。检查一下，发现逻辑上没问题。于是考虑计算出 $c,d,e$。可以列出方程组：

$\begin{cases}
c+e=x\\
d+x=e\\
e+y=c
\end{cases}$

解得 $c=\dfrac{x+y}2,d=-\dfrac{x+y}2,e=\dfrac{x-y}2$，发现 $x+y$ 和 $x-y$ 都不会为 $0$，完全可行。由于要除以 $2$，我们令中间一段整体乘 $2$ 即可。末尾也一样处理。

注意这个只适用于 $n\ge 8$，对于 $n<8$ 的随便构造或者暴力一下即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define wrk(x,y) if(n==x)cout<<y"\n",exit(0)
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N=1e6+5;
int n,a[N],b[]={2,-4,-6,-2,4,6};
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	wrk(2,"YES\n1 1");
	wrk(3,"NO");
	wrk(4,"YES\n1 2 -2 -1");
	wrk(5,"NO");
	wrk(6,"YES\n-2 -1 1 -1 1 2");
	wrk(7,"YES\n-5 -4 3 -1 -2 4 1");
	for(int i=4;i<=n-3;i++)a[i]=b[i%6];
	a[1]=(a[4]+a[5])/2;
	a[2]=-a[1];
	a[3]=(a[4]-a[5])/2;
	a[n]=(a[n-3]+a[n-4])/2;
	a[n-1]=-a[n];
	a[n-2]=(a[n-3]-a[n-4])/2;
	cout<<"YES\n";
	for(int i=1;i<=n;i++)cout<<a[i]<<" \n"[i==n];
	return 0;
}
```

（逃

---

## 作者：Z1qqurat (赞：1)

鉴定为 G<E，这都能评 *2700？

首先其实最重要的就是 $a_i\ne 0$，只要做到这一点其他的就是解个方程的事了。

暴搜打表之后发现，如果 $n=3,5$ 是无解的。其他情况试着增量构造，每次由 $n-2$ 的往后填两个 $a_i,a_{i+1}$ 构造得来，那么容易想到直接 $a_i=-a_{i-1},a_{i+1}=a_{i-2}-a_{i-1}$。所以说只要保证每次的 $a_{i-1},a_{i-2}$ 不同且非 $0$ 之后的 $a_i,a_{i+1}$ 也能构造出来并且满足同样的限制。分奇偶考虑：

1. $n$ 为偶数。容易找到这样一组较优的周期：$1,2,-2,-1,1,-1$，之后的直接以它为周期循环就可以满足条件。
2. $n$ 为奇数。找到一组邻项不同的开头：$-3,1,2,1,-1,-3,-2$，之后的直接通过 $a_i=-a_{i-1},a_{i+1}=a_{i-2}-a_{i-1}$ 增量构造仍能保证邻项不同从而每项非 $0$。注意 $n\le 5$ 的奇数情况是无解的，而偶数都有解。

复杂度 $\mathcal{O}(n)$。

[Submission.](https://codeforces.com/contest/1918/submission/246425444)

---

