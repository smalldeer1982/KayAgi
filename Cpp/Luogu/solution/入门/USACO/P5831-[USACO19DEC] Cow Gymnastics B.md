# [USACO19DEC] Cow Gymnastics B

## 题目描述

为了提高健康水平，奶牛们开始进行体操训练了！Farmer John 选定了他最喜爱的奶牛 Bessie 来执教其他 $N$ 头奶牛，同时评估她们学习不同的体操技术的进度。

$K$ 次训练课的每一次，Bessie 都会根据 $N$ 头奶牛的表现给她们进行排名。之后，她对这些排名的一致性产生了好奇。称一对不同的奶牛是**一致的**，如果其中一头奶牛在每次训练课中都表现得都比另一头要好。

请帮助 Bessie 计算一致的奶牛的对数。

## 说明/提示

一致的奶牛对为 $(1,4)$、$(2,4)$、$(3,4)$ 和 $(1,3)$。

$1 \leq K \leq 10$，$1 \leq N \leq 20$。

供题：Nick Wu

## 样例 #1

### 输入

```
3 4
4 1 2 3
4 1 3 2
4 2 1 3```

### 输出

```
4```

# 题解

## 作者：Talanton_Cerydra (赞：80)

# 这是2019年USACO的第一题

#### （我居然是此题第一篇题解的发布者）

下面简述主要想法：

先开两个二维数组，一个来存储数据，另一个【i】【j】来存储第i天第j头奶牛的排名

再通过暴力来求出个数

/*八卦几句：**（不感兴趣可跳过）**

上次我在我的[一篇题解](https://www.luogu.com.cn/blog/paiwyz314/solution-p1443)中用了[我同学](https://www.luogu.com.cn/user/220359)的名字作变量名，于是他又在[他的题解](https://www.luogu.com.cn/blog/khbzjlwyzdrdbcxqxz/solution-p1588)里用了我的名字……

所以我又要拿他的名字再作一次变量名【嘿嘿！】

*/

### 行了，上代码了：

```cpp
#include <bits/stdc++.h>//不解释了
using namespace std;
int n,k;//输入数据
int zjl=0;//计数器———同学名字（呵呵）
int a[11][21],c[11][21];//a输入数据，c存排名
int main()
{
//读入部分
    scanf("%d%d",&k,&n);//输入k和n
    for(int i=1;i<=k;i++)//双层循环读入
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);//输入a数组
            c[i][a[i][j]]=j;//这里存储第i天第j头奶牛的排名               
        }
    }
    //以下为暴力阶段
    for(int i=1;i<=n;i++)//三层暴力
    {
        for(int j=1;j<=n;j++)
        {
            int cnt=0;//内部计数器
            for(int x=1;x<=k;x++)//枚举每一天
            {
                if(c[x][i]>c[x][j])//如果排名是大于
                {
                    cnt++;
                }
            }
            if(cnt==k)//cnt等于k说明是每一天排名都一致，可以算作是一致的一对
            {
                zjl++;//于是乎，计数器自增
            }
        }
    }
    printf("%d",zjl);//输出“一致的”对数
    return 0;//结束
}
```

大家别急着抢前排，看懂了再说话，**并且禁止抄袭！**

---

## 作者：wrhllll (赞：42)

特别注意！
特别注意！！
特别注意！！！
# **这篇题解很暴力！**
坐着听好：

本代码只有39行！保证每个萌新都看得懂！

思路:

1.头文件（不用说了）

2.定义、读入（不用说了）

3.双重循环枚举出两只奶牛

4.计算排名关系

5.检测排名关系

6.输出

7.完美的结束
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[15][25],b[25][25],c[100010];
int main(){
	int n,k;
	int tot=0,cnt=0;
	cin>>k>>n;
	for(int i=0;i<k;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];//读入
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i!=j){//枚举出任意两只不同的奶牛
				for(int l=0;l<k;l++)
					for(int m=0;m<n-1;m++){
						if(a[l][m]==i){
							for(int o=m+1;o<n;o++)
								if(a[l][o]==j){//如果在某次训练中i奶牛超过了j奶牛
									b[i][j]++;//在b数组中加一
								}
						}
					}
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(b[i][j]==k){//如果i奶牛每次都超过了j奶牛
				tot++;//计数器加1
			}
	cout<<tot;//输出
	return 0;
}
```
又及：喜欢的同志记得在留言处抠个“1”哦！！！

---

## 作者：a1_1 (赞：5)

### P5831 【[USACO19DEC]Cow Gymnastics奶牛体操】
时间复杂度O(n^2*k)

空间复杂度O(n^2)

题目比较简单，直接上码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[25][25];//记a[i][j]为奶牛i比奶牛j的表现好的次数
vector<int>b; 
int main()
{
	int n,k,i,j,l,m,ans=0;
	cin>>k>>n;
	for (i=1;i<=k;i++)
	{ 
		for (j=1;j<=n;j++)
		{
			cin>>m;
		    for (l=0;l<b.size();l++) a[b[l]][m]++;//前面的肯定比后面的表现好,所以次数++
		    b.push_back(m);
		}
		b.clear();
	}
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			ans+=(a[i][j]==k);//如果每次(即k次)奶牛i都比奶牛j表现好,那么答案++
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Ace_Radom (赞：5)

## 这题真的不难。

~~虽然我第一看还没看懂~~。

### 题意分析：

**FarmerJohn** 的奶牛 **Bessie** 负责训练 n 头奶牛。

**Bessie** 每天都会为那 n 头奶牛排名。

它对这个排名十分好奇，想知道在训练的 k 天中，有几对奶牛是一致的。

### 做法+算法分析：

	题目就是要求有几对奶牛，前一头奶牛的排名一直比后一头高。
    
又因为数据较水，用**暴力**就行了。

读入不用讲，二重循环读入。

在处理排名的过程中我用了结构体，看起来~~方便一点~~。

#### 这里不需要像一些 dalao 一样用二维数组，一个变量足矣。

每读入一个排名，便将它誊到结构体中，再用循环暴力枚举即可。

### 代码：

~~~C++
#include<bits/stdc++.h>
using namespace std;
struct Cow{
    int Data[11];
}Cc[21];
// Cc 对应每一头奶牛，Data 数组对应每天的排名。
int main(){
    int k,n;
    cin >> k >> n;
    for ( int i = 1 ; i <= k ; i++ )
    {
        for ( int j = 1 ; j <= n ; j++ )
        {
        	int t;
            cin >> t;
            //读入第 i 天的第 j 名
            Cc[t].Data[i] = j;
            //誊写，第 t 头奶牛在第 i 天是第 j 名
        }
    }
    int ans = 0;
    //后面是暴力枚举
    for ( int i = 1 ; i <= n ; i++ )
    {
        for ( int j = 1 ; j <= n ; j++ )
        {
            //枚举两头奶牛
            bool b = false;
            for ( int l = 1 ; l <= k ; l++ )
            {
                //枚举第 l 天
                if ( Cc[i].Data[l] <= Cc[j].Data[l] )  //出现了第一头奶牛排名在第二头奶牛后的情况
                {
                    b = true;
                    continue;  //跳出
                }
            }
            if ( !b )
            {
                ans++;  //符合条件，计数器+1
            }
        }
    }
    cout << ans << endl;
    return 0;
}
~~~

---

## 作者：Moon_Goddy (赞：4)

### 蒟蒻~~来水篇题解~~
呐，思路如下：  
定义q[20][20]来做判断。
由于求一致奶牛对数，所以a奶牛一次低于b奶牛则求q[a][b]不成立，**但这并不代表q[b][a]不成立**。所以在判断之后输出数量就好啦！（记得q[a][a]不成立，我是被这个卡了好久呜呜呜） 代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int k,n,a[10]//k[20]//n;
   bool q[20][20]={}//判断;
	cin>>k>>n;
	for(int i=0;i<k;++i){
	   for(int j=0;j<n;++j){
	      cin>>a[i][j];//输入
      }
   }
	for(int i=0;i<k;++i){
		for(int j=0;j<n;++j){
		    for(int w=j+1;w<n;w++){
		    	q[a[i][w]-1][a[i][j]-1]=1;
			}
		}
	}
	int s=0;//计数器
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(q[i][j]==0&&i!=j//奶牛不可相同){
			s++;	
			}
		}
	}
	cout<<s;
	return 0;
}
```





---

## 作者：AgrumeStly (赞：3)

# 欢迎

欢迎来到_TNT_ BOOM大讲堂

相信大家都知道，本题是今年$USACO$铜牌组的第一道题。

首先我们理下思路，

我们可以先定义一个二维数组$Flag$,当第$a[i]$只奶牛排在第$a[j]$之奶牛前面时，我们就可以将$flag[a[i]][a[j]]++$,最后在程序末判断，当$flag[a[i]][a[j]] = n$时，$ans++$, 最后输出$ans$。

下面我们看下$AC$代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int k, n;
int a[25]; 
int flag[30][30], cnt = 1;
int main()
{
	//freopen("gymnastics.in", "r", stdin);
	//freopen("gymnastics.out", "w", stdout);
	scanf("%d%d", &k, &n);
	for(int i = 1; i <= k; i++)
	{
		for(int j = 1; j <= n; j++)
			scanf("%d", &a[j]);//输一次，判断一次
		for(int j = 1; j <= n; j++)
			for(int k = j; k <= n; k++)
				if(j < k) flag[a[j]][a[k]]++;//当j 在 k前面时，flag[a[j]][a[k]]++
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(flag[i][j] == k) ans++;//当flag[i][j]这种排列的数等于k次训练课时，ans++
	printf("%d\n", ans);//输出ans
	return 0;
}

```
今天就讲到这里！

# $Bye Bye!$

---

## 作者：DJHJJY (赞：2)

鄙人也来发波题解

看到题目后我们可以想到来用一个二维数组做

每输入一行就在二维数组里操作一下，

具体看代码

```c
#include<bits/stdc++.h>
using namespace std;
int ans,a[100],b[100][100],n,m;//b来判断超过多少次
int main()
{
	//freopen("gymnastics.in","r",stdin);
	//freopen("gymnastics.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[j];
		}
		for(int x=1;x<m;x++)//读入后开始操作
		{
			for(int z=x+1;z<=m;z++)
			b[a[x]][a[z]]++;//每个超过的都加一下
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(b[i][j]==n)ans++;//如果超过n次，则证明每次都超过，ans++.
		}
	}
	cout<<ans<<endl;
	return 0;//华丽输出
}
```


---

## 作者：Real_Create (赞：2)

因为普及还剩几个毒瘤任务，所以我时隔班年又来刷水题了！

看到题目标签，枚举？

看完题目，这要几重循环啊！！！

看到≤20

暴力！

代码和注释

```cpp
#include <bits/stdc++.h>
using namespace std;
#define qwq return 0;
#define QAQ int main()
bool a[25][25];//这个是计算现在着两头奶牛还合不合法
QAQ
{
	int n,k;
	cin>>k>>n;
	int ans=n*n-n;//现在的对数
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=1;//憨批初始化
		}
	}
	for(int i=0;i<k;i++)
	{
		int t[n];
		for(int j=0;j<n;j++)
		{
			cin>>t[j];
			for(int tt=0;tt<j;tt++)
			{
				ans-=a[t[j]][t[tt]];//可以用if代替
				a[t[j]][t[tt]]=0;//把它变成0，不然就重复减惹
			}
		}
	}
	cout<<ans;//简单的输出
	qwq
}


```

---

## 作者：HohleFeuerwerke (赞：1)

#### 前言

第一眼看到这题：窝淦窝这什么神奇的数据范围？暴力啊，随便水。

目前保持[最优解](https://www.luogu.com.cn/record/28599276)，欢迎来打破。

[题目链接，戳我倒退。](https://www.luogu.com.cn/problem/P5831)

#### 正文

本题是一道水题。

我们珂以建一个结构体：cow来存储每个牛每次的排名。  
然后通过这些结构体写一个函数来判断是不是**一致的**。


代码复杂度：$O(n^2k)$，由于$n<20$且$k<10$所以珂以通过。

以下为代码。

```cpp
#include<bits/stdc++.h>//万能头文件
#define MAXK 15//最大k用于建立数组
#define MAXN 25//最大n用于建立数组
using namespace std;
int n,k;//含义如题
struct cow{//结构体cow
	int rk[MAXK];//每次的排名。
}a[MAXN];
int ans;//答案
bool same(cow a,cow b){//用于判断两头牛是否是一致的。
	int agood=false,bgood=false;//agood表示a是否有一次rk比b高，同理可推得bgood的定义。
	for(int i=1;i<=k;i++)//每次课程进行比较
		if(a.rk[i]<b.rk[i])//如果a的排名比b高
			agood=true;//agood为true
		else if(a.rk[i]>b.rk[i])
			bgood=true;//bgood为true
	if(agood){//如果agood为true，代表a起码有一次rk比b高。
		if(bgood)return false;//如果b也有比a高的，则不为一致的
		if(!bgood)return true;//为一致的。
	}
	if(bgood) return true;//由于agood&&bgood判断过了，所以一旦bgood，agood一定为false。直接返回true
}
int main(){
	ios::sync_with_stdio(false);
	cout.tie(0);cin.tie(0);
	cin>>k>>n;//读入
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++){
			int tmp;cin>>tmp;
			a[tmp].rk[i]=j;
		}
    //读入
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)//逐个选牛
			if(same(a[i],a[j]))//如果有两头牛是一致的
				ans++;//答案加一。
	cout<<ans<<endl;//输出
}
```

---

## 作者：星辰一心 (赞：0)

我的思路是以牛为对象，建立每头牛的成绩数组。然后每两头牛两两比较，分为正向和反向比较，最后得到结果。
（就像一个班里的人竞争奖学金，肯定要先以人为对象，搞清楚每个人每次的考试成绩，然后两两比较得出结果。）
```cpp
#include <iostream>
using namespace std;
int main(void)
{
	int k,n;
	cin>>k>>n;
	
	//输入排名矩阵。 
	int rand[k][n];
	for(int i=0;i<k;i++)
		for(int j=0;j<n;j++)
			cin>>rand[i][j];
	
	//建立编号为（rand[i][j]）的牛第（i+1）次的排名：j+1。 
	int score[n][k];
	for(int i=0;i<k;i++)
		for(int j=0;j<n;j++)
		{
			int temp=rand[i][j]-1;
			score[temp][i]=j;
		}
	
	//从此rand矩阵失去意义。 
	
	int sum=0;
	int swit=1;
	int m=0;
	
	//将n头奶牛两两比较，正向比较（n-1)!对。 
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
		{
			swit=1;
			
			for(m=0;m<k;m++)
				if(score[i][m]<score[j][m])
				{
					swit=0;
					break;
				}
			
			if(1==swit)//"一致。"
			{
				sum++;
				
			}
		}
	
	//将n头奶牛两两比较，这次是反向比较（n-1)!对！ 
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
		{
			swit=1;
			
			for(m=0;m<k;m++)
				if(score[i][m]>score[j][m])
				{
					swit=0;
					break;
				}
			
			if(1==swit)//"一致。"
			{
				sum++;
			}
		}
		
	cout<<sum<<endl;
	
	return 0;
}
```


---

## 作者：Strong_Jelly (赞：0)

**思路**：设$f[i][j]$ $=$ $1$表示不可能出现$(i, j)$这个组合，$=$ $0$则表示肯定出现这个组合(初始都是$0$), 如果在任意一个序列中出现了$j$在$i$前面的情况，则$f[i][j]$ $=$ $1$(如果$j$在任意一个时候比$i$表现的好，那么$i$就不可能一直表现的比$j$好), 最后统计有多少个$f[i][j]$ $=$ $0$就好了 

$code$ :
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, q[1001], ans;
map < int, map < int, int > > f;//定义一个二位map(map的用法接近于数组), f[i][j] = 1表示不可能出现(i, j)这个组合，= 0则表示肯定出现这个组合(初始都是0) 
signed main()
{
	scanf("%d %d", &n, &m);
	for(register int i = 1; i <= n; ++i)
	{
		for(register int j = 1; j <= m; ++j)
		{
			scanf("%d", &q[j]);
			for(register int k = 1; k < j; ++k)//枚举所有在q[j]前的奶牛 
			{
				f[q[j]][q[k]] = 1;//q[j]没有比q[k]表现的好, 所以不可能有(q[j], q[k])的这个组合(但是还是有可能出现(q[k], q[j])这个组合) 
			}
		}
	}
	for(register int i = 1; i <= m; ++i)//直接用最后一行了, 反正都出现了所有的奶牛 
	{
		for(register int j = 1; j <= m; ++j)
		{
			if(!f[q[i]][q[j]] && q[i] != q[j])//如果存在(q[i], q[j])这个组合 & 是两头不相同的奶牛 
			{
				++ans;//答案数++ 
			}
		}
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：ffthh (赞：0)

# 心已崩
这道题还是挺 ~~水~~ 好的（理解题意点这里：[奶牛体操](https://www.luogu.com.cn/problem/P5831)）  
### 思路：
鉴于数据很水（1≤K≤10，1≤N≤20。），可以直接暴搜  

定义一个二维数组表示每头奶牛每次课程的表现  
接着再枚举可能的数对，最后输出结果  
**话不多说，献上代码**
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main(){
	//freopen("gymnastics.in", "r", stdin);
	//freopen("gymnastics.out", "w", stdout);
	int k, n, a[25][15], tmp, ans = 0;//初始化 
	cin >> k >> n; 
	for(int i = 1;i <= k;i ++){//输入 
		for(int j = 1;j <= n;j ++){
			cin >> tmp;
			a[tmp][i] = j;//第tmp头奶牛第i天的排名 
		}
	}
	bool flag = true;//标识，如果flag 在后面依然== true，则说明这对奶牛符合规定 
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++){
			flag = true;//重新定义为true 
			if(i == j) continue;
			for(int c = 1;c <= k;c ++){//判断 
				if(a[j][c] >= a[i][c]){
					flag = false;
					break;
				}
			}
			if(flag == true){
				ans ++;
			}
		}
	}
	cout << ans;//输出 
	return 0;
}
```
### 如有问题欢迎指正

---

## 作者：柠青哟 (赞：0)

思路很简单，将第一次排名的结果作为标准，f[i][j]=1表示i号奶牛比j号奶牛排名前。之后如果出现就j在i前但却f[i][j]=1的情况，将f[i][j]标记为0即可，最后统计f[i][j]=1的数量即为ans 
AC代码如下
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,k,a[21],f[21][21],ans;
int main(){
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			f[a[i]][a[j]]=1;//f[i][j]=1表示i号奶牛比j号奶牛排名前 
		}
	k--;
	while(k--){
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=n;i>=1;i--)
			for(int j=i-1;j>=1;j--){
				if(f[a[i]][a[j]]==1) f[a[i]][a[j]]=0;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(f[i][j]==1) ans++;
		}
	cout<<ans;
	return 0;
}
```


---

## 作者：SSFrost (赞：0)

# 解题：
本题要计算一个在所有排名都比另一个靠前的数量

直接开数组记录i比j名次靠前的次数（keep[i][j](long long int)

如果次数==k，那么就将ans加1，最终输出 

附代码
```c
//c++ 代码 
#include<bits/stdc++.h>
using namespace std;
#define mint long long int
mint k,n,ck[25][25];//输入数据 
mint keep[25][25];//keep[i][j]即i比j名次要高的次数 
bool car[25][25]={false};//防重鉴定 
inline int read(){   
	int s=0,w=1;   
	char ch=getchar();   
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}   
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();  
	return s*w;
}//快读 
mint ans;
 

int main(){
	k=read();
	n=read();
	for(mint i=1;i<=k;i++){
		for(mint j=1;j<=n;j++){
			ck[i][j]=read();
		}	
	}
	//输入 
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			for(int l=j+1;l<=n;l++){
				keep[ck[i][j]][ck[i][l]]++;//记录ck[i][j]比ck[i][l]名次大的次数 
			}
		}
	}
	
	for(int j=1;j<=n;j++){
		for(int l=1;l<=n;l++){
			if(!car[j][l] && keep[j][l]==k) {//如果=k，那么就表明 k个排名中j均比l的名次靠前 
				ans++;//记录 
				car[j][l]=true;//防止重复 
			}
		}
	}
	printf("%lld",ans);//输出 
    return 0;
}
//以此无缘出品 
```
#### //以次无缘

---

## 作者：莫明 (赞：0)

# 题解P5831【奶牛体操】
没想到这道题一次就AC了~~题目刚看的时候没看懂，看完提示才明白~~
~~没想到竟然是本题第一篇题解，非常鸡冻的蒟蒻~~

------------
## 数据样例

输入 #1 复制

##### 3 4

##### 4 1 2 3

##### 4 1 3 2

##### 4 2 1 3

输出 #1 复制
##### 4
##  说明/提示
  一致的奶牛对为 (1,4)、(2,4)、(3,4) 和 (1,3)。

------------


这道题我是用表格的统计思路。
## 下表以上数据为例。
| 奶牛编号 | 1 |  2| 3 | 4 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | \ | 2 | 3 | 0 |
| 2 | 1 | \ | 2 | 0 |
| 3 | 0 | 1 | \ | 0 |
| 4 | 3 | 3 | 3 | \ |
~~所以就有4对~~

# AC代码！
```cpp
#include<cstdio>
#include<cstring>
int main()
{
	int k,n,ans=0;
	scanf("%d%d",&k,&n);
	int b[n+2][n+2],c[n+2][n+2];
	memset(c,0,sizeof(c));
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++) scanf("%d",&b[i][j]);//输入第i次排名
		for(int j=1;j<n;j++)
		   for(int k1=j+1;k1<=n;k1++) //j排名之前和自己不用比较
		   {
		   	 c[b[i][j]][b[i][k1]]++;//增加对应的次数
		   	 if(c[b[i][j]][b[i][k1]]==k) ans++;//记录达到k轮的（因为懒多打字了）
		   }
	}
	printf("%d",ans);
	return 0;
}
```
~~嗯，自己yy吧~~
有问题可以评论提出


---

