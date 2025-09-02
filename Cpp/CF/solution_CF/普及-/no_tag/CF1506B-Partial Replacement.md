# Partial Replacement

## 题目描述

You are given a number $ k $ and a string $ s $ of length $ n $ , consisting of the characters '.' and '\*'. You want to replace some of the '\*' characters with 'x' characters so that the following conditions are met:

- The first character '\*' in the original string should be replaced with 'x';
- The last character '\*' in the original string should be replaced with 'x';
- The distance between two neighboring replaced characters 'x' must not exceed $ k $ (more formally, if you replaced characters at positions $ i $ and $ j $ ( $ i < j $ ) and at positions $ [i+1, j-1] $ there is no "x" symbol, then $ j-i $ must be no more than $ k $ ).

For example, if $ n=7 $ , $ s= $ .\*\*.\*\*\* and $ k=3 $ , then the following strings will satisfy the conditions above:

- .xx.\*xx;
- .x\*.x\*x;
- .xx.xxx.

 But, for example, the following strings will not meet the conditions: - .\*\*.\*xx (the first character '\*' should be replaced with 'x');
- .x\*.xx\* (the last character '\*' should be replaced with 'x');
- .x\*.\*xx (the distance between characters at positions $ 2 $ and $ 6 $ is greater than $ k=3 $ ).

Given $ n $ , $ k $ , and $ s $ , find the minimum number of '\*' characters that must be replaced with 'x' in order to meet the above conditions.

## 样例 #1

### 输入

```
5
7 3
.**.***
5 1
..*..
5 2
*.*.*
3 2
*.*
1 1
*```

### 输出

```
3
1
3
2
1```

# 题解

## 作者：kdy20100729 (赞：11)

[CF1506B](https://www.luogu.com.cn/problem/CF1506B)这道题就一句话 —— 一点点分类、贪心 + 模拟。  
### 题意简述：  
在一个长度为 $n$ 字符串中， ```*``` 可以被修改为 ```x```，但修改后的字符串要满足任意两个 ```x``` 之间距离不能大于 $k$，同时第一个星号和最后一个星号必须改为 ```x```。现给定最大距离 $k$，求使得字符串满足条件所改变的字符的最小个数。  
### 思路：  
我们前面也讲了，是贪心+模拟。那么，如何贪心呢？  
很显然，只要我们使每两个 ```x``` 之间的距离尽量的接近 $k$ ( $\leq k$ )，那么答案就是最优解。  
因此，我们只需要，用一个 $last$ 记录上一个 ```*``` 的下标，然后暴力寻找下一个距离最接近 $k$ ( $\leq k$ ) 的 ```*``` 即可。
#### 注意事项：  
- 每次 $ans$ 和 $last$ 都要重新赋值。
- 最后还要判断一下最后一个 ```*``` 是否被累加过，如果没有，答案还要加 $1$。  

#### 下面奉上蒟蒻的 $AC$ 代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int t,n,k,ans,las,last;
signed main()
{
	cin >> t;
	while(t--)
	{
		ans=0;
		last=1e9;
		cin >> n >> k >> s;
		for(int i=0; i<n; i++)
		{
			if (s[i]=='*')
				las=i;
			if (s[i]=='*'&&last==1e9)
			{
				ans++;
				last=i;
				s[i]='x';
			}
			else if (s[i]=='*'&&i-last<k)
				continue;
			else if (s[i]=='*'&&i-last==k)
			{
				ans++;
				last=i;
				s[i]='x';
			}
			else if (s[i]=='*'&&i-last>k)
			{
				for(int j=i-1; j>=last; j--)
				{
					if (s[j]=='*')
					{
						ans++;
						last=j;
						s[j]='x';
						break;
					}
				}
			}
		}
		if (s[las]=='*')
			ans++;
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：きりと (赞：3)

**[题目传送门](https://www.luogu.com.cn/problem/CF1506B)**

### 题目大意

在一个字符串中， ’*‘ 号可以被修改为 ‘x’，但修改后的字符串要满足任意两个 'x' 之间距离不能大于 $k$ ，同时第一个星号和最后一个星号必须改变。现给定字符串长度 $n$ 和 最大距离$k$ ，求使得字符串满足条件所改变的字符的最小个数 。含有多组数据且保证有解。

### 解题思路

由于第一个星号必须变为 'x' 那我们只需要每一次尽量找距离在 $k$ 以内且最远的一个星号，改变它就彳亍了。然后在判断一下最后一个星号有没有被改变过，做一次特判就好。

具体实现就是贪心从距离为 $1$ 找到 $k$，记录一下当前找到的最远的星号，最后没找到就做一次反悔，反悔到当前最远端即可。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
signed main()
{
    int t,n,k;
    cin>>t;
    star:while(t--)
    {
        cin>>n>>k;
        cin>>s;
        int l=s.size()-1,la=-1,cnt=-1,ans=0,temp;    //cnt记录当前的最远端，temp用来试探最远端，la标记最后一次改变的*号，ans记录改变数量
        bool flag=0;
        for(int i=0;i<=l;i++)
        {
            if(s[i]=='.')
            {
                la=cnt;   //有.的时候也要更新，赛时这里调的有点久
                continue;
            }
            if(!flag)   //处理第一个*号
            {
                cnt=i;
                ans++;
                flag=1;
            }
            else
            {
                if(i-cnt<=k)
                {
                    temp=i;
                }
                else
                {
                    cnt=temp;
                    i=cnt;
                    ans++;
                }
            }
            la=cnt;
        }
        for(int i=l;i>=0;i--)   //处理最后一个星号
        {
            if(s[i]=='*')
            {
                if(i!=la)
                {
                    ans++;
                }
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}

```



---

## 作者：张语诚ZYC (赞：3)

## 题意翻译

有一个由 `.` 和 `*` 组成的字符串，你需要将 `*` 修改成 `x` ，使得每两个 `x` 之间的距离和小于等于 $k$。

特别地，第一个 `*` 和，最后一个 `*` 必须要改变。

求出当字符串满足条件时，最少需要改变的次数。

**本题有 $t$ 组测试数据**

第一行有一个变量 $t$ $(1\leq t \leq 500)$， 表示测试数据的数量。

对于每一组测试数据，第一行有两个变量 $n$ 和 $k$ $(1\leq k \leq n \leq 500)$。第二行有一个字符串，只包含 `.` 和 `*` 。

数据保证字符串中至少有一个`*`，且任意两个相邻的`*`字符之间的距离不超过  $k$ 。

## 题目分析

很明显，当字符串中有 $1$ 个 `*` 是，答案是 $1$ ，当字符串中有 $2$ 个 `*` 是，答案是 $2$ 。

当 `*` 的数量大于等于 $3$ 时，这时，**贪心**大法就派上用场了，然后暴力出奇迹。

从第一个 `*` 开始向后找到最远的地方，也就是 $k$ 的值。判断一下该位置是不是 `*` ，如果不是，就向前找，直到找到，由于题目保证有解，所以不需要特盘有没有解。然后再向后找，重复此操作，直到完成，最后输出操作的次数。

## $\texttt{AC Coode}$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int START=-1;
string data;
inline int read_int() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			w=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int core(int n,int k) {
	int len=data.size()-1;
	int last_char=START,cnt=START,ans=0,temp;
	bool flag=0;
	for(int i=0; i<=len; i+=1) {
		if(data[i]=='.') {
			last_char=cnt;
			continue;
		}
		if(flag==0) {
			cnt=i;
			ans++;
			flag=1;
		} else {
			if(i-cnt<=k) {
				temp=i;
			} else {
				cnt=temp;
				i=cnt;
				ans++;
			}
		}
		last_char=cnt;
	}
	for(int i=len; i>=0; i-=1) {
		if(data[i]=='*') {
			if(i!=last_char) {
				ans++;
			}
			break;
		}
	}
	return ans;
}
int main() {
	int	t=read_int();
	for(int k2=0; k2<t; k2+=1) {
		int n=read_int();
		int k=read_int();
		cin>>data;
		printf("%d \n",core(n,k));
	}
	return 0;
}
```

$$\texttt{The End by Yucheng}$$

---

## 作者：zct_sky (赞：1)

### Solution:
-----
简单贪心。

先确定第一个 `*` 和最后一个 `*` 的位置，判断距离是否小于等于 $k$。

如果小于 $k$，则直接输出 $2$（如果第一个 `*` 和最后一个 `*` 的位置相等（只有一个 `*`），那就输出 $1$）。

否则从第一个 `*` 的位置开始遍历，每 $k$ 个位置中找出一个最远的，然后将替换数量 $+1$，当遍历位置大于最后一个 `*` 的位置时，跳出循环，输出答案。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
#define re register
using namespace std;
inline ll read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
	return;
}
string a;
int len,k,t,st,ed,ans; 
int main(){
	t=read();
	for(;t;t--){
		ans=st=ed=0;
		len=read(),k=read();
		cin>>a;
		for(int i=0;i<len;i++){
			if(a[i]=='*'&&!st)st=i+1;
			if(a[i]=='*')ed=i+1;
		}
		st--;ed--;
		if(st==ed)puts("1");
		else if(ed-st<=k)puts("2");
		else{
			ans=2;
			int j;
			for(int i=st;i<ed;i=j)
				for(j=i+k;j<ed&&j>=i;j--)
					if(a[j]=='*'){
						ans++;
						break;
					}
			write(ans),puts("");
		}
	}
	return 0;
} 
```

---

## 作者：nalemy (赞：1)

## 题意简述

给你一个由`*`和`.`组成的字符串，要求替换掉其中一部分`*`为`x`，要求如下：

1. 必须替换掉第一个`*`和最后一个`*`
2. 替换后，每两个相邻的`x`之间的距离**不能大于** $k$（位置 $i$ 和位置 $j$ $(i<j)$ 的距离是$j-i$）

我们想让替换的个数尽可能少。求替换的个数。

## 题目分析

我们要让替换的个数尽可能少，可以让每两个相邻的`x`的间距尽可能大。但题目中已经限制了两个相邻`x`的最大值，我们就要在这个限度内达到最大。**形式化地讲**，对于每一个位置为 $i$ 的`x`，我们想让下一个`x`的位置为满足 $j\le i+k$ 的 $j_{max}$（当然位置$j$必须是个`*`）

### 明显是个贪心啊！

于是我们考虑将所有`x`**离散化**，然后用`upper_bound`找到第一个 $j\gt i+k$ 的 $j$，然后它的**前一个**就一定是最后一个满足 $j\le i+k$ 的值。这道题的解法就呼之欲出啦~

```C++
#include<iostream>
#include<algorithm>
#define N 50
using namespace std;

int pos[N];  // 离散化数组
int main() {
    string s;
    int q, n, k, l, cnt; cin >> q;
    while (q--) {
        // cnt赋值为1是因为题目要求取最后一个，要人工把它算上
        cin >> n >> k >> s, cnt = 1, l = 0;
        for (int i=0; i<n; i++) 
            if (s[i] == '*') pos[l++] = i;  // 离散化
        for (int i=0; i<l-1; cnt++)  // i<l-1是为了人工避开最后一个
            // 找出[i+1,l)中第一个大于pos[i]+k的位置，减一得到最后一个小于pos[i]+k的
            i = upper_bound(pos+i+1, pos+l, pos[i]+k) - pos - 1;
        cout << cnt << endl;
    }
    return 0;
}
```

>  代码里面有一个点要强调一下，第二个循环中要求`i<l-1`是因为，题目要求最后一个要取到，但是循环算到这里的时候就可能会出现一个问题，`upper_bound`已经找不到大于 $pos[i]+k$ 的数了。那么我们就规避掉这个问题，要求它不管最后一个了，而在前面人工给`cnt`加 $1$。

---

## 作者：feicheng (赞：1)

## [$\text{Description}$](https://www.luogu.com.cn/problem/CF1506B)


给定长度为 $n$ 的字符串 $s$ 和 $k$，字符串仅由 `.` 和 `*` 组成，初始将最靠前和最靠后的 `*` 变为 `x`，然后你可以任意将 `*` 变为 `x`，求最小的将 `*` 变为 `x` 的次数使得任意两个 `x` 之间的距离小于等于 $k$。

数据保证有解。


## $\text{Solution}$


考虑贪心，对于每一个 `x` ，寻找离他最远的 `*` 且满足距离不大于 $k$，将这个 `*` 变成 `x`。

关于正确性：因为要使任意两个相邻的 `x` 之间距离都不超过 $k$ ，所以选择尽可能远的能够使 `x` 之间的距离尽可能远，这样子就可以使 `x ` 尽可能少。

## $\text{Code}$

```cpp
/*If you are full of hope,you will be invincible*/
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
using ll = long long ;
using lb = long double;
using u32 = unsigned int;
using u64 = unsigned long long ;
using std::cin ;
using std::cout ;
std::mt19937 hpy(time(nullptr)+(unsigned long long)(new char));
int t,n,k,ans,cnt,a[100],vis[100];
char s[100];
inline void solve() {
    memset(a,0,sizeof a),memset(vis,0,sizeof vis),cnt = 0,ans = 0;
    for(int i = 1 ; i <= n;++i) {
        if(s[i] == '*') a[++cnt] = i; 
    } if(cnt <= 2) return ans = cnt,void();//特判
    ans = 2;
    vis[a[1]] = vis[a[cnt]] = 1;  
    for(int i = 1;i <= cnt;++i)  {
        if(vis[a[i]] == 1) {
            for(int j = std::min(a[i]+k,n);j > a[i];--j) {
                if(s[j] == '*') {
                    if(vis[j]) break;
                    vis[j] = 1,++ans ;
                    break ;
                }
            } 
        }
    }
}
int main() {
	std::ios::sync_with_stdio(false);
	scanf("%d",&t);
	while(t--) scanf("%d%d %s",&n,&k,s+1),solve(),printf("%d\n",ans); 
	return 0;
}
```



---

## 作者：yimuhua (赞：1)

## 题意：
在一个字符串中， '*' 号可以被修改为 'x'，但修改后的字符串要满足任意两个 'x' 之间距离不能大于 $k$，同时第一个星号和最后一个星号必须改变。现给定字符串长度 $n$ 和 最大距离 $k$ ，求使得字符串满足条件所改变的字符的最小个数。

## 思路：
首先，题目说明**保证有解**，则字符串里只有一个 * 时，答案就为 $1$。那么字符串里只有两个 * 的时候，答案必为 $2$。

**贪心思路：**

修改离上一个 * 最远的但是距离在 $k$ 以内一个 *，能使改的 * 数最少。因为每一个 * 都会影响后面的 *。在距离范围的边缘修改，能使下一个 * 尽量远，改的次数尽量小。

**关于代码：**

求出第一个 * 和最后一个 * 的位置，当当前 * 的位置加 $k$ **大于等于**终点的位置就可以跳出循环，而在循环中只要找距离上一个 * 最远且距离又不超过 $k$ 的 * 就可以了。

## AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, p1, p2, n, k;
int main() {
    cin >> t;
    while(t--) {
        string s;
        int sum = 2;
        cin >> n >> k >> s;
        for(int i = 0; i < s.size(); i++)//找第一个*的位置
            if(s[i] == '*') {
                p1 = i;
                break;
            }
        for(int i = s.size() - 1; i >= 0; i--)//找最后一个*的位置
            if(s[i] == '*') {
                p2 = i;
                break;
            }
        if(p1 == p2) {//如果只有一个*
            cout << 1 << endl;
            continue;
        }
        if(p2 - p1 <= k) {//如果只有两个*
            cout << 2 << endl;
            continue;
        }
        while(1) {
            int x = p1 + k;
            if(x >= p2)//当前*的位置距离最后一个*的距离小于等于k
                break;
            for(int i = x; i >= p1; i--)//寻找离上一个*最远但是距离在k以内的*
                if(s[i] == '*') {
                    p1 = i;
                    break;
                }
            sum++;//修改次数++
        }
        cout << sum << endl;//一定要有换行
    }
    return 0;
}
```


---

## 作者：Dragonbell_exp (赞：1)

### 题意：
有一个长度为 n，由 * 和 . 组成的字符串。

你可以把字符串里 * 改变为 x，必须满足每两个 x 之间的距离小于等于 k。

不过，你必须把它的首尾两个 * 改变为 x。

x 的数量大于等于 1，且一定有解。

请输出在满足题意的前提下，最少的改变次数。
### 思路：
我们可以定义两个变量来存储当前点到上一个 x 的距离和离当前点最近的合法的 * 。

在与上一个 x 的距离大于 k 后，我们的试探结束了。

于是，返回到最近的 * 并把它变为 x ，刷新与上一个 x 的距离。

以此类推，就可以满足改变次数最小。

简而言之，就是找到里上一个 x 距离最远的 * 并把它变为 x。

这么做，可以使任意两个相邻 x 的距离和最短，此贪心毫无疑问是正确的。
### 实现：
我们可以找到首尾两个 * 并把它们改变为 x，每次改变答案加一。

结束之后，判断答案是否小于 2。如果小于 2，那么证明 * 的数量一定是 1，直接输出即可。

如果没有，按照上述贪心思路从头到尾寻找结果，然后计算并输出即可。
### 代码：
```c
#include<iostream>
using namespace std;
int t;//数据数 
int n,k;//长度与最长差 
char mus[600];//一个用来存放'.','*','x'的数组 
int cha;//第i个点到上一个x的差 
int las;//上一个* 
int ans;//答案 
int s,e;//第一个*与最后一个* 
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cin>>k;
		for(int i=1;i<=n;i++){
			cin>>mus[i]; 
		}
		ans=0;
		for(int i=1;i<=n;i++){//找出第一个* 并把它变为x 
			if(mus[i]=='*'){
				mus[i]='x';
				ans++;
				s=i;
				break;
			}
		}
		for(int i=n;i>=1;i--){//找出最后一个*  并把它变为x 
			if(mus[i]=='*'){
				mus[i]='x';
				ans++;
				e=i;
				break;
			}
		} 
		if(ans<2){//如果只有一个*那么直接输出不多废话 
			cout<<ans<<endl;
			continue;
		}
		cha=0;
		las=0;
		for(int i=s;i<=e;i++){ 
			if(cha>k){//如果与上一个x的差大于k就回到最近的*并把它变为x，重置与上一个x的差 
				mus[las]='x';
				cha=i-las;
				ans++;
			}
			if(mus[i]=='*'){//如果当前点是*且与上一个x的距离小于等于k那么就把它作为要变为x的点 
				las=i;	
			}
			cha++;//增加与上一个x的差 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：fls233666 (赞：1)

因为要求最小的改变次数，所以考虑一个简单的**贪心**策略：**找与已确定的 $\texttt{x}$ 尽可能远的 $\texttt{*}$ 进行修改。** 这个贪心策略的正确性是显然的。

考虑如何实现上述贪心策略。可以先将开头第一个 $\texttt{*}$ 特判找到后直接改为 $\texttt{x}$ 。之后对于每个找到的 $\texttt{*}$ ,暴力查找到前面距离最近的 $\texttt{x}$，计算距离并记录 $\texttt{*}$ 的位置。当当前的 $\texttt{*}$ 与最近的 $\texttt{x}$ 距离超过 $k$ 时，就可以将上一个 $\texttt{*}$ 修改为 $\texttt{x}$。最后再次特判结尾的 $\texttt{*}$ 即可。

时间复杂度为 $O(tnk)$ 。根据体面中有 $1 \le t \le 500$ , $1 \le n,k \le 50$，可以通过此题。

附上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#define ll long long
#define rgt register int
using namespace std;
int main(){
  
	int test,n,nk,ans,lst;
	string str;
	cin>>test;  //读入测试数据组数
  
	while(test--){
		ans=0;
		cin>>n>>nk>>str;
  
		for(rgt j,i=0;i<n;i++){
			if(str[i]=='*'){  //找到*
                                
				for(j=i-1;j>=0;j--)  //找*前面最近的x
					if(str[j]=='x')
						break;
  
				if(j<0){  //前面没有x，则是第一个*，直接修改
					str[i]='x';
					lst=i;
					ans++;
				}else{
					if(i-j>nk){  //距离超过k,修改上一个*
						str[lst]='x';	
						ans++;
					}
					lst=i;  //记录*的位置
				}
			}
		}
		if(str[lst]=='*')
			ans++;   //特判结尾
		cout<<ans<<endl;	//输出答案
	}
	return 0;
}
```


---

## 作者：wangyibo201026 (赞：0)

## 一道模拟水题

这道题只要模拟有一点基础的人都能做得出。

首先，题目说明保证有解，则字符串里只有一个 ```*``` 时，答案就为 $1$，或者说，当第一个 ```*``` 的位置和最后一个 ```*``` 的位置相同的时候，答案就为 $1$。那么字符串里只有两个 ```*``` 的时候，答案必为 $2$，或者说，第一个 ```*``` 的位置到第二个 ```*``` 的位置小于等于 $k$ 时，答案为 $2$。

上面这段应该都知道，接下来讲难的了。

按照贪心思想，应该改离上一个 ```*``` 最远的但是距离在 $k$ 以内一个 ```*```。这样，才能使改的 ```*``` 最少，因为每一个 ```*``` 都有可能影响后面的 ```*```，只有在距离范围的边缘，才能使下一个 ```*``` 尽量远，改的次数越小。

基础知识讲完了，代码该怎么写呢？

关于代码，只要求出第一个 ```*``` 和最后一个 ```*``` 的位置，再设立无限循环，只要当前 ```*``` 的位置加 $k$ 大于**等于**终点的位置就可以跳出循环，而在循环中只要找距离上一个 ```*``` 最远的 ```*``` 但是距离又不超过 $k$ 的就可以了。

## 代码

文字是讲不清代码的，还是要结合代码理解：

```cpp
#include<bits/stdc++.h>

using namespace std;

int t;

int main(){
	cin >> t;
	while(t--){
		int sum = 2, sx, fx, n, k;
		cin >> n >> k;
		string s;
		cin >> s;
		for(int i = 0; i < s.size(); i++){   //找第一个*的位置
			if(s[i] == '*'){
				sx = i;
				break;
			}
		}
		for(int i = s.size() - 1; i >= 0; i--){  //找最后一个*的位置
			if(s[i] == '*'){
				fx = i;
				break;
			}
		}
		if(sx == fx){   //如果只有一个*
			cout << 1 << endl;
			continue;
		}
		if(fx - sx <= k){  //如果有两个
			cout << sum << endl;
			continue;
		}
		while(true){
			int x = sx + k;
			if(x >= fx){  //当当前*的位置距离最后一个*的距离小于等于k
				break;
			}
			for(int i = x; i >= sx; i--){  //寻找离上一个*最远但是距离在k以内的*
				if(s[i] == '*'){
					sx = i;
					break;
				}
			}
			sum++;  //修改次数+1
		}
		cout << sum << endl;  //一定要有换行
	}
	return 0;
}
```


---

