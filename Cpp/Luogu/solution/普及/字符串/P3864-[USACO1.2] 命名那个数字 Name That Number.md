# [USACO1.2] 命名那个数字 Name That Number

## 题目描述

在威斯康辛州牛守志大农场经营者之中，都习惯于请会计部门用连续数字给母牛打上烙印。但是,母牛本身并没感到这个系统的便利,它们更喜欢用它们喜欢的名字来呼叫它们的同伴，而不是用像这个的语句"C'mon, #4364, get along."。请写一个程序来帮助可怜的牧牛工将一只母牛的烙印编号翻译成一个可能的名字。因为母牛们现在都有手机了，使用标准的按键的排布来把将数目翻译为文字:( 除了 "Q" 和 "Z")

```
2: A,B,C     5: J,K,L    8: T,U,V
3: D,E,F     6: M,N,O    9: W,X,Y
4: G,H,I     7: P,R,S
```
可接受的名字都被放在这样一个叫作"dict.txt" 的文件中，它包含一连串的少于 5,000个（准确地说是4617个）可被接受的牛的名字。 (所有的名字都是大写的且已按字典序排列) 请读入母牛的编号并返回那些能从编号翻译出来并且在字典中的名字。举例来说,编号 4734 能产生的下列各项名字: GPDG GPDH GPDI GPEG GPEH GPEI GPFG GPFH GPFI GRDG GRDH GRDI GREG GREH GREI GRFG GRFH GRFI GSDG GSDH GSDI GSEG GSEH GSEI GSFG GSFH GSFI HPDG HPDH HPDI HPEG HPEH HPEI HPFG HPFH HPFI HRDG HRDH HRDI HREG HREH HREI HRFG HRFH HRFI HSDG HSDH HSDI HSEG HSEH HSEI HSFG HSFH HSFI IPDG IPDH IPDI IPEG IPEH IPEI IPFG IPFH IPFI IRDG IRDH IRDI IREG IREH IREI IRFG IRFH IRFI ISDG ISDH ISDI ISEG ISEH ISEI ISFG ISFH ISFI 碰巧，81个中只有一个"GREG"是有效的(在字典中)。

写一个程序来对给出的编号打印出所有的有效名字，如果没有则输出NONE。编号可能有12位数字。


## 样例 #1

### 输入

```
4734
NMSL
GREG
LSDC
....(太多了不写了)```

### 输出

```
GREG
```

# 题解

## 作者：bjrjk (赞：24)

过了一个高三，把OI全都忘光了，写写这道题练练手。

我看这道题目的题解，大家好像都没有写的感觉太好的。所以把自己的题解发一下。里面用到了stl等等各种奇技淫巧，大家可以学习一下。^v^

题目给的翻译、输入输出根本不能看。去USACO Section 1.3节自己找一下Dict进行参考即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string> Dict; //用Dict存放所有字典中的名字
string str; //给定的编号
const char * str_trans = "2223334445556667 77888999"; //使用该C-风格字符串来存放A-Z(除去Q和Z这24个字母所对应的数字)
int main(){
    ios::sync_with_stdio(false); //只用cin/cout加快IO速度
    cin >> str;
    string tmp;
    while (cin >> tmp){ //将后面所有的字符串循环读入到tmp中，再放到Vector尾，(cin>>tmp)即可以起到读入字符串的作用，也可以起到判断文件是否到达末尾。详情请阅读C++ Primer Plus。
        Dict.push_back(tmp);
    }
    int len = str.length();
    bool global_flag = false;
    for (int i = 0; i < Dict.size(); i++){ //遍历所有字典元素，因为字典元素少
        if (len != Dict[i].length())continue; //剪枝，如果字符串位数不一样就没有必要比较。
        bool flag = true;
        for (int j = 0; j < len; j++){
            if (str_trans[Dict[i][j] - 'A'] != str[j]){ //比对字典中每个字符对应的数字是否与输入的每个数字相同
                flag = false; //不相同直接跳出循环
                break;
            }
        }
        if (flag){ //相同则输出该单词
            cout << Dict[i] << endl;
            global_flag = true;
        }
    }
    if (!global_flag){ //如果没有一个单词符合要求，就输出NONE。
        cout << "NONE" << endl;
    }
}
```

---

## 作者：玉环小姐姐 (赞：11)

研究了一下，貌似没人跟我程序一样（逃···

于是决定来发题解啦！

解法如下：

1.读入该数字字符串（然而要先扔一边去···）

2.读入这么多名字···（是有点多）

3.将所有的名字（字母串）都变成“按键串”（数字子串）

4.然后拿着在第一步里被抛弃的数字子串去比对···

5.找到一个就输出一个呗。

提示点：

1.比对这事，比的其实是结构体里的数字串，然后输出的是结构体里的字母串。当然，用数组没啥大问题，反正不排序，乱不掉。

2.关于复杂度···最多4617*14次是64638.爆不了的！

# 下有凶猛程序，请勿翻阅！
```cpp
#include<bits/stdc++.h>
using namespace std;
struct a{
    string old,new1;
}q[5100];
int main()
{
	string n,n_new="";
	cin>>n;
	for(int i=1;i<=4617;i++)
	{
		cin>>q[i].old;		
	}
	for(int i=1;i<4617;i++)
	{ 
		q[i].new1="";
		for(int j=0;j<q[i].old.size();j++)
		{
			if(q[i].old[j]=='A'||q[i].old[j]=='B'||q[i].old[j]=='C')
			{
			  	q[i].new1+='2';	  		
			}
			if(q[i].old[j]=='D'||q[i].old[j]=='E'||q[i].old[j]=='F')
			{
			  	q[i].new1+='3';			
			}
			if(q[i].old[j]=='H'||q[i].old[j]=='G'||q[i].old[j]=='I')
			{
			  	q[i].new1+='4';			
			}
			if(q[i].old[j]=='J'||q[i].old[j]=='K'||q[i].old[j]=='L')
			{
			  	q[i].new1+='5';			
			}
			if(q[i].old[j]=='M'||q[i].old[j]=='N'||q[i].old[j]=='O')
			{
			  	q[i].new1+='6';			
			}
			if(q[i].old[j]=='P'||q[i].old[j]=='S'||q[i].old[j]=='R')
			{
			  	q[i].new1+='7';			
			}
			if(q[i].old[j]=='T'||q[i].old[j]=='V'||q[i].old[j]=='U')
			{
			  	q[i].new1+='8';			
			}
			if(q[i].old[j]=='X'||q[i].old[j]=='W'||q[i].old[j]=='Y')
			{
			  	q[i].new1+='9';			
			}
		}	
	}
	bool p=true;
	for(int i=1;i<=4617;i++)
	{
		if(q[i].new1==n)
		{
	  		cout<<q[i].old<<endl;
	  		p=false;
		}
	}
	if(p)
	{
		cout<<"NONE";		
	}

	return 0;
}

```

---

## 作者：cellur925 (赞：9)

这题感觉并不需要任何算法（二分也不用），直接枚举判断就好。

我用到了一个stl-map,不了解的同学可以把它理解为一个映射，也就是说把一个数据类型的一个数据通过map映射为其他数据类型的对应数据。

提前各字母对应的数字，读入字典的时候，每读入一个判断一次就好。

由于数字长度最大为12，不想用long long 了，全部字符处理。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#include<iostream>

using namespace std;

int cnt,len;
char num[20];
char word[1000];
map<char,int>m;

void init()
{
	m['A']=2;m['B']=2;m['C']=2;
	m['D']=3;m['E']=3;m['F']=3;
	m['G']=4;m['H']=4;m['I']=4;
	m['J']=5;m['K']=5;m['L']=5;
	m['M']=6;m['N']=6;m['O']=6;
	m['P']=7;m['R']=7;m['S']=7;
	m['T']=8;m['U']=8;m['V']=8;
	m['W']=9;m['Y']=9;m['Z']=9;
	m['Q']=0;m['Z']=0;
}

bool check()
{
	int lenw=strlen(word);
	if(lenw!=len) return 0;
	for(int i=0;i<len;i++)
		if(m[word[i]]!=(int)(num[i]-'0')) return 0;
	return 1;
}

int main()
{
	scanf("%s",num);
	len=strlen(num);
	init();
    while(scanf("%s",word)!=EOF)
    {
    	if(check())
    		printf("%s\n",word),cnt++;
	}
	if(!cnt)
		printf("NONE");
	return 0;
}
```

---

## 作者：zzqDeco (赞：4)

#### 这道题比较坑，题干写得不明不白，但是仔细想想其实比较简单
#### 把数字翻译成字母，有点困难。~~（可能超时）~~
#### 有没有其他的办法呢？
### 当然可以把字母翻译成数字！！！
#### 代码如下~~（不难实现）~~
```cpp
#include<iostream>
#include<string>
using namespace std;
string a,s[4700],d[4700];
char X[]={'0','2','2','2','3','3','3','4','4','4','5','5','5','6','6','6','7','0','7','7','8','8','8','9','9','9','0'};//预处理
bool v;
int main()
{
	cin>>a;
	for(int i=0;i<=4616;i++)
		cin>>s[i];
	for(int i=0;i<=4616;i++)
	{
		d[i]=s[i];
		for(int j=0;j<=s[i].size()-1;j++)
		{
			s[i][j]=X[s[i][j]-'A'+1];//翻译
		}
	}
	for(int i=0;i<=4616;i++)
	{
		if(s[i]==a)
		{
			cout<<d[i]<<endl;
			v=1;//标记
		}
	}
	if(!v)
	cout<<"NONE";//输出反例
}
```
~~正着不行反着来~~
（管理。。。原来的题解改了一点点为什么就过不了了）

---

## 作者：Kewth (赞：4)

###### 其实这题还是很简单的哈哈，只是输入贼坑（洛谷只能用标准输入输出，那哪来的dict.txt？）
###### ~~试了半天才知道~~原来把namenum.in和dict.txt一起放在了标准输入...（先namenum.in再dict.txt,搞反了的话就只有19分（你问我怎么知道的？））
###### 说实话我第一眼看到就大呼字典树，然而看到数据大小后的我果断打了暴力，楼下用的二分，然而我暴力查找也跑得飞快啊2333
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
string name[5000];
char ft[10][4]={{},{},"ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"};
//ft[x]就是x对应的字符表，注意如果定义的是ft[10][3]会报错
int main()
{
	int n=0;//名字的数量（当然我知道都是4617个）
	while(cin>>name[n]) n++;
	string x=name[0];//第一个输入的就是namenum.in
	n--;//注意name[n]为空，也就是说while(cin)会多读入一个空字符串
	sort(name+1,name+n+1);//排序，方便按照字典序输出
	bool none=1;//是否无答案
	for(int i=1;i<=n;i++)
	{
		bool can=(name[i].size()==x.size());
        //can表示是否能对应，如果name[i]与x长度不等就直接判为不能
		for(int j=0;j<name[i].size();j++)///遍历
		{
			char c=name[i][j];
			can=can & (c==ft[x[j]-'0'][0] || c==ft[x[j]-'0'][1] || c==ft[x[j]-'0'][2]);
            //逐个比较
		}
		if(can) printf("%s\n",name[i].c_str()),none=0;//.c_str()把string转化成char*
        //只要有输出，none就可以赋值为0
	}
	if(none) cout<<"NONE\n";
}
```

---

## 作者：信息学好好玩 (赞：3)

这道题本来可以用暴力的方法，或一些大佬特别快的~~简单~~神仙方法做的，但是我~~想不开~~用的是有冲突哈希表。

如果不知道什么是哈希表，可以去百度一下。

我们可以依据字符串的每一位把字符串转成一个编码因为要保证没有冲突肯定炸空间就要用有冲突的对编码取模，如果这一位放了东西，就延后一位。

view the code:
```cpp
#define MAXL 4617
#define HMOD 32767
#include<bits/stdc++.h>
using namespace std;
string h[40005];
int mz[13]={1,37,79,117,131,177,237,277,367,377,467,477,521};
int cnt=0;
string m[10][4];
string s;

void init(){
	m[2][1]="A";m[2][2]="B";m[2][3]="C";
	m[3][1]="D";m[3][2]="E";m[3][3]="F";
	m[4][1]="G";m[4][2]="H";m[4][3]="I";
	m[5][1]="J";m[5][2]="K";m[5][3]="L";
	m[6][1]="M";m[6][2]="N";m[6][3]="O";
	m[7][1]="P";m[7][2]="R";m[7][3]="S";
	m[8][1]="T";m[8][2]="U";m[8][3]="V";
	m[9][1]="W";m[9][2]="X";m[9][3]="Y";
}

void rar(string str){
	int q=0,f=0;
	for(int i=1;i<=str.length();++i)
		q=(q+mz[++f]*(str[i-1]-'A'))%HMOD;
	while(h[q]!="")++q;//cout<<q;
	h[q]=str;
}

bool check(string str){
	int q=0,f=0,cnt=5;
	for(int i=1;i<=str.length();++i)
		q=(q+mz[++f]*(str[i-1]-'A'))%HMOD;
	while(h[q]!=str&&cnt>0)++q,--cnt;
	if(!cnt)return false;
	return true;//这里可以不要cnt,找到空位置即可，排除随机性
}

void DFS(int p,int l,string ns){
	
	if(l==p-1){
		if(check(ns))cout<<ns<<endl,++cnt;
		return;
	}
	for(int i=1;i<=3;++i){
		int pos=s[p-1]-'0';
		string nns=ns;
		ns=ns+m[pos][i];
		DFS(p+1,l,ns);
		ns=nns;
	}
}

int main()
{
	string str;
	cin>>s;
	init();
	int lens=s.length();
	for(int i=1;i<=MAXL;++i)cin>>str,rar(str); 
	DFS(1,lens,"");
	if(!cnt)cout<<"NONE";
	return 0;
}
```

总有题目可以用到这种方法吧。。。


---

## 作者：Skyjoy (赞：2)

其实USACO的题挺有意思的

卜吉豆为什么这么多童鞋用各种神奇的算法和数据结构

# 思路提供者：@bjrjk ，不给版权费

详细讲一讲这题的暴力思路：

首先，输入数字，由于不知道数的位数，所以用字符串$s$表示，计算其位数也方便。之后输入字典，用栈存省空间（注：这题字符串很多，要用$vector$，$stack$会炸）。然后把字典中的每一个字母翻译成数字与输入的数字进行对比和判断就行了。详情见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string>dict;
string s,pre="2223334445556667 77888999",t;//s是数字,pre是用于将字母转换为数字的数组 
int maxn=4617;//字典单词个数 
bool flag,flagplus;//flag是判断字典中的元素与数字是否匹配，flagplus是判断是否有解 
int main(){
	cin>>s;
	int len=s.size();
	while(maxn--){
		cin>>t;
		dict.push_back(t);//进栈 
	}
	for(int i=0;i<4617;i++){
		if(len!=dict[i].size()){//剪枝，加快速度，如大小不相同直接跳过 
			continue;
		}
		flag=1;
		for(int j=0;j<len;j++){
			if(pre[dict[i][j]-'A']!=s[j]){//判断是否与数字匹配 
				flag=0;
			}
		}
		if(flag){
			cout<<dict[i]<<endl;
			flagplus=1;
		}
	}
	if(!flagplus){//若无解输出NONE 
		cout<<"NONE";
	}
	return 0;
}
```

复赛要来了，祝看到此题解的童鞋们$CSP2019$第$2$轮认证$rp++$！！！

---

## 作者：maorui_cow (赞：2)

这道题目做起来真的非常麻烦。。。

我的方法是用bfs，一步一步的添加字母。

详情看代码

```
#include<bits/stdc++.h>
using namespace std;
string c[5005];
string a;
char g[10][4]= {{'A','B','C'},{'D','E','F'},{'G','H','I'},{'J','K','L'},{'M','N','O'},{'P','R','S'},{'T','U','V'},{'W','X','Y'}};//用这个特别爽，直接分区间
int fflag=0;
struct node
{
	int h;//当前字符长度
	string s;//字符
} q[1000005];
int flag(string s)//判断重复字符
{
	for(int i=1; i<=4617; i++)
	{
		if(c[i].size()==a.size())
		{
			int h=0;
			for(int j=0; j<s.size(); j++)
			{
				if(c[i][j]==s[j])
				{
					h++;
				}
			}
			if(h==s.size())//如果完全匹配
			{
				return 1;
			}
		}
	}
	return 0;
}
void bfs()//搜索
{
	int head=0,tail=1;
	do
	{
		head++;
		if(q[head].h!=-1)
		{
			for(int i=0; i<3; i++)
			{
				string s;
				s=q[head].s;
				s+=g[(a[q[head].h]-48)-2][i];//添加字母
				if(flag(s)==1)//不重复
				{
					tail++;
					q[tail].s=s;
					q[tail].h=q[head].h+1;//长度+1
					if(q[tail].h==a.size())
					{
						cout<<q[tail].s<<endl;
						q[tail].h=-1;//已经满足就不要往下添加了
						fflag=1;//有满足字符串
					}
				}
			}
		}
	}
	while(head<tail);
	if(fflag==0)//无解
	{
		cout<<"NONE"<<endl;
	}
}
int main()
{
	cin>>a;
	for(int i=1; i<=4617; i++)
	{
		cin>>c[i];
	}
	bfs();
	return 0;
}
```

---

## 作者：BFSBFSBFSBFS (赞：2)

题意.每1位数均可以表示为3个字母中的1个.根据编号.组合出可能的牛的名字.牛的名字必须在字典里..

附官方给出的[字典](http://train.usaco.org/usaco/namenumdict.txt "字典")...良心的提供者把字典放在了输入后面~~(我把它放进了源程序.-)~~.

表示的字母大概像标程这样储存1下..

```cpp
dic[9][4]={"ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"};
```
然后用DFS.提取每1位的数字.把3个字母都枚举1遍..

```cpp
for (int i = 0; i <= 2; i++)
{
    now[k] = dic[第k位数字,i];
    hahaDFS(k+1);//枚举下1位.
}
```
其中k是当前的位数.now[k]是第k位代表的字母.

当k > n时1个牛的名字就出来了..

之后在字典里找.如果有的话就输出来.字典序已经从小到大了..

查找用2分法.不然会超时.

```cpp
int o = 1, p = maxn;
for (int m = (o+p)/2; o <= p; m = (o+p)/2)//o~p是可能的范围.
{
    if 字典第m个名字和生成的名字相等
    {
        输出;
        退出;
    }
    else 如果字典第m个名字比生成的名字字典序大 p = m-1;//说明在m之后的字典名字比它更大.不可能相等了.
     else o = m+1;
}
```
字典是按字典序排好的.所以可以2分...

最后判断有没有无解的情况就可以了...

Diu上pas代码..

```cpp
program P3864;
 var
  a:array['2'..'9',1..3] of char=(('A','B','C'),('D','E','F'),('G','H','I'),('J','K','L'),('M','N','O'),('P','R','S'),('T','U','V'),('W','X','Y'));                 //组合.
  s:Array[0..4617] of string;
  i,upass:longint;
  sp,sk:string;
 function hahapos(sp:string):boolean;         //2分.
  var
   m,o,p:longint;                             //o~p是可能的范围.
  begin
   o:=1;
   p:=4617;
   while o<=p do
    begin
     m:=(o+p) div 2;
     if s[m]=sp then exit(true)               //找到了..
                else if s[m]<sp then o:=m+1   //排除不可能的..
                                else p:=m-1;  //排除不可能的..
    end;
   exit(false);
  end;
 procedure hahaask(sp:string;k:longint);      //DFS搜索..
  var
   i:longint;
  begin
   if k>length(sk) then                       //每1位都枚举过了..
    begin
     if hahapos(sp) then
      begin
       writeln(sp);                           //名字.判断后输出.
       upass:=1;
      end;
     exit;
    end;
   for i:=1 to 3 do
    hahaask(sp+a[sk[k],i],k+1);               //继续深搜..
  end;
 begin
  s[1]:='AARON';                              //s是字典.
  s[2]:='ABBIE';
  s[3]:='ABBOTT';
  ....                                        //省略4611行..
  s[4615]:='ZURIEL';
  s[4616]:='ZWI';
  s[4617]:='ZYTA';
  upass:=0;
  readln(sk);
  sp:='';
  hahaask(sp,1);
  if upass=0 then writeln('NONE');            //没有可行的解..
 end.
```
(ಡωಡ).


---

## 作者：Manjusaka丶梦寒 (赞：2)

相对比较简单的深搜水题

不过这题目好像有点bug啊，读文件？

名字到底有哪些？(利于打表)[戳我](http://train.usaco.org/usaco/namenumdict.txt)

对于输入的名字，我们可以开一个$map<string,int>$来确定名字是否合法，开二维数组储存每个数字可以代表的字母，记录一下输入字符串的数字顺序，从而得出搜索顺序，最后判断，记录，输出。

细节都在代码里。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define LL long long
#define mod int(1e9+7)
char ch[15];

map<string,bool> f;		//记录名字是否合法。 
int a[15],l,k,ans;
char jihe[11][3]={{},{},{'A','B','C'},{'D','E','F'},
				{'G','H','I'},{'J','K','L'},{'M','N','O'},
/*二维数组*/	{'P','R','S'},{'T','U','V'},{'W','X','Y'}};
string p[5000],str;
void dfs(string ans,int sum)
{
    if(sum==l+1)	//达到理想长度 
    {
        if(!f[ans])return;	//判断 
        else p[++k]=ans;	//合法记录 
        return; 
    }
    for(int i=0;i<3;i++)	//搜索 
        dfs(ans+jihe[a[sum]][i],sum+1);
}
int main()
{
    scanf("%s",ch+1);
    l=strlen(ch+1);
	while(cin>>str)f[str]=1;	//名字合法 
    for(int i=1;i<=l;i++)a[i]=ch[i]-'0';	//记录搜索顺序 
    dfs("",1);	//开始字符串为空。 
    if(k==0)printf("NONE");
    else
    {
        sort(p,p+1+k);	//字典序排序 
        for(int i=1;i<=k;i++)printf("%s\n",p[i].c_str());
    }
}
```

---

## 作者：zyf2224 (赞：1)

# 搜索回溯做法
### 我看到这个题居然第一个想到的是DFS？？
### 基本思想是用一个字符串存储生成的名字
### 用一个set（STL集合）存储可以被接受的名字
### 生成的名字长度等于数字长度时判断它是否再集合中
### 下面给出一段教科书式的DFS代码
```cpp
#include <iostream>
#include <string>
#include <set>
using namespace std;
string ans,num;//ans是中途生成的名字，num是给出的数字
set<string>name;//存储可接受的名字
const char key[8][3]={{'A','B','C'},{'D','E','F'},{'G','H','I'},
{'J','K','L'},{'M','N','O'},{'P','R','S'},{'T','U','V'},{'W','X','Y'}};//打表，对应键盘上的字母
bool flag;//标记是否有可接受的名字
void dfs(int);
int main()
{
	cin >> num;
	for(int i=0;i<4617;++i)
	{
		string tmp;
		cin >> tmp;
		name.insert(tmp);
	}
	dfs(0);
	if(!flag)cout << "NONE";
	return 0;
}
void dfs(int k)//k表示当前是在生成第几位字母
{
	int x = num[k]-'0'-2;//对应键盘按键
	for(int i=0;i<3;++i)//一个按键对应三个字母
	{
		ans += key[x][i];
		if(k==num.length()-1)//生成完毕
		{
			if(name.count(ans))//count()返回值是元素在集合中出现次数
			{
				flag = true;
				cout << ans << endl;
			}
		}
		else dfs(k+1);//搜索下一位
		ans.erase(--ans.end());//回溯
	}
}
```


---

## 作者：浪贱圣 (赞：0)

建一棵trie树，然后按字典序枚举情况，在看是否在树中
上代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char c[10][4],s[100],n[15];
int all,now;
bool flag;
struct d{
	int to[26],bj;
}a[100005];
void insert(){
	int p=0,y,l=strlen(s);
	for(register int i=0;i<l;++i){
		y=s[i]-'A';
		if(!a[p].to[y])a[p].to[y]=++now;
		p=a[p].to[y];
	}
	a[p].bj=1;
}
void check(){
	int p=0;
	for(register int i=0;i<all;++i){
		if(!a[p].to[s[i]-'A'])return;
		p=a[p].to[s[i]-'A'];
	}
	if(a[p].bj&&p){
		cout<<s<<endl;
		flag=true;
	}
}
void dfs(int deep){
	if(deep==all){
		s[deep]=0;
		check();
		return;
	}
	for(register int i=0;i<3;++i){
		s[deep]=c[n[deep]-'0'][i];
		dfs(deep+1);
	}
}
int m;
int main(){
	for(register int i=1;i<=24829;++i){
		scanf("%s",s);
		insert();
	}
	scanf("%s",n);
	c[2][0]='A';
	c[2][1]='B';
	c[2][2]='C';
	c[3][0]='D';
	c[3][1]='E';
	c[3][2]='F';
	c[4][0]='G';
	c[4][1]='H';
	c[4][2]='I';
	c[5][0]='J';
	c[5][1]='K';
	c[5][2]='L';
	c[6][0]='M';
	c[6][1]='N';
	c[6][2]='O';
	c[7][0]='P';
	c[7][1]='R';
	c[7][2]='S';
	c[8][0]='T';
	c[8][1]='U';
	c[8][2]='V';
	c[9][0]='W';
	c[9][1]='X';
	c[9][2]='Y';
	all=strlen(n);
	dfs(0);
	if(!flag)cout<<"NONE"<<endl;
	return 0;
}
```

---

## 作者：RicardoShips (赞：0)

这道题好像$AC$人数有点少啊

严格意义上来说，~~这道题是一道水题~~

就是把名字库转换成数字库，然后暴力匹配即可

但是楼下大佬提出了一种神奇的暴力

可以很好的锻炼码力，但是可能对新人不太友好

那么的话身为他同桌的我还是帮他填这个坑

跟其他玄学做法相比，其实思维难度真心不大 

首先，我们可以先将数字转换成可以用的名字

然后用这些名字去可以选用的名字中匹配

然而这样的最坏复杂度是多少？？？

~~卧槽~~竟然是一个常数。。。

怎么都感觉过不了，然而好像真的有人卡过去了。。。

不知道是数据太水还是$ta$太强了

所以显然是不能暴力匹配的，所以我们可以考虑二分

二分查找来缩小范围，然后就只需要匹配一个

二分的条件就是字典序匹配，从小到大

然而怎么最坏复杂度还是不对？？？

~~不管了反正这题数据水~~

```cpp
#include<bits/stdc++.h>
using namespace std;
char name[5005][15];
char k[15];
char s[15];
bool flag;
int m,n;
char num[11][4]={{},{},{'A','B','C'},{'D','E','F'},{'G','H','I'},{'J','K','L'},{'M','N','O'},{'P','R','S'},{'T','U','V'},{'W','X','Y'}};
inline void Half()
{
    int l=1,r=4618,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        int lon=strlen(name[mid]);
        flag=true;
        for(register int i=0;i<n||i<lon;++i)
        {
            if(name[mid][i]<k[i])
            {
                l=mid+1;
                flag=false;
                break;
            }
            if(name[mid][i]>k[i])
            {
                r=mid-1;
                flag=false;
                break;
            }
        }
        if(flag) break;
    }
    if(strlen(name[mid])!=n) return ;
    for(register int i=0;i<n;++i)
        if(name[mid][i]!=k[i]) return ;
    printf("%s\n",k);
    ++m;
}
inline void Dfs(int z)
{
    if(z==n)
    {
        Half();
        return ;
    }
    else
    {
        int now=s[z]-'0';
        for(register int i=0;i<=2;++i)
        {
            k[z]=num[now][i];
            Dfs(z+1);
        }
    }
}
int main()
{
    scanf("%s",s);
    for(register int i=1;i<=4617;++i)
        scanf("%s",name[i]);
    n=strlen(s);
    Dfs(0);
    if(m==0) puts("NONE");
    return 0;
}
```

---

## 作者：冰冷的心 (赞：0)

```cpp
/*
ID:15173161
TASK:namenum
LANG:C++
*/
#include<bits/stdc++.h>
using namespace std;
char  ask[15], ans[15];
char num[11][4] = {{}, {}, {'A', 'B', 'C'}, {'D', 'E', 'F'}, {'G', 'H', 'I'}, {'J', 'K', 'L'}, {'M', 'N', 'O'}, {'P', 'R', 'S'}, {'T', 'U', 'V'}, {'W', 'X', 'Y'}};
const int N = 4650;
char name[5000][16];
int cnt, len;
void check(){
	int l = 1, r = N, mid;
	while(l <= r){
		mid = (l + r) / 2;
		int leng = strlen(name[mid]);
		bool flag = true;
		for(int i = 0;i < leng || i < len; i++){
			if(name[mid][i] < ans[i]){
				l = mid + 1;
				flag = false;
				break;
			}
			if(name[mid][i] > ans[i]){
				r = mid - 1;
				flag = false;
				break;
			}	
		}
	
		if(flag)
			break;
	}
	if(strlen(name[mid]) != len){
		return ;
	}
	for(int i = 0;i < len; i++){
		if(name[mid][i] != ans[i])return ;
	}
	printf("%s\n", ans);
	cnt++;
}
void ss(int lev){
	if(lev == len){
		check();
		return ;
	}
	int now = ask[lev] - '0';
	for(int i = 0;i <= 2; i++){
		ans[lev] = num[now][i];
		ss(lev+1);
	}
}
int main(){	
	freopen("dict.txt", "r", stdin);	
	for(int i = 1;i <= N; i++){
		cin>>name[i];
	}	
	memset(ans, 0, sizeof(ans));
	freopen("namenum.in", "r", stdin);
	freopen("namenum.out", "w", stdout);	
	scanf("%s", ask);
	len = strlen(ask);
	ss(0);
	if(cnt == 0){
		printf("NONE\n");
	}
	return 0;
}
```

---

## 作者：_louhc (赞：0)

题目 [Click Here](https://www.luogu.org/problemnew/show/P3864)  
这是将名字转换位数字编码(注意int存不下，要用long long以上)，然后用map(I LOVE STL)存储用这个数字可得到的名字。  
洛谷版代码详见：https://www.luogu.org/record/show?rid=7670169 
  
[dict.txt](http://train.usaco.org/usaco/namenumdict.txt)  
  
这里是[USACO](http://train.usaco.org/usacoprob2?S=namenum&a=csG04ZnFfL7)里提交通过的代码
```cpp
/*
ID:louhanc1
LANG:C++
TASK:namenum
*/
//USACO要求的格式，不必管它
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<string>
#include<stack>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<map>
using namespace std;
#define K 103
#define ULL unsigned long long

inline ULL read(){//没有负数，就把flag去掉了(实际上是懒)
	ULL ans(0); char t(getchar());
	while( !isdigit(t) ) t = getchar();
	while( isdigit(t) ){
		ans = ans * 10 + ( t ^ '0' );
		t = getchar();
	}
	return ans;
}

int key[]={0,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,0,7,7,8,8,8,9,9,9,0};
//key是每个字符转化成的数字
map<ULL, vector<string> > f;//因为可得到的名字不止一个，所以用vector
ULL N;
string name;
int ans;
vector<string> tmp;//因为map每次访问f[N]都要一定的时间，所以把结果先存起来

int main(){
	freopen( "dict.txt", "r", stdin );//USACO里在编译环境中给了dict.txt 但在洛谷中直接附在便准输入输出后面
	while( cin >> name ){
		ULL t(0);
		for ( int i = 0; i < name.size(); ++i )
			t = t * 10 + key[name[i] - 'A' + 1];//转换成数字
		f[t].push_back(name);//name能由t转换而来，进f[t]
	}
	freopen( "namenum.in", "r", stdin );
	freopen( "namenum.out", "w", stdout );
	N = read();
	tmp = f[N];
	if ( !tmp.size() ) printf( "NONE\n" );//没有满足的名字
	for ( int i = 0; i < tmp.size(); ++i ) cout << tmp[i] << '\n';
	return 0;
}
//finished on 2018/6/3
//at 14:48
```

---

## 作者：Patrickpwq (赞：0)

哈希表处理
在index的时候只取后三位就行了 转化成26进制
大家看一下代码吧

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

const int hh=19240817;
int n;
string hx[500001],prep,s,s1;
bool ok;
const char hhd[10][4]=
{
   ' ',' ',' ',' ',	
   ' ',' ',' ',' ',	
   ' ','A','B','C',	
   ' ','D','E','F',	
   ' ','G','H','I',	
   ' ','J','K','L',	
   ' ','M','N','O',	
   ' ','P','R','S',	
   ' ','T','U','V',	
   ' ','W','X','Y',

};

int index(string ss)
{
    int h=0,i;
	if(ss.size()>1)
	{
		h=h*27+(ss[0]-64);
		h=h*27+(ss[ss.size()-1]-64);
		h=h*27+(ss[ss.size()-2]-64);
	}	
	else for(i=1;i<=3;i++) h=h*27+(ss[0]-64);
	h=h%hh;
	while(hx[h]!=ss && hx[h].size()>0) h++;
	return h;
}

bool find(string ss)
{
	if(hx[index(ss)]==ss) return true;
	else return false;
}

void work(int k)
{
	int i;
	char c;
	for(i=1;i<=3;i++)
	{
		c=hhd[prep[k-1]-'0'][i];
		s1=s1+c;
		if(s1.size()==prep.size()) 
		{
			if(find(s1))
			{
				cout<<s1<<endl;
				ok=true;
			}
		}
		else work(k+1);
		s1.erase(s1.size()-1,1);
	}
}

int main()
{	
	cin>>prep;
	while(cin>>s)
	{
		hx[index(s)]=s;
	}
	ok=false;
	work(1);
	if(!ok) printf("NONE");
	
	return 0;
}
```

---

## 作者：Jjxxz233 (赞：0)

看了一下，发现大家在把字母转成键盘数字的时候都采用的是打表（~~话说这个算打表吗~~），没有和我一样的方式

###### 所以我就来抛块砖啦 想给大家分享一下我写的这个chr2int

```cpp
int chr2int(char x)
{
    if(x <'Q')	return ((int)x-'A'  )/3+2;
    else 		return ((int)x-'A'-1)/3+2;
    //要注意，字母表里面没有'Q'，要跳过Q的空格
 } 
```

主程序部分，和大家整体思路都基本相同，~~毕竟数据这么小~~，枚举每一个输入的名字，再转成数字，和输入的数字比较。

还有一点，编号有12位数，**int**最大10^9，会爆掉~~然后得到74分~~，所以得用**long long**。当然使用**string**或者**char**来储存也是可以的

## 最后总代码

```cpp
#include <string>
#include <cstdio>
#include <iostream>
#include <cmath> //要用到log10

using namespace std;

//本人比较懒，所以这种东西写了很多
#define LL unsigned long long
#define RI register int
#define pr(x) cout<<x<<endl

bool debug = 0;

LL n;
int l2;
int c[15];
int chr2int(char x)
{
    if(x <'Q')	return ((int)x-'A')/3+2;
    else 		return ((int)x-'A'-1)/3+2;
 } 
 
bool check(string name)
{
//	pr("checking "<<name<<" ...");
    int l=name.length() ;
    if(l!=l2)   return 0;	//长度不一样直接毙掉
    for(RI i=0;i<l;i++)
    {
        if(chr2int(name[i])!=c[i])  
		{
//			pr(name<<" not ok");
			return 0;
		}
        
    }
//    pr(name<<"  is OK");	
    return 1;
}

int main()
{
    cin>>n;
    string t;
    l2=log10(n)+1;
    LL tmpn=n;
    for(int i=l2-1;i>=0;i--)
    {
        c[i] = tmpn%10;
        tmpn/=10;
    }
    bool NONE=1;
    for(RI i=1;i<=4617;i++)
    {
        cin>>t;
        if(check(t))
        {
            pr(t);
            NONE=0;
        }
    }
    if(NONE)    pr("NONE");
    //不要忘记判断没有名字
    return 0;
}
```




---

