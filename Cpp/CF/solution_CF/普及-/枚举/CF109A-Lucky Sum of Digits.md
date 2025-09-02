# Lucky Sum of Digits

## 题目描述

Petya喜欢幸运数字。我们都知道幸运数字是只含有$4$ 和$7$ 的正整数。例如数字$47$ ，$744$ ，$4$ 是幸运数字，而$5$ ，$17$ ，$467$ 不是。

Petya急切的想知道各个数位上数字的和为$n$ 的最小幸运数字是多少。帮助他完成这个任务。

## 样例 #1

### 输入

```
11
```

### 输出

```
47
```

## 样例 #2

### 输入

```
10
```

### 输出

```
-1
```

# 题解

## 作者：MZY666 (赞：9)

[原题传送门](https://www.luogu.com.cn/problem/CF109A)。[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-cf109a)。

### 【目录】

- 目录
- 题意概括
- 思路
- 代码实现+注释

### 【题意概括】

给定一个数的**数位和** $n$，要求这个数只能由 $4$ 或 $7$ 组成（即：这个数的每个数位上只能是 $4$ 或 $7$）。

如果没有方案，则输出 $-1$，否则输出最小的能满足该条件的数。

### 【思路】

既然是要最小，那么先考虑数位为 $4$ 的，每有一个数位为 $4$ 的 $n$ 便减 $4$ 。这是第一步。

若**还有剩余的** $n$ ，则考虑数位为 $7$ 的每有一个数位为 $7$ 的 $n$ 便减 $7$ 。

不够减了怎么办？那就从 $4$ 那边借一个过来。还不够减怎么办？再借撒。借到没了怎么办？这时候就没法满足条件了，便输出 $-1$ 。这是第二步。

但要要球满足最小，就得尽量把位数减小。若有 $7$ 个 $4$ 就可以转换为 $4$ 个 $7$，这是第三步（这一点作者WA了一次）。

时机成熟，是时候上代码了！其它细节也见代码~

### 【代码实现+注释】

```cpp
#include<bits/stdc++.h>//万能头文件好
using namespace std;
#define ll long long//个人习惯
int main(){
	ll n,i=0,j=0;
	//先定义好，i是4的个数，j是7的个数，一定要初始化为0
	scanf("%lld",&n);//输入
	i=n/4;n-=i*4;//前文的第一步
	if(n){
		while(i>0){
			n+=4;i--;
			if(n%7==0){j=n/7;n=0;break;}
			//前文的第二步
		}
	}
	if(n)printf("-1\n");
	//若还有剩余的，则无法满足条件，输出-1
	else{//否则
		while(i>=7){i-=7;j+=4;}//前文的第三步
		while(i--)printf("4");//输出4
		while(j--)printf("7");//输出7
		printf("\n");//换行是个好习惯
	}
	return 0;//over~
}
```

完结撒花~（疯狂暗示AWA）

---

## 作者：Laser_Crystal (赞：5)

### 深夜发题解~

~~哈欠×1~~

这道题个人认为是入门或普及-，因为思路简单，出题人没有设坑（也许设了坑，但我飞过去了QwQ）

总体思路是贪心，以4最少，7最多为贪心标准进行计算。

~~哈欠×2~~

用一个循环变量 i 来枚举4的个数，再判断剩下的数是否能被7整除。如果能，直接输出并结束程序。别忘了在最后加上一句cout<<-1，因为没找到即为不存在。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<=n/4;i++) 
	{
		int f,s;
		f=i*4;
		s=n-f;
		if(s%7==0) 
		{
			for(int j=0;j<i;j++) cout<<'4';
			s/=7;
			for(int j=0;j<s;j++) cout<<'7';
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

~~哈欠×3~~

拜拜，各位~

---

## 作者：06ray (赞：3)

这道题的算法应该是动态规划 + 贪心。

思路：先定义一个结构体数组为f，结构体中有four和seven两个变量，分别表示第i个数的最优解中有几个4和几个7。然后读入n，把f数组初值定义为一个很大的数字。然后确定边界为f[0].four=0,f[0].seven=0;

确定边界后开始写主要的过程，先定义循环变量i从4到n，接下来开始写状态转移方程。如果i-4>=0，那么

f[i].four=f[i-4].four+1;

f[i].seven=f[i-4].seven;

(大家可以想想为什么)

接着再判断如果i-7>=0，那么
先比较f[i-7].four与f[i-7].seven的两个和是否大于f[i]的两个数之和，如果小于或者等于且f[i-7].four>f[i].four,就进行以下操作:

f[i].four=f[i-7].four;

f[i].seven=f[i-7].seven+1;

最后结束了主体部分，就到了输出环节了。先判断如果f[n].four特别大或f[n].seven特别大，就输出-1。其他的话，就先输出所有的4，在输出所有的7。（因为要想它最小，小的数应该放前面）。

下面送代码。

```cpp
#include <iostream>
#include <cstring>//头文件 
using namespace std;//名字空间 
struct lucky{
	int four,seven;//定义一个结构体为lucky 
};
lucky f[1010000];//定义f数组。 
bool pd(lucky a,lucky b)//判断函数 
{
	if(a.four+a.seven+1>b.four+b.seven)//如果f[i-7].four与f[i-7].seven的两个和大于f[i]的两个数之和
	{
		return false;//不能替换 
	}
	if(a.four+a.seven+1<b.four+b.seven)//如果f[i-7].four与f[i-7].seven的两个和小于f[i]的两个数之和
	{
		return true;//可以替换 
	}
	return a.four>b.four;//如果相等，则判断他们4的个数 
}
int main()
{
	int n;
	cin>>n;//读入 
	for(int i=1; i<=n; i++)
	{
		f[i].seven=10000000;//赋值为很大的一个数 
		f[i].four=10000000;//赋值为很大的一个数 
	}
	f[0].seven=0;//确定边界 
	f[0].four=0;
	for(int i=4; i<=n; i++)//循环 
	{
		if(i-4>=0)//如果i不越界 
		{
			f[i].four=f[i-4].four+1;
			f[i].seven=f[i-4].seven;
		}
		if(i-7>=0)//如果i大于7 
		{
			if(pd(f[i-7],f[i]))//满足条件 
			{
				f[i].four=f[i-7].four;
				f[i].seven=f[i-7].seven+1;
			}
		}
	}
	if(f[n].four>=1000000||f[n].seven>=1000000)//如果它有一项很大 
	{
		cout<<-1;//就没有解，输出-1 
	}
	else
	{
		for(int i=1; i<=f[n].four; i++)
		cout<<4;//先输出所有的4 
		for(int i=1; i<=f[n].seven; i++)
		cout<<7;//再输出所有的7 
	}
	return 0;
}
```




---

## 作者：灵光一闪 (赞：2)

~~这题最后一解居然讲到了dp，Orz~~

这题其实就是模拟，具体看代码
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n/4+1;i++){//循环枚举4的数量
        if((n-4*i)%7==0){//如果把4全部减掉后能被7整除
            n=n-4*i;//这时候n/7表示7的数量
            for(int j=0;j<i;j++){//先输出4
                cout<<'4';
            }
            while(n!=0){//再输出7
                cout<<'7';
                n-=7;
            }
            return 0;//记得return 0;
        }
    }
    puts("-1");//如果没有就-1
    return 0;
}
```
The End.

---

## 作者：LB_zzm (赞：1)

```cpp
简单的贪心
#include<iostream>
#include<cstdio>
using namespace std;
int n,sum,cnt;
int fr(){
	char c;
	int neg=1;
	while((c=getchar())<'0'||c>'9')if(c=='-')neg=-1;
	int tot=c-'0';
	while((c=getchar())>='0'&&c<='9')tot=(tot<<3)+(tot<<1)+c-'0';
	return tot*neg;
}
//快读，不多说

void out(){
	int m=sum/4;
	for(int i=1;i<=m;i++)printf("4");
	m=(n-sum)/7;
	for(int i=1;i<=m;i++)printf("7");
}

int main(){
	n=fr();
	for(sum=0;sum+4<=n;sum+=4)if((n-sum)%7==0)break;//处理有几个4，能整除7退出，保证7最多
	if((n-sum)%7==0)out();//可能
	else printf("-1");//不可能
	return 0;
}
题解求过qwq
```

---

## 作者：TRZ_2007 (赞：1)

## Remarks
在集训的时候写题解…… 

瑟瑟发抖……

## Solution

让我们一数学的角度来考虑这一道题目。

第一点：如何确定这个数字是最小的  
首先TA的位数一定要小，比如说：$9 <111111111$，然而他们的各个位数之和是相同的，都是9 。

其次在保证位数的情况下，让小的数更靠前，比如说： $19 < 91$。

然后就可以使用了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;

bool check(int num) {
	for(int i=0;i<=num/4;i++) {//优先考虑4的个数
		if((num - i * 4) % 7 != 0) continue;//不是就别输了
		else {
			for(int k=1;k<=i;k++) printf("4");//先输出那一拨4
			for(int k=1;k<=(num - i * 4)/7;k++) //接下来再输出7			printf("7");
			puts("");
			return true;
		}
	}
	return false;
}

int main()
{
	scanf("%d",&n);
	if(!check(n)) {//首先这个数字必须是合法的，不然算个gost
		puts("-1");
		exit(0);
	}
}
```

---

## 作者：PC_DOS (赞：0)

为了使得生成的数字尽可能地小，我们需要在低位产生尽可能多的'7'并将'4'尽可能放在高位，我们可以从最多的'7'的情况开始枚举'7'的个数并计算还需要的'4'的个数，一旦方案可行，即输出对应的数字并结束，如果枚举到0个'7'之后依旧无解，则输出-1。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
string CreateRequiedString(long long nCount, char chrChrarater){ //产生由nCount个chrChrarater组成的字符串
	int i;
	string sAns;
	for (i = 1; i <= nCount; ++i)
		sAns += chrChrarater;
	return sAns;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iSum, nSeven, nFour; //iSum-个位数字之和；nSeven-'7'的个数；nFour-扣掉7之后还需要的值。
	cin >> iSum; //读入各位之和
	for (nSeven = iSum / 7; nSeven>=0; --nSeven){ //从最多的'7'的情况开始枚举'7'的个数
		nFour = iSum - 7 * nSeven; //计算余下的4的和
		if (nFour % 4 == 0){ //如果是4的倍数，方案可行
			cout << CreateRequiedString(nFour / 4, '4') << CreateRequiedString(nSeven, '7'); //输出
			goto endapp; //结束
		}
	}
	cout << -1; //无解
	endapp:
	return 0; //结束
}
```

---

## 作者：hensier (赞：0)

首先我们来看一下范围：$1\le {n}\le{10^{6}}$。按照最坏的情况，我们的位数可以达到${\frac{10^{6}}{4}}=2500000$，因此我们直接排除普通做法，至少这个数不可能正常存储。

我们可以开一个循环，我们知道，题目要求的是最小数。如果我们要判断一个正整数的大小，那么首先看位数——位数少的必定大。因此我们尽量多用$7$这个数位。也就是说，建立一个$i∈[\lceil\frac{n}{7}\rceil,0]$的循环来判断。对于一个$i$，如果满足$\frac{n-7i}{4}=\lceil\frac{n-7i}{4}\rceil$，即$n-7i$能够被$4$整除，则直接输出答案。

接着看输出。输出的话肯定是$4$在前面。我们知道，为了让数更小，我们一般把小的数放在数值高的位数上面（这里对数值的定义可能有出入——如果是千位数值就是$1000$）。因此我们先输出$4$再输出$7$。其中$4$的个数有$\frac{n-7i}{4}$个，而$7$的个数有$i$个，因此设置一个循环输出字符即可实现。

$AC$代码：

```cpp
#include<cstdio>
int n,i,j;
int main()
{
    scanf("%d",&n);//输入
    for(i=n/7;i>=0;i--)//循环
    {
        if((n-i*7)%4||n<i*7)continue;//不满足条件就跳到下一层循环
        for(;j<(n-i*7)/4;j++)printf("4");//循环输出
        for(j=0;j<i;j++)printf("7");//循环输出
        return 0;//能运行到这一步就说明必定有结果，所以这时直接结束程序
    }
    printf("-1");//没有结束程序就输出-1
}
```

---

