# [USACO17JAN] Hoof, Paper, Scissor G

## 题目背景

*本题与 [银组同名题目](/problem/P6120) 在题意上一致，唯一的差别在于对变手势次数的限制。*


## 题目描述

你可能玩过“石头，剪刀，布”，这个游戏在奶牛中同样流行，不过它的名字变成了“蹄子，剪刀，布”。

“蹄子，剪刀，布”和“石头，剪刀，布”的规则十分类似，两只奶牛数到三，然后出一个代表蹄子，剪刀或布的手势。蹄子胜过剪刀，剪刀胜过布，布胜过蹄子。特别地，如果两只奶牛的手势相同，则视为平局。

现在 FJ 和 Bassie 要进行 $N$ 轮对抗。Bassie 已经预测了 FJ 每一轮要出的手势。然而 Bassie 很懒，她最多只想变换 $K$ 次手势。

现在请你帮 Bassie 求出她最多能赢多少轮。

## 样例 #1

### 输入

```
5 1
P
P
H
P
S```

### 输出

```
4
```

# 题解

## 作者：zgf519orz (赞：51)

**一眼看上去**，像是经典的一大类 $dp$ 题，我们可以枚举 Bassie 最后一次变换手势是第几轮，不过这里，为了判断 Bassie 有没有赢，我们要加上一维来表示 Bassie 最后一次出的是什么手势（0 -> H ，1 -> S ， 2 -> P）。

状态即为： $f[i][j][flag]$ 表示前 $i$ 轮，**严格**变换了 $j$ 次手势，并且最后一次出的是 $flag$ 手势所赢的最多次数。

前面说了。要枚举 “最后一次变换手势是第几轮”，那么我们设为第 $k$ 轮，显然，第 $i$ 轮有三种情况，即出 0 或 1 或 2 手势，而每种情况又对应第 $k$ 轮不同的手势，这里注意，第 $i$ 轮与第 $k$ 轮手势不可以相同（否则不用变换）。

贴下状态转移方程：

```cpp
//分三大类，第i轮分别出0 1 2
//每大类又分2小类，具体见下
f[i][j][0]=max(f[i][j][0],max(f[k][j-1][1],f[k][j-1][2])+h[i]-h[k]);
//第k轮可出1 2，但不可出0

f[i][j][1]=max(f[i][j][1],max(f[k][j-1][0],f[k][j-1][2])+s[i]-s[k]);
//第k轮可出0 2，但不可出1

f[i][j][2]=max(f[i][j][2],max(f[k][j-1][0],f[k][j-1][1])+p[i]-p[k]);
//第k轮可出0 1，但不可出2
```

（温馨提示：#define AC TLE）

$AC$ 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
//H 0
//S 1
//P 2

int n,m; 
int h[100005],s[100005],p[100005];
//这里用三个前缀数组记录1~i轮分别出H S P可以赢的轮数
int f[100005][25][3];
//DP数组

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		char tmp;
		cin >> tmp;
		h[i]=h[i-1];
		s[i]=s[i-1];
		p[i]=p[i-1];
		if(tmp=='H'){
			p[i]++;
		}
		if(tmp=='S'){
			h[i]++;
		}
		if(tmp=='P'){
			s[i]++;
		}
	}
	for(int i=1;i<=n;i++){
		f[i][0][0]=h[i];
		f[i][0][1]=s[i];
		f[i][0][2]=p[i];
	}//初始化，显然只要不变化手势，赢得轮数就是p s h数组记录的
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=i-1;k>=j;k--){//枚举上次变换手势的轮数
            			//状态转移
				f[i][j][0]=max(f[i][j][0],max(f[k][j-1][1],f[k][j-1][2])+h[i]-h[k]);
				f[i][j][1]=max(f[i][j][1],max(f[k][j-1][0],f[k][j-1][2])+s[i]-s[k]);
				f[i][j][2]=max(f[i][j][2],max(f[k][j-1][0],f[k][j-1][1])+p[i]-p[k]);    		
			}
		}
	}
	int ans=0;
	for(int i=0;i<=m;i++){
		ans=max(ans,max(f[n][i][0],max(f[n][i][1],f[n][i][2])));
	}//由于没有强求必须变换m次,应在所有答案中取最大值
	printf("%d",ans);
	return 0;
}
```

不过显然，这份代码肯定会超时的，因为 $1 \le N \le 10^5$ （别跟我说N方过百万，暴力碾标算…………~~真香~~）。

那么考虑优化吧，在原先代码的基础上，枚举 $i$ 和 $j$ 的循环是少不了的，那么我们可不可以省略枚举 $k$ 的循环呢？

事实上，我们不需要考虑过多情况，**当前状态只与 $i-1$ 的状态有关** ，why？

在之前的代码里，我们要求 $i$ 轮和 $k$ 轮手势不可一样，而由 $i-1$ 转移，就不需要考虑这么多了。

我们分析一下：

当第 $i$ 轮选择出与 $i-1$ 轮不同的手势时，就是前 $i-1$ 轮变 $j-1$ 次赢的数量加上第 $i$ 次是否可以赢。

而第 $i$ 轮选择出与 $i-1$ 轮相同的手势时，是不用变换的，也就是说前 $i-1$ 轮要变换 $j$ 次手势，而前 $i-1$ 轮是怎么变换这 $j$ 次手势的？我们根本不用关心，因为答案已经算过了，这就是 $dp$ 的巧妙之处。

废话不多说，献上蒟蒻的代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int n,m;
bool h[100005],s[100005],p[100005];
//这里的h s p数组和上面不一样，表示的是第 $i$ 轮出H/S/P能否赢。
//当然可以省略这三个数组，写个函数也是可以滴~
int f[100005][25][3];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		char tmp;
		cin >> tmp;
		if(tmp=='H'){
			p[i]=1;
		}
		if(tmp=='S'){
			h[i]=1;
		}
		if(tmp=='P'){
			s[i]=1;
		}
     		//字符读入还是cin稳（只是个人看法）
	}
	//H 0
	//S 1
	//P 2
	f[1][0][0]=h[1];
	f[1][0][1]=s[1];
	f[1][0][2]=p[1];
   	//初始化也简单了呢，只有1轮，变换0次，答案显然
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			f[i][j][0]=max(f[i][j][0],
            			   max(f[i-1][j][0]+h[i],
                           	   max(f[i-1][j-1][1]+h[i],f[i-1][j-1][2]+h[i])));
			f[i][j][1]=max(f[i][j][1],
            			   max(f[i-1][j][1]+s[i],
                           	   max(f[i-1][j-1][0]+s[i],f[i-1][j-1][2]+s[i])));
			f[i][j][2]=max(f[i][j][2],
            	  		   max(f[i-1][j][2]+p[i],
                           	   max(f[i-1][j-1][0]+p[i],f[i-1][j-1][1]+p[i])));
            		//可能max有点多，看得有些复杂，稍微解释一下吧。
                 	//只以f[i][j][0]为例，第i-1轮可以出0 1 2，出0时对应状态为f[i-1][j][0]。
                    	//出1时为f[i-1][j-1][1]+h[i]，出2时为f[i-1][j-1][2]+h[i]
                        //f[i][j][1/2]也差不多，只要把其中最后一维的数改一下，再把h[i]改为p/s[i]就可以喽
		}
	}
	int ans=0;
	for(int i=0;i<=m;i++){
		ans=max(ans,max(f[n][i][0],max(f[n][i][1],f[n][i][2])));
	}//同样枚举变换次数选择最优解
	printf("%d",ans);
	return 0;
    	//华丽结束~~~
}
```

呼，写得真累，最后再 ~~恬不知耻~~ 地请大家点个赞吧 $QwQ$

---

## 作者：2017gangbazi (赞：19)

P3609 题解

看到楼上大佬们记搜的写法，蒟蒻表示其实记搜也可以很好写

本题并不用那么多的胜负判断

既然要求胜场最多，一种出拳方式只有一种胜利的方式(就比如对于剪刀只有石头能赢)

那么直接把胜负关系挪位一下

把和FJ出拳方式相同的当做胜出的方式

判断就十分好写了

贴代码

------------



```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+100;
int n,k;
int s[maxn],f[maxn][22][3];
int dp(int x,int b,int w) {
	if(x==0)return 0;
	if(f[x][b][w])return f[x][b][w];//记忆化
	int p=dp(x-1,b,w);
	if(b!=0) {// b=0则不能再改变
		for(int i=0; i<3; i++)
			if(i!=w)p=max(p,dp(x-1,b-1,i));
	}
	return f[x][b][w]=p+(w==s[x]);//如果出拳方式一样则判胜
}
int main() {
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++) {
		char c=getchar();
		while(c!='P'&&c!='H'&&c!='S')c=getchar();
		if(c=='P')s[i]=0;
		if(c=='H')s[i]=1;
		if(c=='S')s[i]=2;
        //出拳方式的代号
	}
	int ans=0;
	for(int i=0; i<=k; i++) {//枚举在前n个改多少次出拳方式
		for(int j=0; j<3; j++)//枚举最后一个改为什么
			ans=max(ans,dp(n,i,j));
	}
	cout<<ans<<endl;
}
```

欢迎hack以及关于题目的私信交流


---

## 作者：南城忆潇湘 (赞：10)

仅限个人理解qwq,如有写的不好的地方，欢迎指出。dalao勿喷qwq。

Warning:"以下内容或许让你感到不适，请坚持到底，多多少少应该会有些收获的"

我们看这道题目，理解一下题意，然后看到“最多能赢多少场”，这道题目差不多就是用dp做了(某位dalao说得好，这道题必须一眼看出用dp,%%%%)(:зゝ∠)_

我们可以看出来，（原谅我这么说qwq）对于每个回合，都有一个最优解。这样，第一维就出来了f[i]中的i表示在第i个回合能赢的最大次数。

这样，思路就基本上出来了。对于i来说，前一个要么不改变，要么改变。这样就可以把它给表示出来。f[i]=(f[i-1]+当前改变得到的值)或者是(f[i]+当前不改变得到的值)。当然，我们在两者中选择的时候，应该要取最大值。

这时候，我们就会发现。。。当我们只用f[i-1]来表示f[i]时，它就会出现错误。因为我们在从f[i-1]推导到f[i]的时候，它少了一些必要的数据（比如:它在f[i-1]的最优情况下换了几次）。辣么这时候怎么办？

那我们就多加一维，变成了f[i][j],代表第i回合最大换j次时的最大值。我们再来进行转移。f[i][j]=(f[i-1][j-1]+当前改变得到的值)或者是(f[i-1][j]+当前不改变得到的值)，我们又在这两个中间选到最优值。想一想：为啥有一个是j,有一个是j-1?qwq

我们一看，这个方程已经可以通过这个表达式进行转移了，但是，我们在写代码的时候，又会发现我们的推导式没有错误，但是对于这个状态，它改不改变得到的值依旧不明朗。它在f[i-1][j]或者是f[i-1][j-1]这个最优值的时候选的是蹄子，剪刀，还是布呢?于是我们就再加一维，表示当前情况下选的是蹄子，剪刀或者是布。

我们就可以表达式写出来了qwq(pk[p][q]表示p与q进行对决的结果,1表示p打败q，0表示p要么打平，要么输了q,而a[i]则表示另一个人第i回合的手势,S表示除了k的手势集合)

### f[ i ][ j ][ k ] = {f[ i - 1 ][ j ][ k ] + pk[ k  ][ a[ i ] ],f[ i - 1 ][ j - 1][ l ] + pk[ k ][ a[ i ] ] | l ∈ S}
然后再求这个集合中的最大值就o~~jb~~k啦啦啦~\(≧▽≦)/~
也可以写得通俗一点qwq

f[i][j][k]=f[i-1][j][k]+k与a[i]对决的值 

				或者是 

f[i-1][j-1][其他手势]+k与a[i]对决的值

注意：j要从0开始，在l的循环中要加上j!=0,~~我才不会说就因为没有这个条件然后WA了两个点怎么都检查不出来~~

题解如下啦:
```cpp
#include<map>
#include<cstdio>
#include<iostream>
using namespace std;
map <char,int> qwq;
int pk[4][4];
void orz(){
	qwq['H']=1;	qwq['S']=2;	qwq['P']=3;
	pk[1][2]=1; pk[2][3]=1; pk[3][1]=1;
	return ;
}
int a[100010],f[100010][21][4];
int main(){
	orz();
	int n,s;
	char x=' ';
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>x;
		a[i]=qwq[x];
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=min(s,i);j++)
			for(int k=1;k<=3;k++){
				int t=pk[k][a[i]];
				f[i][j][k]=max(f[i-1][j][k]+t,f[i][j][k]);
				for(int l=1;l<=3;l++)
					if(l!=k&&j)
						f[i][j][k]=max(f[i-1][j-1][l]+t,f[i][j][k]);
			}
	int ans=0;
	for(int i=1;i<=3;i++)
		ans=max(f[n][s][i],ans);
	cout<<ans;
	return 0;
}
```


---

## 作者：OIer991215 (赞：9)

//看到题解里只有cz大神的动态规划，那我就放心了...

//我这种蒟蒻只会记忆化搜索。。。所以发个记忆化搜索的答案

        
    
    
        
    
```cpp
//其实我是模拟~ 
#include <iostream>
#include <cstdio>
using namespace std;
int n,k;
int dp[4][101010][25];
int f[303030];
char cc;
int dfs(int num,int chance,int pos)
{
    if(pos>n || chance>k)
        return 0;
    if(chance>k)return -0x3FFFFFFF;
    if(dp[num][pos][chance]!=0)
        return dp[num][pos][chance];           //三个if表明这是记忆化 
    if(chance==k)      //机会用完了 
    {
        if(num==1 && f[pos]==2)             //剪刀赢了布   ,可以变换当前的手势，也可以不变换 
            dp[num][pos][chance] = dfs(1,chance,pos+1)+1;  
        else if(num==2 && f[pos]==3)        //布赢了石头 ，可以变换当前的手势，也可以不变换 
            dp[num][pos][chance] = dfs(2,chance,pos+1)+1;
        else if(num==3 && f[pos]==1)        //石头赢了剪刀 ，可以变换当前的手势，也可以不变换 
            dp[num][pos][chance] = dfs(3,chance,pos+1)+1;
        if(num==1 && f[pos]!=2)               //剪刀没有赢布，  可以变换当前的手势，也可以不变换 
            dp[num][pos][chance] = dfs(1,chance,pos+1);
        else if(num==2 && f[pos]!=3)         //布没有赢石头   可以变换当前的手势，也可以不变换 
            dp[num][pos][chance] = dfs(2,chance,pos+1);
        else if(num==3 && f[pos]!=1)         //石头没有赢剪刀    可以变换当前的手势，也可以不变换
            dp[num][pos][chance] = dfs(3,chance,pos+1);
    }    
    else     //机会没用完 
    {
        if(num==1 && f[pos]==2)   //剪刀赢了布   ,可以变换当前的手势，也可以不变换 
            dp[num][pos][chance]= max(  max( dfs(1,chance,pos+1)+1 , dfs(2,chance+1,pos+1)+1 ) , dfs(3,chance+1,pos+1)+1  );
        else if(num==2 && f[pos]==3)//布赢了石头 ，可以变换当前的手势，也可以不变换 
            dp[num][pos][chance]= max(  max( dfs(1,chance+1,pos+1)+1 , dfs(2,chance,pos+1)+1 ) , dfs(3,chance+1,pos+1)+1  );
        else if(num==3 && f[pos]==1)//石头赢了剪刀 ，可以变换当前的手势，也可以不变换 
            dp[num][pos][chance]= max(  max( dfs(1,chance+1,pos+1)+1 , dfs(2,chance+1,pos+1)+1 ) , dfs(3,chance,pos+1)+1  );
        if(num==1 && f[pos]!=2)   //剪刀没有赢布，  可以变换当前的手势，也可以不变换 
            dp[num][pos][chance]= max(  max( dfs(1,chance,pos+1) , dfs(2,chance+1,pos+1) ) , dfs(3,chance+1,pos+1)  );
        else if(num==2 && f[pos]!=3)//布没有赢石头   可以变换当前的手势，也可以不变换 
            dp[num][pos][chance]= max(  max( dfs(1,chance+1,pos+1) , dfs(2,chance,pos+1) ) , dfs(3,chance+1,pos+1)  );
        else if(num==3 && f[pos]!=1)//石头没有赢剪刀    可以变换当前的手势，也可以不变换 
            dp[num][pos][chance]= max(  max( dfs(1,chance+1,pos+1) , dfs(2,chance+1,pos+1) ) , dfs(3,chance,pos+1)  );
    }
    return dp[num][pos][chance];
}
int main()
{
    cin>>n>>k;
    for(int i=1; i<=n; i++)
    {
        cin>>cc;
        if(cc=='P')  //1是剪刀 
            f[i]=1;
        if(cc=='H')
            f[i]=2;     //2是布 
        if(cc=='S')
            f[i]=3;     //3是石头 
    }
    cout<<max(  max( dfs(1,0,1) , dfs(2,0,1) ) , dfs(3,0,1)  ); //模拟 一开始出 剪刀/石头/布 的情况 
    return 0;
}
```

---

## 作者：Meditations (赞：4)

其实是一个很简单的dp(模拟)题,但是对于3个月没code的人来说,还是很难的.....
这题一看就是个dp题,读题嘛:"求出她最多能赢几场"(反正就是说,问你什么最优方案的,一般都是dp,~~其实你也可以用记忆化搜索去做~~)

f的含义很明确,就是最多能赢场次:

-  先来一维,f[i]表示第i个回合(肯定不够)
-  再来一维,f[i][j]表示变换j次(还不够,因为没法表明当前的手势(状态))
-  再加一维,f[i][j][k]表示k为什么手势

所以,f[i][j][k]最终表示第i回合,变了j次,出的(石头,剪刀,布)能赢得最多回合

如果不变,
```
f[i][j][k]=f[i-1][j][k]+pk[k][a[i]];
```
pk就是不同手势对应的胜负(所以要先处理一下),a[i]就是FJ第i次出的手势.

由此,我们可以推出转移方程为:
```
f[i][j][k]=max(f[i-1][j][k]+pk[k][a[i]],f[i-1][j-1][l]+pk[k][a[i]]);
```
l这里指的是初k以外其他两种手势,~~很简单吧~~,那我们来看代码吧!
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<iostream>
using namespace std;

map <char,int> q;
int pk[4][4];
void orz(){
    q['H']=1; q['S']=2; q['P']=3;
    pk[1][2]=1; pk[2][3]=1; pk[3][1]=1;
    return ;
}

char x;
int n,k,a[100010];
int f[100010][21][4];

int main(){
	orz();
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		cin>>x;
		a[i]=q[x];
	} 
	for(int i=1;i<=n;i++)
	for(int j=0;j<=min(k,i);j++)
	for(int k=1;k<=3;k++){
		int temp=pk[k][a[i]];
		f[i][j][k]=max(f[i-1][j][k]+temp,f[i][j][k]);
		for(int l=1;l<=3;l++){
			if(l!=k&&j)
			f[i][j][k]=max(f[i][j][k],f[i-1][j-1][l]+temp);
		}
	}
	int ans=0;
	for(int i=1;i<=3;i++)
	ans=max(f[n][k][i],ans);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Del_Your_Heart (赞：3)


# 题目大意
#### 给你$n$个蹄子/剪刀/布，在你没改变前出法均相同，珂以改$n$次，问你$n$次之后最多的相同的局数有多少。

#### （这里为方便转移状态，把“蹄子大于剪刀，剪刀大于布，布大于石头”换成了“相同的”，其实这两种是等价的，因为贝西珂以改变初始的对策。）



------------

# 思路分析

考虑$DP$。

状态：$f[i][j][k]$表示做到第$i$轮时变了$j$次，当前手势为$k$时能赢的最多局数。

状态转移：对于每个 $(i,j)$，枚举上次的状态$k$和这次的状态$nowk$。

$1^o$ $k=nowk$，不需要变手势，$f[i][j][nowk]=max( f[i][j][nowk] , f[i-1][j][k]+(a[i]==k) )$

$2^o$ $k!=nowk$，考虑变或不变，$f[i][j][nk]=max(f[i][j][nk],f[i-1][j-1][k]+(nk==a[i]))$

答案即为$max(f[n][m][1],f[n][m][2],f[n][m][3])$

时间复杂度为$O(9nm)$，最慢点实际用时$30ms$（$O^2$），常数较小。（珂能是用了$getchar$优化的缘故）

------------

# 代码实现
```cpp
// luogu-judger-enable-o2
//HPS
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch)){f|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return f?-x:x;
}
int n,ct,sum[4][100005],f[100005][25][4];short a[100005];
char tp;
int main(){
	n=read();ct=read()+1;
	for(register int i=1;i<=n;++i){
		while(!isalpha(tp=getchar()));
		if(tp=='H')
			a[i]=1;
		else if(tp=='P')
			a[i]=2;
		else
			a[i]=3;
	}
	f[1][0][a[1]]=0;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=ct;++j)
			for(register int k=1;k<=3;++k)
				for(register int nk=1;nk<=3;++nk){
					if(k==nk)
						f[i][j][nk]=max(f[i][j][nk],f[i-1][j][k]+(a[i]==k));
					else
						f[i][j][nk]=max(f[i][j][nk],f[i-1][j-1][k]+(nk==a[i]));
				}
	cout<<max(f[n][ct][1],max(f[n][ct][2],f[n][ct][3]));
	return 0;
}
```













---

## 作者：MorsLin (赞：3)

这种$DP$能有蓝题？反正我是不信

---

#### 状态

``f[i][j][k]`` 表示当前是第$i$局，已经变了$j$次手势，当前的手势是$k$，之后能赢多少场

#### 转移

用一种类似后缀和的方式，记录下如果当前变为该手势，则之后能赢多少局（其实这步并不必要，但我觉得更好理解一些）

之后疯狂判断就好了

``f[i][j][k]=max(f[i][j][k],f[i][j-1][k]-sum_now[i]+sum_change[i])``

其中``sum_now[i]``为 当前手势之后能赢多少场，``sum_change[i]``为 改变后的手势之后能赢多少场

#### $code$

特判有点冗杂，但还是挺容易理解的……

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define gc() getchar()
using namespace std;
LL read(){LL k=0,f=1;char c=gc();while(c<'0'||c>'9'){if(c=='-') f=-1; c=gc();}while(c>='0'&&c<='9')k=k*10+c-48,c=gc();return k*f;}
char read_c(){char c=gc();while((c<'a'||c>'b')&&(c<'A'||c>'Z'))c=gc();while((c>='a'&&c<='z')||(c>='A'&&c<='Z'))return c;}
int f[100010][21][4],s[100010],m[100010],b[100010];
int ans;
int main(){
    int n=read(),k=read();
    for(int i=n;i>=1;i--){
        char c=read_c();
        s[i]=s[i+1]; m[i]=m[i+1]; b[i]=b[i+1];
        if(c=='P') s[i]++;
        if(c=='S') m[i]++;
        if(c=='H') b[i]++;
    }
    f[0][0][1]=s[1]; f[0][0][2]=m[1]; f[0][0][3]=b[1];
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            f[i][j][1]=f[i-1][j][1]; f[i][j][2]=f[i-1][j][2]; f[i][j][3]=f[i-1][j][3];
            ans=max(ans,max(f[i][j][1],max(f[i][j][2],f[i][j][3])));
            if(j==0) continue;
            f[i][j][1]=max(f[i][j][1],max(f[i][j-1][2]-m[i]+s[i],f[i][j-1][3]-b[i]+s[i]));
            f[i][j][2]=max(f[i][j][2],max(f[i][j-1][1]-s[i]+m[i],f[i][j-1][3]-b[i]+m[i]));
            f[i][j][3]=max(f[i][j][3],max(f[i][j-1][1]-s[i]+b[i],f[i][j-1][2]-m[i]+b[i]));
            ans=max(ans,max(f[i][j][1],max(f[i][j][2],f[i][j][3])));
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：薛裕龙 (赞：3)

虽然不太明白重复解法是指什么……但是用mod判输赢也算有创新吧……其它的都开得数组，其次这次我连dp也换成滚动的了……不要那么严格嘛……

首先H,P,S，这三个字母我们就当做0,1,2，那么假设贝西出的的x，FJ出的y，贝西能赢FJ当且仅当（x+1）%3==y，这个式子可以让状态转移时更简洁。

然后考虑状态转移，定义dp[i][j][v],表示第 i 轮还剩 j 次可以变化的时候出 v 所能赢的最大局数。

如果这个 v 能赢这一局，那么dp[i][j][v]应该是 dp[i-1][j][v]+1,dp[i-1][j+1][(v+1)%3]+1,dp[i-1][j+1][(v+2)%3]+1这三个中的最大值。

如果本来就是 v 那么就说明不用 j，所以是dp[i-1][j][v],然后就是另外两种手势，可以在用一次j的情况下使用，所以是

dp[i-1][j+1][(v+1)%3]+1和dp[i-1][j+1[(v+2)%3]+1

这种转移只在 v 能赢的时候才有意义，因为不赢的时候根本不可能使用一次 j，变化一次之后结果还不赢，这种事情聪明的贝西怎么可能做……。 所以对于 v 不能赢的情况，直接：

dp[i][j][v]=dp[i-1][j][v];

这一步是必须的，要不然之后的转移会错。

并且可以用滚动数组减掉i那一维，省空间……

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int dp[25][3];//第i局还剩j次变换机会出0,1,2时赢的最大场数
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        char s[2];
        scanf("%s",s);
        int o;
        if(s[0]=='H')o=0;else if(s[0]=='P')o=1;else o=2;//o存下FC的手势 
        for(int j=k;j>=0;j--)
            for(int v=2;v>=0;v--)
                if((v+1)%3==o)
                    dp[j][v]=max(dp[j][v],max(dp[j][v]+1,max(dp[j+1][(v+1)%3]+1,dp[j+1][(v+2)%3]+1)));
                else
                    dp[j][v]=dp[j][v];	
    }
    printf("%d",max(dp[0][0],max(dp[0][1],dp[0][2])));//三种手势都可能最优秀 
    return 0;
}
```

---

## 作者：WayneStewart (赞：1)

某些情况下记忆化搜索比循环DP更直接，更符合认知，便于理解
```cpp
首先无论如何要打个暴力看看，任何时候都是个好策略。因此直接暴力枚举每个手势是啥，看看能不能赢。

把题目中有的东西都用到搜索上，记dfs(x, gest, alter_t, win_t)为当前出第x个手势gest，剩余alter_t次转换机会，截止到目前能赢win_t次。每一次考虑换不换手势

如果不换手势，不耗费机会，赢的次数在win_t基础上加上当前是否赢
换手势耗一次机会（需要alter_t > 0），赢的次数在win_t基础上加上当前是否赢。

枚举完所有n个手势后x在第n+1位，此时递归应该终止，比较一下这种方案的win_t与已知的最大赢次数max_win_t谁大。

以上是最基本的暴力枚举思路。代码如下

void dfs(int x, int gest, int alter_t, int win_t)
{
	if (x > n) {
		max_win_t = max(max_win_t, win_t);
		return;
	}
	dfs(x + 1, gest, alter_t, win_t + win[gest][fj[x]]);
	for (int new_gest = 0; new_gest < 3; ++new_gest)
		if (gest != new_gest && alter_t > 0)
			dfs(x + 1, new_gest, alter_t - 1, win_t + win[gest][fj[x]]);
}

考虑记录状态，避免重复运算
之前用到了一个叫max_win_t的全局变量，随着dfs()的进行统计最大值，把它去掉，并将dfs()加上返回值，于是便于接下来的记忆化搜索。
此时dfs(x, gest, alter_t)表示出x..n的手势且第x为gest，剩余alter_t次转换机会的最大赢次
int dfs(int x, int gest, int alter_t)
{
	if (x > n)
		return 0;
	int ans = 0;
	ans = max(ans, dfs(x + 1, gest, alter_t)); 
	for (int new_gest = 0; new_gest < 3; ++new_gest)
		if (gest != new_gest && alter_t > 0)
			ans = max(ans, dfs(x + 1, new_gest, alter_t - 1));
	return win[gest][fj[x]] + ans;
}

最后加上一个数组mem[x][gest][alter_t]记录状态，即是记忆化搜索
int dfs(int x, int gest, int alter_t)
{
	if (mem[x][gest][alter_t] != -1)
		return mem[x][gest][alter_t];
	if (x > n)
		return 0;
	int ans = 0;
	ans = max(ans, dfs(x + 1, gest, alter_t)); 
	for (int new_gest = 0; new_gest < 3; ++new_gest)
		if (gest != new_gest && alter_t > 0)
			ans = max(ans, dfs(x + 1, new_gest, alter_t - 1));
	return mem[x][gest][alter_t] = win[gest][fj[x]] + ans;
}

完整代码如下
注意：win[x][y]表示贝西出x，FJ出y时，贝西是否赢，如是写可省去许多if判断
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100003;
const int win[3][3] = {
//   0  1  2   H:0, S:1, P:2  P->H->S->P
	{0, 1, 0},
	{0, 0, 1},
	{1, 0, 0}
};
int fj[N];
int mem[N][3][23];
int n, k;

int dfs(int x, int gest, int alter_t);

int main()
{
	cin >> n >> k;
	char ch;
	for (int i = 1; i <= n; ++i) {
		scanf(" %c", &ch);
		if (ch == 'H')
			fj[i] = 0;
		if (ch == 'S')
			fj[i] = 1;
		if (ch == 'P')
			fj[i] = 2;
	}
	memset(mem, -1, sizeof mem);
	int ans = 0;
	for (int i = 0; i < 3; ++i)
		ans = max(ans, dfs(1, i, k));
	cout << ans;

	return 0;
}
int dfs(int x, int gest, int alter_t)
{
	if (x > n)
		return 0;
	int ans = 0;
	ans = max(ans, dfs(x + 1, gest, alter_t)); 
	for (int new_gest = 0; new_gest < 3; ++new_gest)
		if (gest != new_gest && alter_t > 0)
			ans = max(ans, dfs(x + 1, new_gest, alter_t - 1));
	return win[gest][fj[x]] + ans;
}
```



---

## 作者：芬特 (赞：1)

首先拿到这个题，理解题意，就是指FJ跟他的牛贝西玩石头剪刀布，贝西可以洞察FJ接下来n轮的出招方式，并且通过改变自己的出招方式来赢得比赛，一共可以改变k次，求最大赢得比赛的回合数目。

（H代表石头，P代表布，S代表剪刀）

首先想到的是贪心，求最长字段，用三个优先队列一个维护H的最长字段一个维护S的最长字段一个维护P的最长字段，但是无法维护最长字段的顺序，若要再维护顺序，可以使用一棵加载权值splay来维护顺序，但是我们思考一下，假如我们不能选择当前的最长字段，就需要改变原有序列的所有权值，就需要重新建一棵树，每次建树O（nlgn），每次取段O（lgn），再加上从一个O（n）的遍历上进行比较，即使使用平板电视也绝对会TLE；

但其实这道题并没有这么复杂，我们思考一下如何使用动态规划解题，可以先思考存在性，k+1的状态中一定包括了k的最大，那么我们就可以得出转移方程 dp[i][j]=max(dp[i][j-1],dp[i-1][j-1]);但是我们并不知道到底上一回合FJ出什么招，所以我们就再设出一个状态[k]表示出招，就得到转移方程

dp[i][j][H]=max(dp[i-1][j][H],max(dp[i-1][j-1][P],dp[i-1][j-1][S]))+v[H][a[i]]

dp[i][j][S] =max(dp[i-1][j][S],max(dp[i-1][j-1][H],dp[i-1][j-1][P]))+v[S][a[i]]

dp[i][j][P] =max(dp[i-1][j][P],max(dp[i-1][j-1][H],dp[i-1][j-1][S]))+v[P][a[i]]

那么初始状态就是所有的没有出过招的，使用一种招赢多少回合

dp[i][0][H]=dp[i-1][0][H]+v(H,a[i])

诸如此类

就可以写出代码：

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxn=100001;
int array[maxn],dp[maxn][21][4];
int ans;
inline int check(int x,int y)
{
    if(x==1&&y==2) return 1;
    else if(x==2&&y==3) return 1;
    else if(x==3&&y==1) return 1;
    return 0;
}
inline int got_into(int ch1,int ch2,int ch3)
{
    if(ch1>ch2) return ch1>ch3?ch1:ch3;
    else return ch2>ch3?ch2:ch3;
    
}
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        char c;
        cin>>c;
        if(c=='H') array[i]=1;
        if(c=='S') array[i]=2;
        if(c=='P') array[i]=3;
    }
    for (int i=1;i<=n;i++)
    {
        dp[i][0][1]=dp[i-1][0][1]+check(1,array[i]);
        dp[i][0][2]=dp[i-1][0][2]+check(2,array[i]);
        dp[i][0][3]=dp[i-1][0][3] +check(3,array[i]);
    }//初始化
    for(int j=1;j<=k;j++)
    {
        for(int i=1;i<=n;i++)
        {    
        dp[i][j][1] =got_into(dp[i-1][j][1] ,dp[i-1][j-1][2] ,dp[i-1][j-1][3] )+check(1,array[i]);
        dp[i][j][2] =got_into(dp[i-1][j][2] ,dp[i-1][j-1][1] ,dp[i-1][j-1][3] )+check(2,array[i]);
        dp[i][j][3] =got_into(dp[i-1][j][3] ,dp[i-1][j-1][1] ,dp[i-1][j-1][2] )+check(3,array[i]);
        }
    } 
    int ans1=-1,ans2=-1,ans3=-1;
    for(int i=1;i<=n;i++)
    {
        ans1=max(ans1,dp[n][k][1] );//,cout<<ans1<<" ";
        ans2=max(ans2,dp[n][k][2] );//,cout<<ans2<<" ";
        ans3=max(ans3,dp[n][k][3] );//,cout<<ans3<<" ";
//        cout<<endl;
    }
    int ans=got_into(ans1,ans2,ans3);
    cout<<ans;
    return 0;
}
```

---

## 作者：Misaka_Azusa (赞：0)

### 看着标签什么记搜什么暴力点进来，读完题第一直觉DP？
------------
还真是个$DP$。

题目所描述的状态十分明显，第 $i$ 轮，变换 $j$ 次，当前FJ手势 ($x,y,z$)

那我们不妨直接令$f[i][j][k]$表示当前第 $i$ 轮，变换 $j$ 次，在FJ手势为 $k$ 时的胜场为多少。（这里懒得考虑啥手势能胜FJ，故直接用FJ的手势为参考。）

那么在转移时，我们考虑的就是两种情况：

要么我换个手势赢FJ的当前手势，要么我不换手势。

#### 对于换手势：

如果变换到$x$手势赢FJ：

$f[i][j][x] = max(f[i-1][j-1][y], f[i-1][j-1][z]) + num[i][x]$

其中，num[i][x]代表我当前是否能赢FJ的x手势，1为能赢，0为不能赢。

对于变换到y,z手势同理。

#### 对于不换手势：

$f[i][j][x] = f[i-1][j][x] + num[i][x]$

所以总转移方程为：

$f[i][j][x] = max(max(f[i-1][j-1][y], f[i-1][j-1][z]) + num[i][x], f[i-1][j][x] + num[i][x])$

接下来就是O(NK)的转移，最后在第n轮中变换0~k次的三个不同手势中选出max即为答案。


### code：

```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int f[maxn][21][3], k, n, answer;
int num[maxn][3];//H 0  P 1  S 2
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 1; i <= n; i++)
	{
		char s;
		cin>>s;
		if(s == 'H')
		num[i][0] = 1;
		if(s == 'P')
		num[i][1] = 1;
		if(s == 'S')
		num[i][2] = 1;
	}
	
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= k; j++)
		{
            if(j - 1 >= 0)//避免数组下标j-1越界
            {
                f[i][j][0] = max(max(f[i-1][j-1][1], f[i-1][j-1][2]) + num[i][0], f[i-1][j][0] + num[i][0]);
			    f[i][j][2] = max(max(f[i-1][j-1][1], f[i-1][j-1][0]) + num[i][2], f[i-1][j][2] + num[i][2]);
			    f[i][j][1] = max(max(f[i-1][j-1][0], f[i-1][j-1][2]) + num[i][1], f[i-1][j][1] + num[i][1]);
            }
			else
            {
                f[i][j][0] = f[i-1][j][0] + num[i][0];
			    f[i][j][2] = f[i-1][j][2] + num[i][2];
			    f[i][j][1] = f[i-1][j][1] + num[i][1];    
            }
		}
		for(int j = 0; j <= k; j++)
		{
			answer = max(answer, f[n][j][0]);
			answer = max(answer, f[n][j][1]);
			answer = max(answer, f[n][j][2]);
		}
	printf("%d",answer);	
	return 0;
}
```

#### 后记：

这个题难度没有蓝题这么高。

---

## 作者：曹老师 (赞：0)

~~很玄学的解法~~

**知识点：DP**

纯三维DP

f[i][j][k] i：统计答案的时候用 j：换了几次 k：出的第几个字母

（代码中有注释！

对于每一个f[i][j][k]都有两种可能 对应两个方程

```
f[i][j][k]=max(f[pre][j][m]) (m==k) 打平 不换

f[i][j][k]=max(f[pre][j-1][m]) (j!=0) 少交换一次？
```

最后统计出答案来就好了	


```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=100005;
int n,k,w[L],f[2][21][5],pre=0,now=1,ans;
int ex(char ch)
{
	if(ch=='H')
		return 0;
	if(ch=='S')
		return 1;
	if(ch=='P')
		return 2;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		char c;
		cin>>c;
		w[i]=ex(c);// 这里可不是随便处理的 
	}
	for(int i=1;i<=n;i++) //第几局
	{
		for(int j=0;j<=k;j++) //改变了几次
			for(int l=0;l<=2;l++) //目前出的第几个字母
			{
				for(int m=0;m<=2;m++) 
				{
					if(m==l)
						f[now][j][l]=max(f[now][j][l],f[pre][j][m]);
					else
						if(j) //防RE专用if 
							f[now][j][l]=max(f[now][j][l],f[pre][j-1][m]);
				}
				f[now][j][l]+=(w[i]==(l+1)%3); //玄学的判断 
			}
		swap(pre,now); //现在变成以前 
	}
    for(int i=0;i<=k;i++)
        for(int j=0;j<=2;j++)
            ans=max(max(ans,f[pre][i][j]),f[now][i][j]);
    printf("%d",ans);
	return 0;
}
```

---

