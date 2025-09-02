---
title: "Flying Saucer Segments"
layout: "post"
diff: 普及/提高-
pid: CF226A
tag: []
---

# Flying Saucer Segments

## 题目描述

An expedition group flew from planet ACM-1 to Earth in order to study the bipedal species (its representatives don't even have antennas on their heads!).

The flying saucer, on which the brave pioneers set off, consists of three sections. These sections are connected by a chain: the 1-st section is adjacent only to the 2-nd one, the 2-nd one — to the 1-st and the 3-rd ones, the 3-rd one — only to the 2-nd one. The transitions are possible only between the adjacent sections.

The spacecraft team consists of $ n $ aliens. Each of them is given a rank — an integer from $ 1 $ to $ n $ . The ranks of all astronauts are distinct. The rules established on the Saucer, state that an alien may move from section $ a $ to section $ b $ only if it is senior in rank to all aliens who are in the segments $ a $ and $ b $ (besides, the segments $ a $ and $ b $ are of course required to be adjacent). Any alien requires exactly $ 1 $ minute to make a move. Besides, safety regulations require that no more than one alien moved at the same minute along the ship.

Alien $ A $ is senior in rank to alien $ B $ , if the number indicating rank $ A $ , is more than the corresponding number for $ B $ .

At the moment the whole saucer team is in the 3-rd segment. They all need to move to the 1-st segment. One member of the crew, the alien with the identification number CFR-140, decided to calculate the minimum time (in minutes) they will need to perform this task.

Help CFR-140, figure out the minimum time (in minutes) that all the astronauts will need to move from the 3-rd segment to the 1-st one. Since this number can be rather large, count it modulo $ m $ .

## 输入格式

The first line contains two space-separated integers: $ n $ and $ m $ $ (1<=n,m<=10^{9}) $ — the number of aliens on the saucer and the number, modulo which you should print the answer, correspondingly.

## 输出格式

Print a single number — the answer to the problem modulo $ m $ .

## 说明/提示

In the first sample the only crew member moves from segment 3 to segment 2, and then from segment 2 to segment 1 without any problems. Thus, the whole moving will take two minutes.

To briefly describe the movements in the second sample we will use value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/45444f2fa560c0037b27d01242b8d4bbde1358aa.png), which would correspond to an alien with rank $ i $ moving from the segment in which it is at the moment, to the segment number $ j $ . Using these values, we will describe the movements between the segments in the second sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/555702f9a61a62f33a391773ccade066ae7cb236.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/32a8caec69f00b67073f877bf4e1c3dbf2cc908d.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/ba5c75ab2dad5cb62463c51a0022dba3fcb2b02b.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/6d7099024bb756bbfa4f326bc16f9c9c0f8e6d88.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/555702f9a61a62f33a391773ccade066ae7cb236.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png); In total: the aliens need 26 moves. The remainder after dividing $ 26 $ by $ 8 $ equals $ 2 $ , so the answer to this test is $ 2 $ .

## 样例 #1

### 输入

```
1 10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 8

```

### 输出

```
2

```

