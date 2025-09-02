# Piet

## 题目描述

Piet is one of the most known visual esoteric programming languages. The programs in Piet are constructed from colorful blocks of pixels and interpreted using pretty complicated rules. In this problem we will use a subset of Piet language with simplified rules.

The program will be a rectangular image consisting of colored and black pixels. The color of each pixel will be given by an integer number between 0 and 9, inclusive, with 0 denoting black. A block of pixels is defined as a rectangle of pixels of the same color (not black). It is guaranteed that all connected groups of colored pixels of the same color will form rectangular blocks. Groups of black pixels can form arbitrary shapes.

The program is interpreted using movement of instruction pointer (IP) which consists of three parts:

- current block pointer (BP); note that there is no concept of current pixel within the block;
- direction pointer (DP) which can point left, right, up or down;
- block chooser (CP) which can point to the left or to the right from the direction given by DP; in absolute values CP can differ from DP by 90 degrees counterclockwise or clockwise, respectively.

Initially BP points to the block which contains the top-left corner of the program, DP points to the right, and CP points to the left (see the orange square on the image below).

One step of program interpretation changes the state of IP in a following way. The interpreter finds the furthest edge of the current color block in the direction of the DP. From all pixels that form this edge, the interpreter selects the furthest one in the direction of CP. After this, BP attempts to move from this pixel into the next one in the direction of DP. If the next pixel belongs to a colored block, this block becomes the current one, and two other parts of IP stay the same. It the next pixel is black or outside of the program, BP stays the same but two other parts of IP change. If CP was pointing to the left, now it points to the right, and DP stays the same. If CP was pointing to the right, now it points to the left, and DP is rotated 90 degrees clockwise.

This way BP will never point to a black block (it is guaranteed that top-left pixel of the program will not be black).

You are given a Piet program. You have to figure out which block of the program will be current after $ n $ steps.

## 说明/提示

In the first example IP changes in the following way. After step 1 block 2 becomes current one and stays it after two more steps. After step 4 BP moves to block 3, after step 7 — to block 4, and finally after step 10 BP returns to block 1.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF132B/ce209b4d4ed0181e1c11bf614ed9fbec2a05e0d7.png)The sequence of states of IP is shown on the image: the arrows are traversed clockwise, the main arrow shows direction of DP, the side one — the direction of CP.

## 样例 #1

### 输入

```
2 10
12
43
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 12
1423
6624
6625
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5 9
10345
23456
34567
45678
56789
```

### 输出

```
5
```

# 题解

## 作者：Ghosty_Neutrino (赞：0)

翻译自 ConwayTian。
## 分析
在第一个示例中，IP 的变化如下。在第 $1$ 步之后，第 $2$ 块成为当前块，并在接下来的步中保持不变。在第 $4$ 步之后，BP 移动到第 $3$ 块，在第 $7$ 步之后移动到第 $4$ 块最后在第 $10$ 步之后，BP 返回到第 $1$ 块。

![](https://cdn.luogu.com.cn/upload/image_hosting/nm3hzfwn.png)

IP 状态的顺序如图所示：箭头按顺时针方向遍历，主箭头表示 DP 的方向，侧箭头表示的方向。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 55
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int vis[N][N][5][5];
int map[N][N];
int m,n,l;
struct Item{
    int dp,cp,r,c,tr,tc;
    void next(){
        while(1){
            tr=r+dir[dp][0];
            tc=c+dir[dp][1];
            if(check()) break;
            r=tr;c=tc;
            }
            int t=dp;
            dp=cp==0?(dp+3)%4:(dp+1)%4;
            while(1){
                tr=r+dir[dp][0];
                tc=c+dir[dp][1];
                if(check()) break;
                r=tr;c=tc;
            }
            dp=t;
            tr=r+dir[dp][0];
            tc=c+dir[dp][1];
            if(tr<0||tr>=m||tc<0||tc>=l||map[tr][tc]==0){
                if(cp==0) cp=1;
                else{cp=0;dp=(dp+1)%4;}
            }
            else{r=tr;c=tc;}
        }
    bool check(){
        return(tr<0||tr>=m||tc<0||tc>=l||map[tr][tc]!=map[r][c]);
    }
    int visId(){
        return vis[r][c][dp][cp];
    }
    void setVis(int id){
        vis[r][c][dp][cp]=id;
    }
};
int main(){
    char tmp[N];
    cin>>m>>n;
    for(int i=0;i<m;i++){
        cin>>tmp;
        if(i==0) l=strlen(tmp);
        for(int j=0;j<l;j++)
            map[i][j]=tmp[j]-'0';
    }
    Item step;
	int id;
    step.cp=step.dp=step.r=step.c=id=0;
    memset(vis,-1,sizeof(vis));
    step.setVis(id++);
    while(n--){
        step.next();
        if(step.visId()==-1) {step.setVis(id++);continue;}
        n=n%(id-step.visId());break;
    }
    n=n<0?0:n;
    while(n--) step.next();
    cout<<map[step.r][step.c]<<endl;
    return 0;
}
```

---

