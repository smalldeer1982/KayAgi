# [Aya Round 1 A] 幻想乡扑克游戏

## 题目背景

**Problem Number:** [$\textit{22}$](https://www.luogu.com.cn/training/1392)

在能力卡牌异变之后，幻想乡的少女们将多余的卡牌收集起来，仿照外界人的「斗地主」这一游戏，进行了愉快的玩耍。

## 题目描述

斗地主是一种使用 $\tt A$ 到 $\tt K$ 加上大小王的共 $54$ 张扑克牌来进行的游戏，其中大小王各一张，其它数码牌各四张。在斗地主中，牌的大小关系根据牌的数码表示如下：

$$\tt 3<4<5<6<7<8<9<10<J<Q<K<A<2<\stackrel{\mathclap{\color{white}\textbf{\textit{wxy}}}}{\text{小王}} < \text{大王}$$

且牌的大小关系和花色无关。

游戏开始时，将会给 $3$ 名玩家各自发放 $17$ 张牌作为手牌，余下三张作为底牌。**玩家会将牌从大到小排序理好**，然后根据自己牌型的好坏程度来选择是否叫地主。

你认为，如果自己的手牌中存在王炸（即大小王各一张）或者至少一个炸弹（即四张数码相同的牌），则你会选择叫地主。

请实现一个程序来判断你是否应该叫地主。

## 说明/提示

### 样例解释

> 对于数据 $1$，输入数据相当于下面的手牌（忽略花色）：
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/g56d0ywv.png)
> 
> 该手牌中存在炸弹：
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/6sal0bye.png)
> 
> 故你选择叫地主。

> 对于数据 $2$，输入数据相当于下面的手牌（忽略花色）：
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/6g2jrx6t.png)
> 
> 该手牌中存在王炸：
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/1ulc1sxz.png)
> 
> 故你选择叫地主。

> 对于数据 $3$，输入数据相当于下面的手牌（忽略花色）：
> 
> ![](https://cdn.luogu.com.cn/upload/image_hosting/5qb6bwen.png)
> 
> 该手牌中不存在王炸和炸弹。故你选择不叫地主。

### 数据范围与约定

对于 $100\%$ 的数据，$1 \le T \le 10^4$。**保证牌已经预先理好**。

## 样例 #1

### 输入

```
3
X2AAKKKKQT9765433
DX22AKKQJTT884443
X2AAAKQQJT8554433```

### 输出

```
Yes
Yes
No```

# 题解

## 作者：chen_zhe (赞：24)

## 解法一

我们可以使用一个桶 `b[]`，将牌全部存入桶中。这样，当 `b[i]>=4` 即可表明有炸弹，而当 `b['D']>0 && b['X']>0` 就说明有大小王存在。这样即可通过本题。注意开桶的做法要多测清空，否则罚时两行泪。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main()
{
    int T,b[128];
    cin >> T;
    while (T--)
    {
        memset(b,0,sizeof(b));//多测清空
        bool flag=false;
        string s;
        cin >> s;
        for (int i=0;i<s.length();i++)//将牌放入桶中
            b[s[i]]++;
        if (b['X']>0 && b['D']>0)//判断是否存在大小王
            flag=true;
        for (int i=1;i<=127 && !flag;i++)//判断是否存在炸弹
        {
            if (b[i]>=4)
                flag=true;
        }
        puts(flag?"Yes":"No");
    }
    return 0;
}
```

## 解法二

实际上，由于牌已经保证了被理好，因而我们可以直接扫一遍牌。对于字符串 `s`，只要有 `s[i]==s[i+1] && s[i+1]==s[i+2] && s[i+2]==s[i+3]`，即可说明存在炸弹。由于只有一副牌，因此只要判断 `s[0]` 与 `s[1]` 是否是王即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        bool flag=false;
        string s;
        cin >> s;
        if (s[0]=='D' && s[1]=='X')//判断大小王
            flag=true;
        for (int i=0;i<s.length()-3 && !flag;i++)//扫描一遍牌，看是否存在炸弹
        {
            if (s[i]==s[i+1] && s[i+1]==s[i+2] && s[i+2]==s[i+3])
                flag=true;
        }
        puts(flag?"Yes":"No");
    }
    return 0;
}
```

---

## 作者：Andy_L (赞：15)

$\color{#E74C3C}\text{温馨提示:}$

$\color{#E74C3C}\text{遇见题解勿抄袭，棕名封号两行泪。}$


[题目传送门](https://www.luogu.com.cn/problem/P8466)

---

### 思路

这道题其实很简单，直接使用 ```string``` 中的查找和计数函数! 

统计函数模板：

```cpp
int cnt=count(字符串.begin(), 字符串.end(), 要查找的字符);
```

查找函数模板：

```cpp
if (字符串.find(字符串) == string::npos ) 语句1; //没找到 
if (字符串.find(字符串) != string::npos ) 语句2; //找到了
```



好了，明白了思路，那就上代码了！

---

$$\text{Coding Time}$$


```cpp
#include <bits/stdc++.h>

using namespace std;

int t,cnt;
string a;
bool flag;

int main()
{
	scanf("%lld",&t);
	while (t--)//注意是多组数据！
	{
		cin>>a;
		flag=false;
        if(a.find('D') != string::npos &&a.find('X')!=string::npos)//如果有王炸
		{
		    printf("Yes\n");
			continue;
		}
		for (int i=0;i<a.length();i++)//枚举，查找第i张牌
		{
			cnt=count(a.begin(), a.end(), a[i]);//查找有几个 相同的牌
			if(cnt>=4)//如果有四个相同的牌
			{
				printf("Yes\n");//输出Yes 
				flag=true;//标记 
				break;
			}
		}
		if(!flag) printf("No\n");//如果没有炸，输出No
	}
	return 0;//完结，撒花 
}  
```

---

## 作者：ShanCreeperPro (赞：4)

# P8466 [Aya Round 1 A] 幻想乡扑克游戏 題解

### 题意

给定 $T$ 个字符串，若字符串中有 'D' 和 'X' 或有 4 个相同元素输出 Yes，否则输出 No。

啊赛时居然挂了。

***

分析题目，发现判断是否拿地主主要看 2 个条件：

- 是否有王炸。

王炸，指一个人的手牌中同时拥有大王和小王，本题中用 `D` 和 `X` 表示。

发现题目中说明了牌已经排好了序，所以只要查找前 2 张牌是不是大王小王即可：

```cpp
inline bool King(void){
    if(str[0]=='D'&&str[1]=='X') return true;
}
```

- 是否有炸弹

炸弹，指一个人的手牌中有 4 张点数相同的牌称为炸弹。

由于总牌数只有 17 张，我们可以大胆枚举，从第一张牌开始，判断这张牌和下面四张牌的点数是否一致：

```cpp
inline bool Boom(void){
    for(int i=0;i<17;i++)
        if(str[i]==str[i+1]&&str[i+1]==str[i+2]&&str[i+2]==str[i+3])
            return true;
}
```

注意，本题有 $T$ 组数据，而不是只有 3 个人！

核心代码如下：



```cpp
class Fight_Against_Landlords
{
public:
    std::string str;
    inline bool King(void){
        if(str[0]=='D'&&str[1]=='X') return true;
    }
    inline bool Boom(void){
        for(int i=0;i<17;i++)
            if(str[i]==str[i+1]&&str[i+1]==str[i+2]&&str[i+2]==str[i+3])
                return true;
    }
};
```

###### 吐槽：這真的是入門模擬賽嘛


---

## 作者：落花月朦胧 (赞：4)

# 题意

给你一个长度为 $17$ 的字符串，问你会不会叫地主。

下面两个条件均可以让你叫地主

+ 你的牌中存在王炸。
+ 你的牌中存在至少一个炸弹。

# 题解

显然就是一个模拟。

对于上述的两个条件，我们分别用 `f1`， `f2` 记录，最后是否叫地主通过 `f1 | f2` 来判断即可。

对于 `f1`：

由于数据保证已经帮你处理好，我们只需要判断前两张牌是否刚好就是大王和小王即可。

对于 `f2`：

在这个字符串中遍历一次，暴力判断是否有炸弹，就是判断是否有 4 个相同字符连在一起。

# 代码

时间复杂度就是 $\mathcal{O} (nt)$。

```cpp
void solve() {
    std::string s;
    std::cin >> s;

    int f1 = 0, f2 = 0;
    if (s[0] == 'D' && s[1] == 'X') f1 = 1;
    for (int i = 0; i + 3 < s.size(); i++) {
        if (s[i] == s[i + 1] && s[i + 1] == s[i + 2] && s[i + 2] == s[i + 3]) {
            f2 = 1;
            break;
        }
    }
    if (f1 | f2) {
        std::cout << "Yes\n";
    } else{
        std::cout << "No\n";
    }
}
```

---

