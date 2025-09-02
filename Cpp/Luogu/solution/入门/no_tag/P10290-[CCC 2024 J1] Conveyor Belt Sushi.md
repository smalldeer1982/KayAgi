# [CCC 2024 J1] Conveyor Belt Sushi

## 题目描述

小镇里新开了一家传送带寿司店。一盘盘寿司在高高架起的传送带上旋转，顾客可以直接通过取走盘子来选择吃什么。

每一个红色盘子的寿司需要 $3$ 美元，每一个绿色盘子的寿司需要 $4$ 美元，每一个蓝色盘子的寿司需要 $5$ 美元。

![](https://cdn.luogu.com.cn/upload/image_hosting/yy1kg2a9.png)

你的任务是根据顾客选择的每种颜色的盘子数量，确定一顿饭的价钱。

## 说明/提示

**【样例 1 解释】**

这个顾客选择了 $0$ 个红色盘子，$2$ 个绿色盘子，$4$ 个蓝色盘子。所以这顿饭的价钱为 $0 \times 3 + 2 \times 4 + 4 \times 5 = 28$ 美元。

**【数据范围】**

对于所有数据，保证 $0\leq R,G,B\leq 500$。

## 样例 #1

### 输入

```
0
2
4
```

### 输出

```
28
```

# 题解

## 作者：zhuxiangrui_2010 (赞：4)

# P10290 [CCC 2024 J1] Conveyor Belt Sushi 题解
## 题意
每一个红色盘子的寿司需要 $3$ 美元，每一个绿色盘子的寿司需要 $4$ 美元，每一个蓝色盘子的寿司需要 $5$ 美元。输入每种颜色的盘子数量，确定一顿饭的价钱。
## 思路
用变量存储每个颜色的盘子数量，乘上相应的价格输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int R,G,B;
int main(){
    cin>>R>>G>>B;
    cout<<R*3+G*4+B*5;
	return 0;
}
```
~~求过。~~

---

## 作者：Turtle1208 (赞：3)

## 简单输出问题
$cnt1$ 代表红盘子的数量， $cnt2$ 表示绿盘子的数量,     $cnt3$ 表示蓝盘子的数量。

最后依题意写出输出即可。     
### 上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int cnt1, cnt2, cnt3; //计数器
    cin >> cnt1 >> cnt2 >> cnt3;
    cout << cnt1 * 3 + cnt2 * 4 + cnt3 * 5; //答案
    return 0;
}
```
## 谢谢观看

---

## 作者：Nostopathily (赞：3)

本题没什么好讲，输入盘数，计算方法为: $C = 3 × R + 4 × G + 5 × B$ 。

Code:

```cpp
#include<iostream>
#define int long long int
using namespace std;
int R,G,B;
signed main(){
    cin>>R>>G>>B;
    cout<<3*R+4*G+5*B;
    return 0;
}
```
谢谢观看，~~求赞&关注~~。

---

## 作者：nightwatch.ryan (赞：2)

### 思路
这道题很简单，输出 $R \times 3 + G \times 4 + B \times 5$ 就可以了。
### 代码
```cpp
#include<iostream>
int main(){
    int a,b,c;std::cin>>a>>b>>c;
    std::cout<<a*3+b*4+c*5;
}
```

---

## 作者：_ayaka_ (赞：1)

### 思路
用变量 $red$，$green$，$blue$ 来分别保存红色，绿色，蓝色盘子的数量。

随后，根据题意输出 $red \times 3 + green \times 4 + blue \times 5$ 的值，就可以解决了。

### 代码
```
#include<bits/stdc++.h>//此为通用头文件，集合了很多常用的头文件，所以大部分情况只用它作为头文件就够了
using namespace std;
int red,green,blue; //推荐定义全局变量，局部变量不仅初始值不一定为0，定义数组还不能过大
int main() {
	cin>>red>>green>>blue;//cin实现输入
	cout<<red*3+green*4+blue*5;//cout实现输出
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：1)

水题一道。

买红盘子寿司需要花费 $3\times R$ 美元，买绿盘子寿司需要花费 $4\times G$ 美元，买蓝盘子寿司需要花费 $5\times B$ 美元，加起来就是 $3\times R+4\times G+5\times B$ 美元。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int r,g,b;

signed main(){
  r=read();g=read();b=read();
  pr("%lld\n",r*3+g*4+b*5);
}
```

---

## 作者：J_Kobe (赞：0)

### 思路
输入完每种颜色的数量后，根据题目所说的将红色的乘上 $3$，绿色的乘上 $4$，蓝色的乘上 $5$，最后再把它们相加求总和即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie();cout.tie();
	int r, g, b;
	cin >> r >> g >> b;
	cout << r * 3 + g * 4 + b * 5;
	return 0;
}

```

---

## 作者：_O_v_O_ (赞：0)

直接按题目模拟即可。

因为每个红盘子 $3$ 元，所以红盘子的总金额为 $R\times 3$ 元。

同理，绿和蓝盘子金额分别为 $G\times 4$ 和 $B\times 5$。

所以最终答案为 $R\times 3+G\times 4+B\times 5$。

---

## 作者：LG086 (赞：0)

### 分析

简单的加减乘除运算。

输入三个非负整数 $R$ 表示红盘数，$G$ 表示绿盘数以及 $B$ 表示蓝盘数。  
每个红盘 $3$ 美元，每个绿盘要 $4$ 美元，每个蓝盘要 $5$ 美元。  
所以答案是 $R \times 3 + G \times 4 + B \times 5$。



------------
### 代码

```cpp
#include<iostream>
#define LG086 signed
LG086 main(){int a,b,c;std::cin>>a>>b>>c,std::cout<<(a*3+b*4+c*5);}
```

---

## 作者：gloomy_ (赞：0)

超级大水题。相乘再相加就行了。  
根据题意，红色一个三元，绿色一个四元，蓝色一个五元。计算的过程可以在输出中完成。  
在比赛中代码运行快慢也是很重要的因素，所以尽量多使用速度快的 scanf 和 printf。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
	scanf("%d%d%d",&a,&b,&c);
	printf("%d",3*a+4*b+5*c);
	return 0;
} 
```

---

## 作者：a1111a (赞：0)

# 思路
输入 $a$，$b$，$c$ 后输出 $a \times 3 + b \times 4 + c \times 5$ 即可
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c;
    cin>>a>>b>>c;
    cout<<a*3+b*4+c*5;
    return 0;
}
```

---

## 作者：ACtheQ (赞：0)

显而易见 $C = R \times 3 + G \times 4 + B \times 5$。

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int R,G,B;
	cin>>R>>G>>B;
	cout<<R*3+G*4+B*5;
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10291)

## 题意

每一个红色盘子的寿司需要 $3$ 美元，每一个绿色盘子的寿司需要 $4$ 美元，每一个蓝色盘子的寿司需要 $5$ 美元，输入三个数代表红色，绿色，蓝色盘子的数量，分别为 $r$ 和 $g$ 还有 $b$。

## 思路

输出 $3r+4g+5b$。

## [AC代码](https://www.luogu.com.cn/record/153150067)

```
#include<bits/stdc++.h>
using namespace std;
int r,g,b;
int main(){
	cin>>r>>g>>b;
	cout<<3*r+4*g+5*b;
}
```

~~话说为啥对了只有那么点分~~

---

## 作者：dongrunxuan (赞：0)

# P10290 题解
## 前言
最基础的问题了，让新手们同我这个蒟蒻一起，向大牛的路出发！
## 思路
按照题意模拟即可。红色的寿司 $3$ 元，故输入的 $R$ 值要乘以 $3$。绿色的寿司 $4$ 元，故输入的 $G$ 值要乘以 $4$。蓝色的寿司 $5$ 元，故输入的 $B$ 值要乘以 $5$。最后累加价格即可。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int r,g,b;
int main()
{
	cin>>r>>g>>b;
	cout<<r*3+g*4+b*5;
	return 0;
}
```

---

## 作者：xd244 (赞：0)

有什么说的呢？一道大水题！

读入三个数 $r$、$g$ 和 $b$，按照题意，计算 $3\times r+4\times g+5\times b$ 并输出。

代码：（真的不想放）
```cpp
#include<iostream>
using namespace std;
int main(){
    int r,g,b;cin>>r>>g>>b;
    cout<<3*r+4*g+5*b;
}
```

---

