# Sereja and Mirroring

## 题目描述

Let's assume that we are given a matrix $ b $ of size $ x×y $ , let's determine the operation of mirroring matrix $ b $ . The mirroring of matrix $ b $ is a $ 2x×y $ matrix $ c $ which has the following properties:

- the upper half of matrix $ c $ (rows with numbers from $ 1 $ to $ x $ ) exactly matches $ b $ ;
- the lower half of matrix $ c $ (rows with numbers from $ x+1 $ to $ 2x $ ) is symmetric to the upper one; the symmetry line is the line that separates two halves (the line that goes in the middle, between rows $ x $ and $ x+1 $ ).

Sereja has an $ n×m $ matrix $ a $ . He wants to find such matrix $ b $ , that it can be transformed into matrix $ a $ , if we'll perform on it several (possibly zero) mirrorings. What minimum number of rows can such matrix contain?

## 说明/提示

In the first test sample the answer is a $ 2×3 $ matrix $ b $ :

`<br></br>001<br></br>110<br></br>`If we perform a mirroring operation with this matrix, we get the matrix $ a $ that is given in the input:

`<br></br>001<br></br>110<br></br>110<br></br>001<br></br>`

## 样例 #1

### 输入

```
4 3
0 0 1
1 1 0
1 1 0
0 0 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3
0 0 0
0 0 0
0 0 0
```

### 输出

```
3
```

## 样例 #3

### 输入

```
8 1
0
1
1
0
0
1
1
0
```

### 输出

```
2
```

# 题解

## 作者：tangber (赞：8)

## 思路
可以用函数递归来做：

因为只会上下翻转，所以在递推过程中只需考虑 $n$ 的值就行了。每次递归判断上下是否能够翻转，最后加一点小小的特判，这道题就能快乐的 AC 啦！

完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int mapp[5005][5005];
int f(int nn)
{
	for(int i=1;i<=nn;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(mapp[i][j]!=mapp[2*nn-i+1][j])//判断是否可以上下颠倒 
			{
				return nn*2;
			}
		}
	}
    if(n==1) return 1;//特判只剩一行的情况 ，但可以省略（与下一行合并） 
    if(n%2==1) return nn;//特判n为奇数的情况 
    return f(nn/2);//递归 
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%lld",&mapp[i][j]);
		}
	}
	if(n%2==1)//特判n为奇数的情况
		printf("%lld",n);
	else
		printf("%lld",f(n/2));
	return 0;
}
```

---

## 作者：Fuxh_18 (赞：2)

## 题意
[题目传送门](https://www.luogu.com.cn/problem/CF426B)
## 思路
这个矩阵只上下镜像，所以和 $m$ 的关系不大（但也有）。我们可以用一个 dfs 来不断往回推，直到它无法形成镜像为止。

注：当 $n$ 为奇数时，一定不能再往下推了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[101][101];
int dfs(int h){
	for(int i=1;i<=h;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=a[h*2-i+1][j]){ //判断当前矩阵是否能镜像后得到之前的矩阵 
				return h*2; //这个矩阵不成立，那它上一个就是最少的 
			}
		}
	}
	if(h%2==1){ //奇数，不能往下 
		return h;
	}
	return dfs(h/2);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j]; //输入 
		}
	}
	if(n%2==1){ //一开始就是奇数，就不用 dfs 了 
		cout<<n;
		return 0;
	}
	cout<<dfs(n/2); //dfs 往回推 
	return 0;
} 
```

---

## 作者：__Immorta__ (赞：1)

**前言：**

这个题其实还是很简单的，略低于黄题难度，个人感觉普及-。

只要看懂题意就很容易理解了。

**题目原文：**

给一个 $n \times m$ 的矩阵，它是由一个小矩阵进行几次镜像而来，
一次镜像代表把原来矩阵上下颠倒，再放在原来矩阵下面。
问这个矩阵镜像前至少有多少行。

**题意剖析：**

大致意思就是让我们逆序推出原来的矩阵。

给出现在的矩阵，该矩阵是由一个矩阵重复镜像翻转（上下颠倒）得来的。

举个栗子。

原矩阵：
```
100
001
```

镜像一次后；
```
100
001
001
100
```

镜像两次后：
```
100
001
001
100
100
001
001
100
```

给出镜像两次的后的矩阵，让我们求出最开始的矩阵的行数，也就是两行。

是不是有点像回文串？我将其成为回文矩阵不过分吧。。

只需要分成两段，判断上下是否相等，如果相等，就进入下一步，然后重复直到最后一个矩阵，是不是也有点递归的思想在里头。

**整体思路：**

- 使用一个函数进行操作
- 每次折半，判断是否相等（回文矩阵），如果是，进入下一轮递归，不是，那么当前矩阵就是原最终矩阵
- 输出行数

**头文件方面：**

这里我使用万能头文件：
`#include<bits/stdc++.h>`

**大致代码：**

- 输入行数列数：
```c
cin>>n>>m;
```

- 输入当前矩阵（n行m列）：
```c
for(int i=1;i<=n;i++){
  for(int j=1;j<=m;j++){
    cin>>a[i][j];
  }
}
```

- “递归” 函数操作：
```c
dfs(n)
```

- 整体主函数代码（有手就行啊）：
```c
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	cout<<dfs(n);
	return 0;
}
```

**接下来就是函数部分的代码了**
```c
int dfs(int x){
  //基础框架
  //每次折半，判断两端是否完全相等
  return dfs(x/2);
}
```

- 判断部分：
```c
for(int i=1;i<=x/2;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=a[x-i+1][j]){
				return x;
			}
		}
	}
```
这里详细的叙述一下：

首先是循环条件，第一重循环作为行循环，作折半处理，所以用行数除2来循环，第二重循环作为列循环，由于列照常不变，所以直接用列数 $m$ 来循环即可。

>注意，变量 $n$ 和 $m$ 定义为全局的！

然后判断，如果上下两个不相等，直接返回 $x$，代表这里行不通。

最后，如果查询到最终目标，也就是只剩一行或者无法折半，就返回并且输出行数即可。

- 所以这里要用到特判了
```c
if(x%2!=0){
		return x;
}
```
这不需要讲解吧，$x$ 为当前行数，如果不能继续就一直返回辣。

最后，给递归套上输出即可

```c
cout<<dfs(n);
```

完结撒花 *★,°*:.☆(￣▽￣)/$:*.°★* 。！！

第三次修改，管理大大求过awa

---

## 作者：ljk8886 (赞：1)

建议降橙。[CF 题目传送门](https://codeforces.com/problemset/problem/426/B)

# 题意分析
注意到 $n,m \le 100$，所以可以直接暴力判断矩阵是不是由镜像得到的，如果是就继续判断这个矩阵的一半，当然如果行数不是偶数就可以直接退出了。

# 代码
```cpp
#include <bits/stdc++.h>
#define ft first
#define sd second
#define endl '\n'
#define pb push_back
#define md make_pair
#define gc() getchar()
#define pc(ch) putchar(ch)
#define umap unordered_map
#define pque priority_queue
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 bint;
typedef pair<int, int> pii;
typedef pair<pii, int> pi1;
typedef pair<pii, pii> pi2;
const int INF = 0x3f3f3f3f;
inline ll read()
{
	ll res = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') f = (ch == '-' ? -1 : f), ch = getchar();
	while (ch >= '0' && ch <= '9') res = res * 10 + ch - '0', ch = getchar();
	return res * f;
}
inline void write(ll x)
{
	if (x < 0) x = -x, pc('-');
	if (x > 9) write(x / 10);
	pc(x % 10 + '0');
}
inline void writech(ll x, char ch) { write(x), putchar(ch); }
const int N = 1e2 + 5;
char ch[N][N];
int n = read(), m = read();
bool check(int h) // 判断 h 行的矩阵是不是由镜像得到的 
{
	for (int i = 1; i <= h / 2; i++)
		for (int j = 1; j <= m; j++)
			if (ch[i][j] != ch[h - i + 1][j]) return false;
	return true;
}
int main()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> ch[i][j];
	while (n % 2 == 0) // 如果 n 是偶数 
		if (check(n)) n /= 2; // 接着处理矩阵的一半 
		else break;
	write(n);
	return 0;
}
```

---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF426B)

## 思路

可以用递归求解。

首先如果行的数量是奇数，那么就不可能是通过镜像操作得到的，直接输出 $n$。然后可以发现每次镜像的操作都可以使行的数量 $\times2$，所以每次递归要把行的数量 $\div2$。检查的时候如果任意一个 $a_{i,j}\ne a_{2n-i+1,j}$，那么答案就是 $2n$。

递归的时候也要特判 $n=1$ 和 $n$ 是奇数的情况。

```cpp
#include <iostream>
using namespace std;
int n, m, a[1010][1010];
int dfs(int n) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] != a[n * 2 - i + 1][j])
                return n * 2;
    if (n == 1)
        return 1;
    if (n & 1)
        return n;
    return dfs(n / 2);
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    if (n & 1) {
        cout << n << endl;
        return 0;
    }
    cout << dfs(n / 2) << endl;
    return 0;
}
```

---

## 作者：Zhang_Shao_ (赞：0)

## 题意
给出一个 $n \times m$ 的矩阵，是由一个小矩阵多次镜像翻转复制或不翻转得到的，求翻转的次数。
## 解法
这题是一道简单的递归题。  
容易发现，对于一个 $n \times m$ 的矩阵 $a$，若 $2 \nmid n$ 则不能通过翻转得到；否则如果所有的 $1 \le i \le \frac{n}{2}$，$1 \le j \le m$ 都满足 $a_{i,j} = a_{n-i+1,j}$，那么 $a$ 就是由它的上半部分翻转成的。  
因此，想要判断一个矩阵翻转的次数，只需判断上下两部分是否轴对称，返回 $1$ 或它的子矩阵的翻转次数 $+ 1$。  
对于每次判断，需要 $O(nm)$ 的时间复杂度，最多需要 $\log(n)$ 次。所以总时间复杂度大约为 $O(\log(n)nm)$。（详见代码）
## 实现过程
```cpp
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int a[105][105],n,m;
//a表示矩阵，n，m，表示矩阵大小
int f(int x){
	//返回 a(x,m) 的翻转次数
	if(x%2) return x;
	for(int i=1;i<=x/2;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=a[x-i+1][j]) return x;
		}
	}
	return f(x/2);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	//输入
	printf("%d",f(n));
	//输出
	return 0;
	//结束
}
```

---

## 作者：zzhbpyy (赞：0)

### [Sereja and Mirroring](https://codeforces.com/problemset/problem/426/B)
根本不用什么递归，不知道为什么要评黄。考虑到 $n$ 的范围这么小，只要暴力判断当前的矩阵是否可以由小矩阵镜像而来即可，若可以就把 $n$ 除以 $2$。重复此过程就可得到答案。

## [Code](https://codeforces.com/contest/426/submission/282414767)

---

## 作者：OIer6666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF426B)（[附CodeForces](https://codeforces.com/problemset/problem/426/B)）

## 题目大意

给你一个 $n$ 行 $m$ 列的镜子，已知镜子可以复制。

举个例子：

```
0 1 0
1 0 1
```

复制后为

```
0 1 0
1 0 1
1 0 1
0 1 0
```

求最少多少行的镜子经过若干次复制后变为输入的镜子。

## 解题思路

模拟就行了。

- 若当前行数为 $h$，$h \bmod 2=1$，跳出循环。

- 判断现在的镜子是不是某个镜子的复制，若不是，则跳出循环；若是，继续判断，将行数减少一半。

输出最后的行数。

### AC代码：
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n,m;
int a[105][105],t;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	t=n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	while(t%2==0){
		bool flag=0;
		for(int i=1;i<=t/2;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]!=a[t-i+1][j]){
					flag=1;
					break;
				}
			}
			if(flag)break;
		}
		if(flag)break;
		t/=2;
	}
	cout<<t;
	return 0;
}
```

---

## 作者：Eason_cyx (赞：0)

首先明确：镜像的过程中不会改变列的数量，也就是 $m$。

那么我们枚举满足 $x \times 2^{y} = n$ 这个条件的所有 $x$，判断初始时如果是一个 $x \times b$ 的矩阵，能否通过镜像变成输入中的 $n \times m$ 的矩阵即可。

注意：如果输入的 $n$ 不是 $2$ 的倍数，那么很显然无法镜像，直接输出 $n$ 即可。

时间复杂度为 $O(nm\log^2n)$，其中 $\log n$ 是外层循环，另一个 $\log n$ 是关于 $len$ 的倍增循环，内层可以看成 $n \times m$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105][105],b[105][105];
int main() {
    int n,m; cin >> n >> m;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++) cin >> a[i][j];
    int ans = n;
    if(n % 2) {
        cout << n << endl;
        return 0;
    }
    int res = n;
    do {
    	res /= 2;
    	for(int i = 1;i <= res;i++) {
            for(int j = 1;j <= m;j++) {
                b[i][j] = a[i][j];
            }
        }
        int len = res * 2;
        for(;len <= n;len *= 2) {
            for(int k = len/2+1;k <= len;k++) {
                for(int j = 1;j <= m;j++) {
                    b[k][j] = b[(len/2)-(k-(len/2)-1)][j];
                }
            }
            len *= 2;
        }
        bool flag = true;
        for(int i = 1;i <= n;i++) {
            for(int j = 1;j <= m;j++) {
                if(b[i][j] != a[i][j]) {
                    flag = false;
                    break;
                }
            }
        }
        if(flag) ans = res;
    } while(res % 2 == 0);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑枚举。

发现每次行数都会翻倍，所以最后的数 $x$ 乘 $2$ 的若干次幂一定是 $n$，所以考虑 $x$ 最小是多少，那么就是将 $n$ 二进制中第一个 $1$ 之前的 $0$ 都去掉。

每次暴力模拟判断，然后这个数再 $\times 2$，直到满足即可（当他 $=n$ 时一定满足）。

具体细节看代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> a, b;

int main() {
	scanf("%d%d", &n, &m);
	a.push_back({});
	b.push_back({});
	for (int i = 1; i <= n; ++i) {
		a.push_back({});
		b.push_back({});
		a[i].push_back(0);
		b[i].push_back(0);
		for (int j = 1; j <= m; ++j) {
			int v; scanf("%d", &v);
			a[i].push_back(v);
			b[i].push_back(0);
		}
	}

	int tmp = n;
	while (tmp) {
		if (tmp & 1) break;
		tmp >>= 1;
	}


	while (tmp < n) {
		// cout << tmp << endl;
		for (int i = 1; i <= tmp; ++i) b[i] = a[i];
		int j = tmp;
		for (; j * 2 <= n; j *= 2) {
			for (int k = j + 1, p = j; k <= 2 * j; ++k, --p)
				b[k] = b[p];
		}
		bool flag = true;
		for (int j = 1; j <= n; ++j) if (b[j] != a[j]) {
			flag = false;
			break;
		}

		if (flag) {
			printf("%d\n", tmp);
			return 0;
		}
		tmp <<= 1;
	}

	printf("%d\n", n);

    return 0;
}
```

---

## 作者：ran_qwq (赞：0)

枚举镜像前矩阵的行数 $x$，如果无法再分割下去，则这就是最小行数。

怎么判断能不能分割呢？

首先，如果 $x$ 为奇数，就无法把 $x$ 行按行平均分成两份，就一定不能分割。

然后就可以对这个 $x\times m$ 的矩阵进行分割，因为以第 $\dfrac{x}{2}$ 与 $\dfrac{x}{2}+1$ 行之间的线为对称轴，所以如果能分割，则 $a_{i,j}(1\leq i\leq\dfrac{x}{2},1\leq j\leq m)$ 相等。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,INF=1e9;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
		if(ch=='-')
			f=-1;
	}
	while(ch>='0'&&ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
void Write(int x)
{
	if(x<0)
	{
		putchar('-'),Write(-x);
		return;
	}
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	Write(x/10),putchar(x%10+'0');
}
void write(int x,char *s)
{
	Write(x),printf("%s",s);
}
int n,m,a[110][110];
bool check(int x)
{
	for(int i=1;i<=(x>>1);i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!=a[x-i+1][j])
				return 0;
	return 1;
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	for(int i=n;i;i>>=1)
		if((i&1)||!check(i))
			Write(i),exit(0);
}

```


---

