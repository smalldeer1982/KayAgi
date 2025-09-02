# 题目信息

# Minimum and Maximum

## 题目描述

This is an interactive problem. You have to use flush operation right after printing each line. For example, in C++ you should use function fflush(stdout), in Java — System.out.flush(), in Pascal — flush(output) and in Python — sys.stdout.flush().

In this problem, you need to find maximal and minimal elements of an array. What could be simpler?

You can imagine that the jury has an array, and initially you know the only number $ n $ — array's length.

Array's elements are numbered from $ 1 $ to $ n $ . You are allowed to compare two elements of the array by using their indices $ i $ and $ j $ . There are three possible responses to this query: '<' (if $ a_{i} $ is less than $ a_{j} $ ), '=' (if $ a_{i} $ is equal to $ a_{j} $ ) and finally '>' (if $ a_{i} $ is greater than $ a_{j} $ ).

It's known that it's always possible to find both maximal and minimal elements of the array by using no more than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF730B/64e27b3d6ef68e5168a71a1fda863cd37a7518ef.png) comparisons, where $ ⌈\ x⌉ $ is the result of rounding $ x $ up.

Write the program that will find positions of the minimum and the maximum in the jury's array of length $ n $ , by using no more than $ f(n) $ comparisons.

## 样例 #1

### 输入

```
2
2
 
&gt;
 
3
 
=
 
=
 ```

### 输出

```
 
 
? 1 2
 
! 2 1
 
? 3 1
 
? 2 1
 
! 2 3```

# AI分析结果



# Minimum and Maximum

## 题目描述

这是一个交互题。你需要在每次输出后立即刷新缓冲区。例如在C++中使用fflush(stdout)，Java中使用System.out.flush()，Python中使用sys.stdout.flush()。

你需要找到数组的最大值和最小值。已知可以通过不超过 $\lceil \frac{3n}{2} \rceil -2$ 次比较完成。

数组元素编号为1到n。每次询问两个下标i和j，会返回'<'、'='或'>'，分别表示$a_i < a_j$、等于或大于。

请编写程序在限定比较次数内找到最大值和最小值的位置。

---

**算法分类**：构造、分治

---

## 题解分析与结论

### 关键思路
采用分组比较策略：
1. 两两分组比较，每组确定较大/较小者
2. 较大者参与最大值竞争，较小者参与最小值竞争
3. 维护当前最大/最小值，通过递推更新极值
4. 奇偶处理：奇数时单独元素初始作为极值

### 最优题解亮点

#### [xwh_hh] ⭐⭐⭐⭐⭐
**核心思路**：
- 奇偶处理：奇数时以末位元素初始化为极值
- 两两分组：每组比较后分别更新极值
- 极值维护：通过三次比较/组（组内比较+极值更新）

**代码实现**：
```cpp
void cmp(int a,int b){
    cout<<"? "<<a<<' '<<b<<endl;
    cin>>c;
}
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        // 初始化极值
        if(n%2==0){
            cmp(n-1,n);
            a = (c=='>' ? n-1 : n);
            b = n*2-1 - a; // 计算互补下标
        }
        // 分组处理
        for(int i=1;i<=n-2;i+=2){
            cmp(i, i+1);
            int u = i, v = i+1;
            if(c=='>') swap(u,v); // 保证u<=v
            
            cmp(a, v);
            if(c=='<') a = v; // 更新最大值
            
            cmp(b, u);
            if(c=='>') b = u; // 更新最小值
        }
        cout<<"! "<<b<<" "<<a<<endl;
    }
}
```

---

## 拓展与应用

### 类似题目推荐
1. P1774 最接近神的人（逆序对分治）
2. P1908 逆序对（分治优化）
3. CF702F T-Shirts（分组贪心策略）

### 技巧总结
- **交互题技巧**：使用`endl`自动刷新缓冲区
- **极值维护**：通过互补计算减少变量
- **分组策略**：奇偶分情况处理保证完整性

---

**个人心得**：
- 初始化处理是代码简洁的关键
- 组内比较时通过swap统一方向简化逻辑
- 互补下标计算技巧（`n*2-1 - a`）避免额外比较

---
处理用时：133.20秒