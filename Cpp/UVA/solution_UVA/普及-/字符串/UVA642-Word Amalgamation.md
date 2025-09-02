# Word Amalgamation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=583

[PDF](https://uva.onlinejudge.org/external/6/p642.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/798288cf0a5caae5367a31141c3cf2e90bd3b5cb.png)

## 样例 #1

### 输入

```
tarp
given
score
refund
only
trap
work
earn
course
pepper
part
XXXXXX
resco
nfudre
aptr
sett
oresuc
XXXXXX```

### 输出

```
score
******
refund
******
part
tarp
trap
******
NOT A VALID WORD
******
course
******```

# 题解

## 作者：_Qer (赞：1)

map吼啊！！！

用map来存每个单词（排序后）的出现次数和出现时的排列，好存又好用啊

```cpp
#include <bits/stdc++.h>
using namespace std;
string s, tmp;//输入的字符串
struct node {
    string word[1010];//不同的出现情况
    int giventime;//出现次数
};
map<string, node> dic;//搞一个map，以string为索引
int main() {
    while (cin >> s && s != "XXXXXX") {//while输入方便的不行
        tmp = s;//先暂存下来
        sort(s.begin(), s.end());//排好序
        dic[s].word[dic[s].giventime++] = tmp;//存进map
    }
    while (cin >> s && s != "XXXXXX") {
        sort(s.begin(), s.end());//先排序来找
        if (!dic[s].giventime) {//字典中没有出现的情况
            cout << "NOT A VALID WORD" << endl << "******" << endl;
            continue;
        }
        sort(dic[s].word, dic[s].word + dic[s].giventime);
        //要按照字典序输出
        for (int i = 0; i < dic[s].giventime; ++i) {//按顺序输出
            cout << dic[s].word[i] << endl;
        }
        cout << "******" << endl;
    }
    return 0;
}
```

----

注：

```cpp
	sort(s.begin(), s.end());
```
是把单个字符串按字典序排序（小字符在前）
```cpp
	sort(s, s + n);
```
是将一个字符串**数组**按字典序排序（每个字符串不变动）


---

## 作者：blsya23a2 (赞：0)

## 分析
首先把字典和需要解读的单词分别存储在列表里。然后用 `itertools.permutations()` 求需要解读的单词的全排列，如果与字典中的单词重合且没有出现过，就存储在另一个列表里。注意最后输出时**需要排序**（翻译里没写导致我因为这个卡了半个月）。
### 好用的函数
`itertools.permutations(str/list,n)`：求字符串或列表指定元素个数的全排列，返回值是包含了全排列的元组。
## 代码
```python
from itertools import permutations
a,b=[],[]
while 1:
    c=input()
    if 'X' not in c:
        a.append(c)
    else:
        break
while 1:
    d=input()
    if 'X' not in d:
        b.append(d)
    else:
        break
for e in b:
    h,i,j=0,[],[]
    for f in permutations(e,len(e)):
        n=''
        for o in f:
            n+=o
        if n in a and f not in i:
            h=1
            i.append(f)
            l=''
            for m in f:
                l+=m
            j.append(l)
    if h==0:
        print('NOT A VALID WORD')
    else:
        j.sort()
        for k in j:
            print(k)
    print('******')
```

---

## 作者：NotNaLocker (赞：0)

## UVA642 Word Amalgamation 题解
### ~~几~~句闲话
STL 大法好！
### 题目考点
- **模拟+字符串**

- **STL 的 next_permutation 函数**

什么是 next_permutation 函数？就是**给定一个数组，求它的下一个排列**。它的参数和 sort 很像：

`next_permutation(起始点，终止点);`

事实证明，这个函数不但可以排列整型数组，**字符数组**同样也可以。但是字符串不行。因为在设置终止点时，字符串得这样定义：

`s+s.size()`

但这又会与字符串本身的连接符 `+` 冲突，所以得把字符串化为字符数组。

另外，如果想要求出某一个序列的所有排列，必须把这个序列**按升序排列**。如果不，那么这个序列前的所有排列**都不会被纳入**。

### 具体实现
我们设置一个字符串数组 `dic` 表示字典，一个字符串 `word` 表示要解析的乱序字符。

```cpp
string dic[105],word;
```

用 while 循环输入字典单词，`n` 统计单词个数。注意最后要减一。

```cpp
while(cin>>dic[++n]&&dic[n]!="XXXXXX");
n--;
```

再用一个 while 输入单词，由于单词是 string 类型，需要创建一个字符数组并按升序排列，以便后面 next_permutation 函数的使用。

```cpp
while(cin>>word&&word!="XXXXXX"){	
	char wd[word.size()];
	for(int i=0;i<word.size();i++) wd[i]=word[i];
	sort(wd,wd+word.size(),cmp);  //cmp都会写吧
```

接着是核心部分：**枚举字典的每个单词，如果相同则输出**。为了判断输出 `NOT A VALID WORD` 的情况，我使用了一个 bool 变量标记。

```cpp
do{  //为输入的刚好是答案之一而考虑
	for(int i=0;i<word.size();i++) word[i]=wd[i];  //将排列后的字符数组赋值回到字符串，便于比较
	
	for(int i=1;i<=n;i++){
		if(dic[i]==word){
			cout<<word<<endl;
			is_find=true;  //标记是否找到
		}
	}
}while(next_permutation(wd,wd+word.size()));  //排列
```

最后判断是否找到：

```cpp
if(!is_find) cout<<"NOT A VALID WORD\n";
else is_find=false;  //还原
cout<<"******\n";
```

## AC Coding

```cpp
//不要ctj，从我做起。
#include<bits/stdc++.h>
using namespace std;
string dic[105],word;
int n;

bool cmp(char a,char b){
	return a<b;
}
bool is_find;

int main(){
	while(cin>>dic[++n]&&dic[n]!="XXXXXX");
	n--;
	while(cin>>word&&word!="XXXXXX"){
		
		char wd[word.size()];
		for(int i=0;i<word.size();i++) wd[i]=word[i];
		sort(wd,wd+word.size(),cmp);
			
		do{
			for(int i=0;i<word.size();i++) word[i]=wd[i];
			
			for(int i=1;i<=n;i++){
				if(dic[i]==word){
					cout<<word<<endl;
					is_find=true;
				}
			}
		}while(next_permutation(wd,wd+word.size()));
		if(!is_find) cout<<"NOT A VALID WORD\n";
		else is_find=false;
		cout<<"******\n";
	}
	return 0;  //华丽结束！
}

```

### 尾声
我在字符串与字符数组这里卡了 40 分钟 [qwq……](https://www.luogu.com.cn/record/106745848)

### 尾声的尾声
制作不易，还望点~个大大的赞！

---

