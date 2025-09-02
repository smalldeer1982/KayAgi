# 题目信息

# Seating Arrangements (hard version)

## 题目描述

It is the hard version of the problem. The only difference is that in this version $ 1 \le n \le 300 $ .

In the cinema seats can be represented as the table with $ n $ rows and $ m $ columns. The rows are numbered with integers from $ 1 $ to $ n $ . The seats in each row are numbered with consecutive integers from left to right: in the $ k $ -th row from $ m (k - 1) + 1 $ to $ m k $ for all rows $ 1 \le k \le n $ .

  $ 1 $

 $ 2 $  $ \cdots $  $ m - 1 $  $ m $  $ m + 1 $

 $ m + 2 $  $ \cdots $  $ 2 m - 1 $  $ 2 m $  $ 2m + 1 $

 $ 2m + 2 $  $ \cdots $  $ 3 m - 1 $  $ 3 m $  $ \vdots $

 $ \vdots $  $ \ddots $  $ \vdots $  $ \vdots $  $ m (n - 1) + 1 $

 $ m (n - 1) + 2 $  $ \cdots $  $ n m - 1 $  $ n m $ The table with seats indicesThere are $ nm $ people who want to go to the cinema to watch a new film. They are numbered with integers from $ 1 $ to $ nm $ . You should give exactly one seat to each person.

It is known, that in this cinema as lower seat index you have as better you can see everything happening on the screen. $ i $ -th person has the level of sight $ a_i $ . Let's define $ s_i $ as the seat index, that will be given to $ i $ -th person. You want to give better places for people with lower sight levels, so for any two people $ i $ , $ j $ such that $ a_i < a_j $ it should be satisfied that $ s_i < s_j $ .

After you will give seats to all people they will start coming to their seats. In the order from $ 1 $ to $ nm $ , each person will enter the hall and sit in their seat. To get to their place, the person will go to their seat's row and start moving from the first seat in this row to theirs from left to right. While moving some places will be free, some will be occupied with people already seated. The inconvenience of the person is equal to the number of occupied seats he or she will go through.

Let's consider an example: $ m = 5 $ , the person has the seat $ 4 $ in the first row, the seats $ 1 $ , $ 3 $ , $ 5 $ in the first row are already occupied, the seats $ 2 $ and $ 4 $ are free. The inconvenience of this person will be $ 2 $ , because he will go through occupied seats $ 1 $ and $ 3 $ .

Find the minimal total inconvenience (the sum of inconveniences of all people), that is possible to have by giving places for all people (all conditions should be satisfied).

## 说明/提示

In the first test case, there is a single way to give seats: the first person sits in the first place and the second person — in the second. The total inconvenience is $ 1 $ .

In the second test case the optimal seating looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566D2/80308625ebb7c50e30fb4af9e2e0a85ec7f6e480.png)In the third test case the optimal seating looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566D2/46f26744e5411d13af43bc68c4d54fb7352debca.png)The number in a cell is the person's index that sits on this place.

## 样例 #1

### 输入

```
7
1 2
1 2
3 2
1 1 2 2 3 3
3 3
3 4 4 1 1 1 1 1 2
2 2
1 1 2 1
4 2
50 50 50 50 3 50 50 50
4 2
6 6 6 6 2 2 9 6
2 9
1 3 3 3 3 3 1 1 3 1 3 1 1 3 3 1 1 3```

### 输出

```
1
0
4
0
0
0
1```

# AI分析结果

### 题目中文重写
# 座位安排（困难版本）

## 题目描述
这是该问题的困难版本。唯一的区别在于，在这个版本中 $1 \le n \le 300$。

在电影院中，座位可以用一个有 $n$ 行和 $m$ 列的表格来表示。行用从 $1$ 到 $n$ 的整数编号。每行的座位从左到右用连续的整数编号：在第 $k$ 行中，座位编号从 $m (k - 1) + 1$ 到 $m k$，其中 $1 \le k \le n$。

  $1$

 $2$  $ \cdots $  $ m - 1 $  $ m $  $ m + 1 $

 $ m + 2 $  $ \cdots $  $ 2 m - 1 $  $ 2 m $  $ 2m + 1 $

 $ 2m + 2 $  $ \cdots $  $ 3 m - 1 $  $ 3 m $  $ \vdots $

 $ \vdots $  $ \ddots $  $ \vdots $  $ \vdots $  $ m (n - 1) + 1 $

 $ m (n - 1) + 2 $  $ \cdots $  $ n m - 1 $  $ n m $ （座位索引表格）

有 $nm$ 个人想去电影院看一部新电影。他们用从 $1$ 到 $nm$ 的整数编号。你应该给每个人恰好分配一个座位。

已知在这个电影院中，座位编号越小，你就越能清楚地看到屏幕上发生的一切。第 $i$ 个人的视力水平为 $a_i$。设 $s_i$ 为分配给第 $i$ 个人的座位编号。你想给视力水平较低的人分配更好的座位，所以对于任意两个满足 $a_i < a_j$ 的人 $i$ 和 $j$，应该满足 $s_i < s_j$。

在你给所有人分配好座位后，他们将开始前往自己的座位。按照从 $1$ 到 $nm$ 的顺序，每个人将进入影厅并坐在自己的座位上。为了到达自己的座位，这个人将走到自己座位所在的行，然后从这一行的第一个座位开始从左到右移动到自己的座位。在移动过程中，有些座位会是空的，有些座位会被已经就座的人占据。这个人的不便程度等于他或她经过的已占用座位的数量。

让我们考虑一个例子：$m = 5$，一个人坐在第一行的第 $4$ 个座位，第一行的第 $1$、$3$、$5$ 个座位已经被占用，第 $2$ 和第 $4$ 个座位是空的。这个人的不便程度将是 $2$，因为他将经过已占用的座位 $1$ 和 $3$。

找到在给所有人分配座位（满足所有条件）的情况下可能的最小总不便程度（所有人不便程度的总和）。

## 说明/提示
在第一个测试用例中，只有一种分配座位的方法：第一个人坐在第一个座位，第二个人坐在第二个座位。总不便程度是 $1$。

在第二个测试用例中，最优的座位安排如下：

（此处有图片链接）

在第三个测试用例中，最优的座位安排如下：

（此处有图片链接）

单元格中的数字是坐在这个位置上的人的编号。

## 样例 #1
### 输入
```
7
1 2
1 2
3 2
1 1 2 2 3 3
3 3
3 4 4 1 1 1 1 1 2
2 2
1 1 2 1
4 2
50 50 50 50 3 50 50 50
4 2
6 6 6 6 2 2 9 6
2 9
1 3 3 3 3 3 1 1 3 1 3 1 1 3 3 1 1 3
```

### 输出
```
1
0
4
0
0
0
1
```

### 算法分类
贪心、树状数组、离散化

### 综合分析与结论
这些题解的核心思路都是先对数据进行预处理（如离散化），再利用贪心策略确定座位分配方案，最后使用树状数组优化计算总不便程度。不同题解在具体实现细节上有所差异，但整体思路一致。

### 所选题解
- **作者：Jur_Cai (赞：3)  4星**
  - **关键亮点**：思路清晰，详细阐述了离散化和树状数组的使用，代码注释丰富，易于理解。
  - **个人心得**：提到“十年CF一场空，memset见祖宗”，强调多组数据时数组清零的重要性。

### 重点代码
```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#include<algorithm>
#define lowbit(x) x&-x 
using namespace std;
map<int,int> mp;
struct node {
	int elem,id;
	bool operator<(const node b) const {
		return this->elem<b.elem;
	}
}a[100005],b[100005];
int cnt,n,m;
int tree[305][90005];
//树状数组板子
//p是行数，每行用一个树状数组维护
inline void update(int p,int x) {
	for(;x<=cnt;x+=lowbit(x)) tree[p][x]++;
}
inline int query(int p,int x){
	int sum=0;
	for(;x;x-=lowbit(x)) sum+=tree[p][x];
	return sum;
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int ans=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n*m;i++)
			scanf("%d",&a[i].elem),b[i].elem=a[i].elem,b[i].id=i;
		stable_sort(b+1,b+n*m+1);
		mp.clear(),cnt=0;
		for(int i=1;i<=n*m;i++) {
			a[b[i].id].id=i;//a.id表示该人座位
			//离散化
			if(mp.find(b[i].elem)==mp.end()) mp[b[i].elem]=++cnt;
		}
		//多组数据数组清零
		for(int i=1;i<=n;i++)
			for(int j=1;j<=cnt;j++)
				tree[i][j]=0;
		for(int i=1;i<=n*m;i++) {
			int l=(a[i].id-1)/m+1;//该人的行数
			//树状数组里存的是离散化后对应值的个数
			//所以query直接查询小于当前值的前缀和就是所需
			ans+=query(l,mp[a[i].elem]-1);
			update(l,mp[a[i].elem]);
		}
		cout<<ans<<'\n';
	} 
	return 0;
}
```
**核心实现思想**：
1. **离散化**：使用 `stable_sort` 对数据排序，利用 `map` 进行离散化，将每个人的视力值映射到一个较小的连续整数范围。
2. **树状数组维护**：为每行维护一个树状数组，`update` 函数用于更新树状数组中某个值的出现次数，`query` 函数用于查询小于某个值的元素个数。
3. **计算不便程度**：遍历每个人，根据其所在行和离散化后的视力值，利用树状数组查询其前面已就座且视力更差的人数，累加到总不便程度中，并更新树状数组。

### 扩展思路
同类型题目可能会改变座位的布局或规则，如增加座位的特殊属性、改变人员进入的顺序等，但核心思路仍然是贪心策略结合数据结构优化计算。类似算法套路包括对数据进行预处理（如排序、离散化），利用贪心思想确定最优方案，使用树状数组、线段树等数据结构优化计算。

### 推荐洛谷题目
1. P1908 逆序对
2. P3374 【模板】树状数组 1
3. P5788 【模板】单调栈

### 个人心得总结
Jur_Cai 提到多组数据时使用 `memset` 对数组清零的重要性，避免因数组残留数据导致错误。在处理多组数据的题目时，一定要注意对数组和变量进行初始化。 

---
处理用时：102.99秒