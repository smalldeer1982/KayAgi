# 题目信息

# Prinzessin der Verurteilung

## 题目描述

定义一个字符串的 $MEX$ 为**在输入中不作为连续子字符串出现的最短字符串**。

如果有长度相同的 $MEX$，则取字典序最小的。

## 样例 #1

### 输入

```
3
28
qaabzwsxedcrfvtgbyhnujmiklop
13
cleanairactbd
10
aannttoonn```

### 输出

```
ac
f
b```

# AI分析结果

### 题目内容
# 定罪公主

## 题目描述
定义一个字符串的 $MEX$ 为**在输入中不作为连续子字符串出现的最短字符串**。
如果有长度相同的 $MEX$，则取字典序最小的。

## 样例 #1
### 输入
```
3
28
qaabzwsxedcrfvtgbyhnujmiklop
13
cleanairactbd
10
aannttoonn
```
### 输出
```
ac
f
b
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是基于数据范围 $n\leq1000$ 以及 $26^3 > 1000 > 26^2$ 这一特性，意识到 $MEX$ 的长度不会超过3，从而通过枚举长度为1到3的子串来寻找答案。
 - **思路方面**：多数题解采用按字典序依次枚举子串，然后判断子串是否在原字符串中出现的方式。不同之处在于枚举的具体实现方式，有的使用嵌套循环，有的使用类似进制转换的方式更新子串。
 - **算法要点**：关键在于如何高效地枚举子串以及快速判断子串是否在原字符串中。判断子串是否存在，大部分题解使用了 `string` 的 `find` 函数，部分题解使用了 `set` 来保存已出现的子串，还有题解使用了 `KMP` 算法。
 - **解决难点**：难点在于确定枚举的范围以及优化枚举和判断的过程，避免超时。例如，通过分析数据范围确定只需要枚举长度为1到3的子串；在更新子串时，采用合适的方式保证按字典序枚举。

### 所选的题解
#### 作者：YCS_GG (5星)
 - **关键亮点**：思路清晰，直接利用数据范围确定枚举长度为1到3的子串，通过三层嵌套循环按字典序枚举子串，并使用 `find` 函数判断子串是否在原字符串中，代码简洁明了，可读性高。
 - **重点代码核心实现思想**：通过三层嵌套循环分别枚举长度为1、2、3的子串，每次构造子串后用 `find` 函数判断其是否在输入字符串中，若不存在则输出并结束循环。
```cpp
#include <bitset>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
int t;
int pos[27];
int main() {
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        memset(pos, 0, sizeof(pos));
        for (int i = 0; i < n; i++) {
            pos[s[i] - 'a'] = 1;
        }
        bool f = 0;
        for (int i = 0; i < 26; i++) {
            if (pos[i] == 0) {
                cout << (char)(i + 'a') << endl;
                f = 1;
                break;
            }
        }
        for (char i = 'a'; i <= 'z'; i++) {
            if (f == 1) {
                break;
            }
            for (char j = 'a'; j <= 'z'; j++) {
                if (f == 1) {
                    break;
                }
                string tmps = "";
                tmps += i;
                tmps += j;
                if (s.find(tmps) == s.npos) {
                    cout << tmps << endl;
                    f = 1;
                    break;
                }
            }
        }
        for (char i = 'a'; i <= 'z'; i++) {
            if (f == 1) {
                break;
            }
            for (char j = 'a'; j <= 'z'; j++) {
                if (f == 1) {
                    break;
                }
                string tmps = "";
                tmps += i;
                tmps += j;
                for (char k = 'a'; k <= 'z'; k++) {
                    if (f == 1) {
                        break;
                    }
                    string p = tmps;
                    p += k;
                    if (s.find(p) == s.npos) {
                        cout << p << endl;
                        f = 1;
                        break;
                    }
                }
            }
        }
    }
}
```

#### 作者：HerikoDeltana (4星)
 - **关键亮点**：对题意理解清晰，通过举例帮助理解 `MEX` 的概念。使用三维 `bool` 数组记录长度为1、2、3的子串是否出现，最后按字典序遍历数组找到未出现的子串输出，方法较为新颖。
 - **重点代码核心实现思想**：通过遍历输入字符串，利用三维 `bool` 数组标记出现过的长度为1、2、3的子串。最后通过三层循环按字典序遍历数组，找到第一个未标记的子串并输出。
```cpp
#include <bits/stdc++.h>
#define Heriko return
#define Deltana 0
#define Romano 1
#define S signed
#define U unsigned
#define LL long long
#define R register
#define I inline
#define D double
#define LD long double
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false)
using namespace std;
I void fr(LL & x)
{
    LL f = 1;
    char c = getchar();
    x = 0;
    while (c < '0' || c > '9') 
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') 
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x *= f;
}
I void fw(LL x)
{
    if(x<0) putchar('-'),x=-x;
    static LL stak[35];
    LL top=0;
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    putchar('\n');
}
char s[1005];
bool k[30][30][30];
S main()
{
    // freopen("my.in","r",stdin);
    LL t;fr(t);
    while(t--)
    {
        LL n;
        mst(k,0);
        fr(n);gets(s+1);
        for( LL i=1;i<=n;++i)
        {
            k[s[i]-'a'+1][0][0]=1;
            if(i>1) k[s[i]-'a'+1][s[i-1]-'a'+1][0]=k[s[i-1]-'a'+1][0][0]=1;
            if(i>2) k[s[i]-'a'+1][s[i-1]-'a'+1][s[i-2]-'a'+1]=k[s[i-1]-'a'+1][s[i-2]-'a'+1][0]=k[s[i-2]-'a'+1][0][0]=1;      
        }
        bool g=0;
        for( LL p=0;p<=26 and g==0;++p)
            for( LL j=min(p,1ll);j<=26 and g==0;++j)
                for( LL i=1;i<=26 and g==0;++i)
                    if(!k[i][j][p])
                    {
                        if(p) putchar(p+'a'-1);
                        if(j) putchar(j+'a'-1);
                        if(i) putchar(i+'a'-1);
                        putchar('\n');
                        g=1;
                    }
    }
    Heriko Deltana;
}
```

#### 作者：123hh2 (4星)
 - **关键亮点**：代码实现详细，通过 `while` 循环和字符串的操作按字典序不断更新子串，并使用 `find` 函数判断子串是否在原字符串中，逻辑连贯，易于理解。
 - **重点代码核心实现思想**：在 `while` 循环中，每次构造一个子串后用 `find` 函数判断其是否在输入字符串中，若不存在则输出。若存在，则通过特定的字符串更新方式（类似进制进位）构造下一个字典序的子串。
```cpp
#include<bits/stdc++.h>
#include<Windows.h>//我才知道CF支持这个头文件qwq 
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-') {f=-1;}ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(int x)
{
	if(x<0) {putchar('-');x=-x;}
	if(x>9) {write(x/10);} 
	putchar (x%10+'0');
	return;
}
int main()
{
	int t=read();
	while(t--)
	{
		int n=read();
		string a="";//原子串 
		cin>>a;
		string b="a";//查找子串 
		while(1)
		{
			if(a.find(b)==string::npos)//找一下有没有子串 b 
			{
				cout<<b<<endl;
				break;
			}
			else
			{
				//这一块是用来让子串从最小字典序到最大字典序更新的 
				reverse(b.begin(),b.end());
				b[0]++;
				for(int i=0;i<b.size();i++)
				{
					if(b[i]>'z'&&i!=b.size()-1)
					{
						b[i]='a';
						b[i+1]++;
					}
					if(b[i]>'z'&&i==b.size()-1)
					{
						b[i]='a';
						b+="a";
					}
				}
				reverse(b.begin(),b.end());
			}
		}
	}
	return 0;
}
```

### 最优关键思路或技巧
利用数据范围确定枚举边界，只枚举长度为1到3的子串，大大减少了枚举量。在枚举子串时，采用合适的方式按字典序生成子串，如使用嵌套循环或者类似进制转换的方法更新子串。判断子串是否在原字符串中，使用 `string` 的 `find` 函数是一种简单有效的方式。

### 拓展
此类题目属于字符串枚举类型，类似的题目套路通常是根据数据范围确定合理的枚举范围，优化枚举过程。例如，在一些字符串匹配问题中，也可能通过分析数据范围来简化匹配过程。

### 推荐题目
 - [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：通过对字符串的处理和校验，考察对字符串操作和简单数学计算的能力。
 - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串的查找与统计，与本题判断子串是否存在有相似之处。
 - [P1593 因子和倍数](https://www.luogu.com.cn/problem/P1593)：虽然主要考察数论知识，但在处理输入数据时需要对字符串进行适当的操作，与本题对输入字符串的处理有类似思路。

### 个人心得摘录与总结
123hh2提到在CF比赛中，A题耗时久且只过了一个测试点，B题因无合适翻译放弃，最后却拿了360分感到离谱。此心得反映出比赛中题目难度判断和时间分配的重要性，同时也说明即使部分题目未完全解决，也可能通过其他题目获得不错的分数。 

---
处理用时：108.77秒