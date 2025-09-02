# Lever

## 题目描述

你有一根杠杆，用一个字符串s表示（$3≤|s|≤10^{6}$）。

若字符串的下标为i的字符为“^”，则表示杠杆的支点的坐标为i；

若字符串的下标为i的字符为“=”，则表示坐标为i的位置没有任何东西；

若字符串的下标为i的字符为一个数字c（$1≤c≤9$），则表示在坐标为i处，有一个质量为c的重物挂在杠杆上。

杠杆一开始是平衡的，杠杆自重忽略不计。

你的任务是判断这根杠杆的状态（平衡、向左倾斜或向右倾斜）。

注意，本题需要使用64位整型。

## 样例 #1

### 输入

```
=^==
```

### 输出

```
balance
```

## 样例 #2

### 输入

```
9===^==1
```

### 输出

```
left
```

## 样例 #3

### 输入

```
2==^7==
```

### 输出

```
right
```

## 样例 #4

### 输入

```
41^52==
```

### 输出

```
balance
```

# 题解

## 作者：miraculously (赞：5)

分析：

这题要判断杠杆的平衡状态，那就用杠杆原理，左边每一个数字乘上这数与支点的距离再全部相加，右边也重复上述过程，把两个结果对比一下，左边大就向左偏，右边大就向右偏，相等则平衡。

提醒：要开 long long，不然会炸掉。

代码如下（有注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long cnt1,cnt2,cnt;//cnt1记录左边的总和，cnt2记录右边的总和，cnt表示支点位置
char c[1000001];
int main()
{
	scanf("%s",c);
	for(int i=0;i<strlen(c);i++)
	if(c[i]=='^')
	{
		cnt=i;
		break;
	}//找出支点
	for(int i=0;i<strlen(c);i++)
	{
		if(i<cnt&&c[i]<='9'&&c[i]>='1')
		cnt1+=(cnt-i)*(c[i]-'0');//处理左边
		if(i>cnt&&c[i]<='9'&&c[i]>='1')
		cnt2+=(i-cnt)*(c[i]-'0');//处理右边
	}
	if(cnt1==cnt2)
	{
		printf("balance");
		return 0;
	}
	cnt1<cnt2?printf("right"):printf("left");
}
```


---

## 作者：hwwqy (赞：1)

# CF376A Lever
前置知识： [杠杆原理](https://baike.baidu.com/item/%E6%9D%A0%E6%9D%86%E5%8E%9F%E7%90%86/1536418?fr=aladdin) 。  
杠杆原理是什么呢？  
>>要使杠杆平衡，作用在杠杆上的两个力矩（力与力臂的乘积）大小必须相等。即：动力 $\times$ 动力臂 $=$ 阻力 $\times$ 阻力臂，用代数式表示为 $F1 \cdot L_1 = F_2 \cdot L_2$。式中，$F_1$ 表示动力，$L1$ 表示动力臂，$F_2$ 表示阻力，$L_2$ 表示阻力臂。从上式可看出，要使杠杆达到平衡，动力臂是阻力臂的几倍，阻力就是动力的几倍。来源于《论平面图形的平衡》。 

>>——摘自百度百科

简单来说，要使杠杆平衡必须要 $F_1L_1=F_2L_1$  。  
而如果有多个物件挂在杠杆上呢？  
那就是 $F_1L1+F_2L2+F_3L3+\cdots=F'_1L'_1+F'_2L'_2+F'_3L'_3+\cdots$     
( $L'_i$ 表示右边的一个点到质点的距离 $F'_i$ 表示重量 )  
那答案就很显然了  ：  
我们可以统计左右的 $F_iL_i$ 之和 ，存到  $L$ 和 $R$ 之中。  
然后再比较，如果 $L>R$ 那么输出 `left` 。  
如果 $L<R$ 那么输出 `right` 。  
如果 $L=R$ 那么输出 `balance` 。  
注意要开 `long long` 。  


完整代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll l=0,r=0;
int main()
{
	string gan;
	cin>>gan;
	int mid;
	for(mid=0;gan[mid]!='^';mid++);//查找杠杆的支点
	for(int i=0;i<gan.size();i++)
	{
		if(i<mid)
		{
			if(gan[i]!='=')l+=(mid-i)*(gan[i]-'0');
		}
		else if(i>mid)
		{
			if(gan[i]!='=')r+=(i-mid)*(gan[i]-'0');
		}
	}//计算L,R
	if(l==r)
	{
		printf("balance");
	}
	else if(l>r)
	{
		printf("left");
	}
	else
	{
		printf("right");
	}//判断
    return 0;
}

```

---

## 作者：CLCK (赞：1)

~~水题，建议评红或橙。~~

### 前铺芝士

典型的杠杆问题，原理：
$$ F_1 \times L_1 + F_2 \times L_2 + ... + F_n \times L_n = F_1' \times L_1' + F_2' \times L_2' + ... + F_n' \times L_n' $$

因为悬挂重物，所以受到的拉力 $F$ 就等于 $G_\text{物}$ ，且方向竖直向下，那么力臂就是悬挂点到支点的距离（施力方向垂直杠杆）。

知道了这些，这题就没有技术含量了，一道简单的字符串模拟。

### 具体做法

先依次读入输入，因为换行符也会被识别成 `char` 类型，所以可以读入字符串依次遍历。对于每一个物体，可以建立一个**结构体**存储位置（绝对位置）和重量，并同时标记支点位置。一次遍历后，一次对于结构体数组中的数据求出两边力矩相比较即可。

### AC代码

```cpp
#include <iostream>
using namespace std;
string s; 
struct item { //建立结构体
	int weight;
	int pos;
}a[1000005];
int acnt;
int main() {
	int point = 0;
	char s; string ss;
	int npos = 0;
	cin >> ss;
	for (int i = 0; i < ss.length(); i++) { //遍历字符串
		s = ss[i];
		npos++;
		if (s == '=') continue;
		if (s == '^') {
			point = npos;
		}
		if (s >= '0' && s <= '9') { //对于物体存储数据
			a[acnt].weight = s - '0';
			a[acnt++].pos = npos;
		}
	}
	long long leftm = 0, rightm = 0; //注意这里要用long long，题面有提示
	for (int i = 0; i < acnt; i++) {
		if (a[i].pos < point) { //累加力矩
			leftm += (point - a[i].pos) * a[i].weight;
		} else if (a[i].pos > point) {
			rightm += (a[i].pos - point) * a[i].weight;
		}
	}
	if (leftm == rightm) { //比较并输出
		cout << "balance" << endl;
		return 0;
	}
	cout << (leftm > rightm ? "left" : "right" ) << endl;
	return 0;
}
```

这么认真不留个赞再走嘛~

管理大大求过

完结撒花

---

## 作者：qprzhzz (赞：0)


# CF376A Lever 题解

# 题意
这道题要你判断杠杆两边平不平衡，如果左边重量大于右边重量输出 `left` ，如果右边重量大于左边重量输出 `right` ，否则输出 `balance` 。
# 分析

杠杆又分称费力杠杆，省力杠杆和等臂杠杆，杠杆原理也称为“杠杆平衡条件”。要使杠杆平衡，作用在杠杆上的两个力矩（力与力臂的乘积）大小必须相等。即：动力×动力臂=阻力×阻力臂，用代数式表示为 $F1 \times L1=F2 \times L2$ ；式中， `F1` 表示动力， `L1` 表示动力臂，`F2` 表示阻力，`L2` 表示阻力臂。![杠杆原理图](https://iknow-pic.cdn.bcebos.com/8cb1cb13495409239b2a07f89858d109b2de49f0)

所以对于这道题，因为杠杆一开始是平衡的，所以我们分别求出左边重量与右边重量，再对比，这道题就切了。

废话不多说，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans1=0,ans2=0;//ans1判断左边重量，ans2判断右边重量
string a;
int main()
{
	cin>>a;
	int len=a.size();
	int balance;
	for(balance=0;a[balance]!='^';balance++);
	for(int i=0;i<len;i++)
	{
		if(i<balance)
		{
			if(isdigit(a[i])) ans1+=(a[i]-'0')*(balance-i);
	    }
		else if(i>balance)
		{
			if(isdigit(a[i])) ans2+=(a[i]-'0')*(i-balance);
		}
	}
	if(ans1==ans2)
	{
		printf("balance");
		return 0;
	}
	else if(ans1>ans2)
	{
		printf("left");
		return 0;
	}
	else
	{
		printf("right");
		return 0;
	}
}
```


---

## 作者：MeowScore (赞：0)

## 题目大意

给定一根杠杆，已知支点和各个位置的物重情况（当然可能什么都没有），判断杠杆的平衡情况。

## 解决问题

~~恶评！建议降红！~~

首先需要用到whk知识——杠杆原理。写成文字就是“动力臂乘动力臂等于阻力臂乘阻力臂”，写成公式：

$$F_1L_1=F_2L_2$$

对于此题有多个物体，只要把一侧的物体的重分别乘上各自到支点的距离，求和即可，最后比较两边。由于不记杠杆自重，初始杠杆是平衡的，力臂长度可以看做对应物体到支点的距离。

读入一个字符串，跑一次循环找到支点的位置。设支点位置为 $o$，字符串长度为 $len$。我们设出 $lsum$ 和 $rsum$，可以求出：


$$lsum=\sum_{i=0}^{o-1}F_iL_i$$


$$rsum=\sum_{i=o+1}^{len-1}F_iL_i$$

如果当前位置是‘=’，那么这里的 $F_i=0$。

比较 $lsum$ 和 $rsum$ 哪边大哪边下沉。


## 上代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	char a[1000010];
	gets(a);
	unsigned long long lsum=0;
	unsigned long long rsum=0;
	int o;
	int len=strlen(a);
	int i;
	for(i=0;i<len;i++){
		if(a[i]=='^'){
			o=i;
			break;
		}
	}
	unsigned long long G;
	for(i=o-1;i>=0;i--){
		if(a[i]=='=')
			continue;
		G=a[i]-'0';
		lsum+=G*(o-i);
	}
	for(i=o+1;i<len;i++){
		if(a[i]=='=')
			continue;
		G=a[i]-'0';
		rsum+=G*(i-o);
	}
	if(lsum==rsum)
		puts("balance");
	if(lsum<rsum)
		puts("right");
	if(lsum>rsum)
		puts("left");
	return 0;
}
```


---

