# [AGC034B] ABC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc034/tasks/agc034_b

`A`,`B`,`C` からなる文字列 $ s $ が与えられます。

すぬけ君は $ s $ に対して次の操作をできるだけ多く行おうとしています。

- $ s $ の連続した部分文字列であって `ABC` であるようなものをひとつ選び、 `BCA` に書き換える。

操作回数の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ |s|\ ≦\ 200000 $
- $ s $ の各文字は `A`,`B`,`C` のいずれか

### Sample Explanation 1

`ABCABC` → `BCAABC` → `BCABCA` → `BCBCAA` とすることで $ 3 $ 回操作可能で、これが最大です。

## 样例 #1

### 输入

```
ABCABC```

### 输出

```
3```

## 样例 #2

### 输入

```
C```

### 输出

```
0```

## 样例 #3

### 输入

```
ABCACCBABCBCAABCB```

### 输出

```
6```

# 题解

## 作者：atarashiTLE (赞：6)

### 题意简述：
略。见题目。

----
### 思路：
显然单独的`C`与`B`是没有用处的。所以我们只保留`BC`与`A`。

于是我们可以记录`A`的个数，如果遇到`BC`就把结果加上记录的值。如果遇到单独的`B`或`C`就把`A`的个数清零。

----
code:
```cpp
#include<iostream>
#include<string>
#define int long long
using namespace std;
signed main(){
   string c;
   cin>>c;
   int tot=0,ans=0;
   for(int i=0;i<c.size();i++){
      if(c[i]=='A')tot++;
      else if(c[i]=='B'){
         if(i+1<c.size()&&c[i+1]=='C'){
            ans+=tot;i++;
         }
         else 
            tot=0;
      }
      else
         tot=0;
   }
   cout<<ans<<endl;
   return 0;
}
```

__tips:__
1. 不开`long long`见祖宗
2. 注意下标

---

## 作者：Keep_RAD (赞：4)

这一题结论好题。

----

显然，不可能使用暴力，因为最多循环次数为 $s^{2}$，
而![](https://cdn.luogu.com.cn/upload/image_hosting/oyqa1zib.png)。

~~（暴力党：放弃）~~

那正解是什么呢？

### 猜想

可以发现，`ABC`中真正可以重复用的只有`A`和`BC`，单独的`B`和`C`与不是`ABC`字串的`CB`直接略去。

而像这样：`AABC`，经过一次转换后变为`ABCA`,还能转换一次！

所以只要发现一个`ABC`，就判断之前的字符是不是`A`,因为转换后`ABC`中的`AB`就变成了`BC`，如果之前是`A`，又能重新组合。

但走回头路显然没有直接一次循环好，正解就来了！

先用数据说话：

`AAABCBC`

第一次转换：

`AABCABC` 

我们发现了最后一个做出了一个贡献，并且前面的`A`也及时的搭配上，这就是理想组合！后面也多出了一个`A`与后面的搭配！

### 做法

先遍历一遍字串，如果找到连续的`A`，那么看后面，如果后面是`BC`，那么之前有多少个`A`就加多少的方案数，否则重新计数，周而复始。

### 验证

为保证正确性，我们再手算一组数据。
数据：

```
AAABCCAAB
```
1. 找到第一组连续的`A`，并且后面是`BC`，方案数加上`A`的个数，即`sum+=3`。
2. 到第二个`C`的时候，由于后面接不上，计算连续`A`数量的变量归零。
3. 找到第二组连续的`A` ，但后面不是`BC`，不算，计算连续`A`个数的变量归零。
4. 最后输出 $sum$。

注意：开`long long`！不然会错！

用这种方法，先编码，后对照程序修改！

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	string s;
	cin>>s;
	int sum=0;//方案数
	int tot=0;//计算连续A的个数 
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='A')
			tot++;
		else
			if(s[i]=='B')//有B
			{
				if(i+1<s.size()&&s[i+1]=='C')//有BC并且下标不越界
				{
					sum+=tot;
					i++;//下表顺延 
				}
				else tot=0;//后面顺延不了，归零 
			} 
			else//没有操作
				tot=0;
	} 
	cout<<sum<<endl;
	return 0;
}


```

完结，点个赞呗~~

---

## 作者：Inxwxc (赞：2)

# 题目分析
第一眼看这道题，以为是道很水的题，再看了看这题的难度，坚定了我的想法！写了个纯暴力，结果 TLE 了！

**实践证明，此题只能用一重循环！**

于是，我面题思过，悟了许久，终于大彻大悟：

- 首先，因为是一重循环，只能线性扫描过去。
- 然后，仔细悟一悟会发现，我们只需要判断一种结构就行了，即为连续的 $\texttt{A}$ 串 $\texttt{+BC}$**（这是最关键的部分）**。
- 接着，根据上述结构我们进行判断：如果我们扫描到一串 $\texttt{A}$，那么就记录它的起始位置和结束位置；如果扫描到一串 $\texttt{A}$ 后跟着 $\texttt{BC}$，操作数就加上 $\texttt{A}$ 串的长度（这个应该很好想到吧。。。），并将 $\texttt{BC}$ 与 $\texttt{A}$ 串互换位置就做完了。
- 最后输出结果即可！

### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string st;
long long ans,j,la,ra;
int main()
{	cin>>st;
	for (int i=1;i<st.size();i++)
	{	if (st[i-1]!='A'&&st[i]=='A')
			la=i,ra=la;
		if (st[i-1]=='A'&&st[i]=='A')
			ra++;
		if (st[i]=='B'&&st[i+1]=='C'&&i==ra+1&&ra!=la)
		{	st[i]='A';st[i+1]='A';
			ans+=ra-la+1;
			st[la]='D';st[la+1]='D';
			la=la+2;ra=i;
		}//由于判断结束后 BC 没用了，就把它变成了 D
		if (st[i]=='B'&&st[i+1]=='C'&&i==ra+1&&la==ra)
			st[i+1]='A',ans++,st[i]='D';
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Sarcasm (赞：1)

**[洛谷题目传送门](https://www.luogu.com.cn/problem/AT4992) + [ATCODER题目传送门](https://atcoder.jp/contests/agc034/tasks/agc034_b)**


------------

- 首先，吐槽一下样例有问题，输入 C 的时候输出应该为 0，并不是不输出。
- 我们不用考虑如何才能最大，其实只要不断做就好了，一定为最大
- 由此，可以由以上思路打一个while循环的暴力

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[200010];
int main(){
	gets(a);
	bool flag=false;//用来标记 
	int ans=0;
	if(strlen(a)<3) {cout<<"0";return 0;}//如果长度不到三，特判 
	while(!flag){
		int f=0;
		for(int i=0;i<strlen(a)-2;i++)
			if(a[i]=='A'&&a[i+1]=='B'&&a[i+2]=='C'){//寻找"ABC" 
				//替换 
				a[i]='B';
				ans++;
				a[i+1]='C';
				a[i+2]='A';
				f=1;
				break;
			}
		if(!f) flag=true;//如果未找到，退出循环 
	}
	printf("%d",ans);
 	return 0;
 }
```

但是，由于时间复杂度太大，这样写会TLE

------------

所以，我们为了节省时间，把字符串一点点地缩短，遇到落单的B,C去掉，只记录连续的BC和A,标记A的个数，并遇到BC就相加，否则中断，A的个数清零

c++代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int d;
long long a;
char s[200010];
int main(){
	gets(s);
	bool flag=false;//标记 为false 
	for(int i=0;i<strlen(s);i++){
	 	if(flag) {//如果这个被处理过了，跳过循环 
	 		flag=false;
	 		continue;
	 	}
	 	if(s[i]=='A') d++;//标记A 
	 	if(s[i]=='B') {//标记B 
	 		if(i+1<strlen(s))//将下一个标记掉 
	 			flag=true;
	 		if(s[i+1]=='C'){
	 			a+=d;//相加 
	 			continue;//跳过循环 
	 		}
	 		else{
				if(s[i+1]=='A') d=1;
				else d=0;//清零 
			}
		}
		if(s[i]=='C') d=0;
	}
	printf("%lld",a);//输出 
	return 0;
}
```

---

