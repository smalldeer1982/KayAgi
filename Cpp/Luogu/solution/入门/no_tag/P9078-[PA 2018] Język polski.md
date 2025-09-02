# [PA 2018] Język polski

## 题目描述

**题目译自 [PA 2018](https://sio2.mimuw.edu.pl/c/pa-2018-1/dashboard/) Runda 1 [Język polski](https://sio2.mimuw.edu.pl/c/pa-2018-1/p/pol/)** 。

给定一个字符串 $s$ ，求出该字符串中满足以下条件的子串的数量。

- 该字符串中至少有一个长度为 $3$ 的子串仅由辅音字母或仅由元音字母构成。

注意，**波兰语的元音字母与英语不同**。波兰语中元音字母有 $a,e,i,o,u,y$。

不是元音字母的字母即为辅音字母。

## 说明/提示

#### 样例 1 解释

所有满足条件的子串列举如下：$\texttt{stk},\texttt{ostk},\texttt{kostk},\texttt{stka},\texttt{ostka},\texttt{kostka}$。

------------

#### 数据范围

**本题采用捆绑测试**

设字符串长度为 $\mathrm{len}$ ，则 $\mathrm{len} \le 200000$。

## 样例 #1

### 输入

```
kostka```

### 输出

```
6```

## 样例 #2

### 输入

```
aaaa```

### 输出

```
3```

# 题解

## 作者：2081a (赞：7)

# P9078 Język polski 题解
看大佬们都提交的 string 字符串，我来交一发 char 代码。
### 思路
从头开始遍历一遍字符串，分别给元音和辅音开一个累加器，满足是元音就清空辅音，元音加一；反之清空元音，辅音加一，如果其中有一个满足了题目的条件，就让 $sum$ 的值变成当前 $i-2$（举例：`aei`只能算一个满足条件的，在 $i=3$ 时 $y=3$，因此 $sum$ 的值改为 $i-2=1$），再设 $ans$ 变量每轮累加 $sum$ 最终得到答案。
## AC代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200010;//范围开始开小了调了好久都是70分
ll f,y,sum;
ll ans;
int read(){
	int op=1,x=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') op=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return op*x;
}//快读，本题用不到
bool check(char c){
	return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='y');
}//判断当前字母是否是元音，是返回true，否则返回false
char s[N];
int main(){
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++){
		if(check(s[i])){//判断如果是元音就让元音累加器加1，辅音累加器清空
			y++;
			f=0;
		}
		else{//如果是辅音与上面相反
			f++;
			y=0;
		}
		if(f>=3||y>=3)//如果其中有一个满足题意达到三就让sum改为i-2
			sum=i-2;
		ans+=sum; 
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：WydnksqhbD (赞：2)

# [P9078 [PA2018] Język polski](https://www.luogu.com.cn/problem/P9078) 题解
## 思路
很容易想到的就是暴力的做法。但是这道题 $O(n^2)$ 暴力明显卡不过去，因为数据范围为 $n\le 2\times 10^5$。

那么我们该怎么办呢？

大家想一想，题目要求是**至少长度为 $3$**，那么我们可以从头到尾枚举一遍。

设枚举到第 $i$ 个字符，
+ 若 $s_i$ 为元音，则用来记录元音个数的 $\text{sum}_1$ 增加 $1$，记录辅音个数的 $\text{sum}_2$ 变为 $0$。
+ 否则 $s_i$ 为辅音，$\text{sum}_1$ 赋值为 $0$，$\text{sum}_2$ 增加 $1$。

然后再判断是否 $sum_1\ge 3$ 或者 $sum_2\ge 3$，
+ 如果为真，则 $\text{ans}$ 加上 $i-2$（因为要求长度为 $3$）。

继续枚举 $i+1$ 即可。

这样时间复杂度为 $O(n)$，可以通过本题。

代码有注释。
```cpp
#include<bits/stdc++.h>
#define int long long //宏定义，将 "int" 替换成 "long long"。
using namespace std;
int ans,sum1,sum2,p; //全局变量自动赋值为 0。
signed main() //这里不能写 int。
{
	string s;
	cin>>s;
	s=" "+s; //不加这句话就要记得从 0 开始。
	int len=s.size(); //获取长度。
	for(int i=1;i<len;i++) //枚举
	{
		if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'||s[i]=='y') //不要忘记'y'。
		{
        sum1++;
			sum2=0;
		}
		else
		{
			sum2++;
			sum1=0;
		}
		if(sum1>=3||sum2>=3) //判断是否≥3。
		{
			p=i-2;
		}
		ans+=p;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_little_Cabbage_ (赞：1)

# P9078 [PA2018] Język polski 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p9078)~~

这是一道思维题。

我们可以发现，如果有一个长度为 $3$ 的子串，满足全都是元音或全都是辅音，那么就将 $ret$ 设为这个字串的第一个字母的下标，然后每一次将答案 $ans$ 加上 $ret$ 就行了。

但是要记住，**一定要开 long long！！！！**

AC 代码
```cpp
#include<bits/stdc++.h>
#define yuanyin s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'||s[i]=='y'
#define houzhui count1>=3||count2>=3
using namespace std;
signed main()
{
	string s;
	cin>>s;
	s=" "+s;
	int len=s.size();
	long long count1=0,count2=0,ans=0,ret=0;
	for(int i=1;i<len;i++)
	{
		if(yuanyin)
		{
			count1++;
			count2=0;
		}
		else
		{
			count2++;
			count1=0;
		}
		if(houzhui)
		{
			ret=i-2;
		}
		ans+=ret;
	}
	cout<<ans;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/143175566)

---

## 作者：Mx_sky (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9078)

## 警示
我为了抢最优解，中间还 $\verb!RE!$ 了一次，大家千万别学我。

## 思路
回归正题，本题我认为思维难度是中等（太蒟蒻了），刚开始想不到思路，唯一能想到的是用 $\verb!cnt1!$ 和 $\verb!cnt2!$ 分别记录元音字母和辅音字母的个数，但是还是想不出来怎么办？那就来模拟一遍样例吧！
```
kostka
```
第一个字母 $k$ 不是元音字母，$\verb!cnt1++!$，元音字母断了，$\verb!cnt1!$ 重置为 $0$，第二个字母 $o$ 是元音字母，$\verb!cnt1++!$，辅音字母断了，$\verb!cnt2!$ 重置为 $0$。接下来三个字母 $stk$ 都是辅音字母，$\verb!cnt2+=3!$，这时已经有三个了，再加上前面的两个字母，就有 $1+2=3$ 种方案，然后后面还有个字母 $a$，所以还有 $2+1=3$ 种方案，$3+3=6$ 种方案就是答案了。 

发现了什么没？给大家看一下我的发现：

设 $i$ 和 $j$ 为长度为 $3$ 的合格的子串的左右端点，那是不是要加上 $i$ 种字符串，那 $i=j-2$，我们要么枚举 $i$，要么枚举 $j$（因为数据范围不允许双重循环），显然的，枚举 $i$ 完全找不到累加条件，那只能枚举 $j$了。

有了这个结论，代码就很容易打了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string s;
int cnt1,cnt2,len;
ll ans;
inline bool pd(char x) //是元音字母还是辅音字母 
{
	if(x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='y') return 1;
	else return 0;
	//大佬可以改成 return (x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='y');
}
int main() {
    cin>>s;s='0'+s;
    int l=s.size(); //长度 
    //register是寄存器，可以加速 
    for(register int i=1;i<l;++i) //++i比i++快 
    {
	    //按照条件累加 
    	if(pd(s[i])) ++cnt1,cnt2=0;
    	else ++cnt2,cnt1=0;
    	//满足条件左端点 
    	if(cnt1>=3||cnt2>=3) len=i-2;
    	ans+=len;
    }
    printf("%lld\n",ans);
    return 0;
} 
```
[提交记录](https://www.luogu.com.cn/record/111210104)（目前是最优解）

---

## 作者：WaterSky (赞：1)

## 题目大意：
求在一个字符串中有多少个子串中只有元音或辅音的子串。

## 正题：
我的做法与一楼的做法差不多，但是我认为他的解释有一点难懂，我来详细的解释一下。

### 我的程序（无注释）：
```
#include<bits/stdc++.h>
using namespace std;
string a;
long long ans,x,y,z;
int main(){
	cin>>a;
	for(int i=1;i<=a.size();i++)
	{
		if(a[i-1]=='a'||a[i-1]=='e'||a[i-1]=='i'||a[i-1]=='o'||a[i-1]=='u'||a[i-1]=='y') x++,y=0;
		else y++,x=0;
		if(x>=3 || y>=3) z=i-2;
		ans+=z;
	}
	cout<<ans;
	return 0;
}
```
### 总结做法：
寻找当前最后一个长度为 3 的合格子串。

当你找到了这一个合格子串后，你就需要计算包含这一个合格子串的合格字符串的数量，累加到最后的答案里。

而计算的方法就是将这一个合格子串看作一个字符，然后再找与它连续组成的字符串，可以通过举例子得知，与它组成的字符串的数量等于这一个合格子串前面字符的数量。最后再把答案累加即可。

### 我的程序（有注释）：
```
#include<bits/stdc++.h>//万能头文件。
using namespace std;
string a;//定义字符串。
long long ans,x,y,z;//定义数据。x 等于元音组成的子串的长度，y等于辅音组成的子串的长度。
int main(){
	cin>>a;//输入。
	for(int i=1;i<=a.size();i++) //为了让后面的步骤更加清晰，可以从 1 开始。
	{
		if(a[i-1]=='a'||a[i-1]=='e'||a[i-1]=='i'||a[i-1]=='o'||a[i-1]=='u'||a[i-1]=='y') x++,y=0; //这一步寻找由元音字符组成的合格子串。
		else y++,x=0; //而这一步寻找由辅音字符组成的合格子串。
		if(x>=3 || y>=3) z=i-2;//如果长度达到标准那么当前最后一个的开头也随之改变。
		ans+=z;//答案累加。
   }
	cout<<ans;//输出结果。
	return 0;//记得return 0。
}
```

### 总结：
这一道题的算法大概为前缀和与计算，难度不高，适合练手。

-------------------------------------------

致审核的管理员：如果有不规范的地方，麻烦一次性把问题指出来，谢谢。

致读者：如果有更好的方法可以评论一起进步。

---

## 作者：int_R (赞：1)

设当前位为 $i$，前面最后的仅由辅音字母或仅由元音字母长度为 $3$ 的子串的位置是 $[pre,pre+2]$，以 $i$ 结尾的符合要求的子串只需要包含上述子串就可以了，所以左端位置在 $[1,pre]$ 间，所以有 $pre$ 个，累加即可。

```cpp
#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
//cnt1是当前后缀连续有几个元音字母
//cnt2是当前后缀连续有几个辅音字母
//pre是上一个长度为 3 的子串开头位置
int cnt1,cnt2,pre;long long ans;
//判断是不是元音字母
inline bool B(char x){return (x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='y');}
int main()
{
	string s;cin>>s;s=" "+s;int len=s.size()-1;
	for(register int i=1;i<=len;++i)
	{
		if(B(s[i])) cnt1++,cnt2=0;
		else cnt2++,cnt1=0;
        //如果后缀有满足要求的了，那么 pre 就更新为 i-2
		if(cnt1>=3||cnt2>=3) pre=i-2;
		ans+=pre;
	}
	cout<<ans<<'\n';return 0;
}
```


---

## 作者：huangzhixia (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/P9078)**

## 题意

我们有一个字符串 $s$，然后简单地找一下由多少个长度为 $3$ 的由波兰语元音字母组成的子串。

波兰语的元音字母有这几个：$a$，$e$，$i$，$o$，$u$，$y$。

## 思路

其实如果暴力枚举根本没有必要，时间复杂度 $O(n^2)$。

因为不难想到，我们每次枚举每一个位置，对于每一个位置，从当前位置 $i$ 考虑到 $i+2$ 的位置，因为要考虑 $i$，这样我们每次用一个 bool 类型的变量 $ok$ 来记当前是不是一个由波兰语元音字母组成的子串，一但碰不到是原音字母的，将 $ok$ 变为 false，否则就往后考虑。

最后对于每一个位置 $i$，考虑完三个位置后，看看 $ok$ 是 true 还是 false，是 true 的话将我们记答案的变量 $ans$ 加 $1$。

而每次我们需要用一个 $pos$ 来记下标，如果当前的长度为 $3$ 子串都是元音字母或都不是，那么我们的 $pos$ 就要更新成子串第一个字母的下标，然后让 $ans$ 加上 $pos$。

最后输出 $ans$。

## 注意

不开 long long 见祖宗。

---

