# bHTML Tables Analisys

## 题目描述

在这个问题中，使用了一个非常简单的HTML表格标记版本(bHTML)。 请把这个陈述作为题目的一部分，并仔细阅读。

如果一个字符串符合语法，它就是一个bHTML表

语法: <br></br>TABLE ::= <table>ROWS</table><br></br>ROWS ::= ROW | ROW ROWS<br></br>ROW ::= <tr>CELLS</tr><br></br>CELLS ::= CELL | CELL CELLS<br></br>CELL ::= <td></td> | <td>TABLE</td><br></br> 解释: 在语法中，只是为了说明的目的，在给定的数据中不会有空格。 bHTML表格非常类似于一个简单的普通HTML表格，其中只符合下列标签：“table”，“tr”，“td”，所有标签都配对，表格至少包含一行和至少一个单元格。在每一行中。为了更深入了解题意，请你看看样本测试，将其作为表格的例子。

可以看出，表格可以嵌套。 给你一个表（可能包含多组数据）。 你需要编写一个分析所有表格的程序，并找出每个表格中的单元格数量。 这些表格不需要是矩形的。

## 样例 #1

### 输入

```
<table><tr><td></td></tr></table>
```

### 输出

```
1 ```

## 样例 #2

### 输入

```
<table>
<tr>
<td>
<table><tr><td></td></tr><tr><td></
td
></tr><tr
><td></td></tr><tr><td></td></tr></table>
</td>
</tr>
</table>
```

### 输出

```
1 4 ```

## 样例 #3

### 输入

```
<table><tr><td>
<table><tr><td>
<table><tr><td>
<table><tr><td></td><td></td>
</tr><tr><td></td></tr></table>
</td></tr></table>
</td></tr></table>
</td></tr></table>
```

### 输出

```
1 1 1 3 ```

# 题解

## 作者：tzc_wk (赞：1)

省选/NOI-?这也未免太夸张了吧，这只是一道字符串模拟题，首先先读入，然后从头到尾扫过整个输入，整理出标签里的内容，如果是table就表明有一个新的表格，如果/table就表明当前表格结束了，退回到上级表格，如果是td那么当前表格单元格数量加1

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[5005];//s指整个输入
int ans[5000],total,pre[5000];//pre记录上级表格
int main(){
    char c;
    char s1[500];
    int l=0,i,q,k;
    while(~scanf("%c",&c)){
        if(c!='\n')	s[l++]=c;//读入，不用说
    }
    s[l]=0;//最后一个设为'\0'
    q=total=1;//q指当前层数，total指表格数量
    for(i=0;i<l;i++){
        if(s[i]=='<')	k=0;//k指的是标签的长度，s1指标签
        else if(s[i]=='>'){
            s1[k]=0;
            if(strcmp(s1,"table")==0){
                int m=q;//表格开头的编号
	            while(ans[q])
                	q++;
                pre[q]=m;//原表格的上级表格
                total++;//总表格数加1
            }
            else if(strcmp(s1,"/table")==0）
                q=pre[q];//表格结束了，回到原表格的上级表格
            else if(strcmp(s1,"td")==0)
                ans[q]++;//表格单元格数量加1
        }
        else	s1[k++]=s[i];//在标签里
    }
    sort(ans+1,ans+total);//因为题目中说按非递减顺序输出，所以要排个序
    for(i=1;i<total;i++)	cout<<ans[i]<< " ";//输出
    cout<<endl;
    return 0;
}
```

---

## 作者：Ag2WO4 (赞：0)

#### 前排提示：这是一篇 Python 题解！
~~とある非常水の栈模拟です。~~
#### 数据处理
直接使用 Python 的 ```sys.stdin.read()``` 获取所有数据，用 ```replace()``` 函数删掉换行和无用的项。我们只需关注三种项：

- ```<table>```：栈顶压入零，表示新的表格；
- ```<td>```：栈顶值加一，表示单元格；
- ```</table>```：弹出栈顶，表示表格结束。

这三种项也可以使用 ```replace()``` 函数转化成单字符方便运行。最后将结果排序即可。
#### AC 代码
```python
import sys;s=sys.stdin.read().replace('\n','').replace('<table>','!').replace('<tr>','').replace('<td>','@').replace('</td>','').replace('</tr>','').replace('</table>','#');a=[];b=[]
for i in s:
    if'!'==i:a.append(0)
    elif'@'==i:a[-1]+=1
    else:b.append(a.pop())
print(str(sorted(b))[1:-1].replace(',',''))
```


---

## 作者：Allanljx (赞：0)

## 题意
表格有 $6$ 种语法：```table /table tr /tr td /td```。```table``` 代表 $1$ 个表格开始；```/table``` 代表 $1$ 个表格结束；```tr /tr``` 没有意义；一组 ```td``` 和 ```/td``` 表示 $1$ 个单元格。问每个表格有多少个单元格（按增序输出）。

## 思路
这是一道模拟，所以我们的任务就变成尽量把代码写的简短一些。```table /table``` 的处理和括号匹配一样，可以用栈实现，栈存表格的编号。碰到 ```table``` 就加 $1$ 个表格进去，碰到 ```/table``` 就弹出栈顶。每次碰到 ```td``` 就给当前栈顶的表格加 $1$ 。碰到 ```/td tr /tr``` 就跳过。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
stack<int> st;//表格的编号 
string s,s1;
int ans[1005];//编号为i的表格中有多少个单元格 
int tmp;
signed main()
{
	while(cin>>s1) s+=s1;//将字符串拼起来 
	int l=s.length();
	for(int i=0;i<l;i++)
	{
		if(s[i]!='<') continue;//不用处理 
		if(s[i+1]!='/')
		{
			if(s[i+2]=='d') ans[st.top()]++;//td 
			else if(s[i+2]=='r') continue;//没有意义 
			else st.push(++tmp);//table 
		}
		else
		{
			if(s[i+3]=='d'||s[i+3]=='r') continue;//没有意义 
			else st.pop();//当前表格结束 
		}
	}
	sort(ans+1,ans+tmp+1);
	for(int i=1;i<=tmp;i++) cout<<ans[i]<<' ';
}
```

---

