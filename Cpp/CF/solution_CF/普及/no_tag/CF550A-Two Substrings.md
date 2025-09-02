# Two Substrings

## 题目描述

You are given string $ s $ . Your task is to determine if the given string $ s $ contains two non-overlapping substrings "AB" and "BA" (the substrings can go in any order).

## 说明/提示

In the first sample test, despite the fact that there are substrings "AB" and "BA", their occurrences overlap, so the answer is "NO".

In the second sample test there are the following occurrences of the substrings: BACFAB.

In the third sample test there is no substring "AB" nor substring "BA".

## 样例 #1

### 输入

```
ABA
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
BACFAB
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
AXBYBXA
```

### 输出

```
NO
```

# 题解

## 作者：Mysterious_Cat (赞：4)

### 题目大意：找出是否有不重叠的子串AB和BA
### 题目思路：暴力解出子串AB或使用find函数，将其替换为其他字符，判断是否仍有子串BA（注意要做两遍：分别是AB和BA）
具体实现（本人懒只给模板）：
```
int AB = s.find("AB");
if(AB != -1)
    {
        s.replace(AB, 2, "MYS");
        int BA = s.find("BA");
        if(BA != -1)
        {
            printf("YES");
            return 0;
        }
    }
```

---

## 作者：little_sun (赞：1)

### 为什么我的做法跟别人如此不一样啊qwq

思路：暴力判每一个"BA"出现的位置，二分查找他前/后有没有满足条件的"AB",时间复杂度$O(n\log_{2}n)$

#### 在博客食用更好哦  [myblog](https://www.cnblogs.com/little-sun0331/p/9917336.html)

```cpp
# include <bits/stdc++.h>

const int MaxN = 100010;

std::vector<int> a, b;//存下标

int upper(int x)//二分后面的位置
{
    int l = 0, r = a.size();
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(a[mid] > x)
            r = mid;
        else l = mid + 1;
    }
    return l;
}

int lower(int x)//二分前面的位置
{
    int l = -1, r = a.size() - 1;
    while(l < r)
    {
        int mid = (l + r + 1) >> 1;
        if(a[mid] < x)
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}
int main()
{
    std::string s;
    std::cin >> s;
    int len = s.length();
    for(int i = 0; i < len - 1; i++)
    {
        std::string tmp = s.substr(i, 2);
        if(tmp == "AB")
            a.push_back(i);
        else if(tmp == "BA")
            b.push_back(i);
    }//查找"AB"和"BA"出现的位置
    if(a.size() == 0 || b.size() == 0)
        return 0 * printf("NO");//特判
    for(int i = 0; i < b.size(); i++)
    {
        int x = lower(b[i] - 1);//防重
        int y = upper(b[i] + 1);
        if(x != -1 || y != a.size())
            return 0 * printf("YES");
    }
    printf("NO");
    return 0;
}
```

---

## 作者：_Clown_ (赞：0)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF550A}$|$\texttt{洛谷难度:普及/提高-}$|[$\texttt{On 2021/06/14}$](https://www.luogu.com.cn/record/51791429)|
# 解析
这道题目题目意思不难理解，

我们看到样例一就知道了选择的 $AB$ 和 $BA$ 位置不能冲突。

所以说我们只有两种情况：
- 先找 $AB$，再找 $BA$：
- 先找 $BA$，再找 $AB$

然后我们就用字符串里的 $\texttt{find}$ 函数直接搜。

找到以后换一个不着边的字符串替换掉即可。![cy](https://cdn.luogu.com.cn/upload/pic/62225.png)![cy](https://cdn.luogu.com.cn/upload/pic/62225.png)
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string S,T;
int main(void)
{
	cin>>S,T=S;register int F=S.find("AB");
	if(F!=-1)
	{
		S.replace(F,2,"JXT"),F=S.find("BA");
		if(F!=-1)puts("YES"),exit(0);
	}
	S=T,F=S.find("BA");
	if(F!=-1)
	{
		S.replace(F,2,"JXT"),F=S.find("AB");
		if(F!=-1)puts("YES"),exit(0);
	}
	puts("NO");
	return 0;
}
```

---

## 作者：yuchenren (赞：0)

### 思路
这道题很简单，用一个字符串代替原来输入的字符串，把 `BA` 和 `AB` 用 `.` 代替。

### 代码
```cpp
#include <bits/stdc++.h>//万能头
using namespace std;

int main() {
	string s;
	cin >> s;
	int AB = s.find("AB");//定义"AB"的位置
	int BA = s.find("BA");//定义"BA"的位置
	if (AB != -1) {
		string temp = s;//定义临时字符串temp
		temp.replace(AB, 2, ".");//用"."代替
		int BA = temp.find("BA");
		if (BA != -1) {
			cout << "YES" << endl;//如果没有输出YES
			return 0;//结束程序
		}
	}
	if (BA != -1) {//同上
		string temp = s;
		temp.replace(BA, 2,".");
		int AB = temp.find("AB");
		if (AB != -1) {
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;//如果都没有找到输出NO
	return 0;//华丽结束
}
```


---

## 作者：Insouciant21 (赞：0)

#### 题意

给出一个字符串 $S$ ，判断其中是否有子串 `AB` 和 `BA` 且 `AB` 和 `BA` 不重叠。

#### 分析

因为不能计算重叠的，所以对于 `ABA` 和 `BAB` 只能算作一个 `AB` 或是 `BA` 来判断，将其个数记作 $p$ 。

然后我们计算去除 `ABA` 和 `BAB` 的 $S$ 中 `AB` 和 `BA` 的个数，分别记作 $a$ 和 $b$ 。

当 `AB` 与 `BA` 存在于 $S$ 时，必有 $a,b>0$ 或是 $p\geq2$ ，以及需要 $p$ 补齐缺少的子串时的情况 $(p>0)$ 。

#### 实现

先计算 $p$ 的值，并在计算过程中去除 `BAB` 和 `ABA`。
```
for (int i = 0; i < in.length() - 2; i++) {
    if ((in[i] == 'A' && in[i + 1] == 'B' && in[i + 2] == 'A') || (in[i] == 'B' && in[i + 1] == 'A' && in[i + 2] == 'B')) {
        in[i] = in[i + 1] = in[i + 2] = '#'; // 去除 ABA 和 BAB
        p++;
    }
}
```

因为已经去除了 `BAB` 和 `ABA` 所以剩下的都是单独的 `AB` 与 `BA`，直接计算个数即可。
```
for (int i = 0; i < in.length() - 1; i++)
    if (in[i] == 'A' && in[i + 1] == 'B')
        a++;
for (int i = 0; i < in.length() - 1; i++)
    if (in[i] == 'B' && in[i + 1] == 'A')
        b++;
```

最后判断是否存在
```
if ((a && b) || (a && p) || (b && p) || (p >= 2))
    puts("YES");
else
    puts("NO");
```

---

## 作者：yzx72424 (赞：0)

贪心的思想，对于找到的每个AB都和谐掉，继续查找BA

```
#include <bits/stdc++.h>
using namespace std;
string a,s;
int kkk;
inline void ltt(char A,char B){
    kkk=0;a=s;
	for (int i=0;i<a.length()-1;i++)
    if (a[i]==A&&a[i+1]==B){a[i]=a[i+1]=12;kkk++;break;}
    for (int i=0;i<a.length()-1;i++)if (a[i]==B&&a[i+1]==A&&kkk){ printf("YES\n");exit(0);}
}
int main(){
    cin>>a;
	s=a; 
    ltt('A','B'); 
    printf("NO\n");
    return 0;
}
```
**然而你会发现Wa了**，为什么呢？

举个反例：ABAAB

 _我机房上一届有个大佬教我：正着贪不行就反着贪，实在不行两边以前贪，~~不放心再从中间贪一次~~_ 

我们再贪一次，贪BA之后再贪AB，这样就A了：

```
#include <bits/stdc++.h>
using namespace std;
string a,s;
int kkk;
inline void ltt(char A,char B){
    kkk=0;a=s;
	for (int i=0;i<a.length()-1;i++)
    if (a[i]==A&&a[i+1]==B){a[i]=a[i+1]=12;kkk++;break;}
    for (int i=0;i<a.length()-1;i++)if (a[i]==B&&a[i+1]==A&&kkk){ printf("YES\n");exit(0);}
}
int main(){
    cin>>a;
	s=a; 
    ltt('A','B');
    ltt('B','A');    
    printf("NO\n");
    return 0;
}
```



---

## 作者：Steven_Meng (赞：0)

### 注意TLE，不能用O(n^2)的算法。
思路：
先把‘AB’找出并且“和谐”，再找‘BA’;再把‘BA’找出并且“和谐”，再找‘AB’;

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int main(){
    string a;
    cin>>a;
    string tmp=a;
    int cnt=0;
    for (int i=0;i<a.length()-1;i++){
        if (a[i]=='A'&&a[i+1]=='B'){
            a[i]=a[i+1]='~';
            cnt++;
            break;
        }
    }
    for (int i=0;i<a.length()-1;i++){
        if (a[i]=='B'&&a[i+1]=='A'){
            if (cnt!=0){
                printf("YES\n");
                return 0;
            }
        }
    }
    a=tmp;
    cnt=0;
    for (int i=0;i<a.length()-1;i++){
        if (a[i]=='B'&&a[i+1]=='A'){
            a[i]=a[i+1]='~';
            cnt++;
            break;
        }
    }
    for (int i=0;i<a.length()-1;i++){
        if (a[i]=='A'&&a[i+1]=='B'){
            if (cnt!=0){
                printf("YES\n");
                return 0;
            }
        }
    }
    printf("NO\n");
    return 0;
}
```

---

## 作者：B_1168 (赞：0)

样例已经很明确的告诉我们：`ABA`或`BAB`只能作为`AB`或`BA`的一个字串，而不能是两个。

如何处理这种特殊情况？我们可以在每次找到`ABA`或`BAB`的时候记录他们的出现，然后用空格替代。在所有的`ABA`或`BAB`被统计后，我们可以另外统计`AB`或`BA`的出现，同样记录下来。

显然，如果一个字符串有两个形如`ABA`或`BAB`的子串，该字符串必同时有`AB`和`BA`两个子串。因为形如`ABA`或`BAB`的子串可客串`AB`或`BA`子串，因此需要稍加判断，具体可见程序。

利用这种方法，可以最小化本题的实操难度，并以$O(n)$的复杂度通过本题。


```python
n=input()

a=0;b=0;c=0

for i in range(0,len(n)-2):
    if n[i]=='A' and n[i+1]=='B' and n[i+2]=='A':
        c+=1
        n[i]=' '
        n[i+1]=' '
        n[i+2]=' '
    if n[i]=='B' and n[i+1]=='A' and n[i+2]=='B':
        c+=1
        n[i]=' '
        n[i+1]=' '
        n[i+2]=' '

if c>=2:
    print("YES")
    exit()

for i in range(0,len(n)-1):
    if n[i]=='A' and n[i+1]=='B':
        a+=1
    if n[i]=='B' and n[i+1]=='A':
        b+=1

if a&b or a&c or b&c:
    print("YES")
    exit()
else:
    print("NO")
```


---

