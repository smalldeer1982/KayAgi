# Vitamins

## 题目描述

Berland shop sells $ n $ kinds of juices. Each juice has its price $ c_i $ . Each juice includes some set of vitamins in it. There are three types of vitamins: vitamin "A", vitamin "B" and vitamin "C". Each juice can contain one, two or all three types of vitamins in it.

Petya knows that he needs all three types of vitamins to stay healthy. What is the minimum total price of juices that Petya has to buy to obtain all three vitamins? Petya obtains some vitamin if he buys at least one juice containing it and drinks it.

## 说明/提示

In the first example Petya buys the first, the second and the fourth juice. He spends $ 5 + 6 + 4 = 15 $ and obtains all three vitamins. He can also buy just the third juice and obtain three vitamins, but its cost is $ 16 $ , which isn't optimal.

In the second example Petya can't obtain all three vitamins, as no juice contains vitamin "C".

## 样例 #1

### 输入

```
4
5 C
6 B
16 BAC
4 A
```

### 输出

```
15
```

## 样例 #2

### 输入

```
2
10 AB
15 BA
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
10 A
9 BC
11 CA
4 A
5 B
```

### 输出

```
13
```

## 样例 #4

### 输入

```
6
100 A
355 BCA
150 BC
160 AC
180 B
190 CA
```

### 输出

```
250
```

## 样例 #5

### 输入

```
2
5 BA
11 CB
```

### 输出

```
16
```

# 题解

## 作者：ZigZagKmp (赞：20)

很好奇题目难度怎么这么不合实际……

### 题意分析
>Berland商店出售n种果汁。每种果汁都有它的价格 Ci 。每种果汁都含有一些维生素。有三种类型的维生素：维生素“A”，维生素“B”和维生素“C”。每种果汁中都含有一种，两种或所有三种维生素。

>Petya知道他需要所有三种维生素才能保持健康。Petya为获得所有三种维生素而必须购买的果汁的最低总价是多少？Petya如果购买至少一种含有它的果汁并饮用它，就会获得一些维生素。

听说我们学校有一个巨佬用暴力AC了这一题（没错，就是楼上的这一位），但是如果不只是3种维生素，而是10种，这种方法就很冗长了。

我的做法是背包+状压。将维生素`A`当做``001``，维生素`B`当做``010``，维生素`C`当做``100``，目标：求出状态为``111``的最小代价。

背包的核心代码如下：
```cpp
for(register int i=1;i<=n;++i){//pv数组表示每一瓶饮料可提供的状态
	for(register int j=7;j>=0;--j){
		f[j|pv[i]]=min(f[j|pv[i]],f[j]+w[i]);
	}//注意这里的|，两瓶饮料同时使用，结果是它们的并集，所以是|
}
```
时间复杂度为$O(n)$

----

下面就贴代码了：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 1005
int n,w[maxn],pv[maxn];
int f[8];
int main(){
	char c;
	memset(f,0x3f,sizeof(f));
	f[0]=0;//这里的初始化一定要加上
	scanf("%d",&n);
	for(register int i=1;i<=n;++i){
		scanf("%d ",&w[i]);
		while(scanf("%c",&c)&&c!='\n'){
			switch(c){
				case 'A':pv[i]|=1;break;
				case 'B':pv[i]|=2;break;
				case 'C':pv[i]|=4;break;
			}
		}
	}
	for(register int i=1;i<=n;++i){
		for(register int j=7;j>=0;--j){//对8种状态的枚举
			f[j|pv[i]]=min(f[j|pv[i]],f[j]+w[i]);
		}
	}
	printf("%d\n",f[7]==0x3f3f3f3f?-1:f[7]);
	return 0;
}
```

---

## 作者：览遍千秋 (赞：15)

## 吐槽

这题目难度假的吧

---

我们可以非常暴力的来做这一题，分别记录下``A``、``B``、``C``、``AB``、``AC``、``BC``、``ABC``几种维生素所需要的最小费用。

然后显然有几种组合方式，取最小值即可。

注意：``AC``、``BC``这类的也是可行方案，可以参见最后一个样例。

---

代码：

```
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;

#define maxn 1007
#define INF 99999999
int am=INF,bm=INF,cm=INF,abm=INF,acm=INF,bcm=INF,abcm=INF,ans,n,c;
string s;
int mian()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&c);
		cin>>s;
		if(s=="A") am=min(am,c);
		else if(s=="B") bm=min(bm,c);
		else if(s=="C") cm=min(cm,c);
		else if(s=="AB") abm=min(abm,c);
		else if(s=="BA") abm=min(abm,c);
		else if(s=="AC") acm=min(acm,c);
		else if(s=="CA") acm=min(acm,c);
		else if(s=="BC") bcm=min(bcm,c);
		else if(s=="CB") bcm=min(bcm,c);
		else abcm=min(abcm,c);
	}
	ans=min(abcm,min(am+bm+cm,min(abm+cm,min(acm+bm,min(bcm+am,min(abm+bcm,min(abm+acm,acm+bcm)))))));
	if(ans>=INF) puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```

---

## 作者：周子衡 (赞：9)

思想：动态规划

我们记$ans[i][A][B][C]$为对于前$i$个物品，得到所需元素所花的最小费用（其中$A,B,C$是布尔型值，代表需不需要对应元素，为1需要，为0则不需要）。

讨论取不取第$i$个物品：

不取：最小值为$ans[i-1][A][B][C]$

取：显然对于每种元素，只有当需要这个元素且第$i$个物品没有该元素时，才需要在前$i-1$个物品中取。故最小值为$ans[i-1][a][b][c]+price[i]$（其中$a,b,c$为根据上面分析出取或不取的情况）。

两种取最小值即可。

另外，可以加一个类似01背包的空间优化。

代码：

```cpp

#include<cstdio>
#include<cstring>

using namespace std;

#define minn(a,b)((a)<(b)?(a):(b))

struct jui
{
    int prc;
    bool a,b,c;
}all[1001]={};

char tmp[4]={};

const long long MAXN=1e15;

long long ans[2][2][2]={};

int main()
{
    int n=0;
    scanf("%d",&n);
    for(int i=1,len=0;i<=n;i++)
    {
        scanf("%d%s",&all[i].prc,tmp);
        len=strlen(tmp);
        for(int j=0;j<len;j++)
        {
            switch(tmp[j])
            {
                case 'A':
                    all[i].a=true;
                    break;
                case 'B':
                    all[i].b=true;
                    break;
                case 'C':
                    all[i].c=true;
                    break;
            }
        }
    }
    

    ans[0][0][0]=0;
    ans[0][0][1]=ans[0][1][0]=ans[1][0][0]
    =ans[0][1][1]=ans[1][0][1]=ans[1][1][0]
    =ans[1][1][1]=MAXN;
    for(int i=1;i<=n;i++)
    {
        for(int A=1;A>=0;A--)
        {
            for(int B=1;B>=0;B--)
            {
                for(int C=1;C>=0;C--)
                {
                    ans[A][B][C]=
                    minn(ans[A][B][C],
                    ans[A&&!all[i].a][B&&!all[i].b][C&&!all[i].c]+all[i].prc);
                }
            }
        }
    }
    if(ans[1][1][1]>=MAXN)
    {
        printf("-1");
    }
    else
    {
        printf("%lld",ans[1][1][1]);
    }
    return 0;
}
```

---

## 作者：Viston (赞：2)

暴力贪心即可。   
为什么说是暴力贪心呢？    
因为是暴力判断情况。   
```
#include<bits/stdc++.h>
using namespace std;
long long a,b[10][100002],c,d[12],i,j,m,n,o;
int main(){
	cin>>a;
	for(i=1;i<=a;i++){
		string s;cin>>c>>s;
		if(s=="A") d[1]++,m=1,b[1][d[1]]=c;
		else if(s=="B") d[2]++,n=1,b[2][d[2]]=c;
		else if(s=="C") d[3]++,o=1,b[3][d[3]]=c;
		else if(s=="AC"||s=="CA") d[5]++,m=1,o=1,b[5][d[5]]=c;
		else if(s=="AB"||s=="BA") d[4]++,m=1,n=1,b[4][d[4]]=c;
		else if(s=="BC"||s=="CB") d[6]++,n=1,o=1,b[6][d[6]]=c;
		else if(s=="ABC"||s=="BAC"||s=="ACB"||s=="CAB"||s=="CBA"||s=="BCA") d[7]++,m=1,o=1,n=1,b[7][d[7]]=c;   //暴力分为七种情况
	}
	if(m==1&&n==1&&o==1){
		long long ans=10e15;
		for(i=1;i<=7;i++)
			for(j=1;j<=d[i];j++)
				for(int k=2;k<=d[i];k++)
					if(b[i][k]<b[i][k-1])
						swap(b[i][k],b[i][k-1]);//冒泡排序
		if(b[1][1]!=0&&b[2][1]!=0&&b[3][1]!=0)//很容易就看出来的情况
			ans=min(ans,b[1][1]+b[2][1]+b[3][1]);//cout<<ans<<'\n';
		if(b[4][1]!=0&&b[3][1]!=0)
			ans=min(ans,b[4][1]+b[3][1]);//cout<<ans<<'\n';
		if(b[5][1]!=0&&b[2][1]!=0)
			ans=min(ans,b[5][1]+b[2][1]);//cout<<ans<<'\n';
		//cout<<b[1][1]<<' ';
		if(b[6][1]!=0&&b[1][1]!=0)
			ans=min(ans,b[1][1]+b[6][1]);
		//cout<<ans<<'\n';
		if(b[7][1]!=0)
			ans=min(ans,b[7][1]);
		if(b[4][1]!=0&&b[5][1]!=0)//后面的是我比赛时交了一遍WA后发现的情况，可千万要注意
			ans=min(ans,b[4][1]+b[5][1]);
		if(b[4][1]!=0&&b[6][1]!=0)
			ans=min(ans,b[4][1]+b[6][1]);
		if(b[6][1]!=0&&b[5][1]!=0)
			ans=min(ans,b[6][1]+b[5][1]);
		cout<<ans;//输出
	}
	else cout<<-1;//如果没有ABC中的一种，输出-1 即可
	return 0;
}//真不像是蓝题
```

---

## 作者：Dog_Two (赞：2)

你谷用户对新题目的难度有点不友好啊。

截止2018-09-18 17:07，题目难度为[提高+/省选-]

令f[j,k,l]为购买了总共含j份维生素A，k份维生素B，l份维生素C所需要的最低花费。

又因为**最多买三杯**即可使得ABC都被覆盖，所以j,k,l<=3（经过分析，其实j,k,l的上界是2）。

所以只需要一个O(k^3*n)(k=2或3)的0-1背包过程就可以求解了.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int n;
bool V[maxn][4];
int cost[maxn];
int f[4][4][4];
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		string s; cin>>cost[i]>>s;
		for(int j=0;j<s.size();++j){
			V[i][1]|=s[j]=='A',
			V[i][2]|=s[j]=='B',
			V[i][3]|=s[j]=='C';
		}
	}
//	for(int i=1;i<=n;++i) printf("%d %d %d %d\n",cost[i],V[i][1],V[i][2],V[i][3]);
	memset(f,0x3f,sizeof(f));
	f[0][0][0]=0;
	for(int i=1;i<=n;++i)
		for(int j=3;j>=0;--j) if(j-V[i][1]>=0)
			for(int k=3;k>=0;--k) if(k-V[i][2]>=0)
				for(int l=3;l>=0;--l) if(l-V[i][3]>=0)
					f[j][k][l]=min(f[j][k][l],f[j-V[i][1]][k-V[i][2]][l-V[i][3]]+cost[i]);
	int ans=INT_MAX;
	for(int i=1;i<=3;++i)
		for(int j=1;j<=3;++j)
			for(int k=1;k<=3;++k)
				ans=min(ans,f[i][j][k]);
	cout<<(ans==0x3f3f3f3f?-1:ans);
	return 0;
}
```

---

## 作者：SIXIANG32 (赞：1)

纪念本人这周绿钩的题解 qwq  
很久以前教练拿这道题给我做，当时我菜死了，用各种手段套到数据写了一份非常容易 Hack 的贪心。在 CF 上闲逛的时候偶然发现了这道题，决定做一下。  
这篇题解是给初学者看的，大佬请自动跳过  
闲话少说，切入正题：  

---
看到这道题，第一反应是状压 dp。  
把 $\texttt{A}$ 压成 $(100)_2$，$\texttt{B}$ 压成 $(010)_2$，$\texttt{C}$ 压成 $(001)_2$  

根据这样的规则，有了字符，字符串就是几个字符的二进制累加起来。

所以我们以 $k_i$ 为状压后的字符串，这是转换部分的代码：  
```cpp
void get_base_two(int i,string str)//i 是位置，str 是字符串
{
	int ans=0;
	for(int p=0;p<str.size();p++)
		if(str[p]=='A')ans=ans+(1<<2);//<<
 是左移，这里表示二进制左移 2 位，就是 (100)_2，就是 (4)_10
		else if(str[p]=='B')ans=ans+(1<<1);//同上
		else if(str[p]=='C')ans=ans+(1<<0);//同上
	k[i]=ans;
}
```

状压的精髓就在于将一个难以表示的状态转化成一个二进制数。  

---
我们已经状压好了，开始 dp  

建立一个一维数组 $f$ 表示状态，$f_i$ 表示当前二进制串（状压后的字符串）为 $i$ 时，最少的花费。

然后我们要初始化。因为只有 $7$ 个状态，是求最小值，所以我们每个都赋值为 $0x3f3f3f3f$ 就行了。  

代码：  
```cpp
for(int p=1;p<=7;p++)
		f[p]=INF;
```

这个时候我们就要开始写 dp 的框架了。  
第一层枚举的一般都是物品，第二层一般枚举二进制串。  
长这样：  
```cpp
for(int p=1;p<=n;p++)
		for(int i=7;i>=0;i--)//二进制串是从 7（111）到 0（000）
```

下面就是方程。  
首先我们需要知道一个道理，$x|y$ （$|$ 是位运算的或，两个位有一个为 $1$ 就是 $1$）就是两个二进制串的并集，这个很好想，稍微懂点脑子就可以了。  

所以我们每次可以更新 $f_{i|k_p}$，这就表示选择 $p$ 个物品时刚好二进制串是 $i$ 的最大值。

然后我们每次都会有两种状态，选择这个物品和不选择这个物品对吧。  

最好考虑的，如果不选择这个物品，$f_{i|k_p}$ 还是 $f_{i|k_p}$，所以是 $f_{i|k_p}$。  

如果是选择这个物品呢？那么应该是 $f_i+v_p$（$v_p$ 是价格），为什么呢？我们更新的是 $f_{i|k_p}$ ，这是已经处理过的，但是没处理过的呢？就无法或上一个 $k_p$，也就是只剩下 $i$，所以说是 $f_i$。算上 $p$ 的话价值肯定要加上，所以是 $f_i+v_p$  

方程写出来了：  
$f_{i|k_p}=\min(f_{i|k_p},f_i+v_p)$  

代码：  
```cpp
for(int p=1;p<=n;p++)
		for(int i=7;i>=0;i--)
			f[i|k[p]]=min(f[i|k[p]],f[i]+v[p]);
```

最后我们要输出答案  
```cpp
cout<<((f[7]==INF)?(-1):(f[7]))<<endl;
//f[7]==INF 是判断无解，这个时候无法 | 变成 (111)_2，更新不了 f[7]，所以是 INF
```

完结撒花~ 

---

## 作者：km_xyx (赞：1)

### 蒟蒻来临！！！！！！

~~（p.s:一道水搜索）~~

这题，一个DFS剪枝就能AC

~~话说这题值蓝吗~~

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int v;bool va,vb,vc;
}a[100001];//结构体，一种果汁有价钱，哪种维生素
//蒟蒻的暴力
string z;int ans=100000000;//ans定初值（大）
bool v1,v2,v3;
#define ava a[zt].va
#define avb a[zt].vb
#define avc a[zt].vc//宏定义，（这是我在机房的源码，QAQ）
void dfs(int m,bool a1,bool a2,bool a3,int zt){//爆搜，当前状态
	if((zt-1)>n) return;//已经不符合
	if(a1==true&&a2==true&&a3==true){//有解，看是否是最优解
		ans=min(ans,m);
		return;
	}
	if((a1==ava&&a2==avb&&a3==avc)||(a1==true&&a2==avb&&a3==avc)||(a1==true&&a2==true&&a3==avc)||(a1==ava&&a2==true&&a3==avc)||(a1==ava&&a2==true&&a3==true)||(a1==ava&&a2==avb&&a3==true)||(a1==true&&a2==avb&&a3==true)){
		dfs(m,a1,a2,a3,zt+1);
		return;
	}
//超长剪枝（思路：如果已有这种维生素，就不买）
	dfs(m,a1,a2,a3,zt+1);
	dfs(m+a[zt].v,a1+ava,a2+avb,a3+avc,zt+1);
//否则，全试试
}
int main(){
//	freopen("vitamins.in","r",stdin);
//	freopen("vitamins.out","w",stdout);
//当时的文件
	scanf("%d",&n);
	for(register int i=1;i<=n;++i){
		scanf("%d",&a[i].v);
		cin>>z;
		for(register int j=0;j<z.size();++j){
			if(z[j]=='A') a[i].va=true;
			if(z[j]=='B') a[i].vb=true;
			if(z[j]=='C') a[i].vc=true;
		}//字符串处理
	}
	dfs(0,false,false,false,1);//爆搜
	if(ans==100000000) printf("-1");//不存在
	else printf("%d",ans);
//	fclose(stdin);
//	fclose(stdout);
	return 0;//终于写完了(hhhh)
}
```


---

## 作者：wky32768 (赞：1)

这题使用状压DP，因为只有三种元素，所以可以找出单个物品所有情况的最优解。然后合并，维生素相当于把两个值或起来，最后三种维生素都存在的值就是答案。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace sxd;
int n, w[120000], life[120000], dp[9];
char ch[120];
signed main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=7;i++) dp[i]=0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> ch;
        for (int j = 0; j <(int)strlen(ch); j++) {
            if (ch[j] == 'A') life[i] |= 1;
            if (ch[j] == 'B') life[i] |= 2;
            if (ch[j] == 'C') life[i] |= 4;
        }
        dp[life[i]]=min(dp[life[i]],w[i]);
    }
    for(int i=0;i<=7;i++)
        for(int j=0;j<=7;j++)
            dp[i|j]=min(dp[i|j],dp[i]+dp[j]);
    if(dp[7]<0x3f3f3f3f) cout<<dp[7];
    else cout<<"-1";
    return 0;
}
```

---

## 作者：sinsop90 (赞：0)

看完题面, 我们可以直接想到一个深搜的做法, 但显然如果不加优化, 是完全过不了的

但是深搜有几个要注意的点:

1.我们要将获得的 $Vitamins$ 记录下来, 要注意如果我们本来有 $A$, 然后取得了 $AB$ 我们要把这次获取的删掉时, 我们要把 $B$ 删掉而不是 $AB$ 一起删掉

2.如果现在的价钱已经大于我们找到了的 $ans$ , 直接 $return$ 即可

3.显然这道题需要状态反转

于是我们得到了以下代码：

```
#include <bits/stdc++.h>
using namespace std;
bool vis[5], visn[100005];
int ans = 2147483647, n;
struct node{
	int x;
	char mps[10];
}e[200005];
void dfs(int x) {
	if(vis[0] == true && vis[1] == true && vis[2] == true) {//是否都有了
		ans = min(ans, x);
		return;
	}
	for(int i = 1;i <= n;i++) {
		if(!visn[i] && x + e[i].x < ans) {//关键的优化,如果价钱超过或等于ans, 最后的价钱一定大于或等于ans, 直接跳掉
			int k = 0;
			char visp[5];
			for(int j = 0;j <= strlen(e[i].mps) - 1;j++) {
				if(vis[e[i].mps[j] - 'A'] == false) { 
					vis[e[i].mps[j] - 'A'] = true;
					visp[++k] = int(e[i].mps[j] - 'A');//记录那些本来没有的
				}
			}
			visn[i] = true;
			dfs(x + e[i].x);
			for(int j = 1;j <= k;j++) {
				vis[visp[j]] = false;//将本来没有的删掉, 保留本来有的
			}
			visn[i] = false;//状态反转
		}
	}
}
int main() {
	cin >> n;
	for(int i = 1;i <= n;i++) {
		cin >> e[i].x >> e[i].mps;
	}
	dfs(0);
	if(ans == 2147483647) cout << -1 << endl;//判断无解
	else cout << ans << endl;
}
```


---

## 作者：Yusani_huh (赞：0)

此题解仅当充数。

这题正解用背包是很明显的，但机房一众巨佬都用爆搜过了...

我这道题用了三天死扯出一个背包（尽管这个背包很玄学又很模糊不清）

咱不说那些令人伤心的事情。

首先只把这题当普通的 01 背包来看。背包的容量在这里为数据上限 $10^5 \times 3$。

那么为什么乘上 $3$？

其实稍微想想就可得。既然说要集齐三种维生素，又要求答案最小，那么含有相同维生素的饮料我们就只选择一种喝。

按照上述思路，想集齐三种维生素，最多需要三种果汁就行，容量自然就是 $3 \times 10^5$。

但是每次都从 $3 \times 10^5$ 开始往前 DP，面对如此数据难免会 TLE，所以我们设一个变量存储当前得到价值的最大量，随着输入更新。

按照“含有相同维生素的饮料我们只选择一种喝”的思想，可以对 DP 过程进行一些玄学优化。

这里简要介绍一下状态压缩和位运算。

状态压缩简单说就是，假如你有一个布尔型数组，你可以使用二进制来把这个数组存储的信息压缩到一个变量里。

具体怎么做呢？

假设你的数组长这样：`{true,true,false,true}`，你就可以用`1`代替`true`，`0`代替`false`，把数组记作`1101`，转换成十进制即为 $13$。这样你就用一个变量存储了一个数组！是不是很棒？

你会问了：既然我已经状态压缩了，怎么再对数组进行操作呢？

这就要用到——神奇的位运算！

关于位运算，可以去看专门讲解的博客，这里就不再赘述，只介绍一下接下来会用到的运算符：按位与`&`和按位或`|`。

这里有两个二进制数字：`0110`，`1101`，分别代表十进制的 $6$ 和 $13$。如果我把这俩数进行与运算，就相当于是把两个数字的每一位两两对应分别进行与运算，也就是`0&&1,1&&1,1&&0,0&&1`，结果为`0100`，即十进制的 $4$。或运算也一样，把两个数字的每一位两两对应分别进行或运算，结果为`0||1,1||1,1||0,0||1`，即`1111`，也即十进制的 $15$。

科普时间结束，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,ma,ans=-1;
string s;
struct vtms{
	bool is;int vtm;
}f[300003]; //背包数组
int main(){
	scanf("%d",&n);
	f[0].is=true;
	for(int i=1;i<=n;++i){
		cin>>c>>s;
		int v=0;
		for(int i=0;i<s.length();++i)
			v+=pow(2,s[i]-'A'); //进行状态压缩，存储维生素的种类
		for(int l=ma+c;l>=c;--l)
			if(f[l-c].is){ //如果这个价值能够得到
				int vt=v|f[l-c].vtm; //使用按位或得到这个价值能够获取的维生素
				if(vt>f[l-c].vtm&&vt>f[l].vtm){ //如果比原来多了某种维生素
					f[l].is=true; //那就存下来
					f[l].vtm=vt;
					ma=max(ma,l); //更新当前最大价值
				}
			}
	}
	for(int l=0;l<=ma;++l) //进行筛选
		if(f[l].is&&f[l].vtm==7){ //如果这个价位集齐了所有维生素
			printf("%d\n",l);
			return 0; //输出答案，结束程序
		}
	printf("-1\n"); //没有一个价位能够集齐维生素
	return 0;
}
```

---

## 作者：yfct (赞：0)

暴力的贪心。

题目的目标是要凑出A,B,C三种维生素，并求出最小花费。

我们考虑如何集齐三个维生素：

1. 选取三种果汁，每种各包含一个
2. 选取两种果汁，一种包含一个，另一种包含两个
3. 选取一种果汁，三种维生素都包含
4. 选取两种果汁，每种各包含两个，最终三种维生素都包含，且存在至少一种维生素有多个

对于情况4再来解释一下：
比如AB和BC，他们不仅能凑出ABC，而且维生素B有2个。

我们将果汁按照所含维生素的种类分为以下几个类别：A,B,C,AB,AC,BC,ABC几类。

不难看出，要想使得总费用最小，只需保留每个类别中最便宜的果汁即可，其他的直接扔掉。

最后将所有能够获得的情况取一遍min，即可得到正确答案。

用map会更形象，但慢一些。

以上。

[书海扬帆的博客](www.ljhedp.cn)
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
int n;
ll ans;
bool ea,eb,ec;
ll a,b,c,ab,bc,ac,abc;
int main() {
	//A;B;C;AB;BC;AC;ABC;
	a=b=c=ab=bc=ac=abc=ans=2147483647;
	cin>>n;
	for(int i=1;i<=n;i++) {
		ll opt=0;char s[10];
		cin>>opt;
		scanf("%s",s);
		int len=strlen(s);
		sort(s,s+len);
		if(s[0]=='A' && len==1) {
			a=min(a,opt);
			ea=true;
		}
		else if(s[0]=='B' && len==1) {
			b=min(b,opt);
			eb=true;
		}
		else if(s[0]=='C' && len==1) {
			c=min(c,opt);
			ec=true;
		}
		else if(s[0]=='A' && s[1]=='B' && len==2) {
			ab=min(ab,opt);
			ea=eb=true;
		}
		else if(s[0]=='B' && s[1]=='C' && len==2) {
			bc=min(bc,opt);
			eb=ec=true;
		}
		else if(s[0]=='A' && s[1]=='C' && len==2) {
			ac=min(ac,opt);
			ea=ec=true;
		}
		else if(s[0]=='A' && s[1]=='B' && s[2]=='C' && len==3) {
			abc=min(abc,opt);
			ea=eb=ec=true;
		}
		else ;
	}
	if(!(ea && eb && ec)) printf("-1\n");
	else {
		ans=min(ans,abc);
		ans=min(ans,ab+bc);
		ans=min(ans,ab+ac);
		ans=min(ans,ac+bc);
		ans=min(ans,a+bc);
		ans=min(ans,b+ac);
		ans=min(ans,c+ab);
		ans=min(ans,a+b+c);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：ztz11 (赞：0)

由题意,我们其实会发现

对于每一种果汁，其对应的状态只有可能有7种

$V_A$  
$V_B$  
$V_C$  
$V_A+V_B$  
$V_A+V_C$  
$V_B+V_C$  
$V_A+V_B+V_C$  
这样这道题就大大简化了

我们把所有果汁都读进来

每种状态取价格最小的（这才有可能最优）

（在这里我状压了一下，用二进制表示其种类）

之后爆搜即可

如果当前已满足（三种维生素都有了，答案就取min）

最后输出即可

## 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rii register int i
#define rij register int j
using namespace std;
int bj[1005],zt[150],n;
long long ans=2147483647;
void dfs(int wz,long long an,int ztz)
{
	if(ztz==7)
	{
		ans=min(ans,an);
		return;
	}
	for(rii=wz+1;i<=7;i++)
	{
		if(zt[i]!=2147483647)
		{
			dfs(i,an+zt[i],ztz|i);
		}
	}
}
int main()
{
	scanf("%d\n",&n);
	for(rii=1;i<=149;i++)
	{
		zt[i]=2147483647;
	}
	for(rii=1;i<=n;i++)
	{
		bj[1]=0;
		bj[2]=0;
		bj[3]=0;
		int ltt;
		int ztz=0;
		scanf("%d ",&ltt);
		char l=getchar();
		while(l!=10)
		{
			if(l=='A'&&bj[1]==0)
			{
				ztz|=1;
				bj[1]=1;
			}
			if(l=='B'&&bj[2]==0)
			{
				ztz|=2;
				bj[2]=1;
			}
			if(l=='C'&&bj[3]==0)
			{
				ztz|=4;
				bj[3]=1;
			}
			l=getchar();
		}
		zt[ztz]=min(zt[ztz],ltt);
	}
	dfs(0,0,0);
	if(ans>=2147483647)
	{
		cout<<"-1";
	}
	else
	{
		cout<<ans;
	}
}
```


---

