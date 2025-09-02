# 题目信息

# Equalize Prices

## 题目描述

There are $ n $ products in the shop. The price of the $ i $ -th product is $ a_i $ . The owner of the shop wants to equalize the prices of all products. However, he wants to change prices smoothly.

In fact, the owner of the shop can change the price of some product $ i $ in such a way that the difference between the old price of this product $ a_i $ and the new price $ b_i $ is at most $ k $ . In other words, the condition $ |a_i - b_i| \le k $ should be satisfied ( $ |x| $ is the absolute value of $ x $ ).

He can change the price for each product not more than once. Note that he can leave the old prices for some products. The new price $ b_i $ of each product $ i $ should be positive (i.e. $ b_i > 0 $ should be satisfied for all $ i $ from $ 1 $ to $ n $ ).

Your task is to find out the maximum possible equal price $ B $ of all productts with the restriction that for all products the condiion $ |a_i - B| \le k $ should be satisfied (where $ a_i $ is the old price of the product and $ B $ is the same new price of all products) or report that it is impossible to find such price $ B $ .

Note that the chosen price $ B $ should be integer.

You should answer $ q $ independent queries.

## 说明/提示

In the first example query you can choose the price $ B=2 $ . It is easy to see that the difference between each old price and each new price $ B=2 $ is no more than $ 1 $ .

In the second example query you can choose the price $ B=6 $ and then all the differences between old and new price $ B=6 $ will be no more than $ 2 $ .

In the third example query you cannot choose any suitable price $ B $ . For any value $ B $ at least one condition out of two will be violated: $ |1-B| \le 2 $ , $ |6-B| \le 2 $ .

In the fourth example query all values $ B $ between $ 1 $ and $ 7 $ are valid. But the maximum is $ 7 $ , so it's the answer.

## 样例 #1

### 输入

```
4
5 1
1 1 2 3 1
4 2
6 4 8 5
2 2
1 6
3 5
5 2 5
```

### 输出

```
2
6
-1
7
```

# AI分析结果

### 题目内容
# 使价格相等

## 题目描述
商店里有 $n$ 件商品。第 $i$ 件商品的价格是 $a_i$ 。商店老板想让所有商品的价格相等。然而，他希望平稳地改变价格。

实际上，商店老板可以改变某件商品 $i$ 的价格，使得这件商品的旧价格 $a_i$ 和新价格 $b_i$ 之间的差值至多为 $k$ 。换句话说，需要满足条件 $|a_i - b_i| \leq k$ （$|x|$ 是 $x$ 的绝对值）。

他对每件商品的价格改变次数不能超过一次。注意，他可以对某些商品保留旧价格。每件商品 $i$ 的新价格 $b_i$ 都应该是正数（即对于从 $1$ 到 $n$ 的所有 $i$ ，都应满足 $b_i > 0$ ）。

你的任务是找出所有商品可能的最大相等价格 $B$ ，且要满足对所有商品都有条件 $|a_i - B| \leq k$ （其中 $a_i$ 是商品的旧价格，$B$ 是所有商品相同的新价格），如果找不到这样的价格 $B$ ，则报告不可能。

注意，所选的价格 $B$ 应为整数。

你需要回答 $q$ 个独立的查询。

## 说明/提示
在第一个示例查询中，你可以选择价格 $B = 2$ 。很容易看出，每个旧价格与新价格 $B = 2$ 之间的差值都不超过 $1$ 。

在第二个示例查询中，你可以选择价格 $B = 6$ ，然后所有旧价格与新价格 $B = 6$ 之间的差值都不超过 $2$ 。

在第三个示例查询中，你无法选择任何合适的价格 $B$ 。对于任何值 $B$ ，至少会违反两个条件中的一个：$|1 - B| \leq 2$ ，$|6 - B| \leq 2$ 。

在第四个示例查询中，$1$ 到 $7$ 之间的所有值 $B$ 都是有效的。但最大值是 $7$ ，所以这就是答案。

## 样例 #1
### 输入
```
4
5 1
1 1 2 3 1
4 2
6 4 8 5
2 2
1 6
3 5
5 2 5
```
### 输出
```
2
6
-1
7
```

### 算法分类
数学

### 题解综合分析与结论
所有题解的核心思路都是通过比较数组中的最大值和最小值来判断是否存在满足条件的统一价格 $B$ ，若存在则求出其最大值。主要区别在于实现方式和代码细节。

1. **思路**：多数题解先找出数组中的最大值和最小值，判断两者差值与 $2k$ 的关系。若差值大于 $2k$ ，则无法使所有价格相等，输出 -1；若差值小于等于 $2k$ ，则满足条件的最大统一价格为最小值加上 $k$ 。
2. **算法要点**：快速找出数组中的最大值和最小值，以及准确判断差值与 $2k$ 的关系。
3. **解决难点**：证明满足条件的最大统一价格为最小值加上 $k$ 。当最大值与最小值的差值小于等于 $2k$ 时，最小值加上 $k$ 能保证所有数与该值的差值不超过 $k$ ，且该值为满足条件的最大值。

### 所选的题解
- **AC_Dolphin（5星）**
  - **关键亮点**：思路清晰，给出严谨证明，代码实现简洁明了，定义了专门求最大值和最小值的函数，逻辑结构清晰。
  - **心得**：无
  ```cpp
  int findmax(int a[],int n){
      int maxn=-1;
      for(register int i(1);i<=n;++i) maxn=max(a[i],maxn);
      return maxn;
  }
  int findmin(int a[],int n){
      int minn=100000010;
      for(register int i(1);i<=n;++i) minn=min(a[i],minn);
      return minn;
  }
  int main(){
      q=read();
      while(q--){
          n=read(),k=read();
          for(register int i(1);i<=n;++i) a[i]=read();
          if(findmax(a,n)-findmin(a,n)>k*2){
              cout<<-1<<endl;
              continue;
          }
          cout<<findmin(a,n)+k<<endl;
      }
      return 0;
  }
  ```
- **decoqwq（4星）**
  - **关键亮点**：将问题转化为区间交集问题，直接取最右的左端点和最左的右端点比较，代码简洁高效，从另一个角度巧妙解决问题。
  - **心得**：无
  ```cpp
  int main()
  {
      int t;
      cin>>t;
      while(t--)
      {
          int n,k;
          cin>>n>>k;
          int l=0,r=0x3f3f3f3f;
          for(int i=1;i<=n;i++)
          {
              int x;
              scanf("%d",&x);
              r=min(r,x+k);
              l=max(l,((x-k)>0?(x-k):1));
          }
          if(l<=r)
          {
              cout<<r<<endl;
          }
          else
          {
              cout<<-1<<endl;
          }
      }
  } 
  ```
- **__HHX__（4星）**
  - **关键亮点**：通过不断更新当前数能取的最大值与最小值，最后判断区间 $[min, max]$ 的合法性，思路直接，代码简洁易懂。
  - **心得**：无
  ```cpp
  int main() {
      int q;
      cin >> q;
      while (q--) {
          long long n, k, maxx = 1e16 + 3,minn = -1e8 - 3;
          cin >> n >> k;
          for (int i = 1, x; i <= n; i++) {
              cin >> x;
              maxx = min(maxx, k + x);
              minn = max(minn, -k + x);
          }
          cout << (maxx >= minn? maxx : -1) << '\n';
      }
  } 
  ```

### 最优关键思路或技巧
1. **数学判断**：通过数学分析得出判断条件，即比较数组中最大值与最小值的差值和 $2k$ 的关系，以此确定是否存在满足条件的统一价格，以及该价格的取值。
2. **区间思维**：如decoqwq的题解，将问题转化为区间交集问题，通过取最右的左端点和最左的右端点比较来求解，提供了一种新颖的解题视角。

### 可拓展之处
此类题目属于价格调整的逻辑判断问题，类似的题目可能会在条件上进行拓展，比如改变价格调整的规则，或者对最终相等价格的限制条件更为复杂。类似算法套路主要围绕对给定数据范围和限制条件进行数学分析，得出关键判断条件来求解。

### 洛谷相似题目推荐
1. **P1085 [NOIP2004 普及组] 不高兴的津津**：通过分析时间限制和活动安排条件，判断是否满足特定要求，与本题分析条件判断可行性类似。
2. **P1192 [NOIP2010 普及组] 台阶问题**：根据给定的台阶行走规则和限制，求解可行的方案数，同样需要对条件进行分析和判断。
3. **P1424 小鱼的航程(改进版)**：依据给定的时间范围和行程规则，计算总的行程，也是在一定条件限制下进行逻辑分析和计算。 

---
处理用时：70.07秒