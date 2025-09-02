# 题目信息

# [SHOI2001] Panda的烦恼

## 题目描述

panda 是个数学怪人，他非常喜欢研究跟别人相反的事情。最近他正在研究筛法，众所周知，对一个范围内的整数，经过筛法处理以后，剩下的全部都是质数，不过 panda 对这些不感兴趣，他只对被筛掉的数感兴趣，他觉得在这些被筛掉的数中一定隐藏着重要的宇宙秘密，只是人们还没有发现罢了。

panda 还觉得如果只是单纯地从小到大筛的话，还不足够发现其中的奥秘，于是他决定对至多只包含某些质因数的数进行研究（比如说至多只包含质因数  $2,3$ 的数有  $2,3,4,6,8,9,\ldots$），他需要得到这些数中第  $k$ 小的数（ $k$ 是 panda 认为的宇宙系数），请你编个程序，帮助他找到这个数。

## 说明/提示

#### 样例解释

前六个数分别是  $3,5,9,15,25,27$。

#### 数据范围及限制

对于所有数据，有  $1\le n\le 100$， $1\le k\le 10^5$， $p_i\in\text{prime}$， $p_i\le 10^3$， $p_i\not=p_j(i\not=j)$， $1\le ans\le 2\times 10^9$。

## 样例 #1

### 输入

```
2 7
3 5```

### 输出

```
45

```

# AI分析结果

### 综合分析与结论
这些题解主要围绕寻找至多只包含某些质因数的数中第k小的数这一问题。思路上，多数题解采用优先队列（小顶堆）或类似数据结构来维护有序序列，通过不断取出最小值并生成新数加入队列，同时处理重复值问题。少数题解尝试用暴力搜索、递推等方式，但存在时间或空间复杂度高的问题。解决难点在于如何高效地生成并排序这些数，避免重复计算，同时满足数据范围和时间限制。

### 所选的题解
- **作者：piggy (5星)**
    - **关键亮点**：思路清晰，利用普通数组模拟优先队列，通过记录每个素数当前乘到的位置，每次取最小值并判重，保证生成的数组单调递增且无重复元素，时间复杂度为n*k，代码简洁高效。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include <cstdio>
int n,k,cnt;
int a[1005],b[1005],ans[100005];

int main(){
    scanf("%d%d",&n,&k);
    for (int i=1; i<=n; i++) scanf("%d",&a[i]);
    ans[0]=1;
    while (cnt<k){
        int Min=2147483647,Minx;
        for (int i=1; i<=n; i++)
            if (ans[b[i]]*a[i]<Min){
                Min=ans[b[i]]*a[i];
                Minx=i;
            }
        b[Minx]++;
        if (Min!=ans[cnt]) ans[++cnt]=Min;
    }
    printf("%d",ans[k]);
}
```
    - **核心思想**：初始化数组，通过循环每次找到当前各素数与对应位置乘积的最小值，更新位置并判重后存入结果数组，直至找到第k小的数。

- **作者：Rush_Hht (4星)**
    - **关键亮点**：详细介绍了暴力解法和正解（优先队列）的思路及代码实现，通过模拟过程帮助理解，代码结构清晰，注释详细。
    - **个人心得**：分享了比赛时从暴力到正解的学习过程。
    - **核心代码**：
```cpp
#include <iostream>
using namespace std;
int sum[111];  //储存题目限定的质数。
int ans[111111];  //储存单调递增的序列。
int position[111];  //储存当前限定质数下一次乘的位置。
int main() {
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
		cin >> sum[i];
	int now = 0;
    ans[0] = 1;
	while(now < k) {
		int Min=2147483647, Max_position;
		for(int i = 1; i <= n ; i++){
			if(ans[position[i]] * sum[i] < Min){
				Min = ans[position[i]] * sum[i];
				Max_position = i;
			}
		}
		position[Max_position]++;
		if(Min!= ans[now])  ans[++now] = Min;
	}
	cout << ans[k] <<endl;
	return 0;
}
```
    - **核心思想**：与piggy思路类似，利用优先队列思想，通过记录每个质数下一次乘的位置，每次找到最小值并判重后更新结果数组。

- **作者：麦克斯韦の妖 (4星)**
    - **关键亮点**：使用优先队列（小顶堆）解题，提出优化思路，在确定前k/2个数后，只取前5个较小的质因数与当前最小值相乘加入队列，有效减少计算量。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<string.h>
#include<cmath>
#include<queue>
#include<algorithm>
#include<deque>
#include<vector> 
using namespace std;
typedef long long ll;
priority_queue<ll,vector<ll>,greater<ll> > q;
int n,k;
int p[101];
int tot;
vector<ll> ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		q.push(p[i]);
	}
	sort(p+1,p+1+n);
	ans.push_back(0);
	while(tot<=k)
	{
		ll now=q.top();
		if(now!=ans[tot])
		{
			tot++;
			ans.push_back(now);	
			int t=n;
			if(tot>k/2)
			{
			    t=min(n,5);
			}	
			for(int i=1;i<=t;i++)
			{
				q.push(now*p[i]);
			}
		}
		q.pop();
	}
	printf("%lld\n",ans[k]);
}
```
    - **核心思想**：将质因数加入优先队列，每次取出队首判重后，根据已确定的数的数量调整与队首相乘的质因数个数，从而优化计算。

### 最优关键思路或技巧
1. **数据结构选择**：优先队列（小顶堆）适合维护有序序列，方便取出最小值并生成新数。
2. **判重处理**：通过记录上一个取出的数或使用set等数据结构避免重复值加入队列，减少无效计算。
3. **算法优化**：如麦克斯韦の妖的题解，根据已确定的数的数量，调整与当前最小值相乘的质因数个数，减少不必要的计算。

### 可拓展思路
此类题目可拓展到更多关于质因数组合、有序序列生成与查找的问题。类似算法套路包括利用优先队列、堆等数据结构维护有序性，同时结合判重、剪枝等优化技巧。

### 推荐题目
1. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)：涉及排序和最小化距离问题，可使用类似优先队列等数据结构维护有序性。
2. [P2370 [SCOI2012] 糖果传递](https://www.luogu.com.cn/problem/P2370)：需要通过数学推导和数据结构优化来解决问题，与本题优化思路有相似之处。
3. [P3378 【模板】堆](https://www.luogu.com.cn/problem/P3378)：直接考察堆的基本操作，可加深对优先队列底层实现的理解。

### 个人心得摘录与总结
1. **作者：Leap_Frog**：在解题过程中遇到多次错误，如初始认为1可构造、未开long long、超时等问题，通过不断调试和优化，如排序、记录最大值等方式最终AC。总结出做题要仔细读题，注意数据类型和范围，同时对代码进行合理优化。
2. **作者：Rush_Hht**：分享了从比赛时暴力破解到学习正解的过程，强调了理解优先队列思想在解决本题中的重要性。 

---
处理用时：36.09秒