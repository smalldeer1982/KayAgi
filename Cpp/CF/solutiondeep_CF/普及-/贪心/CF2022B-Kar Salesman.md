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



# Kar Salesman

## 题目描述

卡雷尔是一家汽车经销店的推销员。该店有 $n$ 种不同型号的汽车，其中第 $i$ 种型号有 $a_i$ 辆。卡雷尔可以说服每位顾客购买最多 $x$ 辆不同型号的汽车。求卖完所有汽车所需的最小顾客数量。

## 题解综合分析

### 关键思路
答案取以下两个值的最大值：
1. **最大车型库存**：至少需要 $\max(a_i)$ 个顾客才能卖完库存最多的车型
2. **总量约束**：$\lceil \frac{\sum a_i}{x} \rceil$，每个顾客最多买 $x$ 辆的总量下限

### 最优题解

#### [Zhl2010] ⭐⭐⭐⭐
**亮点**：  
- 使用整数运算避免浮点误差 `(sum+x-1)/x`  
- 正确处理数据范围（开 long long）  
- 代码简洁高效（时间复杂度 O(n)）

```cpp
#define int long long
signed main(){
    int T; cin>>T;
    while(T--){
        int n,x,sum=0,ma=0,a;
        cin>>n>>x;
        for(int i=1;i<=n;i++){
            scanf("%lld",&a);
            sum+=a;
            ma = max(ma,a);
        }
        cout<<max(ma, (sum+x-1)/x )<<endl;
    }
}
```

#### [linjinkun] ⭐⭐⭐⭐
**亮点**：  
- 强调数据类型的常见陷阱  
- 使用更直观的取模运算处理余数  
**个人心得**：  
> "十年 OI 一场空，不开 long long 见祖宗"

```cpp
#define int long long 
signed main() {
    int _;
    scanf("%lld",&_);
    while(_--) {
        int n,x,ans=0,maxx=0;
        scanf("%lld %lld",&n,&x);
        for(int i=1;i<=n;i++) {
            int x; scanf("%lld",&x);
            ans+=x;
            maxx = max(maxx,x);
        }
        printf("%lld\n",max(maxx, (ans+x-1)/x ));
    }
}
```

#### [cly312] ⭐⭐⭐⭐
**亮点**：  
- 采用布尔表达式处理余数 `sum%x!=0`  
- 代码风格简洁明快  

```cpp
#include <iostream>
using namespace std;
int main(){
    int t; cin>>t;
    while(t--){
        long long n,x,sum=0,mx=0,in;
        cin>>n>>x;
        while(n--){
            cin>>in;
            mx = max(mx,in);
            sum += in;
        }
        cout<<max(mx, sum/x + (sum%x!=0)) <<"\n";
    }
}
```

## 拓展练习
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 优先队列实现贪心  
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 多条件约束下的极值问题  
3. [CF1328C Ternary XOR](https://codeforces.com/problemset/problem/1328/C) - 双约束条件下的构造问题

---
处理用时：77.68秒