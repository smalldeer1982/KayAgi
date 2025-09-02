# No Prime Differences

## 题目描述

You are given integers $ n $ and $ m $ . Fill an $ n $ by $ m $ grid with the integers $ 1 $ through $ n\cdot m $ , in such a way that for any two adjacent cells in the grid, the absolute difference of the values in those cells is not a prime number. Two cells in the grid are considered adjacent if they share a side.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1838C/8c9e5187d31f46fda0ceb06874a7a38c27ed3eed.png)It can be shown that under the given constraints, there is always a solution.

## 说明/提示

The first sample case corresponds to the picture above. The only absolute differences between adjacent elements in this grid are $ 1 $ , $ 4 $ , $ 6 $ , $ 8 $ , and $ 9 $ , none of which are prime.

## 样例 #1

### 输入

```
3
4 4
5 7
6 4```

### 输出

```
16  7  1  9
12  8  2  3
13  4 10 11
14  5  6 15

29 23 17  9  5  6  2
33 27 21 15 11  7  1
32 31 25 19 20 16 10
26 30 24 18 14  8  4
35 34 28 22 13 12  3

 2  3  7 11
 8  9  1 10
17 13  5  4
18 14  6 12
19 23 15 21
20 24 16 22```

# 题解

## 作者：lovely_codecat (赞：4)

其实代码还是需要的……

~~纪念我因为看不懂第二篇题解又写不出来第一篇题解的代码而耗费的一个早上~~

思路：

# 1:思路初现

我们发现，$1$ 不是质数，所以我们可以构造出如下图的矩阵：
$$
\begin{bmatrix}
  1&  2&  3& 4\\
  5&  6&  7& 8\\
  9& 10& 11& 12 \\
  13&  14&  15&16
\end{bmatrix}
$$
但是这样，纵向差是 $m$，如果 $m$ 是质数，那就……寄得不能再寄了……

# 2:思路发展

我们发现，如果纵向差是 $2 \times m$，那么就没有以上问题了，于是我们就可以：
$$
\begin{bmatrix}
  1&  2&  3& 4 &5\\
  11&  12&  13& 14 &15\\
  6& 7& 8& 9&10 \\
  16&  17&  18&19&20  \\
\end{bmatrix}
$$
简单粗暴的把矩阵的奇数行和偶数行分别输出，就可以了。

# 3:细节修补

因为~~宇宙射线~~奇数行和偶数行之间的差的关系，要先输出偶数行。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1001][1001],t;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		int tot=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				a[i][j]=++tot;
			}
		}
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=m;j++){
				cout<<a[2*i][j]<<' ';
			}
			cout<<endl;
		}
		if(n&1){
			for(int i=1;i<=n/2+1;i++){
				for(int j=1;j<=m;j++){
					cout<<a[2*i-1][j]<<' ';
				}
				cout<<endl;
			}
		}
		else{
			for(int i=1;i<=n/2;i++){
				for(int j=1;j<=m;j++){
					cout<<a[2*i-1][j]<<' ';
				}
				cout<<endl;
			}	
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：copper_ingot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1838C)

首先，显然 $1$ 不是质数，所以我们可以构造一个横向差为 $1$ 的矩阵（以下是 $n = 4,m = 5$ 的情况）：

$$\begin{bmatrix} 1 & 2 & 3 & 4 & 5 \\ 6 & 7 & 8 & 9 & 10 \\ 11 & 12 & 13 & 14 & 15 \\ 16 & 17 & 18 & 19 & 20\end{bmatrix}$$

这样的矩阵纵向差是 $m$，当 $m$ 是质数的时候就挂了。

不过我们可以改进一下，把原本矩阵的奇数行提到前面，偶数行放到后面，让纵向差变成 $2m$，就像这样：

$$\begin{bmatrix} 1 & 2 & 3 & 4 & 5 \\ 11 & 12 & 13 & 14 & 15 \\ 6 & 7 & 8 & 9 & 10 \\ 16 & 17 & 18 & 19 & 20\end{bmatrix}$$

此时我们只需要考虑奇数行与偶数行之间的纵向差就可以了。

如果按照上面的方式构造的话，当 $n$ 为奇数时的差为 $m(n-2)$，$n$ 为偶数时差为 $m(n - 3)$。当 $n$ 是 $4$，$m$ 是质数时，差就会变成 $m$，是个质数，像上面的情况一样。

但是，如果我们把奇数行放到后面：

$$\begin{bmatrix}6 & 7 & 8 & 9 & 10 \\ 16 & 17 & 18 & 19 & 20 \\ 1 & 2 & 3 & 4 & 5 \\ 11 & 12 & 13 & 14 & 15\end{bmatrix}$$

当 $n$ 为奇数时差为 $m(n-2)$，$n$ 为偶数时差为 $m(n - 1)$。因为数据范围 $n \ge 4$，所以不会出现差变成 $m$ 的情况。

题讲完了，上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m;
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n / 2; i++){
			for (int j = 1; j <= m; j++) printf("%d ", (2 * i - 1) * m + j);
			puts("");
		}
		for (int i = 1; i <= (n + 1) / 2; i++){
			for (int j = 1; j <= m; j++) printf("%d ", (2 * i - 2) * m + j);
			puts("");
		}
		puts("");
	} 
    return 0;
}
```

---

## 作者：analysis (赞：1)

显然 $1$ 不是质数，除二外偶数不是质数。

然后分类讨论

对于 $m$ 为偶数，构造

$$
\begin{bmatrix}
    1 & 2 & 3 & \cdots & m \\
    m+1 & m+2 & m+3 & \cdots & 2m \\
    &&\cdot\\
    &&\cdot\\
    &&\cdot\\
    (n-1)m+1 & (n-1)m+2 & (n-1)m+3 & \cdots & nm \\
\end{bmatrix}
$$

则列增量为 $1$，行增量为 $m$。

对于 $n$ 为偶数，构造

$$
\begin{bmatrix}
    1 & n+1 & 2n+1 & \cdots & (m-1)n+1 \\
    2 & n+2 & 2n+2 & \cdots & (m-1)n+2 \\
    &&\cdot\\
    &&\cdot\\
    &&\cdot\\
    n & 2n & 3n & \cdots & nm \\
\end{bmatrix}
$$

则行增量为 $1$，列增量为 $n$。

对于 $n$、$m$ 均为奇数的情况，循环移位

$$
\begin{bmatrix}
    1 & 2 & 3 & \cdots & m-1 & m \\
    m+2 & m+3 & m+4 & \cdots & 2m & m+1 \\
    2m+3 & 2m+4 & 2m+5 & \cdots & 2m+1 & 2m+2 \\
    &&\cdot\\
    &&\cdot\\
    &&\cdot\\
\end{bmatrix}
$$

行增量为 $1$ 或 $m-1$，列增量为 $m+1$ 或 $1$。

无了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int T;
signed main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        if(m % 2 == 0)
        {
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=m;j++)
                {
                    cout<<((i-1)*m+j)<<" ";
                }
                cout<<'\n';
            }
        }
        else if(n % 2 == 0)
        {
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=m;j++)
                {
                    cout<<(i + (j-1) * n)<< " ";
                }
                cout<<'\n';
            }
        }
        else
        {
            for(int i=1;i<=n;i++)
            {
                int op = (i-1) % m + 1;
                for(int j=op;j<=m;j++)
                {
                    cout<<((i-1) * m + j)<<" ";
                }
                for(int j=1;j<op;j++)
                {
                    cout<<((i-1) * m + j)<<" ";
                }
                cout<<'\n';
            }
        }
        cout<<'\n';
    }
}
```

---

## 作者：c20231020 (赞：1)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1838C)

[codeforces](https://codeforc.es/contest/1838/problem/C)

### 题目大意

给出两个整数 $n,m$，构造一个 $n$ 行 $m$ 列的矩阵，使矩阵中相邻两个数的差值均不为质数。“矩阵中相邻两个数”指在矩阵中数字所在方格有一条公共边的两个数。

多组数据。

$1 \le t \le 1000,4 \le n,m \le 1000,\sum nm \le 10^6$。

### 思路

~~小~~分类讨论一下：

+ $m$ 为偶数。

  可以构造形如以下形式的矩阵：
  
  $$
    \begin{bmatrix}
    1&2&\cdots&m-1&m\\
    m+1&m+2&\cdots&2m-1&2m\\
    \vdots&\vdots&\ddots&\vdots&\vdots\\
    nm-m&nm-m+1&\cdots&nm-1&nm
    \end{bmatrix}
  $$
  
  每一对横向的相邻的数之差为 $1$，纵向为 $m$（是不为 $2$ 的偶数），符合题意。
  
+ $n$ 为偶数。

  大致把上一种情况按从左上到右下的对角线镜像一下即可，如下：
  
  $$
    \begin{bmatrix}
    1&n+1&\cdots&nm-n\\
    2&n+2&\cdots&nm-n+1\\
    \vdots&\vdots&\ddots&\vdots\\
    n-1&2n-1&\cdots&nm-1\\
    n&2n&\cdots&nm
    \end{bmatrix}
  $$
  
  分析类似。
  
+ $n,m$ 均为奇数。

  如果用上述方法构造，纵向差就不一定不为质数了（因为是奇数）。
  
  那么可以将上述矩阵的第 $i$ 行的位置循环向左移 $i-1$ 位，使纵向差仍不为质数。如下：
  
  $$
    \begin{bmatrix}
    1&2&3&\cdots&m-1&m\\
    m+2&m+3&m+4&\cdots&2m&m+1\\
    2m+3&2m+4&2m+5&\cdots&2m+1&2m+2\\
    \vdots&\vdots&\vdots&\ddots&\vdots&\vdots\\
    nm&nm-m+1&nm-m+2&\cdots&nm-2&nm-1
    \end{bmatrix}
  $$
  
  每一行中相邻数字差要么是 $1$，要么是 $m-1$（同样是不为 $2$ 的偶数）。（于是 $n,m \ge 4$ 就是为了防止 $n=3,m=3$ 的 corner case 吧。）
  
  每一列中相邻数字差要么是 $m+1$（还是不为 $2$ 的偶数），要么是 $1$，都不是质数。
  
  综上，这个矩阵符合题意。
  
三种情况拼起来，做完了。时间复杂度 $O(\sum nm)$。
#### code

[cf link](https://codeforc.es/contest/1838/submission/208465316)

以下代码省略了缺省源。

```cpp
int n,m,a[1010][1010];
void solve(){
	cin>>n>>m;
	int t=0;
	if(n%2==0){//第二种情况
		For(i,1,m){
			For(j,1,n){
				a[j][i]=++t;
			}
		}
		For(i,1,n){
			For(j,1,m){
				cout<<a[i][j]<<' ';
			}
			cout<<'\n';
		}
	}else if(m%2==0){//第一种
		For(i,1,n){
			For(j,1,m){
				cout<<++t<<' ';
			}
			cout<<'\n';
		}
	}else{//第三种
		int now=m;//移动的结束位置
		For(i,1,n){
			for(int j=now%m+1;;j=j%m+1){//循环移动
				a[i][j]=++t;
				if(j==now)break;
			}
			now--;//结束位置向前移一格
		}
		For(i,1,n){
			For(j,1,m){
				cout<<a[i][j]<<' ';
			}
			cout<<'\n';
		}
	}
	return;
}
```

---

## 作者：mouseboy (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1838C)

## 题目大意
- 给定 $ n,m $。
- 构造出 $n \times m$ 的网格，填入 $1,2,3,...,n \times m$。
- 使得相邻的两个方格的差不是质数。

## 大致思路

1. 考虑到肯定不为质数的有（除 $2$ 外）所有的偶数和 $ 1 $。
1. 令 $a_{i,j} = (i - 1) \times  m + j$ 于是每两个之间的差为 $ 1 $。
1. 但是发现若 $m$ 为质数则上下两行之差为质数所以不符合题意。
1. 我们可以令行间距为 $ 2 $，就会使上下的差为 $ 2 \times m $ 从而符合题意。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int t, n, m;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n >> m;
    for (int i = 2; i <= n; i++, i++) {
      for (int j = 1; j <= m; j++) {
        cout << (i - 1) * m + j << " ";
      }
      cout << "\n";
    }
    for (int i = 1; i <= n; i++, i++) {
      for (int j = 1; j <= m; j++) {
        cout << (i - 1) * m + j << " ";
      }
      cout << "\n";
    }
    cout << "\n";
  }

  return 0;
}
```

---

