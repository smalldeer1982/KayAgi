# 题目信息

# Number of Triplets

## 题目描述

You are given $ n $ points on a plane. All points are different.

Find the number of different groups of three points $ (A,B,C) $ such that point $ B $ is the middle of segment $ AC $ .

The groups of three points are considered unordered, that is, if point $ B $ is the middle of segment $ AC $ , then groups $ (A,B,C) $ and $ (C,B,A) $ are considered the same.

## 样例 #1

### 输入

```
3
1 1
2 2
3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
0 0
-1 0
0 1
```

### 输出

```
0
```

# AI分析结果



# 题目中文重写  
（题目已为中文，无需翻译）

## 算法分类  
枚举

---

## 题解分析与结论  
需找出所有满足中点关系的三元组，核心思路为枚举点对计算中点，利用数据结构快速判断中点存在性。关键优化点包括：坐标和奇偶性检验、避免重复枚举、选择高效存储方式。

---

## 高分题解推荐  
### 1. 作者：zh1221_qwq（★★★★★）  
**亮点**：  
- 利用坐标值域小的特点，用二维数组直接存储点存在性  
- 时间复杂度优化至纯O(n²)，无哈希查询消耗  
- 正确处理奇偶性检验与坐标偏移  

**核心代码**：  
```cpp
int b[2005][2005], x[3005], y[3005];
// 预处理坐标偏移
for(int i=1;i<=n;i++) 
    b[x[i]+1000][y[i]+1000] = 1;
// 枚举点对并检查中点
for(int i=1;i<=n;i++) 
    for(int j=i+1;j<=n;j++) 
        if((x[i]+x[j])%2==0 && (y[i]+y[j])%2==0 
          && b[(x[i]+x[j])/2+1000][(y[i]+y[j])/2+1000])
            ans++;
```

### 2. 作者：TheSky233（★★★★☆）  
**亮点**：  
- 使用`std::set`实现通用解法，适用于大坐标范围  
- 代码结构清晰，完整处理中点合法性检验  
- 通过枚举i<j避免重复计数  

**核心代码**：  
```cpp
std::set<std::pair<int, int>> st;
// 枚举点对并验证中点
for(int i=1;i<=n;i++) 
    for(int j=i+1;j<=n;j++) 
        if(!( (a.first+b.first)&1 || (a.second+b.second)&1 ))
            if(st.count(midPoint(a,b))) 
                ans++;
```

### 3. 作者：wang_freedom（★★★★☆）  
**亮点**：  
- 简洁的vector+set混合实现  
- 使用位运算快速判断奇偶性  
- 代码风格紧凑，适合竞赛快速编码  

**核心代码**：  
```cpp
set<pii> st;
vector<pii> v;
// 检查中点存在性
if((v[i].fi+v[j].fi)&1 || (v[i].se+v[j].se)&1) continue;
if(st.find({(v[i].fi+v[j].fi)/2, ... }) != st.end())
    ans++;
```

---

## 关键思路总结  
1. **中点合法性检验**：必须满足两坐标和为偶数，否则跳过  
2. **高效存储结构**：  
   - 小值域：二维数组直接映射（偏移处理负坐标）  
   - 大值域：哈希表（set/unordered_set）  
3. **枚举优化**：仅枚举i<j的点对，避免重复计算  

---

## 同类题目推荐  
1. P1102 A-B 数对（类似的双点关系枚举）  
2. P1257 平面上的最接近点对（点对枚举优化）  
3. P2280 激光炸弹（二维前缀和与坐标映射）

---
处理用时：80.38秒