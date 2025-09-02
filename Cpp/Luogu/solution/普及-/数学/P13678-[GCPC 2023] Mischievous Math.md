# [GCPC 2023] Mischievous Math

## 题目描述

Max 喜欢玩数字游戏，无论是寻找能够得到给定结果的组合，还是发现某些给定整数的所有可能结果。不过，Max 只有 10 岁，数学知识有限，这限制了这些游戏的可能性。幸运的是，在今天的数学课上，Max 学习了括号的概念以及它们对计算的影响。他意识到，在数字游戏中加入括号会让游戏变得更加有趣。

放学回家后，他让姐姐 Nina 和他一起玩一个使用括号的最喜欢的数字游戏的变体。

![](https://cdn.luogu.com.cn/upload/image_hosting/obfj7x59.png)

:::align{center}
Max 正在尝试解决第三个样例。
:::

在这个新游戏中，Max 首先告诉 Nina 一个数字 $d$。然后，Nina 告诉他三个数字 $a$、$b$ 和 $c$。现在，Max 需要用加法、减法、乘法和除法，使用这三个数字（$a$、$b$、$c$，每个最多用一次）构造一个算术表达式，使得结果等于 $d$。数字 $a$、$b$、$c$ 和 $d$ 必须两两不同，并且 Max 也可以使用括号。

例如，当 $a = 5$，$b = 8$，$c = 17$，$d = 96$ 时，一个可能的解是 $(17 - 5) \times 8 = 96$；当 $a = 3$，$b = 7$，$c = 84$，$d = 12$ 时，一个可能的解是 $84 \div 7 = 12$，此时没有用到 $3$。

Nina 很快就对这个游戏感到厌烦。她更想和朋友们一起度过下午，而不是陪弟弟玩游戏。因此，她想给 Max 出一个能让他尽可能长时间都解不开的题目。请你帮她找到三个数字 $a$、$b$ 和 $c$，使得 Max 无法给出任何一个算式使结果等于 $d$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5```

### 输出

```
1 20 30```

## 样例 #2

### 输入

```
100```

### 输出

```
33 55 77```

## 样例 #3

### 输入

```
3```

### 输出

```
11 9 4```

# 题解

## 作者：jinshixian (赞：3)

这是本蒟蒻的第二篇题解，求审核大大通过。
## 题目大意
我们需要找到三个数 $a$，$b$，$c$，使得无法通过对它们进行加、减、乘、除运算（可使用括号，每个数最多用一次）得到 $d$，且这三个数与 $d$ 两两不同。
## 思路
我的思路很直接简单，直接通过三层循环暴力枚举 $a$，$b$，$c$。具体判断流程如下：

- 三个数本身都不等于 $d$。
- 任意两数的和、差、积、商不等于 $d$。
- 三数的和、以及各种组合的加减运算结果不等于 $d$。
- 包含乘法与加减法组合的运算结果不等于 $d$。
- 包含除法与加减法组合的运算结果不等于 $d$。
- 包含括号的复杂组合运算结果不等于 $d$。
- 三数乘积以及连除结果不等于 $d$。

为了层次分明，可能 $\texttt {if}$ 嵌套有些多，显得代码很杂乱，如果有大佬有更好的方法，欢迎来指导一下。
## 代码
```cpp
#include <bits/stdc++.h>//万能头文件 

using namespace std;

int d;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> d;//输入d 
	for (double i = 1; i <= 100; i++)
	    for (double j = i + 1; j <= 100; j++)
	        for (double k = j + 1; k <= 100; k++)//三层循环枚举a，b，c 
	            if (i != d && j != d && k != d)
	                if (i + j != d && j + k != d && i + k != d)
	                    if (j - i != d && k - i != d && k - j != d)
	                        if (i * j != d && j * k != d && i * k != d)
	                            if (j / i != d && k / j != d && k / i != d)
	                                if (i + j + k != d && i + j - k != d && i + k - j != d && k + j - i != d && k - j - i != d)
	                                    if (i * j + k != d && j * k + i != d && i * k + j != d && i * j - k != d && j * k - i != d && i * k - j != d && k - i * j != d)
	                                        if (j / i + k != d && k / j + i != d && k / i + j != d && k / j - i != d && k / i - j != d && i - k / j != d && j - k / i != d && k - j / i != d)
	                                            if ((i + j) * k != d && (j + k) * i != d && (i + k) * j != d && (i + j) / k != d && (j + k) / i != d && (i + k) / j != d && (j - i) * k != d && (k - i) * j != d && (k - j) * i != d && (k - i) / j != d && (k - j) / i != d)
	                                                if (k / (i + j) != d && k / (j - i) != d && j / (k - i) != d && i / (k - j) != d)    
														if (i * j * k != d && k / j / i != d){//一大堆判断。。 
														    cout << i << " " << j << " " << k << endl;//输出 
														    return 0;//结束程序 
													    }
}
```
点个赞再走吧。

---

## 作者：yuhaotian000 (赞：2)

# 题解：P13678 [GCPC 2023] Mischievous Math

## 题目大意

给出一个不超过 $100$ 的正整数 $d$，现在需要构造三个数 $a,b,c$，使得无法选择其中的一些数（注意，一个数不能用多次，但是可以不用）用加法、减法、乘法、除法以及括号计算出来 $d$。

## 题目解法

这是一个构造题，我们肯定要找到一些通用的解法来找到所有答案的解。那么我们先来构造一个尽量小的 $a,b,c$，明显，最小的就是 $a=1,b=2,c=3$。这三个数最大可以算出来的数是 $9$，所以只要 $d$ 在 $9$ 以上就可以用这个作为答案。那么，现在我们需要找到 $d \le 9$ 的通用解法。观察样例，我们可以稍微改一下第一个样例的输出，可以改为 $a=1,b=20,c=50$，来解决 $2 \le d \le 9$ 的时候的问题。那么当 $d=1$，我们只需要找到一个简单的解就行了，我这里选用了 $a=33,b=78,c=91$。

## AC code

```
#include <bits/stdc++.h>
using namespace std;
int main(){
    int d;
    cin>>d;
    if(d>9){
        cout<<"1 2 3";
    }else if(d==1){
        cout<<"33 78 91";
    }else{
        cout<<"1 20 50";
    }
}
```

---

## 作者：Ultra_Robin (赞：2)

# [题解：P13678 [GCPC 2023] Mischievous Math](https://www.luogu.com.cn/problem/P13678)

## 分析题目：

就是有一个数 $d$，现在需要给出三个数 $a$，$b$，$c$。
你可以对这三个数进行任何运算（数字可以不用）使结果为 $d$。但现在要给出的这三个数无论如何也不能凑成 $d$。

## 解题思路：

分类讨论，如果 $d > 9$，那就直接输出 $1$，$2$，$3$，因为这三个数最大才能凑成 $9$。

那如果 $d \le 9$，并且 $d > 2$，那就输出 $98$，$99$，$100$，这三个数不可能凑出这种情况下的 $d$。

最后 $1$ 和 $2$。则输出 $4$，$7$，$55$，同理不可能凑出这种情况下的 $d$。

奉上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int d;
    cin >> d;
    if (d > 9) {
		cout << "1 2 3" << endl;
	}else if (d > 2){
		cout << "98 99 100" << endl;
	}else {
		cout << "4 7 55" << endl;
	}
    return 0;
}
```

谢谢观看，求过求赞。

---

## 作者：x_Toi_QiQi (赞：1)

## 题目翻译:
一个数字游戏，游戏规则：
1. 马克思给粗目标数字 $d$（$1 \leq 100$）。
2. 姐姐给出三个不同的数字 $a,b,c$（$1 \leq a,b,c \leq 100$，且和 $d$ 不同）。
3. 马克斯要用 $a,b,c$（每一个最多用一次）通过加减乘除得到 $d$。

请找出一组 $a,b,c$，使得永远无法通过加减乘除得到 $d$。
## 解题思路：
这是一道数学题，我们只需要考虑到所有的情况就可以了。

当我们将 $a,b,c$ 分别设为 $1,2,3$ 时，除了 $d < 10$ 的情况，其余 $d \geq 10$ 的情况让 $a,b,c$ 为 $1,2,3$ 是没有问题的。所以我们还要解决 $d < 10$ 的情况，经过打表（~~其实是写枚举~~）发现，可以满足的有 $d < 10$ 的可以让 $a,b,c$ 分别为 $31,53,74$，这样我们就讨论完了全部的情况。

## code:
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl "\n"
#define pii pair <int, int>

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int d;
	cin >> d;
	
	if (d > 10) cout << "1 2 3" << endl;
	else cout << "50 60 70" << endl;
	
	return 0;
}

```

---

## 作者：BlackHoles (赞：1)

### 正解

我们对 $d$ 进行分类讨论：当 $d \ge 10$ 时，我们令 $a = 1, b = 2, c = 3$，一定满足条件，因为凑出来的数最大是 $9$。

当 $d < 10$ 时，我们令 $a = 31, b = 53, c = 74$，同理也一定满足条件，凑不出 $i$ 满足 $1 \le i < 10$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int d;
int main(void) {
    cin >> d;
    if (d >= 10)
      	cout << "1 2 3";
    else
        cout << "31 53 74";
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 思路
我们可以对 $d$ 分类讨论。当 $d≥10$ 时，$a=1,b=2,c=3$ 一定可以满足条件。 当 $d<10$ 时，再求 $a,b,c$ 就很难了。  
于是，我们可以再次分类讨论。当 $d$ 为 $3$ 时，我们令 $a=20,b=32,c=48$。当 $d<10$ 且不为 $3$ 时，我们令 $a=19,b=31,c=47$。  
## 代码
```
#include <bits/stdc++.h>
using namespace std;
int main() {
    int d;
    cin >> d;
    if (d >= 10) cout << "1 2 3";
    else if(d!=3) cout << "19 31 47";
    else cout<<"20 32 48";
    return 0;
}
```

---

## 作者：Like_Amao (赞：1)

**前言**

[题目传送门](https://www.luogu.com.cn/problem/P13678)

**思路**

考虑对 $d$ 进行分类讨论：

* 如果 $d \ge 10$，当 $a , b , c$ 分别等于 1、2、3 时，因为最大可以凑出 9，所以一定满足题目条件。

* 如果 $d < 10$，当 $a , b , c$ 分别等于 31、53、47 时，也一定可以满足题目条件。因为这样子凑不出任意一个 $x$ 满足 $1 \le x \le 10$。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int d;
	cin>>d;
	if(d>=10)
	{
		cout<<"1 2 3";
	}
	else
	{
		cout<<"31 53 74";
	}
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## 题解：P13678 [GCPC 2023] Mischievous Math
### 分析
首先看到 $d$ 的最大值只有 $100$，而 $a,b,c$ 都可以取到一百，考虑先构造 $a=100,b=99,c=98$ 使大部分 $d$ 无解。此时开始特判这样有解的情况。

只用 $a,b,c$ 中的两个就有解的情况：当 $d=1$ 时，$a-b=1$，有解；当 $d=2$ 时，$a-c=2$，有解。

$a=100$，$b=99$，$c=98$，$b+c-a=97$，所以 $d=100,99,98,97$ 时都无解。

对于这几种有解情况，我们重新构造一个方案，使得 $3<a,b,c<97$ 且 $a,b,c$ 两两之间的差较大即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int d;
    cin>>d;
    if(d==1||d==2||d==100||d==99||d==98||d==97)
    {
        cout<<"4 7 34";
    }
    else cout<<"98 99 100";
}

---

## 作者：Sunrise_up (赞：1)

## 题意

给定一个数 $d$，输出三个不同的数 $a,b,c$ 满足 $a,b,c$ 使用四则运算和括号（四则运算符号必须不同）无法得到 $d$。

## 思路

考虑构造。

一般构造我们可以考虑极值。

例如 $1,2,3$，他能得到的数最大的是 $9$，所以 $d\ge 10$ 的情况可以直接这样输出。

那 $d<10$ 的情况怎么办呢？再考虑极值，例如 $98,99,100$，然后我们发现这个还要维护一个差值，所以就可以构造 $10,21,100$ 这样即可。

由于这个有开放性，所以这个答案是不唯一的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int d;
int main(){
    cin>>d;
    if(d>=10)cout<<"1 2 3";
    else cout<<"10 21 100";
}
```

这就结束了。

---

## 作者：M1__ (赞：0)

# 题解：P13678 [GCPC 2023] Mischievous Math

[Link](https://www.luogu.com.cn/problem/P13678)

挺有意思的题。

我们的策略如下：

- 对于一个较大的数，使构造出来的数尽可能小；
- 对于一个较小的数，使构造出的数字尽可能大即可。

所以，当 $d \ge10$ 是，显然数字 $a=1,b=2,c=3$ 符合条件。因为无论怎么使用这三个数和运算符，最大的数只能是 $9$。

对应的，当 $0 < d < 10$ 时，那么 $1-100$ 中三个最大的自然数 $a=100,b=99,c=98$ 显然符合条件。

但是注意 $1$ 和 $2$ 要特判，因为 $a-b=100-99=1$，$a-c=100-98=2$。这两组显然不符合条件。

这时我们可以分别找到 $a=100,b=98,c=96$ 和 $a=100,b=99,c=96$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll d;
int main(){
	cin>>d;
	if(d>=10) cout<<1<<" "<<2<<" "<<3<<" ";
	else{
		if(d==1) cout<<100<<" "<<98<<" "<<96<<" ";
		else if(d==2) cout<<100<<" "<<99<<" "<<96<<" ";
		else cout<<100<<" "<<99<<" "<<98<<" ";
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13678)

---
废话不少说，先简单概括题目，一句话就是：

我们要找一组三个数 $a,b,c$（$1$ 到 $100$ 之间，且与 $d$ 都不同），无论怎么加括号、加减乘除（每个数最多用一次），都不能得到 $d$。

既然了解了题目意思，一个小小的枚举即可解决问题。

我们分别枚举 $3$ 种情况：

* 只用一个数。
* 用两个数。
* 三个数全用。

随后比较结果（注意因为有除法的缘故要用 `double`），核心公式就是：
$$ \operatorname{fabs}(x,y) < 10^{-9}$$

在代码中还有一点小小的优化，例如第一个三元组不符合要求就直接输出并退出。

## AC code：
```cpp
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

bool eq(double x, double y) {
    return fabs(x - y) < EPS;
}

bool canMakeWithTwo(double x, double y, double target) {
    if (eq(x + y, target)) return true;
    if (eq(x - y, target)) return true;
    if (eq(y - x, target)) return true;
    if (eq(x * y, target)) return true;
    if (fabs(y) > EPS && eq(x / y, target)) return true;
    if (fabs(x) > EPS && eq(y / x, target)) return true;
    return false;
}

bool canMake(vector<double> nums, double target) {
    int n = nums.size();
    if (n == 0) return false;
    if (n == 1) {
        if (eq(nums[0], target)) return true;
        return false;
    }
    if (n == 2) {
        return canMakeWithTwo(nums[0], nums[1], target);
    }
    sort(nums.begin(), nums.end());
    do {
        double a = nums[0], b = nums[1], c = nums[2];
        vector<double> firstResults;
        firstResults.push_back(a + b);
        firstResults.push_back(a - b);
        firstResults.push_back(b - a);
        firstResults.push_back(a * b);
        if (fabs(b) > EPS) firstResults.push_back(a / b);
        if (fabs(a) > EPS) firstResults.push_back(b / a);

        for (double r : firstResults) {
            if (eq(r + c, target)) return true;
            if (eq(r - c, target)) return true;
            if (eq(c - r, target)) return true;
            if (eq(r * c, target)) return true;
            if (fabs(c) > EPS && eq(r / c, target)) return true;
            if (fabs(r) > EPS && eq(c / r, target)) return true;
        }

        vector<double> secondResults;
        secondResults.push_back(b + c);
        secondResults.push_back(b - c);
        secondResults.push_back(c - b);
        secondResults.push_back(b * c);
        if (fabs(c) > EPS) secondResults.push_back(b / c);
        if (fabs(b) > EPS) secondResults.push_back(c / b);

        for (double r : secondResults) {
            if (eq(a + r, target)) return true;
            if (eq(a - r, target)) return true;
            if (eq(r - a, target)) return true;
            if (eq(a * r, target)) return true;
            if (fabs(r) > EPS && eq(a / r, target)) return true;
            if (fabs(a) > EPS && eq(r / a, target)) return true;
        }

    } while (next_permutation(nums.begin(), nums.end()));

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int d;
    if (!(cin >> d)) return 0;
    for (int a = 1; a <= 100; ++a) {
        if (a == d) continue;
        for (int b = a + 1; b <= 100; ++b) {
            if (b == d) continue;
            for (int c = b + 1; c <= 100; ++c) {
                if (c == d) continue;
                bool possible = false;
           
                if (eq(a, d) || eq(b, d) || eq(c, d)) possible = true;
          
                if (!possible) {
                    if (canMakeWithTwo(a, b, d)) possible = true;
                    else if (canMakeWithTwo(a, c, d)) possible = true;
                    else if (canMakeWithTwo(b, c, d)) possible = true;
                }
      
                if (!possible) {
                    vector<double> nums = {double(a), double(b), double(c)};
                    if (canMake(nums, d)) possible = true;
                }
                if (!possible) {
                    cout << a << " " << b << " " << c << "\n";
                    return 0;
                }
            }
        }
    }
    cout << "1 20 30\n";
    return 0;
}
```

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13678)

### 题目分析
我们可以证明，当 $a = 1,b = 2,c = 3$ 时，完全无法凑出 $\ge 10$ 的数字。当 $d \le 10$ 时，我们让 $a = 57,b = 91,c = 11$，一定无法凑出 $\le 10$ 的数。

### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int d;
int main() {
	cin >> d;
	if (d >= 10)cout << "1 2 3";
	else cout << "57 91 11";
	return 0;
}
```

---

## 作者：cyz1234 (赞：0)

# 题解：P13678 [GCPC 2023] Mischievous Math
## 题意
这里有一个数 $d$，我们要找出 $a,b,c$ 三个数，使得这三个数取若干个数用加减乘除的方式不能得到 $d$。
## 思路
因为有 $a\le100$，所以我们可以取比较大得数，如 $98,99,100$。枚举一下,我们会发现 $1,2,97,98,99,100$ 这几个数仍可以用加减乘除的方式得到 $d$，所以这几个数需要特判，寻找范围为 $3\le a,b,c\le96$，我推荐使用质数,这样就不会出现除法运算了。

经上述推理,我们可以得到 $a,b,c = \begin{cases}
  98,99,100&(3\le d\le96)\\
  23,37,41&(d=1,2,97,98,99,100)\
\end{cases}$
## 奉上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
	int d;
	cin>>d;
	if(d==1||d==2||d==97||d==98||d==99||d==100){ //特判
		cout<<"23 37 41";
	}
	else{ //3<=d<=100
		cout<<"98 99 100";
	}
	return 0;
}
```

---

## 作者：Planet_Earth (赞：0)

## 题解：P13678 \[GCPC 2023] Mischievous Math

### 题目简要

给定一个数字 $d$，找出互不相同的三个数，这三个数均与 $d$ 不同，

使这三个数无法通过组合运算得到 $d$。

### 方法分析

这题的关键在于构造和分类讨论（~~有点难~~）。

这里可以根据 $d$ 的大小分为两种情况：

- 当 $d \geq 10$ 时：使三个数分别为 1,2,3，因为这样通过四则运算，最大的结果为 9。

- 当 $d < 10$ 时：使三个数分别为 41,67,89，因为这样通过四则运算无法得到小于 10 的数（可以有其他构造出的答案，这里不逐个列举）。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
signed main(){
	scanf("%lld",&n);
	if(n>=10){
		puts("1 2 3");
	}
	else{
		puts("41 67 89");
	}
	return 0;
}
//Planet_Earth

```

### 后记

谨以此文，纪念我的童年，那是一段小有遗憾的 OI 时光。

---

## 作者：wjh27465 (赞：0)

# 题解：P13678 [GCPC 2023] Mischievous Math
## 题目大意
输入一个数字 $d$，输出三个互不相等的正整数 $a,b,c$ 使得无法用这三个数通过加、减、乘、除及括号得出结果为 $d$。（每个数字最多用一次）
## 分析
观察到当 $a,b,c$ 很小时，无法运算出较大的数。取 $a=1,b=2,c=3$，此时能运算出的最大数为 $(1+2) \times 3=9$，所以当 $d \ge 10$ 时，输出`1 2 3`即可。  
对于 $d<10$ 的情况，我们可以构造三个素数，每两个之间的差都大于 $10$，同时较小两个素数的和比最大的素数至少小 $10$。例如取`11 29 53`，它们运算不出小于 $10$ 的数。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int d;
    cin>>d;
    if(d>=10)
        cout<<"1 2 3";
    else
        cout<<"11 29 53";
    return 0;
}
```

---

## 作者：枫原万叶 (赞：0)

在此之前先附上该题中文翻译：[中文题面](https://www.luogu.me/paste/eqrigiwq)

由于数据范围中 $1 \le a,b,c,d \le 100$，所以我们可以考虑枚举。

首先明确如果一个数为 $d$ 一定不行的，以及题目明确互不相同，这些情况直接跳过。

我们设置两个 `check` 函数，一个用于检查两个数的情况是否有可能出现结果为 $d$，另一个检查三个数的情况。

在设置第二个 `check` 函数时，我们直接用上一个已经写好的函数计算两两数之间的结果情况。

总而言之，这一题没有难点，使用枚举就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool c2(int x,int y,int d){
	if(x+y==d)return 1;
	if(x-y==d)return 1;
	if(y-x==d)return 1;
	if(x*y==d)return 1;
	if(y&&x%y==0&&x/y==d)return 1;
	if(x&&y%x==0&&y/x==d)return 1;
	return 0;
}
bool c3(int x,int y,int z,int d){
	int t=x+y;
	if(c2(t,z,d))return 1;
	t=x-y;
	if(c2(t,z,d))return 1;
	t=y-x;
	if(c2(t,z,d))return 1;
	t=x*y;
	if(c2(t,z,d))return 1;
	if(y&&x%y==0){
		t=x/y;
		if(c2(t,z,d))return 1;
	}
	if(x&&y%x==0){
		t=y/x;
		if(c2(t,z,d))return 1;
	}
	return 0;
}
bool chk(int a,int b,int c,int d){
	if(c2(a,b,d))return 0;
	if(c2(a,c,d))return 0;
	if(c2(b,c,d))return 0;
	if(c3(a,b,c,d))return 0;
	if(c3(a,c,b,d))return 0;
	if(c3(b,c,a,d))return 0;
	return 1;
}
int main(){
	int d;
	cin>>d;
	for(int a=100;a>=1;a--){
		if(a==d)continue;
		for(int b=100;b>=1;b--){
			if(b==d||b==a)continue;
			for(int c=100;c>=1;c--){
				if(c==d||c==a||c==b)continue;
				if(chk(a,b,c,d)){
					cout<<a<<' '<<b<<' '<<c<<endl;
					return 0;
				}
			}
		}
	}
	return 0;
}
```

---

