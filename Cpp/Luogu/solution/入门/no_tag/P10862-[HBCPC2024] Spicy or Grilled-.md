# [HBCPC2024] Spicy or Grilled?

## 题目描述

由于一场常规的编程比赛持续五个小时，因此在比赛期间为参赛者准备食物是一个大问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/nh1zzieg.png)

在 20XX 年中国湖北省的国际大学生程序设计竞赛中，有 $n$ 名参赛者参加比赛。主办方希望为每位参赛者准备一份辣鸡汉堡套餐，当时每份套餐的价格为 $a$ 美元。但由于有些人无法忍受辣味，比如 Walk Alone，主办方为这些人准备了烤鸡汉堡套餐，每份套餐的价格为 $b$ 美元。比赛前，主办方收集了想要吃烤鸡汉堡套餐的人数 $x$。

但 Walk Alone 太笨太懒，无法计算主办方将花费多少钱。请帮助他计算。

## 说明/提示

在第一个测试用例中，有 $400$ 人选择了辣鸡汉堡套餐，$200$ 人选择了烤鸡汉堡套餐。因此总金额为 $400 \times 27 + 200 \times 26 = 16\ 000$ 美元。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3
600 200 27 26
750 0 26 27
750 750 1 1```

### 输出

```
16000
19500
750```

# 题解

## 作者：luogu_gza (赞：52)

很难不发现答案就是 $(n-x) \times a + x \times b$。

不过个人还是觉得板烧比麦辣好吃！

---

## 作者：Milkshakefairytale (赞：5)

## 大致翻译

### 题意

在中国湖北省举行的 20XX 年国际大学生程序设计大赛中，有 $n$ 名参赛者参加了比赛。主持人想为每位参赛者准备一套辣鸡汉堡，当时每套售价为 $ a $ 美元。但由于有些人无法忍受像 Walk Alone 这样的辣味，因此为这些人准备了一套烤鸡汉堡，每套售价为 $ b $ 美元。比赛前，主持人收集了 $ x $ 位想吃烤鸡汉堡的人。

但 Walk alone 太愚蠢太懒惰了，无法计算主持人会花多少钱。请帮他计算一下。

### 输入格式

第一行输入一个 $ T $ ，表示一共有 $ T $ 组数据

接下来T行，每行输入 $ n,x,a, b $ 。

### 输出格式

输出要花费的总价格。

### 数据范围
$$ 1 \le T,n,a,b \le 1 \times 10^4 $$

$$ 1 \le x \le T $$

## 题目分析

这是一道非常简单的题目。

一共有 $ n $ 个人，其中有 $ x $ 个人不吃辣堡，也就是说有 $ (n-x) $ 吃个人单价为 $ a $ 元的辣堡， $ x $ 个人吃单价为 $ b $ 的烤鸡汉堡。

这样就算是对于一个题目的整体分析了。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {//快读函数 
    int s = 0, f = 1;
    char ch = getchar();
    while ('0' > ch || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while ('0' <= ch && ch <= '9') {s = (s << 3) + (s << 1) + ch - 48; ch = getchar();}
    return s * f;
}
inline void write(int x)//快写函数 
{
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9)
		write(x/10);
    putchar(x%10+'0');
}
int t,n,x,a,b;
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		x=read();
		a=read();
		b=read();
		write((n-x)*a+x*b);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：x1489631649 (赞：5)

### [题目链接](https://www.luogu.com.cn/problem/P10862)
### 输入 
多组数据，每组数据两个整数 $n,a,b,c(1 \le n,a,b,c \le 10^4)$。
### 输出
买汉堡需要耗费的钱数。
### 分析
只有两种汉堡，所以**总人数减去想要第一个汉堡的人数**就可以得到**第二种汉堡的人数**，但是我们要注意一下每个汉堡对应的钱数，**不要写反了**。
### Code
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long t,n,a,b,c;
    cin>>t;
    while(t--)
    {
        cin>>n>>a>>b>>c;
        cout<<a*c+(n-a)*b<<endl;
    }
    return 0;
}
```
### 时间复杂度
时间复杂度为 $O(t)$，显然可以通过。

---

## 作者：Vct14 (赞：4)

本场比赛签到题。

题意：麦辣鸡腿堡一个 $a$ 美元，板烧鸡腿堡一个 $b$ 美元。一共 $n$ 个人，$x$ 吃板烧鸡腿堡，剩下的人吃麦辣鸡腿堡。求总钱数。

按照题意模拟即可。$x$ 个板烧鸡腿堡 $bx$ 美元，剩下 $n-x$ 个麦辣鸡腿堡 $a(n-x)$ 美元。两者相加即可。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int t;cin>>t;
	while(t--){
		int n,x,a,b;cin>>n>>x>>a>>b;
		cout<<(n-x)*a+x*b<<"\n";
	}
	return 0;
}
```

---

## 作者：Amberhart (赞：4)

因为没有翻译，所以我浅翻译一下。

买汉堡，有些人想要烤鸡汉堡，其他人想要辣鸡汉堡。而两种汉堡价格是不一样的。一共有 $t$ 组数据，输入总人数 $n$，想要烤鸡汉堡的人数 $x$，辣鸡汉堡单价 $a$，烤鸡汉堡单价 $b$。输出总费用。

根据，单价 $×$ 数量 $=$ 总价，可得：

总费用 $=$ 辣鸡汉堡费用 $+$ 烤鸡汉堡费用 $=$ 辣鸡汉堡单价 $×$ 辣鸡汉堡数量 $+$ 烤鸡汉堡单价 $×$ 烤鸡汉堡数量。

唯一需要注意的是，输入的第一个数是总人数，并不是想要辣鸡汉堡的人数，所以在计算想要辣鸡汉堡的人数时，应用总人数 $-$ 烤鸡汉堡人数。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,x,a,b;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n>>x>>a>>b;
		cout<<(n-x)*a+x*b<<endl;
	}
	return 0;
}

```

---

## 作者：_Star_Universe_ (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/P10862)
### 题意
有 $n$ 名参赛选手，其中 $x$ 名选手想吃烤鸡汉堡，剩余选手想吃辣鸡汉堡，已知一套辣鸡汉堡价格 $a$ 元，一套烤鸡汉堡价格 $b$ 元，问你请这些选手吃汉堡要花多少钱。

### 思路
按题意计算即可，有 $x$ 名选手想吃烤鸡汉堡，$n-x$ 名选手想吃辣鸡汉堡，单价也都知道了，答案很好算：
$$ans = (n-x) \times a + x \times b$$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x,a,b;
		cin>>n>>x>>a>>b;
		cout<<(n-x)*a+x*b<<endl;
	}
	return 0;
}
```

---

## 作者：_Drifting_ (赞：2)

[P10862 [HBCPC2024] Spicy or Grilled?](https://www.luogu.com.cn/problem/P10862)

## 题意
告诉你参赛者总数，想要烤鸡肉汉堡套餐的人数，辣鸡肉汉堡套餐和烤鸡肉汉堡套餐的价格，让我们求总共需要多少钱。

## 思路
题目让我们要求总钱数，我们都知道总钱数是单价 $\times$ 数量得来的，我们假设告诉你的数是 $a$，$b$，$c$ 和 $d$，那么我们就可以得以得出吃辣鸡肉汉堡套餐有 $a-b$ 个人，总共要付 $b\times d+(a-b)\times c$ 元钱。

## 代码

```cpp
#include<bits/stdc++.h》 
#define int long long
using namespace std;
int t;
signed main(
{
	cin>>t;
	while(t--)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		cout<<b*d+(a-b)*c<<endl;
	}
	return 0； 
}

```

---

## 作者：sieve (赞：2)

# 题解：[P10862 [HBCPC2024] Spicy or Grilled?](https://www.luogu.com.cn/problem/P10862)

## 大致题意

一共有 $t$ 组数据，每组数据给出 $4$ 个数，分别是：参加竞赛的总人数、吃不辣的汉堡套餐的人数、辣的汉堡套餐的价钱、不辣的汉堡套餐的价钱，对于每组数据，让你求出总共要花费的价钱。

## 思路

既然我们知道了吃不辣的汉堡套餐的人数以及不辣的汉堡套餐的价钱，那么我们就可以求出这一类人所需的花费，也就是 $b \times d$。

剩下的人肯定就是吃辣的汉堡的，那么剩下的人数为：$a - b$，我们又知道了辣的汉堡套餐的价钱，我们就可以轻而易举的算出这一类人所需的花费，也就是 $(a - b) \times c$。

既然知道了两类人所需的价钱，我们直接相加就能得到答案。

## Code:


```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//使用命名空间
void solve()//处理每一组数据的函数
{
	int a,b,c,d;//分别是总人数、吃不辣的人数、辣的套餐价钱、不辣的套餐价钱
	cin>>a>>b>>c>>d;//输入
	cout<<b*d+(a-b)*c<<'\n';//按照刚才讲的进行运算
	return;//好习惯
}
int main()//主函数
{
	int t;//数据组数
	cin>>t;//输入
	while(t--) solve();//处理多组数据的模板
	return 0;//结束程序
}
```

---

## 作者：__galaxy_1202__ (赞：1)

## 题目解析：
签到题，总人数减 $x$ 就可以分成吃两种不同汉堡分别的人数，乘对应的价格即可，代码实现就是计算 $(n - x) \times a + b \times x$。
## CODE:

```cpp
#include <iostream>
using namespace std;
int t, n, a, b, x;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> x >> a >> b;
        cout << (n - x) * a + b * x << '\n';
    }
    return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

# 题解：P10862 [HBCPC2024] Spicy or Grilled?
# 0x00 思路
此题为签到题，十分简单。

首先我们注意到这题是 $T$ 组数据，于是我们读入 $T$，然后再输入每组数据。

对于每组数据，我们已知两种汉堡的价格，总人数，和要吃一种汉堡的人数，于是我们可以用总人数减去要吃一种汉堡的人数，就可以得到要吃另一种汉堡的人数，再把吃两种汉堡的人数乘上他们的价格，最后加起来就是结果了。
# 0x01 代码
```cpp
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;

ll T, n, x, a, b;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T--) {
		cin >> n >> x >> a >> b;
		ll y = n - x;
		cout << x * b + y * a << endl;
	}
	return 0;
}
```

---

## 作者：ChampionCyan (赞：1)

# [HBCPC2024] Spicy or Grilled? 题解

## 题意

$T$ 组数据，每组告诉你 $n,x,a,b$ 四个整数，分别代表总数、第二种汉堡的个数、第一种汉堡的价钱和第二种汉堡的价钱。

## 做法

很明显第二种汉堡有 $n-x$ 个。

则答案为：

$$
bx+a(n-x)
$$

输出即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x, a, b;
        scanf("%d%d%d%d", &n, &x, &a, &b);
        printf("%d\n", x * b + (n - x) * a);
    }
    return 0;
}
```

---

## 作者：joker_opof_qaq (赞：1)

### 题意简述

现在一个有 $n$ 个人，且有 $x$ 个人想吃 `Spicy Chicken Burger` 其他人都想吃 `Grilled Chicken Burger`，且告诉你这两种汉堡的价格，求一共要花多少钱？

### 分析 && 实现

直接按照题意模拟即可，签到题。

输出 $a \times ( n - x ) + b \times x$，其中，$n$ 表示总人数，$a$ 和 $b$ 表示两种汉堡的价钱，$x$ 是想吃 `Spicy Chicken Burger` 的人数。

### AC CODE

[link](https://www.luogu.com.cn/problem/P10862#submit)

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if (x<0)x=-x,putchar('-');
	if (x>9)write(x/10);
	putchar(x%10+'0');
}
int main() {
	int t;
	cin>>t;
	while(t--){
		int n=read(),x=read(),a=read(),b=read();
		cout<<a*(n-x)+b*x<<'\n';
	}
	return 0;
}

```

---

## 作者：_QWQ__QWQ_ (赞：0)

## 题目翻译：

有 $n$ 个人，我们为他们买了香辣鸡肉汉堡套餐，每份是 $a$ 元，可是里面有 $x$ 人不能吃辣，于是还准备了 $x$ 份烤鸡汉堡套餐，每份是 $b$ 元，求总共要多少元。

## 解题思路

一眼计算，实际上吃烤鸡汉堡的人是 $x$，吃香辣汉堡的人就是 $n-x$，所以最终答案就是 $(n-x)\times a+x\times b$。

### 考时 AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int maxn=1e6+5;
int t;
int n,x,a,b;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x>>a>>b;
		cout<<(n-x)*a+(x)*b<<endl;
	}
	return 0;
}
```

---

## 作者：RainCQwQ (赞：0)

# P10862
## 思路整理
作为一道签到题，本题还是比较简单的。

本题的题意大概指：有两种汉堡套餐，一种是辣的，另一种不辣，分别需要 $a,b$ 块钱，总共 $n$ 人需要汉堡，但有 $x$ 人不喜欢吃辣，请问一共要花多少元来购买汉堡。

我们可以设有 $y$ 人喜欢吃辣堡，则 $y = n - x$，答案则为 $ya + xb = a(n - x) + xb$。

## Code
```cpp
#include <iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,x,a,b;
        cin>>n>>x>>a>>b;
        cout<<a*(n-x)+b*x<<endl;
    }
    return 0;
}
```

---

## 作者：__qp__ (赞：0)

题意：

有 $n$ 名参赛者。每位参赛者需要一个 $a$ 美元的套餐，但有 $x$ 人需要 $b$ 美元的套餐。计算总花费。

思路：

不难发现总花费为 $x\times b + (n - x)\times a$。直接模拟即可。


```cpp
#include <iostream>
using namespace std;
int main(){
    int T;
    cin >> T;
    while(T--){
        int n, x, a, b;
        cin >> n >> x >> a >> b;
        int c = x * b + (n - x) * a;
        cout << c << '\n';
    }
    return 0;
}

```

---

## 作者：__HappY__ (赞：0)

### 题意

有 $T$ 次询问，每次询问有 $n$ 个选手，$x$ 个人想吃烤鸡肉汉堡套餐，辣鸡肉汉堡套餐的价值为 $a$ 元，烤鸡肉汉堡套餐的价值为 $b$ 元，问一共花费多少元。

### 思路

共有 $n$ 个选手，$x$ 个人想吃烤鸡肉汉堡套餐，则有 $n - x$ 个人想吃辣鸡肉汉堡套餐。所以总花费就是想吃烤鸡肉汉堡套餐的人数乘烤鸡肉汉堡套餐的单价加上想吃辣鸡肉汉堡套餐的人数乘辣鸡肉汉堡套餐的单价。

### 代码

很简单，我就不加注释了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, x, a, b;
int main() {
	cin >> t;
	while(t--) {
		cin >> n >> x >> a >> b;
		cout << (n - x) * a + x * b << endl;
	}
	return 0;
}

``````

---

## 作者：JYX0924 (赞：0)

这道题直接按照题意模拟即可，答案是 $(n-x)\times a+x\times b$。

下面是我的 AC 代码。


```c
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll T;
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>T;
    while(T--)
    {
        ll a,b,c,d; cin>>a>>b>>c>>d;
        cout<<(a-b)*c+b*d<<"\n";
    }
    return 0;
}
```
谢谢大家！！！

---

## 作者：Breath_of_the_Wild (赞：0)

题意：给定 $n,x,a,b$，表示要买 $n-x$ 个价格为 $a$ 的，和 $x$ 个价格为 $b$ 的，求总钱数。

入门题，考察基本运算（算术运算）以及输入输出操作。

```cpp
cout<<(n-x)*a+x*b<<'\n';
```

---

## 作者：xinxin2022 (赞：0)

首先，在烤鸡肉汉堡上花的钱是 $xb$，而其他的 $n-x$ 人想要的就是香辣鸡肉汉堡，会花 $(n-x)a$ 块钱，因此总花费为 $xb+(n-x)a$。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long a,b,c,d;
//开long long!!!
int main(){
    cin>>t;
    while(t--){
        cin>>a>>b>>c>>d;
        cout<<b*d+(a-b)*c<<'\n';
        //直接输出即可
    }
    return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

[P10862 [HBCPC2024] Spicy or Grilled?](https://www.luogu.com.cn/problem/P10862)

题目描述里的图片怎么中英混合啊。

简要题意：第一种汉堡 $a$ 元一个，第二种汉堡 $b$ 元一个。有 $n$ 个人，其中 $x$ 个人要买第二种汉堡，其余人买第一种，求总花费。

这 $x$ 个人都买第二种的总花费为 $x\times b$，剩余 $n-x$ 个人总花费为 $(n-x)\times a$。答案为 $(n-x)\times a+x\times b$。

```cpp
while (T--) {
	int n, x, a, b;
	cin >> n >> x >> a >> b;
	cout << (n - x) * a + x * b << '\n';
}
```

---

## 作者：Restart_Justin (赞：0)

### 题目大意
有 $n$ 个人，有 $x$ 个人想吃烤鸡汉堡（烤鸡汉堡售价为 $b$ 美元），其余的人想吃麦辣汉堡（麦辣汉堡售价为 $a$ 美元），问满足这些人所有要求至少要付多少美元。

### 思路

有 $x$ 个人想吃烤鸡汉堡，那么烤鸡汉堡的总价就是 $xb$ 美元，剩下的人数容易用减法得出是 $n-x$ 人，那么求这些人所需要的总价钱就是 $a(n-x)$ 美元，加起来就是 $xb + a(n-x)$ 美元。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--) {
        int n, x, a, b;
        cin >> n >> x >> a >> b;
        cout << x * b + (n - x) * a << "\n";
    }
}
```

---

