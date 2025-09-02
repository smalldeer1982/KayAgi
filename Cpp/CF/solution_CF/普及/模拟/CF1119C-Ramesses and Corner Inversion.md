# Ramesses and Corner Inversion

## 题目描述

Ramesses came to university to algorithms practice, and his professor, who is a fairly known programmer, gave him the following task.

You are given two matrices $ A $ and $ B $ of size $ n \times m $ , each of which consists of $ 0 $ and $ 1 $ only. You can apply the following operation to the matrix $ A $ arbitrary number of times: take any submatrix of the matrix $ A $ that has at least two rows and two columns, and invert the values in its corners (i.e. all corners of the submatrix that contain $ 0 $ , will be replaced by $ 1 $ , and all corners of the submatrix that contain $ 1 $ , will be replaced by $ 0 $ ). You have to answer whether you can obtain the matrix $ B $ from the matrix $ A $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/07e01026afbc60b96857b7392bf73ad937a6aa47.png)An example of the operation. The chosen submatrix is shown in blue and yellow, its corners are shown in yellow.Ramesses don't want to perform these operations by himself, so he asks you to answer this question.

A submatrix of matrix $ M $ is a matrix which consist of all elements which come from one of the rows with indices $ x_1, x_1+1, \ldots, x_2 $ of matrix $ M $ and one of the columns with indices $ y_1, y_1+1, \ldots, y_2 $ of matrix $ M $ , where $ x_1, x_2, y_1, y_2 $ are the edge rows and columns of the submatrix. In other words, a submatrix is a set of elements of source matrix which form a solid rectangle (i.e. without holes) with sides parallel to the sides of the original matrix. The corners of the submatrix are cells $ (x_1, y_1) $ , $ (x_1, y_2) $ , $ (x_2, y_1) $ , $ (x_2, y_2) $ , where the cell $ (i,j) $ denotes the cell on the intersection of the $ i $ -th row and the $ j $ -th column.

## 说明/提示

The examples are explained below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/e8b2b05f1d91acad1dd27cd7e9d641b53a14a9dc.png)Example 1.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/a67a1a76d04df99ed90143acfb49e6763fb445d5.png)Example 2.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/8179b88f909d57a1d5601735cc5b6ce16cfe2cb8.png)Example 3.

## 样例 #1

### 输入

```
3 3
0 1 0
0 1 0
1 0 0
1 0 0
1 0 0
1 0 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
6 7
0 0 1 1 0 0 1
0 1 0 0 1 0 1
0 0 0 1 0 0 1
1 0 1 0 1 0 0
0 1 0 0 1 0 1
0 1 0 1 0 0 1
1 1 0 1 0 1 1
0 1 1 0 1 0 0
1 1 0 1 0 0 1
1 0 1 0 0 1 0
0 1 1 0 1 0 0
0 1 1 1 1 0 1
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
3 4
0 1 0 1
1 0 1 0
0 1 0 1
1 1 1 1
1 1 1 1
1 1 1 1
```

### 输出

```
No
```

# 题解

## 作者：xht (赞：5)

题目地址：[CF1119C Ramesses and Corner Inversion](https://www.luogu.org/problemnew/show/CF1119C)

将两个矩阵异或起来，为 $1$ 的位置就是需要修改的位置

注意到每一次操作都会导致两行和两列上有两个数被修改

那么如果有一行或一列上只有一个需要被修改的数，显然不可能

否则即可能

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 506;
int n, m, a[N][N], b[N][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &b[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] ^= b[i][j];
    for (int i = 1; i <= n; i++) {
        int o = 0;
        for (int j = 1; j <= m; j++)
            o ^= a[i][j];
        if (o) {
            puts("No");
            return 0;
        }
    }
    for (int j = 1; j <= m; j++) {
        int o = 0;
        for (int i = 1; i <= n; i++)
            o ^= a[i][j];
        if (o) {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}
```

---

## 作者：tth37 (赞：1)

分析性质：每次变换只能取矩形的四个顶点进行取反操作，那么可以证明，再A与B的异或矩阵上，每行、每列都只有偶数个1，则可以通过变换使异或矩阵变为0，即A与B相同。
因此，只需统计A矩阵与B矩阵的异或矩阵每行、每列上1的总数，全部为偶数输出“Yes”，否则输出“No”。

```cpp
#include<bits/stdc++.h>
using namespace std;

int M,N;
bool a[505][505];
bool b[505][505];
bool c[505][505];

int x[505],y[505];

int main(){
    scanf("%d%d",&M,&N);
    for(register int i=1;i<=M;++i){
        for(register int j=1;j<=N;++j){
            cin>>a[i][j];
        }
    }
    for(register int i=1;i<=M;++i){
        for(register int j=1;j<=N;++j){
            cin>>b[i][j];
        }
    }
    for(register int i=1;i<=M;++i){
        for(register int j=1;j<=N;++j){
            c[i][j]=a[i][j]^b[i][j];
            x[i]+=c[i][j];
            y[j]+=c[i][j];
        }
    }
    bool flag=true;
    for(register int i=1;i<=M;++i)
        if(x[i]&1) flag=false;
    for(register int i=1;i<=N;++i)
        if(y[i]&1) flag=false;
    if(flag)
        puts("Yes");
    else
        puts("No");
    return 0;
}


```

---

## 作者：KagurazakaKano (赞：1)

### 题意描述

你有两个 $n \times m$ 的 $01$ 矩阵，请问第一个矩阵是否可以通过变换来得到第二个矩阵。

变换的定义：

> 选取一个 $a \times b$ 的原矩阵的子矩阵，然后将这个子矩阵的 左上角、右上角、左下角、右下角进行异或操作。

### 思路

容易发现，所有的任意操作都可以拆分为对于大小为 $2 \times 2$ 的矩阵进行多次操作。

因此具体操作只要对 $n \times m$ 的矩阵扫一遍，如果发现有元素不相同就对这个 $2 \times 2$ 的子矩阵进行操作，否则继续扫，看最后矩阵是否相等。注意边界条件。

时间复杂度：$\Theta(n^2)$。

### Code
```cpp
#include <cstdio>
#define rep(i, a, b) for(int i = a; i <= b; ++i)

int a[505][505], b[505][505];

int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	rep(i, 1, m) rep(j, 1, n) scanf("%d", &a[i][j]);
	rep(i, 1, m) rep(j, 1, n) scanf("%d", &b[i][j]);
	rep(i, 1, m - 1) rep(j, 1, n - 1) if(a[i][j] != b[i][j]) {
		a[i][j] = (!a[i][j]);
		a[i + 1][j] = (!a[i + 1][j]);
		a[i + 1][j + 1] = (!a[i + 1][j + 1]);
		a[i][j + 1] = (!a[i][j + 1]);
	}
	rep(i, 1, m) rep(j, 1, n) if(a[i][j] != b[i][j]) return puts("No"), 0;  //这里其实可以简化复杂度。
	return puts("Yes"), 0;
}
```

---

## 作者：Sun_wtup (赞：0)

# Ramesses and Corner Inversion 题解
[题目传送](https://www.luogu.com.cn/problem/CF1119C)
## 题意
给出两个只由 $0$ 和 $1$ 构成的矩阵，可以选择第一个矩阵中两行两列以上的一个子矩阵，给这个矩阵的四个角反转（$0$ 变成 $1$，$1$ 变成 $0$）。如果可以通过这种操作将第一个矩阵变成第二个矩阵，就输出 Yes，否则输出 No。
## 分析与思路
思考一下，如果两个矩阵中相对应的每行中不同的元素数量是奇数，那么我们在处理时只能让一行中的偶数个反转，所以就不可能让两个矩阵完全相等。所以只有不同的元素是偶数是，才能成功。类似的，我们还要考虑列，不相同的数量是偶数是就行，是奇数时就不行。
## 实现
非常简单，依次枚举两个矩阵的行和列，进行比较，然后判断就行了。
## Code
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<'='<<x<<std::endl
int a[505][505];
int b[505][505];
bool flag;
int main()
{
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){//比较行
        int cnt=0;
        for(int j=1;j<=m;j++){
            cin>>b[i][j];
            if(a[i][j]!=b[i][j])cnt++;
        }
        if(cnt%2==1)flag=1;
    }
    for(int i=1;i<=m;i++){//比较列
        int cnt=0;
        for(int j=1;j<=n;j++){
            if(b[j][i]!=a[j][i])cnt++;
        }
        if(cnt%2==1)flag=1;
    }
    if(flag)cout<<"No\n";
    else cout<<"Yes\n";
    return 0;
}
```
本蒟蒻水平有限，如有不周之处，希望能原谅。

---

## 作者：Silence_World (赞：0)

# 思路

很显然的，两个矩阵异或，便是要改变的值，我们观察什么时候才能改变，很明显的，改变一个矩阵的四个角也就是行改变两个，列改变两个，也就是当每行每列需要改变偶数个值，每次改变两个，在最后操作时一定能操作完，如果有一个奇数输出 ```no```
即可。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1005][1005];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int t;
			cin>>t;
			a[i][j]^=t;
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum+=a[i][j];
		}
		if(sum%2==1){
			cout<<"No";
			return 0;
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			sum+=a[i][j];
		}
		if(sum%2==1){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}
```


---

## 作者：MILLOPE (赞：0)

## 题目
[题目传送门](https://www.luogu.org/problemnew/show/CF1119C)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190708193132597.png)

## 题解
- 只有当$A_{i,j} \ \ \ \ xor \ \ \ B_{i,j} =1$时才需要变化矩阵
- 如果每一行或每一列的异或和为奇数显然不可行
- 判断一下即可

## $code$
```cpp
#include <bits/stdc++.h> 
using namespace std; 
#define maxn 505

template <typename T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

int n, m; 
int nx[maxn], ny[maxn]; 
int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn]; 

int main() {
	read(n), read(m); 
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) 
			read(a[i][j]); 
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) 
			read(b[i][j]); 

	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= m; ++j) 
			c[i][j] = a[i][j] ^ b[i][j]; 

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			nx[i] += c[i][j]; 
			ny[j] += c[i][j]; 
		}
	}
	for (int i = 1; i <= n; ++i) 
		if (nx[i] & 1) { puts("NO"); return 0; }
	for (int i = 1; i <= m; ++i) 
		if (ny[i] & 1) { puts("NO"); return 0; }
	puts("YES"); 
	return 0; 
}

```

---

## 作者：hpbl (赞：0)

看了现在的题解好像都是一种做法……可能是我的做法有点清奇吧

对于这种变换问题，都是变换前后有什么东西是不变的，例如上场Global Round的E就是数列的差分组合固定，而这次就是变换前后每行每列的异或不变。

因为每行每列都恰好有偶数个数被翻转，因此1的个数奇偶性不变。

所以只要判断A和B每行每列的异或是不是都一样就行了。

COde:
```cpp
#include<cstdio>
using namespace std;
int n,m,x[2][2][501];
int main()
{
    scanf("%d %d",&n,&m);
    for(int k=0,t;k<2;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                scanf("%d",&t);
                x[k][0][i]^=t;
                x[k][1][j]^=t;
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(x[0][0][i]!=x[1][0][i])
        {
            puts("No");
            return 0;
        }
    }
    for(int j=1;j<=m;j++)
    {
        if(x[0][1][j]!=x[1][1][j])
        {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
}
```


---

## 作者：Zechariah (赞：0)

emmm比赛的时候推了一个结论：考虑A和B的异或矩阵，对于每一行和每一列，如果单行或者单列的1的个数都是偶数，那么存在一个从A到B的变换，否则无法从A变换到B
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
typedef unsigned int uint;
const int N = 1e3 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int a[N][N], b[N][N];

int main(void) {
    rg int n = fast_IO::read(), m = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)
        for (rg int j = 1; j <= m; ++j)
            a[i][j] = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)
        for (rg int j = 1; j <= m; ++j)
            b[i][j] = fast_IO::read() ^ a[i][j];
    for (rg int i = 1; i <= n; ++i) {
        rg int sum = 0;
        for (rg int j = 1; j <= m; ++j)
            sum ^= b[i][j];
        if (sum) { puts("No"); return 0; }
    }
    for (rg int i = 1; i <= m; ++i) {
        rg int sum = 0;
        for (rg int j = 1; j <= n; ++j)
            sum ^= b[j][i];
        if (sum) { puts("No"); return 0; }
    }
    puts("Yes");
    return 0;
}
```


---

