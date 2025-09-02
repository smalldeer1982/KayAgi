# War of the Corporations

## 题目描述

A long time ago, in a galaxy far far away two giant IT-corporations Pineapple and Gogol continue their fierce competition. Crucial moment is just around the corner: Gogol is ready to release it's new tablet Lastus 3000.

This new device is equipped with specially designed artificial intelligence (AI). Employees of Pineapple did their best to postpone the release of Lastus 3000 as long as possible. Finally, they found out, that the name of the new artificial intelligence is similar to the name of the phone, that Pineapple released 200 years ago. As all rights on its name belong to Pineapple, they stand on changing the name of Gogol's artificial intelligence.

Pineapple insists, that the name of their phone occurs in the name of AI as a substring. Because the name of technology was already printed on all devices, the Gogol's director decided to replace some characters in AI name with "\#". As this operation is pretty expensive, you should find the minimum number of characters to replace with "\#", such that the name of AI doesn't contain the name of the phone as a substring.

Substring is a continuous subsequence of a string.

## 说明/提示

In the first sample AI's name may be replaced with "int#llect".

In the second sample Gogol can just keep things as they are.

In the third sample one of the new possible names of AI may be "s#ris#ri".

## 样例 #1

### 输入

```
intellect
tell
```

### 输出

```
1```

## 样例 #2

### 输入

```
google
apple
```

### 输出

```
0```

## 样例 #3

### 输入

```
sirisiri
sir
```

### 输出

```
2```

# 题解

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF625B#submit)

# 思路

此题是一道字符串匹配题，找到长串中存在的子串数目，进行统计。

# 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  char a[100005],b[35];
  int len1,len2,i,j,ans;
  int main(){
      cin>>a>>b;
      len1=strlen(a);len2=strlen(b);
      while(i<len1){
          if(a[i]==b[0]){
              while(j<len2){
                  if(a[i+j]==b[j]){
                      j++;
                  }
                  else{
                      break;
                  }
              }
              if(j==len2){//是否相等
                  i+=j-1;
                  ans++;
              }
              j=0;
          }
          i++;
      }
      if(j==len2){
          ans++;
      }
      cout<<ans;
      return 0;
  }
```


---

## 作者：Buried_Dream (赞：1)

## 题意：

题目的翻译有问题：

给你两个字符串 $a,b$，当你从 $a$ 找到一个字串等于 $b$ 的时候，这个时候跳到这个字串的末尾, 问你从 $a$ 中能找到几个字串与 $b$ 相等。

## 思路：

我从 $a$ 串的每一位出发，截取一个长度为 $b$ 串的子串，判断这个串是否与 $b$ 串相等，如果相等答案就加 $1$，同时下次要从这个子串的末尾开始扫，所以此时的从哪里开始扫的指针就加上一个 $b$ 串长度。 

截取的时候用 `substr` 函数，用法是：

```cpp
substr(字符串的某个位置，从这个位置要截取的长度)

```

## AC code：

```cpp

signed main() {
	int tests = 1; // cin >>tests;
	while(tests--) {
		cin >> a >> b;
		int lena = a.length(), lenb = b.length();
		for(int i = 0; i < a.length(); i++) {
			string s = a.substr(i, lenb);
			if(b == s) i += lenb - 1, ans++;
		}
		cout << ans;
	}
}



---

## 作者：BearBig (赞：1)

### 题目 + 方法分析
这道题就是一个子串搜索问题。这是蓝题？！不应该啊，对于 Python 的朋友们来说，这也太简单了吧！

这道题用 Python 的字符串自身方法，一行代码就能搞定。代码为 
`
str.count(obj)
`
方法就能实现。这个方法就是统计字符串 $str$ 中有多少个 $obj$ 字符子串。    
### 知识拓展
`
str.count(obj)
`
方法知道吗？似乎只要学过 Python 算法的都知道吧。如果您没有接触过 Python 算法，并且认为我写的不够详细，看一下[这里](https://m.php.cn/article/442099.html)
### 代码部分
代码如下，非常简单，不再做解释了。
```python
print(input().count(input()))
```
**珍爱生命，远离抄袭！**
### 更新日志
- 2022/1/26  经过管理员提醒，将第一部分和第二部分的 LaTeX 公式与代码块做了调整，感谢管理，希望能再次审核。

---

## 作者：yzx72424 (赞：1)

题意给出s1,s2,每次可以把s1中一个字符变为#,求s1中不含有s2的最小次数

一道纯纯的模拟加贪心，字符串分别为s1,s2,长度为a1,a2.每次找到a1中含有a2，就把对应a2的最后一位的a1所在位置改为#


```
#include<bits/stdc++.h>
using namespace std;
char s1[100000],s2[100000];
int main() {
	gets(s1);
	gets(s2);int i,j,k=0;
	int a1=strlen(s1),a2=strlen(s2);
    for(i=0;i<a1;i++){
    		for( j=0;j<a2;j++){if(s1[i+j]!=s2[j])break;if(j==a2-1)k++,s1[i+j]='#';} 
    }
    printf("%d",k);
}
```

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题本质上采用的是暴力思路。

不妨设输入的两个串为 $a,b$，且他们的长度为 $lena,lenb$。对于串 $a$ 的每一个位置都有一个布尔型的 $flag$ 值，表示这一个位置是否已经被 `#` 替换。那么就可以暴力的枚举 $a$ 中任意相邻 $lenb$ 位，检测是否与 $b$ 串完全相同，如果完全相同，那么就把这 $lenb$ 位的 $flag$ 值赋为 $1$，以后在遍历时，如果到这里就不用算了，只需再去找 $flag$ 不是 $1$ 的字串即可。

那么如果没有这个 $flag$ 的话什么样的样例会错呢？

答：第一个串为 `ttttt`，第二个串为 `ttt`。此时如果你只是正常的去求子串数那会得到 $3$；然而其实这个样例根本不用替换 $3$ 个 `#`，其实只要把中间那个换成 `#` 就没有 `ttt` 这样的子串了。

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string a,b;
	cin>>a>>b;
	int lena=a.length();
	int lenb=b.length();
	int ans=0;
	int pre=0;
	bool flag[1000005];
	memset(flag,0,sizeof(flag));
	for(int i=0;i<=lena-lenb;i++)
	{
		pre=0;
		for(int j=0;j<lenb;j++)
		{
			if(a[i+j]!=b[j])//不相同，直接跳出
			{
				break;
			}
			if(a[i+j]==b[j]&&flag[i+j]==0)
			{
				pre++;//记录有多少位相同
			}
			else 
			{	
				continue;
			}
		}
		if(pre==lenb)//完全相同的子串
		{
			for(int k=i;k<=i+lenb-1;k++) flag[k]=1;//相应位赋成1
			
			ans++;
		}
	}
	cout<<ans;
	return 0;
}

```

谢谢大家观看~


---

## 作者：hyc1026 (赞：0)

问你字符串 $a$ 里有几个子串 $b$。

Python AC Code:
```python
a=input()
b=input()
a=str(a)
b=str(b) //输入
print(a.count(b)) //输出
```

C++ AC Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a,b;
    cin >> a >> b;
    int cnt = 0;
    int la = a.size();
    int lb = b.size();
    for(int i=0; i<la; i++)
    {
    	for(int j=0; j<lb; j++)
    	{
    	    if(b[j] != a[i+j]) break; //跳出循环
    	    if(j == lb - 1)
    	    {
    	        cnt++;
    	        a[i+j] = ' '; //计数并避免重复计算
    	    }
    	} 
    }
    cout << cnt << endl;
}
```

---

