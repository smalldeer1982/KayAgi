# [USACO1.1] 贪婪的送礼者Greedy Gift Givers

## 题目描述

对于一群 $n$ 个要互送礼物的朋友，GY 要确定每个人送出的钱比收到的多多少。在这一个问题中，每个人都准备了一些钱来送礼物，而这些钱将会被平均分给那些将收到他的礼物的人。  

然而，在任何一群朋友中，有些人将送出较多的礼物(可能是因为有较多的朋友)，有些人有准备了较多的钱。  

给出一群朋友，没有人的名字会长于 $14$ 字符，给出每个人将花在送礼上的钱，和将收到他的礼物的人的列表，请确定每个人收到的比送出的钱多的数目。


## 说明/提示

【数据范围】  
$1\le n \le 10$

题目翻译来自NOCOW。

USACO Training Section 1.1


## 样例 #1

### 输入

```
5
dave
laura
owen
vick
amr
dave
200 3
laura
owen
vick
owen
500 1
dave
amr
150 2
vick
owen
laura
0 2
amr
vick
vick
0 0
```

### 输出

```
dave 302
laura 66
owen -359
vick 141
amr -150
```

# 题解

## 作者：Aoki_灏 (赞：82)

这里萌新

不会什么高级方法

全是非常土的方法所以简单易懂

这里重新认真地开始写题解

```cpp
#include <bits/stdc++.h>
#define N 1000000
using namespace std;
int n,x,h;
char s[N],t[N];
struct node// 结构体存名字和钱 我爱结构体
{
    char name[20];
    int sum;
};
struct node q[N];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>q[i].name;
   for(int i=1;i<=n;i++)
   {
       scanf("%s",s);
       for(int j=1;j<=n;j++)
          if(strcmp(s,q[j].name)==0){x=j;break;}//比较名字，看是谁，记下j，千万不要只比较首字母。我之前就这样偷懒然后没a
       int a,b;
       cin>>a>>b;
        if(b==0)continue;//这里注意一定要判断，毕竟0不能做除数，要不然会炸
       int y=a/b;
       int m=y*b;//算每人分到的钱数
       q[x].sum-=m; //减钱
       for(int k=1;k<=b;k++)
       {
          scanf("%s",s);
          for(int g=1;g<=n;g++)
              if(strcmp(s,q[g].name)==0){h=g;break;}//分钱 同上不要只比较首字母mm
            q[h].sum+=y;//加钱
       }
   }
    for(int i=1;i<=n;i++)
        cout<<q[i].name<<' '<<q[i].sum<<endl;
    return 0;
}
//最后再次说明这题我的方法非常土鳖。。。易懂真的、
//注意的事项前面都写了
```

---

## 作者：BlueArc (赞：51)

###为什么每人用map?

###STL大法 映射:map

定义一个关联数组map<string,int> cnt来表示名字到数目的映射

输入时只要对cnt[name]操作,很容易维护

**要注意判断收到这个人礼物的人的个数是否为0，否则会RE floating point exception**

附上简洁的代码:


```cpp
#include"iostream"
#include"cstdio"
#include"map"
using namespace std;
string name[12];
map<string,int> cnt;
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<=n;i++)
 cin>>name[i];
 for(int i=1;i<=n;i++)
 { 
 string s;
 int money,p;
 cin>>s>>money>>p;
 int num;
 if(p!=0) num=money/p;//特判
 else num=0;
 cnt[s]-=num*p;//money/p*p和money*p/p结果是不同的
  for(int j=1;j<=p;j++)
  {
   string person;
   cin>>person;
   cnt[person]+=num;      
  }     
 }
 for(int i=1;i<=n;i++)
 cout<<name[i]<<" "<<cnt[name[i]]<<endl;
}

```

---

## 作者：楚泫 (赞：26)

## **【身为蒟蒻，发个给小白的易懂题解！】** 
- 看到题解区有很多超级长的于是发一下qwq
- 没有任何难懂的地方QAQ，具体都写在注释了x
### 第一次写请多关照orz ||**代码如下**：
------------
```cpp
#include<iostream>
#include<cstring>
using namespace std;
struct person{
	string name;
	int money;
}a[12];			//存储每个人的名字和钱数 
string name_out,name_in;
int n,mout,num,sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].name;//输入所有人名字 
	for(int i=1;i<=n;i++){
		sum=1;
		cin>>name_out>>mout>>num;//输入姓名，钱数，收礼人数 
		if(!num||!mout) continue;//如果给别人的钱数或人数为0，不进行运算 
		for(int j=1;j<=num;j++){
			cin>>name_in;//收礼人姓名 
			for(int k=1;k<=n;k++){
				if(sum&&a[k].name==name_out){
					sum--;//用sum保证只减去一次 
					a[k].money-=mout/num*num;//表示减去给别人的钱数 
				}
				if(a[k].name==name_in) a[k].money+=mout/num;//增加钱数 
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<a[i].name<<" "<<a[i].money<<endl;//输出 
}
```

---

## 作者：yjjr (赞：15)

方法
可以进行优化，不过一般暴力就能过，个人认为用记录类型的数组比较方便，一个存姓名，另一个存钱数，别忘了如果不能整除的剩余钱数归算到原本的人上，例如200 div 3 还有余，余下的2块钱还在Dave上

代码
```delphi
(type data=record
         name:string;
                                    money:longint;
                                end;
var
 a:array[0..15] of data;
 n,i,j,k,kk,jj,x,y:longint;
 st:string;
begin 
 readln(n);
 for i:=1 to n do readln(a[i].name);
 for i:=1 to n do begin 
  readln(st);k:=0;
  for j:=1 to n do 
   if st=a[j].name then k:=j;
  readln(x,y);
  if (x<>0)and(y<>0) then a[k].money:=a[k].money+(-1)*x+(x-((x div y)*y));
  for j:=1 to y do begin 
   readln(st);kk:=0;
   for jj:=1 to n do 
    if st=a[jj].name then kk:=jj;
         if (x<>0)and(y<>0) then a[kk].money:=a[kk].money+x div y;
  end;
 end;
 for i:=1 to n do writeln(a[i].name,' ',a[i].money);
end.)
```

---

## 作者：蒟蒻炒扇贝 (赞：13)

**萌新第一次发题解，由于经验不足，有一些紧张，若有什么错误，请各位dalao们指出~~并狠狠的打我~~**

所有的讲解内容都放在代码的注释当中了~~，如果觉得对自己有帮助的话就点一个赞吧(**^▽^**)~~
```cpp
#include<iostream>
#include<map>
#include<cstdio>
#include<cstring>
#include<cmath>//不用万能头文件，从我做起 
using namespace std;
map<string,int>money;//c++ STL万岁！！！（P党：为什么？为什么！） 
/*
这里着重介绍一下map这个神奇的东东。 
在之前的学习中，我们知道数组的下标一定是一个整数类型的量。
但如果你用map的话，情况就会变得不太一样了。
map的使用格式：map<数组下标类型，数组类型>。
以这一道题为例，我将money这一int类型的数组下标改成了string类型的
也就是说，我们可以通过stirng类型来访问数组的每一个点
如cout<<a["david"];，输出在"david"坐标中的量 
*/ 
int n,l,have;
string name[105],x,buddy;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>name[i];//读入他们的名字 
    for(int i=1;i<=n;i++)
    {
        cin>>x>>have>>l;//分别读入送礼者，拥有的钱数，要为多少个朋友送礼 
        if(l==0)continue;//注意！！！这个句子很重要，因为0不能做除数，如果不判断的话，你将会RE！！！
        money[x]-=have;//根据题意，在答案数组中减去自己原先就拥有的钱数 
        int give=floor(have/l);//朋友：钱钱呢？送礼者：马上来马上来（哈哈哈，愚蠢的朋友们，不知道我这个人相来吝啬，我会将能省的钱尽量省下来，hiahiahiahiahia） 
        money[x]+=(have-l*give);//送礼者：嘿嘿，省下来了钱钱，返还过来的钱当然是归答案数组的！
        //（注意，这里是有一个坑点，送礼者返还下来的钱就相当于其他人给送礼者钱）（如果不考虑这一点你会得到22分的好成绩） 
        for(int i=1;i<=l;i++)
        {
            cin>>buddy;//朋友的名字 
            money[buddy]+=give;//送礼者：来来来，撒币了，撒币了！ 
        }
    }
    for(int i=1;i<=n;i++)
        cout<<name[i]<<" "<<money[name[i]]<<endl;//输出答案 
    return 0;//养成好习惯！ 
}
```

~~写完题解就跑，真刺激，~~去参加复赛去了，溜了溜了
借此题解祝各位CSP2019RP++ ！

---

## 作者：w1049 (赞：9)

## 练习STL用题

#### 全程可以都用STL
```
map存钱数

string存人名

vector存输入顺序
```
```cpp
#include<map>
#include<string>
#include<vector>
#include<iostream>
using namespace std;
int NP,money,num;
map<string,int> m;//存钱数 
vector<string> id;//存人名 
int main(){
	cin>>NP;
	string tmp;
	for(int i=1;i<=NP;i++){
		cin>>tmp;
		id.push_back(tmp);//人名加进数组里(为了最后有序输出) 
	}
	for(int i=1;i<=NP;i++){
		cin>>tmp>>money>>num;//人 钱 送的人数 
		if(money==0||num==0)continue;//不送礼的直接跳 
		m[tmp]-=money;//送走了这么多钱 
		m[tmp]+=money%num;//多的还回来 
		for(int j=1;j<=num;j++){
			cin>>tmp;
			m[tmp]+=money/num;//得到钱数 
		}
	}
	for(vector<string>::iterator i=id.begin();i!=id.end();i++)
		cout<<*i<<" "<<m[*i]<<endl;//遍历输出 
	return 0;
}
```

---

## 作者：In_blue (赞：7)

## 这道题的做法，用数组模拟会十分复杂，因此，我们在这里引入<map>的思想。
  
    首先，<map>的基本使用方法是定义一个类似于数组的东西，但它的数组下标类型和数据类型是可以自己定义的。例如代码中:map<string,int>mp;就是定义一个数组下标为string的类似于数组的东西，但他的存储数据却是int类型的。
### 本题思路如下：   	
  	1、先定义一个结构体，分别保存每个人的支出和收入；
  	2、用name[]数组分别保存此次送礼的人的名字；
  	3、输入送礼者的名字、送的钱和有多少人收到礼物后，需要一个特判，应为当收到礼物的人数为0时，剩下的钱x1%0会运行错误！！
  	4、将收到钱的人的总钱数加上，这时，<map>的好处就体现出来了，我们并不需要寻找送礼人的序号，因为<map>中已经将名字所对应的序号保存好了。
  	5、最后，输出收入减输出的差即可。
	 
###   具体过程看代码
------------
  ```
#include<iostream>
#include<map>//调用map函数要用<map>头文件
using namespace std;
map<string,int>mp;//定义mp数组
string name[15];
struct jgt{
    int x;//x代表支出。
    int y;//y代表收入
}qian[15];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>name[i];
        mp[name[i]]=i;//保存送礼者的序号
    }
    string p;//送礼者名字
    int x1,y1;//x为送的钱，y为送的人数
    for(int i=1;i<=n;i++)
    {
        cin>>p>>x1>>y1;//输入
        if(y1==0);//特判，若送礼的人数为0，则不送礼，因为x1%0会运行错误
        else {
            qian[mp[p]].x=x1-x1%y1;送礼者剩下的钱
        }
        for(int j=1;j<=y1;j++)
        {
            cin>>p;//输入受礼者的人名
            qian[mp[p]].y+=x1/y1;受礼者收入；
        }
    }
    for(int i=1;i<=n;i++)cout<<name[i]<<' '<<qian[mp[name[i]]].y-qian[mp[name[i]]].x<<endl;//输出人名和收入和支出的差
        return 0;
}                                                                            
```
求管理员过QWQ。

---

## 作者：f112358 (赞：7)

一句话，无与伦比好理解的模拟。





    
```cpp
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int n;
string name[11];
int money[11];
int search(string a) 
{
    for(int i=1;i<=n;i++)
    {
        if(a==name[i]) return i;
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>name[i];
    }
    for(int j=1;j<=n;j++)
    {
        string now;
        cin>>now;
        int p,m;
        cin>>m>>p;
        if(p==0) continue;             //感谢输入样例中有0！ 
        money[search(now)]+=m%p-m;
        m-=m%p;
        for(int k=1;k<=p;k++)
        {
            string c;
            cin>>c;
            money[search(c)]+=m/p;
        }
    }
    for(int num=1;num<=n;num++)
    {
        cout<<name[num]<<" "<<money[num]<<endl;
    }
    return 0;
}
```

---

## 作者：大魔鬼灿灿 (赞：7)

模拟

这道题不难，就是一道模拟题，模拟分钱的情况而已

我的思路：

```
用结构体q[ ]来存每个朋友的信息

q[ ].s是每个朋友的名字

q[ ].n是每个朋友要送出的钱数

q[ ].m是每个朋友要送的人数

q[ ].shou是每个朋友会收到的钱数

q[ ].hui是每个朋友不能平均分而退回的钱数

1.输入人数n1，数入每个人的名字q[i].s

开始循环模拟送礼情况

2.输入s为当前的送礼者

  因为本题n1范围只是到10
  
  所以可以循环找s所在的结构体
  
  找到以后用z储存当前循环的s所在结构体编号
  
3.输入q[z].n和q[z].m

  循环输入z的收礼者，用s1数组储存
  
4.特判当q[z].n==0的情况，直接继续循环下一次就行了
  
  特判当q[z].m==0的情况，把该朋友要送的钱全部加入q[z],hui
  
 5.如果该朋友的n和m都！=0,
 
   那么让t=每个收礼者该得的钱数
   
   q[z].hui要加上n%m，是不能平均分的钱
   
   然后循环找s1中的每个名字
   
   找到后该结构体的shou+=t
   
6.输出 每个朋友的收的钱+没有送的钱-送的钱

  这就是每个人收到的比送出的钱多的数目了

```
上代码：

```
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
struct node
{
	string s;
	int n,m,shou,hui;
}q[11];
int n1,z;
string s,s1[11];
int main()
{
	scanf("%d",&n1);
	for(int i=1;i<=n1;i++) 
	  cin>>q[i].s;
	for(int i=1;i<=n1;i++)
	{
		cin>>s;
		for(int j=1;j<=n1;j++)
		  if(q[j].s==s)
		    z=j;
		scanf("%d%d",&q[z].n,&q[z].m);
		for(int j=1;j<=q[z].m;j++) 
		  cin>>s1[j];
		if(q[z].n==0) 
		  continue;
		if(q[z].m==0)
		{
		    q[z].hui+=q[z].n;
			continue;
		}
		int t=q[z].n/q[z].m;
		q[z].hui+=q[z].n%q[z].m;
		for(int j=1;j<=q[z].m;j++)
		{
			for(int w=1;w<=n1;w++)
			{
				if(q[w].s==s1[j])
			    {
				    q[w].shou+=t;
					break;
				}
			}
		}
	}
	for(int i=1;i<=n1;i++)
	{
		cout<<q[i].s;
		printf(" %d\n",q[i].shou-q[i].n+q[i].hui);
	}
	return 0;
}
```

---

## 作者：hjsjhn (赞：4)

/\*
这题其实比较容易，只要注重字符串的处理即可

注意每个人送礼物出去后若钱数除以人数除不尽剩下的钱会归还给赠送者。

\*/
```cpp
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<ctype.h>
#include<cstdio>
using namespace std;
int zz;
void cz(string jsz,string s)
{
    if( jsz != s) zz = 0;
    if(jsz == s) zz = 1;
}
int main()
{
    freopen("gift1.in","r",stdin); 
    freopen("gift1.out","w",stdout);
    int np, mon[11], ngi[11], k=0, dd[11], q[11], px[11], moe[11], ng[121];
    string s[14], jsz[121], m[11];
    memset(mon, 0, sizeof(mon));
    memset(dd, 0, sizeof(dd));
    memset(ngi, 0, sizeof(ngi));
    memset(px, 0, sizeof(px));
    memset(moe, 0, sizeof(moe));
    memset(ng, 0, sizeof(ng));//以上是初始化数组 
    cin>>np;//输入环节 
    for(int i = 0; i < np; i++)
    {
        cin>>m[i];
    }
    for(int j=0; j<np; j++)
    {
        cin>>s[j];
        cin>>mon[j]>>ngi[j];
        if(ngi != 0) {
            //q[j]=mon[j] / ngi;
            for(int i=0; i<ngi[j]; i++) {
                cin>>jsz[k];k++;
                }
            }    
```
}//以上都是输入环节，不做赘述
     
```cpp
    k = 0; 
    /*for(int j=0; j<np; j++) {
       cout<<s[j]<<" "<<mon[j]<<endl;
    }*/
    for(int j=0; j<np; j++)
    {if(ngi[j] == 0) continue;//若没有松他人礼物 ，跳过此次循环 
        q[j] = mon[j] / ngi[j];//分配给每个要赠送的人的钱 
        for(int i=0;i<ngi[j];i++) {
          for(int v=0;v<np;v++){
              cz(jsz[k+i],s[v]);//查找匹配字符串 
              if(zz == 1) {dd[v]+=q[j];/*cout<<s[v]<<" "*/;break;}//找到的赠者，数组得到加上赠送者送出的钱 
          } 
        } k+=ngi[j];//cout<<endl;
    }
    for(int i=0; i<np;i++) {
       for(int j=0; j<np;j++) {
         cz(m[i], s[j]);
         if(zz == 1) {px[i] = dd[j];moe[i] = mon[j];ng[i] = ngi[j];break;}//moe要送出的，px得到的 
       }
    }
    for(int i=0; i<np; i++) {
        cout<<m[i]<<" ";
        if(ng[i] != 0) {cout<<px[i]-moe[i]+moe[i]%ng[i]<<endl;}
        else {cout<<px[i]-moe[i]<<endl;}
    }
    return 0;
}
```

---

## 作者：StyWang (赞：4)

# 字典树存姓名
我是萌新，还不会map大法。虽然题中NP<=10，所以其实可以一个名字一个名字的比较，但是对于强迫症的我来说，希望尽量优化复杂度。

由题可知，我们要给每个人的名字和一个数字建立一一映射关系，也就是给每个人编号。由此想到了哈希，但由于萌新哈希不熟练，所以选择了字典树，一个可以快速建立字符串与数字间映射关系的数据结构。

至于字典树是什么，参见[这里](https://baike.baidu.com/item/字典树/9825209?fr=aladdin#5_3) 和 [这里](https://www.luogu.org/problemnew/solution/P2580)。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#define NOT_HAVE 0
using namespace std;

char namelist[300][20] = {'\0'};//储存所有名字，可以保存输入的顺序，方便输出
struct node
{
	int son[27] = {NOT_HAVE};
    //son[i]中存着当前节点下方i+'a'这一个子母的节点编号
	int index = NOT_HAVE;
}trie[100000];
int p_trie = 0;
int NP;
int account[300] = {0};
int p_account = 0;

int trie_find(char s[]);//输入名字，返回其编号
void trie_insert(char s[]);//向字典树中插入新名字
void trans(char s[]);//所有大写转换小写，题中没有说一定都是小写，转换一下保险一点

int main()
{
	freopen("gift1.in", "r", stdin);
	freopen("gift1.out", "w", stdout);
    //usaco提交需要写的内容
    
	int i, j, money, NG;
	char namec[20];
	int namen;
	scanf("%d", &NP);
	for(i = 0; i < NP; i++)
	{
		scanf("%s", namelist[i]);
		strcpy(namec, namelist[i]);//不能直接给namelist转化大小写，因为题中说要原样输出
		trans(namec);
		trie_insert(namec);
	}
	
	for(i = 0; i < NP; i++)
	{
		scanf("%s\n%d%d", namec, &money, &NG);
		trans(namec);
		int id = trie_find(namec);
		account[trie_find(namec)] -= money;
		if(NG != 0)
			account[trie_find(namec)] += money % NG;
		for(j = 0; j < NG; j++)
		{
			scanf("%s", namec);
			trans(namec);
			int id = trie_find(namec);
			account[id] += money / NG;
		}
	}
	for(i = 1; i <= NP; i++)
		printf("%s %d\n", namelist[i - 1], account[i]);
	return 0;
}

void trans(char s[])
{
	for(int i = 0; i < strlen(s); i++)
		if(s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] - 'A' + 'a';
	return;
}

int trie_find(char s[])
{
	int length = strlen(s);
	int p = 0, c;
	for(int i = 0; i < length; i++)
	{
		c = s[i] - 'a';
		p = trie[p].son[c];
	}
	return trie[p].index;
}

void trie_insert(char s[])
{
	int length = strlen(s);
	int p = 0, c;
	for(int i = 0; i < length; i++)
	{
		c = s[i] - 'a';
		if(trie[p].son[c] == NOT_HAVE)
			trie[p].son[c] = ++p_trie;
		p = trie[p].son[c];
	}
	trie[p].index = ++p_account;
}
```

---

## 作者：小熊熊 (赞：3)

本题题意就是一堆人相互送礼，求最后每个人有多少钱。
用结构体存储每个人的姓名以及钱，进行模拟，具体注释见代码。



```cpp
#include <bits/stdc++.h>

using namespace std;

struct node 
{
	string name;
	int money;
}a[20];

int np,n,mon;
string s;
string s1;

int equal(string x)//找字符串对应的下标 
{
	for(int i=1;i<=np;i++)
		if(x==a[i].name)
			return i;
}

int main()
{
	cin>>np;
	for(int i=1;i<=np;i++)
		cin>>a[i].name;
	for(int i=1;i<=np;i++)
	{
		cin>>s;
		int temp=equal(s);
		cin>>mon>>n;
		a[temp].money-=mon;//给别人发钱，我自己要扣钱的嘛 
		if(n==0)
			continue;
		int give=mon/n;//平均给别人多少钱 
		a[temp].money+=mon-n*give;  //分赃不均，我就把多的放回自己的口袋 
		for(int j=1;j<=n;j++)
		{
			cin>>s1;
			a[equal(s1)].money+=give;//别人收钱 
		}	
	}
	for(int i=1;i<=np;i++)
	{
		cout<<a[i].name<<" "<<a[i].money<<endl;
	}
	return 0;
} 
```



---

## 作者：kisah (赞：3)




```cpp
//正如讨论中说的，其实题目讲的有点玄学 
//稍微讲一下，本体题保留剩下的钱
//希望各位一些小小的帮助 
#include <cstdio>
#include <iostream>
#include <cstring> //我是用string，字符数组挺繁琐的 
using namespace std;
string given,giver,name[15];//被给予的人名，给予的人，存储名字的数组 
int np,i,mon[15],gift[15],wealthy,givenn;//题目中的np，循环，花掉的钱，收到的礼物（钱），要花的钱，要给的人数 
int find(string s){ //查找名字所在的位置（即是数组下标） 
    int i=1;
    while (s!=name[i]) i++;
    return i;
}
void dodo(int n){
    int i;
    cin>>wealthy>>givenn;
    if (givenn == 0) return; //遇到0个被给予的人会爆，所以特殊处理 
    mon[n]=wealthy%givenn-wealthy; //剩下的钱减去花掉的钱 
    for (i=1;i<=givenn;i++){
        cin>>given;
        gift[find(given)]+=wealthy/givenn; //收到礼物的人加钱 
    }
}
int main(){
    cin>>np;
    for (i=1;i<=np;i++)
        cin>>name[i];
    for (i=1;i<=np;i++){ //一个一个做，所以搞了一个viod，易懂 
        cin>>giver;
        dodo(find(giver));
    }
    for (i=1;i<=np;i++) //输出 
        cout<<name[i]<<' '<<mon[i]+gift[i]<<endl;
    return 0;
}
```

---

## 作者：oreimo_eromanga (赞：3)

```cpp

#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<string>
#include<cstdio>
#include<cmath>
using namespace std;
struct xy      //用结构体做更方便。 
{
       string name;
       int rmb;
}a[11];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) //读入名字。 
       cin>>a[i].name;
    string ren;
    int zb,money,rs;      //人坐标、总钱、人数。 
    for(int k=1;k<=n;k++)
    {
       cin>>ren;
       cin>>money>>rs;    //读入。 
       for(int i=1;i<=n;i++)
          if(a[i].name==ren)
            {zb=i;}       //查找人的位置。 
       for(int i=1;i<=rs;i++)
       {
          cin>>ren;
          for(int j=1;j<=n;j++)
             if(a[j].name==ren)
             {
               a[j].rmb+=money/rs;  //加钱，扣钱。 
               a[zb].rmb-=money/rs;
             }
       }
    }
    for(int i=1;i<=n;i++)        //输出。 
       cout<<a[i].name<<" "<<a[i].rmb<<endl;

}

```

---

## 作者：至成天下 (赞：2)

看到大佬们用各种各样的方法，本蒟蒻瑟瑟发抖

其实我们只要开两个map来记送出和收入~~（别问我为什么不用一个）~~

最后用收入减去送出即可

注意送出剩下的钱要还给送出者，我被这个坑了第一次只得了22分

其他细节详见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;//个数
string st[11];//名字
map <string,int> receive;//收入
map <string,int> give;//送出
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>st[i];
	for(int i=1;i<=n;++i){
		string a;//送出者名字
		int x,y;//钱数和人数
		cin>>a;
		cin>>x>>y;
		if(y){//y为零不送
			give[a]+=(x/y)*y;//送出，注意加的不是y
			for(int j=1;j<=y;++j){//逐个送出
			string b;//收钱者名字
			cin>>b;
			receive[b]+=(x/y);//收入
		}
		}
	}
	for(int i=1;i<=n;++i){
	cout<<st[i]<<' '<<receive[st[i]]-give[st[i]]<<endl;//减去后输出
	}
return 0;
}

```


---

## 作者：fifnmar (赞：2)

这道题题解大家已经给了很多，我在编程方面给大家提供一个使用面向对象思想和标准库里map类的用法吧。（这里的unordered\_map可以替换成map，你也可以自定义自己的struct）


代码说明在下面


```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
// 这道题的思想还是比较简单的，这里给出一个面向对象解法，和大家交流一下^_^
using namespace std;
class person                    // 这个类是本程序的核心类，每一个人都看做一个对象。
{
    int getmoney()              // 这是个私有函数，用来返回一个人最终得到的钱数。
    {                           // 在编写这个函数的时候要注意到，每个人送钱都是整数，有一部分钱没有送出去。
        if (friends)            // ！！！一定注意！！！有的人可能没有朋友，因此要做判断，不然会除以0而报错。
            return final - money + money % friends;
        return final - money;
    }
public :
    string name;                // person类的成员，这里我用了值初始化，你也可以选择构造函数初始化。
    int money = 0;
    int final = 0;              // friends是这个人的朋友数量。
    int friends = 0;            // 这个数组用来存储这个人的朋友都是谁。一般来说应该把录入朋友的功能写成一个函数作为这个类的成员之一，
    vector<string> frns;        // 但是在这里我把功能放到了下面的主函数里。
    void print() {cout << name << " " << getmoney();}   // 这个函数用来输出。为了灵活，输出函数不应该有格式控制，所以不要输出回车。
};
void ssli(unordered_map<string, person> & a)
{
    for (auto &w : a)
        for (auto &q : w.second.frns)
            a.find(q)->second.final += w.second.money / w.second.friends;
}   // 这个函数用来进行送礼的过程。
int main()
{
    int np, rfvu, qw;
    cin >> np;
    string a;
    vector<string> daoj;    //注意这道题的输出要求你按照最开始输入的人名顺序输出。所以我又加了这个vector，不然可以直接范围循环那个map。
    unordered_map<string, person> rf;
    for (int i = 0; i != np; i++)
    {
        cin >> a;
        daoj.push_back(a);
        rf[a];
        rf.find(a)->second.name = a;
    }   // 录入名字的循环。
    for (int i = 0; i != np; i++)
    {
        cin >> a >> qw >> rfvu;
        rf.find(a)->second.money = qw;
        rf.find(a)->second.friends = rfvu;
        while (rfvu)
        {
            string temp;
            cin >> temp;
            rf.find(a)->second.frns.push_back(temp);
            rfvu--;
        }
    }   // 录入对应名字数据的循环。这个录入过程也可以做成类的成员函数。
    ssli(rf);
    for (const auto &q: daoj)
    {
        rf.find(q)->second.print();
        cout << endl;
    }
    return 0;
}
```

最后说一下为什么这个程序我会想到使用map呢？因为考虑到录入时人名的顺序可能不同（这道题似乎是按顺序录入的），所以要求随机访问不同的人，我们可以使用map，简化我们的思维。

如果有意见欢迎私信啦！


---

## 作者：kl膜法59改 (赞：2)

看题目花的时间长，其实这道题还是非常非常简单的，结构体加循环轻松解决。。。。。。



```cpp
#include <bits/stdc++.h>
#define N 1000000
using namespace std;
struct ren//结构体记录每组数据
{
    int shou;
    int song;
    char ming[100];
}a[N];
int np,ngi,ans=0;
char ch[N],ssr[N];
int main()
{
    scanf("%d",&np);
    for(int i=1;i<=np;i++)
    {
        scanf("%s",a[i].ming);//按输入顺序存人名，后面对应就行了
    }
    for(int i=1;i<=np;i++)
    {
        scanf("%s",ssr);//送礼的人
        for(int g=1;g<=np;g++)
        {
            if(strcmp(ssr,a[g].ming)==0)//将人名与输入顺序中的人名对应
            {
                cin>>a[g].song>>ngi;//金额和送人数
                for(int j=1;j<=ngi;j++)
                {
                    scanf("%s",ch);
                    for(int k=1;k<=np;k++)
                    {
                        if(strcmp(ch,a[k].ming)==0){a[k].shou+=a[g].song/ngi;ans+=a[g].song/ngi;}//注意这里要加一个ans记录实际到达每个人手中的钱的数量，因为余数最后还是要返还的
                    }
                }
                if(ans<a[g].song)a[g].song=ans;//将实际金额赋给每个人送钱的值
                ans=0;
            }
        }
    }
    for(int i=1;i<=np;i++)
    {
        printf("%s %d\n",a[i].ming,(a[i].shou-a[i].song));//输出结果
    }
    return 0;
}
```

---

## 作者：嘦疒风 (赞：2)

蒟蒻的代码，希望各位别太苛刻了！

主要是没学多久，然后被大佬的函数看懵逼，然而在大佬的函数下我不屈服，不用函数写出了这个

这题其实可以把字符串中的各部分简化进行操作

献上代码


```cpp
#include<bits/stdc++.h> 
using namespace std;
int main()
{
    int NP,n[20]={},y[20],z[20];//n表示人所送出的钱，y是人拥有的要发的钱，z是送礼者送出的礼品次数 ； 
    string a[20],x[20],b[20][20];//a表示人名，x表示送礼者（和a独立，比如a[1]可能是第二个送礼者即x[2]），b表示受礼者； 
    cin>>NP;//输入人数 
    for(int i=1;i<=NP;i++)
    cin>>a[i];// 输入人名 
    for(int i=1;i<=NP;i++)
    {
        cin>>x[i]/*输入送礼者*/>>y[i]/*输入发钱总数*/>>z[i];//输入发出的次数 
        for(int j=1;j<=z[i];j++)
        {
            cin>>b[i][j];//输入受礼者； 
        }
```
}//输入完成；
    
```cpp
    for(int i=1;i<=NP;i++)
    {
        if(z[i]!=0)//这要排除z[i]等于0的情况，因为被除数是0会炸掉 
        {
            for(int h=1;h<=z[i];h++)//在受礼者中与人名进行对比查找 
            {
                for(int ii=1;ii<=NP;ii++)
                {
                    if(b[i][h]==a[ii])//查找到后将对应的人名的花费加上收到的钱 
                    {
                        n[ii]=n[ii]+y[i]/z[i];
                        break;//防止程序炸了 
                    }
                }
```
}//对受礼者进行操作
            
for(int j=1;j<=NP;j++)//在被送礼者中与人名进行对比查找

```cpp
            {
                if(x[i]==a[j])//查找到后将对应的人名的花费减去送出的钱
                {
                    n[j]=n[j]-y[i]/z[i]*z[i];
                    break;
                }
```
}//对送礼者进行操作
        }

}//操作完成

    for(int i=1;i<=NP;i++)//输出不用说什么 

    cout<<a[i]<<' '<<n[i]<<endl;

    return 0;

}

---

## 作者：plazum (赞：2)

1.要求的是收到的减去送出的，除不尽剩下的不用管它；

2.C++可以用STL的map来方便地以名字找编号……但是！不要写map<char\*,int>，这样作为键值的不是字符串（字符数组），而是一个指针……这个坑了我好久……请用map<string,int>。

```cpp

#include<iostream>
#include<string>
#include<map>
using namespace std;
int np,i,j,a[10],give,ng;
string name[10],s;
map<string,int> f;
int main()
{
    for(cin>>np;i<np;i++)cin>>name[i],f[name[i]]=i;
    for(i=0;i<np;i++){
        cin>>s;
        cin>>give>>ng;
        a[f[s]]-=ng?give-give%ng:0;
        for(j=0;j<ng;j++)cin>>s,a[f[s]]+=give/ng;
    }
    for(i=0;i<np;i++)cout<<name[i]<<' '<<a[i]<<'\n';
    
    return 0;
}

```

---

## 作者：Hanzire76 (赞：2)

简单题就是要有简单题的亚子

数据十分小，可以暴力。

先开结构体存下每个人的名字，收入和支出，按顺序读入。

输入送礼名单时，遍历一遍，匹配名字，加上平均数。

最后按顺序输出每个人的收入-支出

详细见代码。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

int n,x,y;
string b;
struct node
{
    string name;
    int in,out;
} a[13];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) cin>>a[i].name;
    for(int i=1;i<=n;i++)
    {
        cin>>b;
        scanf("%d%d",&x,&y);
        if(y==0) continue;              //除数不能为0
        for(int j=1;j<=n;j++)
            if(a[j].name==b)           //string就是方便
                a[j].out+=(x/y)*y;      //平均送礼
        for(int j=1;j<=y;j++)
        {
            cin>>b;
            for(int k=1;k<=n;k++)
                if(a[k].name==b)
                    a[k].in+=x/y;       //到账
        }
    }
    for(int i=1;i<=n;i++)
        cout<<a[i].name<<" "<<a[i].in-a[i].out<<endl;
    return 0;
}
```


---

## 作者：zhaowangji (赞：1)

STL-MAP

因为要存每个人的名字和钱，所以只想到了map

map可以简单理解为将某两个量绑定（数组也行，但只能是数字与其他类型绑定），两个量任意类型都行；赋值可以直接用下标（自动申请空间）或插入（若已有绑定关系，则插入失败）

```cpp
#include<bits/stdc++.h>
using namespace std;
int np;//尽量按题目里的说法
string a[17];//每个人的名字
string x;//读入名字用
map<string,int> m;//string-int型，因为是人与钱的对应
int main(){
	cin>>np;//人数
	for(int i=1;i<=np;i++)
		cin>>a[i],m[a[i]]=0;
       		//读入每个人的名字，初始每个人都是0元
	while(cin>>x){//只要有输入，x是给别人钱的人的名字
		int sum,num;
		cin>>sum>>num;//发出去的钱，以及给了多少人
		if(num==0||sum==0)continue;
        	//特判，不然除以一个为0的数会运行出错
		m[x]-=sum;//给出去了这么多钱
		int mon=sum/num;//被给钱的人收到的钱（题目说是整除）
		m[x]+=sum%num;//余下的钱还给自己
		for(int i=1;i<=num;i++){
			string name;
			cin>>name;//被给钱的人的名字
			m[name]+=mon;//这些人得到了钱
		}
	}
	for(int i=1;i<=np;i++)
		cout<<a[i]<<' '<<m[a[i]]<<endl;
        	//每个人的名字和现在的钱数
	return 0;
}
```


---

## 作者：Ufowoqqqo (赞：1)

[center]**[u][color=red]##P1201 贪婪的送礼者题解[/color][/u]**[/center]

<hr>
\* 这是一道模拟题，只要细节不出错（比如id不要写成i）就没有大的问题。

\* 按照题意模拟的同时要注意：判断total[id]为0的情况要特殊处理，否则Free Pascal会出现200错误（除0）。

\* 本人代码如下（抛砖引玉，献丑了）：

```delphi

var
 n,p,i,j,id:byte;
 name:array [1..10] of string[14];
 temp:string[14];
 total{每个人自己的钱},money{每个人最后拥有的钱}:array [1..10] of integer;

function getid(nam:string):byte;//通过姓名来获得编号
var i:byte;
begin
 for i:=1 to n do if name[i]=nam then exit(i)//枚举，检测是否匹配
end;

begin
 readln(n);
 for i:=1 to n do readln(name[i]);
 fillchar(money,sizeof(money),0);//不初始化的话值有时会变得非常奇怪
 for i:=1 to n do
 begin
  readln(temp);
  id:=getid(temp);
  readln(total[id],p);
  for j:=1 to p do
  begin
   readln(temp);
   inc(money[getid(temp)],total[id] div p)//每个人平均分配
  end;
  if total[id]=0 then continue;//特判
  if p=0 then inc(money[id],total[id]){不分给别人} else inc(money[id],total[id] mod p){分给别人，自己保留余数}
 end;
 for i:=1 to n do writeln(name[i],' ',money[i]-total[i]){拥有的钱-自己本来的钱=多收的钱}
end.

```

---

## 作者：taophee (赞：1)

想法：

这道题准确来说可以就是一个模拟，用数组存储就可以了

然后每次判断一下人名对应的数据（本人比较懒，没用高深的方法）

接着对于钱的分配采用相同方法处理就ok了

程序：

```delphi

var
n,i,j,k,y,z,p,q:longint;
a:array[1..100] of ansistring;
b:array[1..100] of longint;
x:ansistring;

begin
  readln(n);
  for i:=1 to n do
    readln(a[i]);
  for j:=1 to n do
   begin
    readln(x);
    for k:=1 to n do
      if a[k]=x then begin p:=k;break;end;
    readln(y,z);
    if z<>0 then
     begin
     b[p]:=b[p]+y mod z-y;
    y:=y div z;
    for k:=1 to z do
     begin
      readln(x);
      for q:=1 to n do
        if a[q]=x then begin p:=q;break;end;
      b[p]:=b[p]+y;
    end;
    end;
  end;
  for i:=1 to n do
    writeln(a[i],' ',b[i]);
end.

```

---

## 作者：AkiwaZawa (赞：0)

模拟题，用结构体不如用 map

[给不知道map的同学](https://blog.csdn.net/u013550000/article/details/80521509)

感觉没有什么好讲的，就直接看代码吧（有注释哦）。

```
//本代码使用map来存储
#include<bits/stdc++.h>
using namespace std;
map<string,int>ans; //定义一个下标为字符串存整数的map用来储存每个人的总钱数
string a[2001],s,p;
int main()
{
    int t,i,m,n;
    cin>>t;
    getchar();
    for(i=1;i<=t;i++)
		cin>>a[i];
    while(cin>>s)
	{
        scanf("%d%d",&m,&n);
        ans[s]-=m;//总钱数减送出的钱数
        for(i=1;i<=n;i++)
		{
            cin>>p;
            ans[p]+=m/n;//收礼者的总钱数加送礼者送的钱数/人数
        }
        if(n!=0)
        ans[s]+=m%n;//余下的钱还给送礼者
    }
    for(i=1;i<=t;i++){cout<<a[i];printf(" %d\n",ans[a[i]]);}
    return 0;
}
```


    

---

## 作者：MZMH (赞：0)

### 这一题挺简单的，但是如果是纯模拟的话。会十分麻烦

### 这里介绍一个~~STL~~映射map

### map的最大优点是可以使用任意数据类型作为数组的下标 

### map的定义形式为 $map<$  下标类型   ,  存放的数据类型    $>$   数组名

#### 如: $map<string ,int >ans$

map的使用方法与普通数组无异

map数组中值默认为0

------

##### 此题所需注意的点

1. 贪婪者送出去的钱是要减去的
2. x%y ___y!=0___ 否则会 __RE__

```cpp
#include "bits/stdc++.h"
using namespace std;
int n,num,money;
string name[11];
map<string,int>ans;//map定义
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	    cin>>name[i];
	for(int i=1;i<=n;i++) {
		string na;
		cin>>na>>money>>num;
		ans[na]-=money;//先减去，反正后面不能分完会加回来
		if(!num) {//特判 被模数
			if(money)
			    ans[na]+=money;//如果有钱，收入自己囊中
			continue;
		}
		if(!money)//没钱，免谈！！！
		    continue;
		if(money%num)//判断是否有剩余
		    ans[na]+=(money%num),money-=(money%num);
		for(int j=1;j<=num;j++)
		    cin>>na,ans[na]+=(money/num);//把分出去的钱加上收礼者的数组里
	}
	for(int i=1;i<=n;i++)
	    cout<<name[i]<<' '<<ans[name[i]]<<endl;//输出
	return ac;
}
```

~~手动防抄袭~~

---

## 作者：Wshine (赞：0)

其实这道题应该是一道较简单的模拟，我的思路如下：

0.创建结构体存并储每个人的信息；

1.在输入（送礼）过程中，进行钱数的增减；

2.按顺序输出结果；

中途用了两遍for循环来查找人，因为在两段输入中，人名的出现顺序会变化，代码如下（C）：


```cpp
#include<stdio.h>
#include<string.h>
struct people               //定义结构体
{
    char name[14];         //姓名 
    int money;             //所拥有的钱数 
    int list;              //要送礼物的列表（人数） 
    int give;              //送给每个人的钱数  
};
struct people p[11];       //定义结构体变量p来储存人物信息 
int n,money,list,b;         
char man[14];
int moneys(int mo,int friends)      //计算送给每个人的钱数 
{
    if(friends==0)
    {
        return 0;         **/*注意判断要送的人数(list)是否为0，否则会出现除数为0而运行错误的情况（被坑了n次QAQ）*/**
    }
    return mo/friends;    //若非0则返回结果（向下取整） 
}
int main()
{
    //freopen("gift.in","r",stdin);
    //freopen("gift.out","w",stdout);
    scanf("%d",&n);
    int i,j,k;
    for(i=0;i<n;i++)
    {
        scanf("%s",p[i].name);         //记录所有人并将名字存入结构体变量中  
    }
    for(i=0;i<n;i++)
    {
        scanf("%s%d %d",man,&money,&list);      //先将输入内容暂时存入变量中 
        for(j=0;j<n;j++)
        {
            if(strcmp(man,p[j].name)==0)       //搜索姓名相符的变量 
            {
                p[j].list=list;
                p[j].give=moneys(money,p[j].list);   //将信息存入此结构体变量内 
                b=j;                               //保存此变量的下标，留着送礼时用(因为j的值会变动，故需储存) 
                _//printf("\tIN:name:%s money:%d give:%d list:%d\n",p[b].name,p[b].money,p[b].give,p[b].list);//[输出中间值调试]_
            }
        }
        for(j=0;j<p[b].list;j++)
        {
            scanf("%s",man);                  //输入收礼人姓名 
            for(k=0;k<n;k++)
            {
                if(strcmp(p[k].name,man)==0)  //搜索与姓名相符的变量 
                {
                    p[k].money+=p[b].give;    //收礼人拥有钱数增加 
                    p[b].money-=p[b].give;    //送礼人钱数对应减少 
                    _//printf("\tFIND:name:%s money:%d   Now %s has money:%d\n",p[k].name,p[k].money,p[b].name,p[b].money);//[输出中间值调试] _
                }
            }
        }                  //循环循环循环~\(≧▽≦)/~ 
    }
    for(i=0;i<n;i++)
    {
        printf("%s %d\n",p[i].name,p[i].money);   //按要求依次输出信息 。 
    }
     return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这是一道灰常简单的题目，暴力打遍

天下无敌手，

三重循环暴力来暴力去，

这一切的一切

都是因为

N
只到10！！！！！！

那就很简单了，

名字对应编号

于是
附上代码：

```cpp
var
  n,m,i,j,x,y,k:longint;
  a:array[1..10] of  longint;
  s:array[1..10] of string;
  ch:char;
  s1,s2:string;
begin
  readln(n);
  for i:=1 to n do
    readln(s[i]);
  for i:=1 to n do
  begin
    readln(s2);
    readln(x,y);
    if y<>0 then
    begin
      for k:=1 to n do
      if s2=s[k] then
      begin
        a[k]:=a[k]-x+x mod y;//送礼者の损失和回报
        break;
      end;
      for j:=1 to y do
      begin
        readln(s1);
        for k:=1 to n do
        if s1=s[k] then//对应
        begin
          a[k]:=a[k]+x div y;//拿来的
          break;
        end;
      end;
    end; 
  end;
  for i:=1 to n do
  writeln(s[i],' ',a[i]);
end
```

---

## 作者：封禁用户 (赞：0)

这道题的难度相当于联赛第一题。

用数组incom outcom记录每个人的收入和支出，

记录每个人的名字，对于送礼人i，找到他要送给的人j，

inc(incom[j],outcom[i] div n)，其中n是要送的人数，

最后inc(incom[i],outcom[i] mod n) 最后输出incom[i]-outcom[i]即可。

（复杂度O(n^3)）

用Hash表可以进行优化，降复杂度为O(n^2)

PS:其实如果你用c++可以更好更快的解决问题，那就是STL中的map

~~这里仅给出map写法~~

~~呵呵其实都有~~

```cpp
#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;
int main()
{
    string names[50];
    map <string,int> reci,given;    
    int np;
    ifstream cin("gift1.in");
    ofstream cout("gift1.out");    
    cin>>np;
    for (int i=1;i<=np;i++)
        cin>>names[i];
    for (int i=1;i<=np;i++)
    {
        string temp;
        int tempr,tempg,j;        
        cin>>temp;
        cin>>tempg>>j;
        for (int k=1;k<=j;k++)
        {
            string temp2;            
            cin>>temp2;
            reci[temp2]+=tempg/j;//最基础的map 
            given[temp]+=tempg/j;//map的应用 
        }    
    }
    for (int i=1;i<=np;i++)
        cout<<names[i]<<" "<<reci[names[i]]-given[names[i]]<<endl;
    return 0;
}
```
--------------------华丽の分割线---------------------------
 
 
```cpp
#include <fstream>
using namespace std;
ifstream fin("gift1.in");
ofstream fout("gift1.out");
int main()
{
    static int ans[10];
    int np,i,j,p,ini,ng;
    string a[10],giv,rec;
    fin>>np;
    for (i=0;i<np;i++)
        fin>>a[i];
    for (i=0;i<np;i++)
    {
        fin>>giv>>ini>>ng;
        for (p=0;giv!=a[p];p++);
        ans[p]-=ng==0?0:ini-ini%ng;
        for (j=0;j<ng;j++)
        {
            fin>>rec;
            for (p=0;rec!=a[p];p++);
            ans[p]+=ini/ng;
        }
    }
    for (i=0;i<np;i++)
        fout<<a[i]<<' '<<ans[i]<<endl;
    return 0;
}
```
--------------------华丽の分割线---------------------------
 
 
 
 
```cpp
#include <iostream>
using namespace std;
char n[15],name[11][15];
int incm[11],np,ngi,npg;
void shop(char *s){
     cin>>ngi>>npg;
     if (!ngi || !npg)
     return;
     for (int i=0;i<np;i++)
     if (!strcmp(s,name[i])){
        if (npg!=0) incm[i]+=-ngi+ngi%npg;
        break;
     }
     char dn[15];
     for (int i=0;i<npg;i++){
         cin>>dn;
         for(int i=0;i<np;i++)
         if (!strcmp(dn,name[i])){
            incm[i]+=ngi/npg;
            break;
         }
     }
}
int main(){
    freopen("gift1.in","r",stdin);
    freopen("gift1.out","w",stdout);
    memset(incm,0,sizeof(int));
    cin>>np;
    for (int i=0;i<np;i++)
         cin>>name[i];
    for (int i=0;i<np;i++){
        cin>>n;
        shop(n);
    }
    for (int i=0;i<np;i++)
        cout<<name[i]<<' '<<incm[i]<<endl;
    return 0;
}
~~管理员大大求通过~~
```

---

## 作者：转身、已陌路 (赞：0)

这题题目读起来有点拗口  意思就是算收到的钱-送出去的钱

此题最麻烦的就是字符串处理

我用了字符串数组来解决 用一个函数来查找他的序号

还有一个不容易想到的就是如果除不尽的话 剩余的钱他会自己留着





```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200];//记录收到的钱 
int b[200];//记录送出的钱 
int sum;
int n;
string name[200];//记录名字 
string s;
void search(string ss)//找到他是第几个 
{
  for (int i=1;i<=n;i++)
  {
  if (ss==name[i]) 
  {sum=i;
   break;
     }
    }
  return;
   }
int main()
{
scanf("%d",&n);
for (int i=1;i<=n;i++)  
    cin>>name[i];
    int x,y;
for (int i=1;i<=n;i++)
{
  cin>>s;
  cin>>x>>y;
  if (y==0)  
  {
  search(s);
  a[sum]+=x;
  continue;
    }
  int num=x/y;
  search(s);
  a[sum]+=x-num*y;//将没除完的钱保存起来
  b[sum]+=x;
  for (int k=1;k<=y;k++)
   {
     cin>>s;
     search(s);
     a[sum]+=num;
       }
     }
     for (int i=1;i<=n;i++)
     {
       cout<<name[i]<<" ";
       cout<<a[i]-b[i]<<endl;
         }
  return 0;
}
```

---

## 作者：Thor_Odinson (赞：0)

【分析】

直接模拟，注意审题，注意实数处理。


```cpp
 1 #include <cstdlib>
 2 #include <iostream>
 3 #include <cstdio>
 4 #include <cstring>
 5 #include <cmath>
 6 #include <algorithm>
 7 using namespace std;
 8 char name[15][20];
 9 int n,money[15];
```
10
```cpp
11 int bh(char *check);//返回对应人的编号 
12 int main()
13 {
14     int i,j;
15     //文件操作
16     freopen("gift1.in","r",stdin);
17     freopen("gift1.out","w",stdout);
18     memset(money,0,sizeof(money));
19     memset(name,0,sizeof(name));
20     //读入数据 
21     scanf("%d",&n);
22     for (i=1;i<=n;i++) scanf("%s",name[i]);
23     for (i=1;i<=n;i++)
24     {
25         char temp[20];
26         int num,tot;
27         scanf("%s",temp);scanf("%d%d",&tot,&num);
28         int p=bh(temp),rem=num;
29         money[p]=money[p]-((int)(((double)tot/num)))*num;
30         while (num--)
31         {
32               scanf("%s",temp);
33               money[bh(temp)]+=((int)(((double)tot/rem)));
34         }
35     }
36     for (i=1;i<=n;i++)
37     printf("%s %d\n",name[i],money[i]);
```
38
```cpp
39     return 0;
40 }
41 int bh(char *check)
42 {
43     for (int j=1;j<=n;j++) if (!strcmp(name[j],check)) return j;
44 }

```

---

## 作者：March (赞：0)

额这题目...数据范围太xxx的小了吧！！！

好吧正解应该是hash表+模拟

用hash表来从字符串转化成数组下标 ， 而不用每一次都去找一遍所有名字，这样复杂度就降低很多了 （这才是正解好不）; 不懂hash表同鞋请百度hash表。

找到以后直接模拟送红包什么的。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
/*basic*/const int maxn=12;
char allnm[maxn][13];
/*basic*/int N,bill[maxn]={0};
/*hash部分*/const int hshsize=1000;
struct hashnd{char nm[15];int nmlen,num;};
vector<hashnd> Hash[hshsize];
int findhash(hashnd T){int a=T.nmlen + T.nm[0] + T.nm[T.nmlen-1]; for(int i=0;i<Hash[a].size();i++){if(strcmp(Hash[a][i].nm,T.nm)==0) return Hash[a][i].num;}return -1;}
void inshash(hashnd T){int a=T.nmlen + T.nm[0] + T.nm[T.nmlen-1];if(findhash(T)==-1)Hash[a].push_back(T);return;}
/*hash部分*/hashnd newhsh(char nm[13]){hashnd ss; strcpy(ss.nm,nm); ss.nmlen=strlen(nm); return ss;}
void init(){//读入所有名字到hash表里面
    hashnd tmp;
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%s",&tmp.nm);
        strcpy(allnm[i],tmp.nm);
        tmp.nmlen=strlen(tmp.nm), tmp.num=i;
        inshash(tmp);
    }
    return;
}
void slove(){
    int mon,pn,snum,tnum,pres;
    char sender[13],tmp[13];
    while(scanf("%s",&sender)!=EOF){
        scanf("%d%d",&mon,&pn);
        if(mon==0 || pn==0) continue;
        snum=findhash(newhsh(sender));//通过hash找到送礼者数组下标
        pres=mon/pn;//算算每个人能得多少
        bill[snum]-=pres*pn;//扣钱
        for(int i=0;i<pn;i++){
            scanf("%s",&tmp);
            tnum=findhash(newhsh(tmp));
            bill[tnum]+=pres;//送礼
        }
    }
    return;
}
int main(){
    init();
    slove();
    for(int i=0;i<N;i++){//输出所有人的bill
        printf("%s %d\n",allnm[i],bill[ findhash( newhsh(allnm[i]) ) ]);
    }
    return 0;
}
```

---

## 作者：PhantasmDragon (赞：0)

一道暴力的模拟题，数据小到我开心<\_>

有坑，在注释里有详解。


```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int n;
struct peo
{
    char name[30];//名字
    int money;//要送出的钱数
    int income;//收到的钱数
};
void solve()
{
    peo list[50];
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s",list[i].name);
        list[i].money=0;
        list[i].income=0;
    }
    for(int i=0;i<n;i++)
    {
        int num,sig,pos;
        char tmpname[30];
        scanf("%s",tmpname);
        for(pos=0;pos<n;pos++)//在数组中找到需要修改的数据点
        {
            if(strcmp(tmpname,list[pos].name)==0)
            {
                break;
            }
        }
        scanf("%d %d",&list[pos].money,&num);
        if(num==0)//坑！！x/0时要特殊处理，不然RE在微笑着等你TAT
        {
            continue;
        }
        else
        {
            sig=list[pos].money/num;    
        }
        list[pos].income+=list[pos].money-sig*num;//这句看上去没有任何意义，但是如果除不尽的话，剩下的钱要留在送礼人的手里，因为c++里除法是刚好向下取整的，所以这里直接用.(例子:100/3=33...1,那一块钱要留在送礼人手里。)
        for(int j=0;j<num;j++)
        {
            char str[30];
            int lp;
            scanf("%s",str);
            for(lp=0;lp<n;lp++)//在数组中找到需要修改的数据点
            {
                if(strcmp(str,list[lp].name)==0)
                {
                    break;
                }
            }
            list[lp].income+=sig;//加上送礼收入
        }
    }
    for(int i=0;i<n;i++)
    {
        printf("%s %d\n",list[i].name,list[i].income-list[i].money);
    }
}
int main()
{
    solve();
    return 0;
}
```

---

