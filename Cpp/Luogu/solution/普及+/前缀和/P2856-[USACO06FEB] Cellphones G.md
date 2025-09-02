# [USACO06FEB] Cellphones G

## 题目描述

The cows have started using cellphones to cowmunicate with each other, but have found that the button layout doesn't suit their hooves very well. They are designing a special cellphone with fewer but larger buttons.


One feature they liked on the standard cellphones was predictive text. Each button has a few letters associated with it, and one types a word by pushing the associated buttons. Because there is more than one letter for each button, this can be ambiguous for some words.  However, most of the time the ambiguity can be resolved by using a dictionary to determine what word the user wanted.


Since the cows are designing a custom cellphone, they are also going to replace the English alphabet with the Cow alphabet. By an amazing coincidence, the cow alphabet is simply the first L (1 <= L <= 26) letters of the English alphabet, in the same order. They want to find out how to assign the letters of the Cow alphabet to the B buttons (1 <= B <= L) in such a way that the maximum number of words in their dictionary are unambiguous when entered with predictive text. Like normal cellphones, they want the letters on each button to be a contiguous section (one or more consecutive letters) of the alphabet.

奶牛的名字都是由英文字母表的前1(1 < K 26)个字母构成的.现在想设计一种手机， 有个按键.请你把这L个字母按顺序分配给B个按键，使能够通过按这些键而唯一确 定的奶牛数尽量多.


## 说明/提示

Explanation of the sample:




Button 1 contains AB, button two contains C-K, and button 3 contains LM. The words CELL, DILL, FILL and FILM are all entered as 2233, while the remaining 7 words are all entered uniquely.


## 样例 #1

### 输入

```
3 13
11
ALL
BALL
BELL
CALK
CALL
CELL
DILL
FILL
FILM
ILL
MILK```

### 输出

```
7
AB
CDEFGHIJK
LM```

# 题解

## 作者：HPXXZYY (赞：9)

**【题目翻译】：** 奶牛的名字都是由英文字母表的前$L(1 \leq L \leq 26)$个字母构成的（全部为**大写字母**且长度$\leq 10$）。现在奶牛们想设计一种手机， 有$B$个按键。请你把这$L$个字母**按顺序**分配给$B$个按键，使能够通过按这些键而唯一确定的奶牛数尽量多。求最多可以唯一确定多少头奶牛，输出方案。如果有多种方案，输出编号小的按键容纳字母最多的方案。

**【思路】：** 暴力枚举每个字母分配给哪个按键。记$ch[i]$表示字母$i$分配给按键$ch[i]$。不难发现，$ch$可以用**搜索**算法得出。

假设我们已经得到了$ch[i]$，考虑如何计算可以唯一确定多少头奶牛的名字。

依题意，每头奶牛的名字长度$\leq 10$，我们可以视整个字符串为一个$B+1$进制的数，这样就可以判断每个字符串的`hash值`。得到`hash值`后，我们就可以判断每个字符串是否只出现一次了。

**【注意】：** 数据的开头有一个没有用的整数，必须把它输入但忽略掉。

**【代码】：**
```cpp
int L,B,ans,ch[30],CH[30];
string str[1010];int n;
long long num[1010];
void updata_answer(){
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++)
		for(int j=0;j<str[i].size();j++)
			num[i]=num[i]*(B+1)+ch[str[i][j]-'A'+1];//计算hash值
	sort(num+1,num+n+1);
	register int tot=0;
	for(int i=1;i<=n;i++)
		if (num[i]!=num[i-1]&&num[i]!=num[i+1]) tot++;//计算有多少个不同的字符串
	if (tot>=ans){//注意这样才保证了答案字典序最小
		ans=tot;
		memcpy(CH,ch,sizeof(ch));
	}
}
void dfs(int sub,int color){
	if (sub>L){
		if (color>=B)
			updata_answer();
		return;
	}
	if (sub>1&&color<B){
		ch[sub]=color+1;
		dfs(sub+1,color+1);
	}
	if (color+L-sub>=B){
		ch[sub]=color;
		dfs(sub+1,color);
	}
	ch[sub]=-1;
}
int test_number;
int main(){
	cin>>test_number;test_number=1;//忽略掉这个无用的数字
	while (test_number--){
		memset(ch,-1,sizeof(ch));
		cin>>B>>L>>n;
		for(int i=1;i<=n;i++)
			cin>>str[i];
		dfs(1,1);CH[0]=CH[1]-1;
		printf("%d",ans);
		for(int i=1;i<=L;i++)
			if (CH[i]!=CH[i-1])
				printf("\n%c",(char)(i+'A'-1));
			else printf("%c",(char)(i+'A'-1));
		printf("\n");
	}
	return 0;
}
```

---

