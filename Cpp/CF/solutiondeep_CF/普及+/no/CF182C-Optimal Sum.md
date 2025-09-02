# 题目信息

# Optimal Sum

## 题目描述

And here goes another problem on arrays. You are given positive integer $ len $ and array $ a $ which consists of $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . Let's introduce two characteristics for the given array.

- Let's consider an arbitrary interval of the array with length $ len $ , starting in position $ i $ . Value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF182C/a67922122e1d38581ab8c091ae9897d972811ca1.png), is the modular sum on the chosen interval. In other words, the modular sum is the sum of integers on the chosen interval with length $ len $ , taken in its absolute value.
- Value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF182C/93dd358f9082d67d4f803ced64f412bb80cdf4c2.png) is the optimal sum of the array. In other words, the optimal sum of an array is the maximum of all modular sums on various intervals of array with length $ len $ .

Your task is to calculate the optimal sum of the given array $ a $ . However, before you do the calculations, you are allowed to produce no more than $ k $ consecutive operations of the following form with this array: one operation means taking an arbitrary number from array $ a_{i} $ and multiply it by -1. In other words, no more than $ k $ times you are allowed to take an arbitrary number $ a_{i} $ from the array and replace it with $ -a_{i} $ . Each number of the array is allowed to choose an arbitrary number of times.

Your task is to calculate the maximum possible optimal sum of the array after at most $ k $ operations described above are completed.

## 样例 #1

### 输入

```
5 3
0 -2 3 -5 1
2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 2
1 -3 -10 4 1
3
```

### 输出

```
14
```

## 样例 #3

### 输入

```
3 3
-2 -5 4
1
```

### 输出

```
11
```

# AI分析结果

### 题目内容
#### Optimal Sum
1. **题目描述**：这又是一道关于数组的问题。给定正整数 $len$ 和由 $n$ 个整数 $a_{1}, a_{2}, \cdots, a_{n}$ 组成的数组 $a$ 。我们为这个给定数组引入两个特性：
    - 考虑数组中任意一个长度为 $len$ 且起始位置为 $i$ 的区间。值 $S_{i}=\left|\sum_{j = i}^{i + len - 1}a_{j}\right|$ ，即所选区间上的模和。换句话说，模和就是所选长度为 $len$ 的区间上整数的和的绝对值。
    - 值 $OptimalSum=\max_{1\leq i\leq n - len + 1}S_{i}$ 是数组的最优和。也就是说，数组的最优和是数组中各种长度为 $len$ 的区间上的模和中的最大值。
    - 你的任务是计算给定数组 $a$ 的最优和。然而，在进行计算之前，你可以对这个数组执行不超过 $k$ 次以下形式的连续操作：一次操作意味着取数组中的任意一个数 $a_{i}$ 并将其乘以 -1 。换句话说，你最多可以 $k$ 次从数组中取任意一个数 $a_{i}$ 并用 $-a_{i}$ 替换它。数组中的每个数可以被选择任意次数。
    - 你的任务是在完成上述最多 $k$ 次操作后，计算数组可能的最大最优和。
2. **样例 #1**
    - **输入**：
```
5 3
0 -2 3 -5 1
2
```
    - **输出**：
```
10
```
3. **样例 #2**
    - **输入**：
```
5 2
1 -3 -10 4 1
3
```
    - **输出**：
```
14
```
4. **样例 #3**
    - **输入**：
```
3 3
-2 -5 4
1
```
    - **输出**：
```
11
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是围绕如何通过不超过 $k$ 次的取反操作，来最大化长度为 $len$ 的区间和的绝对值。不同题解在实现方式上有所差异，主要体现在数据结构的选择和具体操作的细节上。有的题解使用复杂的数据结构如树状数组、值域分块来优化操作，有的则采用相对简单的优先队列、集合等数据结构进行模拟。

### 所选的题解
#### 作者：Allanljx (4星)
- **关键亮点**：思路清晰，通过优先队列和标记数组来模拟操作过程，易于理解。代码实现简洁明了，直接针对题意进行操作，对于每个新加入和弹出的数进行分类讨论，从而维护区间和以及操作状态。
- **个人心得**：无
```cpp
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
int n,len,k,a[100005],now,sum,ans=-9999999999;
int book[100005];
priority_queue<pair<int,int> > q,q1;
void init()//将正数变为负数 
{
	memset(book,0,sizeof(book));
	for(int i=1;i<=n;i++) a[i]=-a[i];
	while(q.size()) q.pop();
	while(q1.size()) q1.pop();
	now=0,sum=0;
}
void work()
{
	for(int i=1;i<=n;i++)
	{
		if(i<=len)//序列长度不够 
		{
			if(a[i]>=0) sum+=a[i];//正数直接加 
			else
			{
				if(now<k) now++,sum-=a[i],q.push(mp(a[i],i)),book[i]=1;//还有操作次数 
				else
				{
					if(q.size()&&a[i]<=q.top().first)//进行操作
					{
						book[q.top().second]=0;
						sum+=q.top().first*2; 
						sum-=a[i];
						q1.push(mp(-q.top().first,q.top().second));//弹出的数等待补位 
						q.pop();
						q.push(mp(a[i],i));
						book[i]=1;
					}
					else//不进行操作 
					{
						sum+=a[i];
						q1.push(mp(-a[i],i));
					}
				}
			}
			if(i==len) ans=max(ans,sum);
			continue;
		}
		while(q1.size()&&q1.top().second<=i-len) q1.pop();//将下标不符合要求的数弹出 
		if(!book[i-len]) sum-=a[i-len];//没有进行操作 
		else
		{
			sum+=a[i-len],book[i-len]=0,now--;
			if(q1.size())//补位 
			{
				q.push(mp(-q1.top().first,q1.top().second));
				sum+=2*q1.top().first;
				book[q1.top().second]=1;
				q1.pop();
				now++;
			}
		}
		while(q.size()&&!book[q.top().second]) q.pop();
		if(a[i]>=0) sum+=a[i];//正数直接加 
		else
		{
			if(now<k) sum-=a[i],book[i]=1,q.push(mp(a[i],i)),now++;//还有操作次数 
			else
			{
				if(q.size()&&a[i]<=q.top().first)//进行操作 
				{
					book[q.top().second]=0;
					sum+=q.top().first*2;
					sum-=a[i];
					q1.push(mp(-q.top().first,q.top().second));
					q.pop();
					q.push(mp(a[i],i));
					book[i]=1;
				}
				else//补位 
				{
					sum+=a[i];
					q1.push(mp(-a[i],i));
				}
			}
		}
		ans=max(ans,sum);
	}
}
signed main()
{
	cin>>n>>len;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cin>>k;
	work();
	init();
	work();
	cout<<ans;
   	return 0;
}
```
核心实现思想：利用优先队列 `q` 存储已进行操作的数，`q1` 存储未操作的负数，`book` 数组标记数是否已操作。遍历数组，对每个数根据其正负、是否有操作次数以及与队列中数的比较进行不同处理，维护区间和 `sum` 并更新答案 `ans`。

#### 作者：Adolfo_North (4星)
- **关键亮点**：代码简洁高效，通过 `multiset` 来维护区间内的负数，便于插入和删除操作。同时通过将原数组取相反数的方式，统一了将负数变为正数和将正数变为负数的两种情况处理。
- **个人心得**：无
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+7;
int a[N],b[N];
int solve(int n,int len,int k,int a[]){
	multiset<int> s;
	int ans=-1e9,sum=0;
	for(int i=1;i<=len;i++){
		if(a[i]<0) s.insert(a[i]);
		sum+=a[i];
	}
	int now=sum,cnt=0;
	for(auto x:s){
		now-=2*x;
		if(++cnt==k) break;
	}
	ans=max(ans,now);
	for(int l=2,r=len+1;r<=n;l++,r++){
		sum-=a[l-1],sum+=a[r];
		if(a[r]<0) s.insert(a[r]);
		if(a[l-1]<0) s.erase(s.lower_bound(a[l-1]));
		now=sum,cnt=0;
		for(auto x:s){
			now-=2*x;
			if(++cnt==k) break;
		}
		ans=max(ans,now);
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n,len,k;
	cin>>n>>len;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=-a[i];
	cin>>k;
	cout<<max(solve(n,len,k,a),solve(n,len,k,b));
	return 0;
}
```
核心实现思想：`solve` 函数中，先初始化 `multiset` 并计算初始区间和，然后遍历区间，通过更新 `sum` 和 `multiset` 中负数，计算每次操作后的区间和并更新答案。主函数通过调用 `solve` 函数处理原数组和其相反数数组，取两者最大值。

#### 作者：_edge_ (4星)
- **关键亮点**：使用两个 `set` 分别维护要修改的数和备用的数，思路直观，代码实现简洁。通过巧妙地维护这两个 `set` 的元素，实现对滑动区间内前 $k$ 小负数的管理。
- **个人心得**：注意特判 $k = 0$ 的情况，避免出现运行时错误。
```cpp
	scanf("%lld %lld",&n,&len);
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	scanf("%lld",&k);int sum=0;
	for (int i=1;i<len;i++) {
		if (a[i]<0 && k) {
			if (s.size()<k) s.insert(a[i]),sum1+=a[i];
			else if (*s.rbegin()>=a[i])
				{sum1-=*s.rbegin();s1.insert(*s.rbegin());
				s.erase(--s.end());s.insert(a[i]);sum1+=a[i];}
			else s1.insert(a[i]);
		}
		sum+=a[i];
	}
	
	for (int i=len;i<=n;i++) {
		if (i!=len  && k) {
			int l=i-len;
			sum-=a[l];
			if (s.find(a[l])!=s.end()) {sum1-=a[l];s.erase(s.find(a[l]));}
			else if (s1.find(a[l])!=s1.end()) s1.erase(s1.find(a[l]));
		}
		
		while (s.size()<k && s1.size()) {
			s.insert(*s1.begin());
			sum1+=*s1.begin();
			s1.erase(s1.begin()); 
		}
		
		if (a[i]<0  && k) {
			if (s.size()<k) s.insert(a[i]),sum1+=a[i];
			else if (*s.rbegin()>=a[i])
				{sum1-=*s.rbegin();s1.insert(*s.rbegin());
				s.erase(--s.end());s.insert(a[i]);sum1+=a[i];}
			else s1.insert(a[i]);
		}
		sum+=a[i];
//		cout<<sum<<" "<<sum1<<" pp\n";
		ans=max(ans,sum-sum1-sum1);
	}
```
核心实现思想：初始化时将前 $len - 1$ 个数按规则放入 `s` 和 `s1` 两个 `set` 中，滑动区间时，对滑出和滑入的数在两个 `set` 中进行相应操作，维护 `sum` 和 `sum1`，`sum` 为区间和，`sum1` 为 `s` 中负数和的两倍，通过比较更新答案。

### 最优关键思路或技巧
1. **数据结构选择**：使用优先队列、`multiset`、`set` 等数据结构，方便地维护区间内的数以及其操作状态，能够高效地进行插入、删除和查找操作。
2. **统一情况处理**：将原数组取相反数，把将正数变为负数的情况转化为将负数变为正数的情况，统一处理逻辑，简化代码实现。
3. **滑动窗口思想**：通过模拟滑动窗口的过程，对每个长度为 $len$ 的区间进行操作和计算，在窗口滑动过程中动态维护所需的数据，如区间和、已操作数等。

### 同类型题或类似算法套路拓展
同类型题目通常围绕数组的区间操作展开，可能会结合不同的条件限制和操作方式。类似算法套路包括利用数据结构优化对区间元素的管理，如使用堆、优先队列、平衡树等；以及通过预处理或转换问题形式，简化问题的求解过程。例如，在一些题目中可能会要求对区间内的元素进行排序、查找特定元素等操作，都可以借鉴本题中对区间元素的维护方式。

### 洛谷相似知识点题目推荐
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)：同样涉及滑动窗口的操作，通过维护窗口内的最值来解决问题，与本题在滑动窗口的处理思路上有相似之处。
2. [P3378 模板：堆优化 Dijkstra](https://www.luogu.com.cn/problem/P3378)：虽然是最短路问题，但使用堆来优化操作，与本题中利用优先队列等数据结构维护数据有相似的数据结构应用思想。
3. [P2034 选择数字](https://www.luogu.com.cn/problem/P2034)：需要在数组中选择数字并进行操作以满足一定条件，与本题在对数组元素的操作和决策上有类似的思考方式。 

---
处理用时：110.62秒