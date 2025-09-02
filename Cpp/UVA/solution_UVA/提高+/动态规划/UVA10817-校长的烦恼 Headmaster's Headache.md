# 校长的烦恼 Headmaster's Headache

## 题目描述

斯普林菲尔德（春之田野？？？）学院的校长正在考虑为某些科目招聘新老师 现在有一批申请岗位的老师 每个老师能教一个或多个科目 校长想要选择一些申请者以保证每个科目都至少有两名老师能教 同时总共花的钱要最小

## 样例 #1

### 输入

```
2 2 2
10000 1
20000 2
30000 1 2
40000 1 2
0 0 0```

### 输出

```
60000```

# 题解

## 作者：小闸蟹 (赞：12)

```cpp
// 首先先了解一下位运算的一些基本操作：
// &：表示一个元素是否在这个集合里
// |：表示将这个元素加入这个集合中
// ^：表示将这个元素从这个集合中删除
// 然后我们就用二进制数的每一位表示一个科目的状态
// 最后就是简单的dp，难点在于对各个科目状态的表达
// 详见代码和注释
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <string>

constexpr int MaxN = 100 + 20 + 5;
constexpr int MaxS = 8;
constexpr int INF = 1000000000;

int m, n, s, c[MaxN], st[MaxN], d[MaxN][1 << MaxS][1 << MaxS];

// dp(i, s0, s1, s2)表示：
// 已经考虑了前i个人，还剩s0种没人会的科目，s1种一人会的科目，s2种两人以上会的科目
int dp(int i, int s0, int s1, int s2)
{
    if (i == m + n) // 搜完了所有的人了
    {   // 如果s2还没满的话，那就说明不可能满足了
        return s2 == (1 << s) - 1 ? 0 : INF;
    }

    int &Ans = d[i][s1][s2];
    if (Ans >= 0)   // 记忆化搜索的体现，因为没被搜过的时候是-1
    {
        return Ans;
    }

    Ans = INF;  // 没被搜过，就先初始化一下，设为INF
    if (i >= m)
    {
        // 在可选的情况下却不选i。先算出不选i的结果，等待后面与选i的的结果比较。
        Ans = dp(i + 1, s0, s1, s2);
    }

    // 下面是选i的情况：
    // m0：在st[i]中没人会的，但i会的
    // m1：在st[i]中只有一个人会的，i也会的
    int m0 = st[i] & s0, m1 = st[i] & s1;
    s0 ^= m0;   // 在s0中消除那些i会的
    s1 = (s1 ^ m1) | m0;    // 在已经有一个人会的技能里面减去i会的，
                            // 因为不减的话就是两个人会了
                            // 然后再加上i独有的会的，就成了新的一人会的集合
    s2 |= m1;   // 在s2中加上m1，表示现在有两个人会的有这么多
    Ans = std::min(Ans, c[i] + dp(i + 1, s0, s1, s2));  // 看是选i贵还是不选i贵

    return Ans;
}

int main()
{
    int x;
    std::string Line;
    while (std::getline(std::cin, Line))
    {
        std::stringstream ss(Line);
        ss >> s >> m >> n;  // 共s个科目，m名在职，n名应聘
        if (s == 0)
        {
            break;
        }

        for (int i = 0; i < m + n; ++i)
        {
            std::getline(std::cin, Line);
            std::stringstream ss(Line);
            ss >> c[i]; // 第i人所需要的工资
            st[i] = 0;  // 他能教的科目先设为空
            while (ss >> x)
            {
                st[i] |= (1 << (x - 1));    // 添加进去他所能教的科目集合里面
            }                               // 减一是因为输入中的编号从1开始
        }

        std::memset(d, -1, sizeof(d));  // 表示还没有被搜过
        std::cout << dp(0, (1 << s) - 1, 0, 0) << std::endl;
    }             // 初始搜时所有科目都没人教，从0号开始搜

    return 0;
}
```

---

## 作者：Sata_moto (赞：7)

### 前言：


[$ \large{}\color {#6495ED} \mathcal{MyBlog} $](https://xjx885.coding-pages.com/)

顺着LRJ蓝皮书刷到这题的...

看着题解区那么多人，本来不打算写题解的...

不过还是来了一发...

---

### 题目大意：

有s个科目，每个科目需要至少两个老师教，老师分为在职教师和应聘者，每个老师都可以教一些科目，需要的报酬也不同，其中在职教师必须选，应聘者可选可不选，求最少花多少钱....

---

### 题目分析:

观察s的范围...$s<=8$

很明显，这题可以状压...

我们先把题目简化一下，假如说一门科目只需要一名老师教就好，那么这题应该怎么做...

显然，这么一改之后，本题就成了一道模板题...

我们可以设状态f[k][i]表示选择前k名老师，科目有没有人教的状态为i...

转移在这里就略过了...

仔细分析i这一维：

i其实是一个二进制数，每一位的1/0表示某一门科目有没有人教...

我们其实也可以把它定义为：每一位的1/0表示某一门科目有没有至少一个人教...

两者是等价的...

我们会到本题，按照之前的思想，设状态f[k][i]...

i每一位的1/0表示某一门科目有没有至少两个人教...

如何转移？

显然，这样是没法转移的，因为状态表达的都不完整...

我们把没人教和有一个人教的情况混在了一起...

所以我们再加一维状态就可以了...

令状态为f[k][i][j]  ,k表示抉择到了第几个教师...

i每一位的1/0表示某一门科目是不是有且仅有一个人教...

j每一位的1/0表示某一门科目是不是至少有两个人教...

这样，状态就被我们表达清楚了...

i中位置X为的值为1,那么X科目只有一个人教

j中位置X为的值为1,那么X科目至少有两个人教

i，j中位置X为的值都为0,那么X科目没人教

状态搞定之后，转移就简单了...

其他细节见代码吧...

---

### 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const int MAXN = (1 << 8);

int s0, n, m;

int f[N][MAXN][MAXN];//状压数组，含义见题解

int cost[N];//雇第i个职员花多少钱 
int teach[N];//第i个职员能交那些科目 

int main()
{
	while(scanf("%d %d %d", &s0, &m, &n) != EOF)
	{
		if(s0 == 0) break;

		//数据不清空，爆零两行泪 
		memset(f, 0x3f, sizeof(f));
		memset(teach , 0, sizeof(teach));

		//因为在职教师是必选的，那么可以提前把他们处理出来 
		//把他们可以教的科目作为初始状态，花费的费用作为初始消耗 
		int ori1 = 0 , ori2 = 0, mon = 0;
		//ori1与DP中的i等价，ori2与j等价，mon是代价 
		for(int k = 1; k <= m; k++)
		{
			int c;
			scanf("%d", &c);
			mon += c;

			string s;
			getline(cin, s);
			//getline读整行 

			int num = 0;
			for(int i = 0; i < (int )s.length() ; i++)
				if(s[i] >= '0' && s[i] <= '9')
					num *= 10, num += s[i] - '0';
				else if(num)
				{
					if(!(ori2 & (1 << (num - 1))))//这门课不到两个人教（两个人教与N个人教对于我们的状态来说，没有区别） 
					{
						if(ori1 & ((1 << (num - 1))))//这门课有人一个教了， 那么把这一个人教的标志取消掉，换成两个人教的标志 
							ori1 ^= ((1 << (num - 1))), ori2 |= ((1 << (num - 1)));
						else//否则，标记上这门课有一个人教 
							ori1 |= ((1 << (num - 1)));
					}

					num = 0;
				}
			if(num)//最后一位的处理 
			{
				if(!(ori2 & (1 << (num - 1))))
				{
					if(ori1 & ((1 << (num - 1))))
						ori1 ^= ((1 << (num - 1))), ori2 |= ((1 << (num - 1)));
					else
						ori1 |= ((1 << (num - 1)));
				}
			}
		}

		//初态设定 
		f[0][ori1][ori2] = mon;

		for(int k = 1; k <= n; k++)
		{
			scanf("%d", &cost[k]);

			string s;
			getline(cin, s);

			int num = 0;
			for(int i = 0; i < (int )s.length() ; i++)
				if(s[i] >= '0' && s[i] <= '9')
					num *= 10, num += s[i] - '0';
				else if(num)
					teach[k] |= (1 << (num - 1)), num = 0;
			if(num)
				teach[k] |= (1 << (num - 1));
		}
		
		//我习惯的是刷表法...可能快一点 
		for(int k = 0; k < n; k++)
			for(int i = 0; i < MAXN; i++)
				for(int j = 0; j < MAXN; j++)
					if(f[k][i][j] != 0x3f3f3f3f)
					{
						//不雇佣 
						f[k + 1][i][j] = min(f[k + 1][i][j], f[k][i][j]);
						
						int to1 = i, to2 = j;
						//处理出雇佣之后的状态 
						for(int c = 0; c < s0; c++)
						{
							//他不教这一科 
							if(!(teach[k + 1] & (1 << c)))
								continue;

							//这科有两个人教了... 
							if((j & (1 << c) ))
								continue;

							//这个处理有点类似之前读入的处理，不细讲 
							if(i & (1 << c))
								to1 ^= (1 << c), to2 |= (1 << c);
							else
								to1 |= (1 << c);
						}

						//处理完毕，选择此人 
						f[k + 1][to1][to2] = min(f[k + 1][to1][to2], f[k][i][j] + cost[k + 1]);
					}

		//末态：所有科目都有至少两个人教 
		printf("%d\n", f[n][0][(1 << s0) - 1]);
	}

	return 0;
}
```


---


### 结语：

如果本题解有BUG...

那么...那么...那么...

（随意了）还请私信作者....

---

## END

---

## 作者：Ezios (赞：4)

###### ~~蒟蒻的第一篇题解~~



------------



# Problem : Headmaster's Headache


 _Problemsetter: Mak Yan Kei _ 

 _Idea from "Linear Optimization in Applications", S. L. Tang, Hong Kong University Press, 1999_ 


 

------------

这道题可以用状态压缩来做。
 

 
由于这道题的课程数量最多只有8，考虑 **[ 无人教 ]** 、 **[ 一人教 ]** 、 **[ 两人教 ] **也顶多有**0,1,2**三种状况；

所以可以考虑将原有的8位二进制数拓展至16位，分别以**00,01,11(**或者**10)**对应三种情况，进行状态压缩。然后这道题就很像一个01背包了。

那么DP方程可以表示如下：

		dp[i][j]表示决策到第i位教师时授课状态为j，那么转移方程也很简单，
        直接从前往后推即可：
        dp[i][con]=min(dp[i][con],dp[i+1][new_con]+cost[i])
        你甚至还可以砍掉[i]那一维？
        

~~然而不会拓~~

于是自然又想到可以用3进制来对三种状况，进行状态压缩，那么状态和转移同上面几乎完全一样，只是可能预处理3进制要花点空间。

~~不会写3进制~~


------------


最后在~~看了一位[dalao的题解](https://blog.csdn.net/u013625492/article/details/44239089)后~~确定可以将DP方程定义如下：

		DP[i][j] 中i , j 分别以二进制表示当前情况下课程已经满足至少
        有一人教授的状态和课程已经满足至少有二人教授的状态，即把课程
        的两种状态用二维拆开来表示。

例如，现在有两位老师分别能教授编号为**1、2**的课程和编号为**1、3**的课程，那么**i** , **j** 在二进制下分别为**00000111, 00000001**。

那么状态的转移可以表示如下：
```cpp
		dp[ji][ki]=min(dp[ji][ki],dp[j][k]+teacher[i].cost);
```
其中 **ji**，**ki** 分别对应如果招聘该老师的授课情况，该情况由未招聘该老师的授课情况转移而来。
那么启用该状态转移的前提条件是：
```cpp
		(j|k)==j && dp[j][k]!=INT_MAX/2
```
其中 **( j | k ) == j** 用于保证k状态的合法性：

 如果该课程已经至少有两人教授（即 **k** 在二进制下对应是1），那么由状态定义可得对应有一人教授的课程的状态下“该课程至少有一人教授”必须为**真**（即 **j** 的对应位也必定是1），否则与定义矛盾；

所以该判断可以用  _或（如果两个数在二进制下对应位有一个数为1，那么对应位的操作结果便为1）_ 来进行判断，且由于 **“有两个老师教的课程”**  包含于**“有至少一个老师教的课程”**中，所以 **k** 二进制对应的1的个数总是不超过 **j** 二进制对应的1的个数，且位置严格对应，从而保证了结果为 **j** 。（dalao请忽略这段话）

**dp[ j ][ k ] != INT_MAX/2** 则是保证该状态可行。（但因为最优解肯定不会傻到去取INT_MAX，所以去掉这个限制也没有多大影响，程序也慢不了多少。~~至于那个/2可以忽略~~）

------------


下面是改得乱七八糟的代码：
```cpp
#include<cstdio>
#include<cstring>
#include<bitset>
#include<climits>
#include<iostream>
using std::bitset;
using std::cout;
using std::min;
#define endl "\n"
bool isdight(char a)
{
	if(a>='0'&&a<='9') return true;
	return false;
}
int T,S,M,N;
int ans;
struct employes{
	int cost;
	int could_teach[10];
	int tail=0;
}teacher[128];
int classes[16];//存储课程数量 
int dp[300][300];
int state[181];//预处理应聘教师的二进制下的教授课程 
int limit,defult0,defult1;
void init()
{
	limit=(1<<S)-1;
	defult0=0;
	defult1=0;
	for(int i=0;i<=limit;i++)
		for(int j=0;j<=limit;j++)
			dp[i][j]=INT_MAX/2;
	for(int i=1;i<=N;i++)
		for(int j=0;j<teacher[i].tail;j++)
			state[i]=state[i]|(1<<(teacher[i].could_teach[j]-1));//此处把应聘教师的教授课程转换成二进制下的形式 
	for(int i=1;i<=8;i++){
		if(classes[i]<2&&classes[i]>0) defult0|=(1<<(i-1));//初始状态下课程是否已满足至少有一人教授
		else if(classes[i]>=2){
			defult0|=(1<<(i-1));
			defult1|=(1<<(i-1));//初始状态下课程是否已满足二人教授 
		}
	}
	dp[defult0][defult1]=ans;
}
void DPs()
{
	for(int i=1;i<=N;i++)
    {
        for(int j=limit;j>=0;j--)//倒着搞背包
        {
            for(int k=limit;k>=0;k--)
            {
                if((j|k)==j && dp[j][k]!=INT_MAX/2)
                {
                    int s=state[i];
                    int could_two=(s&j);//该教师能让多少已经有至少一人教授的课程变成二人教授 
                    int ji=(j|s);//转移后的至少一人教授的课程的状态 
                    int ki=(k|could_two);//转移后的二人教授的课程的状态 
                    dp[ji][ki]=min(dp[ji][ki],dp[j][k]+teacher[i].cost);
                }
            }
        }
    }
}
int main()
{
	int cost=0;
	char scin;
	while(1)
	{
		ans=0;
		memset(classes,0,sizeof classes);
		memset(teacher,0,sizeof teacher);
		memset(state,0,sizeof state);//因为这4句话没有加, WA 了一天 
		scanf("%d%d%d",&S,&M,&N);
		if(S==0&&M==0&&N==0) return 0;
		for(int i=1;i<=M;i++){
			scanf("%d ",&cost);
			ans+=cost;//因为是强制聘用(官僚制度? ),所以可以直接累加费用 
			while(1){
				scin=getchar();//还是getchar最稳妥 
				if(isdight(scin)) classes[scin-'0']++;//记录
				else if(scin=='\n') break;
			}
		}
		for(int i=1;i<=N;i++)
		{
			scanf("%d ",&teacher[i].cost);
			while(1){
				scin=getchar();	
				if(isdight(scin))teacher[i].could_teach[teacher[i].tail]=(scin-'0'),teacher[i].tail++;//把应聘教师能教的课程存起来 
				else if(scin=='\n') break;
			}
		}
		bool flag=true;
		for(int i=1;i<=8;i++) if(classes[i]<2) flag=false;
		if(flag==true) printf("%d\n",ans);//十分没用的剪枝:如果本来就满足题意，就无需招聘新教师 
		else{
			init();
			DPs();
			printf("%d\n",dp[limit][limit]);
		}
	}
}
```

---

## 作者：andyli (赞：4)

用两个集合，$s1$表示恰好有一个人教的科目集合，$s2$表示至少有两个人教的科目集合，而$d(i,s1,s2)$表示已经考虑了前$i$个人时的最小花费。注意，把所有人一起从$0$编号，则编号$0\sim m-1$是在职教师，$m\sim n+m-1$是应聘者。状态转移方程为$d_{i,s1,s2}\min\{d_{i+1,s1',s2'}+c_i,d_{i+1,s1',s2'}\}$，其中第一项表示“聘用”，第二项表示“不聘用”。当$i\geq m$时状态转移方程才会出现第二项。这里$s1'$和$s2'$表示“招聘第$i$个人后$s1$和$s2$的新值”，具体计算方法见代码。  
下面代码中的$st_i$表示第$i$个人能教的科目集合，$s0$表示没有任何人能教的科目集合。$s0$这个参数并不需要记忆，仅是为了编程的方便。  
主要代码如下：  
```cpp
const int maxn = 130, maxs = 9, INF = -1u / 4; // -1u / 4 = 1073741823

int c[maxn], st[maxn], d[maxn][1 << maxs][1 << maxs], s, m, n;
int dp(int i, int s0, int s1, int s2)
{
    if (i == m + n)
        return s2 == (1 << s) - 1 ? 0 : INF;
    int& ans = d[i][s1][s2];
    if (~ans)
        return ans;
    ans = INF;
    if (i >= m)
        ans = dp(i + 1, s0, s1, s2); // 不选
    int m0 = st[i] & s0, m1 = st[i] & s1;
    return ans = min(ans, dp(i + 1, s0 ^ m0, (s1 ^ m1) | m0, s2 | m1) + c[i]); // 选
}
int main()
{
    while (io.read(s, m, n), s) {
        memset(d, -1, sizeof(d));
        memset(st, 0, sizeof(st));
        for (int i = 0; i < m + n; i++) {
            io.read(c[i]);
            char str[20];
            io.readline(str); // 读取这一行剩下的字符串
            stringstream ss;
            ss << str;
            int t;
            while (ss >> t)
                st[i] |= (1 << (t - 1)); // 科目以0开始编号
        }
        writeln(dp(0, (1 << s) - 1, 0, 0));
    }
    return 0;
}
```

---

## 作者：mcDinic (赞：3)

[更好的阅读效果](https://www.luogu.com.cn/blog/484076/uva10817-xiao-zhang-di-fan-nao-headmasters-headache-ti-xie)

~~一道水题。~~

这题需要用状压 dp （还有点背包的意味），与普通状压的区别仅仅是进制不同。开个 dp，$dp_{i,j}$ 表示到第 i 个应聘者，每门科目的老师数量（不包括在职教师）用三进制表示后转化为十进制时为 j，所需的最少钱数。这样说有点拗口，但学了状压的读者应该都懂是什么意思吧。

但是问题来了，我们如果枚举 j，它可能由前面的好几种状态转化而成，若再枚举一遍之前的状态，就要超时了。所以逆推思路是不可取的，我们只有枚举 $dp_{i-1,k}$，才能确定对应的 $dp_{i,j}$。

有个细节的处理再说说，既然本人思路中的 $dp_{i,j}$ 是不包括在职教师的，那么对于最后的答案该怎么办呢？首先，弄出一个数，该数等于每位上均取 2 的三进制数，减去每门科目已有的教师数拼成的三进制数。可能这样讲大家有些不明白，就举个例子吧。

比如有 2 科目，现在在职教师有 2 个，分别可以教 1，2
两门课。那么上文中的“每位上均取 2 的三进制数”就是 $(22)_3$，化为十进制就是 8。而“每门科目已有的教师数拼成的三进制数”就是这么算的：第一门课已有教师 1 教，共 1 名教师，第二门课已有 教师 2 
教，共有一名教师。那么该数就是 $(11)_3$。

回到刚才的话题，“弄出的这个数”干什么用呢？相信大家发现了，它转化成三进制后，第 i 位（从低到高数）就表示第 i 门课还要几名教师。设它为 hp，那么最终的答案就是 $dp_{n,hp}$。

每次在用前一位的状态 k，与现在这个应聘者能教的课对应的数，进行求和时，如果第 i 位大于第 i 个科目还需要的教师数（即 hp 中的第 i 位），就把它变成 hp 中的第 i 位。当然，这里指的 hp 是化成三进制后的。

讲了那么多，赶紧上代码（都说那么清楚了，所以不加注释，也更方便各位食用）。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int s,m,n,a,b[105][2],dp[105][50005],hp[105],ht;
signed wei(int x,int y,int z){
	int o1[55]={0},o2[55]={0},t1=-1,t2=-1,ans=0;
	if(x==0)++t1;
	if(y==0)++t2;
	while(x>0){
		o1[++t1]=x%3;
		x/=3;
	}
	while(y>0){
		o2[++t2]=y%3;
		y/=3;
	}
	int xpp=max(t1,t2);
	for(int i=0;i<=xpp;i++){
		int ki=o1[i]+o2[i],biao=(z==1?2:hp[i]);
		if(ki>=biao)ki=biao;
		ans+=pow(3,i)*ki;
	}
	return ans;
}
signed main(){
	while(~scanf("%lld%lld%lld",&s,&m,&n)){
		if(s==0)break;
		a=0;
		ht=-1;
		memset(hp,0,sizeof(hp));
		memset(b,0,sizeof(b));
		memset(dp,0x3f3f3f3f,sizeof(dp));
		dp[0][0]=0;
		string st;
		getline(cin,st);
		for(int i=1;i<=m;i++){
			getline(cin,st);
			int klop=st.size(),ck=0,j;
			for(j=0;j<klop;j++){
				if(st[j]>='0'&&st[j]<='9')ck=ck*10+st[j]-48;
				else break;
			}
			dp[0][0]+=ck;
			ck=0;
			for(j=j+1;j<klop;j++){
				if(st[j]>='0'&&st[j]<='9')ck=ck*10+st[j]-48;
				else{
					a=wei(a,pow(3,ck-1),1);
					ck=0;
				}
			}
			if(ck>0)a=wei(a,pow(3,ck-1),1);
		}
		for(int i=1;i<=n;i++){
			getline(cin,st);
			int klop=st.size(),ck=0,j;
			for(j=0;j<klop;j++){
				if(st[j]>='0'&&st[j]<='9')ck=ck*10+st[j]-48;
				else break;
			}
			b[i][0]=ck;
			ck=0;
			for(j=j+1;j<klop;j++){
				if(st[j]>='0'&&st[j]<='9')ck=ck*10+st[j]-48;
				else{
					b[i][1]+=pow(3,ck-1);
					ck=0;
				}
			}
			if(ck>0)b[i][1]+=pow(3,ck-1);
		}
		int ok=pow(3,s)-1-a,lo=ok;
		while(lo>0){
			hp[++ht]=lo%3;
			lo/=3;
		}
		for(int i=1;i<=n;i++){
			b[i][1]=wei(b[i][1],0,2);
			for(int j=0;j<=ok;j++){
				dp[i][j]=min(dp[i-1][j],dp[i][j]);
				int teacher_hei_was_AKIOI=wei(j,b[i][1],2);
				dp[i][teacher_hei_was_AKIOI]=min(dp[i-1][teacher_hei_was_AKIOI],dp[i][teacher_hei_was_AKIOI]);
				dp[i][teacher_hei_was_AKIOI]=min(dp[i][teacher_hei_was_AKIOI],dp[i-1][j]+b[i][0]);
			}
		}
		printf("%lld\n",dp[n][ok]);
	}
	return 0;
}
```


---

## 作者：Lates (赞：2)

设 $f[i][s0][s1]$ 表示前 $i$ 个求职的教师的最小花费，$s0$ 表示无人教的科目集合，$s1$ 表示有且仅有一人教的科目集合。

先把 $m$ 个在职教师所教每个科目几个桶，然后可以得到出状态就是 $f[0][S0][S1]=\sum C[i]$，$S0$ 表示在职教师中没人教的科目集合，$S1$ 表示表示有且仅有一人教的科目集合。$C[i]$ 表示 $m$ 个教师的花费总和。

预处理每个人能达到的集合 $e[i]$

然后转移就是枚举每个求职的选或者不选。

选的时候的转移的集合是 $s0'=s0\ \ \hat{}\ (s0\  \& \ e[i] ),s1'=s1 \ \hat{}\ (s1\ \& \ e[i]) \ |\ (s0\  \& \ e[i] ) $

就是选中以后取两个集合与 $e[i]$ 的交集然后加加减减。

```cpp

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int flbreak;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	if(ch=='\n')flbreak=1;
	return f?-x:x;
}
const int MAXS=(1<<8)+5;
int s,n,m; 
int e[205],c[205],cost,ALL;

int f[200][MAXS][MAXS];
int used[20];
inline void sol(){
	
	m=read(),n=read();
	ALL=(1<<s)-1;
	
	cost=0;
	memset(used,0,sizeof(used));
	memset(e,0,sizeof(e));
	memset(c,0,sizeof(c)); 
	memset(f,0x3f,sizeof(f));
	
	int S0=0,S1=0;
	for(register int i=1,x;i<=m;++i){
		x=read();cost+=x;
		flbreak=0;
		while(!flbreak)x=read(),used[x]++;
	}
	for(register int i=1,x;i<=n;++i){
		c[i]=read();
		flbreak=0;
		while(!flbreak)x=read(),e[i]|=1<<(x-1);
	}
	for(register int i=1;i<=s;++i){
		if(used[i]==0)S0=S0|(1<<i-1);
		if(used[i]==1)S1=S1|(1<<i-1);
	}
	f[0][S0][S1]=cost;
	
	for(register int i=1;i<=n;++i){
		for(register int s0=0;s0<=ALL;++s0){
			for(register int s1=0;s1<=ALL;++s1){
				// bu选
				f[i][s0][s1]=f[i-1][s0][s1];
				int s0_=s0^(s0&e[i]);
				int s1_=(s1^(s1&e[i]))|(s0&e[i]);
				f[i][s0_][s1_]=min(f[i][s0_][s1_],f[i][s0][s1]+c[i]);
			}
		}
	}
	printf("%d\n",f[n][0][0]);
}
signed main(){
	
	while(s=read())sol(); 
	
    return 0;
}
```


---

## 作者：lovely_hyzhuo (赞：1)

萌新写的第一篇状态压缩 dp 题解，如有错误，请私信指出。

## 1.题目大意

就是说有两种教师，一种在职教师，你必须聘用他们；一种申请者，要选至少每个科目都有两个人教。求最小代价。


## 2.初步分析

对于在职教师，直接把费用和科目加到初始状态里就可以了。

看一眼数据范围，你好状压。

令 $f_{i,j,k}$ 表示抉择到了第 $i$ 个教师，有 $j$ 个科目仅有 $1$ 个人教，有 $k$ 个科目至少有两个人教。

## 3.细节

这是 UVA 的题，输入比较恐怖。

要吃掉换行符，读入字符教哪个科目。

具体输入看代码。

## 4.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[130][1<<10][1<<10],w[130],teach[130];
int s,n,m;
void solve()
{
	memset(f,0x7f7f7f,sizeof(f));
	memset(w,0,sizeof(w));
	memset(teach,0,sizeof(teach));	
	int ss1=0,ss2=0,sum=0;
	for(int i=1;i<=m;i++)
	{
		int t;
		cin>>t;
		sum+=t;
		int x=0;
		while(1)
		{
			cin>>x;
			if(ss1&(1<<(x-1)))
				ss2|=1<<(x-1);
			ss1|=1<<(x-1);
			char c=getchar();
			if(c=='\n') 
				break;
		}
	}
	f[0][ss1][ss2]=sum;
	for(int i=1;i<=n;i++)
	{
		int t;
		cin>>t;
		w[i]=t;
		int x=0;
		while(1)
		{
			cin>>x;
			teach[i]|=1<<(x-1);
			char c=getchar();
			if(c=='\n') 
				break;
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<s);j++)
		{
			int k=j;
			f[i+1][j][k]=min(f[i+1][j][k],f[i][j][k]);
			int s1=j|teach[i+1];
			int s2=k|(j&teach[i+1]);
			if(f[i+1][s1][s2]>f[i][j][k]+w[i+1])
			f[i+1][s1][s2]=min(f[i+1][s1][s2],f[i][j][k]+w[i+1]);
			k=((k-1)&j);
			while(k!=j)
			{
				f[i+1][j][k]=min(f[i+1][j][k],f[i][j][k]);
				int s1=j|teach[i+1];
				int s2=k|(j&teach[i+1]);
				if(f[i+1][s1][s2]>f[i][j][k]+w[i+1])
				f[i+1][s1][s2]=min(f[i+1][s1][s2],f[i][j][k]+w[i+1]);
				k=((k-1)&j);
			}
		}
	}
	cout<<f[n][(1<<s)-1][(1<<s)-1]<<endl;
}
int main()
{
	while(cin>>s>>m>>n&&s)
		solve();
	return 0;
}
```


---

## 作者：Ray662 (赞：1)

[洛谷 传送门](https://www.luogu.com.cn/problem/UVA10817) | [UVA 传送门](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1758)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-uva10817)

题目大意：

- 有 $m$ 个在职教师和 $n$ 个求职者，需教授 $s$ 门课程；

- 已知每个人的工资 $c$ 和能教的课程集合，要求支付最少的工资使得每门课都至少有两名教师能教（在职教师不能辞退）；

- $1 \le m \le 20, 1 \le n \le 100, 10^4 \le c \le 5 \times 10^4$。

---

### 分析

- $m$ 比较小，考虑状态压缩。

- $m_1$：恰好有 $1$ 个人能教的科目集合。

- $m_2$：$\ge 2$ 个人能教的科目的集合。

- $f(i, m_1, m_2)$：已经考虑了前 $i$ 个人时，剩余花费的最小值。

- 所有人从 $0$ 开始编号（方便位运算），$0 \sim (m - 1)$ 是任职教师，$m \sim (m + n - 1)$ 是应聘者。

- 状态转移方程如下（其实就是选 or 不选的分别讨论）：

$$
f(i, m_1, m_2) = \min\{f(i + 1, {m_1}', {m_2}') + c_i, f(i + 1, m_1, m_2)\}
$$

- 故答案为：

$$
f(m + n, 0, 2^s - 1)
$$

---

总体复杂度：$O(4^s(m + n))$。

注：本题输入较为特殊，具体详见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 125, M = 10, INF = 2e9;
int s, m, n, C[N], T[N], f[N][1 << M][1 << M];
int DP(int i, int s0, int s1, int s2) {
	if (i == m + n) {
		if (s2 == (1 << s) - 1) return 0;
		return INF;
	}
	int & F = f[i][s1][s2];
	if (F >= 0) return F;
	F = INF;
	if (i >= m) F = DP(i + 1, s0, s1, s2);
	int m0 = T[i] & s0, m1 = T[i] & s1;
	return F = min(F, C[i] + DP(i + 1, s0 ^ m0, (s1 ^ m1) | m0, s2 | m1));
}  // 我写的是记忆化，和 DP 无本质区别
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	// 本题的特殊输入：不知道每个人能教几个学科，故先整行读入再做处理，具体看代码
	while (cin >> s >> m >> n && s) {
		cin.ignore();
		string line;
		for (int i = 0, x; i < m + n; i ++ ) {
			getline(cin, line);
			stringstream ss(line);
			ss >> C[i], T[i] = 0;
			while (ss >> x) T[i] |= (1 << (x - 1));
		}
		memset(f, -1, sizeof(f));
		printf("%d\n", DP(0, (1 << s) - 1, 0, 0));
	}
	return 0;
}
```

---

## 作者：wanggiaoxing (赞：0)

### 三进制状态压缩
这道题与其他题不一样的是需要每一门课上有至少 $2$ 名老师，那么二进制在这里显然不好使，那我们可以尝试使用三进制，其中三进制中每一位的意义为：$0$ 代表 $0$ 名老师，$1$ 代表 $1$ 名，$2$ 代表 $2$ 名及 $2$ 名以上。

那么我们就可以愉快的推 $dp$ 方程辣。

$dp[x]=\min(dp[x],dp[t]+value[i])$

其中 $t$ 必须满足题目一开始所给的集合（就是那些必须雇用的人），那么 $t$ 是枚举出来的，$x$ 即为 $t$ 与 第 $i$ 个教师所教科目集合的并集。
#### 一些预处理
预处理 $3$ 的幂，满足题目一开始所给的集合的数，十进制数在三进制下的每一位。
#### 关于三进制并集与判断是否在同一集合
当这一位与另一位的和大于 $2$ 时取 $2$，否则就取这两位数的和。

当需要判断的数的每一位都大于等于这个集合上对应的那一位，这个数被此集合包含。
#### 关于输入
我们可用字符串的方式读入，详情见代码，在输入是也要取并集，在输入应聘者时可以一边输入一边转移。
```cpp
#include<bits/stdc++.h>
using namespace std;
int s,m,n,now,v[11];
struct node
{
	int q,w;
};
node x[301];
int dp[60000],get1[60000][16],use[60000];
int main()
{
	v[0]=1;
	for(int i=1;i<=9;i++)
		v[i]=v[i-1]*3;
	for(int i=0;i<v[9];i++)
	{
		int o=i;
		for(int k=1;k<=9;k++)
		{
			get1[i][k]=o%3;
			o/=3;
		}
	}
	while(cin>>s>>m>>n,s!=0)
	{		
		memset(dp,0x3f,sizeof(dp));
		int h=0;
		now=0;
		int k;
		for(int i=1;i<=m;i++)
		{
			cin>>k;
			h+=k;
			char ch;
			while((ch=getchar())!='\n')//输入
			{
				if(ch==' ')
					continue;
				else					
				{
					int x1=0,k=v[ch-'0'-1];
					for(int j=1;j<=s;j++)
						if(get1[k][j]+get1[now][j]>2)
							x1+=2*v[j-1];
					else
						x1+=(get1[k][j]+get1[now][j])*v[j-1];
					now=x1;//now即为初始状态，进行并集操作
				}	
			}
		}
		use[0]=0;
		for(int i=now;i<v[s];i++)
		{
			bool flag=0;	
			for(int r=1;r<=s;r++)
				if(get1[i][r]<get1[now][r])
				{
					flag=1;
					break;
				}
			if(flag==1)
				continue;
			use[++use[0]]=i;
		}//初始化合法的数
		dp[now]=h;
		for(int i=1;i<=n;i++)
		{
			cin>>x[i].q;
			x[i].w=0;
			char ch;
			while((ch=getchar())!='\n')
			{
				if(ch==' ')
					continue;
				else					
				{
					int x1=0,k=v[ch-'0'-1];
					for(int j=1;j<=s;j++)
						if(get1[k][j]+get1[x[i].w][j]>2)
							x1+=2*v[j-1];
					else
						x1+=(get1[k][j]+get1[x[i].w][j])*v[j-1];
					x[i].w=x1;						
				}	
			}
			for(int k=use[0];k>=1;k--)
			{
				int x1=0;
				for(int j=1;j<=s;j++)
					if(get1[use[k]][j]+get1[x[i].w][j]>2)
						x1+=2*v[j-1];
					else
						x1+=(get1[use[k]][j]+get1[x[i].w][j])*v[j-1];
				dp[x1]=min(dp[x1],dp[use[k]]+x[i].q);
			}//进行转移
			
		}		
		cout<<dp[v[s]-1]<<endl;
	}
	return 0;
}
```


---

## 作者：wtyqwq (赞：0)

- [UVA10817 Headmaster's Headache](https://www.luogu.com.cn/problem/UVA10817)

- 解题思路：

  - 令集合 $S_1$ 表示恰好有 $1$ 个人教的科目集合，$S_2$ 表示至少有 $2$ 个人教的科目集合，$f(i,S_1,S_2)$ 表示已经考虑了前 $i$ 个人时**要达到目标状态的**最小花费。
  
  - 注意，把所有人一起从 $0$ 编号，则编号 $0\sim m-1$ 是在职教师，$m\sim n+m-1$ 是应聘者。状态转移方程为：
  
    $$f(i,S_1,S_2)=\min\{f(i+1,S_1',S_2')+c_i,f(i+1,S_1,S_2)\}$$
    
  - 状态转移方程中的第一项表示“聘用”，第二项表示不聘用，即当 $i\ge m$ 时状态转移方程中才出现第二项。这里的 $S_1'$ 和 $S_2'$ 表示“招聘第 $i$ 个人之后 $S_1$ 和 $S_2$ 的新值”，具体计算方法见代码。
  
  - 下面的代码中的 $a_i$ 表示第 $i$ 个人能教的科目集合（注意输入中科目从 $1$ 开始编号，程序中我们最好从 $0$ 开始编号，因此输入时要转换一下）。下面的代码中用到了一个技巧：记忆化搜索中有一个参数 $S_0$，表示没有任何人能教的科目集合。这个参数**不需要被记忆**，因为有了 $S_1$ 和 $S_2$ 就可以计算出 $S_0$，仅是为了编程的方便（详见 $S_1'$ 和 $S_2'$ 的计算方式）。

- 代码实现：
 
------------
```cpp
#include <bits/stdc++.h>
#define S (1 << 3)
#define MAX (1 << 8)
#define TOT (1 << 7)
#define INF 0x3F3F3F3F
using namespace std;
string Line;
int n, m, k, x, c[TOT], a[TOT];
int f[TOT][MAX][MAX];
int dfs(int i, int A, int B, int C) {
	if (i == n + m)
		return C == (1 << k) - 1 ? 0 : INF;
	if (f[i][B][C] != -1)
		return f[i][B][C];
	int &ret = f[i][B][C];
	ret = INF;
	if (i >= m)
		ret = dfs(i + 1, A, B, C);
	int D = a[i] & A, E = a[i] & B;
	A ^= D, B = (B ^ E) | D, C |= E;
	ret = min(ret, c[i] + dfs(i + 1, A, B, C));
	return ret;
}
int main() {
	while (getline(cin, Line)) {
		stringstream A(Line);
		A >> k >> m >> n;
		if (k == 0 && m == 0 && n == 0)
			return 0;
		for (int i = 0; i < n + m; ++i) {
			getline(cin, Line);
			stringstream A(Line);
			A >> c[i], a[i] = 0;
			while (A >> x) a[i] |= (1 << x - 1);
		}
		memset(f, -1, sizeof(f));
		cout << dfs(0, (1 << k) - 1, 0, 0) << "\n";
	}
	return 0;
}
```
- 算法标签：状态压缩类 $\text{DP}$。

- 时间复杂度：$O(2^{2k}\times (n+m))$。

- 空间复杂度：$O(2^{2k}\times (n+m))$。

- 期望得分：$100$ 分。[提交记录](https://www.luogu.com.cn/record/39336636)。

---

## 作者：白鲟 (赞：0)

## 前言
显示出现问题请到[博客](https://www.luogu.com.cn/blog/bzlz-zdx/solution-uva10817-new)阅读。

## 题意简述
给出一些集合和它们的权值，取其中某些集合（其中限制某些集合必须取），使它们在多重集意义下的并集中每个出现的元素均出现至少两次，求所取集合权值和的最小值。

## 题目分析
较为显然的状态压缩型动态规划。由于要求每个出现的元素出现至少两次，可以想到将每一个集合压缩成一个三进制数。容易得到以下方程式：
$$
f_S=\max_{T \cup set_i}f_T+value_i
$$
边界条件为
$$
f_{MUST}=\sum_{set_i \subset MUST}{value_i}
$$
其中 $MUST$ 指必须取的集合的集合（谔谔为什么写得这么绕），$T,S$ 均为满足初始状态 $MUST$ 是其子集的多重集，$set_i,value_i$ 分别对应一个集合及其权值。  

这时可以发现，这道题的难点在于三进制集合的处理。通常有两种方法来实现三进制集合操作：拆分成两个二进制集合与模仿二进制集合来实现。前者时间复杂度较低，更易实现（也许吧），但空间复杂度更高；后者则相反。  

对于第一种思路，意即用两个二进制数分别表示只出现一次的元素和出现至少两次的元素两个集合。对于第二种思路，是对三进制上每一位分别进行操作。在这里给出的是第二种思路的代码。  

首先我们可以预处理出 $3$ 的幂。然后观察方程式我们发现此题需要实现的是三进制意义下的并集和判断一个集合是否包含于另一个集合。而这两个操作的前提是实现取三进制的某一位。这个操作与十进制取某一位类似。
```cpp
inline int at(int x,int i)
{
	return x%power[i+1]/power[i];
}
```
对于并集，可以理解为将三进制下每一位分别相加，大于 $2$ 的部分舍去，即不进位的加法。
```cpp
inline int union_of(int x,int y)
{
	int res=0;
	for(int i=0;i<10;++i)
		res+=power[i]*min(2,at(x,i)+at(y,i));
	return res;
}
```
对于判断某一个集合是否包含于另一个集合，可以比较它们三进制上的每一位，如果集合 $S$ 的每一位都不大于 $T$ 的对应位，则 $S \subset T$。
```cpp
inline bool belong(int x,int y)
{
	for(int i=0;i<10;++i)
		if(at(x,i)>at(y,i))
			return false;
	return true;
}
```
对于每组数据时间复杂度为 $\operatorname{O}(3^s\log_3s\cdot n)$（我也不知道我算错没……）。

## 完整代码
由于类似于 01 背包，每个集合只能取一次，故要注意循环顺序。可以预处理出可转移的集合（即满足 $MUST \subset S$ 的集合 $S$），减少时间开销。对于此题有点麻烦的输入，可以直接使用 `getline` 读一行，也可以使用类似快读的方式每次读到 `'\n'` 为止。注意有多组数据。
```cpp
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int power[15]={1,3,9,27,81,243,729,2187,6561,19683,59049};
int s,m,n,x,tot,all,money,status,start,f[60001],usable[60001];
inline int min(int x,int y)
{
	return x<y?x:y;
}
inline int at(int x,int i)
{
	return x%power[i+1]/power[i];
}
inline int union_of(int x,int y)
{
	int res=0;
	for(int i=0;i<10;++i)
		res+=power[i]*min(2,at(x,i)+at(y,i));
	return res;
}
inline bool belong(int x,int y)
{
	for(int i=0;i<10;++i)
		if(at(x,i)>at(y,i))
			return false;
	return true;
}
inline int read(void)
{
	int res=0;
	char t=getchar();
	bool check=false;
	while(!check)
	{
		while(!isdigit(t))
		{
			if(t=='\n')
			{
				check=true;
				break;
			}
			t=getchar();
		}
		int x=0;
		while(isdigit(t))
		{
			x=x*10+t-'0';
			t=getchar();
		}
		res=union_of(res,power[x-1]);
		x=0;
	}
	return res;
}
int main()
{
	while(scanf("%d%d%d",&s,&m,&n)!=EOF)
	{
		if(!s)
			break;
		memset(f,0x3f,sizeof f);
		all=power[s]-1;
		start=money=0;
		while(m--)
		{
			scanf("%d",&x);
			money+=x;
			start=union_of(start,read());
		}
		f[start]=money;
		usable[0]=0;
		for(int i=start;i<=all;++i)
			if(belong(start,i))
				usable[++usable[0]]=i;
		while(n--)
		{
			scanf("%d",&x);
			status=read();
			for(int i=usable[0];i>0;--i)
			{
				int t=union_of(status,usable[i]);
				f[t]=min(f[t],f[usable[i]]+x);
			}
		}
		printf("%d\n",f[all]);
	}
	return 0;
}
```

---

## 作者：CreeperLordVader (赞：0)

### 另一种状态定义和DP的方法

### 状态的定义是LRJ大神的,DP的记忆化搜索是我自己写的

### 设$ d(x,S_1,S_2)$为当前考虑到第x个人,无人教的课程集合为S_1,只有一个人教的课程集合为S_2时,最小的花费

则初态为$ d(1,0,0) $,因为初始时所有课都没人教

末态为$ d(m+n,U,0) $,$U$为全集,此时所有课都有至少有两个人教,不存在只有一个人教的课程

DP时,我们定义$1,2...m$为在职教师,$m+1,m+2...m+n$为应聘者

当$x \le m$时,初值为$INF$

当$x>m$时,初值为$INF$,但在DP中我们可以先将其设为$d(x+1,S_1,S_2)$,表示不雇佣这个人,然后在此基础上继续更新

DP的边界有些复杂

当$x==m+n+1$时,已经考虑完了所有人

此时DP边界为$
 0\qquad if(S_1==U,S_2==0)
$

$INF\qquad otherwise$

### 如果按照我的写法,在代码中实际要变成$INF-1$,这是为了记忆化,我在记忆化时的依据是$d(x,S_1,S_2)<INF$,但实际上,如果这个状态被访问过,但是由于DP边界为$INF$而且该状态的值没有被更新,导致该状态值为$INF$,但是实际上访问过,记忆化时无法查出来,程序效率大打折扣

当然,你也可以选个够大而且小于$INF$的值,你也可以开个数组来标记当前状态是否被访问

DP时就简单了,用能教的所有课程得到新的集合然后DP

我们直接用能教的所有课程去更新,是因为这样做一定能最大限度地~~压榨人力资源~~利用花在这个教师上的钱

一门课的老师永远不嫌多,能教就教,一定更容易满足每门课的教师人数下限

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ok;
int d[150][1<<8][1<<8];
int a[150],c[150];
void read(int& x)
{
	char c=getchar();
	x=0;
	while(c<'0'||c>'9')
	{
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	if(c=='\n')ok=1;
}
int dp(int x,int s1,int s2)
{
	if(x>m+k)
	{
//		cout<<s1<<" "<<s2<<endl;
		if(s1==((1<<n)-1)&&!s2)return 0;
		else return 0x3f3f3f3f-1;
	}
	if(d[x][s1][s2]<0x3f3f3f3f)return d[x][s1][s2];
	if(x>m)d[x][s1][s2]=dp(x+1,s1,s2);
	int nxt1=s1,nxt2=s2;//如果选了这个老师,下一刻的状态
	for(int i=0;i<n;i++)
	{
		if(a[x]&(1<<i))//能教 
		{
			if(!(s1&(1<<i)))//没人教
			{
				nxt1|=(1<<i);
				nxt2|=(1<<i);
			}
			else//有人教
			{
				if(s2&(1<<i))nxt2^=(1<<i);//只有一个人教
				//如果已经至少有两个人教,状态不变 
			}
		}
	}
	d[x][s1][s2]=min(d[x][s1][s2],dp(x+1,nxt1,nxt2)+c[x]);
//	cout<<d[x][nxt1][nxt2]<<endl;
	return d[x][s1][s2];
}
int main()
{
//	freopen("fuck.out","w",stdout);
	while(1)
	{
		read(n);
		if(!n)return 0;
		read(m);
		read(k);
		memset(a,0,sizeof(a));
		for(int i=1;i<=m+k;i++)
		{
			read(c[i]);
			int x;
			while(1)
			{
				ok=0;
				read(x);
				a[i]|=(1<<x-1);
				if(ok)break;
			}
		}
		memset(d,0x3f3f3f3f,sizeof(d));
		printf("%d\n",dp(1,0,0));
	}
}
```


---

## 作者：Prurite (赞：0)

这一道题确实比较坑，让我 ~~在看了题解之后~~ 琢磨了很久，主要问题在于**细节**很多。

## 题目大意

现在有一些在职教师和一些应聘的老师，每个老师需要一定的工资同时可以教一些科目，在职教师不能解雇，问使每个科目都至少有2位老师教的最小总工资支出。

## 分析与解

### 状压DP
因为此题数据范围很小（只有不超过8个科目），并且每个科目又有多个状态（没人教，1人教，2人教），我们就可以想到用状态压缩的思想进行解题。本题是可以使用3进制状压的，但是为方便我就使用4进制了（用两个2进制位表示一个状态）。

我们设 00，01，11 分别表示一个科目有0人，1人，1人以上时的情况，容易想出先算出所有在职老师可以教的科目情况，再逐个枚举应聘老师进行转移。

令 `dp[i][m]` 表示当前考虑到第 $i$ 个应聘老师，各科目状态为 $m$ 时的最小花费，则
```
dp[i][m]=min( dp[i-1][m], dp[i-1][temp]+c[i] )
```
（其中temp为假设没有该老师时的状态）。

初始化及边界：先全部置为 INF ，然后
```
dp[0][当前在职老师能教的状态]=在职老师的工资和
```

听上去这题就做完了，对吧。

但是这里有一个大坑：试试这组数据
```
2 2 2
10000 1
10000 1
10000 1 2
10000 2
```
如果这么做程序会输出 INF 。

因为题目只要求“每科目有至少2个老师”，换而言之，新聘来的老师的科目与原来已经有2个及以上老师教的科目重复也是可以的。所以，我们还需要把所有“在职教师能教的状态的子状态”的花费也置为原来的花费，即，如果某一科目原来就有2人教了，我们还需要把描述这一科目只有1人教、没人教的状态进行初始化。

此题还有很多细节，具体的实现可以看代码。

注意灵活运用位运算。

## 代码

并不是很优秀，大家凑合着看吧。

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=100+1, MAXS=16, INF=0x3f3f3f3f;
int c[MAXN], a[MAXN];
// a[i]表示第i位老师能教的科目，c[i]表示第i位老师的工资
int dp[MAXN][1<<MAXS];
int s, p1, p2, k1, c1;

inline int min( int a, int b )
{
	return a<b?a:b;
}

inline void read( );
inline int solve( );

int main( )
{
	while ( ~scanf( "%d %d %d", &s, &p1, &p2 ) && s!=0 )
	{
		read( );
		int ans=solve( );
		printf( "%d\n", ans );
	}
	return 0;
}

inline void read( )
{
	memset( a, 0, sizeof a );
	memset( c, 0, sizeof c );
	k1=c1=0;
//	k1表示原在职老师的授课情况，c1表示原总工资
	for ( int i=1; i<=p1; i++ )
	{
		int c2;
		scanf( "%d", &c2 );
		c1+=c2;
		int k2=0;
		while ( getchar( )!='\n' )
		{
			scanf( "%d", &k2 );
			if ( (k1>>2*(k2-1)&3) == 1 )
				k1|=1<<2*k2-1; // 由01改为11
			else if ( (k1>>2*(k2-1)&3) == 0 )
				k1|=1<<2*(k2-1); // 由00改为01
		}
	} // 处理在职老师
	for ( int i=1; i<=p2; i++ )
	{
		scanf( "%d", &c[i] );
		int k2;
		while ( getchar( )!='\n' )
		{
			scanf( "%d", &k2 );
			a[i]|=1<<2*(k2-1);
		}
	} // 读入新老师
	return;
}

inline int solve( )
{
	memset( dp, INF, sizeof dp ); // 初始化为INF
	for ( int m=0; m<1<<2*s; m++ )
	{
		bool ok=1;
		for ( int i=1; i<=s; i++ )
		{
			int x=m>>2*(i-1)&3, y=k1>>2*(i-1)&3;
			if ( x==2 ) ok=0;
			if ( x>y ) ok=0;
		}
		if ( ok )
			dp[0][m]=c1;
	} // 将所有“子状态”的花费设为c1
	for ( int i=1; i<=p2; i++ )
		for ( int m=0; m<1<<2*s; m++ )
		{
			int m1=m;
			dp[i][m]=dp[i-1][m];
			bool ok=1;
			for ( int j=1; j<=s; j++ )
				if ( a[i]&1<<2*(j-1) && ( m&1<<2*(j-1) || m&1<<2*j-1 )  )
				{
					if ( (m>>2*(j-1)&3) == 3 )
						m1^=1<<2*j-1;
					else if ( (m>>2*(j-1)&3) == 1 )
						m1^=1<<2*(j-1);
					else if ( (m>>2*(j-1)&3) == 0 )
					{
						ok=0;
						break;
					}
				}
//				获得“如果当前老师不教”时的状态
			if ( !ok )
				continue;
			dp[i][m]=min( dp[i][m], dp[i-1][m1]+c[i] );
		}
	return dp[p2][(1<<2*s)-1];
}
```
[提交记录](https://www.luogu.org/record/show?rid=8546536)

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

某中学开设有 $s$ 门课程，现有教师 $m$ 个。今天有 $n$ 个求职者来应聘新教师。已知每个人工资和能教授的课程。

在职教师不能辞退，校长想知道，最少支付多少工资就能使得每门课都有至少两名教师能教。

# 题目分析

这是一道状压 $\rm dp$。

令 $dp[i,j,k]$ 表示选了 $i$ 个求职者，集合 $j$ 的课程是正好一个老师讲课的课程集合,集合 $k$ 的课程是至少两个老师讲课的课程集合的情况下，满足条件的最小代价。

对于集合 $s$，若每一位为 $0/1$。例如对于集合 $j$，$j$ 的某一位为 $1$ 表示该位置所对应的课程有且仅有 $1$ 个老师教。

根据定义，答案即为 $dp[n,0,2^s-1]$。

状态转移方程见代码，注释较详细。

这道题输入很坑，很多人用的 `getline`，但其实可以用快读的，改一改就好了。

# 代码

这里只给出单次询问的代码，多次询问请自己实现，多测请注意清零。

```cpp


//2022/3/30
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <utility>
#define enter putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if (x < 0) x += mod;
	return x % mod;
}
typedef std::pair<int,int> PII;
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline PII read() {
		int ret = 1,sum = 0;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-') ret = -1;
			if (ch == '\n' || ch == EOF) return std::make_pair(0,1);
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			sum = sum * 10 + ch - '0';
			ch = getchar();
		}
		if (ch == '\n' || ch == EOF) return std::make_pair(0,1);
		return std::make_pair(ret * sum,0);
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int INF = 0x3f3f3f3f;
const int N1 = 105,N2 = 257;
int cost[N1],teach[N1],dp[N1][N2][N2];
//dp[i][j][k]:选了 i 个求职者,集合 j 的课程正好一个老师讲课的课程集合,集合 k 的课程至少两个老师讲课的课程集合的最小代价 
int s,n,m,sum;
int main(void) {
	scanf("%d%d%d",&s,&m,&n);
	int st1 = 0,st2 = 0;
	for (register int i = 1;i <= m; ++ i) {
		int w;
		scanf("%d",&w);
		sum += w;
		PII now = read();
		while (now.second == 0) {
			int x = now.first - 1;	
			if ((st2 & (1 << x)) == 0) {//这一位为 0,表示不到两个老师教
				if (st1 & (1 << x)) {//这一位为 1,表示有一个老师教
					st1 = st1 ^ (1 << x);//现在有两个老师教了,可以变为 0 了
					st2 = st2 ^ (1 << x);//现在有两个老师教了,可以变为 1 了
				} else {//否则表示有没有老师教
					st1 = st1 ^ (1 << x);//现在有一个老师教了
				}
			}
			now = read();
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		scanf("%d",&cost[i]);
		//teach[i] 表示当前求职者能教的课程集合
		PII now = read();
		while (now.second == 0) {
			int x = now.first - 1;
			teach[i] = teach[i] ^ (1 << x);//第 x 门课能教
			now = read();
		}
	}
	mst(dp,0x3f);
	dp[0][st1][st2] = sum;//一个求职者都不录取,现有老师可以教的代价
	for (register int i = 0;i < n; ++ i) {
		for (register int j = 0;j < (1 << s); ++ j) {
			for (register int k = 0;k < (1 << s); ++ k) {
				if (dp[i][j][k] != INF) {
					//不录取
					dp[i + 1][j][k] = min(dp[i + 1][j][k],dp[i][j][k]);
					//录取
					int to1 = j,to2 = k;
					for (register int v = 0;v < s; ++ v) {
						if ((teach[i + 1] & (1 << v)) == 0) continue;
						if ((k & (1 << v))) continue;
						//必须要能教
						if (j & (1 << v)) {
							to1 = to1 ^ (1 << v);
							to2 = to2 ^ (1 << v);
						} else {
							to1 = to1 ^ (1 << v);
						}
					}
					dp[i + 1][to1][to2] = min(dp[i + 1][to1][to2],dp[i][j][k] + cost[i + 1]);
				}
			}
		}
	}
	if (dp[n][0][(1 << s) - 1] == INF) {
		cout << "-1\n";
	} else {
		cout << dp[n][0][(1 << s) - 1] << "\n";
	}
	
	return 0;
}

```

---

