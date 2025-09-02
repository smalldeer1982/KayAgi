# [ICPC 2015 WF] Amalgamated Artichokes

## 题目描述

**题目背景**

法蒂玛是针对联合洋蓟果业公司 (Amalgamated Artichokes , AA) 的股票分析员。和其他的公司一样，联合洋蓟果业公司有的时候行情较好，有的时候不太行。法蒂玛对联合洋蓟果业公司的股票价格做了跟踪分析，她想确定不同时间段内股价最大跌幅是多少。比如如果一段时间内股价分别为19元，12元，13元，11元，20元，14元，则最大的跌幅为第一天和第四天之间的8。如果最后一天的价格不是14元而是10元，则最大跌幅为最后两天股价之间的10元。

法蒂玛做了些前期的分析，发现一段时间的股价可以建模精确合理地表示为以下方程式：
$$
price⁡(k)=p⋅(sin⁡(a⋅k+b)+cos⁡(c⋅k+d)+2)
$$
其中$p,a,b,c,d$均为常数。法蒂玛想要你写个程序确定给定价格序列上的最大股价跌幅。

图1说明了第一组样例的价格函数，你只能考虑时间为整数$k$时的价格。

对于第一组样例，最大股价跌幅出现在第四天和第七天之间。

**一句话题意**

对于给定序列，求差值最大的逆序对

## 说明/提示

时间限制: 5000 ms 

空间限制: 1048576 kB.

International Collegiate Programming Contest (ACM-ICPC) World Finals 2015

## 样例 #1

### 输入

```
42 1 23 4 8 10
```

### 输出

```
104.855110477
```

## 样例 #2

### 输入

```
100 7 615 998 801 3
```

### 输出

```
0.00
```

## 样例 #3

### 输入

```
100 432 406 867 60 1000
```

### 输出

```
399.303813
```

# 题解

## 作者：sxh2325 (赞：3)

#### [题目](https://www.luogu.com.cn/problem/P6904)是要带入公式求**最大**跌幅。
第一眼看到题目，我还以为是双指针，结果就 [TLE](https://www.luogu.com.cn/record/155441129) 了......

## 思路 
$n$ 最高能取到 ${\color{red}10^6}$，所以必须一次运行到位。我们可以以第一个数为第一个标准。当接下来的数是跌了时，就用一个变量加上跌的量；当接下来的数是涨了时，就用一个变量加上涨的量（减去差时涨为负）。如果变量为负，也就意味着对比原数是涨了，此时，刷新变量并把下一个标准定为使变量为负的那个数:
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
double p,a,b,c,d,ans=0,g,j,l,o,i=0,u;
int main() {
	long long k=1,n,h;
	cin>>p>>a>>b>>c>>d>>n;	
	l=p*(sin(a*k+b)+cos(c*k+d));//存储上一个股价 
	for(k=2;k<=n;k++){
		g=p*(sin(a*k+b)+cos(c*k+d));//带入公式 
		if(i<0) i=0;//当股价超过标准时，刷新标准（i为用来累计跌（涨）的量） 
		i+=l-g;//跌（涨）的量 
		if(i>ans) ans=i;//存储最大跌幅	
		l=g;
	}
	printf("%.6lf",ans);//差值小于10的-6次方（0.000001） 
	return 0;
}
```
本蒟蒻第2次写题解，有什么不妥之处请各位大佬指正。

---

## 作者：_one_day_ (赞：3)

# P6904 题解

这道题将题目给出的公式：$price(k)=p\times(\sin(a\times k+b)+\cos(c\times k+d)+2)$ 然后对给定序列，求最大差值的逆序对，最后保留 $8$ 位小数就能拿下这道小水题了！

# code [#](https://www.luogu.com.cn/record/144586918)

```
#include<bits/stdc++.h>//万能头文件
using namespace std;//命名空间
const int N=1e6+1;//看范围
double k,o,b,e;//kobe四周年纪念日好吧(2024.1.26);
double basketball[N],maxx=-100000.000,minn=0.00;//纪念一下 
double x;
double s=0.1;
int n;
int cj(int a,int b){//防抄袭
    return a*b;
}
int duru(){//快速读入
    int sum=0;
    int num=1;
    char ss=getchar();//将ss定义为输入
    while(ss<48||ss>57){//判断'0'到'9'的ASCLL码
        if(ss=='-'){
            num=-1;
        }
        ss=getchar();//再次输入
    }
    while(ss>=48&&ss<=57){
        sum=sum*10+ss-48;//乘完之后一定! 一定! 一定! 要减掉'0'的ASCLL码(重要的事情说三遍!!!)
        ss=getchar();
    }
    return cj(sum,num);//返回答案
}
int main(){
    cin>>k>>o>>b>>e>>x;
    n=duru();
    for(int i=1;i<=n;i++){
        basketball[i]=k*(sin(o*(double)i+b)+cos(e*(double)i+x)+2);//将公式price(k)=p⋅(sin(a⋅k+b)+cos(c⋅k+d)+2)）代入,记得强转
    }
    for(int i=1;i<=n;i++){//从序列结尾倒序处理，查询当前天之后的最小值
        if(maxx>basketball[i])
            minn=max(minn,maxx-basketball[i]);
        maxx=max(maxx,basketball[i]);
    }
    if(minn-s<0)
        cout<<0.00;
    else
        cout<<setprecision(8)<<fixed<<minn;//根据题意保留8位小数
    return 0;//华丽结束
}
```


---

## 作者：MnZnOIer (赞：3)

对于计算公式，题目中给的很明确：

$price(k)=p\cdot (\sin (a\cdot k + b) + \cos (c\cdot k + d) + 2)$

**思路如下：**

根据该式子，我们可以知道 $price(i)$ 的计算方法，然后用一个变量 $j$ 记录在 $price(i)$ 之前最大的 $price$，即 $price(j)$，再用一个变量 $ans$ 来记录最大股价跌幅，即 $price(j)-price(i)$，最后输出的 $ans$ 即可。

但是要注意，输出的 $ans$ 要保留小数位数，为了足够精确，我输出了 12 位小数。

下面是代码，勿抄：
```cpp
#include <bits/stdc++.h>
#define int long long
#define sycn ios::sync_with_stdio (0),cin.tie (0), cout.tie (0)
using namespace std;
double ans, price[1000007];
int a, b, c, d, n, p, j;
signed main ()
{
	sycn;
	cin >> p >> a >> b >> c >> d >> n;
	for (int i = 1; i <= n; ++ i)
	{
		price[i] = p * (sin (a * i + b) + cos (c * i + d) + 2);
		if (i == 1)j = 1;
		else if (price[j] < price[i])j = i;
		else ans = max (ans, price[j] - price[i]);
	}
	printf ("%.12lf", ans);
	return 0;
}
```

---

## 作者：MolotovM (赞：3)

~~针不戳，P6904全谷第一个AC针不戳~~

## 一句话题意
对于给定序列，求差值最大的逆序对

## 做法
看到求逆序对，考虑树状数组维护极值。

从序列结尾倒序处理，查询当前天之后的最小值，差为当前点开始下跌的最大跌幅，更新答案。

考虑当前值为下跌的最后一天，如果能造成贡献那么开始下跌的一天一定在这天之前。更新树状数组中这一天之前的位置的最小值。

~~没想到吧，~~ 树状数组倒着写也是对的。

**注意精度,要用double**

**Code:**
```
#include<bits/stdc++.h>
using namespace std;
#define double long double
inline int Read(){
	int s = 0 , w = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		s = (s << 1) + (s << 3) + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int MAXN = 1e6 + 60;
double s[MAXN];
int lowbit(int x){
	return x&(-x);
}
int n;
void add(int pos,double x){
	while(pos > 0){
		s[pos] = s[pos] < x ? s[pos] : x;
		pos -= lowbit(pos);
	}
}
double query(int pos){
	double res = 0x3f3f3f3f3f3f;
	while(pos <= n){
		res = s[pos] < res ? s[pos] : res;
		pos += lowbit(pos);
	}
	return res;
}
double ans = 0;
int main(){
	memset(s,0x3f3f3f3f,sizeof(s));
	double p = Read() , a = Read() , b = Read() , c = Read() , d = Read();
	n = Read();
	if(n == 1){
		double Max = 0.0;
		printf("%lf\n", Max);
		return 0;
	}
	double mi=1e18;
	for(int i = n ; i >= 1 ; i -= 1){
		double price = sin(a * ( 1.000 * i) + b) + cos(c * 1.000 * i + d) ;
		//cout << price << " ";
		ans = price - query(i) > ans ? price - query(i) : ans;
		add(i,price);
	}
	cout.precision(18);
	cout << ans * p << endl;
	return 0;
}
```

---

## 作者：Eason_AC (赞：2)

## Content
已知常数 $p,a,b,c,d$，我们知道，第 $k$ 天的股价公式为 $price_k=p\times(\sin(a\times k+b)+\cos(c\times k+d)+2)$。根据这个公式，请求出 $n$ 天以来股票的最大跌幅。

**数据范围：$1\leqslant p\leqslant 1000,0\leqslant a,b,c,d\leqslant 1000,1\leqslant n\leqslant 10^6$。**
## Solution
我们一边扫过去，边扫边记录当前的最大股价 $maxi$，然后拿 $maxi$ 减去当前的股价，最后取最大值即可。
## Code
```cpp
int p, a, b, c, d, n, curmax;
double price[1000007], ans;

int main() {
	scanf("%d%d%d%d%d%d", &p, &a, &b, &c, &d, &n);
	for(int i = 1; i <= n; ++i) {
		price[i] = p * (sin(a * i + b) + cos(c * i + d) + 2);
		if(i == 1) curmax = i;
		else if(price[curmax] < price[i]) curmax = i;
		else ans = max(ans, price[curmax] - price[i]);
	}
	printf("%.10lf", ans);
	return 0;
}
```
*/

---

## 作者：Autonomier (赞：2)

## Description 
按照题目所给函数，生成一个1-n的序列，求出求出逆序对中差值最大的。
## Solution 
这道题我们记录一个变量maxi，并将数列从头到尾扫一遍，每到一个数，maxi就表示当前数之前的最大的数，
用maxi和当前数作差维护答案,每次更新maxi即可。
## Code
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e6+10;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
double p,a,b,c,d;
int n;
double r[maxn]; 
int main()
{
	cin>>p>>a>>b>>c>>d;
	n=read();
	for(int i=1;i<=n;i++)
	{
		r[i]=p*(sin(a*(double)i+b)+cos(c*(double)i+d)+2);
	}
	double maxi=-100000.000;
	double res=0.00;
	for(int i=1;i<=n;i++)
	{
		if(maxi>r[i])
			res=max(res,maxi-r[i]);
		maxi=max(maxi,r[i]);
	}
	if(res-0.0000001<0)
		puts("0");
	else
		printf("%.8lf",res);
	return 0;
}
```

---

## 作者：zhoujunchen (赞：1)

[专栏食用更佳](https://www.luogu.com.cn/article/njewmw0w)

题意
---
这道题目需要计算在给定序列的股价模型中，最大的价格下跌幅
度。股价模型由以下方程给出：
$$ \operatorname {price}(k) = p \cdot (\sin (a \cdot k+b) + \cos (c \cdot k+d) + 2) $$
题目要求找出最大的逆序对。  

做题思路
---
- 使用循环计算每个 $k$ 对应的股价，并计算相邻股价之差。

- 维护一个变量记录找到的最大下跌幅度。

- 如果最大下跌幅度为正值，则输出该值；否则输出 $0$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
double pr[1000010],ans;
int p,a,b,c,d,n,maxi;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>p>>a>>b>>c>>d>>n;
	for(int i=1;i<=n;i++)
		pr[i]=p*(sin(a*i+b)+cos(c*i+d)+2);
	maxi=1;
	for(int i=2;i<=n;i++){
		if(pr[maxi]<pr[i])maxi=i;
		else ans=max(ans,pr[maxi]-pr[i]);
	}
	printf("%.8lf",ans);
	return 0;
}
```

---

## 作者：MassPoint (赞：0)

## 思路

翻译中已经很清楚地写明了题意：

>对于给定序列，求差值最大的逆序对。

有人一看到逆序对就用树状数组，其实大可不必。

可以直接从头遍历整个序列，记录下目前的最大值。如果当前数字大于历史最大值，说明不构成逆序对，需要更新历史最大值；否则就构成逆序对，需要维护答案。时间复杂度 $O ( n ) $，本题的数据范围可以通过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double pr[1000010];
int p,a,b,c,d,n;
double Max;
int Maxi;
int main(){
	scanf("%d %d %d %d %d %d",&p,&a,&b,&c,&d,&n);
	for(int i=1;i<=n;i++)
		pr[i]=p*(sin(a*i+b)+cos(c*i+d)+2);
	Maxi=1;
	for(int i=2;i<=n;i++){
		if(pr[Maxi]<pr[i])	Maxi=i;
		else Max=max(Max,pr[Maxi]-pr[i]);
	}
	printf("%.6lf",Max);	//注意精度
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/162508013)

---

## 作者：BK小鹿 (赞：0)

## 题意简述
法蒂玛需要分析特定股票价格公式生成的一系列价格，找出给定时间段内最大的股价跌幅。

## 思路分析

看到很多人用了树状数组，其实根本不用这么复杂。

这道题本质其实就是寻找最大的逆序对差值。

我们使用一个变量记录遍历过的最大股价，每计算一个新的股价，就尝试用它和已记录的最大值计算跌幅，然后更新最大值即可。

## AC Code

```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() 
{
    int p, a, b, c, d, n;
    cin >> p >> a >> b >> c >> d >> n;

    double max_d = 0.0;
    double max_p = -1.0; 

    for (int k = 1; k <= n; k++) 
	{
        double price = p * (sin(a * k + b) + cos(c * k + d) + 2);

        if (max_p == -1.0)  
            max_p = price;
        else 
            if (price > max_p)
                max_p = price;
            else
                max_d = max(max_d, max_p - price); 
    }

    cout << fixed << setprecision(9) << max_d << endl;
    return 0;
}

```

---

## 作者：Flaw_Owl (赞：0)

# P6904 [ICPC2015 WF] Amalgamated Artichokes 题解

题目链接：[P6904 [ICPC2015 WF] Amalgamated Artichokes](https://www.luogu.com.cn/problem/P6904)

## 题目分析

在中文翻译中已经给出了很精准的概括：**对于给定序列，求差值最大的逆序对**。说到逆序对，可能想到**树状数组**。然而这道题数据比较小，而且只要找差值最大的逆序对，如果使用树状数组反而累赘。

直接从头**遍历**整个序列，记录扫过的序列中的**数字最大值**。如果当前数字大于历史最大值，说明不构成逆序对，需更新历史最大值；反之，构成逆序对，维护答案。

值得注意的是，本题的序列需要进行计算，并且是 `double` 类型。请记得使用 `cmath` 或 `math.h` 库，并且注意定义、输出等步骤的变量类型。

## AC 代码

```cpp
#include <iostream>
#include <cctype>
#include <cmath>

using namespace std;

// 快读
int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 1e6 + 5;

int p, a, b, c, d, n;
double maxNum; // 历史最大值
double ans;    // 答案

double price[maxN];

int main()
{
    p = read(), a = read(), b = read(), c = read(), d = read(), n = read();
    for (int i = 1; i <= n; i++)
        price[i] = p * (sin(a * i + b) + cos(c * i + d) + 2);
    for (int i = 1; i <= n; i++)
    {
        if (maxNum > price[i])
            ans = max(ans, maxNum - price[i]);
        else
            maxNum = price[i];
    }
    printf("%lf\n", ans);
    return 0;
}
```

---

## 作者：hchhl___ (赞：0)

解题思路：本题的题目的限制比较宽松，可以直接进行for循环进行遍历。然后在算出他的股价之后就把他记录下来，同时进行比较记录最大的那一个股价。与当前的股价进行相减，比较出差值较大的即可。

```java
package ACM;

import java.util.Scanner;

public class P6904 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int p=sc.nextInt();
        int a=sc.nextInt();
        int b=sc.nextInt();
        int c=sc.nextInt();
        int d=sc.nextInt();
        int n=sc.nextInt();//六个数据的读入。
        double [] price=new double[n+1];
        double max=0;
        int maxi=0;//记录最大的股价的下标
        for (int i=1;i<=n;i++){
            price[i]=p*(Math.sin(a*i+b)+Math.cos(c*i+d)+2);
            if (i==1){
                maxi=i;
            }else if (price[maxi]<price[i]){
                maxi=i;
            }else
                max=Math.max(price[maxi]-price[i],max);
        }
        System.out.println(max);
    }
}

```

---

