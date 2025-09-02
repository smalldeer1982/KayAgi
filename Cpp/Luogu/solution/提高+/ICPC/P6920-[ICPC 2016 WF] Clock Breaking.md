# [ICPC 2016 WF] Clock Breaking

## 题目描述

在无数不幸的畸形死亡事件以及随之而来的诉讼、和解、抗议和抵制之后，ACME时钟制造商的高管们决定最终解决灾难性的质量控制问题。多年来，人们都知道，他们制造的数字钟的液晶显示屏故障率高得令人无法接受，然而，这些无情的人们却一再未能解决这个问题，甚至未能警告他们不幸的消费者！  

你被邀请担任质量顾问，最终制止了这种疯狂。你的工作是编写一个自动程序，可以测试时钟并发现其显示中的故障。  

这些时钟使用标准的7段LCD显示屏显示所有数字（如图1左侧所示），加上两个小段显示`：`，并以24小时计时法显示所有时间。午夜前一分钟是23:59，午夜是0:00。工作时钟的`：`段始终打开。图1右侧显示了使用七段表示的`0~9`每个数字。  

![图1：每个数字的LCD显示。](https://cdn.luogu.com.cn/upload/image_hosting/3ornshtp.png)   

图1：每个数字的LCD显示。

## 说明/提示

时间限制：3000ms=3s  

空间限制：1048576KB=1024MB=1GB  

出处:2016年国际大学生编程大赛（`ACM-ICPC`）世界总决赛

## 样例 #1

### 输入

```
3
......XX.....XX...XX.
.....X..X...X..X....X
.....X..X.X.X..X....X
.............XX...XX.
.....X..X......X.X..X
.....X..X......X.X..X
......XX.....XX...XX.

......XX.....XX...XX.
.....X..X...X..X....X
.....X..X.X.X..X....X
.............XX...XX.
.....X..X......X.X..X
.....X..X......X.X..X
......XX.....XX...XX.

.............XX...XX.
........X...X..X....X
........X.X.X..X....X
.............XX......
........X...X..X.X..X
........X...X..X.X..X
......XX.....XX...XX.
```

### 输出

```
.??...WW.....??...??.
?..?.W..?...?..1.0..?
?..?.W..?.?.?..1.0..?
.??...??.....11...WW.
?..?.W..?.0.W..?.1..?
?..?.W..?...W..?.1..?
.??...11.....??...??.
```

## 样例 #2

### 输入

```
2
......XX.....XX...XX.
...X....X...X..X.X..X
...X....X.X.X..X.X..X
......XX..........XX.
...X.X....X.X..X.X..X
...X.X......X..X.X..X
......XX.....XX...XX.

......XX.....XX......
...X....X...X..X.....
...X....X.X.X..X.....
......XX.............
...X.X....X.X..X.....
...X.X......X..X.....
......XX.....XX......
```

### 输出

```
impossible
```

# 题解

## 作者：__log__ (赞：9)

本来是校内训练挑的题，结果[调了 4h](https://www.luogu.com.cn/record/146970659)。调着调着玩起了面向数据编程。

不管各位的世界有没有昼夜的概念，总之先祝您早上中午晚上好！……
## 题目描述
给定若干个连续时刻的电子钟的样子，分析每一个液晶点的运转情况是否正常。

运转情况具体如下：
1. 工作正常：该位置输出 `W`。
2. 永远亮着：该位置输出 `1`。
3. 永远不亮：该位置输出 `0`。
4. 可能有多种情况：输出 `?`。

## 题目分析
你希望直接从这堆坏掉的钟瞅出钟代表的时间可以说是不可能的（不信你自己看样例 $1$）。但是如果用某种办法得知了钟代表的时间，可以做到事半功倍的效果。

所以我们枚举起始位置代表的分钟数，用 `check(h, m)` 封装分析起始位置为 $h$ 时 $m$ 分的情况。

```cpp
for(int i = 0; i <= 23; ++i)
    for(int j = 0; j <= 59; ++j)
        check(i, j);
```
跑 `check(i, j)` 时可能会遇到这个时刻与钟表相矛盾的情况。所以若每个时刻都与钟表矛盾，就无解了。
```cpp
if(!flag) {
    cout << "impossible";
    return 0;
}
```
## 这个 `check` 又要怎么写？？？
`check(i, j)` 内用 `ans1` 数组记录起始时刻为 $i$ 时 $j$ 分钟的运转情况。每次计算先把 `ans1` 初始化，把没有液晶的地方变成 `.`，剩下的地方变成 `A` 表示还没分析出来。
```cpp
int a[5] = {0, 1, 4, 7}, b[5] = {0, 2, 3, 5, 6};
int c[10] = {0, 1, 4, 6, 9, 13, 16, 18, 21}, d[10] = {0, 2, 3, 7, 8, 14, 15, 19, 20}, e[10] = {0, 5, 10, 12, 17};

for(int i = 1; i <= 7; ++i)
    for(int j = 1; j <= 21; ++j)
        ans1[i][j] = 'A';
for(int i = 1; i <= 8; ++i) {
    for(int j = 1; j <= 3; ++j) ans1[a[j]][c[i]] = '.';
    for(int j = 1; j <= 4; ++j) ans1[b[j]][d[i]] = '.';
}
for(int i = 1; i <= 4; ++i) for(int j = 1; j <= 7; ++j) ans1[j][e[i]] = '.';
ans1[1][11] = ans1[2][11] = ans1[4][11] = ans1[6][11] = ans1[7][11] =  '.';
```
~~我把它叫做初始化半自动机。~~

对于每一个钟表，如果四个数字中有一个与钟表矛盾，就直接 `return` 掉（$x$ 表示现在的小时数，$y$ 表示分钟数）。

`cnum(id, num, base, flag1)` 表示数字 $num$ 能不能放进钟表对应位置里，$flag1$ 代表数字是否为小时数的十位（要特判）。
```cpp
for(int i = 1; i <= n; ++i) {
    if(cnum(i, x / 10, 0, 1) || cnum(i, x % 10, 5, 0) || cnum(i, y / 10, 12, 0) || cnum(i, y % 10, 17, 0)) return;
    ++y;
    if(y == 60) x++, y = 0;
    if(x >= 24) x = 0;
}
```
### 判断数字是否矛盾
输入的时候记录每一个位置 $(x,y)$ 亮的次数 $t_{(x,y)}$。
1. 如果钟表中某一个位置 $(x,y)$ 不应该亮：
	* 此时亮了，但是这个位置是一直亮的 $(t_{(x,y)}=n)$，那么这个位置就直接填 $1$。
	* 此时亮了，但是这个位置有某个时候关闭了 $(t_{(x,y)}\not=n)$，说明这个位置产生了矛盾（既不是 `W`，也不是 $0$，也不是 $1$），直接返回矛盾。
   * 此时没亮，直接不管，等待进一步判断（这个东西下面会说）。
2. 如果钟表中某一个位置 $(x,y)$ 应该亮：
	* 此时亮了，同样不管。
   * 此时没亮，且一直不亮 $(t_{(x,y)}=0)$，那这个位置只能是 $0$。
   * 此时没亮，且有时候亮 $(t_{(x,y)}\not=0)$，矛盾！

**小时位前导 $0$ 要特判**

tips: 你可以用状压记录每种数字有哪些位置应该亮，哪些不应该亮。
```cpp
int s[10] = {16335, 780, 15423, 3903, 1020, 4083, 16371, 783, 16383, 4095};
// 不是随手敲的

bool cnum(int id, int num, int base, int flag1) {
   if(flag1 && num == 0) {
       for(int i = 1; i <= 14; ++i) {
           int st = s[num] >> (i - 1) & 1, px = ex[i][0], py = base + ex[i][1];
            if(ch[id][px][py] == '.') continue;
            else if(t[px][py] == n) ans1[px][py] = '1';
            else return 1;
       }
        return 0;
    }
    for(int i = 1; i <= 14; ++i) {
        int st = s[num] >> (i - 1) & 1;
        int px = ex[i][0], py = base + ex[i][1];
        if(st == (ch[id][px][py] == 'X')) continue;
        else {
        if(t[px][py] == 0 || t[px][py] == n) ans1[px][py] = ((t[px][py] == n) + 48);
        else return 1;
        }
    }
    return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/36imklxo.png)

（状压每一位代表的位置，$1$ 代表亮，$0$ 代表不亮）
### 最后处理答案
收回前面埋的坑：如果这个时候你还有地方没处理出来（没判出 $01$），那么这些地方肯定是该亮的时候亮了，不该亮的时候关了，就有如下可能：
1. 这个位置不是一直亮着 $(t_{(x,y)}\not=0$  且 $t_{(x,y)}\not=n)$，这里必是 `W`。
2. 这个位置一直亮着，它可能是 `W` 或 `1`，所以填 `?`。
3. 这个位置一直不亮，它可能是 `W` 或 `0`，所以填 `?`。

```cpp
for(int i = 1; i <= 7; ++i) {
    for(int j = 1; j <= 21; ++j) {
        if(ans1[i][j] == 'A' && (t[i][j] == 0 || t[i][j] == n)) ans1[i][j] = '?';
        else if(ans1[i][j] == 'A') ans1[i][j] = 'W';
    }
}
```

以上就是处理 `ans1` 数组的办法。最后合并答案就收工了。
* 如果这是第一次算出答案，就直接 `ans[i][j] = ans1[i][j];`
* 如果不是，就要判断 $ans_{i,j}$ 是否等于 $ans1_{i,j}$，如果不相等，就直接 `ans[i][j] = '?'`（有多种可能所以判为 `?`）。

## Code
早就知道你想白嫖代码了，所以我连防抄袭都懒得放了。

```cpp
// I love Furina forever!
# include <bits/stdc++.h>
using namespace std;

int n, cnt;
int t[8][22];
int a[5] = {0, 1, 4, 7}, b[5] = {0, 2, 3, 5, 6};
int c[10] = {0, 1, 4, 6, 9, 13, 16, 18, 21}, d[10] = {0, 2, 3, 7, 8, 14, 15, 19, 20}, e[10] = {0, 5, 10, 12, 17};
int ex[15][2] = {{0, 0}, {1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 3}, {4, 2}, {3, 1}, {2, 1}, {5, 4}, {6, 4}, {7, 3}, {7, 2}, {6, 1}, {5, 1}};
int s[10] = {16335, 780, 15423, 3903, 1020, 4083, 16371, 783, 16383, 4095};
char ch[105][8][22], ans[8][22], ans1[8][22];
bool flag;

void init() {
    for(int i = 1; i <= 7; ++i)
        for(int j = 1; j <= 21; ++j)
            ans1[i][j] = 'A';
    for(int i = 1; i <= 8; ++i) {
        for(int j = 1; j <= 3; ++j) ans1[a[j]][c[i]] = '.';
        for(int j = 1; j <= 4; ++j) ans1[b[j]][d[i]] = '.';
    }
    for(int i = 1; i <= 4; ++i) for(int j = 1; j <= 7; ++j) ans1[j][e[i]] = '.';
    ans1[1][11] = ans1[2][11] = ans1[4][11] = ans1[6][11] = ans1[7][11] =  '.';
    if(t[3][11] == n) ans1[3][11] = '?';
    else if(t[3][11] == 0) ans1[3][11] = '0';
    else {
        cout << "impossible";
        exit(0);
    }
    if(t[5][11] == n) ans1[5][11] = '?';
    else if(t[5][11] == 0) ans1[5][11] = '0';
    else  {
        cout << "impossible";
        exit(0);
        }
}

bool cnum(int id, int num, int base, int flag1) {
    if(flag1 && num == 0) {
        for(int i = 1; i <= 14; ++i) {
            int st = s[num] >> (i - 1) & 1, px = ex[i][0], py = base + ex[i][1];
            if(ch[id][px][py] == '.') continue;
            else if(t[px][py] == n) ans1[px][py] = '1';
            else return 1;
        }
        return 0;
    }
    for(int i = 1; i <= 14; ++i) {
        int st = s[num] >> (i - 1) & 1;
        int px = ex[i][0], py = base + ex[i][1];
        if(st == (ch[id][px][py] == 'X')) continue;
        else {
            if(t[px][py] == 0 || t[px][py] == n) ans1[px][py] = ((t[px][py] == n) + 48);
            else return 1;
        }
    }
    return 0;
}

void check(int x, int y) {
    init();
    for(int i = 1; i <= n; ++i) {
        if(cnum(i, x / 10, 0, 1) || cnum(i, x % 10, 5, 0) || cnum(i, y / 10, 12, 0) || cnum(i, y % 10, 17, 0)) return;
        ++y;
        if(y == 60) x++, y = 0;
        if(x >= 24) x = 0;
    }
    for(int i = 1; i <= 7; ++i) {
        for(int j = 1; j <= 21; ++j) {
            if(ans1[i][j] == 'A' && (t[i][j] == 0 || t[i][j] == n)) ans1[i][j] = '?';
            else if(ans1[i][j] == 'A') ans1[i][j] = 'W';
        }
    }
    ++cnt;
    if(flag) {
        for(int i = 1; i <= 7; ++i)
            for(int j = 1; j <= 21; ++j)
                if(ans[i][j] != ans1[i][j] || ans[i][j] == '?') ans[i][j] = '?';
    }
        else {
            for(int i = 1; i <= 7; ++i)
                for(int j = 1; j <= 21; ++j) ans[i][j] = ans1[i][j];
    }
    flag = 1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= 7; ++j)
            for(int k = 1; k <= 21; ++k)
                cin >> ch[i][j][k], t[j][k] += (ch[i][j][k] == 'X');
    for(int i = 1; i <= 7; ++i)
        for(int j = 1; j <= 21; ++j) ans[i][j] = '.';
    for(int i = 0; i <= 23; ++i)
        for(int j = 0; j <= 59; ++j)
            check(i, j);
    if(!flag) {
        cout << "impossible";
        return 0;
    }
    for(int i = 1; i <= 7; ++i) {
        for(int j = 1; j <= 21; ++j)
            cout << ans[i][j];
        cout << '\n';
    }
    return 0;
}

```
下班收工，原神启动！

---

## 作者：ran_qwq (赞：7)

XP 真会搬题，模拟赛搬道大模拟。

---
题面写得比答辩还难看，简化一下题意：

有一个显示连续 $24$ 小时制中 $n$ 分钟的电子表，判断每个段是常灭、常亮、正常还是无法判断。

$n\le100$。

---
以下讨论的格子都在段上。

首先，如果一个格子在显示时间中永远灭，那么它有可能常灭；如果永远亮，那么它有可能常亮。

接着预处理所有时间的正确的表。

枚举开始时间，比较显示的表与正确的表。

如果显示的格子和正确的对应格子不同，且没有常灭、常亮的可能，表明开始时间不合法。

---
具体实现看代码：

```cpp
#include<bits/stdc++.h>
#define ri register
#define il inline
#define cs const
#define ui unsigned int
#define ll long long
#define ull unsigned ll
#define lll __int128
#define ulll unsigned lll
#define db double
#define ldb long double
#define op operator
#define sct struct
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define gi greater<int>
#define pqi priority_queue<int>
#define fir first
#define sec second
#define gc getchar
#define pc putchar
#define mst(arr,val) memset(arr,val,sizeof arr)
#define mcp(arr,val) memcpy(arr,val,sizeof arr)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define uq unique
#define us using
#define nsp namespace
us nsp std;
cs int N=110,M=10,K=25,INF=0x3f3f3f3f;cs ll INFll=0x3f3f3f3f3f3f3f3f;
nsp FIO {
	il int rd() {int x=0,f=1;char ch=gc();while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=gc();}while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc();return x*f;}
	il ll rdll() {ll x=0;int f=1;char ch=gc();while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=gc();}while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc();return x*f;}
	il void wr(int x) {if(x<-2147483647) {printf("-2147483648");return;}if(x<0) {pc('-'),wr(-x);return;}if(x<10) {pc(x+'0');return;}wr(x/10),pc(x%10+'0');}
	il void wrll(ll x) {if(x<-9223372036854775807) {printf("-9223372036854775808");return;}if(x<0) {pc('-'),wrll(-x);return;}if(x<10) {pc(x+'0');return;}wrll(x/10),pc(x%10+'0');}
	il void wr(int x,char *s) {wr(x),printf("%s",s);}
	il void wrll(ll x,char *s) {wrll(x),printf("%s",s);}
}us nsp FIO;
int n,ok,a[M][K],b[M][K],d[M][K],f[M][K],g1[M][K],g2[M][K],g3[M][K];char s[M][K],ch[N][M][K],t[K][N][M][K];
void QwQ() {
	n=rd();
	for(int i=1;i<=n;i++) for(int j=1;j<=7;j++) {
		string s;cin>>s,s=" "+s;
		for(int k=1;k<=21;k++) ch[i][j][k]=s[k];
	}
	for(int i=1;i<=7;i++) for(int j=1;j<=21;j++) {
		a[i][j]=b[i][j]=1;
		for(int k=1;k<=n;k++) a[i][j]&=ch[k][i][j]=='.',b[i][j]&=ch[k][i][j]=='X';
		f[i][j]=i%3==1&&(j==2||j==3||j==7||j==8||j==14||j==15||j==19||j==20)||i%3!=1&&(j==1||j==4||j==6||j==9||j==13||j==16||j==18||j==21)||(i==3||i==5)&&j==11;
	}
	for(int i=0;i<24;i++) for(int j=0;j<60;j++) {
		for(int k=1;k<=7;k++) for(int l=1;l<=21;l++) s[k][l]='.';
		int x=i/10,y=i%10,p=j/10,q=j%10;s[3][11]=s[5][11]='X';
		if(x==1) s[2][4]=s[3][4]=s[5][4]=s[6][4]='X';
		if(x==2) s[1][2]=s[1][3]=s[2][4]=s[3][4]=s[4][2]=s[4][3]=s[5][1]=s[6][1]=s[7][2]=s[7][3]='X';
		if(!y) s[1][7]=s[1][8]=s[2][6]=s[2][9]=s[3][6]=s[3][9]=s[5][6]=s[5][9]=s[6][6]=s[6][9]=s[7][7]=s[7][8]='X';
		if(y==1) s[2][9]=s[3][9]=s[5][9]=s[6][9]='X';
		if(y==2) s[1][7]=s[1][8]=s[2][9]=s[3][9]=s[4][7]=s[4][8]=s[5][6]=s[6][6]=s[7][7]=s[7][8]='X';
		if(y==3) s[1][7]=s[1][8]=s[2][9]=s[3][9]=s[4][7]=s[4][8]=s[5][9]=s[6][9]=s[7][7]=s[7][8]='X';
		if(y==4) s[2][6]=s[2][9]=s[3][6]=s[3][9]=s[4][7]=s[4][8]=s[5][9]=s[6][9]='X';
		if(y==5) s[1][7]=s[1][8]=s[2][6]=s[3][6]=s[4][7]=s[4][8]=s[5][9]=s[6][9]=s[7][7]=s[7][8]='X';
		if(y==6) s[1][7]=s[1][8]=s[2][6]=s[3][6]=s[4][7]=s[4][8]=s[5][6]=s[5][9]=s[6][6]=s[6][9]=s[7][7]=s[7][8]='X';
		if(y==7) s[1][7]=s[1][8]=s[2][9]=s[3][9]=s[5][9]=s[6][9]='X';
		if(y==8) s[1][7]=s[1][8]=s[2][6]=s[2][9]=s[3][6]=s[4][7]=s[4][8]=s[5][6]=s[5][9]=s[6][6]=s[6][9]=s[7][7]=s[7][8]='X';
		if(y==9) s[1][7]=s[1][8]=s[2][6]=s[2][9]=s[3][6]=s[4][7]=s[4][8]=s[5][9]=s[6][9]=s[7][7]=s[7][8]='X';
		if(!p) s[1][14]=s[1][15]=s[2][13]=s[2][16]=s[3][13]=s[3][16]=s[5][16]=s[5][13]=s[5][16]=s[6][13]=s[6][16]=s[7][14]=s[7][15]='X';
		if(p==1) s[2][16]=s[3][16]=s[5][16]=s[6][16]='X';
		if(p==2) s[1][14]=s[1][15]=s[2][16]=s[3][16]=s[4][14]=s[4][15]=s[5][13]=s[6][13]=s[7][14]=s[7][15]='X';
		if(p==3) s[1][14]=s[1][15]=s[2][16]=s[3][16]=s[4][14]=s[4][15]=s[5][16]=s[6][16]=s[7][14]=s[7][15]='X';
		if(p==4) s[2][13]=s[2][16]=s[3][13]=s[3][16]=s[4][14]=s[4][15]=s[5][16]=s[6][16]='X';
		if(p==5) s[1][14]=s[1][15]=s[2][13]=s[3][13]=s[4][14]=s[4][15]=s[5][16]=s[6][16]=s[7][14]=s[7][15]='X';
		if(!q) s[1][19]=s[1][20]=s[2][18]=s[2][21]=s[3][18]=s[3][21]=s[5][18]=s[5][21]=s[6][18]=s[6][21]=s[7][19]=s[7][20]='X';
		if(q==1) s[2][21]=s[3][21]=s[5][21]=s[6][21]='X';
		if(q==2) s[1][19]=s[1][20]=s[2][21]=s[3][21]=s[4][19]=s[4][20]=s[5][18]=s[6][18]=s[7][19]=s[7][20]='X';
		if(q==3) s[1][19]=s[1][20]=s[2][21]=s[3][21]=s[4][19]=s[4][20]=s[5][21]=s[6][21]=s[7][19]=s[7][20]='X';
		if(q==4) s[2][18]=s[2][21]=s[3][18]=s[3][21]=s[4][19]=s[4][20]=s[5][21]=s[6][21]='X';
		if(q==5) s[1][19]=s[1][20]=s[2][18]=s[3][18]=s[4][19]=s[4][20]=s[5][21]=s[6][21]=s[7][19]=s[7][20]='X';
		if(q==6) s[1][19]=s[1][20]=s[2][18]=s[3][18]=s[4][19]=s[4][20]=s[5][18]=s[5][21]=s[6][18]=s[6][21]=s[7][19]=s[7][20]='X';
		if(q==7) s[1][19]=s[1][20]=s[2][21]=s[3][21]=s[5][21]=s[6][21]='X';
		if(q==8) s[1][19]=s[1][20]=s[2][18]=s[2][21]=s[3][18]=s[3][21]=s[4][19]=s[4][20]=s[5][18]=s[5][21]=s[6][18]=s[6][21]=s[7][19]=s[7][20]='X';
		if(q==9) s[1][19]=s[1][20]=s[2][18]=s[2][21]=s[3][18]=s[3][21]=s[4][19]=s[4][20]=s[5][21]=s[6][21]=s[7][19]=s[7][20]='X';
		for(int k=1;k<=7;k++) for(int l=1;l<=21;l++) t[i][j][k][l]=s[k][l];
	}
	for(int i=0;i<24;i++) for(int j=0;j<60;j++) {
		int fg=1;
		for(int k=1;k<=7;k++) for(int l=1;l<=21;l++) d[k][l]=1;
		for(int k=1,x=i,y=j;k<=n;k++) {
			for(int p=1;p<=7;p++) for(int q=1;q<=21;q++) if(t[x][y][p][q]!=ch[k][p][q]) {
				d[p][q]=0;
				if(!a[p][q]&&!b[p][q]) fg=0;
			}
			y++;if(y==60) x++,y=0;if(x==24) x=0;
		}
		if(fg) {
			ok=1;
			for(int k=1;k<=7;k++) for(int l=1;l<=21;l++) g1[k][l]|=a[k][l],g2[k][l]|=b[k][l],g3[k][l]|=d[k][l];
		}
	}
	if(!ok) puts("impossible"),exit(0);
	for(int i=1;i<=7;i++,puts("")) for(int j=1;j<=21;j++) pc(!f[i][j]?'.':g1[i][j]+g2[i][j]+g3[i][j]>1?'?':g1[i][j]?'0':g2[i][j]?'1':'W');
}
signed main() {int T=1;while(T--) QwQ();}
```

注意以下细节：

1. 数组要开够。

1. 字符画的细节。

1. 格子不在段上要直接输出 `.`。

1. `X` 和 `W` 都是大写。

1. 小时前导零不显示。

1. 考虑有多个初始时间满足要求的情况。

---

