# 题目信息

# Fadi and LCM

## 题目描述

Today, Osama gave Fadi an integer $ X $ , and Fadi was wondering about the minimum possible value of $ max(a, b) $ such that $ LCM(a, b) $ equals $ X $ . Both $ a $ and $ b $ should be positive integers.

 $ LCM(a, b) $ is the smallest positive integer that is divisible by both $ a $ and $ b $ . For example, $ LCM(6, 8) = 24 $ , $ LCM(4, 12) = 12 $ , $ LCM(2, 3) = 6 $ .

Of course, Fadi immediately knew the answer. Can you be just like Fadi and find any such pair?

## 样例 #1

### 输入

```
2```

### 输出

```
1 2```

## 样例 #2

### 输入

```
6```

### 输出

```
2 3```

## 样例 #3

### 输入

```
4```

### 输出

```
1 4```

## 样例 #4

### 输入

```
1```

### 输出

```
1 1```

# AI分析结果

### 题目内容重写
# Fadi and LCM

## 题目描述

今天，Osama给了Fadi一个整数$X$，Fadi想知道满足$LCM(a, b) = X$的最小可能值$max(a, b)$。其中$a$和$b$都是正整数。

$LCM(a, b)$是能被$a$和$b$整除的最小正整数。例如，$LCM(6, 8) = 24$，$LCM(4, 12) = 12$，$LCM(2, 3) = 6$。

当然，Fadi立刻知道了答案。你能像Fadi一样找到这样的数对吗？

## 样例 #1

### 输入

```
2```

### 输出

```
1 2```

## 样例 #2

### 输入

```
6```

### 输出

```
2 3```

## 样例 #3

### 输入

```
4```

### 输出

```
1 4```

## 样例 #4

### 输入

```
1```

### 输出

```
1 1```

### 算法分类
数学

### 题解分析与结论
题目要求找到满足$LCM(a, b) = X$的数对$(a, b)$，并且使得$max(a, b)$最小。通过分析，我们可以得出以下结论：
1. **互质性**：最优解中的$a$和$b$必须互质，即$\gcd(a, b) = 1$。否则，可以通过约去$\gcd(a, b)$得到更小的$max(a, b)$。
2. **枚举因数**：由于$a$和$b$必须是$X$的因数，我们可以通过枚举$1$到$\sqrt{X}$的所有因数，找到满足条件的数对。

### 高星题解推荐
#### 题解1：作者：Aw顿顿 (赞：7)
- **星级**：5星
- **关键亮点**：清晰地解释了为什么$a$和$b$必须互质，并通过枚举因数的方法高效地找到最优解。
- **代码实现**：
  ```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  int x,res1=9223372036854775807,res2;
  signed main(void){
      cin>>x;
      for(int i=1;i*i<=x;++i){
          if(x%i)continue;//如果不是因数就跳过
          int a=i,b=x/i;//分配二元组
          if(a*b/__gcd(a,b)==x){//如果 lcm(a,b)=x
              res1=min(res1,b);//那么取最小值
              if(res1==b)res2=a;
              //如果取得了最小值，就更新另一个值
          }
      }cout<<res2<<" "<<res1;//输出
      return 0;
  }
  ```

#### 题解2：作者：Meatherm (赞：5)
- **星级**：4星
- **关键亮点**：同样强调了$a$和$b$的互质性，并提供了简洁的代码实现。
- **代码实现**：
  ```cpp
  # include <bits/stdc++.h>
  # define int long long
  # define rr register
  using namespace std;
  int X;
  int ans=1e17;
  int ansb;
  signed main(void){
      cin>>X;
      for(rr int i=1;i*i<=X;++i){
          if(X%i)
              continue;
          int a=i,b=X/i;
          if(a*b/std::__gcd(a,b)==X){
              ans=std::min(ans,b);
              if(ans==b)
                  ansb=a;
          }
      }
      cout<<ansb<<" "<<ans;
      return 0;
  }
  ```

#### 题解3：作者：Play_with (赞：0)
- **星级**：4星
- **关键亮点**：从$\sqrt{X}$开始倒序枚举，进一步优化了时间复杂度，代码简洁高效。
- **代码实现**：
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long x;
  int main(){
      cin>>x;
      for(long long i=sqrt(x);i;i--)
          if(x%i==0&&__gcd(i,x/i)==1){
              cout<<i<<" "<<x/i;
              return 0;//x有因数,且x和x/i互质
          }
  }
  ```

### 最优关键思路与技巧
1. **互质性**：确保$a$和$b$互质，可以通过约去$\gcd(a, b)$来优化解。
2. **枚举因数**：通过枚举$1$到$\sqrt{X}$的因数，可以高效地找到满足条件的数对。
3. **倒序枚举**：从$\sqrt{X}$开始倒序枚举，可以更快地找到最优解。

### 拓展与举一反三
类似的问题可以通过枚举因数和互质性的思路来解决。例如，寻找满足特定条件的数对或因数分解问题。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)

---
处理用时：37.23秒