# 题目信息

# Bad Luck Island

## 题目描述

The Bad Luck Island is inhabited by three kinds of species: $ r $ rocks, $ s $ scissors and $ p $ papers. At some moments of time two random individuals meet (all pairs of individuals can meet equiprobably), and if they belong to different species, then one individual kills the other one: a rock kills scissors, scissors kill paper, and paper kills a rock. Your task is to determine for each species what is the probability that this species will be the only one to inhabit this island after a long enough period of time.

## 样例 #1

### 输入

```
2 2 2
```

### 输出

```
0.333333333333 0.333333333333 0.333333333333
```

## 样例 #2

### 输入

```
2 1 2
```

### 输出

```
0.150000000000 0.300000000000 0.550000000000
```

## 样例 #3

### 输入

```
1 1 3
```

### 输出

```
0.057142857143 0.657142857143 0.285714285714
```

# AI分析结果

### 题目内容
# 厄运岛
## 题目描述
厄运岛上栖息着三种生物：$r$ 块石头、$s$ 把剪刀和 $p$ 张纸。在某些时刻，两个随机的个体相遇（所有个体对相遇的概率均等），如果它们属于不同的物种，那么其中一个个体就会杀死另一个：石头砸坏剪刀，剪刀剪坏纸，纸包住石头。你的任务是确定，经过足够长的时间后，每个物种成为岛上唯一栖息物种的概率。
## 样例 #1
### 输入
```
2 2 2
```
### 输出
```
0.333333333333 0.333333333333 0.333333333333
```
## 样例 #2
### 输入
```
2 1 2
```
### 输出
```
0.150000000000 0.300000000000 0.550000000000
```
## 样例 #3
### 输入
```
1 1 3
```
### 输出
```
0.057142857143 0.657142857143 0.285714285714
```

### 算法分类
概率论、动态规划

### 综合分析与结论
这些题解均采用动态规划的方法解决该问题，核心思路是通过定义三维数组 `dp[i][j][k]` 表示剩下 `i` 个 `r`，`j` 个 `s`，`k` 个 `p` 的概率，利用状态转移方程来计算最终每种物种单独存活的概率。状态转移时，根据不同物种相遇的概率更新 `dp` 数组，相遇概率通过当前各物种数量计算得出。难点在于准确理解状态转移关系和概率计算，各题解在处理方式上基本一致，但在细节和代码风格上有所差异。

### 所选的题解
- **作者：Strelitzia (5星)**
  - **关键亮点**：思路清晰，详细阐述了 `dp` 数组定义、状态转移方程推导过程，代码结构完整规范，注释清晰。
  - **个人心得**：考场上构思和编写花费时间较长，反思时间把控问题。
  ```cpp
  const int maxn = 105;
  int r,s,p;
  double dp[maxn][maxn][maxn],rwin,swin,pwin;
  int main () {
      scanf ("%d %d %d",&r,&s,&p);
      dp[r][s][p] = 1.0;
      for (int i = r ; i >= 0 ; -- i) {
          for (int j = s ; j >= 0 ; -- j) {
              for (int k = p ; k >= 0 ; -- k) {
                  double tot = i * j + j * k + i * k;
                  if (i && j) dp[i][j - 1][k] += dp[i][j][k] * i * j / tot;
                  if (j && k) dp[i][j][k - 1] += dp[i][j][k] * j * k / tot;
                  if (k && i) dp[i - 1][j][k] += dp[i][j][k] * i * k / tot;
                  if (i &&!j &&!k) rwin += dp[i][j][k];
                  if (!i && j &&!k) swin += dp[i][j][k];
                  if (!i &&!j && k) pwin += dp[i][j][k]; 
              }
          }
      }
      printf("%.12f %.12f %.12f",rwin,swin,pwin);
      return 0;
  }
  ```
- **作者：寒冰大大 (4星)**
  - **关键亮点**：同样清晰解释了 `dp` 数组含义、状态转移思路及边界条件，代码简洁明了。
  ```cpp
  double f[110][110][110],rwin=0.0,swin=0.0,pwin=0.0;
  int r,s,p,tot;
  int main()
  {
      scanf("%d %d %d",&r,&s,&p);
      int tot;
      f[r][s][p]=1.0;
      int i,j,k;
      for(i=r;i>=0;i--)
      for(j=s;j>=0;j--)
      for(k=p;k>=0;k--)
      {
          tot=i*j+j*k+k*i;
          if(i&&k) f[i-1][j][k]+=1.0*f[i][j][k]*k*i/tot;
          if(j&&i) f[i][j-1][k]+=1.0*f[i][j][k]*i*j/tot;
          if(k&&j) f[i][j][k-1]+=1.0*f[i][j][k]*j*k/tot;
          if(!j&&!k&&i) rwin+=f[i][j][k];
          if(!i&&!k&&j) swin+=f[i][j][k];
          if(!i&&!j&&k) pwin+=f[i][j][k]; 
      }
      printf("%.9lf %.9lf %.9lf",rwin,swin,pwin);
  }
  ```
- **作者：wsy_jim (4星)**
  - **关键亮点**：详细说明了题意和解题思路，对状态转移分析细致，代码规范，使用了模板函数读入数据。
  ```cpp
  const int N=110;
  int r,s,p;
  double f[N][N][N],ansr=0,anss=0,ansp=0;
  signed main(){
      read(r),read(s),read(p);
      f[0][0][0]=1.0;
      for(int i=0;i<=r;i++){
          for(int j=0;j<=s;j++){
              for(int k=0;k<=p;k++){
                  double a=r-i,b=s-j,c=p-k,tot=a*b+b*c+c*a;
                  if(a&&b) f[i][j+1][k]+=f[i][j][k]*a*b/tot;
                  if(b&&c) f[i][j][k+1]+=f[i][j][k]*b*c/tot;
                  if(c&&a) f[i+1][j][k]+=f[i][j][k]*a*c/tot;
                  if(a&&!b&&!c) ansr+=f[i][j][k];
                  if(!a&&b&&!c) anss+=f[i][j][k];
                  if(!a&&!b&&c) ansp+=f[i][j][k];
              }
          }
      }
      printf("%.9lf %.9lf %.9lf\n",ansr,anss,ansp);
      return 0;
  }
  ```

### 最优关键思路或技巧
- **状态定义**：通过三维数组 `dp[i][j][k]` 精准表示当前三种生物的剩余数量状态的概率，这种状态定义直观且易于理解和实现状态转移。
- **概率计算与状态转移**：根据不同物种相遇的组合方式，计算每种相遇情况的概率，并据此更新状态转移方程。这种基于概率的状态转移计算是解决本题的核心技巧。

### 拓展与类似算法套路
此类题目属于概率动态规划类型，通常涉及到不同状态之间的概率转移。类似套路包括明确状态定义，根据题目规则确定状态转移关系和概率计算方式。同类型题可能会改变物种数量、相遇规则或增加更多复杂条件，但核心思路都是通过动态规划解决概率问题。

### 推荐洛谷题目
- [P1288 取数游戏II](https://www.luogu.com.cn/problem/P1288)：同样是概率相关的动态规划问题，需要通过定义状态和状态转移方程来求解概率。
- [P4550 收集邮票](https://www.luogu.com.cn/problem/P4550)：涉及概率与期望的动态规划，在状态转移和期望计算上与本题有相似之处。
- [P3232 [HNOI2013]游走](https://www.luogu.com.cn/problem/P3232)：通过概率计算和动态规划求解最优策略，锻炼对概率动态规划的理解和应用能力。

### 个人心得摘录与总结
- **Strelitzia**：反思在考场上花费时间较长的问题，强调时间把控在解题中的重要性。
- **pipi**：总结了递归实现中的多个易错点，如边界条件判断、避免除零、防止自动下取整、记忆化搜索避免重复计算、输出格式控制等，这些都是在实现概率动态规划时常见的问题。
- **Fading**：指出相同种族不会互相伤害，不能算入概率，强调对题目条件细节的准确把握。 

---
处理用时：73.82秒