# [USACO5.5] 贰五语言 Two Five

## 题目描述

有一种奇怪的语言叫做“贰五语言”。它的每个单词都由 `A` 至 `Y` 这 $25$ 个字母各一个组成。但是，并不是任何一种排列都是一个合法的贰五语言单词。贰五语言的单词必须满足这样一个条件：把它的 $25$ 个字母排成一个 $5\times 5$ 的矩阵，它的每一行和每一列都必须是递增的。比如单词 `ACEPTBDHQUFJMRWGKNSXILOVY`，它排成的矩阵如下所示：

```plain
ACEPT
BDHQU
FJMRW
GKNSX
ILOVY
```

因为它的每行每列都是递增的，所以它是一个合法的单词。而单词 `YXWVUTSRQPONMLKJIHGFEDCBA` 则显然不合法。由于单词太长存储不便，需要给每一个单词编一个码。编码方法如下：从左到右，再从上到下，可以由一个矩阵的得到一个单词，再把单词按照字典顺序排序。比如，单词 `ABCDEFGHIJKLMNOPQRSTUVWXY` 的编码为 $1$，而单词 `ABCDEFGHIJKLMNOPQRSUTVWXY` 的编码为 $2$。

现在，你需要编一个程序，完成单词与编码间的转换。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 5.5。

## 样例 #1

### 输入

```
N
2```

### 输出

```
ABCDEFGHIJKLMNOPQRSUTVWXY```

## 样例 #2

### 输入

```
W 
ABCDEFGHIJKLMNOPQRSUTVWXY```

### 输出

```
2```

# 题解

## 作者：zyzzyzzyzzyz (赞：15)

[此处食用更佳](https://www.cnblogs.com/Zenyz/p/10311267.html)

---
# [USACO5.5]贰五语言Two Five

--------

一道记忆化搜索题

## 一.题面

[题目](https://www.luogu.org/problemnew/show/P2750)

定义一类行列均单调递增的$5\times5$矩阵,将其展开后所形成的字符串按字典序编号.

题目要求实现编号与字符串的相互转换

## 二.解题步骤

### 1.求限制条件下的合法矩阵的数量

​	先不管字符串与编号的相互转换;

​	给你一些限定条件(形如$(x,y)$处只能填某字符),让你求满足条件的合法矩阵数


#### (1).暴搜

​	有两种思路,一种是**按顺序**搜每一个格子放哪一个字母,另一种是**按顺序**搜每一个字母放哪一个格子

​	复杂度是$O(25!)$,过不了

​	在这里要特别注意第二种思路,记忆化也是在此基础上进行

#### (2).记忆化

​	在上面提到的第二种思路进行优化.

​	既然是按照字母顺序依次放到格子里,那么会不会有一些~~美妙的~~性质呢?

​	其实是有的,如下图,可有以下性质:

		 a.已经填进去的数必在一个联通块内.

​		显然应如此,否则中间的空肯定填不进更大的字母

         b.联通块的轮廓线应是连续下降的折线

​		如图,蓝块是已经填好的块

​		假设绿块是我现在要填字母的块,如果填进去后,其上的黄块必定将无字母可填(**因为填字母是按顺序填的!**)

![](https://cdn.luogu.com.cn/upload/pic/49501.png )



		c.合法的联通块内具体的字母顺序不影响剩下的字母填入

​		因为以后将要填入的字母必定比现在所有已经填入的字母大,所以相互之间的*"影响"*是一致的

​	综上所述,我们可以使用记忆化搜索(主要是由于性质c,性质a,b主要是方便设dp状态)

​	设记忆化数组$f[a][b][c][d][e]$ 表示第1,2,3,4,5行分别填了a,b,c,d,e个字母的情况下的可能合法矩阵数量,

这样就求出来限制条件下的合法矩阵的数量.

### 2.实现编号与字符串的相互转换	

​	(ps:可以借鉴一下排列的生成算法,感觉本质上差不多QAQ)

​	即通过大家所说的逼近法来实现,

​	现在有一个合法矩阵对应的字符串$P=p_0p_1p_2...p_{22}p_{23}p_{24}$,那么它的前面还有多少个满足条件的字符串呢?

​	编号小于$P$ 的合法矩阵的字符串集合就很明确了,首先将前缀为$k_0(0<k_0<p_0)$的串加上,再加上$k_0k_1(0<k_0<p_0,0<k_1<p_1)$,以此类推,加上$k_0...k_i(0<k_j<p_j)$为前缀的字符串即可.

​	再结合我们已经可以较快地求出一定限制条件下的合法矩阵的数量

​	这题就到此终结了.

## 三.AC代码

```cpp
/*
  此题要点:
  1.要按字母的顺序来搜
* 2.可以记忆化,用数组f[][][][][]来实现 * 
  3.有值的f数组的下标a,b,c,d,e应该递减
  4.最后用逼近法来完成任务
*/
#include<bits/stdc++.h>
#define il inline 
#define R register int
#define ll long long
#define gc getchar
using namespace std;
il int rd()
{
    R x=0,flag=1;
	char ch=0;
    while((ch>'9'||ch<'0')&&ch!='-')ch=gc();
	if(ch=='-')flag=-1,ch=gc();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=gc();
    return x*flag;
}

int S[26],ans;

inline bool check(int letter,int pos)
{
	return (!S[pos])||(letter==S[pos]);
}

int f[6][6][6][6][6];
bool ok[30];
int dfs(int a,int b,int c,int d,int e,int letter)
{
	if(letter>25) return 1;
	if(f[a][b][c][d][e]) return f[a][b][c][d][e];
	int cnt=0;
	if(a<5 && check(letter,a+1)) {cnt+=dfs(a+1,b,c,d,e,letter+1);}
	if(b<a && check(letter,b+6)) {cnt+=dfs(a,b+1,c,d,e,letter+1);}
	if(c<b && check(letter,c+11)) {cnt+=dfs(a,b,c+1,d,e,letter+1);}
	if(d<c && check(letter,d+16)) {cnt+=dfs(a,b,c,d+1,e,letter+1);}
	if(e<d && check(letter,e+21)) {cnt+=dfs(a,b,c,d,e+1,letter+1);}
	return f[a][b][c][d][e]=cnt;
}
void task1(int num)
{
	for(R i=1;i<=25;i++)
	{
		for(S[i]=1;;S[i]++)
		{
			if(ok[S[i]])continue;
			ok[S[i]]=1;
			memset(f,0,sizeof(f));//记得清零
			int tmp=dfs(0,0,0,0,0,1);
			if(ans+tmp>=num) break;
			ans+=tmp;
			ok[S[i]]=0;
		}
	}
	for(R i=1;i<=25;i++) cout<<char(S[i]+'A'-1);
}

void task2()
{
	string s;
	cin>>s;
	ans=0;
	for(R i=0;i<25;i++)
	{
		for(S[i+1]=1;S[i+1]<=s[i]-'A';S[i+1]++)
		{
			if(ok[S[i+1]])continue;
			ok[S[i+1]]=1;
			memset(f,0,sizeof(f));
			ans+=dfs(0,0,0,0,0,1);
			ok[S[i+1]]=0;
		}
	}
	cout<<ans+1<<endl;
}

int main ()
{
	freopen("twofive.in","r",stdin);
	freopen("twofive.out","w",stdout);
	char opt;
	cin>>opt;
	if(opt=='N')task1(rd());
	else task2();
	//dfs(0,0,0,0,0,1);
	//cout<<f[0][0][0][0][0]<<endl;
    return 0;
}

```



​	



​	

​

---

## 作者：ergeda (赞：9)

发现只有采用记忆化：

记忆化可以用dp[a][b][c][d][e]表示第一行选a个，第二行。。。这样可以大力减少搜索时间

具体思想：逼近法：

先看编号转字符串，枚举字符串开头（即一行一行地填字符矩阵），比如说“AB”开头的字符串有多少个？如果大于要求的编号的话，那么自然答案字符串的开头就是“AB”了。这个思想十分容易理解。字符串转编号，类似地！如果这个字符串是“AC~~~~~”，我们先加上"AB~~~~"的字符串个数，然后一直逼近，直至相同。(看了些网上的）

```cpp
    #include<cmath>  
    #include<cstring>  
    #include<cstdio>  
    #include<cstdlib>  
    #include<iostream>  
    #include<algorithm>  
    #define For(i,a,b) for(i=a;i<=b;++i)  
    #define rep(i,a,b) for(i=a;i>=b;--i)  
    using namespace std;  
    int dp[6][6][6][6][6];  
    char s[10010];  
    char st[2];  
    bool pd(int h,int now){  
        return (!s[h] || s[h]==now+'A');//如果当前这一位没有限制或者满足限制  
    }  
    int dfs(int a,int b,int c,int d,int e,int now){//now是现在搜到了哪一个字母  
        if(now==25)return 1;  
        int res = dp[a][b][c][d][e];  
        if(res)return res;  
        if(a<5 && pd(a,now)){res+=dfs(a+1,b,c,d,e,now+1);}//  
        if(b<a && pd(b+5,now)){res+=dfs(a,b+1,c,d,e,now+1);}//b<a是因为只有这时候b位置的上方才填了数  
       if(c<b && pd(c+10,now)){res+=dfs(a,b,c+1,d,e,now+1);}  
        if(d<c && pd(d+15,now)){res+=dfs(a,b,c,d+1,e,now+1);}  
        if(e<d && pd(e+20,now)){res+=dfs(a,b,c,d,e+1,now+1);}  
        return dp[a][b][c][d][e]=res;//记忆化  
    }  
    char sss[1010];  
    int main(){  
        int i,j,n;  
        scanf("%s",st);  
        if(st[0] == 'N'){  
            scanf("%d",&n);  
            For(i, 0, 24){  
                for(s[i]='A' ; ;++s[i]){//枚举第i位选什么数字  
                    memset(dp,0,sizeof(dp));  
                    int tmp = dfs(0,0,0,0,0,0);  
                    if(tmp >= n)break;//若当前枚举的串方案已超过n，则当前这一位不能选当前枚举的字母，只能慢慢逼近  
                    n-=tmp;  
                }  
            }  
            printf("%s\n",s);  
        }  
        else{  
            int ans=0;  
            scanf("%s",sss);  
            For(i,0,24){  
                for(s[i]='A';s[i]<sss[i];s[i]++){  
                    memset(dp,0,sizeof(dp));  
                    int tmp = dfs(0,0,0,0,0,0);  
                    ans+=tmp;  
                }  
            }  
            printf("%d\n",ans+1);  
        }  
        return 0;  
}
```

---

## 作者：Jason_Yvan (赞：4)

深搜dfs + dp + 逼近

dp[a][b][c][d][e] 表示第一行选a个，第二行选b个......（大力减少搜索时间）

把一串字符串变成5 × 5的矩阵，就像题目所说


主要思想：

比如搜字符串“ABD.....”时会有字符串“ABC.....”要在前面，那么字符串“ABD.....”之前的方案一定有在字符串“ABC.....”之前的所有方案，所有我们就可以不断加上这些小的字符串的方案，不断逼近到所求的方案


详情见代码：（内有详细解释）

/*************************************************************************

    > Author: wzw-cnyali
    > Created Time: 2017/5/25 19:23:03
************************************************************************/



















```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define EREP(i, a) for(register int i = (be[a]); i != -1; i = nxt[i])
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template <class T>
T read(T sum = 0, T fg = 0)
{
    char c = getchar();
    while(c < '0' || c > '9') { fg |= c == '-'; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return fg ? -sum : sum;
}
const int inf = 0x3f3f3f3f;
const int Size = 100000;
const int maxn = 100000;
const int maxm = 100000;
char S[Size];
char str[Size];
int dp[6][6][6][6][6];
bool check(int x, int now)
{
    return (!S[x] || S[x] == now + 'A'); //即该位置是否有限制，或者说必须选 now + 'A' 这个字母
}
int dfs(int a, int b, int c, int d, int e, int now)
{
    if(now == 25) return 1;
    int ret = dp[a][b][c][d][e]; //记忆化
    if(ret) return ret; //有值就返回
    if(a < 5 && check(a, now)) ret += dfs(a + 1, b, c, d, e, now + 1); //加上字符串小的数量
    if(b < a && check(b + 5, now)) ret += dfs(a, b + 1, c, d, e, now + 1); //必须前面要有a个字母才行
    if(c < b && check(c + 10, now)) ret += dfs(a, b, c + 1, d, e, now + 1);
    if(d < c && check(d + 15, now)) ret += dfs(a, b, c, d + 1, e, now + 1);
    if(e < d && check(e + 20, now)) ret += dfs(a, b, c, d, e + 1, now + 1);
    return dp[a][b][c][d][e] = ret; //记忆化存入
}
void work1(int n)
{
    REP(i, 0, 24) //枚举每一个位置
    {
        for(S[i] = 'A'; ; ++S[i]) //枚举该位置上应该选什么字母
        {
            mem(dp, 0);
            int ret = dfs(0, 0, 0, 0, 0, 0);
            if(ret >= n) break; //如果大于等于了就说明这个位置必须选什么字符，然后不断逼近
            n -= ret; //减去该个字符在这个位置的方案
        }
    }
    printf("%s\n", S);
}
void work2()
{
    int ans = 0;
    REP(i, 0, 24)
    {
        for(S[i] = 'A'; S[i] < str[i]; ++S[i]) //在前面的方案不能大于当前字符串
        {
            mem(dp, 0);
            int ret = dfs(0, 0, 0, 0, 0, 0);
            ans += ret; //加上这个方案的值
        }
    }
    printf("%d\n", ans + 1);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    char ch;
    cin >> ch;
    if(ch == 'N')
    {
        int n = read<int>();
        work1(n);
    }
    else if(ch == 'W')
    {
        scanf("%s", str);
        work2();
    }
    return 0;
}

```

---

## 作者：Betrayer_of_love (赞：2)

### 思路

发现当表格填到某个地方后，它一定是呈现出一条逐行递减的轮廓线的。

因此，我们设 $f_{a,b,c,d,e}$ 表示第 $1$ 行填了 $a$ 个……第 $5$ 行填了 $e$ 个的方案数。

则只有 $5 \ge a \ge b \ge c \ge d \ge e \ge 0$ 的状态才是合法的。

用记忆化搜索实现。之后对于每一位确定应该填什么即可。最多跑 $25^7$ 次，但其实远远跑不到。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int f[6][6][6][6][6],n;
char tp[2],s[100],t[100];
bool che(char x,int y){
	return (!x)||x=='A'+y;
}
int dfs(int a,int b,int c,int d,int e){
	if(a+b+c+d+e==25)return 1;
	int &ret=f[a][b][c][d][e];
	if(ret)return ret;
	if(a<5&&che(s[a],a+b+c+d+e))ret+=dfs(a+1,b,c,d,e);
	if(b<a&&che(s[b+5],a+b+c+d+e))ret+=dfs(a,b+1,c,d,e);
	if(c<b&&che(s[c+10],a+b+c+d+e))ret+=dfs(a,b,c+1,d,e);
	if(d<c&&che(s[d+15],a+b+c+d+e))ret+=dfs(a,b,c,d+1,e);
	if(e<d&&che(s[e+20],a+b+c+d+e))ret+=dfs(a,b,c,d,e+1);
	return ret;
}
bool used[100];
int main(){
	scanf("%s",tp);
	if(tp[0]=='N'){
		scanf("%d",&n);
		int sum=0;
		for(int i=0;i<25;i++)for(s[i]='A';s[i]<='Z';s[i]++){
			if(used[s[i]])continue;
			used[s[i]]=true;
			memset(f,0,sizeof(f));
			int tmp=dfs(0,0,0,0,0);
			if(sum+tmp>=n)break;
			sum+=tmp;
			used[s[i]]=false;
		}
		printf("%s\n",s);
	}else{
		scanf("%s",t);
		int res=0;
		for(int i=0;i<25;i++)for(s[i]='A';s[i]<t[i];s[i]++){
			memset(f,0,sizeof(f));
			res+=dfs(0,0,0,0,0); 
		}
		printf("%d\n",res+1);
	}
	return 0;
}

```

**完结撒花，谢谢！！！**

---

## 作者：hahaha1215 (赞：2)

思路：

试图找规律 无果  

所以就搜索啦 （在做之前就知道是一道搜索题qwq）
 
从小到达枚举字母来填方格时

对于每一行 左边的必须比右边先填（保证从左至右递增）

对于每一列 上面的必须比下面先填（保证从上至下递增）

So dfs(a,b,c,d,e,now) a表示第一行已经填了几个 b,c,d,e 同推 now表示现在要填第几个字母了（1表示A etc.）

带上记忆化搜索

那么就是f[a][b][c][d][e]表示第一行填了a个,第二行填b个,第三行填c个,第四行填d个,第5行填e个的满足题意的总方案数

现在我们具体来看两个问题：

1.给定序列求编号

就是求字典序比它小的合法序列个数再加1（加上它自己）

枚举第1-25位上的数的字母 每一位都不能超过题目给定序列对应位置上的字母 （不能等于！）

举个栗子：

我们要知道以BE开头的合法序列个数 那么搜第一位为A的序列列数

然后搜第一二位为BE的合法序列数 而不是搜第一位为B的合法序列数

然后把搜索到的方案数都加起来 输出答案记得加上1

 
2.给定编号求序列

同从小到大枚举第1-25位上的数字

假设 我们求第90个序列  现在枚举第二位（第一位必为A） 第二位为B时 有方案80种 ；为C时 有方案30种 

那么要求的第90个序列的第二位一定为 C （方案总数刚好大于90）   

以此类推 一位一位地确定下去
    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
int f[6][6][6][6][6],map[30],ans;
bool ck(int a,int b) {return (!map[a])||(map[a]==b);}
int dfs(int a,int b,int c,int d,int e,int now)
{
  if(now==26) return 1;
  int &tmp=f[a-1][b-1][c-1][d-1][e-1];
  if(tmp) return tmp;
  if(a<=5 && ck(a,now)) tmp+=dfs(a+1,b,c,d,e,now+1);
  if(b<a && ck(b+5,now)) tmp+=dfs(a,b+1,c,d,e,now+1);
  if(c<b && ck(c+10,now)) tmp+=dfs(a,b,c+1,d,e,now+1);
  if(d<c && ck(d+15,now)) tmp+=dfs(a,b,c,d+1,e,now+1);
  if(e<d && ck(e+20,now)) tmp+=dfs(a,b,c,d,e+1,now+1);
  return tmp;
}
int main()
{
  char tp;scanf("%c",&tp);
  if(tp=='W') {
    string s;cin>>s;
    for(register int i=1;i<=25;i++)
      for(map[i]=1;map[i]<s[i-1]-'A'+1;map[i]++) {
    memset(f,0,sizeof(f));
    ans+=dfs(1,1,1,1,1,1);
      }
    printf("%d",ans+1);
  }
  else {
    int n;scanf("%d",&n);
    for(register int i=1;i<=25;i++)
      for(map[i]=1;map[i]<25;map[i]++) {
      memset(f,0,sizeof(f));
      int tmp=dfs(1,1,1,1,1,1);
      if(tmp>=n) break ;
      n-=tmp;
    }
    for(register int i=1;i<=25;i++) printf("%c",map[i]-1+'A');
  }
  return 0;
}


```

---

## 作者：Celebrate (赞：2)

这是一道类似  [USACO3.2]Stringsobits【01串】的题

我们只需要查找方案数+逼近，不断的逼近正确答案，最后找

到正确答案

i，j从小到大分别枚举行和列，然后查找这个字符的方案数，

不断的逼近，时间大约是

## O（int_max）

当然，我们需要加优化，把暴力搜索改为记忆化搜索

建立一个数组f[a][b][c][d][e]，

表示第一行**确定**a个数，第二行**确定**b个数。。。。。的所有**方案数**（25个格子）

初始化就是f[5][5][5][5][5]=1，因为全部确定就只有一种方案

这，就是记忆化所需要的数组

这道题不是有两种情况吗？

一开始打一个按照前面所说的双重循环

（1）把数字改字符

枚举25个字符，然后放在队列里面，并且查找方案数

如果方案数刚好多于编码，就说明这个位置需要放这个字符

为什么？

因为如果是前一个，那么方案数会不够；如果是后一个方案

数会超过所要找的；这一个方案刚好包含了所要找的单词，

所以总的方案数肯定会大于等于所要找的编码.

这里有一个细节，就是说如果一次没有找到，就要把方案数

减去这样放的方案数，那是因为需要找的编码肯定在它的后

面，而查找无法直接找到前面的方案数

这样说可能有点儿乱，就请多读几遍

（2）把字符改数字

统计初始化0

每个位置枚举这个位置前面的所有字符（不包括当前字

符），不断地增加查找到的方案数，和前面的大同小异，最

后输出的时候要+1，因为前面有k个，那么这个数就是k+1

这样做再加上记忆化搜索，时间大约是

## O(25^3),评测0ms

代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int f[6][6][6][6][6],flag,len[5],t,bk,maxx[5],maxy[5];
char ss[2],a[5][5];
bool v[25];
int dfs(int a,int b,int c,int d,int e,int k)//k表示当前搜到第k个字符 
{
    int &ans=f[a][b][c][d][e]; 
    if(ans!=0) return ans;//记忆化搜索 
    if(v[k]==false) return dfs(a,b,c,d,e,k+1);//如果已经找过了 
    if(a<5 && k>maxx[0] && k>maxy[a]) ans+=dfs(a+1,b,c,d,e,k+1);//能搜索的前提是这个位置的上方和左边都有数 
    if(b<a && k>maxx[1] && k>maxy[b]) ans+=dfs(a,b+1,c,d,e,k+1);//并且满足条件
    if(c<b && k>maxx[2] && k>maxy[c]) ans+=dfs(a,b,c+1,d,e,k+1);
    if(d<c && k>maxx[3] && k>maxy[d]) ans+=dfs(a,b,c,d+1,e,k+1);
    if(e<d && k>maxx[4] && k>maxy[e]) ans+=dfs(a,b,c,d,e+1,k+1);
    return ans;
}
int main()
{
    int i,j,k;
    scanf("%s\n",ss);
    if(ss[0]=='N') scanf("%d",&flag);
    else
    {
        for(i=0;i<5;i++)
            for(j=0;j<5;j++)
                scanf("%c",&a[i][j]);
        bk=1;
    }
    memset(v,true,sizeof(v));
    memset(maxx,-1,sizeof(maxx));//表示行的最大值 
    memset(maxy,-1,sizeof(maxy));//表示列的最大值 
    for(i=0;i<5;i++)
    {
        //len[i]=0;
        for(j=0;j<5;j++)
        {
            len[i]++;//多放一个数 
    		t=max(max(maxx[i],maxy[j])+1,0);
            if(bk==0)
            {
                for(k=t;k<25;k++)//枚举所有对的数，如果不喜欢这样，可以改为for(k=0;k<25;k++) 
                {
                    if(v[k]==true)//如果没有用过这个数 
                    {
                        memset(f,0,sizeof(f));
                        f[5][5][5][5][5]=1;
                        v[k]=false;//设置为找过 
                        maxx[i]=maxy[j]=k;
                        int tmp=dfs(len[0],len[1],len[2],len[3],len[4],0);
                        if(flag<=tmp)
                        {
                            a[i][j]='A'+k;
                            break;
                        }
                        else
                        {
                            v[k]=true;//如果不是这个，就回溯 
                            flag-=tmp;
                        }
                    }
                }
            }
            else
            {
                for(k=t;k<a[i][j]-'A';k++)
                {
                    if(v[k]==true)
                    {
                        memset(f,0,sizeof(f));
                        f[5][5][5][5][5]=1;
                        v[k]=false;
                        maxx[i]=maxy[j]=k;
                        flag+=dfs(len[0],len[1],len[2],len[3],len[4],0);
                        v[k]=true;
                    }
                }
                v[a[i][j]-'A']=false;//当前这个设置为找过 
            }
        }
    }
    if(bk==0) //输出 
    {
        for(i=0;i<5;i++)
            for(j=0;j<5;j++)
                printf("%c",a[i][j]);
        printf("\n");
    }
    else printf("%d\n",flag+1);
    return 0;
}
```

---

## 作者：kczno1 (赞：2)

一开始我直接搜索，从小到大放数(字母当成数)，每个数枚举行，

之后放在这一行已放的末尾，前提是上一行放的比这一行多。

（因为否则该数的左边或上面就无数可放了）。

之后发现可以记忆化，用f[a,b,c,d,e](第i个参数表示第i行已放的数目)表示

该情况下的方案数。


后来我发现从小到大枚举字母并不能保证字典序从小到大，

如将7放在第二行的所有情况未必比将7放在第三行的所有情况字典序都小，

因为第1行会优先影响字典序。


于是只能从小到大枚举行，列，数；但是我们知道之前的搜索虽然不保证字典序升序，

但求出的方案数是正确的。所以可以求出当前状态下的方案数。比如当前状态已经放了

AB,我们就可以求出接下来的方案数。如果总方案数+当前方案数<所求方案数，

我们就让总方案数加上当前方案数，之后再尝试AC。

时间（5\*5\*25\*（6^7）≈3\*10^7），而实际时间远远小于这个数，只用了10ms。


---

## 作者：Jiang_zi_chuan (赞：0)

用150行代码成功的A了，（记得我的时间是最快的）

思路：

记忆化搜索，比较难的一道题。

通过前缀记数的方法完成字母和数字之间的转换。

问题转换为给定前缀，求有多少个合法的摆放方法。

考虑按照A-Y的顺序依次把字母填进表格，填表时需要满足3条规则：（1）所填字母的左边不能为空；

（2）所填字母的上方不能为空；

（3）如果字母在前缀中，则必须填在对应位置，如果字母不在前缀中，也不能占据前缀中出现的字母的位置。

因为字母的位置调换会带来大量的合法摆法，所以这一题直接搜索是过不了的。

标准做法里搜索状态的表示很精妙，我们用F[a][b][c][d][e]表示按照从A-Y的顺序摆，第一行摆a个字母，第二行摆b个字母。。。

的合法摆法数量。

这种状态表示的合理性依赖上述的（1）（2）两条规则。

这样抽象过的状态就大大减少了搜索空间。再用记忆化搜索优化一下，速度非常快。

代码：

```cpp
//2018.12.31 09:26
/*
   Name: Jiang_zi_chuan
   Copyright: Jiang_zi_chuan
   Author: Jiang_zi_chuan
   Date: 31/12/18 09:26
   Description: 深度优先搜索,DFS&&概率论,统计&&动态规划,动规,dp
*/
// luogu-judger-enable-o2
//#define LOCAL
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

#define INF 0x3f
#define ull unsigned long long
#define ll long long
#define FOR(a, b, n) for(int a = b; b >= n ? a >= n : a <= n; b >= n ? a-- : a++)
#define M(a, n) memset(a, n, sizeof(a));
#define S(n) scanf("%d", &n)
#define P(n) printf("%d", n)
#define G(n) getline(cin, n)
#define PI acos(-1.0)
#define QAQ(n) 0
#define chen_zhe 0x3f

using namespace std;

const int NR = 35;

inline int read()  {
   	int s = 0, w = 1;
   	char ch = getchar();
   	while(ch <= '0' || ch > '9') {
   		if(ch == '-') {
   			w = -1;
   			ch = getchar();
   		}
   	}
   	while(ch >= '0' && ch <= '9') {
   		s = s * 10 + ch - '0';
   		ch = getchar();
   	}
   	return s * w;
}

char Str[30];
int Appear[30];
int Table[6][6][6][6][6];
 
inline bool dp(int _l, int _c, int _upc) {
    if(_c == 5) 
    	return false;
    if(Str[_l * 5 + _c] != '\0') 
    	return false;
    if(_c + 1 > _upc) 
    	return false;
    return true;
}
 
int dfs(int _a, int _b, int _c, int _d, int _e) {
    if(Table[_a][_b][_c][_d][_e] != 0)
        return Table[_a][_b][_c][_d][_e];
    int id = _a + _b + _c + _d + _e;
    if(id == 25) 
    	return Table[5][5][5][5][5] = 1;
    int ret = 0;
    if(Appear[id] != -1) {
        int line = Appear[id] / 5;
        if(line == 0)
            ret = dfs(_a + 1, _b, _c, _d, _e);
        else if(line == 1)
            ret = dfs(_a, _b + 1, _c, _d, _e);
        else if(line == 2)
            ret = dfs(_a, _b, _c + 1, _d, _e);
        else if(line == 3)
            ret = dfs(_a, _b, _c, _d + 1, _e);
        else if(line == 4)
            ret = dfs(_a, _b, _c, _d, _e + 1);
    }
    else {
        if(dp(0, _a, 5))
            ret += dfs(_a + 1, _b, _c, _d, _e);
        if(dp(1, _b, _a))
            ret += dfs(_a, _b + 1, _c, _d, _e);
        if(dp(2, _c, _b))
            ret += dfs(_a, _b, _c + 1, _d, _e);
        if(dp(3, _d, _c))
            ret += dfs(_a, _b, _c, _d + 1, _e);
        if(dp(4, _e, _d))
            ret += dfs(_a, _b, _c, _d, _e + 1);
    }
    return Table[_a][_b][_c][_d][_e] = ret;
}
 
int main() {
    char c, s[30], ans_s[30] = {'\0'};
    int n, ans_n = 0;
    scanf("%c", &c);
    if(c == 'W') {
        scanf("%s", s);
        M(Appear, -1);
        FOR(i, 0, 24) {
            for(Str[i] = 'A'; Str[i] < s[i]; Str[i]++) {
                if(Appear[Str[i] - 'A'] != -1) 
                	continue;
                if(i % 5 != 0 && Str[i] < Str[i - 1]) 
                	continue;
                if(i / 5 != 0 && Str[i] < Str[i - 5]) 
                	continue;
                Appear[Str[i] - 'A'] = i;
                M(Table, 0);
                ans_n += dfs(0, 0, 0, 0, 0);
                Appear[Str[i] - 'A'] = -1;
            }
            Appear[Str[i] - 'A'] = i;
        }
        P(++ans_n);
        printf("\n");
    }
    else {
        S(n);
        M(Appear, -1);
        FOR(i, 0, 24) {
            for(Str[i] = 'A';; Str[i]++) {
                if(Appear[Str[i] - 'A'] != -1) 
                	continue;
                if(i % 5 != 0 && Str[i] < Str[i - 1]) 
                	continue;
                if(i / 5 != 0 && Str[i] < Str[i - 5]) 
                	continue;
                Appear[Str[i] - 'A'] = i;
                M(Table, 0);
                int tmp = dfs(0, 0, 0, 0, 0);
                if(tmp >= n) {
                    ans_s[i] = Str[i];
                    break;
                }
                n -= tmp;
                Appear[Str[i] - 'A'] = -1;
            }
        }
        printf("%s\n", ans_s);
    }
    return 0;
}
```

---

