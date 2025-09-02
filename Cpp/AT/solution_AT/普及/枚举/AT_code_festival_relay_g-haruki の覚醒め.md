# haruki の覚醒め

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-relay/tasks/code_festival_relay_g

haruki さんは朝に弱いことで有名です。haruki さんの家には目覚まし時計が $ n $ 個あり、$ i $ 番目の目覚まし時計の音量は $ a_i $ です。

   
haruki さんは鳴っている目覚まし時計の音量の合計が $ m $ 以上にならない限り、目を覚ますことはありません。しかしながら、必要以上に目覚まし時計をセットすると、うるさくて近所迷惑になってしまいます。

   
そこで、合計の音量が $ m $ 以上でかつ最小となるように目覚まし時計を選んだとき、その合計の音量を求めてください。

## 样例 #1

### 输入

```
3 30
25
10
23```

### 输出

```
33```

## 样例 #2

### 输入

```
4 101
10
20
30
40```

### 输出

```
-1```

# 题解

## 作者：MattL (赞：5)

[洛谷链接](https://www.luogu.com.cn/problem/AT1071) & [原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/1071)

一道背包~~水题~~

---

**题意：**

给你 $n$ 和 $m$ 和一串数，要求输出一个最优方案，这个方案中选取的数加起来要最小但又 $\geq m$

---

**解题：**

这题是一题升级版的背包。

我们可以转化一下题目

求出背包容量为 $\sum_{i=1}^n a_i-m$ 可以取到的最大的和

最后用 $\sum_{i=1}^n a_i$ 减去这个数就行了

---

**动规核心：**

首先，背包基础模板的动态转移方程：
$$f[i][o]=\max(or \min)(f[i][o],f[i-1][o-w[i]]+v[i]$$
其中， $f[i][o]$ 表示现在取到第 $i$ 个物品、背包还有 $o$ 的容量， $w[i]$ 表示第 $i$ 个物品的重量， $v[i]$ 表示第 $i$ 个物品的价值。

---

对于这题，我们用 $a[i]$ 表示第 $i$ 个数，这个 $a[i]$ 为重量和价值。所以，动态转移方程为：
$$f[i][o]=\max(f[i][o],f[i-1][o-a[i]]+a[i]$$
$f[i][o]$ 的含义同上。

---

然后，我们发现 $i$ 在里面都是 $i$ 变为 $i-1$ ，所以我们可以把 $i$ 这维压掉。动态转移方程变为：
$$f[o]=\max(f[o],f[o-a[i]]+a[i]$$
$f[o]$ 表示现在背包还有 $o$ 的容量。


---

**注意要点：**

1. 岛国题（ AT ） 一定要换行
2. $\sum_{i=1}^n a_i$ 要是小于 $m$ ，输出-1
3. 动态规划时，第二层循环要逆序枚举，且最小为 $a[i]$ 
3. 最后是 $\sum_{i=1}^n a_i$ 减去这个数，不是背包容量的 $\sum_{i=1}^n a_i-m$ 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[55],sum,f[1111111];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];//求和
	}
	sum-=m;
	if(sum<0)
	{
		cout<<-1<<endl;//怎样都不能凑够m
		return 0;
	}
	for(int i=1;i<=n;i++)
		for(int o=sum;o>=a[i];o--)//逆序枚举背包容量最小为a[i]，否则会溢出
			f[o]=max(f[o],f[o-a[i]]+a[i]);//别错了，是求最大值，我在这卡了一段时间……
	cout<<sum+m-f[sum]<<endl;//别忘了加m
	
	return 0;
}
```
备注：由于个人习惯，没有用 $j$ 而是用 $o$ 。

---

## 作者：zjyqwq (赞：4)

### AT1071 haruki の覚醒め题解
Pascal题解。


------------
#### 解题思路
用dp做，这题就是一个01背包哇！！！

只是dp公式要改一改。
```pascal
f[j]:=f[j]or f[j-c[i]];
```
将01背包里的东西改成这一块。

解析：$i$ 是枚举当前物品的体重，现在每个物品价值都是 $1$，那就只需用布尔类型就好了，只要 $j$ 这个数不用 $c[i]$ 和 $j$ 这个数用 $c[i]$ 二者只要有一个满足条件就可以了。



------------
#### 注意
- AT输出一定要换行。
------------
#### 代码
```pascal
var
i,j,m,n,sum:longint;
c,w:array[0..1000000] of longint;
f:array[0..1000000] of boolean;//由于价值只有0和1，用布尔类型即可。
begin
  readln(n,m);
  for i:=1 to n do readln(c[i]);//输入
  for i:=1 to n do sum:=sum+c[i];//计算所有物品可以达到的最大体积。
  if sum<m then begin writeln(-1);exit;end;//如果全部加起来都达不到，就不用再dp了，直接输出-1。
  f[0]:=true;
  for i:=1 to n do
    for j:=sum downto c[i] do
      f[j]:=f[j]or f[j-c[i]];//开始dp。
  for i:=m to sum do 
   if f[i]then 
    begin
     writeln(i);
     halt;
    end;//枚举可能的范围，只要一找到就输出。
 writeln(-1);//找了个X，输出-1。
end.
```
结束了！！！

---

## 作者：simonG (赞：3)

### 前言
一道经典的动态规划题。  
题意：在n个数里取任意几个数，让它们的和超过m，求最小和。
### 详解
>* 先求出所有数的和s，与m比较，如果$m>s$，那么就一定不可能满足条件，即输出-1。
>* 如果$m\leq s$，那么就转化成01背包问题，即在$s-m$的空间（背包）内，找出几个数（物品），让它们的和（价值）尽量大，就转化成剩下的和尽量小，又不会小于m。
>* 01背包问题：枚举物品的下标，再倒序枚举容量，然后用状态转移方程
$$f_j=\max(f_{j-a_i}+a_i,f_j)$$
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101],f[10001],n,m,s;
//s,表示数字的和
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]),s+=a[i];
	if(s>=m)   //否则就不可能和超过m
		{
			//01背包
			for(int i=1; i<=n; i++)
				for(int j=s-m; j>=a[i]; j--)
					//s-m表示剩下数字空间
					f[j]=max(f[j],f[j-a[i]]+a[i]);
			printf("%d\n",s-f[s-m]);
		}
	else
		puts("-1");
	return 0;

}
```


### 后记
正难则反推


---

## 作者：satCHel (赞：2)

这是我的第一篇题解。

感觉我的方法可能比较好理解吧，就是01背包，所以也更好敲。

首先我们先求出前n个a[i]的和，就是把所有物品都加入背包的最大价值sum。然后把s=sum-m作为01背包的最大容量进行01背包。求出f[s],就是在[m,sum]这个区间中，能取到的最大价值。之后用我们之前求的把所有物品都放入背包中的sum减去这个f[s]就能得出，最小的超过m的值。要是达不到m值，就是物品都入背包也达不到m值，就是s
 <0，就输出-1。

以下c++代码:

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int a[100],f[600000];
int main()
{
	int i,j,n,m,s,sum=0;
	memset(f,0,sizeof(f));
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
	   scanf("%d",&a[i]);
	   sum+=a[i];
    }
    s=sum-m;
	if(s>=0)
	{//开始了，01背包。
    for(i=1;i<=n;i++)
       for(j=s;j>=a[i];j--)
          if(f[j]<f[j-a[i]]+a[i])
             f[j]=f[j-a[i]]+a[i];
    
       printf("%d",sum-f[s]);}
    else
       printf("-1");
       printf("\n");
    return 0;
	
}
```

### 以及很重要很重要的就是输出末尾一定要有“换行符”，要不就全WA了。（我也不知道为什么，可能是日本人有毒吧。）

 以上，祝好！

---

## 作者：cjZYZtcl (赞：1)

## AT1071 haruki の覚醒め 题解
### 题目大意
给出 $n$ 个数，选出其中若干个数，使得这些数的和大于等于 $m$ 且最小，如果不可能满足要求则输出 $-1$。

### 思路
我们先考虑输出 $-1$ 的情况。

如果这 $n$ 个数加起来的和都小于 $m$，那么很显然是不可能满足要求的，而和大于等于 $m$ 时很显然是可以满足要求的。

然后我们考虑满足要求的情况。

我们可以用01背包来解决这道题。

这题的背包和模板有些不同，背包容量数组中，存的不是当前容量可获得的最大价值，而是存不存在这种容量。放到题目中，就是存不存在一种选数方法使得选出来的数的和等于当前下标。

最后的时候从 $m$ 开始从小到大枚举容量，如果当前数组元素为真，就输出这个数。

该怎么实现呢？

我们假设 $f$ 数组表示当前容量是否能达到。

首先，$f[0]$ 很显然为真（全都不选就达到了），其他点先都赋值为假。

然后，用普通背包的方法做，转移方程如下：
$$f[j]=f[j]\ \lor\ f[j-a[i]]$$
（$j$ 为容量，$a[i]$ 为第 $i$ 个数）

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool f[500005];
int a[55];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), m = read(), sum = 0;
	for(int i = 1; i <= n; i++){
		a[i] = read();
		sum += a[i];
	}
	if(sum < m){
		write(-1);
		putchar('\n');
		return 0;
	}
	memset(f, false, sizeof(f));
	f[0] = true;
	for(int i = 1; i <= n; i++){
		for(int j = sum; j >= a[i]; j--){
			f[j] = f[j] || f[j - a[i]];
		}
	}
	for(int i = m; i <= sum; i++){
		if(f[i]){
			write(i);
			putchar('\n');
			return 0;
		}
	}
}
```


---

## 作者：RioBlu (赞：1)

一个动态规划的水题，加一丢丢小优化即可

本题题意：
```
输入n,m 和 n个数字

问从n个数字中任意选几个数字加起来

请输出最小且大于等于m的

若没有请输出-1
```

```
#include<bits/stdc++.h>
using namespace std;
long long a,b,now,ans=9999999999;//ans的初值
bool c[30000]={1};
int main()
{
	cin>>a>>b;
	for(int s=0;s<a;s++)
	{
		cin>>now;
		for(int v=b;v>=0;v--)
		{
			if(c[v]==1)
			{
				c[v+now]=1;
				if(v+now>=b)
				{
					ans=min(ans,v+now);
				}
			}
		}
	}
	if(ans!=9999999999)cout<<ans<<endl;else cout<<-1<<endl;
}
```

---

## 作者：Yang818 (赞：1)

## problem

输入n,m 和 n个数字

问从n个数字中任意选几个数字**加起来**

请输出**最小**且**大于等于**m的

若没有请输出-1

## solution

由于本题的数据范围较小，而且可以进行剪枝，考虑动态规划中的状态压缩和01背包

但是对于状压来说，这个数据范围有些大，本蒟蒻就想到了01背包

01背包大家肯定都会写，这边讲讲怎么剪枝：

首先，只要当前的总和大于了 $m$ 就可以判断是否还要执行下去了。因为数据范围都是正整数，所以只会越加越大，还有一个就是要判断访问的下标是否越位，需要注意的就是两个剪枝的位置。需要在判断越位之前先判断总和，因为如果最后一位加上去后达到了要求，你却因为越位而把它剪掉了，就会导致答案不正确。

## code

代码还需要吗？
    
25行直接搞定。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans=1e9,g_a[10010],g_n,g_m;
void dfs(int k,int sum){
	if(sum>=g_m){
		ans=min(ans,sum);
		return;
	}
	if(k>g_n)
		return;
	dfs(k+1,sum+g_a[k]);
	dfs(k+1,sum);
	return;	
}
int main(){
	cin>>g_n>>g_m;
	for(int i=1;i<=g_n;i++)
		cin>>g_a[i];
	dfs(1,0);
	if(ans==1000000000)
		cout<<-1<<endl;
	else 
		cout<<ans<<endl;
	return 0;
}
```
望通过，谢谢


---

## 作者：Chinshyo (赞：1)

看完题面就知道是背包问题了。
# 题目分析
**题目中$ n $的数据不是特别的强，个人认为用递归的背包是更易懂的。**

求选数中大过  $ m $ 的最小的和。然而，我们就可以吧这里的和作为是背包里的物品体积。我们拿题目中样例举例：
![过程](https://cdn.luogu.com.cn/upload/image_hosting/t2ulhszr.png)
包的物品体积不得小于$ 30 $，更新时的条件比起传统的递归就要多增加这么一行语句：

```cpp
if(sum>=m)
```
这行代码就是控制背包体积不会小于 $ m $ 。
# 递归过程
我们在选数过程中用$ dep $来选举数列中的元素。分为两种情况：一种是取当前的，一种是不取当前的，所以就可以用这种代码表示：

```cpp
dfs(dep+1,sum);
if(sum+a[dep]<=ans)
	dfs(dep+1,sum+a[dep]);
```
当中的剪枝条件纯粹是为了保证不$ T $的。~~其实我自己也担心递归的效率~~由于这道题没有直白的限制容积，所以不需要在这里考虑。
整个递归过程的代码：
```cpp
void dfs(int dep,int sum)
{
	if(dep>n)
	{
		if(sum>=m)
		{
			if(sum<ans) ans=sum;
		}
	}
	else
	{
		dfs(dep+1,sum);
		if(sum+a[dep]<=ans)
			dfs(dep+1,sum+a[dep]);
	}
}
```
# 特殊情况
这道题有一种特殊情况，原题中：请输出最小且大于等于$ m $的，**若没有请输出$ -1 $**。所以在最后输出时要加一句：
```cpp
if(ans!=INT_MAX)
	cout<<ans<<endl;
else cout<<-1<<endl;
```
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55],n,m,ans=INT_MAX;
void dfs(int dep,int sum)
{
	if(dep>n)
	{
		if(sum>=m)
		{
			if(sum<ans) ans=sum;
		}
	}
	else
	{
		dfs(dep+1,sum);
		if(sum+a[dep]<=ans)
			dfs(dep+1,sum+a[dep]);
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	dfs(1,0);
	if(ans!=INT_MAX)
		cout<<ans<<endl;
	else cout<<-1<<endl;
	return 0;
}
```


---

## 作者：Happy_Dream (赞：1)

这道题就是一个基本的背包，可是好多人上来就以为是模拟（包括我）
这是我最开始WA的很惨的模拟代码（惨不忍睹）我就不过多解释了。
***
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n,m;
    int min1=1e9+7;设计最小值
    cin>>n>>m;
    int a[n+5];
    for(int i=1;i<=n;i++)
    cin>>a[i];//输入
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            min1=min(min1,a[i]+a[j]-m);//每次取最小的（和min1自己比较）
        }
    }
    if(min1<0)
    cout<<"-1"<<endl;//判断（不行是-1）
    else
    cout<<min1+m<<endl;//正常输出
    return 0;//结束
 }
 ```
 ***
 后来研究了好久才发现只要用一个01背包就行了（a[i]既是所耗费的数，也是所得到的数）自从公式找到后就容易多了  f[j]=max(f[j],f[j-a[i]]+a[i]);之后再把这个公式放到程序里就好了（也没有绿题的难度）。不过还是有几个点要注意的
 
 1，里层循环不要写反（否则就变成完全背包了）
 
 2，注意输出是换行。
 
 3，一定要先把F数组清为零（否则会出现很奇怪的结果）（我最开始就怎么错了）
 
 ***
 ```cpp
 #include <iostream>
#include <cstring> //memset的头文件
#define H 1000005//装装逼
using namespace std;
int main()
{
    int n,m,sum=0;//sum一定要清零
    cin>>n>>m;//输入N和M
    int a[H],f[H];//一个用来输入和计算，一个用来储存答案
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];//输入数字
        sum+=a[i];//加一下
     } 
    int sum1=sum;
    sum1-=m;//定义一个新变量
    memset(f,0,sizeof(f));//清空数组
    if(sum1<0)//判断能否计算
    {
        cout<<"-1"<<endl;//不能输出-1
        return 0;//直接结束
    }
    for(int i=1;i<=n;i++)//外层枚举从1到N
    {
        for(int j=sum1;j>=a[i];j--)//01背包不要写成完全背包
        {
            f[j]=max(f[j],f[j-a[i]]+a[i]);//前面计算出来的公式，不要忘了。而且一定要取最大值
        }
    }
    cout<<sum-f[sum1]<<endl;//输出，一定记住是sum-f[sum1]，而不是f[sum1]，和P1049
    return 0;//结束（没啥说的????）
}
 ```
 ***
 珍惜生命，远离抄袭
 
 做完此题可尝试
 
 P1048,P1049,P1616等。

 不见不散！

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

### 题目大意

从n个数中找出若干个数，使得它们的和大于等于m且最小。

### 解题思路

* 首先，这是一道动态规划题，当然也可以是一道背包题，本题解使用01背包解题。
* 求出所有数字的和，用sum储存。如果sum小于m，就是说所有数字的和都达不到m，那么输出-1。
* 如果不是-1的情况，用一种选数方法使得选出来的数的和等于当前下标，而和大于等于m且最小。
* 关于状态转移方程，详情看下方代码。

思路如上，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
int n,m,a[100010],sum;
bool dp[60000];//定义变量
int main()
{
	cin>>n>>m;
	for(int i=1; i<=n; i++)
	{
		cin>>a[i];
		sum+=a[i];//求所有数的和
	}
	if(sum<m)//具体解释看上方思路
	{
		cout<<-1<<endl;
		return 0;
	}
	dp[0]=true;
	for(int i=1; i<=n; i++)
		for(int j=sum; j>=a[i]; j--)
			dp[j]=dp[j]||dp[j-a[i]];//具体转移方程
	for(int i=m; i<=sum; i++)
		if(dp[i])//如果和大于等于m且最小
		{
			cout<<i<<endl;
			return 0;
		}
	cout<<-1<<endl;//这个可有可没有，保险而已
	return 0;
}
//PS:j是容量，dp[i]是指第i个数
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：_Qer (赞：0)

这里一个DP

把这题当做01背包，设$f_{i,j}$为是否可以在应该取第$i$个数能否取到和为$j$，那么$f_{i,j}=f_{i-1,j-a_i}~||~f_{i-1,j}$，然后我们再像一般的背包一样压到一维，即$f_j$为能否取到$j$，于是DP就成了这样：

```cpp
  for (int i = 1; i <= n; ++i) {
    for (int j = V; j >= a[i]; --j) {
      f[j] = f[j - a[i]] || f[j];
    }
  }
```

这个时候我们再来看$V$，它可以设为所有数之和，因为所有数都为正数，所以所有数之和为能取的最大值，枚举到它可以保证把所有可能取的值都算到（应该还可以优化，~~但我不想写~~），$V=\sum{a_i}$，最后的结果就在$[m,V]$之间取$i$最小的$f_i=1$的$i$值

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int arr[60];
bool dp[500010];
int main() {
  scanf("%d%d", &n, &m);
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
    sum += arr[i];
  }
  if (sum < m) {//全部都取都不够，显然取不到m以上
    puts("-1");
    return 0;
  }
  dp[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = sum; j >= arr[i]; --j) {
      dp[j] = dp[j - arr[i]] || dp[j];//01背包
    }
  }
  for (int i = m; i <= sum; ++i) {
    if (dp[i]) {
      cout << i << endl;
      return 0;//可以取就输出并结束程序
    }
  }
  return 0;
}
```

---

## 作者：yoyiETO (赞：0)

这是一道01背包求方案数的题。

与01背包求最大价值不同的是，背包承重量会变化，所以要在状态中加入承重量。

状态：dp[i][j]表示前$i$个物品选择一些放入承重量为$j$的背包的方案数。

由于题目只让求有没有方案，所以可以定义成布尔型。

多阶段决策：每个物品都能选或不选，选和不选都是方案，所以相加（或运算）。

方程：$dp[i][j]=dp[i-1][j]+dp[i-1][j-w_i]$

初始化：当承重量为$0$时，什么都不选也是方案，$dp[i][0]=1$

因为只以来前一个状态，所以可以用滚动数组。

**Code**:
```cpp 
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
using namespace std;
const int N = 101,C = 1000001;
int n,m,w[N],dp[C];
int main()
{
    cin>>n>>m;
    int sum=0;
    for(int i=1;i<=n;i++)
    {
    	cin>>w[i];
    	sum+=w[i];//计算物品重量总和
	}
	if(sum<m)//如果总重量小于m输出-1
	{
		cout<<-1;
		return 0;
	}
    dp[0]=1;
    for(int i=1;i<=n;i++)
    for(int j=sum;j>=w[i];j--)//滚动数组
    	dp[j]|=dp[j-w[i]];
    for(int i=m;i<=sum;i++)
    	if(dp[i]){
    		cout<<i;
    		return 0;
		}
		cout<<-1;
    return 0;
}
```

---

