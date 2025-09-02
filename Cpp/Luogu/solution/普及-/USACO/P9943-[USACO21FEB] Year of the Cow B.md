# [USACO21FEB] Year of the Cow B

## 题目描述

Farmer John 的奶牛们得知最近正在庆祝牛年的到来时十分兴奋。牛年总是奶牛们的最爱。

我们知道，中国历法中每一年所对应的生肖遵循 $12$ 年的周期：Ox, Tiger, Rabbit, Dragon, Snake, Horse, Goat, Monkey, Rooster, Dog, Pig, Rat（牛、虎、兔、龙、蛇、马、羊、猴、鸡、狗、猪、鼠），然后回到牛。

奶牛 Bessie 自豪地说她是在许多年前的一个牛年出生的。她的朋友 Elsie 想要知道她与 Bessie 出生相差多少年，并且希望你能够通过查看农场上若干奶牛出生年份之间的关系来帮助她推算。 

## 说明/提示

### 样例解释 1

在以上的输入中，

- Elsie 在 Bessie 之前 $12$ 年出生。
- Mildred 在 Bessie 之前 $9$ 年出生。
- Gretta 在 Bessie 之前 $17$ 年出生。
- Paulina 在 Bessie 之后 $9$ 年出生。

## 样例 #1

### 输入

```
4
Mildred born in previous Dragon year from Bessie
Gretta born in previous Monkey year from Mildred
Elsie born in next Ox year from Gretta
Paulina born in next Dog year from Bessie```

### 输出

```
12```

# 题解

## 作者：Harlem (赞：2)

# 题目链接
[P9943](https://www.luogu.com.cn/problem/P9943)

# 题目概述
给出不同奶牛出生生肖之间的关系，最后求出 _Bessie_ 与 _Elsie_ 的出生年份之间**相差的年数**。

# 解题思路
注意题中有**这三个限制**：
*  _最后一个单词是农场上某一头奶牛的名字，为 Bessie 或一头已经在之前的输入中出现过的奶牛。_  
*  _第一个单词是农场上某一头奶牛的名字，不为 Bessie 且未在之前的输入中出现过。_ 
*  _输入保证可以通过给定的信息求出结果。_ 

**这说明所有的关系式都是由已知推未知，并且确保有结果，大大降低了难度和复杂度。**

我们可以开一个 $c$ 数组表示 _Bessie_ 与其他所有奶牛出生年份的差值，$y$ 数组储存每一头奶牛的生肖的对应年份。

易得：$c_0=0$，$y_0=0$。（以牛年为起始年，_Bessie_ 的编号为 $0$ ）

设已知牛编号为 $a$，未知牛编号为 $b$，易得：

当输入条件为 `previous` 时，

$$
c_b = \begin{cases} c_a+(y_b-y_a) & y_b<y_a\\ c_a+(y_b-12-y_a) & y_b \ge y_a\end{cases}
$$

当输入条件为 `next` 时，

$$
c_b = \begin{cases} c_a+(y_b-y_a) & y_b>y_a\\ c_a+(y_b+12-y_a) & y_b \le y_a\end{cases}
$$

# 代码思路
我们可以使用 `map` 映射奶牛名称与对应的编号和各个生肖与其对应的编号。例子：

```cpp
map<string, int> id;
map<string, int> sx={{"Ox",0},{"Tiger",1},{"Rabbit",2},{"Dragon",3},{"Snake",4},{"Horse",5},{"Goat",6},{"Monkey",7},{"Rooster",8},{"Dog",9},{"Pig",10},{"Rat",11}};

id["Bessie"]=0;
```
然后根据上面推出的公式编写代码即可。

# 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int c[105],y[205];
string a,b,pd,t,year;//已知犇，未知犇，前或后，临时字符串，生肖年
map<string,int> sx={{"Ox",0},{"Tiger",1},{"Rabbit",2},{"Dragon",3},{"Snake",4},{"Horse",5},{"Goat",6},{"Monkey",7},{"Rooster",8},{"Dog",9},{"Pig",10},{"Rat",11}};
map<string,int> id;

int main(){
	cin>>n;
	c[0]=y[0]=0;
	id["Bessie"]=0;
	for(int i=1;i<=n;i++){
		cin>>a>>t>>t>>pd>>year>>t>>t>>b;//此处也可用scanf，但蒟蒻没弄好格式QAQ 
		id[a]=i;y[i]=sx[year];//初始化Bessie的数据
		if(pd=="previous"){
			if(y[i]<y[id[b]]){
				c[i]=c[id[b]]+(y[i]-y[id[b]]);
			}
			else{
				c[i]=c[id[b]]+(y[i]-12-y[id[b]]);
			}
		}
		if(pd=="next"){
			if(y[i]>y[id[b]]){
				c[i]=c[id[b]]+(y[i]-y[id[b]]);
			}
			else{
				c[i]=c[id[b]]+(y[i]+12-y[id[b]]);
			}
		}
	}
	cout<<abs(c[id["Elsie"]]);//c数组中储存的是差值，不要忘了加绝对值
	return 0;
}

```

 _完结撒花_ヾ(≧ ▽ ≦)ゝ

---

## 作者：OIerWu_829 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P9943)

看见明天有比赛，赶紧来写篇题解祝我 RP++！

（思路来源于官方题解）

## 思路

我们要知道如何确定一头牛出生的时间，可以举个例子：

假设我们已知 `Mildred born in next Dragon year from Bessie`（Mildred 在 Bessie 出生的后一个龙年出生），我们可以先把 Mildred 的出生年份设为比 Bessie 晚一年，然后不断增加它的出生年份，直到它是一个龙年。当然如果知道 Mildred 比 Bessie 出生早，那么可以用同样的方法不断地减。

综上所述，我们可以从 Bessie 的出生年份开始，一年一年地改变，直到变为给定的年份。

```cpp
#include <iostream>
#include <map>
using namespace std;
string f[12] = {"Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"};
map<string, int> mp;
string Get(int year) {
    int t = 0, y = 2021;
    while (y < year) {
        y++;
        t++;
        if (t == 12) t = 0;
    }
    while (y > year) {
        y--;
        t--;
        if (t == -1) t = 11;
    }
    return f[t];
}
int main()
{
    mp["Bessie"] = 2021;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string ca, b, inn, r, a, y, f, cb;
        cin >> ca >> b >> inn >> r >> a >> y >> f >> cb;
        mp[ca] = mp[cb];
        do {
            if (r == "previous") mp[ca]--;
            else mp[ca]++;
        } while (Get(mp[ca]) != a);
    }
    int ans = mp["Bessie"] - mp["Elsie"];
    cout << abs(ans) << endl;
    return 0;
}
```


---

## 作者：TipherethB (赞：1)

# [洛谷P9943](https://www.luogu.com.cn/problem/P9943)
小蒟蒻第一篇题解~
## 题目大意
输入一系列奶牛的关系，算出 _Bessie_ 和 _Elsie_ 的出生年份之间相差的年数。
## 解题思路
因为每次输入第一个单词所表示的奶牛未出现过，最后一个单词所表示的奶牛为 _Bessie_ 或出现过，所以顺序往下一定能找到。
## 核心代码
查找两头牛相差几岁，设每个生肖为 $1\sim12$ 的一个数，以牛 $x$ 年龄小为例：

* 当 $x$ 的生肖编号（以下简称 $id$ ）比 $y$ 的 $id$ 小时，说明 $x$ 和 $y$ 在同一个 $12$ 年内，直接大减小就行。

* 当 $x$ 的 $id$ 比 $y$ 的 $id$ 大时，说明 $x$ 和 $y$ 不在同一个 $12$ 年内，也就是说先算还有 $x$ 和 $y$ 的 $12$ 年差几年，也就是$ 12-x $，再加 $y$ 即可。

*  $x$ 年龄大同理。

**可推出公式：**

牛 $x$ 年龄小时：

$ \begin{cases}
   y - x &\text{if } x < y \\
   12 - x + y &\text{if } x \geq y
\end{cases} $

牛 $x$ 年龄大时：

$ \begin{cases}
   x - y &\text{if } x > y \\
   12 - y + x &\text{if } x \leq y
\end{cases} $
## 完整代码

```cpp
#include <bits/stdc++.h>
#define I return
#define love 0
#define luogu ;
using namespace std; //常规 

int n; //关系数量 

string s[10], t[12] = {"Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"}; //存关系和生肖顺序 

map <string, int> age, id; //每头牛的年龄和生肖顺序 

map <string, string> year; //每头牛的生肖 

int find(int x, int y, int f) { //牛x生肖编号，牛y生肖编号，方向 
	if(f == 0) { //往前数 
		if(x < y) {
			return y - x;
		}
		else return 12 - x + y;
	} else { //往后数 
		if(x > y) {
			return x - y;
		}
		else return 12 - y + x;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); //加速 
	year["Bessie"] = "Ox"; //Bessie属牛 
	for (int i = 0; i < 12; i++) {
		id[t[i]] = i; //用map映射数字，如Ox=1，Tiger=2以此类推 
	}
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 8; j++) {
			cin >> s[j];
		} //输入 
		year[s[1]] = s[5]; //给新牛赋生肖 
		if (s[4] == "previous") {
			age[s[1]] = age[s[8]] - find(id[s[5]], id[year[s[8]]], 0); //新牛年龄=老牛年龄-相差年份 
		} else {
			age[s[1]] = age[s[8]] + find(id[s[5]], id[year[s[8]]], 1); //新牛年龄=老牛年龄+相差年份 
		}
		if (s[1] == "Elsie") {
			break;
		} //一个小优化，查到Elsie的年龄直接退出 
	}
	cout << abs(age["Elsie"] - age["Bessie"]) << '\n'; //输出 
	I love luogu //华丽结束 
}
```

---

## 作者：HMSVanguard (赞：1)

# 洛谷P9943题解
## 题目大意
给出 $n$ 行关系，每行关系记录一头牛的出生时间，都是在之前已经出现的一头牛的前一或者后一某生肖年出生，Bessie 在牛年出生，求 Bessie 和 Elsie 的出生年份之间相差的年数。

## 思路

**省流**：本题解提供一种不用 map 容器而使用字典树来将字符串和其编号建立关系的做法。

楼上的几位大佬用的是 map 容器，但是本蒟蒻不会 map 容器啊 qwq。只好用其他做法了。  

不用 map 的话，如何记录牛的信息呢？本蒟蒻看到每一只牛的关系是用牛的名字即字符串来记录的，于是想到了 trie 也就是字典树。所以这里提供一个字典树做法。

那么什么是字典树呢？

### 字典树

“字典树，英文名 trie。顾名思义，就是一个像字典一样的树。”——[OI Wiki](https://oi.wiki/string/trie/)

字典树是一种用边代表字符的树，从根节点到树上的某一结点所经过的路径就代表这一个字符串。树的每个点也会有单独的编号。

如果不明白的话可以看这张图，这张图代表了分别加入以下这四个字符串的字典树。

```
abcd ac abdc bcda
```
![emm](https://cdn.luogu.com.cn/upload/image_hosting/fe5k3jj3.png?x-oss-process=image/resize,m_lfit,h_700,w_700)

我们用下面这个数组记录字符串。
```
trie[p][a]
```
这个数组中 $p$ 代表上一个点的编号，而 $a$ 代表字符的 ASCII 值。如果 $p = 1 \, a = 97$ 时，代表着编号为 $1$ 的点和当前这个点之间的边代表的字符是 a。而数组中存储的数字就是点的编号，也就是点的**指针**。这样，我们就可以通过点的指针依次查找下面的子树了。如果两个字符串有公共前缀，他们就会共用公共前缀所代表的那一条路径，可以看看上面的图。

还有对于 $a$ 的空间可以优化一下：如果你只需要记录 ASCII 值中 a 以后的字符，你就可以在加入字符时将它的 ASCII 值减去 a 的 ASCII 值。这样在开数组时就可以开小一点。不过查找的时候别忘了也要减去 a 的 ASCII 值。详情可以看下面代码中的注释。

如果还没明白的话，可以去看看下面的代码和注释辅助理解，也可以去[ P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)或者[字典树模板](https://www.luogu.com.cn/problem/P8306)学习一下。

总之，字典树是一种可以快速查找一个字符串的数据结构。在日后的学习里，还会有 01trie，AC 自动机等应用字典树的复杂算法。

下面是字典树插入的代码。
```cpp
int trie[100005][99],cnt=0,last[100005];
//cnt代表当前插入点的个数，也就是新的点的编号
//last数组记录每一个字符串的结束指针
//a的ASCII值是97
//当int类型变量减去一个char类型变量时，会自动把字符转化成它对应的ASCII值再进行计算
void add(string s)
{
	int p=0;
	for(int i=0;i<s.size();i++)//从前到后遍历字符串
	{
		int a=s[i]-'a';//这样所有的s[i]的ASCII值都会被减去97，这时数组就不用开太大了。
		if(!trie[p][a])//如果当前点没有被添加过，那么插入这个点 
		trie[p][a]=++cnt;//插入当前点的编号
		p=trie[p][a];//更新指针，继续向下 
	}
	last[p]=1;//记录有字符串在p这里结束了 
}
```

下面是字典树查找的代码。
```cpp
int find(string s)
{
	int p=0;
	for(int i=0;i<s.size();i++)
	{
		int a=s[i]-'a';//查找的时候也别忘了减，不然存储的位置就出错了
		if(!trie[p][a])//当前点没有被添加过，则该字符串没有被添加过，返回0
		return 0;
		p=trie[p][a];
	}
	if(last[p]==1)//有字符串在当前结束，则返回1 
	return 1;
	else//没有字符串在当前结束，则该字符串是某个字符串的前缀，返回2
	return 2;
 } 
 ```
 
 ### 本题思路
 那么如何用字典树解决本题呢？
 
 每输入一个名字，我们便将他存入字典树中，并返回其字符串最后一位的指针。我们再用一个结构体通过指针来存储牛的信息。若要查找一头牛的信息，只需在字典树中查找这头牛的名字并返回指针，然后就可以通过指针找到这头牛的信息啦。
 
 在这之后，我们就可以通过输入的生肖种类来逐个计算每头牛的出生时间，计算的时候要注意生肖的先后顺序，判断两头牛的出生时间是否在同一个 $12$ 年循环中，若不是，则要注意加上或减去 $12$ 来得出正确答案。
 
 
 最后附上 AC 代码~~~马蜂比较奇怪，望见谅。
 
 代码挺长，比较麻烦，但跑的也不算很慢。
 ```
 #include<bits/stdc++.h>
using namespace std;
int trie[114514][70],cnt=0;
struct Cow{//记录奶牛的出生信息
	int year,tim;//year记录生肖，tim记录时间 
}cow[114514]; 
int add(string s)
{
	int p=0;
	for(int i=0;i<s.size();i++)
	{
		int a=s[i]-'A';//牛的名字有大写字母，所以要减'A' 
		if(trie[p][a]==0)
		{
			trie[p][a]=++cnt;
		}
		p=trie[p][a];
	}
	return p;//返回这头牛的指针 
}
int find(string s)
{
	int p=0;
	for(int i=0;i<s.size();i++)
	{
		int a=s[i]-'A';
		p=trie[p][a];//因为这里牛的名字在前面保证出现过，所以不用判断当前点 
	}
	return p;
}
/*Ox, Tiger, Rabbit, Dragon, Snake, Horse, Goat, Monkey, Rooster, Dog, Pig, Rat	这是生肖的顺序 
  0		1		2		3		4		5	6		7		8		9	10	11*/
int main()
{
	int n;
	cin>>n;
	string s="Bessie"; 
	int num=add(s); 
	cow[num].year=0,cow[num].tim=0;//加入Bessie这头牛 
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		num=add(s);
		cin>>s>>s>>s;//无用的字符
		bool mode;//记录在之前还是在之后 
		if(s[0]=='p')
		{
			mode=0;
		}
		else mode=1;
		cin>>s;
		switch (s[0]) {//生肖编号 
	        case 'O':
	            cow[num].year=0;
	            break;
	        case 'T':
	            cow[num].year=1;
	            break;
	        case 'R':
	            if(s[1]=='a')
	            {
	            	if(s[2]=='b')
	            	cow[num].year=2;
	            	else
	            	cow[num].year=11;
				}
				else
	            cow[num].year=8;
	            break;
	        case 'D':
	            if(s[1]=='r')
	            cow[num].year=3;
	            else
	            cow[num].year=9;
	            break;
	        case 'S':
	            cow[num].year=4;
	            break;
	        case 'H':
	            cow[num].year=5;
	            break;
	        case 'G':
	            cow[num].year=6;
	            break;
	        case 'M':
	        	cow[num].year=7;
	        	break;
	        case 'P':
	            cow[num].year=10;
	            break;   
	    }
		cin>>s>>s>>s;
		int num2=find(s);
		if(mode==0)	 //出生在之前的
		{
			if(cow[num].year<cow[num2].year) 
			{
				cow[num].tim=cow[num2].tim-cow[num2].year+cow[num].year;//计算出生时间 
			}
			else//不在一个循环内，更换计算方式，减去 12
			{
				cow[num].tim=cow[num2].tim-12+(cow[num].year-cow[num2].year);
			}
		}
		if(mode==1)	
		{
			if(cow[num].year>cow[num2].year)
			{
				cow[num].tim=cow[num2].tim+cow[num].year-cow[num2].year;
			}
			else//不在一个循环内，更换计算方式，加上 12
			{
				cow[num].tim=cow[num2].tim+12-(cow[num2].year-cow[num].year);
			}
		}
	}
	s="Elsie";
	num=find(s);//找到 Elsie这头牛的信息 
	if(cow[num].tim<0)// Bessie出生时间为0，所以tim的绝对值便为相差的年数 
	cow[num].tim*=-1;
	cout<<cow[num].tim;//输出答案 
	return 0;//程序结束啦~~~ 
 }  
 ```
 那么这篇题解就结束了。这是本蒟蒻的第一篇题解，~~求过~~。
 如果有问题请指出 QWQ。

---

## 作者：LHW_Cosset_Idiot (赞：1)

这是一道非常标准模拟题。 

#### 这是一篇错误的代码（只有30分）:

错在倒推时的模拟。（给出部分）
```
    for(int i=1; ; i++){
        if(f[f[Elsie].who].dwho==0){
            if(f[f[Elsie].who].qh==1){
                ans+=(12-f[f[Elsie].who].year+1);
            }else{
                ans-=(12-f[f[Elsie].who].year+1);
            }
            cout<<abs(ans);
            return 0;
        }else{
            if(f[f[Elsie].who].qh==1){
                if(f[f[Elsie].dwho].year>f[f[Elsie].who].year){
                    ans+=(12-f[f[Elsie].dwho].year-f[f[Elsie].who].year+1);
                }else{
                    ans+=(12-f[f[Elsie].who].year+f[f[Elsie].dwho].year+1);
                }
            }else{
                if(f[f[Elsie].dwho].year>f[f[Elsie].who].year){
                    ans-=(f[f[Elsie].dwho].year-f[f[Elsie].who].year-1);
                }else{
                    ans-=(12-f[f[Elsie].who].year+f[f[Elsie].dwho].year-1);
                }
            }
            f[Elsie].who=f[Elsie].dwho;
            f[Elsie].dwho=f[f[Elsie].dwho].dwho;
        }
    }
    return 0;
}
```
#### 正解思路：
首先我们把每次输入时用变量数组存起来。

然后先求出 $x$ 和 $y$（两头相邻的牛）的生肖之间的年份差，即 $x$ 与 $y$ 的年龄差，再根据它们的年龄之间的大小关系用 $x$ 的出生年份加减年龄差，求出 $y$ 的出生年份。

改成了这样就满分了。
### 正解：
```
#include<bits/stdc++.h>
using namespace std;
int n,a[205],sx[205];
char c[105][10][105],name[205][105],ssx[15][20]= {"Ox","Tiger","Rabbit","Dragon","Snake","Horse","Goat","Monkey","Rooster","Dog","Pig","Rat"};
int main()
{
    int x,sum,y;
    scanf("%d",&n);
    a[0]=1;
    a[1]=0;
    sx[1]=0;
    name[1][0]='B';
    name[1][1]='e';
    name[1][2]='s';
    name[1][3]='s';
    name[1][4]='i';
    name[1][5]='e';
    for(int i=1; i<=n; i++){
        for(int j=1; j<=8; j++){
            scanf("%s",c[i][j]);
        }
        for(int j=1; j<=a[0]; j++){
            if(!strcmp(name[j],c[i][8])){
                x=j;
                break;
            }
        }
        if(c[i][1][0]=='E' && c[i][1][1]=='l' && c[i][1][2]=='s' && c[i][1][3]=='i' && c[i][1][4]=='e' && strlen(c[i][1])==5){
            y=a[0]+1;
        }
        a[0]++;
        strcpy(name[a[0]],c[i][1]);
        if(c[i][4][0]=='p'){
            sum=0;
            for(int j=sx[x]-1; ; j--){
                if(j==-1)
                    j=11;
                sum++;
                if(!strcmp(ssx[j],c[i][5])){
                    a[a[0]]=a[x]-sum;
                    sx[a[0]]=j;
                    break;
                }
            }
        }else{
            sum=0;
            for(int j=sx[x]+1; ; j++){
                if(j==12){
                    j=0;
                }
                sum++;
                if(!strcmp(ssx[j],c[i][5])){
                    a[a[0]]=a[x]+sum;
                    sx[a[0]]=j;
                    break;
                }
            }
        }
    }
    printf("%d",abs(a[1]-a[y]));
    return 0;
}
```
请勿抄袭！！！

---

## 作者：2027zengrihui (赞：1)

可以先用一个字符数组将每个生肖按对应的年份存在数组当中，以便我们后续的调用。
    这道题其实即使最短路，用已知条件去求 Bessie 和 Elsie 之间的年龄差，也就是从 Elsie 到 Bessie 之间的路径的权值的和。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int n,a[205],sx[205];
char c[105][10][105],name[205][105],qw[15][20]= {"Ox","Tiger","Rabbit","Dragon","Snake","Horse","Goat","Monkey","Rooster","Dog","Pig","Rat"};
int main() {
	scanf("%d",&n);
	int x,sum,y;
	a[0]=1;a[1]=0;sx[1]=0;
	name[1][0]='B';name[1][1]='e';name[1][2]='s';
	name[1][3]='s';name[1][4]='i';name[1][5]='e';
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=8; j++)
			scanf("%s",c[i][j]);
		for(int j=1; j<=a[0]; j++)
			if(!strcmp(name[j],c[i][8])) {
				x=j;break;
			}
		if(c[i][1][0]=='E'&&c[i][1][1]=='l'&&c[i][1][2]=='s')y=a[0]+1;a[0]++;
		strcpy(name[a[0]],c[i][1]);
		if(c[i][4][0]=='p') {
			sum=0;
			for(int j=sx[x]-1;; j--) {
				if(j==-1)j=11;sum++;
				if(!strcmp(qw[j],c[i][5])) {a[a[0]]=a[x]-sum;sx[a[0]]=j;break;}
			}
		} else {
			sum=0;
			for(int j=sx[x]+1;; j++) {
				if(j==12)j=0; sum++;
				if(!strcmp(qw[j],c[i][5])) {a[a[0]]=a[x]+sum,sx[a[0]]=j;break;}
			}
		}
	}
	printf("%d",abs(a[1]-a[y]));
}
```

---

## 作者：卷王 (赞：1)

## 大体思路

这是一道模拟题。但是我的实现方法好像跟别人的不太一样。

我们可以假设 `Bessie` 的年龄为 $0$（虽然不现实，但是可以这样假设），然后遍历 $n$ 次，每次从已知的年龄推向未知的年龄，依次求出。显然，每一次至少会有一头牛的年龄被算出，遍历 $n$ 次可以保证正确性。

如果大体的思路懂了，代码就很好实现了。一些细节以及变量含义会在代码中提到。

## 代码
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
string a[107], b[107], c[107], d[107];
map<string, int> mp;
map<string, string> year; //year[s] 表示名字是 s 的奶牛是什么年
map<string, int> know; //know[s] 表示名字是 s 的奶牛年龄，不知道则为 0
bool vis[107]; //vis[i] 表示第 i 条读入信息有没有被用过

signed main() {
	std::ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	mp["Ox"] = 0, mp["Tiger"] = 1, mp["Rabbit"] = 2, mp["Dragon"] = 3, mp["Snake"] = 4;
	mp["Horse"] = 5, mp["Goat"] = 6, mp["Monkey"] = 7, mp["Rooster"] = 8;
	mp["Dog"] = 9, mp["Pig"] = 10, mp["Rat"] = 11; //mp 赋值
	//假设 Bessie 的年龄为 0
	year["Bessie"] = "Ox";
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> a[i] >> s >> s >> b[i] >> c[i] >> s >> s >> d[i];
		year[a[i]] = c[i];
		//a, b, c, d: first_name next/previous year second_name
	}
	for (int l = 1; l <= n; l++) { //遍历 n 次可以保证不会有牛年龄没有被计算
		for (int i = 1; i <= n; i++) {
			if(vis[i]) continue;
			if((know[d[i]] != 0 || d[i] == "Bessie") && !know[a[i]]) {
				vis[i] = 1;
				if(b[i] == "next") { //分讨
					if(mp[year[d[i]]] < mp[year[a[i]]]) know[a[i]] = know[d[i]] + (mp[year[a[i]]] - mp[year[d[i]]]);
					else know[a[i]] = know[d[i]] + (12 - mp[year[d[i]]] + mp[year[a[i]]]);
				}
				else {
					if(mp[year[a[i]]] < mp[year[d[i]]]) know[a[i]] = know[d[i]] - (mp[year[d[i]]] - mp[year[a[i]]]);
					else know[a[i]] = know[d[i]] - (12 - mp[year[a[i]]] + mp[year[d[i]]]);
				}
			}
		}
	}
	cout << abs(know["Bessie"] - know["Elsie"]);
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

模拟题。因为 Bessie 是牛年出生的，而 $2021$ 年也是牛年，那么我们可以假设 Bessie 是 $2021$ 年出生的。我们可以用两个 `map` 来记录每只奶牛的生肖和出生年份。

我们把每次输入的第一头奶牛（输入格式示例中的 Mildred）称为甲，第二头（示例中的 Bessie）称为乙。

我们可以先求出甲和乙的生肖之间的年份差，即甲乙的年龄差，再根据它们的年龄之间的大小关系用甲的出生年份加或减年龄差，求出乙的出生年份。

```c++
#include<bits/stdc++.h>
using namespace std;

map<string,string> m1;
map<string,int> m2;

int getn(string d){
	if(d=="Ox") return 0;
	if(d=="Tiger") return 1;
	if(d=="Rabbit") return 2;
	if(d=="Dragon") return 3;
	if(d=="Snake") return 4;
	if(d=="Horse") return 5;
	if(d=="Goat") return 6;
	if(d=="Monkey") return 7;
	if(d=="Rooster") return 8;
	if(d=="Dog") return 9;
	if(d=="Pig") return 10;
	if(d=="Rat") return 11;
}

int getc(string D1,string D2,int g){ // 求出年份差（年龄差） 
	int d1=getn(D1),d2=getn(D2);
	if(d1==d2) return 12;
	return ((d2-d1)*g+12)%12;
}

int main(){
	int n;cin>>n;
	m1["Bessie"]="Ox";m2["Bessie"]=2021; // 初始化 
	while(n--){
		string ca,cb,gx,dw,in;
		cin>>ca>>in>>in>>gx>>dw>>in>>in>>cb; // 读入需要的信息 
		int f=1;if(gx=="previous") f=-1; // 奶牛年龄的大小关系 
		m1[ca]=dw;m2[ca]=m2[cb]+getc(m1[cb],dw,f)*f; // 这头奶牛的生肖和出生年份 
	} 
	cout<<abs(m2["Elsie"]-m2["Bessie"]);
	return 0;
}

```

---

## 作者：XiaoWhy (赞：0)

关键点:

* 最后一个单词是农场上某一头奶牛的名字，为 `Bessie` 或一头已经在之前的输入中出现过的奶牛。

* 第一个单词是农场上某一头奶牛的名字，不为 `Bessie` 且未在之前的输入中出现过。

因为这两句话，我们可以发现第一句话最后一个单词一定是 `Bessie`，每句话的最后一个单词都是已经出现过的单词，如果我们假设 `Bessie` 的年份是 $0$，那么每个牛的年份都可以唯一确定。
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[15]={"Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"};
int get(int x,int y,int f){//传入两个牛的生肖编号以及前后关系得出年份差
	if(f==0){//x在y的前面
		if(x<y) return y-x;
		else return 12-x+y;
	}else{//x在y的后面
		if(x>y) return x-y;
		else return 12-y+x;
	}
}
int main(){
	int n;
	cin>>n;
	map<string,int> id,year;//生肖的编号以及某个牛的出生年份
	map<string,string> xs;//记录某个牛的生肖
	xs["Bessie"]="Ox";//题目说明了Bessie属于牛年
	for(int i=0;i<12;i++) id[s[i]]=i;
	for(int i=1;i<=n;i++){
		string a[10];
		for(int j=1;j<=8;j++) cin>>a[j];//输入8个单词
		string x=a[1],y=a[8];//联系的两头牛
		if(a[4]=="previous"){
			year[x]=year[y]-get(id[a[5]],id[xs[y]],0);
			xs[x]=a[5];
		}else{
			year[x]=year[y]+get(id[a[5]],id[xs[y]],1);
			xs[x]=a[5];
		}
	}
	cout<<abs(year["Bessie"]-year["Elsie"]);
	return 0;
}
```

---

## 作者：Manki23333333 (赞：0)

#### 废话

大佬可能会直接推出小式子，可是我太菜了，只能分讨加搜索了。

#### 整体思路

看到这种「关系」题，你首先就应该想到图论建模。

由于给定的一定是没锅的，所以我们不需要跑最短路，只需要跑一遍小搜索就可以了。

#### 代码实现

```
#include <bits/stdc++.h>

using namespace std;

int n, top = 1;

struct Edge {
	int to, dir, sx;
};

vector <Edge> G [105];
bool flag [105];

map <string, int> sx2id;

map <string, int> n2id;
map <int, string> id2n;

int years [105];
void dfs (int u, int year, int sx) {
	flag [u] = true;
	years [u] = year;
	
	for (int i = 0 ; i < G [u]. size () ; i ++) {
		if (!flag [G [u] [i]. to]) {
			int to = G [u] [i]. to;
			int nsx = G [u] [i]. sx;
			int nyear = year;
			int dir = G [u] [i]. dir;
			
			if (dir == -1 && nsx < sx) {
				nyear -= (sx - nsx);
			}
			
			if (dir == 1 && nsx < sx) {
				nyear += 12 - (sx - nsx);
			}
			
			if (dir == -1 && nsx > sx) {
				nyear -= (12 + sx - nsx);
			}
			
			if (dir == 1 && nsx > sx) {
				nyear += nsx - sx;
			}
			
			if (nsx == sx) {
				nyear += dir * 12;
			}
			
			dfs (to, nyear, nsx);
		}
	}
}

void Turn () {
	cin >> n;
	
	sx2id ["Ox"] = 1;
	sx2id ["Tiger"] = 2;
	sx2id ["Rabbit"] = 3;
	sx2id ["Dragon"] = 4;
	sx2id ["Snake"] = 5;
	sx2id ["Horse"] = 6;
	sx2id ["Goat"] = 7;
	sx2id ["Monkey"] = 8;
	sx2id ["Rooster"] = 9;
	sx2id ["Dog"] = 10;
	sx2id ["Pig"] = 11;
	sx2id ["Rat"] = 12;
	
	n2id ["Bessie"] = 1;
	id2n [1] = "Bessie";
	
	for (int i = 1 ; i <= n ; i ++){
		string name1, useless, dir, name2, sx;
		cin >> name1 >> useless >> useless >> dir >> sx >> useless >> useless >> name2;
		
		if (!n2id [name1]) {
			n2id [name1] = ++ top;
			id2n [top] = name1;
		}
		
		if (!n2id [name2]) {
			n2id [name2] = ++ top;
			id2n [top] = name1;
		}
		
		G [n2id [name2]]. push_back ( {n2id [name1], dir == "previous" ? -1 : 1, sx2id [sx]} );
	}
	
	dfs (n2id ["Bessie"], 0, 1);
	
	cout << abs (years [n2id ["Elsie"]]);
}

signed main () {
	int T = 1;
	
	while (T --) {
		Turn ();
	}
	return 0;
}
```

---

