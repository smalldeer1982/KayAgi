# [BalticOI 2010] Lego (Day1)

## 题目描述

给定一些 $2 \times 2$ 的乐高方块，分别有白色（W），灰色（G）和黑色（B）。现在您要往 $6 \times 6$ 的底板上放置方块，需要保证不能有完全浮空的方块（即四个方格均无放置的地方）也不能超出 $6 \times 6$ 的底板。

现在给定一个放置完方块的底板的一面的示意图，和这一面逆时针旋转 $90^\circ$ 后的一面的示意图，求有多少种放置方块的方法数。

## 说明/提示

#### 样例 1 解释

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/njr2rk9l.png)

第一个是从 $A$ 面观察到的示意图。    
第二个是从 $B$ 面（$A$ 面逆时针旋转 $90^\circ$）观察到的示意图。

下面是这 $6$ 种情况（感谢 Vonov 提供的图片！）：

![](https://cdn.luogu.com.cn/upload/image_hosting/wymozlif.png)         
![](https://cdn.luogu.com.cn/upload/image_hosting/1vw0fu3t.png)         
![](https://cdn.luogu.com.cn/upload/image_hosting/umn2hync.png)             
![](https://cdn.luogu.com.cn/upload/image_hosting/pykojvay.png)           
![](https://cdn.luogu.com.cn/upload/image_hosting/9z9wvzxp.png)          
![](https://cdn.luogu.com.cn/upload/image_hosting/hkp3tjfp.png)

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le H \le 6$。

#### 说明

翻译自 [BalticOI 2010 Day1 B Lego](https://boi.cses.fi/files/boi2010_day1.pdf)。

## 样例 #1

### 输入

```
2
WWGG..
.BB.WW
.WGG..
WWGG..```

### 输出

```
6```

