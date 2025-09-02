# Sofa Thief

## 题目描述

Yet another round on DecoForces is coming! Grandpa Maks wanted to participate in it but someone has stolen his precious sofa! And how can one perform well with such a major loss?

Fortunately, the thief had left a note for Grandpa Maks. This note got Maks to the sofa storehouse. Still he had no idea which sofa belongs to him as they all looked the same!

The storehouse is represented as matrix $ n×m $ . Every sofa takes two neighbouring by some side cells. No cell is covered by more than one sofa. There can be empty cells.

Sofa $ A $ is standing to the left of sofa $ B $ if there exist two such cells $ a $ and $ b $ that  $ x_{a}&lt;x_{b} $ , $ a $ is covered by $ A $ and $ b $ is covered by $ B $ . Sofa $ A $ is standing to the top of sofa $ B $ if there exist two such cells $ a $ and $ b $ that  $ y_{a}&lt;y_{b} $ , $ a $ is covered by $ A $ and $ b $ is covered by $ B $ . Right and bottom conditions are declared the same way.

Note that in all conditions $ A≠B $ . Also some sofa $ A $ can be both to the top of another sofa $ B $ and to the bottom of it. The same is for left and right conditions.

The note also stated that there are $ cnt_{l} $ sofas to the left of Grandpa Maks's sofa, $ cnt_{r} $ — to the right, $ cnt_{t} $ — to the top and $ cnt_{b} $ — to the bottom.

Grandpa Maks asks you to help him to identify his sofa. It is guaranteed that there is no more than one sofa of given conditions.

Output the number of Grandpa Maks's sofa. If there is no such sofa that all the conditions are met for it then output -1.

## 说明/提示

Let's consider the second example.

- The first sofa has $ 0 $ to its left, $ 2 $ sofas to its right ( $ (1,1) $ is to the left of both $ (5,5) $ and $ (5,4) $ ), $ 0 $ to its top and $ 2 $ to its bottom (both $ 2 $ nd and $ 3 $ rd sofas are below).
- The second sofa has $ cnt_{l}=2 $ , $ cnt_{r}=1 $ , $ cnt_{t}=2 $ and $ cnt_{b}=0 $ .
- The third sofa has $ cnt_{l}=2 $ , $ cnt_{r}=1 $ , $ cnt_{t}=1 $ and $ cnt_{b}=1 $ .

So the second one corresponds to the given conditions.

In the third example

- The first sofa has $ cnt_{l}=1 $ , $ cnt_{r}=1 $ , $ cnt_{t}=0 $ and $ cnt_{b}=1 $ .
- The second sofa has $ cnt_{l}=1 $ , $ cnt_{r}=1 $ , $ cnt_{t}=1 $ and $ cnt_{b}=0 $ .

And there is no sofa with the set $ (1,0,0,0) $ so the answer is -1.

## 样例 #1

### 输入

```
2
3 2
3 1 3 2
1 2 2 2
1 0 0 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
10 10
1 2 1 1
5 5 6 5
6 4 5 4
2 1 2 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2
2 2
2 1 1 1
1 2 2 2
1 0 0 0
```

### 输出

```
-1
```

# 题解

## 作者：yuheng_wang080904 (赞：1)

## 题意
给定沙发数量 $d$，和一个长宽分别为 $n,m$ 的长方形场地，每个沙发占两格。接下来 $d$ 行给出 $x1,y1,x2,y2$，表示每个沙发的所在位置。最后给定$cnt_l,cnt_r,cnt_t,cnt_b$，让你求出一个沙发使得在它左边的沙发有 $cnt_l$ 个，在它右边的沙发有 $cnt_r$ 个，在它上面的沙发有 $cnt_t$ 个，在它下面的沙发有 $cnt_b$ 个。如果没有满足条件的沙发，输出 $-1$。

一个沙发 $a$ 在另一个沙发 $b$ 左边是指沙发 $a$ 的某一个 $x_i$ 与沙发 $b$ 的某一个 $x_j$ 满足 $x_i<x_j$。

同样的，一个沙发 $a$ 在另一个沙发 $b$ 右边是指沙发 $a$ 的某一个 $x_i$ 与沙发 $b$ 的某一个 $x_j$ 满足 $x_i>x_j$。

一个沙发 $a$ 在另一个沙发 $b$ 上面是指沙发 $a$ 的某一个 $y_i$ 与沙发 $b$ 的某一个 $y_j$ 满足 $y_i<y_j$。

同样的，一个沙发 $a$ 在另一个沙发 $b$ 下面是指沙发 $a$ 的某一个 $y_i$ 与沙发 $b$ 的某一个 $y_j$ 满足 $y_i>y_j$。

因此，我们需要注意，一个沙发 $a$ 可能既在另一个沙发 $b$ 的左边又在它的右边。

同样的，一个沙发 $a$ 也可能既在另一个沙发 $b$ 的上面又在它的下面。

## 思路

我们只需要枚举每个沙发，分别以 $O(1)$ 的时间复杂度求出在它左边，右边，上面，下面的有几个沙发。

怎么求呢，我们要预处理前缀和或后缀和（数组多开一点，小心越界）。

当我们找某一沙发左边沙发的个数时，总是看其余沙发的最左边的一点进行比较，因此定义数组 $l$，用于求每个沙发左边沙发的个数时使用，对于每个沙发，令 $l[min(x1,x2)]$ 加一。然后前缀和处理。

同样的，当我们找某一沙发右边沙发的个数时，总是看其余沙发的最右边的一点进行比较，因此定义数组 $r$，用于求每个沙发右边沙发的个数时使用，对于每个沙发，令 $r[max(x1,x2)]$ 加一。然后后缀和处理。

当我们找某一沙发上面沙发的个数时，总是看其余沙发的最上边的一点进行比较，因此定义数组 $t$，用于求每个沙发上面沙发的个数时使用，对于每个沙发，令 $t[min(y1,y2)]$ 加一。然后前缀和处理。

同样的，当我们找某一沙发下面沙发的个数时，总是看其余沙发的最下边的一点进行比较，因此定义数组 $b$，用于求每个沙发下面沙发的个数时使用，对于每个沙发，令 $b[max(y1,y2)]$ 加一。然后后缀和处理。

预处理过后，循环枚举每一个沙发，注意题意中是小于或大于，不带等号！注意自己是否被算了进去！然后与 $cnt_l,cnt_r,cnt_t,cnt_b$ 比较输出。

不要忘记如果循环中没有输出，最后输出 $-1$ 哟！

## 代码

下面给出我的代码，完全根据分析写出来的，大家可以对照着看，是比较简单易懂的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int d,n,m,cntl,cntr,cntt,cntb;
int s[5][100005],l[100005],r[100005],t[100005],b[100005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>d>>n>>m;
    for(int i=1;i<=d;i++)cin>>s[1][i]>>s[2][i]>>s[3][i]>>s[4][i];
    cin>>cntl>>cntr>>cntt>>cntb;
    for(int i=1;i<=d;i++){
	l[min(s[1][i],s[3][i])]++;
	r[max(s[1][i],s[3][i])]++;
	t[min(s[2][i],s[4][i])]++;
	b[max(s[2][i],s[4][i])]++;
    }
    for(int i=1;i<=n;i++)l[i]+=l[i-1];
    for(int i=n;i>=1;i--)r[i]+=r[i+1];
    for(int i=1;i<=m;i++)t[i]+=t[i-1];
    for(int i=m;i>=1;i--)b[i]+=b[i+1];
    for(int i=1;i<=d;i++){
	int ansl=0,ansr=0,anst=0,ansb=0;
	ansl=l[max(s[1][i],s[3][i])-1];
	if(min(s[1][i],s[3][i])==max(s[1][i],s[3][i])-1)ansl--;
	ansr=r[min(s[1][i],s[3][i])+1];
	if(max(s[1][i],s[3][i])==min(s[1][i],s[3][i])+1)ansr--;
	anst=t[max(s[2][i],s[4][i])-1];
	if(min(s[2][i],s[4][i])==max(s[2][i],s[4][i])-1)anst--;
	ansb=b[min(s[2][i],s[4][i])+1];
	if(max(s[2][i],s[4][i])==min(s[2][i],s[4][i])+1)ansb--;
	if(ansl==cntl&&ansr==cntr&&anst==cntt&&ansb==cntb){
	    cout<<i<<endl;
            return 0;
	}
    }
    cout<<-1<<endl;
    return 0;
}
```


---

