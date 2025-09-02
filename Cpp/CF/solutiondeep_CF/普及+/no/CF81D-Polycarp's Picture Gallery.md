# 题目信息

# Polycarp's Picture Gallery

## 题目描述

Polycarp loves not only to take pictures, but also to show his photos to friends. On his personal website he has recently installed a widget that can display $ n $ photos with the scroll option. At each moment of time the widget displays exactly one photograph with the option showing the previous/next one. From the first photo, you can switch to the second one or to the $ n $ -th one, from the second photo you can switch to the third one or to the first one, etc. Thus, navigation is performed in a cycle.

Polycarp's collection consists of $ m $ photo albums, the $ i $ -th album contains $ a_{i} $ photos. Polycarp wants to choose $ n $ photos and put them on a new widget. To make watching the photos interesting to the visitors, he is going to post pictures so that no two photos from one album were neighboring (each photo will have exactly two neighbors, the first photo's neighbors are the second and the $ n $ -th one).

Help Polycarp compile a photo gallery. Select $ n $ photos from his collection and put them in such order that no two photos from one album went one after the other.

## 样例 #1

### 输入

```
4 3
1 3 5
```

### 输出

```
3 1 3 2
```

## 样例 #2

### 输入

```
10 2
5 5
```

### 输出

```
2 1 2 1 2 1 2 1 2 1
```

## 样例 #3

### 输入

```
10 3
1 10 3
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# Polycarp的图片画廊

## 题目描述
Polycarp不仅喜欢拍照，还喜欢向朋友们展示他的照片。最近，他在个人网站上安装了一个小部件，该小部件可以通过滚动选项展示 $n$ 张照片。在任何时刻，该小部件都恰好显示一张照片，并且有显示上一张/下一张照片的选项。从第一张照片，你可以切换到第二张照片或者第 $n$ 张照片，从第二张照片，你可以切换到第三张照片或者第一张照片，以此类推。因此，导航是以循环方式进行的。

Polycarp的收藏由 $m$ 个相册组成，第 $i$ 个相册包含 $a_{i}$ 张照片。Polycarp想从收藏中选择 $n$ 张照片并放到新的小部件上。为了让访客观看照片时觉得有趣，他打算排列这些照片，使得来自同一相册的两张照片不会相邻（每张照片恰好有两个邻居，第一张照片的邻居是第二张和第 $n$ 张照片）。

请帮助Polycarp制作一个图片画廊。从他的收藏中选择 $n$ 张照片，并以这样的顺序排列，使得来自同一相册的两张照片不会相继出现。

## 样例 #1
### 输入
```
4 3
1 3 5
```
### 输出
```
3 1 3 2
```

## 样例 #2
### 输入
```
10 2
5 5
```
### 输出
```
2 1 2 1 2 1 2 1 2 1
```

## 样例 #3
### 输入
```
10 3
1 10 3
```
### 输出
```
-1
```

### 算法分类
构造

### 综合分析与结论
题目要求从多个相册中选取 $n$ 张照片，使得相邻照片不属于同一相册。核心在于判断是否能够构造出满足条件的照片序列，若能则输出该序列，不能则输出 -1 。由于暂无题解，以下给出通用建议与扩展思路。解决该问题，首先需要分析相册照片数量与所需照片总数 $n$ 的关系。若存在某一相册照片数超过总数的一半，显然无法满足相邻照片不同相册的条件。可以尝试先从照片数量最多的相册开始选取，穿插着从其他相册选取照片，逐步构造满足条件的序列。若在构造过程中发现无法继续满足条件，则说明不存在这样的序列。

### 扩展思路
对于这类构造性问题，关键在于找到合理的构造规则。通常需要对数据进行分析，找出限制条件和可行的构造方向。同类型题可能会改变数据的限制，比如相册数量、每个相册照片数量的范围等，或者改变相邻条件，如要求每 $k$ 张照片内不能有来自同一相册的。类似算法套路是先分析极端情况（如某相册照片数过多的情况），然后基于合理规则进行逐步构造。

### 洛谷相似题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合来解决问题，与本题构造序列有一定相似性，需考虑组合的限制条件。
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：经典的构造问题，通过搜索来构造满足条件的皇后摆放位置，与本题构造满足特定条件序列思路类似。
- [P1077 摆花](https://www.luogu.com.cn/problem/P1077)：需要根据不同花盆数量和花的种类数量构造满足条件的摆花方案，同样涉及到对条件的分析和方案的构造。 

---
处理用时：26.53秒