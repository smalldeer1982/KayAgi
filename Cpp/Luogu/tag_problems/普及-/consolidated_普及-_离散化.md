---
title: "火烧赤壁"
layout: "post"
diff: 普及-
pid: P1496
tag: ['离散化', 'O2优化']
---
# 火烧赤壁
## 题目背景

曹操平定北方以后，公元 208 年，率领大军南下，进攻刘表。他的人马还没有到荆州，刘表已经病死。他的儿子刘琮听到曹军声势浩大，吓破了胆，先派人求降了。

孙权任命周瑜为都督，拨给他三万水军，叫他同刘备协力抵抗曹操。

隆冬的十一月，天气突然回暖，刮起了东南风。

没想到东吴船队离开北岸大约二里距离，前面十条大船突然同时起火。火借风势，风助火威。十条火船，好比十条火龙一样，闯进曹军水寨。那里的船舰，都挤在一起，又躲不开，很快地都烧起来。一眨眼工夫，已经烧成一片火海。

曹操气急败坏的把你找来，要你钻入火海把连环线上着火的船只的长度统计出来！
## 题目描述

给定每个起火部分的起点和终点，请你求出燃烧位置的长度之和。
## 输入格式

第一行一个整数，表示起火的信息条数 $n$。  
接下来 $n$ 行，每行两个整数 $a, b$，表示一个着火位置的起点和终点（**注意：左闭右开**）。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
-1 1
5 11
2 9
```
### 样例输出 #1
```
11
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 2 \times 10^4$，$-2^{31} \leq a <  b \lt 2^{31}$，且答案小于 $2^{31}$。





---

---
title: "天际线"
layout: "post"
diff: 普及-
pid: P1904
tag: ['模拟', '线段树', '离散化']
---
# 天际线
## 题目描述

Latium 省的 Genoa 是亚平宁半岛西海岸北端的一片土地，自然资源丰富，却无人居住。你受到罗马执政官 Caesar 的委任，前往 Genoa 建立新的城市。Caesar 对这次任务的要求是在 Genoa 这片土地上建立起一座繁荣的城市，他将以此作为衡量你的表现的标准。

正在你大刀阔斧地进行城市建设的时候，Caesar 突然写信给你，说他要检查 Genoa 的建设情况。Caesar 希望知道你的城市是什么样子，但是他又非常的忙，所以他只要你描述一下城市的轮廓就可以了，他将依照城市的轮廓决定你的薪水。

怎样描述一个城市的轮廓呢？我们知道 Genoa 所有的建筑共享一个地面，你可以认为它是水平的。所有的建筑用一个三元组 $(L_i,H_i,R_i)$，其中 $L_i$ 和 $R_i$ 分别是建筑的左坐标和右坐标，$H_i$ 就是建筑的高度。在下方所示的图表中左边建筑物描述如下 $(1,11,5)$，$(2,6,7)$，$(3,13,9)$，$(12,7,16)$，$(14,3,25)$，$(19,18,22)$，$(23,13,29)$，$(24,4,28)$，右边用轮廓线的顺序$(1,11,3,13,9,0,12,7,16,3,19,18,22,3,23,13,29,0)$ 表示：

![](https://cdn.luogu.com.cn/upload/image_hosting/oe7wpwsi.png)

## 输入格式

在输入数据中，你将得到一系列表示建筑的三元组。在输入数据中所有建筑的坐标中的数值都是小于 $10000$ 的正整数，且至少有 $1$ 幢建筑，最多有 $5000$ 幢建筑。在输入输入中每幢建筑的三元组各占一行。三元组中的所有整数应由一个或多个空格分开。

## 输出格式

在输出数据中，你被要求给出城市的轮廓线。你可以这样来描述：对于所有轮廓线上的折点，按顺序排好，第奇数个点输出 $x$ 坐标，第偶数个点输出 $y$ 坐标，两个数之间用空格分开。

## 样例

### 样例输入 #1
```
1 11 5
2 6 7
3 13 9
12 7 16
14 3 25
19 18 22
23 13 29
24 4 28

```
### 样例输出 #1
```
1 11 3 13 9 0 12 7 16 3 19 18 22 3 23 13 29 0
```


---

---
title: "[USACO17DEC] Blocked Billboard B"
layout: "post"
diff: 普及-
pid: P4122
tag: ['数学', '2017', 'USACO', '离散化']
---
# [USACO17DEC] Blocked Billboard B
## 题目描述

During long milking sessions, Bessie the cow likes to stare out the window of her barn at two huge rectangular billboards across the street advertising "Farmer Alex's Amazingly Appetizing Alfalfa" and "Farmer Greg's Great Grain". Pictures of these two cow feed products on the billboards look much tastier to Bessie than the grass from her farm.

One day, as Bessie is staring out the window, she is alarmed to see a huge rectangular truck parking across the street. The side of the truck has an advertisement for "Farmer Smith's Superb Steaks", which Bessie doesn't quite understand, but she is mostly concerned about the truck potentially blocking the view of her two favorite billboards.

Given the locations of the two billboards and the location of the truck, please calculate the total combined area of both billboards that is still visible. It is possible that the truck obscures neither, both, or only one of the billboards.

## 输入格式

The first line of input contains four space-separated integers: $x_1,y_1,x_2 y_2$, where $(x_1,y_1)$ and $(x_2,y_2)$ are the coordinates of the lower-left and upper-right corners of the first billboard in Bessie's 2D field of view. The next line contains four more integers, similarly specifying the lower-left and upper-right corners of the second billboard. The third and final line of input contains four integers specifying the lower-left and upper-right corners of the truck. All coordinates are in the range $-1000$ to $+1000$. The two billboards are guaranteed not to have any positive area of overlap between themselves.
## 输出格式

Please output the total combined area of both billboards that remains visible.
## 样例

### 样例输入 #1
```
1 2 3 5
6 0 10 4
2 1 8 3
```
### 样例输出 #1
```
17
```
## 提示

Here, 5 units of area from the first billboard and 12 units of area from the second billboard remain visible.

Problem credits: Brian Dean
## 题目翻译

### 题目描述

在漫长的挤奶过程中，奶牛 Bessie 喜欢透过谷仓的窗户盯着街对面的两块巨大的矩形广告牌，上面分别写着“Farmer Alex 的美味苜蓿”和“Farmer Greg 的优质谷物”。广告牌上这两种奶牛饲料的图片对 Bessie 来说比她农场里的草看起来美味得多。

有一天，当 Bessie 正盯着窗外时，她惊讶地看到一辆巨大的矩形卡车停在街对面。卡车的侧面有一则广告，写着“Farmer Smith 的顶级牛排”，Bessie 不太理解这则广告，但她更担心的是卡车可能会挡住她最喜欢的两块广告牌的视线。

给定两块广告牌和卡车的位置，请计算两块广告牌仍然可见的总面积。卡车可能遮挡了其中一块、两块，或者没有遮挡任何一块广告牌。

### 输入格式

输入的第一行包含四个用空格分隔的整数：$x_1,y_1,x_2 y_2$，其中 $(x_1,y_1)$ 和 $(x_2,y_2)$ 是 Bessie 的二维视野中第一块广告牌的左下角和右上角坐标。第二行包含四个整数，以相同的方式指定第二块广告牌的左下角和右上角坐标。第三行也是最后一行输入包含四个整数，指定卡车的左下角和右上角坐标。所有坐标都在 $-1000$ 到 $+1000$ 的范围内。保证两块广告牌之间没有任何重叠的正面积区域。

### 输出格式

请输出两块广告牌仍然可见的总面积。

### 说明/提示

在这个例子中，第一块广告牌有 $5$ 单位面积可见，第二块广告牌有 $12$ 单位面积可见。

题目来源：Brian Dean


---

