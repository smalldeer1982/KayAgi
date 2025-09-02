# Scale

## 题目描述

Tina 有一个 $n$ 行 $n$ 列的正方形网格。网格中的每个格子要么是 $0$，要么是 $1$。

Tina 想要将网格按 $k$ 的比例缩小（$k$ 是 $n$ 的约数）。为此，Tina 会将网格划分为 $k \times k$ 的不重叠小块，使得每个格子恰好属于一个小块。

然后，Tina 用该小块中格子的值来替换整个小块为一个格子。保证每个小块中的所有格子值都相同。

例如，下面的演示展示了一个网格按 $3$ 的比例缩小的过程。

原始网格

$0$  $0$  $0$  
$1$  $1$  $1$  
$0$  $0$  $0$  
$1$  $1$  $1$  
$0$  $0$  $0$  
$1$  $1$  $1$  
$1$  $1$  $1$  
$0$  $0$  $0$  
$1$  $1$  $1$  
$0$  $0$  $0$  
$1$  $1$  $1$  
$0$  $0$  $0$  

缩小后的网格

$0$  $1$  
$1$  $0$  

请帮助 Tina 按 $k$ 的比例缩小网格。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
4 4
0000
0000
0000
0000
6 3
000111
000111
000111
111000
111000
111000
6 2
001100
001100
111111
111111
110000
110000
8 1
11111111
11111111
11111111
11111111
11111111
11111111
11111111
11111111```

### 输出

```
0
01
10
010
111
100
11111111
11111111
11111111
11111111
11111111
11111111
11111111
11111111```

# 题解

## 作者：ycy1124 (赞：5)

### 题目大意
有一个 $n \times n$ 的 $01$ 矩阵，现在要将它变成一个 $(n \div k)\times (n \div k)$ 的 $01$ 矩阵。原矩阵从左上角开始，每一个 **互不重叠** 的 $k \times k$ 的子矩阵的所有元素都相等，变化时将所有的 $k \times k$ 的子矩阵缩小成一个 $1 \times 1$ 的元素与原来子矩阵相等的新的子矩阵。所有缩小后的子矩阵按原来的位置拼在一起后就是新矩阵。

### 想法
已知每一个  $k \times k$ 的子矩阵的所有元素都相等，所以我们只需要知道它的 **任意一个位置** 的元素我们就可以求出它缩小后的 $1 \times 1$ 的矩阵。所以我们可以在输入后枚举一遍 **原矩阵** 所有 $k \times k$ 的 **子矩阵** 的左上角元素输出（其他位置也可以）。

### 做法
由于只需要枚举每个子矩阵的左上角，实现非常的简单，这里就不过多阐述。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1001][1001];
int main(){
	int t;
	scanf("%d",&t);
	while(t){
		t--;
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n/k;i++){
			for(int j=1;j<=n/k;j++){
				cout<<a[(i-1)*k+1][(j-1)*k+1];//枚举每个子矩阵的左上角输出。（本题唯一的难度）
			}
			cout<<'\n';
		}
	}
	return 0;
} 
```
[AC 记录](https://www.luogu.com.cn/record/169049051)。

最后复杂度 $\mathcal{O}(TN^2)$ 通过此题。

---

## 作者：Manki23333333 (赞：1)

~~赛时调试用的 `freopen` 没删挂了一次，结果又 in queue 了十分钟。~~

这题因为每个块的字符都一样，所以我们不妨取左上角。

每隔 $k$ 次取一个数，公式 $(x-1) \mod k = 0$。

```
#include <bits/stdc++.h>
 
using namespace std;
 
int main () {
// 	freopen ("temp.out", "w", stdout);
	
	int T;
	
	cin >> T;
	
	while (T --) {
		int n, k;
		char x;
		cin >> n >> k;
		
		for (int i = 1 ; i <= n ; i ++) {
			for (int j = 1 ; j <= n ; j ++) {
				cin >> x;
				
				if ((((i - 1) % k == 0)) && ((j - 1) % k == 0))  {
					cout << x;
				}
			}
			
			if (((i - 1) % k == 0))
				cout << endl;
		}
 
	}
	return 0;
}
```

---

## 作者：残阳如血 (赞：1)

### $\textbf{Description}$

给定 $n,k$ 和一个 $n\times n$ 的网格。

现在要将每 $k\times k$ 个网格变为一个 $1\times 1$ 的网格，请输出缩小后的网格。

保证 $k$ 是 $n$ 的因数且每 $k\times k$ 个格子内的数字相同。

### $\textbf{Solution}$

由于题目已经保证了每 $k\times k$ 个格子内的数字相同，所以取每个 $k\times k$ 的格子中左上角的数并输出即可。

为了保证每次取左上角的数，下标偏移量应为 $k$。

详见代码。

### $\textbf{Code}$

```cpp
#include <bits/stdc++.h>
const int N = 1e3 + 10;

int T, n, k;
char a[N][N];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	for (std::cin >> T; T; --T) {
		std::cin >> n >> k;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				std::cin >> a[i][j]; // 需要读入单个数字，故用 char 存储
		for (int i = 1; i <= n; i += k) { // 跳着取数
			for (int j = 1; j <= n; j += k)
				std::cout << a[i][j];
			std::cout << '\n';
		}
	}
	std::cout.flush();
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

这道题是一道简单题。

我们可以发现，把图像缩小 $k$ 倍就等价于跳过一些东西输出，那么跟 $k = 1$ 的情况一样，我们只需要将循环的步长设为 $k$ 即可。

```cpp
#include <iostream>
using namespace std; 
int n, m;
char ch[1005][1004];
int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> ch[i][j];
			}
		}
		for (int i = 1; i <= n; i += m) {
			for (int j = 1; j <= n; j += m) {
				cout << ch[i][j];
			}
			cout << '\n';
		}
	}
}
```

---

## 作者：bryce (赞：0)

## 思路
枚举行和列，每次 $+k$，用一个数组记录缩小后位置上的数，输出答案。
## 代码
```cpp
#include<iostream>
#include<cstring>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 1e3 + 10;
int T, n, k;
bool a[N][N], b[N][N];

int main(){
    T = read();
    while (T--){
        n = read(), k = read();
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                char c;cin >> c;
                if (c == '1') a[i][j] = 1;//转换
            }
        }
        for (int x = 1, i = 1; x <= n && i <= n / k; x += k, i++){
            for (int y = 1, j = 1; y <= n && j <= n / k; y += k, j++){//枚举行和列
                b[i][j] = a[x][y];//记录缩小后的答案
            }
        }
        for (int i = 1; i <= n / k; i++){
            for (int j = 1; j <= n / k; j++){
                cout << b[i][j];
            }
            cout  << '\n';
        }
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
    }
    return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

这题看起来很复杂，但是实际上有一种非常非常简单的做法。

因为保证了每个网格所有数字一样，直接把要缩成网格的一块左上角输出就好了。

```cpp
#include<bits/stdc++.h>
#error Don't copy the solution!
using namespace std;
int t;
char a[1005][1005];
int main(){
	cin >> t;
	while (t--){
		int n, m;
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> a[i][j];
		for (int i = 1; i <= n; i += m){
			for (int j = 1; j <= n; j += m)
				cout << a[i][j];
			cout << "\n";
		}
	}
}
```

---

## 作者：GoldenCreeper (赞：0)

我们只需要对每个小矩阵中取一个值输出即可。

参考实现：

```cpp
/*

 @Author: CreeperOI
 @Problem: B_Scale
 @Start Time: 2024-07-26 22:41
 @Finish Time: 2024-07-26

*/
#include <bits/stdc++.h>
// #define int long long
using namespace std;

int const N = 1e5 + 10, mod = 1e9 + 7;
int n, m, k;
char s[1145][1145];

void Main(){
    cin >> n >> k;
    for (int i = 1;i <= n;++i) scanf("%s", s[i] + 1);
    for (int i = 1;i <= n;i += k) {
        for (int j = 1;j <= n;j += k) {
            cout << s[i][j];
        }
        cout << endl;
    }
}
signed main() {
    // freopen("cpp.in", "r", stdin);
    // freopen("cpp.out", "w", stdout);
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--) Main();
    // cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
    return 0;
}
```

---

## 作者：GeXiaoWei (赞：0)

# CF1996B Scale
## 解析
本题考察模拟，难度大约在红橙左右。

只需要将每一个 $k\times k$ 的正方形的右下角位置遍历出来，输出该正方形任意一点即可，因为题目保证，同一区块中的每个单元格都具有相同的值。

右下角还是很好遍历的，因为它一定是 $k$ 的整倍数且小于等于 $n$。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,a[1005][1005];
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld %lld",&n,&k);
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%1d",&a[i][j]);
		for(int i=k;i<=n;i+=k){
			for(int j=k;j<=n;j+=k) printf("%lld",a[i][j]);
			printf("\n");
		}
	}
	return 0;
} 
```

---

## 作者：donnieguo (赞：0)

## 题意简述

有 $t$ 组数据。

每组数据给定两个正整数 $n$ 和 $k$ 以及一个 $n \times n$ 的矩阵，要求你把矩阵缩小 $k$ 倍后输出。

保证 $n$ 是 $k$ 的倍数。

## 思路

这题其实超级简单。

回想我们正常输出一个矩阵的时候，每次都是 `i++` 和 `j++`，这其实相当于将矩阵缩小 $1$ 倍输出。那么我们想要缩小 $k$ 倍，每次 `i += k` 和 `j += k` 就好了。

## AC code
```cpp
#include <iostream>
using namespace std;

int T, n, k;
char a[1010][1010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--)
	{
		cin >> n >> k;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) cin >> a[i][j];
		for (int i = 1; i <= n; i += k, cout << '\n')
			for (int j = 1; j <= n; j += k) cout << a[i][j];
	}
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## CF1996B

对于一个 $k\times k$ 的矩形区域，这 $k\times k$ 个字符一定是一样的，所以缩小之后的字符可以看作其中的任意一个字符。方便起见可以看作是左上角的字符，则输出的字符为 $(1+xk, 1+yk)$ 位置的字符，其中 $ x,y \in \N, 1+xk, 1+yk \le n$。

代码：

```cpp
void Main() {
  n = read(), k = read();
  for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
  for (int i = 1; i <= n; i += k) {
    for (int j = 1; j <= n; j += k) printf("%c", a[i][j]);
    printf("\n");
  }
}
```

---

## 作者：tzzl3035 (赞：0)

# CF1996B 题解
### 题目大意
有 $t$ 组数据，每组给出两个正整数 $n$ 和 $k$，保证 $n$ 是 $k$ 的倍数。接下来输入 $n$ 行 $n$ 列的字符，由一个或多个 $k$ 行 $k$ 列的 `0` 或 `1` 排列而成。请输出将每一个 $k$ 行 $k$ 列的字符简化成**单独 1 个** `0` 或 `1` 后的 $n\div k$ 行 $n\div k$ 列字符。
### 思路
遇到每个 $k$ 行 $k$ 列字符的第一行第一列，将其输出，并且适当加入换行即可。
### 核心代码
```cpp
void solve() {
  // 输入
  int n, k;
  std::cin >> n >> k;
  std::string ans = "";
  for(int i = 0; i < n; ++i) {
    // 输入每一行字符
    std::string s;
    std::cin >> s;
    // 处理答案
    for(int j = 0; j < n; ++j) {
      if(i%k == 0 && j%k == 0) ans += s[j];
    }
    if(i%k == 0) ans += "\n";
  }
  // 输出
  std::cout << ans;
}
```
### [RESULT](https://codeforces.com/contest/1996/submission/272764082)

---

## 作者：PineappleSummer (赞：0)

[CF1996B Scale](https://codeforces.com/contest/1996/problem/B)

要求将每个 $k\times k$ 的矩形合并为一个 $1\times 1$ 格子，由于题目已经保证 $k\times k$ 的矩形内部都相同数字，所以只需考虑其右下角的数字即可。

对于一个 $k\times k$ 的矩形，其右下角的位置 $(x,y)$ 满足 $x\bmod k=0$ 且 $y\bmod k=0$，枚举 $x,y$ 并更新答案即可。

```cpp
void solve () {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> c[i][j];
	for (int i = k; i <= n; i += k) {
		for (int j = k; j <= n; j += k) {
			d[i / k][j / k] = c[i][j]; // 更新答案
		}
	}
	for (int i = 1; i <= n / k; i++) {
		for (int j = 1; j <= n / k; j++)
			cout << d[i][j];
		cout << '\n';
	}
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
题目中说到，每一个 $k \times k$ 的网格中的值是一样的，所以我们枚举从 $1,k+1,2k+1$ 到 $n-k+1$ 的每一行和从 $1,k+1,2k+1$ 到 $n-k+1$ 的每一列，输出这些行列上的数字就是答案。
### 代码
```cpp
#include<iostream>
#define N 1005
bool mp[N][N];
signed main(){
	int t;std::cin>>t;
	while(t--){
		int n,k;
		std::cin>>n>>k; 
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%1d",&mp[i][j]);
		for(int i=1;i<=n;i+=k){
			for(int j=1;j<=n;j+=k)
				std::cout<<mp[i][j];
			std::cout<<std::endl;
		}
	} 
}
```

---

