# Problem with Random Tests

## 题目描述

You are given a string $ s $ consisting of $ n $ characters. Each character of $ s $ is either 0 or 1.

A substring of $ s $ is a contiguous subsequence of its characters.

You have to choose two substrings of $ s $ (possibly intersecting, possibly the same, possibly non-intersecting — just any two substrings). After choosing them, you calculate the value of the chosen pair of substrings as follows:

- let $ s_1 $ be the first substring, $ s_2 $ be the second chosen substring, and $ f(s_i) $ be the integer such that $ s_i $ is its binary representation (for example, if $ s_i $ is 11010, $ f(s_i) = 26 $ );
- the value is the bitwise OR of $ f(s_1) $ and $ f(s_2) $ .

Calculate the maximum possible value you can get, and print it in binary representation without leading zeroes.

## 说明/提示

In the first example, you can choose the substrings 11010 and 101. $ f(s_1) = 26 $ , $ f(s_2) = 5 $ , their bitwise OR is $ 31 $ , and the binary representation of $ 31 $ is 11111.

In the second example, you can choose the substrings 1110010 and 11100.

## 样例 #1

### 输入

```
5
11010```

### 输出

```
11111```

## 样例 #2

### 输入

```
7
1110010```

### 输出

```
1111110```

## 样例 #3

### 输入

```
4
0000```

### 输出

```
0```

# 题解

## 作者：MoyunAllgorithm (赞：6)

相对于其他题解，加入了更多思路推导并对贪心给出证明。

**题意**

给你一个长度为 $N(1 \le N \le 10^6)$ 的**随机生成**的 `01` 字符串。你需要找到他的 $2$ 个可以相交的连续子段，将这两个字段按位或，求结果最大值（用二进制）。

**分析**

先要搞清楚两个二进制数谁大。我们发现：

1. 先比较两个数的**长度**。长的大。

2. 从**最高位**开始往后比，当在某一位出现一个数是 $1$ 而一个数是 $0$ 时，有 $1$ 的大。

这是一个贪心的策略。因此本题也可以贪心的完成。

我们设结果的两个字段所形成的二进制数分别是 $A$ 和 $B$ ,且 $A \ge B$。

首先需要满足长度尽可能大。显然，**原字符串的第一个 `1` 一定出现在 $A$ 中**。证明：如果没有出现，那么这时的 $A_1$ 可以向高位继续扩大直到包含最高的 `1`。这是**不劣**的。

那么我们的 $A$ 其实已经确定了：设原字符串的第一个 `1` 的下标是 $head$，则 $A$ 是 $[head,N]$。

我们来找 $B$。因为 $B$ 存在的意义是填补 $A$ 的 `0` 位的空缺，又结合上文二进制数比较的步骤 $2$，可以得到结论：**$B$ 的最高位一定是 `1`，且这个 `1` 是用来填补 $A$ 的第一个 `0` 的位置的**。 也可以类似地证明：如果 $B$ 的最高位的 `1` 没有用于填补 $A$ 的第一个 `0`，那么这时最终结果会更劣。而且，$B$ 一定时以 `1` 开头的，因为 $B$ 的首要任务是填补 $A$ 的第一个 `0`，如果说填补那个 `0` 的那个 `1` 不是 $B$ 的开头，那么这个 `1` 前面的元素都是毫无意义的，这是不优的。

所以，$B$ 应该符合以下条件：以 `1` 开头；假设 $A$ 的第一个 `0` 出现在原字符串的第 `zero` 个，则 $B$ 的长度是 $|B|=N-zero+1$。如果更长，则会造成浪费，是不优的。

**现在需要对 $B$ 进行枚举**。其实只需要暴力枚举就可以：先枚举 $i \in [1,N-|B|+1]$，对于每个 $i$，枚举 $j \in [1,|B|]$，进行判断。**最劣复杂度是 $O(N^2)$ 没错，但是因为数据随机生成，所以说 $zero$ 会出现得很早，那么 $N-|B|+1$ 会非常小，因此时间复杂度近似于 $O(N)$。**

代码不太好写：**AC CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
int N;
int a[MAXN];
string f,ans;
//文本题解中的变量名与代码中的变量名基本相同，可以一一核对理解
int main()
{
	scanf("%d",&N);
	int head=0,lena=0;
	int zero=0,lenb=0;
//	puts(",,");
	for(int i=1;i<=N;i++) 
	{
		scanf("%1d",&a[i]);
		if(a[i]==1&&head==0) head=i;
		if(a[i]==0&&head&&zero==0)  zero=i;
	}
//	puts("--");
	lena=N-head+1;
	lenb=N-zero+1;
	if(head==0)
	{
		puts("0");
		return 0;
	}
	if(zero==0)
	{
		for(int i=1;i<=lena;i++) putchar('1');
		return 0;
	}//两个特判
//	puts("!!");
	f.resize(N),ans.resize(N);
	for(int i=head;i<zero;i++) putchar('1');//因为这里肯定是要匹配上的，所以先输出了
	for(int i=1;i<=N-lenb+1;i++)
	{
		f.clear();
		if(a[i]==0) continue;
		for(int j=1;j<=lenb;j++)
		{
			f+=((a[i+j-1]||a[zero+j-1])?'1':'0');
		}
		ans=max(ans,f);
	}
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：Allan_Xu (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1743D)

根据题意，要找出两个子串，使其按位或的值最大，可以很容易的想到，其中一个子串肯定是 **它本身**。

---

问题就聚焦到 **另一个子串** 的选取上，首先我们要去除 **前导零**，这点 **非常重要**，因为前导零不会对值的大小产生任何影响，反而干扰我们处理

---

首先我们要保证 **位数最高的** $0$ 被变为 $1$，再是**第二高的**，以此类推，但我们选取子串的时候不能 **直接** 用做高位的 1 对准最高位的 0（如样例 1）去或，我们需要从 **最高位的 $1$ 到最高位 $0$ 之间的 $1$ **为子串最高位的**都去比一遍**，求出 $\max string$，即**另一个子串**。

---

这看似时间复杂度最坏是 $O(n^2)$ 的，但注意 **随机** 二字，他保证了 **最坏情况出现的概率无限小**  ~~比你中彩票的几率可能还小~~，所以可以不考虑。

---

~~你们都喜欢的~~ AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){//快读
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
string s,r;
int main(){
    int n;
    n=read();
    cin >>r;
    bool flag=false;
    int m=0;
    for(int i=0;i<n;i++){
    	if(r[i]=='1'){
    		flag=true;
    		s+=r[i];
    		++m;
		}
    	if(flag&&r[i]=='0'){
    		s+=r[i];
    		++m;
		}
	}
	if(s=="")return puts("0"),0;
	s=" "+s;
	int index_0=0;
	for(int i=1;i<=m;i++){
		if(s[i]=='0'){
			index_0=i;
			break;
		}
	}
	if(index_0==0){
		for(int i=1;i<=m;++i) cout << s[i];
		return 0;
	}
	string maxs=s;
	for(int i=1;i<=index_0;i++){
		string temp=s;
		for(int j=i+1;j<=m;j++){
			if(s[j]=='1'||s[j-i]=='1'){
				temp[j]='1';
			}else{
				temp[j]='0';
			}
		}
		if(maxs<temp)maxs=temp;
	}
	for(int i=1;i<=m;++i) cout << maxs[i];
   	return 0;
}
```

---

## 作者：aimcf (赞：2)

~~zyy：随机算法是没有前途的。~~

首先第一个字符串容易发现就是原串本身。

枚举右端点 $i$。

由于或运算的性质，最好让第一个为 $0$ 的位置变成 $1$，不管右端点枚举到哪一个地方，左端点为 $1$ 的时候最优秀。

$r$ 从大到小枚举，枚举的次数卡时即可。

```cpp
//马蜂鬼畜勿喷
#include<bits/stdc++.h>
#define DILL
#define YYDS
#define This
#define is
#define int long long
using std::cin,std::string,std::bitset,std::cout;
const int N=1e6+10;
bitset<N>bit;bitset<N>max(bitset<N>a,bitset<N>b){
  for(int i=N-1;~i;i--){if(a[i]>b[i])return a;if(a[i]<b[i])return b;}
  {if(rand()&1)return a;return b;}
}
signed main(){
  int n,i=0;cin>>n;string s;cin>>s;
  for(int i=0;i<n;i++)bit[i]=s[n-i-1]-'0';
  bitset<N>bin=bit;
  while(1.*clock()/CLOCKS_PER_SEC<=3.6)bin=max(bin,bit|(bit>>i)),i++;bit=bin;
  if(bit.any()){
    bitset<1>flag;for(int i=n-1;~i;i--){
      if(bit[i]==1){flag|=1;cout<<"1";}
      else if(flag.any())cout<<"0";else{}
    }cout<<'\n';
  }else cout<<"0\n";
  return DILL YYDS! This is true;
}
```

[AC](https://www.luogu.com.cn/record/93169973)

---

## 作者：蒟蒻且菜鸡 (赞：2)

给定一个 $01$ 字符串，要求选择两个字符，将两个字符去除前导 $0$ 后表示成二进制的形式，将两个二进制进行或运算，求最大的值。

注意：去除前导零！！！我就在这里wa了无数次！！！

考虑贪心，我们可以发现：选取的两个字符串中一个必定是原串，另一个串一定是会向右移，去匹配原串中有 $0$ 的位置。

所以我们只需要找到从左往右数第一个 $1$ 的位置和在出现 $1$ 之后第一个 $0$ 的位置，因为他的数据是随机的，最后一位一位匹配就行了。



```

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    int id0=-1,id1=-1;
    bool flag=false;
    for(int i=0;i<s.length();i++)
    {
    	if(s[i]=='1')
		{
			id1=i;
			flag=true;
		} 
    	if(flag&&s[i]=='0') 
    	{
    		id0=i;
    		break;
		}
	}
	if(id1==-1)
	{
		cout<<0;
		return 0;
	}
    int len=n-id0+1;
    string ans=s;
    for(int i=0;i<id0;i++)
    {
        for(int j=i+len-1;j<n;j++)
        {
           string t=s;
           for(int k=n-len+1,l=i;l<=j;l++,k++) 
              if(s[l]=='1') t[k]='1';
           ans=max(ans,t);
        }
    }
    flag=false;
    for(int i=0;i<n;i++)
    {
	    if(ans[i]!='0') flag=true;
		if(flag) cout<<ans[i];
    } 
   	return 0;
}
```


---

## 作者：RockyYue (赞：1)

### 题意

给定一个长度为 $n$ 的 01 串 $s$，取其任意两个子段使得这两个子段最后端对齐进行二进制或运算的结果最大。

其中 $n\le 10^6$，**保证数据随机**。

### 解法

> Tips: “数据随机”蕴含的特殊性质
>
> 1. 树：深度在 $O(\log n)$ 级别。
> 2. 图：所有点度数较为平均（即不会出现菊花图等情况）。
> 3. 01序列：不会出现一长段相同的情况。
> 4. 普通序列：不会出现一长段递增/递减等情况。

由于是按位或操作，是 $1$ 的位尽量都要选上，选上的 $1$ 使其位数尽可能高，可以发现其中一个子段一定是 $s$ 整个串。

接下来想如何选取第二个串让结果尽量大，需要将尽可能高位的 $0$ 或为 $1$。

- 对于原串的前导 $0$ 部分是无能为力的，因为不能找出这么长的首位为 $1$ 的串。
- 但对于非前导 $0$ 的第一个 $0$，设其为 $s_p$（下标从 $0$ 开始），我们一定是可以将其或为 $1$ 的，因为 $s_{0\dots p-1}$ 中必然有 $1$，选取相应长度串即可。于是对于前面的 $1$ 逐个判断其作为第二个串首位的情况，长度即为 $n-p$，由于数据随机，前面 $1$ 的个数有限，复杂度正确。

---

## 作者：CENRUIYANG (赞：1)

首先观察到一个性质，其中一个串一定是从这个 $01$ 串最高位的 $1$ 开始一直到最后（全是 $0$ 的可以特判），因为只有这样才能取到最高位的 $1$ 。

假设最高位的 $1$ 位于 $pos1$ ，在 $pos1$ 之后的最高位的 $0$ 位于 $pos0$ ，我们只需最大化 $[pos0,n]$ 的答案。

考虑第二个串，发现如果我们找到这样一个串使得答案最大，那么 $pos0$ 这个位置一定变成了 $1$ ，所以我们第二个串的长度一定是 $n-pos0+1$ ，直接暴力枚举串的起点统计是 $O(n^2)$ 的。

突破口在于数据随机，因为数据是随机的，所以不会有很长一段连续的 $1$ ，也就是说 $n-pos0+1$ 约等于 $n-pos1+1$ ，因为第二个串的最高位一定是 $1$ ，所以我们枚举的起点一定是 $pos1$ ，可以达到这个长度的起点个数是 $O(1)$ 的，可以直接暴力做。

[代码](https://codeforces.com/contest/1743/submission/180148655)

---

