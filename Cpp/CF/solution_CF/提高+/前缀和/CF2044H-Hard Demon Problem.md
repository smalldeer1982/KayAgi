# Hard Demon Problem

## 题目描述

Swing 正在筹备他的煎饼工厂！一个优秀的煎饼工厂需要具备出色的压平能力，所以 Swing 决定使用二维矩阵来测试他的新设备。

给你一个大小为 $ n \times n $ 的矩阵 $ M $，其中每个元素都是正整数。Swing 有 $ q $ 个查询需要回答。

对于每个查询，Swing 会给出四个整数 $ x_1 $、$ y_1 $、$ x_2 $ 和 $ y_2 $，以此定义一个子矩阵，该子矩阵的左上角为 $(x_1, y_1)$，右下角为 $(x_2, y_2)$。他希望你将这个子矩阵展平为一个一维数组 $ A $。具体的展平顺序是：从 $ M_{(x1,y1)} $ 开始，按行从左到右依次加入子矩阵中的元素，直到 $ M_{(x2, y2)} $ 结束。

下图通过红色虚线展示了子矩阵的边界，橙色箭头指示了元素在进入数组 $ A $ 时的顺序，图下方展示了最终的数组 $ A $。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2044H/75bdaf28c8054bf099c5d719d2a33cac51011434.png)

展平后，Swing 想知道 $\sum_{i=1}^{|A|} A_i \cdot i$ 的值，即数组中每个元素 $ A_i $ 乘以其下标 $ i $ 的总和。

## 说明/提示

在第一个测试用例的第二个查询中，数组 $ A = [9, 5, 5, 2] $。因此，结果为 $ 1 \cdot 9 + 2 \cdot 5 + 3 \cdot 5 + 4 \cdot 2 = 42 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
4 3
1 5 2 4
4 9 5 3
4 5 2 3
1 5 5 2
1 1 4 4
2 2 3 3
1 2 4 3
3 3
1 2 3
4 5 6
7 8 9
1 1 1 3
1 3 3 3
2 2 2 2```

### 输出

```
500 42 168 
14 42 5```

# 题解

## 作者：SUNCHAOYI (赞：7)

将行和列分开考虑。

在每组询问 $(x_1,y_1,x_2,y_2)$ 中：

- 对于每一行，相邻的两个数的下标差为 $1$。
  
- 对于每一列，相邻的两个数的下标差为 $y_2 - y_1 + 1$。

不难想到对行和列分别做 $i \times a_{i,j}$ 和 $j \times a_{i,j}$ 的前缀和处理。由于列的下标之差不为 $1$，所以需要先对其做扩大倍数的处理后再将其相加。设最终要求的 $\sum i a_i$ 的 $i$ 为系数，那么对于一组询问，可以得到以下**系数**矩阵：

$$
\begin{bmatrix}
y_1 + x_1(y_2 - y_1 + 1) & y_1 + 1 + x_1(y_2 - y_1 + 1) & \cdots & y_2 + x_1(y_2 - y_1 + 1)\\
y_1 + (x_1 + 1)(y_2 - y_1 + 1) & y_1 + 1 + (x_1 + 1)(y_2 - y_1 + 1) & \cdots & y_2 + (x_1 + 1)(y_2 - y1 + 1)\\
\vdots & \vdots & \vdots & \vdots\\
y_1 + x_2(y_2 - y_1 + 1) & y_1 + 1 + x_2(y_2 - y_1 + 1) & \cdots & y_2 + x_2(y_2 - y_1 + 1)
\end{bmatrix}
$$

然而正确的系数矩阵应为：

$$
\begin{bmatrix}
1 & 2 & \cdots & y_2 - y_1 + 1\\
y_2 - y_1 + 2 & y_2 - y_1 + 3 & \cdots & 2(y_2 - y_1 + 1)\\
\vdots & \vdots & \vdots & \vdots\\
(x_2 - x_1)(y_2 - y_1 + 1) + 1 & (x_2 - x_1)(y_2 - y_1 + 1) + 2 & \cdots & (x_2 - x_1 + 1)(y_2 - y_1 + 1)
\end{bmatrix}
$$

将矩阵中的每一个数字都减去 $x_1(y_2 - y_1 + 1) + y_1 - 1$ 次即可，也就是再维护一个普通的二维前缀和后处理。总时间复杂度为 $O(t(n^2 + q))$，代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e3 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,q; 
ll sum[MAX][MAX],sumx[MAX][MAX],sumy[MAX][MAX];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();q = read ();
		for (int i = 1;i <= n;++i)
		{
			for (int j = 1;j <= n;++j)
			{
				int x = read ();
				sum[i][j] = x + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
				sumx[i][j] = i * x + sumx[i - 1][j] + sumx[i][j - 1] - sumx[i - 1][j - 1];
				sumy[i][j] = j * x + sumy[i - 1][j] + sumy[i][j - 1] - sumy[i - 1][j - 1];;
			}
		} 
		while (q--)
		{
			int sx = read (),sy = read (),fx = read (),fy = read ();
			ll s = sum[fx][fy] - sum[sx - 1][fy] - sum[fx][sy - 1] + sum[sx - 1][sy - 1];
			ll sum_x = sumx[fx][fy] - sumx[sx - 1][fy] - sumx[fx][sy - 1] + sumx[sx - 1][sy - 1];
			ll sum_y = sumy[fx][fy] - sumy[sx - 1][fy] - sumy[fx][sy - 1] + sumy[sx - 1][sy - 1];
			//同一列的公差为 fy - sy + 1
			printf ("%lld ",sum_x * (fy - sy + 1) + sum_y - s * (1ll * sx * (fy - sy + 1) + sy - 1));
		}	
		puts ("");
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：LostKeyToReach (赞：4)

这道题有 $\text{*2100}$？

题目中的「展开」启示我们根据行列标号表示 $A_i$ 和 $i$，有式子：

$$
\begin{aligned}
\sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}M_{i, j} \times [(i - x_1)(y_2-y_1+1)+(j-y_1+1)] &= \sum_{i=x_1}^{x_2}\sum_{j=y_1}^{y_2}M_{i, j} \times [i(y_2-y_1+1)-x_1(y_2-y_1+1)-(y_1-1)+j] \\
&= [-x_1(y_2-y_1+1)-y_1+1] \times \sum_{i = x_1}^{x_2}\sum_{j = y_1}^{y_2}M_{i, j} + (y_2-y_1+1)\sum_{i = x_1}^{x_2}\sum_{j = y_1}^{y_2}iM_{i, j} + \sum_{i = x_1}^{x_2}\sum_{j = y_1}^{y_2}jM_{i, j}.
\end{aligned}
$$

那么我们考虑分别开 $3$ 个前缀和数组维护 $M_{i, j}, iM_{i, j}, jM_{i, j}$ 的和即可，可以轻松做到 $O(n^2 + q)$ 的时间复杂度。

代码如下：

```cpp
#include <bits/stdc++.h>

#define int long long
#define all(a) a.begin(), a.end()

constexpr int N = 1e5 + 6;

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> p1(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> p2(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> p3(n + 1, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> a[i][j];
            p1[i][j] = a[i][j];
            p2[i][j] = a[i][j] * i;
            p3[i][j] = a[i][j] * j;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            p1[i][j] += p1[i - 1][j];
            p2[i][j] += p2[i - 1][j];
            p3[i][j] += p3[i - 1][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            p1[i][j] += p1[i][j - 1];
            p2[i][j] += p2[i][j - 1];
            p3[i][j] += p3[i][j - 1];
        }
    }
    while (q--) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        int ans = (-x1 * (y2 - y1 + 1) - y1 + 1) * (p1[x2][y2] + p1[x1 - 1][y1 - 1] - p1[x1 - 1][y2] - p1[x2][y1 - 1]);
        ans += (y2 - y1 + 1) * (p2[x2][y2] + p2[x1 - 1][y1 - 1] - p2[x1 - 1][y2] - p2[x2][y1 - 1]);
        ans += p3[x2][y2] + p3[x1 - 1][y1 - 1] - p3[x1 - 1][y2] - p3[x2][y1 - 1];
        std::cout << ans << " ";
    }
    std::cout << "\n";
}

int32_t main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0), std::cout.tie(0);

  int t;
  std::cin >> t;
  // t = 1;

  while (t--) {
    solve();
  }

  return 0;
}
```

---

## 作者：SJZ2010 (赞：1)

不妨把 $\times i$ 的式子写出来推，以下记 $x1, y1, x2, y2$ 为 $x, y, s, t$，那题目里 $A_i \times i$ 就是（$i, j$ 是矩阵里的下标）：

$$[(i - x)(t - y + 1) + j - y + 1]a_{i, j}$$

那么答案式子就是

$$\sum_{i = x}^s \sum_{j = y}^t [(i - x)(t - y + 1) + j - y + 1]a_{i, j}$$

乘法分配律一下得到

$$\sum_{i = x}^s \sum_{j = y}^t (t - y + 1)ia_{i, j} + ja_{i, j} - [x(t - y + 1) + y - 1]a_{i, j}$$

显然用二维前缀和维护。[AC](https://codeforces.com/contest/2044/submission/303634699)。

---

## 作者：WuMin4 (赞：0)

## [CF2044H Hard Demon Problem](https://codeforces.com/contest/2044/problem/H)

## 题意

给出 $n\times n$ 的二维数组 $a$，有 $q$ 个询问，每次询问给出 $x_1,y_1,x_2,y_2$，求以下函数的值：

```txt
cnt=1,ans=0;
for i=x1 to x2:
  for j=y1 to y2:
    ans=ans+a[i][j]*cnt;
    cnt=cnt+1;
return ans;
```

## 思路

很考验对前缀和理解的题。

假如我们要算以下二维数组 $a_{i,j} \pod{1\le i\le n,1\le j\le m}$ 的函数值：

```txt
1 2 3
4 5 6
7 8 9
```
答案即为：

```txt
1*1 + 2*2 + 3*3 +
4*4 + 5*5 + 6*6 +
7*7 + 8*8 + 9*9
```

可以发现每行中都包含了类似 $\sum_{j=1}^m a_{i,j}\times j$ 的算式，把它提出来，原式变为：

```txt
1*1 + 2*2 + 3*3 +
4*1 + 5*2 + 6*3 +
7*1 + 8*2 + 9*3 +

1*0 + 2*0 + 3*0 +
4*3 + 5*3 + 6*3 +
7*6 + 8*6 + 9*6
```

可以发现剩下的算式每列里也包含了类似 $\sum_{i=1}^n a_{i,j}\times m\times (i-1)$ 的算式。

于是可以通过预处理出这两个东西的二维前缀和快速计算答案，但是实际计算时的前缀和数组的 $i$ 与 $j$ 可能并不是从 $1$ 开始，这时便可以再维护一个正常的二维前缀和，计算时再将这两个前缀和数组整体减去一个值即可。


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define g(x,y,xx,yy,z) (z[xx][yy]-z[xx][y-1]-z[x-1][yy]+z[x-1][y-1])
int T,n,q,t[2005][2005],a[2005][2005],b[2005][2005],c[2005][2005];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>t[i][j];
				a[i][j]=a[i][j-1]+a[i-1][j]-a[i-1][j-1]+t[i][j]*j;
				b[i][j]=b[i][j-1]+b[i-1][j]-b[i-1][j-1]+t[i][j]*i;
				c[i][j]=c[i][j-1]+c[i-1][j]-c[i-1][j-1]+t[i][j];
			}
		}
		while(q--){
			int x,y,xx,yy;
			cin>>x>>y>>xx>>yy;
			cout<<(g(x,y,xx,yy,a)-g(x,y,xx,yy,c)*(y-1))+
			(g(x,y,xx,yy,b)-g(x,y,xx,yy,c)*x)*(yy-y+1)<<" ";
		}
		cout<<endl;
	}
	return 0; 
}
```

---

