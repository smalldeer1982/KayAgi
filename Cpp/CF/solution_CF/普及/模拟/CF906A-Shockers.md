# Shockers

## 题目描述

​	Valentin 参加了一个名为 “Shockers” 的节目。节目规则非常简单：评委会选择一个 Valentin 不知道的字母。他需要做一个小演讲，但每当他说出包含选定字母的单词时，他就会受到一次电击。他可以猜测选定的字母是哪一个，但是每猜错一次他也会受到一次电击。当 Valentin 成功猜出选定的字母时，节目结束。Valentin 无法记住所有的事情，所以他可能在选定字母已经能被确定之后很久才猜出选定字母，并因此遭受多余的电击。多余的电击是指 Valentin 在选定字母可以明确被猜出之后所遭受的电击。你需要求出多余电击的次数。

## 样例 #1

### 输入

```
5
! abc
. ad
. b
! cd
? c
```

### 输出

```
1
```

## 样例 #2

### 输入

```
8
! hello
! codeforces
? c
. o
? d
? h
. l
? e
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
! ababahalamaha
? a
? b
? a
? b
? a
? h
```

### 输出

```
0
```

# 题解

## 作者：DarkShadow (赞：6)

# CF906A（模拟）
## 题目大意：

给出 $N$ 个猜字母的操作，`!` 表示单词中含有正确字母，`.` 表示单词中不含正确字母，`?` 表示一次猜字母，保证最后一次猜字母猜对了。

## 思路分析：

可以开一个数组 $A$ 记录每一个字母是否可能是答案，其中 $A_i=1$ 表示该字母可能是答案且答案一定在所有 $A_i=1$ 中，$A_i=-1$ 表示该字母不可能是答案。

## 详细解法：

每次读入操作后分情况讨论，`!` 时把数组中当前单词的所有字母设为 $1$，将其他字母全部设为 $-1$；`.` 时把数组中当前单词所有字母设为 $-1$，`?` 且不是最后一此操作则将当前字母设为 $-1$。

如果当前数组中 $1$ 只有一个或 $-1$ 有 $25$ 个，说明当前已经可以确定答案，后面的操作如果是 `!` 或是 `?` 就统计答案。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,d[27],len,ans,cnt1,cnt2,t;
char c,s[100005];
bool flag,vis[27];
int main(){
	scanf("%d",&n);
	n--;
	while(n--){
		scanf("\n%c %s",&c,s+1);
		memset(vis,0,sizeof(vis));
		len=strlen(s+1);
		for(int i=1;i<=len;i++)
			vis[int(s[i])-'a']=1;
		if(flag&&(c=='!'||c=='?'))  ans++;
		if(c=='!')
			for(int i=0;i<26;i++){
				if(!vis[i])  d[i]=-1;
				if(vis[i]&&(d[i]==0||d[i]==1))  d[i]=1;
			}
		if(c=='.')
			for(int i=0;i<26;i++)
				if(vis[i])  d[i]=-1;
		if(c=='?')  d[s[1]-'a']=-1;
		cnt1=cnt2=0;
		for(int i=0;i<26;i++){
			if(d[i]==1)  cnt1++;
			if(d[i]==-1)  cnt2++;
		}
		if(cnt1==1||cnt2==25)  flag=1;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：arrow_king (赞：2)

## 1.题意

- `.` 表示不被电击，`!` 表示被电击，`?` 表示猜测、猜错了会被电击。
- $\texttt{Valentin}$ 发表的演讲中只有小写字母。
- $\texttt{Valentin}$ 在猜中后仍有可能被电击，称为过量电击。
- 求过量电击的次数。

## 2.思路

首先，因为演讲中只有小写字母，所以可以用 `bool` 数组 $f$ 来记录每个字母是否可能是答案，初始时 $f_i=1$。

如果整个 $f$ 数组中只有一个元素 $f_i$ 为 `true`，那么将 $flag$ 赋值为 $1$，$k$ 赋值为 $i$。

可以用字符变量 $opt$ 表示这个操作的类型（`.`，`!` 或 `?`）。

在处理每一条演讲时：

- 如果 $opt$ 为 `.`，那么答案一定不在这次演讲之中。

```cpp
if(opt=='.') {
    scanf("%s",s);
    int len=strlen(s);
    for(int j=0;j<len;j++) f[s[j]-'a'+1]=0;    //将此次演讲中每个字符的可能性设为0
}
```

- 如果 $opt$ 为 `!`，答案一定在此次演讲中，也就是除了此次演讲中的字符，其他字符都不可能为答案。同时，如果答案已找出，那么**此次电击就是过量电击**。

```cpp
if(opt=='!') {
    scanf("%s",s);
    if(flag) {
        num++;    //num记录过量电击次数
        continue;
    }
    memset(f2,0,sizeof(f2));    //f2数组记录当前字母是否在演讲中出现
    int len=strlen(s);
    for(int j=0;j<len;j++) f2[s[j]-'a'+1]=1;
    for(int j=1;j<=26;j++) if(!f2[j]) f[j]=0;    //如果没有出现，[j]=0
    continue;
}
```

- 如果 $opt$ 为 `?`，此次猜测没有找到正确答案（因为只有最后一次猜测才猜到了正确答案），所以这次猜测会受到电击。如果 $flag=1$，即找到了正确答案后，那么**这次猜测也是过量电击**。

```cpp
if(opt=='?') {
    cin>>tmp;
    f[tmp-'a'+1]=0;
    if(!flag) continue;    //如果没找到，就跳过
    num++;
    continue;
}
```

因为最后一次一定是找到答案的询问，所以最后一次可以忽略。最后直接输出 $num$ 就可以了。

**这里贴上完整代码：**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char opt,s[100005],tmp;
bool f[27],f2[27],flag=0;
int n,num=0,k;
bool pd() {    //判断是否已找到正确答案
	int num=0;
	for(int i=1;i<=26;i++) if(f[i]) num++,k=i;
	if(num>1) {
		k=0;
		return 0;
	}
	return 1;
}
int main() {
	memset(f,1,sizeof(f));
	scanf("%d",&n);
	for(int i=1;i<n;i++) {
		if(!flag) if(pd()) flag=1;
		cin>>opt;    //这里和下面输入tmp一样，必须用cin，不然一个输入\n，一个输入空格
		if(opt=='.') {
			scanf("%s",s);
			int len=strlen(s);
			for(int j=0;j<len;j++) f[s[j]-'a'+1]=0;
			continue;
		}
		if(opt=='!') {
			scanf("%s",s);
			if(flag) {
				num++;
				continue;
			}
			memset(f2,0,sizeof(f2));
			int len=strlen(s);
			for(int j=0;j<len;j++) f2[s[j]-'a'+1]=1;
			for(int j=1;j<=26;j++) if(!f2[j]) f[j]=0;
			continue;
		}
		if(opt=='?') {
			cin>>tmp;
			f[tmp-'a'+1]=0;
			if(!flag) continue;
			num++;
			continue;
		}
	}
	printf("%d\n",num);
	return 0;
}
```

---

## 作者：Fuxh_18 (赞：1)

看好了，这道题就是一道模拟题。

## 题意
有 $n$ 此猜字母操作，`.` 为不含所选字母，`!` 为含所选字母（会被电击），`?` 为询问一个字母是否为所选字母（猜错会被电击）。问有几次电击是多余的。

## 思路
我们可以用数组 $t$ 储存一个字母是否可能为所选字母。

我们可以分成三种情况：

- 当操作为 `.` 时，字符串中的所有字母都不可能。

- 当操作为 `!` 时，其他的所有字母都不可能。并且，若答案已经可以求出，本次操作为多余电击，更新答案。

- 当操作为 `?` 时，根据题意，只要不是最后一个操作，此字母不可能。并且，若答案已经可以求出，本次操作为多余电击，更新答案。

为了使代码更简单，我们可以不用判断最后一个操作（最后一个是 `?` 且保证正确）。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[26],ans;
int ts[26]; //在 ! 操作中暂时存储字符串中有的字母
int f; //用来记录是否已经找到所求字母
int check(){ //判断是否可找出所求字母
	int sum=0;
	for(int i=0;i<26;i++){
		if(t[i]) sum++;
	}
	if(sum>1) return 0;
	return 1;
}
int main(){
	cin>>n;
	for(int i=0;i<26;i++){ //初始化
		t[i]=1;
	}
	for(int k=1;k<n;k++){
		if(!f) f=check();
		char opt;
		string s;
		cin>>opt>>s;
		int len=s.size();
		if(opt=='.'){
			for(int i=0;i<len;i++){
				t[s[i]-'a']=0;
			}
		}
		if(opt=='!'){
			if(f){
				ans++;
				continue;
			}
			for(int i=0;i<len;i++){
				ts[s[i]-'a']=1;
			}
			for(int i=0;i<26;i++){
				if(!ts[i]) {
					t[i]=0;
				}
			}
			memset(ts,0,sizeof ts);
		}
		if(opt=='?'){
			t[s[0]-'a']=0;
			if(f) ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

看懂了，就快去做题吧。

---

## 作者：sxq9 (赞：1)

# 思路

## 排除

如果没被电击，就说明句子中没有那个字母，所以我们就可以排除掉句子中所有的字母。
```cpp
if(fuhao=='.'){
	cin>>hua;
	for(int j=0;j<=25;j++){
		if(hua.find(j+'a'<=hua.length())keneng[j+1]=1;
	}
}
```
因为除了最后一次外，所有的猜测都是错的，所以每次猜测的字母都可以排除。
```cpp
else{
	char cai;
	cin>>cai;
	keneng[cai-'a'+1]=1;
}
```
如果说话时被电击了，那么这个句子中没有的字母就不可能是那个字母了。
```cpp
else if(fuhao=='!'){
	cin>>hua;
	for(int j=0;j<=25;j++){
		if(hua.find(j+'a')>hua.length())keneng[j+1]=1;
	}
}
```

## 题意

如果在已经可以猜到是哪个字母的时候被电击，那么这次电击就叫做“过量电击”，最后要输出过量电击的次数。
```cpp
if(flag&&(fuhao=='!'||fuhao=='?')){
	cin>>hua;s++;continue;
}
```

# 完整代码
```cpp
#include<bits/stdc++.h>
//#define int unsigned long long
using namespace std;
int keneng[30],flag=0;//0为可能，1为不可能
void pd(){//判断是否可以猜到
	int s=0;
	for(int i=1;i<=26;i++){
		if(keneng[i]==0)s++;
	}
	if(s==1)flag=1;
} 
int main(){
	char fuhao;
	int n,s=0;
	cin>>n;
	string hua="";
	for(int i=1;i<n;i++){//最后一次不管
		cin>>fuhao;
		if(flag&&(fuhao=='!'||fuhao=='?')){
			cin>>hua;s++;continue;
		}
		if(fuhao=='.'){
			cin>>hua;
			for(int j=0;j<=25;j++){
				if(hua.find(j+'a')<=hua.length())keneng[j+1]=1;
			}
		}
		else if(fuhao=='!'){
			cin>>hua;
			for(int j=0;j<=25;j++){
				if(hua.find(j+'a')>hua.length())keneng[j+1]=1;
			}
		}
		else{
			char cai;
			cin>>cai;
			keneng[cai-'a'+1]=1;
		}
		pd();
	}
	cout<<s;
	return 0;
}

```

---

## 作者：H2O_TX (赞：0)

## 一、题意

猜一个字母。

每念出一段字母，如果其中有这个字母的话，会被电击，否则不会。

也可以选择问答案是否是某一个字母，猜错了被电击，猜对游戏结束。

给出一段游戏情况，但是如果在可以确定答案之后还被电击了，就是“过量电击”。

求过量电击的次数。

## 二、题解

基本就是模拟。

用一个数组 $vis[]$ 记录一个字母是否被排除，用一个变量 $sum$ 表示还剩几个字母可能是正确答案。

分类讨论：

- 念出一段字母后被电击了：

	这段里没有出现的字母都不可能是正确答案。
- 念出一段字母后没有被电击：

	这段里出现的字母都不可能是正确答案。
- 询问某个字母

	除了最后一次询问，这个字母不可能是正确答案。

当一个字母的 $vis$ 被第一次更新为 $1$ 时使 $sum$ 减少 $1$。

很明显当 $sum=1$ 时就已经确定答案了，这之后被电击了就是过量电击。

贴代码（附有注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int vis[30],sum=26;//一开始所有字母都没被排除

int main()
{
    cin>>n;
    int f=0,ans=0;
    int t[30];
    n--;//直接忽略最后一次询问
    while(n--)
    {
        char op;
        cin>>op;
        string s;
        cin>>s;
        if(op=='.')
        {
            if(sum==1) continue;
            for(int i=0;i<s.size();i++)
                if(!vis[s[i]-'a'])//第一次更新
                {
                    vis[s[i]-'a']=1;
                    sum--;
                    if(sum==1) break;
                }
        }
        if(op=='!')
        {
            if(sum==1)//在确定答案后被电击，属于过量电击
            {
                ans++;
                continue;
            }
            memset(t,0,sizeof t);
            for(int i=0;i<s.size();i++) t[s[i]-'a']=1;//记录本次说了的字母
            for(int i=0;i<26;i++)
                if(!t[i]&&!vis[i])//排除本次没说的字母
                {
                    vis[i]=1;
                    sum--;
                    if(sum==1) break;
                }
        }
        if(op=='?')
        {
            if(sum==1) ans++;
            else if(!vis[s[0]-'a'])
            {
                vis[s[0]-'a']=1;
                sum--;
            }
        }
    }
    cout<<ans;
    return 0;
}

```


---

## 作者：Raymondzll (赞：0)

## CF906A Shockers

### 解题思路

首先你需要根据这些 Valentin 提出的问题最快找到那个字母。

先提一句，最后一句肯定是回答正确的问号，不要理它。

设一个 ```maybe[27]``` 数组，一开始全部赋值为 $1$。

如果是感叹号，那么关键字母一定在这个单词里。

记录每个字母有没有在这个单词里出现过，放在 ```exist[27]``` 里。

然后，根据逻辑，```maybe[i]&=exist[i]``` 就行了。

如果是点，那么关键字母一定**不**在这个单词里。

同样处理 ```exist``` 数组，```maybe[i]&=!exist[i]```。

如果是问号而且不是最后一条指令，那么这个被问的字符 ```maybe``` 设为 $0$。

当你发现整个 ```maybe``` 数组只有一个值为 $1$ 之后，每个感叹号和问号（最后一个除外）都答案加一就行了。

### 代码部分

```
#include <bits/stdc++.h>
using namespace std;
int n;
int maybe[30];
int exist[30];
int c(char ch){return ch-'a'+1;}
bool flag;//答案已经出现
int ans;
int main(){
	cin>>n;
	for(int i=1;i<=26;i++)maybe[i]=1;
	for(int i=1;i<=n;i++){
		char el;string word;
		cin>>el>>word;
		if(i==n)break;
		memset(exist,0,sizeof(exist));//记得清空
		for(int j=0;j<word.size();j++){
			exist[c(word[j])]=1;
		}
		if(el=='!'){
			if(flag)ans++;
			for(int j=1;j<=26;j++)maybe[j]&=exist[j];
		}else if(el=='?'){
			if(flag)ans++;
			maybe[c(word[0])]=0;
		}else if(el=='.'){
			for(int j=1;j<=26;j++)maybe[j]&=(!exist[j]);
		}
		int cnt=0;
		for(int j=1;j<=26;j++)cnt+=maybe[j];
		if(cnt==1)flag=1;
	}
	cout<<ans;
	return 0;
}
```

---

