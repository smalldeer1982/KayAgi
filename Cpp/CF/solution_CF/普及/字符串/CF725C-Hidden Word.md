# Hidden Word

## 题目描述

Let’s define a grid to be a set of tiles with $ 2 $ rows and $ 13 $ columns. Each tile has an English letter written in it. The letters don't have to be unique: there might be two or more tiles with the same letter written on them. Here is an example of a grid:

 `ABCDEFGHIJKLM<br></br>NOPQRSTUVWXYZ`We say that two tiles are adjacent if they share a side or a corner. In the example grid above, the tile with the letter 'A' is adjacent only to the tiles with letters 'B', 'N', and 'O'. A tile is not adjacent to itself.

A sequence of tiles is called a path if each tile in the sequence is adjacent to the tile which follows it (except for the last tile in the sequence, which of course has no successor). In this example, "ABC" is a path, and so is "KXWIHIJK". "MAB" is not a path because 'M' is not adjacent to 'A'. A single tile can be used more than once by a path (though the tile cannot occupy two consecutive places in the path because no tile is adjacent to itself).

You’re given a string $ s $ which consists of $ 27 $ upper-case English letters. Each English letter occurs at least once in $ s $ . Find a grid that contains a path whose tiles, viewed in the order that the path visits them, form the string $ s $ . If there’s no solution, print "Impossible" (without the quotes).

## 样例 #1

### 输入

```
ABCDEFGHIJKLMNOPQRSGTUVWXYZ
```

### 输出

```
YXWVUTGHIJKLM
ZABCDEFSRQPON
```

## 样例 #2

### 输入

```
BUVTYZFQSNRIWOXXGJLKACPEMDH
```

### 输出

```
Impossible
```

# 题解

## 作者：igAC (赞：2)

# $\text{Describe}$

[洛谷link](https://www.luogu.com.cn/problem/CF725C)

[Codeforces link](https://codeforces.com/contest/725/problem/C)

简要题意：

定义网格为 $2 \times 13$ 的矩阵：

```
ABCDEFGHIJKLM
ZYXWVUTSRQPON
```

与一个元素相邻的元素为它的八个方向上的元素（上、下、左、右、左上、右上、左下、右下）。

定义路径为从网格某一个元素开始往与它相邻的元素上走，所遍历的元素。

接下来给定一条路径，请你构造出包含这条路径的网格。

对于上矩阵：``ABCDEFGHIJKLMNOKPWRSTUVWXZQ`` 就是一条合法的路径。

这条路径长度为 $27$，仅包含大写字母，且每个字母都至少出现一次。

# $\text{Solution}$

模拟赛 $\text H$ 题，简单题。

让两个重复的字符中间的字符平分到两行即可，可以证明这样一定是正确的。

无解的情况就是两个字符连续的时候，显然找不到合法的网格。

感觉这道题评蓝有点虚高了。

# $\text{Code}$

```cpp
//模拟赛 H 题 
#include<bits/stdc++.h>
#define ll long long
#define N 50
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
string s;
map<char,int>mp;
char wish;
int n,ans[2][N];
int p1,p2;
int main(){
	cin>>s;n=s.length();s+=s;s=" "+s;
	for(int i=1;i<=n;++i){
		if(mp[s[i]]){
			p1=mp[s[i]];
			p2=i,wish=s[i];
		}
		mp[s[i]]=i;
	}
	if(p2==p1+1){
		puts("Impossible");
		return 0;
	}
	int space=(p2-p1+1)>>1,cnt=p1;
	ans[0][13-space+1]=wish;
	for(int i=13-space+2;i<=13;++i) ans[0][i]=s[++cnt];
	for(int i=13;i>=1;--i){
		++cnt;
		if(cnt==p2) ++cnt;
		ans[1][i]=s[cnt];
	}
	for(int i=1;i<=13-space;++i) ans[0][i]=s[++cnt];
	for(int i=0;i<2;++i){
		for(int j=1;j<=13;++j){
			printf("%c",ans[i][j]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：JLGxy (赞：0)

因为给定的字符串长度为 $27$，并且每个字母至少出现 $1$ 次可知，只会有 $1$ 个字母重复出现。因此可以先判断出这个重复字母两次出现的位置是否相邻，如果相邻就无解；否则，就把这对字符两侧的字母都平分到两行中，然后总可以按照这种顺序构造出一组解：

![](https://cdn.luogu.com.cn/upload/image_hosting/54inunwo.png)

```cpp
#include <cstring>
#include <iostream>

using namespace std;
int mark[305];  // 标记第一次出现的位置
char ans[31][2];  // 存答案
int main()
{
    string s;
    cin >> s;
    int a, b;  // 用于存字母重复出现的位置
    memset(mark, -1, sizeof(mark));
    for (int i = 0; i <= 26; i++) {
        // 判断无解
        if (i < 26 && s[i] == s[i + 1]) {
            cout << "Impossible";
            return 0;
        }
        // 标记每个字母第一次出现的位置
        if (mark[(int)s[i]] != -1)
            a = mark[(int)s[i]], b = i;
        else  // 重复出现
            mark[(int)s[i]] = i;
    }
    // 使这对字符前后的字符数量相差不超过 1
    while (a > 26 - b)
        s += *s.begin(), s.erase(s.begin()), a--, b--;
    while (a < 25 - b)
        s = *s.rbegin() + s, s.erase(s.end() - 1), a++, b++;
    // 第一行直接挨着填
    for (int i = 0; i < 13; i++)
        ans[i][1] = s[i];
    int j = 13;
    for (int i = 12; i >= 0; i--, j++) {
        // 第二行判断有没有重复出现，重复就不填了
        if (ans[i][1] == s[j] || ans[i + 1][1] == s[j])
            j++;
        ans[i][0] = s[j];
    }
    // 输出
    for (int i = 0; i < 13; i++)
        cout << ans[i][0];
    cout << endl;
    for (int i = 0; i < 13; i++)
        cout << ans[i][1];
    return 0;
}
```

---

