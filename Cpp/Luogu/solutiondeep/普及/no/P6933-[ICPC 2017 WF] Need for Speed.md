# 题目信息

# [ICPC 2017 WF] Need for Speed

## 题目描述

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14637/1.png)

Sheila is a student and she drives at ypical student car: it is old, slow, rusty, and falling apart. Recently,the needle on the speedometer fell off. She glued it back on, but she might have placed it at the wrong angle. Thus, when the speedometer reads $s$,her true speed is $s+c$, where $c$ is an unknown constant(possibly negative).

Sheila made a careful record of a recent journey and wants to use this to compute $c$ . The journey consisted of $n$ segments. In the $i^{th}$ segment she traveled a distance of $d_{i}$ and the speedometer read $s_{i}$ for the entire segment. This whole journey took time $t$ . Help Sheila by computing $c$ .

Note that while Sheila's speedometer might have negative readings, her true speed was greater than zero for each segment of the journey.



## 说明/提示

Time limit: 1 s, Memory limit: 512 MB. 

spj provider:@[shenyouran](/user/137367).

## 样例 #1

### 输入

```
3 5
4 -1
4 0
10 3
```

### 输出

```
3.000000000
```

## 样例 #2

### 输入

```
4 10
5 3
2 2
3 6
3 1
```

### 输出

```
-0.508653377
```

# AI分析结果



**算法分类**  
二分

**题解综合分析**  
所有题解均采用浮点数二分法求解速度修正值c，核心思路为：  
1. 通过时间公式 ∑d_i/(s_i+c) = t 构造check函数  
2. 确定c的下界为 -min(s_i) 保证速度>0  
3. 设置合理上界(如1e9)后二分  
关键难点在于浮点精度控制(1e-7)和边界条件处理

**优质题解推荐**  

1. **一只小咕咕（4星）**  
   **亮点**：正确指出输入需用double类型，规范处理浮点精度，代码简洁清晰  
   **代码核心**：
   ```cpp
   bool check(double c){
       double ans=0;
       for(int i=1;i<=n;i++)
           ans += d[i]/(s[i]+c);
       return ans>=t; // 总时间>=t时c可增大
   }
   ```
   
2. **Flaw_Owl（4星）**  
   **亮点**：详细推导边界条件，建议控制循环次数替代精度比较  
   **心得**："被double类型坑了好久，必须所有计算变量声明为double"  
   **代码核心**：
   ```cpp
   while(R - L > eps) { // 显式精度控制
       double mid = L + (R-L)/2;
       if(check(mid)) R = mid;
       else L = mid;
   }
   ```

**关键技巧总结**  
1. **边界确定**：左边界 l = -min(s_i)，确保每段速度>0  
2. **精度控制**：循环直到 r-l < 1e-7，输出保留9位小数  
3. **浮点处理**：使用(double)运算，避免整数除法  
4. **单调性**：c增大→总时间减少→二分方向判断

**同类题目推荐**  
- P1024 [一元三次方程求解]：浮点二分经典应用  
- P3743 kotori的设备：设备运行时间最大化  
- P1182 数列分段 Section II：二分答案+可行性验证

---
处理用时：33.42秒