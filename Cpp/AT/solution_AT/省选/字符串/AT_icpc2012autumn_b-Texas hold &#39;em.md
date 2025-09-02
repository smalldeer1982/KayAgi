# Texas hold &#39;em

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2012autumn/tasks/icpc2012autumn_b



## 样例 #1

### 输入

```
SA SK
DA CA
SQ SJ ST
SA HA
D2 C3
H4 S5 DA
HA D9
H6 C9
H3 H4 H5
#```

### 输出

```
1.00000000000000000000
0.34444444444444444198
0.63030303030303025391```

# 题解

## 作者：mlvx (赞：4)

好玩的大模拟题。

### 题意

你和对手分别有两张手牌，桌面上有三张已知公共牌，两张未知公共牌。

每个人可以从自己的两张手牌和五张公共牌中选出五张，当你和对手都取最优牌，问你的胜率是多少？

### 分析

总共有十种牌型，牌型有大小区别。

同种牌型按如下方式比较。

- 皇家同花顺都是平局。

- 同花顺和顺子都是比较最大牌。

- 四条先比较四张相同牌，再比较另外一张牌。

- 满堂红和三条先比较三张相同牌，再比较另外的牌。

- 同花和高排直接依次比较每张牌。

- 两对先比较较大对，然后比较较小对，最后比较单牌。

- 一对先比较对子，然后依次比较单排。

想一想，这种比较方法像我们平时的什么？

前面的比出来相等，则继续往下比较。

类似我们平时对数字进行比较。

所以我们可以把数字搞成十三进制的，然后从左往右第一位存牌型，往后依次按照上面的比较方式存。

我们只需要枚举每一种牌，然后再枚举自己和对手的选牌方式，对每次使用的方式取最大的权值。

然后记下自己的权值比对手大的组数即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct Card{int hs,ds;}paime[7],paiyou[7],me[5],you[5],a[5];bool operator!=(Card a,Card b){return a.hs!=b.hs||a.ds!=b.ds;}
char c1,c2;
int huase(char c){return c=='S'?0:c=='H'?1:c=='D'?2:3;}
int dianshu(char c){return c>='2'&&c<='9'?c-'0':c=='T'?10:c=='J'?11:c=='Q'?12:c=='K'?13:14;}
ll f(Card*b){
	memcpy(a,b,sizeof a);
	bool tonghua=(a[0].hs==a[1].hs&&a[1].hs==a[2].hs&&a[2].hs==a[3].hs&&a[3].hs==a[4].hs);
	sort(a,a+5,[](Card x,Card y){return x.ds>y.ds;});
	if(tonghua&&a[0].ds==14&&a[1].ds==13&&a[2].ds==12&&a[3].ds==11&&a[4].ds==10)return 100000000000ll;//皇家同花顺
	if(tonghua&&a[0].ds==a[1].ds+1&&a[1].ds==a[2].ds+1&&a[2].ds==a[3].ds+1&&a[3].ds==a[4].ds+1)return 90000000000ll+a[0].ds;//同花顺
	if(tonghua&&a[0].ds==14&&a[1].ds==5&&a[2].ds==4&&a[3].ds==3&&a[4].ds==2)return 90000000005ll;//特判A2345
	if(a[0].ds==a[1].ds&&a[1].ds==a[2].ds&&a[2].ds==a[3].ds)return 80000000000ll+a[0].ds*100+a[4].ds;//四条
	if(a[1].ds==a[2].ds&&a[2].ds==a[3].ds&&a[3].ds==a[4].ds)return 80000000000ll+a[1].ds*100+a[0].ds;//四条
	if(a[0].ds==a[1].ds&&a[1].ds==a[2].ds&&a[3].ds==a[4].ds)return 70000000000ll+a[0].ds*100+a[3].ds;//满堂红
	if(a[2].ds==a[3].ds&&a[3].ds==a[4].ds&&a[0].ds==a[1].ds)return 70000000000ll+a[2].ds*100+a[0].ds;//满堂红
	if(tonghua)return 60000000000ll+a[0].ds*100000000+a[1].ds*1000000+a[2].ds*10000+a[3].ds*100+a[4].ds;//同花
	if(a[0].ds==a[1].ds+1&&a[1].ds==a[2].ds+1&&a[2].ds==a[3].ds+1&&a[3].ds==a[4].ds+1)return 50000000000ll+a[0].ds;//顺子
	if(a[0].ds==14&&a[1].ds==5&&a[2].ds==4&&a[3].ds==3&&a[4].ds==2)return 50000000005ll;//特判A2345
	if(a[0].ds==a[1].ds&&a[1].ds==a[2].ds)return 40000000000ll+a[0].ds*10000+a[3].ds*100+a[4].ds;//三条
	if(a[1].ds==a[2].ds&&a[2].ds==a[3].ds)return 40000000000ll+a[1].ds*10000+a[0].ds*100+a[4].ds;//三条
	if(a[2].ds==a[3].ds&&a[3].ds==a[4].ds)return 40000000000ll+a[2].ds*10000+a[0].ds*100+a[1].ds;//三条
	if(a[0].ds==a[1].ds){
		if(a[2].ds==a[3].ds)return 30000000000ll+a[0].ds*10000+a[2].ds*100+a[4].ds;//两对
		if(a[3].ds==a[4].ds)return 30000000000ll+a[0].ds*10000+a[3].ds*100+a[2].ds;//两对
	}if(a[1].ds==a[2].ds&&a[3].ds==a[4].ds)return 30000000000ll+a[1].ds*10000+a[3].ds*100+a[0].ds;//两对
	if(a[0].ds==a[1].ds)return 20000000000ll+a[0].ds*1000000+a[2].ds*10000+a[3].ds*100+a[4].ds;//一对
	if(a[1].ds==a[2].ds)return 20000000000ll+a[1].ds*1000000+a[0].ds*10000+a[3].ds*100+a[4].ds;//一对
	if(a[2].ds==a[3].ds)return 20000000000ll+a[2].ds*1000000+a[0].ds*10000+a[1].ds*100+a[4].ds;//一对
	if(a[3].ds==a[4].ds)return 20000000000ll+a[3].ds*1000000+a[0].ds*10000+a[1].ds*100+a[2].ds;//一对
	return 10000000000ll+a[0].ds*100000000+a[1].ds*1000000+a[2].ds*10000+a[3].ds*100+a[4].ds;//高牌
}int main(){
	while(1){
		cin>>c1;
		if(c1=='#')break;
		cin>>c2,paime[0]={huase(c1),dianshu(c2)},cin>>c1>>c2,paime[1]={huase(c1),dianshu(c2)};
		cin>>c1>>c2,paiyou[0]={huase(c1),dianshu(c2)},cin>>c1>>c2,paiyou[1]={huase(c1),dianshu(c2)};
		for(int i=2;i<5;i++)cin>>c1>>c2,paime[i]=paiyou[i]={huase(c1),dianshu(c2)};
		int cnt=0;
		for(int i=0;i<4;i++)for(int j=2;j<=14;j++){
			Card x={i,j};
			paime[5]=paiyou[5]=x;
			if(x!=paime[0]&&x!=paime[1]&&x!=paiyou[0]&&x!=paiyou[1]&&x!=paime[2]&&x!=paime[3]&&x!=paime[4])for(int ii=0;ii<4;ii++)for(int jj=2;jj<=14;jj++){
				Card y={ii,jj};
				paime[6]=paiyou[6]=y;
				if(y!=paime[0]&&y!=paime[1]&&y!=paiyou[0]&&y!=paiyou[1]&&y!=paime[2]&&y!=paime[3]&&y!=paime[4]&&x!=y){//枚举未知牌的合法情况
					ll mef=0,youf=0;
					for(int k1=0;k1<7;k1++)for(int k2=k1+1;k2<7;k2++)for(int k3=k2+1;k3<7;k3++)for(int k4=k3+1;k4<7;k4++)for(int k5=k4+1;k5<7;k5++){//7选5
						me[0]=paime[k1],me[1]=paime[k2],me[2]=paime[k3],me[3]=paime[k4],me[4]=paime[k5],mef=max(mef,f(me));//计算每次的权值，取最大值
					}for(int k1=0;k1<7;k1++)for(int k2=k1+1;k2<7;k2++)for(int k3=k2+1;k3<7;k3++)for(int k4=k3+1;k4<7;k4++)for(int k5=k4+1;k5<7;k5++){//7选5
						you[0]=paiyou[k1],you[1]=paiyou[k2],you[2]=paiyou[k3],you[3]=paiyou[k4],you[4]=paiyou[k5],youf=max(youf,f(you));//计算每次的权值，取最大值
					}if(mef>youf)++cnt;
				}
			}
		}printf("%.20lf\n",cnt/1980.);//1980=45*44
	}return 0;
}
```

---

## 作者：Eraine (赞：4)

编号：AT_icpc2012autumn_b

tag：模拟

难度：紫（$\texttt{Clist}$ 数据过于抽象，就不放了）

本篇题解侧重于分析三种写法的优劣。若需要浏览本题其他方面的内容，请移步至其他题解。

说句闲话，这个游戏的拓展版其实在我老家有个通用名字叫做十三水。

正题开始。

如果我们能快速比较两份手牌（五张牌）的输赢关系，那么就可以考虑去枚举每种情况。具体地，我们枚举剩下两张未展示的牌，共计 ${45\choose2}=990$ 种情况。对于剩下两张牌的每种情况，两个人此时都有 $7$ 张牌，而要从中选出 $5$ 张牌共有 ${7\choose 5}=21$ 种情况。我们将两个人的 $21$ 种情况中选出排名最高的牌（即最大的牌）然后进行比较即可判断出输赢。

现在问题在于给定两组五张牌，如何判断它们的大小关系。判断关系有两个维度。牌型与同牌型的每组大小关系。牌型比较可用 $type$ 表示：

$type=1$：皇家同花顺/同花顺（这俩其实没什么区别）。

$type=2$：炸弹（四带一）。

$type=3$：老虎（三带二）。

$type=4$：同花。

$type=5$：顺子。

$type=6$：三条。

$type=7$：两对。

$type=8$：一对。

$type=9$：杂牌。

我们显然发现对于“同花”“顺子”这两个条件是需要被判断两次的，所以我们单独写两个函数判断同花和顺子，顺子多处理一个顺子在 $10$ 种顺子中的排名信息。

接下来将给出三份代码及其分析，分析的重点在于判断。

### predawnrisa's code

[submission](https://atcoder.jp/contests/jag2012autumn/submissions/55231978)

这份其实就是我的代码。极其的史。为什么呢？

我的想法是对于每一种牌型都写出 $\text{check}$ 函数和 $\text{getrank}$ 函数，即对于每种牌类型都求出每种满足条件的一组牌的排名，但是其实这 $9$ 种牌型中很多判断和处理是完全一样的，所以很多是重复的。虽然写出 $9$ 个封装看上去很清晰，但是码量过大极其难调试。

比如：

```cpp
for(int i=0;i<=13;i++){
    buc[i]=0;
}
++buc[id[s1.num]];
++buc[id[s2.num]];
++buc[id[s3.num]];
++buc[id[s4.num]];
++buc[id[s5.num]];
for(int i=1;i<=13;i++){
    buc[i]=buc[i]+buc[i-1];
}
```

上述代码段在我的代码中重复了长达 $13$ 遍之多。

以下结合另外两位大佬的代码分析我的缺陷之处。

### peter50216's code

[submission](https://atcoder.jp/contests/jag2012autumn/submissions/52260)

看上去好很多了是吧，$15\text{k}$ 变成了 $3\text{k}$。

此代码与我的代码最大的差别有两个。一个是把所有 $\text{check}$ 函数压缩成 $1$ 个，即判断一组牌的 $type$ 只需一个函数完成。这其实也很好实现。判断是否同花和顺子，然后开个桶记录即可，或者直接暴力判断 $5$ 张牌的关系也可以。

还有一个是同牌型的排名判断。在我的代码中，我是提前预处理出所有二/三/四/五组的排名，而在他的代码中得到相应的 $type$ 就根据对应的 $type$ 赋给每个大小牌的权重从左到右降序排序，比较的时候直接从左到右比较 $5$ 组数的大小即可。实现较为简单。

### kmjp's code

[submission](https://atcoder.jp/contests/jag2012autumn/submissions/457085)

同样的简短，但是处理不同。

这份代码不需要再特殊判断 $type$ 类型，即不需要 $\text{check}$ 函数。它把 $type$ 和同牌型排名融合成一个值 $Val$，只需要比较 $Val$ 即可。具体地，将 $type$ 乘上很大的权值使得无论同牌型排名多大都影响不了 $type$（因为 $type$ 是第一关键字）。对于同牌型排名，类似 peter50216 的写法将权重大的放前面，将 $5$ 个数转成 $1$ 个十三进制数，将这个十三进制数加上前面的 $type$ 乘上大权值的结果就得到了 $Val$。

收获：对于大模拟题，找到最朴素写法冗余（重复）的部分思考是否可以合并或多重信息合并成一个信息。

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：frankchenfu (赞：4)

### Source

`Atcoder JAG Practice Contest for ACM-ICPC Asia Regional 2012` [B - Texas hold 'em](https://jag2012autumn.contest.atcoder.jp/tasks/icpc2012autumn_b)。

这是一道非常考验细节的题目，代码比较大，一般可以达到$500$行/$20\mbox{KB}$。我是调了两天，差不多一共$10$个小时这样子，最后发现题意理解不清……

## 1. 题意

（网上部分题解表述不严谨，请大家注意）

我们知道德州扑克是有$2$张隐藏手牌、$5$张公共牌，再从$7$张牌中选取$5$张进行押注、比较大小。

这道题首先给定你的$2$张“隐藏手牌“，对手的$2$张"隐藏手牌"，以及$5$张公共牌的其中$3$张。

需要你求出在最后还不知道的$2$张公共牌的所有可能组合中，你获胜的概率$p$。

换言之，假设最后两张一共有$b$种组合，而其中有$a$种是你可以获胜的情况，那么输出$\frac{a}{b}$（误差不超过$10^{-6}$）。

**注意：参与游戏的是标准扑克除去大小王共$52$张牌，并且牌`A`可以作为大于`K`或小于`2`中的一个。**

--------



## 2. 分析

首先我们根据计算可以得出，这道题直接暴力模拟是可以在$1s$之内出解的，因此我们直接采用暴力模拟。具体来讲，分成如下几步：

### 2.1 输入

这道题中给出的输入是由花色+牌面值组成的字符串，因此我们需要把这个字符串转化为我们需要的数字。

**注意：在本题中，我们将花色表示为$1-4$，将牌面值表示为$2-14$，便于后续存储。并且我们将`A`视为$14$**。

设计一个函数将其分类即可。可以像我一样用一个结构体存储，然后设计一个构造函数完成上述功能。

### 2.2 枚举

接下来就是枚举所有可能的剩余公共牌。由于已经明确了有$7$张牌，所以剩下的牌一共有$\frac{(52-7)\times (52-8)}{2}=990$种可能。但是这是**无序**二元组$(a,b)$的情况。在实现代码时，由于不方便判重，因此干脆枚举**有序**二元组$(a,b)$。这样在最终计算时并没有影响（表达式中分子和分母均乘以$2$）。

### 2.3 检查

检查部分是我和其它网上代码最大的不同。首先我们需要依次枚举每一种情况，判断是不是符合条件。

但是这里要注意的是对于每一个情况有$4$种不同结果：

* 己方胜出。

* 对方胜出。

* 平局（双方都满足情况，且牌面相同）。

* 平局（双方均不满足情况）。

对于前$3$种，我们可以直接返回状态（设其分别用`1`、`-1`、`2`表示），对于第四种，我们就需要继续往下判断。

接下来，我们需要看一看每一种情况应该怎么处理。有标注*注意细节*的可能实现较为繁琐，请大家注意。

#### 2.3.1 Royal straight flush（皇家同花顺）

这个比较简单，我们只需要对于每一个花色依次判断$10-14$是否存在即可。

注意：**如果判断某一方拥有了皇家同花顺也不能直接返回**，因为有可能五张牌全部来自公共牌。

#### 2.3.2 straight flush（同花顺）

我们需要把所有牌面为$14$的转换为$1$，且不需要保留$14$的状态。

（一方面是因为有可能是$1-5$的同花顺，因此要转换；另一方面是因为如果是$10-14$的同花顺则在上一层就排除了，因此不用考虑$14$的情况。）

然后对于每一个花色从$5-13$依次枚举即可。

#### 2.3.3 Four of a kind（四张）

枚举每个牌面值判断四个花色是否都存在。

#### 2.3.4 Full house（三带二）

这个较为麻烦。我们首先遍历一遍，找出有$3$张牌的，然后再找有$2$张牌的，最后必须$3$张和$2$张都能找到才算找到，最后比较、返回。**注意细节**。

#### 2.3.5 Flush（同花）

对于每个花色从大到小排序后比较。由于`A`一定当成$14$更优，因此不需考虑$1$的情况。

#### 2.3.6 Straight（顺子）

首先把每个牌面值四种花色的数量加起来，然后判断是否有连续段长度$\ge 5$。

注意，这里既要保留$14$的状态也要加上$1$的状态，但是由于顺子长度只有$5$，因此不用担心产生重复。

#### 2.3.7 Three of a kind（三张）

同`2.3.4`，只是不需要判断$2$张，但是剩下四张要排好序，便于比较（如果前三张是牌面相同的）。**注意细节**。

#### 2.3.8 Two pairs（连对）

类似`2.3.4`查找两次出现次数为$2$的牌，最后将剩下三张排好序便于比较。**注意细节**。

#### 2.3.9 One pair（对子）

同`2.3.8`。

#### 2.3.10 High card（高牌）

直接将七张牌分别排序取最高$5$张排序即可，操作最为简单。

--------



## 3. 代码

[我的代码](https://www.luogu.org/record/show?rid=8732498) 里对于每个判断我都重新记录了`bool`数组，这点可以继续优化……然而足够通过本题。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

bool used[5][20];
struct card{
    int col,num;
    bool operator<(const card &rhs)const{
        return num>rhs.num;
    }
    card(){}
    card(char ch[]){
        switch(ch[0]){
            case 'S':{
                col=1;
                break;
            }
            case 'H':{
                col=2;
                break;
            }
            case 'D':{
                col=3;
                break;
            }
            case 'C':{
                col=4;
                break;
            }
        }
        switch(ch[1]){
            case 'T':{
                num=10;
                break;
            }
            case 'J':{
                num=11;
                break;
            }
            case 'Q':{
                num=12;
                break;
            }
            case 'K':{
                num=13;
                break;
            }
            case 'A':{
                num=14;
                break;
            }
            default:{
                num=ch[1]-'0';
                break;
            }
        }
        used[col][num]=1;
    }
}p1[10],p2[10],com[10];

int ___=0;
class checker{
    private:
        bool a[5][20],b[5][20];
        //Royal straight flush
        int check1(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num]=1;
            a[p1[2].col][p1[2].num]=1;
            b[p2[1].col][p2[1].num]=1;
            b[p2[2].col][p2[2].num]=1;
            a[com[1].col][com[1].num]=1;
            b[com[1].col][com[1].num]=1;
            a[com[2].col][com[2].num]=1;
            b[com[2].col][com[2].num]=1;
            a[com[3].col][com[3].num]=1;
            b[com[3].col][com[3].num]=1;
            a[col1][num1]=1;b[col1][num1]=1;
            a[col2][num2]=1;b[col2][num2]=1;
            bool lans=0,rans=0;
            for(int i=1;i<=4;i++){
                if(a[i][10]&&a[i][11]&&a[i][12]&&a[i][13]&&a[i][14])
                    lans=1;
                if(b[i][10]&&b[i][11]&&b[i][12]&&b[i][13]&&b[i][14])
                    rans=1;
            }
            if(lans&&rans)
            	return 2;
            if(lans&&!rans)
                return 1;
            if(!lans&&rans)
                return -1;
            return 0;
        }
        //straight flush
        int check2(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num==14?1:p1[1].num]=1;
            a[p1[2].col][p1[2].num==14?1:p1[2].num]=1;
            b[p2[1].col][p2[1].num==14?1:p2[1].num]=1;
            b[p2[2].col][p2[2].num==14?1:p2[2].num]=1;
            a[com[1].col][com[1].num==14?1:com[1].num]=1;
            b[com[1].col][com[1].num==14?1:com[1].num]=1;
            a[com[2].col][com[2].num==14?1:com[2].num]=1;
            b[com[2].col][com[2].num==14?1:com[2].num]=1;
            a[com[3].col][com[3].num==14?1:com[3].num]=1;
            b[com[3].col][com[3].num==14?1:com[3].num]=1;
            a[col1][num1==14?1:num1]=1;b[col1][num1==14?1:num1]=1;
            a[col2][num2==14?1:num2]=1;b[col2][num2==14?1:num2]=1;
            int lans=0,rans=0;
            for(int i=1;i<=4;i++){
                for(int j=5;j<=13;j++){
                    if(a[i][j]&&a[i][j-1]&&a[i][j-2]&&a[i][j-3]&&a[i][j-4])
                        lans=std::max(lans,j);
                    if(b[i][j]&&b[i][j-1]&&b[i][j-2]&&b[i][j-3]&&b[i][j-4])
                        rans=std::max(rans,j);
                }
            }
            if(lans&&rans){ 
                if(lans==rans)
                    return 2;
                else
                    return lans>rans?1:-1;
            }
            if(lans&&!rans)
                return 1;
            if(!lans&&rans)
                return -1;
            return 0;
        }
        //Four of a kind
        int check3(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num]=1;
            a[p1[2].col][p1[2].num]=1;
            b[p2[1].col][p2[1].num]=1;
            b[p2[2].col][p2[2].num]=1;
            a[com[1].col][com[1].num]=1;
            b[com[1].col][com[1].num]=1;
            a[com[2].col][com[2].num]=1;
            b[com[2].col][com[2].num]=1;
            a[com[3].col][com[3].num]=1;
            b[com[3].col][com[3].num]=1;
            a[col1][num1]=1;b[col1][num1]=1;
            a[col2][num2]=1;b[col2][num2]=1;
            int lans=0,rans=0;
            int lx[7]={0},rx[7]={0};
            for(int i=2;i<=14;i++){
                if(a[1][i]&&a[2][i]&&a[3][i]&&a[4][i])
                    lans=i;
                if(b[1][i]&&b[2][i]&&b[3][i]&&b[4][i])
                    rans=i;
                if(a[1][i]||a[2][i]||a[3][i]||a[4][i])
                	lx[++lx[0]]=i;
                if(b[1][i]||b[2][i]||b[3][i]||b[4][i])
                	rx[++rx[0]]=i;
            }
            for(int i=1;i<=lx[0];i++)
            	if(lx[i]==lans)
            		lx[i]=0;
            std::sort(lx+1,lx+lx[0]+1);
            for(int i=1;i<=rx[0];i++)
            	if(rx[i]==rans)
            		rx[i]=0;
            std::sort(rx+1,rx+rx[0]+1);
            if(lans&&rans){
            	if(lans!=rans)
                	return lans>rans?1:-1;
                else{
                	if(lx[lx[0]]!=rx[rx[0]])
                		return lx[lx[0]]>rx[rx[0]]?1:-1;
                	return 2;
                }
            }
            if(lans&&!rans)
                return 1;
            if(!lans&&rans)
                return -1;
            return 0;
        }
        //Full house(3+2)
        int check4(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num]=1;
            a[p1[2].col][p1[2].num]=1;
            b[p2[1].col][p2[1].num]=1;
            b[p2[2].col][p2[2].num]=1;
            a[com[1].col][com[1].num]=1;
            b[com[1].col][com[1].num]=1;
            a[com[2].col][com[2].num]=1;
            b[com[2].col][com[2].num]=1;
            a[com[3].col][com[3].num]=1;
            b[com[3].col][com[3].num]=1;
            a[col1][num1]=1;b[col1][num1]=1;
            a[col2][num2]=1;b[col2][num2]=1;
            int lans[2]={0,0},rans[2]={0,0};
            bool ltot=0,rtot=0;
            for(int i=14;i>=2;i--){
            	if(a[1][i]+a[2][i]+a[3][i]+a[4][i]>=3){
            		lans[0]=i;
            		a[1][i]=a[2][i]=a[3][i]=a[4][i]=0;
            		break;
            	}
            }
            for(int i=14;i>=2;i--){
            	if(a[1][i]+a[2][i]+a[3][i]+a[4][i]>=2){
            		lans[1]=i;
            		break;
            	}
            }
            if(lans[0]&&lans[1])
            	ltot=1;
            for(int i=14;i>=2;i--){
            	if(b[1][i]+b[2][i]+b[3][i]+b[4][i]>=3){
            		rans[0]=i;
            		b[1][i]=b[2][i]=b[3][i]=b[4][i]=0;
            		break;
            	}
            }
            for(int i=14;i>=2;i--){
            	if(b[1][i]+b[2][i]+b[3][i]+b[4][i]>=2){
            		rans[1]=i;
            		break;
            	}
            }
            if(rans[0]&&rans[1])
            	rtot=1;
            if(ltot&&rtot){
            	if(lans[0]!=rans[0])
            		return lans[0]>rans[0]?1:-1;
            	else
            		if(lans[1]!=rans[1])
            			return lans[1]>rans[1]?1:-1;
            		else
            			return 2;
            }
            if(ltot&&!rtot)
            	return 1;
            if(!ltot&&rtot)
            	return -1;
            return 0;
        }
        //Flush
        int check5(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num]=1;
            a[p1[2].col][p1[2].num]=1;
            b[p2[1].col][p2[1].num]=1;
            b[p2[2].col][p2[2].num]=1;
            a[com[1].col][com[1].num]=1;
            b[com[1].col][com[1].num]=1;
            a[com[2].col][com[2].num]=1;
            b[com[2].col][com[2].num]=1;
            a[com[3].col][com[3].num]=1;
            b[com[3].col][com[3].num]=1;
            a[col1][num1]=1;b[col1][num1]=1;
            a[col2][num2]=1;b[col2][num2]=1;
            int ltot[5][20],rtot[5][20];
            memset(ltot,0,sizeof(ltot));
            memset(rtot,0,sizeof(rtot));
            for(int i=1;i<=4;i++)
                for(int j=14;j>=2;j--){
                    if(a[i][j])
                        ltot[i][++ltot[i][0]]=j;
                    if(b[i][j])
                        rtot[i][++rtot[i][0]]=j;
                }
            int lans=0,rans=0;
            for(int i=1;i<=4;i++){
                if(ltot[i][0]>=5)
                    lans=i;
                if(rtot[i][0]>=5)
                    rans=i;
            }
            if(lans&&rans){
                for(int i=1;i<=5;i++)
                    if(ltot[lans][i]!=rtot[rans][i])
                        return ltot[lans][i]>rtot[rans][i]?1:-1;
                return 2;
            }
            if(lans&&!rans)
                return 1;
            if(!lans&&rans)
                return -1;
            return 0;
        }
        //Straight
        int check6(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num]=1;
            a[p1[2].col][p1[2].num]=1;
            b[p2[1].col][p2[1].num]=1;
            b[p2[2].col][p2[2].num]=1;
            a[com[1].col][com[1].num]=1;
            b[com[1].col][com[1].num]=1;
            a[com[2].col][com[2].num]=1;
            b[com[2].col][com[2].num]=1;
            a[com[3].col][com[3].num]=1;
            b[com[3].col][com[3].num]=1;
            a[col1][num1]=1;b[col1][num1]=1;
            a[col2][num2]=1;b[col2][num2]=1;
            a[p1[1].col][p1[1].num==14?1:p1[1].num]=1;
            a[p1[2].col][p1[2].num==14?1:p1[2].num]=1;
            b[p2[1].col][p2[1].num==14?1:p2[1].num]=1;
            b[p2[2].col][p2[2].num==14?1:p2[2].num]=1;
            a[com[1].col][com[1].num==14?1:com[1].num]=1;
            b[com[1].col][com[1].num==14?1:com[1].num]=1;
            a[com[2].col][com[2].num==14?1:com[2].num]=1;
            b[com[2].col][com[2].num==14?1:com[2].num]=1;
            a[com[3].col][com[3].num==14?1:com[3].num]=1;
            b[com[3].col][com[3].num==14?1:com[3].num]=1;
            a[col1][num1==14?1:num1]=1;b[col1][num1==14?1:num1]=1;
            a[col2][num2==14?1:num2]=1;b[col2][num2==14?1:num2]=1;
            int ltot[20],rtot[20];
            memset(ltot,0,sizeof(ltot));
            memset(rtot,0,sizeof(rtot));
            for(int i=1;i<=14;i++)
                for(int j=1;j<=4;j++){
                    ltot[i]+=a[j][i];
                    rtot[i]+=b[j][i];
                }
            int lans=0,rans=0;
            for(int i=5;i<=14;i++){
                if(ltot[i]&&ltot[i-1]&&ltot[i-2]&&ltot[i-3]&&ltot[i-4])
                    lans=i;
                if(rtot[i]&&rtot[i-1]&&rtot[i-2]&&rtot[i-3]&&rtot[i-4])
                    rans=i;
            }
            /*
            printf("***********\n");
            printf("%d %d %d %d %d %d %d\n",p1[1].num,p1[2].num,com[1].num,com[2].num,com[3].num,num1,num2);
            printf("%d %d %d %d %d %d %d\n",p2[1].num,p2[2].num,com[1].num,com[2].num,com[3].num,num1,num2);
            for(int i=1;i<=14;i++)
            	printf("%d:l=%d  r=%d\n",i,ltot[i],rtot[i]);
            printf("\n****%d %d****\n",lans,rans);
            printf("***********\n"); 
            */
            if(lans&&rans){
                if(lans!=rans)
                    return lans>rans?1:-1;
                return 2;
            }
            if(lans&&!rans)
                return 1;
            if(!lans&&rans)
                return -1;
            return 0;
        }
        //Three of a kind
        int check7(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num]=1;
            a[p1[2].col][p1[2].num]=1;
            b[p2[1].col][p2[1].num]=1;
            b[p2[2].col][p2[2].num]=1;
            a[com[1].col][com[1].num]=1;
            b[com[1].col][com[1].num]=1;
            a[com[2].col][com[2].num]=1;
            b[com[2].col][com[2].num]=1;
            a[com[3].col][com[3].num]=1;
            b[com[3].col][com[3].num]=1;
            a[col1][num1]=1;b[col1][num1]=1;
            a[col2][num2]=1;b[col2][num2]=1;
            int lans=0,rans=0;
            int lx[8]={0},rx[8]={0};
            for(int i=2;i<=14;i++){
                if(a[1][i]+a[2][i]+a[3][i]+a[4][i]==3)
                    lans=i;
                if(b[1][i]+b[2][i]+b[3][i]+b[4][i]==3)
                    rans=i;
                if(a[1][i]||a[2][i]||a[3][i]||a[4][i])
                	lx[++lx[0]]=i;
                if(b[1][i]||b[2][i]||b[3][i]||b[4][i])
                	rx[++rx[0]]=i;
            }
            for(int i=1;i<=lx[0];i++)
            	if(lx[i]==lans)
            		lx[i]=0;
            std::sort(lx+1,lx+lx[0]+1);
            for(int i=1;i<=rx[0];i++)
            	if(rx[i]==rans)
            		rx[i]=0;
            std::sort(rx+1,rx+rx[0]+1);
            if(lans&&rans){
            	if(lans!=rans)
                	return lans>rans?1:-1;
                else{
                	if(lx[lx[0]]!=rx[rx[0]])
                		return lx[lx[0]]>rx[rx[0]]?1:-1;
                	if(lx[lx[0]-1]!=rx[rx[0]-1])
                		return lx[lx[0]-1]>rx[rx[0]-1]?1:-1;
                	return 2;
                }
            }
            if(lans&&!rans)
                return 1;
            if(!lans&&rans)
                return -1;
            return 0;
        }
        //Two pairs
        int check8(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num]=1;
            a[p1[2].col][p1[2].num]=1;
            b[p2[1].col][p2[1].num]=1;
            b[p2[2].col][p2[2].num]=1;
            a[com[1].col][com[1].num]=1;
            b[com[1].col][com[1].num]=1;
            a[com[2].col][com[2].num]=1;
            b[com[2].col][com[2].num]=1;
            a[com[3].col][com[3].num]=1;
            b[com[3].col][com[3].num]=1;
            a[col1][num1]=1;b[col1][num1]=1;
            a[col2][num2]=1;b[col2][num2]=1;
            int ltot[20],rtot[20];
            memset(ltot,0,sizeof(ltot));
            memset(rtot,0,sizeof(rtot));
            for(int i=2;i<=14;i++)
                for(int j=1;j<=4;j++){
                    ltot[i]+=a[j][i];
                    rtot[i]+=b[j][i];
                }
            int lans[5]={0,0,0,0,0},rans[5]={0,0,0,0,0};
            int lx[5]={0,0,0,0,0},rx[5]={0,0,0,0,0};
            for(int i=14;i>=2;i--)
                if(ltot[i]){
                    if(lans[0]<2&&ltot[i]>=2)
                        lans[++lans[0]]=i;
                    else
                        lx[++lx[0]]=i;
                }
            std::sort(lx+1,lx+lx[0]+1);
            for(int i=14;i>=2;i--)
                if(rtot[i]){
                    if(rans[0]<2&&rtot[i]>=2)
                        rans[++rans[0]]=i;
                    else
                        rx[++rx[0]]=i;
                }
            std::sort(rx+1,rx+rx[0]+1);
            if(lans[0]==2&&rans[0]==2){
                if(lans[1]!=rans[1])
                    return lans[1]>rans[1]?1:-1;
                if(lans[2]!=rans[2])
                    return lans[2]>rans[2]?1:-1;
                if(lx[lx[0]]!=rx[rx[0]])
                    return lx[lx[0]]>rx[rx[0]]?1:-1;
                return 2;
            }
            if(lans[0]==2&&rans[0]<2)
                return 1;
            if(lans[0]<2&&rans[0]==2)
                return -1;
            return 0;
        }
        //One pair
        int check9(int col1,int num1,int col2,int num2){
            memset(a,0,sizeof(a));
            memset(b,0,sizeof(b));
            a[p1[1].col][p1[1].num]=1;
            a[p1[2].col][p1[2].num]=1;
            b[p2[1].col][p2[1].num]=1;
            b[p2[2].col][p2[2].num]=1;
            a[com[1].col][com[1].num]=1;
            b[com[1].col][com[1].num]=1;
            a[com[2].col][com[2].num]=1;
            b[com[2].col][com[2].num]=1;
            a[com[3].col][com[3].num]=1;
            b[com[3].col][com[3].num]=1;
            a[col1][num1]=1;b[col1][num1]=1;
            a[col2][num2]=1;b[col2][num2]=1;
            int ltot[20],rtot[20];
            memset(ltot,0,sizeof(ltot));
            memset(rtot,0,sizeof(rtot));
            for(int i=2;i<=14;i++)
                for(int j=1;j<=4;j++){
                    ltot[i]+=a[j][i];
                    rtot[i]+=b[j][i];
                }
            int lans[5]={0,0,0,0,0},rans[5]={0,0,0,0,0};
            int lx[5]={0,0,0,0,0},rx[5]={0,0,0,0,0};
            for(int i=14;i>=2;i--)
                if(ltot[i]){
                    if(lans[0]<1&&ltot[i]>=2)
                        lans[++lans[0]]=i;
                    else
                        lx[++lx[0]]=i;
                }
            std::sort(lx+1,lx+lx[0]+1);
            for(int i=14;i>=2;i--)
                if(rtot[i]){
                    if(rans[0]<1&&rtot[i]>=2)
                        rans[++rans[0]]=i;
                    else
                        rx[++rx[0]]=i;
                }
            std::sort(rx+1,rx+rx[0]+1);
            if(lans[0]==1&&rans[0]==1){
            	// printf("%d %d\n",lans[1],rans[1]);
                if(lans[1]!=rans[1])
                    return lans[1]>rans[1]?1:-1;
                if(lx[lx[0]]!=rx[rx[0]])
                    return lx[lx[0]]>rx[rx[0]]?1:-1;
                if(lx[lx[0]-1]!=rx[rx[0]-1])
                    return lx[lx[0]-1]>rx[rx[0]-1]?1:-1;
                if(lx[lx[0]-2]!=rx[rx[0]-2])
                    return lx[lx[0]-2]>rx[rx[0]-2]?1:-1;
                return 2;
            }
            if(lans[0]==1&&rans[0]<1)
                return 1;
            if(lans[0]<1&&rans[0]==1)
                return -1;
            return 0;
        }
        //High card
        int check10(int col1,int num1,int col2,int num2){
            int lans[10]={0,p1[1].num,p1[2].num,com[1].num,com[2].num,com[3].num,num1,num2};
            int rans[10]={0,p2[1].num,p2[2].num,com[1].num,com[2].num,com[3].num,num1,num2};
            std::sort(lans+1,lans+8);std::sort(rans+1,rans+8);
            for(int i=7;i>=3;i--)
                if(lans[i]!=rans[i]){
                	// printf("%d:%d %d\n",i,lans[i],rans[i]);
                    return lans[i]>rans[i]?1:-1;
                }
            return 2;
        }

    public:
        bool check(int col1,int num1,int col2,int num2){
            int opt;
            opt=check1(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check1\n");
            opt=check2(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check2\n");
            opt=check3(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check3\n");
            opt=check4(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check4\n");
            opt=check5(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check5\n");
            opt=check6(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            ___++;
            // printf("Finish check6\n");
            opt=check7(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check7\n");
            opt=check8(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check8\n");
            opt=check9(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check9\n");
            opt=check10(col1,num1,col2,num2);
            if(opt)
                return opt==2?0:opt>0;
            // printf("Finish check10\n");
            return 0;
        }
};
checker croupier;

int main(){
    char ch[10][3];
    while(scanf("%s",ch[0]),ch[0][0]!='#'){
        int lans=0,rans=0;
        memset(used,0,sizeof(used));
        for(int i=1;i<7;i++)
            scanf("%s",ch[i]);
        p1[1]=card(ch[0]);p1[2]=card(ch[1]);
        p2[1]=card(ch[2]);p2[2]=card(ch[3]);
        com[1]=card(ch[4]);com[2]=card(ch[5]);com[3]=card(ch[6]);
        for(int i=1;i<=4;i++)
            for(int j=2;j<=14;j++){
                if(used[i][j])
                    continue;
                for(int k=1;k<=4;k++)
                    for(int l=2;l<=14;l++){
                        if(used[k][l])
                            continue;
                        if(i==k&&j==l)
                            continue;
                        rans++;
                        if(croupier.check(i,j,k,l))
                            lans++;
                    }
            }
        printf("%.17Lf\n",(long double)lans/(long double)rans);
    }
    return 0;
}
```

---

## 作者：业余门槛 (赞：4)

题目地址：[点我！](https://jag2012autumn.contest.atcoder.jp/tasks/icpc2012autumn_b)


题目大意：根据德克萨斯扑克的规则，有五张牌应该是明牌，但是此时只明了三张，告诉你你的两张手牌，三张明牌，和对手的三张明牌，求你获胜的概率。

思路：模拟。模拟所有情况，一一PK，数赢得次数。典型的思路简单，程序爆难，考验写程序。

警告：直接提交会爆0！

```cpp
#include<map>
#include<iostream>
#include<iomanip>
//#include<conio.h>
#include<algorithm>
#include<vector>
#include<set>
#include<cmath>
#include<queue>
#include<deque>
#include<stack>
#include<sstream>
#include<string.h>
#define mp make_pair
#define ll long long
#define all(v) v.begin(),v.end()
#define memset(a,b) memset(a,b,sizeof(a))
using namespace std;
const int INF=1e9;
struct pi{
	int hs,ds,bh;
	bool operator < (const pi &q) const{
		return ds > q.ds;
	}
	pi(){}
	pi(int q){
		bh=q;
		hs=q/13;
		ds=q%13;
	}
}p1[10],p2[10],p3[10],p4[10];
bool b[55];
ll mx1,mx2,mi[20];
map<char,int> m1,m2;
inline void init(){
	m1['S']=0;m1['H']=1;m1['D']=2;m1['C']=3;
	m2['2']=0;m2['3']=1;m2['4']=2;m2['5']=3;m2['6']=4;m2['7']=5;m2['8']=6;m2['9']=7;m2['T']=8;m2['J']=9;m2['Q']=10;m2['K']=11;m2['A']=12;
	mi[0]=1;
	for(int i=1;i<17;i++) mi[i]=mi[i-1]*14; 
}
inline bool rd(pi &q){
	string c;
	cin>>c;
	if(c=="#") return 0;
	q=(pi)(m1[c[0]]*13+m2[c[1]]);
	return 1;
}
inline ll work(pi q[]){
	pi w[10];
	memcpy(w,q,sizeof(w));
	sort(w+1,w+6);
	for(int i = 1;i <= 5;++i) ++w[i].ds;
	
	if(w[1].hs==w[2].hs&&w[2].hs==w[3].hs&&w[3].hs==w[4].hs&&w[4].hs==w[5].hs){
		if(w[1].ds-w[2].ds==1&&w[2].ds-w[3].ds==1&&w[3].ds-w[4].ds==1&&w[4].ds-w[5].ds==1) return mi[15]*w[1].ds;
		if(w[1].ds==13&&w[2].ds==4&&w[3].ds==3&&w[4].ds==2&&w[5].ds==1) return mi[15]*4;
	}

	if(w[2].ds==w[3].ds&&w[3].ds==w[4].ds){
		if(w[1].ds==w[3].ds) return mi[14]*w[3].ds+w[5].ds;
		if(w[5].ds==w[3].ds) return mi[14]*w[3].ds+w[1].ds;
	} 

	if(w[1].ds==w[2].ds&&w[4].ds==w[5].ds){
		if(w[3].ds==w[1].ds) return mi[13]*w[3].ds+w[5].ds;
		if(w[3].ds==w[5].ds) return mi[13]*w[3].ds+w[1].ds;
	}

	if(w[1].hs==w[2].hs&&w[2].hs==w[3].hs&&w[3].hs==w[4].hs&&w[4].hs==w[5].hs) return mi[12]*w[1].ds+mi[3]*w[2].ds+mi[2]*w[3].ds+mi[1]*w[4].ds+w[5].ds;

	if(w[1].ds-w[2].ds==1&&w[2].ds-w[3].ds==1&&w[3].ds-w[4].ds==1&&w[4].ds-w[5].ds==1) return mi[11]*w[1].ds;
	if(w[1].ds==13&&w[2].ds==4&&w[3].ds==3&&w[4].ds==2&&w[5].ds==1) return mi[11]*4;

	if(w[1].ds==w[2].ds&&w[2].ds==w[3].ds) return mi[10]*w[3].ds+mi[1]*w[4].ds+w[5].ds;
	if(w[2].ds==w[3].ds&&w[3].ds==w[4].ds) return mi[10]*w[3].ds+mi[1]*w[1].ds+w[5].ds;
	if(w[3].ds==w[4].ds&&w[4].ds==w[5].ds) return mi[10]*w[3].ds+mi[1]*w[1].ds+w[2].ds;

	if(w[1].ds==w[2].ds&&w[3].ds==w[4].ds) return mi[9]*w[1].ds+mi[1]*w[3].ds+w[5].ds;
	if(w[1].ds==w[2].ds&&w[4].ds==w[5].ds) return mi[9]*w[1].ds+mi[1]*w[5].ds+w[3].ds;
	if(w[2].ds==w[3].ds&&w[4].ds==w[5].ds) return mi[9]*w[3].ds+mi[1]*w[5].ds+w[1].ds;

	if(w[1].ds==w[2].ds) return mi[8]*w[1].ds+mi[2]*w[3].ds+mi[1]*w[4].ds+w[5].ds;
	if(w[2].ds==w[3].ds) return mi[8]*w[2].ds+mi[2]*w[1].ds+mi[1]*w[4].ds+w[5].ds;
	if(w[3].ds==w[4].ds) return mi[8]*w[3].ds+mi[2]*w[1].ds+mi[1]*w[2].ds+w[5].ds;
	if(w[4].ds==w[5].ds) return mi[8]*w[4].ds+mi[2]*w[1].ds+mi[1]*w[2].ds+w[3].ds;

	return (mi[4]*w[1].ds+mi[3]*w[2].ds+mi[2]*w[3].ds+mi[1]*w[4].ds+w[5].ds);
}
inline bool check(){
	mx1=mx2=0;
	int i,j,k,l;
	for(i=1;i<=6;i++){
		for(j=i+1;j<=7;j++){
			l=0;
			for(k=1;k<=7;k++) if(k!=i&&k!=j){
				p3[++l]=p1[k];
				p4[l]=p2[k];
			} 
			mx1=max(mx1,work(p3));
			mx2=max(mx2,work(p4));
		}
	}
	return (mx1>mx2);
}
int mian(){
	ios_base::sync_with_stdio(false);
	int i,j;
	int ans=0;
	init();
	while(1){
		memset(b,0);
		ans=0;
		if(!rd(p1[1])) break;
		rd(p1[2]);
		rd(p2[1]);
		rd(p2[2]);
		rd(p1[3]);
		rd(p1[4]);
		rd(p1[5]);
		p2[3]=p1[3];p2[4]=p1[4];p2[5]=p1[5];
		b[p1[1].bh]=b[p1[2].bh]=b[p2[1].bh]=b[p2[2].bh]=b[p1[3].bh]=b[p1[4].bh]=b[p1[5].bh]=1;
		for(i=0;i<52;i++){
			if(!b[i]){
				for(j=i+1;j<52;j++){
					if(!b[j]&&i!=j){
						p1[6]=p2[6]=(pi)(i);
						p1[7]=p2[7]=(pi)(j);
						ans+=check();
					}
				}
			}
		}
		cout<<fixed<<setprecision(20)<<(double)(ans)/(990.0)<<endl; 
	}
}

```

---

## 作者：_rqy (赞：4)

思路：

首先考虑如何比较两手牌的大小。我们给每种五张牌一个字符串，表示其“有多好”；字典序越大的越好。这个字符串可以自己设计，因为牌型基本只分“跟出现次数最多的点数的出现次数有关”和“顺子之类的类型”，不符合这种的可以特判，而大小基本只跟出现次数从多到少的点数有关，所以可以一个一个拼到字符串上。

代码中搞了一些神奇的东西，还有利用宏定义搞出来的“编译期爆搜”（注：这会让编译时间变大不少，跑的也更慢，但是好写啊）。

```cpp
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>

typedef std::string G;

#define mp std::make_pair
std::pair<int, int> P[5];

int k[5];

G Get(int *R, char *S) {
  int s = 0, m = 0, f = 1, t = 0;
  for (int i = 0; i < 5; ++i) k[i] = R[i], f = f && S[i] == S[0];
  std::sort(k, k + 5);
  for (int i = 4; i; --i) if (k[i] != k[0] + i) s = i;
  if (k[0] == 2 && s == 4 && k[4] == 14) s = 0, k[4] = 5;
  if (!s) return G(f ? "S" : "MA") += k[4] + 'A';
  for (int i = 0, j = 1; i < 5; ++i, ++j)
    if (i == 4 || k[i] != k[i + 1])
      P[m++] = mp(j, k[i]), t += j * j, j = 0;
  std::sort(P, P + m);
  G a = "";
#define T(x, y, t) for (int i = (a = x, y); ~i; --i) a += t + 'A'
  if (f && t < 12)
    T("MB", 4, k[i]);
  else
    T('A' + t, m - 1, P[i].second);
  return a;
}

int r[5];
char s[5];
G Run(int *R, char *S) {
  int m = 0;
  G a = "", t;
#define DFS(i, nxt) { nxt; if (m < 5) { r[m] = R[i], s[m++] = S[i]; nxt; --m; } }
  DFS(0, DFS(1, DFS(2, DFS(3, DFS(4, DFS(5, DFS(6, if (m == 5 && (t = Get(r, s)) > a) a = t)))))));
  return a;
}

int R1[7], R2[7];
char S1[7], S2[7], t[9];
int main() {
  while (true) {
#define Read(x, y) {\
    scanf("%s", t);\
    if ((y = *t) == '#') return 0;\
    for (int L = 2; L < 15; ++L) if ("  23456789TJQKA"[L] == t[1]) x = L; }
    Read(R1[0], S1[0]);
    Read(R1[1], S1[1]);
    Read(R2[0], S2[0]);
    Read(R2[1], S2[1]);
    for (int i = 2; i < 5; ++i)
      Read(R1[i] = R2[i], S1[i] = S2[i]);
    int ans = 0;
    for (int a = 2; a < 15; ++a)
      for (int _b = 0; _b < 4; ++_b)
        for (int c = 2; c < 15; ++c)
          for (int _d = 0; _d < 4; ++_d) {
            char b = "SHDC"[_b], d = "SHDC"[_d];
            bool ok = a == c && b == d;
            for (int i = 0; i < 5; ++i)
              ok = ok
                || a == R1[i] && b == S1[i]
                || a == R2[i] && b == S2[i]
                || c == R1[i] && d == S1[i]
                || c == R2[i] && d == S2[i];
            if (ok) continue;
            R1[5] = R2[5] = a; S1[5] = S2[5] = b;
            R1[6] = R2[6] = c; S1[6] = S2[6] = d;
            if (Run(R1, S1) > Run(R2, S2)) ++ans;
          }
    printf("%.9lf\n", ans / 1980.0);
  }
}
```

然后可以来看一看这个 977B 的魔鬼版本（这里为了方便多加了一些换行，实际上第七行起都可以不换行）：

```cpp
#include<bits/stdc++.h>
#define N i]
#define F(i,a,b)for(_ i=a;i<b;++i)
#define T(x,y,p)for(t=x,i=y;i--;)t+=p;
#define W(K)++i;K if(m<5){R[m]=r[N,S[m++]=s[N;K--m;}--i;
#define Y(x,y){cin>>t;if((y=t[0])==35)exit(0);F(L,2,15)if("  23456789TJQKA"[L]==t[1])x=L;}
using namespace std;using _=int;using $=_[11];using G=string;pair<_,_>P[5];$ k,R,A,S,H;G t,e="SHDC";
_ U(){_ s=0,m=0,f=1,T=65,i,j;F(i,0,5)k[N=R[N,f&=S[N==*S;sort(k,k+5);for(i=5;--i;)if(k[N-*k-i)s=i;if(*k==2&s==4&k[4]==14)s=0,*k=1;if(!s)t=G(f?"S":"MA")+=*k;
else{for(i=-1,j=1;++i<5;++j)if(k[N^k[1+N)P[m++]=make_pair(j,k[N),T+=j*j,j=0;sort(P,P+m);if(f&T<77)T("MB",5,k[N)else T(T,m,P[N.second)}}
G V(_*r,_*s){_ m=0,i=-1;G a="";W(W(W(W(W(W(W(if(m==5&&(U(),t>a))a=t;)))))))return a;}
main(){F(i,7,9)Y(A[N,H[N)F(i,0,5)Y(A[N,H[N)_ y=0;F(a,2,15)for(_ b:e)F(c,2,15)for(_ d:e){_ O=a==c&b==d;A[5]=A[6]=0;
F(i,0,9)O|=a==A[N&b==H[N|c==A[N&d==H[N;O||(A[5]=a,H[5]=b,A[6]=c,H[6]=d,y+=V(A,H)<V(A+2,H+2));}printf("%.9lf\n",y/1980.0);main();}
```

---

## 作者：KSCD_ (赞：2)

### 思路
发现从剩余的 $45$ 张牌里选两张的方案数为 $\frac{45\times44}{2}=990$，每个人从七张牌中选五张的方案数为 $\frac{7\times 6}2=28$，总共需要处理的牌型有 $990\times28\times2=55440$ 种，所以直接暴力搜出每一种即可。

另外还有一些处理牌型时能注意到的点：
- 每张牌是什么花色不重要，只需要知道五张牌是否同花色即可。
- 任意两种有区别的牌型均能分出大小。
- 所有比较均是先比较类型，再以某些牌的大小为关键字比较。

因此想到如果能把每种牌型都压成一个数，会更方便比较。所以代码中把牌的类型作为高位，其他关键字依次作为低位压成了一个数。而且这里只需要保证同种类型的牌型处理时位置对齐即可，不同类型之间已经由于最高位不同分出大小了。

一共才 $55440$ 种牌型，且时限 $20$ 秒，处理常数大点也能过，但我的代码大概用了 $200$ 毫秒。

具体还是看代码吧，里面还写了几个函数来简化。
### 代码
```cpp
#include<iostream>
#include<vector>
#include<cstdio> 
#include<algorithm>
#define pb push_back
#define int long long 
#define double long double
using namespace std;
const int P=1e17;
char tc[3];
struct card {int cl,rk;} my[3],op[3],pu[6];
bool eq(card x,card y) {return x.cl==y.cl&&x.rk==y.rk;} //判断两张牌是否相同 
bool chkgl(card x,card y) {return x.rk==y.rk?x.cl<y.cl:x.rk<y.rk;} //给每两张不同牌唯一的大小关系 
vector <card> temp,tem;
vector <int> rk,tk; //rk 为牌型，tk 为比较时的关键字 
int cnt,tcl,p[6];
int ccl(char ch)
{
	if(ch=='S') return 0;
	if(ch=='H') return 1;
	if(ch=='D') return 2;
	return 3;
} //转换花色 
int crk(char ch)
{
	if(ch>='2'&&ch<='9') return ch-'0';
	if(ch=='A') return 14;
	if(ch=='T') return 10;
	if(ch=='K') return 13;
	if(ch=='Q') return 12;
	return 11;
} //转换点数 
bool eqlr(int l,int r)
{
	for(int i=l+1;i<=r;i++) if(rk[i]!=rk[i-1]) return false;
	return true;
} //判断 rk 中 [l,r] 是否相等 
int flus()
{
	if(rk[4]==14)
	{
		bool tf=true;
		for(int i=0;i<4;i++) if(rk[i]!=i+2) tf=false;
		if(tf) return 1;
	}
	for(int i=1;i<5;i++) if(rk[i]!=rk[i-1]+1) return 0;
	return rk[0];
} //判断 rk 中的五张牌是不是顺子，若是，返回其最小值作为权值 
int so()
{
	int res=0,len=tk.size();
	for(int i=0;i<len;i++) res+=tk[i]*p[len-i-1];
	return res;
} //把 tk 中的比较关键字压缩成一个数字 
void ins(int x) {tk.pb(x);}
int sol()
{
	sort(rk.begin(),rk.end()); //先升序排序 
	if(tcl!=-2&&flus()) return P*9+flus(); //同花顺 
	if(eqlr(0,3)) {ins(rk[0]),ins(rk[4]); return P*8+so();}
	if(eqlr(1,4)) {ins(rk[1]),ins(rk[0]); return P*8+so();} //四张 
	if(eqlr(0,2)&&eqlr(3,4)) {ins(rk[0]),ins(rk[3]); return P*7+so();}
	if(eqlr(0,1)&&eqlr(2,4)) {ins(rk[2]),ins(rk[0]); return P*7+so();} //三带二 
	if(tcl!=-2) {for(int i=4;i>=0;i--) ins(rk[i]); return P*6+so();} //同花色 
	if(flus()) return P*5+flus(); //顺子 
	if(eqlr(0,2)) {ins(rk[0]),ins(rk[4]),ins(rk[3]); return P*4+so();}
	if(eqlr(1,3)) {ins(rk[1]),ins(rk[4]),ins(rk[0]); return P*4+so();}
	if(eqlr(2,4)) {ins(rk[2]),ins(rk[1]),ins(rk[0]); return P*4+so();} //三张 
	if(eqlr(1,2)&&eqlr(3,4)) {ins(rk[3]),ins(rk[1]),ins(rk[0]); return P*3+so();}
	if(eqlr(0,1)&&eqlr(3,4)) {ins(rk[3]),ins(rk[0]),ins(rk[2]); return P*3+so();}
	if(eqlr(0,1)&&eqlr(2,3)) {ins(rk[2]),ins(rk[0]),ins(rk[4]); return P*3+so();} //两对 
	for(int i=0;i<4;i++) if(rk[i]==rk[i+1])
	{
		ins(rk[i]);
		for(int j=4;j>=0;j--) if(j!=i&&j!=i+1) ins(rk[j]);
		return P*2+so();
	} //一对 
	for(int i=4;i>=0;i--) ins(rk[i]);
	return P+so(); //单牌 
}
int solv()
{
	tcl=-1,rk.clear(),tk.clear();
	for(card k:tem) rk.pb(k.rk),tcl=((tcl==-1||tcl==k.cl)?k.cl:-2);
	return sol();
} //判断 tem 中五张牌是否同花色，不同则 tcl=-2，同时把点数传到 rk 中 
int solve()
{
	int res=-1;
	for(int i=0;i<7;i++) for(int j=i+1;j<7;j++)
	{
		tem.clear();
		for(int k=0;k<7;k++) if(k!=i&&k!=j) tem.pb(temp[k]);
		res=max(res,solv());
	}
	return res;
} //枚举 temp 中七张牌选五张（不选两张）的方案，并传到 tem 计算最大值 
void check()
{
	if(eq(pu[4],pu[5])||chkgl(pu[4],pu[5])) return;
	for(int i=4;i<=5;i++)
	{
		for(int j=1;j<=2;j++) if(eq(pu[i],my[j])||eq(pu[i],op[j])) return;
		for(int j=1;j<=3;j++) if(eq(pu[i],pu[j])) return;
	} //判断没有牌重复 
	int mysc,opsc; temp.clear();
	for(int i=1;i<=5;i++) temp.pb(pu[i]);
	temp.pb(my[1]),temp.pb(my[2]),mysc=solve(),temp.pop_back();
	temp.pop_back(),temp.pb(op[1]),temp.pb(op[2]),opsc=solve(); //分别把各自的七张牌传到 temp 中计算 
	cnt+=(mysc>opsc);
} //对于每种 pu[4],pu[5] 的情况计算是否获胜 
signed main()
{
	p[0]=1;  for(int i=1;i<=5;i++) p[i]=p[i-1]*1000;
	while(cin>>tc)
	{
		if(tc[0]=='#') break;
		cnt=0,my[1]={ccl(tc[0]),crk(tc[1])};
		cin>>tc,my[2]={ccl(tc[0]),crk(tc[1])};
		for(int i=1;i<=2;i++) cin>>tc,op[i]={ccl(tc[0]),crk(tc[1])};
		for(int i=1;i<=3;i++) cin>>tc,pu[i]={ccl(tc[0]),crk(tc[1])}; //存储牌 
		for(pu[4].cl=0;pu[4].cl<4;pu[4].cl++) for(pu[4].rk=2;pu[4].rk<=14;pu[4].rk++)
		for(pu[5].cl=0;pu[5].cl<4;pu[5].cl++) for(pu[5].rk=2;pu[5].rk<=14;pu[5].rk++) check(); //枚举 
		printf("%.8Lf\n",(double)cnt/990);
	}
	return 0;
}
```

---

## 作者：dead_X (赞：2)

## 前言
不知道什么时候在什么比赛碰到了这个题，发现洛谷上有，水过
## 思路
枚举所有附加两张牌的可能，然后依次比较。

对于比较，我们将所有牌型从高到低判断，如果某一位能分出胜负，就返回对应的结果。在每种牌型的 $21$ 个选择中取对应判断的最大值即可。

这道题只要你的逻辑清晰其实是非常好写的 ``>_<``

**切记多写函数，每个函数里竟可能执行简单的东西，可以大幅度增加调试效率。**

这种大模拟题似乎在这里说一堆话没有什么用，大家直接看代码吧。
## 代码
```
#include<bits/stdc++.h>
#define qwq(c1,c2,c3,c4,c5) p=max(p,check(i,a_create(c1,c2,c3,c4,c5))),q=max(q,check(i,b_create(c1,c2,c3,c4,c5)))
using namespace std;
inline int read(){
   int s=0;
   char ch=getchar();
   while(ch<'0'||ch>'9') ch=getchar();
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s;
}
struct card{ char kind,num; bool operator <(const card &a)const{ if(a.num!=num) return a.num<num; return a.kind<kind; };};
struct cardset{ card c[13]; };
int four(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0;
	for(int i=14; i; i--) if(vis[i]==4) res+=10000*i; else if(vis[i]) res+=i;
	if(res<10000) return 0;
	return res;
} 
//炸弹，不是炸弹返回0，不然返回值越大牌越大 
int three(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0,t=15;
	for(int i=14; i; i--) if(vis[i]==3) res+=10000*i; else if(vis[i]) res+=i*t,t/=15;
	if(res<10000) return 0;
	return res;
} 
//三张，不是返回0，不然返回值越大牌越大 
int twopairs(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0,t=15*15,ps=0;
	for(int i=14; i; i--) if(vis[i]==2) res+=t*i,t/=15,++ps; else if(vis[i]) res+=i;
	if(ps==2) return res;
	return 0;
} 
//两对，不是返回0，不然返回值越大牌越大 
int pair1(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0,t=15*15,ps=0;
	for(int i=14; i; i--) if(vis[i]==2) res+=15*15*15*i,++ps; else if(vis[i]) res+=i*t,t/=15;
	if(ps) return res;
	return 0;
} 
//一对，不是返回0，不然返回值越大牌越大 
int threetwo(cardset x)
{
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int res=0;
	bool two=0;
	for(int i=14; i; i--) if(vis[i]==3) res+=10000*i; else if(vis[i]==2) res+=i,two=1;
	if(res<10000 || !two) return 0;
	return res;
} 
//三带二，不是返回0，不然返回值越大牌越大 
int flush(cardset x) 
{ 
	for(int i=1; i<5; i++) if(x.c[i].kind==x.c[i+1].kind) continue; else return 0;
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]=1; break;
		case 'T': vis[10]=1; break;
		case 'J': vis[11]=1; break;
		case 'Q': vis[12]=1; break;
		case 'K': vis[13]=1; break;
		default: vis[x.c[i].num-48]=1; break;
	}
	int t=15*15*15*15,res=0;
	for(int i=14; i; i--) if(vis[i]) res+=t*i,t/=15;
	return res;
}
//同花，不是同花返回0，不然返回值越大牌越大 
int high(cardset x) 
{ 
	int vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[14]++; break;
		case 'T': vis[10]++; break;
		case 'J': vis[11]++; break;
		case 'Q': vis[12]++; break;
		case 'K': vis[13]++; break;
		default: vis[x.c[i].num-48]++; break;
	}
	int t=15*15*15*15,res=0;
	for(int i=14; i; i--) while(vis[i]--) res+=t*i,t/=15;
	return res;
}
//散牌，返回值越大牌越大 
int straight(cardset x)
{
	bool vis[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i=1; i<=5; i++) switch(x.c[i].num)
	{
		case 'A': vis[1]=vis[14]=1; break;
		case 'T': vis[10]=1; break;
		case 'J': vis[11]=1; break;
		case 'Q': vis[12]=1; break;
		case 'K': vis[13]=1; break;
		default: vis[x.c[i].num-48]=1; break;
	}
	for(int i=1; i<=10; i++) if(vis[i] && vis[i+1] && vis[i+2] && vis[i+3] && vis[i+4]) return i+4;
	return 0;
}
//顺子，不是顺子返回0，不然返回最大的点数 
set<card> S;
card a[13],b[13];
card create(char x,char y) { card tmp; tmp.kind=x,tmp.num=y; return tmp; }
cardset a_create(int n,int m,int p,int q,int r) { cardset tmp; tmp.c[1]=a[n],tmp.c[2]=a[m],tmp.c[3]=a[p],tmp.c[4]=a[q],tmp.c[5]=a[r]; return tmp; }
cardset b_create(int n,int m,int p,int q,int r) { cardset tmp; tmp.c[1]=b[n],tmp.c[2]=b[m],tmp.c[3]=b[p],tmp.c[4]=b[q],tmp.c[5]=b[r]; return tmp; }
char x[13]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
char y[4]={'S','H','D','C'};
int check(int type,cardset s)
{
	switch(type)
	{
		case 1:
			if(flush(s) && straight(s)) return straight(s); else return 0;
			break;
		case 2:
			return four(s);
			break;
		case 3:
			return threetwo(s);
			break;
		case 4:
			return flush(s);
			break;
		case 5:
			return straight(s);
			break;
		case 6:
			return three(s);
			break;
		case 7:
			return twopairs(s);
			break;
		case 8:
			return pair1(s);
			break;
		case 9:
			return high(s);
			break;
	}
}
void debug1()
{
	//for(int i=1; i<=7; i++) cout<<a[i].kind<<a[i].num<<' '; puts("");
	//for(int i=1; i<=7; i++) cout<<b[i].kind<<b[i].num<<' '; puts("");
}
int compare()
{
	for(int i=1; i<=9; i++) 
	{
		int p=0,q=0;
		qwq(1,2,3,4,5);
		qwq(1,2,3,4,6);
		qwq(1,2,3,4,7);
		qwq(1,2,3,5,6);
		qwq(1,2,3,5,7);
		qwq(1,2,3,6,7);
		qwq(1,2,4,5,6);
		qwq(1,2,4,5,7);
		qwq(1,2,4,6,7);
		qwq(1,2,5,6,7);
		qwq(1,3,4,5,6);
		qwq(1,3,4,5,7);
		qwq(1,3,4,6,7);
		qwq(1,3,5,6,7);
		qwq(1,4,5,6,7);
		qwq(2,3,4,5,6);
		qwq(2,3,4,5,7);
		qwq(2,3,4,6,7);
		qwq(2,3,5,6,7);
		qwq(2,4,5,6,7);
		qwq(3,4,5,6,7);
		if(p==0 && q==0) continue;
		if(p>q) {
		debug1();return 1; }else return 0;
	}
	
}
void init() { S.clear(); for(int i=0; i<13; i++) for(int j=0; j<4; j++) S.insert(create(y[j],x[i])); }
void input()
{ 
	a[1].kind=getchar();
	if(a[1].kind=='#') exit(0);
	a[1].num=getchar();getchar();
	a[2].kind=getchar(),a[2].num=getchar();getchar();
	b[1].kind=getchar(),b[1].num=getchar();getchar();
	b[2].kind=getchar(),b[2].num=getchar();getchar();
	a[3].kind=b[3].kind=getchar(),a[3].num=b[3].num=getchar(),getchar();
	a[4].kind=b[4].kind=getchar(),a[4].num=b[4].num=getchar(),getchar();
	a[5].kind=b[5].kind=getchar(),a[5].num=b[5].num=getchar(),getchar();
	S.erase(S.find(a[1])),S.erase(S.find(a[2])),S.erase(S.find(a[3])),S.erase(S.find(a[4])),S.erase(S.find(a[5])),S.erase(S.find(b[1])),S.erase(S.find(b[2])); 
}
void calc()
{
	int ans=0;
	for(set<card>::iterator i=S.begin(); i!=S.end(); i++) for(set<card>::iterator j=i; j!=S.end(); j++) if(i!=j) a[6]=b[6]=*i,a[7]=b[7]=*j,ans+=compare();
	printf("%.10lf\n",ans/990.0);
}
int main()
{
	while(1) init(),input(),calc();
	return 0;
}
/*
SA SK
DA CA
SQ SJ ST
SA HA
D2 C3
H4 S5 DA
HA D9
H6 C9
H3 H4 H5
#

*/
```

---

## 作者：封禁用户 (赞：2)

首先题目不难懂，只需要去暴力模拟即可。但程序很难写，看到楼下几位大佬写的题解都写了几百行，！！！ _其实用13进制加权求和_！！！（划重点） ，写起来就十分容易。具体细节请看代码。

记得关注我的博客哦：https://www.luogu.org/blog/Noi2017/

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef signed long long ll;
#undef _P
#define _P(...) (void)printf(__VA_ARGS__)
#define FOR(x,to) for(x=0;x<to;x++)
#define FORR(x,arr) for(auto& x:arr)
#define ITR(x,c) for(__typeof(c.begin()) x=c.begin();x!=c.end();x++)
#define ALL(a) (a.begin()),(a.end())
#define ZERO(a) memset(a,0,sizeof(a))
#define MINUS(a) memset(a,0xff,sizeof(a))
int card(string S) {
	int v=0;
	if(S[0]=='S') v=0;
	if(S[0]=='D') v=13;
	if(S[0]=='H') v=26;
	if(S[0]=='C') v=39;
	if(S[1]=='A') v+=12;
	else if(S[1]=='T') v+=8;
	else if(S[1]=='J') v+=9;
	else if(S[1]=='Q') v+=10;
	else if(S[1]=='K') v+=11;
	else v+=S[1]-'2';
	return v;
}
int hand(vector<int> V) {
	if(V[0]/13==V[4]/13) {
		FORR(r,V) r%=13; // remove suit
		if(V[0]+4==12) return 9000000; //royal straight flush
		if(V[0]+4==V[4]) return 8000000+V[4]; // straight
		if(V[0]==0 && V[3]==3 && V[4]==12) return 8000000+3;
		return 5000000+(((V[4]*13+V[3])*13+V[2])*13+V[1])*13+V[0];
	}
	else {
		FORR(r,V) r%=13; // remove suit
		sort(ALL(V));
		if(V[0]==V[3]) return 7000000+V[2]*13+V[4]; // four card
		if(V[1]==V[4]) return 7000000+V[2]*13+V[0];
		if(V[0]==V[2] && V[3]==V[4]) return 6000000+V[0]*13+V[4]; // full house
		if(V[0]==V[1] && V[2]==V[4]) return 6000000+V[4]*13+V[0];
		if(V[0]+1==V[1] && V[1]+1==V[2] && V[2]+1==V[3] && V[3]+1==V[4]) return 4000000+V[4]; // straight
		if(V[0]==0 && V[1]==1 && V[2]==2 && V[3]==3 && V[4]==12) return 4000000+3;
		if(V[0]==V[2]) return 3000000+V[2]*13*13+V[4]*13+V[3]; // three card
		if(V[1]==V[3]) return 3000000+V[2]*13*13+V[4]*13+V[0];
		if(V[2]==V[4]) return 3000000+V[2]*13*13+V[1]*13+V[0];
		if(V[0]==V[1]&&V[2]==V[3]) return 2000000+V[3]*13*13+V[1]*13+V[4]; // two pair
		if(V[0]==V[1]&&V[3]==V[4]) return 2000000+V[3]*13*13+V[1]*13+V[2];
		if(V[1]==V[2]&&V[3]==V[4]) return 2000000+V[3]*13*13+V[1]*13+V[0];
		if(V[4]==V[3]) return 1000000+V[3]*13*13*13+V[2]*13*13+V[1]*13+V[0]; // one pair
		if(V[3]==V[2]) return 1000000+V[2]*13*13*13+V[4]*13*13+V[1]*13+V[0];
		if(V[2]==V[1]) return 1000000+V[1]*13*13*13+V[4]*13*13+V[3]*13+V[0];
		if(V[1]==V[0]) return 1000000+V[0]*13*13*13+V[4]*13*13+V[3]*13+V[2];
		return (((V[4]*13+V[3])*13+V[2])*13+V[1])*13+V[0];
	}
}
int hand(int c1,int c2,int c3,int c4,int c5,int c6,int c7) {
	int ma=0,mask,i;
	vector<int> V={c1,c2,c3,c4,c5,c6,c7};
	sort(ALL(V));
	FOR(mask,1<<7) if(__builtin_popcount(mask)==5) {
		vector<int> V2;
		FOR(i,7) if(mask & (1<<i)) V2.push_back(V[i]);
		ma=max(ma,hand(V2));
	}
	return ma;
}
void solve() {
	int i,j,k,l,r,x,y; string s;
	while(1) {
		int my[2],op[2],com[5];
		int vis[60]={};
		cin>>s;
		if(s=="#") return;
		my[0]=card(s), vis[my[0]]=1;
		cin>>s; my[1]=card(s), vis[my[1]]=1;
		cin>>s; op[0]=card(s), vis[op[0]]=1;
		cin>>s; op[1]=card(s), vis[op[1]]=1;
		cin>>s; com[0]=card(s), vis[com[0]]=1;
		cin>>s; com[1]=card(s), vis[com[1]]=1;
		cin>>s; com[2]=card(s), vis[com[2]]=1;
		i=0;
		int win=0;
		FOR(y,52) FOR(x,y) if(vis[x]==0 && vis[y]==0)
			win += hand(my[0],my[1],com[0],com[1],com[2],x,y)>hand(op[0],op[1],com[0],com[1],com[2],x,y);
		_P("%.12lf\n",win/(45*44/2.0));
	}
}
int main(int argc,char** argv){
	string s;int i;
	if(argc==1) ios::sync_with_stdio(false);
	FOR(i,argc-1) s+=argv[i+1],s+='\n';
	FOR(i,s.size()) ungetc(s[s.size()-1-i],stdin);
	solve(); return 0;
}

```

---

## 作者：哈哈人生 (赞：1)

# 前言
### 本题解后面有几种代码 WA 可能性，请有需要的读者自行查看！
打大模拟就是打时很崩溃，打完很爽。

# 题意简化
一副扑克牌，去掉大小王。你和对手各有 $5$ 张牌，桌子上还有 $2$ 张未翻开的牌，你们需要从自己的牌和桌子上的牌中一共选 $5$ 张牌。你的 $5$ 张牌与对手的 $5$ 张牌之间一定有胜负平的关系（可概括为先比牌型再比大小，更进一步具体的关系请参考题面）。请对于桌子上的 $2$ 张盲牌所有的可能性，求出你的胜率（平局不算胜利）。

# 思路
这是一道纯大模拟。因为去掉大小王的牌只有 $52$ 种，直接暴力枚举两张牌即可。然后分别对于自己和对手的手牌和桌牌组成的 $7$ 张牌枚举选 $5$ 张牌的可能，分别选出自己和对手最优可能，再比较它们二者之间（即自己和对手最优可能）谁的更优，记录自己胜利的情况数和总情况数，最后相除转为浮点数即可。总结一下我们大致要干 $3$ 件事。

1. 先从 $52$ 张牌中选 $2$ 张牌，再从 $2+5$ 张牌中选 $5$ 张牌。
2. 对于自己和对手，从以上的可能中选最优可能。
3. 比较自己和对手的最优可能谁更优。

这时我们可以惊喜地发现，其实 $2$ 和 $3$ 是一件事，只需要实现一个 $5$ 张牌和 $5$ 张牌的比较优秀性的函数，$2$ 操作直接对于所有可能用这个函数用打擂法求最优可能即可，$3$ 操作直接比较即可。

# 时间复杂度
操作 $1$ 复杂度为 $52\times 52\times 28(C(7,5))$。\
操作 $2,3$ 复杂度均为比较函数复杂度时间为常数。

# 代码 WA 可能问题
1. 注意未知桌牌没有可能与已知手牌一样，两张未知桌牌也不可能一样，所以两张未知桌牌其实一共只有 $990$ 种可能（如果你没有关注枚举的顺序 $1980$ 种可能也对）。

2. 注意多次测评的清空。
3. 注意 ``2345A`` 和 ``TJQKA`` 最大牌一样，但一个是最小的顺子，一个是最大的顺子。
4. 如果你代码开始关闭了同步流，就不能再使用 ``printf("%.020lf",1.0*ans1/ans2)`` 这一行语句了。

# AC 代码
马蜂非常好。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char dian[15]=" 23456789TJQKA",hua[6]=" SHDC";
string a1,a2,b1,b2,xx,yy,zz,s[11];
string ls[6],bep[6],my[6],your[6];
int ddx(char ch) {
	if(ch=='T')return 9;
	else if(ch=='J')return 10;
	else if(ch=='Q')return 11;
	else if(ch=='K')return 12;
	else if(ch=='A')return 13;
	else return ch-'0'-1;
}
bool cmp(string a,string b) {
	return ddx(a[1])<ddx(b[1]);
}
bool lx(string a[6]) {
	for(int i=1; i<=4; i++) {
		if(i==4&&a[i][1]=='5'&&a[i+1][1]=='A')break;
		if(ddx(a[i][1])+1!=ddx(a[i+1][1]))return 0;
	}
	return 1;
}
bool th(string a[6]) {
	for(int i=2; i<=5; i++) {
		if(a[i][0]!=a[1][0])return 0;
	}
	return 1;
}
int cmp2(string a[6]) {
	int x;
	bool pd1=lx(a),pd2=th(a);
	if(pd1&&pd2) {
		if(a[1][1]=='T')x=1;
		else x=2;
	} else if(a[1][1]==a[4][1]||a[2][1]==a[5][1]) {
		x=3;
	} else if(a[1][1]==a[2][1]&&a[3][1]==a[5][1]||a[1][1]==a[3][1]&&a[4][1]==a[5][1]) {
		x=4;
	} else if(pd2) {
		x=5;
	} else if(pd1) {
		x=6;
	} else if(a[1][1]==a[3][1]||a[2][1]==a[4][1]||a[3][1]==a[5][1]) {
		x=7;
	} else {
		int cnt=0;
		if(a[1][1]==a[2][1])cnt++;
		if(a[2][1]==a[3][1])cnt++;
		if(a[3][1]==a[4][1])cnt++;
		if(a[4][1]==a[5][1])cnt++;
		if(cnt==2)x=8;
		else if(cnt==1)x=9;
		else x=10;
	}
	return x;
}
bool dx(string a[6],string b[6]) {
	int x=cmp2(a),y=cmp2(b);
	if(x<y)return 1;
	else if(x>y)return 0;
	else {
		if(x==1)return 0;
		else if(x==2||x==6) {
			if(a[1][1]=='2'||b[1][1]=='2') {
				if(a[1][1]=='2'&&b[1][1]=='2') {
					if(ddx(a[5][1])>=ddx(b[5][1]))return 0;
					else return 1;
				}
				else if(a[1][1]=='2'){
					return 0;
				}
				else return 1;
			} else if(ddx(a[1][1])<=ddx(b[1][1]))return 0;
			else return 1;
		} else if(x==3) {
			char bj1,bj2;
			if(a[1][1]==a[2][1])bj1=a[1][1];
			else bj1=a[5][1];
			if(b[1][1]==b[2][1])bj2=b[1][1];
			else bj2=b[5][1];
			if(ddx(bj1)<ddx(bj2))return 0;
			else if(ddx(bj1)>ddx(bj2))return 1;
			if(a[1][1]==a[2][1])bj1=a[5][1];
			else bj1=a[1][1];
			if(b[1][1]==b[2][1])bj2=b[5][1];
			else bj2=b[1][1];
			if(ddx(bj1)<=ddx(bj2))return 0;
			else return 1;
		} else if(x==4) {
			char bj1,bj2;
			if(a[1][1]==a[3][1])bj1=a[1][1];
			else bj1=a[5][1];
			if(b[1][1]==b[3][1])bj2=b[1][1];
			else bj2=b[5][1];
			if(ddx(bj1)<ddx(bj2))return 0;
			else if(ddx(bj1)>ddx(bj2))return 1;
			if(a[1][1]==a[3][1])bj1=a[5][1];
			else bj1=a[1][1];
			if(b[1][1]==b[3][1])bj2=b[5][1];
			else bj2=b[1][1];
			if(ddx(bj1)<=ddx(bj2))return 0;
			else return 1;
		} else if(x==5||x==10) {
			for(int i=5; i>=1; i--) {
				if(ddx(a[i][1])>ddx(b[i][1]))return 1;
				else if(ddx(a[i][1])<ddx(b[i][1]))return 0;
			}
			return 0;
		} else if(x==7) {
			char ax,ay,az,bx,by,bz;
			if(a[1][1]==a[3][1]) {
				ax=a[1][1],ay=a[5][1],az=a[4][1];
			} else if(a[2][1]==a[4][1]) {
				ax=a[2][1],ay=a[5][1],az=a[1][1];
			} else {
				ax=a[3][1],ay=a[2][1],az=a[1][1];
			}
			if(b[1][1]==b[3][1]) {
				bx=b[1][1],by=b[5][1],bz=b[4][1];
			} else if(b[2][1]==b[4][1]) {
				bx=b[2][1],by=b[5][1],bz=b[1][1];
			} else {
				bx=b[3][1],by=b[2][1],bz=b[1][1];
			}
			if(ddx(ax)<ddx(bx))return 0;
			else if(ddx(ax)>ddx(bx))return 1;
			if(ddx(ay)<ddx(by))return 0;
			else if(ddx(ay)>ddx(by))return 1;
			if(ddx(az)<=ddx(bz))return 0;
			else if(ddx(az)>ddx(bz))return 1;
		} else if(x==8) {
			char ax,ay,az,bx,by,bz;
			if(a[4][1]==a[5][1]) {
				ax=a[4][1];
				if(a[2][1]==a[3][1])ay=a[2][1],az=a[1][1];
				else ay=a[2][1],az=a[3][1];
			} else {
				ax=a[3][1];
				ay=a[1][1];
				az=a[5][1];
			}
			if(b[4][1]==b[5][1]) {
				bx=b[4][1];
				if(b[2][1]==b[3][1])by=b[2][1],bz=b[1][1];
				else by=b[2][1],bz=b[3][1];
			} else {
				bx=b[3][1];
				by=b[1][1];
				bz=b[5][1];
			}
			if(ddx(ax)<ddx(bx))return 0;
			else if(ddx(ax)>ddx(bx))return 1;
			if(ddx(ay)<ddx(by))return 0;
			else if(ddx(ay)>ddx(by))return 1;
			if(ddx(az)<=ddx(bz))return 0;
			else if(ddx(az)>ddx(bz))return 1;
		} else {
			char ax,ay,az,aa,bx,by,bz,ba;
			if(a[4][1]==a[5][1]) {
				ax=a[4][1];
				ay=a[3][1];
				az=a[2][1];
				aa=a[1][1];
			} else if(a[3][1]==a[4][1]) {
				ax=a[3][1];
				ay=a[5][1];
				az=a[2][1];
				aa=a[1][1];
			} else if(a[2][1]==a[3][1]) {
				ax=a[2][1];
				ay=a[5][1];
				az=a[4][1];
				aa=a[1][1];
			} else {
				ax=a[1][1];
				ay=a[5][1];
				az=a[4][1];
				aa=a[3][1];
			}
			if(b[4][1]==b[5][1]) {
				bx=b[4][1];
				by=b[3][1];
				bz=b[2][1];
				ba=b[1][1];
			} else if(b[3][1]==b[4][1]) {
				bx=b[3][1];
				by=b[5][1];
				bz=b[2][1];
				ba=b[1][1];
			} else if(b[2][1]==b[3][1]) {
				bx=b[2][1];
				by=b[5][1];
				bz=b[4][1];
				ba=b[1][1];
			} else {
				bx=b[1][1];
				by=b[5][1];
				bz=b[4][1];
				ba=b[3][1];
			}
			if(ddx(ax)<ddx(bx))return 0;
			else if(ddx(ax)>ddx(bx))return 1;
			if(ddx(ay)<ddx(by))return 0;
			else if(ddx(ay)>ddx(by))return 1;
			if(ddx(az)<ddx(bz))return 0;
			else if(ddx(az)>ddx(bz))return 1;
			if(ddx(aa)<=ddx(ba))return 0;
			else if(ddx(aa)>ddx(ba))return 1;
		}
	}
}
void dfs(int p,int q,string jp[6]) {
	if(7-p+q<5)return;
	if(q==6) {
		if(bep[0]=="false") {
			bep[0]="true";
			for(int i=1; i<=5; i++)bep[i]=jp[i];
		} else {
			if(dx(jp,bep)) {
				for(int i=1; i<=5; i++)bep[i]=jp[i];
			}
		}
		return;
	}
	for(int i=p; i<=7; i++) {
		jp[q]=s[i];
		dfs(i+1,q+1,jp);
	}
}
signed main() {
	while(1) {
		cin>>a1;
		if(a1=="#")break;
		cin>>a2>>b1>>b2>>xx>>yy>>zz;
		int ans1=0,ans2=0;
		for(int i=1; i<=13; i++) {
			for(int j=1; j<=4; j++) {
				for(int ii=1; ii<=13; ii++) {
					for(int jj=1; jj<=4; jj++) {
						string c1="",c2="";
						c1+=hua[j],c2+=hua[jj];
						c1+=dian[i],c2+=dian[ii];
						if(c1==xx||c1==yy||c1==zz||c1==a1||c1==a2||c1==b1||c1==b2)continue;
						if(c2==xx||c2==yy||c2==zz||c2==a1||c2==a2||c2==b1||c2==b2)continue;
						if(c1==c2)continue;
						s[1]=xx,s[2]=yy,s[3]=zz,s[4]=c1,s[5]=c2;
						s[6]=a1,s[7]=a2;
						sort(s+1,s+8,cmp);
						bep[0]="false";
						dfs(1,1,ls);
						for(int k=1; k<=5; k++)my[k]=bep[k];
						s[1]=xx,s[2]=yy,s[3]=zz,s[4]=c1,s[5]=c2;
						s[6]=b1,s[7]=b2;
						sort(s+1,s+8,cmp);
						bep[0]="false";
						dfs(1,1,ls);
						for(int k=1; k<=5; k++)your[k]=bep[k];
						if(dx(my,your))ans1++;
						ans2++;
					}
				}
			}
		}
		printf("%.020f\n",1.0*ans1/ans2);
	}
	return 0;
}
```
代码接近三百行，点个赞呗。

---

## 作者：FlyPancake (赞：1)

## [Texas hold'em](https://www.luogu.com.cn/problem/AT_icpc2012autumn_b) 题解

这是一道纯纯大模拟，笔者调了 3 天，疯掉了，故写一篇题解纪念。

## Ideas

可以把整个游戏分为几个阶段。

### 0.转换

考虑将 `A` 转换为 `14`，`B` 转换为 `13`，依此类推。

以下 $fi$ 存原卡牌，$se$ 存卡牌点数。

```
void init(psi &s){
    if(s.fi[1] == 'A') s.se = 14;
    else if(s.fi[1] == 'K') s.se = 13;
    else if(s.fi[1] == 'Q') s.se = 12;
    else if(s.fi[1] == 'J') s.se = 11;
    else if(s.fi[1] == 'T') s.se = 10;
    else s.se = int(s.fi[1] - '0');
}
```

### 1.读入

注意读到 `#` 时退出。

### 2.枚举未知牌

从 52 张牌中枚举选出剩下 2 张不知道的牌。

注意要判断是否与已知牌重复。

```
bool is_repeat(string s){
    if(s==ha[0] || s==ha[1] || s==hb[0] || s==hb[1] ||
        s==pub[0] || s==pub[1] || s==pub[2] || s==pub[3] || s==pub[4]) return true;
    else return false;
}

for(int i=0; i<52; i++){
    if(is_repeat(card[i])) continue;
    pub[3] = card[i];
    ha[5] = hb[5] = pub[3]; 
    for(int j=i+1; j<52; j++){
        if(is_repeat(card[j])) continue;
        pub[4] = card[j];
        ha[6] = hb[6] = pub[4]; 
        quan[0].se = quan[1].se = 0;
        choose();
        tot++; if(quan[0].se > quan[1].se) win++;
        pub[4] = "NULL";
    }
    pub[3] = "NULL";
}
```

### 3.选牌

枚举每个人 2 张手牌和 5 张公共牌并选取。

注意每个人是从 7 张牌中选 5 张牌而不是从 5 张牌中选 3 张牌。~~（笔者在这里挂了两天半）~~

```
void choose(){
    for(int i1=0; i1<7; i1++)
        for(int i2=i1+1; i2<7; i2++)
            for(int i3=i2+1; i3<7; i3++)
                for(int i4=i3+1; i4<7; i4++)
                    for(int i5=i4+1; i5<7; i5++){
                        hand[0][0].fi = ha[i1], hand[0][1].fi = ha[i2], hand[0][2].fi = ha[i3], hand[0][3].fi = ha[i4], hand[0][4].fi = ha[i5];
				        init(hand[0][0]); init(hand[0][1]); init(hand[0][2]); init(hand[0][3]); init(hand[0][4]);
                        check(hand[0], 0);
                        quan[0].se = max(quan[0].fi, quan[0].se);
                    }
    for(int j1=0; j1<7; j1++)
        for(int j2=j1+1; j2<7; j2++)
            for(int j3=j2+1; j3<7; j3++)
                for(int j4=j3+1; j4<7; j4++)
                    for(int j5=j4+1; j5<7; j5++){
                        hand[1][0].fi = hb[j1], hand[1][1].fi = hb[j2], hand[1][2].fi = hb[j3], hand[1][3].fi = hb[j4], hand[1][4].fi = hb[j5];
                        init(hand[1][0]); init(hand[1][1]); init(hand[1][2]); init(hand[1][3]); init(hand[1][4]);
                        check(hand[1], 1);
                        quan[1].se = max(quan[1].fi, quan[1].se);
                    }
}
```

### 4.判断卡牌类型

最折磨的部分。

笔者这里将每种卡牌类型和卡牌点数附上权值，以便之后比较。

注意顺子中 `A` **开头**的情况以及**同花顺的处理**。

```
void check(vector<psi> s, int id){
    quan[id].fi = 0;
    sort(s.begin(), s.end(), [&](psi a, psi b){ return a.se > b.se; });
    if(s[0].fi[0]==s[1].fi[0] && s[1].fi[0]==s[2].fi[0] && s[2].fi[0]==s[3].fi[0] && s[3].fi[0]==s[4].fi[0])
        quan[id].fi = 6*TIME + s[0].se*100000000 + s[1].se*1000000 + s[2].se*10000 + s[3].se*100 + s[4].se; // 同花 fi = 6
    if(s[0].se==s[1].se && s[1].se==s[2].se && s[2].se==s[3].se)
        quan[id].fi = 8*TIME + s[0].se*100 + s[4].se;
    else if(s[3].se==s[4].se && s[1].se==s[2].se && s[2].se==s[3].se)
        quan[id].fi = 8*TIME + s[1].se*100 + s[0].se; // 四条 fi = 8
    else if(s[0].se==s[1].se && s[1].se==s[2].se && s[3].se==s[4].se)
        quan[id].fi = 7*TIME + s[0].se*100 + s[4].se;
    else if(s[2].se==s[3].se && s[3].se==s[4].se && s[0].se==s[1].se)
        quan[id].fi = 7*TIME + s[2].se*100 + s[0].se; // 葫芦 fi = 7
    else if(s[0].se==s[1].se+1 && s[1].se==s[2].se+1 && s[2].se==s[3].se+1 && s[3].se==s[4].se+1)
        quan[id].fi += 5*TIME + s[0].se;
    else if(s[0].se==14 && s[4].se==2 && s[3].se==3 && s[2].se==4 && s[1].se==5){
        quan[id].fi += 5*TIME; //  顺子 fi = 5
        if(s[0].fi[0]==s[1].fi[0] && s[1].fi[0]==s[2].fi[0] && s[2].fi[0]==s[3].fi[0] && s[3].fi[0]==s[4].fi[0]) quan[id].fi = 11*TIME;
    }
    else if(s[0].se==s[1].se && s[1].se==s[2].se)
        quan[id].fi = 4*TIME + s[0].se*10000 + s[3].se*100 + s[4].se;
    else if(s[1].se==s[2].se && s[2].se==s[3].se)
        quan[id].fi = 4*TIME + s[1].se*10000 + s[0].se*100 + s[4].se;
    else if(s[2].se==s[3].se && s[3].se==s[4].se)
        quan[id].fi = 4*TIME + s[2].se*10000 + s[0].se*100 + s[1].se; // 三条 fi = 4
    else if(s[0].se==s[1].se && s[2].se==s[3].se)
        quan[id].fi = 3*TIME + s[0].se*10000 + s[2].se*100 + s[4].se;
    else if(s[0].se==s[1].se && s[3].se==s[4].se)
        quan[id].fi = 3*TIME + s[0].se*10000 + s[3].se*100 + s[2].se;
    else if(s[1].se==s[2].se && s[3].se==s[4].se)
        quan[id].fi = 3*TIME + s[1].se*10000 + s[3].se*100 + s[0].se; // 两对 fi = 3
    else if(s[0].se==s[1].se)
        quan[id].fi = 2*TIME + s[0].se*1000000 + s[2].se*10000 + s[3].se*100 + s[4].se;
    else if(s[1].se==s[2].se)
        quan[id].fi = 2*TIME + s[1].se*1000000 + s[0].se*10000 + s[3].se*100 + s[4].se;
    else if(s[2].se==s[3].se)
        quan[id].fi = 2*TIME + s[2].se*1000000 + s[0].se*10000 + s[1].se*100 + s[4].se;
    else if(s[3].se==s[4].se)
        quan[id].fi = 2*TIME + s[3].se*1000000 + s[0].se*10000 + s[1].se*100 + s[2].se; // 一对 fi = 2
    else if(!quan[id].fi)
        quan[id].fi = 1*TIME + s[0].se*100000000 + s[1].se*1000000 + s[2].se*10000 + s[3].se*100 + s[4].se; // 高牌
}
```

### 5.比较类型最大时的权值并统计

以下 $fi$ 存当前牌型的权值，$se$ 存公共牌为当前情况时这个人可选牌型权值的最大值。

在主函数里体现为：
```
tot++;
if(quan[0].se > quan[1].se) win++;
```

在选牌的函数里体现为：
```
quan[0].se = max(quan[0].fi, quan[0].se);

quan[1].se = max(quan[1].fi, quan[1].se);
```

### 6.计算结果

注意浮点误差。（题目中是 $10^{-6}$ ）

注意数据多测。

---

怕读者无法串联起来，故再贴一个笔者实现极烂的[完整代码](https://www.luogu.com.cn/paste/ibny6aqn)。

完结撒花~~

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
纯模拟，这里提供一种思路。

考虑双重循环枚举未知牌，得到未知牌之后再次五重循环枚举使用的牌，因为题中明确指出要取最优的一种方案，所以记录当前的最优方案，每次枚举后都比较一下，再更新这个最优方案，对手也是如此，之后再把双方的最优方案比较，记录答案。

那么如何比较大小呢，首先将方案序列排序，方便统计，之后判断是哪一种类型的牌型，之后如果是同类型的，那么再把其他内容记录，依次比较。

针对上一段的做法，本人有一个我认为较简单的方法。将每个要比较的内容赋一个权值，权值按照优先级依次递减，同时保证不同的类型之间的大小关系与权值的大小关系所对应，这样将抽象的序列变成了一个数字，之后比较即可。
### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std; 
bool vis[5][14];//表示该牌是否出现 
char c;
struct node{
	int col,num;
}q[15],mine_st[6],your_st[6],st[6],cop[6];
int win,zong;
bool cmp(node x,node y){
	return x.num<y.num or (x.num==y.num and x.col<y.col);
}
//q[1]q[2]自己q[3]q[4]对手q[5]q[6]q[7]已知q[8]q[9]未知
int col_(char x){//将花色字符转化为数字 
	if(x=='S') return 1; 
	if(x=='H') return 2; 
	if(x=='D') return 3; 
	if(x=='C') return 4; 
} 
int num_(char x){//将数字字符转化为数字 
	if(x=='A') return 1; 
	if(x=='K') return 13; 
	if(x=='Q') return 12; 
	if(x=='J') return 11; 
	if(x=='T') return 10; 
	else return x-'0';
} 
void init(){
	for(int i=1;i<=5;i++){
		your_st[i]=mine_st[i]={0,0};	
	}	
}
bool check(node *x){
	for(int i=1;i<=5;i++){
		if(x[i].col!=0 or x[i].num!=0) return 0;
	}
	return 1;
}
bool p1(node *x){
	if(x[1].col!=x[2].col or x[2].col!=x[3].col or x[3].col!=x[4].col or x[4].col!=x[5].col) return 0;
	if(x[1].num==1 and x[2].num==10 and x[3].num==11 and x[4].num==12 and x[5].num==13) return 1;
	return 0;
}
bool p2(node *x){
	if(x[1].col!=x[2].col or x[2].col!=x[3].col or x[3].col!=x[4].col or x[4].col!=x[5].col) return 0;
	if(x[1].num+1==x[2].num and x[2].num+1==x[3].num and x[3].num+1==x[4].num and x[4].num+1==x[5].num) return 1;
	if(x[1].num==1 and x[2].num==10 and x[3].num==11 and x[4].num==12 and x[5].num==13) return 1;
	return 0;
}
bool p3(node *x){
	if(x[1].num==x[2].num and x[2].num==x[3].num and x[3].num==x[4].num) return 1;
	if(x[2].num==x[3].num and x[3].num==x[4].num and x[4].num==x[5].num) return 1;
	return 0;
}
bool p4(node *x){
	if(x[1].num==x[2].num and x[2].num==x[3].num and x[4].num==x[5].num) return 1;
	if(x[3].num==x[4].num and x[4].num==x[5].num and x[1].num==x[2].num) return 1;
	return 0;
}
bool p5(node *x){
	if(x[1].col!=x[2].col or x[2].col!=x[3].col or x[3].col!=x[4].col or x[4].col!=x[5].col) return 0;
	return 1;
}
bool p6(node *x){
	if(x[1].num+1==x[2].num and x[2].num+1==x[3].num and x[3].num+1==x[4].num and x[4].num+1==x[5].num) return 1;
	if(x[1].num==1 and x[2].num==10 and x[3].num==11 and x[4].num==12 and x[5].num==13) return 1;
	return 0;
}
bool p7(node *x){
	if(x[1].num==x[2].num and x[2].num==x[3].num) return 1;
	if(x[2].num==x[3].num and x[3].num==x[4].num) return 1;
	if(x[3].num==x[4].num and x[4].num==x[5].num) return 1;
	return 0;
}
bool p8(node *x){
	if(x[1].num==x[2].num and x[3].num==x[4].num) return 1;
	if(x[1].num==x[2].num and x[4].num==x[5].num) return 1;
	if(x[2].num==x[3].num and x[4].num==x[5].num) return 1;
	return 0;
}
bool p9(node *x){
	if(x[1].num==x[2].num or x[3].num==x[4].num or x[2].num==x[3].num or x[4].num==x[5].num) return 1;
	return 0;
}
bool p10(node *x){
	return 1;
}
int id(node *x){//计算x的权值 
	for(int i=1;i<=5;i++) cop[i]=x[i];
	sort(cop+1,cop+5+1,cmp);
	int y=1e10;
	if(p1(cop)) return y*11;
	else if(p2(cop)){
		if(cop[1].num==1 and cop[2].num==10 and cop[3].num==11 and cop[4].num==12 and cop[5].num==13) return y*10+1e8*14;
		else return y*10+1e8*cop[5].num;
	}
	else if(p3(cop)){
		for(int i=1;i<=5;i++) if(cop[i].num==1) cop[i].num=14;
		sort(cop+1,cop+5+1,cmp);
		if(cop[1].num==cop[2].num and cop[2].num==cop[3].num and cop[3].num==cop[4].num){
			return y*9+1e8*cop[1].num+1e6*cop[5].num;
		}
		else{
			return y*9+1e8*cop[2].num+1e6*cop[1].num;
		}
	}
	else if(p4(cop)){
		for(int i=1;i<=5;i++) if(cop[i].num==1) cop[i].num=14;
		sort(cop+1,cop+5+1,cmp);
		if(cop[1].num==cop[2].num and cop[2].num==cop[3].num){
			return y*8+1e8*cop[1].num+1e6*cop[4].num;
		}
		else{
			return y*8+1e8*cop[3].num+1e6*cop[1].num;
		}
	}
	else if(p5(cop)){
		for(int i=1;i<=5;i++) if(cop[i].num==1) cop[i].num=14;
		sort(cop+1,cop+5+1,cmp);
		return y*7+1e8*cop[5].num+1e6*cop[4].num+1e4*cop[3].num+1e2*cop[2].num+cop[1].num;
	}
	else if(p6(cop)){
		if(cop[1].num==1 and cop[2].num==10 and cop[3].num==11 and cop[4].num==12 and cop[5].num==13) return y*6+1e8*14;
		else return y*6+1e8*cop[5].num;
	}
	else if(p7(cop)){
		for(int i=1;i<=5;i++) if(cop[i].num==1) cop[i].num=14;
		sort(cop+1,cop+5+1,cmp);
		if(cop[1].num==cop[2].num and cop[2].num==cop[3].num){
			return y*5+1e8*cop[1].num+1e6*cop[5].num+1e4*cop[4].num;
		}
		else if(cop[2].num==cop[3].num and cop[3].num==cop[4].num){
			return y*5+1e8*cop[2].num+1e6*cop[5].num+1e4*cop[1].num;
		}
		else return y*5+1e8*cop[3].num+1e6*cop[2].num+1e4*cop[1].num;
	}
	else if(p8(cop)){
		for(int i=1;i<=5;i++) if(cop[i].num==1) cop[i].num=14;
		sort(cop+1,cop+5+1,cmp);
		if(cop[1].num==cop[2].num and cop[3].num==cop[4].num) return y*4+1e8*cop[4].num+1e6*cop[2].num+1e4*cop[5].num;
		if(cop[2].num==cop[3].num and cop[4].num==cop[5].num) return y*4+1e8*cop[4].num+1e6*cop[2].num+1e4*cop[1].num;
		if(cop[1].num==cop[2].num and cop[4].num==cop[5].num) return y*4+1e8*cop[4].num+1e6*cop[2].num+1e4*cop[3].num;
	}
	else if(p9(cop)){
		for(int i=1;i<=5;i++) if(cop[i].num==1) cop[i].num=14;
		sort(cop+1,cop+5+1,cmp);
		if(cop[1].num==cop[2].num) return y*3+1e8*cop[2].num+1e6*cop[5].num+1e4*cop[4].num+1e2*cop[3].num;
		if(cop[2].num==cop[3].num) return y*3+1e8*cop[2].num+1e6*cop[5].num+1e4*cop[4].num+1e2*cop[1].num;
		if(cop[3].num==cop[4].num) return y*3+1e8*cop[4].num+1e6*cop[5].num+1e4*cop[2].num+1e2*cop[1].num;
		if(cop[4].num==cop[5].num) return y*3+1e8*cop[4].num+1e6*cop[3].num+1e4*cop[2].num+1e2*cop[1].num;
	}
	else if(p10(cop)){
		for(int i=1;i<=5;i++) if(cop[i].num==1) cop[i].num=14;
		sort(cop+1,cop+5+1,cmp);
		return y*2+1e8*cop[5].num+1e6*cop[4].num+1e4*cop[3].num+1e2*cop[2].num+cop[1].num;
	}
}
int big(node *x,node *y){//1 x>y 0 x==y -1 x<y
	if(check(x)) return -1;
	if(check(y)) return 1;
	int id_x=id(x);
	int id_y=id(y);
	if(id_x>id_y) return 1;
	if(id_x==id_y) return 0;
	if(id_x<id_y) return -1; 
}
signed main(){	
	while(cin>>c){
		if(c=='#') return 0;
		memset(vis,0,sizeof vis),win=zong=0;
		q[1].col=col_(c);
		cin>>c,q[1].num=num_(c);
		cin>>c,q[2].col=col_(c);
		cin>>c,q[2].num=num_(c);
		cin>>c,q[3].col=col_(c);
		cin>>c,q[3].num=num_(c);
		cin>>c,q[4].col=col_(c);
		cin>>c,q[4].num=num_(c);
		cin>>c,q[5].col=col_(c);
		cin>>c,q[5].num=num_(c);
		cin>>c,q[6].col=col_(c);
		cin>>c,q[6].num=num_(c);
		cin>>c,q[7].col=col_(c);
		cin>>c,q[7].num=num_(c);
		vis[q[1].col][q[1].num]=1; 
		vis[q[2].col][q[2].num]=1; 
		vis[q[3].col][q[3].num]=1; 
		vis[q[4].col][q[4].num]=1; 
		vis[q[5].col][q[5].num]=1; 
		vis[q[6].col][q[6].num]=1; 
		vis[q[7].col][q[7].num]=1; 
		for(int i1=1;i1<=4;i1++){
			for(int i2=1;i2<=13;i2++){
				if(vis[i1][i2]) continue;
				vis[i1][i2]=1;
				q[8].col=i1;
				q[8].num=i2;
				for(int i3=1;i3<=4;i3++){
					for(int i4=1;i4<=13;i4++){
						if(vis[i3][i4]) continue;
						vis[i3][i4]=1;
						q[9].col=i3;
						q[9].num=i4;
						zong++;
						init();			
						for(int a=1;a<=5;a++){
							for(int b=a+1;b<=6;b++){
								for(int c=b+1;c<=7;c++){
									for(int d=c+1;d<=8;d++){
										for(int e=d+1;e<=9;e++){
											if(a==3 or a==4 or b==3 or b==4 or c==3 or c==4 or d==3 or d==4 or e==3 or e==4) continue;
											st[1]=q[a];
											st[2]=q[b];
											st[3]=q[c];
											st[4]=q[d];
											st[5]=q[e];
											if(big(st,mine_st)==1){
												for(int i=1;i<=5;i++){
													mine_st[i]=st[i];
												}
											}
										}
									}
								}
							}
						} 
						for(int a=3;a<=5;a++){
							for(int b=a+1;b<=6;b++){
								for(int c=b+1;c<=7;c++){
									for(int d=c+1;d<=8;d++){
										for(int e=d+1;e<=9;e++){
											st[1]=q[a];
											st[2]=q[b];
											st[3]=q[c];
											st[4]=q[d];
											st[5]=q[e];
											if(big(st,your_st)==1){
												for(int i=1;i<=5;i++){
													your_st[i]=st[i];
												}
											}
										}
									}
								}
							}
						} 
						if(big(mine_st,your_st)==1){
							win++;
						}
						vis[i3][i4]=0;
					}
				}
				vis[i1][i2]=0;
			}
		}
		printf("%.20lf\n",(double)win/zong);
	}
	return 0;
}
```

---

## 作者：Chenaknoip (赞：0)

一道大模拟。

考虑定义结构体存储卡牌，然后枚举两张未知牌，通过排列组合选出对于己方和对方的最优解，接下来对双方进行比较。

本题时间充裕，复杂度不必过于严苛。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct card {
	int c, n;
	/*
	c:
	0 -> S
	1 -> H
	2 -> D
	3 -> C
	n:
	A -> 14 / 1
	K -> 13
	Q -> 12
	J -> 11
	T -> 10
	9-2
	*/
};
map<int, bool> vis;
bool operator == (card &x, card &y) {
	return x.c == y.c && x.n == y.n;
}
card me[2], en[2], pu[9]; // me, enemy, public(last 2 for users)
card a[5] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, b[5] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, c[5] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // compare a and b. a->me, b->enemy; c for the best choice
int s1, s2, s3; // judge kind of card
/*
9 -> huang jia tong hua shun
8 -> tong hua shun
7 -> si tiao
6 -> mam tang hong
5 -> tong hua
4 -> shun zi
3 -> san tiao
2 -> liang dui
1 -> yi dui
0 -> gao pai
*/
bool ok(int i, int j, int k, int l) {
	return !vis[i*20+ j] && !vis[k*20+l] && i * 20 + j != k * 20 + l;
}
bool cmp(card &x, card &y) {
	return (x.n != y.n) ? (x.n > y.n) : (x.c < y.c);
}
bool cmpa() {
	/*
	return value:
	1 -> win
	0 -> lost / draw
	*/
	// diff kind
	if (s1 != s3) return s1 > s3;
	if (s1 == 9) return 0;
	if (s1 == 8) {
		return a[0].n > c[0].n;
	}
	if (s1 == 7) {
		if (a[0].n != c[0].n) return a[0].n > c[0].n;
		return a[4].n > c[4].n;
	}
	if (s1 == 6) {
		if (a[0].n != c[0].n) return a[0].n > c[0].n;
		return a[4].n > c[4].n;
	}
	if (s1 == 5) {
		for (int i = 0; i < 5; i++) {
			if (a[i].n != c[i].n) return a[i].n > c[i].n;
		}
		return 0;
	}
	if (s1 == 4) {
		return a[0].n > c[0].n;
	}
	if (s1 == 3) {
		if (a[0].n != c[0].n) return a[0].n > c[0].n;
		if (a[3].n != c[3].n) return a[3].n > c[3].n;
		return a[4].n > c[4].n;
	}
	if (s1 == 2) {
		if (a[0].n != c[0].n) return a[0].n > c[0].n;
		if (a[3].n != c[3].n) return a[3].n > c[3].n;
		return a[4].n > c[4].n;
	}
	if (s1 == 1) {
		if (a[0].n != c[0].n) return a[0].n > c[0].n;
		for (int i = 2; i < 5; i++) {
			if (a[i].n != c[i].n) return a[i].n > c[i].n;
		}
		return 0;
	}
	for (int i = 0; i < 5; i++) {
		if (a[i].n != c[i].n) return a[i].n > c[i].n;
	}
	return 0; // default
}
bool cmpb() {
	/*
	return value:
	1 -> win
	0 -> lost / draw
	*/
	// diff kind
	if (s2 != s3) return s2 > s3;
	if (s2 == 9) return 0;
	if (s2 == 8) {
		return b[0].n > c[0].n;
	}
	if (s2 == 7) {
		if (b[0].n != c[0].n) return b[0].n > c[0].n;
		return b[4].n > c[4].n;
	}
	if (s2 == 6) {
		if (b[0].n != c[0].n) return b[0].n > c[0].n;
		return b[4].n > c[4].n;
	}
	if (s2 == 5) {
		for (int i = 0; i < 5; i++) {
			if (b[i].n != c[i].n) return b[i].n > c[i].n;
		}
		return 0;
	}
	if (s2 == 4) {
		return b[0].n > c[0].n;
	}
	if (s2 == 3) {
		if (b[0].n != c[0].n) return b[0].n > c[0].n;
		if (b[3].n != c[3].n) return b[3].n > c[3].n;
		return b[4].n > c[4].n;
	}
	if (s2 == 2) {
		if (b[0].n != c[0].n) return b[0].n > c[0].n;
		if (b[3].n != c[3].n) return b[3].n > c[3].n;
		return b[4].n > c[4].n;
	}
	if (s2 == 1) {
		if (b[0].n != c[0].n) return b[0].n > c[0].n;
		for (int i = 2; i < 5; i++) {
			if (b[i].n != c[i].n) return b[i].n > c[i].n;
		}
		return 0;
	}
	for (int i = 0; i < 5; i++) {
		if (b[i].n != c[i].n) return b[i].n > c[i].n;
	}
	return 0; // default
}
bool check() {
	/*
	return value:
	1 -> win
	0 -> lost / draw
	*/
	// diff kind
	if (s1 != s2) return s1 > s2;
	if (s1 == 9) return 0;
	if (s1 == 8) {
		return a[0].n > b[0].n;
	}
	if (s1 == 7) {
		if (a[0].n != b[0].n) return a[0].n > b[0].n;
		return a[4].n > b[4].n;
	}
	if (s1 == 6) {
		if (a[0].n != b[0].n) return a[0].n > b[0].n;
		return a[4].n > b[4].n;
	}
	if (s1 == 5) {
		for (int i = 0; i < 5; i++) {
			if (a[i].n != b[i].n) return a[i].n > b[i].n;
		}
		return 0;
	}
	if (s1 == 4) {
		return a[0].n > b[0].n;
	}
	if (s1 == 3) {
		if (a[0].n != b[0].n) return a[0].n > b[0].n;
		if (a[3].n != b[3].n) return a[3].n > b[3].n;
		return a[4].n > b[4].n;
	}
	if (s1 == 2) {
		if (a[0].n != b[0].n) return a[0].n > b[0].n;
		if (a[3].n != b[3].n) return a[3].n > b[3].n;
		return a[4].n > b[4].n;
	}
	if (s1 == 1) {
		if (a[0].n != b[0].n) return a[0].n > b[0].n;
		for (int i = 2; i < 5; i++) {
			if (a[i].n != b[i].n) return a[i].n > b[i].n;
		}
		return 0;
	}
	for (int i = 0; i < 5; i++) {
		if (a[i].n != b[i].n) return a[i].n > b[i].n;
	}
	return 0; // default
}
void judgec() {
	// (huang jia) tong hua shun
	if (c[0].c == c[1].c && c[1].c == c[2].c && c[2].c == c[3].c && c[3].c == c[4].c) {
		if (c[0].n == 14 && c[1].n == 13 && c[2].n == 12 && c[3].n == 11 && c[4].n == 10) { // AKQJT
			s3 = 9;
			return;
		}
		if (c[0].n == c[1].n + 1 && c[1].n == c[2].n + 1 && c[2].n == c[3].n + 1 && c[3].n == c[4].n + 1) { // shun zi
			s3 = 8;
			return;
		}
		if (c[0].n == 14 && c[1].n == 5 && c[2].n == 4 && c[3].n == 3 && c[4].n == 2) { // A2345
			swap(c[0], c[1]);
			swap(c[1], c[2]);
			swap(c[2], c[3]);
			swap(c[3], c[4]);
			c[4].n = 1;
			s3 = 8;
			return;
		}
	}
	// 4 tiao
	if (c[0].n == c[1].n && c[1].n == c[2].n && c[2].n == c[3].n) {
		s3 = 7;
		return;
	}
	if (c[1].n == c[2].n && c[2].n == c[3].n && c[3].n == c[4].n) {
		swap(c[0], c[4]);
		s3 = 7;
		return;
	}
	// mam tang hong (3 dai 2))
	if (c[0].n == c[1].n && c[1].n == c[2].n && c[3].n == c[4].n) {
		s3 = 6;
		return;
	}
	if (c[0].n == c[1].n && c[2].n == c[3].n && c[3].n == c[4].n) {
		s3 = 6;
		// tiao zheng pai de shun xu
		swap(c[0], c[4]);
		swap(c[1], c[3]);
		return;
	}
	// tong hua
	if (c[0].c == c[1].c && c[1].c == c[2].c && c[2].c == c[3].c && c[3].c == c[4].c) {
		s3 = 5;
		return;
	}
	// shun zi
	if (c[0].n == c[1].n + 1 && c[1].n == c[2].n + 1 && c[2].n == c[3].n + 1 && c[3].n == c[4].n + 1) { // shun zi
		s3 = 4;
		return;
	}
	if (c[0].n == 14 && c[1].n == 5 && c[2].n == 4 && c[3].n == 3 && c[4].n == 2) { // A2345
		s3 = 4;
		c[0].n = 1;
		swap(c[0], c[1]);
		swap(c[1], c[2]);
		swap(c[2], c[3]);
		swap(c[3], c[4]);
		return;
	}
	// 3 tiao
	if (c[0].n == c[1].n && c[1].n == c[2].n) {
		s3 = 3;
		return;
	}
	if (c[1].n == c[2].n && c[2].n == c[3].n) {
		s3 = 3;
		c[3] = c[0];
		c[0] = c[1];
		if (c[3].n < c[4].n) swap(c[3], c[4]);
		return;
	}
	if (c[2].n == c[3].n && c[3].n == c[4].n) {
		s3 = 3;
		swap(c[1], c[2]);
		swap(c[2], c[3]);
		swap(c[3], c[4]);
		swap(c[0], c[1]);
		swap(c[1], c[2]);
		swap(c[2], c[3]);
		return;
	}
	// 2 dui
	if (c[0].n == c[1].n) {
		if (c[2].n == c[3].n) {
			s3 = 2;
			return;
		}
		if (c[3].n == c[4].n) {
			s3 = 2;
			swap(c[2], c[3]);
			swap(c[3], c[4]);
			return;
		}
	}
	if (c[1].n == c[2].n) {
		if (c[3].n == c[4].n) {
			s3 = 2;
			swap(c[0], c[1]);
			swap(c[1], c[2]);
			swap(c[2], c[3]);
			swap(c[3], c[4]);
			return;
		}
	}
	// 1 dui
	if (c[0].n == c[1].n) {
		s3 = 1;
		return;
	}
	if (c[1].n == c[2].n) {
		s3 = 1;
		swap(c[2], c[0]);
		return;
	}
	if (c[2].n == c[3].n) {
		s3 = 1;
		swap(c[0], c[2]);
		swap(c[1], c[3]);
		return;
	}
	if (c[3].n == c[4].n) {
		s3 = 1;
		swap(c[0], c[3]);
		swap(c[1], c[4]);
		swap(c[2], c[3]);
		swap(c[3], c[4]);
		return;
	}
	// gao pai
	s3 = 0;
	return;
}
int main() {
	string s;
	while (cin >> s) {
		if (s == "#") break;
		{
			int num, cd;
			if (s[0] == 'S') cd = 0;
			if (s[0] == 'H') cd = 1;
			if (s[0] == 'D') cd = 2;
			if (s[0] == 'C') cd = 3;
			if (s[1] == 'A') num = 14;
			else if (s[1] == 'T') num = 10;
			else if (s[1] == 'J') num = 11;
			else if (s[1] == 'Q') num = 12;
			else if (s[1] == 'K') num = 13;
			else num = s[1] - '0';
			me[0] = {cd, num};
			cin >> s;
			if (s[0] == 'S') cd = 0;
			if (s[0] == 'H') cd = 1;
			if (s[0] == 'D') cd = 2;
			if (s[0] == 'C') cd = 3;
			if (s[1] == 'A') num = 14;
			else if (s[1] == 'T') num = 10;
			else if (s[1] == 'J') num = 11;
			else if (s[1] == 'Q') num = 12;
			else if (s[1] == 'K') num = 13;
			else num = s[1] - '0';
			me[1] = {cd, num};
			cin >> s;
			if (s[0] == 'S') cd = 0;
			if (s[0] == 'H') cd = 1;
			if (s[0] == 'D') cd = 2;
			if (s[0] == 'C') cd = 3;
			if (s[1] == 'A') num = 14;
			else if (s[1] == 'T') num = 10;
			else if (s[1] == 'J') num = 11;
			else if (s[1] == 'Q') num = 12;
			else if (s[1] == 'K') num = 13;
			else num = s[1] - '0';
			en[0] = {cd, num};
			cin >> s;
			if (s[0] == 'S') cd = 0;
			if (s[0] == 'H') cd = 1;
			if (s[0] == 'D') cd = 2;
			if (s[0] == 'C') cd = 3;
			if (s[1] == 'A') num = 14;
			else if (s[1] == 'T') num = 10;
			else if (s[1] == 'J') num = 11;
			else if (s[1] == 'Q') num = 12;
			else if (s[1] == 'K') num = 13;
			else num = s[1] - '0';
			en[1] = {cd, num};
			cin >> s;
			if (s[0] == 'S') cd = 0;
			if (s[0] == 'H') cd = 1;
			if (s[0] == 'D') cd = 2;
			if (s[0] == 'C') cd = 3;
			if (s[1] == 'A') num = 14;
			else if (s[1] == 'T') num = 10;
			else if (s[1] == 'J') num = 11;
			else if (s[1] == 'Q') num = 12;
			else if (s[1] == 'K') num = 13;
			else num = s[1] - '0';
			pu[0] = {cd, num};
			cin >> s;
			if (s[0] == 'S') cd = 0;
			if (s[0] == 'H') cd = 1;
			if (s[0] == 'D') cd = 2;
			if (s[0] == 'C') cd = 3;
			if (s[1] == 'A') num = 14;
			else if (s[1] == 'T') num = 10;
			else if (s[1] == 'J') num = 11;
			else if (s[1] == 'Q') num = 12;
			else if (s[1] == 'K') num = 13;
			else num = s[1] - '0';
			pu[1] = {cd, num};
			cin >> s;
			if (s[0] == 'S') cd = 0;
			if (s[0] == 'H') cd = 1;
			if (s[0] == 'D') cd = 2;
			if (s[0] == 'C') cd = 3;
			if (s[1] == 'A') num = 14;
			else if (s[1] == 'T') num = 10;
			else if (s[1] == 'J') num = 11;
			else if (s[1] == 'Q') num = 12;
			else if (s[1] == 'K') num = 13;
			else num = s[1] - '0';
			pu[2] = {cd, num};
		} // input
		vis[me[0].c * 20 + me[0].n] = vis[me[1].c * 20 + me[1].n] = vis[en[0].c * 20 + en[0].n] = vis[en[1].c * 20 + en[1].n] = vis[pu[0].c * 20 + pu[0].n] = vis[pu[1].c * 20 + pu[1].n] = vis[pu[2].c * 20 + pu[2].n] = 1;
		int ans = 0, cnt = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 2; j <= 14; j++) {
				for (int k = 0; k < 4; k++) {
					for (int l = 2; l <= 14; l++) {
						pu[3] = {i, j};
						pu[4] = {k, l};
						if (!ok(i, j, k, l)) continue;
						memset(a, 0, sizeof(a));
						memset(b, 0, sizeof(b));
						memset(c, 0, sizeof(c));
						s3 = s1 = s2 = 0;
						card t = {0, 0};
						for (int i = 5; i < 9; i++) pu[i] = t;
						// select card
						for (int m = 0; m < 7; m++) {
							for (int n = m + 1; n < 7; n++) {
								for (int o = n + 1; o < 7; o++) {
									for (int p = o + 1; p < 7; p++) {
										for (int q = p + 1; q < 7; q++) {
											pu[5] = me[0];
											pu[6] = me[1];
											c[0] = pu[m];
											c[1] = pu[n];
											c[2] = pu[o];
											c[3] = pu[p];
											c[4] = pu[q];
											sort(c, c + 5, cmp);
											judgec();
											if (!cmpa()) {
												for (int i = 0; i < 5; i++) a[i] = c[i];
												s1 = s3;
											}
											pu[5] = en[0];
											pu[6] = en[1];
											c[0] = pu[m];
											c[1] = pu[n];
											c[2] = pu[o];
											c[3] = pu[p];
											c[4] = pu[q];
											sort(c, c + 5, cmp);
											judgec();
											if (!cmpb()) {
												for (int i = 0; i < 5; i++) b[i] = c[i];
												s2 = s3;
											}
										}
									}
								}
							}
						}
						// cnt win
						ans += check();
						cnt++;
					}
				}
			}
		}
		double pwin = (double)ans / cnt;
		cout << fixed << setprecision(20) << pwin << endl;
		vis[me[0].c * 20 + me[0].n] = vis[me[1].c * 20 + me[1].n] = vis[en[0].c * 20 + en[0].n] = vis[en[1].c * 20 + en[1].n] = vis[pu[0].c * 20 + pu[0].n] = vis[pu[1].c * 20 + pu[1].n] = vis[pu[2].c * 20 + pu[2].n] = 0;
		//cout << ans << " " << cnt << endl;
	}
	return 0;
}
```

---

