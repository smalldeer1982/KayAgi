# The Useless Toy

## 题目描述

走在马什马洛市的街道上，斯拉斯蒂诺纳看到一些商人在卖一种现在很流行的无用玩具——焦糖纺纱机！她想加入热潮，于是便买了一个。

斯威特兰的纺纱工有V形焦糖的形状。每个纺纱机都可以绕着一条看不见的魔法轴旋转。在特定的时间点，旋转器可以采取如下所示的4个位置（每个位置相对于前一个旋转90度，第四个位置后面跟着第一个位置）：
![](https://cdn.luogu.org/upload/vjudge_pic/CF834A/978c2c171211f16d263ee860d565ee38c2afcc26.png)
在纺纱机被纺纱后，它开始旋转，这通过以下算法描述：纺纱机维持其位置一秒钟，然后以顺时针或逆时针的顺序庄严地切换到下一个位置，这取决于纺纱机的纺纱方向。

斯拉斯蒂诺纳设法使旋转器旋转了n秒。被过程的优雅所吸引，她完全忘记了纺纱机旋转的方向！幸运的是，她成功地回忆起了开始的位置，并想根据她所知道的信息推断出方向。请你帮助她完成这件事。

## 样例 #1

### 输入

```
^ >
1
```

### 输出

```
cw
```

## 样例 #2

### 输入

```
< ^
3
```

### 输出

```
ccw
```

## 样例 #3

### 输入

```
^ v
6
```

### 输出

```
undefined
```

# 题解

## 作者：user470883 (赞：0)

## 题意：
给定两个字符 $a$ , $b$ 和 $n$，有 ```v``` , ```>``` , ```^``` , ```<``` 四种状态，分别代表 v 型字符现在的旋转状态。

若刚开始字符是 $a$ 状态，问是顺时针还是逆时针旋转 $n$ 次后会成为 $b$ 状态。

顺时针，输出```cw```；逆时针，输出```ccw```；否则未定义，输出```undefined```（注意：如果顺时针和逆时针都满足时也要输出```undefined```）。

参考了Level_Down巨佬的翻译。

## 思路：
用**模拟**即可。

我们先用一个数组去存四种状态。
```
char c[5]={'0','v','<','^','>'};//我们c[0]不用，就先把它初始化为零。
```
接着分类讨论：

1. 顺时针：

我们用```(x+n)%4```来判断，其中 $n$ 是旋转 $n$ 次。

2. 逆时针：

和顺时针同理，只不过是反过来的。我们```(x-n)%4```来判断。不过请注意：**由于答案有可能是负数**，所以我们做一个小手脚，变成```((x-n)%4+4)%4```,这样就可以避免负数问题了。

```undefined```:

请看我的翻译，这一项有两种情况，我们用```||```链接：```cw&&ccw||!(cw||ccw)```

然后用几个 if,else 串起来就能AC了。

欢迎找茬，有问题尽管私聊我哦！

球管理通过。

---

## 作者：Inorganic_Chemistry (赞：0)

[AC 记录。](https://www.luogu.com.cn/record/37198485)


直接模拟就行。

首先先开 $c$ 数组，将四种情况对应的 ASCII 码转换为 $c$ 数组中这个位置所代表的数并将这四个位置赋值为 $1$,$2$,$3$,$4$。

然后输入并判断是顺时针还是逆时针即可。

注意如果同时满足顺时针和逆时针也应输出 `undefined`。

具体看代码，有详细注释。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	char a,b;
	int n,c[1001];
	c[118]=1,c[60]=2,c[94]=3,c[62]=4;//四种情况存入
	cin>>a>>b>>n;//输入
	int x=a,y=b;//找到输入的情况所对应的数
	bool xx=0,yy=0;//标记
	if((c[x]+n)%4==c[y]%4) xx=1;//顺时针判断，加上 n 表示顺时针转了 n
	if(((c[x]-n)%4+4)%4==c[y]%4) yy=1;//逆时针判断，由于 c[x]-n 可能为负数，要取模之后再加上 4 确保为正数
	if((xx==1&&yy==1)||!(xx==1||yy==1)) cout<<"undefined"<<endl;//顺时针逆时针都行或者是都不行均要排除
	else if(xx==1) cout<<"cw"<<endl;//是顺时针
	else if(yy==1) cout<<"ccw"<<endl;//是逆时针
	return 0;
}
```


---

## 作者：tobie (赞：0)

这道题其实我们可以用模运算来做。我们先把`v < ^ >`编码为` 0 1 2 3`

那么顺时针旋转 $n$ 次就可以用 `(x+n)%4` 来判断。

同理，逆时针旋转就可以用 `((x-n)%4+4)%4` 。这里很关键，因为x-n可能是负数，如果直接取余数是会变成负数的。

剩下的就是判断undefined的步骤了，undefined要嘛是不可能完成这个方法，要嘛是两种旋转方法都可以满足，这种代码也很好写。

时间复杂度是 $O(1)$

话不多说，上代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int ch[128];
char a,b;
int n,x,y;
bool cw,ccw;
int main()
{
	ch['v']=0;//把四中方向编码（懒人必备c++强制转换特性）
	ch['<']=1;
	ch['^']=2;
	ch['>']=3;
	cin>>a>>b>>n;
	x=ch[a],y=ch[b];
	if((x+n)%4==y) cw=1;//判断顺时针
	if(((x-n)%4+4)%4==y) ccw=1;//判断逆时针
	if(cw&&ccw||!(cw||ccw)) printf("undefined");//判断undefined
	else
	{
		if(cw) printf("cw");
		if(ccw) printf("ccw");
	}
}
```

---

## 作者：Level_Down (赞：0)

### 题意简述：

给定两个字符 a , b 和 n，有 v , > , ^ , < 四种情况，分别代表 v 型字符现在的旋转状态

若刚开始字符是 a 状态，问是顺时针还是逆时针旋转 n 次会成为 b 状态。

顺时针，输出cw；逆时针，输出ccw；否则未定义，输出undefined。

### 方法：

**模拟**就可以了！我们可以将这个字符顺时针和逆时针旋转后得到的答案与 b 对比，最后输出。

看一下具体操作（以顺时针旋转为例）：

先定义一个char数组：
```
char s[5] = {'0','v','<','^','>'}
```

然后先求出字符 a 在这个数组中的位置（我这里用 x 存储）：
```
for (int i = 1; i <= 4; i++) if (a == s[i]) {x = i; break;}
```

然后开始模拟，进行 n % 4 次变化，每次变化将对应 x 值加一（如果是逆时针要减一）。

如果 x 值加到最大（即 x 等于 4），x 清零。 具体实现：
```
for (i = 1; i <= n; i++) {if (x == 4) x = 0; x++;}
```

然后比较一下 s [ x ] 和 b 就行了。

最后我愉快地写出了代码：

```cpp
#include<iostream> 
using namespace std; 
char s[5] = {'0','v','<','^','>'},a,b;
long long x,y,n,i,ans1,ans2;
int main() 
{ 
    cin >> a >> b >> n;
    n %= 4;
    for (int i = 1; i <= 4; i++) if (a == s[i]) {x = i; break;}
    y = x;
    for (i = 1; i <= n; i++) {if (x == 4) x = 0; x++;}
    if (s[x] == b) {cout << "cw\n"; return 0;}
    for (i = 1; i <= n; i++) {if (y == 1) y = 5; y--;}
    if (s[y] == b) {cout << "ccw\n"; return 0;}
    	else {cout << "undefined\n"; return 0;}
    return 0;	
} 
```

然后发现样例三没过！？？？

现在我们重新读题，题目说只要是处于顺时针和逆时针之外的都输出undefined。

所以顺时针和逆时针同时满足的情况也要输出undefined。

AC代码：

```cpp
#include<iostream> 
using namespace std; 
char s[5] = {'0','v','<','^','>'},a,b;
long long x,y,n,i,ans1,ans2;//y是处理逆时针时的x的盗版。
int main() 
{ 
    cin >> a >> b >> n;
    n %= 4;
    for (int i = 1; i <= 4; i++) if (a == s[i]) {x = i; break;}
    y = x;
    for (i = 1; i <= n; i++) {if (x == 4) x = 0; x++;}
    if (s[x] == b) {ans1++;}//各种操作上面都讲得很详细了，不再赘述。
    for (i = 1; i <= n; i++) {if (y == 1) y = 5; y--;}
    if (s[y] == b) {ans2++;}
    if (ans1 == 1 && ans2 == 0) cout << "cw\n";
    	else if (ans1 == 0 && ans2 == 1) cout << "ccw\n";
    		else cout << "undefined\n";
    return 0;//AC！	
} 
```


---

## 作者：Provider (赞：0)

[先夹带一波私货](https://www.luogu.com.cn/blog/foreverlovezxy/)


题意:
有四种变换图形，分别为V < ^ > V。

然后给你初始和结束，再给n。

假如初始经过n次顺时针改变到结束，则输出cw。

若是逆时针变换到结束，则输出ccw。

若其他的就输出undefined

# CODE:

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=20;
long long n;
char s[maxn],c1,c2;
int main()
{
	for(int i=1;i<=maxn;i++)把数组中滴每一个初始化，ASCLL题意有讲
	{
		if(i%4==1)
		s[i]=118;
		else
		if(i%4==2)
		s[i]=60;
		else
		if(i%4==3)
		s[i]=94;
		else
		s[i]=62;
	}
    cin>>c1>>c2;
    cin>>n;
    n%=4;//这步很关键，如果不%可能会BOOM
    for(int i=4;i<=7;i++)//为什么是4~7，有兴趣的可以想一想
    if(c1==s[i])
    {
        if(s[i+n]==c2&&s[i-n]==c2)//假如怎么转都可以
        cout<<"undefined";
        else
		if(s[i+n]==c2&&s[i-n]!=c2)//假如顺时针可以
        cout<<"cw";
        else
		if(s[i-n]==c2&&s[i+n]!=c2)//假如逆时针可以
        cout<<"ccw";
    }
    return 0;
}
```

---

## 作者：Awa486 (赞：0)

## 解法：纯模拟+一点点数论

只需要标记一下开始和结束状态的位置posa，posb，再判断一下就好辣


因为题目保证纺轮结束位置一定可以通过给定的n次一定方向的旋转得到 所以只需要做简单的判断即可 

如果a在数组中的位置和n的和除以4等于b在数组中的位置,则顺时针旋转n次即可从a转到b

反之，如果a在数组中的位置减去n除以4等于b在数组中的位置,则逆时针旋转n次即可从a转到b

如果两种旋转都满足要求，那就输出undefined

```cpp
//因为题目保证纺轮结束位置一定可以通过给定的n次旋转得到 
if(((posa+n)%4)==posb&&((posa-n)%4)==posb)
	cout<<"undefined";
else if((posa+n)%4)==posb)
	cout<<"cw";
else
	cout<<"ccw";
```

### 但是这样有明显的bug： posa-n 一旦小于0便会导致出错

![](https://i.loli.net/2019/08/22/HRmAu4NosiSQtpC.png)

所以必须把posa%4(<=3)的结果**加上4再模4** 这样便能规避这个问题 
所以正解如下

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int main() {
	char a,b;//因为输入均为字符 
	int n,posa,posb;
	int ascii[4]= {118,60,94,62};//存储四个方向符的ASCII码 
	cin>>a>>b;
	cin>>n;
	for(int i=0; i<4; i++) {
		if((int)a==ascii[i])//强制类型转换 比较ASCII码 
			posa=i; 
		if((int)b==ascii[i])
			posb=i;
	}
	
	if((posa+n)%4==posb&&(((posa-n)%4)+4)%4==posb)
		cout<<"undefined";
	else if((posa+n)%4==posb) 
		cout<<"cw";
	else
		cout<<"ccw";
	return 0;//完美AC
}
```


---

## 作者：liuyifan (赞：0)

## 解法:打表+模拟

题目英文还挺简单的,这里就不在重复了

先用map存一下每种符号的变换方式,再按题意模拟输出即可

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
using namespace std;
map<char,int>x;//map的定义
init n;
char a,b;
int nain()
{
    x['^]=0,x['>']=1,x['v']=2,x['<']=3;//map的赋值
    cin>>a>>b>>n//输入
	n%=4;
	return 0;
    int x1=x[a]+n;
    if(x1>3)x1-=4;
    int x2=x[a]-n;
    if(x2<0)x2+=4;//模拟
    if(x1==x[b]&&x2!=x[b])puts("cw");
    else if(x1!=x[b]&&x2==x[b])puts("ccw");//继续模拟
    else puts("undefined");
}
```

Ps:[map的用法](https://www.luogu.org/blog/liuyifan/solution-p1428)~~(好像也是道大水题)~~

提交记录:![](https://i.loli.net/2018/10/06/5bb8c9a9772bb.png)


---

