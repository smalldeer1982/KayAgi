# String Transformation

## 题目描述

You are given a string $ s $ consisting of $ |s| $ small english letters.

In one move you can replace any character of this string to the next character in alphabetical order (a will be replaced with b, s will be replaced with t, etc.). You cannot replace letter z with any other letter.

Your target is to make some number of moves (not necessary minimal) to get string abcdefghijklmnopqrstuvwxyz (english alphabet) as a subsequence. Subsequence of the string is the string that is obtained by deleting characters at some positions. You need to print the string that will be obtained from the given string and will be contain english alphabet as a subsequence or say that it is impossible.

## 样例 #1

### 输入

```
aacceeggiikkmmooqqssuuwwyy
```

### 输出

```
abcdefghijklmnopqrstuvwxyz
```

## 样例 #2

### 输入

```
thereisnoanswer
```

### 输出

```
-1
```

# 题解

## 作者：cq_loves_Capoo (赞：7)

我又来发题解啦，希望大家多多支持！   
这题我的思路大致如下：  
先定义一个字符等于a，然后把整个字符串跑一遍，执行下面的步骤。     
>如果字符中的字符小于或等于a，就把他变成a，并且a+1。   
>如果a>'z'，则退出循环。    

循环完后，如果a还没超过'z'，就代表字符串不符合要求，输出-1，并退出程序。    
接着如果还没退出程序，输出改变后的字符串。    
AC代码如下：    
``` 
#include<bits/stdc++.h>
using namespace std;
string st;
char a='a';//定义好一个字符串和一个字符 
int main()
{
	ios::sync_with_stdio(false);//减少cin和cout的缓存，增加cin、cout的速度 
	cin>>st; //输入一个字符串 
	for(int i=0;i<st.length();i++)//按照做法跑一遍循环 
		if(st[i]<=a)//如果该字符小于或等于a则执行以下步骤 
		{
			st[i]=a;//把该字符变成a 
			a++;//a+1 
			if(a>'z') break;//如果a>'z'，退出循环 
		}
	if(a<='z') 
	{//如果a<='z'代表不符合要求，输出-1 
		cout<<"-1";
		return 0;//退出程序 
	}
	cout<<st;//输出改编后的字符串 
	return 0;//养成好习惯 
}
```

---

## 作者：liangbob (赞：0)

### CF946 题解

#### 思路分析

简单字符串题。

首先，我们要变成一个包含从 a 到 z 的所有字母的字符串。而且变换方式是”位移“。

那么显然，我们从前往后一定要依次包含能通过”位移“变成从 a 到 z 的字符。什么字符可以满足呢？根据题意，只要不超过目标字符的字母表位序（其实就是 ASCII 码）的字母都可以满足。于是我们逐个目标的待变换字符确定即可。

现在实现有个难点：怎么才能“依次”‘？我们每次找到一个变换字符后，将确定范围缩小至该字符之后就可以。注意一个细节：每次应查找位置靠前的变换字符，这样才能把更多的机会留给后面的待变换字符。进而保证：如果按此方式找不到，那么就无解。

实现方式较多，题解区已经有大佬讲过按字符串位置逐位枚举的方法了，我就选用按目标字符来枚举的方法。

#### 关键代码

```cpp
for(char i = 'a';i <= 'z';i++) //按目标字符来枚举
{
	bool yes = false; //有无解
	int cur = 0; //变换下标，便于缩小范围。
	for(int j = p;j < s.size();j++)
	{
		if(s[j] <= i) //只要不超过目标字符的字母表位序（其实就是 ASCII 码）的字母都可以满足。
		{
			cur = j; //记录变换位置，便于缩小范围。
			s[cur] = i; //变换字符。
			yes = true; //记录有解。
			break; //找到一个立即 break，保证最小。
		}
	}
	if(!yes) //无解
	{
		cout << -1;
		return 0;
	}
	p = cur + 1; //缩小范围至该字符之后。
}
```



---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF946C)

看到各位大佬都在发题解，我也来~~水~~一篇。

关于这道题，我们首先要理解一下题目。

> 该子序列可以通过删除掉变换后的 $s$ 中的某些字母得到。

从这句话中可以知道，变换后的字符串 $s$ 只需要**包含** $a\thicksim z$ 即可，**并不需要为连续子序列**。

我们可以定义一个字符变量，初始值为 $a$，代表进度（下一个满足要求的 $s_i$ 会变换成进度）。然后遍历一遍字符串 $s$，如果 $s_i$ 小于进度，说明满足要求，可以转变，记得进度也要增加，其他的则不能。而如果当前进度已经大于 $z$，说明字符串 $s$ 已经包含 $a\thicksim z$，那么此时可以直接跳出循环。

最后我们判断一下，如果进度小于等于 $z$，证明并没有跳出循环，字符串 $s$ 不满足要求，输出 `-1`。否则，代表字符串 $s$ 满足要求，直接输出 $s$ 即可。

**最后贴上代码**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s;
char c = 'a';
signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		if (c > 'z') break;
		if (s[i] <= c) {
			s[i] = c;
			c++;
		}
	}
	if (c <= 'z') cout << -1;
	else cout << s;
	return 0;
}
```


---

## 作者：玄学OIER荷蒻 (赞：0)

这里主要补充各位大佬的题解。

首先，题目大意翻译已经有了，我们看分析。

## 题目分析
我们发现，每一个字母 $s_i$ 都可以代表 $s_i$~$\verb'z'$ 的字母。

那么，也就是说，其实字母越往上，难度就越低。

也就是说，如果在遍历途中，我们发现一个可以做 $\verb'a'$ 的字符，那么当然毫不犹豫选择它，因为以后可能就遇不到了。

当然，我们要选第一个 $s_i$=$\verb'a'$ 作为开头，接下来往下就是每一次都要选第一个 $s_i<=\verb'当前字符'$，知道最后任何一个字符都能当结尾。

列如，我们看这个字符串:$\verb"defaaaycccgbahjabczaaabbbnnnxaa"$

前三个都不行，接下来的 $\verb"aaa"$ 可以当作 $\verb"abc"$。

接下来的一个字符 $\verb'y'$ 不行，接下来的一直到 $\verb'z'$ 之前都可以，当作 $\verb'd'$~$\verb'n'$。

然后，$\verb'z'$ 不可取，接下来全部的都可以，对应 $\verb'o'$~$\verb'z'$。

代码大佬们已经有很多了，这里就不贴了。

---

## 作者：KirBytronic (赞：0)

## 思路
题目中的包含子序列并不需要子序列相连，所以只需要判断字符串从头到尾是否依次包含 $a \sim z$ 即可。 

## 做法
遍历整个字符串，用一个变量 $a$ 与当前字符串中的数据做比较，若当前数据小于 $a$ ，就将字符串中的数据变为 $a$ 中的数据，并将 $a+1$。若 $a> z$，则直接输出转换后的字符串。若遍历完成后 $a$ 仍小于等于 $z$，则输出 $-1$。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
char a='a';
int main(){
    cin>>s;
    for(int i=0;i<s.size();i++){
	if(s[i]<=a){
	    s[i]=a;//若当前字符小于a，就将这个字符变换为a，同时将a加上一位
	    a++;
     }
	if(a>'z') break;//当字符串中已包含'a'~'z'，则直接结束遍历
	}
    if(a<='z')//若遍历完成后字符串中仍不包含'a'~'z',输出-1；
	cout<<-1;
    else cout<<s;//若字符串中包含'a'~'z'，输出变换后的字符串	
} 
```


---

## 作者：封禁用户 (赞：0)

#### 思路
由题得：我们只需将字符串变为一个从前
向后能依次存在 a , b , c , d …… z 即可，又因为 z 不能变为其他字母，只需维护一个当前的进度，表示现在需要那个字母即可。

#### 代码
```
#include<bits/stdc++.h>
using namespace std;
char s[100005];
char now='a';//如思路中所说当前的进度 
int main(){
	cin>>(s+1);//读入 
	int len=strlen(s+1);//求长度
	for(int i=1;i<=len;++i){
		if(now>'z')break;//可以完成
		if(s[i]<=now){//可以变成now 
			s[i]=now;//当前替换为now 
			++now;//进度加一 
		} 
	} 
	if(now<='z')cout<<-1;//未完成
	else cout<<(s+1);//输出序列 
	return 0;
}

---

## 作者：TheShuMo (赞：0)

## 题目分析


\
题目的意思是说，在输入的字符串 $s$ 中，通过给定的规则进行字符的变换。

如果能够使该字符串的子序列中包含串 $\verb!abcdefghijklmnopqrstuvwxyz!$。

则输出该变换后的字符串 $s$。否则输出 $-1$。
## 简单思路

我们只需要模拟判断字符串 $s$ 中是否包含了 $a$ 至 $z$ 的字符串即可。

从头开始挨个模拟，定义字符变量 $now$ 为当前模拟到的字符。

如果 $s[i] \geq now(i = 0,1\cdots n-1)$ 则 $s[i]$ 可以经过变换后变成 $now$。

于是 $s[i]=now$。

最后输出字符串即可。

## 代码

~~代码太丑了，此处不放~~

---

