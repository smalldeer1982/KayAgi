# 题目信息

# Coins and Queries

## 题目描述

Polycarp has $ n $ coins, the value of the $ i $ -th coin is $ a_i $ . It is guaranteed that all the values are integer powers of $ 2 $ (i.e. $ a_i = 2^d $ for some non-negative integer number $ d $ ).

Polycarp wants to know answers on $ q $ queries. The $ j $ -th query is described as integer number $ b_j $ . The answer to the query is the minimum number of coins that is necessary to obtain the value $ b_j $ using some subset of coins (Polycarp can use only coins he has). If Polycarp can't obtain the value $ b_j $ , the answer to the $ j $ -th query is -1.

The queries are independent (the answer on the query doesn't affect Polycarp's coins).

## 样例 #1

### 输入

```
5 4
2 4 8 2 4
8
5
14
10
```

### 输出

```
1
-1
3
2
```

# AI分析结果

【题目内容】
# 硬币与查询

## 题目描述

Polycarp有$n$枚硬币，第$i$枚硬币的面值为$a_i$。保证所有面值都是2的整数次幂（即$a_i = 2^d$，其中$d$为非负整数）。

Polycarp想知道$q$次查询的答案。第$j$次查询由一个整数$b_j$描述。查询的答案是用Polycarp拥有的硬币子集凑出$b_j$所需的最少硬币数。如果无法凑出$b_j$，则查询的答案为-1。

查询是独立的（查询的答案不会影响Polycarp的硬币）。

## 样例 #1

### 输入

```
5 4
2 4 8 2 4
8
5
14
10
```

### 输出

```
1
-1
3
2
```

【算法分类】贪心

【题解分析与结论】

这道题的核心思路是贪心算法。由于硬币的面值都是2的幂次，因此从大到小依次选择硬币，尽可能多地使用大面值的硬币，可以保证使用最少的硬币数。如果最终无法凑出目标值，则输出-1。

【评分较高的题解】

1. **作者：NaN_HQJ2007_NaN (赞：11)**  
   - **星级：4.5**  
   - **关键亮点**：使用`map`存储硬币面值及其数量，从大到小遍历，贪心地选择硬币。代码清晰，解释详细，适合初学者理解。  
   - **核心代码**：
     ```cpp
     map<int,int> m;
     for(i=1;i<=n;i++){
         scanf("%d",&a);
         m[a]++;
     }
     map<int,int>::iterator it;
     for(i=1;i<=q;i++){
         int ans=0;
         scanf("%d",&b);
         it=m.end();
         while(1){
             it--;
             int minn=min(b/(it->first),it->second);
             b-=minn*(it->first);
             ans+=minn;
             if(it==m.begin() && b!=0){
                 printf("-1\n");
                 break;
             }else if(b==0){
                 printf("%d\n",ans);
                 break;
             }
         }
     }
     ```

2. **作者：Ryo_Yamada (赞：7)**  
   - **星级：4**  
   - **关键亮点**：使用数组存储2的幂次对应的硬币数量，从高位到低位贪心选择硬币。代码简洁，效率高。  
   - **核心代码**：
     ```cpp
     int cnt[40];
     for(int i = 1; i <= n; i++) { 
         int x; scanf("%d", &x); 
         ++cnt[(int)(log2(x))]; 
     }
     while(q--) {
         int x, ans = 0;
         scanf("%d", &x);
         for(int i = 31; ~i; i--) {
             int m = min(cnt[i], x / (1 << i));
             ans += m;
             x -= m * (1ll << i);
         }
         printf("%d\n", x ? -1 : ans);
     }
     ```

3. **作者：loving丶Drug (赞：7)**  
   - **星级：4**  
   - **关键亮点**：使用`map`存储硬币面值及其数量，从大到小遍历，贪心地选择硬币。代码简洁，适合熟悉STL的读者。  
   - **核心代码**：
     ```cpp
     map <int, int> Q;
     for (int i = 1; i <= n; ++i) {
         a = read ();
         ++ Q[a];
     }
     while (q--) {
         ans = 0;
         b = read ();
         it = Q.end();
         it--;
         for (;; --it) {
             int t = min (b/it->first, it->second);
             b -= t * it->first;
             ans += t;
             if (!b) {
                 cout << ans << endl;
                 break;
             }
             if (it == Q.begin() && b != 0) {
                 cout << -1 << endl;
                 break;
             }
         }
     }
     ```

【最优关键思路】  
从大到小贪心地选择硬币，尽可能多地使用大面值的硬币，可以保证使用最少的硬币数。使用`map`或数组存储硬币面值及其数量，方便快速查询和计算。

【可拓展之处】  
类似的问题可以扩展到其他面值的组合，或者扩展到其他进制（如3进制、5进制等）的硬币组合问题。

【推荐题目】  
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)  
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：34.91秒