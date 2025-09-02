---
title: "KIMO4 - Kawigi quote"
layout: "post"
diff: 难度0
pid: SP15498
tag: []
---

# KIMO4 - Kawigi quote

## 题目描述

2013 年 7 月 25 日，我的朋友 [Goodname](../../../users/hossameldeen/) 在我们的 Facebook 小组（Virtual Contests）里分享了一个链接，指向 [Kawigi](http://community.topcoder.com/tc?module=MemberProfile&cr=8416646) 的 TopCoder 个人资料页面。

他因为 Kawigi 的一句话而感到惊讶，因为在 [Ideone](http://ideone.com/MSrP0c) 上测试后发现它打印出了 "C++Sucks"，这让我们都大为震惊。

几分钟后，另一位朋友 [Mosa](../../../users/mc_mosa/) 在帖子下评论，附上了一段代码的 [Ideone](http://ideone.com/AUPTQx) 链接。令人惊叹的是，他破解了这个秘密，但他有点贪心，不愿意告诉我们其中的诀窍。现在我们想要像 Mosa 那样思考，以便解决这个问题。

给定一个字符串，你需要找到 m\[0\] 和 m\[1\] 的值，使得当我们运行下面的代码时，可以输出给定的字符串。

### 代码

```cpp
#include <stdio.h>

int primes [] = {2,3,5,7,11};  
  
double m[2] = {8242465576917890.0 ,494};  
  
int main() {  
    m[1]-- ? m[0] /= primes[((int)m[1]+1)%5], main() : printf((char*)m);  
}
```

// 这段代码会打印字符串 "123"。

### 输入格式
输入的第一行是一个整数 $T$ （$T \leq 50$），表示接下来有多少组测试数据。

每组测试数据在一行中，包含最多 6 个字符（可以是字母或数字，A-Za-z0-9）。

### 输出格式
针对每组测试数据，输出 m\[0\] 和 m\[1\] 的值，用空格隔开。

保证一定存在满足条件的解。如果有多个解，你可以输出其中任意一个。

### 示例
```
输入：
4
123
abdou
mcMosa
kimo3

输出：
8242465576917890.0 494
6966198460426549.0 487
4484456159639948.0 483
21357815651012032.0 488
```

#### 特别感谢：
- [Mitch Schwartz](../../../users/cyclops/) 发现问题中的错误。
- [Mosa Osama](../../../users/mc_mosa/) 编写了该题目的特殊评测程序。特别要说的是，Mosa 并不吝于分享。😉

 **本翻译由 AI 自动生成**

