# Alice, Bob, Two Teams

## 题目描述

Alice and Bob are playing a game. The game involves splitting up game pieces into two teams. There are $ n $ pieces, and the $ i $ -th piece has a strength $ p_{i} $ .

The way to split up game pieces is split into several steps:

1. First, Alice will split the pieces into two different groups $ A $ and $ B $ . This can be seen as writing the assignment of teams of a piece in an $ n $ character string, where each character is $ A $ or $ B $ .
2. Bob will then choose an arbitrary prefix or suffix of the string, and flip each character in that suffix (i.e. change $ A $ to $ B $ and $ B $ to $ A $ ). He can do this step at most once.
3. Alice will get all the pieces marked $ A $ and Bob will get all the pieces marked $ B $ .

The strength of a player is then the sum of strengths of the pieces in the group.

Given Alice's initial split into two teams, help Bob determine an optimal strategy. Return the maximum strength he can achieve.

## 说明/提示

In the first sample Bob should flip the suffix of length one.

In the second sample Bob should flip the prefix or the suffix (here it is the same) of length $ 5 $ .

In the third sample Bob should do nothing.

## 样例 #1

### 输入

```
5
1 2 3 4 5
ABABA
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
AAAAA
```

### 输出

```
15
```

## 样例 #3

### 输入

```
1
1
B
```

### 输出

```
1
```

# 题解

## 作者：very_easy (赞：2)


# 思路
这一题还是比较简单的，可以使用贪心算法解决，有一个数组 $p$ 又来积分，由于是要找最大能量，所以可以先遍历一下前缀，再遍历一下后缀，看哪个能量更多，先求一下本来可以获得的能量，分别放在变量 $a$ 和 $b$ 中，比较 $a$、$b$ 和 $ans$ 就行。
# AC Code
```c++
#include<iostream>
using namespace std;
const int N=5*1e5+5;
long long p[N],x[N],n,ans;//用x存当前是否能获得能量 
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>p[i];
	}
    for(int i=1;i<=n;i++){
    	char s;
        cin>>s;
        if(s=='A'){
        	x[i]=1;
		}
        ans+=x[i]*p[i];//如果能获得能量就是1*p[i]=p[i],否则就是0*p[i]=0 
    }
	long long a=ans,b=ans;//分别记录一下 
    for(int i=1;i<=n;i++){//遍历前缀 
        if(x[i]==1){
        	a-=p[i];
		}
        else{
			a+=p[i];
		}
        ans=max(ans,a);
    }
    for(int i=n;i>=1;i--){//遍历后缀 
        if(x[i]==1){
        	b-=p[i];
		}
        else{
        	b+=p[i];
		}
        ans=max(ans,b);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：drah_yrev (赞：0)

## 题意
[题目传送门](https://www.luogu.com.cn/problem/CF632B)

题目讲的是初始，有设定一个长度为 $n$ 字符串 $AB$ 串（仅有 $A$ 和 $B$ 的字符串），和积分数组 $P$。

我们可以选择某个前缀或后缀进行翻转（指原本的 $A$ 变为 $B$，$B$ 变为 $A$），当然也可以不选。

结果计算：

字符串第 $i$ 个字符
若为 $B$，则获得 $P_i$ 点能量。求进行翻转操作后所能得到的最大能量。
## 思路
先计算原本数组（未改动）可以获得的能量之和。

然后用两个不同的变量储存。

接着分别枚举前缀和后缀，

最后计算改动后的最大值并输出。
## 代码
```cpp
#include<iostream>
using namespace std;
long long a[500005],b[500005],x,y,n,ans;
char s;
int main(){
    cin>>n;//输入n 
    for(int i=0;i<n;i++)cin>>a[i];//输入a[i] 
    for(int i=0;i<n;i++){
        cin>>s;//一个一个读取字符 
        b[i]=s=='A'?1:0;//判断是否为'A' 
        ans+=b[i]*a[i];//读取总和 
    }
	x=y=ans;//赋值 
    for(int i=0;i<n;i++){//枚举前缀 
        if(!(b[i]-1))x-=a[i];// 如果b[i]=1，说明当前字符为A，让x去减这一位的权值 
        else x+=a[i];//如果b[i]=0，说明当前字符为B，让x去加这一位的权值 
        if(x>ans)ans=x;//轮换，修改最大值 
    }
    for(int i=n-1;i>0;i--){//枚举后缀 
        if(!(b[i]-1))y-=a[i];//如果b[i]=1，说明当前字符为A，让y去减这一位的权值 
        else y+=a[i];//如果b[i]=0，说明当前字符为B，让y去加这一位的权值 
        if(y>ans)ans=y;//轮换，修改最大值
    }
    cout<<ans<<endl;//输出进行翻转操作后所能得到的最大能量。 
    return 0;//byebye 
}
```


---

## 作者：hxhhxh (赞：0)

## 大意

给定一个长度为 $ n $ 的数组 $ a $ 和一个长度为 $ n $ 的字符串 $ S $ 。如果 $ S_i $ 为`A`，表示 $ a_i $ 属于`Alice`，否则属于`Bob`。`Bob`可以选择字符串中的一个前缀或后缀（可以不选），并将其中的`A`换成`B`，`B`换成`A`，求`Bob`操作可以使自己拥有的 $ a_i $ 的和的最大值。

## 思路

枚举选的前缀或后缀的长度。

首先记录一下不操作时`Bob`拥有的 $ a_i $ 的和。依次加上反转 $ S_1,S_2,\dots $ 带来的权值变化，相当于依次计算反转前缀的权值。后缀同理。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[500005],t,ans;
char ch[500005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	cin>>ch+1;
	for(int i=1;i<=n;i++) if(ch[i]=='B') t+=a[i];
	for(int i=1,j=t;i<=n;i++){
		if(ch[i]=='A') j+=a[i];
		else j-=a[i];
		ans=max(ans,j);
	}
	for(int i=n,j=t;i>=1;i--){
		if(ch[i]=='A') j+=a[i];
		else j-=a[i];
		ans=max(ans,j);
	}
	cout<<max(t,ans);
	return 0;
}

```

---

## 作者：DevOvO (赞：0)

$\huge{\text{题意}}$

$\ \ $给你一个长度为$n$的只包含字母$A$和$B$字符串，并告诉你字符串每一位的价值，你可以选择该字符串任意长度的前缀或后缀进行操作，将所有$A$换成$B$，所有$B$换成$A$，但只能这样操作一次。求字符串中所有$B$对应的价值总和最大为多少。

-----------------------------

$\huge{\text{题解}}$

记录一下$A$和$B$每一位的前缀和与后缀和，暴力枚举所有前缀和后缀，每次用初始$B$的价值总和减去该前缀或后缀的$B$的价值再加上$A$的价值更新一下答案，直接输出最大值即可。

--------------------------------------

$\huge{\text{代码}}$

```cpp
/*/Saya-Javelin/*/

/*
此处省略我那又臭又长的头文件和奇怪的快读
*/

const int MAX=500005;
int n;
int v[MAX];
char t[MAX];
int a1[MAX], a2[MAX], b1[MAX], b2[MAX];
int tot, ans=0;

signed main (void) {
    read (n);
    for (int i=1; i<=n; ++i) 
        read (v[i]);
    scanf ("%s", t+1);
    for (int i=1; i<=n; ++i) {//A和B的前缀和
        a1[i]=a1[i-1], b1[i]=b1[i-1];
        if (t[i]=='A') a1[i]+=v[i];
        if (t[i]=='B') b1[i]+=v[i];
    }
    for (int i=n; i>=1; --i) {//A和B的后缀和
        a2[i]=a2[i+1], b2[i]=b2[i+1];
        if (t[i]=='A') a2[i]+=v[i];
        if (t[i]=='B') b2[i]+=v[i];
    }
    tot=b1[n];//初始B的总和
    for (int i=0; i<=n; ++i) 
        ans= Max (ans, tot-b1[i]+a1[i]);
    for (int i=0; i<=n; ++i)
        ans= Max (ans, tot-b2[i]+a2[i]);
    //更新答案
    writeln (ans);
    return 0;
}//完结撒花

```

---

## 作者：szh_AK_all (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF632B)

这道题可以用暴力枚举来做，分别枚举前缀和后缀，然后打擂台，记录最大值，最后输出即可。在枚举时，如果这个字母原来是 `B`，那么变化后总权值就会缩小，减去这一位的权值；反之，总权值就会变大，加上这一位的权值。


具体的，我们将每一位的力量值当做这一位的权值。用一个变量记录初始时的有效权值和。先枚举前缀，改变前一位、前两位、前三位...以此类推，直到改变所有字符。在枚举的过程中，我们看改变后总权值是否变大，如果变大了，那么更新总权值。通过打擂的方式，最终得出最大总权值（后缀类同）。
## 直接上代码！
```c
#include<iostream>
using namespace std;
long long a[500005],b[500005];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    long long tmp=0;
    for(int i=1;i<=n;i++)
    {
        char s;
        cin>>s;
        if(s=='A')//将'A'记为0
            b[i]=0;
        else
            b[i]=1;//将'B'记为1
        tmp+=b[i]*a[i];
    }
    long long ans=tmp;
    long long k=tmp;
    for(int i=1;i<=n;i++)//枚举前缀
    {
        if(b[i]==1)
            ans-=a[i];
        else
            ans+=a[i];
        if(ans>tmp)
            tmp=ans;
    }
    for(int i=n;i>=1;i--)//枚举后缀
    {
        if(b[i]==1)
            k-=a[i];
        else
            k+=a[i];
        if(k>tmp)
            tmp=k;
    }
    cout<<tmp;
    return 0;
}
```


---

