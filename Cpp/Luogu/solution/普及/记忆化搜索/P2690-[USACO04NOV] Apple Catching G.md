# [USACO04NOV] Apple Catching G

## 题目描述

很少有人知道奶牛爱吃苹果。农夫约翰的农场上有两棵苹果树（编号为 $1$ 和 $2$ ）， 每一棵树上都长满了苹果。奶牛贝茜无法摘下树上的苹果，所以她只能等待苹果 从树上落下。但是，由于苹果掉到地上会摔烂，贝茜必须在半空中接住苹果（没有人爱吃摔烂的苹果）。贝茜吃东西很快，她接到苹果后仅用几秒钟就能吃完。每一分钟，两棵苹果树其中的一棵会掉落一个苹果。贝茜已经过了足够的训练， 只要站在树下就一定能接住这棵树上掉落的苹果。同时，贝茜能够在两棵树之间 快速移动（移动时间远少于 $1$ 分钟），因此当苹果掉落时，她必定站在两棵树其中的一棵下面。此外，奶牛不愿意不停地往返于两棵树之间，因此会错过一些苹果。苹果每分钟掉落一个，共 $T$（$1 \le T \le 1000$）分钟，贝茜最多愿意移动 $W$（$1 \le W \le 30$） 次。现给出每分钟掉落苹果的树的编号，要求判定贝茜能够接住的最多苹果数。 开始时贝茜在 1 号树下。

## 样例 #1

### 输入

```
7 2
2
1
1
2
2
1
1
```

### 输出

```
6
```

# 题解

## 作者：ztzshiwo001219 (赞：96)

这是一个比较简单的DP问题。。。我大概讲一下我的动态转移方程

dp[i][j]表示奶牛在第i分钟内转移了j次能够接到的最多苹果

那么显而易见，对于每一分钟来说，枚举转移次数从而得到解

dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])同时如果 a[i]==j%2+1 即奶牛在这一分钟可以见到苹果 那么把dp[i][j]++

初始化是数组一开始都是0

最终的答案是到第T分钟时奶牛走1~w步能够取得的最多苹果

贴C++代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
int dp[1010][31],T,w,a[1010],ans;
int main()
{
    scanf("%d%d",&T,&w);
    for(int i=1;i<=T;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=T;i++)
        for(int j=0;j<=T&&j<=w;j++)
        {
            if(j==0)dp[i][j]=dp[i-1][j];
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
            if(a[i]==j%2+1)dp[i][j]++;
        }
    for(int i=0;i<=w;i++)
        ans=max(ans,dp[T][i]);
    printf("%d\n",ans);
    return 0;
} 
```
其实应该可以边读入边计算DP 可以留给你们自己尝试
我是蒟蒻。。。


---

## 作者：Preccc_LHW (赞：57)

也是为了（liao）庆祝noip的最后一个晚上

rp值猛升↑↑↑

这里就不多说了。。。


这题我用了记忆化搜索（//实际上是不会dp）

下面是代码加注释：





```cpp
#include <cstdio>      //头文件
#include <iostream>
#include <cstring>
using namespace std;
int n, w, a[1005], f[1005][3][35];          //三维数组f表状态
int dfs(int i,int j,int k)                      //i为时间点，j为哪棵树，k为移动了多少次
{
    if (i > n)return 0;                      //边界条件
    if (f[i][j][k] != -1)return f[i][j][k];   //如果搜过了就直接返回
    int tmp1 = 0, tmp2 = 0;            //tmp1（2）表示决策1（2）的答案
    if (k < w && a[i] != j)                 //决策1（移动到另一棵树），这里有个小剪枝：如果在这个时间点里，当前位置会有果子落下，就不走
        tmp1 = dfs(i + 1, -1 * j + 3, k + 1) + 1;   //-1 * j + 3这里表示移动，你可以把1，2代进去算一下
    tmp2 = dfs(i + 1, j, k) + (j == a[i] ? 1 : 0);     //决策2（不动），如果有果子落下就+1。ps：判断语句一定要加括号，我就是因为这个WA
    return f[i][j][k] = max(tmp1, tmp2);       //返回接到果子多的决策
}
int main()
{
    //freopen("  .in","r",stdin);          //在此提醒广大noip考生，一定要加文件输入输出
    //freopen("  .out","w",stdout);
    cin >> n >> w;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    memset(f, -1, sizeof(f));          //把f数组赋值为-1，头文件<cstring>
    cout << dfs(1, 1, 0);              //开始爆搜
}
```
在这里在次祝所以同学可以在noip菜（赛）场上，
题题A————————————————————————C！


---

## 作者：ksydom (赞：26)

这道题简单的地方有两个：一是数据范围小，二是在不用管大小的情况下方程十分好想。但仍然有一些小细节让我错了两回。
分析过程：
### 1.问啥设啥。
 ......时的最大接苹果数；这里我们发现题目设定上有两个比较明显的变量：总数和移动次数。于是先无脑把他们设出来！于是得
####  f[落下多少个][移动几次]；
### 2.想转移方程，进行补充。
那么这个方程的上一种状态是什么呢？首先捡不捡不一定，但上种状态落下的果子肯定少一，所以第一维是i-1;那么他到底有没有移动呢？我们自然会想到会有以下情况：
①他从另一棵树移过来并且接到了果子；

②他从另一棵树移过来但没接到果子；

③他站着不动接到了一颗果子；

④他站着不动也没接到果子；

但他到底有没有接到果子呢？？？我们并不知道他现在在哪里，所以也不知道他有没有接到果子，于是我们决定多加一维来表示他所在的位置。于是得
#### f[落下多少个][移动次数][现在所处位置]

并得到状态转移方程：
```cpp
if(a[i]==1)
{
    f[i][j][1]=max(f[i-1][j-1][2],f[i-1][j][1])+1;
    f[i][j][2]=max(f[i-1][j][2],f[i-1][j-1][1]);
}
if(a[i]==2)
{
    f[i][j][2]=max(f[i-1][j-1][1],f[i-1][j][2])+1;
    f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][2]);
}

```
于是一号代码长这样：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,w;
int a[1009];
int f[1009][35][3];//落到第几个，移动几次，当前在哪棵树下 
///时的最大接苹果数 
int main()
{
	cin>>t>>w;
	for(int i=1;i<=t;i++){
		cin>>a[i];
	}
	for(int i=1;i<=t;i++){
		for(int j=0;j<=w;j++){
			if(a[i]==1)
			{
				f[i][j][1]=max(f[i-1][j-1][2],f[i-1][j][1])+1;
				f[i][j][2]=max(f[i-1][j][2],f[i-1][j-1][1]);
			}
			if(a[i]==2)
			{
				f[i][j][2]=max(f[i-1][j-1][1],f[i-1][j][2])+1;
				f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][2]);
			}
		}
	} 
	cout<<max(f[t][w][1],f[t][w][2]);
	return 0;
}
```
然后愉快的wa了一个点

#### 经过慎重思考（又读了一遍题）
我发现人刚开始在第一棵树下，那就意味着移动奇数次时人一定在二号树下，偶数次时人一定在一号树下!二者不能同时被修改！所以方程改为：

```cpp
if(a[i]==1)
{
    if(j%2==0)   f[i][j][1]=max(f[i-1][j-1][2],f[i-1][j][1])+1;
    else   f[i][j][2]=max(f[i-1][j][2],f[i-1][j-1][1]);
}           
if(a[i]==2)
{
    if(j%2==1）  f[i][j][2]=max(f[i-1][j-1][1],f[i-1][j][2])+1;
    else   f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][2]);
}
```
然后wa了另外一个点。。。
#### 再次慎重思考（下载数据）后
我发现移动次数最多不一定接到的就最多。比如数据（不是题里的）：
```cpp
7 100
1
1
1
1
1
1
1

```
这样就绝对对不了。于是改为遍历所有移动步数寻找最大值便AC啦！


AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,w;
int a[1009];
int f[1009][35][3];//落到第几个，移动几次，当前在哪棵树下 
///时的最大接苹果数 
int main()
{
    cin>>t>>w;
    for(int i=1;i<=t;i++){
        cin>>a[i];
    }
    for(int i=1;i<=t;i++){
        for(int j=0;j<=w;j++){
            if(a[i]==1)
            {
                if(j%2==0)//偶数 
                {
                    f[i][j][1]=max(f[i-1][j-1][2],f[i-1][j][1])+1;
                }
                else 
                f[i][j][2]=max(f[i-1][j][2],f[i-1][j-1][1]);
            }
            if(a[i]==2)
            {
                if(j%2==1)
                {
                    f[i][j][2]=max(f[i-1][j-1][1],f[i-1][j][2])+1;
                } 
                else 
                f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][2]);
            }
        }
    } 
    int ans=-1;
    for(int j=0;j<=w;j++)
    {
        ans=max(ans,max(f[t][j][1],f[t][j][2]));
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：雪颜 (赞：19)

之前的题解有动态规划，也有三维记忆化搜索，我写了一个二维的记忆化搜索，C++党，仅供参考。

```cpp
#include<map>
#include<set>
#include<list>
#include<cmath>
#include<deque>
#include<queue>
#include<stack>
#include<bitset>
#include<cstdio>
#include<time.h>
#include<vector>
#include<climits>
#include<cstdlib>
#include<cstddef>
#include<cstring>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<iostream>
#include<memory.h>
#include<algorithm>
#include<sys/types.h>
#include<bits/stl_algo.h>
using namespace std;
const int ML=10005;
int f[ML][ML/100+1];
int a[ML];
int n,w;
int DFS(int i,int last,int yd){ //i:当前的时刻 last:上次的位置 yd:移动次数
    if(i>n) return 0;
    if(f[i][yd]!=-1) return f[i][yd]; //f[i][yd]:在第i个时刻移动yd次可以得到的最大值
    f[i][yd]=0;
    if(a[i]==last) f[i][yd]=DFS(i+1,a[i],yd)+1; //上次与这次位置相同，不用移动，直接可以接苹果
    else{
        f[i][yd]=DFS(i+1,last,yd); //上次与这次位置不同， 不移动
        if(yd<w) f[i][yd]=max(DFS(i+1,a[i],yd+1)+1,f[i][yd]); //可以移动，比较移动和不移动哪个划算
    }
    return f[i][yd];
}
int main(){
    scanf("%d%d",&n,&w);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    memset(f,-1,sizeof(f));
    printf("%d",DFS(1,1,0));
    return 0;
}
```

---

## 作者：kcn999 (赞：17)

已有题解里没人压缩dp空间为一维？

在这里发一篇只用一维空间的dp题解。

1.首先以时间的递进为状态，可以推出来这就是一道普通的线性dp。

2.因为只有两棵树且初始为第一棵树下，所以移动奇数次到达第二颗树，移动偶数次则到达第一棵树。

知道这两个点后，就可以直接上代码了。

 ```cpp
#include <iostream>

#define MAX_N 31
// 可以理解为const int MAX_N 31

using namespace std;

int t, n;
int dp[MAX_N]; // 移动了i次后的苹果最优方案，这里运用了滚动数组
int ans;

int main()
{
    cin >> t >> n;
    int v; 
    for(register int i = 1; i <= t; ++i)
    // 第i分钟
    // register为寄存器，可以不加，不会影响代码运行结果，但在循环次数大的时候，因为调用i的次数多，所以可以节省一点的时间
    {
    	cin >> v;
	    for(register int j = min(i, n) - ((v & 1) == (min(i, n) & 1)); j >= 0; j -= 2)
        // 第j次移动时到达当前这棵树v
        // min(i, n)：因为当i < n时，最多只有i次移动，所以就这么求最小值
        // & 1可以理解为 % 2
        // 如果当前树的编号的奇偶性与最多移动次数n的奇偶性相同，就最多只能移动(n - 1)次从而回到当前这棵树，具体可以自己带入数据验证
        // j -= 2： 因为要再移动2次才能回到当前的树，所以就- 2
	    {
	    	if(j) dp[j] = max(dp[j], dp[j - 1]) + 1;
            // 如果j不为0，那么就可以从原地不动和从第j-1次移动到另一棵树后在移动回这一棵树中的最优方案
            else ++dp[j];
            // 如果j为0，那么就代表无法移动，所以就只能在最开始的第一棵树捡苹果（j = 0时v就为1）。
		}
    }
    for(register int i = 0; i <= n; ++i)
    {
    	ans = max(ans, dp[i]); // 找最优解
	}
    cout << ans;
    return 0;
}
```

这是自己的第一篇题解，自认为还是会有很多不足之处，欢迎指正。

---

## 作者：微香玉烛暗 (赞：11)

看到了$dfs$记搜，现在只想说一句：$DP$大法好。。。

$DP$思路很简单啊，看了几篇题解，都和我不一样！？于是，写一篇吧，造福谷民，$RP$++;

f[i][j]表示在时间i时转移了j次能接到的苹果最大值


```cpp
#include<cstdio>
using namespace std;
const int N=10005;
const int M=105;
int f[N][M],g[N][M];
int t,w,ans;
int ma[M];
//以上部分不需在意
int min (int x,int y) {
    return x<y?x:y;
}

int max (int x,int y) {
    return x>y?x:y;
}
//这里是自己写的min、max，因为algorithm库里的好慢
int main() {
    f[0][0]=-1e9;//把0,0赋为无穷小
    scanf("%d %d",&t,&w);
    for(int i=1;i<=t;i++) {
    	int a; scanf("%d",&a);
    	int k; k=min(w,i);//k在w和当前时间i之间取小
    	for(int j=k;j>=0;j--) {
    		if(j==0) {
    			f[i][j]=f[i-1][j];
                g[i][j]=g[i-1][j];//如果只剩j==0次转移，那么毋庸置疑，等于上一个时间的数量
            }
    		else {
        		f[i][j]=max(f[i-1][j],g[i-1][j-1]);
        		g[i][j]=max(g[i-1][j],f[i-1][j-1]);
                //上一个时间点中，本棵树与另一棵树转移次数减1取最大值
    		}
    		if(a==1) g[i][j]++;//1号树掉苹果了！！
    		else f[i][j]++;//2号
    	}
    }
    //当然，最后的答案为：max{max{g[t][i],f[t][i]}}
    for (int i=0;i<=w;i++)
    	ma[i]=max(g[t][i],f[t][i]);
    for (int i=0;i<=w;i++)
    	ans=max(ans,ma[i]);
    printf("%d\n",ans);//答案
    return 0;
}
```
思路还好，简单明了。求过。谢谢管理员

---

## 作者：dujiale (赞：9)

## **~~又刷完了一道DP水题！~~**
### 言归正传，其实这道题的站状态转移方程不难想到，我们设:
##  _f[i][j]_ 为第i分钟奶牛移动了j次接到苹果的最大值；
## **则f[i][j]=max(f[i-1][j],f[i-1][j-1]),同时要加上此时在当前接到的苹果数，即加一。**
### ~~是不是很easy？~~
## 上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,w;
int a[1001];
int f[1001][31];//变量名,数组名本人自以为立意明确，相信大家都看得懂
int main()
{
	cin>>t>>w;//输入奶牛共有t分钟和最多移动w次
	for(int i=1;i<=t;i++)
		cin>>a[i];//输入，若a[i]为1，则第i分钟的苹果是从1号苹果树上掉下来的，a[i]为2则是从2号苹果树上掉下来的。
//下面进入核心代码：    
	for(int i=1;i<=t;i++)//i列举1到t分钟
	{
		f[i][0]=f[i-1][0];//f[i][0]先初始化为前一分钟移动0次的次数，大家一定都理解
		if(a[i]==1)
			f[i][0]++;//但是当前是有可能接住第i个苹果的，由于f[i][0]是没有移动过的，而奶牛的初始位置在1号苹果树，所以我们只要判断第i分钟的苹果是不是从1号苹果树上掉下来的，如果是，那么f[i][0]加一
		for(int j=1;j<=w;j++)//j从1到w列举奶牛移动了几次，由于前面没有移动的状态列过了，所以j从1开始
		{
			int f1,f2;
			if(j%2+1==a[i])
				f1=1,f2=0;//判断移动j次时苹果在不在当前位置
			else
				f1=0,f2=1;//否则移动j-1此时能接到当前苹果
			f[i][j]=max(f[i-1][j]+f1,f[i-1][j-1]+f2);//状态转移，要注意的是苹果不是在f[i-1][j]，就是在f[i-1][j-1]，所以f[i-1][j]要加上f1，f[i-1][j-1]要加上f2,有些难理解
		}
	}
	int ans=0;//定义答案变量ans
	for(int i=0;i<=w;i++)//i列举第t分钟移动0到w次
		ans=max(ans,f[t][i]);//ans找出最大值
	cout<<ans;//输出答案ans
	return 0;//程序完美谢幕啦
}
```
# 第一次写题解
# 各位大侠不喜勿喷!
# 各位大侠不喜勿喷!
# 各位大侠不喜勿喷!

---

## 作者：AkiwaZawa (赞：9)

## 记忆化搜索

最近学了记忆化搜索，闲来无事写写题解

（详情注释请见代码）

```
#include<bits/stdc++.h>
#define N 1010
using namespace std;
int n,m,f[N][N],a[N],ans;
int dfs(int k,int s,int t)//k表示移动了几次 s表示在第几颗树下 t表示已过时间
{
	if(t>n) return 0;// 时间已经全部过完
	if(f[t][k]) return f[t][k];
    if(s==a[t]) 
        f[t][k]=dfs(k,a[t],t+1)+1;
    // 如果当前所站的树正好与当前时间所掉果子的树相同，接住果子，时间+1，果子数+1.
    else
    {
        f[t][k]=max(f[t][k],dfs(k,s,t+1));
        if(k<m) f[t][k]=max(f[t][k],dfs(k+1,a[t],t+1)+1);
    }
    //如果不相同，则可以移动也可以不移，如果当前移动的步数少于规定值则可以移动。
    return f[t][k];
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];                       
    printf("%d",dfs(0,1,1));//移动了零次，时间过去了一秒，站在第一棵树下
    return 0;
}
```


---

## 作者：Drinkwater (赞：7)

dp大法好，我们用dp[i][j][k]表示第i分钟，移动j步，在k颗树下（k用0，1表示）

如果不移动dp[i][j][k] = dp[i-i][j][k]+(这分钟这棵树下能不能捡到果子)

移动的话dp[i][j][k] = max(dp[i-1][j-1][k^1]+(这分钟这棵树下能不能捡到果子),dp[i-1][j][k]);

代码如下

：：




```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
using namespace std;
#define REP(i,a,b) for(register int i = (a), i##_end_ = (b); i <= i##_end_ ; ++i)
inline int read()
{
    char c = getchar(); register int fg = 1,sum = 0;
    while(c < '0' || c > '9')
    {
        if(c == '-')fg = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
    {
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return fg * sum;
}
int n, K;
int t[1010];
int dp[1010][50][2];
int main()
{
    n = read(), K =read();
    REP(i,1,n)t[i] = read();
    REP(i,1,n)
    {
        REP(j,0,K)
        {
            REP(k,0,1)
            {
                int f=(k+1==t[i]);
                dp[i][j][k] = dp[i-1][j][k]+f;
                dp[i][j][k] = max(dp[i-1][j-1][k^1]+f,dp[i][j][k]);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=min(n,K);++i)
        if(dp[n][i][i%2]>ans) ans=dp[n][i][i%2];
    printf("%d",ans);
    return 0;
}
```

---

## 作者：原株龙葵 (赞：5)

# P2690 接苹果
------------
我知道，我知道。对于诸位大佬来说，这道题很简单。

但对于本蒟蒻而言，做出这套题，着实让我超级高兴。

因为，我想出来了一个**更加优化的解法**。

各位大佬的代码我都看过了。就是dp呗。

**不过**我有一个更优化的方法。

就是，先统计每次连着在一个树下掉落的苹果数。

例如：1 2 2 1 1 2 2

就可以化简为：1 2 2 2

1 1 2 2 2 1 1 1 1 1 2 1 2 1 2

可化简为：2 3 5 1 1 1 1 1

这么做之后，在dp。肯定会**更快**。
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int T,W,as,s;
int dt[1000],dtp;
int t,tt,m;
int map[30][1000];
int walk(int tim,int loc){//dfs没商量
	if(loc>=dtp) return 0;
	if(tim==0){
		int ass=0;
		for(int i=loc;i<dtp;i+=2){
			ass+=dt[i];
		}
		return ass;
	}
	int a;
	int b;
	if(!map[tim][loc+2]){//dp优化
		a=walk(tim,loc+2);
		map[tim][loc+2]=a;
	}else a=map[tim][loc+2];
	
	if(!map[tim-1][loc+1]){
		b=walk(tim-1,loc+1);
		map[tim-1][loc+1]=b;
	}else b=map[tim-1][loc+1];
	return max(a,b)+dt[loc];
}
int main(){
	cin>>T>>W;
    
	for(int i=0;i<T;i++){//把数据改写成单棵树下连续最多接到苹果数
		cin>>t;
		if(!tt){
			s=t;
			m=0;
			tt=t;
			continue;
		}
		if(t==tt){
			m++;
		}else{
			dt[dtp++]=m+1;
			tt=t;
			m=0;
		}
	}
	dt[dtp++]=m+1;
    
	if(s==1){//判断第一次掉落是哪棵树1还是2
		as+=max(walk(W,0),walk(W-1,1));//要是1就不用减次数就可以开始dfs
	}else{
		as+=max(walk(W-1,0),walk(W,1));//反之亦然
	}
    
	cout<<as<<endl;//输出结果
	return 0;
}
```
本蒟蒻做出**普及**很激动，代码上的不足请诸佬指正
觉得写得好别忘点个赞，谢谢

---

## 作者：千反田 (赞：3)

一道DFS题 （~~本蒟蒻不会dp~~）

但是如果爆搜会进行重复的搜索

浪费大量时间

怎么办？


------------


## 记忆化搜索

用trace这个三维数组表示状态
```cpp
trace[1005][3][35] //时间 在哪棵树下 剩余的移动次数
```
如果已经搜索过 直接查找那个值 返回

```cpp
if(trace[time][tree][left]!=-1)
	 return trace[time][tree][left];
```
这样可以不进行重复搜索 节省大量时间复杂度

~~但是提高了空间复杂度啊~~

# 祭上代码
```cpp
#include<bits/stdc++.h>
#define N 1005
#define inf INT_MAX
int apple[N],t,w,trace[N][3][35];
inline int Depth_First_Search(int time,int tree,int left)//时间 在哪棵树下 剩余的移动次数
{
	int temp_move=-inf,temp_static=-inf;//233
	if(time>t)
	 return 0;//边界判定
	if(trace[time][tree][left]!=-1)
	 return trace[time][tree][left];//记忆化
	if(left<w&&apple[time]!=tree)//这里借鉴了题解里dalao的一个小剪枝：
                                 //如果当前树上有苹果落下，就不走
	 temp_move=Depth_First_Search(time+1,tree==1? 0:1,left+1)+1;//移动
	temp_static=Depth_First_Search(time+1,tree,left)+(tree==apple[time]? 1:0);//不移动
	trace[time][tree][left]=std::max(temp_move,temp_static);//选择两者较大的值
	return trace[time][tree][left];//返回
}
int main()
{
	memset(trace,-1,sizeof(trace));//初始化
	scanf("%d%d",&t,&w);
	for(int i=1;i<=t;++i)
	 scanf("%d",&apple[i]);
	printf("%d",Depth_First_Search(1,1,0));
    return ~~(0-0);//卖萌求通过
}
```




---

## 作者：jackyzhu (赞：3)

f[i][j][1]表示最多走i步，时刻j处于第1棵树下的最多苹果数

f[i][j][2]表示最多走i步，时刻j处于第2棵树下的最多苹果数

最后答案=max(f[w][t][1],f[w][t][2])

dp公式：

对当前时刻j的苹果进行判断：

如果从第1棵树掉下来，

f[i][j][1]=max(f[i][j-1][1]+1,f[i-1][j-1][2]+1); //dp公式分两种情况讨论，最后一次移动在时刻j，最后一次移动不在时刻j

f[i][j][2]=max(f[i][j-1][2],f[i-1][j-1][1]);

如果从第2棵树掉下来：

f[i][j][1]=max(f[i][j-1][1],f[i-1][j-1][2]);

f[i][j][2]=max(f[i][j-1][2]+1,f[i-1][j-1][1]+1);

dp初始，由于刚刚开始在第一棵树下，所以：

f[0][j][1]的 值等于输入序列中到j时刻为止出现的1的个数


AC代码：


        
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,w;
int a[1001];
int f[31][1001][3];
int main()
{
    scanf("%d%d",&t,&w);
    for(int i=1;i<=t;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]==1)
        {
            f[0][i][1]++;
        }
        f[0][i][1]+=f[0][i-1][1];
    }
    //f[0][0][1]=1;    
    for(int i=1;i<=w;i++)
        for(int j=i;j<=t;j++)
        {
            if(a[j]==1)
            {
                f[i][j][1]=max(f[i][j-1][1]+1,f[i-1][j-1][2]+1);
                f[i][j][2]=max(f[i][j-1][2],f[i-1][j-1][1]);
            }
            else
            {
                f[i][j][1]=max(f[i][j-1][1],f[i-1][j-1][2]);
                f[i][j][2]=max(f[i][j-1][2]+1,f[i-1][j-1][1]+1);
            }
        }
    printf("%d",max(f[w][t][1],f[w][t][2]));
}
```

---

## 作者：用户已注销 (赞：2)


/\*
题解：

先进一点的DP

虽然时间都是0Ms，但是如果数据扩大以下算法将有时间+空间优势

首先可以贪心发现，如果下一个苹果和当前的苹果在一棵树上

那么一定没有必要换到别的树下

所以我们可以将所有苹果归为几“波”

其中每一次1号树上和2号树上掉若干的苹果为1波

（总是1号树先，如果第一个是2则为0）

设数组A[1000]，第i位表示i/2+1波第(i+1)%2+1树上掉下的苹果

接下来设数组F[30][500]表示第i次更换位置，此时已经接住了第j波苹果

（虽然最多可能有1000组苹果，但是只有500波）

接下来开始循环：

F[I][J]由以下三种情况转来：

（1）不换，在这颗树下接下一波

（2）换，从1换2则接两波，从2换1则延续上一波（上一次已经抉择了接哪边）

输出F[W][K/2]，其中一共K/2波

代码：

\*/
```cpp
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<iostream>
#define r register 
using namespace std;
int a[1001],f[31][501];
//f[i][j] : 第i次更改的时候，接住第j波苹果 
//a[i] : i%2树的第i/2+1波苹果（贪心可得，没事不要瞎换） 
int w,t,k=0;
int main()
{
    memset(a,0,sizeof(a));
    scanf("%d%d",&t,&w);
    for(r int i=1;i<=t;i++)
    {
        r int c;
        scanf("%d",&c);
        if(c!=k%2+1) k++;//换树 
        a[k+1]++;//当前树+1 
    }
    k%2?k++:k+=2;//补满
    if((a[k]==0 and w>=k-2) or (a[k]!=0 and w>=k-1))
        return !printf("%d\n",t);//如果可以换很多次，一定可以接到所有
    f[0][0]=0;//初始化 
    for(r int i=0;i<=w;i++)
        f[i][1] = i%2==0 ? a[1] : a[1]+a[2] ;//第一波苹果 
    for(r int i=1;i<=k/2;i++)
        f[0][i] = f[0][i-1] + a[i*2-1] ;//第零次更改（不更改） 
    for(r int j=2;j<=k/2;j++)//枚举第j波苹果
        for(r int i=1;i<=w;i++)//枚举当前更换了i次
            f[i][j]=/*每一步的状态由上一步推出*/
            max(
            f[i][j-1]+a[j*2-(i+1)%2],/*不换*/
```
i%2?f[i-1][j-1]+a[j\*2]+a[j\*2-1]:f[i-1][j]/\*换\*/
            );

    return !printf("%d\n",f[w][k/2]);//输出最后一波并换最多次 

}

---

## 作者：Suuon_Kanderu (赞：1)

记忆化搜索，详细篇，适合新手。

大佬： 你想知道如何用一行代码 从 暴力 → 正解 吗？

我：愿闻其详。

首先，你肯定会写 dfs ，于是你写出了这样的代码（虽然简单但也良心给注释了）

设$f(i,j,k)$表示在第 i 分钟，移动了 j 次，在第 k 棵树下最多能得到多少果子。设 g 这分钟我们能否接到这个果子，t 和 w 的含义同题。写出了这样的表达式。

P.S.这里我们把第1、2棵树换成1、0棵树。方便奶牛移动


$$ f(i,j,k)=\left\{
\begin{aligned}
 & 0 & (i >t) \\
 & \max(f(i+1,j+1,!k),f(i+1,j,k)) + g & (j+1 <= w) \\
 & f(i+1,j,k) + g  & (j+1>w)
\end{aligned}
\right.
$$

- 第一种情况就是边界条件。
- 第二种就是奶牛还能移动，则取移动和不移动中的最大值。
- 第三种就是不能移动了，只能干巴巴等着了。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int t,w,a[1100];
//这里我们把第1、2棵树换成1、0棵树。方便转移树
int dp(int i,int j,int k) {
	//分钟，移动了几次,在哪个树下 
	if(i > t)return 0;//边界
	//把 树 看成 1和 0 
	int g = 0;//g 就看做当前是否在要掉苹果的树下
	if(a[i] == k)g = 1;//如果此时树掉下来苹果，总数就加1
	if(j+1 <= w) return max(dp(i+1,j+1,!k),dp(i+1,j,k)) + g;
    //如果cow还能再移动一次，就取移动和不移动中的最大值
	else return  dp(i+1,j,k) + g;
    //否则只能不移动了。
}
int main() {
	cin >> t >> w;
	int h;
	for(int i = 1; i <= t; i++) {
		scanf("%d",&h);
		if(h == 2)a[i] = 0;
		else a[i] = 1;
	}
	cout <<dp(1,0,1);
}

```
然后

![](https://cdn.luogu.com.cn/upload/image_hosting/c9ouj1e5.png)

太慢了，我们要想办法加快速度。

按理说，不应该啊。如果每个$f(i,j,k)$只算一遍，那么时间是$30 \times 1000 \times2$，不会超时啊。

如果你意识到了这一点，就离成功不远了。你注意到了吗？我们每个$f(i,j,k)$其实不是只会算一遍，我们会算 N 多遍，导致复杂度是指数级的。

我们的目标转移为使每个$f(i,j,k)$只算一遍：只算一次，我们就把第一次算出的结果存起来，以后用不就 ok 了。是的，你没有听错，用一个三维数组存我们算出的数据，如果我们发现我们当前的$f(i,j,k)$算过了，直接拿来用。（简单）

只是加了一行,就可以享受 AC 的快感！（当然还把第一次算出的结果存储一下）

$$if(f[i][j][k])return~f[i][j][k];$$

Code:
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int f[1100][35][3],t,w,a[1100];
int dp(int i,int j,int k) {
	//分钟，移动了几次,在1/0的树下 
	if(i > t)return 0;
	if(f[i][j][k])return f[i][j][k];
	//把 树 看成 1和 0 
	int g = 0;
	if(a[i] == k)g = 1;
	if(j+1 <= w)return f[i][j][k] = max(dp(i+1,j+1,!k),dp(i+1,j,k)) + g;
	else return f[i][j][k] = dp(i+1,j,k) + g;
}
int main() {
	cin >> t >> w;
	int h;
	for(int i = 1; i <= t; i++) {
		scanf("%d",&h);
		if(h == 2)a[i] = 0;
		else a[i] = 1;
	}
	cout <<dp(1,0,1);
}


```




---

## 作者：叶枫 (赞：1)

看题解都是用DP ，蒟蒻就发下搜索的题解吧。
____
**思路如下↓**
```
最初状态：站在第一棵树下，时间过去了一秒，移动了零次。
判断边界条件：时间已经全部过完。
然后进行搜索。如果当前状态已经别更新过则没有更新的必要，直接return。
如果当前所站的树正好与当前时间所掉果子的树相同，接住果子，时间+1，果子数+1。
如果不相同，则可以移动也可以不移，如果当前移动的步数少于规定值则可以移动。
```
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<stack> 
#define ll long long
#define INF 2147483647
#define re register 
#define maxn 1010
using namespace std;
//请忽略

inline int read()//快读
{ 
    int x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();} 
    while(isdigit(c)){x=x*10+c-48;c=getchar();}
    return x*f;
}

inline void put(int x)//快输
{
     if(x<0) putchar('-'),x=-x;
     if(x>9) put(x/10);
     putchar(x%10+'0');
}

int n,m,f[maxn][maxn],a[maxn],ans;

inline int dfs(int t,int s,int k)//t表示已过时间，s 表示他站在第几颗树下，k表示他移动了几次 
{
    if(t>n) return 0;
    if(f[t][k]) return f[t][k];
    if(s==a[t]) 
        f[t][k]=dfs(t+1,a[t],k)+1;
    else
    {
        f[t][k]=max(f[t][k],dfs(t+1,s,k));
        if(k<m) f[t][k]=max(f[t][k],dfs(t+1,a[t],k+1)+1);
    }
    return f[t][k];
}

int main()
{
    n=read(),m=read();
    for(re int i=1;i<=n;i++) 
	a[i]=read();                           
    ans=dfs(1,1,0);
    put(ans);
    return 0;
}
```
_____
~~记忆化搜索好难~~

望管理大大给过
_____
*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：桜Sakura (赞：1)

AC代码：

~~直接看程序好了~~

```cpp
//writer: Sakura
//name: 接苹果

#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int t,w;
int a[1005];
int f[1005][3][35];//三维分别为第几分钟，哪一棵树1/2，移动次数
int ans=0;

int dfs(int i,int j,int k){//第i分钟，第j棵树下1/2，移动k次
	if(i>t)return 0;//时间到了
	if(f[i][j][k]!=-1)return f[i][j][k];//记忆化
	int res1=0,res2=0;
	if(k<w && a[i]!=j){//还没移动到限制的次数并且需要移动，即此时有苹果的树并非现在在的树
		if(j==1){res1=dfs(i+1,j+1,k+1)+1;}//如果在1树下，就去2树下
		else{res1=dfs(i+1,j-1,k+1)+1;}//如果在2树下，就去1树下
		//以上两种情况，分钟移动次数均加一
	}
	int tmp=0;
	if(j==a[i])tmp=1;//就在有苹果的树下，可以接到苹果，所以tmp=1
	else tmp=0;//接不到苹果，tmp=0
	res2=dfs(i+1,j,k)+tmp;//不移动+此分钟是否有苹果1/0
	return f[i][j][k]=max(res1,res2);//记忆化移动还是不移动得到的最大苹果数
}

int main(){
	scanf("%d %d",&t,&w);
	for(int i=1;i<=t;i++){
		scanf("%d",&a[i]);
	}
	memset(f,-1,sizeof(f)); 
	ans=dfs(1,1,0);//第一分钟，第一棵树下，没有移动
	printf("%d\n",ans);
	return 0;
}
```

解释的比较详细，管理员大大给过QWQ

---

## 作者：深海鱼的眼泪 (赞：1)

DP，f[i][j][1]表示i时刻移动j次站在第1棵树下吃到的苹果个数，f[i][j][2]表示移动i次站在第2棵树下吃到的苹果个数，a[i]表示i时刻掉苹果的树，

状态转移方程是 f[i][j][a[i]]=max(f[i-1][j][a[i]]+1,f[i-1][j-1][3-a[i]]+1),j>0

f[i][j][a[i]]=f[i-1][j][a[i]]+1,j=0 且a[i]=1（因为一开始站在1号树下，所以移动0次只能站在1号树下）

                          f[i][j][3-a[i]]=f[i-1][j][3-a[i]]

然后我们可以把数组滚动起来，变成二维的  f[j][1]表示移动j次站在第1棵树下吃到的苹果个数，f[j][2]表示移动j次站在第2棵树下吃到的苹果个数，注意k要逆序循环，

状态转移方程为 f[j][a[i]]=max(f[j][a[i]+1,f[j-1][3-a[i]]+1),j>0


```cpp
                          f[j][a[i]]++,j=0且a[i]=1
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int f[35][3],a[1010];
int main(){
    int t,k,i,j;
    cin>>t>>k;
    for (i=1;i<=t;i++){
        scanf("%d",&a[i]);
    }
    for (i=1;i<=t;i++){
        for (j=k;j>=0;j--){
                if (j>0){
                    f[j][a[i]]=max(f[j][a[i]]+1,f[j-1][3-a[i]]+1);
                }else if (a[i]==1) f[j][a[i]]++;
        }
    }
    cout<<max(f[k][1],f[k][2]);
    return 0;
}
```

---

## 作者：za_233 (赞：1)

我看并没有人喜欢用递归啊！！！

用递归的格式写DP十分的好懂！！

我来一发！

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;
int t,w;
int app[1000];
int mem[10][2000][40];
int doit(int pale,int time,int c)       //pale:此时处于的位置     time:状态（时间）     c:所剩的交换次数
{
    if(time==t+1) return 0;     //边界
    if(mem[pale][time][c]!=-1) return mem[pale][time][c];      //记忆化
    int a=0,b=0;
    int a1=0,b1=0;
    if(app[time]==1) a1+=1;       //如果在1且有苹果 则标记加1
    if(app[time]==2) b1+=1;      //若果在2且有苹果   则标记加1
    if(c>0 && pale==1) a=doit(2,time+1,c-1)+a1;      //若交换，分别处理在1与在2的情况
    else if(c>0 && pale==2) a=doit(1,time+1,c-1)+b1;
    if(pale==1) b=doit(pale,time+1,c)+a1;       //若不交换，分别处理。。。。。
    else b=doit(pale,time+1,c)+b1;
    mem[pale][time][c]=max(a,b);      //记住状态，记忆化搜索
    //printf("pal:%d    time:%d     c:%d     ans:%d\n",pale,time,c,max(a,b));
    return mem[pale][time][c];        //返回哪个更值     放还是不放
}
int main()
{
    memset(mem,-1,sizeof(mem));
    cin>>t>>w;
    for(int i=1;i<=t;i++)
        cin>>app[i];
    cout<<doit(1,0,w);    //开始在1处且时间为零（未开始） 还有w次交换次数
    return 0;
} 
```
其实我不太推荐这种做法！！耗时间与空间
但增加了可读性！！


---

## 作者：彩虹猫 (赞：1)

## P2690 接苹果 题解
### 此题的正解是dp（~~记忆化搜索FAKE~~）
- 用dp\[i]\[j]表示 i分钟后移动j次所能接到的最多苹果数  

- 注意！i指的是前i分钟总共能接到的水果，但j仅仅只是移动j次的情况，移动1~j-1次的情况并不包括在内。   
***********************
- 初始化：不需要（后面会讲）

- 输入：用apple[i]表示第i分钟的苹果掉在哪

- 核心部分：根据一般dp的写法设两层循环，外层循环控制时间，内层循环控制步数。在每一次**i循环**的最开始（即j循环未开始时）对dp[i][0]进行初始化：首先dp[i][0]=dp[i-1][0]（不能移动），然后若第i分钟苹果掉在1处则dp[i][0]++（想一想，为什么）

  dp[i][j]的一般状态转移方程：
```cpp
	dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
	if(apple[i]==j%2+1) dp[i][j]++;
```
- 意味着 _**此状态可以由前一分钟移或不移转移而来**_ 。
**********************************
### 最后贴上完整代码



```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[1005][35];
int apple[1005];
int main()
{
    int t,w,i,j;
    scanf("%d%d",&t,&w);
    for(i=1;i<=t;i++)
    {
        scanf("%d",&apple[i]);
    }
    for(i=1;i<=t;i++)
    {
        dp[i][0]=dp[i-1][0];
        if(apple[i]==1) dp[i][0]++;
        for(j=1;j<=w;j++)
        {
            dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
            if(apple[i]==j%2+1) dp[i][j]++;
        }
    }
    int ans=0;
    for(i=0;i<=w;i++)
    {
        ans=max(ans,dp[t][i]);
    }
    printf("%d\n",ans);
    return 0;
}
```


[MY BLOG](https://www.luogu.org/blog/team046/)

---

## 作者：cenbinbin (赞：1)

发一个dp的程序

```cpp
==========================================================
var
  f:array[0..1001,0..30] of longint;
  a:array[0..1001] of longint;
  i,j,n,time,ans:longint;
function min(x,y:longint):longint;//取最小值
begin
  if x>y then exit(y) else exit(x);
end;
function max(x,y:longint):longint;//取最大值
begin
  if x>y then exit(x) else exit(y);
end;
begin
  readln(n,time);
  for i:=1 to n do
   begin
     readln(a[i]);
     a[i]:=a[i] mod 2;//只要奇偶就行
   end;
  for i:=1 to n do
   f[i,0]:=f[i-1,0]+a[i] mod 2;
  for i:=1 to n do
   for j:=1 to min(i,time) do//取小的做即可
    begin
      f[i,j]:=max(f[i-1,j],f[i-1,j-1]);
      if a[i]=(j+1) mod 2 then inc(f[i,j]);
    end;
  ans:=0;
  for i:=0 to time do
   if f[n,i]>ans then ans:=f[n,i];//寻找最大值
  writeln(ans);//输出
end.
```

---

## 作者：MuYC (赞：0)

## 记忆化大法好！

## 步骤：
１.进行题意理解

２．根据题意进行模拟，暴力搜索（先打一个暴力然后才好优化）

３．利用记忆化优化搜索进行优化，根据题目要求记录下四个状态

①此时的时刻（Ｔ）

②此刻剩下多少次移动机会

③此时位于哪棵树下

④目前摘到了多少个苹果

一共需要一个数组：book[1001][31][2][1001],可以是ｂｏｏｌ类型的，所以空间不会爆炸，但是比较紧张（第一维表示现在的时刻，第二维表示剩下的机会，第三维表示位于的树下，第四维表示摘到了多少个苹果）

４．迎接ＡＣ的喜悦

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,w,res=0;
int a[1000+5];
bool b[1005][31][2][1000];
int dfs(int tim,int s,int t,int p){
    if(a[tim]==t)p++;
    res=max(res,p);
        if(b[tim][s][t-1][p] == 1)return 0;
        b[tim][s][t-1][p]=1;
    if(tim < T){
        if(s >= 1){
           if(t == 1)dfs(tim+1 , s-1 , 2 , p);
           else dfs(tim+1 , s-1 , 1 , p );
        }
        dfs(tim+1 , s , t , p);
    }
     return res;
}
int main(){
    cin>>T>>w;
    for (int i = 1 ; i <= T ; i ++)cin>>a[i];
    dfs( 1 , w , 1 , 0);
    cout<<res;
    return 0;
}
```


## 总结：

记忆化应当注意记录的状态是什么，这样同时需要节省空间，能小尽量小，为题目节省空间．

---

## 作者：StephenYoung (赞：0)

哇，有没有搞错啊，一道黄题终于做出来（有种被虐的感觉）

嗯，做题的过程体现出细节的重要性，比如我最早以为是1,2两个点都可以作为起点，其实不然

回到正题

树一共有1,2两种状态，可以想到用0,1来替代但题目中的1和2，这一点待会还有妙（wu）用

我们用$f[i][j]$来表示第$i$分钟走$j$步的最大价值

又因为只有两种状态，所以走偶数步一定在起点，奇数反之

所以得到

$f[i][j]$ = max ($f[i][j]$,max($f[i-1][j-1]$,$f[i-1][j]$)+$j$%2==$a[i]$)

当然还有边界

$if(j==0)$ $f[i][j]=f[i-1][j]$;

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int w,t,a[1005],ans,f[1005][1005];

int cmp(int x,int y)
{
	if(x==y) return 1;
	else return 0;
}

void init()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
}

int main()
{
	//init();
	scanf("%d%d",&t,&w);
	for(int i=1;i<=t;i++)
	{
		scanf("%d",&a[i]);
		a[i]--;
	}
		for(int i=1;i<=t;i++)
		{
			for(int j=0;j<=w;j++)
			{
				if(j==0) f[i][j]=f[i-1][j];
				f[i][j]=max(f[i][j],max(f[i-1][j-1],f[i-1][j])+cmp((0+j)%2,a[i]));
			}
		}
	for(int i=1;i<=w;i++)
	ans=max(ans,f[t][i]);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：神犇梦的蒟蒻 (赞：0)

看了很多大佬都是设时间数组，其实不设可以更快

用f【i】【l】表示移动i次在l树下时最多可以吃多少

跟随时间输入来递推

输入 落下的树a

则动态方程f【i】【a】=max（f【i】【a】，f【i-1】【3-a】）+1；

我们只需要管在a树下方程的变化（毕竟另一棵树没变化）

f【i】【a】表示本来就在树下，f【i-1】【3-a】表示从另一棵树花一次移动机会来吃，比较两者大小，谁大谁吃。

3-a表示另一棵树  3-1=2 ，   3-2=1

代码时间
```
#include<bits/stdc++.h>
using namespace std;
int t,w,a;
int f[35][3];
int main()
{
cin>>t>>w;
for(int i=1;i<=t;i++）
{
cin>>a;
for(int j=w;j>0;j--) f[j][a]=max(f[j][a],f[j-1][3-a])+1;
if(a==1) f[0][1]++;//移动0次只在1树下，单独考虑
}
cout<<max(f[w][1],f[w][2]);
return 0;

}
```


---

## 作者：1saunoya (赞：0)

>## [更好的阅读体验](https://www.cnblogs.com/qf-breeze/p/10574196.html)
> # [$problem$](https://www.luogu.org/problemnew/show/P2690)
>
看到这题 好几种方法
1.搜索 大概有一部分分
2.记忆化搜索 预计100pts
3.DP 预计100pts
4.滚动数组优化DP 预计100pts
---------------------------------------------------------------------------------------
>
1.不带记忆化的搜索妥妥的超时
2.记忆化搜索？ 三个维度？ 内存太大？ 时间还是$O(玄学)$的。
3.DP 能过 但是可以适当优化
4.滚动数组优化的DP
----------------------------------------------------------------------------------------

~~~
主要是DP
搜索太过于单调了。代码也比较好写。
可能还需要剪枝。那么DP？
~~~
>不难想。 每次有两种。 一种是走。另一种是在原地。
>即$dp[i][j]$表示奶牛在第$i$分钟内移动$j$次能够接到的最多苹果
>所以可以推出来动态转移方程
>$dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])$
>上面的方程表示上一步的状态可能是不动的 可能是动的。
>这是一种推的方式 还有一种推的方式是反过来的。
>那就不说那么多了 往下。
>同时如果$a[i]==j%2+1$即奶牛在这一分钟可以见到苹果 那么把$dp[i][j]++$
>因为初始位置是1 所以$j%2+1$是奶牛当前位置。 如果当前位置=苹果位置 那么就可以增加苹果量。
>不难得出这一段代码


~~~
    for(register int i=1;i<=T;i++){
        for(register int j=0;j<=T and j<=w;j++){
            if(!j) dp[i][j]=dp[i-1][j];
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
            if(a[i]==j%2+1) dp[i][j]++;
        }
    }
~~~


>所以求完之后 再根据题目要求 求出来最多的苹果数量。
>显然。$DP[T][w]$不一定是最大值。
>因为有时候不移动比移动要好。
>那么往下走。

得出代码

~~~
    LL ans=-0x7f;
    for(register int i=0;i<=w;i++) ans=max(ans,dp[T][i]);
    cout << ans << endl;
~~~


那么基本程序就完成了。


~~~
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL In() { LL res(0),f(1); register char c ;
    while(isspace(c=getchar())) ; c == '-'? f = -1 , c = getchar() : f = 1 ;
    while(res = (res << 1) + (res << 3) + (c & 15) , isdigit(c=getchar())) ; return res * f ;
}
int T;
int w;
int a[1<<10];
LL dp[1<<10][1<<5];
signed main () {
    T=In(); w=In();
    for(register int i=1;i<=T;i++) a[i]=In();
    for(register int i=1;i<=T;i++){
        for(register int j=0;j<=T and j<=w;j++){
            if(!j) dp[i][j]=dp[i-1][j];
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
            if(a[i]==j%2+1) dp[i][j]++;
        }
    }
    LL ans=-0x7f;
    for(register int i=0;i<=w;i++) ans=max(ans,dp[T][i]);
    cout << ans << endl;
    return 0;
}
~~~

># 如果对滚动数组有兴趣的 往下看。
>滚动数组，顾名思义。就是滚动的数组。反复利用同一个数组的同一个下标变量。
>因为有时候你只需要上一个状态而不是要许许多多的状态。
>所以如果需要上一个状态的话 可以进行$i&1$的操作（即i%2）
>这样子会节省内存。滚动数组很有用的


~~~
LL dp[1<<10][1<<5];//无滚动数组的数组大小
LL dp[2][1<<5];//滚动数组的数组大小
~~~


>因为线性$DP$以及区间$DP$都可以用这个来优化内存。
>比如说 刚才 那一段$DP$的过程 可以转化为 ↓


~~~
    for(register int i=1;i<=T;i++){
        for(register int j=0;j<=T and j<=w;j++){
            if(!j) dp[i&1][j]=dp[(i-1)&1][j];
            else dp[i&1][j]=max(dp[(i-1)&1][j],dp[(i-1)&1][j-1]);
            if(a[i]==j%2+1) dp[i&1][j]++;
        }
    }
~~~

>然后也求出来了。
>不过求最大值需要注意一点。
> # 不是$dp[T][0-w]$！！！！（敲黑板）


~~~
    LL ans=-0x7f;
    T&=1;
    for(register int i=0;i<=w;i++) ans=max(ans,dp[T][i]);
    cout << ans << endl;
~~~

>下面是滚动数组优化的代码。

~~~
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL In() { LL res(0),f(1); register char c ;
    while(isspace(c=getchar())) ; c == '-'? f = -1 , c = getchar() : f = 1 ;
    while(res = (res << 1) + (res << 3) + (c & 15) , isdigit(c=getchar())) ; return res * f ;
}
int T;
int w;
int a[1<<10];
LL dp[2][1<<5];
signed main () {
    T=In(); w=In();
    for(register int i=1;i<=T;i++) a[i]=In();
    for(register int i=1;i<=T;i++){
        for(register int j=0;j<=T and j<=w;j++){
            if(!j) dp[i&1][j]=dp[(i-1)&1][j];
            else dp[i&1][j]=max(dp[(i-1)&1][j],dp[(i-1)&1][j-1]);
            if(a[i]==j%2+1) dp[i&1][j]++;
        }
    }
    LL ans=-0x7f;
    T&=1;
    for(register int i=0;i<=w;i++) ans=max(ans,dp[T][i]);
    cout << ans << endl;
    return 0;
}

~~~

---

## 作者：cx51y (赞：0)

本题借鉴了别人的思想


http://www.bubuko.com/infodetail-1967674.html

f[i][j][kk]表示在i时刻走了j步在kk树下能获得的最大值，

当j==0时说明一直停在0号树下，因此f[i][0][0]=f[i-1][0][0];

当j>=1时枚举j，i阶段的f最大值只能从0,1号树得来，因此

f[i][j][kk]=max(f[i][j][kk],f[i][j-1][kk^1])+在kk号树下能否得到果实;

()内表示前者表示在kk树下不动，后者表示从另外一棵树上转来，

kk^1表示异或，即另一棵树；所以为【i-1】【j-1】；

最后能否得到果实，可以用一个a[i][kk]数组表示,如果i时刻kk果树下有

果实，则a[i][kk]=1;kk=0/1;


代码如下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int n,k;
int a[N][3],f[N][31][3];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        x--;
        a[i][x]=1;
    }
    for(int i=1;i<=n;i++)
    {
        f[i][0][0]=f[i-1][0][0]+a[i][0];//一直在0号树下
        for(int j=1;j<=k;j++)
        {
            f[i][j][0]=max(f[i-1][j][0],f[i-1][j-1][1])+a[i][0];
            f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][0])+a[i][1];
            //printf("%d %d %d %d\n",i,j,f[i][j][0],f[i][j][1]);
        }
    }
    int maxx=0;
    for(int i=0;i<=n;i++)
    maxx=max(maxx,max(f[n][k][0],f[n][k][1]));
    printf("%d\n",maxx);
    return 0;
}
```

---

