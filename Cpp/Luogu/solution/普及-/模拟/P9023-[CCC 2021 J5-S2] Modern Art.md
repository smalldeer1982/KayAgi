# [CCC 2021 J5/S2] Modern Art

## 题目描述

维护一个 $01$ 矩阵，初始矩阵全为 $0$。

每次操作会将一行或一列反转（$0$ 变成 $1$，$1$ 变成 $0$）。

输出最后有多少个 $1$。

## 说明/提示

样例解释：

```
011           01000
100           01000
100           10111
              10111
```

$$M\times N\leq 5000000,K\leq 1000000$$

译自 [CCC2021 J5/S2](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/juniorEF.pdf)。

## 样例 #1

### 输入

```
3
3
2
R 1
C 1
```

### 输出

```
4```

## 样例 #2

### 输入

```
4
5
7
R 3
C 1
C 2
R 2
R 2
C 1
R 4
```

### 输出

```
10```

# 题解

## 作者：zhuweiqi (赞：7)

首先我们一看这个比较奇怪的数据范围，二维数组是肯定开不了的，那么我们就需要用两个一维数组来存储一下每行每列的反转情况了，由于同一行或者同一列被反转了偶数次之后等于没反转，所以我们就用 $r_i=1$ 来表示第 $i$ 行被反转了，用 $c_j=1$ 来表示第 $j$ 列被反转了，等 $k$ 次反转结束之后，我们设当前坐标为 $a_{i,j}$：如果 $r_i=0$ 并且 $c_j=0$，就说明第 $i$ 行第 $j$ 列都没有被真正的反转，所以 $a_{i,j}=0$；同理，如果 $r_i=1$ 并且 $c_j=1$，就说明第 $i$ 行第 $j$ 列都被反转了，那么 $a_{i,j}$ 就被反转了两次，反转了偶数次之后等于没反转，所以 $a_{i,j}=0$；另外，如果第 $i$ 行和第 $j$ 列中**有且只有一个**被反转了，那么 $a_{i,j}$ 就被反转了一次，所以 $a_{i,j}=1$，最终得出结论：如果 $r_i \neq c_j$，$a_{i,j}=1$，我们只需要一个双重循环判断就可以了，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int r[5000005],c[5000005];
int main(){
	std::ios::sync_with_stdio(0);
	int n,m,k,ans=0;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		char d;int x;
		cin>>d>>x;
		if(d=='R') r[x]=!r[x];
		else c[x]=!c[x];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(r[i]!=c[j]) ans++;
		}
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：InversionShadow (赞：4)

## P9023 [CCC2021 J5/S2] Modern Art 题解

和 @OIer1030 大佬的思路一样。

### 思路：

考虑两个数组存储行和列，令他们为 $\{l_n\}$ 和 $\{c_n\}$，输入的为 $k$，如果操作是一行，则 $l_k$ 加一，否则 $c_k$ 加一，表示他们进行一次取反。统计结果的时候，如果 $l_i+c_j\bmod 2=1$，表示为 $1$，答案加一，最后输出即可。

### Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

int l[5000001], c[5000001], k, n, m, ans, h;  // 注意数组大小
char f;

int main() {
  cin >> n >> m >> h;
  for (int i = 1; i <= h; i++) {
    cin >> f >> k;
    if (f == 'R') {  // 如果操作为一行
      l[k]++;
    } else {
      c[k]++;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) { 
      if ((l[i] + c[j]) % 2 == 1) {  
        ans++;
      }
    }
  } 
  cout << ans << endl;
  return 0;
}
```


---

## 作者：LuoFeng_Nanami (赞：2)

这道题首先看数据范围，$M \times N \leq 5000000$，显然地，暴力翻转做法无法通过。  
接着考虑存储翻转次数。对于每次操作，将每行或每列操作的结果取反，储存在数组里。最后遍历每一个点，如果列与行操作结果的总和为 1，则相当于翻转了一次；如果总和为 0 或 2，那么相当于没有被翻过。  
时间复杂度 $O(nm)$，1 秒时限可以过。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 5000000 + 7;

int R[maxn],C[maxn];//R数组存放每列操作次数；C数组存放每行操作次数。 
int n, m, k, ans;

int main(){
	cin >> n >> m >> k;
	for(int i = 1; i <= k; i++){
		char c;
		int a;
		cin >> c >> a;
		if(c == 'R')
			R[a] = !R[a];
		else C[a] = !C[a];//取反操作，0 取反后为 1,1 取反后为 0。
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
				ans += (R[i] + C[j]) % 2;
	cout << ans << endl;
	return 0;
}
```


---

## 作者：CSPJ10pts (赞：2)

## 题目描述：

维护一个 $01$ 矩阵，初始矩阵全为 $0$。

每次操作会将一行或一列反转（$0$ 变成 $1$，$1$ 变成 $0$）。

输出最后有多少个 $1$。

## 分析

解法 $\texttt1$：对于每次操作直接暴力反转，最后统计一下。时间复杂度大约为  $O(kn + nm)$。但看一眼数据范围就知道很明显会超时，而且你不知道统计数组要开多大（而且如果这样可以过的话就不是黄题了）。

解法 $\texttt2$：对于每次的操作，我们给对应行/列的“操作计数器”加 $\texttt1$，最后每个点（注意不用用数组存）的反转次数就是它对应行和对应列的“操作计数器”之和。这个点最后是 $\texttt0$ 还是 $\texttt1$ 只需要看它的奇偶性即可。时间复杂度为 $O(nm)$，可以过。

## 代码

```
#include <iostream>
using namespace std;
#define maxn 5000001
int n, m, k, num, r[maxn], c[maxn], cnt;
char op;
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        cin >> op >> num;
        if (op == 'R') r[num]++; 
        else c[num]++; // 统计对应行/列的反转次数
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cnt += (r[i] + c[j]) % 2; // 对应行和对应列操作计数器之和%2就是这个点现在的状态
    printf("%d\n", cnt);
}
```
[AC 记录~](https://www.luogu.com.cn/record/101560498)

---

## 作者：SDLTF_凌亭风 (赞：2)

如果硬是要模拟翻转的话，肯定会超时，于是考虑更快的做法。  
不难想到，模拟的做法需要重复的翻转多次，导致进行多次赋值操作。不妨把所有的赋值操作先记录下来，再用一次性把这个点的值给算出来。  
在最后，我们遍历每一个点。如果这个点被翻过偶数次，那么相当于没有被翻过；如果这个点被翻过奇数次，那么相当于只被翻了一次。  

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int row[10000005], col[10000005];
int main() {
	register int m, n, k;
	cin >> m >> n >> k;
	while (k -- ) {
		char op, t;
		int x;
		cin >> op >> x;
		(op == 'R') ? row[x - 1] ++ : col[x - 1] ++;
	}
	
	register vector<vector<int> > matri(m, vector<int>(n));// 由于不知道这个数组要开多大，那么干脆vector解决问题
	
	for(register int i = 0; i < m; ++i) {
		for(register int j = 0; j < n; ++j) {
			matri[i][j] += row[i];
		}
	}
	for(register int j = 0; j < n; ++j) {
		for(register int i = 0; i < m; ++i) {
			matri[i][j] += col[j];
		}
	}
	
	register int cnt = 0;
	for(register int i = 0; i < m; ++i) {
		for(register int j = 0; j < n; ++j) {
			cnt += (matri[i][j] % 2 == 1);
		}
	}
	cout << cnt;
}
```

---

## 作者：QWQ_SenLin (赞：1)

### 前言

看其他题解的空间都挺大的，其实可以再优化一下。

### 基本做法

单纯暴力肯定是不行的，空间和时间都会爆。

所以可以把更新放到输入完后，某个点更新的次数记为 $sum_{i,j}$，则 $sum_{i,j} = $ $i$ 行更新次数 + $j$ 列更新次数。

很容易发现，点 $(i,j)$ 更新 $2,4,6,8,...,2n$ 次，是与原数相等的，因为原数为 $0$ ，则说明此点对答案没有贡献，因此当 $sum_{i,j} \bmod 2 =1$ 时，点 $(i,j)$ 才对答案有贡献（答案 $+1$）。

时间复杂度 $\mathcal O(nm)$，空间复杂度 $\mathcal O(n + m)$。

```cpp
if(c == 'R')
    R[x]++; //x 行更新的次数 + 1
else
    C[x]++; //x 列更新的次数 + 1
```

空间有点大啊 QAQ，最大大约 $10^7$ 了，虽然是可以通过本题。

### 空间的优化

我们优化下空间：首先你要知道一个简单的[性质](https://baike.baidu.com/item/MOD%E8%BF%90%E7%AE%97/7885553)，如下。

$(a + b) \bmod p=(a\bmod p +b \bmod p) \bmod p$。

所以每行每列的更新次数可以提前 $\bmod \text{ } 2$，用上面的式子很容易可以证出答案是与原来相等的。这样就不用写 $\text{int}$，可以用 $\text{bool}$ 型，空间会降低很多，大约低了六七倍。

如果不理解，也可以理解为：同一行翻转偶数次后，这时得到的数和第 $0$ 次（未翻转）的数是一样的，因此这时就可以直接把翻转次数归 $0$。列同理。

```cpp
if(c == 'R')
    R[x] = !R[x];
else
    C[x] = !C[x]; //满2就归0
```

如果不在意时间，其实还可以用 $\text{bitset}$ 来进一步减少空间使用（大约能少一倍）。

```cpp
//使用之前需要导入头文件 <bitset>
bitset <5000005> C , R;
C[x].flip(); //C 的第 x 位满2就归0
R[x].flip(); //R 的第 x 位满2就归0
```

思路是差不多的，这里就不给出完整代码了。

---

