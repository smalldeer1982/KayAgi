# DNA Translation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=321

[PDF](https://uva.onlinejudge.org/external/3/p385.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA385/e93f18e2850196cc7c32643963e208aa23d116a5.png)

## 样例 #1

### 输入

```
ATACTCGTAATTCACTCC
CACCTGTACACAGAGGTAACTTAG
TTAATACGACATAATTAT
GCCTTGATATGGAGAACTCATTAGATA
AAGTGTATGTTGAATTATATAAAACGGGCATGA
ATGATGATGGCTTGA
*```

### 输出

```
Ser-Ile-Lys
Cys-Leu-His
Ser-Tyr
*** No translatable DNA found ***
Leu-Asn-Tyr-Ile-Lys-Arg-Ala
Met-Met-Ala```

# 题解

## 作者：wanganze (赞：0)

### 背景
高中生物必修二：转录与翻译。
### 题意
给你一个 DNA 序列，可能是正串、反串，倒序、正序。求按照 DNA 转录生成的 mRNA 编码出的任意一个蛋白质。

三个核苷酸作为一个整体出现。AUG 作为起始密码子或甲硫氨酸，表中空的就是结束密码子（不考虑硒代半胱氨酸）。

![](https://cdn.luogu.com.cn/upload/image_hosting/k1metcyl.png)

上图是翻译的“密码子”表。
### 思路
简单小模拟。

这个表没有什么规律，三个一节，先打起来，见代码中 `init` 函数。

然后枚举 DNA 的类型，变为 mRNA，按照始末标志找到需要的 mRNA 段，三个三个翻译即可。
### 实现
有多组数据。
```cpp
#include<bits/stdc++.h>
using namespace std;
string err = "*** No translatable DNA found ***";
unordered_map<string,string> mp;
string rev(string s)
{
	for(int i = 0; i < s.size(); i ++)
		if(s[i] == 'A') s[i] = 'T';
		else if(s[i] == 'T') s[i] = 'A';
		else if(s[i] == 'C') s[i] = 'G';
		else s[i] = 'C';
	return s;
}
void init()
{
	mp["UUU"] = mp["UUC"] = "Phe",mp["UUA"] = mp["UUG"] = "Leu";
	mp["UCU"] = mp["UCC"] = mp["UCA"] = mp["UCG"] = "Ser";
	mp["UAU"] = mp["UAC"] = "Tyr";
	mp["UGU"] = mp["UGC"] = "Cys",mp["UGG"] = "Trp";
	mp["CUU"] = mp["CUC"] = mp["CUA"] = mp["CUG"] = "Leu";
	mp["CCU"] = mp["CCC"] = mp["CCA"] = mp["CCG"] = "Pro";
	mp["CAU"] = mp["CAC"] = "His",mp["CAA"] = mp["CAG"] = "Gln";
	mp["CGU"] = mp["CGC"] = mp["CGA"] = mp["CGG"] = "Arg";
	mp["AUU"] = mp["AUC"] = mp["AUA"] = "Ile",mp["AUG"] = "Met";
	mp["ACU"] = mp["ACC"] = mp["ACA"] = mp["ACG"] = "Thr";
	mp["AAU"] = mp["AAC"] = "Asn",mp["AAA"] = mp["AAG"] = "Lys";
	mp["AGU"] = mp["AGC"] = "Ser",mp["AGA"] = mp["AGG"] = "Arg";
	mp["GUU"] = mp["GUC"] = mp["GUA"] = mp["GUG"] = "Val";
	mp["GCU"] = mp["GCC"] = mp["GCA"] = mp["GCG"] = "Ala";
	mp["GAU"] = mp["GAC"] = "Asp",mp["GAA"] = mp["GAG"] = "Glu";
	mp["GGU"] = mp["GGC"] = mp["GGA"] = mp["GGG"] = "Gly";
}
string get(string s)
{
	for(int i = 0; i < s.size(); i ++)
		if(s[i] == 'T') s[i] = 'U';
	int st = s.find("AUG"),ed = -1;
	string res = "";
	if(st == -1) return err;
	for(int i = st + 6; i + 2 < s.size(); i += 3)
		if(!mp.count(s.substr(i,3)))
		{
			ed = i;
			break;
		}
	if(ed == -1) return err;
	for(int i = st + 3; i < ed; i += 3) res += mp[s.substr(i,3)] + (i + 3 == ed ? "" : "-"); 
	return res;
}
int main()
{
	string s;
	init();
	while(cin>>s,s != "*")
	{
		string t = get(s);
		if(t != err)
		{
			puts(t.c_str());
			continue;
		}
		t = get(rev(s));
		if(t != err)
		{
			puts(t.c_str());
			continue;
		}
		reverse(s.begin(),s.end());
		t = get(s);
		if(t != err)
		{
			puts(t.c_str());
			continue;
		}
		puts(get(rev(s)).c_str());
	}
	return 0;
}
```

---

## 作者：AFewSuns (赞：0)

### 题目大意

给定一个只包含 $\text{\{'A','C','G','T'\}}$ 的 (DNA) 字符串，有如下规则：

- 将 DNA 串中所有 $A$ 改成 $T$，$T$ 改成 $A$，$C$ 改成 $G$，$G$ 改成 $C$ 得到 DNA 反串。

- 将 DNA 反串中的 $T$ 改为 $U$ 得到 mRNA 串。

- mRNA 中的第一个 `AUG` 子串标志着翻译的开始，然后往后每三个字符翻译成对应的名称，直到出现结束标志 `UAA`，`UAG` 或 `UGA`。对应名称如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/v57bjbrf.png)

然后你需要把这些名称用连接字符 `-` 连起来。

读入的字符可能是 DNA 串、倒序 DNA 串、DNA 反串或倒序 DNA 反串，你只需要输出任意一个翻译后的名称。如果都没有，则输出 `*** No translatable DNA found ***`。

多组数据，以 `*` 结束。

### 题目分析

一个简单的模拟题，可能有一些细节。

假设我们已经拿到了一个 mRNA 串，我们需要找到它的开始位置和结束位置。

对于开始位置，直接从头到尾扫一遍，如果发现有 `AUG`，就记录一下这个位置并退出。

然后从开始位置每 3 个地往后找结束标志，找到就记录并退出。如果没有开始标志或结尾标志则直接判为无解。

对于起点和终点之间的串，也是每 3 个这样往后枚举，然后输出对应的名称。

回到一开始的输入，我们把 DNA 串、倒序 DNA 串、DNA 反串或倒序 DNA 反串都跑一遍结果，如果都无解就输出 `*** No translatable DNA found ***`。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,st,ed;
char s[330],ss[330];
bool work(){
	st=ed=0;
	for(int i=1;i<=n-2;i++){//寻找起始位置 
		if(s[i]=='A'&&s[i+1]=='U'&&s[i+2]=='G'){
			st=i;
			break;
		}
	}
	for(int i=st+3;i<=n-2;i+=3){//找结束标志 
		if((s[i]=='U'&&s[i+1]=='A'&&s[i+2]=='A')||(s[i]=='U'&&s[i+1]=='A'&&s[i+2]=='G')||(s[i]=='U'&&s[i+1]=='G'&&s[i+2]=='A')){
			ed=i;
			break;
		}
	}
	if(!st||!ed||(ed-st)%3||(st+3)==ed) return 0;//如果没找到或中间没有字符直接无解 
	for(int i=st+3;i<ed;i+=3){//暴力判断 
		if(s[i]=='U'){
			if(s[i+1]=='U'){
				if(s[i+2]=='U') printf("Phe");
				if(s[i+2]=='C') printf("Phe");
				if(s[i+2]=='A') printf("Leu");
				if(s[i+2]=='G') printf("Leu");
			}
			if(s[i+1]=='C') printf("Ser");
			if(s[i+1]=='A') printf("Tyr");
			if(s[i+1]=='G'){
				if(s[i+2]=='U') printf("Cys");
				if(s[i+2]=='C') printf("Cys");
				if(s[i+2]=='G') printf("Trp");
			}
		}
		if(s[i]=='C'){
			if(s[i+1]=='U') printf("Leu");
			if(s[i+1]=='C') printf("Pro");
			if(s[i+1]=='A'){
				if(s[i+2]=='U') printf("His");
				if(s[i+2]=='C') printf("His");
				if(s[i+2]=='A') printf("Gln");
				if(s[i+2]=='G') printf("Gln");
			}
			if(s[i+1]=='G') printf("Arg");
		}
		if(s[i]=='A'){
			if(s[i+1]=='U'){
				if(s[i+2]=='U') printf("Ile");
				if(s[i+2]=='C') printf("Ile");
				if(s[i+2]=='A') printf("Ile");
				if(s[i+2]=='G') printf("Met");
			}
			if(s[i+1]=='C') printf("Thr");
			if(s[i+1]=='A'){
				if(s[i+2]=='U') printf("Asn");
				if(s[i+2]=='C') printf("Asn");
				if(s[i+2]=='A') printf("Lys");
				if(s[i+2]=='G') printf("Lys");
			}
			if(s[i+1]=='G'){
				if(s[i+2]=='U') printf("Ser");
				if(s[i+2]=='C') printf("Ser");
				if(s[i+2]=='A') printf("Arg");
				if(s[i+2]=='G') printf("Arg");
			}
		}
		if(s[i]=='G'){
			if(s[i+1]=='U') printf("Val");
			if(s[i+1]=='C') printf("Ala");
			if(s[i+1]=='A'){
				if(s[i+2]=='U') printf("Asp");
				if(s[i+2]=='C') printf("Asp");
				if(s[i+2]=='A') printf("Glu");
				if(s[i+2]=='G') printf("Glu");
			}
			if(s[i+1]=='G') printf("Gly");
		}
		if((i+3)<ed) printf("-");
	}
	printf("\n");
	return 1;
}
int main(){
	while(~scanf("%s",s+1)){
		if(s[1]=='*') break;
		n=strlen(s+1);
		for(int i=1;i<=n;i++) if(s[i]=='T') s[i]='U';
		if(work()) continue;//原串的mRNA 
		for(int i=1;i<=n;i++) ss[i]=s[n-i+1];
		for(int i=1;i<=n;i++) s[i]=ss[i];
		if(work()) continue;//倒序串的mRNA 
		for(int i=1;i<=n;i++){
			if(s[i]=='A') s[i]='U';
			else if(s[i]=='C') s[i]='G';
			else if(s[i]=='G') s[i]='C';
			else s[i]='A';
		}
		if(work()) continue;//DNA反串的mRNA 
		for(int i=1;i<=n;i++) ss[i]=s[n-i+1];
		for(int i=1;i<=n;i++) s[i]=ss[i];
		if(work()) continue;//倒序DNA反串的mRNA 
		printf("*** No translatable DNA found ***\n");
	}
}
```

---

