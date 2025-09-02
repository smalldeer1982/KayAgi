# 题目信息

# Lonely Mountain Dungeons

## 题目描述

Once, the people, elves, dwarves, and other inhabitants of Middle-earth gathered to reclaim the treasures stolen from them by Smaug. In the name of this great goal, they rallied around the powerful elf Timothy and began to plan the overthrow of the ruler of the Lonely Mountain.

The army of Middle-earth inhabitants will consist of several squads. It is known that each pair of creatures of the same race, which are in different squads, adds $ b $ units to the total strength of the army. But since it will be difficult for Timothy to lead an army consisting of a large number of squads, the total strength of an army consisting of $ k $ squads is reduced by $ (k - 1) \cdot x $ units. Note that the army always consists of at least one squad.

It is known that there are $ n $ races in Middle-earth, and the number of creatures of the $ i $ -th race is equal to $ c_i $ . Help the inhabitants of Middle-earth determine the maximum strength of the army they can assemble.

## 说明/提示

In the first test case, the inhabitants of Middle-earth can form $ 3 $ squads. Since $ x = 0 $ , the army's strength will not decrease due to the number of squads. The inhabitants can be distributed among the squads as follows:

- The single representative of the first species can be sent to the first squad.
- The first representative of the second species can be sent to the first squad, the second representative of the second species can be sent to the second squad. Then the total strength of the army will increase by $ b = 1 $ .
- The first representative of the third species can be sent to the first squad, the second representative of the third species can be sent to the second squad, the third representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 3 \cdot b = 3 $ , as they form three pairs in different squads.

Thus, the total strength of the army is $ 4 $ .

In the second test case, the inhabitants of Middle-earth can form $ 3 $ squads. Since $ x = 10 $ , the army's strength will decrease by $ 20 $ . The inhabitants can be distributed among the squads as follows:

- The first representative of the first species can be sent to the first squad, the second representative of the first species can be sent to the second squad. Then the total strength of the army will increase by $ b = 5 $ .
- The first and second representatives of the second species can be sent to the first squad, the third and fourth representatives of the second species can be sent to the second squad, the fifth representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 8 \cdot b = 40 $ .
- The first representative of the third species can be sent to the first squad, the second representative of the third species can be sent to the second squad, the third representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 3 \cdot b = 15 $ , as they form three pairs in different squads.

Thus, the total strength of the army is $ 5 + 40 + 15 - 20 = 40 $ .

## 样例 #1

### 输入

```
5
3 1 0
1 2 3
3 5 10
2 5 3
4 3 3
3 2 1 2
4 1 0
4 1 4 2
4 1 10
4 1 4 2```

### 输出

```
4
40
9
13
0```

# AI分析结果

### 题目内容重写

# 孤山地下城

## 题目描述

曾经，中土世界的人类、精灵、矮人以及其他种族聚集在一起，准备夺回被史矛革偷走的宝藏。为了实现这一伟大目标，他们团结在强大的精灵蒂莫西周围，开始策划推翻孤山统治者的计划。

中土世界的军队将由多个小队组成。已知每对不同小队中的同种族生物会为军队的总力量增加 $b$ 单位。但由于蒂莫西难以指挥由大量小队组成的军队，因此由 $k$ 个小队组成的军队的总力量会减少 $(k - 1) \cdot x$ 单位。注意，军队至少由一个小队组成。

已知中土世界有 $n$ 个种族，第 $i$ 个种族的生物数量为 $c_i$。请帮助中土世界的居民们确定他们可以组建的军队的最大力量。

## 说明/提示

在第一个测试用例中，中土世界的居民可以组成 $3$ 个小队。由于 $x = 0$，军队的力量不会因为小队数量而减少。居民可以按以下方式分配到小队中：

- 第一个种族的唯一代表可以被分配到第一个小队。
- 第二个种族的第一个代表可以被分配到第一个小队，第二个代表可以被分配到第二个小队。这样，军队的总力量将增加 $b = 1$。
- 第三个种族的第一个代表可以被分配到第一个小队，第二个代表可以被分配到第二个小队，第三个代表可以被分配到第三个小队。这样，军队的总力量将增加 $3 \cdot b = 3$，因为他们形成了三对不同小队的组合。

因此，军队的总力量为 $4$。

在第二个测试用例中，中土世界的居民可以组成 $3$ 个小队。由于 $x = 10$，军队的力量将减少 $20$。居民可以按以下方式分配到小队中：

- 第一个种族的第一个代表可以被分配到第一个小队，第二个代表可以被分配到第二个小队。这样，军队的总力量将增加 $b = 5$。
- 第二个种族的第一个和第二个代表可以被分配到第一个小队，第三个和第四个代表可以被分配到第二个小队，第五个代表可以被分配到第三个小队。这样，军队的总力量将增加 $8 \cdot b = 40$。
- 第三个种族的第一个代表可以被分配到第一个小队，第二个代表可以被分配到第二个小队，第三个代表可以被分配到第三个小队。这样，军队的总力量将增加 $3 \cdot b = 15$，因为他们形成了三对不同小队的组合。

因此，军队的总力量为 $5 + 40 + 15 - 20 = 40$。

## 样例 #1

### 输入

```
5
3 1 0
1 2 3
3 5 10
2 5 3
4 3 3
3 2 1 2
4 1 0
4 1 4 2
4 1 10
4 1 4 2```

### 输出

```
4
40
9
13
0```

### 算法分类
数学、差分

### 题解分析与结论

题目要求计算在不同小队数量下，军队的最大力量。核心思路是通过数学公式计算每种小队数量下的力量值，并利用差分数组优化计算过程。难点在于如何高效计算每种小队数量下的力量值，并处理不同种族生物数量的差异。

### 高星题解推荐

1. **作者：FFTotoro (赞：8)**  
   - **星级：5星**  
   - **关键亮点**：使用组合数学和差分数组优化计算，时间复杂度为 $O(\sum c_i)$，代码简洁高效。  
   - **核心代码**：
     ```cpp
     auto upd=[&](int l,int r,int x){
       d[l]+=x; if(r<m)d[r+1]-=x;
     };
     for(int i=0;i<n;i++){
       vector<int> s(c[i]+1);
       for(int j=1;j<=c[i];j++){
         int y=c[i]/j,x1=c[i]%j,x2=j-x1;
         s[j]=(y+1)*(y+1)*b*C2(x1)+y*y*b*C2(x2)+y*(y+1)*b*x1*x2;
         upd(j,j,s[j]);
       }
       if(c[i]+1<=m)upd(c[i]+1,m,s[c[i]]);
     }
     ```
   - **个人心得**：通过差分数组优化了暴力维护的过程，避免了超时问题。

2. **作者：int_R (赞：3)**  
   - **星级：4星**  
   - **关键亮点**：通过数学公式计算每种小队数量下的贡献，利用差分数组优化计算，代码清晰。  
   - **核心代码**：
     ```cpp
     inline int F(int x,int y){
       int p=x/y,q=x%y;
       return x*(x+1)/2-(y-q)*p*(p+1)/2-q*(p+1)*(p+2)/2;
     }
     inline void work(){
       cin>>n>>b>>z;
       for(int i=1;i<=n;++i){
         cin>>c[i];MAX=max(MAX,c[i]);
         for(int j=1;j<c[i];++j){
           int cur=F(c[i],j)*b;
           f[j]+=cur,f[j+1]-=cur;
         }
         f[c[i]]+=F(c[i],c[i])*b;
       }
     }
     ```
   - **个人心得**：通过差分数组优化了单点加与后缀加的过程，提高了计算效率。

3. **作者：Drimpossible (赞：2)**  
   - **星级：4星**  
   - **关键亮点**：通过贪心策略和调和级数优化，时间复杂度为 $O(V \ln V)$，代码简洁。  
   - **核心代码**：
     ```cpp
     int C(int x){return x*(x-1)/2;}
     void solution(){
       cin>>n>>a>>b;
       for(int i=1;i<=n;i++)cin>>c[i];
       sort(c+1,c+n+1);
       int ans=0,sum=0,pos=1;
       for(int i=1;i<=c[n];i++){
         while(pos<=n&&c[pos]<=i)
           sum+=C(c[pos]),pos++;
         int res=sum;
         for(int j=pos;j<=n;j++)
           res+=C(c[j])-C(c[j]/i)*i-(c[j]/i)*(c[j]%i);
         ans=max(ans,res*a-(i-1)*b);
       }
       cout<<ans<<endl;
     }
     ```
   - **个人心得**：通过调和级数优化了枚举过程，避免了超时问题。

### 最优关键思路与技巧
- **差分数组优化**：通过差分数组优化了暴力维护的过程，避免了超时问题。
- **数学公式计算**：通过数学公式计算每种小队数量下的贡献，提高了计算效率。
- **调和级数优化**：通过调和级数优化了枚举过程，减少了时间复杂度。

### 可拓展之处
- 类似的问题可以通过差分数组、数学公式和调和级数优化来提高计算效率。
- 可以进一步研究如何利用组合数学优化其他类型的计算问题。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

---
处理用时：57.93秒