# PALIN - The Next Palindrome

## 题目描述

A positive integer is called a _palindrome_ if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer _K_ of not more than 1000000 digits, write the value of the smallest palindrome larger than _K_ to output. Numbers are always displayed without leading zeros.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
2
808
2133```

### 输出

```
818
2222```

# 题解

## 作者：hsfzLZH1 (赞：13)

这是一道数学题。

题目大意是给你一个大整数k（位数范围为1000000），让你找到最小的回文数x，使得x>k。

根据定义由k+1开始枚举每个数字，判断其是否是回文数，显然太慢，我们需要考虑其他的方法。

回文数的定义就是正着读和倒着读都一样的数，也就是说以中间为对称轴（如果是奇数个数位就是正中间的数字，偶数个数位就是中间两个数字之间的空隙），两侧是对称的，知道了半边就可以反转求出另外半边。

我们由给出的数字k的左半边进行反转，就可以得到一个回文数t，有两种情况：

1.t>k，那么这个t就是我们所求，因为比t小的第一个回文数是数字的左半边-1进行翻转后的数（左半边是个10的幂就不是这样，需要特殊处理），但是这个回文数一定是小于k的；

2.t<=k，那么我们把k的左半边+1进行翻转，如果+1后左半边不是10的整数次幂，得到的这个值一定大于k，为所求答案。如果+1后左半边是10的整数次幂时左半边原来一定是形如9...99的形式，观察可得他下一个回文数一定是10...01，如此可进行特殊处理。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000010;//最大位数
int T,a[maxn],l,c[maxn];
char s[maxn];
inline bool cmp(int x[],int y[])//判断大整数x是否小于等于y
{
	for(int i=0;i<l;i++)if(x[i]!=y[i])return x[i]<y[i];
	return false;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",s);//以字符串形式输入，方便转换
		if(strcmp(s,"9")==0){printf("11\n");continue;}//特判
		l=strlen(s);
		for(int i=0;i<l;i++)a[i]=s[i]-'0';//字符串转化为整数数组进行处理
		for(int i=0;i<=(l-1)/2;i++)c[i]=c[l-i-1]=a[i];//计算k的左半边反转过去后得到的值t
		if(!cmp(a,c))//进行比较，如果k<=t
		{
			a[(l-1)/2]++;//左半边加一
			for(int i=(l-1)/2;i;i--)a[i-1]+=a[i]/10,a[i]%=10;//处理进位
			for(int i=0;i<=(l-1)/2;i++)c[i]=c[l-i-1]=a[i];//反转过去
		}
		for(int i=0;i<l-1;i++)printf("%d",c[i]);//输出
		if(c[l-1]==10)printf("1\n");//特判，因为进位后第一位可能是10
		else printf("%d\n",c[l-1]);
	}
	return 0;
}
```

---

## 作者：maomao233 (赞：2)

这题类似于[P1609](https://www.luogu.com.cn/problem/P1609)，稍微改一下即可

------------
### 题意
给定一个 $\leq$ ${10}^{1000000}$ 的数，找出比它大的最小回文数。
### 分析
- 本题的数据量比较大（每个数字的位数能达到 $1000000$ ），所以需要用字符串来读取。

- 每次完成一次循环数组都要**清零**，不然程序会延续上一次循环的数组。

### 一个小技巧（特判）
在输入字符串的时候可以判断整个字符串是不是都是 $9$ ，如果全是那就直接将这个数 $+2$ 即可。例如输入 $99999$ 则直接输出 $100001$ 。

------------
### $AC$ $code$
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[1000001];
int main()
{
	int t;
	string s;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		memset(c,0,sizeof(c));
		cin>>s;
		int j=0;
		while(s[j]=='9')//判断整个字符串是不是都是9，如果全是那就将这个数+2（例：99999 => 100001） 
		{
			j++;
		}
		if(j==s.size())
		{
			for(s[0]='1',j--,s+="0";j>0;j--)
			{
				s[j]='0';
			}
		}
		for(j=0;j<=s.size()-j-1;j++)
		{
			c[j]=c[s.size()-j-1]=s[j];
		}
		if(c<=s)
		{
			while(c[--j]=='9');
			c[j]=c[s.size()-j-1]=++c[j];
			for(j++;j<=s.size()-1-j;j++)
			{
				c[j]=c[s.size()-1-j]='0';
			}
		}
		cout<<c<<endl;
	}
	return 0;//记得加上，完美结束！
}
```

---

## 作者：Swiftie_wyc22 (赞：1)

这道题同洛谷的P1609，做对了双倍经验哦。

输入的数假设是 $\text{ABCD}$ 这样一个四位数（每一个字母是一位数），那么必然有 $\text{ABBA}$ 是第一个比 $\text{ABCD}$ 大的回文或者第一个比 $\text{ABCD}$ 小的回文。

为什么呢？我们把 $\text{ABCD}$ 分成两半，$\text{AB}$ 和 $\text{CD}$ ，回文数的特征是两边对称，所以要么 $\text{AB}$ 翻转到右侧，要么 $\text{CD}$ 翻转到左侧。

假设 $\text{AB}$ 有改动，则翻转过来的 $\text{BA}$ 一定比原数还要大。变小也同理。所以翻转一半的字符串一定是最优的。

据此算法，时间复杂度是线性的，$200$ 位和这道题的 $100004$ 位都可以处理


还有，不要忘了特判，如果中间位是 $9$ 则需要处理进位。还有，全为 $9$ 的字符串可以直接进位处理，比如 $9999$ 直接当成 $10000$ 处理。

（代码借鉴了P1609的题解）

```cpp
#include <bits/stdc++.h>

using namespace std;

char ans[1000010];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T; cin >> T;
	while (T--)
	{
		string s;
		memset(ans, 0, sizeof(ans));
		cin >> s;
		int i = 0;
		while (s[i] == '9')
			i++;
		if (i == s.size())
			for (s[0] = '1', i--, s+="0"; i>0; i--)
				s[i] = '0';
		for (i = 0; i <= s.size() - i - 1; i++)
			ans[i] = ans[s.size() - i - 1] = s[i];
		if (ans <= s)
		{
			while (ans[--i] == '9');
			ans[i] = ans[s.size() - i - 1] = ++ans[i];
			for (i++; i <= s.size() - 1 - i; i++)
				ans[i] = ans[s.size() - 1 - i] = '0';
		}
		cout << ans << endl;
	}
	
	return 0;
}
```


---

## 作者：亚索s (赞：1)

大于某个数K的最小回文数，做的很纠结~对很多细节还不是很熟。测试了找到的所有用例，结果是对的。

## 主要分K中数字为1个和多个两种情况考虑

### 1. 如果K只含有一个数字，则结果就为K+1，当K=9时结果为11

### 2. 当数字个数大于1时，将K分为两部分，并将前半部分对称到后半部分得到P。这个时候又要考虑两种情况：

###     a. 如果得到的新数字P>K，则P就是大于K的最小回文数，因为P和K的前半部分是一样的，而后半部分又是前半部分的对称，所以P和K之间不会再有比P小的回文数了。

###     b. 如果得到的新数字P<K，则需要从P的中间增加数字来得到新的回文数P‘，因为根据回文数两头对称的特点，增加中间的数才能得到最小的回文数。


代码分割线

---------------------
```

#include <cstdio>
#include <cstring>
 
const int maxn = 1000005;
 
int n, num[maxn];
char str[maxn];
 
inline bool cmp() {
	for(int i = 0; i < n; i++)
		if(num[i] < str[i] - '0') return 1;
		else if(num[i] > str[i] - '0') return 0;
	return 1;
}
 
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", str); n = strlen(str);
		if(n == 1) {
			if(str[0] == '9') printf("11\n");
			else printf("%c\n", str[0] + 1);
			continue;
		}
 
		for(int i = n >> 1; i >= 0; i--) num[i] = num[n - i - 1] = str[i] - '0'; num[n] = 0;
 
		if(cmp()) {
			int st = n >> 1; num[st]++;
			for(int i = st; num[i] > 9; i++) {
				num[i] = 0;
				num[i + 1]++;
				if(i == n - 1) n++;
			}
			for(int i = 0; i < st; i++) num[i] = num[n - i - 1];
		}
		for(int i = 0; i < n; i++) printf("%d", num[i]);
		printf("\n");
	}
	return 0;
}




```
---------------------

---

## 作者：SegTree (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/SP5)

## 题目分析
+ 设这个数为 $\overline{a_1 a_2 \cdots a_n}$。
+ 若 $n\bmod 2=1$，那么将 $\overline{a_1 a_2 a_3\cdots a_{n/2+1}}$（这里 $n/2$ 默认向下整除。）复制一遍，删去末尾并反转，拼在原数后面。
+ 如果这个数大于原数，答案就是这个结果。
+ 如果这个数不大于原数，那么将它加一，再像上面一样复制再删去末尾并反转拼在后面。答案就是这个结果。
+ 若 $n\bmod 2=0$，那么将 $\overline{a_1 a_2 a_3\cdots a_{n/2}}$ 复制一遍拼在原数后面。如果大于原数就是结果。
+ 否则就加一再反转拼在后面，就是结果。
+ 但是上面的算法会有一个问题，$n=1$ 时无法正确处理。那么若原数小于 $9$ 返回这个数加一，否则返回 $11$。
+ 另外一个问题：输入 $999$ 会输出 $10001$。
+ 于是特判所有数字都是 $9$ 的点，即将位数加一，第一个数为 $1$，最后一个数为 $1$，中间为 $0$。
+ 因为只用 $+1$，没必要套高精加。
+ 于是我们就 AC 了本题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Big {
    int a[1000005],len;
    void input(){
        string s;
        cin>>s;
        len=s.length();
        for(int i=0;i<len;++i){
            a[i+1]=s[i]-'0';
        }
    }
    void output(){
        for(int i=1;i<=len;++i)printf("%d",a[i]);
        printf("\n");
    }
    string to_Str(){
        string s;
        for(int i=1;i<=len;++i){
            s+=a[i]+'0';
        }
        return s;
    }
    void to_Big(string s){
        memset(a,0,sizeof(a));
        len=s.length();
        for(int i=0;i<len;++i){
            a[i+1]=s[i]-'0';
        }
    }
};
bool operator>(Big a,Big b){
    if(a.len!=b.len)return a.len>b.len;
    for(int i=1;i<=a.len;++i){
        if(a.a[i]!=b.a[i])return a.a[i]>b.a[i];
    }
    return 0;
}
Big add(Big s){
    s.a[s.len]++;
    if(s.a[s.len]<=9)return s;
    for(int i=s.len-1;i>=1;--i){
        s.a[i]+=s.a[i+1]/10;
        s.a[i+1]%=10;
    }
    if(s.a[1]>=10){
        char ch=s.a[1]/10+'0';
        s.a[1]%=10;
        string t=ch+s.to_Str();
        s.to_Big(t);
        return s;
    }
    return s;
}
Big ans(Big s){
    if(s.len==1){
        if(s.a[1]<9){
            Big k=s;
            k.a[1]++;
            return k;
        }
        else {
            Big k;
            k.len=2;
            k.a[1]=1;
            k.a[2]=1;
            return k;
        }
    }
    bool F=0;
    for(int i=1;i<=s.len;++i){
        if(s.a[i]!=9)F=1;
    }
    if(!F){
        s.len++;
        s.a[1]=s.a[s.len]=1;
        for(int i=2;i<s.len;++i)s.a[i]=0;
        return s;
    }
    if(s.len%2){
        Big t;
        t.len=s.len/2+1;
        for(int i=1;i<=s.len/2+1;++i){
            t.a[i]=s.a[i];
        }
        string a=t.to_Str();
        reverse(a.begin(),a.end());
        a.erase(a.begin());
        Big k;
        k.to_Big(a);
        a=t.to_Str()+k.to_Str();
        k.to_Big(a);
        if(k>s)return k;
        else {
            t=add(t);
            a=t.to_Str();
            reverse(a.begin(),a.end());
            a.erase(a.begin());
            Big k;
            k.to_Big(a);
            a=t.to_Str()+k.to_Str();
            k.to_Big(a);
            return k;
        }
    }
    else {
        Big t;
        t.len=s.len/2;
        for(int i=1;i<=s.len/2;++i){
            t.a[i]=s.a[i];
        }
        string a=t.to_Str();
        reverse(a.begin(),a.end());
        Big k;
        k.to_Big(a);
        a=t.to_Str()+k.to_Str();
        k.to_Big(a);
        if(k>s)return k;
        else {
            t=add(t);
            a=t.to_Str();
            reverse(a.begin(),a.end());
            Big k;
            k.to_Big(a);
            k.to_Big(t.to_Str()+k.to_Str());
            return k;
        }
    }
}
int T;
Big a;
int main(){
    cin>>T;
    while(T--){
        a.input();
        ans(a).output();
    }
}
```

---

## 作者：Wings_of_liberty (赞：0)

# 分析
我们分情况讨论：

首先，我们发现一种特殊情况，全是 $9$，在这种情况下，容易发现，最小值就是 $101$，$1001$ 这种形式。

然后，对于剩下的数，我们将左侧的数翻转复制到右侧，如果大于原数，那么这就是答案，如果小于原数，那么我们将左侧的最后一位加一，再次复制到右侧即可。

# 实现
对于有奇数个数字和偶数个数字来说，在本题没有什么区别，可以一起实现。

对于上文所说的最后一位加一再复制其实只改变最后一位即可。

我看了一些题解，有许多人是通过数组来实现，但是其实字符串也很方便。

# 注意
最重要的是，如果你在修改左侧最后一位时，是 $9$，那么我们需要进位，一定不要忘记，在进位时，便需要循环实现。

如果你也使用字符串，并且使用了流输入（$\text{cin}$），那么你可以像我一样在主函数里加上一行，这样能使输入变快，但是此时就不能使用 $\text{scanf}$ 。

记得你的数据中下标小的是高位数字，不要用反了。

# 其他
[双倍经验](https://www.luogu.com.cn/problem/P1609)

# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define op(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define cl() fclose(stdin),fclose(stdout)
#define F(i,x,y) for(int i=(x);i<=(y);i++)
typedef long long ll;
string a,b;
int len,mid;
bool fla=true;//特判 
inline void init(){
	cin>>a;
	b=a;
	len=a.length();
	mid=len>>1;
	fla=true;//多组数据 
}
inline void work(){
	F(i,0,len-1){
		if(a[i]!='9'){
			fla=false;
			break;
		}
	}
	if(fla){
		cout<<"1";
		F(i,1,len-1){
			cout<<"0";
		}
		cout<<"1"<<endl;
		return;
	}
	F(i,0,mid){
		b[len-i-1]=b[i];
	}
	if(b>a){
		cout<<b<<endl;
		return;
	}
	F(i,mid,len){
		if(b[i]=='9'){
			b[i]=b[len-i-1]='0';
			continue;
		}
		b[i]=b[len-i-1]=b[i]+1;
		break;
	}
	cout<<b<<endl;
}
int main(){
//	op("");
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	F(i,1,t){
		init();
		work();
	}
//	cl();
	return 0;
}

```


---

## 作者：scp020 (赞：0)

### 本题位数较大，所以只能使用字符串读入

因为是回文数，所以我们只考虑前半部分的情况就能确定一个回文数。

如一个型为 $\overline{xyz}$ 的数，我们考虑 $\overline{xyx}$（这个数是回文数）是否大于 $\overline{xyz}$，如果大于，那么就可以输出 $\overline{xyx}$，否则就把 $y$ 自增 $1$，并且考虑进位（同高精度的进位），直到我们求出的数大于原数为止。

这里要特判一下，如果输入是 $9$，我们就直接输出 $11$。

别的不多说了，代码这些大佬都给了。

对了，这题和 [P1609](https://www.luogu.com.cn/problem/P1609) 一样，双倍经验等着你！

---

## 作者：oddy (赞：0)

## 题意解释

给定一个数，找出最小的比它大的回文数。

## 解题思路

考虑如下操作：

让数的前半部分（如果数有 $n$ 位，就是前 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 位）不变，后半部分依着前半部分改变，造出一个回文。倘若这样造出的新数比原数大，那么这个新数就是答案了。反之，就要把原数左半部分加 $1$，再造出新数，就是答案了。

因为该数最多达 $10^6$ 位，所以需要用字符串存储。

Tips：

1. 新数组注意清零！！
2. 我的代码不能处理全是 $9$ 的情况，所以要特判。具体地讲，如果输入的是 $\underbrace{9\dots9}_{n\ \text个\ 9}$，那么直接输出答案：$1\underbrace{0\dots0}_{(n-1)\ \text{个}\ 0}1$。

## 代码

```cpp
#include <cstdio>
#include <cstring>

int T, n;
char s[1000005], t[1000005];

bool all9() {
    for(int i = 1; i <= n; i++)
        if(s[i] != '9') return false;
    return true;
}

int main() {
    for(scanf("%d", &T); T; --T) {
        memset(t, 0, sizeof(t)); // 注意清零！！
        scanf("%s", s+1); // 下标从 1 开始
        n = strlen(s+1);
    
        if(all9()){ // 特判
            putchar('1');
            for(int i = 2; i <= n; i++) putchar('0');
            puts("1");
        } else {
            for(int i = 1; i <= n / 2; i++) t[i] = s[i]; // 构造新数
            for(int i = n / 2 + 1; i <= n; i++) t[i] = s[n-i+1];
            if(strcmp(s+1, t+1) >= 0) { // 直接构造不符合题意，前半部分加 1
                *s = '0';
                int l9;
                for(l9 = n / 2 + (n & 1); l9 >= 0; l9--) {
                    if(s[l9] == '9') s[l9] = '0';
                    else break;
                } // 加 1：找到第一个不为 9 的数，加 1，那些连续的 9 全都变成 0
                s[l9]++;
            }
            for(int i = n / 2 + (n & 1) + 1; i <= n; i++) s[i] = s[n-i+1];
    
            puts(s+1);
        }
    }

    return 0;
}
```

---

## 作者：The_Lost_09 (赞：0)

## [传送门](https://www.luogu.com.cn/problem/SP5)

这题是[P1609](https://www.luogu.com.cn/problem/P1609)的加强版

### 题目描述：
求比一个 $10^{1000000}$ 的数大的最小回文数

### 思路：

1. 如果所有数位都为 $9$，那就是这个数加 $2$，如 $9 \rightarrow 11$, $ 99 \rightarrow 101$，不做 2. 3. 
 
2. 以这个数前一半为基础做出回文数，和原数比较大小 ，如果比原数大，直接输出。

3. 否则从中间开始往前找第一位不是 $9$ 的，将此位和它的对称位加 $1$，它们中间全置为 $0$，这样可以保证它比原数大而又是最小的回文数。

#### 接下来就是你们最喜欢的 $Code$
###### 禁止抄袭

$My Code$:

```cpp
#include<stdio.h>
#include<string.h>

char ch[1000005],rc[1000005];

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		memset(ch,0,sizeof ch);
		memset(rc,0,sizeof rc);
      //记得清空（我才不会告诉你们我因为这个WA了两次）
		scanf("%s",ch);
		int len=strlen(ch),mid;mid=(len-1)/2;//因为是零下标，所以减一再除以二
		bool nine=0;
		for(int i=mid;i>=0;i--){
			rc[len-i-1]=ch[i];
			rc[i]=ch[i];
			if(ch[i]!='9'||ch[len-1-i]!='9')nine=1;
		}
		if(nine==0){
			printf("1");
			for(int i=1;i<len;i++){
				printf("0");
			}
			printf("1\n");
		}//1.的处理
		else{
			if(strcmp(rc,ch)<=0){
	    		for(int j=mid;j>=0;j--){
	    		    if(rc[j]<'9'){
	    		        rc[j]++;
	    		        rc[len-1-j]=rc[j];
	    		        break;
	    		    }
	    		    rc[j]=rc[len-1-j]='0';
	    		}
	    	}//3.的处理
			printf("%s\n",rc);//输出
		}
	}
	return 0;//完结撒花☆(￣▽￣)★ 。
}

---

