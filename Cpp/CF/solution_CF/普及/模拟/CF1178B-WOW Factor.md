# WOW Factor

## 题目描述

Recall that string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly zero or all) characters. For example, for the string $ a $ ="wowwo", the following strings are subsequences: "wowwo", "wowo", "oo", "wow", "", and others, but the following are not subsequences: "owoo", "owwwo", "ooo".

The wow factor of a string is the number of its subsequences equal to the word "wow". Bob wants to write a string that has a large wow factor. However, the "w" key on his keyboard is broken, so he types two "v"s instead.

Little did he realise that he may have introduced more "w"s than he thought. Consider for instance the string "ww". Bob would type it as "vvvv", but this string actually contains three occurrences of "w":

- "vvvv"
- "vvvv"
- "vvvv"

For example, the wow factor of the word "vvvovvv" equals to four because there are four wows:

- "vvvovvv"
- "vvvovvv"
- "vvvovvv"
- "vvvovvv"

Note that the subsequence "vvvovvv" does not count towards the wow factor, as the "v"s have to be consecutive.

For a given string $ s $ , compute and output its wow factor. Note that it is not guaranteed that it is possible to get $ s $ from another string replacing "w" with "vv". For example, $ s $ can be equal to "vov".

## 说明/提示

The first example is explained in the legend.

## 样例 #1

### 输入

```
vvvovvv
```

### 输出

```
4
```

## 样例 #2

### 输入

```
vvovooovovvovoovoovvvvovovvvov
```

### 输出

```
100
```

# 题解

## 作者：jijidawang (赞：11)

[更好的阅读体验](https://www.cnblogs.com/CDOI-24374/p/17189455.html)

这是一道非常富有启发性的题目，值得一做，闪耀着人类和机器人的智慧光辉的绝佳题目 .

首先注意到 `(vv)o(vv)` 的结构，可以考虑枚举中间的 `o`，这样只需要算两边的选法然后用乘法原理即可 .

乘法原理：做一件事，完成它需要分成 $n$ 个步骤，做第一步有 $m_1$ 种不同的方法，做第二步有 $m_2$ 种不同的方法，……，做第 $n$ 步有 $m_n$ 种不同的方法。那么完成这件事共有 $N=m_1\times m_2\times m_3\times\cdots\times m_n$ 种不同的方法 .

根据乘法原理，其实就是选择这个字符串有三个步骤，先选左边有 $a$ 种，中间的 `o` 有 $1$ 种，右边有 $b$ 种，那么总方案数就是 $N=a\times 1\times b$ .

那么考虑怎么求 $a$ 和 $b$，分别考虑：

**Part 1** 求 $a$

厉害的一步到了，令 $f_i$ 表示 $[s_i=s_{i+1}=\texttt v]$（这里的 $[]$ 叫 Iverson Bracket，大佬教的，$[x]$ 就是 `bool(x)`）

那么如果 `o` 的位置是 $i$，那么 $a=f_1+f_2+\cdots+f_{i-1}$ 就是连续 `vv` 的个数了，不用考虑冲突，因为只需要选一个不选多个 .

如果每次都直接求和，需要约 $10^6\times 10^6$ 次加法，无法接受，怎么办呢？

发现是要对于每个位置求，于是假设第 $i$ 个位置的答案是 $A$，第 $i+1$ 个位置的答案是 $B$（不需要考虑是否为 `o`，后面说原因），那么
$$\begin{aligned}&A=f_1+f_2+\cdots+f_{i-1}\\&B=f_1+f_2+\cdots+f_{i-1}+f_i\end{aligned}$$
惊奇的发现：$B=A+f_i$！

这样先算出第一个位置的答案，然后用一个 for 循环就可以求出每个位置的 $a$ 值，使用时只计算有 `o` 的位置就行了 .

**Part 2** 求 $b$

也是类似的做法，如果 `o` 的位置是 $i$，那么 $b=f_i+f_{i+1}+\cdots +f_n$ 就是连续 `vv` 的个数 .

假设第 $i$ 个位置的答案是 $A$，第 $i+1$ 个位置的答案是 $B$，那么
$$\begin{aligned}&A=f_i+f_{i+1}+f_{i+2}+\cdots+f_n\\&B=f_{i+1}+f_{i+2}+\cdots+f_n\end{aligned}$$
这时候我们得到的是 $B=A-f_i$，也是先算出第一个位置的答案用一个 for 循环就可以求出每个位置的 $b$ 值了 .

还可以看 $A=B+f_i$，这样从后往前 for，初始的位置就不需要再用一个 for 循环了 .

总共的时间复杂度为 $O(n)$，可以 Accepted 了 . 记得开 `long long`！

接下来就是简洁的代码，细节很多，要好好考虑：
```cpp
const int N = 1919810;
string s;
int n, pre[N], suf[N];
int main()
{
	cin >> s; n = s.length(); s = "$" + s; 
	for (int i=1; i<n; i++) pre[i] = pre[i-1] + ((s[i] == 'v') && (s[i+1] == 'v'));
	for (int i=n-1; i>=1; i--) suf[i] = suf[i+1] + ((s[i] == 'v') && (s[i+1] == 'v'));
	ll ans = 0;
	for (int i=1; i<n; i++)
		if (s[i] == 'o') ans += 1ll * pre[i-1] * suf[i];
	printf("%lld\n", ans);
	return 0;
}
```

可以看出题面的表述相当自然易懂，而每一步的思维却都非常跳跃，思维量很大结果却很简洁，推导答案的形式不涉及很困难的算法，却又不仅限于结论，而是巧妙地结合了 OI 知识，启发选手独自研发题目所需要的算法，为良心出题人点赞！

---

## 作者：灵茶山艾府 (赞：5)

### 方法一：前后缀分解（两次遍历）

预处理每个 $\texttt{o}$ 左右的 $\texttt{vv}$ 个数，分别记作 $\textit{pre}$ 和 $\textit{suf}$。

然后枚举 $\texttt{o}$，根据乘法原理，把 $\textit{pre}\cdot \textit{suf}$ 加到答案中。

```go
package main
import("bufio";."fmt";"os")

func main() {
	var s string
	Fscan(bufio.NewReader(os.Stdin), &s)
	var pre, suf, ans int
	n := len(s)
	for i := 1; i < n-1; i++ {
		if s[i] == 'v' && s[i+1] == 'v' {
			suf++
		}
	}
	for i := 1; i < n-2; i++ {
		if s[i] == 'o' {
			ans += pre * suf
		} else {
			if s[i-1] == 'v' {
				pre++
			}
			if s[i+1] == 'v' {
				suf--
			}
		}
	}
	Print(ans)
}
```

### 方法二：状态机 DP（一次遍历）

定义：

- $f_{i,0}$ 表示考虑前 $i$ 个字母，能得到的 $\texttt{w}$ 子序列的个数。
- $f_{i,1}$ 表示考虑前 $i$ 个字母，能得到的 $\texttt{wo}$ 子序列的个数。
- $f_{i,2}$ 表示考虑前 $i$ 个字母，能得到的 $\texttt{wow}$ 子序列的个数。

分类讨论：

- 如果 $s_i=\texttt{o}$ 那么 $f_{i,1} = f_{i-1,1} + f_{i-1,0}$，分别表示不选和选 $s_i$。
- 如果 $s_i=\texttt{v}$ 且 $s_{i-1}=\texttt{v}$，那么 $f_{i,0} = f_{i-1,0} + 1$，$f_{i,2} = f_{i-1,2} + f_{i-1,1}$，理由同上。
- 其余情况 $f_{i,j}=f_{i-1,j}$。

答案为 $f_{n,2}$。

代码实现时，第一个维度可以去掉。

```go
package main
import("bufio";."fmt";"os")

func main() {
	var s string
	Fscan(bufio.NewReader(os.Stdin), &s)
	var f0, f1, f2 int
	for i := 1; i < len(s); i++ {
		if s[i] == 'o' {
			f1 += f0
		} else if s[i-1] == 'v' {
			f2 += f1
			f0++
		}
	}
	Print(f2)
}
```

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)


---

## 作者：stycycle (赞：3)

~~一个蒟蒻的题解，不用在意~~
### 做之前让我们先思考一下
* 首先我们必须明白 $o$ 之后每找到一组 $vv$ 就可以与 $o$ 之前的所有 $vv$ 匹配成一个要求的 $vvovv$   

* 所以我们只需要跑一遍字符串，每遇到一个 $vv$，就可以用$cnt_1$记录一下，那么为什么要 $ans$+=$cnt_2$呢？

* 因为我们知道,每出现一个 $o$，我们就应该在之后的查找中，每遇到一个 $vv$，就给$ans$加上之前的$vv$数，所以才用了$ans$+=$cnt_2$。

* 但是我们要明白，可能字符串中出现的不只是一个 $o$，所以我用了$cnt_1$和$cnt_2$两个变量，用$cnt_1$来记录所有$vv$的量，用$cnt_2$来记录应该累加的$vv$。

* 可能大就会有一个疑问，为什么$cnt_1$不用清零，这样每次给$cnt_2$赋值的时候岂不是会重复累加？
  
  其实不是，我们假设第一个$o$之前有$v_1$个$vv$,第二个$o$之前有$v_2$个$vv$……那么第$n$个$o$后面的$vv$就可以与第$n$个$o$匹配，有$v_n$种可能，又可以与第$n-1$个$o$匹配，有$v_{n-1}$种可能，以此类推一共有$v_1+v_2+……+v_n$种可能，所以才需要重复累加
***
  
### 代码：


```cpp
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
const int maxn=1e7;
long long cnt1,cnt2;
long long ans;
string s;
int main(void)
{
	cin>>s;//读入字符串
	for(int i = 1; s[i]; i++)
	{
		if(s[i] == 'v' && s[i-1] == 'v')
		{
			cnt1++;
			ans+=cnt2;
		}
		if(s[i] == 'o')
		{
			cnt2+=cnt1;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：K_Madoka (赞：3)

~~打比赛的时候我看到这道题，五分钟就切了这道题~~

## 这道题的做法就是前缀和和后缀和。

前缀和首先从头统计，如果某一个字符是$v$，并且上一个也是$v$，那么当前的$w$的个数加一。

接着再搞一个后缀和，做和前缀和相反的操作。

最后，从头扫描一遍，每找到一个$o$，就把左边前缀和$w$的个数乘上右边后缀和$w$的个数，根据乘法原理的操作。

好了，上代码吧：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[1000010]={0},b[1000010]={0},ans=0;
int main(){
	string s;
	cin>>s;
	int n=s.size();
	for(int i=1;i<n;i++){
		if(s[i]=='v'&&s[i-1]=='v'){//前缀和
			a[i]=a[i-1]+1;
		}else a[i]=a[i-1];
	}for(int i=n-1;i>=1;i--){//后缀和
		if(s[i]=='v'&&s[i+1]=='v'){
			b[i]=b[i+1]+1;
		}else b[i]=b[i+1];
	}for(int i=0;i<n;i++){
		if(s[i]=='o'){//找到一个o就左右边搭一个w乘上。
			ans+=b[i]*a[i];
		}
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：lhs_chris (赞：2)

[题目](https://www.luogu.com.cn/problem/CF1178B)

# 思路：
首先先把两个连续的 $\texttt{v}$ 合并成一个 $\texttt{w}$。


接着就计算 $\texttt{w}$ 的数量，$\texttt{wo}$ 的数量，最后是 $\texttt{wow}$ 的数量。

注意计算 $\texttt{wow}$ 数量的时候 **需要判断此 $\texttt{w }$  是否在至少一个 $\texttt{o}$ 之后**。

其实只需要判断此 $\texttt{w}$ 是否在 **第一个** 出现的$\texttt{o}$ 之后。
# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int M=2023;
const int inf=0x3f3f3f3f;
char a[N];
ll w,wo,wow;
ll flag=inf,len;
int main()
{
	scanf("%s",a);
	len=strlen(a);
	for(ll i=0;i<len;i++)
	{
		if(a[i]=='o')
		{
			flag=min(flag,i);
		}
		if(a[i]=='v' and a[i+1]=='v')
		{
			a[i]='w';//把两个连续的v合并成一个w 
		}
	}
	for(int i=0;i<len;i++)
	{
		if(a[i]=='w')
		{
			w++;
			if(wo and i>flag)//必须要在至少一个o之后 
			{
				wow+=wo;	
			}
		}
		if(a[i]=='o')
		{
			if(w)
			{
				wo+=w;
			}
		}
	}
	printf("%lld",wow);
	return 0;
}
```


---

## 作者：naroto2022 (赞：1)

# CF1178B题解
### 思路：前缀和+后缀和+乘法原理
首先建立两个数组：$a$，$b$，$a$ 用来记录第 $i$ 个字符前面有几个“`vv`”， $b$ 用来记录第 $i$ 个字符后面有几个“`vv`”。

那就很明了，用两个循环解决！如果第 $i$ 个字符是 $v$，第 $i-1$（$i+1$）个也是，那前（后）缀就加 $1$。

接下来求出来了前后缀，到了重点部分：累加答案。

其实也挺简单的，就是再把整个字符串重新遍历一遍，要是找到一个 $o$（设这个 $o$ 在字符串的第 $i$ 个位置），则答案 $ans$ 就加 $a[i]\times b[i]$。

这时有人就会问为啥加的是 $a[i]\times b[i]$？

这就要涉及小学的加乘原理了，这里用的是乘法原理：

前面有 $a[i]$ 对，后面有 $b[i]$ 对，总共就有 $a[i]\times b[i]$ 对。
### 总结
1. 开 `long long`，不开 `long long` 见祖宗。
2. 前后缀和。
3. 乘法原理。
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
string s;
long long a[1000005],b[1000005],ans;
//a数组记录前缀和：前面有几个"vv"。 
//b数组记录后缀和：后面有几个"vv"。 
int main(){
	cin>>s;
	int len=s.size();
	for(int i=1; i<len; i++){//记录前缀。 
		if(s[i]=='v'&&s[i-1]=='v') a[i]++;//多了一对"vv"。 
		a[i]+=a[i-1];
	} 
	for(int i=len-1; i>=1; i--){//记录后缀。 
		if(s[i]=='v'&&s[i+1]=='v') b[i]++;//多了一对"vv"。 
		b[i]+=b[i+1]; 
	}
	for(int i=0; i<len; i++)//最后一次遍历求答案，找o，然后用乘法原理累加答案。 
		if(s[i]=='o')//找到一个o 
			ans+=b[i]*a[i];
			//乘法原理。 
			//前面有a[i]对，后面有b[i]对，总共就有a[i]*b[i]对。
	printf("%lld",ans); 
	return 0;
}
```


---

## 作者：_bql (赞：1)

### 本题算法
前缀和 & 扫一遍累加

### 思路
求w(即两个连续的v)的前缀和（代码中的vf数组），同理做一遍后缀和（vb数组） 
然后扫一遍 对于每一个o 答案加上这个位置的vf*vb

### Code主要部分

```cpp
#define maxn 1000005
#define ll long long

ll l,vf[maxn],vb[maxn],i=1,cnt=0,ans=0;
char x,c[maxn];
int main()
{
	while(x=getchar())
	{
		if(x!='v' && x!='o') break;
		c[i]=x;//我也不知道我为什么要用这种奇奇怪怪的写法 建议读入不要这样写
		vf[i]=vf[i-1]+(c[i]=='v' && c[i-1]=='v');
		i++;
	}
	l=i-1;
	for(int i=l;i>=1;--i) vb[i]=vb[i+1]+(c[i]=='v' && c[i+1]=='v');
	for(int i=1;i<=l;++i)
	{
		if(c[i]=='o') ans+=vf[i-1]*vb[i+1];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：danlao (赞：1)

## 题目描述
给你一个长度最大为 $10^6$ 的字符串 $s$，问你有多少个非空子序列为 `vvovv`。
## 思路
这题考乘法原理。\
我们在字符串中寻找字符 `o`，然后答案与其左边字符串 `vv` 的个数与右边字符串 `vv` 的个数的积累加，最后结果就是最终答案。\
怎样求左边字符串 `vv` 的个数与右边字符串 `vv` 的个数呢？暴力吗？暴力的时间复杂度应该为 $O(n^2)$，直接超时。注意到字符串的数量为单调不降的，而且个数静止不变，所以我们可以使用类似前缀和和后缀和的方式维护。\
我们使用 $pre_i$ 表示以 $i$ 位置开始左边 `vv` 的个数，$nex_i$ 表示以 $i$ 位置右边 `vv` 的个数。如何更新 $pre_i$ 和 $nex_i$ 呢？\
我们先更新 $pre_i$。我们正序遍历 $pre$ 数组，注意到无论 $i$ 位置是否可以组成一个新的 `vv` 串，$pre_i$ 都一定包含 $pre_{i-1}$。所以当 $s_i$ 与 $s_{i-1}$ 都为 `v` 时，$pre_i=pre_{i-1}+1$，否则 $pre_i=pre_{i-1}$。\
然后我们更新 $nex_i$。此时，我们可以发现 $nex_i$ 的值是与 $nex_{i+1}$ 有关的，所以，我们考虑倒序遍历 $nex$ 数组。所以当 $s_i$ 与 $s_{i+1}$ 都为 `v` 时，$nex_i=nex_{i+1}+1$，否则 $nex_i=nex_{i+1}$。\
[AC 记录](https://codeforces.com/contest/1178/submission/273863699)

---

## 作者：铃宕 (赞：1)

**对于每个 $o$ 只需要记录它前面和后面 $w$ (即 $vv$ ) 的个数再乘起来即可**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans,pre[1000020],cnt,l;
//ans是答案，pre是每个数前面vv的个数，cnt是总共有多少vv，l是字符串长度 
char s[1000020];//记录字符串 
signed main(){
	scanf("%s",s+1);//输入 
	l=strlen(s+1);//正常操作 
	for(int i=1;i<=l;i++){
		pre[i]=pre[i-1];//记录这个数前面vv的个数 
		if(s[i]=='v'&&s[i-1]==s[i]) pre[i]++,cnt++;//如果这个数也可以组成vv，记录答案 
	}
	for(int i=1;i<=l;i++){
		if(s[i]=='o') ans+=pre[i]*(cnt-pre[i]);//cnt-pre[i]即为后面有多少vv，记录答案 
	}
	printf("%lld",ans);//输出 
}
```


---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1178B)

基础到不能再基础的计数。

对于每一个 `o`，我们计算出其前面连续一对 `v` 的数量，做一个前缀和的状物。

然后我们对后缀进行同样的处理，然后乘法原理求解即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
char s[N];
int f[N],g[N];
signed main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='v'&&s[i-1]=='v')	f[i]=f[i-1]+1;
		else	f[i]=f[i-1];
	}
	for(int i=n;i>=1;i--){
		if(s[i]=='v'&&s[i+1]=='v')	g[i]=g[i+1]+1;
		else	g[i]=g[i+1];
	}
	int ans=0;
	for(int i=1;i<=n;i++)	if(s[i]=='o')	ans+=(f[i]*g[i]);
	cout<<ans<<endl;
	return 0;
}
//////
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

给定一个只含 $\texttt{v}$ 和 $\texttt{o}$ 的字符串 $s$，求字符串中有多少个 $\texttt{wow}$（一个 $\texttt{w}$ 即为连续的两个 $\texttt{v}$）。

## 题目分析

考虑枚举每一个 $\texttt{o}$，设下标为 $i$，统计它左边和右边各有多少个 $\texttt{w}$，分别设为 $a_{i-1}$ 和 $b_{i+1}$，依据**乘法原理**，将它们乘起来即为答案，累加即可。

接下来，考虑怎么处理右边出 $\texttt{w}$ 的个数，$a_i$ 表示区间 $[1,i]$ 中有多少个 $\texttt{w}$，如果当前的 $s_i=\texttt{o}$，那么则从 $a_{i-1}$ 转移即可，如果当前 $s_i=\texttt{v}$，那要分两种情况：

- 如果 $s_{i-1}=\texttt{o}$，那么就组合不成 $\texttt{w}$，即 $a_i \leftarrow a_{i-1}$。
- 如果 $s_{i-1}=\texttt{v}$，那么 $s_i$ 就可以与 $s_{i-1}$ 组合成一个 $\texttt{w}$，即 $a_i \leftarrow a_{i-1}+1$。

知道了左边怎么处理，右边也同理，反着做就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
#define se second
#define fi first
#define pr pair<int,int>
#define pb push_back
#define ph push
#define ft front
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,b) memset(a,b,sizeof a)
const int N=1e6+10;
char s[N];
int n;
ll a[N],b[N],ans;
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>s+1;
    n=strlen(s+1);
    For(i,1,n) a[i]=a[i-1]+(s[i]=='v'&&s[i-1]=='v');
    Rep(i,n,1) b[i]=b[i+1]+(s[i]=='v'&&s[i+1]=='v');
    For(i,1,n)
    {
    	if(s[i]=='o')
    	{
    		ans+=(ll)a[i-1]*b[i+1];
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zdd6310 (赞：0)

# solution
字符串水题。

---
### 题意
给你一个字符串 $s$。问其中有多少个子序列是 `wow`。

`w` 定义为两个 **连续** 的 `v`。

---
发现 `wow` 中最重要的是中间的一个 `o`。

首先我们对于 $s$ 的左右两边扫出有多少个 **连续** 的 `v`。

形象的，记录两个数组：

$a_i$ 数组：表示第 $i$ 个字符从左到右有多少个连续的 `v`。

$a_i$ 数组：表示第 $i$ 个字符从右到左有多少个连续的 `v`。

于是 $ans=\sum\limits_{i=0}^{n-1}[s_i='o']a_i\times b_i$。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6+5;
string s;
int a[MAXN],b[MAXN];
int ans;
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>s;
    int n=s.size();s=" "+s;
    for(int i=1;i<=n;i++){
        a[i]=a[i-1]+(s[i]=='v'&&s[i-1]=='v');
    }
    for(int i=n;i>=1;i--){
        b[i]=b[i+1]+(s[i]=='v'&&s[i+1]=='v');
    }
    for(int i=1;i<=n;i++){
        if(s[i]=='o'){
            ans=ans+a[i]*b[i];
        }
    }
    cout<<ans<<"\n";
}
```

---

## 作者：OLE_OIer (赞：0)

这道题是 Codeforces 的一道 B 题，总体思路比较简单，就是前缀和与后缀和。

这里讲一下前缀和是什么：

前缀和是一种常见的优化方法，可以在询问序列时使用，详情请见[P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)。

前缀和是这样的。用一个数组 $x$ 来记录对于第 $i$ 个位置，有 $x_i$ 个某物体。在这道题里，它记录的是第 $i$ 个字符之前所含有字符串“vv”的个数。

同理，后缀和记录的是第 $i$ 个字符之后所含有字符串“vv”的个数。

我们可以利用前缀和来记录每一个“o”左边和右边各有多少个子串“vv”，然后用加乘原理求解。

具体细节看代码吧，里面注释还是比较详细的。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int x[1000010],y[1000010];
//x数组存储前缀和，y数组存储后缀和。
long long cnt;//记录可能性个数
int main(){
	ios::sync_with_stdio(false);//输入输出加速器
	cin>>s;
	int len=s.length();
	for(int i=1;i<len;++i) x[i]=x[i-1]+(s[i]=='v'&&s[i-1]=='v');//前缀和操作
	for(int i=len-1;i>=1;--i) y[i]=y[i+1]+(s[i]=='v'&&s[i+1]=='v');//后缀和操作
	for(int i=0;i<len;++i){
		if(s[i]=='o') cnt+=(long long)x[i]*y[i];
		//乘法原理记录个数，记得要开long long
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：AmemiyaHaruka5 (赞：0)

这个题可以用类似于前缀和的搞法搞（口胡）。

首先，我们可以用一个数组```isv```记录位置i前的‘w’的个数（两个连在一起的‘v’看做一个‘w’）。

然后，我们就可以对每一个‘o’，计算以其为```wow```中间的‘o’时可以构造几个```wow```。

由乘法原理得，此处应有$cnt_{[1,i-1]}cnt_{[i+1,l]}=cnt_{[1,i-1]}(cnt_{[1,l]}-cnt_{[1,i+1]})$个互异解。（$cnt_{[i,j]}$即为区间$[i,j]$内w的个数，l为题中所给字符串长度）

然后就有代码了（

code：

```cpp
#include <bits/stdc++.h>
using namespace std;

long long isv[1000001];

int main()
{
    string s;
    cin >> s;
    int l = s.length();
    for(int i = 1;i < l;i++)
    {
        if(s[i] == 'o')
            isv[i] = isv[i - 1];
        else if(s[i] == 'v' && s[i - 1] == 'v')
            isv[i] = isv[i - 1] + 1;
        else isv[i] = isv[i - 1];
    }
    long long sum = 0;
    for(int i = 0;i < l;i++)
    {
        if(s[i] == 'o')
        {
            if(i != 0 && i != l - 1)
            {
                sum += isv[i - 1] * (isv[l - 1] - isv[i + 1]);
            }
        }
    }
    cout << sum << endl;
}
```

---

