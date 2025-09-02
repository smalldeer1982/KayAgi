# 题目信息

# [ABC128D] equeue

## 题目描述

有一个双端队列，初始时队列中共有 $n$ 个元素，元素从头到尾的权值为 $v_{1},v_{2},\cdots,v_{n}$

你可以进行不超过 $k$ 次操作（也可以一次都不操作），每次操作可以选择队头或队尾的一个元素，将它归为己有，或将自己手上的一个元素塞到队头或队尾

问最终你手上所有元素的权值之和的最大值是多少

## 说明/提示

$ 1 \le n \le 50,1 \le k \le 100, -10^7 \le v_{i} \le 10^7 $

## 样例 #1

### 输入

```
6 4

-10 8 2 1 2 6```

### 输出

```
14```

## 样例 #2

### 输入

```
6 4

-6 -100 50 -2 -5 -3```

### 输出

```
44```

## 样例 #3

### 输入

```
6 3

-6 -100 50 -2 -5 -3```

### 输出

```
0```

# AI分析结果

### 题目翻译
【题目内容】
# [ABC128D] equeue

## 题目描述

有一个双端队列，初始时队列中共有 $n$ 个元素，元素从头到尾的权值为 $v_{1},v_{2},\cdots,v_{n}$。

你可以进行不超过 $k$ 次操作（也可以一次都不操作），每次操作可以选择队头或队尾的一个元素，将它归为己有，或将自己手上的一个元素塞到队头或队尾。

问最终你手上所有元素的权值之和的最大值是多少。

## 说明/提示

$ 1 \le n \le 50,1 \le k \le 100, -10^7 \le v_{i} \le 10^7 $

## 样例 #1

### 输入

```
6 4

-10 8 2 1 2 6```

### 输出

```
14```

## 样例 #2

### 输入

```
6 4

-6 -100 50 -2 -5 -3```

### 输出

```
44```

## 样例 #3

### 输入

```
6 3

-6 -100 50 -2 -5 -3```

### 输出

```
0```

### 算法分类
贪心

### 题解分析与结论
本题的核心在于通过贪心策略最大化手中元素的权值之和。由于数据范围较小（$n \leq 50$，$k \leq 100$），可以直接枚举从队头和队尾取元素的次数，然后利用贪心策略将手中的负数放回队列，以增加最终的总和。

### 所选高星题解
#### 题解1：作者：Licykoc (赞：7)
- **星级**：★★★★★
- **关键亮点**：使用优先队列（小顶堆）来维护手中的元素，确保每次放回的元素是最小的负数，从而最大化最终的总和。代码简洁且高效。
- **个人心得**：通过优先队列的自动排序功能，简化了贪心策略的实现，避免了手动排序的复杂性。

```cpp
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
int n,k,_,ans;
int a[51];
priority_queue<int,vector<int>,greater<int> > Q;
int main () {
	IOS;
	cin>>n>>k;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=0;i<=k;++i)	
		for (int j=0;i+j<=k&&i+j<=n;++j) {
			for (int x=1;x<=i;++x) Q.push(a[x]);
			for (int x=1;x<=j;++x) Q.push(a[n-x+1]);
			_=k-i-j;
			while (!Q.empty()&&_--&&Q.top()<0) Q.pop();
			_=0;
			while (!Q.empty()) _+=Q.top(),Q.pop();
			ans=max(ans,_);
		}
	cout<<ans<<endl;
}
```

#### 题解2：作者：Erica_N_Contina (赞：4)
- **星级**：★★★★
- **关键亮点**：通过两层循环枚举从队头和队尾取元素的次数，然后对取出的元素进行排序，贪心地放回最小的负数。思路清晰，代码易于理解。
- **个人心得**：通过排序和贪心策略的结合，有效地减少了操作的复杂性，确保了算法的正确性。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
using namespace std;

const int N=1e5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

ll n,m,ans,sum,k;
ll t[N],v[N];

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	for(int ia=0;ia<=n&&ia<=k;ia++){
		for(int ib=0;ib+ia<=n&&ib+ia<=k;ib++){
			int cnt=0;sum=0;
			for(int i=1;i<=ia;i++)t[++cnt]=v[i],sum+=v[i];
			for(int i=1;i<=ib;i++)t[++cnt]=v[n-i+1],sum+=v[n-i+1];
			sort(t+1,t+cnt+1);
			int c=k-ia-ib;
			for(int i=1;i<=c&&i<=cnt;i++){
				if(t[i]>0)break;
				sum-=t[i];
			}
			ans=max(ans,sum);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

#### 题解3：作者：qiuqiuqzm (赞：0)
- **星级**：★★★★
- **关键亮点**：通过枚举从队头和队尾取元素的次数，然后利用贪心策略将手中的负数放回队列，思路清晰且代码简洁。
- **个人心得**：通过贪心策略的合理应用，确保了算法的正确性和高效性。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,v[1001],ans=-1;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>v[i];
	for(int i=0;i<=min(n,k);i++)
	{
		for(int j=0;j<=min(n-i,k-i);j++)
		{
			int maxx=0,small[1001],num=0;
			for(int l=1;l<=i;l++)
			{
				maxx+=v[l];
				if(v[l]<0)
					small[++num]=v[l];
			}
			for(int r=n;r>n-j;r--)
			{
				maxx+=v[r];
				if(v[r]<0)
					small[++num]=v[r];
			}
			sort(small+1,small+1+num);
			int last=min(k-i-j,num);
			for(int sum=1;sum<=last;sum++)
				maxx-=small[sum];
			ans=max(maxx,ans);
		}
	}
	cout<<ans;
	return 0;
}
```

### 关键思路与技巧
1. **贪心策略**：通过放回最小的负数来最大化最终的总和。
2. **枚举与排序**：枚举从队头和队尾取元素的次数，并对取出的元素进行排序，确保贪心策略的正确性。
3. **优先队列**：使用优先队列（小顶堆）来维护手中的元素，简化了贪心策略的实现。

### 拓展思路
类似的问题可以通过贪心策略和枚举法来解决，尤其是在数据范围较小的情况下。可以尝试将这种思路应用到其他需要最大化或最小化某个值的题目中。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：44.11秒