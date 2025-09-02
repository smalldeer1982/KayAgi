# 题目信息

# Drinks Choosing

## 题目描述

Old timers of Summer Informatics School can remember previous camps in which each student was given a drink of his choice on the vechorka (late-evening meal). Or may be the story was more complicated?

There are $ n $ students living in a building, and for each of them the favorite drink $ a_i $ is known. So you know $ n $ integers $ a_1, a_2, \dots, a_n $ , where $ a_i $ ( $ 1 \le a_i \le k $ ) is the type of the favorite drink of the $ i $ -th student. The drink types are numbered from $ 1 $ to $ k $ .

There are infinite number of drink sets. Each set consists of exactly two portions of the same drink. In other words, there are $ k $ types of drink sets, the $ j $ -th type contains two portions of the drink $ j $ . The available number of sets of each of the $ k $ types is infinite.

You know that students will receive the minimum possible number of sets to give all students exactly one drink. Obviously, the number of sets will be exactly $ \lceil \frac{n}{2} \rceil $ , where $ \lceil x \rceil $ is $ x $ rounded up.

After students receive the sets, they will distribute their portions by their choice: each student will get exactly one portion. Note, that if $ n $ is odd then one portion will remain unused and the students' teacher will drink it.

What is the maximum number of students that can get their favorite drink if $ \lceil \frac{n}{2} \rceil $ sets will be chosen optimally and students will distribute portions between themselves optimally?

## 说明/提示

In the first example, students could choose three sets with drinks $ 1 $ , $ 1 $ and $ 2 $ (so they will have two sets with two drinks of the type $ 1 $ each and one set with two drinks of the type $ 2 $ , so portions will be $ 1, 1, 1, 1, 2, 2 $ ). This way all students except the second one will get their favorite drinks.

Another possible answer is sets with drinks $ 1 $ , $ 2 $ and $ 3 $ . In this case the portions will be $ 1, 1, 2, 2, 3, 3 $ . Then all the students except one will gain their favorite drinks. The only student that will not gain the favorite drink will be a student with $ a_i = 1 $ (i.e. the first, the third or the fourth).

## 样例 #1

### 输入

```
5 3
1
3
1
1
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 3
2
1
3
2
3
3
1
3
1
2
```

### 输出

```
9
```

# AI分析结果

### 题目内容
# 饮料选择

## 题目描述
夏日信息学学校的老学员们还记得之前的露营活动，在晚餐（晚加餐）时，每位学生都会得到自己心仪的饮料。或许故事更为复杂？

有 $n$ 名学生住在一栋楼里，对于他们每个人，都知道其最喜欢的饮料 $a_i$ 。所以你知道 $n$ 个整数 $a_1, a_2, \dots, a_n$ ，其中 $a_i$（$1 \le a_i \le k$）是第 $i$ 名学生最喜欢的饮料类型。饮料类型从 $1$ 到 $k$ 编号。

有无限数量的饮料套装。每个套装恰好包含两份相同的饮料。换句话说，有 $k$ 种饮料套装，第 $j$ 种套装包含两份饮料 $j$ 。每种 $k$ 类型的套装数量都是无限的。

你知道，为了给所有学生每人恰好一份饮料，将选择尽可能少的套装。显然，套装的数量将恰好是 $\lceil \frac{n}{2} \rceil$ ，其中 $\lceil x \rceil$ 是 $x$ 向上取整。

在学生们收到套装后，他们将根据自己的选择分配饮料份额：每个学生将恰好得到一份。注意，如果 $n$ 是奇数，那么会有一份饮料剩余，由学生的老师饮用。

如果最优地选择 $\lceil \frac{n}{2} \rceil$ 个套装，并且学生们在他们之间最优地分配饮料份额，那么最多有多少学生可以得到他们最喜欢的饮料？

## 说明/提示
在第一个示例中，学生们可以选择三个套装，饮料分别为 $1$ 、$1$ 和 $2$（所以他们将有两个套装，每个套装有两份类型为 $1$ 的饮料，还有一个套装有两份类型为 $2$ 的饮料，因此饮料份额将是 $1, 1, 1, 1, 2, 2$ ）。这样，除了第二个学生之外，所有学生都将得到他们最喜欢的饮料。

另一个可能的答案是选择饮料为 $1$ 、$2$ 和 $3$ 的套装。在这种情况下，饮料份额将是 $1, 1, 2, 2, 3, 3$ 。然后除了一名学生之外，所有学生都将得到他们最喜欢的饮料。唯一得不到最喜欢饮料的学生将是 $a_i = 1$ 的学生（即第一个、第三个或第四个学生）。

## 样例 #1
### 输入
```
5 3
1
3
1
1
2
```
### 输出
```
4
```

## 样例 #2
### 输入
```
10 3
2
1
3
2
3
3
1
3
1
2
```
### 输出
```
9
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路大多基于贪心策略，即优先满足能组成二元组的学生，使相同饮料的学生尽可能多地得到满足。算法要点在于统计每种饮料喜欢的学生人数，然后根据人数计算能组成的二元组数量。解决难点主要在于如何合理分配饮料套装，以达到最多学生得到心仪饮料的目的。不同题解在实现细节上有所差异，如统计方式、计算满足学生数量的具体步骤等。

### 所选的题解
 - **作者：meyi (5星)**
    - **关键亮点**：思路清晰，通过倒推找出能组成二元组的元素，代码简洁高效，对特殊情况（$s<\lceil\frac{n}{2}\rceil$）处理巧妙。
    - **重点代码**：
```cpp
#include<cstdio>
int a[1001],k,n,s;
main(){
    scanf("%d%d",&n,&k),k=(n&1)+(n>>1);
    while(n--)scanf("%d",a),s+=a[*a]++&1;
    printf("%d",k+s);
} 
```
    - **核心实现思想**：用数组`a`记录每种饮料出现次数，在输入时统计每种饮料能组成的二元组个数累加到`s`，最后根据情况输出结果。

 - **作者：_bql (4星)**
    - **关键亮点**：采用数学解法，逻辑清晰，通过统计喜欢每种饮料的人数，直接进行计算，代码简洁明了。
    - **重点代码**：
```cpp
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[a[i]]++;//统计喜欢每种饮料的有多少人
	}
	n+=n%2;
	n/=2;
	for(int i=1;i<=k;i++)
	{
		ans+=s[i]/2*2;
		n-=s[i]/2;
	}
	ans+=n;
	cout<<ans;
```
    - **核心实现思想**：先统计喜欢每种饮料的人数`s`，对`n`进行处理保证向上取整，然后遍历计算能满足的学生数`ans`，最后加上剩余可满足的学生数。

 - **作者：tommychen (4星)**
    - **关键亮点**：贪心策略明确，代码实现直观，通过统计成对的数和剩余二元组个数来计算结果，易于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
using namespace std;
signed main(){
	int n,m;
	cin>>n>>m;
	int a[n+1],tot[m+1]={0};
	for(int i=1;i<=n;i++){
		cin>>a[i];
		tot[a[i]]++;//统计每个数出现的个数，方便后面计算成对的数
	}
	int sum=0;
	for(int i=1;i<=m;i++){
		sum+=tot[i]/2;//统计有多少个成对的数
	}
	int ans=n-n/2;
	ans-=sum;
	cout<<sum*2+ans<<endl;
	return 0;
}
```
    - **核心实现思想**：用数组`tot`统计每种饮料出现次数，计算成对的数`sum`，再算出剩余可使用二元组个数`ans`，最后得出满足的学生总数。

### 最优关键思路或技巧
这些题解中最优的关键思路是利用贪心策略，优先满足能组成二元组的学生。技巧方面，通过数组统计每种饮料喜欢的人数，再基于此进行计算，不同题解在计算满足学生数量的方式上各有巧妙之处，如`meyi`题解对特殊情况的简洁处理，`_bql`题解对向上取整的巧妙数学处理等。

### 可拓展之处
同类型题通常围绕资源分配、物品组合等场景，同样基于贪心策略解决问题。类似算法套路是先统计相关元素的数量，再根据题目条件进行合理分配。

### 洛谷相似题目推荐
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录与总结
无。 

---
处理用时：69.19秒