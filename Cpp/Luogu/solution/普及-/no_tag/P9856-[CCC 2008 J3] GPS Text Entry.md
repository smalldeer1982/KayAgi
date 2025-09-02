# [CCC 2008 J3] GPS Text Entry

## 题目描述

在生日时，Sandy 收到了一个全球定位系统（GPS）设备，这是一种电子设备，她可以用来追踪本地的徒步旅行路线。途中，Sandy 可以标记航点，并在回家后将其记录在地图上。每个航点的描述可以输入到设备中，但设备没有键盘。相反，它有四个光标按钮：上、下、左、右，以及一个接受字母的按钮。键盘看起来如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/cqgjhd0p.png)

屏幕显示了可以用来“输入”描述的字母和符号的网格。网格布局如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/btdfon2b.png)

当你输入航点的名称时，光标从 `A` 开始。你必须将光标移动到下一个字母或符号的位置，然后接受该字母。光标只能水平或垂直移动到相邻的方格（不能对角线移动）。一旦你输入了描述中的所有字母，你需要将光标移动到 `enter` 并接受整个短语。

你需要编写一个程序来计算输入一个短语所需的光标移动次数。例如，要输入单词 `GPS`，从 `A` 位置开始，你需要向下移动 $1$ 次选择 `G`，然后向右移动 $3$ 次并向下移动 $1$ 次选择 `P`，然后向下移动 $1$ 次并向左移动 $3$ 次选择 `S`，最后向下移动 $1$ 次并向右移动 $5$ 次选择 `enter`。这总共需要 $15$ 次光标移动。注意，总的光标移动次数不会因为你选择先向下再向右或先向右再向下而改变。还要注意，你不能超出网格的边界（例如，你不能移出网格或“环绕”网格）。

## 说明/提示

数据保证合法。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
GPS```

### 输出

```
15```

## 样例 #2

### 输入

```
ECHO ROCK```

### 输出

```
29```

# 题解

## 作者：XingnoYi (赞：7)

**很明显的一道模拟题，需要注意的点如下：**

1. 打完字符串后需要按下 ```enter``` 键。

2. 字符串读入需要使用 ```getline()```，因为有输入有 ```space``` 键。

## Step 1：初始化键盘

这一步我是用两个 ```map``` 来存储字符的位置，根据题意写出构造代码。

```cpp
void keyboard()
{
    for(char i = 'A';i <= 'Z';i++)
    {
        x[i] = 1+(i-'A')/6; // x[] 表示在第几行。
        y[i] = (i-'A')%6+1; // y[] 表示在第几个。
    }
    x[' '] = x['-'] = x['.'] = 5;
    y[' '] = 3, y['-'] = 4, y['.'] = 5;
}
```
 注：`enter` 键因为不好表示没有计入数组，也不会多次使用。
## Step 2：计算距离

这里使用**直角距离**，也就是计算两点**横向距离**与**纵向距离**之和。

```cpp
// pntx 与 pnty 表示当前已打完字符的位置
int dis(int x,int y) // x 与 y 表示将要打的字符的位置
{
    return abs(x-pntx)+abs(y-pnty); // 注意绝对值
}
```

## Step 3：模拟操作

根据题意模拟即可。

```cpp
int main()
{
    keyboard(); // 初始化函数写完不要忘记调用！
    getline(cin,s); // 注意点2。
    for(int i = 0;i < s.length();i++)
    {
        ans += dis(x[s[i]],y[s[i]]); // 一个一个敲下字符。
        pntx = x[s[i]], pnty = y[s[i]]; // 更新当前位置。
    }
    ans += dis(5,6); // 注意点1。
    cout << ans;
    return 0;
}
```
**过程就是这么多，下面给一份完整代码。**

```cpp
#include <iostream>
#include <cmath>
#include <map>
#define big long long
using namespace std;
map <char,big> x,y;
big id=1,pntx=1,pnty=1,ans;
string s;
void keyboard()
{
    for(char i = 'A';i <= 'Z';i++)
    {
        x[i] = 1+(i-'A')/6;
        y[i] = (i-'A')%6+1;
    }
    x[' '] = x['-'] = x['.'] = 5;
    y[' '] = 3, y['-'] = 4, y['.'] = 5;
}
big dis(big x,big y)
{
    return abs(x-pntx)+abs(y-pnty);
}
int main()
{
    keyboard();
    getline(cin,s);
    for(big i = 0;i < s.length();i++)
    {
        ans += dis(x[s[i]],y[s[i]]);
        //printf("to %c: %lld\n",s[i],dis(x[s[i]],y[s[i]]));
        pntx = x[s[i]], pnty = y[s[i]];
        
    }
    ans += dis(5,6);
    cout << ans;
    return 0;
}
```

---

## 作者：noi2077 (赞：1)

用两个数组存下来每个字符对应的横坐标和纵坐标。然后遍历字符串，记下来当前的坐标，每次将答案加上这次要移动的距离，然后更新当前坐标。

`getline(cin,str)` 可以从 `cin` 中读入一行存到字符串 `str` 中。

```cpp
#include<iostream>
#include<vector>
using namespace std;
int x[1005], y[1005];
int main()
{
    for(int i = 'A'; i <= 'Z'; i++) x[i] = (i-'A')%6, y[i] = (i-'A')/6;
    x[' '] = 2; y[' '] = 4;
    x['-'] = 3; y['-'] = 4;
    x['.'] = 4; y['.'] = 4;
    x['\n'] = 5; y['\n'] = 4;
    string str;
    getline(cin, str);
    str += '\n';
    int cx = 0, cy = 0, ans = 0;
    for(auto c: str)
    {
        ans += abs(x[c]-cx)+abs(y[c]-cy);
        cx = x[c], cy = y[c];
    }
    cout << ans;
    return 0;
}
```

---

## 作者：IOI_AK_TLR (赞：1)

# 思路

简单题。建一个数组存每个字符所在位置，再写个函数计算两个字符所在位置的曼哈顿距离，剩下的就按照题意模拟累加求和即可。


------------


# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
pair<int,int>f[256];
string s;
int ans=0;
inline void init()
{
	for(int i='A';i<='F';i++)
		f[i]={1,i-'A'+1};
	for(int i='G';i<='L';i++)
		f[i]={2,i-'G'+1};
	for(int i='M';i<='R';i++)
		f[i]={3,i-'M'+1};
	for(int i='S';i<='X';i++)
		f[i]={4,i-'S'+1};
	f['Y']={5,1},f['Z']={5,2},f[' ']={5,3};
	f['-']={5,4},f['.']={5,5},f['\n']={5,6};
}
inline int dis(char x,char y)
{
	return abs(f[x].first-f[y].first)+abs(f[x].second-f[y].second);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	init();
	getline(cin,s);
	s='A'+s+'\n';
	for(int i=1;i<(int)s.size();i++)
		ans+=dis(s[i],s[i-1]);
	cout<<ans;
	return 0;
}


```


---

## 作者：UniGravity (赞：1)

## Solution P9856 [CCC 2008 J3] GPS Text Entry

### 题目分析
是一道简单的模拟题。

首先考虑每一次的移动代价，发现即为两字符间的**曼哈顿距离**（横纵坐标差的和）。

发现排列方式是有序的，我们从 $0$ 开始编号，可以发现：
```cpp
x = id % 6;
y = id / 6;
```

要注意从 `A` 开始，在 `enter` 处结束。

### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

string s;

signed main() {
    getline(cin, s);
    // 开始坐标为 `A`
    int lstx = 0, lsty = 0, x, y, id;
    int ans = 0;
    s += '\n'; // 结束为 `enter`
    for (int i = 0; i < s.length(); i++) {
        // 特判特殊字符
        if (s[i] == ' ') id = 26;
        else if (s[i] == '-') id = 27;
        else if (s[i] == '.') id = 28;
        else if (s[i] == '\n') id = 29;
        else id = s[i] - 'A';
        
        x = id % 6;
        y = id / 6;
        ans += abs(x - lstx) + abs(y - lsty);
        lstx = x;
        lsty = y;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：__O_v_O__ (赞：0)

首先，易知从一个字母的坐标到另一个字母的坐标，最短距离为曼哈顿距离。

于是我们枚举每个字符，同时记录上一个字符的坐标，让答案累加上当前字符和上个字符的曼哈顿距离。

那么，如何存储字符的坐标呢？我用的是两个一维数组，一个存 $x$ 坐标，一个存 $y$ 坐标，就可以了。

此外，这题还有几个坑点：

1. 输入字符串可能有空格。

2. 最后还需累加移到 $enter$ 键的距离。

3. 初始坐标为 $(1,1)$。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
string a;
int x[101]={1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5};//x坐标
int y[101]={1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6};//y坐标
int nx=1,ny=1,ans;//注意初始坐标为(1,1)
signed main(){
	ios::sync_with_stdio(0);
	getline(cin,a);//整行读入
	afor(i,0,a.size()-1,STB){
		int t=0;
		if(a[i]>='A'&&a[i]<='Z')t=a[i]-'A';
		else if(a[i]==' ')t=26;
		else if(a[i]=='-')t=27;
		else t=28;//处理字符
		ans+=(abs(x[t]-nx)+abs(y[t]-ny));//累加答案
		nx=x[t],ny=y[t];//更新当前位置
	}
	cout<<ans+abs(x[29]-nx)+abs(y[29]-ny);//加上enter
	return 0;
}
```

---

