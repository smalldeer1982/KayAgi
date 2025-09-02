---
title: "邮件传输代理的交互 The Letter Carrier's Rounds"
layout: "post"
diff: 普及/提高-
pid: UVA814
tag: []
---

# 邮件传输代理的交互 The Letter Carrier's Rounds

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=755

[PDF](https://uva.onlinejudge.org/external/8/p814.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA814/ce9250ad50e7737c43213a539668fb6c23f3d0ea.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA814/f5728826144f1356571357078ceb40d6d77cbd02.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA814/ccad3c3a3b664c8a1cb83b9a2ac50915f4da21fa.png)

## 样例 #1

### 输入

```
MTA London 4 Fiona Paul Heather Nevil
MTA SanFrancisco 3 Mario Luigi Shariff
MTA Paris 3 Jacque Suzanne Maurice
MTA HongKong 3 Chen Jeng Hee
MTA MexicoCity 4 Conrado Estella Eva Raul
MTA Cairo 3 Hamdy Tarik Misa
*
Hamdy@Cairo Conrado@MexicoCity Shariff@SanFrancisco Lisa@MexicoCity
*
Congratulations on your efforts !!
--Hamdy
*
Fiona@London Chen@HongKong Natasha@Paris
*
Thanks for the report! --Fiona
*
*
```

### 输出

```

Connection between Cairo and MexicoCity
     HELO Cairo
     250
     MAIL FROM:<Hamdy@Cairo>
     250
     RCPT TO:<Conrado@MexicoCity>
     250
     RCPT TO:<Lisa@MexicoCity>
     550
     DATA
     354
     Congratulations on your efforts !!
     --Hamdy
     .
     250
     QUIT
     221
Connection between Cairo and SanFrancisco
     HELO Cairo
     250
     MAIL FROM:<Hamdy@Cairo>
     250
     RCPT TO:<Shariff@SanFrancisco>
     250
     DATA
     354
     Congratulations on your efforts !!
     --Hamdy
     .
     250
     QUIT
     221
Connection between London and HongKong
     HELO London
     250
     MAIL FROM:<Fiona@London>
     250
     RCPT TO:<Chen@HongKong>
     250
     DATA
     354
     Thanks for the report! --Fiona
     .
     250
     QUIT
     221
Connection between London and Paris
     HELO London
     250
     MAIL FROM:<Fiona@London>
     250
     RCPT TO:<Natasha@Paris>
     550
     QUIT
     221
```

