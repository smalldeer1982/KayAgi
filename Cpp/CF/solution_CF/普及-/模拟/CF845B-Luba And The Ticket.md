# Luba And The Ticket

## 题目描述

Luba 有一张票，上有六个数字。每一次操作时，她可以将其中一个数字改为任意一个数字。现在她希望知道最少需要操作多少次才可以将这张票上的数字改为一个幸运数字。 
当一个数的前三位之和与其后三位之和相等时，这便是一个幸运数字

## 说明/提示

样例1给出的数字本身即为幸运数字，因此操作数为 0 次  

样例 2 中仅需将 4、5 替换成 0 即可，很容易便看出最少需要操作 2 次  

样例 3 中仅需将任意一个 0 替换成 3，最少操作次数便是 1  

*以上即为题目简述，有不足之处请大家指出*

## 样例 #1

### 输入

```
000000
```

### 输出

```
0
```

## 样例 #2

### 输入

```
123456
```

### 输出

```
2
```

## 样例 #3

### 输入

```
111000
```

### 输出

```
1
```

# 题解

## 作者：xuyouchen (赞：3)

### 前言
这是一道CF上的题，但是难度不算太大，希望广大**OIer**在看题解之前再好好想想...  
*~~还有就是作者太菜了，怕写得不好~~*  
### 题目描述  
题目并不难理解，即给你两个数，每个数由三个数相加组成，问对于加数最少进行多少次操作才能使两个数相等  
#### 思路  
先看看两数相差了多少，然后看对于哪些数字操作最省事  
省事的定义：可以最大限度地改变这个数的数值（如果想让某数变大，加数越小越省事） 
*举个例子：*  
	使1+2+3 (6) 变大，操作1可使整个数变大8，而操作3只能使整个数变大6； 
*或*  
	使9+8+7 (24) 变小，操作9可使整个数变小9，而操作7只能使整个数变小7  

思路有了，剩下的是代码实现  
*如果您有了思路，再次请您关掉题解，继续思考~~~*  

### 代码  
您还是不理解，剩下的便是代码~  
*(代码较繁琐，为了让您看懂每一步)*  
~~因为作者太菜了，所以代码繁琐，以上是漂亮的借口...~~
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	char a[6];
	int ans=0,first=0,last=0,dif;
	int val[6];
	for(int i=0;i<3;i++)
	{
		scanf("%c",&a[i]);
		first+=(int)a[i]-48; 
	}

	for(int i=3;i<6;i++)
	{
		scanf("%c",&a[i]);
		last+=(int)a[i]-48;
	}
    // 通过char类型以获取每一个数字，同时获取前三个数之和与后三个数之和
    dif=abs(first-last);
    //获取相差的数值
	if(first<last)
	{
		for(int i=0;i<3;i++)
			val[i]=9-(int)a[i]+48;
		for(int i=3;i<6;i++)
			val[i]=(int)a[i]-48;
	}
	else{
		for(int i=0;i<3;i++)
			val[i]=(int)a[i]-48;
		for(int i=3;i<6;i++)
			val[i]=9-(int)a[i]+48;
	}
    //获取每一个数可被利用的价值
	sort(val,val+6,cmp);
    //先用价值多的，也可以认为是贪心
	for(int i=0;i<6;i++)
	{
		if(dif<=0)
			break;
		dif-=val[i];
		ans++;
	}
    //更改某一个数，最大化其价值
	printf("%d",ans);
	return 0;
}
```
代码到此结束了，有不足之处请您指出  
*另外，祝您coding愉快！！*

---

## 作者：伟大的王夫子 (赞：3)

一看到这道题，心想不是搜索水题嘛，数据也不大。

便想到用广搜进行求解。时间复杂度约为O(531441)，既9的六次方。

有些广搜的注意事项，就写在注释里了。
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string, int> d;//步数数组，顺便判重 
queue<string> q;//队列STL 
string st;
bool check(string s) {
	return s[0] + s[1] + s[2] == s[3] + s[4] + s[5];
}
int main() {
	cin >> st;
	q.push(st);
	d[st] = 0;
	//广搜 
	while (q.size()) {
		string x = q.front();
		q.pop();
		if (check(x)) {
			printf("%d\n", d[x]);
			break;
		}
		for (register int i = 0; i < x.size(); ++i) {
			for (register int j = '0'; j <= '9'; ++j) {
				string next = x;
				next[i] = j;
				if (d.find(next) == d.end()) q.push(next), d[next] = d[x] + 1;
				//要是没有访问过这个状态，插入队列 
			}
		}
	}
	//cout << d["123006"];
}
```
最后说一句：暴力出奇迹！

---

## 作者：LittleSnowy (赞：2)

~~这题就是一道大水题~~

我看到这题就想：~~暴力~~贪心

因为我们要把两边变得一样，那么如果把大的一半改为更大，显然更劣

我们要把更改最大化，即把小的改成9，大的改成0，如果两边大小关系发生改变，那就把9变小或把0变大到相等

所以我们得出一个重要结论：

## 若存在一个数满足把它改成9或0后，两边大小关系发生改变，那么可以在一步内令两边相等 ~~好显然啊~~

所以我们逐步贪心直至满足以上条件

上代码
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int x[7];
int cmp(){
	for(int i=1;i<=6;i++)
	for(int j=i+1;j<=6;j++)
	if(x[i]<x[j])swap(x[i],x[j]);
}
int main()
{
	int a[4],b[4],c[3]={0};
	
	char ch;
	for(int i=1;i<=6;i++){
		scanf("%c",&ch),c[(i+2)/3]+=(int)ch-48;
		if(i<=3)a[i]=(int)ch-48;
		else b[i-3]=(int)ch-48;
	}
	if(c[1]==c[2])return printf("0")&&0;
	if(c[1]>c[2]){
		int t=c[1]-c[2];
		for(int i=1;i<=3;i++)x[i]=a[i],x[i+3]=9-b[i];
		cmp();
		int ans=1,m=1;
		while(t>x[m])t-=x[m++];
		return printf("%d",m)&&0;
	}
	int t=c[2]-c[1];
	for(int i=1;i<=3;i++)x[i]=b[i],x[i+3]=9-a[i];
	cmp();
	int ans=1,m=1;
	while(t>x[m])t-=x[m++];
	return printf("%d",m)&&0;
}
```

Q：为什么用冒泡呢？

A：~~sort出问题了~~

---

## 作者：zxc57838706 (赞：0)

```cpp本蒟蒻第一次发题解，不知道说啥，代码很清晰了吧，凑合着看看吧
#include<bits/stdc++.h>
using namespace std;
bool cmp(int a,int b)
{
    return (a>b);
}
int main()
{
	string s;
	getline(cin,s);
	int m,n,a[10],b[10];
	for(int i=0;i<6;++i){
		a[i]=s[i]-'0';
	}
	m=a[0]+a[1]+a[2];
	n=a[3]+a[4]+a[5];
	int cnt=0;
	if(m==n){
		cout<<"0"<<endl;
		return 0;
	}
	else if (m<n)
	{
		   b[0]=9-a[0];
        b[1]=9-a[1];
        b[2]=9-a[2];
        b[3]=a[3];
        b[4]=a[4];
        b[5]=a[5];
        sort(b,b+6,cmp);
        int t=n-m;
        while(t>0) t-=b[cnt++];
        cout<<cnt<<endl;
	}
	else if(m>n)
	{
          b[0]=a[0];
          b[1]=a[1];
          b[2]=a[2];
          b[3]=9-a[3];
          b[4]=9-a[4];
          b[5]=9-a[5];
          sort(b+0,b+6,cmp);
          int t=m-n;
          while(t>0) t-=b[cnt++];
          cout<<cnt<<endl;
	}
	return 0;
}
```


---

