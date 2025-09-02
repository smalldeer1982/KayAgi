# Cubes for Masha

## 题目描述

Absent-minded Masha got set of $ n $ cubes for her birthday.

At each of 6 faces of each cube, there is exactly one digit from 0 to 9. Masha became interested what is the largest natural $ x $ such she can make using her new cubes all integers from 1 to $ x $ .

To make a number Masha can rotate her cubes and put them in a row. After that, she looks at upper faces of cubes from left to right and reads the number.

The number can't contain leading zeros. It's not required to use all cubes to build a number.

Pay attention: Masha can't make digit 6 from digit 9 and vice-versa using cube rotations.

## 说明/提示

In the first test case, Masha can build all numbers from 1 to 87, but she can't make 88 because there are no two cubes with digit 8.

## 样例 #1

### 输入

```
3
0 1 2 3 4 5
6 7 8 9 0 1
2 3 4 5 6 7
```

### 输出

```
87```

## 样例 #2

### 输入

```
3
0 1 3 5 6 8
1 2 4 5 7 8
2 3 4 6 7 9
```

### 输出

```
98```

# 题解

## 作者：引领天下 (赞：4)

看了一下题解很麻烦，我来一发简单的

这题很明显可以直接离散化，每6个数一组，$ O(n^2) $暴力枚举，如果不在一组就进行标记。

程序非常简单。

```cpp
#include <bits/stdc++.h>
using namespace std ;
int a[20],n,i=1;
bool v[300];//标记出现了没有
int main(){
    cin>>n;
    for(int i=0;i<6*n;i++){cin>>a[i];v[a[i]]=1;}//读入，初始标记
    for(int i=0;i<6*n;i++)for(int j=0;j<6*n;j++)if((i!=j)&&((i/6)!=(j/6)))v[a[i]+10*a[j]]=1;//直接暴力枚举拼方块
    while(v[i++]);cout<<i-2;//因为退出循环的时候i已经++过了，所以要-2
}
```

---

## 作者：cbyybccbyybc (赞：3)

# 一道很水的模拟题，只要用每一个骰子的每一面去凑数，最后判断一下。。。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5][10];
bool flag[100010]={0};//标记数组
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<6;j++)
			cin>>a[i][j];//输入每颗骰子的每一面
	for(int i=0;i<n;i++)//模拟每颗骰子
	{
		for(int k=0;k<6;k++)//模拟每颗骰子的每一面
		{
			if(i+1<n)//特判，以免j>=n
			{
				for(int j=i+1;j<n;j++)//模拟剩下骰子
				{
					for(int l=0;l<6;l++)//模拟剩下骰子的每一面
					{
						flag[a[i][k]]=1;
						flag[a[j][l]]=1;
						flag[a[i][k]*10+a[j][l]]=1;
						flag[a[i][k]+a[j][l]*10]=1;
					}
				}
			}
			else//把单独自己的骰子标记掉,我就栽在这儿3次
			{
				flag[a[i][k]]=1;
			}
		}
	}
	for(int i=1;i<100;i++)//在从1~99判断
	{
		if(flag[i]==0)//一旦中断
		{
			cout<<i-1;//输出前一位
			break;
		}
	}
	return 0;
}
```
# 祝大家刷题愉快，谢谢

---

## 作者：tder (赞：2)

[$\Large\color{black}\textbf{CF887B Cubes for Masha}$](https://www.luogu.com.cn/problem/CF887B) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/CF887B)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-cf887B)

~~看着数据范围开始狂喜！！！直接暴搜！！！~~

---

$$\large\textbf{思路}$$

用 $m_{i,j}$ 表示第 $i$ 个骰子上是否出现了点数 $j$。

从 $1$ 到 $10^n-1$ 枚举每一个数 $v$，分类讨论 $v$ 的位数，同时枚举每一种排列，如果可以拼出则继续判断下一个数，否则条件均不满足则无法被拼出，最大可以拼出 $v - 1$ 也就是 $v$ 的前一个数，输出答案并 `break` 跳出循环即可。 

---

$$\large\textbf{代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
map<int, bool> m[5];
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= 6; j++) {
			int x;
			cin>>x;
			m[i][x] = 1; // 标记 map 
		}
	for(int v = 1; v <= pow(10, n) - 1; v++) { // 最大为 n 个 9 
		if(v <= 9) { // 当 v 为一位数 
			if(m[1][v] || m[2][v] || m[3][v]) continue; // 满足其一即可 
		} else if(v <= 99) { // 当 v 为两位数 
			int a = v / 10, b = v % 10; // 存 v 的十位和个位数 
			if((m[1][a] && m[2][b]) || (m[1][a] && m[3][b]) || (m[2][a] && m[3][b])) continue;
			// continue 直接跳到下一个数 
		} else { // 当 v 为三位数 
			if((m[1][b] && m[2][a]) || (m[1][b] && m[3][a]) || (m[2][b] && m[3][a])) continue;
			int a = v / 100, b = v / 10 % 10, c = v % 10; // 存 v 的百位、十位和个位数
			if((m[1][a] && m[2][b] && m[3][c]) || (m[1][a] && m[3][b] && m[2][c])) continue;
			if((m[2][a] && m[1][b] && m[3][c]) || (m[2][a] && m[3][b] && m[1][c])) continue;
			if((m[3][a] && m[1][b] && m[2][c]) || (m[3][a] && m[2][b] && m[1][c])) continue;
		}
		cout<<v - 1; // 输出答案
		break; // 跳出循环
	}
	return 0;
}

```

---

## 作者：yxy666 (赞：2)

这道题貌似蛮简单，但是千万不要把它理解错了。我一开始就看成了求能组合的最大值。。。白耗我半小时。不过这道题貌似蛮水的。。

想法： $n$  的数据给的很弱，所以我们可以直接暴力枚举。先枚举一个方块，再枚举这个方块的一个数，然后再枚举另一个不同的方块，再从 $1——6$ 个数全都枚举一遍，然后标记。等会要输出答案的时候 $i$ 从 $0$ 到 $98$ 枚举，如果下一个造不出来，那就输出 $i$ ，结束程序。~~（看了下其他题解，貌似没有讲得这么详细的）~~

$code$ :
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool vis[105];//判断当前下标能否造出来，造的出来为1 
struct yan{
	int num[10];
}a[5];//用来存不同的方块的数字 
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读 
int main(){
	n=read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=6;j++)a[i].num[j]=read();//我是用结构体读入数据 
	for(int i=1;i<=n;i++){//枚举第一个方块 
		for(int t=1;t<=6;t++){//枚举第一个方块的数字 
			for(int j=1;j<=n;j++){//枚举第二个方块 
				if(i==j)continue;//保证两个方块不同 
				for(int k=1;k<=6;k++){//枚举第二个方块的数字 
					vis[a[i].num[t]]=1;vis[a[j].num[k]]=1;//三种情况，第一：本身 
					vis[a[i].num[t]*10+a[j].num[k]]=1;//第二：x*10+y 
					vis[a[j].num[k]*10+a[i].num[t]]=1;//第三：y*10+x 
				}
			}
		}
		
	}
	for(int i=0;i<99;i++){
		if(vis[i+1]==0){printf("%d",i);return 0;}
	}//找第一个造不出来的，输出 
	return 0;
}
```


---

## 作者：cyrxdzj (赞：1)

### 一、题意简述

给出 $n$ 个方块，每个方块有 $6$ 个面，每个面都有一个数字。求一个数，使得从 $1$ 到这个数都可以使用这些方块所拼成。

数字 $6$ 不能通过颠倒的方式变成 $9$，同理，$9$ 也不能变成 $6$。

### 二、思路

枚举每种可能，并记录下来。

### 三、完整代码

```cpp
#include<cstdio>
using namespace std;
int n,cube[4][7];
int can_make[101];//存储结果。
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)//输入方块。
	{
		for(int j=1;j<=6;j++)
		{
			scanf("%d",&cube[i][j]);
		}
	}
	for(int i1=1;i1<=n;i1++)//枚举第一个方块的编号。
	{
		for(int i2=1;i2<=6;i2++)//枚举第一个方块使用的数。
		{
			can_make[cube[i1][i2]]=true;//记录。
			for(int j1=1;j1<=n;j1++)//枚举第二个方块的编号。
			{
				if(j1==i1)//确保第一个方块与第二个方块不是一个方块。
				{
					continue;
				}
				for(int j2=1;j2<=6;j2++)//枚举第二个方块使用的数。
				{
					can_make[cube[i1][i2]*10+cube[j1][j2]]=true;//记录。
				}
			}
		}
	}
	for(int i=1;i<=100;i++)
	{
		if(!can_make[i])//如果一个数不能被拼成：
		{
			printf("%d\n",i-1);//输出前一个数。
			break;
		}
	}
	return 0;//完结撒花！
}

```

### 四、后记

记录：<https://www.luogu.com.cn/record/51620359>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：IOI_can_AK_lsr (赞：0)

# CF887B 题解

#### [洛谷传送门](https://www.luogu.com.cn/problem/CF887B) | [CF传送门](https://www.codeforces.com/contest/887/problem/B)

[更好的阅读体验](https://www.luogu.com.cn/blog/910468/cf887b-tijie)

### 题面分析&&思路

据题意可知，数据给你了这些方块上的数字，要找出这 $n$ 个方块上的数字最大可组成的数字。

**注:“最大可组成的数字”指的是从 $1$ 到该数字都可以由这n个数字由任意排列所组出，而不是可组出的最大数字。**

组成的数字不可能在一个方块上（一个正方体不可能被扯开），所以可以考虑模拟每一方块的每一数字，挨个组一下。

但是，这么多 if 和 for 写的不累吗？

so，我们可以改一下循环的方式，再用 bool 数组打标记。

扔几张图吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/k12mxita.png)

一开始的程序遍历过程大概长这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/atyxxruk.png)

改了之后的大概长这样。

是不是时间复杂度更少了？

### 代码

说了这么多，也该上代码了。

```cpp
#include<bits/stdc++.h>
int n,a[10][10];//节约空间
bool flag[114];
signed main(){
    std::cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=6;j++){
      std::cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){//多重循环打标记
        for(int j=1;j<=6;j++){
            for(int l=i;l<=n;l++){
                if(i!=l){//如果数字能组出
                    for(int r=1;r<=6;r++){
                flag[a[i][j]]=true;//个位数
                flag[a[l][r]]=true;
                flag[a[i][j]*10+a[l][r]]=true;//两位数
                flag[a[i][j]+a[l][r]*10]=true;
                    }
                }
            }
        }
    }
    for(int i=1;i<=99;i++){
        if(!flag[i]){//如果中断了（题目要求不能中断）
            std::cout<<i-1;//输出可以输出最大的数
            return 0;
        }
    }
    std::cout<<"0";//如果没有
    return 0;
}
```
完结撒花！

---

## 作者：yutong_Seafloor (赞：0)

# [题目在这里 · Cubes for Masha CF887B](https://www.luogu.com.cn/problem/CF887B) 
### 题目简要：
有几个方块，现在这几个方块要组成数字（组成数字范围在 $0$ 到 $99$ 之间），我们要找出它最大可以组成的数字。

**注意这个最大指的是它前面（也就是 $1$ 到这个数字）的数字都可以组出，不是能组出来的最大数字，~~因为这个样例错了好几次~~。**

### 题意分析
我们要知道一点：组成的数字只能是两个不同方块上的，一个方块上的是不存在的，那我们就可以简单的模拟一下，把方块一的数字和方块二的一一配对，这里还要注意下**单独一个方块也要算上一个数字**。

所以在这里~~又双叒叕~~提出一种改良方法：

1. 我们在做一次双方块循环的时候把正着来和反着来一起标记，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/f6uwcuy0.png)

~~有人就要说了，啊这个已经有人写了你发他干什么啊~~，那么为了节约循环，我们再改良。

2. 第二个方块的循环初始值我们直接是第一个方块 $+1$ 的初始值，这样就可以免除判断并且省时间，方便理解贴一张图吧。
![](https://cdn.luogu.com.cn/upload/image_hosting/x6ubydct.png)

## 代码 


```cpp 
#include<bits/stdc++.h>
using namespace std;
int n,a[5][10],i,j,l,k,jg[100];
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	for(j=1;j<=6;j++)
	cin>>a[i][j];
	for(i=1;i<=n;i++)
	for(j=1;j<=6;j++)
	for(k=i;k<=n;k++)
	if(i!=k)
	for(l=1;l<=6;l++)
	{
		jg[a[i][j]]=1;
		jg[a[k][l]]=1;
		jg[a[i][j]*10+a[k][l]]=1;
		jg[a[i][j]+a[k][l]*10]=1;
	}
	for(i=1;i<=99;i++)
	if(jg[i]==0)
	{
		cout<<i-1;
		return 0;
	}
	cout<<"0";
}
``` 

**这里要注意几个点：**
1. 我们找的时候找的是无法输出的最大数，那么能输出的要 $-1$。
2. 最后不要忘了 `cout<<"0";`！

---

## 作者：CCDYJXZ (赞：0)

**题意**：

给出 $n$ 个方块，每个方块都有六个面，每个面都有一个数字。要求用任意两个方块的共两个面拼数，找到第一个 $100$ 以内不能被拼出的数，并输出它前一个数。

**思路**：

这是一道简单的模拟题，我们只需枚举所有可能出现的数字记录，在那之后找出第一个没被记录的数就行。唯一需要注意的是枚举时，只用一个方块拼成的一位数也要记录。

------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int aa[4][7];
bool ss[520];
int main(){
	int a,s,d,f;
	cin>>a;
	for(int i=1;i<=a;i++)
		for(int j=1;j<=6;j++)
			cin>>aa[i][j],ss[aa[i][j]]=1;//输入所有的方块每一个面同时标记一位数。 
	for(int i=1;i<=a;i++)
		for(int j=1;j<=6;j++){//枚举第一个方块。 
			for(int l=1;l<=a;l++){ 
				if(l==i)//如果跟第一个方块是重复的直接退出。 
					continue;
				for(int q=1;q<=6;q++)
					ss[aa[i][j]*10+aa[l][q]]=1;//标记由两个方块组成的两位数。 
			}
		}
	for(int i=1;i<100;i++)
		if(ss[i]==0){//找到第一个没被标记的数在输出它前一个数。 
			cout<<i-1;
			break;
		}
    return 0;
}
```

蒟蒻的一篇题解，如有不满请见谅。

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

## 分析

这一题完全就是一道水模拟，按照题目要求一个数一个数地找一直到找不到为止。

（其实我一开始是把这道题当成二分来写的，结果发现这道题没办法二分……）

这里有一些地方需要注意：

1. 需要注意一位数和两位数的判断时的区别；

2. 通过数组来记录，只要是个答案就更新数组，保证所有答案都被数组记录过；

3. 最后输出的时候是在找第一个没有被存储的数，而题目要求我们输出能拼的数，所以我们的输出应该是输出它前一个数。

于是，这个非常非常水的模拟题目就被我们完美解决了！

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,block[4][7];
bool record[101];//记录所有能拼的数 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=6;j++){
			cin>>block[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=6;j++){//第一个方块的面 
			record[block[i][j]]=true;//1位数也要记录 
			for(int k=1;k<=n;k++){
				if(k==i)continue;//同一个方块不能拼数 
				for(int m=1;m<=6;m++){//第二个方块的面 
					record[block[i][j]*10+block[k][m]]=true;//前面的是十位后面的是个位
					//不用管会不会重复，因为反正能的话就记录，能拼几次和答案没关系 
				}
			}
		}
	}
	for(int i=1;i<=100;i++){
		if(!record[i]){//不能拼就输出 
			cout<<i-1;//记得是输出能拼的数，现在找的是第一个不能拼的 
			return 0;
		}
	}
	return 0;
}

```


---

## 作者：LordLaffey (赞：0)

#### 这道题的思路应该很容易就能想出来，但是可能实现有点困难，我这里想了一种不同的思路，应该很好理解

看完题之后，我们的第一个想法应该就是将所有的数枚举一遍，找到在哪个数的时候拼不成，那么这个数-1应该就是能拼出来的最大的数，但是我感觉这样有些麻烦，于是我找到了一种新思路
>记录0~9每个数出现在第几个色子，如果一个数的各位分别在不同的色子上可以找到，那么这个数就可以拼出来

这样是不是代码就非常好写了

# AC代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
bool num[10][10];
int n;

bool is(int x){

    int a1=x/10,a2=x%10;        //将这个数拆开

    if(a1==0)                   //如果这个数一位数，那么就只需要找它在色子里出没出现过
    {
        for(int i=1;i<=n;i++)
            if(num[a2][i])
                return true;    //这个一位数出现过
        return false;           //没出现过
    }

    for(int i=1;i<=n;i++)       //枚举每个色子
    {
        for(int j=1;j<=n;j++)
        {
            if(j==i)            //这个数的两位不能在同一个色子上
                continue;
            if(num[a1][i]&&num[a2][j])  //可以在两个不同的色子上分别找到x的十位和个位
                return true;
        }
    }

    return false;               //没有找到

}

int main(){

    scanf("%d",&n);

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=6;j++)
        {
            int a;
            scanf("%d",&a);
            num[a][i]=true;         //记录a在第i个色子可以找到
        }
    }

    for(int i=1;i<=100;i++)         //枚举每个数可不可以拼出来
    {
        if(!is(i))
        {
            cout<<i-1;              //如果拼不出来，上一个数则为解
            return 0;
        }
    }

    return 0;

}

```
完结撒花✿✿ヽ(°▽°)ノ✿


---

## 作者：紫妹只有17岁 (赞：0)

为什么我一A就刷成绿题了喵~>.<~……

CF上的题目没人做，也没人写题解喵~>.<~，那么蒟蒻来写一篇

我的方法就是枚举暴力，因为最大只能到99，所以从1枚举到99就行了

used数组表示该数是否可以表示，里面的这一句：

used[a[i][j]*10+a[k][l]]=true;

就是说每一个a[i][j]都枚举它成为10位，然后任意一个数（不包括a[i][j]）成为个位的情况

具体看代码吧喵~>.<~，~~蒟蒻不是很讲的清楚~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4][7];//用来放数的数组
int n;
bool used[100];//从1-99判断是否可以表示
int main()
{
    memset(used,false,sizeof(used));//初始化成都不能表示
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
	{
        for(int j=1;j<=6;++j)
		{
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
	{
        for(int j=1;j<=6;j++)
		 {
            used[a[i][j]]=true;//首先把当前的a[i][j]设置为能够表示
            for(int k=1;k<=n;k++)//枚举（相当于再开一层两重循环
			{
                if(k==i)//首先这两个数（即a[i][j]和a[k][l]）不能一样
					continue;//一样就铺该
                for(int l=1;l<=6;l++)//第二个循环枚举第二位
				{
                    used[a[i][j]*10+a[k][l]]=true;
					//以a[i][j]*10（即以a[i][j]为10位），以a[k][l]为个位的数设置为可用
                }
            }
        }
    }
    for(int i=1;i<=99;++i)//寻找
	{
        if(!used[i])//找到第一个无法表示的数
		{
            printf("%d\n",i-1);//那么就输出这个数之前的那个数（即可以表示的最后一个数）
   			return 0;
        }
    }
}
```

去掉注释的
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4][7];
int n;
bool used[100];
int main()
{
    memset(used,false,sizeof(used));
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=6;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=6;j++)
         {
            used[a[i][j]]=true;
            for(int k=1;k<=n;k++)
            {
                if(k==i)
                    continue;
                for(int l=1;l<=6;l++)
                {
                    used[a[i][j]*10+a[k][l]]=true;
                }
            }
        }
    }
    for(int i=1;i<=99;++i)
    {
        if(!used[i])
        {
            printf("%d\n",i-1);
            break;
        }
    }
    return 0;
}
```

蒟蒻第一次写题解喵~>.<~，希望管理员大大能让过，有任何错误请不吝指正喵~>.<~（谢谢观看）

---

