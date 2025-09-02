# [GCPC 2023] DnD Dice

## 题目描述

在 *Dungeons & Dragons*（DnD）以及许多其他角色扮演游戏中，许多行动都由掷骰子决定，而且通常会使用不同面数的骰子。最常见的骰子基于五种柏拉图立体：四面体、立方体、八面体、十二面体和二十面体，分别有 $4$、$6$、$8$、$12$ 和 $20$ 个面。在 DnD 的术语中，这些骰子通常被称为 d4、d6、d8、d12 和 d20。

![](https://cdn.luogu.com.cn/upload/image_hosting/flvm7fum.png)

:::align{center}
五种标准骰子，[Ramona Trusheim](https://commons.wikimedia.org/wiki/File:Spielw%C3%BCrfel_(als_Modelle_Platonischer_K%C3%B6rper_und_Trapezoeder).jpg)
:::

作为一名地下城主，你正在为你的玩家小队设计一个冒险。在这个冒险的最终战斗中，玩家需要掷出多种不同面数的骰子的组合，敌人的行动由掷出的所有骰子的点数之和决定。为了平衡游戏，你希望根据这些和出现的概率对它们进行排序，以便为每个和分配合适的事件。

给定每种类型骰子的数量，并假设每个骰子的面从 $1$ 编号到其最大面数，找出所有可能的掷骰子点数之和，并按概率从高到低输出。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 1 1 0 0```

### 输出

```
11 10 9 12 8 13 14 7 15 6 5 16 17 4 18 3```

## 样例 #2

### 输入

```
2 0 0 1 0```

### 输出

```
9 14 12 11 10 13 15 8 16 7 6 17 5 18 4 19 3 20```

## 样例 #3

### 输入

```
0 0 0 0 1```

### 输出

```
10 3 9 8 14 13 11 7 6 12 20 4 15 5 16 1 2 19 17 18```

# 题解

## 作者：Phantom_HY (赞：1)

### 题意
有 $5$ 种骰子，分别有 $4,6,8,12,20$ 面。每种骰子各有 $a,b,c,d,e$ 个，**所有**骰子都要投出。

题目要求把所有可出现的点数按可能性**从大到小**输出，可能性相同时**顺序不做要求**。

### 思考分析
蒟蒻最开始没想法先写了个暴力，发现奇妙的事情。

##### 输入
```
1 1 0 0 0
```
##### 输出
左边是数值，右边是次数。
```
2 1
3 2
4 3
5 4
6 4
7 4
8 3
9 2
10 1
```
我们瞪一眼，不难发现前后是对称的。

~~正常做题时，我们发现这个结论就可以直接套用结论写代码就可以了~~。

### 证明
> 设 $cnt_i$ 表示 $i$ 出现的次数，$MIN$ 表示最小值，$MAX$ 表示最大值。
> 
> 设 $cnt_{MIN + a},cnt_{MAX - a}$，证明 $cnt_{MIN + a} = cnt_{MAX - a}$ 就能够证明我们的结论。
>
>  $cnt_{MIN + a}$ 和 $cnt_{MAX - a}$ 通过 $cnt_{MIN + a - 1}$ 和 $cnt_{MAX - a + 1}$ 的基础上调整一个点数而来，问题就可以变为证明 $cnt_{MIN + a - 1} = cnt_{MAX - a + 1}$。
>
>  类推出来就可以通过证明 $cnt_{MIN + a - a} = cnt_{MAX - a + a}$ 即证明 $cnt_{MIN} = cnt_{MAX}$ 得出结论。
>
>  因为最小值和最大值出现次数只有一次，所以 $cnt_{MIN} = cnt_{MAX} = 1$，结论得证。

### 代码实现
实现方法比较简单，算出最大值和最小值从两头开始取然后存入新的数组，最后输出即可。

需要注意的地方有最大值与最小值中间的数可能重复加入或者少加入，需要特判。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e;
int ans[505],l;
int main()
{
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
	int MIN,MAX;
	MIN = a + b + c + d + e;
	MAX = 4 * a + 6 * b + 8 * c + 12 * d + 20 * e;
	while(MIN < MAX)
	{
		ans[++l] = MIN,ans[++l] = MAX;
		MIN++;
		MAX--;
	}
	if (MIN == MAX)//判断中间是否剩下的
		ans[++l] = MIN;
	while(l)//存的时候是倒着存的，这里倒着输出
		printf("%d ",ans[l--]);
	return 0;
}
```

---

## 作者：ycy25 (赞：1)

## First
直接解决此问题显然比较困难，所以我们可以从只有一个骰子的情况开始讨论。  
当只有一个立方体时，显然只有 $1,2,...,6$ 是可能出现的值，概率都是 $\frac{1}{6}$。我们再加一个四面体，此时可能出现的值有 $2,3,...,10$，这时哪些值出现概率更高呢？我们来列个表格：  
|   | 1  | 2  | 3  | 4  | 5  | 6  |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 1  | 2  | 3  | 4  | 5  | 6  | 7  |
| 2  | 3  | 4  | 5  | 6  | 7  | 8  |
| 3  | 4  | 5  | 6  | 7  | 8  | 9  |
| 4  | 5  | 6  | 7  | 8  | 9  | 10  |

其中第一行指立方体掷出的点数，第一列指四面体掷出的点数。可以直观地看出，$4、5、6、7$ 出现概率最高，$3、8$ 次之，$2、9$ 更次，$1、10$ 最低。  
像这样枚举每个骰子的每个面的方法很容易想到，可当每种骰子都有十个的话，**程序要进行 $4^{10}\times 6^{10}\times 8^{10}\times 12^{10} \times 20^{10}$ 次运算**，而仅仅 $20^{10}$ 便超过了 $10^{13}$，显然会 TLE，我们需要更加高效的算法。
### Second
我们仍然从骰子数较少的情况开始求出问题的答案。假设一共有 $n$ 个骰子，我们可以先考虑前 $n-1$ 个骰子。设 $p_i$ 表示前 $n-1$ 个骰子掷出的点数为 $i$ 的概率，最后一个骰子是 $k$ 面体，则**最终掷出的点数为 $s$ 的概率为 $\displaystyle \sum_{i=1}^k\frac{p_{s-i}}{k}$**，因为若最后一个骰子掷出了 $a$（$1\le a\le k$）点，则前 $n-1$ 个骰子掷出的点数必然为 $s-a$，而最后一个骰子仅有 $\frac{1}{k}$ 的概率掷出 $a$ 点，因此**最后一个骰子掷出 $a$ 点时总点数和为 $s$ 的概率为 $\displaystyle\frac{p_{s-a}}{k}$**，而 $a$ 的取值范围为 $1\le a\le k$，所以总概率即为 $\sum_{i=1}^k\frac{p_{s-i}}{k}$。  
知道了这些，我们就可以愉快地 AC 啦~~~
### Third
AC代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
struct JGT
{
    double p;//表示概率
    int s;//表示点数和
}ans[501];//存储答案
bool pd(JGT a,JGT b)
{
	return a.p>b.p;//比较函数，按概率从大到小
}
double dp[501],now[501];//dp数组表示当前掷出各个点数的概率，now存储中间数据
int main()
{
    int t,c,o,d,i;
    scanf("%d%d%d%d%d",&t,&c,&o,&d,&i);
    int di[]={4,6,8,12,20},num[]={t,c,o,d,i};//方便处理
    int min=t+c+o+d+i,max=4*t+6*c+8*o+12*d+20*i;//显然，可能掷出的最小值为骰子总数，最大值为各个骰子面数之和
    int nowmax=0;//已经考虑的骰子的面数之和
    dp[0]=1.0;//没有骰子时掷出0点的概率为1.0
    for(int i=0;i<5;i++)//处理每种骰子
	{
        int face=di[i],cnt=num[i];
        for(int j=0;j<cnt;j++)//处理每个骰子
		{
            memset(now,0,sizeof(now));//清空now数组
            for(int k=0;k<=nowmax;k++)
			{
                if(dp[k]==0)continue;
                double p=dp[k]/face;
                for(int f=1;f<=face;f++)now[k+f]+=p;//更新点数和为k+f时的概率
            }
            nowmax+=face;
            memcpy(dp,now,sizeof(dp));//更新dp数组
        }
    }
    for(int s=min;s<=max;s++)//方便排序
	{
        ans[s].p=dp[s];
        ans[s].s=s;
    }
    std::sort(ans+min,ans+max+1,pd);//排序
    for(int i=min;i<=max;i++)printf("%d ",ans[i].s);//输出
    return 0;//好习惯
}
```
[AC记录](https://www.luogu.com.cn/record/230860222)

---

## 作者：guoshengyu1231 (赞：1)

# 题意翻译&简述
有五种骰子，分别有 $4$，$6$，$8$，$12$，$20$ 面。给定每种骰子的数量，算出投掷多个不同类型的骰子，所有可能出现的点数之和，并按概率降序排序。
# 思路
首先分析问题，我们需要计算所有骰子的点数之和的概率分布。很明显，当前状态可以由之前的状态转移而来，所以考虑动态规划。$\\$
既然是动态规划，那三要素可不能少。
## 状态
设 $dp_i$ 表示投掷出点数为 $i$ 的概率。
## 边界
很明显，和为 $0$ 的概率为 $1$（尚未投掷任何骰子），故 $dp_0=1.0$。
## 转移
这里我们先设 $d_i$ 为第 $i$ 个骰子的面数，那么枚举 $k\le d_i$，那么 $dp_{sum+k}$ 一定可以由 $dp_{sum}$ 转移而来。具体的，每次遍历一个骰子，我们都需要更新一次 $dp$ 数组，对于每一次更新，设更新后的 $dp$ 数组为 $new_{dp}$。则先遍历 $(sum,p)\in dp$，其中 $p$ 是对应的概率，再枚举 $k\le d_i$，那么 ${new_{dp}}_{sum+k} \leftarrow {new_{dp}}_{sum+k}+\frac{p}{d_i}$。每次最外层的循环的最后，再让 $dp\leftarrow new_{dp}$ 就可以啦。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,double> P;
int s1,s2,s3,s4,s5,d[100],tot;
bool cmp(P a,P b)
{
	return a.second>b.second;
}
int main()
{
	cin>>s1>>s2>>s3>>s4>>s5;
	while(s1--) d[++tot]=4;
	while(s2--) d[++tot]=6;
	while(s3--) d[++tot]=8;
	while(s4--) d[++tot]=12;
	while(s5--) d[++tot]=20;//存储所有骰子的面数
	map<int,double> dp;dp[0]=1.0;//dp 初始化
	for(int i=1;i<=tot;i++)//枚举所有骰子
	 {
	 	map<int,double> new_dp;//新dp数组
	 	for(auto& [sum,p]:dp)//遍历dp数组
	 	 for(int k=1;k<=d[i];k++) new_dp[sum+k]+=p/d[i];//状态转移
	 	dp=new_dp;//更新dp数组
	 }
	vector<P> ans(dp.begin(),dp.end());
	sort(ans.begin(),ans.end(),cmp);//所有可能出现的点数之和按概率降序排序。
	for(P x:ans) cout<<x.first<<' ';//最后输出即可。
	return 0;
}
```

---

## 作者：WeWantToRun (赞：0)

作为一道 ICPC 题，我们需要充分发扬遇到困难写 python 的精神。

显然我们可以直接设一个 dp，$dp_i$ 表示 $i$ 这个数可以凑出来的方案数。最后排序就可以了。

于是直接暴力转移即可。

```py
a,b,c,d,e= map(int, input().split())

f = []
g = []

for i in range(1000):
	f.append(0)
	g.append(0)

f[0]=1
for i in range(a):
	for k in range(600):
		for j in range(1,5):
			g[k+j]=g[k+j]+f[k]
	for k in range(600):
		f[k]=g[k]
		g[k]=0
for i in range(b):
	for k in range(600):
		for j in range(1,7):
			g[k+j]=g[k+j]+f[k]
	for k in range(600):
		f[k]=g[k]
		g[k]=0
for i in range(c):
	for k in range(600):
		for j in range(1,9):
			g[k+j]=g[k+j]+f[k]
	for k in range(600):
		f[k]=g[k]
		g[k]=0
for i in range(d):
	for k in range(600):
		for j in range(1,13):
			g[k+j]=g[k+j]+f[k]
	for k in range(600):
		f[k]=g[k]
		g[k]=0
for i in range(e):
	for k in range(600):
		for j in range(1,21):
			g[k+j]=g[k+j]+f[k]
	for k in range(600):
		f[k]=g[k]
		g[k]=0
for i in range(600):
	g[i]=i

for i in range(600):
	for j in range(600):
		if f[j]<f[j+1]:
			f[j],f[j+1]=f[j+1],f[j]
			g[j],g[j+1]=g[j+1],g[j]

for i in range(600):
	if f[i] != 0:
		print(g[i],end=' ')
```

---

## 作者：Doraeman (赞：0)

很高兴我做过类似的研究（~~虽然比较浅层~~）。  

## 暴力思路
如果有 $x$ 个相同的骰子，每个骰子有 $y$ 个面。  
那么这个骰子能得到的点数就是：
- 最少情况下，都骰到 $1$，总共 $x$。
- 最多情况下，都骰到 $y$，总共 $xy$。

在每一层搜索中，从点数 $x$ 到 $xy$ 分别进入下一层搜索。

**这种思路时间复杂度太高，显然不是正解。**  
然而，自测输出中有多个点数概率相同，不方便我们观察规律，所以可以**使用 dfs 或者简单的多层循环嵌套观察各个点数出现的次数（概率）。**

## 小数据找规律
对于 ```1 1 1 0 0``` 这组输入数据，可以写如下代码。
```cpp
#include<bits/stdc++.h>
using namespace std;

map <int, int> p;

void go(){
	for(int a1=1; a1<=4; a1++)
	for(int a2=1; a2<=6; a2++)
	for(int a3=1; a3<=8; a3++)
		p[a1+a2+a3]++;
}

int main(){
	go();
	for(int i=1+1+1; i<=4+6+8; i++)
		cout << i << ' ' << p[i] << '\n';
}
```
得到输出（左边是点数，右边是出现次数）：
```
3 1
4 3
5 6
6 10
7 14
8 18
9 21
10 23
11 23
12 21
13 18
14 14
15 10
16 6
17 3
18 1
```
可以发现：
- **越靠近上下两端的数，出现次数越小**；
- **越靠近中间的数，出现次数越大**。

即，**中位数出现概率最大，两端依次次之**。

这个规律同样可以应用到更多的数据中，可使用代码自行验证，此处不过多赘述。  

## 证明
接下来用数学证明这个规律的正确性。

首先，求一个 $x$ 面骰子的单次点数的[**数学期望值**](https://baike.baidu.com/item/%E6%9C%9F%E6%9C%9B%E5%80%BC/8664642)。
$$
\frac{1+2+\dots+x}{x}=\frac{x+1}{2}
$$

接下来，求一共 $N$ 个骰子（分别有 $x_1,x_2,\dots,x_N$）个面，其**点数之和**的数学期望值：

$$
\frac{x_1+1}{2}+\frac{x_2+1}{2}+\dots+\frac{x_N+1}{2}
$$
$$
=\frac{N+(x_1+x_2+\dots+x_N)}{2}=P
$$

一共 $N$ 个骰子，每个骰子最小得到 $1$ 点，总和最小就是 $N$；  
总和最大显然为 $x_1+x_2+\dots+x_N$。

所以最后的式子 $P$ 就是 **$N$ 个骰子所能得到的最小、最大值的中位数**。

最后，**根据单个骰子点数的分布的对称性，可知 $N$ 个骰子各个点数出现的概率也呈对称分布**。

## 输出答案
题目只是要求我们按照概率排序，**并不要求我们输出每种点数的出现次数。所以找到大小规律即可**，不需要再求概率。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[] = {4, 6, 8, 12, 20},
    ans[505], cnt;
int main(){
    int L = 0, R = 0;
    for(int i=0; i<5; i++){
        int x; cin >> x;
        // 更新最小值, 最大值 
        L += x, R += x * a[i];
    }

    int num = R + L + 1;
    // 求中间值 
    int mid = num / 2;
    // 从中心开始输出 
    int l = mid-1, r = mid;
    // 奇数特殊处理 
    if(num % 2){
        cout << mid << ' ';
        r++;
    }

    // 从中心向两端输出 
    while(l >= L)
        cout << l-- << ' ' << r++ << ' ';
}
```

---

## 作者：Zayn_Pan (赞：0)

## 题目

戳[这里](https://www.luogu.com.cn/problem/P13669)看题目。

#### 简化题意

给定 $5$ 种骰子的数量（$4$ 面、$6$ 面、$8$ 面、$12$ 面、$20$ 面），求所有可能的点数总和，并按出现概率从高到低排序输出。

## 思路

由于单个点数出现的概率是平均的，所以越接近中位数的点数出现的概率越大。

于是我们枚举点数 $i$ 从 $0$ 到中位数，然后将最小总点数与 $i$ 的和、最大总点数与 $i$ 的差存进答案数组里。

最后倒序输出数组即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],maxi,mini,p[10]={0,4,6,8,12,20},ans[100005],k;
bool vis[100005];
int main(){
	for(int i=1;i<=5;i++){
		cin>>a[i];
		mini+=a[i]*1;
		maxi+=a[i]*p[i];
	}
	for(int i=0;i<=(maxi+mini)/2;i++){
		if(!vis[mini+i]){
			vis[mini+i]=1;
			ans[++k]=mini+i;
		}
		if(!vis[maxi-i]){
			vis[maxi-i]=1;
			ans[++k]=maxi-i;
		}
	}
	for(int i=k;i>=1;i--)cout<<ans[i]<<' ';
	return 0;
}
```

---

