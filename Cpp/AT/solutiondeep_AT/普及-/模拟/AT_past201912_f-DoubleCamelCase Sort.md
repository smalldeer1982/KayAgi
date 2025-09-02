# 题目信息

# DoubleCamelCase Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/past201912-open/tasks/past201912_f

文字列 $ S $ が与えられる。これは、$ 1 $ つ以上の単語を (間に空白などを挟まずに) 連結したものである。ここで、各単語は $ 2 $ 文字以上であり、最初の文字と最後の文字のみが英大文字、それ以外の文字は全て英小文字である。

これらの単語を辞書順に並べ (大文字小文字の違いは無視する)、同様に連結して出力するプログラムを作成せよ。

例えば、$ S\ = $ `FisHDoGCaTAAAaAAbCAC` とする。これは `FisH`, `DoG`, `CaT`, `AA`, `AaA`, `AbC`, `AC` の $ 7 $ つの単語を連結したものである。これらを辞書順に並べると `AA`, `AaA`, `AbC`, `AC`, `CaT`, `DoG`, `FisH` となるため、`AAAaAAbCACCaTDoGFisH` と出力すればよい。

## 说明/提示

### 注意

この問題に対する言及は、2019年12月29日 05:00 JST まで禁止されています。言及がなされた場合、賠償が請求される可能性があります。

試験後に総合得点や認定級を公表するのは構いませんが、どの問題が解けたかなどの情報は発信しないようにお願いします。

### 制約

- $ S $ は長さ $ 2 $ 以上 $ 100,000 $ 以下の文字列である。
- $ S $ の各文字は英大文字または英小文字である。
- $ S $ は問題文で述べたような単語の連結である。

### Sample Explanation 1

問題文で用いた例である。

### Sample Explanation 2

同じ単語が複数個存在する可能性があることに注意せよ。

## 样例 #1

### 输入

```
FisHDoGCaTAAAaAAbCAC```

### 输出

```
AAAaAAbCACCaTDoGFisH```

## 样例 #2

### 输入

```
AAAAAjhfgaBCsahdfakGZsZGdEAA```

### 输出

```
AAAAAAAjhfgaBCsahdfakGGdEZsZ```

# AI分析结果

### 题目翻译
# 双驼峰排序

## 题目描述
[问题链接]: https://atcoder.jp/contests/past201912-open/tasks/past201912_f

给定一个字符串 $S$，它是由一个或多个单词（中间没有空格等）连接而成的。这里，每个单词长度至少为 2，且只有第一个字符和最后一个字符是大写英文字母，其余字符均为小写英文字母。

请编写一个程序，将这些单词按字典序（忽略大小写）排序，然后同样地连接起来并输出。

例如，设 $S$ = `FisHDoGCaTAAAaAAbCAC`，它是由 `FisH`、`DoG`、`CaT`、`AA`、`AaA`、`AbC`、`AC` 这 7 个单词连接而成的。将这些单词按字典序排序后得到 `AA`、`AaA`、`AbC`、`AC`、`CaT`、`DoG`、`FisH`，因此应输出 `AAAaAAbCACCaTDoGFisH`。

## 说明/提示
### 注意
在 2019 年 12 月 29 日 05:00 JST 之前，禁止对该问题进行提及。若有提及，可能会被要求赔偿。

考试结束后可以公布综合得分或认定等级，但请不要发布是否解出某道题等信息。

### 约束条件
- $S$ 是长度在 2 到 100000 之间的字符串。
- $S$ 中的每个字符都是大写或小写英文字母。
- $S$ 是如题目描述中那样的单词连接而成的。

### 示例解释 1
这是题目描述中使用的示例。

### 示例解释 2
请注意，可能存在多个相同的单词。

## 样例 #1
### 输入
```
FisHDoGCaTAAAaAAbCAC
```
### 输出
```
AAAaAAbCACCaTDoGFisH
```

## 样例 #2
### 输入
```
AAAAAjhfgaBCsahdfakGZsZGdEAA
```
### 输出
```
AAAAAAAjhfgaBCsahdfakGGdEZsZ
```

### 综合分析与结论
这些题解的整体思路都是先将输入字符串拆分成若干个单词，再对这些单词按字典序（忽略大小写）进行排序，最后将排序后的单词连接成一个新的字符串输出。

#### 思路与算法要点
- **单词拆分**：多数题解使用标记变量（如 `bool` 类型的标记或计数器）来判断单词的起始和结束位置，遇到大写字母时进行相应的状态切换和单词截取。
- **排序**：由于 `string` 的默认比较规则与题目要求不符，所以都需要自定义 `cmp` 函数，先比较字符（忽略大小写），再比较字符串长度。

#### 解决难点
- **大小写不敏感**：通过自定义函数将大写字母转换为小写字母，或者将字母映射到相同的范围进行比较。
- **排序规则**：自定义 `cmp` 函数来实现先按字符字典序、再按长度的排序规则。

### 通用建议与扩展思路
- 对于单词拆分部分，可以使用更简洁的逻辑来处理标记变量的状态转换。
- 在自定义 `cmp` 函数时，可以利用标准库中的 `tolower` 函数来简化大小写转换的操作。
- 同类型题或类似算法套路：对于字符串处理类问题，通常需要先对字符串进行拆分、提取关键信息，再根据题目要求进行排序、合并等操作。可以使用标记变量、双指针等方法来处理字符串的边界和状态。

### 推荐洛谷题目
1. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：涉及排序和去重操作。
2. [P1177 快速排序](https://www.luogu.com.cn/problem/P1177)：考察排序算法的实现。
3. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：需要对字符串进行统计和处理。

### 重点代码及核心实现思想
以下是几个题解的关键代码及核心思想：

#### qwertim 的题解
```cpp
#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
int tmp=-1,cnt;
string s,str[100005];
bool cmp(string a,string b){
    int k=min(a.size(),b.size())-1;
    fo(i,0,k)if(tolower(a[i])!=tolower(b[i]))return tolower(a[i])<tolower(b[i]);//均变成小写
    return a.size()<b.size();//判断长度
}
int main(){
    cin>>s;
    fo(i,0,s.size()-1){
        if(isupper(s[i])){//是否是大写字母
            if(tmp==-1)tmp=i;
            else str[++cnt]=s.substr(tmp,i-tmp+1),tmp=-1;//截取tmp~i
        }
    }
    sort(str+1,str+1+cnt,cmp);
    fo(i,1,cnt)cout<<str[i];
    return 0;
}
```
**核心思想**：使用 `tmp` 标记单词的起始位置，遇到大写字母时进行状态切换和单词截取，最后使用自定义的 `cmp` 函数进行排序。

#### G__G 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,a[100000];
int cnt=1;
int fl=0;
int fun(char c){
	if(c>='a'&&c<='z'){
		return (int)(c-'a'+1);
	}
	return (int)(c-'A'+1);
}
bool cmp(string x,string y){
	for(int i=0;i<min(x.size(),y.size());i++){
		if(fun(x[i])!=fun(y[i])){
			return fun(x[i])<fun(y[i]);
		}
	}
	return x.size()<y.size();
}
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		a[cnt]+=s[i];
		if(s[i]>='A'&&s[i]<='Z'){
			fl++;
			if(fl%2==0){
				cnt++;
			}
		}
	}
	sort(a+1,a+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		cout<<a[i];
	}
	return 0;
}
```
**核心思想**：使用计数器 `fl` 来判断单词的结束位置，将字符添加到对应的字符串中，最后使用自定义的 `cmp` 函数进行排序。

#### Convergent_Series 的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
struct word{int l=-1,r=-1;}a[100010]; 
string s;
bool cmp(word a,word b){
	int i;
	int lna=a.r-a.l+1,lnb=b.r-b.l+1;
	char ta,tb;
	for(i=0;i<lna&&i<lnb;i++){
		if(s[a.l+i]<='Z') ta=s[a.l+i]-'A'+'a';else ta=s[a.l+i];
		if(s[b.l+i]<='Z') tb=s[b.l+i]-'A'+'a';else tb=s[b.l+i];
		if(ta!=tb) return ta<tb;
	}
	return lna<lnb;
}
int ln,cnt=1;
int main(){
    cin>>s;
    ln=s.length();
    int i,j;
    for(i=0;i<ln;i++){
    	if(s[i]>='A'&&s[i]<='Z'){
    		if(a[cnt].l==-1) a[cnt].l=i;
    		else a[cnt].r=i,cnt++;
		}
	}
	sort(a+1,a+cnt,cmp);
    //for循环处理后cnt指向最后一个单词的下一个位置，所以不用加一
	for(i=1;i<cnt;i++){//注意是<而不是<=，理由同上。
		for(j=a[i].l;j<=a[i].r;j++) cout<<s[j];
	}
	cout<<"\n";
	return 0;
}
```
**核心思想**：使用结构体 `word` 存储每个单词的起始和结束位置，通过遍历字符串找到这些位置，最后根据自定义的 `cmp` 函数对结构体数组进行排序并输出。

---
处理用时：54.69秒