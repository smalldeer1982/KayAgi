# Morning Jogging

## 题目描述

The 2050 volunteers are organizing the "Run! Chase the Rising Sun" activity. Starting on Apr 25 at 7:30 am, runners will complete the 6km trail around the Yunqi town.

There are $ n+1 $ checkpoints on the trail. They are numbered by $ 0 $ , $ 1 $ , ..., $ n $ . A runner must start at checkpoint $ 0 $ and finish at checkpoint $ n $ . No checkpoint is skippable — he must run from checkpoint $ 0 $ to checkpoint $ 1 $ , then from checkpoint $ 1 $ to checkpoint $ 2 $ and so on. Look at the picture in notes section for clarification.

Between any two adjacent checkpoints, there are $ m $ different paths to choose. For any $ 1\le i\le n $ , to run from checkpoint $ i-1 $ to checkpoint $ i $ , a runner can choose exactly one from the $ m $ possible paths. The length of the $ j $ -th path between checkpoint $ i-1 $ and $ i $ is $ b_{i,j} $ for any $ 1\le j\le m $ and $ 1\le i\le n $ .

To test the trail, we have $ m $ runners. Each runner must run from the checkpoint $ 0 $ to the checkpoint $ n $ once, visiting all the checkpoints. Every path between every pair of adjacent checkpoints needs to be ran by exactly one runner. If a runner chooses the path of length $ l_i $ between checkpoint $ i-1 $ and $ i $ ( $ 1\le i\le n $ ), his tiredness is $ $$$\min_{i=1}^n l_i, $ $  i. e. the minimum length of the paths he takes.</p><p>Please arrange the paths of the  $ m$$$ runners to minimize the sum of tiredness of them.

## 说明/提示

In the first case, the sum of tiredness is $ \min(2,5) + \min(3,3) + \min(4,1) = 6 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517B/81bbf44dba6a58e8432744a5a3d75d6c54d8fb12.png)In the second case, the sum of tiredness is $ \min(2,4,3) + \min(3,1,5) = 3 $ .

## 样例 #1

### 输入

```
2
2 3
2 3 4
1 3 5
3 2
2 3
4 1
3 5```

### 输出

```
2 3 4
5 3 1
2 3
4 1
3 5```

# 题解

## 作者：BorisDimitri (赞：14)

# 题意
一场马拉松有 $n$ 个报道点，相邻两个报道点之间有 $m$ 条路径。

现在有 $m$ 个选手，每个选手都要跑完这场马拉松。

定义选手的 **疲累值** 为他跑过的相邻两个报道点之间最短的一条路径的长度。

请你安排路径，使得选手的总疲累值最小。

# 分析
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1517B/81bbf44dba6a58e8432744a5a3d75d6c54d8fb12.png)

看样例的这个图。

因为我们只要的最小值的值，所以 **同一行中的最小值出现在哪一列并不影响答案**。

由于同一列上的数可以上下交换，**所以同一列中的最小值出现在那一行也不影响答案**。

我们只要将 **前 $m$ 小的数分别放在不同的行中**，就可以得到最小的疲累总值。
至于其他的位置，可以随便放置，不影响答案。

要注意一点，输入的时候，行列和我们上面分析时的是相反的。

(即输入的行是我们分析时的列，输入的列是我们分析时的行)

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 105;

struct Node
{
    int row,col;//行，列
    int value;
}tired[N*N];

int n,m;
int idx = 0;
int ans[N][N];

bool cmp(Node x,Node y)
{
    return x.value < y.value;
}

int main()
{
    int t;
    scanf("%d",&t);

    while(t--)
    {
        memset(ans,0,sizeof ans);
        idx = 0;

        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                tired[++idx].col=j,tired[idx].row=i,scanf("%d",&tired[idx].value);

        sort(tired+1,tired+idx+1,cmp);


        for(int j=1;j<=m;j++)//放置前m小的在不同的行里
        {
            ans[tired[j].row][j] = tired[j].value;
        }

        //除了前m小的，都可以随便放，不影响答案
        //这里为了方便，就按照排好后的顺序来放
        for(int i=m+1;i<=idx;i++)
            for(int k=1;k<=m;k++)
                if(ans[tired[i].row][k] == 0) 
                {
                    ans[tired[i].row][k] = tired[i].value;
                    break;
                }
            

        for(int i=1;i<=n;i++) // 输出答案
        {
            for(int j=1;j<=m;j++)
                printf("%d ",ans[i][j]);
            putchar('\n');
        }
    }

    return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF1517B)

------------
# 思路：
对全部数据进行从小到大排序 $b$，然后对每一行进行从大到小排序 $a$，$n \times m$ 次循环中 找 $b$ 中前 $m$ 个数中（$m$ 个数放置在 $m$ 列）。

对应于此时行标的值，作为该列的最小值，这样 $b$ 中前 $m$ 个数就分配在不同行不同列了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int a[110][110];
int c[110];
bool cmp2(int x,int y)
{
	return x>y;
}
struct node
{
	int num;///value
	int x,y;///row column
}b[10010];
bool cmp(node a,node b)
{
	return a.num<b.num;
} 
int main() {
	int t;
	cin>>t;
	while(t--) {
		int n,m;
		cin>>n>>m;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++) {
				cin>>a[i][j];
				b[i*m+j].num=a[i][j];
				b[i*m+j].x=i;
				b[i*m+j].y=j;
			}
			sort(a[i],a[i]+m,cmp2);///每行排序   big-->small
		}
		sort(b,b+n*m,cmp);///small-->big
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(b[j].x==i)
				cout<<b[j].num<<" ";///find the j column's minn value
				else cout<<a[i][c[i]++]<<" ";///大到小输出 
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

