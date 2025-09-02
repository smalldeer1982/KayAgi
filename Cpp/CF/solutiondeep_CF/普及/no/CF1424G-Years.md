# 题目信息

# Years

## 题目描述

During one of the space missions, humans have found an evidence of previous life at one of the planets. They were lucky enough to find a book with birth and death years of each individual that had been living at this planet. What's interesting is that these years are in the range $ (1, 10^9) $ ! Therefore, the planet was named Longlifer.

In order to learn more about Longlifer's previous population, scientists need to determine the year with maximum number of individuals that were alive, as well as the number of alive individuals in that year. Your task is to help scientists solve this problem!

## 说明/提示

You can assume that an individual living from $ b $ to $ d $ has been born at the beginning of $ b $ and died at the beginning of $ d $ , and therefore living for $ d $ - $ b $ years.

## 样例 #1

### 输入

```
3
1 5
2 4
5 6```

### 输出

```
2 2```

## 样例 #2

### 输入

```
4
3 4
4 5
4 6
8 10```

### 输出

```
4 2```

# AI分析结果

### 题目内容重写
#### 题目描述
在一次太空任务中，人类在某颗行星上发现了先前生命的证据。他们幸运地找到了一本书，书中记录了每个个体的出生和死亡年份。有趣的是，这些年份的范围是 $(1, 10^9)$！因此，这颗行星被命名为Longlifer。

为了了解更多关于Longlifer先前人口的信息，科学家们需要确定哪一年活着的人数最多，以及该年活着的人数。你的任务是帮助科学家们解决这个问题！

#### 说明/提示
你可以假设一个个体从 $b$ 年活到 $d$ 年，意味着他在 $b$ 年初出生，在 $d$ 年初死亡，因此他活了 $d - b$ 年。

#### 样例 #1
##### 输入
```
3
1 5
2 4
5 6
```
##### 输出
```
2 2
```

#### 样例 #2
##### 输入
```
4
3 4
4 5
4 6
8 10
```
##### 输出
```
4 2
```

### 算法分类
差分

### 题解分析与结论
本题的核心是找到哪一年活着的人数最多，并且输出该年的人数。由于年份的范围非常大（$1$ 到 $10^9$），直接使用数组进行差分会导致内存不足。因此，大多数题解都采用了 `map` 数据结构来处理差分，避免了内存问题。

#### 关键思路
1. **差分思想**：对于每个个体的出生年份 $b$，在 `map` 中增加 $1$，对于死亡年份 $d$，减少 $1$。然后通过遍历 `map` 计算每年的净人数，并记录最大值。
2. **离散化**：部分题解采用了离散化的方法，将年份映射到较小的范围内，再进行差分处理。
3. **STL的使用**：大多数题解使用了 `map` 来存储差分结果，避免了直接使用数组导致的内存问题。

#### 评分较高的题解
1. **作者：lngqb (5星)**
   - **关键亮点**：简洁明了地使用了 `map` 进行差分处理，代码清晰易读。
   - **核心代码**：
     ```cpp
     map<int,int> c;
     for(int i=1;i<=n;i++) {
         cin>>a>>b;
         c[a]++;
         c[b]--;
     }
     int ans=0,pos,max=-1;
     for(map<int,int>::iterator it=c.begin();it!=c.end();it++) {
         ans+=it->second;
         if(ans>max) {
             max=ans;
             pos=it->first;
         }
     }
     cout<<pos<<" "<<max;
     ```

2. **作者：是个汉子 (4星)**
   - **关键亮点**：采用了离散化的方法，将年份映射到较小的范围内，再进行差分处理，适合处理更大范围的数据。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         l[i]=read();
         r[i]=read();
         a[++cnt]=l[i];
         a[++cnt]=r[i];
     }
     sort(a+1,a+cnt+1);
     for(int i=1;i<=cnt;i++)
         if(i==1||a[i]!=a[i-1]) a[++tot]=a[i];
     for(int i=1;i<=n;i++) {
         t1=lower_bound(a+1,a+tot+1,l[i])-a;
         t2=lower_bound(a+1,a+tot+1,r[i])-a;
         b[t1]++, b[t2]--;
     }
     for(int i=1;i<=tot;i++) {
         sum+=b[i];
         if(sum>ans) ans=sum,pos=c[i];
     }
     ```

3. **作者：RioFutaba (4星)**
   - **关键亮点**：同样使用了 `map` 进行差分处理，代码简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     map<int,int> cnt;
     for(int i=1;i<=n;i++) {
         int b,d;
         scanf("%d %d",&b,&d);
         cnt[b]++;
         cnt[d]--;
     }
     int sum=0,ans=0,ac=0;
     for(auto i:cnt) {
         sum+=i.second;
         if(sum>ac) {
             ans=i.first;
             ac=sum;
         }
     }
     printf("%d %d",ans,ac);
     ```

### 最优关键思路
使用 `map` 进行差分处理是最优的解决方案，因为它避免了直接使用数组导致的内存问题，同时保持了代码的简洁性和可读性。

### 拓展思路
类似的问题可以扩展到其他需要处理大范围数据的场景，例如统计某个时间段内的活跃用户数、计算某个时间段内的最大值等。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：36.94秒