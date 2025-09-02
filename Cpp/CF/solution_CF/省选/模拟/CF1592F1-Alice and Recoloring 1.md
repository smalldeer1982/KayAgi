# Alice and Recoloring 1

## 题目描述

给定一个 $n$ 行 $m$ 列的目标矩阵，矩阵元素只有 W 或 B ，并且你有一个初始矩阵，元素全为 W 。

现在你可以矩阵实施以下操作：

1. 使用一块钱，选定一个包含 $(1,1)$ 的子矩阵，把矩阵中的元素全部反转（ W 变 B ， B 变 W ）。
2. 使用两块钱，选定一个包含 $(n,1)$ 的子矩阵，把矩阵中的元素全部反转。
3. 使用四块钱，选定一个包含 $(1,m)$ 的子矩阵，把矩阵中的元素全部反转。
4. 使用三块钱，选定一个包含 $(n,m)$ 的子矩阵，把矩阵中的元素全部反转。

现在需要你求出把初始矩阵变为目标矩阵最少需要几块钱。

## 样例 #1

### 输入

```
3 3
WWW
WBB
WBB```

### 输出

```
3```

## 样例 #2

### 输入

```
10 15
WWWBBBWBBBBBWWW
BBBBWWWBBWWWBBB
BBBWWBWBBBWWWBB
BBWBWBBWWWBBWBW
BBBBWWWBBBWWWBB
BWBBWWBBBBBBWWW
WBWWBBBBWWBBBWW
WWBWWWWBBWWBWWW
BWBWWBWWWWWWBWB
BBBWBWBWBBBWWBW```

### 输出

```
74```

# 题解

## 作者：断清秋 (赞：16)

[题目传送门](https://www.luogu.com.cn/problem/CF1592F1)

超级妙妙题！

题意：

给定一个 $n \times m$ 的矩阵，初始时所有格子都是白色，可以进行以下四种操作：  

1、翻转一个以 $(1,1)$ 为左上角的任意子矩阵的所有颜色，代价为 $1$；

2、翻转一个以 $(n,1)$ 为左下角的任意子矩阵的所有颜色，代价为 $2$；

3、翻转一个以 $(1,m)$ 为右上角的任意子矩阵的所有颜色，代价为 $4$；

4、翻转一个以 $(n,m)$ 为右下角的任意子矩阵的所有颜色，代价为 $3$。

求将初始局面变为给定局面花费代价的最小值。

首先只有黑白两种颜色，所以将一个格子翻转偶数次，相当于没有翻转。

其次，将初始局面变为给定局面，等价于将给定局面变为初始局面。因此问题可以转化成给定一个局面，要将这个局面全部变为白色格子所花费的最小代价。

发现这四种操作好像比较对称，考虑进行一些转化。

对于操作 $2$，翻转一个以 $(n,1)$ 为左下角，$(x,y)$ 为右上角的矩阵，可以转化为使用两次操作 $1$，第一次翻转以 $(1,1)$ 为左上角，$(n,y)$ 为右下角的矩形，第二次翻转以 $(1,1)$ 为左上角，$(x-1,y)$ 为右下角的矩形。
    
显然这两种操作完全等价，花费的代价也相同。因此，操作 $2$ 没有任何意义。

类似地，对于操作 $3$，翻转一个以 $(1,m)$ 为右上角，$(x,y)$ 为左下角的矩阵，可以转化为使用两次操作 $1$，第一次翻转以 $(1,1)$ 为左上角，$(x,m)$ 为右下角的矩形，第二次翻转以 $(1,1)$ 为左上角，$(x,y-1)$ 为右下角的矩形。

这两种操作也是完全等价的，但是两次操作 $1$ 只需要花费 $2$ 代价，因此操作 $3$ 也没有意义。

容易知道操作 $4$ 无法转化为使用不超过三次的操作 $1$，因此操作 $4$ 是有意义的。

于是证明了只有操作 $1$ 和操作 $4$ 有意义。下面考虑如何操作。

显然矩阵修改不好维护且十分麻烦，最好将其转化为单点修改。

可以对原矩阵 $c$ 进行一个巧妙的转化：令白色格子为 $0$，黑色格子为 $1$。设 $a_{i,j}$ 代表 $(c_{i,j}+c_{i+1,j}+c_{i,j+1}+c_{i+1,j+1}) \bmod 2$ 的结果。

容易知道，将原局面全部变成白色格子的充要条件为对于任意 $1 \le i,j \le n,a_{i,j}=0$。于是问题转化为将所有 $a_{i,j}$ 变为 $0$ 的最小方案。

考虑对于操作 $1$，翻转一个以 $(1,1)$ 为左上角，$(x,y)$ 为右下角的矩形等价于只翻转 $a_{x,y}$。

对于操作 $4$，翻转一个以 $(x,y)$ 为左下角，$(n,m)$ 为右下角的矩阵，等价于只翻转 $a_{x-1,y-1},a_{x-1,m},a_{n,y-1},a_{n,m}$。

这两个结论可以自行画图证明，这里略去。

这样操作 $1$ 就是翻转一个点，代价为 $1$，操作 $4$ 就是翻转四个点，代价为 $3$。

看起来操作 $4$ 好像更优。但是操作 $4$ 能用必须满足两个条件：1、$a_{x-1,y-1},a_{x-1,m},a_{n,y-1},a_{n,m}$ 均为 $1$（翻转 $a_{i,j}=0$ 的点会带来负收益）；2、只能进行一次（因为多次进行操作 $4$ 会不断翻转 $a_{n,m}$，实际上最多翻转 $3$ 个有效点）

所以最多进行一次操作 $4$，剩下的点都用操作 $1$ 完成。

于是判断一下能否进行操作 $4$ 并统计一下需要翻转的 $a_{i,j}$ 的个数即可。

时间复杂度 $O(nm)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned ll
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
int n,m,ans,a[505][505],b[505][505];
char c[505][505];
int main()
{
	n=read(),m=read();
	for(ri i=1;i<=n;i++)
		for(ri j=1;j<=m;j++)
		{
			cin>>c[i][j];
			if(c[i][j]=='W')
				b[i][j]=0;
			else
				b[i][j]=1;
		}
	for(ri i=1;i<=n;i++)
		for(ri j=1;j<=m;j++)
			a[i][j]=(b[i][j]+b[i][j+1]+b[i+1][j]+b[i+1][j+1])%2;
	for(ri i=1;i<=n;i++)
		for(ri j=1;j<=m;j++)
			if(a[i][j]==1)	
				ans++;
	if(a[n][m])
		for(ri i=1;i<=n;i++)
			for(ri j=1;j<=m;j++)
				if(a[i-1][j-1]&&a[i-1][m]&&a[n][j-1])	
				{
					cout<<ans-1<<"\n";
					back 0;
				}
	cout<<ans<<"\n";
	back 0;
}
```

---

## 作者：fishing_cat (赞：8)

[传送门](https://codeforces.com/problemset/problem/1592/F1)

### 题意

有四种操作，要求将全白的一个矩形通过操作转化为给定的矩形。最小化花费。

### 做法

为了方便操作，考虑用类似前缀和的思想，对于给定矩阵 $a$，构造一个新矩阵 $c$，满足 $c_{i,j} = (a_{i,j} + a_{i+1, j} + a_{i,j+1} + a_{i+1,j+1}) \bmod 2$，也可以直接看作是这四个格的异或和。自然，多出来的 $a_{x,m}$ 这列和 $a_{n,x}$ 这行，默认为 $0$。

逆向操作，看成将给定矩阵转化成初始矩阵的最小花费。将 $a$ 矩阵转化为初始矩阵即将 $c$ 矩阵准化为全白的一个矩阵。

分别观察四种操作，对于操作一，在构造后的 $c$ 中，就是只将 $c_{i,j}$ 反转。     
对于操作二，发现可以用两次操作一代替，花费一样。   
对于操作三，发现也可以用两次操作一代替，并且两次操作一花费更小。  
对于操作四，就是将 $c_{n,m}$，$c_{i,m}$，$c_{n,j}$ 和 $c_{i,j}$ 都反转。并且因为一次操作四花费为三，所以只有在这四个格都为黑时操作四是比多次操作一更优的。不然，仍可以用多次操作一代替。

即，只需要考虑操作一和操作四，并且操作四只有在 $c_{n,m}$ 为黑是才会使用一次，就可以保证是最优的。

具体实现，对于构造出的 $c$，记录出现的黑的个数为 $res$，如果 $c_{n,m}$ 是黑的，可以使用一次操作四，效果就是将 $res$ 减去一。最后得到的 $res$ 就是最优花费。

时间复杂度 $O(nm)$。

### code

[link](https://codeforces.com/contest/1592/submission/288659051)

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define il inline
using namespace std;
/*快读省了*/
ll n, m, a[510][510], c[510][510], ans;
char s;

int main() {
	read(n); read(m);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) {
			cin >> s;
			if (s == 'B') 
				a[i][j] = 1;
		}

	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j ++) {
			c[i][j] = (a[i][j] + a[i+1][j] + a[i][j+1] + a[i+1][j+1]) % 2;
			if (c[i][j] == 1) ans++;
		}

	if (c[n][m] == 1) 
	 	for (int i = 1; i <= n-1; i++) 
			for (int j = 1; j <= m-1; j++) 
				if (c[i][j] == 1 && c[n][j] == 1 && c[i][m] == 1) {
					ans -= 1;
					cout << ans << "\n";
					exit(0);
				} 	
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：Alex_Wei (赞：8)

> ### *1592F1. [Alice and Recoloring 1](https://www.luogu.com.cn/problem/CF1592F1) 2600
> 
> [F2 题解](https://www.luogu.com.cn/blog/AlexWei/solution-cf1592f2)。

---

神仙思路题。首先不难发现操作 $2,3$ 在搞笑，下记操作 $2$ 为原来的操作 $4$，记 $a_{i,j}=[c_{i,j}=\texttt{B}]$。

一次翻转一个子矩形较难处理，考虑对矩形进行一些变换后简化操作，即**使一次操作改变的格子尽量少**：我们设 $p_{i,j}$ 表示 $a_{i,j}\oplus a_{i,j+1}\oplus a_{i+1,j}\oplus a_{i+1,j+1}$。将 $a$ 变为全 $0$ **等价于把 $p$ 变为全 $0$**。这一步神仙转换使得对于操作 $1$，我们相当于翻转 $p_{x,y}$；对于操作 $2$，相当于翻转 $p_{x-1,y-1},p_{x-1,m},p_{n,y-1}$ 和 $p_{n,m}$（$x>1,y>1$，因为若 $x$ 或 $y=1$ 则可以用两次操作 $1$ 代替）。

不难发现超过一次进行操作 $2$ 是不优的，因为这只改变了 $6$ 个格子的状态（$p_{n,m}$ 被改变了两次），代价不优于使用六次操作 $1$。所以对 $p$ 求和，若存在 $x<n,y<m$ 使得 $p_{x,y}=p_{x,m}=p_{n,y}=p_{n,m}=1$ 则将答案减掉 $1$。时间复杂度 $\mathcal{O}(nm)$。

```cpp
const int N = 500 + 5;
int n, m, ans, a[N][N], p[N][N];
char mp[N][N];

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> mp[i][j], p[i][j] = mp[i][j] == 'B';
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			ans += a[i][j] = 
				(p[i][j] ^ p[i][j + 1] ^ p[i + 1][j] ^ p[i + 1][j + 1]);
	for(int i = 1, ok = 0; i < n && !ok; i++)
		for(int j = 1; j < m && !ok; j++)
			if(a[i][j] && a[i][m] && a[n][j] && a[n][m])
				ok = 1, ans--;
	cout << ans << endl;
    return 0;
}
```

---

## 作者：灵茶山艾府 (赞：6)

我们需要把输入的矩阵变成全 $\texttt{W}$ 矩阵。

### 提示 1

由于操作 $2$ 和操作 $3$ 都等价于 $2$ 次操作 $1$，我们可以只关注操作 $1$ 和操作 $4$。

### 提示 2

由于操作 $1$ 最便宜，下面的分析将围绕操作 $1$ 展开。

想一想，如果只有操作 $1$，最少要操作多少次？

从矩形右下角开始思考。

如果右下角是 $\texttt{B}$，那么必须操作，否则无需操作。

对于不是右下角的位置，我们需要计算这个位置被之前的操作翻转了多少次：

- 如果翻转了偶数次，就看当前位置是否为 $\texttt{B}$，是就翻转。
- 如果翻转了奇数次，就看当前位置是否为 $\texttt{W}$，是就翻转（因为 $\texttt{W}$ 翻转奇数次变成 $\texttt{B}$，需要继续翻转）。

翻转次数可以通过**二维后缀和**计算。

### 提示 3

考虑操作 $4$ 对操作 $1$ 的影响：

- 执行 $1$ 次操作 $4$，相当于改变了 $4$ 个位置 $(i,j), (i,m), (n,j), (n,m)$ 的翻转次数的奇偶性。
- 执行 $2$ 次操作 $4$，由于 $(n,m)$ 被翻转两次，相当于没有翻转，所以只改变了 $4+4-2=6$ 个位置的翻转次数的奇偶性。这意味着 $2$ 次操作 $4$ 等价于 $6$ 次操作 $1$。
- 执行 $3$ 次操作 $4$，我们可以把其中的 $2$ 次操作 $4$ 替换成 $6$ 次操作 $1$。
- 对于更多次的操作 $4$ 也同理。替换后，至多剩下 $1$ 次操作 $4$。

所以只需考虑操作 $4$ 能否执行 $1$ 次，也就是能否代替 $4$ 次操作 $1$，从而节省 $1$ 块钱。

如果存在 $(i,j), (i,m), (n,j), (n,m)$ 这 $4$ 个位置都执行了操作 $1$，那么可以用 $1$ 次操作 $4$ 代替，这会让总花费减少 $1$。

也就是说，答案等于操作 $1$ 的执行次数，减去「是否存在上述情况」，存在就把答案减少 $1$。

注意这 $4$ 个位置不能重叠，也就是 $i < n$ 且 $j < m$。

下面代码下标从 $0$ 开始。

代码实现时，可以把 $(i,j)$ 处的字符改成 `\0`，以表示该位置执行了操作 $1$。

AC 代码（Golang）：

```go
package main
import ("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m, ans int
	Fscan(in, &n, &m)
	a := make([][]byte, n)
	for i := range a {
		Fscan(in, &a[i])
	}

	suf := make([][]byte, n+1)
	for i := range suf {
		suf[i] = make([]byte, m+1)
	}
	for i := n - 1; i >= 0; i-- {
		for j := m - 1; j >= 0; j-- {
			// 二维后缀异或和
			suf[i][j] = suf[i][j+1] ^ suf[i+1][j] ^ suf[i+1][j+1]
			if suf[i][j] == a[i][j]&1 { // 需要翻转
				ans++
				a[i][j] = 0 // 表示 (i,j) 处执行了操作 1
				suf[i][j] ^= 1
			}
		}
	}

	if a[n-1][m-1] == 0 {
		for _, row := range a[:n-1] {
			for j, x := range row[:m-1] {
				if x == 0 && row[m-1] == 0 && a[n-1][j] == 0 {
					Print(ans - 1) // 用 1 次操作 4 代替 4 次操作 1
					return
				}
			}
		}
	}
	Print(ans)
}
```

**时间复杂度**：$\mathcal{O}(nm)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：dead_X (赞：5)

## 思路
首先，略微观察之后可以得到一个结论：翻转包含 $(n,1),(1,m)$ 的矩形必定不优，因为它们可以用 $2$ 个包含 $(1,1)$ 的矩形构造出来。

于是题目变成了只能翻转包含 $(1,1)$ 或 $(n,m)$ 的矩形。

将矩形做一个二阶差分，我们发现翻转包含 $(n,m)$ 的矩形相当于在差分矩阵上修改一个点（注意修改的点一定不在第一行第一列），而在这些位置翻转包含 $(1,1)$ 的矩形会修改 $(1,1),(x,1),(1,y),(x,y)$。

在反转完 $x,y>1$ 的位置后，我们会接着回去翻转 $x=1$ 或 $y=1$ 的矩形，就完成了整个过程。

也就是说，我们记 $f_i$ 为第 $i$ 行是否翻转，$g_j$ 为第 $j$ 行是否翻转，$h$ 为 $(1,1)$ 是否需要最后翻转。一次 $(1,1)$ 的操作等价于翻转 $f_i,g_j,h$，消耗 $1$；而一次 $(n,m)$ 的操作什么都不翻转，消耗 $3$。

也就是说，如果我们翻转 $(n,m)$ 的矩形，可能会比翻转 $(1,1)$ 的矩形多花 $+3,+1,+1$ 的费用。

不难发现 $+1$ 和 $+3$ 的费用最多只能创造一次 $-1$，因此我们一定只执行 $-1$。

而 $-1$ 只会出现最多一次，枚举每个位置即可。
## 代码
```cpp
char s[503][503];
bool a[503][503];
bool b[503][503];
bool f[503],g[503];
signed main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) scanf("%s",s[i]+1);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) a[i][j]=(s[i][j]=='B');
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j) b[i][j]=(a[i][j]!=a[i][j-1]);
	for(int i=n; i>=1; --i)
		for(int j=1; j<=m; ++j) b[i][j]=(b[i][j]!=b[i-1][j]); 
	// for(int i=1; i<=n; ++i,puts(""))
		// for(int j=1; j<=m; ++j) printf("%d",b[i][j]);
	int c=b[1][1];
	int ans=0;
	for(int i=2; i<=n; ++i)
		for(int j=2; j<=m; ++j)
			ans+=b[i][j],f[i]^=b[i][j],g[j]^=b[i][j],c^=b[i][j];
	for(int i=2; i<=n; ++i) f[i]^=b[i][1];
	for(int j=2; j<=m; ++j) g[j]^=b[1][j];
	for(int i=2; i<=n; ++i)
		ans+=f[i],c^=f[i];
	for(int j=2; j<=m; ++j)
		ans+=g[j],c^=g[j];
	ans+=c;
	int flg=0;
	for(int i=2; i<=n; ++i)
		for(int j=2; j<=m; ++j)
			if(b[i][j]&&f[i]&&g[j]&&c)
				flg=1;
	printf("%d\n",ans-flg);
	return 0;
}
```

---

## 作者：Terry2022 (赞：4)



一个不同的理解方式，个人认为比较自然

**思路**：

首先在只使用 $1$ 操作的情况下就可以将 $2$ 操作和 $3$ 操作做到代价 $2$，所以 $2,3$ 操作都是无意义的；$4$ 操作有意义但是 $4$ 操作只能做一次，对于大于 $1$ 次的情况可以简单分类讨论：

如果两次 $4$ 操作有包含关系：

![operation4.1](https://cdn.luogu.com.cn/upload/image_hosting/gku7l2k6.png)

两次 $4$ 操作： $MHDK$ 和 $LIDJ$，代价为 $6$。

六次 $1$ 操作：$ACIG$，$ANJB$，$AEKB$，$ACHF$，$ANLG$，$AEMF$，代价为 $6$。

如果两次 $4$ 操作不互相包含：

![operation4.2](https://cdn.luogu.com.cn/upload/image_hosting/cur9qozc.png)

两次 $4$ 操作：$MHFJ$ 和 $LIDK$，代价为 $6$。

六次 $1$ 操作：$ACIG$，$ANJB$，$ACHF$，$AEKB$，$ANMF$，$AELG$，代价为 $6$。

所以超过 $2$ 次的 $4$ 操作一定可以规约为 $1$ 操作。

暴力枚举进行操作的 $4$ 操作区域，然后考虑如何计算 $1$ 操作需要的最小次数：

由于 $1$ 操作是会操作左上部分，所以从右下开始计算。

设 $a_{i,j}=[c_{i,j}=B]$， $v_{i,j}$ 表示最优策略中 $(i,j)$ 是否操作，$s_{i,j}$ 表示 $v_{i,j}$ 的二维后缀异或和，则有转移：

$v_{i,j}=a_{i,j}\oplus s_{i+1,j}\oplus s_{i,j+1}\oplus s_{i+1,j+1}$，$s_{i,j}=v_{i,j}\oplus s_{i+1,j}\oplus s_{i,j+1}\oplus s_{i+1,j+1}=a_{i,j}$，最小操作次数为 $\sum_{i=1}^{n}\sum_{j=1}^{m}v_{i,j}=\sum_{i=1}^{n}\sum_{j=1}^{m}(a_{i,j}\oplus a_{i+1,j}\oplus a_{i,j+1}\oplus a_{i+1,j+1})$，所以 $1$ 操作的最小操作次数即为该矩阵中大小为 $2\times 2$ 且异或和为 $1$ 的矩阵的数量，注意将 $i>n$ 或 $j>m$ 的 $a_{i,j}$ 视为 $0$。

对于一次 $4$ 操作，其会将右下角的一个矩阵反转，实际会导致的矩形数量的变化只有四个位置，如图：

![change](https://cdn.luogu.com.cn/upload/image_hosting/qpyc30f5.png)

黑色的大框为 $n\times m$ 的矩阵，红色部分为 $4$ 操作区域，绿色的 $4$ 个 $2\times 2$ 的矩阵为值会改变的部分，注意由于值是异或，所以如果反转的数量为偶数，值不会改变。

提前预处理出原来的 $1$ 操作最小数量，然后每次直接重新计算 $4$ 个绿矩阵值即可，时间复杂度 $O(nm)$。

**代码**：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
const int Q=505;
const int INF=(1<<30);
typedef long long ll;
#define rg register int
#define cint const register int
//char ibuf[1<<21],*IP1=ibuf,*IP2=ibuf;
//#define gc() (__builtin_expect(IP1==IP2,0)&&(IP2=(IP1=ibuf)+fread(ibuf,1,1<<21,stdin),__builtin_expect(IP1==IP2,0))?EOF:*IP1++)
#define gc() getchar()
inline bool ig(const char c){return c>=48&&c<=57;}
inline void read(rg&oi){char c;rg f=1,res=0;while(c=gc(),(!ig(c))&&c^'-');c^'-'?res=(c^48):f=-1;while(c=gc(),ig(c))res=res*10+(c^48);oi=f*res;}
inline void print(rg oi){char io[23];rg l=0;if(oi<0)putchar('-'),oi=~oi+1;do io[++l]=(oi%10+48);while(oi/=10);for(;l;--l)putchar(io[l]);}
inline void write(cint oi,const char c){print(oi);putchar(c);}char _ST_;
inline void Min(rg&x,cint y){(x>y)&&(x=y);}
int n,m,a[Q][Q];
inline int calc(cint x,cint y){return a[x][y]^a[x][y+1]^a[x+1][y]^a[x+1][y+1];}
char _ED_;int main(){
	fprintf(stderr,"memory:%llu MB\n",(&_ST_-&_ED_)>>20);
	read(n);read(m);for(rg i=1;i<=n;++i){
		char c;while(c=gc(),c^'W'&&c^'B');a[i][1]=(c=='B');
		for(rg j=2;j<=m;++j)c=gc(),a[i][j]=(c=='B');
	}
	rg sum=0;for(rg i=1;i<=n;++i)for(rg j=1;j<=m;++j)sum+=calc(i,j);
	rg res=sum;for(rg i=1;i<=n;++i){
		for(rg j=1;j<=m;++j){
			rg v=sum;if(i>1&&j>1)v-=calc(i-1,j-1),v+=calc(i-1,j-1)^1;
			if(j>1)v-=calc(n,j-1),v+=calc(n,j-1)^1;
			if(i>1)v-=calc(i-1,m),v+=calc(i-1,m)^1;
			v-=calc(n,m);v+=calc(n,m)^1;Min(res,v+3);
		}
	}
	write(res,'\n');
	return 0;
}
```



---

## 作者：STrAduts (赞：1)

不难发现对于目标矩阵的任意全是 $B$ 的子矩阵，若不包含 $4$ 个角，则都可以使用至多 $4$ 次操作 \#1 单独构造出来且不影响其他子矩阵（如果贴在边缘则仅需 $2$ 次）。

但这不好做啊，因为子矩阵可以相互用部分去组合。

然后发现 \#2、\#3 两种操作是废的，因为操作 \#2 可以用两个操作 \#1 完成，费用为 $2$；操作 \#3 也可以用两个操作 \#1 完成，费用为 $2$。

但这仍然不好做，并不能产生构成方案的动机。开始构思一些神妙做法了。

反直觉，从上面的思路往下走。我们考虑只使用 \#1，且令 `B` 为 $1$，`W` 为 $0$。

当一个位置 $(i, j)$ 需要使用 \#1 变为 $1$ 时，代表它现在的状态是 $0$。即存在本身是 $0$、处理 $(i, j + 1),(i + 1, j),(i + 1, j + 1)$ 时使用了偶数次 \#1 使得 $(i, j)$ 仍为 $0$ 两种情况。

同理考虑需要使用 \#1 变为 $0$ 的情况。

可以得出如果 $(i, j) \space \mathrm{xor} \space (i, j + 1) \space \mathrm{xor} \space (i + 1, j) \space \mathrm{xor} \space (i + 1, j + 1) = 1$，则需要执行 \#1；否则就不需要。如果记一个新的矩阵 $a(i, j) = $ 前面那一坨异或和，则 \#1 可以每次让一个位置翻转，多次使用使矩阵达到目的。

那么我们就可以只用 \#1 构造出一个合法方案，但应该是可以继续用 #4 进行优化的。

\#4 做了什么？将 $a(i - 1, j - 1), a(i - 1, m), a(n, j - 1), a(m, n)$ 同时一次性翻转。对于 $a(m, n)$，以后可能会重复受作用，所以直观上，#4 应该只用一次最赚。

```cpp
#include <cstdio>

int Abs (int x) { return x < 0 ? -x : x; }
int Max (int x, int y) { return x > y ? x : y; }
int Min (int x, int y) { return x < y ? x : y; }

int Read () {
    int x = 0, k = 1;
    char s = getchar ();
    while (s < '0' || s > '9') {
        if (s == '-')
            k = -1;
        s = getchar ();
    }
    while ('0' <= s && s <= '9') 
        x = (x << 3) + (x << 1) + (s ^ 48), s = getchar ();
    return x * k;
}

void Write (int x) {
    if (x < 0)
        putchar ('-'), x = -x;
    if (x > 9)
        Write (x / 10);
    putchar (x % 10 + '0');
}

void Print (int x, char s) { Write (x), putchar (s); }

const int Maxn = 5e2 + 5;

int a[Maxn][Maxn];
char s[Maxn][Maxn];

int main () {
    int n = Read (), m = Read ();
    for (int i = 1; i <= n; i++)
        scanf ("%s", s[i] + 1);
    int Res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            Res += (a[i][j] = ((s[i][j] == 'B') ^ (s[i][j + 1] == 'B') ^ (s[i + 1][j] == 'B') ^ (s[i + 1][j + 1] == 'B')));
    bool Flag = false;
    if (a[n][m]) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++)
                if (a[i - 1][m] && a[n][j - 1] && a[i - 1][j - 1]) {
                    Res--, Flag = true;
                    break;
                }
            if (Flag)
                break;
        }        
    }
    Print (Res, '\n');
    return 0;
}
```

---

## 作者：MiRaciss (赞：1)

## 题目链接
[Link.](https://codeforces.com/problemset/problem/1592/F1)

## 题解
神仙题啊神仙题。

首先，这道题目的操作是反转，而反转两次就等价于没反转。所以从初始状态转换到目标状态等价于从目标状态转换到初始状态。

为了方便，这里把 'W' 看成 $0$，把 'B' 看成 $1$，每次反转就是将矩形 $A$ 的每一个数**异或** $1$。所求就是把所有数变成 $0$。

可以发现，做一次操作 $2$ 或操作 $3$ 等价于做两次操作 $1$，以操作 $2$ 为例，如果我想反转矩形 $(1,i)$ 到 $(2,m)$，我可以先反转 $(1,1)$ 到 $(2,i-1)$，然后反转 $(1,1)$ 到 $(2,m)$。因为两次操作 $1$ 的代价不高于一次操作 $2$ 或 $3$，所以操作 $2$ 和 $3$ 是没有用的。

现在我们可以反转的矩形只有两种：
1. 以 $(1,1)$ 为左上角
2. 以 $(n,m)$ 为右下角

因为操作 $1$ 的代价最小，所以我们先只考虑操作 $1$：

对于一个点，我们怎么考虑它是否需要反转呢？

 如果它自己是 $1$，那么它是需要反转的，但是如果它左边、下边、左下的点有 $1$ 个或是 $3$ 个需要反转，那么它自己就不用反转了，因为其它三个点一次或三次的反转一定都包含了这个点，那么这个点自然就被反转了。否则这个点一定要消耗 $1$ 的代价反转。

同理也可以推出这个点是 0 的情况下是否需要反转。

总结一下，对于一个点，如果它与它右边、下边、右下的点**异或**的值为 $1$，那么这个点需要反转，为 $0$ 就不需要反转。

定义一个新的矩形 $B$，$B_{,j}=A_{i,j} \oplus A_{i+1,j} \oplus A_{i,j+1} \oplus  A_{i+1,j+1}$ ，操作 $1$ 就相当于反转 $B_{i,j}$

那么答案就是 $$ans=\sum_{i=1}^{n}\sum_{j=1}^{m} B_{i,j}$$

但是因为还有一个操作 $4$，考虑操作 $4$ 的作用。可以发现操作 $4$ 就是将 $B_{i,j},B_{i,m},B_{n,j},B_{n,m}$ 同时反转。

看起来操作 $4$ 比操作 $1$ 更优，但是因为不停的反转 $B_{n,m}$，所以只有进行第一次操作 $4$ 的时候才会取得更小的代价，特判即可。

### code
```cpp
int n,m;
char s[505][505];
int a[505][505];
int ans=0;

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>(s[i]+1);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=s[i][j]!='W';
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]^=a[i+1][j]^a[i][j+1]^a[i+1][j+1];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ans+=a[i][j];
	for(int i=1;i<n;i++) for(int j=1;j<m;j++) if(a[i][j]&&a[n][j]&&a[i][m]&&a[n][m]){ ans--;goto Thanks; }
	Thanks:;
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：activeO (赞：1)

## 题目大意

[题面](https://www.luogu.com.cn/problem/CF1592F1) 说得比较清楚，这里就不说了。

## 思路

首先需要发现操作 2 和 操作 3 是没用的，因为他们能用两个操作 1 来完成，那么进行两次操作 1 显然是更优的。（这一点手玩一下就可以发现）

然后，我们设 $ f_{i,j} = a_{i,j} \oplus a_{i+1,j} \oplus a_{i,j+1} \oplus a_{i+1,j+1} $，将 a 变为 0 就转化成了 将 f 变为 0，对于操作 1来说就相当于翻转了 $ f_{x,y} $。对于操作 4，就相当于翻转 $ f_{x-1,y-1},f_{x-1,m},f_{n,y-1},f_{n,m} (x>1,y>1) $ 如果 $ y=1 $，用两次操作 1 代替，显然更优。

不能发现，两次操作 4 并不优，他只改变了 6 个格子，不如进行 6 次操作 1 更优。所以我们只特判一次操作 4，当 $ f_{x-1,y-1}=f_{x-1,m}=f_{n,y-1}=f_{n,m}=1 (x<n,y<m) $ 时执行一次操作 4 ，可以 $ ans \gets ans-1 $。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=510;
int a[maxn][maxn],f[maxn][maxn];
char s[maxn][maxn];

int main(){
	
	int n,m,ans=0;
	
	scanf("%d %d",&n,&m);
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf(" %c",&s[i][j]);
			a[i][j]=(s[i][j]=='B');
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f[i][j]=a[i][j]^a[i+1][j]^a[i][j+1]^a[i+1][j+1];
			if(f[i][j]) ans++;
		}
	}
	
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(f[i-1][m]&&f[n][j-1]&&f[i-1][j-1]&&f[n][m]){
				printf("%d\n",ans-1);
				return 0;
			}
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
```


---

## 作者：EuphoricStar (赞：1)

## 思路

神仙思维题。

首先可以发现操作 2 和 3 都是无意义的。因为操作 2 可以转化成两次操作 1（翻转左下角为 $(n,1)$，右上角为 $(x,y)$ 的矩阵可以转化为翻转 $(1,1),(n,y)$ 再翻转 $(1,1),(x-1,y)$），操作 3 同理。

然后就是最重要的一步。令 $a_{i,j} = [s_{i,j} = \texttt{B}]$，$b_{i,j} = a_{i,j} \oplus a_{i+1,j} \oplus a_{i,j+1} \oplus a_{i+1,j+1}$。那么要让 $a$ 全变为 $0$，就是让 $b$ 全变为 $0$。操作 1（翻转左上角为 $(1,1)$，右下角为 $(x,y)$ 的矩阵）就转化成翻转 $b_{x,y}$，操作 4（翻转左上角为 $(x,y)$，右下角为 $(n,m)$ 的矩阵）就转化成翻转 $b_{x-1,y-1}$，$b_{x-1,m}$，$b_{n,y-1}$ 和 $b_{n,m}$。这一步可以自己手动模拟一下就明白了。

显然我们只会贪心地当 $b_{x,y}$ 为 $1$ 时才执行操作 1，$b_{x-1,y-1}$，$b_{x-1,m}$，$b_{n,y-1}$ 和 $b_{n,m}$都为 $1$ 时才执行操作 2。

然后又发现执行两次及以上操作 4 不优，可以转化为执行 $6$ 次操作 1，因为花了 $6$ 代价只翻转了 $6$ 个元素。所以只用特判是否执行一次操作 4。

## 代码

```cpp
const int maxn = 510;

int n, m, a[maxn][maxn], b[maxn][maxn];
char s[maxn][maxn];

void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= m; ++j) {
			b[i][j] = (s[i][j] == 'B');
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			a[i][j] = (b[i + 1][j + 1] ^ b[i + 1][j] ^ b[i][j + 1] ^ b[i][j]);
			if (a[i][j]) {
				++ans;
			}
		}
	}
	for (int i = 2; i <= n; ++i) {
		for (int j = 2; j <= m; ++j) {
			if (a[i - 1][j - 1] && a[i - 1][m] && a[n][j - 1] && a[n][m]) {
				printf("%d", ans - 1);
				return;
			}
		}
	}
	printf("%d", ans);
}
```


---

## 作者：happybob (赞：0)

简单题。

根据对于构造与贪心的问题的一般思考方式，考虑将操作简化。容易发现以左下和右上为起点的矩形花费太大，完全没有用，但是右下角为起点的矩形可能有用。

不过进一步地，容易发现每一次对右下角矩形操作可以转为 $4$ 次对左上矩形的操作，并且其中有一个操作是将整个矩形翻转。如果最优操作中有偶数次对右下角翻转，那么对整个矩形的翻转就被消去了，可以用左上替代。

更进一步，发现右下矩形操作次数就算是奇数，也可以将右下矩形操作变为只有 $1$ 次。故存在方案使得只有至多一次右下矩形的操作，其余都是左上矩形的操作。

如果想到差分就做完了，想不到的可以考虑每个 $0$ 或 $1$ 相当于限制了这个点右下角的操作次数的奇偶性，对于每个点和右边点异或就能得到这一列的一段后缀的结果。将每一列这样的相邻不同数量求和即可。对于唯一一次右下操作，枚举位置并简单算下贡献就可以做到 $O(n^2)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <queue>
using namespace std;

constexpr int N = 505;

int n, m;

array<array<char, N>, N> c;
array<array<bool, N>, N> b, ts;

inline int calc1()
{
	int ans = 0;
	for (int j = 1; j <= m; j++)
	{
		bool lst = 0;
		for (int i = n; i >= 1; i--)
		{
			bool nd = b[i][j] ^ b[i][j + 1];
			if (nd ^ lst)
			{
				ans++;
			}
			lst = nd;
		}
	}
	return ans;
}

inline int calc2()
{
	int ans = calc1(), minn = ans;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 2; j <= m; j++)
		{
			int nret = ans - (b[n][m] == 1) - (b[n][j - 1] ^ b[n][j] == 1) - (b[i - 1][j] ^ b[i - 1][j - 1] ^ b[i][j - 1] ^ b[i][j]) - (b[i - 1][m] ^ b[i][m]) + 3;
			minn = min(minn, nret);
		}
	}
	return minn;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++) cin >> c[i][j], b[i][j] = (c[i][j] == 'W' ? 0 : 1);
	}
	cout << calc2() << "\n";
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

我会的题就是大 shaber 题，我不会的题还是小 shaber 题。所以这题是大 shaber 题。

考虑我们很容易用两次以 $(1,1)$ 开头的矩阵来代替 $(n,1)$ 开头的矩阵和 $(1,m)$ 开头的矩阵。现在问题就是 $(n,m)$ 开头的矩阵貌似只能用 $4$ 次操作来代替，并不划算。

不过注意到如果要替代多个 $(n,m)$ 开头的矩阵，好像都共用了翻转整个矩阵。所以实际上两个以 $(n,m)$ 开头的矩阵就可以合并为 $6$ 个以 $(1,1)$ 开头的矩阵，代价相等。

所以最多只会有一个 $(n,m)$ 的矩阵。

考虑到一个位置是否要反转，只需要计算 $a_{x,y} \oplus a_{x+1,y} \oplus a_{x,y+1} \oplus a_{x+1,y+1}$ 是否为 $1$，如果为 $1$ 就要翻转，否则不需要。

那么强制性加入一个以 $(n,m)$ 开头的矩阵，最多会有 $4$ 个位置 $a_{x,y} \oplus a_{x+1,y} \oplus a_{x,y+1} \oplus a_{x+1,y+1}$ 奇偶性发生改变——就是四个角落。那么可以 $O(1)$ 判断。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500+10;
int n,m,ans,tans,a[MAXN][MAXN],b[MAXN][MAXN];
int solve(int u) {
	ffor(i,1,n) ffor(j,1,m) b[i][j]=a[i][j]^u;
	int cnt=0;
	ffor(i,1,n) ffor(j,1,m) cnt=cnt+(b[i][j]^b[i+1][j]^b[i][j+1]^b[i+1][j+1]);
	return cnt;
}
int check(int x,int y) {
	if(x==0||y==0) return 0;
	if(a[x][y]^a[x+1][y]^a[x][y+1]^a[x+1][y+1]) return -1;
	return 1;	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m; ffor(i,1,n) {string S;cin>>S;ffor(j,1,m) a[i][j]=(S[j-1]=='B');}
//	ffor(i,1,n) {
//		ffor(j,1,m) cout<<(a[i][j]^a[i+1][j]^a[i][j+1]^a[i+1][j+1])<<' ';
//		cout<<'\n';	
//	}
	ans=min(tans=solve(0),solve(1)+1);
	ffor(i,1,n) ffor(j,1,m) {
		int ttans=tans+3;
		ttans+=check(i-1,j-1)+check(n,j-1)+check(i-1,m)+check(n,m);
		ans=min(ans,ttans);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

对于矩阵取反非常不好做。这时候我们可以联想到差分，将它转化为单点取反。

所以我们构造广义差分数组 $a_{i,j} = s_{i,j}\oplus s_{i+1,j}\oplus s_{i,j + 1}\oplus s_{i+1,j + 1}$，原矩阵 $s$ 全 $0$ 等价于矩阵 $a$ 全 $0$。发现 $1,2,3$ 操作对应单点取反，$4$ 操作对应 $4$ 个点取反。

所以 $4$ 操作最多只会进行一次，枚举以下即可。

```cpp
#define N 505
int n, m, a[N][N], u[N][N]; char s[N];
int main() {
	//int T = read();while(T--)solve();
	n = read(), m = read();
	rep(i, 1, n){
		scanf("%s", s + 1);
		rep(j, 1, m)a[i][j] = s[j] == 'B';
	}
	int ans = 0;
	rep(i, 1, n)rep(j, 1, m)ans += (u[i][j] = a[i][j] ^ a[i + 1][j] ^ a[i][j + 1] ^ a[i + 1][j + 1]);
	if(u[n][m])
		rep(i, 1, n - 1)rep(j, 1, m - 1)if(u[i][j] && u[n][j] && u[i][m]){
			printf("%d\n", ans - 1);return 0;
		}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

性质题。

首先我们会发现，$2$ 和 $3$ 操作是无用的，因为均可被两次 $1$ 操作替代。而 $4$ 操作只能用四次 $1$ 操作替代，可能是优的。

首先我们先贪心地只使用 $1$ 操作，计算出每个位置是否会被操作。

考虑 $4$ 操作在什么情况下有增益。如果存在 $(i,j),(i,m),(n,j),(n,m)$ 均要被操作，不难发现此时使用 $4$ 操作可以减少 $1$ 的花费。然而，在操作完一次后，$(n,m)$ 一定不需要被操作，所以只有不可能再存在 $(i,j),(i,m),(n,j),(n,m)$ 均要被操作。故最多使用一次 $4$ 操作。

总复杂度 $O(nm)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int c[505][505],dw[505][505],ans=0;
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		char p; cin>>p;
		c[i][j]=(p=='B');
	}
	for(int i=n;i>=1;i--) for(int j=m;j>=1;j--){
		c[i][j]^=dw[i+1][j]^dw[i][j+1]^dw[i+1][j+1];
		ans+=c[i][j];
		dw[i][j]=c[i][j]^dw[i+1][j]^dw[i][j+1]^dw[i+1][j+1];
	}
	for(int i=1;i<n;i++) for(int j=1;j<m;j++) if(c[i][j]&&c[i][m]&&c[n][j]&&c[n][m]){
		cout<<ans-1;
		return 0;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CmsMartin (赞：0)

[可能更好的阅读体验](http://cmsblog.top/archives/aliceandrecoloring1)

## 题目描述

[题目传送门](http://codeforces.com/problemset/problem/1592/F1)

## 思路

没想到对矩阵的转化 qwq

不妨假设 `W` 为 $1$，`B` 为 $0$。

显然操作 2、3 都可以由两次操作 1 容斥得到，而且花费更优。可以不考虑。

于是我们只需要考虑操作 1、4 的贡献。

矩阵的全部元素翻转相当于子矩阵异或 $1$。处理矩阵很麻烦，有没有办法将矩阵信息拍平到几个点上呢？

可以考虑构造 $a_{i,j} = c_{i,j} \oplus c_{i+1,j} \oplus c_{i,j + 1} \oplus c_{i + 1,j + 1}$。

这样有什么好处呢？

可以发现操作一变成了 $a_{x,y}$ 异或 $1$，操作四变成了 $a_{x-1,y-1},a_{x-1,m},a_{n,y-1},a_{n,m}$ 异或 $1$。

操作四只能选定四个为 $1$ 的点进行一次，不然会带来负影响。时间复杂度 $\mathcal{\Theta(nm)}$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int w(char c) { return (c == 'B'); }

char c[510][510];
int n, m, a[510][510], Ans;

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> (c[i] + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) 
			Ans += (a[i][j] = (w(c[i + 1][j + 1]) ^ w(c[i + 1][j]) ^ w(c[i][j + 1]) ^ w(c[i][j])));
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
			if (a[i - 1][j - 1] && a[i - 1][m] && a[n][j - 1] && a[n][m]) {
				Ans--;
				goto End;
			}
	End:;
	cout << Ans << endl;
	return 0;
}

---

## 作者：5k_sync_closer (赞：0)

操作 $2,3$ 可以用 $1,4$ 容斥，所以没用。

设 $b_{i,j}=a_{i,j}\oplus a_{i+1,j}\oplus a_{i,j+1}\oplus a_{i+1,j+1}$，

则操作 $1$ 翻转 $(1,1)$ 到 $(i,j)$ 的矩阵等价于 $b_{i,j}\gets b_{i,j}\oplus 1$，

操作 $4$ 翻转 $(i,j)$ 到 $(n,m)$ 的矩阵等价于 $b_{n,m}\gets b_{n,m}\oplus 1,b_{i-1,m}\gets b_{i-1,m}\oplus 1,b_{n,j-1}\gets b_{n.j-1}\oplus 1,b_{i-1,j-1}\gets b_{i-1,j-1}\oplus 1$。

注意到操作 $4$ 最多做 $1$ 次，因为之后的操作 $4$ 只能影响三个位置，不如操作 $1$。

所以如果可以找到 $b_{n,m}=b_{i-1,m}=b_{n,j-1}=b_{i-1,j-1}=1$，对 $(i,j)$ 到 $(n,m)$ 的矩阵做一次操作 $4$，然后用操作 $1$ 翻转剩下的位置即可。

```cpp
#include <cstdio>
int n, m, q;
bool a[550][550], b[550][550];
char c;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= m;++j)
			scanf(" %c", &c), a[i][j] = c == 'B';
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= m;++j)
			b[i][j] = a[i][j] ^ a[i + 1][j] ^ a[i][j + 1] ^ a[i + 1][j + 1];
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= m;++j)
			q += b[i][j];
	if(b[n][m])
		for(int i = 1;i < n;++i)
			for(int j = 1;j < m;++j)
				if(b[i][j] && b[i][m] && b[n][j])
					return !printf("%d", q - 1);
	return !printf("%d", q);
}
```


---

