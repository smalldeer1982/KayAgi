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

