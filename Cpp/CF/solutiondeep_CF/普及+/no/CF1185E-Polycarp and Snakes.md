# 题目信息

# Polycarp and Snakes

## 题目描述

After a hard-working week Polycarp prefers to have fun. Polycarp's favorite entertainment is drawing snakes. He takes a rectangular checkered sheet of paper of size $ n \times m $ (where $ n $ is the number of rows, $ m $ is the number of columns) and starts to draw snakes in cells.

Polycarp draws snakes with lowercase Latin letters. He always draws the first snake with the symbol 'a', the second snake with the symbol 'b', the third snake with the symbol 'c' and so on. All snakes have their own unique symbol. There are only $ 26 $ letters in the Latin alphabet, Polycarp is very tired and he doesn't want to invent new symbols, so the total number of drawn snakes doesn't exceed $ 26 $ .

Since by the end of the week Polycarp is very tired, he draws snakes as straight lines without bends. So each snake is positioned either vertically or horizontally. Width of any snake equals $ 1 $ , i.e. each snake has size either $ 1 \times l $ or $ l \times 1 $ , where $ l $ is snake's length. Note that snakes can't bend.

When Polycarp draws a new snake, he can use already occupied cells for drawing the snake. In this situation, he draws the snake "over the top" and overwrites the previous value in the cell.

Recently when Polycarp was at work he found a checkered sheet of paper with Latin letters. He wants to know if it is possible to get this sheet of paper from an empty sheet by drawing some snakes according to the rules described above. If it is possible, he is interested in a way to draw snakes.

## 样例 #1

### 输入

```
1
5 6
...a..
..bbb.
...a..
.cccc.
...a..
```

### 输出

```
YES
3
1 4 5 4
2 3 2 5
4 2 4 5
```

## 样例 #2

### 输入

```
3
3 3
...
...
...
4 4
..c.
adda
bbcb
....
3 5
..b..
aaaaa
..b..
```

### 输出

```
YES
0
YES
4
2 1 2 4
3 1 3 4
1 3 3 3
2 2 2 3
NO
```

## 样例 #3

### 输入

```
2
3 3
...
.a.
...
2 2
bb
cc
```

### 输出

```
YES
1
2 2 2 2
YES
3
1 1 1 2
1 1 1 2
2 1 2 2
```

# AI分析结果

### 题目翻译
# 波利亚尔普与蛇

## 题目描述
在忙碌的一周后，波利亚尔普喜欢找点乐子。他最喜欢的娱乐活动是在方格纸上画蛇。他会拿一张大小为 $n \times m$ 的矩形方格纸（其中 $n$ 是行数，$m$ 是列数），然后开始在方格中画蛇。

波利亚尔普用小写拉丁字母来画蛇。他总是用符号 'a' 画第一条蛇，用符号 'b' 画第二条蛇，用符号 'c' 画第三条蛇，依此类推。所有的蛇都有自己独特的符号。由于拉丁字母只有 26 个，而且波利亚尔普很累了，不想发明新的符号，所以他画的蛇的总数不超过 26 条。

由于到周末时波利亚尔普非常疲惫，他画的蛇都是没有弯曲的直线。因此，每条蛇要么是垂直放置，要么是水平放置。每条蛇的宽度都为 1，即每条蛇的尺寸要么是 $1 \times l$，要么是 $l \times 1$，其中 $l$ 是蛇的长度。注意，蛇不能弯曲。

当波利亚尔普画一条新蛇时，他可以使用已经被占用的方格来画这条蛇。在这种情况下，他会在已有的方格上“覆盖”画蛇，并覆盖掉方格中之前的值。

最近，波利亚尔普在工作时发现了一张印有拉丁字母的方格纸。他想知道是否可以按照上述规则，从一张空白的方格纸开始，通过画一些蛇来得到这张方格纸。如果可以，他还想知道画蛇的方法。

## 样例 #1
### 输入
```
1
5 6
...a..
..bbb.
...a..
.cccc.
...a..
```
### 输出
```
YES
3
1 4 5 4
2 3 2 5
4 2 4 5
```

## 样例 #2
### 输入
```
3
3 3
...
...
...
4 4
..c.
adda
bbcb
....
3 5
..b..
aaaaa
..b..
```
### 输出
```
YES
0
YES
4
2 1 2 4
3 1 3 4
1 3 3 3
2 2 2 3
NO
```

## 样例 #3
### 输入
```
2
3 3
...
.a.
...
2 2
bb
cc
```
### 输出
```
YES
1
2 2 2 2
YES
3
1 1 1 2
1 1 1 2
2 1 2 2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟画蛇的过程，判断是否能从空白纸得到给定的方格纸。具体做法是先统计每个字母的位置信息，然后根据字母出现的次数分类讨论，判断其是否能构成直线，最后模拟画蛇过程并检查结果是否与给定方格纸一致。

不同题解在实现细节上有所差异，如数据结构的选择、边界条件的处理等，但整体思路相同。

### 所选题解
- **作者：Eibon (赞：6)，4星**
    - **关键亮点**：思路清晰，使用结构体记录字母的位置信息，代码结构较为清晰，易于理解。
- **作者：__phiu (赞：3)，4星**
    - **关键亮点**：对字母出现的情况进行详细分类讨论，逻辑严谨，代码实现较为规范。
- **作者：Zinc_acetate (赞：0)，4星**
    - **关键亮点**：从标号最大的蛇开始处理，代码简洁，通过标记已处理的方格来判断是否合法。

### 重点代码
#### 作者：Eibon
```cpp
struct node
{
    int ax,ay,bx,by;
};
node num[28],ans[28];
char a[maxn][maxn],mp[maxn][maxn];
// ...
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        cin>>a[i][j];
        if(a[i][j]>='a'&&a[i][j]<='z'){
            int c=a[i][j]-'a'+1;
            num[c].ax=min(num[c].ax,i);num[c].bx=max(num[c].bx,i);
            num[c].ay=min(num[c].ay,j);num[c].by=max(num[c].ay,j);
        }
    }
}
// 判断是否合法并模拟画蛇
for(int i=1;i<=26;i++){
    if(num[i].bx){
        if(num[i].ax!=num[i].bx&&num[i].ay!=num[i].by){
            VIP=0;
            break;
        }
        else{
            cnt=i;nx=num[i].ax;ny=num[i].ay;
            ans[i].ax=num[i].ax;ans[i].bx=num[i].bx;
            ans[i].ay=num[i].ay;ans[i].by=num[i].by;
            for(int x=num[i].ax;x<=num[i].bx;x++){
                for(int y=num[i].ay;y<=num[i].by;y++){
                    mp[x][y]=(char)(i+'a'-1);
                }
            }
        }
    }
}
```
**核心实现思想**：使用结构体 `node` 记录每个字母最左上角和最右下角的坐标，遍历方格纸统计字母位置信息，然后判断每个字母的坐标是否能构成直线，若能则模拟画蛇过程。

#### 作者：__phiu
```cpp
pii a[26];
pair<int,bool>q[26];
int minn[26],maxx[26];
// ...
for(int i=1;i<=n && flag;i++){
    for(int j=1;j<=m && flag;j++){
        char s=c[i][j];
        tmp[i][j]='.';
        if(c[i][j]=='.')
            continue;
        if(a[id].first==0){
            a[id]=mp(i,j);
        }
        else{
            if(q[id].first == 0){
                if(i==a[id].first)
                    q[id] = mp(i,0),minn[id] = a[id].second,maxx[id] = j;
                else if(j==a[id].second)
                    q[id] = mp(j,1),minn[id] = a[id].first,maxx[id] = i;
                else{
                    puts("NO");
                    flag=false;
                    break;
                }
            }
            else{
                if(q[id].second == 0){
                    if(i != q[id].first){
                        puts("NO");
                        flag=false;
                        break;
                    }
                    maxx[id]=j;
                }
                else{
                    if(j != q[id].first){
                        puts("NO");
                        flag=false;
                        break;
                    }
                    maxx[id]=i;
                }
            }
        }
    }
}
// 模拟画蛇
for(int i=0;i<=25;i++){
    if(a[i].first == 0)	continue;
    if(q[i].first ==0 ) tmp[a[i].first][a[i].second] = i+'a'; 
    else{
        if(q[i].second == 0){
            for(int j=minn[i];j<=maxx[i];j++)
                tmp[q[i].first][j] = i+'a';
        }
        else{
            for(int j=minn[i];j<=maxx[i];j++)
                tmp[j][q[i].first] = i+'a';
        }
    }
}
```
**核心实现思想**：使用 `pii` 数组记录每个字母第一次出现的位置，`pair<int, bool>` 数组记录字母是水平还是垂直排列，`minn` 和 `maxx` 数组记录字母的边界。遍历方格纸统计信息，判断字母是否能构成直线，最后模拟画蛇过程。

#### 作者：Zinc_acetate
```cpp
vector<pair<int, int>> a[26];
pair<pair<int, int>, pair<int, int>> ans[26];
// ...
for (int i = k; i >= 0; i--)
{
    if (a[i].size() == 0)
    {
        ans[i] = ans[i + 1];
        continue;
    }
    int mx1, mx2, my1, my2;
    mx1 = my1 = INT_MAX;
    mx2 = my2 = INT_MIN;
    for (auto j : a[i])
    {
        mx1 = min(mx1, j.first);
        mx2 = max(mx2, j.first);
        my1 = min(my1, j.second);
        my2 = max(my2, j.second);
    }
    if (mx1 != mx2 && my1 != my2)
    {
        cout << "NO\n";
        return;
    }
    if (mx1 == mx2)
    {
        ans[i] = make_pair(make_pair(mx1, my1), make_pair(mx2, my2));
        for (int j = my1; j <= my2; j++)
        {
            if (c[mx1][j] != 'a' + i && c[mx1][j] != 0)
            {
                cout << "NO\n";
                return;
            }
            c[mx1][j] = 0;
        }
    }
    else
    {
        ans[i] = make_pair(make_pair(mx1, my1), make_pair(mx2, my2));
        for (int j = mx1; j <= mx2; j++)
        {
            if (c[j][my1] != 'a' + i && c[j][my1] != 0)
            {
                cout << "NO\n";
                return;
            }
            c[j][my1] = 0;
        }
    }
}
```
**核心实现思想**：使用 `vector<pair<int, int>>` 数组记录每个字母的所有位置，从标号最大的蛇开始处理，判断字母是否能构成直线，同时检查直线上的方格是否合法，若合法则标记已处理。

### 关键思路或技巧
- 使用结构体或数组记录字母的位置信息，方便后续处理。
- 对字母出现的次数进行分类讨论，分别处理不同情况。
- 模拟画蛇过程，检查结果是否与给定方格纸一致。

### 拓展思路
同类型题可能会改变画蛇的规则，如蛇可以有弯曲、可以斜着画等，或者改变覆盖规则。类似算法套路都是先统计信息，再根据规则进行模拟和判断。

### 推荐洛谷题目
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
- P1067 [多项式输出](https://www.luogu.com.cn/problem/P1067)
- P1042 [乒乓球](https://www.luogu.com.cn/problem/P1042)

### 个人心得
- **作者：__phiu**：“第五道自主切的紫，写题解纪念一下。” 总结：成功解决一道有一定难度的题目，通过写题解来纪念自己的进步。

---
处理用时：74.85秒