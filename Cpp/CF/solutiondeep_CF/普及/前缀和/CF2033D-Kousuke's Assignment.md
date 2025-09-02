# 题目信息

# Kousuke's Assignment

## 题目描述

After a trip with Sakurako, Kousuke was very scared because he forgot about his programming assignment. In this assignment, the teacher gave him an array $ a $ of $ n $ integers and asked him to calculate the number of non-overlapping segments of the array $ a $ , such that each segment is considered beautiful.

A segment $ [l,r] $ is considered beautiful if $ a_l + a_{l+1} + \dots + a_{r-1} + a_r=0 $ .

For a fixed array $ a $ , your task is to compute the maximum number of non-overlapping beautiful segments.

## 样例 #1

### 输入

```
3
5
2 1 -3 2 1
7
12 -4 4 43 -3 -5 8
6
0 -4 0 3 0 1```

### 输出

```
1
2
3```

# AI分析结果

### 题目重写
#### Kousuke的作业

#### 题目描述
在与Sakurako的旅行之后，Kousuke非常害怕，因为他忘记了他的编程作业。在这个作业中，老师给了他一个包含$n$个整数的数组$a$，并要求他计算数组中不重叠的美丽子段的数量。

一个子段$[l,r]$被认为是美丽的，当且仅当$a_l + a_{l+1} + \dots + a_{r-1} + a_r = 0$。

对于一个固定的数组$a$，你的任务是计算不重叠的美丽子段的最大数量。

#### 样例 #1
##### 输入
```
3
5
2 1 -3 2 1
7
12 -4 4 43 -3 -5 8
6
0 -4 0 3 0 1
```

##### 输出
```
1
2
3
```

### 题解分析与结论
#### 综合分析
本题的核心思想是利用前缀和和贪心策略或动态规划来求解不重叠的美丽子段的最大数量。大多数题解都采用了前缀和的思想，通过记录前缀和的出现位置来判断是否存在美丽子段。贪心策略和动态规划是主要的两种解法，贪心策略通过尽可能早地分割出美丽子段来最大化数量，而动态规划则通过状态转移来求解最优解。

#### 最优关键思路
1. **前缀和**：通过计算前缀和，可以快速判断某个子段的和是否为0。
2. **贪心策略**：从左到右扫描数组，一旦发现可以形成一个美丽子段，立即分割，以确保后面的子段数量最大化。
3. **动态规划**：通过记录前缀和的出现位置，利用状态转移方程求解最大不重叠子段数量。

#### 可拓展之处
- 类似的问题可以扩展到求解其他特定条件的子段，如子段和为某个特定值、子段乘积为1等。
- 可以使用哈希表或优先队列来优化前缀和的查找和更新。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)

### 所选高星题解
#### 题解1：作者：chenxi2009 (赞：6)
- **星级**：5星
- **关键亮点**：使用前缀和和贪心策略，代码简洁高效，复杂度为$O(\sum n\log n)$。
- **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[100001],ans;
long long sum;
set<long long>s;
int main(){
	scanf("%d",&T);
	while(T --){
		ans = 0,sum = 0,s.clear(),s.insert(0);//多测清空 
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++){
			scanf("%d",&a[i]);
			sum += a[i];
			if(s.count(sum)){
				sum = 0,ans ++,s.clear(),s.insert(0);//找到了一个子段，前缀和、set 均清空 
			}
			else{
				s.insert(sum);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
- **实现思想**：通过维护一个前缀和的集合，一旦发现当前前缀和已经存在于集合中，说明找到了一个美丽子段，立即分割并清空集合。

#### 题解2：作者：Super_Cube (赞：2)
- **星级**：4星
- **关键亮点**：使用动态规划和前缀和，通过`map`记录前缀和的出现位置，复杂度为$O(n\log n)$。
- **核心代码**：
```cpp
#include<bits/stdc++.h>
std::map<long long,int>mp;
int dp[100005];
int T,n;
long long s;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		mp.clear();
		mp[0]=0;s=0;
		for(int i=1,x;i<=n;++i){
			scanf("%d",&x);s+=x;
			dp[i]=dp[i-1];
			if(mp.count(s))
				dp[i]=std::max(dp[i],dp[mp[s]]+1);
			mp[s]=i;
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
```
- **实现思想**：通过动态规划数组`dp`记录前$i$个元素的最大美丽子段数量，利用`map`记录前缀和的出现位置，进行状态转移。

#### 题解3：作者：A_Bit_Cold (赞：0)
- **星级**：4星
- **关键亮点**：使用贪心策略和前缀和，代码简洁，复杂度为$O(n\log n)$。
- **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,cnt;
long long a[N];
map <long long,int> v;
int main() {
	scanf("%d",&t);
	while(t--) {
		v.clear();
	    scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		v[0]=1; long long s=0ll; cnt=0;
		for(int i=1;i<=n;i++) {
			s+=a[i];
			if(v[s]) cnt++,v.clear(),s=0ll,v[0]=1;
			v[s]=1;
		}
		printf("%d\n",cnt);
	}
	return 0;
}
```
- **实现思想**：通过维护一个前缀和的映射，一旦发现当前前缀和已经存在于映射中，说明找到了一个美丽子段，立即分割并清空映射。

---
处理用时：45.07秒