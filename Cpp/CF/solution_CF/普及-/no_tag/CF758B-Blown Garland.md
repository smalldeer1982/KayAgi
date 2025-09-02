# Blown Garland

## 题目描述

Nothing is eternal in the world, Kostya understood it on the 7-th of January when he saw partially dead four-color garland.

Now he has a goal to replace dead light bulbs, however he doesn't know how many light bulbs for each color are required. It is guaranteed that for each of four colors at least one light is working.

It is known that the garland contains light bulbs of four colors: red, blue, yellow and green. The garland is made as follows: if you take any four consecutive light bulbs then there will not be light bulbs with the same color among them. For example, the garland can look like "RYBGRYBGRY", "YBGRYBGRYBG", "BGRYB", but can not look like "BGRYG", "YBGRYBYGR" or "BGYBGY". Letters denote colors: 'R' — red, 'B' — blue, 'Y' — yellow, 'G' — green.

Using the information that for each color at least one light bulb still works count the number of dead light bulbs of each four colors.

## 说明/提示

In the first example there are no dead light bulbs.

In the second example it is obvious that one blue bulb is blown, because it could not be light bulbs of other colors on its place according to the statements.

## 样例 #1

### 输入

```
RYBGRYBGR
```

### 输出

```
0 0 0 0```

## 样例 #2

### 输入

```
!RGYB
```

### 输出

```
0 1 0 0```

## 样例 #3

### 输入

```
!!!!YGRB
```

### 输出

```
1 1 1 1```

## 样例 #4

### 输入

```
!GB!RG!Y!
```

### 输出

```
2 1 1 0```

# 题解

## 作者：x1489631649 (赞：2)

# 题目分析
- 	主要考察字符串。
# 思路
- 	题目中明确指出是任意四朵连续的花不会有相同的颜色，所以**通过观察可以发现颜色是每四个一次循环的**。
# 代码（[AC 记录](https://www.luogu.com.cn/record/117128419)）
	
```
#include<bits/stdc++.h>//万能头文件 。 
using namespace std;
int f[5];//计录。 
char n[1000];//字符数组 。 
int main()
{
   	cin.get(n,1000);// 一种输入方式
   	int l=strlen(n),a,b,c,d;// a , b , c , d 是计录颜色 ， l 是数组长度。 
   	for(int i=0;i<l;i++)//字符数组是从 0 开始的。 
   	{
		if(n[i]=='R')
			a=i%4;// 模 4 是为了下面的输出 。 
		if(n[i]=='B')
			b=i%4;
		if(n[i]=='Y') 
			c=i%4;
	    if(n[i]=='G')
			d=i%4;
		if(n[i]=='!')
			f[i%4]++;
   }
   cout<<f[a]<<" "<<f[b]<<" "<<f[a]<<" "<<f[d]<<" "<<endl;// endl 纯属个人习惯 ， 不加也行。 
}
```


---

## 作者：_byta (赞：2)

要求每个颜色的数量，由于有四种颜色，所以我们设四个指向这四种颜色的指针。

首先我们可以遍历一遍字符串，当查找到一个颜色，他的指针就指向它模 4 意义

下的位置，如果出现未知字符，就在它模 4 意义下的位置加加，最后输出四个指针

所指位置的值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105];
int a[5];
int main()
{
   scanf("%s",s);
   int len = strlen(s);
   int r,b,y,g;
   for(int i=0;i<len;i++)
   {
       if(s[i]=='R') r = i % 4;
       else if(s[i]=='B') b = i % 4;
       else if(s[i]=='Y') y = i % 4;
       else if(s[i]=='G') g = i % 4;
       else a[i%4]++;
   }
   printf("%d %d %d %d\n",a[r],a[b],a[y],a[g]);
}
```




---

## 作者：DiDi123 (赞：1)

# 一、题意
给你一个字符串 $s$，可能包括五种字符（$R,B,Y,G,!$），$!$ 表示这个位置的字符未知，现在给你一些位置的 $RBYG$，要求相邻四个位置字母不同，请你填出原来的字符串，分别输出用了多少个 $R,G,Y,B$。

# 二、分析
对于这道题我们可以先假设 $s$ 的前四项为 $\overline{abcd}$，第5项的字母要与 $b,c,d$ 都不同，所以第5项字母也为 $a$，依此类推，可以得出数列 $s$ 为 $\overline{abcdabcdabcd}\dots$ 四个一循环。

再看题面，发现原题面说四种字母都至少出现一回，那么说明我们能唯一地确定每个位置的字母都是多少，所以我们按下面的方法扫一遍就可以了。

先分组，位置除以 $4$ 余数一样的数一组。我们先从每一组的第一个数开始，每次往后跳 $4$ 个位置，跳到本组下一个。如果发现有一个位置有字母，那么本组所有位置的字母都为那个字母。

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int ans[4];
int trans(char ch) //将字母转换成数字，方便记录答案
{
	if(ch=='R') return 0;
	if(ch=='B') return 1;
	if(ch=='Y') return 2;
	if(ch=='G') return 3;
}
int main()
{
	cin>>s;
	for(int i=0;i<=min(int(s.length()-1),3);i++)
	{
		int cnt=0,opt;
		for(int j=i;j<s.length();j+=4)
		{
			if(s[j]=='!') cnt++; //如果这个位置是空位，那么这个组的能填的字母就+1
			else opt=trans(s[j]);
		}
		ans[opt]+=cnt; //这个组填入cnt个opt字母
	}
	for(int i=0;i<=3;i++)
		cout<<ans[i]<<' ';
}
```


---

## 作者：LegendaryGrandmaster (赞：0)

每四个颜色为一循环，所以花环应按照 $A,B,C,D,A \dots$ 排列（$A,B,C,D$ 表示分别不同的颜色的花）。

所以每种相同颜色的花对 $4$ 取模后的值应当相等。

则记录每种颜色的花出现的位置对 $4$ 取模。

则每当遇到需要修补的地方是某种颜色的花记录的数的四倍时，则这个花的颜色是这种颜色。

所以遇到需要修补的地方时将这个位置对 $4$ 取模累加记录即可。

最终依次输出每种颜色的花的个数即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int R,B,Y,G;
int color[4];
signed main()
{
    string st;
    cin>>st;
    for(int i=0;i<st.size();i++){
    	if(st[i]=='R')R=i%4;
    	else if(st[i]=='B')B=i%4;
    	else if(st[i]=='Y')Y=i%4;
    	else if(st[i]=='G')G=i%4;
    	else color[i%4]++;
    }
    cout<<color[R]<<' '<<color[B]<<' '<<color[Y]<<' '<<color[G];
}
```

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/758/B)|[链接](https://www.luogu.com.cn/problem/CF758B)

仔细阅读题目，我们不难发现，每种花瓣的颜色会有规律地出现。

例如 `RYBGRYBGRY`，其中 `R` 出现在位置 $0$、$4$、$8$ 上，而 `Y` 出现在位置 $1$、$5$、$9$ 上。可以看出，`R` 出现的位置 $\bmod\ 4$ 的结果为 $0$，`Y` 则为 $1$，`B` 为 $2$，`G` 为 $3$。

这是为什么呢？我们先看 `RYBG` 这段花瓣。如果要在后面增加一种花瓣，那应该是什么颜色的呢？如果选 `Y`，后四位变成了 `YBGY`，不行。如果选 `B`，后四位变成了 `YBGB`，也不行。如果选 `G`，后四位变成了 `YBGG`，也不行。所以只能选 `R`，它与第一片花瓣颜色相同，但不会与其同时处于相邻的四片里。

通过这种性质，我们可以通过已给出的花瓣颜色来确定每种颜色所在位置 $\bmod\ 4$ 的值，再通过这个值算出填补 `!` 时各种颜色所需的量。

给出一种使用 map 的做法。

参考代码：

```cpp
#include<bits/stdc++.h>
#define f for(int i=0;i<strlen(s);i++)
using namespace std;
map<char,pair<int,int>>a;
char s[105];
void find_plus(int i)
{
	if(a['R'].first==i)a['R'].second++;
	if(a['B'].first==i)a['B'].second++;
	if(a['Y'].first==i)a['Y'].second++;
	if(a['G'].first==i)a['G'].second++;
}
int main()
{
	scanf("%s",s);
	f
		if(s[i]-'!'&&a[s[i]].first!=-1)
			a[s[i]].first=i%4;
	f
		if(s[i]=='!')
			find_plus(i%4);
	printf("%d %d %d %d",a['R'].second,a['B'].second,a['Y'].second,a['G'].second);
	return 0;
}
```
感谢你的阅读。

---

## 作者：_cpp (赞：0)

### 1. 思路：
由于题目中说字符串 $s$ 中相邻四个字符不可能重复。所以，$s$ 四个一组重复出现。由于 $s$ 中只含有四种字母，那我们可以推断，$s$ 中的每相邻四个字符都是一样的。利用这个特点，我们可以根据已有的字符，推断出这四个字符。然后用这四个字符，去填补 $'!'$ 的部分。

### 2. 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
struct ans{
    int sum;
    char x;
}b[4];
int main()
{
    cin >> a;
    for(int i = 0;i < a.size();i++)
        if(a[i] != '!') b[i % 4].x = a[i];  //根据已有的字符推断4个一组的字符
    for(int i = 0;i < a.size();i += 4){
        for(int j = 0;j < 4;j++){
            if(a[i + j] == '!') b[j].sum++; // 进行填补
        }
    }
    
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){ //由于题目要求按红、黄、蓝、绿进行输出，所以要排序
            if(b[j].x == 'R' && i == 0) cout << b[j].sum << " ";
            if(b[j].x == 'B' && i == 1) cout << b[j].sum << " ";
            if(b[j].x == 'Y' && i == 2) cout << b[j].sum << " ";
            if(b[j].x == 'G' && i == 3) cout << b[j].sum << " ";
        }
            
    }
    return 0;
}
```


---

## 作者：Steve_xh (赞：0)

# 题面

[题目传送门](https://www.luogu.com.cn/problem/CF758B)

**题目大意：**

四种颜色构成的花圈，其中任意四个一组颜色中没有重复颜色。要求补全原花圈所需的各种颜色数量。

# 思路

其实一些比较粗略的思路在前几篇题解里面都讲到了，这里带大家深入一下。

前面一篇指出了这个字符串必须得四个颜色重复构成，为什么？假如我把其中一个颜色往后推一格，那么中间空出来的格子就必须得用别的颜色，但是别的颜色与这个格子的间隔小于四，所以不能“舍人为己”地放颜色。

那么有了这个前提之后，我们就能知道每组中各个位置的颜色都是确定的，并且其他组相同位置的颜色也必须是一样的。我们可以设置四个动态下标和一个答案数组，其中四个下标指向的位置就是当前颜色在每一组中的位置，答案数组用于储存感叹号（不确定颜色）在每一组中相同位置出现的次数。让这个动态下标和答案数组联系起来，就能知道这个颜色在组中的位置进而知道所需要的颜色数量。

还有一点，面对一些强劲的数据时前面题解会输出错误答案。比如 $\verb!R!!!!$，我们知道，这三个感叹号除了 $\verb!R!$ 其他颜色都能填。但前面题解的思路和做法会直接不管，输出一些离谱的答案。那么对于这个问题，我们可以考虑设置初始值，让答案数组默认随便一个颜色就行了。但是你可能会问：那万一后来确定了不就有重复下标了吗？为了保证每组各个颜色位置确定，可以用交换变量的方式，我不能填，那就让我要填的那个格子去顶罪。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans[5]={0,0,0,0,0};//答案数组
int r=1,g=2,y=3,b=4;//动态下标，设置初值避免相同问题
int main(){
    cin>>s;
    for(int i=0;i<s.size();i++)
        switch(s[i]){
        case'R'://i%4+1的位置是R，找出替罪羊交换
        	if(g==i%4+1)
				swap(r,g);
			else if(y==i%4+1)
				swap(r,y);
			else if(b==i%4+1)
				swap(r,b);
            break;
        case 'G'://i%4+1的位置是G，找出替罪羊交换
        	if(r==i%4+1)
				swap(g,r);
			else if(y==i%4+1)
				swap(g,y);
			else if(b==i%4+1)
				swap(g,b);
            break;
        case 'Y'://i%4+1的位置是Y，找出替罪羊交换
        	if(r==i%4+1)
				swap(y,r);
			else if(g==i%4+1)
				swap(y,g);
			else if(b==i%4+1)
				swap(y,b);
            break;
        case 'B'://i%4+1的位置是B，找出替罪羊交换
        	if(r==i%4+1)
				swap(b,r);
			else if(g==i%4+1)
				swap(b,g);
			else if(y==i%4+1)
				swap(b,y);
            break;
        default:
            ans[i%4+1]++;//是感叹号，那么这个位置就需要多一个颜色
        }
    cout<<ans[r]<<" "<<ans[g]<<" "<<ans[y]<<" "<<ans[b];//联系下标和答案数组得到最终答案
    return 0;
}
```

---

## 作者：scpchangyi (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF758B)

### [题目解析]

给出一个字符串，里面的字符只包括：```R,B,Y,G``` 和 ```!```，每种字符代表不同的花的颜色(```!``` 代表颜色未知)。并且任意四朵连续的花不会有相同的颜色。现在你要做的是把字符串填回原来的样子，并统计共用了每种花多少种。

### [思路分析]

这道题是周期性问题。求四种颜色要用的数量，我们可以定义四个统计数量的变量。当遍历到一个字符时，对应的变量取字符位置 $\bmod \space 4$ 的值，如果遍历到 $!$ 字符，就在 $\bmod \space 4$ 的位置上加 $1$，最后在输出每个颜色的值即可。

### [代码]

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
void check()/*遍历过程*/
{
	int x=i%4;
 	if(s[i]=="R")r=x;
	if(s[i]=="B")b=x;
	if(s[i]=="Y")y=x;
    	if(s[i]=="G")g=x;
    	/*取字符位置 mod 4的值*/
    	if(s[i]=="!")++a[x];
    	/*在 i mod 4的位置上加 1*/
}
int r,b,y,g,a[10];
string s;
signed main()
{
   	cin>>s;
   	for(int i=0;i<s.size();++i)check();//遍历 
   	cout<<a[r]<<' '<<a[b]<<' '<<a[y]<<' '<<a[g];
   	return 0;/*好习惯*/ 
}
```

---

