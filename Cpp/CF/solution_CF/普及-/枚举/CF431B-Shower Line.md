# Shower Line

## 题目描述

学生宿舍里只有一个淋浴，有很多个学生希望早上洗澡。这就是为什么每天早上宿舍门口有五个人排队的原因。淋浴一打开，第一个人就从队里进入淋浴。一段时间后，第一个人离开淋浴，下一个人进入淋浴。这个过程一直持续到每个人淋浴过。 洗澡需要一些时间，所以排队的学生在这时讲话。学生们成对交谈：第 $2\times i-1$ 个人与第 $2\times i$ 个人交谈。 更详细些，把人数从 $1$ 到 $5$ 编号，让我们假设队列最初看起来是 $23154$（编号 $2$ 的人位于队列的开头），然后，在淋浴开始前，$2$ 和 $3$ 谈话, $1$ 和 $5$ 谈话，$4$ 没有任何人交谈，$2$ 洗澡时，$3$ 和 $1$ 交谈，$5$ 和 $4$ 交谈，$3$ 洗澡时，$1$ 和 $5$ 聊天，$4$ 没有任何人交谈，$1$ 洗澡时，$5$ 和 $4$ 聊天，然后 $5$ 淋浴，$4$ 淋浴。 我们知道如果 $i$ 和 $j$ 交谈，$i$ 的幸福值增加 $g_{i,j}$，$j$ 的幸福值增加 $g_{j,i}$，你的任务是找到这样一排学生最初的顺序，使得所有学生的幸福感和最终达到最大。

## 说明/提示

对于 $100\%$ 的数据，满足 $0\le g_{i,j}\le10^5$。

## 样例 #1

### 输入

```
0 0 0 0 9
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
7 0 0 0 0
```

### 输出

```
32
```

## 样例 #2

### 输入

```
0 43 21 18 2
3 0 21 11 65
5 2 0 1 4
54 62 12 0 99
87 64 81 33 0
```

### 输出

```
620
```

# 题解

## 作者：zzx114514 (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/CF431B)
# 题目大意
学生宿舍里只有一个淋浴，有很多个学生希望早上洗澡。这就是为什么每天早上宿舍门口有五个人排队的原因。淋浴一打开，第一个人就从队里进入淋浴。一段时间后，第一个人离开淋浴，下一个人进入淋浴。这个过程一直持续到每个人淋浴过。 洗澡需要一些时间，所以排队的学生在这时讲话。学生们成对交谈：第 $2i-1$ 个人与第 $2i$ 个人交谈。 更详细些，把人数从 $1$ 到 $5$ 编号，让我们假设队列最初看起来是 $23154$（编号 $2$ 的人位于队列的开头），然后，在淋浴开始前，$2$ 和 $3$ 谈话，$1$ 和 $5$ 谈话，$4$ 没有任何人交谈，$2$ 洗澡时，$3$ 和 $1$ 交谈，$5$ 和 $4$ 交谈，$3$ 洗澡时，$1$ 和 $5$ 聊天，$4$ 没有任何人交谈，$1$ 洗澡时，$5$ 和 $4$ 聊天，然后 $5$ 淋浴，$4$ 淋浴。 我们知道如果 $i$ 和 $j$ 交谈，$i$ 的幸福值增加 $g_{i,j}$，$j$ 的幸福值增加 $g_{j,i}$，你的任务是找到这样一排学生最初的顺序，使得所有学生的幸福感和最终达到最大。  
~~PS:原题目翻译未使用 Latex~~
# 解题思路
由于题目中说明只有 $5$ 个学生，$1$ 至 $5$ 的全排列只有 $120$ 种，所以只要枚举全排列，对于每种排列，求其幸福值，取最大值即可。
## 知识点
`next_permutation` 函数可以求给定数组的全排列，改变数组排列顺序，如果没有排完，则返回 `true`，否则返回 `false`，因此我们一般配合 `do-while` 语句食用。
# 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans,sum,g[10][10],a[]={0,1,2,3,4,5};//a数组表示当前下标 
int main()
{
	for (int i=1;i<=5;i++)
		for (int j=1;j<=5;j++)
			cin>>g[i][j];
	do
	{
		sum=g[a[1]][a[2]]+g[a[2]][a[1]];
		sum+=g[a[2]][a[3]]+g[a[3]][a[2]];
		sum+=2*(g[a[3]][a[4]]+g[a[4]][a[3]]);
		sum+=2*(g[a[4]][a[5]]+g[a[5]][a[4]]);
		//为方便观看，将求幸福值代码分行，具体推导过程可参看其它题解，这里不再赘述 
		ans=max(ans,sum);
	}while(next_permutation(a+1,a+6));//对a数组求全排列 
	cout<<ans;
	return 0;//华丽的结尾 
}

```
# [AC!](https://www.luogu.com.cn/record/119780959)

---

## 作者：残阳如血 (赞：3)

# 思路分析
## 答题思路
一道纯**暴力**题！

因为我们发现数据最大是 $5$，而枚举全排列的时间复杂度为 $\mathcal O(n!)$，对于这种极小的数据范围是丝毫不用顾虑的，因为我们只需要执行 $120$ 次。
## 如何快速求出一个数组的全排列？
我们可以使用 dfs，一层一层获取这个数组的全排列。

~~是 STL 大法可是 C++ 党的福利，不用白不用。~~

在 STL 中，有一个函数 `next_permutation()`，可以枚举一个数组的全排列，但是时间复杂度高达 $O(n!)$，在 $1$ 秒内最多只能枚举长度为 $11$ 的数组的全排列。

因为这次最大的长度为 $5$，所以是不会超时的。

**敲响警钟：一开始的数组必须是升序排列的，否则程序运行结果就会出现问题！**

更多了解见[这里](https://blog.csdn.net/howardemily/article/details/68064377)。
## 如何计算一种方法的幸福度？
我们只需按照题目进行模拟即可，题目中已经有明显的示例了，这里不再多言。
# 复杂度分析
`next_permutation()` 的时间复杂度是 $\mathcal O(n!)$，计算幸福度的时间复杂度是 $O(1)$ 的，所以最终的时间复杂度是 $\mathcal O(n!)$ 的。
# 程序实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans = INT_MIN, g[6][6], a[6] = {0, 1, 2, 3, 4, 5}; // ans要赋很小的值，才能求出最大值！
int main() {
	for (int i = 1; i <= 5; i++)
		for (int j = 1; j <= 5; j++)
			cin >> g[i][j]; // 读入
	do ans = max(ans, g[a[1]][a[2]] + g[a[2]][a[1]] + g[a[2]][a[3]] + g[a[3]][a[2]] + 2 * g[a[3]][a[4]] +
		             2 * g[a[4]][a[3]] + 2 * g[a[4]][a[5]] + 2 * g[a[5]][a[4]]);
// 计算幸福度，只需模拟题意
	while (next_permutation(a + 1, a + 6)); // 枚举全排列，后面一项本为a+5+1，简写为a+6
	cout << ans;
	return 0;
}
```

---

## 作者：yydfj (赞：2)

**这是本蒟蒻第十四次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

有 $5$ 名同学前去排队洗澡，第 $i$ 名同学与第 $j$ 名同学交谈会获得幸福值 $g[i][j]+g[j][i]$，他们每过一次交谈，队列中前 $1$ 名的同学就会进去洗澡，正在洗澡或洗完澡的同学将不再进行交流，问这 $5$ 名同学获得的幸福总值最大是多少。

## 解法综述

设 $a[i]$ 为第 $i$ 名同学，则第 $i$ 名同学与第 $j$ 名同学交谈获得的幸福值是 $g[a[i]][a[j]]+g[a[j]][a[i]]$，将这 $5$ 名同学排队洗澡的过程进行模拟。

对于 $5$ 名同学的排队方式，可以将这些同学进行全排列，得出他们每一次的排列结果并得出他们获得的幸福总值，找出他们获得最大的幸福总值即可。

我们可以用 ``next_permutation`` 函数对这 $5$ 名同学进行全排列，共有 $120$ 种排列方案。

## 代码描述
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int g[6][6],a[6]={0,1,2,3,4,5},ans;
int main()
{
	for(int i=1;i<=5;i++)
	for(int j=1;j<=5;j++) scanf("%d",&g[i][j]);
	for(int i=1;i<=120;i++)//5名学生的全排列数共有120种
	{
		ans=max(ans,g[a[1]][a[2]]+g[a[2]][a[1]]+g[a[2]][a[3]]+g[a[3]][a[2]]+g[a[3]][a[4]]+g[a[3]][a[4]]+g[a[4]][a[3]]+g[a[4]][a[3]]+g[a[4]][a[5]]+g[a[4]][a[5]]+g[a[5]][a[4]]+g[a[5]][a[4]]);
		//求5名学生之间交谈获得的最大幸福总值
		next_permutation(a+1,a+6);//将a数组的后五位数进行全排列
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Silencer_jin (赞：1)

# [题面](https://www.luogu.com.cn/problem/CF431B)
这题明显是的思路**枚举**。

关于枚举，由于这里只有 $5$ 个人在排队淋浴，所以可以直接进行枚举。

但，这种做法各位大佬在题解里已经都讲过了。那么，我要将一种~~新~~方法 dfs！


------------

### 思路：
1. 进行 dfs，搜索。
1. 枚举，从 $1$ 到 $5$ 进行回溯（记得标记是否访问过！）。
1. 进行已访问过的标记。
1. 更新是否访问过（改为未访问）。
1. 最后，更新最大值（看清楚了再更新！）。
1. 进行结果输出。

------------
### 代码：
```
#include<bits/stdc++.h>
using namespace std;
int maxx,a[10][10],t[10];
bool vis[10];
void dfs(int point){
	if(point<=5)
	    for(int i=1;i<=5;i++)//枚举
			if(vis[i]==false){//是否访问过（走过）
				vis[i]=true;//已访问（走过）
				t[point]=i;//标记
				dfs(point+1);//更新不要忘
				vis[i]=false;//更新，回溯
			}
		
	else{
		maxx=max(maxx,a[t[1]][t[2]]+a[t[2]][t[1]]+a[t[2]][t[3]]+a[t[3]][t[2]]+2*a[t[3]][t[4]]+2*a[t[4]][t[3]]+2*a[t[4]][t[5]]+2*a[t[5]][t[4]]);//更新最大值
		return;
	}
}
int main(){
    for(int i=1;i<=5;i++)
        for(int j=1;j<=5;j++)
            cin >> a[i][j];
    dfs(1);//深搜
    cout << maxx;
    return 0;
}
```


---

## 作者：Cappuccino_mjj (赞：1)

一道暴力题。

---
## [题目传送门](https://www.luogu.com.cn/problem/CF431B)
题目意思：

给你一个 $5\times5$ 的矩阵 $g$，让你构造一个长度为 $5$ 的序列，使得按照题目给出的方法计算出来的结果最大，输出这个最大值。

---

思路：
1. 使用 dfs 来构造一个序列。
2. 按照题目的方法计算，更新最大值。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int g[10][10];
int ans;
int vis[10];
int a[10];
void dfs(int id)
{
	if(id>5)
	{//计算
		int sum=g[a[1]][a[2]]+g[a[2]][a[1]]+g[a[3]][a[4]];
		sum+=g[a[4]][a[3]]+g[a[2]][a[3]]+g[a[3]][a[2]];
		sum+=g[a[4]][a[5]]+g[a[5]][a[4]]+g[a[3]][a[4]];
		sum+=g[a[4]][a[3]]+g[a[4]][a[5]]+g[a[5]][a[4]];
		ans=max(ans,sum);//更新
		return;
	}
	for(int i=1;i<=5;i++)
	{
		if(vis[i])continue;//用过就跳过
		vis[i]=1;//标记
		a[id]=i;//放入序列
		dfs(id+1);
		vis[i]=0;//回溯
		a[id]=0;
	}
}
int main()
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			cin>>g[i][j];
	dfs(1);
	cout<<ans;
	return 0;
}
```

---

完美撒花~

---

## 作者：Wi_Fi (赞：1)

由于 $n=5$ 所以直接暴力即可。

需要的只是计算全排列。当然你可以从 [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706) 中直接复制过来你的 DFS 代码。但是有更简便的方法，那就是使用泛型算法中的 `next_permutation` 函数。

其用法为：
对于函数 `next_permutation(a,a+n)`，若原序列为最大排列，则将序列重排为最小序列，并返回 false；否则，将序列重排为字典序中下一个排列，并返回 true。

那么对于每一种全排列，若设 $a[i]$ 对应的为一种全排列中第 $i$ 个元素所对应的值，即编号，则它的情况计算方法为：

- 第一轮，第 $1$ 个人 与 第 $2$ 个人交谈，第 $3$ 个人 与 第 $4$ 个人交谈，第 $5$ 个人轮空，则幸福感增加 $g[a[1]][a[2]] + g[a[2]][a[1]] + g[a[3]][a[4]] + g[a[4]][a[3]]$。
- 第二轮，第 $2$ 个人 与 第 $3$ 个人交谈，第 $4$ 个人 与 第 $5$ 个人交谈，则幸福感增加 $g[a[2]][a[3]] + g[a[3]][a[2]] + g[a[4]][a[5]] + g[a[5]][a[4]]$。
- 第三轮，第 $3$ 个人 与 第 $4$ 个人交谈，第 $5$ 个人轮空，则幸福感增加 $g[a[3]][a[4]] + g[a[4]][a[3]]$。
- 第四轮，第 $4$ 个人 与 第 $5$ 个人交谈，则幸福感增加 $g[a[4]][a[5]] + g[a[5]][a[4]]$。

综上，每一种全排列的幸福感为：
`sum=g[a[1]][a[2]]+g[a[2]][a[1]]+g[a[2]][a[3]]+g[a[3]][a[2]]+2*g[a[3]][a[4]]+2*g[a[4]][a[3]]+2*g[a[4]][a[5]]+2*g[a[5]][a[4]]`

CODE:
```cpp
#include<bits/stdc++.h>

using namespace std;

const int INF=0x3f3f3f3f,N=1e5+5;
int i,j,n=5,g[6][6],a[6]={0,1,2,3,4,5},ans,sum;
int main()
{
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)cin>>g[i][j];
	}
	do
	{
		sum=g[a[1]][a[2]]+g[a[2]][a[1]]+g[a[2]][a[3]]+g[a[3]][a[2]]+2*g[a[3]][a[4]]+2*g[a[4]][a[3]]+2*g[a[4]][a[5]]+2*g[a[5]][a[4]];
		ans=max(ans,sum);
	}while(next_permutation(a+1,a+n+1));
	cout<<ans;
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)


### 前置芝士:next_permutation函数
next_permutation可以产生一个数组（vector)的下一个排列，具体使用方法为：

**数组版：**
```cpp
next_permutation(a,a+n);
```

**vector版：**
```cpp
next_permutation(a.begin(),a.end());
```

其作用是可以对一个已排序的数组（vector）做全排列，模板如下：
```
sort(a,a+n);
do
{
//内容
}while(next_permutation(a/*a.begin()*/,a+n/*a.end()*/);
```
注意：其返回值为bool类型。

### 进入正题
我们知道，第$2i-1$个人会和第$2i$个人聊天，而其产生的幸福值
应为$g_{i,j}+g_{j,i}$,所以我们就可以得到方程为:

```cpp
sum+=g[a[j]-1][a[j+1]-1]; 
sum+=g[a[j+1]-1][a[j]-1];
```
根据此公式，我们就可以得到一个循环嵌套，用来计算一个排列的总幸福值：
```cpp
for(int i=0;i<n;i++)
{
	for(int j=0;j<=n-i;j+=2)
	{
		if(j==n-1)continue;
		sum+=g[a[j]-1][a[j+1]-1]; 
		sum+=g[a[j+1]-1][a[j]-1];
	}
	a.erase(a.begin());
}
ans=max(ans,sum); 
```
又由于这边要erase,我们需要将a数组拷贝成b数组:
```cpp
vector<int> b;
for(int i=0;i<n;i++)
{
	b.push_back(a[i]);
}
```
再加上next_permutation的模板和输入等，我们就可以得到完整代码（其他具体看注释）。

$cute \; code$:
```cpp
#include<bits/stdc++.h>
#define n 5
using namespace std;
int g[8][8];
vector<int> a;
int main()
{
	int ans=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>g[i][j];
		}
		a.push_back(i+1);//存入a数组 
	}//输入 
	
	do//当还有排列方法时，继续循环 
	{
		int sum=0;
		vector<int> b;
		for(int i=0;i<n;i++)
		{
			b.push_back(a[i]);
		}//把a拷贝到b 
		
		for(int i=0;i<n;i++)//每个人进去 
		{
			for(int j=0;j<=n-i;j+=2)//求出这时的幸福值 
			{
				if(j==n-1)continue;//如果这是个落单的人，跳过，不然会数组超限 
				sum+=g[b[j]-1][b[j+1]-1];//i和j聊天 
				sum+=g[b[j+1]-1][b[j]-1];//j和i聊天 
			}
			b.erase(b.begin());//删除第一个人，即第一个人进去 
		}
		ans=max(ans,sum); 
		
	}while(next_permutation(a.begin(),a.end())/*调用next_permutation函数产生下一个排列*/);
	cout<<ans;
	return 0;
}

```
注：千万不要抄题解哦！





---

## 作者：zwyyy (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF431B)

---

## 思路
这道题我第一眼看到还以为要用贪心或者其他的算法来做，但是在我重新看了一遍题目后，我发现了~~这题的突破口~~：**人数只有 $5$ 个人**。

那这道题就很简单了，只要直接枚举学生可能的顺序，再记录最大值就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans, ma;
int a[6][6];
int plu(int i, int j){
	return a[i][j] + a[j][i];
}
int main(){
	for(int i = 1; i <= 5; ++i){
		for(int j = 1; j <= 5; ++j){
			scanf("%d", &a[i][j]);
		}
	}
	for(int y = 1; y <= 5; ++y){
		for(int u = 1; u <= 5; ++u){
			if(u == y)	continue;
			for(int i = 1; i <= 5; ++i){
				if(i == u || i == y)	continue;
				for(int o = 1; o <= 5; ++o){
					if(o == i || o == u || o == y)	continue;
					for(int p = 1; p <= 5; ++p){
						if(p == o || p == i || p == u || p == y)	continue;
						ans = 0;
						ans += plu(y, u) + plu(i, o);
						ans += plu(u, i) + plu(o, p);
						ans += plu(i, o);
						ans += plu(o, p);
						if(ans > ma)	ma = ans;
					}
				}
			}
		}
	}
	printf("%d", ma);
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/121454124)

---

## 作者：Jake_M (赞：0)

### 题目简述：

有 5 名同学排队去洗澡。在淋浴开始前，如果 $i$ 和 $j$ 交谈，$i$ 的幸福值增加 $g[$ $i$ $][$ $j$ $]$ ,$j$ 的幸福值增加 $g[$ $j$ $][$ $i$ $]$,即总幸福值增加 $g[$ $i$ $][$ $j$ $]$ $+$ $g[$ $j$ $][$ $i$ $]$，而淋浴一打开，队里第一个人就从队里进入淋浴,正在洗澡或洗完澡的同学将不再进行交流，问这 5 名同学获得的总幸福值最大是多少。

### 算法分析：

这是一道全排列问题。题目中限定了人数只能是 5 个，这是重点，因为   $5!=120$，所以可以直接暴力枚举。

我们用数组 $id$ 存储 5 名同学的顺序，模拟这 5 名同学排队洗澡的过程。而这 5 名同学的顺序，我们可以用  next _ permutation  函数对这 5 名同学进行全排列，共有 120 种排列方案。

对于  next _ permutation  函数，我在这里大概的讲一下：

- 这是一个求一个排序的下一个排列的函数，可以遍历全排列，要用头文件 #include<algorithm>  。

- 原理：若下一个排列存在，则返回真，如果不存在，则返回假。

- 使用方法： next _ permutation (数组头地址，数组尾地址);

### 代码参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10;  //稍微开大一点，防止数组溢出 
int g[N][N];
int id[N]={0,1,2,3,4};
int ans;
int main() {
    for(int i=0; i<5; i++) 
        for(int j=0; j<5; j++) 
            scanf("%d",&g[i][j]);
	do{ans=max(ans,g[id[0]][id[1]]+g[id[1]][id[0]]+g[id[1]][id[2]]+g[id[2]][id[1]]+(g[id[2]][id[3]]+g[id[3]][id[2]]+g[id[3]][id[4]]+g[id[4]][id[3]])*2);}while(next_permutation(id,id+5));
    printf("%d",ans); 
    return 0;
}
```
~~求通过~~

---

## 作者：Juanzhang (赞：0)

**思路**

- 暴力枚举全排列，$O(1)$计算分值

题目限定的$5$个人让题目简单了不少，因为$5!=120$，所以直接暴力，

而计算分值时也可以直接用$"$通项公式$"$

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 7;
bool vis[maxn];
int ans, a[maxn], g[maxn][maxn];

void dfs(int now) {
	if (now > 5) {
		ans = max(ans, g[a[1]][a[2]] + g[a[3]][a[4]] + g[a[2]][a[3]] + g[a[4]][a[5]] + g[a[3]][a[4]] + g[a[4]][a[5]] +
		               g[a[2]][a[1]] + g[a[4]][a[3]] + g[a[3]][a[2]] + g[a[5]][a[4]] + g[a[4]][a[3]] + g[a[5]][a[4]]);
		return;
	}
	for (int i = 1; i < 6; i++) {
		if (!vis[i]) {
			vis[i] = 1, a[now] = i, dfs(now + 1), vis[i] = 0;
		}
	}
}

int main() {
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			scanf("%d", &g[i][j]);
		}
	}
	dfs(1);
	printf("%d", ans);
	return 0;
}
```

---

