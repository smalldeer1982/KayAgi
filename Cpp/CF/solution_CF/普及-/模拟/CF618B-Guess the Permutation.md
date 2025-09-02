# Guess the Permutation

## 题目描述

Bob has a permutation of integers from $ 1 $ to $ n $ . Denote this permutation as $ p $ . The $ i $ -th element of $ p $ will be denoted as $ p_{i} $ . For all pairs of distinct integers $ i,j $ between $ 1 $ and $ n $ , he wrote the number $ a_{i,j}=min(p_{i},p_{j}) $ . He writes $ a_{i,i}=0 $ for all integer $ i $ from $ 1 $ to $ n $ .

Bob gave you all the values of $ a_{i,j} $ that he wrote down. Your job is to reconstruct any permutation that could have generated these values. The input will be formed so that it is guaranteed that there is at least one solution that is consistent with the information given.

## 说明/提示

In the first case, the answer can be $ {1,2} $ or $ {2,1} $ .

In the second case, another possible answer is $ {2,4,5,1,3} $ .

## 样例 #1

### 输入

```
2
0 1
1 0
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
5
0 2 2 1 2
2 0 4 1 3
2 4 0 1 3
1 1 1 0 1
2 3 3 1 0
```

### 输出

```
2 5 4 1 3
```

# 题解

## 作者：lflby (赞：1)

# 思路

对于每一个 $p_i$ 搜一遍 $f_{i,j}$ 和 $f_{j,i} (1 \le i \le n)$ 选最大值。

如果这个数选过则往后找第一个没有被选过的数。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[55][55];
bool b[55];
int main()
{
	cin>>n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin>>a[i][j];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		int s = -2e9;
		for (int j = 1; j <= n; j++)
		{
			s = max(s,a[i][j]);
		}
		for (int j = 1; j <= n; j++)
		{
			s = max(s,a[j][i]);
		}
		while (b[s]) s++;
		cout<<s<<" ";
		b[s]=true; 
	}
	return 0;
 } 
```

---

## 作者：Halberd_Cease (赞：0)

由 $f_{i,j}=\min(p_i,p_j)$ 可得 $\max^n_{j=1}(f_{i,j})$ 是第 $i$ 个数的值（特殊的，最大的数的值是 $(\max^n_{j=1}(f_{i,j}))+1$）。

证明：

令第 $i$ 个数为 $ans_i$；

在第 $i$ 行数中，由于 $f_{i,j}=\min(p_i,p_j)$ 的限制，所有数都会小于或等于 $ans_i$；

如果这个数不是最大数，那么始终会有一个比它大的数与其比较，所以 $ans_i=\max^n_{j=1}(f_{i,j})$；

如果是最大数，那么只有比它小 $1$ 的数与它比较成为最大值。

因为本题有多解，输出一个即可，所以不用特殊讨论，注意不要输出两个最大值即可。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
	int x[60];
	int maxn=0;
	int id;
	int val;
}a[60];
bool cmp1(Node x,Node y)
{
	return x.maxn<y.maxn;
 } 
bool cmp2(Node x,Node y)
{
	return x.id<y.id;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		a[i].id=i;
		int maxn=0;
		for(int j=1;j<=n;j++)
		{
			cin>>a[i].x[j];
			maxn=max(maxn,a[i].x[j]);
		}
		a[i].maxn=maxn;
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++)
	{
		a[i].val=i;
	}
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++)
	{
		cout<<a[i].val<<' ';
	}
}
```

---

## 作者：yangzd (赞：0)

# 题目大意

有一个 $1$ 至 $n$ 的排列 $p$，但却不知它的具体内容.现有一 $n\times n$ 的矩阵 $f$，$f_{i,j}=min(p_{i},p_{j})$。特别的，$f_{i,i}=0$。现请你根据矩阵 $f$ 求出一组合法的排列.

# 分析

这么考虑，首先 $1$ 与其他比较肯定 $1$ 是最小的，那一行肯定除了对角线的 $0$，其他全是 $1$。这样，找到 $1$ 的位置。接下来，把矩阵中所有 $1$ 变成 $2$，找到的那一行标记为“占用”，然后去找“非占用”的行中除了 $0$ 全是 $2$ 的那一行，确定 $2$ 的位置，以此类推。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n;
long long a[55][55],ans[55];
bool v[55];

signed main()
{
	ios::sync_with_stdio(0);
	
	cin >> n;
	
	for(long long i=1; i<=n; i++)
		for(long long j=1; j<=n; j++)
			cin >> a[i][j];
		
	for(long long k=1; k<=n; k++)
	{
		for(long long i=1; i<=n; i++)
		{
			if(ans[i]==0)
			{
				long long ji=0;
				
				for(long long j=1; j<=n; j++)
					if(a[i][j]==k)
						ji++;
					
				if(ji==n-1)
				{
					ans[i]=k;
					
					break;
				}
			}
		}
		
		for(long long i=1; i<=n; i++)
			for(long long j=1; j<=n; j++)
				if(a[i][j]==k)
					a[i][j]=k+1;
	}
	
	for(long long i=1; i<n; i++)
		cout << ans[i] << " ";
		
	cout << ans[n] << endl;
	
	return 0;
}
```

---

## 作者：Saber_Master (赞：0)

B. [Guess the Permutation](https://www.luogu.com.cn/problem/CF618B)

其实很简单，第$i$行出现次数大于$1$的数就是$p_i$，根据$f$矩阵的定义这个显然成立.所以我们只需预处理出每行大于$1$的数并且填进去.剩下的空位随便用一个没有用过的数补上就可以了.

```cpp
const ll N=5e2+2;

ll n;

ll a[N], cnt[N], res[N];
bool used[N];
int main(){
	read(n);
	for (R ll i=1; i<=n; i++){
		memset(cnt, 0, sizeof cnt);
		for (R ll j=1; j<=n; j++){
			read(a[j]);
			++cnt[a[j]];
			if (cnt[a[j]]>1) res[i]=a[j], used[a[j]]=true;
		}
	}
	for (R ll i=1; i<=n; i++){
		if (!res[i]){
			for (R ll j=1; j<=n && !res[i]; j++) if (!used[j]) res[i]=j, used[j]=true;
		}
	}
	for (R ll i=1; i<=n; i++) writesp(res[i]); putchar('\n');
}
```

---

