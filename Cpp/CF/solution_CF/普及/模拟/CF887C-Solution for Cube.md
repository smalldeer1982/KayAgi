# Solution for Cube

## 题目描述

During the breaks between competitions, top-model Izabella tries to develop herself and not to be bored. For example, now she tries to solve Rubik's cube 2x2x2.

It's too hard to learn to solve Rubik's cube instantly, so she learns to understand if it's possible to solve the cube in some state using 90-degrees rotation of one face of the cube in any direction.

To check her answers she wants to use a program which will for some state of cube tell if it's possible to solve it using one rotation, described above.

Cube is called solved if for each face of cube all squares on it has the same color.

<a>https://en.wikipedia.org/wiki/Rubik's\_Cube</a>

## 说明/提示

In first test case cube looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF887C/73004469d714c2206d92e2fac016d4fc092e2426.png)In second test case cube looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF887C/37b512d2c715516faa04a8cfe0023b26918d7893.png)It's possible to solve cube by rotating face with squares with numbers 13, 14, 15, 16.

## 样例 #1

### 输入

```
2 5 4 6 1 3 6 2 5 5 1 2 3 5 3 1 1 2 4 6 6 4 3 4
```

### 输出

```
NO```

## 样例 #2

### 输入

```
5 3 5 3 2 5 2 5 6 2 6 2 4 4 4 4 1 1 1 1 6 3 6 3
```

### 输出

```
YES```

# 题解

## 作者：流绪 (赞：4)

一开始我用二维数组存,写得人都懵了,改成一维数组,感觉世界都清晰多了...

因为只能转一次,那么必定是两个面是好的,然后剩下四个面有两种转的情况,本来是有四种,但是有两个面固定,所以有两种不可以

所以,一共有 2*3 种情况,枚举就好啦,注意边的对应情况

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double 
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int ch[100];
bool check(int a,int b,int c,int d)
{
	if(ch[a]==ch[b]&&ch[a]==ch[c]&&ch[a]==ch[d])
		return 1;
	return 0;
}//判断是不是颜色相同
int main()
{
	for(int i=1;i<=24;i++)
		cin >> ch[i];
	int flag = 0;//记录能不能转
	if(check(13,14,15,16)&&check(17,18,19,20)&&check(2,4,22,24)&&check(1,3,6,8)&&check(5,7,10,12))
		flag = 1;
	if(check(13,14,15,16)&&check(17,18,19,20)&&check(2,4,5,7)&&check(6,8,9,11)&&check(10,12,22,24))
		flag = 1;
		
		
	if(check(1,2,3,4)&&check(9,10,11,12)&&check(5,6,15,16)&&check(17,18,7,8)&&check(21,22,19,20))
		flag = 1;
	if(check(1,2,3,4)&&check(9,10,11,12)&&check(7,8,13,14)&&check(19,20,5,6)&&check(23,24,17,18))
		flag = 1;
		
		
	if(check(5,6,7,8)&&check(21,22,23,24)&&check(1,2,17,19)&&check(13,15,3,4)&&check(11,12,14,16))
		flag = 1;
	if(check(5,6,7,8)&&check(21,22,23,24)&&check(3,4,18,20)&&check(14,16,1,2)&&check(9,10,13,15))
		flag = 1;
	if(flag) 
		cout <<"YES";	
	else 	
	 	cout <<"NO"; 
	return 0;
}
```


---

## 作者：boluo2014 (赞：1)

好抽象的一道题目！大型模拟题。

### 思路

首先，不是 $3\times 3 \times 3$ 的魔方，我放下心了。存储颜色和判断需要提前写好，你可以直接按照题目输入的存储，然后判断每个面也都很简单。

问题就在于模拟。模拟一定要仔细！有很多种方法，但是你只要分步骤，按照面进行模拟即可。面一共有 $6$ 个，正面、左面、右面、后面、下面、上面。每一个面又分为好几种情况，我们假设它初始都是一个 $2 \times 2$ 的方格，也就是永远正着看，这里画了个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/obj9k2ga.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样，分别的做法是：

将 $1,3$ 号向前滚动，将 $1,3$ 号向后滚动。

将 $2,4$ 号向前滚动，将 $2,4$ 号向后滚动。

将 $1,2$ 号向左滚动，将 $1,2$ 号向右滚动。

将 $3,4$ 号向左滚动，将 $3,4$ 号向右滚动。

你会了吗？

---

## 作者：OIerZhang (赞：0)

# [CF887C Solution for Cube](https://www.luogu.com.cn/problem/CF887C)

一道大水题，可惜代码有点过长。

## 思路

这道题乍一看很难，但仔细观察，发现只转一次就够了，那么一道毒瘤题就变成水题啦。

我们可以枚举 $6$ 个方向的旋转，将原来的方块复制到新的位置，判断每个面的颜色是否相同。

注意是 $6$ 个方向，因为可以从 $x,y,z$ 三个维度旋转，这个魔方又有 $2$ 层，所以就是 $6$ 个方向。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[30], t[30];

bool check()
{
    int c = 0;
    if (t[1] == t[2] && t[2] == t[3] && t[3] == t[4])
        c++;
    if (t[5] == t[6] && t[6] == t[7] && t[7] == t[8])
        c++;
    if (t[9] == t[10] && t[10] == t[11] && t[11] == t[12])
        c++;
    if (t[13] == t[14] && t[14] == t[15] && t[15] == t[16])
        c++;
    if (t[17] == t[18] && t[18] == t[19] && t[19] == t[20])
        c++;
    if (t[21] == t[22] && t[22] == t[23] && t[23] == t[24])
        c++;
    return c == 6;
}

void yes()
{
    cout << "YES";
}

void no()
{
    cout << "NO";
}

signed main()
{
    for (int i = 1; i <= 24; i++)
        cin >> a[i];
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= 24; i++)
        t[i] = a[i];
    t[5] = a[1], t[7] = a[3], t[9] = a[5], t[11] = a[7];
    t[24] = a[9], t[22] = a[11], t[1] = a[24], t[3] = a[22];
    if (check())
    {
        yes();
        return 0;
    }
    
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= 24; i++)
        t[i] = a[i];
    t[6] = a[2], t[8] = a[4], t[10] = a[6], t[12] = a[8];
    t[23] = a[10], t[21] = a[12], t[2] = a[23], t[4] = a[21];
    if (check())
    {
        yes();
        return 0;
    }
    
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= 24; i++)
        t[i] = a[i];
    t[5] = a[13], t[6] = a[14], t[17] = a[5], t[18] = a[6];
    t[21] = a[17], t[22] = a[18], t[13] = a[21], t[14] = a[22];
    if (check())
    {
        yes();
        return 0;
    }
    
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= 24; i++)
        t[i] = a[i];
    t[7] = a[15], t[8] = a[16], t[19] = a[7], t[20] = a[8];
    t[23] = a[19], t[24] = a[20], t[15] = a[23], t[16] = a[24];
    if (check())
    {
        yes();
        return 0;
    }
    
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= 24; i++)
        t[i] = a[i];
    t[18] = a[1], t[20] = a[2], t[12] = a[18], t[11] = a[20];
    t[15] = a[12], t[13] = a[11], t[1] = a[15], t[2] = a[13];
    if (check())
    {
        yes();
        return 0;
    }
    
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= 24; i++)
        t[i] = a[i];
    t[17] = a[3], t[19] = a[4], t[10] = a[17], t[9] = a[19];
    t[16] = a[10], t[14] = a[9], t[3] = a[16], t[4] = a[14];
    if (check())
    {
        yes();
        return 0;
    }
    no();
    return 0;
}
```

珍爱账号，远离抄袭。

---

## 作者：kimi0705 (赞：0)

题解：

其实题目比较简单。

1. 易得如果只能转一次，有两个相对的面一定是拼好的。
1. 然后枚举
     1. 下面一层逆时针
     1. 下面一层顺时针
     1. 上面一层逆时针
     1. 上面一层顺时针
     
tips : 可以写 $3$ 个 if 分开写比较方便。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int ch[100];
bool check(int a, int b, int c, int d) { // 检查a == b == c == d
	if (ch[a] == ch[b] && ch[a] == ch[c] && ch[a] == ch[d])
		return 1;
	return 0;
}
int main() {
	for (int i = 1; i <= 24; i++) // 输入
		cin >> ch[i];
        // 枚举情况
	if (check(13, 14, 15, 16)		&& check(17, 18, 19, 20) 	&& check(2, 4, 22, 24) 	&& check(1, 3, 6, 8) 	&& check(5, 7, 10, 12))
		cout << "YES\n";
	else if (check(13, 14, 15, 16)	&& check(17, 18, 19, 20)	&& check(2, 4, 5, 7) 	&& check(6, 8, 9, 11) 	&& check(10, 12, 22, 24))
		cout << "YES\n";
	else if (check(1, 2, 3, 4) 		&& check(9, 10, 11, 12) 	&& check(5, 6, 15, 16) 	&& check(17, 18, 7, 8) 	&& check(21, 22, 19, 20))
		cout << "YES\n";
	else if (check(1, 2, 3, 4) 		&& check(9, 10, 11, 12) 	&& check(7, 8, 13, 14) 	&& check(19, 20, 5, 6) 	&& check(23, 24, 17, 18))
		cout << "YES\n";
	else if (check(5, 6, 7, 8) 		&& check(21, 22, 23, 24) 	&& check(1, 2, 17, 19) 	&& check(13, 15, 3, 4) 	&& check(11, 12, 14, 16))
		cout << "YES\n";
	else if (check(5, 6, 7, 8) 		&& check(21, 22, 23, 24) 	&& check(3, 4, 18, 20) 	&& check(14, 16, 1, 2) 	&& check(9, 10, 13, 15))
		cout << "YES\n";
	else 
		cout << "NO\n";
	return 0;
}
```

---

## 作者：过氧化氢_syq0057 (赞：0)

是个好题，但是有点麻烦 /ll

### solution

分别判断对应面 $(1,3),(2,6),(4,5)$ 是不是已经拼好了，然后判断剩下四个面能不能一步到位就行了。

但是有坑点 qwq

坑点 $1$：

题面上要求转动一次，所以已经拼好的魔方不行，输出 ```NO```。

坑点 $2$：

有两面互相反着，是不行的。

数据 ```1 1 1 1 2 2 3 3 6 6 6 6 5 5 4 4 3 3 2 2 4 4 5 5```。

坑点 $3$：

对应可以拼的隔了一个面，也是不行的。

数据 ```5 5 5 5 1 1 2 2 6 6 6 6 4 4 3 3 3 3 4 4 2 2 1 1```。

其实如果直接判横（竖）向上（下）转一次能不能成更简单，只是刚开始我觉得我这种写法更简单，但写到最后反而需要特判，更难写了 /ll/wl。

### code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 10;
const int M = 10;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int cube[N][M];
bool check(int a, int b) {
	if (cube[a][1] != cube[a][2] || cube[a][2] != cube[a][3] || cube[a][3] != cube[a][4])
		return 0;
	if (cube[b][1] != cube[b][2] || cube[b][2] != cube[b][3] || cube[b][3] != cube[b][4])
		return 0;
	return 1;
}
bool isok1() {//1,3
	if (cube[4][3] != cube[4][4] || cube[2][3] != cube[2][4] || cube[5][3] != cube[5][4] ||
	cube[6][3] != cube[6][4]) return 0;
	if (cube[4][3] == cube[2][3] || cube[2][3] == cube[5][3] || cube[5][3] == cube[6][3] || 
	cube[6][3] == cube[4][3]) return 0;
	if (cube[2][1] == cube[5][3] && cube[2][3] == cube[5][1]) return 0;//特判2 
	if (cube[4][3] == cube[5][1] && cube[2][1] == cube[6][3]) return 0;//特判3 
	return 1;
}
bool isok2() {//2,6
	if (cube[1][1] != cube[1][2] || cube[3][3] != cube[3][4] || cube[4][1] != cube[4][3] ||
	cube[5][2] != cube[5][4]) return 0;
	if (cube[1][1] == cube[4][1] || cube[4][1] == cube[3][3] || cube[3][3] == cube[5][4] || 
	cube[5][4] == cube[1][1]) return 0;
	if (cube[1][1] == cube[4][2] && cube[1][3] == cube[4][1]) return 0;//特判2 
	if (cube[1][1] == cube[3][1] && cube[4][1] == cube[5][1]) return 0;//特判3 
	return 1;
}
bool isok3() {//4,5
	if (cube[1][1] != cube[1][3] || cube[2][1] != cube[2][3] || cube[3][1] != cube[3][3] ||
	cube[6][1] != cube[6][3]) return 0;
	if (cube[1][1] == cube[2][1] || cube[2][1] == cube[3][1] || cube[3][1] == cube[6][2] || 
	cube[6][2] == cube[1][1]) return 0;
	if (cube[1][1] == cube[2][2] && cube[1][2] == cube[2][1]) return 0;//特判2 
	if (cube[1][1] == cube[3][2] && cube[2][1] == cube[6][3]) return 0;//特判3 
	return 1;
}
int main() {
	for (int i=1; i<=6; i++)
		for (int j=1; j<=4; j++)
			scanf("%d", &cube[i][j]);
	if (!check(1, 3) && !check(2, 6) && !check(4, 5)) {
		puts("NO");
		return 0;
	}
	if (check(1, 3) && check(2, 6) && check(4, 5)) {
		puts("NO");
		return 0;
	}//特判1
	if (check(1, 3)) {
		if (isok1()) puts("YES");
		else puts("NO");
	}
	else if (check(2, 6)) {
		if (isok2()) puts("YES");
		else puts("NO");
	}
	else if (check(4, 5)) {
		if (isok3()) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

完结散花 qaq

---

