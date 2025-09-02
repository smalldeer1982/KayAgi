# 题目信息

# Everyone is a Winner!

## 题目描述

给定$n$ 对于所有正整数$k$求出$\lfloor \frac{n}{k} \rfloor$可以有多少种不同的值 并求出所有可能的值

## 样例 #1

### 输入

```
4
5
11
1
3
```

### 输出

```
4
0 1 2 5 
6
0 1 2 3 5 11 
2
0 1 
3
0 1 3 
```

# AI分析结果

### 题目翻译
# 人人都是赢家！

## 题目描述
给定 $n$，对于所有正整数 $k$，求出 $\lfloor \frac{n}{k} \rfloor$ 有多少种不同的值，并求出所有可能的值。

## 样例 #1
### 输入
```
4
5
11
1
3
```

### 输出
```
4
0 1 2 5 
6
0 1 2 3 5 11 
2
0 1 
3
0 1 3 
```

### 算法分类
数学

### 综合分析与结论
这三道题解均围绕求解 $\lfloor \frac{n}{k} \rfloor$ 不同取值展开。Rainbow_qwq 先尝试 $O(n)$ 暴力法，后通过打表找规律，利用枚举和排序求解，时间复杂度为 $O(\sqrt{n} \log{\sqrt{n}})$；Karry5307 运用整除分块思想，借助递归实现；woshishei 同样采用整除分块思想，迭代更新 $cur$ 变量求解。三者都利用了整除分块的特性，不同在于实现方式和复杂度分析。

### 所选的题解
- **Rainbow_qwq（4星）**：
    - **关键亮点**：思路清晰，先尝试暴力法，再通过打表找规律，最后给出证明，代码简洁易读。
    - **个人心得**：2019/12/2 上午突然想出证明方法，过来补一下。

### 重点代码
```cpp
int n;
vector<int>res;
void work()
{
    res.clear();
    n=read();
    int sqn=sqrt(1.0*n);
    For(i,0,sqn){
        res.push_back(i);
        if(i&&i!=n/i)res.push_back(n/i);
    }
    sort(res.begin(),res.end());
    cout<<res.size()<<endl;
    For(i,0,res.size()-1)printf("%d ",res[i]);
    puts("");
}
```
**核心实现思想**：先计算 $\sqrt{n}$，然后枚举 $0$ 到 $\sqrt{n}$ 的数，将其本身和 $\lfloor\frac{n}{i}\rfloor$ 加入结果数组，最后排序输出。

### 拓展思路
同类型题目常涉及整除分块的应用，如求解区间内满足某种整除条件的数的个数等。类似算法套路可用于处理一些与整数除法相关的数学问题，通过分块减少不必要的计算。

### 推荐题目
1. [P2261 余数求和](https://www.luogu.com.cn/problem/P2261)
2. [P3935 Calculating](https://www.luogu.com.cn/problem/P3935)
3. [P2424 约数和](https://www.luogu.com.cn/problem/P2424)

---
处理用时：22.76秒