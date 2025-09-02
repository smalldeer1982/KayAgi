# Stripes

## 题目描述

On an $ 8 \times 8 $ grid, some horizontal rows have been painted red, and some vertical columns have been painted blue, in some order. The stripes are drawn sequentially, one after the other. When the stripe is drawn, it repaints all the cells through which it passes.

Determine which color was used last.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1742C/6f423ce4b1dd07561098c185bf230d882c12b3e9.png)The red stripe was painted after the blue one, so the answer is R.

## 说明/提示

The first test case is pictured in the statement.

In the second test case, the first blue column is painted first, then the first and last red rows, and finally the last blue column. Since a blue stripe is painted last, the answer is B.

## 样例 #1

### 输入

```
4


....B...
....B...
....B...
RRRRRRRR
....B...
....B...
....B...
....B...


RRRRRRRB
B......B
B......B
B......B
B......B
B......B
B......B
RRRRRRRB


RRRRRRBB
.B.B..BB
RRRRRRBB
.B.B..BB
.B.B..BB
RRRRRRBB
.B.B..BB
.B.B..BB


........
........
........
RRRRRRRR
........
........
........
........```

### 输出

```
R
B
B
R```

# 题解

## 作者：Andy_L (赞：6)

$\color{#E74C3C}\text{温馨提示:}$

$\color{#E74C3C}\text{遇见题解勿抄袭，棕名封号两行泪。}$

[CF 题目传送门](https://codeforces.com/contest/1742/problem/C)

[洛谷 题目传送门](https://www.luogu.com.cn/problem/CF1742C)

### 思路

我们模拟一下，就可以发现只要输入里有一行是8个 `R` ，那么答案即为 `R` ，因为如果答案是 `B` 的话，总有一列是全 `B` 的，就不会出现一行全是 `R` 的情况了。

---

$$\text{Code}$$

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[101];

int main()
{
	int t;cin>>t;
	while (t--)
	{
		bool flag=0;
		string s;
		for (int i=1;i<=8;i++)
		{
			cin>>s;
			if(count(s.begin(), s.end(), 'R')==8) flag=1; //计数
		}
		if(flag) printf("R\n");
		else printf("B\n");
	}
	return 0;
}
```

[AC 记录](https://codeforces.com/contest/1742/submission/175943920)

---

## 作者：Clyfort (赞：1)

## Problem
在 $8 \times 8$ 的网格上，轮流染上红色和蓝色。

- 红色只能染一整行。
- 蓝色只能染一整列。

问最后用的是哪种颜色。

## Solution
题目说明了至少会染一个条纹，所以我们只需判断有没有一行是 `RRRRRRRR` 就行了。

因为没有 `RRRRRRRR`，那必定就是最后染的蓝色。

如果有当然就是最后染的红色啦。

## Code
```c++
#include <bits/stdc++.h>
using namespace std;

#define file(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout);
#define r(x) x = read()

inline int read()
{
    int d = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        d = (d << 3) + (d << 1) + ch - 48, ch = getchar();
    return d;
}

string grid[10];

void work()
{
    bool flag = false;
    for (int i = 1; i <= 8; i ++)
    {
        cin >> grid[i];
        if (grid[i] == "RRRRRRRR")
            flag = true;
    }

    if (flag == true)
        cout << "R\n";
    else
        cout << "B\n";
}

int main()
{
    file("stripes");
    int tt = 1;
    r(tt);
    while (tt --)
        work();
    return 0;
}
```

---

## 作者：zfx_VeXl6 (赞：1)

用 $r$ 数组统计每行中 `R` 的数量，用 $b$ 数组统计每列中 `B` 的数量，如果存在 $r_i=8$，则输出 `R`，否则输出 `B`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,r[9],b[9];
char a;
int main()
{
	cin>>t;
	while(t--)
	{
		memset(r,0,sizeof(r));
		memset(b,0,sizeof(b));
		for(int i=1;i<=8;i++)
			for(int j=1;j<=8;j++)
			{
				cin>>a;
				if(a=='R')
					r[i]++;
				else
					b[j]++;
			}
		for(int i=1;i<=8;i++)
			if(r[i]==8)
			{
				cout<<"R\n";
				break;
			}
		for(int i=1;i<=8;i++)
			if(b[i]==8)
			{
				cout<<"B\n";
				break;
			}
	}
	return 0;
}
```

---

## 作者：江户川·萝卜 (赞：1)

$8\times8$ 的染色地图，初始是白色，给你染完色的地图，`.` 代表白色，`R` 代表红色，`B` 代表蓝色。

其中染红色的策略必定是涂一行，染蓝色的策略必定是涂一列。颜色会覆盖。

求最后涂的颜色是什么，`R`代表红，`B` 代表蓝。

---
由于题目保证一定染色，考虑如下：

若最后染红色，那么肯定存在一列 `RRRRRRRR`。

否则最后染的就是蓝色。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[8];
void solve(){
    bool f=0;
    for(int i=0;i<8;i++){
        cin>>s[i];
        if(s[i]=="RRRRRRRR") f=1;
    }
    puts(f?"R":"B");
}
int main(){
	int t;cin>>t;
	while(t--){
		solve();
	}
}
```

---

## 作者：liangbob (赞：0)

### CF1742C 题解

#### 思路分析

题目保证至少会染一条行或列，而且染的色会覆盖。

所以最后染色的行或列必定为全红或全蓝，不能有格子被覆盖。不然就绝对不是最后一次的染色，就一定有后来染色的行或列去覆盖它。

所以有一下两种判断方式：

1. 判断某一行是否全部为红色。是，则最后一次用红色。否则，最后一次用蓝色。
2. 判断某一列是否全部为蓝色。是，则最后一次用蓝色。否则，最后一次用红色。

任选一种进行判断即可。这里我们选用第 1 种方式。因为行遍历相对容易实现。

#### 关键代码

```cpp
void solve() 
{
    for(int i = 1;i <= 8;i++)
    {
        bool pd = (s[i][1] == 'R'); //先判断第一个，为后面的与运算做铺垫。
        for(int j = 2;j <= 8;j++)
        {
			pd = (pd && (s[i][j] == 'R'));
        }
        if(pd)
        {
            cout << "R" << endl;
            return; 
        }
    }
    cout << "B" << endl; //前面全部红色的已经返回了，执行到此绝对为蓝色。
    //（因为不可能不染色）
}
```

---

