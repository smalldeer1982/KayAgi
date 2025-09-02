# [ABC038D] プレゼント

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc038/tasks/abc038_d

高橋くんはプレゼントを用意することになりました。プレゼントの中身はすでに決まり、あとはプレゼントを入れる箱を用意するだけです。 高橋くんが使える箱は$ N $個あり、$ i $番目の箱は縦$ h_i $cm×横$ w_i $cmのサイズです。

プレゼントがより多くの箱に入っていたほうが面白いと考えた高橋くんは、なるべく多くの箱を入れ子にし、最も内側の箱にプレゼントを入れることにしました。 ある箱は、縦・横ともにより大きいサイズの箱にのみ入れることができます。また、ある箱は$ 1 $つまでしか他の箱を入れることはできません。

プレゼントを入れる箱を最大で何重の入れ子にできるか答えてください。

## 说明/提示

### 制約

- $ 1≦N≦10^5 $
- $ 1≦h_i≦10^5 $
- $ 1≦w_i≦10^5 $

### 部分点

- $ N\ ≦\ 1,000 $ を満たすテストケース全てに正解した場合、部分点として$ 30 $点が与えられる。

### Sample Explanation 1

外側の箱から順に、$ 1,\ 3,\ 2 $番目の箱でプレゼントを包むことができます。

### Sample Explanation 2

箱を$ 90 $度回転することはできないことに注意してください。また、ある箱を縦または横の長さが等しい箱に入れることはできません。

## 样例 #1

### 输入

```
3
3 3
1 1
2 2```

### 输出

```
3```

## 样例 #2

### 输入

```
2
4 5
4 3```

### 输出

```
1```

## 样例 #3

### 输入

```
4
2 5
3 3
4 5
6 6```

### 输出

```
3```

## 样例 #4

### 输入

```
5
8 8
5 3
2 2
4 2
2 1```

### 输出

```
4```

# 题解

## 作者：Сталин (赞：0)

~~纪念一下这道有坑的题 调了几个小时~~

~~感觉我的做法有点奇技淫巧的味道QAQ~~

1. 先把盒子**按宽**排一遍序 然后记录下每个盒子**原来(读入时的)位置 在宽升序的情况下**排名第几(ys) 

因为后面还要**按长**排一遍序，两次排序后**只有p(原位置)可以记录且保持不变**

2. 用**树状数组维护已找到答案最大值，下标是按宽排序处理后的数组(ys)** 

3. 按长再排一遍序 保证当前数组按长升序 寻找时 **先找回在按宽排序(ys)里面的排名 再在树状数组里找最大的继承**

当然，还有很多细节(坑！！！)，都在代码里面啦

UPD:其实这题就是最长（严格）上升子序列啦QAQ我撒了……

code:

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ri register int
#include<queue>
using namespace std;
inline int mymax(ri x,ri y){return x>y?x:y;}
inline int mymin(ri x,ri y){return x<y?x:y;}
struct node
{
    int x,y,p;
}a[110000];

struct myqueue
{
    int x,p,c;
}stack[110000]; int top;

inline bool cmp(node n1,node n2)
{//注意符号 cmp是按长(输入的第一个)优先排序的 
    if(n1.x==n2.x)return n1.y<n2.y;
    return n1.x<n2.x;
}
inline bool mmp(node n1,node n2)
{//按宽优先排序的 由于要避免宽度相等时重复计算，故此时第二优先字长按降序排 让先出现的排在后面，后出现的排在前面，就可以避免（y相同时）后出现的继承前面出现的
    if(n1.y==n2.y)return n1.x>n2.x;
    return n1.y<n2.y;
}
int n;
int ys[110000];

int f[110000];//树状数组 f[i]记录宽度<=a[i].x的盒子中最多能放几个盒子 
inline int lowbit(ri x){return x&-x;}//树状数组 

inline int ask(ri x)
{
    ri maxn=0,p=ys[ a[x].p ];
    for(int i=p;i;i-=lowbit(i))maxn=mymax(maxn,f[i]);
    return maxn;
}

inline void add(ri x,ri c)
{
    ri p=ys[ a[x].p ];
    for(int i=p;i<=n;i+=lowbit(i))f[i]=mymax(f[i],c);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].p=i;
    }

    sort(a+1,a+n+1,mmp);
    for(int i=1;i<=n;i++)
    {
        ys[ a[i].p ]=i;
    }

    sort(a+1,a+n+1,cmp); int ans=0;
    for(int i=1;i<=n;i++)
    {
        while( top && a[ stack[top].p ].x<a[i].x )//当有很多个长相等的箱子时，加入备选栈 因为长或宽相等都不能套进
        {
            add(stack[top].p,stack[top].c);
            top--;
        }
        int c=ask(i)+1; ans=mymax(ans,c);
        top++; stack[top].x=a[i].y; stack[top].p=i; stack[top].c=c;
    }
    printf("%d\n",ans);
    return 0;
}
```


---

