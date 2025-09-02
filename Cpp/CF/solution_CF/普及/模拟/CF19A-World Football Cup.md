# World Football Cup

## 题目描述

## 题意
众所周知，2010 年 FIFA 世界杯在南非举行。BFA 决定下一届世界杯将在伯兰德举行。BFA 决定改变世界杯的一些规定：  

- 最后的比赛涉及 $n$ 支球队（$n$ 总是偶数）；
- 前 $\frac{n}{2}$ 队（根据排名）进入淘汰赛阶段。

积分榜是按照以下原则制作的：胜利一个队得 $3$ 分，平分 $1$ 分，失败 $0$ 分。首先，球队按积分顺序排在积分榜上，分数相等比较净胜球，净胜球相等比较进球数。

你被要求写一个程序，通过给定的比赛名单和所有比赛的结果，找到设法进入淘汰赛阶段的球队名单。

## 样例 #1

### 输入

```
4
A
B
C
D
A-B 1:1
A-C 2:2
A-D 1:0
B-C 1:0
B-D 0:3
C-D 0:3
```

### 输出

```
A
D
```

## 样例 #2

### 输入

```
2
a
A
a-A 2:1
```

### 输出

```
a
```

# 题解

## 作者：灵光一闪 (赞：5)

哇，感觉我的最简单了（蜜汁自信

这题就是个很坑的大模拟……

具体看程序，我调了将近1个多小时吧……

直接上代码：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
#include<map>
using namespace std;
struct TEAM{//结构体（我当初还傻乎乎的发帖求助：这是啥，怎么用？？？2333
    string name;
    int pts;
    int jsq;//jing shen qiu
    int jqs;//jing qiu shu
};
TEAM t[233];
map <int,bool> error;
map <string,int> mp;
vector <string> ans;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){//输入
        cin>>t[i].name;
        mp[t[i].name]=i;
    }
    for(int i=0;i<n*(n-1)/2;i++){
        string s1,s2;
        cin>>s1;
        s2=s1.substr(s1.find('-')+1);
        s1=s1.substr(0,s1.find('-'));
//cout<<"#"<<s1<<" "<<s2<<endl;
        int a,b;
        scanf("%d:%d",&a,&b);
        int team1=mp[s1],team2=mp[s2];
        if(a>b){//这个比较简单，可以理解，
            t[team1].pts+=3;
        }
        else if(a<b){
            t[team2].pts+=3;
        }
        else{
            t[team1].pts++;
            t[team2].pts++;
        }
        t[team1].jsq+=(a-b);//这里是可能为负数的qaq
        t[team2].jsq+=(b-a);
        t[team1].jqs+=a;
        t[team2].jqs+=b;
/*
for(int i=0;i<n;i++){
    cout<<"debug{"<<t[i].pts<<" "<<t[i].jsq<<" "<<t[i].jqs<<" "<<t[i].name<<"}"<<endl;
}
*/
    }
    ans.clear();
/*
for(int i=0;i<n;i++){
    cout<<"debug{"<<t[i].pts<<" "<<t[i].jsq<<" "<<t[i].jqs<<" "<<t[i].name<<"}"<<endl;
}
return 0;
*/
    for(int i=0;i<n/2;i++){//这是重点（敲黑板
        int team=200;//先赋值（保证不要爆边界又不能和数据重叠，开200可以的）
        for(int j=0;j<n;j++){
            if(error[j]){
                continue;//这个队伍已经用过了
            }
            if(t[team].pts<t[j].pts){//下面是比较环节，自己理解，灰常简单
                team=j;
                continue;
            }
            else if(t[team].pts>t[j].pts){
                continue;
            }
            else{
                if(t[team].jsq<t[j].jsq){
                    team=j;
                    continue;
                }
                else if(t[team].jsq>t[j].jsq){
                    continue;
                }
                else{
                    if(t[team].jqs<t[j].jqs){
                        team=j;
                        continue;
                    }
                }
            }
        }
        error[team]=true;//防止下次碰到这支队伍
        ans.push_back(t[team].name);//把名字输进去
/*
for(int j=0;j<n;j++){
    if(error[j]){
        cout<<"can't"<<" ";
    }
    else{
        cout<<"can"<<" ";
    }
}
puts("");
*/
    }
    sort(ans.begin(),ans.end());//sort+输出，没毛病
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
/*//曾经卡掉窝的数据（#4改编）
4
t
a
b
e
a-t 37:34
b-t 38:99
b-a 33:84
e-t 79:34
e-a 24:37
e-b 3:6
*/
```

The End.

---

## 作者：1saunoya (赞：4)

>炒鸡$6$批的模拟题。

>注意的是输入

>把握好空格 大小写。

>再根据
~~~
积分榜是按照以下原则制作的：胜利一个队得3分，平分1分，失败0分。
首先，球队按积分顺序排在积分榜上，分数相等比较净胜球，净胜球相等比较进球数。
~~~

 >至于代码 -> [$here$](https://www.cnblogs.com/qf-breeze/p/10700653.html)

---

## 作者：codeLJH114514 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF19A)

# 题目大意

有 $n$ 支球队和 $\frac{(n - 1)n}{2}$ 场比赛，排序规则即得分（赢球加 $3$ 分，平局加 $1$ 分，输球不加不减。）为第一关键字，净胜球为第二关键字，进球数为第三关键字。（注，净胜球为赢球数 $-$ 输球数），前 $\frac{n}{2}$ 的队伍可以进淘汰赛，让你求出可以进淘汰赛的队伍（按球队名的字典序排序）。

# 数据范围

$1 \leqslant n \leqslant 50$, 且 $n$ 为偶数。

$1 \leqslant |name| \leqslant 30$

# 解题思路

我们先建一个球队的类，这样就可以使用 $sort$ 进行快速排序。
```cpp
class Team{
    public:
        int score, win, get; // score为得分，win为净胜球，get为进球数
        string name;
        Team(int s, int w, int g): score(s), win(w), get(g){};
        Team(): score(0), win(0), get(0){};
        bool operator<(const Team& a) const&;
} t[maxn]; // maxn = 64
bool Team::operator<(const Team& a) const& {
// 重载小于号，以分数为第一关键字，净胜球为第二关键字，进球数为第三关键字
    if (score != a.score)
        return score > a.score;
    else if (win != a.win)
        return win > a.win;
    else
        return get > a.get;
}
```

接下来还是大模拟，输入队伍名称，得分，然后统计，这里可以用一个 unordered_map 来建立队伍名和下标的映射关系。

这里的 unordered_map 和 map 是很相似的，区别是 unordered_map 内部不排序，底层是哈希表，还有一个最重要的区别就是：

**unordered_map 时间复杂度期望为 $O(1)$ !**

然后我们就可以求出每一个球队的分数，净胜球和进球数了！

最后，只需要将前 $\frac{n}{2}$ 个团队的名字取出来，再排个序，就可以了！

附 AC 代码:

```cpp
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#define maxn 64
using namespace std;
class Team{
    public:
        int score, win, get; // score为得分，win为净胜球，get为进球数
        string name;
        Team(int s, int w, int g): score(s), win(w), get(g){};
        Team(): score(0), win(0), get(0){};
        bool operator<(const Team& a) const&;
} t[maxn];
int n;
unordered_map<string, int> teams;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i].name;
    for (int i = 1; i <= n; i++)    
        teams[t[i].name] = i;
    int m = n * (n - 1) / 2;
    for (int i = 1; i <= m; i++) {
        int in1, in2;
        string name1, name2;
        string s;
        char ch;
        cin >> s >> in1 >> ch >> in2;// 直接使用 cin 读入
        name1 = s.substr(0, s.find('-')); // 在s中的子串即为name1, name2.
        name2 = s.substr(s.find('-') + 1);
        if (in1 == in2) {
            t[teams[name1]].score += 1;
            t[teams[name2]].score += 1;
        } else if (in1 < in2)
            t[teams[name2]].score += 3;
        else
            t[teams[name1]].score += 3;
        t[teams[name1]].win += in1 - in2;
        t[teams[name2]].win += in2 - in1;
        t[teams[name1]].get += in1;
        t[teams[name2]].get += in2;
    }
    sort(t + 1, t + n + 1);
    vector<string> v;
    for (int i = 1; i <= n / 2; i++)
        v.push_back(t[i].name); // 取出前 n/2 个球队的名字
    sort(v.begin(), v.end()); // sort对string默认就是字典序排序
    for (auto i : v)
        cout << i << "\n";
    return 0;
}
bool Team::operator<(const Team& a) const& {
// 重载小于号，以分数为第一关键字，净胜球为第二关键字，进球数为第三关键字
    if (score != a.score)
        return score > a.score;
    else if (win != a.win)
        return win > a.win;
    else
        return get > a.get;
}
```

无注释版代码

```cpp
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#define maxn 64
using namespace std;
class Team{
    public:
        int score, win, get;
        string name;
        Team(int s, int w, int g): score(s), win(w), get(g){};
        Team(): score(0), win(0), get(0){};
        bool operator<(const Team& a) const&;
} t[maxn];
int n;
unordered_map<string, int> teams;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i].name;
    for (int i = 1; i <= n; i++)    
        teams[t[i].name] = i;
    int m = n * (n - 1) / 2;
    for (int i = 1; i <= m; i++) {
        int in1, in2;
        string name1, name2;
        string s;
        char ch;
        cin >> s >> in1 >> ch >> in2;
        name1 = s.substr(0, s.find('-'));
        name2 = s.substr(s.find('-') + 1);
        if (in1 == in2) {
            t[teams[name1]].score += 1;
            t[teams[name2]].score += 1;
        } else if (in1 < in2)
            t[teams[name2]].score += 3;
        else
            t[teams[name1]].score += 3;
        t[teams[name1]].win += in1 - in2;
        t[teams[name2]].win += in2 - in1;
        t[teams[name1]].get += in1;
        t[teams[name2]].get += in2;
    }
    sort(t + 1, t + n + 1);
    vector<string> v;
    for (int i = 1; i <= n / 2; i++)
        v.push_back(t[i].name);
    sort(v.begin(), v.end());
    for (auto i : v)
        cout << i << "\n";
    return 0;
}
bool Team::operator<(const Team& a) const& {
    if (score != a.score)
        return score > a.score;
    else if (win != a.win)
        return win > a.win;
    else
        return get > a.get;
}
```

---

## 作者：Ousmane_Dembele (赞：2)

从没见过如此厚颜无耻之题……

看一下数据，n<=50，也就是可以4层暴力，基本上就是不卡常，让你直接模拟。

作为一个蒟蒻，我只会瞎暴力，开始做法是把比分一个一个输进去，往死里判断，但是发现太累了。

于是想到一个做法：一个字符一个字符输进去，判断已经输到了哪里
```
        while(1){
            scanf("%c",&nlong);
            if(nlong=='-')break;
            else if((nlong>='a'&&nlong<='z')||(nlong>='A'&&nlong<='Z')){nameone+=nlong;sum++;}
        }
        tmp=sum;//tmp记录的是第一队字符数
        sum++;//sum是两队加起来字符数+1
        
        while(1){
            scanf("%c",&nlong);
            if(nlong==' ')break;
            else{nametwo+=nlong;sum++;}
        }
        while(1){
            scanf("%c",&nlong);
            if(nlong==':')break;
            else numone=numone*10+nlong-'0';
        }
```
输完后，开始判断，不像那些dalao一样用map，用最暴力的方法判断，字符数相等在挨个判断（就像简陋版的hash）
```
        cin>>numtwo;
        int one,two;
        for(int i=1;i<=n;i++)
          if(wxy[i].q==tmp)
          if(check(i)){one=i;break;}
        for(int i=1;i<=n;i++)
          if(wxy[i].q+tmp+1==sum)
          if(checktwo(i)){two=i;break;}//one记录的是第一队的编号
```
得到编号后，就简单了，暴力加减
```
        wxy[one].goal+=numone;//纯模拟
        wxy[two].goal+=numtwo;
        wxy[one].moregoal+=numone-numtwo;
        wxy[two].moregoal+=numtwo-numone;
        if(numone>numtwo)
            wxy[one].score+=3;
        else if(numtwo>numone)
            wxy[two].score+=3;
        else{
            wxy[one].score++;
            wxy[two].score++;
        }
```
接下来排序，我排两次序一次确定前一半一次把前一半二次排序
```
bool cmpfirst(node a,node b){
    if(a.score>b.score)return 1;
    if(a.score<b.score)return 0;
    if(a.moregoal>b.moregoal)return 1;
    if(a.moregoal<b.moregoal)return 0;
    if(a.goal>b.goal)return 1;
    return 0;
}
bool cmplast(node a,node b){
    return a.name<b.name;
}
sort(wxy+1,wxy+n+1,cmpfirst);
sort(wxy+1,wxy+n/2+1,cmplast);
```
接下来输出。
这题真是坑，我一开始忘了char遇到空格就停炸了5分钟后来把纯模拟那段一个>打成<再后来画蛇添足把不用添加特判的地方提案了一个
```
if(glong>='1'&&glong<='9')//应该>='0'
```
总之，卡了一个下午

上程序，不写注释了，前面解释的够清楚了
```
#include<bits/stdc++.h>
using namespace std;
int n,numone,numtwo,sum,tmp;
char nlong;
string nameone,nametwo;
struct node{
    string name;
    int goal,moregoal,score;
    int q;
}wxy[100];
bool check(int t){//t是一开始我写的垃圾程序的一部分
    for(int i=0;i<tmp;i++)
      if(wxy[t].name[i]!=nameone[i])return false;
    return true;
}
bool checktwo(int t){
    for(int i=tmp+1;i<sum;i++)
        if(wxy[t].name[i-tmp-1]!=nametwo[i-tmp-1])return false;
    return true;
}
// int t(){
//         int i=wxy[nameone].namelong+wxy[nametwo].namelong+3;
//         while(read[i]>='0'&&read[i]<='9'){
//             numone=numone*10+read[i];
//             i++;
//         }
//         i++;
//         while(read[i]>='0'&&read[i]<='9'){
//             numtwo=numtwo*10+read[i];
//             i++;
//         }
// }
bool cmpfirst(node a,node b){
    if(a.score>b.score)return 1;
    if(a.score<b.score)return 0;
    if(a.moregoal>b.moregoal)return 1;
    if(a.moregoal<b.moregoal)return 0;
    if(a.goal>b.goal)return 1;
    return 0;
}
bool cmplast(node a,node b){
    return a.name<b.name;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>wxy[i].name;
        wxy[i].q=wxy[i].name.size();
    }
    for(int j=1;j<=n*(n-1)/2;j++){
        sum=0;tmp=0;
        nameone="",nametwo="";
        numone=numtwo=0;
        while(1){
            scanf("%c",&nlong);
            if(nlong=='-')break;
            else if((nlong>='a'&&nlong<='z')||(nlong>='A'&&nlong<='Z')){nameone+=nlong;sum++;}
        }
        tmp=sum;
        sum++;
        
        while(1){
            scanf("%c",&nlong);
            if(nlong==' ')break;
            else{nametwo+=nlong;sum++;}
        }
        while(1){
            scanf("%c",&nlong);
            if(nlong==':')break;
            else numone=numone*10+nlong-'0';
        }
        cin>>numtwo;
        int one,two;
        for(int i=1;i<=n;i++)
          if(wxy[i].q==tmp)
          if(check(i)){one=i;break;}
        for(int i=1;i<=n;i++)
          if(wxy[i].q+tmp+1==sum)
          if(checktwo(i)){two=i;break;}
        wxy[one].goal+=numone;
        wxy[two].goal+=numtwo;
        wxy[one].moregoal+=numone-numtwo;
        wxy[two].moregoal+=numtwo-numone;
        if(numone>numtwo)
            wxy[one].score+=3;
        else if(numtwo>numone)
            wxy[two].score+=3;
        else{
            wxy[one].score++;
            wxy[two].score++;
        }
    }
    sort(wxy+1,wxy+n+1,cmpfirst);
    sort(wxy+1,wxy+n/2+1,cmplast);
    for(int i=1;i<=n/2;i++)
      cout<<wxy[i].name<<endl;
    return 0;
}
```

---

## 作者：Adam_Ng (赞：2)

这道题~~真麻烦~~我的思路是用c++STL的map做

就除了题目有点复杂输入有点~~恶心~~之外还是蛮简单的

代码
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,num1,num2;
string nm[51];//存名字
char c;
map<string,int> point,win,ball;//总分map，净胜球map，总进球map
string a,name1,name2;
struct Struct{
    string name;//球队名称
    int point,win,ball;//point总分，win净胜球,ball总进球
}Sort[51];
bool cmp(Struct a,Struct b)
{
    if(a.point==b.point)//如果分数相等
    {
        if(a.win==b.win)//如果净胜球相等
        return a.ball>b.ball;//返回总进球数
        else
        return a.win>b.win;//返回净胜球
    }
    else
    return a.point>b.point;//返回分数
}
bool cmp2(Struct a,Struct b)
{

    return a.name<b.name;//按字典序排序
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;//读入球队名称
        nm[i]=a;//表示第i个球队的名称是a
          ball[a]=0;//总进球数map初始化
        point[a]=0;//总分数map初始化
        win[a]=0;//净胜球map初始化
    }
    for(int i=1;i<=n*(n-1)/2;i++)
    {   name1="";name2="";num1=0;num2=0;//name1，name2，num1，num2初始化
        while(1)//name1输入
        {
            scanf("%c",&c);
            if(c=='-')break;//如果输入'-'就退出
            else
            if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))name1+=c;//判断读入是否是字母，因为之前会读入回车。
        }
        while(1)//name2输入
        {
            scanf("%c",&c);
            if(c==' ')break;//如果输入空格就退出
            else
            name2+=c;//现在不用判断了因为之前没有回车。
        }
        while(1)//num1输入
        {
            scanf("%c",&c);
            if(c==':')break;//如果输入':'就退出
            else
            num1*=10,num1+=c-'0';//末位加数
        }
        cin>>num2;//直接输入num2
        if(num1>num2)point[name1]+=3;
        if(num1==num2)point[name1]++,point[name2]++;
        if(num1<num2)point[name2]+=3;
        //判断输赢累加分数
        win[name1]+=num1-num2;win[name2]+=num2-num1;//加净胜球
        ball[name1]+=num1;ball[name2]+=num2;//加总进球

    }
    for(int i=1;i<=n;i++)//将名称，得分，净胜球和总进球放入结构体进行排序
    {
    //利用存好的名字逐个放进结构体
        Sort[i].name=nm[i];//名称
        Sort[i].point=point[nm[i]];//总分             
        Sort[i].win=win[nm[i]];//净胜球
        Sort[i].ball=ball[nm[i]];//总进球
    }
    sort(Sort+1,Sort+n+1,cmp);//排出前n/2个进入淘汰赛的名单
    sort(Sort+1,Sort+n/2+1,cmp2);//将前n/2个球队按字典序排序
    for(int i=1;i<=n/2;i++)
    {
        cout<<Sort[i].name<<endl;
    }//输出
}
```
前面交了若干次没AC一直没发现错误，是因为~~题目太复杂有些事项没看见（看见了也顾不过来）~~我是个蒟蒻人森经验不够丰富吧~

---

## 作者：PC_DOS (赞：1)

一道模拟题，难度不大但是还是要认真来，三个注意点:

1. STL的map很好用，但是很遗憾的是map是不能直接排序的。为了解决这个问题使用一个vector记录每支球队的名字和得分，用一个map记录这支球队在vector中的位置。

2. 净胜球可以是负数，差点被这个坑...~~(原谅我不怎么看足球)~~

3. 输出出线队伍的名字要按照字典序输出。

然后就开始模拟了:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <sstream>
#include <set>
#include <queue>
#include <stack>
#include <cctype>
#include <map>
using namespace std; //头文件和命名空间，有一些没用上的就不删掉了
struct TeamData{
	string sName; //队名
	long long iScore = 0; //积分
	long long iNetGoal = 0; //净胜球
	long long iGoal=0; //进球数
}; //定义一个存放各支球队信息的结构体
bool cmp(TeamData tdTeam1, TeamData tdTeam2){ //降序排名使用的比较函数
	if (tdTeam1.iScore != tdTeam2.iScore) //先比积分
		return tdTeam1.iScore > tdTeam2.iScore;
	else if (tdTeam1.iNetGoal != tdTeam2.iNetGoal) //再比净胜球
		return tdTeam1.iNetGoal > tdTeam2.iNetGoal;
	else //最后比总进球
		return tdTeam1.iGoal > tdTeam2.iGoal;
}
void ParseMatch(string sMatch, string &sTeam1, string &sTeam2){ //用来处理输入比赛数据时产生的形如"T1-T2"的字符串的函数，将T1和T2分别赋给sTeam1和sTeam2，注意sTeam1和sTeam2要定义为引用
	long long i;
	sTeam1 = "";
	sTeam2 = ""; //注意一定要先清空它们
	for (i = 0; i <= sMatch.length() - 1; ++i){
		if (sMatch[i] != '-')
			sTeam1 += sMatch[i];
		else
			break;
	}
	for (i = i + 1; i <= sMatch.length() - 1; ++i){
		sTeam2 += sMatch[i];
	}
	return;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	map<string, int> mapTeamMapping; //记录一支球队在arrTeams中的索引
	vector<TeamData> arrTeams; //存放各支球队的资料
	vector<string> arrOut; //存放出线球队的名字
	int nTeams, nMatches, i, iScore1, iScore2,iPos1,iPos2; //nTeams-球队总数，nMatches-比赛总数，i-循环计数器，iScore1、iScore2-一场比赛的比分，iPos1、iPos2-存放两支比赛球队在arrTeams中的索引
	string sMatch,sTeam1, sTeam2; //sMatch-一场比赛的双方，sTeam1、sTeam2-一场比赛两支参与球队的名字
	char chrTmp; //输入比分时读取掉":"
	TeamData tdTeam; //暂存输入的球队的资料
	cin >> nTeams; //输入球队数
	nMatches = nTeams*(nTeams - 1) / 2; //计算比赛数
	for (i = 1; i <= nTeams; ++i){ //读入球队
		cin >> tdTeam.sName;
		mapTeamMapping[tdTeam.sName] = i - 1; //记录球队在arrTeams的索引，注意要减去1
		arrTeams.push_back(tdTeam); //保存记录
	}
	for (i = 1; i <= nMatches; ++i){ //输入比赛数据
		cin >> sMatch >> iScore1>> chrTmp >> iScore2; //读入比赛双方以及比分
		ParseMatch(sMatch, sTeam1, sTeam2); //解析两支球队的名字
		iPos1 = mapTeamMapping[sTeam1];
		iPos2 = mapTeamMapping[sTeam2]; //读取两支球队在arrTeams的索引
		if (iScore1 > iScore2){ //第一队胜出
			arrTeams[iPos1].iScore += 3;
			arrTeams[iPos1].iNetGoal += iScore1 - iScore2;
			arrTeams[iPos1].iGoal += iScore1;
			arrTeams[iPos2].iScore += 0;
			arrTeams[iPos2].iNetGoal += iScore2 - iScore1;
			arrTeams[iPos2].iGoal += iScore2; //依照要求处理
		}
		else if (iScore1 < iScore2){ //第二队胜出
			arrTeams[iPos1].iScore += 0;
			arrTeams[iPos1].iNetGoal += iScore1 - iScore2;
			arrTeams[iPos1].iGoal += iScore1;
			arrTeams[iPos2].iScore += 3;
			arrTeams[iPos2].iNetGoal += iScore2 - iScore1;
			arrTeams[iPos2].iGoal += iScore2; //依照要求处理
		}
		else{ //平局
			arrTeams[iPos1].iScore += 1;
			arrTeams[iPos1].iNetGoal += 0;
			arrTeams[iPos1].iGoal += iScore1;
			arrTeams[iPos2].iScore += 1;
			arrTeams[iPos2].iNetGoal += 0;
			arrTeams[iPos2].iGoal += iScore2; //依照要求处理
		}
	}
	sort(arrTeams.begin(), arrTeams.end(), cmp); //对所有球队排名
	for (i = 0; i <= nTeams / 2-1; ++i){ //读取出线球队
		arrOut.push_back(arrTeams[i].sName); //将其名字存入arrOut中
	}
	sort(arrOut.begin(), arrOut.end()); //将arrOut按照字典序排序
	for (i = 0; i <= nTeams / 2 - 1; ++i){ //输出出线球队
		cout << arrOut[i] << endl;
	}
	return 0; //结束
}
```

---

## 作者：晨·曦 (赞：0)

### -分析

不难看出，这道题就是模拟，所以用**结构体**来存每只队伍的各项信息：球队名称、分数、净胜球、总进球，最后用 $sort$ 按照题目要求排序一下即可（先比较总得分，分数相等比较净胜球，净胜球相等比较进球数），$\because$ 要字典序排序，$\therefore$ 再用一个数组存前 $n/2$ 个队伍，最后再按照字典序排序一遍。

**坑点**：
- 净胜球：进球数减失球数，**可以为负数**。（不知道的我就被卡了好久）

### -代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	string name; // 球队名称
	int f; // 总得分
	int js; //净胜球
	int jq; //总进球个数
}a[10010];
string ans[120]; 
bool cmp(node x,node y) { 
//比较总得分，分数相等比较净胜球，净胜球相等比较进球数
	if(x.f==y.f) {
		if(x.js==y.js) return x.jq>y.jq;
		else return x.js>y.js;
	}
	else return x.f>y.f;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].name;
	for(int i=1;i<=n*(n-1)/2;i++) {
		string s,x,y;
		cin>>s;
     	//截取球队名称
		int j=s.find('-'),xj,yj;
		x=s.substr(0,j);
		y=s.substr(j+1,s.size()-1);
		int xx,yy;
		scanf("%d:%d",&xx,&yy); // 这样输入可以过滤掉 “:”
		for(j=1;j<=n;j++) { //查找球队编号
			if(a[j].name==x) {
				xj=j;
				break;
			}
		}
		for(j=1;j<=n;j++) {
			if(a[j].name==y) {
				yj=j;
				break;
			}
		}
        // 分别给两个队伍加上得分、净胜球和总进球
		if(xx>yy) a[xj].f+=3;
		else if(xx<yy) a[yj].f+=3;
		else {
			a[xj].f++;
			a[yj].f++;
		}
		a[xj].js+=(xx-yy);
		a[yj].js+=(yy-xx);
		a[xj].jq+=xx;
		a[yj].jq+=yy;
	}
	sort(a+1,a+1+n,cmp);
    //把前n/2只球队存到ans数组里再排序一遍
	for(int i=1;i<=n/2;i++) ans[i]=a[i].name;
	sort(ans+1,ans+1+n/2);
    //输出前n/2个队伍
	for(int i=1;i<=n/2;i++) cout<<ans[i]<<"\n";
	return 0;
} 
```


---

## 作者：_HiKou_ (赞：0)

[原题传送~](https://www.luogu.com.cn/problem/CF19A)

大模拟。

思路：

1. 用三个 map 数组分别存分数，净胜球，进球数。（注意了，净胜球可以是负数，不知道可以自行 BDFS）
2. 输入数量，名字。
3. 输入比赛情况。分别把名字和分数提取出来。
4. 根据题意加上分数，净胜球和进球数。
5. 写一个排序的 cmp，依照优先顺序排序即可。
6. （看到有大佬说要字典序所以再把排序好的前半个序列按字典序排好）
114514. 输出。

码了大概 15 min。码量适中，可用于大模拟练手（


CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
map <string,int> sco,wi,in;
string name[114];//别看了，臭死了
bool cmp(string a,string b){//这里是排序条件函数
	if(sco[a]!=sco[b])return sco[a]>sco[b];//返回分数较高的
	else if(wi[a]!=wi[b])return wi[a]>wi[b];//分数相同返回净胜球多的
	else return in[a]>in[b];//净胜球相同返回进球数多的
}
int main(){
	int n,i,j;
	cin>>n;
	for(i=1;i<=n;i++)cin>>name[i];
	for(i=1;i<=n*(n-1)/2;i++)//题目有提到是这么多比赛，要注意
	{
		string s;
		cin>>s;//注意中间有空格，这里先提取名字
		string name1,name2;
		int h=0,k=0;
		for(j=0;j<s.length();j++)
		{
			if(s[j]=='-')
			{
				h=1;
				continue;
			}
			if(h==0)name1+=s[j];
			else name2+=s[j];
		}
		cin>>s;//然后提取数字
		
		int s1=0,s2=0,m=0;
		for(j=0;j<s.length();j++)
		{
			if(s[j]==':')
			{
				m=1;
				continue;
			}
			if(m==0)s1=s1*10+(s[j]-'0');
			else s2=s2*10+(s[j]-'0');
		}
		
		
		if(s1>s2)sco[name1]+=3;
		if(s1==s2)
		{
			sco[name1]++;
			sco[name2]++;
		}
		if(s1<s2)sco[name2]+=3;
        
        //依照题意加上分数
		wi[name1]+=(s1-s2);
		wi[name2]+=(s2-s1);
		in[name1]+=s1;
		in[name2]+=s2;
        //以及净胜球和进球数
	}
	
	sort(name+1,name+1+n,cmp);//按照条件排序
	sort(name+1,name+1+n/2);//按照字典序再排一次序
	
	for(i=1;i<=n/2;i++)cout<<name[i]<<endl;
	
	
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个球队参加一场足球比赛，比赛排名前 $\dfrac{n}{2}$ 的队伍将会进入下一轮的淘汰赛。比赛将会打 $\dfrac{n(n-1)}{2}$ 场，胜者得 $3$ 分，负者得 $0$ 分，平局双方各得 $1$ 分。排行榜上首先会按球队的积分从大到小排序，如果积分相同将会比较净胜球数（胜场比另一方领先的球数的总和减去负场比另一方落后的球数的总和的值），如果净胜球数相同会比较进球数，如果进球数还相同则会比较字典序。试求出能够晋级淘汰赛的 $\dfrac{n}{2}$ 个队伍。

**数据范围：$1\leqslant n\leqslant 50$，球队名不超过 $30$ 个字符，单场双方的进球数都不会超过 $100$。另根据 CF 官网给出的数据可得，$n$ 保证是偶数。**
## Solution
看啥做啥的模拟题。

我们可以通过 $\texttt{map}$ 直接映射得到球队名所属的球队的积分、胜场比另一方领先的球数的总和、负场比另一方落后的球数的总和、进球数。然后按照如上的关键字次序排序，便可以得到前 $\dfrac{n}{2}$ 名的球队。
## Code
```cpp
int n;
string s[57], win[57];
map<string, int> q, goal, wingoal, losegoal;
struct team {
	string name;
	int score, wingoals, goals;
	bool operator < (const team& dxy) const {
		if(score != dxy.score)	return score > dxy.score;
		else if(wingoals != dxy.wingoals)	return wingoals > dxy.wingoals;
		else if(goals != dxy.goals)	return goals > dxy.goals;
		return name < dxy.name;
	}
}teams[57];

int main() {
	getint(n);
	_for(i, 1, n)	cin >> s[i];
	_for(i, 1, n * (n - 1) / 2) {
		string a, team1 = "", team2 = ""; int x, y;
		cin >> a; scanf("%d:%d", &x, &y);
		int len = a.size(), flag = 1;
		_for(j, 0, len - 1) {
			if(a[j] == '-')	flag++;
			else if(flag == 1)	team1 += a[j];
			else if(flag == 2)	team2 += a[j];
		}
		goal[team1] += x, goal[team2] += y;
		if(x > y)	q[team1] += 3, wingoal[team1] += (x - y), losegoal[team2] += (x - y);
		else if(x == y)	q[team1] += 1, q[team2] += 1;
		else	q[team2] += 3, wingoal[team2] += (y - x), losegoal[team1] += (y - x);
	}
	_for(i, 1, n)
		teams[i] = (team){s[i], q[s[i]], wingoal[s[i]] - losegoal[s[i]], goal[s[i]]};
	sort(teams + 1, teams + n + 1);
	_for(i, 1, n / 2)	win[i] = teams[i].name;
	sort(win + 1, win + n / 2 + 1);
	_for(i, 1, n / 2)	cout << win[i] << endl;
	return 0;
}
```

---

