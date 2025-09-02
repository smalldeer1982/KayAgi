# Construct Matrix

## 题目描述

You are given an even integer $ n $ and an integer $ k $ . Your task is to construct a matrix of size $ n \times n $ consisting of numbers $ 0 $ and $ 1 $ in such a way that the following conditions are true, or report that it is impossible:

- the sum of all the numbers in the matrix is exactly $ k $ ;
- the bitwise $ \texttt{XOR} $ of all the numbers in the row $ i $ is the same for each $ i $ ;
- the bitwise $ \texttt{XOR} $ of all the numbers in the column $ j $ is the same for each $ j $ .

## 说明/提示

In the first example, all conditions are satisfied:

- the sum of all the numbers in the matrix is exactly $ 0 $ ;
- the bitwise $ \texttt{XOR} $ of all the numbers in the row $ i $ is $ 0 $ for each $ i $ ;
- the bitwise $ \texttt{XOR} $ of all the numbers in the column $ j $ is $ 0 $ for each $ j $ .

In the third example, it can be shown that it's impossible to find a matrix satisfying all the problem's conditions.

## 样例 #1

### 输入

```
5
4 0
6 6
6 5
4 2
6 36```

### 输出

```
Yes
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
Yes
1 0 0 0 0 0
0 1 0 0 0 0
0 0 1 0 0 0
0 0 0 1 0 0
0 0 0 0 1 0
0 0 0 0 0 1
No
No
Yes
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1```

# 题解

## 作者：sunkuangzheng (赞：9)

$k$ 是奇数显然无解，因为要满足要求，每行的 $1$ 的数量奇偶性必须相同，列同理。

从易到难，分四种情况讨论。

### $k \bmod 4 = 0$

只需要用 $2 \times 2$ 的 $1$ 矩阵一直填即可，填一个 $2 \times 2$ 的矩阵显然不会影响任何一行和任何一列的异或和。

### $6 \le k \le n^2-10$ 且 $k \bmod 4 = 2$

考虑在左上角构造一个这样的图案：

| $1$ | $1$ | $0$ | $0$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $0$ | $1$ | $0$ |
| $0$ | $1$ | $1$ | $0$ |
| $0$ | $0$ | $0$ | $0$ |

它会用去 $6$ 个 $1$，填完后 $k \bmod 4 = 0$，在剩余位置继续填 $2 \times 2$ 矩阵即可。

### $k= n^2-6$

把除了左上角以外填满，左上角在刚才的基础上需要多填四个位置。

| $1$ | $1$ | $0$ | $0$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $0$ | $1$ | $0$ |
| $\color{blue}1$ | $1$ | $1$ | $\color{blue}1$ |
| $\color{blue}1$ | $0$ | $0$ | $\color{blue}1$ |

这样填的依据是，要保证每一行每一列的异或和不变。

### $k=2$ 或 $k=n^2-2$

这两种情况本质等价，我们只考虑 $k=2$。

如果两个位置填在同一行，那么列的异或和必定不同，反之亦然。因此，$k=2$ 时只有 $n=2$ 有解，其余情况无解。

按照上面的分类模拟即可。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 25.12.2023 10:40:05
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using ll = long long;
const int N = 1e3+5;
using namespace std;
int T,n,k,a[N][N];
void los(){
    cin >> n >> k;
    for(int i = 1;i <= n;i ++) for(int j = 1;j <= n;j ++) a[i][j] = 0;
    if(k & 1) return cout << "No\n",void();
    if(n == 2){
        if(!k) cout << "Yes\n0 0\n0 0\n";
        if(k == 2) cout << "Yes\n1 0\n0 1\n";
        if(k == 4) cout << "Yes\n1 1\n1 1\n"; 
        return ;
    }if(k == n * n - 2 || k == 2) return cout << "No\n",void();
    for(int i = 1;i <= n;i += 2) for(int j = 1;j <= n;j += 2)
        if(k >= 8 && (i > 4 || j > 4)) a[i][j] = a[i+1][j] = a[i][j+1] = a[i+1][j+1] = 1,k -= 4;
    if(k % 4) a[1][1] = a[1][2] = a[2][1] = a[2][3] = a[3][2] = a[3][3] = 1,k -= 6;
    else for(int i = 1;i <= 4;i += 2) for(int j = 1;j <= 4;j += 2)
        if(k >= 4) a[i][j] = a[i+1][j] = a[i][j+1] = a[i+1][j+1] = 1,k -= 4;
    if(k) assert(k == 4),a[3][1] = a[4][1] = a[3][4] = a[4][4] = 1,k -= 4;
    assert(k == 0);
    cout << "Yes\n";
    for(int i = 1;i <= n;i ++,cout << "\n") for(int j = 1;j <= n;j ++) cout << a[i][j] << " ";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}

```






---

## 作者：WilliamFranklin (赞：3)

### 主要思路

看到这道题，我第一反应就是打表，然后，就是奇迹。

首先我先考虑了一下奇数的情况，发现奇数的情况无论如何都不可以，证明也很简单。

然后就考虑偶数，关于 $k = 2$ 的情况，我发现只有在 $n = 2$ 时才可以，其他情况都不行。那么同样的，我将整个矩阵取反，得到 $k = n^2 - 2$ 时，也不可以构造出来。

下面就是 $k = 4$ 的情况，这个很好想，就是直接左上角的那个 $2 \times 2$ 的小方阵都为 $1$ 即可。那么这样我们又可以推广到 $k$ 为 $4$ 的倍数的情况，因为 $n$ 是偶数，所以这个大方阵一定可以划分成若干 $2 \times 2$ 的小方阵，那么我们每一次都随便将一整个 $2 \times 2$ 的小方阵变为 $1$，直到共有 $k$ 个 $1$ 为止，这样，每一行每一列的异或和都为 $0$。

再然后就是 $k = 6$ 的情况，首先，可以保证此时 $n > 3$ 了，我发现可以将左上角那个 $3 \times 3$ 的小方阵，按下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/10vo9hqv.png)

但是我发现，不能推广到 $k$ 为 $6$ 的倍数的情况，那后面的路就需要另走了。

其实剩下的情况就是 $k \equiv 2 \pmod{4}$，并且 $k > 6$，所以我们可以考虑将 $k$ 为 $6$ 的时候，与 $k$ 为 $4$ 的倍数的时候相结合。也就是说，我们可以将除了左上角那 $4 \times 4$ 的小方阵外，将其他的按照 $2 \times 2$ 的小方阵变为 $1$。但是在我对拍时，发现了个特例，那就是 $k = n^2 - 6$ 时，然后我发现可以将 $(1,1), (1,4), (4,1), (4,4)$ 这四个变为 $1$ 即可。

下面就看下代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first 
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 1005;
int a[N][N];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		memset(a, 0, sizeof(a));
		if (k % 2 == 1) {
			cout << "No" << '\n';
			continue;
		}
		if (k == 2 || k == n * n - 2) {
			if (n == 2) {
				cout << "Yes" << '\n';
				cout << "0 1\n 1 0" << '\n';
				continue;
			}
			cout << "No" << '\n';
			continue;
		}
		if (k % 4 == 0) {
			int now = 0;
			for (int i = 1; i <= n; i += 2) {
				for (int j = 1; j <= n; j++) {
					now += 2;
					if (now > k) a[i][j] = a[i + 1][j] = 0;
					else a[i][j] = a[i + 1][j] = 1;
				}
			}
			cout << "Yes" << '\n';
			For(i, 1, n) For(j, 1, n) cout << a[i][j] << " \n"[j == n];
			continue; 
		}
		a[1][3] = a[1][2] = a[2][1] = a[2][2] = a[3][1] = a[3][3] = 1;
		int now = 6;
		for (int i = 1; i <= n; i += 2) {
			for (int j = 1; j <= n; j += 2) {
				if (i == 1 && j == 1) continue;
				if (i == 1 && j == 3) continue;
				if (i == 3 && j == 1) continue;
				if (i == 3 && j == 3) continue;
				if (now < k) {
					a[i][j] = 1;
					a[i + 1][j] = 1;
					a[i][j + 1] = 1;
					a[i + 1][j + 1] = 1;
					now += 4;
				}
			}
		}
		if (k == n * n - 6) {
			a[1][1] = a[1][4] = a[4][1] = a[4][4] = 1;
		}
		cout << "Yes" << '\n';
		For(i, 1, n) {
			For(j, 1, n) {
				cout << a[i][j] << ' ';
			}
			cout << '\n';
		}
	}
	return 0;
} 
```

### 谢谢观看

---

## 作者：daniEl_lElE (赞：2)

由于 $n$ 是偶数，$k$ 为奇数时不可能。

观察到翻转 $2\times 2$ 的小正方形是一个很优的操作。

考虑 $4\mid k$ 的情况。此时我们可以对于每个 $2\times 2$ 的小正方形依次翻转，即可构造出所有情况。

考虑 $2\mid k$ 但 $4 \nmid k$ 的情况。首先如果 $k=2$ 或 $k=n^2-2$ 那么显然没有合法构造方案。考虑魔改左上 $4\times 4$ 小正方形。对于 $k<n^2-6$ 的情形，左上角 $4\times 4$ 小正方形可以只填 $(1,1),(1,2),(2,1),(2,3),(3,2),(3,3)$ 位置，其他位置按照前面 $4\mid k$ 的情况做。$k=n^2-6$ 时，可以在上述基础上额外填 $(2,2),(2,4),(4,2),(4,4)$。

总复杂度 $O(n^2)$。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
#define double long double
#define lowbit(i) (i&(-i))
using namespace std;
int a[1005][1005];
signed main(){
	int t; cin>>t;
	while(t--){
		int n,k; cin>>n>>k;
		if(k&1){
			cout<<"No\n";
			continue;
		} 
		if(n==2){
			if(k==0) cout<<"Yes\n0 0\n0 0\n";
			else if(k==2) cout<<"Yes\n1 0\n0 1\n";
			else cout<<"Yes\n1 1\n1 1\n";
			continue;
		}
		if(k==2||k==n*n-2){
			cout<<"No\n";
			continue;
		}
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=0;
		if(k%4==0){
			k/=4;
			for(int i=1;i<=n;i+=2){
				for(int j=1;j<=n;j+=2){
					if(k){
						k--;
						a[i][j]=a[i+1][j+1]=a[i][j+1]=a[i+1][j]=1;
					}
				}
			}
		}
		else{
			if(k==n*n-6){
				for(int i=1;i<=3;i++) for(int j=1;j<=3;j++) a[i][j]=1;
				a[1][3]=a[3][1]=0,a[2][4]=a[4][2]=a[4][4]=1;
				k-=10;
			}
			else{
				for(int i=1;i<=3;i++) for(int j=1;j<=3;j++) a[i][j]=1;
				a[1][3]=a[2][2]=a[3][1]=0;
				k-=6;
			}
			k/=4;
			for(int i=1;i<=n;i+=2){
				for(int j=1;j<=n;j+=2){
					if(i<=4&&j<=4) continue;
					if(k){
						k--;
						a[i][j]=a[i+1][j+1]=a[i][j+1]=a[i+1][j]=1;
					}
				}
			}
		}
		cout<<"Yes\n";
		for(int i=1;i<=n;i++,cout<<"\n") for(int j=1;j<=n;j++) cout<<a[i][j]<<" ";
	}
	return 0;
}
```

---

## 作者：Acerkaio (赞：2)

# E_Construct_Matrix题解
## 题面

[Luogu](https://www.luogu.com.cn/problem/CF1917E)

[Codeforces](http://codeforces.com/problemset/problem/1917/E)

## 思路

考虑分块，把大矩阵分成多个分块矩阵。

我们容易构造出： $\begin{pmatrix}
 1 & 1\\
 1 & 1
\end{pmatrix}$，$\begin{pmatrix}
 1 & 1 & 0\\
 1 & 0 & 1\\
 0 & 1 & 1
\end{pmatrix}$ 每行每列的异或值都是 $0$ 且贡献分别是 $4$ 和 $6$。

考虑到 $n$ 是偶数且 $2 \times 2$ 的小矩阵能贡献 $4$。我们有如下讨论：

当 $4 \mid k$，我们能构造出一个大矩阵能分块出 $\frac{k}{4}$ 个 $2 \times 2$ 的 $\begin{pmatrix}
 1 & 1\\
 1 & 1
\end{pmatrix}$ 矩阵，与 $\frac{n^2 - k}{4}$ 个 $2 \times 2$ 的 $\begin{pmatrix}
 0 & 0\\
 0 & 0
\end{pmatrix}$ 矩阵。

例如 $n = 4, k = 12$ 时：

$\begin{pmatrix}
1  & 1 & 1 & 1 \\
1  & 1 & 1 & 1\\
1  & 1 & 0 & 0 \\
1  & 1 & 0 & 0
\end{pmatrix}$

当 $4 \nmid k$ 时，我们考虑使用 $\begin{pmatrix}
 1 & 1 & 0\\
 1 & 0 & 1\\
 0 & 1 & 1
\end{pmatrix}$ 贡献。

举例 $n = 8$ 时，我们若分块出一个上文的 $3 \times 3$ 的矩阵，则剩下区域考虑 $1$ 最多可能长什么样。

若构造：

$\begin{pmatrix}
 1 & 1 & 0 & 1 & 1 & 1 & 1 & 0\\
 1 & 0 & 1 & 1 & 1 & 1 & 1 & 0\\
 0 & 1 & 1 & 1 & 1 & 1 & 1 & 0\\
 1 & 1 & 1 & 1 & 1 & 1 & 1 & 0\\
 1 & 1 & 1 & 1 & 1 & 1 & 1 & 0\\
 1 & 1 & 1 & 1 & 1 & 1 & 1 & 0\\
 1 & 1 & 1 & 1 & 1 & 1 & 1 & 0\\
 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0
\end{pmatrix}$

但似乎不优，可以更充分地使用空间。

若构造：

$\begin{pmatrix}
 1 & 1 & 0 & 0 & 1 & 1 & 1 & 1\\
 1 & 0 & 1 & 0 & 1 & 1 & 1 & 1\\
 0 & 1 & 1 & 0 & 1 & 1 & 1 & 1\\
 0 & 0 & 0 & 0 & 1 & 1 & 1 & 1\\
 1 & 1 & 1 & 1 & 1 & 1 & 1 & 1\\
 1 & 1 & 1 & 1 & 1 & 1 & 1 & 1\\
 1 & 1 & 1 & 1 & 1 & 1 & 1 & 1\\
 1 & 1 & 1 & 1 & 1 & 1 & 1 & 1
\end{pmatrix}$


我们分块出左上角 $4 \times 4$ 的分块矩阵去贡献 $6$。既然动用了 $4 \times 4$ 的矩阵，我们能否构造贡献更多的一种分块矩阵呢？

$\begin{pmatrix}
 1 & 1 & 0 & 0\\
 1 & 0 & 1 & 0\\
 1 & 1 & 1 & 1\\
 1 & 0 & 0 & 1
\end{pmatrix}$ 或 $\begin{pmatrix}
 0 & 0 & 1 & 1\\
 0 & 1 & 0 & 1\\
 1 & 0 & 0 & 1\\
 1 & 1 & 1 & 1
\end{pmatrix}$

构造了贡献 $10$ 的分块矩阵。

至此，包括 $4 \mid k$ 的情况，**不考虑不等关系**，我们利用贡献 $4$ 和 $6$ 的矩阵已经可以构造出：$k = 4i$ 或 $k = 4i + 6$ 的情况，其中 $i$ 为上文 $2 \times 2$ 的分块矩阵个数。

**若使用贡献 $6$ 的分块矩阵时** $k = 4i + 6 = 4 (i + 1) + 2$，考虑到 $0 \le i \le \frac{n ^ 2 - 16}{4}$，也就是 $k$ 的最小范围为 $k \ge 6$，$k$ 的最大范围 $k \le n ^ 2 - 10$，我们再把贡献 $6$ 的分块矩阵**替换**为使用贡献 $10$ 的分块矩阵即可把这个 $k$ 的最大范围变为 $k \le n^2 - 6$。

至此，我们实际已构造出 $2 | k$，$0 \le k \le n$ 且 $k \neq 2 \neq n ^ 2 - 2$，的所有 $k$ 的情况。

剩下的情况是否无解呢？

事实上，除了特例 $n = 2, k = 2$ 时有：$\begin{pmatrix} 1 & 0\\ 0 & 1\end{pmatrix}$，剩下的 $k = 2$ 或 $n ^ 2 - 2$ 时都无解。

证明：

$k = 2, n \ge 4$ 时。

我们填写一个 $1$ 之后，有 $1$ 行**和** $1$ 列的异或值为 $1$，$n - 1 \ge 3$ 行**和** $n - 1 \ge 3$ 列的异或值为 $0$。

我们发现第二个 $1$ 无论填哪里都至少有 $1$ 列**或** $1$ 行的异或值为 $1$，至少有 $n - 2 \ge 2$ 行**或** $n - 2 \ge 2$ 列的异或值为 $0$。

不符合要求。

证毕。

接下来证明 $2 \nmid k$ 时一定无解。

有：

$n \ge 2, 2 \nmid k, 2 \mid n$

若：$k$ 为奇数有解。

设 $1$ 的个数为偶数的行数（即这一行的异或值为 $0$）为 $x$，设 $1$ 的个数为奇数的行数（即这一行的异或值为 $1$）为 $y$。

因为题设，则有 $2 \nmid y$，且 $y \ge 1$。

又因为每一行的异或值相同。

所以 $x = 0, y = n$ 或 $x = n, y = 0$。

又 $2 \mid n$

所以 $y$ 的奇偶性矛盾。

所以此题中 $2 \nmid k$ 时一定无解。

---

至此，我们讨论出了所有情况。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;
const int _ = 2e3 + 7;

// data:
bool c[_][_];
// function:

signed main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        memset(c, 0, sizeof c);
        int n, k;
        cin >> n >> k;
        if (k & 1) {
            cout << "No\n";
        } else {
            
            if (k % 4 == 0) {
                cout << "Yes\n";
                for (int i = 1; i <= n / 2; i++) {
                    for (int j = 1; j <= n / 2; j++) {
                        if (k > 0) {
                            c[2 * i][2 * j] = c[2 * i][2 * j - 1] = c[2 * i - 1][2 * j] = c[2 * i - 1][2 * j - 1] = 1;
                            k -= 4;
                        } else {
                            break;
                        }
                    }
                }
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        cout << c[i][j] << ' ';
                    }
                    cout << '\n';
                }
            } else {
                if (n == 2) {
                    cout << "Yes\n";
                    cout << "1 0\n0 1\n";
                    continue;
                }
                if (k == 2 || k == n * n - 2) {
                    cout << "No\n";
                    continue;
                }
                cout << "Yes\n";

                for (int i = 1; i <= n / 2; i++) {
                    for (int j = 1; j <= n / 2; j++) {
                        if ((i == 1 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 1) || (i == 2 && j == 2)) continue;
                        
                        if (k > 0) {
                            if (k == 6 || k == 10) break;
                            c[2 * i][2 * j] = c[2 * i][2 * j - 1] = c[2 * i - 1][2 * j] = c[2 * i - 1][2 * j - 1] = 1;
                            k -= 4;
                        } else {
                            break;
                        }
                    }
                }
                c[1][1] = c[1][2] = c[2][1] = c[2][3] = c[3][2] = c[3][3] = 1; // if(k == 6). k must be 6 or 10
                if (k == 10)
                    c[3][1] = c[4][1] = c[3][4] = c[4][4] = 1;
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        cout << c[i][j] << ' ';
                    }
                    cout << '\n';
                }
            }
        }
    }
    return 0;
}
// submit by Acerkaio.
```

---

## 作者：hcywoi (赞：1)

### 题解

显然地，$2\nmid k$ 无解。

分情况讨论。

1. $k\bmod 4=0$；

2. $k\bmod 4=2$。

对于情况 $1$，我们发现 $2\times 2$ 全 $1$ 的矩阵对行的异或值和列的异或值没有影响，选 $\dfrac{k}{4}$ 互不相同的 $2\times 2$ 矩阵填成全 $1$ 即可。

---

对于情况 $2$，当 $6\le k\le n^2-10$ 时，将矩阵左上角填成以下图形：

$$
\begin{pmatrix}
1 & 0 & 1 & 0 \\
1 & 1 & 0 & 0 \\
0 & 1 & 1 & 0 \\
0 & 0 & 0 & 0
\end{pmatrix}
$$

填完之后，$k\bmod 4=0$，即变成了情况 $1$。

---

当 $k=n^2-6$ 时，将矩阵左上角填成以下图形：

$$
\begin{pmatrix}
1 & 0 & 1 & 0 \\
1 & 1 & 0 & 0 \\
1 & 1 & 1 & 1 \\
1 & 0 & 0 & 1
\end{pmatrix}
$$

填完之后，$k\bmod 4=0$，即变成了情况 $1$。

---

当 $k=2$ 或 $k=n^2-2$ 时，我们要将一个 $n\times n$ 的全 $0$ 或全 $1$ 矩阵选两个位置填 $1$ 或填 $0$。

我们发现**当且仅当** $n=2$ 时，我们能构造出合法的矩阵，$n\neq 2$ 时无解。

显然，操作两个位置后，行异或值改变的数量和列异或值改变的数量之和**至少**为 $2$，**至多**为 $4$，因此当 $n\neq 2$ 时，无解。

---

### 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    if (k % 2) {
        std::cout << "No\n";
        return;
    }

    int t = k % 4;
    std::vector a(n, std::vector<int>(n));
    if (k % 4 == 2) {
        if (k >= 6 && k <= n * n - 10) {
            a[0][0] = a[0][2] = a[1][0] = a[1][1] = a[2][1] = a[2][2] = 1;
            k -= 6;
        } else if (k == n * n - 6) {
            a[0][0] = a[0][2] = a[1][0] = a[1][1] = a[2][0] = a[2][1] = a[2][2] = a[2][3] = a[3][0] = a[3][3] = 1;
            k -= 10;
        } else if (n != 2) {
            std::cout << "No\n";
            return;
        } else {
            a[0][0] = a[0][1] = 1;
        }
    }
    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < n; j += 2) {
            if (t && i < 4 && j < 4) {
                continue;
            }
            for (auto x: {i, i + 1}) {
                for (auto y: {j, j + 1}) {
                    a[x][y] = k ? 1 : 0;
                }
            }
            k = std::max(0, k - 4);
        }
    }
    std::cout << "Yes\n";
    for (int i = 0; i < n; i ++ ) {
        for (int j = 0; j < n; j ++ ) {
            std::cout << a[i][j] << " \n"[j == n - 1];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t -- ) {
        solve();
    }

    return 0;
}
```

---

## 作者：arrow_king (赞：0)

简单易想小构造。

# 1

$k$ 为奇数的时候显然无解。

# 2

我们发现，在矩阵中放一个 $2\times2$ 的全 $1$ 矩阵不会对任何行列的奇偶性产生影响，而 $1$ 的数量会增加 $4$。因此如果 $k\equiv 0\pmod4$ 就可以直接通过放置 $2\times2$ 来做到。

# 3

现在只剩 $k\bmod 4=2$ 的情况。我们可以找到这样一种结构，其中 $k=6$：

```plain
1 0 0 ... 0 0 1
1 0 0 ... 0 1 0
0 0 0 ... 0 0 0
. . . .   . . .
. . .  .  . . .
. . .   . . . .
0 0 0 ... 0 0 0
0 0 0 ... 0 0 0
0 0 0 ... 0 1 1
```
这样可以做到让每行每列的和都是偶数，而总浪费空间也是 $6$ 格，剩下的位置还可以通过放置 $2\times 2$ 来达到效果。比如 $n=6,k=14$ 的时候就可以按如下方案构造：

```plain
101101
101110
110000
110000
000000
000011
```

最后只剩下 $k=2$ 或 $k=n^2-2$ 的情况，上述构造无法成立。但实际上，上述情况当且仅当 $n=2$ 时有解，因此这题做完了。

---

## 作者：oyoham (赞：0)

### Problem  
[CF 传送门](https://codeforces.com/contest/1917/problem/E)  
给定 $n,k$，其中 $n$ 是偶数，求一个 $n\times n$ 的 $01$ 矩阵满足每一列和每一行的异或和相等，且矩阵的所有元素和等于 $k$。
### solution & proof  
开始大分类讨论与构造：  
当 $k$ 为奇数时，显然无解，因为所有异或和为奇数，而 $n$ 为偶数，所以直接输出 `No`。  
当 $k=2$ 或 $k=n^2-2$ 且 $n\ne 2$ 时，矩阵上只有两个位置与其他位置不同，而这两个位置不可能同时出现在同一列与同一行，因此必然有一列（或一行）与其他列（或行）的异或值不等，所以直接输出 `No`。  
剩下全部情况都有解。  
当 $k$ 为 $4$ 的倍数时，用 $2\times2$ 的 $1$ 矩阵来填充，这样每行异或与每列异或均不改变。  
当 $k=n=2$ 时，随意构造均符合题意。  
当 $k \bmod 4 = 2$ 且 $k> 6$ 且 $k\ne n^2-2$，构造右上角矩阵如下：  
$$ \begin{bmatrix}
	1 & 0 & 1 & 0  \\
	0 & 0 & 1 & 1  \\
	1 & 1 & 1 & 1  \\
	0 & 1 & 1 & 0  \\
\end{bmatrix}$$  
然后剩余部分可用 $2\times 2$ 的 $1$ 矩阵来填充。  
当 $k=6$ 时，将 $k=n^2-6$ 的构造矩阵取反即可。  
结束分类讨论。  
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int T=read();
int a[2005][2005];
int main(){
	while(T--){
		int n=read(),k=read();
		if(n^2&&(k==2||k==n*n-2)||k%2){
			puts("no");
			continue;
		}
		puts("yes");
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=0;
			}
		}
		if(n==2){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					a[i][j]=!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(k>>1<i);
				}
			}
		}
		else if(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(k%4)){
			int cnt=0;
			for(int i=1;i<=n&&cnt<<2<k;i+=2){
				for(int j=1;j<=n&&cnt<<2<k;j+=2){
					++cnt;
					a[i][j]=a[i+1][j]=a[i+1][j+1]=a[i][j+1]=1;
				}
			}
		}
		else{
			int cnt=3-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(k^6);
			for(int i=1;i<=n&&cnt<<2<k;i+=2){
				for(int j=1;j<=n&&cnt<<2<k;j+=2){
					if(i<4&&j<4) continue;
					++cnt;
					a[i][j]=a[i+1][j]=a[i+1][j+1]=a[i][j+1]=1;
				}
			}
			a[1][2]=a[1][4]=a[2][1]=a[2][2]=a[4][1]=a[4][4]=!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(k^6);
			a[1][3]=a[1][1]=a[2][3]=a[2][4]=a[3][1]=a[3][4]=a[3][3]=a[3][2]=a[4][2]=a[4][3]=!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(k==6);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				putchar(a[i][j]|48);
				putchar(32);
			}
			putchar(10);
		}
	}
}
```

---

## 作者：RDFZchenyy (赞：0)

这是本人在 CF 上筛选 Constructive 时看到的一道好题。

## 题目大意

给定两个数 $n,k$，其中 $n$ 为偶数。请构造一个有 $k$ 个 $1$ 的 $01$ 矩阵，使得矩阵每一列的所有数 $\oplus$ 起来后的值相同，同时使得矩阵每一行的所有数 $\oplus$ 起来后的值相同，或说明这是不可能的。

## 按步分析

### 问题 #1

考虑这样一个问题，对于一个足够大的矩阵，$k>0$ 时 $k$ 最小为多少才是可能的？

这启发我们什么？

### 答案 #1

我们试着构造一个 $k=1$ 的矩阵，这一定是不可能的。

我们只能让一行的 $\oplus$ 值取 $1$，故不可能。同时这也说明了所有 $k$ 取奇数的情况都不行，当 $k$ 为奇数时，我们只能使得奇数行的 $\oplus$ 值取 $1$。

我们接着试着构造一个 $k=2$ 的矩阵，这也一定是不可能的。

我们可以发现 $k=2$ 时，我们只能使两行 $\oplus$ 的值（将两个 $1$ 填入不同的两行）或者没有一行 $\oplus$ 的值（将两个 $1$ 填入同一行）改变。

但将两个 $1$ 填入同一行时，必然会改变两列 $\oplus$ 的值。这说明除非 $n=2$ 时，$k=2$ 不可行。同理，$k=n^2-2$ 时不可行。

接着试着构造一个 $k=4$ 的矩阵，这好像是可能的。

回顾 $k=2$ 时，我们之所以不能构造，是因为我们不可以把对某一行 $\oplus$ 值的影响消去。但是 $k=4$ 时，将一个 $2\times 2$ 的都填满 $1$ 的格子放入矩阵中是没有影响的。

这就说明：

$k=2,k=2m+1(m\in \mathbb{Z})$ 时不行，$k=4m(m\in \mathbb{Z})$ 时可行，整齐地排 $m$  个 $2\times2$ 的填满 $1$ 的格子。


### 问题 #2

$k=4m+2(m\in\mathbb{Z})$ 时真的不可行吗？

请尝试构造 $n=4,k=6$ 与 $n=4,k=10$。

这启发我们什么？

### 解答 #2

我们发现这好像是可行的。

我们把两个 $2\times 2$ 的填满 $1$ 的格子叠一个角地 $\oplus$ 在一起，像这样：

$$
\begin{bmatrix}
1 & 1 & 0 \\
1 & 1 & 0 \\
0 & 0 & 0
\end{bmatrix}

\oplus

\begin{bmatrix}
0 & 0 & 0 \\
0 & 1 & 1 \\
0 & 1 & 1
\end{bmatrix}

=
\begin{bmatrix}
1 & 1 & 0 \\
1 & 0 & 1 \\
0 & 1 & 1
\end{bmatrix}
$$

这正好是 $6$ 个。但是由于 $n=4$ 故我们需要把这个东西补成 $4\times 4$，如：

$$
\begin{bmatrix}
1 & 1 & 0 & 0\\
1 & 0 & 1 & 0\\
0 & 1 & 1 & 0\\
0 & 0 & 0 & 0\\
\end{bmatrix}
$$

那如果 $n=4,k=10$ 呢？

我们把 $4\times4$ 所有数的都取反即可实现，如：

$$
\begin{bmatrix}
0 & 0 & 1 & 1\\
0 & 1 & 0 & 1\\
1 & 0 & 0 & 1\\
1 & 1 & 1 & 1\\
\end{bmatrix}
$$

这告诉我们，我们不妨留下左上角不处理，剩下的部分直接填 $2\times 2$ 的填满 $1$ 的方格即可。

## 解法分析

当 $k=2m+1(m\in \mathbb{Z})$ 时不可行。

当 $n=2$ 时，所有 $k=2m$ 都可行，特殊处理。

当 $n\not =2$ 时，$k=2$ 或 $k=n^2-2$ 不可行。

此外，若 $k=4m(m\in \mathbb{Z})$，强行堆放 $2\times2$ 的填满 $1$ 的方格即可。

否则我们可以留下左上 $4\times 4$ 不填，余下的位置直接按需要堆满 $2\times 2$，直至还需填写至多 $6$ 个 $1$ 或余下位置填满。此时左上角必然还需填写 $6$ 或 $10$ 个 $1$，此时按情况填写：

$$
\begin{bmatrix}
1 & 1 & 0 & 0\\
1 & 0 & 1 & 0\\
0 & 1 & 1 & 0\\
0 & 0 & 0 & 0\\
\end{bmatrix}

\begin{bmatrix}
0 & 0 & 1 & 1\\
0 & 1 & 0 & 1\\
1 & 0 & 0 & 1\\
1 & 1 & 1 & 1\\
\end{bmatrix}
$$

其中的一个即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

const int s[2][2]={
    {2,4},
    {4,2}
};
const int t[4][4]={
    {1,1,0,0},
    {1,0,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

int n,k;
int a[1005][1005];
void run(){
    cin>>n>>k;
    if(k&1){
        cout<<"No"<<endl;
        return;
    }
    if(n==2){
        cout<<"Yes"<<endl;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                cout<<(int)(k>=s[i][j])<<" ";
            }
            cout<<endl;
        }
    }else{
        if(k==2||k==n*n-2){
            cout<<"No"<<endl;
            return;
        }

        cout<<"Yes"<<endl;
        if(k&2){
            for(int i=0;i<n/2;i++){
                for(int j=0;j<n/2;j++){
                    if(i<=1&&j<=1){
                        continue;
                    }
                    if(k>=8){
                        a[(i<<1)][(j<<1)]=a[(i<<1)|1][(j<<1)]=a[(i<<1)][(j<<1)|1]=a[(i<<1)|1][(j<<1)|1]=1;
                        k-=4;
                    }
                }
            }
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    if(k==6){
                        a[i][j]=t[i][j];
                    }else if(k==10){
                        a[i][j]=t[i][j]^1;
                    }
                }
            }
        }else{
            for(int i=0;i<n/2;i++){
                for(int j=0;j<n/2;j++){
                    if(k>=4){
                        a[(i<<1)][(j<<1)]=a[(i<<1)|1][(j<<1)]=a[(i<<1)][(j<<1)|1]=a[(i<<1)|1][(j<<1)|1]=1;
                        k-=4;
                    }
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<a[i][j]<<" ";
                a[i][j]=0;
            }
            cout<<endl;
        }
    }

    return;
}

int T;
int main(){
    cin>>T;
    for(int i=1;i<=T;i++){
        run();
    }

    return 0;
}
```

## 做一赠一

请解决 $n$ 为奇数时的情况。

### 解答

记 $n=2x+1$。

我们不妨先说明这样一个事情：我们只需要解决所有 $k=2m(m\in\mathbb{Z})$ 的情况即可。这是因为在其它情况下，我们只需要把所有数取反即可解决。

对于 $k=2m(m\in\mathbb{Z})$ 的情况，显然每行 $\oplus$ 的值必须为 $0$，故每行最多填写 $2x$ 个 $1$，此时最多填写 $4x^2+2x$ 个 $1$，这说明 $k>4x^2+2x$ 时一定不行。

考虑怎么填写 $4x^2+2x$ 这种情况，我们可以构造如下：

$$
\begin{bmatrix}
0 & 1 & 1 & \cdots & 1 & 1 \\
1 & 0 & 1 & \cdots & 1 & 1\\
1 & 1 & 0 & \cdots & 1 & 1\\
\vdots & \vdots & \vdots & \ddots & \vdots & \vdots \\
1 & 1 & 1 & \cdots & 0 & 1\\
1 & 1 & 1 & \cdots & 1 & 0\\
\end{bmatrix}
$$

接着对于一些 $k$ 不接近这个数的 $k$，我们可以放弃掉第一行和第一列，先从右下角起排布若干 $2\times2$ 的填满 $1$ 的方格，接着在左上角的 $3\times 3$ 中按照刚才的方案填入 $6$ 个（当然也可以填入 $0$ 或 $4$ 个）$1$：

$$
\begin{bmatrix}
1 & 1 & 0 \\
1 & 0 & 1 \\
0 & 1 & 1
\end{bmatrix}
$$

此时可以容纳 $k=4m$ 或 $k=4m+2$ 的所有情况（注意 $k\not= 4$ 仍需满足），其中 $m\le x^2$，即 $k\le 4x^2+2$ 的所有情况。

这说明我们接着只需满足 $4x^2+4\le k\le 4x^2+2x$ 的情况即可。

我们考虑在 $4x^2+2x$ 的基础上把对角线上每一个单位做如下的变更：

$$
\begin{bmatrix}
1 & 0 \\
1 & 1
\end{bmatrix}

\rightarrow

\begin{bmatrix}
0 & 1\\
0 & 0
\end{bmatrix}
$$

这会使得 $1$ 的总个数减少 $2$。

我们依次进行第 $2,4,6,\cdots,2x$ 行的变更，每次减少 $2$，可使得总个数从 $4x^2+2x$ 变为 $4x^2$，这会覆盖所有的偶数 $k$ 的值。

带着对星海的向往，谨此作答。 $\square$

这就完成了对解答过程的说明。

此外，对于这部分的代码，读者可自行实现。

## Change Log

+ 第二次提交：修改了 答案#1 中的逻辑错误。

---

## 作者：Exp10re (赞：0)

分类讨论题 be like:

## 解题思路

注意到 $k$ 为奇数显然无解。

考虑 $k$ 为偶数的情况，进行分类讨论：

### $k=4m$

注意到因为 $n$ 为偶数，因此 $n\times n$ 的矩阵等同于 $(\frac n 2)\times(\frac n 2)$ 个 $2\times2$ 的小矩阵构成的矩阵。

将其中任一 $2\times2$ 的小矩阵全部填 $1$ 显然不会改变异或和，总共填 $m$ 个 $2\times2$ 的小矩阵即可。

### $k=2$ 或 $k=n^2-2$

这两种情况本质相同。

注意到当 $n=2$ 时 $k=n^2-2=2$ 是可行的，但对于 $n\gt2$ 的情况，$k=2$ 意味着只会有两行（或者两列）异或和为 $1$，其余为 $0$。显然无解。

特判即可。

### 除上述情况外的 $k$ 为偶数的情况

显然 $k=4m+2$。

因为 $n=2$ 已经特判过了，接下来默认 $n\ge4$。

注意到当 $k=6$ 时可以用以下方式构造一个矩阵：

| $1$ | $1$ | $0$ | $0$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $0$ | $1$ | $0$ |
| $0$ | $1$ | $1$ | $0$ |
| $0$ | $0$ | $0$ | $0$ |

当 $k=10$ 时，考虑在 $k=8$ 的矩阵的基础上用以下方式构造一个矩阵：

| $1$ | $1$ | $1$ | $1$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $1$ | $1$ | $1$ |
| $0$ | $0$ | $0$ | $0$ |
| $0$ | $0$ | $0$ | $0$ |

以上是 $k=8$ 的矩阵，接下来构造 $k=10$。

| $1$ | $1$ | $1$ | $1$ |
| :----------: | :----------: | :----------: | :----------: |
| $\color{red}0$ | $\color{red}0$ | $1$ | $1$ |
| $\color{red}1$ | $0$ | $\color{red}1$ | $0$ |
| $0$ | $\color{red}1$ | $\color{red}1$ | $0$ |

其中红色代表改动的位置（和 $k=6$ 的图形相似）。

注意到总和增加了 $2$，使用 $k=4m$ 的做法构造出和为 $k-2$ 的矩阵之后使用上述方法进行变换即可。

---

## 作者：ethan0328 (赞：0)

## 思路
发现我们如果把一个 $2\times2$ 的矩阵填满 $1$，不会有影响。

当 $k$ 为 $4$ 的倍数，直接填就可以了。

当 $k$ 为奇数显然无解，因为你无法让每行奇偶性相同。

当 $k$ 除 $4$ 余 $2$，如果 $k$ 为 $2$ 或 $n\times n-2$ 时无解。

不然的话，我们可以在一个 $4\times4$ 的矩形里把 $(1,1)$，$(1,2)$，$(2,1)$，$(2,3)$，$(3,2)$，$(3,3)$ 填 $1$，剩下直接填。

注意到 $k=n\times n-6$ 时这时爆的。我们可以在 $4\times4$ 的矩形里多填 $(1,3)$，$(1,4)$，$(4,3)$，$(4,4)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int t,k,n,a[N][N];
bool flg;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		if(k&1)
		{
			cout<<"No\n";
			continue;
		}
		if(n==2)
		{
			cout<<"Yes\n";
			if(k==0)
			{
				cout<<"0 0\n0 0\n";
			}else if(k==2)
			{
				cout<<"1 0\n0 1\n";
			}else
			{
				cout<<"1 1\n1 1\n";
			}
			continue;
		}
		if(k==2||k==n*n-2)
		{
			cout<<"No\n";
			continue;
		}
		cout<<"Yes\n";
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				a[i][j]=0;
			}
		}
		flg=0;
		if(k%4!=0)
		{
			a[1][1]=a[1][2]=a[2][1]=a[2][3]=a[3][2]=a[3][3]=1;
			if(k==n*n-6)
			{
				a[3][1]=a[4][1]=a[3][4]=a[4][4]=1;
				k-=4;
			}
			flg=1;
			k-=6;
		}
		for(int i=1;i<=n;i+=2)
		{
			for(int j=1;j<=n;j+=2)
			{
				if(k==0)
				{
					break;
				}
				if(flg==1&&i<=4&&j<=4)
				{
					continue;
				}
				a[i][j]=a[i+1][j]=a[i][j+1]=a[i+1][j+1]=1;
				k-=4;
			}
			if(k==0)
			{
				break;
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				cout<<a[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
}
```

---

## 作者：EuphoricStar (赞：0)

$2 \nmid k$ 显然无解。

若 $4 \mid k$，发现给一个全 $2 \times 2$ 子矩形全部异或 $1$ 不会对行异或和和列异或和造成影响。那么我们找到 $\frac{k}{4}$ 个全 $0$ 的 $2 \times 2$ 子矩形填 $1$ 即可。

否则若 $k = 2$ 或 $k = n^2 - 2$，除 $n = 2$ 外无解。

否则我们有一个 $k = 6$ 的构造，即令 $a_{1, 1} = a_{1, 2} = a_{2, 1} = a_{2, 3} = a_{3, 2} = a_{3, 3} = 1$。

若 $k$ 更大，把左上角的 $4 \times 4$ 矩形抠掉后再找 $2 \times 2$ 全 $0$ 矩形，全部填 $1$。

若 $k$ 还有剩余，在左上角 $4 \times 4$ 矩形中找和为 $1$ 的 $2 \times 2$ 子矩形，全部异或上 $1$，可以使得这个子矩形的和变为 $3$。重复这样找直到 $k$ 被消耗尽即可。容易发现一定能找到这样的子矩形。

[code](https://codeforces.com/problemset/submission/1917/238939566)

---

## 作者：Phartial (赞：0)

# CF1917E Construct Matrix 题解

首先显然 $k$ 是奇数时无解。

注意到我们可以将矩阵中的任意一个 $2\times2$ 的全 $0$ 子矩阵改成全 $1$ 子矩阵，这给了我们一种将 $k$ 加 $4$ 的方案，再以 $k=0$ 为基础，我们就能得到任意 $k=4v$。

考虑 $k=4v+2$，我们有这样一种构造：

```
110
101
011
```

我们可以将矩阵中的任意一个 $3\times3$ 的全 $0$ 子矩阵改成这种模式，这给了我们一种将 $k$ 加 $6$ 的方案。由 $k=0$ 的方案可以得到 $k=6$ 的方案，再通过不断地将 $k$ 加 $4$，我们就可以得到所有 $k=4v+2$（$v>0$）。

但你发现这样做会浪费一些空间：

```
11001111
10101111
01101111
00001111
11111111
11111111
11111111
11111111
```

这是当 $k=n^2-10$ 时的构造，而我们已经无法继续得到 $k=n^2-6$ 了（因为没有空地放 $2\times2$ 的全 $1$ 子矩阵）。

注意到这样一个事实：对于一种合法方案，我们将其中的数取反（$0$ 变 $1$，$1$ 变 $0$）后仍然合法，且 $k$ 变成了 $n^2-k$。因此对于 $k>\frac{n^2}{2}$，我们只需要构造出 $n^2-k$ 并将其中的数取反即可规避掉直接构造 $k\ge n^2-6$ 的情况。

特判一下 $n=2,k=2$ 的情况即可。

```cpp
#include <iostream>

using namespace std;

const int kN = 1001;
const int kT[4][4] = {
    {1, 1, 0, 0},
    {1, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}};

int t, n, k, a[kN][kN];

void G(int c) {  // 生成 c 个 2*2 的全 1 子矩阵
  for (int i = 0, j = 4 * a[0][0]; c--;) {
    a[i][j] = a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 1] = 1;
    if ((j += 2) == n) {
      i += 2, j = 4 * (a[0][0] && i < 4);
    }
  }
}
void S(int k, int v0) {
  if (k == 2) {
    cout << "No\n";
    return;
  }
  fill(a[0], a[n], 0);
  if (k % 4 == 0) {
    G(k / 4);
  } else {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        a[i][j] = kT[i][j];
      }
    }
    G((k - 6) / 4);
  }
  cout << "Yes\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << (v0 ^ a[i][j]) << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n >> k;
    if (k & 1) {
      cout << "No\n";
      continue;
    }
    if (n == 2 && k == 2) {
      cout << "Yes\n1 1\n0 0\n";
      continue;
    }
    if (k <= n * n / 2) {
      S(k, 0);
    } else {
      S(n * n - k, 1);
    }
  }
  return 0;
}
```


---

## 作者：dalao_see_me (赞：0)

感觉比 F 有趣多了。

$n=2$ 很 easy，考虑 $n\neq 2$，显然 $k$ 一定是 $2$ 的倍数，然后很容易想到可以填一个 $2\times 2$ 的 $1$ 矩阵，这样就能做 $k\bmod4=0$ 的情况了。

考虑 $k\bmod4=2$ 怎么做，容易想到可以填一行，但这样很不优，再想一下发现问题的本质相当于要构造 $6$ 个 $1$，随便画一下发现可以变成一个 $3\times3$ 矩阵扣掉主对角线，这样右下角还能空出来一个 $2\times2$。

虽然这种构造会空出来一些缝隙，但是可以发现 $k=2$ 显然无解，$k=n^2-2$ 和 $k=2$ 是一样的所以也无解，其它的情况都是可以构造出解的。

不要忘记特判 $n=2$ /cf。

---

## 作者：翼德天尊 (赞：0)

首先 $k$ 为奇数时一定无解。除此之外 $n=2$ 时一定有解。

显然 $4$ 个一组摆成 $2\times 2$ 的矩形是一个很优的策略。且由于 $n$ 为偶数，故当 $k\equiv 0\pmod 4$ 时一定有解。下面考虑 $k\equiv 2\pmod 4$。

从最小的情况开始考虑：对于 $n=4$，$k\equiv 2\pmod 4$ 时该如何构造：

- $k=2,14$ 时一定无解。
- $k=6$ 时，可以将 $(1,1),(1,3),(2,2),(2,3),(3,1),(3,2)$ 赋值为 $1$。
- $k=10$ 时，可以在 $k=6$ 的基础上将 $(3,3),(3,4),(4,3),(4,4)$ 赋值为 $1$。

不难发现这个东西可以扩展：当 $k=2$ 或 $k=n^2-2$ 的时候，一定无解；否则一定可以如上构造。


---

