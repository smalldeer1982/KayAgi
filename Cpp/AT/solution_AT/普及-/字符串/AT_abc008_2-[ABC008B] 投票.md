# [ABC008B] 投票

## 题目描述

题目大意
某个组织进行了选拔领导人的选举。组织由n人组成，每个人都写了最领导的人物的名字。投票数最多的人的名字就是领袖。如果有多个得票数最多的人物，输出其中一个即可。

## 说明/提示

1<=名字长度<=50


感谢@Andysun06  提供的翻译

## 样例 #1

### 输入

```
4
taro
jiro
taro
saburo```

### 输出

```
taro```

## 样例 #2

### 输入

```
1
takahashikun```

### 输出

```
takahashikun```

## 样例 #3

### 输入

```
9
a
b
c
c
b
c
b
d
e```

### 输出

```
b```

# 题解

## 作者：翼德天尊 (赞：38)

**想练习map ? 就这道题了！**

个人认为这道题可以改名为：【模版】map（日版）了。

废话不多说，开始我们这道题的题解吧！

------------


### STEP 1 审题

1.投票，选票数最大的。

2.给人名，比较票数。

不用想了，肯定用map！

------------


### STEP 2 介绍map

```
map，一个另类的数组。
声明格式：map<数据类型1，数据类型2> 变量名
赋值格式：变量名[数据类型1]=数据类型2

好处：可以对应两个不同格式的变量，例如可以立马调出某一个字符串对应的数等
```

------------

### STEP 3 本题AC代码及详细注释
```
//是不是很短呢？
#include<bits/stdc++.h>//万能头棒棒
using namespace std;
int n,maxn;//分别储存选票数量以及最大票数
string name;//储存当前最大票数对应的人名
map<string,int> m;//我们的map
int main(){
    scanf("%d",&n);//正常输入
    for (int i=1;i<=n;i++){
    	string a;
    	cin>>a;
    	m[a]++;
    	if (m[a]>maxn){//如果加了一票后的某位候选人的票数大于现在的最大票数
    		maxn=m[a];
    		name=a;//修改数据
		}
	}
	cout<<name<<endl;//输出最大票数的名字
    return 0;//好习惯从我做起
}
```


------------
### STEP 4 完结撒花！
本题的代码是不是很简单呢？

如果还有不懂的地方，可以在评论区留言，我会第一时间回复哒！

如果看完本题解后很明白，那么就点个赞纪念一下自己的成长吧！


---

## 作者：lzqy_ (赞：7)

# 给大家一个不一样的map做法

## 题意：

有$n$张选票，每张选票投给一位领导人，请输出票数最多的领导人的名字。

## 分析

**先简单介绍一下$map$：**

----
$map$是一种特殊的数组。

普通的数组:
```
a[int]--->(int/string/char……)
```
$map$数组：
```
a[int/string/char……]--->(int/string/char……）
```
(更具体的介绍看[这里](https://www.cnblogs.com/fnlingnzb-learner/p/5833051.html))

----
很明显，在这里，我们可以用$map$来实现领导人名字和票数之间的映照，代码如下：
```
string s;//定义字符串
map<string,int>m;//定义map数组
//此处'<string,int>'表示这个数组以字符串为下标，存储整形
for(int i=0;i<n;i++)
{
   cin>>s;//读入领导人名称
   m[s]++;//对应的选票++
   //（此处也可写成m[s]=m[s]+1）
}
```
**下一步，如何统计谁的票数多呢？**

这里我们可以用迭代器来实现。但是，作为一个不太熟悉指针的人，我换了个方法：

我们再开一个$string$型的数组（即$int$下标，存储$string$），反过来存储领导人的名字，与$map$数组来相互对应，来遍历每一个领导人。

注：领导人的名字在选票里不止出现一次，为了效率更高，记得去重哦。

## 代码
没有代码还不是很好理解，上代码：
```
#include <bits/stdc++.h>
using namespace std;
string a[100000];//存储每个领导人的名字
int cnt;//计数器，记录共有几个领导人
map<string,int>m;//定义map数组 
int main()
{
  string s;
  int n;
  cin>>n;
  for(int i=0;i<n;i++)
  {
   cin>>s;//读入选票
   if(m[s]==0)//去重
   //m[s]==0的意思是这个领导人的名字是第一次出现
   {
   	cnt++;//又多了一个领导人
   	a[cnt]=s;//存储下来
   }
	m[s]++;//这个领导人选票++
  }
  int Max=-1;//把最大值先定义到最小
  string ans;
  for(int i=1;i<=cnt;i++)
  if(Max<m[a[i]])//如果领导人a[i]的选票比Max还要多
  Max=m[a[i]],ans=a[i];
  //更新Max的值，更新选票最多的领导人的名字
  cout<<ans<<endl;//输出答案
  return 0;
}

```
### 几点注意：

- 题目末尾要换行

- 在使用$map$的时候，一定要理清思路，想清楚下标是什么、存储的又是什么。

- 其实，这道题目不去重也是可以的。但是，即使能AC，我们也尽量寻找更快的方法。

### 祝大家AC愉快！

---

## 作者：zjyqwq (赞：6)

### AT899 投票 题解
我又来发题解了！！！

------------
#### 整体思路
使用排序使这个序列变得有序，然后再用最长平台长度。

每个长度便是这个名字的个数。


------------
#### 提醒

- 最长平台长度要多做一次，使序列最后的名字不被遗漏。

- AT要换行！！！


------------
#### 代码
```Pascal
//珍爱生命，请勿抄袭。
var
n,i,x,max:longint;
t,maxx:string;
a:Array[0..100000]of string;//定义部分，无话可说。
procedure sort(l,r:longint);//快速排序。
var
i,j:longint;m,t:string;
begin
i:=l;j:=r;m:=a[(i+j)div 2];
while i<=j do
begin
while a[i]<m do inc(i);
while a[j]>m do dec(j);
if i<=j then
begin
t:=a[i];
a[i]:=a[j];
a[j]:=t;
inc(i);
dec(j);
end;
end;
if j>l then sort(l,j);
if i<r then sort(i,r);
end;
 begin
  readln(n);
  for i:=1 to n do
   readln(a[i]);//输入
  sort(1,n);
  for i:=1 to n+1 do
   if a[i]=t then x++;//同一个人，个数加一
   else
    begin
     if x>max then begin max:=x;maxx:=t;end;
     x:=1;
     t:=a[i];
    end;//换新人了，比较大小，重新开始
  write(maxx);//输出
 end.

```
结束了！！！

---

## 作者：MarchKid_Joe (赞：5)

康到很多 DaLao 用 map 做的，我整个排序式统计吧。~~“水”~~
# 1. 题意
题意很简单，就是一个**统计**题目，统计票数**最多**的任意一人
# 2. 思路
- 变量解释

  我们可以先用 s[n + 1] 存储名字，用 ansn 存储最多票数的那个人，用 maxn 来存储最大值并比较比较，用 t 来存储不同人的个数。
- 实现

  先对所有名字排序一遍，然后只需要判断相邻的两个名字是否相同，若相同，计数器+1；如果不相同，则和最大值比较，若大于最大值，存下名字，更改最大值。

# 3. Ac代码
```cpp
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
string s[52] , ansn;
int maxn , t = 1 , n;
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i ++) cin >> s[i];
	sort (s + 1,s + n + 1);
	for (int i = 2;i <= n + 1/*注意+1，否则会少存一个值*/;i ++)
	{
		if (s[i] != s[i-1])
		{
			if (t > maxn)
			{
				maxn = max (maxn,t);
				ansn = s[i-1];
			}
			t = 1;
		}
		else t ++;
	}
	cout << ansn << endl;
	return 0;
}
```
友情提示：~~AT特色~~ 注意"**\n**";

---

## 作者：Nt_Tsumiki (赞：4)

### 题意
投票，有 $n$ 个人参与，投了若干人（少于 $n$ 人），被投的每个人的名字为字符串，问哪个人被投的次数最多。
### 做法
看完题首先想到的是桶排，但是由于输入的是字符串，所以一般的桶排肯定行不通，就需要用到一个神奇的东西：`map`。

`map`是什么呢，在这道题里你可以理解为是一个下标为字符串的数组，具体定义如下。
```
map<string,int> m;
```
但实际上，它的意义是定义一下标为任何类型的数组，具体说明如下。
```
map<下标类型,数组类型> 数组名称;
```
解决了这个，这道题就非常简单了，首先输入数据，然后桶排，再循环判断最大，最后输出，上代码。
### Code
```cpp
#include<map>
#include<string>
#include<iostream>

using namespace std;
map<string,int> m;//map
string str[51];
int n;

int main() {
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>str[i];
		m[str[i]]++;
	}
	int maxn=0;
	string name; //答案
	for (int i=1;i<=n;i++) {
		if (m[str[i]]>maxn) {//找最大
			maxn=m[str[i]];
			name=str[i];
		}
	}
	cout<<name<<endl;
	return 0;//完美结束
}
```
### 总结
考察对于`map`的掌握，没有太大坑点。

---

## 作者：A_Plus_Gu (赞：4)


$\color{purple}\text{考察内容：}$ 结构体排序、字符串（也可以用STL）

$\color{orange}\text{思路：}$ 

1. 输入并统计出现次数
2. 对出现次数进行排序
3. 输出票数最高的那个人

$\color{red}\text{贴上AC代码：}$ 
```
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
struct people{
	string name;//名字
	long time;//出现次数
}p[10001];
string x;
long long n,k=1;
bool cmp(people a,people b){//结构体排序
	return a.time>b.time;//按照出现次数进行排序
}
int main(){
	cin>>n;
	cin>>x;//先输入第一个名字，如果放在循环里面，会WA掉三个点
	p[1].name=x;//记录名字
	p[1].time=1;//出现次数为1（第一个数嘛）
	for(int i=2;i<=n;i++){
		cin>>x;//依次输入第2~n个名字
		long f=0;//后面会说
		for(int j=1;j<=i;j++){//判断此人的名字是不是第一次出现
			if(p[j].name==x){
            	//如果此人名字不是第一次出现的话，那么它的出现次数加1，同时标记
				p[j].time++;
				f=1;
				break;
			}
		}
		if(f) continue;//如果不是，就直接跳过后面这一段
		//如果此人的名字是第一次出现的话，就要记录他的名字，并且出现次数要改为1
        k++;
		p[k].name=x;
		p[k].time=1;
	}
	sort(p+1,p+n+1,cmp);//排序
	cout<<p[1].name<<endl;//输出
	return 0;
}
```


---

## 作者：cjZYZtcl (赞：3)

## 这是一道字符串处理题
这里讲两种做法。

### 1：暴力模拟
我们先把字符串存起来，然后二重循环枚举每一个字符串和它之后的字符串，然后比较一下，如果两个字符串相等就把当前个数累加1。

第一重循环枚举完之后与最大值比较，如果大的话就把最大值改为当前值，然后把最大字符串改成当前字符串。

注意：第一重循环每做一次就要把统计当前个数的变量清零。

由于数据小，所以可以过。

### AC Code（楼主不太会C++字符串操作，于是手码了字符数组）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[55];
char b[55][55], strans[55];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
bool bj(int x, int y){
	for(int i = 1; i <= max(a[x], a[y]); i++){
		if(b[x][i] != b[y][i]) return false;
	}
	return true;
}
signed main(){
	int n = read(), s, ans = 0, lenans = 0;
	char ch = getchar();
	for(int i = 1; i <= n; i++){
		while(ch < 'a' || ch > 'z') ch = getchar();
		a[i] = 0;
		while(ch >= 'a' && ch <= 'z'){
			b[i][++a[i]] = ch;
			ch = getchar();
		}
	}
	for(int i = 1; i <= n; i++){
		s = 1;
		for(int j = i + 1; j <= n; j++){
			if(bj(i, j)) s++;
		}
		if(s > ans){
			ans = s;
			lenans = a[i];
			for(int j = 1; j <= a[i]; j++){
				strans[j] = b[i][j];
			}
		}
	}
	for(int i = 1; i <= lenans; i++) putchar(strans[i]);
	putchar('\n');
}
```
### 2.桶
由于关键字是字符串，所以用map来存每一个字符串出现的次数。

每存一次与最大值比较一次，最后输出出现次数最多的字符串即可。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<string, int> a;
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), ans = 0;
	string s, strans;
	for(int i = 1; i <= n; i++){
		cin>>s;
		a[s]++;
		if(a[s] > ans){
			ans = a[s];
			strans = s;
		}
	}
	cout<<strans<<endl;
}
```
### 温馨提示：AT输出要换行！！！

---

## 作者：HsKr (赞：3)

发现有用map的，但没人使用迭代器

```cpp
//maxn记录最大票数，maxs记录最大值所对应的名字
#include<iostream>
#include<map>
using namespace std;
map<string,int> m;
int main(){
	int n,maxn=-1;
	string x,maxs;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x;
		m[x]++;//x的票数加1
	}
	for(map<string,int>::iterator it=m.begin();it!=m.end();it++){
//有点复杂，定义一个类型为map<string,int>的迭代器，从m的开头开始，直到末尾（左闭右开）
		if(it->second>maxn){//如果票数更大
			maxn=it->second;//更新票数
			maxs=it->first;//更新名字
		}
	}
	cout<<maxs<<endl;//输出最大票数的人
	return 0;
}
```

---

## 作者：wushuang0828 (赞：2)

**思路：先输入名字，在跟之前存在a数组中的比较，有没有相同的，如果相同的就累加b数组中的相应元素，如果不相同，就记录在a、b数组中，b数组中的加1**

如果听不懂，可以看代码，如下：
```pascal
var
 n,i,j,k,x,m,max:longint;
 s1:string;
 p:boolean;
 a:array[0..51] of string;
 b:array[0..51] of longint;
begin
 readln(n);
 for i:=1 to n do
  begin
   readln(s1);//输入
   p:=true;//用假设法来寻找输入的名字在之前有没有出先过
   for j:=1 to k do
    if a[j]=s1 then begin p:=false; x:=j; end;
   if p=true then begin inc(k); a[k]:=s1; inc(b[k]); end//如果没有出现过，就在a数组中记录下心得名字，在b数组中对应的元素也加1
             else inc(b[x]);//如果出现过，就在出现过的对应b数组中加1
  end;
 for i:=1 to k do
  if b[i]>max then begin max:=b[i]; m:=i; end;//寻找最大值，并记录下标
 writeln(a[m]);//输出票数最多的人的名字
end.
```

---

## 作者：_Qer (赞：2)

本题可以用一个自定义结构体来存每个候选人的情况，用一个string（代码中的name）来存名字，一个int（代码中的tic）来存票数。

循环N次，每次输入一个名字，在已有的候选人名单中查找，发现有这个人就把他的票数+1，没找到就在名单中加一个人，并且把他的票数置为1。

最后用一个循环，找名单中票数最多的人。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;//总票数
struct precident{//结构体，我不会解释，不知道就百度吧
    string name;//名称
    int tic=0;//票数
}p[100];
//定义50个即可，因为总票数不会超过50，所以最多50个候选人（大一点保险）
int m;//当前名单上有多少人
string in;//输入的投票对象
int main(){
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>in;//输入投票的对象
        bool neww=true;
        //neww若为1(true)代表是新名字，否则为已有名字
        for(int i=0;i<m;++i){//在名单中查找
            if(in==p[i].name){//找到了这个人
                ++p[i].tic;//投一票
                neww=false;//说明这不是新人
                break;//节约时间
            }
        }
        if(neww){//如果没找到
            p[m++].name=in;//名单中下一个人为现在这个
            //不能理解？
            //上面的代码等同于：
            //p[m].name=in;++m;
            ++p[m].tic;//票数记得加一
        }
    }
    int maxn=0,winner=0;
    //maxn为当前最高票数，winner为最高票数者的编号
    //编号初始化为0（下标1开始就初始化为1）
    //原因：如果所有票都是给一个人，不初始化就会炸
    //（我也不知道为什么，哪位大佬知道麻烦评论一下谢谢）
    for(int i=0;i<m;++i){
        if(p[i].tic>maxn){//如果当前候选人的票数高于之前最高的
            maxn=p[i].tic;
            winner=i;
            //更新最高数据
        }
    }
    cout<<p[winner].name<<endl;//输出名字即可
    return 0;
}
```

---

## 作者：StObOtZ (赞：1)

# **AT899 投票 题解报告**

 本题一看就是用Map做的~~水~~题啦。
 
 不应多讲，直接用Map存储，然后找最大。
 
 **注意**：每存一次与最大值比较一次，每一次出现最多的名字和数量都要存，最后输出出现次数最多的字符串即可。
 
 
##  **AC Code**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
map<string, int> a;
signed main(){
	cin>>n;
	string s, maxs;
	for(int i=1;i<=n;i++){
		cin>>s;
		a[s]++;
		if(a[s]>ans){
			ans=a[s];
			maxs=s;
		}
	}
	cout<<maxs<<endl;
}
```

**为了观赏方便，就不加快读快输了。**

大家顺便也可以把[AT5274](https://www.luogu.com.cn/problem/AT5274)刷了，方法一样。

---

## 作者：Waaifu_D (赞：1)

## 题意简述

给我们 $n$ 个人的名字，求哪个人的名字出现次数最多，输出这个人的名字

## 思路

如果这题让我们输出最多的次数，那么这题肯定只是个橙题，但是让我们输出最多次数的名字，我们就要考虑如何存储每个人的名字

这时，我们肯定会想到 _STL_ 中一个神奇的容器，那就是 $map$ 

$map$ 的神奇之处在于，它的“下标”可以是任意数据类型，相当于加强的数组，本来数据的下标只可以是 $int$ 类型，但是依靠于 $map$ 的强大，我们可以用 $string$ 类型来做本题的 $map$ 下标

## Code

```cpp
#include<cstdio>
#include<iostream>
#include<map>
#include<cstring>//map和string的库名
using namespace std;
int n,sum,maxx=-114514;//maxx是用来求最大次数的
map<string,int> x;//map定义，前面的是下标类型，后面的是存的类型
string k[55],ans;//存名字
int main()
{
	cin>>n;
	for(int i=1; i<=n;i++)
	{
		string s;
		cin>>s;
		if(x[s]==0) sum++;//统计一共有几个名字存出现
		x[s]++;//相应的map值++
		k[i]=s;//存储下名字
	}
	for(int i=1; i<=sum;i++)//求出现次数最多的名字
	{
		if(x[k[i]]>maxx)//如果比他大，就更新最大值和最大值的名字
		{
			maxx=x[k[i]];
			ans=k[i];
		}
	}
	cout<<ans<<endl;//输出（记得换行）
	return 0;
}
```


---

## 作者：hjxxcbq (赞：1)

### 我看到n<=50时，我暗暗欢喜，因为我可以暴力枚举了。
这道题不算很难，代码长度只是23行罢了。

不用什么结构体啦，map啦。（~~反正我不会~~）

只要一个一个判断就OK啦。

每判断一次，要把它隔离啦，如果发现是隔离的人，立刻退出循环啦。

变量提醒：**n就是组织由n人组成，s就是来记票最多的，a[51]是每个人都写了最领导的人物的名字，b就是最多的人，l就是来记有多少个人**。

```
#include<bits/stdc++.h>//万能头文件
using namespace std;//使用标准命名空间
int n,s;
string a[51],b;//前面已经说得很清楚了
int main()
{
cin>>n;输入n
for(int i=0;i<n;i++)cin>>a[i];//输入a[i]
for(int i=0;i<n;i++)//暴力开始啦
{
int l=1;//就是自己，也算是一个。
for(int j=0;j<n;j++)
{
if(a[i]==" ")break;//如果是隔离的人，立刻退出循环
else 
if(i!=j)if(a[i]==a[j])l++,a[j]=" ";//如果是一样，票数加1。
}
if(s<l)s=l,b=a[i];//如果l比s大，换人了！
a[i]=" ";//变为隔离的人了
}
cout<<b<<endl;//输出最多票的人，AT题要换行！
return 0;//注意要return 0;
}
```

**如果发现题解有问题，请私信我。**

---

## 作者：1lgorithm (赞：0)

#### 这道题可以用哈希！

看到各位大佬都用map，我就用哈希给大家写一篇题解。

众所周知，哈希可以加快比较的速度，但是为了避免哈希冲突，所以我们可以使用双模数哈希。

代码：

```cpp
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
#define ll long long
struct str{
	ll h1,h2,cnt;
	string s;
};
bool cmp(str a,str b){
	return a.cnt>b.cnt;
}
str a[51];
ll cnt=0;
ll hassh(string s,ll mod){
	ll now=1,sum=0;
	for(int i=0;i<s.size();i++){
		sum=(sum+s[i]*now)%mod;
		now=now*27%mod;
	}
	return sum;
}
void add(string s){
	string s;
	cin>>s;
	ll x=hassh(s,233);
	ll y=hassh(s,1e9+7);
	for(ll i=1;i<=cnt;++i){
		if(a[i].h1==x&&a[i].h2==y){
			++a[i].cnt;
			return ;
		}
	}
	a[++cnt].s=s,a[cnt].cnt=1,a[cnt].h1=x,a[cnt].h2=y;
	return ;
}
int main(){
	ll n;
	cin>>n;
	string s;
	while(n--) add(s);
	sort(a+1,a+cnt+1,cmp);
	cout<<a[1].s<<endl;
}
 
```


---

## 作者：happybob (赞：0)

~~管理你让我怎么排版？~~

- STL！！！
- map是本题的通常解法，也是很简单的
- 每次将候选人的票数++，用迭代器遍历一遍，找到最大值以及答案

代码：

```cpp
#include <iostream>
#include <map>
#include <cstring>
using namespace std;

map<string, int> mp;

int main()
{
    int n;
    cin >> n;
    while(n--)
    {
        string s;
        cin >> s; mp[s]++;
    }
    int max = -1;
    string ans = "";
    for(map<string, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
        if(it -> second > max)
        {
            max = it -> second;
            ans = it -> first;
        }
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：gdjcwsk (赞：0)

这题我一开始想用桶排，但不久之后就发现这是一道~~经典的~~ $map$ 好题。

本题思路：先定义一个 $map$ 来计算每种字符串出现的次数，然后在打擂台求出最大的。

废话不多说，先上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
map<string,int>m;
const int maxn=1000005;
int mnum;//票数最多的人的票数
string a[maxn],ma;//a[maxn]表示输入的n票，ma表示票数最多的人
int main()
{
    int n;//n张选票
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        m[a[i]]=0;//每输入一张选票，直接映射为0（map的初始化）
    }
    for(int i=0;i<n;i++)
    {
        m[a[i]]++;//初始化之后才能数票数
    }
    for(int i=0;i<n;i++)//打擂台
    {
        if(m[a[i]]>mnum)//注意千万不要把">"写成">="
        {
            mnum=m[a[i]];
            ma=a[i];
        }
    }
    cout<<ma<<endl;
    return 0;
}
```
本蒟蒻的这片题解就要结束了，有什么问题请私信我，我会继续改正。

---

