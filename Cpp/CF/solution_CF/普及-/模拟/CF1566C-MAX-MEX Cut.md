# MAX-MEX Cut

## 题目描述

A binary string is a string that consists of characters $ 0 $ and $ 1 $ . A bi-table is a table that has exactly two rows of equal length, each being a binary string.

Let $ \operatorname{MEX} $ of a bi-table be the smallest digit among $ 0 $ , $ 1 $ , or $ 2 $ that does not occur in the bi-table. For example, $ \operatorname{MEX} $ for $ \begin{bmatrix} 0011\\ 1010 \end{bmatrix} $ is $ 2 $ , because $ 0 $ and $ 1 $ occur in the bi-table at least once. $ \operatorname{MEX} $ for $ \begin{bmatrix} 111\\ 111 \end{bmatrix} $ is $ 0 $ , because $ 0 $ and $ 2 $ do not occur in the bi-table, and $ 0 < 2 $ .

You are given a bi-table with $ n $ columns. You should cut it into any number of bi-tables (each consisting of consecutive columns) so that each column is in exactly one bi-table. It is possible to cut the bi-table into a single bi-table — the whole bi-table.

What is the maximal sum of $ \operatorname{MEX} $ of all resulting bi-tables can be?

## 说明/提示

In the first test case you can cut the bi-table as follows:

- $ \begin{bmatrix} 0\\ 1 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 2 $ .
- $ \begin{bmatrix} 10\\ 10 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 2 $ .
- $ \begin{bmatrix} 1\\ 1 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 0 $ .
- $ \begin{bmatrix} 0\\ 1 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 2 $ .
- $ \begin{bmatrix} 0\\ 0 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 1 $ .
- $ \begin{bmatrix} 0\\ 0 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 1 $ .

The sum of $ \operatorname{MEX} $ is $ 8 $ .

## 样例 #1

### 输入

```
4
7
0101000
1101100
5
01100
10101
2
01
01
6
000000
111111```

### 输出

```
8
8
2
12```

# 题解

## 作者：wangqinyan (赞：3)

这题思路与代码实现其实都很简单。

**题目思路**

这道题其实就是一道贪心，我们可以用一个``a``数组来存储第``i``列切开来后这一列能获得的价值。这时，有以下三种情况：当这一列上下两个分别为 $0$ 和 $1$ 时，能获得的价值为 $2$ 时，直接将这一列切割出来，单独存储。当这一列全为 $0$ 或全为 $1$ 时，同时，他前一列全为 $1$ 或全为 $0$ 时，就将这两列单独存储。当前面两个可能都不满足时，就先暂时将这一列存储起来，看能不能与下一列合并。具体实现可以看代码。

**注意点**

注意每次做完都要初始化，输出答案时要换行。

**代码**
```
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
long long ans,x,n,t;
bool p1,p2;
int main()
{
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	cin>>t;
	while(t--)
	{
		cin>>n;
		cin>>s1>>s2;
		ans=0,x=-1;
		for(int i=0;i<n;i++)
		{
		 	p1=((s1[i]=='0')|(s2[i]=='0'));
			p2=((s1[i]=='1')|(s2[i]=='1'));
		 	if(p1&&p2)x=2,ans+=x;
		 	else
			if(p1==false)
			{
		 		if(x==1)ans++,x=-1;
		 		else
				x=0;
			}
			else
			{
				ans++;
				if(x==0)ans++,x=-1;
				else x=1;
			}
		}
		cout<<ans<<endl;
	}
//    fclose(stdin);
//    fclose(stdout);
	return 0;
}

 
```
感谢观看！

---

## 作者：Big_Dinosaur (赞：2)

记录 $a_i$ 为将第 $i$ 列切开来后这一列能获得的价值。接下来进行贪心。

对于 $a_i=2$，将它单独切开来，价值为 $2$。

对于 $a_i=1$ 或 $a_i=0$，则继续分类讨论。

若 $a_{i+1}=2-a_i$，则将这两列切开来，价值为 $2$，否则单独切开，价值为 $a_i$。

最后就是代码啦！
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Dino{
inline int r(){
int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}return x*f;
}
int n,t,a[114514];
inline void bigdino(){
n=r();string x,y;cin>>x>>y;for(int i=1;i<=n;++i)
if(x[i-1]!=y[i-1])a[i]=2;else if(x[i-1]=='1')a[i]=0;else a[i]=1;a[n+1]=3;
int ans=0;for(int i=1;i<=n;++i){
if(a[i]==2)ans+=2;
else if((a[i]==1&&a[i+1]==0)||(a[i]==0&&a[i+1]==1)){ans+=2;a[i+1]=-1;}
else if(a[i]!=-1)ans+=a[i];
}cout<<ans<<endl;
}
inline void _(){
t=r();while(t--)bigdino();
}
}
signed main(){Dino::_();}
```

---

## 作者：Jur_Cai (赞：2)

### 题意
$\operatorname{MEX}$ 的定义和 [B](https://www.luogu.com.cn/problem/CF1566B) 一样，就是二进制串变成了上下两个，求值变为了最大值。

### 分析
[B 中的思想不再复述了](https://www.luogu.com.cn/blog/105865/solution-cf1566b)

当一列 $01$ 具备时，就可以直接分出去。当一列全为 $0/1$ 时，我们希望它能和后面的组合，由于一列 $1$ 的 $\operatorname{MEX}$ 值为 $0$，分不分出去没区别，但当一列是 $0$ 时，且后面有 $0$ 的情况下，将它分出去能获得额外的 $1$。处理好这个就过了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char s1[100005],s2[100005];
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		//flag0/1表示前面是否有0/1
		int n,ans=0,flag0=0,flag1=0;
		scanf("%d",&n);
		scanf("%s%s",s1+1,s2+1);
		for(int i=1;i<=n;i++) {
			if(s1[i]=='0'||s2[i]=='0'){
				if(flag0) ans++;//前面有多余的0
				flag0=1;
			}
			if(s1[i]=='1'||s2[i]=='1') flag1=1;
			if(flag1&&flag0) {
				flag1=flag0=0;
				ans+=2; 
			}
		}
		if(flag0) ans++;
		cout<<ans<<'\n'; 
	}
}
```

---

## 作者：The_jester_from_Lst (赞：0)

# 分享一种不一样的贪心思路。
## 预处理
在输入时，先对数据做预处理：对于每一个 $a_i$ 与 $b_i$，我们通过交换使得 $a_i$ **严格不大于** $b_i$，以方便后面判断。
```cpp
for(int i=1;i<=n;i++)cin>>a[i];
for(int i=1;i<=n;i++){
	cin>>b[i];
	if(a[i]>b[i])swap(a[i],b[i]);
}
```
## 贪心
对于每一个 $a_i$ 与 $b_i$，我们先假设它们是一个被单独切出来的双表。由于我们已经进行了预处理，所以此时存在 $3$ 种情况：
### 1：$a_i=0$，$b_i=1$
这种情况最好，贡献为 $2$。
### 2：$a_i=0$，$b_i=0$
这时我们需要联系下一位：若下一位的 $a$，$b$ 都是 $1$，则如果让这两位合并为一个双表，贡献为 $2$，不合并则两位的总贡献仅有 $1$。所以果断合并。
### 3：$a_i=1$，$b_i=1$
同样的，我们联系下一位：若下一位的 $a$，$b$ 都是 $0$，则如果让这两位合并为一个双表，贡献为 $2$，不合并则两位的总贡献仅有 $1$。所以果断合并。
## 坑点：
### 1：考虑下一位时需要判断有没有越界。
### 2：字符数组大小需要开至 $10^6$。
### 3：（也可能是自身缘故？）快读会错！！！
将这三个点合起来，一个满分的贪心代码就诞生了：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n;
char a[1000086],b[1000086];
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		int s=0;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(a[i]>b[i])swap(a[i],b[i]);
		}
		int i=1;
		while(i<=n){
			if(a[i]=='0'&&b[i]=='1')s+=2;
			else if(a[i]=='0'&&b[i]=='0'){
				if(i!=n&&a[i+1]=='1'&&b[i+1]=='1'){
					s+=2;
					i++;
				}
				else s++;
			}
			else if(a[i]=='1'&&b[i]=='1'){
				if(i!=n&&a[i+1]=='0'&&b[i+1]=='0'){
					s+=2;
					i++;
				}
			}
			i++;
		}
		cout<<s<<endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

***题目大意：***

有两个长度相等的字符串，你可以任意截取长度的串，在这个截取的部分中，两个字符串中只会出现 $0$ $1$ 这三个数字。这个部分返回的值就是两个子串都没有的数字。

像

```11```

```00```

返回的就是 $2$。

思路：

贪心。我们分类讨论，发现一个字符串中的数无非只有三种情况。要么是一串 $0$。要么是一串 $1$。（用串来表示）

第一种：

```000000```

第二种：

```111111```

而两个串组合也只有三种情况。全一，全零，零一交替。

第一种：

```000000```

```000000```

第二种：

```000000```

```111111```

第三种：

```101011```

```010100```

随后我们又能发现，只有第一种情况和第三种情况才能加上数。

那我们就贪心，如果是第一种情况，我们每次就加一，第三种情况每次加二。这时就会出现这么一种情况：

```000001```

```000001```

零和一不是交替的，那么我们是不是就要特判了呢？那肯定不用，这种情况我们结合代码一起讲。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define re ra()
int ans, s, T, p1, p2, s0 = 2, n;
string s1, s2;
inline int ra()
{
    int jjy = 0,txy = 1;
    char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') txy = -1; ch = getchar(); }
    while(isdigit(ch)){jjy = jjy * 10 + ch - '0'; ch = getchar(); }

    return jjy * txy;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	T = re;
	while(T --) {
		n = re;	cin >> s1 >> s2;
		p1 = p2 = 0;ans = 0;
		for(int i = 0; i < s1.size(); i ++)
		{
			if(p1 && (s1[i] == '0' || s2[i] == '0')) ans ++;//这里之所以要判断p1是否为真是因为可能上一次的0和1匹配掉了，那这里就多加了。
			if(s1[i] == '0' || s2[i] == '0') p1 = 1;
			if(s1[i] == '1' || s2[i] == '1') p2 = 1;
			if(p1 && p2) {ans += 2; p1 = 0; p2 = 0; continue;}//0和1在一列，就直接加二
			//cout << ans << "\n";
		}
		if(p1) ans ++; cout << ans << "\n";
	} 
	return 0;
}



```

既然看完代码了，那我就来解释一下刚刚那种情况。


```000001```

```000001```

$i =$ $0$ $1$ $2$ $3$ $4$ $5$

$ans =$ $0$ $1$ $2$ $3$ $4$ $6$

答案是正确的。这是因为在第一种情况（即全零）每次加的时候，都会少加一次，而有零一情况的时候，加的二刚好抵消掉这个少加的一。

```0000``` ```01```

```0000``` ```01```

$4 + 2 = 6$

如果是普通情况我们就需要在最后加特判。

---

## 作者：江户川·萝卜 (赞：0)

- 如果上下两个是 `0` 和 `1`，那么 `MEX` 是 `2`，达到最大值，直接独立分开。
- 如果这一列都是 $0$ 或都是 $1$，且前面一列都是 `1` 或都是 `0`，那么把这两列独立分开。
- 否则，暂时记录 `MEX`，- 等待下一列是否可以与这一列组合。

具体看代码。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int t;cin>>t;
	while(t--){
		int n;
		cin>>n;
		string s1,s2;
		cin>>s1>>s2;
		int ans=0,lst=-1;
		for(int i=0;i<n;i++){
		 	bool f1=((s1[i]=='0')|(s2[i]=='0')),f2=((s1[i]=='1')|(s2[i]=='1'));
		 	if(f1&&f2) lst=2,ans+=lst;
		 	else if(!f1){
		 		if(lst==1) ans++,lst=-1;
		 		else lst=0;
			}
			else{
				ans++;
				if(lst==0) ans++,lst=-1;
				else lst=1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：0)

### 题意

> 有两个`01`串 $a$ 和 $b$。现在你要把 $[1,n]$ 分成若干份，不妨设分成了 $k$ 份，每份是 $[p_i,p_{i+1}-1]$ 。显然 $1=p_1<p_2<\dots<p_{k+1}=n+1$ 。
> 
> 定义一个集合的 $\text{MEX}$ 为其中没有出现的最小自然数。
> 
> 求 $\sum_{1\le i\le k} \text{MEX}(a_{p_i}.a_{p_i+1},\dots,a_{p_{i+1}-1},b_{p_i}.b_{p_i+1},\dots,b_{p_{i+1}-1})$ 的最小值。

### 做法

首先我们可以注意到，最优解中每一段的长度是 $1$ 或 $2$ 。

这个很好理解：如果一段的长度为 $3$ ，考虑把最左边一列分出去，那么唯一会使答案变小的就是

$$\begin{vmatrix}1&0&0\\1&0&0\end{vmatrix}$$

这种形态。那么把右边分出去即可使答案变大。

如果长度超过了 $3$ ，也是类似的情况。

-----------

考虑 DP。

设 $dp_i$ 表示把 $[1,i]$ 分成若干份，答案的最小值。

那么转移时枚举最后一份的长度是 $1$ 还是 $2$，则 $dp_i=\min(dp_{i-1}+MEX_{i,i},dp_{i-2}+MEX_{i-1,i})$ 。

其中 $MEX_{l,r}$ 表示 $\text{MEX}(a_{l}.a_{l+1},\dots,a_{r},b_{l}.b_{l+1},\dots,b_{r})$ 。

求 $\text{MEX}$ 很简单，不赘述。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
char s1[100005],s2[100005];
int dp[100005];
int calc(int l,int r){
	int num[2];
	num[0]=num[1]=0;
	for(int i=l;i<=r;i++)num[s1[i]-'0']++,num[s2[i]-'0']++; 
	if(!num[0])return 0;
	else if(!num[1])return 1;
	else return 2;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		scanf("%s%s",s1+1,s2+1);
		dp[0]=0;
		for(int i=1;i<=n;i++)dp[i]=max(dp[i-1]+calc(i,i),dp[i-2]+calc(i-1,i));
		printf("%d\n",dp[n]);
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

对于一列的 $2$ 个数，有 $3$ 状态：

+ 状态 `0`，即全为 $0$；

+ 状态 `1`，即全为 $1$；

+ 状态 `2`，即一个 $0$ 一个 $1$。

为方便理解，我们可以把输入字符转化为一个字符串，表示状态。当然代码里不会这么干。

例如，第一组数据里就可以这么写：

```
2101200
```

设第 $i$ 为的状态为 $s[i]$。

设一个从 $l$ 位到 $r$ 位的子串为 $(l,r)$，其中 $1\le l\le r\le n$。

设答案为 $ans$。

本题可以一个个枚举。

设当前位置为 $i$，则：

+ 当 $s[i]$ 为 `0`：

	+ 当 $i=n$ 或者 $s[i+1]$ 为 `0`：
    
      直接划分出 $(i,i)$，并且 $ans$ 加 $1$。
        
   + 当 $s[i+1]$ 为 $1$：
   
     划分出 $(i,i+1)$，$ans$ 加 $2$，并且跳过第 $i+1$ 位。
     
   + 否则划分出 $(i,i)$ 和 $(i+1,i+1)$，$ans$ 加 $3$，并且跳过第 $i+1$ 位。

+ 当 $s[i]$ 为 `1`：

	令 $j$ 满足 $i<j\le n$，并且对于所有的 $k\ (i<k<j)$，都有 $s[k]$ 为 `1`，但是 $s[j]$ 不为 `1`。
    
	划分 $(i,j)$，$ans$ 加 $2$，并且直接跳过第 $i+1$ 位到第 $j$ 位。

+ 当 $s[i]$ 为 `2`：

	直接划分出 $(i,i)$ ，并且 $ans$ 加 $2$。
    
输出 $ans$ 即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
char a[100002];
char b[100002];
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1566C_1.in","r",stdin);
	freopen("CF1566C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%s%s",&n,a+1,b+1);
		ans=0;
		for(int i=1;i<=n;++i){
			if(a[i]!=b[i]){
				ans+=2;
				continue;
			}
			if(a[i]=='1'){
				while(i<=n){
					++i;
					if(a[i]=='0'||b[i]=='0'){
						ans+=2;
						break;
					}
				}
			}
			else{
				if(i==n)++ans;
				else if(a[i+1]=='0'&&b[i+1]=='0')++ans;
				else{
					if(a[i+1]=='1'&&b[i+1]=='1')ans+=2;
					else ans+=3;
					++i;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/58013733)

By **dengziyue**

---

