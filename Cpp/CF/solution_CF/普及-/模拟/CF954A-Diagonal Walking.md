# Diagonal Walking

## 题目描述

Mikhail walks on a 2D plane. He can go either up or right. You are given a sequence of Mikhail's moves. He thinks that this sequence is too long and he wants to make it as short as possible.

In the given sequence moving up is described by character U and moving right is described by character R. Mikhail can replace any pair of consecutive moves RU or UR with a diagonal move (described as character D). After that, he can go on and do some other replacements, until there is no pair of consecutive moves RU or UR left.

Your problem is to print the minimum possible length of the sequence of moves after the replacements.

## 说明/提示

In the first test the shortened sequence of moves may be DUD (its length is $ 3 $ ).

In the second test the shortened sequence of moves can be UUDRRRDUDDUUU (its length is $ 13 $ ).

## 样例 #1

### 输入

```
5
RUURU
```

### 输出

```
3
```

## 样例 #2

### 输入

```
17
UUURRRRRUUURURUUU
```

### 输出

```
13
```

# 题解

## 作者：applese (赞：2)

个人认为红题吧QAQ

实际上这道题目的解法很简单，我们只需要判断连续两个操作是否可以替换成$D$就可以啦QAQ

下面附上代码和解释：

```
#include<iostream>
#include<cmath>
using namespace std;
int n,i;
string st;
int main()
{
    cin>>n;
    cin>>st;
    int sum=n;    //先存上n 
    while(i!=n)   //如果字符串没有到结尾时一直执行QAQ 
    {
    	if(st[i]=='R'&&st[i+1]=='U'||st[i]=='U'&&st[i+1]=='R') //判断如果该行为为RU或是UR执行 
    	{
    		i+=2;  //跳至下两个数（避免到时候重叠出现错误） 
    		sum--;   //那么就可以减少一个动作，所以sum--；如果这里使用n，将会导致循环问题QAQ 
		}
		else
		i++;   //否则就跳至下一个 
	}
	cout<<sum;
    return 0;
}
```
如对题解**有疑问**，请在**右侧留言**，谢谢QAQ

---

## 作者：LJY_ljy (赞：1)

## CF954A 题解：

个人认为此题红题。

其实这题的意思就是将序列中的“UR”和“RU”替换成"D"即可。

那么这题就迎刃而解了。



-------------

从1 到 序列长度 - 1 遍历。

因为序列只出现“R”或者“U”，所以一个“UR”或“RU”出现的条件是：

- str[i] != str[i + 1]

然后就可以将这个“RU”或“UR”替换成“D”就行了。

剩下的细节我们在代码中再分析。



------------

## Code:

```cpp
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 110;
bool flag[MAXN];//标记这个字符是否用过。
int n, ans;
string str;

int main() {
	cin >> n;
	getline(cin, str);
	getline(cin, str);
	ans = n;
	for (int i = 0; i < str.size() - 1; i++) {
		if (str[i] != str[i + 1] && !flag[i] && !flag[i + 1]) { // 这两个数不相同，并且这两个数都没有用过，就可以把这两个字符合并成“D”
			ans--;//两个字符转换成一个字符，总字符数就要减1
			flag[i] = flag[i + 1] = true;//标记这个两个数用过了。
		}
	}
	printf("%d\n", ans);
	return 0;
} 
```

### Q:为什么要用flag数组标记，不加不行吗？

### A：我们先来举个栗子：

例如一串字符： RUR

如果没用flag数组，程序就会标记到str[0] 和 str[1] 组成的“RU”，和str[1] 和 str[2] 组成的“UR”。在这种情况下，输出为1。

### 可是，正确答案为2！

为什么呢？因为RUR只能转换成DR或RD。所以最少也会存在两个字符。所以这就是flag数组起到的作用。

用了flag数组之后，flag[0] = flag[1] = true, 这样遍历到str[1] 时就不会重复计算了，这样即可AC。

---

## 作者：恨穹不是妹 (赞：1)

###### 题目翻译：Mikhail在一架2D飞机（我也不知道是啥）上行走。他可以往上走也可以往右走。你得到了Mikhail的一系列动作。他认为这个序列太长了，他想使它尽可能短。

###### 在给定的序列中，向上移动由字符U描述，右移动由字符R描述。Mikhail可以用对角线移动(描述为字符D)替换任意一对连续的移动，RU或UR。

###### 您的任务是打印替换后移动序列的最小可能长度。

这道题其实很简单，给新手练手还是不错，因为它只是需要求缩减之后序列的长度，就是说要求序列的总长度减去可以进行合并的个数。我们只需要从头到尾模拟一遍，找出有几个可合并的序列。（亲测暴力能过）

下面贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000010];//再不爆空间的基础上尽量多开数组，血的教训
int main()
{
	int n,count=0;//count记录可合并的串数
	cin>>n;
	cin>>a+1;//字符串a从1的位置开始读入,这样就可以把i从1到n循环，不然要从0到n-1循环
	for(int i=1;i<=n;i++)
	{
		if((a[i]=='U'&&a[i+1]=='R')||(a[i]=='R'&&a[i+1]=='U'))//可以U在前也可以R在前
		{
	    	count++;
	    a[i]=' ';
	    a[i+1]=' ';//为了避免重复匹配，把匹配过的变成空格（实际上除了U或R都可以变）
		}
	}
	cout<<n-count;
}
```



---

## 作者：Colead (赞：0)

就是一个很简单的字符串处理。

只要在原串中找到相邻两个字符不同就将计数器++，然后从后面两个再开始搜就可以了。

唯一需要注意的地方就是每搜到一对要从下一对而非下一个开始搜，否则诸如 $UFU$ 这样的就会被算作两次，就会导致最终答案偏小。

```
#include<bits/stdc++.h>
using namespace std;
int n;
char p[105]={};
int ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>p[i];
	}
	for(int i=2;i<=n;i++)
	{
		if(p[i]!=p[i-1])
		{
			ans++;
			i++;//for循环已经加了一次，这里再加一次
		}
	}
	cout<<n-ans<<endl;
	return 0;
}
```

祝大家AC愉快~

---

## 作者：orange166 (赞：0)

## CF954A Diagonal Walking  
[传送门](https://www.luogu.com.cn/problem/CF954A)  
### 思路： 
当有相邻的 $\text{R}$ 和 $\text{U}$ 时，可以把他们替换成一个 $\text{D}$ 让序列最短。  
又因为只有 $\text{R}$ 和 $\text{U}$ 两种移动，所以可以用 $\space$ `if b[i]!=b[i-1]` $\space$ 判断能否替换 $\text{D}$ 。  
  
代码里有解释。 
### 代码：  
```python
a=int(input()) //转换成整型
b=input()  //python默认输入的是字符串
i=1; s=0  //s用来计总共能换几个D
while i<a:
    if b[i]!=b[i-1]:
        s+=1; i+=2  //防止下一个字符与已经替换过的字符替换
    else:
        i+=1  //不能替换就试下一个字符
print(a-s)  //最终总长度

```
[喜提最短解](https://www.luogu.com.cn/record/43726172)    

有疑问请留言

---

## 作者：k3v1n070828 (赞：0)

### 这题用模拟完全能解

思路：

答案变量$ans$的初值设为字符串长度$n$，只要遇到$R$和$U$在一起就减$1$（因为两个字符变成了一个字符，$2-1=1$）。

注意：直接按照上面这样算会导致重复计算情况，所以我们需要一个布尔型数组$flag$记录一个数字是否已被合并成$D$，每次合并后把这个位置记录，已避免重复记录。

话不多说，代码如下：

```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>//头文件
using namespace std;
string m;//字符串
int n;//字符串长度
bool flag[110];//flag数组
int main(){
	memset(flag,false,sizeof(flag));//一开始把整个flag赋值为false
    scanf("%d",&n);//输入长度
    cin>>m;//输入字符串用cin更简单
    int ans=n;//答案变量一开始赋值为n
    for(int i=0;i<n;i++)//枚举查找
    	if(((m[i]=='R'&&m[i+1]=='U')||(m[i]=='U'&&m[i+1]=='R'))&&flag[i]==false)//判断是否可以合并成D（flag数组的作用所在）
    		flag[i]=flag[i+1]=true,ans--;//合并操作：flag记录+答案自减1
	printf("%d\n",ans);//输出答案
    return 0;//结束程序
}
```
讲完了，自己写代码AC吧~

---

