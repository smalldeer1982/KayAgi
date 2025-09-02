# Headquarters

## 题目描述

Sensation, sensation in the two-dimensional kingdom! The police have caught a highly dangerous outlaw, member of the notorious "Pihters" gang. The law department states that the outlaw was driving from the gang's headquarters in his car when he crashed into an ice cream stall. The stall, the car, and the headquarters each occupies exactly one point on the two-dimensional kingdom.

The outlaw's car was equipped with a GPS transmitter. The transmitter showed that the car made exactly $ n $ movements on its way from the headquarters to the stall. A movement can move the car from point $ (x,y) $ to one of these four points: to point $ (x-1,y) $ which we will mark by letter "L", to point $ (x+1,y) $ — "R", to point $ (x,y-1) $ — "D", to point $ (x,y+1) $ — "U".

The GPS transmitter is very inaccurate and it doesn't preserve the exact sequence of the car's movements. Instead, it keeps records of the car's possible movements. Each record is a string of one of these types: "UL", "UR", "DL", "DR" or "ULDR". Each such string means that the car made a single movement corresponding to one of the characters of the string. For example, string "UL" means that the car moved either "U", or "L".

You've received the journal with the outlaw's possible movements from the headquarters to the stall. The journal records are given in a chronological order. Given that the ice-cream stall is located at point $ (0,0) $ , your task is to print the number of different points that can contain the gang headquarters (that is, the number of different possible locations of the car's origin).

## 说明/提示

The figure below shows the nine possible positions of the gang headquarters from the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183A/5eedd58060bd35a7ed9fa57f2be7f5f0bfad5425.png)For example, the following movements can get the car from point $ (1,0) $ to point $ (0,0) $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183A/a0545c148a057862574d8aad0a7d3d66cb719bc3.png)

## 样例 #1

### 输入

```
3
UR
UL
ULDR
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2
DR
DL
```

### 输出

```
4
```

# 题解

## 作者：sun_qy (赞：3)

# CF183A Headquarters 题解

[原题链接](https://www.luogu.com.cn/problem/CF183A)

## 题意提取

一个平面直角坐标系的第一象限（包括 x, y 两个正半轴）中的动点 $P(x, y)$ 有上下左右 `(U/D/L/R)` 四种移动方式，其从某固定点 $A$ 移动到坐标原点 $(0, 0)$ 经过了 $n$ 步，每步的可能情况由一个字符串 $s _ {i} $ 给出，其中不同的字母代表 P 在这一步可能的走法，例如 `UR` 代表 $P$ 在这一步可能向上走 `U`， 也可能向右走 `R`。给出 n 以及 $s _ {i}$ ，求 $A$ 的可能个数。

## 题目分析

前置知识： STL 库中的 `map` （若不会请阅读[这个](https://blog.csdn.net/nyist_zxp/article/details/119840727)）

由于 $s _ {i}$ 只有确定的 $5$ 种取值，我们可以开一个 `map <string, int> ` 来储存 $P$ 的每一步走法。

然后就是一个结论题，根据[乘法原理](https://oi-wiki.org/math/combinatorics/combination/#%E5%8A%A0%E6%B3%95--%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86)，所求点 $A$ 的个数可以记作：

```
(mov["UL"] + mov["ULDR"] + mov["DR"] + 1) * (mov["UR"] + mov["DL"] + mov["ULDR"] + 1)
```
为便于理解，可认为 `UL` 和 `DR` 在某种意义上是**等价**的， `UR` 和 `DL` 同理。 `ULDR` 则可以理解为两种情况都可以取到。

因此，可以将整个移动过程分为 **UL/DR** 和 **UR/DL** 两个**大步骤**，然后根据乘法原理计算即可。注意会爆 `int` ，要乘上 `1ll` 。

## 代码

```cpp
#include <bits/stdc++.h> //坏习惯 
using namespace std;
map <string, int> mov; //存储走法 
int n;
string s;
string getstr() { //读入字符串 
	string res;
	char ch = getchar();
	while(isspace(ch)) ch = getchar();
	while(!isspace(ch)) {
		res += ch;
		ch = getchar();
	}
	return res;
}
int main() {
	scanf("%lld", &n);
	for(int i = 1; i <= n; i ++) {
		s = getstr();
		mov[s] ++; //记录走法 
	}
	long long ans = 1ll * (mov["UL"] + mov["ULDR"] + mov["DR"] + 1) * (mov["UR"] + mov["DL"] + mov["ULDR"] + 1);
	printf("%lld\n", ans);
	return 0; //完结撒花 
}
```

---

## 作者：_int123_ (赞：3)

题目：

## Headquarters

### 题意：

警方要抓捕一名逃犯,逃犯开着车从总部驶出,撞上了一个冰淇淋摊,摊位、汽车和总部在二维平面上各占据一个点。

车在路上正好做了n次移动,每次按 $ \operatorname{L、R、D、U} $ 分别可以左、右、上、下移动一格

显示的移动不准确，它无法保存汽车运动的确切顺序。相反，它会记录汽车可能的运动。每个记录都是以下类型之一的字符串: $ \operatorname{UL、UR、DL、DR} $ 或者 $ \operatorname{ULDR} $ 每个这样的字符串意味着汽车做出了与字符串中的一个对应的移动。

你收到了逃犯可能的行动。记录是按时间顺序排列的,冰淇淋摊位于 $ (0,0) $ 你的任务是输出总部的不同点的数量

### 思路：

1. 假如我们要到一个点 $(x,y)$，显然只能从 $(x+1,y)$，$(x,y+1)$，$(x-1,y)$，$(x,y-1)$ 这 $4$ 个点来。

2. 根据[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447)，可以看出结果即为上面 $4$ 种可能的数量分别计数之后的乘积。

3. 不难得出公式。

### 公式解释：

公式为：

$ (a_{UL} + a_{DR} + a_{ULDR} + 1) \times (a_{UR} + a_{DL} + a_{ULDR} + 1) $

其中：

- $a_{UL}$ 表示移动中包含 $UL$ 的次数。
- $a_{DR}$ 表示移动中包含 $DR$ 的次数。
- $a_{ULDR}$ 表示移动中包含 $ULDR$ 的次数。
- 以此类推

该公式计算了总部可能的位置数量。让我们逐步解释一下：

1. 对于第一个因子 $(a_{UL} + a_{DR} + a_{ULDR} + 1)$：
   - $ a_{UL} $ 表示在 $UL$ 移动中选择的可能次数。
   - $ a_{DR} $ 表示在 $DR$ 移动中选择的可能次数。
   - $ a_{ULDR} $ 表示在 $ULDR$ 移动中选择的可能次数。
   - 最后的 $+1$ 表示在每一步都可以选择不移动。

2. 对于第二个因子 $(a_{UR} + a_{DL} + a_{ULDR} + 1)$：
   - $a_{UR}$ 表示在 $UR$ 移动中选择的可能次数。
   - $a_{DL}$ 表示在 $DL$ 移动中选择的可能次数。
   - $a_{ULDR}$ 表示在 $ULDR$ 移动中选择的可能次数。
   - 最后的 $+1$ 表示在每一步都可以选择不移动。

最终，将这两个因子相乘，得到总的可能总部位置数量。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
#define int long long//记得开 long long 
using namespace std;
map <string,int> a;//用 map 计数 
string s;
int n;
signed main()//因为 #define int long long 了，要用 signed 
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>n;//输入 
	for(int i=1;i<=n;i++) cin>>s,a[s]++;//输入字符串，用 map 记录个数 
	cout<<(a["UL"]+a["DR"]+a["ULDR"]+1)*(a["UR"]+a["DL"]+a["ULDR"]+1);//由公式，输出 
	return 0;
}
```

完结撒花！！！

---

## 作者：nightwatch.ryan (赞：1)

## 题意
一辆车移动了 $n$ 次，可以移动到上下左右四个方向一格，分别用 U，D，L，R 表示。现在告诉你小车的移动记录（只可能是 UL，UR，DL，DR，ULDR 中的一种）。请你按照它的移动方法判断最终的位置会有几种可能。
## 思路
分别求出所有方向的个数，求出来之后相乘 UL、DR、ULDR 和 UR、DL、ULDR 相乘。本题用 std::map 会方便很多。
#### 坑点
相乘时个数需要+1。相乘的时候会爆 `int`，所以还要乘一个 `1ll`。`1ll` 会在运算时把后面的临时数据扩容成 `long long` 类型。
```cpp
#include<iostream>
#include<map>
#include<string>
#define ll long long
int n;
std::map<std::string,int>mps;
std::string str;
int main(){
	std::cin>>n;
	for(int i=1;i<=n;i++){
		std::cin>>str;
		mps[str]++;
	}
	std::cout<<1ll*(mps["UL"]+mps["DR"]+mps["ULDR"]+1)*(mps["UR"]+mps["DL"]+mps["ULDR"]+1);
	return 0;
}
```

---

## 作者：CSPJ10pts (赞：1)

## 题意简述

一辆车可以移动到上下左右四个方向一格，分别用 U，D，L，R 表示。现在告诉你这辆小车的移动记录（是 UL，UR，DL，DR，ULDR 中的一种），请问按着它的移动方法，它可以到达哪几个不同地方。

## 分析

据题意，小车会有五种移动方法：左上，右上，左下，右下，不动。我们利用人类最宝贵的财富——大脑想一想。先在脑子里设想一张相邻两点之间距离为 $1$ 的网格图并在上面进行操作。首先把它四十五度旋转一下，这样我们的所有操作就变成直上直下了。然后我们给自己一组数据，在你的网格图里以一个点为中心的四个方向连四条线段，长度分别是左上右上左下右下的数量，对应着每个方向的极限，然后给这四条线段靠外的相邻两个端点之间连线，构造出一个正方形，被这个正方形包括的点就是可以走到的点，因为这个正方形之内，所有的点距离中心点的距离都可以通过不同方向的组合走到。题目就简化成了求这个正方形包括的点的数量。

怎么求？我们可以直接用求正方形面积的公式，带入这里便是：$($UL $+$ DR $+$ ULDR $ + 1) \times ($UR $+$ DL $+$ ULDR $ + 1)$。

更多详情见代码吧~

## 代码

```
#include <iostream>
#include <map> // map十分方便我们计数
using namespace std;
int n;
string s;
map<string, int> m;
int main() {
	cin >> n;
	while (n--) {
		cin >> s;
		m[s]++;
	}
	cout << 1ll * (m["UL"] + m["DR"] + m["ULDR"] + 1) * (m["UR"] + m["DL"] + m["ULDR"] + 1) << endl; // 求我们正方形的包括点的数量。注意！答案会爆int，所以一定要加1ll
	return 0;
}
```

[通过记录~](https://www.luogu.com.cn/record/102260855)

---

## 作者：哈士奇憨憨 (赞：1)

# [传送门](https://www.luogu.com.cn/problem/CF183A)
# 题意
一辆车在从一个点到 $（0，0）$ 移动了 $n$ 次。移动可以将汽车从点 $（x，y）$ 移动到这四个点之一：到点 $(x-1，y）-- L$ ，到点 $(x+1，y) -- R$，到点 $(x，y-1) -- D$ ，到点 $（x，y+1）-- U$ 。

每个记录都是以下类型之一的字符串：“$UL$”、“$UR$”、“$DL$”、“$DR$”或“$ULDR$”。每一个这样的字符串意味着汽车做出了与字符串中的一个字符对应的单个移动。例如，字符串“$UL$”表示汽车移动了“$U$”或“$L$”。
求汽车从来源到 $（0，0）$ 的不同可能位置的数量。
# 思路
求出 $UL、DR、ULDR、UR、DL$ 的个数，然后 $  UL、DR、ULDR$ 的个数和 $ULDR、UR、DL$ 的个数相乘。
## 坑点：
+ 相乘会爆`int`所以要开`long long`。
+ 相乘时记得个数要+1。
# CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  char s[10];
  int d1 = 1, d2 = 1;
  while (n--) {
    cin >> s;
    if (s[2] == 0) {
      if (s[0] == 'U') {
        if (s[1] == 'R') d1++;
	else d2++;
      } else {
        if (s[1] == 'R') d2++;
	else d1++;
      }
    } else {
      d1++;
      d2++;
    }
  }
  cout << d1 * (long long) d2 << endl;
  return 0;
}
```

---

## 作者：ggc123 (赞：0)

## 思路

假设冰淇凌摊原来的位置在 $\left ( x,y \right ) $，那么任意一次运动可能的位置在 $\left ( x-1,y-1 \right ) $、$\left ( x-1,y+1 \right ) $、$\left ( x,y \right ) $、$\left ( x+1,y-1 \right ) $、$\left ( x+1,y+1 \right ) $，如下图所示。

![](https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1725096185152/cjd.png)

所以，一共有 $6$ 种方法走到 $A\left ( x,y \right ) $：

1. 从 $B\left ( x-1,y-1 \right ) $ 选择 $UR$。
2. 从 $C\left ( x-1,y+1 \right ) $ 选择 $UL$。
3. 从 $D\left ( x+1,y-1 \right ) $ 选择 $DR$。
4. 从 $E\left ( x+1,y+1 \right ) $ 选择 $DL$。
5. 从 $A\left ( x,y \right ) $ 选择 $ULDR$。
6. 从 $A\left ( x,y \right ) $ 不进行选择。
   
所以我们就应当用 `map<string,int>` 存下来每一种走的类型的步数。

冰淇凌摊的移动路线如下图所示。

![](https://fs-im-kefu.7moor-fs1.com/ly/4d2c3f00-7d4c-11e5-af15-41bf63ae4ea0/1725097452912/CF183A_3.png)

因为第 $5$ 种方案和第 $6$ 种方案同时可以从直线 $f$ 和直线 $g$ 走到 $A\left ( x,y \right ) $，所以它们应同时计入到直线 $f$ 和直线 $g$ 之中。

所以从直线 $f$ 上走的方案数是 $cnt_{UL}+cnt_{DR}+cnt_{ULDR}+1$，从直线 $g$ 上走的方案数是 $cnt_{UR}+cnt_{DL}+cnt_{ULDR}+1$。因此最终的答案就是 $\left ( cnt_{UL}+cnt_{DR}+cnt_{ULDR}+1 \right ) \times \left ( cnt_{UR}+cnt_{DL}+cnt_{ULDR}+1 \right ) $。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s;
map<string, int> cnt;
signed main() {
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		cnt[s]++;
	}
	cout << (cnt["UR"] + cnt["DL"] + cnt["ULDR"] + 1)*(cnt["UL"] + cnt["DR"] + cnt["ULDR"] + 1);
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

车子移动了 $n$ 次，每次可以移动上下左右，分别用 $\text{U,D,L,R}$ 表示，车子的移动记录只可能是 $\text{UL,UR,DL,DR,ULDR}$ 中的一种。问最终的位置有多少种可能。

**解题思路**

令每种记录的个数为 $t_i$。

求出所有方向的个数，即 $(t_\text{UL}+t_\text{DR}+t_\text{ULDR}+1)\times(t_\text{UR}+t_\text{DL}+t_\text{ULDR}+1)$。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<string, int> mp;
string s;
int n;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  while(n--) {
    cin >> s;
    ++mp[s];
  }
  cout << (mp["UR"] + mp["DL"] + mp["ULDR"] + 1) * (mp["UL"] + mp["DR"] + mp["ULDR"] + 1);
  return 0;
}
```

---

## 作者：MsgNotFound (赞：0)

# 前置芝士
[乘法原理（必学）](https://baike.baidu.com/item/乘法原理/7538447)

这里来简单说一下 `map` 是什么。

学过编程的人都知道，我们是无法使用字符串作为数组的下标的。就想这样：`int a["cnt"]=1;` 是不行的，会报错。但是我们使用 `map` 就能完美使用，只需要这样：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int>mp;
int main(){
	mp["U"]=1;
	return 0;
}
```
就可以了，非常的方便。


# 题目大意
很简单的题目，可以使用 `map`。

记录 $\texttt{UR}$、$\texttt{DL}$、$\texttt{ULDR}$、$\texttt{UL}$、$\texttt{DR}$ 的个数，利用乘法原理求出总共的可能性，可以使用 `map` 存储，更加方便。
# 思路分析
首先将 $\texttt{UR}$、$\texttt{DL}$、$\texttt{ULDR}$、$\texttt{UL}$、$\texttt{DR}$ 情况的个数分别设为 $a \ b \ c \ d \ e$，并定义一个 `map` 数组，随后根据乘法原理可以推导出总共的情况数，计算的公式如下：

$$cnt=(mp_a+mp_b+mp_c+1)\times (mp_c+mp_d+mp_e+1)$$

# code
```cpp
//注意：数据量很大，需要开long long。
#include<bits/stdc++.h>
using namespace std;
#define int long long
sigend main(){
	int n;string str;
	map<string,int> a;//使用map进行存储更加方便。
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>str;
		a[str]++;
	}
    int ans=(a["UL"]+a["DR"]+a["ULDR"]+1)*(a["UR"]+a["DL"]+a["ULDR"]+1);// 体现出map好处：字符串下标。
	cout<<ans;
	return 0;
}
```

---

## 作者：_QyGyQ_ (赞：0)

## 思路
先分别记录 `DR`，`UL`，`ULDR` 的总个数和 `DL`，`UR`，`ULDR` 的总个数，根据乘法原理，总方案数就等于两个量相乘。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
signed main(){
	map<string,int>mp;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		mp[s]++;
	}
	int a=mp["DR"]+mp["UL"]+mp["ULDR"]+1;
	int b=mp["DL"]+mp["UR"]+mp["ULDR"]+1;
	cout<<a*b;
	return 0;
}

```


---

## 作者：luohaoyu1011 (赞：0)

# $\tt0x00$ 前言

……

# $\tt0x01$ 题意

一个点为了到 $(0,0)$ 开始做了 $n$ 次移动，每次移动可以向上下左右（$\text{U,D,L,R}$）四个方向，给出每次移动的字符串（$\text{UL,UR,DL,DR,ULDR}$ 之一），求出移动方案数。

# $\tt0x02$ 思路

前置芝士：[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447)

设 $\text{UL,UR,DL,DR,ULDR}$ 分别有 $p,q,x,y,z$ 个。

据此，我们可以得出式子 $\text{ans}=(a_p+a_y+a_z+1)\times(a_q+a_x+a_z+1)$。

# $\tt0x03$ 注意事项

- 可以用 `map` 存储，更方便
- 最后乘出来的结果可能很大，别忘了开 `long long`。

# $\tt0x04$ Code

一个公式而已，还用放吗？

---

## 作者：__CrossBow_EXE__ (赞：0)

又是一道简单的模拟题。
# 思路
众所周知，一个坐标可能是从相邻坐标过来的。有 4 种可能：

- $(x - 1,y) \longrightarrow (x,y)$
- $(x + 1,y) \longrightarrow (x,y)$
- $(x,y - 1) \longrightarrow (x,y)$
- $(x,y + 1) \longrightarrow (x,y)$

根据乘法原理，我们要求的结果即为上面 4 中可能的数量的积。

（[什么是乘法原理？](https://wenku.baidu.com/view/76d270680a12a21614791711cc7931b764ce7b5d.html?_wkts_=1694947284541&bdQuery=%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86)）

把上面的结果~~收拾收拾~~整理一下，就变成了：

$ ans = (a_{UL} + a_{DR} + a_{ULDR} + 1) \times (a_{UR} + a_{DL} + a_{ULDR} + 1) $

其中，$a_{UL}$ 代表字符串 “UL” 出现的次数，以此类推。
# 注意事项

- 看到刚刚公式中的相乘了吗？题面中 $n$ 的范围高达 $2 \times 10^5$，而相乘后则是 $(2 \times 10^5) \times (2 \times 10^5) = 4 \times 10^{10}$，所以不能用 int，只能用 long long。
- 一定不要忘记公式中括号里的加 1
- 使用 map，它让储存数据更方便。

# 代码
因为思路讲的很详细，所以不放代码了，能理解吧？

---

## 作者：Yousa_Ling (赞：0)

数学题。

分析题面可得，由于运动的方向只有四个，所以根据乘法原理，使用`map`计数，输出`(a["UL"]+a["DR"]+a["ULDR"]+1)*(a["UR"]+a["DL"]+a["ULDR"]+1)`即可。

注意事项：要开`long long`。

代码：
~~~c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	string s;
	map<string,long long> a;//使用map计数更加方便 
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		a[s]++;
	}
	cout<<(a["UL"]+a["DR"]+a["ULDR"]+1)*(a["UR"]+a["DL"]+a["ULDR"]+1)<<endl;
	return 0;
}
~~~

---

## 作者：zfw100 (赞：0)

# CF183A Headquarters 题解

[题目传送门](https://www.luogu.com.cn/problem/CF183A)

## 题目分析

因为一个点只能从上下左右四个地方过来，所以答案即为所有方向出现的次数之可能，所以答案即为 `UL`、`DR`、`ULDR` 的个数乘上 `UR`、`DL`、`ULDR` 的个数。

## 注意事项

- 开 `long long`。

- 相乘个数要加 $1$。

代码不放了。

---

## 作者：VitrelosTia (赞：0)

题链：[CF](https://codeforces.com/contest/183/problem/A)/[Luogu](https://www.luogu.com.cn/problem/CF183A)

### 题意
一辆车移动了 $n$ 次，每次只移动到上下左右四个方向一格，分别用 U,D,L,R 表示。现在每次移动告诉你一个日志，只可能是 UL,UR,DL,DR 或 ULDR，表示移动的方向可能是日志中的一个字符。请你判断的最终位置有多少种可能。

### 思路
结论题。一个点只能从四周而来，所以答案应该是所有方向的出现次数的可能，需要分别计数之后相乘。于是由乘法原理容易得知答案是: 

(UL $+$ DR $+$ ULDR $+$ $1$ ) $\times$ (UR $+$ DL $+$ ULDR $+$ $1$ )

可以在输入时直接用 `map` 计数，不需要各种判断，十分简便。

特别的，在做乘法运算时，会爆`int`，需要乘上 `1ll`。

### code
```
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
map<string,int> mp;
int main() {
    cin>>n;
    for(int i=1;i<=n;i++){ cin>>s;mp[s]++; }
    cout<<(mp["UL"]+mp["DR"]+mp["ULDR"]+1)*1ll*(mp["UR"]+mp["DL"]+mp["ULDR"]+1);
    return 0;
}
```


---

