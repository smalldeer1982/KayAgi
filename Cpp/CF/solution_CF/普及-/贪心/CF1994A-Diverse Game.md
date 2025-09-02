# Diverse Game

## 题目描述

### 题目大意
给定一个 $n\times m$ 的矩阵 $a$，该矩阵的每个元素都是 $\left[1,n\cdot m\right]$ 内的整数且互不相同。请求出一个矩阵 $b$，满足：

- $b$ 的每个元素都是 $\left[1,n\cdot m\right]$ 内的整数且互不相同。
- $\forall 1\le i\le n,1\le j \le m:a_{i,j}\neq b_{i,j}$。

## 样例 #1

### 输入

```
5
1 1
1
2 1
2
1
1 5
2 4 5 3 1
2 4
1 2 3 4
5 6 7 8
3 3
4 2 1
9 8 3
6 7 5```

### 输出

```
-1
1 
2 
4 5 3 1 2 
6 7 8 5 
2 3 4 1 
8 3 9 
7 5 6 
2 1 4```

# 题解

## 作者：ELECTRODE_kaf (赞：5)

### 题意概要

给定一个 $n \times m$ 的由 $[1,n \times m]$ 填充的矩阵，构造一个同大小且同样由 $[1,n \times m]$ 填充的矩阵，使得每个位置上的数都与原矩阵不同。

### 思路

对于每个位置，给原数 $+1$，如果超出范围则填 $1$。

根据这个填法，只有当矩阵只有一个数时无解，特判就行。

### AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define srt short
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define ctn continue
int q,n,m;
srt a[11][11];
int main(){
	cin>>q;
	while(q--){
		cin>>n>>m;
		rep(i,1,n){
			rep(j,1,m)cin>>a[i][j];
		}
		if(n==1&&m==1){
			cout<<"-1\n";
			ctn;
		}
		rep(i,1,n){
			rep(j,1,m)cout<<(a[i][j]+1>n*m?1:a[i][j]+1)<<' ';
			cout<<'\n';
		}
	}
}
```

---

## 作者：flangeborg (赞：1)

#### [题目传送门](https://www.luogu.com.cn/problem/CF1994A)

## 解题思路

- 结合样例，并加以思考，不难得出当且仅当 $n = m = 1$ 时，没有合法的矩阵 $b$。
- 对于其他的 $n$ 与 $m$ 我们都可以使用同一种方法去构造一个合法的矩阵 $b$。对于矩阵 $a$ 中的任意位置 $a_{i,j}$，将在矩阵 $b$ 中的对应位置 $b_{i,j}$ 的值设定为 $a_{i,j} - 1$，若 $a_{i,j} = 1$,则将值设定为 $n \times m$。以上述方法生成的矩阵 $b$ 即是答案。

### CODE

```cpp
#include<iostream>
#define int long long
using namespace std;
int T,n,m;
int a[15][15];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> T;
	while(T--)
	{
		cin >> n >> m;
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= m; j++)
				cin >> a[i][j];
		if(n == 1 && m == 1) cout << "-1" << endl;
		else
		{
			for(int i = 1; i <= n; i++)
			{
				for(int j = 1; j <= m; j++)
				{
					if(a[i][j] == 1) cout << n * m << " ";
					else cout << a[i][j] - 1 << " ";
				}
				cout << endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：GreenMelon (赞：0)

在 $n\times m$ 不等于 $1$ 的情况下，$a_{i,j}$ 取模 $n\times m$ 再加上 $1$ 一定不等于 $a_{i,j}$。根据这个规律，即可写出代码。


```cpp
#include<bits/stdc++.h>
using namespace std; 
int main(){
	int t;
	cin>>t;
	while(t--){
		int n, m;
		cin>>n>>m;
		int a[15][15];
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>a[i][j];
			}
		}
		if(n*m==1){
			cout<<-1<<endl;
			continue;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cout<<a[i][j]%(n*m)+1<<" ";
			}
			cout<<endl;
		}
	}
	return 0; 
} 
```

---

## 作者：ManGo_Mouse (赞：0)

更新：修正了在题解页面查看题解，部分 KaTex 无法正常显示的问题（专栏可正常查看），和改进了部分语言描述。

### $\tt Solving\ Ideas$
可以想到将第 $i$ 列的数字全部移动至第 $i + 1$ 列（第 $n$ 列移动至第 $1$ 列）。

注意需要处理特殊情况：
+ $n = 1, m = 1$，此时无解。
+ $m = 1$，此时无法移动列，改为移动行即可（即第 $i$ 行的移动至 $i + 1$ 行，而第 $n$ 行则移动至第 $1$ 行）。

### $\tt Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e1 + 20;
int T, n, m, a[N][N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while (T --) {
        cin >> n >> m;
        for (int i = 1; i <= n; i ++)
            for (int j = 1; j <= m; j ++)
                cin >> a[i][j];
        if (n == 1 && m == 1)
            cout << -1 << '\n';
        else if (m == 1) {
            for (int i = 2; i <= n; i ++)
                cout << a[i][1] << '\n';
            cout << a[1][1] << '\n';
        }
        else {
            for (int i = 1; i <= n; i ++) {
                for (int j = 2; j <= m; j ++)
                    cout << a[i][j] << " ";
                cout << a[i][1] << '\n';
            }
        }
    }
    return 0;
}
```

---

## 作者：WAis_WonderfulAnswer (赞：0)

其实就是一道简单的贪心。

首先 $a$ 的每个元素不相同，又要让 $b$ 的每个位置都跟 $a$ 不同。我们可以让 $a$ 的每个元素在 $b$ 中对应位置等于 $a$ 中这个元素右边的元素，即对于 $1 \le i \le n$，$1 \le j < m$，$b [ i ] [ j ] = a [ i ] [ j + 1 ]$。

但要注意的是，当 $j = m$ 时，$b [ i ] [ j ] = a [ i + 1 ] [ 1 ]$，当 $i = n$ 并且 $j = m$ 时，$b [ i ] [ j ] = a [ 1 ] [ 1 ]$。

特判：当 $n$，$m$ 都为 $1$ 时，则无解。

这样一来 $b$ 数组中的数就与 $a$ 数组中的数各不相同了。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int _,a[15][15],b[15][15];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>_;
	while (_--)
	{
		int n,m;
		cin>>n>>m;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
			{
				cin>>a[i][j];
			}
		}
		if (n==1&&m==1) //无解 
		{
			cout<<-1<<'\n';
			continue;
		}
		memset(b,0,sizeof(b));
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
			{
				if (i==n&&j==m) continue;
				if (j==m)
				{
					b[i][j]=a[i+1][1];
				}
				else
				{
					b[i][j]=a[i][j+1];
				}
			}
		}
		b[n][m]=a[1][1];
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
			{
				cout<<b[i][j]<<" ";
			}
			cout<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：zsh_haha (赞：0)

### 题目大意

给定一个 $n$ 行 $m$ 列二维数组 $a$，其中的每一个数字 $a_{i,j}\in[1,nm](1\le i\le n,1\le j\le m)$ 且互不相同。

要你构造一个 $n$ 行 $m$ 列二维数组 $b$，要求任意一个 $b_{i,j}\neq a_{i,j}(1\le i\le n,1\le j\le m)$。

### 解题思路

若 $n=m=1$，那么无论怎么变，都无法满足要求，直接输出 `-1`。

若 $n=1$ 且 $m>1$，因为每一个 $a_{i,j}(1\le i\le n,1\le j\le m)$ 都互不相同，所以 $a_{i,j}\neq a_{i,j+1},a_{i,m}\neq a_{i,1}(1\le i\le n,1\le j<m)$。

我们可以使 $b_{i,j}=a_{i,j+1},b_{i,m}=a_{i,1}(1\le i\le n,1\le j<m)$。

若 $n,m>1$，因为每一个 $a_{i,j}(1\le i\le n,1\le j\le m)$ 都互不相同，所以 $a_{i,j}\neq a_{i+1,j},a_{n,j}\neq a_{1,j}(1\le i<n,1\le j\le m)$。

我们可以使 $b_{i,j}=a_{i+1,j},b_{n,j}=a_{i,j}(1\le i<n,1\le j\le m)$。

### AC 代码

综上所述，代码如下。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int m,n; 
int a[11][11];
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		if(n==1&&m==1){//不可能满足要求 
			cout<<"-1\n";//直接输出 -1 跳过 
			continue;
		}
		if(n==1){//只有一行 
			for(int i=2;i<=m;i++){//右移一位输出 
				cout<<a[1][i]<<' ';
			}
			cout<<a[1][1]<<endl;
		}else{
			for(int i=2;i<=n;i++){//上移一位输出 
				for(int j=1;j<=m;j++){
					cout<<a[i][j]<<' ';
				}
				cout<<endl;
			}
			for(int i=1;i<=m;i++){
				cout<<a[1][i]<<' ';
			}
			cout<<endl;
		}
	}
    return 0;
}
```

---

## 作者：linjinkun (赞：0)

很简单的一道模拟题，感觉可以降到红题。

### 思路
由于题目保证 $a$ 互不相同，那么这道题就非常简单了，为了避免一些奇奇葩葩的问题，每次输出 $b_{i,j}$ 这个位置时，直接输出 $a_{i+1,j+1}$ 就行了。
### 细节
- 如果 $i+1$ 超过了 $n$，那么当前下标为 $1$。
- 如果 $n \times m = 1$，说明只有一个数，不可行，输出 $-1$。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 15;
int a[N][N];
signed main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		scanf("%d %d",&n,&m);
		for(int i = 1;i<=n;i++)
		{
			for(int j = 1;j<=m;j++)
			{
				scanf("%d",&a[i][j]);
			}
		}
		if(n*m == 1)
		{
			printf("-1\n");
			continue;
		}
		for(int i = 1;i<=n;i++)
		{
			for(int j = 1;j<=m;j++)
			{
				printf("%d ",a[(i+1)%n == 0?n:(i+1)%n][(j+1)%m == 0?m:(j+1)%m]);
			}
			printf("\n");
		}
	} 
	return 0;
}
```

---

## 作者：M1KuM3yusQAQ (赞：0)

### 题意

题目设有 $T$ 组测试数据。对于每组测试数据，给定一个 $n \times m$ 的矩阵 $a$，矩阵中的每个数字 $a_{i, j}$ 满足 $1 \le a_{i, j} \le n \times m$ 且各不相同，问是否存在矩阵 $b$ 使矩阵 $b$ 中的任何一个数字 $b_{i, j} \not = a_{i, j}$。如果有输出矩阵 $b$，如果没有输出 $-1$。

### 分析

很显然对于任何 $n \times m > 1$ 的矩阵都存在符合条件的矩阵 $b$。

那么对于存在符合条件的矩阵 $b$ 的询问，如何控制两个矩阵对应位置的数字各不相同？

我们可以控制矩阵 $a$ 每行上的数字向右移一格，并将该行最后一个数字移至第一格形成矩阵 $b$，由于数字各不相同，可以所有数字不与原矩阵对应位置的数字相同。

需要注意的是，有的矩阵列数为 $1$，如果按照上述方法操作会导致输出与原矩阵相同。所以我们需要在每次询问后特判列数是否为 $1$。如果是，按照上述方法控制该列上的每个数字向下移一格，并将该列最后一个数字移至第一格即可。

当然，当 $n = 1$ 且 $m = 1$ 时，程序输出 $-1$。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

int T;
int n, m;
int xmap[15][15];

int main() {
	ios::sync_with_stdio(false);
	cin >> T;

	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> xmap[i][j];
			}
		}

		if (n == 1 && m == 1)
			cout << -1 << endl;
		else {
			if (m == 1) {
				for (int j = 1; j <= n; j++) {
					int tmp = j + 1;
					if (tmp == n + 1)
						tmp = 1;
					cout << xmap[tmp][1] << endl;
				}
			} else {
				for (int j = 1; j <= n; j++) {
					for (int k = 1; k <= m; k++) {
						int tmp = k + 1;
						if (tmp == m + 1)
							tmp = 1;
						cout << xmap[j][tmp] << " ";
					}
					cout << endl;
				}
			}
		}
	}


	return 0;
}

```

希望能帮到各位，请多指教！orz

---

## 作者：cfkk (赞：0)

思路：将每一行的数都向后移一位，如果是最后一列就移到第一列。

注意：
- 当 $n=m=1$ 时，无解。
- 当 $m=1$ 时，要将每一列的数都向下移一位，如果是最后一行就一移到第一行。

代码如下：

```cpp
#define maxn 11
int mp[maxn][maxn];
signed main()
{
    int T=read();
    while(T--)
    {
        int n=read(),m=read();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)mp[i][j]=read();
        if(n==1&&m==1){puts("-1");continue;}
        if(m==1)
        {
            print(mp[n][1]);pc(1);
            for(int i=1;i<n;i++)print(mp[i][1]),pc(1);
            continue;
        }
        for(int i=1;i<=n;i++)
        {
            print(mp[i][m]);pc(2);
            for(int j=1;j<m;j++)print(mp[i][j]),pc(2);
            pc(1);
        }
    }
    return 0;
}
```

---

## 作者：__XU__ (赞：0)

# CF1994A 题解

### 题意

给定一个数组 $a$ 让我们操作这个数组使它变成数组 $b$，对于任何位置 $i,j$ 保证 $a_{i,j}\neq b_{i,j}$ 若无解，输出 $-1$。

### 做法

首先判断输出 $-1$ 的情况，很显然，当 $n=m=1$ 时无论如何改变 $a_{1,1}$ 始终等于 $b_{1,1}$。

然后判断 $n,m$ 其中一方为 $1$ 的情况，思考如何将数组 $a$ 里的数重新组合使得 $b$ 数组与原数组 $a$ 不想同，显然的，倒序输出即可。(似乎不用判断也可以)。

最后就是 $n\neq 1,m\neq1$ 的情况，就普通的让每行的顺序倒过来，将每列的顺序也到过来即可。

### 值得注意

当 $n$ 或者 $m$ 是奇数的时候，无论怎么倒转，第 $\large\frac{1+m \text{ or } n}{2}$ 是不会变的，那么就暴力的将 $b_{(1+m \text{ or } n)\div 2}$ 变成 $b_1$ 即可，这里也是这道题的坑点。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
void solve(){
	int n,m;
	cin>>n>>m;
	vector<vector<int>> a(n+5,vector<int>(m+5,0));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	if(n==1&&m==1){
		cout<<-1<<'\n';
	}
	else if(n==1&&m!=1){
		int mid=((1+m)/2);
		int f=0;
		if(m%2==1){
			f=1;
		}
		for(int i=m;i;i--){
			if(i==1&&f==1){
				cout<<a[1][mid]<<' ';
				continue;
			}
			if(i==mid&&f==1){
				cout<<a[1][1]<<' ';
				continue;
			}
			cout<<a[1][i]<<' ';
		}
		
		cout<<'\n';
	}
	else if(n!=1&&m==1){
		int mid=((1+n)/2);
		int f=0;
		if(n%2==1){
			f=1;
		}
		for(int i=n;i;i--){
			if(i==1&&f==1){
				cout<<a[mid][1]<<'\n';
				continue;
			}
			if(i==mid&&f==1){
				cout<<a[1][1]<<'\n';
				continue;
			}
			cout<<a[i][1]<<'\n';
		}
	}
	else{
		for(int i=n;i;i--){
			for(int j=m;j;j--){
				if(j==1&&m%2==1){
					cout<<a[i][(1+m)/2]<<' ';
					continue;
				}
				if(j==(1+m)/2&&m%2==1){
					cout<<a[i][1]<<' ';
					continue;
				}
				cout<<a[i][j]<<' ';
			}
			cout<<'\n';
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

谢谢观看。

---

## 作者：Furina_Saikou (赞：0)

# 题意

给定一个 $n$ 行 $m$ 列的矩阵，矩阵内元素不重复，要求打乱序列并且任何一个位置不能和原数组重复。

# 思路

很显然 $n,m$ 都为 $1$ 的时候无解。

对于有解的情况，我们考虑每行独立打乱，将每一行平分为两段，从左往右遍历两段，同时交换对应位置的数，如果 $m$ 是奇数，还得交换第 $1$ 个和第 $m$ 个保证最后一个的位置能被考虑到。

需要注意的是，如果 $m$ 为 $1$ 就要改成按列打乱否则按行打乱有误。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114;
int t,n,m,a[N][N];
signed main()
{
//	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cin>>a[i][j];
			}
		}
		if(n==1&&m==1)
		{
			cout<<"-1\n";
			continue;
		}else if(m==1)
		{
			int mid=n/2+1;
			for(int i=1;i<mid;i++)
			{
				swap(a[i+mid-1][1],a[i][1]);
			}
			if(n&1)swap(a[1][1],a[n][1]);
		}else
		{
			for(int i=1;i<=n;i++)
			{
				int mid=m/2+1;
				for(int j=1;j+mid-1<=m&&j<mid;j++)
				{
					swap(a[i][j],a[i][j+mid-1]);
				}
				if(m&1)swap(a[i][1],a[i][m]);
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cout<<a[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
	return 0;
}
```

---

