# Fall Down

## 题目描述

There is a grid with $ n $ rows and $ m $ columns, and three types of cells:

- An empty cell, denoted with '.'.
- A stone, denoted with '\*'.
- An obstacle, denoted with the lowercase Latin letter 'o'.

All stones fall down until they meet the floor (the bottom row), an obstacle, or other stone which is already immovable. (In other words, all the stones just fall down as long as they can fall.)

Simulate the process. What does the resulting grid look like?

## 样例 #1

### 输入

```
3
6 10
.*.*....*.
.*.......*
...o....o.
.*.*....*.
..........
.o......o*
2 9
...***ooo
.*o.*o.*o
5 5
*****
*....
*****
....*
*****```

### 输出

```
..........
...*....*.
.*.o....o.
.*........
.*......**
.o.*....o*

....**ooo
.*o**o.*o

.....
*...*
*****
*****
*****```

# 题解

## 作者：封禁用户 (赞：7)

这是本蒟蒻的第一篇题解，写的不好请见谅 OvO

------------
# 关于题目
这道题的翻译有问题：```.```是空格子，```*```是石子，
``o``是障碍物。

# 解题思路

我们可以对每个石子进行 dfs 直接递归到最下面，边递归边改变原始数组的内容。

但是如果向下递归的过程中碰到了别的石子就会很麻烦。

所以我们考虑直接从最下面一行的石子进行处理.

### 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#define LL long long
using namespace std;
template<typename T>
void in(T &x) //快读
{
	x=0;
	T f=1;
	char c=getchar();
	while(!isdigit(c)){if(!isspace(c))f=-1; c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
	return;
}
int t,n,m;
char s[55][55];
inline void dfs(int x,int y)
{
	if(x+1>n||s[x+1][y]=='o'||s[x+1][y]=='*') return; //下一格要是出界、石子或障碍物就返回
	swap(s[x][y],s[x+1][y]); //否则下落一格
	dfs(x+1,y); //递归下一层
}
int main()
{
	in(t);
	while(t--)
	{
		in(n); in(m);
		for(int i=1;i<=n;i++)
			scanf("%s",s[i]+1);
		for(int i=n;i>=1;i--) //从最下面一行开始找石子
		{
			for(int j=1;j<=m;j++)
			{
				if(s[i][j]=='*')
				{
					dfs(i,j);
				}
			}
		}
		for(int i=1;i<=n;i++)//输出
		{
			for(int j=1;j<=m;j++)
			{
				putchar(s[i][j]);
			}
			putchar('\n');
		}
	}
	return 0;//完美结束
}
```


---

## 作者：mmr123 (赞：4)

## 注意
题面问题：
1. `*` 字符：此块为一个石子
2. `o` 字符：此块为障碍物，石子不能通过。
3. `.` 字符：此块为空，石子可以通过。

## 思路
```
.*.*....*.
.*.......*
...o....o.
.*.*....*.
..........
.o......o*
```
由于模拟的是掉落过程，只需对于每一列从下向上遍历，依次处理每一个 $*$ 的掉落过程。
对于每一个 $*$ 向下遍历直到遇到第一个 $o$ 或 $*$ 后，就把它放在这个 $o$ 或 $*$ 的上面。

## AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
 
char chat[51][51];
int t, n, m;
 
int main(int argc, char const *argv[]) {
 
    cin >> t;
 
    for (int i = 0; i < t; ++i) {
        cin >> n >> m;
 
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                cin >> chat[j][k];
            }
        }
 
 
        for (int j = n - 1; j >= 0; --j) { //注意遍历顺序，从下向上
            for (int k = 0; k < m; ++k) {
                if (chat[j][k] == '.' || chat[j][k] == 'o') {
                    continue;
                }
 
                if (j == n - 1) {
                    continue;
                }
 
                chat[j][k] = '.';
 
                for (int l = j; l < n; ++l) { //从当前点向下搜索
                    if (chat[l][k] == 'o' || chat[l][k] == '*') {
                        chat[l - 1][k] = '*';
                        break;
                    } else if (l == n - 1) { //搜索到底部则落在底部；
                        chat[l][k] = '*';
                    }
                }
            }
        }
 
 
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                cout << chat[j][k];
            }
            cout << endl;
        }
        cout << endl;
    }
 
    system("pause");
 
    return 0;
}
```

---

## 作者：C_sir (赞：3)


题的思路就不多说了，大家都明白

具体就一个重点：从下向上找！！！！！
不然会有的落不到自己该到的位置



DFS 大家都会^-^



```
#include<iostream>//头文件eee 
using namespace std;
int n,m,l;
char a[55][55];
void diao(int x,int y) {//调用函数，判断能否下落，以及下落到哪 
	a[x][y]='.';
	for(int i=x; i<=n; i++) {
		if(a[i+1][y]!='.') {
			a[i][y]='*';
			return;
		}
	}
}
int main() {
	cin>>l;//输入 
	for(int i=1; i<=l; i++) {
		cin>>n>>m;
		for(int i=1; i<=m; i++) a[n+1][i]='o';
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				cin>>a[i][j];
			}
		}
		//依次判断每一个点是否满足要求 
		for(int i=n; i>=1; i--) {
			for(int j=1; j<=m; j++) {
				if(a[i][j]=='*') {
					diao(i,j);
				}
			}
		}
		 
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				cout<<a[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
	}
	return 0; //好习惯 
}
```

第一次发题解，求过---

---

## 作者：Galex (赞：2)

因为每个石头是可以落在其他石头上面的，所以我们需要将石头按纵坐标从大到小排序（这里的坐标是指左上角为 $(1,1)$，右下角为 $(n,m)$）。然后依次处理每个石头，如果它的下面为空，就与它下面的字符交换，直到到了最底下或某个物品的上面。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

char readc() {
	char ch = getchar();
	while (ch != 'o' && ch != '*' && ch != '.')
		ch = getchar();
	return ch;
}

int n, m;
char a[55][55];

int cnt;
pair<int, int> stn[3000];

signed main() {
	int T = read();
	while (T--) {
		cnt = 0;
		n = read(), m = read();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				a[i][j] = readc();
				if (a[i][j] == '*')
					stn[++cnt].first = n - i + 1, stn[cnt].second = j;
			}
		sort(stn + 1, stn + cnt + 1);
		for (int i = 1; i <= cnt; i++) {
			int x = n - stn[i].first + 1, y = stn[i].second;
			while (x < n && a[x + 1][y] == '.')
				swap(a[x][y], a[x + 1][y]), x++;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				putchar(a[i][j]);
			putchar('\n');
		}
		putchar('\n');
	}	
	return 0;
}
```


---

## 作者：GI录像机 (赞：0)

## 大致思路：

我们考虑顺序枚举。

对于一个石子，遇到障碍物和地面（最后一行），好说，直接停止。那要是碰到一个石子呢？不能直接停下，因为下面的石子可能还要下落。怎么处理呢？简单，倒着考虑，先让下面的石子下落，这样就不会出现下面的石子可能会继续下落的情况了。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(long long x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, t = read();
int main() {
	while (t--) {
		n = read();
		m = read();
		string s[100];
		for (int i = 1; i <= n; i++) {
			cin >> s[i];
			s[i] = " " + s[i];
		}
		for (int i = n; i >= 1; i--)
			for (int j = 1; j <= m; j++)
				if (s[i][j] == '*') {
					int xx = i, yy = j;
					while (s[xx + 1][yy] == '.' && xx + 1 <= n) {
						swap(s[xx][yy], s[xx + 1][yy]);
						xx++;
					}
				}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)putchar(s[i][j]);
			putchar('\n');
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：IvanZhang2009 (赞：0)

## 题意
给你一个矩阵，里面有石子 ``*``，障碍物 ``o``，空格 ``.``。

现在让石子往下掉，直到碰到障碍物或者到了矩阵的最后一行，输出所有石子变化后的矩阵。

## 解法
我们看到 50 的数据范围，毫不犹豫选择 ~~暴戾~~ 暴力。

如果石子碰到了矩阵的最后一行，就不会继续往下掉，那么我们可以人为的在最下面加上一整行障碍物。这样 ~~应该~~ 可以避免数组越界。

可以一列一列考虑。很显然可以用障碍物来将每一列分成几组，每组内所有的石子会掉到障碍物上方。

这个时候只需要找到列中所有障碍物的位置，在中间统计石子的总数并将石子改成空格，最后将石子统一放在障碍物上方。

为了方便写代码，可以将整个矩阵倒过来（第 1 行变成最后一行，第 2 行变成倒数第二行，以此类推），这样统一放置石子的时候就可以更方便。

## 代码
```cpp
#define REP(i,a,n) for(int i=(a);i<(n);i++)
int n,m;
string s[1005];
void Main(){
    cin>>n>>m;
    REP(i,0,n)cin>>s[n-i-1];//将整个矩阵倒过来
    s[n]="";
    REP(i,0,m)s[n]+='o';//最后一行放满障碍物
    REP(i,0,m){//一列一列地考虑
        REP(j,0,n){
            int x=j;
            while(x<=n&&s[x][i]!='o')x++;//寻找下一个障碍物，区间[j,x)是障碍物之间的空间
            int y=0;
            REP(k,j,x)if(s[k][i]=='*'){
                y++;//记录有多少个石子
                s[k][i]='.';
            }
            REP(k,j,j+y)s[k][i]='*';//方便写代码的地方：将矩阵倒过来之后，相当于石子往上掉。从上往下将空格改成石子
            j=x;
        }
    }
    REP(i,0,n)cout<<s[n-i-1]<<endl;
}
```

---

## 作者：Phartial (赞：0)

考虑对每一列单独处理。

对于每一列，我们从上往下扫，记录当前的石头数量，如果碰到了障碍，把当前的石头数量从上一个开始依次往上堆，直到剩余石头数量为 $0$ 为止，最后把剩下的石头从 $n$ 开始往上堆即可。

```cpp
#include <iostream>

using namespace std;

const int kN = 51;

int t, n, m;
char a[kN][kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        cin >> a[i][j];
      }
    }
    for (int j = 1; j <= m; ++j) {  // 对于每一列
      int c = 0;
      for (int i = 1; i <= n; ++i) {          // 从上至下处理
        if (a[i][j] == '*') {                 // 如果这里是石头
          ++c, a[i][j] = '.';                 // 累加石头数量，将此处设为空
        } else if (a[i][j] == 'o') {          // 如果碰到了障碍
          for (int k = i - 1; c; --k, --c) {  // 往上堆石头
            a[k][j] = '*';
          }
        }
      }
      for (int k = n; c; --k, --c) {  // 把剩下的石头从第 n 行开始堆
        a[k][j] = '*';
      }
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        cout << a[i][j];
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
```

---

