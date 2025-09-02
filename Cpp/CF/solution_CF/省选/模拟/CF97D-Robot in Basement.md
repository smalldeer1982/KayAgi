# Robot in Basement

## 题目描述

The Professor has lost his home robot yet again. After some thinking Professor understood that he had left the robot in the basement.

The basement in Professor's house is represented by a rectangle $ n×m $ , split into $ 1×1 $ squares. Some squares are walls which are impassable; other squares are passable. You can get from any passable square to any other passable square moving through edge-adjacent passable squares. One passable square is the exit from the basement. The robot is placed exactly in one passable square. Also the robot may be placed in the exit square.

Professor is scared of going to the dark basement looking for the robot at night. However, he has a basement plan and the robot's remote control. Using the remote, Professor can send signals to the robot to shift one square left, right, up or down. When the robot receives a signal, it moves in the required direction if the robot's neighboring square in the given direction is passable. Otherwise, the robot stays idle.

Professor wrote a sequence of $ k $ commands on a piece of paper. He thinks that the sequence can lead the robot out of the basement, wherever it's initial position might be. Professor programmed another robot to press the required buttons on the remote according to the notes on the piece of paper. Professor was just about to run the program and go to bed, when he had an epiphany.

Executing each command takes some energy and Professor doesn't want to get huge electricity bill at the end of the month. That's why he wants to find in the sequence he has written out the minimal possible prefix that would guarantee to lead the robot out to the exit after the prefix is fulfilled. And that's the problem Professor challenges you with at this late hour.

## 样例 #1

### 输入

```
5 5 7
#####
#...#
#...#
#E..#
#####
UULLDDR
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 5 7
#####
#.#.#
#...#
#E..#
#####
UULLDDR
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 3 2
###
#.#
#.#
#E#
###
DD
```

### 输出

```
2
```

# 题解

## 作者：zhangbo1000 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF97D)

update 2024.3.21 重新提交以去除旧博客分类。

update 2024.1.24：
1. 修正了行间代码格式，去除了不应有的空格。

2. 修复了“题目传送门”的链接。

~~题目翻译 Latex 好像炸了。~~

一个简单的暴力解法就是把每个位置所有的能到终点的步数给处理出来，但是这样时空的复杂度都是 $\Theta(nml)$。最大 $2.25\times 10^{9}$，过不了。

然后发现各个机器的移动是相互独立的，可以重叠，而且两个机器的某一步如果走到了一个地点，那么它们接下来所有的移动都是一样的，所以我们可以把所有机器摆上一起走，空间复杂度就可以接受了，只需一个 `bool` 数组存下所有机器人当前位置即可。

但时间还是很炸裂，~~吸口氧气？，~~卡卡常数？

用 `bitset` 。

`bitset` 是 c++ 中一个很好有的 STL 容器，类似一维 `bool` 数组，用 $1$ bit 存储一个元素，时间和空间常数极小，用上 `bitset` 的埃氏筛质数甚至 $\Theta(n\log\log{n})$ 能过 $n=10^8$ 的数据，并且支持位运算（比如 ```<<``` 能将其中所有元素右移一位，像对整数一样。）

但是这东西不支持二维的（各位可以试一下开 `bitset` 的数组，真的跑的非常慢，还不如 `bool` 数组。），我们映射一下，把第 $i$ 行第 $j$ 列映射到第 $i\times m+j$ 个元素，然后竖着走 $1$ 格改为横着走 $m$ 格。（那走到一行末尾怎么办？**注意题目保证了边界都是墙。**）

现在时间基本可以了，看一看怎么模拟，注意 `bitset` 用 $1$ 字节存 $8$ 个元素，本题中一个 $n\times m$ 大小的 `bitset` 才大概 $2.8 $ kB ，可以随便来个~~成千上百~~好几个。

我们开几个，下面 $robots$ 存当前位置，$tmp$ 存所有能走的格，$qiang$ 存墙，$end$ 存终点。以 U 操作为例：

不考虑墙明显走完在 `robots>>m`，必须走到的位置能走则是 `(robots>>m)&tmp`，走不了停在原地的一定是墙下方一格处，即 `robots&(qiang<<m)`，两者合并后即`((robots>>m)&tmp)|(robots&(qiang<<m))`。

其它操作也大同小异，向下/右就把 `<<` 和 `>>` 互换，横着走就把 $m$ 换成 $1$。我们发现全程 $qiang$ 是不变的，因此可以将 `qiang<<m,qiang>>m,qiang<<1,qiang>>1`，四个预处理出来，反正这题空间大。

某一步数是解的判断也简单，明显此时 $end=robots$。

使用 `bitset` 的位运算常数极小，复杂度一般写成 $\Theta(\dfrac{n}{w})$
，其中 $w$ 为 $64$ 或 $32$，那么本算法总复杂度为 $\Theta(\dfrac{nml}{w})$。

最终代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cmath>
#include<bitset>
using namespace std;
#define M 151
#define end _end
char a[M][M];
bitset<25000>robots,tmp,qiang,end,qiang1,qiang2,qiang3,qiang4;
#define N 100001
char change[N];
int main(){
	int n,m,l;
	scanf("%d%d%d",&n,&m,&l);
	for(int i=1;i<=n;i++){
		getchar();
		for(int j=1;j<=m;j++){
			scanf("%c",&a[i][j]);
			if(a[i][j]=='#')robots[i*m+j]=0,qiang[i*m+j]=1;
			else robots[i*m+j]=1;
			if(a[i][j]=='E')end[i*m+j]=1;
		}
	}
	tmp=robots;
	qiang1=qiang<<m;
	qiang2=qiang>>m;
	qiang3=qiang<<1;
	qiang4=qiang>>1;
	scanf("%s",change);
	for(int i=0;i<l;i++){
		if(end==robots){
			printf("%d",i);
			return 0;
		}
		switch(change[i]){
		case 'U':{
			robots=((robots>>m)&tmp)|(qiang1&robots);
			break;
		}
		case 'D':{
			robots=((robots<<m)&tmp)|(qiang2&robots);
			break;
		}
		case 'L':{
			robots=((robots>>1)&tmp)|(qiang3&robots);
			break;
		}
		case 'R':{
			robots=((robots<<1)&tmp)|(qiang4&robots);
			break;
		}
		}
	}
	if(end==robots){
		printf("%d",l);
	}
	else cout<<-1;
	return 0;
}
```

---

## 作者：傅思维666 (赞：1)

## 题解：

暴力的思路是一个一个按序列模拟。但是很容易发现的性质是各个机器人的行动是互相独立的，不存在谁挡谁路的情况。这样的话，可以在每个空位都放一个机器人，然后大家同步走，直到大家都重合了并且都到终点了，这时就是最少的步数了。

这也就变成了模拟题。

那么很自然地想到了用0/1表示有没有机器人，然后用位运算模拟就行。

模拟的时候大约遵从以下思路：因为bitset没有二维的，所以先考虑把它映射到一维。然后发现机器人一直在左右上下地动，墙是不动的，比较难维护，所以考虑开3个bitset分别记录墙、机器人、出口。最后，上下左右的模拟需要在一维状态下进行，这里需要特殊注意。

代码：

```cpp
#include<cstdio>
#include<bitset>
using namespace std;
const int maxn=155;
const int maxm=1e5+5;
int n,m,k;
int id[maxn][maxn];
char s[maxm];
bitset<50005> a,b,e,mp;
void init()
{
    int tot=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            id[i][j]=tot++;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    init();
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
        {
            if(s[j]=='#')
                mp[id[i][j]]=1;
            else
                a[id[i][j]]=1;
            if(s[j]=='E')
                e[id[i][j]]=1;
        }
    }
    scanf("%s",s+1);
    b=a;
    for(int i=1;i<=k+1;i++)
    {
        if(a==e)
        {
            printf("%d\n",i-1);
            return 0;
        }
        if(s[i]=='U')
            a=(((a>>m)&b)|((mp<<m)&a));
        else if(s[i]=='D')
            a=(((a<<m)&b)|((mp>>m)&a));
        else if(s[i]=='L')
            a=(((a>>1)&b)|((mp<<1)&a));
        else 
            a=(((a<<1)&b)|((mp>>1)&a));
    }
    puts("-1");
    return 0;
}
```



---

## 作者：Priestess_SLG (赞：0)

直接暴力模拟时间复杂度为 $O(nml)$，显然过不去。因此考虑优化。发现若两个机器人移动到同一个位置，那么她们之后移动的状态也必然完全相同，可以合并，即只需要记录某一个位置是否存在机器人即可，不需要计数。因此考虑到用 bitset 优化，记录终止状态即只有 `E` 位置有机器人，所有机器人可在的位置集合 `rob`，当前所有机器人所在位置集合 `nrb`，机器人不能走到的位置集合 `blk`。循环枚举每一个操作，若某一个时刻第一次发现 `nrb == E` 表达式成立，则直接输出当前执行的操作数作为前缀的长度即可。否则，分类讨论四个方向，用 bitset 暴力模拟机器人会移动到的位置即可。时间复杂度为 $O(\frac{nml}\omega)$，具体参见代码。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int N = 155;
const int mod = 1e9 + 7;
char s[N][N];
int id[N][N], idx;
bitset<N * N> block, rob;
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, l, ex = -1, ey = -1;
    cin >> n >> m >> l;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) id[i][j] = ++idx;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> s[i][j];
            if (s[i][j] == '#') block[id[i][j]] = 1;
            else rob[id[i][j]] = 1;
            if (s[i][j] == 'E') ex = i, ey = j;
        }
    bitset<N * N> Final; Final[id[ex][ey]] = 1;
    string op; cin >> op;
    auto nrb = rob;
    for (int i = 0; i < op.size(); ++i) {
        if (nrb == Final) {
            cout << i << '\n';
            return 0;
        }
        if (op[i] == 'L') {
            nrb = ((nrb >> 1) & rob) | (nrb & (block << 1));
        } else if (op[i] == 'R') {
            nrb = ((nrb << 1) & rob) | (nrb & (block >> 1));
        } else if (op[i] == 'U') {
            nrb = ((nrb >> m) & rob) | (nrb & (block << m));
        } else {
            nrb = ((nrb << m) & rob) | (nrb & (block >> m));
        }
    }
    if (nrb == Final) {
        cout << op.size() << '\n';
    } else {
        cout << "-1\n";
    }
    return 0;
}
```

---

## 作者：火星大王 (赞：0)

这道题就是bitset~~胡乱~~模拟,我在洛谷上没有AC好像是~~洛谷BUG~~(瞎说，洛谷怎么能BUG呢)了，它老是说我代码重复我也不知道为啥，我自己去CF交了一遍，是AC的，CF提交编号41733072 原题连接连接[CF97D](http://codeforces.com/problemset/problem/97/D)
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include<cstring>
#include<string>
#include<cctype>
#include<cstdlib>
#include<map>
#include<bitset>
#define debug(x) cerr<<"\tdebug:"<<#x<<"="<<x<<endl
#define debugg(x,y) cerr<<"\tdebug;"<<x<<":"<<#y<<"="<<y<<endl
#define debugzu(x,a,b) 	cerr<<"\tdebug:"<<#x<<"=\n\t";for(int i=a;i<b;i++)cerr<<x[i]<<" ";fprintf(stderr,"\n");
#define debugerzu(x,a,b,c,d) 	cerr<<"\tdebug:"<<#x<<"=\n\t";for(int i=a;i<b;i++,fprintf(stderr,"\n\t"))for(int j=c;j<d;j++)cerr<<x[i][j]<<" ";fprintf(stderr,"\n");
#define R register
#define LL long long
#define I inline
using namespace std;
bitset <23000> a,b,c,e;



int main()
{
// 	freopen("CF97D.in","r",stdin);
// 	freopen("CF97D.out","w",stdout);
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	getchar();
	for(int i=0;i<n;i++,getchar())
		for(int j=0;j<m;j++)
		{
			char s=getchar();
			(s=='#'?b:a).set(i*m+j);
			(s=='E'?e.set(i*m+j):0);
		}
	c=a;
	for(int i=0;i<k;i++)
	{
		char s=getchar();
		if(c==e)
		{
			printf("%d\n",i);
			return 0;
		}
		if(s=='U') c = ( (c>>m)&a) | (c&(b<<m));
		else if(s=='L') c = ((c>>1)&a) | (c&(b<<1));
		else if(s=='D') c = ((c<<m)&a) | (c&(b>>m));
		else if(s=='R') c = ((c<<1)&a) | (c&(b>>1));
	}
	if(c==e)
		printf("%d\n",k);
	else
		printf("%d\n",-1);
	


	fclose(stdin);
	fclose(stdout);
 	return 0;
}

```
上代码

请自行忽略那一大坨define和头文件

可以用一维bitset模拟模拟二维，然后~~胡乱~~位移操作，分不清楚<<和>>的自己试一下就好了

还有我知道洛谷会审帖子，麻烦管理员尽快查看一下是什么BUG我会在[这里](https://www.luogu.org/discuss/show?postid=57648)持续关注这个BUG

---

