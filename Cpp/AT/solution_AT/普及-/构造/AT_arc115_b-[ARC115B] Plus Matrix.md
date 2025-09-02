# [ARC115B] Plus Matrix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc115/tasks/arc115_b

$ N $ 行 $ N $ 列の非負整数を成分とする行列 $ C $ が与えられます。すべての $ (i,j) $ について $ C_{i,j}=A_i+B_j $ を満たすような非負整数列 $ A_1,A_2,\ldots,A_N $ と $ B_1,B_2,\ldots,B_N $ の組が存在するか判定し、存在するなら一つ出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $
- $ 0\ \leq\ C_{i,j}\ \leq\ 10^9 $

### Sample Explanation 1

$ A,B $ は非負整数列であることに注意してください。

## 样例 #1

### 输入

```
3
4 3 5
2 1 3
3 2 4```

### 输出

```
Yes
2 0 1
2 1 3```

## 样例 #2

### 输入

```
3
4 3 5
2 2 3
3 2 4```

### 输出

```
No```

# 题解

## 作者：封禁用户 (赞：3)

#### 题意简述

给定一个 $N \times N$ 的矩阵 $C$。你需要求出两个数组 $A$ 和 $B$，使得 $\forall i,j$ 都有 $C_{i,j}=A_i+B_j$，输出 $A$ 和 $B$，无解则输出 `No`。

---

#### 题目分析

一眼构造题，通过观察可以发现：\
如果 $C$ 中的每一行的差分数组都相同，那么这个矩阵就有解，否则无解。\
那么进一步可以得出，如果有一个基准数组 $S$，那么 $C$ 中的每一行都是 $S$ 加上某个数，而这个 $S$ 就是 $B$ 数组，即 $C$ 中最小的一行，$A$ 数组中的元素 $A_i$ 就对应了 $C$ 中第 $i$ 行需要加上的数。

---

#### AC Code

```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=505;
int n,idx,a[N],c[N][N],b[N][N];
std::string s[N];
signed main() {
    std::cin>>n;
    rep(i,1,n) {
        rep(j,1,n) {
            std::cin>>c[i][j];
        }
    }
    if(n==1) {
        puts("Yes");
        std::cout<<c[1][1];
        exit(0);
    }
    int min=LLONG_MAX;
    rep(i,1,n) {
        min=std::min(min,c[i][1]);
    }
    rep(i,1,n) {
        if(min==c[i][1]) {
            idx=i;
            rep(j,1,n) {
                std::swap(c[i][j],c[1][j]);
            }
            break;
        }
    }
    rep(i,1,n) {
        rep(j,2,n) {
            b[i][j]=c[i][j]-c[i][j-1];
        }
    }
    rep(i,1,n-1) {
        rep(j,2,n) {
            if(b[i][j]!=b[i+1][j]) {
                puts("No");
                exit(0);
            }
        }
    }
    puts("Yes");
    rep(i,1,n) {
        a[i]=c[i][1]-c[1][1];
    }
    std::swap(a[1],a[idx]);
    rep(i,1,n) {
        std::cout<<a[i]<<" ";
    }
    puts("");
    rep(i,1,n) {
        std::cout<<c[1][i]<<" ";
    }
    return 0;
}
```

---

## 作者：xuan_gong_dong (赞：2)

## 题面

[[ARC115B] Plus Matrix](https://www.luogu.com.cn/problem/AT_arc115_b)

## 分析
通过手算一下样例发现如果有解，那 $C$ 中同一列的任意值与其右侧相邻的值的差相同，同一行的任意值与其右侧相邻的值的差也一定相同。

即：

 $$C_{i,j}-C_{i,j-1}=C_{i-1,j}-C_{i-1,j}(2\le i,j \le n)$$
 $$C_{i-1,j}-C_{i,j}=C_{i-1,j-1}-C_{i,j-1}(2\le i,j \le n)$$

如果不满足上式，则无解。

因为 $A,B$ 数列中的元素都为非负整数，同时容易发现 $ C_{i,i}=A_i+B_i$，
所以只要让 $A$ 或者 $B$ 取最小的行或者列（此处最小意为各个值都为最小的），那么另一个数列就直接求出来了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[510][510];
int aa[510][510],bb[510][510];
int a[510],b[510];
int n;
int main()
{
	scanf("%d",&n);
	int Min=0x7f7f7f7f,x,y;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&c[i][j]);
			if(Min>c[i][j])
			{
				Min=c[i][j];
				x=i,y=j;
			}
			aa[i][j]=c[i][j]-c[i][j-1];
			bb[i][j]=c[i][j]-c[i-1][j];
		}
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=2;j<=n;j++)
		{
			if(aa[i][j]!=aa[i-1][j]||bb[i][j]!=bb[i][j-1])
			{
				printf("No");
				return 0;
			}
		}
	}
	puts("Yes");
	for(int i=1;i<=n;i++)
	{
		b[i]=c[x][i];
	}
	for(int i=1;i<=n;i++)
	{
		a[i]=c[i][i]-b[i];
		printf("%d ",a[i]);
	}
	putchar(10);
	for(int i=1;i<=n;i++)
	{
		printf("%d ",b[i]);
	}	
	return 0;
	
}
```


---

## 作者：czh___ (赞：1)

题目大意：对所有 $C$ 数组，都有 $c _ {j} ^ {i}=a_{i}+b_{j}$。是否存在一个序列 $A,B$。如果存在则输出 Yes 并且输出 $A$ 序列和 $B$ 序列，否则就输出一个 No 就行了。（但这个题隐含了 $A,B$ 的每个元素都为非负数这个条件。所以导致我错了好几次）。

题目思路：首先我们得先判断是否存在 $A,B$ 序列。这个判断我们可以用对角线来判断，对角线所有元素相加 $\times$ $n$ $=$ 所有元素相加。（为什么是对的呢？我想是因为对角线上面对所有 $A,B$ 的元素都用上了，偶然性不存在（我之前听同学说过有个类似题别人是这样写的，因为这个等式永远存在，所以我就没证明直接用了））。判断出来之后，我们就可以输出 $A,B$。在我们输入的时候用一个 $min1$ 记录最小值。$idx$ 记录这个最小值的 $i$。 我们令 $a_{idx}=0-min1$ 的数均可。这样的话对第 $i$ 行（我们可以求出所有的 $b$ 序列）并且 $b$ 序列为非负。然后我们对第一列,把所有的 $a_{i}$ 也能求出来，$a$ 序列也为非负（好好想想！！！）。
上代码！
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<iostream>
#include<cmath>
#include<queue>
#include<vector>
#define IOS ios::sync_with_stdio(false);cin.tie();cout.tie(0)

using namespace std;
typedef pair<int,int> pll;
typedef long long ll;
const int N=2e5+100;
const int maxn=550;
const int M=100003;

map<string,int> q;
bool st[N];
ll g[maxn][maxn];
ll a[maxn],b[maxn];
int n,idx=1;

void prit()
{
    a[idx]=0;
    for(int i=1;i<=n;i++)
    {
        b[i]=g[idx][i]-a[idx];
    }
    for(int i=1;i<=n;i++)
    {
        a[i]=g[i][1]-b[1];
    }
    for(int i=1;i<n;i++)
        cout<<a[i]<<" ";
    cout<<a[n]<<endl;
    for(int i=1;i<n;i++)
        cout<<b[i]<<" ";
    cout<<b[n]<<endl;
}

int main()
{
    IOS;
    cin>>n;

    ll sum1=0,sum2=0;
    int min1=1e9;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
    {
        cin>>g[i][j];
        if(g[i][j]<min1)
        {
            min1=g[i][j];
            idx=i;
        }
        if(i==j) sum1+=g[i][j];
        sum2+=g[i][j];
    }

    if(sum1*n==sum2)
    {
        cout<<"Yes"<<endl;
        prit();
    }
    else cout<<"No"<<endl;
    return 0;
}


```

---

## 作者：KυρωVixen (赞：1)

## 题意：
给你一个由非负整数组成的矩阵 $c$ 满足 $c_{i,j}=a_i+b_j$，求 $a$，$b$ 或报告无解。要求 $a_i\ge 0$，$b_i\ge 0$。

## 解法：
很显然的有一个贪心：先把每列减去这一列最小值并且记录 $b_j$，随后检查剩下每行的所有元素是否相同，如果有不相同的报告无解，否则对于每个 $i$ 令 $a_i\gets c_{i,1}$。最后输出 $a$，$b$ 即可。

正确性的证明考虑反证：

感性理解，因为每一列必然有一个最小值，所以每一列都有位置减掉之后变为 $0$，不会出现“这一列少减 $x$ 反而检查时合法”的情况（易证），保证我们的减去过程不会影响答案存在性。检查过程根据定义就知道是对的，所以该算法正确。

不知道第一篇题解为啥讲这么难。

## 代码：
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define rep(i,a,b) for(int i=(int)a;i<=(int)b;i++)
#define endl '\n'
using namespace std;
const int N=505;
int n,c[N][N],a[N],b[N];
int chk(int p){
    rep(i,2,n) if(c[p][i]!=c[p][1]) return -1;
    return c[p][1]; 
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    rep(i,1,n) rep(j,1,n) cin>>c[i][j];
    rep(j,1,n){
        b[j]=INF;
        rep(i,1,n) b[j]=min(b[j],c[i][j]);
        rep(i,1,n) c[i][j]-=b[j];
    } 
    rep(i,1,n){
        int tmp=chk(i);
        if(tmp==-1){
            cout<<"No"<<endl; return 0;
        }
        a[i]=tmp;
    }
    cout<<"Yes"<<endl;
    rep(i,1,n) cout<<a[i]<<" ";
    cout<<endl;
    rep(i,1,n) cout<<b[i]<<" ";
    cout<<endl;
}
```

---

## 作者：xiaoyang111 (赞：0)

### 思路

首先通过观察样例，可以发现好似跟差分数组有关系，所以我们往这方面想。

因为同一行的 $c$ 加的 $a_i$ 是一样的，所以我们可以让前面减后面的，就可以得到 $b$ 的差分数组。因为 $a_i$ 是在减的过程中被减去了。$a$ 的差分数组同理。

无解就是每一行每一列的差分数组算出来不同，就是无解。

答案就是先设 $a_1=0$，然后通过差分数组推原来的每个数。如果最后有负数，整体偏移一下。

然后先可以把 $b_1$ 通过矩阵的第一行第一列算出来，然后再用差分数组来算出来。

### 实现

不懂旁边有注释。

```cpp
#include <iostream>
using namespace std;
const int N=500+5;
int c[N][N];
int da[N];//a的差分数组
int db[N];//b的差分数组
int n;
bool check(){//是否有解
	int t;
	for (int i=2;i<=n;++i)
		for (int j=2;j<=n;++j){
			t=c[i][j]-c[i-1][j];//列
			if (t!=da[i]) return false;
			t=c[i][j]-c[i][j-1];//行
			if (t!=db[j]) return false;
		}
	return true;
}
int a[N],b[N];
int main(){
	cin >> n;
	for (int i=1;i<=n;++i){
		for (int j=1;j<=n;++j){
			scanf("%d",&c[i][j]);
		}
	}
	for (int i=1;i<=n;++i){
		da[i]=c[i][1]-c[i-1][1];//求列的差分数组
		db[i]=c[1][i]-c[1][i-1];//求行的差分数组
	}
	if (!check()){
		cout<<"No\n";
		return 0;
	}
	int mn=2e9;
	for (int i=1;i<=n;++i){//直接前缀和推出来
		a[i]=da[i]+a[i-1];
		mn=min(mn,a[i]);
	}
	mn=0-mn;//偏移量
	for (int i=1;i<=n;++i) a[i]+=mn;//偏移
	b[1]=c[1][1]-a[1];//算出第一个
	for (int i=2;i<=n;++i) b[i]=b[i-1]+db[i];
	cout<<"Yes\n";
	for (int i=1;i<=n;++i) printf("%d ",a[i]);
	putchar('\n');
	for (int i=1;i<=n;++i) printf("%d ",b[i]);
	return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
有一个长宽相同的矩阵，求是否有两个数组，对应坐标相加可以得到该矩阵。
# 题目思路
首先考虑是否有解。

仔细观察可以发现，每一行的差分是一样的。同理，每一列的差分也是一样的。我们可以运用这一性质判断是否有解。

对于求出答案，其实也很简单。仔细观察题目，答案其实是有无数种的。但为什么没有打上 Special Judge 呢？因为……

>$A,B,C$ 中元素均为非负整数。

由此，我们可以发现，数组 $B$ 就是矩阵 $C$ 中最小的一行。而有了数组 $B$，就可以轻松求出数组 $A$ 了。

至此，问题解决。

P.S. 下面的代码请勿直接交。
# AC Code
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

inline bool input (int x) {
	x = 0;
	int f = 1;
	bool flag = 0;
	char c = getchar ();

	while (!isdigit(c)) {
		if (c == '-') {
			c = getchar ();

			if (isdigit (c)) {
				f = -1;
				break;
			}
		} else {
			c = getchar ();
		}
	}

	while (isdigit (c)) {
		flag = 1;
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar ();
	}

	x *= f;
	return flag;
}

inline bool output (int x) {
	if (x < 0) {
		putchar ('-');
		x = -x;
	}

	char write[25], cnt = 0;

	do {
		write[++ cnt] = x % 10;
		x /= 10;
	} while (x);

	do {
		putchar (write[cnt --] | 48);
	} while (cnt);

	return x;
}

const int N = 500;

void init ();

int n, a[N + 5], b[N + 5], c[N + 5][N + 5], minn, minid; 

signed main () {
	init ();
	input (n);
	
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			input (c[i][j]);
		}
	}
	
	for (int i = 1; i < n; ++ i) {
		for (int j = 2; j <= n; ++ j) {
			if (c[i][j] - c[i][j - 1] != c[i + 1][j] - c[i + 1][j - 1]) {
				puts ("No");
				return 0;
			}
			
			if (c[j][i] - c[j - 1][i] != c[j][i + 1] - c[j - 1][i + 1]) {
				puts ("No");
				return 0;
			}
		}
	}
	
	for (int i = 1; i <= n; ++ i) {
		if (c[i][1] < minn) {
			minn = c[i][1];
			minid = i;
		}
	}
	
	for (int i = 1; i <= n; ++ i) {
		b[i] = c[minid][i];
	}
	
	for (int i = 1; i <= n; ++ i) {
		a[i] = c[i][i] - b[i];
	}
	
	puts ("Yes");
	
	for (int i = 1; i <= n; ++ i) {
		output (a[i]);
		putchar (' ');
	}
	
	puts ("");
	
	for (int i = 1; i <= n; ++ i) {
		output (b[i]);
		putchar (' ');
	}
	
	return 0;
}

void init () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
//	ios::sync_with_stdio (false);
//	cin.tie (0);
//	cout.tie (0);
}
```

---

## 作者：2011FYCCCTA (赞：0)

[原题](https://www.luogu.com.cn/problem/AT_arc115_b)

---
### 分析&思路

根据 $C_{i,j}=A_i+B_j$ 这个式子，不难发现相邻两行或两列的差是一定的，因为 $C_{i,j}-C_{i,j-1}=A_i+B_j-A_i-B_{j-1}=B_j-B_{j-1}$，$C_{i,j}-C_{i-1,j}=A_i+B_j-A_{i-1}-B_j=A_i-A_{i-1}$（被减数与减数交换同理）。可以依此来判断是否存在数列 $A$，$B$。

如果从 $C$ 中随便选择一行当 $B$，由于相邻两行的差是一定的，所以 $A_i = C_{i,j}-B_{i,j}$。但又由于题目中说 $A$ 中元素必须均为非负整数，因为相邻两行的差是一定的，所以在 $C$ 中相同列中最小的所在的那一行即为 $B$。

---
### 代码
```cpp
#include "bits/stdc++.h"
using namespace std;
int n , c[505][505];
int main()
{
    cin >> n;
    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j <= n ; j++) cin >> c[i][j];

    int minb = c[1][1] , minbp = 1;
    for (int i = 2 ; i <= n ; i++)
    {
        int t = c[i][1] - c[i - 1][1];
        if (c[i][1] < minb) {minb = c[i][1]; minbp = i;}
        bool flag = 1;
        for (int j = 2 ; j <= n ; j++)
            if (c[i][j] - c[i - 1][j] != t) {flag = 0; break;}
        if (!flag) {cout << "No"; return 0;}
    }
    cout << "Yes\n";
    for (int i = 1 ; i <= n ; i++) cout << c[i][1] - c[minbp][1] << ' ';
    cout << '\n';
    for (int i = 1 ; i <= n ; i++) cout << c[minbp][i]<< ' ';
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/arc115b-plus-matrix-de-ti-jie/)
## 题目大意
给你一个 $n\times n$ 的数组 $C$，$c_{i,j}=a_i+b_j$，求 $a$ 数组与 $b$ 数组，不保证有解，其中 $1\le n\le 500,1\le c_{i,j}\le 10^9$，而且 $a_i,b_i$ 都是非负整数。

$$\begin{bmatrix}
a_1+b_1&a_1+b_2&\cdots&a_1+b_{n-1}&a_1+b_n\\
a_2+b_1&a_2+b_2&\cdots&a_2+b_{n-1}&a_2+b_n\\
\vdots&\vdots&\vdots&\vdots&\vdots\\
a_{n-1}+b_1&a_{n-1}+b_2&\cdots&a_{n-1}+b_{n-1}&a_{n-1}+b_n\\
a_n+b_1&a_n+b_2&\cdots&a_n+b_{n-1}&a_n+b_n\\
\end{bmatrix}$$

## 思路
因为 $c_{i,j}=a_i+b_j,c_{i,j+1}=a_i+b_{j+1}$。

所以 $c_{i,j}-c_{i,j+1}=a_i+b_j-(a_i+b_{j+1})=a_j-a_{j+1}$。

将我们一行依次相减，就得到了 $b$ 的一组关系，其实就是 $n-1$ 个等式。

$\begin{cases}
b_1-b_2=c_{i,1}-c_{i,2}\\
\cdots\\
b_{n-1}-b_{n}=c_{i,n-1}-c_{i,n}
\end{cases}$

显然，对于所有的 $i\in [1,n]$  这 $n-1$ 个等式应该都是满足的。如果不能满足这个条件，那么就是无解的。

因为 $a_i,b_i$ 都是非负整数，所以我们需要找到一组解使上面的等式全部满足。为了让答案在最后好处理，我们可以先找到一组最小解。

因为上面的方程对于所有的 $i\in [1,n]$ 都满足，所以我们只需要考虑一行就可以了，为了便于讨论，我选取了第 $1$ 行。得到第 $i$ 行最小的元素 $x$，所有 $b_i=a_i-x$，对于 $a$ 数组也是如此。

因为我们找到的是最小解，所有有可能会出现 $a_i+b_j<c_{i,j}$ 的情况。因为我们已经得到了 $a$ 数组之间的关系，那么我们就可以将 $a$ 数组全部加 $1$。

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int n,c[N][N],a[N],b[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>c[i][j];
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<n;j++){
			if(c[i][j]-c[i][j+1]!=c[i+1][j]-c[i+1][j+1]){
				cout<<"No";
				return 0;
			}
		}
	}
	for(int j=1;j<n;j++){
		for(int i=1;i<n;i++){
			if(c[i][j]-c[i][j+1]!=c[i+1][j]-c[i+1][j+1]){
				cout<<"No";
				return 0;
			}
		}
	}
	int mmin=INT_MAX;
	for(int i=1;i<=n;i++){
		mmin=min(c[1][i],mmin);
	}
	for(int i=1;i<=n;i++){
		b[i]=c[1][i]-mmin;
	}
	mmin=INT_MAX;
	for(int i=1;i<=n;i++){
		mmin=min(c[i][1],mmin);
	}
	for(int i=1;i<=n;i++){
		a[i]=c[i][1]-mmin;
	}
	cout<<"Yes\n";
	int add=c[1][1]-a[1]-b[1];
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	cout<<'\n';
	for(int i=1;i<=n;i++){
		cout<<b[i]+add<<" ";
	}
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：0)

# AT_arc115_b [ARC115B] Plus Matrix题解
对于 $\forall 2\le i\le n,1\le j\le n$，有 $C_{i,j}-C_{i-1,j} = A_i-A_{i-1},C_{j,i}-C_{j,i-1} = B_i-B_{i-1}$，所以如果有解，则 $C$ 数组每行的差分数组应相同，每列的差分数组应相同。最后注意元素 $\ge 0$ 就行了。

没看题引发的悲剧：本人没看见 $A,B$ 中的元素应 $\ge 0$，卡了好一会才调出来。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std ;
const int N = 5e2 + 5 ;
int n , c[N][N] , l[N] , h[N] , minh = LONG_LONG_MAX , minl = minh , maxh = INT_MIN , maxl = maxh ;
signed main()
{
    cin >> n ;
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = 1 ; j <= n ; j++)   cin >> c[i][j] ;
    }
    if(n == 1)
    {
        cout << "Yes\n0\n" << c[1][1] ;
        return 0 ;
    }
    for(int i = 2 ; i <= n ; i++)   l[i] = c[1][i] - c[1][i - 1] , h[i] = c[i][1] - c[i - 1][1] ;
    for(int i = 2 ; i <= n ; i++)
    {
        for(int j = 2 ; j <= n ; j++)
        {
            if(l[i] != c[j][i] - c[j][i - 1] || h[i] != c[i][j] - c[i - 1][j])
            {
                cout << "No" ;
                return 0 ;
            }
        }
    }
    h[1] = c[1][1] ;
    for(int i = 1 ; i <= n ; i++)   h[i] += h[i - 1] , minh = min(minh , h[i]) ;
    for(int i = 2 ; i <= n ; i++)   l[i] += l[i - 1] , minl = min(minl , l[i]) ;
    if(minh + minl < 0)
    {
        cout << "No" ;
        return 0 ;
    }
    cout << "Yes\n" ;
    if(minl < 0)
    {
        for(int i = 1 ; i <= n ; i++)   cout << h[i] - minh << ' ' ;
        cout << '\n' ;
        for(int i = 1 ; i <= n ; i++)   cout << l[i] + minh << ' ' ;
    }
    else
    {
        for(int i = 1 ; i <= n ; i++)   cout << h[i] << ' ' ;
        cout << '\n' ;
        for(int i = 1 ; i <= n ; i++)   cout << l[i] << ' ' ;
    }
    return 0 ;
}
```

---

## 作者：forever_nope (赞：0)

### 题意

给定矩阵 $C_{n \times n}$，求两个数列 $A_n,B_n$，使得 $C_{i,j}=A_i+B_j$。

### 分析

画出一个表格来：

|         |  2  |  1  |  3  |
|   :-:   | :-: | :-: | :-: |
|  **2**  |  4  |  3  |  5  |
|  **0**  |  2  |  1  |  3  |
|  **1**  |  3  |  2  |  4  |

可以看出来，对于任意一列 $j$，$C_{*,j}$ 都存在有 $B_j$ 的贡献。

那么我们可以贪心的考虑。如果有解的话，将每列的最小值作为 $B_j$。

也就是就是 $C_{*,j}$ 减去 $\min_{k=1}^n C_{k,j}$。

然后考虑 $A_i$ 是什么。

我们画出来现在的矩阵：

|         |  2  |  1  |  3  |
|   :-:   | :-: | :-: | :-: |
|  **2**  |  2  |  2  |  2  |
|  **0**  |  0  |  0  |  0  |
|  **1**  |  1  |  1  |  1  |

可以看出 $A_i$ 就是剩下的 $C_{i,*}$ 了。

### 无解判断

什么时候无解。有矛盾的时候无解。

看任意一列，都是 $A$ 这个数列。

如果 $A \neq A$ 那么就是无解。

翻译成人话就是每一列如果有不同的，就是无解。

### 总结思路

将每一列减去这一列的最小值。

减去的数作为 $B_j$。

然后剩下的数，如果每一列都不同的话，就是无解。

否则输出即可。

评测记录：<https://atcoder.jp/contests/arc115/submissions/49387103>

核心代码：

```cpp
#define rep(i, n) for (decltype(n) i = 0; i < n; ++i)
#define gor(i, l, r) for (decltype(r) i = l; i < r; ++i)
#define rr read()
int main() {
    int n = rr; vector<int> b(n, 1e9);
    vector<vector<int>> c(n, vector<int>(n));
    rep(i, n) rep(j, n) c[i][j] = rr, b[j] = min(b[j], c[i][j]);
    rep(i, n) rep(j, n) if ((c[i][j] -= b[j]) != c[i][0]) printf("No\n"), exit(0);
    printf("Yes\n");
    rep(i, n) printf("%d%c", c[i][0], " \n"[i == n - 1]);
    rep(i, n) printf("%d%c", b[i], " \n"[i == n - 1]);
    return 0;
}
```

### 易错点

输出别反了。


---

## 作者：xiongzecheng (赞：0)

### 题目分析：

不难发现，$C$ 矩阵中第 $i$ 行是由 $B$ 数组中的每一个数分别加上 $A$ 数组的第 $i$ 位。

由此可以得到初步结论：如果 $A$ 和 $B$ 数组存在，$C$ 矩阵每一行相邻两数的差组成的数列必须全部相同。

比如第二组样例，每一行相邻两数的差分别是：

$$
\begin{pmatrix}
  -1 & 2 \\
  0 & 1 \\
  -1 & 2 \\
\end{pmatrix}
$$

则第二行与其他两行不同，$A$ 和 $B$ 数组不存在。

同时，不考虑 $A$ 和 $B$ 中元素非负，我们可以找出一组 $A$ 和 $B$。例如：
$$A_i=C_{i,1}$$
$$B_i=C_{1,i}-C_{1,1}$$

接下来考虑 $A$ 和 $B$ 数组中元素能否全部非负。

我们发现，如果将 $A$ 数组中每个数加上常数 $D$，将 $B$ 数组中每个数减去常数 $D$，对产生的 $C$ 数组是不影响的。

令 $m_1$ 是 $A$ 数组中的最小元素，$m_2$ 是 $B$ 数组中的最小元素。

那么，将 $A$ 数组中每个数减去 $m_1$ 后，所得的数全部是非负的。这时 $B$ 数组中的每个数需要加上 $m_1$。此时只要 $m_2+m_1$ 是非负的，那么 $B$ 数组中的每一个元素必定是非负的。而如果 $m_2+m_1$ 是负数，那么一定无法构造出 $A$ 和 $B$ 数组使得其中所有元素非负。

于是，我们成功找出了判断是否有可行方案的方法，也能构造出一组可行的方案。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c[505][505];
vector<int>st,a,b;
int main(){
	scanf("%d",&n);
	for(int j=1;j<=n;j++){
		scanf("%d",&c[1][j]);
		if(j!=1)st.push_back(c[1][j]-c[1][j-1]);
		//记录第一行中相邻两数的差，方便之后比较。 
	}
	bool f=true;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&c[i][j]);
			if(j!=1&&c[i][j]-c[i][j-1]!=st[j-2])f=false;
			//只要有一个数与第一行记录结果不同，一定不存在a,b数组。 
		}
	if(!f){
		printf("No\n");
		return 0;
	}
	for(int i=1;i<=n;i++)a.push_back(c[i][1]);
	for(int i=1;i<=n;i++)b.push_back(c[1][i]-c[1][1]);
	//a和b数组的初始值 
	int min1=INT_MAX,min2=INT_MAX;
	for(int i=0;i<a.size();i++){
		min1=min(min1,a[i]);
		min2=min(min2,b[i]);
	}
	//记录两数组的最小值 
	if(min1+min2<0){
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	for(int i=0;i<a.size();i++)
		printf("%d ",a[i]-min1);
	printf("\n");
	for(int i=0;i<b.size();i++)
		printf("%d ",b[i]+min1);
	//输出答案 
	printf("\n");
	return 0;
}
```

---

## 作者：Laisira (赞：0)

### 题面
给一个 $n\times n$ 的矩阵 ${C}$，问是否存在序列 ${A},{B}$ 满足 $C_{i,j}=A_{i}+B_{j}$。

如果存在，输出 `Yes`，及 ${A},{B}$。否则输出 `No`。

### 思路
浅浅的写一下：

$$C_{i,j}=A_{i}+B_{j}$$
$$C_{i+1,j}=A_{i+1}+B_{j}$$
$$C_{i,j+1}=A_{i}+B_{j+1}$$
$$C_{i+1,j+1}=A_{i+1}+B_{j+1}=C_{i+1,j}+C_{i,j+1}-C_{i,j}$$

然后判断依据就出来了。

接着：

$$A_{i}-A_{i+1}=C_{i,j}-C_{i+1,j}$$

$B$ 同理，我们就可以把他们所有值的关系式就求出来了。

然后我们又发现要让 $0\leq A_{i}$ 而且可以二分 $A_1$ 的值。

于是就二分枚举，最后判一下大于等于 $0$ 就行了，随便一个快读 3ms 切了。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 505 
using namespace std;
int C[Maxn][Maxn];
int a[Maxn],b[Maxn];
int res[Maxn],n;
bool check(int x) {
    res[1]=x;
    for(int i=2;i<=n;i++) {
        res[i]=res[i-1]-a[i];
        if(res[i] < 0)return false;
    } return true;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>C[i][j];
    for(int i=2;i<=n;i++)
        for(int j=2;j<=n;j++)
            if(C[i][j]!=C[i-1][j]+C[i][j-1]-C[i-1][j-1])
                return cout<<"No",0;
    for(int i=2;i<=n;i++)
        a[i]=C[i-1][1]-C[i][1];
    for(int i=2;i<=n;i++)
        b[i]=C[1][i-1]-C[1][i];
    int l=0,r=C[1][1],mid,ans=-1;
    while(l <= r) {
        mid=(l+r)>>1;
        if(!check(mid))l=mid+1;
        else r=mid-1,ans=mid;
    } if(ans == -1)return cout<<"No",0;
    a[1]=ans; b[1]=C[1][1]-ans;
    for(int i=2;i<=n;i++) {
        a[i]=a[i-1]-a[i],b[i]=b[i-1]-b[i];
        if(b[i] < 0)return cout<<"No",0;
    } cout<<"Yes\n";
    for(int i=1;i<=n;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
    for(int i=1;i<=n;i++)
        cout<<b[i]<<" ";
    return 0;
}
```

---

