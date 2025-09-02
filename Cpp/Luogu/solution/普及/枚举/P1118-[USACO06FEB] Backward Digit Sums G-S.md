# [USACO06FEB] Backward Digit Sums G/S

## 题目描述

`FJ` 和他的奶牛们喜欢玩一个心算游戏。他们将数字从 $1$ 到 $N(1 \le N \le 10)$ 按某种顺序写下来，然后将相邻的数字相加，得到一个数字更少的新列表。他们重复这个过程，直到只剩下一个数字。例如，游戏的一种情况（当 $N=4$ 时）可能是这样的：

```cpp
    3   1   2   4
      4   3   6
        7   9
         16
```
在 `FJ` 背后，奶牛们开始玩一个更难的游戏，她们试图从最终的总和和数字 $N$ 中确定起始序列。不幸的是，这个游戏有点超出了 `FJ` 的心算能力。


编写一个程序来帮助 `FJ` 玩这个游戏，并跟上奶牛们的步伐。



## 说明/提示

- 对于 $40\%$ 的数据，$1\le n\le 7$；
- 对于 $80\%$ 的数据，$1\le n \le 10$；
- 对于 $100\%$ 的数据，$1\le n \le 12$，$1\le sum\le 12345$。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 16```

### 输出

```
3 1 2 4```

# 题解

## 作者：Sweetlemon (赞：301)

Upd: 这篇题解是我很久以前写的，当时错误也比较多；由于这篇题解的位置比较靠前，为防止误导，现在根据评论区的建议，对这篇题解进行更新。

拿到题目，是不是有一种“手足无措”的感觉呢？

在手足无措之前，先认真审题！

审题有两个要点：一是“$a$ 是 $1\sim n$ 的排列”，二是“字典序”的具体含义。

而且，并不是手足无措——我们可以暴力呢。

暴力的方法当然是，按字典序**枚举**最开始时的排列，对每一个排列都**计算**最后得到的数的值，如果这个值和题目给出的 $\mathrm{sum}$ 相等，那么我们就找到答案了。

如何按字典序枚举呢？可以使用 C++ 的 `next_permutation` 函数，也可以在 dfs 枚举排列时，每一层都从小到大枚举，这样自然就是按“字典序”枚举了。

--------------------------

这种方法有什么问题呢？当然是 **跑得太慢了**。于是我们要考虑优化“枚举”和“计算”的过程。

首先考虑优化“计算”过程。

要优化“计算”过程，就必须搞清楚这个数字三角形究竟是什么。

> 举例是理解的试金石。  

> ——《数学女孩》

> 数学上来先打表。

> —— OIer 行动准则（雾）

那我们就举例子吧！大家可以自己在草稿纸上写一下，假设 $n$ 为一个比较小的数（比如，按样例，$4$），设第一行的 $n$ 个数分别为 $a,b,c,\cdots$ （我这里是 $a,b,c,d$），然后模拟加一下，就会发现 $\mathrm{sum}$ 是……

如果 $n$ 为 $4$，那么 $\mathrm{sum}$ 是 $a+3b+3c+d$。  
如果 $n$ 为 $5$，那么 $\mathrm{sum}$ 是 $a+4b+6c+4d+e$。    
如果 $n$ 为 $6$，那么 $\mathrm{sum}$ 是 $a+5b+10c+10d+5e+f$。

观察各项的系数，你发现了什么？

---------------------------

如果你有敏锐的数学眼光，你会发现，各项系数恰与杨辉三角有关！恰好是杨辉三角中第 $n-1$ 行的各项系数！

那么我们就可以快速计算出“某个排列玩游戏的结果”了！

注：如果你想要证明这个结论，可以考虑使用“数学归纳法”（如果不了解这个方法，可以查找相关资料），你会发现“相邻两项相加”和杨辉三角（也就是组合数）有密切的联系。不过在 OI 中证明倒显得不是特别重要。

---------------------------

下面是算法的过程。

首先，为了避免重复计算，我们算出杨辉三角的值——“预处理”。

由于我们要计算的是杨辉三角一行（第 $n-1$ 行）所有数的值，因此可以使用这个公式：

$$\mathrm{C}^{r}_{n}=\frac{n-r+1}{r}\mathrm{C}^{r-1}_{n}$$

边界是 $\mathrm{C}^{0}_{n}=1$。

上述公式可根据组合数的定义推导。我们还可以利用杨辉三角的对称性，只计算一半（当然算一半和算完并没有显著的效率差异，因为 $n\le 12$ 很小）。

当然，我们也可以用 $\mathrm{C}^r_n=\mathrm{C}^{r-1}_{n-1}+\mathrm{C}^{r}_{n-1}$，边界是 $\mathrm{C}^{n}_{n}=\mathrm{C}^{0}_{n}=1$。

甚至直接根据组合数的定义计算也是可以的，但是要注意避免溢出。

---------------------------

然后，使用深度优先搜索。因为 dfs 可以按照题目中的“字典序”依次得出答案，因此我们不需再进行判断。这里使用了一个全局数组 `ans` 来存储答案。

---------------------------

最后，如果有解，输出答案。这个比较简单，就略过了。

---------------------------

我们其实还可以进一步优化“枚举”的过程。考虑这个问题：如果一个排列前面的数的（带系数的）和就已经超过了 $\mathrm{sum}$，那它还有可能成为答案吗？当然是不可能的。

因此我们在枚举的过程中可以注意把已枚举出的数的（带系数的）和与 $\mathrm{sum}$ 比较，如果已经比 $\mathrm{sum}$ 大就及时返回（“迷途知返”），从而加快速度。这个优化叫“剪枝”，是加快搜索速度的重要手段。

事实上，题目中的三档子任务，正对应了上面的三级优化！

---------------------------

下面是代码。

```cpp
#include <cstdio>
using namespace std;

int n,sum;
//以下所有数组的大小都比所需值稍大，是为了防止越界
int visited[25]={0}; //防止重复选数，这是 dfs 枚举排列的要点
int ans[25]; //放置答案
int pc[25];//构造所有i C n-1

int dfs(int i,int num,int v); //写函数原型是（我的）好习惯！

int main(void){
    scanf("%d%d",&n,&sum);
    //下面构造杨辉三角(即组合数表)
    pc[0]=pc[n-1]=1; //杨辉三角性质,两边都是1
    if (n>1)
        for (int i=1;i*2<n;i++)
            pc[i]=pc[n-1-i]=(n-i)*pc[i-1]/i; //利用杨辉三角对称性和组合数公式计算
    //下面枚举计算
    if (dfs(0,0,0)) //0 仅起占位符作用
        for (int i=1;i<=n;i++)
            printf("%d ",ans[i]); //输出答案
    return 0;
}

int dfs(int i,int num,int v){
//参数说明：i 表示已经枚举了前 i 个数(数的序号从 1 开始),num 表示第 i 个数是 num，v 表示前 i 个数的“和”为 v
//返回值说明:返回 0 表示不行(不可能)，返回 1 表示找到了可行解。利用返回值就可以在找到第一个解后直接返回了
    if (v>sum) //“剪枝”，及时排除不可能情况，加速枚举
        return 0; //不可能
    if (i==n){ //已经枚举了前 n 个（全部）,判断一下是否是可行解
        if (v==sum){
            ans[i]=num; //放置解
            return 1;
        }
        else
            return 0;
    }
    visited[num]=1; //标记一下“第 i 个数的值已经使用过了”
    //下面寻找第 i+1 个数
    for (int j=1;j<=n;j++){
        if (!visited[j] && dfs(i+1,j,v+pc[i]*j)){ //v+pc[i]*j表示前(i+1)个数的“和”
            //注意，如果数的序号从 1 开始，那么第 i 个数的系数实际上是 (i-1) C (n-1)
            //执行到这里表示已经找到了可行的解
            ans[i]=num;
            return 1;
        }
    }
    visited[num]=0; //如果没有找到，一定记得复位，为进一步的寻找做准备
    return 0; //执行到这里一定是没有找到解
}
Show you my code(C++,94 ms,776 KB).
```

---

## 作者：wpy233 (赞：184)

首先，你想要AC此题，就必须搞懂这个三角形的本质究竟是神马。

大家可以算一算，设一个较小的数，模拟一下。

比如偶设n=5，按照题目中的要求一步步模拟：
```
a     b     c     d      e
  a+b   b+c   c+d     d+e
   a+2b+c b+2c+d  c+2d+e
    a+3b+3c+d b+3c+3d+e
        a+4b+6c+4d+e
```
好，最终我们通过一步步的模拟，算出当n=5时，1~5位上对应的权值应该是：
```
位数 1 2 3 4 5
权值 1 4 6 4 1
```
想必各位萌新看到这很激动——这不就是杨辉三角的第五行么！！！

别急，我们再来验证一个,设n=8，我们再来模拟一遍：
```
a       b      c       d       e        f        g       h
 a+b      b+c      c+d      d+e      e+f       f+g     g+h
  a+2b+c    b+2c+d    c+2d+e    d+2e+f    e+2f+g   f+2g+h
   a+3b+3c+d  b+3c+3d+e  c+3d+3e+f  d+3e+3f+g  e+3f+3g+h
    a+4b+6c+4d+e b+4c+6d+4e+f c+4d+6e+4f+g d+4e+6f+4g+h
     a+5b+10c+10d+5e+f b+5c+10d+10e+5f+g c+5d+10e+10f+5g+h
      a+6b+15c+20d+15e+6f+g b+6c+15d+20e+15f+6g+h
       		a+7b+21c+35d+35e+21f+7g+h
```
经过一番激动人心的验算，我们算出了当n=8时，1~8位对应的权值：
```
位数  1  2  3  4  5  6  7  8
权值  1  7  21 35 35 21 7  1
```
。。。算到这里，结论已经很明确了。。。

#最终答案=该位杨辉三角中的数*该数#

所以，本题的第一步，你需要先算出第n行杨辉三角的值是多少。
```
c[1][1]=1;//最左上角的数初始化为1
for(int i=2;i<=n;i++)//由于这里数组的记录是从1开始记的，所以不用担心越界
	for(int j=1;j<=i;j++)
		c[i][j]=c[i-1][j]+c[i-1][j-1];//每个数都等于它肩上两数之和
```
#至此，辉煌的第一步完成了#

接下来，就是④字：

#暴力深搜！#

注意，在深搜的过程中要好好剪枝，不然你会_TLE_嘻嘻

由于本人是萌新，代码不难看懂吧：）
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int n,p;//输入必备
int a[13];//输出必备
int c[13][13];//杨辉三角必备
bool b[13];//判重必备
void dfs(int dep,int s)
{
	if(s>p)//如果现在累加的数已经超过了给定的数，就返回
		return;
	if(dep>n)//如果已经搜完了n个数，就返回
	{
		if(s==p)//如果答案跟给定的数相等
		{
			cout<<a[1];
			for(int i=2;i<=n;i++)
				cout<<" "<<a[i];//输出
			exit(0);//终止程序
		}
		return;//如果没有输出答案，就返回
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i]==false)//如果当前这个数没有用过
		{
			b[i]=true;//标记成用过
			a[dep]=i;//保存第dep个取的数
			dfs(dep+1,s+i*c[n][dep]);
			b[i]=false;//注意这里要将状态回归，不然TLE
		}
	}
}
int main()
{
	cin>>n>>p;//输入
	c[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i;j++)
			c[i][j]=c[i-1][j]+c[i-1][j-1];//生成杨辉三角
	dfs(1,0);//开启深搜之旅
	return 0;
}
```
本弱弱的第二篇题解。

#感谢大佬欣赏#

---

## 作者：geek痕 (赞：65)

看了一下题解，居然没人用stl，next\_permutation生成下一个排列不就直接完事了嘛。

**超时！**是的，直接next\_permutation会超时，但优化一下就亦可赛艇了。。

具体措施如下：

当发现当前的和值大于目标时，那么再next\_permutation是肯定超的，应该跳过去。

怎么跳呢？我们把从发现超过目标时所计算到的位开始，一直到结束的所有位排序成从大到小，下次再next\_permutation的时候就能完美跳过这一段了。perfect！

来来来，一起念，stl大法好，简单粗暴没得跑。

具体上代码，尽量注释。





    
    
    
        
        
        
        

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
int num_a[15];
int log_a[15][15];
int cmp(int t1,int t2){
    return t1>t2;
}
int main() {
    //freopen("test.in","r",stdin);
    int n,sum;
    cin>>n>>sum;
    for(int i=1; i<=n; i++) num_a[i]=i;
    for(int i=1;i<=n;i++)log_a[i][1]=log_a[i][i]=1;
    for(int i=3;i<=n;i++){
        for(int k=1;k<=(i-1)/2;k++){
            log_a[i][k+1]=log_a[i][i-k]=log_a[i-1][k]+log_a[i-1][k+1];
        }
    }
    //以上先弄出一个杨辉三角来，这是必须的。
    do {
        int out_a=0;
        int num_tmp[15];
        memcpy(num_tmp,num_a,sizeof(num_tmp));
        int tsum=0;
        for(int i=1;i<=n;i++){
            tsum+=num_tmp[i]*log_a[n][i];
            if(tsum>sum){//没错，关键就这里，发现从当前开始的i位开始往后累加都会超过预期，就把它从大到小排一遍，再next的时候就能跳过这一段了                
                                sort(num_a+i,num_a+n+1,cmp);
                out_a=1;
                break;
            }
        }
        if(out_a) continue;
        if(tsum==sum){
            for(int i=1;i<=n;i++){
                cout<<num_a[i]<<" ";
            }
            break;
        }
    } while(next_permutation(num_a+1,num_a+1+n));
}
```

---

## 作者：xzlhxc_ed (赞：37)

~~重新提交更改错字~~
 
刚看到这题，以为要从底到上dfs，想了想，绝对TLE，就想着用全排列骗些分。
# 让我们从骗分开始……
# ①全排列dfs爆算
```cpp
//输入
int ans[maxn],n,sum;
bool is_used[maxn];
bool is_success();
void dfs(int now)
{
	if(now==n+1)
	{
		if(is_success())
		{
			print();//略 
			flag=1;
			return;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(flag)break;
		if(!is_used[i])
		{
			is_used[i]=true;
			ans[now]=i;
			dfs(now+1);
			is_used[i]=false;
		}
	}
} 
```
大部分的问题已经解决，那么如何解决```is_success()```呢？
# ②杨辉三角
#### 最简单的办法自然是双重循环模拟，但是时间复杂度为（n^2）太慢了！！！
其实，看到这道题的题目，手模一遍就可以知道里面的某些数是重复加的，所以，我们只要求出它的规律便可。手模可得这个规律就是杨辉三角。

鉴于前面的大佬们介绍得很详细了，在此不再赘述。

杨辉三角的递推式是：
### yhsj[i][j] = yhsj[i-1][j-1] + yhsj[i][j-1]

当然，在这一题中，我们可以开一个yhsj[maxn][maxn]的二维数组来储存，不过，递推式的每一层（每一个j）都只于上一层（j-1）有关系，所以我们可以利用奇偶性滚动利用数组（轮流使用yhsj[i][0]与yhsj[i][1]）。
```cpp
int N=n&1;
void makes//预处理
{
    yhsj[1][1]=1;
	for(int i=2;i<=n;i++)
	 for(int j=1;j<=i;j++)
      yhsj[j][i&1]=yhsj[j][(i-1)&1]+yhsj[j-1][(i-1)&1];
    return;
}//事实上并不会复杂到哪里去，这个思想在其它算法中也是可以运用的
bool is_success()
{
	int summ=0;
	for(int i=1;i<=n;i++)
	{
		summ+=ans[i]*yhsj[i][N];
		if(summ>sum)return false;//预判
	}
	return summ==sum;
}
```
这样，判断的函数就可以写出来了。但是，当你提交后，你会发现，80分……
# ③dfs二维优化
前面的代码的判断函数往往在排列结束时调用，那么，有些不可能的状态只有在结束时才会被排除，浪费了大量的时间。所以，我们要剪枝，在发现超出sum时立刻停止。因此，我们要将dfs函数多开一维。
```cpp
void dfs(int now,int summ)//summ表示到目前的总和
{
	if(now==n+1)
	{
		if(summ==sum)
		{
			print();
			flag=1;
			return;
		}
		else return;
	}
	for(int i=1;i<=n;i++)
	{
		if(flag)break;
		if(!isused[i]&&summ+i*yhsj[now][N]<=sum)//一旦超出，立刻停止
		{
			isused[i]=true;
			ans[now]=i;
			dfs(now+1,summ+i*yhsj[now][N]);
			isused[i]=false;
		}
	}
	return;
}
```
# ④ AC！

---

## 作者：RedContritio (赞：25)

第一次写的时候，发现模拟计算求和非常费时间，通过找规律，可以发现，规律是杨辉三角加权。

然后，每次dfs到最后一层的时候求和计算。

最后，TLE，挂在了70分。

后来发现 ， 可以将dfs写成二元函数，即 dfs(int sum,int p) sum表示目前的和，p表示待搜索位置。

CPP

```cpp
#include <cstdio>
#include <cstdlib>
const int PT[][13] = //先打一张杨辉三角表
{
    { 1 } , // N = 1 
    { 1 , 1 } , // N = 2
    { 1 , 2 , 1 } , // N = 3
    { 1 , 3 , 3 , 1 } , // N = 4
    { 1 , 4 , 6 , 4 , 1 } , // N = 5
    { 1 , 5 , 10, 10, 5 , 1 } , // N = 6
    { 1 , 6 , 15, 20, 15, 6 , 1 } , // N = 7
    { 1 , 7 , 21, 35, 35, 21, 7 , 1 } , // N = 8
    { 1 , 8 , 28, 56, 70, 56, 28, 8 , 1 } , // N = 9
    { 1 , 9 , 36, 84,126,126, 84, 36, 9 , 1 } , // N = 10 
    { 1 , 10, 45,120,210,252,210,120, 45, 10 , 1 } , // N = 11
    { 1 , 11, 55,165,330,462,462,330,165, 55 ,11 , 1 } }; // N = 12 
int a[15],dfs(int s,int p);
int n,sum;
bool finished,used[15];
int main()
{
    scanf("%d%d",&n,&sum);
    dfs(0,0); // 从 0，0 开始搜索
    if(finished)for(int i=0;i<n;i++)printf("%d ",a[i]);
}
int dfs(int s,int p)
{
    if( p == n )
    {
        if( s==sum) finished = true ;
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        if(used[i])continue ;
        used[i] = true ;
        a[p] = i;
        if( s+ PT[n-1][p]*a[p] <= sum )dfs( s+ PT[n-1][p]*a[p] , p+1 ) ; //剪枝 ， 若dfs之后无意义，则跳过本回合
        if(finished )return 0;
        used[i] = false ;
    }
}

```

---

## 作者：远航之曲 (赞：14)

运用的dfs思想，fn代表这一层的杨辉三角。a代表这一层的排列。运用这个优化可以优化时间效率。（要不会tle）

废话不多说，直接上代码。

（减少题解复制，创建美好洛谷）


```cpp 
//#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int f[130][130]={0};
int a[130]={0};
bool v[130]={true};
int n=0,m,sum=0;

void init()
{
    scanf("%d%d",&n,&sum);
    for (int i=1;i<=n;i++)
      f[i][1]=1;
    for (int i=2;i<=n;i++)
      for (int j=2;j<=i;j++)
        f[i][j]=f[i-1][j]+f[i-1][j-1];
    m=0;
    memset(v,true,sizeof(v));
}

void dfs(int i)
{
    if (m>sum) return;
    if (i==n+1)
    {
        if (sum==m)
        {
            for (int j=1;j<=n;j++)
              printf("%d ",a[j]);
            exit(0);
        }
        return;
    }
    for (int j=1;j<=n;j++)
      if (v[j])
        {
            a[i]=j;
            m+=f[n][i]*j;
            v[j]=false;
            dfs(i+1);
            a[i]=0;
            m-=f[n][i]*j;
            v[j]=true;
        }
}
main()
{
    init();
    dfs(1);
}
```

---

## 作者：Utsuji_risshū (赞：8)

这题数据比较水所以很多人dfs全排列加简单剪枝就水过了。但是如果把$n$范围调到$18$以上可能有的题解要$gg$。这里提供一种题解区暂时没发现有的强剪枝:

首先要知道一开始一个数列加到最后得到的数是可以用杨辉三角形系数算的,这个其他dalao已经在题解中总结这里不再赘述.

当当前$dfs$到某一个状态s(采用二进制位表示,第$i-1$位代表$i$这个数填没填过$(0/1)$)如果当前状态累加值加上剩下没选的数填充上去最大可以产生的值都小于$sum$或当前状态累加值加上剩下没选的数填充上去最小可以产生的值大于$sum$那么就可以咔嚓剪掉了.实测效果很好.

重点在于预处理这样一个判断的数组.我们用$minv[s]$表示推到$s$状态时剩下的数填充可以产生的最小值.$maxv[s]$同理.然后$minv[(1<<n)-1]=0$作为初始状态从后向前状压dp预处理即可.详细见代码.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20,INF=0x3f3f3f3f;
inline int MIN(int&a,int b){return a>b?(a=b,1):0;}
inline int MAX(int&a,int b){return a<b?(a=b,1):0;}
inline int read(){
	char c;int f=0,x=0;while(!isdigit(c=getchar()))if(c==45)f=1;
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();return f?-x:x;
}
int C[N],bin[N],used[N];
int maxv[1<<N],minv[1<<N];
int n,k,ful,cnt,flag;

inline int Count(int x){int ret=0;while(x)++ret,x&=(x-1);return ret;}
void dfs(int step,int s,int sum){
	if(step==n&&sum==k){
		for(register int j=1;j<=step;++j)printf("%d ",used[j]);puts("");
		flag=1;return;
	}
	if(sum+minv[s]>k||sum+maxv[s]<k)return;//强剪枝
	for(register int j=0;j<n;++j)
		if(flag)return;
		else if(!(bin[j]&s))used[step+1]=j+1,dfs(step+1,s|bin[j],sum+C[step]*(j+1));
}

int main(){
	n=read(),k=read();C[0]=bin[0]=1;ful=1<<n;
	for(register int i=1;i<n;++i) C[i]=C[i-1]*(n-i)/i;//这里采用直接组合数推杨辉三角
	for(register int i=1;i<=n;++i) bin[i]=bin[i-1]<<1;
	for(register int i=ful-1;~i;--i) minv[i]=INF;minv[ful-1]=0;//注意清零
	for(register int i=ful-1;i;--i){
		cnt=Count(i);
		for(register int j=0;j<n;++j) if(bin[j]&i)//逆推
		MAX(maxv[i^bin[j]],maxv[i]+(j+1)*C[cnt-1]),MIN(minv[i^bin[j]],minv[i]+(j+1)*C[cnt-1]);
	}//码风不正常见谅像dalao学的
	dfs(0,0,0);
	return 0;
}
```

---

## 作者：封禁用户 (赞：7)

首先，这个题有关全排列。              
这个题可以用全排列，先排出来再算sum的值，如果正确就输出，然后退出DFS，错误就继续进行排列。
```cpp
#include<iostream>
using namespace std;
int a[12][12],n,sum;
bool b[13],c=true;
int f()
{
    int i;
    for(i=1;i<n;i++)
        for(int k=0;k<n-i;k++)
            a[i][k]=a[i-1][k]+a[i-1][k+1];		
    return a[i-1][0];			
}//计算sum的值。
void dfs(int t)
{
    for(int i=1;i<=n;i++)
    {
        if(b[i]==false)
        {
            b[i]=true;
            a[0][t]=i;
            if(t==n-1&&f()==sum)
            {
                c=false;
                return;
            }
            else dfs(t+1);
            if(c==false) return;//搜到答案之后，退出DFS。
            b[i]=false;
        }
    }
}//进行全排列。
int main()
{
   	cin>>n>>sum;
    dfs(0);
    for(int i=0;i<n;i++)
        cout<<a[0][i]<<" ";//输出答案。
    return 0;
}
```
### 这个代码只能骗60分，4个点TLE。
### 所以，要写优化！
优化并不难，细心就可以看出，可以用杨辉三角形进行优化。   
如果n为4，那么sum是a1+3a2+3a3+a4。  
如果n为5，那么sum是a1+4a2+6a4+4a5+a6。
### 这就是一个杨辉三角形的优化！
所以，代码改成:
```cpp
#include<iostream>
using namespace std;
int a[12],n,sum;
bool b[13],c=true;
int d[12][13]= 
{
    {1}, 
    {1,1}, 
    {1,2,1},
    {1,3,3,1}, 
    {1,4,6,4,1}, 
    {1,5,10,10,5,1},  
    {1,6,15,20,15,6,1} , 
    {1,7,21,35,35,21,7,1}, 
    {1,8,28,56,70,56,28,8,1}, 
    {1,9,36,84,126,126,84,36,9,1}, 
    {1,10,45,120,210,252,210,120,45,10,1}, 
    {1,11,55,165,330,462,462,330,165,55,11,1}};
//打表杨辉三角形（闲的）。    
int f()
{
    int ans=0;
    for(int i=0;i<n;i++)
        ans=d[n-1][i]*a[i]+ans;	
    return ans;		
}//计算sum的值。
void dfs(int t)
{
    for(int i=1;i<=n;i++)
    {
        if(b[i]==false)
        {
            b[i]=true;
            a[t]=i;
            if(t==n-1&&f()==sum)
            {
                c=false;
                return;
            }
            else dfs(t+1);
            if(c==false) return;//搜到答案之后，退出DFS。
            b[i]=false;
        }
    }
}//进行全排列。
int main()
{
    cin>>n>>sum;
    dfs(0);
    if(c==false)
    {
        for(int i=0;i<n;i++)
            cout<<a[i]<<" ";//输出答案。
    }
    return 0;
}
```

### 但是，只得了80分，依旧TLE了两个点。
### 因此还要优化！
优化也不难，只是在DFS中加个特判，数值超限就停止那次搜索，立刻回溯。
所以，代码改成:
```cpp
#include<iostream>
using namespace std;
int a[12],n,sum,ans=0;
bool b[13],c=true;
const int d[12][13]= 
{
    {1}, 
    {1,1}, 
    {1,2,1},
    {1,3,3,1}, 
    {1,4,6,4,1}, 
    {1,5,10,10,5,1},  
    {1,6,15,20,15,6,1}, 
    {1,7,21,35,35,21,7,1}, 
    {1,8,28,56,70,56,28,8,1}, 
    {1,9,36,84,126,126,84,36,9,1}, 
    {1,10,45,120,210,252,210,120,45,10,1}, 
    {1,11,55,165,330,462,462,330,165,55,11,1}};
//打表杨辉三角形（闲的）。    
void dfs(int t)
{
    for(int i=1;i<=n;i++)
    {
        if(b[i]==false)
        {
            b[i]=true;
            a[t]=i;
            ans+=d[n-1][t]*i;//计算DFS中sum的值。
            if(t==n-1&&ans==sum)
            {
                c=false;
                return;
            }
            else if(ans<sum) dfs(t+1);//不超限的话，继续搜索。
            if(c==false) return;//搜到答案之后，退出DFS。
            b[i]=false;
            ans-=d[n-1][t]*i;
        }
    }
}//进行全排列。
int main()
{
    cin>>n>>sum;
    dfs(0);
    if(c==false)
    {
        for(int i=0;i<n;i++)
            cout<<a[i]<<" ";//输出答案。
    }
    return 0;
}
```
## 100分，完美AC结束！

---

## 作者：B_K201 (赞：6)

首先，这题目要运用到两个数学知识，一个是杨辉三角，这个自己多写几遍可以发现这个规律，杨辉三角的递推式子是

c[i][j]=c[i-1][j-1]+c[i-1][j];  OK

接下来，我们需要另一个数学知识，叫做排序不等式，就是存在两个不等式队列，x1<=x2<=x3<=x4.<=xn；y1<=y2<=y3<=y4...<=yn。两个相乘符号不变，用于查看还没选的数，它必须满足这个排序不等式的规律

最后，再加上一个判断的最优性剪枝即可





```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n,sum,ans[25]={0},c[25][25]={0};
bool vis[25]={0};
void solve(int step,int &maxx,int &minx)
{
    maxx=minx=0;
    int j1=1,j2=n;
    for(int i=0;n-i>=i+1;i++)
    {
        if (!ans[i+1])
        {
            while(vis[j1]) j1++;
            while(vis[j2]) j2--;
            maxx+=j1*c[n][i+1];j1++;
            minx+=j2*c[n][i+1];j2--;
        }
        if (!ans[n-i]&&n-i>i+1)
        {
            while(vis[j1]) j1++;
            while(vis[j2]) j2--;
            maxx+=j1*c[n][i+1];j1++;
            minx+=j2*c[n][i+1];j2--;
        }
    }
}
bool dfs(int step,int now)
{
    if (step==n+1)
    {
        if (now==sum) {for(int i=1;i<=n;i++) printf("%d ",ans[i]);return 1;}
        else return 0;
    }
    int maxx,minx;
    solve(step,maxx,minx);
    if (now+maxx<sum) return 0;
    if (now+minx>sum) return 0;
    int i=1;
    if (step>n-step+1) i=ans[n-step+1]+1;
    for(;i<=n;i++)
        if (!vis[i])
        {
            ans[step]=i;
            vis[i]=1;
            if (dfs(step+1,now+i*c[n][step])) return 1;
            ans[step]=0;
            vis[i]=0;
        }
    return 0;
}
int main()
{
    scanf("%d%d",&n,&sum);
    c[1][1]=1;
    for(int i=2;i<=n;i++)
        for(int j=1;j<=i;j++)
            c[i][j]=c[i-1][j-1]+c[i-1][j];
    dfs(1,0);
    return 0;
}
```

---

## 作者：幻蓝刀心 (赞：4)

# **杨辉三角及普通枚举应用**
### 大佬们，放过我这个啥也不会、啥也不懂的蒟蒻吧！！！
首先，这道题最开始要解决的便是由几个数推出来的最后一个数；
先举个栗子
![](https://cdn.luogu.com.cn/upload/image_hosting/jinfr431.png)
 
同志们，发现最后结果的特点了吗？？？
## 那就是
#### 满足杨辉三角的系数
那么便有如下推导方式
![](https://cdn.luogu.com.cn/upload/image_hosting/0152g9t3.png)

再加上明显可以压缩空间变为一维数组
故最后的方程就是
# f[j]+=f[j-1]
#### 啥子?问我为啥要用j??f~~我不会告诉你~~是从右往左刷的
于是乎，可以预处理一哈
```cpp
	memset(c,0,sizeof(c));
	c[1]=1;
	for(int i=2;i<=n;i++)
		for(int j=i;j>=1;j--)
			c[j]+=c[j-1];
```
也就是说a[i]来存数，而c[i]表示最后的系数
然后运用一下系统里的next_permutation(a+1,a+n+1)来列举全排列，然后你会惊奇的发现，这题基本就完了？？？

然鹅

时间会爆掉
于是就要进行剪枝操作，吼吼吼，具体如何剪枝你猜啊！！！
代码放上
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int maxn=20;
int a[maxn];
int c[maxn];
int n,sum;
bool comp(int x,int y)
{
	return x>y;
}
main()
{
	cin>>n>>sum;
	for(int i=1;i<=n;i++)
		a[i]=i;
	memset(c,0,sizeof(c));
	c[1]=1;
	for(int i=2;i<=n;i++)
		for(int j=i;j>=1;j--)
			c[j]+=c[j-1];
	do
	{
		int s=0;
		bool flag=false;
		for(int i=1;i<=n;i++)
		{
			s+=a[i]*c[i];
			if(s>sum)
			{
				flag=true;
				sort(a+i,a+n+1,comp);
				break;
			}
		}
		if(flag)continue;
		if(s==sum)
		{
			for(int i=1;i<=n;i++)
				cout<<a[i]<<' ';
			cout<<endl;
			break;
		}
	}while(next_permutation(a+1,a+n+1));
	return 0;
}
```



---

## 作者：momo5440 (赞：4)

正如前辈所说此题正是杨辉三角与深搜，但我与别人不一样，杨辉三角我打表！！！
不废话 上代码
```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
int db[13][13]={
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,0,0,0,0,0,0,0,0,0,0},
{0,1,2,1,0,0,0,0,0,0,0,0,0},
{0,1,3,3,1,0,0,0,0,0,0,0,0},
{0,1,4,6,4,1,0,0,0,0,0,0,0},
{0,1,5,10,10,5,1,0,0,0,0,0,0},
{0,1,6,15,20,15,6,1,0,0,0,0,0},
{0,1,7,21,35,35,21,7,1,0,0,0,0},
{0,1,8,28,56,70,56,28,8,1,0,0,0},
{0,1,9,36,84,126,126,84,36,9,1,0,0},
{0,1,10,45,120,210,252,210,120,45,10,1,0},
{0,1,11,55,165,330,462,462,330,165,55,11,1},
};//杨辉三角 
int a[20];//存储数 
int n,sum;
int su=0;//当前的和 
bool b[20];//判断一个数有没有被用过 
void dfs(int x){
	if (x==n+1){//深搜边界 
		if (su==sum){
			for (int i=1;i<=n;i++){
				cout<<a[i]<<' ';
			}
			exit(0);
		}
		return;
	}
	if (su>sum) return;//剪枝（过了边界就回去）（不剪枝两个TLE） 
	for (int i=1;i<=n;i++){//深搜模板（从1到n枚举数） 
		if (b[i]==false){
			b[i]=true;
			a[x]=i;
			su+=i*db[n][x];
			dfs(x+1);
			su-=i*db[n][x];
			b[i]=false;
		}
	}
}
int main(){
	cin>>n>>sum;
	memset(b,0,sizeof(b));
	dfs(1);
}
```

---

## 作者：龙行龘龘 (赞：3)

# 看了下题解,你们都很优秀啊

不过这么简单为什么不打表......

数学的老公是科学，物理的老爹是科学，化学的老爷是科学，信息的老祖是科学。

哦，多么多情的科学！！！

首先,我们第一反应就是看数据打个杨辉三角的表

接着就是输入输出处理一下

### 最后DFS爆搜啊...

# 等等

好像T了两个点...

哦哦,对,还有就是要在DFS里进行剪枝(过边就退)

这题特判输出有点制杖...

顺便献上我的blog:https://www.luogu.org/blog/Root-std-admin/

好了,下面是代码:

```cpp
//Written By:Jason_Root
//Time Limit : 1000 MS
//Memory Limit : 65536 KB
#include<bits/stdc++.h>
using namespace std;
int n,sum;//输入数据
int su = 0;//当前的和
int ans[20];//输出数据 
int book[20];//标记
inline int read() {//快读
	char ch = getchar();
	int x = 0, f = 1;
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
const int PT[][14] = {//打个杨辉三角的表
	{1},
	{1,1},
	{1,2 ,1},
	{1,3 ,3 ,1},
	{1,4 ,6 ,4  ,1},
	{1,5 ,10,10 ,5  ,1},
	{1,6 ,15,20 ,15 ,6  ,1},
	{1,7 ,21,35 ,35 ,21 ,7  ,1},
	{1,8 ,28,56 ,70 ,56 ,28 ,8  ,1},
	{1,9 ,36,84 ,126,126,84 ,36 ,9  ,1},
	{1,10,45,120,210,252,210,120,45 ,10 ,1},
	{1,11,55,165,330,462,462,330,165,55 ,11,1},
	{1,12,66,220,495,792,924,792,495,220,66,12,1}
};
void DFS(int dep) {
	if(dep == n+1) { //深搜边界
		if (su == sum){
		    for (int i = 1;i <= n;i++){
		        printf("%d ",ans[i]);
		    }
		    exit(0);
		}
		return;
	}
	if (su > sum) {
		return;//剪枝（过了边界就回去）（不剪枝两个TLE）
	}
	for (int i = 1; i <= n; i++) { //深搜模板（从1到n枚举数）
		if (!book[i]) {
			book[i] = 1;
			ans[dep] = i;
			su+= i*PT[n-1][dep-1];
			DFS(dep+1);
			su-= i*PT[n-1][dep-1];
			book[i] = 0;
		}
	}
}
void func() {
	ios_base::sync_with_stdio(false);
	memset(book,0,sizeof(book));
	n = read();//输入层数n
	sum = read();//输入最后得到的数字的大小sum
	DFS(1);
	return;
}
int main() {
	func();
	return 0;
}
```
真心感谢大家观看,谢谢!!!

---

## 作者：passerbyYSQ (赞：3)

## 杨辉三角
看完题目的计算规则，总感觉跟杨辉三角有点关系。不妨手动模拟一下sum的计算。

如果n为4，那么sum是a+3b+3c+d

如果n为5，那么sum是a+4b+6c+4d+e

如果n为6，那么sum是a+5b+10c+10d+5e+f

...

然后对比一下杨辉三角。。
![](https://img-blog.csdnimg.cn/20191005094054801.jpg)
额，，，此时，，，像发现了新大陆

sum的各项系数与杨辉三角有关！那么主题思路就有了：

那我们就可以通过预处理n<=12杨辉三角，在dfs枚举全排列中的每一个数时就乘上这个系数

## 大剪枝

dfs中有个累加的ans，一旦这个ans>sum。那么当前这个有n个数的全排列序列没有深搜完，也没必要继续下去了，因为后面无论填充什么数，它都不可能等于sum。继续深搜只是做无用功。


## 小剪枝

 这个是**lzh**大佬告诉我的，利用杨辉三角的对称性！

以n=5说明，如果n为5，那么sum是a+4b+6c+4d+e

那么我们dfs找一个全排列序列：a, b, c, d, e

注意到上式的系数是对称的，有什么好处呢？举例说：当b=3, d=5 和 当b=5, d=3，其他数位a,c,e相同，那么计算出来的sum值是一样的

又由于要求是字典序最小的，那么必定有符合题目要求的全排列必定有以下规律：a<e 且 b<d（这里仅仅是以n=5说明）

注：代码中有个细节我已经加了注释，原因我就不说了。如果懂了这个剪枝的意思，自然就明白为什么了。

**代码**
https://blog.csdn.net/qq_43290318/article/details/102131328
阅读效果更佳。。。

求过QAQ

---

## 作者：吴海啸 (赞：3)

```cpp
var n,m,i,j:longint;
sj:array[0..20,0..20] of longint;
pd:array[1..12] of boolean;
a:array[1..12] of longint;
procedure dfs(k,s:longint);
var i,t:longint;
begin
if s>m then exit;
if k=n then 
begin
t:=0;
for i:=1 to n do 
    t:=t+a[i]*sj[n,i];
if t=m then 
begin
for i:=1 to n do 
    write(a[i],' ');
halt;
end;
end;
for i:=1 to n do
if pd[i]=false then 
begin
s:=s+i*sj[n,k+1];
a[k+1]:=i;
pd[i]:=true;
dfs(k+1,s);
s:=s-i*sj[n,k+1];
pd[i]:=false;
end;
end;
begin
readln(n,m);
fillchar(pd,sizeof(pd),false);
fillchar(a,sizeof(a),0);
for i:=1 to n do 
begin
sj[i,1]:=1;
sj[i,i]:=1;
end;
for i:=3 to n do
for j:=2 to i do
sj[i,j]:=sj[i-1,j]+sj[i-1,j-1];
for i:=1 to n do
if pd[i]=false then 
begin
a[1]:=i;
pd[i]:=true;
dfs(1,i);
pd[i]:=false;
end;
end.
本题使用dfs。1—n的某个排列按题目规则最后合并成一个sum，给出sum，求字典序最小的排列。其实该倒三角对应着杨辉三角，第N层相应位置的数值相乘之和就是SUM。于是先预处理好杨辉三角，再按字典序从小到大进行深度优先搜索，找到的第一个符合的便退出并输出。可是这样还不够，还是会超时，必须加入优化。每一层都计算当前的和，当当前和已经超过目前最小值，说明再搜索已经无用了，提前退出。到达最底层后，依题目的意思，什么都不输出。
```

---

## 作者：coyangjr (赞：2)

分享一下自己打表的方法，就是那个题解说的杨辉三角，不过自己没看出，就推了一遍样例。

# ~~数学~~老师说过
>##  从特殊到一般

所以就不能~~老老实实~~的拿样例数据来推。

我们先设$n=4$， 原始数据为$a,b,c,d$

line 1 $a\qquad\ \ b\qquad \ \ c\qquad \ \ d$

line 2 $\ \ a+b\quad b+c\quad c+d$ 

line 3 $\ a+2b+c \quad b+2c+d$ 

line 4$\qquad a+3b+3c+d$

~~latex不会用，丑，见谅~~

于是就有了
$a+3b+3c+d=sum$

之后由于$a,b,c,d \in \{1,2,3,4\}$,~~暴力~~$DFS$求解，找到第一个就$OK$,$exit(0)$了（因为是按顺序dfs的，第一个一定是字典序最小的）

所以，我们现在就需要找$a\ b\ c\ d $的系数~~（因为$a+3b+3c+d=sum$中要用。。。）~~

献上代码

```cpp
struct box{//结构体，方便写。。吧
	int a[12];//a数组记录系数，A的系数->a[0],B的系数->a[1]...
	box operator + (const box &rhs) {
    /*
    运算符重载，就是对两个结构体相加时
    分别对系数相加（提取公因数？（逃 ）
    1*A+2*A=(1+2)*A
    */
		box n;
		for (re int i=0;i<12;i++){
			n.a[i]=a[i]+rhs.a[i];
		}
		return n;
	}
}mp[12][12]; //建表存储
box a,b,c;
int main()
{
	freopen("out.txt","w",stdout);//文件输出，方便粘贴
	int n;
	for (re int n=0;n<=12;n++){//枚举n=0~12的情况
	for (re int i=0;i<n;i++)//对于初值赋值
	 mp[0][i].a[i]=1;//第0行(初始)的第i列，a[i]为1；
	for (re int i=1;i<n;i++)
	{
		for (re int j=0;j<n-i;j++)
		{
			mp[i][j]=mp[i-1][j]+mp[i-1][j+1];//从上到下累加
		}
	}
	cout<<"{";//控制下输出格式，方便最后调试
	for (re int i=0;i<n;i++) {cout << mp[n-1][0].a[i];if (i!=n-1)cout<<",";}//输出表
	cout<<"},";}
}
```

打出来后out.txt中是这样的
>{},{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1},{1,5,10,10,5,1},{1,6,15,20,15,6,1},{1,7,21,35,35,21,7,1},{1,8,28,56,70,56,28,8,1},{1,9,36,84,126,126,84,36,9,1},{1,10,45,120,210,252,210,120,45,10,1},{1,11,55,165,330,462,462,330,165,55,11,1},

修改一下
```cpp
int f[15][15]={{0},{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1},{1,5,10,10,5,1},{1,6,15,20,15,6,1},{1,7,21,35,35,21,7,1},{1,8,28,56,70,56,28,8,1},{1,9,36,84,126,126,84,36,9,1},{1,10,45,120,210,252,210,120,45,10,1},{1,11,55,165,330,462,462,330,165,55,11,1}};
```

再加上dfs的代码，便可AC

```cpp
//P1118 [USACO06FEB]数字三角形
#include <iostream>
#include <cctype>
#include <cmath>
#include <ctime>
#include <climits>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <sstream>
#define debug cout << "debug"<<endl

using namespace std;
#define il inline
#define re register
typedef long long ll;


#ifndef ONLINE_JUDGE
il void scan(int &x)
{
	x=0;re int w=0;re char ch=0;
	while (!isdigit(ch)) w|=ch=='-',ch=getchar();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if (w) x=-x;
}

il void scan(ll &x)
{
	x=0;re int w=0;re char ch=0;
	while (!isdigit(ch)) w|=ch=='-',ch=getchar();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if (w) x=-x;
}
#endif
#ifdef ONLINE_JUDGE
il char getc()
{
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
il void scan(int &x)
{
	x=0;re int w=0;re char ch=0;
	while (!isdigit(ch)) w|=ch=='-',ch=getc();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getc();
	if (w) x=-x;
}

il void scan(ll &x)
{
	x=0;re int w=0;re char ch=0;
	while (!isdigit(ch)) w|=ch=='-',ch=getc();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getc();
	if (w) x=-x;
}
#endif
int f[15][15]={{0},{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1},{1,5,10,10,5,1},{1,6,15,20,15,6,1},{1,7,21,35,35,21,7,1},{1,8,28,56,70,56,28,8,1},{1,9,36,84,126,126,84,36,9,1},{1,10,45,120,210,252,210,120,45,10,1},{1,11,55,165,330,462,462,330,165,55,11,1}};
int n,sum;
int tmp[15];
bool book[15];
il void dfs(int x,int Sum)
{
	if (Sum>sum) return;
	if (x==n&&Sum==sum)
	{
		for (re int i=0;i<n;i++) cout << tmp[i]<<" ";
		putchar('\n');
		exit(0);
	}
	for (re int i=1;i<=n;i++)
	{
		if (book[i]) continue;
		tmp[x]=i;
		book[i]=1;
		dfs(x+1,Sum+f[n][x]*i);
		book[i]=0;
	}
}

int main()
{
	scan(n);scan(sum);
	dfs(0,0);
}
```

---

## 作者：Misaka19280 (赞：2)

（之前说排版乱没过，重排一遍又发了一次，希望能过）

这题用纯粹的爆搜你会发现你T掉了

然后就要用神奇的办法搞一搞

分析样例

```
3                 1                    2               4

                              ↓
 
            4（3+1）         3（1+2）            6（2+4）

                              ↓

                    7（3+1+1+2）  9（1+2+2+4）

                              ↓

                              16（3+1+1+1+1+2+2+2+4）


```

最后一层16是怎么得到的呢？


```
3*1+1*3+2*3+4*1
```

我们可以变为
1a+3b+3c+1d的形式

看一下每个字母的系数

分别为

1 3 3 1

有没有觉得熟悉

               1
             1   1
           1   2   1
         1   3   3   1
       1   4   6   4   1
       ↑还记得这个三角形吗
       
没错就是杨辉三角的第四层

说明各项系数就是杨辉三角形的各项位置（你还可以手玩一下，结果一样，很简单可以想出来）

就非常的简单了

先求出相应第n层的杨辉三角形

再搜索往里面带

就ok了

搜索的时候i:=1 to n

从小到大

所以不用考虑字典序的问题

by the way

一维求杨辉三角形的方法

```
	for i:=1 to n do
		begin
			a[1]:=1;
			a[i]:=1;
			if i mod 2=1 then
					a[i div 2+1]:=a[i div 2+1]+a[i div 2];
			for j:=i div 2 downto 1 do
				a[j]:=a[j]+a[j-1];
			for j:=i div 2+1 to i-1 do
				a[j]:=a[i-j+1];
		end;
```

（好像有个大佬@ plazum写过了Orz）

-----------------------------------------------------------
代码分割线


```
Var
	a:array[1..12]of longint;
	n,i,ans,j:longint;
	visited:array[1..12]of boolean;
	f:array[1..12]of longint;
	t:boolean;
	
Procedure print;
var
	i:longint;
begin
	for i:=1 to n do
		write(f[i],' ');
end;
	
Procedure dfs(k,sum:longint); //一个正常的搜索模板
var
	i:longint;
begin 
	if sum<0 then exit; //这里是个优化，如果当前的结果已经大于之前的sum了，那这条路径就可以去死了
	if t=false then exit;
	if k>n then //到达条件判断
		if sum=0 then 
			begin 
				print;
				t:=false;
			end;
	for i:=1 to n do
		if visited[i] then   //一个一个带入尝试，因为从小到大搜索，所以不用考虑字典序的问题
			begin
				visited[i]:=false; 
				f[k]:=i;
				dfs(k+1,sum-f[k]*a[k]); //搜索的数*系数
				visited[i]:=true;//回溯
			end;
end;
			
	
Begin
	read(n,ans);//ans是乱写的变量名
	fillchar(visited,sizeof(visited),true);
	t:=true;
	for i:=1 to n do
		begin
			a[1]:=1;
			a[i]:=1;
			if i mod 2=1 then
				a[i div 2+1]:=a[i div 2+1]+a[i div 2];//这里单独判了奇数的情况，中间那个数单独算
			for j:=i div 2 downto 1 do
				a[j]:=a[j]+a[j-1]; //从中间向两边更新没有影响
			for j:=i div 2+1 to i-1 do
				a[j]:=a[i-j+1];
		end;
	dfs(1,ans);
End.
```

---

## 作者：McGrady (赞：2)

看题解好像都没有我的一个优化啊

我无聊地查看了所有题解的用时，最快的好像80+/90+ms

我的只要30+ms

其他都一样：杨辉三角，用一维数组算的，枚举，加上当前和>sum就退出的剪枝。

不一样的在这里：由于杨辉三角每一行是左右对称的，所以将对称的两个位置上的数对调也是一组解，而题目要字典序最小的解，所以搜到后一半时候就可以利用前一半，从与它对称的位置的数+1开始搜。

这样快不少，虽然有解的时候只快一点儿，但无解的时候能省很多时间。

代码(pascal万岁)：

```cpp
program rrr(input,output);
var
  a,b:array[0..15]of longint;
  f:array[0..15]of boolean;
  i,j,n,sum,m:longint;
procedure dfs(k,s:longint);
var
  i:longint;
begin
   if s>sum then exit;
   if k=n+1 then
      begin
         if s=sum then
             begin
                for i:=1 to n do write(a[i],' ');
                close(input);close(output);
                halt;
             end;
         exit;
      end;
   if k<=m then
       begin
          for i:=1 to n do
             if not f[i] then
                begin
                   f[i]:=true;a[k]:=i;
                   dfs(k+1,s+i*b[k]);
                   f[i]:=false;
                end
       end
   else
       begin
          for i:=a[n-k+1]+1 to n do
             if not f[i] then
                begin
                   f[i]:=true;a[k]:=i;
                   dfs(k+1,s+i*b[k]);
                   f[i]:=false;
                end;
       end;
end;
begin
   assign(input,'r.in');assign(output,'r.out');reset(input);rewrite(output);
   readln(n,sum);
   b[1]:=1;
   for i:=2 to n do
       begin
          b[i]:=1;
          for j:=i-1 downto 2 do b[j]:=b[j]+b[j-1];
       end;
   fillchar(f,sizeof(f),false);
   m:=(n+1)>>1;
   dfs(1,0);
   close(input);close(output);
end.
```

---

## 作者：plazum (赞：2)

这里提供一个用一维数组算杨辉三角的方法……

```cpp

for(i=0;i<n;i++){
    yh[i]=1;
    for(j=i/2;j>0;j--)yh[j]=yh[i-j]=yh[j]+yh[j-1];
}

```

---

## 作者：RPChe_ (赞：2)

此题的思路还是很简单的，可以直接打印杨辉三角，然后使用dfs枚举，遇到第一个解就输出并终止。（dfs正序枚举可以保证第一个解的字典序最小）~~当然你也可以直接枚举全排列~~

dfs过程就近乎是一个模板，这里就不赘述了。但是，我看了题解之后却发现了一个问题——好像杨辉三角大部分使用二维存储。

## 这样，我就发现我打出了一个空间优化。

就是在双重循环的条件下使用一维数组存储杨辉三角，递推式很长，直接上代码吧——

```cpp
for(register int i=1;i<=m;i++)//外循环是层数
    {
        for(register int j=i*(i-1)/2+1;j<=i*(i-1)/2+i;j++)//内循环是当前这一层的个数
        {
            if(j==i*(i-1)/2+1||j==i*(i-1)/2+i)//如果在最边上，就赋值成一
            b[j]=1;
            else b[j]=b[(i-2)*(i-1)/2+j-i*(i-1)/2-1]+b[(i-2)*(i-1)/2+j-i*(i-1)/2];//如果不在边上就根据上一层递推出当前数（杨辉三角基本性质都知道吧）
        }
    }
```

于是乎，这样我们就把空间从二维优化到了一维，虽然因为此题数据小，二维根本不会爆掉，但有优化肯定是好事啊。（集思广益嘛）

最后，来抬上代码——

```cpp
#include<iostream>
#include<stdlib.h>
using namespace std;
int n,m,k,ans[100000],vis[10000];
short b[1234567],a[10000];
void dfs(int i,int s)
{
    if(i>n)
    {
        if(s==0)
        {
            for(int j=1;j<=n;j++)
            cout<<ans[j]<<" ";
            exit(0);//必须用stdlib.h头文件
        }
    } else {
        for(int j=1;j<=min(s/a[i],n);j++)//其实上界还可以优化到n和还放得下的最大值这两个数中的较小数
        {
            if(vis[j]==0)
            {
            	ans[i]=j;
        	    vis[j]=1;
         		dfs(i+1,s-j*a[i]);
         	    vis[j]=0;
            }
        }
    }
}
int main()
{
    cin>>n>>m;
    int j1=0;
    for(register int i=1;i<=n;i++)//打印杨辉三角
    {
        for(register int j=i*(i-1)/2+1;j<=i*(i-1)/2+i;j++)
        {
            if(j==i*(i-1)/2+1||j==i*(i-1)/2+i)
            b[j]=1;
            else b[j]=b[(i-2)*(i-1)/2+j-i*(i-1)/2-1]+b[(i-2)*(i-1)/2+j-i*(i-1)/2];
            if(i==n)//保存目标层数
            {
                j1++;
                a[j1]=b[j];
            }
        }
    }
    dfs(1,m);
}
```


---

## 作者：zhangyuxing (赞：2)

此题楼下各位DaoLao已把方法讲明

蒟蒻上[code/c++]



```cpp
#include<bits/stdc++.h>//c++万能库 
int flag,n,m,t,in[13],p[13],c[13];
using namespace std;  
void ch(int t)//print+标记  
{  
    int i;
    if(t==m)   
    {  
        flag=1;  
        for(i=1;i<=n;i++) printf("%d ",p[i]);  
        printf("\n");  
    }  
}
void so(int k)//search  
{  
    if(flag)return;//标记则return 
    if(t>m)return;//超过行数则return
    if(k>n)//if搜到则return+print  
    {  
        ch(t);  
        return;  
    } 
        int i; 
    for(i=1;i<=n;i++)  
    if(c[i])  
    {  
    c[i]=0;  
    t+=i*in[k];  
    p[k]=i;  
    so(k+1);//search  
    t-=i*in[k];c[i]=1;//归原位 
    }  
}  
int answer(int k,int i)//杨辉三角构造  
{  
    if(i<1||i>k)return 0;  
    if(k==1)return 1;  
    return answer(k-1,i)+answer(k-1,i-1);  
}  
int main()  
{  
    int i;
    scanf("%d%d",&n,&m);  
    for(i=1;i<=n;i++) c[i]=true;//cstring中memset同等作用
    for(i=1;i<=n;i++) 
        in[i]=answer(n,i);//使用answer函数 
    so(1);//搜索开始！ 
}
```

---

## 作者：sky_1 (赞：1)

首先杨辉三角形就不再说了，已经有老兄说明白了。

由于是第一次发题解可能有些说的不怎么清楚，但是老弟我贴了代码也写了一些注释，希望各位老兄见谅!

我是dfs解决的，首先要考虑字典序，比如先从1开始递归一共n层

最重要是怎么剪枝，我是这样来判断的


1. 定义两个数组，分别把倍数和还未选中的数字存起来排个序

用样例来演算，

第一层， 当前还没开始选的所以 t1数组有值 1,3,3,1 t2数组有值1,2,3,4分别排序（升序）算出区间值，最小值16， 最大值24

	int l = 0, r = 0;
    for(int i = 0, j = len-1; i < len; i++, j--)
    {
        l += t1[i] * t2[j];
        r += t1[i] * t2[i];
    }
    
如果当前sum值不再该区间就 return 了，

总之呢，简单来说
先选中i后， 算出除了选中的以外的最大最小值，看sum在不在这个区间内
，不在就return继续下一次循环，在的话则进行下一次递归
直接完整代码了
时间复杂度很低，最快n*n*logn 就是1234这样的例子 最慢 n*n*n*logn 就是4321这样的例子而n只有12所以根本不慌

    int times[13][13];
    int flag[13];
    int res[13];
    int n;

    void init(){
       for(int i = 1; i <= 12; i++){
            times[i][1] = 1;
            times[i][i] = 1;
       }
       for(int i = 3; i <= 12; i++){
            for(int j = 2; j < i; j++){
                times[i][j] = times[i-1][j-1] + times[i-1][j];
            }
       }
    }

	int dfs(int cur, int sum){

    if(cur == n+1) // 说明找到了直接return
        return 1;

    int t1[13];
    int t2[13];
    int len = n - cur + 1; // 当前元素个数

    for(int i = cur, j = 0; i <= n; i++) // 杨辉三角形的值
        t1[j++] = times[n][i];
    for(int i = 1, j = 0; i <= n; i++) // 还未选中的值
        if(!flag[i])
            t2[j++] = i;
    sort(t1, t1 + len); // 排序
    sort(t2, t2 + len);

    int l = 0, r = 0;
    for(int i = 0, j = len-1; i < len; i++, j--){
        l += t1[i] * t2[j]; // 存最小值
        r += t1[i] * t2[i]; // 存最大值
    }

    if(sum < l || sum > r) // 剪枝，不在区间的值就没必要进行下去了
        return 0;

    for(int i = 1; i <= n; i++){
        if(!flag[i]){ // 进行选值
            flag[i] = 1; 
            res[cur] = i; // 存选中的值
            if(dfs(cur+1, sum - i*times[n][cur] )) // 进行下一次递归， sum值一定要减去选中的值
                return 1; // 如果if语句成立就不需要继续找了，直接返回，因为我是从最小的值开始递归的，后面满足条件的字典序都比它大
            flag[i] = 0; // 回溯
        }
    }

    return 0;
  	}

  	int main(){
      int sum;
      in(n, sum); // 这个函数是我封装了的，不需要在意
      init();
      if(dfs(1, sum)) // return 1 说明找到了该输出了
          out(n, res+1); // 这个函数是我封装了的，不需要在意

  	}





---

## 作者：wanxiang_zx (赞：1)

```
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
const int maxn=1000;
int n,sum;
int a[maxn][maxn];
int b[maxn];
bool v[maxn];
void pri()
{
     for(int i=1;i<=n;i++)
       cout<<b[i]<<" ";
     cout<<endl;
     //只输出第一种解，就是最优解 
     exit(0);
}
void dfs(int x,int s)
{
     //表示当前正在处理第x个位置，之前所有累加和为s 
     if(x>n && s==sum)
       pri();
     for(int i=1;i<=n;i++)
     {
       //列举从1到n每一个数字 
       if(a[n][x]*i+s>sum)
         return;
       //v数组表示每一个数字是否出现过
       //出现过标记为true 
       if(v[i])
         continue;
       v[i]=true;
       b[x]=i;
       //b数组记录答案每一个位置填的是数字几 
       dfs(x+1,s+a[n][x]*i);
       v[i]=false;
     }
}
int main()
{
    /*
    列举每一个n，发现n个数字每个数字的使用次数为杨辉三角第n层的数字
    1
    1 1
    1 2 1
    1 3 3 1
    1 4 6 4 1
    1 5 10 10 5 1
    如n==1时，最后得到的数字和为1×1； 
    */
    scanf("%d%d",&n,&sum);
    a[1][1]=1;
    for(int i=2;i<=n;i++)
      for(int j=1;j<=i;j++)
        a[i][j]=a[i-1][j]+a[i-1][j-1];
    //求出杨辉三角前n层 
    dfs(1,0);
    system("pause");
    return 0;
}

```
```
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
const int maxn=1000;
int n,sum;
int a[maxn][maxn];
int b[maxn];
bool v[maxn];
void pri()
{
     for(int i=1;i<=n;i++)
       cout<<b[i]<<" ";
     cout<<endl;
     exit(0);
}
void dfs(int x,int s)
{
     //表示当前正在处理第x个位置，之前所有累加和为s 
     if(x>n && s==sum)
       pri();
     for(int i=1;i<=n;i++)
     {
       //列举从1到n每一个数字 
       if(a[n][x]*i+s>sum)
         return;
       //v数组表示每一个数字是否出现过
       //出现过标记为true 
       if(v[i])
         continue;
       v[i]=true;
       b[x]=i;
       //b数组记录答案每一个位置填的是数字几 
       dfs(x+1,s+a[n][x]*i);
       v[i]=false;
     }
}
int main()
{
    /*
    列举每一个n，发现n个数字每个数字的使用次数为杨辉三角第n层的数字
    1
    1 1
    1 2 1
    1 3 3 1
    1 4 6 4 1
    1 5 10 10 5 1
    如n==1时，最后得到的数字和为1×1； 
    */
    scanf("%d%d",&n,&sum);
    a[1][1]=1;
    for(int i=2;i<=n;i++)
      for(int j=1;j<=i;j++)
        a[i][j]=a[i-1][j]+a[i-1][j-1];
    //求出杨辉三角前n层 
    dfs(1,0);
    system("pause");
    return 0;
}

```


---

## 作者：forest_lja (赞：1)

~~（我被这题目坑的好惨）~~

咳咳，首先非常明显的一个杨辉三角大家应该都可以看出来，楼上有一群大佬讲过我也就不多说了。

（~~看到数字三角不应该第一个想到杨辉么？）~~

实际上我第一次看到这题的时候手推一遍答案是1119来着。所以说要好好看题啊，这种排列个叫（~~叫什么来着？~~），题目要求的是全排列，这意味着第一行N以内的整数必须全部出现且仅有一次出现。

废话不多说了（~~好像已经说了很多废话~~）我本人本来学的是pascal,由于举办方将残忍的废除pascal的参赛资格我才不得不转C++，所以我的代码几乎没有做过压缩（~~不然我自己都看不懂~~），所以我相信你们是可以看得懂代码和注释的,

（~~代码好丑~~）

```cpp
#include<bits/stdc++.h> 
using std::cin;
using std::cout;
using std::endl;
int a[15][15],num[15],n,m;//a数组存放杨辉三角，num放原始数据
bool b[15]={false};//b数组用于判断数字是否已经用过
void work(int dep,int sum)
{
	if (sum>m) return; //这里有一个小剪枝，作用不是太大，聊胜于无，去了也能AC
	if (dep>n&&sum==m){
		cout<<num[1];
		for (int j=2;j<=n;j++)
	    	cout<<' '<<num[j];//由于是DFS，第一个一定是最小的，直接输出推出就好了
	    cout<<endl;
	    exit(0);
	}
	else {
		for (int i=1;i<=n;i++)
		{
			if (b[i]==false){
				b[i]=true;
				num[dep]=i;
				work(dep+1,sum+a[n][dep]*i);//后面那个是计算结果
				b[i]=false;//要记得重置，不然会出问题
			}
		}
    }
 } 
int main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++) 
	{
		a[i][1]=1;
		a[i][i]=1;
	}
	for (int i=3;i<=n;i++)
		for (int j=2;j<=i-1;j++)
		{
			a[i][j]=a[i-1][j]+a[i-1][j-1];
		}//上面全部在构建杨辉三角
	work(1,0);
	return 0;
}
```
好多巨佬在构建杨辉的时候都好有想法，我这个蒟蒻嫌麻烦（~~其实是不会~~）就写了一个水水的杨辉糊弄一下拉。

orz

第一次发题解，不喜勿喷。

---

## 作者：RayI_ovo (赞：1)

这个题属于dfs的加强训练的题，所以dfs的基础说明就不做了

通过观察总结出对1到N排列后，和杨辉三角系数加权求和与sum相同即为正解

考虑到杨辉三角系数的中央对对称性，也就是第一个系数和最后一个系数相同，第二个和倒数第二个相同，如果一个排列的结果能够满足要求，那么把排列的数据按照系数相同的规则调换也必然是正解。

题目要求的是满足条件的多个解按照字典排序输出最小的，也就是dfs当中生成的系数都是从1到N，从前到后到话，第一个满足条件的排列就是所需，直接输出就可以了。

此外还可以优化的时候，在dfs深搜的过程当中同时记录加权和，如果超过了sum直接pass掉就好了

此外，在判断排列中是否已经使用了某个数字的时候，可以利用位运算，全局做一个flag变量来记录哪些位还可以选择就可以了

上述条件达到了，代码其实可以很简短

```
#include <iostream>
#include <cstring>
using namespace std;
#define MAXN 12
int N, sum;
int c[MAXN]; // 系数
int v[MAXN]; // 排列结果
unsigned int flag = 0xFFFF; // 默认全部可用
unsigned int BITS[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, }; // 标志位数组
int tempSum=0; //深搜过程中的临时加权和
int bFound = 0;// 用来找到正解后安全返回
void dfs(int nPos){
    if ( nPos == N ) {
        if ( tempSum == sum ) {
            for (int i=0; i<N; i++) cout << v[i] << " ";
            bFound = 1;//找到了
        };
    } else {
        for (int i = 1; i<=N; i++ ) {
            if (0 == (BITS[i]&flag) )     continue;
            if ( tempSum + i*c[nPos] > sum ) continue;
            tempSum += i*c[nPos];
            v[nPos] = i;
            flag &= ~BITS[i];
            dfs(nPos+1);
            if (bFound) break;
            flag    |= BITS[i];
            tempSum -= i*c[nPos];
        };
    };
};
int main() {
    cin >> N >> sum;
    c[0] = 1;
    for ( int i=1; i<N; i++ ) {
        c[i] = c[i-1] * (N-i)/i;
    };
    dfs(0);
    return 0;
}
```

---

## 作者：孤_独 (赞：1)

```cpp

因为n<=12，可以把杨辉三角存起来：

很容易发现这题与杨辉三角有关。
拿样例举例：
样例答案：	3   1   2   4
使用次数：	1	3	3	1   


因为n<=12，可以把杨辉三角存起来
```
源代码如下：
```cpp
#include <iostream>
using namespace std;
const int a[14][14]={		//杨辉三角
				{0},
				{0,1},
				{0,1,1},
				{0,1,2,1},
				{0,1,3,3,1},
				{0,1,4,6,4,1},
				{0,1,5,10,10,5,1},
				{0,1,6,15,20,15,6,1},
				{0,1,7,21,35,35,21,7,1},
				{0,1,8,28,56,70,56,28,8,1},
				{0,1,9,36,84,126,126,84,36,9,1},
				{0,1,10,45,120,210,252,210,120,45,10,1},
				{0,1,11,55,165,330,462,462,330,165,55,11,1},
				{0,1,12,66,220,495,792,924,792,495,220,66,12,1}
};
int ans[15];		
int book[15];
bool flag=0;
int n,k;
void dfs(int i,int sum)			//枚举
{
	if(flag==1)		//已有答案，停程序
		return;
	else if(sum>k)		//超过重来
		return;
	else if(i==n+1 && sum==k)	//输出答案
	{
		for(int j=1;j<=n;j++)
		{
			cout<<ans[j]<<" ";
		}
		cout<<'\n';
		flag=1;
		return;
	}
	else
	{
		for(int j=1;j<=n;j++)
        //从一开始，第一个就是字典序最小的
		{
			if(book[j]==0)
			{
				ans[i]=j;
				book[j]=1;
				dfs(i+1,sum+j*a[n][i]);	计算下一步
				book[j]=0;
			}
		}
	}
}
int main()
{
	cin>>n>>k;	//输入
	dfs(1,0);	//枚举
	return 0;
}

```

---

## 作者：bztMinamoto (赞：1)

//发现题解里都是杨辉三角，但我压根不知道是啥玩意儿……可能我naive吧

```cpp
//不过反正能做出来就是好方法
//可以发现，在一个规定为n的数组里，num可以看做数组元素乘特定个数，如a~g，总和就等于x1a+x2b+……+xng
//不需要去算出每个x是多少，模拟就好了，算的话会哭出来的
//注解已经到了啰嗦的地步自己看
#include<bits/stdc++.h>//万能头文件
using namespace std;
string s[12];//模拟用
int a[12],c[12];//a模拟用，c用来存搜索结果
bool d[12];//搜索时查数字是否用过
int n,m;
bool f=0;//只需要输出一个结果，那么有解就不用进行了
void ab()
{
    for(int i=n-1;i>0;i--)
    for(int j=0;j<i;j++)
    s[j]+=s[j+1];
        //模拟三角形相加的过程
        //如果把数组中所有数字看为字母，最后的结果就是一个多项式
    for(int i=0;i<s[0].size();i++)
    a[s[0][i]-'a']++;
        //多项式中出现过的每个字母代表第几位数字，出现次数等于要乘几
}
void dfs(int x,int ans1)
{
        //x存搜索第几位，ans1存当前总和
    if(ans1>m||f) return;
        //如果和大于num或已经有答案，退出
    if(x==n&&ans1==m) {for(int i=0;i<n-1;i++) printf("%d ",c[i]);printf("%d",c[n-1]);f=1;return;}
        //输出答案不多说，顺便f变为true
    for(int i=0;i<n;i++)
    {if(!f&&!d[i])
    {d[i]=1;
    c[x]=i+1;
    dfs(x+1,ans1+(c[x]*a[x]));
        //数没用过就搜索（ps：这是将n个数排序，每个数只能出现一次）
        //毕竟c++数组从0到n-1，存储数字要+1s，不是，+1
        //当前总和是搜索的数加那一位应该乘几
    d[i]=0;
        }
        }
    return;
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(d,0,d[n]);
    for(int i=0;i<n;i++)
    s[i]+=(i+'a');//将1~n设为a~a+n
    ab();
    dfs(0,0);
    return 0;
}
```

---

## 作者：LCGLG (赞：1)

```cpp
#include<cstdio>
using namespace std;
int i,n,sum,flag=false,_xishu[13]={0},_ans[13]={0},_book[13]={0};
inline int _get(int s,int t,int n){
    return s*(n-t+1)/(t-1);//利用杨辉三角第n行第t个元素为C(t-1,n-1)得，下一元素与上一元素之比为(t-1)/(n-t+1)，故利用上一个元素s即可求得下一元素。 
}
inline void _printf(){
    flag=true;//因为只需输出字典序最小的一组数据，故得到答案之后即可跳出深搜。 
    for(i=1;i<=n;++i) printf("%d ",_ans[i]);
}
inline int _dfs(int step,int count){
    if(count==sum && step>n) _printf();//满足条件时输出。 
    if(step>n) return 0;
    if(count>sum) return 0;
    for(int i=1;i<=n;++i){
        if(_book[i]) continue;//标记数字是否使用过 
        _ans[step]=i;
        _book[i]=true;
        _dfs(step+1,count+i*_xishu[step]);
        if(flag) return 0;//判断是否得出答案，是则递归返回。 
        _ans[step]=0;
        _book[i]=false;
    }
}
int main(){
    scanf("%d%d",&n,&sum);
    _xishu[1]=_xishu[n]=1;
    for(i=2;i<=n/2+1;++i){//此处由于杨辉三角的对称性，故循环最少只需进行n/2+1次 ，另半边镜像同时赋值。 
        _xishu[i]=_get(_xishu[i-1],i,n);
        _xishu[n-i+1]=_xishu[i];//推理可得sum等于_ans[i]*该元素对应杨辉三角数值之和{i|1~n} 。 
    }
    _dfs(1,0);
    return 0;
}
```

---

## 作者：天狗的手帖 (赞：1)

直接搜索的思路大家都能想到，这里就不赘述了，但这样会TLE

我们发现，排列A中每一个元素对答案的贡献都是不变的（其实能发现是一个杨辉三角），所以我们并不需要完全搜索出一个全排列之后再去验证，而是在搜索每个元素时就能得出当前答案了，如果发现当前答案已经大于实际答案就剪枝


具体见代码（由于一开始没有想到剪枝方法，改来改去写的很丑陋。。）

```cpp

int n,m,tmp;  
int Index[13];  
int p[13];  
bool FLAG;  
bool c[13];  
  
using namespace std;  
  
void check(int tmp)  
{  
    if (tmp==m)   
    {  
        FLAG=true;  
        for (int i=1;i<=n;i++) printf("%d ",p[i]);  
        printf("\n");  
    }  
}  
  
void solve(int k)  
{  
    if (FLAG) return;  
    if (tmp>m) return;  
    if (k>n)  
    {  
        check(tmp);  
        return;  
    }  
    for (int i=1;i<=n;i++)  
        if (c[i])  
        {  
            c[i]=false;  
            tmp+=i*Index[k];  
            p[k]=i;  
            solve(k+1);  
            tmp-=i*Index[k];  
            c[i]=true;  
        }  
}  
  
int Ansersfill(int k,int i)  
{  
    if (i<1 or i>k) return 0;  
    if (k==1) return 1;  
    return Ansersfill(k-1,i)+Ansersfill(k-1,i-1);  
}  
int main()  
{  
    scanf("%d%d",&n,&m);  
      
    for (int i=1;i<=n;i++) c[i]=true;  
    for (int i=1;i<=n;i++) Index[i]=Ansersfill(n,i);   
    tmp=0;  
    solve(1);  
}  

```

---

## 作者：汇文客 (赞：1)

sum=∑ Yni\*Ai，Yn代表第n层杨辉三角数，Ai为相应排列。证明可以自己推导。利用这个，可以大大节省搜索时间。

```delphi

var y:array[1..12,1..12]of longint;
    a:array[1..12]of longint;
    v:array[1..12]of boolean;
    n,sum,m:longint;
procedure init;
var i,j:longint;
begin
  readln(n,sum);
  for i:=1 to n do y[i,1]:=1;
  for i:=2 to n do
  for j:=2 to i do
  y[i,j]:=y[i-1,j]+y[i-1,j-1];
  m:=0;
  fillchar(v,sizeof(v),true);
  fillchar(a,sizeof(a),0);
end;

procedure dfs(i:longint);
var j:longint;
begin
  if m>sum then exit;
  if i=n+1 then
  begin
    if sum=m then
    begin
      for j:=1 to n do write(a[j],' ');
      writeln;halt;
    end;
    exit;
  end;
  for j:=1 to n do
  if v[j] then
  begin
    a[i]:=j;
    m:=m+y[n,i]*j;
    v[j]:=false;
    dfs(i+1);
    a[i]:=0;
    m:=m-y[n,i]*j;
    v[j]:=true;
  end;
end;

begin
  init;
  dfs(1);
end.

```

---

## 作者：AKB48 (赞：1)

观察后可以发现，其实该倒三角对应着杨辉三角，第N层相应位置的数值相乘之和就是SUM。于是先预处理杨辉三角，再按字典序从小到大进行深搜，找到的第一个符合的便退出输出。如果这样还不够，还会超时，必须加入优化。每一层都计算当前的和，当当前和已经超过目前最小值，说明再搜索已经无用了，提前exit;


---

## 作者：oisdoaiu (赞：1)

~~这道题做了好久，可能是我优化太过了~~  

其实这道题题意挺简单的，枚举每一种排列，照题意模拟即可（~~数据范围那么小肯定是暴力~~）  

# $BUT$！

算算复杂度，全排列($DFS$)$n!$，模拟判断$n^2$，还是优化一下吧~~（优化又不会更慢）~~  
### 首先判断肯定是可以优化的

具体的方案就是
——推出公式，一步到位。  这样就省去了模拟的步骤（$O(n^2)->O(n)$）  严谨的证明本蒟蒻当然不会，所以就直接举几个例子，找找规律就好了。  

$n=2$的时候  
$(x,y)$->$(x+y)$  


$n=3$的时候
$(x,y,z)$->$(x+y,y+z)$-$(x+2y+z)$  

...

把各项系数提出来:  
$1$ $1$  
$1$ $2$ $1$  
$1$ $3$ $3$ $1$
...

#### 这不就是杨辉三角吗
结合通项公式得到：$a_i$（下标从$1$开始）的系数就是$C_{n-1}^{i-1}$

于是就可以得到$O(n)$求模拟结果的公式：

$$ans=\sum_{i=1}^n C_{n-1}^{i-1}\cdot a_i$$

### ~~反正没事干，~~继续优化（其实优化以后细节非常多，尽量理解，实在不理解就请略过吧，免得绕晕了脑子）

根据组合的特点——$C_n^i=C_n^{n-i}$
我们可以进一步地将公式变形（这里需要分类讨论）（默认为自动向下取整）

$n$为偶数时  
$$ans=\sum_{i=1}^{\frac{n}{2}}C_{n-1}^{i-1}\cdot (a_i +a_{n-i+1})$$

$n$为奇数时$ans$要比偶数情况多一点：
$$ans+=C_{n-1}^{\frac{n-1}{2}+1}\cdot a_{\frac{n-1}{2}+1}$$

其实这两个公式很好理解，就是一个合并同类项的过程（因为系数相同嘛），把$a$中的元素进行两两配对，让这两个元素的下标之和为$n$，然后奇数的情况就把中间项单独拿出来  
### 没错，还能进行各种各样的优化
- 我们可以把求全排列的$DFS$的顺序变一下，即一前一后（第奇数个为‘前’，第偶数个为‘后’），这样就能配合上面的公式使用（具体的配合方法**见下一段**）  
- 刚才那个式子优化前后好像没啥区别，但我们可以发现当按上面的方案配对后的数对$(x,y)$中的元素确定时，**$x$，$y$的顺序时可以交换**，所以在枚举数对中后一个元素的时候，**保证它比前一个元素大**，就可以去掉一半的情况
- 因为求$ans$只需知道每对数字的和，所以预处理出$1$~$n$的和，最后剩下 $2$个（$n$为偶数）$/$ $1$个（$n$为奇数）时，直接用$O(1)$求出剩下的数对和$/$数，判断一下即可（又省去了几次$DFS$）

- 这里其实还有一个**小优化**，选第奇数个数时（即‘前’），$i$从$1$到$n$枚举；反之则从$n$到$1$枚举，这样找到一个答案就可以输出了，具体的证明大家可以试试

### 剩下的一系列剪枝就不过多赘述了，直接上代码（细节超多有木有）
```
#include<bits/stdc++.h>
using namespace std;

int n, sum, ssum;
int order[15], visit[15];   //不用bool是为了方便调试 
int C[15];
bool tr;               //输出后直接终止每一层DFS(小剪枝) 

inline void Dfs(int s, int step, int num_sum){
	if(s > sum) return;  //小剪枝 
	
	//第奇数次取数 
	if(step%2){
		if(step == n){
			int temp = ssum - num_sum;   //O(1)求剩下的那个数字 
			if(s + C[step/2]*temp == sum){
				for(int i=1;i<=step/2;i++){ 
					printf("%d ", order[i]);
				}
				printf("%d ", temp);
				for(int i=step/2+1; i<step; i++){
					printf("%d ", order[i]);
				}
				tr = 1;
			}
			return;
		}
		for(int i=1;i<=n;i++){               //正向枚举 
	 		if(!visit[i]){ //没取过 
	 			order[step/2+1] = i;
			 	visit[i] = 1;
			 	Dfs(s+C[step/2]*i, step+1, num_sum+i);
			 	 if(tr) return;                //终止DFS 
				visit[i] = 0;
		 		order[step/2+1] = 0;
		 	}
		}
	}
	
	//第偶数次取数 
	else{
		for(int i=n; i>order[step/2]; i--){     //逆序枚举，同时大于上一项(小剪枝） 
			if(!visit[i]){  //没取过
				order[2*((n-1)/2)-step/2+1] = i;
				visit[i] = 1;
				num_sum+=i, s+=C[step/2-1]*i;   //更新操作单独提出，方便判断
												//还要注意对应的回溯操作 
				if(step == n-2){
					int temp = ssum - num_sum;
					if(s + C[step/2]*temp == sum){
						for(int i=1;i<=step/2;i++){
							printf("%d ", order[i]);
						}
						for(int i=1;i<=n;i++){
							(!(visit[i])) && printf("%d ", i);
						}
						for(int i=step/2+1; i<=step; i++){
							printf("%d ", order[i]);
						}
						tr = 1;
						return;
					}
					visit[i] = 0;
					num_sum-=i;
					s-=C[step/2-1]*i;
					order[2*((n-1)/2)-step/2+1] = 0;
					continue;              //这里不是return,还要选下一个数 
				}
				Dfs(s, step+1, num_sum);
				 if(tr) return;   //终止DFS 
				visit[i] = 0;
				num_sum-=i;
				s-=C[step/2-1]*i;
				order[2*((n-1)/2)-step/2+1] = 0;
			}
		}
	} 
}

int main(){
	freopen("test.in", "r", stdin);      //为什么不屏蔽？你懂的 
	scanf("%d%d", &n, &sum);
	C[0] = 1;
	for(int i=1; i<=n; i++) C[i] = C[i-1] * (n-i) / i, ssum+=i; //预处理C数组 
	Dfs(0, 1, 0);
	return 0;
}
```
结果：$158ms$ $/$ $924KB$

---

