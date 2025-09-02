# Radio Station

## 题目描述

As the guys fried the radio station facilities, the school principal gave them tasks as a punishment. Dustin's task was to add comments to nginx configuration for school's website. The school has $ n $ servers. Each server has a name and an ip (names aren't necessarily unique, but ips are). Dustin knows the ip and name of each server. For simplicity, we'll assume that an nginx command is of form "command ip;" where command is a string consisting of English lowercase letter only, and ip is the ip of one of school servers.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF918B/ad878d2803e8a6ba1a8b3d8d599829e1c536a92a.png)Each ip is of form "a.b.c.d" where $ a $ , $ b $ , $ c $ and $ d $ are non-negative integers less than or equal to $ 255 $ (with no leading zeros). The nginx configuration file Dustin has to add comments to has $ m $ commands. Nobody ever memorizes the ips of servers, so to understand the configuration better, Dustin has to comment the name of server that the ip belongs to at the end of each line (after each command). More formally, if a line is "command ip;" Dustin has to replace it with "command ip; #name" where name is the name of the server with ip equal to ip.

Dustin doesn't know anything about nginx, so he panicked again and his friends asked you to do his task for him.

## 样例 #1

### 输入

```
2 2
main 192.168.0.2
replica 192.168.0.1
block 192.168.0.1;
proxy 192.168.0.2;
```

### 输出

```
block 192.168.0.1; #replica
proxy 192.168.0.2; #main
```

## 样例 #2

### 输入

```
3 5
google 8.8.8.8
codeforces 212.193.33.27
server 138.197.64.57
redirect 138.197.64.57;
block 8.8.8.8;
cf 212.193.33.27;
unblock 8.8.8.8;
check 138.197.64.57;
```

### 输出

```
redirect 138.197.64.57; #server
block 8.8.8.8; #google
cf 212.193.33.27; #codeforces
unblock 8.8.8.8; #google
check 138.197.64.57; #server
```

# 题解

## 作者：风格雨关 (赞：4)

这道题感觉像是一道十分高大上的题，但掐指一算，貌似十分简单

------------------------
（正文分割线）

------------------------
这道题我果断的选择了用c++里的map，
把IP当做key，然后把名字存进去，最后查询，输出


```
#include<bits/stdc++.h> //万能头文件
using namespace std;
map<string,string> ip;//定义map，注意IP是一个字符串
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		string a,b;
		cin>>b>>a;
		ip[a]=b;
	}
	for(int i=0;i<m;i++)
	{
		string b,a;
		cin>>b>>a;
		a=a.substr(0,a.size()-1);//注意，这里的查询后有一个分号，
        //而map里的IP中没有分号，所以要去分号
		cout<<b<<' '<<a<<"; #"<<ip[a]<<"\n";//但输出中要记得加分号
	}
	return 0;
}
```

---

## 作者：wangyilin (赞：2)

CF918B Radio Station题解
==
芝士点：字符串运用

思路：存入结构体后查找按格式输出

首先，定义一个结构体$Node$用来储存每一个ip及使用者：
```
struct Node{
	int a,b,c,d;
	string name;
}s[100005];
```
然后，按格式输入ip：
```
cin>>s[i].name>>s[i].a>>x>>s[i].b>>x>>s[i].c>>x>>s[i].d;
```
查找ip：
```
for(int j = 0;j<n;j++){//查找已有ip
		if(s[j].a==na&&s[j].b==nb&&s[j].c==nc&&s[j].d==nd)
```
最后按格式输出：
```
cout<<newname<<' '<<na<<'.'<<nb<<'.'<<nc<<'.'<<nd<<';'<<' '<<'#'<<s[j].name<<endl;
```

完整代码：

```
#include<bits/stdc++.h>
using namespace std;
struct Node//定义结构体来存储ip
{
	int a,b,c,d;//ip地址
	string name;//名字
}s[100005];//数组
char x;//字符x用来输入不需要的字符
int main()
{
	int n,m;
	cin>>n>>m;//输入n和m
	for(int i=0;i<n;i++)
    {
		cin>>s[i].name>>s[i].a>>x>>s[i].b>>x>>s[i].c>>x>>s[i].d;//输入ip地址
	}
	string newname;//查找名字
	int na,nb,nc,nd;//要查找的ip
	for(int i=0;i<m;i++)
  	{
		cin>>newname>>na>>x>>nb>>x>>nc>>x>>nd>>x;//输入要查找的ip
		for(int j = 0;j<n;j++)//查找已有ip
     	{
			if(s[j].a==na&&s[j].b==nb&&s[j].c==nc&&s[j].d==nd)//如果ip全部相等
            {
				cout<<newname<<' '<<na<<'.'<<nb<<'.'<<nc<<'.'<<nd<<';'<<' '<<'#'<<s[j].name<<endl;//输出
				break;//跳出循环优化运行时间
			}
		}
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有 $n$ 个形如 $a_i.b_i.c_i.d_i$ 的 IP 地址。有 $m$ 条命令，每条命令由一条字符串 $s$ 和一个形如 $p.q.r.s$ 的 IP 地址，你需要输出这个命令，并输出这个命令所指向的 IP 地址对应的名称。

**数据范围：$1\leqslant n,m\leqslant 1000,0\leqslant a_i,b_i,c_i,d_i,p,q,r,s\leqslant 255,1\leqslant|s|\leqslant 10$。**
## Solution
这题乍一看有些高大上，但看到这个数据范围之后，我就认定了这道题目只需要 $\mathcal{O}(nm)$ 的枚举就能够解决。具体怎么解决？很简单，输入完每一次命令，直接再在所有 $n$ 个 IP 地址中一个一个去找，看是否有和当前命令的 IP 地址相等的，一旦碰到相等的就直接输出就好了。
## Code
```cpp
string name[1007];
int n, m, a[1007], b[1007], c[1007], d[1007];

int main() {
	getint(n), getint(m);
	_for(i, 1, n) {cin >> name[i]; scanf("%d.%d.%d.%d", &a[i], &b[i], &c[i], &d[i]);}
	_for(i, 1, m) {
		string tmpname; int tmpa, tmpb, tmpc, tmpd;
		cin >> tmpname;
		scanf("%d.%d.%d.%d;", &tmpa, &tmpb, &tmpc, &tmpd);
		_for(j, 1, n)
			if(tmpa == a[j] && tmpb == b[j] && tmpc == c[j] && tmpd == d[j]) {
				cout << tmpname << ' ';
				writeint(tmpa), putchar('.');
				writeint(tmpb), putchar('.');
				writeint(tmpc), putchar('.');
				writeint(tmpd), putchar(';'), putchar(' '), putchar('#');
				cout << name[j] << endl;
				break;
			}
	}
	return 0;
}
```

---

## 作者：zilingheimei (赞：0)

蒟蒻来写题解了

先看题目：

[CF918B Radio Station](https://www.luogu.com.cn/problem/CF918B)


有 n 个形如 ai.bi.ci.di
  的 IP 地址。有 m 条命令，每条命令由一条字符串 s 和一个形如 p.q.r.s 的 IP 地址，你需要输出这个命令，并输出这个命令所指向的 IP 地址对应的名称。
  
------------

思路如下：

1. 将学校服务器中加上 ' ; ' ，方便与查找的服务区来对比
.
```cpp
struct sausage{
	string s,ip;
}a[1010],b[1010];
for(int i=1;i<=n;i++){
	cin>>a[i].s>>a[i].ip;
	a[i].ip+=';';//运用string可以直接添加
}
```


2. 如果查找到的IP地址IP相同，按题目要求输出，注意在 ' # ' 前面有空格

```cpp
for(int j=1;j<=m;j++){
	for(int i=1;i<=n;i++){
		if(a[i].ip==b[j].ip){
			cout<<b[j].s<<" "<<b[j].ip<<" #"<<a[i].s<<endl;
		}
	}
}
```


------------

主要代码已放，就不放完整了


---

## 作者：applese (赞：0)

这个题目不难，只是涉及到字符串的使用罢了QAQ，附上代码和解释：
```
#include<iostream>
using namespace std;
string name[10001],id[10001],check_name,check_id;
int main()
{
	int n,m;
	cin>>n>>m;    //输入n和m
	for(int i=1;i<=n;i++)
	{
		cin>>name[i]>>id[i];   //输入小写字母串及IP地址
	}
	for(int i=1;i<=m;i++)
	{
		cin>>check_name>>check_id;   //输入要查找的IP地址
		check_id.erase(check_id.size()-1,1);    //IP地址上会有“;”的符号，要先删除，以便查找QAQ
		for(int j=1;j<=n;j++)
		{
			if(id[j]==check_id)   //如果相同就输出
			{
				cout<<check_name<<" "<<check_id<<"; #"<<name[j]<<endl;   //按照题目要求输出
			}
		}
	}
	return 0;  //结束
}
```
如果您对本题解有疑问，请在右边回复，谢谢QAQ

---

