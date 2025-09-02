# 题目信息

# Cinema

## 题目描述

Overall there are $ m $ actors in Berland. Each actor has a personal identifier — an integer from $ 1 $ to $ m $ (distinct actors have distinct identifiers). Vasya likes to watch Berland movies with Berland actors, and he has $ k $ favorite actors. He watched the movie trailers for the next month and wrote the following information for every movie: the movie title, the number of actors who starred in it, and the identifiers of these actors. Besides, he managed to copy the movie titles and how many actors starred there, but he didn't manage to write down the identifiers of some actors. Vasya looks at his records and wonders which movies may be his favourite, and which ones may not be. Once Vasya learns the exact cast of all movies, his favorite movies will be determined as follows: a movie becomes favorite movie, if no other movie from Vasya's list has more favorite actors.

Help the boy to determine the following for each movie:

- whether it surely will be his favourite movie;
- whether it surely won't be his favourite movie;
- can either be favourite or not.

## 说明/提示

Note to the second sample:

- Movie jumanji can theoretically have from 1 to 3 Vasya's favourite actors.
- Movie theeagle has all three favourite actors, as the actor Vasya failed to remember, can only have identifier 5.
- Movie matrix can have exactly one favourite actor.
- Movie sourcecode doesn't have any favourite actors.

Thus, movie theeagle will surely be favourite, movies matrix and sourcecode won't surely be favourite, and movie jumanji can be either favourite (if it has all three favourite actors), or not favourite.

## 样例 #1

### 输入

```
5 3
1 2 3
6
firstfilm
3
0 0 0
secondfilm
4
0 0 4 5
thirdfilm
1
2
fourthfilm
1
5
fifthfilm
1
4
sixthfilm
2
1 0
```

### 输出

```
2
2
1
1
1
2
```

## 样例 #2

### 输入

```
5 3
1 3 5
4
jumanji
3
0 0 0
theeagle
5
1 2 3 4 0
matrix
3
2 4 0
sourcecode
2
2 4
```

### 输出

```
2
0
1
1
```

# AI分析结果



# Cinema

## 题目描述

总共有 $ m $ 个演员在伯兰。每个演员都有一个唯一标识符（整数 $ 1 $ 到 $ m $）。Vasya 有 $ k $ 个最喜欢的演员。他记录了 $ n $ 部电影的信息，每部电影包含：片名、参演人数、演员标识符列表（其中 0 表示未知演员）。

请对每部电影判断：
- 必定成为最爱电影（输出 0）
- 必定不会成为最爱（输出 1）
- 可能成为或不成（输出 2）

## 算法分类
模拟

---

### 题解对比分析
所有题解均采用**上下界分析+极值比较**的核心思路：
1. 对每部电影计算可能包含的喜爱演员数的最小值（min_love）和最大值（max_love）
2. 遍历所有电影，比较当前电影的极值与其他电影的极值

**关键公式**：
- max_love = 已确认喜爱数 + min(未知位置数, 剩余喜爱演员数)
- min_love = 已确认喜爱数 + max(0, 未知位置数 - 可用非喜爱演员数)

---

### 最优题解（评分：⭐⭐⭐⭐⭐）
#### 作者：封禁用户
**核心亮点**：
- 极值计算简洁高效：`maxn = min(已确认+未知数, k)`，`minn = max(已确认, k - m + d)`
- 双重极值比较逻辑清晰：先求其他电影的max(max_love)和max(min_love)
```cpp
for(int j=1; j<=n; j++) {
    if(i == j) continue;
    maxmin = max(maxmin, s[j].minn);
    maxmax = max(maxmax, s[j].maxn);
}
if(s[i].minn >= maxmax) cout << "0\n";
else if(s[i].maxn < maxmin) cout << "1\n";
else cout << "2\n";
```

#### 作者：LEMON_dasiy（评分：⭐⭐⭐⭐）
**个人心得**：
> "计算min_love时要考虑：当可用非喜爱演员数不足以填充未知位置时，剩余位置必须用喜爱演员填充。例如总演员数m=5，当前电影演员数d=3，未知位置数2，此时最多只能有 m-d=2 个非喜爱演员可用"

---

### 关键技巧总结
1. **上下界压缩法**：通过数学分析将不确定性问题转化为确定的极值比较
2. **极值传递性**：用全局极值代替两两比较，降低时间复杂度到 O(n²)
3. **输入优化**：注意本题的特殊输入要求（文件重定向）

---

### 拓展练习
1. [P3740 接水问题](https://www.luogu.com.cn/problem/P3740) - 极值模拟
2. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157) - 上下界剪枝 
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056) - 贪心极值选择

---

### 调试心得摘录
> "十年OI一场空，不打freopen见祖宗" —— 多位题解作者强调文件重定向的重要性  
> "当电影中的未知位置数超过可用非喜爱演员时，必须填入喜爱演员" —— LEMON_dasiy 的极值计算心得

---
处理用时：51.82秒