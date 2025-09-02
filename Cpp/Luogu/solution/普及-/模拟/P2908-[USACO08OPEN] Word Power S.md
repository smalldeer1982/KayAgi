# [USACO08OPEN] Word Power S

## 题目描述

Farmer John wants to evaluate the quality of the names of his N (1 <= N <= 1000) cows. Each name is a string with no more than 1000 characters, all of which are non-blank.

He has created a set of M (1 <= M <= 100) 'good' strings (no

longer than 30 characters and fully non-blank). If the sequence letters of a cow's name contains the letters of a 'good' string in the correct order as a subsequence (i.e., not necessarily all next to each other), the cow's name gets 1 quality point.

All strings is case-insensitive, i.e., capital letters and lower case letters are considered equivalent.  For example, the name 'Bessie' contains the letters of 'Be', 'sI', 'EE', and 'Es' in the correct order, but not 'is' or 'eB'. Help Farmer John determine the number of quality points in each of his cow's names.

约翰想要计算他那N(l < =N <= 1000)只奶牛的名字的能量.每只奶牛的名字由不超过1000个字 符构成，没有一个名字是空字体串.

约翰有一张“能量字符串表”，上面有M(1 < =M < =100)个代表能量的字符串.每个字符串 由不超过30个字体构成，同样不存在空字符串.一个奶牛的名字蕴含多少个能量字符串，这个名 字就有多少能量.所谓“蕴含”，是指某个能量字符串的所有字符都在名字串中按顺序出现（不 一定一个紧接着一个）.

所有的大写字母和小写字母都是等价的.比如，在贝茜的名字“Bessie”里，蕴含有“Be” “si” “EE”以及“Es”等等字符串，但不蕴含“Ls”或“eB” .请帮约翰计算他的奶牛的名字 的能量.


## 说明/提示

There are 5 cows, and their names are "Bessie", "Jonathan", "Montgomery", "Alicia", and "Angola". The 3 good strings are "se", "nGo", and "Ont".


"Bessie" contains "se", "Jonathan" contains "Ont", "Montgomery" contains both "nGo" and "Ont", Alicia contains none of the good strings, and "Angola" contains "nGo".


## 样例 #1

### 输入

```
5 3 
Bessie 
Jonathan 
Montgomery 
Alicia 
Angola 
se 
nGo 
Ont 
```

### 输出

```
1 
1 
2 
0 
1 
```

# 题解

## 作者：agicy (赞：9)

# 思路

很明显，这道题的做法就是**模拟**，但一定要注意字符串的大小写和出现的判断，可用一个函数来判断是否出现。

# 代码

代码如下。

```cpp
#include<stdio.h>
#include<string.h>//头文件

char name[1001][1024],word[101][32];
//name[][]为名字，word[][]为单词
int n,m,len;

bool Appered(const char*,const char*);

int main(void){
	register int i,j,ans;//用寄存器存储更快些
	scanf("%d%d",&n,&m);//读入n,m
	for(i=1;i<=n;i++){
		scanf("%s",name[i]);//读入名字
		for(j=0,len=strlen(name[i]);j<len;j++)
			if('A'<=name[i][j]&&name[i][j]<='Z')//如果是大写字母
				name[i][j]+=32;//则转换为小写字母
	}
	for(i=1;i<=m;i++){
		scanf("%s",word[i]);//读入单词
		for(j=0,len=strlen(word[i]);j<len;j++)
			if('A'<=word[i][j]&&word[i][j]<='Z')//如果是大写字母
				word[i][j]+=32;//则转换为小写字母
	}
	for(i=1;i<=n;i++){
		ans=0;
		for(j=1;j<=m;j++)
			if(Appered(name[i],word[j]))//如果word[j]在name[i]中出现过
				ans++;//答案数量增加
		printf("%d\n",ans);//输出，记得换行
	}
	return 0;
}

bool Appered(const char *Name,const char *Word){
	int i,j,lenN=strlen(Name),lenW=strlen(Word);
	for(i=j=0;i<lenN;i++){
		if(Name[i]==Word[j])
			j++;
		if(j==lenW)
			return true;//出现
	}
	return false;//不出现
}
```

---

## 作者：超级小帆船RP (赞：6)

一道简单的字符串模拟题。

用枚举可以过。

步骤：

1.对读入的名字串和能量串进行大小写统一。

2.对于每个名字，枚举包含的能量串，找到之后立马break（算是个小小的优化）。

3.输出每个名字的得分即可。

请大家**不**要抄代码！考前要**攒人品**！！

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    char s[1008];
    int len;
}a[1008],b[108];
int score[1008];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",a[i].s+1);
        a[i].len=strlen(a[i].s+1);
        for(int j=1;j<=a[i].len;j++){
            if(a[i].s[j]>='A'&&a[i].s[j]<='Z'){
                a[i].s[j]=a[i].s[j]-'A'+'a';
            }
        }
    }
    for(int i=1;i<=m;i++){
        scanf("%s",b[i].s+1);
        b[i].len=strlen(b[i].s+1);
        for(int j=1;j<=b[i].len;j++){
            if(b[i].s[j]>='A'&&b[i].s[j]<='Z'){
                b[i].s[j]=b[i].s[j]-'A'+'a';
            }
        }
    }
    for(int i=1;i<=n;i++){
        int tot=0;
        for(int j=1;j<=m;j++){
            int now=1,L=b[j].len;
            for(int k=1;k<=a[i].len;k++){
                if(a[i].s[k]==b[j].s[now]){
                    now++;
                    if(now>L){
                        ++tot;
                        break;
                    }
                }
            }
        }
        score[i]=tot;
    }
    for(int i=1;i<=n;i++){
        printf("%d\n",score[i]);
    }
    return 0;
}

```

---

## 作者：B_Qu1e7 (赞：3)

貌似M\_sea dalao的代码时间复杂度过高??（蒟蒻：并不会判断时间复杂度）

介绍另一种方法 使用string内自带find函数

其实string内有很多find函数[详见该博客](http://www.cnblogs.com/balingybj/p/4679401.html)

这里就不多说

该find函数格式

```cpp
find(要找的字符串,开始下标)
```
这样比较方便（自己体会）

然后
好像就没什么可说的了

```cpp
#include<iostream>
using namespace std;
int n,m,tot[1001]={0};string nx[1001],en[101];
int f(string nn,string ee)
{
    int now=-1;
    string::size_type po=0;//自带size_type若find不出解返回npos 
    for(int i=0;i<ee.size();i++)
    {
        po=nn.find(ee[i],now+1);
        if(po==nn.npos)return 0;
        now=po;
    }
    return 1;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>nx[i];
        for(int j=0;j<nx[i].size();j++)if(nx[i][j]>96)nx[i][j]-=32;//转啊 
    }
    for(int i=1;i<=m;i++) 
    {
        cin>>en[i];
        for(int j=0;j<en[i].size();j++)if(en[i][j]>96)en[i][j]-=32;//全转小写 
        for(int j=1;j<=n;j++)//枚举名字 
        {
            if(f(nx[j],en[i]))tot[j]++;//内含能量串 
        }
    }
    for(int i=1;i<=n;i++)cout<<tot[i]<<endl;
}
```

---

## 作者：珅肐 (赞：2)

算是一道比较简单的模拟吧

思路与其他人差不多，主要是介绍一个不太常见的STL：

transform 这个函数是将某操作应用于指定范围的每个元素

通常形式为
	transform(str.begin(), str.end(), str.begin(),tolower);（tolower可换成别的函数）
    
但是这样的话编译的时候会出错，因为有两个tolower函数，而系统辨别不出，于是我们需要加上 (int(*)(int)),来表示调用“输入参数是一个int，返回值也是int”的函数”，这样就可以了
#### 代码：
```cpp
#include<algorithm>
#include<cstring>
#include<ctype.h>
#include<iostream>
using namespace std;
string s[1007],ss[107];
inline bool Check(string a,string b){//检查b串是否在a串a里
	for(int i=0,j=0;i<a.length();++i){//用i、j两个指针来跳
		if(a[i]==b[j])++j;//如果匹配到了，b串的指针就++
		if(j==b.length())return 1;//如果匹配到了最后，返回1
	}
	return 0;//否则返回0
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i){
    	cin>>s[i];//先把他们都大写转小写，下同
        transform(s[i].begin(),s[i].end(),s[i].begin(),(int(*)(int))tolower);
	}
    for(int i=1;i<=m;++i){
    	cin>>ss[i];
        transform(ss[i].begin(),ss[i].end(),ss[i].begin(),(int(*)(int))tolower);
    }
	for(int i=1;i<=n;++i){//n²挨个枚举
		int ans=0;
		for(int j=1;j<=m;++j) ans+=Check(s[i],ss[j]);
		cout<<ans<<"\n";//输出记得换行，还有"\n"要比endl快得多
	}
	return 0;//再见
}
```

---

## 作者：jbc392 (赞：1)

此题就是纯模拟

注意一些细节就可以了

AC code：

```
#include <bits/stdc++.h>
#define r register
using namespace std;

const int MAXN = 1010;

int n ,m;
int power[MAXN];//储存答案

string name[MAXN];//用来储存每个人的名字
string Pow[MAXN];//储存能量字符串

inline long long read()//快读
{
    long long x = 0;
    char c = getchar();
    while(!isdigit(c))
    {
        c = getchar();
    }
    while(isdigit(c))
    {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x;
}

int check(string s,string p)//判断函数
{
	int k = 0;
	for(r int i = 0;i < s.size();i++)
	{
		if(k < p.size() && s[i] == p[k]) k++;//如果有相同的则k++
	}
	if(k == p.size()) return 1;//如果k的值和能量串的长度相同则答案++
	else return 0;
}

string pre(string s)//把字符串中的大写之母转成小写
{
	string ds = "";
	for(r int i = 0;i < s.size();i++)
	{
		if(s[i] >= 'A' && s[i] <= 'Z') ds += s[i] - 'A' + 'a';
		else ds += s[i];
	}
	return ds;
}

void init()//输入
{
	n = read(); m = read();
	for(r int i = 1;i <= n;i++)
	{
		cin >> name[i];
		name[i] = pre(name[i]);
	}
	for(r int i = 1;i <= m;i++)
	{
		cin >> Pow[i];	
		Pow[i] = pre(Pow[i]);
	}
}

int main()
{
	init();
	for(r int i = 1;i <= n;i++)
	{
		for(r int j = 1;j <= m;j++) power[i] += check(name[i] ,Pow[j]);
	}
	for(r int i = 1;i <= n;i++) cout << power[i] << endl;//输出
	
	return 0;//好习惯
}
```


---

## 作者：天黑了ha (赞：1)

##### 这是一道模拟题。

##### 根据题意，可以枚举每一个能量字符串表中的字符串，若是符合则sum++,可以用一个work函数来判断这个字符串是否具有某一个字符串的能量

因为不区分大小写，我们可以把每个字符都转换成大写或是小写

下面是代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[1001];
string b[101];
bool work(string s1,string s2)//用来判断s1中是否含有s2
{
	int i=0,j=0;
	bool find=0;
	while(i<s2.size())//把s2的循环放外面
	{                 //来判断当前的字符是否能在s1中匹配
		while(j<s1.size())
		{
			if(s1[j]==s2[i])
			{
				if(i==s2.size()-1)
				{
					find=true;
				}
				j+=1;//不能直接break,不然j的值不会变
				break;
			}
			j+=1;
		}
		if(j>=s1.size()&&find==false)//要加上find=false
		{
			return false;//因为若是最后一个字符匹配，j就已经等于s1.size
		}
		i+=1;
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);//可以加快输入的速度
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<a[i].size();j++)
		{
			a[i][j]=toupper(a[i][j]);//把每个字符转换成大写
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<b[i].size();j++)
		{
			b[i][j]=toupper(b[i][j]);//把每个字符转换成大写
		}
	}
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		for(int j=1;j<=m;j++)
		{
			if(work(a[i],b[j]))//依次找寻每个字符串是否符合
			{
				sum++;//若是符合则sum++
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}
```


---

## 作者：xukuan (赞：1)

第一篇pascal题解

纯模拟，但要统一字符串大小写


```pascal
var
 i,j,m,n,ans:longint;
 s,cow:array[0..1010] of ansistring;

function work(s1,s2:ansistring):boolean;
 var
  i,j:longint;
 begin
  i{s1指针}:=1; j{s2指针}:=1;
  while i<=length(s1) do
   begin
    if s1[i]=s2[j] then inc(j);//相等
    if j=length(s2)+1 then exit(true);//全部找到
    inc(i);
   end;
  exit(false);
end;

begin
 readln(n,m);
 for i:=1 to n do
  begin
   readln(cow[i]);
   cow[i]:=lowercase(cow[i]);
  end;
 for i:=1 to m do
  begin
   readln(s[i]);
   s[i]:=lowercase(s[i]);
  end; 

 for i:=1 to n do
  begin
   ans:=0;//计数器清零
   for j:=1 to m do
    if work(cow[i],s[j]) {匹配} then inc(ans);
   writeln(ans);
  end;
end.
```

---

