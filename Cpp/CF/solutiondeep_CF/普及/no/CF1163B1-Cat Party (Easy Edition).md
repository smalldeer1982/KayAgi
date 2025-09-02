# 题目信息

# Cat Party (Easy Edition)

## 题目描述

This problem is same as the next one, but has smaller constraints.

Shiro's just moved to the new house. She wants to invite all friends of her to the house so they can play monopoly. However, her house is too small, so she can only invite one friend at a time.

For each of the $ n $ days since the day Shiro moved to the new house, there will be exactly one cat coming to the Shiro's house. The cat coming in the $ i $ -th day has a ribbon with color $ u_i $ . Shiro wants to know the largest number $ x $ , such that if we consider the streak of the first $ x $ days, it is possible to remove exactly one day from this streak so that every ribbon color that has appeared among the remaining $ x - 1 $ will have the same number of occurrences.

For example, consider the following sequence of $ u_i $ : $ [2, 2, 1, 1, 5, 4, 4, 5] $ . Then $ x = 7 $ makes a streak, since if we remove the leftmost $ u_i = 5 $ , each ribbon color will appear exactly twice in the prefix of $ x - 1 $ days. Note that $ x = 8 $ doesn't form a streak, since you must remove exactly one day.

Since Shiro is just a cat, she is not very good at counting and needs your help finding the longest streak.

## 说明/提示

In the first example, we can choose the longest streak of $ 13 $ days, since upon removing the last day out of the streak, all of the remaining colors $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ will have the same number of occurrences of $ 3 $ . Note that the streak can also be $ 10 $ days (by removing the $ 10 $ -th day from this streak) but we are interested in the longest streak.

In the fourth example, if we take the streak of the first $ 6 $ days, we can remove the third day from this streak then all of the remaining colors $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ will occur exactly once.

## 样例 #1

### 输入

```
13
1 1 1 2 2 2 3 3 3 4 4 4 5
```

### 输出

```
13```

## 样例 #2

### 输入

```
5
10 2 5 4 1
```

### 输出

```
5```

## 样例 #3

### 输入

```
1
10
```

### 输出

```
1```

## 样例 #4

### 输入

```
7
3 2 1 1 4 5 1
```

### 输出

```
6```

## 样例 #5

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
5```

# AI分析结果

### 题目内容重写
#### 题目描述
Shiro刚搬到了新家，她想邀请所有的朋友来家里玩大富翁。然而，她的房子太小了，所以她一次只能邀请一个朋友。

自从Shiro搬到新家的第$n$天起，每天都会有一只猫来到Shiro的家。第$i$天来的猫的丝带颜色为$u_i$。Shiro想知道最大的数字$x$，使得如果我们考虑前$x$天的连续天数，可以从中移除恰好一天，使得剩下的$x-1$天中，每个丝带颜色出现的次数都相同。

例如，考虑以下$u_i$序列：$[2, 2, 1, 1, 5, 4, 4, 5]$。那么$x=7$是一个有效的连续天数，因为如果我们移除最左边的$u_i=5$，剩下的$x-1$天中，每个丝带颜色都恰好出现了两次。注意，$x=8$不满足条件，因为必须移除恰好一天。

由于Shiro只是一只猫，她不擅长计数，需要你帮助她找到最长的连续天数。

#### 说明/提示
在第一个例子中，我们可以选择最长的连续天数$13$，因为从这$13$天中移除最后一天后，剩下的颜色$1$、$2$、$3$和$4$都出现了$3$次。注意，连续天数也可以是$10$天（通过移除第$10$天），但我们感兴趣的是最长的连续天数。

在第四个例子中，如果我们取前$6$天的连续天数，移除第三天后，剩下的颜色$1$、$2$、$3$、$4$和$5$都恰好出现了一次。

#### 样例 #1
##### 输入
```
13
1 1 1 2 2 2 3 3 3 4 4 4 5
```
##### 输出
```
13
```

#### 样例 #2
##### 输入
```
5
10 2 5 4 1
```
##### 输出
```
5
```

#### 样例 #3
##### 输入
```
1
10
```
##### 输出
```
1
```

#### 样例 #4
##### 输入
```
7
3 2 1 1 4 5 1
```
##### 输出
```
6
```

#### 样例 #5
##### 输入
```
6
1 1 1 2 2 2
```
##### 输出
```
5
```

### 算法分类
模拟

### 题解分析与结论
题目要求找到最长的连续天数$x$，使得在前$x$天中移除恰好一天后，剩下的$x-1$天中每个颜色出现的次数都相同。题解的核心思路是通过统计每个颜色的出现次数以及每种出现次数的频率，来判断是否满足条件。

### 所选题解
#### 题解作者：ikunTLE (赞：10)
- **星级**: 4
- **关键亮点**: 使用$C_x$表示颜色$x$的出现次数，$S_y$表示出现次数为$y$的颜色的数量。通过遍历序列，更新$C_x$和$S_y$，并判断是否满足条件。代码简洁，逻辑清晰。
- **个人心得**: 特判$i=1$的情况，确保代码的鲁棒性。

#### 题解作者：_little_Cabbage_ (赞：0)
- **星级**: 4
- **关键亮点**: 详细分析了满足条件的三种情况，并通过统计每个颜色的出现次数和每种出现次数的频率来判断是否满足条件。代码实现简洁，逻辑清晰。
- **个人心得**: 通过分析三种情况，确保代码的正确性和完整性。

#### 题解作者：_Fontainebleau_ (赞：0)
- **星级**: 4
- **关键亮点**: 使用$cnt_i$表示颜色$i$的出现次数，$num_i$表示出现次数为$i$的颜色的数量。通过遍历序列，更新$cnt_i$和$num_i$，并判断是否满足条件。代码简洁，逻辑清晰。
- **个人心得**: 通过分析三种情况，确保代码的正确性和完整性。

### 关键思路与技巧
1. **统计出现次数与频率**: 使用两个数组或哈希表分别统计每个颜色的出现次数和每种出现次数的频率。
2. **条件判断**: 通过判断出现次数和频率的关系，来确定是否满足移除一天后每个颜色出现次数相同的条件。
3. **特判处理**: 特判$i=1$的情况，确保代码的鲁棒性。

### 可拓展之处
类似的问题可以通过统计频率和出现次数来解决，例如判断一个序列是否可以通过移除一个元素后满足某种条件。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 核心代码片段
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e5+10;
int a[N],sum[N],cnt[20];
int main(){
	int n=read();
	if(n==1)
		return printf("1\n"),0;
	for(int i=1;i<=n;++i)
		a[i]=read();
	--sum[cnt[a[1]]],++cnt[a[1]],++sum[cnt[a[1]]];
	int maxx=cnt[a[1]],ans=0;
	for(int i=2;i<=n;++i){
		--sum[cnt[a[i]]],++cnt[a[i]],++sum[cnt[a[i]]];
		maxx=max(maxx,cnt[a[i]]);
		if(sum[i]==1||sum[1]==i||sum[1]==1&&sum[maxx]*maxx==i-1||sum[maxx]==1&&sum[maxx-1]*(maxx-1)+maxx==i)
			ans=i;
	}
	printf("%d\n",ans);
	return 0;
}
```

---
处理用时：47.25秒