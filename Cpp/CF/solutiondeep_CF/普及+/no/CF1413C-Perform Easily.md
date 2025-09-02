# 题目信息

# Perform Easily

## 题目描述

After battling Shikamaru, Tayuya decided that her flute is too predictable, and replaced it with a guitar. The guitar has $ 6 $ strings and an infinite number of frets numbered from $ 1 $ . Fretting the fret number $ j $ on the $ i $ -th string produces the note $ a_{i} + j $ .

Tayuya wants to play a melody of $ n $ notes. Each note can be played on different string-fret combination. The easiness of performance depends on the difference between the maximal and the minimal indices of used frets. The less this difference is, the easier it is to perform the technique. Please determine the minimal possible difference.

For example, if $ a = [1, 1, 2, 2, 3, 3] $ , and the sequence of notes is $ 4, 11, 11, 12, 12, 13, 13 $ (corresponding to the second example), we can play the first note on the first string, and all the other notes on the sixth string. Then the maximal fret will be $ 10 $ , the minimal one will be $ 3 $ , and the answer is $ 10 - 3 = 7 $ , as shown on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/75869e5e3f35cb76d96c1bbe62cb5730522c5a69.png)

## 说明/提示

In the first sample test it is optimal to play the first note on the first string, the second note on the second string, the third note on the sixth string, the fourth note on the fourth string, the fifth note on the fifth string, and the sixth note on the third string. In this case the $ 100 $ -th fret is used each time, so the difference is $ 100 - 100 = 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/4a9f5f121daaf96225841a762483d6d36c81ea82.png)In the second test it's optimal, for example, to play the second note on the first string, and all the other notes on the sixth string. Then the maximal fret will be $ 10 $ , the minimal one will be $ 3 $ , and the answer is $ 10 - 3 = 7 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/d3f532a5b4af047547fabc1dd582c7d88c33efa7.png)

## 样例 #1

### 输入

```
1 4 100 10 30 5
6
101 104 105 110 130 200```

### 输出

```
0```

## 样例 #2

### 输入

```
1 1 2 2 3 3
7
13 4 11 12 11 13 12```

### 输出

```
7```

# AI分析结果

### 题目翻译
# 轻松演奏

## 题目描述
在与鹿丸战斗后，手鞠觉得她的长笛太容易被预测了，于是用吉他代替了它。这把吉他有 6 根弦，且品柱的数量是无限的，品柱编号从 1 开始。在第 $i$ 根弦上按住第 $j$ 个品柱会产生音符 $a_{i} + j$。

手鞠想要演奏一段包含 $n$ 个音符的旋律。每个音符都可以通过不同的弦 - 品柱组合来演奏。演奏的难易程度取决于所使用品柱的最大编号和最小编号之间的差值。这个差值越小，演奏技巧就越容易。请确定这个最小可能的差值。

例如，如果 $a = [1, 1, 2, 2, 3, 3]$，并且音符序列是 $4, 11, 11, 12, 12, 13, 13$（对应第二个样例），我们可以在第一根弦上演奏第一个音符，而在第六根弦上演奏所有其他音符。那么最大的品柱编号将是 10，最小的是 3，答案就是 $10 - 3 = 7$，如图所示。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/75869e5e3f35cb76d96c1bbe62cb5730522c5a69.png)

## 说明/提示
在第一个样例测试中，最优的做法是在第一根弦上演奏第一个音符，在第二根弦上演奏第二个音符，在第六根弦上演奏第三个音符，在第四根弦上演奏第四个音符，在第五根弦上演奏第五个音符，在第三根弦上演奏第六个音符。在这种情况下，每次都使用第 100 个品柱，所以差值是 $100 - 100 = 0$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/4a9f5f121daaf96225841a762483d6d36c81ea82.png)
在第二个测试中，例如，最优的做法是在第一根弦上演奏第二个音符，而在第六根弦上演奏所有其他音符。那么最大的品柱编号将是 10，最小的是 3，答案就是 $10 - 3 = 7$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1413C/d3f532a5b4af047547fabc1dd582c7d88c33efa7.png)

## 样例 #1
### 输入
```
1 4 100 10 30 5
6
101 104 105 110 130 200
```
### 输出
```
0
```

## 样例 #2
### 输入
```
1 1 2 2 3 3
7
13 4 11 12 11 13 12
```
### 输出
```
7
```

### 算法分类
排序

### 综合分析与结论
这些题解主要围绕如何找到满足条件的最小差值展开，核心在于对所有可能的差值进行处理和筛选。大部分题解的思路是先计算出所有 $b - a$ 的差值，将其排序后，再通过不同的方法（如双指针、堆、线段树等）来找到包含所有音符且差值最小的区间。

### 高评分题解
- **Time_tears（4星）**
    - **关键亮点**：思路清晰，通过枚举最大值，利用线段树快速维护，代码实现简洁明了。
    - **核心代码**：
```cpp
// 线段树构建
void Build(int p,int l,int r) {
    if(l==r)return minn[p]=-0x3f3f3f3f,void();
    int mid=l+r>>1;
    minn[p]=-0x3f3f3f3f,Build(p<<1,l,mid),Build(p<<1|1,mid+1,r);
}
// 线段树单点修改
void Change(int p,int l,int r,int x,int y) {
    if(l==r)return minn[p]=y,void();
    int mid=l+r>>1;
    if(x<=mid)Change(p<<1,l,mid,x,y);
    else Change(p<<1|1,mid+1,r,x,y);
    minn[p]=min(minn[p<<1],minn[p<<1|1]);
}
// 主函数部分
for(int i=0; i<6; ++i)a[i]=read();
n=read();
for(int i=1,x; i<=n; ++i) {
    x=read();
    for(int j=0; j<6; ++j)b[++cnt].x=x-a[j],b[cnt].id=i;
}
sort(b+1,b+6*n+1),Build(1,1,n);
int ans=0x3f3f3f3f;
for(int i=1; i<=6*n; ++i)Change(1,1,n,b[i].id,b[i].x),ans=min(ans,b[i].x-minn[1]);
printf("%d",ans);
```
    - **核心思想**：先计算所有可能的差值并排序，然后用线段树维护每个音符对应的最大差值，通过枚举最大值更新答案。
- **QianianXY（4星）**
    - **关键亮点**：提出了复杂度为 $O(n)$ 的双指针贪心做法，思路简单易懂，代码实现规范。
    - **核心代码**：
```cpp
// 双指针部分
while (q < tot)
{
    if (!cnt[a[++q].id]) cntn++;
    ++cnt[a[q].id];
    while (p < q && a[q].v - a[p].v >= ans)
    {
        if (cnt[a[p].id] == 1) cntn--;
        --cnt[a[p].id];
        ++p;
    }
    while (p < q && cntn == n)
    {
        ans = min(ans, a[q].v - a[p].v);
        if (cnt[a[p].id] == 1) cntn--;
        --cnt[a[p].id];
        ++p;
    } 
}
```
    - **核心思想**：将所有可能的差值排序，用双指针维护一个区间，当区间内包含所有音符时更新答案。
- **xrk2006（4星）**
    - **关键亮点**：思路清晰，对问题进行了详细的分析和转化，利用双指针优化了枚举过程，复杂度为 $O(6n)$。
    - **核心代码**：
```cpp
// 双指针部分
for(int l=0;l<p.size();l++)
{
    while((r<(signed)p.size()-1)&&now<n)
    {
        r++;
        cntnow[p[r].second]++;
        if(cntnow[p[r].second]==1)now++;
    }
    if(now>=n)ans=min(ans,p[r].first-p[l].first);
    cntnow[p[l].second]--;
    if(cntnow[p[l].second]==0)now--;
}
```
    - **核心思想**：将所有可能的差值存入 `vector` 并排序，用双指针维护区间，保证区间内包含所有音符，更新最小差值。

### 最优关键思路或技巧
- **排序**：将所有可能的差值排序，为后续的查找和筛选提供了便利。
- **双指针**：利用双指针维护一个区间，通过移动指针找到满足条件的最小差值，时间复杂度较低。
- **数据结构的运用**：如线段树、堆等，可以快速维护和查找所需信息。

### 拓展思路
同类型题目通常涉及在多个选择中找到最优的区间或组合，关键在于对所有可能情况进行合理的排序和筛选。类似的算法套路包括双指针、贪心、二分等。

### 推荐题目
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)
- [P2085 最小函数值](https://www.luogu.com.cn/problem/P2085)

### 个人心得摘录与总结
- **Spasmodic**：考试时只想到了二分的做法，错失 Expert，说明在考试中要多思考，尝试不同的解法。
- **Zesty_Fox**：考场被该题卡了 1 个小时，提示我们在遇到难题时要冷静分析，找到问题的关键所在。
- **gyh20**：被卡了好久，最后莫名其妙想到了做法，告诉我们在解题过程中要保持耐心，不断尝试新的思路。

---
处理用时：60.68秒