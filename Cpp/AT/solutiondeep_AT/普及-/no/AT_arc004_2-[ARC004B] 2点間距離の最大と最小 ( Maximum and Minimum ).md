# 题目信息

# [ARC004B] 2点間距離の最大と最小 ( Maximum and Minimum )

## 题目描述

间距最大值和最小值。( Maximum and Minimum )

平面上有n + 1个点，分别从0到n编号.
虽然不知道各点位置，但对于0以上且小于n的整数i，第i点和第i+1点的距离为d_i。
请求出从第0个点和第n个点的距离能够取到的值的最大值和最小值。

# AI分析结果

### 题目内容重写
平面上有n + 1个点，分别从0到n编号。虽然不知道各点位置，但对于0以上且小于n的整数i，第i点和第i+1点的距离为d_i。请求出从第0个点和第n个点的距离能够取到的值的最大值和最小值。

### 算法分类
数学

### 题解分析与结论
所有题解的核心思路一致：最大距离是所有相邻点距离之和，最小距离则取决于最长距离与其他距离之和的关系。如果最长距离小于等于其他距离之和，最小距离为0；否则，最小距离为最长距离减去其他距离之和。

### 所选高星题解
#### 题解1：Doveqise (4星)
- **关键亮点**：通过图示直观解释了最大和最小距离的计算方法，代码简洁明了。
- **代码核心**：
  ```cpp
  int n, tot=0, maxx=0;
  scanf("%d",&n);
  for (int i=1,x; i<=n; i++) {
      scanf("%d",&x);
      tot+=x; 
      maxx=max(maxx, x);
  }
  printf("%d\n",tot); 
  tot-=maxx;
  if (tot>=maxx)
      puts("0");
  else 
      printf("%d\n",maxx-tot);
  ```

#### 题解2：インデックス (3星)
- **关键亮点**：代码优化了输入输出，使用了O2优化，但思路与题解1相同。
- **代码核心**：
  ```cpp
  int n=read(), sum=0, mx=0;
  for (int i=1; i<=n; i++) {
      int x=read();
      sum+=x; mx=max(mx, x);
  }
  printf("%d\n",sum); sum-=mx;
  if (sum>=mx) printf("0\n");
  else printf("%d\n",mx-sum);
  ```

#### 题解3：qwq___qaq (2星)
- **关键亮点**：强调了最小距离的计算逻辑，代码简洁。
- **代码核心**：
  ```cpp
  int n,sum,maxn,a;
  scanf("%d%d",&n,&maxn);
  sum=maxn;
  for(int i=2;i<=n;i++){
      scanf("%d",&a);
      sum+=a;
      maxn=max(maxn,a);
  }
  printf("%d\n",sum);
  sum-=maxn;
  printf("%d\n",max(maxn-sum,0));
  ```

### 最优关键思路
最大距离是所有相邻点距离之和，最小距离取决于最长距离与其他距离之和的关系。如果最长距离小于等于其他距离之和，最小距离为0；否则，最小距离为最长距离减去其他距离之和。

### 拓展思路
类似的问题可以出现在几何或图论中，考察点之间的距离关系。可以通过调整点的位置来满足不同的距离条件。

### 推荐题目
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：18.22秒