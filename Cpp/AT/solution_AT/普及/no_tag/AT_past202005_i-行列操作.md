# 行列操作

## 题目描述

有一个满足以下条件的一个 $n \times n$ 的矩阵 $a$。若将该数列上起第 $i$ 行，左起第 $j$ 列上的数记为 $a_{i,j}$，则：

- 当 $1 \le i,j \le n$ 时，$a_{i,j}=n \times (i-1)+j-1$。

## 说明/提示

**数据规模与约定**

对于全部测试点，数据保证：

- $1 \le n,q \le 10^5$；
- $1 \le x,y \le n$；
- 保证至少存在一个形如`4 x y`格式的查询；
- 输入中的所有数值均为整数。

## 样例 #1

### 输入

```
2
19
4 1 1
4 1 2
4 2 1
4 2 2
3
4 1 1
4 1 2
4 2 1
4 2 2
1 1 2
4 1 1
4 1 2
4 2 1
4 2 2
2 2 1
4 1 1
4 1 2
4 2 1
4 2 2```

### 输出

```
0
1
2
3
0
2
1
3
1
3
0
2
3
1
2
0```

## 样例 #2

### 输入

```
3
9
2 2 3
3
1 2 1
2 3 2
1 1 3
3
4 1 1
4 2 2
4 2 3```

### 输出

```
1
6
8```

# 题解

## 作者：ylch (赞：4)

## Description

我们有一个 $n \times n$ 的矩阵 $a$，其元素满足以下条件：
$$
a_{i,j} = n \times (i - 1) + j - 1 \quad (1 \leq i, j \leq n)
$$

接下来，我们需要对这个矩阵进行 $q$ 次操作，操作类型包括：
1. 交换两行的元素。
2. 交换两列的元素。
3. 转置矩阵。
4. 查询某个位置的元素值。

数据范围：$n,q \le 10^5$

## Analysiss

发现每次操作貌似都是针对行和列的，和具体数字无关。所以我们只要用两个数组记录行和列的变化，在处理询问时按照公式 $O(1)$ 处理出值即可。

具体地，可以记录两个数组 $row,col$，其中 $row[i]$ 表示初始矩阵第 $i$ 行在当前矩阵中的实际存储位置（可以理解为两个指针）。初始状态即为 $row[i]=i$，表示没有交换。对于 $col$ 的处理同理。

考虑处理操作，操作 $1,2$ 显然，只要交换对应的行、列指针即可。操作 $4$ 可以根据题面给的递推式求值。

现在本题的难点来到了操作 $3$：矩阵转置。

考虑拿一个矩阵模拟一下，对于以下矩阵：

```
1 2 3
4 5 6
7 8 9
```

转置后的矩阵如下：

```
1 4 7
2 5 8
3 6 9
```

我们发现，转置矩阵好像就是把第一列与第一行交换，第二列与第二行交换，以此类推。

也就是说，在查询转置矩阵位置 $(x,y)$ 时，实际要查询的是原矩阵位置 $(y,x)$ 的值。再转置一次呢？查询原矩阵的位置又变回 $(x,y)$。

以上发现带给我们几个思路：

1. 如果矩阵转置了一次，我们只要把存储行、列的数组整体交换一下，就可以实现目标。

   这个有点抽象，可以理解为矩阵转置本身其实不需要交换两个数组，只要询问时交换行列坐标就行。但我们还要处理操作 $1,2$，这样做能保证**在进行若干次操作 $1,2$ 后再进行操作 $3$ 换回来时，换回来的行、列顺序是交换后的正确位置**。具体见代码。
  
2. 矩阵转置只有两种结果来回变，根据奇偶性决定，奇变偶不变。所以我们可以用标记变量记录当前矩阵的答案是否为转置状态，从而处理询问。

3. 在处理询问 $(x,y)$ 时，如果矩阵处于转置状态，则答案应该是位置 $(col[y], row[x])$ 的值；否则答案应为 $(row[x],col[y])$ 的值。

## Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;

    // 初始化行和列的映射
    vector <int> row(n + 1), col(n + 1);
    for(int i = 1; i <= n; i ++){
        row[i] = col[i] = i;
    }

    bool flag = false; // 矩阵转置的标记
    while(q --){
        int op; cin >> op;
        if(op == 1){
            int x, y; cin >> x >> y;
            swap(row[x], row[y]);
        }
        else if(op == 2){
            int x, y; cin >> x >> y;
            swap(col[x], col[y]);
        }
        else if(op == 3){
            flag ^= 1;
            swap(row, col);
        }
        else if(op == 4){
            int x, y; cin >> x >> y;
            int i = row[x], j = col[y];
            if(flag) swap(i, j);
            cout << 1LL * n * (i - 1) + (j - 1) << '\n'; // long long！！！
        }
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}

```

时间复杂度：每次操作的时间复杂度为 $O(1)$，总时间复杂度为 $O(n+q)$。

## End

管理员大大辛苦啦~

这里是 ylch，谢谢大家！

---

## 作者：Never_care (赞：2)

### 思路
首先可以看出应该要将行和列分开计算，因为如果按照整个二维数组解决会爆空间。这里比较偏向使用两个动态数组，灵活性更高，当然把二维转一维也是可以的。

直接看操作。操作 $1$ 和操作 $2$ 简单，在此不过多赘述。看操作 $3$，这里需要设立一个变量来判断数组是否转置过。因为转置会将数组的行和列交换，即代表行和列的数组的值也会被交换。在操作 $4$ 中，通过变量判断数组是否经历过转置。如果没有被转置过，则直接计算，否则则要调换位置。然后就会写出如下代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
using namespace std;
signed main(){
	int n,q;
    cin>>n>>q;
    vector<int> a(n+5);
	vector<int> b(n+5);
    for(int i=1;i<=n;i++){
        a[i]=i;
		b[i]=i;
    }
    int cnt=0;
    while(q--){
        int op,x,y;
		cin>>op;
        if(op==1){
        	cin>>x>>y;
            swap(a[x],a[y]);
        }
        if(op==2){
        	cin>>x>>y;
            swap(b[x],b[y]);
        }
        if(op==3){
        	cnt=1;
            swap(a,b);
        }
        else if(op==4){
        	cin>>x>>y;
            int t1=a[x],t2=b[y];
            if(cnt){
            	swap(t1,t2);
			}
            cout<<n*(t1-1)+(t2-1)<<'\n';
        }
    }
    return 0;
}
```
当然，这是个十分弱智的错误。通过分析可知数组在转置奇数次的时候会变换，而在偶数次的时候又会变回去，举例子可知。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
using namespace std;
signed main(){
	int n,q;
    cin>>n>>q;
    vector<int> a(n+5);
	vector<int> b(n+5);
    for(int i=1;i<=n;i++){
        a[i]=i;
		b[i]=i;
    }
    int cnt=0;
    while(q--){
        int op,x,y;
		cin>>op;
        if(op==1){
        	cin>>x>>y;
            swap(a[x],a[y]);
        }
        if(op==2){
        	cin>>x>>y;
            swap(b[x],b[y]);
        }
        if(op==3){
        	if(cnt==0){
        		cnt=1;
			}
			else if(cnt==1){
				cnt=0;
			}
            swap(a,b);
        }
        else if(op==4){
        	cin>>x>>y;
            int t1=a[x],t2=b[y];
            if(cnt){
            	swap(t1,t2);
			}
            cout<<n*(t1-1)+(t2-1)<<'\n';
        }
    }
    return 0;
}
```
[record](https://www.luogu.com.cn/record/207111154)

---

## 作者：NFGase (赞：2)

这道题最难的点在于用什么方法存储矩阵 $a$ 和一个特殊的操作方式。

要存矩阵 $a$，最先想到的是二维数组，但是二维数组开不到 $1 \le n \le 10^5$，所以可以用一个长度为 $2 \cdot n$ 的一维数组 $m$ 来存。当 $i \le n$ 时，让一维数组 $m_{i}$ 负责存第 $i$ 行的内容；而当 $n + 1 \le i \le 2 \cdot n$ 时，$m_{i}$ 负责存第 $i$ 列的内容。

由题目给出的内容公式和我们用的方法可知最终该怎么对 $m_{i}$ 赋初始值。

- $i \le n$ 时，$m_{i} = n \cdot (i - 1)$

- $n + 1 \le i \le 2 \cdot n$ 时， $m_{i} = i - 1 - n$

于是有了以下代码。

```cpp
for(long long i = 1; i <= n; i++) m[i] = n * (i - 1);
for(long long i = n + 1; i <= 2 * n; i++) m[i] = i - 1 - n;
```

之后我们可以想一下大概思路。首先定义两个变量 $a$ 和 $b$，$a$ 初始值设定为 $0$，负责行，$b$ 初始值设定为 $n$，负责列，他们俩要担负表示行列和交换行列的重任，大概意思是第 $i$ 行被表示为 `m[a + x]`，第 $i$ 列则被表示为 `m[b + y]`，要交换的时候只要交换 $a$ 和 $b$ 即可。

大概思路已经说完了，我就直接在下面放代码了。

```cpp
#include <iostream>
using namespace std;
long long n, q, m[1000001], a, b;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    cin >> n >> q;
    for(long long i = 1; i <= n; i++) m[i] = n * (i - 1);
    for(long long i = n + 1; i <= 2 * n; i++) m[i] = i - 1 - n;
    a = 0, b = n;
    for(long long i = 1; i <= q; i++){
        long long option;
        cin >> option;
        if(option == 1){
            long long x, y;
            cin >> x >> y;
            swap(m[a + x], m[a + y]);
        }
        else if(option == 2){
            long long x, y;
            cin >> x >> y;
            swap(m[b + x], m[b + y]);
        }
        else if(option == 3) swap(a, b);
        else{
            long long x, y;
            cin >> x >> y;
            long long ans = m[a + x] + m[b + y];
            cout << ans << endl;
        }
    }
    return 0;
}
```

[记录](https://atcoder.jp/contests/past202005-open/submissions/44889961)

---

## 作者：andyli (赞：0)

记录两个数组表示每行每列对应的原行/列编号，以及一个变量表示是否为转置状态。则容易处理各操作：对于前两种操作，交换行/列表示的数组对应的位置；对于第三种操作，取反表示转置状态的变量并交换行/列表示的数组。  

```cpp
int main() {
    dR(int, n, q);
    vi R(n), C(n);
    iota(all(R), 0);
    iota(all(C), 0);
    bool transpose = false;
    _for (q) {
        dR(int, t);
        if (t == 1) {
            dR(int, x, y), x--, y--;
            swap(R[x], R[y]);
        }
        if (t == 2) {
            dR(int, x, y), x--, y--;
            swap(C[x], C[y]);
        }
        if (t == 3) {
            transpose ^= 1;
            swap(R, C);
        }
        if (t == 4) {
            dR(int, x, y), x--, y--;
            x = R[x], y = C[y];
            if (transpose)
                swap(x, y);
            print(i64(x) * n + y);
        }
    }
    return 0;
}
```

---

