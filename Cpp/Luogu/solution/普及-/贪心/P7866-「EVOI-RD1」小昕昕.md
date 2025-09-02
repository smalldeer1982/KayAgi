# 「EVOI-RD1」小昕昕

## 题目背景

一副扑克牌共有 $54$ 张牌，除去大小王后有 $52$ 张。在同一副牌中，一张牌只可能出现一次。

一副扑克牌中一共有四种花色：黑桃($\texttt{spade}$)、红桃($\texttt{heart}$)、梅花($\texttt{club}$)、方块($\texttt{diamond}$)。每个花色的牌共有 $13$ 张，分别为 $\texttt{A} \sim \texttt{K}$。

在题目中，以上四种花色分别以 $\texttt{S,H,C,D}$ 表示。

我们约定，任何一张牌，都以 **花色+点数** 表示，并且约定用 $\texttt{T}$ 表示 $\texttt{10}$，如 $\texttt{SA,D5,HT,CQ}$。

## 题目描述

昕昕手上有 **两副无大小王** 的扑克牌，她会从这些扑克牌里取出 $n$ 张牌。

昕昕创造了一个组合为 **“小昕昕”**，它的定义是，任意取出 $3$ 张牌，若这 $3$ 张牌的 **牌点一样** ，且花色有且仅有 **两种** ，则称为一对“小昕昕”。如 $\texttt{H3,S3,S3}$ 是一对“小昕昕”。

当这三张扑克牌组成 **“小昕昕”** 后，昕昕就会把它们从牌堆内拿出，**不可再次使用**。

现在，昕昕想让你帮她数数，这副牌里最多能组成多少对 **“小昕昕”**。

## 说明/提示

**本题采用捆绑测试。**

+ $\texttt{Subtask 1 (10 pts)}$ ：$1 \le n \le 3$。
+ $\texttt{Subtask 2 (20 pts)}$ ：$1 \le n \le 5$。
+ $\texttt{Subtask 3 (30 pts)}$ ：$1 \le n \le 20$。
+ $\texttt{Subtask 4 (10 pts)}$ ：$1 \le n \le 70$。
+ $\texttt{Subtask 5 (30 pts)}$ ：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 104$，保证输入的牌都存在于两副无大小王的扑克牌中。

## 样例 #1

### 输入

```
3
S3
H3
S3```

### 输出

```
1```

## 样例 #2

### 输入

```
7
ST
ST
HT
HT
CT
CT
DT```

### 输出

```
2```

## 样例 #3

### 输入

```
6
DA
HA
D4
C5
DA
D4```

### 输出

```
1```

# 题解

## 作者：昒昕 (赞：13)

更新了数据，卡掉了暴力做法，在此表示歉意。

---

### 做法 1 

**贪心+桶排**，时间复杂度 $\mathcal{O}(n)$

对于一个牌点，一对“小昕昕”是优先把 **牌最少的花色** 配 **牌最多的花色**。

也就是对于某一牌点，优先拿 $1$ 张牌的花色与 $2$ 张牌的花色配对，如果没有 $1$ 张牌的花色，才可以把 $2$ 张牌的花色拆开。

所以就想到了桶排。

```cpp
#include <cstdio>

int poke[6][21];
int ans;

int change_color(char p) {
    switch (p) {
        case 'S': return 1;
        case 'H': return 2;
        case 'C': return 3;
        case 'D': return 4;
    }
}
int change_num(char p) {
    switch (p) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return int(p-'0');
    }
}
int main() {
//  freopen("xinxin.in","r",stdin);
//  freopen("xinxin.out","w",stdout);
    int n;
    char c,num;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf(" %c%c",&c,&num); //空格是为了吃前面的回车
        poke[change_color(c)][change_num(num)]++; //相应的牌个数加1
    }
    for (int i=1;i<=13;i++) //13个牌点
        for (int j=1;j<=4;j++) //4个花色
            for (int k=1;k<=4;k++)
                if (poke[j][i]==2&&poke[k][i]==1&&j!=k) { //正好是1-2的配对
                    poke[j][i]=0;
                    poke[k][i]=0;
                    ans++;
                }

    for (int i=1;i<=13;i++)
        for (int j=1;j<=4;j++)
            for (int k=1;k<=4;k++)
                if (poke[j][i]==2&&poke[k][i]!=0&&j!=k) { //如果这两个花色都是两张，那么只能拆其中一个花色，给另一个花色配
                    poke[j][i]=0;
                    poke[k][i]--;
                    ans++;
                }
    printf("%d\n",ans);
    return 0;
}
```

---

### 做法 2 

**桶排+找规律**，时间复杂度 $\mathcal{O}(n \log n)$

想一想，一共有 $2$ 副无大小王的扑克牌，说明每个花色至多有 $2$ 张牌。

由于不同牌点间**相互不影响**，所以单从一个牌点考虑，**并且无视花色**。

+ 如果该牌点如果共有 $1$ 或 $2$ 张牌，肯定无法组成“小昕昕”。
+ 如果有 $3$ 或 $4$ 张牌，$0$ 对或 $1$ 对“小昕昕”都有可能，所以需要依靠花色判断。
+ 如果有 $5$ 张牌，只有 $2-1-1-1$ 或 $2-2-1-0$ 的情况，最多能配 $1$ 对。
+ 如果有 $6$ 张牌，有 $2-2-2$ 和 $2-2-1-1$ 的情况，都是 $2$ 对。
+ 如果有 $7$ 或 $8$ 张牌，则分别是 $2-2-2-1$ 和 $2-2-2-2$ 的情况，$2$ 对。

---

+ 再来考虑 $3$ 张牌，有 $1-1-1-0$ 和 $2-1-0-0$ 的情况，花色分别是 $3$ 种和 $2$ 种，如果花色有两种，就是 $1$ 对小昕昕。
+ $4$ 张牌也同理，最多配 $1$ 对“小昕昕”。

```cpp
#include <bits/stdc++.h>
using namespace std;

int change_num(char p) {
    switch (p) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return int(p-'0');
    }
}

int n,ans;
set <char> color[14];
int cnt[14]; //存储每个牌点的数量，无视花色

int main() {
//  freopen("xinxin.in","r",stdin);
//  freopen("xinxin.out","w",stdout);
    char a,b;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
    	scanf(" %c%c",&a,&b);
    	int t=change_num(b);
    	cnt[t]++; //该牌点的数量增加
    	color[t].insert(a); //保存花色，以判断3张或4张牌的情况
	}
	for (int i=1;i<=13;i++) {
		if (cnt[i]==5) ans++; //5张1对
		else if (cnt[i]>=6) ans+=2; //6,7,8张2对
		else if (cnt[i]>=3&&cnt[i]<=4&&(int)color[i].size()!=cnt[i]) ans++;
        //如果是3,4张，则看总花色数
        //如果3张牌共有3个不同的花色 或 4张牌共有不同的4个花色，肯定不能组成“小昕昕”
	}
	printf("%d\n",ans);
   return 0;
}
```


---

## 作者：369Pai (赞：5)

由题意得，一张扑克牌只会由两个字母表示。
考虑用 `map<char,map<char,int> >` 记录扑克牌的出现次数，用法如 `m[][]` 其中第一维表示牌的点数，第二维表示牌的花色，这么做可以不进行字母与数字的转化。

逐点数进行统计，由于两副扑克牌中取 $n$ 张，同样的牌最多有 $2$ 张，同一点数的牌最多有 $8$ 张，所以同一点数最多组成 $2$ 对“小昕昕“。对同一点数的牌**张数**进行讨论：

1. 组成 $2$ 对“小昕昕“：牌的张数大于等于 $6$ 张，由于抽屉原理，一定至少会有 $2$ 对花色也相同的两张牌。

2. 组成 $1$ 对“小昕昕”：牌的张数为 $3$ 张到 $5$ 张，并且有两张花色也相同的牌。

3. 牌的张数少于 $3$ 张，不足以组成一对“小昕昕”。

代码（需要 c++11 标准，还是挺短的）：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<map>
using namespace std;
map<char , map<char , int>> m;
int main()
{
	int n , ans = 0;
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		string str;
		cin >> str;
		m[str[1]][str[0]]++;
	}
	for(auto i:m)
	{
		int sum = 0 , cnt2 = 0;
		for(auto j:i.second)//.second 的类型可以看成 map<T1,T2>的 T2 ,如 i.second 就是 map<char,int> 
		{
			sum += j.second;
			if(j.second == 2)cnt2++;
		}
		if(sum >= 6)
		{
			ans += 2;
		}
		else if(sum >= 3 && cnt2)
		{
			ans += 1;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：lichenzhen (赞：4)

## 题目大意

有 $n$ 张扑克牌，求能组成几个由牌点一样且花色有且仅有两种的“小昕昕”。

## 题目解法

这个题目就是一道有点难度的桶思想的题目，需要用一个二维的数组来当桶，还要与贪心思想结合。

解题的过程主要分为两部分，第一部分是将扑克牌的信息存入道桶中，我用了两个函数处理花色和点数。

之后就是循环扫描桶的环节，首先最外层的循环是点数,之后要分为两种情况来处理。

认真看题目描述，发现只有两副牌，所以相同点数和花色的牌最多出现两张。

所以贪心的思想就是：

- 如果其中相同的点数正好有 $2+1$ 个，也就是一种花色是有 $2$ 张，另外一种有 $1$ 张。此时我们将这两种花色对应的桶清零；

- 在排除完前面那种情况以后，还有一种情况，就是这两种花色都有 $2$ 张，此时就要拆开其中一个来凑。此时我们其中一个的桶清零，另外一个减去一。

### 参考代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
char s[3];
int book[15][5],ans;
int check1(char ch){
	if(ch=='A') return 1;
	if(ch=='T') return 10;
	if(ch=='J') return 11;
	if(ch=='Q') return 12;
	if(ch=='K') return 13;
	return ch-'0';
}
int check2(char ch){
	if(ch=='S') return 1;
	if(ch=='H') return 2;
	if(ch=='C') return 3;
	if(ch=='D') return 4;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s+1;
		book[check1(s[2])][check2(s[1])]++;
	}
	for(int i=1;i<=13;i++){
		for(int j=1;j<=4;j++)
			for(int k=1;k<=4;k++)
				if(book[i][j]+book[i][k]==3){
					ans++;
					book[i][j]=0;
					book[i][k]=0;
				}
		for(int j=1;j<=4;j++)
			for(int k=j+1;k<=4;k++)
				if(book[i][j]+book[i][k]>=3){
					ans++;
					if(book[i][j]==2) book[i][j]=0,book[i][k]--;
	                else if(book[i][k]==2) book[i][k]=0,book[i][j]--;
				} 
	}
	cout<<ans;
}
```


---

## 作者：szh_AK_all (赞：2)

[客官慢走](https://www.luogu.com.cn/problem/P7866)

这道题我们要分**两步**来做：第一步，我们需要将所输入的数据按照某种顺序存入数组中；第二步，我们要判断**最多**可以组成多少组小昕昕。
## 第一步
做好这一步无非就是要判断几种情况，下面是这一步的代码（伪代码）。
```c
for(int i=1;i<=n;i++)
    {
        char x,y;
        cin>>x>>y;
        int p,p1;
        if(x=='S')
            p=1;
        else if(x=='H')
            p=2;
        else if(x=='C')
            p=3;
        else
            p=4;
        if(y>='2'&&y<='9')
            p1=y-'0';
        if(y=='A')
            p1=1;
        if(y=='J')
            p1=11;
        if(y=='Q')
            p1=12;
        if(y=='K')
            p1=13;
        if(y=='T')
            p1=10;//虽然这样写有点麻烦，但应该好理解些
        s[p1][p]++;
    }
```
注意，特殊字母都是大写的。我们将数据存入数组内，然后循环枚举，枚举每一个点数可以组成多少组小昕昕。
## 第二步
判断分为两种情况：一、对于某个点数，其中两种花色的数量加起来刚好为 $3$（也就是它们的数量分别为 $1$ 和 $2$）对于这种情况可以直接让计时器加 $1$，并将它们的数量改为 $0$；二、对于某个点数，当循环判断完第一种情况后，若还有某两种花色的数量加起来不小于 $3$（也就是它们的初始数量都为 $2$，或是循环时遗漏的第一种情况），那么我们并不能将它们的数量都改为 $0$，而是把其中一个数量为 $2$ 的改为 $0$，另一个减 $1$ 就行了。
# Code
```c
#include<iostream>
using namespace std;
int s[20][10];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        char x,y;
        cin>>x>>y;
        int p,p1;
        if(x=='S')
            p=1;
        else if(x=='H')
            p=2;
        else if(x=='C')
            p=3;
        else
            p=4;
        if(y>='2'&&y<='9')
            p1=y-'0';
        if(y=='A')
            p1=1;
        if(y=='J')
            p1=11;
        if(y=='Q')
            p1=12;
        if(y=='K')
            p1=13;
        if(y=='T')
            p1=10;//虽然这样写有点麻烦，但应该好理解些
        s[p1][p]++;
    }
    int ans=0;
    for(int i=1;i<=13;i++)
    {
        for(int j=1;j<4;j++)//第一种情况
            for(int k=j+1;k<=4;k++)
            {
                if((s[i][j]+s[i][k])==3)
                {
                    s[i][j]=s[i][k]=0;
                    ans++;
                }
            }
        for(int j=1;j<4;j++)//第二种情况（注意，这层循环可以与第一种情况并列）
            for(int k=j+1;k<=4;k++)
            {
                if((s[i][j]+s[i][k])>=3)
                {
                    if(s[i][j]==2)
                    {
                        s[i][j]=0;
                        s[i][k]--;
                    }
                    else if(s[i][k]==2)
                    {
                        s[i][k]=0;
                        s[i][j]--;
                    }
                    ans++;
                }
            }
    }
    cout<<ans;
    return 0;
}
```



---

## 作者：FanYongchen (赞：2)

这道题，我们统计出每个牌点每个花色的牌的个数。

那么，对于同一个牌点，我们可以从中取两张花色一样的和一张另一个花色的牌。

那怎么取才能最多呢？

我们肯定是取**有牌最少的花色**来作为取一张的，用**有牌最多的花色**来作为取两张的。

就是我们用小的来消耗掉大的。

如果最少的把最多的消耗光了仍有剩余，则继续消耗第二大的。

一轮结束后，在用更新过的最小值重复一遍，直到结束。

当然，最小值为 $0$ 时，是不用进行操作的。

这样就可以得出最多的答案了。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
using namespace std;
#define ms(x,y) memset(x,y,sizeof(x))
#define mc(x,y) memcpy(x,y,sizeof(x))
const int M=1000;
int n;
int cnt[155][5];//每个牌点每个花色的牌的个数
//cnt[i][j]表示牌点为i，花色为j的牌的个数
int main()
{
    clock_t t1=clock();
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//==================================
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        string s;
        cin>>s;
        int f;
        switch(s[0])//把花色转换一下
        {
            case 'S':{f=0;break;}
            case 'H':{f=1;break;}
            case 'C':{f=2;break;}
            case 'D':{f=3;break;}
        }
        cnt[s[1]][f]++;
    }
    int ans=0;
    for(int i=0;i<155;i++)//枚举每个牌点
    {
        while(true)
        {
            sort(cnt[i],cnt[i]+4);//先排序
            int r=ans;
            //记录答案，解释在下面
            int j=0;
            while(cnt[i][j]==0&&j<4) j++;//先过滤掉前面已经为0的
            for(int k=3;k>j&&cnt[i][j]>0;k--)
            {
                if(cnt[i][k]>=cnt[i][j]*2) cnt[i][k]-=cnt[i][j]*2,ans+=cnt[i][j],cnt[i][j]=0;//少的可以全部都组成小昕昕
                else ans+=cnt[i][k]/2,cnt[i][j]-=cnt[i][k]/2,cnt[i][k]%=2;//消耗光了仍有剩余
            }
            if(ans==r) break;
            //当连最少的都不能与其他的组成小昕昕
            //那么之后的也一定不能组成了
            //所以直接跳出，进行下一个牌点的计算即可
        }
    }
    cout<<ans;
//==================================

    cerr<<"Time used:"<<clock()-t1<<"ms"<<"\n";
    return 0;
}
```

---

## 作者：zbk233 (赞：1)

## 解题思路

考虑用桶保存对于每一个点数，每张花色的数量。

之后的难点就是如何判断“小昕昕”的数量了。

因为只有两幅牌，所以相同牌的数量最多也只有 $2$ 张。

我们考虑求出对于每一个点数，四个花色的牌数量为 $1$ 与 $2$ 的花色数。

不难看出此时答案就是 $\min(one,two)$。

但是，这还不够，我们考虑暴力枚举，将若干个花色数量为 $2$ 的牌转化为 $2$ 张数量为 $1$ 的牌。之后再继续判断。

## 代码实现

```cpp
#include<iostream>
using namespace std;
char c1,c2;
int a[200][10],n,ans;
int fuck1(char ch){
	if(ch=='A') return 1;
	if(ch>='2'&&ch<='9') return ch-'0';
	if(ch=='T') return 10;
	if(ch=='J') return 11;
	if(ch=='Q') return 12;
	return 13;
}
int fuck2(char ch){
	if(ch=='S') return 1;
	if(ch=='H') return 2;
	if(ch=='C') return 3;
	return 4;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>c1>>c2;
    	a[fuck1(c2)][fuck2(c1)]++;
	}
	for(int i=1;i<=13;i++){
		int one=0,two=0,sum=0;
		for(int j=1;j<=4;j++){
			if(a[i][j]==1){
				one++;
			}
			if(a[i][j]==2){
				two++;
			}
		}
		for(int i=0;i<=two;i++){
			sum=max(sum,min(two-i,one+i*2));
		}
		ans+=sum;
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：封禁用户 (赞：1)

[题目](https://www.luogu.com.cn/problem/P7866)不难，直接模拟即可。

因为题目只有 2 副扑克牌，所以每种牌最多只有 2 张。

所以当比如点数 J 这种类型的牌有 6 张或以上时，肯定能组成 2 对小昕昕；

而当只有 3 张或者以上时就需要分类讨论了：如果有某种花色的 J 有2张，则肯定能组成 1 对小昕昕，否则无法组成 1 组小昕昕。

代码见下：
```cpp
// Problem: P7866 「EVOI-RD1」小昕昕
// From: Luogu
// Url: https://www.luogu.com.cn/problem/P7866?contestId=49613
// Interactive:false
// MemoryLimit: 128 MB
// TimeLimit: 1000 ms
//
//
// Powered by CP Editor (https://cpeditor.org)
#include <bits/stdc++.h>
using namespace std;
int s[6][16] = {0};//用来统计每张牌的个数
int num, ans = 0;
void input() {//将每张牌统计计入数组
  for (int i = 1; i <= num; i++) {
    string sum;
    cin >> sum;
    if ((sum[0] == 'S' && sum[1] == 'A') || (sum[0] == 'S' && sum[1] == '1'))
      s[1][1]++;                                     //黑桃1
    if (sum[0] == 'S' && sum[1] == '2') s[1][2]++;   //黑桃2
    if (sum[0] == 'S' && sum[1] == '3') s[1][3]++;   //黑桃3
    if (sum[0] == 'S' && sum[1] == '4') s[1][4]++;   //黑桃4
    if (sum[0] == 'S' && sum[1] == '5') s[1][5]++;   //黑桃5
    if (sum[0] == 'S' && sum[1] == '6') s[1][6]++;   //黑桃6
    if (sum[0] == 'S' && sum[1] == '7') s[1][7]++;   //黑桃7
    if (sum[0] == 'S' && sum[1] == '8') s[1][8]++;   //黑桃8
    if (sum[0] == 'S' && sum[1] == '9') s[1][9]++;   //黑桃9
    if (sum[0] == 'S' && sum[1] == 'T') s[1][10]++;  //黑桃10
    if (sum[0] == 'S' && sum[1] == 'J') s[1][11]++;  //黑桃J
    if (sum[0] == 'S' && sum[1] == 'Q') s[1][12]++;  //黑桃Q
    if (sum[0] == 'S' && sum[1] == 'K') s[1][13]++;  //黑桃K
    if ((sum[0] == 'H' && sum[1] == 'A') || (sum[0] == 'H' && sum[1] == '1'))
      s[2][1]++;                                     //红桃1
    if (sum[0] == 'H' && sum[1] == '2') s[2][2]++;   //红桃2
    if (sum[0] == 'H' && sum[1] == '3') s[2][3]++;   //红桃3
    if (sum[0] == 'H' && sum[1] == '4') s[2][4]++;   //红桃4
    if (sum[0] == 'H' && sum[1] == '5') s[2][5]++;   //红桃5
    if (sum[0] == 'H' && sum[1] == '6') s[2][6]++;   //红桃6
    if (sum[0] == 'H' && sum[1] == '7') s[2][7]++;   //红桃7
    if (sum[0] == 'H' && sum[1] == '8') s[2][8]++;   //红桃8
    if (sum[0] == 'H' && sum[1] == '9') s[2][9]++;   //红桃9
    if (sum[0] == 'H' && sum[1] == 'T') s[2][10]++;  //红桃10
    if (sum[0] == 'H' && sum[1] == 'J') s[2][11]++;  //红桃J
    if (sum[0] == 'H' && sum[1] == 'Q') s[2][12]++;  //红桃Q
    if (sum[0] == 'H' && sum[1] == 'K') s[2][13]++;  //红桃K
    if ((sum[0] == 'C' && sum[1] == 'A') || (sum[0] == 'C' && sum[1] == '1'))
      s[3][1]++;                                     //梅花1
    if (sum[0] == 'C' && sum[1] == '2') s[3][2]++;   //梅花2
    if (sum[0] == 'C' && sum[1] == '3') s[3][3]++;   //梅花3
    if (sum[0] == 'C' && sum[1] == '4') s[3][4]++;   //梅花4
    if (sum[0] == 'C' && sum[1] == '5') s[3][5]++;   //梅花5
    if (sum[0] == 'C' && sum[1] == '6') s[3][6]++;   //梅花6
    if (sum[0] == 'C' && sum[1] == '7') s[3][7]++;   //梅花7
    if (sum[0] == 'C' && sum[1] == '8') s[3][8]++;   //梅花8
    if (sum[0] == 'C' && sum[1] == '9') s[3][9]++;   //梅花9
    if (sum[0] == 'C' && sum[1] == 'T') s[3][10]++;  //梅花10
    if (sum[0] == 'C' && sum[1] == 'J') s[3][11]++;  //梅花J
    if (sum[0] == 'C' && sum[1] == 'Q') s[3][12]++;  //梅花Q
    if (sum[0] == 'C' && sum[1] == 'K') s[3][13]++;  //梅花K
    if ((sum[0] == 'D' && sum[1] == 'A') || (sum[0] == 'D' && sum[1] == '1'))
      s[4][1]++;                                     //方块1
    if (sum[0] == 'D' && sum[1] == '2') s[4][2]++;   //方块2
    if (sum[0] == 'D' && sum[1] == '3') s[4][3]++;   //方块3
    if (sum[0] == 'D' && sum[1] == '4') s[4][4]++;   //方块4
    if (sum[0] == 'D' && sum[1] == '5') s[4][5]++;   //方块5
    if (sum[0] == 'D' && sum[1] == '6') s[4][6]++;   //方块6
    if (sum[0] == 'D' && sum[1] == '7') s[4][7]++;   //方块7
    if (sum[0] == 'D' && sum[1] == '8') s[4][8]++;   //方块8
    if (sum[0] == 'D' && sum[1] == '9') s[4][9]++;   //方块9
    if (sum[0] == 'D' && sum[1] == 'T') s[4][10]++;  //方块10
    if (sum[0] == 'D' && sum[1] == 'J') s[4][11]++;  //方块J
    if (sum[0] == 'D' && sum[1] == 'Q') s[4][12]++;  //方块Q
    if (sum[0] == 'D' && sum[1] == 'K') s[4][13]++;  //方块K
  }
}
/*
void test() {
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= 13; j++) {
      cout << s[i][j] << " ";
    }
    cout << "\n";
  }
}
*/
void solve() {
  for (int i = 1; i <= 13; i++) {
    if (s[1][i] + s[2][i] + s[3][i] + s[4][i] >= 6)//该点数的牌不少于6张时肯定能组成 2 对小昕昕
      ans += 2;
    else {
      if (s[1][i] >= 2 && s[2][i] >= 1) {
        s[1][i] -= 2;
        s[2][i] -= 1;
        ans++;
      }
      if (s[1][i] >= 2 && s[3][i] >= 1) {
        s[1][i] -= 2;
        s[3][i] -= 1;
        ans++;
      }
      if (s[1][i] >= 2 && s[4][i] >= 1) {
        s[1][i] -= 2;
        s[4][i] -= 1;
        ans++;
      }
      if (s[2][i] >= 2 && s[3][i] >= 1) {
        s[2][i] -= 2;
        s[3][i] -= 1;
        ans++;
      }
      if (s[2][i] >= 2 && s[4][i] >= 1) {
        s[2][i] -= 2;
        s[4][i] -= 1;
        ans++;
      }
      if (s[3][i] >= 2 && s[4][i] >= 1) {
        s[3][i] -= 2;
        s[4][i] -= 1;
        ans++;
      }
      if (s[1][i] >= 1 && s[2][i] >= 2) {
        s[1][i] -= 1;
        s[2][i] -= 2;
        ans++;
      }
      if (s[1][i] >= 1 && s[3][i] >= 2) {
        s[1][i] -= 1;
        s[3][i] -= 2;
        ans++;
      }
      if (s[1][i] >= 1 && s[4][i] >= 2) {
        s[1][i] -= 1;
        s[4][i] -= 2;
        ans++;
      }
      if (s[2][i] >= 1 && s[3][i] >= 2) {
        s[2][i] -= 1;
        s[3][i] -= 2;
        ans++;
      }
      if (s[2][i] >= 1 && s[4][i] >= 2) {
        s[2][i] -= 1;
        s[4][i] -= 2;
        ans++;
      }
      if (s[3][i] == 1 && s[4][i] == 2) {
        s[3][i] -= 1;
        s[4][i] -= 2;
        ans++;
      }
    }
  }
}
int main() {
  ios::sync_with_stdio(false);//关闭同步流
  cin >> num;
  input();
  solve();
  cout << ans << "\n";
  return 0;
}
```


---

## 作者：zhengzidu (赞：0)

# P7866 「EVOI-RD1」小昕昕
[题目传送门](https://www.luogu.com.cn/problem/P7866)

## 题目背景
给定 $n$ 张牌，任意取出 $3$ 张牌，若这 $3$ 张牌的牌点一样且花色有且仅有两种，则称为一对“小昕昕”，求最多能组成多少对“小昕昕”。

## 题目算法--贪心+模拟
因为读入的是字符，所以要在处理前先把它转成 `int` 型。根据题意模拟一遍。

贪心策略：当两种花色的牌中，一堆花色为 $k$ 的牌数量为 $2$，一堆花色为 $k$ 的牌数量为 $1$ 时优先取出。当扫描完一次后，两种花色的牌中，一堆花色为 $k$ 的牌数量大于 $2$，一堆花色为 $k$ 的牌数量为 $1$ 时优先取出，拆散这套牌。

## 题目代码
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
inline int read(){ 
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
	x=x*10+ch-'0';
	ch=getchar();
}
	return x*f;
}
void write(int x){ 
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
	return;
}
int n;
char a,b;
int card[1145][1145];
long long tot;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		int x,y;
		scanf(" %c",&a);
		scanf("%c",&b);
			if(a=='S') x=1;
			else if(a=='H') x=2;
			else if(a=='C') x=3;
			else if(a=='D') x=4;
			if(b=='A') y=1;
			else if(b=='T') y=10;
			else if(b=='J') y=11;
			else if(b=='Q') y=12;
			else if(b=='K') y=13;
			else y=b-'0';
			card[x][y]++;
	}
	//第一次配对 
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if (i==j) continue;
			for(int k=1;k<=13;k++){
				if(card[i][k]>=2&&card[j][k]==1){
					card[i][k]-=2;
					card[j][k]--;
					tot++;
				} 
			}
		}
	}
	//第二次配对 
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(i==j) continue;
			for(int k=1;k<=13;k++){
				if(card[i][k]>=2&&card[j][k]>0){
					card[i][k]-=2;
					card[j][k]--;
					tot++;
				} 
			}
		}
	} 
	write(tot);
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

## 题目描述

[「EVOI-RD1」小昕昕](https://www.luogu.com.cn/problem/P7866)

## 算法思路

我们可以对同一点数的牌张数进行讨论：

- 如果牌的张数大于等于 $6$ 张，而且有 $2$ 对花色相同，就可以组成两对“小昕昕”。

- 如果牌的张数为 $3$ 到 $5$ 张，而且有两张花色相同的牌，就可以组成一对“小昕昕”。

- 如果牌的张数小于 $3$ 张，那么一定不能组成“小昕昕”。

### 样例讲解

样例是上面第二种情况，所以可以组成一对“小昕昕”。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long
ll n,ans,tmpx,tmpy;
string s;
unordered_map<char,unordered_map<char,ll>> cnt;//我习惯用unordered_map
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);//输入输出优化
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		cnt[s[1]][s[0]]++;//累加 
	}
	for(auto u:cnt)
	{
		tmpx=tmpy=0;
		for(auto i:u.second)
		{
			tmpx+=i.second;
			if(i.second==2)
			{
				tmpy++;
			}
		}
		if(tmpx>=6&&tmpy>=2)
		//如果牌的张数大于等于6张，而且有2对花色相同
		{
			ans+=2;//组成两对"小昕昕" 
		}
		else if(tmpx>=3&&tmpy)
		//牌的张数为3到5张，而且有两张花色相同的牌
		{
			ans++;//组成一对"小昕昕"
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：huangmingyi (赞：0)

#### 思路
一开始以为这题可以用结构体、排序一起来做。代码如下：

```
#include<bits/stdc++.h>
using namespace std;
struct hs{//结构体
	char a,b;
	int c;
}a[109];
int n,sum;//sum 来统计小昕昕的个数

void zuanshuzi(){//所用自己拼
	for(int i=1;i<=n;i++){
		if(a[i].b>='2' && a[i].b<='9'){
			a[i].c=a[i].b-'0';
		}else if(a[i].b=='A'){
			a[i].c=1;
		}else if(a[i].b=='J'){
			a[i].c=11;
		}else if(a[i].b=='Q'){
			a[i].c=12;
		}else if(a[i].b=='K'){
			a[i].c=13;
		}
	}
	return ;
}

int cmp(hs x,hs y){//结构体排序必用
	return x.c>y.c;
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
	}
	zuanshuzi();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		int cnt=0;
		if(a[i+1].a=='S' || a[i].a=='S' || a[i+2].a=='S'){//判断
			cnt++;
		}
		if(a[i+1].a=='H' || a[i].a=='H' || a[i+2].a=='H'){//如上
			cnt++;
		}
		if(a[i+1].a=='C' || a[i].a=='C' || a[i+2].a=='C'){//如上
			cnt++;
		}
		if(a[i+1].a=='D' || a[i].a=='D' || a[i+2].a=='D'){//如上
			cnt++;
		}
		if(a[i+1].c==a[i+2].c && a[i].c==a小昕昕[i+2].c && a[i].c==a[i+1].c && cnt<=2){//判断是否为小昕昕
			sum++;
			i+=3;
		}
	}
	cout<<sum<<endl;
	return 0;
}
```

结果![](https://www.luogu.com.cn/record/125221904)

看了一下题解思路马上明白了错在有些花色有两个一样的先不拆，优先拆一个花色。我这个不管三七二十一按输入顺序来拆的。
#### 真解思路
对于每一个牌点，每一对“小昕昕”都要把牌最少的花色配对 牌最多的花色。也就是说一张牌的，优先选择拿只有 $1$ 张牌的花色与至少 $2$ 张牌的花色配对，如果没有只有 $1$ 张牌的花色的话，才不得不要把至少 $2$ 张牌的花色拆开来进行配对。
代码（无注释）：

```
a#include<bits/stdc++.h>
using namespace std;
int poke[6][21];
int ans;

int change1(char p) {
    switch (p) {
        case 'S': return 1;
        case 'H': return 2;
        case 'C': return 3;
        case 'D': return 4;
    }
}
int change2(char p) {
    switch (p) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return int(p-'0');
    }
}
int main() {
    freopen("xinxin.in","r",stdin);
    freopen("xinxin.out","w",stdout);
    int n;
    char c,num;
    cin>>n;
    for (int i=1;i<=n;i++) {
        cin>>c>>num;
        poke[change1(c)][change2(num)]++;
    }
    for (int i=1;i<=13;i++){
        for (int j=1;j<=4;j++){
            for (int k=1;k<=4;k++){
                if (poke[j][i]==2&&poke[k][i]==1&&j!=k) { 
                    poke[j][i]=0;
                    poke[k][i]=0;
                    ans++;
                }
            }
        }
    }
    for (int i=1;i<=13;i++)
        for (int j=1;j<=4;j++)
            for (int k=1;k<=4;k++)
                if (poke[j][i]==2&&poke[k][i]!=0&&j!=k) {
                    poke[j][i]=0;
                    poke[k][i]--;
                    ans++;
                }
            }
        }
    }
    cout<<ans; 
    return 0;
}
```


---

