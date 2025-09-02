# 题目信息

# Minimum Diameter Tree

## 题目描述

You are given a tree (an undirected connected graph without cycles) and an integer $ s $ .

Vanya wants to put weights on all edges of the tree so that all weights are non-negative real numbers and their sum is $ s $ . At the same time, he wants to make the diameter of the tree as small as possible.

Let's define the diameter of a weighed tree as the maximum sum of the weights of the edges lying on the path between two some vertices of the tree. In other words, the diameter of a weighed tree is the length of the longest simple path in the tree, where length of a path is equal to the sum of weights over all edges in the path.

Find the minimum possible diameter that Vanya can get.

## 说明/提示

In the first example it is necessary to put weights like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085D/c1a70d116ee899735bc4ecf7ff6c6bf75b292051.png)It is easy to see that the diameter of this tree is $ 2 $ . It can be proved that it is the minimum possible diameter.

In the second example it is necessary to put weights like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085D/7a6a70a648e37d9e55f1bb9aed6b2be7637ee566.png)

## 样例 #1

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
2.000000000000000000```

## 样例 #2

### 输入

```
6 1
2 1
2 3
2 5
5 4
5 6
```

### 输出

```
0.500000000000000000```

## 样例 #3

### 输入

```
5 5
1 2
2 3
3 4
3 5
```

### 输出

```
3.333333333333333333```

# AI分析结果

### 题目内容
# 最小直径树

## 题目描述
给定一棵树（一个无环的无向连通图）和一个整数 $s$ 。

万尼亚想给树的所有边赋予权重，使得所有权重都是非负实数且它们的和为 $s$ 。同时，他想使树的直径尽可能小。

我们将加权树的直径定义为树中两个顶点之间路径上的边权重之和的最大值。换句话说，加权树的直径是树中最长简单路径的长度，其中路径的长度等于路径上所有边的权重之和。

求万尼亚能得到的最小可能直径。

## 说明/提示
在第一个示例中，必须按如下方式赋予权重：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085D/c1a70d116ee899735bc4ecf7ff6c6bf75b292051.png)
很容易看出，这棵树的直径是 $2$ 。可以证明这是最小可能的直径。

在第二个示例中，必须按如下方式赋予权重：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085D/7a6a70a648e37d9e55f1bb9aed6b2be7637ee566.png)

## 样例 #1
### 输入
```
4 3
1 2
1 3
1 4
```
### 输出
```
2.000000000000000000
```
## 样例 #2
### 输入
```
6 1
2 1
2 3
2 5
5 4
5 6
```
### 输出
```
0.500000000000000000
```
## 样例 #3
### 输入
```
5 5
1 2
2 3
3 4
3 5
```
### 输出
```
3.333333333333333333
```

### 算法分类
贪心

### 综合分析与结论
这些题解思路较为统一，均认为连接叶子节点的边对树直径影响最小，应将总边权 $s$ 平均分配到连接叶子节点的边，其他边权设为 0 ，此时树的直径为 $\frac{2s}{cnt}$（$cnt$ 为叶子节点数）。算法要点在于统计叶子节点数量，难点主要是证明该贪心策略的正确性。部分题解通过反证法，分情况讨论改变边权后对直径的影响来证明；部分题解仅从感性上分析。

### 所选的题解
- **作者：shiroi (赞：3)  星级：4星**
    - **关键亮点**：思路清晰，代码简洁明了，直接给出关键结论并实现。
    - **重点代码核心实现思想**：通过 `deg` 数组统计每个节点的度，遍历节点找出度为 1 的叶子节点并计数，最后根据公式计算并输出结果。
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int x=0,f=1,c=getchar();
    while(c<48) c=='-'&&(f=-1),c=getchar();
    while(c>47) x=x*10+c-'0',c=getchar();
    return x*f;
}

const int MAXN = 100005;
int deg[MAXN];
int n,s,tot;

int main(int argc, char const *argv[])
{
    n=read(); s=read()<<1;
    for(int i=1; i<n; ++i)
        ++deg[read()],++deg[read()];
    for(int i=1; i<=n; ++i)
        if(deg[i]==1) ++tot;
    printf("%.8lf", (double)s/tot);
    return 0;
}
```
- **作者：ChpyX2 (赞：0)  星级：4星**
    - **关键亮点**：不仅给出解题思路，还通过反证法详细证明了贪心策略的正确性，逻辑严谨。
    - **重点代码核心实现思想**：利用 `d` 数组统计各节点度数，遍历找出度为 1 的叶子节点计数，按公式计算并输出答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int d[maxn],u,v,n;
double s,c;
int main(){
    cin>>n>>s;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        d[u]++;
        d[v]++;//计算度数
    }
    for(int i=1;i<=n;i++)if(d[i]==1)c++;//度数为1的就是叶子节点,相应的有一条叶子边
    printf("%.10f",s/c*2);
    return 0;
}
```
- **作者：clownor (赞：0)  星级：4星**
    - **关键亮点**：先感性分析得出结论，再详细分类证明结论的正确性，对特殊情况讨论较为细致。
    - **重点代码核心实现思想**：通过 `du` 数组统计节点度数，找出叶子节点计数，按公式计算并输出结果。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define int long long
using namespace std;
int read()
{
	int fl=1,v=0;
	char c=getchar();
	while (c!='-'&&(c<'0'||c>'9')) c=getchar();
	if (c=='-')
	{
		c=getchar();
		fl=-1; 
	}
	while (c>='0'&&c<='9')
	{
		v=v*10+c-'0';
		c=getchar();
	}
	return v*fl;
}
int n,s,du[100005];
signed main()
{
	n=read(),s=read();
	for (int i=1;i<n;i++)
	{
		int x=read(),y=read();
		du[x]++,du[y]++;
	}
	int cnt=0;
	for (int i=1;i<=n;i++) if (du[i]==1)
	{
		cnt++;
	}
	double ans=2.0*s/cnt;
	printf("%.10lf",ans);
	return 0;
}
```

### 最优关键思路或技巧
本题关键在于通过分析得出将边权集中分配到连接叶子节点的边可使树直径最小这一贪心策略，并能严谨证明其正确性。在实现上，利用统计节点度数来确定叶子节点数量的方法简单有效。

### 拓展
同类型题常围绕树的性质和边权分配展开，类似算法套路是对树的结构特点进行分析，结合贪心思想寻找最优的边权分配方式。例如在一些题目中，可能需要根据树的深度、节点层次等因素进行边权分配以优化某个指标。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序实现贪心策略，与本题类似，需分析问题找到最优的决策方式。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：运用贪心算法解决调度问题，同样要思考如何通过合理分配资源达到最优结果。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：需通过推导证明贪心策略的正确性，进而解决双属性排序问题，与本题证明贪心策略正确性有相似之处。

### 个人心得摘录与总结
- **作者：GoodLuckCat**：一开始 WA 在第八个点，后来发现是精度问题。总结：在涉及浮点数计算和输出的题目中，要特别注意精度设置，避免因精度问题导致答案错误。 

---
处理用时：77.42秒