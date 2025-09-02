# [COCI 2013/2014 #5]  EKSPLOZIJA

## 题目描述

给出一个字符串和一个目标字符串，在给出的字符串中找到所有的目标字符串并删除。

将剩下的小字符串按照原来的顺序拼接，再继续在剩下的字符串中持续这种操作，直到没有更多的目标字符串出现为止。

请打印出剩下的字符串。如果没有剩下的字符串，输出 `FRULA`。

## 说明/提示

**【样例解释 #1】**

第一次删除，原字符串变为 `mirkov**nizC**4` （`*` 表示被删除的字符），即 `mirkovnizC4`。

第二次删除，字符串变为 `mirkovniz**`，即 `mirkovniz`。

**【样例解释 #2】**

第一次删除，原字符串变为 `****1****2ab` （`*` 表示被删除的字符），即 `12ab`。

第二次删除，字符串变为 `****`。故输出 `FRULA`。

**【数据范围】**

对于 $50\%$ 的数据，$1\le $ 原字符串长度 $\le 3000$；

对于 $100\%$ 的数据，$1\le $ 原字符串长度 $\le 10^6$，$1\le $ 目标字符串长度 $\le 36$，所有字符串均由大写字母、小写字母和数字 $0,1...9$ 组成，保证目标字符串中没有重复的字符。

**【说明】**

本题分值按 COCI 原题设置，满分 $100$。

题目译自[COCI2013_2014](https://hsin.hr/coci/archive/2013_2014/) [CONTEST #5](https://hsin.hr/coci/archive/2013_2014/contest5_tasks.pdf) _**T3 EKSPLOZIJA**_

## 样例 #1

### 输入

```
mirkovC4nizCC44
C4 ```

### 输出

```
mirkovniz```

## 样例 #2

### 输入

```
12ab112ab2ab
12ab```

### 输出

```
FRULA```

# 题解

## 作者：CornWorld (赞：4)

Python 大法好!

众所周知，Python 自带正则库 （[re — Regular expression operations — Python 3.10.0 documentation](https://docs.python.org/3/library/re.html)），而且实测效率不错。

循环正则替换，~~那么这个题就能 6 行秒了~~

```python
import re
s = input().strip()
b = input().strip()
while b in s: s = re.sub(b, '', s)
if len(s) : print(s)
else : print("FRULA")
```


---

## 作者：pxb0801 (赞：3)

### 0.题目大意：

这道题题意已经十分简洁，我就不再过多赘述了。

--------------
### 1.思考过程：

首先看到数据范围，发现 $1≤$ 原字符串长度 $≤10^6$，我不禁倒吸一口凉气：暴力做不了了。

为什么不行呢？因为这题不仅仅是要求子串，关键是删完子串后还要合并，这个时间是 $O(n^2)$ 级别的。

看到这，你知道怎么做了吗？

哦，我听到有人说用栈。没错，这道题我就给大家用栈来做一做。

------------
### 2.分析：

首先我们需要一个 $st[]$ 数组，用于记录放入栈的字符；我们还需要一个 $w[]$ 数组，用于记录放入栈的字符是在子串中的位置，即第几个。

接下来我们开始从头遍历原字符串。如果我们发现此时遍历的字符既不是子串的第一个字符，也不是子串的 $w[top]+1$ 位，即没有连着前面的字符，则栈内元素全部输出，再输出当前字符。

如果满足当中任意一个条件，则放入栈中。如果发现此字符的位置已是子串的结尾字符，则直接将 $top$ 减掉。

最后，如果栈内还有字符，说明这些是最后未被删除的，也应输出。

### 3.正确代码

不要抄袭哦~

```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
char st[1000005];
int l1,l2,top,w[1000005];
int main(){
	ios::sync_with_stdio(false);
	cin>>s1>>s2;
	l1=s1.size();
	l2=s2.size();
	s2=" "+s2;
	bool ok=0;
	for(int i=0;i<l1;i++){
		if(s1[i]!=s2[w[top]+1]&&s1[i]!=s2[1]){
			for(int j=1;j<=top;j++){
				cout<<st[j];
			}
			top=0;
			cout<<s1[i];
			ok=1;
//			cout<<top<<" "<<s1[i]<<" "<<111111<<endl;
			continue;
		}
		st[++top]=s1[i];
		if(s1[i]!=s2[w[top-1]+1]){
			w[top]=1;
		}
		else{
			w[top]=w[top-1]+1;
		}
		if(w[top]==l2){
			top-=l2;
		}
//		cout<<top<<" "<<s1[i]<<endl;
	}
	for(int i=1;i<=top;i++){
		cout<<st[i];
		ok=1;
	}
	if(!ok) cout<<"FRULA";
    return 0;
}
```

### 4.写在后面：

本蒟蒻的第一篇题解，望过，谢谢！

---

## 作者：苏联小渣 (赞：3)

### 题目大意

在原字符串 $s$ 中不断删去目标字符串 $t$，求最终的字符串。

### 分析

发现题解都是暴力，来一波 KMP。双倍经验题：[P4824](https://www.luogu.com.cn/problem/P4824)

首先先预处理目标串 $t$ 的 $kmp$ 数组，其中 $kmp_j$ 表示匹配到 $t$ 的第 $j$ 个字母而第 $j+1$ 个不能匹配时，新的 $j$ 最大是多少。预处理代码如下：
```cpp
ls = strlen(s+1), lt = strlen(t+1);
for (int i=2, j=0; i<=lt; i++){
	while (j && t[j+1] != t[i]) j = kmp[j];
	if (t[j+1] == t[i]) j ++;
	kmp[i] = j;
}
```
接下来还是类似正常的 KMP，只不过需要加入**栈**操作（看到这种类似括号序列的就会想到栈）。当 KMP 匹配完成时，就让匹配的部分出栈。用 $f$ 数组记录应该去的最大位置，然后返回栈顶对应的 $f$ 值即可。代码如下：
```cpp
for (int i=1, j=0; i<=ls; i++){
	while (j && t[j+1] != s[i]) j = kmp[j];
	if (t[j+1] == s[i]) j ++;
	f[i] = j;
	zhan[++top] = i;
	if (j == lt){
		top -= lt;
		j = f[zhan[top]];
	}
}
```

如果栈无元素，即 $s$ 已被删完，否则输出栈内下标所对应的字符（即没被删去的字符）。输出代码：
```cpp
if (top <= 0) return puts ("FRULA"), 0;
for (int i=1; i<=top; i++){
	printf ("%c", s[zhan[i]]);
}
```

---

## 作者：cqbztz2 (赞：2)

 **这是一道模拟题**

 这道题并不是很难，只需要用数组模拟栈来存储字符串，一边寻找目标字符串一边删除，最后输出字符串就行了。

 **详解见代码:**

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  char s[1000005],target[1000005]; 
  char z[1000005];
  int tot,len1,len2;//分别为栈长度，s字符串长度 ，target字符串长度 
  bool flag;
  int main(){
      cin>>s+1;
      cin>>target+1;
      len1=strlen(s+1),len2=strlen(target+1);
      for(int i=1;i<=len1;i++){
          z[++tot]=s[i];//栈存字符串 
          if(tot>=len2&&z[tot]==target[len2]){
              flag=1;
              for(int j=1;j<=len2;j++){
                  if(z[tot-len2+j]!=target[j]){//是否为目标字符串 
                      flag=false;
                      break;
                  }
              }
              if(flag==true){//剪去目标字符串
                  tot-=len2;
              }	
          }
      }
      if(tot==0){//如果没有剩下的字符串，输出 FRULA
          cout<<"FRULA";
          return 0;
      }	
      for(int i=1;i<=tot;i++){//输出栈 
          cout<<z[i];
      }
      return 0;
  }
```


---

## 作者：Moyyer_suiy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7674)

## 题目简述
在给出的字符串 $s$ 中不断找寻目标字符串 $k$ 并删掉，直到删完求出最终字符串。
## 思路
采用比较基础的一个操作：栈+暴力。将给出字符串依次压入栈中，同时处理此时栈顶是否存在目标字符串，是则弹出这个串。

贴代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,k;
char stk[1000010];
int main(){
    cin>>s>>k;
    int len=-1,lenk=k.length();
    for(int i=0;i<(int)s.length();i++){
        stk[++len]=s[i];
        while(stk[len]==k[lenk-1]){
            int flag=1;
            for(int j=0;j<lenk;j++) if(stk[len-lenk+j+1]!=k[j]){flag=0;break;}//判断栈顶是否为目标字符串
            if(flag) len-=lenk;//弹出
            if(flag==0) break;//一定注意这里的结束循环！
        }
    }
    len++;
    if(len==0) cout<<"FRULA";
    else for(int i=0;i<len;i++) cout<<stk[i];
}
```
总而言之，本题是非常水的一道黄，但是本蒟蒻在做此题时因为 while 循环没处理好卡了很久。这告诫我们做题的时候一定要认真谨慎有始有终，起码要清楚的知道自己的代码做了什么、在做什么、要做什么。这是我从本题中学到的。

---

## 作者：tjer (赞：1)

# 思路
[题链](https://www.luogu.com.cn/problem/P7674)

看到题解都是些 KMP+栈 或 暴力+栈。

这里来一发 hash+栈。

选一个素数进制对当前位数的目标字符串进行 hash 处理。

然后将 hash 处理后的数存入一个长整型的数组里（ hash 处理后的数可能很大，所以用长整型）。

然后再用栈的方式将当前位数的原字符串进行同样 hash 处理后的结果存入另一个长整型数组。

如果当前位数的原字符串处理后的结果减去储存原字符串的 hash 栈中前目标字符串位数的 hash 值乘上目标字符串整个字符串的 hash 值的积与原字符串的最大进制相同，说明成功匹配了，然后调动栈顶指针，继续遍历直到遍历完原字符串每一位。
# code
```cpp
#include<bits/stdc++.h>
#define maxn 1000005
using namespace std;
typedef unsigned long long as;
as base=37,a[maxn]={1},ht,hs[maxn],tot,lens,lent;
char z[maxn],s[maxn],t[maxn];
int main () {
    scanf("%s%s",s+1,t+1);
    lens=strlen(s+1),lent=strlen(t+1);
    for(int i=1;i<=lent;i++){
        a[i]=a[i-1]*base;
        ht=ht*base+t[i];//ht记录原字符串到第 i 位时的进制
    }
    for(int i=1;i<=lens;i++){
        z[++tot]=s[i];
        hs[tot]=hs[tot-1]*base+s[i];//目标字符串使用数组因为
        //调动栈顶指针时，所对应的进制也要修改
        if(ht==hs[tot]-hs[tot-lent]*a[lent]) tot-=lent;
        //如上所述
    }
    if(tot==0){
        cout <<"FRULA";
        return 0;
        //消完了
    }
    for(int i=1;i<=tot;i++) 
        printf("%c",z[i]);//蕐骊的输出
    return 0;
}
```


---

## 作者：LJKX (赞：0)

### 思路

这道题比较简单，我们可以用 ```vector``` 来存储字符串，一直枚举寻找目标字符串并删除即可。

~~因为数据比较水，所以暴力也能过~~

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<char> a;
string b;int l1,l2;
bool pei(int op) {//从第op位枚举判断是否符合条件
    for(int i=op,j=0;j<l2;i++,j++)
    if(a[i]!=b[j])return 0;
    return 1;
}
int main() {
    cin>>b;l1=b.size();
    for(int i=0;i<l1;i++)a.push_back(b[i]);
    cin>>b;l2=b.size();
    for(int j=1;j<=30;j++) {//多次判断
        for(int i=0;i+l2<=a.size();i++) 
        if(pei(i)) a.erase(a.begin()+i,a.begin()+i+l2);//如果符合，删除此处
    }
    if(!a.size()) puts("FRULA");
    else for(int i=0;i<a.size();i++)putchar(a[i]);
    return 0;
}
```


---

## 作者：杨岛主杨东润 (赞：0)

# P7674 题解
### 题目解析：
就是让你在第一个字符串中删掉所有的第二个字符串。

### 具体解法：
这道题，我们先输入两个字符串 $s$,$b$。

接下来，我们用一个循环，分别一次次删掉，并减去对应的长度。

如果找不到了，直接break。

最后，我们输出便可以了，在这里要注意一点，如果最后是一个空串，要输出FRULA。

具体过程见代码

### 具体代码：
不要抄袭哦！
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
char s[1000006]; //要开的大一点 
char a[1000006],b[1000006];
int main(){
    int flag=2;//判定变量 
    int sum=0;//计数器 
    cin.operator(s+1)//这个东西会CE！请慎重使用。 
    cin.operator(b+1)
    int l1=strlen(s+1);//长度是多少 
    int l2=strlen(b+1);
    for(int i=1;i<=l1;i++){//循环减去字符串大小 
        sum++;//计数器++ 
        a[sum]=s[i];
        if(sum>=l2&&a[sum]==b[l2]){//尝试 
            flag=1;
            for(int j=1;j<=l2;j++){
                if(a[sum-l2+j]!=b[j]){//如果不可以 
                    flag=2;
                    break;//离开循环 
                }
            }
            if(flag==1){//如果成功去除 
                sum-=l2;//减去字符串的长度 
            }   
        }
    }
    if(sum==0){//如果是空串 
        cout<<"FRULA";//输出 
        return 0;
    }   
    for(int i=1;i<=sum;i++){//输出新的字符串 
        cout<<a[i];
    }
    return 0;//完美的结束 
}
```
谢谢观看！

---

## 作者：fls233666 (赞：0)

我们设 $len_1$ 为原字符串长度，$len_2$ 为目标字符串长度。

通过题目的样例解释，我们可以先得出一种简单暴力的做法：先把原字符串中每个目标字符串删掉，然后把剩下的字符串拼起来，再扫一遍字符串，删掉所有的目标字符串......如此循环，直到不能再删位置。

显然这个方法太暴力了，一定会超时的。实际上，**真的需要每次删完全部目标字符串后再重新拼接字符串吗？**

我们先简化一下问题：把原字符串设为只有 ```(``` 与 ```)```，把目标串变成 ```()```。简化后相信很多人就会做了：**这不就是括号匹配吗，压到栈里匹配就好了。时间复杂度是 $O(len_1)$ 的。**

那么我们做一步推广。我们把原字符串与目标字符串限制为只有两种字符，并令 $len_2=2$。那么不难得出一种与括号匹配类似的做法：把原串内每个字符依次入栈，设栈顶为 $top$，检查栈中 $top$ 与 $top-1$ 位置的字符是否能拼接成目标字符串，如果能就出栈。我们发现，**这个做法的时间复杂度仍然是 $O(len_1)$ 的。**

进一步，我们发现把字符种数的限制去掉，只保留 $len_2=2$ 的限制，做法也是大致相同的，时间复杂度也不变。

那么最后来考虑一般情况：$1 \le len_2 \le 36$ 怎么做。可以发现，解法还是把原字符串中的字符一个一个压到栈里面，然后每次从栈顶开始，取出 $len_2$ 个字符，看看能否按顺序拼成目标字符串。如果能，这 $len_2$ 个字符串就可以全部出栈了。这样，我们只要把原字符串扫一遍，就能完成全部的目标字符串的删除了。全部删完后，留下的字符就都在栈里面了。时间复杂度是 $O(len_1 \times len_2)$，可以接受。

把上面的思路转化成代码实现，你就得到了下面这份 AC 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 1e6+6;

string instr,delstr;
char ans[mxn];
int top,len,del_len;

int main(){
	cin>>instr>>delstr;
    //读入原字符串与目标字符串
    
	len=instr.size();  //原串长度
	del_len=delstr.size();  //目标字符串长度
    
	for(rgt j,j_top,i=0;i<len;i++){
		top++;
		ans[top]=instr[i];  //把字符放到栈里面
		if(top>=del_len){
			j_top=top;
			j=del_len-1;
			while(j>=0&&ans[j_top]==delstr[j]){
				j_top--;
				j--;
			}   //匹配并取出 del_len 个字符
			if(j<0)  //全部匹配成功
				top=j_top;  //这些字符出栈
		}
	}
    
	if(!top){   //栈空了，整个字符串被删完了
		putchar('F');
		putchar('R');
		putchar('U');
		putchar('L');
		putchar('A');
	}else{  //把栈里面剩的东西输出
		for(rgt i=1;i<=top;i++)
			putchar(ans[i]);
	}
	return 0;
}
```


---

