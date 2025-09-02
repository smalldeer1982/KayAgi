# 题目信息

# Flamingoes of Mystery

## 题目描述

This is an interactive problem. You have to use a flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout), in Java — System.out.flush(), in Pascal — flush(output) and in Python — sys.stdout.flush().

Mr. Chanek wants to buy a flamingo to accompany his chickens on his farm. Before going to the pet shop, Mr. Chanek stops at an animal festival to have fun. It turns out there is a carnival game with a flamingo as the prize.

There are $ N $ mysterious cages, which are numbered from $ 1 $ to $ N $ . Cage $ i $ has $ A_i $ $ (0 \le A_i \le 10^3) $ flamingoes inside $ (1 \le i \le N) $ . However, the game master keeps the number of flamingoes inside a secret. To win the flamingo, Mr. Chanek must guess the number of flamingoes in each cage.

Coincidentally, Mr. Chanek has $ N $ coins. Each coin can be used to ask once, what is the total number of flamingoes inside cages numbered $ L $ to $ R $ inclusive? With $ L < R $ .

## 说明/提示

In the sample input, the correct flamingoes amount is $ [1, 4, 4, 6, 7, 8] $ .

## 样例 #1

### 输入

```
6
 
5
 
15
 
10
 ```

### 输出

```
 
? 1 2
 
? 5 6
 
? 3 4
 
! 1 4 4 6 7 8```

# AI分析结果

### 题目内容重写（中文）

#### 神秘的火烈鸟

## 题目描述

这是一道交互题。你必须在每次打印一行后立即使用刷新操作。例如，在C++中你应该使用函数`fflush(stdout)`，在Java中使用`System.out.flush()`，在Pascal中使用`flush(output)`，在Python中使用`sys.stdout.flush()`。

Mr. Chanek想买一只火烈鸟来陪伴他农场里的鸡。在去宠物店之前，Mr. Chanek在一个动物节上停下来玩耍。结果发现有一个以火烈鸟为奖品的嘉年华游戏。

有$N$个神秘的笼子，编号从$1$到$N$。笼子$i$里面有$A_i$只火烈鸟（$0 \le A_i \le 10^3$，$1 \le i \le N$）。然而，游戏主持人将笼子里的火烈鸟数量保密。为了赢得火烈鸟，Mr. Chanek必须猜出每个笼子里的火烈鸟数量。

巧合的是，Mr. Chanek有$N$个硬币。每个硬币可以用来询问一次，编号从$L$到$R$（包含$L$和$R$）的笼子里共有多少只火烈鸟？其中$L < R$。

## 说明/提示

在样例输入中，正确的火烈鸟数量是$[1, 4, 4, 6, 7, 8]$。

## 样例 #1

### 输入

```
6

5

15

10
```

### 输出

```

? 1 2

? 5 6

? 3 4

! 1 4 4 6 7 8
```

---

### 题解综合分析与结论

这道题的核心在于通过有限次数的区间和询问，推导出每个笼子中的火烈鸟数量。所有题解都利用了前缀和和差分的思路，通过询问$1$到$i$的区间和，再通过差分得到每个笼子的数量。难点在于如何通过$n$次询问得到所有笼子的数量，尤其是如何处理前两个笼子的数量。

#### 关键思路与技巧：
1. **前缀和与差分**：通过询问$1$到$i$的区间和，再通过差分得到每个笼子的数量。
2. **最后一次询问的处理**：通过询问$2$到$n$的区间和，结合之前的结果，推导出第一个和第二个笼子的数量。
3. **交互题的处理**：每次询问后需要刷新输出缓冲区，确保及时获取结果。

#### 推荐题解：
1. **RioFutaba (4星)**  
   - **亮点**：清晰地解释了如何通过前缀和和差分推导出每个笼子的数量，尤其是如何处理前两个笼子的数量。
   - **代码简洁**：代码结构清晰，逻辑严谨，易于理解。
   - **核心代码**：
     ```cpp
     for(int i=2;i<=n;i++){ 
         cout << "? 1 " << i << endl;
         cin >> res[i];
         a[i]=res[i]-res[i-1];
     }
     cout << "? 2 " << n << endl;
     cin >> x;
     a[1]=res[n]-x;
     a[2]-=a[1];
     ```

2. **ZQIN_P (4星)**  
   - **亮点**：详细解释了如何通过询问$1$到$i$的区间和，再通过差分得到每个笼子的数量，尤其是如何处理前两个笼子的数量。
   - **代码简洁**：代码结构清晰，逻辑严谨，易于理解。
   - **核心代码**：
     ```cpp
     cout<<"? 1 2"<<endl;
     cin>>num1;
     num=num1;
     for(int i=3;i<=n;i++){
         cout<<"? 1 "<<i<<endl;
         cin>>num2;
         a[i]=num2-num1;
         num1=num2;
     }
     cout<<"? 2 3"<<endl;
     cin>>num2;
     a[2]=num2-a[3];
     a[1]=num-a[2];
     ```

3. **charleshe (4星)**  
   - **亮点**：通过询问$1$到$n$的区间和，再通过询问$2$到$n$的区间和，推导出第一个和第二个笼子的数量。
   - **代码简洁**：代码结构清晰，逻辑严谨，易于理解。
   - **核心代码**：
     ```cpp
     cout<<"? "<<1<<" "<<n<<endl;
     cin>>lst;
     _1n=lst;
     for(int i=2;i<n;i++){
         cout<<"? "<<i<<" "<<n<<endl;
         cin>>nw;
         a[i-1]=lst-nw;
         lst=nw;
     }
     cout<<"? "<<1<<" "<<n-1<<endl;
     cin>>nw;
     a[n]=_1n-nw;
     a[n-1]=lst-a[n];
     ```

#### 可拓展之处：
- **类似题目**：可以通过前缀和和差分的思想解决类似的区间和问题，如求区间最大值、最小值等。
- **交互题处理**：在交互题中，及时刷新输出缓冲区是关键，确保程序能够及时获取输入。

#### 推荐题目：
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：44.02秒