# Picking Strings

## 题目描述

Alice has a string consisting of characters 'A', 'B' and 'C'. Bob can use the following transitions on any substring of our string in any order any number of times:

- A ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/5a518872d8942914aef6c33d251688a64a8d6d74.png)BC
- B ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/5a518872d8942914aef6c33d251688a64a8d6d74.png)AC
- C ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/5a518872d8942914aef6c33d251688a64a8d6d74.png)AB
- AAA ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/5a518872d8942914aef6c33d251688a64a8d6d74.png) empty string

Note that a substring is one or more consecutive characters. For given queries, determine whether it is possible to obtain the target string from source.

## 说明/提示

In the first query we can achieve the result, for instance, by using transitions ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/bc389404fee8abb9f1186ea5ef11a96a445486ca.png).

The third query asks for changing AAB to A — but in this case we are not able to get rid of the character 'B'.

## 样例 #1

### 输入

```
AABCCBAAB
ABCB
5
1 3 1 2
2 2 2 4
7 9 1 1
3 4 2 3
4 5 1 3
```

### 输出

```
10011
```

# 题解

## 作者：C20203030 (赞：3)

## 一、题目
[点此看题](https://www.luogu.com.cn/problem/CF923D)
## 二、解法
智商题，像我这种蒟蒻怎么想得出来...????

第一步就是手玩，看你的想象力丰不丰富了，可以手$\text{van}$出这样一些结论：
- ``B->AC->AAB->AAAC->C->AB->AAC->AAAB->B``，这说明了``B,C``等价，原串中只需考虑两个字符
- ``B->AB->AAB->AAAB->B``，这说明了``AB,B``等价，也就是只要有``B``就可以生成$/$消去前面得``A``
- ``A->BC->BB``，这说明一个``A``是可以替换成``BB``

综合以上变化，我们可以得出一下判断方法：
- 由变化$2$得，``B``前的``A``是可以消去的，所以我们只需要考虑最后面``A``就行了，因为``A``后缀不能生成，所以$S$的``A``后缀一定不能小于$T$的``A``后缀。
- 由变化$2,3$得，只要有一个``B``，可以任意生成偶数的``B``，但是``B``不能删去，所以$S$的``B``一定不能更多，并且差值只能为偶数。
- 如果``A``后缀差值不为$3$的倍数，我们只能把$S$后缀``A``中的一个删去，使得删去后两者后缀``A``数量正好相等，此时$S$中``B``的数量会增加两个，要再次使用判断方法二。
- 最后再处理一种特殊情况，就是$S$中没有``B``但是$T$中有，如果这时候没有后缀``A``可以删去（也就是两个的后缀``A``已经相等），那这种情况就不行。

我们只需要维护一个``B``的前缀和，还有后缀``A``的长度即可，时间复杂度$O(n)$，更多细节请参考代码。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int M = 100005;
int read()
{
 int x=0,flag=1;char c;
 while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
 while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
 return x*flag;
}
int n,m,q,sa[M],ta[M],sb[M],tb[M];
char s[M],t[M];
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
    {
        sb[i]=sb[i-1]+(s[i]!='A');
        if(s[i]=='A') sa[i]=sa[i-1]+1;
    }
    scanf("%s",t+1);
    m=strlen(t+1);
    for(int i=1;i<=m;i++)
    {
        tb[i]=tb[i-1]+(t[i]!='A');
        if(t[i]=='A') ta[i]=ta[i-1]+1;
    }
    q=read();
    while(q--)
    {
        int a=read(),b=read(),c=read(),d=read(),f=1;
        int db=tb[d]-tb[c-1]-(sb[b]-sb[a-1]);
        int Sa=min(b-a+1,sa[b]),Ta=min(d-c+1,ta[d]);
        if(db<0 || Sa<Ta || db%2==1) f=0;
        bool pd=(Sa-Ta)%3>0;
        if(db-pd*2<0) f=0;
        if(sb[b]-sb[a-1]==0 && db && Sa==Ta) f=0;
        printf("%d",f);
    }
}

```



---

## 作者：tZEROちゃん (赞：2)

感觉不是我能想出来的题。但其实没啥算法在里面。

我们不如先把题目里的条件全部放出来：

- $\tt A\to BC$
- $\tt B\to AC$
- $\tt C\to AB$
- $\tt AAA\to$ 空串

首先我们看几个结论。

第一个就是 $\tt B$ 是等价于 $\tt C$ 的：$\tt {\color{red}B}\to A{\color{red}C}\to A{\color{red}AB}\to {\color{red}AAA}C\to C$，所以我们就不管 $\tt C$ 了，直接把他全部换成 $\tt B$。

然后就变成了这个样子：

- $\tt A\to BC$
- $\tt B\to AB$
- $\tt AAA\to$ 空串

我们注意到原来有个 $\tt C\to AB$，但是这个没了，因为替代之后这个其实等价于 $\tt B\to AB$，有一种想法是我们考虑把他反过来，变成 $\tt AB \to B$，成不成立，$\tt A{\color{red}B}\to AA{\color{red}C}\to {\color{red}AAA}B\to B$。你发现它是成立的。但其实「把他反过来」这种想法跟这个结论没啥关系。

- $\tt A\to BB$
- $\tt B\to AB$
- $\tt AB\to B$
- $\tt AAA\to$ 空串

可以注意到一些比较显然的结论：

1. $\tt B$ 的数量可以增加偶数个。        
   比如说，单个 $\tt B$，我们可以这样操作：$\tt {\color{red}B} \to \tt {\color{red} A}B\to BBB$ 这样我们就增加了 $2$ 个 $\tt B$，然后以此类推。
   
2. 任何 $\tt B$ 之前的 $\tt A$ 的数量都可以改变。  
   这个可以分两种情况看：
   - 增加：比如 $\tt A{\color{red} B}\to AAB$，这样就实现了一次增加，不断对 $\tt B$ 做这个操作就可以了。
   - 减少：比如 $\tt A{\color{red} AB} \to AB$，这样就实现了一次减少，不断对 $\tt B$ 做这个操作就可以了。

那根据结论 $2$，在 $\tt B$ 前面的 $\tt A$ 肯定不会影响什么，那我们就考虑后面的 $\tt A$。

还是分类考虑这个问题。

1. 如果原串 $\tt B$ 的数量正好和目标串相同。
2. 如果原串有 $\tt B$ 但比目标串多了。
3. 如果原串没有 $\tt B$ 但目标串有。

分这三类考虑即可。

计算 $\tt B,C$ 的前缀和以及对于每个位置连续 $\tt A$ 的长度即可。

代码很好写，不放了。

---

## 作者：Kazeno_Akina (赞：1)

写在前面：注意力惊人题目。

被同学搬到了模拟赛里，考场上想出来了几乎就是正解的东西，然而差两个细节光荣保龄！

下面将详细阐述我如何获得了正解思路，以及那一大堆需要注意的细节。

首先注意到本题的要求是「判断有没有解」并且数据范围相当大，因此容易想到这是一种类似构造/寻找不变量就可以判断的题。

然而没有什么头绪，因此考虑手玩一下样例。根据样例的第一个查询我们发现，存在手段能做到：`AAB`->`AB`。注意到第一个 `A` 被吃了。

于是我们考虑是否存在一个类似通解的东西，能做单位字符的删除/变换/添加。

我从 `C` 入手大概玩了 7min 左右，然后发现一个非常神秘的好东西：

`C`->`AB`->`AAC`->`AAAB`->`B`。

然后观察发现因为 `B` 和 `C` 在变换时模式相同所以这也意味着 `B` 能变成 `C`。

因此 `B` 和 `C` 完全等价。

于是我们把它转化成了一个 $01$ 串问题，即：$0\rightarrow 11$，$1\rightarrow 01$，$000\rightarrow NULL$。（其中 $0$ 为 `A`，$1$ 为 `B` 或 `C`）

这样就非常容易看出一些规律了。

1. $1$ 是不会变少的，$1$ 的奇偶性也是不变的，根据这个我们就能判断很多 $0$ 出来。

2. 只要 $1$ 的数量够了，对于最后一个 $1$ 前面的部分我们必然可以操作至和目标串的最后一个 $1$ 前面的部分相同。

3. 对于最后一个 $1$ 后面的部分，首先由于此处的 $0$ 只能减不能加，所以如果原始串结尾的 $0$ 本来就比目标串少那么就肯定不行。此时如果两者模三的余数相同，那么就存在构造；但如果不同，那么原始串里面的 $1$ 至少要比目标串少 $2$，因为此时原始串结尾的 $0$ 显然有要变成 $11$ 的，如果二者的 $1$ 数量相同那再塞两个 $1$ 进去就废了。

以上就是我考场上想到的部分，具体实现的时候为了不超时，需要维护一个 $1$ 数量的前缀和数组，还有一个「以这个下标为结尾最多有多少个连续的 $0$」的数组。

如果你只写了这些，就会像我一样在考场上光荣保龄（但是甚至可以过样例）。

接下来就是我在考后修改的两个细节，改完就可以通过了。

1. 考虑一种特殊的情况：原始串为 $x$ 个 $0$，目标串结尾正好 $x$ 个 $0$，并且前面是有 $1$ 的。此时原始串中没有 $1$，至少需要让一个 $0$ 变成 $11$ 才行。但是如果这样变，结尾的 $0$ 数量就会不够，所以需要特判一下无解。

2. 对于「以这个下标为结尾最多有多少个连续的 $0$」的数组，在实际使用的时候，需要记得将所记长度和全串长度取 $\min$。

修改完这些细节你就可以光荣 AC 此题了。

code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int q,l1,r1,l2,r2,c1,c2,k1,k2,d,lens,lent,pres[N],pret[N],mems[N],memt[N];
string s1,t1;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> s1 >> t1,lens=s1.length(),lent=t1.length();
    for(int i(1);i<=lens;++i){
        pres[i]=pres[i-1]+(s1[i-1]!='A');
        if(s1[i-1]=='A') mems[i]=mems[i-1]+1;
        else mems[i]=0;
    }
    for(int i(1);i<=lent;++i){
        pret[i]=pret[i-1]+(t1[i-1]!='A');
        if(t1[i-1]=='A') memt[i]=memt[i-1]+1;
        else memt[i]=0;
    }
    cin >> q;
    while(q--){
        cin >> l1 >> r1 >> l2 >> r2;
        c1=pres[r1]-pres[l1-1],c2=pret[r2]-pret[l2-1];
        if(c1>c2){cout << 0;continue;}
        if((c2-c1)&1){cout << 0;continue;}
        k1=mems[r1],k2=memt[r2];
        k1=min(r1-l1+1,k1),k2=min(r2-l2+1,k2);
        if(k1<k2){cout << 0;continue;}
        if(c1==0&&c2>0&&k1==k2){cout << 0;continue;}
        d=(k1-k2)%3;
        if(!d){cout << 1;continue;}
        if(c2==c1){cout << 0;continue;}
        cout << 1;
    }
    return 0;
}
```

---

