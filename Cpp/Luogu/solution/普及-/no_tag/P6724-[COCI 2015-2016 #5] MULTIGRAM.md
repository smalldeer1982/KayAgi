# [COCI 2015/2016 #5] MULTIGRAM

## 题目描述

定义由多个相同的单词首尾相连组成的字符串为复词，定义组成这个字符串的单词为词根。你需要判断它是否为复词。如果是，你需要找到其中第一个出现的词根。如果有多种可能的词根，请输出长度最短的。不是复词则输出 `-1`。

**注意：如果两个字符串经过字母顺序的改变后能够完全相同，则认作同一个单词。**

## 说明/提示

#### 样例解释

##### 样例 $1$

注意到 `aa` 也是第一个出现的词根，但 `a` 是最短的。

##### 样例 $2$

这个字符串仅由单词 `ab` 构成，不是复词。

##### 样例 $3$

字符串由两个相同的单词 `bba` 和`bab` 组成，第一个出现的为 `bba`。

#### 数据规模与约定

对于 $100\%$ 的数据，字符串的长度不超过 $10^5$。

#### 说明

**题目译自 [COCI2015-2016](https://hsin.hr/coci/archive/2015_2016/) [CONTEST #5](https://hsin.hr/coci/archive/2015_2016/contest5_tasks.pdf) *T2 MULTIGRAM***。

## 样例 #1

### 输入

```
aaaa```

### 输出

```
a```

## 样例 #2

### 输入

```
ab ```

### 输出

```
-1```

## 样例 #3

### 输入

```
bbabab```

### 输出

```
bba```

# 题解

## 作者：封禁用户 (赞：6)

### 题意分析
给定字符串，求最小词根。
### 解题方法
枚举词根的长度，切片并判断哈希值即可。
### AC 代码
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int hash_str(string k){
	int ans=0;
	for(int i=0;i<k.size();++i)
		ans+=k[i]*k[i];
		//普通的进制哈希无法判断两个字符串字母改变顺序后能否完全相同
		//如 "ab" 与 "ba" 的哈希值是不相等的 
		//故计算字符串每一位的 Ascii 码值的平方之和 
	return ans;
}
signed main(){
	string k;
	cin>>k;
	int sizeof_k=k.size();
	for(int i=1;i<=k.size()-1;++i){		//枚举词根长度 
		if(sizeof_k%i==0){	 
			int xb=i;
			bool kk=true;
			int right=hash_str(k.substr(0,i));    //词根哈希值 
			while(xb<sizeof_k){
				if(hash_str(k.substr(xb,i))!=right){
					kk=false;
					break;
				}
				xb+=i;
			}
			if(kk==true){     
				cout<<k.substr(0,i);
				return 0;
			}
		}
	}
	cout<<-1;
}
```

---

## 作者：JK_LOVER (赞：5)

## 题意
给你一个字符串，求出最小词根。词根的定义为：首尾相连可以拼接成原串，而且可以改变字母位置。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p6724)
## 分析
可以改变字母位置，这表明此题不是什么匹配算法。而无论怎样改变字母位置，字符的多少和种类是确定了的，而且字符集合很小，可以直接开个桶记录。那么现在只需要暴力枚举词根长度就可以了。由于
$$
\sum_{i=1}^{n} \frac{n}{i} = O(n\log n)
$$
所以总的复杂度为 $O(26\times n\log n)$ 。实测跑得飞快。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
int cnt[30],c[30][N],len = 0,flag = 0;
char ch[N];
int main()
{
	scanf("%s",ch + 1);
	len = strlen(ch+1);
	for(int i = 1;i <= len;i++) 
	{
		for(int j = 1;j <= 26;j++)
		c[j][i] = c[j][i-1] + ((ch[i] - 'a' + 1) == j);
	}
	for(int i = 1;i < len;i++)
	{
		if(len%i) continue;
		memset(cnt,0,sizeof(cnt));
		for(int j = 1;j <= 26;j++) cnt[j] = c[j][i] - c[j][0]; 
		flag = 0;
		for(int j = 1;j*i <= len;j++)
		{
			int L = i*(j-1),R = i*j;
			for(int k = 1;k <= 26;k++)
			{
				if(c[k][R] - c[k][L] != cnt[k]) {
					flag = 1;break; 
				}
			}
		}
		if(!flag){
			for(int j = 1;j <= i;j++)
			putchar(ch[j]);
			printf("\n");
			return 0;
		}
	}
	cout<<"-1"<<endl;
	return 0;
}
```


---

## 作者：Genshin_ZFYX (赞：5)

[原题传送门](https://www.luogu.com.cn/problem/P6724)

题意（言意简赅版）：输入一个长度为 $len$ 字符串，把他平均分成 $x$ 份，$1 \le x \le len $。每部分每个字母的数量必须一样。输出 $x$ 最小时的字符串的前 $x$ 个字母，如没有输出 $-1$。

这下看的懂了。

$10^5$ 以内因数最多的数是 $83160$ 和 $98280$，各有 $128$ 个因数，直接暴力。[害得我又写了一个代码](https://www.luogu.com.cn/paste/ugacjdhm)。

## 解题思路

由于它可以改变字母的顺序，我们开个桶记录每个字符出现的次数，再一一匹配每一部分即可。

AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define I return
#define love 0
#define FIRESTARS ;
string s;
int a[10005],b[10005];
signed main()
{
	cin>>s;
	int len=s.size(),sum=0;
	for(int i=0;i<len-1;i++)
	{
		if(len%(i+1))continue; // i 记得加1，否则会 RE
		memset(a,0,sizeof(a)); //记得初始化
		int f=0,len1=len/(i+1),k=i;
		for(int j=0;j<=i;j++)a[s[j]]++; //记录
		for(int j=1;j<len1;j++)
		{
            memset(b,0,sizeof(b));
            for(int u=1;u<=i+1;u++)++b[s[++k]];
            for(int u='a';u<='z';u++)
					if(a[u]!=b[u])
					{
						f=1;break;
					}
			if(f)break; //如果不行直接跳过
		}
		if(f)continue;
		for(int j=0;j<=i;j++)cout<<s[j]; //找到后了就直接输出
		I love FIRESTARS //我爱火星！
	}
	cout<<"-1";
	I love FIRESTARS //我爱火星！
}

```

---

## 作者：Tjaweiof (赞：1)

# P6724 题解——Tjaweiof
[题目传送门](https://www.luogu.com.cn/problem/P6724)

看到数据范围字符串的长度不超过 $10^5$，~~什么？这么多？必须用 dp！~~

解法：暴力枚举词根的长度（设为 $s$），用桶存前 $s$ 个字母，再判断后面每一组符不符合要求。若符合，则直接输出前 $s$ 个字母。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[1000001];
int a[27], b[27], n;
bool work(int i){
	memset(a, 0, sizeof a);
	int now = 0, k = n / i - 1;
	bool f = 1;
	for (int j = 1; j <= i; j++){
		a[ch[now] - 97]++;
		now++;
	}
	for (int t = 1; t <= k; t++){
	    memset(b, 0, sizeof b);
	    for (int j = 1; j <= i; j++){
			b[ch[now] - 97]++;
			now++;
		}
	    for (int j = 0; j < 26; j++){
			if (a[j] != b[j]){
				f = 0;
			}
		}
	}
	return f;
}
int main(){
    scanf("%s", ch);
    n = strlen(ch);
    for (int i = 1; i < n; i++){
		if (n % i == 0){
	        if (work(i)){
				for (int j = 0; j < i; j++){
					printf("%c", ch[j]);
				}
				return 0;
			}
	    }
	}
    printf("-1");
    return 0;
}

```
#### 此代码时间复杂度 $O(d(n)n)$，空间复杂度 $O(n)$，完美过关！

---

## 作者：dead_X (赞：1)

## 题意
求一个字符串的最小循环节，使得字符串能被分割成几个完整的循环节且每个循环节每个字符的出现次数相同，并输出第一个循环节。

找不到最小循环节输出 $-1$ 。
## 思路
本来以为是什么kmp……

看看这个数据范围，立马开始写暴力。

注意到不超过 $10^5$ 的数因数一定不会很多，所以枚举循环节长度并依次匹配。

是否每个字符出现次数相同直接桶排序即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int w=0;
    char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) w=w*10+ch-48,ch=getchar();
    return w;
}
char ch[1000003];
int a[33],b[33];
int main()
{
    scanf("%s",ch);
    int n=strlen(ch);
    for(int i=1; i<n; i++) if(n%i==0)
    {
        memset(a,0,sizeof(a));
        int now=0,k=n/i-1;
        bool f=1;
        for(int j=1; j<=i; j++) ++a[ch[now++]-'a'];
        for(int t=1; t<=k; t++) 
        {
            memset(b,0,sizeof(b));
            for(int j=1; j<=i; j++) ++b[ch[now++]-'a'];
            for(int j=0; j<26; j++) if(a[j]!=b[j]) f=0;
        }
        if(f) { for(int j=0; j<i; j++) printf("%c",ch[j]); exit(0); }
    }
    puts("-1");
    return 0;
}
```

---

## 作者：Oracynx (赞：0)

## P6724 [COCI2015-2016#5] MULTIGRAM 题解

### 思路分析

本题形式化题面如下：

给你一个字符串 $s$ 找到一个合适的分割方式，使每一个分割的所含字符相同，输出长度最小的分割中的第一个字符串。特别的，如果如果无法将 $s$ 分为 $2$ 段及以上，输出 $\texttt{-1}$。

由于所含字符相同的前提是它们的长度相同，所以我们只需枚举 $n$ 的所有因子即可。

我们先枚举长度，如果 $n \bmod i \ne 0$ 直接跳过，否则枚举每个相邻的分段检查即可。

### 代码实现

```cpp
#include <cstdio>
#include <cstring>
constexpr int MaxN = 1e5 + 5;
int n;
int t[MaxN][26];
char s[MaxN];
bool check(int x)
{
    for (int i = x; i < n; i += x)
    {
        for (int j = 0; j < 26; j++)
        {
            if (t[i][j] - t[i - x][j] != t[i + x][j] - t[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            t[i][j] = t[i - 1][j];
        }
        t[i][s[i] - 'a']++;
    }
    for (int i = 1; i <= n - 1; i++)
    {
        if (n % i == 0)
        {
            if (check(i))
            {
                for (int j = 1; j <= i; j++)
                {
                    printf("%c", s[j]);
                }
                printf("\n");
                return 0;
            }
        }
    }
    printf("-1\n");
    return 0;
}
```

---

## 作者：ACtheQ (赞：0)

### P6724 [COCI2015-2016#5] MULTIGRAM

#### 题意简述

给定一个环状字符串，你需要找到其中第一个出现的词根。如果有多种可能的词根，请输出长度最短的。如果没有词根，输出 $-1$。

#### 思路及实现


首先知道定义由多个相同的单词首尾相连组成的字符串为复词。

那么就可以把这个字符串看成为一个环，所以枚举的范围是 $1 \sim 2n$。

**注意**：当字符串的长度为 $i(1 \le i \le n)$ 的倍数时 `continue`。

我们可以用个桶，变量 $j$ 循环 $0 \sim i-1$ 统计每个 $S_j$ 出现了多少回。

再用变量 $j$ 循环 $i \sim$`s.size()-1`。

我们再用个桶，变量 $k$ 循环 $j \sim j+i$ 统计每个 $S_k$ 出现了多少回。

然后再匹配判断 $0 \sim i-1$ 的这个字串是否能成为词根。

如果可以，那么输出结束程序。

最后，循环结束输出 $-1$。

---

## 作者：BreakPlus (赞：0)

第一眼看到题目，你会以为是什么 $\text{hash}$ 或者 $\text{kmp}$，实际上它没有那么复杂。

首先，一个字符串的词根的长度必定是该字符串长度的因子，所以枚举词根长度的时候，一旦发现不是总长度的因子直接跳过，成功节省时间。

还有，字符串的顺序任意，相信大家都会想到用排序来搞，为了提升效率~~卡常~~，桶排序比较合适。

然后就可以暴力枚举了！

上代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100010;
char str[maxn]; int t[26],tmp[26];
int main(){
    scanf("%s",str);
    int len=strlen(str);
    for(register int sub=1;sub<=(len>>1);sub++){ //词根不能是整个字符串！
        if(len%sub) continue;//剪枝
        memset(t,0,sizeof(t));//别忘了初始化
        for(register int i=0;i<sub;i++) t[(int)(str[i]-'a')]++;//统计词根的各个字母个数
        bool flag=true;
        for(register int i=sub;i<len;i+=sub){
            memset(tmp,0,sizeof(tmp));
            for(register int j=i;j<i+sub;j++) tmp[(int)(str[j]-'a')]++;
            for(register int j=0;j<26;j++)
                if(tmp[j]!=t[j]) flag=false;//统计并判断是否和词根相同
        }
        if(flag){
            for(register int i=0;i<sub;i++) putchar(str[i]);
            putchar('\n'); return 0;
        }//满足条件就输出
    }
    puts("-1");//特殊情况
    return 0;
}
```

相似题目： [LibreOJ P10035](https://loj.ac/p/10035)

---

## 作者：lgydkkyd (赞：0)

这题浅浅观察一下，还是用暴力写比较易于理解，不过这题的暴力估计得优化才能过。

------------

由于多个相同词根可以成为该字符串，我们可以得出词根的长度一定是母串长度的因数且不等于母串。

------------

于是接下来我们可以暴力枚举母串的长度，如果是总长度的因数则用桶数组记录每种字母的个数，然后往后遍历如果下一个子串字母个数与第一个假定子串完全一致则继续循环否则跳出循环，如果遍历完整个母串仍符合要求输出词根并结束程序，当枚举完母串长度依然没有词根则输出不可以的情况。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100001];
int l=0;
int main(){
	cin>>s;
	l=strlen(s);
	for(int i=l;i>=0;i--)s[i+1]=s[i];//向后挪动一位，方便计算 
	for(int i=1;i<l;i++){//遍历母串 
		if(l%i==0){
			int cnt[27]={},f=true;
			for(int j=1;j<=i;j++){
				cnt[(int)(s[j]-'a'+1)]++;//统计第一个词根26个字母的个数 
			}
			for(int j=i+1;j<=l;j+=i){//向后遍历 
				int cnt2[27]={};
				for(int k=j;k<j+i;k++){
					cnt2[(int)(s[k]-'a'+1)]++;//统计后面词根26个字母的个数 
				}
				for(int k=1;k<=26;k++){
					if(cnt[k]!=cnt2[k]){//不是词根 
						f=false;
						break;
					}
				}
			}
			if(f==true){//是词根 
				for(int j=1;j<=i;j++)cout<<s[j];
				return 0;//结束程序 
			}
		}
	}
	cout<<-1;//输出-1 
	return 0;//华丽结束 
}
```

---

