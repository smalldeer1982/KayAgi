# 题目信息

# Photographer

## 题目描述

Valera's lifelong ambition was to be a photographer, so he bought a new camera. Every day he got more and more clients asking for photos, and one day Valera needed a program that would determine the maximum number of people he can serve.

The camera's memory is $ d $ megabytes. Valera's camera can take photos of high and low quality. One low quality photo takes $ a $ megabytes of memory, one high quality photo take $ b $ megabytes of memory. For unknown reasons, each client asks him to make several low quality photos and several high quality photos. More formally, the $ i $ -th client asks to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos.

Valera wants to serve as many clients per day as possible, provided that they will be pleased with his work. To please the $ i $ -th client, Valera needs to give him everything he wants, that is, to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos. To make one low quality photo, the camera must have at least $ a $ megabytes of free memory space. Similarly, to make one high quality photo, the camera must have at least $ b $ megabytes of free memory space. Initially the camera's memory is empty. Valera also does not delete photos from the camera so that the camera's memory gradually fills up.

Calculate the maximum number of clients Valera can successfully serve and print the numbers of these clients.

## 样例 #1

### 输入

```
3 10
2 3
1 4
2 1
1 0
```

### 输出

```
2
3 2 ```

## 样例 #2

### 输入

```
3 6
6 6
1 1
1 0
1 0
```

### 输出

```
1
2 ```

# AI分析结果

### 题目翻译
# 摄影师

## 题目描述
瓦莱拉一生的抱负就是成为一名摄影师，所以他买了一台新相机。每天找他拍照的客户越来越多，有一天，瓦莱拉需要一个程序来确定他最多能为多少人服务。

相机的内存为 $d$ 兆字节。瓦莱拉的相机可以拍摄高质量和低质量的照片。一张低质量照片占用 $a$ 兆字节的内存，一张高质量照片占用 $b$ 兆字节的内存。出于未知原因，每个客户都要求他拍摄若干张低质量照片和若干张高质量照片。更正式地说，第 $i$ 个客户要求拍摄 $x_{i}$ 张低质量照片和 $y_{i}$ 张高质量照片。

瓦莱拉希望每天尽可能多地服务客户，前提是他们对他的工作满意。为了让第 $i$ 个客户满意，瓦莱拉需要满足他的所有要求，即拍摄 $x_{i}$ 张低质量照片和 $y_{i}$ 张高质量照片。要拍摄一张低质量照片，相机至少需要有 $a$ 兆字节的可用内存空间。同样，要拍摄一张高质量照片，相机至少需要有 $b$ 兆字节的可用内存空间。最初，相机的内存是空的。瓦莱拉也不会从相机中删除照片，因此相机的内存会逐渐被填满。

计算瓦莱拉最多能成功服务的客户数量，并打印出这些客户的编号。

## 样例 #1
### 输入
```
3 10
2 3
1 4
2 1
1 0
```
### 输出
```
2
3 2
```

## 样例 #2
### 输入
```
3 6
6 6
1 1
1 0
1 0
```
### 输出
```
1
2
```

### 综合分析与结论
- **思路**：所有题解均采用贪心算法，核心思路是先计算每个客户所需的内存，将客户按所需内存从小到大排序，然后依次尝试满足客户需求，直到内存不足为止。
- **算法要点**：
    - 定义结构体存储客户信息，包括低、高质量照片数量、客户编号和所需内存。
    - 输入时计算每个客户所需内存。
    - 使用 `sort` 函数对客户按所需内存排序。
    - 遍历排序后的客户，依次判断能否满足需求。
- **解决难点**：本题难点在于想到使用贪心策略，通过优先满足所需内存少的客户来最大化服务的客户数量。同时，需要注意记录客户编号以便最后输出。

### 所选题解
- **作者：Szr__QAQ（5星）**
    - **关键亮点**：思路清晰，代码注释详细，易于理解。
    - **核心代码**：
```cpp
struct szr{
    int x,y,id,sum;
}photo[qwq];
bool cmp(szr a,szr b){
    return a.sum<b.sum;
}
//...
sort(photo+1,photo+n+1,cmp);
for(int i=1;i<=n;i++){
    if(photo[i].sum<=d)
    {
        d-=photo[i].sum;
        cnt++;
    }
    else
    {
        break;
    }
}
```
核心实现思想：定义结构体存储客户信息，编写比较函数按所需内存从小到大排序，遍历排序后的客户，若内存足够则满足该客户需求并更新内存和满足客户数量。

- **作者：yzm0325（4星）**
    - **关键亮点**：代码简洁，逻辑清晰。
    - **核心代码**：
```cpp
struct client {
    int s, id;
} yh[100010];
bool cmp(client a, client b) {
    return a.s < b.s;
}
//...
sort(yh + 1, yh + n + 1, cmp);
for(int i = 1; i <= n; i++) {
    d -= yh[i].s;
    if(d < 0) break;
    ans++;
}
```
核心实现思想：定义结构体存储客户信息，编写比较函数排序，遍历客户，若内存足够则满足该客户需求并更新内存和满足客户数量。

- **作者：CleverRaccoon（4星）**
    - **关键亮点**：使用了 C++ 新特性和 `lambda` 函数，代码简洁且具有一定的创新性。
    - **核心代码**：
```cpp
struct node {
    int use, id;
} a[N];
sort(a + 1, a + n + 1, [](node a, node b) {
    return a.use < b.use;
});
for(int i = 1; i <= n; ++i) {
    if((d -= a[i].use) <= 0)
        break;
    ans.push_back(a[i].id);
}
```
核心实现思想：定义结构体存储客户信息，使用 `lambda` 函数按所需内存从小到大排序，遍历客户，若内存足够则满足该客户需求并记录客户编号。

### 最优关键思路或技巧
- 使用结构体存储客户信息，方便排序和记录客户编号。
- 采用贪心算法，优先满足所需内存少的客户。
- 部分题解使用 `lambda` 函数简化排序比较函数的编写。

### 拓展思路
同类型题通常涉及资源分配问题，如背包问题的变种、任务调度问题等，都可以考虑使用贪心算法解决。解题关键在于找到合适的贪心策略，如按某种属性排序后依次处理。

### 推荐题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得摘录与总结
- **yzm0325**：因 RMJ 炸了导致代码一开始错误，后已改正。总结：在提交代码前应确保测试环境稳定，避免因外部因素导致代码错误。
- **liupan2010**：RMJ 暂时炸了使最初代码错误，现已改正。总结：要注意测试环境的稳定性，代码出现问题时需排查是否受外部因素影响。 

---
处理用时：37.99秒