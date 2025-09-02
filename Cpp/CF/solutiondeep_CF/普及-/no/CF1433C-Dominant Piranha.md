# 题目信息

# Dominant Piranha

## 题目描述

There are $ n $ piranhas with sizes $ a_1, a_2, \ldots, a_n $ in the aquarium. Piranhas are numbered from left to right in order they live in the aquarium.

Scientists of the Berland State University want to find if there is dominant piranha in the aquarium. The piranha is called dominant if it can eat all the other piranhas in the aquarium (except itself, of course). Other piranhas will do nothing while the dominant piranha will eat them.

Because the aquarium is pretty narrow and long, the piranha can eat only one of the adjacent piranhas during one move. Piranha can do as many moves as it needs (or as it can). More precisely:

- The piranha $ i $ can eat the piranha $ i-1 $ if the piranha $ i-1 $ exists and $ a_{i - 1} < a_i $ .
- The piranha $ i $ can eat the piranha $ i+1 $ if the piranha $ i+1 $ exists and $ a_{i + 1} < a_i $ .

When the piranha $ i $ eats some piranha, its size increases by one ( $ a_i $ becomes $ a_i + 1 $ ).

Your task is to find any dominant piranha in the aquarium or determine if there are no such piranhas.

Note that you have to find any (exactly one) dominant piranha, you don't have to find all of them.

For example, if $ a = [5, 3, 4, 4, 5] $ , then the third piranha can be dominant. Consider the sequence of its moves:

- The piranha eats the second piranha and $ a $ becomes $ [5, \underline{5}, 4, 5] $ (the underlined piranha is our candidate).
- The piranha eats the third piranha and $ a $ becomes $ [5, \underline{6}, 5] $ .
- The piranha eats the first piranha and $ a $ becomes $ [\underline{7}, 5] $ .
- The piranha eats the second piranha and $ a $ becomes $ [\underline{8}] $ .

You have to answer $ t $ independent test cases.

## 说明/提示

The first test case of the example is described in the problem statement.

In the second test case of the example, there are no dominant piranhas in the aquarium.

In the third test case of the example, the fourth piranha can firstly eat the piranha to the left and the aquarium becomes $ [4, 4, 5, 4] $ , then it can eat any other piranha in the aquarium.

## 样例 #1

### 输入

```
6
5
5 3 4 4 5
3
1 1 1
5
4 4 3 4 4
5
5 5 4 3 2
3
1 1 2
5
5 4 3 5 5```

### 输出

```
3
-1
4
3
3
1```

# AI分析结果

### 题目内容
# 优势食人鱼

## 题目描述
在水族馆中有 $n$ 条食人鱼，它们的大小分别为 $a_1, a_2, \ldots, a_n$ 。食人鱼按照它们在水族馆中的生活顺序从左到右编号。

伯兰德州立大学的科学家们想要找出水族馆中是否存在优势食人鱼。如果一条食人鱼能够吃掉水族馆中的所有其他食人鱼（当然不包括它自己），那么这条食人鱼就被称为优势食人鱼。在优势食人鱼进食时，其他食人鱼不会有任何动作。

由于水族馆又窄又长，食人鱼在一次行动中只能吃掉相邻的食人鱼之一。食人鱼可以根据需要（或者能够）进行任意多次行动。更准确地说：
- 如果食人鱼 $i - 1$ 存在且 $a_{i - 1} < a_i$ ，那么食人鱼 $i$ 可以吃掉食人鱼 $i - 1$ 。
- 如果食人鱼 $i + 1$ 存在且 $a_{i + 1} < a_i$ ，那么食人鱼 $i$ 可以吃掉食人鱼 $i + 1$ 。

当食人鱼 $i$ 吃掉某条食人鱼后，它的大小会增加一（$a_i$ 变为 $a_i + 1$ ）。

你的任务是找出水族馆中的任意一条优势食人鱼，或者确定不存在这样的食人鱼。

请注意，你只需要找出任意一条（确切地一条）优势食人鱼，而不需要找出所有的优势食人鱼。

例如，如果 $a = [5, 3, 4, 4, 5]$ ，那么第三条食人鱼可以成为优势食人鱼。考虑它的行动序列：
- 食人鱼吃掉第二条食人鱼，$a$ 变为 $[5, \underline{5}, 4, 5]$ （下划线标注的食人鱼是我们的候选者）。
- 食人鱼吃掉第三条食人鱼，$a$ 变为 $[5, \underline{6}, 5]$ 。
- 食人鱼吃掉第一条食人鱼，$a$ 变为 $[\underline{7}, 5]$ 。
- 食人鱼吃掉第二条食人鱼，$a$ 变为 $[\underline{8}]$ 。

你需要回答 $t$ 个独立的测试用例。

## 说明/提示
示例中的第一个测试用例在题目描述中已经说明。

在示例的第二个测试用例中，水族馆中不存在优势食人鱼。

在示例的第三个测试用例中，第四条食人鱼可以先吃掉左边的食人鱼，水族馆变为 $[4, 4, 5, 4]$ ，然后它可以吃掉水族馆中的任何其他食人鱼。

## 样例 #1
### 输入
```
6
5
5 3 4 4 5
3
1 1 1
5
4 4 3 4 4
5
5 5 4 3 2
3
1 1 2
5
5 4 3 5 5
```
### 输出
```
3
-1
4
3
3
1
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解的核心思路都是围绕体积最大的食人鱼展开。因为体积最大的食人鱼在竞争优势上更具潜力，若存在一条最大体积且能吃掉相邻较小体积食人鱼的鱼，那么它就能成为优势食人鱼。各题解的主要差异在于实现细节和代码风格。有的题解先判断特殊情况（如所有食人鱼体积相同），有的则是直接遍历找符合条件的最大体积食人鱼。整体来看，这些题解都较为直接地实现了题目的要求，思路清晰，代码复杂度也相近。

### 所选的题解
- **作者：ttq012（5星）**
  - **关键亮点**：思路清晰，对各种情况进行了详细分类讨论，代码简洁明了，直接利用 `max_element` 函数获取数组最大值，且使用 `goto` 语句跳出多层循环，优化了代码结构。
  - **个人心得**：无
  ```cpp
  int a[1000010];
  signed main() {
      int t;
      cin >> t;
      while (t --) {
          int n;
          cin >> n;
          for (int i = 1; i <= n; i ++)
              cin >> a[i];
          int mx = (*(max_element(a + 1, a + n + 1)));
          if (n == 1) puts("1");
          else if (a[1] == mx && a[2]!= mx) puts("1");
          else if (a[n] == mx && a[n - 1]!= mx) printf ("%d\n", n);
          else {
              for (int i = 2; i < n; i ++)
                  if (a[i] == mx && (a[i + 1]!= mx || a[i - 1]!= mx)) {
                      printf ("%d\n", i);
                      goto nlbl;
                  }
              puts("-1");
          }
          nlbl:;
      }
      return 0;
  }
  ```
  核心实现思想：先获取数组最大值 `mx`，然后分情况判断：若数组只有一个元素，直接输出1；若第一个元素为最大值且第二个元素小于它，输出1；若最后一个元素为最大值且倒数第二个元素小于它，输出数组长度 `n`；否则遍历中间元素，若找到最大值且其相邻元素至少有一个小于它，输出该元素下标，若遍历完未找到则输出 `-1`。
- **作者：Natsume_Rin（4星）**
  - **关键亮点**：代码简洁，利用数组边界值的巧妙设置简化了判断条件，通过 `max` 函数获取最大值，整体逻辑清晰。
  - **个人心得**：无
  ```cpp
  const int MAXN = 3e5+5;
  int q, n, a[MAXN];
  int maxn, maxid;
  int minn;
  bool pd;
  int main(){
      scanf("%d",&q);
      while(q--){
          maxn=0, pd=1;
          scanf("%d",&n);
          for(RI i=1;i<=n;++i) {scanf("%d",&a[i]);maxn=max(maxn,a[i]);}
          a[0]=a[n+1]=maxn;
          for(RI i=1;i<=n;++i){
              if(a[i]==maxn&&(a[i+1]!=maxn||a[i-1]!=maxn)){
                  printf("%d\n",i);
                  pd=0;
                  break;
              }
          }
          if(pd) 
          printf("-1\n");
      }
      return 0;
  }
  ```
  核心实现思想：先读入数据并获取最大值 `maxn`，然后将数组两端设为最大值，遍历数组，若找到最大值且其相邻元素至少有一个不等于它，输出该元素下标并标记找到，否则最后输出 `-1`。
- **作者：vectorwyx（4星）**
  - **关键亮点**：代码简洁高效，通过设置数组边界值简化判断，直接在遍历中寻找符合条件的最大值，逻辑清晰。
  - **个人心得**：无
  ```cpp
  const int maxn=3e5+5;
  int a[maxn];
  void work(){
      int n=read(),mx=-1,ans=-1;
      fo(i,1,n) a[i]=read(),mx=max(mx,a[i]);
      a[0]=a[n+1]=mx;
      fo(i,1,n) if(a[i]==mx&&(a[i-1]<a[i]||a[i+1]<a[i])){
          ans=i;
          break;
      }
      printf("%d\n",ans);
  }
  int main(){
      int T=read();
      while(T--){
          work();
      }
      return 0;
  }
  ```
  核心实现思想：读入数据并获取最大值 `mx`，将数组两端设为最大值，遍历数组，若找到最大值且其相邻元素至少有一个小于它，记录该元素下标并跳出循环，最后输出结果。

### 最优关键思路或技巧
1. **利用数组边界值简化判断**：将数组两端设为最大值，这样在判断中间元素时可以避免单独处理边界情况，简化了代码逻辑。
2. **基于贪心选择最大体积食人鱼**：优先考虑最大体积的食人鱼，因为它在竞争优势上更明显，只要能吃掉相邻较小体积的食人鱼，就能成为优势食人鱼。

### 拓展思路
此类题目属于贪心策略应用，类似题目常围绕资源分配、最优选择等场景，通常需要从局部最优选择出发，逐步达到全局最优。比如会出现一些动物竞争场景，或者任务分配场景等，在这些场景中找到一种贪心策略，使得最终能满足特定的全局目标。

### 洛谷推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过不断合并最小的两堆果子，以达到总代价最小，考察贪心策略。
2. [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要根据武将武力值等信息，利用贪心思想选择最优策略。
3. [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：通过对字符串的处理，利用贪心思路解决重复子串问题。 

---
处理用时：68.07秒