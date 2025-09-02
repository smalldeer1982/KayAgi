# OIer们的烦恼

## 题目背景

OIer 们有一个烦恼，他们本来可以随心所欲玩游戏上网的，自从学校机房开启 URL 过滤后，OIer 们就开始在 luogu上 面找游戏玩。

但是他们刚玩 slay.one 几天之后 slay.one 就被封禁了，只有工作日的中午 2 小时可以嗨皮，并且会有帅气的老师来巡视机房，他们该怎么办呢？

## 题目描述

有 3 个帅气的老师 $A$，$B$ 和 $C$。

有 5 个学生 $a$，$b$，$c$，$d$，$e$。当他们当中的某一个人开始玩游戏时，会显示一条消息 `XX started playing games!`。当他们当中的某一个人停止玩游戏时，会显示一条消息 `XX stopped playing games!`。

当某个老师来巡视机房时，会显示一条消息：`XX came!`。如果某个老师走了，会显示一条消息：`XX left!`。

如果老师发现某个学生**正在**玩游戏时，请输出该学生的姓名。

## 说明/提示

对于 $20\%$ 的数据，$1\leq N\leq 23.3333333333333$          
对于 $30\%$ 的数据，$1\leq N\leq 999.999$，有一个点答案为 `How Good Oiers Are!`。         
对于 $60\%$ 的数据，$1\leq N\leq 100,000$。    
对于$99.9999999999999999999\%$的数据，不保证全部消息都符合题意。           
对于 $100\%$ 的数据，$1\leq N\leq 233,333$，数据有梯度。
 
### Tips:
1.消息中肯定有奇奇怪怪的东西  
2.消息必须**完全符合题意**才有效  
3.样例很恶心，数据很纯真   
4.数据满足不会同时有多个**老师**巡视。     
5.注意仔细阅读**题目**和**样例**，**该题有坑！**      

## 样例 #1

### 输入

```
10
A B C
a b c d e
A came!
a started playing games!
b started playing games!
A left!
c started playing games!
d started playing games!
e started playing games!
B came!
PS:zhe_ge_yang_li_hen_zheng_chang!
B left!```

### 输出

```
a b c d e
How Bad Oiers Are!```

## 样例 #2

### 输入

```
10
I_Love_You I_Hate_You Why_Not_love_Me
Gay Che_Wan_Dang QwQ WuMaRu PDD
I_Love_You came!
Gay:Why do you love me?
I_Love_You died!
I_Love_You left!
Che_Wan_Dang prepared to play Dong_Fang!
But nobody came!
QwQ:I am so QwQ,I love myself!
PDD started playing Gay!
Gay died!And WuMaRu cried!
WuMaRu:dai su ki!```

### 输出

```
How Good Oiers Are!```

## 样例 #3

### 输入

```
20
Sans QwQ QAQ
A B C D E
A started playing B!
B started fighting with A!
A won!
A get 10000000 Exp!
QwQ:I and QAQ are looking at you all!
C died!
D died!
E recovered 123456789 HP!
E started playing games!
Sans came!
Sans:It is really a nice day today!
Sans:The birds are singing!
Sans:The flowers in bloom!
Sans:In a beautiful day like this!
Sans:People like you!
Sans:Should burn in hell!
E tried to attack Sans!
Sans was killed!
Sans:Papyrus,do you want something?
E still played his Undertale!```

### 输出

```
E```

## 样例 #4

### 输入

```
20
a b c
A B C D E
A came!
a started playing games!
b came!
b came together!
b came! dan_shi_zhe_ju_hua_bu_dui!
A came came came!
b start playing games!
b left!
c came!
c left!
A left!
B started playing games!
A started playing game!
C started palying games!
E started playing games!
lu_ren_jia came!
lu_ren_jia:What are you doing?
C&D:We are studying!
lu_ren_jia:Good boy!
C:qwq```

### 输出

```
How Good Oiers Are!```

# 题解

## 作者：⑨baka (赞：17)

[题目地址](https://www.luogu.org/problemnew/show/P4896)

#### 前言

这道题虽然很水但耗费了我一个多小时去调试...可能是我太弱了吧..~~还有测试数据3是什么鬼~~

#### Solution

此题就是一道模拟题...只要按照题目的意思模拟即可。但这道题也有一些坑点，比如getline多出来的空格，或者是打名字时多出来的回车...~~在这里我用了一种特殊的方法，就是什么也不判断~~

详见代码。

```
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
#define M 114514
string teacher[4],stu[6],s;
char s1[M],stop_play[110]={" stopped playing games!"};
char start_play[110]={" started playing games!"};
char come[110]={" came!"},l[110]={" left!"};//char字符在全局变量里定义为空格...所以如果gets有多出空格的话是不需要判断的
bool a[11],comes,play[11];
int len,n;
int main()
{
    cin>>n;
    for(int i=1;i<=3;++i)
        cin>>teacher[i];
    for(int i=1;i<=5;++i)
        cin>>stu[i];
    sort(stu+1,stu+6); //题目中要求按字典序
    for(int i=1;i<=n;++i)
    {
        cin>>s; //cin以空格为结束符号 所以可以用来判断此题中的学生名字或老师名字，并且也可以避免
        gets(s1); //gets以回车作为结束符号
        for(int j=1;j<=3;++j)
            if(s==teacher[j])
            {
                if(!strcmp(s1,come)) comes=1;//按题意模拟
                if(!strcmp(s1,l)) comes=0;
            }
        for(int j=1;j<=5;++j)
            if(s==stu[j])
            {
                if(!strcmp(s1,stop_play)) play[j]=0; //strcmp函数判断两字符串是否相同
                if(!strcmp(s1,start_play)) play[j]=1;
            }
        if(comes==1) //当老师在的时候判断学生们是否在打游戏
        {
            for(int j=1;j<=5;++j)
                if(play[j] && !a[j])
                {
                    ++len;
                    a[j]=1; //标记一下...
                }
        }
        if(len==5) break;
    }
    for(int i=1;i<=5;++i)
        if(a[i]==1)
            cout<<stu[i]<<" ";
    if(len==0) cout<<"How Good Oiers Are!";
    if(len==5) cout<<endl<<"How Bad Oiers Are!";
    return 0;
}
```

据大佬们说此题还可以用string.erase来解决...~~不过我太弱不会~~

---

## 作者：666DHG (赞：8)

- ### [Blog](https://666DHG.github.io/)

其实这道题真的很水

不信的话你们看：

>有$N$条消息。
先输入$N$，第$2$行输入$3$个老(shen)师(ben)的名字，第$3$行输入$5$个学(ju)生(ruo)的名字，第$4-N+3$行输入$N$条消息。

那么小的数据范围，才$3$个老师与$5$个学生，光是暴力都能过啦

比较**完全相同**字符串也很简单，这样就可以了：

```
if (a+b==c) /*do something*/
```

然后就一遍过了

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
string a[5]用来存储老师的名字
string b[10]用来存储学生的名字
string ans[10]用来存储被抓到学生的名字 
bool k1用来记录现在有没有老师在 
bool c[10]用来记录哪个老师来了 
bool p[10]用来记录哪个学生在玩游(fu)戏(bai)
int size用来记录被抓到的学生有多少人 
*/

int n,size;
bool k1,c[10],p[10],vis[10];
string a[5],b[10],t,ans[10];

int main()
  {
  	ios::sync_with_stdio(false);
  	cin.tie(0);
  	cin>>n;
  	cin>>a[1]>>a[2]>>a[3];
  	cin>>b[1]>>b[2]>>b[3]>>b[4]>>b[5];
  	getline(cin,t);
  	while (n--)
  	  {
  	  	k1=false;
		getline(cin,t);
		for (int i=1;i<=3;i++) if (a[i]+" came!"==t)
  	  	  {
  	  	  	c[i]=true;
  	  	  	break;
		  }
		for (int i=1;i<=3;i++) if (a[i]+" left!"==t)
  	  	  {
  	  	  	c[i]=false;
  	  	  	break;
		  }
  	  	for (int i=1;i<=5;i++) if (b[i]+" started playing games!"==t)
  	  	  {
  	  	  	p[i]=true;
  	  	  	break;
		  }
		for (int i=1;i<=5;i++) if (b[i]+" stopped playing games!"==t)
  	  	  {
  	  	  	p[i]=false;
  	  	  	break;
		  }
		for (int i=1;i<=3;i++) if (c[i]) k1=true;
		for (int i=1;i<=5;i++) if (k1&&p[i]&&!vis[i])
	  	  {
	  	  	vis[i]=true;
	  	  	ans[++size]=b[i];
		  }
	  }
	sort(ans+1,ans+1+size); //排序
	for (int i=1;i<=size;i++) cout<<ans[i]<<" ";
    //特判集体腐败与无人腐败现象
	if (size==0) cout<<"How Good Oiers Are!";
	if (size==5) cout<<"\nHow Bad Oiers Are!";
	return 0;
  }
```

~~突然感觉我的跑得很慢，居然987ms~~

~~反正能过就行~~

~~算了反正蒟蒻就应该写蒟蒻的代码，要有蒟蒻的亚子~~

---

## 作者：Alarm5854 (赞：8)

### 评价：
这道题目其实不难，不过这个样例太搞笑了，有玩电脑的老师，有玩$B$的$A$，笑了我半个小时，然后才开始解题，这也只用了我$45$分钟，而且有$20$分钟左右的时间因为函数少加取地址符在调试，$5$分钟的时间被这个~~不灵光~~的在线$IDE$所迷惑，直到我复制了两位大佬的题解调试，发现情况是一样的我才安心(当然我没有抄题解，解法也不太一样)，并成功的以$\bold{486ms/1.01MB}$的成绩$AC$本题，废话不多说，开始讲解解题思路。
### 解题思路:
1. 这道题其实也就要储存$8$个人的名字，$1$句话，进来的老师，正在玩游戏的学生和被逮捕(枪毙)的学生。名字和说的话可以用$string$类型储存；进来的老师，正在玩游戏的学生以及被逮捕的学生可以用$string$类型的$set$储存。
1. 输入$n$和$8$个名字可以用$cin$流输入，但是说的话要用$getline$，因为有空格。
1. 找名字有一点难，不过可以用$string$里的$find$函数来找名字，找到的位置是$0$则找到了。
1. 找到名字了以后，判断一下这个是老师还是学生，防止出现玩电脑的老师和逮捕老师的学生，再根据相应的身份执行相应的指令。
1. 有进来的老师的时候，如果有玩电脑的学生，就马上逮捕他，并把他加入黑名单(不用担心出现两个相同的人，$set$可以自动处理这个问题，并且不需要按字典序排序，自动排序，并且时间复杂度仅为$O(logp)$，$p$为被逮捕的学生数量，由于$p$很小，可以把它理解为常数)。
1. 做完这些操作之后，先判断有没有学生被捕，没有则输出$"How\ Good\ Oiers\ Are!"$，有则先输出黑名单人物，再判断被逮捕的人数是否为$5$，有则输出$"How\ Bad\ Oiers\ Are!"$，然后就可以$AC$本题了。
1. 如果你没看懂了我讲解的思路，没关系，我上代码了。
### 完整代码如下：
```cpp
    #include<bits/stdc++.h>//万能头，能用STL！
    #define se set<string>::iterator//用于减少代码长度
    using namespace std;//生成一间机房
    int n;//发生了n件事
    string A,B,C,a,b,c,d,e,s,name;//前8个为老师和学生的名字，name为当前的主角
    set<string>catched,playing,come;//catched为被枪毙的学生，playing为正在玩游戏的学生，come为来的老师
    bool finds(string &name,string &s)//这个地方就是把我卡了20分钟的地方，一定要在name前面加上取地址符，s前面可以不加
    {
        bool f=0;//判断是不是这八个人里面的其中一个
        if(!s.find(A,0)) name=A,f=1;//如果找到了，标记为1，否则为0
        if(!s.find(B,0)) name=B,f=1;
        if(!s.find(C,0)) name=C,f=1;
        if(!s.find(a,0)) name=a,f=1;
        if(!s.find(b,0)) name=b,f=1;
        if(!s.find(c,0)) name=c,f=1;
        if(!s.find(d,0)) name=d,f=1;
        if(!s.find(e,0)) name=e,f=1;
        return f;
    }
    void check(string &name,string &s)//判断这个人是什么身份
    {
        if(name==A||name==B||name==C)//是老师
        {
            if(s==name+" came!") come.insert(name);//老师看到机房里面这么热闹，他就来了
            else if(s==name+" left!") come.erase(name);//老师看到没有可逮捕的学生了，失望地走了
        }
        else if(name==a||name==b||name==c||name==d||name==e)//是学生
        {
            if(s==name+" started playing games!") playing.insert(name);//这个学生以为很安全，玩起了游戏
            else if(s==name+" stopped playing games!") playing.erase(name);//这个学生觉得游戏不好玩，停止玩游戏
        }
        /*这个函数专门防玩电脑的老师以及学生之间的机房惨案*/
    }
    int main()
    {
        ios::sync_with_stdio(false);//打消cin的缓存
        cout.tie(NULL);//打消cout的缓存
        cin>>n>>A>>B>>C>>a>>b>>c>>d>>e;//暴力输入
        getline(cin,s);//吃掉换行符
        while(n--)//相当于for(int i=1;i<=n;i++)
        {
            getline(cin,s);//输入发生的事情
            if(finds(name,s))//找名字
                check(name,s);//判断身份
            if(come.size()&&playing.size())//老师发现学生玩电脑
                for(se it=playing.begin();it!=playing.end();it++)
                    catched.insert(*it);//一个个枪毙掉
        }
        if(catched.size())//如果有被枪毙的学生，开始处理
        {
            for(se it=catched.begin();it!=catched.end();it++)
                cout<<*it<<' ';
            cout<<endl;
            if(catched.size()==5)//学生全被枪毙了
            cout<<"How Bad Oiers Are!\n";//他们的运气真差啊
        }
        else cout<<"How Good Oiers Are!\n";//一个都没有被枪毙，他们的运气真好啊
        return 0;
    }
```
这个程序的时间复杂度为$O(n)$，只不过常数大，最后一个点跑了$287ms$，不过算好了。当你$A$了这道题之后，别忘记给我点个赞，谢谢！

---

## 作者：DEATH_ENDER (赞：4)

看了**第三感233**的题解，觉得这一题这样写有点麻烦，对于蒟蒻~~（我）~~也不易懂。这里是我的见解，请大家同样采纳。

这一题看起来不容易，做起来也不容易。（~~但是**AC**了突然就很想嘲笑一下大家qwq~~）可以定义四个不同操作的字符串，每个各代表题目中的操作。每个在输入后就位，加上它们各需要的后缀（要加空格~~不加错了别怪我~~）。
每个字符串就位程序如下：
```cpp
string came[3],leave[3];
string start[5],stop[5];
//main函数里操作如下：
cin>>came[0]>>came[1]>>came[2];
cin>>start[0]>>start[1]>>start[2]>>start[3]>>start[4];
for(int i=0;i<5;i++) names[i]=start[i];
for(int i=0;i<3;i++){
	leave[i]=came[i];
	leave[i]+=" left!";
	came[i]+=" came!";
}
for(int i=0;i<5;i++){
	stop[i]=start[i];
	stop[i]+=" stopped playing games!";
	start[i]+=" started playing games!";
}
```
这样，每次输入以后，可以对照这些模板，判断出是否是符合题意的系统信息。

下一步就是输入每句消息了。~~（我系蒟蒻，也不知道为啥要多循环一次才能输入全）~~
我们可以定义一个string，作为每次输入的消息。只要每次都及时（立即）处理消息，即可做到既快捷又不占空间。※提醒一下，每次输入是会有空格的，得用getline才行（~~本蒟蒻竟然写完了对着输进一半的程序发了好一会儿呆。。。欲哭无泪TOT~~）

为了更快，我还把 _0~4_ 循环和 _0~2_ 循环写到一起~~，实际上是不必要的~~，这样又减少了 _3/100000000_ 秒qwq。
```cpp
for(int i=0;i<=N;i++){
		getline(cin,presnt); //present是现在的意思，为了不跟c++自带的东西撞衫，减掉了一个e,结果以后写的时候竟然忘了去e两次。。。
		for(int i=0;i<3;i++){
			if(came[i]==presnt) cancaught=1;//cancaught是能抓学生的意思，老师来了，自然能抓了，老师没来你难道有机器人监管啊 机器人：！#￥#@￥@￥%@$ 我：Σ(⊙▽⊙" 
			else if(leave[i]==presnt) cancaught=0;
			else if(start[i]==presnt) isplaying[i]=1;
			else if(stop[i]==presnt) isplaying[i]=0;
		} 
		for(int i=3;i<5;i++) 
			if(start[i]==presnt) isplaying[i]=1;//这个学生开始玩了
			else if(stop[i]==presnt) isplaying[i]=0;//他不玩了。。。他这么好好学习。。。不玩slay.one干么呢
		if(cancaught)
			for(int i=0;i<5;i++) if(isplaying[i]) caught[i]=1; //这个是第i个学生被抓到的信息，如果老师（hu）来了，他还在玩传（xian）说（shi）中的slay.one，就被（si）抓（ding）了
	}
```
结束了后，就要再次注意了※※要以字典序排列，我的程序曾经 _90_ ，就是没排字典序！就是没排字典序！就是没排字典序！(╯‵□′)╯︵┻━┻

可以定义一个排序函数CMP：
```cpp
bool cmp(const string &a,const string &b){
	int len_a=a.size();
	int len_b=b.size();
	int min_len=min(len_a,len_b);
	for(int i=0;i<min_len;i++)
	{
		if(a[i]>b[i])
		    return false;
		else if(b[i]>a[i])
		    return true;
	}
	if(len_a>len_b)
	  	return false;
	else
	    return true;
}
```
然后呢，把它加入 _sort_ 函数里就可以排序名字啦。。。（好像顺序被打乱了，不过下面就是拼顺序了）

但是，**还是有一个problem的**！！！

排完名字后，名字和是否被抓是不对应的！（我们不想误抓好人是不是。。。~~（像我一样的好人）~~）因此，我们还要用像倒醋和酱油的那个水爆的题一样，用 _names2_ 和 _caught2_ 来对应。
```cpp
string names2[5];
int caught2[5];
for(int i=0;i<5;i++) names2[i]=names[i];
sort(names2,names2+5,cmp);
```
这样就可以用两个名单对应， _caught2_ 的值也就出来了
```cpp
for(int i=0;i<5;i++)
	for(int j=0;j<5;j++){
		if(names2[i]==names[j]){
     		caught2[i]=caught[j];
			break;
		}
	}
```
~~可能是因为自己喜欢自(hen)己(cai)的程序吧，感觉这个比第三感的方便~~

还有一个最终的问题，how good the oiers are 和 bad 都没有输出
于是我们可以在输出被抓的蒟蒻名时，顺便判断一下，有被抓的good就不可能，然后再循环一下bad成不成立，判断完了就可以根据good 和 bad 的情况输出啦~~
```cpp
bool gd=true;
	for(int i=0;i<5;i++)if(caught2[i]){
		cout<<names2[i]<<" ";
		gd=false;
	}
	bool bd=true;
	for(int i=0;i<5;i++){
		if(!caught2[i]) bd=false;
	}
	if(gd) cout<<"How Good Oiers Are!\n";
	else if(bd) cout<<"\nHow Bad Oiers Are!\n";
	return 0;
```
所以，作为总结，这个程序就出来了：
```cpp
//T37785
#include<bits/stdc++.h>
using namespace std;
int N;
string came[3],leave[3];
string start[5],stop[5];
string presnt;
int cancaught;
int caught[5];
int isplaying[5];
string names[5];
bool cmp(const string &a,const string &b){
	int len_a=a.size();
	int len_b=b.size();
	int min_len=min(len_a,len_b);
	for(int i=0;i<min_len;i++)
	{
		if(a[i]>b[i])
		    return false;
		else if(b[i]>a[i])
		    return true;
	}
	if(len_a>len_b)
	  	return false;
	else
	    return true;
}
int main(){
	scanf("%d",&N);
	cin>>came[0]>>came[1]>>came[2];
    cin>>start[0]>>start[1]>>start[2]>>start[3]>>start[4];
	for(int i=0;i<5;i++) names[i]=start[i];
	for(int i=0;i<3;i++){
		leave[i]=came[i];
		leave[i]+=" left!";
		came[i]+=" came!";
	}
	for(int i=0;i<5;i++){
		stop[i]=start[i];
		stop[i]+=" stopped playing games!";
		start[i]+=" started playing games!";
	}
	for(int i=0;i<=N;i++){
		getline(cin,presnt);
		for(int i=0;i<3;i++){
			if(came[i]==presnt) cancaught=1;
			else if(leave[i]==presnt) cancaught=0;
			else if(start[i]==presnt) isplaying[i]=1;
			else if(stop[i]==presnt) isplaying[i]=0;
		} 
		for(int i=3;i<5;i++) 
			if(start[i]==presnt) isplaying[i]=1;
			else if(stop[i]==presnt) isplaying[i]=0;
		if(cancaught)
			for(int i=0;i<5;i++) if(isplaying[i]) caught[i]=1;
	}
	string names2[5];
	int caught2[5];
	for(int i=0;i<5;i++) names2[i]=names[i];
	sort(names2,names2+5,cmp);
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++){
			if(names2[i]==names[j]){
				caught2[i]=caught[j];
				break;
			}
		}
	bool gd=true;
	for(int i=0;i<5;i++)if(caught2[i]){
		cout<<names2[i]<<" ";
		gd=false;
	}
	bool bd=true;
	for(int i=0;i<5;i++){
		if(!caught2[i]) bd=false;
	}
	if(gd) cout<<"How Good Oiers Are!\n";
	else if(bd) cout<<"\nHow Bad Oiers Are!\n";
	return 0;
}
```
所有的注释和讲解看前面的部分，完整程序如上（原谅我用的万能头QWQ），还有问题的话请私信我。

~~突然想爆一句，How Good I Am!~~

---

## 作者：UnyieldingTrilobite (赞：3)

呼~调了一个多小时终于调出来了。

上手鉴定大膜你，细节不少。

思路：老师来的时候扫描学生，有肝slay.one的就直接记录下来。

学生开肝的时候康康是否有老师，要是有也直接记录下来。

**别忘了排序！！！**

番外：

然后······我就直接敲代码了。

90TE.

调了半天没调出来。

然后把string改成char数组后AC······

结论：

要么luogu的getline不能正常使用，

要么luogu评测姬的char数组比string快12倍。（

就直接上代码了吧，感觉注释还比较清晰，不懂的也珂以私聊窝。
```cpp
#include<bits/stdc++.h>
using namespace std;
char ls[10][1000],xs[10][1000];
//老师名字，学生名字
bool caut[10],isp[10],com;
//（某学生）是否已经被抓，是否正在肝slay.one，老师是否在巡视
int n,num;
//消息总数，被抓学生总数
char emm;
//占位符
string cm=" came!",lf=" left!",
       st=" started playing games!",
       ov=" stopped playing games!";
//一些消息字符串，后面判断用
char k[1000];//消息
int main(){
	scanf("%d\n",&n);
	for(register int i=1;i<=3;++i)scanf("%s%c",ls[i],&emm);
	for(register int i=1;i<=5;++i)scanf("%s%c",xs[i],&emm);
        //读入
	for(register int i=1;i<5;++i){
		for(register int j=i+1;j<=5;++j)if(strcmp(xs[j],xs[i])<0)swap(xs[i],xs[j]);
	}
        //sort好像有锅，数据又不大，缩以······n^2排序走起
	while(n--){
		gets(k);//getline出锅gets不出，真神奇
		for(register int i=1;i<=3;++i){
			if(k==ls[i]+cm){
				com=1;
				for(register int i=1;i<=5;++i)if(isp[i])caut[i]=1;
				break;
			}//老师来了扫描学生
			if(k==ls[i]+lf){
				com=0;
				break;
			}//老师走了
		}
		for(register int i=1;i<=5;++i)
        if(!caut[i]){//如果已经被抓，再开肝或在被抓也没意义了，对答案无影响
			if(k==xs[i]+st){
				if(com)caut[i]=1;//同上
				else isp[i]=1;
				break;
			}//学生开肝，康康老师
			if(k==xs[i]+ov){
				isp[i]=0;
				break;
			}//学生停止
		}
	}
	for(register int i=1;i<=5;++i)if(caut[i]){
		printf("%s ",xs[i]);
		++num;
	}//输出
	if(num)putchar('\n');
	else puts("How Good Oiers Are!");
	if(num==5)puts("How Bad Oiers Are!");
    //特判
	return 0;
}
```
最后宣传[blog](https://www.luogu.com.cn/blog/2007100723874wxz/)和[~~英文~~编程语言](https://www.luogu.com.cn/blog/2007100723874wxz/define)（滑稽~

**Over.**

---

## 作者：Tiphereth_A (赞：2)

这么好的题怎么能没有“位掩码”题解呢（滑稽

大致思路就是**用一个char来记录老师是否在机房和学生是否被抓到**（一共需要3+5=8位来记录，正好是一个char），再**用一个char记录被抓到的学生的编号**，就像这样：

```
char in_room, dead;
//in_room的1～3位记录老师，4～8位记录学生
```

然而为了降低调试难度，我们可以用两个char分别记录老师和学生的状态，就像这样：

```
char onlineT,onlineS,deadS;
//按字面意思理解即可
```

我们还需要定义一些函数来对它们进行操作，就像这样（这里以宏定义为例）：

```
#define _teacher_in(i)  onlineT|=1<<i //老师进机房
#define _teacher_out(i) onlineT&=~(1<<i) //老师出机房
#define _student_in(i)  onlineS|=1<<i //学生开始玩游戏
#define _student_out(i) onlineS&=~(1<<i) //学生停止玩游戏
#define _dead(i) deadS&(1<<i) //查询学生是否被发现
#define _kill_student deadS|=onlineS //学生被发现
```

其他就没什么了，可以参照其他题解~~没错我就是懒（理直气壮~~

---

## 作者：Viston (赞：2)

模拟即可。    
用两个map存老师学生的名字，用getline读取。    
如果符合题意，就标记，最后加个判断
```
#include<bits/stdc++.h>
using namespace std;
int a,i,j,ans;
bool came;
map<string ,int>mmp;
map<string ,int>mmq;
string s,s1[7],s2,s3;
char qqq;
int main(){
    ios::sync_with_stdio(false);
    cin>>a;
    for(i=1;i<=3;i++)
        cin>>s,mmp[s]=1;
    for(i=1;i<=5;i++)
        cin>>s1[i],mmp[s1[i]]=2,mmq[s1[i]]=0;
    sort(s1+1,s1+6);
    for(i=1;i<=a;i++)
    {
        cin>>s;
        char qqq=cin.get();
        if(qqq=='\n')
            continue;
        if(mmp[s]==1)
        {
            getline(cin,s2);
            if(s2=="came!")
            {
                for(j=1;j<=5;j++)
                    if(mmq[s1[j]]==1)
                        mmq[s1[j]]=2;
                came=1;
            }
            if(s2=="left!")
                came=0;
            continue;
        }
        if(mmp[s]==2)
        {
            getline(cin,s2);
            if(s2=="started playing games!")
            {
                if(came==0)
                    mmq[s]=1;
                else
                    mmq[s]=2;
            }
            if(s2=="stopped playing games!")
                if(mmq[s]!=2)
                    mmq[s]=0;
            continue;
        }
        getline(cin,s2);
    }
    bool my;
    for(i=1;i<=5;i++)
        if(mmq[s1[i]]==2)
            cout<<s1[i]<<' ',ans++;
    if(ans==5)
        cout<<"\nHow Bad Oiers Are!";
    if(ans==0)
        cout<<"How Good Oiers Are!";
    return 0;
}
```

---

## 作者：yu__xuan (赞：1)

### 题意简述

一群 $OIer$ 正在机房里颓废，如果某一名 $OIer$ 在老师在的时候颓废那么他就凉了，输出凉了的人的名字（按字典序），若没有人凉输出一行`How Good Oiers Are!`，如果全凉了在第二行输出`How Bad Oiers Are!`。

### 题目分析
我们可以看到 $n$ 并不大，所以模拟即可。

### $Code$

```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}//读优。

int n,cnt;
std::string ans[6],a[4],b[6],s;
bool playing[6],dead[6],at[4];
//playing 数组用来表示某个人玩没玩。
//dead 数组表示某个人凉没凉。
//at 数组表示某个老师在不在。

int main() {
	read(n);
	for(int i=1;i<=3;++i) std::cin>>a[i];
	for(int i=1;i<=5;++i) std::cin>>b[i];
	getchar();//getchar();使用 getchar() 读掉第 3 行最后的字符否则 getline 会将这个作为单独一行。
	for(int i=1;i<=n;++i) {
		getline(std::cin,s);//getline 可以读一整行包括空格和回车。
		for(int j=1;j<=5;++j) {//枚举 5 个 OIer。
			if(dead[j]) continue;//如果已经凉了就略过他
			std::string qwq=b[j]+" started playing games!"/*+char(13)*/;//string 类型的可以使用 + 将两个字符串拼起来
			if(qwq==s) playing[j]=true;
			qwq=b[j]+" stopped playing games!"/*+char(13)*/;
			if(qwq==s) playing[j]=false;
			if(playing[j]) {//如果 j 正在玩就去枚举老师看是否有老师在，若有 j 凉了。
				for(int k=1;k<=3;++k) {
					if(at[k]) {
						dead[j]=1;playing[j]=0;
						ans[++cnt]=b[j];
						break;
					}
				}
			}
		}
		for(int j=1;j<=3;++j) {//枚举老师
			std::string qwq=a[j]+" came!"/*+char(13)*/;
			if(qwq==s) at[j]=true;
			qwq=a[j]+" left!"/*+char(13)*/;
			if(qwq==s) at[j]=false;
			if(at[j]) {//如果老师在就去枚举 OIer，看是否有 OIer 在玩，若有他凉了。
				for(int k=1;k<=5;++k) {
					if(playing[k]&&!dead[k]) {
						dead[k]=1;
						playing[k]=0;
						ans[++cnt]=b[k];
					}
				}
			}
		}
	}
	std::sort(ans+1,ans+cnt+1);//对 string 类型的使用 sort 就是按字典序排序。
	if(cnt==0) printf("How Good Oiers Are!\n");
	for(int i=1;i<=cnt;++i) std::cout<<ans[i]<<" ";
	puts("");
	if(cnt==5) printf("How Bad Oiers Are!\n");
	return 0;
}
```

---

## 作者：chenxinyang2006 (赞：1)

这道题我一开始没注意字典序，以为是按照输入顺序输出名字，结果竟然还有80分，只能说数据水了

本题解法也没什么好说的，就是直接模拟。

唯一的难点可能就是判定当前的消息是哪个操作，以及分离出人名。实现不好的话，可能会很麻烦

我的建议是：强制认为第一个单词是人名，然后判定后面的部分和前面的部分是否同时合法，判定可以用$strcmp$，这样可以减少一定码量

顺便科普下$strcmp$用法：

```cpp
strcmp函数是string compare(字符串比较)的缩写，用于比较两个字符串并根据比较结果返回整数。

基本形式为strcmp(str1,str2)，若str1=str2，则返回0；若str1<str2，则返回负数；若str1>str2，则返回正数。
```

然后这道题就做完了，我也不知道为什么还是个绿题

代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream> 
using namespace std;
char come[105] = {' ','c','a','m','e','!'};
char start[105] = {' ','s','t','a','r','t','e','d',' ','p','l','a','y','i','n','g',' ','g','a','m','e','s','!'};
char left1[105] = {' ','l','e','f','t','!'};
char stop[105] = {' ','s','t','o','p','p','e','d',' ','p','l','a','y','i','n','g',' ','g','a','m','e','s','!'};
//打表出有效的句子。scanf读字符串不会读掉空格，所以前面要空一格

struct name{
    char type[100];
}tea[15],stu[15];//存储姓名，下标从0开始 


bool cmp(name a,name b){//将名字按照字典序排序 
    int len1 = strlen(a.type);
    int len2 = strlen(b.type);
    for(int i = 0;i <= max(len1,len2);i++){
        if(a.type[i] != b.type[i]){
            return a.type[i] < b.type[i];
        }
    }
}

int n;
int teacher[15];//teacher[i]表示i老师在不在 
int student[15];//student[i]表示i学生在不在玩游戏 
int ans[15];//ans[i]表示i学生有没有被发现 

int main(){    
    scanf("%d",&n);
    scanf("%s%s%s%s%s%s%s%s",tea[1].type,tea[2].type,tea[3].type,stu[1].type,stu[2].type,stu[3].type,stu[4].type,stu[5].type);
    char str[10000],name[1000];
    sort(stu + 1,stu + 6,cmp);
    for(int i = 1;i <= n;i++){
        scanf("%s",name);//默认第一个单词是名字，后面为内容。如果只有一个单词，那么scanf不会读入'\n',getline会读掉'\n',不会出事 
        cin.getline(str,1000);//1000可以改成别的,只要保证这个数大于一行字符数就行了
        for(int j = 1;j <= 3;j++){
            if(strcmp(tea[j].type,name) == 0){
                if(strcmp(come,str) == 0){
                    teacher[j] = 1;
                }else if(strcmp(left1,str) == 0){
                    teacher[j] = 0;
                }
            }
        }
        for(int j = 1;j <= 5;j++){
            if(strcmp(stu[j].type,name) == 0){
                if(strcmp(start,str) == 0){
                    student[j] = 1;
                }else if(strcmp(stop,str) == 0){
                    student[j] = 0;
                }
            }
        }
        int tag = 0;//tag表示这个时刻有没有老师巡查 
        for(int j = 1;j <= 3;j++){
            if(teacher[j]) tag = 1;
        }
        for(int j = 1;j <= 5;j++){
            if(tag && student[j]) ans[j] = 1;
        }
    }
    int count = 0;
    for(int i = 1;i <= 5;i++){
        if(ans[i]){
            count++;
            printf("%s ",stu[i].type);
        }
    }
    if(!count) printf("How Good Oiers Are!\n");
    else if(count == 5) printf("\nHow Bad Oiers Are!\n");//注意，这里全都被发现的时候要加回车，而全部没被发现的不用。因为全部没被发现的话，上一行什么都没输出 
    return 0;
}
```

顺便说一句，本题好像是可以加强的，比如把人名的个数开到$10 ^ 5$，然后限定输入字符数$ \le10 ^ 7$。这样搞一个字典树的题，也挺不错的，现在这个版本是真的水

**update on 2020.1.29 让代码变得好看一点，增加一些说明**

---

## 作者：disangan233 (赞：1)

纯字符串模拟**大水题**   
为啥这题难度都是蓝的？  
蛤？还需要题解？    
那我就勉为其难提示一下下：  
题目中名字的输入是**空格隔开**，可以使用$stringstream$，本蒟蒻不会用的字符数组重载排序。  
写得很复杂的代码：(因为时间复杂度对模拟题留下了阴影就写复杂了)  
```
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define re register ll
ll n,s[6],t[4],f[6],ff[6],tot,teacher,bjjjj;
string a,d;
struct did{
    char s[100];
}sn[6],tn[4];
bool operator <(did a,did b)
{
    for(re i=0;i<strlen(a.s)&&i<strlen(b.s);i++)
    {
        if (a.s[i]<b.s[i]) return 1;
        if (a.s[i]>b.s[i]) return 0;
    }
    return strlen(a.s)<strlen(b.s);
}
int main()
{
    scanf("%lld",&n);
    for(re i=1;i<=3;i++) cin>>tn[i].s; 
    for(re i=1;i<=5;i++) cin>>sn[i].s; scanf("\n");
    sort(sn+1,sn+6);
    for(re i=1;i<=n;i++)
    {
        re ans[6];
        getline(cin,a);
        re l=a.length();
        string h="";
        for(re j=l-6;j<l-1;j++)
        h+=a[j];
        if(h=="games")
        {
            string bj1="",bj2="",bj3="";re bjj=-1;
            for(re j=l-14;j<=l-8;j++)
            bj1+=a[j];
            if(bj1=="playing")
            {
                for(re j=l-22;j<=l-16;j++)
                bj2+=a[j];
                if(bj2=="started") bjj=1;
                else if(bj2=="stopped") bjj=0;
                if(bjj>=0)
                {
                    for(re j=0;j<=l-24;j++)
                    bj3+=a[j];
                    for(re j=1;j<=5;j++)
                    if(bj3==sn[j].s)
                    {
                        s[j]=bjj;
                        break;
                    }
                }
            }
        }
        else if(h==" came"||h==" left")
        {			
            string bj="";
            re bjj=0;
            for(re j=0;j<=l-7;j++)
            bj+=a[j];
            for(re j=1;j<=3;j++)
            if(bj==tn[j].s)
            bjj=1;
            if(bjj)
            {
                if(h==" came") teacher=1;
                else teacher=0;
            }
        }
        if(teacher)
        for(re j=1;j<=5;j++)
        if(s[j])
        {
            f[j]=1;
            bjjjj=1;
        }
    }
    for(re i=1;i<=5;i++)
    if(f[i])
    {
    	cout<<sn[i].s<<" ";
        tot++;
    }
    if(tot==0) cout<<"How Good Oiers Are!"<<endl;
    else if(tot==5) cout<<endl<<"How Bad Oiers Are!"<<endl;
    return 0;
}
```

---

