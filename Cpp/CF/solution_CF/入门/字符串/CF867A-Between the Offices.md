# Between the Offices

## 题目描述

As you may know, MemSQL has American offices in both San Francisco and Seattle. Being a manager in the company, you travel a lot between the two cities, always by plane.

You prefer flying from Seattle to San Francisco than in the other direction, because it's warmer in San Francisco. You are so busy that you don't remember the number of flights you have made in either direction. However, for each of the last $ n $ days you know whether you were in San Francisco office or in Seattle office. You always fly at nights, so you never were at both offices on the same day. Given this information, determine if you flew more times from Seattle to San Francisco during the last $ n $ days, or not.

## 说明/提示

In the first example you were initially at San Francisco, then flew to Seattle, were there for two days and returned to San Francisco. You made one flight in each direction, so the answer is "NO".

In the second example you just flew from Seattle to San Francisco, so the answer is "YES".

In the third example you stayed the whole period in San Francisco, so the answer is "NO".

In the fourth example if you replace 'S' with ones, and 'F' with zeros, you'll get the first few digits of $ π $ in binary representation. Not very useful information though.

## 样例 #1

### 输入

```
4
FSSF
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2
SF
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
10
FFFFFFFFFF
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
10
SSFFSFFSFF
```

### 输出

```
YES
```

# 题解

## 作者：Eismcs (赞：4)

这题并不难，因为给了长度，所以无需运用字符串，用在线读入就行了

AC代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    char c,k;
    int x=0,y=0,n;
    scanf("%d%c",&n,&c);
    //把换行读入，这就是在线读入的坑点。
    k=getchar();
    for(int i=1;i<n;i++){
        c=getchar(); 
        if(k!=c){
            if(k=='S')x++;
            else y++;
        }
        k=c;
    }//在线模拟
    if(x>y)printf("YES\n");
    else printf("NO\n");
    return 0;
}
```

---

## 作者：绝顶我为峰 (赞：3)

这大概是史上最短的代码了（滑稽）

分析题目，会发现条件是YES的都有以下特点：

1.首先，至少2天

2.第一天待在西雅图，否则无论如何从西雅图飞向旧金山的航班都不会比旧金山飞往西雅图的多

3.最后一天在旧金山，否则两个方向的会一样多

这样是不是很简单了呢~

什么，代码？┻┳|･ω･)问我？

拿起~~代码~~AK-47，去吧

```cpp
#include<iostream>
#include<string>
using namespace std;
string s;
int main()
{
    int n;
    cin>>n;
    cin>>s;
    if(n!=1&&s[0]=='S'&&s[n-1]=='F')//同时满足三个条件
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
    return 0;
}
```

---

## 作者：OdtreePrince (赞：2)

# -字符串技巧-

>这道题是纯字符串er，

>判断水过哦...

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    int l,sum1=0,sum2=0;
    string s;
    cin>>l>>s;
    for(int i=0;i<l-1;i++){
        if(s[i]=='S'&&s[i+1]=='F') sum1++;
        if(s[i]=='F'&&s[i+1]=='S') sum2++;
    }
    if(sum1>sum2) cout<<"YES";
    else cout<<"NO";
    cout<<endl;
    return 0;
}~~~

---

## 作者：RBI_GL (赞：0)

**题目大意：**
----
输入的字符串中，如果S->F，那么西雅图飞向旧金山航班数+1；如果F->S，那么旧金山飞向西雅图+1。

-------------

**Code:**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,sum1=0,sum2=0;
char s[105];

bool bj(int a, int b)
{
	if (a>b) return true;
	else return false;
}

int main()
{
    cin>>n;
    for (int i=0;i<n;i++) cin>>s[i]; //输入
    for(int i=0;i<n-1;i++) //判断 & 统计
	{
        if(s[i]=='S' && s[i+1]=='F') sum1++;
        if(s[i]=='F' && s[i+1]=='S') sum2++;    //如果S->F，那么西雅图飞向旧金山航班数+1；如果F->S，那么旧金山飞向西雅图+1。
    }
    if (bj(sum1,sum2) == true) cout<<"YES"; 
    else cout<<"NO";  //比较 & 输出
    return 0;
}
```

**不含注释版：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,sum1=0,sum2=0;
char s[105];

bool bj(int a, int b)
{
	if (a>b) return true;
	else return false;
}

int main()
{
    cin>>n;
    for (int i=0;i<n;i++) cin>>s[i];
    for(int i=0;i<n-1;i++)
	{
        if(s[i]=='S' && s[i+1]=='F') sum1++;
        if(s[i]=='F' && s[i+1]=='S') sum2++;    
    }
    if (bj(sum1,sum2) == true) cout<<"YES";
    else cout<<"NO";
    return 0;
}
```



---

## 作者：zhn0707 (赞：0)

这是一篇python的题解。

我们首先分析一下：如果S->F，那么西雅图飞向旧金山航班数+1；如果F->S，那么旧金山飞向西雅图+1。

这样一来，不就很简单了吗？上代码！
```python
n = int(input())
s = input()
a = 0
b = 0
for i in range(0, (n - 1)):
    if (s[i] == 'S' and s[(i + 1)] == 'F'):
        a += 1
    if (s[i] == 'F' and s[(i + 1)] == 'S'):
        b += 1
if (a > b):
    print('YES')
else:
    print('NO')
```


---

