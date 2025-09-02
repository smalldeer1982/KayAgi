# 题目信息

# Mittens

## 题目描述

A Christmas party in city S. had $ n $ children. All children came in mittens. The mittens can be of different colors, but each child had the left and the right mitten of the same color. Let's say that the colors of the mittens are numbered with integers from 1 to $ m $ , and the children are numbered from 1 to $ n $ . Then the $ i $ -th child has both mittens of color $ c_{i} $ .

The Party had Santa Claus ('Father Frost' in Russian), his granddaughter Snow Girl, the children danced around the richly decorated Christmas tree. In fact, everything was so bright and diverse that the children wanted to wear mittens of distinct colors. The children decided to swap the mittens so that each of them got one left and one right mitten in the end, and these two mittens were of distinct colors. All mittens are of the same size and fit all the children.

The children started exchanging the mittens haphazardly, but they couldn't reach the situation when each child has a pair of mittens of distinct colors. Vasily Petrov, the dad of one of the children, noted that in the general case the children's idea may turn out impossible. Besides, he is a mathematician and he came up with such scheme of distributing mittens that the number of children that have distinct-colored mittens was maximum. You task is to repeat his discovery. Note that the left and right mittens are different: each child must end up with one left and one right mitten.

## 样例 #1

### 输入

```
6 3
1 3 2 2 1 1
```

### 输出

```
6
2 1
1 2
2 1
1 3
1 2
3 1
```

## 样例 #2

### 输入

```
4 2
1 2 1 1
```

### 输出

```
2
1 2
1 1
2 1
1 1
```

# AI分析结果

### 题目内容
# Mittens

## 题目描述
在S市的一场圣诞派对上，有$n$个孩子。所有孩子都戴着手套，手套颜色可能不同，但每个孩子的左手和右手手套颜色相同。假设手套颜色用从1到$m$的整数编号，孩子们从1到$n$编号。那么第$i$个孩子的两只手套颜色均为$c_{i}$。

派对上有圣诞老人（俄语中为“Father Frost”）、他的孙女雪姑娘，孩子们围着装饰华丽的圣诞树跳舞。事实上，一切都如此明亮多彩，以至于孩子们想戴上不同颜色的手套。孩子们决定交换手套，以便最后每个孩子都能得到一只左手手套和一只右手手套，且这两只手套颜色不同。所有手套大小相同，适合所有孩子。

孩子们开始随意交换手套，但他们无法达到每个孩子都有一双不同颜色手套的情况。其中一个孩子的父亲瓦西里·彼得罗夫指出，一般情况下，孩子们的想法可能无法实现。此外，他是一位数学家，他想出了一种分配手套的方案，使得拥有不同颜色手套的孩子数量最多。你的任务是重复他的发现。注意，左手手套和右手手套是不同的：每个孩子最终必须得到一只左手手套和一只右手手套。

## 样例 #1
### 输入
```
6 3
1 3 2 2 1 1
```
### 输出
```
6
2 1
1 2
2 1
1 3
1 2
3 1
```

## 样例 #2
### 输入
```
4 2
1 2 1 1
```
### 输出
```
2
1 2
1 1
2 1
1 1
```

### 算法分类
贪心

### 题解综合分析与结论
这两篇题解思路基本一致，核心思路都是先通过统计颜色出现次数来确定最多能有多少孩子拿到不同颜色的手套，然后通过暴力枚举交换手套来构造满足条件的方案。主要难点在于理解如何根据颜色出现的最大次数来确定不同色手套孩子的最大数量，以及如何通过合理交换来实现方案。

### 题解1（作者：_HMZ_  赞：0）
- **星级**：3星
- **关键亮点**：思路较为清晰，代码实现简洁明了，通过注释对关键步骤进行了说明。
```cpp
#include<iostream>
using namespace std;
int n,m,x[10005],y[10005],cnt[10005],maxx;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i];
        y[i]=x[i];
        cnt[x[i]]+=2;//注意是一双手套，实际有两只。
        maxx=max(maxx,cnt[x[i]]);//统计上文的w。
    }
    if(maxx<=n)
        cout<<n<<endl;
    else
        cout<<2*n-maxx<<endl;
    for(int i=1;i<=n;i++)
    {
        if(x[i]!=y[i])  continue;//当前枚举到的人手套已经不同色，则不交换。
        for(int j=1;j<=n;j++)
        {
            if(x[j]!=y[i] && x[i]!=y[j])//交换之后两人都能手套不同色。
                swap(x[i],x[j]);
            else if(x[i]!=y[j] && x[j]!=y[i])
                swap(y[i],y[j]);
        }
    }
    for(int i=1;i<=n;i++)
        cout<<x[i]<<' '<<y[i]<<endl;
    return 0;
}
```
核心实现思想：先统计每种颜色手套的总数（因为每人有两只同色手套所以每次加2），找到出现次数最多的颜色数量maxx，根据maxx与n的关系确定不同色手套孩子的最大数量。然后双重循环枚举孩子，若当前孩子手套同色则尝试与其他孩子交换，使双方手套都不同色。

### 题解2（作者：Allanljx  赞：0）
- **星级**：3星
- **关键亮点**：同样思路清晰，代码逻辑简洁，变量命名较为直观。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[5005],sum[105],maxn;
int l[5005],r[5005];//l表示左手的颜色，r表示右手的颜色
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		l[i]=r[i]=a[i];
		sum[a[i]]+=2;
		maxn=max(maxn,sum[a[i]]);//某一颜色的数量
	}
	if(maxn<=n) printf("%d\n",n);
	else printf("%d\n",2*n-maxn);
	for(int i=1;i<=n;i++)//暴力交换
	{
		if(l[i]!=r[i]) continue;
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			if(l[i]!=r[j]&&l[j]!=r[i]) swap(l[i],l[j]);//交换左手
			else if(l[j]!=r[i]&&l[i]!=r[j]) swap(r[i],r[j]);//交换右手
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d %d\n",l[i],r[i]);//最终颜色
	}
}
```
核心实现思想：与题解1类似，先统计每种颜色手套总数找到最大数量maxn，根据maxn与n的关系确定不同色手套孩子最大数量。之后通过双重循环枚举孩子，若当前孩子手套同色则尝试与其他孩子交换左手或右手手套，使双方手套都不同色。

### 最优关键思路或技巧
1. **统计颜色数量**：通过数组记录每种颜色手套的数量，方便后续判断和计算。
2. **贪心策略**：优先满足尽可能多的孩子拿到不同颜色手套，先根据颜色出现的最大次数确定不同色手套孩子的最大数量，再通过暴力交换来实现方案。

### 拓展思路
此类题目属于贪心策略在实际场景中的应用，类似题目通常会给出一些资源分配的条件，要求在满足一定限制下达到某个最优目标。解题关键在于找到合适的贪心策略，比如根据某种资源的数量来决定分配方式。

### 洛谷相似题目推荐
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序实现贪心策略来解决问题。
2. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析游戏规则，利用贪心思想找到最优策略。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间的长短进行排序，运用贪心策略求解。 

---
处理用时：61.20秒