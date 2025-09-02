# Double Cola

## 题目描述

肖尔顿，莱奥纳多，佩妮，拉杰什和霍华德正在在卖“分裂可乐”的自动贩卖机那里排队。

队里第一个人（肖尔顿）会买一瓶分裂可乐，喝完以后他就会分裂成两个人并站到队尾。

下一个人（莱奥纳多）也会买一瓶分裂可乐，喝完后也会和刚才的肖尔顿一样分裂成两个人并站到队尾。

这个过程可以一直持续下去。~~（永动机）~~

举个例子，当佩妮喝下可乐（他之前的人也喝完了）后队列会变成这样：拉杰什，霍华德，肖尔顿，肖尔顿，莱奥纳多，莱奥纳多，佩妮，佩妮。

请您编写一个程序来输出喝下第$ n $罐分裂可乐的人。

__注意：__一开始的队列总会是这样的：肖尔顿，莱奥纳多，佩妮，拉杰什，霍华德。第一个去买可乐的人总会是肖尔顿。

## 样例 #1

### 输入

```
1
```

### 输出

```
Sheldon
```

## 样例 #2

### 输入

```
6
```

### 输出

```
Sheldon
```

## 样例 #3

### 输入

```
1802
```

### 输出

```
Penny
```

# 题解

## 作者：Azazеl (赞：3)

(ps:如果你很忙，请略过蒟蒻的胡扯区域)

------------    
#### 胡扯区域 

蒟蒻看到这道题第一个想法：**队列**~~（明眼人都知道）~~  
所以三下五除二，代码就出来了
```cpp
#include <cstdio>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
queue <string> a;//定义队列
int main() {
    int n;
    scanf("%d",&n);
    /*将五个人放入队列*/
    a.push("Sheldon");
    a.push("Leonard");
    a.push("Penny");
    a.push("Rajesh");
    a.push("Howard");
    for(int i=1;i<n;i++)//只用（n-1）次
    //因为第n个喝可乐的人排在第（n-1）个人后面
    {
        a.push(a.front());
        a.push(a.front());
        a.pop();
        /*每次将最前面的人置于队尾（两次），并弹出第一个人*/
    }
    cout<<a.front();
    return 0;
}
```
然而果不其然，华丽丽的$MLE$了  
于是蒟蒻自行进行了：数组模拟，双向队列···  
总之都$MLE$了  
由此，我们可以知道**模拟**是**下下策** ，还有学了高级的东西不代表有用

~~看看蒟蒻的提交记录就知道多蒻了~~


------------
#### 正解区域
通过计算机的大量枚举，可以发现：  
f[i]=(f[i-1]-f[i-2])*2+f[i-1]  
但是$1e9$的数组一定会$MLE$的
所以我们还得自己手算
```cpp
#include <cstdio>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
int sum[1000005]= {0,1},i=1,n;
string s[5]= {"Sheldon","Leonard","Penny","Rajesh","Howard"};
int main() {
    scanf("%d",&n);
    for(i=2; sum[i-1]*5<n; i++) sum[i]=(sum[i-1]-sum[i-2])*2+sum[i-1];//递推式,for循环顺便找出那一段区间 
    i-=2;
    n-=sum[i]*5;//然后一发玄学的式子 
    i=pow(2,i);
    if(n%i==0) n=n/i-1;
    else n/=i;
    cout<<s[n]<<endl; 
    return 0;
}
```
附：[枚举图片](https://cdn.luogu.com.cn/upload/pic/58746.png)，想看就看吧，有点长

---

## 作者：phil071128 (赞：1)

这道题其实一开始蒟蒻也是用的

## 队列模拟

但是结果可想而知，**MLE（空间超限）**

[评测记录](https://www.luogu.com.cn/record/40043961)
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[5]={"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};
queue <int> Q;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<=4;i++){
		Q.push(i);
	}
	for(int i=0;i<n;i++){
		Q.push(Q.front());
		Q.push(Q.front());
		Q.pop();
	}

	switch (n){
		case 1:{
			cout<<"Sheldon";
			break;
		}
		case 2:{
			cout<<"Leonard";
			break;
		}
		case 3:{
			cout<<"Penny";
			break;
		}
		case 4:{
			cout<<"Rajesh";
			break;
		}
		case 5:{
			cout<<"Howard";
			break;
		}
		
	}
	if(n<=5){
		return 0;
	}
	cout<<s[Q.front()];
	return 0;
}
```
那我们只好找规律了，如下

```cpp
//1 2 3 4 5 6 7 8 9 10 11 12 13 14 14 15 16 17...
//S L P R H S S L L P  P  R  R  H  H  S  S  S...
```
## 递推公式

$f_i = (f_{i-1}-f_{i-2})*2+f_{i-1} $



代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[5]={"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};
long long f[10000];
int main(){
	//1 2 3 4 5 6 7 8 9 10 11 12 13 14 14 15 16 17
	//S L P R H S S L L P  P  R  R  H  H  S  S  S
	//f[i]=(f[i-1]-f[i-2])*2+f[i-1]
	long long n;
	cin>>n;
	f[1]=1;
	int i=1;
	while(f[i]*5<n){
		f[++i]=(f[i-1]-f[i-2])*2+f[i-1];
		
	}
	i--;	
	n-=f[i]*5;
	i=pow(2,i);
	if(n%i==0){
		n=n/i-1;
	}else{
		n/=i;
	}
	cout<<s[n];
	return 0;
}
```


---

## 作者：_Legacy (赞：1)

#### 特殊解法：找规律
看到这题时我本来打算模拟的，但是打完之后MLE了(可能是我方法不好)，于是我开始找规律：

```
号数：01,02,03,04,05,||06,07,08,09,10,11,12,13,14,15||16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
人名：01,02,03,04,05,||01,01,02,02,03,03,04,04,05,05||01,01,01,01,02,02,02,02,03,03,03,03,04,04,04,04,05,05,05,05
```

所以我们先把队列分成几段：第一段为0号，段的号数用 i 表示。

段的规律为：每段之间差为 $(2^i)$X5
注意：因为要在之前的基础上增加，所以得出
```
int pox(int n){
	int ans=0;
	for(int i=0;i<=n;i++) ans+=pow(2,i)*5;
	return ans;
}
```
和
```
while(pox(i)<n) i++;
```
来计算号数和段数。

接下来发现每段里都会有$2^i$个同样的名字号数，再把一段分成5个部分，每个部分长为 i+1 。当总号数减去前面所有段后便剩下它在这一段的号数。于是便有了
```
while(n-pox(i-1)>pow(2,i)*j) j++;
```
来求它是哪一个部分的(j 表示部分)。
而 j 正是名字的号数。

#### 完整代码
```
#include<bits/stdc++.h>
using namespace std;
int pox(int n){
	int ans=0;
	for(int i=0;i<=n;i++) ans+=pow(2,i)*5;
	return ans;
}
//计算第 i 段的末尾是几号的函数。
int main(){
	int n,i=0,j=1;
//n 为总号数。
	cin >> n;
	while(pox(i)<n) i++;
//当找到一个大于 n 的号数以找到总号数在那一段。
	while(n-pox(i-1)>pow(2,i)*j) j++;
//当找到一个大于 n 在第 i 段的号数以找到它属于哪个部分。
	switch(j){
		case 1:{
			cout << "Sheldon" << endl;
			break;
		}
		case 2:{
			cout << "Leonard" << endl;
			break;
		}
		case 3:{
			cout << "Penny" << endl;
			break;
		}
		case 4:{
			cout << "Rajesh" << endl;
			break;
		}
		case 5:{
			cout << "Howard" << endl;
			break;
		}
	}
//它在哪个部分就说明它是哪个名字。
}
//CF82A
```

---

## 作者：long_long (赞：1)

这道题很水。
# 题目大意：

肖尔顿，莱奥纳多，佩妮，拉杰什和霍华德正在在卖“分裂可乐”的自动贩卖机那里排队。

队里第一个人（肖尔顿）会买一瓶分裂可乐，喝完以后他就会分裂成两个人并站到队尾。

下一个人（莱奥纳多）也会买一瓶分裂可乐，喝完后也会和刚才的肖尔顿一样分裂成两个人并站到队尾。

这个过程可以一直持续下去。（永动机）

举个例子，当佩妮喝下可乐（他之前的人也喝完了）后队列会变成这样：拉杰什，霍华德，肖尔顿，肖尔顿，莱奥纳多，莱奥纳多，佩妮，佩妮。

请您编写一个程序来输出喝下第n罐分裂可乐的人。

__注意：__一开始的队列总会是这样的：肖尔顿，莱奥纳多，佩妮，拉杰什，霍华德。第一个去买可乐的人总会是肖尔顿。


# 思路：

好啦，一个思路使用队列。

循环1到n-1，每次让最前面的人到最后。然后弹出第一个人。

```
for(int i=1;i<n;i++){
   	q.push(q.front());q.push(q.front());q.pop();//很香的
}
```

最后输出队列的front。

# code:

连起来就是

```
#include <queue>
#include <iostream>
using namespace std;
queue <string> q;
int main() {
    int n;
    cin>>n;
   q.push("Sheldon");q.push("Leonard");q.push("Penny");q.push("Rajesh");q.push("Howard");//初始化
    for(int i=1;i<n;i++){
	   q.push(q.front());q.push(q.front());q.pop();//操作
    }
    cout<<q.front()<<endl;
    return 0;
}
```




---

## 作者：Fa1thful (赞：0)

### 一、题意
有五个人在排队买可乐，编号为 `1` 的人买了一瓶后排到队尾，变成两个编号为 `1` 的人，编号为 `2` 的人模仿同样的操作，就这样一直循环下去，求第 `n` 个买可乐的人编号是几。

### 二、分析
首先看到题目的第一眼，想到直接从 `1` 到 `n` 枚举一遍，模拟第 `i` 瓶饮料是谁买的。可是数据范围 $1\le n \le 10^{9}$ 显然不支持线性的复杂度。这道题不可能用一个公式算出来，因为你不能确定到了 `n` 的时候一个人会分裂成几个人。因此这里我们考虑 $O(\log n)$ 的办法。

![](https://cdn.luogu.com.cn/upload/image_hosting/b6dlewt0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们先把前 `6` 瓶可乐的购买者列出来，发现购买的人的编号的顺序刚好是按照最初始的序列的排列顺序的。这也不难理解，因为排在最前面的人最早买。我们就可以列出来购买的顺序。

![](https://cdn.luogu.com.cn/upload/image_hosting/3l0dpb06.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们把序列最开头的变成 `1` 的第一次称为一个新的循环，我们发现每个循环中五种编号的数量都相等且都有 $2^p$ 个( $p$ 为第几个循环)。所以我们一直循环，每次 $now+tmp$。如果说加了五次就说明进入下一个循环， $2\cdot tmp$。如果 $now-n<tmp$，说明第 `n` 个买可乐的人编号就是当前的编号，就直接输出。这样一来，整个模拟的思路就十分清晰了。

### 三、时间复杂度
因为每次 $now+tmp$ 五次后 $tmp\cdot2$，最大的 `tmp` 大概是 $O(\log n)$。所以整个的复杂度大概是 $O(5\cdot\log n)$。

### 四、代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
string a[100] = {"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};   //五个人名 
int main()
{
	int n;
	cin >> n;
	int tmp = 1;   //一次加几个 
	int num = 1;     //现在加到几了 
	int time = 0;  //加一个tmp加了多少次 
	int leixing = 0;  //是那个人买可乐 
	while (1)
	{
		if (n == 1)    //特判，如果n=1那么一定小于tmp所以直接输出 
		{
			cout << a[0] << endl;
			return 0;
		}
		time++;   //加的次数++ 
		if (time == 5)   //加了五次 
		{
			tmp *= 2;   //进入下一个循环 
			leixing = 0;  //第一个人买 
			time = 0;  //开始新的循环 
		}
		num += tmp; //加 
		if (num - n < tmp && num >= n)  //如果往前找能找到n在与当前编号相同的编号 
		{
			if (n <= 5)    //特判 
			{
				cout << a[leixing + 1] << endl;
				return 0;
			}
			cout << a[leixing] << endl;     //直接输出 
			return 0;
		}
		leixing++;    //下一个人买可乐 
	}
	return 0;
}
```
谢谢观赏

---

## 作者：Need_No_Name (赞：0)

# Solution For CF82A

## 题意

有 $5$ 个人, 每个人依次喝下可乐，会分解成 $2$ 个相同的人，排到队尾继续进行。求第 $n$ 个喝可乐的人是谁。

## 思路

可以看见，这个队列是有规律的

比如这五个小朋友是杰哥，阿伟，彬彬，阿嫲，淑慧 ~~（皮一下很快乐）~~，还是方便起见，叫 $A, B, C, D,E$

则第一轮是这样的：

$A→B→C→D→E$

第二轮：

$A→A→B→B→C→C→D→D→E→E$

则可以观察，第 $x$ 轮先后有 $2^{x - 1}$ 个 $A, B, C, D, E$

则我们可以去不断减去以前的数目，再去将剩下的去模 $2^{x - 1}$ 就完事了

对于前面减去的数目，就可以暴力枚举即可。

## 代码

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 1e9 + 10;
const int M = 5;
const int mod = 5;
int n;
signed main()
{
	cin >> n;
	int cnt1 = 1;
	int tmp = 5;
	int nn = n;
	while(true)
	{
		if(n < tmp) break;
		else
		{
			n -= tmp;
			cnt1 *= 2;
			tmp *= 2;
		}
	}
	int fn = n / cnt1;
	int rn = n % cnt1;
	if(rn == 0)
	{
		if(fn == 1) cout << "Sheldon" << endl;
		else if(fn == 2) cout << "Leonard" << endl;
		else if(fn == 3) cout << "Penny" << endl;
		else if(fn == 4) cout << "Rajesh" << endl;
		else cout << "Howard" << endl;
		return 0;
	}
	else
	{
		if(fn == 0) cout << "Sheldon" << endl;
		else if(fn == 1) cout << "Leonard" << endl;
		else if(fn == 2) cout << "Penny" << endl;
		else if(fn == 3) cout << "Rajesh" << endl;
		else if(fn == 4) cout << "Howard" << endl;
		else cout << "Sheldon" << endl;
		return 0;
	}
	return 0;
}
```


---

## 作者：sysong (赞：0)

# 题解CF82A Double Cola

[传送门](https://www.luogu.com.cn/problem/CF82A)

### 题目描述

根据题目，有五个人排队，每一次队首会变成两个排到队尾，问第 $n$ 次操作时，排在队首的是哪一个人。

### $Solution$

由题，我们列表可以发现：

1. 操作前，队伍长度为 $5$，总长度为 $5$。

2. 经过第一轮操作后，队伍长度为 $10$，总长度为 $15$。

3. 经过第二轮操作后，队伍长度为 $20$，总长度为 $35$。

$\cdots$

可以看出，第一次队伍长度为 $5 \times 2^{0}$，第二次队伍长度为 $5 \times 2^{1}$，第三次队伍长度为 $5 \times 2^{2}$，$\cdots$，第 $n$ 次队伍长度为 $5 \times 2^{n - 1}$。

队伍总长则为 $5 \times (2^{n} - 1)$ （公比为 $2$ 的等比数列）

那么可以枚举总队伍长度（$5 \times (2^{t} - 1)$）要小于 $n$，从而算出当前每个人所分裂成的人数，得到答案。

### $C++ \quad Code$

```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
using namespace std;

inline int rd(){
	R int x=0;R char c=gc();//,f=1
	while(c>'9'||c<'0')c=gc();//{if(c=='-')f=-1;
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x;//*f
}

int main(){
	R int n=rd(),t=1,k,f;
	while(5*(1<<t)-5<n)++t;--t;					// 枚举队伍长度
	k=n-5*(1<<t)+5;								// 求出当前排在队伍中个数
	f=(1<<t);									// 每个人分裂成的人数
	k=(k-1)/f+1;								// 识别出是哪个人
	switch(k){
		case 1:printf("Sheldon\n");break;
		case 2:printf("Leonard\n");break;
		case 3:printf("Penny\n");break;
		case 4:printf("Rajesh\n");break;
		case 5:printf("Howard\n");break;
	}
	return 0;
}
```





***by jsntsys***

$2020.12.7$



---

## 作者：OdtreePrince (赞：0)

# -模拟-

说这道题是入门难度，真的把蒟蒻我给吓坏喽！

这道题我也解释不清楚，凭感觉打的一段代码，居然过了！太幸福了！！！

请大佬们评析一下我的代码，谢谢！

~~~
#include<bits/stdc++.h>
using namespace std;
int sum[1000005],i=1,n;
string s[5]={"Sheldon","Leonard","Penny","Rajesh","Howard"};
int main(){    
    scanf("%d",&n);
    sum[1]=1;
    sum[0]=0;
    while(sum[i]*5<n){
        sum[++i]=(sum[i-1]-sum[i-2])*2+sum[i-1];
    }
    i--;
    n-=sum[i]*5;
    i=pow(2,i);
    if(n%i==0){
    	n=n/i-1;
	}
	else n/=i;
    cout<<s[n];
    return 0;
}~~~

---

