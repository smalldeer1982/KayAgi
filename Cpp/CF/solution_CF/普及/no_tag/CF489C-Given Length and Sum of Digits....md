# Given Length and Sum of Digits...

## 题目描述

You have a positive integer $ m $ and a non-negative integer $ s $ . Your task is to find the smallest and the largest of the numbers that have length $ m $ and sum of digits $ s $ . The required numbers should be non-negative integers written in the decimal base without leading zeroes.

## 样例 #1

### 输入

```
2 15
```

### 输出

```
69 96
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
-1 -1
```

# 题解

## 作者：晨曦墨凝 (赞：9)

[题目传送门 （ $Luogu$ ）](https://www.luogu.com.cn/problem/CF489C)

[题目传送门 （ $codefoces$ ）](https://codeforces.com/problemset/problem/489/C)

本题主要考察**贪心**，请各位先思考，实在想不出来再看代码

#### 贪心思路：最小数低位最大，最大数高位最大

#### 坑点：
- 特判
- 遍历顺序与输出顺序

如果还是 AC 不了的话再看看下面

------------


#### 具体实现思路：
- **最小数**：先用一个 $1$ 把最高位占上，然后从低位到高位遍历，每位追求最大
- **最大数**：从高位到低位遍历，每位追求最大

#### 具体特判方式：

1. 若每位都是 $9$ ，但各位数字之和仍小于输入的和则无解 

2. 若和为 $0$ ：若长度为 $1$ 则最大数与最小数均为 $0$ ；否则，则无解 
    
3. (~~若长度为 $0$ ，则无解，观察数据范围，其实这条没必要~~)

实在不行的话再看代码

------------

```
#include <iostream>
#define MAXN 105
using namespace std;

int n, m, tmp, i, flag;
int mi[MAXN], ma[MAXN];

int main()
{
	cin >> n >> m;		//n指长度，m指和 
	
	/*特判*/
	if (n == 0 || m > 9 * n)	
	{
		printf("-1 -1");
		return 0;
	}
	if (m == 0)	
	{
		if(n == 1)
			printf("0 0");
		else
			printf("-1 -1");
		return 0;
	}
	
	/*最小数*/ 
	tmp = m - 1;
	mi[1] = 1;	//先把第一位占上 
	for (i = n; i >= 1 && tmp; --i)	//低位数字最大 
	{
		if (tmp >= 9)
		{
			mi[i] += 9;
			tmp -= 9;
		}
		else
		{
			mi[i] += tmp;
			break;
		}
	}
	for (i = 1; i <= n; ++i)
		cout << mi[i];	
	
	cout << " ";	//别忘了输出空格 
	
	/*最大数*/ 
	tmp = m;
	for (i = 1; i <= n && tmp; ++i)		//高位数字最大 
	{
		if (tmp >= 9)
		{
			ma[i] = 9;
			tmp -= 9;
		}
		else
		{
			ma[i] = tmp;
			break;
		}
	}
	for (i = 1; i <= n; ++i)
		cout << ma[i];
	return 0;
}
```


---

## 作者：Zaku (赞：2)

偶然刷到这题，跑来发个题解。（~~我才不会说我是比赛时做不出来最后看解析才过的~~）

这是一题基础贪心。
### 解法：
本题要求分别找出最小和最大的，各位之和为 $s$ 的 $m$ 位数。

**策略**：要找最小的，肯定把小数放在前面；要找最大的，肯定把大数放在前面。可以采用两个数组分别存储答案的每一位，通过不断判断 $s$ 剩余多少来填每一位。（代码难度不高，建议先独立写写看）
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int Min[105],Max[105]; 
int main(){
    int m,s;cin>>m>>s;
    if(s<1&&m>1||s>m*9){
		cout<<-1<<" "<<-1;//列举特殊情况 
		return 0;
	}
	Min[0]=1;
	int sum=s-1;//先给第一位赋1，总所有数字和先减1 
	//找最小值 
    for(int i=m-1;i>=1;i--){
        if(sum-9>=0)Min[i]=9;//如果总和比9大，直接在最后一位写9 
    	else Min[i]=sum;//反之就是总和(没得减了)
		sum-=Min[i];
	}
	Min[0]+=s1;//如果遍历完还有剩余，说明第一位不能是1，加上剩下的即可 
    for(int i=0;i<m;i++)cout<<Min[i];
	cout<<" ";
    sum=s;
    //找最大值(从第一位开始遍历，能写9就写9，其他同最小值 
    for(int i=0;i<m;i++){
        if(sum-9>=0)Max[i]=9;
        else Max[i]=sum;
        sum-=Max[i];
    }
    for(int i=0;i<m;i++)cout<<Max[i]; 
    return 0;
}
```


---

## 作者：Fearliciz (赞：2)

~~这道题其实很水~~

### 思路：

最小值：

最高位为 $1$，用剩下的 $\texttt{s-1}$ 放在低位。

最大值：

把所有的 $\texttt{s}$ 都放到高位，其余的低位用 $0$ 填充。

不过除了正常的情况，还有特殊情况，如下：

+ 当 $\texttt{s/m>9}$ 或 $\texttt{s/m=9}$ 且 $\texttt{s mod m}$ 不等于 $0$ 则说明每一位都写 $9$ 也无法满足。

+ 当 $\texttt{m=0}$ 即数位为 $0$，也无解。

+ 当 $\texttt{s=0}$ 且 $\texttt{m=1}$ 时，则输出都输出 $0$。

讲完这些，就可以写代码了。


```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1001], b[1001], k1, k2;

int main() {
	int m, s;
	cin >> m >> s;
	if (m == 0) {
		cout << "-1 -1" << endl;
		return 0;
	} else if (s == 0 && m == 1) {
		cout << "0 0" << endl;
		return 0;
	} else if (s == 0 && m != 1) {
		cout << "-1 -1" << endl;
		return 0;
	} else if (s / m > 9 || (s / m == 9 && s % m != 0)) {
		cout << "-1 -1" << endl;
		return 0;
	}
	int ss = 1;
	a[m] = 1;
	while (ss + 9 <= s) {
		a[++k1] = 9;
		ss += 9;
	}
	if (s - ss)
		a[++k1] += s - ss; //如果还有尾数，放在末尾。
	for (int i = m; i >= 1; i--)
		cout << a[i];
	cout << ' ';

	ss = 0;
	memset(a, 0, sizeof(a));
	while (ss + 9 <= s) {
		a[++k2] = 9;
		ss += 9;
	}
	if (s - ss)
		a[++k2] = s - ss; //如果还有尾数，判断。

	for (int i = 1; i <= m; i++)
		cout << a[i];
	return 0;
}
```


---

## 作者：hhhhahaha (赞：2)

这道题目就是叫我们~~慢慢~~模拟贪心，因为最大值只需要从第一位开始取最大就可以了，最小值除了第一位要是个1，依然是从最后一位将最大值储存进去，贪心过程如下
```cpp
#include<iostream>   
#include<cstdio>  
#include<cmath>  
using namespace std;  
int main()  
{  
   	int m,s,a[101],b[101];  
	cin>>m>>s;  
	if(s==0)  
	{  
		if(m==1)  
		{  
			cout<<0<<" "<<0;  
			return 0;  
		}//这个坑了我30分钟……  
		else cout<<-1<<" "<<-1;  
		return 0;  
	}  
	if(s%m==0&&s/m>9)//除的尽的情况
	{
		cout<<-1<<" "<<-1;
		return 0;
	}  
	if(s%m!=0&&s/m>=9)//除不尽的情况  
	{  
		cout<<-1<<" "<<-1;  
		return 0;  
	}//一堆玄学特判
	for(int i=1;i<=100;i++)  
	{  
		a[i]=0;  
		b[i]=0;  
	}//先清0，后面方便储存  
	int l=0,k=1;  
	while(l<s)  
	{  
		if(a[k]==9)  
			k++;//9是最大值  
		a[k]++;//储存    
		l++;  
	}//贪心
	int r=0;  
	k=1;  
	b[m]=1;//处理的时候需要特别注意  
	r++;  
	while(r<s)  
	{  
		if(b[k]==9)  
			k++;  
		b[k]++;  
		r++;  
	}//同上
	int ss=m;  
	for(int i=m;i>=1;i--)  
	{  
		cout<<b[i];  
	}  
	cout<<" ";  
	for(int i=1;i<=m;i++)  
	{  
		cout<<a[i];  
	}  
	return 0;  
}
```


---

## 作者：zhouxia (赞：2)

~~其实这题挺水的~~

这题主要需要注意的是在题目中的s（本代码中的n）等于0的时候，需要判断 m=1 的情况。还有就是最大值让高位尽量大，最小值让低位尽量大，注意最小值是要先让最高位等于1。然后其他的就见注释吧。
```cpp
#include<iostream>   
#include<cstdio>
using namespace std;
int n,m,a[110],b[110],l,j;    
int main(){  
	cin>>m>>n;
	if(n==0){
		if(m==1)printf("0 0"); 
		else printf("-1 -1");
		return 0;
	}  
	if(n/m>9){
		//n/m>9就说明即使全是九，数位和仍然小于n，就直接输出无解 
		printf("-1 -1");
		return 0;
	}
	if(n%m!=0&&n/m==9){
		//如果n不能整除m，则当n/m=9时，也无法构成自然数 
		printf("-1 -1");
		return 0;  
	}
	while(l+9<=n){//要取最大数，就尽量让高位变大 
		a[++j]=9;
		l+=9;
	}if(n-l)a[++j]=(n-l);
	j=0;l=1;
	b[m]=1; 
	while(l+9<=n){//同上，要取最小值，就尽量让低位变大 
		b[++j]=9;
		l+=9;
	}if(n-l)b[++j]+=(n-l);
	//注意，这里是+=，原因是当j=m时刚好取到最高位，而最高位已经付为1了
	for(int i=m;i>=1;i--)printf("%d",b[i]);
	printf(" ");
	for(int i=1;i<=m;i++)printf("%d",a[i]);
	return 0;  
}
```

完结撒花~

谢谢 qwq

---

## 作者：qhztz (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF489C)
## 思路：
**最大值**只需要从第一位开始储存最大值即可，

**最小值**则是除了第一位是 1  以外，
从最后一位将最大值储存进去。

注意：**要特判！！！**
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,s,a[101],b[101],u=1,j=1,sm;
int main(){
	scanf("%d%d",&m,&s);
	sm=m;
	if(s==0){//特判和为0
		if(m==1){//只有一位
			printf("0 0");
			return 0;
		}
		else printf("-1 -1");//无法找到
		return 0;
	}
	if(s%m==0&&s/m>9){//除的尽且全是九位数但和小于n，无解
		printf("-1 -1");
		return 0;
	}
	else if(s%m!=0&&s/m>=9){//除不尽且全是九位数但和小于n，无解
		printf("-1 -1");
		return 0;
	}
	while(u<s){//储存每一位
		if(a[j]==9) j++;
		a[j]++;
		u++;
	}
	u=1,j=1,b[m]=1;
	while(u<s){//储存每一位
		if(b[j]==9) j++;
		b[j]++;
		u++;
	}
	for(int i=m;i>=1;i--)
		printf("%d",b[i]);//输出
	printf(" ");
	for(int i=1;i<=m;i++)
		printf("%d",a[i]);//输出
}
```
拜拜qwq

---

## 作者：TheSky233 (赞：0)

## Description

给定数位长度 $m$ 和各数位之和 $s$，求符合这两个条件的最小整数与最大整数。

## Solution

算法：贪心和数组模拟。

------------

### 如何判断无解

- 显然，如果数位和为 $0$ 且长度大于 $1$，无解。
- 考虑到每一位最多能填到 $9$，所以如果 $s > m \times 9$，无解。


------------

定义当前长度 $len$ 与剩余的数位之和 $tot$。

求最小值时，从最后一位向前填。如果 $tot > 9$，直接将当前位填入 $9$ 即可，并把 $tot$ 减去 $9$。否则将当前位赋值为 $tot-1$，并把第一位的值加 $1$（因为最高位至少为 $1$）。

求最大值时，从第一位向后填。如果 $tot > 9$，直接将当前位填入 $9$ 即可，并把 $tot$ 减去 $9$。否则把这一位赋值为 $tot$，退出循环。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int m,s,len,tot;
int num[105];

int main(){
	cin>>m>>s;
	if(((s==0 && m!=1) || s>9*m)){puts("-1 -1"); return 0;}
	len=m,tot=s;
	while(tot>0 && len>=1){
		if(tot>9) num[len--]=9,tot=tot-9;
		else {num[len]=tot-1,num[1]++;break;}
	}
	for(int i=1;i<=m;i++) cout<<num[i],num[i]=0;
	putchar(' ');
	len=1,tot=s;
	while(tot>0 && len<=m){
		if(tot>9) num[len++]=9,tot=tot-9;
		else num[len++]=tot,tot=0;
	}
	for(int i=1;i<=m;i++) cout<<num[i],num[i]=0;
	return 0;
}
```

## Conclusion
~~是道水题~~，祝大家 $\color{green}\texttt{AC}$ 愉快！

---

