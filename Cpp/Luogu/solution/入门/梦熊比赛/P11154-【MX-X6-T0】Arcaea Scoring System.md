# 【MX-X6-T0】Arcaea Scoring System

## 题目背景

原题链接：<https://oier.team/problems/X6A>。

## 题目描述

Arcaea 是一款风靡全球的音乐游戏，以其创新式的三维立体游玩界面知名。在 Arcaea 中，玩家通过点击/滑动屏幕的方式随着音乐的节奏游玩对应的谱面。一次谱面游玩的计分方式如下：

- 谱面包含若干个**物件**。每一个物件的判定结果有 **大 Pure**、**小 Pure**、**Far**、**Lost** 四种。
- 对于一个 $n$ 个物件的谱面，其 **基本分** 为 $10^7$ 分，**附加分** 为 $n$ 分，满分为 $10^7+n$ 分。每一个物件分别占 $\dfrac{10^7}{n}$ 分 **基本分** 和 $1$ 分 **附加分**。
- 如果一个物件获得 **大 Pure** 判定，则玩家获得该物件的全部基本分和附加分。
- 如果一个物件获得 **小 Pure** 判定，则玩家仅获得该物件的全部基本分，不获得附加分。
- 如果一个物件获得 **Far** 判定，则玩家仅获得该物件的基本分的一半。
- 如果一个物件获得 **Lost** 判定，则玩家不获得任何分数。
- 游玩分数为玩家所有物件获得的分数总和**下取整**。

玩家在分数的基础上可以获得 **评级**：

- 游玩分数 $\geq 9.9\times 10^6$ 时，获得 **EX+** 评级；
- 游玩分数 $\geq 9.8\times 10^6$ 但 $<9.9\times 10^6$ 时，获得 **EX** 评级；
- 游玩分数 $\geq 9.5\times 10^6$ 但 $<9.8\times 10^6$ 时，获得 **AA** 评级；
- 游玩分数 $\geq 9.2\times 10^6$ 但 $<9.5\times 10^6$ 时，获得 **A** 评级；
- 游玩分数 $\geq 8.9\times 10^6$ 但 $<9.2\times 10^6$ 时，获得 **B** 评级；
- 游玩分数 $\geq 8.6\times 10^6$ 但 $<8.9\times 10^6$ 时，获得 **C** 评级；
- 游玩分数 $<8.6\times 10^6$ 时，获得 **D** 评级。

现在分别给定一次谱面游玩的四种判定的个数，请计算这次游玩的评级。

## 说明/提示

**【样例解释 #1】**

所有物件的判定结果均为大 Pure，因此玩家获得全部基本分 $10^7$ 分和全部附加分，由于总共有 $44$ 个物件，故额外获得 $44$ 分，故游玩分数为 $10{,}000{,}044$；总分大于等于 $9.9\times 10^6$，从而获得 EX+ 评级。

**【样例解释 #2】**

物件个数为 $33 + 10 + 0 + 1 = 44$ 个。$33$ 个物件的判定结果为大 Pure、$10$ 个物件的判定结果为小 Pure、$1$ 个物件的判定结果为 Lost，因此玩家获得 $\dfrac{43}{44} \times 10^7$ 的基本分和 $33$ 分附加分，故分数总和为 $9{,}772{,}760.\dot 2 \dot 7$，游玩分数向下取整到 $9{,}772{,}760$；总分大于等于 $9.5\times 10^6$ 且小于 $9.8\times 10^6$，从而获得 AA 评级。

**【数据范围】**

对于所有数据，保证 $p_0,p_1,f,l\geq 0$，$1\leq n\leq 100$。

共 $10$ 组数据，对于前 $2$ 组数据，保证 $n=1$。

## 样例 #1

### 输入

```
44 0 0 0```

### 输出

```
EX+```

## 样例 #2

### 输入

```
33 10 0 1```

### 输出

```
AA```

## 样例 #3

### 输入

```
0 0 0 1```

### 输出

```
D```

# 题解

## 作者：Little_x_starTYJ (赞：10)

### 题意简述
在某款游戏中，有着 $n$ 个物件，每个物件都有四种判定方式。

- **大 Pure** 判定，该玩家获得 $\frac{10^7}{n} + 1$ 分。
- **小 Pure** 判定，该玩家获得 $\frac{10^7}{n}$ 分。
- **Far** 判定，该玩家获得 $\frac{\frac{10^7}{n}}{2}$ 分。
- **Lost** 判定，该玩家不得分。

玩家获得的分数也有着一种评级方式。

设 $s$ 为该玩家获得的分数。
- $s < 8.6\times 10^6$ 时，该玩家获得 **D** 评级。
- $8.6\times 10^6 \leq s < 8.9\times 10^6$ 时，该玩家获得 **C** 评级；
- $8.9\times 10^6 \leq s < 9.2\times 10^6$ 时，该玩家获得 **B** 评级；
- $9.2\times 10^6 \leq s < 9.5\times 10^6$ 时，该玩家获得 **A** 评级；
- $9.5\times 10^6 \leq s < 9.8\times 10^6$ 时，该玩家获得 **AA** 评级；
- $9.8\times 10^6 \leq s < 9.9\times 10^6$ 时，该玩家获得 **EX** 评级；
- $s \geq 9.9\times 10^6$ 时，该玩家获得 **EX+** 评级；

现告诉你该玩家获得 **大 Pure、小 Pure、Far、Lost** 评定的物件的个数，请你求出玩家所得分数的评级。

### 解题思路
设 $n = p_1 + p_0 + f + l,x = \frac{10^7}{n}$。

- 对于 **大 Pure** 判定，我们把总分加上 $(x + 1) \times p_1$。
- 对于 **小 Pure** 判定，我们把总分加上 $x \times p_0$。
- 对于 **Far** 判定，我们把总分加上 $\frac{x}{2} \times f$。
- 对于 **Lost** 判定，我们什么也不用管。

算出来总分后，我们挨个判定当前分数属于哪个评级即可。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int p1, p0, f, l;
	cin >> p1 >> p0 >> f >> l;
	int n = p1 + p0 + f + l;
	int scores = (1e7 / n + 1) * p1;
	scores += (1e7 / n) * p0;
	scores += (1e7 / n / 2) * f;
	scores += 0;   //Lost 不用加分。
	if (scores < 8.6 * 1e6) {
		cout << "D";
	} else if (scores < 8.9 * 1e6) { //这里已经满足 scores >= 8.6 * 1e6
		cout << "C";
	} else if (scores < 9.2 * 1e6) {
		cout << "B";
	} else if (scores < 9.5 * 1e6) {
		cout << "A";
	} else if (scores < 9.8 * 1e6) {
		cout << "AA";
	} else if (scores < 9.9 * 1e6) {
		cout << "EX";
	} else {
		cout << "EX+";
	}
	return 0;
}
```

---

## 作者：Chillturtle (赞：7)

有多少人是~~水灌水~~的时候点进来的（逃。

# 题意

就是输入 4 个数，每个数代表四种不同操作的数量。然后有一个基本分 $\frac{10^7}{n}$，其中 $n$ 就是 4 种操作的总数量。一个 $p_1$ 操作的分数是基本分再加一个附加分。一个 $p_0$ 操作只有基本分。一个 $f$ 操作是基本分的一半。一个 $l$ 操作没有分。

给你如下标准，让你判断是哪个等级：

- 游玩分数 $\geq 9.9\times 10^6$ 时，获得 **EX+** 评级；
- 游玩分数 $\geq 9.8\times 10^6$ 但 $<9.9\times 10^6$ 时，获得 **EX** 评级；
- 游玩分数 $\geq 9.5\times 10^6$ 但 $<9.8\times 10^6$ 时，获得 **AA** 评级；
- 游玩分数 $\geq 9.2\times 10^6$ 但 $<9.5\times 10^6$ 时，获得 **A** 评级；
- 游玩分数 $\geq 8.9\times 10^6$ 但 $<9.2\times 10^6$ 时，获得 **B** 评级；
- 游玩分数 $\geq 8.6\times 10^6$ 但 $<8.9\times 10^6$ 时，获得 **C** 评级；
- 游玩分数 $<8.6\times 10^6$ 时，获得 **D** 评级。

# 思路

没有思路直接模拟即可。有的人问这个下取整是不是要用 float 或者 double 先存再算。实际上是不需要的直接用 int 存就好啦。

# AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int p1,p0,f,l,n,jb,zongfen;
signed main(){
    cin>>p1>>p0>>f>>l;
    n=p1+p0+f+l;
    jb=10000000/n;
    zongfen=p1*(jb+1)+p0*jb+f*jb/2;
    if(zongfen>=9.9*1e6){
        cout<<"EX+"<<endl;
    }else if(zongfen>=9.8*1e6){
        cout<<"EX"<<endl;
    }else if(zongfen>=9.5*1e6){
        cout<<"AA"<<endl;
    }else if(zongfen>=9.2*1e6){
        cout<<"A"<<endl;
    }else if(zongfen>=8.9*1e6){
        cout<<"B"<<endl;
    }else if(zongfen>=8.6*1e6){
        cout<<"C"<<endl;
    }else{
        cout<<"D"<<endl;
    }
    return 0;
}
```

# 广告

既然出题人都给大家安利了 Arcaea，那 Phigros 也不能少呀。。。

[传送门](https://baike.baidu.com/item/Phigros/23574270?fr=ge_ala) ~~找不到下载地址了，放了个百度百科。~~

使用 ipad 体感更好 (＾Ｕ＾)ノ~ＹＯ。

---

## 作者：csxx601cjy (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/P11154)

简单的模拟题。

题意：输入 4 个数，算出总分并评级。

需掌握的知识点：浮点数，条件判断语句。

只要统计每个结果的总分就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int P,p,f,l,n;
double sum=0,sn;

int main(){
	cin>>P>>p>>f>>l;

	n=P+p+f+l;
	sn=1.0*1e7/n;//每个物品的基本分
	sum+=sn*P+P;//开始统计总分
	sum+=sn*p;
	sum+=sn*0.5*f;

	if(sum>=9.9e6){cout<<"EX+";return 0;}//评等级
	if(sum>=9.8e6){cout<<"EX"; return 0;}
	if(sum>=9.5e6){cout<<"AA"; return 0;}
	if(sum>=9.2e6){cout<<"A";  return 0;}
	if(sum>=8.9e6){cout<<"B";  return 0;}
	if(sum>=8.6e6){cout<<"C";  return 0;}
	cout<<"D";
  return 0;
}
```
嫌我代码长的大佬可以看下面这篇：

```cpp
#include<bits/stdc++.h>
int P,p,f,l,n,k=1e6;
double sum,sn,s[7]={9.9,9.8,9.5,9.2,8.9,8.6,0};
std::string level[7]={"EX+","EX","AA","A","B","C","D"};
int main(){
	std::cin>>P>>p>>f>>l;
	n=P+p+f+l,sn=10.0*k/n,sum=sn*P+P+sn*p+sn*0.5*f;
	for(int i=0;i<7;i++)if(sum>=s[i]*k){std::cout<<level[i];return 0;}
}
```
管理员审核辛苦了，希望这篇题解可以帮助大家。

---

## 作者：__Rickysun__ (赞：0)

### 思路
阅读题目之后我们不难推出分数就是 $\frac{10^7}{n}×a+1+\frac{10^7}{n}×b+\frac{5×10^6}{n}×c+0×d$ ，然后再向下取整，并通过比较分出等级，从而得出最终的答案。
### 提醒
答案计算的时候一定要是浮点数类型，不能在其中一次计算中就想下取整，可能造成精度损失，从而导致最后的答案不正确。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a，b，c，d;
double ans;
int main(){
	cin>>a>>b>>c>>d;
	int n=a+b+c+d;
	ans+=10000000.0/n*a+1+10000000.0/n*b+5000000.0/n*c+0*d;//计算
	ans=(int)ans;//向下取整
	//比较
	if(ans>=9900000) cout<<"EX+";
	else if(ans>=9800000) cout<<"EX";
	else if(ans>=9500000) cout<<"AA";
	else if(ans>=9200000) cout<<"A";
	else if(ans>=8900000) cout<<"B";
	else if(ans>=8600000) cout<<"C";
	else cout<<"D";
	return 0;
}
```

---

## 作者：Tsz1024_AK (赞：0)

### 题目解析
- 谱面包含若干个物件，分别有 大 Pure、小 Pure、Far、Lost 四种。对于 $n$ 个物件的谱面，其 **基本分** 为 $10^7$ 分，**附加分** 为 $n$ 分，满分为 $10^7+n$ 分。每一个物件分别占 $10^7 \div n$ 分 **基本分** 和 $1$ 分 **附加分**。
- 玩家在分数的基础上可以获得 **评级**：
  - 游玩分数 $\geq 9.9\times 10^6$ 时，获得 **EX+** 评级；
  - 游玩分数 $\geq 9.8\times 10^6$ 但 $<9.9\times 10^6$ 时，获得 **EX** 评级；
  - 游玩分数 $\geq 9.5\times 10^6$ 但 $<9.8\times 10^6$ 时，获得 **AA** 评级；
  - 游玩分数 $\geq 9.2\times 10^6$ 但 $<9.5\times 10^6$ 时，获得 **A** 评级；
  - 游玩分数 $\geq 8.9\times 10^6$ 但 $<9.2\times 10^6$ 时，获得 **B** 评级；
  - 游玩分数 $\geq 8.6\times 10^6$ 但 $<8.9\times 10^6$ 时，获得 **C** 评级；
  - 游玩分数 $<8.6\times 10^6$ 时，获得 **D** 评级。
### 题目思路
- 首先，从上面的第一段中可以得出 $n$ 和总的分数 $num$，代码如下：
```cpp
double num=(p1*(N/n+1))+(p0*(N/n))+(f*(N/n/2));
```
- 接下来按照第二段的判断依据，求得以下代码：
```cpp
if(num>9.9*M) cout<<"EX+";
else if(num>=9.8*M) cout<<"EX";
else if(num>=9.5*M) cout<<"AA";
else if(num>=9.2*M) cout<<"A";
else if(num>=8.9*M) cout<<"B";
else if(num>=8.6*M) cout<<"C";
else cout<<"D";
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11154)

### 解题思路
纯模拟题。首先我们需要理解游戏分数的计算方式。

读入 $p_1,p_0,f,l$ 后，我们先将 $n$ 算出来，也就是 $n=p_1+p_0+f+l$，接着我们令 $t=\frac{10^7}{n}$，这里最好把 $t$ 定义为 double 类型（~~尽管用 int 存也过了~~）。

得到 $n$ 和 $t$ 之后，我们可以计算出 **大 Pure** 的得分为 $t \times (p_1+1)$，**小 Pure** 的得分为 $t \times p_0$，**Far** 的得分为 $\frac{t \times f}{2}$，而 **Lost** 没有得分。

所以最终答案为 $t \times (p_1+1)+t \times p_0+\frac{t \times f}{2}$，注意精度问题。

最后判断一下就完事了。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int p1,p0,f,l,n,ans;
double t,tmp;
int main(){
	cin>>p1>>p0>>f>>l;
	n=p1+p0+f+l,t=1e7/n;
	tmp=p1*t+p1+p0*t+f*t/2.0;
	ans=floor(tmp);
	if(ans>=9900000) cout<<"EX+";
	else if(ans>=9800000) cout<<"EX";
	else if(ans>=9500000) cout<<"AA";
	else if(ans>=9200000) cout<<"A";
	else if(ans>=8900000) cout<<"B";
	else if(ans>=8600000) cout<<"C";
	else cout<<"D";
}
```

---

## 作者：fanjiayu666 (赞：0)

本题题目较复杂，但仔细理解后就不难。

首先输入：
```cpp
cin>>p0>>p1>>f>>l;
```

接着按照题意，计算 $n$ 的值：
```cpp
n=p0+p1+f+l;
```

然后直接计算得分：
```cpp
p0=floor(1e7*1.0/n+1)*p0;//获得基本分和一分附加分。
p1=floor(1e7*1.0/n)*p1;//获得基本分。
f=floor(1e7*1.0/n/2);//获得基本分的一半。
l=0;//不获得分。
//为减少使用变量，此处使用自赋值。
```

最后判断等级：
```cpp
int ans=p0+p1+l+f;//计算总和。
if(ans>=9.9*1e6)cout<<"EX+\n";
else if(ans>=9.8*1e6)cout<<"EX\n";
else if(ans>=9.5*1e6)cout<<"AA\n";
else if(ans>=9.2*1e6)cout<<"A\n";
else if(ans>=8.9*1e6)cout<<"B\n";
else if(ans>=8.6*1e6)cout<<"C\n";
else cout<<"D\n";//输出等级。
```
所以最后得到代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int p0,p1,l,f,n;
int main(){
    cin>>p0>>p1>>f>>l;
    n=p0+p1+f+l;
    p0=floor(1e7*1.0/n+1)*p0;
    p1=floor(1e7*1.0/n)*p1;
    f=floor(1e7*1.0/n/2)*f;
    l=0;
    int ans=p0+p1+l+f;
    if(ans>=9.9*1e6)cout<<"EX+\n";
    else if(ans>=9.8*1e6)cout<<"EX\n";
    else if(ans>=9.5*1e6)cout<<"AA\n";
    else if(ans>=9.2*1e6)cout<<"A\n";
    else if(ans>=8.9*1e6)cout<<"B\n";
    else if(ans>=8.6*1e6)cout<<"C\n";
    else cout<<"D\n";
    return 0;
}
```

---

## 作者：AFO_Lzx (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P11154)

### $\texttt{Description}$

按照题目要求算出玩家的分数，并评级。评级规则见题面。

### $\texttt{Solution}$

这题就是个简单的 $\texttt{if}$ 判断，只需要计算出大 $\texttt{Pure}$ 和小 $\texttt{Pure}$ 还有 $\texttt{Far}$ 的分数总和，按照题目的要求评级即可，详见代码。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
	int p1, p0, f, l;
	cin >> p1 >> p0 >> f >> l;
	int n = p1 + p0 + f + l;
	int sc = 10000000 * 1ll / n;
	int sc1 = 0;
	
	sc1 += p1 * (sc + 1); // 大 Pure
	sc1 += p0 * sc; // 小 Pure    
	sc1 += f * (sc / 2); // Far

	if (sc1 >= 9900000) {
		cout << "EX+" << endl;
	} else if (sc1 >= 9800000) {
		cout << "EX" << endl;
	} else if (sc1 >= 9500000) {
		cout << "AA" << endl;
	} else if (sc1 >= 9200000) {
		cout << "A" << endl;
	} else if (sc1 >= 8900000) {
		cout << "B" << endl;
	} else if (sc1 >= 8600000) {
		cout << "C" << endl;
	} else {
		cout << "D" << endl;
	}
    // 评级
	
	return 0;
}
```

完结。

---

## 作者：Aron_2023 (赞：0)

本题乍一看特别复杂，实际上很简单。

前置知识：常量、变量与条件语句分支结构。

题目描述很多，看到关键点：基本分、附加分、向下取整。我们可以知道，题目要求我们计算一次游玩的总分数，并给出评级，可以想到使用条件语句完成。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int ben=1e7;//n个物件的基本分 
const double pin=1e6;//评级 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//加速cin cout速度 
	int p1,p0,f,l;
	cin>>p1>>p0>>f>>l;//依照题意输入 
	double sum=0;//建立1个sum计算总分
	int n=p1+p0+f+l;
	sum+=p1*(ben/n+1);//依次计算每个 
	sum+=p0*(ben/n);
	sum+=f*(ben/n/2); 
	if(sum>=pin*9.9) cout<<"EX+"; //依次判断每个评级标准 
	else if(sum<pin*9.9&&sum>=9.8*pin) cout<<"EX";
	else if(sum<pin*9.8&&sum>=9.5*pin) cout<<"AA";
	else if(sum<pin*9.5&&sum>=9.2*pin) cout<<"A";
	else if(sum<pin*9.2&&sum>=8.9*pin) cout<<"B";
	else if(sum<pin*8.9&&sum>=8.6*pin) cout<<"C";
	else cout<<"D";
	return 0;
}

```

---

