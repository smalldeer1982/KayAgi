# 题目信息

# Preparation for International Women's Day

## 题目描述

International Women's Day is coming soon! Polycarp is preparing for the holiday.

There are $ n $ candy boxes in the shop for sale. The $ i $ -th box contains $ d_i $ candies.

Polycarp wants to prepare the maximum number of gifts for $ k $ girls. Each gift will consist of exactly two boxes. The girls should be able to share each gift equally, so the total amount of candies in a gift (in a pair of boxes) should be divisible by $ k $ . In other words, two boxes $ i $ and $ j $ ( $ i \ne j $ ) can be combined as a gift if $ d_i + d_j $ is divisible by $ k $ .

How many boxes will Polycarp be able to give? Of course, each box can be a part of no more than one gift. Polycarp cannot use boxes "partially" or redistribute candies between them.

## 说明/提示

In the first example Polycarp can give the following pairs of boxes (pairs are presented by indices of corresponding boxes):

- $ (2, 3) $ ;
- $ (5, 6) $ ;
- $ (1, 4) $ .

So the answer is $ 6 $ .

In the second example Polycarp can give the following pairs of boxes (pairs are presented by indices of corresponding boxes):

- $ (6, 8) $ ;
- $ (2, 3) $ ;
- $ (1, 4) $ ;
- $ (5, 7) $ .

So the answer is $ 8 $ .

In the third example Polycarp can give the following pairs of boxes (pairs are presented by indices of corresponding boxes):

- $ (1, 2) $ ;
- $ (6, 7) $ .

So the answer is $ 4 $ .

## 样例 #1

### 输入

```
7 2
1 2 2 3 2 4 10
```

### 输出

```
6
```

## 样例 #2

### 输入

```
8 2
1 2 2 3 2 4 6 10
```

### 输出

```
8
```

## 样例 #3

### 输入

```
7 3
1 2 2 3 2 4 5
```

### 输出

```
4
```

# AI分析结果

### 题目内容重写
**题目描述**  
国际妇女节即将到来！Polycarp正在为这个节日做准备。  
商店里有 $n$ 个糖果盒出售，第 $i$ 个盒子包含 $d_i$ 颗糖果。  
Polycarp想为 $k$ 个女孩准备尽可能多的礼物。每个礼物由恰好两个盒子组成。女孩们需要能够平等地分享每个礼物，因此每个礼物中的糖果总数（即两个盒子的糖果数之和）必须能被 $k$ 整除。换句话说，两个盒子 $i$ 和 $j$（$i \ne j$）可以组合成一个礼物，当且仅当 $d_i + d_j$ 能被 $k$ 整除。  
Polycarp最多能送出多少个盒子？当然，每个盒子最多只能是一个礼物的一部分。Polycarp不能“部分使用”盒子或重新分配糖果。

### 算法分类
数学

### 题解分析与结论
题目要求将糖果盒两两配对，使得每对盒子的糖果数之和能被 $k$ 整除。核心思路是利用模运算的性质，将问题转化为余数的配对问题。具体来说，两个盒子的糖果数之和能被 $k$ 整除，当且仅当它们的余数之和为 $0$ 或 $k$。因此，我们可以统计每个余数的出现次数，然后根据余数的配对规则计算最大配对数。

### 评分较高的题解
1. **作者：I_like_magic (赞：10)**  
   **星级：5**  
   **关键亮点**：思路清晰，代码简洁，特别处理了 $k$ 为偶数时余数为 $k/2$ 的情况，输出时记得乘 $2$。  
   **核心代码**：
   ```cpp
   int n,k,cnt[100],sum;
   int main(){
       n=read(),k=read();
       for(int i=1;i<=n;i++){
           int a=read();
           cnt[a%k]++;
       }
       sum+=cnt[0]/2;
       for(int i=1;i<k/2.0;i++) sum+=min(cnt[i],cnt[k-i]);
       if(k%2==0) sum+=cnt[k/2]/2;
       printf("%d",sum*2);
       return 0;
   }
   ```

2. **作者：AzureMist (赞：6)**  
   **星级：4**  
   **关键亮点**：代码结构清晰，特判了余数为 $0$ 和 $k/2$ 的情况，逻辑严谨。  
   **核心代码**：
   ```cpp
   int n,k,sum=0;
   int main(){
       cin>>n>>k;
       int d[n],r[k];
       memset(r,0,sizeof(r));
       for(int i=0;i<=n-1;i++){
           cin>>d[i];
           r[d[i]%k]++;
       }
       for(int i=0;i<=k/2;i++){
           if(i==0||i*2==k) sum=sum+r[i]/2;
           else sum=sum+min(r[i],r[k-i]);
       }
       sum*=2;
       cout<<sum;
       return 0;
   }
   ```

3. **作者：fuxuantong123 (赞：4)**  
   **星级：4**  
   **关键亮点**：代码简洁，逻辑清晰，特别处理了余数为 $0$ 和 $k/2$ 的情况。  
   **核心代码**：
   ```cpp
   int mp[110];
   int main(){
       int n,k;
       scanf("%d%d",&n,&k);
       int ans=0;
       for(int i=1;i<=n;i++){
           int fw;
           scanf("%d",&fw);
           mp[fw%k]++;
       }
       for(int i=0;i<=k/2;i++){
           if(i==k-i || i==0) ans+=mp[i]/2;
           else ans+=min(mp[i],mp[k-i]);
       }
       printf("%d",ans*2);
       return 0;
   }
   ```

### 最优关键思路
1. **余数配对**：利用模运算的性质，将问题转化为余数的配对问题，统计每个余数的出现次数，然后根据余数的配对规则计算最大配对数。
2. **特判处理**：特别处理余数为 $0$ 和 $k/2$ 的情况，确保配对的正确性。
3. **输出处理**：最终结果需要乘以 $2$，因为每对配对对应两个盒子。

### 可拓展之处
类似的问题可以扩展到多个数的配对，或者扩展到其他模运算相关的题目。例如，给定一个数组，求有多少对数的和、差、积等满足某种模运算条件。

### 推荐题目
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)  
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)  
3. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)

---
处理用时：29.84秒