# 题目信息

# [USACO21FEB] Year of the Cow B

## 题目描述

Farmer John 的奶牛们得知最近正在庆祝牛年的到来时十分兴奋。牛年总是奶牛们的最爱。

我们知道，中国历法中每一年所对应的生肖遵循 $12$ 年的周期：Ox, Tiger, Rabbit, Dragon, Snake, Horse, Goat, Monkey, Rooster, Dog, Pig, Rat（牛、虎、兔、龙、蛇、马、羊、猴、鸡、狗、猪、鼠），然后回到牛。

奶牛 Bessie 自豪地说她是在许多年前的一个牛年出生的。她的朋友 Elsie 想要知道她与 Bessie 出生相差多少年，并且希望你能够通过查看农场上若干奶牛出生年份之间的关系来帮助她推算。 

## 说明/提示

### 样例解释 1

在以上的输入中，

- Elsie 在 Bessie 之前 $12$ 年出生。
- Mildred 在 Bessie 之前 $9$ 年出生。
- Gretta 在 Bessie 之前 $17$ 年出生。
- Paulina 在 Bessie 之后 $9$ 年出生。

## 样例 #1

### 输入

```
4
Mildred born in previous Dragon year from Bessie
Gretta born in previous Monkey year from Mildred
Elsie born in next Ox year from Gretta
Paulina born in next Dog year from Bessie```

### 输出

```
12```

# AI分析结果



### 综合分析与结论
本题核心在于通过相对生肖关系建立年份差模型，利用数学公式处理周期性问题。最优解法通过映射存储信息并推导公式直接计算年份差，避免了逐次遍历的低效操作。关键点包括正确分情况处理"previous"和"next"的跨周期情况，以及利用数据结构快速索引节点信息。

---

### 精选题解

#### 1. 作者：Harlem（4星）
**关键亮点**  
- 使用`map`高效管理奶牛信息，代码简洁清晰。  
- 推导数学公式直接处理跨周期年份差，逻辑严谨。  
- 利用题目约束条件简化问题，确保无环依赖。  

**核心代码**  
```cpp
if(pd=="previous"){
    if(y[i]<y[id[b]]){
        c[i]=c[id[b]]+(y[i]-y[id[b]]);
    }
    else{
        c[i]=c[id[b]]+(y[i]-12-y[id[b]]);
    }
}
if(pd=="next"){
    if(y[i]>y[id[b]]){
        c[i]=c[id[b]]+(y[i]-y[id[b]]);
    }
    else{
        c[i]=c[id[b]]+(y[i]+12-y[id[b]]);
    }
}
```

---

#### 2. 作者：Vct14（4星）
**关键亮点**  
- 假设Bessie为基准年（2021），直观计算绝对年份。  
- 封装`getc`函数统一处理年份差，代码高度模块化。  
- 利用方向参数`g`简化条件判断，逻辑紧凑。  

**核心代码**  
```cpp
int getc(string D1,string D2,int g){ 
    int d1=getn(D1),d2=getn(D2);
    if(d1==d2) return 12;
    return ((d2-d1)*g+12)%12;
}
// 调用
m2[ca] = m2[cb] + getc(m1[cb],dw,f)*f; 
```

---

#### 3. 作者：XiaoWhy（4星）
**关键亮点**  
- 直接公式法，通过`get`函数分方向计算年份差。  
- 代码简洁，利用`map`存储生肖和年份，无冗余操作。  
- 显式处理同生肖情况，避免潜在错误。  

**核心代码**  
```cpp
int get(int x,int y,int f){
    if(f==0){ // previous
        if(x<y) return y-x;
        else return 12-x+y;
    }else{ // next
        if(x>y) return x-y;
        else return 12-y+x;
    }
}
```

---

### 关键思路与技巧
1. **周期处理公式**：将生肖映射为0-11的数值，通过`(差值 + 12) % 12`处理跨周期情况。
2. **方向参数统一**：用正负1表示"next"和"previous"，简化条件分支。
3. **基准年假设**：以Bessie为基准（如年份0或2021），避免处理绝对时间。
4. **数据结构选择**：优先使用`map`管理动态添加的节点，平衡效率与代码简洁性。

---

### 拓展练习
1. [P2921 USACO08DEC] Trick or Treat on the Farm（图论建模）  
2. [P1217 USACO1.5] 回文质数（周期性质与数学优化）  
3. [P6384 MdOI R2] Quo Vadis（复杂周期性计算）  

---

### 个人心得摘录
- **Harlem**：题目约束确保依赖无环，可直接顺序处理关系。  
- **HMSVanguard**：字典树虽非最优解，但展示了多数据结构适应性。  
- **卷王**：多次遍历确保所有关系被处理，暴力的正确性验证方法。

---
处理用时：110.64秒