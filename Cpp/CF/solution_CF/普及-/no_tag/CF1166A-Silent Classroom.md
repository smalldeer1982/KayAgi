# Silent Classroom

## 题目描述

There are $ n $ students in the first grade of Nlogonia high school. The principal wishes to split the students into two classrooms (each student must be in exactly one of the classrooms). Two distinct students whose name starts with the same letter will be chatty if they are put in the same classroom (because they must have a lot in common). Let $ x $ be the number of such pairs of students in a split. Pairs $ (a, b) $ and $ (b, a) $ are the same and counted only once.

For example, if there are $ 6 $ students: "olivia", "jacob", "tanya", "jack", "oliver" and "jessica", then:

- splitting into two classrooms ("jack", "jacob", "jessica", "tanya") and ("olivia", "oliver") will give $ x=4 $ ( $ 3 $ chatting pairs in the first classroom, $ 1 $ chatting pair in the second classroom),
- splitting into two classrooms ("jack", "tanya", "olivia") and ("jessica", "oliver", "jacob") will give $ x=1 $ ( $ 0 $ chatting pairs in the first classroom, $ 1 $ chatting pair in the second classroom).

You are given the list of the $ n $ names. What is the minimum $ x $ we can obtain by splitting the students into classrooms?

Note that it is valid to place all of the students in one of the classrooms, leaving the other one empty.

## 说明/提示

In the first sample the minimum number of pairs is $ 1 $ . This can be achieved, for example, by putting everyone except jose in one classroom, and jose in the other, so jorge and jerry form the only chatty pair.

In the second sample the minimum number of pairs is $ 2 $ . This can be achieved, for example, by putting kambei, gorobei, shichiroji and kyuzo in one room and putting heihachi, katsushiro and kikuchiyo in the other room. In this case the two pairs are kambei and kyuzo, and katsushiro and kikuchiyo.

In the third sample the minimum number of pairs is $ 4 $ . This can be achieved by placing three of the students named mike in one classroom and the other two students in another classroom. Thus there will be three chatty pairs in one classroom and one chatty pair in the other classroom.

## 样例 #1

### 输入

```
4
jorge
jose
oscar
jerry
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
kambei
gorobei
shichiroji
kyuzo
heihachi
katsushiro
kikuchiyo
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
mike
mike
mike
mike
mike
```

### 输出

```
4
```

# 题解

## 作者：兮水XiShui丶 (赞：3)

这可能是我有史以来写的时间最长的一个Div2的A题了。。。

思路是贪心，我们可以这么想：如果有两个姓名首字母相同的人，那么把两个人分别放在不同的房间，那么这两个人便不会相互交流，所以我们可以把任意两个姓名首字母相同的人看成一个组，每一个组两两分到不同教室中，那么这样得到的答案一定是最优的。  

而且我们注意到，对一个人来说，唯一有影响的就是这个人的姓名的第一个字母，所以我们完完全全可以不把整个姓名都存起来，而是转化成数字，这样方便下一步的工作。  

显然，无论怎么样，前两个人分别放到不同教室里是最优的，所以我们可以从第三个人开始考虑，如果第$i$个人和第$i-2$个人姓名首字母相同的话，我们才不得不把这两个人分到同一组教室内，同时记录一下在这个教室内，已经有多少“对”这样的人了。 

最后统计答案，答案便是$\sum_{i=1}^n \frac {num[i]*(num[i]-1)}2$了

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>

inline int read () {
    int s = 0 , w = 1;
    char ch = getchar ();
    while ( ch > '9' || ch < '0' ) { if ( ch == '-' ) w = -1; ch = getchar ();}
    while ( ch >= '0' && ch <= '9' ) { s = s * 10 + ch - '0'; ch = getchar ();}
    return s * w;
}

const int N = 105;

int n , ans;
int num[N];
std :: map < int , int > mp;

inline bool cmp ( int x , int y ) {
    return x < y;
}

int main ( void ) {
    n = read ();
    for ( int i = 1 ; i <= n ; i++ ) {
    	std :: string x;
        std :: cin >> x;
        num[i] = ( int ) x[0];
    }
    std :: sort ( num + 1 , num + 1 + n , cmp );
    for ( int i = 3 ; i <= n ; i++ ) 
        if (num[i] == num[i - 2] ) 
            mp[num[i] + 1005 * ( i % 2 )]++;
    for ( auto it = mp.begin () ; it != mp.end () ; it++ ) 
    	ans += ( it->second + 1 ) * ( it->second ) / 2;
    printf ( "%d\n" , ans );
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

这道题思路比较容易想，因为如果他们的名字首字母相同，他们就会聊天，所以容易想到使用**数组计数**统计姓名的首字母。

循环枚举每个名字首字母，把个数平均分成一班和二班。知道人数，求有多少对，这是一个组合问题，可以用公式 $a\times(a+1)/2$ 计算，最后再加上去，就得到了结果。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,x,h;
int a[200];
string st;
void cl()
{
	for(int i=0; i<26; i++)
    {
    	s=(a[i]/2)*(a[i]/2-1)/2;
    	x=(a[i]-a[i]/2)*(a[i]-a[i]/2-1)/2;
    	h+=max(0,int(s+x));
    }
}
int main()
{
    cin>>n;
    for(int i=1; i<=n; i++)
    {
    	cin>>st;
    	a[st[0]-97]++;
    }
    cl();
    cout<<h;
    return 0;
}
```

---

## 作者：Novice233 (赞：1)

又是一道CF水题

这道题既然看的是名字的首字母 输入名字之后只有第一位是有用的

那么 用ascii代码来把字符转为数字 然后存在数组里就好了

附上一份丑陋代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[205],n,ans;
string s;
int m;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		m=s[0]-' '+32;
		a[m]++;
	} 
	for(int i=97;i<=122;i++){
		ans+=max(0,(a[i]/2)*(a[i]/2-1)/2+(a[i]-a[i]/2)*(a[i]-a[i]/2-1)/2);
		//cout<<a[i]<<endl;
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：AC_Dolphin (赞：1)

~~这是紫题？？？~~

这道题其实就是贪心，如果有偶数个以相同字符开始的字符串，那么就将这$n$个人分成$2$个$n/2$，如果有奇数个就分成$(n-1)/2$和$(n+1)/2$

那么，怎么算每个部分里的答案呢？设该部分有$n$个人，那么在这$n$个人中选取$2$人即为答案，所以$ans=C^2_n=n*(n-1)/2$，最后统计一下即可

$Code$:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100];
int c(int m,int n){
    if(m==0) return 0;	
    if(m<n) return 0;
        double temp = 1;
        if(n<m-n)
            return c(m,m-n);
        for(int i=0;i<m-n;++i){
            temp*=n+i+1;
            temp/=i+1;
        }

        return (int)temp;
    }
int main(){
    int n;
    cin>>n;
    string s;
    for(int i=1;i<=n;i++){
        cin>>s;
        a[s[0]-'a'+1]++;
    } 
    long long ans=0;
    for(int i=1;i<=26;i++){
        if(a[i]==0) continue;
        if(a[i]%2==0) ans+=c(a[i]/2,2)*2;
        else ans+=(c(a[i]/2,2)+c((a[i]+1)/2,2));
        //cout<<a[i]<<endl;
    }
    cout<<ans<<endl;
    return 0; 
}
```

---

## 作者：JustinXiaoJunyang (赞：0)

这些学生们在教室里摸鱼聊天，我们今天就来把他们聊天的学生对数尽可能缩小～

前排芝士（致小学生们）：

Q ：什么是组合数？

A ：组合数 $C^m_n$ 就是指从 $m$ 个人里选 $n$ 个人的方法数，计算方法是 $\dfrac{A^m_m}{A^m_n}$（转化为排列数）。

思路分析：

为了惩治他们，老师把他们分成两个教室里上课，名字首字母一毛一样的就会聊天。（玄）

贪心方法：

我们在这里算的是组合数。假如有 $n$ 位学生在聊天，那么就有 $C^2_n$ 对人聊天的情况。

贪心的最优化就是把人分成尽量平均分成两个班，举个栗子：

现在有 4 个人讲话，有两种分教室的方法：

- 1 人及 3 人：$C^2_1$ 第一个教室（这里当作没法讲话吧）及 $C^2_3$ 第二个教室和为 3 种。

- 2 人平分：$C^2_2$ 第一个教室及 $C^2_2$ 第二个教室和为 2 种。

我不举这么多例子了，反正平均分是最优的。

根据上面的贪心，把所有首字母情况算在一起就是答案。

参考代码：

```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

map <char, int> m;
int f(int x)
{
    return x * (x - 1) / 2;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        m[s[0]]++;
    }
    long long ans = 0;
    for (char i = 'a'; i <= 'z'; i++)
    {
        ans += f(m[i] / 2) + f(m[i] - m[i] / 2);
    }
    cout << ans << endl;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
现在有 $n$ 名学生，我们需要将这些学生分到两个班上。对于两名在同一班级的学生，如果他们的名字首字母相同，他们就会聊天。

现在给定这些学生的名字，问最少有多少对学生会在一起聊天。

**数据范围：$1\leqslant n\leqslant 100$。**
## Solution
这道题目主要用到贪心。具体来说，对于所有名字首字母相同的同学，将他们尽可能平均地分到两个班里面。例如，假如名字首字母为 R 的同学有 $5$ 名，那么我们就将 $2$ 个人分到 $1$ 班，$3$ 个人分到 $2$ 班。

然后，如果在一个班上且首字母相同的同学人数为 $x$，那么就相当于在这 $x$ 个人当中随机选出 $2$ 个人聊天，那么这些人当中聊天的学生对数为 $\begin{pmatrix}x\\2\end{pmatrix}=\dfrac{x(x-1)}2$。

依照这个思路直接模拟统计答案就好了。
## Code
```cpp
namespace Solution {
    int n, ans, vis[26]; string s;

    iv Main() {
        read(n);
        F(int, i, 1, n) cin >> s, vis[s[0] - 'a']++;
        F(int, i, 0, 25) {
            int x = vis[i] / 2, y = vis[i] / 2 + (vis[i] & 1);
            ans += (x * (x - 1) / 2 + y * (y - 1) / 2);
        }
        write(ans);
    }
}
```

---

## 作者：Huaji_King (赞：0)

首先，题目只需要首字母，那我们就可以把首字母转成数字，进行数组计数。

**解题思路：数组计数。**

其次，题目要求分到两个班上。平均分可以使题目最优解。

![](https://cdn.luogu.com.cn/upload/image_hosting/hcmj5s29.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以，我们只需把 26 个字母逐一查找，并把人数平均分到两个班上，用公式 $r*(r-1)/2$ 分别求出两个班的对数即可。


------------

# 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[30],n,sum,cl1,cl2;
string s;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>s;
		a[s[0]-'a'+1]++; //直接转成数字计数 
	}
	for(int i=1;i<=26;i++)//从a~z里找 
	{
		cl1=(a[i]/2)*(a[i]/2-1)/2;//1班 
		cl2=(a[i]-a[i]/2)*(a[i]-a[i]/2 -1)/2;//2班 
		sum+=max(0,cl1+cl2);//有可能出现负数 
	}
	cout<<sum;
	return 0;
}
```


---

