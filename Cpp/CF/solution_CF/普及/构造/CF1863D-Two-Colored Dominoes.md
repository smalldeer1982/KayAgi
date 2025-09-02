# Two-Colored Dominoes

## 题目描述

There is an $ n\times m $ board divided into cells. There are also some dominoes on this board. Each domino covers two adjacent cells (that is, two cells that share a side), and no two dominoes overlap.

Piet thinks that this board is too boring and it needs to be painted. He will paint the cells of the dominoes black and white. He calls the painting beautiful if all of the following conditions hold:

- for each domino, one of its cells is painted white and the other is painted black;
- for each row, the number of black cells in this row equals the number of white cells in this row;
- for each column, the number of black cells in this column equals the number of white cells in this column.

Note that the cells that are not covered by dominoes are not painted at all, they are counted as neither black nor white.

Help Piet produce a beautiful painting or tell that it is impossible.

## 说明/提示

In the first test case, the answer is illustrated below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1863D/c02597064063806335d0d205f181144db4826066.png)In the second test case, it is impossible to paint all cells the right way.

## 样例 #1

### 输入

```
3
4 6
..LR..
ULRU..
DLRDUU
..LRDD
5 4
.LR.
.UU.
UDDU
D..D
LR..
2 2
..
..```

### 输出

```
..WB..
WWBB..
BBWWWB
..BWBW
-1
..
..```

# 题解

## 作者：Creeper_l (赞：9)

## 前言

看了这道题的几篇题解，感觉讲的方法都比较麻烦，这里讲一个感觉比较简单的方法。

## 思路

首先判断是否有解。计算一下每一行和每一列的牌的数量，只要有一个是奇数就无解，否则有解。证明显然，偶数一定可以分成两组，在纸上模拟一下也可以得出。

其次看如何构造。对于竖着的牌，显然只对每行有影响，因为列上的颜色一定是一黑一白的。所以我们就只需要按照行来枚举竖着的牌，每一行上依次按照 $0101...$ 这样的顺序去构造就可以了。需要注意的是，我们只用构造每张牌的上面的那个点，因为下面的点可以通过上面的点的颜色计算出来。

横着的牌按照相同方法构造就可以了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define re register
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 1e3 + 10;
int T,n,m,ans[MAXN][MAXN],len_l[MAXN],len_r[MAXN];
char c[MAXN][MAXN];
signed main()
{
	cin >> T;
	while(T--)
	{
		int flag = false,tmp = 2;
		cin >> n >> m;
		for(int i = 1;i <= n;i++) len_l[i] = 0;
		for(int i = 1;i <= m;i++) len_r[i] = 0;
		for(int i = 1;i <= n;i++) for(int j = 1;j <= m;j++) ans[i][j] = 2;
		for(int i = 1;i <= n;i++) 
			for(int j = 1;j <= m;j++) 
			{
				cin >> c[i][j];
				if(c[i][j] != '.') len_l[i]++,len_r[j]++;
				else ans[i][j] = 1;
			}
		for(int i = 1;i <= n;i++) if(len_l[i] % 2) flag = true;
		for(int i = 1;i <= m;i++) if(len_r[i] % 2) flag = true;
		if(flag == true){puts("-1");continue;}
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= m;j++)
				if(c[i][j] == 'U') ans[i][j] = tmp,ans[i + 1][j] = tmp ^ 1,tmp ^= 1;
		for(int j = 1;j <= m;j++)
			for(int i = 1;i <= n;i++)
				if(c[i][j] == 'L') ans[i][j] = tmp,ans[i][j + 1] = tmp ^ 1,tmp ^= 1;
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= m;j++)
			{
				if(ans[i][j] == 1) cout << '.';
				if(ans[i][j] == 2) cout << 'B';
				if(ans[i][j] == 3) cout << 'W'; 
			}	
			cout << endl;
		}
			
	}
	return 0;
}
```


---

## 作者：ScottSuperb (赞：2)

## 解法分析
首先可以发现，纵向卡片仅影响行、横向卡牌仅影响列，因此可以分开处理。对于纵向卡牌，显然只要上端满足黑白数相同，下端也可满足，因此只需考虑上端：我们采用黑白交替染色的策略，如果发现哪一行染色奇数次说明无解。横向卡牌如法炮制即可。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int ans[505][505], row[505], col[505];

int main() {
  int t, n, m, fl;
  char a;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) row[i] = 2;
    for (int i = 1; i <= m; ++i) col[i] = 2;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
        cin >> a;
        if (a == '.') ans[i][j] = 0;
        if (a == 'U') ans[i][j] = row[i], row[i] ^= 1, ans[i + 1][j] = row[i];
        if (a == 'L') ans[i][j] = col[j], col[j] ^= 1, ans[i][j + 1] = col[j];
      }
    fl = 0;
    for (int i = 1; i <= n; ++i)
      if (row[i] & 1) fl = 1;
    for (int i = 1; i <= m; ++i)
      if (col[i] & 1) fl = 1;
    if (fl) {
      puts("-1");
      continue;
    }
    for (int i = 1; i <= n; ++i, puts(""))
      for (int j = 1; j <= m; ++j)
        putchar(ans[i][j] ? ans[i][j] & 1 ? 'B' : 'W' : '.');
  }
  return 0;
}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

首先考虑保证每行的黑白数量一样，横着的一定是贡献一黑一白，所以只用考虑竖着的，同理竖着的任何方案也不会影响横着的要求。

因为两个同行的竖着的颜色可以互换，所以在满足条件的情况下，谁黑谁白无所谓。

考虑从上往下满足，因为 ```D``` 的格子已经在上一行中确定了，所以可以在上一行时就先把这一行的黑白初始数量确定，然后考虑这一行的 ```U```，如果缺白的就放白的，如果缺黑的就放黑的，顺便把下一排的颜色也确定了，如果某行无法使黑白数量一样，就一定无解。

然后再从左到右一样的判断就行了。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,m,num[505][2],flag;
char ch[505][505];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m),flag=0;
		for(int i=1;i<=n;++i) scanf("%s",ch[i]+1);
		memset(num,0,sizeof(num));
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
			{
				if(ch[i][j]=='U')
				{
					if(num[i][0]<=num[i][1]) ++num[i][0],ch[i][j]='B',++num[i+1][1],ch[i+1][j]='W';
					else ++num[i][1],ch[i][j]='W',++num[i+1][0],ch[i+1][j]='B';
				}
			}
			if(num[i][0]!=num[i][1]){flag=1;break;}
		}
		if(flag){printf("-1\n");continue;}
		memset(num,0,sizeof(num));
		for(int j=1;j<=m;++j)
		{
			for(int i=1;i<=n;++i)
			{
				if(ch[i][j]=='L')
				{
					if(num[j][0]<=num[j][1]) ++num[j][0],ch[i][j]='B',++num[j+1][1],ch[i][j+1]='W';
					else ++num[j][1],ch[i][j]='W',++num[j+1][0],ch[i][j+1]='B';
				}
			}
			if(num[j][0]!=num[j][1]){flag=1;break;}
		}
		if(flag) printf("-1\n");
		else
		{
			for(int i=1;i<=n;++i){for(int j=1;j<=m;++j) printf("%c",ch[i][j]);puts("");}
		}
	}
	return 0;
}
```

---

## 作者：SunnyYuan (赞：1)

## 前言

一个普及组 T3 难度的题耗费了我近 40 分钟。

总的来说我太弱了。

## 思路

我们首先来想一想怎么满足让每一行的黑白数量相同。

我们发现，横着摆的多米诺骨牌对每一行的黑白数量没有影响，反正黑白数量都 $+1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/psuplk93.png)

那么只有竖着摆（竖着摆指上面的方框在这一行）对这一行的黑白数量有影响，假设这一行竖着摆的有 $cnt$ 个，如果 $cnt$ 是奇数，那么肯定无解；否则，我们将 $\frac{cnt}{2}$ 个染成上面黑下面白，将另外 $\frac{cnt}{2}$ 个染成上面白下面黑。

![](https://cdn.luogu.com.cn/upload/image_hosting/xh9b6w5q.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/cmzgkyns.png)

我们考虑了横着摆和竖着摆对每一行的黑白数量的影响。

那我们可以用相同的方法考虑横着摆和竖着摆对每一列的黑白数量的影响。

我们发现只有当横着摆（横着摆指左边的方框在这一行）的时候会对每一列的数量产生影响。

所以我们可以用刚刚同样的方法得出：假设这一列有 $cnt$ 个横着摆的，如果 $cnt$ 为奇数，那么无解，否则将 $\frac{cnt}{2}$ 染成左边黑右边白，另外 $\frac{cnt}{2}$ 染成左边白右边黑。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: D. Two-Colored Dominoes
| Contest: Pinely Round 2 (Div. 1 + Div. 2)
| URL:     https://codeforces.com/contest/1863/problem/D
| When:    2023-08-30 22:35:21
| 
| Memory:  256 MB
| Time:    1000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 510;

int n, m;
char g[N][N];

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> (g[i] + 1);
    for (int i = 1; i <= n; i++) {
        vector<int> s;
        for (int j = 1; j <= m; j++) {
            if (i < n && g[i][j] == 'U' && g[i + 1][j] == 'D') s.push_back(j);
        }
        int sz = s.size();
        if (sz & 1) {
            cout << -1 << '\n';
            return;
        }
        for (int k = 0; k < (sz >> 1); k++) g[i][s[k]] = 'W', g[i + 1][s[k]] = 'B';
        for (int k = (sz >> 1); k < sz; k++) g[i][s[k]] = 'B', g[i + 1][s[k]] = 'W';
    }
    for (int j = 1; j <= m; j++) {
        vector<int> s;
        for (int i = 1; i <= n; i++) {
            if (j < m && g[i][j] == 'L' && g[i][j + 1] == 'R') s.push_back(i);
        }
        int sz = s.size();
        if (sz & 1) {
            cout << -1 << '\n';
            return;
        }
        for (int k = 0; k < (sz >> 1); k++) g[s[k]][j] = 'W', g[s[k]][j + 1] = 'B';
        for (int k = (sz >> 1); k < sz; k++) g[s[k]][j] = 'B', g[s[k]][j + 1] = 'W';
    }
    for (int i = 1; i <= n; i++) cout << (g[i] + 1) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    
    return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF1863D Two-Colored Dominoes](https://www.luogu.com.cn/problem/CF1863D) 题解

## 题意

在做题之前，我们先理清一下样例：

```latex
输入：    输出：
4 6      ..WB..
..LR..   WWBB..
ULRU..   BBWWWB
DLRDUU   ..BWBW
..LRDD
```

这里的 `4 6` 表示的是 $n$ 和 $m$，但是这里的 `. L R U D W B` 又是什么意思？很遗憾，翻译里没有提出。所以我们把目光转移到英文版题面，关键处翻译后如下：

> 每个字符都是 `U`、`D`、`L`、`R` 或 `.` 中的一个，分别为多米诺骨牌的上半部分（up）、下半部分（down）、左半部分（left）、右半部分（right）或什么都没有。
>
> 未被多米诺骨牌覆盖的单元格相对应的每个字符必须是 `.`（一个点），如果相应的单元格是黑色的，则对应的每个字符必须为 `B`（black），如果相应的单元格是白色的，则必须是 `W`（white）。

所以，现在再看样例，看懂了吗？如果一个字符为 `L`，那么这个骨牌的另一半一定在它的右边，这样的骨牌是水平放置的；如果一个字符为 `U`，那么这个骨牌的另一半一定在它的下边，这样的骨牌是垂直放置的。

## 思路

看懂了题目，接下来开始梳理思路。

我们先思考如何判断当前的数据无法满足要求。题目中要求对于棋盘的每一行和每一列，被染黑的格子数等于被染白的格子数。意味着每一行/列有骨牌的格子数量一定是偶数，反之则不可能满足要求。我们可以用两个数组统计每一行/列有骨牌的格子数量，再判断数组中有没有奇数。

判断出能否满足要求后，我们需要找到一种通用的方法，能构造出正确的方案。由于要使黑格和白格数量相同，所以有两种方式（作者用的是第一种）：

1. 对于相同的非 `.` 字符，交替涂色。
2. 对于相同的非 `.` 字符，先涂一半黑，再涂一半白。

因为对于任意一个非 `.` 字符，我们都能确定对应骨牌的另一半的位置，所以我们只用枚举 `L` 和 `U` 两种字符即可。而且骨牌是一黑一白，所以竖着的骨牌对行有影响，需要一行一行循环，横着的骨牌对列有影响，需要一列一列循环。

时间复杂度 $O(n^2)$，轻松通过本题。

## 核心代码

判断是否满足要求：
```cpp
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= m; j++)
    {
        cin >> g[i][j];
        if (g[i][j] != '.')
            lx[i]++, ly[j]++; // 统计有骨牌的格子
    }
}
for (int i = 1; i <= n; i++)
{
    if (lx[i] & 1) // x & 1 = x % 2
    {
        flag = true;
        break;
    }
}
for (int i = 1; i <= m; i++)
{
    if (ly[i] & 1 || flag)
    {
        flag = true;
        break;
    }
}
if (flag)
{
    cout << -1 << endl; // 无法满足要求
    continue; // 因为是多组数据，这里不能用 break 或 return 0;
}
```

构造方案：
```cpp
char mp[5] = {'.', 'B', 'W'};
for (int j = 1; j <= m; j++) // 一列一列循环
{
    for (int i = 1; i <= n; i++)
    {
        if (g[i][j] == 'L')
        {
            g[i][j] = mp[c + 1];
            g[i][j + 1] = mp[(c ^ 1) + 1]; // 另一半涂相反的颜色
            c ^= 1; // 交替涂色
        }
    }
}
for (int i = 1; i <= n; i++) // 一行一行循环
{
    for (int j = 1; j <= m; j++)
    {
        if (g[i][j] == 'U')
        {
            g[i][j] = mp[c + 1];
            g[i + 1][j] = mp[(c ^ 1) + 1];
            c ^= 1;
        }
    }
}
```

别忘了在输入之前清空统计数组 $lx$ 和 $ly$。

---

## 作者：Falling_Sakura (赞：0)

# 思路

> 事先说明：对于覆盖区域为 LR 的骨牌，称为水平骨牌，对于覆盖区域为 UD 的骨牌，称为竖直骨牌。

首先可以发现，水平骨牌在某一行内无论怎么分配都不会使这一行不合法，所以对于水平骨牌我们只需要考虑它所在的列（一个水平骨牌会横跨两列）。假如某一列中有 $x$ 个水平骨牌，如果 $x$ 是奇数那么就一定无解，否则就按照一半骨牌为黑白一半骨牌为白黑的方向放置，顺序无所谓，对于每一列均是如此。

对于竖直骨牌我们同样只考虑它所在的行（一个竖直骨牌横跨两行），与列的情况相同，这里不多赘述，直接上代码。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 505;

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        char s[N][N], ans[N][N];
        int ver[N], hor[N];
        memset(ver, 0, sizeof(ver));
        memset(hor, 0, sizeof(hor));
        memset(ans, '.', sizeof(ans));
        for(int i = 0; i < n; i++)
            scanf("%s", s[i]);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(s[i][j] == 'U')
                {
                    ver[i]++;
                }
                else if(s[i][j] == 'L')
                {
                    hor[j]++;
                }
            }
        }
        bool bj = false;
        for(int i = 0; i < n; i++)
        {
            int cnt = 0;
            if(ver[i] & 1)
            {
                bj = true;
                cout << -1 << endl;
                break;
            }
            for(int j = 0; j < m; j++)
            {
                if(s[i][j] == 'U')
                {
                    cnt++;
                    if(cnt <= (ver[i] >> 1))
                    {
                        ans[i][j] = 'B';
                        ans[i + 1][j] = 'W';
                    }
                    else
                    {
                        ans[i][j] = 'W';
                        ans[i + 1][j] = 'B';
                    }
                }
            }
        }
        for(int i = 0; i < m; i++)
        {
            int cnt = 0;
            if((hor[i] & 1) && !bj)
            {
                bj = true;
                cout << -1 << endl;
                break;
            }
            for(int j = 0; j < n; j++)
            {
                if(s[j][i] == 'L')
                {
                    cnt++;
                    if(cnt <= (hor[i] >> 1))
                    {
                        ans[j][i] = 'B';
                        ans[j][i + 1] = 'W';
                    }
                    else
                    {
                        ans[j][i] = 'W';
                        ans[j][i + 1] = 'B';
                    }
                }
            }
        }
        if(bj) continue;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
                printf("%c", ans[i][j]);
            puts("");
        }
    }
    return 0;
}
```

---

## 作者：hfjh (赞：0)

# D. Two-Colored Dominoes

## 题意

有一个 $n \times m$ 的棋盘，上面铺着一些 $1 \times 2$ 的多米诺骨牌（横竖均有可能），骨牌之间没有重叠。

你需要找到一种染色方案满足以下条件：

- 每个多米诺骨牌一端被染白，另一端被染黑。其他没有骨牌的格子不染色。
- 对于棋盘的每一行，被染黑的格子数等于被染白的格子数。
- 对于棋盘的每一列，被染黑的格子数等于被染白的格子数。

请输出任意一种染色方案，如果无解，输出 $-1$。

本题有多组测试数据，$1 \leq T \leq 10^{4}$，$2 \leq n,m \leq 500$，$\sum (n \times m) \leq 2.5 \times 10^{5}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/u3g4tl3k.png)

## 题解

考虑竖着的骨块对列没有影响，横着的骨块对行没有影响。

竖骨块用 $U,D$ 表示。

横骨块用 $L,R$ 表示。

我们先考虑行，对于第 $i$ 行的我们只考虑 $U$，把 $U$ 交替黑白染色，对应的 $D$ 就是另一种颜色。

若 $U$ 个数不为偶数则无解。

按照这种方式染色可以保证 $i$ 行 $U$ 和 $i + 1$ 行 $D$ 均合法，那么整张图也就合法。

列也类似。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 510;
int t, n, m, cnt, flag;
char c[N][N], ans[N][N];
void input(){
	cin >> n >> m;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			cin >> c[i][j];
			ans[i][j] = '.';
		}
	}
}
void op(){
	for(int i = 1; i <= n; ++i){//h
		cnt = 0;
		for(int j = 1, ty = 1; j <= m; ++j){//
			if(c[i][j] == 'U'){
				ty = ty ^ 1; ++cnt;
				ans[i][j] = (ty) ? 'W' : 'B';
				ans[i + 1][j] = (!ty) ? 'W' : 'B';	
			}
		}
		if(cnt % 2 == 1) flag = 1;
	}
	for(int j = 1; j <= m; ++j){//h
		cnt = 0;
		for(int i = 1, ty = 1; i <= n; ++i){//
			if(c[i][j] == 'L'){
				ty = ty ^ 1; ++cnt;
				ans[i][j] = (ty) ? 'W' : 'B';
				ans[i][j + 1] = (!ty) ? 'W' : 'B';	
			}
		}
		if(cnt % 2 == 1) flag = 1;
	}
}
void output(){
	if(flag){ cout<<-1<<'\n';return ;}
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			cout<< ans[i][j];
		}
		cout<<'\n';
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(false);
	cin>>t;
	while(t--){
		flag = 0;
		input();	
		op();
		output();
	} 
} 
```


---

## 作者：Aisaka_Taiga (赞：0)

### 题意

给你一个 $n\times m$ 的棋盘，上面有一些 $1\times 2$ 的多米诺骨牌，整个棋盘用三种字符表示：

* `.` 表示没有东西。
* `U` 表示一块竖着放置的多米诺骨牌上半部分。
* `D` 表示一块竖着放置的多米诺骨牌下半部分。
* `L` 表示一块横着放置的多米诺骨牌左半部分。
* `R` 表示一块横着放置的多米诺骨牌右半部分。

你需要把里面的棋盘有骨牌的格子染成黑白两色，要求一个骨牌里两块格子的颜色不能相同，棋盘每行每列的黑白格子数相等。

保证输入合法，误解输出 `-1`。

### Solution

因为多米诺骨牌怎么染都是一黑一白，所以我们这样考虑。

对于一行，我们可以发现横着的对他没有影响。反而是竖着的需要考虑。

对于一列，我们发现竖着的对他没有影响，我们只需要考虑横着的。

然后我们来考虑一个构造，我们直接一个双重循环，对于行，我们只要遇到 `U` 或者 `D`，我们就染色，因为一张骨牌要一黑一白，我们顺便把与他相连的染色，然后打上标记，我们染色是按照“黑白黑白黑白”这样交替染色，如果染的首尾格子颜色一样就说明无解。

对于列也同理，不再多做赘述。

这样做为什么是对的？

先来说行。

考虑我们在染色的过程中如果不是上面的无解情况的话，染完的骨牌一定合法，延伸到下一行也是一定合法，因为打了标记，所以下一行遍历不会考虑到，然后就相当于没有那些骨牌，所以后面只要不是上面无解的情况就一定合法。

对于列也是同理。

code:

```cpp
/*
 * @Author: Aisaka_Taiga
 * @Date: 2023-08-31 00:44:12
 * @LastEditTime: 2023-08-31 07:38:42
 * @LastEditors: Aisaka_Taiga
 * @FilePath: \Desktop\CFD.cpp
 * 心比天高，命比纸薄。
 */
#include <bits/stdc++.h>

#define int long long
#define N 510

using namespace std;

int t, n, m, vis[N][N];
char a[N][N], b[N][N];

signed main()
{
    cin >> t;
    while(t --)
    {
        int ff = 0;
        // memset(vis, 0, sizeof vis);
        cin >> n >> m;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                cin >> a[i][j], vis[i][j] = 0;
        for(int i = 1; i <= n; i ++)
        {
            int t = 1;
            for(int j = 1; j <= m; j ++)
            {
                if(vis[i][j]) continue;
                if(a[i][j] == '.') b[i][j] = '.', vis[i][j] = 1;
                if(a[i][j] == 'U')
                {
                    b[i][j] = (t ^ 1 ? 'W' : 'B');
                    b[i + 1][j] = (t ? 'W' : 'B');
                    vis[i][j] = vis[i + 1][j] = 1;
                    t ^= 1;
                }
            }
            if(t == 0) ff = 1;
        }
        for(int j = 1; j <= m; j ++)
        {
            int t = 1;
            for(int i = 1; i <= n; i ++)
            {
                if(vis[i][j]) continue;
                if(a[i][j] == '.') b[i][j] = '.', vis[i][j] = 1;
                if(a[i][j] == 'L')
                {
                    b[i][j] = (t ^ 1 ? 'W' : 'B');
                    b[i][j + 1] = (t ? 'W' : 'B');
                    vis[i][j] = vis[i][j + 1] = 1;
                    t ^= 1;
                }
            }
            if(t == 0) ff = 1;
        }
        if(ff == 1) {cout << "-1" << endl; continue;}
        for(int i = 1; i <= n; i ++)
        {
            for(int j = 1; j <= m; j ++)
                cout << b[i][j];
            cout << endl;
        }
    }
    return 0;
}
/*
..BW..
BBWW..
WWBBBW
..WBWB
-1
..
..
*/
```

---

