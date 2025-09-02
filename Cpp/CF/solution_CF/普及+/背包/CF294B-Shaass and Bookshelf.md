# Shaass and Bookshelf

## 题目描述

Shaass拥有n本书。他想为他的所有书制作一个书架，并想让书架的长宽尽量小。第i本书的厚度是t[i]，且这本书的纸张宽度是w[i]。书的厚度是1或2，所有书都有同样的高度（即书架的高是均匀的）。

Shaass以以下的方式摆放这些书籍。

1.他选择了一些书并竖直摆放它们。

2.他将剩余的书籍水平纺织于竖直的书上面。
水平放置的书的宽度和不能多于竖直放置的书的总厚度。图中描绘了书籍的样本排列。

帮助Shaass找到可以达到的书架长度最小值。

## 样例 #1

### 输入

```
5
1 12
1 3
2 15
2 5
2 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3
1 10
2 1
2 4
```

### 输出

```
3
```

# 题解

## 作者：星落云川 (赞：34)

先前的题解讲的有点跳，我作为初学者倒腾了一晚上才弄明白。我想以一个新手的视角来帮大家理一理解题的思路。  
这道题本质上是一道01背包题，但同时融合了贪心的思想。  
首先让我们明确三个前提：
- 书架的最大长度为所有书的厚度和，即全部书竖着放。
- 某本厚度为 $t$ 的书横着放后可以使全书厚度和减少 $t$。
- 书无非竖着放和横着放两种状态。
  
书架的长度只和下层竖着放的书的厚度和有关。因此，我们当然希望竖着放的书越少越好。  
现在假设我们有一个容量为 $j$ 的背包。任意选取若干本书，使其厚度和为 $j$，恰好塞满背包。之后，在我们往书架上放书的过程中，背包里的书一律横着放。显然，这样可以为我们的书架节约 $j$ 个长度。  
可以预见，往背包里塞书的方案可能不止一种。但不管怎么塞，这些书都只能为我们节省 $j$ 个长度。而题目中还要求上层横着放的书的宽度和不能大于下层竖着放的书的厚度和。贪心而言，我们当然希望背包里的书，即上层书的宽度和尽可能小。  
那么现在，问题转化成了去寻找减少 $j$ 个宽度时的最小花费 $w$。  
联系01背包，背包模版是在 $n$ 个物品中寻找满足背包容量条件下获得物品价值的最大值。在这里，**书的厚度等效于物品的重量，书的宽度等效于物品的价值，书架的长度等效于背包的容量**。只不过我们这次希望价值尽可能小。因此，得到状态转移方程：$dp[j]=min(dp[j],dp[j-v[i]]+w[i])$  
需要注意的是，$dp$ 完后的数组并不是最终答案。  
**$dp[j]$ 只表示在下层书籍厚度和不小于上层宽度和 $dp[j]$ 时可为你节省 $j$ 个长度。**  
所以最终答案还应该倒序查找。我们希望节省尽可能多的长度，但也要有足够多的下层厚度负担上层宽度。具体见代码：
```c
#include<stdio.h>
#include<stdlib.h>
int v[105]={}, w[105]={}; //厚度 宽度
int dp[205]={}; //背包的最大容量是所有书的厚度总和(n<=100 厚度<=2)
int min( int x, int y )
{
	return x>y ? y : x;
}
int main()
{
	int n, totLen=0;
	scanf("%d", &n);
	for( int i=1; i<=n; i++ ){
		scanf("%d %d", &v[i], &w[i]);
		totLen += v[i]; //总厚度
	}
	for( int i=1; i<=totLen; i++ )
		dp[i] = 10086; //初始化
	for( int i=1; i<=n; i++ ) //当前放第 i 本书
		for( int j=totLen; j>=v[i]; j-- ) // j是当前书架长度(等效于背包容量)
			dp[j] = min( dp[j], dp[ j-v[i] ]+w[i] ); //dp表示选厚度和为 j 的若干本书横着放的最小值
	for( int i=totLen; i>=0; i-- ) //倒序查找
		if( totLen-i >= dp[i] ){ //左式是下层书的厚度和 右式是上层书的宽度和
			printf("%d\n", totLen-i);
			break;
		}
	system("pause");
	return 0;
}
```



---

## 作者：Tyyyyyy (赞：15)

## 实质上是一道01背包问题。
分析题目：每本书对应有两种选择：竖着放、横着放。

正好对应了背包问题：放或不放。

对应背包问题的标准dp方程（P1049）：$dp[j]=max(dp[j],dp[j-v[i]]+v[i]);$

我们用一个结构体存储每本书的数据，很容易就可以推出这题的方程：
$dp[j]=min(dp[j],dp[j-a[i].v]+a[i].w);$

再联系到这题具体情况，总体积相当于所有书的$v$之和。

而自己翻译一下原文，需输出的是“我们能达到的垂直书籍的最小总厚度”，因此最后还需要对结果进行处理。

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[100001],sum[101],ans;
struct book
{
	int v,w;
}a[101]; 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].v,&a[i].w);
		sum[i]=sum[i-1]+a[i].v;//记录总量
	}
	for(int i=1;i<=sum[n];i++)dp[i]=1e5;//后面要用min，初始化
	for(int i=1;i<=n;i++)
	{
        	for(int j=sum[n];j>=a[i].v;j--)
		{                            
            		dp[j]=min(dp[j],dp[j-a[i].v]+a[i].w);
        	}
    	}
    	for(int i=sum[n];i>=0;i--)
    	{
    		if(sum[n]-i>=dp[i])
    		{
    			ans=sum[n]-i;break;//最后进行处理
		}
    	}
    	printf("%d",ans);
	return 0;
}
```

---

## 作者：linyinuo2008 (赞：12)

[原题链接](https://www.luogu.com.cn/problem/CF294B)

刚做完一道背包题，来写一篇题解吧。

# 1、题目大意
给你 $n$ 本书和每本书的厚度与宽度，让你求一求书架最少要有多长。每本书有两种放的方法，立着插在那里与横着放在书的上面（如图）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF294B/294454fb546e216dead52db8f9eb3345eef061e2.png)

请注意：每本书的厚度一定是 $1$ 或 $2$并且最多有 $100$ 本书。

# 2、算法理解

由于要求书架的最小长度，~~又因为算法标签上写着“背包”~~，我们可以用 [$01$ 背包](https://www.baidu.com/s?wd=01%E8%83%8C%E5%8C%85)来做（[这里](https://www.luogu.com.cn/problem/P1049)有一个减弱版），其中把每本书立着放和倒着放上面分别对应着选和不选。

显然，书架的最大长度不可能超过所有书的厚度之和（所有书都立着放），那我们就开一个变量 $sum$ 记录所有书的厚度和，把 $sum$ 当成背包的最大容量，把每一本书当成物品。这样，我们来做一次求最小的 $01$ 背包。这个 $01$ 背包的限制是上层放书的总宽度和不能大于下层书的厚度和（不然就掉下来了）。

这里有一个小方法来判断开一维还是开两维：

**1. 若物品有不选这个选项，一维好写。**

**2. 若每个物品都得被选中，但有多种选的方式，二维比一维好写。**

设 $f_j$ 表示当书架总长度为 $j$ 时上层放书的总宽度最小值，于是状态转移方程为：

$f_j=$ $\min (f_j,f_{j-v_i}+w_i)$ 

这里的 $v_i$ 和 $w_i$ 分别是书的厚度和宽度。

最后别忘了倒着扫一遍来判断答案，如果底下放书的总厚度比上面总宽度大，直接把答案输出就可以了。

# 3、代码

代码中有注释。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int NR=105;
const int MR=205; //因为书的厚度可能是2，因此要开两倍
int f[MR],v[NR],w[NR];
int n,sum;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>v[i]>>w[i];
		sum+=v[i];//要记录书的总厚度
	}
	memset(f,999999,sizeof(f));//初始把f设成INF
	f[0]=0;
	for(int i=1;i<=n;i++)//第一层枚举物品
		for(int j=sum;j>=v[i];j--)//第二层倒序枚举容量
			f[j]=min(f[j],f[j-v[i]]+w[i]);
	for(int i=sum;i>=0;i--)//从大到小扫一遍
		if(sum-i>=f[i])
		{
			cout<<sum-i;//可以就输出
			return 0;
		}
	return 0; 
}
```

**若有错误，欢迎指出！**

---

## 作者：littlebug (赞：8)

为什么题解区都是这么难理解的 dp 做法呀……

但是我不想动脑子。

---

## Solution 1

显然我们在设状态的时候可以添加限制，设 $f_{i,j}$ 为前 $i$ **都必须选**，下层厚度之和为 $j$，这时上层宽度之和的最小值。转移考虑一本书放在上层还是下层即可，有式子：

$$
f_{i,j} = \min
\begin{cases}
f_{i-1,j} + w_i \\
f_{i-1,j-t_i}
\end{cases}
$$

答案就是最小满足 $j \ge f_j$ 的 $j$。

时间复杂度 $O(n^2)$。

## Solution 2

还有一个更无脑的做法，甚至复杂度更优秀。

发现 $t_i$ 的取值只有 $1,2$，所以当下层厚度之和确定的时候，是容易计算上层最小宽度的。具体地，按照 $t_i$ 的取值分开，然后分别排个序，贪心把宽度大的放到下面，双指针维护即可。

于是就可以二分答案了，复杂度只有 $O(n \log n)$。

---

华风夏韵，洛水天依！

---

## 作者：Cry_For_theMoon (赞：6)

&emsp;&emsp;考前发一波题解祈祷rp++

&emsp;&emsp;~~WA最后一个点的痛苦~~

&emsp;&emsp;考虑这题的厚度最大值其实只有 400，不如从小到大枚举：若当前厚度为 $j$，选出一些书的厚度之和为 $j$，同时剩下的数的宽度之和 $<=j$。这个子问题显然背包，因为我们要让选出的那些书宽度之和最大，这样剩下的数宽度之和就尽可能小了。把厚度看作重量，宽度看作价值，问题变成了一个恰好为 $j$ 的0/1背包，因为是恰好，所以开始 $f(1..200)$ 都置为 -INF。因为会出现没有恰好选够的情况，要让他们不合法，求最大值的话置为最小值（和求最小值置为INF一个道理），这种小细节应该做过一点变形题的都懂。~~不然你会收获#27 WA的好成绩~~

&emsp;&emsp;$sum$ 代表宽度之和，最后如果 $sum-f(j)<=j$ 就输出（如果 $f(j)$ INF，显然左边的值会极大）

&emsp;&emsp;这个思路比前几楼的题解更容易看懂些吧

&emsp;&emsp;CSP-S rp++

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=110,MAXM=210;
int f[MAXM];
int n,t[MAXN],w[MAXN],sum;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=200;i++){
		f[i] = -1e5;
	}
	for(int i=1;i<=n;i++){
		scanf("%d%d",&t[i],&w[i]);
		for(int j=200;j>=t[i];j--){
			f[j] = max(f[j],f[j-t[i]]+w[i]);
		}
		sum+=w[i];
	}
	for(int j=1;j<=200;j++){
		if(sum-f[j] <= j){
			printf("%d",j);return 0;
		}
	}
	return 0;
}
```


---

## 作者：_Felix (赞：5)

莫名a了，发一波题解

```
#include<bits/stdc++.h>//万能头文件
using namespace std;


int dp[105];//数组不必开大，哈哈哈
struct pos
{
	int t;
	int w;
}a[105];//哦，我可爱的结构体
 
 
int main()
{
	int n,sum=0;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i].t>>a[i].w;
		sum+=a[i].t;//算和
	}//读入
	for(int i=1;i<=sum;i++)
		dp[i]=1000000009;//初始化
		
		
	for(int i=0;i<n;i++)
		for(int j=sum;j>=a[i].t;j--)
			dp[j]=min(dp[j],dp[j-a[i].t]+a[i].w);//01背包
			
			
	int k;
	for(int i=sum;i>=0;i--)
	{
		if(sum-i>=dp[i])
		{
			k=sum-i;
			break;
		}
	}//题目说“The sum of the widths of the horizontal books must be no more than the total thickness of the vertical books.”
	
	
	cout<<k<<endl;//输出啦，啦啦啦
	return 0;
 } 
 ```

---

## 作者：lhjy666 (赞：3)

### 其实就是个01背包
### 每本书只有2种情况：横着和竖着。所以01背包走起
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100000],b[100000],f[1005];
int main()
{
	ll n,z=0,t=0;
	scanf("%lld",&n);
	for (ll i=0;i<n;i++)
	{
		scanf("%lld%lld",&a[i],&b[i]);
		z=z+a[i];
	}
	for (ll i=1;i<=z;i++)
	{
		f[i]=201;//初始化
	}
	f[0]=0;//其实也可以不写全局变量自动清0
	for (ll i=0;i<n;i++)
	{
		for (ll j=z;j>=a[i];j--)
		{
			f[j]=min(f[j],f[j-a[i]]+b[i]);//此处与普通的背包不同此处要取小
		}
	}
	for (ll i=z;i>=0;i--)//从z开始保证最大
	{
		if(z-i>=f[i])
		{
			t=i;
			break;
		}
	}
	printf("%lld",z-t);
	return 0;
}
```

---

## 作者：y0y68 (赞：2)

题目难度有点虚高，蒟蒻就来发一篇题解吧。
##### 上题面
```cpp
Shaass拥有n本书。他想为他的所有书制作一个书架，并想
让书架的长宽尽量小。第i本书的厚度是t[i]，且这本书的
纸张宽度是w[i]。书的厚度是1或2，所有书都有同样的高
度（即书架的高是均匀的）。

Shaass以以下的方式摆放这些书籍。

1.他选择了一些书并竖直摆放它们。

2.他将剩余的书籍水平纺织于竖直的书上面。 水平放置的
书的宽度和不能多于竖直放置的书的总厚度。图中描绘了
书籍的样本排列。

帮助Shaass找到可以达到的书架长度最小值。
```

##### 读题可知：
- 只是一道dp题
- 有点像01背包（每本书只有横放和竖放两种状态）
接下来就是~~要把这道题套到01背包的板子上~~认真思考这道题的解法
- 分析可得横放肯定节省长度，所以要尽量横放
- 背包的容量是书架长度
- 背包的最大容量肯定是每本书都竖放
- **由此确定$dp_i$表示放第i本书时理想情况的最优解**
- 那么转移方程就为$dp_j$ = $ dp_{j-t[i]}$ + $w_i$
- 注意数组大小

# Code
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,all=0,ans=0;
int w[1005],t[1005],dp[1005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&t[i],&w[i]);
		all+=t[i];
		//厚度, 宽度 
	}
	memset(dp,0x3f,sizeof dp);
	//初始化 
	dp[0]=0;
	//没放书的状态长度为0
	for(int i=1;i<=n;i++)
		for(int j=all;j>=t[i];j--)
			dp[j]=min(dp[j-t[i]]+w[i],dp[j]);
	//最后dp出的结果是i本书的最优解（理想情况的最小长度） 
	for(int i=all;i>=0;i--){
		if(all-i>=dp[i]){
			ans=all-i;
			//一一配对，看什么时候满足理想情况 
			break;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：xyf007 (赞：2)

# 01背包
## 用f[i]表示将第i本书放入最多节省多少
```
#include<bits/stdc++.h>
using namespace std;
int n,f[100001],yy,w[100001],t[100001];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	  {
	  	scanf("%d%d",&t[i],&w[i]);
	  	yy+=t[i];
	  }
	for(int i=1;i<=yy;i++)
	  f[i]=1<<30;
	for(int i=0;i<n;i++)
	  for(int j=yy;j>=t[i];j--)
	    f[j]=min(f[j],f[j-t[i]]+w[i]);
	for(int i=yy;i>=0;i--)
	  if(yy-i>=f[i])
	    {
	      printf("%d",yy-i);
	      return 0;
		}
	return 0;
}
```

---

## 作者：Skies (赞：1)

- ### 思路：01背包

我们用 $dp(i)$ 表示用厚度为 $i$ 的书能够占据的最大宽度。

那么摆在上面的宽度就是所有书的宽度之和 $sum-dp(i)$ 即可。



我们只需要判定i是否大于 $ sum-dp(i) $ 即可。

- ### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
struct node{
	int h,k;//h==1 / 2
}a[N];
int hou,chang,n,sum;
int dp[N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].h,&a[i].k);
		hou+=a[i].h,sum+=a[i].k;//厚度之和和宽度之和 
	}
	memset(dp,-60,sizeof(dp));//这一行必须要，不然有些非法状态就会被转移
	dp[0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=hou;j>=a[i].h;j--)
		{
			dp[j]=max(dp[j],dp[j-a[i].h]+a[i].k);
		}
	}
	for(int i=1;i<=hou;i++)
	{
		if(i>=sum-dp[i])
		{
			cout<<i;return 0;
		}
	}
	
	return 0;
}
```



---

## 作者：Lucre (赞：1)

### 解题思路
1.定义状态量:   

$dp[i][j]$,表示竖直放置的书厚度和为$(8-j)$时,也就是抽出j厚度和的书横放在上面,其余均竖直放置,考虑前$i$本书来放在上层所得到的上层书最小的长度和;成功转换成典型的01背包问题;    

2.状态转移:    
  
依次考虑每本书,有两种情况:   
  
  
第一种,这本书的厚度超过$j$,**$dp[i][j] = dp[i - 1][j]$**;  
  
  
第二种,这本书的厚度小于等于$j$,**$dp[i][j] = min(dp[i - 1][j] , dp[i - 1][j - t[i]]+w[i])$**; 
  
  
3.边界条件:$dp[i][0] = 0;dp[0][j] = max$ ; 

4.我们只需要找到:    

抽出j厚度和的书横放在上面所得到的上层书最小的长度和$dp[n][j]\leq$竖直放置的书厚度和$(8-j)$.遍历找出最小满足条件的竖直放置的书厚度和$(8-j)$即可; 
### 样例
对于第一个试例,进行测试  

| $dp[i][j]$ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- | :----------- |
| 1 | 12 | max | max | max | max | max | max | max |
| 2 | 3 | 15 | max | max | max | max | max | max |
| 3 | 3 | 15 | 18 | 30 | max | max | max | max |
| 4 | 3 | 5 | 8 | 20 | 23 | 35 | max | max |
| 5 | 3 | 1 | 4 | 6 | 9 | 21 | 24 | 36 |
$dp[5][3]<5$ ,输出5;
```
#include<iostream>
#include<algorithm>
using namespace std;
int n;//书本数
int t[105],w[105];//厚度,宽度
int dp[105][205];//dp[i][j]考虑前i本书,抽出j厚度和的书放在上层
int all[105];//记录前i本书的厚度和
int main()
{
    cin>>n;
    int sum=0;//所有书的厚度和
    for(int i=1;i <= n;i++)
    {
        cin>>t[i]>>w[i];
        sum += t[i];
        all[i] = sum;
    }
    for(int i = 0;i < 105;i++)
    dp[i][0] = 0;
    for(int j = 1;j <= sum;j++)//拿出j厚度和的书放在上层
    {
        int i = 0;
        while(all[i] < j)
        {
            dp[i][j] =  1000005;//厚度和不够时,置为最大值
            i++;
        }
        for(;i <= n;i ++)
        {
            if(j < t[i])//这本书厚度超过允许的厚度和
            dp[i][j] = dp[i-1][j];
            else//没有超过 
            dp[i][j] = min(dp[i-1][j] , dp[i-1][j-t[i]]+w[i]);
        }
    }
    int i = sum;
    while(dp[n][i] > sum - i)//找到符合上层长度小于等于下层长度的条件
    {
        i--;
    }
    cout<<sum - i;
}
```

---

## 作者：2333tech (赞：1)

## CF294B 的题解
见题目，**题目求“厚度”的最小值**，并且书籍可以横放与竖放。  
思考~~片刻~~一段时间后，可以发现将书籍横放可以减小总厚度，但是横放书籍的宽度不能大于总厚度。  
所以，为了让总厚度最小，**要让尽可能多的书籍放在上面，** 同时保证上面的总宽度小于下面的总厚度。  
于是，为了让上面的数尽可能多，我们得出了让上面的书宽度之和**最小**的转移方程：  
$$f[j] = min(f[j],f[j-v[i]] + w[i])$$  
**其中 $j$ 从所有书籍厚度之和递减循环到当前书籍厚度 $v[i]$ , 并且 $w[i]$ 为当前书籍的宽度。**  
最后，从厚度为0向厚度之和遍历一遍，得到符合条件的最小的厚度。  
```cpp
#include <bits/stdc++.h>
using namespace std;
int v[110],w[110];
int f[500];
int n;
int sum;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n;i++) {
        scanf("%d%d", &v[i], &w[i]);
        sum += v[i];	//求出所有书籍厚度之和 sum
    }
    memset(f, 0x7f, sizeof f);	//要求最小值，初始化为最大值
    f[0] = 0; //!!!
    for (int i = 1; i <= n;i++) {
        for (int j = sum; j >= v[i];j--) {
            f[j] = min(f[j], f[j - v[i]] + w[i]);
        }
    }
    for (int i = sum; i >= 0;i--) {	//此处 i 为上面放书所节省的厚度，所以 sum-i 题目要求的最小厚度
        if (sum - i >= f[i]) {	//判断是否符合条件
            printf("%d", sum - i);	//输出 i 最大即 sum-i 最小值
            return 0;
        }
    }
    return 0;
}
```


---

## 作者：black_trees (赞：1)

### [P1049](https://www.luogu.com.cn/problem/P1049)的翻版

-----

很明显的，这是一道 $01$背包的模板题，其实和P1049没有太大差别。

看了看其它题解，说的都含含糊糊的，只说了套板子，还常常出现不明不白的东西（都不知道哪里来的），对萌新就真的非常不友好。

所以我要给刚学 $01$ 背包的萌新同学更好的体验。

所以我好好地推一遍方程。

------

为啥是 $01$ 背包？ $01$ 背包该怎么推方程？

既然我说这是 $01$ 背包。

那么先从最基本的 $01$ 背包推起。
 
普通 $01$ 背包：

>有$N$件物品和一个容量为$V$的背包。第$i$件物品所占空间是$c[i]$，价值是$w[i]$。将哪些物品装入背包可使价值总和最大？

既然我们要搞出方程，就要想想状态从哪儿来。

这个题只有不选和选两个决策。

先设计状态。

设 $f[i][j]$ 表示 考虑前 $i$ 个物品，用 $j$ 的空间所得的最大价值。

+ 选：我们在背包里减去当前物体的体积，加上它的价值 $c[i]$（这里要保证空间足够，加一个$if$来判断）,也就是 $f[i][j]=\max(f[i-1][j-v[i]]+c[i],f[i-1][j])$ （这里 $i-1$ 很明显，是从上一个状态继承的）。

+ 不选 也就是要直接继承状态。 那么 $f[i][j]=f[i-1][j]$。

可得到以下代码：

```cpp
for(register int i=1;i<=n;++i){
		for(register int j=0;j<=m;++j){
			f[i][j]=f[i-1][j];
			if(j-v[i]>=0){
				f[i][j]=max(f[i][j],f[i-1][j-v[i]]+c[i]);
			}
		}
	}
```


当然，这里可以用滚动数组优化。

因为版面原因在这里不细说，需要的同学可以看看：[这篇博客](https://www.luogu.com.cn/blog/hwk/guan-yu-gun-dong-shuo-zu-di-bi-ji)（直接跳下面的滚动数组部分即可，他的细节和要点讲的很清楚）。


滚动数组代码：

```cpp
for(register int i=1;i<=n;++i){
		for(register int j=m;j>=v[i];--j){//倒序循环防止出错（这里必须倒序）
			f[j]=max(f[j],f[j-v[i]]+c[i]);
		}
	}
```

好的，你现在应该可以搞懂 $01$背包了。

回过头来看这一道题：

我们不难看出：这题的背包容量是所有书的厚度之和。第 $i$ 本书的厚度是 $v[i]$ ,宽度是 $c[i]$。

那么，我们就可以开始愉快的套板子了！

只是要注意，这里求的是最后书架的最小长度，所以方程里的 $max$ 要改成 $min$ ，最后要输出 $m-res$ 。

代码如下：
```cpp
unsigned long long f[1004];//这里稍微开大点，我就在这里卡了好久 
unsigned long long v[1000004];// 同上 
unsigned long long c[1000004];//同上 
unsigned long long n;
unsigned long long m=0;
unsigned long long res=-1;

int main(){
	cin>>n;
	for(register unsigned long long i=0;i<n;++i){
		cin>>v[i]>>c[i];
		m+=v[i];
	}
	memset(f,203,sizeof(f));
	f[0]=0;
	for(register unsigned long long i=0;i<n;++i){
		for(register unsigned long long j=m;j>=v[i];--j){
			f[j]=min(f[j],f[j-v[i]]+c[i]);
		}
	}
	for(register unsigned long long i=m;i>=0;--i){
		if(m-i>=f[i]){//这里倒序循环，找到就是最优的，所以直接break；
			res=i;
			break;
		}
	}
	printf("%llu",m-res);
	return 0;
}

```

[我的提交记录](https://www.luogu.com.cn/record/list?pid=CF294B&user=304550)（因为各种细节不注意调了很久，别学我）。

------

如果说这篇题解有帮到你，那我就很开心啦。

---

## 作者：lihanyang (赞：1)

一个典型的01背包问题，体积是厚度总和
```cpp
#include<bits/stdc++.h>
```
//万能头文件~~（虽然不包括ctime和windows.h）~~
```cpp
using namespace std;
long long f[1005];
long long w[100000],v[100000];
int main()
{
    ios::sync_with_stdio(false);//流加速，比scanf快（感觉）
	long long t;
	long long sum=0;
	cin>>t;
	for(long long i=0;i<t;i++)
	{
		cin>>v[i]>>w[i];
		sum+=v[i];	//算总和
	}
	for(long long i=1;i<=sum;i++)
	{
		f[i]=10000;//其实201也可以，只是装逼开大一些
	 } 
	 f[0]=0;
	for(long long i=0;i<t;i++)
	{
		for(long long j=sum;j>=v[i];j--)
		{
			f[j]= min(f[j],f[j-v[i]]+w[i]);
		}
	}
	long long ss;
	for(long long i=sum;i>=0;i--)
	{
		if(sum-i>=f[i])
		{
			ss=i;
			break;
		}
	}
	cout<<sum-ss<<endl;//输出
	return 0;
}
```


---

