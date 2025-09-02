---
title: "CITY2 - A Famous City"
layout: "post"
diff: 提高+/省选-
pid: SP11578
tag: []
---

# CITY2 - A Famous City

## 题目描述

After Mr. B arrived in Warsaw, he was shocked by the skyscrapers and took several photos. But now when he looks at these photos, he finds in surprise that he isn't even able to point out the number of buildings in it. So he decides to work it out as follows:

\- divide the photo into n vertical pieces from left to right. The buildings in the photo can be treated as rectangles, the lower edge of which is the horizon. One building may span several consecutive pieces, but each piece can only contain one visible building, or no buildings at all.

\- measure the height of each building in that piece.

\- write a program to calculate the minimum number of buildings.

Mr. B has finished the first two steps, the remaining comes to you.

## 输入格式

Each test case starts with a line containing an integer **n** (1 <= **n** <= 100,000). Following this is a line containing **n** integers - the height of building in each piece respectively. Note that zero height means there are no buildings in this piece at all. All the input numbers will be nonnegative and less than 1,000,000,000.

## 输出格式

For each test case, display a single line containing the case number and the minimum possible number of buildings in the photo.

## 样例 #1

### 输入

```
3
1 2 3
3
1 2 1
```

### 输出

```
Case 1: 3
Case 2: 2
```

