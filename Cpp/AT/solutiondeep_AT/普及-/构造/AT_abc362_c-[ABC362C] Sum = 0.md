# 题目信息

# [ABC362C] Sum = 0

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_c

$ N $ 個の整数の組 $ (L_1,R_1),(L_2,R_2),\ldots,(L_N,R_N) $ が与えられます。

以下の条件を満たす長さ $ N $ の整数列 $ X=(X_1,X_2,\ldots,X_N) $ が存在するか判定し、存在するならば一つ出力してください。

- 各 $ i=1,2,\ldots,N $ に対して $ L_i\leq\ X_i\leq\ R_i $
- $ \displaystyle\ \sum_{i=1}^N\ X_i=0 $

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ -10^9\leq\ L_i\leq\ R_i\leq\ 10^9 $
- 入力は全て整数
 
### Sample Explanation 1

数列 $ X=(4,-3,-1) $ は問題の条件をすべて満たします。ほかにも $ (3,-3,0) $ や $ (5,-4,-1) $ などが条件を満たします。

### Sample Explanation 2

条件を満たす整数列 $ X $ は存在しません。

## 样例 #1

### 输入

```
3

3 5

-4 1

-2 3```

### 输出

```
Yes

4 -3 -1```

## 样例 #2

### 输入

```
3

1 2

1 2

1 2```

### 输出

```
No```

## 样例 #3

### 输入

```
6

-87 12

-60 -54

2 38

-76 6

87 96

-17 38```

### 输出

```
Yes

-66 -57 31 -6 89 9```

# AI分析结果

### 题目内容翻译
给定 $N$ 个整数对 $(L_1,R_1),(L_2,R_2),\ldots,(L_N,R_N)$。

判断是否存在满足以下条件的长度为 $N$ 的整数序列 $X=(X_1,X_2,\ldots,X_N)$，若存在则输出其中一个。
- 对于每个 $i = 1,2,\ldots,N$，都有 $L_i\leq X_i\leq R_i$。
- $\sum_{i = 1}^{N}X_i = 0$。

### 综合分析与结论
这些题解的核心思路都是先判断是否存在满足条件的序列，再尝试构造出这样的序列。判断的依据是计算所有区间左端点之和 `suml` 与右端点之和 `sumr`，若 `suml > 0` 或 `sumr < 0`，则不存在满足条件的序列。构造序列时，大部分题解采用贪心策略，从某个初始状态（如全部取左端点或全部取右端点）开始，逐步调整每个数，使总和趋近于 0。

### 所选题解
- **作者：_wsq_ (赞：8)  4星**
    - **关键亮点**：思路清晰，代码简洁，直接计算左右端点之和判断是否有解，然后采用贪心策略构造序列。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
#define maxn 200005
typedef long long ll;
int main(){
    ll n,l[maxn],r[maxn],suml=0,sumr=0;
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>l[i]>>r[i];
        suml+=l[i];
        sumr+=r[i];
    }
    if(suml>0||sumr<0){
        cout<<"No";
        exit(0);
    }
    cout<<"Yes"<<endl;
    for(ll i=1;i<=n;i++){
        cout<<r[i]-min(r[i]-l[i],sumr)<<' ';
        sumr-=min(r[i]-l[i],sumr);
    }
    return 0;
}
```
    - **核心实现思想**：先计算所有区间左端点之和 `suml` 与右端点之和 `sumr`，若 `suml > 0` 或 `sumr < 0`，则输出 `No`。否则，假设 $X_i = R_i$，此时总和为 `sumr`，然后依次给每个数减去其减去后使得总和仍大于等于 0 的能减去的最大值。

- **作者：xuduang (赞：2)  4星**
    - **关键亮点**：详细分析了贪心的过程，分情况讨论如何使总和更接近 0。
    - **核心代码**：
```cpp
#include <iostream>
#include <cmath>
#include <string.h>
#include <queue>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n;
int l[N], r[N];
int c[N];
void output()
{
	cout << "Yes\n";
	for(int i = 1; i <= n; i++) cout << c[i] << " ";
	cout << endl;
	exit(0);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];
	int now = 0;
	for(int i = 1; i <= n; i++)
	{
		now += l[i];
		c[i] = l[i];
	}
	if(now > 0)//怎么样都不能完成 
	{
		cout << "No\n";
		exit(0);
	}
	for(int i = 1; i <= n; i++)
	{
		int ned = 0 - now;
		if(r[i] - l[i] >= ned)//情况1 
		{
			c[i] = l[i] + ned;
			output();
		}
		//情况2 
		c[i] = r[i];
		now += (r[i] - l[i]);
	}
	cout << "No\n";//还是不行 
	return 0;
}
```
    - **核心实现思想**：先计算所有区间左端点之和 `now`，若 `now > 0`，则输出 `No`。然后遍历每个区间，分两种情况讨论：若 `now` 变成 0 的距离小于区间大小，则直接将该数调整为能使总和为 0 的值；否则，将该数调整为区间右端点。

- **作者：Lame_Joke (赞：2)  4星**
    - **关键亮点**：将问题转化为将最大值的和减成 0，思路清晰，实现简单。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],l[200005],r[200005],n;
int sm=0,r1[200005];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&l[i],&r[i]);
		sm+=r[i];
		r1[i]=r[i];
	}
	if(sm<0)             			//最大值和小于0；         
	{
		printf("No");				//不可能完成；
		return 0;
	}
	int x;
	for(int i=1;i<=n;i++)
	{
		x=r[i]-l[i];				//x为能减的最大值；
		if(sm==0) continue;
		if(sm-x<0)					//无需减完就已经合法；
		{
			r1[i]-=sm;
			sm=0;
			break;
		}
		if(sm>=x)					//尽量减；
		{
			r1[i]=r[i]-x;
			sm-=x;
		}
	}
	if(sm) printf("No");			//如果和为0就可以输出答案了；
	else
	{
		printf("Yes\n");
		for(int i=1;i<=n;i++) printf("%lld ",r1[i]);
	}
}
```
    - **核心实现思想**：先计算所有区间右端点之和 `sm`，若 `sm < 0`，则输出 `No`。然后将答案数组初始化为每个数的最大值，依次尝试将每个数减为最小值，直到总和为 0 或无法再减。最后判断总和是否为 0，若是则输出 `Yes` 及答案数组，否则输出 `No`。

### 最优关键思路或技巧
- **判断无解条件**：计算所有区间左端点之和 `suml` 与右端点之和 `sumr`，若 `suml > 0` 或 `sumr < 0`，则不存在满足条件的序列。
- **贪心构造**：从某个初始状态（如全部取左端点或全部取右端点）开始，逐步调整每个数，使总和趋近于 0。

### 可拓展之处
同类型题可能会有更多的限制条件，如要求序列满足某些特定的性质，或者给定更多的区间约束。类似算法套路可以应用于其他需要构造满足特定条件序列的问题，通过判断可行性和贪心构造来解决。

### 推荐洛谷题目
- [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录与总结
- **Cosine_Func**：提到“十年 OI 一场空，不开 `long long` 见祖宗！”，总结为在处理可能涉及大数值的问题时，一定要注意数据类型的选择，避免因数据溢出导致错误。 

---
处理用时：47.30秒