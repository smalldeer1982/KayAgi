# [USACO4.3] 字母游戏 Letter Game

## 题目描述

给定 $3 \sim 7$ 张卡片和不超过 $4 \times 10^4$ 个合法单词，请用卡片拼出（每张卡片只能用一次）一个或多个（即“词组”）合法单词，使得用到的卡片的价值之和最大，并输出所有方案。

卡片的价值取决于卡片上的字母，其对应关系如下：

```plain
[Letter]  a b c d e f g h i j k l m n o p q r s t u v w x y z
[Value]   2 5 4 4 1 6 5 5 1 7 6 3 5 2 3 5 7 2 1 2 4 6 6 7 5 7
```

![](https://cdn.luogu.com.cn/upload/pic/1969.png)

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 4.3。

## 样例 #1

### 输入

```
prmgroa
profile
program
prom
rag
ram
rom
.```

### 输出

```
24
program
prom rag```

# 题解

## 作者：Celebrate (赞：4)

这一道题也没有什么算法了，就是纯靠思维来做的

在输入的字母之中，有很多个都是不行的（或超出范围的），

所以我们只用记录可以用的单词

找完可以用的单词，就用两重for循环找出最大值并且直接

记录，最后输出就可以了，把小写字母a,b,c,d变成1,2,3,4 就是

ss[]-'a'+1

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y;//记录最大值，x记录被选单词的序号，如果y是0，就只有x一个 
}result[5100];int len,maxx=0;
struct node1
{
	char s[11];
	int len,score;//记录单词 
}st[5100];int n;
char ss[31];
const int s[27]={0,2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};//分值 
int flag[31];//flag记录每个字母最多可以出现多少次 
bool pd()//判断这一个是否可以 
{
	int i,k[31];memset(k,0,sizeof(k));
	for(i=1;i<=strlen(ss+1);i++)
	{
		k[ss[i]-'a'+1]++;
		if(k[ss[i]-'a'+1]>flag[ss[i]-'a'+1]) return false;//如果超出范围，就肯定不可以了 
	}
	return true;
}
bool check(int x,int y)//判断两个加起来是否超出范围 
{
	int i,k[31];memset(k,0,sizeof(k));
	for(i=1;i<=st[x].len;i++)
	{
		k[st[x].s[i]-'a'+1]++;
		if(k[st[x].s[i]-'a'+1]>flag[st[x].s[i]-'a'+1]) return false;
	}
	for(i=1;i<=st[y].len;i++)
	{
		k[st[y].s[i]-'a'+1]++;
		if(k[st[y].s[i]-'a'+1]>flag[st[y].s[i]-'a'+1]) return false;
	}
	return true;
}
int main()
{
	int i,j;
	scanf("%s",ss+1);
	for(i=1;i<=strlen(ss+1);i++) flag[ss[i]-'a'+1]++;//记录 
	while(scanf("%s",ss+1)!=EOF)
	{
		if(ss[1]=='.') break;//如果输入到句号，就推出 
		if(pd()==true)//如果这个单词没有超出范围 
		{
			n++;
			st[n].len=strlen(ss+1);
			for(i=1;i<=st[n].len;i++)//把这个单词记录下来 
			{
				st[n].s[i]=ss[i];
				st[n].score=st[n].score+s[ss[i]-'a'+1];//分值 
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		if(st[i].score>maxx)//先找单独一个单词，如果超过分值 
		{
			len=1;//重置并且记录 
			result[1].x=i;
			maxx=st[i].score;
		}
		else if(st[i].score==maxx)//如果等于最大值 
		{
			len++;//增加一个 
			result[len].x=i;
		}
		for(j=i;j<=n;j++)//找后面的（包括自己，因为一个单词可以用两次） 
		{
			if(check(i,j)==true)//如果可以 
			{
				if(st[i].score+st[j].score>maxx)//更新最大值 
				{
					len=1;result[1].x=i;result[1].y=j;
					maxx=st[i].score+st[j].score;
				}
				else if(st[i].score+st[j].score==maxx)
				{
					len++;result[len].x=i;result[len].y=j;
				}
			}
		}
	}
	printf("%d\n",maxx);//直接输出，因为已经按照字典序排好了，没有必要再排一次 
	for(i=1;i<=len;i++)//输出 
	{
		for(j=1;j<=st[result[i].x].len;j++) printf("%c",st[result[i].x].s[j]);
		if(result[i].y>0)
		{
			printf(" ");
			for(j=1;j<=st[result[i].y].len;j++) printf("%c",st[result[i].y].s[j]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：「QQ红包」 (赞：3)

题解 by redbag

这道题虽然没有数据，但是还是可以在usaco上做的。

4w看起来很可怕，但是有很多的情况都可以不要

1.某字母出现次数>读入的串中 该字母的 出现次数

2.出现了 在 读入的串中 未出现的字母

而且usaco很良心，并没有出现4w个数都满足条件的情况

然后就是愉快的枚举+暴力了

```cpp
/*
ID: ylx14271
PROG: lgame
LANG: C++     
*/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
const int v[28]={2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
int in[28];//统计出现次数 
int in1[28];
int in2[28];

char word[40003][10];//存每个单词,下标从1开始 
int lw[40003],n;
int va[40003];//存每个单词的价值 

char s[10];
int ls,i,j;
int ans[40003][2],num,ans1;//ans：下标0开始  
void qm(int x,int y)
{
    if (va[x]+va[y]<ans1) return;
    if (va[x]+va[y]>ans1)//价值更大 
    {
        ans1=va[x]+va[y];//更新 
        num=0;
    }
    num++;//相当于价值和max相等，所以统计 
    ans[num][0]=x;
    ans[num][1]=y; 
}

int main()
{
    freopen("lgame.in","r",stdin);
    scanf("%s",s);
    ls=strlen(s);
    for (i=0;i<ls;i++)
    {
        in[s[i]-'a']++;//统计出现次数 
    }
    freopen("lgame.dict","r",stdin);
    freopen("lgame.out","w",stdout);
    while (scanf("%s",s)!=EOF)
    {
        if (s[0]=='.') break;
        memcpy(in1,in,sizeof(in));
        int ll=strlen(s);
        int flag=0;
        for (i=0;i<ll;i++)//看这个串要不要存  
        {
            in1[s[i]-'a']--;
            if (in1[s[i]-'a']<0)
            {
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
            n++;
            strcpy(word[n],s); 
            lw[n]=strlen(word[n]);
            for (i=0;i<lw[n];i++)
            {
                va[n]+=v[s[i]-'a'];//算他的价值 
            }
        }
    }//对读入的处理
    for (i=1;i<=n;i++)
    {
        qm(i,0);
        memcpy(in1,in,sizeof(in));
        for (j=0;j<lw[i];j++)
        {
            in1[word[i][j]-'a']--;
        }
        for (j=i;j<=n;j++)//j从i开始去重
        {
            int flag=0;
            memcpy(in2,in1,sizeof(in2));
            for (int k=0;k<lw[j];k++)//看i和j两个串拼一起符不符合条件 
            {
                in2[word[j][k]-'a']--;
                if (in2[word[j][k]-'a']<0)
                {
                    flag=1;//标记 
                    break;
                }
            }
            if (flag==0)
            {
                qm(i,j);
            }
        }
    }
    printf("%d\n",ans1);
    for (i=1;i<=num;i++)//输出 
    {
        printf("%s",word[ans[i][0]]);
        if (ans[i][1]!=0) printf(" %s",word[ans[i][1]]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：zhangjianweivv (赞：2)

这道题主要就是信息点太多，导致连自己都容易搞混。

别看它给的字典很大，到了40,000行，但是其实真正能用的很少（这里下面的大佬都详细解说了，我就不赘述了）~~然后就拿一个数组记录一下...~~不对，是拿一堆数组记录一下。具体的我在代码里有讲到。

其实是有很大的坑点的。比如我原本以为找串是要找全部都匹配的单词或词组（也就是把目标单词的每一个字母都用上），但是其实不是的，只要找到最大的就行了。所以不用弄很麻烦的判断也能找到解。

然后接下来就是暴力啦（~~其实就是懒~~）咳咳，好的，贴上代码：
```cpp
/*
ID:zhangji78
LANG:C++
TASK:lgame
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,y;//ans存答案，有的是词，有的是词组，所以定了结构体（两个变量）
}ans[2100];
struct node1
{
	int sss,other[20],le;
	node1()
	{
	//sss表示它是词还是词组
	//le表示和它匹配的有多少个字符串
	//other存的是和它匹配的所有字符串
		sss=-1;le=0;//sss=-1(还没访问到)，sss=1(本身)，sss=0(组合)
		memset(other,0,sizeof(other));
	}
}kk[2100];//kk用来标记第一轮符合要求的串儿
//注意：和某个单词匹配的可能不止一个单词
int maxx,lens[2100];
int aa[27]={0,2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
//强势打表（手动滑稽）
int f[2100][27],len,n,a[2100];
char c[10],st[10],ss[2100][10];
bool pd(int lena)//一个小判断。s用来记录当前st数组中每个字母出现的个数
{
	int s[27];memset(s,0,sizeof(s));
	for(int i=1;i<=lena;i++)
	{
		s[st[i]-'a'+1]++;
		if(s[st[i]-'a'+1]>f[0][st[i]-'a'+1])return false;
	}//将s数组和f[0]比较
    //因为f[0]存的是目标串儿中每个字母出现的个数（下面有讲到）
	return true;
}
bool pp(int x,int y)
{
	for(int i=1;i<=26;i++)
	{//另一个小判断。因为即使不要求位数，但是还是要有个限制的
		if(f[x][i]+f[y][i]>f[0][i])return false;
	}
	return true;
}
int main()
{
	//freopen("lgame.in","r",stdin);
	//freopen("lgame.out","w",stdout);
	scanf("%s",c+1);len=strlen(c+1);//c是目标串儿
	for(int i=1;i<=len;i++)f[0][c[i]-'a'+1]++;
    //f[0]存目标串儿每个字母出现的个数
	//freopen("lgame.dict","r",stdin);
	while(scanf("%s",st+1)!=EOF)
	{
		if(st[1]=='.')break;
		int lena=strlen(st+1);
		if(pd(lena)==true)//只有满足条件的才能储存，大剪枝（手动滑稽）
		{
			n++;lens[n]=lena;
			for(int i=1;i<=lena;i++)
			{
				f[n][st[i]-'a'+1]++;
				ss[n][i]=st[i];
				a[n]+=aa[st[i]-'a'+1];
			}
            //lens[i]表示第i个符合条件的单词的长度
            //f[i]表示第i个符合条件的单词每个字母出现的个数
            //ss[i](char型，我不太习惯用string)存第i个符合条件的单词
            //a[i]表示第i个符合条件的单词的得分
		}
	}
	for(int i=1;i<=n;i++)
	{
		maxx=max(maxx,a[i]);kk[i].sss=1;//如果光是本身就已经很大了
		for(int j=i;j<=n;j++)
		{
			if(lens[i]+lens[j]<=len)//长度不能超过len
			{//去找一轮符合条件的匹配串（当然能匹配上就更好啦）
				if(pp(i,j)==true)
				{
					if(a[i]+a[j]>=maxx)
					{//这里一定是>=maxx，也是一个坑。因为=maxx的也要输出
						maxx=a[i]+a[j];
						kk[i].sss=0;kk[j].sss=0;
						kk[i].other[++kk[i].le]=j;
                        //注意这里，只用把kk标记就行了
                        //不用标记kk[i].other，因为同一个串只找一次就行了
                        //如果把kk[i].other也标记了，可能会出现同一词组输出两次的尴尬情况
					}
				}
			}
		}
	}
	int lena=0;
	for(int i=1;i<=n;i++)
	{//ans去寻找并记录（这里很容易理解，就不多赘述了）
		if(kk[i].sss==1)
		{
			if(a[i]==maxx)ans[++lena].x=i;
		}
		else
		{
			for(int j=1;j<=kk[i].le;j++)
			{
				if(a[i]+a[kk[i].other[j]]==maxx)
				{
					ans[++lena].x=i;
					ans[lena].y=kk[i].other[j];
				}
			}
		}
	}
	printf("%d\n",maxx);
	for(int i=1;i<=lena;i++)
	{//输出
		for(int j=1;j<=lens[ans[i].x];j++)printf("%c",ss[ans[i].x][j]);
		if(ans[i].y>0)
		{
			printf(" ");
			for(int j=1;j<=lens[ans[i].y];j++)printf("%c",ss[ans[i].y][j]);
		}
		printf("\n");
	}
    //有一个小问题：其他dalao都是要排序的，为什么这个代码没排呢？
    //emmm...因为这是小蒟蒻的代码啊...
    //好吧其实是因为输入的时候就是按字典序输入的
    //for的时候也是按照字典序从小到大for的
    //在每次记录的时候，都已经是默认按照字典序保存了，不会出现乱序
    //所以就不需要按照字典序排序啦~
    //谢谢你这么厉害还过来看一个小蒟蒻简陋又暴力的题解（手动滑稽）
	return 0;
}
```

---

## 作者：祥瑞御免 (赞：1)

题解里的代码都好长...于是想贡献一下自己的写法了。

这道题就是一道模拟题，主要的难度在于阅读理解。就是要在字典中挑出若干个单词，其字母分类后的数量不超过文本串中字母的数量，输出其价值最大值以及方案即可

没什么好说的，解释代码里有

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 40010;

int cnt, len, jsq, ans;
int val[N], can[N], tran[30], buc[N][30], tbuc[30];

char text[10], dict[N][10];

void init() {
	tran[0] = 2, tran[1] = 5, tran[2] = 4, tran[3] = 4, tran[4] = 1;
	tran[5] = 6, tran[6] = 5, tran[7] = 5, tran[8] = 1, tran[9] = 7;
	tran[10] = 6, tran[11] = 3, tran[12] = 5, tran[13] = 2, tran[14] = 3;
	tran[15] = 5, tran[16] = 7, tran[17] = 2, tran[18] = 1, tran[19] = 2;
	tran[20] = 4, tran[21] = 6, tran[22] = 6, tran[23] = 7, tran[24] = 5;
	tran[25] = 7;
} //字符的价值暴力赋值

inline int check(int x, int y) {
	for (int i = 0; i < 26; ++i)
		if (buc[x][i] + buc[y][i] > tbuc[i])	return 0;
	return 1;	
} //用来判断两个字符串中的字符数是否超过了文本串

void subtask_1() {
	
	// single word
	for (int i = 1; i <= cnt; ++i) 
		if (check(i, 0))	ans = max(ans, val[i]), can[++jsq] = i;	
	// paired words
	for (int i = 1; i <= jsq; ++i)
		for (int j = i; j <= jsq; ++j)
			if (check(can[i], can[j]))	ans = max(ans, val[can[i]] + val[can[j]]);
	
} //暴力求出最大价值。将可行单词存至can数组中降低复杂度

void subtask_2() {
	for (int i = 1; i <= jsq; ++i) {
		if (val[can[i]] == ans)	printf("%s\n", dict[can[i]] + 1);
		for (int j = i; j <= jsq; ++j)
			if (val[can[i]] + val[can[j]] == ans && check(can[i], can[j]))
				printf("%s %s\n", dict[can[i]] + 1, dict[can[j]] + 1);
	}
		
} //按照字典序输出方案

int main() {
	
	init();
	
	scanf("%s", text + 1);
	while (scanf("%s", dict[++cnt] + 1)) {
		if (dict[cnt][1] == '.')	{
			--cnt;	
			break;
		}
	} //输入
	
	for (int i = 1; i <= cnt; ++i) {
		len = strlen(dict[i] + 1);
		for (int j = 1; j <= len; ++j)	
			buc[i][dict[i][j] - 'a']++, val[i] += tran[dict[i][j] - 'a'];
	} //开两个桶，一个是文本串的，一个是字典中单词的。val数组是单词的价值
	
	len = strlen(text + 1);
	for (int i = 1; i <= len; ++i)	tbuc[text[i] - 'a']++;
	
	subtask_1();
	printf("%d\n", ans);
	subtask_2();
	
	return 0;
}

/*
prmgroa
profile
program
prom
rag
ram
rom
.
*/
```


---

## 作者：feng_chengjie (赞：1)

##此题非常的良心，通过分析我们发现：

1、每个单词的长度是3~7，那么就算是单词对也只能有两个

2、不是所有的词典中的单词都满足要求

于是我们先把所有词典中的合法单词加入候选列表，再两两枚举单词凑成合法的词对并加入，经排序，选出所有的满足最大值的单词及单词对






```cpp
#include <iostream>
#include <cstdio>
#include <cstring> 
#include <algorithm>
#include <map>
#include <set>
using namespace std;
struct point
{
    string w;
    int val;
}word[40010];
string S,dic[40010];
int chart[]={0,2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
map<string,int> list;
set<string> pp;
int cnt=0,nword,maxx,nalp[40010][30];
bool judge1(string);
bool judge2(int,int);
int cal(string);
bool cmp(const point &a,const point &b)
{
    if(a.val!=b.val)
        return a.val>b.val;
    else
        return a.w<b.w;
}
int main()
{
    memset(nalp,0,sizeof(nalp));
    cin>>S;
    for(int i=0;i<S.size();i++)
        nalp[0][S[i]-'a'+1]++;
    while(1)
    {
        string s;
        cin>>s;
        if(s==".")
            break;
        if(judge1(s))//判断是否够凑
        {
            dic[cnt]=s;
            word[cnt].w=s;
            word[cnt].val=cal(s);//计算单词的价值 
        }
    }
    nword=cnt;
    for(int i=1;i<=cnt;i++)
        for(int j=1;j<=cnt;j++)
        {
            string s1,s2;
            s1=dic[i];
            s2=dic[j];
            if(judge2(i,j))
            {
                string ss;
                if(s1<s2)
                    ss=s1+" "+s2;
                else
                    ss=s2+" "+s1;
                if(pp.count(ss)==0)
                {
                    pp.insert(ss);
                    word[++nword].w=ss;
                    word[nword].val=list[s1]+list[s2];                        
                }
            } 
        } 
    sort(word+1,word+1+nword,cmp);
    maxx=word[1].val;
    cout<<maxx<<endl;
    int i=1;
    while(word[i].val==maxx)
    {
        cout<<word[i].w<<endl;
        i++;
    }
    return 0;    
} 
bool judge1(string tt)
{
    int len=tt.size();
    int nn[30]={0};
    for(int i=0;i<len;i++)
    {
        nn[tt[i]-'a'+1]++;
        if(nn[tt[i]-'a'+1]>nalp[0][tt[i]-'a'+1])    
            return 0; 
    }
    cnt++;
    for(int i=1;i<=26;i++)
        nalp[cnt][i]=nn[i];
    return 1;
}
bool judge2(int t1,int t2)
{
    for(int i=1;i<=26;i++)
        if(nalp[t1][i]+nalp[t2][i]>nalp[0][i])
            return 0;
    return 1;
}
int cal(string tmp)
{
    int len=tmp.size();
    int sum=0;
    for(int i=0;i<len;i++)
        if(tmp[i]>='a' && tmp[i]<='z')
            sum+=chart[tmp[i]-'a'+1];
    list[tmp]=sum;
    return list[tmp];
}

```

---

## 作者：姚文涛 (赞：1)

//注意一下，这里所选的最大分值不一定要和输入的字符串完全匹配，只需在字典中找到单个或组合的最大值即可。


//下面我们来考虑算法。对于单个的字符串在读入时可以直接判断。因为所有字符串长度都是3--7之内的，我们很快就会发现——如果组合的话，最多才2个。然而40000^2的效率仍然不可观。仔细看翻译中对输入字符串的描述“这就是收集到字母(就是可以使用的字母)”因此我们可以把字典中的字符串先进行一次判断。设给定字符串为S，字典中某字符串是P，如果P中含有S里不含有的字母，就可以直接踢掉。这样效率就非常可观了。我们在找最大分值的同时，也可以顺带地记录答案。


const rank:array['a'..'z'] of longint=(2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7);


```cpp
var
  temp,map:array['a'..'z'] of longint;
  ans:array[1..5001] of string;
  cnt,max,i,len,j,l,n:longint;
  p:array[1..40001] of string;
  t,s:string;
function check(o:string):longint;
var
  i:longint;
begin
  check:=0;l:=length(o);
  for i:=1 to l do
    begin
      if (temp[o[i]]+1>map[o[i]]) then exit(0);
      temp[o[i]]:=temp[o[i]]+1;
      check:=check+rank[o[i]];
    end;
end;
procedure find_max;
var
  t,j,i:longint;
begin
  for i:=1 to n do
    for j:=i to n do
      begin
        if length(p[i])+length(p[j])>len then continue;
        fillchar(temp,sizeof(temp),0);
        t:=check(p[i]+p[j]);
        if t>max then begin max:=t;cnt:=0;end;
        if t=max then begin cnt:=cnt+1;ans[cnt]:=p[i]+' '+p[j];end;
      end;
end;
procedure scanf;
var
  t:longint;ss:string;
begin
  readln(ss);
  while ss<>'.' do
    begin
      fillchar(temp,sizeof(temp),0);
      t:=check(ss);
      if t>0 then
        begin
          inc(n);
          p[n]:=ss;
          if (t>max) then begin max:=t;cnt:=0;end;
          if (t=max) then begin cnt:=cnt+1;ans[cnt]:=ss;end;
        end;
      readln(ss);
    end;
end;
begin
  readln(s);
  close(input);
  len:=length(s);
  for i:=1 to len do
    inc(map[s[i]]);
  assign(input,'lgame.dict');
  reset(input);
  max:=0;
  scanf;find_max;
  writeln(max);
  for i:=1 to cnt-1 do
    for j:=i+1 to cnt do
      if (ans[i]>ans[j]) then begin t:=ans[i];ans[i]:=ans[j];ans[j]:=t;end;
  for i:=1 to cnt do
    writeln(ans[i]);
end.
```

---

## 作者：eternal (赞：0)

这个题要仔细读，理解题意。起初我理解得不对，以为是输出的每个结果都必须是输入的一个排列，不能多也不能少。这种理解不正确。汗，我一直以为样例居然是错的，其实使用的字典不一样。


这道题正确的理解应该是，在结果的单词或词组构所成的字母中，每个字母出现的频数不大于输入的字符串中每个字母的频数。也就是例如输入是 aaa，字典中有单词 a,aa,aaa,aaaa，其中a,aa,aaa都是符合条件的解，但只有aaa才是要输出的最优解。


理解题意以后编程不难，直接枚举每种可行解，单词可以在O(n)内解决，词组要O(N^2)。但是对于40000个单词但是太多了。可以发现，大多数单词都是用不到的，而所以我们可以在读入字典的时候直接去除非可行解的单词，即该单词有输入字串中未出现的字母，或者在该单词中的字母中，有频数大于输入字串所含该字母频数的（例：输入字串为aabb，该单词为aaa，其中a的频数大于输入字串，必定无法有输入字串构成）。


这样优化可以去掉绝大部分的冗余，使得程序能够在很快的时间内算出结果。


所后别忘了对结果排序，可以把单词当作一个第二个单词为空串的词组，按字典顺序排序即可。

/\*
ID: chenzhu3

PROG: lgame

LANG: C++

\*/












```cpp
#include <iostream>
#include <fstream>
using namespace std;
ifstream fi("lgame.in");
ifstream fd("lgame.dict");
ofstream fo("lgame.out");
typedef struct
{
    char c[7];
    int len;
    int score;
}str;
typedef struct
{
    char c1[7],c2[7];
    int len1,len2;
}Tans;
int uw['z'+1],used['z'+1];
int v['z'+1];
str S[40001];
Tans ans[50];
int N=1,L,acnt;
int Ms=0;
void init()
{
    int i;
    char c;
    bool k;
    while (!fi.eof())
    {
        c=fi.get();
        uw[c]++;
    }
    while (c!='.')
    {
        memset(used,0,sizeof(used));
        L++;
        c=fd.get();
        if (c=='.')
            break;
        k=true;
        while (c==10 || c==13)    c=fd.get();
        S[N].len=0;
        while (c!=10 && c!=13)
        {
            S[N].c[ S[N].len++ ]=c;
            used[c]++;
            if (!uw[c])
                k=false;
            c=fd.get();
        }
        S[N].c[ S[N].len ]=0;
        for (i='a';i<='z';i++)
            if (used[i]>uw[i])
            {
                k=false;
                break;
            }
        if (k)
            N++;
    }
    N--;
    v['q']=v['j']=v['z']=v['x']=7;
    v['w']=v['f']=v['k']=v['v']=6;
    v['y']=v['p']=v['g']=v['h']=v['b']=v['m']=5;
    v['u']=v['d']=v['c']=4;
    v['o']=v['l']=3;
    v['r']=v['t']=v['a']=v['n']=2;
    v['e']=v['i']=v['s']=1;
}
void findans()
{
    int i,k,p;
    for (i=1;i<=N;i++)
    {
        for (k=0;k<=S[i].len-1;k++)
            S[i].score+=v[ S[i].c[k] ];
        if (S[i].score>Ms)
        {
            Ms=S[i].score;
            acnt=1;
            for (p=0;p<=S[i].len-1;p++)
                ans[acnt].c1[p]=S[i].c[p];
            ans[acnt].len1=S[i].len;
            ans[acnt].c1[ ans[acnt].len1 ]=0;
        }
        else if (S[i].score==Ms)
        {
            acnt++;
            for (p=0;p<=S[i].len-1;p++)
                ans[acnt].c1[p]=S[i].c[p];
            ans[acnt].len1=S[i].len;
            ans[acnt].c1[ ans[acnt].len1 ]=0;
        }
    }
}
void findpair()
{
    memset(used,0,sizeof(used));
    int i,j,p;
    bool K;
    int T;
    for (i=1;i<=N-1;i++)
    {
        for (j=i+1;j<=N;j++)
        {
            T=S[i].score+S[j].score;
            for (p=0;p<=S[i].len-1;p++)
                used[S[i].c[p]]++;
            for (p=0;p<=S[j].len-1;p++)
                used[S[j].c[p]]++;
            K=true;
            for (p='a';p<='z';p++)
                if (used[p]>uw[p])
                {
                    K=false;
                    break;
                }
            memset(used,0,sizeof(used));
            if (!K) continue;
            if (T>Ms)
            {
                Ms=T;
                acnt=1;
                for (p=0;p<=S[i].len-1;p++)
                    ans[acnt].c1[p]=S[i].c[p];
                ans[acnt].len1=S[i].len;
                ans[acnt].c1[ ans[acnt].len1 ]=0;
                for (p=0;p<=S[j].len-1;p++)
                    ans[acnt].c2[p]=S[j].c[p];
                ans[acnt].len2=S[j].len;
                ans[acnt].c2[ ans[acnt].len2 ]=0;
            }
            else if (T==Ms)
            {
                acnt++;
                for (p=0;p<=S[i].len-1;p++)
                    ans[acnt].c1[p]=S[i].c[p];
                ans[acnt].len1=S[i].len;
                ans[acnt].c1[ ans[acnt].len1 ]=0;
                for (p=0;p<=S[j].len-1;p++)
                    ans[acnt].c2[p]=S[j].c[p];
                ans[acnt].len2=S[j].len;
                ans[acnt].c2[ ans[acnt].len2 ]=0;
            }
        }
    }
}
void print()
{
    fo << Ms << endl;
    int i,j;
    for (i=1;i<=acnt;i++)
    {
        for (j=0;j<=ans[i].len1-1;j++)
            fo << ans[i].c1[j];
        if (ans[i].len2)
        {
            fo << ' ';
            for (j=0;j<=ans[i].len2-1;j++)
                fo << ans[i].c2[j];
        }
        fo <<endl;
    }
}
inline int cmp(const void *a,const void *b)
{
    int k;
    Tans *A=(Tans *)a,*B=(Tans *)b;
    k=strcmp(A->c1,B->c1);
    if (k!=0) return k;
    k=strcmp(A->c2,B->c2);
    return k;
}
void sortans()
{
    qsort(ans+1,acnt,sizeof(Tans),cmp);
    print();
}
int main()
{
    init();
    findans();
    findpair();
    sortans();
    fi.close();
    fd.close();
    fo.close();
    return 0;
}
```

---

## 作者：cupWolf (赞：0)

## 说明

$O(n^2)$ 的题解主要依赖于数据中输入的很多单词是无效的，但是这种性质并未在题面写明，~~加之此题是一道蓝题，正解不会这么简单~~，因此我认为 $O(n^2)$ 的做法并非此题的正解。

## 思路

首先，注意到 $3 \times 3 > 7$，于是词组最多可能有两个单词。一种朴素的思路是枚举词组的两个单词。

如何优化？我们不难发现：在判断最优性的时候，我们并不需要关心字母具体的排列，`cbac ef` 和 `abcc fe` 二者的价值是一样的。

因此，我们可以维护一个字母多重集到单词的映射，把字母数量相同的单词放到一起判断，优化循环。

## 复杂度分析

由于多重集 $S$ 的子集最多有 $2^{|S|}$ 个，这个算法的时间复杂度是 $O(2^{2|c|} + a \log a)$，  
其中 $|c|$ 是卡片的个数，$a$ 是答案的个数。

后面一项是因为此算法不保证答案有序（毕竟我们都不关心字母的具体排列了），还要对答案排一次序。

不过由于常数问题，在本题的数据下，只优化一重循环的 $O(n \cdot 2^{|c|} + a \log a)$ 的做法与优化两重循环的做法时间相差无几（甚至最优解是只优化一重循环的），在后面我会同时贴出。

## 状态压缩优化

更进一步地，对字符进行离散化，映射到 $0 \sim 7$，此时可以发现字母多重集可以压缩成一个 `unsigned long long`，这样建立映射的常数可以小一些。~~这么小的数据范围不状压可惜了。~~

截至我写这篇题解时，此算法仍是最优解。

## 代码

:::info[优化一重循环]
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned char ui8;
typedef unsigned long long char_multiset;  // 离散化之后的字符多重集可以状压
#define split(cms) ((ui8*)&(cms))

const int maxc=8, maxn=4e4+100;


int varr[26] = {
	2, 5, 4, 4, 1, 6, 5, 5,
	1, 7, 6, 3, 5, 2, 3, 5,
	7, 2, 1, 2, 4, 6, 6, 7, 5, 7
};

int charmap[256];  // 字符离散化
int valmap[maxc];

char limits[maxc];  // 卡片限制
char words[maxn][8];

struct node {
	int value;
	vector<int> idx;
};

unordered_map<char_multiset, node> mp;
pair<int, int> ans[200000];
int maxval = 0, anscnt = 0;


inline int value(char_multiset cms) {
	int ans = 0;
	for (int i=0; i<8; i++) {
		ans += valmap[i] * split(cms)[i];
	}
	return ans;
}

inline char_multiset to_cms(char *s) {
	char_multiset ans=0ll;
	
	for (; *s!=0; s++) {
		if (charmap[*s] == -1) {
			return 0;
		}
		
		split(ans)[charmap[*s]]++;
	}
	
	return ans;
}

inline bool check(char_multiset cms) {
	for (int i=0; i<8; i++) {
		if (split(cms)[i] > limits[i]) {
			return false;
		}
	}
	return true;
}

inline bool check2(char_multiset cms1, char_multiset cms2) {
	for (int i=0; i<8; i++) {
		if (split(cms1)[i] + split(cms2)[i] > limits[i]) {
			return false;
		}
	}
	return true;
}

inline void upd_maxval(int val) {
	if (val > maxval) {
		maxval = val;
		anscnt = 0;
	}
}

inline void add_ans(int i1, int i2) {
	anscnt++;
	ans[anscnt] = {i1, i2};
}


// 调试专用
inline void print(char_multiset cms) {
	putchar('{');
	for (int i=0; i<8; i++) {
		printf("%d%s", split(cms)[i], i==7?"}":", ");
	}
}

// 为了抢最优解写的快读
inline bool read(char *s){
	char c = getchar();
	
	while (c=='\n' || c=='\r') {
		c = getchar();
	}
	
	if (c == '.') {
		return false;
	}
	
	for (; c!='\n'&&c!='\r'; s++) {
		*s = c;
		c = getchar();
	}
	*s = '\0';
	
	return true;
}


int main() {
	char cards[8];
	read(cards);
	
	memset(charmap, -1, sizeof charmap);
	int ccnt=0;
	for (int i=0; cards[i]; i++) {
		char c = cards[i];
		
		if (charmap[c] == -1) {
			charmap[c] = ccnt;
			valmap[ccnt] = varr[c - 'a'];
			ccnt++;
		}
		
		limits[charmap[c]]++;
	}
	
	int i=0;
	while (true) {
		i++;
		if (!read(words[i])) {
			break;
		}
		
		char_multiset cms = to_cms(words[i]);
		if (!cms || !check(cms) {
			// 超出卡片表示范围
			continue;
		}
		
		int val = value(cms);
		if (val >= maxval) {
			upd_maxval(val);
			add_ans(i, 0);
		}
		
		for (auto [cms2, no]: mp) {
			if (check2(cms, cms2) && val+no.value>=maxval) {
				upd_maxval(val + no.value);
				
				for (int j: no.idx) {
					add_ans(j, i);
				}
			}
		}
		
		mp[cms].value = val;
		mp[cms].idx.push_back(i);
	}
	
	sort(ans + 1, ans + 1 + anscnt);  // 这个算法不能保证答案有序
	
	printf("%d\n", maxval);
	for (int i=1; i<=anscnt; i++) {
		printf("%s %s\n", words[ans[i].first], words[ans[i].second]);
		// 尾部空格不会影响测评机判断，因此 ans[i][2]==0 也能工作
	}
	
	return 0;
}
```
:::

:::info[优化两重循环]
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned char ui8;
typedef unsigned long long char_multiset;  // 离散化之后的字符多重集可以状压
#define split(cms) ((ui8*)&(cms))

const int maxc=8, maxn=4e4+100;


int varr[26] = {
	2, 5, 4, 4, 1, 6, 5, 5,
	1, 7, 6, 3, 5, 2, 3, 5,
	7, 2, 1, 2, 4, 6, 6, 7, 5, 7
};

int charmap[256];  // 字符离散化
int valmap[maxc];

char limits[maxc];  // 卡片限制
char words[maxn][8];

struct node {
	int value;
	vector<int> idx;
};

map<char_multiset, node> mp;  // 甚至比 unordered 快（unordered 由于无序，在 i==j 时退出是危险的）
pair<int, int> ans[200000];
int maxval = 0, anscnt = 0;


inline int value(char_multiset cms) {
	int ans = 0;
	for (int i=0; i<8; i++) {
		ans += valmap[i] * split(cms)[i];
	}
	return ans;
}

inline char_multiset to_cms(char *s) {
	char_multiset ans=0ll;
	
	for (; *s!=0; s++) {
		if (charmap[*s] == -1) {
			return 0;
		}
		
		split(ans)[charmap[*s]]++;
	}
	
	return ans;
}

inline bool check(char_multiset cms) {
	for (int i=0; i<8; i++) {
		if (split(cms)[i] > limits[i]) {
			return false;
		}
	}
	return true;
}

inline bool check2(char_multiset cms1, char_multiset cms2) {
	for (int i=0; i<8; i++) {
		if (split(cms1)[i] + split(cms2)[i] > limits[i]) {
			return false;
		}
	}
	return true;
}

inline void upd_maxval(int val) {
	if (val > maxval) {
		maxval = val;
		anscnt = 0;
	}
}

inline void add_ans(int i1, int i2) {
	anscnt++;
	ans[anscnt] = {i1, i2};
}


// 调试专用
inline void print(char_multiset cms) {
	putchar('{');
	for (int i=0; i<8; i++) {
		printf("%d%s", split(cms)[i], i==7?"}":", ");
	}
}

// 为了抢最优解写的快读
inline bool read(char *s){
	char c = getchar();
	
	while (c=='\n' || c=='\r') {
		c = getchar();
	}
	
	if (c == '.') {
		return false;
	}
	
	for (; c!='\n'&&c!='\r'; s++) {
		*s = c;
		c = getchar();
	}
	*s = '\0';
	
	return true;
}


int main() {
	char cards[8];
	read(cards);
	
	memset(charmap, -1, sizeof charmap);
	int ccnt=0;
	for (int i=0; cards[i]; i++) {
		char c = cards[i];
		
		if (charmap[c] == -1) {
			charmap[c] = ccnt;
			valmap[ccnt] = varr[c - 'a'];
			ccnt++;
		}
		
		limits[charmap[c]]++;
	}
	
	int n = 0;
	while (true) {
		n++;
		if (!read(words[n])) {
			break;
		}
		
		char_multiset cms = to_cms(words[n]);
		if (!cms || !check(cms)) {
			// 超出卡片表示范围
			continue;
		}
		
		int val = value(cms);
		
		if (val >= maxval) {
			upd_maxval(val);
			add_ans(n, 0);
		}
		
		if (strlen(words[n]) <= 4) {
			node &no = mp[cms];
			no.value = val;
			no.idx.push_back(n);
		}
	}
	
	for (auto [cms1, no1]: mp) {
		if (check2(cms1, cms1) && no1.value*2>=maxval) {
			upd_maxval(no1.value*2);
			for (int i: no1.idx) {
				for (int j: no1.idx) {
					if (i == j) { break; }
					add_ans(j, i);
				}
			}
		}
		
		for (auto [cms2, no2]: mp) {
			if (cms2 == cms1) {
				break;
			}
			
			if (check2(cms1, cms2) && no1.value+no2.value>=maxval) {
				upd_maxval(no1.value + no2.value);
				
				for (int i: no1.idx) {
					for (int j: no2.idx) {
						if (i < j) {
							add_ans(i, j);
						} else {
							add_ans(j, i);
						}
					}
				}
			}
		}
	}
	
	sort(ans + 1, ans + 1 + anscnt);  // 这个算法不能保证答案有序
	
	printf("%d\n", maxval);
	for (int i=1; i<=anscnt; i++) {
		printf("%s %s\n", words[ans[i].first], words[ans[i].second]);
		// 尾部空格不会影响测评机判断，因此 ans[i][2]==0 也能工作
	}
	
	return 0;
}
```
:::

---

