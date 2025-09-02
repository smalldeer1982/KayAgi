# OKEA

## 题目描述

People worry that computers will get too smart and take over the world, but the real problem is that they're too stupid and they've already taken over the world.

— Pedro Domingos



You work for a well-known department store that uses leading technologies and employs mechanistic work — that is, robots!

The department you work in sells $ n \cdot k $ items. The first item costs $ 1 $ dollar, the second item costs $ 2 $ dollars, and so on: $ i $ -th item costs $ i $ dollars. The items are situated on shelves. The items form a rectangular grid: there are $ n $ shelves in total, and each shelf contains exactly $ k $ items. We will denote by $ a_{i,j} $ the price of $ j $ -th item (counting from the left) on the $ i $ -th shelf, $ 1 \le i \le n, 1 \le j \le k $ .

Occasionally robots get curious and ponder on the following question: what is the mean price (arithmetic average) of items $ a_{i,l}, a_{i,l+1}, \ldots, a_{i,r} $ for some shelf $ i $ and indices $ l \le r $ ? Unfortunately, the old robots can only work with whole numbers. If the mean price turns out not to be an integer, they break down.

You care about robots' welfare. You want to arrange the items in such a way that the robots cannot theoretically break. Formally, you want to choose such a two-dimensional array $ a $ that:

- Every number from $ 1 $ to $ n \cdot k $ (inclusively) occurs exactly once.
- For each $ i, l, r $ , the mean price of items from $ l $ to $ r $ on $ i $ -th shelf is an integer.

Find out if such an arrangement is possible, and if it is, give any example of such arrangement.

## 样例 #1

### 输入

```
4
1 1
2 2
3 3
3 1```

### 输出

```
YES
1 
YES
1 3 
2 4 
NO
YES
1 
2 
3```

# 题解

## 作者：Yusani_huh (赞：4)

链接：[CF1634C OKEA](https://www.luogu.com.cn/problem/CF1634C)

题意：将 $1$ 到 $n\times k$ 的正整数排成 $n$ 行 $k$ 列，使得每一行 $k$ 个数所有子串的平均数都为整数。

## 题解

先大胆猜一下，要求这么苛刻的话合法的情况一定不多，经推导果然是这样。

要求所有子串的平均数都为整数，其实可以只看相邻两数。要求所有相邻两数平均数为整数，也就是要求它们奇偶性相同（两数之和能够被 $2$ 整除）。因此我们可以推导出，每一行的数都分别奇偶性相同。

但因为要填的数是连续正整数，奇偶数的数量之间最多只会相差 $1$，因此如果在 $k>1$ 的情况下 $n$ 不是偶数，就一定无法满足每一行的数都分别奇偶性相同的要求（此时需要的奇偶数数量差为 $k$）。而当 $k=1$ 的时候，或 $k>1$ 但 $n$ 是偶数的时候一定有解（后者为什么有解构造一下即可）。

那么来看如何构造。

当 $k=1$ 的时候，可以直接按顺序输出 $1$ 到 $n$。

而当 $k>1$ 时，由于要求每一行的数都分别奇偶性相同，所以把所有的奇数排成 $\frac{k}{2}$ 行，所有的偶数排成 $\frac{k}{2}$ 行。别忘了除了要求相邻两数平均数为整数，还要求连续任意个数平均数都为整数。而直接按顺序排恰好能够满足这个要求：

设连续 $b$ 个奇偶性相同的数，开头的数为 $a$，则平均数为：

$$\frac{\sum_{i=1}^{b}a+2(i-1)}{b}=\frac{ab+b(b-1)}{b}=a+b-1$$

可以证明其为整数。

综上，对输入分类讨论即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define INF 0x3f3f3f3f
int t,n,k;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		if(n%2&&k>1){
			puts("NO");
			continue;
		}
		else{
			puts("YES");
			if(k==1){
				for(int i=1;i<=n;++i)
					printf("%d\n",i);
			}
			else{
				int cnt=0;
				for(int i=1;i<=n*k;i+=2){
					printf("%d",i),cnt++;
					if(cnt==k) puts(""),cnt=0;
					else printf(" ");
				}
				for(int i=2;i<=n*k;i+=2){
					printf("%d",i),cnt++;
					if(cnt==k) puts(""),cnt=0;
					else printf(" ");
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：XiaoQuQu (赞：2)

首先分类讨论。

若 $k=1$，则显然可以，直接 `YES` 并第 $i$ 行输出 $i$ 即可。

若 $k\ne 1$，那么每行就不止一个。

- 每一行上的数肯定同为奇数或同为偶数。

证明特别容易。令数组 $a$ 表示这一行上的所有数，若 $a_i$ 为奇数，$a_{i-1}$ 为偶数，则 $\dfrac{a_i+a_{i-1}}{2}$ 肯定不为整数。

由上面那点可以知道，当 $k\ge 2$ 的时候，$n\bmod 2=1$ 必定不能成立，因为全为奇数的货架与全为偶数的货架数量不一样，则不满足要求货架上的数是 $1\sim n\times k$ 的排列。

当 $k\ge 2,n\bmod 2=0$ 的时候，绝对有解。即在第 $i$ 个货架上放置 $i,i+n,i+2\times n,\cdots,i+(k-1)\times n$，或轮流一个货架全为奇数、一个货架全为偶数这样放置。

考虑证明第二种放置方式。设序列的第一个数为 $x$，则第二个数为 $x+2$，第三个数为 $x+4$，第 $k$ 个数为 $x+2\times(k-1)$。则这 $k$ 个数的和很好算出来：$sum=\dfrac{(x+x+2\times(k-1))\times k}{2}=\dfrac{(2\times x+2\times(k-1))\times k}{2}=\dfrac{2\times k\times {(x+k-1)}}{2}=k\times (x+k-1$)。

很显然，由于有因子 $k$，即可以被 $k$ 整除。

更普遍的，设**任意一段**的第一个数为 $x$，长度为 $k$，上式也同样使用。所以即我们这种放置方法为正确的。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k;
int main(void){
    cin >> t;
    while (t--){
        cin >> n >> k;
        if (k == 1){
            cout << "YES" << endl;
            for (int i = 1; i <= n; ++i)  cout << i << endl;
        }
        else if (n & 1)  cout << "NO" << endl;
        else{
            cout << "YES" << endl;
            int x = 1, y = 2;
            for (int i = 1; i <= n; ++i){
                if (i & 1)
                    for (int j = 1; j <= k; ++j)
                    {
                        cout << x << ' ';
                        x += 2;
                    }
                else
                    for (int j = 1; j <= k; ++j)
                    {
                        cout << y << ' ';
                        y += 2;
                    }
                cout << endl;
            }
        }
    }
}
```

---

## 作者：czxQQQ (赞：0)

## 思路

首先这题要特判 $m=1$ 的情况，直接输出即可。

容易发现，如果 $n$ 是奇数是无解的。所以只需要考虑 $n$ 是偶数的情况，奇偶相间输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,sum,a[505][505];
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		if(m==1){
			cout<<"YES\n";
			for(int i=1;i<=n;i++) cout<<i<<"\n";
		}
		else if(n&1) cout<<"NO\n";
		else{
			cout<<"YES\n";
			sum=1;
			for(int j=1;j<=m;j++){
				for(int i=1;i<=n;i++){
					a[i][j]=sum;
					sum++;
				}
			}
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					cout<<a[i][j]<<" ";
				}
				cout<<"\n";
			}
		}
	}
	return 0;
}
```



---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1634C)

## 题目大意

你有一个 $n\times m$ 的网格，你需要将 $[1,n\times m]$ 内的所有整数不重不漏地填入网格中，使得对于每一行 $i$，都有对于所有的 $1\leqslant l,r\leqslant m$，都有 $(r-l+1)\mid\sum\limits_{j=1}^r a_{i,j}$ 成立。请给出一种填数方式，如果不存在满足要求的填数方式，输出 $NO$。
  
## 分析
先可以特判，如果 $k=1$ 的时候，输出 $\texttt{YES}$，然后打印 $1$ 到 $n$。要求每一行的数都分别奇偶性相同。

可以发现如果 $n$ 是奇数，很明显不可能。

如果是偶数，就直接奇数偶数间隔填入就可以了。

## 下面是通过代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int p[550][550];
		int n,m;
		cin>>n>>m;
		if(m==1)
		{
			cout<<"YES"<<endl;
			for (int i = 1; i <= n; i ++) 
			{
			cout<<i<<endl;
			}
		}
		else
		{
			if(n%2==1)
			{
				cout<<"NO"<<endl; 
			} 
			else
			{
				cout<<"YES"<<endl;
				int ans = 0;
                for (int j = 1; j <= m; j ++)
                {
                	for (int i = 1; i <= n; i ++)
                    {
                    	p[i][j] = ++ ans;
                    }
                }  
                for (int i = 1; i <= n; i ++) 
				{
                    for (int j = 1; j <= m; j ++)
					{
					cout<<p[i][j]<<" ";
					} 
					 cout<<endl;
                }
               
			}
		}
	}
} 
```


---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1634C)

# 题意

题意是说，让你用 $[1,nm]$ 这些数填满 $n \times m$ 的表格，使得对于每一行，任意区间的平均值为整数，求构造。

# 思路

先考虑单独一行，由题意可知，任意相邻两个数相加为偶数，也就是奇偶性相同。

考虑当 $m=1$ 的时候，肯定有解，就是输出 $n$ 行，每行一个数 $i$。

而 $m \ne 1$ 的时候，因为每行数字数量相同，所以 $n$ 应为偶数，即当 $n \bmod 2=1$ 时，无解。

那么当 $m \ne 1$ 且 $n \bmod 2=1$ 时，有解，解就是奇数排列，再偶数排列，依此输出即可。

---

## 作者：Buried_Dream (赞：0)

~~看了眼样例猜了个结论就切了~~

## Solution

不需要分类讨论的做法。

给定一个等差数列，序列的长度为 $l$ 的时候，等差数列的和一定能被 $l$ 整除。

直接构造一个等差数列矩阵，如果说合法就输出，不合法就输出 `NO`。

怎么构造，就是竖着 $1,2,3,4...$，然后一列一列填起来。

也就是 $a_{i,j} = (j - 1)\times n + i$。


写起来很好写，并且不用分类讨论。

```cpp
const int Maxn = 1e3 + 10;
int n, m, a[Maxn][Maxn], qzh[Maxn][Maxn];

void Main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			a[i][j] = (j - 1) * n + i;
			qzh[i][j] = qzh[i][j - 1] + a[i][j];
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(qzh[i][j] % j != 0) return (void) printf("NO\n");
		}
	}
	printf("YES\n");
	for(int i = 1; i <= n; i++, printf("\n")) for(int j = 1; j <= m; j++) printf("%d ", a[i][j]);
}
signed main() 	
{
	int T = read();
	while(T--) Main();
	return (0 - 0);
}
```

---

## 作者：ttq012 (赞：0)

数学题。

前置知识：

当我们给定一个等差数列，序列的长度为 $l$ 的时候，等差数列的和一定能被 $l$ 整除。

**sol**

需要分类讨论。

通过上面的公式，我们可以发现，对于该矩阵中的每一个序列，我们都只需要构造一个等差数列即可。

当 $m=1$ 的时候，我们直接输出 $1, 2, 3, \ldots, n$ 即可。很明显是等差数列。

当 $m\ge 2$ 的时候，我们还需要继续分类讨论。

在上面条件满足的前提之下，当 $n\bmod 2=1$ 的时候，我们是很明显地无法构造出来 $n$ 个等差数列，输出 `NO`。

否则，我们可以构造出来下面的矩阵，这个矩阵是满足每一行都是等差数列的。

$$
\begin{aligned}
\begin{matrix}
& 1 & m+1 & 2\times m+1 & \cdots & (n-1)\times m + 1\\
& 2 & m+2 & 2\times m+2 & \cdots & (n-1)\times m + 2\\
& \vdots & \vdots  & \vdots & \vdots & \vdots\\
& m & 2\times m & 3\times m & \cdots & n \times m
\end{matrix}
\end{aligned}
$$

打印上述的矩阵即可。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 510;
int mp[N][N];

signed main() {
    int t;
    cin >> t;
    while (t --) {
        int n, m;
        scanf ("%d%d", &n, &m);
        if (m >= 2) {
            if (n & 1) puts("NO");
            else {
                puts("YES");
                int cnt = 0;
                for (int j = 1; j <= m; j ++)
                    for (int i = 1; i <= n; i ++)
                        mp[i][j] = ++ cnt;
                for (int i = 1; i <= n; i ++) {
                    for (int j = 1; j <= m; j ++) printf ("%d ", mp[i][j]);
                    puts("");
                }
            }
        } else if (m == 1) {
            puts("YES");
            for (int i = 1; i <= n; i ++) printf ("%d\n", i);
        } else {
            puts("NO");
        }
    }
    return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 题意

有一个 $n$ 行 $k$ 列的矩阵 $a$。现在，你要填进小于等于 $n\times k$ 的所有正整数，每个数必须且只能填 $1$ 次。

是否存在一种方式，使得对于所有的 $i,l,r(1\le i\le n,1\le l\le r\le k)$，都有 $\dfrac{\sum^{r}_{j=l}a[i][j]}{r-l+1}$ 为整数（即它们的平均数为整数）。如果存在，请输出任意一种方式。

### 2 思路

我们可以先进行特判：如果 $k=1$，必定有，即将 $1$ 到 $n$ 直接输出。

然后我们发现，一行里必定全是奇数或全是偶数，否则相邻的奇偶性不同的数的平均数必定不是整数。

所以，只要 $n\operatorname{mod}2=1$ 且 $k>1$，直接判否。因为这样不可能存在解。

然后我们可以证明，其它情况必定有解。可以这样填：

将 $n\times k$ 分为奇数一组偶数一组，分别排序。

然后按顺序给所有 $i\operatorname{mod}2=1$ 的 $i$ 填上奇数，按顺序给所有 $i\operatorname{mod}2=0$ 的 $i$ 填上偶数。比如，当 $n=4$，$k=3$ 时：

$$a=\begin{bmatrix}1&3&5\\2&4&6\\7&9&11\\8&10&12\end{bmatrix}$$

可以证明：

$$\dfrac{\sum^{r}_{j=l}a[i][j]}{r-l+1}=\dfrac{(a[i][l]+a[i][r])}{2}$$

即为整数。

### 3 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
int n;
int k;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1634C_1.in","r",stdin);
	freopen("CF1634C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		if(k==1){
			printf("YES\n");
			for(int i=1;i<=n;++i){
				printf("%d\n",i);
			}
			continue;
		}
		if(n&1){
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		for(int i=1,x;i<=n;++i){
			if(i&1){
				x=(i-1)*k;
				for(int j=1;j<=k;++j){
					printf("%d ",x+(j<<1)-1);
				}
			}
			else{
				x=(i-2)*k;
				for(int j=1;j<=k;++j){
					printf("%d ",x+(j<<1));
				}
			}
			printf("\n");
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/68887615)

### 4 说明

在比赛时，@[dengzijun](/user/387836) 给我提供了一种新的方式：按照列优先顺序依次填入 $n\times k$。很明显，这比我的代码更简单。

并且，无论何种填法，**填完后**改变行的顺序（注意不能改变行内元素顺序）都是可以的。

By **dengziyue**

---

