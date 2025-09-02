# 题目信息

# Yet Another Ball Problem

## 题目描述

The king of Berland organizes a ball! $ n $ pair are invited to the ball, they are numbered from $ 1 $ to $ n $ . Each pair consists of one man and one woman. Each dancer (either man or woman) has a monochrome costume. The color of each costume is represented by an integer from $ 1 $ to $ k $ , inclusive.

Let $ b_i $ be the color of the man's costume and $ g_i $ be the color of the woman's costume in the $ i $ -th pair. You have to choose a color for each dancer's costume (i.e. values $ b_1, b_2, \dots, b_n $ and $ g_1, g_2, \dots g_n $ ) in such a way that:

1. for every $ i $ : $ b_i $ and $ g_i $ are integers between $ 1 $ and $ k $ , inclusive;
2. there are no two completely identical pairs, i.e. no two indices $ i, j $ ( $ i \ne j $ ) such that $ b_i = b_j $ and $ g_i = g_j $ at the same time;
3. there is no pair such that the color of the man's costume is the same as the color of the woman's costume in this pair, i.e. $ b_i \ne g_i $ for every $ i $ ;
4. for each two consecutive (adjacent) pairs both man's costume colors and woman's costume colors differ, i.e. for every $ i $ from $ 1 $ to $ n-1 $ the conditions $ b_i \ne b_{i + 1} $ and $ g_i \ne g_{i + 1} $ hold.

Let's take a look at the examples of bad and good color choosing (for $ n=4 $ and $ k=3 $ , man is the first in a pair and woman is the second):

Bad color choosing:

- $ (1, 2) $ , $ (2, 3) $ , $ (3, 2) $ , $ (1, 2) $ — contradiction with the second rule (there are equal pairs);
- $ (2, 3) $ , $ (1, 1) $ , $ (3, 2) $ , $ (1, 3) $ — contradiction with the third rule (there is a pair with costumes of the same color);
- $ (1, 2) $ , $ (2, 3) $ , $ (1, 3) $ , $ (2, 1) $ — contradiction with the fourth rule (there are two consecutive pairs such that colors of costumes of men/women are the same).

Good color choosing:

- $ (1, 2) $ , $ (2, 1) $ , $ (1, 3) $ , $ (3, 1) $ ;
- $ (1, 2) $ , $ (3, 1) $ , $ (2, 3) $ , $ (3, 2) $ ;
- $ (3, 1) $ , $ (1, 2) $ , $ (2, 3) $ , $ (3, 2) $ .

You have to find any suitable color choosing or say that no suitable choosing exists.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
YES
3 1
1 3
3 2
2 3
```

## 样例 #2

### 输入

```
10 4
```

### 输出

```
YES
2 1
1 3
4 2
3 4
4 3
3 2
2 4
4 1
1 4
3 1
```

## 样例 #3

### 输入

```
13 4
```

### 输出

```
NO
```

# AI分析结果

### 题目内容中文重写
# 另一个舞会问题

## 题目描述
伯兰国王要举办一场舞会！有 $n$ 对情侣被邀请参加舞会，他们的编号从 $1$ 到 $n$。每对情侣由一名男士和一名女士组成。每名舞者（男士或女士）都有一套单色服装。每套服装的颜色用一个 $1$ 到 $k$（包含 $1$ 和 $k$）的整数表示。

设 $b_i$ 是第 $i$ 对情侣中男士服装的颜色，$g_i$ 是第 $i$ 对情侣中女士服装的颜色。你需要为每名舞者的服装选择一种颜色（即确定 $b_1, b_2, \dots, b_n$ 和 $g_1, g_2, \dots g_n$ 的值），使得：
1. 对于每个 $i$，$b_i$ 和 $g_i$ 都是 $1$ 到 $k$（包含 $1$ 和 $k$）之间的整数；
2. 不存在两个完全相同的情侣对，即不存在两个索引 $i, j$（$i \ne j$），使得 $b_i = b_j$ 且 $g_i = g_j$ 同时成立；
3. 不存在某对情侣中男士服装的颜色与女士服装的颜色相同的情况，即对于每个 $i$，都有 $b_i \ne g_i$；
4. 对于每两个相邻的情侣对，男士服装的颜色和女士服装的颜色都不同，即对于从 $1$ 到 $n - 1$ 的每个 $i$，都满足 $b_i \ne b_{i + 1}$ 且 $g_i \ne g_{i + 1}$。

让我们来看一些颜色选择的好坏示例（$n = 4$ 且 $k = 3$，男士在情侣对中排在第一位，女士排在第二位）：

不好的颜色选择：
- $(1, 2)$，$(2, 3)$，$(3, 2)$，$(1, 2)$ —— 与第二条规则矛盾（存在相同的情侣对）；
- $(2, 3)$，$(1, 1)$，$(3, 2)$，$(1, 3)$ —— 与第三条规则矛盾（存在某对情侣服装颜色相同）；
- $(1, 2)$，$(2, 3)$，$(1, 3)$，$(2, 1)$ —— 与第四条规则矛盾（存在两个相邻的情侣对，男士/女士服装颜色相同）。

好的颜色选择：
- $(1, 2)$，$(2, 1)$，$(1, 3)$，$(3, 1)$；
- $(1, 2)$，$(3, 1)$，$(2, 3)$，$(3, 2)$；
- $(3, 1)$，$(1, 2)$，$(2, 3)$，$(3, 2)$。

你需要找到任何合适的颜色选择方案，或者说明不存在合适的选择方案。

## 样例 #1
### 输入
```
4 3
```
### 输出
```
YES
3 1
1 3
3 2
2 3
```

## 样例 #2
### 输入
```
10 4
```
### 输出
```
YES
2 1
1 3
4 2
3 4
4 3
3 2
2 4
4 1
1 4
3 1
```

## 样例 #3
### 输入
```
13 4
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先判断是否有解，通过计算可知，能组成的不同情侣对最多有 $k\times(k - 1)$ 种，若 $n > k\times(k - 1)$ 则无解。在有解的情况下，不同题解采用了不同的构造方案，多数题解通过输出 $(a, b)$ 和 $(b, a)$ 这样的组合来满足相邻情侣对服装颜色不同的条件。

### 所选题解
- **furbzy（4星）**
    - **关键亮点**：思路清晰，对有解时的构造方案解释详细，代码中使用了快读优化输入。
    - **个人心得**：作者提到自己调代码时习惯加文件操作，虽然此处无用可删，但体现了调试习惯。
- **Crazyouth（4星）**
    - **关键亮点**：通过具体例子展示构造方式，易于理解，使用 `vector` 存储结果，代码简洁。
- **lmz_（4星）**
    - **关键亮点**：思路清晰，对无解和有解情况的处理逻辑明确，代码实现简洁。

### 重点代码
#### furbzy 的核心代码
```c
#include<bits/stdc++.h>
#define ri register int
#define in inline
using namespace std;
in int read()	//快读 
{
	int ans=0;
	bool j=false;
	char c=getchar();
	while(!(isdigit(c)))
	{
		if(c=='-')
		j=true;
		c=getchar();
	}
	while(isdigit(c))
	{
		ans=(ans<<3)+(ans<<1)+(c^48);
		c=getchar();
	}
	return j? ~ans+1:ans;
}
int main()
{
	long long m,n,cnt=0;    //cnt表示已输出cnt个数对 
	scanf("%lld %lld",&m,&n);
	if(m>n*n-n)
	{
		printf("no");  //输出任意字母的大小写都行
		return 0;
	}
	printf("yes\n");
	for(ri i=1;i<=n;i++)
	{
		for(ri j=i;cnt<m&&j<=n;j++)    //i前面的已经枚举过 
		{
			if(i==j)
			continue;
			if(cnt<=m-2)    //还需输出>=2个数对 
			printf("%d %d\n%d %d\n",i,j,j,i);
			else
			printf("%d %d",i,j);
			cnt+=2;
		}
		if(cnt>=m)
		break;
	}
	return 0;
}
```
**核心实现思想**：先判断是否有解，有解时通过两层循环枚举 $(i, j)$，若 $i \ne j$ 则输出 $(i, j)$ 和 $(j, i)$，直到输出 $n$ 个情侣对。

#### Crazyouth 的核心代码
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int>> ans;
int main()
{
	int n,k,a=1,b=2;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		if(b==k+1) a++,b=a+1;
		if(a==k+1||b==k+1)
		{
			cout<<"NO";
			return 0;
		}
		ans.push_back({a,b});
		if(i==n) break;
		ans.push_back({b,a});
		i++;
		b++;
	}
	cout<<"YES"<<endl;
	for(auto p:ans) cout<<p.first<<' '<<p.second<<endl;
}
```
**核心实现思想**：先判断是否有解，有解时通过循环生成 $(a, b)$ 和 $(b, a)$ 并存储在 `vector` 中，最后输出结果。

#### lmz_ 的核心代码
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ud unsigned double
#define db double
#define ll long long
using namespace std;
const int maxn = 1e6,INF=0x7fffffff;
ll n,k,s;
int main(){
	cin>>n>>k;
	if(n>k*k-k){
		cout<<"No";
		return 0;
	}
	cout<<"Yes\n";
	for(int i=1;i<=k;i++){
		for(int j=i;j<=k&&s<n;j++){
			if(i==j) continue;
			if(n-s>=2) cout<<i<<' '<<j<<endl<<j<<' '<<i<<endl;
			else cout<<i<<' '<<j<<endl;
			s+=2;
		}
		if(s>=n) break;
	}
	return 0;
}
```
**核心实现思想**：先判断是否有解，有解时通过两层循环枚举 $(i, j)$，若 $i \ne j$ 则输出 $(i, j)$ 和 $(j, i)$，直到输出 $n$ 个情侣对。

### 最优关键思路或技巧
- 先通过数学计算判断是否有解，能组成的不同情侣对最多有 $k\times(k - 1)$ 种。
- 在有解的情况下，通过输出 $(a, b)$ 和 $(b, a)$ 这样的组合来满足相邻情侣对服装颜色不同的条件。

### 拓展思路
同类型题可能会有更多的约束条件，例如增加服装颜色的限制、情侣对之间的其他关系等。类似算法套路可以是先通过数学分析判断是否有解，再根据条件构造满足要求的方案。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)

### 个人心得摘录与总结
- furbzy 提到自己调代码时习惯加文件操作，虽然此处无用可删，但这是一种常见的调试手段，方便在本地测试数据。
- lmz_ 提到你谷的爬虫有问题，交两次就好了，第二次爬取的是第一次的结果，这是在使用洛谷平台时可能遇到的小问题及解决方法。

---
处理用时：67.37秒