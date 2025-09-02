# Unusual Product

## 题目描述

Little Chris is a huge fan of linear algebra. This time he has been given a homework about the unusual square of a square matrix.

The dot product of two integer number vectors $ x $ and $ y $ of size $ n $ is the sum of the products of the corresponding components of the vectors. The unusual square of an $ n×n $ square matrix $ A $ is defined as the sum of $ n $ dot products. The $ i $ -th of them is the dot product of the $ i $ -th row vector and the $ i $ -th column vector in the matrix $ A $ .

Fortunately for Chris, he has to work only in $ GF(2) $ ! This means that all operations (addition, multiplication) are calculated modulo 2. In fact, the matrix $ A $ is binary: each element of $ A $ is either 0 or 1. For example, consider the following matrix $ A $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF405C/097f29d1003281620afd851d4fbf370e4162e70a.png)The unusual square of $ A $ is equal to $ (1·1+1·0+1·1)+(0·1+1·1+1·0)+(1·1+0·1+0·0)=0+1+1=0 $ .

However, there is much more to the homework. Chris has to process $ q $ queries; each query can be one of the following:

1. given a row index $ i $ , flip all the values in the $ i $ -th row in $ A $ ;
2. given a column index $ i $ , flip all the values in the $ i $ -th column in $ A $ ;
3. find the unusual square of $ A $ .

To flip a bit value $ w $ means to change it to $ 1-w $ , i.e., 1 changes to 0 and 0 changes to 1.

Given the initial matrix $ A $ , output the answers for each query of the third type! Can you solve Chris's homework?

## 样例 #1

### 输入

```
3
1 1 1
0 1 1
1 0 0
12
3
2 3
3
2 2
2 2
1 3
3
3
1 2
2 1
1 1
3
```

### 输出

```
01001
```

# 题解

## 作者：ny_Dacong (赞：0)

# 思路

当第 $i$ 行与第 $i$ 列相乘的时候，这一次相乘的第 $j$ 对数是 $A_{i,j}$ 和 $A_{j,i}$。

当第 $j$ 行与第 $j$ 列相乘的时候，这一次相乘的第 $i$ 对数是 $A_{j,i}$ 和 $A_{i,j}$。

因为它们的乘积要么是 $0$，要么是 $1$。而 $A_{i,j} \times A_{j,i} = A_{j,i} \times A_{i,j}$。所以当 $i \not = j$ 时，$A_{i,j} \times A_{j,i}+ A_{j,i} \times A_{i,j} = 0$，也就是说它们对答案没有贡献。因此当 $i \not = j$ 时，它们的乘积不用计算。

真正对答案有贡献的是当 $i = j$ 的这种情况。我们最开始读入的时候维护答案即可。

对于翻转操作，因为只有 $i = j$ 的情况有用，所以单独处理这个数即可。

# AC 代码

[AC 链接](https://codeforces.com/contest/405/submission/292158630)。

代码当中，只记录了 $A_{i,i}$。

$ans$ 为最终答案。

代码中 `^1` 相当于把 $0$ 变成 $1$，把 $1$ 变成 $0$。

代码中 `&1` 相当于 $\bmod 2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans = 0;
int num[1005];
int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		static int tp;
		for(int j = 1; j <= n; j++){
			scanf("%d",&tp);
			if(i == j){
				num[i] = tp;
				ans += tp;
			}
		}
	}
	scanf("%d",&m);
	while(m--){
		static int tpa,tpb;
		scanf("%d",&tpa);
		if(tpa < 3){
			scanf("%d",&tpb);
			if(num[tpb]){
				ans--;
			}else{
				ans++;
			}
			num[tpb] ^= 1;
		}else{
			printf("%d",ans&1);
		}
	}
	return 0;
}
```

~~祭我死去的 RMJ。~~

---

## 作者：Michael1234 (赞：0)

- 本题主要为**思维**题：

- 我们很容易发现，在每次相乘时，$mp_{i,j}$ 总会和 $mp_{j,i}$ 凑成一对。

- 而每当计算到第 $i$ 行 $i$ 列、第 $j$ 行 $j$ 列时 $mp_{i,j} \times mp_{j,i}$ 就会被算一次。

- 因此每个 $mp_{i,j}\times mp_{j,i}$ 都会被计算两次，其和在二进制下为 $0$，对答案无影响。

- 但对于 $mp_{i,i}$，其只有在计算到第 $i$ 行 $i$ 列时才会被计算，且只有一次，所以其对答案有影响。

- 因此我们可以维护答案，累加所有 $mp_{i,i}$。

- 当修改第 $i$ 行或第 $i$ 列时，只有 $mp_{i,i}$ 对答案产生影响，答案会 $+1$ 或 $-1$。

- 所以每次修改时，改变一下答案即可。

- 而每次查询时，输出维护的答案即可。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,q,x,ans,mp[N][N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>mp[i][j];
		}
		ans+=mp[i][i];
	}
	ans%=2;
	for(cin>>q;q;q--)
	{
		cin>>x;
		if(x!=3)
		{
			cin>>x;
			ans=1-ans;
		}
		else
		{
			cout<<ans;
		}
	}
	return 0;
}
```

---

