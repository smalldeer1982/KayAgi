# Diamond A&B(1)

## 题目背景

由于本题较难，将本题拆做两题，分别为 diamond A 以及 diamond B。本题为 Diamond A。



## 题目描述

教主上电视了！这个消息绝对是一个爆炸性的新闻。一经传开，大街上瞬间就没人了（都回家看电视去了），商店打烊，工厂停业。大家都把电视机的音量开到最大，教主的声音回响在大街小巷。

小 L 给小 X 慌乱地打开自己家的电视机，发现所有频道都播放的是教主的采访节目（-\_-bbb）。只见电视屏幕上的教主笑意吟吟，给大家出了一道难题：

一个边长为 $n$ 的大菱形被均匀地划分成了 $n\times n$ 个边长为 $1$ 的小菱形组成的网格，但是网格中部分边被抹去了，小 $L$ 想知道，大菱形内有多少个平行四边形，这些平行四边形内不存在边（平行四边形内是空的）。

教主说，如果谁写出了程序，移动用户请将程序发送到 xxxx，联通用户请将程序发送到 xxxx……如果答对这个题，将有机会参加抽奖，大奖将是教主签名的 Orz 教主 T-Shirt 一件！这个奖品太具有诱惑力了。于是你需要编一个程序完成这么一道题。


## 说明/提示

### 数据范围及约定

- 对于 $20\%$ 的数据，$n \le 10$；
- 对于 $40\%$ 的数据，$n \le 60$；
- 对于 $60\%$ 的数据，$n \le 200$；
- 对于 $100\%$ 的数据，$n \le 888$。

## 样例 #1

### 输入

```
4
   /\   
  /\/\  
 /\  /\ 
/  \/  \
\/\/ / /
 \/\  / 
  \ \/  
   \/   
```

### 输出

```
4
1111
11101
1000
10111
1100
10101
0111
11101
1111
```

# 题解

## 作者：kkxacj (赞：12)

#### [P1740 题目传送门](https://www.luogu.com.cn/problem/P1740)
#### 题意
先输出输入的 $n$。

再将原题中的输入菱形改为矩形输出。

用 $1$ 表示有边，$0$ 表示无边。

#### 思路
读题可知，棱形会从右上到左下的顺序变为矩阵，可先找起点的坐标，然后往右下打印，其中，输出奇数边时有 $n$ 条边，偶数时有 $n-1$ 条边。棱形有 $2n+1$ 行，我们可以开一个大小为 $2n+1$ 的字符串。

#### 注意：本题菱形里可能有空格

所以记得用
```c
getline(cin,s[i]);
```
根据样例，起点的 $x$ 坐标只会为每一行的第 $1,2$ 条边，$y$ 坐标隔两次加 $1$，得出 

$x=1+(i+1)/2$

$y=n-i/2$

code
```c
#include<bits/stdc++.h>
using namespace std;
int n,m,o,x,y;
string s[1900];
int main()
{
	scanf("%d",&n); //cin >> n;
	printf("%d\n",n); //cout << n << endl; 
	m = 2 * n + 1;
	while(m--) getline(cin,s[++o]);//o++,getline(cin,s[o]);
	for(int i = 1;i <= 2 * n + 1;i++)
	{
		m = n,x = 1 + (i + 1) / 2,y = n - i / 2;
		if(i % 2 == 0) m++;
		while(m--)
		{
			if(s[x++][y++] == ' ') printf("0"); //如果是空格,x++和y++可以写在后面
			else printf("1");
		}
		cout << endl; //换行，别忘了
	}
	return 0;
}

```


---

## 作者：引领天下 (赞：11)

这题有毒。。。

貌似就我一个是用C++写过的……

楼下已经说过题目什么意思，我这里就来说一下怎么实现

具体请看代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string a[1777];
int main(void){
    cin>>n;
    cout<<n<<endl;
    for (int i=0;i<=n*2;i++){
    	string s;
    	getline(cin,s);
        a[i]=" ";
        a[i]+=s;
    }//由于string读入时自动0下标，所以我要强制转成1下标
    for (int i=1;i<=2*n+1;i++,puts("")){
        int ps=n+!(i&1),o=1+(i-1)/2,p=n+1-i/2;//ps是输出个数，o是起始行，p是起始列
        for (int j=1;j<=ps;j++)putchar(a[o++][p++]==' '?'0':'1');//模拟过去
    }
}
```

---

## 作者：BFSBFSBFSBFS (赞：9)

~~冷静冷静..~~

题意:输出1个菱形..

观察样例..可以发现是.将菱形向左旋.至左下边平行后.从上往下输出..

样例旋转..大概..这样子吧..

```cpp
 1 2 3 4
 - - - -
| | |   |
 -      
|   | | |
 - -    
|   |   |
   - - -
| | |   |
 - - - -
```
每行输出的数量:**n**(单行.)或者**n+1**(双行.).

第**i**行起始位置:**(i-1)/2+1**行.**(n+1)-i/2**列.

随后行列不断**+1**.就能成功遍历菱形**1**行了.

Diu代码..

```cpp
program P1740;
 var
  s:array[0..1777] of ansistring;
  i,j,n,o,p,ps:longint;
 begin
  readln(n);
  writeln(n);
  for i:=1 to 2*n do
   readln(s[i]);
  for i:=1 to 2*n+1 do
   begin
    if i mod 2=1 then ps:=n      //表示要输出的边数..
                 else ps:=n+1;
    o:=1+(i-1)>>1;               //起始行列.
    p:=n+1-i>>1;
    for j:=1 to ps do
     begin
      if s[o,p]<>' ' then write('1')
                     else write('0');
      inc(o);
      inc(p);
     end;
    writeln;
   end;
 end.
```
(ಡωಡ).


---

## 作者：FwbAway (赞：3)

题目意思：输入一个菱形，输出一个“菱形”。

不同点在于输入是用“/\”组成的，输出是 1 和 0 组成的。

题目有几个大测试点，请开够数组。

先向左旋转，$i$ 和 $j$ 的改变，和数组没有什么关系。

然后平移，这个动不动都行，测试点的问题。

最后输出，从上往下，最后别忘了打换行。

代码略。

---

## 作者：RatingStar (赞：2)

~~我天......这题目说实话没看懂~~

题目大意：

输入一个菱形，输出一个矩形。
为什么说是矩形呢？
请看，这是个菱形：
```cpp
   /\
  /\/\
 /\/\/\
/\/\/\/\
\/\/\/\/
 \/\/\/
  \/\/
   \/

```
现在把你的头往右转，让菱形**左下方的边**贴紧底面。

它就是一个矩形。

于是我们发现，他其实就是一个矩形，**整体移过来之后从上往下输出**就好了。

需要注意的几个点：
1. 不要把原本简单的思维题想复杂了，导致 $10$ 分， $20$   分之类的。着手一道题，先看他的算法，再看思维，实在不行再暴力骗分。

2. 对于字符串，不能直接格式输入输出或者流输入输出，因为这样读不到空格！遇到第一个空格就会停止输入。建议使用以下读入一行的办法：
```cpp
#include<cstdio>
char a[10005]; 
using namespace std;
int main()
{
	gets(a);//第一种办法
	int n;
	while(scanf("%c",&a[++n])!='\n');
	//第二种方法，同时n为字符长度
	while((a[++n]=getchar())!='\n');
	//第三种方法，同时n为字符长度
}
```


3. 要有空间思维，实在不行画个图，对应每一个字符。

4. 注意细节。

代码（有注释，看不懂上文看代码）：

**杜 绝 抄 袭！**
```cpp
#include<cstdio>
char a[2005][2005];
int n,x,y,s;
int main()
{		
	scanf("%d",&n);
	for(int i=0;i<=2*n;i++)
		gets(a[i]);
	printf("%d\n",n); 
	for(int i=0;i<=2*n;i++)
	{
		x=1+i/2; 
		y=n-(i+1)/2;//由于每一行的起始字符都是从左上到右下不转方向判定的，所以定起点为左上角
		if(i%2)s=n+1;
		else s=n;
		/*
			s表示转成矩形之后此行一共有s个字符，如为单行 
			则有n+1个字符（全横），否则为n个（全竖） 
		*/ 
		while(s--)//当还有字符 
		{
			if(a[x][y]==' ')printf("0");
			else printf("1");
			x++;y++;//由于菱形要往右下转，所以右，下的循环坐标都要加 
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：brealid (赞：2)

先吐槽一句，这道题目抄题解的人真多（提交记录一翻就知道，有的人抄能抄成70pts，10人左右抄题解AC【这里指c++抄 @引领天下 的】）

思路是比较简单的，这里提几个易错点：

1. #2，#9，#10 为大数据点，请开够数组（以C风格的数组为例，需要开1776\*1776的，实际需要再稍微大一些）  
2. 枚举部分注意逻辑，不要想错  
3. 换行符为 ``\r`` 不是 ``\n``  
4. 第一行末尾有多余的空格

坑了我好多提交记录。

放代码：（比较乱？）

等等，几个说明：  
1. readStrtypeC: 以C风格读入数据（其实是getchar）  
   readStrtypeCpp: 以C++风格读入数据
2. 中间一大段被注释掉的代码也能很好地完成算法核心  

```cpp
/*************************************
 * problem:      P1740 Diamond A&B(1).
 * user ID:      63720.
 * user name:    Jomoo.
 * time:         2019-06-22.
 * language:     C++.
 * upload place: Luogu.
*************************************/ 

#include <bits/stdc++.h>
using namespace std;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
    return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}  

int n;

char s[2007][2007];

#define isVal(ch) ((ch) == ' ' || (ch) == '/' || (ch) == '\\')

void readStrtypeC(char *s)
{
    bool isReadSomething = false;
    char t = getchar();
    int pos = 1;
    while (!isReadSomething || isVal(t)) {
        if (isVal(t)) {
            if (!isReadSomething) isReadSomething = true;
            s[pos++] = t;
        }
        t = getchar();
    }
}

void readStrtypeCpp(char *s)
{
    string ha;
    getline(cin, ha);
    // ha = ha;
    strcpy(s + 1, ha.c_str());
}

int main()
{
    cin >> n;
    memset(s, ' ', sizeof(s));
    for (int i = 0; i <= n * 2; i++) {
        // readStrtypeC(s[i]);
        readStrtypeCpp(s[i]);
    }
    // for (int i = 1; i <= n * 2; i++) {
    //     printf("%s\n", s[i] + 1);
    // }
    write(n, 10);
    // for (int x = 1, y = n, i, j; x <= n; x++, y--) {
    //     for (i = x, j = y + 1; i <= x + n - 1; i++, j++) {
    //         putchar(48 | (s[i][j] == '\\'));
    //     }
    //     putchar(10);
    //     for (i = x, j = y; i <= x + n; i++, j++) {
    //         putchar(48 | (s[i][j] == '/'));
    //     }
    //     putchar(10);
    // }
    // for (int i = n + 1, j = 1; i <= n * 2; i++, j++) {
    //     putchar(48 | (s[i][j] == '\\'));
    // }
    for (int i = 1; i <= 2 * n + 1; i++) {
        int cnt = n + !(i & 1);
        int x = (i - 1) / 2 + 1, y = n - i / 2 + 1;
        // printf("cnt = %d, x = %d, y = %d : ", cnt, x, y);
        while (cnt--) putchar(s[x++][y++] != ' ' ? 49 : 48);
        putchar(10);
    }
    return 0;
}

/*
6
     /\     
    /\ \    
   /  \/\   
  / /  \ \  
 /\    /\ \ 
/\/\  / /\/\
\/\/\/\/\/\/
 \/ /\ \/ / 
  \/ /\ \/  
   \/ /\/   
    \ \/    
     \/   
6
111111
1010011
111111
1001111
000010
1101111
000111
1001001
111111
1111111
110001
1111101
111111  
*/

/*
5
    /\    
   /  \   
  / /  \  
 /\    /\ 
/\/\  / /\
\/\/\/\/\/
 \/ /\ \/ 
  \/ /\/  
   \/ /   
    \/       
5
11111
100111
00001
110111
00011
100101
11111
111111
11000
111111
11111  
*/
```

---

