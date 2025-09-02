# Average Numbers

## 题目描述

You are given a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Find all such indices $ i $ , that the $ i $ -th element equals the arithmetic mean of all other elements (that is all elements except for this one).

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1
3 ```

## 样例 #2

### 输入

```
4
50 50 50 50
```

### 输出

```
4
1 2 3 4 ```

# 题解

## 作者：封禁用户 (赞：3)

此题只需按照题意模拟即可。  
题目传送>>[CF134A](https://www.luogu.com.cn/problem/CF134A)  
### 题意简述：  
- 给定 $n$ 个整数，求其中等于平均值的数的个数及其这几个数的序号。  
- 如果没有等于平均值的数，在第一行输出 $0$，这时，可以输出一个空行，也可以不输出。
### 题目分析：  
在输入这些整数时进行累加总和，输入完成后除于 $n$ 求出平均值，然后一个个枚举看是否等于平均值，如等于则计数，然后输出其计数结果，最后再一个个枚举输出其等于平均值的数的序号。  
最后还要注意等于平均值的数的个数为 $0$ 的特殊情况，我们可以在计数输出后来个判断，如果为 $0$，就直接结束程序，免去再枚举输出序号。
### Code：  
```cpp
#include <iostream>
using namespace std;
#define endl '\n'   //宏定义加速endl换行 
double a[200001];   //开数组存数 
int main()
{
	ios::sync_with_stdio(0);   //关同步流，加速cin输入和cout输出 
	double n,z=0,p,j=0;   //定义数的个数、总和、平均值 、计等平均值的数的个数
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	    z+=a[i];	//累加总和 
	}
	p=z/n;   //求平均值 
	for(int i=1;i<=n;i++)
	{
		if(a[i]==p)   //如果等于平均值就计数 
		{
			j++;
		}
	}
	cout<<j;
	if(j==0) return 0;     //如果没有一个数等于平均值就直接在输出个数后结束程序，无需再判断输出序号 
	cout<<endl;    //注意换行 
	for(int i=1;i<=n;i++)
	{
		if(a[i]==p)
		{
			cout<<i<<" " ;   //输出其序号 
		}
	}
	return 0;   //结束整个程序 
}
```
### 评测结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/3ryvk7fy.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：Remake_ (赞：1)

这道题，其实不用那么麻烦。

首先有一个大家都知道的结论，便是：往一个平均数为$n$的数列里加入$n$，平均值不变。

然后，我们发现其逆命题依然成立，便是往一个平均数为$n$的数列里加入一个非$n$的数，平均值一定会变。

在联系此题，题目就变成了有多少个数是这个数列的平均数，并依次输出。

所以谁不会写推到这一步的题呢？

```cpp
#include<bits/stdc++.h>
using namespace std;
int b[200005],a,sum,cnt;
int main(){
	cin>>a;
	for(int i=1;i<=a;i++){
		cin>>b[i];
		sum+=b[i];
	}
	for(int i=1;i<=a;i++){
		if(b[i]*1.0==sum*1.0/a){
			cnt++;
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=a;i++){
		if(b[i]*1.0==sum*1.0/a){
			cout<<i<<" ";
		}
	}
}
```


---

## 作者：氷スイカ233 (赞：1)

这题就是简单的模拟。

只不过要优化一下常数什么的

思路：

为了不浪费时间总是取平均数，直接用一个$S$储存总和，每次都减去$a _ i$再除以$n - i$再乘以$1.0$就珂已了。

下面上代码：

```
#include <bits/stdc++.h>
using namespace std;
int a[200001],S,b[200001],top = 0,ans;
int main() {
    int n;
    cin>>n;
    for (register int i = 1; i <= n; i++) {
        cin>>a[i];
        S += a[i];//S累加
    }
    for (register int i = 1; i <= n; i++) {
        if(a[i] == (S - a[i]) * 1.0 / (n - 1)) {//判断平均数与ai是否相等
            b[++top] = i;//标记
            ans++;//统计个数
        }
    }
    cout<<ans<<endl;
    for (register int i = 1; i <= top; i++)
        cout<<b[i]<<' ';//输出，不解释
    cout<<endl;
    return 0;
}
```

提醒：直接交会蜜汁UKE：

![233](https://cdn.luogu.com.cn/upload/pic/32101.png)

---

## 作者：cyrxdzj (赞：0)

### 一、思路

根据统计的相关知识，在一个数列里剔除一个数，如果剩下的数的平均值与这个被剔除的数相等，则就算不剔除这个数，数列的平均值也相等。

因此，我们只需求一次平均值，再进行判断。

### 二、完整代码

```
#include<cstdio>
using namespace std;
int n,input[200001];
int sum,average;
int ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&input[i]);
		sum+=input[i];//计算总和。
	}
	if(sum%n!=0)//平均值为小数，不可能有答案。
	{
		printf("0\n");
		return 0;
	}
	average=sum/n;//计算平均值。
	for(int i=1;i<=n;i++)//计算符合要求的数的数量。
	{
		if(input[i]==average)
		{
			ans++;
		}
	}
	printf("%d\n",ans);//输出数量。
	if(ans==0)//特判ans为0的情况。
	{
		return 0;
	}
	for(int i=1;i<=n;i++)//输出第二行的结果。
	{
		if(input[i]==average)
		{
			printf("%d ",i);
		}
	}
	printf("\n");//换行。
	return 0;//完结撒花！
}

```

### 三、后记

记录：<https://www.luogu.com.cn/record/51670493>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：清清老大 (赞：0)

## 题意

有 $n$ 个正整数 $a_1,a_2,...,a_n$ 求出所有的 $i$ ，使得 $a_i$ 与其他所有正整数的算术平均值相等

## 思路

可以将题目理解为：求出所有的 $i$ ，使得 
$$a_i=\frac{\sum\limits_{j=1}^na_j-a_i}{n-1}$$
即
$$(n - 1)a_i=\sum\limits_{j=1}^na_j-a_i$$

$$na_i=\sum\limits_{j=1}^na_j$$

所以只需要把 $\sum\limits_{j=1}^na_j$ 求出来，再枚举 $a_i$ 就可以了

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int a[200010],sum = 0,n,ans = 0;
    // 首先输入数据
    cin >> n;
    for(int i = 1;i <= n;i ++)
    {
        cin >> a[i];
        sum += a[i];
    }
    // 先把符合题意的i的数量求出来
    for(int i = 1;i <= n;i ++)
    {
        if(a[i] * n == sum)
        {
            ans ++;
        }
    }
    cout << ans << endl;
    // 再输出每一个i
    for(int i = 1;i <= n;i ++)
    {
        if(a[i] * n == sum)
        {
            cout << i << " ";
        }
    }
    return 0;
}
```


---

## 作者：tribool4_in (赞：0)

首先记录整个数组的和 ```sum```，接着枚举每一个位置 ```i```，如果 ```a[i]``` 等于数组中其他数的平均数，那么记录这个答案。

至于求出 数组中其他数的平均数，只需用除了这一项以外的数的和除以 ```n-1``` 即可（即 ```(sum - a[i]) / (n - 1)```），当然由于要考虑浮点数，最好写成 ```(sum - a[i]) * 1.0 / (n - 1)```。

上代码：

```cpp
// Code By WLS
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int s=0, w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int n;
int a[200011], sum, cnt, ans, anss[200011];
int main() {
	n = read();
	for (int i = 1; i <= n; i++) sum += (a[i] = read());
	for (int i = 1; i <= n; i++) if (a[i] == (sum - a[i]) * 1.0 / (n - 1)) ans++, anss[++cnt] = i;
	printf("%d\n", ans);
	for (int i = 1; i <= cnt; i++) printf("%d ", anss[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：2132B (赞：0)

### 思路

这题就是模拟求一个数列中有多少个和这个数列平均数相等的

#### 具体实现

用一个$sum$变量来记录这个数列的和，然后用$for$循环来判断数列中的每个数是否与$sum/n($平均数$)$一样。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
double n,a[200010],sum,ans;//注意double
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]==sum/n)
            ans++;//有多少个数
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)
    {
        if(a[i]==sum/n)
            cout<<i<<" ";//注意！！输出编号而不是数
    }
    return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个数 $a_1,a_2,a_3,...,a_n$。试求出使得 $a_i$ 与其他所有整数的算术平均值相等的所有 $i$。

**数据范围：$2\leqslant n\leqslant 2\times10^5,1\leqslant a_i\leqslant 1000$。**
## Solution
我们可以将其转化为：求出能满足 $a_i=\dfrac{\sum\limits_{j=1}^na_j-a_i}{n-1}$ 的所有 $i$。直接在数列中扫一遍看能不能满足这个条件即可。注意精度问题，需要将 $a_i$ 开成高精度的 $\texttt{double}$。
## Code
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n, ans[200007];
double s, a[200007];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lf", &a[i]);
		s += a[i];
	} 
	for(int i = 1; i <= n; ++i)
		if(a[i] == (s - a[i]) / (n - 1))	ans[++ans[0]] = i;
	for(int i = 0; i <= ans[0]; ++i) {
		printf("%d", ans[i]);
		if(!i)	puts("");
		else	printf(" ");
	}
	return 0;
}
```

---

## 作者：TRZ_2007 (赞：0)

### 题解[Average Numbers](https://www.luogu.com.cn/problem/CF134A)  
# Description  
给你一个长为 $n$ 的数组，其中 $1\le n\le 200000$，让你计算其中有多少个数是这个数组的平均数，并输出他们的编号。  
# Solution  
没错，就是这么简单。但是唯一要注意的是有可能会丢精度，所以判断的时候要小心一点。  
~~其他没有了吧~~。  
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200009;

int a[N],n,cnt;
double sum,ave;

template<class T>
inline void read(T &x) {//没啥用的快读
	x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
}

int main() {
	read(n);
	for(int i = 1;i <= n;i++) {
		read(a[i]);
		sum += a[i];
	}
	ave = sum / n;//ave表示这个数组的平均数
	for(int i = 1;i <= n;i++) {
		if(a[i] * 1.0 == ave) {//如果有
			++cnt;//记录
		}
	}
	printf("%d\n",cnt);//输出有几个
	for(int i = 1;i <= n;i++) {
		if(a[i] * 1.0 == ave) {//输出编号
			printf("%d ",i);
		}
	}
    return 0;
}
```

---

## 作者：hensier (赞：0)

~~这道题本蒟蒻用了freopen，直接挂了。~~

该题主要考察了$int$数组和$float$变量的使用。首先分别定义$a,b$数组，分别保存输入的数和满足条件的数，大小$2e5+1$，即$2*10^5+1$就足够了。

我们边输入边对于$sum$进行累加。然后在$[1,n]$区间进行判断——如果$1.0*(sum-a[i])/(n-1)=a[i]$就满足条件。注意：必须要加$1.0$，$1.0$代表这是浮点数。

这样分析过后，我们可以得到代码：

```cpp
#include<cstdio>
int n,i,s,x,a[200001],b[200001];
float f;
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s+=a[i];
    }
    for(i=1;i<=n;i++)
    {
        f=1.0*(s-a[i])/(n-1);
        if(f==a[i])b[++x]=i;//直接用++x，这样能让代码看起来更清晰、更容易理解
    }
    printf("%d\n",x);//输出x（即数量），对x=0不需要特判——因为输出0后下面的程序[1,0]就不合法，所以不需要特判
    for(i=1;i<=x;i++)printf("%d ",b[i]);
}
```


---

