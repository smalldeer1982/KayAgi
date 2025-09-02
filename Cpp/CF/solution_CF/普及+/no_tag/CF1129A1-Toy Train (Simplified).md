# Toy Train (Simplified)

## 题目描述

Alice 有一辆玩具火车，和 $n$ 个首尾相接的站台（即火车位于第 $i$（$1\le i<n$）站台时可前往第 $i+1$ 个站台；若 $i=n$，则可前往第 $1$ 个站台。

Alice 需要用火车搬运 $m$ 个糖果，第 $i$ 个糖果需要从 $a_i$ 号站台运到 $b_i$ 号站台。火车容量无限，每到一个站台可以装上 $1$ 个糖果，也可以卸下任意多的糖果。

请你求出从每个车站出发，火车至少要经过（不包括起始站）多少个站台将每个糖果运送完毕。

## 样例 #1

### 输入

```
5 7
2 4
5 1
2 3
3 4
4 1
5 3
3 5
```

### 输出

```
10 9 10 10 9 
```

## 样例 #2

### 输入

```
2 3
1 2
1 2
1 2
```

### 输出

```
5 6 
```

# 题解

## 作者：qfpjm (赞：1)

# 题目大意

- 给定 $n$ 个点，$m$ 个糖，告诉你这个糖要从 $x$ 点拿到 $y$ 点，每次经过一个城市只能拿一个糖，但可以放任意数量的糖。只能从 $1$ 经过中间的点到 $n$，再从 $n$ 走到 $1$。问将所有糖果运送完毕至少应经过多少步。

# 题解 

-  考虑贪心+暴力，因为数据范围不大。

- 所以，我们可以按题意去模拟暴力，但是需要思考的是如果一个站有很多颗糖，应该先要装哪颗糖？

- 我们可以想一下，如果优先装离当前点最远的糖，就应该是最优了（手动模拟一下即可），剩下模拟即可。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, t;
priority_queue<int, vector<int>, less<int> > q[1005][1005];
 
int main()
{
    cin >> n >> m;
    for (int i = 1 ; i <= m ; i ++)
    {
        cin >> x >> y;
        if (y > x)
		{
			t = y - x;	
		}
        else
		{
			t = n - x + y;
		}
        for (int j = 1 ; j <= n ; j ++)
        {
            q[j][x].push(t);
		}
    }
    for (int j = 1 ; j <= n ; j ++)
    {
        int v = 0, o = 0;
        t = j - 1;
        for (int i = 1 ; ; i ++)
        {
            v --;
            t ++;
            if (v == 0 && o == m)
            {
                printf("%d ", i - 1);
                break;
            }
            if (t % n)
			{
				t = t % n;
			}
            else
			{
				t = n;
			}
            if (!q[j][t].empty())
            {
                o ++;
                int k = q[j][t].top();
                v = max(v, k);
                q[j][t].pop();
            }
        }
    }
    return 0;
}

```


---

## 作者：lovely_hyzhuo (赞：0)

这题我本来没想到贪心，因为数据范围实在是太小了，贪心一般都是 $O(n \log n)$。可是仔细一想，求最小值似乎只有动态规划和贪心。于是尝试贪心。

### 1.贪心策略

对于同一个点，手动模拟一下，可发现，优先处理离这个点最远的点，然后次远的......就是最短路径。

### 2.具体施行

优先队列求离这个点最远的点，然后暴力模拟。

细节：

1. $n$ 的下一个点是 $1$。

2. 一次只能放一个糖果。

### 3.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y,t;
}a[100010];
priority_queue <int,vector<int> > q[1010][1010];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].x>>a[i].y;
		if(a[i].y>a[i].x)
			a[i].t=a[i].y-a[i].x;
		else
			a[i].t=n+a[i].y-a[i].x;
		for(int j=1;j<=n;j++)
			q[j][a[i].x].push(a[i].t);
	}
	for(int i=1;i<=n;i++)
	{
		int l=0,c=0;
		int t=i-1;
		for(int j=1;j;j++)
		{
			l--,t++;
			if(l==0&&c==m)
			{
				cout<<j-1<<" ";
				break;
			}
			if(t%n)
				t%=n;
			else
				t=n;
			if(!q[i][t].empty())
            {
                c++;
                l=max(l,q[i][t].top());
                q[i][t].pop();
            }
		}
	}
	return 0;
}
```


---

