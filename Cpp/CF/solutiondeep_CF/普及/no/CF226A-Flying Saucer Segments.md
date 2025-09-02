# 题目信息

# Flying Saucer Segments

## 题目描述

An expedition group flew from planet ACM-1 to Earth in order to study the bipedal species (its representatives don't even have antennas on their heads!).

The flying saucer, on which the brave pioneers set off, consists of three sections. These sections are connected by a chain: the 1-st section is adjacent only to the 2-nd one, the 2-nd one — to the 1-st and the 3-rd ones, the 3-rd one — only to the 2-nd one. The transitions are possible only between the adjacent sections.

The spacecraft team consists of $ n $ aliens. Each of them is given a rank — an integer from $ 1 $ to $ n $ . The ranks of all astronauts are distinct. The rules established on the Saucer, state that an alien may move from section $ a $ to section $ b $ only if it is senior in rank to all aliens who are in the segments $ a $ and $ b $ (besides, the segments $ a $ and $ b $ are of course required to be adjacent). Any alien requires exactly $ 1 $ minute to make a move. Besides, safety regulations require that no more than one alien moved at the same minute along the ship.

Alien $ A $ is senior in rank to alien $ B $ , if the number indicating rank $ A $ , is more than the corresponding number for $ B $ .

At the moment the whole saucer team is in the 3-rd segment. They all need to move to the 1-st segment. One member of the crew, the alien with the identification number CFR-140, decided to calculate the minimum time (in minutes) they will need to perform this task.

Help CFR-140, figure out the minimum time (in minutes) that all the astronauts will need to move from the 3-rd segment to the 1-st one. Since this number can be rather large, count it modulo $ m $ .

## 说明/提示

In the first sample the only crew member moves from segment 3 to segment 2, and then from segment 2 to segment 1 without any problems. Thus, the whole moving will take two minutes.

To briefly describe the movements in the second sample we will use value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/45444f2fa560c0037b27d01242b8d4bbde1358aa.png), which would correspond to an alien with rank $ i $ moving from the segment in which it is at the moment, to the segment number $ j $ . Using these values, we will describe the movements between the segments in the second sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/555702f9a61a62f33a391773ccade066ae7cb236.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/32a8caec69f00b67073f877bf4e1c3dbf2cc908d.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/ba5c75ab2dad5cb62463c51a0022dba3fcb2b02b.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/6d7099024bb756bbfa4f326bc16f9c9c0f8e6d88.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/555702f9a61a62f33a391773ccade066ae7cb236.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png); In total: the aliens need 26 moves. The remainder after dividing $ 26 $ by $ 8 $ equals $ 2 $ , so the answer to this test is $ 2 $ .

## 样例 #1

### 输入

```
1 10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 8
```

### 输出

```
2
```

# AI分析结果



题目内容已为中文，无需重复翻译。

**算法分类**：数学

---

### 题解综合分析与结论
所有题解均基于数学推导，通过递推公式 $f(n) = 3^n -1$ 结合快速幂求解。核心难点在于发现递推关系并推导通项，以及处理大数取模。最优思路是快速幂+数学递推公式的直接应用。

---

### 精选题解与评分
1. **作者：ooliver（★★★★☆）**  
   **关键亮点**：同时给出递推推导和找规律两种方法，代码简洁高效。  
   **个人心得**：通过对比汉诺塔问题，发现系数差异，巧妙构造递推式。

2. **作者：小杨小小杨（★★★★☆）**  
   **关键亮点**：将递推式转换为等比数列求和，数学推导清晰。  
   **核心代码**：
   ```cpp
   int f_pow(long long x, long long y, long long mod) {
       long long tmp = 1;
       while (y > 0) {
           if (y & 1) tmp = tmp * x % mod;
           y >>= 1; x = x * x % mod;
       }
       return tmp;
   }
   ```

3. **作者：Noby_Glds（★★★★☆）**  
   **关键亮点**：详细模拟移动步骤，明确得出递推式，代码包含负数处理注释。  
   **核心代码**：
   ```cpp
   int Pow(int x, int y) {
       int ans = 1;
       while (y) {
           if (y % 2) ans = ans * x % m;
           y /= 2, x = x * x % m;
       }
       return ans;
   }
   ```

---

### 最优思路总结
**关键技巧**：  
1. 将复杂移动规则抽象为递推式 $f(n)=3f(n-1)+2$，通过构造等比数列求得通项 $f(n)=3^n-1$。  
2. 利用快速幂计算大指数取模，注意最终结果加模数再取模避免负数。

---

### 拓展与相似题目
**类似题型套路**：递推式转通项（如斐波那契数列）、汉诺塔变种问题。  
**推荐题目**：  
1. [P1760 汉诺塔](https://www.luogu.com.cn/problem/P1760)  
2. [P1225 黑白棋子的移动](https://www.luogu.com.cn/problem/P1225)  
3. [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)

---
处理用时：35.56秒