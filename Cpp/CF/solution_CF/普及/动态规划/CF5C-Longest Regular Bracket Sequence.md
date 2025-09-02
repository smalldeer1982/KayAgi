# Longest Regular Bracket Sequence

## 题目描述

This is yet another problem dealing with regular bracket sequences.

We should remind you that a bracket sequence is called regular, if by inserting «+» and «1» into it we can get a correct mathematical expression. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

You are given a string of «(» and «)» characters. You are to find its longest substring that is a regular bracket sequence. You are to find the number of such substrings as well.

## 样例 #1

### 输入

```
)((())))(()())
```

### 输出

```
6 2
```

## 样例 #2

### 输入

```
))(
```

### 输出

```
0 1
```

# 题解

## 作者：LuckyCloud (赞：44)

~~我也不知道用的什么算法，思维题？乱搞？~~首先就是和常规的括号匹配那样用栈存起来——遇到“（”放入栈里，遇到“）”栈顶高度减一，相当于成功找到一组括号匹配。变化的地方就在我们先建立一个a数组初始全部是Flase代表所有括号是独立的没有匹配，然后每次当遇到“）”时，**把与当前“）”匹配的“（”和当前“）”对应的a数组中的元素分别赋值为True。这样做完之后，序列中匹配过的括号就是True，没有匹配的括号就是Flase。**

------------
 _还不懂？看例子_ 
 

------------
**( ) ( ) ) ) ( ) )( ) ( ) (( )**

**1111001101111011**

------------
我们用1表示True，0表示False，然后就是这个样子


------------
然后我们就可以直接求最长连续1就好了呀，**也就是相当于求最长连续的已完成匹配的括号**


------------
1的长度自然是最长的合法括号长度，第一遍做按上面所描述的做法求出长度，然后再做一遍求出有多少个一样长的。————LuckyCloud.


------------

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int sum,tot,l,r,len,w,ans,stack[1001003],top;
bool a[1001003];
char s[1000103];
int main()
{
  scanf("%s",s);
  len=strlen(s);
  for (int i=0;i<len;i++)
  {
   if (s[i]=='(') stack[++top]=i;
   else {if (top){a[stack[top]]=true;a[i]=true;top--;}}
  }
  for (int i=0;i<=len;i++)
   if (a[i]) w++;
   else {ans=max(w,ans);w=0;}
 for (int i=0;i<=len;i++)
   if (a[i]) w++;
   else {if (w==ans)tot++;w=0;}
 if (ans)
  printf("%d %d\n",ans,tot);
 else puts("0 1\n");
  return 0;
}
```

------------



---

## 作者：linyinuo2008 (赞：9)

大家好,这是本人在洛谷的第二篇题解,望大家支持.


之所以想写篇题解总结一下这道题,因为这题我好几次都没过,而且有很多点要注意.

好,闲话不多说,现在开始.


------------
# Step 1:题目分析

我认为这题用了线性动规的思想，确实不错（有点类似于田忌赛马）。这也能算一道经典题了吧。个人建议提升为绿题。

有以下几点要注意。

- 合法序列：所有左括号都和右括号匹配。

- 不仅仅要求最长合法子序列，而且还要求个数。

- 字符串长度最大为10的6次方，所以不能用getline,得用cin或scanf。


------------
# Step 2:算法分析
先来看个例子。

( ( ) ( ) ) )

设一个stack数组模拟栈（记录当前已经进栈字符的位置）。

我们把已经匹配到的两个括号在a数组中记录为1，其余记录为0。

具体操作是这样的：按1到n扫描一遍，碰到"("直接进栈到")"判断上一个进栈的是否是"("，如果是的话就直接把两个都设为1，否则继续。



综上可知，我们需要一个变量p来记录扫到哪里，这样由于进栈的都是"("，我们在判断时只需看p是不是0（也就是是否有可以匹配的"(" ).

然后例子中对应的a数组就变成了这样：

1111110



------------
然后就变成求a数组最长连续1子序列长度+个数就可以了。相信奆佬们都会吧。


------------
# Step 3：代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e6+1;//节省空间

char c[maxn];
int len,st[maxn];//数组模拟栈
bool a[maxn];//由于只用0和1，所以采用bool，操作方便，且节省空间
int maximum(int a,int b)//自己写max更快
{
	return a>b?a:b;
}
int main()
{
	int i,j,p=0,ans=0,sum=0,num=0;
	scanf("%s",c);
	len=strlen(c);
	for(i=0;i<len;i++)
	{
		if(c[i]=='(')
		{
			p++;
			st[p]=i;
		}
		else
		{
			if(p!=0)//栈是否为空，即是否有能匹配的
			{
				a[st[p]]=1;
				a[i]=1;
				p--;
			}
		}
	}
	for(i=0;i<=len;i++)
	{
		if(a[i])
		{
			sum++;
		}
		else
		{
			ans=maximum(ans,sum);
			sum=0;
		}
	}
	for(i=0;i<=len;i++)
	{
		if(a[i])
		{
			sum++;
		}
		else
		{
			if(sum==ans)
			{
				num++;
			}
			sum=0;
		}
	}
	if(ans==0)
	{
		cout<<"0 1";
	}
	else
	{
		cout<<ans<<' '<<num;
	}
	return 0;
}


```
# 题解求通过。谢谢。

---

## 作者：Loner_Knowledge (赞：4)

这是一道动态规划题

---

首先`)`肯定匹配最近的没有匹配的`(`，不然一定出现没有匹配的或者交替匹配的。


可以把`(`入栈，遇到`)`出栈，而两个`()`之间的括号序列一定是匹配的。


于是可以把`(`的**位置**入栈，出栈时计算即可知道当前括号序列的长度。


但题意里表明了除了`(...)`，`(...)(...)`也是合法的括号序列。


于是设ans数组管理**到目前位置的合法括号序列长度**，每次出栈时更新相应位置的值，使用了动态规划的思想。


最后输出的答案1即是ans数组里的最大值，答案2即是答案1在ans数组里出现的次数。


答案1的计算可以在遍历字符串时计算，也可以在遍历字符串之后计算。


```cpp
#include<cstdio>
#include<cstring>
int sta[1000001],head,ans[1000001];
    //sta数组是栈，存储'('的位置。
    //ans[i]代表遍历到s[i]时的合法括号序列长度
char s[1000001];
int main() {
    int ans1=0,ans2=1;    //最大子串长度，最大子串个数(初值应为1)
    scanf("%s",s);
    for(int i=0;s[i];++i) {
        if(s[i]==')') {    //准备出栈
            if(!head)        //栈为空，无栈可出
                continue;
            head--;            //出栈
            ans[i]=i-sta[head]+1+ans[sta[head]-1];    //更新值
            if(ans1==ans[i])
                ans2++;
            //如果答案1等于ans[i]，更新答案2
            else if(ans1<ans[i]) {
                ans1=ans[i];
                ans2=1;
            }
            //如果答案1小于ans[i]，更新答案1，重置答案2为1(初值)
        }
        else
            sta[head++]=i;    //入栈
    }
    printf("%d %d",ans1,ans2);
    return 0;
}
```

---

---

## 作者：simonG (赞：3)

### 前言
这是一道动态规划&栈的题
栈：
```
#include<stack>
stack<int>st;
```

### 详解
>* 1，括号的匹配：先把括号入栈，如果在栈口，碰到$\texttt{（}$ 与 $\texttt{）}$，则两个一起出栈，答案+1。

>* 2，动态规划，则表示以当前符号结尾的符号的最长符合要求的数量，即相似于最长上升子序列。
核心代码：

```cpp
dp[i]=i-st.top()+1+dp[st.top()-1];
++cnt[dp[i]],st.pop();
```

### 代码
```cpp
#include<bits/stdc++.h>
//#include<stack>栈
#define re register
using namespace std;
const int N=1000011;
stack<int>st;//栈的定义
char s[N];
int n,dp[N],cnt[N];//动态规划
int main() {
	scanf("%s",s+1);//输入
	n=strlen(s+1);
	for (re int i=1; i<=n; ++i)
		if (s[i]=='(') 
			st.push(i);//入栈
		else if (st.size()) {
			dp[i]=i-st.top()+1+dp[st.top()-1],//具体动规过程
			      ++cnt[dp[i]],st.pop();
		}
	cnt[0]=1;
	for (re int i=n; ~i; --i)
		if (cnt[i]){
			printf("%d %d",i,cnt[i]);//输出
			return 0;
		}	
	return 0;
}
```

### 后记
动态规划多用。

---

## 作者：Huaji_King (赞：2)

其实这题我们只需要把正确匹配的括号都标记为1，那我们只需要找连续一段1就完事了

但问题是怎么才能把正确匹配的括号标记呢？
## 重点
我们可以找一个数组来存放“（”，每次找到一个“）”就和上一个“（”一起标记为正确匹配的括号，也就是1，那这下不就解决了吗

### 话不多说，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,w,ans,ss[1001010],t,i;
int a[1001010];
char s[1001010];
int main()
{
	scanf("%s",s);
  	l=strlen(s);
	for(i=0;i<l;i++)
  	{
		if(s[i]=='(') ss[++t]=i;
   		else
		{
			if(t!=0)
			{
				a[ss[t]]=1;
				a[i]=1;
				t--;
			}
		}
  	}
  	t=0;
  	for(i=0;i<=l;i++) 
	{
	  	if(a[i]==1) w++;
   		else ans=max(w,ans),w=0;
	}
	for(i=0;i<=l;i++) if(a[i]==1) w++;
   	else
	{
		if(w==ans) t++;
		w=0;
	}
 	if(ans!=0) printf("%d %d",ans,t);
 	else cout<<"0 1";
  	return 0;
}
```
题解求通过，谢谢。

---

## 作者：joyoi (赞：2)

### $Description$

给定一个括号序列，求合法的最长序列的长度以及这么长的合法序列的个数

下面是关于合法序列的定义和性质：

1. 一个空串是一个合法序列
2. 若 $S$ 是一个合法序列，则 $(S)$ 也是一个合法序列
3. 若 $A，B$ 都是合法序列，则 $AB$ 也是一个合法序列

数据范围：字符串长度 $n$ $≤$ $10^6$

### $Solution$

首先我们可以用栈找出所有配对的扩展，这样我们就找出了所有满足第二条的串，那如何处理第三条呢？

第三条本质就是可以把两个合法的串连接起来，设$f [ i ]$表示以 $i$ 结尾的合法串的长度，则 $f$ $[ i ]$ $=$ $i$ $−$ $j$ $+$ $1$ $+$ $f$ $[ j − 1 ]$， $j$ 是与 $i$ 匹配的位置，而之前说的栈正好能找出所有的 $i$ 对应的 $j$ ，于是这道题就愉快的淦掉了

### 时间复杂度：$O ( n )$

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

stack<int> st;
char s[5000001];
int n, f[5000001], t[5000001] = {1};
int main()
{
        cin >> s + 1;
	n = strlen(s + 1);
	for(register int i = 1; i <= n; i++){
	   if(s[i] == '(') st.push(i);
	   else if(st.size()) ++t[f[i] = i - st.top() + 1 + f[st.top() - 1]], st.pop();//用桶统计个数
    }
	for(int i = n; i >= 0; i--){
        if(t[i]) return printf("%d %d\n", i, t[i]) & 0;//骚气~
    }
}
```






---

## 作者：tonyre (赞：1)

# CF5C 题解

## 1 题面

给出一个仅由左括号和右括号的序列，求最长合法子串的长度以及数量（不是求出所有合法子串数）。合法要求括号左右匹配。

如果没有合法子串，输出 `0 1`。

## 2 题解

### 2.1 思路

前置知识：[括号匹配](https://www.luogu.com.cn/problem/P1739)、[栈](https://oi-wiki.org/ds/stack/)。

括号匹配就是栈的思想。左括号按照先后顺序入栈；右括号总是和栈顶的左括号匹配，即最前面的没有被匹配的左括号。

什么样子叫不合法呢？右括号没有左括号可匹配了，即栈为空。

这样的话，我们可以先手动模拟一遍栈，匹配所有括号。匹配到标记为 `true`，没匹配到就是 `false`。

那么最长合法字串的长度（要求连续）就是**求最长连续 `true` 的个数**；而数量就再循环一遍找到就好了（由于求的是最长长度的字串的数量，所以保证**最长长度的子串只要全是 `ture`，就一定是合法的**）。

### 2.2 实现

三次循环。第一次括号匹配，第二次求最长长度，第三次求数量。

时间复杂度 $O(|a|)$。由于字符串长度小于 $10^6$，所以可以过。

## 3 代码

```c++
#include<iostream>
using namespace std;
const int MAXN=1000005;
int s[MAXN];
bool vis[MAXN];
int main()
{
    string a;
    cin>>a;
    
    //1
    int top=0;
    for(int i=0;i<a.size();i++)
        if(a[i]=='(') s[++top]=i;
        else if(top>0)
        {
            vis[s[top]]=vis[i]=true;//a[s[top]] 与 a[i] 匹配
            top--;
        }

    //2
    int cur=0,maxn=0;
    for(int i=0;i<a.size();i++)
        if(vis[i]) maxn=max(maxn,++cur);
        else cur=0;
    
    if(maxn==0)//特判
    {
        cout<<"0 1"<<endl;
        return 0;
    }
    
    //3
    int cnt=0;
    cur=0;
    for(int i=0;i<a.size();i++)
        if(vis[i]) cur++;
        else
        {
            if(cur==maxn) cnt++;
            cur=0;
        }
    if(cur==maxn) cnt++;//注意
    
    cout<<maxn<<' '<<cnt<<endl;
    return 0;
}
```



---

## 作者：Symbolize (赞：1)

# 思路
思路分为两部分
## 整体思路
将匹配成功的括号标记为 $1$，无法匹配的标记为 $0$，然后求标记数组 $a$ 的最长连续为 $1$ 的子序列。那么这个值就是最大值了。
## 第一部分
利用栈找到可以匹配的括号。

具体方法：

遇到左括号，将其下标入栈，如果遇到右括号，那么在栈非空时弹出栈顶元素，并将其下标与目前这个右括号的下标都标记为 $1$。
## 第二部分
1. 遍历 $a$ 标记数组，找到其最长连续为 $1$ 的子序列。

2. 再次遍历找个数
------------
最后输出即可，但要记得特判。
# Code
最后附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>//万能头 
#define int long long
const int N=1e6+10;
using namespace std;
int stk[N],t1,t2,ans;
bool a[N];
char s[N];
signed main()
{
  	cin>>s;
	//第一部分 
  	int len=strlen(s);
  	for(int i=0;i<len;i++)//处理字符串 
  	{
   		if(s[i]=='(') stk[++t2]=i;//入栈 
   		else//出栈 
		{
			if(t2)//判断是否为空 
			{
				a[stk[t2]]=1;//标记
				a[i]=1;
				--t2;
			}	
		}
	}
	//第二部分 
	int res=0;
  	for(int i=0;i<=len;i++)//找最大值 
  	{
  		if(a[i]) ++res;
   		else 
		{
			ans=max(res,ans);
			res=0;
		}
	}
 	for(int i=0;i<=len;i++)//找个数 
 	{
 		if(a[i]) ++res;
   		else 
		{
			if(res==ans) ++t1;
			res=0;
		}
	}	
 	if(ans) cout<<ans<<' '<<t1<<endl;
 	else puts("0 1");//特判 
  	return 0;//结束 
}
```

---

## 作者：刘健铭 (赞：1)

# Longest Regular Bracket Sequence

字符串 $dp$ 题一道。

我们可以用 $dp[i]$ 表示以i结尾的最长合法序列长度。

那么对于每一个元素，只需考虑它的上一个元素的长度即可。

就有dp方程：$dp[i]=dp[i-1]+2+dp[i-2-dp[i-1]]$。

以下是代码：

```c++
#include<bits/stdc++.h>
using namespace std;
char st[1000007];
int ans,flag;
int dp[1000007],cnt;
int main()
{
    scanf("%s",st+1);
	int len=strlen(st+1);
    for(int i=1;i<=len;i++)
    {
        if(st[i]=='(' || st[i]=='[')continue;
        if(st[i]==')' || st[i]==']')
        {
            if(st[i]==')' && st[i-1-dp[i-1]]=='(')
            {
                dp[i]=dp[i-1]+2+dp[i-2-dp[i-1]];
                ans=max(ans,dp[i]);
            }
        }
    }
    for(int i=1;i<=len;i++)
    {
		if(dp[i]==ans)
		{
			flag++;
		    for(int j=i-ans+1;j<=i;j++)
			{
				if(st[j]=='('||st[j]==')')cnt++;
			}
		}
	}
	cnt=cnt/flag;
	if(cnt>0)
	cout<<cnt<<" "<<flag;
	else cout<<"0 1";
    return 0;
}
```


---

## 作者：Fengxiang008 (赞：1)

## 思路：

求一个括号序列的最长合法序列和它的数量。

设 $f[i]$ 表示以 $i$ 结尾的最长的合法序列。

当当前字符为左括号 " ```(``` " 时，
将它入栈，
否则为右括号，并且栈不为空， $f[i]$ 就是上一个入栈的左括号到当前位置的长度。

## 代码：
```cpp
#include <bits/stdc++.h>
#define A 1000010
#define B 2010
using namespace std;
typedef long long ll;
int f[A], cnt[A], ans, sta[A], top;
char s[A];
int main(int argc, char const *argv[]) 
{
    cin >> (s + 1); 
    int n = strlen(s + 1);
    cnt[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') sta[++top] = i;
        else if (top) {
            f[i] = i - sta[top] + 1 + f[sta[top] - 1];
            top--;
            cnt[f[i]]++;
        }
    }
    for (int i = n; i >= 0; i--)
        if (cnt[i]) {
            cout << i << " " << cnt[i] << endl;
            break;
        }
    return 0;
}

```

当然 "```( ) ( )```" 的答案是 $4$ 。

如果只是上面那种操作的话答案只是 $2$ 。

所以还要加上上一个匹配成功的 ```f```

就是上一个左括号的左边。

也就是匹配成功的右括号的的 ```f``` 。


---

## 作者：瀛洲仙子 (赞：0)

### 大体思路分析
线性表，就差不多是《括号匹配升级版》。
### 具体思路分析
栈。首先输入一个字符串。
```python
s=input().split(' ')
s=s[0]
```
然后进行筛选。首先初始化两个列表，一个用来模拟栈，另一个用来记录每一次出栈的结果。如果这个字符是 `(`，入栈。否则，如果栈不为空，记录匹配成功，出栈。
```python
st,a,top=[0],[False]*1000003,0
for i in range(len(s)):
		if s[i]=='(':
        st.append(i)
        top+=1
     elif bool(top):
     		a[st[top]]=a[i]=True
            a.pop(len(a)-1)
            top-=1
```
然后我们计数器一次，判断 $[0,n]$ 范围内有多少个连续的成功匹配，并求最大。
```python
ans=w=0
for i in range(len(s)+1):
		if a[i]:
        w+=1
     else:
        ans=max([ans,w])
        w=0
```
第二次统计，找最多次数。
```python
tot=0
for i in range(len(s)+1):
		if a[i]:
        w+=1
     elif w==ans:
     		tot+=1
            w=0
```
最后输出。如果没有
```python
if bool(ans):
		print(ans,tot)
else:
		print("0 1")
```
### 具体代码
根据以上思路，无注释代码如下。
```python
s=input().split(' ')
s=s[0]
st,a,top=[0],[False]*1000003,0
for i in range(len(s)):
		if s[i]=='(':
        st.append(i)
        top+=1
     elif bool(top):
     		a[st[top]]=a[i]=True
            a.pop(len(a)-1)
            top-=1
ans=w=0
for i in range(len(s)+1):
		if a[i]:
        w+=1
     else:
        ans=max([ans,w])
        w=0
tot=0
for i in range(len(s)+1):
		if a[i]:
        w+=1
     elif w==ans:
     		tot+=1
            w=0
if bool(ans):
		print(ans,tot)
else:
		print("0 1")
```
**珍爱生命，远离抄袭！**

---

