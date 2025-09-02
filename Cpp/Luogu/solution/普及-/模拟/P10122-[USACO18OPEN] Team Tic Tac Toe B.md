# [USACO18OPEN] Team Tic Tac Toe B

## 题目描述

Farmer John 有 $26$ 头奶牛，恰好她们名字都以不同的字母开头，所以 Farmer John 用每头奶牛的名字的首字母来指代她——一个 `A-Z` 之间的字母。

这些奶牛最近沉迷于井字游戏，但是由于她们并不满足只有两头奶牛可以一起玩，她们改编了这个游戏，可以让许多奶牛可以一块儿玩！就像常规的井字游戏一样，这个游戏是在一块 $3×3$
的棋盘上进行的，只是与仅用 `X` 和 `O` 不同，每个格子用一个 `A-Z` 之间的字母标记，表示占有这个格子的奶牛名字的首字母。

以下是一个棋盘的例子：

```plain
COW
XXO
ABC
```

这些奶牛会在她们迷惑于如何判断胜负之前就占满这九个格子。显然，就像常规的井字游戏一样，如果任何一头奶牛占有了一整行、一整列，或是一整条对角线，那么这头奶牛就获胜了。然而，由于奶牛认为多牛游戏中这并不容易出现，所以她们决定允许奶牛组成两牛一队，如果某一行、一列，或是一条对角线仅包含一队的两头奶牛的字母，并且同时包含了这两头奶牛（不仅仅是一头）的字母，那么这一队就获胜。

请帮助奶牛们判断有多少头奶牛或是两头奶牛组成的队伍可以获胜。注意棋盘上的同一个格子可能在不同奶牛或队伍的获胜中均被用到。 

## 说明/提示

在这个例子中，没有单独的奶牛可以获得胜利。但是，如果奶牛 `C` 和奶牛 `X` 组队，她们可以通过 `C-X-C` 对角线获胜。同样地，如果奶牛 `X` 和 `O` 组队，她们可以通过中间一行取胜。 

## 样例 #1

### 输入

```
COW
XXO
ABC```

### 输出

```
0
2```

# 题解

## 作者：2021zjhs005 (赞：6)

这是一道强大的 `if` 语句题，难度大概为橙。


Despriction
------------
给定一个 $3\times 3$ 的“井”自行棋盘，求每一行、每一列、每一对角线中，**不同的**全部相等的和 $2$ 个相等的出现的次数。

Solution
------------
直接枚举每一行、每一列、每一对角线，然后判断即可。

这时因为大量重复代码不太美观，所以可以自定义一个 $\operatorname{judge}(a,b,c)$ 函数。$a,b,c$ 分别表示当前行或列或对角线的 $3$ 个元素。

- 如果 $a=b\ \Lambda\ a=c\ \Lambda\ b=c$，这时对答案一的贡献为 $1$。

- 如果 $a,b,c$ 中有两个相等，那么对答案二的贡献为 $1$。

但是这题也有坑点，不仔细看清题目的可能会掉进去。

比如：
```
Input:

ABA
BAB
ABA

Output:

1
1
```

这是因为题目求的是**不同的**奶牛的数量，相同的可能会造成 $2$ 次，或者更多贡献，然而实际只算 $1$ 次。

开两个 `map`，第一个 $f_i = 1$ 表示 $i$ 已经对答案一作出贡献，反之，则没有对答案一做出贡献。

第二个 $f_{i,j} = 1$，表示 $i,j$ 组队已经对答案二做出贡献，反之，则没有。

判断条件就变成了：


- 如果 $a=b\ \Lambda\ a=c\ \Lambda\ b=c\ \Lambda\ f_a = 0$，这时对答案一的贡献为 $1$。

- 如果 $a,b,c$ 中有两个相等，并且相等的 $i,j$ 满足 $f_{i,j} = 0\ \Lambda\ f_{j,i} = 0$，那么对答案二的贡献为 $1$。


Code
------------
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int ans1,ans2;
char a[4][4];
map <char,bool> f,f1[100];

inline char min(char a,char b){
    return a<b?a:b;
}
inline char max(char a,char b){
    return a>b?a:b;
}
inline void judge(char cow1,char cow2,char cow3){
    if(cow1==cow2&&cow2==cow3){//三个都相等。
        if(!f[cow1]){//没有重复，则对答案一贡献加 1。
            ans1++;
            f[cow1]=1;
        }
    }
    else if(!(cow1!=cow2&&cow1!=cow3&&cow2!=cow3)){//如果不是两两不同，那么只有三个都相同或者有两个相同。因为 else 否决了一个，所以只剩下两个相同的情况。
        char c1=min(cow1,min(cow2,cow3)),c2=max(cow1,max(cow2,cow3));//比最小值和最大值，方便查找不同的元素。
        if(!f1[c1][c2]&&!f1[c2][c1]){//没有重复，则对答案二的贡献加 1。
            ans2++;
            f1[c1][c2]=f1[c2][c1]=1;
        }
    }
}
signed main(){
    rep(i,1,3)
        rep(j,1,3)
            cin>>a[i][j];
    rep(i,1,3){
        judge(a[i][1],a[i][2],a[i][3]);//行。
        //-------------------------------
        judge(a[1][i],a[2][i],a[3][i]);//列。
    }
    judge(a[1][1],a[2][2],a[3][3]);
    judge(a[1][3],a[2][2],a[3][1]);//对角线。
    pr("%lld\n%lld\n",ans1,ans2);
    return 0;
}
```


---

## 作者：laozhang_123 (赞：4)

## P10122 [USACO18OPEN] Team Tic Tac Toe B
[题目传送门](https://www.luogu.com.cn/problem/P10122)

这是一道大模拟（对我来说），看到很多人用 `map`，那我就来发个不一样的题解。

我决定只用模拟来做这道题。

首先是输入：

```cpp
char ch[3][3];
for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        scanf("%c",&ch[i][j]);
    }
    getchar();		//输入字符后，指针停留在行末，可以通过输入一个字符来转移指针
}
```


对于一只牛，获胜的情况如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/de42fmqq.png)![](https://cdn.luogu.com.cn/upload/image_hosting/yvbcrjk7.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/n43hbzvi.png)![](https://cdn.luogu.com.cn/upload/image_hosting/5vselu2f.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/wlbsatyq.png)![](https://cdn.luogu.com.cn/upload/image_hosting/3ad2i06o.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/byiqk8li.png)![](https://cdn.luogu.com.cn/upload/image_hosting/jrf9yfcy.png)

于是就有了如下的代码：

```cpp
int cnt1=0;
//判断单独的奶牛
//判断第一行
if(ch[0][0]==ch[0][1]&&ch[0][1]==ch[0][2]) cnt1++,cow1[ch[0][0]-'A']=1;
//判断第二行
if(ch[1][0]==ch[1][1]&&ch[1][1]==ch[1][2]) cnt1++,cow1[ch[1][0]-'A']=1;
//判断第三行
if(ch[2][0]==ch[2][1]&&ch[2][1]==ch[2][2]) cnt1++,cow1[ch[2][0]-'A']=1;
//判断第一列
if(ch[0][0]==ch[1][0]&&ch[1][0]==ch[2][0]) cnt1++,cow1[ch[0][0]-'A']=1;
//判断第二列
if(ch[0][1]==ch[1][1]&&ch[1][1]==ch[2][1]) cnt1++,cow1[ch[0][1]-'A']=1;
//判断第三列
if(ch[0][2]==ch[1][2]&&ch[1][2]==ch[2][2]) cnt1++,cow1[ch[0][2]-'A']=1;
//判断2条对角线
if(ch[0][0]==ch[1][1]&&ch[1][1]==ch[2][2]) cnt1++,cow1[ch[0][0]-'A']=1;
if(ch[0][2]==ch[1][1]&&ch[1][1]==ch[2][0]) cnt1++,cow1[ch[0][2]-'A']=1;

```
而两只牛组队的情况则比较难处理一点，判断是否有两个字符相同的同时，还要判断三个字符是不是不相等：

```cpp
int cnt2=0;
//判断组队的奶牛 
//判断第一行
if((ch[0][0]==ch[0][1]||ch[0][1]==ch[0][2]||ch[0][0]==ch[0][2])&&!(ch[0][0]==ch[0][1]&&ch[0][1]==ch[0][2])) cnt2++;
//判断第二行
if((ch[1][0]==ch[1][1]||ch[1][1]==ch[1][2]||ch[1][0]==ch[1][2])&&!(ch[1][0]==ch[1][1]&&ch[1][1]==ch[1][2])) cnt2++;
//判断第三行
if((ch[2][0]==ch[2][1]||ch[2][1]==ch[2][2]||ch[2][0]==ch[2][2])&&!(ch[2][0]==ch[2][1]&&ch[2][1]==ch[2][2])) cnt2++;
//判断第一列
if((ch[0][0]==ch[1][0]||ch[1][0]==ch[2][0]||ch[0][0]==ch[2][0])&&!(ch[0][0]==ch[1][0]&&ch[1][0]==ch[2][0])) cnt2++;
//判断第二列
if((ch[0][1]==ch[1][1]||ch[1][1]==ch[2][1]||ch[0][1]==ch[2][1])&&!(ch[0][1]==ch[1][1]&&ch[1][1]==ch[2][1])) cnt2++;
//判断第三列
if((ch[0][2]==ch[1][2]||ch[1][2]==ch[2][2]||ch[0][2]==ch[2][2])&&!(ch[0][2]==ch[1][2]&&ch[1][2]==ch[2][2])) cnt2++;
//判断2条对角线
if((ch[0][0]==ch[1][1]||ch[1][1]==ch[2][2]||ch[0][0]==ch[2][2])&&!(ch[0][0]==ch[1][1]&&ch[1][1]==ch[2][2])) cnt2++;
if((ch[0][2]==ch[1][1]||ch[1][1]==ch[2][0]||ch[0][2]==ch[2][0])&&!(ch[0][2]==ch[1][1]&&ch[1][1]==ch[2][0])) cnt2++;
```
这样代码就打好了。

可是一交上去，却发现[WA](https://www.luogu.com.cn/record/146681066)了。这是为什么呢？

原来，如果一个队伍有两个或以上次获胜，那么 `cnt2` 会重复计算。

所以我们的应对措施就是：

```cpp
bool cow1[26],cow2[26][26];
//判断单独的奶牛
//判断第一行
if(ch[0][0]==ch[0][1]&&ch[0][1]==ch[0][2]&&!cow1[ch[0][0]-'A']) cnt1++,cow1[ch[0][0]-'A']=1;
//判断第二行
if(ch[1][0]==ch[1][1]&&ch[1][1]==ch[1][2]&&!cow1[ch[1][0]-'A']) cnt1++,cow1[ch[1][0]-'A']=1;
//判断第三行
if(ch[2][0]==ch[2][1]&&ch[2][1]==ch[2][2]&&!cow1[ch[2][0]-'A']) cnt1++,cow1[ch[2][0]-'A']=1;
//判断第一列
if(ch[0][0]==ch[1][0]&&ch[1][0]==ch[2][0]&&!cow1[ch[0][0]-'A']) cnt1++,cow1[ch[0][0]-'A']=1;
//判断第二列
if(ch[0][1]==ch[1][1]&&ch[1][1]==ch[2][1]&&!cow1[ch[0][1]-'A']) cnt1++,cow1[ch[0][1]-'A']=1;
//判断第三列
if(ch[0][2]==ch[1][2]&&ch[1][2]==ch[2][2]&&!cow1[ch[0][2]-'A']) cnt1++,cow1[ch[0][2]-'A']=1;
//判断2条对角线
if(ch[0][0]==ch[1][1]&&ch[1][1]==ch[2][2]&&!cow1[ch[0][0]-'A']) cnt1++,cow1[ch[0][0]-'A']=1;
if(ch[0][2]==ch[1][1]&&ch[1][1]==ch[2][0]&&!cow1[ch[0][2]-'A']) cnt1++,cow1[ch[0][2]-'A']=1;
//判断组队的奶牛 
//判断第一行
if((ch[0][0]==ch[0][1]||ch[0][1]==ch[0][2]||ch[0][0]==ch[0][2])&&!(ch[0][0]==ch[0][1]&&ch[0][1]==ch[0][2])&&(!cow2[ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')]&&!cow2[ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')][ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')])) cnt2++,cow2[ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')]=1;
//判断第二行
if((ch[1][0]==ch[1][1]||ch[1][1]==ch[1][2]||ch[1][0]==ch[1][2])&&!(ch[1][0]==ch[1][1]&&ch[1][1]==ch[1][2])&&(!cow2[ch[1][0]==ch[1][1]?ch[1][0]-'A':(ch[1][1]==ch[1][2]?ch[1][1]-'A':ch[1][0]-'A')][ch[1][0]==ch[1][1]?ch[1][2]-'A':(ch[1][1]==ch[1][2]?ch[1][0]-'A':ch[1][1]-'A')]&&!cow2[ch[1][0]==ch[1][1]?ch[1][2]-'A':(ch[1][1]==ch[1][2]?ch[1][0]-'A':ch[1][1]-'A')][ch[1][0]==ch[1][1]?ch[1][0]-'A':(ch[1][1]==ch[1][2]?ch[1][1]-'A':ch[1][0]-'A')])) cnt2++,cow2[ch[1][0]==ch[1][1]?ch[1][0]-'A':(ch[1][1]==ch[1][2]?ch[1][1]-'A':ch[1][0]-'A')][ch[1][0]==ch[1][1]?ch[1][2]-'A':(ch[1][1]==ch[1][2]?ch[1][0]-'A':ch[1][1]-'A')]=1;
//判断第三行
if((ch[2][0]==ch[2][1]||ch[2][1]==ch[2][2]||ch[2][0]==ch[2][2])&&!(ch[2][0]==ch[2][1]&&ch[2][1]==ch[2][2])&&(!cow2[ch[2][0]==ch[2][1]?ch[2][0]-'A':(ch[2][1]==ch[2][2]?ch[2][1]-'A':ch[2][0]-'A')][ch[2][0]==ch[2][1]?ch[2][2]-'A':(ch[2][1]==ch[2][2]?ch[2][0]-'A':ch[2][1]-'A')]&&!cow2[ch[2][0]==ch[2][1]?ch[2][2]-'A':(ch[2][1]==ch[2][2]?ch[2][0]-'A':ch[2][1]-'A')][ch[2][0]==ch[2][1]?ch[2][0]-'A':(ch[2][1]==ch[2][2]?ch[2][1]-'A':ch[2][0]-'A')])) cnt2++,cow2[ch[2][0]==ch[2][1]?ch[2][0]-'A':(ch[2][1]==ch[2][2]?ch[2][1]-'A':ch[2][0]-'A')][ch[2][0]==ch[2][1]?ch[2][2]-'A':(ch[2][1]==ch[2][2]?ch[2][0]-'A':ch[2][1]-'A')]=1;
//判断第一列
if((ch[0][0]==ch[1][0]||ch[1][0]==ch[2][0]||ch[0][0]==ch[2][0])&&!(ch[0][0]==ch[1][0]&&ch[1][0]==ch[2][0])&&(!cow2[ch[0][0]==ch[1][0]?ch[0][0]-'A':(ch[1][0]==ch[2][0]?ch[1][0]-'A':ch[0][0]-'A')][ch[0][0]==ch[1][0]?ch[2][0]-'A':(ch[1][0]==ch[2][0]?ch[0][0]-'A':ch[1][0]-'A')]&&!cow2[ch[0][0]==ch[1][0]?ch[2][0]-'A':(ch[1][0]==ch[2][0]?ch[0][0]-'A':ch[1][0]-'A')][ch[0][0]==ch[1][0]?ch[0][0]-'A':(ch[1][0]==ch[2][0]?ch[1][0]-'A':ch[0][0]-'A')])) cnt2++,cow2[ch[0][0]==ch[1][0]?ch[0][0]-'A':(ch[1][0]==ch[2][0]?ch[1][0]-'A':ch[0][0]-'A')][ch[0][0]==ch[1][0]?ch[2][0]-'A':(ch[1][0]==ch[2][0]?ch[0][0]-'A':ch[1][0]-'A')]=1;
//判断第二列
if((ch[0][1]==ch[1][1]||ch[1][1]==ch[2][1]||ch[0][1]==ch[2][1])&&!(ch[0][1]==ch[1][1]&&ch[1][1]==ch[2][1])&&(!cow2[ch[0][1]==ch[1][1]?ch[0][1]-'A':(ch[1][1]==ch[2][1]?ch[1][1]-'A':ch[0][1]-'A')][ch[0][1]==ch[1][1]?ch[2][1]-'A':(ch[1][1]==ch[2][1]?ch[0][1]-'A':ch[1][1]-'A')]&&!cow2[ch[0][1]==ch[1][1]?ch[2][1]-'A':(ch[1][1]==ch[2][1]?ch[0][1]-'A':ch[1][1]-'A')][ch[0][1]==ch[1][1]?ch[0][1]-'A':(ch[1][1]==ch[2][1]?ch[1][1]-'A':ch[0][1]-'A')])) cnt2++,cow2[ch[0][1]==ch[1][1]?ch[0][1]-'A':(ch[1][1]==ch[2][1]?ch[1][1]-'A':ch[0][1]-'A')][ch[0][1]==ch[1][1]?ch[2][1]-'A':(ch[1][1]==ch[2][1]?ch[0][1]-'A':ch[1][1]-'A')]=1;
//判断第三列
if((ch[0][2]==ch[1][2]||ch[1][2]==ch[2][2]||ch[0][2]==ch[2][2])&&!(ch[0][2]==ch[1][2]&&ch[1][2]==ch[2][2])&&(!cow2[ch[0][2]==ch[1][2]?ch[0][2]-'A':(ch[1][2]==ch[2][2]?ch[1][2]-'A':ch[0][2]-'A')][ch[0][2]==ch[1][2]?ch[2][2]-'A':(ch[1][2]==ch[2][2]?ch[0][2]-'A':ch[1][2]-'A')]&&!cow2[ch[0][2]==ch[1][2]?ch[2][2]-'A':(ch[1][2]==ch[2][2]?ch[0][2]-'A':ch[1][2]-'A')][ch[0][2]==ch[1][2]?ch[0][2]-'A':(ch[1][2]==ch[2][2]?ch[1][2]-'A':ch[0][2]-'A')])) cnt2++,cow2[ch[0][2]==ch[1][2]?ch[0][2]-'A':(ch[1][2]==ch[2][2]?ch[1][2]-'A':ch[0][2]-'A')][ch[0][2]==ch[1][2]?ch[2][2]-'A':(ch[1][2]==ch[2][2]?ch[0][2]-'A':ch[1][2]-'A')]=1;
//判断2条对角线
if((ch[0][0]==ch[1][1]||ch[1][1]==ch[2][2]||ch[0][0]==ch[2][2])&&!(ch[0][0]==ch[1][1]&&ch[1][1]==ch[2][2])&&(!cow2[ch[0][0]==ch[1][1]?ch[0][0]-'A':(ch[1][1]==ch[2][2]?ch[1][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[1][1]?ch[2][2]-'A':(ch[1][1]==ch[2][2]?ch[0][0]-'A':ch[1][1]-'A')]&&!cow2[ch[0][0]==ch[1][1]?ch[2][2]-'A':(ch[1][1]==ch[2][2]?ch[0][0]-'A':ch[1][1]-'A')][ch[0][0]==ch[1][1]?ch[0][0]-'A':(ch[1][1]==ch[2][2]?ch[1][1]-'A':ch[0][0]-'A')])) cnt2++,cow2[ch[0][0]==ch[1][1]?ch[0][0]-'A':(ch[1][1]==ch[2][2]?ch[1][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[1][1]?ch[2][2]-'A':(ch[1][1]==ch[2][2]?ch[0][0]-'A':ch[1][1]-'A')]=1;
if((ch[0][2]==ch[1][1]||ch[1][1]==ch[2][0]||ch[0][2]==ch[2][0])&&!(ch[0][2]==ch[1][1]&&ch[1][1]==ch[2][0])&&(!cow2[ch[0][2]==ch[1][1]?ch[0][2]-'A':(ch[1][1]==ch[2][0]?ch[1][1]-'A':ch[0][2]-'A')][ch[0][2]==ch[1][1]?ch[2][0]-'A':(ch[1][1]==ch[2][0]?ch[0][2]-'A':ch[1][1]-'A')]&&!cow2[ch[0][2]==ch[1][1]?ch[2][0]-'A':(ch[1][1]==ch[2][0]?ch[0][2]-'A':ch[1][1]-'A')][ch[0][2]==ch[1][1]?ch[0][2]-'A':(ch[1][1]==ch[2][0]?ch[1][1]-'A':ch[0][2]-'A')])) cnt2++,cow2[ch[0][2]==ch[1][1]?ch[0][2]-'A':(ch[1][1]==ch[2][0]?ch[1][1]-'A':ch[0][2]-'A')][ch[0][2]==ch[1][1]?ch[2][0]-'A':(ch[1][1]==ch[2][0]?ch[0][2]-'A':ch[1][1]='A')]=1;
```
看到代码的长度后不要慌，让我一步一步的解说这段代码。

第一步，是设定数组：

 `cow1` 是单独的奶牛是否赢过的标记数组，`cow2` 则是组队的奶牛是否赢过的标记数组。

第二步，你要知道 `问号表达式`。

`问号表达式`的作用就是替代 `if/else`：

```cpp
a==b ? a : b
``` 
同等于
```cpp
if(a==b) 
    return a; 
else 
    return b;
```

知道了 `问号表达式` 后，看看这段：

```cpp
!cow2[ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')]
```
这是一个组队的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/deqm6zop.png)

如果其中有两个字符相同，要求多的字符，需要做一下逻辑推理：

若 `c0` 等于 `c1`，那么肯定就是 `c0` 和 `c1`。

若 `c0` 不等于 `c1` 的话：

若 `c1` 等于 `c2`，那么就是 `c1` 和 `c2`。

否则就是 `c0` 等于 `c2`。

同样，要求少的字符，也需要做一下推理：

若 `c0` 等于 `c1`，那么肯定就是 `c2`。

若 `c0` 不等于 `c1` 的话：

若 `c1` 等于 `c2`，那么就是 `c0`。

否则就是 `c0` 等于 `c2`，那就是 `c1`。

这就是`cow2[ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')]`的情况。

如果要返回 `true` 值，那么就要把这个算式的结果取反。

这就是 `!cow2[ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')]` 。

但这种做法有可能会出现以下情况：

`cow2['A'(-'A')]['B'(-'A')]=1,cow2['B'(-'A')]['A'(-'A')]=1`

使得一次算成了两次。

所以就要：

```cpp
(!cow2[ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')]&&!cow2[ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')][ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')])
```
看起来很复杂，实际上就是 `!cow2[a][b]&&!cow[b][a]`。

所以代码就出来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool cow1[26],cow2[26][26];
int cnt1=0,cnt2=0;
char ch[3][3]; 
int main(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%c",&ch[i][j]);
        }
        getchar();
    }
    //判断单独的奶牛
    //判断第一行
    if(ch[0][0]==ch[0][1]&&ch[0][1]==ch[0][2]&&!cow1[ch[0][0]-'A']) cnt1++,cow1[ch[0][0]-'A']=1;
    //判断第二行
    if(ch[1][0]==ch[1][1]&&ch[1][1]==ch[1][2]&&!cow1[ch[1][0]-'A']) cnt1++,cow1[ch[1][0]-'A']=1;
    //判断第三行
    if(ch[2][0]==ch[2][1]&&ch[2][1]==ch[2][2]&&!cow1[ch[2][0]-'A']) cnt1++,cow1[ch[2][0]-'A']=1;
    //判断第一列
    if(ch[0][0]==ch[1][0]&&ch[1][0]==ch[2][0]&&!cow1[ch[0][0]-'A']) cnt1++,cow1[ch[0][0]-'A']=1;
    //判断第二列
    if(ch[0][1]==ch[1][1]&&ch[1][1]==ch[2][1]&&!cow1[ch[0][1]-'A']) cnt1++,cow1[ch[0][1]-'A']=1;
    //判断第三列
    if(ch[0][2]==ch[1][2]&&ch[1][2]==ch[2][2]&&!cow1[ch[0][2]-'A']) cnt1++,cow1[ch[0][2]-'A']=1;
    //判断2条对角线
	if(ch[0][0]==ch[1][1]&&ch[1][1]==ch[2][2]&&!cow1[ch[0][0]-'A']) cnt1++,cow1[ch[0][0]-'A']=1;
	if(ch[0][2]==ch[1][1]&&ch[1][1]==ch[2][0]&&!cow1[ch[0][2]-'A']) cnt1++,cow1[ch[0][2]-'A']=1;
	//判断组队的奶牛 
	//判断第一行
    if((ch[0][0]==ch[0][1]||ch[0][1]==ch[0][2]||ch[0][0]==ch[0][2])&&!(ch[0][0]==ch[0][1]&&ch[0][1]==ch[0][2])&&(!cow2[ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')]&&!cow2[ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')][ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')])) cnt2++,cow2[ch[0][0]==ch[0][1]?ch[0][0]-'A':(ch[0][1]==ch[0][2]?ch[0][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[0][1]?ch[0][2]-'A':(ch[0][1]==ch[0][2]?ch[0][0]-'A':ch[0][1]-'A')]=1;
	//判断第二行
    if((ch[1][0]==ch[1][1]||ch[1][1]==ch[1][2]||ch[1][0]==ch[1][2])&&!(ch[1][0]==ch[1][1]&&ch[1][1]==ch[1][2])&&(!cow2[ch[1][0]==ch[1][1]?ch[1][0]-'A':(ch[1][1]==ch[1][2]?ch[1][1]-'A':ch[1][0]-'A')][ch[1][0]==ch[1][1]?ch[1][2]-'A':(ch[1][1]==ch[1][2]?ch[1][0]-'A':ch[1][1]-'A')]&&!cow2[ch[1][0]==ch[1][1]?ch[1][2]-'A':(ch[1][1]==ch[1][2]?ch[1][0]-'A':ch[1][1]-'A')][ch[1][0]==ch[1][1]?ch[1][0]-'A':(ch[1][1]==ch[1][2]?ch[1][1]-'A':ch[1][0]-'A')])) cnt2++,cow2[ch[1][0]==ch[1][1]?ch[1][0]-'A':(ch[1][1]==ch[1][2]?ch[1][1]-'A':ch[1][0]-'A')][ch[1][0]==ch[1][1]?ch[1][2]-'A':(ch[1][1]==ch[1][2]?ch[1][0]-'A':ch[1][1]-'A')]=1;
	//判断第三行
    if((ch[2][0]==ch[2][1]||ch[2][1]==ch[2][2]||ch[2][0]==ch[2][2])&&!(ch[2][0]==ch[2][1]&&ch[2][1]==ch[2][2])&&(!cow2[ch[2][0]==ch[2][1]?ch[2][0]-'A':(ch[2][1]==ch[2][2]?ch[2][1]-'A':ch[2][0]-'A')][ch[2][0]==ch[2][1]?ch[2][2]-'A':(ch[2][1]==ch[2][2]?ch[2][0]-'A':ch[2][1]-'A')]&&!cow2[ch[2][0]==ch[2][1]?ch[2][2]-'A':(ch[2][1]==ch[2][2]?ch[2][0]-'A':ch[2][1]-'A')][ch[2][0]==ch[2][1]?ch[2][0]-'A':(ch[2][1]==ch[2][2]?ch[2][1]-'A':ch[2][0]-'A')])) cnt2++,cow2[ch[2][0]==ch[2][1]?ch[2][0]-'A':(ch[2][1]==ch[2][2]?ch[2][1]-'A':ch[2][0]-'A')][ch[2][0]==ch[2][1]?ch[2][2]-'A':(ch[2][1]==ch[2][2]?ch[2][0]-'A':ch[2][1]-'A')]=1;
	//判断第一列
    if((ch[0][0]==ch[1][0]||ch[1][0]==ch[2][0]||ch[0][0]==ch[2][0])&&!(ch[0][0]==ch[1][0]&&ch[1][0]==ch[2][0])&&(!cow2[ch[0][0]==ch[1][0]?ch[0][0]-'A':(ch[1][0]==ch[2][0]?ch[1][0]-'A':ch[0][0]-'A')][ch[0][0]==ch[1][0]?ch[2][0]-'A':(ch[1][0]==ch[2][0]?ch[0][0]-'A':ch[1][0]-'A')]&&!cow2[ch[0][0]==ch[1][0]?ch[2][0]-'A':(ch[1][0]==ch[2][0]?ch[0][0]-'A':ch[1][0]-'A')][ch[0][0]==ch[1][0]?ch[0][0]-'A':(ch[1][0]==ch[2][0]?ch[1][0]-'A':ch[0][0]-'A')])) cnt2++,cow2[ch[0][0]==ch[1][0]?ch[0][0]-'A':(ch[1][0]==ch[2][0]?ch[1][0]-'A':ch[0][0]-'A')][ch[0][0]==ch[1][0]?ch[2][0]-'A':(ch[1][0]==ch[2][0]?ch[0][0]-'A':ch[1][0]-'A')]=1;
	//判断第二列
    if((ch[0][1]==ch[1][1]||ch[1][1]==ch[2][1]||ch[0][1]==ch[2][1])&&!(ch[0][1]==ch[1][1]&&ch[1][1]==ch[2][1])&&(!cow2[ch[0][1]==ch[1][1]?ch[0][1]-'A':(ch[1][1]==ch[2][1]?ch[1][1]-'A':ch[0][1]-'A')][ch[0][1]==ch[1][1]?ch[2][1]-'A':(ch[1][1]==ch[2][1]?ch[0][1]-'A':ch[1][1]-'A')]&&!cow2[ch[0][1]==ch[1][1]?ch[2][1]-'A':(ch[1][1]==ch[2][1]?ch[0][1]-'A':ch[1][1]-'A')][ch[0][1]==ch[1][1]?ch[0][1]-'A':(ch[1][1]==ch[2][1]?ch[1][1]-'A':ch[0][1]-'A')])) cnt2++,cow2[ch[0][1]==ch[1][1]?ch[0][1]-'A':(ch[1][1]==ch[2][1]?ch[1][1]-'A':ch[0][1]-'A')][ch[0][1]==ch[1][1]?ch[2][1]-'A':(ch[1][1]==ch[2][1]?ch[0][1]-'A':ch[1][1]-'A')]=1;
	//判断第三列
    if((ch[0][2]==ch[1][2]||ch[1][2]==ch[2][2]||ch[0][2]==ch[2][2])&&!(ch[0][2]==ch[1][2]&&ch[1][2]==ch[2][2])&&(!cow2[ch[0][2]==ch[1][2]?ch[0][2]-'A':(ch[1][2]==ch[2][2]?ch[1][2]-'A':ch[0][2]-'A')][ch[0][2]==ch[1][2]?ch[2][2]-'A':(ch[1][2]==ch[2][2]?ch[0][2]-'A':ch[1][2]-'A')]&&!cow2[ch[0][2]==ch[1][2]?ch[2][2]-'A':(ch[1][2]==ch[2][2]?ch[0][2]-'A':ch[1][2]-'A')][ch[0][2]==ch[1][2]?ch[0][2]-'A':(ch[1][2]==ch[2][2]?ch[1][2]-'A':ch[0][2]-'A')])) cnt2++,cow2[ch[0][2]==ch[1][2]?ch[0][2]-'A':(ch[1][2]==ch[2][2]?ch[1][2]-'A':ch[0][2]-'A')][ch[0][2]==ch[1][2]?ch[2][2]-'A':(ch[1][2]==ch[2][2]?ch[0][2]-'A':ch[1][2]-'A')]=1;
	//判断2条对角线
    if((ch[0][0]==ch[1][1]||ch[1][1]==ch[2][2]||ch[0][0]==ch[2][2])&&!(ch[0][0]==ch[1][1]&&ch[1][1]==ch[2][2])&&(!cow2[ch[0][0]==ch[1][1]?ch[0][0]-'A':(ch[1][1]==ch[2][2]?ch[1][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[1][1]?ch[2][2]-'A':(ch[1][1]==ch[2][2]?ch[0][0]-'A':ch[1][1]-'A')]&&!cow2[ch[0][0]==ch[1][1]?ch[2][2]-'A':(ch[1][1]==ch[2][2]?ch[0][0]-'A':ch[1][1]-'A')][ch[0][0]==ch[1][1]?ch[0][0]-'A':(ch[1][1]==ch[2][2]?ch[1][1]-'A':ch[0][0]-'A')])) cnt2++,cow2[ch[0][0]==ch[1][1]?ch[0][0]-'A':(ch[1][1]==ch[2][2]?ch[1][1]-'A':ch[0][0]-'A')][ch[0][0]==ch[1][1]?ch[2][2]-'A':(ch[1][1]==ch[2][2]?ch[0][0]-'A':ch[1][1]-'A')]=1;
	if((ch[0][2]==ch[1][1]||ch[1][1]==ch[2][0]||ch[0][2]==ch[2][0])&&!(ch[0][2]==ch[1][1]&&ch[1][1]==ch[2][0])&&(!cow2[ch[0][2]==ch[1][1]?ch[0][2]-'A':(ch[1][1]==ch[2][0]?ch[1][1]-'A':ch[0][2]-'A')][ch[0][2]==ch[1][1]?ch[2][0]-'A':(ch[1][1]==ch[2][0]?ch[0][2]-'A':ch[1][1]-'A')]&&!cow2[ch[0][2]==ch[1][1]?ch[2][0]-'A':(ch[1][1]==ch[2][0]?ch[0][2]-'A':ch[1][1]-'A')][ch[0][2]==ch[1][1]?ch[0][2]-'A':(ch[1][1]==ch[2][0]?ch[1][1]-'A':ch[0][2]-'A')])) cnt2++,cow2[ch[0][2]==ch[1][1]?ch[0][2]-'A':(ch[1][1]==ch[2][0]?ch[1][1]-'A':ch[0][2]-'A')][ch[0][2]==ch[1][1]?ch[2][0]-'A':(ch[1][1]==ch[2][0]?ch[0][2]-'A':ch[1][1]='A')]=1;
	printf("%d\n%d",cnt1,cnt2);
	return 0;
}
```

~~合着一道大模拟~~

---

## 作者：Vct14 (赞：3)

下文中字母相等即指相同。

因为题目中的棋盘是 $3\times3$ 的，因此暴力枚举即可。

本题的重点就是给定三个字母，如何判断有没有奶牛或队伍可以通过这三个字母取胜。

判断奶牛能否取胜较为简单，只需判断三个字母是否都相等即可。

如果某支队伍能取胜，那么这三个字母中一定有且仅有两种字母，而且必定是一种字母有两个，另一种字母只有一个。那么反过来，只要有一种字母在这三个字母中出现了（且仅出现了）两次，即三个字符中有且仅有两个相等，那么就有一支队伍可以获胜。

但是如果一只奶牛或是一支队伍赢了多次就会重复算，因此用两个布尔类型的数组存储即可。

因为有很多相似的操作（比如查询有没有牛是否可以通过某一行取胜），因此可以写函数简化。

```c++
#include<bits/stdc++.h>
using namespace std;

char C[5][5];
bool y[26],l[26][26];

void chk(char a,char b,char c){
	if(a==b){
		if(a==c) y[a-'A']=true; // a=b=c，奶牛胜 
		else l[a-'A'][c-'A']=true; // 仅 a=b，a,c（b,c）队伍胜 
		return ;
	}
	if(a==c || b==c) l[a-'A'][b-'A']=true; // 仅 a=c 或仅 b=c，a,b 队伍胜 
}

void ch(int i){chk(C[i][0],C[i][1],C[i][2]);} // 行 
void cl(int j){chk(C[0][j],C[1][j],C[2][j]);} // 列 

int main(){
	for(int i=0; i<3; i++) for(int j=0; j<3; j++) cin>>C[i][j];
	for(int i=0; i<3; i++) ch(i),cl(i);
	chk(C[0][0],C[1][1],C[2][2]);chk(C[0][2],C[1][1],C[2][0]); // 对角线 
	int sum1=0,sum2=0;
	for(int i=0; i<26; i++){
		if(y[i]) sum1++;
		for(int j=0; j<i; j++) if(l[i][j] || l[j][i]) sum2++;
	} 
	cout<<sum1<<"\n"<<sum2;
	return 0;
}
```

下面的是无注释版，也是目前的最短解。

```c++
#include<bits/stdc++.h>
using namespace std;

char C[5][5];
bool y[26],l[26][26];

void chk(char a,char b,char c){
	if(a==b){
		if(a==c) y[a-'A']=true;
		else l[a-'A'][c-'A']=true;
		return ;
	}
	if(a==c || b==c) l[a-'A'][b-'A']=true;
}

void ch(int i){chk(C[i][0],C[i][1],C[i][2]);}
void cl(int j){chk(C[0][j],C[1][j],C[2][j]);}

int main(){
	for(int i=0; i<3; i++) for(int j=0; j<3; j++) cin>>C[i][j];
	for(int i=0; i<3; i++) ch(i),cl(i);
	chk(C[0][0],C[1][1],C[2][2]);chk(C[0][2],C[1][1],C[2][0]);
	int sum1=0,sum2=0;
	for(int i=0; i<26; i++){
		if(y[i]) sum1++;
		for(int j=0; j<i; j++) if(l[i][j] || l[j][i]) sum2++;
	} 
	cout<<sum1<<"\n"<<sum2;
	return 0;
}
```

---

## 作者：maomao233 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P10122)

竟然是某 OJ 的月赛原题，~~震惊了。~~

注意到棋盘为 $3\times3$，所以可以暴力地枚举。

于是我们分类计算。  
第一类，我们计算每行、每列和每个对角线的字符种类。若种类为 $\textbf{1}$，则第一类的答案加一。  
第二类，我们计算每行、每列和每个对角线的字符种类。若种类为 $\textbf{2}$，则第二类的答案加一。

最后输出即可。有代码：  
~~看似代码很长，其实都是一段一段复制的。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
#define lb(x) x&-x
#define itn int
inline string its(int x){stringstream ss;string s;ss<<x;ss>>s;return s;}
inline int sti(string s){stringstream ss;int x;ss<<s;ss>>x;return x;}
inline string jia(string a1,string b1){int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=max(lena,lenb),t=0;for(int i=0;i<lenc;i++){c[i]=a[i]+b[i]+t;if(c[i]>=10){t=1,c[i]%=10;}else{t=0;}}if(t==1){lenc++;c[lenc-1]=1;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline string jian(string a1,string b1){if(a1.size()<b1.size()||a1.size()==b1.size()&&a1<b1){pc('-'),swap(a1,b1);}int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=lena;for(int i=0;i<lenc;i++){if(a[i]<b[i]){a[i+1]--,a[i]+=10;}c[i]=a[i]-b[i];}while(lenc>=1&&c[lenc-1]==0){lenc--;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline int qpow(int a,int b,int p){int ans=1;while(b){if(b&1){ans=(ans*a)%p;}b>>=1;a=(a*a)%p;}return ans;}
inline int qp(int a,int b){int ans=1;while(b){if(b&1){ans*=a;}b>>=1;a*=a;}return ans;}
char a[10][10];
bool b[200];
map<char,bool>x;
map<char,bool>y[200];
signed main()
{
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			cin>>a[i][j];
		}
	}
	int ans1=0;
	for(int i=1;i<=3;i++)
	{
		memset(b,0,sizeof(b));
		int cnt=0;
		for(int j=1;j<=3;j++)
		{
			if(!b[a[i][j]])
			{
				b[a[i][j]]=1,cnt++;
			}
		}
		if(cnt==1&&!x[a[i][1]])
		{
			ans1++,x[a[i][1]]=1;
		}
	}
	for(int j=1;j<=3;j++)
	{
		memset(b,0,sizeof(b));
		int cnt=0;
		for(int i=1;i<=3;i++)
		{
			if(!b[a[i][j]])
			{
				b[a[i][j]]=1,cnt++;
			}
		}
		if(cnt==1&&!x[a[1][j]])
		{
			ans1++,x[a[1][j]]=1;
		}
	}
	memset(b,0,sizeof(b));
	int cnt=0;
	for(int i=1;i<=3;i++)
	{
		if(!b[a[i][i]])
		{
			b[a[i][i]]=1,cnt++;
		}
	}
	if(cnt==1&&!x[a[1][1]])
	{
		ans1++,x[a[1][1]]=1;
	}
	memset(b,0,sizeof(b));
	cnt=0;
	for(int i=1;i<=3;i++)
	{
		if(!b[a[i][3-i+1]])
		{
			b[a[i][3-i+1]]=1,cnt++;
		}
	}
	if(cnt==1&&!x[a[1][3]])
	{
		ans1++,x[a[1][3]]=1;
	}
	int ans2=0;
	for(int i=1;i<=3;i++)
	{
		memset(b,0,sizeof(b));
		int cnt=0;
		for(int j=1;j<=3;j++)
		{
			if(!b[a[i][j]])
			{
				b[a[i][j]]=1,cnt++;
			}
		}
		if(cnt==2&&!y[min(a[i][1],min(a[i][2],a[i][3]))][max(a[i][1],max(a[i][2],a[i][3]))])
		{
			ans2++,y[min(a[i][1],min(a[i][2],a[i][3]))][max(a[i][1],max(a[i][2],a[i][3]))]=1;
		}
	}
	for(int j=1;j<=3;j++)
	{
		memset(b,0,sizeof(b));
		int cnt=0;
		for(int i=1;i<=3;i++)
		{
			if(!b[a[i][j]])
			{
				b[a[i][j]]=1,cnt++;
			}
		}
		if(cnt==2&&!y[min(a[1][j],min(a[2][j],a[3][j]))][max(a[1][j],max(a[2][j],a[3][j]))])
		{
			ans2++,y[min(a[1][j],min(a[2][j],a[3][j]))][max(a[1][j],max(a[2][j],a[3][j]))]=1;
		}
	}
	memset(b,0,sizeof(b));
	cnt=0;
	for(int i=1;i<=3;i++)
	{
		if(!b[a[i][i]])
		{
			b[a[i][i]]=1,cnt++;
		}
	}
	if(cnt==2&&!y[min(a[1][1],min(a[2][2],a[3][3]))][max(a[1][1],max(a[2][2],a[3][3]))])
	{
		ans2++,y[min(a[1][1],min(a[2][2],a[3][3]))][max(a[1][1],max(a[2][2],a[3][3]))]=1;
	}
	memset(b,0,sizeof(b));
	cnt=0;
	for(int i=1;i<=3;i++)
	{
		if(!b[a[i][3-i+1]])
		{
			b[a[i][3-i+1]]=1,cnt++;
		}
	}
	if(cnt==2&&!y[min(a[1][3],min(a[2][2],a[3][1]))][max(a[1][3],max(a[2][2],a[3][1]))])
	{
		ans2++,y[min(a[1][3],min(a[2][2],a[3][1]))][max(a[1][3],max(a[2][2],a[3][1]))]=1;
	}
	wtl(ans1),wtl(ans2);
	return 0;
}
```

好的大型枚举。

---

## 作者：Drest (赞：2)

## P10122 [USACO18OPEN] Team Tic Tac Toe B

[传送门](https://www.luogu.com.cn/problem/P10122)

[【广告】蒟蒻的blog](https://www.luogu.com.cn/blog/drest/)

## 本题思路

1. 对于一只奶牛可以**自己单独获胜的情况**，可以判断整行/整列/斜边**三个字符是否相等**。
2. 对于两只奶牛**共同获胜的情况**，可以通过判断整行/整列/斜边**三个字符是否有两个相等**。

注意：在判断过程中可能会出现某个奶牛即在第一行能单独获胜，也在第二行能单独获胜的情况，所以**需要进行标记以防重复**。

可以使用 `map<pair<int,int>,bool>` 进行标记，其中 `pair<int,int>` 是指某一个奶牛单独获胜（**pair 中两个元素相同**）或某两个奶牛共同获胜（**注意两个奶牛的顺序**，可以采用升序或降序）。

由于常数很小，所以**时间复杂度**可以近似看为 $O(1)$。

附上 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
// 存每一位的字母 
char a, b, c;
char d, e, f;
char g, h, i;
int ans1, ans2;
map<pair<int,int>,bool> teamt; // 用于判重 
pair<int,int> get(char x, char y, char z) {  // 这个函数用于判断三个数中哪两个数相等，并返回一个pair 
	// 记得pair中元素排个序
	if (x == y) return make_pair(min(x - 'A', z - 'A'), max(x - 'A', z - 'A'));
	if (x == z) return make_pair(min(x - 'A', y - 'A'), max(x - 'A', y - 'A'));
	if (y == z) return make_pair(min(x - 'A', y - 'A'), max(x - 'A', y - 'A'));
	return make_pair(min(x - 'A', y - 'A'), max(x - 'A', y - 'A'));
}
int main()
{
	cin >> a >> b >> c >> d >> e >> f >> g >> h >> i;
	// 第一行  
	if (a == b && b == c && !teamt[{a - 'A', a - 'A'}]) ans1++, teamt[{a - 'A', a - 'A'}]=true; //自己获胜 
	else if((a == b || b == c || a == c) && !teamt[get(a,b,c)]) ans2++, teamt[get(a,b,c)]=true; //团队获胜 
	// 第二行 
	if (d == e && e == f && !teamt[{d - 'A', d - 'A'}]) ans1++, teamt[{d - 'A', d - 'A'}]=true;
	else if((d == e || e == f || d == f) && !teamt[get(d,e,f)]) ans2++, teamt[get(d,e,f)]=true;
	// 第三行 
	if (g == h && h == i && !teamt[{g - 'A', g - 'A'}]) ans1++, teamt[{g - 'A', g - 'A'}]=true;
	else if((g == h || h == i || g == i) && !teamt[get(g,h,i)]) ans2++, teamt[get(g,h,i)]=true;
	// 第一列 
	if (a == d && d == g && !teamt[{a - 'A', a - 'A'}]) ans1++, teamt[{a - 'A', a - 'A'}]=true;
	else if((a == d || d == g || a == g) && !teamt[get(a,d,g)]) ans2++, teamt[get(a,d,g)]=true;
	// 第二列 
	if (b == e && e == h && !teamt[{b - 'A', b - 'A'}]) ans1++, teamt[{b - 'A', b - 'A'}]=true;
	else if((b == e || e == h || b == h) && !teamt[get(b,e,h)]) ans2++, teamt[get(b,e,h)]=true;
	// 第三列 
	if (c == f && f == i && !teamt[{c - 'A', c - 'A'}]) ans1++, teamt[{c - 'A', c - 'A'}]=true;
	else if((c == f || f == i || c == i) && !teamt[get(c,f,i)]) ans2++, teamt[get(c,f,i)]=true;
	// 左上-右下斜边 
	if (a == e && e == i && !teamt[{a - 'A', a - 'A'}]) ans1++, teamt[{a - 'A', a - 'A'}]=true;
	else if((a == e || e == i || a == i) && !teamt[get(a,e,i)]) ans2++, teamt[get(a,e,i)]=true;
	// 右上-左下斜边 
	if (c == e && e == g && !teamt[{c - 'A', c - 'A'}]) ans1++, teamt[{c - 'A', c - 'A'}]=true;
	else if((c == e || e == g || c == g) && !teamt[get(c,e,g)]) ans2++, teamt[get(c,e,g)]=true;
	// 输出答案
	cout << ans1 << endl << ans2;
	return 0;
}

```

---

## 作者：we_are_the_chuibing (赞：2)

直接一遍过，上位红至下位橙。

### 思路

数据范围较小，直接暴力枚举三列，三行，还有两个对角线。

先上一份错误代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
   char ch[10];
	for(int i=1;i<=9;i++)cin>>ch[i];
	int x=0,y=0;
	if(ch[1]==ch[2]&&ch[2]==ch[3])x++;
	if(ch[4]==ch[5]&&ch[5]==ch[6])x++;
	if(ch[7]==ch[8]&&ch[8]==ch[9])x++;
	if(ch[1]==ch[4]&&ch[4]==ch[7])x++;
	if(ch[2]==ch[5]&&ch[5]==ch[8])x++;
	if(ch[3]==ch[6]&&ch[6]==ch[9])x++;
	if(ch[1]==ch[5]&&ch[5]==ch[9])x++;
	if(ch[3]==ch[5]&&ch[5]==ch[7])x++;
   if(ch[1]==ch[2]||ch[1]==ch[3]||ch[2]==ch[3])y++;
   if(ch[4]==ch[5]||ch[4]==ch[6]||ch[5]==ch[6])y++;
   if(ch[7]==ch[8]||ch[7]==ch[9]||ch[9]==ch[8])y++;
   if(ch[1]==ch[4]||ch[1]==ch[7]||ch[7]==ch[4])y++;
   if(ch[2]==ch[5]||ch[2]==ch[8]||ch[8]==ch[5])y++;
   if(ch[6]==ch[9]||ch[6]==ch[3]||ch[9]==ch[3])y++;
   if(ch[1]==ch[5]||ch[1]==ch[9]||ch[9]==ch[5])y++;
   if(ch[5]==ch[7]||ch[5]==ch[3]||ch[7]==ch[3])y++;
   cout<<x<<endl<<y;
	return 0;
}
```

错误点：两个线上的奶牛相同，会把他们认为是两种方案。

由于字母只有 $26$ 个，可以直接开数组来存储哪些奶牛可以获胜。

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[10];
int a[27],b[27][27],ans1,ans2;
void f(int x,int y,int z){
	if(c[x]==c[y]&&c[y]==c[z]){
		a[c[x]-64]=1;
		return;
	}
	if(c[x]==c[y]){
		int mn=min(c[x],c[z])-64;
		int mx=max(c[x],c[z])-64;
		b[mn][mx]=1;
		return;
	}if(c[z]==c[y]){
		int mn=min(c[x],c[z])-64;
		int mx=max(c[x],c[z])-64;
		b[mn][mx]=1;
		return;
	}if(c[x]==c[z]){
		int mn=min(c[y],c[z])-64;
		int mx=max(c[y],c[z])-64;
		b[mn][mx]=1;
		return;
	}
}
int main(){
	for(int i=1;i<=9;i++)cin>>c[i];
	f(1,2,3);
	f(4,5,6);
	f(7,8,9);
	f(1,4,7);
	f(2,5,8);
	f(3,6,9);
	f(1,5,9);
	f(3,5,7);
	for(int i=1;i<=26;i++)ans1+=a[i];
	for(int i=1;i<=26;i++){
		for(int j=1;j<=26;j++){
			ans2+=b[i][j];
		}
	}
	cout<<ans1<<endl<<ans2;
	return 0;
}
```


---

## 作者：DFM_O (赞：1)

## [P10122 题目](https://www.luogu.com.cn/problem/P10122)

### 解题思路
我们可以枚举每一行、每一列和两条对角线并判断是否满足题目条件，但是别忘了也许会出现某一个奶牛或某一个队伍类似于既能通过第一行获胜，也能通过第一列获胜的情况（即能通过两条路线获胜），我们需要用数组标记，以保证不会重复计算。

### Code
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
#define int long long
int pd[27][27],a[4][4],pd2[27],b[4];
signed main()
{
	ios::sync_with_stdio(false);
	int s1=0,s2=0;
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			char ch;
			cin>>ch;
			a[i][j]=ch-'A'+1;
		}
	}
	for(int i=1;i<=3;i++)
	{
		if(a[i][1]==a[i][2]&&a[i][2]==a[i][3])//行
		{
			if(pd2[a[i][1]]==0)
				s1++;
			pd2[a[i][1]]=1;
		}
		else
		{
			if(a[i][1]==a[i][2]||a[i][2]==a[i][3]||a[i][1]==a[i][3])
			{
				b[1]=a[i][1],b[2]=a[i][2],b[3]=a[i][3];
				sort(b+1,b+4);
				if(pd[b[1]][b[3]]==0)
					s2++,pd[b[1]][b[3]]=1;
			}
		}
		if(a[1][i]==a[2][i]&&a[2][i]==a[3][i])//列
		{
			if(pd2[a[1][i]]==0)
				s1++;
			pd2[a[1][i]]=1;
		}
		else
		{
			if(a[1][i]==a[2][i]||a[1][i]==a[3][i]||a[2][i]==a[3][i])
			{
				b[1]=a[1][i],b[2]=a[2][i],b[3]=a[3][i];
				sort(b+1,b+4);
				if(pd[b[1]][b[3]]==0)
					s2++,pd[b[1]][b[3]]=1;
			}
		}
	}
	if(a[1][1]==a[2][2]&&a[2][2]==a[3][3])//两条对角线
	{
		if(pd2[a[1][1]]==0)
			s1++;
		pd2[a[1][1]]=1;
	}
	else
	{
		if(a[1][1]==a[2][2]||a[2][2]==a[3][3]||a[1][1]==a[3][3])
		{
			b[1]=a[1][1],b[2]=a[2][2],b[3]=a[3][3];
			sort(b+1,b+4);
			if(pd[b[1]][b[3]]==0)
				s2++,pd[b[1]][b[3]]=1;
		}
	}
	if(a[1][3]==a[2][2]&&a[2][2]==a[3][1])
	{
		if(pd2[a[1][3]]==0)
			s1++;
		pd2[a[1][3]]=1;
	}
	else
	{
		if(a[1][3]==a[2][2]||a[2][2]==a[3][1]||a[1][3]==a[3][1])
		{
			b[1]=a[3][1],b[2]=a[2][2],b[3]=a[1][3];
			sort(b+1,b+4);
			if(pd[b[1]][b[3]]==0)
				s2++,pd[b[1]][b[3]]=1;
		}
	}
	cout<<s1<<"\n"<<s2;//输出
    return 0;
}
```

---

## 作者：Ericnoi (赞：1)

### UpDate 2024.2.10
[更好的阅读体验](https://www.luogu.com.cn/blog/Ericcsps/solution-p10122)

[题目传送门](https://www.luogu.com.cn/problem/P10122)
## 题意简述
给定 $3$ * $3$ 字符九宫格，求：
- 只有 $1$ 种字符的行/列/对角线的字符种类数
- 有 $2$ 种字符的行/列/对角线的两种字符组合数
## 解题思路 && 常见误区
显然，本题应该使用枚举 && 模拟的思想，枚举出每一列，每一行，以及两条对角线的情况，并依次统计答案。


但是，这题真的有这么简单吗？


~~当然不是~~（其实这题也比较简单），原因就在于对题意的理解可能有误。
**题目要求的是获胜奶牛/队伍数**。如果还不是很清楚，
来看一组数据，思考以下问题：

|  | $1$ | $2$ | $3$ |
| -----------: | -----------: | -----------: | -----------: |
| $1$ | A | B | A |
| $2$ | A | A | A |
| $3$ | B | B | A |


- 奶牛 A 在第 $2$ 行与 第 $3$ 列**获胜两次**，这能算是**两头奶牛获胜**吗？
- 组合 AB 在行$1$、$3$，列 $1$、$2$ **获胜四次**，这算是**四个组合获胜**吗？

所以，解题的关键在于**去重**。第 $2$ 行与 第 $3$ 列 ，行 $1$、$3$ 与列$1$、$2$ 应算作**一种情况**。

有了这个思路，写出代码就很容易了。

## 代码实现

提到去重，很容易想到可以用 **set** 。

找到一种情况，插入对应的集合，集合的 size 即为所求。

Talk is cheap, show me the code.
## AC Code
代码已做防抄袭处理，防君子不防小人。注重学术诚信，共创和谐洛谷。
```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;
char a[5][5];	// 九宫格，下标 1~3
set<char> ans1;	// 第一个集合
set< pair<char, char> > ans2;	// 第二个集合，尖括号间要用空格隔开，否则会被识别为 >>
void judge(char c1, char c2, char c3) {		// 将情况插入集合，复杂度近似 O(1)
    set<char> s;
    s.insert(c1);
    s.insert(c2);
    s.insert(c3);
    if(s.size() == 1) {
        ans1.insert(c1);
    }
    if(s.size() == 2) {
        vector<char> v;		// STL 大法好
        for(auto i : s) {	// C++11新型for循环，类似python
            v.push_back(i);	// 将集合中的元素转移到 vector 中
        }
        ans2.insert(make_pair(v[0], v[1]));
        // 热知识：遍历set得到的元素是有序的，因此不用担心排序问题
    }
    return s.size();
}
int main() {
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    for(int i = 1 ; i <= 3 ; i++) {
        cin >> (a[i] + 1);	// 字符矩阵输入懒人小技巧：看作字符串
    }
    for(int i = 1 ; i <= 3 ; i++) {		// 一次循环解决
        jugde(a[i][1], a[i][2], a[i][3]);	// i 行
        jugde(a[1][i], a[2][i], a[3][i]);	// i 列
    }
    judge(a[1][1], a[2][2], a[3][3]);	// 两条对角线
    judge(a[1][3], a[2][2], a[3][1]);	
    cout << ans1.size() << endl << ans2.size() << endl;	// 输出答案
    return 0;	// 功德圆满
}
```
祝大家 ```rp++```，功不唐捐;

---

## 作者：Mason123456 (赞：1)

# [P10122](https://www.luogu.com.cn/problem/P10122)

## 思路

由于这题只有 $3 \times 3$，所以直接 8 个 if 判断。若有一行或列或斜对角有一个字母，`ans1 + 1`，若有两个字母，`ans2 + 1`。

需要注意，本题不接受重复的获胜条件。感谢 @2021zjhs005 提供的 `HACK` 样例。

```
INPUT

ABA
BAB
ABA

OUTPUT

1
1
```

我们需要开一个 `map`。`mp1[i]` 表示对于单个牛 $i$ 的胜利已经被标记。`mp2[i][j]` 表示 $i$ 和 $j$ 已经是一个队伍。

## CODE [#](https://www.luogu.com.cn/record/146602145)

```cpp
#include <iostream>
#include <map>
using namespace std;
char a[10];
int ans1, ans2;
map<char, bool> mp1;
bool mp2[30][30];
void f(int x, int y, int z){
    int cnt;
    char r1, r2;
    map<char, int> mp;
    mp.clear();
    cnt = 0;

    mp[a[x]] = 1;
    r1 = a[x];
    cnt ++;
    if(!mp[a[y]]){
        mp[a[y]] = 1;
        if(cnt == 1 && r1 != a[y])    r2 = a[y];
        cnt ++;
    }
    if(!mp[a[z]]){
        mp[a[z]] = 1;
        if(cnt == 1 && r1 != a[z])    r2 = a[z];
        cnt++;
    }

    if(cnt == 1 && !mp1[a[x]]){
        mp1[a[x]] = true;
        ans1++;
    }
    int ir1 = r1 - 'A';
    int ir2 = r2 - 'A';
    if(cnt == 2 && !mp2[ir1][ir2] && !mp2[ir2][ir1]){
        mp2[ir1][ir2] = true;
        mp2[ir2][ir1] = true;
        ans2++;
    }
}
int main() {
    for(int i = 1;i <= 9;i ++){
        cin>>a[i];
    }

    f(1, 2, 3);
    f(4, 5, 6);
    f(7, 8, 9);
    f(1, 4, 7);
    f(2, 5, 8);
    f(3, 6, 9);
    f(1, 5, 9);
    f(3, 5, 7);

    cout<<ans1<<endl<<ans2;
    return 0;
}
```


---

## 作者：tder (赞：1)

模拟即可。

若牛 $a$ 可以独自获胜，则在同一行、同一列或同一对角线上均为 $a$，即其上只有一种字符；同理，若牛 $a$ 和 $b$ 可以组队获胜，则在同一行、同一列或同一对角线上均为 $a$ 或 $b$，即其上只有两种字符。

对于每一行，用 vector 存储，再使用 STL 中的 `unique()` 函数去重即可，此思路在[离散化](https://www.luogu.com.cn/problem/B3694)中亦可使用。具体地，对于一个 vector 类型的 $v$，调用 `k = unique(v.begin(),v.end()) - v.begin()` 即为 $v$ 中不同元素的数量。注意，调用其并不会真正改变 $v$ 的大小，只会将不同的元素移至数组前 $k$ 项，并且其只能将有序数组进行去重。

用 set 处理均可，这里不做过多介绍。

另外，注意最后答案中，组队完成的方案 $(x,y)$ 与 $(y,x)$ 相同。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3 + 5;
int n = 3;
char c[N][N];
vector<char> v1; vector<pair<char, char>> v2;
void work() {
    // 行
    for(int i = 1; i <= n; i++) {
        vector<char> s;
        for(int j = 1; j <= n; j++) s.push_back(c[i][j]);
        sort(s.begin(), s.end()); int k = unique(s.begin(), s.end()) - s.begin();
        if(k == 1) v1.push_back(s[0]);
        else if(k == 2) v2.push_back({min(s[0], s[1]), max(s[0], s[1])});
    }
    // 列
    for(int j = 1; j <= n; j++) {
        vector<char> s;
        for(int i = 1; i <= n; i++) s.push_back(c[i][j]);
        sort(s.begin(), s.end()); int k = unique(s.begin(), s.end()) - s.begin();
        if(k == 1) v1.push_back(s[0]);
        else if(k == 2) v2.push_back({min(s[0], s[1]), max(s[0], s[1])});
    }
    // 左上 - 右下对角线
    vector<char> s;
    for(int i = 1; i <= n; i++) s.push_back(c[i][i]);
    sort(s.begin(), s.end()); int k = unique(s.begin(), s.end()) - s.begin();
    if(k == 1) v1.push_back(s[0]);
    else if(k == 2) v2.push_back({min(s[0], s[1]), max(s[0], s[1])});
    // 右上 - 左下对角线
    s.clear();
    for(int i = 1; i <= n; i++) s.push_back(c[i][n - i + 1]);
    sort(s.begin(), s.end()); k = unique(s.begin(), s.end()) - s.begin();
    if(k == 1) v1.push_back(s[0]);
    else if(k == 2) v2.push_back({min(s[0], s[1]), max(s[0], s[1])});
}
signed main() {
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin>>c[i][j];
    work();
    sort(v1.begin(), v1.end()); int k1 = unique(v1.begin(), v1.end()) - v1.begin();
    sort(v2.begin(), v2.end()); int k2 = unique(v2.begin(), v2.end()) - v2.begin();
    cout<<k1<<endl<<k2<<endl;
    return 0;
}
```

---

## 作者：FallingFYC_ (赞：0)

[题目](https://www.luogu.com.cn/problem/P10122)

---
### 思路

开两个 `set` 分别记录两个答案具体的奶牛（顺便去重），最终输出大小即可。

然后枚举每条直线，记录所含的奶牛的数量，枚举，如果满足条件加进 `set` 中。注意一下两头奶牛组成的队伍的情况的细节，需要分别记录。

代码看似很长，其实只是复制而已。

---
### 代码
```cpp
#include "bits/stdc++.h"
#define mkp(a , b) make_pair(a , b)
using namespace std;
char c[4][4] , f = '@' , s = '@';
set<char> ans1;
set<pair<char , char>> ans2;
int main()
{
    for (int i = 1 ; i <= 3 ; i++)
        for (int j = 1 ; j <= 3 ; j++) cin >> c[i][j];

    //行
    for (int i = 1 ; i <= 3 ; i++)
    {
        map<char , int> mp1;
        for (int j = 1 ; j <= 3 ; j++) ++mp1[c[i][j]];
        for (auto i : mp1)
            if (i.second == 3) ans1.insert(i.first);
            else if (i.second == 2) f = i.first;
            else if (i.second == 1) s = i.first;
        if (f != '@' && s != '@') ans2.insert(mkp(max(f , s) , min(f , s)));
        f = s = '@';
    }
    //列
    for (int i = 1 ; i <= 3 ; i++)
    {
        map<char , int> mp1;
        for (int j = 1 ; j <= 3 ; j++) ++mp1[c[j][i]];
        for (auto i : mp1)
            if (i.second == 3) ans1.insert(i.first);
            else if (i.second == 2) f = i.first;
            else if (i.second == 1) s = i.first;
        if (f != '@' && s != '@') ans2.insert(mkp(max(f , s) , min(f , s)));
        f = s = '@';
    }
    //右对角
    map<char , int> mp1;
    for (int i = 1 ; i <= 3 ; i++) ++mp1[c[i][i]];
    for (auto i : mp1)
        if (i.second == 3) ans1.insert(i.first);
        else if (i.second == 2) f = i.first;
        else if (i.second == 1) s = i.first;
    if (f != '@' && s != '@') ans2.insert(mkp(max(f , s) , min(f , s)));
    f = s = '@';
    //左对角
    map<char , int> mp2;
    for (int i = 1 ; i <= 3 ; i++) ++mp2[c[i][4 - i]];
    for (auto i : mp2)
        if (i.second == 3) ans1.insert(i.first);
        else if (i.second == 2) f = i.first;
        else if (i.second == 1) s = i.first;
    if (f != '@' && s != '@') ans2.insert(mkp(max(f , s) , min(f , s)));
    f = s = '@';
    cout << ans1.size() << '\n' << ans2.size() << '\n';
    return 0;
}
```

---

## 作者：__Sky__Dream__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P10122)

## 题目大意
给定一个“井”字形的棋盘，求每行、每列、每对角线上全部相同的和 $2$ 个相同的出现的次数。

## 解题思路
其实这是一道比较简单的模拟题，只要理清情况就很好写了。

那么有以下两种情况：

1. 一只奶牛单独获胜：只要判断每行、每列、每对角线上**每个字符是否完全相同**。
1. 两只奶牛同时获胜：只要判断每行、每列、每对角线上**是否只有两个字符**即可。

具体情况参见代码注释。

## AC Code（有点抽象）：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[4][4];
int b[100][3],ans[100];
int s=0,l=0;
int cnt=0,sum=0;
int dfs(char a,char b,char c,int r,int t)//判断胜负
{
	if(a!=b&&b!=c&&a!=c)//三个字母都不相同
		return 0;
	if((a!=r&&a!=t)||(b!=r&&b!=t)||(c!=r&&c!=t))//出现非组队字母
		return 0;
	if(r==t) cnt++;//三个字母相同单独胜
	if((a!=b||b!=c||a!=c)&&r!=t) sum++;//组队胜
	return 0;//千万不要忘记加，否则只有10分
}
int main()
{
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			a[i][j]=getchar(),ans[a[i][j]]=1;
		}
		getchar();
	}
	for(int r='A';r<='Z';r++)
	{
		for(int t=r;t<='Z';t++)//t=r保证不会重复
		{
			cnt=0,sum=0;
			if(ans[r]==0||ans[t]==0)
				continue;
			for(int i=1;i<=3;i++)//枚举行
				dfs(a[i][1],a[i][2],a[i][3],r,t);
			for(int j=1;j<=3;j++)//枚举列
				dfs(a[1][j],a[2][j],a[3][j],r,t);
			dfs(a[1][1],a[2][2],a[3][3],r,t);
			dfs(a[1][3],a[2][2],a[3][1],r,t);//对角线
			if(cnt) b[r][1]++;
			if(sum) b[r][2]++;//字母r的两种胜利情况
		}
	}
	for(int k=60;k<100;k++)//A-Z即65-90
	{
		if(b[k][1]) s++;
		if(b[k][2]) l+=b[k][2];
	}
	cout<<s<<"\n"<<l;
	return 0;//好习惯
}
```
##### ~~其实这道题也不是很简单哦！~~

---

## 作者：wht_1218 (赞：0)

~~咋没有子任务~~

一道模拟题。

在这个问题中，我们有一个填满字母的井字棋棋盘。我们需要为每个单独的字母和每对字母找出是否存在**三连排**。

遍历所有的单个字母和所有的字母对。然后我们可以**枚举所有的行、列和对角线**，并检查行、列或对角线上的所有字母是否**都等于固定的字母或一组固定的字母对**。

在检查行、列或对角线上的所有字母是否都是一组固定的字母对时，我们还必须检查**不是所有的三个字母都相同**，时间复杂度极小~~分明就是不会算~~，能在短时间内运行。


### 核心部分：
```cpp
int f1(char c){
  if (B[0][0] == ch && B[1][1] == ch && B[2][2] == ch) return 1;
  if (B[0][2] == ch && B[1][1] == ch && B[2][0] == ch) return 1;
  for (int i=1; i<=3; i++) {
    if (B[0][i] == ch && B[1][i] == ch && B[2][i] == ch) return 1;
    if (B[i][0] == ch && B[i][1] == ch && B[i][2] == ch) return 1;
  }return 0; 
}bool check(char ch1, char ch2, char a, char b, char c) {
  /* 自己写 */
}//check函数是检查不是所有的三个字母都相同的
int f2(char ch1, char ch2){
  if (check(ch1,ch2,B[0][0],B[1][1],B[2][2]))return 1;
  if (check(ch1,ch2,B[0][2],B[1][1],B[2][0]))return 1;
  for (int i=1; i<=3; i++) {
    if(check(ch1, ch2, B[0][i], B[1][i], B[2][i]))return 1;
    if(check(ch1, ch2, B[i][0], B[i][1], B[i][2]))return 1;
  }
  return 0; 
}
```

~~这次的坑还不少哩~~


---

## 作者：luoguDomi (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P10122)
这道题让我们判断得分情况，看起来很复杂，其实很简单。我们可以看到题目输入的棋盘一定是个九宫格，所以我发现，只要一行，一列或一个对角线中有且只有两个字母是相等的，那么两个不同字母就可以组队得分。如果这一行，一列或一个对角线中三个字母都相等，那这个字母可以单人得分。所以我们只需要枚举每行，每列，以及每个对角线即可。

下面是代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans1,ans2;/*ans1表示单人得分，ans2表示组队得分*/
char m[5][5];
int main(){
	for(int i=1;i<=3;i++)for(int j=1;j<=3;j++)cin>>m[i][j];
	if(m[1][1]==m[1][2]||m[1][1]==m[1][3]||m[1][2]==m[1][3])if(m[1][1]!=m[1][2]||m[1][1]!=m[1][3]||m[1][2]!=m[1][3])ans2++;
	if(m[2][1]==m[2][2]||m[2][1]==m[2][3]||m[2][2]==m[2][3])if(m[2][1]!=m[2][2]||m[2][1]!=m[2][3]||m[2][2]!=m[2][3])ans2++;
	if(m[3][1]==m[3][2]||m[3][1]==m[3][3]||m[3][2]==m[3][3])if(m[3][1]!=m[3][2]||m[3][1]!=m[3][3]||m[3][2]!=m[3][3])ans2++;
	/*以上枚举的是组队在三行中的得分，每行的第二个if是用于防止把单人得分也算进组队得分*/
	if(m[1][1]==m[2][1]||m[1][1]==m[3][1]||m[2][1]==m[3][1])if(m[1][1]!=m[2][1]||m[1][1]!=m[3][1]||m[2][1]!=m[3][1])ans2++;
	if(m[1][2]==m[2][2]||m[1][2]==m[3][2]||m[2][2]==m[3][2])if(m[1][2]!=m[2][2]||m[1][2]!=m[3][2]||m[2][2]!=m[3][2])ans2++;
	if(m[1][3]==m[2][3]||m[1][3]==m[3][3]||m[2][3]==m[3][3])if(m[1][3]!=m[2][3]||m[1][3]!=m[3][3]||m[2][3]!=m[3][3])ans2++;
	/*以上枚举的是组队在三列中的得分*/
	if(m[1][1]==m[2][2]||m[1][1]==m[3][3]||m[2][2]==m[3][3])if(m[1][1]!=m[2][2]||m[1][1]!=m[3][3]||m[2][2]!=m[3][3])ans2++;
	if(m[1][3]==m[2][2]||m[1][3]==m[3][1]||m[2][2]==m[3][1])if(m[1][3]!=m[2][2]||m[1][3]!=m[3][1]||m[2][2]!=m[3][1])ans2++;
	/*以上枚举的是组队在对角线中的得分*/
	if(m[1][1]==m[1][2]&&m[1][2]==m[1][3])ans1++;
	if(m[2][1]==m[2][2]&&m[2][2]==m[2][3])ans1++;
	if(m[3][1]==m[3][2]&&m[3][2]==m[3][3])ans1++;
	/*以上枚举的是单人在三行中的得分*/
	if(m[1][1]==m[2][1]&&m[2][1]==m[3][1])ans1++;
	if(m[1][2]==m[2][2]&&m[2][2]==m[3][2])ans1++;
	if(m[1][3]==m[2][3]&&m[2][3]==m[3][3])ans1++;
	/*以上枚举的是单人在三列中的得分*/
	if(m[1][1]==m[2][2]&&m[2][2]==m[3][3])ans1++;
	if(m[1][3]==m[2][2]&&m[2][2]==m[3][1])ans1++;
   /*以上枚举的是单人在对角线中的得分*/
	cout<<ans1<<endl<<ans2;/*这道题输出别忘了换行*/
	return 0;
}
```

---

## 作者：xiaoyang111 (赞：0)

### 前言

[题目传送门。](https://www.luogu.com.cn/problem/P10122)

[可能更好的阅读体验。](https://www.luogu.com.cn/blog/xiaoyang111/p10122-ti-xie)

### 讲解

其实这题挺简单的。

我们先枚举每一行每一列和对角线，然后枚举出来这个行或列或对角线长啥样后，按照题目的意思算一下记一下答案就可以了。

怎么记答案？

其实我们拿到这三个格子是谁下的过后，可以先排一下序，让相同的靠在一起，这个时候就好判断了。如果有三个字符相同，将第一问的答案加一；如果只有两个字符相同，将第二问的答案加一。

就可以得到以下代码：

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main(){
	vector<vector<char>> c(3,vector<char>(4));
	for (int i=0;i<3;++i){
		for (int j=0;j<3;++j){
			c[i][j]=getchar();
		}
		getchar();
	} 
	int ans1=0,ans2=0;
	auto solve=[&ans1,&ans2](char a,char b,char c){//记答案 
		if (a>b) swap(a,b);
		if (a>c) swap(a,c);
		if (b>c) swap(b,c);//类似冒泡排序
		if (a==b && a==c){
			++ans1;
		}else if (a==b || b==c){
			++ans2;
		}
	};
	for (int i=0;i<3;++i){
		solve(c[i][0],c[i][1],c[i][2]);//行 
		solve(c[0][i],c[1][i],c[2][i]);//列 
	}
	solve(c[0][0],c[1][1],c[2][2]);//对角线
	solve(c[0][2],c[1][1],c[2][0]);//对角线
	cout<<ans1<<endl<<ans2<<endl; 
	return 0;
}
```

[完结。。。撒花？](https://www.luogu.com.cn/record/146160152)

怎么错了？

这里感谢一下 [这个帖子](https://www.luogu.com.cn/discuss/771680)，让我找到了错误。

题目要求的是：

> 请帮助奶牛们判断有多少头奶牛或是两头奶牛组成的队伍可以获胜。

而不是有多少个地方获胜了，所以我们还要开一个标记数组来记录这一队是否已经赢过了。如果赢过了，就不再加。

所以说下面才是正确代码。~~嘿嘿嘿 STL 真好用。~~

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main(){
	vector<vector<char>> c(3,vector<char>(4));
	for (int i=0;i<3;++i){
		for (int j=0;j<3;++j){
			c[i][j]=getchar();
		}
		getchar();
	} 
	int ans1=0,ans2=0;
	auto solve=[&ans1,&ans2](char a,char b,char c){//记答案 
		if (a>b) swap(a,b);
		if (a>c) swap(a,c);
		if (b>c) swap(b,c);//排序
		if (a==b && a==c){
			++ans1;
		}else if (a==b || b==c){//这里较巧妙第一个字符和第三个字符一定不一样 
			++ans2;
		}
	};
	for (int i=0;i<3;++i){
		solve(c[i][0],c[i][1],c[i][2]);//行 
		solve(c[0][i],c[1][i],c[2][i]);//列 
	}
	solve(c[0][0],c[1][1],c[2][2]);//对角线
	solve(c[0][2],c[1][1],c[2][0]);//对角线
	cout<<ans1<<endl<<ans2<<endl; 
	return 0;
}
```

[完结撒花！](https://www.luogu.com.cn/record/146159146)

---

## 作者：mywzj_mo (赞：0)

### 前言
暴力能出奇迹，况且这道题也可以直接暴力。

### 正言
显然，大写英文字母只有 $\text{A-Z}$ 共26个字母。通过枚举每种组队的情况也不会超时。所以我们可以直接使用暴力的方法进行枚举。

1. 判断一头奶牛的获胜情况：只有同一个字母占据了一个横排、一个竖排或对角线，这一头奶牛才能获胜。

2. 判断两头奶牛（组队）的获胜情况：先枚举所有的组队情况。设两头奶牛的字母在一个横排，一个竖排或对角线中出现的次数为 $a,b$，则只有当 $a+b=3$ 和 $a \ne 0 $ 与 $b\ne 0$ 同时成立时，这两头奶牛占据了一个横排，一个竖排或一条对角线。

### 代码
温馨提示：诚信做人，不要抄袭。
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[5][5];
int ans;
int main(){
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			cin>>c[i][j];
		}
	}
	for(char ch='A';ch<='Z';ch++){
		int flag=0;
		for(int i=1;i<=3;i++){
			if(c[i][1]==ch&&c[i][2]==ch&&c[i][3]==ch)flag=1;//横排
			if(c[1][i]==ch&&c[2][i]==ch&&c[3][i]==ch)flag=1;//竖排
		}
		if(c[1][1]==ch&&c[2][2]==ch&&c[3][3]==ch)flag=1;//判断两条对角线
		if(c[1][3]==ch&&c[2][2]==ch&&c[3][1]==ch)flag=1;
		ans+=flag;
	}
	cout<<ans<<'\n';
	ans=0;
	for(char ch1='A';ch1<='Z';ch1++){//枚举所有的组队情况，注意去重
		for(char ch2=ch1+1;ch2<='Z';ch2++){
			int flag=0;
			int vis1,vis2;//vis用于记录出现次数
			vis1=vis2=0;
			for(int i=1;i<=3;i++){//横排
				vis1=vis2=0;
				for(int j=1;j<=3;j++){
					if(c[i][j]==ch1)vis1++;
					if(c[i][j]==ch2)vis2++;
				}
				if(vis1+vis2==3&&vis1!=0&&vis2!=0){
					flag=1;
				}
			}
			for(int j=1;j<=3;j++){//竖排
				vis1=vis2=0;
				for(int i=1;i<=3;i++){
					if(c[i][j]==ch1)vis1++;
					if(c[i][j]==ch2)vis2++;
				}
				if(vis1+vis2==3&&vis1!=0&&vis2!=0){
					flag=1;
				}
			}
			vis1=vis2=0;
			for(int i=1;i<=3;i++){//对角线1:左上到右下
				if(c[i][i]==ch1)vis1++;
				if(c[i][i]==ch2)vis2++;
			}
			if(vis1+vis2==3&&vis1!=0&&vis2!=0){
				flag=1;
			}
			vis1=vis2=0;
			for(int i=1;i<=3;i++){//对角线2:右上到左下
				if(c[i][4-i]==ch1)vis1++;
				if(c[i][4-i]==ch2)vis2++;
			}
			if(vis1+vis2==3&&vis1!=0&&vis2!=0){
				flag=1;
			}
			ans+=flag;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：_little_Cabbage_ (赞：0)

# P10122 [USACO18OPEN] Team Tic Tac Toe B 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p10122)~~

这是一道模拟题。

对于每一种情况直接枚举即可，注意要去重。

~~或成本题最长 AC 代码~~好吧看来不是最长了。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,int>mp1;
map<pair<char,char>,int>mp2;
char s[10];
int main()
{
	for(int i=1;i<=9;i++)
	{
		cin>>s[i];
	}
	int ans1=0,ans2=0;
	if(s[1]==s[2]&&s[2]==s[3]&&mp1[s[1]]==0)
	{
		ans1++;
		mp1[s[1]]=1;
	}
	if(s[4]==s[5]&&s[5]==s[6]&&mp1[s[4]]==0)
	{
		ans1++;
		mp1[s[4]]=1;
	}
	if(s[7]==s[8]&&s[8]==s[9]&&mp1[s[7]]==0)
	{
		ans1++;
		mp1[s[7]]=1;
	}
	if(s[1]==s[4]&&s[4]==s[7]&&mp1[s[1]]==0)
	{
		ans1++;
		mp1[s[1]]=1;
	}
	if(s[2]==s[5]&&s[5]==s[8]&&mp1[s[2]]==0)
	{
		ans1++;
		mp1[s[2]]=1;
	}
	if(s[3]==s[6]&&s[6]==s[9]&&mp1[s[3]]==0)
	{
		ans1++;
		mp1[s[3]]=1;
	}
	if(s[1]==s[5]&&s[5]==s[9]&&mp1[s[1]]==0)
	{
		ans1++;
		mp1[s[1]]=1;
	}
	if(s[3]==s[5]&&s[5]==s[7]&&mp1[s[3]]==0)
	{
		ans1++;
		mp1[s[3]]=1;
	}
	if(s[1]==s[2]&&s[2]!=s[3]&&mp2[make_pair(s[3],s[2])]==0||s[1]==s[3]&&s[3]!=s[2]&&mp2[make_pair(s[2],s[3])]==0||s[1]!=s[2]&&s[2]==s[3]&&mp2[make_pair(s[2],s[1])]==0)
	{
		ans2++;
		if(s[1]==s[2])
		{
			mp2[make_pair(s[3],s[2])]=1;
			mp2[make_pair(s[2],s[3])]=1;
		}
		else if(s[1]==s[3])
		{
			mp2[make_pair(s[2],s[3])]=1;
			mp2[make_pair(s[3],s[2])]=1;
		}
		else
		{
			mp2[make_pair(s[1],s[2])]=1;
			mp2[make_pair(s[2],s[1])]=1;
		}
	}
	if(s[4]==s[5]&&s[5]!=s[6]&&mp2[make_pair(s[6],s[5])]==0||s[4]==s[6]&&s[4]!=s[5]&&mp2[make_pair(s[4],s[5])]==0||s[4]!=s[5]&&s[5]==s[6]&&mp2[make_pair(s[5],s[4])]==0)
	{
		ans2++;
		if(s[4]==s[5])
		{
			mp2[make_pair(s[6],s[5])]=1;
			mp2[make_pair(s[5],s[6])]=1;
		}
		else if(s[4]==s[6])
		{
			mp2[make_pair(s[4],s[5])]=1;
			mp2[make_pair(s[5],s[4])]=1;
		}
		else
		{
			mp2[make_pair(s[4],s[5])]=1;
			mp2[make_pair(s[5],s[4])]=1;
		}
	}
	if(s[7]==s[8]&&s[8]!=s[9]&&mp2[make_pair(s[9],s[8])]==0||s[7]==s[9]&&s[8]!=s[9]&&mp2[make_pair(s[8],s[9])]==0||s[7]!=s[8]&&s[9]==s[8]&&mp2[make_pair(s[8],s[7])]==0)
	{
		ans2++;
		if(s[7]==s[8])
		{
			mp2[make_pair(s[9],s[8])]=1;
			mp2[make_pair(s[8],s[9])]=1;
		}
		else if(s[7]==s[9])
		{
			mp2[make_pair(s[8],s[9])]=1;
			mp2[make_pair(s[9],s[8])]=1;
		}
		else
		{
			mp2[make_pair(s[8],s[7])]=1;
			mp2[make_pair(s[7],s[8])]=1;
		}
	}
	if(s[1]==s[4]&&s[4]!=s[7]&&mp2[make_pair(s[7],s[4])]==0||s[1]==s[7]&&s[7]!=s[4]&&mp2[make_pair(s[7],s[4])]==0||s[7]==s[4]&&s[1]!=s[4]&&mp2[make_pair(s[4],s[1])]==0)
	{
		ans2++;
		if(s[1]==s[4])
		{
			mp2[make_pair(s[7],s[4])]=1;
			mp2[make_pair(s[4],s[7])]=1;
		}
		else if(s[1]==s[7])
		{
			mp2[make_pair(s[7],s[4])]=1;
			mp2[make_pair(s[4],s[7])]=1;
		}
		else
		{
			mp2[make_pair(s[1],s[4])]=1;
			mp2[make_pair(s[4],s[1])]=1;
		}
	}
	if(s[2]==s[5]&&s[5]!=s[8]&&mp2[make_pair(s[8],s[5])]==0||s[2]==s[8]&&s[5]!=s[8]&&mp2[make_pair(s[5],s[8])]==0||s[5]==s[8]&&s[2]!=s[5]&&mp2[make_pair(s[5],s[2])]==0)
	{
		ans2++;
		if(s[1+1]==s[4+1])
		{
			mp2[make_pair(s[8],s[5])]=1;
			mp2[make_pair(s[5],s[8])]=1;
		}
		else if(s[1+1]==s[7+1])
		{
			mp2[make_pair(s[8],s[5])]=1;
			mp2[make_pair(s[5],s[8])]=1;
		}
		else
		{
			mp2[make_pair(s[2],s[5])]=1;
			mp2[make_pair(s[5],s[2])]=1;
		}
	}
	if(s[3]==s[6]&&s[6]!=s[9]&&mp2[make_pair(s[9],s[6])]==0||s[3]==s[9]&&s[3]!=s[6]&&mp2[make_pair(s[3],s[6])]==0||s[9]==s[6]&&s[3]!=s[6]&&mp2[make_pair(s[6],s[3])]==0)
	{
		ans2++;
		if(s[3]==s[6])
		{
			mp2[make_pair(s[9],s[6])]=1;
			mp2[make_pair(s[6],s[9])]=1;
		}
		else if(s[3]==s[9])
		{
			mp2[make_pair(s[6],s[3])]=1;
			mp2[make_pair(s[3],s[6])]=1;
		}
		else
		{
			mp2[make_pair(s[3],s[6])]=1;
			mp2[make_pair(s[6],s[3])]=1;
		}
	}
	if(s[1]==s[5]&&s[1]!=s[9]&&mp2[make_pair(s[1],s[9])]==0||s[1]==s[9]&&s[1]!=s[5]&&mp2[make_pair(s[1],s[5])]==0||s[5]==s[9]&&s[1]!=s[9]&&mp2[make_pair(s[1],s[9])]==0)
	{
		ans2++;
		if(s[1]==s[5])
		{
			mp2[make_pair(s[1],s[9])]=1;
			mp2[make_pair(s[9],s[1])]=1;
		}
		else if(s[1]==s[9])
		{
			mp2[make_pair(s[5],s[1])]=1;
			mp2[make_pair(s[1],s[5])]=1;
		}
		else
		{
			mp2[make_pair(s[9],s[1])]=1;
			mp2[make_pair(s[1],s[9])]=1;
		}
	}
	if(s[3]==s[5]&&s[5]!=s[7]&&mp2[make_pair(s[7],s[5])]==0||s[3]==s[7]&&s[7]!=s[5]&&mp2[make_pair(s[7],s[5])]==0||s[7]==s[5]&&s[5]!=s[3]&&mp2[make_pair(s[5],s[3])]==0)
	{
		ans2++;
		if(s[3]==s[5])
		{
			mp2[make_pair(s[7],s[5])]=1;
			mp2[make_pair(s[5],s[7])]=1;
		}
		else if(s[3]==s[7])
		{
			mp2[make_pair(s[7],s[5])]=1;
			mp2[make_pair(s[5],s[7])]=1;
		}
		else
		{
			mp2[make_pair(s[3],s[5])]=1;
			mp2[make_pair(s[5],s[3])]=1;
		}
	}
	printf("%d\n%d",ans1,ans2);
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/146061924)

---

