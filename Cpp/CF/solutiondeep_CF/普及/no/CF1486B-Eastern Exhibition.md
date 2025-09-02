# 题目信息

# Eastern Exhibition

## 题目描述

You and your friends live in $ n $ houses. Each house is located on a 2D plane, in a point with integer coordinates. There might be different houses located in the same point. The mayor of the city is asking you for places for the building of the Eastern exhibition. You have to find the number of places (points with integer coordinates), so that the summary distance from all the houses to the exhibition is minimal. The exhibition can be built in the same point as some house. The distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ , where $ |x| $ is the absolute value of $ x $ .

## 说明/提示

Here are the images for the example test cases. Blue dots stand for the houses, green — possible positions for the exhibition.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/ef8e7107a46bf60bf70b2b89dad798828df776de.png)

First test case.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/3bfbc5c12bc5661837030d46309064e5728abb33.png)

Second test case. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/f4355abdf55b6e2aba57eaba9ac1bd5b3e9a9937.png)

Third test case. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/7ac3252595a464db25ea4d6a5a88bb674df5da85.png)

Fourth test case. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/2ad0e39ceaeb8df93cdbdc07468766d61acf71ed.png)

Fifth test case. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/bf530ae677a95adfe7eacb87263816efab51ccdb.png)

Sixth test case. Here both houses are located at $ (0, 0) $ .

## 样例 #1

### 输入

```
6
3
0 0
2 0
1 2
4
1 0
0 2
2 3
3 1
4
0 0
0 1
1 0
1 1
2
0 0
1 1
2
0 0
2 0
2
0 0
0 0```

### 输出

```
1
4
4
4
3
1```

# AI分析结果

### 题目内容重写

# 东方展览

## 题目描述

你和你的朋友们住在 $n$ 栋房子里。每栋房子位于二维平面上的一个整数坐标点。可能有多个房子位于同一个点。市长要求你为东方展览选择一个建筑地点。你需要找到使得所有房子到展览地点的曼哈顿距离之和最小的整数坐标点的数量。展览地点可以与某个房子的位置相同。两个点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 之间的距离为 $|x_1 - x_2| + |y_1 - y_2|$，其中 $|x|$ 是 $x$ 的绝对值。

## 说明/提示

以下是示例测试用例的图片。蓝点代表房子，绿点代表可能的展览地点。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/ef8e7107a46bf60bf70b2b89dad798828df776de.png)

第一个测试用例。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/3bfbc5c12bc5661837030d46309064e5728abb33.png)

第二个测试用例。 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/f4355abdf55b6e2aba57eaba9ac1bd5b3e9a9937.png)

第三个测试用例。 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/7ac3252595a464db25ea4d6a5a88bb674df5da85.png)

第四个测试用例。 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/2ad0e39ceaeb8df93cdbdc07468766d61acf71ed.png)

第五个测试用例。 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/bf530ae677a95adfe7eacb87263816efab51ccdb.png)

第六个测试用例。这里两栋房子都位于 $(0, 0)$。

## 样例 #1

### 输入

```
6
3
0 0
2 0
1 2
4
1 0
0 2
2 3
3 1
4
0 0
0 1
1 0
1 1
2
0 0
1 1
2
0 0
2 0
2
0 0
0 0```

### 输出

```
1
4
4
4
3
1```

### 算法分类
数学

### 题解分析与结论

本题的核心在于利用曼哈顿距离的性质，将二维问题分解为两个独立的一维问题。通过排序和计算中位数，可以快速找到使得距离和最小的点。具体来说，对于奇数个点，中位数即为最优解；对于偶数个点，最优解位于中间两个点之间的所有整数点。

### 所选高星题解

#### 题解1：作者：pomelo_nene (赞：6)
- **星级**：5星
- **关键亮点**：清晰地将问题分解为两个独立的一维问题，并利用中位数的性质快速求解。代码简洁，逻辑清晰。
- **代码核心思想**：
  - 对x和y坐标分别排序。
  - 如果n为奇数，答案为1；否则计算中间两个点的区间长度，乘积即为答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL x[1005],y[1005],n;
int main(){
	LL T;
	scanf("%lld",&T);
	while(T-->0)
	{
		scanf("%lld",&n);
		for(LL i=1;i<=n;++i)	scanf("%lld %lld",&x[i],&y[i]);
		if(n&1)
		{
			puts("1");
			continue;
		}
		sort(x+1,x+1+n),sort(y+1,y+1+n);
		LL sx=x[n/2+1]-x[n/2]+1,sy=y[n/2+1]-y[n/2]+1;
		printf("%lld\n",sx*sy);
	}
	return 0;
}
```

#### 题解2：作者：BrotherCall (赞：4)
- **星级**：4星
- **关键亮点**：详细解释了曼哈顿距离的性质，并通过图示帮助理解。代码实现简洁，逻辑清晰。
- **代码核心思想**：
  - 对x和y坐标分别排序。
  - 如果n为奇数，答案为1；否则计算中间两个点的区间长度，乘积即为答案。
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;

int T,n;
ll x[1010],y[1010],ans1,ans2,a,b;

int main(){
	cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&a,&b);
			x[i] = a;
			y[i] = b;
		}
		if(n & 1 == 1){
			cout<<1<<endl;
			continue;
		}
		sort(x + 1,x + 1 + n);
		sort(y + 1,y + 1 + n);
		ans1 = x[n/2+1] - x[n/2] + 1;
		ans2 = y[n/2+1] - y[n/2] + 1;
		cout<<ans1 * ans2<<endl;
	}
	return 0;
}
```

#### 题解3：作者：Rolling_L (赞：1)
- **星级**：4星
- **关键亮点**：简洁明了地解释了曼哈顿距离的性质，并通过排序和中位数快速求解。代码实现简洁。
- **代码核心思想**：
  - 对x和y坐标分别排序。
  - 如果n为奇数，答案为1；否则计算中间两个点的区间长度，乘积即为答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x[1005];
long long y[1005];
int T;
int main(){
	cin>>T;
	while(T--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d",&x[i],&y[i]);
		}
		if(n%2){
			printf("1\n");
			continue;
		}
		sort(x+1,x+n+1);
		sort(y+1,y+n+1);
		printf("%lld\n",(x[n/2+1]-x[n/2]+1ll)*(y[n/2+1]-y[n/2]+1ll));
	}
	return 0;
}
```

### 最优关键思路与技巧
1. **曼哈顿距离的性质**：将二维问题分解为两个独立的一维问题，分别处理x和y坐标。
2. **中位数的应用**：对于奇数个点，中位数即为最优解；对于偶数个点，最优解位于中间两个点之间的所有整数点。
3. **排序与区间计算**：通过排序快速找到中位数，并计算区间长度。

### 可拓展之处
类似的问题可以扩展到更高维度，依然可以通过分解为多个独立的一维问题来解决。此外，曼哈顿距离的性质在其他优化问题中也有广泛应用，如物流路径优化、机器人导航等。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：57.50秒