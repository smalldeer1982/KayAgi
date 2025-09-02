# Ksenia and Pan Scales

## 题目描述

Ksenia has ordinary pan scales and several weights of an equal mass. Ksenia has already put some weights on the scales, while other weights are untouched. Ksenia is now wondering whether it is possible to put all the remaining weights on the scales so that the scales were in equilibrium.

The scales is in equilibrium if the total sum of weights on the left pan is equal to the total sum of weights on the right pan.

## 样例 #1

### 输入

```
AC|T
L
```

### 输出

```
AC|TL
```

## 样例 #2

### 输入

```
|ABC
XYZ
```

### 输出

```
XYZ|ABC
```

## 样例 #3

### 输入

```
W|T
F
```

### 输出

```
Impossible
```

## 样例 #4

### 输入

```
ABC|
D
```

### 输出

```
Impossible
```

# 题解

## 作者：追梦之鲸 (赞：2)

本蒟蒻的第$014$篇题解。

[经典回顾CF382A](https://www.luogu.com.cn/problem/CF382A)

### 2021 05-16 11:03:17纪念最优解

此题一共有这几种可能的方案（$x$ 代表左边的重量，$y$ 代表右边的重量，$z$ 代表需要放上的重量）：

1. $x==y$

那么我们只要求需要放上的重量是否为偶数就完事了。

输出为下：

```c
for(int i=0;i<z/2;i++)cout<<b[i];
cout<<a;
for(int i=z/2;i<z;i++)cout<<b[i];
```

2. $x==y+z$

直接输出串1+串2就完事了。

3. $x+z==y$

直接输出串2+串1就完事了。

4. $x+y+z\mod2==0$

这个需要两个特判

一是 $x<=(x+y+z)/2$，二是$y<=(x+y+z)/2$

为什么呐？因为$(x+y+z)/2$是两边放完之后的长度，如果超过这个长度，那么就说明全放在一边也不行，所以就要输出``Impossible``

输出如下：

```c
for(int i=0;i<ban-x;i++)cout<<b[i];
cout<<a;
for(int i=ban-x;i<z;i++)cout<<b[i];
```

*****

其他就直接输出``Impossible``

### Code：
```c
#include<bits/stdc++.h>
using namespace std;
string a,b;
int x,y,z,n;

int main()
{
	cin>>a>>b;
    n=a.size();
	for(int i=0;i<n;i++)
	{//求左边的重量和右边的重量
		if(a[i]=='|')
		{
			x=i;//因为是从0开始的，所以不用-1
			y=n-x-1;
			break;
		}
	}
	z=b.size();
	if(x==y)
	{//第一种
		if(z%2!=0)return cout<<"Impossible",0;
		else
		{
			for(int i=0;i<z/2;i++)cout<<b[i];
			cout<<a;
			for(int i=z/2;i<z;i++)cout<<b[i];
		}
	}else if(x==y+z)
	{//第二种
		cout<<a<<b;
	}else if(y==x+z)
	{//第三种
		cout<<b<<a;
	}else
	{
		if((y+x+z)%2==0)
		{//第四种
			int ban=(y+x+z)/2;
			if(y>ban)return cout<<"Impossible",0;
			if(x>ban)return cout<<"Impossible",0;
			for(int i=0;i<ban-x;i++)cout<<b[i];
			cout<<a;
			for(int i=ban-x;i<z;i++)cout<<b[i];
		}
		else return cout<<"Impossible",0;//都不是就输出"Impossible"
	}
    return 0;
}
```

最后蟹蟹管理大大的审核Orz

---

## 作者：Noby_Glds (赞：1)

大佬们的代码都好长啊，在这里我分享一下我的思路。
### 思路：
首先要存储一开始天平两边的字符串，记为 $a$ 和 $b$，用 $p$ 来记录是否已经越过分隔符。

如果 $p$ 为 $0$，则该字符加入 $a$ 字符串，反之加入 $b$ 字符串。

再记录要放上去的字符串，记为 $d$。

接下来用 $zx$ 记录 $d$ 字符串的“中线”，就是指 $d$ 字符串中，下标为 $0$ 到 $zx-1$ 加入 $a$ 字符串，剩下的加入 $b$ 字符串。

求 $zx$ 的公式为，$d$ 的长度减去 $a$ 的长度再加上 $b$ 的长度的值除以 $2$（可以自己尝试推导一下）。

可还有 $\texttt{Impossible}$ 的情况啊，没关系，比较 $a$ 和 $b$ 的长度就可以了，如果不一样。就是 $\texttt{Impossible}$。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int p,lena,lenb,lend,zx;
string a,b,c,d;
int main(){
	cin>>c>>d;
	lend=d.size();
	for(int i=0;i<c.size();i++){
		if(c[i]!='|'&&p==0) a+=c[i],lena++;
		if(c[i]!='|'&&p==1) b+=c[i],lenb++;
		if(c[i]=='|') p=1;
	}
	zx=(lend-lena+lenb)/2;
	for(int i=0;i<zx;i++) a+=d[i],lena++;
	for(int i=zx;i<d.size();i++) b+=d[i],lenb++;
	if(lena!=lenb){
		cout<<"Impossible";
		return 0;
	}
	cout<<a<<"|"<<b;
	return 0;
}
```
$\texttt{165ms}$，庆祝最优解第二！

---

## 作者：Otue (赞：1)

蒟蒻又来发题解了，大佬们的代码好短啊，我看不懂，这里展示特别暴力的代码。

#### 第零步

定义 string 类型的 $a$ 和 $b$，分别表示第一行和第二行。

设 $b$ 字符串长度为 bbbb。
#### 第一步
首先找到 `|` 的位置，这个不用多说。
```cpp
for(int i=0;i<a.size();i++){
	if(a[i]=='|'){
		eee=i;//用一个变量记录
		s=1;//标记为已经找到了此字符
	}
	if(a[i]!='|'){
		if(s==1){
			y++;//y表示|后面字符的个数
		}
		if(s==0){
			x++;//x表示|前面字符的个数
		}
	}
}
```

#### 输出 Impossible(1)

什么情况不符合标准呢？

题目中说天平两边的字符串个数相等，所以 $a+b-1$ 必须是偶数。

#### 输出 Impossible(2)
还有没有不符合标准的呢？当然有啦！

比如样例4给出的情况：

$y+bbbb<x$

```cpp
if(x>y){
	if(bbbb+y<x){
		cout<<"Impossible"<<endl;
		return 0;
	}	
}
if(x<y){
	if(bbbb+x<y){
		cout<<"Impossible"<<endl;
		return 0;
	}
}
```
#### 几种特殊情况(1)
当 $x=y$ 的时候

```c++
if(x==y){
	for(int i=0;i<eee;i++){
		cout<<a[i];
	}
	for(int i=0;i<bbbb/2;i++){
		cout<<b[i];
	}
	cout<<'|';
	for(int i=eee+1;i<a.size();i++){
		cout<<a[i];
	}
	for(int i=bbbb/2;i<bbbb;i++){
		cout<<b[i];
	}
	cout<<endl;
	return 0;
}
```
#### 几种特殊情况(2)
当 $x=0,y=0$ 时:
```cpp
if(x==0&&y==0){
	if((x+y+bbbb)%2==0){
		for(int i=0;i<=bbbb/2-1;i++){
			cout<<b[i];
		}
		cout<<"|";
		for(int i=bbbb/2;i<bbbb;i++){
			cout<<b[i];
		}
		cout<<endl;
	}
	return 0;
}
```
#### 正常情况讨论(1)
当 $x>y$ 时：
```cpp
if(x>y){
	xx=(bbbb-(x-y))/2;//xx表示x加上字符串的数量
	yy=(bbbb+x-y)/2;//yy表示y加上字符串的数量
	for(int i=0;i<eee;i++){
		cout<<a[i];
	}
	for(int i=0;i<xx;i++){
		cout<<b[i];//加上去
	}
	cout<<'|';
	for(int i=eee+1;i<a.size();i++){
		cout<<a[i];
	}
	for(int i=xx;i<bbbb;i++){
		cout<<b[i];//加上去
	}
	cout<<endl;
	return 0;
} 
```
#### 正常情况讨论(2)
当 $x<y$ 时
```cpp
if(x<y){
	xx=(bbbb+(y-x))/2;
	yy=(bbbb-y+x)/2;
	for(int i=0;i<eee;i++){
		cout<<a[i];
	} 
	for(int i=0;i<xx;i++){
		cout<<b[i];
	}
	cout<<'|';
	for(int i=eee+1;i<a.size();i++){
		cout<<a[i];
	}
	for(int i=xx;i<bbbb;i++){
		cout<<b[i];
	}
	cout<<endl;
	return 0;//同上
} 
```
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
string b;
bool s;
int x,y;
int xx,yy;
int eee;
int main(){
	getline(cin,a);
	getline(cin,b);
	int bbbb=b.size();
	for(int i=0;i<a.size();i++){
		if(a[i]=='|'){
			eee=i;
			s=1;
		}
		if(a[i]!='|'){
			if(s==1){
				y++;
			}
			if(s==0){
				x++;
			}
		}
	}
	if((x+y+bbbb)%2!=0){
		cout<<"Impossible"<<endl;
		return 0;
	}
	
	if(x>y){
		if(bbbb+y<x){
			cout<<"Impossible"<<endl;
			return 0;
		}
	}
	if(x<y){
		if(bbbb+x<y){
			cout<<"Impossible"<<endl;
			return 0;
		}
	}
	if(x==y){
		for(int i=0;i<eee;i++){
			cout<<a[i];
		}
		for(int i=0;i<bbbb/2;i++){
			cout<<b[i];
		}
		cout<<'|';
		for(int i=eee+1;i<a.size();i++){
			cout<<a[i];
		}
		for(int i=bbbb/2;i<bbbb;i++){
			cout<<b[i];
		}
		cout<<endl;
		return 0;
	}
	if(x==0&&y==0){
		if((x+y+bbbb)%2==0){
			for(int i=0;i<=bbbb/2-1;i++){
				cout<<b[i];
			}
			cout<<"|";
			for(int i=bbbb/2;i<bbbb;i++){
				cout<<b[i];
			}
			cout<<endl;
		}
		return 0;
	}
	int t=(x+y+bbbb)/2;//t表示每边因该分的数量 
	if(x>y){
		xx=(bbbb-(x-y))/2;
		yy=(bbbb+x-y)/2;
		for(int i=0;i<eee;i++){
			cout<<a[i];
		}
		for(int i=0;i<xx;i++){
			cout<<b[i];
		}
		cout<<'|';
		for(int i=eee+1;i<a.size();i++){
			cout<<a[i];
		}
		for(int i=xx;i<bbbb;i++){
			cout<<b[i];
		}
		cout<<endl;
		return 0;
	} 
	if(x<y){
		xx=(bbbb+(y-x))/2;
		yy=(bbbb-y+x)/2;
		for(int i=0;i<eee;i++){
			cout<<a[i];
		} 
		for(int i=0;i<xx;i++){
			cout<<b[i];
		}
		cout<<'|';
		for(int i=eee+1;i<a.size();i++){
			cout<<a[i];
		}
		for(int i=xx;i<bbbb;i++){
			cout<<b[i];
		}
		cout<<endl;
		return 0;
	} 
	cout<<"Impossible"<<endl;
} 
```

---

## 作者：hensier (赞：1)

本题为字符串题。我们先读入两个字符串$s,t$，找到第一个字符串`|`（竖线）字符的位置$line$，然后比较左右两边的大小。我们取左右两部分的子串$sa,sb$，统一让$|sa|\ge|sb|$。假如$|sb|^{*}+|t|<|sa|$，则不能往$sb$中加入字符使得$|sb|=|sa|$。否则就能够在第二个字符串中不断加入字符，使得两串长度相等，但此时可能有剩余。如果剩余的字符数为奇数，说明两者不能平衡。

$\text{C++}$代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t,sa,sb;
int line;
bool flag;
int main()
{
    cin>>s>>t;
    line=s.find('|');
    //s1.find(s2)可以查找s1内的字符串s2，查找不到的话就返回string::npos（一般为-1），否则返回s2第一次出现的位置
    sa=s.substr(0,line);//从下标0开始取子串，长度为line
    sb=s.substr(line+1);//从下标line+1开始取子串，直到字符串结束
    if(sa.size()<sb.size())//交换位置，使得|sa|>=|sb|
    {
        swap(sa,sb);
        flag=true;//flag记录是否交换了位置
    }
    if(sb.size()+t.size()<sa.size())//特判
    {
        puts("Impossible");
        return 0;
    }
    while(!t.empty()&&sa.size()!=sb.size())//empty函数判断一个字符串是否为空
    {
        sb+=t[0];//把t的第一个字符不断加入sb中
        t.erase(0,1);//擦除t的第一个字符
    }
    if(t.size()&1)//a&1等同于a%2，判断t剩余字符个数是否为奇数
    {
        puts("Impossible");
        return 0;
    }
    for(int i=0;t[i];i++)//如果是偶数的话，每次两个字符——一个加入到sa，一个加入到sb
    {
        if(i&1)sa+=t[i];
        else sb+=t[i];
    }
    if(flag)swap(sa,sb);//如果之前交换了位置，那么就要换回来
    cout<<sa<<'|'<<sb;//输出两个字符串，中间用分隔线隔开
    return 0;
}
```

当然，本题还可用$Python$练手（注意$Python$没有字符类型）：

```python
import sys//相当于头文件，用于使用sys.exit()，即退出程序
def find(x, y):
    for i in range(len(x)):
        if x[i] == y[0]:
            return i
def substr(x, y, z):
    a = ''
    for i in range(y, z):
        a += x[i]
    return a
def erase(x)://自定义系统没有的函数
    a = ''
    for i in range(1, len(x)):
        a += x[i]
    return a
s = str(input())
t = str(input())//输入
line = find(s, '|')//调用函数查找
sa = substr(s, 0, line)
sb = substr(s, line + 1, len(s))//取子串
flag = False//flag初始为False
if len(sa) < len(sb):
    sa, sb = sb, sa//Python可直接实现交换
    flag = True
if len(sb) + len(t) < len(sa)://特判
    print('Impossible')
    sys.exit()
while len(t) > 0 and len(sa) != len(sb)://字符串操作
    sb += t[0]
    t = erase(t)
if len(t) & 1://特判
    print('Impossible')
    sys.exit()
for i in range(len(t))://向两端加入字符
    if i & 1:
        sa += t[i]
    else:
        sb += t[i]
if flag://交换回去
    sa, sb = sb, sa
print(sa, end = '|')
print(sb)//输出
```

$\text{*:|s|表示s的长度，即s.size()。}$

---

## 作者：Katsura_Hinagiku (赞：1)

每个物品重量都为1，因此左右添加那些物品都无关紧要。先求出天平左右物品重量分别是多少，再考虑如何添加使其平衡即可。

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string s1,s2;
int l=0,r=0;
int main()
{
	cin>>s1;
	cin>>s2;
	bool p=0;
	for(int i=0;i<s1.length();++i)
	{
		if(s1[i]=='|')
		{
			p=1;
			continue;
		}//左右的划分
		if(!p)//天平左侧
		{
			++l;
		} 
		else//天平右侧 
		{
			++r;
		}
	}
	if((l+r+s2.length())%2)
	{
		printf("Impossible\n");
		return 0;
	}//总共有奇数个物品，无法让天平平衡
	if(s2.length()<abs(l-r))
	{
		printf("Impossible\n");
		return 0;
	}//全放在轻的一侧也无法使天平平衡
	int res=abs(l-r);//两侧物品重量差 
	int pos=0;
	for(int i=0;i<s1.length();++i)
	{
		if(s1[i]=='|')
		{
			if(l<r)
			{
				for(pos;pos<res+(s2.length()-res)/2;++pos)
				{
					printf("%c",s2[pos]);
				}
			}
			else
			{
				for(pos;pos<(s2.length()-res)/2;++pos)
				{
					printf("%c",s2[pos]);
				}
			}//闲置物品中放左边的 
		}
		printf("%c",s1[i]);
	} 
	for(pos;pos<s2.length();++pos)printf("%c",s2[pos]);//闲置物品中放右边的 
	return 0;
}
```

---

## 作者：xiezihanAKIOI (赞：0)

看了各位大佬的做法，感觉有点麻烦。这里分享一下我的思路。
（话说 15ms 应该是最优解了吧。）

首先，我们可以调用 string 里面的函数 find 来搜索 "|" 的位置。就可以获取 "|" 前面字符的数量和后面字符的数量。然后我们在获取我们可以放到天平上面的字母的数量。如果可以放到天平上的字母大于两边字符的差并且所有字母加起来是偶数，那就是有解的。

注：查找前后字符数量的时候要减去 "|" 的数量。

```
#include <bits/stdc++.h>

using namespace std;

string s, str;

signed main () {
	ios::sync_with_stdio (false), cin.tie (0), cout.tie (0);
	cin >> s;
	int cnt1 = s.find ('|'); //查找前面字符的数量 。 
	int cnt2 = s.size () - cnt1 - 1; //后面字符的数量。 
	cin >> str;
	int k = str.size (); //获取可以加的字母的数量。 
	if (!((k - abs (cnt1 - cnt2)) & 1) && k >= abs (cnt1 - cnt2)) { //如果有解。 
		int maxn = (cnt1 + cnt2 + k) >> 1; //计算两边放几个字母。 
		for (int i = 0 ; i < cnt1 ; i++) cout << s[i]; //前面原本有的字符。 
		for (int i = 0 ; i < maxn - cnt1 ; i++) { //前面要加的字母。 
			cout << str[i];
		}
		for (int i = cnt1 ; i < s.size () ; i++) cout << s[i]; //后面原本有的字母。 
		for (int i = maxn - cnt1 ; i < str.size () ; i++) cout << str[i]; //后面要加的字母。 
	}
	else cout << "Impossible"; //无解 
	return 0;
}
```

---

## 作者：kaceqwq (赞：0)

# 题目大意：
一架天平,中间有一个 ‘|’ 作为分隔符，分割左盘和右盘。天平上面放有一些字母，准备放上去一些字母使得天平平衡。每个字母的重量都是 1 。输出任意一种使得天平平衡的方案，否则输出 ‘Impossible’ 。

# 分析：
首先根据题意我们就可以知道，这道题的主要思路和算法就是**模拟**，接下来根据题意模拟：先输入两个字符串，分别表示现在天平上的情况，和准备放上去的一些字母，接着我们可以先找出天平的分割线 ‘|’ 的位置，因为每个字母的重量都为 1 ，所以无需考虑字母的特殊性（也就是说，摆放的方案对于任意输入的字母都适用），然后思考便可得出摆放的以下几种情况，接下来根据情况判断，输出即可。

设分割线 ‘|’ 左边部分为 L ，右边部分为 R 。

### 第一种：L的重量==R的重量
如果准备放上去的字符串重量为奇数，那么一定不可能，输出 “Impossible” 。  
否则在天平上两边各放上一半的字符串。

### 第二种：L的重量 - R的重量 == 准备放上去的字符串重量
直接把所有字符串放在天平右边即可。

### 第三种：R的重量 - L的重量 == 准备放上去的字符串重量
直接把所有字符串放在天平左边即可。

### 第四种：L的重量 + R的重量 + 准备放上去的字符串重量 为偶数时
这样就说明在天平两边放入若干字符串也可以使天平保持平衡。先求出如果天平平衡，天平两边的重量，如果原来 L的重量或 R的重量 大于天平平衡的重量，那么不可能是由后面放入字符串得到的，就输出 “Impossible” 。否则天平左边放上
（天平平衡的重量 - 原来左边的重量）的字符串，右边同理。

# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int l,r,lenb,lena;
int main()
{
	cin>>a>>b;
    lena=a.size();   //lena为原来天平的长度
    lenb=b.size();   //lenb为准备放入字符串的重量
	for(int i=0;i<lena;i++)
	{
		if(a[i]=='|')
		{
			l=i;   //l为左边的重量
			r=lena-l-1;   //r为右边的重量
			break;
		}
	}
	if(l==r)  //第一种
	{
		if(lenb%2!=0)   //如果lenb为偶数，直接输出“Impossible”
		{
		cout<<"Impossible"<<'\n';  
		return 0;
		}
		for(int i=0;i<lenb/2;i++)
		cout<<b[i];
		cout<<a;
		for(int i=lenb/2;i<lenb;i++)
		cout<<b[i];
		cout<<'\n';
		return 0;
	}
	if(l-r==lenb)	//第二种
	{
	cout<<a<<b<<'\n';  //直接输出原来的天平和准备放上的字符串
	return 0;
	}
	if(r-l==lenb)   //第三种
	{
	cout<<b<<a<<'\n';   //直接输出准备放上的字符串和原来的天平
	return 0;
	}
	if((r+l+lenb)%2==0)   //第四种
	{
		int sum=(r+l+lenb)/2;   //如果全部字符串加起来的一半
		if(r>sum||l>sum)   
		{
		cout<<"Impossible"<<'\n';
		return 0;
		}
		for(int i=0;i<sum-l;i++)
		cout<<b[i];
		cout<<a;
		for(int i=sum-l;i<lenb;i++)
		cout<<b[i];
		cout<<'\n';
		return 0;
	}	
	cout<<"Impossible"<<'\n';
    return 0;
}

```


---

## 作者：xkcdjerry (赞：0)

看到没有用`char`数组的人，我来一发：  
主要人们用`string`都是 ~~屑CodeForces~~ 这道题 没有明确写数据范围所以以为可以随便开，但是观察可以发现  
> It is guaranteed that all the English letters in the input data are different. It is guaranteed that the input does not contain any extra characters.  

（大意为只有二十六个大写英语字母而且互相不重复）

那么无论怎么拼接字符串长度最多是 26 实际要开到 27 来容纳 NUL 字符，这里开到 30 保险一下。  

那么这里看见要让两边相同又有 $n \leqslant 26$ 直接想到模拟：由于每个字母重量都为 1 可以思考时忽略每个之间的区别。  

那么类比人类平衡天平的过程先给小的加，由于要求一直加完，所以两个重量一样就随便给一个盘（因为忽略字母之间区别之后两个盘是完全相同的）  

那么就可以快乐写出线性的模拟代码了~  

（相信你们一看就会）
```
#include <cstdio>
//因为只有26个大写英文字母所以长度最多为26
#define N 30

//懒人缩写法（读一个字符和判断是不是A~Z）
#define GC ch=getchar()
#define VAILD (ch>='A'&&ch<='Z')

char l[N],r[N],t[N];
int a,b,c;
int main()
{
	int ch;
	//读第一个字符串
	for(GC;VAILD;GC)
		l[a++]=ch;
	//ch现在存的是'|'所以读第二个
	for(GC;VAILD;GC)
		r[b++]=ch;
	//由于可能Windows下生成产生\r\n再读一下去除
	for(GC;!VAILD;GC)
		;
	//读第三个字符串
	for(;VAILD;GC)
		t[c++]=ch;
	//每次给最少的
	for(int i=0;i<c;i++)
	{
		if(a<b) l[a++]=t[i];
		else r[b++]=t[i];
	}
	//如果长度相等报答案，否则Impossible
	if(a==b) printf("%s|%s",l,r);
	else puts("Impossible");
	return 0;
}
```
后注：  
写完之后突然想到实际上减来模去的那些按长度算的代码因为要读入实际上和这个复杂度一样都是线性的，而且因为这个用了`char`反而比他们的快好多。  

 [Luogu记录](http://codeforces.com/problemset/submission/382/118010386)  
因为Luogu一直Waiting贴上对应的[CF记录](http://codeforces.com/problemset/submission/382/118010386) (31ms)  
可以用看到甩了（这篇文章写的时候的）最优解285ms八条街。

---

## 作者：nalemy (赞：0)

## 目标

给你一个字符串形式的天平和一堆物品，让你把所有物品堆中的物品往天平上放。

试问天平能否平衡。如果能，输出操作后的天平。

## 分析

主要有如下几个重点：

- 字符串的解析
- 放上物品后判断天平是否平衡

首先，这道题给你的这堆物品的重量都为 $1$，所以东西无关紧要，我们只需统计天平两端物品的数目。

而表示天平的这个字符串用 `|` 分割，所以 `|` 所在的位置就是天平左半部分的物品数量（因为字符串下标从 $0$ 开始）。

而我们放上去**不平衡**无非有两种情况：

1. 天平上某一端的物品个数已经超过了目标物品个数；
2. 天平上和物品堆里的东西总和是奇数，就算全放上去了也无法平衡。

所以我们分别对它进行判定就好啦！

## 代码

~~码风巨丑 勿喷~~

```C++
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int main() {
    string s, t; cin >> s >> t; int l, r, a, b, c;
    l = s.find('|'), r = s.size() - l - 1;
    a = abs(l - r), b = t.size(), c = l + r + b >> 1;
    if (c < l || c < r || (a ^ b) & 1) cout << "Impossible";
    else cout << t.substr(0, c-l) << s << t.substr(c-l);
    return 0;
}
```

## 补充

代码中运用到了 C++ 字符串中的两个方法。

### find 方法

返回某个字符在字符串中**第一次出现**的位置。

1. `s.find(c)` 返回字符串中第一次出现 $c$ 的位置（下标从 $0$ 开始）；
2. `s.find(c, pos)` 返回字符串中 $pos$ 位置之后第一次出现 $c$ 的位置。

### substr 方法

返回某个字符串的子串。

1. `s.substr(s, l)` 返回从 $s$ 开始的 $l$ 个字符组成的字符串；
2. `s.substr(s)` 返回从 $s$ 开始到结尾的字符串。


---

## 作者：CobaltChloride (赞：0)

```
/*依旧是暴力,求出左右重量,比较添加
#include<bits/stdc++.h>
using namespace std;
int suml,sumr,remain,i,j,l,used;
string s,t;
int main(){
	cin>>s>>t;
	l=s.length();
	for(i=0;i<l;i++){
		if(s[i]=='|'){
			suml=i;
			break;
		}
	}
	sumr=l-suml-1;
	//求出两部分重量 
	remain=t.length();
	if(abs(suml-sumr)>remain/*相差过大,不够补*/||(suml+sumr+remain)&1/*总个数分不成相等两部分*/) cout<<"Impossible";
	else{//构造串 
		if(suml<sumr) s.insert(0,t,0,sumr-suml),/*从s的最左端插入字符*/used+=sumr-suml;
		if(suml>sumr) s.insert(l,t,0,suml-sumr),/*在s的最右端添上字符*/used+=suml-sumr;
		//used:已用去字符个数 
		for(i=used;i<remain;i+=2){
			s.insert(0,t,i,1);//左端插入 
			s.insert(s.length(),t,i+1,1);//右端添上 
		}
		cout<<s;
	}
	return 0;
}
```

---

