# A Serial Killer

## 题目描述

我们所深爱的侦探夏洛克，目前正试图抓住一个每天都要杀死一个人的强迫症杀手。通过运用其自身高超的推理能力，夏洛克目前对于凶手挑选下一位受害者的策略了然于心。
当第一天降临，杀手首先从两位潜在的受害者中随机挑选一位脸黑人士进行暗杀，并且每当一位潜在的受害者倒下，都会有另一人取代该受害者之位置，成为新的潜在受害者（幸免于难的那位仍然留在潜在受害者名单上）。可以确定这位杀手每天都会重复这一过程，这样一来，杀手每天都有两个潜在的受害者可供选择进行暗杀。好在夏洛克知道最初的两个潜在受害者是谁，并且，夏洛克知道发生杀人事件的当天的死者是谁以及新的潜在受害者是谁。
显然，好心的你需要每天帮助夏洛克列出每天的的潜在受害者名单，这样一来夏洛克就能从中观察到一些奇妙的规律。

## 说明/提示

如样例1所示，杀手从ross和rachel开始杀起。
第一天结束后，ross不幸被杀而joey接替。
第二天结束后，rachel不幸被杀而phoebe接替。
第三天结束后，phoebe不幸被杀而monica接替。
第四天结束后，monica不幸被杀而chandler接替。

## 样例 #1

### 输入

```
ross rachel
4
ross joey
rachel phoebe
phoebe monica
monica chandler
```

### 输出

```
ross rachel
joey rachel
joey phoebe
joey monica
joey chandler
```

## 样例 #2

### 输入

```
icm codeforces
1
codeforces technex
```

### 输出

```
icm codeforces
icm technex
```

# 题解

## 作者：_edge_ (赞：0)

~~这道题卡了我半年终于做出来了！~~

言归正传！

---

让我们先来分析题目：

~~乍一看，这题目还有点长~~

题目描述：

> 就是说有一个凶手要杀人，然后让你列出前n天的幸存者(也就是潜受害者) 

输入格式：

> 输入的第一行包含两个名字，这是最初的两个幸存者。

> 下一行包含整数天数n。 接下来的n行每行包含两个名字，第一个是当天被谋杀的人，第二个是取代死者成为新的幸存者的人。

> 输入格式是一致的，也就是说，一名死者肯定是当时的两个潜在受害者之一。

注意上面的题目要好好看！

然后我们来分析：

```cpp
    string zfc1,zfc2;
    cin>>zfc1>>zfc2;
```

首先定义两个字符串。

```cpp
   cout<<zfc1<<" "<<zfc2<<endl;//注意换行 
```

这个是还没有开始杀的幸存者！

```cpp
   int n;
	cin>>n;
```

读入天数

```cpp
    for (int i=1;i<=n;i++)
    {
    	string zfc3,zfc4;
    	cin>>zfc3>>zfc4;
    	if (zfc1==zfc3) zfc1=zfc4;
    	else zfc2=zfc4;
    	cout<<zfc1<<' '<<zfc2<<endl;
    }
```
此for循环十分重要！

因为：```一名死者肯定是当时的两个潜在受害者之一```

比较一下是zfc1这个人死了，还是zfc2这个人死了！zfc3就是死者

总结：

这道题目标签应该是：模拟+字符串

最后祝大家CSP-J或CSP-S第二轮加油！

---

## 作者：Chiaro (赞：0)

#### 输入匹配再输出

#### 很简单的一道题

~~总感觉我的代码强行增加复杂度~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring> 
#include<algorithm>
#define inf 1000
#define sc scanf
#define pr printf
#define ii int
#define ll long long
using namespace std;
ii n,b;
char read[40];
char now[2][40];
ii main(){
	cin>>now[0]>>now[1]>>n;         //输入
	cout<<now[0]<<' '<<now[1]<<'\n';//第一次直接输出
	for(ii i=0;i<n;i++){   //循环
		cin>>read;         //如果要被杀的人
		for(ii j=0;j<2;j++)//循环匹配(强行增加复杂度)
			if(!strcmp(now[j],read))b=j;//记录位置
            //strcmp()如果两个字符串字典序相同返回0
		cin>>now[b];                    //输入代替的人
		cout<<now[0]<<' '<<now[1]<<'\n';//输出
	}
	return 0;
}
```
_~~求过~~_

---

## 作者：小水滴 (赞：0)

题目大意：一个凶手要杀人。他每天会从两个名字中选择一个杀掉，并用新的一个人代替被杀掉的人。给出$N$天的情况，输出$N+1$行，每行表示此天结束后的两个候选名字。

思路：很简单的模拟，我们只需要用两个字符串记录候选名单，读入每天的信息，再将新的名字代替被杀的人，每次都输出一遍即可。

注意一开始读入时也要输出。

参考代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
string s1,s2,tmp1,tmp2;
//s1,s2用来不断记录候选名单
//tmp1,tmp2是每次读入的两个名字
int n;//天数
int main()
{
    cin>>s1>>s2;
    cout<<s1<<' '<<s2<<endl;
    //一开始先输出一遍
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>tmp1>>tmp2;
        if(s1==tmp1) s1=tmp2;
        else s2=tmp2;
        //判断哪个人被杀了，再更新
        cout<<s1<<' '<<s2<<endl;
        //每次都输出一遍
    }
    return 0;
}
```

---

