# Clock Patience

## 题目描述

Card sharp Albert (Foxy) Smith 正在写一本有关于耐心游戏的书。为了仔细检查书中的例子，他正在编写程序以找到最佳玩法。

一个叫做 Clock Patience 的游戏的描述如下：

扑克牌面朝下按顺时针方向绕一个圆形发牌，代表一个时钟。每个小时上有一堆卡片，时钟中心还有一堆额外的卡片。第一张牌放在一点钟的位置，第二张放在两点钟，依此类推，顺时针方向放置，每第十三张牌放到时钟的中心。这就形成了十三堆，每堆里有四张牌是面朝下的。（下文中用 T 来代替 $10$）
![](https://cdn.luogu.com.cn/upload/image_hosting/zxlzflxl.png)

发完牌后游戏开始。K 牌堆的顶牌（即最后一张发的牌）作为当前牌。此后按照如下方式进行：

1. 将当前牌翻开，放在其点数对应的牌堆的最下面。
2. 当前牌堆的最上面的牌成为新的当前牌。
3. 如果当前牌正面朝上，游戏结束。

现在写一个程序，输入一叠被打乱的牌，然后玩这个游戏。

## 样例 #1

### 输入

```
TS QC 8S 8D QH 2D 3H KH 9H 2H TH KS KC
9D JH 7H JD 2S QS TD 2C 4H 5H AD 4D 5D
6D 4S 9S 5S 7S JS 8H 3D 8C 3S 4C 6S 9C
AS 7C AH 6H KD JC 7D AC 5C TC QD 6C 3C
#```

### 输出

```
44,KD```

# 题解

## 作者：b__b (赞：1)

~~UVa 大模拟的奇怪输入我已经见怪不怪了~~

首先可以先实现一个将 char 转换为 int 的函数：
```cpp
int ctoi(char c) {
    if ('2' <= c && c <= '9') return c - '0';
    switch (c) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
    }
}
```
然后接着我们考虑如何实现牌堆，由于这里牌是从下往上放，从上往下拿，后面还有一个将牌放到最后面的操作，因此我们会很自然的想到双端队列，所以我们要用一个双端队列数组来实现牌堆的操作

吗？

（下面可以说是一种投机取巧的方案，用双端队列或者栈其实也没问题）

> 牌组是从下到上排列的，所以发的第一张牌就是最后一张牌。

输入是从下到上给的，因此输入时放进一个栈里面，输入完后将每一个元素弹出。

然后牌是从下往上放的，这时可以看成一个栈，遍历时将每一个元素放入。

我们发现，**这不就是用栈来实现队列的步骤吗？**

因此我们放牌时可以直接顺序读取然后将牌放到队列的最后。

接着我们考虑后面将牌放到最后面的操作，由于先将牌转到前面再放进去，而当这一个牌堆里面的最上面的牌是正面朝上时游戏结束，因此这张翻过来的牌其实已经没有用了，可以直接弹出，不需要后面再放入的操作。

所以牌堆的数据结构实现就可以是
```cpp
std::queue<std::pair<char, char>> pais[15];
//数组下标为几就是第几堆牌
//std::pair<char, char> 的第一个元素就是牌的数字，第二个元素就是牌的花色
```
然后游戏过程按照题意稍加处理就可以实现了。

#### 一些细节
最主要的细节还是输入。

~~**不要用 getchar 啊！**~~

因为我们不知道输入数据在样例上看起来的纯洁无害是否是真的，因此我们要~~用最大的恶意去揣测别人~~做好一切准备。

由于这道题最多只有 $52$ 张牌，因此只要算法正确（~~大模拟有什么算法~~），我们基本不需要考虑时间问题。

这时 cin 就很符合我们的要求，cin 在输入时会自动过滤一些不可见字符，保证你输入到的数据都是纯洁无害的。

最后，再说一句：这道题有多个测试数据。
### 代码
注：由于写这篇题解的人马蜂诡异且有着奇怪的癖好，以下代码仅供参考。
```cpp
#include <iostream>
#include <queue>
std::queue<std::pair<char, char>> pais[15];
inline int ctoi(char c) {
    if ('2' <= c && c <= '9') return c - '0';
    switch (c) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
    }
}
int main() {
    for (char c, j; std::cin >> c && c != '#';) {
        for (int i = 1; i <= 13; ++i) while (!pais[i].empty()) pais[i].pop();
        std::cin >> j, pais[13].push({c, j});
        int ans = 0, ind = 13;
        std::pair<char, char> now;
        for (int i = 1; i < 52; ++i) std::cin >> now.first >> now.second, pais[13 - i % 13].push(now);
        for (; !pais[ind].empty(); now = pais[ind].front(), pais[ind].pop(), ind = ctoi(now.first), ++ans);
        printf("%02d,", ans), putchar(now.first), putchar(now.second), putchar('\n');
    }
}
```

---

