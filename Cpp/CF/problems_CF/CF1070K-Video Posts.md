---
title: "Video Posts"
layout: "post"
diff: 普及-
pid: CF1070K
tag: []
---

# Video Posts

## 题目描述

Polycarp took $ n $ videos, the duration of the $ i $ -th video is $ a_i $ seconds. The videos are listed in the chronological order, i.e. the $ 1 $ -st video is the earliest, the $ 2 $ -nd video is the next, ..., the $ n $ -th video is the last.

Now Polycarp wants to publish exactly $ k $ ( $ 1 \le k \le n $ ) posts in Instabram. Each video should be a part of a single post. The posts should preserve the chronological order, it means that the first post should contain one or more of the earliest videos, the second post should contain a block (one or more videos) going next and so on. In other words, if the number of videos in the $ j $ -th post is $ s_j $ then:

- $ s_1+s_2+\dots+s_k=n $ ( $ s_i>0 $ ),
- the first post contains the videos: $ 1, 2, \dots, s_1 $ ;
- the second post contains the videos: $ s_1+1, s_1+2, \dots, s_1+s_2 $ ;
- the third post contains the videos: $ s_1+s_2+1, s_1+s_2+2, \dots, s_1+s_2+s_3 $ ;
- ...
- the $ k $ -th post contains videos: $ n-s_k+1,n-s_k+2,\dots,n $ .

Polycarp is a perfectionist, he wants the total duration of videos in each post to be the same.

Help Polycarp to find such positive integer values $ s_1, s_2, \dots, s_k $ that satisfy all the conditions above.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 10^5 $ ). The next line contains $ n $ positive integer numbers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^4 $ ), where $ a_i $ is the duration of the $ i $ -th video.

## 输出格式

If solution exists, print "Yes" in the first line. Print $ k $ positive integers $ s_1, s_2, \dots, s_k $ ( $ s_1+s_2+\dots+s_k=n $ ) in the second line. The total duration of videos in each post should be the same. It can be easily proven that the answer is unique (if it exists).

If there is no solution, print a single line "No".

## 样例 #1

### 输入

```
6 3
3 3 1 4 1 6

```

### 输出

```
Yes
2 3 1 
```

## 样例 #2

### 输入

```
3 3
1 1 1

```

### 输出

```
Yes
1 1 1 
```

## 样例 #3

### 输入

```
3 3
1 1 2

```

### 输出

```
No
```

## 样例 #4

### 输入

```
3 1
1 10 100

```

### 输出

```
Yes
3 
```

