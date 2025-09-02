# [IOI 1994] 时钟 The Clocks

## 题目描述

考虑将如此安排在一个 $3 \times 3$ 行列中的九个时钟:

```plain
|-------|   |-------|   |-------|
|       |   |       |   |   |   |
|---o   |   |---o   |   |   o   |
|       |   |       |   |       |
|-------|   |-------|   |-------|
    A           B           C

|-------|   |-------|   |-------|
|       |   |       |   |       |
|   o   |   |   o   |   |   o   |
|   |   |   |   |   |   |   |   |
|-------|   |-------|   |-------|
    D           E           F

|-------|   |-------|   |-------|
|       |   |       |   |       |
|   o   |   |   o---|   |   o   |
|   |   |   |       |   |   |   |
|-------|   |-------|   |-------|
    G           H           I
```

目标要找一个最小的移动顺序将所有的指针指向 $12$ 点。下面原表格列出了 $9$ 种不同的旋转指针的方法，每一种方法都叫一次移动。  
选择 $1 \sim 9$ 号移动方法，将会使在表格中对应的时钟的指针顺时针旋转 
 $90$ 度。


|移动方法  | 受影响的时钟 |
| :----------: | :----------: |
| 1 | ABDE |
| 2 | ABC |
| 3 | BCEF |
| 4 | ADG |
| 5 | BDEFH |
| 6 | CFI |
| 7 | DEGH |
| 8 | GHI |
| 9 | EFHI |

例子：

```plain
9 9 12       9 12 12        9 12 12        12 12 12        12 12 12
6 6 6   5 -> 9  9  9   8 -> 9  9  9   4 -> 12  9  9   9 -> 12 12 12
6 3 6        6  6  6        9  9  9        12  9  9        12 12 12
```

**但这可能不是正确的方法，请看下文。**


## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 1.4


## 样例 #1

### 输入

```
9 9 12
6 6 6
6 3 6 
```

### 输出

```
4 5 8 9
```

# 题解

## 作者：一念之间 (赞：44)

枚举暴力大法好！！！！！！！！！

因为时钟只有3,6,9,12，三个状态，每个时钟转到12需要（12-k）%4次移动，

累计每次移动，如a表受1,2,4,控制，所以if(p1+p2+p4)%4==(4-a[1])%4,a表就转到12

以此类推，从1 开始，保证最小

比较丑的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int b[10000];
void out()
{
    for(int i=1;i<=9;i++)
    if(b[i]>0)
    for(int j=1;j<=b[i];j++)
    cout<<i<<" ";
}
int main()
{int a[100];
    for(int i=1;i<=9;i++)
    {cin>>a[i];
     a[i]=a[i]/3;
    }
    for(int p1=0;p1<=3;p1++)
    for(int p2=0;p2<=3;p2++)
    for(int p3=0;p3<=3;p3++)
    for(int p4=0;p4<=3;p4++)
    for(int p5=0;p5<=3;p5++)
    for(int p6=0;p6<=3;p6++)
    for(int p7=0;p7<=3;p7++)
    for(int p8=0;p8<=3;p8++)
    for(int p9=0;p9<=3;p9++)
    if((p1+p2+p4)%4==(4-a[1])%4&&(p1+p2+p3+p5)%4==(4-a[2])%4&&(p2+p3+p6)%4==(4-a[3])%4&&(p1+p4+p5+p7)%4==(4-a[4])%4&&
    (p1+p3+p5+p7+p9)%4==(4-a[5])%4&&(p3+p5+p6+p9)%4==(4-a[6])%4&&(p4+p7+p8)%4==(4-a[7])%4&&(p5+p7+p8+p9)%4==(4-a[8])%4&&
    (p6+p8+p9)%4==(4-a[9])%4)
    {b[1]=p1;
    b[2]=p2;
    b[3]=p3;
    b[4]=p4;
    b[5]=p5;
    b[6]=p6;
    b[7]=p7;
    b[8]=p8;
    b[9]=p9;
    out();
    }
}
```

---

## 作者：cww970329 (赞：25)


这题需要在可读性和效率之间妥协

## Overview

一共只有 $4^9$ 个状态，大概二十六万多一点，所以肯定是够用了

bfs肯定是那个bfs，关键是状态的表示，可以用一个int来表示状态，这样转移的时候比较麻烦，也可以用`3*3`矩阵来表示这样效率与空间开销会比较大~~虽然我用的就是这个~~

阅读了一下已有的题解，ummmmm，代码~~好丑~~不是很直观

可以联想到八数码和华容道

从数学角度来看，这9种运算是9个算子（最简单的加法运算）

## ~~心路历程~~探索过程

### `map <Matrix, int>`

于是乎我的第一份代码（出于篇幅和美观这里给出关键代码，大家可以意会，完整代码附在最后面）

```c++

const int MOVES[11][MATRIX_N][MATRIX_N] = {
    {// ABDE
        {1,1,0},
        {1,1,0},
        {0,0,0}
    },{//ABC
        {1,1,1},
        {0,0,0},
        {0,0,0}
    },
    ...
};

struct Matrix{
    int s[MATRIX_N][MATRIX_N];

    Matrix(){memset(s, 0, sizeof(s));}
    int* operator [](int idx){return s[idx];}
    Matrix (const int arr[MATRIX_N][MATRIX_N]){...}
    void read(){...}
    friend Matrix operator + (Matrix &a, Matrix &b){...}
    friend Matrix operator - (Matrix &a, Matrix &b){...}
    friend bool operator < (const Matrix &a, const Matrix &b){...}
    bool is_target(){..}
    void print(){...}
} moves[11];

map <Matrix, int> vis;  // come from which move

void print_path(Matrix cur){
    if (vis[cur] == -1) return;
    Matrix pre = cur - moves[vis[cur]];
    print_path(pre);
    printf("%d", vis[cur] + 1);
    //cur.print();
    if (!cur.is_target()) putchar(' ');
}

void bfs(Matrix start){
    queue <Matrix> Q;
    vis[start] = -1;
    for (Q.push(start); !Q.empty();){
        Matrix cur = Q.front(); Q.pop();
        if (cur.is_target()) {
            print_path(cur);
            return;
        }
        for (int i = 0; i < 9; i++){
            Matrix nxt = cur + moves[i];
            if (vis[nxt]) continue;
            vis[nxt] = i;
            Q.push(nxt);
        }
    }
}

int main(){...}
```

自以为是最直观的一个版本，可能是python写多了吧。

只过了两个点，可能是过多的matrix导致效率降低，内存也难以控制

### `map <int, int>`

于是乎往matrix中添加`to_int()`函数

```c++
struct Matrix{
	...

    int to_int(){
        int ans = 0;
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                ans = (ans * 10) + s[i][j];
        return ans;
    }
    ...
}

...

typedef pair<int, int> P;
map <int, P> vis;  // pair<pre, come from which move>
```

过了5个点，果然有毒，ummmm，加个氧气优化，过了

但是不甘心啊，思索一下，一共就那么点状态，出锅的大概率是`map`

### 老老实实哈希吧

其实数组长度只要`30w`就足够，可以整一个类似康托展开的哈希函数，直接计算出他是排号第几大的，不过，~~因为懒~~，为什么先模一个大质数呢~~暴力一下呢~~

于是乎

```c++
const int MOD = magic_number(a girls qq id);

struct Matrix{
    ...

    int to_int(){
        int ans = 0;
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                ans = (ans * 10) + s[i][j];
        return ans % MOD;
    }
    ...

} start, target, moves[11];

...

P vis[MOD];
//map <int, P> vis;  // pair<pre, come from which move>

void print_path(int cur){
    if (cur == start.to_int()) return;
    int pre = vis[cur].first;
    print_path(pre);
    printf("%d", vis[cur].second + 1);
    if (cur != target.to_int()) putchar(' ');
}
...

```

试了几个数字都WA了，这个时候已经想写类似康托展开的一样东西了，但是，似乎还能挣扎一下，[常用Hash质数表](https://blog.csdn.net/shiyongyang/article/details/78079109)

又试了两个数字，好了，A了。标准写法康托展开或者整个哈希冲突的处理（线性探查或者拉链都行）或者多次哈希多来几个`magic_number`。自己没有继续往下可能是因为折腾了挺久累了~~懒~~

~~STL有风险，使用需谨慎，~~ 真香

## ~~最后bb几句~~Summary

可能工程代码写多了，更倾向于使用造好的轮子吧。

下面两份代码相信不需要什么注释，因为函数名与变量名都是有意义的单词或短语，读起来感觉像是写文章一般。每个函数都保持在20行以内，出锅的概率大大降低，编译样例无debug一遍过，这里不是说代码能力有多好，而是说，使用这个写法，会让自己思路更加清晰，一段时间内只关注一段逻辑，很多人代码debug不出来不是因为代码能力弱，反而是因为代码能力太强，像一个 `int main`完成所有的逻辑。这样的代码在自己脑子十分清晰的时候是可以码的飞起的，不过可能只有两天内的自己才能看懂，可能过了两天自己回头看的时候惊呼“我靠，什么shit”。这里大部分的代码依然是c语言中的`strct`其实是把其当成一个完全`public`的`class`来用了，再~~需求变更~~换写法的时候，只要专注那么几个函数就好了，非常快。稍微讲一点软件工程吧，但太“优雅”了又会导致代码过于膨胀，每个人写的时候都会有一个自己的平衡点。这里给出一个栗子，只是希望以后OI选手的代码风格不再被业界喷。希望以后看题解区的时候能如同读文章一样读大家的代码。

一不小心絮絮叨叨又写了一堆，睡觉睡觉

## 致谢

感谢又白、jjm、贾维斯帮忙看代码，感谢偶像派歌手的音乐陪我度过这个夜晚

see you later

## Future Work

依然有优化空间，比如说bfs的队列里面填的是int然后做一个int转Matrix进行计算甚至直接对int空间进行九种运算。哈希这里是搜了一个简单的magic_number混过去了，前文提了可以使用更优雅的哈希。不写了，~~懒~~

- 又白：只要容忍丑陋，九维的vis
- 我：我拒绝

## 附录

悲伤是奢侈品我消受不起，快乐像噩梦总让人惊醒


### AC版本代码

```c++

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;
const int MOD = 12255871;

const int MATRIX_N = 5;
const int MATRIX_SIZE = 3;

const int MOVES[11][MATRIX_N][MATRIX_N] = {
    {// ABDE
        {1,1,0},
        {1,1,0},
        {0,0,0}
    },{//ABC
        {1,1,1},
        {0,0,0},
        {0,0,0}
    },{//BCEF
        {0,1,1},
        {0,1,1},
        {0,0,0}
    },{//ADG
        {1,0,0},
        {1,0,0},
        {1,0,0}
    },{//BDEFH
        {0,1,0},
        {1,1,1},
        {0,1,0}
    },{//CFI
        {0,0,1},
        {0,0,1},
        {0,0,1}
    },{//DEGH
        {0,0,0},
        {1,1,0},
        {1,1,0}
    },{//GHI
        {0,0,0},
        {0,0,0},
        {1,1,1}
    },{//EFHI
        {0,0,0},
        {0,1,1},
        {0,1,1}
    }
};

struct Matrix{
    int s[MATRIX_N][MATRIX_N];

    Matrix(){memset(s, 0, sizeof(s));}
    int* operator [](int idx){return s[idx];}
    Matrix (const int arr[MATRIX_N][MATRIX_N]){
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                s[i][j] = arr[i][j] * 3;
    }
    void read(){
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++) {
                scanf("%d", &s[i][j]);
                s[i][j] %= 12;
            }
    }

    friend Matrix operator + (Matrix &a, Matrix &b){
        Matrix c;
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                c[i][j] = (a[i][j] + b[i][j]) % 12;
        return c;
    }

    int to_int(){
        int ans = 0;
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                ans = (ans * 10) + s[i][j];
        return ans % MOD;
    }

    void print(){
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                printf("%d%c", s[i][j], j==MATRIX_SIZE-1?' ':' ');
        puts("");
    }
} start, target, moves[11];

P vis[MOD];
//map <int, P> vis;  // pair<pre, come from which move>

void print_path(int cur){
    if (cur == start.to_int()) return;
    int pre = vis[cur].first;
    print_path(pre);
    printf("%d", vis[cur].second + 1);
    if (cur != target.to_int()) putchar(' ');
}

int bfs(Matrix start){
    queue <Matrix> Q;
    memset(vis, 0, sizeof vis);
    vis[start.to_int()] = P(-1, -1);
    for (Q.push(start); !Q.empty();){
        Matrix cur = Q.front(); Q.pop();
        if (cur.to_int() == target.to_int()) return cur.to_int();
        for (int i = 0; i < 9; i++){
            Matrix nxt = cur + moves[i];
            if (vis[nxt.to_int()] != P(0, 0)) continue;
            //if (vis.find(nxt.to_int()) != vis.end()) continue;
            vis[nxt.to_int()] = P(cur.to_int(), i);
            Q.push(nxt);
        }
    }
}

int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    for (int i = 0; i < 9; i++){
        moves[i] = Matrix(MOVES[i]);
    }
    start.read();
    int ans = bfs(start);
    print_path(ans);
    return 0;
}

```

### 第一版代码}（可能还有小坑）

反正只能过两个点，who cares

```c++
#include <bits/stdc++.h>
using namespace std;

const int MATRIX_N = 5;
const int MATRIX_SIZE = 3;

const int MOVES[11][MATRIX_N][MATRIX_N] = {
    {// ABDE
        {1,1,0},
        {1,1,0},
        {0,0,0}
    },{//ABC
        {1,1,1},
        {0,0,0},
        {0,0,0}
    },{//BCEF
        {0,1,1},
        {0,1,1},
        {0,0,0}
    },{//ADG
        {1,0,0},
        {1,0,0},
        {1,0,0}
    },{//BDEFH
        {0,1,0},
        {1,1,1},
        {0,1,0}
    },{//CFI
        {0,0,1},
        {0,0,1},
        {0,0,1}
    },{//DEGH
        {0,0,0},
        {1,1,0},
        {1,1,0}
    },{//GHI
        {0,0,0},
        {0,0,0},
        {1,1,1}
    },{//EFHI
        {0,0,0},
        {0,1,1},
        {0,1,1}
    }
};

struct Matrix{
    int s[MATRIX_N][MATRIX_N];

    Matrix(){memset(s, 0, sizeof(s));}
    int* operator [](int idx){return s[idx];}
    Matrix (const int arr[MATRIX_N][MATRIX_N]){
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                s[i][j] = arr[i][j] * 3;
    }
    void read(){
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++) {
                scanf("%d", &s[i][j]);
                s[i][j] %= 12;
            }
    }

    friend Matrix operator + (Matrix &a, Matrix &b){
        Matrix c;
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                c[i][j] = (a[i][j] + b[i][j]) % 12;
        return c;
    }

    friend Matrix operator - (Matrix &a, Matrix &b){
        Matrix c;
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                c[i][j] = (a[i][j] - b[i][j] + 12) % 12;
        return c;
    }

    friend bool operator < (const Matrix &a, const Matrix &b){
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                if (a.s[i][j] != b.s[i][j]) return a.s[i][j] < b.s[i][j]; 
        return false;
    }

    bool is_target(){
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                if (s[i][j]) return false; 
        return true;
    }

    void print(){
        puts("");
        for (int i = 0; i < MATRIX_SIZE; i++)
            for (int j = 0; j < MATRIX_SIZE; j++)
                printf("%d%c", s[i][j], j==MATRIX_SIZE-1?'\n':' ');
    }
} moves[11];

map <Matrix, int> vis;  // come from which move

void print_path(Matrix cur){
    if (vis[cur] == -1) return;
    Matrix pre = cur - moves[vis[cur]];
    print_path(pre);
    printf("%d", vis[cur] + 1);
    //cur.print();
    if (!cur.is_target()) putchar(' ');
}

void bfs(Matrix start){
    queue <Matrix> Q;
    vis[start] = -1;
    for (Q.push(start); !Q.empty();){
        Matrix cur = Q.front(); Q.pop();
        if (cur.is_target()) {
            print_path(cur);
            return;
        }
        for (int i = 0; i < 9; i++){
            Matrix nxt = cur + moves[i];
            if (vis[nxt]) continue;
            vis[nxt] = i;
            Q.push(nxt);
        }
    }
}

int main(){
    //freopen("in.txt", "r", stdin);
    for (int i = 0; i < 9; i++){
        moves[i] = Matrix(MOVES[i]);
    }
    Matrix start;
    start.read();
    bfs(start);
    return 0;
}

```



---

## 作者：SUNCHAOYI (赞：24)

## 直接打表存入后，进行dfs求解
**上代码：**
```
#include<iostream>
#define M 9//3*3 
using namespace std;
//打表式存入，相当于移动的方法 
int node[M][M]={
{1,1,0,1,1,0,0,0,0},
{1,1,1,0,0,0,0,0,0},
{0,1,1,0,1,1,0,0,0},
{1,0,0,1,0,0,1,0,0},
{0,1,0,1,1,1,0,1,0},
{0,0,1,0,0,1,0,0,1},
{0,0,0,1,1,0,1,1,0},
{0,0,0,0,0,0,1,1,1},
{0,0,0,0,1,1,0,1,1}
};
int a[M],c[M],f[M];
void dfs(int x);
int main()
{
	for(int i=0;i<M;i++)
	{
		cin>>a[i];
		a[i]=a[i]/3%4;//用0-4来表示12,3,6,9点 
	}//
	dfs(0);//开始深搜 
	return 0;
}
void dfs(int x)
{
	bool ok=1;//由于判断是否符合条件:全变为12点 
	for(int i=0;i<M;i++)f[i]=a[i];//复制 
	for(int i=0;i<M;i++)
		for(int j=0;j<M;j++)f[i]=(f[i]+node[j][i]*c[j])%4;//循环进行取数，并模4取余 
	for(int i=0;i<M;i++)
		if(f[i]>0){ok=0;break;} //只有全为0，即全是12点才可以 
	if(ok)//如果符合，进行输出 
	{
		for(int i=0;i<M;i++)
			for(int j=0;j<c[i];j++)cout<<i+1<<" ";//数组从0开始的原因才要i+1 
		cout<<endl;
		x=9;//相当于return; (让它变为边界数) 
	}
	if(x==M)return;//边界条件 
	for(int i=0;i<4;i++){c[x]=i;dfs(x+1);} //继续进行搜索(0-3即可) 
}
```


---

## 作者：woshishei (赞：10)

## 暴力搜索

dfs枚举9次，相当于一个九重循环。

因为使用4次同一种转法会转回原来的状态，所以使用每一种转法最多秩序使用三次，也就自然从0枚举到3。
```cpp
void dfs(int cur)
{
	if(cur>9)//9重循环后
	{
		if(check())//判断
			fl=true;//表示已经找到解
		return;
	}
	for(f[cur]=0;f[cur]<=3;f[cur]++)//枚举使用每一种转法的次数
	{
		dfs(cur+1);
		if(fl)
			return;//有解则直接跳出
	}
}
```
转法都是给出来的，所以可以统计每个时钟会收到哪些操作的影响。

| A | B | C | D | E | F | G | H | I |
| :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- |
| 124 | 1235 | 236 | 1457 | 13579 | 3569 | 478 | 5789 | 689 |

例如，时钟A只会收到1、2、4的影响，所以只需要看经过1、2、4的操作后，时钟A是否朝向12，以此类推。

```cpp
//a[]中储存的是需要转动的次数
bool check()
{
	return ((f[1]+f[2]+f[4]          )%4==a[1]&&\
			(f[1]+f[2]+f[3]+f[5]     )%4==a[2]&&\
			(f[2]+f[3]+f[6]          )%4==a[3]&&\
			(f[1]+f[4]+f[5]+f[7]     )%4==a[4]&&\
			(f[1]+f[3]+f[5]+f[7]+f[9])%4==a[5]&&\
			(f[3]+f[5]+f[6]+f[9]     )%4==a[6]&&\
			(f[4]+f[7]+f[8]          )%4==a[7]&&\
			(f[5]+f[7]+f[8]+f[9]     )%4==a[8]&&\
			(f[6]+f[8]+f[9]          )%4==a[9]);
}
```
[AC代码](https://user50130.blog.luogu.org/p1213-code) **33ms, 0.8MB**

_温馨提示：代码仅供参考，请勿抄袭_

---

## 作者：rikkidayo (赞：8)

# 暴力碾标算！

标算应该是**搜索**，~~也不难想~~，不过本蒟蒻深得某带佬
**~~[@贞白叶翔](https://www.luogu.org/space/show?uid=113884)~~**
的暴力心得（雾），所以打了个暴力出来。

具体(暴力)思路楼上大佬都说了，这里就不多讲了，详见代码注释

```cpp
#include<cstdio>
using namespace std;

int Time[10];//空间复杂度也很小233 
int Ans[10];

int main()
{
	for(int i=1;i<10;Time[i]/=3,i++)
	scanf("%d",&Time[i]);//读入时处理 
	
	//如果你打过暴力，看题目就不难想到 O(3^9 = 19683)复杂度，几乎约等于 O(1)
	//只枚举到3是因为转4下就等于不转，很好理解 
	for(Ans[1]=0;Ans[1]<4;Ans[1]++)
	for(Ans[2]=0;Ans[2]<4;Ans[2]++)
	for(Ans[3]=0;Ans[3]<4;Ans[3]++)
	for(Ans[4]=0;Ans[4]<4;Ans[4]++)
	for(Ans[5]=0;Ans[5]<4;Ans[5]++)//码风不好请见谅 QOQ 
	for(Ans[6]=0;Ans[6]<4;Ans[6]++)
	for(Ans[7]=0;Ans[7]<4;Ans[7]++)
	for(Ans[8]=0;Ans[8]<4;Ans[8]++)
	for(Ans[9]=0;Ans[9]<4;Ans[9]++)
	//判断公式：(Ans[a]+Ans[b]+...+Ans[n])%4 == 4-Time[x]
	if( ( Ans[1]+Ans[2]+Ans[4] )%4               == 4-Time[1])
	if( ( Ans[1]+Ans[2]+Ans[3]+Ans[5] )%4        == 4-Time[2])
	if( ( Ans[6]+Ans[2]+Ans[3] )%4               == 4-Time[3])
	if( ( Ans[1]+Ans[4]+Ans[7]+Ans[5] )%4        == 4-Time[4]) 
	if( ( Ans[3]+Ans[5]+Ans[9]+Ans[1]+Ans[7] )%4 == 4-Time[5])//利用公式判断 
	if( ( Ans[3]+Ans[5]+Ans[9]+Ans[6] )%4        == 4-Time[6])
	if( ( Ans[7]+Ans[4]+Ans[8] )%4               == 4-Time[7])
	if( ( Ans[8]+Ans[5]+Ans[9]+Ans[7] )%4        == 4-Time[8])
	if( ( Ans[6]+Ans[8]+Ans[9] )%4               == 4-Time[9])
	{
		for(int i=1;i<10;i++)
		if(Ans[i]>0)//这里我卡了挺久(阅读理解差) 
		for(int j=1;j<=Ans[i];j++)//不是输出每一种做法的次数 
		printf("%d ",i);//而是输出具体步骤 
		
		return 0;
	}
	
	return 0;
}
```

~~快得一批~~

(本人第一篇题解，求过)

---

## 作者：Ousmane_Dembele (赞：7)

~~贡献O(1)暴力~~

枚举九种方案在每种方案使用4次以下的情况下算出所有可以的情况，排序输出最小的

4^9=262144(手算不知道对不对）肯定没有时间问题，空间嘛就更没问题了。

虽然时间没问题，但是时间越少越好嘛，观察一下

- 1.ABDE
- 2.ABC
- 3.BCEF
- 4.ADG
- 5.BDEFH
- 6.CFI
- 7.DEGH
- 8.GHI
- 9.EFHI

含A的只有1.2.4.所以枚举到第4个就可以特判第一个时间表可不可以了

~~其实我们假如把序列变换一下还可以更省时间，但没必要了~~

calc完成后进入计算环节，排序一下sum然后输出第一个就行了，下面请看我比之前那几位好看一点的代码

```
#include<bits/stdc++.h>
using namespace std;
int a[10],cnt;
struct node{
    int g[100];
    int sum,cntss;//sum是和，cntss是ans[i].g[]前多少个数非0
}ans[10000];
bool cmp(node a,node b){
    return a.sum<b.sum;
}
void add(int aa,int b,int c,int d,int e,int f,int g,int h,int i){
    int cnts=0;//赋初值
    cnt++;
    for(int j=1;j<=aa;j++)
       ans[cnt].g[++cnts]=1;//em……过于丑陋
    for(int j=1;j<=b;j++)
       ans[cnt].g[++cnts]=2;//全部压入
    for(int j=1;j<=c;j++)
       ans[cnt].g[++cnts]=3;
    for(int j=1;j<=d;j++)
       ans[cnt].g[++cnts]=4;
    for(int j=1;j<=e;j++)
       ans[cnt].g[++cnts]=5;
    for(int j=1;j<=f;j++)
       ans[cnt].g[++cnts]=6;
    for(int j=1;j<=g;j++)
       ans[cnt].g[++cnts]=7;
    for(int j=1;j<=h;j++)
       ans[cnt].g[++cnts]=8;
    for(int j=1;j<=i;j++)
       ans[cnt].g[++cnts]=9;
    for(int j=1;j<=cnts;j++)
       ans[cnt].sum+=ans[cnt].g[i];//相加
    ans[cnt].cntss=cnts;//em
}
void print(){
    for(int i=1;i<ans[1].cntss;i++)//及其丑陋的输出
       cout<<ans[1].g[i]<<" ";
    cout<<ans[1].g[ans[1].cntss];
    exit(0);
}
void init(){
    for(int i=1;i<=9;i++){cin>>a[i];a[i]=a[i]/3;a[i]=4-a[i];}
    //在这些操作后a[i]的值就是后面和i有关的操作的和%4的值
}
void solve(){
    sort(ans+1,ans+cnt+1,cmp);
    print();
}
void calc(){
    for(int aa=0;aa<=3;aa++)
       for(int b=0;b<=3;b++)
          for(int c=0;c<=3;c++) 
             for(int d=0;d<=3;d++)
                if((aa+b+d)%4==a[1])//省去一些复杂度
                   for(int e=0;e<=3;e++)
                      if((aa+b+c+e)%4==a[2])
                         for(int f=0;f<=3;f++)
                            if((b+c+f)%4==a[3])//又省去一些复杂度
                                for(int g=0;g<=3;g++)
                                    if((aa+d+e+g)%4==a[4])
                                        for(int h=0;h<=3;h++)
                                           if((d+g+h)%4==a[7])
                                               for(int i=0;i<=3;i++)
                                                  if((aa+c+e+g+i)%4==a[5]&&(c+e+f+i)%4==a[6]&&(e+g+h+i)%4==a[8]&&(f+h+i)%4==a[9])add(aa,b,c,d,e,f,g,h,i);//这么丑
}
int main(){
    init();//输入
    calc();//暴力
    solve();//排序输出
    return 0;                        
}
```

---

## 作者：Y_B_Y (赞：6)

## 枚举的时间复杂度可以优化（3个循环）

我们先将输入的每一个数化为它最少还要几次变成12记为c[i]（如：9->1）{公式（4-（输入的数/3）}；

由题意可知：

1钟可受开关1，2，4控制

2钟可受开关1，2，3，5控制

3钟可受开关2，3，6控制

4钟可受开关1，4，5，7控制

5钟可受开关1，3，5，7，9控制

6钟可受开关3，5，6，9控制

7钟可受开关4，7，8控制

8钟可受开关5，7，8，9控制

9钟可受开关4，8，9控制



------------


用p1-p9表示开关使用的次数，所以当

#### （可以影响i钟的开关的总使用次数%4）与c[i]相等时

就可以将钟i移动到12；

我们可以列一个表来表示可以的情况


|号数   |可以的情况|
| :----------- | :----------- |
|  1|c[1]==(p1+p2+p4)%4
| 2 | c[2]==(p1+p2+p3+p5)%4   |
|  3|  c[3]==(p3+p2+p6)%4  |
| 4 |c[4]==(p1+p4+p5+p7)%4    |
|  5|  c[5]==(p1+p3+p5+p7+p9)%4  |
|  6| c[6]==(p3+p5+p6+p9)%4   |
|  7| c[7]==(p8+p4+p7)%4   |
|  8| c[8]==(p5+p7+p8+p9)%4   |
|  9|   c[9]==(p6+p8+p9)%4 |


------------


# 重点

观察可以发现p4与c[1]-p1-p2可能有一些关系

这些关系可以表示为p4=order（c[1]-p1-p2）

其中order是一个函数

int order(int x)

{

   if(x>=0) return x%4;
   
	else return (x+4*1024)%4;//其中1024可以换成任意一个较大的数
}



#### 同理

p5=order(c[2]-p1-p2-p3);

p6=order(c[3]-p2-p3);
                    
p7=order(c[4]-p1-p4-p5);
                    
p8=order(c[7]-p4-p7);
                    
p9=order(c[9]-p6-p8);

### 解释

order函数的意思就是表示最少还要几次才能到12

当pl=order（c[i]-pj-pk-p..）【表示某一种情况】大于零时说明还没有超过12，pl还需（c[i]-pj-pk-p..）%4次才可以到12

当它小于零时，表示它以超过12已经绕了y圈（y>=1）,所以它需要加上一个4的倍数再去模四，因为假如当它为-1与-5时，钟指针是在同一个地方（返回的数相等）

其实
(x+（4* 1024）)%4=(（4*n+x）+(1024-n)*4)%4=（4*n+x）%4+((1024-n)*4)%4==(4*n+x)%4【因为0<=4*n+x<4，所以才要一个较大的数,也说明了为什么要用这个式子】

#### 所以只要枚举p1，p2，p3就可以表示出所有的情况；


------------


#### 至于如何输出：就是从p1-p9使用几次就输几个


------------


上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[10],j;
int order(int x)//函数本体
{
	if(x>=0) return x%4;
	else return (x+4*1024)%4;
}
int main()
{
	for(int p=1;p<=9;p++)
	{
		cin>>j;
		c[p]=4-(j/3);//得c[1]
	}
	for(int p1=0;p1<=3;p1++)//枚举
	{
		for(int p2=0;p2<=3;p2++)
		{
			for(int p3=0;p3<=3;p3++)
			{
					int p4=order(c[1]-p1-p2);//得出其他数据
					int p5=order(c[2]-p1-p2-p3);
					int p6=order(c[3]-p2-p3);
					int p7=order(c[4]-p1-p4-p5);
					int p8=order(c[7]-p4-p7);
					int p9=order(c[9]-p6-p8);
				if(c[1]==(p1+p2+p4)%4&&c[2]==(p1+p2+p3+p5)%4&&c[3]==(p3+p2+p6)%4&&c[4]==(p1+p4+p5+p7)%4&&
				c[5]==(p1+p3+p5+p7+p9)%4&&c[6]==(p3+p5+p6+p9)%4&&c[7]==(p8+p4+p7)%4&&c[8]==(p5+p7+p8+p9)%4&&
				c[9]==(p6+p8+p9)%4)//判断
				{
					for(int p=1;p<=p1;p++) cout<<1<<' ';
					for(int p=1;p<=p2;p++) cout<<2<<' ';
					for(int p=1;p<=p3;p++) cout<<3<<' ';
					for(int p=1;p<=p4;p++) cout<<4<<' ';
					for(int p=1;p<=p5;p++) cout<<5<<' ';
					for(int p=1;p<=p6;p++) cout<<6<<' ';
					for(int p=1;p<=p7;p++) cout<<7<<' ';
					for(int p=1;p<=p8;p++) cout<<8<<' ';
					for(int p=1;p<=p9;p++) cout<<9<<' ';//输出
					return 0;
				}
			}
		}
	}
    return 0；
}
```

                    

---

## 作者：神一般的世界 (赞：6)

萌新第一次题解

这道题是一道非常裸的搜索

```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#include<iostream>
using namespace std;
const int mv[10][10]={
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,0,1,1,0,0,0,0},
    {0,1,1,1,0,0,0,0,0,0},
    {0,0,1,1,0,1,1,0,0,0},
    {0,1,0,0,1,0,0,1,0,0},
    {0,0,1,0,1,1,1,0,1,0},
    {0,0,0,1,0,0,1,0,0,1},
    {0,0,0,0,1,1,0,1,1,0},
    {0,0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,1,1,0,1,1},
};
int dos[100],ansd[100];
int n,did[1000000],ansl;
int done[10];
int move(int k,int p){//用位运算直接改变状态 
    int t=k,t1,t2,t3;
    for(int i=1;i<=9;i++){ 
        if(mv[p][i]){
            int s=2*(9-i);
            t1=t&(3<<s);
            t2=((1<<s)+t1)&(3<<s);
            t=t&(~(3<<s));
            t=t2|t;
        }
    }
    return t;
}
void dfs(int x,int k){//略加剪枝，如有不足，请大神指点 
    if(k>ansl||k>40)return;
    if(x==0){
        if(ansl>k){
            for(int i=1;i<=k;i++){
                ansd[i]=dos[i];
            }
            ansl=k;
        }
        return;
    }
    if(did[x]==1)return;
    did[x]=1;
    for(int i=1;i<=9;i++){
        if(done[i]<3){
            done[i]++;
            int t=x;
            t=move(t,i);
            dos[k+1]=i;
            dfs(t,k+1);
            done[i]--;
        }
    }
}
int main(){
    int x=0;ansl=1<<20;
    for(int i=1;i<=9;i++){
        scanf("%d",&x);
        n=n<<2;n+=((x/3)%4);
```
}//时钟只有2^2种状态，于是心中一喜,hahahaha
    dfs(n,0);    

    for(int i=1;i<=ansl;i++)printf("%d ",ansd[i]);

}

---

## 作者：aRenBigFather (赞：5)

 查看完整题解代码请点这里:[NOIPiao51](https://www.noipiao.cf/view/51)
 
 就是正常的暴力bfs
```cpp
void bfs(){
    node tt;
    for(int j=0;j<9;j++){
        tt.state[j] = state[j];
    }
    tt.ans = "";
    q.push(tt);
    while(!q.empty()){
        node now = q.front();
        q.pop();
        //if(vis.count(now.ans)) continue;
        //cout << now.ans << endl;
        if(checkOK(now.state)){
            ans = now.ans;
            return;
        }
        for(int i=0;i<9;i++){
            node nextn = now;
            for(int k=0;k<9;k++){
                nextn.state[k] = (nextn.state[k] + movement[i][k]) % 5;
                if(nextn.state[k] == 0) nextn.state[k] = 1;
            }
            nextn.ans += (char)('0'+i+1);
            if(!vis[nextn.state[0]][nextn.state[1]][nextn.state[2]][nextn.state[3]][nextn.state[4]][nextn.state[5]][nextn.state[6]][nextn.state[7]][nextn.state[8]]){
                q.push(nextn);
                vis[nextn.state[0]][nextn.state[1]][nextn.state[2]][nextn.state[3]][nextn.state[4]][nextn.state[5]][nextn.state[6]][nextn.state[7]][nextn.state[8]] = true;
            }
        }
    }
}
```
 不过要注意的是记录已经出现过的情况
 
 如果已经出现过就不必向下继续搜索了，否则搜索了也是无用功
 
 这里用一个笨但是很有效地方法，9维数组分别记录每一个状态
```cpp
bool vis[5][5][5][5][5][5][5][5][5];
```
然后是完整代码
```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
struct node{
    int state[9];
    string ans;
};
const bool movement[9][9] = 
{
// A B C D E F G H I
// 1 2 3 4 5 6 7 8 9
  {1,1,0,1,1,0,0,0,0},
  {1,1,1,0,0,0,0,0,0},
  {0,1,1,0,1,1,0,0,0},
  {1,0,0,1,0,0,1,0,0},
  {0,1,0,1,1,1,0,1,0},
  {0,0,1,0,0,1,0,0,1},
  {0,0,0,1,1,0,1,1,0},
  {0,0,0,0,0,0,1,1,1},
  {0,0,0,0,1,1,0,1,1}
};
int state[9];
inline bool checkOK(int state[]){
    for(int i=0;i<9;i++){
        if(state[i] != 4) return false;
    }
    return true;
}
string ans = "";
bool vis[5][5][5][5][5][5][5][5][5];
queue<node> q;
void bfs(){
    node tt;
    for(int j=0;j<9;j++){
        tt.state[j] = state[j];
    }
    tt.ans = "";
    q.push(tt);
    while(!q.empty()){
        node now = q.front();
        q.pop();
        //if(vis.count(now.ans)) continue;
        //cout << now.ans << endl;
        if(checkOK(now.state)){
            ans = now.ans;
            return;
        }
        for(int i=0;i<9;i++){
            node nextn = now;
            for(int k=0;k<9;k++){
                nextn.state[k] = (nextn.state[k] + movement[i][k]) % 5;
                if(nextn.state[k] == 0) nextn.state[k] = 1;
            }
            nextn.ans += (char)('0'+i+1);
            if(!vis[nextn.state[0]][nextn.state[1]][nextn.state[2]][nextn.state[3]][nextn.state[4]][nextn.state[5]][nextn.state[6]][nextn.state[7]][nextn.state[8]]){
                q.push(nextn);
                vis[nextn.state[0]][nextn.state[1]][nextn.state[2]][nextn.state[3]][nextn.state[4]][nextn.state[5]][nextn.state[6]][nextn.state[7]][nextn.state[8]] = true;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    for(int i=0;i<9;i++){
        int time;
        //scanf("%d",&time);
        cin >> time;
        state[i] = time / 3;
    }
    memset(vis,false,sizeof vis);
    bfs();
    for(int i=0;i<ans.size();i++){
        if(i == 0){
            cout << ans[i];
        }else{
            cout << " " << ans[i];
        }
    }
    return 0;
}
```

---

## 作者：2016jzy (赞：3)

楼下几位的代码太难看了，看我这个多清爽。。

（大佬们别打我T-T）

显而易见，当然是广搜啦！

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<string>
#include<cstdlib>
#include<cmath>    //一坨头文件
using namespace std;
int list[1000007]={0};
string data[1000000];
int next[1000000]={0},cnt;
string s[10]={"","1245","123","2356","147","24568","369","4578","789","5689"};  //比那矩阵吼看多了对不对————这段表示移动方法
string a;
struct clo
{
    string sz,bz;
}tim;    //结构体
queue<clo>q;
int ok(string h)
{
    int sum=0;
    for(int i=0;i<h.size();i++)sum=sum*33+h[i];
    sum=abs(sum%1000007);
    int u=list[sum];
    while(u)
    {
        if(data[u]==h)return 0;
        u=next[u];
    }
    data[++cnt]=h;
    next[cnt]=list[sum];
    list[sum]=cnt;
    return 1;
}   //此题一定要去重！！不过我觉得哈希代码真的比九维数组好看多了，虽然时间慢了一些~\(^o^)/
int bfs()
{
    tim.sz=a;tim.bz="";
    q.push(tim);       //初始化+入队
    while(q.size())
    {
        clo p=q.front();
        q.pop();
        for(int i=1;i<=9;i++)
        {
            tim=p;
            for(int j=0;j<s[i].size();j++)
            {
                int k=(char)(tim.sz[s[i][j]-49]-48)+1;
                if(k>4)k=1;
                tim.sz[s[i][j]-49]=k+48;
            }   //修改时钟时间
            tim.bz+=i+48;
            if(tim.sz=="444444444")  //判断是否达到目标
            {
                for(int j=0;j<tim.bz.size();j++)cout<<tim.bz[j]<<" ";
                cout<<endl;            //输出结果
                return 0;
            }
            if(ok(tim.sz))q.push(tim);    //如果没有重复，则入队
        }
    }
}       //广搜代码
int main()
{
    for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=3;j++)
        {
            int t;
            cin>>t;       //输入
            t/=3;
            a=a+(char)(t+48);     //将时钟矩阵压成一个字符串
        }
    }
    bfs();      //广搜大法吼！！
    return 0;
}
```

---

## 作者：Minclxc (赞：2)

写个二进制的状态转移

```cpp
const int c[10][6]={{},{4,8,7,5,4,0},{3,8,7,6,0,0},{4,7,6,4,3,0},{3,8,5,2,0,0},{5,7,5,4,3,1},{3,6,3,0},{4,5,4,2,1},{3,2,1,0},{4,4,3,1,0}};
//9种转移，[0]表示移动的个数，[i](1<=i<=[0])表示左移位数（计算方法：9-移动的时钟编号）
//每个时钟用两位二进制数表示，样例是111100101010100110
fj(1,c[i][0]){
                if(y&(1<<(c[i][j]*2)))//如果第二位是1
        y^=(1<<(c[i][j]*2+1));//第一位取反
                y^=(1<<(c[i][j]*2));//第二位取反
            }
```
00->01  01->10  10->11  11->00


---

## 作者：BallBall (赞：1)

难看的广搜。。。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int mm=1<<19;
const int cc[9][9]= {{3,3,0,3,3,0,0,0,0},
    {3,3,3,0,0,0,0,0,0},
    {0,3,3,0,3,3,0,0,0},
    {3,0,0,3,0,0,3,0,0},
    {0,3,0,3,3,3,0,3,0},
    {0,0,3,0,0,3,0,0,3},
    {0,0,0,3,3,0,3,3,0},
    {0,0,0,0,0,0,3,3,3},
    {0,0,0,0,3,3,0,3,3}
};
bool v[4][4][4][4][4][4][4][4][4];
struct Node
{
    int status[9];
    int step,path;
};
Node q[mm];
int cl[9];
int head,tail;
bool bb=1;
int ans;
bool isEnd(int c[])
{
    for(int i=0; i<9; i++)
        if(c[i]!=0)return 0;
    return 1;
}
void printout(int i)
{
    if(q[i].path<0)return;
    printout(q[i].path);
    printf("%d ",q[i].step+1);
}
int main()
{
    //freopen(".in" ,"r",stdin)
    //freopen(".out" ,"w",stdout)
    for(int i=0; i<9; i++)
    {
        cin>>cl[i];
        cl[i]%=12;
    }
    v[cl[0]/3][cl[1]/3][cl[2]/3][cl[3]/3][cl[4]/3][cl[5]/3][cl[6]/3][cl[7]/3][cl[8]/3]=1;
    if(v[0][0][0][0][0][0][0][0][0])
        return 0;
    for(int i=0; i<9; i++)
        q[0].status[i]=cl[i];
    q[0].step=-1;
    q[0].path=-1;
    head=tail=0;
    while(head<=tail&&tail<mm-10&&bb)
    {
        int tc[9];
        for(int k=0; k<9; k++)
        {
            for(int i=0; i<9; i++)
                tc[i]=(q[head].status[i]+cc[k][i])%12;
            if(v[tc[0]/3][tc[1]/3][tc[2]/3][tc[3]/3][tc[4]/3][tc[5]/3][tc[6]/3][tc[7]/3][tc[8]/3])continue;
            v[tc[0]/3][tc[1]/3][tc[2]/3][tc[3]/3][tc[4]/3][tc[5]/3][tc[6]/3][tc[7]/3][tc[8]/3]=1;
            ++tail;
            for(int i=0; i<9; i++)
                q[tail].status[i]=tc[i];
            q[tail].step=k;
            q[tail].path=head;
            if(v[0][0][0][0][0][0][0][0][0])
            {
                ans=tail;
                bb=0;
                break;
            }
        }
        ++head;
    }
    printout(ans);
    return 0;
}
```

---

## 作者：Undefined_Myth (赞：1)

```cpp
#include<cstdio>
#include<cstdlib>
//#include<iostream>
//#include<algorithm>
using namespace std;
#define N 262145  //为4^9 一个种有4种状态，有9个钟，所以这整个布局就有4^9个状态 
const int size[9] = {4, 3, 4, 3, 5, 3, 4, 3, 4};
const int dir[9][6] = {{0, 1, 3, 4}, {0, 1, 2}, {1, 2, 4, 5},
                       {0, 3, 6}, {1, 3, 4, 5, 7}, {2, 5, 8},
                       {3, 4, 6, 7}, {6, 7, 8}, {4, 5, 7, 8}};//从0到8 表示从第1个时钟到第9个时钟 
int T,a[4][4],b[4][4],q[N],step[N],op[N][30];//op为序列顺序 
void bfs(int st)
{
    int i,j;
    for(i=0;i<N;i++)//一定要从0开始！因为全是12时就是step[0]要执行后面if(step[]==-1)后面的操作必须先要赋初始值为-1 
        step[i]=-1;//初始化
    int l=1,r=0;
    q[++r]=st;    step[st]=0;//step表示到达这个4进制转成的十进制编码[]的步骤数 
    while(l<=r)
    {
        int cur=q[l++];
        int x=cur;
        for(i=1;i<=3;i++)
            for(j=1;j<=3;j++,x=x/4)//这个=赋值一定要写上 
                a[i][j]=x%4;//倒叙储存转成的4进制——翻译 
        for(int k=0;k<9;k++)//枚举操作
        {
            for(i=1;i<=3;i++)
                for(j=1;j<=3;j++)
                    b[i][j]=a[i][j];//复制棋盘    
            for(i=0;i<size[k];i++)//dir数组是从0开始的 
            {
                int x=dir[k][i]/3+1;
                int y=dir[k][i]%3+1;//注意实际的布局和dir数组有点差异
                //当然我们也可以让实际布局从0开始来使得更加方便 
                b[x][y]=(b[x][y]+1)%4;//使得顺时针旋转90度而且不出这4种情况 
            }
            int code=0,m=1;
            for(i=1;i<=3;i++)
                for(j=1;j<=3;j++,m*=4)
                    code+=b[i][j]*m;
            if(step[code]==-1)//之前没有被遍历过
            {
                step[code]=step[cur]+1;//只多了一步 
                for(i=1;i<=step[cur];i++)//把之前的所有顺序赋值，step已经记录了这些顺序的总量有多少方便枚举轮数
                    op[code][i]=op[cur][i];//后面的i表示这个顺序是第几个
                op[code][step[cur]+1]=k+1;//如果后面写i，那么会错！因为i在最后还加了1！！
                //写k+1是因为题目中是从1开始的，而我们的dir枚举是从0开始的
                q[++r]=code; 
                if(code==0)//这个代表全部是12的情况，我们这里是把12的4进制定义为0 来方便计算
                    return ;
            } 
        }  
    }
}
int main() 
{
    int x;
    for(int i=1,m=1;i<=3;i++)
        for(int j=1;j<=3;j++,m*=4)//注意这是个严格的转4进制的方法 
        {
            scanf("%d",&x);
                T+=((x/3)%4)*m;//我们可以这么操作使得到这个状态的4进制表示 
        }
    bfs(T);
    for(int i=1;i<=step[0];i++)//step[0]表示到全部是12 的步骤数
        printf("%d%c",op[0][i],i==step[0]?'\n':' ');//op前面是指的编码，后面是指的顺序中每一个元素的顺序坐标什么的 
        return 0; 
    }
```
/\*我们在这里用一个4进制串来表示312、3、6、9点的情况
dir代表要进行操作的时钟编码

size表示一次移动要涉及到的时钟个数，方便之后枚举

用step初始值为-1 并之后先判断他是否为-1 再进行更新操作，我们就可以实现一定的记忆化搜索

并且保证第一次到这个状态时的步骤最小

我们从小的开始往大的 枚举，那么就可以解决输出时的连接数最小的问题了 \*/


---

## 作者：zx2003 (赞：1)

直接通过二进制穷举状态



```cpp
const a:array[1..9,1..9] of longint=
((1,1,0,1,1,0,0,0,0),
(1,1,1,0,0,0,0,0,0),
(0,1,1,0,1,1,0,0,0),
(1,0,0,1,0,0,1,0,0),
(0,1,0,1,1,1,0,1,0),
(0,0,1,0,0,1,0,0,1),
(0,0,0,1,1,0,1,1,0),
(0,0,0,0,0,0,1,1,1),
(0,0,0,0,1,1,0,1,1));
var
 b,c,d,ans:array[1..9] of longint;
 e:array[0..27] of longint;
 i,min,s,xb,j,t,x,k:longint;
 f:boolean;
begin
 for i:=1 to 9 do read(b[i]);
 min:=1 shl 30;
 for j:=0 to 1 shl 19-1 do//连续两位二进制表示该操作进行次数,次数为0,1,2,3，因为同一个操作操作4次与不操作效果一样
 begin
  t:=j;
  for i:=9 downto 1 do
  begin
   d[i]:=t xor (t shr 1 shl 1);
   t:=t shr 1;
   x:=t xor (t shr 1 shl 1);
   d[i]:=x shl 1 or d[i];
   t:=t shr 1
  end;//读取
  c:=b;
  f:=true;
  for i:=1 to 9 do
   for k:=1 to 9 do
    inc(c[k],d[i]*3*a[i,k]);
  for i:=1 to 9 do
   if c[i] mod 12<>0 then
   begin
    f:=false;
```
break

```cpp
   end;
  if f then
  begin
   s:=0;
   for i:=1 to 9 do inc(s,d[i]);
   if s<min then
   begin
    min:=s;
    ans:=d
   end
  end
 end;
 for i:=1 to 9 do
  for s:=1 to ans[i] do
  begin
   inc(xb);
   e[xb]:=i
  end;
 for i:=1 to xb-1 do write(e[i],' ');
 writeln(e[xb])
end.

```

---

## 作者：1jia1 (赞：1)

这道题可以把二维化一维，然后就会简单很多了。

核心思路：江3\*3的二维数组改成9的一维数组，建立一个二维表，存每种操作影响的时钟。然后广搜，用九维数组判当前状态是否与之前的状态相同（这个很重要）。

```cpp
-#include <cstdio>-
-#include <cstdlib>-
-using namespace std;-
-struct doby{-
-    short a[10],mov[61],no;-
-}q[262145];-
-int h=0,t=1,move[10][10]={---move为记录每种操作影响的时钟
```
-    0,0,0,0,0,0,0,0,0,0,-
-    0,1,1,0,1,1,0,0,0,0,-

-    0,1,1,1,0,0,0,0,0,0,-

-    0,0,1,1,0,1,1,0,0,0,-

-    0,1,0,0,1,0,0,1,0,0,-

-    0,0,1,0,1,1,1,0,1,0,-

-    0,0,0,1,0,0,1,0,0,1,-

-    0,0,0,0,1,1,0,1,1,0,-

-    0,0,0,0,0,0,0,1,1,1,-

-    0,0,0,0,0,1,1,0,1,1,-

```cpp
-    },start[10];-
-bool f[5][5][5][5][5][5][5][5][5];---判重数组
-int main()-
-{-
-    for(register int i=1;i<=9;i++)scanf("%d",&start[i]),start[i]/=3;---把每个时间÷3，3,6,9,12改成1,2,3,4，会让数组变小
-    for(register int i=1;i<=9;i++)q[1].a[i]=start[i];
-    f[start[1]][start[2]][start[3]][start[4]][start[5]][start[6]][start[7]][start[8]][start[9]]=1;---记录当前状态
-    q[1].no=0;-
-    int p=1;-
-            for(register int i=1;i<=9;i++)---先判断初始状态是否符合要求
-            {-
-                if(q[1].a[i]!=4)-
-                {-
-                    p=0;-
-                    break;-
-                }-
-            }-
-            if(p)return 0;-
-    while(h<t)-
-    {-
    -    h++;-
-        for(register int k=1;k<=9;k++)---九种操作
-        {-
-            t++;-
-            register int p=0;-
-            for(register int i=1;i<=9;i++)---操作时钟
-            {-
-                q[t].a[i]=q[h].a[i]+move[k][i];-
    -            if(q[t].a[i]==5)q[t].a[i]=1;-
-            }-
-            if(f[q[t].a[1]][q[t].a[2]][q[t].a[3]][q[t].a[4]][q[t].a[5]][q[t].a[6]][q[t].a[7]][q[t].a[8]][q[t].a[9]]==1)---判重，如果当前状态与之前状态相同
-            {-
-            t--;---则无视本次操作
-                continue;-
-            }-
-            else f[q[t].a[1]][q[t].a[2]][q[t].a[3]][q[t].a[4]][q[t].a[5]][q[t].a[6]][q[t].a[7]][q[t].a[8]][q[t].a[9]]=1;-记录当前状态
-            for(register int i=1;i<=q[h].no;i++)---记步数
-            {-
-                q[t].mov[i]=q[h].mov[i];-
-            }-
-            q[t].no=q[h].no+1;-
-            q[t].mov[q[t].no]=k;-
-            p=1;-
-            for(register int i=1;i<=9;i++)---判断是否符合标准
-            {-
-            if(q[t].a[i]!=4)-
-                {-
-                    p=0;-
-                    break;-
-                }-
-            }-
-            if(p)-
-            {-
-                for(register int i=1;i<=q[t].no;i++)-
-                {-
-                    printf("%d ",q[t].mov[i]);-
-                }-
-                return 0;-
-            }-
-        }-
-    }-
-    return 0;-
-}-
```

---

## 作者：Snow_Dreams (赞：0)

这道题有一个非常重要的性质，时钟转4次会回到原始状态，所以只需要枚举0~3就可以了

然后就是爆搜，通过9^3的时间复杂度就可以AC此题

然后我还是看了一下题目的标签：进制

然后这道题就可以转化为一个四进制的问题，如果超过4就自然溢出就可以了

可以自己定义一个容器也可以宏替换，将代码枚举部分全不断的模四取余

```cpp
单独的一行包括一个用空格分开的将所有指针指向 1212 点的最短移动顺序的列表。

如果有多种方案，输出那种使其连接起来的数字最小的方案。(举例来说 5 2 4 6 < 9 3 1 1 )。
```
但是有上面的那一行

所以我们在操作的同时还需要记录每次操作，可以通过vis来看，
只用定义一个，如果数更小就直接更新

---

