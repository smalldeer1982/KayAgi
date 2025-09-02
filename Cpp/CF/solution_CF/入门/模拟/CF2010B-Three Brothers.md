# Three Brothers

## 题目描述

### 题目翻译：

三兄弟相约见面。我们按以下顺序给他们编号：老大是 $1$ 号，老二是 $2$ 号，老三是 $3$ 号。

到了约定的时间，有一个兄弟迟到了。现在给出准时到达的两个兄弟的编号，你需要确定那个迟到的兄弟的编号。

## 样例 #1

### 输入

```
3 1```

### 输出

```
2```

# 题解

## 作者：lxyz (赞：3)

### 题目大意
题目意思非常简单，就是三兄弟出来玩谁没出来把他的编号输出出来就可以了。

---
### 思路
用数组把去了的兄弟的编号的下标用 $1$ 标记下来，最后看哪个兄弟的编号的下标是 $0$ 把那个兄弟的编号输出。

---
## code


```python
a, b = map(int, input().split())
c = [0] * 5
c[a] = 1
c[b] = 1
for i in range(1, 4):
    if c[i] == 0:
        print(i)

```

---

## 作者：Super_Cube (赞：1)

# Solution

三个人，编号为 $1,2,3$，编号总和为 $6$，设来的两个人编号为 $a,b$，那么没来的就是 $6-a-b$。

---

## 作者：xyx404 (赞：1)

## 题意：
三兄弟约定见面，大哥编号为 $1$，中弟编号为 $2$，小弟编号为 $3$。

到了开会时间，其中一个兄弟迟到了。

给出准时到达的两个兄弟的编号，你需要确定迟到的那个兄弟的编号。

## 思路：
输入的是两个准时到达的，那么没有在输入里出现的就是迟到的。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int a[4];
int main(){
	int x,y;cin>>x>>y;
	a[x]=a[y]=1;
	if(!a[1])cout<<1;
	else if(!a[2])cout<<2;
	else cout<<3;
	return 0;
}

```
[AC 记录](https://codeforces.com/contest/2010/submission/284768697)。

---

## 作者：wuyouawa (赞：1)

### 题目大意

三兄弟同意见面。让我们按以下方式对兄弟进行编号：年龄最大的兄弟是 $1$ 号，年龄第二大的兄弟是 $2$ 号，年龄最小的兄弟是 $3$ 号。到了聚会时间，其中一位兄弟迟到了。给定准时到达的两兄弟的号码，您需要确定迟到的兄弟的号码。

### 思路

签到题。

情况很少，一个个枚举即可。

### CODE


```cpp
#include<bits/stdc++.h>  
using namespace std; 
int a,b;
int main()  
{ 
    cin>>a>>b;
    if(a==1&&b==2||a==2&&b==1)  cout<<3;//前两种情况
    if(a==1&&b==3||a==3&&b==1)  cout<<2;//中间两种情况
    if(a==2&&b==3||a==3&&b==2)  cout<<1;//后两种情况
    return 0;
}  
```

---

## 作者：Mzh2012 (赞：1)

## 题目意思
一共有 $3$ 个兄弟要见面，大哥编号为 $1$，二弟编号为 $2$，小弟编号为 $3$。

给定其中两个人的编号，输出另一个人的编号。

## 思路
非常简单的一道语法题，输入两个数，判断是哪两个数，最后输出另外一个数即可。

但如果一个个的判断太麻烦了，所以我们可以优化一下程序。编号是固定的，所以他们三个人的编号和一定是 $1+2+3=6$，而又知道了其中两个，那另外一个绝对就是 $6$ 减去这两个数相加的和。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	cout<<6-a-b;	
	return 0;
}

```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/CF2010B)

输入是两个准时到的，所以没有在输入的就是迟到的。可以用 $1+2+3$ 的结果减掉 $a$ 和 $b$，就是答案。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int a,b;
	cin >>a>>b;
	cout<<6-a-b;
	return 0;
}
```

---

## 作者：furina_yyds (赞：0)

## 题意

有 $3$ 个兄弟，编号分别为 $1,2,3$，现在他们要开会，但是有一个迟到了，输入两个准时到的兄弟的编号，请你输出迟到的编号。

## 解法

这题的 $a$ 和 $b$ 均小于 $3$，数据非常小，那么就可以采用小数据杀手：打表。

表 $l_{i,j}$ 的数表示若 $i,j$ 准时到达，迟到的那个编号。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int l[4][4] = {
{0, 0, 0, 0},
{0, 0, 3, 2},
{0, 3, 0, 1},
{0, 2, 1, 0}
};
int main(){
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", l[a][b]);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2010B)

~~一道大 water 题。~~

### 题目大意
三兄弟约定见面，大哥编号为 $1$，二哥编号为 $2$，小弟编号为 $3$。

到了约定的时间，其中一个兄弟迟到了。

给出准时到达的两个兄弟的编号，你需要确定迟到的那个兄弟的编号。

### 解题思路
总共就 $3$ 种可能的情况，乱搞都能过。

由于 $3$ 个人的编号总和为 $6$，所以迟到的那个人的编号就是 $6-a-b$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main(){
	cin>>a>>b;
	cout<<6-a-b;
}
```

---

## 作者：Lfz312g (赞：0)

# CF2010B Three Brothers
## 题目分析
签到题。  
判断哪个兄弟没有到。只要用三兄弟数字的和减去 $a$ 和 $b$ 即可。

```cpp
#include <iostream>
using std::cin;
using std::cout;
void solve()
{
	int a,b;
	cin>>a>>b;
	cout<<6-a-b<<'\n';
}
int main()
{
    solve();
}
```

---

## 作者：Kratos_Charger (赞：0)

## CF2010B Three Brothers 题解

## 题目大意
大哥编号是 $1$，二哥编号是 $2$，三弟编号是 $3$。现在到了两人，求剩下的一人是谁？

## 思路
因为三兄弟的编号是固定的，所以只需要用三兄弟编号的和减去已经到的两人的编号即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
signed main(){
	cin>>x>>y;//输入到了的两兄弟
	cout<<6-x-y; 
	return 0;
} 
```

---

## 作者：mc_xiexie (赞：0)

### 题意

三兄弟出去玩，只来了两个，给定那两个的编号，问谁没来。

直接模拟：

```
#include<bits/stdc++.h>
using namespace std;
bool b[4];
int main(){
    int a,x;
    cin>>a>>x;
    b[a]=1;b[x]=1;
    if(!b[1]){
        cout<<1;
    }
    if(!b[2]){
        cout<<2;
    }
    if(!b[3]){
        cout<<3;
    }
    return 0;
}
```

用数字和减两人编号也行：

```
#include<bits/stdc++.h>
using namespace std;
bool b[4];
int main(){
    int a,b;
    cin>>a>>b;
    cout<<6-a-b;
    return 0;
}
```

还可以暴力枚举每种可能：

```
#include<bits/stdc++.h>
using namespace std;
bool b[4];
int main(){
    int a,b;
    cin>>a>>b;
    int c=a;
    a=max(a,b);
    b=min(c,b);
    if(a==2 && b==1){
        cout<<3;
    }
    else if(a==3 && b==1){
        cout<<2;
    }
    else if(a==3 && b==2){
        cout<<1;
    }
    return 0;
}
```

---

