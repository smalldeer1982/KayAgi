# [NERC 2022] Hot and Cold

## 题目描述

这是一道交互题。

移居到另一个国家后，小 Hanna 发现玩“热与冷”游戏变得更加困难了：她听不懂提示语！你需要为她编写一个辅助程序。

游戏进行的场地是一个矩形，宝藏藏在某个整点坐标处，坐标范围在 $0$ 和 $10^6$ 之间（包含两端）。Hanna 会访问几个坐标合法的点。如果访问的点藏有宝藏，她会收到当地语言的短语“Found!”。幸运的是，语调让她能够识别出这个短语——在本题中，它将以一个感叹号作为标记。

否则，对于除第一个点外的每个访问点，Hanna 都会收到一个当地语言的短语，说明与前一个点相比，她现在距离宝藏是“Closer”、“Further”还是“At the same distance”。距离使用欧几里得度量进行计算。在访问第一个点后，如果那里没有宝藏，Hanna 会收到当地语言的短语“Not found”。

你的程序必须帮助 Hanna 在**最多访问 64 个点**的情况下找到宝藏。

### 交互方式

你的程序应该每行输出一个访问点的两个坐标（范围在 $0$ 到 $10^6$ 之间，包含两端），并在每次输出后刷新输出流。

对于每个访问的点，测试系统会用某种在整个游戏过程中保持一致的语言写入以下短语之一：“Found!”、“Closer”、“Further”、“At the same distance”或“Not found”。第一个短语以感叹号结尾，所有其他短语不包含感叹号。所有短语只包含拉丁字母、空格和感叹号，长度在 $2$ 到 $30$ 之间（包含两端），不以空格开头或结尾，并且两两不同。这些短语不一定来自任何真实的人类语言。

在收到带感叹号的短语后，你的程序必须停止，且不再打印任何内容。允许重复访问同一点，每次这样的访问都会计入 64 次查询的限制中。

## 样例 #1

### 输入

```

Tabilmadi

Daha yakin

Daha yakin

Sama distanco

Dalej

Znaydeno!```

### 输出

```
500 200

560 230

566 240

566 238

30 239

566 239```

## 样例 #2

### 输入

```

You are lucky today!```

### 输出

```
777777 777777```

# 题解

## 作者：RainySoul (赞：1)

好玩！好题要点赞。但是别人怎么都是两分钟秒了，好像难度虚高。

首先考虑我们询问的步骤应该是确定出每个单次的词义之后，先跳到与宝藏 $x$ 坐标相同的点上，然后跳到与宝藏 $y$ 坐标相同的点上。

问出词义这个东西不能再简单了，从 $(0,0)$ 开始询问，然后跳到 $(1,1)$，然后跳回 $(0,0)$，稍微分讨即可。只有宝藏在 $(1,0)$ 或者 $(0,1)$ 的时候你会问出两个 `At the same distance`，其他时候跳到 $(1,1)$ 问出的都是 `Closer`，跳回 $(0,0)$ 问出的都是 `Further`。

确定一维坐标的过程可以直接二分，现在范围是 $[l,r]$ 时你从 $l$ 跳到 $r$ 就可以知道宝藏是在 $[l,mid]$ 还是 $[mid+1,r]$，最劣情况下两次操作可以将询问范围减半，$2^{16}=65536<10^6$，还不太够用。

想到一个比较上流的做法，考虑能不能直接两维一起确定。发现只要跳当前范围矩阵的三个角就可以将两维都减少一半。

![](https://cdn.luogu.com.cn/upload/image_hosting/1snktpxh.png)

然后就是三次操作将二维都变为原来一半，这部分需要的操作次数是 $3\times \log(10^6)=3\times 19.931568569=60$，加上确定词义的 $3$ 次，共是 $63$ 次，卡得非常死。

```cpp
/*落叶的位置 谱出一首诗
时间在消逝 我们的故事开始*/
#include<bits/stdc++.h>
using namespace std;
int main(){
    string notfound,closer,further;
    cout<<"0 0\n";
    getline(cin,notfound);
    if(notfound.back()=='!')return 0;
    cout<<"1 1\n";
    getline(cin,closer);
    if(closer.back()=='!')return 0;
    cout<<"0 0\n";
    getline(cin,further);
    if(closer==further){
        string temp;
        cout<<"0 1\n";
        getline(cin,temp);
        if(temp.back()=='!')return 0;
        cout<<"1 0\n";
        getline(cin,temp);
        if(temp.back()=='!')return 0;
    }
    int lx=0,rx=1000000,ly=0,ry=1000000;
    while(1){
        string temp1,temp2;
        int midx=(lx+rx)>>1,midy=(ly+ry)>>1;
        cout<<rx<<" "<<ly<<'\n';
        getline(cin,temp1);
        if(temp1.back()=='!')return 0;
        cout<<rx<<" "<<ry<<'\n';
        getline(cin,temp2);
        if(temp2.back()=='!')return 0;
        if(temp1==closer)lx=midx+1;
        else if(temp1==further)rx=midx;
        else lx=rx=midx;
        if(temp2==closer)ly=midy+1;
        else if(temp2==further)ry=midy;
        else ly=ry=midy;
        cout<<lx<<" "<<ly<<'\n';
        getline(cin,temp2);
        if(temp2.back()=='!')return 0;
    }
    return 0;
}
```

广告：强推林俊杰《愿与愁》《关键词》

---

## 作者：AC_love (赞：1)

首先考虑如果我们知道每个单词是什么含义，这时该怎么做。

先从一维的情况开始考虑，不难发现可以二分。

在当前区域内，每次取中点和中点右面的点，如果得到的回复是“Closer”说明在中点右面，反之则在中点左面。

一个维度的二分次数为 $2 \times \log_210^6$，是 $40$ 次。对两个维度分别做二分，需要的次数是 $80$。

这样做是对的，但超过了 $64$。原因是我们对两个维度分别做二分，对一个维度二分时会浪费另一个维度的信息。我们考虑对两个维度同时做二分。

取平面中点，再取中点上方的点，如果回复“Closer”说明宝藏在中点上方，反之在中点下方。然后取中点右上方的点，如果回复“Closer”说明在中点右侧，反之则在中点左侧。

这样做只需要取 $3$ 个点就对两个维度同时进行了二分。最后需要的次数是 $60$，小于 $64$ 次，非常成功。

现在我们并不知道每个单词是什么含义，我们考虑如何知道。

带感叹号的一定是“Found!”，第一个出现的一定是“Not Found”。我们只需要区分“Closer”“Further”和“At the same distance”即可。

取 $(0, 0)$ 作为第一个点，取 $(1, 1)$ 作为第二个点，这时得到的回复要么是“Closer”要么是“At the same distance”。

然后我们再取回 $(0, 0)$，如果得到的回复和刚才不同，那么刚才的回复是“Closer”，现在的回复是“Further”，那个没出现的回复就是“At the same distance”。这时用了 $3$ 次询问，加上刚才的 $60$ 次，总共 $63$ 次，没有超过 $64$。

如果相同的话，说明这个回复是“At the same distance”，那么宝藏一定在 $(0, 1)$ 或 $(1, 0)$ 的位置，分别询问即可。

---

