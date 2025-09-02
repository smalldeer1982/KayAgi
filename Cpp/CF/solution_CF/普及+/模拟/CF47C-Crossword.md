# Crossword

## 题目描述

Vasya trains to compose crossword puzzles. He can only compose crosswords of a very simplе type so far. All of them consist of exactly six words; the words can be read only from top to bottom vertically and from the left to the right horizontally. The words are arranged in the form of a rectangular "eight" or infinity sign, not necessarily symmetrical.

The top-left corner of the crossword coincides with the top-left corner of the rectangle. The same thing is correct for the right-bottom corners. The crossword can't degrade, i.e. it always has exactly four blank areas, two of which are surrounded by letters. Look into the output for the samples for clarification.

Help Vasya — compose a crossword of the described type using the given six words. It is allowed to use the words in any order.

## 样例 #1

### 输入

```
NOD
BAA
YARD
AIRWAY
NEWTON
BURN
```

### 输出

```
BAA...
U.I...
R.R...
NEWTON
..A..O
..YARD
```

## 样例 #2

### 输入

```
AAA
AAA
AAAAA
AAA
AAA
AAAAA
```

### 输出

```
AAA..
A.A..
AAAAA
..A.A
..AAA
```

## 样例 #3

### 输入

```
PTC
JYNYFDSGI
ZGPPC
IXEJNDOP
JJFS
SSXXQOFGJUZ
```

### 输出

```
JJFS....
Y..S....
N..X....
Y..X....
F..Q....
D..O....
S..F....
G..G....
IXEJNDOP
...U...T
...ZGPPC
```

# 题解

## 作者：_lxy_ (赞：4)

### 题意

有 $6$ 个字符串，让你把他们摆成一个8字形，使得交叉处相等，并且使得最后组合成的图形字典序最小。

### 分析

因为字符串的个数很小，所以可以枚举这 $6$ 个字符串的每一个排列。观察样例可以发现，一种排列是合法的当且仅当 $7$ 个交叉处的字符相同 $($ 详见代码 $)$ 。如果当前枚举到的排列合法，且它的字典序比之前的答案小，就把答案更新成这个排列的结果，最后输出结果即可。

### 代码
```cpp
#include <bits/stdc++.h>
#define elif else if
using namespace std;
const int MAXN=37;
vector<string>s;
vector<string>tmp,ans;
bool check(int l1,int l2,int l3,int l4,int l5,int l6)
{
    return l1+l3-1==l2
         &&l4+l6-1==l5
         &&s[1][0]==s[4][0] //左上角的交叉处
         &&s[4][l4-1]==s[2][0] //最左列，第二个交叉处
         &&s[5][l5-1]==s[3][0] //中间一列最后一个交叉处
         &&s[5][0]==s[1][l1-1] //第一行，第二个交叉处
         &&s[2][l1-1]==s[5][l4-1] //中心的交叉处
         &&s[6][0]==s[2][l2-1] //最右列，第一个交叉处
         &&s[6][l6-1]==s[3][l3-1]; //右下角的交叉处
} 
int main()
{
    int i,j;bool flag=false;
    s.resize(7);
    for(i=1;i<=6;i++) cin>>s[i];
    sort(s.begin()+1,s.begin()+7);
    do 
    { 
        //从上至下将横行编成1-3号，从左至右将竖列编成4-6号
        int l1=s[1].size(),l2=s[2].size(),l3=s[3].size(),l4=s[4].size(),l5=s[5].size(),l6=s[6].size();
        if(check(l1,l2,l3,l4,l5,l6))
        {
            tmp=vector<string>(l5,string(l2,'.')); //将整个结果初始化
            for(i=0;i<l5;i++)
            {
                if(!i)  for(j=0;j<l1;j++) tmp[i][j]=s[1][j]; //给第一行赋值
                if(i==l4-1) for(j=0;j<l2;j++) tmp[i][j]=s[2][j]; //给中间一行赋值
                if(i==l5-1) for(j=l1-1;j<l2;j++) tmp[i][j]=s[3][j-l1+1]; //给最后一行赋值
                tmp[i][l1-1]=s[5][i]; //给中间一列赋值
                if(i<l4) tmp[i][0]=s[4][i]; //给第一列赋值
                if(i>=l4) tmp[i][l2-1]=s[6][i-l4+1]; //给最后一列赋值
            }
            if(!flag) ans=tmp,flag=true;
            elif(ans>tmp) ans=tmp; //更新答案
        }
    }while(next_permutation(s.begin()+1,s.begin()+7));
    if(!flag) printf("Impossible\n"); //没有可行解
    else
    {
        for(i=0;i<ans.size();i++)
        {
            for(j=0;j<ans[i].size();j++) printf("%c",ans[i][j]);
            putchar(10);
        }
    }
    return 0;
}
```




---

## 作者：封禁用户 (赞：3)

## 题解：CF47C Crossword

### 题意简述

将 $6$ 个字符串摆成 $8$ 字型，让交叉处字符相同，输出字典序最小的结果。

### 解题思路

我们可以发现，无论如何拼，总会形成一个如下面的结构：

```txt
*1*..
2.3..
*4*4*
..3.5
..*6*
```

其中 `*` 表示交叉点，`1` 到 `6` 表示这 $6$ 个 字符串。

我们可以**枚举**所有可能的答案，最后选取**字典序最小**的输出。

我是使用了一个简单的 $6$ 层循环（在 `dfs` 函数中）枚举的所有情况，所有情况对应上面的 `1` 到 `6` 与输入的字符串的不同对应情况。

此时，我们可以筛出一些不符合条件的情况，为我们最后的字典序比较降低复杂度。

我整理了一下所有答案必须符合的条件：

- 边的条件：
    + 字符串 `1` 的长度 $+$ 字符串 `6` 的长度 $=$ 字符串 `4` 的长度 $+ 1$。
    + 字符串 `2` 的长度 $+$ 字符串 `5` 的长度 $=$ 字符串 `3` 的长度 $+ 1$。
 - 点的条件：
    + 字符串 `1` 的开头和字符串 `2` 的开头相等。
    + 字符串 `1` 的结尾和字符串 `3` 的开头相等。
    + 字符串 `2` 的结尾和字符串 `4` 的开头相等
    + 字符串 `3` 的结尾和字符串 `6` 的开头相等。
    + 字符串 `4` 的结尾和字符串 `5` 的开头相等。
    + 字符串 `5` 的结尾和字符串 `6` 的结尾相等。
    + 字符串 `3` 和字符串 `4` 中间的那个交点要相等（最难判断）。

这时符合条件的情况最多剩下 $4!\times2!=48$ 种，可以放心的暴力排字典序。

此时，若最长的字符串长度为 $n$，第二长的长度为 $m$，共有 $k$ 个字符串，则复杂度为：$O(k^k+nm)$。因为 $k = 6$ 且 $3 \le n , m \le 30$，所以不会超时。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
struct p
{
	int t , l;
	char s , e;
 
}c[10];
string a[10];
int b[10] , an = -1 , am = -1 , n , m;
bool flag[10];
char ans[35][35] , tmp[35][35];
bool cmp()
{
	if(an == -1 || am == -1)
	{
		return 1;
	}
	for(int i = 1 ; i <= max(n , an) ; i++)
	{
		for(int j = 1 ; j <= max(m , am) ; j++)
		{
			if(tmp[i][j] < ans[i][j])
			{
				return 1;
			}
			if(tmp[i][j] > ans[i][j])
			{
				return 0;
			}
		}
	}
	return 0;
}
void check()
{
	if(c[1].l + c[6].l != c[4].l + 1 || c[2].l + c[5].l != c[3].l + 1)
	{
		return;
	}
	if(c[1].s != c[2].s || c[1].e != c[3].s || c[2].e != c[4].s || a[c[3].t][c[2].l - 1] != a[c[4].t][c[1].l - 1] || c[4].e != c[5].s || c[3].e != c[6].s || c[5].e != c[6].e)
	{
		return;
	}
	n = c[3].l;
	m = c[4].l;
	memset(tmp , '!' , sizeof(tmp));
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			tmp[i][j] = '.';
		}
	}
	for(int i = 1 ; i <= c[1].l ; i++)
	{
		tmp[1][i] = a[c[1].t][i - 1];
	}
	for(int i = 1 ; i <= c[2].l ; i++)
	{
		tmp[i][1] = a[c[2].t][i - 1];
	}
	for(int i = 1 ; i <= c[3].l ; i++)
	{
		tmp[i][c[1].l] = a[c[3].t][i - 1];
	}
	for(int i = 1 ; i <= c[4].l ; i++)
	{
		tmp[c[2].l][i] = a[c[4].t][i - 1];
	}
	for(int i = 1 ; i <= c[5].l ; i++)
	{
		tmp[n - c[5].l + i][m] = a[c[5].t][i - 1];
	}
	for(int i = 1 ; i <= c[6].l ; i++)
	{
		tmp[n][m - c[6].l + i] = a[c[6].t][i - 1];
	}
	if(cmp())
	{
		for(int i = 1 ; i <= n ; i++)
		{
			for(int j = 1 ; j <= m ; j++)
			{
				ans[i][j] = tmp[i][j];
			}
		}
		an = n;
		am = m;
	}
	return;
}
void dfs(int deep)
{
	if(deep > 6)
	{
		check();
	}
	for(int i = 1 ; i <= 6 ; i++)
	{
		if(flag[i])
		{
			continue;
		}
		flag[i] = 1;
		c[deep].t = i;
		c[deep].l = b[i];
		c[deep].s = a[i][0];
		c[deep].e = a[i][b[i] - 1];
		dfs(deep + 1);
		flag[i] = 0;
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6];
	b[1] = a[1].size();
	b[2] = a[2].size();
	b[3] = a[3].size();
	b[4] = a[4].size();
	b[5] = a[5].size();
	b[6] = a[6].size();
	memset(ans , '!' , sizeof(ans));
	dfs(1);
	if(an == -1 || am == -1)
	{
		cout << "Impossible";
		return 0;
	}
	for(int i = 1 ; i <= an ; i++)
	{
		for(int j = 1 ; j <= am ; j++)
		{
			cout << ans[i][j]; 
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Confringo (赞：1)

### 题意简述
现在有 6 个字符串，让你把他们摆成一个 8 字形，使得交叉处相等。输出摆放后的位置。

（来自翻译）

---

### 思路
读题，发现题目中的数据范围：

- 六行包含给定的单词。每个单词由不超过 30 个且不少于 3 个大写拉丁字母组成。

我们发现单词数量只有 6，并且每个单词的长度不超过 30，所以考虑暴力求解。

&nbsp;

再次回顾题目，可以发现题目中还有这么一句话：

- 按照字典序输出最小的答案。

比较部分代码如下：
（minimum 数组为当前最小，res 为待比较数组，resn 为待比较数组长度，$minn$ 为当前最小数组长度，step 为当前比较的行序号，`maxstep=min(minn,resn)`）
```cpp
bool check3(int step,int maxstep,string res[110],int resn){
	if (step==maxstep+1) return resn<minn; //如果等到一个被比较完，另一个还有余，那么被比较完的更小。
	if (res[step]<minimum[step]) return true;//如果待比较数组的某一行小于当前最小，结束比较
	else if (res[step]>minimum[step]) return false;//和上一行同理
	else return check3(step+1,maxstep,res,resn);//如果两行相等，比较下一行
}
```

---

### 实现
至此，我们已经完成了主体部分构思。下面针对搜索部分给出实现。

```cpp
void dfs(int step,int state[7]){
	if (step==6){//六个字符串位置确定
		if (check2(state)){//满足八字要求
			flag=true;//标记找到答案
			int n=str[state[3]].size();
			int m=str[state[4]].size();
			char ch[110][110];
			string result[110];
			for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) ch[i][j]='.';//答案初始化
			for (int i=1;i<110;i++) result[i]="";//答案初始化
			for (int i=1;i<=str[state[1]].size();i++) ch[1][i]=str[state[1]][i-1];//本行和以下5行均为绘图
			for (int i=1;i<=str[state[2]].size();i++) ch[i][1]=str[state[2]][i-1];
			for (int i=1;i<=str[state[3]].size();i++) ch[i][str[state[1]].size()]=str[state[3]][i-1];
			for (int i=1;i<=str[state[4]].size();i++) ch[str[state[2]].size()][i]=str[state[4]][i-1];
			for (int i=str[state[2]].size();i<=n;i++) ch[i][m]=str[state[5]][i-str[state[2]].size()];
			for (int i=str[state[1]].size();i<=m;i++) ch[n][i]=str[state[6]][i-str[state[1]].size()];
			for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) result[i]+=ch[i][j];//将此答案存入string数组中
			if (check3(1,min(n,minn),result,n)){//求字典序最小的答案
				minn=n;
				for (int i=1;i<=n;i++) minimum[i]=result[i];
			}
		}
		return;
	}
	for (int i=1;i<=6;i++){//dfs基础
		if (check(state,i,step)){
			state[step+1]=i;
			dfs(step+1,state);
		}
	}
}
```

check 函数代码如下（判断在当前状态中某数是否已被取过）
```cpp
bool check(int state[7],int num,int cnt){
	for (int i=1;i<=cnt;i++){
		if (num==state[i]) return false;
	}
	return true;
}
```

check2 函数代码如下（判断八字是否合法）
```cpp
bool check2(int state[7]){
	if (str[state[2]].size()+str[state[5]].size()-1!=str[state[3]].size()) return false;//判断纵向长度是否正确
	if (str[state[1]].size()+str[state[6]].size()-1!=str[state[4]].size()) return false;//判断横向长度是否正确
	if (str[state[1]][0]!=str[state[2]][0]) return false;//本行和下方六行判断交点字母是否相同
	if (str[state[1]][str[state[1]].size()-1]!=str[state[3]][0]) return false;
	if (str[state[2]][str[state[2]].size()-1]!=str[state[4]][0]) return false;
	if (str[state[3]][str[state[3]].size()-1]!=str[state[6]][0]) return false;
	if (str[state[4]][str[state[4]].size()-1]!=str[state[5]][0]) return false;
	if (str[state[3]][str[state[2]].size()-1]!=str[state[4]][str[state[1]].size()-1]) return false;
	if (str[state[5]][str[state[5]].size()-1]!=str[state[6]][str[state[6]].size()-1]) return false;
	return true;//都满足返回 true
}
```

---

### 代码
至此，大部分实现都已结束，完整代码就不放了，大家可以通过 [我的CF记录入口](https://codeforces.com/contest/47/submission/165733120) 学习代码。

---

### 最后的最后
在这里，我想和大家分享一下我做这道题时遇到的一些坑。

[第 1 次提交](https://codeforces.com/contest/47/submission/165730712)：排序时 cmp 函数写错导致答案错误。

[第 2 次提交](https://codeforces.com/contest/47/submission/165730875)：判断交点代码少写一行并且没有 return 导致答案错误。

[第 3 次提交](https://codeforces.com/contest/47/submission/165731146)：输出时把 $m$ 写成 $n$ 并且没有 return 导致答案错误。

[第 4 次提交](https://codeforces.com/contest/47/submission/165731224)：初始化时把 $m$ 写成 $n$ 导致答案错误。

[第 5 次提交](https://codeforces.com/contest/47/submission/165731867)：写了两次 dfs，但是只保证了第一行字典序最小，导致答案错误。

[第 6 次提交](https://codeforces.com/contest/47/submission/165733034)：重构代码，但是把判断是否无解的代码放在了输出语句后，导致答案错误。

[第 7 次提交](https://codeforces.com/contest/47/submission/165733120)：Accepted。

---
感谢您能看到这里。

---

## 作者：CGDGAD (赞：1)

之前那篇题解解释得不是特别清楚，我来发个题解说一下。

### 题目大意

这道题意思一看样例就懂了。把六个字符串拼接成一个“8” 字形。

### 思路

随便选一个样例进行观察。这里选择样例3。

```plain
JJFS....
Y..S....
N..X....
Y..X....
F..Q....
D..O....
S..F....
G..G....
IXEJNDOP
...U...T
...ZGPPC
```

我们发现“8”字由 $6$ 个单词构成，分别是 $3$ 个横的， $3$ 个竖的。

观察一下这三个横的单词：

```plain
JJFS.... // 长度为4
........
IXEJNDOP // 长度为8
........
...ZGPPC // 长度为5
```

发现 $4 + 5 - 1 = 8$。

再观察竖着的三个单词：

```plain
J..S....
Y..S....
N..X....
Y..X....
F..Q....
D..O....
S..F....
G..G....
I..J...P
...U...T
...Z...C
// 长度分别为 9, 11, 3
```

发现 $3 + 9 - 1 = 11$。

这样规律就很明显了。

对于 $6$ 个长度分别为 $a, b, c, d, e, f$ 的字符串，只要满足 $a + b - 1 = c, d + e - 1 = f$ ，就可以构成一个 $8$ 字形。

这里生成这个满足要求的字符串排列时候使用 `algorithm` 里的 `next_permutation` 函数。

这个函数可以生成一个数组的全部排列，比如对于一个数组 `1 2 3 4`，不断调用它，可以使数组里的数变成 `1 2 4 3`, `1 3 2 4`, `1 3 4 2`, `1 4 2 3`, `1 4 3 2`, `2 1 3 4`, ...

每次生成一个排列的时候，判断它是否合法，如果合法就输出。这过程中有很多细节要注意。

最坑的是，这题不是SPJ，他要你输出**按字典序排序最小**的那个解。

因为加入了这个限制，就上STL吧。

### 代码（含注释）

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
using std::string; // 使用std::string解决本题
using std::cin;
using std::cout;
using std::endl;
string a[1001];
// 用STL更方便，因为自带比较大小、排序的功能
std::vector<string> best; // 目前最优的8字形方案（动态数组）
std::vector<string> res; // 当前计算出的8字形方案（动态数组）
int main() {
	for (int i = 1; i <= 6; i += 1) {
		cin >> a[i]; // 输入
	}
	std::sort(a + 1, a + 7); // 先（按字典序）排序
	do {
		// 如果满足 a + b - 1 = c 且 d + e - 1 = f
		if (a[1].length() + a[3].length() - 1 == a[2].length()
		 &&  a[4].length() + a[6].length() - 1 == a[5].length()) {
			// 判断单词的交点处是不是同一个字母，如果不是则退出（这部分的下标比较搞脑子，注意了）
			// a[m][a[m].length() - 1] 表示第m个字符串的最后一个字符
		 	if (a[1][0] != a[4][0]) continue;
		 	if (a[1][a[1].length() - 1] != a[5][0]) continue;
		 	if (a[4][a[4].length() - 1] != a[2][0]) continue;
		 	if (a[2][a[1].length() - 1] != a[5][a[4].length() - 1]) continue;
		 	if (a[2][a[2].length() - 1] != a[6][0]) continue;
		 	if (a[6][a[6].length() - 1] != a[3][a[3].length() - 1]) continue;
		 	if (a[5][a[5].length() - 1] != a[3][0]) continue;
		 	
			// 初始化res，初始化为全是 '.' 的
			// res数组下标从0开始
		 	res = std::vector<string>(a[5].size(), string(a[2].size(), '.'));
		 	
			// 画出第一个单词
		 	for (int i = 0; i < a[1].length(); i += 1)
		 		res[0][i] = a[1][i];
			// 画出第二个单词
		 	for (int i = 0; i < a[2].length(); i += 1)
		 		res[a[4].length() - 1][i] = a[2][i];
			// 画出第三个单词
		 	for (int i = 0; i < a[3].length(); i += 1)
		 		res[a[5].length() - 1][i + a[1].length() - 1] = a[3][i];
			// 画出第四个单词
		 	for (int i = 0; i < a[4].length(); i += 1)
		 		res[i][0] = a[4][i];
			// 画出第五个单词
		 	for (int i = 0; i < a[5].length(); i += 1)
		 		res[i][a[1].length() - 1] = a[5][i];
			// 画出第六个单词
		 	for (int i = 0; i < a[6].length(); i += 1)
		 		res[i + a[4].length() - 1][a[2].length() - 1] = a[6][i];
			// 更新best的值
		 	if (best.size() == 0 || res < best) {
		 		best = res;
		 	}
		 }
	} while (next_permutation(a + 1, a + 7)); // next_permutation，在“思路”这一部分讲过
	// 没有方案则Impossible
	if (best.size() == 0) printf("Impossible\n");
	else {
		// 输出每一行
		for (int i = 0; i < best.size(); i += 1) {
			std::cout << best[i] << endl;
		}
	}
	return 0;
}
```



---

## 作者：封禁用户 (赞：1)

本题就是一个大模拟，全排列可以通过next_permutation得到

下面是丑陋的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[6];
int l[6];
void draw (vector<string> &w, int i, int j, int di, int dj, string s) {
	for (int k = 0; k < s.size (); k++, i += di, j += dj)
	w[i][j] = s[k];
}
int main () {
	for (int i = 0; i < 6; i++) cin >> s[i];
	sort (s, s + 6);
	vector<string> res; res.clear ();
	do {
		if (s[0].size () + s[2].size () == s[1].size () + 1 && s[3].size () + s[5].size () == s[4].size () + 1) {
	for (int i = 0; i < 6; i++) l[i] = s[i].size () - 1;
	if (s[0][0] == s[3][0] && s[0][l[0]] == s[4][0] && s[1] [0] == s[3][l[3]] && s[1][l[0]] == s[4][l[3]] && s[1][l[1]] == s[5][0] && s[2][0] == s[4][l[4]] && s[2][l[2]] == s[5][l[5]]) {
	int n = l[1] + 1, m = l[4] + 1;
	vector<string> w (n, string (m, '.'));
	draw (w, 0, 0, 1, 0, s[0]);
	draw (w, 0, l[3], 1, 0, s[1]);
	draw (w, l[0], m - 1, 1, 0, s[2]);
	draw (w, 0, 0, 0, 1, s[3]);
	draw (w, l[0], 0, 0, 1, s[4]);
	draw (w, n - 1, l[3], 0, 1, s[5]);
	if (res.size () == 0 || res > w) res = w;}}
	} while (next_permutation (s, s + 6));
    //next_permutation必须用do...while格式！
	if (!res.size ()) cout << "Impossible" << endl; else
	for (int i = 0; i < res.size (); i++)
	cout << res[i] << endl;
	return 0;
}
```

---

