# [ABC073C] Write and Erase

## 题目描述

你和 joisino 姐姐正在玩如下的游戏。

- 一开始，有一张什么都没有写的纸。
- joisino 姐姐每次说一个数字，如果该数字已经写在纸上，就把它从纸上擦掉；如果没有写在纸上，就把它写上。这个过程重复 $N$ 次。
- 最后，请回答纸上还剩下多少个数字。

给定 joisino 姐姐依次说出的数字 $A_1,\ldots,A_N$，请你在游戏结束后，输出纸上剩下的数字个数。

## 说明/提示

## 限制条件

- $1 \leq N \leq 100000$
- $1 \leq A_i \leq 1000000000 (=10^9)$
- 输入均为整数。

## 样例解释 1

操作如下：

- 纸上没有 $6$，写上 $6$。
- 纸上没有 $2$，写上 $2$。
- 纸上有 $6$，擦掉 $6$。

因此，最后纸上只剩下 $2$，答案为 $1$。

## 样例解释 2

最后纸上也有可能一个数字都没有。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
6
2
6```

### 输出

```
1```

## 样例 #2

### 输入

```
4
2
5
5
2```

### 输出

```
0```

## 样例 #3

### 输入

```
6
12
22
16
22
18
12```

### 输出

```
2```

# 题解

## 作者：封禁用户 (赞：4)

#### 好像蒟蒻的代码是题解里最好懂的

蒟蒻的思想就是算有几个数是无用的

如果一个数出现过偶数次，那它就是添不进去的

code:
```
#include<bits/stdc++.h>
using namespace std;
int a[1000010];
long long ans,n;//定义及表头
int main(void)
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);//排个序，方便找数（因为Ai的范围是10的9次方）
	for(int i=1;i<n;)这里i不用++,下面判断完再++
		if(a[i]==a[i+1]) ans+=2,i+=2;
      //如果这两个数是一样的话,无用数累计的变量就+2，i也+2
			else i++;//不然的话，这个数就添得进去,所以i+1
	cout<<n-ans<<"\n";//用总数字数量-无用数字数量，就是添进去的个数
	return 0;
}
```
管理员求过，给个[滑稽官网](http://lvmaojun.com/huaji/),再赠送一枚滑稽币：

![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1574845639140&di=9de8f79412fbad25e59751d986495fe9&imgtype=jpg&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20180831%2F19480eff63ea4351bf9db975d466b2bb.jpeg)



---

## 作者：wzw_ (赞：3)

# ~~看大佬们的方法都好麻烦啊~~
本人是一遍循环做的，简单易懂。
附上程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100002],z,zs;//z是出现奇数次，还是偶数次，zs是留下了多少个数
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	  cin>>a[i];
	sort(a+1,a+n+1);//输入排序不解释
	z=1;//初值定1，方便以后运算
	for(int i=2;i<=n;i++)//因为和前一个比较，所以从2开始。
	{
		if(a[i]==a[i-1])z=(z+1)%2;//相等则加一个，看看是奇数次，还是偶数次，奇数次就还有，偶数次就没有。
		else zs+=z,z=1;//否则加上它，赋值为1。
	}
	if(z%2)zs++;//最后一次特判
    cout<<zs<<endl;//输出答案
	return 0;
}```

---

## 作者：李之恒 (赞：2)

# STL set大法好
这道题目其实可以用STL中的容器**set**做

[set容器具体实现](https://www.baidu.com/link?url=rTIQUuAaf0HfSrgwfQOzarFyzp5mmn6orZn-XSG2Uk2gfmg-wt29ZzHTMcy_qRAIpgENd-cn49O5alHrJK_n1-M-_1wUmZ2UVm5jibLuy-u&wd=&eqid=c9272ae500055a26000000045e5905c4)
### set本题使用函数及时间复杂度
**find**
 s.find(x),在集合中查找等于x的元素，并返回指向该元素的迭代器。若不存在，则返回s.end()。时间复杂度为O（log n）
 
**end**
 s.end()指向集合中尾元素下一个位置的迭代器。

**insert**
 s.insert(x)，把一个元素插入到集合中，并按从小到大自动排序（红黑树的特性）。时间复杂度为O（log n）
 
**erase（本题所用一类）**
 s.erase(x)，从集合s中删除所有等于x的元素。时间复杂度为O（k+log n）,其中k为被删除的元素个数
###  本题代码实现

结合以上内容，本题应该~~很容易~~解决了吧
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> con;
int main()
{
	int n,x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(con.find(x)!=con.end())
		    con.erase(con.find(x));
		else
		    con.insert(x);
	}
	printf("%d\n",con.size());
	return 0;
}
```

**希望大家能理解**


---

## 作者：智子·起源 (赞：1)

## 在讲这道题有史以来最简单的方法之前，我来讲一下输出样例 2 为什么啥都没有。

### 其实输出的答案应该是0（加个换行），但由于操作符的混合问题，（0和换行）所以样例就什么都没有。

大家理解就行。

emmm……这道题直接暴枚，比较简单。

上程序，如果看不懂的话可以看看注释：
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
int a[100000],n,t,ans;
int main()
{
  scanf("%d",&n);
  for(int i=0;i<n;i++)scanf("%d",&a[i]);
  sort(a,a+n);a[n]=2100000000;//给读入的数据排序。
  for(int i=0;i<n;i++)
  {
    ++t;//把当前数字出现的次数累加
	if(a[i]!=a[i+1])//如果这是这个数出现的最后一次
	{
	  if(t%2==1)++ans;//如果这个数的出现次数是奇数（最终这个数还是存在在数列里的），数列长度累加
	  t=0;//继续统计下一个数。（将出现次数统计清0）
	}
  }
  printf("%d\n",ans);//输出队列长度。
  return 0;
}
```


---

## 作者：CZQ_King (赞：1)

这道题用数组计数也是有可能的。

但是这里用``map``。

因为这里$n$最大只可能是$100000$。所以``map``最多只会开$100000$的空间，因此不会$MLE$。

------------
``map``定义：``map<下标类型,存储类型>名字;``例：``map<string,bool>mp;``

``map``的插入与普通数组一样：``名字[下标]=值``。注意下标的类型要和``下标类型``一样；值的类型要和``储存类型``一样。

**注意：只要访问``map``的某一个元素，如果之前没有开过这个元素的空间，``map``就会开这个空间**

------------
代码：
```
#include<bits/stdc++.h>
using namespace std;
map<int,int>t;//定义map
int n,a,s;
main(){
	cin>>n;
	while(cin>>a){//缩短代码
		s+=t[a]*-2+1;
        /*
        如果这个元素本来就存在(数组为1)说明最终要减去一个(-1)
        如果不存在(数组为0)就说明要增加一个(+1)
        那么1变-1；0变1。就推出这个式子
        */
		t[a]=!t[a];//0变1,1变0，相当于有的删掉没的添加
	}
	cout<<s<<endl;
}
```

---

## 作者：lyclyc_NSP (赞：1)

我又要来发布一篇新鲜出炉的题解了，我先来分析下题目的意思，题目说两个人轮流写一个数字，如有前面重复出现的数字就删掉，看看最后剩下多少数字？

### 1、这里我最先想到的是数组统计，但是数据范围是在太大了，1亿，会爆的！！！
### 2、所以我采用了第二个方法数组压缩统计，这样就不怕了，然后看看哪一个书出现的次数是奇数次就统计。
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,z,a[100005],c;
struct haha//结构体
{
	long long s,gs;
}f[100005];
void quchong()//去重过程
{
	f[1].s=a[1];f[1].gs=1;c=1;
	for(int i=2;i<=n;i++)//去重
	{
		if(a[i]!=a[i-1])//如果不相等便新开一个数组装下，否则便个数++
		f[++c].s=a[i],f[c].gs=1;
		else f[c].gs++;
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+n+1);
	quchong();//调用过程
	for(int i=1;i<=c;i++)
	if(f[i].gs%2==1)z++;//如果出现奇数次便统计
	cout<<z<<endl;
	return 0;
}
```
大家看了我的题解是否明白了呢？~~期待~~！

---

## 作者：yzhang (赞：1)

###### **模拟+数据结构！！！**
（滑稽）
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	set <int> s;//集合大法好！
	while(n--)
	{
		int x;
		cin>>x;
		if(s.find(x)!=s.end())
			s.erase(x);//有了，删除！
		else
			s.insert(x);//没有，添加！
	}
	cout<<s.size();//打印输出集合里元素的个数！
	return 0;
 } 
```

---

## 作者：rui_er (赞：0)

刚刚看了下面的题解，貌似有桶排的有set的，那么我就要用map了！（连map都没人用吗？）

# 头文件

```cpp
#include <iostream>
#include <map>
using namespace std;
```

# 准备阶段——输入

```cpp
map<int, bool> have;
int n;
cin>>n;
int k;
for(int i=0;i<n;i++) 
{
	cin>>k;
    //剩下的下一阶段介绍
}
```

have是一个以int类型为索引存储bool类型的map。
根据题意可以写出输入部分：输入询问个数n，再输入n个询问内容k。

# 判断出现与否

```cpp
for(int i=0;i<n;i++) 
{
	cin>>k;
	if(have[k]) have.erase(k);//$
	else have[k] = true;//%
}
```

其中$行表示，如果k出现过，就把它从have中删除；
%行表示，否则将它加入have中。

# 统计次数

```cpp
cout<<have.size()<<endl;
```

调用STL的统计大小的函数即可。

> 综合以上，得

```cpp
#include <iostream>
#include <map>
using namespace std;

map<int, bool> have;

int main()
{
	int n;
	cin>>n;
	int k;
	for(int i=0;i<n;i++) 
	{
		cin>>k;
		if(have[k]) have.erase(k);
		else have[k] = true;
	}
	cout<<have.size()<<endl;
	return 0;
}
```

---

