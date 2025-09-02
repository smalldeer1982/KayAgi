# 题目信息

# Kar Salesman

## 题目描述

Karel is a salesman in a car dealership. The dealership has $ n $ different models of cars. There are $ a_i $ cars of the $ i $ -th model. Karel is an excellent salesperson and can convince customers to buy up to $ x $ cars (of Karel's choice), as long as the cars are from different models.

Determine the minimum number of customers Karel has to bring in to sell all the cars.

## 说明/提示

For the first case, Karel only needs to lure in $ 3 $ customers. He will convince the customers to buy the following models of cars:

- Customer $ 1 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .
- Customer $ 2 $ buys $ 2 $ cars with model $ 1 $ and $ 2 $ .
- Customer $ 3 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .

For the second case, Karel only needs to lure in $ 3 $ customers. He will convince the customers to buy the following models of cars:

- Customer $ 1 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .
- Customer $ 2 $ buys $ 3 $ cars with model $ 1 $ , $ 2 $ and $ 3 $ .
- Customer $ 3 $ buys $ 1 $ car with model $ 3 $ .

## 样例 #1

### 输入

```
4
3 2
3 1 2
3 3
2 1 3
5 3
2 2 1 9 2
7 4
2 5 3 3 5 2 5```

### 输出

```
3
3
9
7```

# AI分析结果

### 题目内容重写
Karel 是一家汽车经销店的推销员。这家经销商有 $n$ 种不同型号的汽车。第 $i$ 种型号的汽车有 $a_i$ 辆。Karel 是一名优秀的销售人员，他可以说服顾客购买多达 $x$ 辆车（Karel 的选择），只要这些车来自不同的型号。

请确定 Karel 必须引入的最小客户数量才能销售所有汽车。

### 题解综合分析
所有题解的核心思路基本一致，即通过两个条件来确定最小客户数量：
1. 每个顾客购买的车必须来自不同型号，因此至少需要 $\max\{a_1, a_2, \dots, a_n\}$ 个顾客。
2. 每个顾客最多只能购买 $x$ 辆车，因此至少需要 $\lceil \frac{\sum_{i=1}^{n} a_i}{x} \rceil$ 个顾客。

最终答案为这两个条件的最大值。

### 关键思路与技巧
1. **贪心思想**：通过最大化每个顾客的购买量来最小化客户数量。
2. **数学公式**：使用取整函数 $\lceil \cdot \rceil$ 来计算满足第二个条件的客户数量。
3. **代码优化**：通过一次遍历同时计算最大值和总和，避免多次遍历。

### 推荐题解
#### 题解1：作者：jubaoyi2011 (赞：2)
- **星级**：4
- **关键亮点**：思路清晰，代码简洁，直接使用公式计算客户数量。
- **核心代码**：
  ```cpp
  int T,n,x,ans,mmax,a;
  main(){
      cin>>T;
      while(T--){
          cin>>n>>x;
          ans=0;
          mmax=0;
          while(n--){
              cin>>a;
              mmax=max(mmax,a);
              ans+=a;
          }
          cout<<max(mmax,(ans+x-1)/x)<<endl;
      }
  }
  ```

#### 题解2：作者：Zhl2010 (赞：1)
- **星级**：4
- **关键亮点**：使用 `long long` 防止溢出，代码结构清晰。
- **核心代码**：
  ```cpp
  signed main(){
      int T;
      cin>>T;
      while(T--){
          int n,x;
          cin>>n>>x;
          int sum=0,a;
          int ma=0;
          for(int i=1;i<=n;i++){
              scanf("%lld",&a);
              sum+=a;
              ma=max(ma,a);
          }
          cout<<max(ma,(sum+x-1)/x)<<endl;
      }
      return 0;
  }
  ```

#### 题解3：作者：FXLIR (赞：0)
- **星级**：4
- **关键亮点**：使用 `ceil` 函数计算客户数量，代码简洁。
- **核心代码**：
  ```cpp
  signed main(){
      ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
      cin>>t;
      while(t--){
          maxa=-1e9,sum=0;
          cin>>n>>x;
          for(int i=1;i<=n;i++){
              cin>>a;
              sum+=a,maxa=max(maxa,a);
          }
          int t=sum/x+(sum%x!=0);
          cout<<max(maxa,t)<<"\n";
      }
      return 0;
  }
  ```

### 扩展思路与推荐题目
1. **扩展思路**：类似问题可以通过贪心算法和数学公式结合的方式解决，如任务调度、资源分配等。
2. **推荐题目**：
   - [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
   - [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
   - [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)

---
处理用时：28.69秒