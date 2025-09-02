# Bag of mice

## 题目描述

The dragon and the princess are arguing about what to do on the New Year's Eve. The dragon suggests flying to the mountains to watch fairies dancing in the moonlight, while the princess thinks they should just go to bed early. They are desperate to come to an amicable agreement, so they decide to leave this up to chance.

They take turns drawing a mouse from a bag which initially contains $ w $ white and $ b $ black mice. The person who is the first to draw a white mouse wins. After each mouse drawn by the dragon the rest of mice in the bag panic, and one of them jumps out of the bag itself (the princess draws her mice carefully and doesn't scare other mice). Princess draws first. What is the probability of the princess winning?

If there are no more mice in the bag and nobody has drawn a white mouse, the dragon wins. Mice which jump out of the bag themselves are not considered to be drawn (do not define the winner). Once a mouse has left the bag, it never returns to it. Every mouse is drawn from the bag with the same probability as every other one, and every mouse jumps out of the bag with the same probability as every other one.

## 说明/提示

Let's go through the first sample. The probability of the princess drawing a white mouse on her first turn and winning right away is 1/4. The probability of the dragon drawing a black mouse and not winning on his first turn is 3/4 \* 2/3 = 1/2. After this there are two mice left in the bag — one black and one white; one of them jumps out, and the other is drawn by the princess on her second turn. If the princess' mouse is white, she wins (probability is 1/2 \* 1/2 = 1/4), otherwise nobody gets the white mouse, so according to the rule the dragon wins.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
0.500000000
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
0.658730159
```

# 题解

## 作者：yingyudou (赞：25)

#### Description

~~翻译君写的清清楚楚明明白白~~

----

#### Solution

- 概率dp
- 设 $f(i,j)$ 表示有 $i$ 只白鼠，$j$ 只黑鼠时A先手胜的概率

- 初始状态
- 全白时，显然先手必胜
- 有一只黑鼠时，先手若抽到黑鼠则后手必胜，所以先手首回合必须抽到白鼠
- $f(i,0)=1,f(i,1)=\frac{i}{i+1}$

- 转移方程 $f(i,j)$
- 先手抽到白鼠，胜：$\frac{i}{i+j}$
- 先手抽到黑鼠，后手抽到白鼠，败： $0$
- 先手抽到黑鼠，后手抽到黑鼠，跑一只白鼠：$\frac{j}{i+j}\times \frac{j-1}{i+j-1}\times \frac{i}{i+j-2}\times f(i-1,j-2)$
- 先手抽到黑鼠，后手抽到黑鼠，跑一只黑鼠：$\frac{j}{i+j}\times \frac{j-1}{i+j-1}\times \frac{j-2}{i+j-2}\times f(i,j-3)$
- $f(i,j)=\frac{i}{i+j}+\frac{j}{i+j}\times \frac{j-1}{i+j-1}\times \frac{i}{i+j-2}\times f(i-1,j-2)+\frac{j}{i+j}\times \frac{j-1}{i+j-1}\times \frac{j-2}{i+j-2}\times f(i,j-3)$

- $O(wb)$

----

#### Code 1
```cpp
//DP
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    int N=0,C=0;char tf=getchar();
    for(;!isdigit(tf);tf=getchar())C|=tf=='-';
    for(;isdigit(tf);tf=getchar())N=(N<<1)+(N<<3)+(tf^48);
    return C?-N:N;
}

const int N=1010;
int w,b;
double f[N][N];

int main()
{
	w=read(),b=read();
	
	for(int i=1;i<=w;++i)
		f[i][0]=1.0,f[i][1]=1.0*i/(i+1);//全白必胜，一黑首回合必须抽到白鼠
		
	if(!b||b==1)return printf("%.9lf\n",f[w][b]),0;
	for(int i=1;i<=w;++i)
		for(int j=2;j<=b;++j)
		{
			f[i][j]=1.0*i/(i+j);
			f[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*i/(i+j-2)*f[i-1][j-2];//跑白
			if(j^2)f[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*(j-2)/(i+j-2)*f[i][j-3];//跑黑 
		}
	printf("%.9lf\n",f[w][b]);
	
    return 0;
}
```

----

#### Code 2
```cpp
//记忆化搜索
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    int N=0,C=0;char tf=getchar();
    for(;!isdigit(tf);tf=getchar())C|=tf=='-';
    for(;isdigit(tf);tf=getchar())N=(N<<1)+(N<<3)+(tf^48);
    return C?-N:N;
}

const int N=1010;
int w,b;
double f[N][N];

double dfs(int i,int j)
{
	if(f[i][j])return f[i][j];
	if(!i)return 0;//全黑必败 
	if(!j)return f[i][j]=1.0;//全白必胜 
	if(j==1)return f[i][j]=1.0*i/(i+1);//一黑首回合必须抽到白鼠 
	f[i][j]=1.0*i/(i+j);
	f[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*i/(i+j-2)*dfs(i-1,j-2);//跑白
	if(j>2)f[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*(j-2)/(i+j-2)*dfs(i,j-3);//跑黑 
	return f[i][j];
}

int main()
{
	w=read(),b=read();
	printf("%.9lf\n",dfs(w,b));
	
    return 0;
}
```

---

## 作者：mzgwty (赞：20)

~~你谷群众真会恶意评分~~

~~这题最多蓝题~~

~~虽然刚学概率dp~~

首先一波预处理

$dp[i][j]$表示i只白兔，j只黑兔时获胜的概率

则$dp[i][0]=1$,$dp[i][1]=i/(i+1)$

然后对于每个$dp[i][j]$

1.先手刚好拿到白兔:$dp[i][j]=i/(i+j)$

2.先手黑兔，后手白兔:$dp[i][j]=0$,这种情况不用处理

3.先手黑兔，后手黑兔，跑白兔:$dp[i][j]=j/(i+j)*(j-1)/(i+j-1)*i/(i+j-2)*dp[i-1][j-2]$

4.先手黑兔，后手黑兔，跑黑兔:$dp[i][j]=j/(i+j)*(j-1)/(i+j-1)*(j-2)/(i+j-2)*dp[i][j-3]$

最后输出$dp[w][h]$即可

$Talk \ is \ cheap,show \ you \ the \ code.$

```cpp
#include<bits/stdc++.h>
#define rep(a,b,c) for(register int a=b ; a<=c ; ++a)
#define dwn(a,b,c) for(register int a=b ; a>=c ; --a) 
using namespace std;

inline int read() {
	int res=0,f=1;char ch;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	do {
		res=res*10+ch-'0';
	} while(isdigit(ch=getchar()));
	return res*f;
}

double dp[1005][1005];

int main() {
	int w=read(),b=read();
	rep(i,1,w) dp[i][0]=1.0,dp[i][1]=1.0*i/(i+1);
	rep(i,1,w) {
		rep(j,2,b) {
			dp[i][j]=1.0*i/(i+j);
			dp[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*i/(i+j-2)*dp[i-1][j-2];
			if(j^2) dp[i][j]+=1.0*j/(i+j)*(j-1)/(i+j-1)*(j-2)/(i+j-2)*dp[i][j-3];
		}
	}
	printf("%.9lf",dp[w][b]);
	return 0;
}
```
（很短的）

---

## 作者：Pathetique (赞：16)

歪？看到大家都是刷表做的quq我来发个记忆化搜索的题解，这道题的话搜索比刷表简单而且快，因为刷表有好多状态都是多余的呢.

首先dfs的时候记录一个$nw$和$nb$表示当前还剩下$nw$个白老鼠$nb$个黑老鼠时$A$赢的概率，记忆化可以用一个$f[nw][nb]$来记。

然后说一下边界，当$nw=0$的时候，显然$A$是必输的，$return\ 0$，当$nb=0$的时候，因为$nw=0$的情况以及判掉了，那么此时$A$是必赢的，$return\ 1$，其他的情况可以分类讨论，如果这一次$A$首先抽到了白老鼠，那么他就赢了，所以可以不用管后边的，先让$ans+=nw/(nw+nb)$，如果说$A$这次抽到了黑老鼠，那么$B$一定也要抽到黑老鼠，否则$A$就输了，所以只需要再讨论一下最后随机溜掉的那只老鼠到底是什么老鼠就好了。

可以看到我们只会搜到有用的状态，因此这道题记忆化搜索是比无脑刷表快很多的。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define maxn 1005
using namespace std;
int w,b;
double f[maxn][maxn];

double dfs(int nw,int nb){
	if(nw==0) return 0.0;
	if(nb==0) return 1.0;
	if(f[nw][nb]>0) return f[nw][nb];
	double ans=0;
	ans+=1.0*nw/(nw+nb);
	if(nb==2)
	ans+=1.0*nb/(nw+nb)*(nb-1)/(nw+nb-1)*dfs(nw-1,nb-2);
	else if(nb>=3)
	ans+=1.0*nb/(nw+nb)*(nb-1)/(nw+nb-1)*
	(1.0*nw/(nw+nb-2)*dfs(nw-1,nb-2)+1.0*(nb-2)/(nw+nb-2)*dfs(nw,nb-3));
	return f[nw][nb]=ans;
}

int main(){
	scanf("%d%d",&w,&b);
	printf("%.9lf",dfs(w,b));
	return 0;
}
```

---

## 作者：Monster_Qi (赞：3)

# 解题思路

​	~~这怕是本蒟蒻第一个独立做出来的期望$dp$的题，发篇题解庆祝一下~~。首先，应该是能比较自然的想出状态设计$f[i][j][0/1]$ 表示当前还剩 $i$个白老鼠，$j$个黑老鼠，当前是$A/B$抓的概率。有个问题似乎因为当其中一个人抓到白老鼠时游戏就结束了，而在转移过程中比较难表示出来这个，但换状态的话比较难转移。所以要想一个办法，因为如果知道当前有$i$只白老鼠和$j$只黑老鼠的话，那么当前人获胜的概率可以$O(1)$的算出来，$p=\dfrac {i}{i+j}$。所以转移时只去转移那些抓黑老鼠的状态，而答案则在转移中更新就行了，具体转移和实现看代码。


# 代码实现

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
const int MAXN = 1005;

int w,b;
double f[MAXN][MAXN][2],ans;

int main(){
	cin>>w>>b;int n=w+b;
	f[w][b][0]=1;if((w|b))ans=(double)w/n; //初值是还剩 w个白老鼠，b个黑老鼠，当前A取的概率是1。 
	for(int i=w;i>=0;i--)	
		for(int j=b-(i==w);j>=0;j--){
			f[i][j][0]=f[i+1][j+1][1]*((double)(j+1)/(i+j+2))*((double)(i+1)/(i+j+1));
			f[i][j][0]+=f[i][j+2][1]*((double)(j+2)/(i+j+2))*((double)(j+1)/(i+j+1));
			//f[i][j][0]可以从上一轮B拿走一只黑鼠扔掉一只黑鼠和拿走一只黑鼠和扔掉一只白鼠转移
				//但绝对不能从拿走一只白鼠转移，因为这样游戏就结束了。 
			if((i|j)) ans+=f[i][j][0]*((double)i/(i+j)); //每步加一次当前的答案。 
		 	f[i][j][1]=f[i][j+1][0]*((double)(j+1)/(i+j+1));
			  //f[i][j][1]只能从上一轮A拿走一只黑鼠转移，因为拿走白鼠已经累计到答案里了 
		}
	printf("%.9lf",ans);
	return 0;
}
```

---

## 作者：zimindaada (赞：3)

2020/2/2注：修复了$LaTeX$，感谢刘开予2019顺便%%%

令$f_{i,j}$为包中剩下$i$个白色，$j$个黑色的时候，且A先手的时候，A的获胜概率。

则根据题目条件，可以得出式子：

$f_{i,0} = 1, f_{i,1} =$ $ i \over {i+1}$

$f_{0,j} = 0, ans = f_{w,b}$

再考虑当${i,j}$为任意值的时候，该怎么求$f_{i,j}$。我们从比赛的某一时候进行分析。

1、A先手，一次抽就中了白色，此时A达到此条件的概率为 $i \over {i+j}$

2、A先手，抽到了黑色，轮到B后抽到了白色，A获胜的概率为 $0$。

3、A、B都抽到了黑色，从袋子里跑出了白老鼠，概率为 $ \frac {j}{i+j} \times \frac {j-1}{i+(j-1)} \times \frac {i}{i+(j-2)} \times  f_{i-1,j-2}$ 


4、A、B都抽到了黑色，从袋子里跑出了白老鼠，概率为 $ \frac {j}{i+j} \times  \frac {j-1}{i+(j-1)} \times  \frac {j-2}{i+(j-2)} \times f_{i-1,j-3}$  

所以，我们先预处理$f_{i,0}, f_{i,1}$，再推剩下的推到答案。注意条件4需要$j>2$，否则数组下标会到负数。

```cpp
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
const int maxn = 1e3+5;
typedef long long ll;
int w, b;
double f[maxn][maxn];
int main(){
    scanf("%d%d",&w,&b);
    for(int i = 1; i <= w; ++i){
        f[i][0] = 1.0;
        f[i][1] = 1.0*i/(i+1);
    } 
    if(!b || b == 1) goto print;
    for(int i = 1; i <= w; ++i){
        for(int j = 2; j <= b; ++j){
            f[i][j] = (1.0*i)/(j+i) + (1.0*j)/(j+i) * (1.0*j-1)/(j+i-1) * (1.0*i)/(j+i-2) * f[i-1][j-2];
            if(j^2) f[i][j] += (1.0*j)/(j+i) * (1.0*j-1)/(j+i-1) * (1.0*j-2)/(j+i-2) * f[i][j-3];
        } 
    }
    print: printf("%.15lf\n", f[w][b]);
    end: return 0;
}
```

---

## 作者：lx_zjk (赞：2)

~~来水一波题解，这有紫？~~

#### upd:修改了markdown。

题意：袋子里有$n$只白鼠和$m$只黑鼠,$A$和$B$轮流从袋子里抓，谁先抓到白色谁就赢。$A$每次随机抓一只，$B$每次随机抓完一只之后会有另一只随机老鼠跑出来。如果两个人都没有抓到白色则$B$赢。$A$先抓，问$A$赢的概率。

题解：我们考虑我们现在有$a$个白鼠，$b$个黑鼠，那么$A$怎样才能胜利？

先考虑边界情况。

如果$a$不为$0$，$b$为$0$，那么$A$先手必定拿的是$a$，那么$A$ $\text{win}$了。

如果$a$为$0$，$b$不为$0$，那么只能抽到$b$，那么$B$ $\text{win}$了。

如果$a$为$0$，$b$为$0$，那么$B$ $\text{win}$了。

考虑完了边界情况，进而考虑正常情况下$A$赢的概率。

$A$一发入魂，直接抽到了$a$，那么$A$就赢了，其概率就是$\frac{a}{a+b}$

$A$抽到了$b$，$B$抽到了$b$，逃出去的是$a$，那么$A$赢得概率就是$\frac{b}{a+b}\frac{b-1}{a+b-1}\frac{a}{a+b-2}f(a-1,b-2)$

$A$抽到了$b$，$B$抽到了$b$，逃出去的是$b$，那么$A$赢得概率就是$\frac{b}{a+b}\frac{b-1}{a+b-1}\frac{b-2}{a+b-2} f(a,b-3)$

其他的就必然是是$B$获胜，这样我们就可以写出一个记忆化搜索的代码。

```cpp

inline double dp (int a, int b) {
    if (vis[a][b]) return f[a][b];
    if (!b && a) return 1;
    if (!a && b) return 0;
    if (!a && !b) return 0;
    vis[a][b] = 1;
    if (b >= 3) f[a][b] += (1.0 * (b * (b - 1) * (b - 2)) / (1.0 * (a + b) *  (a + b - 1) * (a + b - 2))) * dp (a, b - 3);
    if (b >= 2 && a >= 1) f[a][b] += (1.0 * (b * (b - 1) * a) / (1.0 * (a + b) * (a + b - 1) * (a + b - 2))) * dp (a - 1, b - 2);
    f[a][b] += 1.0 * a / (a + b);
    return f[a][b]; 
}

```



---

## 作者：Phoenix030821 (赞：2)

## 第一道AC的概率DP题，庆祝一下~

首先分析一下，如果只剩黑的那么必负，如果只剩白的就必胜
所以处理一下边界：
```
for(int x=1;x<=w;x++)f[x][0]=1;
for(int y=0;y<=b;y++)f[0][y]=0;//f[0][0]是谁也没摸到白的，必负
```

### 之后就开始分情况讨论：

如果直接摸到白的，那么必胜
如果摸到黑的，分三种情况：
1.对方摸到白的，必负
2.对方摸到黑的，掉一个白的
3.对方摸到黑的，掉一个黑的

第一种情况获胜概率是0，所以不用加
第二种要用f[x-1][y-2]乘情况出现的概率
第三种要用f[x][y-3]乘情况出现的概率
#### 加起来就OK了~

cpp代码如下：

```
#include<bits/stdc++.h>
#define dd *1.0
using namespace std;
int w,b;
double f[1100][1100];
int main(){
	cin>>w>>b;
	for(int x=1;x<=w;x++)f[x][0]=1;
	for(int y=0;y<=b;y++)f[0][y]=0;
	for(int x=1;x<=w;x++){
	    for(int y=1;y<=b;y++){
			f[x][y]=(x)dd/(x+y)dd;
			if(y>=3)f[x][y]+=f[x][y-3]*((y)dd/(x+y)dd)*((y-1)dd/(x+y-1)dd)*((y-2)dd/(x+y-2)dd);
			if(y>=2)f[x][y]+=f[x-1][y-2]*((y)dd/(x+y)dd)*((y-1)dd/(x+y-1)dd)*((x)dd/(x+y-2)dd);
		}
	}
	printf("%.9lf",f[w][b]);
	return 0;
}
 ```
 
 

---

## 作者：LiftingTheElephant (赞：0)

那么多DP的，来一个记忆化搜索。    
首先定义$dfs(w,b)$为有$w$只白鼠，$b$只黑鼠时$A$赢的期望。    
我们又定义$E(w,b)=w/(w+b)$

显然$w<0$或$b<0$时无意义，返回$0$。    
当$w=0$时，无论如何都会败，返回$0$。    
当$b=0$时，无论如何都会胜，返回$1$。   
如果当前状态已经被访问过，直接返回值。
若以上都不满足，则

$dfs(w,b)=E(w,b)+
E(b,w)×E(b-1,w)×E(b-2,w)×dfs(w,b-3)+
E(b,w)×E(b-1,w)×E(w,b-2)×dfs(w-1,b-2)$

也就是说，它的期望是：$A$拿白鼠+$A$$B$都拿黑鼠，逃跑一黑鼠+$A$$B$都拿黑鼠，逃跑一白鼠。    
代码如下：
```cpp
double dfs(int w,int b)
{
	if(w<0||b<0)
		return 0;
	if(w==0)
		return 0;
	if(b==0)
		return 1;
	if(dp[w][b])
		return dp[w][b];
	dp[w][b]=E(w,b)+E(b,w)*E(b-1,w)*E(b-2,w)*dfs(w,b-3)+E(b,w)*E(b-1,w)*E(w,b-2)*dfs(w-1,b-2);
	return dp[w][b];
}
```


---

