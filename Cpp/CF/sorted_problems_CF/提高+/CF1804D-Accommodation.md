---
title: "Accommodation"
layout: "post"
diff: 提高+/省选-
pid: CF1804D
tag: []
---

# Accommodation

## 题目描述

Annie is an amateur photographer. She likes to take pictures of giant residential buildings at night. She just took a picture of a huge rectangular building that can be seen as a table of $ n \times m $ windows. That means that the building has $ n $ floors and each floor has exactly $ m $ windows. Each window is either dark or bright, meaning there is light turned on in the room behind it.

Annies knows that each apartment in this building is either one-bedroom or two-bedroom. Each one-bedroom apartment has exactly one window representing it on the picture, and each two-bedroom apartment has exactly two consecutive windows on the same floor. Moreover, the value of $ m $ is guaranteed to be divisible by $ 4 $ and it is known that each floor has exactly $ \frac{m}{4} $ two-bedroom apartments and exactly $ \frac{m}{2} $ one-bedroom apartments. The actual layout of apartments is unknown and can be different for each floor.

Annie considers an apartment to be occupied if at least one of its windows is bright. She now wonders, what are the minimum and maximum possible number of occupied apartments if judged by the given picture?

Formally, for each of the floors, she comes up with some particular apartments layout with exactly $ \frac{m}{4} $ two-bedroom apartments (two consecutive windows) and $ \frac{m}{2} $ one-bedroom apartments (single window). She then counts the total number of apartments that have at least one bright window. What is the minimum and maximum possible number she can get?

## 输入格式

The first line of the input contains two positive integers $ n $ and $ m $ ( $ 1 \leq n \cdot m \leq 5 \cdot 10^5 $ ) — the number of floors in the building and the number of windows per floor, respectively. It is guaranteed that $ m $ is divisible by $ 4 $ .

Then follow $ n $ lines containing $ m $ characters each. The $ j $ -th character of the $ i $ -th line is "0" if the $ j $ -th window on the $ i $ -th floor is dark, and is "1" if this window is bright.

## 输出格式

Print two integers, the minimum possible number of occupied apartments and the maximum possible number of occupied apartments, assuming each floor can have an individual layout of $ \frac{m}{4} $ two-bedroom and $ \frac{m}{2} $ one-bedroom apartments.

## 说明/提示

In the first example, each floor consists of one two-bedroom apartment and two one-bedroom apartments.

The following apartment layout achieves the minimum possible number of occupied apartments equal to $ 7 $ .

```
<pre class="verbatim"><br></br>|0 1|0|0|<br></br>|1 1|0|0|<br></br>|0|1 1|0|<br></br>|1|0 1|0|<br></br>|1|0|1 1|<br></br>
```

The following apartment layout achieves the maximum possible number of occupied apartments equal to $ 10 $ .

```
<pre class="verbatim"><br></br>|0 1|0|0|<br></br>|1|1 0|0|<br></br>|0 1|1|0|<br></br>|1|0 1|0|<br></br>|1 0|1|1|<br></br>
```

## 样例 #1

### 输入

```
5 4
0100
1100
0110
1010
1011
```

### 输出

```
7 10
```

## 样例 #2

### 输入

```
1 8
01011100
```

### 输出

```
3 4
```

