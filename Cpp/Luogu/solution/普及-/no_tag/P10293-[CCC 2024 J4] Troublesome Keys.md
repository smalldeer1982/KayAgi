# [CCC 2024 J4] Troublesome Keys

## 题目描述

Alex 的键盘很奇怪。有两个字母按键出现了问题：

- 键盘上有一个按键，每次按下它的时候总是显示另一个错误的字母。Alex 把这个按键称为愚蠢的按键。奇怪的是，Alex 从来没有尝试过输入这个错误的字母。
- 键盘上还有一个按键，按下它的时候则不会显示任何内容。Alex 把这个按键称为安静的按键。

Alex 至少按下了一次愚蠢的按键，但不一定按下了安静的按键。

你需要确定出现问题的按键和按下它时显示的错误的字母。幸运的是，这是可能的，因为 Alex 从来没有在按下愚蠢的按键之后立即按下安静的按键，也没有再按下安静的按键之后立即按下愚蠢的按键。

## 说明/提示

**【样例 1 解释】**

与愚蠢的按键对应的字母是 `o`，每次按下会显示错误的字母 `x`。安静的按键没有被按下过。

**【样例 2 解释】**

与愚蠢的按键对应的字母是 `o`，每次按下会显示错误的字母 `x`。没有显示的安静的按键对应的字母是 `s`。

**【样例 3 解释】**

与愚蠢的按键对应的字母是 `s`，每次按下会显示错误的字母 `z`。没有显示的安静的按键对应的字母是 `o`。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证输入中每行都只包含小写字母，$1\leq N\leq 5\times 10^5$。

下面的表格显示了 $15$ 分的分配方案：

| 分值 | 描述 | 范围 |
| :-: | :- | :-: |
| $3$ | 安静的按键没有被按下过，按键次数很少。 | $N \leq 50$ |
| $3$ | 按下的第一个有问题的按键是愚蠢的按键，按键次数很少。 | $N \leq 50$ |
| $5$ | 按下的第一个有问题的按键可能是愚蠢的按键或者安静的按键，按键次数很少。 | $N \leq 50$ |
| $4$ | 按下的第一个有问题的按键可能是愚蠢的按键或者安静的按键，按键次数可能很多。 | $N \leq 5 \times 10^5$ |

## 样例 #1

### 输入

```
forloops
fxrlxxps```

### 输出

```
o x
-```

## 样例 #2

### 输入

```
forloops
fxrlxxp```

### 输出

```
o x
s```

## 样例 #3

### 输入

```
forloops
frlpz```

### 输出

```
s z
o```

# 题解

## 作者：superballll (赞：9)

# 题目分析

定义两个字符串，其中字符串 $a$ 为按下按键的字符串，字符串 $b$ 为电脑上显示的错误的字符串。然后梳理下这两个特殊的按键的特点：

- 愚蠢的按键：按下的字母不会出现，但是会出现一个没有按下过的字母。即按下的字母在字符串 $a$ 中出现了，但是在字符串 $b$ 中没有出现过。并且，显示的字母在字符串 $b$ 中出现了，但是在字符串 $a$ 中没有出现过。
- 安静的按键：按下的字母不会出现，而且也不会出现其他的字母。即在字符串 $a$ 中出现了，但是在字符串 $b$ 中没有出现过。

那么，我们可以通过字母在两个字符串中出现次数的不同来找到突破口。

定义两个数组，其中 $sa[0] \sim sa[25]$ 和 $sb[0] \sim sb[25]$ 分别表示 $26$ 个小写字母分别在 $a$ 串和 $b$ 串中出现的次数。由于可能会按下过安静的按键，因此两个字符串的串长可能不同，用 $lena$ 和 $lenb$ 表示两串串长，那么一定满足 $lena \ge lenb$。所以在计数的时候稍微注意一下就可以了，程序如下：
```
for(int i=0;i<lena;i++){
	sa[a[i]-'a']++;
	if(i<lenb) sb[b[i]-'a']++;
}
```
在刚才的分析中，我们会发现：如果某个字母在 $a$ 串中没有出现，但是在 $b$ 串中出现了，那一定是愚蠢的按键在按下时显示的错误字母。但是，在 $a$ 串中出现，在 $b$ 串中没有出现的字母，可能是愚蠢的按键也可能是安静的按键（仅当 $lena >lenb$ 时），那么我们除了要记录这两个字母，还需要再确定一下具体谁是谁。

再次对两个字符串进行枚举，当遇到 $a[i]$ 和 $b[i]$ 不同时，判断一下此时的 $b[i]$ 是不是前面我们已经获取到的**错误字母**：如果是，由于题目中说**两个特殊按键不会连续按下**，就是说不会有先按安静键再按愚蠢键的这种情况，那么 $a[i]$ 就是愚蠢的按键键入时的字母了；如果不是，那么 $a[i]$ 就是安静的按键了！

# 代码
```
#include<bits/stdc++.h>
using namespace std;

string a,b;
int lena,lenb;
int sa[30],sb[30];
char yc1='$',yc2,aj='-';

int main()
{
	cin>>a>>b;
	lena=a.length();
	lenb=b.length();
	for(int i=0;i<lena;i++)
	{
		sa[a[i]-'a']++;
		if(i<lenb) sb[b[i]-'a']++;
	}
	
	for(int i=0;i<=25;i++)
	{
		if(sa[i]==0&&sb[i]!=0) yc2=(char)('a'+i); //a中未出现 b中出现了 一定是错误的那个 
		if(sa[i]!=0&&sb[i]==0) //不能确定是愚蠢的还是安静的
		{  
			if(yc1=='$') yc1=(char)('a'+i); 
			else aj=(char)('a'+i);
		}
	}
	
	if(lena!=lenb){ //按下过安静键 
		for(int i=0;i<lena;i++)
		{
			if(a[i]!=b[i])
			{
				if(b[i]==yc2&&a[i]==aj||b[i]!=yc2&&a[i]==yc1) //记录反了的情况
					swap(yc1,aj);
				break;
			}
		} 
	} 
	
	cout<<yc1<<" "<<yc2<<endl;
	cout<<aj;
	return 0;
} 
```

---

## 作者：TruchyR (赞：4)

尝试一种比较暴力的方法：枚举错误的按键和安静的按键，然后模拟按下按键的过程，有以下限制：  

- 两种按键不能是同一个。  
- 两种按键不能交替按下。  
- 如果是正常按键需要与输出相符合。  
- 如果是错误按键，看它对应的按键数量，如果有多个就不行。  
- 如果是安静按键直接跳过，最后记得检查长度。

一个只是看起来会超时的代码过了这道题。  

```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
#define MX 500005
using namespace std;
const int CHECK=0,FIL=0;
int n,m,F,id,lst,mst,cnt,a[MX],b[MX],c[26];string A,B;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>A>>B;n=A.size();m=B.size();
	for(int i=1;i<=n;i++) a[i]=A[i-1]-'a';
	for(int i=1;i<=m;i++) b[i]=B[i-1]-'a';
	for(int i=0;i<26;i++){
	for(int j=0;j<26;j++){
		if(i==j) continue;
		lst=0,F=1,cnt=0,id=1;
		for(int k=0;k<26;k++) c[k]=0;
		for(int k=1;k<=n;k++){
			int w=a[k];
			mst=(w==i?1:(w==j?2:0));
			if(mst+lst==3){F=0;break;}
			if(mst==1){
				if(!c[b[id]]) cnt++,c[b[id]]++;
				if(cnt>1){F=0;break;}
				id++;
			}else if(!mst){
				if(b[id]!=w){F=0;break;}
				id++;
			}
			lst=mst;
		}
		if(id!=m+1 || !F || !cnt) continue;
		cout<<char(i+'a')<<' ';
		for(int k=0;k<26;k++) if(c[k]) cout<<char(k+'a')<<'\n';
		if(n==m) cout<<'-';
		else cout<<char(j+'a'); 
		return 0;
	}}
	return 0;
}


```

---

## 作者：__Sky__Dream__ (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/P10293)

## 解题思路
这道题就是统计字母出现的次数，基于次数来进行判断。

分析：

定义 $ch1$ 是输入的，$ch2$ 是屏幕上显示的。

如果是普通按键，那么在 $ch1$ 和 $ch2$ 所统计的个数是相同的。如果是“愚蠢的按键”，那么按键对应的字母就会在 $ch1$ 中比在 $ch2$ 中多，而它显示错误的字母就会比 $ch2$ 少，这样我们可以快速的找到错误字母，并且知道按下了多少个“愚蠢的按键”。如果是“安静的按键”，那么按键对应的字母也是要在 $ch1$ 中比在 $ch2$ 中多，这样我们可以找到“安静的按键”。

由于按下“安静的按键”和按下“愚蠢的按键”的次数是**可能相同的**，所以我们要**遍历两次**。

## AC Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[150],y[150],l;
char ch1,ch2,ch='-';
string a,b;
int main()
{
    cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>a>>b;
	for(int i=0;i<a.length();i++) x[a[i]]++;
	for(int i=0;i<b.length();i++) y[b[i]]++;
	for(int i=90;i<150;i++)
	{
		if(x[i]<y[i])
		{
			ch2=(char)i;
			l=y[i]-x[i];
			break;
		}
	}
	for(int i=90;i<150;i++)
	{
		if(x[i]-y[i]==l&&y[i]==0)
		{
			ch1=(char)i;
			break;
		}
	}
	for(int i=90;i<150;i++)
	{
		if(x[i]>y[i]&&y[i]==0&&i!=ch1)
		{
			ch=(char)i;
			break;
		}
	}
	string m;
	for(int i=0;i<a.length();i++)
	{
		if(a[i]==ch1) m+=ch2;
		else if(a[i]==ch) continue;
		else m+=a[i];
	}
	if(m==b)
	{
		cout<<ch1<<' '<<ch2<<"\n";
		cout<<ch;
		return 0;
	}
	for(int i=149;i>90;i--)
	{
		if(x[i]-y[i]==l&&y[i]==0)
		{
			ch1=(char)i;
			break;
		}
	}
	for(int i=149;i>90;i--)
	{
		if(x[i]>y[i]&&y[i]==0&&i!=ch1)
		{
			ch=(char)i;
			break;
		}
	}
	string n;
	for(int i=0;i<a.length();i++)
	{
		if(a[i]==ch1) n+=ch2;
		else if(a[i]==ch) continue;
		else n+=a[i];
	}
	if(n==b)
	{
		cout<<ch1<<' '<<ch2<<"\n";
		cout<<ch;
		return 0;
	}
    return 0;
}
```
[我的( ^_^ )记录](https://www.luogu.com.cn/record/153325942)，感谢大家！

---

## 作者：Wilderness_ (赞：0)

一道需要思维的字符串题。

## 思路
原来打算先遍历找到第一个出现偏差的点再从这个点开始向后找来判定是静音还是愚蠢键，结果写得更狗屎一样。

后来想到先用桶计每个字符出现数，然后通过次数的差来判断是静音还是愚蠢键。

比如输进来的第一行按键为正常的按键顺序，记为 $key_1$，而 $key_2$ 则是显示出来的。一个按键的情况有以下几种：

1. 如果一个按键是正常按键，那么它在 $key_1$ 和 $key_2$ 中出现的次数应是相同的；
2. 如果一个按键是愚蠢的按键或静音的按键，那么它在 $key_1$ 出现的次数显然会比在 $key_2$ 中出现的次数多；
3. 如果一个按键是错误的按键，那么它在 $key_1$ 出现的次数显然会比在 $key_2$ 中出现的次数少；

至此，我们可以判别出错误的按键，但是我们还需要判别愚蠢的按键和静音的按键（因为按愚蠢的按键和静音的按键次数可能是相同的）。所以我们可以现设第一次出现的两次显示按键出现次数不相等的按键为愚蠢的按键，第二个则为静音的按键，然后按照题意模拟一遍，判断是否与 $key_2$ 相同。如果不同就将之前找到的愚蠢的按键和静音的按键互换即可。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
char fool_key,error_key,quiet_key='-';
int buk_1[114514],buk_2[114514],del;
string key_1,key_2,tmp;
int main()
{
    cin>>key_1>>key_2;
    for(int i=0;i<key_1.length();++i)++buk_1[key_1[i]];
    for(int i=0;i<key_2.length();++i)++buk_2[key_2[i]];
    for(int i=97;i<=127;++i)
        if(buk_2[i]>buk_1[i]){error_key=(char)i;del=buk_2[i]-buk_1[i];break;}
    for(int i=97;i<=127;++i)
        if(buk_1[i]-buk_2[i]==del&&!buk_2[i]){fool_key=(char)i;break;}
    for(int i=97;i<=127;++i)
        if(buk_2[i]<buk_1[i]&&!buk_2[i]&&i!=fool_key){quiet_key=(char)i;break;}
    for(int i=0;i<key_1.length();++i)
	{
        if(key_1[i]==fool_key)tmp+=error_key;
        else if(key_1[i]==quiet_key)continue;
        else tmp+=key_1[i];
    }
    if(tmp!=key_2)swap(fool_key,quiet_key);
	printf("%c %c\n%c",fool_key,error_key,quiet_key);
    return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

设按下的 $N$ 个按键构成字符串为 $s1$，屏幕上显示的字符串为 $s2$。

本题枚举安静的按键，设为 $ch$，之后在 $s1$ 中删去 $ch$，得 $s3$。

若 $s2$ 长度与 $s3$ 的不一样，则跳过这个 $ch$。

在 $s3$ 中每一个字符与 $s2$ 中对应的字符，找出不一样的，第一次找到将它设为愚蠢的按键 $f1$，打出字符 $f2$。之后每一次找到判断愚蠢的按键是否为按下 $f1$ 得 $f2$，若不是，也跳过。

若 $ch$ 可得唯一的愚蠢的按键，则判 $s1$ 长度与 $s2$ 的长度，相同则将安静的字符设为 `-`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace dIn0 {
	string s1,s2,s3;
	char f1,f2,q;
	inline void _() {
		cin>>s1>>s2;
		for(char ch='a'; ch<='z'; ++ch) {
zyt:
			s3="";
			for(int i=0; i<s1.size(); ++i)if(s1[i]!=ch)s3+=s1[i];
			int sz=s3.size();
			if(sz!=s2.size())continue;
			f1=' ',f2=' ';
			for(int i=0; i<sz; ++i)
             if(s3[i]!=s2[i]) {
					if(f1==' ')f1=s3[i],f2=s2[i];
					else if(s3[i]!=f1||s2[i]!=f2) {
						++ch;
						goto zyt;
					}
				}
			if(f1==' ')continue;
			if(s1.size()==s2.size())q='-';
			else q=ch;
			cout<<f1<<' '<<f2<<'\n'<<q;
			break;
		}
	}
}
signed main() {
	dIn0::_();
}
```

---

