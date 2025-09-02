# yyy loves Easter_Egg I

## 题目背景

Soha 的出题效率着实让人大吃一惊。OI，数学，化学的题目都出好了，物理的题还没有一道。于是，Huntfire，absi2011，redbag 对 soha 进行轮番炸，准备炸到 soha 出来，不料，人群中冲出了个 kkksc03……

## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1456.png)

![](https://cdn.luogu.com.cn/upload/pic/1455.png)

yyy loves OI（Huntfire），yyy loves Maths（redbag），yyy loves Chemistry（absi2011）对 yyy loves Physics（soha）进行轮番炸，轰炸按照顺序进行，顺序为 Huntfire，redbag，absi2011。

现在这一题中，我们不考虑太复杂的队形形式。我们认为只要这一句内含有且恰好含有一次@，@的人和上一句话一样就算为队形。

比如以下也视为队形：

- `yyy loves OI : @yyy loves Microelectronic`
- `yyy loves Maths : @yyy loves Microelectronic 我佩服soha的出题效率`
- `yyy loves OI : @yyy loves Microelectronic +1`
- `yyy loves Chemistry : +1 @yyy loves Microelectronic`

若 @ 的人与第一个人不同，就算队形被打破。若这个人在队形被打破之前出来发言了，或者就是他打破队形了，就算（油）炸成功了。

若（油）炸成功，输出 `Successful @某某某 attempt`，若队形被破坏先输出 `Unsuccessful @某某某 attempt`，再输出队形第一次被破坏的行数与第一次破坏队形的人的 $\text{id}$。

如果队形一直没被打破，就先输出 `Unsuccessful @某某某 attempt`，再输出队形的长度，最后输出 `Good Queue Shape`。

~~p.s.yyy loves Microelectronic 是 kkksc03~~



## 说明/提示

**@yyy loves Physics 我佩服你的出题效率**

此题仅吐槽 soha，纪念出题者的队形，此队形长达 $91$ 行。

对于 $100\%$ 的数据,每行消息长度 $\le$ $10^3$。 

- 保证行数不超过 $5\times 10^4$；
- 保证输入文件大小不超过 $4\text{MB}$；
- 保证第一个说话的一定在 @ 某人；
- 保证大家的名字都是 $\text{yyy loves ***}$ 的格式；
- 保证每个人说的话中没有 `:`；
- 保证第一个说话的一定艾特了一个人且只 @ 了一个人；
- 保证第一个说话的一定不会艾特自己；
- 保证文件结束一定有一行空行，方便你判定文件结束；
- 并不保证后面说话的艾特了几个人 然而艾特人数不为一个人视为破坏队形；
- 并不保证后面说话是否会反复艾特同一个人；
- 并不保证被炸的人一定破坏队形；
- 并不保证这一题是或不是压轴题；
- 并不保证这一套比赛存在压轴题；
- 并不保证下一套比赛和这一套比赛一样水；
- 并不保证群里除了这 $4$ 个人和 kkksc03 以外没有别人了；
- 并不保证你没 AC 这题的情况下吐槽 soha 不会出事儿；
- AC 了可以吐槽 soha 一句，soha 不会介意。

## 样例 #1

### 输入

```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Microelectronic : ni men wu liao me 
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv

```

### 输出

```
Unsuccessful @yyy loves Physics attempt
4
yyy loves Microelectronic
```

## 样例 #2

### 输入

```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Physics : ni men gou le 

```

### 输出

```
Successful @yyy loves Physics attempt
```

# 题解

## 作者：ironwheel (赞：122)

~~求各位神犇点赞~~

-------------
首先介绍一下函数：

```
string search(string s,int l){
    string kk;
    int spacesum=0;
    for(register int i=l;s[i]!=' '&&i<s.size();i++){
        if(s[i]==' ') spacesum++;
        if(spacesum==3||s[i]==13) break;
        kk+=s[i];
    }
    return kk;
}
```
search函数：找到l位置以后的名字（yyy loves____）

返回一个名字，原理不多说

注意如果发现第二个点WA且有以下这种操作：

On line 1 column 35, read 
 att, expected atte. 得分0
 
 那你一定就是没有特判换行符了！！！
 ---
 ~~没错，就是spacesum那玩意儿~~
 
 再次膜拜一下讨论区里的@treasure 大佬

```
string find_name(string s){
    string a=search(s,10);
    return a;
}
```
find_name函数：寻找发消息的人的名字（同上）

其实就是调用search函数，利用名字一定是yyy loves XXX
```
int kkk(string q){
    int sum=0,gg;
    for(register int i=0;i<q.size();i++){
        if(q[i]=='@'){sum++;gg=i;}
    }
    if(sum!=1)return 0;
    else return gg;
}
```
kkk函数：（逃

原理：扫一遍寻找一句话中@的个数

以及@的位置（方便search）

如@的个数不为1则返回0，否则返回@的位置

```
string wss(string s){
    int g=kkk(s);
    if(g!=0)return search(s,g+11);
    else return "tenyearsatreehundredyearsatreeman";
}
```
wss函数：

原理：调用kkk函数，搜索被@的人的名字；

若@的人数不为1个，直接返回一段乱码（逃

然后就是主程序：

不停输入，判断空行（保证文件结束一定有一行空行 方便你判定文件结束）

如果跳出来的人（find_name(a)）和@的人一样，~~油~~炸成功，直接结束

否则如果被@的人(wss(a))与第一个人@的人不一样（包括不@或@了多人），破坏队形，返回

如果输入结束，没有停止运行，退出了：队形没有被破坏，输出
```
int main(){
    getline(cin,a);
    mega=wss(a);
    while(++jl){
        getline(cin,a);
        if(a.size()==1)break;
        //cout<<wss(a)<<' '<<mega<<' '<<"\n";
        if(find_name(a)==mega){
            cout<<"Successful @yyy loves "<<mega<<" attempt";
            return 0;
        }//轰炸成功
        else if(wss(a)!=mega){
            cout<<"Unsuccessful @yyy loves "<<mega<<" attempt"<<endl;
            cout<<jl+1<<endl;
            cout<<"yyy loves "<<find_name(a)<<endl;
            return 0;
        }//队形被破坏
    }
    cout<<"Unsuccessful @yyy loves "<<mega<<" attempt\n";
    cout<<jl<<"\n";
    cout<<"Good Queue Shape";//队形保持
}
```
---
~~华丽丽地结束~~

tips：如果有认识我的人可以看一下wss函数返回的乱码，可以断句读一下~~貌似跑题了~~（逃

---

## 作者：Deny_小田 (赞：21)

……终于做完了。。

这题不错，用来练练字符串处理。


刚开始使用最朴素的方法，结果最高没超过30分。。


**吐槽一句：#4 .in 文件过大，导致无法下载，不然我用朴素方法也有可能AC的/(ㄒoㄒ)/~~**


AC算法参考某位神犇。——特此说明，不要说我侵权。。


思路：找到每个@和轰炸的人，判断是否相同。

具体看代码。

代码附赠注释：


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int size = 1005;
        //注意，这里初始化不能 = 0！ 因为 = 0之后第一个while循环还没开始循环就退出了
int c = 1;
char s[size],name[size],importer[size],t[size];

int main(int argc, char const *argv[]){
//     freopen("Luogu1580_2.in","r",stdin);
                //注意！这里使用的是gets，所以他遇到空格是就会停止
    gets(s);                    //s用来记录每一句话
    sscanf(strstr(s, "@"), "@yyy loves %s", name);                    //本来我是想用string的，但是sscanf特别方便
    while(c++){
        gets(s);
        int len = strlen(s);
        if(len == 1) break;

        sscanf(s, "yyy loves %s",importer);                //输入名字
        if(!strcmp(importer, name)){                    //如果相同，即轰炸成功
            printf("Successful @yyy loves %s attempt\n",name);
            return 0;
        }
            //count函数包含于#include <algorithm>中，作用是查看字符串中最后一个参数字符的个数
            //后面的意思是有人没有按照队列轰炸，故轰炸不成功
        if(count(s, s+len, '@') != 1 || (sscanf(strstr(s, "@"), "@yyy loves %s", t), strcmp(t, name))){
            printf("Unsuccessful @yyy loves %s attempt\n", name);
            printf("%d\n", c);
            printf("yyy loves %s\n", importer);                    //输出破队形的人

            return 0;
        }
    }
                //最后一种情况：
                //队形一直没有被打破
    printf("Unsuccessful @yyy loves %s attempt\n", name);
    printf("%d\n", c-1);
    printf("Good Queue Shape\n");

    return 0;
}
```

---

## 作者：jyz666 (赞：16)

~~我想这篇题解应该是最短的了吧。。。~~

[题面](https://www.luogu.com.cn/problem/P1580)

解释我就不解释了，见代码

```cpp
#include<bits/stdc++.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define Gmax(x,y) (x<(y)&&(x=(y)))
#define Gmin(x,y) (x>(y)&&(x=(y))) 
#define abs(x) ((x)<0?-(x):(x))
#define swap(x,y) (x^=y^=x^=y)
#define uint unsigned int
#define LL long long
#define ull unsigned long long
#define INF 1000000000
#define N 1000 
#define DRC_AK_NOI true
#define GetAt(s,t) (sscanf(strstr(s,"@"),"@yyy loves %s",t))
using namespace std;
char now[N+5],At[N+5],cur[N+5],target[N+5];
inline bool check(char *s,int len)
{
    register int i,tot=0;
    for(i=0;i<len;++i) if(!(s[i]^'@')&&tot++) return false;
    return tot;
}
int main()
{
    register int cnt=1,len;
    gets(now),GetAt(now,target);
    while(DRC_AK_NOI)
    {
        if(++cnt,gets(now),len=strlen(now),len<2) return printf("Unsuccessful @yyy loves %s attempt\n%d\nGood Queue Shape",target,cnt-1),0;//判断是否读完
        if(sscanf(now,"yyy loves %s",cur),!strcmp(cur,target)) return printf("Successful @yyy loves %s attempt",target),0;//比较当前说话的人与target
        if(!check(now,len)) return printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",target,cnt,cur),0;//判断这句话中存在的@个数是否为1
        if(GetAt(now,At),strcmp(At,target)) return printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",target,cnt,cur),0;//判断被@的人是否为target
    }
    return 0;
}
```
~~点个赞再走呗~~



---

## 作者：一叶知秋。 (赞：16)

这么多C++，那我来发一个C党的代码吧。

~~（本人全洛谷最弱蒟蒻，勿喷）~~

一言不合上代码：

```c
#include<stdio.h>
#include<string.h>
char s[100001],bz[100001],dmz[100001];
int maohao,xf,ls,sss,lll,xxf,xxxf;
int n,d,a[1000001],i,j,k,f,cjf,l;
int main() {
    ls=1;
    gets(s);//第一个要特殊输入，以便寻找队列要@的人
    l=strlen(s);
    if(s[l-1]=='/r')s[l-1]=' ';
    for(i=10; i<l; i++) {
        if(f) {
            k=0;
            for(j=i; j<l; j++) {//记录人名
                if(s[j]==' ')xxf++;
                if(xxf==3||s[j]==13)break;//特判符
                bz[lll]=s[j];
                lll++;
            }
            break;
        }
        if(s[i]=='@')f=1;
    }
    while(gets(s)) {//输到没有为止
        l=strlen(s);
        if(l<2)break;//以防结尾回车
        if(s[l-1]=='/r')s[l-1]=' ';
        ls++;
        if(cjf==0&&xf==0) {
            xxxf=0;
            char mz[100001]="yyy loves ";
            sss=10;
            j=0;
            f=0;
            l=strlen(s);
            for(i=0; i<l; i++) {
                if(s[i+1]==':') {
                    maohao=i;
                    break;
                }
                if(s[i]==bz[j])j++;
                mz[i]=s[i];
                sss++;
            }
            if(j==lll) {//油炸成功
                cjf=1;
                continue;
            }
            for(i=maohao+1; i<l; i++) {
                if(f) {
                    k=0;
                    for(j=i; j<l; j++) {
                        if(s[j]==bz[k])k++;
                        else break;
                    }
                    if(k!=lll)xf=ls;//队列被破坏
                    break;
                }
                if(s[i]=='@')f=1;
            }
            if(f==0)xf=ls;
            for(i=0; i<sss; i++)//录下当前说话的人的人名
                dmz[i]=mz[i];
            for(i=0; i<l; i++)if(s[i]=='@')xxxf++;
            if(xxxf>1) {//判断@个数
                xf=ls;
                break;
            }
        }
    }
    if(cjf)printf("Successful @%s attempt",bz);//输出
    else if(xf) {
        printf("Unsuccessful @%s attempt\n",bz);
        printf("%d\n",xf);
        puts(dmz);
    } else {
        printf("Unsuccessful @%s attempt\n",bz);
        printf("%d\n",ls);
        puts("Good Queue Shape");
    }
    return 0;
}
```

这道题从算法上来说其实不难，但主要是注意一些细节

最后%%%soha

~~题目要我干的~~

---

## 作者：HanPi (赞：7)

~~这道题坑是真的多~~
我在这里列举一下需要注意的坑:

- 如果成功或失败了,就**直接结束**
- 有多个 $@$ 的**直接判失败**
- 用gets要处理**换行**

### 说下大体思路

其实就是道模拟题

运用scanf的特性,我们阔以直接读入发言人的姓名.
然后处理发言信息,抠出被At的人.

1. 如果是第一个发言的人,把At的姓名记录下来 ```firstAtName``` .

2. 如果发言者姓名是 ```firstAtName``` ,就判成功.

3. 如果At的人不是 ```firstAtName``` ,就判失败.

4. 如果没有At人,但为 2. 也判成功,否则判失败.

5. 如果输入结束了,因为保证了每组数据末尾都有换行,所以scanf在读入换行时不会返回EOF,需要我们自己判断

### 代码

```c
#define _CRT_SECURE_NO_DEPRECATE // VS特判
#include <stdio.h>
#include <string.h>

#if _MSC_VER // VS特判++
#define gets gets_s // get_s自动帮我丢掉了换行,害我不浅
#endif

int GetAtName(const char str[], char dest[])
{
	int i = 0, j = 0, flag = 1; // 标识是否没有@
	while (str[i])
	{
		if (str[i] == '@')
		{
			flag = 0;
			break;
		}
		i++;
	}
	if (flag)return 0;
	i += 11; // 直接跳过定的部分
	while (str[i] && str[i] != ' ' && str[i] != '\r')
	{
		dest[j++] = str[i++];
	}
	// 如果还有@
	while (str[i++]) { if (str[i] == '@') { dest[0] = 0; return 1; } }
	dest[j] = 0;
	return 1;
}

char name[1007], info[1007], atname[1007], firstAtName[1007];
int line, firstAt = 1,r;
int main()
{
	//freopen("P1580_5.in", "r", stdin);
	while (++line)
	{
		if (scanf("yyy loves %s : ", &name) == EOF)break;
		if (!name[0])break; // 没有读入的情况下不会改变
		gets(info);
		if (GetAtName(info, atname))
		{
			//printf("\t_%s_ @ %s\n", name, atname);
			if (firstAt)
			{
				strcpy(firstAtName, atname);
				firstAt = 0;
			}
			if (strcmp(firstAtName, name) == 0)
			{
				printf("Successful @yyy loves %s attempt\n", firstAtName);
				return 0;
			}
			if (strcmp(firstAtName, atname) != 0)
			{
				printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s\n", firstAtName, line, name);
				return 0;
			}
		}
		else
		{
			if (strcmp(firstAtName, name) == 0)
			{
				printf("Successful @yyy loves %s attempt\n", firstAtName);
				return 0;
			}
			else
			{
				printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s\n", firstAtName, line, name);
				return 0;
			}
		}

		//printf("\t_%s_ @ %s\n", name, atname);
		name[0] = 0; // 我们无需清空字符串,scanf会覆盖原字符串,但为了判断结尾换行,给它赋一个标识值
	}
	printf("Unsuccessful @yyy loves %s attempt\n%d\nGood Queue Shape\n", atname, line-1);
	return 0;
}
```
~~尽然只有 $23ms$ , 这么快的吗??~~

---

## 作者：Wen_kr (赞：6)

比较朴素的方法过的这道题。

全程序只用了cin cout以及if while函数

感觉这道题难度不是那么高，可以水过去。

        
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int longstr=0,yiding=0,yiaite=1;//行长，是否已经确定了要炸的人，艾特了几个人
    string now,zha,name,panding; //正处理的，炸的人的名字，说话者的名字，判定是否为说话者
    while(cin>>now)    //不断输入直到结束
    {
        if(now=="yyy") //如果当前处理为yyy
        {
            cin>>now;  //再输入一次
            if(now=="loves")  //如果为loves
            {
                cin>>now;  //继续输入
                if(now!="@yyy")  //如果不是艾特
                {
                    cin>>panding;  //输入判定
```
/\*这里为什么不用now呢？主要是因为
now如果储存了名字的话，那么再次输入会顶掉名字，因此另外用一个字符串 \*/

```cpp
                    if(panding==":")  //如果是冒号
                    {
                    if(yiaite!=1)  //如果上一个人没有艾特人
                    {
                    cout<<"Unsuccessful @yyy loves "<<zha<<" attempt"<<endl;
                    cout<<longstr<<endl;
                    cout<<"yyy loves "<<name<<endl;
                    return 0;   //输出，直接返回0，不需要继续查找
                    }
                    longstr++;  //新的一排
                    yiaite = 0;  //重新回到没有艾特的值
                    name = now;  //名字变为now储存的
                    if(name==zha)  //如果现在的名字成了要炸的人，则成功了
                    {   
                        cout<<"Successful @yyy loves "<<zha<<" attempt"<<endl;
                        return 0;
                    }
                    continue;  //继续执行
                    }
                    else if(panding=="@yyy")  //因为判定如果是@yyy的话，则会无法判定艾特，因此这里goto e2（可改为 now = panding;)
                    goto e2;
                }
            }
        }
        if(now==":")    //如果now是冒号
        {
            longstr++;
            yiaite = 0;    //同上所述
        }
        if(now=="@yyy")    //如果当前值是@yyy
        {
```
e2:
```cpp
            yiaite++;   //艾特了一个人
            cin>>now>>now;    //判定艾特了谁
            if(yiding==0)   //如果第一次出现艾特
            {
                zha = now;  //确定要炸的人
                yiding = 1;  
                continue;
            }
            if(now!=zha)   //如果当前艾特的人不是炸的人
            {
                cout<<"Unsuccessful @yyy loves "<<zha<<" attempt"<<endl;
                cout<<longstr<<endl;
                cout<<"yyy loves "<<name<<endl;
                return 0;  //输出失败
            }
        }
    }
    if(yiaite!=1)   //因为循环结束的时候没有判定艾特人，这里补上
    {
        cout<<"Unsuccessful @yyy loves "<<zha<<" attempt"<<endl;
        cout<<longstr<<endl;
        cout<<"yyy loves "<<name<<endl;
        return 0;
    }
    cout<<"Unsuccessful @yyy loves "<<zha<<" attempt"<<endl;
    cout<<longstr<<endl;
    cout<<"Good Queue Shape"<<endl;
    return 0;  //到最后还没有炸出来，输出失败（记住return 0 是必要的）
}
```

---

## 作者：Mingoal (赞：6)

4ms，挺快的

直接贴代码，解释在代码里有

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1003],s1[1003],s2[1003],fry[1003];
//s1是当前的人的id，s2是s1@的人的id，fry是被油炸的人的id
int i;
void change(char *s){
//计算s1和s2
    int i,k,l=strlen(s);
    s[l-1]=' ';
    for (i=10;s[i]!=' ';i++) s1[i-10]=s[i];//算s1
    for (;s[i]!='@';i++);
    for (i+=11,k=i;s[i]!=' ';i++) s2[i-k]=s[i];//算s2
    for (;i<l;i++)//判断特殊情况：同时@两个人算破坏队形
        if (s[i]=='@'){
            s2[0]=' ';
//把s2随便改一下，待会儿判断的时候可以知道队形被破坏了
            return;
        }
}
bool cmp(char *s1,char *s2){//比较s1和s2是否一样
    int l1=strlen(s1),l2=strlen(s2);
    if (l1!=l2) return 0;
    for (int i=0;i<l1;i++)
        if (s1[i]!=s2[i]) return 0;
    return 1;
}
int main(){
    gets(s);
    change(s);
    memcpy(fry,s2,sizeof(s2));
    while (gets(s)){
        i++;
        memset(s1,0,sizeof(s1));
        memset(s2,0,sizeof(s2));
        change(s);
        if (cmp(s1,fry)){//成功油炸
            printf("Successful @yyy loves %s attempt",s1);
            return 0;
        }
        if (!cmp(s2,fry)){//队形破坏
            printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",fry,i+1,s1);
            return 0;
        }
    }
    printf("Unsuccessful @yyy loves %s attempt\n%d\nGood Queue Shape",fry,i);//队形一直没被打破
}
```
我在打程序的时候遇到一个问题，在这里顺便问一下：如何在函数里传入变量型参的数组？


---

## 作者：AFOier (赞：5)

说实话这题确实挺水的，纯字符串模拟就能过了，不需要任何算法，我看这道省选/NOI-的题还没有P1844某普及/提高-的纯模拟难度高吧。注意题目下面说明一定要看清楚，我就是被@两个人算打破队形这个坑了好几次。。。总之就是看清题目，打好代码，然后就A了。呵呵。最后%%%soha大佬。问我为什么？~~无可奉告~~题面让我干的@\_@。

模拟题不上代码怎么行，蒟蒻c++代码参上：


```cpp
#include <string>//字符串专属头文件
#include <iostream>
using namespace std;
int ans;//计算队列长度的
string a,at;//at在这里面大概等于@
string fname(string b)//find name:找说话的人名字
{
    int w=0;string s="";
    while(b[w+1]!=':')w++;//找到冒号位置
    for(int i=0;i<w;i++)//循环
    s+=b[i];//其实只要把冒号前面的都加起来返回就行了
    return s;
}
string fat(string b)//find @:找@的第一个人
{
    int w=0;
    while(b[w]!='@'&&w<b.size()-1)w++;
    if(w==b.size()-1)return "abcd";//如果这个人没有@任何人，那么就是打破队列，返回一个非名字的字符串，返回主程序后可以判断并输出
    w++;
    string s="";
    while(b[w]!=' ')
    s+=b[w],w++;s+=' ';//加入"yyy "//注意有空格
    w++;
    while(b[w]!=' ')
    s+=b[w],w++;s+=' ';//加入"loves "，注意有空格
    w++;
    while(b[w]!=' '&&w<b.size()-1)
    s+=b[w],w++;//加入最后那一段，如"OI"，注意无空格，不过想要有空格也行，就是挺麻烦
    return s;//成功加入全名，返回
    //这个找名字的步骤可能有些麻烦，大神们可以修改，本蒟蒻不想改了
}
int ats(string pp)//判断这个人@了几个人，不多说了
{
    int ss=0;
    for(int i=0;i<pp.size();i++)
    if(pp[i]=='@')ss++;
    return ss;
}
int main()
{
    getline(cin,a);ans=1;//必须用getline，因为有空格
    at=fat(a);//找第一个被@的人，即被轰炸的人的名字
    while(getline(cin,a))//一直输入
    {
        int ww=0;
        while(a[ww]==' ')ww++;
        if(ww==(a.size()-1))break;//前面这些其实是判断是否为空格串，如果就退出循环。如果不及时退出，会在判断队列长度时出问题。补充一下，其实如果能读到空格串说明轰炸没有成功并且没有人打破队列，所以可以在这里直接输出，不过我选择的是在循环后输出
        ans++;//队列长度+1
        string p=fname(a),q=fat(a);//找出当前说话的人的名字以及他@的人
        if(p==at)//如果说话的人是被轰炸的人，说明轰炸成功，输出，程序结束
        {
            cout<<"Successful @"<<at<<" attempt"<<endl;
            return 0;
        }
        if(q!=at||ats(a)!=1)//如果这个人@了一个不是被轰炸的人或者没有@人亦或是@了不止一个人，那么视为打破队列，输出，程序结束
        {
            cout<<"Unsuccessful @"<<at<<" attempt"<<endl;
            cout<<ans<<endl<<p<<endl;return 0;
        }
    }
    cout<<"Unsuccessful @"<<at<<" attempt"<<endl;
    cout<<ans<<endl<<"Good Queue Shape"<<endl;//如果成功到了while外面，说明轰炸失败，并且没人打破队列，输出
    return 0;
}
```

---

## 作者：Peter_Z (赞：4)

题外话：

历尽千辛万苦才AC这道题……可能是沉迷于用char数组而无法自拔太久了……都不会用string了……

## 进入正题：

此题有几点需要注意的地方：

1.输入一个字符串之后，把最后一位改成空格（原来是回车），因为如果@符号在最后，而第一次找（油）炸的人是谁用空格判断，就会因为数组越界RE……（或WA）。


2.后面说话的人可能同时@多个人，虽然没有因为这个而WA但还是要提醒一下。

3.注意提取@的人的时候边界不要搞错，就因为这点WA多次……

orz

然后其他地方用string类型的函数轻松解决。

如果string类型函数不会，参照这篇题解：[网页链接](https://blog.csdn.net/u013046610/article/details/72674185)

**~~BB完了~~**

### 代码
```cpp
#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
const int Size=100001;
string a,b,name;
int len;
void checkname(int pos) {		//把@的人存在b数组里
    bool flag=false;
    int count=0;
    for(int i=pos+11; i<len; i++) {		//@yyy loves xxxxx
        if(a[i]==' ') {
            count=i-pos-1;
            break;
        }
    }
    b=a.substr(pos+1,count);
}
void init() {		//初始化一下
    getline(cin,a);
    a[a.length()-1]=' ';
    int pos=a.find('@');
    len=a.length();
    checkname(pos);
    name=b;
}
int main() {
    init();
    int qlen=1;
    while(getline(cin,a) && a.length()>1) {	//循环输入
        qlen++;
    	a[a.length()-1]=' ';
        len=a.length();
        int pos=a.find("@");		   //第一个@的位置
        int pos2=a.find(":");		  //第一个:的位置
        string ans=a.substr(0,pos2-1);
        if(name==ans) {		//
        	cout<<"Successful @"<<name<<" attempt";
            return 0;
        }
        if(pos==-1) {
            if(name==ans) {			//炸成功
                cout<<"Successful @"<<name<<" attempt";
                return 0;
            } else {
                cout<<"Unsuccessful @"<<name<<" attempt"<<endl;
                cout<<qlen<<endl;
                cout<<ans<<endl;
                return 0;
            }
        } else {
            checkname(pos);
            a[pos]='.';
            if(a.find("@")!=-1 || b!=name) {	//打破队形
                int pos2=a.find(":");
            	string ans=a.substr(0,pos2-1);
    			cout<<"Unsuccessful @"<<name<<" attempt"<<endl;
                cout<<qlen<<endl;
                cout<<ans<<endl;
                return 0;
            }
        }
    }
    /*如果始终没打破队形就输出以下这些*/
    cout<<"Unsuccessful @"<<name<<" attempt"<<endl;
    cout<<qlen<<endl;
    cout<<"Good Queue Shape"<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：4)

这么多题解都没有用scanf格式化输入做的吗qwq...
这道题用scanf格式化输入做起来非常简单啊..
输入最关键在于这行代码:
```cpp
sscanf(buff,"yyy loves %[^: ] :%*[^@] @yyy loves %s%*s",name,at);
```
```plain
yyy loves %[^: ] :%*[^@] @yyy loves %s%*s
```
这个格式化字符串的含义是，先读入yyy loves 这几个字符，然后一直读，读到冒号或者空格为止(如果读到了冒号或者空格会扔回输入流)，并且把到这里读到的字符串放到第一个变量里，然后再读一个冒号，然后再接着读入，一直读到@为止，并且到at为止的字符串直接扔掉(加了一个*),然后读@yyy loves %s，然后再读入一个字符串，并全部扔掉。  
sscanf返回读入元素的数目。  
可一个根据读入元素的数目来判断有没有@  
举例:  
```plain
yyy loves [name] : before_at @yyy loves [target] after_at
[name]会被放到字符数组name中，[target]会被放到字符数组at中，其他读入的内容全部扔掉
```
```plain
yyy loves [name] : nothing
[name]会被读入到name中，而at不会有任何改动。
```

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <inttypes.h>
typedef int int_t;

using std::cin;
using std::endl;
using std::cout;

char buff[1 << 10];

int main(){
    int_t index = 1;
    int_t len = 0;
    std::string curr = "";
    do{
        cin.getline(buff,sizeof(buff));
//        cout<<"input "<<buff<<endl;
        if(strlen(buff) == 0) break;
        if(buff[0] == '\n' || buff[0] == '\r') break;
        int_t atcount = 0;
        for(char* ptr = buff;*ptr != '\0';ptr ++) atcount += *ptr == '@';

        char name[1 << 10],at[1 << 10];
        int count = sscanf(buff,"yyy loves %[^: ] :%*[^@] @yyy loves %s%*s",name,at);
//        cout <<"name = '"<<  name <<"' at = '"<<at <<"' count = "<< count <<" curr = '"<<curr<<"'" << endl;
        if(atcount >= 2){
            printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",curr.c_str(),len + 1,name); 
            return 0;
        }
        if(curr == name){
            printf("Successful @yyy loves %s attempt",curr.c_str());
            return 0;
        }
        if(count == 1){
            if(curr == "") continue;
            printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",curr.c_str(),len + 1,name); 
            return 0;
        }else{
            if(curr == ""){
                len = 1;
                curr = at;
            }else if(at == curr){
                len += 1;
                continue;
            }else{
                printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",curr.c_str(),len + 1,name); 
                return 0;
            }
        }
        index += 1;
    }while(strlen(buff) != 0);
    printf("Unsuccessful @yyy loves %s attempt\n%d\nGood Queue Shape",curr.c_str(),len); 
	return 0;
}

```


---

## 作者：クリオネ (赞：2)

跟前面所有的题解不同，我为了练快读用了
```cpp
getchar()
```
然后就~~涨了很多姿势~~ RE+WA了很多遍
#### 想看题解的请直奔代码OwO

### 姿势1：devc++的字符判断跟洛谷的评测不一定一样，洛谷IDE的字符判断同上！
AC这道题之后可以去看看我的提交记录，一路修RE修到洛谷IDE都能跑过去但评测过不了的程度**qwq**，然后我就学到了以下其它姿势：

### 姿势2：char型变量不能存储EOF~~（至少在洛谷评测下是这样的）~~。

我们知道EOF的值是-1，而我百度之后发现char型变量是不能赋值-1的。那么我们要怎么做呢？
```cpp
int x;
x=getchar();
```
不错,这样读入的字符在处理和给字符串赋值的时候和普通的char读入没有任何区别，而且不会被EOF卡。我认为这个在各种比赛是非常可能用到的。顺带一提，在devc++和洛谷IDE中char赋值-1为TLE，而洛谷评测中为RE。

### 姿势3：换行符有两种
我们在平时编程的时候，一般判断换行符为'\n'（或者直接不用判断，比如题解一票的getline），然而实际上换行符有两种：

ASCII=10 ,即我们平常用的'\n'，在ASCII的解释中它是“换行键”
 
ASCII=13 ,它是“回车键”；

我并不知道这个ASCII=13的键有什么鬼用，我只知道我第二个点无数次的**WA：read (ASCII 13)，expected  **(←这里是一个空格)。原因在于第二个点的名字读入紧接着就是换行符，由于我只判断 x!='\n' 所以反复去世了

另外在洛谷的IDE与评测中，使用getchar()会将两个换行符都读入，因此最后判断的行数需要除以2

~~摸了摸了，心态崩了~~

------------
上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool zt,same;
int lc=1,anl,nl,atcnt;
int x;
char name[1010],atname[1010],name2[1010];
int main()
{
    x=getchar();
    while (x!='@')
        x=getchar();
    for (register int i=1;i<=10;i++)
        x=getchar();
    x=getchar();
    while (x!=' '&&x!=10&&x!=13)
    {
        atname[anl++]=x;
        x=getchar();
    }
    while (x!=13&&x!=10)
        x=getchar();
    while (1)
    {
        if (x==13||x==10)
        {
            lc++;
            zt=0;
            nl=0;
            memset(name,0,sizeof(name));
            memset(name2,0,sizeof(name2));
            x=getchar();
            continue;
        }
        if (x==-1)
        {
            printf("Unsuccessful @yyy loves %s attempt\n%d\nGood Queue Shape",atname,lc/2-1); //猜猜这里为什么是-1？ 
            return 0;
        }	
        for (int i=1;i<=9;i++)
            x=getchar();
        x=getchar();
        while (x!=' ')
        {
            name[nl++]=x;
            x=getchar();
        }
        if (nl==anl)
        {
            same=1;
            for (int i=0;i<anl;i++)
            {
                if (name[i]!=atname[i])
                {
                    same=0;
                    break;
                }
            }
            if (same==1)
            {
                printf("Successful @yyy loves %s attempt",atname);
                return 0;
            }
        }
        same=0;
        nl=0;
        while (x!=13&&x!=10)
        {
            x=getchar();
            if (x=='@')
            {
                zt=1;
                for (int i=1;i<=10;i++)
                    x=getchar();
                x=getchar();
                while (x!=' '&&x!=13&&x!=10)
                {
                    name2[nl++]=x;
                    x=getchar();
                }		
                if (nl==anl)
                {
                    same=1;
                    for (int i=0;i<nl;i++)
                    {
                        if (name2[i]!=atname[i])
                        {
                            same=0;
                            break;
                        }
                    }
                }
                if (same==0)
                {
                    {
                        printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",atname,lc/2+1,name);//在第n行的时候，lc值为2n-1  
                        return 0;
                    }
                }
                break;
            }
        }
        while (x!=13&&x!=10)
        {
            x=getchar();
            if (x=='@')
            {
                printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",atname,lc/2+1,name);
                return 0;
            }
        }
        if (zt==0)
        {
            printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",atname,lc/2+1,name);
            return 0;
        }
    }  
}
```
**需要注意的是，在devc++上这个程序是绝对不对的，本机运行只需要把所有输出的行数改为 lc 即可**

---

## 作者：青春ing (赞：2)

按题目字面意思模拟即可，小心自己弄出来的坑


[codep]var c,d,e:longint;  //c:队形长度;d:'@'位置;e:b的长度

  
```cpp
    a,b:ansistring;  //a:输入的字符串;b:@的人
begin  
  readln(a);  
  a:=a+' ';  
  c:=2;  
  d:=pos('@',a);  
  b:='yyy loves ';  
  e:=d+11;  
  while a[e]<>' ' do begin  //确定b
    b:=b+a[e];  
    inc(e);  
  end;  
  b:=b+' ';  //便与判断
  e:=length(b);  
  readln(a);  
  while a<>'' do begin  //如果@的人出现就输出
    if copy(a,1,e)=b then begin  
      writeln('Successful @'+b+'attempt');  
      halt;  
    end;  
    d:=pos('@',a);  
    if (copy(a,d+1,e)<>b) and (copy(a,d+1,e)+' '<>b) or (d=0) then begin  //如果 @的不是同一个人 或 没有@人 就输出(特判'@某某某'出现在结尾且无空格的情况)
      writeln('Unsuccessful @'+b+'attempt');  
      writeln(c);  
      writeln(copy(a,1,pos(':',a)-1));  
      halt;  
    end;  
    delete(a,d,1);  //删除'@'
    if pos('@',a)<>0 then begin  //如果还有'@'即@了不止一个人就输出
      writeln('Unsuccessful @'+b+'attempt');  
      writeln(c);  
      writeln(copy(a,1,pos(':',a)-1));  
      halt;  
    end;  
    readln(a);  
    inc(c);  
  end;  
  writeln('Unsuccessful @'+b+'attempt');  //队形未打破但@的人未出现,输出
  writeln(c-1);  
  writeln('Good Queue Shape');  
end. [/codep]
```

---

## 作者：judgejudge (赞：1)

# 注重细节的题
其实这道题就是纯模拟，只是有太多的东西要注意。
：**
大体注意：

1. **名字是个坑**：@不能忘，有可能会重复@，有可能人说的话后会有人名，但没有@。
1. **话是个坑**：话中千奇百怪，可能附带名字。

下面见代码：
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define N 100001//数组开大点，1000绝对爆
using namespace std;
typedef long long ll; 
char s[N];
ll vis[N];//判断是否@人了，且@了几次，几个
unsigned long long ti=0;//不开unsigned 也可以
int main(){
	register int i,j;
	string yyy,loves,name,realname,lastname;
	char fuhao;//存冒号
	bool fh=false;
	//freopen("eggs.in","r",stdin);
	//freopen("eggs.out","w",stdout);//建议：像这种输入量不定的最好用freopen文件输入输出来调试
	while(cin>>yyy){
		if(yyy!="yyy"&&yyy!="@yyy")continue;//冗杂信息直接过滤
		if(yyy=="yyy"&&fh==false){//我们用符号判断这是单纯人名还是要说话了
			cin>>loves;
			if(loves=="loves"){//一定要特判！！不然会有奇怪的名字WA
				cin>>name;
				if(name[name.length()-1]=='.'||name[name.length()-1]=='?')continue;//有可能名字出现在话语中，且作宾语。
				cin>>fuhao;
				if(fuhao==':'){//要说话
					if(vis[ti]!=1&&ti){//如果上一个人没@或@太多，破坏行阵
				    cout<<"Unsuccessful @yyy loves "<<realname<<" attempt"<<endl;
				    cout<<ti<<endl;
				    cout<<"yyy loves "<<lastname<<endl;
				    return 0;
			        }
		            if(name==realname){//轰炸成功
			            cout<<"Successful @yyy loves "<<realname<<" attempt"<<endl;
			            return 0;
		            }    
		        ti++;lastname=name;fh=true;//记录说话了，用lastname将name储存，不然会变成@人的名字
				}
			}
		}
		else if(yyy=="@yyy"){//@人
			fh=false;
			vis[ti]++;//计算@了几个
			cin>>loves>>name;
			if(realname=="")realname=name;//储存第一个@的人
			if(name!=realname){//@错误，破坏行阵
			    cout<<"Unsuccessful @yyy loves "<<realname<<" attempt"<<endl;
			    cout<<ti<<endl;
			    cout<<"yyy loves "<<lastname<<endl;
			    return 0;
			}
		}
	}
	if(vis[ti]==false&&ti){//万一最后一个出错，要在循环外判断
		cout<<"Unsuccessful @yyy loves "<<realname<<" attempt"<<endl;
		cout<<ti<<endl;
		cout<<"yyy loves "<<lastname<<endl;
		return 0;
	}
	cout<<"Unsuccessful @yyy loves "<<realname<<" attempt"<<endl;
	cout<<ti<<endl;
	cout<<"Good Queue Shape"<<endl;//没有破坏队列
	return 0;
}
```


---

## 作者：2011FYCCCTA (赞：0)

# [原题](https://www.luogu.com.cn/problem/P1580)
这题题目我看了 30 分钟才搞懂。

---
### 题目
- 队列被打破的情况

  1. 当前吱声的人艾特的人与第一个人艾特的人不同。
  2. 当前吱声的人艾特了大于 $1$ 个人。

输出格式：第一行输出 `Unsuccessful @第一个人艾特的人
attempt`，第二行输出 `队形被破坏时的行数`，第三行输出 `第一次破坏队形的人的名称`。

- （油）炸成功的情况

  1. 当前吱声的人就是第一个人艾特的人。
  
输出格式：第一行输出 `Successful @第一个人艾特的人 attempt`。

若有以上情况，直接结束程序。

若输入结束尚未出现以上情况，第一行输出 `Unsuccessful @第一个人艾特的人 attempt`，第二行输出 `队形被破坏时的行数`，第三行输出 `Good Queue Shape`。

---
### 分析
我的大致思路如下：
1. 用 `getline` 输入得到每一条消息。
2. 编写一个函数，输入一条消息，返回其中所有出现的名称（用向量存储）。
3. 利用如上函数返回的名称集来判断是否有队列被打破或（油）炸成功的情况。

---
#### 着重看第二部分的函数：
我令返回的向量的第一项为发出消息的人的名称，从第二项开始，都是在消息中艾特的名字。

由于题目保证了每个人的名称都是 `yyy loves ____` 的形式，因此存储名字时只用只用存储如上未知的部分即可。

可以发现，在消息中艾特到的人名前都有一个 `@` 符号（废话）。而 `yyy loves ` 的长度为 $10$，因此当遍历到 `@` 时，需将下标加上 $11$，这样就跳转到了名字的第一个字符，将直到下一个空格前的内容存储下来即是名字。

得到发出此消息的的人的名字也同理，直接从下标为 $10$ 的地方开始遍历，将直到下一个空格前的内容存储下来即可。

代码：
```cpp
vector<string> get_names(string l)
{
	vector<string> names;
	int len = 0 , llen = l.length();
	names.push_back("");
	
	int i = 10;
	while (l[i] != ' ') {names[len] += l[i]; ++i;}
	i += 3;
	while (i < llen)
	{
		while (i < llen && l[i] != '@') i++;
		i += 11; ++len; names.push_back("");
		while (i < llen && l[i] != ' ')
        {
        	//有可能一条消息最后艾特人的，这样会把换行符也算作名字的一部分，因此要特判。
            if (l[i] != '\r') names[len] += l[i];
            ++i;
        }
	}
	//如果下标的范围超限了，程序还会创建一个空字符串存储名字，需要删掉。 
    if (names[names.size() - 1] == "") names.pop_back();
	return names;
}
```
---
#### 第三部分
很简单，只有一点需要说一下：`printf` 中的 `%s`，并不能直接输出一个 `string` 类型的变量，要用 `char*` 类型，即一个数组。

代码：
```cpp
vector<string> n(get_names(m));
//'\0'是char数组默认值，在用printf输出时不会显示 
memset(name , '\0' , sizeof(name)); nlen = 0; string tmp = n[0];
//将名称转换成char数组 
for (int i = 0 ; i < tmp.length() ; i++)
    name[nlen++] = tmp[i];
//如果是第一个人 
if (sum == 1)
{
    //存储ta艾特的人 
    string tmp = n[1];
    for (int i = 0 ; i < tmp.length() ; i++)
        fn[fnlen++] = tmp[i];
}
//不止艾特了一个人 
if (n.size() > 2) {printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s\n" , fn , sum , name); end;}
//第一个人艾特的人吱声了 
else if (n[0] == fn) {printf("Successful @yyy loves %s attempt\n" , fn); end;}
//艾特的人不是第一个人艾特的人 
else if (n[1] != fn) {printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s\n" , fn , sum , name); end;}
//Tips：嫌写那么多return 0;太麻烦，宏定义end就是return 0;
```
---
完整代码：
```cpp
#include <bits/stdc++.h>
#define end return 0
using namespace std;
int sum , fnlen , nlen;
string m;
char fn[1005], name[1005];

vector<string> get_names(string l)
{
	vector<string> names;
	int len = 0 , llen = l.length();
	names.push_back("");
	
	int i = 10;
	while (l[i] != ' ') {names[len] += l[i]; ++i;}
	i += 3;
	while (i < llen)
	{
		while (i < llen && l[i] != '@') i++;
		i += 11; ++len; names.push_back("");
		while (i < llen && l[i] != ' ')
        {
        	//有可能一条消息最后艾特人的，这样会把换行符也算作名字的一部分，因此要特判。
            if (l[i] != '\r') names[len] += l[i];
            ++i;
        }
	}
	//如果下标的范围超限了，程序还会创建一个空字符串存储名字，需要删掉。 
    if (names[names.size() - 1] == "") names.pop_back();
	return names;
}

int main()
{
	while (++sum)
	{
		getline(cin , m);
		//能读到换行，就说明队列一直没被打破 
		if (m == "\r") {printf("Unsuccessful @yyy loves %s attempt\n%d\nGood Queue Shape\n" , fn , sum - 1); end;}

		vector<string> n(get_names(m));
		//'\0'是char数组默认值，在用printf输出时不会显示 
        memset(name , '\0' , sizeof(name)); nlen = 0; string tmp = n[0];
        //将名称转换成char数组 
        for (int i = 0 ; i < tmp.length() ; i++)
            name[nlen++] = tmp[i];
        //如果是第一个人 
		if (sum == 1)
        {
        	//存储ta艾特的人 
            string tmp = n[1];
            for (int i = 0 ; i < tmp.length() ; i++)
                fn[fnlen++] = tmp[i];
        }
        //不止艾特了一个人 
		if (n.size() > 2) {printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s\n" , fn , sum , name); end;}
		//第一个人艾特的人吱声了 
		else if (n[0] == fn) {printf("Successful @yyy loves %s attempt\n" , fn); end;}
		//艾特的人不是第一个人艾特的人 
		else if (n[1] != fn) {printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s\n" , fn , sum , name); end;}
	} 
   	return 0;
}
```
[悲惨的寄录](https://www.luogu.com.cn/record/list?user=923403&pid=P1580&page=1)

---

