# 题目信息

# Diagonal Walking v.2

## 题目描述

Mikhail walks on a Cartesian plane. He starts at the point $ (0, 0) $ , and in one move he can go to any of eight adjacent points. For example, if Mikhail is currently at the point $ (0, 0) $ , he can go to any of the following points in one move:

- $ (1, 0) $ ;
- $ (1, 1) $ ;
- $ (0, 1) $ ;
- $ (-1, 1) $ ;
- $ (-1, 0) $ ;
- $ (-1, -1) $ ;
- $ (0, -1) $ ;
- $ (1, -1) $ .

If Mikhail goes from the point $ (x1, y1) $ to the point $ (x2, y2) $ in one move, and $ x1 \ne x2 $ and $ y1 \ne y2 $ , then such a move is called a diagonal move.

Mikhail has $ q $ queries. For the $ i $ -th query Mikhail's target is to go to the point $ (n_i, m_i) $ from the point $ (0, 0) $ in exactly $ k_i $ moves. Among all possible movements he want to choose one with the maximum number of diagonal moves. Your task is to find the maximum number of diagonal moves or find that it is impossible to go from the point $ (0, 0) $ to the point $ (n_i, m_i) $ in $ k_i $ moves.

Note that Mikhail can visit any point any number of times (even the destination point!).

## 说明/提示

One of the possible answers to the first test case: $ (0, 0) \to (1, 0) \to (1, 1) \to (2, 2) $ .

One of the possible answers to the second test case: $ (0, 0) \to (0, 1) \to (1, 2) \to (0, 3) \to (1, 4) \to (2, 3) \to (3, 2) \to (4, 3) $ .

In the third test case Mikhail cannot reach the point $ (10, 1) $ in 9 moves.

## 样例 #1

### 输入

```
3
2 2 3
4 3 7
10 1 9
```

### 输出

```
1
6
-1
```

# AI分析结果

### 中文重写题目内容

# 对角线行走 v.2

## 题目描述

Mikhail 在笛卡尔平面上行走。他从点 $ (0, 0) $ 开始，每次移动可以走到八个相邻的点之一。例如，如果 Mikhail 当前在点 $ (0, 0) $，他可以在一次移动中走到以下任意一个点：

- $ (1, 0) $ ;
- $ (1, 1) $ ;
- $ (0, 1) $ ;
- $ (-1, 1) $ ;
- $ (-1, 0) $ ;
- $ (-1, -1) $ ;
- $ (0, -1) $ ;
- $ (1, -1) $ .

如果 Mikhail 从点 $ (x1, y1) $ 移动到点 $ (x2, y2) $，并且 $ x1 \ne x2 $ 且 $ y1 \ne y2 $，那么这样的移动称为对角线移动。

Mikhail 有 $ q $ 个查询。对于第 $ i $ 个查询，Mikhail 的目标是从点 $ (0, 0) $ 出发，在恰好 $ k_i $ 步内到达点 $ (n_i, m_i) $。在所有可能的移动中，他希望选择一种对角线移动次数最多的方案。你的任务是找出最大可能的对角线移动次数，或者判断是否无法在 $ k_i $ 步内从点 $ (0, 0) $ 到达点 $ (n_i, m_i) $。

注意，Mikhail 可以多次访问任意点（包括目标点）。

## 说明/提示

第一个测试用例的一个可能答案：$ (0, 0) \to (1, 0) \to (1, 1) \to (2, 2) $。

第二个测试用例的一个可能答案：$ (0, 0) \to (0, 1) \to (1, 2) \to (0, 3) \to (1, 4) \to (2, 3) \to (3, 2) \to (4, 3) $。

在第三个测试用例中，Mikhail 无法在 9 步内到达点 $ (10, 1) $。

## 样例 #1

### 输入

```
3
2 2 3
4 3 7
10 1 9
```

### 输出

```
1
6
-1
```

### 算法分类
数学

### 题解分析与结论

本题的核心在于如何通过分类讨论来确定在给定步数内到达目标点的最大对角线移动次数。所有题解都基于以下两个关键点进行讨论：
1. **无解情况**：当步数 $k$ 小于 $\max(n, m)$ 时，无法到达目标点，输出 $-1$。
2. **有解情况**：根据 $\max(n, m) - \min(n, m)$ 的奇偶性以及 $k$ 与 $\max(n, m)$ 的关系，确定最大对角线移动次数。

### 评分较高的题解

#### 题解1：作者：封禁用户 (赞：5)
- **星级**：4.5
- **关键亮点**：通过详细的分类讨论，清晰地解释了每种情况下的最大对角线移动次数，并提供了直观的图示辅助理解。
- **个人心得**：作者提到在考试时犯迷糊，但通过静心思考最终AC，强调了冷静分析的重要性。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,k;
int main(){
    scanf("%lld",&t);
    while(t--){
    	bool flag=0;
        scanf("%lld%lld%lld",&n,&m,&k);
        if(k<max(n,m)&&flag==0){
        	cout<<"-1\n";
        	flag=1;
        }
        if((max(n,m)-min(n,m))%2&&flag==0){
        	cout<<k-1<<"\n";
        	flag=1;
        }
        else if(flag==0){
            if((min(n,m)-k)%2) cout<<k-2<<"\n";
            else cout<<k<<"\n";
			flag=1;
        }
    }
}
```

#### 题解2：作者：Light_Pursuer (赞：1)
- **星级**：4
- **关键亮点**：简洁明了地分类讨论了无解和有解的情况，代码实现简洁高效。
- **个人心得**：无

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int ret=0,f=1;char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') 
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*f;
}
int n,m,k;
signed main()
{
	int t;t=read();
    while(t--)
	{
    	n=read(),m=read(),k=read();
        if(k<max(n,m))
		{
        	cout<<"-1"<<endl;
        	continue;
        }
        if((max(n,m)-min(n,m))%2)
		{
        	cout<<k-1<<endl;
        	continue;
        }
        else
		{
            if((min(n,m)-k)%2) 
			{
				cout<<k-2<<"\n";	
			}
            else 
			{
				cout<<k<<"\n";
			}
        }
    }
    return 0;
}
```

#### 题解3：作者：Alloverzyt (赞：1)
- **星级**：4
- **关键亮点**：通过图示和详细的解释，帮助读者理解如何通过增加一步来调整对角线移动次数，思路清晰。
- **个人心得**：作者提到自己在理解某些细节时有些迷糊，但通过画图和分析最终理解了问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,k;
int main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld%lld%lld",&n,&m,&k);
        if(k<max(n,m)){
        	printf("-1\n");
        	continue; 
        }
        if((max(n,m)-min(n,m))%2==1) k--;
        else if((k-max(n,m))%2==1) k-=2;
        printf("%lld\n",k);
    }
	return 0;
}
```

### 最优关键思路或技巧
1. **分类讨论**：根据 $\max(n, m) - \min(n, m)$ 的奇偶性以及 $k$ 与 $\max(n, m)$ 的关系，确定最大对角线移动次数。
2. **图示辅助理解**：通过图示帮助理解如何通过增加一步来调整对角线移动次数。

### 可拓展之处
类似的问题可以通过分类讨论和图示辅助理解来解决，尤其是在涉及步数和移动方向的问题中。

### 推荐题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

---
处理用时：52.09秒