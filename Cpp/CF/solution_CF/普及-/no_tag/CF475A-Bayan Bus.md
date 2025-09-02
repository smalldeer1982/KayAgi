# Bayan Bus

## 题目描述

The final round of Bayan Programming Contest will be held in Tehran, and the participants will be carried around with a yellow bus. The bus has 34 passenger seats: 4 seats in the last row and 3 seats in remaining rows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475A/8bce19353e5f54c2dfc8345d92904e1c0260a14e.png)The event coordinator has a list of $ k $ participants who should be picked up at the airport. When a participant gets on the bus, he will sit in the last row with an empty seat. If there is more than one empty seat in that row, he will take the leftmost one.

In order to keep track of the people who are on the bus, the event coordinator needs a figure showing which seats are going to be taken by $ k $ participants. Your task is to draw the figure representing occupied seats.

## 样例 #1

### 输入

```
9
```

### 输出

```
+------------------------+
|O.O.O.#.#.#.#.#.#.#.#.|D|)
|O.O.O.#.#.#.#.#.#.#.#.|.|
|O.......................|
|O.O.#.#.#.#.#.#.#.#.#.|.|)
+------------------------+
```

## 样例 #2

### 输入

```
20
```

### 输出

```
+------------------------+
|O.O.O.O.O.O.O.#.#.#.#.|D|)
|O.O.O.O.O.O.#.#.#.#.#.|.|
|O.......................|
|O.O.O.O.O.O.#.#.#.#.#.|.|)
+------------------------+
```

# 题解

## 作者：BCZSX (赞：7)

~~这题绝对恶意评分~~

~~暴力出奇迹，骗分过样例，打表出省一~~

~~代码千万条，暴力第一条~~

~~所以说我这题是打表的~~

~~打表大法好呀！！！~~
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int k,a,b,c;

int main()
{
    scanf("%d", &k);
    printf("+------------------------+\n");
	if (k == 0) printf("|#.#.#.#.#.#.#.#.#.#.#.|D|)\n|#.#.#.#.#.#.#.#.#.#.#.|.|\n|#.......................|\n|#.#.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 1) printf("|O.#.#.#.#.#.#.#.#.#.#.|D|)\n|#.#.#.#.#.#.#.#.#.#.#.|.|\n|#.......................|\n|#.#.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 2) printf("|O.#.#.#.#.#.#.#.#.#.#.|D|)\n|O.#.#.#.#.#.#.#.#.#.#.|.|\n|#.......................|\n|#.#.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 3) printf("|O.#.#.#.#.#.#.#.#.#.#.|D|)\n|O.#.#.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|#.#.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 4) printf("|O.#.#.#.#.#.#.#.#.#.#.|D|)\n|O.#.#.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.#.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 5) printf("|O.O.#.#.#.#.#.#.#.#.#.|D|)\n|O.#.#.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.#.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 6) printf("|O.O.#.#.#.#.#.#.#.#.#.|D|)\n|O.O.#.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.#.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 7) printf("|O.O.#.#.#.#.#.#.#.#.#.|D|)\n|O.O.#.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 8) printf("|O.O.O.#.#.#.#.#.#.#.#.|D|)\n|O.O.#.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 9) printf("|O.O.O.#.#.#.#.#.#.#.#.|D|)\n|O.O.O.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.#.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 10) printf("|O.O.O.#.#.#.#.#.#.#.#.|D|)\n|O.O.O.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 11) printf("|O.O.O.O.#.#.#.#.#.#.#.|D|)\n|O.O.O.#.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 12) printf("|O.O.O.O.#.#.#.#.#.#.#.|D|)\n|O.O.O.O.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.#.#.#.#.#.#.#.#.|.|)\n");
    if (k == 13) printf("|O.O.O.O.#.#.#.#.#.#.#.|D|)\n|O.O.O.O.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.#.#.#.#.#.#.#.|.|)\n");
    if (k == 14) printf("|O.O.O.O.O.#.#.#.#.#.#.|D|)\n|O.O.O.O.#.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.#.#.#.#.#.#.#.|.|)\n");
    if (k == 15) printf("|O.O.O.O.O.#.#.#.#.#.#.|D|)\n|O.O.O.O.O.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.#.#.#.#.#.#.#.|.|)\n");
    if (k == 16) printf("|O.O.O.O.O.#.#.#.#.#.#.|D|)\n|O.O.O.O.O.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.#.#.#.#.#.#.|.|)\n");
    if (k == 17) printf("|O.O.O.O.O.O.#.#.#.#.#.|D|)\n|O.O.O.O.O.#.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.#.#.#.#.#.#.|.|)\n");
    if (k == 18) printf("|O.O.O.O.O.O.#.#.#.#.#.|D|)\n|O.O.O.O.O.O.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.#.#.#.#.#.#.|.|)\n");
    if (k == 19) printf("|O.O.O.O.O.O.#.#.#.#.#.|D|)\n|O.O.O.O.O.O.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.#.#.#.#.#.|.|)\n");
    if (k == 20) printf("|O.O.O.O.O.O.O.#.#.#.#.|D|)\n|O.O.O.O.O.O.#.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.#.#.#.#.#.|.|)\n");
    if (k == 21) printf("|O.O.O.O.O.O.O.#.#.#.#.|D|)\n|O.O.O.O.O.O.O.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.#.#.#.#.#.|.|)\n");
    if (k == 22) printf("|O.O.O.O.O.O.O.#.#.#.#.|D|)\n|O.O.O.O.O.O.O.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.#.#.#.#.|.|)\n");
    if (k == 23) printf("|O.O.O.O.O.O.O.O.#.#.#.|D|)\n|O.O.O.O.O.O.O.#.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.#.#.#.#.|.|)\n");
    if (k == 24) printf("|O.O.O.O.O.O.O.O.#.#.#.|D|)\n|O.O.O.O.O.O.O.O.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.#.#.#.#.|.|)\n");
    if (k == 25) printf("|O.O.O.O.O.O.O.O.#.#.#.|D|)\n|O.O.O.O.O.O.O.O.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.#.#.#.|.|)\n");
    if (k == 26) printf("|O.O.O.O.O.O.O.O.O.#.#.|D|)\n|O.O.O.O.O.O.O.O.#.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.#.#.#.|.|)\n");
    if (k == 27) printf("|O.O.O.O.O.O.O.O.O.#.#.|D|)\n|O.O.O.O.O.O.O.O.O.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.#.#.#.|.|)\n");
    if (k == 28) printf("|O.O.O.O.O.O.O.O.O.#.#.|D|)\n|O.O.O.O.O.O.O.O.O.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.O.#.#.|.|)\n");
    if (k == 29) printf("|O.O.O.O.O.O.O.O.O.O.#.|D|)\n|O.O.O.O.O.O.O.O.O.#.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.O.#.#.|.|)\n");
    if (k == 30) printf("|O.O.O.O.O.O.O.O.O.O.#.|D|)\n|O.O.O.O.O.O.O.O.O.O.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.O.#.#.|.|)\n");
    if (k == 31) printf("|O.O.O.O.O.O.O.O.O.O.#.|D|)\n|O.O.O.O.O.O.O.O.O.O.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.O.O.#.|.|)\n");
    if (k == 32) printf("|O.O.O.O.O.O.O.O.O.O.O.|D|)\n|O.O.O.O.O.O.O.O.O.O.#.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.O.O.#.|.|)\n");
    if (k == 33) printf("|O.O.O.O.O.O.O.O.O.O.O.|D|)\n|O.O.O.O.O.O.O.O.O.O.O.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.O.O.#.|.|)\n");
    if (k == 34) printf("|O.O.O.O.O.O.O.O.O.O.O.|D|)\n|O.O.O.O.O.O.O.O.O.O.O.|.|\n|O.......................|\n|O.O.O.O.O.O.O.O.O.O.O.|.|)\n");
    printf("+------------------------+");
    return 0;

}
```
~~请求管理员过审，我这题打了好久的呀！！！~~

---

## 作者：梦里调音 (赞：3)

~~代码复杂度极高！~~

# 前方高能特判预警！！！

我是用bool记录每个座位是否有人来着。

```
#include <iostream>
using namespace std;
int f[51][51];
int main(){
	int n,y,x;
    //人数、最后一列人数(有人但未坐满）、坐了人的列数
	cin>>n;
	if(n>=3)f[3][2]=1;//那个最特别的位置
	if(n<4)y=n,x=1;//特判<4的情况
	else {
		n-=4;
		x=n/3+2;
		y=n%3;
	}
//	cout<<n<<endl;
//	cout<<x<<endl<<y<<endl;
	for(int i=1;i<=4;i++)
		for(int j=1;j<x;j++){//中间部分标记，1有人，0没人
			if(i==3)break;
			f[i][2*j]=1;
		}
	for(int i=1;i<=y;i++)f[i][x*2]=1;//有人但未坐满的最后一列
	cout<<"+------------------------+\n";
	for(int i=1;i<=4;i++){
		for(int j=1;j<=26;j++){
			if(i==1&&j==25)cout<<"D";//司机
			else if(i==2&&j==25)cout<<".";//
			else if(i==4&&j==25)cout<<".";//几个特殊的点
			else if(i==3&&j==24)cout<<".";//
			else if(j==1||j==24||j==26)cout<<"|";//
			else if(j%2==1&&j<=23)cout<<".";//列数为奇数的基本上是“.”
			else{//座位
				if(i==3&&j!=2)cout<<".";//特殊位子
				else if(f[i][j]==1)cout<<"O";
				else cout<<"#";
			}
		}
		if(i==1||i==4)cout<<")";//车灯（应该是吧）
		cout<<endl;
	}
	cout<<"+------------------------+\n";
}
```


---

## 作者：Ciyang (赞：2)

### 题目略水，评分虚高。

放一个既简单又省事的思路，首先copy一下样例，然后改为以下的样式。
```
char bus[][28]= {
"+------------------------+ ",
"|#.#.#.#.#.#.#.#.#.#.#.|D|)",
"|#.#.#.#.#.#.#.#.#.#.#.|.| ",
"|#.......................| ",
"|#.#.#.#.#.#.#.#.#.#.#.|.|)",
"+------------------------+ "};
```
某些行多空了一格只是为了对齐。然后我们先读入 N ， 循环从左到右，从上到下搜索 # 字符，将先搜索到 N 个 # 都换成 O 。

代码注释较少，但基本看看就能懂。

代码:

```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
int n;
char bus[][28]= {"+------------------------+ ", "|#.#.#.#.#.#.#.#.#.#.#.|D|)", "|#.#.#.#.#.#.#.#.#.#.#.|.| ", "|#.......................| ", "|#.#.#.#.#.#.#.#.#.#.#.|.|)", "+------------------------+ "};
// 初始状态
int main() {
//主程序
	cin >> n;
	for(int i= 0; i < 28; i++)
		for(int j= 0; j < 6; j++)
			if(bus[j][i] == '#' && n) --n, bus[j][i]= 'O';
   // 找到#字符并且 N 不为 0 就替换成 O 
	for(int i= 0; i < 6; i++) {
		for(int j= 0; j < 27; j++)
			if(bus[i][j] != ' ') putchar(bus[i][j]);
		if(i != 5) putchar('\n');
	}
   // 输出，最后一行换不换行都行
	return 0;
}
```


---

## 作者：CobaltChloride (赞：1)

```
//模拟水题
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,i;
int main(){
	cin>>n;
	cout<<"+------------------------+"<<endl;//车的左侧
	if(n>=3){
		n-=1;//此时第三栏的座位必有人,为处理方便先-1
		cout<<'|';//后部
		for(i=1;i<=11;i++){
			if((n+2)/3>=i) cout<<"O.";//有人
			else cout<<"#.";//没人
		}
		cout<<"|D|)"<<endl;//司机
		cout<<'|';
		for(i=1;i<=11;i++){
			if((n+1)/3>=i) cout<<"O.";
			else cout<<"#.";
		}
		cout<<"|.|"<<endl;
		cout<<"|O.......................|"<<endl;//第三栏
		cout<<'|';
		for(i=1;i<=11;i++){
			if(n/3>=i) cout<<"O.";
			else cout<<"#.";
		}
		cout<<"|.|)"<<endl;
	}
	else{//此时第三栏的座位必无人
		cout<<'|';
		if(n>=1) cout<<"O.";//有1人
		else cout<<"#.";
		cout<<"#.#.#.#.#.#.#.#.#.#.|D|)"<<endl;
		cout<<'|';
		if(n>=2) cout<<"O.";//有两人
		else cout<<"#.";
		cout<<"#.#.#.#.#.#.#.#.#.#.|.|"<<endl;
		cout<<"|#.......................|"<<endl;
		cout<<"|#.#.#.#.#.#.#.#.#.#.#.|.|)"<<endl;
	}
	cout<<"+------------------------+"<<endl;//车的右侧
    return 0;
}
```

---

## 作者：little_cindy (赞：0)

建议降红。
## 思路
我的思路非常简单，比前面的稍微简单一些。
我们可一把一个车分开。
### 车身

```
+------------------------+
|                      |D|)
|                      |.|
|  ......................|
|                      |.|)
+------------------------+
```

这部分直接输出就好了

### 座位

分为两种：
1. 有人：```O.```
1. 没人：```#.```

位置编号分布：

|列|1|2|3|4|5|6|7|8|9|10|11|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|**1**|$1$|$5$|$8$|$11$|$14$|$17$|$20$|$23$|$26$|$29$|$32$|
|**2**|$2$|$6$|$9$|$12$|$15$|$18$|$21$|$24$|$27$|$30$|$33$|
|**3**|$3$|走廊|走廊|走廊|走廊|走廊|走廊|走廊|走廊|走廊|走廊|
|**4**|$4$|$7$|$10$|$13$|$16$|$19$|$22$|$25$|$28$|$31$|$34$|

我们只要检查位置编号是否大于个数，是，输出```#.```；否则，输出```O.```。

#### 代码实现

```cpp
void O(int a) {
	if (n >= a) {
		cout << "O.";
	} else {
		cout << "#.";
	}
	return;
}
```

## code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define inl inline
#define Ofast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
int n;

void O(int a) {
	if (n >= a) {
		cout << "O.";		
	} else {
		cout << "#.";
	}
	return;
}

int main() {
	cin >> n;
	cout << "+------------------------+\n|";
	O(1);
	for (int i = 5; i <= 32; i += 3) {
		O(i);
	}
	cout << "|D|)\n|";
	O(2);
	for (int i = 6; i <= 33; i += 3) {
		O(i);
	}
	cout << "|.|\n|";
	O(3);
	cout << "......................|\n|";
	for (int i = 4; i <= 34; i += 3) {
		O(i);
	}
	cout << "|.|)\n+------------------------+";
	return 0;
}
```

---

## 作者：yf最qhhh (赞：0)

~~我在这里先 % 一波那个打表的大佬~~

这道题用不着打表啊，可以模拟

首先我们把公交车的样子复制过来
```cpp
char s[10][30]={//字符串最后一位是\0，把位置空出来。
"+------------------------+ ",
"|#.#.#.#.#.#.#.#.#.#.#.|D|)",
"|#.#.#.#.#.#.#.#.#.#.#.|.| ",
"|#.......................| ",
"|#.#.#.#.#.#.#.#.#.#.#.|.|)",
"+------------------------+ ",
};
```
然后就可以直接模拟了。
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rll register long long
using namespace std;
char s[6][28]={
"+------------------------+ ",
"|#.#.#.#.#.#.#.#.#.#.#.|D|)",
"|#.#.#.#.#.#.#.#.#.#.#.|.| ",
"|#.......................| ",
"|#.#.#.#.#.#.#.#.#.#.#.|.|)",
"+------------------------+ ",
};
int main(){
	rll n,i=1,j=1,k,l;
	scanf("%lld",&n);
	for(k=1;k<=n;++k){
		if(j==1){//特别判断一下最后一排
			if(i==5)i=1,j+=2;
			s[i][j]='O';
			i++;
		}
		else{
			if(i==3){//不是最后一排的话需要特别判断一下过道
				s[++i][j]='O';
				i=1,j+=2;
			}
			else s[i++][j]='O';
		}
	}
	for(l=0;l<=5;l++){
		cout<<s[l]<<endl;
	}
	return 0;
}

```
~~挑战最短代码，我还有机会吗。~~

---

## 作者：Eason_AC (赞：0)

## Update
- $\texttt{2020.10.6}$ 修改了一些笔误。

## Content
模拟一个核载 $34$ 人的巴士上有 $k$ 个人时的巴士的状态。

每个人都会优先选择有空位的最后一排最左侧一个空位入座。

**数据范围：$0\leqslant k\leqslant 34$。**
## Solution
有 $6$ 行，所以按 $6$ 行来分类讨论。
### Part 1 第一行
第一行只需要输出一串字符串就行了，不需要多讲。

由于第六行输出的东西和第一行一模一样，故之后不做详细讲解。
### Part 2 第二行
第二行开始一直到第五行都需要考虑到车上的人的情况。我们先来看这一行。

首先得要考虑最后一排的情况（因为最后一排有 $4$ 个人）。

- 如果 $k=0$，那么最后一排上的这一列不坐人。
- 否则，这里肯定会坐人。

然后，还有坐在这一列的人数 $p_2=\left\lceil\dfrac{\max\{0,k-4\}}{3}\right\rceil$，没坐在这一列的人数则是 $10-p_2$。这个可以自己去推算。
### Part 3 第三行
首先还是考虑最后一排的情况。

- 如果 $k<2$，那么这里不坐人。
- 否则，这里肯定坐人。

然后，还有坐在这一列的人数 $p_3=\left\lceil\dfrac{\max\{0,k-5\}}{3}\right\rceil$，没坐在这一列的人数则是 $10-p_3$。

由于第五行与第二、三行的情况类似，故之后不做详细讲解。
### Part 4 第四行
首先还是考虑最后一排的情况。

- 如果 $k<3$，那么这里不坐人。
- 否则，这里肯定坐人。

然后这里就是过道了，直接输出 ``.``（经检验总共有 $22$ 个）。

其他的不做多讲。

注意，除了我讲的东西要输出外，每一行后面可能还会有一些多余的东西，它们也要输出。
## Code
```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
	int k;
	scanf("%d", &k);
	printf("+------------------------+\n|");
	if(!k)	printf("#.");
	else	printf("O.");
	for(int i = 1; i <= (int)ceil(max(0, k - 4) / 3.0); ++i)	printf("O.");
	for(int i = 1; i <= 10 - (int)ceil(max(0, k - 4) / 3.0); ++i)	printf("#.");
	printf("|D|)\n|");
	if(k < 2)	printf("#.");
	else	printf("O.");
	for(int i = 1; i <= (int)ceil(max(0, k - 5) / 3.0); ++i)	printf("O.");
	for(int i = 1; i <= 10 - (int)ceil(max(0, k - 5) / 3.0); ++i)	printf("#.");
	printf("|.|\n|");
	if(k < 3)	printf("#.");
	else	printf("O.");
	for(int i = 1; i <= 22; ++i)	printf(".");
	printf("|\n|");	
	if(k < 4)	printf("#.");
	else	printf("O.");
	for(int i = 1; i <= (int)ceil(max(0, k - 6) / 3.0); ++i)	printf("O.");
	for(int i = 1; i <= 10 - (int)ceil(max(0, k - 6) / 3.0); ++i)	printf("#.");
	printf("|.|)\n+------------------------+");
}
```

---

## 作者：智子·起源 (赞：0)

### 我说你们水题归水题，题解也要认真写啊。。。（逃~~

-----

首先，我用一个2维数组把每一个位置有没有人记录下来。

下面是我存数的方式（以样例2为例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/h36k3syo.png)

接着按位置将小车车生成即可。

### code（红蝶在此，抄袭可耻）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y=1,f[100][100];
int main()
{
  scanf("%d",&n);
  while(n--)
  {
    x++;
    if(y==1&&x>4)y++,x=1;
    if(y>1&&x>3)x=1,y++;
    f[x][y]=1;
  }//记录位置
  
  cout<<"+------------------------+";
    
  cout<<endl<<'|';
  for(int i=1;i<=11;i++)
  {
    if(f[1][i])cout<<'O';
    else cout<<'#';
    cout<<'.';
  }
  cout<<"|D|)"<<endl;
  
  cout<<'|';
  for(int i=1;i<=11;i++)
  {
    if(f[2][i])cout<<'O';
    else cout<<'#';
    cout<<'.';
  }
  cout<<"|.|"<<endl;
  
  cout<<'|';
  if(f[3][1])cout<<'O';
  else cout<<'#';
  cout<<".......................|"<<endl;
  
  cout<<'|';
  for(int i=1;i<=11;i++)
  {
  	if(i==1)
  	{
  	  if(f[4][i])cout<<'O';
      else cout<<'#';
      cout<<'.';
      continue;
  	}
    if(f[3][i])cout<<'O';
    else cout<<'#';
    cout<<'.';
  }
  cout<<"|.|)"<<endl<<"+------------------------+"<<endl;//模拟（恐怖）
  return 0;
}

```


---

## 作者：yuangq (赞：0)

这道题直接模拟即可，详情请见题解注释

~~~
#include<bits/stdc++.h>
#define MAXN 10005
#define LL long long
using namespace std;
//int a[MAXN];
int a[12];
int pic[100][100];
void printall()
{
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=27;j++)
		{
			if(pic[i][j]==1)//   +
				cout<<"+";
			if(pic[i][j]==2)//   -
				cout<<"-";
			if(pic[i][j]==3)//   |
				cout<<"|";
			if(pic[i][j]==4)//   O
				cout<<"O";
			if(pic[i][j]==5)//   .
				cout<<".";
			if(pic[i][j]==6)//   #
				cout<<"#";
			if(pic[i][j]==7)//   )
				cout<<")";
			if(pic[i][j]==8)//   D
				cout<<"D";
		}
		cout<<endl;
	}
}
int main()
{
	//freopen("train.in","r",stdin);
	//freopen("train.out","w",stdout);
	int n;
	cin>>n;
	if(n>=1)
	{
		n--;
		a[1]++;
	}
	int ii=1;
	while(n>0)
	{
		if(n<=3)
		{
			a[ii]+=n;
			n=0;
		}
		else
		{
			a[ii]+=3;
			n-=3;
			ii++;
		}
	}//计算每列有多少人 
	pic[1][1]=pic[1][26]=pic[6][1]=pic[6][26]=1;
	for(int i=2;i<=25;i++)
	{
		pic[1][i]=pic[6][i]=2;
	}
	for(int i=2;i<=5;i++)
	{
		pic[i][1]=pic[i][26]=3;
	}
	//画巴士的边框 
	pic[2][27]=pic[5][27]=7;
	for(int i=3;i<=25;i+=2)
	{
		for(int j=2;j<=5;j++)
		{
			pic[j][i]=5;
			if(j==2 && i==25)
			{
				pic[j][i]=8; 
			} 
		}
	}
	for(int i=3;i<=25;i++)
	{
		pic[4][i]=5;
	}
	//画巴士中座位间隔，走廊及司机 
	pic[2][24]=pic[3][24]=pic[5][24]=3;
	if(a[1]==4)
	{
		pic[2][2]=pic[3][2]=pic[5][2]=pic[4][2]=4;
	}
	if(a[1]==0)
	{
		pic[2][2]=pic[3][2]=pic[5][2]=pic[4][2]=6;
	} 
	if(a[1]==3)
	{
		pic[2][2]=pic[3][2]=pic[4][2]=4;
		pic[5][2]=6;
	} 
	if(a[1]==2)
	{
		pic[2][2]=pic[3][2]=4;
		pic[5][2]=pic[4][2]=6;
	} 
	if(a[1]==1)
	{
		pic[2][2]=4;
		pic[5][2]=pic[4][2]=pic[3][2]=6;
	}
	for(int i=2;i<=11;i++)
	{
		if(a[i]==3)
		{
			pic[2][i*2]=pic[3][i*2]=pic[5][i*2]=4;
		}
		if(a[i]==0)
		{
			pic[2][i*2]=pic[3][i*2]=pic[5][i*2]=6;
		}
		if(a[i]==1)
		{
			pic[2][i*2]=4;
			pic[3][i*2]=pic[5][i*2]=6;
		}
		if(a[i]==2)
		{
			pic[2][i*2]=pic[3][i*2]=4;
			pic[5][i*2]=6;
		}
	}
	//画座位 
	printall();//输出 
	return 0;
}
~~~

---

