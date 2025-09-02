# Football

## 题目描述

Petya loves football very much. One day, as he was watching a football match, he was writing the players' current positions on a piece of paper. To simplify the situation he depicted it as a string consisting of zeroes and ones. A zero corresponds to players of one team; a one corresponds to players of another team. If there are at least $ 7 $ players of some team standing one after another, then the situation is considered dangerous. For example, the situation $ 00100110111111101 $ is dangerous and $ 11110111011101 $ is not. You are given the current situation. Determine whether it is dangerous or not.

## 样例 #1

### 输入

```
001001
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
1000000001
```

### 输出

```
YES
```

# 题解

## 作者：时律 (赞：10)

~~很想问其他写题解的人，用那么多标题字符干什么啊~~

如某篇题解所说的，可以用`find()`函数。

把位置用字符串读进来，然后再用`find()`寻找有没有七个站在一起的队员即可。


```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;
	cin>>a;
	if(a.find("0000000")!=-1 or a.find("1111111")!=-1)//不等于-1，即为存在（-1代表不存在所查找的字符串）
		cout<<"YES";
	else
		cout<<"NO";
}
```

---

## 作者：Cream_ (赞：3)

### 这是一道  ****普及/提高--****的题？？
~~ 这是个入门难度的题~~

~~水的不要不要的（别打我）~~。。


------------
## 上
------------
## 代
------------
## 码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string s;
int sum0,sum1,flag1=2,flag2;

int main(){
	cin >> s;
	if (s.length() <= 7)
	{
		cout << "NO" << endl;
		return 0;
	}
	for (int i = 0;i <= s.length()-1;i++)
	{
		if (s[i] == '0' )
		{
			flag1 = 0;
		}
		if (s[i] == '1')
		{
			flag1 = 1;
		}
		if (flag1 == 0)
		{
			sum0++;
			sum1 = 0;
			if (sum0 == 7)
			{
				cout << "YES" << endl;
				flag2 = 1;
				break;
			}
		}
		if (flag1 == 1)
		{
			sum1++;
			sum0 = 0;
			if (sum1 == 7)
			{
				cout << "YES" << endl;
				flag2 = 1;
				break;
			}
		}
	}
	if (flag2 == 0)
	{
		cout << "NO" << endl;
	}
	return 0;
}
```


------------
## 简单易懂，本蒟蒻就不解释了。。

---

## 作者：小鲍bob (赞：2)

## 题目较水
首先这道题题意就是：如果有7个同样的数连在一起，就输出YES，否则输出NO

这道题的重点就是在累加次数和判断上
先上重点
```
        if(s[i]==s[i+1]) su++;//如果当前字符和后一个字符一样，su++
	    else su=1;//千万不可以用0，因为当前数也算一个
		if(su==7)//到了就输出
		{
			cout<<"YES";
			return 0;
		}

```
重点分析完了之后，我们发现题目其实还有一个优化：如果字符串的长度本身就小于7，那么直接输出NO，其实快了一点点

上完整代码：
```
#include<bits/stdc++.h>//万能头
using namespace std;
int main()
{
	string s;//s为输入的字符串
	int i,su=1;//i用于循环，su用于累加，su初始化必须为1，不然会WA一个点
	cin>>s;//因为没有空格，所以可以用cin
	if(s.length()<7)//优化
	{
	    cout<<"NO";
	    return 0;
	}
	for(i=0;i<s.length()-1;i++)//循环
	{
		if(s[i]==s[i+1]) su++;//一样就累加
		else su=1;//当前字符
		if(su==7)
		{
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
	return 0;
 } 
```

---

## 作者：C20212724杨京朝 (赞：2)

（~~纪念又A了一道水题~~）模拟！模拟！模拟！
------------
    #include <cstdio>
    #include <cstring>
    char a[105];//定义一个字符串
    int main() {
        int tot = 1;//计数器初值为一
        scanf("%s",a);//输入
        int len = strlen(a);
        for(int i = 0;i < len;i ++) {//从0号位开始扫
            if(a[i] == a[i - 1]) tot ++;//如果前后两位数字相同，tot ++
            else tot = 1;//否则赋为初值
            if(tot >= 7) {//根据题意输出
                printf("YES");
                return 0;
            }
        }
        printf("NO");
        return 0;
        //解释一下为什么tot初值为1，n个数之间的间隔为n - 1,所以为了避免误差，tot为1
    }

---

## 作者：封禁用户 (赞：1)

暴力能过

评测机真是卡，测了半天。。

本来以为是模拟踢球的什么东西，结果来了这一茬。。

~~（以上为废话~~

先重新康康题目：

>有一天看比赛时，Petya是如此无聊以至于在纸上写下各个球员的当前位置。为了看起来好看，他把各个球员用$1$与$0$来表示，$1$与$0$表示不同球队的人。如果一个队至少有七个人是站在一起的，那么就被认为很危险。例如，$00100110111111101$被认为是危险的（因为有$7$个$1$连在一起），而$11110111011101$则不是。现在Petya给了你现在的球队情况，让你判断是否危险。

其实说白了就是让你判断一个由$0$和$1$组成的数组中有没有$a_i$~$a_{i+6}$相等的情况。有，输出$YES$；没有输出$NO$。

那就写个循环暴力呗~


哦，不过，在惨不忍睹的暴力之前，先得做个小小的判断：

```cpp
if(n<7) {
	printf("NO\n");
	return 0;
}
```

大致就是判断这个$01$串的长度是否$≥7$。

这是很有必要的，原因有两点：

1.  从时间的角度出发

如果特判成立（即$n<7$），那只要输出就可以了。但是如果没有特判，循环必定会耗时更多（功劳归属于我们十分香的$if$判断）。所以，特判能省时。

2. 从答案的准确性角度出发

你没有特判，如果$a_{i+?}$不属于这个$01$串，那数组里是什么数我就不能保证了。所以，很可能影响答案的正确性。

>PS:$?$为未知数（$≤6$）

代码就不详细讲了，相信各位弄明白了之后都能写出来。

$code$
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int main() {
	cin>>s;
	n=s.length();
	int x=1;
	if(n<7) {
		printf("NO\n");
		return 0;
	}
	for(int i=0; i<n; ++i) {
		if(s[i]==s[i+1]&&s[i+1]==s[i+2]&&s[i+2]==s[i+3]&&s[i+3]==s[i+4]&&s[i+4]==s[i+5]&&s[i+5]==s[i+6]) {//判断
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
```

---

## 作者：呵呵侠 (赞：1)

# 水题！！！

这一题如果会方法就是A+B Problem的难度

这一题很多人用的是模拟，对此，我有一个更好的方法

不知在座的各位，有没有听说过.find函数？

听过就好说了，如果没听过，我来说说

## .find的正确使用姿势：

首先是.find的作用，类似于Ctrl+F，就是寻找！

用法
```
string a,b;
cin>>a>>b;
int c=a.find(b);
```
先输入a

再输入b

最后寻找看看a里面有没有b（仅限字符串）

如果没有，c=-1

如果有，c是正数（表示b字符串的位置）

然后黏贴AC代码：
```
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    string a,b="1111111",c="0000000";
    cin>>a;
    int k=a.find(b);
    int m=a.find(c);
    if(k!=-1||m!=-1)
        cout<<"YES";
    else
        cout<<"NO";
}
```
简单吧

如果你觉得对你有帮助，欢迎留言

---

## 作者：LRL65 (赞：1)

一道入门难度的**模拟题**

**思路**：记录0和1连续的个数，当连续1的个数或0的个数超过7个时就输出"YES"，如果一直没有就输出"NO"。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int s0=0,s1=0;//初始化
int main() {
    cin>>a;//输入
    for(int i=0;i<a.size();i++) {
        if(a[i]=='0') {
            s0++;//记录连续0的个数
            s1=0;//连续1的个数变为0
        }
        else {
            s1++;//记录连续1的个数
            s0=0;//连续0的个数变为0
        }
        if(s1>=7||s0>=7) {
            cout<<"YES"<<endl;//连续1的个数或0的个数超过7个时就输出"YES"
            return 0;
        }
    }
    cout<<"NO"<<endl;//一直没有就输出"NO"
	return 0;
}
```


---

## 作者：TRZ_2007 (赞：0)

## Solution
题目大意：给你一个**长度未知的**字符串，让你判断是否其中有长度**大于等于**7的相同字符串。

模拟即可，注释放代码里。

```cpp
#include <bits/stdc++.h>
using namespace std;

string str;//那个字符串
char now;//当前你在判断什么串
int ans;//看看是否能达到标准

int main()
{
	getline(cin,str);
	int len = str.size();
	now = str[0];
	for(int i=0;i<len;i++) {
		if(now == str[i]) {//相等的话
			ans++;
		}
		else {
			now = str[i];//更换被测点
			if(ans >= 7) {//若达到标准
				puts("YES");//后面就不用测了
				exit(0);//那就弹出
			}
			ans = 1;//你还剩一个数
		}
	}
	if(ans >= 7) {//最后必须判断！！！
		puts("YES");
		exit(0);
	}
	puts("NO");//不满足条件就咕咕咕了……
}
```

---

## 作者：CrTsIr400 (赞：0)

##### ~~这是![](https://cdn.luogu.com.cn/upload/image_hosting/thw9oww6.png)的题目？~~
# 全洛谷就没人边读入边判断了吗？
## 算法：边读边判断qwq
## 如何判断？
### 判断前面7个队员是否穿同样球衣，如果是，直接exit。
# （直接exit，不用读入多余的字符）
### 上判断代码（c++11）：
```cpp
if(n>=7&&a[n]==a[n-1]&&a[n]==a[n-2]&&a[n]==a[n-3]&&a[n]==a[n-4]
&&a[n]==a[n-5]&&a[n]==a[n-6])
{
	printf("YES");
	return 0;
}
```
# 这
# ~~难~~点其实就在字符串的处理。
## 字符串的输入，可以用gets
	gets:读入一个字符串，不过滤空格
## 也可以用scanf
	scanf:读入一个字符串，遇到空格或者非显示字符停止。
## 我的是一个一个getchar
	getchar:读入一个字符，不过滤非显示字符
## 可以把getchar升级，变成可见字符的getchar
## 代码：
```cpp
char c=getchar();
while((c<32)||(c>126))c=getchar();
```
## 这回上完整代码：
```cpp
#include<cstdio>
char a[10001]={};int n;
int main()
{                  
	while((a[++n]=getchar())>='0'&&a[n]<='9')//读入字符
	{
		if(n>=7&&a[n]==a[n-1]&&a[n]==a[n-2]&&a[n]==a[n-3]&&a[n]==a[n-4]&&a[n]==a[n-5]&&a[n]==a[n-6]){printf("YES");return 0;}//就是上面所述的核心代码，一边读一边判断，如果已经读到了7个相同的字符就输出“YES”，并直接退出，不用继续读入
	}
	printf("NO");//没有的情况输出“NO”
	return 0;
}
```
###### qwq（滑稽）

---

## 作者：WKAHPM (赞：0)

### 一道字符串模拟，直接暴力枚举即可

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin >> s;
	for(int i = 0 ; i < s.size(); i++)
	{
		int ans = 1;
		char c = s[i];
		for(int j = i + 1 ; j < s.size(); j++)
		{
			if(s[j] != c)//不一样直接退出
			{
				break;
			}
			else
			{
				ans++;
			}
			if(ans == 7)//有七个一样的输出YES
			{
				puts("YES");
				return 0;
			}
		}
	}
	puts("NO");//不危险输出NO
	return 0;
}

```


---

## 作者：partychicken (赞：0)

### 发篇题解证明清白（关于选了NOI+/CTSC-）
这道题还是很水的，毕竟A题，不想说什么，上代码

至于为什么选了那个难度，都是因为某UID49866的大佬调皮干哒

—————————————————————————————————————

ummm。。。第一遍没过（尴尬）（以下内容为二次添加）

每次如果读到0就更新num0，并把num1清零（为了保险，而且我菜，找不到什么好的实现方式），读到1同理

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int num0=0,num1=0;
    string s;
    cin>>s;
    int len=s.size();
    for(int i=1;i<=len;i++)
    {
        if(s[i]=='0')
        {
            num0++;
            num1=0;
        }
        else
        {
            num1++;
            num0=0;
        }
        if(num0>=7||num1>=7)
        {
            cout<<"YES"<<endl;
            return 0;
        }
    }
    cout<<"NO"<<endl;
}
```

---

