# 「SWTR-3」Password

## 题目背景

小 $\mathrm{A}$ 在茂密的森林里找到了一个宝箱。

宝箱设有密码锁，但小 $\mathrm{A}$ 不知道密码。

## 题目描述

宝箱的密码由 $n$ 位数字组成，如果将它们连在一起写，就可以看作是一个长度为 $n$ 的字符串。

小 $\mathrm{A}$ 想通过猜的方式试出密码。对于每一位数字，都会有一个集合 $s_i$，表示小 $\mathrm{A}$ 第 $i$ 位的尝试范围。

同时，小 $\mathrm{A}$ 已经试过了 $k$ 个密码组合 $d_1,d_2,\dots,d_k$，**这些密码不一定符合上文中的“尝试范围”**。

小 $\mathrm{A}$ 想知道他最多还需要尝试多少次才可以试出宝箱的密码，如果永远试不出输出 $\mathrm{-1}$。

## 说明/提示

---

### 样例说明

- 在样例 $1$ 中，小 $\mathrm{A}$ 可能试的密码组合有：`014,015,044,045,094,095,114,115,144,145,194,195` 共 $12$ 个数，其中包含密码，但因为 `145` 已经试过，所以小 $\mathrm{A}$ 最多还需尝试 $11$ 次。

- 在样例 $2$ 中，小 $\mathrm{A}$ 可能试的密码组合有：`13,14,23,24`，共 $4$ 个数，其中没有密码，所以小 $\mathrm{A}$ 永远试不出密码。

---

### 数据范围与约定

**本题使用捆绑测试。**

Subtask 编号 | $n\leq$ | 特殊性质 | 分数
:-: | :-: | :-: | :-:
$1$ | $18$ | 答案为 $-1$ | $7$
$2$ | $1$ | 无 | $13$
$3$ | $6$ | 无 | $24$
$4$ | $18$ | $k=0$ | $21$
$5$ | $18$ | 无 | $35$

对于 $100\%$ 的数据，有 $1\leq n\leq 18$，$0\leq k \leq\min(10^n-1,10^4)$。

保证 $d_i$ 不为密码。

---

对于所有测试点，时间限制 $1\mathrm{s}$，空间限制 $128\mathrm{MB}$。

## 样例 #1

### 输入

```
3 2
094
2 01
3 149
2 45
145
345
```

### 输出

```
11```

## 样例 #2

### 输入

```
2 1
12
2 12
2 34
13
```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 10
907887
9 295064731
6 796350
9 295378410
5 48520
9 745208361
7 8079632
111664
422880
521471
433649
037388
091076
235569
979229
268527
690028
```

### 输出

```
153085```

## 样例 #4

### 输入

```
18 10
869813962161100526
7 1762348
8 13948756
6 542169
8 78314952
6 432601
9 697130845
8 16358709
8 95204367
8 24079563
6 145602
7 6231549
6 157096
8 62534170
5 82390
7 5396702
8 20536491
7 1438692
5 59261
396440170984129947
891187409797339137
626815840963841542
192230179244843846
148170753474901744
142718603216393332
486224779191226121
819116507635433912
879948053659796486
875405657525125039
```

### 输出

```
1468282385203195```

# 题解

## 作者：wpy233 (赞：20)

（前言）

$14:11$，偶打开电脑，看见有 巨佬 已经狂切了$4$题……

蒟蒻我顿时被吓晕了……然后发现比赛时间推前了一个小时……

## 正文开始

作为一场`unRating`比赛的$T1$，这道题目真的是印证了比赛描述中的那段话：
```
比赛良心！没有毒瘤模拟题！没有毒瘤数据结构题！
尤！其！是！没有毒瘤的数学推公式题！
无论你是小学六年级还是高中生，都有足够的数学功底 A 掉前 4 题！
```
*****

### 题意简述


给你一个密码，每个字符位置上都有$v_i$种选择。

而且，现在有一些组合是已经尝试过的（不必再尝试一遍，同一种组合只会试一次），问还要多少次才能试出密码。

### 题目分析

让我们对 『题意简述』 里的话来逐句翻译。

*****

给你一个密码，每个字符位置上都有$v_i$种选择。

**即：一共要尝试$v_1 v_2 v_3 ... v_n$次。**

为什么呢？因为你可以是**第一次尝试成功，第二次尝试成功，第三次尝试成功……第$v_1 v_2 v_3 ... v_n$次尝试成功。**由于题目中是“最少”多少次，所以你必须把你自己看得**非常倒霉**→_→（虽然这种情况出现的可能性很小）

*****

而且，现在有一些组合是已经尝试过的（不必再尝试一遍，同一种组合只会试一次），

**即：若$d$字符串上的第$i$位都是第$i$位的$v_i$种选择之一，我们就可以$ans--$（因为每种选择互不相同）**

```
举个例子：
现在密码有2位。
第一位的可能性有：0123
第二位的可能性有：2345
即：ans=4*4=16.
而：给出的有2种尝试：
12
36
第一种：第一位1在可能的尝试中出现了，第二位2在可能的尝试中也出现了，所以ans--，ans变为15.
第二种：第一位3在可能的尝试中出现了，第二位6在可能的尝试中没有出现。所以ans不变。ans仍为15.
所以最终答案是15.
```
*****

### 代码实现

**对于答案不是$-1$的情况：**

我们可以将每个字符可能出现的情况都存下来。每输入一个$d_i$就将$d_i$的每一位都判断一遍。如果每一位都在给定的尝试范围以内就$ans--$。最后输出。

**对于答案是$-1$的情况：**

边输入边判断一遍。如果每一位给定的尝试范围中都没有给定的密码的那一位，输出$-1$然后`return 0`即可。

**注意$ans$的范围**

一开始我以为每一位都是$1$~$9$中的任意一个，每位只有$9$种可能。这样算，答案最大为

$9^{18}=150,094,635,296,999,121<9,223,372,036,854,775,807$

然后发现，每一位都可以取$0$~$9$中共$10$个数……

然后`long long`还没爆？~~QAQ？~~

所以窝为什么要开`unsigned long long`？？？

~~脑抽现场~~

### 吐槽

`样例强？！`

一开始我在代码中把`true`和`false`写反了……

结果还是跑过了四个样例？？？你们确定这样例强度够高？？？~~能查出低级错误？？？~~

### AC代码~~放心抄~~

```
#include <bits/stdc++.h>//I love 万能头
using namespace std;
int n,k;
int a[19];
bool b[19][10];//定义
unsigned long long ans=1;//貌似只要long long……
int main()
{
	cin>>n>>k;//输入
	string mima;
	cin>>mima;//密码
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//输入第i位可能的情况
		bool flag=false;//定义标记变量
		for(int j=1;j<=a[i];j++)
		{
			char t;
			cin>>t;//输入第i位的第j种可能
			if(t==mima[i-1]) flag=true;//如果这种情况与密码的第i位相同就标记成可能
			b[i][t-48]=true;//标记第i位第j种可能尝试
		}
		if(!flag)//没有？？？
		{
			cout<<-1<<endl;
			return 0;//直 接 歇 菜
		}
		ans*=a[i];//排列组合
	}
	string p;
	for(int i=1;i<=k;i++)//判断尝试的密码是否符合要求
	{
		cin>>p;//输入第i个尝试的字符串
		bool flag=true;//定义标记变量
		for(int j=0;j<n;j++)
			if(!b[j+1][p[j]-48])//第j+1位没有在给定的尝试中出现过？！
			{
				flag=false;
				break;//歇 菜 + 1
			}
		if(flag) ans--;//是尝试的组合之一，答案-1
	}
	cout<<ans<<endl;//输出
	return 0;//完结撒花
}
```
提交……

Waiting……

Judging……

Accepted 100分

~~欧 耶~~

---

## 作者：荷叶下 (赞：2)

### 题意分析
##### 1.给出一个字符串
##### 2.从给出的范围中枚举
##### 3.给出几个字符串,找出与枚举的字符串相同的
##### 找出几个枚举次数减几
##### 4.输出枚举次数或-1
### 代码实现及注释
##### *不开long long见祖宗*
```cpp
#include <bits/stdc++.h>
#define P password
typedef long long ll ; //相当于#define ll long long
using namespace std ;
int n , k ;
ll sum = 1 ; //不开long long见祖宗
int num[2020] ;
bool vis[2020][2020] ;
string P ; 
int main()
{
    cin >> n >> k ;
    cin >> P ;
    P = " " + P ; //让字符串从下标为1开始存 更方便¿¿¿
    for(int i = 1 ; i <= n ; ++i)
    {
        bool flag = false ;
        cin >> num[i] ;
        for(int j = 1 ; j <= num[i] ; ++j)
        {
            char x ;
            cin >> x ;
            if(x == P[i])
                flag = true ;
            vis[i][x - '0'] = true ; //x在第i位这个数出现过
        }
        if(!flag) //如果没找到
        {
            cout << -1 ;
            return 0 ;
        }
        sum *= num[i] ;//sum为枚举的总次数
    }
    for(int i = 1 ; i <= k ; ++i)
    {
        string s ;
        bool flag = true ;
        cin >> s ; 
        s = " " + s ; //让字符串从下标为1开始存,更容易理解?
        for(int j = 1 ; j <= n ; ++j)
            if(!vis[j][s[j] - '0']) //如果没有出现过这位的数字
                flag = false ;
        if(flag)
            --sum ;
    }
    cout << sum ;
    return 0 ;
}
``` 

---

## 作者：Crab_Dave (赞：2)

模拟好题

~~明明你就是来水题解的~~

详见代码：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;

#define int long long//因为总方案数需要相乘，所以开long long
int n,k,x[20],can,ans=1;
char a[20],ty[20][20],tr[20];//a为密码，ty为每一位能够尝试的密码集合，tr为特判的密码

signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);//cin加速
	cin>>n>>k;
	cin>>a+1;
	for(register int i=1;i<=n;i++)
	{
		cin>>x[i];ans*=x[i];//先统计不特判的方案数
		for(register int j=1;j<=x[i];j++)
		{
			cin>>ty[i][j];
			if(ty[i][j]==a[i])can++;//该位能否输入密码所需的那位
		}
	}
	for(register int i=1;i<=k;i++)
	{
		cin>>tr+1;
		if(strcmp(tr+1,a+1)==0){puts("0");return 0;}//直接试到密码则输出0
		int fl=0;
		for(register int j=1;j<=n;j++)
		{
			for(register int l=1;l<=x[j];l++)
			{
				if(ty[j][l]==tr[j])fl++;//判断该位是不是本来就可以试的
			}
		}
		if(fl==n)ans--;//如果在可试集合内，就少试一次
	}
	if(can<n)puts("-1");//如果刚才没有试出并且密码不在可试集合内则-1
	else cout<<ans<<'\n';//输出
	return 0;
}
```
资瓷一下叭qwq

---

## 作者：翼德天尊 (赞：2)

一道很不错的模拟题……

[题目传送门](https://www.luogu.com.cn/problem/P5855) [博客食用更佳哦](https://www.luogu.com.cn/blog/5y2d1n/solution-p5855)

**言归正传……下面就开始我们本道题的题解吧！**

------------
### STEP 1 审题&&整理条件

1.给出密码；

2.给出每一位尝试的范围；

3.给出已经尝试的密码；

4.输出（还有几次密码没试||-1）


------------
### STEP 2 思路概述

- **如何储存数据**

密码用字符串储存，每一位的密码范围用结构体（自愿）分别储存长度和密码

- **如何判断无解（-1）**

当密码的任何一位不包含在尝试范围内时，无解，应该输出-1

- **如何判断答案**

设置$unsigned$ $long$ $long$变量$ans$储存，初始输入时用组合的方式算出全部可能；

然后判断尝试密码是否每一位都在范围内，如果是的话$ans$减去1即可


------------
### STEP 3 AC代码实现及完整注释
```c
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,k;//如题
unsigned long long ans=1;。//答案
string m;//真正密码
bool ma[20][10];//每一位的每一个数字是否是密码
struct node{
	int l;//长度
	string k;//每一位的范围
}kn[19];//每一位的结构体
int main(){
    scanf("%d %d",&n,&k);
    cin>>m;//输入
    for (int i=0;i<n;i++){
    	cin>>kn[i].l>>kn[i].k;
    	ans*=kn[i].l;//先组合答案
    	for (int j=0;j<kn[i].l;j++){
    		ma[i][kn[i].k[j]-'0']=1;
		}//标记
	}
	for (int i=0;i<n;i++){//挨个判断密码的每一位
		if (ma[i][m[i]-'0']==0){//只要有一位不在尝试范围内
			printf("-1\n");
			return 0;//输出-1
		}
	}
	while (k--){//判断你每一个尝试的密码
		bool f=0;//打标记的变量
		string c;//暂存尝试密码
		cin>>c;
		for (int i=0;i<n;i++){//判断每一位
			if (ma[i][c[i]-'0']==0){有一位不在尝试范围内就标记
				f=1;
				break;	
			} 
		}
		if (f==0) ans--;//没打过标记就将答案-1
	}
	cout<<ans<<endl;//输出
    return 0;//好习惯++
}
```


------------
### STEP 4 完结撒花！

本次题解就这么愉快的结束啦！如果还有没弄明白的地方，评论区随时等着你！我会第一时间回复哒！

如果全部明白了，就点个赞记录一下你的成长吧！




---

## 作者：Alex_Wei (赞：2)

$\color{orange}\mathrm{This\ is\ Sweet\ Round\ 03.}$

[$\color{orange}\mathrm{Link:T1\ Password}$](https://www.luogu.com.cn/problem/P5855)

作为一场比赛的 $\mathrm{T1}$，自然不会很难。

基础模拟。

---

先判断是否能试到密码，如果不行，输出 $-1$。

然后将所有集合 $s_i$ 的大小相乘，得到最多可能试多少种密码。

最后对所有密码组合 $d_i$，判断是否为可能试到的密码，如果可能，则将最终答案减去 $1$。

时间复杂度：$\mathcal O(nk)$。

期望得分：$100\%$。

---

$\mathrm{std:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll ans=1,n,k,v[20];
string a,s[20],d;
bool check(string pas){//判断字符串是否在尝试范围内
	for(int i=0;i<n;i++){
		int legal=0;
		for(int j=0;j<v[i];j++)
			if(s[i][j]==pas[i])
				legal=1;
		if(!legal)return false; 
	}
	return true;
}
int main(){
	cin>>n>>k>>a;
	for(int i=0;i<n;i++){
		cin>>v[i]>>s[i];
		ans*=v[i];
	}
	if(!check(a)){//如果密码不在尝试范围内，输出 -1
		puts("-1");
		exit(0);
	}
	for(int i=0;i<k;i++){
		cin>>d;
		ans-=check(d);//相当于 if(check(d))ans--;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：CQ_Bab (赞：1)

# 思路

这道题其实就是一道非常简单的题目，我们可以用正难则反的思想去解决它。我们先将所有的可能枚举出来，再去减去猜测中符合条件的次数便能得到答案，我们可以在中途用 $flag$ 来表示在第 $i$ 位的猜测中是否有正确答案。

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int num;
long long ans=1; // 一定要开 long long
bool vis[1010][1010];
string s;
char c;
signed main(){
	cin>>n>>k;
	cin>>s;
	for(int i=0;i<n;i++){
		cin>>num;
		bool flag=false;
		for(int j=1;j<=num;j++){
			cin>>c;
			if(s[i]==c) {
				flag=true;
			}
			vis[i][c-'0']=1; // 说明这一位猜过了这一个数 
		}
		if(!flag) {
			puts("-1"); //判无解 
			return 0;
		}
		ans*=num;
	}
	while(k--){
		string x;
		cin>>x;
		bool f=true;
		for(int i=0;i<n;i++){
			if(!vis[i][x[i]-'0']) f=0; //若在猜的答案中只要有一位没有在可猜测范围中出现过那就是等于没用 
		} 
		if(f) ans--; // 可排除一次 
	}
	cout<<ans; // 输出答案 
	return false; // 结束罪恶的一生 
}

```

---

## 作者：HikariVVIP (赞：1)

[原题链接](https://www.luogu.com.cn/problem/P5855)  
~~蒟蒻第一次写题解，有问题请各位巨佬指出，谢谢！~~

------------
## 题意简述
给定一个字符串和字符串的每一位的范围 $v_i$ 和一些已经枚举过的字符串（意思就是不用再尝试这些组合），输出**最多**还要枚举的次数 $ans$。  

## 思路
- 由于要输出**最多**的尝试次数，我们必须把每一种可能的密码都试一遍。具体来说，就是 $ans=\prod_{i=1}^{k}v_k$。  
- 如果给定范围内根本不包含密码，那么我们可以直接输出 $-1$。  
- 如果可以试出密码，就应将那些已经试过的且在范围内的密码排除，也就是 $ans--$。  

## 代码实现
纯模拟。输入每一位的范围时直接判断密码的这一位是否属于给定范围，如果不属于，直接输出 $-1$ 然后 `return 0`。在判断已尝试过的字符串时，直接 `find()`。  
#### 贴上代码 
```cpp
/********************
*designer:HikariVVIP*
********************/
#include<bits/stdc++.h>
using namespace std;
string pw,guess[20], trys[10005];// pw是要找的密码，guess[20]是每一位的范围，trys[10005]是已经试过的密码 
unsigned long long n,k,ans=1,test[20];// n，k含义同题中所述，ans是答案，test是每一位范围的长度 
int main()
	{
		cin>>n>>k;
		cin>>pw;
		for (int i=0;i<n;i++)
			{
				cin>>test[i]>>guess[i];// cin方便输入 
				ans*=test[i];// 一边输入一边计算 
				if (guess[i].find(pw[i])==string::npos)// string::npos是find()函数没有找到时的返回值 
					{
						cout<<-1;
						return 0;// 如果在范围内没有找到真正密码的第i位，那么肯定试不出来，直接返回 
					}
			}
		for (int i=0;i<k;i++)
			{
				bool flag=1;// flag标记是否已经枚举过 
				cin>>trys[i];
				for (int j=0;j<n;j++)
					{
						if (guess[j].find(trys[i][j])==string::npos)// 如果没找到就代表没有被枚举 
							{
								flag=0;
								break;
							}
					}
				ans-=flag; //小技巧，false=0,true=1 
			}
		cout<<ans;
		return 0;
	}
```
时间复杂度 $\mathcal{O}(n^2k)$ ~~能过就行~~。

---

## 作者：james1BadCreeper (赞：1)

对```james1```这种傻子非常友好的签到题。    
直接模拟即可，大致思路为：先计算出总共的可能，再减去已经试过的。

初始化：
```cpp
	for(register int i=1;i<=n;i++)
	{
		ans*=read();//ans初始化为1，乘上每个位数的可能便是最终的可能数
		cin>>z;//z为string类，也可以换位字符数组加速代码
		for(register int j=0;j<z.length();j++)
			f[i][z[j]-'0']=1;//第i个字符串有第j个数，为判输出-1用
	}
```

判定试过的：
```cpp
	for(register int i=1;i<=k;i++)
	{
		flag=1;//先默认可能
		cin>>z;
		for(register int j=0;j<z.length();j++)
			if(f[j+1][z[j]-'0']==0)//如果有不在尝试范围内的
			{
				flag=0;//不可能
				break;
			}
		if(flag) sum++;//真正要减去的
	}
```

求解输出：
```cpp
	for(register int i=0;i<ANS.length();i++)
		if(f[i+1][ANS[i]-'0']==0)//不在尝试范围内
		{
		    puts("-1");
        	return 0;
		}
	print(ans-sum,'\0');
```

完整代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#pragma GCC optimize(3,"Ofast")
#define LL long long

//个人码风习惯，为增加rp
namespace The_Future_Diary
{
	using namespace std;
	inline int read(void)
	{
		register int x=0,c=getchar();
		while(!isdigit(c)) c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return x;
	}
	int buf[30];
	inline void print(LL x,char k)
	{
		if(x<0) putchar('-'),x=-x;
		register int tot=0;
		if(x==0) buf[++tot]=0;
		while(x)
		{
			buf[++tot]=x%10;
			x/=10;
		}
		for(register int i=tot;i>=1;i--)
			putchar(buf[i]+'0');
		putchar(k);
	}
}

using namespace The_Future_Diary;

string ANS;
string z;

int f[20][10];

int main(void)
{
    register int sum=0;
    register LL ans=1;
    register int n,k;
    register int flag;
	n=read(),k=read();
	cin>>ANS;
	for(register int i=1;i<=n;i++)
	{
		ans*=read();
		cin>>z;
		for(register int j=0;j<z.length();j++)
			f[i][z[j]-'0']=1;
	}
    //好像调换一下求解顺序能加速?
	for(register int i=1;i<=k;i++)
	{
		flag=1;
		cin>>z;
		for(register int j=0;j<z.length();j++)
			if(f[j+1][z[j]-'0']==0)
			{
				flag=0;
				break;
			}
		if(flag) sum++;
	}
	for(register int i=0;i<ANS.length();i++)
		if(f[i+1][ANS[i]-'0']==0)
		{
		    puts("-1");
        	return 0;
		}
	print(ans-sum,'\0');
    return 0;
}
```

---

## 作者：allqpsi (赞：0)

### 这是一道大水题！
首先我们可以用循环算出密码是否包含在集合里面。

如果不包含在里面，就是不可能的。
 
然后用累乘算出用集合里的数能有多少个结果，再减去已经试过的数。

接着，我们查看每个试过的数，如果不包含在集合里面，就把多减的加回来。

最后，输出就行了。 
#### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m,num[19];
long long ans=1;
string s,a;
bool vis[19][10];
int main(){
	cin>>n>>k>>s;
	for(int i=1;i<=n;i++){
		cin>>num[i];
		bool isit=false;
		for(int j=1;j<=num[i];j++){
			char ch;
			cin>>ch;
			if(ch==s[i-1]){
				isit=true;
				//如果密码的第i个字符包含在里面isit=true 
			}
			vis[i][ch-'0']=true;
		}
		if(!isit){//如果密码的第i个字符不包含在里面输出-1 
			cout<<-1;
			return 0;
		}
		ans*=num[i];
		//累乘ans 
	}
	for(int i=1;i<=k;i++){
		cin>>a;
		ans--;
		//已经试了的就减去 
		bool isit=true;
		for(int j=0;j<n;j++){
			if(!vis[j+1][a[j]-'0']){
				//不包含在合集里面的加回来 
				ans++;
				break;
			}
		}
	}
	cout<<ans;
}
```


---

## 作者：Create_Random (赞：0)

模拟签到题

蒟蒻思路：

先把所有可能密码统计一次

然后验证每个已输入密码

(逐位验证每位是否出现即可）

最后判断已输入密码每位是否全部匹配

(如匹配$ans--$即可)

~~请自动忽略本蒟蒻的计数方式~~

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long ans=1;
bool tmp[20];
string s;
char c[20][20];
string s1[10010];
int a[20];
bool cnt,cnt1;
int main()
{
	scanf("%d%d",&n,&k);
	cin>>s;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		for(int j=1;j<=a[i];j++)
		{
			cin>>c[i][j];
			if(c[i][j]==s[i-1])
			{
				cnt1=1;
			}
		}
		if(cnt1==0)//如果可尝试区间没有密码
        			//就直接输出-1
		{
			printf("-1");
			return 0;
		}
		cnt1=0;
		ans=ans*a[i];
	}
	for(int i=1;i<=k;i++)
	{
		cin>>s1[i];
		for(int j=0;j<n;j++)
		{
			for(int q=1;q<=a[j+1];q++)
			{
				if(s1[i][j]==c[j+1][q])//判断第j位是否存在
				{
					tmp[j+1]=1;
					break;
				}
			}
		}
		for(int j=1;j<=n;j++)//判断是否每位全部匹配
		{
			if(tmp[j]==1)
			{
				cnt=1;
			}
			else
			{
				cnt=0;
				break;
			}
		}
		if(cnt)//如果每位全部匹配
        		//ans--即可
		{
			ans--;
		}
		memset(tmp,0,sizeof(tmp));
		cnt=0;
	}
	cout<<ans;
	return 0;
}
```


---

