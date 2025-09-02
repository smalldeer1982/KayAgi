# Tweetuzki 爱伊图

## 题目背景

Tweetuzki 的教练最近常常在群里发有关「伊图科技」的文章。「伊图科技」是一家专注于计算机视觉技术的上海创业公司，其人脸识别技术在世界处于领先地位。2018 年 6 月，在全球工业界黄金标准 FRVT 测试中，依图在千万分之一误报下识别准确率接近 $99\%$，是全球工业界在此项指标下的最好水平，这是依图科技连续第二年摘得此项竞赛的冠军，也是首个夺得此项竞赛冠军的中国团队。2018 年 11 月 16 日，美国国家标准与技术研究院（NIST）公布了全球权威人脸识别比赛（FRVT）最新报告，依图算法继续保持第一，在千万分之一误报下的识别准确率超过 $99\%$，是目前全球人脸识别技术的最好水平。

更重要的是，伊图科技的创始人，是附中的毕业生——Tweetuzki 的学长呢！人脸识别真的好难呢！Tweetuzki 常常幻想，要是自己的程序能有学长们的亿万分之一厉害，那就很好了呢！

## 题目描述

Tweetuzki 希望设计出一个程序，这个程序应当能识别输入矩阵中隐藏的数字。

输入的是一个 $r \times c$ 的字符矩阵，矩阵中的元素只有 `. `或 `#`。其中 `#` 可以构成一些数字。输入的矩阵将严格遵守以下规则：

- 除 $1$ 占 $5 \times 1$ 的长方形区域外，其余数字均占 $5 \times 3$ 的长方形区域。

- 相邻两个数字间至少有一列 `.`，即**数字不会贴在一块儿**；且数字**只会左右排放**，不会上下排放。这两点综合起来可以表述为：对于两个数字 $A$ 和 $B$（$A$ 在 $B$ 的左侧），若它们在横向上延伸的区间分别为 $[l_A, r_A]$ 和 $[l_B, r_B]$，那么一定满足 $l_B \ge r_A + 2$。

- 数字的组成严格按照如下所列：

  ```plain
  数字的组成方式：
  #   # # #   # # #   # . #   # # #   # # #   # # #   # # #   # # #   # # # 
  #   . . #   . . #   # . #   # . .   # . .   . . #   # . #   # . #   # . # 
  #   # # #   # # #   # # #   # # #   # # #   . . #   # # #   # # #   # . # 
  #   # . .   . . #   . . #   . . #   # . #   . . #   # . #   . . #   # . # 
  #   # # #   # # #   . . #   # # #   # # #   . . #   # # #   # # #   # # # 
  
  所代表的数字：
  1     2       3       4       5       6       7       8       9       0
  ```

  **数字不会倾斜、放大或缩小。**具体可见样例。

- 除构成数字的长方形区域外，其余位置皆由 `.` 填充。保证所有的 `#` 的连通块一定都能够组成数字，且一定满足上述规则。

由于 Tweetuzki 太弱了，于是向你求助，聪明的你，能不能帮助 Tweetuzki 解决这个问题呢？

## 说明/提示

### 样例解释

建议复制进记事本（或各种 IDE）中用等宽字体查看。 

###  子任务

**_Subtask_ #1 _(30 points)_**：矩阵中仅有数字 $1$。  
**_Subtask_ #2 _(30 points)_**：矩阵中不含有数字 $1$ 和 $4$。  
**_Subtask_ #3 _(40 points)_**：无特殊性质。

## 样例 #1

### 输入

```
6 10
# . . . . . # . . #
# . . . # . # . . #
# . . . # . # . . #
# . . . # . # . . #
# . . . # . # . . #
. . . . # . . . . .```

### 输出

```
1111```

## 样例 #2

### 输入

```
8 37
. . . # # # . . . . . . . . . . . . . . . . . . # # # . # . . . . . . . .
. # . # . # . . . . . . . . # # # . . . . . . . # . # . # . . . . . . . .
. # . # # # . . . . . . . . # . . . # # # . . . # # # . # . . # # # . . .
. # . . . # . . . # # # . . # # # . # . # . . . # . # . # . . . . # . . .
. # . # # # . . . . . # . . # . # . # . # . . . # # # . # . . . . # . . .
. # . . . . . . . # # # . . # # # . # . # . . . . . . . . . . . . # . . .
. . . . . . . . . # . . . . . . . . # # # . . . . . . . . . . . . # . . .
. . . . . . . . . # # # . . . . . . . . . . . . . . . . . . . . . . . . .
```

### 输出

```
19260817```

## 样例 #3

### 输入

```
9 94
# # # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . # # # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
# . # . . . . . . . . . . . . . . . . . . . . . . . . # . # . . . . . . . . . . # . . . . . . . . . . . # # # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
# . # . . . # . . . . . . . . . . . . . . . # # # . . # . # . . . . . . . . . . # # # . . . . . . . . . # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
# . # . . . # . . # # # . . . . . . . . . . . . # . . # # # . . . . . . . . . . . . # . . . . . . . . . # # # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
# # # . . . # . . . . # . . . . . . . . . . # # # . . . . # . . . . . . . . . . # # # . . . . . . . . . # . # . . . . . . . # # # . . . . . . # # # . . . . . . . . . # # # . . . . . . . .
. . . . . . # . . # # # . . . . . . . . . . . . # . . . . # . . . . . . . . . . . . . . . . . . . . . . # # # . . . . . . . . . # . . . . . . # . # . . . . . . . . . # . # . . . . . . . .
. . . . . . # . . # . . . . . . . . . . . . # # # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . # . . . . . . # # # . . . . . . . . . # # # . . . . . . . .
. . . . . . . . . # # # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . # . . . . . . # . # . . . . . . . . . . . # . . . . . . . .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . # . . . . . . # # # . . . . . . . . . # # # . . . . . . . .
```

### 输出

```
0123456789
```

# 题解

## 作者：y2823774827y (赞：13)

从1到0枚举，找到当前数对比后面的数独特之处，遍历的时候一列一列来，由于
 $l_B \ge r_A + 2$没搜到一个数时可以多跳几列
 ```cpp
#include<cstdio>
using namespace std;
typedef long long LL;
LL n,m;
char a[20][100005];
int main(){
    scanf("%lld%lld",&n,&m);
    for(LL i=1;i<=n;++i){
        for(LL j=1;j<=m;++j)
            scanf(" %c",&a[i][j]);
    }
    for(LL i=1;i<=m;++i){
        for(LL j=1;j<=n;++j){
            if(a[j][i]=='#'){
                if(i>=m-1){
                    printf("1");
                    return 0;
                }else if(a[j][i+1]=='.'&&a[j+1][i+1]=='.'&&a[j+2][i+1]=='.'){
                    printf("1");
                    i+=1;
                }else{
                    if(a[j+1][i+2]=='#'&&a[j+3][i+2]=='.'){
                        printf("2");						
                    }else if(a[j+1][i]=='.'&&a[j+2][i]=='#'&&a[j+3][i]=='.'){
                        printf("3");
                    }else if(a[j][i+1]=='.'&&a[j+4][i+1]=='.'){
                        printf("4");
                    }else if(a[j+1][i]=='#'&&a[j+3][i]=='.'&&a[j+1][i+2]=='.'){
                        printf("5");
                    }else if(a[j+1][i]=='#'&&a[j+1][i+1]=='.'&&a[j+1][i+2]=='.'){
                        printf("6");
                    }else if(a[j+1][i]=='.'){
                        printf("7");
                    }else if(a[j+1][i]=='#'&&a[j+3][i]=='#'&&a[j+2][i+1]=='#'){
                        printf("8");
                    }else if(a[j+3][i]=='.'){
                        printf("9");
                    }else
                        printf("0");
                    i+=3;
                }
                break;
            }
        }
    }
    return 0;
}
```

---

## 作者：WAMonster (赞：11)

纯模拟。根据每个数字的特性和字符的排列分类讨论即可。

按列枚举判断，每列扫完一个数字后即放弃此列（因为这列不可能有数字了），跳到后面的列。2~0每个数字宽度为3，1的宽度为1，分别跳相应列数即可。

code：

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

char inp[20][100100];

vector<int> num;
int r, c;
char rchar() {
	char c = getchar();
	while(c == ' ' || c == '\n' || c == '\r') c = getchar();
	return c;
}


int main() {
	scanf("%d%d", &r, &c);
	memset(inp, '.', sizeof(inp));
	for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= c; ++j) 
			inp[i][j] = rchar();
		
	for(int j = 1; j <= c; ++j)
		for(int i = 1; i <= r; ++i) 
			if(inp[i][j] == '#' && inp[i - 1][j] == '.' && inp[i][j - 1] == '.') {//必须是左上角第一个字符才做判断
				if(inp[i + 1][j] == '#') {
					if(inp[i][j + 1] == '.') {
						if(inp[i + 2][j + 1] == '#') num.push_back(4), j += 3;
						else num.push_back(1), j += 1;
					}
					else {
						if(inp[i + 1][j + 2] == '.') {
							if(inp[i + 3][j] == '.') num.push_back(5), j += 3;
							else num.push_back(6), j += 3;
						}
						else {
							if(inp[i + 2][j + 1] == '#') {
								if(inp[i + 3][j] == '#') num.push_back(8), j += 3;
								else num.push_back(9), j += 3;
							}
							else num.push_back(0), j += 3;
						} 
						
					}
				}
				else {
					if(inp[i + 2][j + 1] == '#') {
						if(inp[i + 2][j + 1] == '#') {
							if(inp[i + 3][j] == '#') num.push_back(2), j += 3;
							else num.push_back(3), j += 3;
						}
					}
					else num.push_back(7), j += 3;
				}
			}
	for(int i = 0; i < num.size(); ++i) printf("%d", num[i]);
	return 0;
}
```

---

## 作者：一扶苏一 (赞：6)


## Solution

写完这篇题解整场比赛的题解我就全写了qwq~~到底谁是出题人啊喂（逃~~

看起来就很复杂的题，想想比赛的时候过了其他的所有题然而这个题连写的欲望都没有= =

看起来需要字符串判等，于是自然而然的会想到hash，于是我们就能轻而易举的写出下面的代码：(话说你谷什么时候资瓷py的高亮啊qwq)

```python
s = ["0" for i in range(5)]

MOD = (1 << 32)
x = 19620718
for i in range(5):
	s[i] = input()
	ll = len(s[i])
	for j in range(ll):
		k = 0
		if(s[i][j] == '#'):
			k = 10
		else:
			k = 20
		x ^= (x << k) % MOD
		x %= MOD
		x ^= (x >> k - 5) % MOD
		x %= MOD
print(x)
```

这份代码输入一个数字就可以得到hash值，例如：

![qwq](https://cdn.luogu.com.cn/upload/pic/45850.png)



这类异或哈希是最常见的hash，具体的，从上到下，从左到右扫描整个图，初始的hash值为19620718，如果该位置为 '#' 则$hash~~xor=~~ x~<<~10$，$hash~~xor=~~x << 5$，同理如果该位置为'.'，将10和5改为20和15。取模是为了方便C++在unsigned下操作。

然后就可以打出这张表

```cpp
void DDOSvoid_AK_IOI() {
	qwq[985634642u] = 1;
	qwq[1624219359u] = 2;
	qwq[3644615882u] = 3;
	qwq[2206558270u] = 4;
	qwq[3208977527u] = 5;
	qwq[3464952113u] = 6;
	qwq[3112560961u] = 7;
	qwq[2916542032u] = 8;
	qwq[754805991u] = 9;
	qwq[2232034402u] = 0;
}
```

于是我们从左到右，从上到下扫描整张表，如果这个位置是 '#' 就求这是哪个数字。然后清空整个数字的位置。因为是顺序扫描的，扫到的点一定是点阵的左上角。

注意到1的宽度和别的不一样，需要特判，此时观察1和其他数字的显著区别：$1$的第一行右侧一个格子是空，并且第三行右侧第一个格子是空。有且仅有 $1$ 满足这个特性，于是通过这个特征可以判断 $1$ 的存在。剩下的数字直接hash即可。

## Code

```cpp
#include <map>
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;
typedef unsigned int uit;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 100010;

int n, m;
char MU[15][maxn];
std::map<uit,int>qwq;

void DDOSvoid_AK_IOI();
int check(int x,int y);

int main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(m);
	for (rg int i = 1; i <= n; ++i) {
		for (rg int j = 1; j <= m; ++j) {
			MU[i][j] = IPT::GetChar();
			while ((MU[i][j] != '#') && (MU[i][j]) != '.') MU[i][j] = IPT::GetChar();
		}
	}
	for (rg int i = 1, dm = m + 1; i <= n; ++i) MU[i][dm] = '.';
	DDOSvoid_AK_IOI();
	for (rg int i = 1; i <= m; ++i) {
		for (rg int j = 1; j <= n; ++j) if (MU[j][i] == '#') {
			qw(check(j, i), ' ', false);
		}
	}
	putchar('\n');
	return 0;
}

void DDOSvoid_AK_IOI() {
	qwq[985634642u] = 1;
	qwq[1624219359u] = 2;
	qwq[3644615882u] = 3;
	qwq[2206558270u] = 4;
	qwq[3208977527u] = 5;
	qwq[3464952113u] = 6;
	qwq[3112560961u] = 7;
	qwq[2916542032u] = 8;
	qwq[754805991u] = 9;
	qwq[2232034402u] = 0;
}

int check(int x, int y) {
	if (MU[x][y + 1] == '.') {
		if (MU[x + 2][y + 1] == '.') {
			for (rg int i = 0; i < 5; ++i) MU[x + i][y] = '.';
			return 1;
		}
	}
	uit _ret = 19620718;
	for (rg int i = 0; i < 5; ++i) {
		for (rg int j = 0; j < 3; ++j) {
			int k = 0;
			if (MU[x + i][j + y] == '#') k = 10;
			else k = 20;
			_ret ^= _ret << k;
			_ret ^= _ret >> (k - 5);
			MU[x + i][y + j] = '.';
		}
	}
	return qwq[_ret];
}
```

#### p.s.：DDOSvoid当然不是我辣2333

---

## 作者：LinkZelda (赞：4)

# 看到各位大佬的暴力手法，我也来写一个不一样的暴力。
我的不一样在于：我用了一个 $for$ 循环，对每一个数字直接进行 $if$ 语句判断是否满足，然后如果满足就 $ans$ 加上这个对应的数字（$ans$ 是字符串）。代码自我感觉~~简单清晰易懂~~良好（其实只要找到 $#$ 后就调用函数就好）。

具体请看代码（全注释AC）：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
string ans="";//定义ans为空（初始化）
int n,m,k[10]={8,6,9,3,2,0,5,7,4,1};//这个顺序是因为如果直接按0-9判断的话，满足8的格子会先满足2的情况，所以要改变顺序
char a[11][100005]={0};//初始化 
void dfs(int x,int y)
{
    for(int i=0;i<=9;i++)
    {
        switch(k[i])//注意我的判断顺序
        {
            case 1://如果是一，判断下面四个是否为‘#’
                if(a[x+1][y]=='#'&&a[x+2][y]=='#'&&a[x+3][y]=='#'&&a[x+4][y]=='#')
				{
                			ans+="1";//如果满足这种情况，ans加上一个"1" 
                			return;
				}
                break;
            case 2://二的情况，方法同上
                if(a[x][y+1]=='#'&&a[x][y+2]=='#'&&a[x+1][y+2]=='#'&&a[x+2][y]=='#'&&a[x+2][y+1]=='#'&&a[x+2][y+2]=='#'&&a[x+3][y]=='#'&&a[x+4][y]=='#'&&a[x+4][y+1]=='#'&&a[x+4][y+2]=='#')
				{
                			ans+="2";//如果满足这种情况，ans加上一个"2"
                			return;
				}
                break;
            case 3://三的情况，方法同上
                if(a[x][y+1]=='#'&&a[x][y+2]=='#'&&a[x+1][y+2]=='#'&&a[x+2][y]=='#'&&a[x+2][y+1]=='#'&&a[x+2][y+2]=='#'&&a[x+3][y+2]=='#'&&a[x+4][y]=='#'&&a[x+4][y+1]=='#'&&a[x+4][y+2]=='#')
				{
                			ans+="3";//如果满足这种情况，ans加上一个"3"
                			return;
				}
                break;
            case 4://四的情况，方法同上
                if(a[x][y+2]=='#'&&a[x+1][y]=='#'&&a[x+1][y+2]=='#'&&a[x+2][y]=='#'&&a[x+2][y+1]=='#'&&a[x+2][y+2]=='#'&&a[x+3][y+2]=='#'&&a[x+4][y+2]=='#')
				{
                			ans+="4";//如果满足这种情况，ans加上一个"4"
                			return;
				}
                break;
            case 5://五的情况，方法同上
                if(a[x][y+1]=='#'&&a[x][y+2]=='#'&&a[x+1][y]=='#'&&a[x+2][y]=='#'&&a[x+2][y+1]=='#'&&a[x+2][y+2]=='#'&&a[x+3][y+2]=='#'&&a[x+4][y]=='#'&&a[x+4][y+1]=='#'&&a[x+4][y+2]=='#')
				{
                			ans+="5";//如果满足这种情况，ans加上一个"5"
                			return;
				}
                break;
            case 6://六的情况，方法同上
                if(a[x+1][y]=='#'&&a[x+2][y]=='#'&&a[x+3][y]=='#'&&a[x+4][y]=='#'&&a[x][y+1]=='#'&&a[x][y+2]=='#'&&a[x+2][y+1]=='#'&&a[x+2][y+2]=='#'&&a[x+4][y+1]=='#'&&a[x+4][y+2]=='#'&&a[x+3][y+2]=='#')
				{
                			ans+="6";//如果满足这种情况，ans加上一个"6"
                			return;
				}
                break;
            case 7://七的情况，方法同上
                if(a[x+1][y+2]=='#'&&a[x+2][y+2]=='#'&&a[x+3][y+2]=='#'&&a[x+4][y+2]=='#'&&a[x][y+1]=='#'&&a[x][y]=='#'&&a[x][y+2]=='#')
				{
                			ans+="7";//如果满足这种情况，ans加上一个"7"
                			return;
				}
                break;
            case 8://八的情况，方法同上
                if(a[x+1][y]=='#'&&a[x+2][y]=='#'&&a[x+3][y]=='#'&&a[x+4][y]=='#'&&a[x][y+1]=='#'&&a[x][y+2]=='#'&&a[x+2][y+1]=='#'&&a[x+2][y+2]=='#'&&a[x+4][y+1]=='#'&&a[x+4][y+2]=='#'&&a[x+3][y+2]=='#'&&a[x+1][y+2]=='#')
				{
                			ans+="8";//如果满足这种情况，ans加上一个"8"
                			return;
				}
                break;
            case 9://九的情况，方法同上
                if(a[x+1][y]=='#'&&a[x+2][y]=='#'&&a[x+4][y]=='#'&&a[x][y+1]=='#'&&a[x][y+2]=='#'&&a[x+2][y+1]=='#'&&a[x+2][y+2]=='#'&&a[x+4][y+1]=='#'&&a[x+4][y+2]=='#'&&a[x+3][y+2]=='#'&&a[x+1][y+2]=='#')
				{
                			ans+="9";//如果满足这种情况，ans加上一个"9"
                			return;
				}
                break;
            case 0://零的情况，方法同上
                if(a[x+1][y]=='#'&&a[x+2][y]=='#'&&a[x+3][y]=='#'&&a[x+4][y]=='#'&&a[x][y+1]=='#'&&a[x][y+2]=='#'&&a[x+2][y+2]=='#'&&a[x+4][y+1]=='#'&&a[x+4][y+2]=='#'&&a[x+3][y+2]=='#'&&a[x+1][y+2]=='#')
				{
                			ans+="0";//如果满足这种情况，ans加上一个"0"
                			return;
				}
                break;
        }
    }
}
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)//输入
    {
    	for(int j=0;j<m;j++)
    	{
    		cin>>a[i][j];
		}
	}
    for(int j=0;j<m;j++)//注意！这里要从上至下再从左到右，否则会判断多次同列的“#”，可能会tle
    {
    	for(int i=0;i<n;i++)
    	{
       	 	if(a[i][j]=='#')
        	{
        		dfs(i,j);
        		if(ans[ans.size()-1]=='1') j+=2;//如果判断出的是一，就移左两列，可以少判断很多格
        		else j+=4;//不是一的话，因为本来数字就占用三格，就要移左4格开始判断
        		i=-1;//i=-1，因为循环会自动加一，所以下一个循环是从a[0][j]开始判断
        	}
    	}
	}
    for(int i=0;i<ans.size();i++)
	{
		cout<<ans[i];//输出字符串
	}
    return 0;
}
```

暴力难写，调试不易，希望管理大大通过（已改排版再次提交）

---

## 作者：JK_LOVER (赞：3)

还是再代码里说吧，见下：

```cpp

/*

 
	首先声明本蒟蒻不会高级的算法，dalao们将就一下吧 
	分析： 
	零：存图； 
	一：求连通块；
	二：判断连通块的数字；
	三：保存数字；
	四：输出； 
---------------------------------------------	
华丽的分割线 
	
	
	1：用dfs求联通块；
	2：用联通块的特殊性判断数字； 
	方法如下：
	3.输出呗 
-------------------------------------------------
不华丽的分割线	


数字的组成方式：
#   # # #   # # #   # . #   # # #   # # #   # # #   # # #   # # #   # # # 
#   . . #   . . #   # . #   # . .   # . .   . . #   # . #   # . #   # . # 
#   # # #   # # #   # # #   # # #   # # #   . . #   # # #   # # #   # . # 
#   # . .   . . #   . . #   . . #   # . #   . . #   # . #   . . #   # . # 
#   # # #   # # #   . . #   # # #   # # #   . . #   # # #   # # #   # # # 

所代表的数字：
1     2       3       4       5       6       7       8       9       0


可以看出“1”是5个“*”组成的； 
“2，3，5”是11个“*”组成的； 
“4”是9个“*”组成的； 
“6，9，0”是12个“*”组成的； 
“8”是13个“*” 组成的；
“7”是7个“*”组成的；

通过*的个数可以判断一部分连通块的种类； 

thus 现在只需对2，3，5和6，8，0 判断；
 2，3，5；中只有2的（2，1）和（4，3）是‘.’；3的（2，1）和（4，1）是‘.’；
 6，9，0：中只有6的（2，3）是‘.’；9的（4，1）是‘.’；0的（3，2）是‘.’ 
所以对联通块的判断也结束了

上代码吧
	
*/
#include<bits/stdc++.h>

using namespace std;

int n,m,ss;
int ans=0;//数字的个数 
char tu[110][100990];
bool pd[110][100990];// 判断 
char su[110][100990];
int bao[109900];// 数字保存 
int dx[4]={0,0,1,-1};//四个方向 
int dy[4]={1,-1,0,0};
void dfs(int x,int y)
{
	if(x<0||y<0||x>=n||y>=m||!pd[x][y]) return;//越界判断 
	pd[x][y]=false;
	ss++;//联通块的个数 
	for(int i=0;i<4;i++)
	{
		dfs(x+dx[i],y+dy[i]);			
	}
}
int main()
{
	memset(pd,true,sizeof(pd));
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{//存图 
			cin>>tu[i][j];
			su[i][j]=tu[i][j];
			if(tu[i][j]=='.') pd[i][j]=false;
		}
	}
	for(int j=0;j<m;j++)
	{
		for(int i=0;i<n;i++)
		{
			ss=0;
			dfs(i,j);//神奇的判定，还算好理解 ，先通过联通快的个数筛一次，再枚举每个数字的特殊点 
			if(ss==5) bao[ans++]=1;
			if(ss==11)
			{
			if(su[i+1][j]=='.'&&su[i+3][j]=='#') 
			bao[ans++]=2;
			else if(su[i+1][j]=='.'&&su[i+3][j]=='.')
			bao[ans++]=3;
			else bao[ans++]=5;
			}
			if(ss==12) 
			{
			if(su[i+1][j+2]=='.') bao[ans++]=6;
			else if(su[i+3][j]=='.') bao[ans++]=9;
			else {bao[ans++]=0;}
			}
			if(ss==13) bao[ans++]=8;
			if(ss==9) bao[ans++]=4;
			if(ss==7) bao[ans++]=7;
		}
	}
	for(int i=0;i<ans;i++)//输出 
	cout<<bao[i];
	return 0;
}

```


---

## 作者：csdfret (赞：2)

因为每个数字左上角都是`#`，所以可以从左到右，从上到下枚举图上每个点，如果是`#`号就用1-9的模型覆盖，覆盖成功就把数字用`.`覆盖掉。

上代码
```
#include <iostream>
using namespace std;
char m[20][100010];
//打数字表
char num[10][5][3]={
{
'#','#','#',
'#','.','#',
'#','.','#',
'#','.','#',
'#','#','#'
},
{//1的图形只用到前两列，为防把0，8误判成1，在右边多加一列小数点
'#','.',' ',
'#','.',' ',
'#','.',' ',
'#','.',' ',
'#','.',' ',
},
{
'#','#','#',
'.','.','#',
'#','#','#',
'#','.','.',
'#','#','#'
},
{
'#','#','#',
'.','.','#',
'#','#','#',
'.','.','#',
'#','#','#'
},
{
'#','.','#',
'#','.','#',
'#','#','#',
'.','.','#',
'.','.','#'
},
{
'#','#','#',
'#','.','.',
'#','#','#',
'.','.','#',
'#','#','#'
},
{
'#','#','#',
'#','.','.',
'#','#','#',
'#','.','#',
'#','#','#'
},
{
'#','#','#',
'.','.','#',
'.','.','#',
'.','.','#',
'.','.','#'
},
{
'#','#','#',
'#','.','#',
'#','#','#',
'#','.','#',
'#','#','#'
},
{
'#','#','#',
'#','.','#',
'#','#','#',
'.','.','#',
'#','#','#'
}
};
void fg(int x,int y)//覆盖
{
	bool yes;
	for(int kk=0;kk<=9;kk++)//枚举数字
	if(kk==1)//特判1
	{
	  yes=1;
	  for(int ii=0;ii<=4;ii++)
	    for(int jj=0;jj<=1;jj++)
	      if(m[x+ii][y+jj]!=num[kk][ii][jj]) 
	      yes=0;
	  if(yes==1) //覆盖成功，用.填掉四格
	  {
	  	cout<<kk;
	  	for(int iii=x;iii<=x+4;iii++)
	  	  m[iii][y]='.';
	  	return;
	  }
	  }
	else//其他数字同理
	{
	  yes=1;
	  for(int ii=0;ii<=4;ii++)
	    for(int jj=0;jj<=2;jj++)
	      if(m[x+ii][y+jj]!=num[kk][ii][jj]) 
	      yes=0;
	  if(yes==1) 
	  {
	  	cout<<kk;
	  	for(int iii=x;iii<=x+4;iii++)
	  	  for(int jjj=y;jjj<=y+2;jjj++)
	  	  m[iii][jjj]='.';
	  	return;
	  }
	 }   
	 return;
}
int main()
{
	int a,b;
	cin>>a>>b;
    //为判出最右边的1，在右边加一列小数点
	for(int i=0;i<=a;i++)
	  m[i][b+1]='.';
	for(int i=1;i<=a;i++)
	  for(int j=1;j<=b;j++)
	    cin>>m[i][j];
	for(int j=0;j<=b;j++)
	   for(int i=1;i<=a;i++)
        if(m[i][j]=='#')
        {fg(i,j);continue;}//小优化
	return 0;
 } 
 ```

---

## 作者：斗神_君莫笑 (赞：1)

~~就没有人像我一样赤裸裸的暴力吗~~    
看到本题，很明显想出的第一解法就是扫过去以此判断  
那么我是这么想的，也是这么做的  
这种做法最困难的部分就是处理每个数字所对应的表  
于是我写了一个简易的数据生成器  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("1.txt","w",stdout);
	int ch=getchar();
	for(int i=1;i<=15;++i){
		while(ch!='.'&&ch!='#')ch=getchar();
		printf("'%c',",ch);
		ch=0;
	}
	return 0;
}
/*
# # # 
# . #  
# . #  
# . #   
# # #   */
```
显然我们只需要录入每个数字本身，就可以输出它所对应的表  
你问我为什么不写好一点的？其实只是因为我懒啊~   
~~有完善它的时间还不如复制粘贴~~
```cpp
#include<bits/stdc++.h>
using namespace std;
char is_2[5][3]={'#','#','#','.','.','#','#','#','#','#','.','.','#','#','#'};
char is_3[5][3]={'#','#','#','.','.','#','#','#','#','.','.','#','#','#','#'};
char is_4[5][3]={'#','.','#','#','.','#','#','#','#','.','.','#','.','.','#'};//
char is_5[5][3]={'#','#','#','#','.','.','#','#','#','.','.','#','#','#','#'};
char is_6[5][3]={'#','#','#','#','.','.','#','#','#','#','.','#','#','#','#'};
char is_7[5][3]={'#','#','#','.','.','#','.','.','#','.','.','#','.','.','#'};
char is_8[5][3]={'#','#','#','#','.','#','#','#','#','#','.','#','#','#','#'};
char is_9[5][3]={'#','#','#','#','.','#','#','#','#','.','.','#','#','#','#'};
char is_0[5][3]={'#','#','#','#','.','#','#','.','#','#','.','#','#','#','#'};
int a[11][100010],s[100010],top;
int find_num(int x,int y){
	int num[10];
	for(int i=0;i<=9;++i)num[i]=1;
	num[1]=0;
	for(int i=0;i<5;++i)
		for(int j=0;j<3;++j){
			if(a[i+x][j+y]!=is_2[i][j])num[2]=0;
			if(a[i+x][j+y]!=is_3[i][j])num[3]=0;
			if(a[i+x][j+y]!=is_4[i][j])num[4]=0;
			if(a[i+x][j+y]!=is_5[i][j])num[5]=0;
			if(a[i+x][j+y]!=is_6[i][j])num[6]=0;
			if(a[i+x][j+y]!=is_7[i][j])num[7]=0;
			if(a[i+x][j+y]!=is_8[i][j])num[8]=0;
			if(a[i+x][j+y]!=is_9[i][j])num[9]=0;
			if(a[i+x][j+y]!=is_0[i][j])num[0]=0;
		}
	for(int i=0;i<=9;++i)
		if(num[i]){
			s[++top]=i;
			return 3;
		}
	s[++top]=1;
	return 1;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			char ch=getchar();
			while(ch!='#'&&ch!='.')ch=getchar();
			a[i][j]=ch;
		}
	for(int j=1;j<=m;++j)
		for(int i=1;i<=n;++i)
			if(a[i][j]=='#'){
				j+=find_num(i,j);//为了跳过当前数字的范围
				break;
			}
	for(int i=1;i<=top;++i)
		printf("%d",s[i]);
	return 0;
}
```


---

## 作者：installb (赞：1)

看上去很吓人的题目 其实仔细想想并不难写  
### 这里先做一个小的处理
2~0都是3x5的矩阵 只有这个1是1x5 由于题目中说了数字不会贴在一起 我们可以把1左右各加一列 '.'  
就像这样
```cpp
数字的组成方式：
. # .   # # #   # # #   # . #   # # #   # # #   # # #   # # #   # # #   # # # 
. # .   . . #   . . #   # . #   # . .   # . .   . . #   # . #   # . #   # . # 
. # .   # # #   # # #   # # #   # # #   # # #   . . #   # # #   # # #   # . # 
. # .   # . .   . . #   . . #   . . #   # . #   . . #   # . #   . . #   # . # 
. # .   # # #   # # #   . . #   # # #   # # #   . . #   # # #   # # #   # # # 

所代表的数字：
  1       2       3       4       5       6       7       8       9       0
```
题目中又说 数字不会上下排放 只会左右排放 所以可以建立一个数组存每一列有多少个'#'  
然后从头到尾扫一遍，如果有一列含有'#'数不是零，就通过每三列的'#'数量判断这是哪个数  
这里考虑到1的问题我是枚举中间那一列
```cpp
数字的组成方式：
0 1 0   4 3 4   4 4 5   3 1 5   4 3 4   5 3 4   1 1 5   5 3 5   4 3 5   5 2 5
. # .   # # #   # # #   # . #   # # #   # # #   # # #   # # #   # # #   # # # 
. # .   . . #   . . #   # . #   # . .   # . .   . . #   # . #   # . #   # . # 
. # .   # # #   # # #   # # #   # # #   # # #   . . #   # # #   # # #   # . # 
. # .   # . .   . . #   . . #   . . #   # . #   . . #   # . #   . . #   # . # 
. # .   # # #   # # #   . . #   # # #   # # #   . . #   # # #   # # #   # # # 

所代表的数字：
  1       2       3       4       5       6       7       8       9       0
```
但是2,5是相同的,~~那就写个特判吧~~
```cpp
# # #   # # #
. . *   # . *
# # #   # # #
# . .   . . #
# # #   # # #
```
2和5打星号的地方是不一样的 从上往下枚举知道找到第一个'#' 然后通过那一格判断2还是5  
~~好吧，我承认这个方法确实有点繁 不过比较好想好写点~~
## 上代码
```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
#define LL long long
using namespace std;
int mp[15][100050] = {0}; // 存图
int row[100050] = {0}; // 存每列'#'数量
char ch;
int main(){
	int r,c;
	cin >> r >> c;
	for(int i = 1;i <= r;i ++){
		for(int j = 1;j <= c;j ++){
			cin >> ch;
			if(ch == '#') mp[i][j] = 1;
			row[j] += mp[i][j]; // 有'#'就+1
		}
	}
	for(int j = 1;j <= c;j ++){
    	// 判断2,5
		if(row[j] == 3 && row[j - 1] == 4 && row[j + 1] == 4){
			for(int i = 1;i <= r;i ++){
				if(mp[i][j + 1]){
					if(mp[i + 1][j + 1]){
						printf("2");
					}
					else{
						printf("5");
					}
					break;
				}
			}
		}
        // 直接判断出2,5以外的所有数
		if(row[j] == 5 && row[j - 1] == 0 && row[j + 1] == 0) printf("1");
		if(row[j] == 3 && row[j - 1] == 3 && row[j + 1] == 5) printf("3");
		if(row[j] == 1 && row[j - 1] == 3 && row[j + 1] == 5) printf("4");
		if(row[j] == 3 && row[j - 1] == 5 && row[j + 1] == 4) printf("6");
		if(row[j] == 1 && row[j - 1] == 1 && row[j + 1] == 5) printf("7");
		if(row[j] == 3 && row[j - 1] == 5 && row[j + 1] == 5) printf("8");
		if(row[j] == 3 && row[j - 1] == 4 && row[j + 1] == 5) printf("9");
		if(row[j] == 2 && row[j - 1] == 5 && row[j + 1] == 5) printf("0");
	}
	return 0;
}
```

---

## 作者：SSerxhs (赞：1)

简单模拟题。

由于任意两个数字之间有空列，且数字不可能上下摆放，所以直接从左往右扫描，如果为空列且l指针紧贴这一列则把l指针指向这一列，如果为空列且l指针不紧贴这一列则说明l指针到这一列之间有非空列，即有数字，根据各个数字的特点判断数字，同时把l指针移动到当前列。判断数字时并不需要O(10·3·5)判断，只需要看未排除的数字中最独特的那一个即可。个人感觉自己这个顺序会比较简洁。

```cpp
// luogu-judger-enable-o2
#include <stdio.h>
#include <math.h>
const int N=1e5+10;
char s[12][N],c;
int n,m,i,j,k,l;
bool pd;
int main()
{
    scanf("%d %d",&n,&m);
    c=getchar();
    for (i=1;i<=n;i++)
    {
        while ((c!='.')&&(c!='#')) c=getchar();
        for (j=1;j<=m;j++)
        {
            s[i][j]=c;if ((i<n)||(j<m)) getchar();c=getchar();
        }
    }
    l=0;
    ++m;
    for (i=1;i<=n;i++) s[i][0]=s[i][m]='.';
    for (i=1;i<=m;i++)
    {
        pd=0;
        for (j=1;j<=n;j++) if (s[j][i]=='#')
        {
            pd=1;
            break;
        }
        if (pd) continue;
        if (l+1>=i)
        {
            l=i;
            continue;
        }
        if (l==i-2)
        {
            printf("1");
            l=i;continue;
        }
        ++l;
        for (j=1;j<=n-4;j++) if (s[j][l]=='#')
        {
            if (s[j+3][l+2]=='.')
            {
                printf("2");
                break;
            }
            if (s[j][l+1]=='.')
            {
                printf("4");
                break;
            }
            if (s[j+4][l]=='.')
            {
                printf("7");
                break;
            }
            if (s[j+1][l]=='.')
            {
                printf("3");
                break;
            }
            if (s[j+2][l+1]=='.')
            {
                printf("0");
                break;
            }
            if ((s[j+3][l]=='#')&&(s[j+1][l+2]=='#'))
            {
                printf("8");
                break;
            }
            if (s[j+3][l]=='#')
            {
                printf("6");
                break;
            }
            if (s[j+1][l+2]=='#')
            {
                printf("9");
                break;
            }
            printf("5");
            break;
        }
        l+=3;
    }
}
```

---

## 作者：公主殿下MIKU (赞：1)

这题因为最多只有十行，而每个数字有5行，我们只需枚举前n-4行，因为数字相互之间不会重合，所以只需找到左上角第一个"#",然后扫描3*5 的小矩阵 ，根据每个数字的小特征，暴力标记就行
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long 
using namespace std;
int r,c;
char a[11][100001];
bool vis[100001];
int read()
{
    int p=1;
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') p=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*p;
}
void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int ans=0;
int b[1000001],num;
int main()
{
    r=read();c=read();
    for(int i=1;i<=r;i++)
    for(int j=1;j<=c;j++)
     cin>>a[i][j];
    for(int i=1;i<=c;i++)
    for(int j=1;j<=r;j++)
    {
        if(a[j][i]=='#'&&!vis[i])
        {
            int sum=0;
            for(int k=0;k<5;k++)
            if(a[j+k][i]=='#'&&(a[j+k][i+1]=='.'||i+1>c)) sum++;//找1
            if(sum==5)
            {
                b[++num]=1;
                vis[i]=1;
                continue;
            }
        }
        if(a[j][i]=='#'&&!vis[i]&&!vis[i+1]&&!vis[i+2])
        {
            bool p=0;
            for(int k=0;k<3;k++) if(a[j][i+k]=='.')//找4
            {
                b[++num]=4;
                vis[i]=1,vis[i+1]=1,vis[i+2]=1;
                p=1;
                continue;
            }
            if(p) continue;
            int sum=0;
            for(int k=0;k<5;k++)
            {
                if(a[j+k][i]=='.') sum++;
            }
            if(sum==4)
            {
                b[++num]=7;
                vis[i]=1,vis[i+1]=1,vis[i+2]=1;找7
                continue;
            }
            else
            {
                if(sum==1)
                {
                    if(a[j+1][i]=='.'&&a[j+3][i]=='#')
                    {
                        b[++num]=2;
                        vis[i]=1,vis[i+1]=1,vis[i+2]=1;//找2
                        continue;
                    }
                    else
                    {
                        if(a[j+1][i+2]=='.')
                        {
                            b[++num]=5;//找5
                        }
                        else b[++num]=9;//找九
                        vis[i]=1,vis[i+1]=1,vis[i+2]=1;
                        continue;
                    }
                }
                if(sum==2)
                {
                    b[++num]=3;//找三
                    vis[i]=1,vis[i+1]=1,vis[i+2]=1;
                    continue;
                }
                else
                {
                    if(a[j+1][i+2]=='.') b[++num]=6;//找6
                    else
                    if(a[j+1][i+2]=='#'&&a[j+2][i+1]=='#') b[++num]=8;//找8
                    else b[++num]=0;//找0
                    vis[i]=1,vis[i+1]=1,vis[i+2]=1;
                }
            }
        }
    }
    for(int i=1;i<=num;i++) cout<<b[i];//依次输出
    return 0;
}
````
管理大大求过

---

## 作者：pipiispig (赞：0)

#我好弱呀，只会模拟，写了个极其暴力的代码w(ﾟДﾟ)w
```#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
char s[15][100100];
int r,c,w=0,q=0;
void o(int x,int y){//（判断第3行）
	for(int i=0;i<3;i++)if(s[x+2][y+i]!='#')w=1;
}
void f(int x,int y){//判断最后一行
	for(int i=0;i<3;i++)if(s[x+4][y+i]!='#')q=1;
}
int cherk(int x,int y){//分别判定是否为数字（1,2,3,4,5,6,7,8,9,0）
	w=0,q=0;
	int p=0;
	for(int i=0;i<5;i++){
		if(s[x+i][y]!='#'||s[x+i][y+1]=='#'||s[x+i][y-1]=='#'){
		 break;
		}
		p=p+1;
	}		
	if(p==5)return 1;
	p=0;
	o(x,y);f(x,y);
	if(s[x][y+2]!='#')return 0;
	if(s[x][y+1]!='#'){
		if(s[x+1][y]!='#'||s[x+1][y+2]!='#'){
			return 0;
		}
		if(w==1)return 0;
		if(s[x+3][y+2]!='#'||s[x+4][y+2]!='#')return 0;	
		return 4;
	}
	if(s[x+1][y+1]=='#')return 0;
	if(s[x+1][y+2]=='#'){
		if(s[x+1][y]!='#'){
			for(int i=0;i<5;i++){
				if(s[x+i][y+2]!='#'||s[x+i+1][y+1]=='#'){
					break;
				}
				p++;
			}
			if(p==5)return 7;
			p=0;
			if(q==1)return 0;
			if(w==1)return 0;
			if(s[x+3][y]=='#')return 2;
			if(s[x+3][y+2]=='#')return 3;
			return 0;
		}
		else{
			if(q==1)return 0;
			if(s[x+2][y]!='#'||s[x+2][y+2]!='#')return 0;
			if(s[x+2][y+1]!='#'){
				if(s[x+3][y]!='#'||s[x+3][y+2]!='#')return 0;
				return 10;
			}
			else {
				if(s[x+3][y+1]=='#')return 0;
				if(s[x+3][y+2]!='#')return 0; 
				if(s[x+3][y]=='#')return 8;
				else return 9;
			}
		}
	}
	if(s[x+1][y]=='#'){
		if(w==1)return 0;
		if(q==1)return 0;
		if(s[x+3][y+1]=='#')return 0;
		if(s[x+3][y+2]!='#')return 0;
		if(s[x+3][y]=='#')return 6;
		return 5;
	}
	return 0;
}
int main(){//愉快的开始主程序
	cin>>r>>c;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			cin>>s[i][j];
		}
	}
		for(int j=1;j<=c;j++){
			for(int i=1;i<=r;i++){
			if(s[i][j]=='#'){
					int w=cherk(i,j);
					if(w==1){
						cout<<1;
						j=j+1;
						break;
					}
					if(w>=2){
						if(w==10)cout<<0;
						else cout<<w;
						j=j+3;
						break;
				}
			} 
		}
	}
}
```
##我好弱呀，一个水题让我写了100多行QAQ

---

## 作者：NGC7841 (赞：0)

发一个朴素的hash的题解。。
每个数字左上都是#，扫起来很方便，注意特判1就好了。
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
bool g[20][100010];
int n,m,ans[100010],cnt;
const int hash[]={32319,31,24253,22207,28831,30391,32439,16927,32447,30399};//每个数字的hash值
int GetNum(int row,int col){
    int tmp=0;
    for(int j=col;j<=col+2;j++)
	    for(int i=row;i<=row+4;i++)
		    tmp=(tmp<<1)+g[i][j];
	for(int i=0;i<=9;i++)
	    if(hash[i] == tmp)
		    return i;
}
void Go(int col){
    if(col > m) return;
    int row=1,is1=1;
	while(!g[row][col]){//空列
	    if(row++ <= n) continue;
		Go(col+1);
		return;
	}
	for(int i=1;i<=4;i++)
	    if(!g[row+i][col])
		    is1=0;
    if(!is1 || g[row][col+1]){//不是1
	    ans[++cnt]=GetNum(row,col);
	    Go(col+4);
	}
	else{//是1
	    ans[++cnt]=1;
	    Go(col+2);
	}
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
	    for(int j=1;j<=m;j++){
	        char ch=getchar();
		    while(ch!='.'&&ch!='#') ch=getchar();
		    if(ch == '#') g[i][j]=1;
	    }
    }
    Go(1);
    for(int i=1;i<=cnt;i++) printf("%d",ans[i]);
    printf("\n");
    return 0;
}
```

---

